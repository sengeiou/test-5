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
#include <bundle.h>
#include <string.h>

#define PROVIDER_ID "http://datacontrolprovider.com/datacontrol/provider/datacontrolprovider"
#define SQL_DATA_ID "Dictionary"

#define TEST_KEY "WORD"
#define TEST_VALUE "'test'"

/**
 * @function		utc_data_control_bulk_startup
 * @description		Called before each test
 * @parameter		NA
 * @return		NA
 */
void utc_data_control_bulk_startup(void)
{
}

/**
 * @function		utc_data_control_bulk_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return		NA
 */
void utc_data_control_bulk_cleanup(void)
{
}

/**
 * @testcase		utc_data_control_bulk_data_create_p
 * @since_tizen		3.0
 * @description		Create bulk data
 * @scenario		Calls data_control_bulk_data_create()
 */
int utc_data_control_bulk_data_get_data_p(void)
{
	int result;
	data_control_bulk_data_h bulk_data_h;
	bundle *b;
	bundle *ret_b;
	char *ret_val;

	b = bundle_create();
	bundle_add_str(b, TEST_KEY, TEST_VALUE);

	result = data_control_bulk_data_create(&bulk_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_bulk_data_add(bulk_data_h, b);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_bulk_data_get_data(bulk_data_h, 0, &ret_b);
	assert_neq_with_exit(ret_b, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	bundle_get_str(ret_b, TEST_KEY, &ret_val);
	assert_with_exit(!strcmp(ret_val, TEST_VALUE));
	data_control_bulk_data_destroy(bulk_data_h);
	bundle_free(b);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_data_get_data_n01
 * @since_tizen		3.0
 * @description		Create bulk data in intended error case
 * @scenario		Calls data_control_bulk_data_get_data() with invalid parameter
 */
int utc_data_control_bulk_data_get_data_n01(void)
{
	int result;
	bundle *ret_b;
	result = data_control_bulk_data_get_data(NULL, 0, &ret_b);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_data_get_data_n02
 * @since_tizen		3.0
 * @description		Create bulk data in intended error case
 * @scenario		Calls data_control_bulk_data_get_data() with invalid parameter
 */
int utc_data_control_bulk_data_get_data_n02(void)
{
	int result;
	bundle *ret_b;
	data_control_bulk_data_h bulk_data_h;
	result = data_control_bulk_data_create(&bulk_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_bulk_data_get_data(bulk_data_h, -1, &ret_b);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	data_control_bulk_data_destroy(bulk_data_h);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_data_get_count_p
 * @since_tizen		3.0
 * @description		Get bulk data count
 * @scenario		Calls data_control_bulk_data_get_count()
 */
int utc_data_control_bulk_data_get_count_p(void)
{
	int result;
	data_control_bulk_data_h bulk_data_h;
	bundle *b;
	int count;

	b = bundle_create();
	bundle_add_str(b, TEST_KEY, TEST_VALUE);

	result = data_control_bulk_data_create(&bulk_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_bulk_data_add(bulk_data_h, b);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_bulk_data_get_count(bulk_data_h, &count);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	assert_with_exit(count == 1);

	data_control_bulk_data_destroy(bulk_data_h);
	bundle_free(b);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_data_get_data_n01
 * @since_tizen		3.0
 * @description		Get bulk data count in intended error case
 * @scenario		Calls data_control_bulk_data_get_count() with invalid parameter
 */
int utc_data_control_bulk_data_get_count_n01(void)
{
	int result;
	int count;
	result = data_control_bulk_data_get_count(NULL, &count);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_data_get_count_n02
 * @since_tizen		3.0
 * @description		Get bulk data count in intended error case
 * @scenario		Calls data_control_bulk_data_get_count() with invalid parameter
 */
int utc_data_control_bulk_data_get_count_n02(void)
{
	int result;
	data_control_bulk_data_h bulk_data_h;

	result = data_control_bulk_data_create(&bulk_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_bulk_data_get_count(bulk_data_h, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	data_control_bulk_data_destroy(bulk_data_h);
	normal_exit(0);
	return 0;
}


/**
 * @testcase		utc_data_control_bulk_data_add_p
 * @since_tizen		3.0
 * @description		Adds bulk data
 * @scenario		Calls data_control_bulk_data_add()
 */
int utc_data_control_bulk_data_add_p(void)
{
	int result;
	data_control_bulk_data_h bulk_data_h;
	bundle *b1;
	bundle *b2;
	bundle *ret_b;
	char *ret_val;

	b1 = bundle_create();
	bundle_add_str(b1, TEST_KEY, TEST_VALUE);
	b2 = bundle_create();
	bundle_add_str(b2, TEST_KEY, TEST_VALUE);

	result = data_control_bulk_data_create(&bulk_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_bulk_data_add(bulk_data_h, b1);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	result = data_control_bulk_data_add(bulk_data_h, b2);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	data_control_bulk_data_get_data(bulk_data_h, 1, &ret_b);
	assert_neq_with_exit(ret_b, NULL);

	bundle_get_str(ret_b, TEST_KEY, &ret_val);
	assert_with_exit(!strcmp(ret_val, TEST_VALUE));

	data_control_bulk_data_destroy(bulk_data_h);
	bundle_free(b1);
	bundle_free(b2);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_data_add_n01
 * @since_tizen		3.0
 * @description		Adds bulk data in intended error case
 * @scenario		Calls data_control_bulk_data_get_data() with invalid parameter
 */
int utc_data_control_bulk_data_add_n01(void)
{
	int result;
	bundle *b;
	b = bundle_create();
	bundle_add_str(b, TEST_KEY, TEST_VALUE);
	result = data_control_bulk_data_add(NULL, b);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	bundle_free(b);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_data_create_p
 * @since_tizen		3.0
 * @description		Create bulk data
 * @scenario		Calls data_control_bulk_data_create()
 */
int utc_data_control_bulk_data_create_p(void)
{
	int result;
	data_control_bulk_data_h bulk_data_h;
	result = data_control_bulk_data_create(&bulk_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	data_control_bulk_data_destroy(bulk_data_h);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_data_create_n
 * @since_tizen		3.0
 * @description		Create bulk data in intended error case
 * @scenario		Calls data_control_bulk_data_create() with invalid parameter
 */
int utc_data_control_bulk_data_create_n(void)
{
	int result;
	result = data_control_bulk_data_create(NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_data_destroy_p
 * @since_tizen		3.0
 * @description		Create bulk data
 * @scenario		Calls data_control_bulk_data_destroy()
 */
int utc_data_control_bulk_data_destroy_p(void)
{
	int result;
	data_control_bulk_data_h bulk_data_h;
	result = data_control_bulk_data_create(&bulk_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	result = data_control_bulk_data_destroy(bulk_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_data_destroy_n
 * @since_tizen		3.0
 * @description		Create bulk data in intended error case
 * @scenario		Calls data_control_bulk_data_destroy() with invalid parameter
 */
int utc_data_control_bulk_data_destroy_n(void)
{
	int result;
	result = data_control_bulk_data_destroy(NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_data_get_result_data_p
 * @since_tizen		3.0
 * @description		Get bulk result data
 * @scenario		Calls data_control_bulk_result_data_get_result_data()
 */
int utc_data_control_bulk_result_data_get_result_data_p(void)
{
	int result;
	data_control_bulk_result_data_h result_data_h;
	bundle *b;
	bundle *ret_b;
	int ret_result;
	char *ret_val;

	b = bundle_create();
	bundle_add_str(b, TEST_KEY, TEST_VALUE);

	result = data_control_bulk_result_data_create(&result_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_bulk_result_data_add(result_data_h, b, DATA_CONTROL_ERROR_NONE);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_bulk_result_data_get_result_data(result_data_h, 0, &ret_b, &ret_result);
	assert_neq_with_exit(ret_b, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	bundle_get_str(ret_b, TEST_KEY, &ret_val);
	assert_with_exit(!strcmp(ret_val, TEST_VALUE));
	assert_with_exit(ret_result == DATA_CONTROL_ERROR_NONE);

	data_control_bulk_result_data_destroy(result_data_h);
	bundle_free(b);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_result_data_get_result_data_n01
 * @since_tizen		3.0
 * @description		Get bulk result data in intended error case
 * @scenario		Calls data_control_bulk_result_data_get_result_data() with invalid parameter
 */
int utc_data_control_bulk_result_data_get_result_data_n01(void)
{
	int result;
	result = data_control_bulk_result_data_get_result_data(NULL, 0, NULL, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_result_data_get_result_data_n02
 * @since_tizen		3.0
 * @description		Get bulk result data in intended error case
 * @scenario		Calls data_control_bulk_result_data_get_result_data() with invalid parameter
 */
int utc_data_control_bulk_result_data_get_result_data_n02(void)
{
	int result;
	data_control_bulk_result_data_h result_data_h;

	result = data_control_bulk_result_data_create(&result_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_bulk_result_data_get_result_data(result_data_h, -1, NULL, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	data_control_bulk_result_data_destroy(result_data_h);
	normal_exit(0);
	return 0;
}


/**
 * @testcase		utc_data_control_bulk_result_data_get_count_p
 * @since_tizen		3.0
 * @description		Get bulk result data count
 * @scenario		Calls data_control_bulk_result_data_get_count()
 */
int utc_data_control_bulk_result_data_get_count_p(void)
{
	int result;
	data_control_bulk_result_data_h result_data_h;
	bundle *b;
	int count;

	b = bundle_create();
	bundle_add_str(b, TEST_KEY, TEST_VALUE);

	result = data_control_bulk_result_data_create(&result_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_bulk_result_data_add(result_data_h, b, DATA_CONTROL_ERROR_NONE);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_bulk_result_data_get_count(result_data_h, &count);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	assert_with_exit(count == 1);

	data_control_bulk_result_data_destroy(result_data_h);
	bundle_free(b);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_result_data_get_count_n01
 * @since_tizen		3.0
 * @description		Get bulk result data count in intended error case
 * @scenario		Calls data_control_bulk_result_data_get_count() with invalid parameter
 */
int utc_data_control_bulk_result_data_get_count_n01(void)
{
	int result;
	int count;
	result = data_control_bulk_result_data_get_count(NULL, &count);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_result_data_get_count_n02
 * @since_tizen		3.0
 * @description		Get bulk data count in intended error case
 * @scenario		Calls data_control_bulk_data_get_count() with invalid parameter
 */
int utc_data_control_bulk_result_data_get_count_n02(void)
{
	int result;
	data_control_bulk_result_data_h result_data_h;

	result = data_control_bulk_result_data_create(&result_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_bulk_result_data_get_count(result_data_h, NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	data_control_bulk_result_data_destroy(result_data_h);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_result_data_add_p
 * @since_tizen		3.0
 * @description		Add bulk result data
 * @scenario		Calls data_control_bulk_result_data_add()
 */
int utc_data_control_bulk_result_data_add_p(void)
{
	int result;
	data_control_bulk_result_data_h result_data_h;
	bundle *b;
	bundle *ret_b;
	int ret_result;
	char *ret_val;

	b = bundle_create();
	bundle_add_str(b, TEST_KEY, TEST_VALUE);

	result = data_control_bulk_result_data_create(&result_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_bulk_result_data_add(result_data_h, b, DATA_CONTROL_ERROR_NONE);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_bulk_result_data_add(result_data_h, b, DATA_CONTROL_ERROR_NONE);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_bulk_result_data_get_result_data(result_data_h, 1, &ret_b, &ret_result);
	assert_neq_with_exit(ret_b, NULL);

	bundle_get_str(ret_b, TEST_KEY, &ret_val);
	assert_with_exit(!strcmp(ret_val, TEST_VALUE));
	assert_with_exit(ret_result == DATA_CONTROL_ERROR_NONE);

	data_control_bulk_result_data_destroy(result_data_h);
	bundle_free(b);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_result_data_add_n01
 * @since_tizen		3.0
 * @description		Add bulk result data in intended error case
 * @scenario		Calls data_control_bulk_result_data_add() with invalid parameter
 */
int utc_data_control_bulk_result_data_add_n01(void)
{
	int result;
	data_control_bulk_result_data_h result_data_h;

	result = data_control_bulk_result_data_create(&result_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);

	result = data_control_bulk_result_data_add(NULL, NULL, DATA_CONTROL_ERROR_NONE);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);

	data_control_bulk_result_data_destroy(result_data_h);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_result_data_create_p
 * @since_tizen		3.0
 * @description		Create bulk result data
 * @scenario		Calls data_control_bulk_result_data_create()
 */
int utc_data_control_bulk_result_data_create_p(void)
{
	int result;
	data_control_bulk_result_data_h result_data_h;
	result = data_control_bulk_result_data_create(&result_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	data_control_bulk_result_data_destroy(result_data_h);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_result_data_create_n
 * @since_tizen		3.0
 * @description		Create bulk result data in intended error case
 * @scenario		Calls data_control_bulk_result_data_create() with invalid parameter
 */
int utc_data_control_bulk_result_data_create_n(void)
{
	int result;
	result = data_control_bulk_result_data_create(NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_result_data_destroy_p
 * @since_tizen		3.0
 * @description		Create bulk result data
 * @scenario		Calls data_control_bulk_result_data_destroy()
 */
int utc_data_control_bulk_result_data_destroy_p(void)
{
	int result;
	data_control_bulk_result_data_h result_data_h;
	result = data_control_bulk_result_data_create(&result_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	result = data_control_bulk_result_data_destroy(result_data_h);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_NONE);
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_data_control_bulk_result_data_destroy_n
 * @since_tizen		3.0
 * @description		Destroy bulk result data in intended error case
 * @scenario		Calls data_control_bulk_result_data_destroy() with invalid parameter
 */
int utc_data_control_bulk_result_data_destroy_n(void)
{
	int result;
	result = data_control_bulk_result_data_destroy(NULL);
	assert_eq_with_exit(result, DATA_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}
