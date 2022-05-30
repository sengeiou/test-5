/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
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
 */
#include <glib.h>
#include <system_info.h>
#include <iotcon.h>

#include "utc-iotcon-common.h"

static bool g_result;
static bool g_feature;
static GMainLoop *g_loop;

enum {
	DEVICE_GET_DEVICE_INFO_P,
	DEVICE_GET_DEVICE_INFO_N,
	DEVICE_GET_DEVICE_INFO_PROPERTY_P,
	DEVICE_GET_DEVICE_INFO_PROPERTY_N,
	DEVICE_GET_PLATFORM_INFO_P,
	DEVICE_GET_PLATFORM_INFO_N,
	DEVICE_GET_PLATFORM_INFO_PROPERTY_P,
	DEVICE_GET_PLATFORM_INFO_PROPERTY_N,
};

static gboolean _device_main_loop_quit_idle(gpointer p)
{
	FN_CALL;
	g_main_loop_quit(g_loop);
	return G_SOURCE_REMOVE;
}

static void _device_main_loop_quit(bool result)
{
	ICUTC_INFO("result = %d", result);
	g_result = result;
	g_idle_add(_device_main_loop_quit_idle, NULL);
}


/**
 * @function      utc_iotcon_device_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_device_startup(void)
{
	int ret;
	char *path;

	g_feature = false;

	icutc_check_wifi_state();

	ret = system_info_get_platform_bool("http://tizen.org/feature/iot.ocf", &g_feature);
	if (SYSTEM_INFO_ERROR_NONE != ret) {
		ICUTC_ERR("system_info_get_platform_bool() Fail(%d)", ret);
		return;
	}

	ret = icutc_get_svr_db_path(&path);
	if (0 != ret) {
		ICUTC_ERR("icutc_get_svr_db_path() Fail(%d)", ret);
		return;
	}

	ICUTC_INFO("path : %s", path);
	ret = iotcon_initialize(path);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_initialize() Fail(%d)", ret);
		free(path);
		return;
	}
	free(path);
}

/**
 * @function      utc_iotcon_device_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_device_cleanup(void)
{
	if (true == g_feature)
		iotcon_deinitialize();
}

static bool _request_device_info(iotcon_device_info_h info, iotcon_error_e result,
		void *user_data)
{
	FN_CALL;
	int i;
	int ret;
	int tc_index = (int)user_data;
	char *value;

	if (IOTCON_ERROR_NONE != result) {
		ICUTC_ERR("iotcon_find_device_info() Fail(%d)", result);
		_device_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}

	switch (tc_index) {
	case DEVICE_GET_DEVICE_INFO_P:
		_device_main_loop_quit(true);
		return IOTCON_FUNC_STOP;

	case DEVICE_GET_DEVICE_INFO_PROPERTY_P:
		for (i = IOTCON_DEVICE_INFO_NAME; i <= IOTCON_DEVICE_INFO_DATA_MODEL_VER; i++) {
			ret = iotcon_device_info_get_property(info, i, &value);
			if (IOTCON_ERROR_NONE != ret) {
				ICUTC_ERR("iotcon_device_info_get_property() Fail(%d)", ret);
				_device_main_loop_quit(false);
				return IOTCON_FUNC_STOP;
			}
		}
		_device_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case DEVICE_GET_DEVICE_INFO_PROPERTY_N:
		for (i = IOTCON_DEVICE_INFO_NAME; i <= IOTCON_DEVICE_INFO_DATA_MODEL_VER; i++) {
			ret = iotcon_device_info_get_property(NULL, i, &value);
			if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
				ICUTC_ERR("iotcon_device_info_get_property() Fail(%d)", ret);
				_device_main_loop_quit(false);
				return IOTCON_FUNC_STOP;
			}
			ret = iotcon_device_info_get_property(info, i, NULL);
			if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
				ICUTC_ERR("iotcon_device_info_get_property() Fail(%d)", ret);
				_device_main_loop_quit(false);
				return IOTCON_FUNC_STOP;
			}
		}
		ret = iotcon_device_info_get_property(info, -1, &value);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_device_info_get_property() Fail(%d)", ret);
			_device_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_device_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case DEVICE_GET_DEVICE_INFO_N:
	default:
		ICUTC_ERR("Invalid tc_index(%d)", tc_index);
		_device_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}
	return IOTCON_FUNC_STOP;
}

/**
 * @testcase      utc_iotcon_find_device_info_n
 * @since_tizen   3.0
 * @description   Test fail getting device information with invalid parameter.
 */
int utc_iotcon_find_device_info_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_find_device_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_ALL,
				NULL, NULL, (void *)DEVICE_GET_DEVICE_INFO_N);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_find_device_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_ALL, NULL,
			NULL, (void *)DEVICE_GET_DEVICE_INFO_N);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_find_device_info_p
 * @since_tizen   3.0
 * @description   Test getting device information.
 */
int utc_iotcon_find_device_info_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_find_device_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP,
				NULL, _request_device_info, (void *)DEVICE_GET_DEVICE_INFO_P);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	g_loop = g_main_loop_new(NULL, FALSE);

	ret = iotcon_find_device_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP,
			NULL, _request_device_info, (void *)DEVICE_GET_DEVICE_INFO_P);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);
	g_loop = NULL;

	if (true == g_result)
		return 0;
	return 1;
}

/**
 * @testcase      utc_iotcon_device_info_get_property_n
 * @since_tizen   3.0
 * @description   Test fail getting properties from device information with invalid parameter.
 */
