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
#include <system_info.h>
#include <phone_number.h>
#include <dlog.h>

//& set: PhonenumberUtils

#define TEST_BLOCKING_RULE_COUNT 8

typedef struct {
	char *number;
	phone_number_blocking_rule_match_type_e match_type;
} phn_blocking_rule_s;

phn_blocking_rule_s blocking_rules[TEST_BLOCKING_RULE_COUNT] = {
	{"+821092381673", PHONE_NUMBER_MATCH_TYPE_EXACTLY},
	{"010-1234-1234", PHONE_NUMBER_MATCH_TYPE_EXACTLY},
	{"01028850863", PHONE_NUMBER_MATCH_TYPE_EXACTLY},
	{"07015001500", PHONE_NUMBER_MATCH_TYPE_EXACTLY},
	{"070", PHONE_NUMBER_MATCH_TYPE_STARTS_WITH},
	{"1588", PHONE_NUMBER_MATCH_TYPE_STARTS_WITH},
	{"0909", PHONE_NUMBER_MATCH_TYPE_ENDS_WITH},
	{"070", PHONE_NUMBER_MATCH_TYPE_INCLUDES},
};

extern bool phn_support_telephony_feature(void);

static int _startup_err;

static int _phn_tc_add_blocking_rules(phn_blocking_rule_s *rules, int length)
{
	int ret = 0;
	int idx = 0;
	phone_number_blocking_rule_h rule = NULL;
	do {
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_create(&rule))) break;
		for (idx = 0; idx < length; idx++) {
			if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_set_number(rule, rules[idx].number))) break;
			if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_set_match_type(rule, rules[idx].match_type))) break;
			if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_add_blocking_rule(rule))) break;
		}
		if (PHONE_NUMBER_ERROR_NONE != ret) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_destroy(rule))) break;
		rule = NULL;
	} while(0);

	phone_number_blocking_rule_destroy(rule);
	return ret;
}

static int _phn_tc_free_blocking_rules(phone_number_blocking_rule_h *rules, int length)
{
	int ret = 0;
	int idx = 0;

	for (idx = 0; idx < length; idx++)
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_destroy(rules[idx]))) break;

	return ret;
}

static int _phn_tc_remove_blocking_rules(phone_number_blocking_rule_h *rules, int length)
{
	int ret = 0;
	int idx = 0;

	for (idx = 0; idx < length; idx++)
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_remove_blocking_rule(rules[idx]))) break;

	return ret;
}

static int _phn_tc_compare_blocking_rules(phn_blocking_rule_s rule1, phone_number_blocking_rule_h rule2)
{
	int ret = 0;
	char *number = NULL;
	phone_number_blocking_rule_match_type_e match_type = 0;

	do {
       	if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_get_number(rule2, &number))) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_get_match_type(rule2, &match_type))) break;

		if (0 != strncmp(rule1.number, number, strlen(rule1.number)) || rule1.match_type != match_type) {
			ret = -1;
			break;
		}
	} while(0);
	free(number);
	return ret;
}


/**
 * @function		utc_phonenumber_utils_block_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_phonenumber_utils_blocking_rule_startup(void)
{
	_startup_err = PHONE_NUMBER_ERROR_NONE;
	_startup_err = phone_number_connect();
	if (PHONE_NUMBER_ERROR_NOT_SUPPORTED == _startup_err
		&& false == phn_support_telephony_feature())
		_startup_err = PHONE_NUMBER_ERROR_NONE;
}

/**
 * @function		utc_phonenumber_utils_block_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_phonenumber_utils_blocking_rule_cleanup(void)
{
	phone_number_disconnect();
}

/**
 * @testcase		utc_phonenumber_utils_blocking_rule_create_p
 * @since_tizen		4.0
 * @description		Creates a blocking rule handle
 */
int utc_phonenumber_utils_blocking_rule_create_p(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int ret = 0;
	phone_number_blocking_rule_h rule = NULL;

	if (false == phn_support_telephony_feature()) {
		ret = phone_number_blocking_rule_create(&rule);
		assert_eq(ret, PHONE_NUMBER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_create(&rule))) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_destroy(rule))) break;
		rule = NULL;
		return 0;
	} while(0);
	phone_number_blocking_rule_destroy(rule);
	return ret;
}

/**
 * @testcase		utc_phonenumber_utils_blocking_rule_destroy_p
 * @since_tizen		4.0
 * @description		Destroys a blocking rule and releases its all resources.
 */
int utc_phonenumber_utils_blocking_rule_destroy_p(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int ret = 0;
	phone_number_blocking_rule_h rule = NULL;

	if (false == phn_support_telephony_feature()) {
		ret = phone_number_blocking_rule_destroy(rule);
		assert_eq(ret, PHONE_NUMBER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_create(&rule))) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_destroy(rule))) break;
		rule = NULL;
		return 0;
	} while(0);
	phone_number_blocking_rule_destroy(rule);
	return ret;
}

