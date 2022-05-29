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
#include "ITs-alarm-common.h"

/** @addtogroup itc-application
*  @ingroup itc
*  @{
*/

/**
* @function 		ApplicationGetDataPath
* @description	 	Returnes the application data path
* @parameter		pAppDataPath: application data path
* @return 			true if succeed else false
*/
bool ApplicationGetDataPath(char* pAppDataPath)
{
	if ( NULL == pAppDataPath )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	memset(pAppDataPath, 0, PATH_LEN);

	char* pPath = NULL;
	pPath = app_get_data_path();
	if ( NULL == pPath )
	{
		FPRINTF("[Line : %d][%s] Unable to get application data path; app_get_data_path returned null value \\n", __LINE__, API_NAMESPACE);
		return false;
	}

	strncpy(pAppDataPath, pPath, strlen(pPath)+1);

	FPRINTF("[Line : %d][%s] application data path returned = %s\\n", __LINE__, API_NAMESPACE, pAppDataPath);

	return true;
}

/**
* @function 		ApplicationAppendToAppDataPath
* @description	 	Appends the input string to application data path
* @parameter		pInputPath: path to append to data path; pFinalPath: final resultant path
* @return 			true if succeed else false
*/
bool ApplicationAppendToAppDataPath(char* pInputPath, char* pFinalPath)
{
	if ( (NULL == pInputPath) || (NULL == pFinalPath) )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	char pAppDataPath[PATH_LEN] = {0,};
	if ( false == ApplicationGetDataPath(pAppDataPath) )
	{
		return false;
	}

	memset(pFinalPath, 0, PATH_LEN);
	strncpy(pFinalPath, pAppDataPath, strlen(pAppDataPath)+1);
	strncat(pFinalPath, pInputPath, strlen(pInputPath)+1);

	FPRINTF("[Line : %d][%s] result path returned = %s\\n", __LINE__, API_NAMESPACE, pFinalPath);

	return true;
}

