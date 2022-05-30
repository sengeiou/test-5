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
#include "CTs-platform-permission-common.h"

/** @addtogroup ctc-platform-permission
* @ingroup		ctc
* @{
*/

/**
* @function 		TimeoutFunction
* @description	 	time out function for gmain loop quit
* @parameter		data : gpointer
* @return 			gboolean
*/
gboolean TimeoutFunction(gpointer data)
{
	g_main_loop_quit((GMainLoop *)data);
	return false;
}

#ifdef MOBILE	//Starts MOBILE

/**
* @function			storage_device_supported_cb_p
* @description		callback function to retrieves all storage in device
* @parameter[IN]	int storage_id - storage device id
* @parameter[IN]	storage_type_e type - storage type
* @parameter[IN]	storage_state_e - storage device state
* @parameter[IN]	void *user_data - user data
* @return			NA
*/
bool storage_device_supported_cb_p(int storage_id, storage_type_e type, storage_state_e state, const char *path, void *user_data)
{
	g_bLibStorageCallbackHit = true;

	if ( (type == STORAGE_TYPE_INTERNAL || type == STORAGE_TYPE_EXTERNAL) &&
		(state == STORAGE_STATE_UNMOUNTABLE || state == STORAGE_STATE_REMOVED || state == STORAGE_STATE_MOUNTED
			|| state ==STORAGE_STATE_MOUNTED_READ_ONLY) )
			g_bLibStorageCallbackResultValid = true;

	FPRINTF("[Line : %d][%s] storage_device_supported_callback callback hit\\n", __LINE__, API_NAMESPACE);

	if ( type == STORAGE_TYPE_INTERNAL )
	{
		g_bLibStorageIsInternal = true;
		g_nLibInternalStorageId = storage_id;
	}

	if ( type == STORAGE_TYPE_EXTERNAL )
	{
		g_bLibStorageIsExternal = true;
		g_nLibExternalStorageId = storage_id;
	}

	if ( g_bLibStorageIsInternal && g_bLibStorageIsExternal )
	{
		if (g_pMainLoop)
		{
			g_main_loop_quit(g_pMainLoop);
		}
		return false;
	}
	return true;
}

/**
* @function			get_storage_id_callback
* @description		make a call to callback function to retrieves all storage in device
* @parameter[IN]	NA
* @return			bool
*/
bool get_storage_id_callback()
{
	g_bLibStorageCallbackHit = false;
	g_bLibStorageCallbackResultValid = false;
	g_bLibStorageIsInternal = false;
	g_bLibStorageIsExternal = false;
	void *pvUserData = "User data";

	storage_error_e nRet = storage_foreach_device_supported(storage_device_supported_cb_p, pvUserData);
	if ( nRet != STORAGE_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Failed to get storage_foreach_device_supported, error returned = %s\\n", __LINE__, API_NAMESPACE, StoragePrintErrorInfo(nRet));
		return false;
	}

	g_pMainLoop = g_main_loop_new(NULL, false);
	int nTimeoutId = g_timeout_add(10000, TimeoutFunction, g_pMainLoop);
	g_main_loop_run(g_pMainLoop);
	g_source_remove(nTimeoutId);
	if ( g_bLibStorageCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] After %s, callback has not been invoked.\\n", __LINE__, API_NAMESPACE, "storage_device_supported_callback");
		return false;
	}
	else if ( g_bLibStorageCallbackResultValid == false )
	{
		FPRINTF("[Line : %d][%s] After %s, callback having invalid values.\\n", __LINE__, API_NAMESPACE, "storage_device_supported_callback");
		return false;
	}
	if ( g_bLibStorageIsInternal == false )
	{
		FPRINTF("[Line : %d][%s] After %s, callback could not find any internal storage id\\n", __LINE__, API_NAMESPACE, "storage_device_supported_callback");
		return false;
	}
	if ( g_bLibStorageIsExternal == false )
	{
		FPRINTF("[Line : %d][%s] After %s, callback could not find any external storage id\\n", __LINE__, API_NAMESPACE, "storage_device_supported_callback");
		return false;
	}

	return true;
}
#endif  //MOBILE	//End MOBILE
//Add helper function definitions here
// Callbacks

/**
* @function 			SoundManagerPrintErrorInfo
* @description 			Display the details error information
* @parameter	[IN] 	nResult (return value of wifi api)
* @return 				NA
*/
char* SoundManagerPrintErrorInfo(int nResult)
{
	char* pszErrInfo = NULL;
	switch ( nResult )
	{
	case SOUND_MANAGER_ERROR_NONE:						pszErrInfo = "SOUND_MANAGER_ERROR_NONE";					break;
	case SOUND_MANAGER_ERROR_OUT_OF_MEMORY:				pszErrInfo = "SOUND_MANAGER_ERROR_OUT_OF_MEMORY";			break;
	case SOUND_MANAGER_ERROR_INVALID_PARAMETER:			pszErrInfo = "SOUND_MANAGER_ERROR_INVALID_PARAMETER";		break;
	case SOUND_MANAGER_ERROR_INVALID_OPERATION:			pszErrInfo = "SOUND_MANAGER_ERROR_INVALID_OPERATION";		break;
	case SOUND_MANAGER_ERROR_INTERNAL:					pszErrInfo = "SOUND_MANAGER_ERROR_INTERNAL";				break;
	case SOUND_MANAGER_ERROR_POLICY:					pszErrInfo = "SOUND_MANAGER_ERROR_POLICY";					break;
	case SOUND_MANAGER_ERROR_NO_PLAYING_SOUND:			pszErrInfo = "SOUND_MANAGER_ERROR_NO_PLAYING_SOUND";		break;
	default:											pszErrInfo = "UNKNOWN ERROR";
	}

	return pszErrInfo;
}


