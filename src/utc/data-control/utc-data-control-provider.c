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
#include <app_manager.h>
#include <app.h>
#include <dlog.h>

#define PROVIDER_ID "http://datacontrolprovider.com/datacontrol/provider/datacontrolprovider"
#define SQL_DATA_ID "Dictionary"
#define MAX_COUNTER 5

static data_control_h __provider;

static data_control_provider_sql_cb *sql_callback;
static data_control_provider_map_cb *map_callback;
static const char __consumer_app[] = "org.tizen.datacontrolnoticonsumer";

void __run_normal_app() {

	static app_control_h app_control_handler;
	bool is_running = false;
	int counter = MAX_COUNTER;
	int ret = app_control_create(&app_control_handler);
	assert_eq_with_exit_no_returnval(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control_handler , __consumer_app);
	assert_eq_with_exit_no_returnval(ret, APP_CONTROL_ERROR_NONE);

	do {
		ret = app_control_send_launch_request(app_control_handler, NULL, NULL);
		if (ret != APP_CONTROL_ERROR_NONE)
			sleep(1);
		app_manager_is_running(__consumer_app, &is_running);
	} while (--counter > 0 && !is_running);
	sleep(1);
}


static void bulk_insert_request_cb(int request_id, data_control_h provider, data_control_bulk_data_h bulk_data_h, void *user_data)
{
}

static void insert_request_cb(int request_id, data_control_h provider, bundle *insert_data, void *user_data)
{
}

static void delete_request_cb(int request_id, data_control_h provider, const char *where, void *user_data)
{
}

static void select_request_cb(int request_id, data_control_h provider, const char **column_list, int column_count, const char *where, const char *order, void *user_data)
{

}

static void update_request_cb(int request_id, data_control_h provider, bundle *update_data, const char *where, void *user_data)
{

}

static void bulk_add_value_request_cb(int request_id, data_control_h provider, data_control_bulk_data_h bulk_data_h, void *user_data)
{
}

static void get_value_request_cb(int request_id, data_control_h provider, const char *key, void *user_data)
{

}

static void set_value_request_cb(int request_id, data_control_h provider, const char *key, const char *old_value, const char *new_value, void *user_data)
{

}

static void add_value_request_cb(int request_id, data_control_h provider, const char *key, const char *value, void *user_data)
{

}

static void remove_value_request_cb(int request_id, data_control_h provider, const char *key, const char *value, void *user_data)
{

}

bool change_noti_consumer_list_cb(
    data_control_h provider,
    char *consumer_appid,
    void *user_data)
{
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] change_noti_consumer_list_cb @@@@@@", __FUNCTION__, __LINE__);
	normal_exit(0);
	return true;
}

static bool consumer_filter_cb(
    data_control_h provider,
    char *consumer_appid,
    void *user_data)
{
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] consumer_filter_cb ", __FUNCTION__, __LINE__);
	int ret;
	if (__is_foreach_check) {
		ret = data_control_provider_foreach_data_change_consumer(
			provider,
			&change_noti_consumer_list_cb,
			NULL);
		assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);
	} else {
		/*  check foreach after consumer app's first add noti request (after registered) */
		__is_foreach_check = true;
	}
	return true;
}

/**
 * @function		utc_data_control_provider_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_data_control_provider_startup(void)
{
	int result = 0;
	result = data_control_sql_create(&__provider);
	if(result)
		printf("startup error");

	result = data_control_sql_set_provider_id(__provider, PROVIDER_ID);
	if(result)
		printf("set provider id error");

	result = data_control_sql_set_data_id(__provider, SQL_DATA_ID);
	if(result)
		printf("set data id error");

	TCT_UTCCheckInstalledApp(1, "org.tizen.datacontrolnoticonsumer");
}

/**
 * @function		utc_data_control_provider_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_data_control_provider_cleanup(void)
{
	// int result = 0;
	// result = data_control_sql_destroy(__provider);
	// if(result) {
	// 	printf("cleanup error");
	// }
}

/**
 * @testcase		utc_data_control_provider_create_select_statement_n
 * @since_tizen		2.3
 * @description		
 */
