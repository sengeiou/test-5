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

static int g_nCallbackRet = UA_ERROR_NONE;

static bool __ua_foreach_service_cb(
	ua_service_h service_handle, void *user_data)
{
	g_nCallbackRet = UA_ERROR_NONE;

	if (service_handle) {
		int ret = UA_ERROR_NONE;
		char *name = NULL;

		ret = ua_service_get_name(service_handle, &name);
		if (UA_ERROR_NONE == ret) {
			PRINT_LOG("service name", name);
			GFREE(name);
		}
	}

	return true;
}

int utc_ua_foreach_service_p(void)
{
	int ret = UA_ERROR_NONE;

	if (!ua_is_feature_supported()) {
		ret = ua_foreach_service(NULL, NULL);
		CHECK_RETURN("ua_foreach_service", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	g_nCallbackRet = UA_ERROR_INVALID_PARAMETER;
	ret = ua_foreach_service(__ua_foreach_service_cb, NULL);
	CHECK_RETURN("ua_foreach_service", ret, UA_ERROR_NONE);
	CHECK_RETURN("g_nCallbackRet", g_nCallbackRet, UA_ERROR_NONE);

	return 0;
}

int utc_ua_foreach_service_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_foreach_service(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_foreach_service", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_foreach_service", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_get_default_service_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_service_h service_h = NULL;
	char *name = NULL;

	if (!ua_is_feature_supported()) {
		ret = ua_get_default_service(NULL);
		CHECK_RETURN("ua_get_default_service", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_get_default_service(&service_h);
	CHECK_RETURN("ua_get_default_service", ret, UA_ERROR_NONE);

	ret = ua_service_get_name(service_h, &name);
	if (UA_ERROR_NONE == ret) {
		PRINT_LOG("default service name", name);
		GFREE(name);
	}

	return 0;
}

int utc_ua_get_default_service_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_get_default_service(NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_get_default_service", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_get_default_service", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_get_service_by_name_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_service_h service_h = NULL;
	ua_service_h get_service_h = NULL;
	char service_str[] = {"ua.service.default"};

	if (!ua_is_feature_supported()) {
		ret = ua_get_service_by_name(NULL, NULL);
		CHECK_RETURN("ua_get_service_by_name", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_service_create(service_str, &service_h);
	CHECK_RETURN("ua_service_create", ret, UA_ERROR_NONE);

	ret = ua_get_service_by_name(service_str, &get_service_h);
	CHECK_RETURN("ua_get_service_by_name", ret, UA_ERROR_NONE);

	ret = ua_service_destroy(service_h);
	CHECK_RETURN("ua_service_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_get_service_by_name_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_get_service_by_name(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_get_service_by_name", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_get_service_by_name", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
