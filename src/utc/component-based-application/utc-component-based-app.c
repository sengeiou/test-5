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
#include <component_manager.h>
#include <app_control.h>
#include <system_info.h>
#include <dlog.h>
#include <message_port.h>

#include "assert.h"
#include "assert_common.h"

#define TIZEN_FEATURE_SCREEN   "http://tizen.org/feature/screen"

static const char *g_app_id = "org.example.componentbased";
static const char *g_frame_comp_id = "frame_comp_test";
static const char *g_service_comp_id = "service_comp_test";
static const char *g_extra_key = "component_utc_func";
static int g_local_port_id;
static const char *g_utc_name;

static void __message_cb(int local_port_id, const char *remote_app_id,
		const char *remote_port, bool trusted_remote_port,
		bundle *message, void *user_data) {
	char *extra = NULL;
	char *result = NULL;

	dlog_print(DLOG_INFO, LOG_TAG, "remote_app_id(%s), remote_port(%s)",
			remote_app_id, remote_port);

	bundle_get_str(message, g_extra_key, &extra);
	if (!extra)
		return;

	if (g_utc_name && !strcmp(extra, g_utc_name)) {
		bundle_get_str(message, "result", &result);
		if (result && !strcmp(result, "success"))
			normal_exit(0);
		else
			normal_exit(1);
	}
}

void utc_component_based_application_startup(void)
{
	char* app_id;

	if (g_local_port_id == 0) {
		app_get_id(&app_id);
		g_local_port_id = message_port_register_local_port("NativeTCT",
				__message_cb, NULL);
	}
}

void utc_component_based_application_cleanup(void)
{
}

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

	if (extra_data) {
		ret = app_control_add_extra_data(handle, g_extra_key, extra_data);
		if (ret != APP_CONTROL_ERROR_NONE) {
			dlog_print(DLOG_ERROR, LOG_TAG,
					"Failed to add extra data");
			goto end;
		}
	}

	ret = app_control_send_launch_request_sync(handle,
			&reply, &result);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to send launch request async");
	}

end:
	if (handle)
		app_control_destroy(handle);

	return result;
}

static void result_cb(app_control_h h, app_control_error_e result, void *user_data)
{
	dlog_print(DLOG_INFO, LOG_TAG, "reult_cb result[%d]", result);
}

static void reply_cb(app_control_h req,
		app_control_h reply, app_control_error_e result, void *user_data)
{
	dlog_print(DLOG_INFO, LOG_TAG, "reply_cb result[%d]", result);

	if (result == APP_CONTROL_RESULT_SUCCEEDED)
		normal_exit(0);
	else
		normal_exit(1);
}

static int __app_control_send_async(const char *app_id, const char *component_id,
				const char *extra_data)
{
	app_control_h handle = NULL;
	int ret;

		dlog_print(DLOG_ERROR, LOG_TAG, " app control async");
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

	ret = app_control_send_launch_request_async(handle,
			result_cb, reply_cb, NULL);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to send launch request async");
	}

end:
	if (handle)
		app_control_destroy(handle);

	return ret;
}

static Evas_Object* __frame_component_create_cb(
		component_h context,
		void *user_data)
{
	return NULL;
}

static void __frame_component_start_cb(
		component_h context,
		app_control_h app_control,
		bool restarted,
		void *user_data)
{
}

static void __frame_component_resume_cb(
		component_h context,
		void *user_data)
{
}

static void __frame_component_pause_cb(
		component_h context,
		void *user_data)
{
}

static void __frame_component_stop_cb(
		component_h context,
		void *user_data)
{
}

static void __frame_component_destroy_cb(
		component_h context,
		void *user_data)
{
}

static void __frame_component_restore_content_cb(
		component_h context,
		bundle *content,
		void *user_data)
{
}

static void __frame_component_save_content_cb(
		component_h context,
		bundle *content,
		void *user_data)
{
}

static void __frame_component_action_cb(component_h context,
		const char *action, app_control_h app_control,
		void *user_data)
{
}

static void __frame_component_device_orientation_changed_cb(
		component_h context,
		component_device_orientation_e orientation,
		void *user_data)
{
}

static void __frame_component_language_changed_cb(
		component_h context,
		const char *language,
		void *user_data)
{
}

