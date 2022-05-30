/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
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

#include <app_control.h>
#include <component_manager.h>

#include "assert.h"
#include "tct_app_common.h"
#include "log_private.h"
#include "utc_common.h"

static bool __check_running(void *data)
{
	bool running = false;

	component_manager_is_running("org.example.frame-component", &running);
	if (running) {
		_I("component is running");
		return true;
	}

	return false;
}

void utc_component_manager_is_running_p_startup(void)
{
	int ret;

	TCT_UTCCheckInstalledApp(1, "org.example.componentbased");

	ret = common_send_launch_request("org.example.componentbased",
			"org.example.frame-component", NULL);
	if (ret < 0) {
		_E("Failed to send launch request");
		return;
	}

	common_wait_until_done(__check_running, NULL);
}

/**
 * @testcase            utc_component_manager_is_running_p
 * @since_tizen         5.5
 * @description         Checks whether the component is running or not.
 * @scenario            Calls the component_manager_is_running() and checks the return value.
 *                      The running should be "true".
 */
int utc_component_manager_is_running_p(void)
{
	bool running;
	int ret;

	ret = component_manager_is_running("org.example.frame-component",
			&running);
	if (ret != COMPONENT_MANAGER_ERROR_NONE) {
		_E("Failed to check running state. error(%d)", ret);
		return ret;
	}

	if (!running) {
		_E("`org.example.frame-component` is not running");
		return -1;
	}

	return 0;
}

/**
 * @testcase            utc_component_manager_is_running_n
 * @since_tizen         5.5
 * @description         checks whether the component is running or not.
 * @scenario            calls the component_manager_is_running() with nullptr.
 *                      The return value must be COMPONENT_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_component_manager_is_running_n(void)
{
	int ret;

	ret = component_manager_is_running(NULL, NULL);
	if (ret != COMPONENT_MANAGER_ERROR_INVALID_PARAMETER) {
		_E("The return value(%d) is not invalid parameter", ret);
		return ret;
	}

	return 0;
}
