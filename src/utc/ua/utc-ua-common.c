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

#include "utc-ua-common.h"

static GMainLoop *g_pMainLoop = NULL;
static int g_nCallbackRet = UA_ERROR_NONE;
static bool g_bInitialized = false;
static bool g_bFeatureUA = false;
static bool g_bFeatureUALocation = false;

static gboolean __ua_callback_timeout(gpointer data)
{
	g_nCallbackRet = UA_ERROR_TIMED_OUT;
	PRINT_RETURN("__ua_callback_timeout", g_nCallbackRet);
	QUIT_GMAIN_LOOP;
	return false;
}

static bool __ua_check_feature_supported(char *key)
{
	bool value = false;
	int ret = system_info_get_platform_bool(key, &value);

	if (ret != SYSTEM_INFO_ERROR_NONE)
		return false;

	return value;
}

const char *ua_error_to_string(ua_error_e err)
{
	switch (err) {
	/* CHECK: List all enum values here */
	CASE_TO_STR(UA_ERROR_NONE)
	CASE_TO_STR(UA_ERROR_NOT_PERMITTED)
	CASE_TO_STR(UA_ERROR_INVALID_PARAMETER)
	CASE_TO_STR(UA_ERROR_OUT_OF_MEMORY)
	CASE_TO_STR(UA_ERROR_PERMISSION_DENIED)
	CASE_TO_STR(UA_ERROR_RESOURCE_BUSY)
	CASE_TO_STR(UA_ERROR_TIMED_OUT)
	CASE_TO_STR(UA_ERROR_CANCELED)
	CASE_TO_STR(UA_ERROR_NOW_IN_PROGRESS)
	CASE_TO_STR(UA_ERROR_NOT_SUPPORTED)
	CASE_TO_STR(UA_ERROR_NO_DATA)
	CASE_TO_STR(UA_ERROR_NOT_INITIALIZED)
	CASE_TO_STR(UA_ERROR_NOT_IN_PROGRESS)
	CASE_TO_STR(UA_ERROR_ALREADY_DONE)
	CASE_TO_STR(UA_ERROR_OPERATION_FAILED)
	CASE_TO_STR(UA_ERROR_NOT_READY)
	CASE_TO_STR(UA_ERROR_NOT_ENABLED)
	CASE_TO_STR(UA_ERROR_NOT_FOUND)
	CASE_TO_STR(UA_ERROR_ALREADY_REGISTERED)
	CASE_TO_STR(UA_ERROR_DB_FAILED)
	CASE_TO_STR(UA_ERROR_NOT_REGISTERED)
	default :
		return "UA_ERROR_UNKNOWN";
	}
}

void utc_ua_startup(void)
{
	int ret = UA_ERROR_NONE;

	g_bFeatureUA = __ua_check_feature_supported(UA_FEATURE);
	g_bFeatureUALocation = __ua_check_feature_supported(UA_LOCATION_FEATURE);
	ret = ua_initialize();
	if (g_bFeatureUA) {
		if (UA_ERROR_NONE == ret || UA_ERROR_ALREADY_DONE == ret)
			g_bInitialized = true;
	} else {
		DEBUG_LOG("Feature is not supported");
	}
}

void utc_ua_cleanup(void)
{
	if (g_bFeatureUA && g_bInitialized)
		ua_deinitialize();
}

bool ua_is_initialized(void)
{
	return g_bInitialized;
}

int ua_is_feature_supported(void)
{
	return g_bFeatureUA;
}

int ua_is_feature_location_supported(void)
{
	return g_bFeatureUALocation;
}
