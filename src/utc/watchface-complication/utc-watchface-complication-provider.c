/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "assert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <system_info.h>
#include <app_manager.h>
#include <watchface-complication-provider.h>
#include <watchface-editable.h>
#include <dlog.h>
#include <glib.h>

#include "utc-watchface-complication.h"

#define WATCH_APP_FEATURE "http://tizen.org/feature/watch_app"
#define TEST_PROVIDER_ID "org.tizen.watchface_sample_provider/test"
#define PROVIDER_ID "org.tizen.watchface-complication-native-utc/test"
#define EDITOR_CMD_KEY "EDITOR_CMD"
#define EDITOR_ID "org.tizen.watchface_sample_editor"
#define WATCHFACE_ID "org.tizen.watchface_sample"
#define COMPLICATION_TEST_APP "org.tizen.complication_test"
#define MAX_COUNTER 5
static char __check_user_data[] = "check_user_data";
static bool __is_supported = false;

static void __run_app(char *target_app, char *key, char *value) {
	static app_control_h app_control;
	bool is_running = false;
	int counter = MAX_COUNTER;
	int ret;

	ret = app_control_create(&app_control);
	ret = app_control_set_app_id(app_control, target_app);
	if (key && value) {
		app_control_add_extra_data(app_control, key, value);
	}
	app_control_add_extra_data(app_control, "SENDER_ID", "org.tizen.watchface-complication-native-utc");
	do {
		ret = app_control_send_launch_request(app_control, NULL, NULL);
		if (ret != APP_CONTROL_ERROR_NONE)
			sleep(1);
		app_manager_is_running(target_app, &is_running);
	} while (--counter > 0 && !is_running);
	sleep(1);

	app_control_destroy(app_control);
}

void utc_watchface_complication_provider_startup(void)
{
	system_info_get_platform_bool(WATCH_APP_FEATURE, &__is_supported);
}

void utc_watchface_complication_provider_cleanup(void)
{
}

static void __complication_provider_update_requested_cb1(
		const char *provider_id, const char *req_appid,
		watchface_complication_type_e type, const bundle *context,
		bundle *share_data, void *user_data) {
}

static void __complication_provider_update_requested_cb2(
		const char *provider_id, const char *req_appid,
		watchface_complication_type_e type, const bundle *context,
		bundle *share_data, void *user_data) {
}

/**
 * @testcase watchface_complication_provider_add_update_requested_cb
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_provider_add_update_requested_cb()
 */
