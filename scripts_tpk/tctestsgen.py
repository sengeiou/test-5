#!/usr/bin/python

import os
import platform
import sys
import commands
import subprocess 
import re
import shutil
from shutil import copy
from os import path
from os import getenv
from sys import argv
from sys import exit
from string import capwords
from xml.etree.ElementTree import parse

def getFeature():
        xml = PACKAGING_DIR
	if(BUILD_TYPE=="ctc" or BUILD_TYPE=="itc"):
		xml += "native-"+MODULE_NAME+"-"+BUILD_TYPE+".xml"
	elif(BUILD_TYPE=="utc"):
		xml += "core-"+MODULE_NAME+"-"+"tests"+".xml"
	tree = parse(xml)
	root = tree.getroot()
	feature = []
	for child in root.iter("{http://tizen.org/ns/packages}feature"):
                if 'true' in child.text:
                    feature.append(child.attrib["name"])
	return feature

def gen(tcfile):
	# checking feature element
	feature = getFeature()
        
	set=''
	tfile=open(TFILE)
	fil=open(FILE, 'w')

	# begin
	fil.write('<?xml version="1.0" encoding="UTF-8"?>\n')
	fil.write('    <?xml-stylesheet type="text/xsl" href="./testcase.xsl"?>\n')
	fil.write('<test_definition>\n')
	fil.write('  <suite name="tct-'+MODULE_NAME+'-native-'+BUILD_TYPE+'" category="Native APIs">\n')

	for line in tfile:
		line=line.strip('\n')
		fields=line.split(',')
		if ( set != '' and set != fields[1] ):
			fil.write('    </set>\n')
		if ( set != fields[1] ):
			set=fields[1]
			fil.write('    <set name="'+set+'">\n')
			if(len(feature)!=0):
				print("feature is given : " + str(feature))
				fil.write('      <capabilities>\n')
				for element in feature:
        	                	fil.write('        <capability name="'+element+'"/>\n')
				fil.write('      </capabilities>\n')
		tcname=fields[0]
		tcpurpose=''
		
		fil.write('      <testcase component="NativeAPI/'+MODULE_NAME_C+'/'+set+'" execution_type="auto" id="'+tcname+'" purpose="'+tcpurpose+'">\n')
		fil.write('        <description>\n')
		fil.write('          <test_script_entry test_script_expected_result="0">'+'{DEVICE_SUITE_TARGET_30}/external_wrapper.sh '+MODULE_FULL_NAME+' '+tcname+' '+BUILD_TYPE+'</test_script_entry>\n')
		fil.write('        </description>\n')
		fil.write('      </testcase>\n')
	
	# end
	if ( set != '' ):
		fil.write('    </set>\n')
	fil.write('  </suite>\n')
	fil.write('</test_definition>\n')

	tfile.close()
	fil.close()
	return

### script starts here ###

if ( len(argv) < 5 ):
	print('Usage note: tctestsgen.py <build_type> <module_name> <path_to_xml>')
	exit()

# global variables

if ( platform.system() == 'Windows' ):
	dirSeparator='\\'
else:
	dirSeparator='/'

MODULE_NAME=argv[2]
profile=argv[4]
arch=argv[5]
TCT_CONFIG_FILE='/opt/tools/TCT_CONFIG'
#DEVICE_SUITE_TARGET_30=subprocess.check_output('cat '+TCT_CONFIG_FILE+' | grep DEVICE_SUITE_TARGET_30 | cut -f 2- -d =', shell=True)
#DEVICE_SUITE_TARGET_30=DEVICE_SUITE_TARGET_30.rstrip('\n')
BUILD_TYPE=argv[1]
MODULE_NAME_MOD=MODULE_NAME+'-native-'+BUILD_TYPE
MODULE_FULL_NAME='org.tizen.'+MODULE_NAME_MOD
MODULE_NAME_C=capwords(MODULE_NAME, '-').translate(None, '-')
SCRIPT_DIR=path.abspath(path.dirname(argv[0]))
WORKSPACE_SRC_DIR=getenv('HOME')+dirSeparator+'workspace'+'_'+profile+dirSeparator+MODULE_NAME_MOD
PACKAGING_DIR =SCRIPT_DIR+dirSeparator+".."+dirSeparator+"packaging"+dirSeparator+BUILD_TYPE+dirSeparator

FILE=argv[3]+dirSeparator+'tests.xml'
if ( path.exists(FILE) ):
	os.remove(FILE)

TFILE=dirSeparator+'tmp'+dirSeparator+'tcs.csv'
if ( path.exists(TFILE) ):
	os.remove(TFILE)

os.chdir(SCRIPT_DIR+dirSeparator+'..')
# test this a bit
status=commands.getstatusoutput('scripts_tpk'+dirSeparator+'retriever.py -f '+WORKSPACE_SRC_DIR+' '+BUILD_TYPE+' '+profile+' '+MODULE_NAME+' '+arch+' > '+TFILE+'_pre')
if ( (status[0] % 256) != 0 ):
	tfil_pre=open(TFILE+'_pre')
	for line in tfile_pre:
		print(line.strip('\n'))
	tfile_pre.close()
	exit('Error executing retriever.py!!! Aborting...')
# TODO sort tcs based on set field (module)
status=os.system('cat '+TFILE+'_pre | sort -t\',\' -k2,2 -s > '+TFILE)
#copy(TFILE+'_pre', TFILE)

#####exclude.list#####
if ( arch == 'x86' ):
	if os.path.exists('custom_tclist/Emulator.tclist_'+profile) and os.path.getsize('custom_tclist/Emulator.tclist_'+profile) > 0:
		NEWFILE="/tmp/tnum.csv_pre_new"
		dest=open(TFILE,'r')
		new_file=open(NEWFILE,'w')
		src=open('custom_tclist/Emulator.tclist_'+profile,'r')
		for line in dest:
			FLAG=1
			test1=line.strip('\n')
			src.seek(0)
			for f in src:
				test2=f.strip('\n')
				if (test1.find(test2)>=0):
					FLAG=0
					break
			if FLAG==1:
				new_file.write(line)
		src.close()
		dest.close()
		new_file.close()
		shutil.copy(NEWFILE,TFILE)
if os.path.exists('exclude.list') and os.path.getsize('exclude.list') > 0:
	NEWFILE="/tmp/tnum.csv_pre_new"
	dest=open(TFILE,'r')
	new_file=open(NEWFILE,'w')
	src=open('exclude.list','r')
	for line in dest:
		FLAG=1
		test1=line.strip('\n')
		src.seek(0)
		for f in src:
			test2=f.strip('\n')
			if (test1.find(test2)>=0):
				FLAG=0
				break
		if FLAG==1:
			new_file.write(line)
	src.close()
	dest.close()
	new_file.close()
	shutil.copy(NEWFILE,TFILE)
#####exclude.list#####

gen(TFILE)