/**
 * @testcase		utc_phonenumber_utils_blocking_rule_get_number_p
 * @since_tizen		4.0
 * @description		Gets a number from the blocking rule.
 */
int utc_phonenumber_utils_blocking_rule_get_number_p(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int ret = 0;
	char *number = NULL;
	phone_number_blocking_rule_h rule = NULL;

	if (false == phn_support_telephony_feature()) {
		ret = phone_number_blocking_rule_get_number(rule, &number);
		assert_eq(ret, PHONE_NUMBER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_create(&rule))) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_set_number(rule, blocking_rules[0].number))) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_get_number(rule, &number))) break;
		if (0 != strncmp(number, blocking_rules[0].number, strlen(blocking_rules[0].number))) {
			ret = -1;
			break;
		}
		free(number);
		number = NULL;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_destroy(rule))) break;
		rule = NULL;
	} while(0);

	free(number);
	phone_number_blocking_rule_destroy(rule);
	return ret;
}

/**
 * @testcase		utc_phonenumber_utils_blocking_rule_get_match_type_p
 * @since_tizen		4.0
 * @description		Gets a match type from the blocking rule.
 */
int utc_phonenumber_utils_blocking_rule_get_match_type_p(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int ret = 0;
	phone_number_blocking_rule_match_type_e match_type = -1;
	phone_number_blocking_rule_h rule = NULL;

	if (false == phn_support_telephony_feature()) {
		ret = phone_number_blocking_rule_get_match_type(rule, &match_type);
		assert_eq(ret, PHONE_NUMBER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_create(&rule))) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_set_match_type(rule, blocking_rules[0].match_type))) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_get_match_type(rule, &match_type))) break;
		if (blocking_rules[0].match_type != match_type) {
			ret = -1;
			break;
		}
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_destroy(rule))) break;
		rule = NULL;
	} while(0);

	phone_number_blocking_rule_destroy(rule);
	return ret;
}

/**
 * @testcase		utc_phonenumber_utils_blocking_rule_set_number_p
 * @since_tizen		4.0
 * @description		Sets a number to the blocking rule.
 */
int utc_phonenumber_utils_blocking_rule_set_number_p(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int ret = 0;
	char *number = NULL;
	phone_number_blocking_rule_h rule = NULL;

	if (false == phn_support_telephony_feature()) {
		ret = phone_number_blocking_rule_set_number(rule, blocking_rules[0].number);
		assert_eq(ret, PHONE_NUMBER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_create(&rule))) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_set_number(rule, blocking_rules[0].number))) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_get_number(rule, &number))) break;
		if (0 != strncmp(number, blocking_rules[0].number, strlen(blocking_rules[0].number))) {
			ret = -1;
			break;
		}
		free(number);
		number = NULL;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_destroy(rule))) break;
		rule = NULL;
	} while(0);

	free(number);
	phone_number_blocking_rule_destroy(rule);
	return ret;
}

/**
 * @testcase		utc_phonenumber_utils_blocking_rule_set_match_type_p
 * @since_tizen		4.0
 * @description		Sets a match type to the blocking rule.
 */
int utc_phonenumber_utils_blocking_rule_set_match_type_p(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int ret = 0;
	phone_number_blocking_rule_match_type_e match_type = -1;
	phone_number_blocking_rule_h rule = NULL;

	if (false == phn_support_telephony_feature()) {
		ret = phone_number_blocking_rule_set_match_type(rule, blocking_rules[0].match_type);
		assert_eq(ret, PHONE_NUMBER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_create(&rule))) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_set_match_type(rule, blocking_rules[0].match_type))) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_get_match_type(rule, &match_type))) break;
		if (blocking_rules[0].match_type != match_type) {
			ret = -1;
			break;
		}
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_destroy(rule))) break;
		rule = NULL;
	} while(0);

	phone_number_blocking_rule_destroy(rule);
	return ret;
}

/**
 * @testcase		utc_phonenumber_utils_blocking_rule_create_n
 * @since_tizen		4.0
 * @description		Creates a blocking rule handle
 */
int utc_phonenumber_utils_blocking_rule_create_n(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int ret = 0;

	ret = phone_number_blocking_rule_create(NULL);
	if (phn_support_telephony_feature())
		assert_eq(PHONE_NUMBER_ERROR_INVALID_PARAMETER, ret);
	else
		assert_eq(PHONE_NUMBER_ERROR_NOT_SUPPORTED, ret);
	return 0;
}

/**
 * @testcase		utc_phonenumber_utils_blocking_rule_destroy_n
 * @since_tizen		4.0
 * @description		Destroys a blocking rule and releases its all resources.
 */
