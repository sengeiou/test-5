/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "utc-intelligent-network-monitoring-common.h"

gboolean inm_callback_timeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		FPRINTF("[%s:%d] Quit mainloop(timeout)[%p]", __FILE__, __LINE__, pMainLoop);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Quit mainloop(timeout)[%p]", __FILE__, __LINE__, pMainLoop);
		g_main_loop_quit(pMainLoop);
	}
	FPRINTF("[%s:%d] Callback Timeout\\n", __FILE__, __LINE__);
	dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Callback Timeout", __FILE__, __LINE__);
	return false;
}

char* inm_get_error(int error)
{
	char *error_value = NULL;
	switch (error) {
	case INM_ERROR_NONE:
		error_value = "INM_ERROR_NONE";
		break;
	case INM_ERROR_NOT_PERMITTED:
		error_value = "INM_ERROR_NOT_PERMITTED";
		break;
	case INM_ERROR_OUT_OF_MEMORY:
		error_value = "INM_ERROR_OUT_OF_MEMORY";
		break;
	case INM_ERROR_PERMISSION_DENIED:
		error_value = "INM_ERROR_PERMISSION_DENIED";
		break;
	case INM_ERROR_RESOURCE_BUSY:
		error_value = "INM_ERROR_RESOURCE_BUSY";
		break;
	case INM_ERROR_INVALID_PARAMETER:
		error_value = "INM_ERROR_INVALID_PARAMETER";
		break;
	case INM_ERROR_CONNECTION_TIME_OUT:
		error_value = "INM_ERROR_CONNECTION_TIME_OUT";
		break;
	case INM_ERROR_NOW_IN_PROGRESS:
		error_value = "INM_ERROR_NOW_IN_PROGRESS";
		break;
	case INM_ERROR_NOT_SUPPORTED:
		error_value = "INM_ERROR_NOT_SUPPORTED";
		break;
	case INM_ERROR_NOT_INITIALIZED:
		error_value = "INM_ERROR_NOT_INITIALIZED";
		break;
	case INM_ERROR_ALREADY_INITIALIZED:
		error_value = "INM_ERROR_ALREADY_INITIALIZED";
		break;
	case INM_ERROR_OPERATION_FAILED:
		error_value = "INM_ERROR_OPERATION_FAILED";
		break;
	default:
		error_value = "Unknown Error";
		break;
	}
	return error_value;
}

bool inm_get_value_from_configfile(char* key, char* value)
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
			if(pszKey != NULL) {
				if (strstr(pszKey, key) != NULL) {
					memset(value, 0, CONFIG_VALUE_LEN_MAX);
					strncpy(value, pszValue, CONFIG_VALUE_LEN_MAX);
					bvalue = true;
				}
				if(bvalue)
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

bool inm_check_feature_supported(char *key)
{
	bool value = false;
	int ret = system_info_get_platform_bool(key, &value);

	if (ret != SYSTEM_INFO_ERROR_NONE) {
		FPRINTF("[%s:%d] system_info_get_platform_bool failed, error returned = %d\\n", __FILE__, __LINE__, ret);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] system_info_get_platform_bool failed, error returned = %d\\n", __FILE__, __LINE__, ret);
		return false;
	}

	if (value) {
		FPRINTF("[%s:%d] %s feature is supported\\n", __FILE__, __LINE__, key);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] %s feature is supported\\n", __FILE__, __LINE__, key);
	} else {
		FPRINTF("[%s:%d] %s feature is not supported\\n", __FILE__, __LINE__, key);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] %s feature is not supported\\n", __FILE__, __LINE__, key);
	}

	return value;
}

int inm_get_any_profile(inm_connection_h *profile)
{
	int rv = inm_get_current_connection(g_hInm, profile);
	PRINT_RETURN("inm_get_current_connection", rv);
	if(rv != INM_ERROR_NONE)
		return -1;

	return 1;
}

int inm_get_current_link(inm_link_h *link)
{
	inm_connection_h profile;
	inm_connection_type_e type;
	int  rv;

	rv = inm_get_current_connection(g_hInm, &profile);
	PRINT_RETURN("inm_get_current_connection", rv);
	if(rv != INM_ERROR_NONE)
		return rv;

	rv = inm_connection_get_type(profile, &type);
	PRINT_RETURN("inm_connection_get_type", rv);
	if(rv != INM_ERROR_NONE)
		return rv;

	if (type != INM_CONNECTION_TYPE_WIFI &&
			type != INM_CONNECTION_TYPE_ETHERNET) {
		PRINT_RETURN("unwanted connection type", rv);
	}

	rv = inm_connection_get_link(profile, link);
	PRINT_RETURN("inm_connection_get_link", rv);

	rv = inm_connection_destroy(&profile);
	PRINT_RETURN("inm_connection_destroy", rv);

	return rv;
}

