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

int g_nBluetoothSocketFd;

/**
* @brief Callback funtions
*/
static void Bluetooth_bt_socket_connection_requested_cb_p(int socket_fd, const char *remote_address, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked for socket connection requested\\n", __LINE__, API_NAMESPACE);
	FPRINTF("[Line : %d][%s] Socket FD value: %d\\n", __LINE__, API_NAMESPACE, socket_fd);
	FPRINTF("[Line : %d][%s] Remote address: %s\\n", __LINE__, API_NAMESPACE, remote_address);
}

/**
* @brief Callback funtions
*/
static void Bluetooth_bt_socket_data_received_cb_p(bt_socket_received_data_s *pData, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked for socket data received\\n", __LINE__, API_NAMESPACE);

	if ( pData != NULL )
	{
		FPRINTF("[Line : %d][%s] Socketfd value: %d\\n", __LINE__, API_NAMESPACE, pData->socket_fd);
		FPRINTF("[Line : %d][%s] Data size: %d\\n", __LINE__, API_NAMESPACE, pData->data_size);
		FPRINTF("[Line : %d][%s] Data : %s\\n", __LINE__, API_NAMESPACE, pData->data);
	}
}


//Bluetooth Socket Callbacks

/**
* @brief Callback funtions
*/
static void Bluetooth_socket_connection_state_changed_cb_p(int result, bt_socket_connection_state_e connection_state, bt_socket_connection_s *connection, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked for socket connection state change\\n", __LINE__, API_NAMESPACE);
	if ( connection_state == BT_SOCKET_CONNECTED )
	{
		if ( result == BT_ERROR_NONE )
		{
			g_bCallbackResult = true;
			g_nBluetoothSocketFd = connection->socket_fd;
			FPRINTF("[Line : %d][%s] Callback (CONNECTED): socket_fd = %d\\n", __LINE__, API_NAMESPACE, g_nBluetoothSocketFd);
			if ( g_pMainLoop )
			{
				g_main_loop_quit(g_pMainLoop);
			}
		}
	}
	else if ( connection_state == BT_SOCKET_DISCONNECTED )
	{
		if ( result == BT_ERROR_NONE )
		{
			g_bCallbackResult = true;
			g_nBluetoothSocketFd = connection->socket_fd;
			FPRINTF("[Line : %d][%s] Callback (DISCONNECTED): socket_fd = %d\\n", __LINE__, API_NAMESPACE, g_nBluetoothSocketFd);
			if ( g_pMainLoop )
			{
				g_main_loop_quit(g_pMainLoop);
			}
		}
	}
}

/**
* @function 		ITs_bluetooth_socket_startup
* @description	 	Called before each test, Bluetooth is initialized
* @parameter		NA
* @return 			NA
*/
void ITs_bluetooth_socket_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Bluetooth_p\\n", __LINE__, API_NAMESPACE);
#endif

#if (defined(MOBILE) || defined(WEARABLE)  || defined(TIZENIOT)) //Starts MOBILE or WEARABLE or TIZENIOT
	g_bBluetoothIsSupported = TCTCheckSystemInfoFeatureSupported(BLUETOOTH_FEATURE, API_NAMESPACE);
#else
	g_bBluetoothIsSupported = true;
#endif  // End MOBILE or WEARABLE or TIZENIOT

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
* @function 		ITs_bluetooth_socket_cleanup
* @description	 	Called after each test, Bluetooth is de-initialized
* @parameter		NA
* @return 			NA
*/
void ITs_bluetooth_socket_cleanup(void)
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

