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
#include "ITs-wifi-manager-common.h"
#include <dlog.h>

/** @addtogroup itc-wifi-manager
*  @ingroup itc
*  @{
*/

/**
* @function         WifiManagerGetError
* @description      Maps error enumerators to string values
* @parameter        nRet : error code returned
* @return           error string
*/
char* WifiManagerGetError(int nRet)
{
	char *error_value = "Unknown Error";

	switch (nRet) {
	case WIFI_MANAGER_ERROR_NONE:
		error_value = "WIFI_MANAGER_ERROR_NONE";
		break;
	case WIFI_MANAGER_ERROR_INVALID_PARAMETER:
		error_value = "WIFI_MANAGER_ERROR_INVALID_PARAMETER";
		break;
	case WIFI_MANAGER_ERROR_OUT_OF_MEMORY:
		error_value = "WIFI_MANAGER_ERROR_OUT_OF_MEMORY";
		break;
	case WIFI_MANAGER_ERROR_INVALID_OPERATION:
		error_value = "WIFI_MANAGER_ERROR_INVALID_OPERATION";
		break;
	case WIFI_MANAGER_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED:
		error_value = "WIFI_MANAGER_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED";
		break;
	case WIFI_MANAGER_ERROR_OPERATION_FAILED:
		error_value = "WIFI_MANAGER_ERROR_OPERATION_FAILED";
		break;
	case WIFI_MANAGER_ERROR_NO_CONNECTION:
		error_value = "WIFI_MANAGER_ERROR_NO_CONNECTION";
		break;
	case WIFI_MANAGER_ERROR_NOW_IN_PROGRESS:
		error_value = "WIFI_MANAGER_ERROR_NOW_IN_PROGRESS";
		break;
	case WIFI_MANAGER_ERROR_ALREADY_EXISTS:
		error_value = "WIFI_MANAGER_ERROR_ALREADY_EXISTS";
		break;
	case WIFI_MANAGER_ERROR_OPERATION_ABORTED:
		error_value = "WIFI_MANAGER_ERROR_OPERATION_ABORTED";
		break;
	case WIFI_MANAGER_ERROR_DHCP_FAILED:
		error_value = "WIFI_MANAGER_ERROR_DHCP_FAILED";
		break;
	case WIFI_MANAGER_ERROR_INVALID_KEY:
		error_value = "WIFI_MANAGER_ERROR_INVALID_KEY";
		break;
	case WIFI_MANAGER_ERROR_NO_REPLY:
		error_value = "WIFI_MANAGER_ERROR_NO_REPLY";
		break;
	case WIFI_MANAGER_ERROR_SECURITY_RESTRICTED:
		error_value = "WIFI_MANAGER_ERROR_SECURITY_RESTRICTED";
		break;
	case WIFI_MANAGER_ERROR_OFFLINE:
		error_value = "WIFI_MANAGER_ERROR_OFFLINE";
		break;
	case WIFI_MANAGER_ERROR_INVALID_GATEWAY:
		error_value = "WIFI_MANAGER_ERROR_INVALID_GATEWAY";
		break;
	case WIFI_MANAGER_ERROR_NOT_INITIALIZED:
		error_value = "WIFI_MANAGER_ERROR_NOT_INITIALIZED";
		break;
	}
	return error_value;
}


/**
* @function         WifiManagerTimeout
* @description      Called if some callback is not invoked for a particular timeout
* @parameter        gpointer data
* @return           gboolean
*/
gboolean WifiManagerTimeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		dlog_print(DLOG_INFO, "NativeTCT", "[%d:%s] Quit mainloop(timeout)[%p]", __LINE__, __FUNCTION__, pMainLoop);
		g_main_loop_quit(pMainLoop);
	}
	FPRINTF("[%d:%s] Callback Timeout\\n", __LINE__, __FUNCTION__);
	dlog_print(DLOG_ERROR, "NativeTCT", "[%d:%s] Callback Timeout", __LINE__, __FUNCTION__);
	return false;
}

