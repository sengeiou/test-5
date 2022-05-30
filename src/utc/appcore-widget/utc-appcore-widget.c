//
// Copyright (c) 2015 Samsung Electronics Co., Ltd.
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
#include <widget_app.h>
#include <widget_app_efl.h>
#include <Evas.h>
#include <glib.h>
//#include <widget_viewer.h>
#include <widget_viewer_evas.h>
#include <Elementary.h>
#include <system_info.h>

#define FEATURE_SHELL_APPWIDGET "http://tizen.org/feature/shell.appwidget"

static gboolean __widget_app_exit(gpointer user_data)
{
	widget_app_exit();
	return FALSE;
}

/**
 * @function		utc_appcore_widget_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_appcore_widget_startup(void)
{
}

/**
 * @function		utc_appcore_widget_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_appcore_widget_cleanup(void)
{
}

static int widget_obj_create(widget_context_h context, bundle *content, int w,
                             int h, void *user_data)
{
	widget_app_exit();
	return 0;
}

static int widget_obj_destroy(widget_context_h context,
                              widget_app_destroy_type_e reason, bundle *content, void *user_data)
{
	return 0;
}

static int widget_obj_pause(widget_context_h context, void *user_data)
{
	return 0;
}

static int widget_obj_resume(widget_context_h context, void *user_data)
{
	return 0;
}

static int widget_obj_update(widget_context_h context, bundle *content,
                             int force, void *user_data)
{
	return 0;
}

static int widget_obj_resize(widget_context_h context, int w, int h, void *user_data)
{
	return 0;
}

static widget_class_h _app_create(void *user_data)
{
	widget_instance_lifecycle_callback_s ops = {
		.create = widget_obj_create,
		.destroy = widget_obj_destroy,
		.pause = widget_obj_pause,
		.resume = widget_obj_resume,
		.update = widget_obj_update,
		.resize = widget_obj_resize,
	};

	return widget_app_class_create(ops, user_data);
}

static void _app_terminate(void *user_data)
{
}

/**
 * @testcase		utc_appcore_widget_widget_app_main_p
 * @since_tizen		2.3.1
 * @type		Positive
 * @description		Runs the main loop of the application until widget_app_exit() is called.
 * @scenario		Runs the main loop and stops the main loop by calling widget_app_exit().
 */
