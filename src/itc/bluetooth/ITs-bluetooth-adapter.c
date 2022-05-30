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

//& set: Bluetooth
static bool g_bReturnValueState = false;
static bool g_bAdapterState = false;
char g_pszLocalAdapterName[ADAPTER_NAME_LENGTH];
int g_nBluetoothSocketFd;

static GMainLoop *mainloop = NULL;

/**
* @brief Callback funtions
*/
static void Bluetooth_adapter_state_changed_cb_p(int nResult, bt_adapter_state_e adapter_state, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked for Adapter state change\\n", __LINE__, API_NAMESPACE);
	FPRINTF("[Line : %d][%s] Result value: %d\\n", __LINE__, API_NAMESPACE, nResult);

	g_bReturnValueState = false;

	switch ( adapter_state )
	{
	case BT_ADAPTER_ENABLED:
		FPRINTF("[Line : %d][%s] Adapter State: BT_ADAPTER_ENABLED\\n", __LINE__, API_NAMESPACE);
		if (g_bAdapterState == true)
		{
			g_bReturnValueState = true;
		}
		break;
	case BT_ADAPTER_DISABLED:
		FPRINTF("[Line : %d][%s] Adapter State: BT_ADAPTER_DISABLED\\n", __LINE__, API_NAMESPACE);
		if (g_bAdapterState == false)
		{
			g_bReturnValueState = true;
		}
		break;
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
static void Bluetooth_adapter_visibility_mode_changed_cb_p(int result, bt_adapter_visibility_mode_e visibility_mode, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked for Adapter visibility mode change\\n", __LINE__, API_NAMESPACE);
	FPRINTF("[Line : %d][%s] Result value: %d\\n", __LINE__, API_NAMESPACE,  result);
	g_bReturnValueState = false;

	switch ( visibility_mode )
	{
	case BT_ADAPTER_VISIBILITY_MODE_NON_DISCOVERABLE:
		FPRINTF("[Line : %d][%s] Adapter Visibility mode: %s\\n", __LINE__, API_NAMESPACE, "BT_ADAPTER_VISIBILITY_MODE_NON_DISCOVERABLE");
		g_bReturnValueState = true;
		break;
	case BT_ADAPTER_VISIBILITY_MODE_GENERAL_DISCOVERABLE:
		FPRINTF("[Line : %d][%s] Adapter Visibility mode: %s\\n", __LINE__, API_NAMESPACE, "BT_ADAPTER_VISIBILITY_MODE_GENERAL_DISCOVERABLE");
		g_bReturnValueState = true;
		break;
	case BT_ADAPTER_VISIBILITY_MODE_LIMITED_DISCOVERABLE:
		FPRINTF("[Line : %d][%s] Adapter Visibility mode: %s\\n", __LINE__, API_NAMESPACE, "BT_ADAPTER_VISIBILITY_MODE_LIMITED_DISCOVERABLE");
		g_bReturnValueState = true;
		break;
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
static void Bluetooth_bt_adapter_name_changed_cb_p(char *pszDeviceName, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked for adapter name change\\n", __LINE__, API_NAMESPACE);
	g_bReturnValueState = false;

	if ( strcmp(g_pszLocalAdapterName, pszDeviceName) == 0 )
	{
		g_bReturnValueState = true;
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
static void Bluetooth_bt_adapter_visibility_duration_changed_cb_p(int nDuration, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked for adapter visibility duration change\\n", __LINE__, API_NAMESPACE);
	FPRINTF("[Line : %d][%s] Duration value: %d\\n", __LINE__, API_NAMESPACE, nDuration);

	g_bCallbackResult = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}


/**
* @brief Callback funtions
*/
static void Bluetooth_adapter_device_discovery_state_changed_cb_p(int result, bt_adapter_device_discovery_state_e discovery_state, bt_adapter_device_discovery_info_s *discovery_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked for device discovery state change\\n", __LINE__, API_NAMESPACE);
	FPRINTF("[Line : %d][%s] Result value: %d\\n", __LINE__, API_NAMESPACE, result);
	g_bReturnValueState = false;

	switch ( discovery_state )
	{
	case BT_ADAPTER_DEVICE_DISCOVERY_STARTED:
		FPRINTF("[Line : %d][%s] Device discovery state: %s\\n", __LINE__, API_NAMESPACE, "BT_ADAPTER_DEVICE_DISCOVERY_STARTED");
		g_bReturnValueState = true;
		break;
	case BT_ADAPTER_DEVICE_DISCOVERY_FINISHED:
		FPRINTF("[Line : %d][%s] Device discovery state: %s\\n", __LINE__, API_NAMESPACE, "BT_ADAPTER_DEVICE_DISCOVERY_FINISHED");
		g_bReturnValueState = true;
		break;
	case BT_ADAPTER_DEVICE_DISCOVERY_FOUND:
		{
			FPRINTF("[Line : %d][%s] Device discovery state: %s\\n", __LINE__, API_NAMESPACE, "BT_ADAPTER_DEVICE_DISCOVERY_FOUND");
			if ( discovery_info != NULL )
			{
				FPRINTF("[Line : %d][%s] Remote Address: %s\\n", __LINE__, API_NAMESPACE, discovery_info->remote_address);
				FPRINTF("[Line : %d][%s] Remote Name: %s\\n", __LINE__, API_NAMESPACE, discovery_info->remote_name);
				g_bReturnValueState = true;
			}
			else
			{
				g_bReturnValueState = false;
			}
		}
		break;
	}

	g_bCallbackResult = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

static gboolean timeout_func(gpointer data)
{
    g_main_loop_quit((GMainLoop *)data);
    return FALSE;
}

static void wait_for_async()
{
    int timeout_id = 0;
    mainloop = g_main_loop_new(NULL, FALSE);

    timeout_id = g_timeout_add(1000, timeout_func, mainloop);
    g_main_loop_run(mainloop);
    g_source_remove(timeout_id);
}

/**
* @function 		ITs_bluetooth_startup
* @description	 	Called before each test, Bluetooth is initialized
* @parameter		NA
* @return 			NA
*/
void ITs_bluetooth_startup(void)
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
	g_bBluetoothIsOOBSupported = TCTCheckSystemInfoFeatureSupported(BLUETOOTH_OOB_FEATURE, API_NAMESPACE);
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
* @function 		ITs_bluetooth_cleanup
* @description	 	Called after each test, Bluetooth is de-initialized
* @parameter		NA
* @return 			NA
*/
void ITs_bluetooth_cleanup(void)
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

/** @addtogroup itc-bluetooth-testcases
*  @brief 		Integration testcases for module bluetooth
*  @ingroup 	itc-bluetooth
*  @{
*/

/**
* @testcase 			ITc_bluetooth_adapter_bt_adapter_set_get_name_p
* @since_tizen			2.3
* @type 				auto
* @description			Set and Get the name of the local Bluetooth adapter.
* @scenario				Register name change callback\n
*						Set the name of the local Bluetooth adapter. \n
*						Check callback\n
*						Get the name of the local Bluetooth adapter. \n
*						Unregister name change callback
* @apicovered			bt_adapter_set_name, bt_adapter_get_name
* @passcase				When bt_adapter_set_name and bt_adapter_get_name is successful and both set and get values matches.
* @failcase				If targest APIs bt_adapter_set_name or bt_adapter_get_name fails or set and get values doesn't match.
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_adapter_bt_adapter_set_get_name_p(void)
{
	START_TEST;
	char pszSetLocalName[ADAPTER_NAME_LENGTH] = {0};
	char* pszGetLocalName = NULL;
	char* pszTempGetLocalName = NULL;

	int nRetVal = bt_adapter_get_name(&pszTempGetLocalName);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_get_name", BluetoothGetError(nRetVal));
	CHECK_HANDLE(pszTempGetLocalName,"bt_adapter_get_name");

	snprintf(pszSetLocalName, ADAPTER_NAME_LENGTH, "%s0", ADAPTER_NAME);
	if ( pszTempGetLocalName != NULL )
	{
		if ( strcmp(pszSetLocalName, pszTempGetLocalName) == 0 )
		{
			snprintf(pszSetLocalName, ADAPTER_NAME_LENGTH, "%s00", ADAPTER_NAME);
		}
	}
	
	nRetVal = bt_adapter_set_name(pszSetLocalName);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_adapter_set_name", BluetoothGetError(nRetVal),FREE_MEMORY(pszTempGetLocalName));

	wait_for_async();
	
	nRetVal =  bt_adapter_get_name(&pszGetLocalName);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_adapter_get_name", BluetoothGetError(nRetVal), FREE_MEMORY(pszTempGetLocalName));
	if ( strcmp(pszSetLocalName, pszGetLocalName) != 0 )
	{
		FPRINTF("[Line : %d][%s] Set and Get values mismatch. Set value is: %s, Get value is: %s\\n", __LINE__, API_NAMESPACE, pszSetLocalName, pszGetLocalName);
		FREE_MEMORY(pszGetLocalName);
		FREE_MEMORY(pszTempGetLocalName)
		return 1;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Set Adapter name is: %s\\n", __LINE__, API_NAMESPACE, pszSetLocalName);
		FPRINTF("[Line : %d][%s] Get Adapter name is: %s\\n", __LINE__, API_NAMESPACE, pszGetLocalName);
		FREE_MEMORY(pszGetLocalName);
	}

	if ( pszTempGetLocalName != NULL )
	{
		nRetVal = bt_adapter_set_name(pszTempGetLocalName);
		PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_adapter_set_name", BluetoothGetError(nRetVal), FREE_MEMORY(pszTempGetLocalName));
		FREE_MEMORY(pszTempGetLocalName);
	}
	return 0;
}


//& purpose: Register and unregister a callback function to be invoked when the name of Bluetooth adapter changes.
//& type: auto
/**
* @testcase 			ITc_bluetooth_adapter_bt_adapter_set_unset_name_changed_cb_p
* @since_tizen			2.3
* @type 				auto
* @description			Register and unregister callback function to be invoked when the name of Bluetooth adapter changes.
* @scenario				Register a callback function to be invoked when the name of Bluetooth adapter changes.\n
*						Set Bluetooth adapter name\n
*						Check, whether callback is invoked or not\n
*						Unregister the callback\n
*						Set Bluetooth adapter name.\n
*						Check, whether callback is invoked or not
* @apicovered			bt_adapter_set_name_changed_cb, bt_adapter_set_name and bt_adapter_unset_name_changed_cb
* @passcase				When bt_adapter_set_name_changed_cb is successful and callback is invoked and\n
*						When bt_adapter_unset_name_changed_cb is successful and callback is not invoked
* @failcase				If targest APIs bt_adapter_set_name_changed_cb fails or callback is not invoked or\n
*						If bt_adapter_unset_name_changed_cb fails or callback is invoked
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_adapter_bt_adapter_set_unset_name_changed_cb_p(void)
{
	START_TEST;

	int nTimeoutId = 0;
	char pszSetLocalName[ADAPTER_NAME_LENGTH] = {0};
	char* pszTempGetLocalName = NULL;
	g_pMainLoop = g_main_loop_new(NULL, false);

	int nRetVal = bt_adapter_get_name(&pszTempGetLocalName);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_get_name", BluetoothGetError(nRetVal));

	memset(g_pszLocalAdapterName, '\0', sizeof(g_pszLocalAdapterName));
	g_bReturnValueState = false;
	g_bCallbackResult = false;
	snprintf(pszSetLocalName, ADAPTER_NAME_LENGTH, "%s0", ADAPTER_NAME);
	if ( pszTempGetLocalName != NULL )
	{
		if ( strcmp(pszSetLocalName, pszTempGetLocalName) == 0 )
		{
			snprintf(pszSetLocalName, ADAPTER_NAME_LENGTH, "%s00", ADAPTER_NAME);
		}
	}

	strncpy(g_pszLocalAdapterName, pszSetLocalName, ADAPTER_NAME_LENGTH);
	nRetVal = bt_adapter_set_name_changed_cb(Bluetooth_bt_adapter_name_changed_cb_p, NULL);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_adapter_set_name_changed_cb", BluetoothGetError(nRetVal),FREE_MEMORY(pszTempGetLocalName));

	nRetVal = bt_adapter_set_name(pszSetLocalName);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_adapter_set_name", BluetoothGetError(nRetVal),FREE_MEMORY(pszTempGetLocalName));
	CHECK_CALLBACK_STATUS("bt_adapter_set_name_changed_cb");
	if ( g_bReturnValueState == false )
	{
		FPRINTF("[Line : %d][%s] After 'bt_adapter_set_name' API, Bluetooth_adapter_state_changed_cb_p callback is failed. Callback returned invalid value\\n", __LINE__, API_NAMESPACE);
		nRetVal = bt_adapter_unset_name_changed_cb();
		PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_adapter_unset_name_changed_cb", BluetoothGetError(nRetVal),FREE_MEMORY(pszTempGetLocalName));
		FREE_MEMORY(pszTempGetLocalName);
		return 1;
	}

	nRetVal = bt_adapter_unset_name_changed_cb();
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_adapter_unset_name_changed_cb", BluetoothGetError(nRetVal),FREE_MEMORY(pszTempGetLocalName));
	g_bCallbackResult = false;

	nRetVal = bt_adapter_set_name(pszSetLocalName);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_set_name", BluetoothGetError(nRetVal));
	CHECK_UNSET_CALLBACK_STATUS(LONG_DELAY, "bt_adapter_unset_name_changed_cb");

	if ( pszTempGetLocalName != NULL )
	{
		nRetVal = bt_adapter_set_name(pszTempGetLocalName);
		if ( nRetVal != BT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] bt_adapter_set_name failed after for loop, error returned = %s\\n", __LINE__, API_NAMESPACE, BluetoothGetError(nRetVal));
			FREE_MEMORY(pszTempGetLocalName);
			return 1;
		}
		FREE_MEMORY(pszTempGetLocalName);
	}
	return 0;
}

//& purpose: Get the visibility mode of the local Bluetooth adapter
//& type: auto
/**
* @testcase 			ITc_bluetooth_adapter_bt_adapter_get_visibility_p
* @since_tizen			2.3
* @type 				auto
* @description			Get the visibility mode of the local Bluetooth adapter.
* @scenario				Get the visibility mode of the local Bluetooth adapter
* @apicovered			bt_adapter_get_visibility
* @passcase				When bt_adapter_get_visibility is successful
* @failcase				If targest API bt_adapter_get_visibility fails
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_adapter_bt_adapter_get_visibility_p(void)
{
	START_TEST;

	int nGetDuration = 0;
	bt_adapter_visibility_mode_e get_discoverable_mode;

	int nRetVal = bt_adapter_get_visibility(&get_discoverable_mode, &nGetDuration);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_get_visibility", BluetoothGetError(nRetVal));
	FPRINTF("[Line : %d][%s] Discoverable Mode: %s\\n", __LINE__, API_NAMESPACE, BluetoothGetEnumString(get_discoverable_mode));
	FPRINTF("[Line : %d][%s] Duration: %d\\n", __LINE__, API_NAMESPACE, nGetDuration);
	return 0;
}

//& purpose: Checks if the device discovery is in progress or not
//& type: auto
/**
* @testcase 			ITc_bluetooth_adapter_bt_adapter_is_discovering_p
* @since_tizen			2.3
* @type 				auto
* @description			Checks if the device discovery is in progress or not.
* @scenario				Start device discovery\n
*						Checks if the device discovery is in progress or not\n
*						Stop device discovery
* @apicovered			bt_adapter_start_device_discovery, bt_adapter_is_discovering and bt_adapter_stop_device_discovery
* @passcase				When bt_adapter_is_discovering is successful.
* @failcase				If targest API bt_adapter_is_discovering fails
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_adapter_bt_adapter_is_discovering_p(void)
{
	START_TEST;

	int nTimeoutId = 0;
	bool bIsDiscovering = false;

	int nRetVal = bt_adapter_start_device_discovery();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_start_device_discovery", BluetoothGetError(nRetVal));
	nRetVal = bt_adapter_is_discovering(&bIsDiscovering);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_adapter_is_discovering", BluetoothGetError(nRetVal),bt_adapter_stop_device_discovery());
	
	if (bIsDiscovering == false)
	{
		FPRINTF("[Line : %d][%s] bt_adapter_is_discovering returned false\\n", __LINE__, API_NAMESPACE);
		nRetVal = bt_adapter_stop_device_discovery();
		PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_stop_device_discovery", BluetoothGetError(nRetVal));
		return 1;
	}
	
	WAIT(SHORT_DELAY);
	nRetVal = bt_adapter_stop_device_discovery();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_stop_device_discovery", BluetoothGetError(nRetVal));
	WAIT(SHORT_DELAY);
	return 0;
}

//& purpose: Start and Stop the device discovery
//& type: auto
/**
* @testcase 			ITc_bluetooth_adapter_bt_start_stop_device_discovery_p
* @since_tizen			2.3
* @type 				auto
* @description			Start and Stop the device discovery
* @scenario				Set callback\n
*						Start device discovery\n
*						Check callback\n
*						Stop device discovery\n
*						Check callback\n
*						Unset callback
* @apicovered			bt_adapter_is_discovering, bt_adapter_set_device_discovery_state_changed_cb, bt_adapter_unset_device_discovery_state_changed_cb, bt_adapter_start_device_discovery and bt_adapter_stop_device_discovery
* @passcase				When bt_adapter_start_device_discovery and bt_adapter_stop_device_discovery is successful and callback is invoked for both APIs
* @failcase				If targest API bt_adapter_start_device_discovery or bt_adapter_stop_device_discovery fails or callback is not invoked for any API
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_adapter_bt_start_stop_device_discovery_p(void)
{
	START_TEST;

	int nTimeoutId = 0;
	bool bIsDiscovering = false;
	g_pMainLoop = g_main_loop_new(NULL, false);

	int nRetVal = bt_adapter_is_discovering(&bIsDiscovering);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_is_discovering", BluetoothGetError(nRetVal));

	if ( bIsDiscovering == true )
	{
		nRetVal = bt_adapter_stop_device_discovery();
		PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_stop_device_discovery", BluetoothGetError(nRetVal));
		WAIT(SHORT_DELAY);
	}

	nRetVal = bt_adapter_set_device_discovery_state_changed_cb(Bluetooth_adapter_device_discovery_state_changed_cb_p, NULL);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_set_device_discovery_state_changed_cb", BluetoothGetError(nRetVal));

	g_bCallbackResult = false;
	g_bReturnValueState = false;
	nRetVal = bt_adapter_start_device_discovery();
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_adapter_start_device_discovery", BluetoothGetError(nRetVal), bt_adapter_unset_device_discovery_state_changed_cb());
	CHECK_CALLBACK_STATUS("bt_adapter_start_device_discovery");
	if ( g_bReturnValueState == false )
	{
		FPRINTF("[Line : %d][%s] Bluetooth_adapter_device_discovery_state_changed_cb_p callback is failed. Callback returned invalid value\\n", __LINE__, API_NAMESPACE);
		nRetVal = bt_adapter_unset_device_discovery_state_changed_cb();
		PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_unset_device_discovery_state_changed_cb", BluetoothGetError(nRetVal));
		return 1;
	}

	g_bCallbackResult = false;
	g_bReturnValueState = false;

	nRetVal = bt_adapter_stop_device_discovery();
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_adapter_stop_device_discovery", BluetoothGetError(nRetVal) , bt_adapter_unset_device_discovery_state_changed_cb() );
	CHECK_CALLBACK_STATUS("bt_adapter_stop_device_discovery");
	if ( g_bReturnValueState == false )
	{
		FPRINTF("[Line : %d][%s] Bluetooth_adapter_device_discovery_state_changed_cb_p callback is failed. Callback returned invalid value\\n", __LINE__, API_NAMESPACE);
		nRetVal = bt_adapter_unset_device_discovery_state_changed_cb();
		PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_unset_device_discovery_state_changed_cb", BluetoothGetError(nRetVal));
		return 1;
	}
	nRetVal = bt_adapter_unset_device_discovery_state_changed_cb();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_unset_device_discovery_state_changed_cb", BluetoothGetError(nRetVal));
	return 0;
}

//& purpose: Initialize and Deinitialize the Bluetooth API
//& type: auto
/**
* @testcase 			ITc_bluetooth_bt_initialize_deinitialize_p
* @since_tizen			2.3
* @type 				auto
* @description			Initialize and Deinitialize the Bluetooth API
* @scenario				Initialize bluetooth API\n
*						Deinitialize bluetooth API
* @apicovered			bt_initialize and bt_deinitialize
* @passcase				When bt_initialize and bt_deinitialize is successful
* @failcase				If targest API bt_initialize or bt_deinitialize fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_bluetooth_bt_initialize_deinitialize_p(void)
{
	START_TEST;

	int nTimeoutId = 0;
	int nRetVal = bt_deinitialize();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_deinitialize", BluetoothGetError(nRetVal));
	WAIT(SHORT_DELAY);

	nRetVal = bt_initialize();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_initialize", BluetoothGetError(nRetVal));
	WAIT(SHORT_DELAY);

	nRetVal = bt_deinitialize();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_initialize", BluetoothGetError(nRetVal));

	nRetVal = bt_initialize();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_initialize", BluetoothGetError(nRetVal));
	return 0;
}

//& purpose: Registers and Deregister callback functions for bluetooth adapter state changes
//& type: auto
/**
* @testcase 			ITc_bluetooth_adapter_bt_adapter_set_unset_state_changed_cb_p
* @since_tizen			2.3
* @type 				auto
* @description			Registers callback functions for bluetooth adapter state changes and unregister the callback
* @scenario				Register callback\n
*						Unregister callback
* @apicovered			bt_adapter_set_state_changed_cb and bt_adapter_unset_state_changed_cb
* @passcase				When bt_adapter_set_state_changed_cb and bt_adapter_unset_state_changed_cb is successful
* @failcase				If targest API bt_adapter_set_state_changed_cb or bt_adapter_unset_state_changed_cb fails
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_adapter_bt_adapter_set_unset_state_changed_cb_p(void)
{
	START_TEST;

	int nRetVal = bt_adapter_set_state_changed_cb(Bluetooth_adapter_state_changed_cb_p, NULL);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_set_state_changed_cb", BluetoothGetError(nRetVal));
	nRetVal = bt_adapter_unset_state_changed_cb();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_unset_state_changed_cb", BluetoothGetError(nRetVal));
	return 0;
}

//& purpose: Registers a callback function to be invoked when the device discovery state changes and unregister the callback
//& type: auto
/**
* @testcase 			ITc_bluetooth_adapter_bt_adapter_set_unset_device_discovery_state_changed_cb_p
* @since_tizen			2.3
* @type 				auto
* @description			Registers a callback function to be invoked when the device discovery state changes and unregister the callback
* @scenario				Register callback\n
*						Start device discovery\n
*						Check callback\n
*						Unregister callback\n
*						Stop device discovery\n
*						Check callback
* @apicovered			bt_adapter_is_discovering, bt_adapter_set_device_discovery_state_changed_cb, bt_adapter_unset_device_discovery_state_changed_cb, bt_adapter_start_device_discovery and bt_adapter_stop_device_discovery
* @passcase				When bt_adapter_set_device_discovery_state_changed_cb is successful and callback is invoked and\n
* 							When bt_adapter_unset_device_discovery_state_changed_cb is successful and callback is not invoked
* @failcase				If targest API bt_adapter_set_device_discovery_state_changed_cb fails or callback is not invoked or\n
*						If targest API bt_adapter_unset_device_discovery_state_changed_cb fails or callback is invoked
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_adapter_bt_adapter_set_unset_device_discovery_state_changed_cb_p(void)
{
	START_TEST;

	int nTimeoutId = 0;
	bool bIsDiscovering = false;
	g_pMainLoop = g_main_loop_new(NULL, false);

	int nRetVal = bt_adapter_is_discovering(&bIsDiscovering);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_is_discovering", BluetoothGetError(nRetVal));
	if ( bIsDiscovering == true )
	{
		nRetVal = bt_adapter_stop_device_discovery();
		PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_stop_device_discovery", BluetoothGetError(nRetVal));
		WAIT(SHORT_DELAY);;
	}
	g_bCallbackResult = false;
	g_bReturnValueState = false;
	nRetVal = bt_adapter_set_device_discovery_state_changed_cb(Bluetooth_adapter_device_discovery_state_changed_cb_p, NULL);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_set_device_discovery_state_changed_cb", BluetoothGetError(nRetVal));

	nRetVal = bt_adapter_start_device_discovery();
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_adapter_start_device_discovery", BluetoothGetError(nRetVal), bt_adapter_unset_device_discovery_state_changed_cb(););
	CHECK_CALLBACK_STATUS("bt_adapter_set_device_discovery_state_changed_cb");

	if ( g_bReturnValueState == false )
	{
		FPRINTF("[Line : %d][%s] After 'bt_adapter_start_device_discovery' API, Bluetooth_adapter_device_discovery_state_changed_cb_p callback is failed. Callback returned invalid value\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = bt_adapter_unset_device_discovery_state_changed_cb();
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRetVal, "bt_adapter_unset_device_discovery_state_changed_cb", BluetoothGetError(nRetVal), bt_adapter_stop_device_discovery());

	nRetVal = bt_adapter_stop_device_discovery();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_stop_device_discovery", BluetoothGetError(nRetVal));
	CHECK_UNSET_CALLBACK_STATUS(LONG_DELAY, "bt_adapter_unset_device_discovery_state_changed_cb");

	return 0;
}

//& purpose: Checks whether the UUID of a service is used or not
//& type: auto
/**
* @testcase 			ITc_bluetooth_adapter_bt_adapter_is_service_used_p
* @since_tizen			2.3
* @type 				auto
* @description			Checks whether the UUID of a service is used or not
* @scenario				Checks whether the UUID (OPP service) of a service is used or not
* @apicovered			bt_adapter_is_service_used
* @passcase				When bt_adapter_is_service_used is successful.
* @failcase				If targest API bt_adapter_is_service_used fail.
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_adapter_bt_adapter_is_service_used_p(void)
{
	START_TEST;
	bool bUsedStatus = false;
	int nRetVal = bt_adapter_is_service_used(BLUETOOTH_SERVICE_UUID, &bUsedStatus);
	FPRINTF("[Line : %d][%s] Service used status: %d\\n", __LINE__, API_NAMESPACE, bUsedStatus);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_is_service_used", BluetoothGetError(nRetVal));
	return 0;
}

#if (defined(MOBILE) || defined(WEARABLE)  || defined(TIZENIOT) || defined(TV)) //Starts MOBILE or WEARABLE or TIZENIOT
//Bluetooth Socket ITc

//& purpose: Get local OOB data (Hash and Randomizer values)
//& type: auto
/**
* @testcase 			ITc_bluetooth_adapter_bt_adapter_get_local_oob_data_p
* @since_tizen			2.3
* @type 				auto
* @description			Get local OOB data (Hash and Randomizer values)
* @scenario				Get local OOB data
* @apicovered			bt_adapter_get_local_oob_data
* @passcase				When bt_adapter_get_local_oob_data is successful.
* @failcase				If targest API bt_adapter_get_local_oob_data fails.
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_adapter_bt_adapter_get_local_oob_data_p(void)
{
	START_TEST;
	unsigned char* pszHash = NULL;
	unsigned char* pszRandomizer = NULL;
	int nHashLength = 0;
	int nRandomizerLength = 0;

	int nRetVal = bt_adapter_get_local_oob_data(&pszHash, &pszRandomizer , &nHashLength , &nRandomizerLength);

	/* OOB not supported case : API should return BT_ERROR_NOT_SUPPORTED */
	if (g_bBluetoothIsOOBSupported == false) {
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRetVal, "bt_adapter_get_local_oob_data", BluetoothGetError(nRetVal));
		return 0;
	}

	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_get_local_oob_data", BluetoothGetError(nRetVal));
	if ( pszHash == NULL )
	{
		FPRINTF("[Line : %d][%s] After bt_adapter_get_local_oob_data, pszHash value is null\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Get hash value : %s\\n", __LINE__, API_NAMESPACE, pszHash);
		FREE_MEMORY(pszHash);
	}

	if ( pszRandomizer == NULL )
	{
		FPRINTF("[Line : %d][%s] After bt_adapter_get_local_oob_data, pszRandomizer value is null\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Get randomizer value : %s\\n", __LINE__, API_NAMESPACE, pszRandomizer);
		FREE_MEMORY(pszRandomizer);
	}
	return 0;
}
#endif  // End MOBILE or WEARABLE or TIZENIOT

//& purpose: Gets the address of the local Bluetooth adapter
//& type: auto
/**
* @testcase 			ITc_bluetooth_adapter_bt_adapter_get_address_p
* @since_tizen			2.3
* @type 				auto
* @description			Gets the address of the local Bluetooth adapter
* @scenario				Get the address of the local Bluetooth adapter
* @apicovered			bt_adapter_get_address
* @passcase				When bt_adapter_get_address is successful.
* @failcase				If targest API bt_adapter_get_address fail.
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_adapter_bt_adapter_get_address_p(void)
{
	START_TEST;
	char *pszLocalAddress = NULL;
	int nRetVal = bt_adapter_get_address(&pszLocalAddress);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_get_address", BluetoothGetError(nRetVal));
	if ( pszLocalAddress != NULL )
	{
		FPRINTF("[Line : %d][%s] Adapter address is: %s\\n", __LINE__, API_NAMESPACE, pszLocalAddress);
		FREE_MEMORY(pszLocalAddress);
	}
	else
	{
		FPRINTF("[Line : %d][%s] bt_adapter_get_address failed as adapter address is NULL, error returned = %s\\n", __LINE__, API_NAMESPACE, BluetoothGetError(nRetVal));
		return 1;
	}
	return 0;
}

//& purpose: Gets the current state of the local Bluetooth adapter
//& type: auto
/**
* @testcase 			ITc_bluetooth_adapter_bt_adapter_get_state_p
* @since_tizen			2.3
* @type 				auto
* @description			Gets the current state of the local Bluetooth adapter. State may be either BT_ADAPTER_ENABLED or BT_ADAPTER_DISABLED.
* @scenario				Gets the current state of the local Bluetooth adapter
* @apicovered			bt_adapter_get_state
* @passcase				When bt_adapter_get_state is successful.
* @failcase				If targest API bt_adapter_get_state fail.
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_adapter_bt_adapter_get_state_p(void)
{
	START_TEST;
	bt_adapter_state_e adapter_state = BT_ADAPTER_DISABLED;
	int nRetVal = bt_adapter_get_state(&adapter_state);
	if ( adapter_state == BT_ADAPTER_ENABLED )
	{
		FPRINTF("[Line : %d][%s] bt_adapter_get_state returned state as BT_ADAPTER_ENABLED\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] bt_adapter_get_state returned state as BT_ADAPTER_DISABLED\\n", __LINE__, API_NAMESPACE);
	}
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_get_state", BluetoothGetError(nRetVal));
	return 0;
}

//& purpose: Registers a callback function to be invoked when the visibility mode changes and Unregister callback.
//& type: auto
/**
* @testcase 			ITc_bluetooth_adapter_bt_adapter_set_unset_visibility_mode_changed_cb_p
* @since_tizen			2.3
* @type 				auto
* @description			Registers a callback function to be invoked when the visibility mode of bluetooth adapter changes and Unregister callback
* @scenario				Register callback\n
*						Unregister callback
* @apicovered			bt_adapter_set_visibility_mode_changed_cb and bt_adapter_unset_visibility_mode_changed_cb
* @passcase				When bt_adapter_set_visibility_mode_changed_cb and bt_adapter_unset_visibility_mode_changed_cb is successful
* @failcase				If targest APIs bt_adapter_set_visibility_mode_changed_cb or bt_adapter_unset_visibility_mode_changed_cb fails
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_adapter_bt_adapter_set_unset_visibility_mode_changed_cb_p(void)
{
	START_TEST;
	int nRetVal = bt_adapter_set_visibility_mode_changed_cb(Bluetooth_adapter_visibility_mode_changed_cb_p, NULL);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_set_visibility_mode_changed_cb", BluetoothGetError(nRetVal));
	nRetVal = bt_adapter_unset_visibility_mode_changed_cb();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_unset_visibility_mode_changed_cb", BluetoothGetError(nRetVal));
	return 0;
}

//& purpose: Registers a callback function to be invoked when visibility duration is change and Unregister callback.
//& type: auto
/**
* @testcase 			ITc_bluetooth_adapter_bt_adapter_set_unset_visibility_duration_changed_cb_p
* @since_tizen			2.3
* @type 				auto
* @description			Registers a callback function to be invoked every second until the when visibility mode is changed and Unregister the callback
* @scenario				Register callback\n
*						Unregister callback
* @apicovered			bt_adapter_set_visibility_duration_changed_cb and bt_adapter_unset_visibility_duration_changed_cb
* @passcase				When bt_adapter_set_visibility_duration_changed_cb and bt_adapter_unset_visibility_duration_changed_cb is successful
* @failcase				If targest APIs bt_adapter_set_visibility_duration_changed_cb or bt_adapter_unset_visibility_duration_changed_cb fails
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_adapter_bt_adapter_set_unset_visibility_duration_changed_cb_p(void)
{
	START_TEST;
	int nRetVal = bt_adapter_set_visibility_duration_changed_cb(Bluetooth_bt_adapter_visibility_duration_changed_cb_p, NULL);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_set_visibility_duration_changed_cb", BluetoothGetError(nRetVal));
	nRetVal = bt_adapter_unset_visibility_duration_changed_cb();
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_unset_visibility_duration_changed_cb", BluetoothGetError(nRetVal));
	return 0;
}

//& purpose: Gets the specification name for the given UUID.
//& type: auto
/**
* @testcase 			ITc_bluetooth_adapter_bt_get_uuid_name_p
* @since_tizen			3.0
* @type 				auto
* @description			Gets the specification name for the given UUID.
* @scenario				bt_get_uuid_name
* @apicovered			bt_get_uuid_name
* @passcase				When bt_get_uuid_name is successful
* @failcase				If target APIs fails
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_adapter_bt_get_uuid_name_p(void)
{
	START_TEST;
	char *pszName = NULL;
	int nRetVal = bt_get_uuid_name(BLUETOOTH_SERVICE_UUID, &pszName);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_get_uuid_name", BluetoothGetError(nRetVal));
	if ( pszName != NULL )
	{
		FPRINTF("[Line : %d][%s] specification name for the given UUID is: %s\\n", __LINE__, API_NAMESPACE, pszName);
		FREE_MEMORY(pszName);
	}
	else
	{
		FPRINTF("[Line : %d][%s] bt_get_uuid_name failed!!!\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Gets the local oob extended data.
//& type: auto
/**
* @testcase 			ITc_bluetooth_adapter_bt_adapter_get_local_oob_ext_data_p
* @since				3.0
* @author				SRID(mandadi.mr)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description			Gets the local oob extended data
* @scenario				bt_adapter_get_local_oob_ext_data
* @apicovered			bt_adapter_get_local_oob_ext_data
* @passcase				When bt_adapter_get_local_oob_ext_data is successful
* @failcase				If target APIs or any pre-condition fails
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_adapter_bt_adapter_get_local_oob_ext_data_p(void)
{
	START_TEST;

	unsigned char *pszHash192 = NULL;
	unsigned char *pszRandomizer192 = NULL;
    int nHash192_len = 0;
	int nRandomizer192_len = 0;
    unsigned char *pszHash256 = NULL;
	unsigned char *pszRandomizer256 = NULL;
    int nHash256_len = 0;
	int nRandomizer256_len = 0;
	
	//Target API
	int nRetVal = bt_adapter_get_local_oob_ext_data(&pszHash192, &pszRandomizer192, &nHash192_len, &nRandomizer192_len, &pszHash256, &pszRandomizer256, &nHash256_len, &nRandomizer256_len);

	/* OOB not supported case : API should return BT_ERROR_NOT_SUPPORTED */
	if (g_bBluetoothIsOOBSupported == false) {
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRetVal, "bt_adapter_get_local_oob_ext_data", BluetoothGetError(nRetVal));
		return 0;
	}

	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_get_local_oob_ext_data", BluetoothGetError(nRetVal));

	FREE_MEMORY(pszHash192);
	FREE_MEMORY(pszRandomizer192);
	FREE_MEMORY(pszHash256);
	FREE_MEMORY(pszRandomizer256);

	return 0;
}