static void __frame_component_region_format_changed_cb(
		component_h context,
		const char *region,
		void *user_data)
{
}

static void __frame_component_low_battery_cb(
		component_h context,
		component_low_battery_status_e status,
		void *user_data)
{
}

static void __frame_component_low_memory_cb(
		component_h context,
		component_low_memory_status_e status,
		void *user_data)
{
}

static void __frame_component_suspended_state_changed_cb(
		component_h context,
		component_suspended_state_e state,
		void *user_data)
{
}

static bool __service_component_create_cb(
		component_h context,
		void *user_data)
{
	return false;
}

static void __service_component_start_command_cb(
		component_h context,
		app_control_h app_control,
		bool restarted,
		void *user_data)
{
}

static void __service_component_destroy_cb(
		component_h context,
		void *user_data)
{
}

static void __service_component_save_content_cb(
		component_h context,
		bundle *content,
		void *user_data)
{
}

static void __service_component_action_cb(component_h context,
		const char *action, app_control_h app_control,
		void *user_data)
{
}

static void __service_component_device_orientation_changed_cb(
		component_h context,
		component_device_orientation_e orientation,
		void *user_data)
{
}

static void __service_component_language_changed_cb(
		component_h context,
		const char *language,
		void *user_data)
{
}

static void __service_component_region_format_changed_cb(
		component_h context,
		const char *region,
		void *user_data)
{
}

static void __service_component_low_battery_cb(
		component_h context,
		component_low_battery_status_e status,
		void *user_data)
{
}

static void __service_component_low_memory_cb(
		component_h context,
		component_low_memory_status_e status,
		void *user_data)
{
}

static void __service_component_suspended_state_changed_cb(
		component_h context,
		component_suspended_state_e state,
		void *user_data)
{
}

/**
 * @testcase		utc_component_based_app_main_p
 * @since_tizen		5.5
 * @description		Run component based application with arguments.
 */
