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

#include <system_info.h>

#include <watchface-complication.h>
#include "utc-watchface-complication.h"

#define WATCH_APP_FEATURE "http://tizen.org/feature/watch_app"
#define PROVIDER_ID "org.tizen.watchface_sample_provider/test"
static char __check_user_data[] = "check_user_data";
static bool __is_supported = false;

static void __complication_updated_cb(int complication_id,
		const char *provider_id, watchface_complication_type_e type,
		const bundle *data, void *user_data) {
}

static void __complication_error_cb(
            int complication_id,
            const char *provider_id,
            watchface_complication_type_e type,
            watchface_complication_error_e error,
            void *user_data) {
}

void utc_watchface_complication_startup(void)
{
	system_info_get_platform_bool(WATCH_APP_FEATURE, &__is_supported);
}

void utc_watchface_complication_cleanup(void)
{
}

/**
 * @testcase utc_watchface_complication_get_current_provider_id_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_get_current_provider_id()
 */
int utc_watchface_complication_get_current_provider_id_p(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;
	char *cur_provider_id;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_get_current_provider_id(complication, &cur_provider_id);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	watchface_complication_destroy(complication);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_get_current_provider_id_p
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_get_current_provider_id()
 */
int utc_watchface_complication_get_current_provider_id_n1(void)
{
	int ret;
	char *cur_provider_id;

	ret = watchface_complication_get_current_provider_id(NULL, &cur_provider_id);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_get_current_type_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_get_current_type()
 */
int utc_watchface_complication_get_current_type_p(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;
	watchface_complication_type_e cur_type;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_get_current_type(complication, &cur_type);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	watchface_complication_destroy(complication);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_get_current_type_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_get_current_type()
 */
int utc_watchface_complication_get_current_type_n1(void)
{
	int ret;
	watchface_complication_type_e cur_type;

	ret = watchface_complication_get_current_type(NULL, &cur_type);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_add_updated_cb_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_add_updated_cb()
 */
int utc_watchface_complication_add_updated_cb_p(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_add_updated_cb(complication,
			__complication_updated_cb, __complication_error_cb,
			NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	watchface_complication_destroy(complication);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_add_updated_cb_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_add_updated_cb()
 */
int utc_watchface_complication_add_updated_cb_n1(void)
{
	int ret;

	ret = watchface_complication_add_updated_cb(NULL,
		__complication_updated_cb, __complication_error_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_remove_updated_cb_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_remove_updated_cb()
 */
int utc_watchface_complication_remove_updated_cb_p(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_add_updated_cb(complication,
			__complication_updated_cb, __complication_error_cb,
			NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_remove_updated_cb(complication,
			__complication_updated_cb);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	watchface_complication_destroy(complication);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_remove_updated_cb_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_remove_updated_cb()
 */
int utc_watchface_complication_remove_updated_cb_n1(void)
{
	int ret;

	ret = watchface_complication_remove_updated_cb(NULL,
			__complication_updated_cb);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_send_update_request_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_send_update_request()
 */
int utc_watchface_complication_send_update_request_p(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_send_update_request(complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	watchface_complication_destroy(complication);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_send_update_request_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_send_update_request()
 */
int utc_watchface_complication_send_update_request_n1(void)
{
	int ret;

	ret = watchface_complication_send_update_request(NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_create_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_create()
 */
int utc_watchface_complication_create_p(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	watchface_complication_destroy(complication);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_create_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_create()
 */
int utc_watchface_complication_create_n1(void)
{
	int ret;
	complication_h complication;
	int comp_id = 1;

	ret = watchface_complication_create(comp_id, NULL,
			-1, -1,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_destroy_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_destroy()
 */
int utc_watchface_complication_destroy_p(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_destroy(complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_destroy_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_destroy()
 */
int utc_watchface_complication_destroy_n1(void)
{
	int ret;

	ret = watchface_complication_destroy(NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_data_get_type_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_data_get_type()
 */
int utc_watchface_complication_data_get_type_n1(void)
{
	int ret;
	watchface_complication_type_e type;

	ret = watchface_complication_data_get_type(NULL, &type);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

static void __short_text_complication_updated_cb(int complication_id,
		const char *provider_id, watchface_complication_type_e type,
		const bundle *data, void *user_data) {
	char *text;
	int ret;

	ret = watchface_complication_data_get_short_text(data, &text);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	normal_exit_no_returnval(ret);
}

/**
 * @testcase utc_watchface_complication_data_get_short_text_p1
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_data_get_short_text()
 */
int utc_watchface_complication_data_get_short_text_p1(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_add_updated_cb(complication,
			__short_text_complication_updated_cb,
			__complication_error_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_send_update_request(complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_watchface_complication_data_get_short_text_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_data_get_short_text()
 */
int utc_watchface_complication_data_get_short_text_n1(void)
{
	int ret;
	char *text;

	ret = watchface_complication_data_get_short_text(NULL, &text);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

static void __long_text_complication_updated_cb(int complication_id,
		const char *provider_id, watchface_complication_type_e type,
		const bundle *data, void *user_data) {
	char *text;
	int ret;

	ret = watchface_complication_data_get_long_text(data, &text);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	normal_exit_no_returnval(ret);
}

/**
 * @testcase utc_watchface_complication_data_get_long_text_p1
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_data_get_long_text()
 */
int utc_watchface_complication_data_get_long_text_p1(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_LONG_TEXT,
			WATCHFACE_COMPLICATION_TYPE_LONG_TEXT,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_add_updated_cb(complication,
			__long_text_complication_updated_cb,
			__complication_error_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_send_update_request(complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_watchface_complication_data_get_long_text_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_data_get_long_text()
 */
int utc_watchface_complication_data_get_long_text_n1(void)
{
	int ret;
	char *text;

	ret = watchface_complication_data_get_long_text(NULL, &text);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

static void __title_complication_updated_cb(int complication_id,
		const char *provider_id, watchface_complication_type_e type,
		const bundle *data, void *user_data) {
	char *text;
	int ret;

	ret = watchface_complication_data_get_title(data, &text);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	normal_exit_no_returnval(ret);
}

/**
 * @testcase utc_watchface_complication_data_get_title_p1
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_data_get_title()
 */
int utc_watchface_complication_data_get_title_p1(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_LONG_TEXT,
			WATCHFACE_COMPLICATION_TYPE_LONG_TEXT,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_add_updated_cb(complication,
			__title_complication_updated_cb,
			__complication_error_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_send_update_request(complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_watchface_complication_data_get_title_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_data_get_title()
 */
int utc_watchface_complication_data_get_title_n1(void)
{
	int ret;
	char *text;

	ret = watchface_complication_data_get_title(NULL, &text);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

static void __time_complication_updated_cb(int complication_id,
		const char *provider_id, watchface_complication_type_e type,
		const bundle *data, void *user_data) {
	long time_value;
	int ret;

	ret = watchface_complication_data_get_timestamp(data, &time_value);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	normal_exit_no_returnval(ret);
}

/**
 * @testcase utc_watchface_complication_data_get_timestamp_p1
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_data_get_timestamp()
 */
int utc_watchface_complication_data_get_timestamp_p1(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_TIME,
			WATCHFACE_COMPLICATION_TYPE_TIME,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_add_updated_cb(complication,
			__time_complication_updated_cb,
			__complication_error_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_send_update_request(complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_watchface_complication_data_get_timestamp_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_data_get_timestamp()
 */
int utc_watchface_complication_data_get_timestamp_n1(void)
{
	int ret;
	long timestamp;

	ret = watchface_complication_data_get_timestamp(NULL, &timestamp);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

static void __image_complication_updated_cb(int complication_id,
		const char *provider_id, watchface_complication_type_e type,
		const bundle *data, void *user_data) {
	char *text;
	int ret;

	ret = watchface_complication_data_get_image_path(data, &text);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	normal_exit_no_returnval(ret);
}

/**
 * @testcase utc_watchface_complication_data_get_image_path_p1
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_data_get_image_path()
 */
int utc_watchface_complication_data_get_image_path_p1(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_IMAGE,
			WATCHFACE_COMPLICATION_TYPE_IMAGE,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_add_updated_cb(complication,
			__image_complication_updated_cb,
			__complication_error_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_send_update_request(complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_watchface_complication_data_get_image_path_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_data_get_image_path()
 */
int utc_watchface_complication_data_get_image_path_n1(void)
{
	int ret;
	char *path;

	ret = watchface_complication_data_get_image_path(NULL, &path);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

static void __ranged_complication_updated_cb(int complication_id,
		const char *provider_id, watchface_complication_type_e type,
		const bundle *data, void *user_data) {
	int ret;
	double cur_val, min_val, max_val;

	ret = watchface_complication_data_get_ranged_value(
			data, &cur_val, &min_val, &max_val);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	normal_exit_no_returnval(ret);
}

/**
 * @testcase utc_watchface_complication_data_get_ranged_value_p1
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_data_get_ranged_value()
 */
int utc_watchface_complication_data_get_ranged_value_p1(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_RANGED_VALUE,
			WATCHFACE_COMPLICATION_TYPE_RANGED_VALUE,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_add_updated_cb(complication,
			__ranged_complication_updated_cb,
			__complication_error_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_send_update_request(complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_watchface_complication_data_get_ranged_value_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_data_get_ranged_value()
 */
int utc_watchface_complication_data_get_ranged_value_n1(void)
{
	int ret;
	double cur_val, min_val, max_val;

	ret = watchface_complication_data_get_ranged_value(NULL,
			&cur_val, &min_val, &max_val);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

static void __icon_complication_updated_cb(int complication_id,
		const char *provider_id, watchface_complication_type_e type,
		const bundle *data, void *user_data) {
	char *text;
	int ret;

	ret = watchface_complication_data_get_icon_path(data, &text);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	normal_exit_no_returnval(ret);
}

/**
 * @testcase utc_watchface_complication_data_get_icon_path_p1
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_data_get_icon_path()
 */
int utc_watchface_complication_data_get_icon_path_p1(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_ICON,
			WATCHFACE_COMPLICATION_TYPE_ICON,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_add_updated_cb(complication,
			__icon_complication_updated_cb,
			__complication_error_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_send_update_request(complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_watchface_complication_data_get_icon_path_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_data_get_icon_path()
 */
int utc_watchface_complication_data_get_icon_path_n1(void)
{
	int ret;
	char *text;

	ret = watchface_complication_data_get_icon_path(NULL, &text);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}


static void __extra_complication_updated_cb(int complication_id,
		const char *provider_id, watchface_complication_type_e type,
		const bundle *data, void *user_data) {
	char *text;
	int ret;
	char *user_data_char = (char *)user_data;

	ret = watchface_complication_data_get_extra_data(data, &text);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	assert_eq_with_exit_no_returnval(user_data_char, __check_user_data);
	normal_exit_no_returnval(ret);
}

static void __screen_reader_cb(int complication_id,
		const char *provider_id, watchface_complication_type_e type,
		const bundle *data, void *user_data) {
	char *text;
	int ret;

	ret = watchface_complication_data_get_screen_reader_text(data, &text);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	free(text);
	normal_exit_no_returnval(ret);
}

/**
 * @testcase utc_watchface_complication_data_get_extra_data_p1
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_data_get_extra_data()
 */
int utc_watchface_complication_data_get_extra_data_p1(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_ICON,
			WATCHFACE_COMPLICATION_TYPE_ICON,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_add_updated_cb(complication,
			__extra_complication_updated_cb,
			__complication_error_cb, __check_user_data);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_send_update_request(complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_watchface_complication_data_get_extra_data_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_data_get_extra_data()
 */
int utc_watchface_complication_data_get_extra_data_n1(void)
{
	int ret;
	char *text;

	ret = watchface_complication_data_get_extra_data(NULL, &text);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_allowed_list_create_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_allowed_list_create()
 */
int utc_watchface_complication_allowed_list_create_p(void)
{
	int ret;
	complication_allowed_list_h handle;

	ret = watchface_complication_allowed_list_create(&handle);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	watchface_complication_allowed_list_destroy(handle);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_allowed_list_create_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_allowed_list_create()
 */
int utc_watchface_complication_allowed_list_create_n1(void)
{
	int ret;

	ret = watchface_complication_allowed_list_create(NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_allowed_list_destroy_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_allowed_list_destroy()
 */
int utc_watchface_complication_allowed_list_destroy_p(void)
{
	int ret;
	complication_allowed_list_h handle;

	ret = watchface_complication_allowed_list_create(&handle);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_allowed_list_destroy(handle);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_allowed_list_destroy_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_allowed_list_destroy()
 */
int utc_watchface_complication_allowed_list_destroy_n1(void)
{
	int ret;

	ret = watchface_complication_allowed_list_destroy(NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_allowed_list_add_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_allowed_list_add()
 */
int utc_watchface_complication_allowed_list_add_p(void)
{
	int ret;
	complication_allowed_list_h handle;

	ret = watchface_complication_allowed_list_create(&handle);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_allowed_list_add(
			handle, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	watchface_complication_allowed_list_destroy(handle);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_allowed_list_add_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_allowed_list_add()
 */
int utc_watchface_complication_allowed_list_add_n1(void)
{
	int ret;

	ret = watchface_complication_allowed_list_add(
			NULL, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_allowed_list_add_n2
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_allowed_list_add()
 */
int utc_watchface_complication_allowed_list_add_n2(void)
{
	int ret;
	complication_allowed_list_h handle;

	ret = watchface_complication_allowed_list_create(&handle);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_allowed_list_add(
			handle, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_allowed_list_add(
			handle, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_EXIST_ID);

	watchface_complication_allowed_list_destroy(handle);

	normal_exit(0);
}


/**
 * @testcase utc_watchface_complication_allowed_list_get_nth_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_allowed_list_get_nth()
 */
int utc_watchface_complication_allowed_list_get_nth_p(void)
{
	int ret;
	complication_allowed_list_h handle;
	char *provider_id;
	int types;

	ret = watchface_complication_allowed_list_create(&handle);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_allowed_list_add(
			handle, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_allowed_list_get_nth(
			handle, 0, &provider_id, &types);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	watchface_complication_allowed_list_destroy(handle);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_allowed_list_get_nth_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_allowed_list_get_nth()
 */
int utc_watchface_complication_allowed_list_get_nth_n1(void)
{
	int ret;
	char *provider_id;
	int types;

	ret = watchface_complication_allowed_list_get_nth(
			NULL, 0, &provider_id, &types);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_allowed_list_delete_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_allowed_list_delete()
 */
int utc_watchface_complication_allowed_list_delete_p(void)
{
	int ret;
	complication_allowed_list_h handle;

	ret = watchface_complication_allowed_list_create(&handle);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_allowed_list_add(
			handle, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_allowed_list_delete(handle, PROVIDER_ID);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	watchface_complication_allowed_list_destroy(handle);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_allowed_list_delete_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_allowed_list_delete()
 */
int utc_watchface_complication_allowed_list_delete_n1(void)
{
	int ret;
	complication_allowed_list_h handle;

	ret = watchface_complication_allowed_list_create(&handle);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_allowed_list_add(
			handle, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_allowed_list_delete(handle, "wrong_provider_id");
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NO_DATA);

	watchface_complication_allowed_list_destroy(handle);
	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_allowed_list_delete_n2
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_allowed_list_delete()
 */
int utc_watchface_complication_allowed_list_delete_n2(void)
{
	int ret;

	ret = watchface_complication_allowed_list_delete(NULL, PROVIDER_ID);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_allowed_list_apply_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_allowed_list_apply()
 */
int utc_watchface_complication_allowed_list_apply_p(void)
{
	int ret;
	complication_allowed_list_h handle;
	int comp_id = 1;
	complication_h complication;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_allowed_list_create(&handle);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_allowed_list_add(
			handle, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_allowed_list_apply(complication, handle);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	watchface_complication_allowed_list_destroy(handle);
	watchface_complication_destroy(complication);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_allowed_list_apply_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_allowed_list_apply()
 */
int utc_watchface_complication_allowed_list_apply_n1(void)
{
	int ret;

	ret = watchface_complication_allowed_list_apply(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}


/**
 * @testcase utc_watchface_complication_allowed_list_clear_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_allowed_list_clear()
 */
int utc_watchface_complication_allowed_list_clear_p(void)
{
	int ret;
	complication_allowed_list_h handle;
	int comp_id = 1;
	complication_h complication;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_allowed_list_create(&handle);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_allowed_list_add(
			handle, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_allowed_list_apply(complication, handle);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_allowed_list_clear(complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	watchface_complication_allowed_list_destroy(handle);
	watchface_complication_destroy(complication);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_allowed_list_clear_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_allowed_list_clear()
 */
int utc_watchface_complication_allowed_list_clear_n1(void)
{
	int ret;

	ret = watchface_complication_allowed_list_clear(NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_data_get_screen_reader_text_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_data_get_screen_reader_text()
 */
int utc_watchface_complication_data_get_screen_reader_text_p(void)
{
	int comp_id = 1;
	int ret;
	complication_h complication;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_ICON,
			WATCHFACE_COMPLICATION_TYPE_ICON,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_add_updated_cb(complication,
			__screen_reader_cb,
			__complication_error_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_send_update_request(complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_watchface_complication_data_get_screen_reader_text_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_data_get_screen_reader_text()
 */
int utc_watchface_complication_data_get_screen_reader_text_n1(void)
{
	int ret;
	char *text;

	ret = watchface_complication_data_get_screen_reader_text(NULL, &text);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);;
}

/**
 * @testcase utc_watchface_complication_data_get_screen_reader_text_n2
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_data_get_screen_reader_text()
 */
int utc_watchface_complication_data_get_screen_reader_text_n2(void)
{
	int ret;
	bundle *data;

	data = bundle_create();
	ret = watchface_complication_data_get_screen_reader_text(data, NULL);
	bundle_free(data);

	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_transfer_event_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_complication_transfer_event()
 */
int utc_watchface_complication_transfer_event_p(void)
{
	int comp_id = 1;
	int ret;
	complication_h complication;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_ICON,
			WATCHFACE_COMPLICATION_TYPE_ICON,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_add_updated_cb(complication,
			__screen_reader_cb,
			__complication_error_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_transfer_event(complication,
			WATCHFACE_COMPLICATION_EVENT_TAP);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	normal_exit(0);
}


/**
 * @testcase utc_watchface_complication_transfer_event_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_transfer_event()
 */
int utc_watchface_complication_transfer_event_n1(void)
{
	int ret;
	ret = watchface_complication_transfer_event(NULL,
			WATCHFACE_COMPLICATION_EVENT_TAP);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_watchface_complication_transfer_event_n2
 * @since_tizen 5.0
 * @description Negative test case of watchface_complication_transfer_event()
 */
int utc_watchface_complication_transfer_event_n2(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_ICON,
			WATCHFACE_COMPLICATION_TYPE_ICON,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_transfer_event(complication, 0);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}


static void __timeinfo_complication_updated_cb(int complication_id,
		const char *provider_id, watchface_complication_type_e type,
		const bundle *data, void *user_data) {
	complication_time_info_h info;
	int ret;

	ret = watchface_complication_data_get_timeinfo(data, &info);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	normal_exit_no_returnval(ret);
}

/**
 * @testcase utc_watchface_complication_data_get_timeinfo_p
 * @since_tizen 5.5
 * @description Positive test case of watchface_complication_data_get_timeinfo()
 */
int utc_watchface_complication_data_get_timeinfo_p(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);
	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_TIME,
			WATCHFACE_COMPLICATION_TYPE_TIME,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_add_updated_cb(complication,
			__timeinfo_complication_updated_cb,
			__complication_error_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_send_update_request(complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_watchface_complication_data_get_timeinfo_n
 * @since_tizen 5.5
 * @description Negative test case of watchface_complication_data_get_timeinfo()
 */
int utc_watchface_complication_data_get_timeinfo_n(void)
{
	int ret;
	char *cur_provider_id;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);
	ret = watchface_complication_data_get_timeinfo(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

static void __timezone_complication_updated_cb(int complication_id,
		const char *provider_id, watchface_complication_type_e type,
		const bundle *data, void *user_data) {
	complication_time_info_h info;
	int ret;
	char *timezone;

	watchface_complication_data_get_timeinfo(data, &info);
	ret = watchface_complication_timeinfo_get_timezone(info, &timezone);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	assert_eq_with_exit_no_returnval(strcmp("UTC+9", timezone), 0);
	free(timezone);
	normal_exit_no_returnval(ret);
}

/**
 * @testcase utc_watchface_complication_timeinfo_get_timezone_p
 * @since_tizen 5.5
 * @description Positive test case of watchface_complication_timeinfo_get_timezone()
 */
int utc_watchface_complication_timeinfo_get_timezone_p(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);
	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_TIME,
			WATCHFACE_COMPLICATION_TYPE_TIME,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_add_updated_cb(complication,
			__timezone_complication_updated_cb,
			__complication_error_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_send_update_request(complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_watchface_complication_timeinfo_get_timezone_n
 * @since_tizen 5.5
 * @description Negative test case of watchface_complication_timeinfo_get_timezone()
 */
int utc_watchface_complication_timeinfo_get_timezone_n(void)
{
	int ret;
	char *cur_provider_id;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);
	ret = watchface_complication_timeinfo_get_timezone(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

static void __timezone_id_complication_updated_cb(int complication_id,
		const char *provider_id, watchface_complication_type_e type,
		const bundle *data, void *user_data) {
	complication_time_info_h info;
	char *timezone_id;
	int ret;

	watchface_complication_data_get_timeinfo(data, &info);
	ret = watchface_complication_timeinfo_get_timezone_id(info, &timezone_id);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	assert_eq_with_exit_no_returnval(strcmp("Asia/Seoul", timezone_id), 0);
	free(timezone_id);
	normal_exit_no_returnval(ret);
}

/**
 * @testcase utc_watchface_complication_timeinfo_get_timezone_id_p
 * @since_tizen 5.5
 * @description Positive test case of watchface_complication_timeinfo_get_timezone_id()
 */
int utc_watchface_complication_timeinfo_get_timezone_id_p(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);
	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_TIME,
			WATCHFACE_COMPLICATION_TYPE_TIME,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_add_updated_cb(complication,
			__timezone_id_complication_updated_cb,
			__complication_error_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_send_update_request(complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_watchface_complication_timeinfo_get_timezone_id_n
 * @since_tizen 5.5
 * @description Negative test case of watchface_complication_timeinfo_get_timezone_id()
 */
int utc_watchface_complication_timeinfo_get_timezone_id_n(void)
{
	int ret;
	char *cur_provider_id;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);
	ret = watchface_complication_timeinfo_get_timezone_id(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

static void __timezone_country_complication_updated_cb(int complication_id,
		const char *provider_id, watchface_complication_type_e type,
		const bundle *data, void *user_data) {
	complication_time_info_h info;
	char *country;
	int ret;

	watchface_complication_data_get_timeinfo(data, &info);
	ret = watchface_complication_timeinfo_get_timezone_country(info, &country);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	assert_eq_with_exit_no_returnval(strcmp("Korea", country), 0);
	free(country);
	normal_exit_no_returnval(ret);
}

/**
 * @testcase utc_watchface_complication_timeinfo_get_timezone_country_p
 * @since_tizen 5.5
 * @description Positive test case of watchface_complication_timeinfo_get_timezone_country()
 */
int utc_watchface_complication_timeinfo_get_timezone_country_p(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);
	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_TIME,
			WATCHFACE_COMPLICATION_TYPE_TIME,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_add_updated_cb(complication,
			__timezone_country_complication_updated_cb,
			__complication_error_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_send_update_request(complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_watchface_complication_timeinfo_get_timezone_country_n
 * @since_tizen 5.5
 * @description Negative test case of watchface_complication_timeinfo_get_timezone_country()
 */
int utc_watchface_complication_timeinfo_get_timezone_country_n(void)
{
	int ret;
	char *cur_provider_id;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);
	ret = watchface_complication_timeinfo_get_timezone_country(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

static void __timezone_city_complication_updated_cb(int complication_id,
		const char *provider_id, watchface_complication_type_e type,
		const bundle *data, void *user_data) {
	complication_time_info_h info;
	char *city;
	int ret;

	watchface_complication_data_get_timeinfo(data, &info);
	ret = watchface_complication_timeinfo_get_timezone_city(info, &city);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	assert_eq_with_exit_no_returnval(strcmp("Seoul", city), 0);
	free(city);
	normal_exit_no_returnval(ret);
}

/**
 * @testcase utc_watchface_complication_timeinfo_get_timezone_city_p
 * @since_tizen 5.5
 * @description Positive test case of watchface_complication_timeinfo_get_timezone_city()
 */
int utc_watchface_complication_timeinfo_get_timezone_city_p(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);
	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_TIME,
			WATCHFACE_COMPLICATION_TYPE_TIME,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_add_updated_cb(complication,
			__timezone_city_complication_updated_cb,
			__complication_error_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_send_update_request(complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_watchface_complication_timeinfo_get_timezone_city_n
 * @since_tizen 5.5
 * @description Negative test case of watchface_complication_timeinfo_get_timezone_city()
 */
int utc_watchface_complication_timeinfo_get_timezone_city_n(void)
{
	int ret;
	char *cur_provider_id;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);
	ret = watchface_complication_timeinfo_get_timezone_city(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}


static void __timestamp_complication_updated_cb(int complication_id,
		const char *provider_id, watchface_complication_type_e type,
		const bundle *data, void *user_data) {
	complication_time_info_h info;
	time_t timestamp;
	int ret;

	watchface_complication_data_get_timeinfo(data, &info);
	ret = watchface_complication_timeinfo_get_timestamp(info, &timestamp);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	normal_exit_no_returnval(ret);
}

/**
 * @testcase utc_watchface_complication_timeinfo_get_timestamp_p
 * @since_tizen 5.5
 * @description Positive test case of watchface_complication_timeinfo_get_timestamp()
 */
int utc_watchface_complication_timeinfo_get_timestamp_p(void)
{
	int ret;
	int comp_id = 1;
	complication_h complication;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);
	ret = watchface_complication_create(comp_id, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_TIME,
			WATCHFACE_COMPLICATION_TYPE_TIME,
			WATCHFACE_COMPLICATION_EVENT_NONE, &complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_add_updated_cb(complication,
			__timestamp_complication_updated_cb,
			__complication_error_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_send_update_request(complication);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_watchface_complication_timeinfo_get_timestamp_n
 * @since_tizen 5.5
 * @description Negative test case of watchface_complication_timeinfo_get_timestamp()
 */
int utc_watchface_complication_timeinfo_get_timestamp_n(void)
{
	int ret;
	char *cur_provider_id;

	if (!__is_supported)
		normal_exit(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED);
	ret = watchface_complication_timeinfo_get_timestamp(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}