bool wifi_manager_check_feature_supported(char *key)
{
	bool value = false;
	int ret = system_info_get_platform_bool(key, &value);

	if (ret != SYSTEM_INFO_ERROR_NONE) {
		FPRINTF("[%s:%d] system_info_get_platform_bool failed, error returned = %d\\n", __FILE__, __LINE__, ret);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] system_info_get_platform_bool failed, error returned = %d", __FILE__, __LINE__, ret);
		return false;
	}

	if (value) {
		FPRINTF("[%s:%d] %s feature is supported\\n", __FILE__, __LINE__, key);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] %s feature is supported", __FILE__, __LINE__, key);
	} else {
		FPRINTF("[%s:%d] %s feature is not supported\\n", __FILE__, __LINE__, key);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] %s feature is not supported", __FILE__, __LINE__, key);
	}

	return value;
}

void wifi_manager_activated_callback(wifi_manager_error_e result, void* user_data)
{
	g_bWifiManagerCB = true;
	g_bWifiManagerCBHit = true;
	PRINT_RETURN("wifi_manager_activated_callback", result);

	g_nCallbackRet = result;
	QUIT_GMAIN_LOOP;
}

void wifi_manager_activated_callback_without_mainloop(wifi_manager_error_e result, void* user_data)
{
	g_bWifiManagerCB = true;
	g_bWifiManagerCBHit = true;
	PRINT_RETURN("wifi_manager_activated_callback_without_mainloop", result);

	g_nCallbackRet = result;
}

void wifi_manager_deactivated_callback(wifi_manager_error_e result, void* user_data)
{
	g_bWifiManagerCB = true;
	g_bWifiManagerCBHit = true;
	PRINT_RETURN("wifi_manager_deactivated_callback", result);

	g_nCallbackRet = result;
	QUIT_GMAIN_LOOP;
}

void wifi_manager_deactivated_callback_without_mainloop(wifi_manager_error_e result, void* user_data)
{
	g_bWifiManagerCB = true;
	g_bWifiManagerCBHit = true;
	PRINT_RETURN("wifi_manager_deactivated_callback_without_mainloop", result);

	g_nCallbackRet = result;
}

void wifi_manager_activated_with_picker_callback(wifi_manager_error_e result, void* user_data)
{
	g_bWifiManagerCB = true;
	PRINT_RETURN("wifi_manager_activated_with_picker_callback", result);

	g_nCallbackRet = result;
	QUIT_GMAIN_LOOP;
}

void wifi_manager_scanned_callback(wifi_manager_error_e result, void* user_data)
{
	g_bWifiManagerCB = true;
	PRINT_RETURN("wifi_manager_scanned_callback", result);

	g_nCallbackRet = result;
	QUIT_GMAIN_LOOP;
}

void wifi_manager_scan_state_changed_callback(wifi_manager_scan_state_e state, void* user_data)
{
	g_bWifiManagerCBHit = true;
	PRINT_RETURN("wifi_manager_scan_state_changed_callback", WIFI_MANAGER_ERROR_NONE);
}


void wifi_manager_background_scanned_callback(wifi_manager_error_e result, void* user_data)
{
	g_bWifiManagerScanFinishCB  = true;
	PRINT_RETURN("wifi_manager_background_scanned_callback", result);

	QUIT_GMAIN_LOOP;
}

bool wifi_manager_found_ap_callback(wifi_manager_ap_h ap, void *user_data)
{
	g_bWifiManagerCB = true;
	PRINT_RETURN("wifi_manager_found_ap_callback", WIFI_MANAGER_ERROR_NONE);

	char *ap_name;
	char *ap_name_part = (char *)user_data;
	int ret = WIFI_MANAGER_ERROR_NONE;
	wifi_manager_security_type_e sec_type = WIFI_MANAGER_SECURITY_TYPE_NONE;

	if (ap)
	{
		ret = wifi_manager_ap_get_essid(ap, &ap_name);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, ret, "wifi_manager_ap_get_essid", WifiManagerGetError(ret));
		ret = wifi_manager_ap_get_security_type(ap, &sec_type);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, ret, "wifi_manager_ap_get_security_type", WifiManagerGetError(ret));

		FPRINTF("[%s:%d] AP ssid : %s, security type : %d\\n", __FILE__, __LINE__, ap_name, sec_type);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] AP ssid : %s, security type : %d", __FILE__, __LINE__, ap_name, sec_type);

		if (!strcmp(ap_name, ap_name_part))
		{
			FPRINTF("[%s:%d] ap_name : %s, ap_name_part : %s\\n", __FILE__, __LINE__, ap_name, ap_name_part);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ap_name : %s, ap_name_part : %s", __FILE__, __LINE__, ap_name, ap_name_part);
			FREE_MEMORY(ap_name);
			ret = wifi_manager_ap_clone(&g_hWifiAP, ap);
			CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, ret, "wifi_manager_ap_clone", WifiManagerGetError(ret));
			if (g_hWifiAP)
			{
				g_nCallbackRet = WIFI_MANAGER_ERROR_NONE;
				return false;
			}
		}
	}
	return true;
}

