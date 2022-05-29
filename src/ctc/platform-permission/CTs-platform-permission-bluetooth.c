#include "CTs-platform-permission-common.h"

#define SHORT_DELAY						2000
#define LONG_DELAY						5000
#define CALLBACK_DELAY					40000
#define PATH_LEN						1024
#define BLUETOOTH_SERVICE_UUID			"00001105-0000-1000-8000-00805f9b34fb"
int nTimeoutId = -1;
#define WAIT(nTime)\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(nTime, TimeoutFunction, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nTimeoutId);\
	

bool g_bCallbackResult;
static bool g_bCallbackPushRequested = false;

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
 * @brief Callback funtions
 */
static void Bluetooth_bt_adapter_le_scan_start_stop_result_cb(int result,bt_adapter_le_device_scan_result_info_s *info, void *user_data)
{
	g_bCallbackResult = true;
	FPRINTF("\\n[Line : %d][%s] Bluetooth_bt_adapter_le_scan_start_stop_result_cb  called successfully!", __LINE__ ,API_NAMESPACE);
	return;
}
	/**
* @brief Callback funtions
*/
static void Bluetooth_bt_opp_server_connection_requested_cb_p(const char *pszRemoteAddress, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked: opp_server_connection_requested\\n", __LINE__, API_NAMESPACE);
	FPRINTF("[Line : %d][%s] Remote Device Address: %s\\n", __LINE__, API_NAMESPACE, pszRemoteAddress);
	g_bCallbackPushRequested = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

#ifdef MOBILE	//Starts MOBILE
/**
* @brief Callback funtions
*/
static void Bluetooth_bt_adapter_le_advertising_state_changed_cb(int result,
		bt_advertiser_h advertiser, bt_adapter_le_advertising_state_e adv_state, void *user_data)
{
	FPRINTF("Result : %d", result);
	FPRINTF("Advertiser : %p", advertiser);
	FPRINTF("Advertising %s [%d]", adv_state == BT_ADAPTER_LE_ADVERTISING_STARTED ?
				"started" : "stopped", adv_state);
}

/**
* @brief Callback funtions
*/
static void __bt_adapter_le_advertising_state_changed_cb(int result, bt_advertiser_h advertiser,bt_adapter_le_advertising_state_e adv_state,void *user_data)
{
		return;
}
#endif 		//End MOBILE

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
		strncpy(pszPath, pszTempPath, strlen(pszTempPath)+1);
		free(pszTempPath);
		pszTempPath = NULL;		
	}
	return true;
}
/**
* @function 					BluetoothGetError
* @description 					print the error information
* @parameter[in]				nResult: the error code
* @return 						pszErrorMsg: return the error message
*/
char *BluetoothGetError(int nResult)
{
	char *pszErrorMsg = NULL;

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
	case BT_ERROR_NONE :
		pszErrorMsg = "BT_ERROR_NONE  \n";
		break;
	default:
		pszErrorMsg = "UNDEFINED ERROR \n";
		break;
	}
	return pszErrorMsg;
}

/**
* @function 		CTs_platform_permission_bluetooth_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_bluetooth_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_bluetooth_startup\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function 		CTs_platform_permission_bluetooth_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_bluetooth_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_bluetooth_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
//& purpose: Checking tizen.org/privilege/bluetooth privilege
//& type: auto
/**
* @testcase			CTc_Bluetooth_PrivilegeBluetooth_set_name
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Initializes the Bluetooth API\n
*					Sets the name of local Bluetooth adapter\n
*					Deinitializes the Bluetooth API
* @apicovered		bt_initialize, bt_adapter_set_name and bt_deinitialize
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		If bluetooth is supported then it must be enable on target device
* @postcondition	NA
*/
int CTc_Bluetooth_PrivilegeBluetooth_set_name(void)
{
	START_TEST;
	char* pszAdapterName = "Test";
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH, g_bIsSupported, API_NAMESPACE);
	if ( false == g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH);
		return 0;
	}

	
	int nRet = bt_initialize();
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_initialize", BluetoothGetError(nRet));

	nRet = bt_adapter_set_name(pszAdapterName);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "bt_adapter_set_name", BluetoothGetError(nRet), bt_deinitialize());

	nRet = bt_deinitialize();
	PRINT_RESULT_NORETURN(BT_ERROR_NONE, nRet, "bt_deinitialize", BluetoothGetError(nRet));
	return 0;
}

