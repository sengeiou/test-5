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


static bool g_bCallbackPushRequested = false;
static const char *g_szDest = "/tmp";

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

/**
* @function 		ITs_bluetooth_OPP_startup
* @description	 	Called before each test, Bluetooth is initialized
* @parameter		NA
* @return 			NA
*/
void ITs_bluetooth_OPP_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Bluetooth_p\\n", __LINE__, API_NAMESPACE);
#endif

	if ( !TCTCheckSystemInfoFeatureSupported(BLUETOOTH_FEATURE, API_NAMESPACE) )
	{
		g_bBluetoothIsSupported = false;
	}
	else
	{
		g_bBluetoothIsSupported = true;
	}

	int nRetVal = bt_initialize();
	if ( false == g_bBluetoothIsSupported )
	{
		if ( nRetVal != BT_ERROR_NOT_SUPPORTED )
		{
			g_bBluetoothMismatch = true;
		}
		else
		{
			g_bBluetoothNotSupported = true;
		}
		return;
	}

	if ( nRetVal != BT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Bluetooth initialization failed, error returned = %s\\n", __LINE__, API_NAMESPACE, BluetoothGetError(nRetVal));
		g_bBluetoothInit = false;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Bluetooth initialized successfully\\n", __LINE__, API_NAMESPACE);
		g_bBluetoothInit = true;
	}

	if ( !TCTCheckSystemInfoFeatureSupported(BLUETOOTH_OPP_FEATURE, API_NAMESPACE) )
	{
		g_bBluetoothIsOPPSupported = false;
	}
	else
	{
		g_bBluetoothIsOPPSupported = true;
	}
	return;
}

/**
* @function 		ITs_bluetooth_OPP_cleanup
* @description	 	Called after each test, Bluetooth is de-initialized
* @parameter		NA
* @return 			NA
*/
void ITs_bluetooth_OPP_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Bluetooth_p\\n", __LINE__, API_NAMESPACE);
#endif
	if ( g_bBluetoothInit )
	{
		int nRetVal = bt_deinitialize();
		if ( nRetVal != BT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Bluetooth de-initialization failed, error returned = %s\\n", __LINE__, API_NAMESPACE, BluetoothGetError(nRetVal));
		}
		else
		{
			FPRINTF("[Line : %d][%s] Bluetooth de-initialized successfully\\n", __LINE__, API_NAMESPACE);
		}
	}

	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
	sleep(SLEEP_TIME);

	return;
}

