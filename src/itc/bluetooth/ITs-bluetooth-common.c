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
#include "ITs-bluetooth-common.h"

/** @addtogroup itc-bluetooth
*  @ingroup itc
*  @{
*/

/**
* @function 					BluetoothGetError
* @description 					print the error information
* @parameter[in]				nResult: the error code
* @return 						pszErrorMsg: return the error message
*/
char *BluetoothGetError(int nResult)
{
	char *pszErrorMsg = "UNDEFINED ERROR \n";

	switch ( nResult )
	{
	case BT_ERROR_CANCELLED :
		pszErrorMsg = "BT_ERROR_CANCELLED  \n";
		break;
	case BT_ERROR_INVALID_PARAMETER :
		pszErrorMsg = "BT_ERROR_INVALID_PARAMETER \n";
		break;
	case BT_ERROR_OUT_OF_MEMORY :
		pszErrorMsg = "BT_ERROR_OUT_OF_MEMORY \n";
		break;
	case BT_ERROR_RESOURCE_BUSY :
		pszErrorMsg = "BT_ERROR_RESOURCE_BUSY \n";
		break;
	case BT_ERROR_TIMED_OUT :
		pszErrorMsg = "BT_ERROR_TIMED_OUT  \n";
		break;
	case BT_ERROR_NOW_IN_PROGRESS:
		pszErrorMsg = "BT_ERROR_NOW_IN_PROGRESS \n";
		break;
	case BT_ERROR_NOT_INITIALIZED:
		pszErrorMsg = "BT_ERROR_NOT_INITIALIZED \n";
		break;
	case BT_ERROR_NOT_ENABLED :
		pszErrorMsg = "BT_ERROR_NOT_ENABLED  \n";
		break;
	case BT_ERROR_ALREADY_DONE :
		pszErrorMsg = "BT_ERROR_ALREADY_DONE \n";
		break;
	case BT_ERROR_OPERATION_FAILED :
		pszErrorMsg = "BT_ERROR_OPERATION_FAILED  \n";
		break;
	case BT_ERROR_NOT_IN_PROGRESS :
		pszErrorMsg = "BT_ERROR_NOT_IN_PROGRESS  \n";
		break;
	case BT_ERROR_REMOTE_DEVICE_NOT_BONDED :
		pszErrorMsg = "BT_ERROR_REMOTE_DEVICE_NOT_BONDED  \n";
		break;
	case BT_ERROR_AUTH_REJECTED :
		pszErrorMsg = "BT_ERROR_AUTH_REJECTED \n";
		break;
	case BT_ERROR_AUTH_FAILED:
		pszErrorMsg = "BT_ERROR_AUTH_FAILED \n";
		break;
	case BT_ERROR_REMOTE_DEVICE_NOT_FOUND :
		pszErrorMsg = "BT_ERROR_REMOTE_DEVICE_NOT_FOUND  \n";
		break;
	case BT_ERROR_SERVICE_SEARCH_FAILED :
		pszErrorMsg = "BT_ERROR_SERVICE_SEARCH_FAILED  \n";
		break;
	case BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED:
		pszErrorMsg = "BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED \n";
		break;
	case BT_ERROR_PERMISSION_DENIED :
		pszErrorMsg = "BT_ERROR_PERMISSION_DENIED  \n";
		break;
	case BT_ERROR_NOT_SUPPORTED :
		pszErrorMsg = "BT_ERROR_NOT_SUPPORTED  \n";
		break;
	case BT_ERROR_QUOTA_EXCEEDED :
		pszErrorMsg = "BT_ERROR_QUOTA_EXCEEDED  \n";
		break;
	case BT_ERROR_NO_DATA :
		pszErrorMsg = "BT_ERROR_NO_DATA  \n";
		break;
	case BT_ERROR_DEVICE_POLICY_RESTRICTION :
		pszErrorMsg = "BT_ERROR_DEVICE_POLICY_RESTRICTION  \n";
		break;
	case BT_ERROR_AGAIN :
		pszErrorMsg = "BT_ERROR_AGAIN  \n";
		break;
	case BT_ERROR_SERVICE_NOT_FOUND :
		pszErrorMsg = "BT_ERROR_SERVICE_NOT_FOUND  \n";
		break;
	case BT_ERROR_AUTHORIZATION_REJECTED :
		pszErrorMsg = "BT_ERROR_AUTHORIZATION_REJECTED  \n";
		break;
	case BT_ERROR_NONE :
		pszErrorMsg = "BT_ERROR_NONE  \n";
		break;
	}
	return pszErrorMsg;
}

