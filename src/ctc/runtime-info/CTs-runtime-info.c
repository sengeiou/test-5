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
#include "CTs-runtime-info-common.h"

/** @addtogroup ctc-runtime-info
* @ingroup		ctc
* @{
*/

//& set: RuntimeInfo

/**
* @function 		CTs_runtime_info_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_runtime_info_startup(void)
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
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Runtime_Info_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function 		CTs_runtime_info_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_runtime_info_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Runtime_Info_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup	ctc-runtime-info-testcases
* @brief 		Integration testcases for module runtime-info
* @ingroup		ctc-runtime-info
* @{
*/

//& purpose: Checks whether Bluetooth is enabled or disabled
//& type: auto
/**
* @testcase			CTc_RuntimeInfo_IsBluetoothEnabled_p
* @since_tizen		2.3
* @author            SRID(satyajit.a)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Checks whether Bluetooth is enabled or disabled from the runtime information.
* @apicovered		runtime_info_get_value_bool
* @passcase			If runtime_info_get_value_bool gets the current state of the given key from runtime information successfully
* @failcase			If runtime_info_get_value_bool fails to get the current state of the given key from runtime information
* @precondition		NA
* @postcondition	NA
*/
int CTc_RuntimeInfo_IsBluetoothEnabled_p(void)
{
	START_TEST;	
	if ( RuntimeGetSystemState(RUNTIME_INFO_KEY_BLUETOOTH_ENABLED) == false )
	{
		return 1;
	}
	PRINT_KEY_STATUS(g_bRuntimeKeyState,"RUNTIME_INFO_KEY_BLUETOOTH_ENABLED");
}

//& purpose: Checks whether Wifi-Hotspot is enabled or disabled
//& type: auto
/**
* @testcase			CTc_RuntimeInfo_IsWifiHotspotEnabled_p
* @since_tizen		2.3
* @author            SRID(satyajit.a)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Checks whether Wifi-Hotspot is enabled or disabled from the runtime information.
* @apicovered		runtime_info_get_value_bool
* @passcase			If runtime_info_get_value_bool gets the current state of the given key from runtime information successfully
* @failcase			If runtime_info_get_value_bool fails to get the current state of the given key from runtime information
* @precondition		NA
* @postcondition	NA
*/
int CTc_RuntimeInfo_IsWifiHotspotEnabled_p(void)
{
	START_TEST;
	if ( RuntimeGetSystemState(RUNTIME_INFO_KEY_WIFI_HOTSPOT_ENABLED) == false )
	{
		return 1;
	}
	PRINT_KEY_STATUS(g_bRuntimeKeyState,"RUNTIME_INFO_KEY_WIFI_HOTSPOT_ENABLED");
}

//& purpose: Checks whether Bluetooth is enabled or disabled
//& type: auto
/**
* @testcase			CTc_RuntimeInfo_IsBluetoothTetheringEnabled_p
* @since_tizen		2.3
* @author            SRID(satyajit.a)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Checks whether Bluetooth is enabled or disabled from the runtime information.
* @apicovered		runtime_info_get_value_bool
* @passcase			If runtime_info_get_value_bool gets the current state of the given key from runtime information successfully
* @failcase			If runtime_info_get_value_bool fails to get the current state of the given key from runtime information
* @precondition		NA
* @postcondition	NA
*/
int CTc_RuntimeInfo_IsBluetoothTetheringEnabled_p(void)
{
	START_TEST;
	if ( RuntimeGetSystemState(RUNTIME_INFO_KEY_BLUETOOTH_TETHERING_ENABLED) == false )
	{
		return 1;
	}
	PRINT_KEY_STATUS(g_bRuntimeKeyState,"RUNTIME_INFO_KEY_BLUETOOTH_TETHERING_ENABLED");
}

//& purpose: Checks whether USB tethering is enabled or disabled
//& type: auto
/**
* @testcase			CTc_RuntimeInfo_IsUSBTetheringEnabled_p
* @since_tizen		2.3
* @author            SRID(satyajit.a)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Checks whether USB tethering is enabled or disabled from the runtime information.
* @apicovered		runtime_info_get_value_bool
* @passcase			If runtime_info_get_value_bool gets the current state of the given key from runtime information successfully
* @failcase			If runtime_info_get_value_bool fails to get the current state of the given key from runtime information
* @precondition		NA
* @postcondition	NA
*/
int CTc_RuntimeInfo_IsUSBTetheringEnabled_p(void)
{
	START_TEST;
	if ( RuntimeGetSystemState(RUNTIME_INFO_KEY_USB_TETHERING_ENABLED) == false )
	{
		return 1;
	}
	PRINT_KEY_STATUS(g_bRuntimeKeyState,"RUNTIME_INFO_KEY_USB_TETHERING_ENABLED");
}

