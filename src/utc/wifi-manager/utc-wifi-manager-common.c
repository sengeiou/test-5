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

#include "utc-wifi-manager-common.h"

gboolean wifi_manager_callback_timeout(gpointer data)
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

char* wifi_manager_get_error(int error)
{
	char *error_value = NULL;
	switch (error) {
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
	default:
		error_value = "Unknown Error";
		break;
	}
	return error_value;
}

bool wifi_manager_get_value_from_configfile(char* key, char* value)
{
	FILE* pfilePtr = fopen(CONFIGFILE_PATH, "r");

	if (NULL == pfilePtr)
		return false;

	char* pszKey = NULL;
	char* pszValue = NULL;
	char* pszDelim = "=\n";
	char* temp = NULL;
	char szConfigLine[CONFIG_LINE_LEN_MAX] = {0,};
	bool bvalue = false;

	while (!feof(pfilePtr)) {
		if (fgets(szConfigLine, CONFIG_LINE_LEN_MAX, pfilePtr) != NULL) {
			pszKey = strtok_r(szConfigLine, pszDelim, &temp);
			pszValue = strtok_r(NULL, pszDelim, &temp);
			if (pszKey != NULL) {
				if ((pszValue != NULL) && (strstr(pszKey, key) != NULL) ) {
					memset(value, 0, CONFIG_VALUE_LEN_MAX);
					strncpy(value, pszValue, CONFIG_VALUE_LEN_MAX);
					bvalue = true;
				}
				if (bvalue)
					break;

				pszKey = NULL;
				pszValue = NULL;
			}
		}
	}

	fclose(pfilePtr);
	if (NULL == pszValue)
		return false;

	if (strlen(pszValue) >= CONFIG_VALUE_LEN_MAX)
		return false;

	return true;
}

bool wifi_manager_check_feature_supported(char *key)
{
	bool value = false;
	int ret = system_info_get_platform_bool(key, &value);

	if (ret != SYSTEM_INFO_ERROR_NONE) {
		FPRINTF("[%s:%d] system_info_get_platform_bool failed, error returned = %d\\n", __FILE__, __LINE__, ret);
		return false;
	}

	if (value) {
		FPRINTF("[%s:%d] %s feature is supported\\n", __FILE__, __LINE__, key);
	} else {
		FPRINTF("[%s:%d] %s feature is not supported\\n", __FILE__, __LINE__, key);
	}

	return value;
}

void wifi_manager_activated_callback(wifi_manager_error_e result, void* user_data)
{
	PRINT_RETURN("wifi_manager_activated_callback", result);

	g_nCallbackRet = result;
	QUIT_GMAIN_LOOP;
}

void wifi_manager_deactivated_callback(wifi_manager_error_e result, void* user_data)
{
	PRINT_RETURN("wifi_manager_deactivate_callback", result);

	g_nCallbackRet = result;
	QUIT_GMAIN_LOOP;
}

void wifi_manager_activated_with_picker_callback(wifi_manager_error_e result, void* user_data)
{
	PRINT_RETURN("wifi_manager_activated_with_picker_callback", result);

	g_nCallbackRet = result;
	QUIT_GMAIN_LOOP;
}

void wifi_manager_scanned_callback(wifi_manager_error_e result, void* user_data)
{
	PRINT_RETURN("wifi_manager_scanned_callback", result);

	g_nCallbackRet = result;
	QUIT_GMAIN_LOOP;
}

void wifi_manager_background_scanned_callback(wifi_manager_error_e result, void* user_data)
{
	PRINT_RETURN("wifi_manager_background_scanned_callback", result);
}