int utc_phonenumber_utils_blocking_rule_destroy_n(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int ret = 0;

	ret = phone_number_blocking_rule_destroy(NULL);
	if (phn_support_telephony_feature())
		assert_eq(PHONE_NUMBER_ERROR_INVALID_PARAMETER, ret);
	else
		assert_eq(PHONE_NUMBER_ERROR_NOT_SUPPORTED, ret);
	return 0;
}

/**
 * @testcase		utc_phonenumber_utils_blocking_rule_get_number_n
 * @since_tizen		4.0
 * @description		Gets a number from the blocking rule.
 */
int utc_phonenumber_utils_blocking_rule_get_number_n(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int ret = 0;
	char *number = NULL;
	phone_number_blocking_rule_h rule = NULL;

	if (false == phn_support_telephony_feature()) {
		ret = phone_number_blocking_rule_get_number(NULL, &number);
		assert_eq(ret, PHONE_NUMBER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (PHONE_NUMBER_ERROR_INVALID_PARAMETER != (ret = phone_number_blocking_rule_get_number(NULL, &number))) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_create(&rule))) break;
		if (PHONE_NUMBER_ERROR_INVALID_PARAMETER != (ret = phone_number_blocking_rule_get_number(rule, NULL))) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_destroy(rule))) break;
		rule = NULL;

		return 0;
	} while(0);

	free(number);
	phone_number_blocking_rule_destroy(rule);
	return -1;
}

/**
 * @testcase		utc_phonenumber_utils_blocking_rule_get_match_type_n
 * @since_tizen		4.0
 * @description		Gets a match type from the blocking rule.
 */
int utc_phonenumber_utils_blocking_rule_get_match_type_n(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int ret = 0;
	phone_number_blocking_rule_match_type_e match_type = 0;
	phone_number_blocking_rule_h rule = NULL;

	if (false == phn_support_telephony_feature()) {
		ret = phone_number_blocking_rule_get_match_type(NULL, &match_type);
		assert_eq(ret, PHONE_NUMBER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (PHONE_NUMBER_ERROR_INVALID_PARAMETER != (ret = phone_number_blocking_rule_get_match_type(NULL, &match_type))) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_create(&rule))) break;
		if (PHONE_NUMBER_ERROR_INVALID_PARAMETER != (ret = phone_number_blocking_rule_get_match_type(rule, NULL))) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_destroy(rule))) break;
		rule = NULL;

		return 0;
	} while(0);

	phone_number_blocking_rule_destroy(rule);
	return -1;
}

/**
 * @testcase		utc_phonenumber_utils_blocking_rule_set_number_n
 * @since_tizen		4.0
 * @description		Sets a number to the blocking rule.
 */
int utc_phonenumber_utils_blocking_rule_set_number_n(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int ret = 0;
	phone_number_blocking_rule_h rule = NULL;

	if (false == phn_support_telephony_feature()) {
		ret = phone_number_blocking_rule_set_number(rule, NULL);
		assert_eq(ret, PHONE_NUMBER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (PHONE_NUMBER_ERROR_INVALID_PARAMETER != (ret = phone_number_blocking_rule_set_number(NULL, blocking_rules[0].number))) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_create(&rule))) break;
		if (PHONE_NUMBER_ERROR_INVALID_PARAMETER != (ret = phone_number_blocking_rule_set_number(rule, NULL))) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_destroy(rule))) break;
		rule = NULL;

		return 0;
	} while(0);

	phone_number_blocking_rule_destroy(rule);
	return -1;
}

/**
 * @testcase		utc_phonenumber_utils_blocking_rule_set_match_type_n
 * @since_tizen		4.0
 * @description		Sets a match type to the blocking rule.
 */
int utc_phonenumber_utils_blocking_rule_set_match_type_n(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int ret = 0;
	phone_number_blocking_rule_h rule = NULL;

	if (false == phn_support_telephony_feature()) {
		ret = phone_number_blocking_rule_set_match_type(NULL, blocking_rules[0].match_type);
		assert_eq(ret, PHONE_NUMBER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (PHONE_NUMBER_ERROR_INVALID_PARAMETER != (ret = phone_number_blocking_rule_set_match_type(NULL, blocking_rules[0].match_type))) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_create(&rule))) break;
		if (PHONE_NUMBER_ERROR_INVALID_PARAMETER != (ret = phone_number_blocking_rule_set_match_type(rule, PHONE_NUMBER_MATCH_TYPE_EXACTLY - 1))) break;
		if (PHONE_NUMBER_ERROR_INVALID_PARAMETER != (ret = phone_number_blocking_rule_set_match_type(rule, PHONE_NUMBER_MATCH_TYPE_ENDS_WITH + 1))) break;
		if (PHONE_NUMBER_ERROR_NONE != (ret = phone_number_blocking_rule_destroy(rule))) break;
		rule = NULL;

		return 0;
	} while(0);

	phone_number_blocking_rule_destroy(rule);
	return -1;
}