bool wifi_manager_foreach_found_ap_callback(wifi_manager_ap_h ap, void *user_data)
{
	g_bWifiManagerCB = true;
	PRINT_RETURN("wifi_manager_foreach_found_ap_callback", WIFI_MANAGER_ERROR_NONE);

	QUIT_GMAIN_LOOP;
	return false;
}

void wifi_manager_scanned_specific_ap_callback(wifi_manager_error_e result, void* user_data)
{
	g_bWifiManagerCB = true;
	PRINT_RETURN("wifi_manager_scanned_specific_ap_callback", result);

	g_nCallbackRet = result;
	QUIT_GMAIN_LOOP;
}

bool wifi_manager_foreach_found_specific_ap_callback(wifi_manager_ap_h ap, void *user_data)
{
	g_bWifiManagerCB = true;
	PRINT_RETURN("wifi_manager_foreach_found_specific_ap_callback", WIFI_MANAGER_ERROR_NONE);
	return false;
}

void wifi_manager_connected_callback(wifi_manager_error_e result, void* user_data)
{
	g_bWifiManagerCB = true;
	PRINT_RETURN("wifi_manager_connected_callback", result);

	g_nCallbackRet = result;
	QUIT_GMAIN_LOOP;
}

void wifi_manager_disconnected_callback(wifi_manager_error_e result, void* user_data)
{
	g_bWifiManagerCB = true;
	PRINT_RETURN("wifi_manager_disconnected_callback", result);
	g_nCallbackRet = result;
	QUIT_GMAIN_LOOP;
}

void wifi_manager_device_state_changed_callback(wifi_manager_device_state_e state, void* user_data)
{
	g_bWifiManagerCB = true;
	PRINT_RETURN("wifi_manager_device_state_changed_callback", WIFI_MANAGER_ERROR_NONE);
	QUIT_GMAIN_LOOP;
}

void wifi_manager_connection_state_changed_callback(wifi_manager_connection_state_e state, wifi_manager_ap_h ap, void* user_data)
{
	g_bWifiManagerCB = true;
	PRINT_RETURN("wifi_manager_connection_state_changed_callback", WIFI_MANAGER_ERROR_NONE);
	// Do not quit the mainloop here. The mainloop will be finished after invoking activated(or deactivated) callback.
}

void wifi_manager_forget_ap_async_callback(wifi_manager_error_e result, void *user_data)
{
	PRINT_RETURN("wifi_manager_forget_ap_async_callback", WIFI_MANAGER_ERROR_NONE);

	g_nCallbackRet = true;
	QUIT_GMAIN_LOOP;
}

void wifi_manager_rssi_level_changed_callback(wifi_manager_rssi_level_e rssi_level, void* user_data)
{
	g_bWifiManagerCB = true;
	PRINT_RETURN("wifi_manager_rssi_level_changed_callback", WIFI_MANAGER_ERROR_NONE);
	QUIT_GMAIN_LOOP;
}

bool wifi_manager_foreach_configuration_cb(const wifi_manager_config_h config, void *user_data)
{
	g_bWifiManagerCB = true;
	PRINT_RETURN("wifi_manager_foreach_configuration_cb", WIFI_MANAGER_ERROR_NONE);

	g_nCallbackRet = WIFI_MANAGER_ERROR_NONE;
	return false;
}

