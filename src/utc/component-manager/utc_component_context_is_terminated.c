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
#include <bundle.h>
#include <component_manager.h>
#include <message_port.h>

#include "assert.h"
#include "tct_app_common.h"
#include "log_private.h"
#include "utc_common.h"

static component_context_h __component_context;
static int __local_port_id;

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

static bool __check_not_running(void *data)
{
	bool running = false;

	component_manager_is_running("org.example.frame-component", &running);
	if (!running) {
		_I("component is not running");
		return true;
	}

	return false;
}

static int __send_terminate_message(void)
{
	bundle *message;
	int ret;

	message = bundle_create();
	if (!message) {
		_E("bundle_create() is failed");
		return -1;
	}

	bundle_add_str(message, "extra", "terminate");
	ret = message_port_send_message("org.example.componentbased",
			"frame-component", message);
	if (ret < 0)
		_E("message_port_send_message() is failed. error(%d)", ret);

	bundle_free(message);

	return ret;
}

static void __message_cb(int local_port_id, const char *remote_app_id,
		const char *remote_port, bool trusted_remote_port,
		bundle *message, void *user_data)
{
}

void utc_component_context_is_terminated_p_startup(void)
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

	if (__local_port_id == 0) {
		__local_port_id = message_port_register_local_port("NativeTCT",
				__message_cb, NULL);
	}

	ret = __send_terminate_message();
	if (ret < 0) {
		_E("Failed to send terminate message");
		return;
	}

	common_wait_until_done(__check_not_running, NULL);
}

void utc_component_context_is_terminated_p_cleanup(void)
{
	if (__local_port_id != 0) {
		message_port_unregister_local_port(__local_port_id);
		__local_port_id = 0;
	}

	component_context_destroy(__component_context);
}

/**
 * @testcase            utc_component_context_is_terminated_p
 * @since_tizen         5.5
 * @description         Checks whether the component is terminated or not.
 * @scenario            Calls the component_context_is_terminated() and checks the return value.
 *                      The terminated must not be "true".
 */
int utc_component_context_is_terminated_p(void)
{
	bool terminated;
	int ret;

	ret = component_context_is_terminated(__component_context, &terminated);
	if (ret != COMPONENT_MANAGER_ERROR_NONE) {
		_E("Failed to get component running state. error(%d)", ret);
		return ret;
	}

	if (!terminated) {
		_E("terminated(%d) should be `true`", terminated);
		return -1;
	}

	return 0;
}

/**
 * @testcase            utc_component_context_is_terminated_n
 * @since_tizen         5.5
 * @description         Checks whether the component is terminated or not.
 * @scenario            Calls the component_context_is_terminated() with nullptrs.
 *                      The return value must be COMPONENT_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_component_context_is_terminated_n(void)
{
	int ret;

	ret = component_context_is_terminated(NULL, NULL);
	if (ret != COMPONENT_MANAGER_ERROR_INVALID_PARAMETER) {
		_E("The return value(%d) is not invalid parameter", ret);
		return ret;
	}

	return 0;
}