int utc_appcore_widget_widget_app_main_p(void)
{
	bool feature;
	int ret;
	widget_app_lifecycle_callback_s callback = {0,};
	int argc = 1;
	char *argv[] = {
		"widget_app"
	};

	utc_result = 0;

	callback.create = _app_create;
	callback.terminate = _app_terminate;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_without_exit(ret, SYSTEM_INFO_ERROR_NONE);

	g_timeout_add_seconds(4, __widget_app_exit, NULL);

	if (!feature) {
		ret = widget_app_main(argc, argv, &callback, NULL);
		assert_eq_without_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = widget_app_main(argc, argv, &callback, NULL);

	assert_eq_without_exit(ret, WIDGET_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_appcore_widget_widget_app_main_n1
 * @since_tizen		2.3.1
 * @type		Negative
 * @description		Runs the main loop of the application until widget_app_exit() is called.
 * @scenario		Calls widget_app_main() and then checks the return value.
 */
int utc_appcore_widget_widget_app_main_n1(void)
{
	bool feature;
	int ret;
	char *argv[] = {"test", "argv"};
	widget_app_lifecycle_callback_s ops;
	utc_result = 0;

	ops.create = (widget_app_create_cb)_app_create;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_without_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		ret = widget_app_main(0, argv, &ops, NULL);
		assert_eq_without_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = widget_app_main(0, argv, &ops, NULL);
	assert_eq_without_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_appcore_widget_widget_app_main_n2
 * @since_tizen		2.3.1
 * @type		Negative
 * @description		Runs the main loop of the application until widget_app_exit() is called.
 * @scenario		Calls widget_app_main() and then checks the return value.
 */
int utc_appcore_widget_widget_app_main_n2(void)
{
	bool feature;
	int ret;
	int argc = 2;
	widget_app_lifecycle_callback_s ops;
	utc_result = 0;
	ops.create = (widget_app_create_cb)_app_create;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_without_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		ret = widget_app_main(argc, NULL, &ops, NULL);
		assert_eq_without_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = widget_app_main(argc, NULL, &ops, NULL);
	assert_eq_without_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_appcore_widget_widget_app_main_n3
 * @since_tizen		2.3.1
 * @type		Negative
 * @description		Runs the main loop of the application until widget_app_exit() is called.
 * @scenario		Calls widget_app_main() and then checks the return value.
 */
int utc_appcore_widget_widget_app_main_n3(void)
{
	bool feature;
	int ret;
	int argc = 2;
	char *argv[] = {"test", "argv"};
	widget_app_lifecycle_callback_s ops;
	utc_result = 0;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_without_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		ret = widget_app_main(argc, argv, &ops, NULL);
		assert_eq_without_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = widget_app_main(argc, argv, NULL, NULL);
	assert_eq_without_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);

	ops.create = NULL;
	ret = widget_app_main(argc, argv, &ops, NULL);
	assert_eq_without_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);

	return 0;
}

static void event_callback(void *event, void *data)
{
}

/**
 * @testcase		utc_appcore_widget_widget_app_add_event_handler_p
 * @since_tizen		2.3.1
 * @type		Positive
 * @description		Adds the system event handler.
 * @scenario		Adds the low-memory system event handler and then checks
 *			the return value.
 */
int utc_appcore_widget_widget_app_add_event_handler_p(void)
{
	int ret;
	bool feature;
	app_event_handler_h handler;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_with_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		ret = widget_app_add_event_handler(&handler, APP_EVENT_LOW_MEMORY,
	                                   (app_event_cb)event_callback, NULL);
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
		normal_exit(0);
		return 0;
	}

	ret = widget_app_add_event_handler(&handler, APP_EVENT_LOW_MEMORY,
	                                   (app_event_cb)event_callback, NULL);
	assert_eq_with_exit(ret, WIDGET_ERROR_NONE);

	ret = widget_app_remove_event_handler(handler);
	assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_appcore_widget_widget_app_add_event_handler_n
 * @since_tizen		2.3.1
 * @type		Negative
 * @description		Adds the system event handler.
 * @scenario		Adds the low-memory system event handler and then checks
 *			the return value that is WIDGET_ERROR_INVALID_PARAMETER.
 */
int utc_appcore_widget_widget_app_add_event_handler_n(void)
{
	int ret;
	bool feature;
	app_event_handler_h handler;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_with_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		ret = widget_app_add_event_handler(&handler, APP_EVENT_LOW_MEMORY,
	                                   (app_event_cb)event_callback, NULL);
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
		normal_exit(0);
		return 0;
	}

	ret = widget_app_add_event_handler(NULL, APP_EVENT_LOW_MEMORY,
	                                   (app_event_cb)event_callback, NULL);
	assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);

	ret = widget_app_add_event_handler(&handler, -1, (app_event_cb)event_callback,
	                                   NULL);
	assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);

	ret = widget_app_add_event_handler(&handler, APP_EVENT_LOW_MEMORY, NULL, NULL);
	assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_appcore_widget_widget_app_remove_event_handler_p
 * @since_tizen		2.3.1
 * @type		Positive
 * @description		Removes registered event handler.
 * @scenario		Adds the low-memory system event handler and then
 *			removes the low-memory system event handler.
 */
int utc_appcore_widget_widget_app_remove_event_handler_p(void)
{
	int ret;
	bool feature;
	app_event_handler_h handler;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_with_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		ret = widget_app_add_event_handler(&handler, APP_EVENT_LOW_MEMORY,
	                                   (app_event_cb)event_callback, NULL);
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
		normal_exit(0);
		return 0;
	}

	ret = widget_app_add_event_handler(&handler, APP_EVENT_LOW_MEMORY,
	                                   (app_event_cb)event_callback, NULL);
	assert_eq_with_exit(ret, WIDGET_ERROR_NONE);

	ret = widget_app_remove_event_handler(handler);
	assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_appcore_widget_widget_app_remove_event_handler_n
 * @since_tizen		2.3.1
 * @type		Negative
 * @description		Removes registered event handler.
 * @scenario		Calls the widget_app_remove_event_handler() with the NULL parameter
 *			and then checks the return value.
 */
int utc_appcore_widget_widget_app_remove_event_handler_n(void)
{
	int ret;
	bool feature;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_with_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		ret = widget_app_remove_event_handler(NULL);
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
		normal_exit(0);
		return 0;
	}

	ret = widget_app_remove_event_handler(NULL);
	assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_appcore_widget_widget_app_class_create_p
 * @since_tizen		2.3.1
 * @type		Positive
 * @description		Makes a class for widget instance.
 * @scenario		Calls the widget_app_class_create() and then checks the return value.
 */
int utc_appcore_widget_widget_app_class_create_p(void)
{
	widget_instance_lifecycle_callback_s ops = {
		.create = widget_obj_create,
		.destroy = widget_obj_destroy,
		.pause = widget_obj_pause,
		.resume = widget_obj_resume,
		.update = widget_obj_update,
		.resize = widget_obj_resize,
	};

	widget_class_h  ch;
	int ret;
	bool feature;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_with_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		ch = widget_app_class_create(ops, NULL);
		assert_eq_with_exit(get_last_result(), WIDGET_ERROR_NOT_SUPPORTED);
		normal_exit(0);
		return 0;
	}

	ch = widget_app_class_create(ops, NULL);
	assert_eq_with_exit(get_last_result(), WIDGET_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_appcore_widget_widget_app_class_add_p
 * @since_tizen		3.0
 * @type		Positive
 * @description		Makes multiple classes for widget instance.
 * @scenario		Calls the widget_app_class_add() and then checks the return value.
 */
int utc_appcore_widget_widget_app_class_add_p(void)
{
	widget_instance_lifecycle_callback_s ops = {
		.create = widget_obj_create,
		.destroy = widget_obj_destroy,
		.pause = widget_obj_pause,
		.resume = widget_obj_resume,
		.update = widget_obj_update,
		.resize = widget_obj_resize,
	};

	widget_class_h ch = NULL;
	int ret;
	bool feature;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_with_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		ch = widget_app_class_add(NULL, NULL, ops, NULL);
		assert_eq_with_exit(get_last_result(), WIDGET_ERROR_NOT_SUPPORTED);
		normal_exit(0);
		return 0;
	}

	ch = widget_app_class_add(ch, "test", ops, NULL);

	assert_eq_with_exit(get_last_result(), WIDGET_ERROR_NONE);

	ch = widget_app_class_add(ch, "2@test", ops, NULL);

	assert_eq_with_exit(get_last_result(), WIDGET_ERROR_NONE);

	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_appcore_widget_widget_app_class_add_n
 * @since_tizen		3.0
 * @type		Negative
 * @description		Makes multiple classes for widget instance.
 * @scenario		Calls the widget_app_class_add() and then checks the return value.
 */
int utc_appcore_widget_widget_app_class_add_n(void)
{
	int ret;
	bool feature;
	widget_instance_lifecycle_callback_s ops = {
		.create = widget_obj_create,
		.destroy = widget_obj_destroy,
		.pause = widget_obj_pause,
		.resume = widget_obj_resume,
		.update = widget_obj_update,
		.resize = widget_obj_resize,
	};

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_with_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		widget_app_class_add(NULL, NULL, ops, NULL);
		assert_eq_with_exit(get_last_result(), WIDGET_ERROR_NOT_SUPPORTED);
		normal_exit(0);
		return 0;
	}

	widget_app_class_add(NULL, NULL, ops, NULL);

	assert_eq_with_exit(get_last_result(), WIDGET_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

static widget_class_h _app_create_and_exit(void *user_data)
{
	widget_instance_lifecycle_callback_s ops = {
		.create = widget_obj_create,
		.destroy = widget_obj_destroy,
		.pause = widget_obj_pause,
		.resume = widget_obj_resume,
		.update = widget_obj_update,
		.resize = widget_obj_resize,
	};

	g_idle_add(__widget_app_exit, NULL);
	return widget_app_class_create(ops, user_data);
}

/**
 * @testcase		utc_appcore_widget_widget_app_exit_p
 * @since_tizen		2.3.1
 * @type		Positive
 * @description		Exits the main loop of the application.
 * @scenario		Calls the widget_app_main() and then calls the widget_app_exit().
 */
int utc_appcore_widget_widget_app_exit_p(void)
{
	int ret = WIDGET_ERROR_NONE;
	widget_app_lifecycle_callback_s callback = {0,};
	int argc = 1;
	bool feature;
	char *argv[] = {
		"widget_app"
	};

	utc_result = 0;

	callback.create = _app_create_and_exit;
	callback.terminate = NULL;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_without_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		ret = widget_app_main(argc, argv, &callback, NULL);
		assert_eq_without_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = widget_app_main(argc, argv, &callback, NULL);
	assert_eq_without_exit(ret, WIDGET_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_appcore_widget_widget_app_terminate_context_n
 * @since_tizen		2.3.1
 * @type		Negative
 * @description		Finishes context for the widget instance.
 * @scenario		Calls the widget_app_terminate_context() with the NULL parameter
 *			and then checks the return value.
 */
int utc_appcore_widget_widget_app_terminate_context_n(void)
{
	int ret;
	bool feature;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_with_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		ret = widget_app_terminate_context(NULL);
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
		normal_exit(0);
		return 0;
	}

	ret = widget_app_terminate_context(NULL);

	assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

static bool __foreach_cb(widget_context_h context, void *data)
{
	return true;
}

/**
 * @testcase		utc_appcore_widget_widget_app_foreach_context_p
 * @since_tizen		2.3.1
 * @type		Positive
 * @description		Retrieves all widget contexts in this application.
 * @scenario		Calls the widget_app_foreach_context with the foreach callback
 *			and then checks the return value.
 */
int utc_appcore_widget_widget_app_foreach_context_p(void)
{
	int ret;
	bool feature;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_with_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		ret = widget_app_foreach_context(__foreach_cb, NULL);
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
		normal_exit(0);
		return 0;
	}

	ret = widget_app_foreach_context(__foreach_cb, NULL);

	assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_appcore_widget_widget_app_foreach_context_n
 * @since_tizen		2.3.1
 * @type		Negative
 * @description		Retrieves all widget contexts in this application.
 * @scenario		Calls the widget_app_foreach_context() with the NULL parameter
 *			and then checks the return value.
 */
int utc_appcore_widget_widget_app_foreach_context_n(void)
{
	int ret;
	bool feature;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_with_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		ret = widget_app_foreach_context(NULL, NULL);
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
		normal_exit(0);
		return 0;
	}

	ret = widget_app_foreach_context(NULL, NULL);

	assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_appcore_widget_widget_app_get_id_n
 * @since_tizen		2.3.1
 * @type		Negative
 * @description		Gets a widget instance id.
 * @scenario		Calls the widget_app_get_id() with the NULL parameter
 *			and then checks the return value.
 */
int utc_appcore_widget_widget_app_get_id_n(void)
{
	int ret;
	bool feature;
	const char* id;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_with_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		id = widget_app_get_id(NULL);
		assert_eq_with_exit(get_last_result(), WIDGET_ERROR_NOT_SUPPORTED);
		normal_exit(0);
		return 0;
	}

	id = widget_app_get_id(NULL);

	assert_eq_with_exit(get_last_result(), WIDGET_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_appcore_widget_widget_app_context_set_tag_n
 * @since_tizen		2.3.1
 * @type		Negative
 * @description		Sets a tag in the context.
 * @scenario		Calls the widget_app_context_set_tag() with the NULL parameter
 *			and then checks the return value.
 */
int utc_appcore_widget_widget_app_context_set_tag_n(void)
{
	int ret;
	bool feature;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_with_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		ret = widget_app_context_set_tag(NULL, NULL);
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
		normal_exit(0);
		return 0;
	}

	ret = widget_app_context_set_tag(NULL, NULL);

	assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_appcore_widget_widget_app_context_get_tag_n1
 * @since_tizen		2.3.1
 * @type		Negative
 * @description		Gets the tag in the context.
 * @scenario		Calls the widget_app_context_get_tag() with the NULL parameter
 *			and then checks the return value.
 */
int utc_appcore_widget_widget_app_context_get_tag_n1(void)
{
	void *tag;
	int ret;
	bool feature;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_with_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		ret = widget_app_context_get_tag(NULL, &tag);
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
		normal_exit(0);
		return 0;
	}

	ret = widget_app_context_get_tag(NULL, &tag);

	assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_appcore_widget_widget_app_context_get_tag_n2
 * @since_tizen		2.3.1
 * @type		Negative
 * @description		Gets the tag in the context.
 * @scenario		Calls the widget_app_context_get_tag() with the invalid parameter
 *			and then checks the return value.
 */
int utc_appcore_widget_widget_app_context_get_tag_n2(void)
{
	widget_context_h h;
	char buf[10];
	int ret;
	bool feature;

	h = (widget_context_h) &buf[0];

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_with_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		ret = widget_app_context_get_tag(h, NULL);
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
		normal_exit(0);
		return 0;
	}

	ret = widget_app_context_get_tag(h, NULL);

	assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_appcore_widget_widget_app_context_set_content_info_n
 * @since_tizen		2.3.1
 * @type		Negative
 * @description		Sets the content info to the widget.
 * @scenario		Calls the widget_app_context_set_content_info() with the NULL parameter
 *			and then checks the return value.
 */
int utc_appcore_widget_widget_app_context_set_content_info_n(void)
{
	int ret;
	bool feature;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_with_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		ret = widget_app_context_set_content_info(NULL, NULL);
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
		normal_exit(0);
		return 0;
	}

	ret = widget_app_context_set_content_info(NULL, NULL);
	assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_appcore_widget_widget_app_context_set_title_n
 * @since_tizen		2.3.1
 * @type		Negative
 * @description		Sends the title to the widget.
 * @scenario		Calls the widget_app_context_set_title() with the NULL parameter
 *			and then checks the return value.
 */
int utc_appcore_widget_widget_app_context_set_title_n(void)
{
	int ret;
	bool feature;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_with_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		ret = widget_app_context_set_title(NULL, "test");
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
		normal_exit(0);
		return 0;
	}

	ret = widget_app_context_set_title(NULL, "test");

	assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_appcore_widget_widget_app_get_elm_win_n
 * @since_tizen		2.3.1
 * @type		Negative
 * @description		Gets a evas object for the widget.
 * @scenario		Calls the widget_app_get_elm_win() with the NULL parameter
 *			and then checks the return value.
 */
int utc_appcore_widget_widget_app_get_elm_win_n(void)
{
	Evas_Object *win;
	int ret;
	bool feature;

	ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	assert_eq_with_exit(ret, SYSTEM_INFO_ERROR_NONE);

	if (!feature) {
		ret = widget_app_get_elm_win(NULL, &win);
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
		normal_exit(0);
		return 0;
	}

	ret = widget_app_get_elm_win(NULL, &win);
	assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}
