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

//& set: PhonenumberUtils

#define PHONE_NUMBER_TEST_NUMBER "13112345678"
static int _startup_err;

#define PHN_FEATURE_TELEPHONY "http://tizen.org/feature/network.telephony"

bool phn_support_telephony_feature(void)
{
	int ret;
	static bool feature_checked = false;
	static bool telephony_feature = false;

	if (feature_checked)
		return telephony_feature;

	ret = system_info_get_platform_bool(PHN_FEATURE_TELEPHONY, &telephony_feature);
	if (SYSTEM_INFO_ERROR_NONE != ret) {
		return telephony_feature;
	}

	feature_checked = true;
	return telephony_feature;
}

/**
 * @function		utc_phonenumber_utils_service_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_phonenumber_utils_service_startup(void)
{
	_startup_err = PHONE_NUMBER_ERROR_NONE;
	_startup_err = phone_number_connect();
	if (PHONE_NUMBER_ERROR_NOT_SUPPORTED == _startup_err
		&& false == phn_support_telephony_feature())
		_startup_err = PHONE_NUMBER_ERROR_NONE;
}

/**
 * @function		utc_phonenumber_utils_service_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_phonenumber_utils_service_cleanup(void)
{
	phone_number_disconnect();
}


/**
 * @testcase		utc_phonenumber_utils_service_phone_number_disconnect_p
 * @since_tizen		3.0
 * @description		Disconnects from the phonenumber-utils service.
 */
