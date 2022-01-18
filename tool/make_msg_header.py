#python xml library import 
from xml.etree.ElementTree import parse
import os
import sys
import shutil

curpath = os.path.dirname( os.path.abspath( __file__ ) )
msgpath = os.path.join( curpath, "../error_messages/" )
headerpath = os.path.join( curpath, "tizen_error_private.h" )

shutil.copy( os.path.join( curpath, "tizen_error_private_template.h" ), headerpath )
fp = open( headerpath, 'a' )

fp.write( "\n#ifndef __TIZEN_COMMON_ERROR_PRIVATE_H__\n" )
fp.write( "#define __TIZEN_COMMON_ERROR_PRIVATE_H__\n\n" )

fp.write( "#ifdef __cplusplus\n" )
fp.write( "extern \"C\" {\n" )
fp.write( "#endif\n\n" )

fp.write( "#define ERR_ENTRY(name, value, msg) {value, name, msg}\n\n" )
fp.write( "typedef struct tizen_err_info {\n" )
fp.write( "\tint value;\n" )
fp.write( "\tchar *name;\n" )
fp.write( "\tchar *msg;\n" )
fp.write( "} err_info;\n\n" )

fp.write( "static err_info err_list[] = {\n" );
for root, dirs, files in os.walk( msgpath ):
	for file in files:
		print ">>>> " + file
		targetXML = open( os.path.join( msgpath, file ) )
		tree = parse( targetXML )
		errorroot = tree.getroot()		

		for error in errorroot.findall( "error" ):
			fp.write( "\tERR_ENTRY(\"" )
			fp.write( error.get( "name" ) + "\", ")
			fp.write( error.findtext( "value" ) + ", \"" )
			fp.write( error.findtext( "msg" ) + "\"),\n" )
			print error.get( "name" )

fp.write( "\t{0, NULL, NULL}\n" )
fp.write( "};\n" )

fp.write( "\n#ifdef __cplusplus\n" )
fp.write( "}\n" )
fp.write( "#endif\n\n" )
fp.write( "#endif\t/**<__TIZEN_COMMON_ERROR_PRIVATE_H__ */\n" )
fp.close()

privatepath = os.path.join( curpath, "../include/private/" )
if not os.path.isdir( privatepath ):
	os.mkdir( privatepath )

# os.remove( privatepath + "tizen_error_private.h" )
# shutil.move( headerpath, privatepath )