/**
* @function 		BluetoothGetEnumString
* @description	 	Maps type enums to string values
* @parameter[IN]	enum_discoverable_mode: enum value
* @return 			pszEnumString: enum value as a string
*/
char* BluetoothGetEnumString(bt_adapter_visibility_mode_e enum_discoverable_mode)
{
	char *pszEnumString = "UNKNOWN";
	switch ( enum_discoverable_mode )
	{
	case BT_ADAPTER_VISIBILITY_MODE_NON_DISCOVERABLE: 
		pszEnumString = "BT_ADAPTER_VISIBILITY_MODE_NON_DISCOVERABLE"; 
		break;  
	case BT_ADAPTER_VISIBILITY_MODE_GENERAL_DISCOVERABLE: 
		pszEnumString = "BT_ADAPTER_VISIBILITY_MODE_GENERAL_DISCOVERABLE"; 
		break;  
	case BT_ADAPTER_VISIBILITY_MODE_LIMITED_DISCOVERABLE: 
		pszEnumString = "BT_ADAPTER_VISIBILITY_MODE_LIMITED_DISCOVERABLE"; 
		break;  
	}
	return pszEnumString;
}


/**
* @function 		BluetoothGetPacketTypeEnumString
* @description	 	Maps type enums to string values
* @parameter[IN]	nRet: enum value
* @return 			pszEnumString: enum value as a string
*/
char* BluetoothGetPacketTypeEnumString(int nRet)
{
	char *pszEnumString = NULL;
	switch ( nRet )
	{
	case BT_ADAPTER_LE_PACKET_ADVERTISING:
		pszEnumString = "BT_ADAPTER_LE_PACKET_ADVERTISING"; 
		break;
	case BT_ADAPTER_LE_PACKET_SCAN_RESPONSE:
		pszEnumString = "BT_ADAPTER_LE_PACKET_SCAN_RESPONSE"; 
		break;
	default : 
		pszEnumString = "UNKNOWN"; 
		break;
	}
	return pszEnumString;
}

/**
* @function 		BluetoothInitAudio
* @description	 	Initialize bluetooth audio and create device bond
* @parameter[IN]	pszRemoteDeviceAddress: Address of the remote device to connect with.
* @return 			true or false
*/ 
bool BluetoothInitAudio(char *pszRemoteDeviceAddress)
{
	int nRetVal = bt_audio_initialize();
	if (nRetVal != BT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] bt_audio_initialize failed. Error returned = %s\\n", __LINE__, API_NAMESPACE, BluetoothGetError(nRetVal));
		return false;
	}
	else
	{
		FPRINTF("[Line : %d][%s] bt_audio_initialize passed\\n", __LINE__, API_NAMESPACE);
	}

	nRetVal = bt_device_create_bond(pszRemoteDeviceAddress);
	if (nRetVal != BT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] bt_device_create_bond failed. Error returned = %s\\n", __LINE__, API_NAMESPACE, BluetoothGetError(nRetVal));
		bt_audio_deinitialize();
		return false;
	}
	else
	{
		FPRINTF("[Line : %d][%s] bt_device_create_bond passed\\n", __LINE__, API_NAMESPACE);
	}
	sleep(5);
	return true;
}

