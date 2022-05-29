import os
import sys
from shutil import copyfile
XML_PATH=""
TC_COUNT=""
FILENAME=""
START_TC="<testcase "
END_TC="</testcase>"
tcFound=0
TC_TAG=""
NEW_TESTS_XML_CONTENT=""
file=""	
def contentfortestsxml(tc_tag,tc_count):
	global NEW_TESTS_XML_CONTENT
	for i in range(int(tc_count)):
	   NEW_TESTS_XML_CONTENT = NEW_TESTS_XML_CONTENT + tc_tag 

def ReadandFind():
	global file
	global tcFound
	global TC_TAG
	global TC_COUNT
	for line in file:
		if START_TC in line:
			TC_TAG = line
			tcFound=1
		elif END_TC in line:
			TC_TAG = TC_TAG + line
			contentfortestsxml(TC_TAG,TC_COUNT)
			TC_TAG=""
			tcFound=0
		elif tcFound==1:
			TC_TAG = TC_TAG + line
		else:
		   contentfortestsxml(line,1)

def gentestxmlfile(xml_path,tc_count):
	global XML_PATH
	global TC_COUNT
	global FILENAME
	global START_TC
	global END_TC
	global tcFound
	global TC_TAG
	global NEW_TESTS_XML_CONTENT
	global file
	XML_PATH=xml_path
	TC_COUNT=tc_count
	FILENAME= XML_PATH+"tmp_tests.xml"
	START_TC="<testcase "
	END_TC="</testcase>"
	tcFound=0
	TC_TAG=""
	NEW_TESTS_XML_CONTENT=""
	copyfile(XML_PATH+"tests.xml", FILENAME)
	try:
		file = open(FILENAME)
	except Exception as ex:
		template = "An exception of type {0} occured. Arguments:\n{1!r}"
		message = template.format(type(ex).__name__, ex.args)
		#print message
	ReadandFind() 
	file.close()
	os.remove(XML_PATH+"tests.xml")
	os.remove(FILENAME)
	fo = open(XML_PATH+"tests.xml", "ab+")
	fo.write(NEW_TESTS_XML_CONTENT);
	fo.close()