void wifi_manager_tdls_state_changed_callback(wifi_manager_tdls_state_e state, char* peer_mac_addr, void* user_data)
{
	g_bWifiManagerCB = true;
	PRINT_RETURN("wifi_manager_tdls_state_changed_callback", WIFI_MANAGER_ERROR_NONE);
}

bool wifi_manager_ap_ipv6_address_callback(char *ipv6_address, void *user_data)
{
	g_bWifiManagerCB = true;
	PRINT_RETURN("wifi_manager_ap_ipv6_address_callback", WIFI_MANAGER_ERROR_NONE);
	return false;
}

void wifi_manager_bssid_scan_finished_callback(wifi_manager_error_e result, void *user_data)
{
	g_bWifiManagerCB = true;
	PRINT_RETURN("wifi_manager_bssid_scan_finished_callback", WIFI_MANAGER_ERROR_NONE);
	g_nCallbackRet = result;
	QUIT_GMAIN_LOOP;
}

bool wifi_manager_foreach_found_bssid_ap_callback(wifi_manager_ap_h ap, void *user_data)
{
	g_bWifiManagerCB = true;
	PRINT_RETURN("wifi_manager_foreach_found_bssid_ap_callback", WIFI_MANAGER_ERROR_NONE);
	QUIT_GMAIN_LOOP;
	return false;
}

int wifi_manager_pre_activate(void)
{
	if (g_bFeatureWifi) {
		bool activated;
		int ret = WIFI_MANAGER_ERROR_NONE;

		ret = wifi_manager_is_activated(g_hWifi, &activated);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, ret, "wifi_manager_is_activated", WifiManagerGetError(ret));

		if (!activated)
		{
			g_bWifiManagerCB = false;
			ret = wifi_manager_activate(g_hWifi, wifi_manager_activated_callback, NULL);
			CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, ret, "wifi_manager_activate", WifiManagerGetError(ret));
			RUN_POLLING_LOOP;
			if( !g_bWifiManagerCB )
			{
				FPRINTF("[%s:%d] wifi_manager_activate not invoked!!\\n", __FILE__, __LINE__);
				dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_activate not invoked!!", __FILE__, __LINE__);
				return 1;
			}
		}
		return WIFI_MANAGER_ERROR_NONE;
	} else
		return WIFI_MANAGER_ERROR_NOT_SUPPORTED;

}
int wifi_manager_pre_deactivate(void)
{
	if (g_bFeatureWifi) {
		bool activated;
		int ret = WIFI_MANAGER_ERROR_NONE;

		ret = wifi_manager_is_activated(g_hWifi, &activated);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, ret, "wifi_manager_is_activated", WifiManagerGetError(ret));

		if (activated)
		{
			g_bWifiManagerCB = false;
			ret = wifi_manager_deactivate(g_hWifi, wifi_manager_deactivated_callback, NULL);
			CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, ret, "wifi_manager_deactivate", WifiManagerGetError(ret));
			RUN_POLLING_LOOP;
			if( !g_bWifiManagerCB )
			{
				FPRINTF("[%s:%d] wifi_manager_deactivate not invoked!!\\n", __FILE__, __LINE__);
				dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_deactivate not invoked!!", __FILE__, __LINE__);
				return 1;
			}
		}
		return WIFI_MANAGER_ERROR_NONE;
	} else
		return WIFI_MANAGER_ERROR_NOT_SUPPORTED;

}

