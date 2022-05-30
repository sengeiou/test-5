#!/usr/bin/python3

import os
import argparse
import re
import sys
import shutil
from sys import argv

def printUsage():
	print('Usage note: retriever.py [option] [directory] [build_type]')
	print('Options:')
	print('  -n      retrieve TC names with corresponding startup and cleanup functions')
	print('  -f      retrieveve TC name with corresponding "set" and "purpose" clauses')
	print('  -anum   retrieve automatic TC number')
	print('  -mnum   retrieve manual TC number')
	print('')
	print('In case of TC in form of "int tc_name()" script will abort.')
	print('("int tc_name(void)" is a proper function signature)')

	return

def get_tc_files_new(dir,module_name,tag,device_type):
#	FILES=[]
#	print('DIR****************************************'+dir)
#	print("*******module"+MODULE_NAME)
#	FILES=dir+'/inc/tct-'+MODULE_NAME+'-'+TAG+'_'+DEVICE_TYPE+'.h'
	if ( some_data[0] == 'src' ):
		FILES=dir+'/tct-'+module_name+'-'+tag+'_'+device_type+'.h'
	else:
		FILES=dir+'/inc/tct-'+module_name+'-'+tag+'_'+device_type+'.h'
#	print('FILES: '+FILES)
	return FILES

def get_tc_files(dir):
	FILES=[]
	if ( TYPE == 'ctc' ):
		prefix='CTs'
	elif (TYPE == 'itc' ):
		prefix='ITs'
	elif (TYPE == 'utc' ):
		prefix='utc'

	for root, dirs, files in os.walk(dir):
		for f in files:
			if ( re.search('^'+prefix+'.*\.(c|cpp)$', f) ):
				FILES.append(os.path.join(root, f))
	return FILES

def tc_names(TC_FILES):
	TC_LIST=[]
	for f in TC_FILES:
		fil=open(f)
		errFlag=False
		lineCount=0
		start_fn=''
		clean_fn=''
		for line in fil:
			lineCount+=1
			start_m=re.search('^void (?P<fn>.*startup)\(void\)', line)
			clean_m=re.search('^void (?P<fn>.*cleanup)\(void\)', line)
			tc_m=re.search('^int (?P<fn>.*)\(void\)', line)
			err_m=re.search('^int (?P<fn>.*)\(\)', line)
			if ( start_m != None ):
				start_fn=start_m.group('fn')
			elif ( clean_m != None ):
				clean_fn=clean_m.group('fn')
			elif ( tc_m != None ):
				TC_LIST.append(tc_m.group('fn')+','+start_fn+','+clean_fn)
			elif ( err_m != None ):
				print('Warning: function with empty argument list -- " '+err_m.group('fn')+' " in " '+f+' ":" '+lineCount)
				errFlag=True

		fil.close()
		if ( errFlag ):
			sys.exit()

	for tc in TC_LIST:
		print(tc)

	return

def tc_anum(TC_FILES):
	TC_COUNT=0
	for f in TC_FILES:
		fil=open(f)
		errFlag=False
		lineCount=0
		for line in fil:
			lineCount+=1
			err_m=re.search('^int (?P<fn>.*)\(\)', line)
			if (  err_m != None ):
				print('Warning: function with empty argument list -- " '+err_m.group('fn')+' " in " '+f+' ":" '+lineCount)
				errFlag=True
			elif ( re.search('^int (?P<fn>.*)\(void\)', line) != None ):
				TC_COUNT+=1

		fil.close()
		if ( errFlag ):
			sys.exit()

	TC_CUSTOM_COUNT=int(argv[6])
	TC_COUNT=TC_COUNT*TC_CUSTOM_COUNT
	print(TC_COUNT)

	return

def tc_mnum(TC_FILES):
	# TODO
	print(0)
	return

TFILE="/tmp/tnum.csv"
TFILEPRE="/tmp/tnum.csv_pre"
def tc_fullinfo(TC_FILES):
	TC_LIST=[]
	fil=open(TC_FILES)
	lineCount=0
	errFlag=False
	set='Default'
	purpose=''
	for line in fil:
		lineCount+=1
		tc_m=re.search('^extern int (?P<fn>.*)\(void\)\;', line)
		err_m=re.search('^extern int (?P<fn>.*)\(\)', line)
		if ( tc_m != None ):
			TC_LIST.append(tc_m.group('fn')+','+set+','+purpose)
		elif (  err_m != None ):
			print('Warning: function with empty argument list -- " '+err_m.group('fn')+' " in " '+f+' ":" '+lineCount)
			errFlag=True
	fil.close()
	if ( errFlag ):
		sys.exit()

	#for tc in TC_LIST:
		#print(tc)
	
	f=open(TFILEPRE, 'w')
	for tc in TC_LIST:
		f.write(tc+'\n')
		print(tc)

	f.close()

	return