/**
* @function 			LocationsPrintErrorInfo
* @description 			Print the error information
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* LocationsPrintErrorInfo(int nResult)
{
	char *pszErrorMsg = NULL;
	switch ( nResult )
	{
	case LOCATIONS_ERROR_NONE:							pszErrorMsg = "LOCATIONS_ERROR_NONE";						break;
	case LOCATIONS_ERROR_OUT_OF_MEMORY:					pszErrorMsg = "LOCATIONS_ERROR_OUT_OF_MEMORY";				break;
	case LOCATIONS_ERROR_INVALID_PARAMETER:				pszErrorMsg = "LOCATIONS_ERROR_INVALID_PARAMETER";			break;
	case LOCATIONS_ERROR_INCORRECT_METHOD:				pszErrorMsg = "LOCATIONS_ERROR_INCORRECT_METHOD";			break;
	case LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE:			pszErrorMsg = "LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE";		break;
	case LOCATIONS_ERROR_GPS_SETTING_OFF:				pszErrorMsg = "LOCATIONS_ERROR_GPS_SETTING_OFF";			break;
	case LOCATIONS_ERROR_SECURITY_RESTRICTED:			pszErrorMsg = "LOCATIONS_ERROR_SECURITY_RESTRICTED";		break;
	case LOCATIONS_ERROR_ACCESSIBILITY_NOT_ALLOWED:		pszErrorMsg = "LOCATIONS_ERROR_ACCESSIBILITY_NOT_ALLOWED";	break;
	default:											pszErrorMsg = "UNDEFINED ERROR";
	}

	return pszErrorMsg;
}

/**
* @function				AppControlPrintErrorInfo
* @description 			Print the error information
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* AppControlPrintErrorInfo(int nResult)
{
	char *pszErrorMsg = NULL;
	switch ( nResult )
	{
	case APP_CONTROL_ERROR_NONE:					pszErrorMsg = "APP_CONTROL_ERROR_NONE";					break;
	case APP_CONTROL_ERROR_INVALID_PARAMETER:		pszErrorMsg = "APP_CONTROL_ERROR_INVALID_PARAMETER";	break;
	case APP_CONTROL_ERROR_OUT_OF_MEMORY:			pszErrorMsg = "APP_CONTROL_ERROR_OUT_OF_MEMORY";		break;
	case APP_CONTROL_ERROR_APP_NOT_FOUND:			pszErrorMsg = "APP_CONTROL_ERROR_APP_NOT_FOUND";		break;
	case APP_CONTROL_ERROR_KEY_NOT_FOUND:			pszErrorMsg = "APP_CONTROL_ERROR_KEY_NOT_FOUND";		break;
	case APP_CONTROL_ERROR_KEY_REJECTED:			pszErrorMsg = "APP_CONTROL_ERROR_KEY_REJECTED";			break;
	case APP_CONTROL_ERROR_INVALID_DATA_TYPE:		pszErrorMsg = "APP_CONTROL_ERROR_INVALID_DATA_TYPE";	break;
	case APP_CONTROL_ERROR_LAUNCH_REJECTED:			pszErrorMsg = "APP_CONTROL_ERROR_LAUNCH_REJECTED";		break;
	case APP_CONTROL_ERROR_PERMISSION_DENIED:		pszErrorMsg = "APP_CONTROL_ERROR_PERMISSION_DENIED ";	break;
	case APP_CONTROL_ERROR_LAUNCH_FAILED:			pszErrorMsg = "APP_CONTROL_ERROR_LAUNCH_FAILED";		break;
	case APP_CONTROL_ERROR_TIMED_OUT:				pszErrorMsg = "APP_CONTROL_ERROR_TIMED_OUT";			break;
	default:										pszErrorMsg = "UKNOWN ERROR";
	}

	return pszErrorMsg;
}

/**
* @function				PackageManagerPrintErrorInfo
* @description 			Print the error information
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* PackageManagerPrintErrorInfo(int nResult)
{
	char *pszErrorMsg = NULL;
	switch ( nResult )
	{
	case PACKAGE_MANAGER_ERROR_NONE:				pszErrorMsg = "PACKAGE_MANAGER_ERROR_NONE";					break;
	case PACKAGE_MANAGER_ERROR_INVALID_PARAMETER:	pszErrorMsg = "PACKAGE_MANAGER_ERROR_INVALID_PARAMETER";	break;
	case PACKAGE_MANAGER_ERROR_OUT_OF_MEMORY:		pszErrorMsg = "PACKAGE_MANAGER_ERROR_OUT_OF_MEMORY";		break;
	case PACKAGE_MANAGER_ERROR_IO_ERROR:			pszErrorMsg = "PACKAGE_MANAGER_ERROR_IO_ERROR";				break;
	case PACKAGE_MANAGER_ERROR_NO_SUCH_PACKAGE:		pszErrorMsg = "PACKAGE_MANAGER_ERROR_NO_SUCH_PACKAGE";		break;
	case PACKAGE_MANAGER_ERROR_SYSTEM_ERROR:		pszErrorMsg = "PACKAGE_MANAGER_ERROR_SYSTEM_ERROR";			break;
	case PACKAGE_MANAGER_ERROR_PERMISSION_DENIED:	pszErrorMsg = "PACKAGE_MANAGER_ERROR_PERMISSION_DENIED ";	break;
	default:										pszErrorMsg = "UKNOWN ERROR";
	}

	return pszErrorMsg;
}

#ifdef MOBILE
/**
* @function 			DownloadPrintErrorInfo
* @description 			Print the error information
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* DownloadPrintErrorInfo(int nResult)
{
	char *pszErrorMsg = NULL;
	switch ( nResult )
	{
	case DOWNLOAD_ERROR_NONE:						pszErrorMsg = "DOWNLOAD_ERROR_NONE";					break;
	case DOWNLOAD_ERROR_INVALID_PARAMETER:			pszErrorMsg = "DOWNLOAD_ERROR_INVALID_PARAMETER";		break;
	case DOWNLOAD_ERROR_OUT_OF_MEMORY:				pszErrorMsg = "DOWNLOAD_ERROR_OUT_OF_MEMORY";			break;
	case DOWNLOAD_ERROR_NETWORK_UNREACHABLE:		pszErrorMsg = "DOWNLOAD_ERROR_NETWORK_UNREACHABLE";		break;
	case DOWNLOAD_ERROR_CONNECTION_TIMED_OUT:		pszErrorMsg = "DOWNLOAD_ERROR_CONNECTION_TIMED_OUT";	break;
	case DOWNLOAD_ERROR_NO_SPACE:					pszErrorMsg = "DOWNLOAD_ERROR_NO_SPACE";				break;
	case DOWNLOAD_ERROR_FIELD_NOT_FOUND:			pszErrorMsg = "DOWNLOAD_ERROR_FIELD_NOT_FOUND";			break;
	case DOWNLOAD_ERROR_PERMISSION_DENIED:			pszErrorMsg = "DOWNLOAD_ERROR_PERMISSION_DENIED";		break;
	case DOWNLOAD_ERROR_INVALID_STATE:				pszErrorMsg = "DOWNLOAD_ERROR_INVALID_STATE";			break;
	case DOWNLOAD_ERROR_CONNECTION_FAILED:			pszErrorMsg = "DOWNLOAD_ERROR_CONNECTION_FAILED";		break;
	case DOWNLOAD_ERROR_INVALID_URL:				pszErrorMsg = "DOWNLOAD_ERROR_INVALID_URL";				break;
	case DOWNLOAD_ERROR_INVALID_DESTINATION:		pszErrorMsg = "DOWNLOAD_ERROR_INVALID_DESTINATION";		break;
	case DOWNLOAD_ERROR_TOO_MANY_DOWNLOADS:			pszErrorMsg = "DOWNLOAD_ERROR_TOO_MANY_DOWNLOADS";		break;
	case DOWNLOAD_ERROR_QUEUE_FULL:					pszErrorMsg = "DOWNLOAD_ERROR_QUEUE_FULL";				break;
	case DOWNLOAD_ERROR_ALREADY_COMPLETED:			pszErrorMsg = "DOWNLOAD_ERROR_ALREADY_COMPLETED";		break;
	case DOWNLOAD_ERROR_FILE_ALREADY_EXISTS:		pszErrorMsg = "DOWNLOAD_ERROR_FILE_ALREADY_EXISTS";		break;
	case DOWNLOAD_ERROR_CANNOT_RESUME:				pszErrorMsg = "DOWNLOAD_ERROR_CANNOT_RESUME";			break;
	case DOWNLOAD_ERROR_TOO_MANY_REDIRECTS:			pszErrorMsg = "DOWNLOAD_ERROR_TOO_MANY_REDIRECTS";		break;
	case DOWNLOAD_ERROR_UNHANDLED_HTTP_CODE:		pszErrorMsg = "DOWNLOAD_ERROR_UNHANDLED_HTTP_CODE";		break;
	case DOWNLOAD_ERROR_REQUEST_TIMEOUT:			pszErrorMsg = "DOWNLOAD_ERROR_REQUEST_TIMEOUT";			break;
	case DOWNLOAD_ERROR_RESPONSE_TIMEOUT:			pszErrorMsg = "DOWNLOAD_ERROR_RESPONSE_TIMEOUT";		break;
	case DOWNLOAD_ERROR_SYSTEM_DOWN:				pszErrorMsg = "DOWNLOAD_ERROR_SYSTEM_DOWN";				break;
	case DOWNLOAD_ERROR_ID_NOT_FOUND:				pszErrorMsg = "DOWNLOAD_ERROR_ID_NOT_FOUND";			break;
	case DOWNLOAD_ERROR_INVALID_NETWORK_TYPE:		pszErrorMsg = "DOWNLOAD_ERROR_INVALID_NETWORK_TYPE";	break;
	case DOWNLOAD_ERROR_NO_DATA:					pszErrorMsg = "DOWNLOAD_ERROR_NO_DATA";					break;
	case DOWNLOAD_ERROR_IO_ERROR:					pszErrorMsg = "DOWNLOAD_ERROR_IO_ERROR";				break;
	default:										pszErrorMsg = "UNKNOWN ERROR";
	}

	return pszErrorMsg;
}
#endif  //End MOBILE

/**
* @function 			AlarmPrintErrorInfo
* @description 			Print the error information
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* AlarmPrintErrorInfo(int nResult)
{
	char *pszErrorMsg = NULL;
	switch ( nResult )
	{
	case ALARM_ERROR_NONE:							pszErrorMsg = "ALARM_ERROR_NONE";						break;
	case ALARM_ERROR_INVALID_PARAMETER:				pszErrorMsg = "ALARM_ERROR_INVALID_PARAMETER";			break;
	case ALARM_ERROR_INVALID_TIME:					pszErrorMsg = "ALARM_ERROR_INVALID_TIME";				break;
	case ALARM_ERROR_INVALID_DATE:					pszErrorMsg = "ALARM_ERROR_INVALID_DATE";				break;
	case ALARM_ERROR_CONNECTION_FAIL:				pszErrorMsg = "ALARM_ERROR_CONNECTION_FAIL";			break;
	case ALARM_ERROR_OUT_OF_MEMORY:					pszErrorMsg = "ALARM_ERROR_OUT_OF_MEMORY";				break;
	case ALARM_ERROR_PERMISSION_DENIED:				pszErrorMsg = "ALARM_ERROR_PERMISSION_DENIED";			break;
	default:										pszErrorMsg = "UNKNOWN ERROR";
	}

	return pszErrorMsg;
}

#ifdef MOBILE	//Starts MOBILE
/**
* @function 			CalendarPrintErrorInfo
* @description	 		Prints Error API Error message
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* CalendarPrintErrorInfo(int nResult)
{
	char* pszErrInfo = NULL;
	switch ( nResult )
	{
	case CALENDAR_ERROR_NONE:						pszErrInfo = "CALENDAR_ERROR_NONE";						break;
	case CALENDAR_ERROR_DB_FAILED:					pszErrInfo = "CALENDAR_ERROR_DB_FAILED";				break;
	case CALENDAR_ERROR_DB_RECORD_NOT_FOUND:		pszErrInfo = "CALENDAR_ERROR_DB_RECORD_NOT_FOUND";		break;
	case CALENDAR_ERROR_OUT_OF_MEMORY:				pszErrInfo = "CALENDAR_ERROR_OUT_OF_MEMORY";			break;
	case CALENDAR_ERROR_INVALID_PARAMETER:			pszErrInfo = "CALENDAR_ERROR_INVALID_PARAMETER";		break;
	case CALENDAR_ERROR_NO_DATA:					pszErrInfo = "CALENDAR_ERROR_NO_DATA";					break;
	case CALENDAR_ERROR_NOW_IN_PROGRESS:			pszErrInfo = "CALENDAR_ERROR_NOW_IN_PROGRESS";			break;
	case CALENDAR_ERROR_ALREADY_IN_PROGRESS:		pszErrInfo = "CALENDAR_ERROR_ALREADY_IN_PROGRESS";		break;
	case CALENDAR_ERROR_NOT_PERMITTED:				pszErrInfo = "CALENDAR_ERROR_NOT_PERMITTED";			break;
	case CALENDAR_ERROR_IPC:						pszErrInfo = "CALENDAR_ERROR_IPC";						break;
	case CALENDAR_ERROR_FILE_NO_SPACE:				pszErrInfo = "CALENDAR_ERROR_FILE_NO_SPACE";			break;
	case CALENDAR_ERROR_PERMISSION_DENIED:			pszErrInfo = "CALENDAR_ERROR_PERMISSION_DENIED";		break;
	case CALENDAR_ERROR_SYSTEM:						pszErrInfo = "CALENDAR_ERROR_SYSTEM";					break;
	default:										pszErrInfo = "UNKNOWN ERROR";
	}

	return pszErrInfo;
}
#endif  //MOBILE	//End MOBILE

/**
* @function 			SystemSettingsPrintErrorInfo
* @description 			Print the error of system settings information
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* SystemSettingsPrintErrorInfo(int nResult)
{
	char *pszErrLog = NULL;
	switch ( nResult )
	{
	case SYSTEM_SETTINGS_ERROR_NONE:							pszErrLog = "SYSTEM_SETTINGS_ERROR_NONE";							break;
	case SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER:				pszErrLog = "SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER";				break;
	case SYSTEM_SETTINGS_ERROR_OUT_OF_MEMORY:					pszErrLog = "SYSTEM_SETTINGS_ERROR_OUT_OF_MEMORY";					break;
	case SYSTEM_SETTINGS_ERROR_IO_ERROR:						pszErrLog = "SYSTEM_SETTINGS_ERROR_IO_ERROR";						break;
	case SYSTEM_SETTINGS_ERROR_LOCKSCREEN_APP_PASSWORD_MODE:	pszErrLog = "SYSTEM_SETTINGS_ERROR_LOCKSCREEN_APP_PASSWORD_MODE";	break;
	default:													pszErrLog = "UNKNOWN ERROR";
	}

	return pszErrLog;
}

#ifdef MOBILE		//Starts MOBILE
/**
* @function 			CkmcPrintErrorInfo
* @description 			Print the error of Key Manager
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* CkmcPrintErrorInfo(int nResult)
{
	char *pszErrLog = NULL;
	switch ( nResult )
	{
	case CKMC_ERROR_NONE:						pszErrLog = "CKMC_ERROR_NONE ";						break;
	case CKMC_ERROR_INVALID_PARAMETER:			pszErrLog = "CKMC_ERROR_INVALID_PARAMETER";			break;
	case CKMC_ERROR_DB_LOCKED:					pszErrLog = "CKMC_ERROR_DB_LOCKED";					break;
	case CKMC_ERROR_DB_ERROR:					pszErrLog = "CKMC_ERROR_DB_ERROR";					break;
	case CKMC_ERROR_DB_ALIAS_UNKNOWN:			pszErrLog =  "CKMC_ERROR_DB_ALIAS_UNKNOWN";			break;
	case CKMC_ERROR_OUT_OF_MEMORY:				pszErrLog =  "CKMC_ERROR_OUT_OF_MEMORY";			break;
	case CKMC_ERROR_SOCKET:						pszErrLog =  "CKMC_ERROR_SOCKET";					break;
	case CKMC_ERROR_BAD_REQUEST:				pszErrLog =  "CKMC_ERROR_BAD_REQUEST";				break;
	case CKMC_ERROR_BAD_RESPONSE:				pszErrLog =  "CKMC_ERROR_BAD_RESPONSE";				break;
	case CKMC_ERROR_SEND_FAILED:				pszErrLog =  "CKMC_ERROR_SEND_FAILED";				break;
	case CKMC_ERROR_RECV_FAILED:				pszErrLog =  "CKMC_ERROR_RECV_FAILED";				break;
	case CKMC_ERROR_AUTHENTICATION_FAILED:		pszErrLog =  "CKMC_ERROR_AUTHENTICATION_FAILED ";	break;
	case CKMC_ERROR_BUFFER_TOO_SMALL:			pszErrLog =  "CKMC_ERROR_BUFFER_TOO_SMALL";			break;
	case CKMC_ERROR_SERVER_ERROR:				pszErrLog =  "CKMC_ERROR_SERVER_ERROR";				break;
	case CKMC_ERROR_DB_ALIAS_EXISTS:			pszErrLog =  "CKMC_ERROR_DB_ALIAS_EXISTS";			break;
	case CKMC_ERROR_VERIFICATION_FAILED:		pszErrLog =  "CKMC_ERROR_VERIFICATION_FAILED";		break;
	case CKMC_ERROR_INVALID_FORMAT:				pszErrLog =  "CKMC_ERROR_INVALID_FORMAT";			break;
	case CKMC_ERROR_FILE_ACCESS_DENIED:			pszErrLog =  "CKMC_ERROR_FILE_ACCESS_DENIED ";		break;
	case CKMC_ERROR_NOT_EXPORTABLE:				pszErrLog =  "CKMC_ERROR_NOT_EXPORTABLE";			break;
	case CKMC_ERROR_UNKNOWN:					pszErrLog =  "CKMC_ERROR_UNKNOWN ";					break;
	default:									pszErrLog =  "UNKNOWN ERROR";
	}

	return pszErrLog;
}
#endif  //MOBILE	//End MOBILE

/**
* @function 			PushServicePrintErrorInfo
* @description 			Print the error information
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* PushServicePrintErrorInfo(int nResult)
{
	char *pszErrorMsg = NULL;
	switch ( nResult )
	{
	case PUSH_SERVICE_ERROR_NONE:					pszErrorMsg = "PUSH_SERVICE_ERROR_NONE";				break;
	case PUSH_SERVICE_ERROR_OUT_OF_MEMORY:			pszErrorMsg = "PUSH_SERVICE_ERROR_OUT_OF_MEMORY";		break;
	case PUSH_SERVICE_ERROR_INVALID_PARAMETER:		pszErrorMsg = "PUSH_SERVICE_ERROR_INVALID_PARAMETER";	break;
	case PUSH_SERVICE_ERROR_NO_DATA:				pszErrorMsg = "PUSH_SERVICE_ERROR_NO_DATA";				break;
	case PUSH_SERVICE_ERROR_NOT_CONNECTED:			pszErrorMsg = "PUSH_SERVICE_ERROR_NOT_CONNECTED";		break;
	case PUSH_SERVICE_ERROR_OPERATION_FAILED:		pszErrorMsg = "PUSH_SERVICE_ERROR_OPERATION_FAILED";	break;
	case PUSH_SERVICE_ERROR_PERMISSION_DENIED:		pszErrorMsg = "PUSH_SERVICE_ERROR_PERMISSION_DENIED";	break;
	default:										pszErrorMsg = "UNDEFINED ERROR";
	}

	return pszErrorMsg;
}

/**
* @function 			BluetoothPrintErrorInfo
* @description 			Print the error information
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* BluetoothPrintErrorInfo(int nResult)
{
	char *pszErrorMsg = NULL;
	switch ( nResult )
	{
	case BT_ERROR_NONE:							pszErrorMsg = "BT_ERROR_NONE";						break;
	case BT_ERROR_CANCELLED:					pszErrorMsg = "BT_ERROR_CANCELLED";					break;
	case BT_ERROR_INVALID_PARAMETER:			pszErrorMsg = "BT_ERROR_INVALID_PARAMETER";			break;
	case BT_ERROR_OUT_OF_MEMORY:				pszErrorMsg = "BT_ERROR_OUT_OF_MEMORY";				break;
	case BT_ERROR_RESOURCE_BUSY:				pszErrorMsg = "BT_ERROR_RESOURCE_BUSY";				break;
	case BT_ERROR_TIMED_OUT:					pszErrorMsg = "BT_ERROR_TIMED_OUT";					break;
	case BT_ERROR_NOW_IN_PROGRESS:				pszErrorMsg = "BT_ERROR_NOW_IN_PROGRESS";			break;
	case BT_ERROR_NOT_INITIALIZED:				pszErrorMsg = "BT_ERROR_NOT_INITIALIZED";			break;
	case BT_ERROR_NOT_ENABLED:					pszErrorMsg = "BT_ERROR_NOT_ENABLED";				break;
	case BT_ERROR_ALREADY_DONE:					pszErrorMsg = "BT_ERROR_ALREADY_DONE";				break;
	case BT_ERROR_OPERATION_FAILED:				pszErrorMsg = "BT_ERROR_OPERATION_FAILED";			break;
	case BT_ERROR_NOT_IN_PROGRESS:				pszErrorMsg = "BT_ERROR_NOT_IN_PROGRESS";			break;
	case BT_ERROR_REMOTE_DEVICE_NOT_BONDED:		pszErrorMsg = "BT_ERROR_REMOTE_DEVICE_NOT_BONDED";	break;
	case BT_ERROR_AUTH_REJECTED:				pszErrorMsg = "BT_ERROR_AUTH_REJECTED";				break;
	case BT_ERROR_AUTH_FAILED:					pszErrorMsg = "BT_ERROR_AUTH_FAILED";				break;
	case BT_ERROR_REMOTE_DEVICE_NOT_FOUND:		pszErrorMsg = "BT_ERROR_REMOTE_DEVICE_NOT_FOUND";	break;
	case BT_ERROR_SERVICE_SEARCH_FAILED:		pszErrorMsg = "BT_ERROR_SERVICE_SEARCH_FAILED";		break;
	case BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED:	pszErrorMsg = "BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED";break;
	case BT_ERROR_PERMISSION_DENIED:			pszErrorMsg = "BT_ERROR_PERMISSION_DENIED";			break;
	default:									pszErrorMsg = "UNDEFINED ERROR";
	}

	return pszErrorMsg;
}

/**
* @function 			RecorderPrintErrorMsg
* @description 			Print message.
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* RecorderPrintErrorMsg(int nRet)
{
	char *pszErrorMsg = NULL;
	switch(nRet)
	{
	case RECORDER_ERROR_NONE:							pszErrorMsg = "RECORDER_ERROR_NONE";					break;
	case RECORDER_ERROR_INVALID_PARAMETER:				pszErrorMsg = "RECORDER_ERROR_INVALID_PARAMETER";		break;
	case RECORDER_ERROR_INVALID_STATE:					pszErrorMsg = "RECORDER_ERROR_INVALID_STATE";			break;
	case RECORDER_ERROR_OUT_OF_MEMORY:					pszErrorMsg = "RECORDER_ERROR_OUT_OF_MEMORY";			break;
	case RECORDER_ERROR_DEVICE:							pszErrorMsg = "RECORDER_ERROR_DEVICE";					break;
	case RECORDER_ERROR_INVALID_OPERATION:				pszErrorMsg = "RECORDER_ERROR_INVALID_OPERATION";		break;
	case RECORDER_ERROR_SECURITY_RESTRICTED:			pszErrorMsg = "RECORDER_ERROR_SECURITY_RESTRICTED";		break;
	case RECORDER_ERROR_ESD:							pszErrorMsg = "RECORDER_ERROR_ESD";						break;
	case RECORDER_ERROR_OUT_OF_STORAGE:					pszErrorMsg = "RECORDER_ERROR_OUT_OF_STORAGE";			break;
	case RECORDER_ERROR_PERMISSION_DENIED:				pszErrorMsg = "RECORDER_ERROR_PERMISSION_DENIED";		break;
	default:											pszErrorMsg = "UNKNOWN ERROR";
	}

	return pszErrorMsg;
}

/**
* @function 			MessagesPrintErrorInfo
* @description 			Display the details error information
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* MessagesPrintErrorInfo(int nResult)
{
	char *pszErrLog = NULL;
	switch ( nResult )
	{
	case MESSAGES_ERROR_NONE:								pszErrLog = "MESSAGES_ERROR_NONE";								break;
	case MESSAGES_ERROR_OUT_OF_MEMORY:						pszErrLog = "MESSAGES_ERROR_OUT_OF_MEMORY";						break;
	case MESSAGES_ERROR_INVALID_PARAMETER:					pszErrLog = "MESSAGES_ERROR_INVALID_PARAMETER";					break;
	case MESSAGES_ERROR_SERVER_NOT_READY:					pszErrLog = "MESSAGES_ERROR_SERVER_NOT_READY";					break;
	case MESSAGES_ERROR_COMMUNICATION_WITH_SERVER_FAILED:	pszErrLog = "MESSAGES_ERROR_COMMUNICATION_WITH_SERVER_FAILED";	break;
	case MESSAGES_ERROR_SENDING_FAILED:						pszErrLog = "MESSAGES_ERROR_SENDING_FAILED";					break;
	case MESSAGES_ERROR_OPERATION_FAILED:					pszErrLog = "MESSAGES_ERROR_OPERATION_FAILED";					break;
	case MESSAGES_ERROR_NO_SIM_CARD:						pszErrLog = "MESSAGES_ERROR_NO_SIM_CARD";						break;
	case MESSAGES_ERROR_NO_DATA:							pszErrLog = "MESSAGES_ERROR_NO_DATA";							break;
	default:												pszErrLog =  "UNKNOWN ERROR";
	}

	return pszErrLog;
}

/**
* @function 			CameraPrintErrorMsg
* @description 			Display the details error information
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* CameraPrintErrorMsg(int nRet)
{
	char *pszErrorMsg = NULL;

	switch(nRet)
	{
	case CAMERA_ERROR_NONE:						pszErrorMsg = "CAMERA_ERROR_NONE";					break;
	case CAMERA_ERROR_INVALID_PARAMETER:		pszErrorMsg = "CAMERA_ERROR_INVALID_PARAMETER";		break;
	case CAMERA_ERROR_INVALID_STATE:			pszErrorMsg = "CAMERA_ERROR_INVALID_STATE";			break;
	case CAMERA_ERROR_OUT_OF_MEMORY:			pszErrorMsg = "CAMERA_ERROR_OUT_OF_MEMORY";			break;
	case CAMERA_ERROR_DEVICE:					pszErrorMsg = "CAMERA_ERROR_DEVICE";				break;
	case CAMERA_ERROR_INVALID_OPERATION:		pszErrorMsg = "CAMERA_ERROR_INVALID_OPERATION";		break;
	case CAMERA_ERROR_SECURITY_RESTRICTED:		pszErrorMsg = "CAMERA_ERROR_SECURITY_RESTRICTED";	break;
	case CAMERA_ERROR_DEVICE_BUSY:				pszErrorMsg = "CAMERA_ERROR_DEVICE_BUSY";			break;
	case CAMERA_ERROR_DEVICE_NOT_FOUND:			pszErrorMsg = "CAMERA_ERROR_DEVICE_NOT_FOUND";		break;
	case CAMERA_ERROR_ESD:						pszErrorMsg = "CAMERA_ERROR_ESD";					break;
	case CAMERA_ERROR_PERMISSION_DENIED:		pszErrorMsg = "CAMERA_ERROR_PERMISSION_DENIED";		break;
	default:									pszErrorMsg = "UNKNOWN ERROR";
	}

	return pszErrorMsg;
}


/**
* @function 			NetworkConnectionPrintErrorMsg
* @description 			Display the details error information
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* NetworkConnectionPrintErrorMsg(int nRet)
{
	char* pszEnum = NULL;
	switch(nRet)
	{
	case CONNECTION_ERROR_NONE:									pszEnum = "CONNECTION_ERROR_NONE";							break;
	case CONNECTION_ERROR_INVALID_PARAMETER:					pszEnum = "CONNECTION_ERROR_INVALID_PARAMETER";				break;
	case CONNECTION_ERROR_OUT_OF_MEMORY:						pszEnum = "CONNECTION_ERROR_OUT_OF_MEMORY";					break;
	case CONNECTION_ERROR_INVALID_OPERATION:					pszEnum = "CONNECTION_ERROR_INVALID_OPERATION";				break;
	case CONNECTION_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED:			pszEnum = "CONNECTION_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED";	break;
	case CONNECTION_ERROR_OPERATION_FAILED:						pszEnum = "CONNECTION_ERROR_OPERATION_FAILED";				break;
	case CONNECTION_ERROR_ITERATOR_END:							pszEnum = "CONNECTION_ERROR_ITERATOR_END";					break;
	case CONNECTION_ERROR_NO_CONNECTION:						pszEnum = "CONNECTION_ERROR_NO_CONNECTION";					break;
	case CONNECTION_ERROR_ALREADY_EXISTS:						pszEnum = "CONNECTION_ERROR_ALREADY_EXISTS";				break;
	case CONNECTION_ERROR_OPERATION_ABORTED:					pszEnum = "CONNECTION_ERROR_OPERATION_ABORTED";				break;
	case CONNECTION_ERROR_DHCP_FAILED:							pszEnum = "CONNECTION_ERROR_DHCP_FAILED";					break;
	case CONNECTION_ERROR_INVALID_KEY:							pszEnum = "CONNECTION_ERROR_INVALID_KEY";					break;
	case CONNECTION_ERROR_NO_REPLY:								pszEnum = "CONNECTION_ERROR_NO_REPLY";						break;
	case CONNECTION_ERROR_PERMISSION_DENIED:					pszEnum = "CONNECTION_ERROR_PERMISSION_DENIED";				break;
	case CONNECTION_ERROR_NOT_SUPPORTED:						pszEnum = "CONNECTION_ERROR_NOT_SUPPORTED";					break;
	case CONNECTION_ERROR_ALREADY_INITIALIZED:					pszEnum = "CONNECTION_ERROR_ALREADY_INITIALIZED";			break;
	case CONNECTION_ERROR_NOT_INITIALIZED:						pszEnum = "CONNECTION_ERROR_NOT_INITIALIZED";				break;
	default:													pszEnum = "UNKNOWN ERROR";
	}

	return pszEnum;
}

/**
* @function 			NotificationPrintAPIErrorMSG
* @description	 		Display the details error information
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* NotificationPrintAPIErrorMSG(int nRet)
{
	char* pszErrorMessage = NULL;
	switch(nRet)
	{
	case NOTIFICATION_ERROR_NONE:					pszErrorMessage = "NOTIFICATION_ERROR_NONE ";				break;
	case NOTIFICATION_ERROR_INVALID_PARAMETER:		pszErrorMessage = "NOTIFICATION_ERROR_INVALID_PARAMETER ";	break;
	case NOTIFICATION_ERROR_OUT_OF_MEMORY:			pszErrorMessage = "NOTIFICATION_ERROR_OUT_OF_MEMORY";		break;
	case NOTIFICATION_ERROR_FROM_DB:				pszErrorMessage = "NOTIFICATION_ERROR_FROM_DB";				break;
	case NOTIFICATION_ERROR_ALREADY_EXIST_ID:		pszErrorMessage = "NOTIFICATION_ERROR_ALREADY_EXIST_ID";	break;
	case NOTIFICATION_ERROR_FROM_DBUS:				pszErrorMessage = "NOTIFICATION_ERROR_FROM_DBUS";			break;
	case NOTIFICATION_ERROR_NOT_EXIST_ID:			pszErrorMessage = "NOTIFICATION_ERROR_NOT_EXIST_ID";		break;
	case NOTIFICATION_ERROR_IO_ERROR:				pszErrorMessage = "NOTIFICATION_ERROR_IO_ERROR";			break;
	case NOTIFICATION_ERROR_SERVICE_NOT_READY:		pszErrorMessage = "NOTIFICATION_ERROR_SERVICE_NOT_READY";	break;
	case NOTIFICATION_ERROR_PERMISSION_DENIED:		pszErrorMessage = "NOTIFICATION_ERROR_PERMISSION_DENIED";	break;
	default:										pszErrorMessage = "UNKNOWN ERROR";
	}

	return pszErrorMessage;
}
/**
* @function 			DevicePrintErrorInfo
* @description			Display the details error information
* @parameter   [IN]		nResult, the error code
* @return 				NA
*/
char* DevicePrintErrorInfo(int nResult)
{
	char* pszErrInfo = NULL;
	switch ( nResult )
	{
	case DEVICE_ERROR_NONE:						pszErrInfo = "DEVICE_ERROR_NONE";					break;
	case DEVICE_ERROR_OPERATION_FAILED:			pszErrInfo = "DEVICE_ERROR_OPERATION_FAILED";		break;
	case DEVICE_ERROR_INVALID_PARAMETER:		pszErrInfo = "DEVICE_ERROR_INVALID_PARAMETER";		break;
	case DEVICE_ERROR_ALREADY_IN_PROGRESS:		pszErrInfo = "DEVICE_ERROR_ALREADY_IN_PROGRESS";	break;
	case DEVICE_ERROR_NOT_SUPPORTED:			pszErrInfo = "DEVICE_ERROR_NOT_SUPPORTED";			break;
	case DEVICE_ERROR_NOT_INITIALIZED:			pszErrInfo = "DEVICE_ERROR_NOT_INITIALIZED";		break;
	default:									pszErrInfo = "UNKNOWN ERROR";
	}

	return pszErrInfo;
}

