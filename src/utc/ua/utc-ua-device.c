/*
 * Copyright (c) 2021 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <system_info.h>
#include <glib.h>
#include <dlog.h>
#include <user-awareness.h>

#include "utc-ua-common.h"

/*
static void __ua_device_added_device_cb(int result,
	ua_device_h handle, void *user_data)
{
}
*/

int utc_ua_device_create_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_device_h device_h = NULL;
	char mac_addr_str[] = {"30:AB:6A:09:1B:4C"};
	char device_id_str[] = {"18:54:CF:06:37:FE"};

	if (!ua_is_feature_supported()) {
		ret = ua_device_create(0, NULL, NULL, NULL);
		CHECK_RETURN("ua_device_create", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_device_create(UA_MAC_TYPE_WIFI, mac_addr_str, device_id_str, &device_h);
	CHECK_RETURN("ua_device_create", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_device_create_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_device_create(0, NULL, NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_device_create", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_device_create", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_device_destroy_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_device_h device_h = NULL;
	char mac_addr_str[] = {"30:AB:6A:09:1B:4C"};
	char device_id_str[] = {"18:54:CF:06:37:FE"};

	if (!ua_is_feature_supported()) {
		ret = ua_device_destroy(NULL);
		CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_device_create(UA_MAC_TYPE_WIFI, mac_addr_str, device_id_str, &device_h);
	CHECK_RETURN("ua_device_create", ret, UA_ERROR_NONE);

	ret = ua_device_destroy(device_h);
	CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_device_destroy_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_device_destroy(NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_device_get_mac_type_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_device_h device_h = NULL;
	char mac_addr_str[] = {"30:AB:6A:09:1B:4C"};
	char device_id_str[] = {"18:54:CF:06:37:FE"};
	ua_mac_type_e mac_type = UA_MAC_TYPE_INVALID;

	if (!ua_is_feature_supported()) {
		ret = ua_device_get_mac_type(NULL, NULL);
		CHECK_RETURN("ua_device_get_mac_type", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_device_create(UA_MAC_TYPE_WIFI, mac_addr_str, device_id_str, &device_h);
	CHECK_RETURN("ua_device_create", ret, UA_ERROR_NONE);

	ret = ua_device_get_mac_type(device_h, &mac_type);
	CHECK_RETURN("ua_device_get_mac_type", ret, UA_ERROR_NONE);

	ret = ua_device_destroy(device_h);
	CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_device_get_mac_type_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_device_get_mac_type(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_device_get_mac_type", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_device_get_mac_type", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_device_set_os_info_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_device_h device_h = NULL;
	char mac_addr_str[] = {"30:AB:6A:09:1B:4C"};
	char device_id_str[] = {"18:54:CF:06:37:FE"};

	if (!ua_is_feature_supported()) {
		ret = ua_device_set_os_info(NULL, 0);
		CHECK_RETURN("ua_device_set_os_info", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_device_create(UA_MAC_TYPE_WIFI, mac_addr_str, device_id_str, &device_h);
	CHECK_RETURN("ua_device_create", ret, UA_ERROR_NONE);

	ret = ua_device_set_os_info(device_h, UA_OS_TYPE_TIZEN);
	CHECK_RETURN("ua_device_set_os_info", ret, UA_ERROR_NONE);

	ret = ua_device_destroy(device_h);
	CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_device_set_os_info_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_device_set_os_info(NULL, 0);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_device_set_os_info", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_device_set_os_info", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_device_get_os_info_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_device_h device_h = NULL;
	char mac_addr_str[] = {"30:AB:6A:09:1B:4C"};
	char device_id_str[] = {"18:54:CF:06:37:FE"};
	ua_os_type_e ostype = UA_OS_TYPE_NOT_DEFINED;

	if (!ua_is_feature_supported()) {
		ret = ua_device_get_os_info(NULL, NULL);
		CHECK_RETURN("ua_device_get_os_info", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_device_create(UA_MAC_TYPE_WIFI, mac_addr_str, device_id_str, &device_h);
	CHECK_RETURN("ua_device_create", ret, UA_ERROR_NONE);

	ret = ua_device_get_os_info(device_h, &ostype);
	CHECK_RETURN("ua_device_get_os_info", ret, UA_ERROR_NONE);

	ret = ua_device_destroy(device_h);
	CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_device_get_os_info_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_device_get_os_info(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_device_get_os_info", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_device_get_os_info", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_device_get_mac_address_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_device_h device_h = NULL;
	char mac_addr_str[] = {"30:AB:6A:09:1B:4C"};
	char device_id_str[] = {"18:54:CF:06:37:FE"};
	char *mac = NULL;

	if (!ua_is_feature_supported()) {
		ret = ua_device_get_mac_address(NULL, NULL);
		CHECK_RETURN("ua_device_get_mac_address", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_device_create(UA_MAC_TYPE_WIFI, mac_addr_str, device_id_str, &device_h);
	CHECK_RETURN("ua_device_create", ret, UA_ERROR_NONE);

	ret = ua_device_get_mac_address(device_h, &mac);
	GFREE(mac);
	CHECK_RETURN("ua_device_get_mac_address", ret, UA_ERROR_NONE);

	ret = ua_device_destroy(device_h);
	CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_device_get_mac_address_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_device_get_mac_address(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_device_get_mac_address", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_device_get_mac_address", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_device_get_device_id_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_device_h device_h = NULL;
	char mac_addr_str[] = {"30:AB:6A:09:1B:4C"};
	char device_id_str[] = {"18:54:CF:06:37:FE"};
	char *device_id = NULL;

	if (!ua_is_feature_supported()) {
		ret = ua_device_get_device_id(NULL, NULL);
		CHECK_RETURN("ua_device_get_device_id", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_device_create(UA_MAC_TYPE_WIFI, mac_addr_str, device_id_str, &device_h);
	CHECK_RETURN("ua_device_create", ret, UA_ERROR_NONE);

	ret = ua_device_get_device_id(device_h, &device_id);
	GFREE(device_id);
	CHECK_RETURN("ua_device_get_device_id", ret, UA_ERROR_NONE);

	ret = ua_device_destroy(device_h);
	CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_device_get_device_id_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_device_get_device_id(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_device_get_device_id", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_device_get_device_id", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_device_set_wifi_bssid_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_device_h device_h = NULL;
	char mac_addr_str[] = {"30:AB:6A:09:1B:4C"};
	char device_id_str[] = {"18:54:CF:06:37:FE"};
	char wifi_bssid[] = {"30:AB:6A:09:1B:4C"};

	if (!ua_is_feature_supported()) {
		ret = ua_device_set_wifi_bssid(NULL, NULL);
		CHECK_RETURN("ua_device_set_wifi_bssid", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_device_create(UA_MAC_TYPE_WIFI, mac_addr_str, device_id_str, &device_h);
	CHECK_RETURN("ua_device_create", ret, UA_ERROR_NONE);

	ret = ua_device_set_wifi_bssid(device_h, wifi_bssid);
	CHECK_RETURN("ua_device_set_wifi_bssid", ret, UA_ERROR_NONE);

	ret = ua_device_destroy(device_h);
	CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_device_set_wifi_bssid_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_device_set_wifi_bssid(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_device_set_wifi_bssid", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_device_set_wifi_bssid", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_device_get_wifi_bssid_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_device_h device_h = NULL;
	char mac_addr_str[] = {"30:AB:6A:09:1B:4C"};
	char device_id_str[] = {"18:54:CF:06:37:FE"};
	char *wifi_bssid = NULL;

	if (!ua_is_feature_supported()) {
		ret = ua_device_get_wifi_bssid(NULL, NULL);
		CHECK_RETURN("ua_device_get_wifi_bssid", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_device_create(UA_MAC_TYPE_WIFI, mac_addr_str, device_id_str, &device_h);
	CHECK_RETURN("ua_device_create", ret, UA_ERROR_NONE);

	ret = ua_device_get_wifi_bssid(device_h, &wifi_bssid);
	GFREE(wifi_bssid);
	CHECK_RETURN("ua_device_get_wifi_bssid", ret, UA_ERROR_NONE);

	ret = ua_device_destroy(device_h);
	CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_device_get_wifi_bssid_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_device_get_wifi_bssid(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_device_get_wifi_bssid", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_device_get_wifi_bssid", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_device_set_wifi_ipv4_address_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_device_h device_h = NULL;
	char mac_addr_str[] = {"30:AB:6A:09:1B:4C"};
	char device_id_str[] = {"18:54:CF:06:37:FE"};
	char ipv4_address[] = {"192.168.107.10"};

	if (!ua_is_feature_supported()) {
		ret = ua_device_set_wifi_ipv4_address(NULL, NULL);
		CHECK_RETURN("ua_device_set_wifi_ipv4_address", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_device_create(UA_MAC_TYPE_WIFI, mac_addr_str, device_id_str, &device_h);
	CHECK_RETURN("ua_device_create", ret, UA_ERROR_NONE);

	ret = ua_device_set_wifi_ipv4_address(device_h, ipv4_address);
	CHECK_RETURN("ua_device_set_wifi_ipv4_address", ret, UA_ERROR_NONE);

	ret = ua_device_destroy(device_h);
	CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_device_set_wifi_ipv4_address_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_device_set_wifi_ipv4_address(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_device_set_wifi_ipv4_address", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_device_set_wifi_ipv4_address", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_device_get_wifi_ipv4_address_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_device_h device_h = NULL;
	char mac_addr_str[] = {"30:AB:6A:09:1B:4C"};
	char device_id_str[] = {"18:54:CF:06:37:FE"};
	char *ipv4_address = NULL;

	if (!ua_is_feature_supported()) {
		ret = ua_device_get_wifi_ipv4_address(NULL, NULL);
		CHECK_RETURN("ua_device_get_wifi_ipv4_address", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_device_create(UA_MAC_TYPE_WIFI, mac_addr_str, device_id_str, &device_h);
	CHECK_RETURN("ua_device_create", ret, UA_ERROR_NONE);

	ret = ua_device_get_wifi_ipv4_address(device_h, &ipv4_address);
	GFREE(ipv4_address);
	CHECK_RETURN("ua_device_get_wifi_ipv4_address", ret, UA_ERROR_NONE);

	ret = ua_device_destroy(device_h);
	CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_device_get_wifi_ipv4_address_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_device_get_wifi_ipv4_address(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_device_get_wifi_ipv4_address", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_device_get_wifi_ipv4_address", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_device_get_last_presence_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_device_h device_h = NULL;
	char mac_addr_str[] = {"30:AB:6A:09:1B:4C"};
	char device_id_str[] = {"18:54:CF:06:37:FE"};
	unsigned long long last_seen = 0;

	if (!ua_is_feature_supported()) {
		ret = ua_device_get_last_presence(NULL, NULL);
		CHECK_RETURN("ua_device_get_last_presence", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_device_create(UA_MAC_TYPE_WIFI, mac_addr_str, device_id_str, &device_h);
	CHECK_RETURN("ua_device_create", ret, UA_ERROR_NONE);

	ret = ua_device_get_last_presence(device_h, &last_seen);
	CHECK_RETURN("ua_device_get_last_presence", ret, UA_ERROR_NONE);

	ret = ua_device_destroy(device_h);
	CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_device_get_last_presence_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_device_get_last_presence(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_device_get_last_presence", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_device_get_last_presence", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_device_get_pairing_required_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_device_h device_h = NULL;
	char mac_addr_str[] = {"30:AB:6A:09:1B:4C"};
	char device_id_str[] = {"18:54:CF:06:37:FE"};
	bool required = false;

	if (!ua_is_feature_supported()) {
		ret = ua_device_get_pairing_required(NULL, NULL);
		CHECK_RETURN("ua_device_get_last_presence", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_device_create(UA_MAC_TYPE_WIFI, mac_addr_str, device_id_str, &device_h);
	CHECK_RETURN("ua_device_create", ret, UA_ERROR_NONE);

	ret = ua_device_get_pairing_required(device_h, &required);
	CHECK_RETURN("ua_device_get_pairing_required", ret, UA_ERROR_NONE);

	ret = ua_device_destroy(device_h);
	CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_device_get_pairing_required_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_device_get_pairing_required(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_device_get_pairing_required", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_device_get_pairing_required", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

#if 0
int utc_ua_device_update_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_user_h user_h = NULL;
	ua_device_h device_h = NULL;
	char user_account_str[] = {"default@default.com"};
	char mac_addr_str[] = {"30:AB:6A:09:1B:4C"};
	char device_id_str[] = {"18:54:CF:06:37:FE"};

	if (!ua_is_feature_supported()) {
		ret = ua_device_update(NULL);
		CHECK_RETURN("ua_device_update", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_user_create(user_account_str, &user_h);
	CHECK_RETURN("ua_user_create", ret, UA_ERROR_NONE);

	ret = ua_device_create(UA_MAC_TYPE_WIFI, mac_addr_str, device_id_str, &device_h);
	CHECK_RETURN("ua_device_create", ret, UA_ERROR_NONE);

	ret = ua_user_add_device(user_h, device_h, __ua_device_added_device_cb, NULL);
	CHECK_RETURN("ua_user_add_device", ret, UA_ERROR_NONE);

	ret = ua_device_update(device_h);
	CHECK_RETURN("ua_device_update", ret, UA_ERROR_NONE);

	ret = ua_user_remove_device(user_h, device_h);
	CHECK_RETURN("ua_user_remove_device", ret, UA_ERROR_NONE);

	ret = ua_device_destroy(device_h);
	CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NONE);

	ret = ua_user_destroy(user_h);
	CHECK_RETURN("ua_user_destroy", ret, UA_ERROR_NONE);

	return 0;
}
#endif

int utc_ua_device_update_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_device_update(NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_device_update", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_device_update", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_device_get_by_mac_address_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_device_h device_h = NULL;
	ua_device_h get_device_h = NULL;
	char mac_addr_str[] = {"30:AB:6A:09:1B:4C"};
	char device_id_str[] = {"18:54:CF:06:37:FE"};

	if (!ua_is_feature_supported()) {
		ret = ua_device_get_by_mac_address(NULL, NULL);
		CHECK_RETURN("ua_device_get_by_mac_address", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_device_create(UA_MAC_TYPE_WIFI, mac_addr_str, device_id_str, &device_h);
	CHECK_RETURN("ua_device_create", ret, UA_ERROR_NONE);

	ret = ua_device_get_by_mac_address(mac_addr_str, &get_device_h);
	CHECK_RETURN("ua_device_get_by_mac_address", ret, UA_ERROR_NONE);

	ret = ua_device_destroy(device_h);
	CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_device_get_by_mac_address_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_device_get_by_mac_address(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_device_get_by_mac_address", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_device_get_by_mac_address", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_device_get_by_device_id_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_device_h device_h = NULL;
	ua_device_h get_device_h = NULL;
	char mac_addr_str[] = {"30:AB:6A:09:1B:4C"};
	char device_id_str[] = {"18:54:CF:06:37:FE"};

	if (!ua_is_feature_supported()) {
		ret = ua_device_get_by_device_id(NULL, 0, NULL);
		CHECK_RETURN("ua_device_get_by_device_id", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_device_create(UA_MAC_TYPE_WIFI, mac_addr_str, device_id_str, &device_h);
	CHECK_RETURN("ua_device_create", ret, UA_ERROR_NONE);

	ret = ua_device_get_by_device_id(device_id_str, UA_MAC_TYPE_WIFI, &get_device_h);
	CHECK_RETURN("ua_device_get_by_device_id", ret, UA_ERROR_NONE);

	ret = ua_device_destroy(device_h);
	CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_device_get_by_device_id_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_device_get_by_device_id(NULL, 0, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_device_get_by_device_id", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_device_get_by_device_id", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
