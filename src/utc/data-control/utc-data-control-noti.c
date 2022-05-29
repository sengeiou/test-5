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
#include "utc-data-control.h"
#include "tct_app_common.h"
#include <data_control.h>
#include <data_control_sql.h>
#include <data_control_noti.h>
#include <bundle.h>
#include <string.h>
#include <dlog.h>

#define PROVIDER_ID "http://datacontrolnotiprovider.com/datacontrol/provider/datacontrolnotiprovider"
#define SQL_DATA_ID "Dictionary"

#define DISTRUST_PROVIDER_ID "http://distrust_provider.com/datacontrol/provider/distrust_provider"

static data_control_h __provider;
static data_control_h __distrust_provider;
static char *__result_cb_user_data = "user1";
static char *__noti_cb_user_data = "user2";
static int __cb_id1;
static int __cb_id2;
static int __tc_num;

static void __data_changed_cb1(data_control_h provider,
	data_control_data_change_type_e type,
	bundle *data,
	void *user_data)
{
	dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] __data_changed_cb1", __FUNCTION__, __LINE__);
	normal_exit(0);
}

static void __data_changed_cb2(data_control_h provider,
	data_control_data_change_type_e type,
	bundle *data,
	void *user_data)
{
}

static void __add_data_changed_callback_result_cb(
		data_control_h provider,
		data_control_error_e result,
		int callback_id,
		void *user_data)
{
	int req_id;
	bundle *b = bundle_create();
	bundle_add_str(b, "WORD", "'test'");
	bundle_add_str(b, "WORD_DESC", "'test desc'");

	data_control_sql_insert(__provider, b, &req_id);
	bundle_free(b);
	dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] __add_data_changed_callback_result_cb", __FUNCTION__, __LINE__);
}

static void __insert_response_cb(int request_id, data_control_h provider, long long inserted_row_id, bool provider_result, const char *error, void *user_data)
{
}

static void __delete_response_cb(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
}

static void __select_response_cb(int request_id, data_control_h provider, result_set_cursor cursor,
		bool provider_result, const char *error, void *user_data)
{
}

static void __update_response_cb(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
}

/**
 * @function		utc_data_control_sql_startup
 * @description		Called before each test
 * @parameter		NA
 * @return		NA
 */
void utc_data_control_noti_startup(void)
{
	int result = 0;
	result = data_control_sql_create(&__provider);
	if (result)
		printf("startup error");

	result = data_control_sql_set_provider_id(__provider, PROVIDER_ID);
	if (result)
		printf("set provider id error");

	result = data_control_sql_set_data_id(__provider, SQL_DATA_ID);
	if (result)
		printf("set data id error");

	result = data_control_sql_create(&__distrust_provider);
	if (result)
		printf("startup error");

	result = data_control_sql_set_provider_id(__distrust_provider, DISTRUST_PROVIDER_ID);
	if (result)
		printf("set provider id error");

	result = data_control_sql_set_data_id(__distrust_provider, SQL_DATA_ID);
	if (result)
		printf("set data id error");

	TCT_UTCCheckInstalledApp(2, "org.tizen.datacontrolnotiprovider",
			"org.tizen.datacontrolnotiprovider",
			"org.tizen.distrust_provider");
}

/**
 * @function		utc_data_control_sql_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return		NA
 */
void utc_data_control_noti_cleanup(void)
{
}

static void insert_response_cb(int request_id, data_control_h provider, long long inserted_row_id, bool provider_result, const char *error, void *user_data)
{
}

/**
 * @testcase		utc_data_control_add_data_change_cb_p
 * @since_tizen		3.0
 * @description		Add data changed callback
 * @scenario		Calls data_control_add_data_change_cb()
 */
