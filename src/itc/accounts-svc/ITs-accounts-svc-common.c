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
#include "ITs-accounts-svc-common.h"

/** @addtogroup itc-accounts-svc
*  @ingroup itc
*  @{
*/

/**	
* @function 			AccManagerGetErrorMSG
* @description	 		Gets Error MSG
* @parameter	[IN]   	int nRet [error code return from API]
* @return 				NA
*/
char* AccManagerGetErrorMSG(int nRet)
{
	char* pszErrorMSG = NULL;

	switch ( nRet )
	{
	case ACCOUNT_ERROR_NONE:		    			pszErrorMSG = "ACCOUNT_ERROR_NONE";						break;
	case ACCOUNT_ERROR_INVALID_PARAMETER:			pszErrorMSG = "ACCOUNT_ERROR_INVALID_PARAMETER";		break;
	case ACCOUNT_ERROR_OUT_OF_MEMORY:				pszErrorMSG = "ACCOUNT_ERROR_OUT_OF_MEMORY";			break;
	//case ACCOUNT_ERROR_ACCESS_DENIED:				pszErrorMSG = "ACCOUNT_ERROR_ACCESS_DENIED";			break;
	case ACCOUNT_ERROR_DATABASE_BUSY:				pszErrorMSG = "ACCOUNT_ERROR_DATABASE_BUSY";			break;
	case ACCOUNT_ERROR_DUPLICATED:					pszErrorMSG = "ACCOUNT_ERROR_DUPLICATED";				break;
	case ACCOUNT_ERROR_NO_DATA:						pszErrorMSG = "ACCOUNT_ERROR_NO_DATA";					break;
	case ACCOUNT_ERROR_RECORD_NOT_FOUND:			pszErrorMSG = "ACCOUNT_ERROR_RECORD_NOT_FOUND";			break;
	case ACCOUNT_ERROR_DB_FAILED:					pszErrorMSG = "ACCOUNT_ERROR_DB_FAILED";				break;
	case ACCOUNT_ERROR_NOT_ALLOW_MULTIPLE:			pszErrorMSG = "ACCOUNT_ERROR_NOT_ALLOW_MULTIPLE";		break;
	case ACCOUNT_ERROR_NOT_REGISTERED_PROVIDER:		pszErrorMSG = "ACCOUNT_ERROR_NOT_REGISTERED_PROVIDER";	break;
	case ACCOUNT_ERROR_EVENT_SUBSCRIPTION_FAIL:		pszErrorMSG = "ACCOUNT_ERROR_EVENT_SUBSCRIPTION_FAIL";	break;
	case ACCOUNT_ERROR_DB_NOT_OPENED:				pszErrorMSG = "ACCOUNT_ERROR_DB_NOT_OPENED";			break;
	case ACCOUNT_ERROR_QUERY_SYNTAX_ERROR:			pszErrorMSG = "ACCOUNT_ERROR_QUERY_SYNTAX_ERROR";		break;
	case ACCOUNT_ERROR_ITERATOR_END:				pszErrorMSG = "ACCOUNT_ERROR_ITERATOR_END";				break;
	case ACCOUNT_ERROR_NOTI_FAILED:					pszErrorMSG = "ACCOUNT_ERROR_NOTI_FAILED";				break;
	case ACCOUNT_ERROR_PERMISSION_DENIED:			pszErrorMSG = "ACCOUNT_ERROR_PERMISSION_DENIED";		break;
	case ACCOUNT_ERROR_XML_PARSE_FAILED:			pszErrorMSG = "ACCOUNT_ERROR_XML_PARSE_FAILED";			break;
	case ACCOUNT_ERROR_XML_FILE_NOT_FOUND:			pszErrorMSG = "ACCOUNT_ERROR_XML_FILE_NOT_FOUND";		break;
	case ACCOUNT_ERROR_NOT_SUPPORTED:				pszErrorMSG = "ACCOUNT_ERROR_NOT_SUPPORTED";			break;
	default:										pszErrorMSG = "Unknown Error";
	}
	return pszErrorMSG;
}