//& purpose: Checks whether the packet data through 3G network is enabled
//& type: auto
/**
* @testcase			CTc_RuntimeInfo_IsKeyPacketDataEnabled_p
* @since_tizen		2.3
* @author            SRID(satyajit.a)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Checks whether the packet data through 3G network is enabled from the runtime information.
* @apicovered		runtime_info_get_value_bool
* @passcase			If runtime_info_get_value_bool gets the current state of the given key from runtime information successfully
* @failcase			If runtime_info_get_value_bool fails to get the current state of the given key from runtime information
* @precondition		NA
* @postcondition	NA
*/
int CTc_RuntimeInfo_IsKeyPacketDataEnabled_p(void)
{
	START_TEST;
	if ( RuntimeGetSystemState(RUNTIME_INFO_KEY_PACKET_DATA_ENABLED) == false )
	{
		return 1;
	}
	PRINT_KEY_STATUS(g_bRuntimeKeyState,"RUNTIME_INFO_KEY_PACKET_DATA_ENABLED");
}

//& purpose: Checks whether data roaming is enabled
//& type: auto
/**
* @testcase			CTc_RuntimeInfo_IsDataRoamingEnabled_p
* @since_tizen		2.3
* @author            SRID(satyajit.a)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Checks whether data roaming is enabled from the runtime information.
* @apicovered		runtime_info_get_value_bool
* @passcase			If runtime_info_get_value_bool gets the current state of the given key from runtime information successfully
* @failcase			If runtime_info_get_value_bool fails to get the current state of the given key from runtime information
* @precondition		NA
* @postcondition	NA
*/
int CTc_RuntimeInfo_IsDataRoamingEnabled_p(void)
{
	START_TEST;
	if ( RuntimeGetSystemState(RUNTIME_INFO_KEY_DATA_ROAMING_ENABLED) == false )
	{
		return 1;
	}
	PRINT_KEY_STATUS(g_bRuntimeKeyState,"RUNTIME_INFO_KEY_DATA_ROAMING_ENABLED");
}

//& purpose: Checks whether vibration is enabled
//& type: auto
/**
* @testcase			CTc_RuntimeInfo_IsVibrationEnabled_p
* @since_tizen		2.3
* @author            SRID(satyajit.a)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Checks whether vibration is enabled from the runtime information.
* @apicovered		runtime_info_get_value_bool
* @passcase			If runtime_info_get_value_bool gets the current state of the given key from runtime information successfully
* @failcase			If runtime_info_get_value_bool fails to get the current state of the given key from runtime information
* @precondition		NA
* @postcondition	NA
*/
int CTc_RuntimeInfo_IsVibrationEnabled_p(void)
{
	START_TEST;
	if ( RuntimeGetSystemState(RUNTIME_INFO_KEY_VIBRATION_ENABLED) == false )
	{
		return 1;
	}
	PRINT_KEY_STATUS(g_bRuntimeKeyState,"RUNTIME_INFO_KEY_VIBRATION_ENABLED");
}

//& purpose: Checks whether audio jack is connected
//& type: auto
/**
* @testcase			CTc_RuntimeInfo_IsAudioJackConnectedEnabled_p
* @since_tizen		2.3
* @author            SRID(satyajit.a)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Checks whether audio jack is connected from the runtime information.
* @apicovered		runtime_info_get_value_bool
* @passcase			If runtime_info_get_value_bool gets the current state of the given key from runtime information successfully
* @failcase			If runtime_info_get_value_bool fails to get the current state of the given key from runtime information
* @precondition		NA
* @postcondition	NA
*/
int CTc_RuntimeInfo_IsAudioJackConnectedEnabled_p(void)
{
	START_TEST;
	if ( RuntimeGetSystemState(RUNTIME_INFO_KEY_AUDIO_JACK_CONNECTED) == false )
	{
		return 1;
	}
	PRINT_KEY_STATUS(g_bRuntimeKeyState,"RUNTIME_INFO_KEY_AUDIO_JACK_CONNECTED");
}