/**
* @function 			DataControlPrintErrorInfo
* @description			Display the details error information
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* DataControlPrintErrorInfo(int nResult)
{
	char* pszErrInfo = NULL;

	switch ( nResult )
	{
	case DATA_CONTROL_ERROR_NONE:					pszErrInfo = "DATA_CONTROL_ERROR_NONE";					break;
	case DATA_CONTROL_ERROR_OUT_OF_MEMORY:			pszErrInfo = "DATA_CONTROL_ERROR_OUT_OF_MEMORY";		break;
	case DATA_CONTROL_ERROR_IO_ERROR:				pszErrInfo = "DATA_CONTROL_ERROR_IO_ERROR";				break;
	case DATA_CONTROL_ERROR_INVALID_PARAMETER:		pszErrInfo = "DATA_CONTROL_ERROR_INVALID_PARAMETER";	break;
	case DATA_CONTROL_ERROR_MAX_EXCEEDED:			pszErrInfo = "DATA_CONTROL_ERROR_MAX_EXCEEDED";			break;
	default:										pszErrInfo = "UNKNOWN ERROR";
	}

	return pszErrInfo;
}

/**
* @function 			AccountManagerPrintErrorCode
* @description			Display the details error information
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* AccountManagerPrintErrorCode(int nResult)
{
	char* pszErrInfo = NULL;
	switch ( nResult )
	{
	case ACCOUNT_ERROR_NONE:						pszErrInfo = "ACCOUNT_ERROR_NONE";						break;
	case ACCOUNT_ERROR_OUT_OF_MEMORY:				pszErrInfo = "ACCOUNT_ERROR_OUT_OF_MEMORY";				break;
	case ACCOUNT_ERROR_INVALID_PARAMETER:			pszErrInfo = "ACCOUNT_ERROR_INVALID_PARAMETER ";		break;
	case ACCOUNT_ERROR_DUPLICATED:					pszErrInfo = "ACCOUNT_ERROR_DUPLICATED ";				break;
	case ACCOUNT_ERROR_NO_DATA:						pszErrInfo = "ACCOUNT_ERROR_NO_DATA";					break;
	case ACCOUNT_ERROR_RECORD_NOT_FOUND:			pszErrInfo = "ACCOUNT_ERROR_RECORD_NOT_FOUND ";			break;
	case ACCOUNT_ERROR_DB_FAILED:					pszErrInfo = "ACCOUNT_ERROR_DB_FAILED ";				break;
	case ACCOUNT_ERROR_DB_NOT_OPENED:				pszErrInfo = "ACCOUNT_ERROR_DB_NOT_OPENED  ";			break;
	case ACCOUNT_ERROR_QUERY_SYNTAX_ERROR:			pszErrInfo = "ACCOUNT_ERROR_QUERY_SYNTAX_ERROR";		break;
	case ACCOUNT_ERROR_ITERATOR_END:				pszErrInfo = "ACCOUNT_ERROR_ITERATOR_END ";				break;
	case ACCOUNT_ERROR_NOTI_FAILED:					pszErrInfo = "ACCOUNT_ERROR_NOTI_FAILED ";				break;
	case ACCOUNT_ERROR_PERMISSION_DENIED:			pszErrInfo = "ACCOUNT_ERROR_PERMISSION_DENIED  ";		break;
	case ACCOUNT_ERROR_XML_PARSE_FAILED:			pszErrInfo = "ACCOUNT_ERROR_XML_PARSE_FAILED ";			break;
	case ACCOUNT_ERROR_XML_FILE_NOT_FOUND:			pszErrInfo = "ACCOUNT_ERROR_XML_FILE_NOT_FOUND  ";		break;
	case ACCOUNT_ERROR_EVENT_SUBSCRIPTION_FAIL:		pszErrInfo = "ACCOUNT_ERROR_EVENT_SUBSCRIPTION_FAIL  ";	break;
	case ACCOUNT_ERROR_NOT_REGISTERED_PROVIDER:		pszErrInfo = "ACCOUNT_ERROR_NOT_REGISTERED_PROVIDER ";	break;
	case ACCOUNT_ERROR_NOT_ALLOW_MULTIPLE:			pszErrInfo = "ACCOUNT_ERROR_NOT_ALLOW_MULTIPLE ";		break;
	case ACCOUNT_ERROR_DATABASE_BUSY:				pszErrInfo = "ACCOUNT_ERROR_DATABASE_BUSY  ";			break;
	default:										pszErrInfo = "UNKNOWN ERROR";
	}

	return pszErrInfo;
}

/**
* @function 			BadgePrintErrorCode
* @description 			Display the details error information
* @parameter	[IN] 	nResult (return value of badge api)
* @return 				NA
*/
char* BadgePrintErrorCode(int nResult)
{
	char* pszEnum = NULL;
	switch ( nResult )
	{
	case BADGE_ERROR_NONE:					pszEnum = "BADGE_ERROR_NONE";					break;
	case BADGE_ERROR_INVALID_PARAMETER:		pszEnum = "BADGE_ERROR_INVALID_PARAMETER";		break;
	case BADGE_ERROR_OUT_OF_MEMORY:			pszEnum = "BADGE_ERROR_OUT_OF_MEMORY";			break;
	case BADGE_ERROR_PERMISSION_DENIED:		pszEnum = "BADGE_ERROR_PERMISSION_DENIED";		break;
	case BADGE_ERROR_IO_ERROR:				pszEnum = "BADGE_ERROR_IO_ERROR ";				break;
	case BADGE_ERROR_FROM_DB:				pszEnum = "BADGE_ERROR_FROM_DB";				break;
	case BADGE_ERROR_ALREADY_EXIST:			pszEnum = "BADGE_ERROR_ALREADY_EXIST";			break;
	case BADGE_ERROR_FROM_DBUS:				pszEnum = "BADGE_ERROR_FROM_DBUS";				break;
	case BADGE_ERROR_NOT_EXIST:				pszEnum = "BADGE_ERROR_NOT_EXIST";				break;
	case BADGE_ERROR_SERVICE_NOT_READY:		pszEnum = "BADGE_ERROR_SERVICE_NOT_READY";		break;
	default:								pszEnum = "UNKNOWN ERROR";
	}

	return pszEnum;
}
/**
* @function				MediaContentPrintErrorInfo
* @description 			Print the error information for Media Content.
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* MediaContentPrintErrorInfo(int nResult)
{
	char *pszErrorMsg = NULL;
	switch ( nResult )
	{
	case MEDIA_CONTENT_ERROR_NONE:					pszErrorMsg = "MEDIA_CONTENT_ERROR_NONE";					break;
	case MEDIA_CONTENT_ERROR_INVALID_PARAMETER:		pszErrorMsg = "MEDIA_CONTENT_ERROR_INVALID_PARAMETER";		break;
	case MEDIA_CONTENT_ERROR_OUT_OF_MEMORY:			pszErrorMsg = "MEDIA_CONTENT_ERROR_OUT_OF_MEMORY";			break;
	case MEDIA_CONTENT_ERROR_INVALID_OPERATION:		pszErrorMsg = "MEDIA_CONTENT_ERROR_INVALID_OPERATION";		break;
	case MEDIA_CONTENT_FILE_NO_SPACE_ON_DEVICE:		pszErrorMsg = "MEDIA_CONTENT_FILE_NO_SPACE_ON_DEVICE";		break;
	case MEDIA_CONTENT_ERROR_PERMISSION_DENIED:		pszErrorMsg = "MEDIA_CONTENT_ERROR_PERMISSION_DENIED";		break;
	case MEDIA_CONTENT_ERROR_DB_FAILED:				pszErrorMsg = "MEDIA_CONTENT_ERROR_DB_FAILED";				break;
	case MEDIA_CONTENT_ERROR_DB_BUSY:				pszErrorMsg = "MEDIA_CONTENT_ERROR_DB_BUSY";				break;
	case MEDIA_CONTENT_ERROR_NETWORK:				pszErrorMsg = "MEDIA_CONTENT_ERROR_NETWORK";				break;
	case MEDIA_CONTENT_ERROR_UNSUPPORTED_CONTENT:	pszErrorMsg = "MEDIA_CONTENT_ERROR_UNSUPPORTED_CONTENT";	break;
	default:										pszErrorMsg = "UKNOWN ERROR";
	}

	return pszErrorMsg;
}

#ifdef MOBILE
/**
* @function				WifiDirectPrintErrorInfo
* @description 			Print the error information for Wifi direct.
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* WifiDirectPrintErrorInfo(int nResult)
{
	char *pszErrorMsg = NULL;
	switch ( nResult )
	{
	case WIFI_DIRECT_ERROR_NONE:					pszErrorMsg = "WIFI_DIRECT_ERROR_NONE";					break;
	case WIFI_DIRECT_ERROR_NOT_PERMITTED:			pszErrorMsg = "WIFI_DIRECT_ERROR_NOT_PERMITTED";		break;
	case WIFI_DIRECT_ERROR_OUT_OF_MEMORY:			pszErrorMsg = "WIFI_DIRECT_ERROR_OUT_OF_MEMORY";		break;
	case WIFI_DIRECT_ERROR_PERMISSION_DENIED:		pszErrorMsg = "WIFI_DIRECT_ERROR_PERMISSION_DENIED";	break;
	case WIFI_DIRECT_ERROR_RESOURCE_BUSY:			pszErrorMsg = "WIFI_DIRECT_ERROR_RESOURCE_BUSY";		break;
	case WIFI_DIRECT_ERROR_INVALID_PARAMETER:		pszErrorMsg = "WIFI_DIRECT_ERROR_INVALID_PARAMETER";	break;
	case WIFI_DIRECT_ERROR_CONNECTION_TIME_OUT:		pszErrorMsg = "WIFI_DIRECT_ERROR_CONNECTION_TIME_OUT";	break;
	case WIFI_DIRECT_ERROR_NOT_SUPPORTED:			pszErrorMsg = "WIFI_DIRECT_ERROR_NOT_SUPPORTED";		break;
	case WIFI_DIRECT_ERROR_NOT_INITIALIZED:			pszErrorMsg = "WIFI_DIRECT_ERROR_NOT_INITIALIZED";		break;
	case WIFI_DIRECT_ERROR_COMMUNICATION_FAILED:	pszErrorMsg = "WIFI_DIRECT_ERROR_COMMUNICATION_FAILED";	break;
	case WIFI_DIRECT_ERROR_WIFI_USED:				pszErrorMsg = "WIFI_DIRECT_ERROR_WIFI_USED";			break;
	case WIFI_DIRECT_ERROR_MOBILE_AP_USED:			pszErrorMsg = "WIFI_DIRECT_ERROR_MOBILE_AP_USED";		break;
	case WIFI_DIRECT_ERROR_CONNECTION_FAILED:		pszErrorMsg = "WIFI_DIRECT_ERROR_CONNECTION_FAILED";	break;
	case WIFI_DIRECT_ERROR_AUTH_FAILED:				pszErrorMsg = "WIFI_DIRECT_ERROR_AUTH_FAILED";			break;
	case WIFI_DIRECT_ERROR_OPERATION_FAILED:		pszErrorMsg = "WIFI_DIRECT_ERROR_OPERATION_FAILED";		break;
	case WIFI_DIRECT_ERROR_TOO_MANY_CLIENT:			pszErrorMsg = "WIFI_DIRECT_ERROR_TOO_MANY_CLIENT";		break;
	case WIFI_DIRECT_ERROR_ALREADY_INITIALIZED:		pszErrorMsg = "WIFI_DIRECT_ERROR_ALREADY_INITIALIZED";	break;
	case WIFI_DIRECT_ERROR_CONNECTION_CANCELED:		pszErrorMsg = "WIFI_DIRECT_ERROR_CONNECTION_CANCELED";	break;
	default:										pszErrorMsg = "UKNOWN ERROR";
	}

	return pszErrorMsg;
}

/**
* @function				ShortcutPrintErrorCode
* @description 			Print the error information for Shortcut.
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* ShortcutPrintErrorCode(int nResult)
{
	char* pszEnum = NULL;
	switch ( nResult )
	{
	case SHORTCUT_ERROR_NONE:					pszEnum = "SHORTCUT_ERROR_NONE";				break;
	case SHORTCUT_ERROR_NO_SPACE:				pszEnum = "SHORTCUT_ERROR_NO_SPACE";			break;
	case SHORTCUT_ERROR_EXIST:					pszEnum = "SHORTCUT_ERROR_EXIST";				break;
	case SHORTCUT_ERROR_FAULT:					pszEnum = "SHORTCUT_ERROR_FAULT";				break;
	case SHORTCUT_ERROR_INVALID_PARAMETER:		pszEnum = "SHORTCUT_ERROR_INVALID_PARAMETER";	break;
	case SHORTCUT_ERROR_COMM:					pszEnum = "SHORTCUT_ERROR_COMM";				break;
	case SHORTCUT_ERROR_OUT_OF_MEMORY:			pszEnum = "SHORTCUT_ERROR_OUT_OF_MEMORY";		break;
	case SHORTCUT_ERROR_IO_ERROR:				pszEnum = "SHORTCUT_ERROR_IO_ERROR";			break;
	case SHORTCUT_ERROR_PERMISSION_DENIED:		pszEnum = "SHORTCUT_ERROR_PERMISSION_DENIED";	break;
	default:									pszEnum = "UNKNOWN ERROR";
	}

	return pszEnum;
}
#endif

/**
* @function				NfcPrintErrorInfo
* @description 			Print the error information for NFC
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* NfcPrintErrorInfo(int nResult)
{
	char *pszErrLog = NULL;
	switch ( nResult )
	{
	case NFC_ERROR_NONE:						pszErrLog = "NFC_ERROR_NONE";						break;
	case NFC_ERROR_OUT_OF_MEMORY:				pszErrLog = "NFC_ERROR_OUT_OF_MEMORY";			break;
	case NFC_ERROR_OPERATION_FAILED:			pszErrLog = "NFC_ERROR_OPERATION_FAILED";			break;
	case NFC_ERROR_INVALID_PARAMETER:			pszErrLog = "NFC_ERROR_INVALID_PARAMETER";		break;
	case NFC_ERROR_INVALID_NDEF_MESSAGE:		pszErrLog =  "NFC_ERROR_INVALID_NDEF_MESSAGE";	break;
	case NFC_ERROR_INVALID_RECORD_TYPE:			pszErrLog = "NFC_ERROR_INVALID_RECORD_TYPE";		break;
	case NFC_ERROR_TIMED_OUT:					pszErrLog = "NFC_ERROR_TIMED_OUT";				break;
	case NFC_ERROR_DEVICE_BUSY:					pszErrLog = "NFC_ERROR_DEVICE_BUSY";				break;
	case NFC_ERROR_NO_DEVICE:					pszErrLog =  "NFC_ERROR_NO_DEVICE";				break;
	case NFC_ERROR_NOT_ACTIVATED:				pszErrLog = "NFC_ERROR_NOT_ACTIVATED";			break;
	case NFC_ERROR_NOT_SUPPORTED:				pszErrLog = "NFC_ERROR_NOT_SUPPORTED";			break;
	case NFC_ERROR_ALREADY_ACTIVATED:			pszErrLog = "NFC_ERROR_ALREADY_ACTIVATED";		break;
	case NFC_ERROR_ALREADY_DEACTIVATED:			pszErrLog =  "NFC_ERROR_ALREADY_DEACTIVATED";		break;
	case NFC_ERROR_READ_ONLY_NDEF:				pszErrLog = "NFC_ERROR_READ_ONLY_NDEF";			break;
	case NFC_ERROR_NO_SPACE_ON_NDEF:			pszErrLog = "NFC_ERROR_NO_SPACE_ON_NDEF";			break;
	case NFC_ERROR_NO_NDEF_MESSAGE:				pszErrLog = "NFC_ERROR_NO_NDEF_MESSAGE";			break;
	case NFC_ERROR_NOT_NDEF_FORMAT:				pszErrLog =  "NFC_ERROR_NOT_NDEF_FORMAT";			break;
	case NFC_ERROR_SECURITY_RESTRICTED:			pszErrLog = "NFC_ERROR_SECURITY_RESTRICTED";		break;
	case NFC_ERROR_ILLEGAL_STATE:				pszErrLog = "NFC_ERROR_ILLEGAL_STATE";			break;
	case NFC_ERROR_NOT_INITIALIZED:				pszErrLog = "NFC_ERROR_NOT_INITIALIZED";			break;
	case NFC_ERROR_TAG_NOT_SUPPORTED:			pszErrLog =  "NFC_ERROR_TAG_NOT_SUPPORTED";		break;
	default:									pszErrLog =  "UNKNOWN ERROR";
	}

	return pszErrLog;
}

/**
* @function				StoragePrintErrorInfo
* @description 			Print the error information for storage
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* StoragePrintErrorInfo(int nResult)
{
	char *pszErrLog = NULL;
	switch ( nResult )
	{
	case STORAGE_ERROR_NONE:					pszErrLog = "STORAGE_ERROR_NONE";				break;
	case STORAGE_ERROR_INVALID_PARAMETER:		pszErrLog = "STORAGE_ERROR_INVALID_PARAMETER";			break;
	case STORAGE_ERROR_OUT_OF_MEMORY:			pszErrLog = "STORAGE_ERROR_OUT_OF_MEMORY";		break;
	case STORAGE_ERROR_NOT_SUPPORTED:			pszErrLog = "STORAGE_ERROR_NOT_SUPPORTED";		break;
	case STORAGE_ERROR_OPERATION_FAILED:		pszErrLog = "STORAGE_ERROR_OPERATION_FAILED";	break;
	default:									pszErrLog =  "UNKNOWN ERROR";
	}
	return pszErrLog;
}

#ifdef MOBILE		//Starts MOBILE

/**
* @function 			EmailPrintErrorInfo
* @description 			Print the error of Email Error information
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/
char* EmailPrintErrorInfo(int nResult)
{
	char *pszErrLog = NULL;
	switch ( nResult )
	{
	case EMAILS_ERROR_NONE:									pszErrLog = "EMAILS_ERROR_NONE";								break;
	case EMAILS_ERROR_OUT_OF_MEMORY:						pszErrLog = "EMAILS_ERROR_OUT_OF_MEMORY";						break;
	case EMAILS_ERROR_INVALID_PARAMETER:					pszErrLog = "EMAILS_ERROR_INVALID_PARAMETER";					break;
	case EMAILS_ERROR_SERVER_NOT_READY:						pszErrLog = "EMAILS_ERROR_SERVER_NOT_READY";					break;
	case EMAILS_ERROR_COMMUNICATION_WITH_SERVER_FAILED:		pszErrLog = "EMAILS_ERROR_COMMUNICATION_WITH_SERVER_FAILED";	break;
	case EMAILS_ERROR_ACCOUNT_NOT_FOUND:					pszErrLog = "EMAILS_ERROR_ACCOUNT_NOT_FOUND";					break;
	case EMAILS_ERROR_OPERATION_FAILED:						pszErrLog = "EMAILS_ERROR_OPERATION_FAILED";					break;
	case EMAILS_ERROR_DB_FAILED:							pszErrLog = "EMAILS_ERROR_DB_FAILED";							break;
	default:												pszErrLog =  "UNKNOWN ERROR";
	}

	return pszErrLog;
}
#endif  //MOBILE	//End MOBILE

#ifdef WEARABLE	//Starts WEARABLE
/**
* @function 			EmailPrintErrorInfo
* @description 			Print the error of Email Error information
* @parameter	[IN]	nResult, the error code
* @return 				NA
*/

