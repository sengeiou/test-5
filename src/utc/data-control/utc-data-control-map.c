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
#include <dlog.h>
#include "tct_app_common.h"

#define PROVIDER_ID "http://datacontrolmapprovider.com/datacontrol/provider/datacontrolmapprovider"
#define MAP_DATA_ID "Dictionary"

#define DISTRUST_PROVIDER_ID "http://distrust_provider.com/datacontrol/provider/distrust_provider"
#define PRIVILEGE_PROVIDER_ID "http://privilegetestprovider1.com/datacontrol/provider/privilegetestprovider1"
#define UNPRIVILEGE_PROVIDER_ID "http://privilegetestprovider2.com/datacontrol/provider/privilegetestprovider2"

static const char *test_key = "wrong_key";
static const char *old_val = "old_value";
static const char *new_val = "new_value";
static data_control_h g_provider;
static data_control_h g_provider_for_bind;
static data_control_h distrust_provider;
static data_control_h unprivilege_provider;
static data_control_h privilege_provider;

static int g_provider_handle_id;
static int g_provider_handle_id_for_bind;

static int check_handle_id = 0;
static int check_handle_id_for_bind = 0;

static int check_count_of_call = 0;
static char bulk_test[10];

/**
 * @function		utc_data_control_map_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_data_control_map_startup(void)
{
	bulk_test[0] = '\0';
	int result = 0;

	result = data_control_map_create(&g_provider);
	if (result)
		printf("create error");

	result = data_control_map_set_provider_id(g_provider, PROVIDER_ID);
	if (result)
		printf("set provider id error");

	result = data_control_map_set_data_id(g_provider, MAP_DATA_ID);
	if (result)
		printf("set data id error");

	result = data_control_map_create(&distrust_provider);
	if (result)
		printf("create error");

	result = data_control_map_set_provider_id(distrust_provider,
			DISTRUST_PROVIDER_ID);
	if (result)
		printf("set provider id error");

	result = data_control_map_set_data_id(distrust_provider, MAP_DATA_ID);
	if (result)
		printf("set data id error");


	result = data_control_map_create(&privilege_provider);
	if (result)
		printf("create error");

	result = data_control_map_set_provider_id(privilege_provider,
			PRIVILEGE_PROVIDER_ID);
	if (result)
		printf("set provider id error");

	result = data_control_map_set_data_id(privilege_provider, MAP_DATA_ID);
	if (result)
		printf("set data id error");

	result = data_control_map_create(&unprivilege_provider);
	if (result)
		printf("create error");

	result = data_control_map_set_provider_id(unprivilege_provider,
			UNPRIVILEGE_PROVIDER_ID);
	if (result)
		printf("set provider id error");

	result = data_control_map_set_data_id(unprivilege_provider, MAP_DATA_ID);
	if (result)
		printf("set data id error");

	result = data_control_map_create(&g_provider_for_bind);
	if (result)
		printf("create error");

	result = data_control_map_set_provider_id(g_provider_for_bind, PROVIDER_ID);
	if (result)
		printf("set provider id error");

	result = data_control_map_set_data_id(g_provider_for_bind, MAP_DATA_ID);
	if (result)
		printf("set data id error");

	result = data_control_map_get_handle_id(g_provider_for_bind,
			&g_provider_handle_id_for_bind);
	if (result)
		printf("get handle id error");

	TCT_UTCCheckInstalledApp(5, "org.tizen.datacontrolmapprovider",
			"org.tizen.datacontrolprovider",
			"org.tizen.distrust_provider",
			"org.example.privilegetestprovider1",
			"org.example.privilegetestprovider2");
}

/**
 * @function		utc_data_control_map_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_data_control_map_cleanup(void)
{
	check_handle_id = 0;
	check_handle_id_for_bind = 0;

	check_count_of_call = 0;
}

static void map_bulk_add_response_cb(int request_id, data_control_h provider, data_control_bulk_result_data_h bulk_results,
		bool provider_result, const char *error, void *user_data)
{
	int i;
	int result;
	int count;

	dlog_print(DLOG_INFO, "NativeTCT", "map_bulk_add_response_cb ");

	if (provider_result) {
		dlog_print(DLOG_INFO, "NativeTCT", "%d bulk add operation is successful ", request_id);
		data_control_bulk_result_data_get_count(bulk_results, &count);
		dlog_print(DLOG_INFO, "NativeTCT", "bulk add operation is successful count %d", count);

		assert_eq_with_exit_no_returnval(__correct_row_cnt, count);
		for (i = 0; i < count; i++) {
			data_control_bulk_result_data_get_result_data(bulk_results, i, NULL, &result);
			dlog_print(DLOG_INFO, "NativeTCT", "BULK add result ###### %d", result);
			assert_eq_with_exit_no_returnval(result, DATA_CONTROL_ERROR_NONE);
		}
	} else {
		dlog_print(DLOG_ERROR, "NativeTCT",
				"The bulk add operation for the request %d is failed. error message: %s  ", request_id, error);
		normal_exit(1);
	}
	normal_exit(0);
}

static void get_response_cb(int request_id, data_control_h provider, char **result_value_list,
		int result_value_count, bool provider_result, const char *error, void *user_data)
{

	int result = 0;

	printf("get_response_cb \n");
	printf("next operation : %s\n", __next_operation);

	bool is_valid_return = false;

	if (provider_result && (__correct_row_cnt == result_value_count)) {

		if (__correct_row_cnt == 0) {
			is_valid_return = true;
		} else {

			int i = 0;
			for (i = 0 ; i < result_value_count ; i ++) {

				printf("count : %d, value : %s \n ", result_value_count, result_value_list[i]);
				if (strcmp(result_value_list[i], __correct_value) == 0) {
					is_valid_return = true;
					break;
				}
			}
		}

	}

	assert_eq_with_exit_no_returnval(is_valid_return, true);

	if (strcmp(__next_operation, "remove") == 0) {

		result = data_control_map_remove(g_provider, test_key, __correct_value, &request_id);
		assert_eq_with_exit_no_returnval(result, DATA_CONTROL_ERROR_NONE);
	} else {
		result = data_control_map_destroy(g_provider);
		if(result) {
			printf("cleanup error");
		}

		normal_exit(0);
	}
}

static void set_response_cb(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
	int result = 0;

	printf("set_response_cb \n");
	printf("next operation : %s\n", __next_operation);

	if (strcmp(__next_operation, "get") == 0) {
		__next_operation = "remove";

		result = data_control_map_get(g_provider, test_key, &request_id);
		assert_eq_with_exit_no_returnval(result, DATA_CONTROL_ERROR_NONE);
	} else {
		result = data_control_map_destroy(g_provider);
		if(result) {
			printf("cleanup error");
		}
		normal_exit(0);
	}

}

static void add_response_cb(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
	int result = 0;

	printf("add_response_cb \n");
	printf("next operation : %s\n", __next_operation);

	if (strcmp(__next_operation, "get") == 0) {

		__next_operation = "remove";

		result = data_control_map_get(g_provider, test_key, &request_id);
		assert_eq_with_exit_no_returnval(result, DATA_CONTROL_ERROR_NONE);

	} else if (strcmp(__next_operation, "remove") == 0) {

		__next_operation = "get";

		result = data_control_map_remove(g_provider, test_key, __correct_value, &request_id);
		assert_eq_with_exit_no_returnval(result, DATA_CONTROL_ERROR_NONE);

	} else if (strcmp(__next_operation, "set") == 0) {

		__correct_value = new_val;
		__correct_row_cnt = 1;
		__next_operation = "get";

		result = data_control_map_set(g_provider, test_key, old_val, new_val, &request_id);
		assert_eq_with_exit_no_returnval(result, DATA_CONTROL_ERROR_NONE);

	} else {
		result = data_control_map_destroy(g_provider);
		if(result) {
			printf("cleanup error");
		}
		normal_exit(0);
	}

}

static void remove_response_cb(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
	printf("remove_response_cb \n");

	int result = 0;
	if (strcmp(__next_operation, "get") == 0) {
		__correct_row_cnt = 0;
		__next_operation = "done";

		result = data_control_map_get(g_provider, test_key, &request_id);
		assert_eq_with_exit_no_returnval(result, DATA_CONTROL_ERROR_NONE);

	} else {

		result = data_control_map_destroy(g_provider);
		if(result) {
			printf("cleanup error");
		}
		normal_exit(0);
	}

}

static void map_bulk_add_response_cb2(int request_id, data_control_h provider, data_control_bulk_result_data_h bulk_results,
		bool provider_result, const char *error, void *user_data)
{
	int temp_handle_id1;
	int result;

	char *temp_bind1_text = "bind1";
	char *temp_bind2_text = "bind2";
	char *temp_unbind_text = "unbind";

	dlog_print(DLOG_INFO, "NativeTCT", "bulk_test : %s", bulk_test);

	result = data_control_map_get_handle_id(provider, &temp_handle_id1);
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

static void get_response_cb2(int request_id, data_control_h provider, char **result_value_list,
		int result_value_count, bool provider_result, const char *error, void *user_data)
{
	dlog_print(DLOG_INFO, "NativeTCT", "get_response_cb ");
	int temp_handle_id1;
	int result;

	result = data_control_map_get_handle_id(provider, &temp_handle_id1);
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

static void set_response_cb2(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
	dlog_print(DLOG_INFO, "NativeTCT", "set_response_cb ");

	check_count_of_call++;

	if (check_count_of_call == 2)
		normal_exit(0);
}

static void add_response_cb2(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
	printf("add_response_cb \n");
	int temp_handle_id1;
	int result;

	result = data_control_map_get_handle_id(provider, &temp_handle_id1);
	if (result != DATA_CONTROL_ERROR_NONE)
		normal_exit(1);

	if (temp_handle_id1 == g_provider_handle_id)
		check_handle_id = 1;

	if (temp_handle_id1 == g_provider_handle_id_for_bind)
		normal_exit(1);

	if (check_handle_id)
		normal_exit(0);
}

static void remove_response_cb2(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
	printf("remove_response_cb \n");
}


/**
 * @testcase		utc_data_control_map_create_p
 * @since_tizen		2.3
 * @description		Creates a provider handle
 * @scenario		Calls data_control_map_create()
 */
