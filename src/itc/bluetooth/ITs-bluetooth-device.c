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

char **g_pszBluetoothUuids;
int g_nBluetoothServiceCount = 0;


/**
* @brief Callback funtions
*/
static void Bluetooth_bt_device_authorization_changed_cb_p(bt_device_authorization_e authorization, char *remote_address, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked for device set authorization\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

/**
* @brief Callback funtions
*/
static void Bluetooth_bt_device_service_searched_cb_p(int result, bt_device_sdp_info_s *sdp_info, void *user_data)
{
	int nCounter = 0;
	FPRINTF("[Line : %d][%s] Callback invoked for service search\\n", __LINE__, API_NAMESPACE);
	FPRINTF("[Line : %d][%s] result is: %d\\n", __LINE__, API_NAMESPACE,result);
	FPRINTF("[Line : %d][%s] service_count is: %d\\n", __LINE__, API_NAMESPACE, sdp_info->service_count);

	if ( sdp_info->service_count > 0 )
	{
		g_nBluetoothServiceCount = sdp_info->service_count;
		g_pszBluetoothUuids = malloc(sdp_info->service_count * sizeof(char*));
		for ( nCounter = 0; nCounter < g_nBluetoothServiceCount; nCounter++ )
		{
			g_pszBluetoothUuids[nCounter] = malloc(BLUETOOTH_UUID_LENGTH * sizeof(char));
			strncpy(g_pszBluetoothUuids[nCounter], sdp_info->service_uuid[nCounter], BLUETOOTH_UUID_LENGTH);
		}
	}
	g_bCallbackResult = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

/**
* @brief Callback funtions
*/
static void Bluetooth_bt_device_bond_created_cb_p(int result, bt_device_info_s * device_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked for device bonding creation\\n", __LINE__, API_NAMESPACE);
	if ( device_info != NULL )
	{
		FPRINTF("[Line : %d][%s] Remote Address: %s\\n", __LINE__, API_NAMESPACE, device_info->remote_address);
		FPRINTF("[Line : %d][%s] Remote Name: %s\\n", __LINE__, API_NAMESPACE, device_info->remote_name);
		FPRINTF("[Line : %d][%s] Is Bonded: %d\\n", __LINE__, API_NAMESPACE, device_info->is_bonded);
		FPRINTF("[Line : %d][%s] Is Connected: %d\\n", __LINE__, API_NAMESPACE, device_info->is_connected);
	}

	g_bCallbackResult = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

/**
* @brief Callback funtions
*/
static void Bluetooth_bt_device_bond_destroyed_cb_p(int result, char *remote_address, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked for device bonding destroy\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

/**
* @brief Callback funtions
*/
static void Bluetooth_bt_device_connection_state_changed_cb_p(bool connected, bt_device_connection_info_s *conn_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked for connection state change\\n", __LINE__, API_NAMESPACE);
	FPRINTF("[Line : %d][%s] Connection Status: %d\\n", __LINE__, API_NAMESPACE, connected);
	g_bCallbackResult = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}


/**
* @function 		ITs_bluetooth_device_startup
* @description	 	Called before each test, Bluetooth is initialized
* @parameter		NA
* @return 			NA
*/
void ITs_bluetooth_device_startup(void)
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
		return;
	}
	else
	{
		g_bBluetoothIsSupported = true;
	}
	
	int nRetVal = bt_initialize();
	if ( false == g_bBluetoothIsSupported )
	{
		if ( nRetVal != TIZEN_ERROR_NOT_SUPPORTED )
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
	return;

}

/**
* @function 		ITs_bluetooth_device_cleanup
* @description	 	Called after each test, Bluetooth is de-initialized
* @parameter		NA
* @return 			NA
*/
void ITs_bluetooth_device_cleanup(void)
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

//& purpose: Registers a callback function to be invoked when the authorization of device changes and Unregister the callback.
//& type: auto
/**
* @testcase 			ITc_bluetooth_device_bt_device_set_unset_authorization_changed_cb_p
* @since_tizen			2.3
* @type 				auto
* @description			Registers a callback function to be invoked when the authorization of device changes and Unregister the callback.
* @scenario				Register callback for set authorization\n
*						Unregister callback for set authorization
* @apicovered			bt_device_set_authorization_changed_cb, bt_device_unset_authorization_changed_cb
* @passcase				When bt_device_set_authorization_changed_cb and bt_device_unset_authorization_changed_cb is successful.
* @failcase				If targest API bt_device_set_authorization_changed_cb or bt_device_unset_authorization_changed_cb fails
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_device_bt_device_set_unset_authorization_changed_cb_p(void)
{
	START_TEST;

	int nRetVal = bt_device_set_authorization_changed_cb(Bluetooth_bt_device_authorization_changed_cb_p, "SetAuthorization");
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_device_set_authorization_changed_cb", BluetoothGetError(nRetVal));

	nRetVal = bt_device_unset_authorization_changed_cb();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_device_unset_authorization_changed_cb", BluetoothGetError(nRetVal));
	return 0;
}

//& purpose: Registers a callback function to be invoked when a bond is created and unregister the callback
//& type: auto
/**
* @testcase 			ITc_bluetooth_device_bt_device_set_unset_bond_created_cb_p
* @since_tizen			2.3
* @type 				auto
* @description			Registers a callback function to be invoked when a bond is created and unregister the callback
* @scenario				Register callback\n
*						Unregister the callback
* @apicovered			bt_device_set_bond_created_cb, bt_device_unset_bond_created_cb,
* @passcase				When bt_device_set_bond_created_cb and bt_device_unset_bond_created_cb is successful.
* @failcase				If targest API bt_device_set_bond_created_cb or bt_device_unset_bond_created_cb fails.
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_device_bt_device_set_unset_bond_created_cb_p(void)
{
	START_TEST;
	int nRetVal = bt_device_set_bond_created_cb(Bluetooth_bt_device_bond_created_cb_p, "CreateBond");
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_device_set_bond_created_cb", BluetoothGetError(nRetVal));
	nRetVal = bt_device_unset_bond_created_cb();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_device_unset_bond_created_cb", BluetoothGetError(nRetVal));
	return 0;
}

//& purpose: Registers a callback function to be invoked when a bond is destroyed and Unregister the callback
//& type: auto
/**
* @testcase 			ITc_bluetooth_device_bt_device_set_unset_bond_destroyed_cb_p
* @since_tizen			2.3
* @type 				auto
* @description			Registers a callback function to be invoked when a bond is destroyed and Unregister the callback
* @scenario				Register callback\n
*						Unregister the callback
* @apicovered			bt_device_set_bond_destroyed_cb and bt_device_unset_bond_destroyed_cb
* @passcase				When bt_device_set_bond_destroyed_cb and bt_device_unset_bond_destroyed_cb is successful
* @failcase				If targest API bt_device_set_bond_destroyed_cb or bt_device_unset_bond_destroyed_cb is failed
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_device_bt_device_set_unset_bond_destroyed_cb_p(void)
{
	START_TEST;
	int nRetVal = bt_device_set_bond_destroyed_cb(Bluetooth_bt_device_bond_destroyed_cb_p, "DestroyBond");
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_device_set_bond_destroyed_cb", BluetoothGetError(nRetVal));
	nRetVal = bt_device_unset_bond_destroyed_cb();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_device_unset_bond_destroyed_cb", BluetoothGetError(nRetVal));
	return 0;
}

//& purpose: Registers a callback function to be invoked when the connection state is changed and Unregister callback
//& type: auto
/**
* @testcase 			ITc_bluetooth_device_bt_device_set_unset_connection_state_changed_cb_p
* @since_tizen			2.3
* @type 				auto
* @description			Registers a callback function to be invoked when the connection state is changed and Unregister callback
* @scenario				Register callback\n
*						Unregister the callback
* @apicovered			bt_device_set_connection_state_changed_cb and bt_device_unset_connection_state_changed_cb
* @passcase				When bt_device_set_connection_state_changed_cb and bt_device_unset_connection_state_changed_cb is successful
* @failcase				If targest API bt_device_set_connection_state_changed_cb or bt_device_unset_connection_state_changed_cb is failed
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_device_bt_device_set_unset_connection_state_changed_cb_p(void)
{
	START_TEST;
	int nRetVal = bt_device_set_connection_state_changed_cb(Bluetooth_bt_device_connection_state_changed_cb_p, "SetConnection");
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_device_set_connection_state_changed_cb", BluetoothGetError(nRetVal));

	nRetVal = bt_device_unset_connection_state_changed_cb();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_device_unset_connection_state_changed_cb", BluetoothGetError(nRetVal));
	return 0;
}

//& purpose: Registers a callback function to be invoked when the process of service search finishes and unregister callback
//& type: auto
/**
* @testcase 			ITc_bluetooth_device_bt_device_set_unset_service_searched_cb_p
* @since_tizen			2.3
* @type 				auto
* @description			Registers a callback function to be invoked when the process of service search finishes and unregister callback
* @scenario				Register callback\n
*						Unregister callback
* @apicovered			bt_device_set_service_searched_cb, and bt_device_unset_service_searched_cb
* @passcase				When bt_device_set_service_searched_cb and bt_device_unset_service_searched_cb is successful
* @failcase				If targest API bt_device_set_service_searched_cb or bt_device_unset_service_searched_cb is failed
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_device_bt_device_set_unset_service_searched_cb_p(void)
{
	START_TEST;
	int nRetVal = bt_device_set_service_searched_cb(Bluetooth_bt_device_service_searched_cb_p, "SetServiceSearch");
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_device_set_service_searched_cb", BluetoothGetError(nRetVal));

	nRetVal = bt_device_unset_service_searched_cb();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_device_unset_service_searched_cb", BluetoothGetError(nRetVal));
	return 0;
}

/** @} */