/**
* @function 		BluetoothDeinitAudio
* @description	 	Destroy device bonding, deinitialize bluetooth audio
* @parameter[IN]	pszRemoteDeviceAddress: Address of the remote device to disconnect
* @return 			NA
*/ 
void BluetoothDeinitAudio(char *pszRemoteDeviceAddress)
{
	int nRetVal = bt_device_destroy_bond(pszRemoteDeviceAddress);
	if ( nRetVal == BT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] bt_device_destroy_bond failed, error returned = %s\\n", __LINE__, API_NAMESPACE, BluetoothGetError(nRetVal));
		return ;
	}
	sleep(2);
	nRetVal = bt_audio_deinitialize();
	if ( nRetVal == BT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] bt_audio_deinitialize failed, error returned = %s\\n", __LINE__, API_NAMESPACE, BluetoothGetError(nRetVal));
		return ;
	}	
	return;
}

/**
* @function 		BluetoothGetDataPath
* @description	 	Returns the application data path
* @parameter		pAppDataPath: application data path
* @return 			true if succeed else false
*/
bool BluetoothGetDataPath(char* pAppDataPath)
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
		FPRINTF("[Line : %d][%s] Unable to get application data path; app_get_data_path returned null value\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	strncpy(pAppDataPath, pPath, PATH_LEN);

	FPRINTF("[Line : %d][%s] application data path returned = %s\\n", __LINE__, API_NAMESPACE, pAppDataPath);

	return true;
}


/**
* @function 		StorageGetError
* @description	 	Maps storage_error_e enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* StorageGetError(storage_error_e nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case STORAGE_ERROR_NONE:		szErrorVal = "STORAGE_ERROR_NONE";			break;
	case STORAGE_ERROR_INVALID_PARAMETER:	szErrorVal = "STORAGE_ERROR_INVALID_PARAMETER";		break;
	case STORAGE_ERROR_OUT_OF_MEMORY:	szErrorVal = "STORAGE_ERROR_OUT_OF_MEMORY";		break;
	case STORAGE_ERROR_NOT_SUPPORTED:	szErrorVal = "STORAGE_ERROR_NOT_SUPPORTED";		break;
	case STORAGE_ERROR_OPERATION_FAILED:	szErrorVal = "STORAGE_ERROR_OPERATION_FAILED";		break;
	default:				szErrorVal = "Unknown Error";				break;
	}
	return szErrorVal;
}


/**
* @function 		BluetoothGetStorageDownloadsPath
* @description	 	Returns downloads directory path
* @parameter		pszPath: path of downloads directory
* @return 			true if succeed else false
*/
bool BluetoothGetStorageDownloadsPath(char *pszPath)
{
	char *pszTempPath = NULL;
	storage_error_e nRet = storage_get_directory(STORAGE_TYPE_INTERNAL, STORAGE_DIRECTORY_DOWNLOADS, &pszTempPath);//target api
	if ( nRet != STORAGE_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] storage_get_directory failed to get path for STORAGE_DIRECTORY_DOWNLOADS, error returned = %s\\n", __LINE__, API_NAMESPACE, StorageGetError(nRet));
		return false;	
	}

	if ( pszTempPath == NULL )
	{
		FPRINTF("[Line : %d][%s] storage_get_directory returned NULL path for STORAGE_DIRECTORY_DOWNLOADS\\n", __LINE__, API_NAMESPACE);
		return false;	
	}
	else
	{
		FPRINTF("[Line : %d][%s] STORAGE_DIRECTORY_DOWNLOADS path is = %s\\n", __LINE__, API_NAMESPACE, pszTempPath);
		strncpy(pszPath, pszTempPath, PATH_LEN);
		free(pszTempPath);
		pszTempPath = NULL;		
	}
	return true;
}

/**
* @function 		TimeoutFunction
* @description	 	Called if some callback is not invoked for a particular timeout
* @parameter		gpointer data
* @return 			gboolean
*/ 
gboolean TimeoutFunction(gpointer data)
{
	g_main_loop_quit((GMainLoop *)data);
	return false;
}

/** @} */
