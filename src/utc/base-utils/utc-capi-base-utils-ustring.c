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
#include <utils_i18n.h>
#include <string.h>

#define STR_LEN 64

//& set: capi-base-utils-string

static i18n_uchar g_ustr[STR_LEN] = { 0, };
static const i18n_uchar g_const_ustr[STR_LEN] = { 0, };
static i18n_uchar g_target[STR_LEN] = { 0, };
static int g_str_len = -1;
static char *g_astr = "Test String";

static i18n_uchar g_pattern_target[STR_LEN];
static i18n_uchar g_pattern[16];

/**
 * @function        utc_capi_base_utils_string_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_string_startup(void)
{
    char *tgtstr = "The quick brown fox jumped over the lazy fox";
    char *patstr = "fox";
    i18n_ustring_copy_ua(g_pattern_target, tgtstr);
    i18n_ustring_copy_ua(g_pattern, patstr);

    i18n_ustring_copy_ua_n(g_ustr, g_astr, strlen(g_astr));
    i18n_ustring_copy_ua_n(g_target, g_astr, strlen(g_astr));
    g_str_len = i18n_ustring_get_length(g_ustr);
}

/**
 * @function        utc_capi_base_utils_string_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_string_cleanup(void)
{
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_get_length_p
 * @since_tizen     2.3
 * @description     Gets length of the given string and
 *                  check whether no error occurred and the length is correct.
 */
