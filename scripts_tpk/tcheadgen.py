#!/usr/bin/python

import os
import sys
import platform
import re
import commands
import shutil
from shutil import copy
from commands import getstatusoutput
from os import path
from sys import argv
from sys import exit

def gen():
	startup_counter = 0;
	startup_list=[];

	cleanup_counter = 0;
	cleanup_list=[];

	testcase_counter = 0;
	testcase_list=[];

	tc_array_counter = 0;
	tc_array_list=[];

	tf=open(TFILE)
	f=open(FILE, 'w')
	
	f.write('//\n// Copyright (c) 2021 Samsung Electronics Co., Ltd.\n//\n// Licensed under the Apache License, Version 2.0 (the License);\n// you may not use this file except in compliance with the License.\n// You may obtain a copy of the License at\n//\n//     http://www.apache.org/licenses/LICENSE-2.0\n//\n// Unless required by applicable law or agreed to in writing, software\n// distributed under the License is distributed on an "AS IS" BASIS,\n// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n// See the License for the specific language governing permissions and\n// limitations under the License.\n//\n')
	f.write('#ifndef __'+HEADER_NAME+'__\n')
	f.write('#define __'+HEADER_NAME+'__\n')
	f.write('\n')
	f.write('#include "testcase.h"\n')
	f.write('#include "tct_common.h"\n')
	f.write('\n')

	for line in tf:
		fields=line.strip('\n').split(',')
		testcase_list.append(fields[0])
		testcase_counter+=1
		
		if ( (startup_counter == 0) or (startup_list[startup_counter-1] != fields[1]) ):
			startup_list.append(fields[1])
			startup_counter+=1
		
		if ( (cleanup_counter == 0) or (cleanup_list[cleanup_counter-1] != fields[2]) ):
			cleanup_list.append(fields[2])
			cleanup_counter+=1

		if ( fields[1] and fields[2] ):
			tc_array_list.append('"'+fields[0]+'", '+fields[0]+', '+fields[1]+', '+fields[2])
		else:
			tc_array_list.append('"'+fields[0]+'", '+fields[0]+', '+'NULL'+', '+'NULL')

		tc_array_counter+=1

	if ( startup_counter > cleanup_counter ):
		sc_count=startup_counter
	else:
		sc_count=cleanup_counter

	for i in range(sc_count):
		if ( (i < startup_counter) and (startup_list[i] != '') ):
			f.write('extern void '+startup_list[i]+'(void);\n')
		if ( (i < cleanup_counter) and (cleanup_list[i] != '') ):
			f.write('extern void '+cleanup_list[i]+'(void);\n')

	f.write('\n')

	for i in range(testcase_counter):
		f.write('extern int '+testcase_list[i]+'(void);\n')

	f.write('\n')
	f.write('testcase tc_array[] = {\n')

	for i in range(tc_array_counter):
		f.write('    {'+tc_array_list[i]+'},\n')

	f.write('    {NULL, NULL}\n')
	f.write('};\n')
	f.write('\n')
	f.write('#endif // __'+HEADER_NAME+'__\n')

	tf.close()
	f.close()

	return

### script starts here ###

if ( len(argv) < 4 ):
	print('Usage note: tcheadgen.py <header_filename.h> <src_dir> <build_type>')
	exit()

# global variables

if ( platform.system() == 'Windows' ):
	dirSeparator='\\'
else:
	dirSeparator='/'

FILE=os.getcwd()+dirSeparator+argv[1]
TFILE=dirSeparator+'tmp'+dirSeparator+'retr.csv'
HEADER_NAME=argv[1].upper().replace('-', '_').replace('.', '_')
SCRIPT_DIR=path.abspath(path.dirname(argv[0]))

status=getstatusoutput(SCRIPT_DIR+dirSeparator+'retriever.py -n '+argv[2]+' '+argv[3]+' > '+TFILE+'_pre')
if ( (status[0] % 256) != 0 ):
	tfile_pre=open(TFILE+'_pre')
	for line in tfile_pre:
		print(line.strip('\n'))
	tfile_pre.close()
	exit('Error executing retriever.py!!! Aborting...')

# TODO sort tcs based on set field (module name)
status=os.system('cat '+TFILE+'_pre | sort -t\',\' -k2,2 -s > '+TFILE+'_remove')
#copy(TFILE+'_pre', TFILE+'_remove')

# remove duplicate lines
tfr=open(TFILE+'_remove')
tf=open(TFILE, 'w')
x={}
for l in tfr:
	tc=l.split(',')[0]
	if ( (tc in x.keys()) == False ):
		x[tc]=1
		tf.write(l)
tfr.close()
tf.close()

gen()