int utc_data_control_map_create_p(void)
{
	data_control_h provider;
	int result = 0;

	result = data_control_map_create(&provider);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_create_n
 * @since_tizen		2.3
 * @description		Creates a provider handle in intended error case
 * @scenario		Calls data_control_map_create() with invalid parameter
 */
int utc_data_control_map_create_n(void)
{
	int result = 0;

	result = data_control_map_create(NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_destroy_p
 * @since_tizen		2.3
 * @description		Destroys the provider handle and releases all its resources
 * @scenario		Calls data_control_map_create() to create handle and
 * 					calls data_control_map_destroy() to destroy
 */
int utc_data_control_map_destroy_p(void)
{
	data_control_h provider;
	int result = 0;

	result = data_control_map_create(&provider);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_map_destroy(provider);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_destroy_n
 * @since_tizen		2.3
 * @description		Destroys the provider handle and releases all its resources in intended error case
 * @scenario		Calls data_control_map_destroy() with invalid error case
 */
int utc_data_control_map_destroy_n(void)
{
	data_control_h provider = NULL;
	int result = 0;

	result = data_control_map_destroy(provider);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_set_provider_id_p
 * @since_tizen		2.3
 * @description		Sets the provider id
 * @scenario		Calls data_control_map_set_provider_id()
 */
int utc_data_control_map_set_provider_id_p(void)
{
	int result = 0;

	result = data_control_map_set_provider_id(g_provider, PROVIDER_ID);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_set_provider_id_n
 * @since_tizen		2.3
 * @description		Sets the provider id in intended error case
 * @scenario		Calls data_control_map_set_provider_id() with invalid parameter
 */
int utc_data_control_map_set_provider_id_n(void)
{
	int result = 0;

	result = data_control_map_set_provider_id(g_provider, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_get_provider_id_p
 * @since_tizen		2.3
 * @description		Gets the provider id
 * @scenario		Calls data_control_map_set_provider_id() to set provider id and
 * 					calls data_control_map_get_provider_id() to get provider id
 */
int utc_data_control_map_get_provider_id_p(void)
{
	char *provider_id;
	int result = 0;

	result = data_control_map_set_provider_id(g_provider, PROVIDER_ID);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_map_get_provider_id(g_provider, &provider_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	assert(!strcmp(PROVIDER_ID, provider_id));

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_get_provider_id_n
 * @since_tizen		2.3
 * @description		Gets the provider id in intended error case
 * @scenario		Calls data_control_map_get_provider_id() with invalid parameter
 */
int utc_data_control_map_get_provider_id_n(void)
{
	int result = 0;

	result = data_control_map_get_provider_id(g_provider, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_set_data_id_p
 * @since_tizen		2.3
 * @description		Sets data id
 * @scenario		Calls data_control_map_set_data_id() with invalid parameter
 */
int utc_data_control_map_set_data_id_p(void)
{
	int result = 0;

	result = data_control_map_set_data_id(g_provider, MAP_DATA_ID);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_set_data_id_n
 * @since_tizen		2.3
 * @description		Sets data id
 * @scenario		Calls data_control_map_set_data_id() with invalid parameter
 */
int utc_data_control_map_set_data_id_n(void)
{
	int result = 0;

	result = data_control_map_set_data_id(g_provider, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_get_data_id_p
 * @since_tizen		2.3
 * @description		Gets the data id
 * @scenario		Calls data_control_map_set_data_id() to set data id and
 * 					calls data_control_map_get_data_id() to get data id
 */
int utc_data_control_map_get_data_id_p(void)
{
	char *data_id;
	int result = 0;

	result = data_control_map_set_data_id(g_provider, MAP_DATA_ID);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_map_get_data_id(g_provider, &data_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	assert(!strcmp(data_id, MAP_DATA_ID));

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_get_data_id_n
 * @since_tizen		2.3
 * @description		Gets the data id
 * @scenario		Calls data_control_map_get_data_id() with invalid parameter
 */
int utc_data_control_map_get_data_id_n(void)
{
	int result = 0;

	result = data_control_map_set_data_id(g_provider, MAP_DATA_ID);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_map_get_data_id(g_provider, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_register_response_cb_p
 * @since_tizen		2.3
 * @description		Registers callback functions
 * @scenario		Calls data_control_map_register_response_cb()
 */
int utc_data_control_map_register_response_cb_p(void)
{
	data_control_map_response_cb *map_callback;
	int result = 0;

	map_callback = (data_control_map_response_cb *) malloc(sizeof(data_control_map_response_cb));
	assert_neq_with_exit(map_callback, NULL);

	map_callback->get_cb = get_response_cb;
	map_callback->add_cb = add_response_cb;
	map_callback->remove_cb = remove_response_cb;
	map_callback->set_cb = set_response_cb;

	result = data_control_map_register_response_cb(g_provider, map_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	free(map_callback);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_register_response_cb_n
 * @since_tizen		2.3
 * @description		Registers callback functions in intended error case
 * @scenario		Calls data_control_map_register_response_cb() with invalid parameter
 */
int utc_data_control_map_register_response_cb_n(void)
{
	int result = 0;

	result = data_control_map_register_response_cb(g_provider, NULL, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_unregister_response_cb_p
 * @since_tizen		2.3
 * @description		Unregisters callback functions
 * @scenario		Calls data_control_map_register_response_cb() to register callback functions and
 * 					calls data_control_map_unregister_response_cb() to unregister callback functions
 */
int utc_data_control_map_unregister_response_cb_p(void)
{
	data_control_map_response_cb *map_callback;
	int result = 0;

	map_callback = (data_control_map_response_cb *) malloc(sizeof(data_control_map_response_cb));
	assert_neq_with_exit(map_callback, NULL);

	map_callback->get_cb = get_response_cb;
	map_callback->add_cb = add_response_cb;
	map_callback->remove_cb = remove_response_cb;
	map_callback->set_cb = set_response_cb;

	result = data_control_map_register_response_cb(g_provider, map_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	result = data_control_map_unregister_response_cb(g_provider);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	free(map_callback);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_add_p
 * @since_tizen		2.3
 * @description		Adds the value
 * @scenario		Calls data_control_map_add()
 */
int utc_data_control_map_add_p(void)
{

	int result = 0;
	int req_id;
	data_control_map_response_cb *map_callback;


	map_callback = (data_control_map_response_cb *) malloc(sizeof(data_control_map_response_cb));
	assert_neq_with_exit(map_callback, NULL);

	map_callback->get_cb = get_response_cb;
	map_callback->add_cb = add_response_cb;
	map_callback->remove_cb = remove_response_cb;
	map_callback->set_cb = set_response_cb;

	result = data_control_map_register_response_cb(g_provider, map_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	__next_operation = "get";
	__correct_value = old_val;
	__correct_row_cnt = 1;


	printf("utc_data_control_map_add_p \n");
	result = data_control_map_add(g_provider, test_key, old_val, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	free(map_callback);

	return 0;
}

/**
* @testcase	utc_data_control_map_add_p1
* @since_tizen	2.3
* @remarks	This testcase is for data-control privilege feature
*		which is enabled since tizen 4.0
* @type		Positive
* @description	Adds the value
* @scenario	Sends the map_add to provider which requires
*		privilege(http://tizen.org/privilege/appmanager.launch).
*/
int utc_data_control_map_add_p1(void)
{
	int result = 0;
	int req_id;
	data_control_map_response_cb *map_callback;

	map_callback = (data_control_map_response_cb *) malloc(sizeof(data_control_map_response_cb));
	assert_neq_with_exit(map_callback, NULL);

	map_callback->get_cb = get_response_cb;
	map_callback->add_cb = add_response_cb;
	map_callback->remove_cb = remove_response_cb;
	map_callback->set_cb = set_response_cb;

	result = data_control_map_register_response_cb(privilege_provider, map_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	__next_operation = "";

	printf("utc_data_control_map_add_p1 \n");
	result = data_control_map_add(privilege_provider, test_key, old_val, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	free(map_callback);

	return 0;
}

/**
 * @testcase		utc_data_control_map_add_n1
 * @since_tizen		2.3
 * @description		Adds the value in intended error case
 * @scenario		Calls data_control_map_add() with invalid parameter
 */
int utc_data_control_map_add_n1(void)
{
	int result = 0;
	int req_id;
	const char *val = "old_value";

	result = data_control_map_add(NULL, test_key, val, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase        utc_data_control_map_add_n2
 * @since_tizen     4.0
 * @description     Adds the value in intended error case
 * @scenario        Calls data_control_map_add() with untrusted provider
 */
int utc_data_control_map_add_n2(void)
{
	int result = 0;
	int req_id;
	const char *val = "old_value";

	result = data_control_map_add(distrust_provider, test_key, val, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_PERMISSION_DENIED);

	normal_exit(0);
	return 0;
}

/**
* @testcase	utc_data_control_map_add_n3
* @since_tizen	2.3
* @remarks	This testcase is for data-control privilege feature
*		which is enabled since tizen 4.0
* @type		Negative
* @description	Adds the value in intended error case
* @scenario	Sends the map_add to provider which requires
*		privilege(http://tizen.org/privilege/alarm.set).
*/
int utc_data_control_map_add_n3(void)
{
	int result = 0;
	int req_id;
	data_control_map_response_cb *map_callback;

	map_callback = (data_control_map_response_cb *) malloc(sizeof(data_control_map_response_cb));
	assert_neq_with_exit(map_callback, NULL);

	map_callback->get_cb = get_response_cb;
	map_callback->add_cb = add_response_cb;
	map_callback->remove_cb = remove_response_cb;
	map_callback->set_cb = set_response_cb;

	result = data_control_map_register_response_cb(unprivilege_provider, map_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	__next_operation = "";

	printf("utc_data_control_map_add_n3 \n");
	result = data_control_map_add(unprivilege_provider, test_key, old_val, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_PERMISSION_DENIED, map_callback);

	free(map_callback);

	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_data_control_map_set_p01
 * @since_tizen		2.3
 * @description		Sets the value
 * @scenario		Calls data_control_map_set()
 */
int utc_data_control_map_set_p01(void)
{

	int result = 0;
	int req_id;
	data_control_map_response_cb *map_callback;


	map_callback = (data_control_map_response_cb *) malloc(sizeof(data_control_map_response_cb));
	assert_neq_with_exit(map_callback, NULL);

	map_callback->get_cb = get_response_cb;
	map_callback->add_cb = add_response_cb;
	map_callback->remove_cb = remove_response_cb;
	map_callback->set_cb = set_response_cb;

	result = data_control_map_register_response_cb(g_provider, map_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	__next_operation = "done";
	__correct_value = old_val;
	__correct_row_cnt = 1;

	result = data_control_map_set(g_provider, test_key, old_val, new_val, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	free(map_callback);

	return 0;
}

/**
 * @testcase		utc_data_control_map_set_p02
 * @since_tizen		2.3
 * @description		Sets the value
 * @scenario		Calls data_control_map_add() and set next operation "set" then
 * 					data_control_map_set() is called from add callback function
 */
int utc_data_control_map_set_p02(void)
{

	int result = 0;
	int req_id;
	data_control_map_response_cb *map_callback;


	map_callback = (data_control_map_response_cb *) malloc(sizeof(data_control_map_response_cb));
	assert_neq_with_exit(map_callback, NULL);

	map_callback->get_cb = get_response_cb;
	map_callback->add_cb = add_response_cb;
	map_callback->remove_cb = remove_response_cb;
	map_callback->set_cb = set_response_cb;

	result = data_control_map_register_response_cb(g_provider, map_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	__next_operation = "set";
	__correct_value = old_val;
	__correct_row_cnt = 1;

	result = data_control_map_add(g_provider, test_key, old_val, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	free(map_callback);

	return 0;
}

/**
 * @testcase		utc_data_control_map_set_n1
 * @since_tizen		2.3
 * @description		Sets the value in intended error case
 * @scenario		Calls data_control_map_set() with invalid parameter
 */
int utc_data_control_map_set_n1(void)
{
	int result = 0;
	int req_id;
	const char *old_val = "old_value";
	const char *new_val = "new_value";

	result = data_control_map_set(NULL, test_key, old_val, new_val, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase        utc_data_control_map_set_n2
 * @since_tizen     4.0
 * @description     Sets the value in intended error case
 * @scenario        Calls data_control_map_set() with untrusted provider
 */
int utc_data_control_map_set_n2(void)
{
	int result = 0;
	int req_id;
	const char *old_val = "old_value";
	const char *new_val = "new_value";

	result = data_control_map_set(distrust_provider, test_key, old_val, new_val, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_PERMISSION_DENIED);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_get_p
 * @since_tizen		2.3
 * @description		Gets the value
 * @scenario		Calls data_control_map_get() with invalid parameter
 */
int utc_data_control_map_get_p(void)
{
	int result = 0;
	int req_id;

	data_control_map_response_cb *map_callback;

	map_callback = (data_control_map_response_cb *) malloc(sizeof(data_control_map_response_cb));
	assert_neq_with_exit(map_callback, NULL);

	map_callback->get_cb = get_response_cb;
	map_callback->add_cb = add_response_cb;
	map_callback->remove_cb = remove_response_cb;
	map_callback->set_cb = set_response_cb;

	result = data_control_map_register_response_cb(g_provider, map_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	__next_operation = "done";
	__correct_row_cnt = 0;

	result = data_control_map_get(g_provider, test_key, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	free(map_callback);

	return 0;

}

/**
 * @testcase		utc_data_control_map_get_n1
 * @since_tizen		2.3
 * @description		Gets the value in intended error case
 * @scenario		Calls data_control_map_get() with invalid parameter
 */
int utc_data_control_map_get_n1(void)
{
	int result = 0;
	int req_id;

	result = data_control_map_get(NULL, test_key, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase        utc_data_control_map_set_n2
 * @since_tizen     4.0
 * @description     Gets the value in intended error case
 * @scenario        Calls data_control_map_get() with untrusted provider
 */
int utc_data_control_map_get_n2(void)
{
	int result = 0;
	int req_id;

	result = data_control_map_get(distrust_provider, test_key, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_PERMISSION_DENIED);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_get_with_page_p
 * @since_tizen		2.3
 * @description		Gets the value
 * @scenario		Calls data_control_map_get_with_page()
 */
int utc_data_control_map_get_with_page_p(void)
{
	int result = 0;
	int req_id;

	data_control_map_response_cb *map_callback;

	map_callback = (data_control_map_response_cb *) malloc(sizeof(data_control_map_response_cb));
	assert_neq_with_exit(map_callback, NULL);

	map_callback->get_cb = get_response_cb;
	map_callback->add_cb = add_response_cb;
	map_callback->remove_cb = remove_response_cb;
	map_callback->set_cb = set_response_cb;

	result = data_control_map_register_response_cb(g_provider, map_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	__next_operation = "done";
	__correct_row_cnt = 0;

	result = data_control_map_get_with_page(g_provider, test_key, &req_id, 1, 20);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	free(map_callback);

	return 0;

}

/**
 * @testcase		utc_data_control_map_get_with_page_n1
 * @since_tizen		2.3
 * @description		Gets the value in intended error case
 * @scenario		Calls data_control_map_get_with_page() with invalid parameter
 */
int utc_data_control_map_get_with_page_n1(void)
{
	int result = 0;
	int req_id;

	result = data_control_map_get_with_page(NULL, test_key, &req_id, 1, 20);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase        utc_data_control_map_get_with_page_n2
 * @since_tizen     4.0
 * @description     Gets the value in intended error case
 * @scenario        Calls data_control_map_get_with_page() with untrusted provider
 */
int utc_data_control_map_get_with_page_n2(void)
{
	int result = 0;
	int req_id;

	result = data_control_map_get_with_page(distrust_provider, test_key, &req_id, 1, 20);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_PERMISSION_DENIED);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_remove_p
 * @since_tizen		2.3
 * @description		Removes the value
 * @scenario		Calls data_control_map_add() and set next operatio "remove" then
 * 					data_control_map_remove() is called from add callback function
 */
int utc_data_control_map_remove_p(void)
{

	int result = 0;
	int req_id;
	data_control_map_response_cb *map_callback;


	map_callback = (data_control_map_response_cb *) malloc(sizeof(data_control_map_response_cb));
	assert_neq_with_exit(map_callback, NULL);

	map_callback->get_cb = get_response_cb;
	map_callback->add_cb = add_response_cb;
	map_callback->remove_cb = remove_response_cb;
	map_callback->set_cb = set_response_cb;

	result = data_control_map_register_response_cb(g_provider, map_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	__next_operation = "remove";
	__correct_value = old_val;
	__correct_row_cnt = 0;

	result = data_control_map_add(g_provider, test_key, old_val, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	free(map_callback);

	return 0;
}

/**
 * @testcase		utc_data_control_map_remove_n1
 * @since_tizen		2.3
 * @description		Removes the value in intended error case
 * @scenario		Calls data_control_map_remove() with invalid parameter
 */
int utc_data_control_map_remove_n1(void)
{
	int result = 0;
	int req_id;
	const char *val = "old_value";

	result = data_control_map_remove(NULL, test_key, val, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase        utc_data_control_map_remove_n2
 * @since_tizen     4.0
 * @description     Removes the value in intended error case
 * @scenario        Calls data_control_map_remove() with untrusted provider
 */
int utc_data_control_map_remove_n2(void)
{
	int result = 0;
	int req_id;
	const char *val = "old_value";

	result = data_control_map_remove(distrust_provider, test_key, val, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_PERMISSION_DENIED);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_add_bulk_data_p
 * @since_tizen		3.0
 * @description		Adds the value
 * @scenario		Calls data_control_map_add_bulk_data()
 */
int utc_data_control_map_add_bulk_data_p(void)
{

	int req_id;
	data_control_bulk_data_h bulk_data_h;
	bundle *b1;
	bundle *b2;
	int count;

	int result = data_control_map_register_add_bulk_data_response_cb(g_provider, map_bulk_add_response_cb, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	b1 = bundle_create();
	bundle_add_str(b1, "key", "test key");
	bundle_add_str(b1, "value", "test value");
	b2 = bundle_create();
	bundle_add_str(b2, "key", "test key");
	bundle_add_str(b2, "value", "test value");

	data_control_bulk_data_create(&bulk_data_h);
	data_control_bulk_data_add(bulk_data_h, b1);
	data_control_bulk_data_add(bulk_data_h, b2);
	bundle_free(b1);
	bundle_free(b2);

	data_control_bulk_data_get_count(bulk_data_h, &count);
	dlog_print(DLOG_INFO, "NativeTCT", "bulk add count %d", count);

	__correct_row_cnt = count;
	result = data_control_map_add_bulk_data(g_provider, bulk_data_h, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_bulk_data_destroy(bulk_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_data_control_map_add_bulk_data_n1
 * @since_tizen		3.0
 * @description		Adds the value in intended error case
 * @scenario		Calls data_control_map_add_bulk_data() with invalid parameter
 */
int utc_data_control_map_add_bulk_data_n1(void)
{
	int result = 0;
	int req_id;

	result = data_control_map_add_bulk_data(NULL, NULL, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase        utc_data_control_map_remove_n2
 * @since_tizen     4.0
 * @description     Adds bundle data in intended error case
 * @scenario        Calls data_control_map_add_bulk_data() with untrusted provider
 */
int utc_data_control_map_add_bulk_data_n2(void)
{
	int result = 0;
	int req_id;
	data_control_bulk_data_h bulk_data_h;
	bundle *b1;

	b1 = bundle_create();
	bundle_add_str(b1, "key", "test key");
	bundle_add_str(b1, "value", "test value");

	data_control_bulk_data_create(&bulk_data_h);
	data_control_bulk_data_add(bulk_data_h, b1);

	result = data_control_map_add_bulk_data(distrust_provider, bulk_data_h, &req_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_PERMISSION_DENIED);

	bundle_free(b1);
	data_control_bulk_data_destroy(bulk_data_h);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_register_add_bulk_data_response_cb_p
 * @since_tizen		3.0
 * @description		Registers add bulk data response callback
 * @scenario		Calls data_control_map_register_add_bulk_data_response_cb()
 */
int utc_data_control_map_register_add_bulk_data_response_cb_p(void)
{
	int result = data_control_map_register_add_bulk_data_response_cb(g_provider, map_bulk_add_response_cb, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_data_control_map_register_add_bulk_data_response_cb_n
 * @since_tizen		3.0
 * @description		Registers add bulk data response callback in intended error case
 * @scenario		Calls data_control_map_register_add_bulk_data_response_cb() with invalid parameter
 */
int utc_data_control_map_register_add_bulk_data_response_cb_n(void)
{
	int result = 0;
	result = data_control_map_register_add_bulk_data_response_cb(NULL, NULL, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_unregister_add_bulk_data_response_cb_p
 * @since_tizen		3.0
 * @description		Unregisters add bulk data response callback
 * @scenario		Calls data_control_map_unregister_add_bulk_data_response_cb()
 */
int utc_data_control_map_unregister_add_bulk_data_response_cb_p(void)
{
	int result;

	result = data_control_map_register_add_bulk_data_response_cb(g_provider, map_bulk_add_response_cb, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_map_unregister_add_bulk_data_response_cb(g_provider);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_data_control_map_unregister_add_bulk_data_response_cb_n
 * @since_tizen		3.0
 * @description		Unregisters add bulk data response callback in intended error case
 * @scenario		Calls utc_data_control_map_unregister_add_bulk_data_response_cb_n() with invalid parameter
 */
int utc_data_control_map_unregister_add_bulk_data_response_cb_n(void)
{
	int result = 0;
	result = data_control_map_unregister_add_bulk_data_response_cb(g_provider);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_get_handle_id_p
 * @since_tizen		4.0
 * @description		Gets the handle id
 * @scenario		Calls data_control_map_get_handle_id() to get handle id
 */
int utc_data_control_map_get_handle_id_p(void)
{
	int result = 0;

	result = data_control_map_get_handle_id(g_provider, &g_provider_handle_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_get_handle_id_n
 * @since_tizen		4.0
 * @description		Gets the handle id in intended error case
 * @scenario		Calls data_control_map_get_handle_id() to get handle id
 * 					with invalid parameter
 */
int utc_data_control_map_get_handle_id_n(void)
{
	int result = 0;

	result = data_control_map_get_handle_id(NULL, &g_provider_handle_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_bind_response_cb_p1
 * @since_tizen		4.0
 * @description		Binds callback functions
 * @scenario		Calls data_control_map_bind_response_cb()
 */
int utc_data_control_map_bind_response_cb_p1(void)
{
	int result = 0;
	int req_id;

	data_control_map_response_cb *map_callback;

	map_callback = (data_control_map_response_cb *) malloc(
			sizeof(data_control_map_response_cb));
	assert_neq_with_exit(map_callback, NULL);

	map_callback->get_cb = get_response_cb2;
	map_callback->add_cb = add_response_cb2;
	map_callback->remove_cb = remove_response_cb2;
	map_callback->set_cb = set_response_cb2;

	result = data_control_map_get_handle_id(g_provider, &g_provider_handle_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	result = data_control_map_bind_response_cb(g_provider, map_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	result = data_control_map_bind_response_cb(g_provider_for_bind,
			map_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	result = data_control_map_get(g_provider, test_key, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	result = data_control_map_get(g_provider_for_bind, test_key, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	free(map_callback);
	return 0;
}

/**
 * @testcase		utc_data_control_map_bind_response_cb_p2
 * @since_tizen		4.0
 * @description		Binds callback functions
 * @scenario		Calls data_control_map_bind_response_cb()
 */
int utc_data_control_map_bind_response_cb_p2(void)
{
	int result = 0;
	int req_id;
	const char *val = "old_value";

	data_control_map_response_cb *map_callback;

	map_callback = (data_control_map_response_cb *) malloc(
			sizeof(data_control_map_response_cb));
	assert_neq_with_exit(map_callback, NULL);

	map_callback->get_cb = get_response_cb2;
	map_callback->add_cb = add_response_cb2;
	map_callback->remove_cb = remove_response_cb2;
	map_callback->set_cb = set_response_cb2;

	result = data_control_map_get_handle_id(g_provider, &g_provider_handle_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	result = data_control_map_register_response_cb(g_provider, map_callback,
			NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	result = data_control_map_bind_response_cb(g_provider_for_bind,
			map_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	result = data_control_map_get(g_provider, test_key, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	result = data_control_map_get(g_provider_for_bind, test_key, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	free(map_callback);
	return 0;
}

/**
 * @testcase		utc_data_control_map_bind_response_cb_p3
 * @since_tizen		4.0
 * @description		Binds callback functions
 * @scenario		Calls data_control_map_bind_response_cb()
 */
int utc_data_control_map_bind_response_cb_p3(void)
{
	int result = 0;
	int req_id;
	const char *old_val = "old_value";
	const char *new_val = "new_value";

	data_control_map_response_cb *map_callback;

	map_callback = (data_control_map_response_cb *) malloc(
			sizeof(data_control_map_response_cb));
	assert_neq_with_exit(map_callback, NULL);

	map_callback->get_cb = get_response_cb2;
	map_callback->add_cb = add_response_cb2;
	map_callback->remove_cb = remove_response_cb2;
	map_callback->set_cb = set_response_cb2;

	result = data_control_map_register_response_cb(g_provider, map_callback,
			NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	result = data_control_map_bind_response_cb(g_provider, map_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	result = data_control_map_set(g_provider, test_key, old_val,
			new_val, &req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	free(map_callback);
	return 0;
}

/**
 * @testcase		utc_data_control_map_bind_response_cb_n
 * @since_tizen		4.0
 * @description		Binds callback functions
 * @scenario		Calls data_control_map_bind_response_cb() with invalid parameter
 */
int utc_data_control_map_bind_response_cb_n(void)
{
	int result = 0;

	result = data_control_map_bind_response_cb(g_provider, NULL, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_unbind_response_cb_p
 * @since_tizen		4.0
 * @description		Unbinds callback functions
 * @scenario		Calls data_control_map_unbind_response_cb()
 */
int utc_data_control_map_unbind_response_cb_p(void)
{
	int result = 0;
	int req_id;
	char *temp_key = "temp_key";

	data_control_map_response_cb *map_callback;

	map_callback = (data_control_map_response_cb *) malloc(
			sizeof(data_control_map_response_cb));
	assert_neq_with_exit(map_callback, NULL);

	map_callback->get_cb = get_response_cb2;
	map_callback->add_cb = add_response_cb2;
	map_callback->remove_cb = remove_response_cb2;
	map_callback->set_cb = set_response_cb2;

	result = data_control_map_get_handle_id(g_provider, &g_provider_handle_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	result = data_control_map_bind_response_cb(g_provider, map_callback,
			NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	result = data_control_map_bind_response_cb(g_provider_for_bind,
			map_callback, NULL);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	result = data_control_map_unbind_response_cb(g_provider_for_bind);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	result = data_control_map_add(g_provider_for_bind, temp_key, old_val,
			&req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	result = data_control_map_add(g_provider, temp_key, old_val,
			&req_id);
	assert_eq_with_free(result, DATA_CONTROL_ERROR_NONE, map_callback);

	free(map_callback);
	return 0;
}

/**
 * @testcase		utc_data_control_map_unbind_response_cb_n
 * @since_tizen		4.0
 * @description		Unbinds callback functions
 * @scenario		Calls data_control_map_unbind_response_cb() with invalid parameter
 */
int utc_data_control_map_unbind_response_cb_n(void)
{
	int result = 0;

	result = data_control_map_unbind_response_cb( NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_bind_add_bulk_data_response_cb_p1
 * @since_tizen		4.0
 * @description		Binds the value
 * @scenario		Calls data_control_map_bind_add_bulk_data_response_cb()
 */
int utc_data_control_map_bind_add_bulk_data_response_cb_p1(void)
{
	int req_id;
	data_control_bulk_data_h bulk_data_h;
	bundle *b1;
	int count;
	int result;

	char *temp = "bind1";
	snprintf(bulk_test, 10, "%s", temp);

	result = data_control_map_get_handle_id(g_provider, &g_provider_handle_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_map_bind_add_bulk_data_response_cb(g_provider,
			map_bulk_add_response_cb2, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_map_bind_add_bulk_data_response_cb(
			g_provider_for_bind, map_bulk_add_response_cb2, NULL);
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

	result = data_control_map_add_bulk_data(g_provider_for_bind, bulk_data_h, &req_id);
	if (result != DATA_CONTROL_ERROR_NONE)
		goto out;

	result = data_control_map_add_bulk_data(g_provider, bulk_data_h, &req_id);
	if (result != DATA_CONTROL_ERROR_NONE)
		goto out;

out:
	data_control_bulk_data_destroy(bulk_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_data_control_map_bind_add_bulk_data_response_cb_p2
 * @since_tizen		4.0
 * @description		Binds the value
 * @scenario		Calls data_control_map_bind_add_bulk_data_response_cb()
 */
int utc_data_control_map_bind_add_bulk_data_response_cb_p2(void)
{
	int req_id;
	data_control_bulk_data_h bulk_data_h;
	bundle *b1;
	int count;
	int result;

	char *temp = "bind2";
	snprintf(bulk_test, 10, "%s", temp);

	result = data_control_map_get_handle_id(g_provider, &g_provider_handle_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_map_register_add_bulk_data_response_cb(
			g_provider, map_bulk_add_response_cb2, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_map_bind_add_bulk_data_response_cb(g_provider,
			map_bulk_add_response_cb2, NULL);
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

	result = data_control_map_add_bulk_data(g_provider, bulk_data_h, &req_id);
	if (result != DATA_CONTROL_ERROR_NONE)
		goto out;

out:
	data_control_bulk_data_destroy(bulk_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_data_control_map_bind_add_bulk_data_response_cb_p3
 * @since_tizen		4.0
 * @description		Binds the value
 * @scenario		Calls data_control_map_bind_add_bulk_data_response_cb()
 */
int utc_data_control_map_bind_add_bulk_data_response_cb_p3(void)
{
	int req_id;
	data_control_bulk_data_h bulk_data_h;
	bundle *b1;
	int count;
	int result;

	char *temp = "bind1";
	snprintf(bulk_test, 10, "%s", temp);

	result = data_control_map_get_handle_id(g_provider, &g_provider_handle_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_map_register_add_bulk_data_response_cb(
			g_provider, map_bulk_add_response_cb2, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_map_bind_add_bulk_data_response_cb(
			g_provider_for_bind, map_bulk_add_response_cb2, NULL);
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

	result = data_control_map_add_bulk_data(g_provider, bulk_data_h, &req_id);
	if (result != DATA_CONTROL_ERROR_NONE)
		goto out;

	result = data_control_map_add_bulk_data(g_provider_for_bind, bulk_data_h,
			&req_id);
	if (result != DATA_CONTROL_ERROR_NONE)
		goto out;

out:
	data_control_bulk_data_destroy(bulk_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_data_control_map_bind_add_bulk_data_response_cb_n
 * @since_tizen		4.0
 * @description		Binds callback functions
 * @scenario		Calls data_control_map_bind_add_bulk_data_response_cb() with invalid parameter
 */
int utc_data_control_map_bind_add_bulk_data_response_cb_n(void)
{
	int result = 0;

	result = data_control_map_bind_add_bulk_data_response_cb(g_provider, NULL, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_map_unbind_add_bulk_data_response_cb_p
 * @since_tizen		4.0
 * @description		Unbinds the value
 * @scenario		Calls data_control_map_unbind_add_bulk_data_response_cb()
 */
int utc_data_control_map_unbind_add_bulk_data_response_cb_p(void)
{
	int req_id;
	data_control_bulk_data_h bulk_data_h;
	bundle *b1;
	int count;
	int result;

	char *temp = "unbind";
	snprintf(bulk_test, 10, "%s", temp);

	result = data_control_map_get_handle_id(g_provider, &g_provider_handle_id);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_map_bind_add_bulk_data_response_cb(
			g_provider, map_bulk_add_response_cb2, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_map_bind_add_bulk_data_response_cb(
			g_provider_for_bind, map_bulk_add_response_cb2, NULL);
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

	result = data_control_map_unbind_add_bulk_data_response_cb(
			g_provider_for_bind);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_map_add_bulk_data(g_provider_for_bind, bulk_data_h,
			&req_id);
	if (result != DATA_CONTROL_ERROR_NONE)
		goto out;

	result = data_control_map_add_bulk_data(g_provider, bulk_data_h, &req_id);
	if (result != DATA_CONTROL_ERROR_NONE)
		goto out;

out:
	data_control_bulk_data_destroy(bulk_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_data_control_map_unbind_add_bulk_data_response_cb_n
 * @since_tizen		4.0
 * @description		Unbinds callback functions
 * @scenario		Calls data_control_map_unbind_add_bulk_data_response_cb() with invalid parameter
 */
int utc_data_control_map_unbind_add_bulk_data_response_cb_n(void)
{
	int result = 0;

	result = data_control_map_unbind_add_bulk_data_response_cb(NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}
