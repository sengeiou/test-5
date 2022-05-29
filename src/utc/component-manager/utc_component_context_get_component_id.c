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

void utc_component_context_get_component_id_p_startup(void)
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

void utc_component_context_get_component_id_p_cleanup(void)
{
	component_context_destroy(__component_context);
}

/**
 * @testcase            utc_component_context_get_component_id_p
 * @since_tizen         5.5
 * @description         Gets the ID of the component.
 * @scenario            Calls the component_context_get_component_id() and checks the return value.
 *                      The component_id must be "org.example.frame-component".
 */
int utc_component_context_get_component_id_p(void)
{
	char *component_id;
	int ret;

	ret = component_context_get_component_id(__component_context,
			&component_id);
	if (ret != COMPONENT_MANAGER_ERROR_NONE) {
		_E("Failed to get component ID. error(%d)", ret);
		return ret;
	}

	if (strcmp(component_id, "org.example.frame-component") != 0) {
		_E("component_id(%s) should be `org.example.frame-component`",
				component_id);
		free(component_id);
		return -1;
	}

	free(component_id);

	return 0;
}

/**
 * @testcase            utc_component_context_get_component_id_n
 * @since_tizen         5.5
 * @description         Gets the ID of the component.
 * @scenario            Calls the component_context_get_component_id() with nullptrs.
 *                      The return value must be COMPONENT_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_component_context_get_component_id_n(void)
{
	int ret;

	ret = component_context_get_component_id(NULL, NULL);
	if (ret != COMPONENT_MANAGER_ERROR_INVALID_PARAMETER) {
		_E("The return value(%d) is not invalid parameter", ret);
		return ret;
	}

	return 0;
}