//& purpose: Checks if the device discovery is in progress or not
//& type: auto
/**
* @testcase			CTc_Bluetooth_PrivilegeBluetooth_bt_adapter_is_discovering
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Start device discovery\n
*					Checks if the device discovery is in progress or not\n
*					Stop device discovery
* @apicovered		bt_adapter_start_device_discovery, bt_adapter_is_discovering and bt_adapter_stop_device_discovery
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		Bluetooth must be initialized
* @postcondition	Bluetooth must be de-initialized
*/
int CTc_Bluetooth_PrivilegeBluetooth_bt_adapter_is_discovering(void)
{
	START_TEST;
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH, g_bIsSupported, API_NAMESPACE);
	if ( false == g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH);
		return 0;
	}
	int nRet = bt_initialize();
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_initialize", BluetoothGetError(nRet));

	nRet = bt_adapter_start_device_discovery();
        if(nRet == BT_ERROR_NONE)
        {
            bt_adapter_stop_device_discovery();
        }
    PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, " bt_adapter_start_device_discovery", BluetoothGetError(nRet),bt_deinitialize());

	nRet = bt_deinitialize();
	PRINT_RESULT_NORETURN(BT_ERROR_NONE, nRet, "bt_deinitialize", BluetoothGetError(nRet));
	
	return 0;
}
//& purpose: Registers a RFCOMM socket with a specific UUID
//& type: auto
/**
* @testcase 			CTc_Bluetooth_PrivilegeBluetooth_bt_socket_create_destroy_rfcomm
* @since_tizen			2.3
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Registers a RFCOMM socket with a specific UUID
* @scenario				Create a RFCOMM socket\n
*						Destroy RFCOMM socket
* @apicovered			bt_socket_create_rfcomm and bt_socket_destroy_rfcomm
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int CTc_Bluetooth_PrivilegeBluetooth_bt_socket_create_destroy_rfcomm(void)
{
	START_TEST;
	int nSocketFd = -1;
	int nRetVal =0;
	bool g_bIsSupported =false;
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH, g_bIsSupported, API_NAMESPACE);
	if ( false == g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH);
		return 0;
	}
	nRetVal = bt_initialize();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_initialize", BluetoothGetError(nRetVal));
	
	nRetVal = bt_socket_create_rfcomm(BLUETOOTH_SERVICE_UUID, &nSocketFd);
	if(nRetVal == BT_ERROR_NONE)
        {
            bt_socket_destroy_rfcomm(nSocketFd);
        }
    PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRetVal, " bt_socket_create_rfcomm", BluetoothGetError(nRetVal),bt_deinitialize());

	nRetVal = bt_deinitialize();
	PRINT_RESULT_NORETURN(BT_ERROR_NONE, nRetVal, "bt_deinitialize", BluetoothGetError(nRetVal));
	return 0;
}
//& purpose: Sets the destination path of the file to be pushed.
//& type: auto
/**
* @testcase 			CTc_Bluetooth_PrivilegeBluetooth_bt_opp_server_set_destination
* @since_tizen			2.3
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets the destination path of the file to be pushed.
* @scenario				Initialize bluetooth OPP Server\n
*						Set destination path\n
*						Deinitialize bluetooth OPP Server
* @apicovered			bt_opp_server_initialize, bt_opp_server_set_destination and bt_opp_server_deinitialize
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int CTc_Bluetooth_PrivilegeBluetooth_bt_opp_server_set_destination(void)
{
	START_TEST;
	int nRet =0;
	char szFilePath[PATH_LEN] = {0,};
	bool g_bIsBlueSupported =false;
	bool g_bIsOppSupported =false;
	bool g_bIsSupported =false;
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH, g_bIsBlueSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH_OPP, g_bIsOppSupported, API_NAMESPACE);
	g_bIsSupported =g_bIsBlueSupported && g_bIsOppSupported;
	if ( false == g_bIsSupported  )
	{
		FPRINTF("[Line : %d][%s] Feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	nRet = bt_initialize();
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_initialize", BluetoothGetError(nRet));
	
	if ( false == BluetoothGetStorageDownloadsPath(szFilePath))
	{
		return 1;
	}

	nRet = bt_opp_server_initialize_by_connection_request(szFilePath, Bluetooth_bt_opp_server_connection_requested_cb_p, NULL);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_opp_server_initialize_by_connection_request", BluetoothGetError(nRet),bt_deinitialize());

	WAIT(SHORT_DELAY);
	
	nRet = bt_opp_server_set_destination(szFilePath);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "bt_opp_server_set_destination", BluetoothGetError(nRet),bt_opp_server_deinitialize();bt_deinitialize());

	bt_opp_server_deinitialize();
	nRet = bt_deinitialize();
	PRINT_RESULT_NORETURN(BT_ERROR_NONE, nRet, "bt_deinitialize", BluetoothGetError(nRet));
	return 0;
}
//& purpose: To test bt_adapter_le_start_scan
//& type: auto
/**
 * @testcase 			CTc_Bluetooth_PrivilegeBluetooth_adapter_le_start_stop_scan
 * @since_tizen			2.3.1
 * @author				SRID(manoj.g2)
 * @reviewer			SRID(shobhit.v)
 * @type 				Positive
 * @description			To test bt_adapter_le_start_scan
 * @scenario			Call bt_adapter_le_start_scan
 * @apicovered			bt_adapter_le_start_scan, bt_adapter_le_stop_scan
 * @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
 * @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
 * @precondition		Bluetooth must be initialized
 * @postcondition		Bluetooth must be deinitialized
 */
