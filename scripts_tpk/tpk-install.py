#!/usr/bin/python

import platform
import os
import stat
import sys
import time
import commands
import subprocess
import re
import argparse
import shutil
import zipfile
import gentestsxml
from gentestsxml import *

def copytpk(btype, module,arch):
	if ( os.path.exists(TPK_DIR) == False ):
		os.makedirs(TPK_DIR)

	os.chdir(WORKSPACE_DIR)
	PKG_NAME='org\.tizen\.'+module
	PKG_NAME=PKG_NAME+'-native-'+btype
	VER='1\.0\.0'
	PKG_VNAME=PKG_NAME+'-'+VER
	PKG_VNAME=PKG_VNAME+'-'+arch
	FIND_FILE=PKG_VNAME+'\.tpk'
	for root, dirs, files in os.walk(os.getcwd()):
		for f in files:
			if ( re.search(FIND_FILE, f) != None ):
				shutil.copy(os.path.join(root, f), TPK_DIR+dirSeparator)
				print('COPYING: '+PKG_NAME.replace('\\', '')+' tpk file is copied to '+TPK_DIR)
	return

def removeDir(path):
	for root, dirs, files in os.walk(path, topdown=False):
		if ( len(dirs) == 0 ):
			for f in files:
				try:
					os.remove(os.path.join(root, f))
				except(OSError):
					return False

		elif ( len(files) == 0 ):
			for d in dirs:
				try:
					os.removedirs(os.path.join(root, d))
				except(OSError):
					return False
	try:
		os.rmdir(path)
	except(OSError):
		# if exception is raised here it means dir is not empty and this shouldnot happen
		return False

	return True

