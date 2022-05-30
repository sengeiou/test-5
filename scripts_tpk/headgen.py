####################################### Script to generate Header files ########################################
#################################### Developed by ambarish.p@samsung.com #######################################
import os
import os.path
import re
import sys
###################################### Generate function starts here #####################################
def generate(profile,module):
	if profile == "mobile":
		profile_check_1 = "defined(MOBILE)"
		profile_check_11 = "def MOBILE"
		profile_check_2 = "defined(WEARABLE)"
		profile_check_22 = "def WEARABLE"
		profile_check_3 = "defined(TIZENIOT)"
		profile_check_33 = "def TIZENIOT"
		profile_check_4 = "defined(TV"
		profile_check_44 = "def TV"
		cmake_check_1 = "DEFINED MOBILE"
		cmake_check_2 = "DEFINED WEARABLE"
		cmake_check_3 = "DEFINED TIZENIOT"
		cmake_check_4 = "DEFINED TV"
	elif profile == "wearable":
        	profile_check_2 = "defined(MOBILE)"
		profile_check_22 = "def MOBILE"
        	profile_check_1 = "defined(WEARABLE)"
		profile_check_11 = "def WEARABLE"
        	profile_check_3 = "defined(TIZENIOT)"
		profile_check_33 = "def TIZENIOT"
        	profile_check_4 = "defined(TV"
		profile_check_44 = "def TV"
        	cmake_check_2 = "DEFINED MOBILE"
        	cmake_check_1 = "DEFINED WEARABLE"
        	cmake_check_3 = "DEFINED TIZENIOT"
        	cmake_check_4 = "DEFINED TV"
	#elif profile == "commoniot" or profile == "tizeniot":
        #	profile_check_3 = "defined(MOBILE)"
	#	profile_check_33 = "def MOBILE"
        #	profile_check_2 = "defined(WEARABLE)"
	#	profile_check_22 = "def WEARABLE"
        #	profile_check_1 = "defined(TIZENIOT)"
	#	profile_check_11 = "def TIZENIOT"
        #	profile_check_4 = "defined(TV"
	#	profile_check_44 = "def TV"
        #	cmake_check_3 = "DEFINED MOBILE"
        #	cmake_check_2 = "DEFINED WEARABLE"
        #	cmake_check_1 = "DEFINED TIZENIOT"
        #	cmake_check_4 = "DEFINED TV"
	#elif profile == "tv":
        #	profile_check_4 = "defined(MOBILE)"
	#	profile_check_44 = "def MOBILE"
        #	profile_check_2 = "defined(WEARABLE)"
	#	profile_check_22 = "def WEARABLE"
        #	profile_check_3 = "defined(TIZENIOT)"
	#	profile_check_33 = "def TIZENIOT"
        #	profile_check_1 = "defined(TV"
	#	profile_check_11 = "def TV"
        #	cmake_check_4 = "DEFINED MOBILE"
        #	cmake_check_2 = "DEFINED WEARABLE"
        #	cmake_check_3 = "DEFINED TIZENIOT"
        #	cmake_check_1 = "DEFINED TV"

	for suite in suites:
		#load all the modules of this suite in tcs
		tcs = os.listdir("src/"+suite) 
		for tc in tcs:
			#check to handle only one module, input given from command line
			if module_check == 1:
				tc = tc.strip()
				module = module.strip()
				if tc not in module:
					continue
			print "#####################################################"
			print "Profile:"+profile+"  Suite:"+suite+"  Module:"+tc
			print "#####################################################"
			startup_counter = 0;
			startup_list = [];
			cleanup_counter = 0;
			cleanup_list = [];
			testcase_counter = 0;
			testcase_list = [];
			testcase_startup = {}
			testcase_cleanup = {}
			unsupported_file_path = 'tct_unsupported.txt'
			unsupported_file = open(unsupported_file_path,'r')
			check_unsupported_armv7l = profile+":armv7l:"+suite+":"+tc+";"
			check_unsupported_aarch64 = profile+":aarch64:"+suite+":"+tc+";"
			check_unsupported_x86 = profile+":x86:"+suite+":"+tc+";"
			check_unsupported_x86_64 = profile+":x86_64:"+suite+":"+tc+";"
			count_unsupported = 0
			for line in unsupported_file:
				if check_unsupported_armv7l in line or check_unsupported_aarch64 in line or check_unsupported_x86 in line or check_unsupported_x86_64 in line:
					count_unsupported+=1
			if count_unsupported is 4:
				print "This module is not supported\n"
				continue
			cmakefile_path = "src/"+suite+'/' + tc + '/CMakeLists.txt'
			#read the cmakefile to know which source files contain headers
			cmake_file = open(cmakefile_path,'r')
			escape_line = 0
			for line in cmake_file:
				if  (cmake_check_1 not in line and (cmake_check_2 in line or cmake_check_3 in line or cmake_check_4 in line)):
					escape_line = 1
				if "ENDIF()" in line:
					escape_line = 0 	
				if '.' in line and "}" not in line and escape_line  == 0:
					#print line
					#check for .c and .cpp file
					if ".c" in line or ".cpp" in line:
						#print line
						line = line.strip()
						if '*' in line:
							if '/' in line:
								line1=line.split('/')[0]
								source_files = [f for f in os.listdir("src/"+suite+'/'+tc+'/'+line1) if ".c" in f or ".cpp" in f]
							else:
								line1=line.split('*')[0]
								source_files = [f for f in os.listdir("src/"+suite+'/'+tc) if ((line1 in f) and (".c" in f or ".cpp" in f))]
						else:
							source_files=[line]
						#read each source file
						for fil in source_files:
							common_file_check = tc+"-common"
							#check for common file
							if common_file_check in fil:
								continue
							if suite == "utc":
								header_temp = "core"
							else:
								header_temp = "native"	
							header_file = "src/"+suite+'/' + tc +"/tct-" + tc + "-" + header_temp +  "_" + profile + ".h"

							tcfile_path = "src/"+suite+'/' + tc + '/' + fil
							if os.path.isfile(tcfile_path)and "../" not in tcfile_path:
								print "Reading File: "+fil
								brace = 0
								continu = 0
								flag_comment = 0
								flag_comment_2 = 0
								tc_file = open(tcfile_path,'r')
								startup = "NULL"
								cleanup = "NULL"
								#read the source file
								for tc_line in tc_file:
									#ignore the comments
									if "/*" in tc_line:
										flag_comment = 1
									if "*/" in tc_line:
										flag_comment = 0
										continue
									if "#if 0" in tc_line:
										flag_comment_2 = 1
									if "#endif" in tc_line and flag_inside_function == 0 and flag_comment_2 == 1:
										flag_comment_2 = 0
										continue
									if flag_comment == 1 or flag_comment_2 == 1:
										continue
									if "//" in tc_line:
										tc_line = tc_line.split("//")[0]
									#check curly braces count
									for chars in tc_line: 
										if '{' == chars:
											brace+=1
										if '}' in chars:
											brace-=1
									if brace <= 0: 
										flag_inside_function = 0
									else:
										flag_inside_function = 1
									
									#print str(brace) + str(flag_inside_function)
									#check whether somes tcs are not for a particular profile
									#if "utc_image_util_decode_jpeg_n2" in tc_line:
									#	print brace
									negative_check_1 = '!'+profile_check_1
									negative_check_2 = '!'+profile_check_2
									negative_check_3 = '!'+profile_check_3
									negative_check_4 = '!'+profile_check_4
									negative_check_11 = 'n'+profile_check_11
                                                                        negative_check_22 = 'n'+profile_check_22
                                                                        negative_check_33 = 'n'+profile_check_33
                                                                        negative_check_44 = 'n'+profile_check_44
									if  (negative_check_1 in tc_line or negative_check_11 in tc_line) and flag_inside_function is 0:
										continu = 1
									if negative_check_22 not in tc_line and negative_check_33 not in tc_line and negative_check_44 not in tc_line and negative_check_2 not in tc_line and negative_check_3 not in tc_line and negative_check_4 not in tc_line and ((profile_check_1 not in tc_line and (profile_check_2 in tc_line or profile_check_3 in tc_line or profile_check_4 in tc_line)) or (profile_check_11 not in tc_line and (profile_check_22 in tc_line or profile_check_33 in tc_line or profile_check_44 in tc_line))) and flag_inside_function is 0:
										continu = 1
									if "#endif" in tc_line and flag_inside_function == 0:
										continu = 0
									#print "continu" + str(continu)
									pat = r'([\w]+)\s+([\S]+)\(([\w+\s+\w+])+\)'
									
									if re.search(pat,tc_line) and "actorSource.GetProperty" not in tc_line and tc_line is not "" and (("int " in tc_line and "(void)" in tc_line) or ("void " in tc_line and "(void)" in tc_line and ("startup" in tc_line or "cleanup" in tc_line))):
										if continu == 1:
											continue;
										#re.sub( '\s+', ' ', tc_line ).strip()
										tc_line = ' '.join(tc_line.split())
										function_name = tc_line.split(' ')[1]
										#print function_name
										function_name = function_name.split('(')[0]
										#print function_name
										if function_name == "void" or function_name == "int":
                                                                			continue;
										#check whether function is tc or startup function or cleanup function
										if function_name.split('_')[-1] == "startup" or function_name.split('_')[-1] == "startup2":
											if startup_counter > cleanup_counter:
												cleanup_list.append("NULL")
												cleanup_counter+=1
											startup_list.append(function_name)
											startup_counter+=1
											startup = function_name
										elif function_name.split('_')[-1] == "cleanup" or function_name.split('_')[-1] == "cleanup2":
											if startup_counter < cleanup_counter:
                                                						startup_list.append("NULL")
                                                						startup_counter+=1
											cleanup_list.append(function_name)
											cleanup_counter+=1
											cleanup = function_name
										else:
											testcase_list.append(function_name)
											testcase_counter+=1
											testcase_startup[function_name] = startup
											testcase_cleanup[function_name] = cleanup
								if startup_counter < cleanup_counter:
									startup_list.append("NULL")
                                               				startup_counter+=1			
								elif startup_counter > cleanup_counter:
									cleanup_list.append("NULL")
                                                			cleanup_counter+=1
					
						 
			
			#print startup_counter
			#print cleanup_counter
			#header_file = suite+'/' + tc +"/tct-" + tc + "-_" + profile + ".h"
			#Write in the header file
			f = open(header_file,'w')
			HEADER = 'TCT_'+tc.upper()+'-NATIVE_H'
			f.write('//\n// Copyright (c) 2021 Samsung Electronics Co., Ltd.\n//\n// Licensed under the Apache License, Version 2.0 (the License);\n// you may not use this file except in compliance with the License.\n// You may obtain a copy of the License at\n//\n//     http://www.apache.org/licenses/LICENSE-2.0\n//\n// Unless required by applicable law or agreed to in writing, software\n// distributed under the License is distributed on an "AS IS" BASIS,\n// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n// See the License for the specific language governing permissions and\n// limitations under the License.\n//\n')
			f.write('#ifndef __'+HEADER+'__\n')
			f.write('#define __'+HEADER+'__\n')
			f.write('\n')
			f.write('#include "testcase.h"\n')
			f.write('#include "tct_common.h"\n')
			f.write('\n')
			for i in range(startup_counter):
				if startup_list[i] is not "NULL":
					f.write('extern void '+startup_list[i]+'(void);\n')
				if cleanup_list[i] is not "NULL":
					f.write('extern void '+cleanup_list[i]+'(void);\n')
			f.write('\n')
			for i in range(testcase_counter):
				f.write('extern int '+testcase_list[i]+'(void);\n')
			f.write('\n')
			f.write('testcase tc_array[] = {\n')
		
			for i in range(testcase_counter):
				f.write('	{"'+testcase_list[i]+'"' + ','+testcase_list[i]+','+testcase_startup[testcase_list[i]] + ',' + testcase_cleanup[testcase_list[i]] + '},\n')
			f.write('	{NULL, NULL}\n')
			f.write('};\n')
			f.write('\n')
			f.write('#endif // __'+HEADER+'__\n')
			f.close
			print "Total test cases:  " + str(testcase_counter)+"\n"