int CTc_Bluetooth_PrivilegeBluetooth_adapter_le_start_stop_scan(void)
{
	START_TEST;
	int nRet =0;
	bool g_bIsSupported =false;
	
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH, g_bIsSupported, API_NAMESPACE);
	if ( (false == g_bIsSupported))
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH);
		return 0;
	}
	
	// Checking for bluetooth.le feature
	bool g_bIsSupported_le =false;
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH_LE, g_bIsSupported_le, API_NAMESPACE);
	if ( (g_bIsSupported_le == false))
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH_LE);
		return 0;
	}
	
	
	nRet = bt_initialize();
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_initialize", BluetoothGetError(nRet));
	
	nRet = bt_adapter_le_start_scan(Bluetooth_bt_adapter_le_scan_start_stop_result_cb,NULL);
	if(nRet == BT_ERROR_NONE)
        {
            bt_adapter_le_stop_scan();
        }
    PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, " bt_adapter_le_start_scan", BluetoothGetError(nRet),bt_deinitialize());
	
	nRet = bt_deinitialize();
	PRINT_RESULT_NORETURN(BT_ERROR_NONE, nRet, "bt_deinitialize", BluetoothGetError(nRet));
	return 0;
}

#ifdef MOBILE	//Starts MOBILE
//& purpose: To test bt_adapter_le_start_advertising_new
//& type: auto
/**
 * @testcase 			CTc_Bluetooth_PrivilegeBluetooth_le_start_advertising_new
 * @since_tizen			2.3.1
 * @author				SRID(manoj.g2)
 * @reviewer			SRID(shobhit.v)
 * @type 				Positive
 * @description			To test bt_adapter_le_start_advertising_new
 * @scenario			Call bt_adapter_le_start_advertising_new
 * @apicovered			bt_adapter_le_start_advertising_new
 * @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
 * @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
 * @precondition		Bluetooth must be initialized
 * @postcondition		Bluetooth must be deinitialized
 */
int CTc_Bluetooth_PrivilegeBluetooth_le_start_advertising_new(void)
{
	START_TEST;
	int nRet =0;
	bt_advertiser_h advertiser = NULL;
	bt_adapter_le_advertising_state_changed_cb cb;
	cb = Bluetooth_bt_adapter_le_advertising_state_changed_cb;
	bool g_bIsSupported =false;
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH, g_bIsSupported, API_NAMESPACE);
	if ( false == g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH);
		return 0;
	}
	
	// Checking for bluetooth.le feature
	bool g_bIsSupported_le =false;
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH_LE, g_bIsSupported_le, API_NAMESPACE);
	if ( (g_bIsSupported_le == false))
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH_LE);
		return 0;
	}
	
	nRet = bt_initialize();
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_initialize", BluetoothGetError(nRet));
	

	nRet = bt_adapter_le_create_advertiser(&advertiser);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_start_scan", BluetoothGetError(nRet),bt_deinitialize());

	nRet = bt_adapter_le_start_advertising_new(advertiser, cb, NULL);
	if(nRet == BT_ERROR_NONE)
        {
            bt_adapter_le_stop_advertising(advertiser);
        }
    PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, " bt_adapter_le_start_advertising_new", BluetoothGetError(nRet),bt_deinitialize();bt_adapter_le_destroy_advertiser(advertiser));
	bt_adapter_le_destroy_advertiser(advertiser);
	nRet = bt_deinitialize();
	PRINT_RESULT_NORETURN(BT_ERROR_NONE, nRet, "bt_deinitialize", BluetoothGetError(nRet));
	return 0;
}
#endif  //End MOBILE

