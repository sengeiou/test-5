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
#include <Ecore.h>

#include <system_info.h>
#include <app_manager.h>
#include <app_control.h>

#include <watchface-editable.h>
#include "utc-watchface-complication.h"

#define PROVIDER_ID "org.tizen.watchface_sample_provider/test"
#define EDITOR_ID "org.tizen.watchface_sample_editor"
#define MAX_COUNTER 5
#define GEO_X 100
#define GEO_Y 100
#define GEO_W 100
#define GEO_H 100
static char __check_user_data[] = "check_user_data";

static void _run_editor_app() {
	static app_control_h app_control;
	bool is_running = false;
	int counter = MAX_COUNTER;
	int ret;

	ret = app_control_create(&app_control);
	ret = app_control_set_app_id(app_control, EDITOR_ID);
	app_control_add_extra_data(app_control, "SENDER_ID", "org.tizen.watchface-complication-native-utc");
	do {
		ret = app_control_send_launch_request(app_control, NULL, NULL);
		if (ret != APP_CONTROL_ERROR_NONE)
			sleep(1);
		app_manager_is_running(EDITOR_ID, &is_running);
	} while (--counter > 0 && !is_running);
	sleep(1);
}

static void _edit_ready_cb(watchface_editable_container_h ed_con_h,
		const char *editor_appid,
		void *user_data) {
}

void utc_watchface_editable_startup(void)
{
}

void utc_watchface_editable_cleanup(void)
{
}

/**
 * @testcase utc_watchface_editable_candidates_list_create_n
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_candidates_list_create()
 */