#if 0
char* EmailPrintErrorInfo(int nResult)
{
	char *pszErrLog = NULL;
	switch ( nResult )
	{
	case EMAILS_ERROR_NONE:									pszErrLog = "EMAILS_ERROR_NONE";								break;
	case EMAILS_ERROR_OUT_OF_MEMORY:						pszErrLog = "EMAILS_ERROR_OUT_OF_MEMORY";						break;
	case EMAILS_ERROR_INVALID_PARAMETER:					pszErrLog = "EMAILS_ERROR_INVALID_PARAMETER";					break;
	case EMAILS_ERROR_SERVER_NOT_READY:						pszErrLog = "EMAILS_ERROR_SERVER_NOT_READY";					break;
	case EMAILS_ERROR_COMMUNICATION_WITH_SERVER_FAILED:		pszErrLog = "EMAILS_ERROR_COMMUNICATION_WITH_SERVER_FAILED";	break;
	case EMAILS_ERROR_ACCOUNT_NOT_FOUND:					pszErrLog = "EMAILS_ERROR_ACCOUNT_NOT_FOUND";					break;
	case EMAILS_ERROR_OPERATION_FAILED:						pszErrLog = "EMAILS_ERROR_OPERATION_FAILED";					break;
	case EMAILS_ERROR_DB_FAILED:							pszErrLog = "EMAILS_ERROR_DB_FAILED";							break;
	default:												pszErrLog =  "UNKNOWN ERROR";
	}

	return pszErrLog;
}
#endif
#endif  //WEARABLE	//End WEARABLE