int utc_phonenumber_utils_service_phone_number_disconnect_p(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int err;

	err = phone_number_disconnect();
	assert_eq(err, PHONE_NUMBER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_phonenumber_utils_service_phone_number_get_location_from_number_p
 * @since_tizen		3.0
 * @description		Gets the location string from number.
 */
int utc_phonenumber_utils_service_phone_number_get_location_from_number_p(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int i,j;
	int err;

	for (i = 0; i < PHONE_NUMBER_REGION_ANDORRA; i++) {
		for (j = 0; j < PHONE_NUMBER_LANG_MAX; j++) {
			char *location = NULL;
			err = phone_number_get_location_from_number(PHONE_NUMBER_TEST_NUMBER, i, j, &location);
			free(location);
			assert_eq(err, PHONE_NUMBER_ERROR_NONE);
		}
	}
	return 0;
}

/**
 * @testcase		utc_phonenumber_utils_service_phone_number_get_location_from_number2_p
 * @since_tizen		3.0
 * @description		Gets the location string from number.
 */
int utc_phonenumber_utils_service_phone_number_get_location_from_number2_p(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int i,j;
	int err;

	for (i = PHONE_NUMBER_REGION_ANDORRA; i < PHONE_NUMBER_REGION_MAX; i++) {
		for (j = 0; j < PHONE_NUMBER_LANG_MAX; j++) {
			char *location = NULL;
			err = phone_number_get_location_from_number(PHONE_NUMBER_TEST_NUMBER, i, j, &location);
			free(location);
			assert_eq(err, PHONE_NUMBER_ERROR_NONE);
		}
	}
	return 0;
}

/**
 * @testcase		utc_phonenumber_utils_service_phone_number_get_location_from_number_n
 * @since_tizen		3.0
 * @description		Gets the location string from number with invalid parameters.
 */
int utc_phonenumber_utils_service_phone_number_get_location_from_number_n(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int err;
	char *location = NULL;

	err = phone_number_get_location_from_number(NULL, PHONE_NUMBER_REGION_REPUBLIC_OF_KOREA, PHONE_NUMBER_LANG_KOREAN, &location);
	free(location);
	assert_eq(err, PHONE_NUMBER_ERROR_INVALID_PARAMETER);

	err = phone_number_get_location_from_number(PHONE_NUMBER_TEST_NUMBER, -1, PHONE_NUMBER_LANG_KOREAN, &location);
	free(location);
		assert_eq(err, PHONE_NUMBER_ERROR_INVALID_PARAMETER);

	err = phone_number_get_location_from_number(PHONE_NUMBER_TEST_NUMBER, PHONE_NUMBER_REGION_REPUBLIC_OF_KOREA, -1, &location);
	free(location);
		assert_eq(err, PHONE_NUMBER_ERROR_INVALID_PARAMETER);

	err = phone_number_get_location_from_number(PHONE_NUMBER_TEST_NUMBER, PHONE_NUMBER_REGION_REPUBLIC_OF_KOREA, PHONE_NUMBER_LANG_KOREAN, NULL);
		assert_eq(err, PHONE_NUMBER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_phonenumber_utils_service_phone_number_get_formatted_number_p
 * @since_tizen		3.0
 * @description		Gets the formatted number that includes the separators (such as dash or space).
 */
int utc_phonenumber_utils_service_phone_number_get_formatted_number_p(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int i;
	int err;

	for (i=0;i<PHONE_NUMBER_REGION_MAX;i++) {
		char *formatted_number = NULL;
		err = phone_number_get_formatted_number(PHONE_NUMBER_TEST_NUMBER, i, &formatted_number);
		free(formatted_number);
			assert_eq(err, PHONE_NUMBER_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_phonenumber_utils_service_phone_number_get_formatted_number_n
 * @since_tizen		3.0
 * @description		Gets the formatted number with invalid parameters.
 */
int utc_phonenumber_utils_service_phone_number_get_formatted_number_n(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int err;

	char *formatted_number = NULL;

	err = phone_number_get_formatted_number(NULL, PHONE_NUMBER_REGION_REPUBLIC_OF_KOREA, &formatted_number);
	free(formatted_number);
	assert_eq(err, PHONE_NUMBER_ERROR_INVALID_PARAMETER);

	err = phone_number_get_formatted_number(PHONE_NUMBER_TEST_NUMBER, -1, &formatted_number);
	free(formatted_number);
	assert_eq(err, PHONE_NUMBER_ERROR_INVALID_PARAMETER);

	err = phone_number_get_formatted_number(PHONE_NUMBER_TEST_NUMBER, PHONE_NUMBER_REGION_REPUBLIC_OF_KOREA, NULL);
	assert_eq(err, PHONE_NUMBER_ERROR_INVALID_PARAMETER);

   return 0;
}

/**
 * @testcase		utc_phonenumber_utils_service_phone_number_get_normalized_number_p
 * @since_tizen		3.0
 * @description		Get normalized number
 */
int utc_phonenumber_utils_service_phone_number_get_normalized_number_p(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int err;
	char *normalized_number = NULL;

	err = phone_number_get_normalized_number(PHONE_NUMBER_TEST_NUMBER, &normalized_number);
	free(normalized_number);
	if (phn_support_telephony_feature())
		assert_eq(err, PHONE_NUMBER_ERROR_NONE);
	else
		assert_eq(err, PHONE_NUMBER_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_phonenumber_utils_service_phone_number_get_normalized_number_n
 * @since_tizen		3.0
 * @description		Get normalized number with invalid parameters
 */
int utc_phonenumber_utils_service_phone_number_get_normalized_number_n(void)
{
	assert_eq(_startup_err, PHONE_NUMBER_ERROR_NONE);
	int err;
	char *normalized_number = NULL;

	err = phone_number_get_normalized_number(NULL, &normalized_number);
	free(normalized_number);
	if (phn_support_telephony_feature())
		assert_eq(err, PHONE_NUMBER_ERROR_INVALID_PARAMETER);
	else
		assert_eq(err, PHONE_NUMBER_ERROR_NOT_SUPPORTED);

	err = phone_number_get_normalized_number(PHONE_NUMBER_TEST_NUMBER, NULL);
	if (phn_support_telephony_feature())
		assert_eq(err, PHONE_NUMBER_ERROR_INVALID_PARAMETER);
	else
		assert_eq(err, PHONE_NUMBER_ERROR_NOT_SUPPORTED);

	return 0;
}