int utc_capi_base_utils_i18n_ustring_get_length_p(void)
{
    const i18n_uchar ustring[] = { 'T', 'I', 'Z', 'E', 'N', '\0' };

    int32_t length = i18n_ustring_get_length(ustring);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(length, 5);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_get_length_n
 * @since_tizen     2.3
 * @description     Gets length of the empty string, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_get_length_n(void)
{
    int err_code = I18N_ERROR_NONE;

    i18n_ustring_get_length(NULL);
    err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_count_char32_p
 * @since_tizen     2.3
 * @description     Gets count of characters in the given string and
 *                  check whether no error occurred and the length is correct.
 */
int utc_capi_base_utils_i18n_ustring_count_char32_p(void)
{
    int32_t len = 16;
    int32_t num_of_code_points;

    num_of_code_points = i18n_ustring_count_char32(g_ustr, len);
    assert_eq(num_of_code_points, 16);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_count_char32_n
 * @since_tizen     2.3
 * @description     Gets count of characters in the empty string, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_count_char32_n(void)
{
    int32_t len = 16;

    i18n_ustring_count_char32(NULL, len);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_has_more_char32_than_p
 * @since_tizen     2.3
 * @description     Checks whether the given string has more than specified number of characters.
 *                  Checks whether no error occurred and the length is correct.
 */
int utc_capi_base_utils_i18n_ustring_has_more_char32_than_p(void)
{
    int32_t len = -1;
    int32_t number = 100;
    i18n_ubool result = false;

    result = i18n_ustring_has_more_char32_than(g_const_ustr, len, number);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(result, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_has_more_char32_than_n
 * @since_tizen     2.3
 * @description     Checks whether an invalid string has more than specified
 *                  number of characters, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_has_more_char32_than_n(void)
{
    int32_t len = -1;
    int32_t number = 100;

    i18n_ustring_has_more_char32_than(NULL, len, number);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_cat_p
 * @since_tizen     2.3
 * @description     Concatenate string with another given string and
 *                  check whether no error occurred and compare strings.
 */
int utc_capi_base_utils_i18n_ustring_cat_p(void)
{
    char *string = "tizen";
    i18n_uchar src[64] = { 0, };
    i18n_uchar dest[64] = { 0, };
    int32_t result = 0;

    // copy string to src
    i18n_ustring_copy_ua_n(src, string, strlen(string));

    // cat src to dest
    i18n_ustring_cat(dest, (const i18n_uchar *)src);

    // compare dest with src
    result = i18n_ustring_compare((const i18n_uchar *)src, (const i18n_uchar *)dest);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    assert_eq(result, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_cat_n
 * @since_tizen     2.3
 * @description     Concatenate string with another empty string, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_cat_n(void)
{
    i18n_ustring_cat(NULL, NULL);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_cat_n_p
 * @since_tizen     2.3
 * @description     Concatenate string with another given string and
 *                  check whether no error occurred and compare strings.
 */
int utc_capi_base_utils_i18n_ustring_cat_n_p(void)
{
    char *string = "tizen";
    i18n_uchar src[64] = { 0, };
    i18n_uchar dest[64] = { 0, };
    int32_t result = 0;

    // copy string to src
    i18n_ustring_copy_ua_n(src, string, strlen(string));

    // cat src to dest
    i18n_ustring_cat_n(dest, (const i18n_uchar *)src, sizeof(dest) / sizeof(dest[0]));
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    // compare dest with src
    result = i18n_ustring_compare((const i18n_uchar *)src, (const i18n_uchar *)dest);

    assert_eq(result, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_cat_n_n
 * @since_tizen     2.3
 * @description     Concatenate string with another empty string, so error is expected.
*/
int utc_capi_base_utils_i18n_ustring_cat_n_n(void)
{
    i18n_ustring_cat_n(NULL, NULL, 0);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_string_p
 * @since_tizen     2.3
 * @description     Finds first occurrence of substring in string.
 *                  Checks whether no error occurred and compare pointers.
 */
int utc_capi_base_utils_i18n_ustring_string_p(void)
{
    const i18n_uchar str[64] = { 0, };
    const i18n_uchar sub_str[64] = { 0, };
    i18n_uchar *ptr = NULL;

    ptr = i18n_ustring_string(str, sub_str);
    assert_eq(ptr, str);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_string_n
 * @since_tizen     2.3
 * @description     Finds first occurrence of substring in string, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_string_n(void)
{
    const i18n_uchar sub_str[64] = { 0, };

    i18n_ustring_string(NULL, sub_str);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_find_first_p
 * @since_tizen     2.3
 * @description     Finds first occurrence of substring in string.
 *                  Checks whether no error occurred and compare pointers.
 */
int utc_capi_base_utils_i18n_ustring_find_first_p(void)
{
    char *string = "tizen";
    i18n_uchar ustring[64] = { 0, };
    char *sub_string = "a";
    i18n_uchar sub_ustring[64] = { 0, };
    i18n_uchar *result = NULL;

    // copy string to src
    i18n_ustring_copy_ua_n(ustring, string, strlen(string));
    i18n_ustring_copy_ua_n(sub_ustring, sub_string, strlen(sub_string));

    // find first occurrence
    result = i18n_ustring_find_first(ustring, i18n_ustring_get_length((const i18n_uchar *)ustring), sub_ustring, i18n_ustring_get_length((const i18n_uchar *)sub_ustring));

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    assert_eq(result, NULL);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_find_first_n
 * @since_tizen     2.3
 * @description     Finds first occurrence of substring in invalid string, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_find_first_n(void)
{
    i18n_uchar sub_ustring[64] = { 0, };
    i18n_uchar *result = NULL;

    result = i18n_ustring_find_first(NULL, 0, sub_ustring, i18n_ustring_get_length((const i18n_uchar *)sub_ustring));

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(result, NULL);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_char_p
 * @since_tizen     2.3
 * @description     Finds first occurrence of BMP code in the string, and
 *                  check error.
 */
int utc_capi_base_utils_i18n_ustring_char_p(void)
{
    const i18n_uchar string[4] = { 0x0041, 0x0042, 0x0043, 0x0000 }; // A, B, C, NULL
    i18n_uchar code_point = 0x0044; // D
    i18n_uchar *result = NULL;

    result = i18n_ustring_char(string, code_point);
    assert_eq(result, NULL);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_char_n
 * @since_tizen     2.3
 * @description     Finds first occurrence of BMP code in invalid string, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_char_n(void)
{
    i18n_uchar code_point = 0x0044; // D

    i18n_ustring_char(NULL, code_point);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_char32_p
 * @since_tizen     2.3
 * @description     Finds first occurrence of code point in string and
 *                  check error.
 */
int utc_capi_base_utils_i18n_ustring_char32_p(void)
{
    const i18n_uchar string[4] = { 0x0041, 0x0042, 0x0043, 0x0000 }; // A, B, C, NUL
    i18n_uchar32 code_point = 0x00000044; // D
    i18n_uchar *result = NULL;

    result = i18n_ustring_char32(string, code_point);
    assert_eq(result, NULL);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_char32_n
 * @since_tizen     2.3
 * @description     Finds first occurrence of code point in invalid string, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_char32_n(void)
{
    i18n_uchar32 code_point = 0x00000044; // D

    i18n_ustring_char32(NULL, code_point);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_r_string_p
 * @since_tizen     2.3
 * @description     Finds last occurrence of a substring in a string,
 *                  compare pointers and check error.
 */
int utc_capi_base_utils_i18n_ustring_r_string_p(void)
{
    i18n_uchar str[64];
    i18n_ustring_copy_ua(str, "tizen mobile platform for mobile phone");
    i18n_uchar sub_str[64];
    i18n_ustring_copy_ua(sub_str, "mobile");

    i18n_uchar *ptr = i18n_ustring_r_string(str, sub_str);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(ptr, str + 26);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_r_string_n
 * @since_tizen     2.3
 * @description     Finds last occurrence of an invalid substring in a string,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_r_string_n(void)
{
    const i18n_uchar sub_str[64] = { 0, };
    i18n_uchar *ptr = NULL;

    ptr = i18n_ustring_r_string(NULL, sub_str);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(ptr, NULL);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_find_last_p
 * @since_tizen     2.3
 * @description     Finds last occurrence of a substring in a string, compare pointers and
 *                  check error.
 */
int utc_capi_base_utils_i18n_ustring_find_last_p(void)
{
    i18n_uchar str[64];
    i18n_ustring_copy_ua(str, "tizen mobile platform for mobile phone");
    i18n_uchar sub_str[64];
    i18n_ustring_copy_ua(sub_str, "mobile");

    i18n_uchar *ptr = i18n_ustring_find_last(str, -1, sub_str, -1);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(ptr, str + 26);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_find_last_n
 * @since_tizen     2.3
 * @description     Finds last occurrence of an invalid substring in a string,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_find_last_n(void)
{
    const i18n_uchar str[64] = { 0, };
    const i18n_uchar sub_str[64] = { 0, };
    i18n_uchar *ptr = NULL;

    ptr = i18n_ustring_find_last(str, -2, sub_str, -1);
    assert_eq(ptr, NULL);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_r_char_p
 * @since_tizen     2.3
 * @description     Finds last occurrence of a BMP code point in a string,
 *                  compare pointers and check error.
 */
int utc_capi_base_utils_i18n_ustring_r_char_p(void)
{
    const i18n_uchar string[4] = { 0x0041, 0x0042, 0x0043, 0x0000 }; // A, B, C, NULL
    i18n_uchar code_point = 0x0042; // B

    i18n_uchar *last = i18n_ustring_r_char(string, code_point);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(last, string + 1);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_r_char_n
 * @since_tizen     2.3
 * @description     Finds last occurrence of an invalid BMP code point in
 *                  an invalid string, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_r_char_n(void)
{
    i18n_uchar code_point = 0x0044; // D

    i18n_ustring_r_char(NULL, code_point);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_r_char32_p
 * @since_tizen     2.3
 * @description     Finds last occurrence of a code point in a string,
 *                  compare pointers and check error.
 */
int utc_capi_base_utils_i18n_ustring_r_char32_p(void)
{
    const i18n_uchar string[4] = { 0x0041, 0x0042, 0x0043, 0x0000 }; // A, B, C, NULL
    i18n_uchar32 code_point = 0x00000044; // D
    i18n_uchar *result = NULL;

    result = i18n_ustring_r_char32(string, code_point);
    assert_eq(result, NULL);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_r_char32_n
 * @since_tizen     2.3
 * @description     Finds last occurrence of an invalid code point in a string,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_r_char32_n(void)
{
    i18n_uchar32 code_point = 0x00000044; // D

    i18n_ustring_r_char32(NULL, code_point);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_pbrk_p
 * @since_tizen     2.3
 * @description     Finds last occurrence of specified characters in a string,
 *                  compare results and check error.
 */
int utc_capi_base_utils_i18n_ustring_pbrk_p(void)
{
    char *string = "a,b,c";
    i18n_uchar ustring[64] = { 0, };
    char *match_set = ",";
    i18n_uchar umatch_set[64] = { 0, };
    i18n_uchar *result = NULL;

    // copy string to src
    i18n_ustring_copy_ua_n(ustring, string, strlen(string));
    i18n_ustring_copy_ua_n(umatch_set, match_set, strlen(match_set));

    result = i18n_ustring_pbrk((const i18n_uchar *)ustring, (const i18n_uchar *)umatch_set); // return the address of umatch_set[3]

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    assert_eq(result, i18n_ustring_find_first(ustring, i18n_ustring_get_length(ustring), umatch_set, i18n_ustring_get_length(umatch_set)));

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_pbrk_n
 * @since_tizen     2.3
 * @description     Finds last occurrence of specified characters in a string,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_pbrk_n(void)
{
    i18n_ustring_pbrk(NULL, NULL);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_cspn_p
 * @since_tizen     2.3
 * @description     Gets number of consecutive characters in a substring in a string,
 *                  compare pointers and check error.
 */
int utc_capi_base_utils_i18n_ustring_cspn_p(void)
{
    const i18n_uchar str[64] = { 0, };
    const i18n_uchar match_set[64] = { 0, };
    int32_t num;

    num = i18n_ustring_cspn(str, match_set);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(num, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_cspn_n
 * @since_tizen     2.3
 * @description     Gets number of consecutive characters in
 *                  an invalid substring in a string, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_cspn_n(void)
{
    const i18n_uchar match_set[64] = { 0, };

    i18n_ustring_cspn(NULL, match_set);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_spn_p
 * @since_tizen     2.3
 * @description     Gets number of consecutive characters in a substring in a string,
 *                  compare pointers and check error.
 */
int utc_capi_base_utils_i18n_ustring_spn_p(void)
{
    i18n_uchar str[64];
    i18n_ustring_copy_ua(str, "testcase");

    i18n_uchar match_set[64] = { 0, };
    i18n_ustring_copy_ua(match_set, "abcdeft");
    int32_t num;

    num = i18n_ustring_spn(str, match_set);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(num, 2);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_spn_n
 * @since_tizen     2.3
 * @description     Gets number of consecutive characters in an invalid substring in a string, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_spn_n(void)
{
    const i18n_uchar match_set[64] = { 0, };

    i18n_ustring_spn(NULL, match_set);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_tokenizer_r_p
 * @since_tizen     2.3
 * @description     Break a string into tokens, compare result with string
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_tokenizer_r_p(void)
{
    i18n_uchar string[6] = { 0x0041, 0x002C, 0x0043, 0x002C, 0x0045, 0x0000 }; // A, B, C NUL
    const i18n_uchar delimeiter[2] = { 0x002C, 0x0000 }; // B, NUL
    i18n_uchar *save_state = NULL;
    i18n_uchar *result = NULL;

    result = i18n_ustring_tokenizer_r(string, delimeiter, &save_state);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    assert_eq(result, string);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_tokenizer_r_n
 * @since_tizen     2.3
 * @description     Break a string into tokens, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_tokenizer_r_n(void)
{
    i18n_ustring_tokenizer_r(NULL, NULL, NULL);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_compare_p
 * @since_tizen     2.3
 * @description     Compare two strings, compare pointers and check error.
 */
int utc_capi_base_utils_i18n_ustring_compare_p(void)
{
    int result;

    result = i18n_ustring_compare(g_ustr, g_target);
    assert_eq(result, 0);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_compare_n
 * @since_tizen     2.3
 * @description     Compare two strings, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_compare_n(void)
{
    int result = i18n_ustring_compare(NULL, g_target);
    assert_eq(result, 0);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_compare_code_point_order_p
 * @since_tizen     2.3
 * @description     Compare code points of the same strings, compare pointers
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_compare_code_point_order_p(void)
{
    i18n_uchar str1[64];
    i18n_ustring_copy_ua(str1, "testcase");

    i18n_uchar str2[64] = { 0, };
    i18n_ustring_copy_ua(str2, "testcase");
    int result;

    result = i18n_ustring_compare_code_point_order(str1, str2);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(result, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_compare_code_point_order_p2
 * @since_tizen     2.3
 * @description     Compare code points of different strings, compare pointers
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_compare_code_point_order_p2(void)
{
    i18n_uchar str1[64];
    i18n_ustring_copy_ua(str1, "testcase");

    i18n_uchar str2[64] = { 0, };
    i18n_ustring_copy_ua(str2, "testcass");
    int result;

    result = i18n_ustring_compare_code_point_order(str1, str2);
    assert_neq(result, 0);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_compare_code_point_order_n
 * @since_tizen     2.3
 * @description     Compare code points of invalid strings, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_compare_code_point_order_n(void)
{
    i18n_uchar str2[64] = { 0, };

    i18n_ustring_compare_code_point_order(NULL, str2);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_compare_binary_order_p
 * @since_tizen     2.3
 * @description     Compare binary order of the same strings, compare pointers
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_compare_binary_order_p(void)
{
    i18n_uchar str1[64];
    i18n_ustring_copy_ua(str1, "testcase");

    i18n_uchar str2[64] = { 0, };
    i18n_ustring_copy_ua(str2, "testcase");

    i18n_ubool code_pointer_order = false;
    int result;

    result = i18n_ustring_compare_binary_order(str1, -1, str2, -1, code_pointer_order);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(result, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_compare_binary_order_p2
 * @since_tizen     2.3
 * @description     Compare binary order of different strings, compare pointers
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_compare_binary_order_p2(void)
{
    i18n_uchar str1[64];
    i18n_ustring_copy_ua(str1, "testcase");

    i18n_uchar str2[64] = { 0, };
    i18n_ustring_copy_ua(str2, "testcass");

    i18n_ubool code_pointer_order = false;
    int result;

    result = i18n_ustring_compare_binary_order(str1, -1, str2, -1, code_pointer_order);
    assert_neq(result, 0);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_compare_binary_order_n
 * @since_tizen     2.3
 * @description     Compare binary order of invalid strings, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_compare_binary_order_n(void)
{
    const i18n_uchar str2[64] = { 0, };
    i18n_ubool code_pointer_order = false;

    i18n_ustring_compare_binary_order(NULL, -1, str2, -1, code_pointer_order);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_case_compare_with_length_p
 * @since_tizen     2.3
 * @description     Compare with default case of different strings, compare pointers
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_case_compare_with_length_p(void)
{
    i18n_uchar str1[64];
    i18n_ustring_copy_ua(str1, "testcase");

    i18n_uchar str2[64] = { 0, };
    i18n_ustring_copy_ua(str2, "testcase");

    int error = 0;
    int result = i18n_ustring_case_compare_with_length(str1, -1, str2, -1, I18N_U_FOLD_CASE_DEFAULT, &error);

    assert_eq(error, I18N_ERROR_NONE);
    assert_eq(result, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_case_compare_with_length_p2
 * @since_tizen     2.3
 * @description     Compare with default case of different strings, compare pointers
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_case_compare_with_length_p2(void)
{
    i18n_uchar str1[64];
    i18n_ustring_copy_ua(str1, "testcase");

    i18n_uchar str2[64] = { 0, };
    i18n_ustring_copy_ua(str2, "testcass");

    int error = 0;
    int result = i18n_ustring_case_compare_with_length(str1, -1, str2, -1, I18N_U_FOLD_CASE_DEFAULT, &error);

    assert_eq(error, I18N_ERROR_NONE);
    assert_neq(result, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_case_compare_with_length_n
 * @since_tizen     2.3
 * @description     Compare with default case of invalid strings, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_case_compare_with_length_n(void)
{
    const i18n_uchar str1[64] = { 0, };

    int error = 0;
    i18n_ustring_case_compare_with_length(str1, -1, NULL, -1, I18N_U_FOLD_CASE_DEFAULT, &error);
    assert_eq(error, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_compare_n_p
 * @since_tizen     2.3
 * @description     Compare strings bitwise, check result and error.
 */
int utc_capi_base_utils_i18n_ustring_compare_n_p(void)
{
    const i18n_uchar str1[64] = { 0, };
    const i18n_uchar str2[64] = { 0, };
    int n = 32;
    int result;

    result = i18n_ustring_compare_n(str1, str2, n);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(result, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_compare_n_n
 * @since_tizen     2.3
 * @description     Compare invalid string bitwise, so error is expected.
*/
int utc_capi_base_utils_i18n_ustring_compare_n_n(void)
{
    const i18n_uchar str2[64] = { 0, };
    int n = 32;

    i18n_ustring_compare_n(NULL, str2, n);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_compare_n_code_point_order_p
 * @since_tizen     2.3
 * @description     Compare n code points of different strings, compare pointers
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_compare_n_code_point_order_p(void)
{
    i18n_uchar str1[64];
    i18n_ustring_copy_ua(str1, "testcase");

    i18n_uchar str2[64] = { 0, };
    i18n_ustring_copy_ua(str2, "testcase");

    int n = 32;
    int result;

    result = i18n_ustring_compare_n_code_point_order(str1, str2, n);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(result, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_compare_n_code_point_order_p2
 * @since_tizen     2.3
 * @description     Compare n code points of different strings, compare pointers
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_compare_n_code_point_order_p2(void)
{
    i18n_uchar str1[64];
    i18n_ustring_copy_ua(str1, "testcase");

    i18n_uchar str2[64] = { 0, };
    i18n_ustring_copy_ua(str2, "testcase2");
    int n = 32;
    int result;

    result = i18n_ustring_compare_n_code_point_order(str1, str2, n);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_neq(result, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_compare_n_code_point_order_n
 * @since_tizen     2.3
 * @description     Compare n code points of invalid strings, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_compare_n_code_point_order_n(void)
{
    const i18n_uchar str2[64] = { 0, };
    int n = 32;

    i18n_ustring_compare_n_code_point_order(NULL, str2, n);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_case_compare_p
 * @since_tizen     2.3
 * @description     Compare with default case of different strings, compare pointers
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_case_compare_p(void)
{
    i18n_uchar str1[64];
    i18n_ustring_copy_ua(str1, "testCase");

    i18n_uchar str2[64] = { 0, };
    i18n_ustring_copy_ua(str2, "testcase");

    uint32_t option = I18N_U_FOLD_CASE_DEFAULT;
    int result;

    result = i18n_ustring_case_compare(str1, str2, option);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(result, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_case_compare_p2
 * @since_tizen     2.3
 * @description     Compare with default case of different strings, compare pointers
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_case_compare_p2(void)
{
    i18n_uchar str1[64];
    i18n_ustring_copy_ua(str1, "testącase");

    i18n_uchar str2[64] = { 0, };
    i18n_ustring_copy_ua(str2, "testĄCase");

    uint32_t option = I18N_U_FOLD_CASE_DEFAULT;
    int result;

    result = i18n_ustring_case_compare(str1, str2, option);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(result, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_case_compare_n
 * @since_tizen     2.3
 * @description     Compare with default case of invalid string, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_case_compare_n(void)
{
    const i18n_uchar str2[64] = { 0, };
    uint32_t option = I18N_U_FOLD_CASE_DEFAULT;

    i18n_ustring_case_compare(NULL, str2, option);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_case_compare_n_p
 * @since_tizen     2.3
 * @description     Compare with default case of different strings, compare pointers
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_case_compare_n_p(void)
{
    i18n_uchar str1[64];
    i18n_ustring_copy_ua(str1, "testCase");

    i18n_uchar str2[64] = { 0, };
    i18n_ustring_copy_ua(str2, "testCase");

    int n = 32;
    uint32_t option = I18N_U_FOLD_CASE_DEFAULT;
    int result;

    result = i18n_ustring_case_compare_n(str1, str2, n, option);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(result, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_case_compare_n_p2
 * @since_tizen     2.3
 * @description     Compare with default case of different strings, compare pointers
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_case_compare_n_p2(void)
{
    i18n_uchar str1[64];
    i18n_ustring_copy_ua(str1, "testCase");

    i18n_uchar str2[64] = { 0, };
    i18n_ustring_copy_ua(str2, "testcase");

    int n = 32;
    uint32_t option = I18N_U_FOLD_CASE_EXCLUDE_SPECIAL_I;
    int result;

    result = i18n_ustring_case_compare_n(str1, str2, n, option);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(result, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_case_compare_n_n
 * @since_tizen     2.3
 * @description     Compare with default case of invalid strings, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_case_compare_n_n(void)
{

    const i18n_uchar str2[64] = { 0, };
    int n = 32;
    uint32_t option = I18N_U_FOLD_CASE_DEFAULT;

    i18n_ustring_case_compare_n(NULL, str2, n, option);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_case_compare_p
 * @since_tizen     2.3
 * @description     Compare with default case of different strings, compare pointers
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_mem_case_compare_p(void)
{
    i18n_uchar str1[64];
    i18n_ustring_copy_ua(str1, "testCase");

    i18n_uchar str2[64] = { 0, };
    i18n_ustring_copy_ua(str2, "testCase");

    int n = 8;
    uint32_t option = I18N_U_FOLD_CASE_DEFAULT;

    int result = i18n_ustring_mem_case_compare(str1, str2, n, option);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(result, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_case_compare_n
 * @since_tizen     2.3
 * @description     Compare with default case of invalid string, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_mem_case_compare_n(void)
{
    const i18n_uchar str2[64] = { 0, };
    int n = 32;
    uint32_t option = I18N_U_FOLD_CASE_DEFAULT;

    i18n_ustring_mem_case_compare(NULL, str2, n, option);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_copy_au_p
 * @since_tizen     2.3
 * @description     Copy a ustring to a byte string, compare buffers
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_copy_au_p(void)
{
    char dest[STR_LEN] = { 0, };
    char *ptr = NULL;

    ptr = i18n_ustring_copy_au(dest, g_ustr);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    assert_eq(ptr, dest);
    assert_eq(strcmp(dest, g_astr), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_copy_au_n
 * @since_tizen     2.3
 * @description     Copy an invalid ustring to an invalid byte string case strings,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_copy_au_n(void)
{
    i18n_ustring_copy_au(NULL, g_ustr);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_copy_au_n_p
 * @since_tizen     2.3
 * @description     Copy uchar string to char of different strings, compare pointers
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_copy_au_n_p(void)
{
    char dest[STR_LEN] = { 0, };
    char *ptr = NULL;

    ptr = i18n_ustring_copy_au_n(dest, g_ustr, g_str_len);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    assert_eq(ptr, dest);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_copy_au_n_n
 * @since_tizen     2.3
 * @description     Copy uchar string to char using invalid output string, that's why
 *                  error is expected here.
 */
int utc_capi_base_utils_i18n_ustring_copy_au_n_n(void)
{
    i18n_ustring_copy_au_n(NULL, g_ustr, g_str_len);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_copy_p
 * @since_tizen     2.3
 * @description     Copy strings of different strings, compare buffers
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_copy_p(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };

    i18n_ustring_copy(dest, g_ustr);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    assert_eq(i18n_ustring_compare(dest, g_ustr), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_copy_n
 * @since_tizen     2.3
 * @description     Copy invalid string, that's why
 *                  error is expected here.
 */
int utc_capi_base_utils_i18n_ustring_copy_n(void)
{
    i18n_ustring_copy(NULL, g_ustr);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_copy_n_p
 * @since_tizen     2.3
 * @description     Copy strings of different strings, compare pointers
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_copy_n_p(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };

    i18n_ustring_copy_n(dest, g_ustr, g_str_len);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    assert_eq(i18n_ustring_compare(dest, g_ustr), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_copy_n_n
 * @since_tizen     2.3
 * @description     Copy invalid strings, that's why
 *                  error is expected here.
 */
int utc_capi_base_utils_i18n_ustring_copy_n_n(void)
{
    i18n_ustring_copy_n(NULL, g_ustr, g_str_len);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_copy_ua_p
 * @since_tizen     2.3
 * @description     Copy char string to uchar string, compare results
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_copy_ua_p(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    i18n_uchar *ptr = NULL;

    ptr = i18n_ustring_copy_ua(dest, g_astr);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(ptr, dest);
    assert_eq(memcmp(g_ustr, dest, g_str_len * sizeof(i18n_uchar)), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_copy_ua_n
 * @since_tizen     2.3
 * @description     Copy empty string to uchar string, that's why
 *                  error is expected here.
 */
int utc_capi_base_utils_i18n_ustring_copy_ua_n(void)
{
    i18n_ustring_copy_ua(NULL, g_astr);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
/**
 * @testcase        utc_capi_base_utils_i18n_ustring_copy_ua_n_p
 * @since_tizen     2.3
 * @description     Copy char string to uchar string, compare results and
 *                  check error.
 */
int utc_capi_base_utils_i18n_ustring_copy_ua_n_p(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    i18n_uchar *ptr = NULL;

    ptr = i18n_ustring_copy_ua_n(dest, g_astr, g_str_len);
    assert_eq(ptr, dest);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_copy_ua_n_n
 * @since_tizen     2.3
 * @description     Copy invalid char string to uchar, that's why
 *                  error is expected here.
 */
int utc_capi_base_utils_i18n_ustring_copy_ua_n_n(void)
{
    i18n_ustring_copy_ua_n(NULL, g_astr, g_str_len);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_copy_p
 * @since_tizen     2.3
 * @description     Copy uchar strings, compare results and
 *                  check error.
 */
int utc_capi_base_utils_i18n_ustring_mem_copy_p(void)
{
    char *string = "tizen";
    i18n_uchar src[64] = { 0, };
    i18n_uchar dest[64] = { 0, };
    int32_t result = 0;

    // copy string to src
    i18n_ustring_copy_ua_n(src, string, strlen(string));

    // cat src to dest
    i18n_ustring_mem_copy(dest, (const i18n_uchar *)src, i18n_ustring_get_length(src));
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    // compare dest with src
    result = i18n_ustring_mem_compare((const i18n_uchar *)src, (const i18n_uchar *)dest, i18n_ustring_get_length(src));

    assert_eq(result, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_copy_n
 * @since_tizen     2.3
 * @description     Copy invalid uchar string, that's why
 *                  error is expected here.
 */
int utc_capi_base_utils_i18n_ustring_mem_copy_n(void)
{
    i18n_uchar src[64] = { 0, };
    i18n_uchar dest[64] = { 0, };

    // cat src to dest
    i18n_ustring_mem_copy(dest, NULL, i18n_ustring_get_length(src));

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_move_p
 * @since_tizen     2.3
 * @description     Move char string to uchar string, compare results and
 *                  check error.
 */
int utc_capi_base_utils_i18n_ustring_mem_move_p(void)
{
    i18n_uchar dest[64];

    i18n_uchar src[64] = { 0, };
    i18n_ustring_copy_ua(src, "testcase");

    int32_t count = 32;
    i18n_uchar *ptr = NULL;

    ptr = i18n_ustring_mem_move(dest, src, count);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(ptr, dest);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_move_n
 * @since_tizen     2.3
 * @description     Move invalid char string to uchar, that's why
 *                  error is expected here.
 */
int utc_capi_base_utils_i18n_ustring_mem_move_n(void)
{
    const i18n_uchar src[64] = { 0, };
    int32_t count = 32;

    i18n_ustring_mem_move(NULL, src, count);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_set_p
 * @since_tizen     2.3
 * @description     Sets memory of uchar string, compare results and
 *                  check error.
 */
int utc_capi_base_utils_i18n_ustring_mem_set_p(void)
{
    i18n_uchar dest[64] = { 0, };
    const i18n_uchar c = 'a';
    int32_t count = 32;
    i18n_uchar *ptr = NULL;

    ptr = i18n_ustring_mem_set(dest, c, count);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    assert_eq(ptr, dest);

    int i = 0;
    for(; i < count; i++) {
        assert_eq(dest[i], c);
    }
    assert_eq(dest[count + 1], 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_set_n
 * @since_tizen     2.3
 * @description     Sets memory of invalid uchar string, that's why
 *                  error is expected here.
 */
int utc_capi_base_utils_i18n_ustring_mem_set_n(void)
{
    const i18n_uchar c = '0';
    int32_t count = 32;

    i18n_ustring_mem_set(NULL, c, count);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_compare_p
 * @since_tizen     2.3
 * @description     Compare memory of the same uchar string, compare results
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_mem_compare_p(void)
{
    i18n_uchar buf1[64] = { 0, };
    i18n_ustring_copy_ua(buf1, "testcase");
    i18n_uchar buf2[64] = { 0, };
    i18n_ustring_copy_ua(buf2, "testcase");
    int32_t count = 32;
    int32_t result = -1;

    result = i18n_ustring_mem_compare(buf1, buf2, count);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(result, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_compare_p2
 * @since_tizen     2.3
 * @description     Compare memory of different uchar strings, compare results
 *                  and check error.
 */
int utc_capi_base_utils_i18n_ustring_mem_compare_p2(void)
{
    i18n_uchar buf1[64] = { 0, };
    i18n_uchar buf2[64] = { 0, };
    i18n_ustring_copy_ua(buf1, "testcase");
    i18n_ustring_copy_ua(buf2, "testcas");
    int32_t count = 32;
    int32_t result = -1;

    result = i18n_ustring_mem_compare(buf1, buf2, count);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_neq(result, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_compare_n
 * @since_tizen     2.3
 * @description     Compare memory of invalid uchar string and uchar, that's why
 *                  error is expected here.
 */
int utc_capi_base_utils_i18n_ustring_mem_compare_n(void)
{
    const i18n_uchar buf2[64] = { 0, };
    int32_t count = 32;

    int result = i18n_ustring_mem_compare(NULL, buf2, count);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(result, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_compare_code_point_order_p
 * @since_tizen     2.3
 * @description     Compare memory in code point order of uchar string to uchar string,
 *                  compare results and check error.
 */
int utc_capi_base_utils_i18n_ustring_mem_compare_code_point_order_p(void)
{
    i18n_uchar s1[64] = { 0, };
    i18n_uchar s2[64] = { 0, };
    i18n_ustring_copy_ua(s1, "testcas");
    i18n_ustring_copy_ua(s2, "testcas");
    int32_t count = 32;
    int32_t result = -1;

    result = i18n_ustring_mem_compare_code_point_order(s1, s2, count);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(result, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_compare_code_point_order_n
 * @since_tizen     2.3
 * @description     Compare memory in code point order of invalid char string to uchar, that's why
 *                  error is expected here.
 */
int utc_capi_base_utils_i18n_ustring_mem_compare_code_point_order_n(void)
{
    const i18n_uchar s2[64] = { 0, };
    int32_t count = 32;

    i18n_ustring_mem_compare_code_point_order(NULL, s2, count);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_char_p
 * @since_tizen     2.3
 * @description     Finds the first occurrence of a BMP code point in a string, compare results and
 *                  check error.
 */
int utc_capi_base_utils_i18n_ustring_mem_char_p(void)
{
    const i18n_uchar ustring[64] = { 'T', 'I', 'Z', 'E', 'N', '\0' };
    i18n_uchar code_point = 'Z';
    i18n_uchar *result = NULL;

    result = i18n_ustring_mem_char(ustring, code_point, i18n_ustring_get_length(ustring));

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(result, ustring + 2);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_char_n
 * @since_tizen     2.3
 * @description     Finds the first occurrence of an invalid BMP code point in
 *                  an invalid string, that's why error is expected here.
 */
int utc_capi_base_utils_i18n_ustring_mem_char_n(void)
{
    i18n_uchar code_point = 'O';

    i18n_ustring_mem_char(NULL, code_point, 0);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_char32_p
 * @since_tizen     2.3
 * @description     Finds the first occurrence of a code point in a string,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_mem_char32_p(void)
{
    const i18n_uchar ustring[64] = { 'T', 'I', 'Z', 'E', 'N', '\0' };
    i18n_uchar32 code_point = 'E';
    i18n_uchar *result = NULL;

    result = i18n_ustring_mem_char32(ustring, code_point, i18n_ustring_get_length(ustring));

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(result, ustring + 3);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_char32_n
 * @since_tizen     2.3
 * @description     Finds the first occurrence of an invalid code point in an invalid string,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_mem_char32_n(void)
{
    i18n_uchar32 code_point = 'O';

    i18n_ustring_mem_char32(NULL, code_point, 0);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_r_char_p
 * @since_tizen     2.3
 * @description     Finds the last occurrence of a BMP code point in a string,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_mem_r_char_p(void)
{
    const i18n_uchar ustring[64] = { 'T', 'I', 'Z', 'E', 'N', 'E', 'T', '\0' };
    i18n_uchar code_point = 'E';
    i18n_uchar *result = NULL;

    result = i18n_ustring_mem_r_char(ustring, code_point, i18n_ustring_get_length(ustring));

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(result, ustring + 5);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_r_char_n
 * @since_tizen     2.3
 * @description     Finds the last occurrence of an invalid BMP code point in an invalid string,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_mem_r_char_n(void)
{
    i18n_uchar code_point = 'O';

    i18n_ustring_mem_r_char(NULL, code_point, 0);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_r_char32_p
 * @since_tizen     2.3
 * @description     Finds the last occurrence of a code point in a string,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_mem_r_char32_p(void)
{
    const i18n_uchar ustring[64] = { 'T', 'I', 'Z', 'E', 'N', 'E', 'T', '\0' };
    i18n_uchar32 code_point = 'E';
    i18n_uchar *result = NULL;

    result = i18n_ustring_mem_r_char32(ustring, code_point, i18n_ustring_get_length(ustring));

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(result, ustring + 5);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_mem_r_char32_n
 * @since_tizen     2.3
 * @description     Finds the last occurrence of an invalid code point in an invalid string,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_mem_r_char32_n(void)
{
    i18n_uchar32 code_point = 'O';

    i18n_ustring_mem_r_char32(NULL, code_point, 0);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_unescape_p
 * @since_tizen     2.3
 * @description     Unescape a string of characters, write the resulting
 *                  unicode characters to the destination buffer,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_unescape_p(void)
{
    const char *src = "Hello \\\"World.\\\"";
    i18n_uchar dest[64] = { 0, };
    int32_t dest_capacity = 64;
    int32_t length;

    length = i18n_ustring_unescape(src, dest, dest_capacity);

    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);
    assert_eq(dest[6], '"');
    assert_geq(length, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_unescape_n
 * @since_tizen     2.3
 * @description     Unescape an invalid string of characters in invalid string, write
 *                  the resulting unicode characters to the destination buffer,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_unescape_n(void)
{
    i18n_uchar dest[64] = { 0, };
    int32_t dest_capacity = 64;

    i18n_ustring_unescape(NULL, dest, dest_capacity);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

static i18n_uchar char_at(int32_t offset, void *context)
{
    i18n_uchar dest[1] = { 0, };
    i18n_ustring_copy_ua_n(dest, context + offset, 1);
    return dest[0];
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_unescape_at_p
 * @since_tizen     2.3
 * @description     Unescape a single sequence, checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_unescape_at_p(void)
{
    const char *src = "\a";
    int32_t offset = 0;
    i18n_uchar32 character;

    character = i18n_ustring_unescape_at(char_at, &offset, strlen(src), (void *)src);
    assert_neq(character, 0xFFFFFFFF);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_unescape_at_n
 * @since_tizen     2.3
 * @description     Unescape a single invalid sequence, checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_unescape_at_n(void)
{
    const char *src = "\a";
    int32_t offset = 0;

    i18n_ustring_unescape_at(NULL, &offset, 0, (void *)src);
    int err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_to_upper_p
 * @since_tizen     2.3
 * @description     Uppercases the characters in a string,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_to_upper_p(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);
    const i18n_uchar src[] = { 't', 'i', 'z', 'e', 'n', '\0' };
    const char *locale = I18N_ULOCALE_US;
    i18n_error_code_e err_code = I18N_ERROR_NONE;

    i18n_ustring_to_upper(dest, dest_capacity, src, i18n_ustring_get_length(src), locale, &err_code);
    assert_eq(err_code, I18N_ERROR_NONE);

    const i18n_uchar upper[] = { 'T', 'I', 'Z', 'E', 'N', '\0' };
    assert_eq(memcmp(upper, dest, i18n_ustring_get_length(src) * sizeof(src[0])), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_to_upper_n
 * @since_tizen     2.3
 * @description     Uppercases the characters in an invalid string,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_to_upper_n(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    int32_t dest_capacity = -1; // Illegal argument
    const char *locale = I18N_ULOCALE_US;
    i18n_error_code_e err_code = I18N_ERROR_NONE;

    i18n_ustring_to_upper(dest, dest_capacity, NULL, -10000, locale, &err_code);

    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_to_lower_p
 * @since_tizen     2.3
 * @description     Titlecases a string, checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_to_lower_p(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);
    const i18n_uchar src[] = { 'T', 'I', 'Z', 'E', 'N', '\0' };
    const char *locale = I18N_ULOCALE_US;
    i18n_error_code_e err_code = I18N_ERROR_NONE;

    i18n_ustring_to_lower(dest, dest_capacity, src, i18n_ustring_get_length(src), locale, &err_code);
    assert_eq(err_code, I18N_ERROR_NONE);

    const i18n_uchar lower[] = { 't', 'i', 'z', 'e', 'n', '\0' };
    assert_eq(memcmp(lower, dest, i18n_ustring_get_length(src) * sizeof(src[0])), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_to_lower_n
 * @since_tizen     2.3
 * @description     Lowercases the characters in an invalid string,
 *                  so error is expected here.
 */
int utc_capi_base_utils_i18n_ustring_to_lower_n(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    int32_t dest_capacity = -1; // Illegal argument
    const char *locale = I18N_ULOCALE_US;
    i18n_error_code_e err_code = I18N_ERROR_NONE;

    i18n_ustring_to_lower(dest, dest_capacity, NULL, -10000, locale, &err_code);
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_to_title_new_p
 * @since_tizen     2.3.1
 * @description     Titlecases a string, checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_to_title_new_p(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);
    i18n_uchar src[] = { 'T', 'I', 'Z', 'E', 'N', '\0' };
    const char *locale = I18N_ULOCALE_US;
    i18n_error_code_e err_code = I18N_ERROR_NONE;

    i18n_ustring_to_title_new(dest, dest_capacity, src, i18n_ustring_get_length(src), NULL, locale);
    err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_NONE);

    const i18n_uchar title[] = { 'T', 'i', 'z', 'e', 'n', '\0' };
    assert_eq(memcmp(title, dest, i18n_ustring_get_length(src) * sizeof(src[0])), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_to_title_new_n
 * @since_tizen     2.3.1
 * @description     Titlecases an invalid string, so error is expected here.
 */
int utc_capi_base_utils_i18n_ustring_to_title_new_n(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    int32_t dest_capacity = -1; // Illegal argument
    const char *locale = I18N_ULOCALE_US;
    i18n_error_code_e err_code = I18N_ERROR_NONE;

    i18n_ustring_to_title_new(dest, dest_capacity, NULL, -10000, NULL, locale);
    err_code = get_last_result();
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_fold_case_p
 * @since_tizen     2.3
 * @description     Case-folds the characters in a string,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_fold_case_p(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);
    i18n_uchar src[] = { 0x61, 0x42, 0x130, 0x49, 0x131, 0x3d0, 0xdf, 0xfb03, 0xd93f, 0xdfff, 0x0 };

    i18n_error_code_e err_code = I18N_ERROR_NONE;

    int32_t length = i18n_ustring_fold_case(dest, dest_capacity, src, i18n_ustring_get_length(src), I18N_U_FOLD_CASE_DEFAULT, &err_code);

    assert_eq(err_code, I18N_ERROR_NONE);

    static const i18n_uchar foldedDefault[] = { 0x61, 0x62, 0x69, 0x307, 0x69, 0x131, 0x3b2, 0x73, 0x73, 0x66, 0x66, 0x69, 0xd93f, 0xdfff };
    assert_eq(memcmp(foldedDefault, dest, length * sizeof(i18n_uchar)), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_fold_case_n
 * @since_tizen     2.3
 * @description     Case-folds the characters in an invalid string,
 *                  so error is expected
 */
int utc_capi_base_utils_i18n_ustring_fold_case_n(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    int32_t dest_capacity = -1; // Illegal argument
    i18n_error_code_e err_code = I18N_ERROR_NONE;

    i18n_ustring_fold_case(dest, dest_capacity, NULL, -10000, I18N_U_FOLD_CASE_DEFAULT, &err_code);

    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_to_WCS_p
 * @since_tizen     2.3
 * @description     Convert a UTF-16 string to a wchar_t string,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_ustring_to_WCS_p(void)
{
    wchar_t dest[STR_LEN] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);
    int32_t dest_len = 0;
    const i18n_uchar src[] = { 'T', 'I', 'Z', 'E', 'N', '\0' };
    int32_t src_len = i18n_ustring_get_length(src);
    int err_code = I18N_ERROR_NONE;

    i18n_ustring_to_WCS(dest, dest_capacity, &dest_len, src, src_len, &err_code);
    assert_eq(err_code, I18N_ERROR_NONE);

    i18n_uchar from_dest[STR_LEN] = { 0, };
    int32_t from_dest_capacity = sizeof(from_dest) / sizeof(from_dest[0]);
    int32_t from_dest_len = 0;
    i18n_ustring_from_WCS(from_dest, from_dest_capacity, &from_dest_len, dest, dest_len, &err_code);
    assert_eq(err_code, I18N_ERROR_NONE);

    int i;
    for(i = 0; i < src_len; i++) {
        assert_eq(from_dest[i], src[i]);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_to_WCS_n
 * @since_tizen     2.3
 * @description     Convert an invalid UTF-16 string to an invalid wchar_t string,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_ustring_to_WCS_n(void)
{
    wchar_t dest[STR_LEN] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);
    int32_t dest_len = 0;
    int err_code = I18N_ERROR_NONE;

    i18n_ustring_to_WCS(dest, dest_capacity, &dest_len, NULL, -10000, &err_code);
    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_from_WCS_p
 * @since_tizen     2.3
 * @description     Convert a wchar_t string to UTF-16,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_from_WCS_p(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    int dest_capacity = sizeof(dest) / sizeof(dest[0]);
    int32_t dest_len = 0; // out
    const wchar_t src[STR_LEN] = { 'T', 'I', 'Z', 'E', 'N', '\0' };
    int err_code = I18N_ERROR_NONE;

    i18n_ustring_from_WCS(dest, dest_capacity, &dest_len, src, -1, &err_code);
    assert_eq(err_code, I18N_ERROR_NONE);

    wchar_t to_dest[STR_LEN] = { 0, };
    int32_t to_dest_capacity = sizeof(to_dest) / sizeof(to_dest[0]);
    int32_t to_dest_len = 0;
    i18n_ustring_to_WCS(to_dest, to_dest_capacity, &to_dest_len, dest, dest_len, &err_code);
    assert_eq(err_code, I18N_ERROR_NONE);

    int i;
    for(i = 0; i < to_dest_len; i++) {
        assert_eq(to_dest[i], src[i]);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_from_WCS_n
 * @since_tizen     2.3
 * @description     Convert an invalid wchar_t string to UTF-16,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_ustring_from_WCS_n(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    int dest_capacity = sizeof(dest) / sizeof(dest[0]);
    int32_t dest_len = 0; // out
    int err_code = I18N_ERROR_NONE;

    i18n_ustring_from_WCS(dest, dest_capacity, &dest_len, NULL, -1000, &err_code);

    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_to_UTF8_p
 * @since_tizen     2.3
 * @description     Converts a UTF-16 string to UTF-8, checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_to_UTF8_p(void)
{
    int err = I18N_ERROR_NONE;
    char dest[STR_LEN] = { 0, };
    int32_t dest_capacity = STR_LEN;
    int32_t dest_len = -1;
    i18n_uchar src[STR_LEN] = { 0, };
    i18n_ustring_copy_ua_n(src, "TIZEN", strlen("TIZEN")); // 0054 0049 005A 0045 004E - "TIZEN" in UTF16 encoding
    int32_t src_len = -1;

    i18n_ustring_to_UTF8(dest, dest_capacity, &dest_len, src, src_len, &err);
    assert_eq(err, I18N_ERROR_NONE);

    const uint8_t test_utf8[] = { 0x54, 0x49, 0x5A, 0x45, 0x4E, 0 }; // "TIZEN" in UTF8 encoding
    assert_eq(strncmp((const char * )test_utf8, dest, dest_len + 1), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_to_UTF8_n
 * @since_tizen     2.3
 * @description     Converts an invalid UTF-16 string to UTF-8, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_to_UTF8_n(void)
{
    int err = I18N_ERROR_NONE;
    char dest[STR_LEN] = { 0, };
    int32_t dest_len = -1;

    i18n_ustring_to_UTF8(dest, STR_LEN, &dest_len, NULL, -1, &err);
    assert_eq(err, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_from_UTF8_p
 * @since_tizen     2.3
 * @description     Converts a UTF-8 string to UTF-16, checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_from_UTF8_p(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);
    int32_t dest_len = 0;
    const char *src = "TIZEN";
    int err_code = I18N_ERROR_NONE;

    i18n_ustring_from_UTF8(dest, dest_capacity, &dest_len, src, strlen(src), &err_code);
    assert_eq(err_code, I18N_ERROR_NONE);

    i18n_uchar test_utf16[STR_LEN] = { 0, };
    i18n_ustring_copy_ua_n(test_utf16, "TIZEN", strlen("TIZEN")); // 0054 0049 005A 0045 004E - "TIZEN" in UTF16 encoding
    assert_eq(memcmp(test_utf16, dest, (dest_len + 1) * sizeof(dest[0])), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_from_UTF8_n
 * @since_tizen     2.3
 * @description     Converts an invalid UTF-8 string to UTF-16,
 *                  checks and error code.
 */
int utc_capi_base_utils_i18n_ustring_from_UTF8_n(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);
    int32_t dest_len = 0;
    int err_code = I18N_ERROR_NONE;

    i18n_ustring_from_UTF8(dest, dest_capacity, &dest_len, NULL, -10000, &err_code);

    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_to_UTF8_with_sub_p
 * @since_tizen     2.3
 * @description     Convert a UTF-16 string to UTF-8,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_to_UTF8_with_sub_p(void)
{
    int err = I18N_ERROR_NONE;
    char dest[STR_LEN] = { 0, };
    int32_t dest_capacity = STR_LEN;
    int32_t dest_len = 0;
    i18n_uchar src[STR_LEN] = { 0, };
    i18n_ustring_copy_ua_n(src, "TIZEN", strlen("TIZEN")); // 0054 0049 005A 0045 004E - "TIZEN" in UTF16 encoding
    int32_t src_len = -1;
    i18n_uchar32 sub_char = 0xFFFD;
    int32_t num_substitutions = 0;

    i18n_ustring_to_UTF8_with_sub(dest, dest_capacity, &dest_len, src, src_len, sub_char, &num_substitutions, &err);
    assert_eq(err, I18N_ERROR_NONE);

    const uint8_t test_utf8[] = { 0x54, 0x49, 0x5A, 0x45, 0x4E, 0 }; // "TIZEN" in UTF8 encoding
    assert_eq(strncmp((const char * )test_utf8, dest, dest_len + 1), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_to_UTF8_with_sub_n
 * @since_tizen     2.3
 * @description     Convert an invalid UTF-16 string to UTF-8,
 *                  so error is expected
 */
int utc_capi_base_utils_i18n_ustring_to_UTF8_with_sub_n(void)
{
    int err = I18N_ERROR_NONE;
    char dest[STR_LEN] = { 0, };
    int32_t dest_capacity = STR_LEN;
    int32_t dest_len = 0;
    int32_t src_len = STR_LEN;
    i18n_uchar32 sub_char = '0';
    int32_t num_substitutions = 0;

    i18n_ustring_to_UTF8_with_sub(dest, dest_capacity, &dest_len, NULL, src_len, sub_char, &num_substitutions, &err);
    assert_eq(err, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_from_UTF8_with_sub_p
 * @since_tizen     2.3
 * @description     Convert a UTF-8 string to UTF-16,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_from_UTF8_with_sub_p(void)
{
    int err = I18N_ERROR_NONE;
    i18n_uchar dest[STR_LEN] = { 0, };
    int32_t dest_capacity = STR_LEN;
    int32_t dest_len = 0;
    const char src[STR_LEN] = "TIZEN";
    int32_t src_len = -1;
    i18n_uchar32 sub_char = 0xFFFD;
    int32_t num_substitutions = 0;

    i18n_ustring_from_UTF8_with_sub(dest, dest_capacity, &dest_len, src, src_len, sub_char, &num_substitutions, &err);
    assert_eq(err, I18N_ERROR_NONE);

    i18n_uchar test_utf16[STR_LEN] = { 0, };
    i18n_ustring_copy_ua_n(test_utf16, "TIZEN", strlen("TIZEN")); // 0054 0049 005A 0045 004E - "TIZEN" in UTF16 encoding
    assert_eq(memcmp(test_utf16, dest, (dest_len + 1) * sizeof(dest[0])), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_from_UTF8_with_sub_n
 * @since_tizen     2.3
 * @description     Convert an invalid UTF-8 string to UTF-16,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_from_UTF8_with_sub_n(void)
{
    int err = I18N_ERROR_NONE;
    i18n_uchar dest[STR_LEN] = { 0, };
    int32_t dest_capacity = STR_LEN;
    int32_t dest_len = 0;
    int32_t src_len = STR_LEN;
    i18n_uchar32 sub_char = '0';
    int32_t num_substitutions = 0;

    i18n_ustring_from_UTF8_with_sub(dest, dest_capacity, &dest_len, NULL, src_len, sub_char, &num_substitutions, &err);
    assert_eq(err, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_from_UTF8_lenient_p
 * @since_tizen     2.3
 * @description     Convert a UTF-8 string to UTF-16,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_from_UTF8_lenient_p(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);
    int32_t dest_len = 0;
    const char *src = "TIZEN";
    int err_code = I18N_ERROR_NONE;

    i18n_ustring_from_UTF8_lenient(dest, dest_capacity, &dest_len, src, strlen(src), &err_code);
    assert_eq(err_code, I18N_ERROR_NONE);

    i18n_uchar test_utf16[STR_LEN] = { 0, };
    i18n_ustring_copy_ua_n(test_utf16, "TIZEN", strlen("TIZEN")); // 0054 0049 005A 0045 004E - "TIZEN" in UTF16 encoding
    assert_eq(memcmp(test_utf16, dest, (dest_len + 1) * sizeof(dest[0])), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_from_UTF8_lenient_n
 * @since_tizen     2.3
 * @description     Convert an invalid UTF-8 string to UTF-16,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_from_UTF8_lenient_n(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);
    int32_t dest_len = 0;
    int err_code = I18N_ERROR_NONE;

    i18n_ustring_from_UTF8_lenient(dest, dest_capacity, &dest_len, NULL, -10000, &err_code);

    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_to_UTF32_p
 * @since_tizen     2.3
 * @description     Convert a UTF-16 string to UTF-32,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_to_UTF32_p(void)
{
    int err = I18N_ERROR_NONE;
    i18n_uchar32 dest[STR_LEN] = { 0, };
    int32_t dest_capacity = STR_LEN;
    int32_t dest_len = 0;
    i18n_uchar src[STR_LEN] = { 0, };
    i18n_ustring_copy_ua_n(src, "TIZEN", strlen("TIZEN")); // 0054 0049 005A 0045 004E - "TIZEN" in UTF16 encoding
    int32_t src_len = -1;

    i18n_ustring_to_UTF32(dest, dest_capacity, &dest_len, src, src_len, &err);
    assert_eq(err, I18N_ERROR_NONE);

    const uint32_t result_utf32[] = { 0x00000054, 0x00000049, 0x0000005A, 0x00000045, 0x0000004E, 0 }; // "TIZEN" in UTF32 encoding
    assert_eq(memcmp(result_utf32, dest, (dest_len + 1) * sizeof(dest[0])), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_to_UTF32_n
 * @since_tizen     2.3
 * @description     Convert an invalid UTF-16 string to UTF-32, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_to_UTF32_n(void)
{
    int err = I18N_ERROR_NONE;
    i18n_uchar32 dest[STR_LEN] = { 0, };
    int32_t dest_capacity = STR_LEN;
    int32_t dest_len = 0;

    i18n_ustring_to_UTF32(dest, dest_capacity, &dest_len, NULL, -1, &err);
    assert_eq(err, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_from_UTF32_p
 * @since_tizen     2.3
 * @description     Convert a UTF-32 string to UTF-16, checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_from_UTF32_p(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);
    int32_t dest_len = 0;
    const i18n_uchar32 src[] = { 'T', 'I', 'Z', 'E', 'N', '\0' };
    int err_code = I18N_ERROR_NONE;

    i18n_ustring_from_UTF32(dest, dest_capacity, &dest_len, src, -1, &err_code);

    assert_eq(err_code, I18N_ERROR_NONE);

    i18n_uchar test_utf16[STR_LEN] = { 0, };
    i18n_ustring_copy_ua_n(test_utf16, "TIZEN", strlen("TIZEN")); // 0054 0049 005A 0045 004E - "TIZEN" in UTF16 encoding
    assert_eq(memcmp(test_utf16, dest, (dest_len + 1) * sizeof(dest[0])), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_from_UTF32_n
 * @since_tizen     2.3
 * @description     Convert an invalid UTF-32 string to UTF-16, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_from_UTF32_n(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    int32_t dest_capacity = -1; // Illegal argument
    int32_t dest_len = 0; // out
    int err_code = I18N_ERROR_NONE;

    i18n_ustring_from_UTF32(dest, dest_capacity, &dest_len, NULL, -10000, &err_code);

    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_to_UTF32_with_sub_p
 * @since_tizen     2.3
 * @description     Convert a UTF-16 string to UTF-32, checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_to_UTF32_with_sub_p(void)
{
    i18n_uchar32 dest[STR_LEN] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);
    int32_t dest_len = 0; // out
    const i18n_uchar src[] = { 'T', 'I', 'Z', 'E', 'N', '\0' };
    i18n_uchar32 sub_char = 0xFFFD;
    int32_t num_substitutions = 0;
    int err_code = I18N_ERROR_NONE;

    i18n_ustring_to_UTF32_with_sub(dest, dest_capacity, &dest_len, src, i18n_ustring_get_length(src), sub_char, &num_substitutions, &err_code);

    assert_eq(err_code, I18N_ERROR_NONE);

    const uint32_t result_utf32[] = { 0x00000054, 0x00000049, 0x0000005A, 0x00000045, 0x0000004E, 0 }; // "TIZEN" in UTF32 encoding
    assert_eq(memcmp(result_utf32, dest, (dest_len + 1) * sizeof(dest[0])), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_to_UTF32_with_sub_n
 * @since_tizen     2.3
 * @description     Convert an invalid UTF-16 string to UTF-32, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_to_UTF32_with_sub_n(void)
{
    i18n_uchar32 dest[STR_LEN] = { 0, };
    int32_t dest_capacity = -1; // Illegal argument
    int32_t dest_len = 0; // out
    i18n_uchar32 sub_char = 0xFFFD;
    int32_t num_substitutions = 0;
    int err_code = I18N_ERROR_NONE;

    i18n_ustring_to_UTF32_with_sub(dest, dest_capacity, &dest_len, NULL, -10000, sub_char, &num_substitutions, &err_code);

    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_from_UTF32_with_sub_p
 * @since_tizen     2.3
 * @description     Convert a UTF-32 string to UTF-16,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ustring_from_UTF32_with_sub_p(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);
    int32_t dest_len = 0; // out
    const i18n_uchar32 src[] = { 'T', 'I', 'Z', 'E', 'N', '\0' };
    i18n_uchar32 sub_char = 0xFFFD;
    int32_t num_substitutions = 0;
    int err_code = I18N_ERROR_NONE;

    i18n_ustring_from_UTF32_with_sub(dest, dest_capacity, &dest_len, src, -1, sub_char, &num_substitutions, &err_code);

    assert_eq(err_code, I18N_ERROR_NONE);

    i18n_uchar test_utf16[STR_LEN] = { 0, };
    i18n_ustring_copy_ua_n(test_utf16, "TIZEN", strlen("TIZEN")); // 0054 0049 005A 0045 004E - "TIZEN" in UTF16 encoding
    assert_eq(memcmp(test_utf16, dest, (dest_len + 1) * sizeof(dest[0])), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ustring_from_UTF32_with_sub_n
 * @since_tizen     2.3
 * @description     Convert an invalid UTF-32 string to UTF-16, so error is expected.
 */
int utc_capi_base_utils_i18n_ustring_from_UTF32_with_sub_n(void)
{
    i18n_uchar dest[STR_LEN] = { 0, };
    int32_t dest_capacity = -1; // Illegal argument
    int32_t dest_len = 0; // out
    i18n_uchar32 sub_char = 0xFFFD;
    int32_t num_substitutions = 0;
    int err_code = I18N_ERROR_NONE;

    i18n_ustring_from_UTF32_with_sub(dest, dest_capacity, &dest_len, NULL, -10000, sub_char, &num_substitutions, &err_code);

    assert_eq(err_code, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