TFILE='/tmp/tnum.csv'
NEWFILE="/tmp/tnum.csv_pre_new"

def tc_anum2(TC_FILES):
	TC_COUNT=0

	#####exclude.list#####
	if ( arch == 'x86' ):
		if os.path.exists('custom_tclist/Emulator.tclist_'+DEVICE_TYPE) and os.path.getsize('custom_tclist/Emulator.tclist_'+DEVICE_TYPE) > 0:
			dest=open(TFILEPRE,'r')
			new_file=open(NEWFILE,'w')
			src=open('custom_tclist/Emulator.tclist_'+DEVICE_TYPE,'r')
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
			shutil.copy(NEWFILE,TFILEPRE)
	if os.path.exists('exclude.list'):
		dest=open(TFILEPRE,'r')
		new_file=open(NEWFILE,'w')
		src=open('exclude.list','r')
		for line in dest:
			FLAG=1
			checking=False
			test1=line.strip('\n')
			src.seek(0)
			for line_in_list in src:
				stripped_line=line_in_list.strip('\n')
				#for profile
				if(stripped_line.startswith('##') and stripped_line.endswith('##')):
					end_hash_index = stripped_line.find('##',2)
					profile_name = stripped_line[3:end_hash_index-1]	#for removing trailing and leading space
					#check if the profile is all
					if(profile_name == 'all'):
						checking = True
					elif(profile_name == profile):
						checking = True
					else:
						checking = False
				#for build_type
				if(checking == True and stripped_line.startswith(TYPE)):
					tc_name_index = stripped_line.find(':')
					tc_name = stripped_line[tc_name_index+1:]
					if (test1.find(tc_name)>=0):
						FLAG=0
						break
			if FLAG==1:
				new_file.write(line)
		src.close()
		dest.close()
		new_file.close()
		shutil.copy(NEWFILE,TFILEPRE)
	#####exclude.list#####

	f=open(TFILEPRE,'r')
	for tc in f:
		TC_COUNT+=1
	f.close()
	TC_CUSTOM_COUNT=int(argv[6])
	TC_COUNT = TC_COUNT * TC_CUSTOM_COUNT
	print(TC_COUNT)
#        os.system('cat '+TFILE+'_pre | sort -t\',\' -k2,2 -s > '+TFILE+'_remove')
#        os.system('awk "!x[$0]++" '+TFILE+'_remove > '+TFILE)
#        count=os.system('cat '+TFILE+' | wc -l')
#        count=os.system('cat '+TFILE+'_remove | wc -l')
#        os.system('rm '+TFILE+' '+TFILE+'_pre '+TFILE+'_remove')
#        os.system('rm '+TFILE+'_pre '+TFILE+'_remove')
	return

# global variables

DIR=None
TYPE=None
TC_FILES=""
TAG='native'
some_data=None

### script starts here ###

lenArgs=len(argv)

if ( lenArgs == 1 ):
	sys.exit()

DEVICE_TYPE=argv[4]
profile=DEVICE_TYPE
MODULE_NAME=argv[5]
if ( argv[1] == '-anum' ):
	arch=argv[7]
if ( (argv[1][0] == '-' and ( (re.search('^-(anum|mnum|f|n)$', argv[1]) == None) or (lenArgs > 8) )) or ( (argv[1][0] != '-') and (lenArgs > 1) ) ):
	printUsage()
	sys.exit()

if ( lenArgs > 3 ):
	TYPE=argv[3]

if ( re.search('^-(anum|mnum|f)$', argv[1]) == None ):
	DIR='.'
	if ( argv[1] == '-n' ):
		if ( lenArgs > 8 ):
			DIR=argv[8]
	else:
		DIR=argv[1]
else:
	if ( lenArgs > 2 ):
		DIR=argv[2]

if ( TYPE == 'utc' ):
	TAG='core'
some_data=argv[2].split("/")

#TC_FILES=get_tc_files(DIR)
TC_FILES=get_tc_files_new(DIR,MODULE_NAME,TAG,DEVICE_TYPE)
command=argv[1]
if ( command == '-anum' ):
	tc_anum2(TC_FILES)
elif ( command == '-mnum' ):
	tc_mnum(TC_FILES)
elif ( command == '-f' ):
	tc_fullinfo(TC_FILES)
elif ( command == '-n' ):
	tc_names(TC_FILES)
else:
	tc_names(TC_FILES)