//& purpose: To test bt_adapter_le_set_advertising_mode
//& type: auto
/**
 * @testcase 			CTc_Bluetooth_PrivilegeBluetooth_adapter_le_set_advertising_mode
 * @since_tizen			2.3.1
 * @author				SRID(manoj.g2)
 * @reviewer			SRID(shobhit.v)
 * @type 				auto
 * @description			To test bt_adapter_le_set_advertising_mode
 * @scenario			Call bt_adapter_le_set_advertising_mode
 * @apicovered			bt_adapter_le_set_advertising_mode
 * @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
 * @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
 * @precondition		Bluetooth must be initialized
 * @postcondition		Bluetooth must be deinitialized
 */
int CTc_Bluetooth_PrivilegeBluetooth_adapter_le_set_advertising_mode(void)
{
	START_TEST;

	bt_advertiser_h advertiser = NULL;
	bool g_bIsSupported =false;
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH, g_bIsSupported, API_NAMESPACE);
	if ( false == g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH);
		return 0;
	}
	
	// Checking for bluetooth.le feature
	bool g_bIsSupported_le =false;
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH_LE, g_bIsSupported_le, API_NAMESPACE);
	if ( (g_bIsSupported_le == false))
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH_LE);
		return 0;
	}
	
	int nRet = bt_initialize();
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_initialize", BluetoothGetError(nRet));
	
	nRet = bt_adapter_le_create_advertiser(&advertiser);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, " bt_adapter_le_create_advertiser", BluetoothGetError(nRet),bt_deinitialize());
	
	nRet = bt_adapter_le_set_advertising_mode(advertiser, BT_ADAPTER_LE_ADVERTISING_MODE_BALANCED);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, " bt_adapter_le_set_advertising_mode", BluetoothGetError(nRet),bt_adapter_le_destroy_advertiser(advertiser);bt_deinitialize());

	bt_adapter_le_destroy_advertiser(advertiser);
	nRet = bt_deinitialize();
	PRINT_RESULT_NORETURN(BT_ERROR_NONE, nRet, "bt_deinitialize", BluetoothGetError(nRet));
	return 0;
}

/**
 * @testcase 			CTc_Bluetooth_PrivilegeBluetooth_adapter_set_remove_remote_oob_data
 * @since_tizen			3.0
 * @author				SRID(arvin.mittal)
 * @reviewer			SRID(shobhit.v)
 * @type 				auto
 * @description			Call to set the Hash and Randmoizer value, synchronously by setting the input parameters "NULL"
 *						and check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le	is supported otherwise just try
 *						set the value with "NULL" parameters and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 *						Call to delete the Hash and Randmoizer value, synchronously by setting the input parameter "NULL"
 *						and check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le	is supported otherwise just try
 *						to delete the value with "NULL" parameter and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario			scenario to set the Hash and Randmoizer value, synchronously
 * @apicovered			bt_adapter_set_remote_oob_data, bt_adapter_remove_remote_oob_data
 * @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
 * @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
 * @precondition		Bluetooth must be initialized
 * @postcondition		Bluetooth must be deinitialized
 */
int CTc_Bluetooth_PrivilegeBluetooth_adapter_set_remove_remote_oob_data(void)
{
	START_TEST;
	
	const char *remote_address = "E4:32:CB:41:1F:A6";
	unsigned char *hash = (unsigned char*)"123456";
	unsigned char *randomizer = (unsigned char*)"123456";
	int hash_len = 8;
	int randomizer_len = 8;
	int nRet ;
	bool bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH, bIsSupported, API_NAMESPACE);
	if ( false == bIsSupported )
	
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH);
		return 0;
	}
	else
	{
	
		nRet = bt_initialize();
		PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_initialize", BluetoothGetError(nRet));
		
		nRet = bt_adapter_set_remote_oob_data(remote_address, hash, randomizer, hash_len,randomizer_len);
		if(nRet == BT_ERROR_NONE)
        {
            bt_adapter_remove_remote_oob_data(remote_address);
        }
		PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "bt_adapter_set_remote_oob_data", BluetoothGetError(nRet),bt_deinitialize());
		nRet = bt_deinitialize();
		PRINT_RESULT_NORETURN(BT_ERROR_NONE, nRet, "bt_deinitialize", BluetoothGetError(nRet));
	}
    return 0;
}

