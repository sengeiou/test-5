#include "assert.h"
#include <utils_i18n.h>
#include <string.h>
#include <dlog.h>

#define BUFSIZE 256

static i18n_plural_format_h plural_format = NULL;
static i18n_plural_rules_h plural_rules = NULL;
static i18n_field_position_h field_position = NULL;
static i18n_formattable_h formattable = NULL;
static i18n_unumber_format_h number_format = NULL;

static int ret = I18N_ERROR_NONE;
static const char *start_string = "Sample: ";
static const char *pattern = "one{pes} two{psa} few{psi} other{psov}";
static const char *locale = "en_US";

/**
 * @function        utc_capi_base_utils_plural_format_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_plural_format_startup(void)
{
    ret = i18n_plural_format_create(&plural_format);
}

/**
 * @function        utc_capi_base_utils_plural_format_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_plural_format_cleanup(void)
{
    if (plural_format != NULL) {
        ret = i18n_plural_format_destroy(plural_format);
        plural_format = NULL;
    }

    if (plural_rules != NULL) {
        ret = i18n_plural_rules_destroy(plural_rules);
        plural_rules = NULL;
    }
    if (field_position != NULL) {
        ret = i18n_field_position_destroy(field_position);
        field_position = NULL;
    }
    if (formattable != NULL) {
        ret = i18n_formattable_destroy(formattable);
        formattable = NULL;
    }
    if (number_format != NULL) {
        ret = i18n_unumber_destroy(number_format);
        number_format = NULL;
    }
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_p
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_create_p(void)
{
    utc_capi_base_utils_plural_format_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_format, NULL);

    ret = i18n_plural_format_create(&plural_format);

    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_n
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create passing invalid plural_format
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_create_n(void)
{
    ret = i18n_plural_format_create(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_locale_p
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_locale and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_locale_p(void)
{
    utc_capi_base_utils_plural_format_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_format, NULL);

    ret = i18n_plural_format_create_from_locale(locale, &plural_format);

    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_locale_n
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_locale passing invalid plural_format
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_locale_n(void)
{
    ret = i18n_plural_format_create_from_locale(locale, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_rules_pattern_p
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_rules_pattern and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_rules_pattern_p(void)
{
    utc_capi_base_utils_plural_format_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_format, NULL);

    i18n_plural_rules_create(&plural_rules);

    ret = i18n_plural_format_create_from_rules_pattern(plural_rules, pattern, &plural_format);

    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_rules_pattern_n
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_rules_pattern passing invalid plural_format
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_rules_pattern_n(void)
{
    i18n_plural_rules_create(&plural_rules);

    ret = i18n_plural_format_create_from_rules_pattern(plural_rules, pattern, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_rules_pattern_n2
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_rules_pattern passing invalid plural_rules
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_rules_pattern_n2(void)
{
    ret = i18n_plural_format_create_from_rules_pattern(NULL, pattern, &plural_rules);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_rules_pattern_n3
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_rules_pattern passing invalid pattern
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_rules_pattern_n3(void)
{
    i18n_plural_rules_create(&plural_rules);

    ret = i18n_plural_format_create_from_rules_pattern(plural_rules, NULL, &plural_rules);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_locale_type_pattern_p
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_locale_type_pattern and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_locale_type_pattern_p(void)
{
   utc_capi_base_utils_plural_format_cleanup();
   assert_eq(ret, I18N_ERROR_NONE);
   assert_eq(plural_format, NULL);

   ret = i18n_plural_format_create_from_locale_type_pattern(locale,
                                                            I18N_UPLURAL_TYPE_CARDINAL,
                                                            pattern,
                                                            &plural_format);

   assert_neq(plural_format, NULL);
   assert_eq(ret, I18N_ERROR_NONE);

   return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_locale_type_pattern_n
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_locale_type_pattern passing invalid plural_format
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_locale_type_pattern_n(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_create_from_locale_type_pattern(locale,
                                                             I18N_UPLURAL_TYPE_CARDINAL,
                                                             pattern,
                                                             NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_locale_type_pattern_n2
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_locale_type_pattern passing invalid type
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_locale_type_pattern_n2(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_create_from_locale_type_pattern(locale,
                                                             5,
                                                             pattern,
                                                             &plural_format);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_locale_type_pattern_n3
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_locale_type_pattern passing invalid pattern
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_locale_type_pattern_n3(void)
{
   utc_capi_base_utils_plural_format_cleanup();
   assert_eq(ret, I18N_ERROR_NONE);
   assert_eq(plural_format, NULL);

   ret = i18n_plural_format_create_from_locale_type_pattern(locale,
                                                            I18N_UPLURAL_TYPE_CARDINAL,
                                                            NULL,
                                                            &plural_format);

   assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

   return 0;
}


/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_locale_type_p
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_locale_type and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_locale_type_p(void)
{
   utc_capi_base_utils_plural_format_cleanup();
   assert_eq(ret, I18N_ERROR_NONE);
   assert_eq(plural_format, NULL);

   ret = i18n_plural_format_create_from_locale_type(locale, I18N_UPLURAL_TYPE_CARDINAL, &plural_format);

   assert_neq(plural_format, NULL);
   assert_eq(ret, I18N_ERROR_NONE);

   return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_locale_type_n
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_locale_type passing invalid plural_format
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_locale_type_n(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_create_from_locale_type(locale, I18N_UPLURAL_TYPE_CARDINAL, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_locale_type_n2
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_locale_type passing invalid type
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_locale_type_n2(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_create_from_locale_type(locale, 5, &plural_format);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_locale_pattern_p
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_locale_pattern and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_locale_pattern_p(void)
{
   utc_capi_base_utils_plural_format_cleanup();
   assert_eq(ret, I18N_ERROR_NONE);
   assert_eq(plural_format, NULL);

   ret = i18n_plural_format_create_from_locale_pattern(locale, pattern, &plural_format);

   assert_neq(plural_format, NULL);
   assert_eq(ret, I18N_ERROR_NONE);

   return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_locale_pattern_n
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_locale_pattern passing invalid plural_format
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_locale_pattern_n(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_create_from_locale_pattern(locale, pattern, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_locale_pattern_n2
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_locale_pattern passing invalid pattern
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_locale_pattern_n2(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_create_from_locale_pattern(locale, NULL, &plural_format);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_locale_pattern_n3
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_locale_pattern passing invalid pattern
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_locale_pattern_n3(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_create_from_locale_pattern(locale, "qweasd", &plural_format);

    assert_neq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_locale_rules_pattern_p
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_locale_rules_pattern and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_locale_rules_pattern_p(void)
{
   utc_capi_base_utils_plural_format_cleanup();
   assert_eq(ret, I18N_ERROR_NONE);
   assert_eq(plural_format, NULL);

   i18n_plural_rules_create(&plural_rules);

   ret = i18n_plural_format_create_from_locale_rules_pattern(locale, plural_rules, pattern, &plural_format);

   assert_neq(plural_format, NULL);
   assert_eq(ret, I18N_ERROR_NONE);

   return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_locale_rules_pattern_n
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_locale_rules_pattern passing invalid plural_format
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_locale_rules_pattern_n(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_plural_rules_create(&plural_rules);

    ret = i18n_plural_format_create_from_locale_rules_pattern(locale, plural_rules, pattern, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_locale_rules_pattern_n2
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_locale_rules_pattern passing invalid plural_rules
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_locale_rules_pattern_n2(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_create_from_locale_rules_pattern(locale, NULL, pattern, &plural_format);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_create_from_locale_rules_pattern_n3
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_create_from_locale_rules_pattern passing invalid pattern
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_create_from_locale_rules_pattern_n3(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_plural_rules_create(&plural_rules);

    ret = i18n_plural_format_create_from_locale_rules_pattern(locale, plural_rules, NULL, &plural_format);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_destroy_p
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_destroy_p(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_destroy(plural_format);

    assert_eq(ret, I18N_ERROR_NONE);

    plural_format = NULL;

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_destroy_n
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_destroy passing invalid
 *              plural_format and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_destroy_n(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_destroy(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_clone_p
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_clone and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_clone_p(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_plural_format_h clone = NULL;

    ret = i18n_plural_format_clone(plural_format, &clone);

    assert_neq(clone, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_clone_n
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_clone passing invalid
 *              plural_format and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_clone_n(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_plural_format_h clone = NULL;

    ret = i18n_plural_format_clone(NULL, &clone);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_clone_n2
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_clone passing invalid
 *              clone and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_clone_n2(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_clone(plural_format, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_apply_pattern_p
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_apply_pattern and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_apply_pattern_p(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_apply_pattern(plural_format, pattern);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_apply_pattern_n
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_apply_pattern passing invalid
 *              plural_format and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_apply_pattern_n(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_apply_pattern(NULL, pattern);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_apply_pattern_n2
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_apply_pattern passing invalid
 *              pattern and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_apply_pattern_n2(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_apply_pattern(plural_format, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_format_int32_p
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_format_int32 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_format_int32_p(void)
{
    const char *output_string = "Sample: psov";

    utc_capi_base_utils_plural_format_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_format, NULL);

    ret = i18n_plural_format_create_from_locale_pattern(locale, pattern, &plural_format);

    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t number = 4;
    int output_length = -1;
    ret = i18n_plural_format_format_int32(plural_format,
                                          number,
                                          field_position,
                                          BUFSIZE,
                                          append_to,
                                          &output_length);

    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(output_buffer, output_string), 0);
    assert_eq(output_length, strnlen(output_string, BUFSIZE));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_format_int32_p2
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_format_int32 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_format_int32_p2(void)
{
    const char *output_string = "Sample: pes";

    utc_capi_base_utils_plural_format_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_format, NULL);

    ret = i18n_plural_format_create_from_locale_pattern(locale, pattern, &plural_format);

    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t number = 1;
    int output_length = -1;
    ret = i18n_plural_format_format_int32(plural_format,
                                          number,
                                          field_position,
                                          BUFSIZE,
                                          append_to,
                                          &output_length);

    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(output_buffer, output_string), 0);
    assert_eq(output_length, strnlen(output_string, BUFSIZE));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_format_int32_p3
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_format_int32 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_format_int32_p3(void)
{
    const char *output_string = "Sample: 10";

    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t number = 10;
    int output_length = -1;
    ret = i18n_plural_format_format_int32(plural_format,
                                          number,
                                          field_position,
                                          BUFSIZE,
                                          append_to,
                                          &output_length);

    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(output_buffer, output_string), 0);
    assert_eq(output_length, strnlen(output_string, BUFSIZE));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_format_int32_n
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_format_int32 passing invalid
 *              plural_format and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_format_int32_n(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t number = 4;
    int output_length = -1;
    ret = i18n_plural_format_format_int32(NULL,
                                          number,
                                          field_position,
                                          BUFSIZE,
                                          append_to,
                                          &output_length);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);


    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_format_int32_n2
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_format_int32 passing invalid
 *              field_position and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_format_int32_n2(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    int32_t number = 4;
    int output_length = -1;
    ret = i18n_plural_format_format_int32(plural_format,
                                          number,
                                          NULL,
                                          BUFSIZE,
                                          append_to,
                                          &output_length);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);


    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_format_int32_n3
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_format_int32 passing invalid
 *              output_length and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_format_int32_n3(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t number = 4;
    ret = i18n_plural_format_format_int32(NULL,
                                          number,
                                          field_position,
                                          BUFSIZE,
                                          append_to,
                                          NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);


    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_format_double_p
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_format_double and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_format_double_p(void)
{
    const char *output_string = "Sample: psov";

    utc_capi_base_utils_plural_format_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_format, NULL);

    ret = i18n_plural_format_create_from_locale_pattern(locale, pattern, &plural_format);

    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    double number = 4;
    int output_length = -1;
    ret = i18n_plural_format_format_double(plural_format,
                                          number,
                                          field_position,
                                          BUFSIZE,
                                          append_to,
                                          &output_length);

    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(output_buffer, output_string), 0);
    assert_eq(output_length, strnlen(output_string, BUFSIZE));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_format_double_p2
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_format_double and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_format_double_p2(void)
{
    const char *output_string = "Sample: pes";

    utc_capi_base_utils_plural_format_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_format, NULL);

    ret = i18n_plural_format_create_from_locale_pattern(locale, pattern, &plural_format);

    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    double number = 1;
    int output_length = -1;
    ret = i18n_plural_format_format_double(plural_format,
                                          number,
                                          field_position,
                                          BUFSIZE,
                                          append_to,
                                          &output_length);

    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(output_buffer, output_string), 0);
    assert_eq(output_length, strnlen(output_string, BUFSIZE));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_format_double_p3
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_format_double and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_format_double_p3(void)
{
    const char *output_string = "Sample: 10";

    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    double number = 10;
    int output_length = -1;
    ret = i18n_plural_format_format_double(plural_format,
                                          number,
                                          field_position,
                                          BUFSIZE,
                                          append_to,
                                          &output_length);

    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(output_buffer, output_string), 0);
    assert_eq(output_length, strnlen(output_string, BUFSIZE));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_format_double_n
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_format_double passing invalid
 *              plural_format and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_format_double_n(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    double number = 4;
    int output_length = -1;
    ret = i18n_plural_format_format_double(NULL,
                                          number,
                                          field_position,
                                          BUFSIZE,
                                          append_to,
                                          &output_length);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);


    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_format_double_n2
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_format_double passing invalid
 *              field_position and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_format_double_n2(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    double number = 4;
    int output_length = -1;
    ret = i18n_plural_format_format_double(plural_format,
                                          number,
                                          NULL,
                                          BUFSIZE,
                                          append_to,
                                          &output_length);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);


    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_format_double_n3
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_format_double passing invalid
 *              output_length and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_format_double_n3(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    double number = 4;
    ret = i18n_plural_format_format_double(NULL,
                                          number,
                                          field_position,
                                          BUFSIZE,
                                          append_to,
                                          NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);


    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_format_formattable_p
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_format_formattable and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_format_formattable_p(void)
{
    const char *output_string = "Sample: psov";

    utc_capi_base_utils_plural_format_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_format, NULL);

    ret = i18n_plural_format_create_from_locale_pattern(locale, pattern, &plural_format);

    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_formattable_h formattable;
    ret = i18n_formattable_create_with_double(4, &formattable);
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_plural_format_format_formattable(plural_format,
                                                formattable,
                                                field_position,
                                                BUFSIZE,
                                                append_to,
                                                &output_length);

    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(output_buffer, output_string), 0);
    assert_eq(output_length, strnlen(output_string, BUFSIZE));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_format_formattable_p2
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_format_formattable and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_format_formattable_p2(void)
{
    const char *output_string = "Sample: pes";

    utc_capi_base_utils_plural_format_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_format, NULL);

    ret = i18n_plural_format_create_from_locale_pattern(locale, pattern, &plural_format);

    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_formattable_create_with_double(1, &formattable);
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_plural_format_format_formattable(plural_format,
                                                formattable,
                                                field_position,
                                                BUFSIZE,
                                                append_to,
                                                &output_length);

    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(output_buffer, output_string), 0);
    assert_eq(output_length, strnlen(output_string, BUFSIZE));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_format_formattable_p3
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_format_formattable and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_format_formattable_p3(void)
{
    const char *output_string = "Sample: 10";

    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_formattable_create_with_double(10, &formattable);
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_plural_format_format_formattable(plural_format,
                                                formattable,
                                                field_position,
                                                BUFSIZE,
                                                append_to,
                                                &output_length);

    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(output_buffer, output_string), 0);
    assert_eq(output_length, strnlen(output_string, BUFSIZE));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_format_formattable_n
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_format_formattable passing invalid
 *              plural_format and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_format_formattable_n(void)
{
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_formattable_create_with_double(4, &formattable);
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_plural_format_format_formattable(NULL,
                                                formattable,
                                                field_position,
                                                BUFSIZE,
                                                append_to,
                                                &output_length);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_format_formattable_n2
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_format_formattable passing invalid
 *              formattable and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_format_formattable_n2(void)
{
    utc_capi_base_utils_plural_format_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_format, NULL);

    ret = i18n_plural_format_create_from_locale_pattern(locale, pattern, &plural_format);

    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_plural_format_format_formattable(plural_format,
                                                NULL,
                                                field_position,
                                                BUFSIZE,
                                                append_to,
                                                &output_length);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_format_formattable_n3
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_format_formattable passing invalid
 *              field_position and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_format_formattable_n3(void)
{
    utc_capi_base_utils_plural_format_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_format, NULL);

    ret = i18n_plural_format_create_from_locale_pattern(locale, pattern, &plural_format);

    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_formattable_create_with_double(4, &formattable);
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_plural_format_format_formattable(plural_format,
                                                formattable,
                                                NULL,
                                                BUFSIZE,
                                                append_to,
                                                &output_length);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_format_formattable_n4
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_format_formattable passing invalid
 *              output_length and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_format_formattable_n4(void)
{
    utc_capi_base_utils_plural_format_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_format, NULL);

    ret = i18n_plural_format_create_from_locale_pattern(locale, pattern, &plural_format);

    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_formattable_create_with_double(4, &formattable);
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_format_formattable(plural_format,
                                                formattable,
                                                field_position,
                                                BUFSIZE,
                                                append_to,
                                                NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_set_number_format_p
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_set_number_format and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_set_number_format_p(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uparse_error_s parse_err;
    ret = i18n_unumber_create(I18N_UNUMBER_NUMBERING_SYSTEM, NULL, -1,
                              locale, &parse_err, &number_format);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_set_number_format(plural_format, number_format);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_set_number_format_n
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_set_number_format passing invalid
 *              plural_format and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_set_number_format_n(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uparse_error_s parse_err;
    ret = i18n_unumber_create(I18N_UNUMBER_NUMBERING_SYSTEM, NULL, -1,
                              locale, &parse_err, &number_format);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_set_number_format(NULL, number_format);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_set_number_format_n2
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_set_number_format passing invalid
 *              number_format and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_set_number_format_n2(void)
{
    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_set_number_format(plural_format, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_to_pattern_p
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_to_pattern and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_plural_format_to_pattern_p(void)
{
    const char *output_string = "Sample: one{pes} two{psa} few{psi} other{psov}";

    utc_capi_base_utils_plural_format_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_format, NULL);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_create_from_locale_pattern(locale, pattern, &plural_format);

    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t output_length = -1;
    ret = i18n_plural_format_to_pattern(plural_format,
                                        field_position,
                                        BUFSIZE,
                                        append_to,
                                        &output_length);

    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(output_buffer, output_string), 0);
    assert_eq(output_length, strnlen(output_string, BUFSIZE));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_to_pattern_n
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_to_pattern passing invalid
 *              plural_format and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_to_pattern_n(void)
{
    utc_capi_base_utils_plural_format_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_format, NULL);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t output_length = -1;
    ret = i18n_plural_format_to_pattern(NULL,
                                        field_position,
                                        BUFSIZE,
                                        append_to,
                                        &output_length);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_to_pattern_n2
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_to_pattern passing invalid
 *              field_position and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_to_pattern_n2(void)
{
    utc_capi_base_utils_plural_format_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_format, NULL);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_plural_format_create_from_locale_pattern(locale, pattern, &plural_format);

    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t output_length = -1;
    ret = i18n_plural_format_to_pattern(plural_format,
                                        NULL,
                                        BUFSIZE,
                                        append_to,
                                        &output_length);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_plural_format_to_pattern_n3
 * @since_tizen 5.0
 * @description Calls i18n_plural_format_to_pattern passing invalid
 *              output_length and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_plural_format_to_pattern_n3(void)
{
    utc_capi_base_utils_plural_format_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(plural_format, NULL);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, start_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_create_from_locale_pattern(locale, pattern, &plural_format);

    assert_neq(plural_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_plural_format_to_pattern(plural_format,
                                        field_position,
                                        BUFSIZE,
                                        append_to,
                                        NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
