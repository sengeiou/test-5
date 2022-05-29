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
#include "ITs-wifi-direct-common.h"

/** @addtogroup itc-wifi-direct
*  @ingroup itc
*  @{
*/

bool g_bFeatureWifiDirect = false;
bool g_bFeatureWifiDirectDisplay = false;
bool g_bFeatureWifiDirectSrvcDiscovery = false;
bool g_bSkipTestCaseWithPass = false;

bool g_bWifi_direct_device_state_changed_callback_invoked_check_activation = false;
wifi_direct_device_state_e g_device_state_activate_check_activation = WIFI_DIRECT_DEVICE_STATE_DEACTIVATED;

static bool g_bCallbackResult = false;
gboolean TimeoutFunction(gpointer data)
{
	FPRINTF("[Line : %d][%s] Timeout Occurs\\n", __LINE__, API_NAMESPACE);
	GMainLoop *pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
		g_main_loop_unref(pMainLoop);
		pMainLoop = NULL;
	}
	return false;
}


/**
* @function 		wifi_direct_device_state_changed_callback_check_activation_state
* @description	 	Callback function to indicate change in state
* @parameter		int error_code  - error value, wifi_direct_device_state_e device_state - Current state, void* user_data - user data passed
* @return 			NA
*/
void wifi_direct_device_state_changed_callback_check_activation_state(int error_code, wifi_direct_device_state_e device_state, void* user_data)
{
	FPRINTF("[Line : %d][%s] wifi_direct_device_state_changed_callback_check_activation_state invoked; error_code = %d, device_state = %d\\n", __LINE__, API_NAMESPACE, error_code, device_state);
	g_bWifi_direct_device_state_changed_callback_invoked_check_activation = true;

	g_device_state_activate_check_activation = device_state;
	g_bCallbackResult = true;
	if ( g_pMainLoop != NULL )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		WifiDirectGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* WifiDirectGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case WIFI_DIRECT_ERROR_NONE  :
		szErrorVal = "Successful" ;
		break;
	case WIFI_DIRECT_ERROR_NOT_PERMITTED  :
		szErrorVal = "Operation not permitted(1)" ;
		break;
	case WIFI_DIRECT_ERROR_OUT_OF_MEMORY  :
		szErrorVal = "Out of memory" ;
		break;
	case WIFI_DIRECT_ERROR_PERMISSION_DENIED  :
		szErrorVal = "Permission denied" ;
		break;
	case WIFI_DIRECT_ERROR_RESOURCE_BUSY  :
		szErrorVal = "Device or resource busy" ;
		break;
	case WIFI_DIRECT_ERROR_INVALID_PARAMETER  :
		szErrorVal = "Invalid function parameter" ;
		break;
	case WIFI_DIRECT_ERROR_CONNECTION_TIME_OUT  :
		szErrorVal = "Connection timed out" ;
		break;
	case WIFI_DIRECT_ERROR_NOT_SUPPORTED  :
		szErrorVal = "Not supported" ;
		break;
	case WIFI_DIRECT_ERROR_NOT_INITIALIZED  :
		szErrorVal = "Not initialized" ;
		break;
	case WIFI_DIRECT_ERROR_COMMUNICATION_FAILED  :
		szErrorVal = "I/O error" ;
		break;
	case WIFI_DIRECT_ERROR_WIFI_USED  :
		szErrorVal = "WiFi is being used" ;
		break;
	case WIFI_DIRECT_ERROR_MOBILE_AP_USED  :
		szErrorVal = "Mobile AP is being used" ;
		break;
	case WIFI_DIRECT_ERROR_CONNECTION_FAILED  :
		szErrorVal = "Connection failed" ;
		break;
	case WIFI_DIRECT_ERROR_AUTH_FAILED  :
		szErrorVal = "Authentication failed" ;
		break;
	case WIFI_DIRECT_ERROR_OPERATION_FAILED  :
		szErrorVal = "Operation failed" ;
		break;
	case WIFI_DIRECT_ERROR_TOO_MANY_CLIENT  :
		szErrorVal = "Too many client" ;
		break;
	case WIFI_DIRECT_ERROR_ALREADY_INITIALIZED  :
		szErrorVal = "Already initialized client" ;
		break;
	case WIFI_DIRECT_ERROR_CONNECTION_CANCELED  :
		szErrorVal = "Connection cancelled by local device" ;
		break;
	default :
		szErrorVal = "Undefined error" ;
		break;
	}

	return szErrorVal;
}

