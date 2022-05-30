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



/**
* @brief Callback funtions
*/
static void Bluetooth_bt_audio_connection_state_changed_cb_p(int result, bool connected, const char *remote_address, bt_audio_profile_type_e type, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked: bt_audio_connection_state_changed\\n", __LINE__, API_NAMESPACE);
	switch ( type )
	{
	case BT_AUDIO_PROFILE_TYPE_ALL:
		FPRINTF("[Line : %d][%s] PROIFLE: BT_AUDIO_PROFILE_TYPE_ALL Profile\\n", __LINE__, API_NAMESPACE);
		break;
	case BT_AUDIO_PROFILE_TYPE_HSP_HFP:
		FPRINTF("[Line : %d][%s] PROIFLE: BT_AUDIO_PROFILE_TYPE_HSP_HFP Profile\\n", __LINE__, API_NAMESPACE);
		break;
	case BT_AUDIO_PROFILE_TYPE_A2DP :
		FPRINTF("[Line : %d][%s] PROIFLE: BT_AUDIO_PROFILE_TYPE_A2DP\\n", __LINE__, API_NAMESPACE);
		break;
	default:
		FPRINTF("[Line : %d][%s] PROIFLE: UNKNOWN\\n", __LINE__, API_NAMESPACE);
		break;
	}
	FPRINTF("[Line : %d][%s] RemoteAddress: %s\\n", __LINE__, API_NAMESPACE, remote_address);
	FPRINTF("[Line : %d][%s] Connected: %d\\n", __LINE__, API_NAMESPACE, connected);
	g_bCallbackResult = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}


/**
* @function 		ITs_bluetooth_audio_startup
* @description	 	Called before each test, Bluetooth is initialized
* @parameter		NA
* @return 			NA
*/
void ITs_bluetooth_audio_startup(void)
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

	if ( !TCTCheckSystemInfoFeatureSupported(BLUETOOTH_AUDIOMEDIA_FEATURE, API_NAMESPACE) && !TCTCheckSystemInfoFeatureSupported(BLUETOOTH_AUDIOCALL_FEATURE, API_NAMESPACE) )
	{
		g_bBluetoothIsAudioSupported = false;
	}
	else
	{
		g_bBluetoothIsAudioSupported = true;
	}
	return;
}

/**
* @function 		ITs_bluetooth_audio_cleanup
* @description	 	Called after each test, Bluetooth is de-initialized
* @parameter		NA
* @return 			NA
*/
void ITs_bluetooth_audio_cleanup(void)
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

/** @addtogroup itc-bluetooth
*  @ingroup itc
*  @{
*/

//& purpose: Initialize and Deinitialize the Bluetooth profile which is related with audio
//& type: auto
/**
* @testcase 			ITc_bluetooth_audio_bt_audio_initialize_deinitialize_p
* @since_tizen			2.3
* @type 				auto
* @description			Initialize and Deinitialize the Bluetooth profile which is related with audio
* @scenario				Initialize bluetooth audio profile
*						Deinitialize bluetooth audio profile
* @apicovered			bt_audio_initialize and bt_audio_deinitialize
* @passcase				When bt_audio_initialize and bt_audio_deinitialize is successful
* @failcase				If targest API bt_audio_initialize or bt_audio_deinitialize fails
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_audio_bt_audio_initialize_deinitialize_p(void)
{
	START_TEST;
	int nTimeoutId = 0;

	WAIT(SHORT_DELAY);
	int nRetVal = bt_audio_initialize();
	if ( !g_bBluetoothIsAudioSupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRetVal, "bt_audio_initialize", BluetoothGetError(nRetVal));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_audio_initialize", BluetoothGetError(nRetVal));
	WAIT(SHORT_DELAY);
	nRetVal = bt_audio_deinitialize();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_audio_deinitialize", BluetoothGetError(nRetVal));
	return 0;
}

//& purpose: Registers a callback function that will be invoked when the connection state is changed and Unregister the callback
//& type: auto
/**
* @testcase 			ITc_bluetooth_audio_bt_audio_set_unset_connection_state_changed_cb_p
* @since_tizen			2.3
* @type 				auto
* @description			Registers a callback function that will be invoked when the connection state is changed and Unregister the callback
* @scenario				Initialize bluetooth audio profile\n
*						Register connection state change callback\n
*						Unregister connection state change callback\n
*						Deinitialize bluetooth audio profile
* @apicovered			bt_audio_initialize, bt_audio_set_connection_state_changed_cb, bt_audio_unset_connection_state_changed_cb and bt_audio_deinitialize
* @passcase				When bt_audio_set_connection_state_changed_cb and bt_audio_unset_connection_state_changed_cb is successful
* @failcase				If bt_audio_set_connection_state_changed_cb or bt_audio_unset_connection_state_changed_cb fails
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_audio_bt_audio_set_unset_connection_state_changed_cb_p(void)
{
	START_TEST;

	int nRetVal = bt_audio_initialize();
	if ( !g_bBluetoothIsAudioSupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRetVal, "bt_audio_initialize", BluetoothGetError(nRetVal));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_audio_initialize", BluetoothGetError(nRetVal));

	nRetVal = bt_audio_set_connection_state_changed_cb(Bluetooth_bt_audio_connection_state_changed_cb_p, "AudioDeviceConnection");
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_audio_set_connection_state_changed_cb", BluetoothGetError(nRetVal),bt_audio_deinitialize());

	nRetVal = bt_audio_unset_connection_state_changed_cb();
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_audio_unset_connection_state_changed_cb", BluetoothGetError(nRetVal),bt_audio_deinitialize());

	nRetVal = bt_audio_deinitialize();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_audio_deinitialize", BluetoothGetError(nRetVal));
	return 0;
}

/** @} */
/** @} */