int utc_data_control_add_data_change_cb_p(void)
{
	int result;
	data_control_sql_response_cb sql_callback;
	sql_callback.insert_cb = insert_response_cb;

	result = data_control_sql_register_response_cb(__provider, &sql_callback, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_add_data_change_cb(__provider,
				__data_changed_cb1,
				__noti_cb_user_data,
				__add_data_changed_callback_result_cb,
				__result_cb_user_data,
				&__cb_id1);

	dlog_print(DLOG_ERROR, "NativeTCT", "utc_data_control_add_data_change_cb_p @@@@@@@");
	return 0;
}

/**
 * @testcase		utc_data_control_add_data_change_cb_n01
 * @since_tizen		3.0
 * @description		Add data changed callback in intended error case
 * @scenario		Calls data_control_add_data_change_cb() with invalid parameter
 */
int utc_data_control_add_data_change_cb_n01(void)
{
	int result = 0;
	result = result = data_control_add_data_change_cb(NULL,
				__data_changed_cb1,
				__noti_cb_user_data,
				__add_data_changed_callback_result_cb,
				__result_cb_user_data,
				&__cb_id1);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_add_data_change_cb_n02
 * @since_tizen		3.0
 * @description		Add data changed callback in intended error case
 * @scenario		Calls data_control_add_data_change_cb() with invalid parameter
 */
int utc_data_control_add_data_change_cb_n02(void)
{
	int result = 0;
	result = result = data_control_add_data_change_cb(__provider,
				NULL,
				__noti_cb_user_data,
				__add_data_changed_callback_result_cb,
				__result_cb_user_data,
				&__cb_id1);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_add_data_change_cb_n03
 * @since_tizen		3.0
 * @description		Add data changed callback in intended error case
 * @scenario		Calls data_control_add_data_change_cb() with invalid parameter
 */
int utc_data_control_add_data_change_cb_n03(void)
{
	int result = 0;
	result = result = data_control_add_data_change_cb(__provider,
				__data_changed_cb1,
				__noti_cb_user_data,
				__add_data_changed_callback_result_cb,
				__result_cb_user_data,
				NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_add_data_change_cb_n04
 * @since_tizen     4.0
 * @description     Add data changed callback in intended error case
 * @scenario        Calls data_control_add_data_change_cb() with untrusted provider
 */
int utc_data_control_add_data_change_cb_n04(void)
{
	int result = 0;
	result = data_control_add_data_change_cb(__distrust_provider,
				__data_changed_cb1,
				__noti_cb_user_data,
				__add_data_changed_callback_result_cb,
				__result_cb_user_data,
				&__cb_id1);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_PERMISSION_DENIED);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_remove_data_change_cb_p
 * @since_tizen		3.0
 * @description		Remove data changed callback
 * @scenario		Calls data_control_remove_data_change_cb() after add data change callback
 */
int utc_data_control_remove_data_change_cb_p(void)
{
	int result;
	result = data_control_add_data_change_cb(__provider,
				__data_changed_cb1,
				__noti_cb_user_data,
				__add_data_changed_callback_result_cb,
				__result_cb_user_data,
				&__cb_id1);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_remove_data_change_cb(__provider, __cb_id1);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_remove_data_change_cb_n01
 * @since_tizen		3.0
 * @description		Remove data changed callback in intended error case
 * @scenario		Calls data_control_remove_data_change_cb() with invalid parameter
 */
int utc_data_control_remove_data_change_cb_n01(void)
{
	int result = 0;
	result = data_control_remove_data_change_cb(NULL, __cb_id1);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_remove_data_change_cb_n02
 * @since_tizen		3.0
 * @description		Remove data changed callback in intended error case
 * @scenario		Calls data_control_remove_data_change_cb() with invalid parameter
 */
int utc_data_control_remove_data_change_cb_n02(void)
{
	int result = 0;
	result = data_control_remove_data_change_cb(__provider, -1);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase        utc_data_control_remove_data_change_cb_n03
 * @since_tizen     4.0
 * @description     Remove data changed callback in intended error case
 * @scenario        Calls data_control_remove_data_change_cb() with untrusted provider
 */
int utc_data_control_remove_data_change_cb_n03(void)
{
	int result = 0;
	result = data_control_remove_data_change_cb(__distrust_provider, 2);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_PERMISSION_DENIED);
	normal_exit(0);
	return 0;
}
