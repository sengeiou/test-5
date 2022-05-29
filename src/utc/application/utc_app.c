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

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <dlog.h>
#include <app.h>
#include <app_manager.h>
#include <system_info.h>

#include "assert.h"
#include "assert_common.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "NativeTCT"

typedef struct app_context_s {
	char *id;
	app_info_app_component_type_e comp_type;
} app_context;

static app_context __context;

//& set: ApplicationMain

/**
 * @testcase		utc_application_app_get_name_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the localized name of the application.
 * @scenario		Gets the localized name.
 *			Calls the app_get_name() and then checks the return value.
 */
int utc_application_app_get_name_p(void)
{
	int ret = APP_ERROR_NONE;
	char *name = NULL;

	ret = app_get_name(&name);
	assert_neq_with_exit(name, NULL);
	free(name);

	assert_eq_with_exit(ret, APP_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_get_name_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the localized name of the application.
 * @scenario		Calls the app_get_name() with the invalid parameter
 *			that name is NULL, and then checks the return value.
 */
int utc_application_app_get_name_n(void)
{
	int ret = APP_ERROR_NONE;

	ret = app_get_name(NULL);

	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_get_version_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the version of the application package.
 * @scenario		Gets the version.
 *			Calls the app_get_version() and then checks the return value.
 */
int utc_application_app_get_version_p(void)
{
	int ret = APP_ERROR_NONE;
	char *version = NULL;

	ret = app_get_version(&version);
	assert_neq_with_exit(version, NULL);
	free(version);

	assert_eq_with_exit(ret, APP_ERROR_NONE);
	normal_exit(0);

	return 0;
}


/**
 * @testcase		utc_application_app_get_version_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the version of the application package.
 * @scenario		Calls the app_get_version() with the invalid paramerter
 *			that version is NULL, and then checks the return value.
 */
int utc_application_app_get_version_n(void)
{
	int ret = APP_ERROR_NONE;

	ret = app_get_version(NULL);

	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_get_device_orientation_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the current device orientation.
 * @scenario		Calls the app_get_device_orientation() and then checks the return value.
 */
int utc_application_app_get_device_orientation_p(void)
{
	app_device_orientation_e orientation = APP_DEVICE_ORIENTATION_0 - 1;

	orientation = app_get_device_orientation();

	assert_with_exit(orientation == APP_DEVICE_ORIENTATION_0 ||
			orientation == APP_DEVICE_ORIENTATION_90 ||
			orientation == APP_DEVICE_ORIENTATION_180 ||
			orientation == APP_DEVICE_ORIENTATION_270);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_get_id_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the ID of the application.
 * @scenario		Gets the ID.
 *			Calls the app_get_id() and then checks the return value.
 */
int utc_application_app_get_id_p(void)
{
	int ret = APP_ERROR_NONE;
	char *id = NULL;

	ret = app_get_id(&id);
	assert_neq_with_exit(id, NULL);
	free(id);

	assert_eq_with_exit(ret, APP_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_get_id_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the ID of the application.
 * @scenario		Calls the app_get_id() with the invalid parameter
 *			that id is NULL, and then checks the return value.
 */
int utc_application_app_get_id_n(void)
{
	int ret = APP_ERROR_NONE;

	ret = app_get_id(NULL);

	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_get_cache_path_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the absolute path to the cache directory of the application
 *			which is used to store temporary data of the application.
 * @scenario		Calls the app_get_cache_path() and then checks the return value.
 */
int utc_application_app_get_cache_path_p(void)
{
	char *path;

	path = app_get_cache_path();
	assert_neq_with_exit(path, NULL);
	assert_with_exit(strstr(path, "cache/"));
	free(path);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_get_data_path_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the absolute path to the data directory of the application
 *			which is used to store private data of the application.
 * @scenario		Calls the app_get_data_path() and then checks the return value.
 */
int utc_application_app_get_data_path_p(void)
{
	char *path;

	path = app_get_data_path();
	assert_neq_with_exit(path, NULL);
	assert_with_exit(strstr(path, "data/"));
	free(path);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_get_resource_path_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the absolute path to the application resource directory.
 *			The resource files are delivered with the application package.
 * @scenario		Calls the app_get_resource_path() and then checks the return value.
 */
int utc_application_app_get_resource_path_p(void)
{
	char *path;

	path = app_get_resource_path();
	assert_neq_with_exit(path, NULL);
	assert_with_exit(strstr(path, "res/"));
	free(path);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_get_external_cache_path_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the absolute path to external cache directory of the application
 *			which is used to  store temporary data of the application.
 * @scenario		Calls the app_get_external_cache_path() and then checks the return value.
 */
int utc_application_app_get_external_cache_path_p(void)
{
	char *path;

	path = app_get_external_cache_path();
	assert_neq_with_exit(path, NULL);
	assert_with_exit(strstr(path, "cache/"));
	free(path);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_get_external_data_path_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the absolute path to external data directory of the application
 *			which is used to store data of the application.
 * @scenario		Calls the app_get_external_data_path() and then checks the return value.
 */
int utc_application_app_get_external_data_path_p(void)
{
	char *path;

	path = app_get_external_data_path();
	assert_neq_with_exit(path, NULL);
	assert_with_exit(strstr(path, "data/"));
	free(path);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_get_external_shared_data_path_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the absolute path to external shared data directory of the application
 *			which is used to share data with other applications.
 * @scenario		Calls the app_get_external_shared_data_path() and then checks the return value.
 */
int utc_application_app_get_external_shared_data_path_p(void)
{
	char *path;

	path = app_get_external_shared_data_path();
	assert_neq_with_exit(path, NULL);
	assert_with_exit(strstr(path, "shared/data/"));
	free(path);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_get_shared_data_path_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the absolute path to the shated data directory of the application
 *			which is used to share data with other applications.
 * @scenario		Calls the app_get_shared_data_path() and then checks the return value.
 */
int utc_application_app_get_shared_data_path_p(void)
{
	char *path;

	path = app_get_shared_data_path();
	assert_with_exit(path != NULL);
	assert_with_exit(get_last_result() == APP_ERROR_NONE);
	free(path);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_get_shared_resource_path_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the absolute path to shared resource directory of the application
 *			which is used to share resources with other applications.
 * @scenario		Calls the app_get_shared_resource_path() and then checks the return value.
 */
int utc_application_app_get_shared_resource_path_p(void)
{
	char *path;

	path = app_get_shared_resource_path();
	assert_neq_with_exit(path, NULL);
	assert_with_exit(strstr(path, "shared/res/"));
	free(path);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_get_shared_trusted_path_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the absolute path to the shared trusted directory of the application
 *			which is used to share data with a family of trusted applications
 * @scenario		Calls the app_get_shared_trusted_path() and then checks the return value.
 */
int utc_application_app_get_shared_trusted_path_p(void)
{
	char *path;

	path = app_get_shared_trusted_path();
	assert_neq_with_exit(path, NULL);
	assert_with_exit(strstr(path, "shared/trusted/"));
	free(path);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_get_tep_resource_path_p
 * @since_tizen		2.4
 * @type		Positive
 * @description		Gets the absolute path to the TEP(Tizen Expansion Package) directory of the application.
 *			The resource files are delivered with the expansion package.
 * @scenario		Calls the app_get_tep_resource_path() and then checks return value.
 */
int utc_application_app_get_tep_resource_path_p(void)
{
	char *path;

	path = app_get_tep_resource_path();
	assert_neq_with_exit(path, NULL);
	assert_with_exit(strstr(path, "tep/mount/"));
	free(path);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_get_low_memory_status_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the low memory status from given event info.
 * @scenario		Calls the app_event_get_low_memory_status() with the invalid paramter
 *			that the event_info is NULL or the status is NULL,
 *			and then checks the return value.
 */
int utc_application_app_event_get_low_memory_status_n(void)
{
	int ret;
	app_event_low_memory_status_e status;
	app_event_info_h info = NULL;

	ret = app_event_get_low_memory_status(NULL, &status);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);

	ret = app_event_get_low_memory_status(info, NULL);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_get_low_battery_status_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the low battery status from given event info.
 * @scenario		Calls the app_event_get_low_battery_status() with the invalid paramter
 *			that the event_info is NULL or the status is NULL,
 *			and then checks the return value.
 */
int utc_application_app_event_get_low_battery_status_n(void)
{
	int ret;
	app_event_low_battery_status_e status;
	app_event_info_h info = NULL;

	ret = app_event_get_low_battery_status(NULL, &status);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);

	ret = app_event_get_low_battery_status(info, NULL);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_get_language_n
 * @since_tizen		2.3
 * @type		Nagative
 * @description		Gets the language from given event info.
 * @scenario		Calls the app_event_get_language() with the invalid paramter
 *			that the event_info is NULL or the statue is NULL,
 *			and then checks the return value.
 */
int utc_application_app_event_get_language_n(void)
{
	int ret;
	char *lang;
	app_event_info_h info = NULL;

	ret = app_event_get_language(NULL, &lang);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);

	ret = app_event_get_language(info, NULL);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_get_device_orientation_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the device orientation from given event info.
 * @scenario		Calls the app_get_device_orientation() with the invalid paramter
 *			that the event_info is NULL or the status is NULL,
 *			and then checks the return value.
 */
int utc_application_app_event_get_device_orientation_n(void)
{
	int ret;
	app_device_orientation_e orient;
	app_event_info_h info = NULL;

	ret = app_event_get_device_orientation(NULL, &orient);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);

	ret = app_event_get_device_orientation(info, NULL);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_get_region_format_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the region format from given event info.
 * @scenario		Calls the app_event_get_region_format() with the invalid parameter
 *			that the event_info is NULL or the status is NULL,
 *			and then checks the return value.
 */
int utc_application_app_event_get_region_format_n(void)
{
	int ret;
	char *region;
	app_event_info_h info = NULL;

	ret = app_event_get_region_format(NULL, &region);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);

	ret = app_event_get_region_format(info, NULL);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_get_suspended_state_n
 * @since_tizen		2.4
 * @type		Negative
 * @description		Gets the suspended state of the application from given event info.
 * @scenario		Calls the app_event_get_suspend_state() with the invalid parameter
 *			that the event_info is NULL or the status is NULL,
 *			and then checks the return value.
 */
int utc_application_app_event_get_suspended_state_n(void)
{
	int ret;
	app_suspended_state_e state;
	app_event_info_h info = NULL;

	ret = app_event_get_suspended_state(NULL, &state);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);

	ret = app_event_get_suspended_state(info, NULL);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_ui_app_main_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Runs the application's main loop until ui_app_exit() is called.
 * @scenario		Calls the ui_app_main() with the invalid parameters
 *			and then checks the return value.
 */
int utc_application_ui_app_main_n(void)
{
	int ret;

	ret = ui_app_main(0, NULL, NULL, NULL);
	assert_eq_without_exit(ret, APP_ERROR_INVALID_PARAMETER);

	normal_exit(0);

	return 0;
}

static void event_callback(void *event, void *data)
{
}

/**
 * @testcase		utc_application_ui_app_add_event_handler_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Adds the system event handler
 * @scenario		Adds the low-memory system event handler
 *			Calls the ui_app_add_event_handler() with APP_EVENT_LOW_MEMORY event type.
 */
int utc_application_ui_app_add_event_handler_p(void)
{
	int ret;
	app_event_handler_h handler;

	ret = ui_app_add_event_handler(&handler, APP_EVENT_LOW_MEMORY, (app_event_cb)event_callback, NULL);
	assert_eq_with_exit(ret, APP_ERROR_NONE);

	ret = ui_app_remove_event_handler(handler);
	assert_eq_with_exit(ret, APP_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_ui_app_add_event_handler_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Adds the system event handler
 * @scenario		Calls the ui_app_add_event_handler() with the invalid parameter
 *			that the event_handler is NULL or the event type is -1,
 *			and then checks the return value.
 */
int utc_application_ui_app_add_event_handler_n(void)
{
	int ret;
	app_event_handler_h handler;

	ret = ui_app_add_event_handler(NULL, APP_EVENT_LOW_MEMORY, (app_event_cb)event_callback, NULL);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);

	ret = ui_app_add_event_handler(&handler, -1, (app_event_cb)event_callback, NULL);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);

	ret = ui_app_add_event_handler(&handler, APP_EVENT_LOW_MEMORY, NULL, NULL);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_ui_app_remove_event_handler_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Removes registered event handler.
 * @scenario		Adds the low-memory system event handler and removes the event handler.
 *			Calls the ui_app_add_event_handler() and calls the
 *			ui_app_remove_event_handler(), and then checks the return value.
 */
int utc_application_ui_app_remove_event_handler_p(void)
{
	int ret;
	app_event_handler_h handler;

	ret = ui_app_add_event_handler(&handler, APP_EVENT_LOW_MEMORY, (app_event_cb)event_callback, NULL);
	assert_eq_with_exit(ret, APP_ERROR_NONE);

	ret = ui_app_remove_event_handler(handler);
	assert_eq_with_exit(ret, APP_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_ui_app_remove_event_handler_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Removes registered event handler/
 * @scenario		Calls the ui_app_remove_event_handler() with the invalid parameter
 *			that the event_handler is NULL, and then checks the return value.
 */
int utc_application_ui_app_remove_event_handler_n(void)
{
	int ret;

	ret = ui_app_remove_event_handler(NULL);
	assert_eq_with_exit(ret, APP_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_ui_app_exit_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Exits the main loop of application.
 * @scenario		Calls the ui_app_main() and Calls the ui_app_exit().
 */
int utc_application_ui_app_exit_p(void)
{
	ui_app_exit();
	utc_result = 0;

	return 0;
}

void utc_application_app_get_display_state_startup(void)
{
	app_info_h app_info = NULL;
	int ret;

	dlog_print(DLOG_INFO, LOG_TAG, "%s", __FUNCTION__);
	ret = app_get_id(&__context.id);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to get id");
		return;
	}

	ret = app_info_create(__context.id, &app_info);
	if (ret != APP_MANAGER_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create app info");
		return;
	}

	ret = app_info_get_app_component_type(app_info, &__context.comp_type);
	if (ret != APP_MANAGER_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to get app component type");
		app_info_destroy(app_info);
		return;
	}

	app_info_destroy(app_info);
}

void utc_application_app_get_display_state_cleanup(void)
{
	dlog_print(DLOG_INFO, LOG_TAG, "%s", __FUNCTION__);
	if (__context.id) {
		free(__context.id);
		__context.id = NULL;
	}
}

/**
 * @testcase		utc_application_app_get_display_state_p
 * @since_tizen		5.5
 * @type		Positive
 * @description		Gets the display state
 * @scenario            Calls the app_get_display_state(). And then,
 *                      Checks the return value.
 *                      If the running application is service-application,
 *                      the return value is "APP_ERROR_INVALID_CONTEXT".
 *                      If the feature is not supported, the function
 *                      returns "APP_ERROR_NOT_SUPPORTED".
 */
int utc_application_app_get_display_state_p(void)
{
	app_display_state_e state = -1;
	bool feature = false;
	int ret;

	ret = system_info_get_platform_bool(
			"http://tizen.org/feature/display.state",
			&feature);
	if (ret != SYSTEM_INFO_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to get platform feature");
		normal_exit(1);
		return -1;
	}

	ret = app_get_display_state(&state);
	if (ret != APP_ERROR_NONE) {
		if (ret == APP_ERROR_NOT_SUPPORTED && !feature) {
			dlog_print(DLOG_INFO, LOG_TAG,
					"display state is not supported");
			normal_exit(0);
			return 0;
		}

		if (__context.comp_type == APP_INFO_APP_COMPONENT_TYPE_SERVICE_APP &&
				ret == APP_ERROR_INVALID_CONTEXT) {
			dlog_print(DLOG_INFO, LOG_TAG,
					"This is service-application");
			normal_exit(0);
			return 0;
		}

		/**
		 * @remarks Currently, this test application doesn't draw any windows.
		 * So, the app_get_display_state() returns APP_ERROR_INVALID_CONTEXT.
		 * The function returns APP_ERROR_NONE with proper display state while
		 * the running application is resumed or paused.
		 */
		if (ret == APP_ERROR_INVALID_CONTEXT) {
			normal_exit(0);
			return 0;
		}

		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to get display state");
		normal_exit(1);
		return -1;
	}

	if (state != APP_DISPLAY_STATE_ON &&
			state == APP_DISPLAY_STATE_OFF) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Unknown state");
		normal_exit(1);
		return -1;
	}

	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_get_display_state_n
 * @since_tizen		5.5
 * @type		Negative
 * @description		Gets the display state
 * @scenario            Calls the app_get_display_state(). And then,
 *                      Checks the return value.
 *                      The value should be "APP_ERROR_INVALID_PARAMETER".
 */
int utc_application_app_get_display_state_n(void)
{
	int ret;

	ret = app_get_display_state(NULL);
	if (ret != APP_ERROR_INVALID_PARAMETER) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"The result is not invalid parameter");
		normal_exit(1);
		return -1;
	}

	normal_exit(0);

	return 0;
}
