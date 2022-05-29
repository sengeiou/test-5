#ifndef _DALI_COMMMON_H_
#define _DALI_COMMMON_H_

// common headers added here
#include "assert.h"
#include <storage.h>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <dali/dali.h>
#include <system_info.h>
#include <tizen.h>

using namespace std;

#define INTERVAL 500

#define OPEN_GL_ES_FEATURE		"http://tizen.org/feature/opengles.version.2_0"

extern void (*DaliCheckFailCB)(void*);

extern int test_return_value;
#define TC_RESULT "/tmp/tcresult"
void TcResult(); //Tc Result write to /tmp/tcresult


// enums/ structures/ classes defined here
enum ELogType
{
	LOG_INFO,
	LOG_ERROR,
	LOG_RESULT
};
enum ETcResult
{
	TC_PASS=0,
	TC_FAIL
};

class DaliLog
{
	public:
		DaliLog();
		~DaliLog();
		static void Print(ELogType eLogType, string strModuleName, string strLogMessage);
		static void Print(ELogType eLogType, string strModuleName, string strLogMessage, int nLine);
		static void Print(ELogType eLogType, string strModuleName, string strLogMessage, string strFuncName);
		static void PrintV(ELogType eLogType, string strModuleName, string strLogMessage, ...);
		static void PrintPass(string strModuleName, string strTcName);
		static void PrintPass();
		static void PrintExecStarted(string strModuleName, string strTcName);
		static void PrintMgs(string strMgs);
		static string mstrModuleName;
		static string mstrTcName;
};

// function macros defined here

// simple error log macro - NOT for formatted message
#define LOG_E(MESSAGE) \
	DaliLog::Print(LOG_ERROR, SUITE_NAME, MESSAGE, __LINE__);

// simple info log macro - NOT for formatted message
#define LOG_I(MESSAGE) \
	DaliLog::Print(LOG_INFO, SUITE_NAME, MESSAGE, __LINE__);


#define DALI_CHECK_INSTANCE(condition,MESSAGE) \
if ( (!condition) ) \
{ \
LOG_E(MESSAGE); \
test_return_value=1; \
TcResult(); \
return; \
}

#define DALI_CHECK_FAIL(CONDITION, MESSAGE)\
if(CONDITION){\
LOG_E(MESSAGE);\
test_return_value=1; \
TcResult(); \
return;\
}

#define DALI_CHECK_FALSE(CONDITION, MESSAGE)\
if(CONDITION){\
LOG_E(MESSAGE);\
return false;\
}

#define DALI_CHECK_FAIL_CB(CONDITION, MESSAGE, CALLBACK, PARAM){\
if(CONDITION){\
LOG_E(MESSAGE);\
DaliCheckFailCB=CALLBACK;\
if( DaliCheckFailCB )\
{(*DaliCheckFailCB)(PARAM);}\
test_return_value=1; \
TcResult(); \
return;}\
}

#define DALI_SAFE_FREE(buffer) {\
	if ( buffer != NULL )\
{\
	delete buffer; \
	buffer = NULL; \
}\
}


#define FPRINTF(...) {\
	FILE *fpLog = fopen(ERR_LOG, "a");\
	fprintf(fpLog, __VA_ARGS__);\
	fclose(fpLog);\
}


#define CHECK_OPEN_GL(MODULE_NAME,LINE_NUMBER) {\
	bool g_bSupported_OpenGl_Es=false; \
	g_bSupported_OpenGl_Es=getSystemInfoFeature((char *)OPEN_GL_ES_FEATURE, (char *)MODULE_NAME, LINE_NUMBER); \
	if(!g_bSupported_OpenGl_Es){ \
		DaliLog::PrintV(LOG_INFO, MODULE_NAME, "[Line : %d] '%s' feature is not supported so leaving from TC.\\n", LINE_NUMBER, OPEN_GL_ES_FEATURE); \
		test_return_value=0; \
		DaliLog::PrintPass(); \
		return test_return_value;}\
	}
		
#define CHECK_GL \
			int ret = TIZEN_ERROR_NONE;\
			ret = get_last_result();\
			bool featureFlag = true;\
			system_info_get_platform_bool("tizen.org/feature/opengles.version.2_0", &featureFlag);\
			if( featureFlag == false )\
			{\
			assert_eq( ret, TIZEN_ERROR_NOT_SUPPORTED );\
			test_return_value=0;\
			TcResult();\
			return test_return_value;\
			}

/** Helper Function for Get Application Resource Path*/
char* getAppDataPath();
string getResourceFullPath(string strFile);

/**Tizen System feature support check*/
bool getSystemInfoFeature(char* pszKey, char* strModuleName, int nLine);

#endif //_DALI_COMMMON_H_