int utc_data_control_provider_create_select_statement_n(void)
{
	int ret;

	ret = data_control_provider_create_select_statement(NULL, NULL, 0, NULL, NULL);
	ret = get_last_result();
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_create_insert_statement_n
 * @since_tizen		2.3
 * @description		
 */
int utc_data_control_provider_create_insert_statement_n(void)
{
	int ret;

	data_control_provider_create_insert_statement(NULL, NULL);
	ret = get_last_result();
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_create_delete_statement_n
 * @since_tizen		2.3
 * @description		
 */
int utc_data_control_provider_create_delete_statement_n(void)
{
	int ret;

	data_control_provider_create_delete_statement(NULL, NULL);
	ret = get_last_result();
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_create_update_statement_n
 * @since_tizen		2.3
 * @description		
 */
int utc_data_control_provider_create_update_statement_n(void)
{
	int ret;

	data_control_provider_create_update_statement(NULL, NULL, NULL);
	ret = get_last_result();
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_get_client_appid_n
 * @since_tizen		2.3
 * @description		
 */
int utc_data_control_provider_get_client_appid_n(void)
{
	int ret;

	ret = data_control_provider_get_client_appid(-1, NULL);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_send_delete_result_n
 * @since_tizen		2.3
 * @description		
 */
int utc_data_control_provider_send_delete_result_n(void)
{
	int ret;

	ret = data_control_provider_send_delete_result(-1);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_send_error_n
 * @since_tizen		2.3
 * @description		
 */
int utc_data_control_provider_send_error_n(void)
{
	int ret;

	ret = data_control_provider_send_error(-1, NULL);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_send_insert_result_n
 * @since_tizen		2.3
 * @description		
 */
int utc_data_control_provider_send_insert_result_n(void)
{
	int ret;

	ret = data_control_provider_send_insert_result(-1, 0);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_send_map_get_value_result_n
 * @since_tizen		2.3
 * @description		
 */
int utc_data_control_provider_send_map_get_value_result_n(void)
{
	int ret;

	ret = data_control_provider_send_map_get_value_result(-1, NULL, 0);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_send_map_result_n
 * @since_tizen		2.3
 * @description		
 */
int utc_data_control_provider_send_map_result_n(void)
{
	int ret;

	ret = data_control_provider_send_map_result(-1);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_send_select_result_n
 * @since_tizen		2.3
 * @description		
 */
int utc_data_control_provider_send_select_result_n(void)
{
	int ret;

	ret = data_control_provider_send_select_result(-1, NULL);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_send_update_result_n
 * @since_tizen		2.3
 * @description		
 */
int utc_data_control_provider_send_update_result_n(void)
{
	int ret;

	ret = data_control_provider_send_update_result(-1);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_sql_register_cb_p
 * @since_tizen		2.3
 * @description		
 */
int utc_data_control_provider_sql_register_cb_p(void)
{
	int ret;

	sql_callback = (data_control_provider_sql_cb *) malloc(sizeof(data_control_provider_sql_cb));
	sql_callback->select_cb = select_request_cb;
	sql_callback->insert_cb = insert_request_cb;
	sql_callback->delete_cb = delete_request_cb;
	sql_callback->update_cb = update_request_cb;

	ret = data_control_provider_sql_register_cb(sql_callback, NULL);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);
	free(sql_callback);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_sql_register_cb_n
 * @since_tizen		2.3
 * @description		
 */
int utc_data_control_provider_sql_register_cb_n(void)
{
	int ret;

	ret = data_control_provider_sql_register_cb(NULL, NULL);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_sql_unregister_cb_p
 * @since_tizen		2.3
 * @description		
 */
int utc_data_control_provider_sql_unregister_cb_p(void)
{
	int ret;

	ret = data_control_provider_sql_unregister_cb();
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_map_register_cb_p
 * @since_tizen		2.3
 * @description		
 */
int utc_data_control_provider_map_register_cb_p(void)
{
	int ret;

	map_callback = (data_control_provider_map_cb *) malloc(sizeof(data_control_provider_map_cb));
	map_callback->get_cb = get_value_request_cb;
	map_callback->add_cb = add_value_request_cb;
	map_callback->remove_cb = remove_value_request_cb;
	map_callback->set_cb = set_value_request_cb;

	ret = data_control_provider_map_register_cb(map_callback, NULL);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);
	free(map_callback);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_map_register_cb_n
 * @since_tizen		2.3
 * @description		
 */
int utc_data_control_provider_map_register_cb_n(void)
{
	int ret;

	ret = data_control_provider_map_register_cb(NULL, NULL);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_map_unregister_cb_p
 * @since_tizen		2.3
 * @description		
 */
int utc_data_control_provider_map_unregister_cb_p(void)
{
	int ret;

	ret = data_control_provider_map_unregister_cb();
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);

	normal_exit(0);
	return 0;
}


/**
 * @testcase		utc_data_control_provider_send_data_change_noti_p
 * @since_tizen		3.0
 * @description		Send data change noti
 * @scenario		Calls data_control_provider_send_data_change_noti()
 */
int utc_data_control_provider_send_data_change_noti_p(void)
{
	int ret;
	bundle *insert_data = bundle_create();
	ret = data_control_provider_send_data_change_noti(__provider, DATA_CONTROL_DATA_CHANGE_SQL_INSERT, insert_data);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);
	bundle_free(insert_data);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_send_data_change_noti_n01
 * @since_tizen		3.0
 * @description		Add data changed callback in intended error case
 * @scenario		Calls data_control_provider_send_data_change_noti() with invalid parameter
 */
int utc_data_control_provider_send_data_change_noti_n01(void)
{
	int ret;
	bundle *insert_data = bundle_create();
	ret = data_control_provider_send_data_change_noti(NULL, DATA_CONTROL_DATA_CHANGE_SQL_INSERT, insert_data);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	bundle_free(insert_data);
	normal_exit(0);
	return 0;
}


/**
 * @testcase		utc_data_control_provider_send_data_change_noti_n02
 * @since_tizen		3.0
 * @description		Add data changed callback in intended error case
 * @scenario		Calls data_control_provider_send_data_change_noti() with invalid parameter
 */
int utc_data_control_provider_send_data_change_noti_n02(void)
{
	int ret;
	bundle *insert_data = bundle_create();
	ret = data_control_provider_send_data_change_noti(__provider, -1, insert_data);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	bundle_free(insert_data);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_add_data_change_consumer_filter_cb_p
 * @since_tizen		3.0
 * @description		Add data change consumer filter callback
 * @scenario		Calls data_control_provider_add_data_change_consumer_filter_cb()
 */
int utc_data_control_provider_add_data_change_consumer_filter_cb_p(void)
{
	int ret;
	int filter_callback_id;

	sql_callback = (data_control_provider_sql_cb *) malloc(sizeof(data_control_provider_sql_cb));
	sql_callback->select_cb = select_request_cb;
	sql_callback->insert_cb = insert_request_cb;
	sql_callback->delete_cb = delete_request_cb;
	sql_callback->update_cb = update_request_cb;

	ret = data_control_provider_sql_register_cb(sql_callback, NULL);
	ret = data_control_provider_add_data_change_consumer_filter_cb(consumer_filter_cb, NULL, &filter_callback_id);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);
	assert_with_exit(filter_callback_id > 0);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_data_control_provider_send_data_change_noti_n01
 * @since_tizen		3.0
 * @description		Add data change consumer filter callback in intended error case
 * @scenario		Calls data_control_provider_add_data_change_consumer_filter_cb() with invalid parameter
 */
int utc_data_control_provider_add_data_change_consumer_filter_cb_n01(void)
{
	int ret;
	int filter_callback_id;
	ret = data_control_provider_send_data_change_noti(NULL, DATA_CONTROL_DATA_CHANGE_SQL_INSERT, &filter_callback_id);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_send_data_change_noti_n02
 * @since_tizen		3.0
 * @description		Add data change consumer filter callback in intended error case
 * @scenario		Calls data_control_provider_add_data_change_consumer_filter_cb() with invalid parameter
 */
int utc_data_control_provider_add_data_change_consumer_filter_cb_n02(void)
{
	int ret;
	int filter_callback_id;
	ret = data_control_provider_send_data_change_noti(consumer_filter_cb, -1, &filter_callback_id);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_remove_data_change_consumer_filter_cb_p
 * @since_tizen		3.0
 * @description		Remove data change consumer filter callback
 * @scenario		Calls data_control_provider_remove_data_change_consumer_filter_cb() after add filter callback
 */
int utc_data_control_provider_remove_data_change_consumer_filter_cb_p(void)
{
	int ret;
	int filter_callback_id;
	ret = data_control_provider_add_data_change_consumer_filter_cb(consumer_filter_cb, NULL, &filter_callback_id);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);
	assert_with_exit(filter_callback_id > 0);

	ret = data_control_provider_remove_data_change_consumer_filter_cb(filter_callback_id);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_remove_data_change_consumer_filter_cb_n
 * @since_tizen		3.0
 * @description		Remove data change consumer filter callback in intended error case
 * @scenario		Calls data_control_provider_remove_data_change_consumer_filter_cb() with invalid parameter
 */
int utc_data_control_provider_remove_data_change_consumer_filter_cb_n(void)
{
	int ret;
	ret = data_control_provider_remove_data_change_consumer_filter_cb(-1);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_foreach_data_change_consumer_p
 * @since_tizen		3.0
 * @description		Foreach data change consumer
 * @scenario		Calls data_control_provider_foreach_data_change_consumer()
 */
int utc_data_control_provider_foreach_data_change_consumer_p(void)
{

	int ret;
	int filter_callback_id;
	sql_callback = (data_control_provider_sql_cb *) malloc(sizeof(data_control_provider_sql_cb));
	sql_callback->select_cb = select_request_cb;
	sql_callback->insert_cb = insert_request_cb;
	sql_callback->delete_cb = delete_request_cb;
	sql_callback->update_cb = update_request_cb;

	ret = data_control_provider_sql_register_cb(sql_callback, NULL);
	ret = data_control_provider_add_data_change_consumer_filter_cb(consumer_filter_cb, NULL, &filter_callback_id);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);
	assert_with_exit(filter_callback_id > 0);
	__is_foreach_check = false;
	__run_normal_app();

	return 0;
}

/**
 * @testcase		utc_data_control_provider_foreach_data_change_consumer_n01
 * @since_tizen		3.0
 * @description		Foreach data change consumer in intended error case
 * @scenario		Calls data_control_provider_foreach_data_change_consumer() with invalid parameter
 */
int utc_data_control_provider_foreach_data_change_consumer_n01(void)
{
	int ret;
	ret = data_control_provider_foreach_data_change_consumer(
		NULL,
		&change_noti_consumer_list_cb,
		NULL);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_foreach_data_change_consumer_n02
 * @since_tizen		3.0
 * @description		Foreach data change consumer in intended error case
 * @scenario		Calls data_control_provider_foreach_data_change_consumer() with invalid parameter
 */
int utc_data_control_provider_foreach_data_change_consumer_n02(void)
{
	int ret;
	ret = data_control_provider_foreach_data_change_consumer(
		__provider,
		NULL,
		NULL);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_send_bulk_insert_result_n01
 * @since_tizen		3.0
 * @description		Send bulk insert result in intended error case
 * @scenario		Calls data_control_provider_send_bulk_insert_result() with invalid parameter
 */
int utc_data_control_provider_send_bulk_insert_result_n01(void)
{
	int ret;
	ret = data_control_provider_send_bulk_insert_result(-1, NULL);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_send_map_bulk_add_result_n01
 * @since_tizen		3.0
 * @description		Send map bulk add result in intended error case
 * @scenario		Calls data_control_provider_send_map_bulk_add_result() with invalid parameter
 */
int utc_data_control_provider_send_map_bulk_add_result_n01(void)
{
	int ret;
	ret = data_control_provider_send_map_bulk_add_result(-1, NULL);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_sql_register_insert_bulk_data_request_cb_p
 * @since_tizen		3.0
 * @description		Register insert bulk data request callback
 * @scenario		Calls data_control_provider_sql_register_insert_bulk_data_request_cb()
 */
int utc_data_control_provider_sql_register_insert_bulk_data_request_cb_p(void)
{
	int ret;
	ret = data_control_provider_sql_register_insert_bulk_data_request_cb(bulk_insert_request_cb, NULL);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_sql_register_insert_bulk_data_request_cb_n01
 * @since_tizen		3.0
 * @description		Register insert bulk data request callback in intended error case
 * @scenario		Calls data_control_provider_sql_register_insert_bulk_data_request_cb() with invalid parameter
 */
int utc_data_control_provider_sql_register_insert_bulk_data_request_cb_n01(void)
{
	int ret;
	ret = data_control_provider_sql_register_insert_bulk_data_request_cb(NULL, NULL);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_sql_unregister_insert_bulk_data_request_cb_p
 * @since_tizen		3.0
 * @description		Register insert bulk data request callback
 * @scenario		Calls data_control_provider_sql_unregister_insert_bulk_data_request_cb()
 */
int utc_data_control_provider_sql_unregister_insert_bulk_data_request_cb_p(void)
{
	int ret;
	ret = data_control_provider_sql_unregister_insert_bulk_data_request_cb();
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_map_register_add_bulk_data_request_cb_p
 * @since_tizen		3.0
 * @description		Register add bulk data request callback
 * @scenario		Calls data_control_provider_map_register_add_bulk_data_request_cb()
 */
int utc_data_control_provider_map_register_add_bulk_data_request_cb_p(void)
{
	int ret;
	ret = data_control_provider_map_register_add_bulk_data_request_cb(bulk_insert_request_cb, NULL);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_map_register_add_bulk_data_request_cb_n01
 * @since_tizen		3.0
 * @description		Register add bulk data request callback in intended error case
 * @scenario		Calls data_control_provider_map_register_add_bulk_data_request_cb() with invalid parameter
 */
int utc_data_control_provider_map_register_add_bulk_data_request_cb_n01(void)
{
	int ret;
	ret = data_control_provider_map_register_add_bulk_data_request_cb(NULL, NULL);
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_provider_map_unregister_add_bulk_data_request_cb_p
 * @since_tizen		3.0
 * @description		Register add bulk data request callback
 * @scenario		Calls data_control_provider_map_unregister_add_bulk_data_request_cb()
 */
int utc_data_control_provider_map_unregister_add_bulk_data_request_cb_p(void)
{
	int ret;
	ret = data_control_provider_map_unregister_add_bulk_data_request_cb();
	assert_eq_with_exit(ret, DATA_CONTROL_ERROR_NONE);
	normal_exit(0);
	return 0;
}