bool wifi_manager_found_ap_callback(wifi_manager_ap_h ap, void *user_data)
{
	PRINT_RETURN("wifi_manager_scanned_callback", WIFI_MANAGER_ERROR_NONE);

	char *ap_name;
	char *ap_name_part = (char *)user_data;
	int ret = WIFI_MANAGER_ERROR_NONE;

	if (ap) {
		ret = wifi_manager_ap_get_essid(ap, &ap_name);
		CHECK_RETURN("wifi_manager_ap_get_essid", ret, WIFI_MANAGER_ERROR_NONE);

		FPRINTF("[%s:%d] AP ssid : %s\\n", __FILE__, __LINE__, ap_name);
		if (!strcmp(ap_name, ap_name_part)) {
			FREE_MEMORY(ap_name);
			ret = wifi_manager_ap_clone(&g_hWifiAP, ap);
			CHECK_RETURN("wifi_manager_ap_clone", ret, WIFI_MANAGER_ERROR_NONE);
			if (g_hWifiAP) {
				g_nCallbackRet = WIFI_MANAGER_ERROR_NONE;
				return false;
			}
		}
	}

	return true;
}

bool wifi_manager_foreach_found_ap_callback(wifi_manager_ap_h ap, void *user_data)
{
	PRINT_RETURN("wifi_manager_foreach_found_ap_callback", WIFI_MANAGER_ERROR_NONE);
	return false;
}

void wifi_manager_scanned_specific_ap_callback(wifi_manager_error_e result, void* user_data)
{
	PRINT_RETURN("wifi_manager_scanned_specific_ap_callback", result);

	g_nCallbackRet = result;
	QUIT_GMAIN_LOOP;
}

void wifi_manager_bssid_scanned_callback(wifi_manager_error_e result, void* user_data)
{
	PRINT_RETURN("wifi_manager_bssid_scanned_callback", result);

	g_nCallbackRet = result;
	QUIT_GMAIN_LOOP;
}

bool wifi_manager_foreach_found_specific_ap_callback(wifi_manager_ap_h ap, void *user_data)
{
	PRINT_RETURN("wifi_manager_foreach_found_specific_ap_callback", WIFI_MANAGER_ERROR_NONE);
	return false;
}

bool wifi_manager_foreach_found_bssid_ap_callback(wifi_manager_ap_h ap, void *user_data)
{
	PRINT_RETURN("wifi_manager_foreach_found_bssid_ap_callback", WIFI_MANAGER_ERROR_NONE);
	return false;
}

void wifi_manager_connected_callback(wifi_manager_error_e result, void* user_data)
{
	PRINT_RETURN("wifi_manager_connected_callback", result);

	g_nCallbackRet = result;
	QUIT_GMAIN_LOOP;
}

void wifi_manager_disconnected_callback(wifi_manager_error_e result, void* user_data)
{
	PRINT_RETURN("wifi_manager_disconnected_callback", result);

	g_nCallbackRet = result;
	QUIT_GMAIN_LOOP;
}

void wifi_manager_device_state_changed_callback(wifi_manager_device_state_e state, void* user_data)
{
	PRINT_RETURN("wifi_manager_device_state_changed_callback", WIFI_MANAGER_ERROR_NONE);
}

void wifi_manager_scan_state_changed_callback(wifi_manager_scan_state_e state, void* user_data)
{
	PRINT_RETURN("wifi_manager_scan_state_changed_callback", WIFI_MANAGER_ERROR_NONE);
}

void wifi_manager_connection_state_changed_callback(wifi_manager_connection_state_e state, wifi_manager_ap_h ap, void* user_data)
{
	PRINT_RETURN("wifi_manager_connection_state_changed_callback", WIFI_MANAGER_ERROR_NONE);
}

void wifi_manager_rssi_level_changed_callback(wifi_manager_rssi_level_e rssi_level, void* user_data)
{
	PRINT_RETURN("wifi_manager_rssi_level_changed_callback", WIFI_MANAGER_ERROR_NONE);
}

bool wifi_manager_foreach_configuration_cb(const wifi_manager_config_h config, void *user_data)
{
	PRINT_RETURN("wifi_manager_foreach_configuration_cb", WIFI_MANAGER_ERROR_NONE);

	g_nCallbackRet = WIFI_MANAGER_ERROR_NONE;
	return false;
}

