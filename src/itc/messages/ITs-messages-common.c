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
#include "ITs-messages-common.h"

/** @addtogroup itc-messages
* @ingroup		itc
* @{
*/

/**
* @function 		MessagesGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* MessagesGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case MESSAGES_ERROR_INVALID_PARAMETER:					szErrorVal = "MESSAGES_ERROR_INVALID_PARAMETER";		break;
	case MESSAGES_ERROR_OUT_OF_MEMORY:						szErrorVal = "MESSAGES_ERROR_OUT_OF_MEMORY";			break;
	case MESSAGES_ERROR_SERVER_NOT_READY:					szErrorVal = "MESSAGES_ERROR_SERVER_NOT_READY";			break;
	case MESSAGES_ERROR_COMMUNICATION_WITH_SERVER_FAILED:	szErrorVal = "MESSAGES_ERROR_COMMUNICATION_WITH";		break;
	case MESSAGES_ERROR_OPERATION_FAILED:					szErrorVal = "MESSAGES_ERROR_OPERATION_FAILED";			break;
	case MESSAGES_ERROR_SENDING_FAILED:						szErrorVal = "MESSAGES_ERROR_SENDING_FAILED";			break;
	case MESSAGES_ERROR_OUT_OF_RANGE:						szErrorVal = "MESSAGES_ERROR_OUT_OF_RANGE";				break;
	case MESSAGES_ERROR_NO_SIM_CARD:						szErrorVal = "MESSAGES_ERROR_NO_SIM_CARD";				break;
	case MESSAGES_ERROR_NO_DATA:							szErrorVal = "MESSAGES_ERROR_NO_DATA";					break;
	case MESSAGES_ERROR_PERMISSION_DENIED:					szErrorVal = "MESSAGES_ERROR_PERMISSION_DENIED";		break;
	case MESSAGES_ERROR_NOT_SUPPORTED:						szErrorVal = "MESSAGES_ERROR_NOT_SUPPORTED";			break;		
	case MESSAGES_ERROR_NONE:								szErrorVal = "MESSAGES_ERROR_NONE";						break;
	default:												szErrorVal = "Unknown Error";							break;
	}
	return szErrorVal;
}

/**
* @function 		MessagesGetDataPath
* @description	 	Returnes the application data path
* @parameter		pAppDataPath: application data path
* @return 			true if succeed else false
*/
bool MessagesGetDataPath(char* pAppDataPath)
{
	if ( NULL == pAppDataPath )
	{
		FPRINTF("[Line : %d][%s] Null Path provided;Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	memset(pAppDataPath, 0, PATH_LEN);

	char* pPath = NULL;
	pPath = app_get_data_path();
	if ( NULL == pPath )
	{
		FPRINTF("[Line : %d][%s] Unable to get application data path;app_get_data_path returned null value\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	strncpy(pAppDataPath, pPath, strlen(pAppDataPath)+1);

	FPRINTF("[Line : %d][%s] application data path returned = %s\\n", __LINE__, API_NAMESPACE, pAppDataPath);

	return true;
}

/**
* @function 		MessagesAppendToAppDataPath
* @description	 	Appends the input string to application data path
* @parameter		pInputPath: path to append to data path;pFinalPath: final resultant path
* @return 			true if succeed else false
*/
bool MessagesAppendToAppDataPath(char* pInputPath, char* pFinalPath)
{
	if ( NULL == pInputPath || NULL == pFinalPath )
	{
		FPRINTF("[Line : %d][%s] Null Path provided;Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	char pAppDataPath[PATH_LEN] = {0,};
	if ( false == MessagesGetDataPath(pAppDataPath) )
	{
		return false;
	}

	memset(pFinalPath, 0, PATH_LEN);
	strncpy(pFinalPath, pAppDataPath, strlen(pFinalPath)+1);
	strncat(pFinalPath, pInputPath, strlen(pInputPath)+1);

	FPRINTF("[Line : %d][%s] result path returned = %s\\n", __LINE__, API_NAMESPACE, pFinalPath);

	return true;
}

/**
* @function 		MessagesTimeout
* @description	 	Called if some callback is not invoked for a particular timeout
* @parameter		gpointer data
* @return 			gboolean
*/ 
gboolean MessagesTimeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
		pMainLoop = NULL;
	}
	FPRINTF("[Line : %d][%s] Callback Timeout\\n", __LINE__, API_NAMESPACE);
	return false;
}

/** @} */ //end of itc-messages
