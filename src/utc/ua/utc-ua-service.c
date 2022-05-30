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

static bool __ua_service_foreach_added_user_cb(
	ua_service_h service_handle, ua_user_h user_handle, void *user_data)
{
	if (user_handle) {
		int ret = UA_ERROR_NONE;
		char *account = NULL;

		ret = ua_user_get_account(user_handle, &account);
		if (UA_ERROR_NONE == ret) {
			PRINT_LOG("user account", account);
			GFREE(account);
		}
	}

	return true;
}

int utc_ua_service_create_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_service_h service_h = NULL;
	char service_str[] = {"ua.service.default"};

	if (!ua_is_feature_supported()) {
		ret = ua_service_create(NULL, NULL);
		CHECK_RETURN("ua_service_create", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_service_create(service_str, &service_h);
	CHECK_RETURN("ua_service_create", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_service_create_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_service_create(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_service_create", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_service_create", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_service_destroy_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_service_h service_h = NULL;
	char service_str[] = {"ua.service.default"};

	if (!ua_is_feature_supported()) {
		ret = ua_service_destroy(NULL);
		CHECK_RETURN("ua_service_destroy", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_service_create(service_str, &service_h);
	CHECK_RETURN("ua_service_create", ret, UA_ERROR_NONE);

	ret = ua_service_destroy(service_h);
	CHECK_RETURN("ua_service_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_service_destroy_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_service_destroy(NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_service_destroy", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_service_destroy", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_service_add_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_service_h service_h = NULL;
	char service_str[] = {"ua.service.default"};

	if (!ua_is_feature_supported()) {
		ret = ua_service_add(NULL);
		CHECK_RETURN("ua_service_add", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_service_create(service_str, &service_h);
	CHECK_RETURN("ua_service_create", ret, UA_ERROR_NONE);

	ret = ua_service_add(service_h);
	CHECK2_RETURN("ua_service_add", ret, UA_ERROR_NONE, UA_ERROR_ALREADY_REGISTERED);

	ret = ua_service_remove(service_h);
	CHECK2_RETURN("ua_service_remove", ret, UA_ERROR_NONE, UA_ERROR_NOT_REGISTERED);

	ret = ua_service_destroy(service_h);
	CHECK_RETURN("ua_service_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_service_add_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_service_add(NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_service_add", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_service_add", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_service_update_p(void)
{
	int ret = UA_ERROR_NONE;
	int ret1 = UA_ERROR_NONE;
	int ret2 = UA_ERROR_NONE;
	ua_service_h service_h = NULL;
	char service_str[] = {"ua.service.default"};

	if (!ua_is_feature_supported()) {
		ret = ua_service_update(NULL);
		CHECK_RETURN("ua_service_update", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret1 = ua_get_default_service(&service_h);
	if (UA_ERROR_NONE != ret1) {
		ret = ua_service_create(service_str, &service_h);
		CHECK_RETURN("ua_service_create", ret, UA_ERROR_NONE);

		ret2 = ua_service_add(service_h);
		CHECK2_RETURN("ua_service_add", ret2, UA_ERROR_NONE, UA_ERROR_ALREADY_REGISTERED);
	} else {
		CHECK_RETURN("ua_get_default_service", ret1, UA_ERROR_NONE);
	}

	ret = ua_service_update(service_h);
	CHECK_RETURN("ua_service_update", ret, UA_ERROR_NONE);

	if (UA_ERROR_NONE == ret2) {
		ret = ua_service_remove(service_h);
		CHECK2_RETURN("ua_service_remove", ret, UA_ERROR_NONE, UA_ERROR_NOT_REGISTERED);
	}

	if (UA_ERROR_NONE != ret1) {
		ret = ua_service_destroy(service_h);
		CHECK_RETURN("ua_service_destroy", ret, UA_ERROR_NONE);
	}

	return 0;
}

int utc_ua_service_update_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_service_update(NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_service_update", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_service_update", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_service_remove_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_service_h service_h = NULL;
	char service_str[] = {"ua.service.default"};

	if (!ua_is_feature_supported()) {
		ret = ua_service_remove(NULL);
		CHECK_RETURN("ua_service_remove", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_service_create(service_str, &service_h);
	CHECK_RETURN("ua_service_create", ret, UA_ERROR_NONE);

	ret = ua_service_add(service_h);
	CHECK2_RETURN("ua_service_add", ret, UA_ERROR_NONE, UA_ERROR_ALREADY_REGISTERED);

	ret = ua_service_remove(service_h);
	CHECK2_RETURN("ua_service_remove", ret, UA_ERROR_NONE, UA_ERROR_NOT_REGISTERED);

	ret = ua_service_destroy(service_h);
	CHECK_RETURN("ua_service_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_service_remove_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_service_remove(NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_service_remove", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_service_remove", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_service_get_name_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_service_h service_h = NULL;
	char service_str[] = {"ua.service.default"};
	char *service_name = NULL;

	if (!ua_is_feature_supported()) {
		ret = ua_service_get_name(NULL, NULL);
		CHECK_RETURN("ua_service_get_name", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_service_create(service_str, &service_h);
	CHECK_RETURN("ua_service_create", ret, UA_ERROR_NONE);

	ret = ua_service_get_name(service_h, &service_name);
	GFREE(service_name);
	CHECK_RETURN("ua_service_get_name", ret, UA_ERROR_NONE);

	ret = ua_service_destroy(service_h);
	CHECK_RETURN("ua_service_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_service_get_name_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_service_get_name(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_service_get_name", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_service_get_name", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_service_set_detection_threshold_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_service_h service_h = NULL;
	char service_str[] = {"ua.service.default"};

	if (!ua_is_feature_supported()) {
		ret = ua_service_set_detection_threshold(NULL, 0, 0);
		CHECK_RETURN("ua_service_set_detection_threshold", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_service_create(service_str, &service_h);
	CHECK_RETURN("ua_service_create", ret, UA_ERROR_NONE);

	ret = ua_service_set_detection_threshold(service_h, 0, 0);
	CHECK_RETURN("ua_service_set_detection_threshold", ret, UA_ERROR_NONE);

	ret = ua_service_destroy(service_h);
	CHECK_RETURN("ua_service_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_service_set_detection_threshold_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_service_set_detection_threshold(NULL, 0, 0);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_service_set_detection_threshold", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_service_set_detection_threshold", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_service_get_detection_threshold_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_service_h service_h = NULL;
	char service_str[] = {"ua.service.default"};
	unsigned int presence_threshold = 0;
	unsigned int absence_threshold = 0;

	if (!ua_is_feature_supported()) {
		ret = ua_service_get_detection_threshold(NULL, NULL, NULL);
		CHECK_RETURN("ua_service_get_detection_threshold", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_service_create(service_str, &service_h);
	CHECK_RETURN("ua_service_create", ret, UA_ERROR_NONE);

	ret = ua_service_get_detection_threshold(service_h, &presence_threshold, &absence_threshold);
	CHECK_RETURN("ua_service_get_detection_threshold", ret, UA_ERROR_NONE);

	ret = ua_service_destroy(service_h);
	CHECK_RETURN("ua_service_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_service_get_detection_threshold_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_service_get_detection_threshold(NULL, NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_service_get_detection_threshold", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_service_get_detection_threshold", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_service_get_user_by_account_p(void)
{
	int ret = UA_ERROR_NONE;
	int ret1 = UA_ERROR_NONE;
	int ret2 = UA_ERROR_NONE;
	ua_service_h service_h = NULL;
	ua_user_h user_h = NULL;
	ua_user_h user_handle = NULL;
	char service_str[] = {"ua.service.default"};
	char user_account_str[] = {"default@default.com"};

	if (!ua_is_feature_supported()) {
		ret = ua_service_get_user_by_account(NULL, NULL, NULL);
		CHECK_RETURN("ua_service_get_detection_threshold", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret1 = ua_get_default_service(&service_h);
	if (UA_ERROR_NONE != ret1) {
		ret = ua_service_create(service_str, &service_h);
		CHECK_RETURN("ua_service_create", ret, UA_ERROR_NONE);

		ret2 = ua_service_add(service_h);
		CHECK2_RETURN("ua_service_add", ret2, UA_ERROR_NONE, UA_ERROR_ALREADY_REGISTERED);
	} else {
		CHECK_RETURN("ua_get_default_service", ret1, UA_ERROR_NONE);
	}

	ret = ua_user_create(user_account_str, &user_h);
	CHECK_RETURN("ua_user_create", ret, UA_ERROR_NONE);

	ret = ua_user_add(user_h);
	CHECK2_RETURN("ua_user_add", ret, UA_ERROR_NONE, UA_ERROR_ALREADY_REGISTERED);

	ret = ua_service_add_user(service_h, user_h);
	CHECK_RETURN("ua_service_add_user", ret, UA_ERROR_NONE);

	ret = ua_service_get_user_by_account(service_h, user_account_str, &user_handle);
	CHECK_RETURN("ua_service_get_user_by_account", ret, UA_ERROR_NONE);

	ret = ua_service_remove_user(service_h, user_h);
	CHECK_RETURN("ua_service_remove_user", ret, UA_ERROR_NONE);

	ret = ua_user_remove(user_h);
	CHECK_RETURN("ua_user_remove", ret, UA_ERROR_NONE);

	if (UA_ERROR_NONE == ret2) {
		ret = ua_service_remove(service_h);
		CHECK2_RETURN("ua_service_remove", ret, UA_ERROR_NONE, UA_ERROR_NOT_REGISTERED);
	}

	if (UA_ERROR_NONE != ret1) {
		ret = ua_service_destroy(service_h);
		CHECK_RETURN("ua_service_destroy", ret, UA_ERROR_NONE);
	}

	return 0;
}

int utc_ua_service_get_user_by_account_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_service_get_user_by_account(NULL, NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_service_get_user_by_account", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_service_get_user_by_account", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_service_add_user_p(void)
{
	int ret = UA_ERROR_NONE;
	int ret1 = UA_ERROR_NONE;
	int ret2 = UA_ERROR_NONE;
	ua_service_h service_h = NULL;
	ua_user_h user_h = NULL;
	char service_str[] = {"ua.service.default"};
	char user_account_str[] = {"default@default.com"};

	if (!ua_is_feature_supported()) {
		ret = ua_service_add_user(NULL, NULL);
		CHECK_RETURN("ua_service_add_user", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret1 = ua_get_default_service(&service_h);
	if (UA_ERROR_NONE != ret1) {
		ret = ua_service_create(service_str, &service_h);
		CHECK_RETURN("ua_service_create", ret, UA_ERROR_NONE);

		ret2 = ua_service_add(service_h);
		CHECK2_RETURN("ua_service_add", ret2, UA_ERROR_NONE, UA_ERROR_ALREADY_REGISTERED);
	} else {
		CHECK_RETURN("ua_get_default_service", ret1, UA_ERROR_NONE);
	}

	ret = ua_user_create(user_account_str, &user_h);
	CHECK_RETURN("ua_user_create", ret, UA_ERROR_NONE);

	ret = ua_user_add(user_h);
	CHECK2_RETURN("ua_user_add", ret, UA_ERROR_NONE, UA_ERROR_ALREADY_REGISTERED);

	ret = ua_service_add_user(service_h, user_h);
	CHECK_RETURN("ua_service_add_user", ret, UA_ERROR_NONE);

	ret = ua_service_remove_user(service_h, user_h);
	CHECK_RETURN("ua_service_remove_user", ret, UA_ERROR_NONE);

	ret = ua_user_remove(user_h);
	CHECK_RETURN("ua_user_remove", ret, UA_ERROR_NONE);

	if (UA_ERROR_NONE == ret2) {
		ret = ua_service_remove(service_h);
		CHECK2_RETURN("ua_service_remove", ret, UA_ERROR_NONE, UA_ERROR_NOT_REGISTERED);
	}

	if (UA_ERROR_NONE != ret1) {
		ret = ua_service_destroy(service_h);
		CHECK_RETURN("ua_service_destroy", ret, UA_ERROR_NONE);
	}

	return 0;
}

int utc_ua_service_add_user_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_service_add_user(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_service_add_user", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_service_add_user", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_service_remove_user_p(void)
{
	int ret = UA_ERROR_NONE;
	int ret1 = UA_ERROR_NONE;
	int ret2 = UA_ERROR_NONE;
	ua_service_h service_h = NULL;
	ua_user_h user_h = NULL;
	char service_str[] = {"ua.service.default"};
	char user_account_str[] = {"default@default.com"};

	if (!ua_is_feature_supported()) {
		ret = ua_service_remove_user(NULL, NULL);
		CHECK_RETURN("ua_service_remove_user", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret1 = ua_get_default_service(&service_h);
	if (UA_ERROR_NONE != ret1) {
		ret = ua_service_create(service_str, &service_h);
		CHECK_RETURN("ua_service_create", ret, UA_ERROR_NONE);

		ret2 = ua_service_add(service_h);
		CHECK2_RETURN("ua_service_add", ret2, UA_ERROR_NONE, UA_ERROR_ALREADY_REGISTERED);
	} else {
		CHECK_RETURN("ua_get_default_service", ret1, UA_ERROR_NONE);
	}

	ret = ua_user_create(user_account_str, &user_h);
	CHECK_RETURN("ua_user_create", ret, UA_ERROR_NONE);

	ret = ua_user_add(user_h);
	CHECK2_RETURN("ua_user_add", ret, UA_ERROR_NONE, UA_ERROR_ALREADY_REGISTERED);

	ret = ua_service_add_user(service_h, user_h);
	CHECK_RETURN("ua_service_add_user", ret, UA_ERROR_NONE);

	ret = ua_service_remove_user(service_h, user_h);
	CHECK_RETURN("ua_service_remove_user", ret, UA_ERROR_NONE);

	ret = ua_user_remove(user_h);
	CHECK_RETURN("ua_user_remove", ret, UA_ERROR_NONE);

	if (UA_ERROR_NONE == ret2) {
		ret = ua_service_remove(service_h);
		CHECK2_RETURN("ua_service_remove", ret, UA_ERROR_NONE, UA_ERROR_NOT_REGISTERED);
	}

	if (UA_ERROR_NONE != ret1) {
		ret = ua_service_destroy(service_h);
		CHECK_RETURN("ua_service_destroy", ret, UA_ERROR_NONE);
	}

	return 0;
}

int utc_ua_service_remove_user_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_service_remove_user(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_service_remove_user", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_service_remove_user", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_service_foreach_users_p(void)
{
	int ret = UA_ERROR_NONE;
	int ret1 = UA_ERROR_NONE;
	int ret2 = UA_ERROR_NONE;
	ua_service_h service_h = NULL;
	char service_str[] = {"ua.service.default"};

	if (!ua_is_feature_supported()) {
		ret = ua_service_foreach_users(NULL, NULL, NULL);
		CHECK_RETURN("ua_service_foreach_users", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret1 = ua_get_default_service(&service_h);
	if (UA_ERROR_NONE != ret1) {
		ret = ua_service_create(service_str, &service_h);
		CHECK_RETURN("ua_service_create", ret, UA_ERROR_NONE);

		ret2 = ua_service_add(service_h);
		CHECK2_RETURN("ua_service_add", ret2, UA_ERROR_NONE, UA_ERROR_ALREADY_REGISTERED);
	} else {
		CHECK_RETURN("ua_get_default_service", ret1, UA_ERROR_NONE);
	}

	ret = ua_service_foreach_users(service_h, __ua_service_foreach_added_user_cb, NULL);
	CHECK_RETURN("ua_service_foreach_users", ret, UA_ERROR_NONE);

	if (UA_ERROR_NONE == ret2) {
		ret = ua_service_remove(service_h);
		CHECK2_RETURN("ua_service_remove", ret, UA_ERROR_NONE, UA_ERROR_NOT_REGISTERED);
	}

	if (UA_ERROR_NONE != ret1) {
		ret = ua_service_destroy(service_h);
		CHECK_RETURN("ua_service_destroy", ret, UA_ERROR_NONE);
	}

	return 0;
}

int utc_ua_service_foreach_users_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_service_foreach_users(NULL, NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_service_foreach_users", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_service_foreach_users", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