int utc_watchface_complication_provider_add_update_requested_cb_p(void)
{
	int ret;

	ret = watchface_complication_provider_add_update_requested_cb(
			PROVIDER_ID, __complication_provider_update_requested_cb1, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase watchface_complication_provider_add_update_requested_cb
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_add_update_requested_cb()
 */
int utc_watchface_complication_provider_add_update_requested_cb_n1(void)
{
	int ret;

	ret = watchface_complication_provider_add_update_requested_cb(NULL, NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_remove_update_requested_cb_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_provider_remove_update_requested_cb()
 */
int utc_watchface_complication_provider_remove_update_requested_cb_p(void)
{
	int ret;

	ret = watchface_complication_provider_add_update_requested_cb(
			PROVIDER_ID, __complication_provider_update_requested_cb2, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_provider_remove_update_requested_cb(
			PROVIDER_ID, __complication_provider_update_requested_cb2);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_remove_update_requested_cb_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_remove_update_requested_cb()
 */
int utc_watchface_complication_provider_remove_update_requested_cb_n1(void)
{
	int ret;

	ret = watchface_complication_provider_remove_update_requested_cb(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_notify_update_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_provider_notify_update()
 */
int utc_watchface_complication_provider_notify_update_p(void)
{
	int ret;
	ret = watchface_complication_provider_add_update_requested_cb(
			PROVIDER_ID, __complication_provider_update_requested_cb2, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_provider_notify_update(PROVIDER_ID);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_provider_remove_update_requested_cb(
			PROVIDER_ID, __complication_provider_update_requested_cb2);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_notify_update_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_notify_update()
 */
int utc_watchface_complication_provider_notify_update_n1(void)
{
	int ret;

	ret = watchface_complication_provider_notify_update(NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

void _utc_watchface_complication_provider_setup_reply_to_editor_p_checker(void) {
	int ret;
	bundle *context = bundle_create();

	ret = watchface_complication_provider_setup_reply_to_editor(__test_control, context);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	bundle_free(context);
	app_control_destroy(__test_control);

	normal_exit_no_returnval(0);
}

static void _update_requested_cb(const watchface_editable_h handle,
			int selected_idx,
			const watchface_editable_edit_state_e state,
			void *user_data)
{
}

static void _setup_on_edit_ready(
		watchface_editable_container_h ed_con_h,
		const char *editor_appid,
		void *user_data) {
	int ret;
	int editable_id = 1;
	complication_h comp;
	watchface_editable_highlight_h highlight;

	ret = watchface_editable_highlight_create(&highlight,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_set_geometry(highlight,
			100, 100, 30, 30);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_create(1, TEST_PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_EVENT_NONE, &comp);

	ret = watchface_editable_add_complication(ed_con_h, editable_id, comp, highlight);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_request_edit(ed_con_h, _update_requested_cb, NULL);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
}

/**
 * @testcase utc_watchface_complication_provider_setup_reply_to_editor_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_provider_setup_reply_to_editor()
 */
int utc_watchface_complication_provider_setup_reply_to_editor_p(void)
{
	int ret;

	ret = watchface_editable_add_edit_ready_cb(_setup_on_edit_ready, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	__run_app(EDITOR_ID, EDITOR_CMD_KEY, SETUP_REPLY_TO_EDITOR_TEST_VAL);

	return 0;
}


/**
 * @testcase utc_watchface_complication_provider_setup_reply_to_editor_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_setup_reply_to_editor()
 */
int utc_watchface_complication_provider_setup_reply_to_editor_n1(void)
{
	int ret;

	ret = watchface_complication_provider_setup_reply_to_editor(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

void _utc_watchface_complication_provider_setup_is_editing_p_checker(void) {
	int ret;
	bool is_editing;

	ret = watchface_complication_provider_setup_is_editing(__test_control, &is_editing);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	normal_exit_no_returnval(0);
}

/**
 * @testcase utc_watchface_complication_provider_setup_is_editing_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_provider_setup_is_editing()
 */
int utc_watchface_complication_provider_setup_is_editing_p(void)
{
	int ret;

	ret = watchface_editable_add_edit_ready_cb(_setup_on_edit_ready, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	__run_app(EDITOR_ID, EDITOR_CMD_KEY, SETUP_IS_EDITING_TEST_VAL);

	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_setup_is_editing_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_setup_is_editing()
 */
int utc_watchface_complication_provider_setup_is_editing_n1(void)
{
	int ret;
	bool is_editing;

	ret = watchface_complication_provider_setup_is_editing(NULL, &is_editing);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

void _utc_watchface_complication_provider_setup_get_context_p_checker(void) {
	int ret;
	bundle *context;

	ret = watchface_complication_provider_setup_get_context(__test_control, &context);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	bundle_free(context);
	app_control_destroy(__test_control);

	normal_exit_no_returnval(0);
}

/**
 * @testcase utc_watchface_complication_provider_setup_get_context_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_provider_setup_get_context()
 */
int utc_watchface_complication_provider_setup_get_context_p(void)
{
	int ret;

	ret = watchface_editable_add_edit_ready_cb(_setup_on_edit_ready, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	__run_app(EDITOR_ID, EDITOR_CMD_KEY, SETUP_GET_CONTEXT_TEST_VAL);

	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_setup_get_context_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_setup_get_context()
 */
int utc_watchface_complication_provider_setup_get_context_n1(void)
{
	int ret;
	bundle *b;

	ret = watchface_complication_provider_setup_get_context(NULL, &b);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

static void __update_requested_cb(
                const char *provider_id, const char *req_appid,
                watchface_complication_type_e type, const bundle *context,
                bundle *shared_data, void *user_data) {
	int ret = WATCHFACE_COMPLICATION_ERROR_IO_ERROR;
	complication_time_info_h info;

	switch(type) {
	case WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT :
		ret = watchface_complication_provider_data_set_short_text(
			shared_data, "short text");
		assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
		ret =  watchface_complication_provider_data_set_title(
			shared_data, "title");
		break;
	case WATCHFACE_COMPLICATION_TYPE_LONG_TEXT :
		ret = watchface_complication_provider_data_set_long_text(
			shared_data, "long text");
		assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
		ret = watchface_complication_provider_data_set_extra_data(
			shared_data, "extra data");
		break;
	case WATCHFACE_COMPLICATION_TYPE_RANGED_VALUE :
		ret = watchface_complication_provider_data_set_ranged_value(
			shared_data, 50.0, 0.0, 100.0);
		break;
	case WATCHFACE_COMPLICATION_TYPE_ICON :
		ret = watchface_complication_provider_data_set_icon_path(
			shared_data, "temp_icon_path");
		break;
	case WATCHFACE_COMPLICATION_TYPE_IMAGE :
		ret = watchface_complication_provider_data_set_image_path(
			shared_data, "temp_image_path");
		break;
	case WATCHFACE_COMPLICATION_TYPE_TIME :
		ret = watchface_complication_provider_data_set_timestamp(
			shared_data, 12345);
		assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

		watchface_complication_provider_timeinfo_create(&info);
		ret = watchface_complication_provider_timeinfo_set_timezone(info, "UTC+9");
		assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

		ret = watchface_complication_provider_timeinfo_set_timezone_id(info, "Asia/Seoul");
		assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

		ret = watchface_complication_provider_timeinfo_set_timezone_country(info, "Korea");
		assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

		ret = watchface_complication_provider_timeinfo_set_timezone_city(info, "Seoul");
		assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

		ret = watchface_complication_provider_data_set_timeinfo(shared_data, info);
		assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

		watchface_complication_provider_timeinfo_destroy(info);
		break;
	default :
		break;
	}

	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	normal_exit_no_returnval(0);
}

/**
 * @testcase utc_watchface_complication_provider_data_set_short_text_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_provider_data_set_short_text()
 */
int utc_watchface_complication_provider_data_set_short_text_p(void)
{
	int ret;

	ret = watchface_complication_provider_add_update_requested_cb(
			PROVIDER_ID, __update_requested_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	__run_app(COMPLICATION_TEST_APP, "COMP_TYPE", "SHORT_TEXT");

	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_data_set_short_text_n1
 * @since_tizen 5.0
 * @description Negative test case of utc_watchface_complication_provider_data_set_short_text_n1()
 */
int utc_watchface_complication_provider_data_set_short_text_n1(void)
{
	int ret;
	bundle *shared_data = bundle_create();

	ret = watchface_complication_provider_data_set_short_text(shared_data,
			"text data");
	bundle_free(shared_data);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_data_set_long_text_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_provider_data_set_long_text()
 */
int utc_watchface_complication_provider_data_set_long_text_p(void)
{
	int ret;

	ret = watchface_complication_provider_add_update_requested_cb(
			PROVIDER_ID, __update_requested_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	__run_app(COMPLICATION_TEST_APP, "COMP_TYPE", "LONG_TEXT");

	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_data_set_long_text_n1
 * @since_tizen 5.0
 * @description Negative test case of utc_watchface_complication_provider_data_set_long_text_n1()
 */
int utc_watchface_complication_provider_data_set_long_text_n1(void)
{
	int ret;
	bundle *shared_data = bundle_create();

	ret = watchface_complication_provider_data_set_long_text(shared_data,
			"text data");
	bundle_free(shared_data);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_data_set_title_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_provider_data_set_title()
 */
int utc_watchface_complication_provider_data_set_title_p(void)
{
	int ret;

	ret = watchface_complication_provider_add_update_requested_cb(
			PROVIDER_ID, __update_requested_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	__run_app(COMPLICATION_TEST_APP, "COMP_TYPE", "SHORT_TEXT");

	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_data_set_title_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_data_set_title()
 */
int utc_watchface_complication_provider_data_set_title_n1(void)
{
	int ret;
	bundle *shared_data = bundle_create();

	ret = watchface_complication_provider_data_set_title(NULL, "text data");
	bundle_free(shared_data);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_data_set_timestamp_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_provider_data_set_timestamp()
 */
int utc_watchface_complication_provider_data_set_timestamp_p(void)
{
	int ret;

	ret = watchface_complication_provider_add_update_requested_cb(
			PROVIDER_ID, __update_requested_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	__run_app(COMPLICATION_TEST_APP, "COMP_TYPE", "TIME");

	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_data_set_timestamp_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_data_set_timestamp()
 */
int utc_watchface_complication_provider_data_set_timestamp_n1(void)
{
	int ret;
	time_t seconds;
	bundle *shared_data = bundle_create();

	seconds = time(NULL);
	ret = watchface_complication_provider_data_set_timestamp(
			shared_data, seconds);
	bundle_free(shared_data);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}


/**
 * @testcase utc_watchface_complication_provider_data_set_image_path_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_provider_data_set_image_path()
 */
int utc_watchface_complication_provider_data_set_image_path_p(void)
{
	int ret;

	ret = watchface_complication_provider_add_update_requested_cb(
			PROVIDER_ID, __update_requested_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	__run_app(COMPLICATION_TEST_APP, "COMP_TYPE", "IMAGE");

	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_data_set_image_path_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_data_set_image_path()
 */
int utc_watchface_complication_provider_data_set_image_path_n1(void)
{
	int ret;
	bundle *shared_data = bundle_create();

	ret = watchface_complication_provider_data_set_image_path(
			shared_data, "IMAGE PATH");
	bundle_free(shared_data);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_data_set_ranged_value_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_provider_data_set_ranged_value()
 */
int utc_watchface_complication_provider_data_set_ranged_value_p(void)
{
	int ret;

	ret = watchface_complication_provider_add_update_requested_cb(
			PROVIDER_ID, __update_requested_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	__run_app(COMPLICATION_TEST_APP, "COMP_TYPE", "RANGED_VALUE");

	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_data_set_ranged_value_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_data_set_ranged_value()
 */
int utc_watchface_complication_provider_data_set_ranged_value_n1(void)
{
	int ret;
	bundle *shared_data = bundle_create();

	ret = watchface_complication_provider_data_set_ranged_value(
			shared_data, 50, 0, -1);
	bundle_free(shared_data);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_data_set_icon_path_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_provider_data_set_icon_path()
 */
int utc_watchface_complication_provider_data_set_icon_path_p(void)
{
	int ret;

	ret = watchface_complication_provider_add_update_requested_cb(
			PROVIDER_ID, __update_requested_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	__run_app(COMPLICATION_TEST_APP, "COMP_TYPE", "ICON");

	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_data_set_icon_path_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_data_set_icon_path()
 */
int utc_watchface_complication_provider_data_set_icon_path_n1(void)
{
	int ret;
	bundle *shared_data = bundle_create();

	ret = watchface_complication_provider_data_set_icon_path(
			shared_data, "ICON PATH");
	bundle_free(shared_data);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}


/**
 * @testcase utc_watchface_complication_provider_data_set_extra_data_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_provider_data_set_extra_data()
 */
int utc_watchface_complication_provider_data_set_extra_data_p(void)
{
	int ret;

	ret = watchface_complication_provider_add_update_requested_cb(
			PROVIDER_ID, __update_requested_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	__run_app(COMPLICATION_TEST_APP, "COMP_TYPE", "LONG_TEXT");

	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_data_set_extra_data_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_data_set_extra_data()
 */
int utc_watchface_complication_provider_data_set_extra_data_n1(void)
{
	int ret;
	bundle *shared_data = bundle_create();

	ret = watchface_complication_provider_data_set_extra_data(
			shared_data, NULL);
	bundle_free(shared_data);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_data_set_screen_reader_text_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_provider_data_set_screen_reader_text()
 */
int utc_watchface_complication_provider_data_set_screen_reader_text_p(void)
{
	int ret;
	bundle *shared_data = bundle_create();

	ret = watchface_complication_provider_data_set_screen_reader_text(
			shared_data, "screen_reader_text test");
	bundle_free(shared_data);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_data_set_screen_reader_text_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_data_set_screen_reader_text()
 */
int utc_watchface_complication_provider_data_set_screen_reader_text_n1(void)
{
	int ret;
	bundle *shared_data = bundle_create();

	ret = watchface_complication_provider_data_set_screen_reader_text(
			shared_data, NULL);
	bundle_free(shared_data);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

void _utc_watchface_complication_provider_data_is_valid_p_checker(
                const char *provider_id, const char *req_appid,
                watchface_complication_type_e type, const bundle *context,
                bundle *shared_data, void *user_data) {

	bool is_valid;
	char *user_data_char = (char *)user_data;

	if (type == WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT) {
		watchface_complication_provider_data_set_short_text(
			shared_data, "short_text");
		watchface_complication_provider_data_is_valid(shared_data, &is_valid);

		assert_eq_with_exit_no_returnval(is_valid, true);
		assert_eq_with_exit_no_returnval(user_data_char, __check_user_data);
		normal_exit_no_returnval(0);
	}
}

void _utc_watchface_complication_provider_data_is_valid_n1_checker(
                const char *provider_id, const char *req_appid,
                watchface_complication_type_e type, const bundle *context,
                bundle *shared_data, void *user_data) {

	bool is_valid;

	if (type == WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT) {
		watchface_complication_provider_data_set_long_text(
			shared_data, "long_text");
		watchface_complication_provider_data_is_valid(shared_data, &is_valid);

		assert_eq_with_exit_no_returnval(is_valid, false);
		normal_exit_no_returnval(0);
	}
}

void _utc_watchface_complication_provider_data_is_valid_n2_checker(
                const char *provider_id, const char *req_appid,
                watchface_complication_type_e type, const bundle *context,
                bundle *shared_data, void *user_data) {
    int ret;
	bool is_valid;
	bundle *data = bundle_create();

	ret = watchface_complication_provider_data_is_valid(data, &is_valid);

	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);
	normal_exit_no_returnval(0);
}


/**
 * @testcase utc_watchface_complication_provider_data_is_valid_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_provider_data_is_valid()
 */
int utc_watchface_complication_provider_data_is_valid_p(void)
{
	int ret;

	ret = watchface_complication_provider_add_update_requested_cb(
			PROVIDER_ID, _utc_watchface_complication_provider_data_is_valid_p_checker, __check_user_data);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	__run_app(COMPLICATION_TEST_APP, "COMP_TYPE", "SHORT_TEXT");

	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_data_is_valid_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_data_is_valid()
 */
int utc_watchface_complication_provider_data_is_valid_n1(void)
{
	int ret;

	ret = watchface_complication_provider_add_update_requested_cb(
			PROVIDER_ID, _utc_watchface_complication_provider_data_is_valid_n1_checker, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	__run_app(COMPLICATION_TEST_APP, "COMP_TYPE", "SHORT_TEXT");

	return 0;
}


/**
 * @testcase utc_watchface_complication_provider_data_is_valid_n2
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_data_is_valid()
 */
int utc_watchface_complication_provider_data_is_valid_n2(void)
{
	int ret;

	ret = watchface_complication_provider_add_update_requested_cb(
			PROVIDER_ID, _utc_watchface_complication_provider_data_is_valid_n2_checker, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	__run_app(COMPLICATION_TEST_APP, "COMP_TYPE", "SHORT_TEXT");

	return 0;

}

void __utc_watchface_complication_provider_event_get_type_p_checker(void)
{
	watchface_complication_event_type_e event_type = WATCHFACE_COMPLICATION_EVENT_NONE;
	watchface_complication_provider_event_get_type(__test_control, &event_type);

	assert_eq_with_exit_no_returnval(event_type, WATCHFACE_COMPLICATION_EVENT_TAP);
	normal_exit_no_returnval(0);

}

/**
 * @testcase utc_watchface_complication_provider_event_get_type_p
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_event_get_type()
 */
int utc_watchface_complication_provider_event_get_type_p(void)
{
	__event_cmd = EVENT_GET_EVENT_TYPE_TEST_VAL;
	__run_app(COMPLICATION_TEST_APP, "EVENT_TEST", EVENT_GET_EVENT_TYPE_TEST_VAL);
	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_event_get_type_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_event_get_type()
 */
int utc_watchface_complication_provider_event_get_type_n1(void)
{
	int ret;
	watchface_complication_event_type_e event_type;

	ret = watchface_complication_provider_event_get_type(NULL, &event_type);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

void __utc_watchface_complication_provider_event_get_provider_id_p_checker(void)
{
	int ret;
	char *provider_id = NULL;

	ret = watchface_complication_provider_event_get_provider_id(__test_control, &provider_id);

	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	free(provider_id);
	normal_exit_no_returnval(0);

}

/**
 * @testcase utc_watchface_complication_provider_event_get_provider_id_p
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_event_get_provider_id()
 */
int utc_watchface_complication_provider_event_get_provider_id_p(void)
{
	__event_cmd = EVENT_GET_PROVIDER_ID_TEST_VAL;
	__run_app(COMPLICATION_TEST_APP, "EVENT_TEST", EVENT_GET_PROVIDER_ID_TEST_VAL);
	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_event_get_provider_id_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_event_get_provider_id()
 */
int utc_watchface_complication_provider_event_get_provider_id_n1(void)
{
	int ret;
	char *provider_id = NULL;

	ret = watchface_complication_provider_event_get_provider_id(NULL, &provider_id);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

void __utc_watchface_complication_provider_event_get_complication_type_p_checker(void)
{
	int ret;
	watchface_complication_type_e type;

	ret = watchface_complication_provider_event_get_complication_type(__test_control, &type);

	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	normal_exit_no_returnval(0);

}

/**
 * @testcase utc_watchface_complication_provider_event_get_complication_type_p
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_event_get_complication_type()
 */
int utc_watchface_complication_provider_event_get_complication_type_p(void)
{
	__event_cmd = EVENT_GET_COMP_TYPE_TEST_VAL;
	__run_app(COMPLICATION_TEST_APP, "EVENT_TEST", EVENT_GET_COMP_TYPE_TEST_VAL);
	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_event_get_complication_type_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_event_get_complication_type()
 */
int utc_watchface_complication_provider_event_get_complication_type_n1(void)
{
	int ret;
	watchface_complication_type_e type;

	ret = watchface_complication_provider_event_get_complication_type(NULL, &type);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

void __utc_watchface_complication_provider_event_get_context_p_checker(void)
{
	int ret;
	watchface_complication_type_e type;

	ret = watchface_complication_provider_event_get_complication_type(__test_control, &type);

	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	normal_exit_no_returnval(0);

}

/**
 * @testcase utc_watchface_complication_provider_event_get_context_p
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_event_get_context()
 */
int utc_watchface_complication_provider_event_get_context_p(void)
{
	__event_cmd = EVENT_GET_CONTEXT_TEST_VAL;
	__run_app(COMPLICATION_TEST_APP, "EVENT_TEST", EVENT_GET_CONTEXT_TEST_VAL);
	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_event_get_context_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_provider_event_get_context()
 */
int utc_watchface_complication_provider_event_get_context_n1(void)
{
	int ret;
	bundle *context = bundle_create();

	ret = watchface_complication_provider_event_get_context(NULL, &context);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);
	bundle_free(context);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_timeinfo_create_p1
 * @since_tizen 5.5
 * @description Negative test case of watchface_complication_provider_timeinfo_create()
 */
int utc_watchface_complication_provider_timeinfo_create_p1(void)
{
	int ret;
	complication_time_info_h info;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);

	ret = watchface_complication_provider_timeinfo_create(&info);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	watchface_complication_provider_timeinfo_destroy(info);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_timeinfo_create_n1
 * @since_tizen 5.5
 * @description Negative test case of watchface_complication_provider_timeinfo_create()
 */
int utc_watchface_complication_provider_timeinfo_create_n1(void)
{
	int ret;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);

	ret = watchface_complication_provider_timeinfo_create(NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_timeinfo_destroy_p1
 * @since_tizen 5.5
 * @description Negative test case of watchface_complication_provider_timeinfo_destroy()
 */
int utc_watchface_complication_provider_timeinfo_destroy_p1(void)
{
	int ret;
	complication_time_info_h info;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);

	ret = watchface_complication_provider_timeinfo_create(&info);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	ret = watchface_complication_provider_timeinfo_destroy(info);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_timeinfo_destroy_n1
 * @since_tizen 5.5
 * @description Negative test case of watchface_complication_provider_timeinfo_destroy()
 */
int utc_watchface_complication_provider_timeinfo_destroy_n1(void)
{
	int ret;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);

	ret = watchface_complication_provider_timeinfo_destroy(NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_timeinfo_set_timezone_p
 * @since_tizen 5.5
 * @description Positive test case of watchface_complication_provider_timeinfo_set_timezone()
 */
int utc_watchface_complication_provider_timeinfo_set_timezone_p(void)
{
	int ret;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);

	ret = watchface_complication_provider_add_update_requested_cb(
			PROVIDER_ID, __update_requested_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	__run_app(COMPLICATION_TEST_APP, "COMP_TYPE", "TIME_ZONE");

	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_timeinfo_set_timezone_n1
 * @since_tizen 5.5
 * @description Negative test case of watchface_complication_provider_timeinfo_set_timezone()
 */
int utc_watchface_complication_provider_timeinfo_set_timezone_n1(void)
{
	int ret;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);

	ret = watchface_complication_provider_timeinfo_set_timezone(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_timeinfo_set_timezone_id_p
 * @since_tizen 5.5
 * @description Positive test case of watchface_complication_provider_timeinfo_set_timezone_id()
 */
int utc_watchface_complication_provider_timeinfo_set_timezone_id_p(void)
{
	int ret;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);

	ret = watchface_complication_provider_add_update_requested_cb(
			PROVIDER_ID, __update_requested_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	__run_app(COMPLICATION_TEST_APP, "COMP_TYPE", "TIME_ZONE_ID");

	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_timeinfo_set_timezone_id_n1
 * @since_tizen 5.5
 * @description Negative test case of watchface_complication_provider_timeinfo_set_timezone_id()
 */
int utc_watchface_complication_provider_timeinfo_set_timezone_id_n1(void)
{
	int ret;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);

	ret = watchface_complication_provider_timeinfo_set_timezone_id(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_timeinfo_set_timezone_country_p
 * @since_tizen 5.5
 * @description Positive test case of watchface_complication_provider_timeinfo_set_timezone_country()
 */
int utc_watchface_complication_provider_timeinfo_set_timezone_country_p(void)
{
	int ret;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);

	ret = watchface_complication_provider_add_update_requested_cb(
			PROVIDER_ID, __update_requested_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	__run_app(COMPLICATION_TEST_APP, "COMP_TYPE", "TIME_ZONE_COUNTRY");

	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_timeinfo_set_timezone_country_n1
 * @since_tizen 5.5
 * @description Negative test case of watchface_complication_provider_timeinfo_set_timezone_country()
 */
int utc_watchface_complication_provider_timeinfo_set_timezone_country_n1(void)
{
	int ret;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);

	ret = watchface_complication_provider_timeinfo_set_timezone_country(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_timeinfo_set_timezone_city_p
 * @since_tizen 5.5
 * @description Positive test case of watchface_complication_provider_timeinfo_set_timezone_city()
 */
int utc_watchface_complication_provider_timeinfo_set_timezone_city_p(void)
{
	int ret;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);

	ret = watchface_complication_provider_add_update_requested_cb(
			PROVIDER_ID, __update_requested_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	__run_app(COMPLICATION_TEST_APP, "COMP_TYPE", "TIME_ZONE_CITY");

	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_timeinfo_set_timezone_city_n1
 * @since_tizen 5.5
 * @description Negative test case of watchface_complication_provider_timeinfo_set_timezone_city()
 */
int utc_watchface_complication_provider_timeinfo_set_timezone_city_n1(void)
{
	int ret;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);

	ret = watchface_complication_provider_timeinfo_set_timezone_city(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_provider_data_set_timeinfo_p
 * @since_tizen 5.5
 * @description Positive test case of watchface_complication_provider_data_set_timeinfo()
 */
int utc_watchface_complication_provider_data_set_timeinfo_p(void)
{
	int ret;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);

	ret = watchface_complication_provider_add_update_requested_cb(
			PROVIDER_ID, __update_requested_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	__run_app(COMPLICATION_TEST_APP, "COMP_TYPE", "TIME_INFO");

	return 0;
}

/**
 * @testcase utc_watchface_complication_provider_data_set_timeinfo_n1
 * @since_tizen 5.5
 * @description Negative test case of watchface_complication_provider_data_set_timeinfo()
 */
int utc_watchface_complication_provider_data_set_timeinfo_n1(void)
{
	int ret;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);

	ret = watchface_complication_provider_data_set_timeinfo(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}