/**
* @function 			TelServicePrintAPIErrorMSG
* @description	 		Display the details error information
* @parameter	[IN] 	nError	[the error code which has to be converted to string]
* @return 				NA
*/
char* TelServicePrintAPIErrorMSG(int nError)
{
	char* pszException = NULL;
	switch(nError)
	{
	case TELEPHONY_ERROR_NONE:	 				pszException = "TELEPHONY_ERROR_NONE";					break;
	case TELEPHONY_ERROR_OUT_OF_MEMORY:			pszException = "TELEPHONY_ERROR_OUT_OF_MEMORY";			break;
	case TELEPHONY_ERROR_INVALID_PARAMETER:		pszException = "TELEPHONY_ERROR_INVALID_PARAMETER";		break;
	case TELEPHONY_ERROR_PERMISSION_DENIED:		pszException = "TELEPHONY_ERROR_PERMISSION_DENIED";		break;
	case TELEPHONY_ERROR_OPERATION_FAILED:		pszException = "TELEPHONY_ERROR_OPERATION_FAILED";		break;
	case TELEPHONY_ERROR_SIM_NOT_AVAILABLE:		pszException = "TELEPHONY_ERROR_SIM_NOT_AVAILABLE";		break;
	default:									pszException = "UNKNOWN ERROR";
	}

	return pszException;
}

