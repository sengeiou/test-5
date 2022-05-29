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

	component_manager_is_running("org.example.frame-component", &running);
	if (running) {
		_I("component is running");
		return true;
	}

	return false;
}

void utc_component_context_get_component_state_p_startup(void)
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

	ret = component_manager_get_component_context(
			"org.example.frame-component", &__component_context);
	if (ret != COMPONENT_MANAGER_ERROR_NONE)
		_E("Failed to create component context. error(%d)", ret);
}

void utc_component_context_get_component_state_p_cleanup(void)
{
	component_context_destroy(__component_context);
}

/**
 * @testcase            utc_component_context_get_component_state_p
 * @since_tizen         5.5
 * @description         Gets the state of the component.
 * @scenario            Calls the component_context_get_component_state() and checks the return value.
 *                      The state must not be "COMPONENT_STATE_SERVICE".
 */
int utc_component_context_get_component_state_p(void)
{
	component_state_e state;
	int ret;

	ret = component_context_get_component_state(__component_context,
			&state);
	if (ret != COMPONENT_MANAGER_ERROR_NONE) {
		_E("Failed to get component state. error(%d)", ret);
		return ret;
	}

	if (state == COMPONENT_STATE_INITIALIZED) {
		_E("state(%d) should not be `COMPONENT_STATE_INITIALIZED`",
				state);
		return -1;
	}

	return 0;
}

/**
 * @testcase            utc_component_context_get_component_state_n
 * @since_tizen         5.5
 * @description         Gets the state of the component.
 * @scenario            Calls the component_context_get_component_state() with nullptrs.
 *                      The return value must be COMPONENT_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_component_context_get_component_state_n(void)
{
	int ret;

	ret = component_context_get_component_state(NULL, NULL);
	if (ret != COMPONENT_MANAGER_ERROR_INVALID_PARAMETER) {
		_E("The return value(%d) is not invalid parameter", ret);
		return ret;
	}

	return 0;
}
