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

static component_context_h __component_context;

static bool __check_running(void *data)
{
	bool running = false;

	component_manager_is_running("org.example.service-component", &running);
	if (running) {
		_I("component is running");
		return true;
	}

	return false;
}

void utc_component_manager_terminate_bg_component_p_startup(void)
{
	int ret;

	TCT_UTCCheckInstalledApp(1, "org.example.componentbased");

	ret = common_send_launch_request("org.example.componentbased",
			"org.example.service-component", NULL);
	if (ret < 0) {
		_E("Failed to send launch request");
		return;
	}

	if (!common_wait_until_done(__check_running, NULL)) {
		_W("component is not running");
		return;
	}

	ret = component_manager_get_component_context(
			"org.example.service-component", &__component_context);
	if (ret != COMPONENT_MANAGER_ERROR_NONE)
		_E("Failed to get running component context. error(%d)", ret);
}

void utc_component_manager_terminate_bg_component_p_cleanup(void)
{
	component_context_destroy(__component_context);
}

/**
 * @testcase            utc_component_manager_terminate_bg_component_p
 * @since_tizen         5.5
 * @description         Terminates the background component.
 * @scenario            Calls the component_manager_terminate_bg_component() and checks the return value.
 */
int utc_component_manager_terminate_bg_component_p(void)
{
	int ret;

	ret = component_manager_terminate_bg_component(__component_context);
	if (ret != COMPONENT_MANAGER_ERROR_NONE) {
		_E("Failed to send resume request. error(%d)", ret);
		return ret;
	}

	return 0;
}

/**
 * @testcase            utc_component_manager_terminate_bg_component_n
 * @since_tizen         5.5
 * @description         Terminates the background component.
 * @scenario            Calls the component_manager_terminate_bg_component() with nullptr.
 *                      The return value must be COMPONENT_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_component_manager_terminate_bg_component_n(void)
{
	int ret;

	ret = component_manager_terminate_bg_component(NULL);
	if (ret != COMPONENT_MANAGER_ERROR_INVALID_PARAMETER) {
		_E("The return value(%d) is not invalid parameter", ret);
		return ret;
	}

	return 0;
}
