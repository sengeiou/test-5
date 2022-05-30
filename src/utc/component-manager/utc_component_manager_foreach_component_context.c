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

void utc_component_manager_foreach_component_context_p_startup(void)
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

static bool __component_context_cb(component_context_h context, void *data)
{
	bool *matched = (bool *)data;
	char *component_id;
	int ret;

	ret = component_context_get_component_id(context, &component_id);
	if (ret != COMPONENT_MANAGER_ERROR_NONE) {
		_E("Failed to get component ID. error(%d)", ret);
		return false;
	}

	if (!strcmp(component_id, "org.example.frame-component")) {
		_I("Matched");
		*matched = true;
		free(component_id);
		return false;
	}

	free(component_id);

	return true;
}

/**
 * @testcase            utc_component_manager_foreach_component_context_p
 * @since_tizen         5.5
 * @description         Retrieves all component contexts of running components.
 * @scenario            Calls the component_manager_foreach_component_context() and checks the return value.
 *                      The matched is "true" if the component(org.example.frame-component) is running,
 *                      otherwise "false" if not running.
 *                      The matched must be "true" in this testcase.
 */
int utc_component_manager_foreach_component_context_p(void)
{
	bool matched = false;
	int ret;

	ret = component_manager_foreach_component_context(
			__component_context_cb, (void *)&matched);
	if (ret != COMPONENT_MANAGER_ERROR_NONE) {
		_E("Failed to retrieve running component contexts. error(%d)",
				ret);
		return ret;
	}

	if (!matched) {
		_E("`org.example.frame-component` is not running");
		return -1;
	}

	return 0;
}

/**
 * @testcase            utc_component_manager_foreach_component_context_n
 * @since_tizen         5.5
 * @description         Retrieves all component contexts of running components.
 * @scenario            Calls the component_manager_foreach_component_context() with nullptrs.
 *                      The return value must be COMPONENT_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_component_manager_foreach_component_context_n(void)
{
	int ret;

	ret = component_manager_foreach_component_context(NULL, NULL);
	if (ret != COMPONENT_MANAGER_ERROR_INVALID_PARAMETER) {
		_E("The return value(%d) is not invalid parameter", ret);
		return ret;
	}

	return 0;
}