/**
 * @testcase 			CTc_Bluetooth_PrivilegeBluetooth_gatt_connect
 * @since_tizen			3.0
 * @author				SRID(arvin.mittal)
 * @reviewer			SRID(shobhit.v)
 * @type 				auto
 * @description			if bluetooth LE is supported and startup_flag is asserted then initialize the bluetooth and
 *						connect to the remote device and check for errors.
 * @scenario			Try to connect to a specific LE based service on a remote bluetooth dievice address,
 *						asynchronously after bluetooth initialization.
 * @apicovered			bt_gatt_connect
 * @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
 * @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
 * @precondition		Bluetooth must be initialized
 * @postcondition		Bluetooth must be deinitialized
 */
int CTc_Bluetooth_PrivilegeBluetooth_gatt_connect(void)
{
	START_TEST;
	
	int nRet;
	const char *remote_address = "E4:32:CB:41:1F:A6";
    bool auto_connect = true;
	
	bool bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH, bIsSupported, API_NAMESPACE);
	if ( false == bIsSupported )
	
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH);
		return 0;
	}
	
	bool bIsSupported_le = false;
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH_LE, bIsSupported_le, API_NAMESPACE);
	if ( false == bIsSupported_le )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH_LE);
		return 0;
	}

	bool bIsSupportedGattClient = false;
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH_GATT_CLIENT, bIsSupportedGattClient, API_NAMESPACE);
	if ( false == bIsSupportedGattClient )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH_GATT_CLIENT);
		return 0;
	}
    else
	{
		nRet = bt_initialize();
		PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_initialize", BluetoothGetError(nRet));
		
		nRet = bt_gatt_connect(remote_address, auto_connect);
		PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "bt_gatt_connect", BluetoothGetError(nRet),bt_deinitialize()); 
		nRet = bt_deinitialize();
		PRINT_RESULT_NORETURN(BT_ERROR_NONE, nRet, "bt_deinitialize", BluetoothGetError(nRet));	
    }
    return 0;
}

/**
 * @testcase 			CTc_Bluetooth_PrivilegeBluetooth_audio_connect_disconnect
 * @since_tizen			3.0
 * @author				SRID(arvin.mittal)
 * @reviewer			SRID(shobhit.v)
 * @type 				auto
 * @description			check if audio profile is supported and startup_flag is asserted, then initialize the bluetooth and
 *						connect to the remote device with given audio profile and check for errors.
 * @scenario			Try to connect the remote device with the given audio profile,
 * @apicovered			bt_audio_connect, bt_audio_disconnect
 * @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
 * @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
 * @precondition		Bluetooth must be initialized
 * @postcondition		Bluetooth must be deinitialized
 */
int CTc_Bluetooth_PrivilegeBluetooth_audio_connect_disconnect(void)
{

	START_TEST;
	
	int nRet;
	const char *remote_address = "E4:32:CB:41:1F:A6";
	
	bool bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH, bIsSupported, API_NAMESPACE);
	if ( false == bIsSupported )
	
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH);
		return 0;
	}
	
	bool bIsSupported_media = false;
	bool bIsSupported_call = false;
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH_AUDIO_MEDIA, bIsSupported_media, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH_CALL, bIsSupported_call, API_NAMESPACE);
	if ( false == bIsSupported_media )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH_AUDIO_MEDIA);
		return 0;
	} 
	else if ( bIsSupported_call == false )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH_CALL);
		return 0;
	}
	else
	{
		nRet = bt_initialize();
		PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_initialize", BluetoothGetError(nRet));
		
		nRet = bt_audio_initialize();
		PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_audio_initialize", BluetoothGetError(nRet),bt_deinitialize());
		
		nRet = bt_audio_connect(remote_address, BT_AUDIO_PROFILE_TYPE_A2DP);
		if(nRet == BT_ERROR_NONE)
        {
            bt_audio_disconnect(remote_address,BT_AUDIO_PROFILE_TYPE_A2DP);
        }
        PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "bt_audio_connect", BluetoothGetError(nRet),bt_audio_deinitialize();bt_deinitialize());
		
		bt_audio_deinitialize();
		nRet = bt_deinitialize();
		PRINT_RESULT_NORETURN(BT_ERROR_NONE, nRet, "bt_deinitialize", BluetoothGetError(nRet));	
		
    } 
    return 0;
}