/**
* @function 		WifiDirectReadyService
* @description	 	Ready the wifi-direct service
* @parameter		none
* @return 			true if succeed else false
*/
bool WifiDirectReadyService()
{
	int nTimeoutId = 0;
	
	wifi_direct_state_e eState = WIFI_DIRECT_STATE_DEACTIVATED;
	int nRet = wifi_direct_initialize();
	if ( !g_bFeatureWifiDirect )
	{
		if ( nRet == TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] wifi_direct_initialize correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
			g_bSkipTestCaseWithPass = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] wifi_direct_initialize returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
		}
		return false;
	}
	if ( nRet != WIFI_DIRECT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to initialize the wifi-direct service; wifi_direct_initialize returned error code = %s\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
		return false;
	}

	FPRINTF("[Line : %d][%s] Initialized the wifi-direct service successfully\\n", __LINE__, API_NAMESPACE);

	nRet = wifi_direct_get_state(&eState);
	if ( nRet != WIFI_DIRECT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] wifi_direct_get_state failed, returned error code = %s\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
		return false;
	}
	if ( eState == WIFI_DIRECT_STATE_ACTIVATED )
	{
		FPRINTF("[Line : %d][%s] Wifi direct is already in Activated State.\\n \\n", __LINE__, API_NAMESPACE);
		sleep(5);
		return true;
	}
	
	nRet = wifi_direct_set_device_state_changed_cb(wifi_direct_device_state_changed_callback_check_activation_state, NULL);
	if ( nRet !=  WIFI_DIRECT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] wifi_direct_set_device_state_changed_cb API call returned error = %s\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
		wifi_direct_deinitialize();
		return false;
	}

	g_bWifi_direct_device_state_changed_callback_invoked_check_activation = false;
	g_bCallbackResult = false;
	
	nRet = wifi_direct_activate();
	if ( nRet != WIFI_DIRECT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to activate the wifi-direct service; wifi_direct_activate returned error code = %s\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
		wifi_direct_unset_device_state_changed_cb();
		wifi_direct_deinitialize();
		return false;
	}
	
	RUN_POLLING_LOOP("wifi_direct_set_device_state_changed_cb");
	if ( false == g_bWifi_direct_device_state_changed_callback_invoked_check_activation )
	{
		FPRINTF("[Line : %d][%s] Unable to get call back for wifi_direct_activate\\n", __LINE__, API_NAMESPACE);
		wifi_direct_unset_device_state_changed_cb();
		wifi_direct_deinitialize();
		return false;
	}

	if ( g_device_state_activate_check_activation != WIFI_DIRECT_DEVICE_STATE_ACTIVATED )
	{
		FPRINTF("[Line : %d][%s] wifi_direct_activate callback returned wrong device state = %d\\n", __LINE__, API_NAMESPACE, g_device_state_activate_check_activation);
		wifi_direct_unset_device_state_changed_cb();
		wifi_direct_deinitialize();
		return false;
	}

	FPRINTF("[Line : %d][%s] Successfully able to retrieve the WIFI_DIRECT_DEVICE_STATE_ACTIVATED device state in device state change callback\\n", __LINE__, API_NAMESPACE);
	wifi_direct_unset_device_state_changed_cb();
	FPRINTF("[Line : %d][%s] Activated the wifi-direct service successfully\\n", __LINE__, API_NAMESPACE);
	sleep(5);
	return true;
}

/**
* @function 		WifiDirectTerminateService
* @description	 	Terminates the wifi-direct service
* @parameter		none
* @return 			none
*/
bool WifiDirectTerminateService()
{
	int nTimeoutId = 0;
	g_bWifi_direct_device_state_changed_callback_invoked_check_activation = false;
	int nRet = wifi_direct_set_device_state_changed_cb(wifi_direct_device_state_changed_callback_check_activation_state, NULL);
	if ( nRet !=  WIFI_DIRECT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] wifi_direct_set_device_state_changed_cb API call returned error = %s\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
		nRet = wifi_direct_deactivate();
		PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deactivate", WifiDirectGetError(nRet));

		wifi_direct_unset_device_state_changed_cb();
		wifi_direct_deinitialize();
		return false;
	}
	g_bCallbackResult = false;
	nRet = wifi_direct_deactivate();
	if ( nRet != WIFI_DIRECT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to deactivate the wifi-direct service; wifi_direct_deactivate returned error code = %s\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
		wifi_direct_unset_device_state_changed_cb();
		wifi_direct_deinitialize();
		return false;
	}
	
	RUN_POLLING_LOOP("wifi_direct_set_device_state_changed_cb");
	if ( false == g_bWifi_direct_device_state_changed_callback_invoked_check_activation )
	{
		FPRINTF("[Line : %d][%s] Unable to get call back for wifi_direct_deactivate\\n", __LINE__, API_NAMESPACE);
		wifi_direct_unset_device_state_changed_cb();
		wifi_direct_deinitialize();
		return false;
	}

	if ( g_device_state_activate_check_activation != WIFI_DIRECT_DEVICE_STATE_DEACTIVATED )
	{
		FPRINTF("[Line : %d][%s] wifi_direct_activate callback returned wrong device state = %d\\n", __LINE__, API_NAMESPACE, g_device_state_activate_check_activation);
		wifi_direct_unset_device_state_changed_cb();
		wifi_direct_deinitialize();
		return false;
	}

	FPRINTF("[Line : %d][%s] Successfully able to retrieve the WIFI_DIRECT_DEVICE_STATE_DEACTIVATED device state in device state change callback\\n", __LINE__, API_NAMESPACE);

	wifi_direct_unset_device_state_changed_cb();

	nRet = wifi_direct_deinitialize();
	if ( nRet != WIFI_DIRECT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to de initialize the wifi-direct service; wifi_direct_deinitialize returned error code = %s\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
	}

	FPRINTF("[Line : %d][%s] Successfully able to de-activate and de-initialise the wifi-direct service\\n", __LINE__, API_NAMESPACE);
	sleep(5);
	return true;
}

