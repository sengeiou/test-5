/*
 * Copyright (c) 2017 Samsung Electronics Co., Ltd
 *
 * Licensed under the Flora License, Version 1.1 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://floralicense.org/license/
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

static const i18n_uversion_info version_info_1 = {
    57, 1, 0, 0
};
static const i18n_uversion_info version_info_2 = {
    234, 55, 12, 56
};

static const char *version_info_1_string = "57.1";
static const char *version_info_2_string = "234.55.12.56";

static int ret = I18N_ERROR_NONE;

/**
 * @function        utc_capi_base_utils_uversion_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_uversion_startup(void)
{
}

/**
 * @function        utc_capi_base_utils_uversion_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_uversion_cleanup(void)
{
}

/**
 * @testcase utc_capi_base_utils_i18n_uversion_get_version_p
 * @since_tizen 4.0
 * @description Calls i18n_uversion_get_version to check whether the result will be equal to
 *              currently used ICU version.
 */
int utc_capi_base_utils_i18n_uversion_get_version_p(void)
{
    i18n_uversion_info dest;
    ret = i18n_uversion_get_version(dest);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uversion_to_string_p
 * @since_tizen 4.0
 * @description Calls i18n_uversion_to_string to check whether the array with ICU version
 *              information will be formatted properly.
 */
int utc_capi_base_utils_i18n_uversion_to_string_p(void)
{
    char dest[I18N_UVERSION_MAX_VERSION_STRING_LENGTH];

    ret = i18n_uversion_to_string(version_info_1, dest);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strlen(version_info_1_string), strlen(dest));
    assert_eq(memcmp(dest, version_info_1_string, sizeof(char) * strlen(dest)), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uversion_to_string_p2
 * @since_tizen 4.0
 * @description Calls i18n_uversion_to_string to check whether the array with ICU version
 *              information will be formatted properly.
 */
int utc_capi_base_utils_i18n_uversion_to_string_p2(void)
{
    char dest[I18N_UVERSION_MAX_VERSION_STRING_LENGTH];

    ret = i18n_uversion_to_string(version_info_2, dest);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strlen(version_info_2_string), strlen(dest));
    assert_eq(memcmp(dest, version_info_2_string, sizeof(char) * strlen(dest)), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uversion_from_string_p
 * @since_tizen 4.0
 * @description Calls i18n_uversion_from_string to check whether the string with dotted-decimal
 *              version information will be parsed properly.
 */
int utc_capi_base_utils_i18n_uversion_from_string_p(void)
{
    i18n_uversion_info dest;

    ret = i18n_uversion_from_string(version_info_1_string, dest);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(memcmp(dest, version_info_1, sizeof(dest)), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uversion_from_string_p2
 * @since_tizen 4.0
 * @description Calls i18n_uversion_from_string to check whether the string with dotted-decimal
 *              version information will be parsed properly.
 */
int utc_capi_base_utils_i18n_uversion_from_string_p2(void)
{
    i18n_uversion_info dest;

    ret = i18n_uversion_from_string(version_info_2_string, dest);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(memcmp(dest, version_info_2, sizeof(dest)), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uversion_from_ustring_p
 * @since_tizen 4.0
 * @description Calls i18n_uversion_from_ustring to check whether the Unicode string with
 *              dotted-decimal version information will be parsed properly.
 */
int utc_capi_base_utils_i18n_uversion_from_ustring_p(void)
{
    i18n_uversion_info dest;
    i18n_uchar u_version[I18N_UVERSION_MAX_VERSION_STRING_LENGTH];

    i18n_ustring_copy_ua(u_version, version_info_1_string);
    ret = i18n_uversion_from_ustring(u_version, dest);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(memcmp(dest, version_info_1, sizeof(dest)), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uversion_from_ustring_p2
 * @since_tizen 4.0
 * @description Calls i18n_uversion_from_ustring to check whether the Unicode string with
 *              dotted-decimal version information will be parsed properly.
 */
int utc_capi_base_utils_i18n_uversion_from_ustring_p2(void)
{
    i18n_uversion_info dest;
    i18n_uchar u_version[I18N_UVERSION_MAX_VERSION_STRING_LENGTH];

    i18n_ustring_copy_ua(u_version, version_info_2_string);
    ret = i18n_uversion_from_ustring(u_version, dest);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(memcmp(dest, version_info_2, sizeof(dest)), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uversion_get_version_n
 * @since_tizen 4.0
 * @description Calls i18n_uversion_get_version with invalid @a version_array and checks
 *              whether the function returns an error code.
 */
int utc_capi_base_utils_i18n_uversion_get_version_n(void)
{
    ret = i18n_uversion_get_version(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uversion_from_string_n
 * @since_tizen 4.0
 * @description Calls i18n_uversion_from_string with invalid @a version_string and checks
 *              whether the function returns an error code.
 */
int utc_capi_base_utils_i18n_uversion_from_string_n(void)
{
    i18n_uversion_info dest;
    ret = i18n_uversion_from_string(NULL, dest);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uversion_from_string_n2
 * @since_tizen 4.0
 * @description Calls i18n_uversion_from_string with invalid @a version_array and checks
 *              whether the function returns an error code.
 */
int utc_capi_base_utils_i18n_uversion_from_string_n2(void)
{
    ret = i18n_uversion_from_string(version_info_1_string, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uversion_from_ustring_n
 * @since_tizen 4.0
 * @description Calls i18n_uversion_from_ustring with invalid @a version_string and checks
 *              whether the function returns an error code.
 */
int utc_capi_base_utils_i18n_uversion_from_ustring_n(void)
{
    i18n_uversion_info dest;
    ret = i18n_uversion_from_ustring(NULL, dest);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uversion_from_ustring_n2
 * @since_tizen 4.0
 * @description Calls i18n_uversion_from_ustring with invalid @a version_array and checks
 *              whether the function returns an error code.
 */
int utc_capi_base_utils_i18n_uversion_from_ustring_n2(void)
{
    i18n_uchar u_version[I18N_UVERSION_MAX_VERSION_STRING_LENGTH];

    i18n_ustring_copy_ua(u_version, version_info_1_string);
    ret = i18n_uversion_from_ustring(u_version, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uversion_to_string_n
 * @since_tizen 4.0
 * @description Calls i18n_uversion_to_string with invalid @a version_string and checks
 *              whether the function returns an error code.
 */
int utc_capi_base_utils_i18n_uversion_to_string_n(void)
{
    ret = i18n_uversion_to_string(version_info_1, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uversion_to_string_n2
 * @since_tizen 4.0
 * @description Calls i18n_uversion_to_string with invalid @a version_array and checks
 *              whether the function returns an error code.
 */
int utc_capi_base_utils_i18n_uversion_to_string_n2(void)
{
    char dest[I18N_UVERSION_MAX_VERSION_STRING_LENGTH];

    ret = i18n_uversion_to_string(NULL, dest);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
