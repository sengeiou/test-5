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
static void __ua_user_added_device_cb(int result,
	ua_device_h handle, void *user_data)
{
}

static bool __ua_user_foreach_added_device_cb(ua_device_h device_handle,
	void *user_data)
{
	return true;
}
*/

int utc_ua_user_create_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_user_h user_h = NULL;
	char user_account_str[] = {"default@default.com"};

	if (!ua_is_feature_supported()) {
		ret = ua_user_create(NULL, NULL);
		CHECK_RETURN("ua_user_create", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_user_create(user_account_str, &user_h);
	CHECK_RETURN("ua_user_create", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_user_create_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_user_create(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_user_create", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_user_create", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_user_destroy_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_user_h user_h = NULL;
	char user_account_str[] = {"default@default.com"};

	if (!ua_is_feature_supported()) {
		ret = ua_user_destroy(NULL);
		CHECK_RETURN("ua_user_destroy", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_user_create(user_account_str, &user_h);
	CHECK_RETURN("ua_user_create", ret, UA_ERROR_NONE);

	ret = ua_user_destroy(user_h);
	CHECK_RETURN("ua_user_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_user_destroy_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_user_destroy(NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_user_destroy", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_user_destroy", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_user_add_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_user_h user_h = NULL;
	char user_account_str[] = {"default@default.com"};

	if (!ua_is_feature_supported()) {
		ret = ua_user_add(NULL);
		CHECK_RETURN("ua_user_add", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_user_create(user_account_str, &user_h);
	CHECK_RETURN("ua_user_create", ret, UA_ERROR_NONE);

	ret = ua_user_add(user_h);
	CHECK2_RETURN("ua_user_add", ret, UA_ERROR_NONE, UA_ERROR_ALREADY_REGISTERED);

	ret = ua_user_remove(user_h);
	CHECK_RETURN("ua_user_remove", ret, UA_ERROR_NONE);

	ret = ua_user_destroy(user_h);
	CHECK_RETURN("ua_user_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_user_add_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_user_add(NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_user_add", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_user_add", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_user_remove_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_user_h user_h = NULL;
	char user_account_str[] = {"default@default.com"};

	if (!ua_is_feature_supported()) {
		ret = ua_user_remove(NULL);
		CHECK_RETURN("ua_user_remove", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_user_create(user_account_str, &user_h);
	CHECK_RETURN("ua_user_create", ret, UA_ERROR_NONE);

	ret = ua_user_add(user_h);
	CHECK2_RETURN("ua_user_add", ret, UA_ERROR_NONE, UA_ERROR_ALREADY_REGISTERED);

	ret = ua_user_remove(user_h);
	CHECK_RETURN("ua_user_remove", ret, UA_ERROR_NONE);

	ret = ua_user_destroy(user_h);
	CHECK_RETURN("ua_user_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_user_remove_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_user_remove(NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_user_remove", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_user_remove", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_user_get_account_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_user_h user_h = NULL;
	char user_account_str[] = {"default@default.com"};
	char *account = NULL;

	if (!ua_is_feature_supported()) {
		ret = ua_user_get_account(NULL, NULL);
		CHECK_RETURN("ua_user_get_account", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_user_create(user_account_str, &user_h);
	CHECK_RETURN("ua_user_create", ret, UA_ERROR_NONE);

	ret = ua_user_get_account(user_h, &account);
	GFREE(account);
	CHECK_RETURN("ua_user_get_account", ret, UA_ERROR_NONE);

	ret = ua_user_destroy(user_h);
	CHECK_RETURN("ua_user_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_user_get_account_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_user_get_account(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_user_get_account", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_user_get_account", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

#if 0
int utc_ua_user_add_device_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_user_h user_h = NULL;
	ua_device_h device_h = NULL;
	char user_account_str[] = {"default@default.com"};
	char mac_addr_str[] = {"30:AB:6A:09:1B:4C"};
	char device_id_str[] = {"18:54:CF:06:37:FE"};

	if (!ua_is_feature_supported()) {
		ret = ua_user_add_device(NULL, NULL, NULL, NULL);
		CHECK_RETURN("ua_user_add_device", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_user_create(user_account_str, &user_h);
	CHECK_RETURN("ua_user_create", ret, UA_ERROR_NONE);

	ret = ua_user_add(user_h);
	CHECK2_RETURN("ua_user_add", ret, UA_ERROR_NONE, UA_ERROR_ALREADY_REGISTERED);

	ret = ua_device_create(UA_MAC_TYPE_WIFI, mac_addr_str, device_id_str, &device_h);
	CHECK_RETURN("ua_device_create", ret, UA_ERROR_NONE);

	ret = ua_user_add_device(user_h, device_h, __ua_user_added_device_cb, NULL);
	CHECK_RETURN("ua_user_add_device", ret, UA_ERROR_NONE);

	ret = ua_user_remove_device(user_h, device_h);
	CHECK_RETURN("ua_user_remove_device", ret, UA_ERROR_NONE);

	ret = ua_user_remove(user_h);
	CHECK_RETURN("ua_user_remove", ret, UA_ERROR_NONE);

	ret = ua_device_destroy(device_h);
	CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NONE);

	ret = ua_user_destroy(user_h);
	CHECK_RETURN("ua_user_destroy", ret, UA_ERROR_NONE);

	return 0;
}
#endif

int utc_ua_user_add_device_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_user_add_device(NULL, NULL, NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_user_add_device", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_user_add_device", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

#if 0
int utc_ua_user_remove_device_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_user_h user_h = NULL;
	ua_device_h device_h = NULL;
	char user_account_str[] = {"default@default.com"};
	char mac_addr_str[] = {"30:AB:6A:09:1B:4C"};
	char device_id_str[] = {"18:54:CF:06:37:FE"};

	if (!ua_is_feature_supported()) {
		ret = ua_user_remove_device(NULL, NULL);
		CHECK_RETURN("ua_user_remove_device", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_user_create(user_account_str, &user_h);
	CHECK_RETURN("ua_user_create", ret, UA_ERROR_NONE);

	ret = ua_user_add(user_h);
	CHECK2_RETURN("ua_user_add", ret, UA_ERROR_NONE, UA_ERROR_ALREADY_REGISTERED);

	ret = ua_device_create(UA_MAC_TYPE_WIFI, mac_addr_str, device_id_str, &device_h);
	CHECK_RETURN("ua_device_create", ret, UA_ERROR_NONE);

	ret = ua_user_add_device(user_h, device_h, __ua_user_added_device_cb, NULL);
	CHECK_RETURN("ua_user_add_device", ret, UA_ERROR_NONE);

	ret = ua_user_remove_device(user_h, device_h);
	CHECK_RETURN("ua_user_remove_device", ret, UA_ERROR_NONE);

	ret = ua_device_destroy(device_h);
	CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NONE);

	ret = ua_user_remove(user_h);
	CHECK_RETURN("ua_user_remove", ret, UA_ERROR_NONE);

	ret = ua_user_destroy(user_h);
	CHECK_RETURN("ua_user_destroy", ret, UA_ERROR_NONE);

	return 0;
}
#endif

int utc_ua_user_remove_device_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_user_remove_device(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_user_remove_device", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_user_remove_device", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

#if 0
int utc_ua_user_foreach_devices_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_user_h user_h = NULL;
	ua_device_h device_h = NULL;
	char user_account_str[] = {"default@default.com"};
	char mac_addr_str[] = {"30:AB:6A:09:1B:4C"};
	char device_id_str[] = {"18:54:CF:06:37:FE"};

	if (!ua_is_feature_supported()) {
		ret = ua_user_foreach_devices(NULL, NULL, NULL);
		CHECK_RETURN("ua_user_foreach_devices", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_user_create(user_account_str, &user_h);
	CHECK_RETURN("ua_user_create", ret, UA_ERROR_NONE);

	ret = ua_user_add(user_h);
	CHECK2_RETURN("ua_user_add", ret, UA_ERROR_NONE, UA_ERROR_ALREADY_REGISTERED);

	ret = ua_device_create(UA_MAC_TYPE_WIFI, mac_addr_str, device_id_str, &device_h);
	CHECK_RETURN("ua_device_create", ret, UA_ERROR_NONE);

	ret = ua_user_add_device(user_h, device_h, __ua_user_added_device_cb, NULL);
	CHECK_RETURN("ua_user_add_device", ret, UA_ERROR_NONE);

	ret = ua_user_foreach_devices(user_h, __ua_user_foreach_added_device_cb, NULL);
	CHECK_RETURN("ua_user_foreach_devices", ret, UA_ERROR_NONE);

	ret = ua_user_remove_device(user_h, device_h);
	CHECK_RETURN("ua_user_remove_device", ret, UA_ERROR_NONE);

	ret = ua_user_remove(user_h);
	CHECK_RETURN("ua_user_remove", ret, UA_ERROR_NONE);

	ret = ua_device_destroy(device_h);
	CHECK_RETURN("ua_device_destroy", ret, UA_ERROR_NONE);

	ret = ua_user_destroy(user_h);
	CHECK_RETURN("ua_user_destroy", ret, UA_ERROR_NONE);

	return 0;
}
#endif

int utc_ua_user_foreach_devices_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_user_foreach_devices(NULL, NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_user_foreach_devices", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_user_foreach_devices", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