void wifi_manager_tdls_state_changed_callback(wifi_manager_tdls_state_e state, char* peer_mac_addr, void* user_data)
{
	PRINT_RETURN("wifi_manager_tdls_state_changed_callback", WIFI_MANAGER_ERROR_NONE);
}

void wifi_manager_tdls_discovered_callback(wifi_manager_tdls_discovery_state_e state, char* peer_mac_addr, void* user_data)
{
	PRINT_RETURN("wifi_manager_tdls_discovered_callback", WIFI_MANAGER_ERROR_NONE);
}

bool wifi_manager_ap_ipv6_address_callback(char *ipv6_address, void *user_data)
{
	return false;
}

void wifi_manager_forget_ap_callback(wifi_manager_connection_state_e state, wifi_manager_ap_h ap, void *user_data)
{
	PRINT_RETURN("wifi_manager_forget_ap_callback", WIFI_MANAGER_ERROR_NONE);
	if (state == WIFI_MANAGER_CONNECTION_STATE_DISCONNECTED)
		QUIT_GMAIN_LOOP;
}

void wifi_manager_forget_ap_async_callback(wifi_manager_error_e result, void *user_data)
{
	PRINT_RETURN("wifi_manager_forget_ap_async_callback", WIFI_MANAGER_ERROR_NONE);

	g_nCallbackRet = result;
	QUIT_GMAIN_LOOP;
}

void wifi_manager_multi_scan_callback(wifi_manager_error_e result, void* user_data)
{
	PRINT_RETURN("wifi_manager_multi_scan_callback", result);

	g_nCallbackRet = result;
	QUIT_GMAIN_LOOP;
}

void wifi_manager_ip_conflict_callback(char *mac, wifi_manager_ip_conflict_state_e state, void *user_data)
{
	PRINT_RETURN("wifi_manager_ip_conflict_callback", WIFI_MANAGER_ERROR_NONE);
}

bool wifi_manager_ap_foreach_vsie_callback(unsigned char *vsie_bytes, int vsie_len, void *user_data)
{
	PRINT_RETURN("wifi_manager_ap_foreach_vsie_callback", WIFI_MANAGER_ERROR_NONE);
	return false;
}

bool wifi_manager_ap_foreach_bssid_list_callback(const char *bssid, int rssi, int freq, void *user_data)
{
	PRINT_RETURN("wifi_manager_ap_foreach_bssid_list_callback", WIFI_MANAGER_ERROR_NONE);
	return false;
}

