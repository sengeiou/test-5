//
// Copyright (c) 2022 Samsung Electronics Co., Ltd.
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

int g_nL2cap_test_psm = 37;
int g_nSocketFd = 0;
bool g_bBtLeCocFeature = false;
bool g_bL2cap_channel = false;
bool g_bL2cap_FeatureError = false;
/**
* @brief Callback funtions
*/

static void Bluetooth_socket_connection_requested_cb(int socket_fd, const char *remote_address, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked for connection request.\\n", __LINE__, API_NAMESPACE);
}


static void Bluetooth_socket_l2cap_channel_connection_state_changed_cb(int result, bt_socket_connection_state_e connection_state, bt_socket_l2cap_le_connection_s *connection, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked for connection state change\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ITs_bluetooth_l2cap_channel_startup
* @description	Called before each test, Bluetooth is initialized
* @parameter		NA
* @return 			NA
*/
void ITs_bluetooth_l2cap_channel_startup(void)
{
	struct stat stBuff;
	int nBtLeFeature = false;
    g_bL2cap_FeatureError = false;
    g_bL2cap_channel = false;

	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Bluetooth_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bBluetoothIsSupported = TCTCheckSystemInfoFeatureSupported(BLUETOOTH_FEATURE, API_NAMESPACE);
	nBtLeFeature = TCTCheckSystemInfoFeatureSupported(BLUETOOTH_LE_FEATURE, API_NAMESPACE);
	g_bBtLeCocFeature = TCTCheckSystemInfoFeatureSupported(BLUETOOTH_LE_COC_FEATURE, API_NAMESPACE);

	int nRetVal = bt_initialize();
	if ( (false == g_bBluetoothIsSupported) || (false == nBtLeFeature) )
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
		return;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Bluetooth initialized successfully\\n", __LINE__, API_NAMESPACE);
		g_bBluetoothInit = true;
	}

	bt_adapter_state_e adapter_state = BT_ADAPTER_DISABLED;
	nRetVal = bt_adapter_get_state(&adapter_state);
	if (adapter_state != BT_ADAPTER_ENABLED)
	{
			FPRINTF("[Line : %d][%s] Bluetooth adaptor is not enabled.\\n", __LINE__, API_NAMESPACE);
			g_bBluetoothInit = false;
	}

        nRetVal = bt_socket_create_l2cap_channel(g_nL2cap_test_psm, &g_nSocketFd);
        if ( false == g_bBtLeCocFeature )
        {
		if ( nRetVal != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature is not supported, bt_socket_create_l2cap_channel API didn't returned TIZEN_ERROR_NOT_SUPPORTED error code.\\n", __LINE__, API_NAMESPACE);
			g_bL2cap_FeatureError =  true;
		}
		else
			FPRINTF("[Line : %d][%s] Feature is not supported, bt_socket_create_l2cap_channel API returned TIZEN_ERROR_NOT_SUPPORTED error code.\\n", __LINE__, API_NAMESPACE);

		return;
        }

	if ( nRetVal != BT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] bt_socket_create_l2cap_channel API failed, error returned = %s\\n", __LINE__, API_NAMESPACE, BluetoothGetError(nRetVal));
	}
	else
	{
		FPRINTF("[Line : %d][%s] bt_socket_create_l2cap_channel API success.\\n", __LINE__, API_NAMESPACE);
		FPRINTF("[Line : %d][%s] Socket ID is: %d\\n", __LINE__, API_NAMESPACE, g_nSocketFd);
		g_bL2cap_channel = true;
	}

	return;
}

/**
* @function 		ITs_bluetooth_l2cap_channel_cleanup
* @description	Called after each test, Bluetooth is de-initialized
* @parameter		NA
* @return 			NA
*/
void ITs_bluetooth_l2cap_channel_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Bluetooth_p\\n", __LINE__, API_NAMESPACE);
#endif
    int nRetVal = -1;

	if ( g_bL2cap_channel == true )
	{
		nRetVal = bt_socket_destroy_l2cap_channel(g_nSocketFd);
	    PRINT_RESULT_NORETURN(BT_ERROR_NONE, nRetVal, "bt_socket_destroy_l2cap_channel", BluetoothGetError(nRetVal));
	}

	if ( g_bBluetoothInit )
	{
		nRetVal = bt_deinitialize();
		if ( nRetVal != BT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Bluetooth de-initialization failed, error returned = %s\\n", __LINE__, API_NAMESPACE, BluetoothGetError(nRetVal));
		}
		else
		{
			FPRINTF("[Line : %d][%s] Bluetooth de-initialized successfully\\n", __LINE__, API_NAMESPACE);
		}
	}

	return;
}


