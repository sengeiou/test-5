//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
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
#include "assert.h"
#include "assert_common.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <service_app.h>
#include <glib.h>

static int main_loop_flag = 0;

static gboolean service_app_exit_cb(gpointer user_data)
{
	service_app_exit();

	return FALSE;
}

static bool _service_app_create(void *user_data)
{
	main_loop_flag = 1;

	g_idle_add(service_app_exit_cb, NULL);

	return true;
}

static void _service_app_terminate(void *user_data)
{
	main_loop_flag = 0;
}

/**
 * @testcase		utc_appcore_agent_service_app_main_p1
 * @since_tizen		2.3
 * @description		Run service application with a argument.
 */
int utc_appcore_agent_service_app_main_p1(void)
{
	int ret;
	service_app_lifecycle_callback_s ops = {0};

	main_loop_flag = 0;
	ops.create = _service_app_create;

	ret = service_app_main(g_argc, g_argv, &ops, NULL);

	assert_eq_without_exit(ret, APP_ERROR_NONE);
	assert_eq_without_exit(main_loop_flag, 1);

	utc_result = 0;

	return 0;
}

static bool _app_create_cb(void *user_data)
{
	return false;
}

static void _app_terminate_cb(void *user_data)
{
}

/**
 * @testcase		utc_appcore_agent_service_app_main_p2
 * @since_tizen		2.3
 * @description		Run service application with arguments.
 */
int utc_appcore_agent_service_app_main_p2(void)
{
	int ret;
	service_app_lifecycle_callback_s ops = {0};

	ops.create = _app_create_cb;
	ops.terminate = _app_terminate_cb;

	ret = service_app_main(g_argc, g_argv, &ops, NULL);
	assert_eq_without_exit(ret, APP_ERROR_NONE);

	utc_result = 0;

	return 0;
}

/**
 * @testcase		utc_appcore_agent_service_app_main_n1
 * @since_tizen		2.3
 * @description		Run service application with invalid parameter(argc 0)
 */
int utc_appcore_agent_service_app_main_n1(void)
{
	int ret;
	service_app_lifecycle_callback_s ops = {0};

	ops.create = (service_app_create_cb)_service_app_create;

	ret = service_app_main(0, g_argv, &ops, NULL);
	assert_eq_without_exit(ret, APP_ERROR_INVALID_PARAMETER);

	utc_result = 0;

	return 0;
}

/**
 * @testcase		utc_appcore_agent_service_app_main_n2
 * @since_tizen		2.3
 * @description		Run service application with invalid parameter(argv NULL)
 */
int utc_appcore_agent_service_app_main_n2(void)
{
	int ret;
	service_app_lifecycle_callback_s ops = {0};

	ops.create = (service_app_create_cb)_service_app_create;

	ret = service_app_main(g_argc, NULL, &ops, NULL);
	assert_eq_without_exit(ret, APP_ERROR_INVALID_PARAMETER);

	utc_result = 0;

	return 0;
}


/**
 * @testcase		utc_appcore_agent_service_app_main_n3
 * @since_tizen		2.3
 * @description		Run service application with invalid parameter(service_app_lifecycle_callback_s NULL)
 */
int utc_appcore_agent_service_app_main_n3(void)
{
	int ret;
	service_app_lifecycle_callback_s ops = {0};

	ret = service_app_main(g_argc, g_argv, NULL, NULL);
	assert_eq_without_exit(ret, APP_ERROR_INVALID_PARAMETER);

	ops.create = NULL;
	ret = service_app_main(g_argc, g_argv, &ops, NULL);
	assert_eq_without_exit(ret, APP_ERROR_INVALID_PARAMETER);

	utc_result = 0;

	return 0;
}

/**
 * @testcase		utc_appcore_agent_service_app_exit_p
 * @since_tizen		2.3
 * @description		Exit service application
 */
int utc_appcore_agent_service_app_exit_p(void)
{
	int ret;
	service_app_lifecycle_callback_s ops = {0};

	main_loop_flag = 1;
	ops.create = _service_app_create;
	ops.terminate = _service_app_terminate;

	ret = service_app_main(g_argc, g_argv, &ops, NULL);
	assert_eq_without_exit(ret, APP_ERROR_NONE);
	assert_eq_without_exit(main_loop_flag, 0);

	utc_result = 0;

	return 0;
}

static void event_callback(void *event, void *data)
{
}

/**
 * @testcase		utc_appcore_agent_service_app_add_event_handler_p1
 * @since_tizen		2.3
 * @description		Add a system event handler.
 */
int utc_appcore_agent_service_app_add_event_handler_p1(void)
{
	int ret;
	app_event_handler_h handler;

	ret = service_app_add_event_handler(&handler, APP_EVENT_LOW_MEMORY, (app_event_cb)event_callback, NULL);
	assert_eq_with_exit(ret, APP_ERROR_NONE);

	ret = service_app_remove_event_handler(handler);
	assert_eq_with_exit(ret, APP_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_appcore_agent_service_app_add_event_handler_p2
 * @since_tizen		2.3
 * @description		Add system event handlers.
 */
int utc_appcore_agent_service_app_add_event_handler_p2(void)
{
	int ret;
	app_event_handler_h handler;

	ret = service_app_add_event_handler(&handler, APP_EVENT_LOW_BATTERY, (app_event_cb)event_callback, NULL);
	assert_eq_with_exit(ret, APP_ERROR_NONE);

	ret = service_app_add_event_handler(&handler, APP_EVENT_LANGUAGE_CHANGED, (app_event_cb)event_callback, NULL);
	assert_eq_with_exit(ret, APP_ERROR_NONE);

	ret = service_app_add_event_handler(&handler, APP_EVENT_REGION_FORMAT_CHANGED, (app_event_cb)event_callback, NULL);
	assert_eq_with_exit(ret, APP_ERROR_NONE);

	ret = service_app_remove_event_handler(handler);
	assert_eq_with_exit(ret, APP_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_appcore_agent_service_app_add_event_handler_n
 * @since_tizen		2.3
 * @description		Add system event handlers with invalid parameter.
 */
int utc_appcore_agent_service_app_add_event_handler_n(void)
{
	int ret;
	app_event_handler_h handler;

	ret = service_app_add_event_handler(NULL, APP_EVENT_LOW_MEMORY, (app_event_cb)event_callback, NULL);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);

	ret = service_app_add_event_handler(&handler, -1, (app_event_cb)event_callback, NULL);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);

	ret = service_app_add_event_handler(&handler, APP_EVENT_LOW_MEMORY, NULL, NULL);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_appcore_agent_service_app_remove_event_handler_p
 * @since_tizen		2.3
 * @description		Remove system event handler.
 */
int utc_appcore_agent_service_app_remove_event_handler_p(void)
{
	int ret;
	app_event_handler_h handler;

	ret = service_app_add_event_handler(&handler, APP_EVENT_LOW_MEMORY, (app_event_cb)event_callback, NULL);
	assert_eq_with_exit(ret, APP_ERROR_NONE);

	ret = service_app_remove_event_handler(handler);
	assert_eq_with_exit(ret, APP_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_appcore_agent_service_app_remove_event_handler_n
 * @since_tizen		2.3
 * @description		Remove system event handler with invalid parameter.
 */
int utc_appcore_agent_service_app_remove_event_handler_n(void)
{
	int ret;

	ret = service_app_remove_event_handler(NULL);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}