/**
* @function 		AccManagerGetDataPath
* @description	 	Returns the application data path
* @parameter		pAppDataPath: application data path
* @return 			true if succeed else false
*/
bool AccManagerGetDataPath(char* pAppDataPath)
{
	if ( NULL == pAppDataPath )
	{
		FPRINTF( "[Line: %d] [%s] Null Path provided;Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	memset(pAppDataPath, 0, PATH_LEN);

	char* pPath = NULL;
	pPath = app_get_data_path();
	if ( NULL == pPath )
	{
		FPRINTF( "[Line: %d] [%s] Unable to get application data path;app_get_data_path returned null value \\n", __LINE__, API_NAMESPACE);
		return false;
	}

	strncpy(pAppDataPath, pPath, strlen(pPath)+1);

	FPRINTF( "[Line: %d] [%s] application data path returned = %s\\n", __LINE__, API_NAMESPACE, pAppDataPath);

	return true;
}



/**
* @function 		AccManagerAppendToAppDataPath
* @description	 	Appends the input string to application data path
* @parameter		pInputPath: path to append to data path;pFinalPath: final resultant path
* @return 			true if succeed else false
*/
bool AccManagerAppendToAppDataPath(char* pInputPath, char* pFinalPath)
{
	if ( (NULL == pInputPath) || (NULL == pFinalPath) )
	{
		FPRINTF( "[Line: %d] [%s] Null Path provided;Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	char pAppDataPath[PATH_LEN] = {0,};
	if ( false == AccManagerGetDataPath(pAppDataPath) )
	{
		return false;
	}

	memset(pFinalPath, 0, PATH_LEN);
	strncpy(pFinalPath, pAppDataPath, strlen(pAppDataPath)+1);
	strncat(pFinalPath, pInputPath, strlen(pInputPath)+1);

	FPRINTF( "[Line: %d] [%s] result path returned = %s\\n", __LINE__, API_NAMESPACE, pFinalPath);

	return true;
}

/**
* @function 		AccountGetSecret
* @description	 	Maps Types of given values to string.
* @parameter		nRet: result code returned
* @return 			Type represented as string
*/
char* AccountGetSecret(int nRet)
{
	char *pszTypeVal = NULL;

	switch ( nRet )
	{
	case ACCOUNT_SECRECY_INVALID:		pszTypeVal = "ACCOUNT_SECRECY_INVALID";		break;
	case ACCOUNT_SECRECY_INVISIBLE:		pszTypeVal = "ACCOUNT_SECRECY_INVISIBLE";	break;
	case ACCOUNT_SECRECY_VISIBLE:		pszTypeVal = "ACCOUNT_SECRECY_VISIBLE";		break;
	default:							pszTypeVal = "UNKNOWN_SECRET_TYPE";			break;
	}
	return pszTypeVal;
}

/**
* @function 		AccountGetCapabilityState
* @description	 	Maps Types of given values to string.
* @parameter		nRet: result code returned
* @return 			Type represented as string
*/
char* AccountGetCapabilityState(int nRet)
{
	char *pszTypeVal = NULL;

	switch ( nRet )
	{
	case ACCOUNT_CAPABILITY_STATE_INVALID:	pszTypeVal = "ACCOUNT_CAPABILITY_STATE_INVALID";	break;
	case ACCOUNT_CAPABILITY_DISABLED:		pszTypeVal = "ACCOUNT_CAPABILITY_DISABLED";			break;
	case ACCOUNT_CAPABILITY_ENABLED:		pszTypeVal = "ACCOUNT_CAPABILITY_ENABLED";			break;
	default:								pszTypeVal = "UNKNOWN_CAPABILITY_STATE";			break;
	}
	return pszTypeVal;
}

/**
* @function 		AccountGetAuthType
* @description	 	Maps Types of given values to string.
* @parameter		nRet: result code returned
* @return 			Type represented as string
*/
char* AccountGetAuthType(int nRet)
{
	char *pszTypeVal = NULL;

	switch(nRet)
	{
	case ACCOUNT_AUTH_TYPE_INVALID:			pszTypeVal = "ACCOUNT_AUTH_TYPE_INVALID";		break;
	case ACCOUNT_AUTH_TYPE_XAUTH:			pszTypeVal = "ACCOUNT_AUTH_TYPE_XAUTH";			break;
	case ACCOUNT_AUTH_TYPE_OAUTH:			pszTypeVal = "ACCOUNT_AUTH_TYPE_OAUTH";			break;
	case ACCOUNT_AUTH_TYPE_CLIENT_LOGIN:	pszTypeVal = "ACCOUNT_AUTH_TYPE_CLIENT_LOGIN";	break;
	default:								pszTypeVal = "UNKNOWN_AUTH_TYPE";				break;
	}
	return pszTypeVal;
}

/**
* @function 		AccountGetSyncState
* @description	 	Maps Types of given values to string.
* @parameter		nRet: result code returned
* @return 			Type represented as string
*/
char* AccountGetSyncState(int nRet)
{
	char *pszTypeVal = NULL;

	switch ( nRet )
	{
	case ACCOUNT_SYNC_INVALID:			pszTypeVal = "ACCOUNT_SYNC_INVALID";		break;
	case ACCOUNT_SYNC_NOT_SUPPORT:		pszTypeVal = "ACCOUNT_SYNC_NOT_SUPPORT";	break;
	case ACCOUNT_SYNC_STATUS_OFF:		pszTypeVal = "ACCOUNT_SYNC_STATUS_OFF";		break;
	case ACCOUNT_SYNC_STATUS_IDLE:		pszTypeVal = "ACCOUNT_SYNC_STATUS_IDLE";	break;
	case ACCOUNT_SYNC_STATUS_RUNNING:	pszTypeVal = "ACCOUNT_SYNC_STATUS_RUNNING";	break;
	case ACCOUNT_SUPPORTS_SYNC:			pszTypeVal = "ACCOUNT_SUPPORTS_SYNC";		break;
	case ACCOUNT_NOT_SUPPORTS_SYNC:		pszTypeVal = "ACCOUNT_NOT_SUPPORTS_SYNC";	break;
	default:							pszTypeVal = "UNKNOWN_SYNC_STATE";			break;
	}
	return pszTypeVal;
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

/** @} */