int utc_watchface_editable_candidates_list_create_n(void)
{
	int ret;

	ret = watchface_editable_candidates_list_create(NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_candidates_list_create_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_editable_candidates_list_create()
 */
int utc_watchface_editable_candidates_list_create_p(void)
{
	int ret;
	complication_candidates_list_h list;

	ret = watchface_editable_candidates_list_create(&list);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	assert(list);

	watchface_editable_candidates_list_destroy(list);
	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_candidates_list_add_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_candidates_list_add()
 */
int utc_watchface_editable_candidates_list_add_n1(void)
{
	int ret;
	bundle *candidate;

	candidate = bundle_create();
	assert(candidate);

	bundle_add_str(candidate, "COLOR", "RED");

	ret = watchface_editable_candidates_list_add(NULL, candidate);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	bundle_free(candidate);
	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_candidates_list_add_n2
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_candidates_list_add()
 */
int utc_watchface_editable_candidates_list_add_n2(void)
{
	int ret;
	complication_candidates_list_h list;

	ret = watchface_editable_candidates_list_create(&list);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);


	ret = watchface_editable_candidates_list_add(list, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	watchface_editable_candidates_list_destroy(list);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_candidates_list_add_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_editable_candidates_list_add()
 */
int utc_watchface_editable_candidates_list_add_p(void)
{
	int ret;
	complication_candidates_list_h list;
	bundle *candidate;

	ret = watchface_editable_candidates_list_create(&list);
	assert(list);

	candidate = bundle_create();
	assert(candidate);
	bundle_add_str(candidate, "COLOR", "RED");

	ret = watchface_editable_candidates_list_add(list, candidate);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	watchface_editable_candidates_list_destroy(list);
	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_candidates_list_destroy_n
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_candidates_list_destroy()
 */
int utc_watchface_editable_candidates_list_destroy_n(void)
{
	int ret;

	ret = watchface_editable_candidates_list_destroy(NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_candidates_list_destroy_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_editable_candidates_list_destroy()
 */
int utc_watchface_editable_candidates_list_destroy_p(void)
{
	int ret;
	complication_candidates_list_h list;

	ret = watchface_editable_candidates_list_create(&list);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	assert(list);

	watchface_editable_candidates_list_destroy(list);
	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_add_design_element_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_add_design_element()
 */
int utc_watchface_editable_add_design_element_n1(void)
{
	int ret;
	complication_candidates_list_h list;
	bundle *candidate;
	watchface_editable_highlight_h highlight;

	watchface_editable_candidates_list_create(&list);

	candidate = bundle_create();
	bundle_add_str(candidate, "COLOR", "RED");
	ret = watchface_editable_candidates_list_add(list, candidate);

	ret = watchface_editable_highlight_create(&highlight,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_set_geometry(highlight,
			100, 100, 30, 30);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_add_design_element(NULL, 0, 0, list, highlight, "Dummy");
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_add_design_element_n2
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_add_design_element()
 */
int utc_watchface_editable_add_design_element_n2(void)
{
	int ret;
	complication_candidates_list_h list;
	watchface_editable_highlight_h highlight;

	watchface_editable_candidates_list_create(&list);

	ret = watchface_editable_highlight_create(&highlight,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_set_geometry(highlight,
			100, 100, 30, 30);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_add_design_element(NULL, 0, 0, list, highlight, "Dummy");
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_add_design_element_n3
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_add_design_element()
 */
int utc_watchface_editable_add_design_element_n3(void)
{
	int ret;
	complication_candidates_list_h list;
	watchface_editable_highlight_h highlight;
	bundle *candidate;

	watchface_editable_candidates_list_create(&list);

	candidate = bundle_create();
	bundle_add_str(candidate, "COLOR", "RED");
	ret = watchface_editable_candidates_list_add(list, candidate);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_create(&highlight,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_set_geometry(highlight,
			100, 100, 30, 30);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_add_design_element(NULL, 0, 0, list, highlight, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

static void _update_requested_cb(const watchface_editable_h handle,
			int selected_idx,
			const watchface_editable_edit_state_e state,
			void *user_data)
{
	normal_exit_no_returnval(0);
}

static int _request_edit_with_design_elements(
		watchface_editable_container_h ed_con_h,
		watchface_editable_update_requested_cb update_cb) {
	int ret;
	complication_candidates_list_h list;
	bundle *candidate1;
	bundle *candidate2;
	watchface_editable_highlight_h highlight;

	ret = watchface_editable_candidates_list_create(&list);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	candidate1 = bundle_create();
	assert_with_exit(candidate1);
	bundle_add_str(candidate1, "COLOR", "RED");
	ret = watchface_editable_candidates_list_add(list, candidate1);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	candidate2 = bundle_create();
	assert_with_exit(candidate2);
	bundle_add_str(candidate2, "COLOR", "BLUE");
	ret = watchface_editable_candidates_list_add(list, candidate2);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_create(&highlight,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_set_geometry(highlight,
			GEO_X, GEO_Y, GEO_W, GEO_H);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_add_design_element(ed_con_h, 0, 0, list,
			highlight, "Color");
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_request_edit(ed_con_h, update_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	bundle_free(candidate1);
	bundle_free(candidate2);
	watchface_editable_candidates_list_destroy(list);

	return ret;
}

static void _design_element_on_edit_ready(
		watchface_editable_container_h ed_con_h,
		const char *editor_appid,
		void *user_data) {
	int ret;
	ret = _request_edit_with_design_elements(ed_con_h, _update_requested_cb);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
}

/**
 * @testcase utc_watchface_editable_add_design_element_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_editable_add_design_element()
 */
int utc_watchface_editable_add_design_element_p(void)
{
	int ret;

	ret = watchface_editable_add_edit_ready_cb(_design_element_on_edit_ready, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	_run_editor_app();

	return 0;
}

/**
 * @testcase utc_watchface_editable_add_complication_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_add_complication()
 */
int utc_watchface_editable_add_complication_n1(void)
{
	int ret;
	int editable_id = 0;
	complication_h comp;
	watchface_editable_highlight_h highlight;

	ret = watchface_editable_highlight_create(&highlight,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_set_geometry(highlight,
			100, 100, 30, 30);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_create(0, "org.tizen.sample_provider",
		WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
		WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
		WATCHFACE_COMPLICATION_EVENT_TAP, &comp);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_add_complication(NULL, editable_id, comp, highlight);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_add_complication_n2
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_add_complication()
 */
int utc_watchface_editable_add_complication_n2(void)
{
	int ret;
	int editable_id = 0;
	watchface_editable_highlight_h highlight;

	//_run_editor_app();

	ret = watchface_editable_highlight_create(&highlight,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_set_geometry(highlight,
			100, 100, 30, 30);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_add_complication(NULL, editable_id, NULL, highlight);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

static void _request_edit_with_complication(
		const watchface_editable_h handle,
		int selected_idx,
		const watchface_editable_edit_state_e state,
		void *user_data)
{
	char *user_data_char = (char *)user_data;

	assert_eq_with_exit_no_returnval(user_data_char, __check_user_data);
	normal_exit_no_returnval(0);
}

static void _add_complication_on_edit_ready(watchface_editable_container_h ed_con_h,
		const char *editor_appid,
		void *user_data) {
	int ret;
	int editable_id = 1;
	complication_h comp;
	watchface_editable_highlight_h highlight;
	char *user_data_char = (char *)user_data;

	assert_eq_with_exit_no_returnval(user_data_char, __check_user_data);

	ret = watchface_editable_highlight_create(&highlight,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_set_geometry(highlight,
			100, 100, 30, 30);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_create(1, PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_EVENT_TAP, &comp);

	ret = watchface_editable_add_complication(ed_con_h, editable_id, comp, highlight);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_request_edit(ed_con_h, _request_edit_with_complication, __check_user_data);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
}

/**
 * @testcase utc_watchface_editable_add_complication_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_editable_add_complication()
 */
int utc_watchface_editable_add_complication_p(void)
{
	int ret;

	ret = watchface_editable_add_edit_ready_cb(_add_complication_on_edit_ready, __check_user_data);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	_run_editor_app();

	return 0;
}

/**
 * @testcase utc_watchface_editable_request_edit_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_request_edit()
 */
int utc_watchface_editable_request_edit_n1(void)
{
	int ret;

	ret = watchface_editable_request_edit(NULL, _update_requested_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_request_edit_n2
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_request_edit()
 */
int utc_watchface_editable_request_edit_n2(void)
{
	int ret;

	ret = watchface_editable_request_edit(NULL, NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}


static void _request_edit_on_edit_ready(watchface_editable_container_h ed_con_h,
		const char *editor_appid,
		void *user_data) {
	int ret;
	complication_h comp;
	watchface_editable_highlight_h highlight;

	ret = watchface_editable_highlight_create(&highlight,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_set_geometry(highlight,
			100, 100, 30, 30);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_complication_create(0, "org.tizen.sample_provider",
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_EVENT_TAP, &comp);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_add_complication(ed_con_h, 0, comp, highlight);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_request_edit(ed_con_h, _update_requested_cb, NULL);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	normal_exit_no_returnval(ret);
}

/**
 * @testcase utc_watchface_editable_request_edit_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_editable_request_edit()
 */
int utc_watchface_editable_request_edit_p(void)
{
	int ret;

	ret = watchface_editable_add_edit_ready_cb(_request_edit_on_edit_ready, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	_run_editor_app();

	return 0;
}
/**
 * @testcase utc_watchface_editable_add_edit_ready_cb_n
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_add_edit_ready_cb()
 */
int utc_watchface_editable_add_edit_ready_cb_n(void)
{
	int ret;

	ret = watchface_editable_add_edit_ready_cb(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_add_edit_ready_cb_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_editable_add_edit_ready_cb()
 */
int utc_watchface_editable_add_edit_ready_cb_p(void)
{
	int ret;

	ret = watchface_editable_add_edit_ready_cb(_edit_ready_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_remove_edit_ready_cb(_edit_ready_cb);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_remove_edit_ready_cb_n
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_remove_edit_ready_cb()
 */
int utc_watchface_editable_remove_edit_ready_cb_n(void)
{
	int ret;

	ret = watchface_editable_remove_edit_ready_cb(NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_remove_edit_ready_cb_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_editable_remove_edit_ready_cb()
 */
int utc_watchface_editable_remove_edit_ready_cb_p(void)
{
	int ret;

	ret = watchface_editable_add_edit_ready_cb(_edit_ready_cb, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_remove_edit_ready_cb(_edit_ready_cb);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_get_editable_name_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_get_editable_name()
 */
int utc_watchface_editable_get_editable_name_n1(void)
{
	int ret;
	char *editable_name;

	ret = watchface_editable_get_editable_name(NULL, &editable_name);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_get_editable_name_n2
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_get_editable_name()
 */
int utc_watchface_editable_get_editable_name_n2(void)
{
	int ret;

	ret = watchface_editable_get_editable_name(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

static void _editable_name_update_requested_cb(const watchface_editable_h handle,
			int selected_idx,
			const watchface_editable_edit_state_e state,
			void *user_data)
{
	int ret;
	char *editable_name = NULL;

	ret = watchface_editable_get_editable_name(handle, &editable_name);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	assert_neq_with_exit_no_returnval(editable_name, NULL);
	free(editable_name);

	normal_exit_no_returnval(ret);
}

static void _editable_name_on_edit_ready(
		watchface_editable_container_h ed_con_h,
		const char *editor_appid,
		void *user_data) {
	int ret;
	ret = _request_edit_with_design_elements(
			ed_con_h, _editable_name_update_requested_cb);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
}

/**
 * @testcase utc_watchface_editable_get_editable_name_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_editable_get_editable_name()
 */
int utc_watchface_editable_get_editable_name_p(void)
{
	int ret;

	ret = watchface_editable_add_edit_ready_cb(_editable_name_on_edit_ready, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	_run_editor_app();

	return 0;
}

/**
 * @testcase utc_watchface_editable_set_editable_name_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_set_editable_name()
 */
int utc_watchface_editable_set_editable_name_n1(void)
{
	int ret;

	ret = watchface_editable_set_editable_name(NULL, "Editor");
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_set_editable_name_n2
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_set_editable_name()
 */
int utc_watchface_editable_set_editable_name_n2(void)
{
	int ret;

	ret = watchface_editable_set_editable_name(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}


static void _editable_set_name_update_requested_cb(const watchface_editable_h handle,
			int selected_idx,
			const watchface_editable_edit_state_e state,
			void *user_data)
{
	int ret;

	ret = watchface_editable_set_editable_name(handle, "TEST");
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	normal_exit_no_returnval(ret);
}

static void _editable_set_name_on_edit_ready(
		watchface_editable_container_h ed_con_h,
		const char *editor_appid,
		void *user_data) {
	int ret;
	ret = _request_edit_with_design_elements(
			ed_con_h, _editable_set_name_update_requested_cb);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
}

/**
 * @testcase utc_watchface_editable_set_editable_name_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_editable_set_editable_name()
 */
int utc_watchface_editable_set_editable_name_p(void)
{
	int ret;

	ret = watchface_editable_add_edit_ready_cb(_editable_set_name_on_edit_ready, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	_run_editor_app();

	return 0;
}

/**
 * @testcase utc_watchface_editable_get_nth_data_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_get_nth_data()
 */
int utc_watchface_editable_get_nth_data_n1(void)
{
	int ret;
	bundle *data = NULL;

	ret = watchface_editable_get_nth_data(NULL, 0, &data);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_get_nth_data_n2
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_get_nth_data()
 */
int utc_watchface_editable_get_nth_data_n2(void)
{
	int ret;

	//_run_editor_app();

	ret = watchface_editable_get_nth_data(NULL, 0, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}


static void _get_nth_update_requested_cb(const watchface_editable_h handle,
			int selected_idx,
			const watchface_editable_edit_state_e state,
			void *user_data)
{
	int ret;
	int n = 0;
	bundle *data = NULL;

	ret = watchface_editable_get_nth_data(handle, n, &data);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	assert_neq_with_exit_no_returnval(data, NULL);
	bundle_free(data);

	normal_exit_no_returnval(ret);
}

static void _get_nth_on_edit_ready(
		watchface_editable_container_h ed_con_h,
		const char *editor_appid,
		void *user_data) {
	int ret;
	ret = _request_edit_with_design_elements(
			ed_con_h, _get_nth_update_requested_cb);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
}

/**
 * @testcase utc_watchface_editable_get_nth_data_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_editable_get_nth_data()
 */
int utc_watchface_editable_get_nth_data_p(void)
{
	int ret;

	ret = watchface_editable_add_edit_ready_cb(_get_nth_on_edit_ready, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	_run_editor_app();

	return 0;
}

/**
 * @testcase utc_watchface_editable_get_current_data_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_get_current_data()
 */
int utc_watchface_editable_get_current_data_n1(void)
{
	int ret;
	bundle *data = NULL;

	ret = watchface_editable_get_current_data(NULL, &data);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_get_current_data_n2
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_get_current_data()
 */
int utc_watchface_editable_get_current_data_n2(void)
{
	int ret;

	ret = watchface_editable_get_current_data(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

static void _get_cur_data_update_requested_cb(const watchface_editable_h handle,
			int selected_idx,
			const watchface_editable_edit_state_e state,
			void *user_data)
{
	int ret;
	bundle *data = NULL;

	ret = watchface_editable_get_current_data(handle, &data);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	assert_neq_with_exit_no_returnval(data, NULL);
	bundle_free(data);

	normal_exit_no_returnval(ret);
}

static void _get_cur_data_on_edit_ready(
		watchface_editable_container_h ed_con_h,
		const char *editor_appid,
		void *user_data) {
	int ret;
	ret = _request_edit_with_design_elements(
			ed_con_h, _get_cur_data_update_requested_cb);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
}

/**
 * @testcase utc_watchface_editable_get_current_data_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_editable_get_current_data()
 */
int utc_watchface_editable_get_current_data_p(void)
{
	int ret;

	ret = watchface_editable_add_edit_ready_cb(_get_cur_data_on_edit_ready, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	_run_editor_app();

	return 0;
}

/**
 * @testcase utc_watchface_editable_get_current_data_idx_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_get_current_data_idx()
 */
int utc_watchface_editable_get_current_data_idx_n1(void)
{
	int ret;
	int idx = 0;

	ret = watchface_editable_get_current_data_idx(NULL, &idx);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_get_current_data_idx_n2
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_get_current_data_idx()
 */
int utc_watchface_editable_get_current_data_idx_n2(void)
{
	int ret;

	ret = watchface_editable_get_current_data_idx(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

static void _get_cur_data_idx_update_requested_cb(const watchface_editable_h handle,
			int selected_idx,
			const watchface_editable_edit_state_e state,
			void *user_data)
{
	int ret;
	int idx;

	ret = watchface_editable_get_current_data_idx(handle, &idx);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	normal_exit_no_returnval(ret);
}

static void _get_cur_data_idx_on_edit_ready(
		watchface_editable_container_h ed_con_h,
		const char *editor_appid,
		void *user_data) {
	int ret;
	ret = _request_edit_with_design_elements(
			ed_con_h, _get_cur_data_idx_update_requested_cb);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
}

/**
 * @testcase utc_watchface_editable_get_current_data_idx_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_editable_get_current_data_idx()
 */
int utc_watchface_editable_get_current_data_idx_p(void)
{
	int ret;

	ret = watchface_editable_add_edit_ready_cb(_get_cur_data_idx_on_edit_ready, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	_run_editor_app();

	return 0;
}

/**
 * @testcase utc_watchface_editable_get_editable_id_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_get_editable_id()
 */
int utc_watchface_editable_get_editable_id_n1(void)
{
	int ret;
	int editable_id;

	ret = watchface_editable_get_editable_id(NULL, &editable_id);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_get_editable_id_n2
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_get_editable_id()
 */
int utc_watchface_editable_get_editable_id_n2(void)
{
	int ret;

	ret = watchface_editable_get_editable_id(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}


static void _get_editable_id_update_requested_cb(const watchface_editable_h handle,
			int selected_idx,
			const watchface_editable_edit_state_e state,
			void *user_data)
{
	int ret;
	int id;

	ret = watchface_editable_get_editable_id(handle, &id);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	normal_exit_no_returnval(ret);
}

static void _get_editable_id_on_edit_ready(
		watchface_editable_container_h ed_con_h,
		const char *editor_appid,
		void *user_data) {
	int ret;
	ret = _request_edit_with_design_elements(
			ed_con_h, _get_editable_id_update_requested_cb);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
}

/**
 * @testcase utc_watchface_editable_get_editable_id_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_editable_get_editable_id()
 */
int utc_watchface_editable_get_editable_id_p(void)
{
	int ret;

	ret = watchface_editable_add_edit_ready_cb(_get_editable_id_on_edit_ready, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	_run_editor_app();

	return 0;
}

/**
 * @testcase utc_watchface_editable_get_highlight_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_get_highlight()
 */
int utc_watchface_editable_get_highlight_n1(void)
{
	int ret;
	watchface_editable_highlight_h highlight;

	ret = watchface_editable_get_highlight(NULL, &highlight);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_get_highlight_n2
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_get_highlight()
 */
int utc_watchface_editable_get_highlight_n2(void)
{
	int ret;

	ret = watchface_editable_get_highlight(NULL, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}


static void _get_highlight_update_requested_cb(const watchface_editable_h handle,
			int selected_idx,
			const watchface_editable_edit_state_e state,
			void *user_data)
{
	int ret;
	watchface_editable_highlight_h highlight;
	int x;
	int y;
	int w;
	int h;

	ret = watchface_editable_get_highlight(handle, &highlight);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_get_geometry(highlight, &x, &y, &w, &h);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	watchface_editable_highlight_destroy(highlight);

	assert_eq_with_exit_no_returnval(x, GEO_X);
	assert_eq_with_exit_no_returnval(y, GEO_Y);
	assert_eq_with_exit_no_returnval(h, GEO_H);
	assert_eq_with_exit_no_returnval(w, GEO_W);

	normal_exit_no_returnval(ret);
}

static void _get_highlight_on_edit_ready(
		watchface_editable_container_h ed_con_h,
		const char *editor_appid,
		void *user_data) {
	int ret;
	ret = _request_edit_with_design_elements(
			ed_con_h, _get_highlight_update_requested_cb);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
}

/**
 * @testcase utc_watchface_editable_get_highlight_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_editable_get_highlight()
 */
int utc_watchface_editable_get_highlight_p(void)
{
	int ret;

	ret = watchface_editable_add_edit_ready_cb(_get_highlight_on_edit_ready, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	_run_editor_app();

	return 0;

}

/**
 * @testcase utc_watchface_editable_load_current_data_n
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_load_current_data()
 */
int utc_watchface_editable_load_current_data_n(void)
{
	int ret;
	int edit_id = 1;

	ret = watchface_editable_load_current_data(edit_id, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

static void _load_current_data_update_requested_cb(const watchface_editable_h handle,
			int selected_idx,
			const watchface_editable_edit_state_e state,
			void *user_data)
{
	int ret;
	bundle *selected_data = NULL;
	int edit_id;

	if (state == WATCHFACE_EDITABLE_EDIT_STATE_COMPLETE) {
		watchface_editable_get_editable_id(handle, &edit_id);
		ret = watchface_editable_load_current_data(edit_id, &selected_data);
		assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

		if (selected_data)
			bundle_free(selected_data);

		normal_exit_no_returnval(ret);
	}
}

static void _load_current_data_on_edit_ready(
		watchface_editable_container_h ed_con_h,
		const char *editor_appid,
		void *user_data) {
	int ret;
	ret = _request_edit_with_design_elements(
			ed_con_h, _load_current_data_update_requested_cb);
	assert_eq_with_exit_no_returnval(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
}

/**
 * @testcase utc_watchface_editable_load_current_data_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_editable_load_current_data()
 */
int utc_watchface_editable_load_current_data_p(void)
{
	int ret;

	ret = watchface_editable_add_edit_ready_cb(_load_current_data_on_edit_ready, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);
	_run_editor_app();

	return 0;
}

/**
 * @testcase utc_watchface_editable_highlight_create_n
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_highlight_create()
 */
int utc_watchface_editable_highlight_create_n(void)
{
	int ret;

	ret = watchface_editable_highlight_create(NULL,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_highlight_create_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_editable_highlight_create()
 */
int utc_watchface_editable_highlight_create_p(void)
{
	int ret;
	watchface_editable_highlight_h handle;

	ret = watchface_editable_highlight_create(&handle,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	watchface_editable_highlight_destroy(handle);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_highlight_destroy_n
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_highlight_destroy()
 */
int utc_watchface_editable_highlight_destroy_n(void)
{
	int ret;

	ret = watchface_editable_highlight_destroy(NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_highlight_destroy_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_editable_highlight_destroy()
 */
int utc_watchface_editable_highlight_destroy_p(void)
{
	int ret;
	watchface_editable_highlight_h handle;

	ret = watchface_editable_highlight_create(&handle,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_destroy(handle);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_highlight_set_geometry_n
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_highlight_set_geometry()
 */
int utc_watchface_editable_highlight_set_geometry_n(void)
{
	int ret;

	ret = watchface_editable_highlight_set_geometry(NULL, 0, 0, 0, 0);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_highlight_set_geometry_p
 * @since_tizen 5.0
 * @description Positive test case of watchface_editable_highlight_set_geometry()
 */
int utc_watchface_editable_highlight_set_geometry_p(void)
{
	int ret;
	watchface_editable_highlight_h handle;

	ret = watchface_editable_highlight_create(&handle,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_set_geometry(handle, 100, 100, 30, 30);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	watchface_editable_highlight_destroy(handle);

	normal_exit(0);
}


/**
 * @testcase utc_watchface_editable_highlight_get_geometry_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_highlight_get_geometry()
 */
int utc_watchface_editable_highlight_get_geometry_n1(void)
{
	int ret;
	int x;
	int y;
	int w;
	int h;

	ret = watchface_editable_highlight_get_geometry(NULL, &x, &y, &w, &h);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_highlight_get_geometry_n2
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_highlight_get_geometry()
 */
int utc_watchface_editable_highlight_get_geometry_n2(void)
{
	int ret;
	int y;
	int w;
	int h;
	watchface_editable_highlight_h handle;

	ret = watchface_editable_highlight_create(&handle,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_get_geometry(handle, NULL, &y, &w, &h);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_highlight_get_geometry_n3
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_highlight_get_geometry()
 */
int utc_watchface_editable_highlight_get_geometry_n3(void)
{
	int ret;
	int x;
	int w;
	int h;
	watchface_editable_highlight_h handle;

	ret = watchface_editable_highlight_create(&handle,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_get_geometry(handle, &x, NULL, &w, &h);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_highlight_get_geometry_n4
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_highlight_get_geometry()
 */
int utc_watchface_editable_highlight_get_geometry_n4(void)
{
	int ret;
	int x;
	int y;
	int h;
	watchface_editable_highlight_h handle;

	ret = watchface_editable_highlight_create(&handle,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_get_geometry(handle, &x, &y, NULL, &h);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_highlight_get_geometry_n5
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_highlight_get_geometry()
 */
int utc_watchface_editable_highlight_get_geometry_n5(void)
{
	int ret;
	int x;
	int y;
	int w;
	watchface_editable_highlight_h handle;

	ret = watchface_editable_highlight_create(&handle,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_get_geometry(handle, &x, &y, &w, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_highlight_get_geometry_p
 * @since_tizen 5.0
 * @description Postive test case of watchface_editable_highlight_get_geometry()
 */
int utc_watchface_editable_highlight_get_geometry_p(void)
{
	int ret;
	int x;
	int y;
	int w;
	int h;
	watchface_editable_highlight_h handle;

	ret = watchface_editable_highlight_create(&handle,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_set_geometry(handle, 100, 100, 30, 30);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_get_geometry(handle, &x, &y, &w, &h);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	watchface_editable_highlight_destroy(handle);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_highlight_set_shape_type_p
 * @since_tizen 5.0
 * @description Postive test case of watchface_editable_highlight_set_shape_type()
 */
int utc_watchface_editable_highlight_set_shape_type_p(void)
{
	int ret;
	watchface_editable_highlight_h handle;

	ret = watchface_editable_highlight_create(&handle,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_set_shape_type(handle, WATCHFACE_EDITABLE_SHAPE_TYPE_RECT);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	watchface_editable_highlight_destroy(handle);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_highlight_set_shape_type_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_highlight_set_shape_type()
 */
int utc_watchface_editable_highlight_set_shape_type_n1(void)
{
	int ret;

	ret = watchface_editable_highlight_set_shape_type(NULL, WATCHFACE_EDITABLE_SHAPE_TYPE_RECT);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_highlight_set_shape_type_n2
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_highlight_set_shape_type()
 */
int utc_watchface_editable_highlight_set_shape_type_n2(void)
{
	int ret;
	watchface_editable_highlight_h handle;

	ret = watchface_editable_highlight_create(&handle,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_set_shape_type(handle, -1);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	watchface_editable_highlight_destroy(handle);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_highlight_get_shape_type_p
 * @since_tizen 5.0
 * @description Postive test case of watchface_editable_highlight_get_shape_type()
 */
int utc_watchface_editable_highlight_get_shape_type_p(void)
{
	int ret;
	watchface_editable_highlight_h handle;
	watchface_editable_shape_type_e shape;

	ret = watchface_editable_highlight_create(&handle,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_set_shape_type(handle, WATCHFACE_EDITABLE_SHAPE_TYPE_RECT);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_get_shape_type(handle, &shape);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	watchface_editable_highlight_destroy(handle);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_highlight_get_shape_type_n1
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_highlight_get_shape_type()
 */
int utc_watchface_editable_highlight_get_shape_type_n1(void)
{
	int ret;
	watchface_editable_shape_type_e shape;

	ret = watchface_editable_highlight_get_shape_type(NULL, &shape);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_watchface_editable_highlight_get_shape_type_n2
 * @since_tizen 5.0
 * @description Negative test case of watchface_editable_highlight_get_shape_type()
 */
int utc_watchface_editable_highlight_get_shape_type_n2(void)
{
	int ret;
	watchface_editable_highlight_h handle;

	ret = watchface_editable_highlight_create(&handle,
			WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_NONE);

	ret = watchface_editable_highlight_get_shape_type(handle, NULL);
	assert_eq_with_exit(ret, WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER);

	watchface_editable_highlight_destroy(handle);

	normal_exit(0);
}