static int _wifi_manager_pre_connect(void)
{
	wifi_manager_connection_state_e connection_state;
	char ap_name[CONFIG_VALUE_LEN_MAX] = {0,};
	char ap_passphrase[CONFIG_VALUE_LEN_MAX] = {0,};
	bool required = false;
	int ret = WIFI_MANAGER_ERROR_NONE;

	ret = wifi_manager_pre_activate();
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, ret, "wifi_manager_pre_activate", WifiManagerGetError(ret));

	ret = wifi_manager_get_connection_state(g_hWifi, &connection_state);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, ret, "wifi_manager_get_connection_state", WifiManagerGetError(ret));

	if (connection_state == WIFI_MANAGER_CONNECTION_STATE_CONNECTED)
	{
		FPRINTF("[%s:%d] Connection State is connected.\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Connection State is connected.", __FILE__, __LINE__);
		return WIFI_MANAGER_ERROR_NONE;
	}

	if (GetValueFromConfigFile("WIFI_WPSACCESSPOINTNAME", ap_name, API_NAMESPACE)
		&& GetValueFromConfigFile("WIFI_ACCESSPOINTPIN", ap_passphrase, API_NAMESPACE)) {
		FPRINTF("[%s:%d] Values Received ap_name = %s, ap_passphrase = %s\\n", __FILE__, __LINE__, ap_name, ap_passphrase);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Values Received ap_name = %s, ap_passphrase = %s", __FILE__, __LINE__, ap_name, ap_passphrase);
	} else {
		FPRINTF("[%s:%d] GetValueFromConfigFile returned error\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Values Received = %s", __FILE__, __LINE__);
		return 1;
	}

	g_bWifiManagerCB = false;
	ret = wifi_manager_scan(g_hWifi, wifi_manager_scanned_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, ret, "wifi_manager_scan", WifiManagerGetError(ret));
	RUN_POLLING_LOOP;
	if (!g_bWifiManagerCB || (g_nCallbackRet != WIFI_MANAGER_ERROR_NONE) )
	{
		FPRINTF("[%s:%d] Callback issue for wifi_manager_scan api\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Callback issue for wifi_manager_scan api", __FILE__, __LINE__);
		return 1;
	}

	ret = wifi_manager_foreach_found_ap(g_hWifi, wifi_manager_found_ap_callback, ap_name);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, ret, "wifi_manager_foreach_found_ap", WifiManagerGetError(ret));

	ret = wifi_manager_ap_is_passphrase_required(g_hWifiAP, &required);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, ret, "wifi_manager_ap_is_passphrase_required", WifiManagerGetError(ret));

	if (required)
	{
		ret = wifi_manager_ap_set_passphrase(g_hWifiAP, ap_passphrase);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, ret, "wifi_manager_ap_set_passphrase", WifiManagerGetError(ret));
	}

	g_bWifiManagerCB = false;
	ret = wifi_manager_connect(g_hWifi, g_hWifiAP, wifi_manager_connected_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, ret, "wifi_manager_connect", WifiManagerGetError(ret));
	RUN_POLLING_LOOP;

	if (!g_bWifiManagerCB || (g_nCallbackRet != WIFI_MANAGER_ERROR_NONE) )
	{
		FPRINTF("[%s:%d] Callback issue for wifi_manager_connect api\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Callback issue for wifi_manager_connect api", __FILE__, __LINE__);
		return 1;
	}

	return WIFI_MANAGER_ERROR_NONE;
}

int wifi_manager_pre_connect(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	for (int i = 0; i < PRE_CONNECT_RETRY; i++) {
		ret = _wifi_manager_pre_connect();

		if (ret != WIFI_MANAGER_ERROR_NONE)
			continue;
		else
			break;
	}

	return ret;
}

void wifi_manager_multi_scan_callback(wifi_manager_error_e result, void* user_data)
{
	g_bWifiManagerCB = true;
	PRINT_RETURN("wifi_manager_multi_scan_callback", WIFI_MANAGER_ERROR_NONE);
	QUIT_GMAIN_LOOP;
}

bool wifi_manager_ap_foreach_vsie_callback(unsigned char *vsie_bytes, int vsie_len, void *user_data)
{
	FPRINTF("[%s:%d] wifi_manager_ap_foreach_vsie_callback\\n", __FILE__, __LINE__);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] wifi_manager_ap_foreach_vsie_callback", __FILE__, __LINE__);

	g_bWifiManagerVsieCB = true;

	if (!vsie_bytes)
		return false;

	return true;
}
bool wifi_manager_foreach_found_bssid_callback(const char *bssid, int rssi, int freq, void *user_data)
{
	FPRINTF("[%s:%d] wifi_manager_foreach_found_bssid_callback\\n", __FILE__, __LINE__);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] wifi_manager_foreach_found_bssid_callback", __FILE__, __LINE__);

	g_bWifiManagerCB = true;

	if (!bssid)
		return false;

	return true;
}

/** @} */