def install(TYPE, MODNAME, PROFILE, TC_COUNT, ARCH, COVERAGE):

	rpmCheck=False
	global INSTALL_PKG_COUNT
	if ( TYPE == None ):
		install('ctc', None, PROFILE, TC_COUNT, ARCH, COVERAGE)
		install('itc', None, PROFILE, TC_COUNT, ARCH, COVERAGE)
		install('utc', None, PROFILE, TC_COUNT, ARCH, COVERAGE)
	else:
		if ( MODNAME == None ):
			#os.chdir(WORKSPACE_DIR)
			for root, dirs, files in os.walk(WORKSPACE_DIR):
				for f in files:
					r=re.search('^org\.tizen\.(?P<module_name>.*)-native-'+TYPE+'-1\.0\.0-'+ARCH+'\.tpk', f)
					if ( r ):
						install(TYPE, r.group('module_name'), PROFILE, TC_COUNT, ARCH, COVERAGE)

		else:
			print('')
			print('********************START Installing '+TYPE+':'+MODNAME+'**********************')
			copytpk(TYPE, MODNAME, ARCH)
			os.chdir(PROJECT_DIR)
			# setting variables
			PKG_NAME='org.tizen.'+MODNAME+'-native-'+TYPE
			VER='1.0.0'
			PKG_VNAME=PKG_NAME+'-'+VER+'-'+ARCH
			PKG_FNAME=PKG_VNAME+'.tpk'
			if ( os.path.exists(TPK_DIR+dirSeparator+PKG_FNAME) == False):
				sys.exit('Package Not Found '+PKG_VNAME)
			TIZEN____='tizen_native_6.5'
			TCT_DIR='opt'+dirSeparator+'tct-'+MODNAME+'-native-'+TYPE
			TO_PKG_DIR=dirSeparator+'opt'+dirSeparator+'tct'+dirSeparator+TIZEN____+dirSeparator+'packages'

			print('Deploying '+TYPE+'->'+MODNAME+' suite to tct-mgr...')
			# prepare tct directory and files
			print('-- Preparing suite .zip file...')
			print('---- Creating '+dirSeparator+'tmp'+dirSeparator+TCT_DIR+' directory')
			removeDir(dirSeparator+'tmp'+dirSeparator+'opt')
			os.makedirs(dirSeparator+'tmp'+dirSeparator+TCT_DIR)

			# README
			print('---- Copying '+dirSeparator+'tmp'+dirSeparator+TCT_DIR)
			shutil.copy('scripts_tpk'+dirSeparator+'README', dirSeparator+'tmp'+dirSeparator+TCT_DIR)

			# tpk
			print('---- Copying '+dirSeparator+'tmp'+dirSeparator+TCT_DIR+' package')
			try:
				shutil.copy(TPK_DIR+dirSeparator+PKG_FNAME, dirSeparator+'tmp'+dirSeparator+TCT_DIR)
			except(shutil.Error):
				sys.exit('Aborting...')

			# inst.sh
			print('---- Generating '+dirSeparator+'tmp'+dirSeparator+TCT_DIR+dirSeparator+'inst.sh file')
			# TODO port for windows
			#status=os.system('sed -e "s:%{PKG_NAME}:"'+PKG_NAME+'":g" \
			#	-e "s:%{PKG_FULLNAME}:"'+PKG_FNAME+'":g" \
			#	-e "s:%{PKG_DIR}:"/opt/usr/media/tct/'+TCT_DIR+'":g" \
			#	scripts_tpk/inst.sh > /tmp/'+TCT_DIR+'/inst.sh')
			src_f=open('scripts_tpk'+dirSeparator+'inst.sh')
			dest_f=open(dirSeparator+'tmp'+dirSeparator+TCT_DIR+dirSeparator+'inst.sh', 'w')

			for line in src_f:
			
				pkg_dir_m=re.search('^\sPKG_DIR=(?P<pkg_dir>%{PKG_DIR})', line)
				pkg_name_m=re.search('^\sPKG_NAME=(?P<pkg_name>%{PKG_NAME})', line)
				pkg_fname_m=re.search('^\sPKG_FULLNAME=(?P<pkg_fname>%{PKG_FULLNAME})', line)
				if ( pkg_dir_m != None ):
					PKG_DIR=dirSeparator+'home'+dirSeparator+'owner'+dirSeparator+'share'+dirSeparator+'tct'+dirSeparator+TCT_DIR
					line=line.replace('%{PKG_DIR}', '"'+PKG_DIR+'"')
				elif ( pkg_name_m != None ):
					line=line.replace('%{PKG_NAME}', '"'+PKG_NAME+'"')
				elif ( pkg_fname_m != None ):
					line=line.replace('%{PKG_FULLNAME}', '"'+PKG_FNAME+'"')


				dest_f.write(line)
			src_f.close()
			dest_f.close()

			#if ( (status % 256) != 0 ):
			#	sys.exit('Error executing inst.sh!!! Aborting...')
			os.chmod(dirSeparator+'tmp'+dirSeparator+TCT_DIR+dirSeparator+'inst.sh', stat.S_IXUSR|stat.S_IXGRP|stat.S_IXOTH|stat.S_IRUSR|stat.S_IRGRP|stat.S_IROTH|stat.S_IWUSR)

			# tests.xml
			print('---- Generating '+dirSeparator+'tmp'+dirSeparator+TCT_DIR)
			status=commands.getstatusoutput('scripts_tpk'+dirSeparator+'tctestsgen.py '+TYPE+' '+MODNAME+' '+dirSeparator+'tmp'+dirSeparator+TCT_DIR+' '+PROFILE+' '+ARCH)
			if ( len(status[1]) > 0 ):
				print(status[1])
			if ( ( status[0] % 256 ) != 0 ):
				print('Failed to execute tctestsgen.py!!!')
				sys.exit('Aborting...')

			# external_wrapper.sh

			process_dali_application = "dali-application"
			process1 = "dali-"
			process2 = "_dali"
			if ( re.search(process_dali_application, MODNAME) != None ):
				shutil.copy('scripts_tpk'+dirSeparator+'external_wrapper_dali_app_launch.sh', dirSeparator+'tmp'+dirSeparator+TCT_DIR+dirSeparator+'external_wrapper.sh')
			elif ( re.search(process1, MODNAME) != None or re.search(process2, MODNAME) != None ):
				shutil.copy('scripts_tpk'+dirSeparator+'external_wrapper_dali_multi_app_launch.sh', dirSeparator+'tmp'+dirSeparator+TCT_DIR+dirSeparator+'external_wrapper.sh')
			elif ( COVERAGE == '1' ):
				print('-- Using Coverage Wrapper...')
				shutil.copy('scripts_tpk'+dirSeparator+'external_wrapper_coverage.sh', dirSeparator+'tmp'+dirSeparator+TCT_DIR+dirSeparator+'external_wrapper.sh')
			else:
				shutil.copy('scripts_tpk'+dirSeparator+'external_wrapper.sh', dirSeparator+'tmp'+dirSeparator+TCT_DIR)

			# LICENSE, add_all_smack_rule.sh, all_smack.rule
			shutil.copy('scripts_tpk'+dirSeparator+'LICENSE', dirSeparator+'tmp'+dirSeparator+TCT_DIR)

			# gentestsxml.py generate multiple TC in tests.xml
			if int(TC_COUNT) > 1:
				gentestsxml.gentestxmlfile(dirSeparator+'tmp'+dirSeparator+TCT_DIR+dirSeparator, TC_COUNT)

			# zip
			print('---- Preparing '+dirSeparator+'tmp'+dirSeparator+'tct'+dirSeparator+'packages'+dirSeparator+'tct-'+MODNAME+'-'+'native-'+TYPE+'-6.5.zip file')

			# clear old zips
			removeDir(dirSeparator+'tmp'+dirSeparator+'tct'+dirSeparator+'packages')
			os.makedirs(dirSeparator+'tmp'+dirSeparator+'tct'+dirSeparator+'packages')

			# create new zip
			#os.chdir(dirSeparator+'tmp')
			zipper(dirSeparator+'tmp'+dirSeparator+'opt', dirSeparator+'tmp'+dirSeparator+'tct'+dirSeparator+'packages'+dirSeparator+'tct-'+MODNAME+'-native-'+TYPE+'-6.5.zip', True, dirSeparator)

			# deployment
			print('-- Suite deployment...')
			print('---- Copying '+TO_PKG_DIR+dirSeparator+PROFILE+dirSeparator+'tct-'+MODNAME+'-native-'+TYPE+'-6.5.zip')
			if ( os.path.exists(TO_PKG_DIR+dirSeparator+PROFILE) == False):
				os.makedirs(TO_PKG_DIR+dirSeparator+PROFILE)
			shutil.copy(dirSeparator+'tmp'+dirSeparator+'tct'+dirSeparator+'packages'+dirSeparator+'tct-'+MODNAME+'-native-'+TYPE+'-6.5.zip', TO_PKG_DIR+dirSeparator+PROFILE)
			print('---- Updating '+TO_PKG_DIR+dirSeparator+'pkg_infos'+dirSeparator+PROFILE+'_pkg_info.xml')
			status=commands.getstatusoutput('scripts_tpk'+dirSeparator+'tcpackageslistsgen.py '+TYPE+' '+MODNAME+' '+PROFILE+' '+TO_PKG_DIR+dirSeparator+'pkg_infos'+dirSeparator+PROFILE+'_pkg_info.xml 0'+' '+TC_COUNT+' '+ARCH)
			if ( len(status[1]) > 0 ):
				print(status[1])
			if ( removeDir(TPK_DIR) == False ):
				sys.exit('Error removing '+TPK_DIR+'. Aborting...')
			print('**************Task finished successfully*********************')
			print('')
			os.chdir(PROJECT_DIR)
			logFile=open('install.log', 'a')
			logFile.write(TYPE+':->'+MODNAME+'\n')
			logFile.close()
			INSTALL_PKG_COUNT+=1

	return

