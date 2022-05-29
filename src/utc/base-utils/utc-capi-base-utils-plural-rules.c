#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

#define BUFSIZE 256

static i18n_plural_rules_h plural_rules = NULL;
static int ret = I18N_ERROR_NONE;
static const char *rules = "one: n is 1; few: n in 2..4";

/**
 * @function        utc_capi_base_utils_plural_rules_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_plural_rules_startup(void)
{
    ret = i18n_plural_rules_create_rules_from_descr(rules, &plural_rules);
}

/**
 * @function        utc_capi_base_utils_plural_rules_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_plural_rules_cleanup(void)
{
    if (plural_rules != NULL) {
        ret = i18n_plural_rules_destroy(plural_rules);
        plural_rules = NULL;
    }
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_create_p
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_rules_create_p(void)
{
   utc_capi_base_utils_plural_rules_cleanup();
   assert_eq(ret, I18N_ERROR_NONE);
   assert_eq(plural_rules, NULL);

   ret = i18n_plural_rules_create(&plural_rules);

   assert_neq(plural_rules, NULL);
   assert_eq(ret, I18N_ERROR_NONE);

   return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_create_n
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_create passing invalid plural_rules
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_create_n(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_rules_create(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_destroy_p
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_rules_destroy_p(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_rules_destroy(plural_rules);

    assert_eq(ret, I18N_ERROR_NONE);

    plural_rules = NULL;

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_destroy_n
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_destroy passing invalid
 *              plural_rules and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_destroy_n(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_rules_destroy(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_clone_p
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_clone and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_rules_clone_p(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_plural_rules_h clone = NULL;

    ret = i18n_plural_rules_clone(plural_rules, &clone);

    assert_neq(clone, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_clone_n
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_clone passing invalid
 *              plural_rules and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_clone_n(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_plural_rules_h clone = NULL;

    ret = i18n_plural_rules_clone(NULL, &clone);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_clone_n2
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_clone passing invalid
 *              clone and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_clone_n2(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_rules_clone(plural_rules, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_create_rules_from_descr_p
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_create_rules_from_descr and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_rules_create_rules_from_descr_p(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *description = "one: n is 1; few: n in 2..4";

    utc_capi_base_utils_plural_rules_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_rules, NULL);

    ret = i18n_plural_rules_create_rules_from_descr(description, &plural_rules);

    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_create_rules_from_descr_n
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_create_rules_from_descr passing non-parsable
 *              description and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_create_rules_from_descr_n(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *description = "sample string";

    utc_capi_base_utils_plural_rules_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_rules, NULL);

    ret = i18n_plural_rules_create_rules_from_descr(description, &plural_rules);

    assert_eq(plural_rules, NULL);
    assert_neq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_create_rules_from_descr_n2
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_create_rules_from_descr passing invalid
 *              description and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_create_rules_from_descr_n2(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_rules_create_rules_from_descr(NULL, &plural_rules);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_create_rules_from_descr_n3
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_create_rules_from_descr passing invalid
 *              plural_rules and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_create_rules_from_descr_n3(void)
{
    const char *description = "sample string";

    utc_capi_base_utils_plural_rules_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_rules, NULL);

    ret = i18n_plural_rules_create_rules_from_descr(description, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_for_locale_p
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_for_locale and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_rules_for_locale_p(void)
{
    const char *language = I18N_ULOCALE_ENGLISH;
    const char *country = "US";

    utc_capi_base_utils_plural_rules_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_rules, NULL);

    ret = i18n_plural_rules_for_locale(language, country, I18N_UPLURAL_TYPE_CARDINAL, &plural_rules);

    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_for_locale_p2
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_for_locale and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_rules_for_locale_p2(void)
{
    const char *language = I18N_ULOCALE_ENGLISH;
    const char *country = "US";

    utc_capi_base_utils_plural_rules_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_rules, NULL);

    ret = i18n_plural_rules_for_locale(language, country, I18N_UPLURAL_TYPE_ORDINAL, &plural_rules);

    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_for_locale_n
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_for_locale passing invalid
 *              plural_rules and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_for_locale_n(void)
{
    const char *language = I18N_ULOCALE_ENGLISH;
    const char *country = "US";

    ret = i18n_plural_rules_for_locale(language, country, I18N_UPLURAL_TYPE_CARDINAL, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_select_int32_p
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_select_int32 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_rules_select_int32_p(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *output_string = "one";
    int32_t number = 1;
    i18n_uchar buffer[BUFSIZE] = { 0 };

    int output_length = -1;
    ret = i18n_plural_rules_select_int32(plural_rules, number, BUFSIZE, buffer, &output_length);

    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, buffer, BUFSIZE);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strncmp(output_buffer, output_string, strlen(output_string)), 0);
    assert_eq(output_length, strlen(output_string));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_select_int32_n
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_select_int32 passing invalid
 *              output_length and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_select_int32_n(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t number = 1;
    i18n_uchar buffer[BUFSIZE] = { 0 };

    ret = i18n_plural_rules_select_int32(plural_rules, number, BUFSIZE, buffer, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_select_int32_n2
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_select_int32 passing invalid
 *              plural_rules and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_select_int32_n2(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t number = 1;
    i18n_uchar buffer[BUFSIZE] = { 0 };

    int output_length = -1;
    ret = i18n_plural_rules_select_int32(NULL, number, BUFSIZE, buffer, &output_length);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_select_double_p
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_select_double and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_rules_select_double_p(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *output_string = "few";
    double number = 2.0;
    i18n_uchar buffer[BUFSIZE] = { 0 };

    int output_length = -1;
    ret = i18n_plural_rules_select_double(plural_rules, number, BUFSIZE, buffer, &output_length);

    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, buffer, BUFSIZE);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strncmp(output_buffer, output_string, strlen(output_string)), 0);
    assert_eq(output_length, strnlen(output_string, BUFSIZE));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_select_double_n
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_select_double passing invalid
 *              output_length and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_select_double_n(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    double number = 2.5;
    i18n_uchar buffer[BUFSIZE] = { 0 };

    ret = i18n_plural_rules_select_double(plural_rules, number, BUFSIZE, buffer, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_select_double_n2
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_select_int32 passing invalid
 *              plural_rules and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_select_double_n2(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    double number = 1;
    i18n_uchar buffer[BUFSIZE] = { 0 };

    int output_length = -1;
    ret = i18n_plural_rules_select_double(NULL, number, BUFSIZE, buffer, &output_length);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_get_keywords_p
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_get_keywords and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_rules_get_keywords_p(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uenumeration_h result = NULL;

    ret = i18n_plural_rules_get_keywords(plural_rules, &result);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(result, NULL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_get_keywords_n
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_get_keywords passing invalid
 *              string_enum and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_get_keywords_n(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_rules_get_keywords(plural_rules, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_get_keywords_n2
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_get_keywords passing invalid
 *              plural_rules and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_get_keywords_n2(void)
{
    i18n_uenumeration_h result = NULL;
    ret = i18n_plural_rules_get_keywords(NULL, result);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_get_samples_p
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_get_samples and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_rules_get_samples_p(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    double array[BUFSIZE] = { 0 };
    const char *keyword = "few";
    int count = -1;

    ret = i18n_plural_rules_get_samples(plural_rules, keyword, array, BUFSIZE, &count);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_get_samples_n
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_get_samples passing invalid
 *              plural_rules and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_get_samples_n(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    double array[BUFSIZE] = { 0 };
    const char *keyword = "few";
    int count = -1;

    ret = i18n_plural_rules_get_samples(NULL, keyword, array, BUFSIZE, &count);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_get_samples_n2
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_get_samples passing invalid
 *              output_buffer buffer and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_get_samples_n2(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *keyword = "few";
    int count = -1;

    ret = i18n_plural_rules_get_samples(plural_rules, keyword, NULL, BUFSIZE, &count);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_get_samples_n3
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_get_samples passing invalid
 *              output_buffer_size and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_get_samples_n3(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    double array[BUFSIZE] = { 0 };
    const char *keyword = "few";
    int count = -1;

    ret = i18n_plural_rules_get_samples(plural_rules, keyword, array, -1, &count);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_get_samples_n4
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_get_samples passing invalid
 *              count and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_get_samples_n4(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    double array[BUFSIZE] = { 0 };
    const char *keyword = "few";

    ret = i18n_plural_rules_get_samples(plural_rules, keyword, array, BUFSIZE, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_is_keyword_p
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_is_keyword and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_rules_is_keyword_p(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubool is_keyword = false;
    const char *keyword = "one";

    ret = i18n_plural_rules_is_keyword(plural_rules, keyword, &is_keyword);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_keyword, true);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_is_keyword_p2
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_is_keyword and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_rules_is_keyword_p2(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubool is_keyword = false;
    const char *keyword = "few";

    ret = i18n_plural_rules_is_keyword(plural_rules, keyword, &is_keyword);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_keyword, true);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_is_keyword_p3
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_is_keyword and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_rules_is_keyword_p3(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubool is_keyword = true;
    const char *keyword = "false_keyword";

    ret = i18n_plural_rules_is_keyword(plural_rules, keyword, &is_keyword);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_keyword, false);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_is_keyword_n
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_is_keyword passing invalid
 *              plural_rules and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_is_keyword_n(void)
{
    i18n_ubool is_keyword = false;
    const char *keyword = "one";

    ret = i18n_plural_rules_is_keyword(NULL, keyword, &is_keyword);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_is_keyword_n2
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_is_keyword passing invalid
 *              is_keyword and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_is_keyword_n2(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *keyword = "one";

    ret = i18n_plural_rules_is_keyword(plural_rules, keyword, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_get_keyword_other_p
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_get_keyword_other and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_rules_get_keyword_other_p(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *output_string = "other";
    i18n_uchar buffer[BUFSIZE] = { 0 };

    int output_length = -1;
    ret = i18n_plural_rules_get_keyword_other(plural_rules, BUFSIZE, buffer, &output_length);

    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, buffer, BUFSIZE);
    assert_eq(ret, I18N_ERROR_NONE);

    assert_eq(strncmp(output_buffer, output_string, strlen(output_string)), 0);
    assert_eq(output_length, strlen(output_string));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_get_keyword_other_n
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_get_keyword_other passing invalid
 *              plural_rules and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_get_keyword_other_n(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar buffer[BUFSIZE] = { 0 };

    int output_length = -1;
    ret = i18n_plural_rules_get_keyword_other(NULL, BUFSIZE, buffer, &output_length);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_get_keyword_other_n2
 * @since_tizen 4.0
 * @description Calls i18n_plural_rules_get_keyword_other passing invalid
 *              output_length and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_get_keyword_other_n2(void)
{
    assert_neq(plural_rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar buffer[BUFSIZE] = { 0 };

    ret = i18n_plural_rules_get_keyword_other(plural_rules, BUFSIZE, buffer, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_for_locale_id_p
 * @since_tizen 5.0
 * @description Calls i18n_plural_rules_for_locale_id and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_rules_for_locale_id_p(void)
{
    utc_capi_base_utils_plural_rules_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_rules, NULL);

    const char *locale_id = "en_US";

    ret = i18n_plural_rules_for_locale_id(locale_id, I18N_UPLURAL_TYPE_CARDINAL, &plural_rules);

    assert_neq(rules, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_rules_for_locale_id_n
 * @since_tizen 5.0
 * @description Calls i18n_plural_rules_for_locale_id passing invalid
 *              plural_rules and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_rules_for_locale_id_n(void)
{
    const char *locale_id = "en_US";

    ret = i18n_plural_rules_for_locale_id(locale_id, I18N_UPLURAL_TYPE_CARDINAL, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