static bool __save_address_callback(inm_link_address_h address, void *user_data)
{
	int rv = inm_link_address_clone(&g_hAddress, address);
	PRINT_RETURN("inm_link_address_clone", rv);

	return FALSE;
}

int inm_save_any_address(inm_link_h link)
{
	assert(link);

	int rv = inm_link_foreach_address(link, __save_address_callback, NULL);

	return rv;
}

static bool __save_route_callback(inm_link_route_h route, void *user_data)
{
	int rv = inm_link_route_clone(&g_hRoute, route);
	PRINT_RETURN("inm_link_route_clone", rv);

	return FALSE;
}

int inm_save_any_route(inm_link_h link)
{
	assert(link);

	int rv = inm_link_foreach_route(link, __save_route_callback, NULL);

	return rv;
}

void inm_wifi_state_changed_callback(inm_wifi_state_e result, void* user_data)
{
	PRINT_RETURN("inm_wifi_state_changed_callback", result);

	g_nCallbackRet = result;
	QUIT_GMAIN_LOOP();
}

void inm_connection_state_changed_callback(inm_connection_state_e state, void* user_data)
{
	char *profile_name;
	inm_connection_h profile = user_data;

	QUIT_GMAIN_LOOP();

	if (profile == NULL)
		return;

	int ret = inm_connection_get_name(profile, &profile_name);
	PRINT_RETURN("inm_connection_get_name", ret);
	if (ret != INM_ERROR_NONE) {
		FREE_MEMORY_TC(profile_name);
		return;
	}

	FREE_MEMORY_TC(profile_name);
}

bool inm_foreach_found_ap_callback(inm_connection_h ap, void *user_data)
{
	PRINT_RETURN("inm_foreach_found_ap_callback", INM_ERROR_NONE);
	return false;
}

bool inm_wifi_ap_foreach_vsie_callback(unsigned char *vsie_bytes, int vsie_len, void *user_data)
{
	PRINT_RETURN("inm_wifi_ap_foreach_vsie_callback", INM_ERROR_NONE);
	return false;
}

void inm_set_ethernet_cable_state_changed_callback(inm_ethernet_cable_state_e result, void* user_data)
{
	PRINT_RETURN("inm_set_ethernet_cable_state_changed_callback", INM_ERROR_NONE);
}

void inm_set_ip_conflict_callback(char *if_name, char *ip, inm_ip_conflict_state_e state, void *user_data)
{
	PRINT_RETURN("inm_set_ip_conflict_callback", INM_ERROR_NONE);
}

void inm_set_congestion_level_callback(inm_congestion_level_e result, void* user_data)
{
	PRINT_RETURN("inm_set_congestion_level_callback", INM_ERROR_NONE);
}

void inm_set_retry_tx_rate_callback(int rate, void* user_data)
{
	PRINT_RETURN("inm_set_retry_tx_rate_callback", INM_ERROR_NONE);
}

void inm_set_channel_interference_callback(int freq, double channel_intf, void* user_data)
{
	PRINT_RETURN("inm_set_channel_interference_callback", INM_ERROR_NONE);
}

void inm_set_cellular_state_changed_callback(inm_cellular_state_e result, void* user_data)
{
	PRINT_RETURN("inm_set_cellular_state_changed_callback", INM_ERROR_NONE);
}

void inm_set_wifi_state_changed_callback(inm_wifi_state_e result, void* user_data)
{
	PRINT_RETURN("inm_set_cellular_state_changed_callback", INM_ERROR_NONE);
}

void inm_set_ethernet_state_changed_callback(inm_ethernet_state_e result, void* user_data)
{
	PRINT_RETURN("inm_set_cellular_state_changed_callback", INM_ERROR_NONE);
}

bool inm_foreach_link_callback(inm_link_h link, void *user_data)
{
	PRINT_RETURN("inm_foreach_link_callback", INM_ERROR_NONE);
	return false;
}

bool inm_foreach_address_callback(inm_link_address_h address, void *user_data)
{
	PRINT_RETURN("inm_foreach_address_callback", INM_ERROR_NONE);
	return false;
}

bool inm_foreach_route_callback(inm_link_route_h route, void *user_data)
{
	PRINT_RETURN("inm_foreach_route_callback", INM_ERROR_NONE);
	return false;
}