#ifdef MOBILE	//Starts MOBILE
/**
* @function 			ContactsPrintErrorCode
* @description 			Display the details error information
* @parameter	[IN] 	nResult, API return value code
* @return 				NA
*/
char* ContactsPrintErrorCode( int nResult)
{
	char* pszErrInfo = NULL;
	switch ( nResult )
	{
	case CONTACTS_ERROR_NONE:				pszErrInfo = "CONTACTS_ERROR_NONE";					break;
	case CONTACTS_ERROR_OUT_OF_MEMORY:		pszErrInfo = "CONTACTS_ERROR_OUT_OF_MEMORY";		break;
	case CONTACTS_ERROR_INVALID_PARAMETER:	pszErrInfo = "CONTACTS_ERROR_INVALID_PARAMETER";	break;
	case CONTACTS_ERROR_FILE_NO_SPACE:		pszErrInfo = "CONTACTS_ERROR_FILE_NO_SPACE";		break;
	case CONTACTS_ERROR_NO_DATA:			pszErrInfo = "CONTACTS_ERROR_NO_DATA";				break;
	case CONTACTS_ERROR_PERMISSION_DENIED:	pszErrInfo = "CONTACTS_ERROR_PERMISSION_DENIED";	break;
	case CONTACTS_ERROR_DB_LOCKED:			pszErrInfo = "CONTACTS_ERROR_DB_LOCKED ";			break;
	case CONTACTS_ERROR_DB:					pszErrInfo = "CONTACTS_ERROR_DB ";					break;
	case CONTACTS_ERROR_IPC_NOT_AVALIABLE:	pszErrInfo = "CONTACTS_ERROR_IPC_NOT_AVALIABLE";	break;
	case CONTACTS_ERROR_IPC:				pszErrInfo = "CONTACTS_ERROR_IPC";					break;
	case CONTACTS_ERROR_INTERNAL:			pszErrInfo = "CONTACTS_ERROR_INTERNAL";				break;
	default:								pszErrInfo = "UNKNOWN ERROR";
	}

	return pszErrInfo;
}
#endif  //MOBILE	//End MOBILE

/**
 * @function 		SmartcardGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
char* SmartcardGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case SMARTCARD_ERROR_NONE:						szErrorVal = "SMARTCARD_ERROR_NONE";				break;
		case SMARTCARD_ERROR_GENERAL:					szErrorVal = "SMARTCARD_ERROR_GENERAL";				break;
		case SMARTCARD_ERROR_IO_ERROR:					szErrorVal = "SMARTCARD_ERROR_IO_ERROR";			break;
		case SMARTCARD_ERROR_NO_SUCH_ELEMENT:			szErrorVal = "SMARTCARD_ERROR_NO_SUCH_ELEMENT";		break;
		case SMARTCARD_ERROR_ILLEGAL_STATE:				szErrorVal = "SMARTCARD_ERROR_ILLEGAL_STATE";		break;
		case SMARTCARD_ERROR_INVALID_PARAMETER:			szErrorVal = "SMARTCARD_ERROR_INVALID_PARAMETER";	break;
		case SMARTCARD_ERROR_ILLEGAL_REFERENCE:			szErrorVal = "SMARTCARD_ERROR_ILLEGAL_REFERENCE";	break;
		case SMARTCARD_ERROR_OPERATION_NOT_SUPPORTED:	szErrorVal = "SMARTCARD_ERROR_OPERATION_NOT_SUPPORTED";break;
		case SMARTCARD_ERROR_PERMISSION_DENIED:			szErrorVal = "SMARTCARD_ERROR_PERMISSION_DENIED";	break;
		case SMARTCARD_ERROR_CHANNEL_NOT_AVAILABLE:		szErrorVal = "SMARTCARD_ERROR_CHANNEL_NOT_AVAILABLE";break;
		case SMARTCARD_ERROR_NOT_INITIALIZED:			szErrorVal = "SMARTCARD_ERROR_NOT_INITIALIZED";		break;
		case SMARTCARD_ERROR_NOT_SUPPORTED:				szErrorVal = "SMARTCARD_ERROR_NOT_SUPPORTED";		break;
		default:										szErrorVal = "Unknown Error";						break;
	}

	return szErrorVal;
}
/**
 * @function 		SmartcardGetErrorCode
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
char* SmartcardGetErrorCode(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case SMARTCARD_ERROR_NONE:						szErrorVal = "SMARTCARD_ERROR_NONE";				break;
		case SMARTCARD_ERROR_GENERAL:					szErrorVal = "SMARTCARD_ERROR_GENERAL";				break;
		case SMARTCARD_ERROR_IO_ERROR:					szErrorVal = "SMARTCARD_ERROR_IO_ERROR";			break;
		case SMARTCARD_ERROR_NO_SUCH_ELEMENT:			szErrorVal = "SMARTCARD_ERROR_NO_SUCH_ELEMENT";		break;
		case SMARTCARD_ERROR_ILLEGAL_STATE:				szErrorVal = "SMARTCARD_ERROR_ILLEGAL_STATE";		break;
		case SMARTCARD_ERROR_INVALID_PARAMETER:			szErrorVal = "SMARTCARD_ERROR_INVALID_PARAMETER";	break;
		case SMARTCARD_ERROR_ILLEGAL_REFERENCE:			szErrorVal = "SMARTCARD_ERROR_ILLEGAL_REFERENCE";	break;
		case SMARTCARD_ERROR_OPERATION_NOT_SUPPORTED:	szErrorVal = "SMARTCARD_ERROR_OPERATION_NOT_SUPPORTED";break;
		case SMARTCARD_ERROR_PERMISSION_DENIED:			szErrorVal = "SMARTCARD_ERROR_PERMISSION_DENIED";	break;
		case SMARTCARD_ERROR_CHANNEL_NOT_AVAILABLE:		szErrorVal = "SMARTCARD_ERROR_CHANNEL_NOT_AVAILABLE";break;
		case SMARTCARD_ERROR_NOT_INITIALIZED:			szErrorVal = "SMARTCARD_ERROR_NOT_INITIALIZED";		break;
		case SMARTCARD_ERROR_NOT_SUPPORTED:				szErrorVal = "SMARTCARD_ERROR_NOT_SUPPORTED";		break;
		default:										szErrorVal = "Unknown Error";						break;
	}

	return szErrorVal;
}

/**
* @function 		AppManagerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* AppManagerGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case APP_MANAGER_ERROR_NONE:					szErrorVal = "APP_MANAGER_ERROR_NONE";						break;
	case APP_MANAGER_ERROR_INVALID_PARAMETER:		szErrorVal = "APP_MANAGER_ERROR_INVALID_PARAMETE";			break;
	case APP_MANAGER_ERROR_OUT_OF_MEMORY:			szErrorVal = "APP_MANAGER_ERROR_OUT_OF_MEMORY";				break;
	case APP_MANAGER_ERROR_IO_ERROR:				szErrorVal = "APP_MANAGER_ERROR_IO_ERROR";					break;
	case APP_MANAGER_ERROR_NO_SUCH_APP:				szErrorVal = "APP_MANAGER_ERROR_NO_SUCH_APP";				break;
	case APP_MANAGER_ERROR_DB_FAILED:				szErrorVal = "APP_MANAGER_ERROR_DB_FAILED";					break;
	case APP_MANAGER_ERROR_INVALID_PACKAGE:			szErrorVal = "APP_MANAGER_ERROR_INVALID_PACKAGE";			break;
	case APP_MANAGER_ERROR_APP_NO_RUNNING:			szErrorVal = "APP_MANAGER_ERROR_APP_NO_RUNNING";			break;
	case APP_MANAGER_ERROR_REQUEST_FAILED:			szErrorVal = "APP_MANAGER_ERROR_REQUEST_FAILED";			break;
	case APP_MANAGER_ERROR_PERMISSION_DENIED:		szErrorVal = "APP_MANAGER_ERROR_PERMISSION_DENIED";			break;
	default:										szErrorVal = "Unknown Error";								break;
	}

	return szErrorVal;
}

/**
* @function 		MapServiceGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* MapServiceGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case MAPS_ERROR_NONE:					szErrorVal = "MAPS_ERROR_NONE";						break;
		case MAPS_ERROR_PERMISSION_DENIED:   	szErrorVal = "MAPS_ERROR_PERMISSION_DENIED";		break;
		case MAPS_ERROR_OUT_OF_MEMORY:       	szErrorVal = "MAPS_ERROR_OUT_OF_MEMORY";			break;
		case MAPS_ERROR_INVALID_PARAMETER:   	szErrorVal = "MAPS_ERROR_INVALID_PARAMETER";		break;
		case MAPS_ERROR_NOT_SUPPORTED:       	szErrorVal = "MAPS_ERROR_NOT_SUPPORTED";			break;
		case MAPS_ERROR_CONNECTION_TIME_OUT: 	szErrorVal = "MAPS_ERROR_CONNECTION_TIME_OUT";		break;
		case MAPS_ERROR_NETWORK_UNREACHABLE: 	szErrorVal = "MAPS_ERROR_NETWORK_UNREACHABLE";		break;
		case MAPS_ERROR_INVALID_OPERATION:   	szErrorVal = "MAPS_ERROR_INVALID_OPERATION";		break;
		case MAPS_ERROR_KEY_NOT_AVAILABLE:   	szErrorVal = "MAPS_ERROR_KEY_NOT_AVAILABLE";		break;
		case MAPS_ERROR_RESOURCE_BUSY:	    	szErrorVal = "MAPS_ERROR_RESOURCE_BUSY";			break;
		case MAPS_ERROR_CANCELED:            	szErrorVal = "MAPS_ERROR_CANCELED";					break;
		case MAPS_ERROR_UNKNOWN:				szErrorVal = "MAPS_ERROR_UNKNOWN";					break;
		case MAPS_ERROR_SERVICE_NOT_AVAILABLE:	szErrorVal = "MAPS_ERROR_SERVICE_NOT_AVAILABLE";	break;
		case MAPS_ERROR_NOT_FOUND:           	szErrorVal = "MAPS_ERROR_NOT_FOUND";				break;
		default : 					           	szErrorVal = "Unknown Error";						break;
	}
	return szErrorVal;
}

/**
* @function 		MediaControllerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* MediaControllerGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch(nRet)
	{
		case MEDIA_CONTROLLER_ERROR_NONE:						szErrorVal = "MEDIA_CONTROLLER_ERROR_NONE";						break;
		case MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER:			szErrorVal = "MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER";		break;
		case MEDIA_CONTROLLER_ERROR_OUT_OF_MEMORY:				szErrorVal = "MEDIA_CONTROLLER_ERROR_OUT_OF_MEMORY";			break;
		case MEDIA_CONTROLLER_ERROR_INVALID_OPERATION:			szErrorVal = "MEDIA_CONTROLLER_ERROR_INVALID_OPERATION";		break;
		case MEDIA_CONTROLLER_ERROR_FILE_NO_SPACE_ON_DEVICE:	szErrorVal = "MEDIA_CONTROLLER_ERROR_FILE_NO_SPACE_ON_DEVICE";	break;
		case MEDIA_CONTROLLER_ERROR_PERMISSION_DENIED:			szErrorVal = "MEDIA_CONTROLLER_ERROR_PERMISSION_DENIED";		break;
		default: 												szErrorVal = "MEDIA_CONTROLLER_ERROR_UNKNOWN";					break;
	}
	return szErrorVal;
}

/**
 * @function 		WidgetServiceGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet: error code returned
 * @return 			error string
 */
char* WidgetServiceGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch(nRet)
	{
		case WIDGET_ERROR_NONE:				szErrorVal="WIDGET_ERROR_NONE";					break;
		case WIDGET_ERROR_INVALID_PARAMETER:		szErrorVal = "WIDGET_ERROR_INVALID_PARAMETER";			break;
		case WIDGET_ERROR_OUT_OF_MEMORY:			szErrorVal = "WIDGET_ERROR_OUT_OF_MEMORY";				break;
		case WIDGET_ERROR_RESOURCE_BUSY:			szErrorVal = "WIDGET_ERROR_RESOURCE_BUSY";				break;
		case WIDGET_ERROR_PERMISSION_DENIED:		szErrorVal = "WIDGET_ERROR_PERMISSION_DENIED";			break;
		case WIDGET_ERROR_CANCELED:					szErrorVal = "WIDGET_ERROR_CANCELED";					break;
		case WIDGET_ERROR_IO_ERROR:					szErrorVal = "WIDGET_ERROR_IO_ERROR";					break;
		case WIDGET_ERROR_TIMED_OUT:				szErrorVal = "WIDGET_ERROR_TIMED_OUT";					break;
		case WIDGET_ERROR_NOT_SUPPORTED:			szErrorVal = "WIDGET_ERROR_NOT_SUPPORTED";				break;
		case WIDGET_ERROR_FILE_NO_SPACE_ON_DEVICE:	szErrorVal = "WIDGET_ERROR_FILE_NO_SPACE_ON_DEVICE";	break;
		case WIDGET_ERROR_FAULT:					szErrorVal = "WIDGET_ERROR_FAULT";						break;
		case WIDGET_ERROR_ALREADY_EXIST:			szErrorVal = "WIDGET_ERROR_ALREADY_EXIST";				break;
		case WIDGET_ERROR_ALREADY_STARTED:			szErrorVal = "WIDGET_ERROR_ALREADY_STARTED";			break;
		case WIDGET_ERROR_NOT_EXIST:				szErrorVal = "WIDGET_ERROR_NOT_EXIST";					break;
		case WIDGET_ERROR_DISABLED:					szErrorVal = "WIDGET_ERROR_DISABLED";					break;
		default:									szErrorVal = "Unknown Error";							break;
	}
	return szErrorVal;
}


#ifdef MOBILE
/**
* @function 		MinicontrolGetError
* @description	 	Maps minicontrol_error_e enums to string values
* @parameter		nRet : error code returned
* @return 			minicontrol error string
*/
char* MinicontrolGetError(minicontrol_error_e nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case MINICONTROL_ERROR_NONE:					szErrorVal = "MINICONTROL_ERROR_NONE";					break;
	case MINICONTROL_ERROR_INVALID_PARAMETER:		szErrorVal = "MINICONTROL_ERROR_INVALID_PARAMETER";		break;
	case MINICONTROL_ERROR_OUT_OF_MEMORY:			szErrorVal = "MINICONTROL_ERROR_OUT_OF_MEMORY";			break;
	case MINICONTROL_ERROR_PERMISSION_DENIED:		szErrorVal = "MINICONTROL_ERROR_PERMISSION_DENIED";		break;
	case MINICONTROL_ERROR_IPC_FAILURE:				szErrorVal = "MINICONTROL_ERROR_IPC_FAILURE";			break;
	case MINICONTROL_ERROR_NOT_SUPPORTED: 			szErrorVal = "MINICONTROL_ERROR_NOT_SUPPORTED"; 			break;
	case MINICONTROL_ERROR_ELM_FAILURE: 			szErrorVal = "MINICONTROL_ERROR_ELM_FAILURE" ;			break;
	case MINICONTROL_ERROR_UNKNOWN:					szErrorVal = "MINICONTROL_ERROR_UNKNOWN"; 				break;
	default:										szErrorVal = "Unknown Error";							break;
	}
	return szErrorVal;
}
#endif

/**
* @function 		EflUtilGetError
* @description	 	Maps error enumerators to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* EflUtilGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch(nRet)
	{
	case EFL_UTIL_ERROR_NONE : 								szErrorVal = " EFL_UTIL_ERROR_NONE " ; 						break;
	case EFL_UTIL_ERROR_INVALID_PARAMETER : 				szErrorVal = " EFL_UTIL_ERROR_INVALID_PARAMETER " ; 		break;
	case EFL_UTIL_ERROR_NOT_SUPPORTED_WINDOW_TYPE : 		szErrorVal = " EFL_UTIL_ERROR_NOT_SUPPORTED_WINDOW_TYPE " ; break;
	default:											szErrorVal = "Unknown Error";								break;
	}

	return szErrorVal;
}

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
* @function 		PackageManagerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* PackageManagerGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case PACKAGE_MANAGER_ERROR_INVALID_PARAMETER:	szErrorVal = "PACKAGE_MANAGER_ERROR_INVALID_PARAMETER";		break;
	case PACKAGE_MANAGER_ERROR_OUT_OF_MEMORY:		szErrorVal = "PACKAGE_MANAGER_ERROR_OUT_OF_MEMORY";			break;
	case PACKAGE_MANAGER_ERROR_IO_ERROR:			szErrorVal = "PACKAGE_MANAGER_ERROR_IO_ERROR";				break;
	case PACKAGE_MANAGER_ERROR_NO_SUCH_PACKAGE:		szErrorVal = "PACKAGE_MANAGER_ERROR_NO_SUCH_PACKAGE";		break;
	default:										szErrorVal = "Unknown Error";								break;
	}
	return szErrorVal;
}

/**
* @function 		RuntimeInfoGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* RuntimeInfoGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch(nRet)
	{
	case RUNTIME_INFO_ERROR_NONE:					szErrorVal = "RUNTIME_INFO_ERROR_NONE";						break;
	case RUNTIME_INFO_ERROR_INVALID_PARAMETER:		szErrorVal = "RUNTIME_INFO_ERROR_INVALID_PARAMETER";		break;
	case RUNTIME_INFO_ERROR_OUT_OF_MEMORY:			szErrorVal = "RUNTIME_INFO_ERROR_OUT_OF_MEMORY";			break;
	case RUNTIME_INFO_ERROR_IO_ERROR:				szErrorVal = "RUNTIME_INFO_ERROR_IO_ERROR";					break;
	default:										szErrorVal = "Unknown Error";								break;
	}
	return szErrorVal;
}


/**
* @function			NFCGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return			error string
*/
char* NFCGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case NFC_ERROR_NONE:					szErrorVal = "NFC_ERROR_NONE";						break;
	case NFC_ERROR_OUT_OF_MEMORY:			szErrorVal = "NFC_ERROR_OUT_OF_MEMORY";				break;
	case NFC_ERROR_OPERATION_FAILED:		szErrorVal = "NFC_ERROR_OPERATION_FAILED";			break;
	case NFC_ERROR_INVALID_PARAMETER:		szErrorVal = "NFC_ERROR_INVALID_PARAMETER";			break;
	case NFC_ERROR_INVALID_NDEF_MESSAGE:	szErrorVal = "NFC_ERROR_INVALID_NDEF_MESSAGE";		break;
	case NFC_ERROR_INVALID_RECORD_TYPE:		szErrorVal = "NFC_ERROR_INVALID_RECORD_TYPE";		break;
	case NFC_ERROR_TIMED_OUT:				szErrorVal = "NFC_ERROR_TIMED_OUT";					break;
	case NFC_ERROR_DEVICE_BUSY:				szErrorVal = "NFC_ERROR_DEVICE_BUSY";				break;
	case NFC_ERROR_NO_DEVICE:				szErrorVal = "NFC_ERROR_NO_DEVICE";					break;
	case NFC_ERROR_NOT_ACTIVATED:			szErrorVal = "NFC_ERROR_NOT_ACTIVATED";				break;
	case NFC_ERROR_NOT_SUPPORTED:			szErrorVal = "NFC_ERROR_NOT_SUPPORTED";				break;
	case NFC_ERROR_ALREADY_ACTIVATED:		szErrorVal = "NFC_ERROR_ALREADY_ACTIVATED";			break;
	case NFC_ERROR_ALREADY_DEACTIVATED:		szErrorVal = "NFC_ERROR_ALREADY_DEACTIVATED";		break;
	case NFC_ERROR_READ_ONLY_NDEF:			szErrorVal = "NFC_ERROR_READ_ONLY_NDEF";			break;
	case NFC_ERROR_NO_SPACE_ON_NDEF:		szErrorVal = "NFC_ERROR_NO_SPACE_ON_NDEF";			break;
	case NFC_ERROR_NO_NDEF_MESSAGE:			szErrorVal = "NFC_ERROR_NO_NDEF_MESSAGE";			break;
	case NFC_ERROR_NOT_NDEF_FORMAT:			szErrorVal = "NFC_ERROR_NOT_NDEF_FORMAT";			break;
	case NFC_ERROR_SECURITY_RESTRICTED:		szErrorVal = "NFC_ERROR_SECURITY_RESTRICTED";		break;
	default:								szErrorVal = "Unknown Error";						break;
	}

	return szErrorVal;
}

#ifdef MOBILE      //Starts MOBILE
/**
 * @function		OAuth2GetError
 * @description		Maps error enums to string values
 * @parameter		nRet: error code returned
 * @return			error string
 */
char* Oauth2InfoGetError(int nRet)
{
    char *szErrorVal = NULL;

    switch ( nRet )
    {
    case OAUTH2_ERROR_NONE:						szErrorVal = "OAUTH2_ERROR_NONE";						break;
    case OAUTH2_ERROR_INVALID_PARAMETER:		szErrorVal = "OAUTH2_ERROR_INVALID_PARAMETER";			break;
    case OAUTH2_ERROR_ALREADY_IN_PROGRESS:		szErrorVal = "OAUTH2_ERROR_ALREADY_IN_PROGRESS";		break;
    case OAUTH2_ERROR_OUT_OF_MEMORY:			szErrorVal = "OAUTH2_ERROR_OUT_OF_MEMORY";				break;
    case OAUTH2_ERROR_NOT_SUPPORTED:			szErrorVal = "OAUTH2_ERROR_NOT_SUPPORTED";				break;
    case OAUTH2_ERROR_PERMISSION_DENIED:		szErrorVal = "OAUTH2_ERROR_PERMISSION_DENIED";			break;
    case OAUTH2_ERROR_PARSE_FAILED:				szErrorVal = "OAUTH2_ERROR_PARSE_FAILED";				break;
    case OAUTH2_ERROR_NETWORK_ERROR:			szErrorVal = "OAUTH2_ERROR_NETWORK_ERROR";				break;
    case OAUTH2_ERROR_SERVER:					szErrorVal = "OAUTH2_ERROR_SERVER";						break;
    case OAUTH2_ERROR_USER_CANCELLED:			szErrorVal = "OAUTH2_ERROR_USER_CANCELLED";				break;
    case OAUTH2_ERROR_VALUE_NOT_FOUND:			szErrorVal = "OAUTH2_ERROR_VALUE_NOT_FOUND";			break;
    default:									szErrorVal = "Unknown Error";							break;
    }

    return szErrorVal;
}
#endif  //MOBILE   //End MOBILE