/**
* @function 		WifiDirectGetVSIEFrameID
* @description	 	Maps type enums to string values
* @parameter		nFrameId : code returned
* @return 		error string
*/
char* WifiDirectGetVSIEFrameID(wifi_direct_vsie_frames_e nFrameId)
{
	char *szFrameId = "Unknown Frame ID";
	switch ( nFrameId )
	{
	case WIFI_DIRECT_VSIE_FRAME_P2P_PROBE_REQ:	szFrameId = "WIFI_DIRECT_VSIE_FRAME_P2P_PROBE_REQ"; 		break;
	case WIFI_DIRECT_VSIE_FRAME_P2P_PROBE_RESP:	szFrameId = "WIFI_DIRECT_VSIE_FRAME_P2P_PROBE_RESP"; 		break;
	case WIFI_DIRECT_VSIE_FRAME_P2P_GO_PROBE_RESP:	szFrameId = "WIFI_DIRECT_VSIE_FRAME_P2P_GO_PROBE_RESP"; 	break;
	case WIFI_DIRECT_VSIE_FRAME_P2P_GO_BEACON:	szFrameId = "WIFI_DIRECT_VSIE_FRAME_P2P_GO_BEACON"; 		break;
	case WIFI_DIRECT_VSIE_FRAME_P2P_PD_REQ:		szFrameId = "WIFI_DIRECT_VSIE_FRAME_P2P_PD_REQ"; 		break;
	case WIFI_DIRECT_VSIE_FRAME_P2P_PD_RESP:	szFrameId = "WIFI_DIRECT_VSIE_FRAME_P2P_PD_RESP"; 		break;
	case WIFI_DIRECT_VSIE_FRAME_P2P_GO_NEG_REQ:	szFrameId = "WIFI_DIRECT_VSIE_FRAME_P2P_GO_NEG_REQ"; 		break;
	case WIFI_DIRECT_VSIE_FRAME_P2P_GO_NEG_RESP:	szFrameId = "WIFI_DIRECT_VSIE_FRAME_P2P_GO_NEG_RESP"; 		break;
	case WIFI_DIRECT_VSIE_FRAME_P2P_GO_NEG_CONF:	szFrameId = "WIFI_DIRECT_VSIE_FRAME_P2P_GO_NEG_CONF"; 		break;
	case WIFI_DIRECT_VSIE_FRAME_P2P_INV_REQ:	szFrameId = "WIFI_DIRECT_VSIE_FRAME_P2P_INV_REQ"; 		break;
	case WIFI_DIRECT_VSIE_FRAME_P2P_INV_RESP:	szFrameId = "WIFI_DIRECT_VSIE_FRAME_P2P_INV_RESP"; 		break;
	case WIFI_DIRECT_VSIE_FRAME_P2P_ASSOC_REQ:	szFrameId = "WIFI_DIRECT_VSIE_FRAME_P2P_ASSOC_REQ"; 		break;
	case WIFI_DIRECT_VSIE_FRAME_P2P_ASSOC_RESP:	szFrameId = "WIFI_DIRECT_VSIE_FRAME_P2P_ASSOC_RESP"; 		break;
	case WIFI_DIRECT_VSIE_FRAME_ASSOC_REQ:		szFrameId = "WIFI_DIRECT_VSIE_FRAME_ASSOC_REQ"; 		break;
	}
	return szFrameId;
}

/** @} */
