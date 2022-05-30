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

static bool g_feature;

/**
 * @function      utc_iotcon_service_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_service_startup(void)
{
	int ret;
	g_feature = false;

	icutc_check_wifi_state();

	ret = system_info_get_platform_bool("http://tizen.org/feature/iot.ocf", &g_feature);
	if (SYSTEM_INFO_ERROR_NONE != ret) {
		ICUTC_ERR("system_info_get_platform_bool() Fail(%d)", ret);
		return;
	}
}

/**
 * @function      utc_iotcon_service_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_service_cleanup(void)
{
}

/**
 * @testcase      utc_iotcon_initialize_p
 * @since_tizen   3.0
 * @description   Test connecting iotcon service.
 */
int utc_iotcon_initialize_p(void)
{
	int ret;
	char *path = NULL;

	if (false == g_feature) {
		ret = iotcon_initialize(path);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_get_svr_db_path(&path);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_initialize(path);
	free(path);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	iotcon_deinitialize();

	return 0;
}

/**
 * @testcase      utc_iotcon_deinitialize_p
 * @since_tizen   3.0
 * @description   Test disconnecting iotcon service.
 */
int utc_iotcon_deinitialize_p(void)
{
	int ret;
	char *path;

	if (false == g_feature) {
		ret = iotcon_deinitialize();
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = icutc_get_svr_db_path(&path);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_initialize(path);
	free(path);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_deinitialize();
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	return 0;

}

