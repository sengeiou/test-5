//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef _TCT_COMMON_H_
#define _TCT_COMMON_H_

#include "assert.h"

#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <system_info.h>

#define CONFIG_LINE_LEN_MAX			2048
#define CONFIG_VALUE_LEN_MAX		1024

#define UTC_LOG "/tmp/utclog_core"
#define TC_RESULT "/tmp/tcresult"

extern FILE *g_fpLog;
extern FILE *g_fpLogDump;
extern int g_Serr;

extern int old_Serr;

#define FPRINTF(...) {\
	g_fpLog = fopen(ERR_LOG, "a");\
	fprintf(g_fpLog, __VA_ARGS__);\
	fclose(g_fpLog);\
}

#define DUMP_UTC_ERRLOG() {\
	g_Serr = dup(fileno(stderr));\
	g_fpLogDump = freopen(ERR_UTC_LOG, "w", stderr);\
	fflush(stderr);\
}

#define CLOSE_UTC_ERRLOG() {\
	if(g_fpLogDump) \
	{\
		if (g_Serr != -1)\
		{\
			old_Serr = fileno(stderr);\
			if(old_Serr != -1)\
			{\
				dup2(g_Serr, old_Serr);\
			}\
			close(g_Serr);\
		}\
		fclose(g_fpLogDump);\
	}\
}

#define PRINT_UTC_LOG(...) {\
	g_fpLog = fopen(UTC_LOG, "a+");\
	fprintf(g_fpLog, __VA_ARGS__);\
	fclose(g_fpLog);\
}


#define PRINT_TC_RESULT(...) {\
	g_fpLog = fopen(TC_RESULT, "w");\
	fprintf(g_fpLog, __VA_ARGS__);\
	fclose(g_fpLog);\
}


#define FREE_MEMORY_TC(buffer) {\
	if ( buffer != NULL )\
{\
	free(buffer);\
	buffer = NULL;\
}\
}



#define IS_FEATURE_SUPPORTED(feature_name, featureFlag, ModuleName)\
{\
	if ( !(TCTCheckSystemInfoFeatureSupported(feature_name, ModuleName)) )\
{\
	featureFlag = false;\
}\
	else\
{\
	featureFlag = true;\
}\
}

#define PRINT_RESULT(eCompare, eRetVal, API, Error) {\
	if ( eRetVal == eCompare )\
{\
	if ( DEBUG )\
{\
	FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
}\
}\
	else \
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, Error, eRetVal);\
	return 1;\
}\
}

#define PRINT_RESULT_NORETURN(eCompare, eRetVal, API, Error) {\
	if ( eRetVal == eCompare )\
{\
	if ( DEBUG )\
{\
	FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
}\
}\
	else \
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, Error, eRetVal);\
}\
}

#define PRINT_RESULT_CLEANUP(eCompare, eRetVal, API, Error, FreeResource) {\
	if ( eRetVal == eCompare )\
{\
	if ( DEBUG )\
{\
	FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
}\
}\
else \
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, Error, eRetVal);\
	FreeResource;\
	return 1;\
}\
}

#define CHECK_VALUE_STRING(StringVariable, API) {\
	if ( StringVariable == NULL )\
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = value returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
	return 1;\
}\
	else if ( DEBUG )\
{\
	FPRINTF("[Line : %d][%s] value returned = %s\\n", __LINE__, API_NAMESPACE, StringVariable);\
}\
	free(StringVariable);\
	StringVariable = NULL;\
}

#define CHECK_VALUE_INT(Variable, API) {\
	if ( Variable == 0 )\
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = value returned is Zero\\n", __LINE__, API_NAMESPACE, API);\
	return 1;\
}\
	else if ( DEBUG )\
{\
	FPRINTF("[Line : %d][%s] value returned = %d\\n", __LINE__, API_NAMESPACE, Variable);\
}\
}

#define CHECK_HANDLE(Handle, API) {\
	if ( Handle == NULL )\
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
	return 1;\
}\
}

#define FREE_MEMORY(buffer) {\
	if ( buffer != NULL )\
{\
	free(buffer);\
	buffer = NULL;\
}\
}

bool TCTCheckSystemInfoFeatureSupported(char* pszKey, char* pszModuleName);
char* TCTSystemInfoGetError(int nRet);
bool GetValueFromConfigFile(char* pstrKeyString, char* pstrValue, char* pstrModule);
bool GetValueForTCTSetting(char* pstrKeyString, char* pstrValue, char* pstrModule);
#endif // _TCT_COMMON_H_