int utc_iotcon_device_info_get_property_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_find_device_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP,
				NULL, _request_device_info, (void *)DEVICE_GET_DEVICE_INFO_PROPERTY_N);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	g_loop = g_main_loop_new(NULL, FALSE);

	ret = iotcon_find_device_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP,
			NULL, _request_device_info, (void *)DEVICE_GET_DEVICE_INFO_PROPERTY_N);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);
	g_loop = NULL;

	if (true == g_result)
		return 0;
	return 1;
}

/**
 * @testcase      utc_iotcon_device_info_get_property_p
 * @since_tizen   3.0
 * @description   Test getting properties from device information.
 */
int utc_iotcon_device_info_get_property_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_find_device_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP,
				NULL, _request_device_info, (void *)DEVICE_GET_DEVICE_INFO_PROPERTY_P);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	g_loop = g_main_loop_new(NULL, FALSE);

	ret = iotcon_find_device_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP,
			NULL, _request_device_info, (void *)DEVICE_GET_DEVICE_INFO_PROPERTY_P);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);
	g_loop = NULL;

	if (true == g_result)
		return 0;
	return 1;
}

static bool _request_platform_info(iotcon_platform_info_h info, iotcon_error_e result,
		void *user_data)
{
	FN_CALL;
	int i;
	int ret;
	int tc_index = (int)user_data;
	char *value;

	if (IOTCON_ERROR_NONE != result) {
		ICUTC_ERR("iotcon_find_platform_info() Fail(%d)", result);
		_device_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}

	switch (tc_index) {
	case DEVICE_GET_PLATFORM_INFO_P:
		_device_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case DEVICE_GET_PLATFORM_INFO_PROPERTY_P:
		for (i = IOTCON_PLATFORM_INFO_ID; i <= IOTCON_PLATFORM_INFO_SYSTEM_TIME; i++) {
			ret = iotcon_platform_info_get_property(info, i, &value);
			if (IOTCON_ERROR_NONE != ret) {
				ICUTC_ERR("iotcon_platform_info_get_property() Fail(%d)", ret);
				_device_main_loop_quit(false);
				return IOTCON_FUNC_STOP;
			}
		}
		_device_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case DEVICE_GET_PLATFORM_INFO_PROPERTY_N:
		for (i = IOTCON_PLATFORM_INFO_ID; i <= IOTCON_PLATFORM_INFO_SYSTEM_TIME; i++) {
			ret = iotcon_platform_info_get_property(NULL, i, &value);
			if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
				ICUTC_ERR("iotcon_platform_info_get_property() Fail(%d)", ret);
				_device_main_loop_quit(false);
				return IOTCON_FUNC_STOP;
			}
			ret = iotcon_platform_info_get_property(info, i, NULL);
			if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
				ICUTC_ERR("iotcon_platform_info_get_property() Fail(%d)", ret);
				_device_main_loop_quit(false);
				return IOTCON_FUNC_STOP;
			}
		}
		ret = iotcon_platform_info_get_property(info, -1, &value);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_platform_info_get_property() Fail(%d)", ret);
			_device_main_loop_quit(false);
			return IOTCON_FUNC_STOP;
		}
		_device_main_loop_quit(true);
		return IOTCON_FUNC_STOP;
	case DEVICE_GET_PLATFORM_INFO_N:
	default:
		ICUTC_ERR("Invalid tc_index(%d)", tc_index);
		_device_main_loop_quit(false);
		return IOTCON_FUNC_STOP;
	}
	return IOTCON_FUNC_STOP;
}

/**
 * @testcase      utc_iotcon_find_platform_info_n
 * @since_tizen   3.0
 * @description   Test fail getting platform information with invalid parameter.
 */
int utc_iotcon_find_platform_info_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_find_platform_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_ALL,
				NULL, NULL, (void *)DEVICE_GET_PLATFORM_INFO_N);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_find_platform_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_ALL,
			NULL, NULL, (void *)DEVICE_GET_PLATFORM_INFO_N);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_find_platform_info_p
 * @since_tizen   3.0
 * @description   Test getting platform information.
 */
int utc_iotcon_find_platform_info_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_find_platform_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP,
				NULL, _request_platform_info, (void *)DEVICE_GET_PLATFORM_INFO_P);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	g_loop = g_main_loop_new(NULL, FALSE);

	ret = iotcon_find_platform_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP,
			NULL, _request_platform_info, (void *)DEVICE_GET_PLATFORM_INFO_P);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);
	g_loop = NULL;

	if (true == g_result)
		return 0;
	return 1;
}

/**
 * @testcase      utc_iotcon_platform_info_get_property_n
 * @since_tizen   3.0
 * @description   Test fail getting properties from platform information with invalid parameter.
 */
int utc_iotcon_platform_info_get_property_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_find_platform_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP,
				NULL, _request_platform_info, (void *)DEVICE_GET_PLATFORM_INFO_PROPERTY_N);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	g_loop = g_main_loop_new(NULL, FALSE);

	ret = iotcon_find_platform_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP,
			NULL, _request_platform_info, (void *)DEVICE_GET_PLATFORM_INFO_PROPERTY_N);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);
	g_loop = NULL;

	if (true == g_result)
		return 0;
	return 1;
}

/**
 * @testcase      utc_iotcon_platform_info_get_property_p
 * @since_tizen   3.0
 * @description   Test getting properties from platform information.
 */
int utc_iotcon_platform_info_get_property_p(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_find_platform_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP,
				NULL, _request_platform_info, (void *)DEVICE_GET_PLATFORM_INFO_PROPERTY_P);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	g_loop = g_main_loop_new(NULL, FALSE);

	ret = iotcon_find_platform_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP,
			NULL, _request_platform_info, (void *)DEVICE_GET_PLATFORM_INFO_PROPERTY_P);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);
	g_loop = NULL;

	if (true == g_result)
		return 0;
	return 1;
}


