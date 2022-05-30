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
#include "assert.h"
#include <app.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <libintl.h>

#include <notification_ex.h>

#include "utc-notification.h"

#define GROUP_NOTI_ID "test_group"

noti_ex_reporter_h reporter_handle__ = NULL;
noti_ex_manager_h manager_handle__ = NULL;
void utc_notification_ex_reporter_startup(void)
{
}

void utc_notification_ex_reporter_cleanup(void)
{
	int req_id;

	noti_ex_reporter_delete_all(reporter_handle__, &req_id);
}

void _reporter_events_event_cb(noti_ex_reporter_h handle, noti_ex_event_info_h info,
		noti_ex_item_h *items, int cnt, void *data) {
}

void _reporter_events_error_cb(noti_ex_reporter_h handle,
		noti_ex_error_e error, int req_id, void *data) {
}

/**
 * @testcase utc_noti_ex_reporter_create_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_reporter_create()
 */
int utc_noti_ex_reporter_create_p(void)
{
	int ret;
	noti_ex_reporter_h handle;
	noti_ex_reporter_events_s ev = {0};

	ev.event = _reporter_events_event_cb;
	ev.error = _reporter_events_error_cb;
	ret = noti_ex_reporter_create(&handle, ev, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_reporter_create_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_reporter_create()
 */
int utc_noti_ex_reporter_create_n(void)
{
	int ret;
	noti_ex_reporter_events_s ev = {0};

	ret = noti_ex_reporter_create(NULL, ev, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_reporter_destroy_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_reporter_destroy()
 */
int utc_noti_ex_reporter_destroy_p(void)
{
	int ret;
	noti_ex_reporter_h handle;
	noti_ex_reporter_events_s ev = {0};

	ev.event = _reporter_events_event_cb;
	ev.error = _reporter_events_error_cb;
	ret = noti_ex_reporter_create(&handle, ev, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_reporter_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_reporter_destroy_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_reporter_destroy()
 */
int utc_noti_ex_reporter_destroy_n(void)
{
	int ret;

	ret = noti_ex_reporter_destroy(NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

static void __create_noti(noti_ex_item_h **noti_list) {
	if (reporter_handle__ == NULL) {
		noti_ex_reporter_events_s ev = {0};
		ev.error = _reporter_events_error_cb;
		noti_ex_reporter_create(&reporter_handle__, ev, NULL);
	}
	int req_id;
	noti_ex_reporter_delete_all(reporter_handle__, &req_id);
	noti_ex_item_h *list = (noti_ex_item_h*)calloc(2, sizeof(noti_ex_item_h));
	noti_ex_item_h group_item = NULL;
	noti_ex_item_h child_item = NULL;
	noti_ex_item_group_create(&group_item, GROUP_NOTI_ID);
	noti_ex_item_button_create(&child_item, "btn1", "test1");
	noti_ex_item_group_add_child(group_item, child_item);
	noti_ex_item_button_create(&child_item, "btn2", "test2");
	noti_ex_item_group_add_child(group_item, child_item);
	list[0] = group_item;

	noti_ex_item_group_create(&group_item, "group_id2");
	noti_ex_item_button_create(&child_item, "btn3", "test3");
	noti_ex_item_group_add_child(group_item, child_item);

	noti_ex_item_button_create(&child_item, "btn4", "test4");
	noti_ex_item_group_add_child(group_item, child_item);
	list[1] = group_item;

	*noti_list = list;
}

/**
 * @testcase utc_noti_ex_reporter_post_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_reporter_post()
 */
int utc_noti_ex_reporter_post_p(void)
{
	noti_ex_item_h *noti_list;
	int req_id;

	__create_noti(&noti_list);

	int ret = noti_ex_reporter_post(reporter_handle__, noti_list[0], &req_id);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_reporter_post_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_reporter_post()
 */
int utc_noti_ex_reporter_post_n(void)
{
	int req_id;
	int ret = noti_ex_reporter_post(reporter_handle__, NULL, &req_id);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_reporter_post_list_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_reporter_post_list()
 */
int utc_noti_ex_reporter_post_list_p(void)
{
	noti_ex_item_h *noti_list;
	int req_id;

	__create_noti(&noti_list);

	int ret = noti_ex_reporter_post_list(reporter_handle__, noti_list, 2, &req_id);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_reporter_post_list_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_reporter_post_list()
 */
int utc_noti_ex_reporter_post_list_n(void)
{
	int req_id;
	int ret = noti_ex_reporter_post_list(reporter_handle__, NULL, 2, &req_id);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_reporter_update_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_reporter_update()
 */
int utc_noti_ex_reporter_update_p(void)
{
	noti_ex_item_h *noti_list;
	noti_ex_item_h item;
	int req_id;

	__create_noti(&noti_list);

	int ret = noti_ex_reporter_post(reporter_handle__, noti_list[0], &req_id);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_reporter_find_by_root_id(reporter_handle__, GROUP_NOTI_ID, &item);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_reporter_update(reporter_handle__, item, &req_id);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_reporter_update_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_reporter_update()
 */
int utc_noti_ex_reporter_update_n(void)
{
	int req_id;
	int ret = noti_ex_reporter_update(reporter_handle__, NULL, &req_id);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_reporter_delete_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_reporter_delete()
 */
int utc_noti_ex_reporter_delete_p(void)
{
	noti_ex_item_h *noti_list;
	noti_ex_item_h item;
	int req_id;

	__create_noti(&noti_list);

	int ret = noti_ex_reporter_post(reporter_handle__, noti_list[0], &req_id);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_reporter_find_by_root_id(reporter_handle__, GROUP_NOTI_ID, &item);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_reporter_delete(reporter_handle__, item, &req_id);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_reporter_delete_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_reporter_delete()
 */
int utc_noti_ex_reporter_delete_n(void)
{
	int req_id;
	int ret = noti_ex_reporter_delete(reporter_handle__, NULL, &req_id);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_reporter_delete_all_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_reporter_delete_all()
 */
int utc_noti_ex_reporter_delete_all_p(void)
{
	noti_ex_item_h *noti_list;
	int req_id;

	__create_noti(&noti_list);

	int ret = noti_ex_reporter_post(reporter_handle__, noti_list[0], &req_id);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_reporter_delete_all(reporter_handle__, &req_id);
	assert_eq_with_exit_no_returnval(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_reporter_delete_all_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_reporter_delete_all()
 */
int utc_noti_ex_reporter_delete_all_n(void)
{
	int req_id;
	int ret = noti_ex_reporter_delete_all(NULL, &req_id);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_reporter_find_by_root_id_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_reporter_find_by_root_id()
 */
int utc_noti_ex_reporter_find_by_root_id_p(void)
{
	noti_ex_item_h *noti_list;
	noti_ex_item_h item;
	int req_id;

	__create_noti(&noti_list);

	int ret = noti_ex_reporter_post(reporter_handle__, noti_list[0], &req_id);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_reporter_find_by_root_id(reporter_handle__, GROUP_NOTI_ID, &item);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_reporter_find_by_root_id_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_reporter_find_by_root_id()
 */
int utc_noti_ex_reporter_find_by_root_id_n(void)
{
	int ret = noti_ex_reporter_find_by_root_id(NULL, GROUP_NOTI_ID, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}
