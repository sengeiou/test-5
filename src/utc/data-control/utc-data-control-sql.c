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
#include <data_control.h>
#include <data_control_sql.h>
#include <bundle.h>
#include <dlog.h>
#include <string.h>
#include "tct_app_common.h"

#define PROVIDER_ID "http://datacontrolprovider.com/datacontrol/provider/datacontrolprovider"
#define PROVIDER_ID2 "http://tizen.org/datacontrol/provider/datacontrolprovider2"
#define DISTRUST_PROVIDER_ID "http://distrust_provider.com/datacontrol/provider/distrust_provider"
#define SQL_DATA_ID "Dictionary"
#define SQL_DATA_ID2 "SqlRepository2"
#define COLUMN_CNT 3

static data_control_h g_provider;
static data_control_h distrust_provider;
const char* insert_row_list[2][2];
char *__column_list[3];

static long long row_id;
static long long last_id;

static const char *test_key = "wrong_key";
static data_control_h g_provider;
static data_control_h g_provider_for_bind;
const char *__where = "WORD = 'test'";
const char *__updated_where = "WORD = 'test2'";
const char *__order = "WORD ASC";

static int g_provider_handle_id;
static int g_provider_handle_id_for_bind;

static int check_handle_id = 0;
static int check_handle_id_for_bind = 0;

static int check_count_of_call = 0;
static char bulk_test[10];