int wifi_manager_pre_activate(void)
{
	if (g_bFeatureWifi) {
		bool activated;
		int ret = WIFI_MANAGER_ERROR_NONE;

		ret = wifi_manager_is_activated(g_hWifi, &activated);
		CHECK_RETURN("wifi_manager_is_activated", ret, WIFI_MANAGER_ERROR_NONE);

		if (!activated) {
			ret = wifi_manager_activate(g_hWifi, wifi_manager_activated_callback, NULL);
			PRINT_RETURN("wifi_manager_activate", ret);
			RUN_GMAIN_LOOP;
			CHECK_RETURN(CALLBACK_RETURN, g_nCallbackRet, WIFI_MANAGER_ERROR_NONE);
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
		CHECK_RETURN("wifi_manager_is_activated", ret, WIFI_MANAGER_ERROR_NONE);

		if (activated) {
			ret = wifi_manager_deactivate(g_hWifi, wifi_manager_deactivated_callback, NULL);
			PRINT_RETURN("wifi_manager_deactivate", ret);
			RUN_GMAIN_LOOP;
			CHECK_RETURN(CALLBACK_RETURN, g_nCallbackRet, WIFI_MANAGER_ERROR_NONE);
		}
		return WIFI_MANAGER_ERROR_NONE;
	} else
		return WIFI_MANAGER_ERROR_NOT_SUPPORTED;

}

static int _wifi_manager_pre_connect(void)
{
	if (g_bFeatureWifi) {
		wifi_manager_connection_state_e connection_state;
		char ap_name[CONFIG_VALUE_LEN_MAX] = {0,};
		char ap_passphrase[CONFIG_VALUE_LEN_MAX] = {0,};
		bool required = false;
		int ret = WIFI_MANAGER_ERROR_NONE;

		ret = wifi_manager_pre_activate();
		CHECK_RETURN("wifi_manager_pre_activate", ret, WIFI_MANAGER_ERROR_NONE);

		ret = wifi_manager_get_connection_state(g_hWifi, &connection_state);
		CHECK_RETURN("wifi_manager_get_connection_state", ret, WIFI_MANAGER_ERROR_NONE);

		if (connection_state == WIFI_MANAGER_CONNECTION_STATE_CONNECTED)
			return WIFI_MANAGER_ERROR_NONE;

		if (!wifi_manager_get_value_from_configfile("WIFI_WPSACCESSPOINTNAME", ap_name)) {
			FPRINTF("[%s:%d] wifi_manager_get_value_from_configfile(WIFI_WPSACCESSPOINTNAME) failed \\n", __FILE__, __LINE__);
			return -1;
		}

		if (!wifi_manager_get_value_from_configfile("WIFI_ACCESSPOINTPIN", ap_passphrase)) {
			FPRINTF("[%s:%d] wifi_manager_get_value_from_configfile(WIFI_ACCESSPOINTPIN) failed \\n", __FILE__, __LINE__);
			return -1;
		}

		ret = wifi_manager_scan(g_hWifi, wifi_manager_scanned_callback, NULL);
		PRINT_RETURN("wifi_manager_scan", ret);
		RUN_GMAIN_LOOP;
		CHECK_RETURN(CALLBACK_RETURN, g_nCallbackRet, WIFI_MANAGER_ERROR_NONE);

		g_hWifiAP = NULL;
		ret = wifi_manager_foreach_found_ap(g_hWifi, wifi_manager_found_ap_callback, ap_name);
		PRINT_RETURN("wifi_manager_foreach_found_ap", ret);
		if (g_hWifiAP == NULL) {
			FPRINTF("[%s:%d] Not found AP\n", __FILE__, __LINE__);
			return -1;
		}

		ret = wifi_manager_ap_is_passphrase_required(g_hWifiAP, &required);
		CHECK_RETURN("wifi_manager_ap_is_passphrase_required", ret, WIFI_MANAGER_ERROR_NONE);

		if (required) {
			ret = wifi_manager_ap_set_passphrase(g_hWifiAP, ap_passphrase);
			CHECK_RETURN("wifi_manager_ap_set_passphrase", ret, WIFI_MANAGER_ERROR_NONE);
		}

		ret = wifi_manager_connect(g_hWifi, g_hWifiAP, wifi_manager_connected_callback, NULL);
		PRINT_RETURN("wifi_manager_connect", ret);
		RUN_GMAIN_LOOP;
		if (g_nCallbackRet != WIFI_MANAGER_ERROR_NONE
				&& g_nCallbackRet != WIFI_MANAGER_ERROR_ALREADY_EXISTS) {
			return -1;
		}
		return WIFI_MANAGER_ERROR_NONE;
	} else {
		return WIFI_MANAGER_ERROR_NOT_SUPPORTED;
	}

}

int wifi_manager_pre_connect(void)
{
	int ret = WIFI_MANAGER_ERROR_NONE;

	for (int i = 0; i < PRE_CONNECT_RETRY; i++) {
		ret = _wifi_manager_pre_connect();

		if (ret == WIFI_MANAGER_ERROR_NOT_SUPPORTED
				|| ret == WIFI_MANAGER_ERROR_NONE)
			return ret;

		sleep(5);
	}

	return ret;
}
