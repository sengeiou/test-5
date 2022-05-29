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
#include <string.h>
#include <assert.h>
#include "system_info.h"

/* this is the sting with 2^15 elements, really huge */
#define HUGE_STRING_LEN 65536


//& set: SystemInfo


/**
 * @testcase		utc_system_info_get_platform_bool_p
 * @since_tizen		2.3
 * @description		Positive test case of system_info_get_platform_bool
 */
int utc_system_info_get_platform_bool_p(void)
{
    bool supported;
    int retcode = -1;

    retcode = system_info_get_platform_bool("http://tizen.org/feature/fmradio", &supported);
    assert_eq(retcode, SYSTEM_INFO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_system_info_get_platform_bool_n
 * @since_tizen		2.3
 * @description		Negative test case of system_info_get_platform_bool. Invalid parameter
 */
int utc_system_info_get_platform_bool_n(void)
{
    bool supported;
    int retcode = -1;

    retcode = system_info_get_platform_bool("http://tizen.org/feature/invalid_key", &supported);
    assert_neq(retcode, SYSTEM_INFO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_system_info_get_platform_int_p
 * @since_tizen		2.3
 * @description		Positive test case of system_info_get_platform_int
 */
int utc_system_info_get_platform_int_p(void)
{
    int value = -1;

    int ret = system_info_get_platform_int("http://tizen.org/feature/screen.bpp", &value);
    assert_eq(ret, SYSTEM_INFO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_system_info_get_platform_int_n
 * @since_tizen		2.3
 * @description		Negative test case of system_info_get_platform_int. Invalid parameter
 */
int utc_system_info_get_platform_int_n(void)
{
    int value = -1;

    int ret = system_info_get_platform_int("http://tizen.org/feature/invalid_key", &value);
    assert_neq(ret, SYSTEM_INFO_ERROR_NONE);

    return 0;
}

//& purpose: there is no test case for double feature type
/**
 * @testcase		utc_system_info_get_platform_double_p
 * @since_tizen		2.3
 * @description		Positive test case of system_info_get_platform_double
 */
int utc_system_info_get_platform_double_p(void)
{
    return 0;
}

/**
 * @testcase		utc_system_info_get_platform_double_n
 * @since_tizen		2.3
 * @description		Negative test case of system_info_get_platform_double. Invalid parameter
 */
int utc_system_info_get_platform_double_n(void)
{
    double value;
    int retcode = -1;

    retcode = system_info_get_platform_double("http://tizen.org/feature/invalid_key", &value);
    assert_neq(retcode, SYSTEM_INFO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_system_info_get_platform_string_p
 * @since_tizen		2.3
 * @description		Positive test case of system_info_get_platform_string
 */
int utc_system_info_get_platform_string_p(void)
{
	char *value = NULL;
	int string_len = 0;
	int result = 0;
	int key_len;
	int i, ret;
	char *system_keys[] = {
		"http://tizen.org/system/platform.name",
		"http://tizen.org/system/tizenid",
		"http://tizen.org/system/build.date",
		"http://tizen.org/system/build.string",
		"http://tizen.org/system/build.time",
	};

	key_len = sizeof(system_keys)/sizeof(system_keys[0]);

	for (i = 0 ; i < key_len ; i++) {
		ret = system_info_get_platform_string(system_keys[i], &value);
		assert_eq(ret, SYSTEM_INFO_ERROR_NONE);
		assert(value);

		string_len = strlen(value);
		free(value);
		value = NULL;

		result = (string_len < HUGE_STRING_LEN)  &&  (string_len > 0);
		assert_eq(result, 1);
	}

	return 0;
}

/**
 * @testcase		utc_system_info_get_platform_string_n
 * @since_tizen		2.3
 * @description		Negative test case of system_info_get_platform_string. Invalid parameter
 */
int utc_system_info_get_platform_string_n(void)
{
    char *value = NULL;

    int ret = system_info_get_platform_string("http://tizen.org/system/invalid.key", &value);
    assert_neq(ret, SYSTEM_INFO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_system_info_get_custom_bool_n
 * @since_tizen		2.3
 * @description		Negative test case of system_info_get_custom_bool. Invalid parameter
 */
int utc_system_info_get_custom_bool_n(void)
{
    int retcode = -1;

    retcode = system_info_get_custom_bool("custom/feature/invalid_key", NULL);
    assert_neq(retcode, SYSTEM_INFO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_system_info_get_custom_int_n
 * @since_tizen		2.3
 * @description		Negative test case of system_info_get_custom_int. Invalid parameter
 */
int utc_system_info_get_custom_int_n(void)
{
    int retcode = -1;

    retcode = system_info_get_custom_int("custom/feature/invalid_key", NULL);
    assert_neq(retcode, SYSTEM_INFO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_system_info_get_custom_double_n
 * @since_tizen		2.3
 * @description		Negative test case of system_info_get_custom_double. Invalid parameter
 */
int utc_system_info_get_custom_double_n(void)
{
    int retcode = -1;

    retcode = system_info_get_custom_double("custom/feature/invalid_key", NULL);
    assert_neq(retcode, SYSTEM_INFO_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_system_info_get_custom_string_n
 * @since_tizen		2.3
 * @description		Negative test case of system_info_get_custom_string. Invalid parameter
 */
int utc_system_info_get_custom_string_n(void)
{
    char *value = NULL;
    int retcode = -1;

    retcode = system_info_get_custom_string("custom/feature/invalid_key", &value);
    free(value);
    value = NULL;
    assert_neq(retcode, SYSTEM_INFO_ERROR_NONE);

    return 0;
}