/**
* @function 		AppControlGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* AppControlGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case APP_CONTROL_ERROR_NONE:					szErrorVal = "APP_CONTROL_ERROR_NONE";break;
	case APP_CONTROL_ERROR_INVALID_PARAMETER:		szErrorVal = "APP_CONTROL_ERROR_INVALID_PARAMETER";break;
	case APP_CONTROL_ERROR_OUT_OF_MEMORY:			szErrorVal = "APP_CONTROL_ERROR_OUT_OF_MEMORY";break;
	case APP_CONTROL_ERROR_APP_NOT_FOUND:			szErrorVal = "APP_CONTROL_ERROR_APP_NOT_FOUND";break;
	case APP_CONTROL_ERROR_KEY_NOT_FOUND:			szErrorVal = "APP_CONTROL_ERROR_KEY_NOT_FOUND";break;
	case APP_CONTROL_ERROR_KEY_REJECTED:			szErrorVal = "APP_CONTROL_ERROR_KEY_REJECTED";break;
	case APP_CONTROL_ERROR_INVALID_DATA_TYPE:		szErrorVal = "APP_CONTROL_ERROR_INVALID_DATA_TYPE";break;
	case APP_CONTROL_ERROR_LAUNCH_REJECTED:			szErrorVal = "APP_CONTROL_ERROR_LAUNCH_REJECTED";break;
	case APP_CONTROL_ERROR_PERMISSION_DENIED:		szErrorVal = "APP_CONTROL_ERROR_PERMISSION_DENIED";break;
	case APP_CONTROL_ERROR_LAUNCH_FAILED:			szErrorVal = "APP_CONTROL_ERROR_LAUNCH_FAILED";break;
	case APP_CONTROL_ERROR_TIMED_OUT:				szErrorVal = "APP_CONTROL_ERROR_TIMED_OUT";break;
	default:										szErrorVal = "Undefined Error";break;
	}
	return szErrorVal;
}

/**
* @function 		AlarmGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* AlarmGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case ALARM_ERROR_NONE:					szErrorVal = "ALARM_ERROR_NONE";break;
	case ALARM_ERROR_INVALID_PARAMETER:		szErrorVal = "ALARM_ERROR_INVALID_PARAMETER";break;
	case ALARM_ERROR_INVALID_TIME:			szErrorVal = "ALARM_ERROR_INVALID_TIME";break;
	case ALARM_ERROR_INVALID_DATE:			szErrorVal = "ALARM_ERROR_INVALID_DATE";break;
	case ALARM_ERROR_CONNECTION_FAIL:		szErrorVal = "ALARM_ERROR_CONNECTION_FAIL";break;
	case ALARM_ERROR_OUT_OF_MEMORY:			szErrorVal = "ALARM_ERROR_OUT_OF_MEMORY";break;
	case ALARM_ERROR_PERMISSION_DENIED :	szErrorVal = "ALARM_ERROR_PERMISSION_DENIED";break;
	case ALARM_ERROR_NOT_PERMITTED_APP :    szErrorVal = "ALARM_ERROR_NOT_PERMITTED_APP";break;
	default:								szErrorVal = "Undefined Error";break;
	}

	return szErrorVal;
}


/**
* @function 		AppGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* AppGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case APP_ERROR_NONE :					szErrorVal = "APP_ERROR_NONE";					break;
	case APP_ERROR_INVALID_PARAMETER:		szErrorVal = "APP_ERROR_INVALID_PARAMETER";		break;
	case APP_ERROR_OUT_OF_MEMORY:			szErrorVal = "APP_ERROR_OUT_OF_MEMORY";			break;
	case APP_ERROR_INVALID_CONTEXT:			szErrorVal = "APP_ERROR_INVALID_CONTEXT";		break;
	case APP_ERROR_NO_SUCH_FILE:			szErrorVal = "APP_ERROR_NO_SUCH_FILE";			break;
	case APP_ERROR_ALREADY_RUNNING:			szErrorVal = "APP_ERROR_ALREADY_RUNNING";		break;
	default:								szErrorVal = "Undefined error";					break;
	}

	return szErrorVal;
}
/**
* @function 		AppControlGetLaunchMode
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* AppControlGetLaunchMode(app_control_launch_mode_e nRet)
{
	char *szErrorVal = "Undefined Error";

	switch ( nRet )
	{
	case APP_CONTROL_LAUNCH_MODE_SINGLE:		szErrorVal = "APP_CONTROL_LAUNCH_MODE_SINGLE";	break;
	case APP_CONTROL_LAUNCH_MODE_GROUP:			szErrorVal = "APP_CONTROL_LAUNCH_MODE_GROUP";	break;
	}

	return szErrorVal;
}

/**
* @function 		BundleGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* BundleGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case BUNDLE_ERROR_NONE:					szErrorVal = "BUNDLE_ERROR_NONE";					break;
	case BUNDLE_ERROR_OUT_OF_MEMORY:		szErrorVal = "BUNDLE_ERROR_OUT_OF_MEMORY";			break;
	case BUNDLE_ERROR_INVALID_PARAMETER:	szErrorVal = "BUNDLE_ERROR_INVALID_PARAMETER";		break;
	case BUNDLE_ERROR_KEY_NOT_AVAILABLE:	szErrorVal = "BUNDLE_ERROR_KEY_NOT_AVAILABLE";		break;
	case BUNDLE_ERROR_KEY_EXISTS:			szErrorVal = "BUNDLE_ERROR_KEY_EXISTS";				break;
	default:								szErrorVal = "Unknown Error";						break;
	}
	return szErrorVal;
}

/**
 * @function 		Timeout
 * @description	 	Called if some callback is not invoked for a particular timeout
 * @parameter		gpointer data
 * @return 			gboolean
 */ 
gboolean Timeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
	}
	return false;
}

/** @} */