//& purpose: Create and Destroy l2 Cap channel
//& type: auto
/**
* @testcase 				ITc_bluetooth_bt_socket_create_destroy_l2cap_channel_p
* @since_tizen			7.0
* @type 					auto
* @description			Create l2 Cap channel if bluetooth is supported and initialized and destroy
* @scenario				Create l2 Cap channel \n
*								Destroy RFCOMM socket
* @apicovered			bt_socket_create_l2cap_channel and bt_socket_destroy_l2cap_channel
* @passcase				When bt_socket_create_l2cap_channel and bt_socket_destroy_l2cap_channel are successful.
* @failcase					If targest APIs bt_socket_create_l2cap_channel or bt_socket_destroy_l2cap_channel fails.
* @precondition			Bluetooth must be initialized and adaptor must be enabled
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_bt_socket_create_destroy_l2cap_channel_p(void)
{
	START_TEST;
	int nRetVal = -1;

	CHECK_LE_COC_FEATURE_ERROR;

	nRetVal = bt_socket_destroy_l2cap_channel(g_nSocketFd);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_socket_destroy_l2cap_channel", BluetoothGetError(nRetVal));

	nRetVal = bt_socket_create_l2cap_channel(g_nL2cap_test_psm, &g_nSocketFd);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_socket_create_l2cap_channel", BluetoothGetError(nRetVal));
	FPRINTF("[Line : %d][%s] Socket ID is: %d\\n", __LINE__, API_NAMESPACE, g_nSocketFd);

	nRetVal = bt_socket_destroy_l2cap_channel(g_nSocketFd);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_socket_destroy_l2cap_channel", BluetoothGetError(nRetVal));

	nRetVal = bt_socket_create_l2cap_channel(g_nL2cap_test_psm, &g_nSocketFd);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_socket_create_l2cap_channel", BluetoothGetError(nRetVal));
	FPRINTF("[Line : %d][%s] Socket ID is: %d\\n", __LINE__, API_NAMESPACE, g_nSocketFd);

	return 0;
}



//& purpose: Listen and Accept l2 Cap channel
//& type: auto
/**
* @testcase 				ITc_bluetooth_bt_socket_listen_and_accept_l2cap_channel_p
* @since_tizen			7.0
* @type 					auto
* @description			listen l2 Cap channel if bluetooth is supported and initialized and accept
* @scenario				Listen l2 Cap channel \n
*								Accept RFCOMM socket
* @apicovered			bt_socket_listen_and_accept_l2cap_channel
* @passcase				When bt_socket_listen_and_accept_l2cap_channel is successful.
* @failcase					If targest API bt_socket_listen_and_accept_l2cap_channel fails.
* @precondition			Bluetooth must be initialized and adaptor must be enabled
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_bt_socket_listen_and_accept_l2cap_channel_p(void)
{
	START_TEST;
	int nRetVal = -1;

	CHECK_LE_COC_FEATURE_ERROR;

	nRetVal = bt_socket_listen_and_accept_l2cap_channel(g_nSocketFd, 1);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_socket_listen_and_accept_l2cap_channel", BluetoothGetError(nRetVal), bt_socket_destroy_l2cap_channel(g_nSocketFd));

	return 0;
}


//& purpose: Get l2 Cap psm
//& type: auto
/**
* @testcase 				ITc_bluetooth_bt_socket_get_l2cap_psm_p
* @since_tizen			7.0
* @type 					auto
* @description			Get l2 Cap psm if bluetooth is supported and initialized
* @scenario				Get l2 Cap psm
* @apicovered			bt_socket_get_l2cap_psm
* @passcase				When bt_socket_get_l2cap_psm is successful.
* @failcase					If targest API bt_socket_get_l2cap_psm fails.
* @precondition			Bluetooth must be initialized and adaptor must be enabled
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_bt_socket_get_l2cap_psm_p(void)
{
	START_TEST;
	int nRetVal = -1;
	int nPsm = -1;

	CHECK_LE_COC_FEATURE_ERROR;

	nRetVal = bt_socket_listen_and_accept_l2cap_channel(g_nSocketFd, 1);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_socket_listen_and_accept_l2cap_channel", BluetoothGetError(nRetVal), bt_socket_destroy_l2cap_channel(g_nSocketFd));

	nRetVal = bt_socket_get_l2cap_psm(g_nSocketFd, &nPsm);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_socket_get_l2cap_psm", BluetoothGetError(nRetVal), bt_socket_destroy_l2cap_channel(g_nSocketFd));

	return 0;
}


//& purpose: listen for l2cap connection
//& type: auto
/**
* @testcase 				ITc_bluetooth_bt_socket_listen_l2cap_channel_p
* @since_tizen			7.0
* @type 					auto
* @description			listen for l2cap connection if bluetooth is supported and initialized
* @scenario				listen for l2cap connection
* @apicovered			bt_socket_listen_l2cap_channel
* @passcase				When bt_socket_listen_l2cap_channel is successful.
* @failcase					If targest API bt_socket_listen_l2cap_channel fails.
* @precondition			Bluetooth must be initialized and adaptor must be enabled
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_bt_socket_listen_l2cap_channel_p(void)
{
	START_TEST;
	int nRetVal = -1;
	int nPsm = -1;

	CHECK_LE_COC_FEATURE_ERROR;

	nRetVal = bt_socket_listen_l2cap_channel(g_nSocketFd, 1);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_socket_listen_l2cap_channel", BluetoothGetError(nRetVal), bt_socket_destroy_l2cap_channel(g_nSocketFd));

	return 0;
}


//& purpose: Set and Unset connection requested callback
//& type: auto
/**
* @testcase 				ITc_bluetooth_bt_socket_set_unset_l2cap_channel_connection_requested_cb_p
* @since_tizen			7.0
* @type 					auto
* @description			Set and Unset connection requested callback if bluetooth is supported and initialized
* @scenario				Set connection requested callback\n
*								Unset connection requested callback\n
* @apicovered			bt_socket_set_l2cap_channel_connection_requested_cb and bt_socket_unset_l2cap_channel_connection_requested_cb
* @passcase				When bt_socket_set_l2cap_channel_connection_requested_cb and bt_socket_unset_l2cap_channel_connection_requested_cb is successful.
* @failcase					If targest API bt_socket_set_l2cap_channel_connection_requested_cb Or bt_socket_unset_l2cap_channel_connection_requested_cb fails.
* @precondition			Bluetooth must be initialized and adaptor must be enabled
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_bt_socket_set_unset_l2cap_channel_connection_requested_cb_p(void)
{
	START_TEST;
	int nRetVal = -1;
	int nPsm = -1;

	CHECK_LE_COC_FEATURE_ERROR;

	nRetVal = bt_socket_set_l2cap_channel_connection_requested_cb(Bluetooth_socket_connection_requested_cb, NULL);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_socket_set_l2cap_channel_connection_requested_cb", BluetoothGetError(nRetVal), bt_socket_destroy_l2cap_channel(g_nSocketFd));

	nRetVal = bt_socket_unset_l2cap_channel_connection_requested_cb();
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_socket_unset_l2cap_channel_connection_requested_cb", BluetoothGetError(nRetVal), bt_socket_destroy_l2cap_channel(g_nSocketFd));

	return 0;
}



//& purpose: Set and Unset connection state changed callback
//& type: auto
/**
* @testcase 				ITc_bluetooth_bt_socket_set_unset_l2cap_channel_connection_state_changed_cb_p
* @since_tizen			7.0
* @type 					auto
* @description			Set and Unset connection state changed callback if bluetooth is supported and initialized
* @scenario				Set connection state changed callback\n
*								Unset connection state changed callback\n
* @apicovered			bt_socket_set_l2cap_channel_connection_state_changed_cb and bt_socket_unset_l2cap_channel_connection_state_changed_cb
* @passcase				When bt_socket_set_l2cap_channel_connection_state_changed_cb and bt_socket_unset_l2cap_channel_connection_state_changed_cb is successful.
* @failcase					If targest API bt_socket_set_l2cap_channel_connection_state_changed_cb Or bt_socket_unset_l2cap_channel_connection_state_changed_cb fails.
* @precondition			Bluetooth must be initialized and adaptor must be enabled
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_bt_socket_set_unset_l2cap_channel_connection_state_changed_cb_p(void)
{
	START_TEST;
	int nRetVal = -1;
	int nPsm = -1;

	CHECK_LE_COC_FEATURE_ERROR;

	nRetVal = bt_socket_set_l2cap_channel_connection_state_changed_cb(Bluetooth_socket_l2cap_channel_connection_state_changed_cb, NULL);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_socket_set_l2cap_channel_connection_state_changed_cb", BluetoothGetError(nRetVal), bt_socket_destroy_l2cap_channel(g_nSocketFd));

	nRetVal = bt_socket_unset_l2cap_channel_connection_state_changed_cb();
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_socket_unset_l2cap_channel_connection_state_changed_cb", BluetoothGetError(nRetVal), bt_socket_destroy_l2cap_channel(g_nSocketFd));

	return 0;
}

/** @} */
/** @} */