//& purpose: Registers a RFCOMM socket with a specific UUID
//& type: auto
/**
* @testcase 			ITc_bluetooth_socket_bt_socket_create_destroy_rfcomm_p
* @since_tizen			2.3
* @type 				auto
* @description			Registers a RFCOMM socket with a specific UUID
* @scenario				Create a RFCOMM socket\n
*						Destroy RFCOMM socket
* @apicovered			bt_socket_create_rfcomm and bt_socket_destroy_rfcomm
* @passcase				When bt_socket_create_rfcomm and bt_socket_destroy_rfcomm are successful.
* @failcase				If targest APIs bt_socket_create_rfcomm or bt_socket_destroy_rfcomm fails.
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_socket_bt_socket_create_destroy_rfcomm_p(void)
{
	START_TEST;
	int nSocketFd = -1;
	int nRetVal = bt_socket_create_rfcomm(BLUETOOTH_SPP_UUID, &nSocketFd);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_socket_create_rfcomm", BluetoothGetError(nRetVal));
	FPRINTF("[Line : %d][%s] Socketfd is: %d\\n", __LINE__, API_NAMESPACE, nSocketFd);
	nRetVal = bt_socket_destroy_rfcomm(nSocketFd);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_socket_destroy_rfcomm", BluetoothGetError(nRetVal));
	return 0;
}


//& purpose: Starts listening on passed RFCOMM socket and accepts connection requests.
//& type: auto
/**
* @testcase 			ITc_bluetooth_socket_bt_socket_listen_and_accept_rfcomm_p
* @since_tizen			2.3
* @type 				auto
* @description			Starts listening on passed RFCOMM socket and accepts connection requests.
* @scenario				Create a RFCOMM socket
*						Starts listening on passed RFCOMM socket and accepts connection requests
*						Destroy RFCOMM socket
* @apicovered			bt_socket_create_rfcomm, bt_socket_destroy_rfcomm and bt_socket_listen_and_accept_rfcomm
* @passcase				When bt_socket_listen_and_accept_rfcomm is successful.
* @failcase				If targest API bt_socket_listen_and_accept_rfcomm fails.
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_socket_bt_socket_listen_and_accept_rfcomm_p(void)
{
	START_TEST;

	int nTimeoutId = 0;
	int nSocketFd = -1;
	int nMaxConnections = 2;

	int nRetVal = bt_socket_create_rfcomm(BLUETOOTH_SPP_UUID, &nSocketFd);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_socket_create_rfcomm", BluetoothGetError(nRetVal));
	WAIT(SHORT_DELAY);

	nRetVal = bt_socket_listen_and_accept_rfcomm(nSocketFd, nMaxConnections);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_socket_listen_and_accept_rfcomm", BluetoothGetError(nRetVal), bt_socket_destroy_rfcomm(nSocketFd));

	nRetVal = bt_socket_destroy_rfcomm(nSocketFd);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_socket_destroy_rfcomm", BluetoothGetError(nRetVal));
	return 0;
}



//& purpose: Registers a callback function that will be invoked when a RFCOMM connection is requested and unregister callback
//& type: auto
/**
* @testcase 			ITc_bluetooth_socket_bt_socket_set_unset_connection_requested_cb_p
* @since_tizen			2.3
* @type 				auto
* @description			Registers a callback function that will be invoked when a RFCOMM connection is requested and unregister callback
* @scenario				Set callback\n
*						Unset callback
* @apicovered			bt_socket_set_connection_requested_cb and bt_socket_unset_connection_requested_cb
* @passcase				When bt_socket_set_connection_requested_cb and bt_socket_unset_connection_requested_cb is successful
* @failcase				If targest API bt_socket_set_connection_requested_cb or bt_socket_unset_connection_requested_cb fails
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_socket_bt_socket_set_unset_connection_requested_cb_p(void)
{
	START_TEST;
	int nRetVal = bt_socket_set_connection_requested_cb(Bluetooth_bt_socket_connection_requested_cb_p, NULL);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_socket_set_connection_requested_cb", BluetoothGetError(nRetVal));
	nRetVal = bt_socket_unset_connection_requested_cb();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_socket_unset_connection_requested_cb", BluetoothGetError(nRetVal));
	return 0;
}

//& purpose: Registers a callback function that will be invoked when data is received and unregister the callback
//& type: auto
/**
* @testcase 			ITc_bluetooth_socket_bt_socket_set_unset_data_received_cb_p
* @since_tizen			2.3
* @type 				auto
* @description			Registers a callback function that will be invoked when data is received and unregister the callback
* @scenario				Set callback\n
*						Unset callback
* @apicovered			bt_socket_set_data_received_cb and bt_socket_unset_data_received_cb
* @passcase				When bt_socket_set_data_received_cb and bt_socket_unset_data_received_cb is successful
* @failcase				If targest API bt_socket_set_data_received_cb or bt_socket_unset_data_received_cb fails
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_socket_bt_socket_set_unset_data_received_cb_p(void)
{
	START_TEST;
	int nRetVal = bt_socket_set_data_received_cb(Bluetooth_bt_socket_data_received_cb_p, NULL);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_socket_set_data_received_cb", BluetoothGetError(nRetVal));
	nRetVal = bt_socket_unset_data_received_cb();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_socket_unset_data_received_cb", BluetoothGetError(nRetVal));
	return 0;
}




//& purpose: Registers a callback function that will be invoked when the connection state changes and Unregister
//& type: auto
/**
* @testcase 			ITc_bluetooth_socket_bt_socket_set_unset_connection_state_changed_cb_p
* @since_tizen			2.3
* @type 				auto
* @description			Registers a callback function that will be invoked when the connection state changes and Unregister
* @scenario				Register callback for socket connection state change\n
*						Unregister the callback
* @apicovered			bt_socket_set_connection_state_changed_cb and bt_socket_unset_connection_state_changed_cb
* @passcase				When bt_socket_set_connection_state_changed_cb and bt_socket_unset_connection_state_changed_cb is successful
* @failcase				If targest APIs bt_socket_set_connection_state_changed_cb or bt_socket_unset_connection_state_changed_cb fails
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_socket_bt_socket_set_unset_connection_state_changed_cb_p(void)
{
	START_TEST;
	int nRetVal = bt_socket_set_connection_state_changed_cb(Bluetooth_socket_connection_state_changed_cb_p, "SocketConnectionChange");
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_socket_set_connection_state_changed_cb", BluetoothGetError(nRetVal));
	nRetVal = bt_socket_unset_connection_state_changed_cb();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_socket_unset_connection_state_changed_cb", BluetoothGetError(nRetVal));
	return 0;
}

/** @} */
/** @} */

