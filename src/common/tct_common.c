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

#include "tct_common.h"
FILE *g_fpLog;
FILE *g_fpLogDump;
int g_Serr;
int old_Serr;

/**
* @function 		TCTCheckSystemInfoFeatureSupported
* @description	 	Check the supported feature for the given key value
* @parameter		char* pszKey : key value, char* pszModuleName : module name
* @return 			true if supported else false
*/
bool TCTCheckSystemInfoFeatureSupported(char* pszKey, char* pszModuleName)
{
	if ( NULL == pszKey )
	{
		FPRINTF("[Line : %d][%s] Null key value passed to function : TCTCheckSystemInfoFeatureSupported\\n", __LINE__, pszModuleName);
		return false;
	}

	bool bValue = false;
	int nRet = system_info_get_platform_bool (pszKey, &bValue);

	if ( nRet != SYSTEM_INFO_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool returned (error = %s) for (key = %s)\\n", __LINE__, pszModuleName, TCTSystemInfoGetError(nRet), pszKey);
		return false;
	}

	if ( bValue )
	{
		FPRINTF("[Line : %d][%s] Feature %s is supported\\n", __LINE__, pszModuleName, pszKey);
	}
	else
	{
		FPRINTF("[Line : %d][%s] Feature %s is not supported\\n", __LINE__, pszModuleName, pszKey);
	}


	return bValue;
}

/**
* @function 		TCTSystemInfoGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* TCTSystemInfoGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case SYSTEM_INFO_ERROR_NONE:				szErrorVal = "SYSTEM_INFO_ERROR_NONE";					break;
	case SYSTEM_INFO_ERROR_INVALID_PARAMETER:	szErrorVal = "SYSTEM_INFO_ERROR_INVALID_PARAMETER";		break;
	case SYSTEM_INFO_ERROR_IO_ERROR:			szErrorVal = "SYSTEM_INFO_ERROR_IO_ERROR";				break;
	case SYSTEM_INFO_ERROR_OUT_OF_MEMORY :		szErrorVal = "SYSTEM_INFO_ERROR_OUT_OF_MEMORY";			break;
	default : 									szErrorVal = "Unknown error";							break;
	}

	return szErrorVal;
}

/**
* @function 		GetValueFromConfigFile
* @description	 	Get the corresponding value for a key from config file
* @parameter		pstrKeyString : Key, pstrValue : Value
* @return 			true for success, false for failure
*/ 
bool GetValueFromConfigFile(char* pstrKeyString, char* pstrValue, char* pstrModule)
{
	if ( NULL == pstrKeyString )
	{
		FPRINTF("[Line : %d][%s] The key string provided to fetch config file value is null\\n", __LINE__, pstrModule);
		return false;
	}


	FILE* pfilePtr = fopen(CONFIGFILE_PATH, "r");
	if ( NULL == pfilePtr )
	{
		FPRINTF("[Line : %d][%s] Unable to open configuration file : %s\\n", __LINE__, pstrModule, CONFIGFILE_PATH);
		return false;
	}

	char* pszKey = NULL;
	char* pszValue = NULL;
	char* pszDelim = "=\n";
	char szConfigLine[CONFIG_LINE_LEN_MAX] = {0,};

	while ( !feof(pfilePtr) )
	{
		if ( fgets(szConfigLine, CONFIG_LINE_LEN_MAX, pfilePtr) != NULL )
		{
			pszKey = strtok(szConfigLine, pszDelim);
			pszValue = strtok(NULL, pszDelim);
			if ( NULL == pszKey )
			{
				FPRINTF("[Line : %d][%s] Null key value pszKey \\n", __LINE__,pstrModule);
				fclose(pfilePtr);
				return false;
			}
			if ( 0 == strcmp(pszKey, pstrKeyString) )
			{
#if DEBUG
				FPRINTF("[Line : %d][%s][Key = %s;Config value = %s]\\n", __LINE__, pstrModule, pszKey, pszValue);
#endif
				break;
			}

			pszKey = NULL;
			pszValue = NULL;
		}
	}

	fclose(pfilePtr);
	if ( NULL == pszValue )
	{
		FPRINTF("[Line : %d][%s][Key = %s;Unable to retrieve config value for this key. Check key at config file location : %s]\\n", __LINE__, pstrModule, pstrKeyString, CONFIGFILE_PATH);
		return false;
	}

	if (strlen(pszValue) >= CONFIG_VALUE_LEN_MAX )
	{
		FPRINTF("[Line : %d][%s][Key = %s;Config Value should be less than %d characters in length]\\n", __LINE__, pstrModule, pszKey, CONFIG_VALUE_LEN_MAX);
		return false;
	}

	memset(pstrValue, 0, CONFIG_VALUE_LEN_MAX);
	strncpy(pstrValue, pszValue, strlen(pszValue)+1);
	return true;
}




/**
* @function 		GetValueForTCTSetting
* @description	 	Get the corresponding value for a key from TCT_CONFIG file
* @parameter		pstrKeyString : Key, pstrValue : Value
* @return 			true for success, false for failure
*/ 
bool GetValueForTCTSetting(char* pstrKeyString, char* pstrValue, char* pstrModule)
{
	if ( NULL == pstrKeyString )
	{
		FPRINTF("[Line : %d][%s] The key string provided to fetch config file value is null\\n", __LINE__, pstrModule);
		return false;
	}


	FILE* pfilePtr = fopen(TCT_CONFIG, "r");
	if ( NULL == pfilePtr )
	{
		FPRINTF("[Line : %d][%s] Unable to open configuration file : %s\\n", __LINE__, pstrModule, TCT_CONFIG);
		return false;
	}

	char* pszKey = NULL;
	char* pszValue = NULL;
	char* pszDelim = "=\n";
	char szConfigLine[CONFIG_LINE_LEN_MAX] = {0,};

	while ( !feof(pfilePtr) )
	{
		if ( fgets(szConfigLine, CONFIG_LINE_LEN_MAX, pfilePtr) != NULL )
		{
			pszKey = strtok(szConfigLine, pszDelim);
			pszValue = strtok(NULL, pszDelim);
			if ( NULL == pszKey )
			{
				FPRINTF("[Line : %d][%s] Null key value pszKey \\n", __LINE__,pstrModule);
				fclose(pfilePtr);
				return false;
			}
			if ( 0 == strcmp(pszKey, pstrKeyString) )
			{
#if DEBUG
				FPRINTF("[Line : %d][%s][Key = %s;Config value = %s]\\n", __LINE__, pstrModule, pszKey, pszValue);
#endif
				break;
			}

			pszKey = NULL;
			pszValue = NULL;
		}
	}

	fclose(pfilePtr);
	if ( NULL == pszValue )
	{
		FPRINTF("[Line : %d][%s][Key = %s;Unable to retrieve config value for this key. Check key at config file location : %s]\\n", __LINE__, pstrModule, pstrKeyString, TCT_CONFIG);
		return false;
	}

	if (strlen(pszValue) >= CONFIG_VALUE_LEN_MAX )
	{
		FPRINTF("[Line : %d][%s][Key = %s;Config Value should be less than %d characters in length]\\n", __LINE__, pstrModule, pszKey, CONFIG_VALUE_LEN_MAX);
		return false;
	}

	memset(pstrValue, 0, CONFIG_VALUE_LEN_MAX);
	strncpy(pstrValue, pszValue, strlen(pszValue)+1);
	return true;
}
