//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <component_based_app.h>
#include <component_common.h>
#include <component_manager.h>
#include <app_control.h>

#include "assert.h"
#include "assert_common.h"


static const char *g_app_id = "org.example.componentbased";
static const char *g_service_comp_id = "service_comp_test";
static const char *g_extra_key = "component_utc_func";

static int __app_control_send(const char *app_id, const char *component_id,
				const char *extra_data)
{
	app_control_h handle = NULL;
	app_control_h reply;
	app_control_result_e result = APP_CONTROL_RESULT_FAILED;
	int ret;

	ret = app_control_create(&handle);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create app control");
		return -1;
	}

	ret = app_control_set_app_id(handle, app_id);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set application ID");
		goto end;
	}

	if (component_id) {
		ret = app_control_set_component_id(handle, component_id);
		if (ret != APP_CONTROL_ERROR_NONE) {
			dlog_print(DLOG_ERROR, LOG_TAG,
					"Failed to set component ID");
			goto end;
		}
	}

	ret = app_control_add_extra_data(handle, g_extra_key, extra_data);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to add extra data");
		goto end;
	}

	ret = app_control_send_launch_request_sync(handle,
			&reply, &result);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to send launch request sync");
	}

end:
	if (handle)
		app_control_destroy(handle);

	return result;
}

/**
 * @testcase		utc_component_get_id_p
 * @since_tizen		5.5
 * @description		Get component id.
 */
int utc_component_get_id_p(void)
{
	int ret;

	ret =  __app_control_send(g_app_id, g_service_comp_id,
			"utc_component_get_id");
	assert_eq_with_exit(ret, APP_CONTROL_RESULT_SUCCEEDED);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_component_get_id_n
 * @since_tizen		5.5
 * @description		Get component id with invalid parameter.
 */
int utc_component_get_id_n(void)
{
	int ret;
	char *id;

	ret =  component_get_id(NULL, &id);
	assert_eq_with_exit(ret, COMPONENT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_component_get_instance_id_p
 * @since_tizen		5.5
 * @description		Get component instance id.
 */
int utc_component_get_instance_id_p(void)
{
	int ret;

	ret =  __app_control_send(g_app_id, g_service_comp_id,
			"utc_component_get_instance_id");
	assert_eq_with_exit(ret, APP_CONTROL_RESULT_SUCCEEDED);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_component_get_instance_id_n
 * @since_tizen		5.5
 * @description		Get component instance id with invalid parameter.
 */
int utc_component_get_instance_id_n(void)
{
	int ret;
	char *id;

	ret =  component_get_instance_id(NULL, &id);
	assert_eq_with_exit(ret, COMPONENT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_component_register_action_p
 * @since_tizen		5.5
 * @description		Register appcontrol action.
 */
int utc_component_register_action_p(void)
{
	int ret;

	ret =  __app_control_send(g_app_id, g_service_comp_id,
			"utc_component_register_action");
	assert_eq_with_exit(ret, APP_CONTROL_RESULT_SUCCEEDED);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_component_register_action_n
 * @since_tizen		5.5
 * @description		Register appcontrol action with invalid parameter.
 */
int utc_component_register_action_n(void)
{
	int ret;
	const char *action = "action";

	ret =  component_register_action(NULL, action);
	assert_eq_with_exit(ret, COMPONENT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_component_deregister_action_p
 * @since_tizen		5.5
 * @description		Deregister appcontrol action.
 */
int utc_component_deregister_action_p(void)
{
	int ret;

	ret =  __app_control_send(g_app_id, g_service_comp_id,
			"utc_component_deregister_action");
	assert_eq_with_exit(ret, APP_CONTROL_RESULT_SUCCEEDED);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_component_deregister_action_n
 * @since_tizen		5.5
 * @description		Deregister appcontrol action with invalid parameter.
 */
int utc_component_deregister_action_n(void)
{
	int ret;
	const char *action = "action";

	ret =  component_deregister_action(NULL, action);
	assert_eq_with_exit(ret, COMPONENT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_component_send_launch_request_sync_p
 * @since_tizen		5.5
 * @description		Sends the launch request synchronously.
 */
int utc_component_send_launch_request_sync_p(void)
{
	int ret;

	ret =  __app_control_send(g_app_id, g_service_comp_id,
			"utc_component_launch_sync");
	assert_eq_with_exit(ret, APP_CONTROL_RESULT_SUCCEEDED);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_component_send_launch_request_sync_n
 * @since_tizen		5.5
 * @description		Sends the launch request synchronously with invalid parameter.
 */
int utc_component_send_launch_request_sync_n(void)
{
	int ret;

	ret = component_send_launch_request_sync(NULL, NULL, NULL, NULL);
	assert_eq_with_exit(ret, COMPONENT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_component_send_launch_request_async_p
 * @since_tizen		5.5
 * @description		Sends the launch request asynchronously.
 */
int utc_component_send_launch_request_async_p(void)
{
	int ret;

	ret =  __app_control_send(g_app_id, g_service_comp_id,
			"utc_component_launch_async");
	assert_eq_with_exit(ret, APP_CONTROL_RESULT_SUCCEEDED);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_component_send_launch_request_async_n
 * @since_tizen		5.5
 * @description		Sends the launch request asynchronously with invalid parameter.
 */
int utc_component_send_launch_request_async_n(void)
{
	int ret;

	ret =  component_send_launch_request_async(NULL, NULL, NULL, NULL, NULL);
	assert_eq_with_exit(ret, COMPONENT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_component_finish_p
 * @since_tizen		5.5
 * @description		Finishes the component instance.
 */
int utc_component_finish_p(void)
{
	int ret;

	ret =  __app_control_send(g_app_id, g_service_comp_id,
			"utc_component_finish");
	assert_eq_with_exit(ret, APP_CONTROL_RESULT_SUCCEEDED);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_component_finish_n
 * @since_tizen		5.5
 * @description		Finishes the component instance with invalid parameter.
 */
int utc_component_finish_n(void)
{
	int ret;

	ret =  component_finish(NULL);
	assert_eq_with_exit(ret, COMPONENT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}