//& purpose: Initialize and Deinitialize the Bluetooth OPP Client
//& type: auto
/**
* @testcase 			ITc_bluetooth_client_OPP_bt_opp_client_initialize_deinitialize_p
* @since_tizen			2.3
* @type 				auto
* @description			Initialize and Deinitialize the Bluetooth API
* @scenario				Initialize bluetooth OPP Client\n
*						Deinitialize bluetooth OPP Client
* @apicovered			bt_opp_client_initialize and bt_opp_client_deinitialize
* @passcase				When bt_opp_client_initialize and bt_opp_client_deinitialize is successful
* @failcase				If targest APIs bt_opp_client_initialize or bt_opp_client_deinitialize fails
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_client_OPP_bt_opp_client_initialize_deinitialize_p(void)
{
	START_TEST;
	int nTimeoutId = 0;
	
	int nRetVal = bt_opp_client_initialize();
	if ( !g_bBluetoothIsOPPSupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRetVal, "bt_opp_client_initialize", BluetoothGetError(nRetVal));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_opp_client_initialize", BluetoothGetError(nRetVal));
	WAIT(SHORT_DELAY);
	nRetVal = bt_opp_client_deinitialize();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_opp_client_deinitialize", BluetoothGetError(nRetVal));
	return 0;
}

//& purpose: Adds a file to be pushed and clear the file
//& type: auto
/**
* @testcase 			ITc_bluetooth_client_OPP_bt_opp_client_add_file_clear_files_p
* @since_tizen			2.3
* @type 				auto
* @description			Adds a file to be pushed and clear the file
* @scenario				Initialize bluetooth OPP Client\n
*						Add file\n
*						Clear file\n
*						Deinitialize bluetooth OPP Client
* @apicovered			bt_opp_client_initialize, bt_opp_client_add_file, bt_opp_client_clear_files and bt_opp_client_deinitialize
* @passcase				When bt_opp_client_add_file and bt_opp_client_clear_files are successful
* @failcase				If targest APIs bt_opp_client_add_file or bt_opp_client_clear_files fails
* @precondition			Bluetooth must be initialized
*						File (to be added) must be present at application data path
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_client_OPP_bt_opp_client_add_file_clear_files_p(void)
{
	START_TEST;
	int nTimeoutId = 0;
	char pPath[PATH_LEN] = {0,};
	
	if ( false == BluetoothGetDataPath(pPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__ , API_NAMESPACE);
		return 1;
	}

	strncat(pPath, OPP_FILE_NAME, PATH_LEN);
	FPRINTF("[Line : %d][%s] Complete file path is: %s\\n", __LINE__, API_NAMESPACE, pPath);

	int nRetVal = bt_opp_client_initialize();
	if ( !g_bBluetoothIsOPPSupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRetVal, "bt_opp_client_initialize", BluetoothGetError(nRetVal));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_opp_client_initialize", BluetoothGetError(nRetVal));

	nRetVal = bt_opp_client_add_file(pPath);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_opp_client_add_file", BluetoothGetError(nRetVal), bt_opp_client_deinitialize());

	WAIT(SHORT_DELAY);
	nRetVal = bt_opp_client_clear_files();
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_opp_client_clear_files", BluetoothGetError(nRetVal), bt_opp_client_deinitialize() );

	WAIT(SHORT_DELAY);
	nRetVal = bt_opp_client_deinitialize();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_opp_client_deinitialize", BluetoothGetError(nRetVal));

	return 0;
}

//Bluetooth OPP Server

//& purpose: Initialize and Deinitialize the Bluetooth OPP Server
//& type: auto
/**
* @testcase 			ITc_bluetooth_server_OPP_bt_opp_server_initialize_deinitialize_connection_request_p
* @since_tizen			2.3
* @type 				auto
* @description			Initializes the Bluetooth OPP server requested by bt_opp_server_connection_requested_cb(). Deinitialize the Bluetooth OPP Server
* @scenario				Initialize bluetooth OPP Server requested by bt_opp_server_connection_requested_cb()\n
*						Deinitialize bluetooth OPP Server
* @apicovered			bt_opp_server_initialize_by_connection_request and bt_opp_server_deinitialize
* @passcase				When bt_opp_server_initialize_by_connection_request and bt_opp_server_deinitialize is successful
* @failcase				If targest APIs bt_opp_server_initialize_by_connection_request or bt_opp_server_deinitialize failso
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_server_OPP_bt_opp_server_initialize_deinitialize_connection_request_p(void)
{
	START_TEST;
	int nTimeoutId = 0;
	
	int nRetVal = bt_opp_server_initialize_by_connection_request(g_szDest, Bluetooth_bt_opp_server_connection_requested_cb_p, NULL);
	if ( !g_bBluetoothIsOPPSupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRetVal, "bt_opp_server_initialize_by_connection_request", BluetoothGetError(nRetVal));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_opp_server_initialize_by_connection_request", BluetoothGetError(nRetVal));
	WAIT(SHORT_DELAY);
	nRetVal = bt_opp_server_deinitialize();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_opp_server_deinitialize", BluetoothGetError(nRetVal));
	return 0;
}

//& purpose: Sets the destination path of the file to be pushed.
//& type: auto
/**
* @testcase 			ITc_bluetooth_server_OPP_bt_opp_server_set_destination_p
* @since_tizen			2.3
* @type 				auto
* @description			Sets the destination path of the file to be pushed.
* @scenario				Initialize bluetooth OPP Server\n
*						Set destination path\n
*						Deinitialize bluetooth OPP Server
* @apicovered			bt_opp_server_initialize, bt_opp_server_set_destination and bt_opp_server_deinitialize
* @passcase				When bt_opp_server_set_destination is successful
* @failcase				If targest API bt_opp_server_set_destination fails
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_server_OPP_bt_opp_server_set_destination_p(void)
{
	START_TEST;
	int nTimeoutId = 0;

	int nRetVal = bt_opp_server_initialize_by_connection_request(g_szDest, Bluetooth_bt_opp_server_connection_requested_cb_p, NULL);
	if ( !g_bBluetoothIsOPPSupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRetVal, "bt_opp_server_initialize_by_connection_request", BluetoothGetError(nRetVal));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_opp_server_initialize_by_connection_request", BluetoothGetError(nRetVal));

	WAIT(SHORT_DELAY);
	nRetVal = bt_opp_server_set_destination(g_szDest);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_opp_server_set_destination", BluetoothGetError(nRetVal),bt_opp_server_deinitialize());

	nRetVal = bt_opp_server_deinitialize();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_opp_server_deinitialize", BluetoothGetError(nRetVal));
	return 0;
}

/** @} */
/** @} */
