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
#include "assert_common.h"
#include <glib.h>
#include <string.h>
#include <app_preference.h>
#include <app.h>
//& set: ApplicationPreference

static bool foreach_item_passed = true;
static bool preference_changed_unset_passed = true;
static bool preference_changed_no_action_passed = true;
static int foreach_item_int = 5;
static const char *foreach_item_string = "foreach_item_string";

/**
 * @function		utc_application_preference_startup
 * @description		Called the preference_remove_all().
 * @parameter		NA
 * @return			NA
 */
void utc_application_preference_startup(void)
{
	preference_remove_all();
}

/**
 * @testcase		utc_application_preference_set_int_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sets an integer value in the preference.
 * @scenario		Sets an integer value and gets the value.
 *			Calls the preference_set_int() and calls the preference_get_int(),
 *			and then checks the return value.
 */
int utc_application_preference_set_int_p(void)
{
	int ret;

	const char *key = "preference_key";
	int value = 1;
	int output = 0;

	ret = preference_set_int(key, value);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_int(key, &output);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);
	assert_eq_with_exit(output, value);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_set_int_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets an integer value in the preference.
 * @scenario		Calls the preference_set_int() with the invalid parameter
 *			that the key is NULL, and then checks the return value.
 */
int utc_application_preference_set_int_n(void)
{
	int ret;
	int value = 1;

	ret = preference_set_int(NULL, value);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_set_double_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sets a double value in the preference.
 * @scenario		Sets a double value and gets the value.
 *			Calls the preference_set_double() and calls the preference_get_double(),
 *			and then checks the return value.
 */
int utc_application_preference_set_double_p(void)
{
	const char *key = "preference_key";

	int ret;

	double value = 1.0;
	double output = 0.0;

	ret = preference_set_double(key, value);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_double(key, &output);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);
	assert_eq_with_exit(output, value);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_set_double_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets a double value in the preference.
 * @scenario		Calls the preference_set_double() with the invalid parameter
 *			that the key is NULL, and then checks the return value.
 */
int utc_application_preference_set_double_n(void)
{
	int ret;
	double value = 1.0;

	ret = preference_set_double(NULL, value);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_set_string_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sets a string value in the preference.
 * @scenario		Sets a string value and gets the value.
 *			Calls the preference_set_string() and calls the preference_get_string(),
 *			and then checks the return value.
 */
int utc_application_preference_set_string_p(void)
{
	const char *key = "preference_key";
	char *value = "value";
	char *output = NULL;

	int ret;

	ret = preference_set_string(key, value);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_string(key, &output);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);
	assert_neq_with_exit(output, NULL);
	assert_with_exit(!strcmp(output, value));

	free(output);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_set_string_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets a string value in the preference.
 * @scenario		Calls the preference_set_string() with the invalid parameter
 *			that the key is NULL, and then checks the return value.
 */
int utc_application_preference_set_string_n1(void)
{
	int ret;
	char *value = "value";

	ret = preference_set_string(NULL, value);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_set_string_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets a string value in the preference.
 * @scenario		Calls the preference_set_string() with the invalid parameter
 *			that the value is NULL, and then checks the return value.
 */
int utc_application_preference_set_string_n2(void)
{
	int ret;
	const char *key = "preference_key";

	ret = preference_set_string(key, NULL);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_set_boolean_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sets a boolean value in the preference.
 * @scenario		Sets a boolean value and gets the value.
 *			Calls the preference_set_boolean() and calls the preference_get_boolean(),
 *			and then checks the return value.
 */
int utc_application_preference_set_boolean_p(void)
{
	const char *key = "preference_key";
	bool value = true;
	bool output = false;

	int ret;

	ret = preference_set_boolean(key, value);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_boolean(key, &output);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);
	assert_eq_with_exit(output, value);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_set_boolean_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets a boolean value in the preference.
 * @scenario		Calls the preference_set_boolean() with the invalid parameter
 *			that the key is NULL, and then checks the return value.
 */
int utc_application_preference_set_boolean_n(void)
{
	int ret;

	ret = preference_set_boolean(NULL, true);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}


/**
 * @testcase		utc_application_preference_get_int_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets an integer value from the preference.
 * @scenario		Sets an integer value and gets the value.
 *			Calls the preference_set_int() and calls the preference_get_int(),
 *			and then checks the return value.
 */
int utc_application_preference_get_int_p(void)
{
	int ret;
	const char *key = "get_key";
	int value = 1;
	int output = 0;

	ret = preference_set_int(key, value);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_int(key, &output);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);
	assert_eq_with_exit(output, value);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_get_int_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets an integer value from the preference.
 * @scenario		Calls the preference_get_int() with the invalid parameter
 *			that the value is NULL, and then checks the return value.
 */
int utc_application_preference_get_int_n1(void)
{
	const char *key = "key";
	int value = 1;
	int ret = PREFERENCE_ERROR_NONE;

	ret = preference_set_int(key, value);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_int(key, NULL);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_get_int_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets an integer value from the preference.
 * @scenario		Calls the preference_get_int() with the invalid parameter
 *			that the key is NULL, and then checks the return value.
 */
int utc_application_preference_get_int_n2(void)
{
	int output = -1;
	int ret = PREFERENCE_ERROR_NONE;

	ret = preference_get_int(NULL, &output);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_get_int_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets an integer value from the preference.
 * @scenario		Calls the preference_get_int() with the invalid key,
 *			and then checks the return value.
 */
int utc_application_preference_get_int_n3(void)
{
	const char *key = "key";
	int output = -1;
	int ret = PREFERENCE_ERROR_NONE;

	ret = preference_get_int(key, &output);
	assert_neq_with_exit(ret, PREFERENCE_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_get_double_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets a double value from the preference.
 * @scenario		Sets a dobule value and gets the value.
 *			Calls the preference_set_double() and calls the preference_get_double(),
 *			and then checks the return value.
 */
int utc_application_preference_get_double_p(void)
{
	const char *key = "get_key";
	int ret;
	double value = 1.0;
	double output = 0.0;

	ret = preference_set_double(key, value);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_double(key, &output);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);
	assert_eq_with_exit(output, value);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_get_double_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets a double value from the preference.
 * @scenario		Calls the preference_get_double() with the invalid parameter
 *			that the value is NULL, and then checks the return value.
 */
int utc_application_preference_get_double_n1(void)
{
	const char *key = "key";
	double value = 1;
	int ret;

	ret = preference_set_double(key, value);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_double(key, NULL);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_get_double_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets a double value from the preference.
 * @scenario		Calls the preference_get_double() with the invalid parameter
 *			that the key is NULL, and then checks the return value.
 */
int utc_application_preference_get_double_n2(void)
{
	double output = -1;
	int ret;

	ret = preference_get_double(NULL, &output);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_get_double_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets a double value from the preference.
 * @scenario		Calls the preference_get_double() with the invalid key,
 *			and then checks the return value.
 */
int utc_application_preference_get_double_n3(void)
{
	const char *key = "key";
	double output = -1;
	int ret;

	ret = preference_get_double(key, &output);
	assert_neq_with_exit(ret, PREFERENCE_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_get_string_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets a string value from the preference.
 * @scenario		Sets a string value and gets the value.
 *			Calls the preference_set_string() and calls the preference_get_string(),
 *			and then checks the return value.
 */
int utc_application_preference_get_string_p(void)
{
	const char *key = "get_key";
	char *value = "value";
	char *output = NULL;
	int ret;

	ret = preference_set_string(key, value);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_string(key, &output);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);
	assert_neq_with_exit(output, NULL);
	assert_with_exit(!strcmp(output, value));

	free(output);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_get_string_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets a string value from the preference.
 * @scenario		Calls the preference_get_string() with the invalid paramter
 *			that the value is NULL, and then checks the return value.
 */
int utc_application_preference_get_string_n1(void)
{
	const char *key = "key";
	char *value = "value";
	int ret = PREFERENCE_ERROR_NONE;

	ret = preference_set_string(key, value);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_string(key, NULL);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_get_string_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets a string value from the preference.
 * @scenario		Calls the preference_get_strinbg() with the invalid parameter
 *			that the key is NULL, and then checks the return value.
 */
int utc_application_preference_get_string_n2(void)
{
	char *output = NULL;
	int ret = PREFERENCE_ERROR_NONE;

	ret = preference_get_string(NULL, &output);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_get_string_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets a string value from the preference.
 * @scenario		Calls the preference_get_string() with the invalid key,
 *			and then checks the return value.
 */
int utc_application_preference_get_string_n3(void)
{
	const char *key = "key";
	char *output = NULL;
	int ret = PREFERENCE_ERROR_NONE;

	ret = preference_get_string(key, &output);
	assert_neq_with_exit(ret, PREFERENCE_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_get_boolean_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets a boolean value from the preference.
 * @scenario		Sets a boolean value and gets the value.
 *			Calls the preference_set_boolean() and calls the preference_get_boolean(),
 *			and then checks the return value.
 */
int utc_application_preference_get_boolean_p(void)
{
	const char *key = "get_key";
	bool value = true;
	bool output = false;
	int ret;

	ret = preference_set_boolean(key, value);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_boolean(key, &output);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);
	assert_eq_with_exit(output, value);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_get_boolean_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets a boolean value from the preference.
 * @scenario		Calls the preference_get_boolean() with the invalid parameter
 *			that the value is NULL, and then checks the return value.
 */
int utc_application_preference_get_boolean_n1(void)
{
	const char *key = "key";
	bool value = true;
	int ret = PREFERENCE_ERROR_NONE;

	ret = preference_set_boolean(key, value);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_boolean(key, NULL);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_get_boolean_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets a boolean value from the preference.
 * @scenario		Calls the preference_get_boolean() with the invalid parameter
 *			that the key is NULL, and then checks the return value.
 */
int utc_application_preference_get_boolean_n2(void)
{
	bool output = true;
	int ret = PREFERENCE_ERROR_NONE;

	ret = preference_get_boolean(NULL, &output);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_get_boolean_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets a boolean value from the preference.
 * @scenario		Calls the preference_get_boolean() with the invalid key,
 *			and then checks the return value.
 */
int utc_application_preference_get_boolean_n3(void)
{
	const char *key = "key";
	bool output = true;
	int ret = PREFERENCE_ERROR_NONE;

	ret = preference_get_boolean(key, &output);
	assert_neq_with_exit(ret, PREFERENCE_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_remove_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Removes any value with the given @a key from the preference.
 * @scenario		Sets a integer value and gets the value, and then remove the key.
 *			Next, gets the value.
 *			Calls the preference_set_int() and calls the preference_get_int(),
 *			and then preference_remove(). Next, call the preference_get_int(),
 *			checks the return value.
 */
int utc_application_preference_remove_p(void)
{
	const char *key = "key";
	int value = 1;
	int output = -1;
	int ret;

	ret = preference_set_int(key, value);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_int(key, &output);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);
	assert_eq_with_exit(output, value);

	ret = preference_remove(key);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_int(key, &output);
	assert_neq_with_exit(ret, PREFERENCE_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_remove_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Removes any value with the given @a key from the preference.
 * @scenario		Calls the preference_remove() with the invalid parameter
 *			that the key is NULL, and then checks the return value.
 */
int utc_application_preference_remove_n1(void)
{
	int ret;

	ret = preference_remove(NULL);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_remove_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Removes any value with the given @a key from the preference.
 * @scenario		Calls the preference_remove() with the invalid key,
 *			and then checks the return value.
 */
int utc_application_preference_remove_n2(void)
{
	const char *key = "key";
	int ret;

	ret = preference_remove(key);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NO_KEY);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_remove_all_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Removes all key-value pairs from the preference.
 * @scenario		Sets the integer values and gets the values,
 *			and then removes all key-value pairs. Next, gets the value.
 */
int utc_application_preference_remove_all_p(void)
{
	const char *key1 = "key1";
	int value1 = 1;
	const char *key2 = "key2";
	int value2 = 2;
	int output;
	int ret;

	ret = preference_set_int(key1, value1);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_int(key1, &output);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);
	assert_eq_with_exit(output, value1);

	ret = preference_set_int(key2, value2);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_int(key2, &output);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);
	assert_eq_with_exit(output, value2);

	ret = preference_remove_all();
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_int(key1, &output);
	assert_neq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_int(key2, &output);
	assert_neq_with_exit(ret, PREFERENCE_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_is_existing_p1
 * @since_tizen		2.3
 * @type		Positive
 * @description		Checks whether the given @a key exists in the preference.
 * @scenario		Sets an integer value and gets the value,
 *			and then checks the value.
 */
int utc_application_preference_is_existing_p1(void)
{
	const char *key = "key";
	int value = 1;
	int output;
	bool exists = false;
	int ret;

	ret = preference_set_int(key, value);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_int(key, &output);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);
	assert_eq_with_exit(output, value);

	ret = preference_is_existing(key, &exists);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);
	assert_eq_with_exit(exists, true);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_is_existing_p2
 * @since_tizen		2.3
 * @type		Positive
 * @description		Checks whether the given @a key exists in the preference.
 * @scenario		Checks the key-value pairs. The "key1" and the "key2" are not exists.
 *			Calls the preference_is_existing() and then checks the return value.
 */
int utc_application_preference_is_existing_p2(void)
{
	const char *key1 = "key1";
	const char *key2 = "key2";
	bool exists = true;
	int ret;

	ret = preference_is_existing(key1, &exists);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);
	assert_eq_with_exit(exists, false);

	ret = preference_is_existing(key2, &exists);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);
	assert_eq_with_exit(exists, false);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_is_existing_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Checks whether the given @a key exists in the preference.
 * @scenario		Calls the preference_is_existing() with the invalid parameter
 *			that the key is NULL, and then checks the return value.
 */
int utc_application_preference_is_existing_n1(void)
{
	bool exists;
	int ret;

	ret = preference_is_existing(NULL, &exists);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_is_existing_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Checks whether the given @a key exists in the preference.
 * @scenario		Callthe the preference_is_existing() with the invalid parameter
 *			that the existing is NULL, and then checks the return value.
 */
int utc_application_preference_is_existing_n2(void)
{
	int ret;

	ret = preference_is_existing("key", NULL);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_is_existing_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Checks whether the given @a key exists in the preference.
 * @scenario		Calls the preference_is_existing() with the invalid key,
 *			and then checks the return value.
 */
int utc_application_preference_is_existing_n3(void)
{
	int ret;
	bool exists;

	ret = preference_is_existing("dummy_key", &exists);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);
	assert_eq_with_exit(exists, 0);
	normal_exit(0);

	return 0;
}

static guint timeout_id = 0;
static gboolean timeout_function(gpointer data)
{
	printf("timeout");
	normal_exit(1);

	return FALSE;
}

static void pref_changed_cb(const char *key, void *user_data)
{
	int value = 0;
	int ret = PREFERENCE_ERROR_NONE;

	ret = preference_get_int(key, &value);
	if (ret == PREFERENCE_ERROR_NONE) {
		if (value == 2) {
			if (timeout_id > 0) {
				g_source_remove(timeout_id);
				timeout_id = 0;
			}

			normal_exit(0);
		}
	}
}

/**
 * @testcase		utc_application_preference_set_changed_cb_p1
 * @since_tizen		2.3
 * @type		Positive
 * @description		Registers a callback function to be invoked when value of the given key in the preference changes.
 * @scenario		Sets a integer value and registers a callback function,
 *			and then changes the value.
 */
int utc_application_preference_set_changed_cb_p1(void)
{
	int ret = 0;
	const char *key1 = "key1";
	int value1 = 1;
	int value2 = 2;

	ret = preference_set_int(key1, value1);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_set_changed_cb(key1, pref_changed_cb, NULL);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_set_int(key1, value2);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	timeout_id = g_timeout_add(5000, timeout_function, NULL);

	return 0;
}

static void pref_changed_no_action_cb(const char *key, void *user_data)
{
	preference_changed_no_action_passed = false;
}

/**
 * @testcase		utc_application_preference_set_changed_cb_p2
 * @since_tizen		2.3
 * @type		Positive
 * @description		Registers a callback function to be invoked when value of the given key in the preference changes.
 * @scenario		Sets a integer value and registers a callback function,
 *			and then removes the key-value pair.
 */
int utc_application_preference_set_changed_cb_p2(void)
{
	int ret;

	const char *key1 = "key1";
	int value1 = 1;
	int count1 = 0;

	preference_changed_no_action_passed = true;

	ret = preference_set_int(key1, value1);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_set_changed_cb(key1, pref_changed_no_action_cb, &count1);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_remove(key1);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);
	assert_eq_with_exit(preference_changed_no_action_passed, true);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_set_changed_cb_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Registers a callback function to be invoked when value of the given key in the preference changes.
 * @scenario		Calls the preference_set_changed_cb() with the invalid parameter
 *			that the key is NULL, and then checks the return value.
 */
int utc_application_preference_set_changed_cb_n1(void)
{
	int ret;

	ret = preference_set_changed_cb(NULL, pref_changed_cb, NULL);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_set_changed_cb_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description	egisters a callback function to be invoked when value of the given key in the preference changes.
 * @scenario		Calls the preference_set_changed_cb() with the invalid parameter
 *			that the callback is NULL, and then checks the return value.
 */
int utc_application_preference_set_changed_cb_n2(void)
{
	int ret;
	const char *key = "key";

	ret = preference_set_changed_cb(key, NULL, NULL);
	assert_neq_with_exit(ret, PREFERENCE_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_set_changed_cb_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Registers a callback function to be invoked when value of the given key in the preference changes.
 * @scenario		Calls the preference_set_changed_cb() with the invalid parameter,
 *			and then checks the return value.
 */
int utc_application_preference_set_changed_cb_n3(void)
{
	int ret;
	const char *key = "key";

	ret = preference_set_changed_cb(key, pref_changed_cb, NULL);
	assert_neq_with_exit(ret, PREFERENCE_ERROR_NONE);
	normal_exit(0);

	return 0;
}

static void pref_changed_unset_cb(const char *key, void *user_data)
{
	preference_changed_unset_passed = false;
}

/**
 * @testcase		utc_application_preference_unset_changed_cb_p1
 * @since_tizen		2.3
 * @type		Positive
 * @description		Unregisters the callback function.
 * @scenario		Sets a integer value and registers a callback function,
 *			and then unregisters the callback function.
 */
int utc_application_preference_unset_changed_cb_p1(void)
{
	int ret;
	const char *key1 = "key1";
	int value1 = 1;
	int value2 = 2;

	preference_changed_unset_passed = true;

	ret = preference_set_int(key1, value1);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_set_changed_cb(key1, pref_changed_unset_cb, NULL);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_unset_changed_cb(key1);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_set_int(key1, value2);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);
	assert_eq_with_exit(preference_changed_unset_passed, true);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_unset_changed_cb_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Unregisters the callback function.
 * @scenario		Calls the preference_unset_changed_cb() with the invalid parameter
 *			that the key is NULL, and then checks the return value.
 */
int utc_application_preference_unset_changed_cb_n1(void)
{
	int ret;

	ret = preference_unset_changed_cb(NULL);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_unset_changed_cb_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Unregisters the callback function.
 * @scenario		Calls the preference_unset_changed_cb() with the invalid parameter,
 *			and then checks the return value.
 */
int utc_application_preference_unset_changed_cb_n2(void)
{
	int ret;
	const char *key = "key";

	ret = preference_unset_changed_cb(key);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NO_KEY);
	normal_exit(0);

	return 0;
}

static bool pref_item_cb(const char *key,void *user_data)
{
	//Headers and Docs are not consistient, CB should be  pref_item_cb(const char *key,void * value,void *user_data)
	//Can't define if void * represents user_data or value because test is failing on  preference_set_int()
	int value1 = -1;
	char *value2 = NULL;
	int *count;
	const char *key1 = "key1";
	const char *key2 = "key2";

	if (!strcmp(key, key1)) {
		///value1 = *((int*) value);
		preference_get_int(key1,&value1);
		if (value1 != foreach_item_int) {
			foreach_item_passed = false;
		}
	}
	else if (!strcmp(key, key2)) {
		//value2 = (char *) value;
		preference_get_string(key2,&value2);
		if (strcmp(value2, foreach_item_string)) {
			foreach_item_passed = false;
		}
		free(value2);
	}
	else {
		foreach_item_passed = false;
	}

	if (user_data == NULL) {
		foreach_item_passed = false;
	} else {
		count = (int *) user_data;
		(*count)++;
	}

	return true;
}

/**
 * @testcase		utc_application_preference_foreach_item_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Retrieves all key-value pairs in the preference by invoking the callback function.
 * @scenario		Sets a integer value and sets a string value,
 *			and then calls the preference_foreach_item().
 */
int utc_application_preference_foreach_item_p(void)
{
	const char *key1 = "key1";
	const char *key2 = "key2";
	int value1 = foreach_item_int;
	const char *value2 = foreach_item_string;
	int count = 0;

	foreach_item_passed = true;

	int ret;

	ret = preference_set_int(key1, value1);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_set_string(key2, value2);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_foreach_item(pref_item_cb, &count);

	assert_eq_with_exit(foreach_item_passed, true);
	assert_eq_with_exit(count, 2);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_foreach_item_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Retrieves all key-value pairs in the preference by invoking the callback function.
 * @scenario		Calls the preference_foreach_item() with the invalid parameter
 *			that the key is NULL, and then checks the return value.
 */
int utc_application_preference_foreach_item_n(void)
{
	int ret;

	ret = preference_foreach_item(NULL, NULL);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_get_type_n
 * @since_tizen		6.0
 * @type		Negative
 * @description		Gets the type of a preference.
 */
int utc_application_preference_get_type_n(void)
{
	preference_type_e type;
	int ret;

	ret = preference_get_type(NULL, &type);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_preference_get_type_p
 * @since_tizen		6.0
 * @type		Positive
 * @description		Gets the type of a preference.
 */
int utc_application_preference_get_type_p(void)
{
	const char *key = "preference_key";
	preference_type_e type;
	int value = 1;
	int ret;

	ret = preference_set_int(key, value);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);

	ret = preference_get_type(key, &type);
	assert_eq_with_exit(ret, PREFERENCE_ERROR_NONE);
	assert_eq_with_exit(type, PREFERENCE_TYPE_INT);
	normal_exit(0);

	return 0;
}