/**
 * @function		utc_data_control_sql_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_data_control_sql_startup(void)
{
	int result = 0;

	result = data_control_sql_create(&g_provider);
	if (result)
		printf("startup error");

	insert_row_list[0][0] = "'word_0'";
	insert_row_list[1][0] = "'word_1'";
	insert_row_list[0][1] = "'word_0 initially'";
	insert_row_list[1][1] = "'word_1 initially'";

	__column_list[0] = "WORD";
	__column_list[1] = "WORD_DESC";
	__column_list[2] = "WORD_NUM";

	result = data_control_sql_set_provider_id(g_provider, PROVIDER_ID);
	if (result)
		printf("set provider id error");

	result = data_control_sql_set_data_id(g_provider, SQL_DATA_ID);
	if (result)
		printf("set data id error");

	result = data_control_sql_create(&distrust_provider);
	if (result)
		printf("startup error");

	result = data_control_sql_set_provider_id(distrust_provider, DISTRUST_PROVIDER_ID);
	if (result)
		printf("set provider id error");

	result = data_control_sql_set_data_id(distrust_provider, SQL_DATA_ID);
	if(result)
		printf("set data id error");

	result = data_control_sql_create(&g_provider_for_bind);
	if (result)
		printf("create error");

	result = data_control_sql_set_provider_id(g_provider_for_bind, PROVIDER_ID);
	if (result)
		printf("set provider id error");

	result = data_control_sql_set_data_id(g_provider_for_bind, SQL_DATA_ID);
	if (result)
		printf("set data id error");

	result = data_control_sql_get_handle_id(g_provider_for_bind,
			&g_provider_handle_id_for_bind);
	if (result)
		printf("get handle id error");


	TCT_UTCCheckInstalledApp(2, "org.tizen.datacontrolmapprovider", "org.tizen.datacontrolprovider");
}

/**
 * @function		utc_data_control_sql_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_data_control_sql_cleanup(void)
{
}

static void sql_bulk_insert_response_cb(int request_id, data_control_h provider, data_control_bulk_result_data_h bulk_results,
		bool provider_result, const char *error, void *user_data)
{
	int i;
	int result;
	int count;

	dlog_print(DLOG_INFO, "NativeTCT", "sql_bulk_insert_response_cb ");

	if (provider_result) {
		dlog_print(DLOG_INFO, "NativeTCT", "%d bulk insert operation is successful", request_id);
		data_control_bulk_result_data_get_count(bulk_results, &count);
		dlog_print(DLOG_INFO, "NativeTCT", "bulk insert operation is successful count %d", count);

		assert_eq_with_exit_no_returnval(__correct_row_cnt, count);
		for (i = 0; i < count; i++) {
			data_control_bulk_result_data_get_result_data(bulk_results, i, NULL, &result);
			dlog_print(DLOG_INFO, "NativeTCT", "BULK insert result ###### %d", result);
			assert_eq_with_exit_no_returnval(result, DATA_CONTROL_ERROR_NONE);
		}
	} else {
		dlog_print(DLOG_ERROR, "NativeTCT",
				"The bulk insert operation for the request %d is failed. error message: %s ", request_id, error);
		normal_exit(1);
	}
	normal_exit(0);
}

static void insert_response_cb(int request_id, data_control_h provider, long long inserted_row_id, bool provider_result, const char *error, void *user_data)
{
	int result = 0;

	printf("insert_response_cb \n");
	printf("next operation : %s\n", __next_operation);

	if (strcmp(__next_operation, "select") == 0) {

		__next_operation = "delete";
		result = data_control_sql_select(g_provider, __column_list, COLUMN_CNT, __where, __order, &request_id);
		assert_eq_with_exit_no_returnval(result, DATA_CONTROL_ERROR_NONE);

	} else if (strcmp(__next_operation, "delete") == 0) {

		__next_operation = "select";
		result = data_control_sql_delete(g_provider, __where, &request_id);
		assert_eq_with_exit_no_returnval(result, DATA_CONTROL_ERROR_NONE);

	} else if (strcmp(__next_operation, "update") == 0) {

		__correct_value = "test2";
		__correct_row_cnt = 1;
		__next_operation = "select";

		bundle *b = bundle_create();
		bundle_add_str(b, "WORD", "'test2'");
		result = data_control_sql_update(g_provider, b, __where, &request_id);
		bundle_free(b);

	} else if (strcmp(__next_operation, "insert_for_page_select") == 0) {

		__next_operation = "select_for_page_select";

		bundle *b = bundle_create();
		bundle_add_str(b, "WORD", "'test2'");
		bundle_add_str(b, "WORD_DESC", "'test description'");
		bundle_add_str(b, "WORD_NUM", "1");

		result = data_control_sql_insert(g_provider, b, &request_id);
		bundle_free(b);

	} else if (strcmp(__next_operation, "select_for_page_select") == 0) {

		__correct_value = "test2";
		__correct_row_cnt = 1;

		__next_operation = "delete";
		int count_per_page = 1;
		int page_number = 2;
		result = data_control_sql_select_with_page(g_provider, __column_list, COLUMN_CNT, NULL, __order, page_number, count_per_page, &request_id);
		assert_eq_with_exit_no_returnval(result, DATA_CONTROL_ERROR_NONE);

	} else {
		result = data_control_sql_destroy(g_provider);
		if(result) {
			printf("cleanup error");
		}
		normal_exit(0);
	}

}

static void delete_response_cb(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
	printf("delete_response_cb \n");
	printf("next operation : %s\n", __next_operation);

	int result = 0;

	if (strcmp(__next_operation, "select") == 0) {

		__correct_row_cnt = 0;
		__next_operation = "done";
		result = data_control_sql_select(g_provider, __column_list, COLUMN_CNT, __where, __order, &request_id);
		assert_eq_with_exit_no_returnval(result, DATA_CONTROL_ERROR_NONE);

	} else {
		result = data_control_sql_destroy(g_provider);
		if(result) {
			printf("cleanup error");
		}
		normal_exit(0);
	}

}

static void select_response_cb(int request_id, data_control_h provider, result_set_cursor cursor,
		bool provider_result, const char *error, void *user_data)
{

	printf("select_response_cb \n");
	printf("next operation : %s\n", __next_operation);

	bool is_valid_return = false;
	int result = 0;
	int row_cnt = 0;
	char col_name[32] = {0,};
	char buf[32] = {0,};
	data_control_sql_column_type_e type;
	int int_data;
	int index;
	double double_data;

	while (data_control_sql_step_next(cursor) == DATA_CONTROL_ERROR_NONE) {

		char word[32] = {0,};
		char word_desc[32] = {0,};
		long long word_number = -1;

		data_control_sql_get_text_data(cursor, 0, word);
		data_control_sql_get_text_data(cursor, 1, word_desc);
		data_control_sql_get_int64_data(cursor, 2, &word_number);

		row_cnt ++;

		if (strcmp(word, __correct_value) == 0) {
			is_valid_return = true;
		}
		printf("Word : %s, Word DESC : %s, Word NUM : %ld \n",
				word, word_desc, word_number);

	}
	printf("correct, row_cnt : [%d:%d]\n",
			__correct_row_cnt, row_cnt);

	data_control_sql_step_last(cursor);
	data_control_sql_step_previous(cursor);
	data_control_sql_step_first(cursor);

	for (index = 0; index < data_control_sql_get_column_count(cursor); index++) {
		data_control_sql_get_column_name(cursor, index, col_name);
		data_control_sql_get_column_item_size(cursor, index);
		data_control_sql_get_column_item_type(cursor, index, &type);
		data_control_sql_get_blob_data(cursor, index, buf, 10);
		data_control_sql_get_int_data(cursor, index, &int_data);
		data_control_sql_get_double_data(cursor, index, &double_data);
	}

	if (__correct_row_cnt != row_cnt) {
		is_valid_return = false;
	} else if (__correct_row_cnt == 0) {
		is_valid_return = true;
	}

	assert_eq_with_exit_no_returnval(is_valid_return, true);

	if (strcmp(__next_operation, "delete") == 0) {
		result = data_control_sql_delete(g_provider, NULL, &request_id);
		assert_eq_with_exit_no_returnval(result, DATA_CONTROL_ERROR_NONE);
	} else {
		result = data_control_sql_destroy(g_provider);
		if(result) {
			printf("cleanup error");
		}

		normal_exit(0);
	}

}

static void update_response_cb(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
	int result = 0;

	printf("update_response_cb \n");
	printf("next operation : %s\n", __next_operation);

	if (strcmp(__next_operation, "select") == 0) {
		__next_operation = "delete";
		result = data_control_sql_select(g_provider, __column_list, COLUMN_CNT, __updated_where, __order,
				&request_id);
		assert_eq_with_exit_no_returnval(result, DATA_CONTROL_ERROR_NONE);
	} else {
		result = data_control_sql_destroy(g_provider);
		if(result) {
			printf("cleanup error");
		}
		normal_exit(0);
	}
}

static void sql_bulk_insert_response_cb2(int request_id, data_control_h provider, data_control_bulk_result_data_h bulk_results,
		bool provider_result, const char *error, void *user_data)
{
	int temp_handle_id1;
	int result;

	char *temp_bind1_text = "bind1";
	char *temp_bind2_text = "bind2";
	char *temp_unbind_text = "unbind";

	dlog_print(DLOG_INFO, "NativeTCT", "bulk_test : %s", bulk_test);

	result = data_control_sql_get_handle_id(provider, &temp_handle_id1);
	if (result != DATA_CONTROL_ERROR_NONE)
		normal_exit(1);


	if (strcmp(bulk_test, temp_bind1_text) == 0) {
		if (temp_handle_id1 == g_provider_handle_id)
			check_handle_id = 1;

		if (temp_handle_id1 == g_provider_handle_id_for_bind)
			check_handle_id_for_bind = 1;

		if (check_handle_id && check_handle_id_for_bind)
			normal_exit(0);
	} else if (strcmp(bulk_test, temp_bind2_text) == 0) {
		if (temp_handle_id1 == g_provider_handle_id)
			check_count_of_call++;

		if (check_count_of_call > 1)
			normal_exit(0);
	} else if (strcmp(bulk_test, temp_unbind_text) == 0) {
		if (temp_handle_id1 == g_provider_handle_id)
			check_handle_id = 1;

		if (temp_handle_id1 == g_provider_handle_id_for_bind)
			normal_exit(1);

		if (check_handle_id)
			normal_exit(0);
	}
}


static void insert_response_cb2(int request_id, data_control_h provider, long long inserted_row_id, bool provider_result, const char *error, void *user_data)
{
	int result = 0;
	int temp_handle_id1;

	dlog_print(DLOG_INFO, "NativeTCT", "insert_response_cb ");

	result = data_control_sql_get_handle_id(provider, &temp_handle_id1);
	if (result != DATA_CONTROL_ERROR_NONE)
		normal_exit(1);

	dlog_print(DLOG_INFO, "NativeTCT", "temp_handle_id1 : %d ", temp_handle_id1);
	dlog_print(DLOG_INFO, "NativeTCT", "g_provider_handle_id : %d ", g_provider_handle_id);
	if (temp_handle_id1 == g_provider_handle_id)
		check_handle_id = 1;

	dlog_print(DLOG_INFO, "NativeTCT", "g_provider_handle_id : %d ", g_provider_handle_id_for_bind);

	if (temp_handle_id1 == g_provider_handle_id_for_bind)
		check_handle_id_for_bind = 1;

	if (check_handle_id && check_handle_id_for_bind)
		normal_exit(0);

}

static void delete_response_cb2(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
	dlog_print(DLOG_INFO, "NativeTCT", "delete_response_cb ");

	int temp_handle_id1;
	int result;

	result = data_control_sql_get_handle_id(provider, &temp_handle_id1);
	if (result != DATA_CONTROL_ERROR_NONE)
		normal_exit(1);

	if (temp_handle_id1 == g_provider_handle_id)
		check_handle_id = 1;

	if (temp_handle_id1 == g_provider_handle_id_for_bind)
		normal_exit(1);

	if (check_handle_id)
		normal_exit(0);
}

static void select_response_cb2(int request_id, data_control_h provider, result_set_cursor cursor,
		bool provider_result, const char *error, void *user_data)
{
	data_control_h temp_provider = (data_control_h)user_data;

	int handle_id1;
	int handle_id2;

	int result = data_control_sql_get_handle_id(provider, &handle_id1);
	if (result != DATA_CONTROL_ERROR_NONE)
		normal_exit(1);

	result = data_control_sql_get_handle_id(temp_provider, &handle_id2);
	if (result != DATA_CONTROL_ERROR_NONE)
		normal_exit(1);

	dlog_print(DLOG_INFO, "NativeTCT", "select_response_cb %d :: %d ",
			handle_id1, handle_id2);

	if (handle_id1 == handle_id2)
		check_count_of_call++;

	if (check_count_of_call == 2)
		normal_exit(0);
}

static void update_response_cb2(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
	dlog_print(DLOG_INFO, "NativeTCT", "update_response_cb ");

}

/**
 * @testcase		utc_data_control_sql_create_p
 * @since_tizen		2.3
 * @description		Create data control provider
 * @scenario		Calls data_control_sql_create() with the provider that want to be created
 * 					and calls data_control_sql_destory() to free the provider
 */
