#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

#define BUFSIZE 256

static int ret = I18N_ERROR_NONE;
static i18n_simple_date_fmt_h date_fmt = NULL;
static i18n_field_position_h field_pos = NULL;
static i18n_parse_position_h parse_pos = NULL;
static i18n_ucalendar_h calendar = NULL;
static const char *pattern = "EEE, MMM d, yyyy";
static const char *override = "y=hanidec;M=hans;d=hans";
static const char *locale = "en_US";



/**
 * @function        utc_capi_base_utils_simple_date_fmt_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_simple_date_fmt_startup(void)
{
    ret = i18n_simple_date_fmt_create_from_pattern_locale(pattern, locale,  &date_fmt);
}

/**
 * @function        utc_capi_base_utils_simple_date_fmt_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_simple_date_fmt_cleanup(void)
{
    if (date_fmt != NULL) {
        i18n_simple_date_fmt_destroy(date_fmt);
        date_fmt = NULL;
    }

    if (field_pos != NULL) {
        i18n_field_position_destroy(field_pos);
        field_pos = NULL;
    }

    if (calendar != NULL) {
        i18n_ucalendar_destroy(calendar);
        calendar = NULL;
    }

    if (parse_pos != NULL) {
        i18n_parse_position_destroy(parse_pos);
        parse_pos = NULL;
    }
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_create_p
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_create_p(void)
{
    utc_capi_base_utils_simple_date_fmt_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(date_fmt, NULL);

    ret = i18n_simple_date_fmt_create(&date_fmt);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_fmt, NULL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_create_n
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_create passing invalid simple_date_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_create_n(void)
{
    ret = i18n_simple_date_fmt_create(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_p
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_create_from_pattern and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_p(void)
{
    utc_capi_base_utils_simple_date_fmt_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(date_fmt, NULL);

    ret = i18n_simple_date_fmt_create_from_pattern(pattern, &date_fmt);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_fmt, NULL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_n
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_create_from_pattern passing invalid simple_date_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_n(void)
{
    ret = i18n_simple_date_fmt_create_from_pattern(pattern, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_n2
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_create_from_pattern passing invalid pattern
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_n2(void)
{
    ret = i18n_simple_date_fmt_create_from_pattern(NULL, date_fmt);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_override_p
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_create_from_pattern_override and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_override_p(void)
{
    utc_capi_base_utils_simple_date_fmt_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(date_fmt, NULL);

    ret = i18n_simple_date_fmt_create_from_pattern_override(pattern, override, &date_fmt);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_fmt, NULL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_override_n
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_create_from_pattern_override passing invalid simple_date_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_override_n(void)
{
    ret = i18n_simple_date_fmt_create_from_pattern_override(pattern, override, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_override_n2
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_create_from_pattern_override passing invalid pattern
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_override_n2(void)
{
    ret = i18n_simple_date_fmt_create_from_pattern_override(NULL, override, date_fmt);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_override_n3
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_create_from_pattern_override passing invalid override
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_override_n3(void)
{
    ret = i18n_simple_date_fmt_create_from_pattern_override(pattern, NULL, date_fmt);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_locale_p
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_create_from_pattern_locale and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_locale_p(void)
{
    utc_capi_base_utils_simple_date_fmt_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(date_fmt, NULL);

    ret = i18n_simple_date_fmt_create_from_pattern_locale(pattern, locale, &date_fmt);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_fmt, NULL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_locale_n
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_create_from_pattern_locale passing invalid simple_date_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_locale_n(void)
{
    ret = i18n_simple_date_fmt_create_from_pattern_locale(pattern, locale, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_locale_n2
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_create_from_pattern_locale passing invalid pattern
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_locale_n2(void)
{
    ret = i18n_simple_date_fmt_create_from_pattern_locale(NULL, locale, date_fmt);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_locale_n3
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_create_from_pattern_locale passing invalid locale
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_locale_n3(void)
{
    ret = i18n_simple_date_fmt_create_from_pattern_locale(pattern, NULL, date_fmt);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_override_locale_p
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_create_from_pattern_override_locale and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_override_locale_p(void)
{
    utc_capi_base_utils_simple_date_fmt_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(date_fmt, NULL);

    ret = i18n_simple_date_fmt_create_from_pattern_override_locale(pattern, override, locale, &date_fmt);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_fmt, NULL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_override_locale_n
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_create_from_pattern_override_locale passing invalid simple_date_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_override_locale_n(void)
{
    ret = i18n_simple_date_fmt_create_from_pattern_override_locale(pattern, override, locale, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_override_locale_n2
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_create_from_pattern_override_locale passing invalid pattern
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_override_locale_n2(void)
{
    ret = i18n_simple_date_fmt_create_from_pattern_override_locale(NULL, override, locale, date_fmt);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_override_locale_n3
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_create_from_pattern_override_locale passing invalid override
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_override_locale_n3(void)
{
    ret = i18n_simple_date_fmt_create_from_pattern_override_locale(pattern, NULL, locale, date_fmt);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_override_locale_n4
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_create_from_pattern_override_locale passing invalid locale
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_create_from_pattern_override_locale_n4(void)
{
    ret = i18n_simple_date_fmt_create_from_pattern_override_locale(pattern, override, NULL, date_fmt);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_destroy_p
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_destroy_p(void)
{
    ret = i18n_simple_date_fmt_destroy(date_fmt);
    assert_eq(ret, I18N_ERROR_NONE);
    date_fmt = NULL;

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_destroy_n
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_destroy passing invalid simple_date_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_destroy_n(void)
{
    ret = i18n_simple_date_fmt_destroy(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_clone_p
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_clone and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_clone_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_fmt, NULL);

    i18n_simple_date_fmt_h clone = NULL;

    ret = i18n_simple_date_fmt_clone(date_fmt, &clone);

    assert_eq(ret, I18N_ERROR_NONE);
    i18n_simple_date_fmt_destroy(clone);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_clone_n
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_clone passing invalid simple_date_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_clone_n(void)
{
    i18n_simple_date_fmt_h clone = NULL;
    ret = i18n_simple_date_fmt_clone(NULL, &clone);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_clone_n2
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_clone passing invalid clone
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_clone_n2(void)
{
    ret = i18n_simple_date_fmt_clone(date_fmt, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_equals_p
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_equals and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_equals_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_fmt, NULL);

    i18n_simple_date_fmt_h to_compare = NULL;
    bool is_equal = false;

    ret = i18n_simple_date_fmt_clone(date_fmt, &to_compare);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_simple_date_fmt_equals(date_fmt, to_compare, &is_equal);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_equal, true);

    i18n_simple_date_fmt_destroy(to_compare);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_equals_p2
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_equals and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_equals_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_fmt, NULL);

    i18n_simple_date_fmt_h to_compare = NULL;
    bool is_equal = false;

    ret = i18n_simple_date_fmt_create_from_pattern_override("MMM d, yyyy", override, &to_compare);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_simple_date_fmt_equals(date_fmt, to_compare, &is_equal);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_equal, false);

    i18n_simple_date_fmt_destroy(to_compare);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_equals_n
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_equals passing invalid simple_date_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_equals_n(void)
{
    i18n_simple_date_fmt_h to_compare = NULL;
    bool is_equal = false;

    ret = i18n_simple_date_fmt_clone(date_fmt, &to_compare);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_simple_date_fmt_equals(NULL, to_compare, &is_equal);

    i18n_simple_date_fmt_destroy(to_compare);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_equals_n2
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_equals passing invalid to_compare
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_equals_n2(void)
{
    i18n_simple_date_fmt_h to_compare = NULL;
    bool is_equal = false;

    ret = i18n_simple_date_fmt_clone(date_fmt, &to_compare);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_simple_date_fmt_equals(date_fmt, NULL, &is_equal);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_equals_n3
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_equals passing invalid is_equal
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_equals_n3(void)
{
    i18n_simple_date_fmt_h to_compare = NULL;

    ret = i18n_simple_date_fmt_clone(date_fmt, &to_compare);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_simple_date_fmt_equals(date_fmt, to_compare, NULL);

    i18n_simple_date_fmt_destroy(to_compare);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_format_with_field_position_p
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_format_with_field_position and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_format_with_field_position_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_fmt, NULL);

    const char *result = "Date: Thu, Feb 1, 2018";
    char *append_to = malloc(sizeof(char) * BUFSIZE);
    snprintf(append_to, BUFSIZE, "Date: ");

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_pos);
    assert_neq(field_pos, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ucalendar_create(NULL, -1, locale, I18N_UCALENDAR_DEFAULT, &calendar);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(calendar, NULL);

    i18n_ucalendar_set_date_time(calendar, 2018, 1, 1, 12, 0, 0);

    ret = i18n_simple_date_fmt_format_with_field_position(date_fmt, calendar, &append_to, field_pos);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(result, append_to), 0);
    free(append_to);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_format_with_field_position_n
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_format_with_field_position passing invalid simple_date_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_format_with_field_position_n(void)
{
    char *append_to = malloc(sizeof(char) * BUFSIZE);
    snprintf(append_to, BUFSIZE, "Date: ");

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_pos);
    assert_neq(field_pos, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ucalendar_create(NULL, -1, locale, I18N_UCALENDAR_DEFAULT, &calendar);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(calendar, NULL);

    i18n_ucalendar_set_date_time(calendar, 2018, 1, 1, 12, 0, 0);

    ret = i18n_simple_date_fmt_format_with_field_position(NULL, calendar, &append_to, field_pos);

    free(append_to);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_format_with_field_position_n2
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_format_with_field_position passing invalid calendar
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_format_with_field_position_n2(void)
{
    char *append_to = malloc(sizeof(char) * BUFSIZE);
    snprintf(append_to, BUFSIZE, "Date: ");

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_pos);
    assert_neq(field_pos, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_simple_date_fmt_format_with_field_position(date_fmt, NULL, &append_to, field_pos);

    free(append_to);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_format_with_field_position_n3
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_format_with_field_position passing invalid append_to
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_format_with_field_position_n3(void)
{
    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_pos);
    assert_neq(field_pos, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ucalendar_create(NULL, -1, locale, I18N_UCALENDAR_DEFAULT, &calendar);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(calendar, NULL);

    i18n_ucalendar_set_date_time(calendar, 2018, 1, 1, 12, 0, 0);

    ret = i18n_simple_date_fmt_format_with_field_position(date_fmt, calendar, NULL, field_pos);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_format_with_field_position_n4
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_format_with_field_position passing invalid field_position
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_format_with_field_position_n4(void)
{
    char *append_to = malloc(sizeof(char) * BUFSIZE);
    snprintf(append_to, BUFSIZE, "Date: ");

    ret = i18n_ucalendar_create(NULL, -1, locale, I18N_UCALENDAR_DEFAULT, &calendar);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(calendar, NULL);

    i18n_ucalendar_set_date_time(calendar, 2018, 1, 1, 12, 0, 0);

    ret = i18n_simple_date_fmt_format_with_field_position(date_fmt, calendar, &append_to, NULL);

    free(append_to);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_parse_p
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_parse and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_parse_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_fmt, NULL);

    const char *source = "08/12/2016 4:5 PM, PDT";
    ret = i18n_parse_position_create(&parse_pos);
    assert_neq(parse_pos, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_simple_date_fmt_parse(date_fmt, source, parse_pos, &calendar);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(calendar, NULL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_parse_n
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_parse passing invalid simple_date_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_parse_n(void)
{
    const char *source = "08/12/2016 4:5 PM, PDT";
    ret = i18n_parse_position_create(&parse_pos);
    assert_neq(parse_pos, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_simple_date_fmt_parse(NULL, source, parse_pos, &calendar);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_parse_n2
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_parse passing invalid source
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_parse_n2(void)
{
    ret = i18n_parse_position_create(&parse_pos);
    assert_neq(parse_pos, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_simple_date_fmt_parse(date_fmt, NULL, parse_pos, &calendar);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_parse_n3
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_parse passing invalid parse_position
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_parse_n3(void)
{
    const char *source = "08/12/2016 4:5 PM, PDT";

    ret = i18n_simple_date_fmt_parse(date_fmt, source, NULL, &calendar);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_parse_n4
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_parse passing invalid calendar
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_parse_n4(void)
{
    const char *source = "08/12/2016 4:5 PM, PDT";
    ret = i18n_parse_position_create(&parse_pos);
    assert_neq(parse_pos, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_simple_date_fmt_parse(date_fmt, source, parse_pos, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_set_2digit_year_start_p
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_set_2digit_year_start and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_set_2digit_year_start_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_fmt, NULL);

    i18n_udate udate = 150000.0;

    ret = i18n_simple_date_fmt_set_2digit_year_start(date_fmt, udate);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_set_2digit_year_start_n
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_set_2digit_year_start passing invalid simple_date_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_set_2digit_year_start_n(void)
{
    i18n_udate udate = 150000.0;

    ret = i18n_simple_date_fmt_set_2digit_year_start(NULL, udate);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_get_2digit_year_start_p
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_get_2digit_year_start and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_get_2digit_year_start_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_fmt, NULL);

    i18n_udate udate = 150000.0;

    ret = i18n_simple_date_fmt_set_2digit_year_start(date_fmt, udate);

    udate = 0.0;

    ret = i18n_simple_date_fmt_get_2digit_year_start(date_fmt, &udate);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(udate, 150000.0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_get_2digit_year_start_n
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_get_2digit_year_start passing invalid simple_date_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_get_2digit_year_start_n(void)
{
    i18n_udate udate = 0.0;

    ret = i18n_simple_date_fmt_get_2digit_year_start(NULL, &udate);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_get_2digit_year_start_n2
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_get_2digit_year_start passing invalid udate
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_get_2digit_year_start_n2(void)
{
    ret = i18n_simple_date_fmt_get_2digit_year_start(date_fmt, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_to_pattern_p
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_to_pattern and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_to_pattern_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_fmt, NULL);

    char *result = malloc(BUFSIZE);

    ret = i18n_simple_date_fmt_to_pattern(date_fmt, &result);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(result, pattern), 0);
    free(result);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_to_pattern_n
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_to_pattern passing invalid simple_date_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_to_pattern_n(void)
{
    char *result = malloc(BUFSIZE);

    ret = i18n_simple_date_fmt_to_pattern(NULL, &result);

    free(result);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_to_pattern_n3
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_to_pattern passing invalid result
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_to_pattern_n3(void)
{
    ret = i18n_simple_date_fmt_to_pattern(date_fmt, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_to_localized_pattern_p
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_to_localized_pattern and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_to_localized_pattern_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_fmt, NULL);

    char *result = malloc(BUFSIZE);

    ret = i18n_simple_date_fmt_to_localized_pattern(date_fmt, &result);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(result, pattern), 0);
    free(result);


    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_to_localized_pattern_n
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_to_localized_pattern passing invalid simple_date_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_to_localized_pattern_n(void)
{
    char *result = malloc(BUFSIZE);

    ret = i18n_simple_date_fmt_to_localized_pattern(NULL, &result);

    free(result);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_to_localized_pattern_n3
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_to_localized_pattern passing invalid result
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_to_localized_pattern_n3(void)
{
    ret = i18n_simple_date_fmt_to_localized_pattern(date_fmt, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_apply_pattern_p
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_apply_pattern and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_apply_pattern_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_fmt, NULL);

    const char *new_pattern = "yyyy.MM.dd G 'at' HH:mm:ss vvvv";

    ret = i18n_simple_date_fmt_apply_pattern(date_fmt, new_pattern);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_apply_pattern_n
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_apply_pattern passing invalid simple_date_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_apply_pattern_n(void)
{
    const char *new_pattern = "yyyy.MM.dd G 'at' HH:mm:ss vvvv";

    ret = i18n_simple_date_fmt_apply_pattern(NULL, new_pattern);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_apply_pattern_n2
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_apply_pattern passing invalid pattern
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_apply_pattern_n2(void)
{
    ret = i18n_simple_date_fmt_apply_pattern(date_fmt, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_apply_localized_pattern_p
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_apply_localized_pattern and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_apply_localized_pattern_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_fmt, NULL);

    const char *new_pattern = "yyyy.MM.dd G 'at' HH:mm:ss vvvv";

    ret = i18n_simple_date_fmt_apply_localized_pattern(date_fmt, new_pattern);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_apply_localized_pattern_n
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_apply_localized_pattern passing invalid
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_apply_localized_pattern_n(void)
{
    const char *new_pattern = "yyyy.MM.dd G 'at' HH:mm:ss vvvv";

    ret = i18n_simple_date_fmt_apply_localized_pattern(NULL, new_pattern);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_apply_localized_pattern_n2
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_apply_localized_pattern passing invalid pattern
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_apply_localized_pattern_n2(void)
{
    ret = i18n_simple_date_fmt_apply_localized_pattern(date_fmt, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_adopt_calendar_p
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_adopt_calendar and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_adopt_calendar_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_fmt, NULL);

    i18n_ucalendar_create(NULL, -1, locale, I18N_UCALENDAR_DEFAULT, &calendar);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(calendar, NULL);

    ret = i18n_simple_date_fmt_adopt_calendar(date_fmt, calendar);
    calendar = NULL;

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_adopt_calendar_n
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_adopt_calendar passing invalid simple_date_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_adopt_calendar_n(void)
{
    i18n_ucalendar_create(NULL, -1, locale, I18N_UCALENDAR_DEFAULT, &calendar);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(calendar, NULL);

    ret = i18n_simple_date_fmt_adopt_calendar(NULL, calendar);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_adopt_calendar_n2
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_adopt_calendar passing invalid calendar
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_adopt_calendar_n2(void)
{
    ret = i18n_simple_date_fmt_adopt_calendar(date_fmt, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_set_context_p
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_set_context and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_set_context_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_fmt, NULL);

    ret = i18n_simple_date_fmt_set_context(date_fmt, I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_MIDDLE_OF_SENTENCE);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_simple_date_fmt_set_context_n
 * @since_tizen 5.0
 * @description Calls i18n_simple_date_fmt_set_context passing invalid simple_date_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_simple_date_fmt_set_context_n(void)
{
    ret = i18n_simple_date_fmt_set_context(NULL, I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_MIDDLE_OF_SENTENCE);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