/**
* @function 		SensorsGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* SensorsGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case SENSOR_ERROR_NONE: 					szErrorVal = "SENSOR_ERROR_NONE";						break;
	case SENSOR_ERROR_IO_ERROR: 				szErrorVal = "SENSOR_ERROR_IO_ERROR";					break;
	case SENSOR_ERROR_INVALID_PARAMETER: 		szErrorVal = "SENSOR_ERROR_INVALID_PARAMETER";			break;
	case SENSOR_ERROR_OUT_OF_MEMORY: 			szErrorVal = "SENSOR_ERROR_OUT_OF_MEMORY";				break;
	case SENSOR_ERROR_NOT_NEED_CALIBRATION: 	szErrorVal = "SENSOR_ERROR_NOT_NEED_CALIBRATION";		break;
	case SENSOR_ERROR_NOT_SUPPORTED: 			szErrorVal = "SENSOR_ERROR_NOT_SUPPORTED";				break;
	case SENSOR_ERROR_OPERATION_FAILED: 		szErrorVal = "SENSOR_ERROR_OPERATION_FAILED";			break;
	case SENSOR_ERROR_PERMISSION_DENIED: 		szErrorVal = "SENSOR_ERROR_PERMISSION_DENIED";			break;
	default : 									szErrorVal = "Unknown error";							break;
	}
	return szErrorVal;
}

/**
 * @function 		InputmethodManagerGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
char* InputmethodManagerGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case IME_MANAGER_ERROR_NONE:
			szErrorVal = "IME_MANAGER_ERROR_NONE";
			break;
		case IME_MANAGER_ERROR_INVALID_PARAMETER:
			szErrorVal = "IME_MANAGER_ERROR_INVALID_PARAMETER";
			break;
		case IME_MANAGER_ERROR_PERMISSION_DENIED:
			szErrorVal = "IME_MANAGER_ERROR_PERMISSION_DENIED";
			break;
		case IME_MANAGER_ERROR_OPERATION_FAILED:
			szErrorVal = "IME_MANAGER_ERROR_OPERATION_FAILED";
			break;
		default:
			szErrorVal = "Unknown Error";
			break;
	}

	return szErrorVal;
}

/**
 * @function 		InputmethodGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
char* InputmethodGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case IME_ERROR_NONE: 							szErrorVal = "IME_ERROR_NONE";						break;
		case IME_ERROR_INVALID_PARAMETER: 				szErrorVal = "IME_ERROR_INVALID_PARAMETER";			break;
		case IME_ERROR_PERMISSION_DENIED: 				szErrorVal = "IME_ERROR_PERMISSION_DENIED";			break;
		case IME_ERROR_NO_CALLBACK_FUNCTION: 			szErrorVal = "IME_ERROR_NO_CALLBACK_FUNCTION";		break;
		case IME_ERROR_NOT_RUNNING: 					szErrorVal = "IME_ERROR_NOT_RUNNING";				break;
		case IME_ERROR_OPERATION_FAILED: 				szErrorVal = "IME_ERROR_OPERATION_FAILED";			break;
	}

	return szErrorVal;
}

#ifdef MOBILE	//Starts MOBILE
/**
* @function 		ContextHistoryGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* ContextHistoryGetError(int nRet)
{
	char *pszErrorVal = NULL;
	switch ( nRet )
	{
		case CONTEXT_HISTORY_ERROR_NONE:
			pszErrorVal = "CONTEXT_HISTORY_ERROR_NONE";
			break;
		case CONTEXT_HISTORY_ERROR_INVALID_PARAMETER:
			pszErrorVal = "CONTEXT_HISTORY_ERROR_INVALID_PARAMETER";
			break;
		case CONTEXT_HISTORY_ERROR_PERMISSION_DENIED:
			pszErrorVal = "CONTEXT_HISTORY_ERROR_PERMISSION_DENIED";
			break;
		case CONTEXT_HISTORY_ERROR_NOT_SUPPORTED:
			pszErrorVal = "CONTEXT_HISTORY_ERROR_NOT_SUPPORTED";
			break;
		case CONTEXT_HISTORY_ERROR_OUT_OF_MEMORY:
			pszErrorVal = "CONTEXT_HISTORY_ERROR_OUT_OF_MEMORY";
			break;
		case CONTEXT_HISTORY_ERROR_NO_DATA:
			pszErrorVal = "CONTEXT_HISTORY_ERROR_NO_DATA";
			break;
		case CONTEXT_HISTORY_ERROR_OUT_OF_RANGE:
			pszErrorVal = "CONTEXT_HISTORY_ERROR_OUT_OF_RANGE";
			break;
		case CONTEXT_HISTORY_ERROR_OPERATION_FAILED:
			pszErrorVal = "CONTEXT_HISTORY_ERROR_OPERATION_FAILED";
			break;
		default:
			pszErrorVal = "Unknown Error";
			break;
	}

	return pszErrorVal;
}
#endif  //MOBILE	//End MOBILE

/**
* @function 		MediaContentConnect
* @description 		Connects to the media content service.
* @return 			Return true if it connects to the media content service successfully otherwise false
*/
bool MediaContentConnect()
{
	int nRet = MEDIA_CONTENT_ERROR_NONE;

	nRet = media_content_connect();
	if ( nRet != MEDIA_CONTENT_ERROR_NONE )
	{
		MediaContentPrintErrorInfo(nRet);
		return false;
	}
	return true;
}

/**
* @function 		MediaContentDisconnect
* @description 		Disconnects from the media content service.
* @return 			Return true if it disconnects from the media content service otherwise false
*/
bool MediaContentDisconnect()
{
	int nRet = MEDIA_CONTENT_ERROR_NONE;

	nRet = media_content_disconnect();
	if ( nRet != MEDIA_CONTENT_ERROR_NONE )
	{
		MediaContentPrintErrorInfo(nRet);
		return false;
	}
	return true;
}


/**
* @function 		TelServiceInitializeHandler
* @description	 	Create a handler(TapiHandle) for telephonyservice
* @parameter		NA
* @return 			true if telephony service initialize successfully otherwise false
*/
bool TelServiceInitializeHandler()
{
	int nRet = TELEPHONY_ERROR_NONE;

	nRet = telephony_init(&g_hTelephonyList);
	if ( nRet != TELEPHONY_ERROR_NONE )
	{
		TelServicePrintAPIErrorMSG(nRet);
		return false;
	}
	g_hTelephony = g_hTelephonyList.handle[0];
	return true;
}
/**
* @function 		TelServiceDeInitializeHandler
* @description	 	Deinitialize telephony handler
* @parameter		NA
* @return 			true if telephony service deinitialize successfully otherwise false
*/

bool TelServiceDeInitializeHandler()
{
	int nRet = TELEPHONY_ERROR_NONE;
	nRet = telephony_deinit(&g_hTelephonyList);
	if ( nRet != TELEPHONY_ERROR_NONE )
	{
		TelServicePrintAPIErrorMSG(nRet);
		return false;
	}
	g_hTelephony = NULL;
	return true;
}

/**
* @function 		PackageManagerDestroy
* @description		Clean and destroy resources
* @parameter		NA
* @return 			true [if no error occurs] or false [if error occurs]
*/
bool PackageManagerDestroy()
{
	int nRet = PACKAGE_MANAGER_ERROR_NONE;
	nRet = package_manager_destroy(g_hPackageManager);
	if ( nRet != PACKAGE_MANAGER_ERROR_NONE )
	{
		PackageManagerPrintErrorInfo(nRet);
		return false;
	}
	return true;
}

#ifdef MOBILE	//Starts MOBILE
/**
* @function 		ContactDisconnect
* @description 		Disconnects from the contacts service.
* @return 			Return true if Contact service is disconnected otherwise false
*/
bool ContactDisconnect()
{
	int nRet = CONTACTS_ERROR_NO_DATA;

	nRet = contacts_disconnect();
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		ContactsPrintErrorCode(nRet);
		return false;
	}
	return true;
}

/**
* @function 		ContactRecordDestroy
* @description 		Destroys a record and releases its all resources.
* @return 			Return true if it destroys a record and releases its all resources otherwise false
*/
bool ContactRecordDestroy()
{
	int nRet = CONTACTS_ERROR_NO_DATA;

	nRet = contacts_record_destroy(g_hContactRecord, true);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		ContactsPrintErrorCode(nRet);
		return false;
	}
	return true;
}

/**
* @function 		ContactConnect
* @description 		Connects to the contacts service.
* @return 			Return true if it connects to the contacts service successfully otherwise false
*/
bool ContactConnect()
{
	int nRet = CONTACTS_ERROR_NONE;

	nRet = contacts_connect();
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		ContactsPrintErrorCode(nRet);
		return false;
	}

	return true;
}

/**
* @function 		ContactRecordCreate
* @description 		Creates a record.
* @return 			Return true if it creates a record successfully otherwise false
*/
bool ContactRecordCreate()
{
	int nRet = CONTACTS_ERROR_NONE;
	g_hContactRecord = NULL;
	nRet = contacts_record_create(_contacts_contact._uri, &g_hContactRecord);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		ContactsPrintErrorCode(nRet);
		return false;
	}
	return true;
}
#endif  //MOBILE	//End MOBILE

/**
* @function 		AppControlCreate
* @description 		Create App control and sets the default operation
* @parameter		NA
* @return 			true or false
*/
bool AppControlCreate()
{
	int nRet = APP_CONTROL_ERROR_NONE;

	nRet = app_control_create(&g_hAppControl);
	if ( nRet != APP_CONTROL_ERROR_NONE )
	{
		AppControlPrintErrorInfo(nRet);
		return false;
	}

	nRet = app_control_set_operation(g_hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	if ( nRet != APP_CONTROL_ERROR_NONE )
	{
		AppControlPrintErrorInfo(nRet);
		AppControlDestroy();
		return false;
	}

	return true;
}

/**
* @function 		AppControlDestroy
* @description 		Destroys the app_control handle
* @parameter		NA
* @return 			Return true if handler is destroyed succesfully else false
*/
bool AppControlDestroy()
{
	int nRet = APP_CONTROL_ERROR_NONE;
	nRet = app_control_destroy (g_hAppControl);
	if ( nRet != APP_CONTROL_ERROR_NONE )
	{
		AppControlPrintErrorInfo(nRet);
		return false;
	}
	return true;
}

#ifdef MOBILE	//Starts MOBILE
/**
* @function 		ContextHistDestroy
* @description 		Destroys a record and releases its all resources.
* @return 			Return true if it destroys a record and releases its all resources otherwise false
*/
bool ContextHistDestroy()
{
	int nRet = context_history_filter_destroy(g_hContxtHistFilter);
	if ( nRet != CONTEXT_HISTORY_ERROR_NONE )
	{
		ContextHistoryGetError(nRet);
		context_history_destroy(g_hContxtHist);
		return false;
	}

	nRet = context_history_destroy(g_hContxtHist);
	if ( nRet != CONTEXT_HISTORY_ERROR_NONE )
	{
		ContextHistoryGetError(nRet);
		return false;
	}
	return true;
}
#endif  //MOBILE	//End MOBILE

#ifdef MOBILE	//Starts MOBILE
/**
* @function 		ContextHistCreate
* @description 		create a record
* @return 			Return true if it create a record otherwise false
*/
bool ContextHistCreate()
{
	int nRet = CONTEXT_HISTORY_ERROR_NONE;

	nRet = context_history_create(&g_hContxtHist);
	if ( nRet != CONTEXT_HISTORY_ERROR_NONE )
	{
		ContextHistoryGetError(nRet);
		return false;
	}

	nRet = context_history_filter_create(&g_hContxtHistFilter);
	if ( nRet != CONTEXT_HISTORY_ERROR_NONE )
	{
		ContextHistoryGetError(nRet);
		if(g_hContxtHist)
		{
			context_history_destroy(g_hContxtHist);
		}
		return false;
	}

	nRet = context_history_filter_set_int(g_hContxtHistFilter, CONTEXT_HISTORY_FILTER_TIME_SPAN,INT_VAL1);
	if ( nRet != APP_CONTROL_ERROR_NONE )
	{
		ContextHistoryGetError(nRet);
		ContextHistDestroy();
		return false;
	}
	nRet = context_history_filter_set_int(g_hContxtHistFilter, CONTEXT_HISTORY_FILTER_RESULT_SIZE,INT_VAL2);
	if ( nRet != APP_CONTROL_ERROR_NONE )
	{
		ContextHistoryGetError(nRet);
		ContextHistDestroy();
		return false;
	}

	return true;
}
#endif  //MOBILE	//End MOBILE

/**
* @function			EflUtilDeleteWindow
* @description		Callback function invoked while deleting ELM window
* @parameter[OUT]	pData [User data if any]
*					pstWindow [Pointer to EFL window]
*					pEvent [Type of Event]
* @return			NA
*/
void EflUtilDeleteWindow(void *pData, Evas_Object *pstWindow, void *pEvent)
{
	elm_exit();
}

/**
* @function			EflUtilCreateNotificationWindow
* @description		Creates a notification window
* @parameter[OUT]	pstWindow [Pointer to Evas_Object type to get a new window created]
* @return			NA
*/
bool EflUtilCreateNotificationWindow(Evas_Object **pstWindow)
{
	*pstWindow = elm_win_add(NULL, "Notification Window", ELM_WIN_NOTIFICATION);
	if (*pstWindow)
	{
		elm_win_title_set(*pstWindow, "Notification Window");
		elm_win_borderless_set(*pstWindow, EINA_TRUE);
		evas_object_smart_callback_add(*pstWindow, "Delete Request", EflUtilDeleteWindow, NULL);
		elm_win_indicator_mode_set(*pstWindow, ELM_WIN_INDICATOR_SHOW);
                evas_object_show(*pstWindow);
		return true;
	}
	else
	{
		return false;
	}
}

/**
* @function		IotconGetSvrDBPath
* @description		Gets path to initialize iotcon
* @parameter[OUT]	path
* @return		NA
*/
int IotconGetSvrDBPath(char **path)
{
        char file_path[PATH_MAX] = {0};
        char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
        const char *svr_db_file = "svr_db.dat";

        if (false == GetValueForTCTSetting("DEVICE_USER_30", pszValue, API_NAMESPACE)) {
                PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
                return -1;
        }

        PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_USER_30' Values Received = %s\\n",
                        __LINE__, API_NAMESPACE,  pszValue);

        snprintf(file_path, sizeof(file_path), "%s/apps_rw/native-iotcon-itc/data/%s", pszValue,
                        svr_db_file);

        *path = strdup(file_path);

        return 0;
}

/** @} */ //end of ctc-platform-permission