int utc_data_control_sql_create_p(void)
{
	data_control_h provider;
	int result = 0;

	result = data_control_sql_create(&provider);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_sql_destroy(provider);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_create_n
 * @since_tizen		2.3
 * @description		Create data control provider in intended error case.
 * @scenario		Calls data_control_sql_create() with invalid parameter
 */
int utc_data_control_sql_create_n(void)
{
	int result = 0;

	result = data_control_sql_create(NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	printf("utc_data_control_sql_create_n %d \n", result);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_destroy_p
 * @since_tizen		2.3
 * @description		Destroy data control provider
 * @scenario		Calls data_control_sql_create() to create provider and
 * 					calls data_control_sql_destory() to free the provider
 */
int utc_data_control_sql_destroy_p(void)
{
	data_control_h provider;
	int result = 0;

	result = data_control_sql_create(&provider);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	printf("utc_data_control_sql_destroy_p %d \n", result);

	result = data_control_sql_destroy(provider);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	printf("utc_data_control_sql_destroy_p %d \n", result);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_destroy_n
 * @since_tizen		2.3
 * @description		Destroy data control provider in intended error case
 * @scenario		Calls data_control_sql_destroy() with invalid parameter
 */
int utc_data_control_sql_destroy_n(void)
{
	int result = 0;

	result = data_control_sql_destroy(NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	printf("utc_data_control_sql_destroy_n %d \n", result);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_set_provider_id_p
 * @since_tizen		2.3
 * @description		Set data control provider id
 * @scenario		Calls data_control_sql_set_provider_id() with provider and PROVIDER_ID
 */
int utc_data_control_sql_set_provider_id_p(void)
{
	int result = 0;

	result = data_control_sql_set_provider_id(g_provider, PROVIDER_ID);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_set_provider_id_n
 * @since_tizen		2.3
 * @description		Set data control provider id in intended error case
 * @scenario		Calls data_control_sql_set_provider_id() with invalid parameter
 */
int utc_data_control_sql_set_provider_id_n(void)
{
	int result = 0;

	result = data_control_sql_set_provider_id(g_provider, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_get_provider_id_p
 * @since_tizen		2.3
 * @description		Get data control provider id
 * @scenario		Calls data_control_sql_set_provider_id() to set provider id and
 * 					calls data_control_sql_get_provider_id() to get provider id
 */
int utc_data_control_sql_get_provider_id_p(void)
{
	char *provider_id;
	int result = 0;

	result = data_control_sql_set_provider_id(g_provider, PROVIDER_ID);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_sql_get_provider_id(g_provider, &provider_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	assert(!strcmp(PROVIDER_ID, provider_id));

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_get_provider_id_n
 * @since_tizen		2.3
 * @description		Get data control provider id in intended error case
 * @scenario		Calls data_control_sql_set_provider_id() with invalid parameter
 */
int utc_data_control_sql_get_provider_id_n(void)
{
	int result = 0;

	result = data_control_sql_get_provider_id(g_provider, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_match_provider_id_p
 * @since_tizen		2.3
 * @description		Get provider id from data control provider and compare it with PROVIDER_ID parameter
 * @scenario		Calls data_control_sql_set_provider_id() to set provider id and
 * 					calls data_control_provider_match_provider_id() to compare
 */
int utc_data_control_provider_match_provider_id_p(void)
{
	bool result = false;
	int ret = 0;

	ret = data_control_sql_set_provider_id(g_provider, PROVIDER_ID);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);

	result = data_control_provider_match_provider_id(g_provider, PROVIDER_ID);
	assert_eq_with_exit(get_last_result(), DATA_CONTROL_ERROR_NONE);
	assert(result);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_match_provider_id_n01
 * @since_tizen		2.3
 * @description		Get provider id from data control provider and compare it with PROVIDER_ID parameter in intended error case
 * @scenario		Calls data_control_sql_set_provider_id() to set provider id and
 * 					calls data_control_provider_match_provider_id() with another provider id that's not set.
 */
int utc_data_control_provider_match_provider_id_n01(void)
{

	bool result = false;
	int ret = 0;

	ret = data_control_sql_set_provider_id(g_provider, PROVIDER_ID);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);

	result = data_control_provider_match_provider_id(g_provider, PROVIDER_ID2);
	assert_eq_with_exit(get_last_result(), DATA_CONTROL_ERROR_NONE);
	assert(!result);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_match_provider_id_n02
 * @since_tizen		2.3
 * @description		Get provider id from data control provider and compare it with PROVIDER_ID parameter in intended error case
 * @scenario		Calls data_control_provider_match_provider_id() with invalid parameter
 */
int utc_data_control_provider_match_provider_id_n02(void)
{

	bool result = false;
	int ret = 0;

	result = data_control_provider_match_provider_id(NULL, PROVIDER_ID2);
	assert_eq_with_exit(get_last_result(), DATA_CONTROL_ERROR_INVALID_PARAMETER);
	assert(!result);

	normal_exit(0);
	return 0;
}


/**
 * @testcase		utc_data_control_sql_set_data_id_p
 * @since_tizen		2.3
 * @description		Set data id into data control provider
 * @scenario		Calls data_control_provider_match_provider_id() with invalid parameter
 */
int utc_data_control_sql_set_data_id_p(void)
{
	int result = 0;

	result = data_control_sql_set_data_id(g_provider, SQL_DATA_ID);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_set_data_id_n
 * @since_tizen		2.3
 * @description		Set data id into data control provider in intented error case
 * @scenario		Calls data_control_sql_set_provider_id() with invalid parameter
 */
int utc_data_control_sql_set_data_id_n(void)
{
	int result = 0;

	result = data_control_sql_set_provider_id(g_provider, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_match_data_id_p
 * @since_tizen		2.3
 * @description		Get data id from data control provider and compare it with SQL_DATA_ID parameter
 * @scenario		Calls data_control_sql_set_data_id() to set data id and
 * 					calls data_control_provider_match_data_id() to compare
 */
int utc_data_control_provider_match_data_id_p(void)
{
	bool result = false;
	int ret = 0;

	ret = data_control_sql_set_provider_id(g_provider, PROVIDER_ID);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);

	ret = data_control_sql_set_data_id(g_provider, SQL_DATA_ID);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);

	result = data_control_provider_match_data_id(g_provider, SQL_DATA_ID);
	assert(result);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_match_data_id_n01
 * @since_tizen		2.3
 * @description		Get data id from data control provider and compare it with SQL_DATA_ID parameter in intended error case
 * @scenario		Calls data_control_sql_set_data_id() to set data id and
 * 					calls data_control_provider_match_data_id() with another data id that's not set
 */
int utc_data_control_provider_match_data_id_n01(void)
{
	bool result = false;
	int ret = 0;

	ret = data_control_sql_set_provider_id(g_provider, PROVIDER_ID);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);

	ret = data_control_sql_set_data_id(g_provider, SQL_DATA_ID);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);

	result = data_control_provider_match_data_id(g_provider, SQL_DATA_ID2);
	assert_eq_with_exit(get_last_result(), DATA_CONTROL_ERROR_NONE);
	assert(!result);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_match_data_id_n02
 * @since_tizen		2.3
 * @description		Get data id from data control provider and compare it with SQL_DATA_ID parameter in intended error case
 * @scenario		Calls data_control_provider_match_data_id() with invalid parameter
 */
int utc_data_control_provider_match_data_id_n02(void)
{
	bool result = false;
	int ret = 0;

	result = data_control_provider_match_data_id(NULL, SQL_DATA_ID2);
	assert_eq_with_exit(get_last_result(), DATA_CONTROL_ERROR_INVALID_PARAMETER);
	assert(!result);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_get_data_id_p
 * @since_tizen		2.3
 * @description		Get data id from data control provider
 * @scenario		Calls data_control_sql_get_data_id()
 */
int utc_data_control_sql_get_data_id_p(void)
{
	char *data_id;
	int result = 0;

	result = data_control_sql_set_data_id(g_provider, SQL_DATA_ID);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_sql_get_data_id(g_provider, &data_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	assert(!strcmp(data_id, SQL_DATA_ID));
	free(data_id);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_get_data_id_n
 * @since_tizen		2.3
 * @description		Get data id from data control provider in intended error case
 * @scenario		Calls data_control_sql_get_data_id() with invalid parameter
 */
int utc_data_control_sql_get_data_id_n(void)
{
	int result = 0;

	result = data_control_sql_set_data_id(g_provider, SQL_DATA_ID);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_sql_get_data_id(g_provider, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_register_response_cb_p
 * @since_tizen		2.3
 * @description		Registers response callback functions
 * @scenario		Calls data_control_sql_register_response_cb()
 */
int utc_data_control_sql_register_response_cb_p(void)
{
	int result = 0;
	data_control_sql_response_cb *sql_callback;

	sql_callback = (data_control_sql_response_cb *) malloc(sizeof(data_control_sql_response_cb));
	assert_neq_with_exit(sql_callback, NULL);

	sql_callback->insert_cb = insert_response_cb;
	sql_callback->delete_cb = delete_response_cb;
	sql_callback->update_cb = update_response_cb;
	sql_callback->select_cb = select_response_cb;

	result = data_control_sql_register_response_cb(g_provider, sql_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	free(sql_callback);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_register_response_cb_n
 * @since_tizen		2.3
 * @description		Registers response callback functions in intended error case
 * @scenario		Calls data_control_sql_register_response_cb() with invalid parameter
 */
int utc_data_control_sql_register_response_cb_n(void)
{
	int result = 0;

	result = data_control_sql_register_response_cb(g_provider, NULL, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_unregister_response_cb_p
 * @since_tizen		2.3
 * @description		Unregisters response callback function
 * @scenario		Calls data_control_sql_register_response_cb() to register callback functions and
 * 					calls data_control_sql_unregister_response_cb() to unregister callback functions
 */
int utc_data_control_sql_unregister_response_cb_p(void)
{
	data_control_sql_response_cb *sql_callback;
	int result = 0;

	sql_callback = (data_control_sql_response_cb *) malloc(sizeof(data_control_sql_response_cb));
	assert_neq_with_exit(sql_callback, NULL);

	sql_callback->insert_cb = insert_response_cb;
	sql_callback->delete_cb = delete_response_cb;
	sql_callback->update_cb = update_response_cb;
	sql_callback->select_cb = select_response_cb;

	result = data_control_sql_register_response_cb(g_provider, sql_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	result = data_control_sql_unregister_response_cb(g_provider);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	free(sql_callback);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_insert_p
 * @since_tizen		2.3
 * @description		Insert new rows in a table
 * @scenario		Calls data_control_sql_insert()
 */
int utc_data_control_sql_insert_p(void)
{

	int req_id;
	int result;

	bundle *b = bundle_create();
	bundle_add_str(b, "WORD", "'test'");
	bundle_add_str(b, "WORD_DESC", "'test description'");
	bundle_add_str(b, "WORD_NUM", "1");

	data_control_sql_response_cb *sql_callback;

	sql_callback = (data_control_sql_response_cb *) malloc(sizeof(data_control_sql_response_cb));
	assert_neq_with_exit(sql_callback, NULL);

	sql_callback->insert_cb = insert_response_cb;
	sql_callback->delete_cb = delete_response_cb;
	sql_callback->update_cb = update_response_cb;
	sql_callback->select_cb = select_response_cb;

	result = data_control_sql_register_response_cb(g_provider, sql_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	printf("utc_data_control_sql_insert_p \n");
	result = data_control_sql_insert(g_provider, b, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	bundle_free(b);

	__next_operation = "select";
	__correct_value = "test";
	__correct_row_cnt = 1;

	free(sql_callback);

	return 0;
}

/**
 * @testcase		utc_data_control_sql_insert_n1
 * @since_tizen		2.3
 * @description		Insert new rows in a table in intended error case
 * @scenario		Calls data_control_sql_insert() with invalid parameter
 */
int utc_data_control_sql_insert_n1(void)
{
	int result = 0;
	int req_id;

	result = data_control_sql_insert(NULL, NULL, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase        utc_data_control_sql_insert_n2
 * @since_tizen     4.0
 * @description     Insert new rows in a table in intended error case
 * @scenario        Calls data_control_sql_insert() with untrusted provider
 */
int utc_data_control_sql_insert_n2(void)
{
	int req_id;
	int result;

	bundle *b = bundle_create();
	bundle_add_str(b, "WORD", "'test'");
	bundle_add_str(b, "WORD_DESC", "'test description'");
	bundle_add_str(b, "WORD_NUM", "1");

	result = data_control_sql_insert(distrust_provider, b, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_PERMISSION_DENIED);

	bundle_free(b);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_update_p
 * @since_tizen		2.3
 * @description		Update values of a table
 * @scenario		Calls data_control_sql_insert() and set the next operation "update" then
 * 					data_control_sql_update() will be called from insert callback function.
 */
int utc_data_control_sql_update_p(void)
{

	int req_id;
	int result;

	bundle *b = bundle_create();
	bundle_add_str(b, "WORD", "'test'");
	bundle_add_str(b, "WORD_DESC", "'test description'");
	bundle_add_str(b, "WORD_NUM", "1");

	data_control_sql_response_cb *sql_callback;

	sql_callback = (data_control_sql_response_cb *) malloc(sizeof(data_control_sql_response_cb));
	assert_neq_with_exit(sql_callback, NULL);

	sql_callback->insert_cb = insert_response_cb;
	sql_callback->delete_cb = delete_response_cb;
	sql_callback->update_cb = update_response_cb;
	sql_callback->select_cb = select_response_cb;

	result = data_control_sql_register_response_cb(g_provider, sql_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	result = data_control_sql_insert(g_provider, b, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	bundle_free(b);

	__next_operation = "update";
	__correct_value = "test";
	__correct_row_cnt = 1;

	free(sql_callback);

	return 0;
}

/**
 * @testcase		utc_data_control_sql_update_n1
 * @since_tizen		2.3
 * @description		Update values of a table in intended error case
 * @scenario		Calls data_control_sql_update() with invalid parameter
 */
int utc_data_control_sql_update_n1(void)
{
	int result = 0;
	int req_id;

	result = data_control_sql_update(NULL, NULL, NULL, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase        utc_data_control_sql_update_n2
 * @since_tizen     4.0
 * @description     Update values of a table in intended error case
 * @scenario        Calls data_control_sql_update() with untrusted provider
 */
int utc_data_control_sql_update_n2(void)
{
	int req_id;
	int result;

	bundle *b = bundle_create();
	bundle_add_str(b, "WORD", "'test'");
	bundle_add_str(b, "WORD_DESC", "'test description'");
	bundle_add_str(b, "WORD_NUM", "1");

	result = data_control_sql_update(distrust_provider, b, __where, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_PERMISSION_DENIED);

	bundle_free(b);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_select_p
 * @since_tizen		2.3
 * @description		Select the specified columns to be queried
 * @scenario		Calls data_control_sql_select()
 */
int utc_data_control_sql_select_p(void)
{

	int req_id;
	int result;

	data_control_sql_response_cb *sql_callback;

	sql_callback = (data_control_sql_response_cb *) malloc(sizeof(data_control_sql_response_cb));
	assert_neq_with_exit(sql_callback, NULL);

	sql_callback->insert_cb = insert_response_cb;
	sql_callback->delete_cb = delete_response_cb;
	sql_callback->update_cb = update_response_cb;
	sql_callback->select_cb = select_response_cb;

	result = data_control_sql_register_response_cb(g_provider, sql_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	__next_operation = "done";
	__correct_row_cnt = 0;

	result = data_control_sql_select(g_provider, __column_list, COLUMN_CNT, __where, __order, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	free(sql_callback);

	return 0;

}

/**
 * @testcase		utc_data_control_sql_select_n1
 * @since_tizen		2.3
 * @description		Select the specified columns to be queried in intended error case
 * @scenario		Calls data_control_sql_select() with invalid parameter
 */
int utc_data_control_sql_select_n1(void)
{
	int result = 0;
	int req_id;

	result = data_control_sql_select(NULL, NULL, 5, NULL, NULL, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase        utc_data_control_sql_select_n2
 * @since_tizen     4.0
 * @description     Select the specified columns to be queried in intended error case
 * @scenario        Calls data_control_sql_select() with untrusted provider
 */
int utc_data_control_sql_select_n2(void)
{
	int req_id;
	int result;

	result = data_control_sql_select(distrust_provider, __column_list, COLUMN_CNT, __where, __order, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_PERMISSION_DENIED);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_select_with_page_p
 * @since_tizen		2.3
 * @description		Select the specified columns to be queried
 * @scenario		Calls data_control_sql_select_with_page()
 */
int utc_data_control_sql_select_with_page_p(void)
{

	int req_id;
	int result;

	data_control_sql_response_cb *sql_callback;

	sql_callback = (data_control_sql_response_cb *) malloc(sizeof(data_control_sql_response_cb));
	assert_neq_with_exit(sql_callback, NULL);

	sql_callback->insert_cb = insert_response_cb;
	sql_callback->delete_cb = delete_response_cb;
	sql_callback->update_cb = update_response_cb;
	sql_callback->select_cb = select_response_cb;

	result = data_control_sql_register_response_cb(g_provider, sql_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	__next_operation = "done";
	__correct_row_cnt = 0;

	result = data_control_sql_select_with_page(g_provider, __column_list, COLUMN_CNT, __where, __order,
			1, 5, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	free(sql_callback);

	return 0;

}

/**
 * @testcase		utc_data_control_sql_select_with_page_p2
 * @since_tizen		2.3
 * @description		Select the specified columns to be queried
 * @scenario		Calls data_control_sql_insert() then
 * 					data_control_sql_select_with_page() will be called from insert callback function
 */
int utc_data_control_sql_select_with_page_p2(void)
{

	int req_id;
	int result;

	bundle *b = bundle_create();
	bundle_add_str(b, "WORD", "'test'");
	bundle_add_str(b, "WORD_DESC", "'test description'");
	bundle_add_str(b, "WORD_NUM", "1");

	data_control_sql_response_cb *sql_callback;

	sql_callback = (data_control_sql_response_cb *) malloc(sizeof(data_control_sql_response_cb));
	assert_neq_with_exit(sql_callback, NULL);

	sql_callback->insert_cb = insert_response_cb;
	sql_callback->delete_cb = delete_response_cb;
	sql_callback->update_cb = update_response_cb;
	sql_callback->select_cb = select_response_cb;

	result = data_control_sql_register_response_cb(g_provider, sql_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	printf("utc_data_control_sql_insert_p \n");
	result = data_control_sql_insert(g_provider, b, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	bundle_free(b);

	__next_operation = "insert_for_page_select";

	free(sql_callback);

	return 0;
}


/**
 * @testcase		utc_data_control_sql_select_with_page_n1
 * @since_tizen		2.3
 * @description		Select the specified columns to be queried in intended error case
 * @scenario		Calls data_control_sql_select_with_page() with invalid paramter
 */
int utc_data_control_sql_select_with_page_n1(void)
{
	int result = 0;
	int req_id;

	result = data_control_sql_select_with_page(NULL, NULL, 5, NULL, "WORD ASC", 1, 5, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase        utc_data_control_sql_select_with_page_n2
 * @since_tizen     4.0
 * @description     Select the specified columns to be queried in intended error case
 * @scenario        Calls data_control_sql_select_with_page() with untrusted provider
 */
int utc_data_control_sql_select_with_page_n2(void)
{
	int req_id;
	int result;

	result = data_control_sql_select_with_page(distrust_provider, __column_list, COLUMN_CNT, __where, __order,
			1, 5, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_PERMISSION_DENIED);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_delete_p
 * @since_tizen		2.3
 * @description		Delete rows of a table
 * @scenario		Calls data_control_sql_insert() and set next operation "delete" then
 * 					data_control_sql_delete() will be called from insert callback function
 */
int utc_data_control_sql_delete_p(void)
{

	int req_id;
	int result;

	bundle *b = bundle_create();
	bundle_add_str(b, "WORD", "'test'");
	bundle_add_str(b, "WORD_DESC", "'test description'");
	bundle_add_str(b, "WORD_NUM", "1");

	data_control_sql_response_cb *sql_callback;

	sql_callback = (data_control_sql_response_cb *) malloc(sizeof(data_control_sql_response_cb));
	assert_neq_with_exit(sql_callback, NULL);

	sql_callback->insert_cb = insert_response_cb;
	sql_callback->delete_cb = delete_response_cb;
	sql_callback->update_cb = update_response_cb;
	sql_callback->select_cb = select_response_cb;

	result = data_control_sql_register_response_cb(g_provider, sql_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	result = data_control_sql_insert(g_provider, b, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	bundle_free(b);

	__next_operation = "delete";

	free(sql_callback);

	return 0;
}

/**
 * @testcase		utc_data_control_sql_delete_n1
 * @since_tizen		2.3
 * @description		Delete rows of a table in intended error case
 * @scenario		Calls data_control_sql_delete() with invalid paramter
 */
int utc_data_control_sql_delete_n1(void)
{
	int result = 0;
	int req_id = 0;

	result = data_control_sql_delete(NULL, NULL, &req_id);
	printf("utc_data_control_sql_delete_n %d \n", result);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase        utc_data_control_sql_delete_n2
 * @since_tizen     4.0
 * @description     Delete rows of a table in intended error case
 * @scenario        Calls data_control_sql_delete() with untrusted provider
 */
int utc_data_control_sql_delete_n2(void)
{
	int req_id;
	int result;

	result = data_control_sql_delete(distrust_provider, NULL, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_PERMISSION_DENIED);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_get_blob_data_n
 * @since_tizen		2.3
 * @description		Get blob type data in intended error case
 * @scenario		Calls data_control_sql_delete() with invalid paramter
 */
int utc_data_control_sql_get_blob_data_n(void)
{
	int result = 0;

	result = data_control_sql_get_blob_data(NULL, 0, NULL, 0);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_get_column_count_n
 * @since_tizen		2.3
 * @description		Gets the numbers of columns for this cursor in intended error case
 * @scenario		Calls data_control_sql_get_column_count() with invalid paramter
 */
int utc_data_control_sql_get_column_count_n(void)
{
	int result = 0;

	result = data_control_sql_get_column_count(NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_get_column_item_size_n
 * @since_tizen		2.3
 * @description		Gets column item size in intended error case
 * @scenario		Calls data_control_sql_get_column_item_size() with invalid parameter
 */
int utc_data_control_sql_get_column_item_size_n(void)
{
	int result = 0;

	result = data_control_sql_get_column_item_size(NULL, 0);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_get_column_item_type_n
 * @since_tizen		2.3
 * @description		Gets column item type in intended error case
 * @scenario		Calls data_control_sql_get_column_item_type() with invalid parameter
 */
int utc_data_control_sql_get_column_item_type_n(void)
{
	int result = 0;

	result = data_control_sql_get_column_item_type(NULL, 0, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_get_column_name_n
 * @since_tizen		2.3
 * @description		Gets column name in intended error case
 * @scenario		Calls data_control_sql_get_column_name() with invalid parameter
 */
int utc_data_control_sql_get_column_name_n(void)
{
	int result = 0;

	result = data_control_sql_get_column_name(NULL, 0, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_get_double_data_n
 * @since_tizen		2.3
 * @description		Gets double type data in inteded error case
 * @scenario		Calls data_control_sql_get_double_data() with invalid parameter
 */
int utc_data_control_sql_get_double_data_n(void)
{
	int result = 0;

	result = data_control_sql_get_double_data(NULL, 0, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}


/**
 * @testcase		utc_data_control_sql_get_int_data_n
 * @since_tizen		2.3
 * @description		Gets int type data in intended error case
 * @scenario		Calls data_control_sql_get_int_data() with invalid parameter
 */
int utc_data_control_sql_get_int_data_n(void)
{
	int result = 0;

	result = data_control_sql_get_int_data(NULL, 0, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}


/**
 * @testcase		utc_data_control_sql_get_int64_data_n
 * @since_tizen		2.3
 * @description		Gets int64 type data in intended error case
 * @scenario		Calls data_control_sql_get_int64_data() with invalid parameter
 */
int utc_data_control_sql_get_int64_data_n(void)
{
	int result = 0;

	result = data_control_sql_get_int64_data(NULL, 0, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}


/**
 * @testcase		utc_data_control_sql_get_text_data_n
 * @since_tizen		2.3
 * @description		Gets text type data in intended error case
 * @scenario		Calls data_control_sql_get_text_data() with invalid parameter
 */
int utc_data_control_sql_get_text_data_n(void)
{
	int result = 0;

	result = data_control_sql_get_text_data(NULL, 0, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_step_first_n
 * @since_tizen		2.3
 * @description		Move cursor to first in intended error case
 * @scenario		Calls data_control_sql_step_first() with invalid parameter
 */
int utc_data_control_sql_step_first_n(void)
{
	int result = 0;

	result = data_control_sql_step_first(NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}
/**
 * @testcase		utc_data_control_sql_step_last_n
 * @since_tizen		2.3
 * @description		Move cursor to last in intended error case
 * @scenario		Calls data_control_sql_step_last() with invalid parameter
 */
int utc_data_control_sql_step_last_n(void)
{
	int result = 0;

	result = data_control_sql_step_last(NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}


/**
 * @testcase		utc_data_control_sql_step_next_n
 * @since_tizen		2.3
 * @description		Move cursor to next in intended error case
 * @scenario		Calls data_control_sql_step_next() with invalid parameter
 */
int utc_data_control_sql_step_next_n(void)
{
	int result = 0;

	result = data_control_sql_step_next(NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}


/**
 * @testcase		utc_data_control_sql_step_previous_n
 * @since_tizen		2.3
 * @description		Move cursor to previous in intended error case
 * @scenario		Calls data_control_sql_step_previous() with invalid parameter
 */
int utc_data_control_sql_step_previous_n(void)
{
	int result = 0;

	result = data_control_sql_step_previous(NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_insert_bulk_data_p
 * @since_tizen		3.0
 * @description		Insert new rows in a table
 * @scenario		Calls data_control_sql_insert_bulk_data()
 */
int utc_data_control_sql_insert_bulk_data_p(void)
{

	data_control_bulk_data_h bulk_data_h;
	bundle *b1;
	bundle *b2;
	int req_id;
	int result;
	int count;

	result = data_control_sql_register_insert_bulk_data_response_cb(g_provider, sql_bulk_insert_response_cb, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	b1 = bundle_create();
	bundle_add_str(b1, "WORD", "'bulk test'");
	bundle_add_str(b1, "WORD_DESC", "'bulk test description'");
	b2 = bundle_create();
	bundle_add_str(b2, "WORD", "'bulk test'");
	bundle_add_str(b2, "WORD_DESC", "'bulk test description'");

	data_control_bulk_data_create(&bulk_data_h);
	data_control_bulk_data_add(bulk_data_h, b1);
	data_control_bulk_data_add(bulk_data_h, b2);

	data_control_bulk_data_get_count(bulk_data_h, &count);
	dlog_print(DLOG_INFO, "NativeTCT", "bulk insert count %d", count);

	__correct_row_cnt = count;
	result = data_control_sql_insert_bulk_data(g_provider, bulk_data_h, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	data_control_bulk_data_destroy(bulk_data_h);
	bundle_free(b1);
	bundle_free(b2);

	return 0;
}

/**
 * @testcase		utc_data_control_sql_insert_bulk_data_n1
 * @since_tizen		3.0
 * @description		Insert new rows in a table in intended error case
 * @scenario		Calls data_control_sql_insert_bulk_data() with invalid parameter
 */
int utc_data_control_sql_insert_bulk_data_n1(void)
{
	int result = 0;
	int req_id;

	result = data_control_sql_insert_bulk_data(NULL, NULL, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase        utc_data_control_sql_insert_bulk_data_n2
 * @since_tizen     4.0
 * @description     Insert new rows in a table in intended error case
 * @scenario        Calls data_control_sql_insert_bulk_data() with untrusted provider
 */
int utc_data_control_sql_insert_bulk_data_n2(void)
{
	int result = 0;
	int req_id;
	data_control_bulk_data_h bulk_data_h;

	data_control_bulk_data_create(&bulk_data_h);
	result = data_control_sql_insert_bulk_data(distrust_provider, NULL, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_PERMISSION_DENIED);

	data_control_bulk_data_destroy(bulk_data_h);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_register_insert_bulk_data_response_cb_p
 * @since_tizen		3.0
 * @description		Registers insert bulk data response callback
 * @scenario		Calls data_control_sql_register_insert_bulk_data_response_cb()
 */
int utc_data_control_sql_register_insert_bulk_data_response_cb_p(void)
{
	int result;

	result = data_control_sql_register_insert_bulk_data_response_cb(g_provider, sql_bulk_insert_response_cb, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_register_insert_bulk_data_response_cb_n
 * @since_tizen		3.0
 * @description		Registers insert bulk data response callbackin intended error case
 * @scenario		Calls data_control_sql_register_insert_bulk_data_response_cb() with invalid parameter
 */
int utc_data_control_sql_register_insert_bulk_data_response_cb_n(void)
{
	int result = 0;
	int req_id;

	result = data_control_sql_register_insert_bulk_data_response_cb(NULL, NULL, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_unregister_insert_bulk_data_response_cb_p
 * @since_tizen		3.0
 * @description		Unregisters insert bulk data response callback
 * @scenario		Calls data_control_sql_unregister_insert_bulk_data_response_cb()
 */
int utc_data_control_sql_unregister_insert_bulk_data_response_cb_p(void)
{
	int result;

	result = data_control_sql_register_insert_bulk_data_response_cb(g_provider, sql_bulk_insert_response_cb, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_sql_unregister_insert_bulk_data_response_cb(g_provider);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_unregister_insert_bulk_data_response_cb_n
 * @since_tizen		3.0
 * @description		Unregisters insert bulk data response callbackin intended error case
 * @scenario		Calls data_control_sql_unregister_insert_bulk_data_response_cb() with invalid parameter
 */
int utc_data_control_sql_unregister_insert_bulk_data_response_cb_n(void)
{
	int result = 0;
	int req_id;
	result = data_control_sql_unregister_insert_bulk_data_response_cb(g_provider);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_get_handle_id_p
 * @since_tizen		4.0
 * @description		Gets the handle id
 * @scenario		Calls data_control_sql_get_handle_id() to get handle id
 */
int utc_data_control_sql_get_handle_id_p(void)
{
	int result = 0;

	result = data_control_sql_get_handle_id(g_provider, &g_provider_handle_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_get_handle_id_n
 * @since_tizen		4.0
 * @description		Gets the handle id in intended error case
 * @scenario		Calls data_control_sql_get_handle_id() to get handle id
 * 					with invalid parameter
 */
int utc_data_control_sql_get_handle_id_n(void)
{
	int result = 0;

	result = data_control_sql_get_handle_id(NULL, &g_provider_handle_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_bind_response_cb_p1
 * @since_tizen		4.0
 * @description		Binds callback functions
 * @scenario		Calls data_control_sql_bind_response_cb()
 */
int utc_data_control_sql_bind_response_cb_p1(void)
{
	int result = 0;
	int req_id;

	bundle *b = bundle_create();
	bundle_add_str(b, "WORD", "'test'");
	bundle_add_str(b, "WORD_DESC", "'test description'");
	bundle_add_str(b, "WORD_NUM", "1");

	data_control_sql_response_cb *sql_callback;

	sql_callback = (data_control_sql_response_cb *) malloc(
			sizeof(data_control_sql_response_cb));
	assert_neq_with_exit(sql_callback, NULL);

	sql_callback->insert_cb = insert_response_cb2;
	sql_callback->select_cb = select_response_cb2;
	sql_callback->update_cb = update_response_cb2;
	sql_callback->delete_cb = delete_response_cb2;

	result = data_control_sql_get_handle_id(g_provider, &g_provider_handle_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	result = data_control_sql_bind_response_cb(g_provider, sql_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	result = data_control_sql_bind_response_cb(g_provider_for_bind,
			sql_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	result = data_control_sql_insert(g_provider, b, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	result = data_control_sql_insert(g_provider_for_bind, b, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	bundle_free(b);
	free(sql_callback);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_bind_response_cb_p2
 * @since_tizen		4.0
 * @description		Binds callback functions
 * @scenario		Calls data_control_sql_bind_response_cb()
 */
int utc_data_control_sql_bind_response_cb_p2(void)
{
	int result = 0;
	int req_id;

	bundle *b = bundle_create();
	bundle_add_str(b, "WORD", "'test'");
	bundle_add_str(b, "WORD_DESC", "'test description'");
	bundle_add_str(b, "WORD_NUM", "1");

	data_control_sql_response_cb *sql_callback;

	sql_callback = (data_control_sql_response_cb *) malloc(
			sizeof(data_control_sql_response_cb));
	assert_neq_with_exit(sql_callback, NULL);

	sql_callback->insert_cb = insert_response_cb2;
	sql_callback->select_cb = select_response_cb2;
	sql_callback->update_cb = update_response_cb2;
	sql_callback->delete_cb = delete_response_cb2;

	result = data_control_sql_get_handle_id(g_provider, &g_provider_handle_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	result = data_control_sql_register_response_cb(g_provider, sql_callback,
			NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	result = data_control_sql_bind_response_cb(g_provider_for_bind,
			sql_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	result = data_control_sql_insert(g_provider, b, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	result = data_control_sql_insert(g_provider_for_bind, b, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	bundle_free(b);
	free(sql_callback);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_bind_response_cb_p3
 * @since_tizen		4.0
 * @description		Binds callback functions
 * @scenario		Calls data_control_sql_bind_response_cb()
 */
int utc_data_control_sql_bind_response_cb_p3(void)
{
	int result = 0;
	int req_id;

	bundle *b = bundle_create();
	bundle_add_str(b, "WORD", "'test'");
	bundle_add_str(b, "WORD_DESC", "'test description'");
	bundle_add_str(b, "WORD_NUM", "1");

	data_control_sql_response_cb *sql_callback;

	sql_callback = (data_control_sql_response_cb *) malloc(
			sizeof(data_control_sql_response_cb));
	assert_neq_with_exit(sql_callback, NULL);

	sql_callback->insert_cb = insert_response_cb2;
	sql_callback->select_cb = select_response_cb2;
	sql_callback->update_cb = update_response_cb2;
	sql_callback->delete_cb = delete_response_cb2;

	result = data_control_sql_register_response_cb(g_provider_for_bind,
			sql_callback, g_provider_for_bind);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	result = data_control_sql_bind_response_cb(g_provider_for_bind,
			sql_callback, g_provider_for_bind);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	result = data_control_sql_select(g_provider_for_bind, __column_list,
			COLUMN_CNT, __where, __order, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	bundle_free(b);
	free(sql_callback);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_bind_response_cb_n
 * @since_tizen		4.0
 * @description		Binds callback functions
 * @scenario		Calls data_control_sql_bind_response_cb() with invalid parameter
 */
int utc_data_control_sql_bind_response_cb_n(void)
{
	int result = 0;

	result = data_control_sql_bind_response_cb(g_provider, NULL, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_unbind_response_cb_p
 * @since_tizen		4.0
 * @description		Unbinds callback functions
 * @scenario		Calls data_control_sql_unbind_response_cb()
 */
int utc_data_control_sql_unbind_response_cb_p(void)
{
	int result = 0;
	int req_id;

	data_control_sql_response_cb *sql_callback;

	sql_callback = (data_control_sql_response_cb *) malloc(
			sizeof(data_control_sql_response_cb));
	assert_neq_with_exit(sql_callback, NULL);

	sql_callback->insert_cb = insert_response_cb2;
	sql_callback->select_cb = select_response_cb2;
	sql_callback->update_cb = update_response_cb2;
	sql_callback->delete_cb = delete_response_cb2;

	result = data_control_sql_get_handle_id(g_provider, &g_provider_handle_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	result = data_control_sql_bind_response_cb(g_provider, sql_callback,
			NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	result = data_control_sql_bind_response_cb(g_provider_for_bind,
			sql_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	result = data_control_sql_unbind_response_cb(g_provider_for_bind);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	result = data_control_sql_delete(g_provider_for_bind, __where, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	result = data_control_sql_delete(g_provider, __where, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, sql_callback);

	free(sql_callback);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_unbind_response_cb_n
 * @since_tizen		4.0
 * @description		Unbinds callback functions
 * @scenario		Calls data_control_sql_unbind_response_cb() with invalid parameter
 */
int utc_data_control_sql_unbind_response_cb_n(void)
{
	int result = 0;

	result = data_control_sql_unbind_response_cb( NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_bind_insert_bulk_data_response_cb_p1
 * @since_tizen		4.0
 * @description		Binds the value
 * @scenario		Calls data_control_sql_bind_insert_bulk_data_response_cb()
 */
int utc_data_control_sql_bind_insert_bulk_data_response_cb_p1(void)
{
	int req_id;
	data_control_bulk_data_h bulk_data_h;
	bundle *b1;
	int count;
	int result;

	char *temp = "bind1";
	snprintf(bulk_test, 10, "%s", temp);

	result = data_control_sql_get_handle_id(g_provider, &g_provider_handle_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_sql_bind_insert_bulk_data_response_cb(g_provider,
			sql_bulk_insert_response_cb2, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_sql_bind_insert_bulk_data_response_cb(
			g_provider_for_bind, sql_bulk_insert_response_cb2, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	b1 = bundle_create();
	bundle_add_str(b1, "key", "test key");
	bundle_add_str(b1, "value", "test value");

	result = data_control_bulk_data_create(&bulk_data_h);
	if (result != DATA_CONTROL_ERROR_NONE)
		goto out;

	data_control_bulk_data_add(bulk_data_h, b1);
	bundle_free(b1);

	data_control_bulk_data_get_count(bulk_data_h, &count);
	dlog_print(DLOG_INFO, "NativeTCT", "bulk add count %d", count);

	result = data_control_sql_insert_bulk_data(g_provider, bulk_data_h, &req_id);
	if (result != DATA_CONTROL_ERROR_NONE)
		goto out;

	result = data_control_sql_insert_bulk_data(g_provider_for_bind, bulk_data_h, &req_id);
	if (result != DATA_CONTROL_ERROR_NONE)
		goto out;

out:
	data_control_bulk_data_destroy(bulk_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_data_control_sql_bind_insert_bulk_data_response_cb_p2
 * @since_tizen		4.0
 * @description		Binds the value
 * @scenario		Calls data_control_sql_bind_insert_bulk_data_response_cb()
 */
int utc_data_control_sql_bind_insert_bulk_data_response_cb_p2(void)
{
	int req_id;
	data_control_bulk_data_h bulk_data_h;
	bundle *b1;
	int count;
	int result;

	char *temp = "bind2";
	snprintf(bulk_test, 10, "%s", temp);

	result = data_control_sql_get_handle_id(g_provider, &g_provider_handle_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_sql_register_insert_bulk_data_response_cb(
			g_provider, sql_bulk_insert_response_cb2, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_sql_bind_insert_bulk_data_response_cb(g_provider,
			sql_bulk_insert_response_cb2, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	b1 = bundle_create();
	bundle_add_str(b1, "key", "test key");
	bundle_add_str(b1, "value", "test value");

	result = data_control_bulk_data_create(&bulk_data_h);
	if (result != DATA_CONTROL_ERROR_NONE)
		goto out;

	data_control_bulk_data_add(bulk_data_h, b1);
	bundle_free(b1);

	data_control_bulk_data_get_count(bulk_data_h, &count);
	dlog_print(DLOG_INFO, "NativeTCT", "bulk add count %d", count);

	result = data_control_sql_insert_bulk_data(g_provider, bulk_data_h, &req_id);
	if (result != DATA_CONTROL_ERROR_NONE)
		goto out;

out:
	data_control_bulk_data_destroy(bulk_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_data_control_sql_bind_insert_bulk_data_response_cb_p3
 * @since_tizen		4.0
 * @description		Binds the value
 * @scenario		Calls data_control_sql_bind_insert_bulk_data_response_cb()
 */
int utc_data_control_sql_bind_insert_bulk_data_response_cb_p3(void)
{
	int req_id;
	data_control_bulk_data_h bulk_data_h;
	bundle *b1;
	int count;
	int result;

	char *temp = "bind1";
	snprintf(bulk_test, 10, "%s", temp);

	result = data_control_sql_get_handle_id(g_provider, &g_provider_handle_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_sql_register_insert_bulk_data_response_cb(
			g_provider, sql_bulk_insert_response_cb2, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_sql_bind_insert_bulk_data_response_cb(
			g_provider_for_bind, sql_bulk_insert_response_cb2, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	b1 = bundle_create();
	bundle_add_str(b1, "key", "test key");
	bundle_add_str(b1, "value", "test value");

	result = data_control_bulk_data_create(&bulk_data_h);
	if (result != DATA_CONTROL_ERROR_NONE)
		goto out;

	data_control_bulk_data_add(bulk_data_h, b1);
	bundle_free(b1);

	data_control_bulk_data_get_count(bulk_data_h, &count);
	dlog_print(DLOG_INFO, "NativeTCT", "bulk add count %d", count);

	result = data_control_sql_insert_bulk_data(g_provider, bulk_data_h, &req_id);
	if (result != DATA_CONTROL_ERROR_NONE)
		goto out;

	result = data_control_sql_insert_bulk_data(g_provider_for_bind,
			bulk_data_h, &req_id);
	if (result != DATA_CONTROL_ERROR_NONE)
		goto out;

out:
	data_control_bulk_data_destroy(bulk_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_data_control_sql_bind_insert_bulk_data_response_cb_n
 * @since_tizen		4.0
 * @description		Binds callback functions
 * @scenario		Calls data_control_sql_bind_insert_bulk_data_response_cb() with invalid parameter
 */
int utc_data_control_sql_bind_insert_bulk_data_response_cb_n(void)
{
	int result = 0;

	result = data_control_sql_bind_insert_bulk_data_response_cb(g_provider, NULL, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_sql_unbind_insert_bulk_data_response_cb_p
 * @since_tizen		4.0
 * @description		Unbinds the value
 * @scenario		Calls data_control_sql_unbind_insert_bulk_data_response_cb()
 */
int utc_data_control_sql_unbind_insert_bulk_data_response_cb_p(void)
{
	int req_id;
	data_control_bulk_data_h bulk_data_h;
	bundle *b1;
	int count;
	int result;

	char *temp = "unbind";
	snprintf(bulk_test, 10, "%s", temp);

	result = data_control_sql_get_handle_id(g_provider, &g_provider_handle_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_sql_bind_insert_bulk_data_response_cb(
			g_provider, sql_bulk_insert_response_cb2, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_sql_bind_insert_bulk_data_response_cb(
			g_provider_for_bind, sql_bulk_insert_response_cb2, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	b1 = bundle_create();
	bundle_add_str(b1, "key", "test key");
	bundle_add_str(b1, "value", "test value");

	result = data_control_bulk_data_create(&bulk_data_h);
	if (result != DATA_CONTROL_ERROR_NONE)
		goto out;
	
	data_control_bulk_data_add(bulk_data_h, b1);
	bundle_free(b1);

	data_control_bulk_data_get_count(bulk_data_h, &count);
	dlog_print(DLOG_INFO, "NativeTCT", "bulk add count %d", count);

	result = data_control_sql_unbind_insert_bulk_data_response_cb(
			g_provider_for_bind);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_sql_insert_bulk_data(g_provider_for_bind, bulk_data_h,
			&req_id);
	if (result != DATA_CONTROL_ERROR_NONE)
		goto out;

	result = data_control_sql_insert_bulk_data(g_provider, bulk_data_h, &req_id);
	if (result != DATA_CONTROL_ERROR_NONE)
		goto out;

out:
	data_control_bulk_data_destroy(bulk_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_data_control_sql_unbind_insert_bulk_data_response_cb_n
 * @since_tizen		4.0
 * @description		Unbinds callback functions
 * @scenario		Calls data_control_sql_unbind_insert_bulk_data_response_cb() with invalid parameter
 */
int utc_data_control_sql_unbind_insert_bulk_data_response_cb_n(void)
{
	int result = 0;

	result = data_control_sql_unbind_insert_bulk_data_response_cb(NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}