//& purpose: Checks whether the battery is currently charging or not
//& type: auto
/**
* @testcase			CTc_RuntimeInfo_IsBatteryCharging_p
* @since_tizen		2.3
* @author            SRID(satyajit.a)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Checks whether the battery is currently charging or not from the runtime information.
* @apicovered		runtime_info_get_value_bool
* @passcase			If runtime_info_get_value_bool gets the current state of the given key from runtime information successfully
* @failcase			If runtime_info_get_value_bool fails to get the current state of the given key from runtime information
* @precondition		NA
* @postcondition	NA
*/
int CTc_RuntimeInfo_IsBatteryCharging_p(void)
{
	START_TEST;
	if ( RuntimeGetSystemState(RUNTIME_INFO_KEY_BATTERY_IS_CHARGING) == false )
	{
		return 1;
	}
	PRINT_KEY_STATUS(g_bRuntimeKeyState,"RUNTIME_INFO_KEY_BATTERY_IS_CHARGING");
}

//& purpose: Checks whether TV out is connected
//& type: auto
/**
* @testcase			CTc_RuntimeInfo_IsTVconnected_p
* @since_tizen		2.3
* @author            SRID(satyajit.a)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Checks whether TV out is connected from the runtime information.
* @apicovered		runtime_info_get_value_bool
* @passcase			If runtime_info_get_value_bool gets the current state of the given key from runtime information successfully
* @failcase			If runtime_info_get_value_bool fails to get the current state of the given key from runtime information
* @precondition		NA
* @postcondition	NA
*/
int CTc_RuntimeInfo_IsTVconnected_p(void)
{
	START_TEST;
	if ( RuntimeGetSystemState(RUNTIME_INFO_KEY_TV_OUT_CONNECTED) == false )
	{
		return 1;
	}
	PRINT_KEY_STATUS(g_bRuntimeKeyState,"RUNTIME_INFO_KEY_TV_OUT_CONNECTED");
}

//& purpose: Checks whether USB is connected
//& type: auto
/**
* @testcase			CTc_RuntimeInfo_IsUSBconnected_p
* @since_tizen		2.3
* @author            SRID(satyajit.a)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Checks whether USB is connected from the runtime information.
* @apicovered		runtime_info_get_value_bool
* @passcase			If runtime_info_get_value_bool gets the current state of the given key from runtime information successfully
* @failcase			If runtime_info_get_value_bool fails to get the current state of the given key from runtime information
* @precondition		NA
* @postcondition	NA
*/
int CTc_RuntimeInfo_IsUSBconnected_p(void)
{
	START_TEST;
	if ( RuntimeGetSystemState(RUNTIME_INFO_KEY_USB_CONNECTED) == false )
	{
		return 1;
	}
	PRINT_KEY_STATUS(g_bRuntimeKeyState,"RUNTIME_INFO_KEY_USB_CONNECTED");
}

//& purpose: Checks whether charger is connected
//& type: auto
/**
* @testcase			CTc_RuntimeInfo_IsChargerConnected_p
* @since_tizen		2.3
* @author            SRID(satyajit.a)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Checks whether charger is connected from the runtime information.
* @apicovered		runtime_info_get_value_bool
* @passcase			If runtime_info_get_value_bool gets the current state of the given key from runtime information successfully
* @failcase			If runtime_info_get_value_bool fails to get the current state of the given key from runtime information
* @precondition		NA
* @postcondition	NA
*/
int CTc_RuntimeInfo_IsChargerConnected_p(void)
{
	START_TEST;
	if ( RuntimeGetSystemState(RUNTIME_INFO_KEY_CHARGER_CONNECTED) == false )
	{
		return 1;
	}
	PRINT_KEY_STATUS(g_bRuntimeKeyState,"RUNTIME_INFO_KEY_CHARGER_CONNECTED");
}

//& purpose: Checks whether auto rotation is enabled
//& type: auto
/**
* @testcase			CTc_RuntimeInfo_IsAutoRotationEnabled_p
* @since_tizen		2.3
* @author            SRID(satyajit.a)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Checks whether auto rotation is enabled from the runtime information.
* @apicovered		runtime_info_get_value_bool
* @passcase			If runtime_info_get_value_bool gets the current state of the given key from runtime information successfully
* @failcase			If runtime_info_get_value_bool fails to get the current state of the given key from runtime information
* @precondition		NA
* @postcondition	NA
*/
int CTc_RuntimeInfo_IsAutoRotationEnabled_p(void)
{
	START_TEST;
	if ( RuntimeGetSystemState(RUNTIME_INFO_KEY_AUTO_ROTATION_ENABLED) == false )
	{
		return 1;
	}
	PRINT_KEY_STATUS(g_bRuntimeKeyState,"RUNTIME_INFO_KEY_AUTO_ROTATION_ENABLED");
}

/** @} */ //end of ctc-runtime-info
/** @} */ //end of ctc-runtime-info-testcases