def zipper(zip_dir, zip_file, include_root, sep):
	zf = zipfile.ZipFile(zip_file, 'w', compression=zipfile.ZIP_DEFLATED)
	root_len = len(os.path.abspath(zip_dir))
	if ( include_root ):
		zip_root=os.path.abspath(zip_dir).strip(sep).split(sep)[-1]
		root_len-=len(zip_root)
	for root, dirs, files in os.walk(zip_dir):
		archive_root = os.path.abspath(root)[root_len:]
		for f in files:
			fullpath = os.path.join(root, f)
			archive_name = os.path.join(archive_root, f)
			if(profile == "tv"):
				#If profile is tv final zip file will be signed by kuep certificate as it contains .sh and .tpk
				if  f.endswith('.sh'):
					print('signing of ' + fullpath + ' is started')
					os.system('./scripts_tpk/kuep_net_signer.sh -s -tizen_major_ver 6 ' + fullpath)
					print('signing of ' + fullpath + ' successfully done')
			zf.write(fullpath, archive_name, zipfile.ZIP_DEFLATED)
	zf.close()
	return zip_file

# global variables
dirSeparator='/'

module=None
build_ctype=None
profile=None
tc_count=None
is_coverage=0
INSTALL_PKG_COUNT=0

### script starts here ###

OS=platform.system()
if ( OS == 'Windows' ):
	dirSeparator='\\'

PROJECT_DIR=(os.path.abspath(os.path.dirname(sys.argv[0])))
TPK_DIR=os.getenv('HOME')+dirSeparator+'tpks'
WORKSPACE_DIR=os.getenv('HOME')+dirSeparator+'workspace'+'_'+ sys.argv[2]

# TODO use argparse
if ( len(sys.argv) >= 2 ):
	arch=sys.argv[1]
if ( len(sys.argv) >= 3 ):
	profile=sys.argv[2]
if ( len(sys.argv) >= 4 ):
	tc_count=sys.argv[3]
if ( len(sys.argv) >= 5 ):
	is_coverage=sys.argv[4]
if ( len(sys.argv) >= 6 ):
	build_ctype=sys.argv[5]
if ( len(sys.argv) >= 7 ):
	module=sys.argv[6]


if ( os.path.exists('install.log') ):
	os.remove('install.log')

instLog=open('install.log', 'w')
instLog.write('**********************************************\n')
instLog.write('Following packages get installed successfully:\n')
instLog.close()

install(build_ctype, module, profile,tc_count, arch, is_coverage)

if ( module == None ):
	instLog=open('install.log', 'a')
	instLog.write('**********************************************\n')
	instLog.write('Total Intall PASS Count = ' + str(INSTALL_PKG_COUNT) + '\n')
	instLog.close()
	instLog=open('install.log')
	for line in instLog:
		print(line.strip('\n'))
	instLog.close()

os.remove('install.log')