int utc_component_based_app_main_p(void)
{
	int ret;

	ret =  __app_control_send(g_app_id, g_service_comp_id,
			"utc_component_based_app_main");
	assert_eq_with_exit(ret, APP_CONTROL_RESULT_SUCCEEDED);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_component_based_app_main_n
 * @since_tizen		5.5
 * @description		Run component based application with invalid parameter.
 */
int utc_component_based_app_main_n(void)
{
	int ret;

	ret = component_based_app_main(0, NULL, NULL, NULL);
	assert_eq_without_exit(ret, APP_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_component_based_app_add_frame_component_p
 * @since_tizen		5.5
 * @description		Adds frame component to component based application with arguments.
 */
int utc_component_based_app_add_frame_component_p(void)
{
	component_class_h comp = NULL;
	const char *comp_id = "frame_comp_test";

	frame_component_lifecycle_callback_s cb = {
		.create = __frame_component_create_cb,
		.start = __frame_component_start_cb,
		.resume = __frame_component_resume_cb,
		.pause = __frame_component_pause_cb,
		.stop = __frame_component_stop_cb,
		.destroy = __frame_component_destroy_cb,
		.restore_content = __frame_component_restore_content_cb,
		.save_content = __frame_component_save_content_cb,
		.action = __frame_component_action_cb,
		.device_orientation_changed = __frame_component_device_orientation_changed_cb,
		.language_changed = __frame_component_language_changed_cb,
		.region_format_changed = __frame_component_region_format_changed_cb,
		.low_battery = __frame_component_low_battery_cb,
		.low_memory = __frame_component_low_memory_cb,
		.suspended_state_changed = __frame_component_suspended_state_changed_cb
	};

	comp = component_based_app_add_frame_component(comp, comp_id, &cb, NULL);
	assert_with_exit(comp != NULL);
	assert_with_exit(get_last_result() == APP_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_component_based_app_add_frame_component_n
 * @since_tizen		5.5
 * @description		Adds frame component to component based application with invalid parameter.
 */
int utc_component_based_app_add_frame_component_n(void)
{
	component_class_h comp = NULL;
	const char *comp_id = "frame_comp_test";

	comp = component_based_app_add_frame_component(comp, comp_id, NULL, NULL);
	assert_with_exit(get_last_result() == APP_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_component_based_app_add_service_component_p
 * @since_tizen		5.5
 * @description		Adds service component to component based application with arguments.
 */
int utc_component_based_app_add_service_component_p(void)
{
	component_class_h comp = NULL;
	const char *comp_id = "service_comp_test";

	service_component_lifecycle_callback_s cb = {
		.create = __service_component_create_cb,
		.start_command = __service_component_start_command_cb,
		.destroy = __service_component_destroy_cb,
		.save_content = __service_component_save_content_cb,
		.action = __service_component_action_cb,
		.device_orientation_changed = __service_component_device_orientation_changed_cb,
		.language_changed = __service_component_language_changed_cb,
		.region_format_changed = __service_component_region_format_changed_cb,
		.low_battery = __service_component_low_battery_cb,
		.low_memory = __service_component_low_memory_cb,
		.suspended_state_changed = __service_component_suspended_state_changed_cb
	};

	comp = component_based_app_add_service_component(comp, comp_id, &cb, NULL);
	assert_with_exit(comp != NULL);
	assert_with_exit(get_last_result() == APP_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_component_based_app_add_service_component_n
 * @since_tizen		5.5
 * @description		Adds service component to component based application with invalid parameter.
 */
int utc_component_based_app_add_service_component_n(void)
{
	component_class_h comp = NULL;
	const char *comp_id = "service_comp_test";

	comp = component_based_app_add_service_component(comp, comp_id, NULL, NULL);
	assert_with_exit(get_last_result() == APP_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}


/**
 * @testcase		utc_frame_component_get_display_status_p
 * @since_tizen		5.5
 * @description		Gets the display status of frame component.
 */
int utc_frame_component_get_display_status_p(void)
{
	int ret;
	bool is_screen = false;

	/* For IOT headless */
	system_info_get_platform_bool(TIZEN_FEATURE_SCREEN, &is_screen);
	dlog_print(DLOG_INFO, "NativeTCT", "%d", is_screen);
	if (!is_screen) {
		normal_exit(0);
		return 0;
    }

	ret =  __app_control_send_async(g_app_id, g_frame_comp_id,
			"utc_frame_component_get_display_status");
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_frame_component_get_display_status_n
 * @since_tizen		5.5
 * @description		Gets the display status of frame component with invalid parameter.
 */
int utc_frame_component_get_display_status_n(void)
{
	int ret;
	component_display_status_e display;

	ret =  frame_component_get_display_status(NULL, &display);
	assert_eq_with_exit(ret, COMPONENT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_frame_component_get_window_p
 * @since_tizen		5.5
 * @description		Gets the window of frame component.
 */
int utc_frame_component_get_window_p(void)
{
	int ret;
	bool is_screen = false;
	bundle *message;

	/* For IOT headless */
	system_info_get_platform_bool(TIZEN_FEATURE_SCREEN, &is_screen);
	dlog_print(DLOG_INFO, "NativeTCT", "%d", is_screen);
	if (!is_screen) {
		normal_exit(0);
		return 0;
	}

	__app_control_send_async(g_app_id, g_frame_comp_id,
			"utc_frame_component_get_window");

	message = bundle_create();
	g_utc_name = "utc_frame_component_get_window";
	bundle_add_str(message, g_extra_key, g_utc_name);
	ret = message_port_send_message(g_app_id, g_frame_comp_id, message);
	bundle_free(message);
	assert_eq_with_exit(ret, MESSAGE_PORT_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_frame_component_get_window_n
 * @since_tizen		5.5
 * @description		Gets the window of frame component with invalid parameter.
 */
int utc_frame_component_get_window_n(void)
{
	int ret;
	Evas_Object	*window;

	ret =  frame_component_get_window(NULL, &window);
	assert_eq_with_exit(ret, COMPONENT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_component_based_app_exit_p
 * @since_tizen		5.5
 * @description		Exit component based application.
 */
int utc_component_based_app_exit_p(void)
{
	int ret;
	bool running = true;
	int retry_count = 0;

	ret =  __app_control_send_async(g_app_id, g_service_comp_id,
			"utc_component_based_app_exit");
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	 do {
		component_manager_is_running(g_service_comp_id, &running);
                if (!running)
			break;

                usleep(500000);
                retry_count++;
        } while (retry_count <= 10);

	assert_eq_with_exit(running, false);

	normal_exit(0);
	return 0;
}
