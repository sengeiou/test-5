#!/usr/bin/python3

import os
import sys
import platform
import re
import subprocess
import shutil
from shutil import copy
from os import path
from sys import argv
from sys import exit

def regen():
	found=0
	replaced=0

	f=open(FILE)
	tf=open(TFILE, 'w')

	for line in f:
		match=re.search('\s<suite name="tct-'+MODULE_NAME+'-native-'+TYPE+'"\scategory="\s'+CATEGORY+'\s"', line)
		if ( match != None ):
			found=1
			continue
		match=re.search('</suite>', line)
		if ( match != None ):
			if ( (found == 1) and (RMMOD == 0) ):
				tf.write('  <suite name="tct-'+MODULE_NAME+'-native-'+TYPE+'" category=" '+CATEGORY+' ">\n')
				tf.write('    <auto_tcn>'+AUTO_NUM+'</auto_tcn>\n')
				tf.write('    <manual_tcn>'+MAN_NUM+'</manual_tcn>\n')
				tf.write('    <total_tcn>'+TOT_NUM+'</total_tcn>\n')
				tf.write('    <pkg_name>'+PROFILE+'/tct-'+MODULE_NAME+'-native-'+TYPE+'-7.0.zip</pkg_name>\n')
				tf.write('  </suite>\n')

				found = 0;
				replaced = 1;
			elif ( (found == 1) and (RMMOD == 1) ):
				found=0
				replaced=1
			else:
				tf.write(line)

			continue
		match=re.search('</ns3:testplan>', line)
		if ( match != None ):
			if ( (replaced == 0) and (RMMOD == 0) ):
				tf.write('  <suite name="tct-'+MODULE_NAME+'-native-'+TYPE+'" category=" '+CATEGORY+' ">\n')
				tf.write('    <auto_tcn>'+AUTO_NUM+'</auto_tcn>\n')
				tf.write('    <manual_tcn>'+MAN_NUM+'</manual_tcn>\n')
				tf.write('    <total_tcn>'+TOT_NUM+'</total_tcn>\n')
				tf.write('    <pkg_name>'+PROFILE+'/tct-'+MODULE_NAME+'-native-'+TYPE+'-7.0.zip</pkg_name>\n')
				tf.write('  </suite>\n')
				tf.write(line+'\n')
			else:
				tf.write(line)

			continue
		if ( found == 0 ):
			tf.write(line)

	f.close()
	tf.close()

	copy(TFILE, FILE)

	return

### script starts here ###

if ( len(argv) < 5 ):
	print('Usage note: tcpackageslistsgen.py <type> <module_name> <profile> <output_file.xml>')
	exit()

# global variables

if ( platform.system() == 'Windows' ):
	dirSeparator='\\'
else:
	dirSeparator='/'

TYPE=argv[1]
MODULE_NAME=argv[2]
PROFILE=argv[3]
FILE=argv[4]
RMMOD=int(argv[5])
TC_COUNT=int(argv[6])
ARCH=argv[7]
if ( path.exists(FILE) == False ):
	exit('No such file: '+FILE)

MODULE_NAME_MOD=MODULE_NAME+'-native-'+TYPE
WORKSPACE_SRC_DIR=os.getenv('HOME')+dirSeparator+'workspace'+'_'+PROFILE+dirSeparator+MODULE_NAME_MOD

CATEGORY='IntegrationTestCases'
if ( TYPE == 'utc' ):
	CATEGORY='UnitTestCases'
if ( TYPE == 'ctc' ):
	CATEGORY='CompatibilityTestCases'

SCRIPT_DIR=path.abspath(path.dirname(argv[0]))
cwd=os.getcwd()
os.chdir(SCRIPT_DIR)
os.chdir('..')
status, output=subprocess.getstatusoutput('scripts_tpk'+dirSeparator+'retriever.py -anum '+WORKSPACE_SRC_DIR+' '+TYPE+' '+PROFILE+' '+MODULE_NAME+' '+str(TC_COUNT)+' '+ARCH)
if ( status > 0 ):
	exit(output)
else:
	AUTO_NUM=output

status, output=subprocess.getstatusoutput('scripts_tpk'+dirSeparator+'retriever.py -mnum '+WORKSPACE_SRC_DIR+' '+TYPE+' '+PROFILE+' '+MODULE_NAME+' '+str(TC_COUNT)+' '+ARCH)
if ( status > 0 ):
	exit(output)
else:
	MAN_NUM=output
TOT_NUM=str(int(AUTO_NUM)+int(MAN_NUM))

TFILE=dirSeparator+'tmp'+dirSeparator+'tempfile.xml'
if ( path.exists(TFILE) ):
	os.remove(TFILE)

regen()