##################################################### End of generate function ############################################################
#################################################### Script Starts Here ###################################################################

module_check = 0
module = ""
os.chdir("..")
if ( len(sys.argv) == 1):
	profiles = ['mobile','wearable']
	suites = ['itc','ctc','utc']
	
elif ( len(sys.argv) == 2):
	if sys.argv[1] == "itc" or sys.argv[1] == "ctc" or sys.argv[1] == "utc":
		suites = [sys.argv[1]]
		profiles = ['mobile','wearable']
	elif sys.argv[1] == "mobile" or sys.argv[1] == "wearable":
		suites = ['itc','ctc','utc']
		profiles = [sys.argv[1]]
	elif sys.argv[1] == "tizeniot" or sys.argv[1] == "tv":
		print "#####################################################"
		print "Currently not supported for "+sys.argv[1]
		print "#####################################################"
		exit()
elif ( len(sys.argv) == 3):
	if (sys.argv[1] == "itc" or sys.argv[1] == "ctc" or sys.argv[1] == "utc") and (sys.argv[2] == "mobile" or sys.argv[2] == "wearable" or sys.argv[2] == "tizeniot" or sys.argv[2] == "tv"):
		if sys.argv[2] == "wearable" or sys.argv[2] == "tizeniot" or sys.argv[2] == "tv":
			print "#####################################################"
			print "Currently not supported for "+sys.argv[2]
			print "#####################################################"
			exit()
		else:
			suites = [sys.argv[1]]
			profiles = [sys.argv[2]]
	elif (sys.argv[1] == "mobile" or sys.argv[1] == "wearable" or sys.argv[1] == "tizeniot" or sys.argv[1] == "tv") and (sys.argv[2] == "itc" or sys.argv[2] == "ctc" or sys.argv[2] == "utc"):
		if sys.argv[1] == "tizeniot" or sys.argv[1] == "tv":
			print "#####################################################"
			print "Currently not supported for "+sys.argv[1]
			print "#####################################################"
			exit()
		else:
			suites = [sys.argv[2]]
                	profiles = [sys.argv[1]]
	elif sys.argv[2] == "mobile" or sys.argv[2] == "wearable" or sys.argv[2] == "tizeniot" or sys.argv[2] == "tv":
		if sys.argv[2] == "tizeniot" or sys.argv[2] == "tv":
			print "#####################################################"
			print "Currently not supported for "+sys.argv[2]
			print "#####################################################"
			exit()
		else:
			profiles = [sys.argv[2]]
			suites = ['itc','ctc','utc']
			module_check = 1
			module = sys.argv[1]
	else:
		profiles = ['mobile','wearable']
		suites = [sys.argv[1]]
		module_check = 1
		module = sys.argv[2]

elif ( len(sys.argv) == 4):
	if sys.argv[3] == "tizeniot" or sys.argv[3] == "tv":
		print "#####################################################"
		print "Currently not supported for "+sys.argv[3]
		print "#####################################################"
		exit()
	else:
		suites = [sys.argv[1]]
		module_check = 1
		module = sys.argv[2]
		profiles = [sys.argv[3]]

for profile in profiles:
	generate(profile,module)

########################################################## End of script ###################################################################
