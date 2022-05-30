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
#include <phone_number.h>

//& set: PhonenumberUtils

#define PHONE_NUMBER_TEST_NUMBER "13112345678"
extern bool phn_support_telephony_feature(void);

/**
 * @function		utc_phonenumber_utils_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_phonenumber_utils_startup(void)
{
}

/**
 * @function		utc_phonenumber_utils_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_phonenumber_utils_cleanup(void)
{
}

/**
 * @testcase		utc_phonenumber_utils_phone_number_get_location_from_number_p
 * @since_tizen		2.4
 * @description		Gets the location string from number.
 */
int utc_phonenumber_utils_phone_number_get_location_from_number_p(void)
{
	int i,j;
	int err;

	for (i = 0; i < PHONE_NUMBER_REGION_JORDAN; i++) {
		for (j = 0; j < PHONE_NUMBER_LANG_MAX; j++) {
			char *location = NULL;
			err = phone_number_get_location_from_number(PHONE_NUMBER_TEST_NUMBER, i, j, &location);
			free(location);
			if (phn_support_telephony_feature())
				assert_eq(err, PHONE_NUMBER_ERROR_NONE);
			else
				assert_eq(err, PHONE_NUMBER_ERROR_NOT_SUPPORTED);
		}
	}
	return 0;
}

/**
 * @testcase		utc_phonenumber_utils_phone_number_get_location_from_number2_p
 * @since_tizen		2.4
 * @description		Gets the location string from number.
 */
int utc_phonenumber_utils_phone_number_get_location_from_number2_p(void)
{
	int i,j;
	int err;

	for (i = PHONE_NUMBER_REGION_JORDAN; i < PHONE_NUMBER_REGION_ANDORRA; i++) {
		for (j = 0; j < PHONE_NUMBER_LANG_MAX; j++) {
			char *location = NULL;
			err = phone_number_get_location_from_number(PHONE_NUMBER_TEST_NUMBER, i, j, &location);
			free(location);
			if (phn_support_telephony_feature())
				assert_eq(err, PHONE_NUMBER_ERROR_NONE);
			else
				assert_eq(err, PHONE_NUMBER_ERROR_NOT_SUPPORTED);
		}
	}
	return 0;
}

/**
 * @testcase		utc_phonenumber_utils_phone_number_get_location_from_number_n
 * @since_tizen		2.4
 * @description		Gets the location string from number with invalid parameters.
 */
int utc_phonenumber_utils_phone_number_get_location_from_number_n(void)
{
	int err;
	char *location = NULL;

	err = phone_number_get_location_from_number(NULL, PHONE_NUMBER_REGION_REPUBLIC_OF_KOREA, PHONE_NUMBER_LANG_KOREAN, &location);
	free(location);
	if (phn_support_telephony_feature())
		assert_eq(err, PHONE_NUMBER_ERROR_INVALID_PARAMETER);
	else
		assert_eq(err, PHONE_NUMBER_ERROR_NOT_SUPPORTED);

	err = phone_number_get_location_from_number(PHONE_NUMBER_TEST_NUMBER, -1, PHONE_NUMBER_LANG_KOREAN, &location);
	free(location);
	if (phn_support_telephony_feature())
		assert_eq(err, PHONE_NUMBER_ERROR_INVALID_PARAMETER);
	else
		assert_eq(err, PHONE_NUMBER_ERROR_NOT_SUPPORTED);

	err = phone_number_get_location_from_number(PHONE_NUMBER_TEST_NUMBER, PHONE_NUMBER_REGION_REPUBLIC_OF_KOREA, -1, &location);
	free(location);
	if (phn_support_telephony_feature())
		assert_eq(err, PHONE_NUMBER_ERROR_INVALID_PARAMETER);
	else
		assert_eq(err, PHONE_NUMBER_ERROR_NOT_SUPPORTED);

	err = phone_number_get_location_from_number(PHONE_NUMBER_TEST_NUMBER, PHONE_NUMBER_REGION_REPUBLIC_OF_KOREA, PHONE_NUMBER_LANG_KOREAN, NULL);
	if (phn_support_telephony_feature())
		assert_eq(err, PHONE_NUMBER_ERROR_INVALID_PARAMETER);
	else
		assert_eq(err, PHONE_NUMBER_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_phonenumber_utils_phone_number_get_formatted_number_p
 * @since_tizen		2.4
 * @description		Gets the formatted number that includes the separators (such as dash or space).
 */
int utc_phonenumber_utils_phone_number_get_formatted_number_p(void)
{
	int i;
	int err;

	for (i=0;i<PHONE_NUMBER_REGION_MAX;i++) {
		char *formatted_number = NULL;
		err = phone_number_get_formatted_number(PHONE_NUMBER_TEST_NUMBER, i, &formatted_number);
		free(formatted_number);
		if (phn_support_telephony_feature())
			assert_eq(err, PHONE_NUMBER_ERROR_NONE);
		else
			assert_eq(err, PHONE_NUMBER_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_phonenumber_utils_phone_number_get_formatted_number_n
 * @since_tizen		2.4
 * @description		Gets the formatted number with invalid parameters.
 */
int utc_phonenumber_utils_phone_number_get_formatted_number_n(void)
{
	int err;

	char *formatted_number = NULL;

	err = phone_number_get_formatted_number(NULL, PHONE_NUMBER_REGION_REPUBLIC_OF_KOREA, &formatted_number);
	free(formatted_number);
	if (phn_support_telephony_feature())
		assert_eq(err, PHONE_NUMBER_ERROR_INVALID_PARAMETER);
	else
		assert_eq(err, PHONE_NUMBER_ERROR_NOT_SUPPORTED);

	err = phone_number_get_formatted_number(PHONE_NUMBER_TEST_NUMBER, -1, &formatted_number);
	free(formatted_number);
	if (phn_support_telephony_feature())
		assert_eq(err, PHONE_NUMBER_ERROR_INVALID_PARAMETER);
	else
		assert_eq(err, PHONE_NUMBER_ERROR_NOT_SUPPORTED);

	err = phone_number_get_formatted_number(PHONE_NUMBER_TEST_NUMBER, PHONE_NUMBER_REGION_REPUBLIC_OF_KOREA, NULL);
	if (phn_support_telephony_feature())
		assert_eq(err, PHONE_NUMBER_ERROR_INVALID_PARAMETER);
	else
		assert_eq(err, PHONE_NUMBER_ERROR_NOT_SUPPORTED);

   return 0;
}
