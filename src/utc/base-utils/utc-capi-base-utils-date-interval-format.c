#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

#define BUFSIZE 256

static int ret = I18N_ERROR_NONE;
static const char *skeleton = "yMMMMd";
static i18n_date_interval_fmt_h date_int_fmt = NULL;
static i18n_timezone_h timezone = NULL;
static i18n_field_position_h field_pos = NULL;
static const char *locale = "en_US";

/**
 * @function        utc_capi_base_utils_date_interval_fmt_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_date_interval_fmt_startup(void)
{
    ret = i18n_date_interval_fmt_create_from_locale(skeleton, locale, &date_int_fmt);
}

/**
 * @function        utc_capi_base_utils_date_interval_fmt_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_date_interval_fmt_cleanup(void)
{
    if (!date_int_fmt) {
        i18n_date_interval_fmt_destroy(date_int_fmt);
        date_int_fmt = NULL;
    }

    if (!timezone) {
        i18n_timezone_destroy(timezone);
        timezone = NULL;
    }

    if (!field_pos) {
        i18n_field_position_destroy(field_pos);
        field_pos = NULL;
    }
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_create_p
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_create_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_int_fmt, NULL);


    ret = i18n_date_interval_fmt_create(skeleton, &date_int_fmt);

    assert_neq(date_int_fmt, NULL);
    assert_eq(ret, I18N_ERROR_NONE);


    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_create_n
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_create passing invalid date_interval_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_create_n(void)
{
    ret = i18n_date_interval_fmt_create(skeleton, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_create_from_locale_p
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_create_from_locale and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_create_from_locale_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_int_fmt, NULL);

    ret = i18n_date_interval_fmt_create_from_locale(skeleton, locale, &date_int_fmt);

    assert_neq(date_int_fmt, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_create_from_locale_n
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_create_from_locale passing invalid date_interval_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_create_from_locale_n(void)
{
    ret = i18n_date_interval_fmt_create_from_locale(skeleton, locale, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_clone_p
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_clone and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_clone_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_int_fmt, NULL);

    i18n_date_interval_fmt_h clone = NULL;

    ret = i18n_date_interval_fmt_clone(date_int_fmt, &clone);

    assert_neq(clone, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_clone_n
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_clone passing invalid date_interval_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_clone_n(void)
{
    i18n_date_interval_fmt_h clone = NULL;

    ret = i18n_date_interval_fmt_clone(NULL, &clone);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_clone_n2
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_clone passing invalid clone
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_clone_n2(void)
{
    ret = i18n_date_interval_fmt_clone(date_int_fmt, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_destroy_p
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_destroy_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_int_fmt, NULL);

    ret = i18n_date_interval_fmt_destroy(date_int_fmt);

    assert_eq(ret, I18N_ERROR_NONE);
    date_int_fmt = NULL;

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_destroy_n
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_destroy passing invalid date_interval_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_destroy_n(void)
{
    ret = i18n_date_interval_fmt_destroy(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_equals_p
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_equals and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_equals_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_int_fmt, NULL);

    i18n_date_interval_fmt_h date_int_fmt_2 = NULL;
    bool is_equal = false;

    ret = i18n_date_interval_fmt_clone(date_int_fmt, &date_int_fmt_2);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_date_interval_fmt_equals(date_int_fmt, date_int_fmt_2, &is_equal);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_equal, true);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_equals_p2
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_equals and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_equals_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_int_fmt, NULL);

    i18n_date_interval_fmt_h date_int_fmt_2 = NULL;
    const char *skeleton2 = "yMEd";
    bool is_equal = true;

    ret = i18n_date_interval_fmt_create(skeleton2, &date_int_fmt_2);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_date_interval_fmt_equals(date_int_fmt, date_int_fmt_2, &is_equal);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_equal, false);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_equals_n
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_equals passing invalid date_interval_fmt1
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_equals_n(void)
{
    i18n_date_interval_fmt_h date_int_fmt_2 = NULL;
    bool is_equal = false;

    ret = i18n_date_interval_fmt_clone(date_int_fmt, &date_int_fmt_2);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_date_interval_fmt_equals(NULL, date_int_fmt_2, &is_equal);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_equals_n2
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_equals passing invalid date_interval_fmt2
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_equals_n2(void)
{
    bool is_equal = false;

    ret = i18n_date_interval_fmt_equals(date_int_fmt, NULL, &is_equal);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_equals_n3
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_equals passing invalid is_equal
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_equals_n3(void)
{
    i18n_date_interval_fmt_h date_int_fmt_2 = NULL;

    ret = i18n_date_interval_fmt_clone(date_int_fmt, &date_int_fmt_2);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_date_interval_fmt_equals(date_int_fmt, date_int_fmt_2, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_set_time_zone_p
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_set_time_zone and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_set_time_zone_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_int_fmt, NULL);

    ret = i18n_timezone_create(&timezone, "Europe/London");
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_date_interval_fmt_set_time_zone(date_int_fmt, timezone);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_set_time_zone_n
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_set_time_zone passing invalid date_interval_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_set_time_zone_n(void)
{
    ret = i18n_timezone_create(&timezone, "Europe/London");
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_date_interval_fmt_set_time_zone(NULL, timezone);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_set_time_zone_n2
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_set_time_zone passing invalid timezone
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_set_time_zone_n2(void)
{
    ret = i18n_date_interval_fmt_set_time_zone(date_int_fmt, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_get_time_zone_p
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_get_time_zone and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_get_time_zone_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_int_fmt, NULL);

    i18n_timezone_h timezone_2 = NULL;
    char *timezone_id = "";

    ret = i18n_timezone_create(&timezone, "Europe/London");
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_date_interval_fmt_set_time_zone(date_int_fmt, timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_date_interval_fmt_get_time_zone(date_int_fmt, &timezone_2);

    assert_eq(ret, I18N_ERROR_NONE);
    ret = i18n_timezone_get_id(timezone_2, &timezone_id);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(timezone_id, "Europe/London"), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_get_time_zone_n
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_get_time_zone passing invalid date_interval_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_get_time_zone_n(void)
{
    ret = i18n_timezone_create(&timezone, "Europe/London");
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_date_interval_fmt_get_time_zone(NULL, timezone);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_get_time_zone_n2
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_get_time_zone passing invalid timezone
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_get_time_zone_n2(void)
{
    ret = i18n_date_interval_fmt_set_time_zone(date_int_fmt, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_adopt_time_zone_p
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_adopt_time_zone and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_adopt_time_zone_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_int_fmt, NULL);

    i18n_timezone_h timezone_2 = NULL;

    ret = i18n_timezone_create(&timezone_2, "Europe/London");
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_date_interval_fmt_adopt_time_zone(date_int_fmt, timezone_2);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_adopt_time_zone_n
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_adopt_time_zone passing invalid date_interval_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_adopt_time_zone_n(void)
{
    i18n_timezone_h timezone_2 = NULL;

    ret = i18n_timezone_create(&timezone_2, "Europe/London");
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_date_interval_fmt_adopt_time_zone(NULL, timezone_2);
    i18n_timezone_destroy(timezone_2);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_adopt_time_zone_n2
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_adopt_time_zone passing invalid timezone
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_adopt_time_zone_n2(void)
{
    ret = i18n_date_interval_fmt_adopt_time_zone(date_int_fmt, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_format_with_date_interval_p
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_format_with_date_interval and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_format_with_date_interval_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_int_fmt, NULL);

    char *append_to = malloc(sizeof(char) * BUFSIZE);
    snprintf(append_to, BUFSIZE, "Date: ");
    const char *result = "Date: January 1, 1970";
    i18n_date_interval_h date_int = NULL;
    i18n_udate from = 1000000.0;
    i18n_udate to = 1500000.0;

    ret = i18n_date_interval_create(from, to, &date_int);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_int, NULL);

    ret = i18n_field_position_create(&field_pos);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(field_pos, NULL);

    ret = i18n_date_interval_fmt_format_with_date_interval(date_int_fmt,
                                                           date_int,
                                                           &append_to,
                                                           field_pos);
    i18n_date_interval_destroy(date_int);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(append_to, result), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_format_with_date_interval_n
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_format_with_date_interval passing invalid date_interval_fmt
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_format_with_date_interval_n(void)
{
    char *append_to = malloc(sizeof(char) * BUFSIZE);
    snprintf(append_to, BUFSIZE, "Date: ");
    i18n_date_interval_h date_int = NULL;
    i18n_udate from = 1000000.0;
    i18n_udate to = 1500000.0;

    ret = i18n_date_interval_create(from, to, &date_int);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_int, NULL);

    ret = i18n_field_position_create(&field_pos);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(field_pos, NULL);

    ret = i18n_date_interval_fmt_format_with_date_interval(NULL,
                                                           date_int,
                                                           &append_to,
                                                           field_pos);
    i18n_date_interval_destroy(date_int);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_format_with_date_interval_n2
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_format_with_date_interval passing invalid date_interval
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_format_with_date_interval_n2(void)
{
    char *append_to = malloc(sizeof(char) * BUFSIZE);
    snprintf(append_to, BUFSIZE, "Date: ");

    ret = i18n_field_position_create(&field_pos);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(field_pos, NULL);

    ret = i18n_date_interval_fmt_format_with_date_interval(date_int_fmt,
                                                           NULL,
                                                           &append_to,
                                                           field_pos);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_format_with_date_interval_n3
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_format_with_date_interval passing invalid append_to
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_format_with_date_interval_n3(void)
{
    i18n_date_interval_h date_int = NULL;
    i18n_udate from = 1000000.0;
    i18n_udate to = 1500000.0;

    ret = i18n_date_interval_create(from, to, &date_int);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_int, NULL);

    ret = i18n_field_position_create(&field_pos);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(field_pos, NULL);

    ret = i18n_date_interval_fmt_format_with_date_interval(date_int_fmt,
                                                           date_int,
                                                           NULL,
                                                           field_pos);
    i18n_date_interval_destroy(date_int);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_format_with_date_interval_n4
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_format_with_date_interval passing invalid field_position
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_format_with_date_interval_n4(void)
{
    char *append_to = malloc(sizeof(char) * BUFSIZE);
    snprintf(append_to, BUFSIZE, "Date: ");
    i18n_date_interval_h date_int = NULL;
    i18n_udate from = 1000000.0;
    i18n_udate to = 1500000.0;

    ret = i18n_date_interval_create(from, to, &date_int);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_int, NULL);

    ret = i18n_date_interval_fmt_format_with_date_interval(date_int_fmt,
                                                           date_int,
                                                           &append_to,
                                                           NULL);
    i18n_date_interval_destroy(date_int);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_format_with_calendar_p
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_format_with_calendar and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_format_with_calendar_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(date_int_fmt, NULL);

    i18n_ucalendar_h from = NULL;
    i18n_ucalendar_h to = NULL;
    char *append_to = malloc(sizeof(char) * BUFSIZE);
    snprintf(append_to, BUFSIZE, "Date: ");
    const char *result = "Date: February 1, 2000 \u2013 February 1, 2015";

    ret = i18n_ucalendar_create(NULL, -1, locale, I18N_UCALENDAR_DEFAULT, &from);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(from, NULL);

    i18n_ucalendar_set_date_time(from, 2000, 1, 1, 1, 1, 1);

    ret = i18n_ucalendar_create(NULL, -1, locale, I18N_UCALENDAR_DEFAULT, &to);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(to, NULL);

    i18n_ucalendar_set_date_time(to, 2015, 1, 1, 1, 1, 1);

    ret = i18n_field_position_create(&field_pos);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(field_pos, NULL);

    ret = i18n_date_interval_fmt_format_with_calendar(date_int_fmt,
                                                      from, to,
                                                      &append_to,
                                                      field_pos);

    i18n_ucalendar_destroy(from);
    i18n_ucalendar_destroy(to);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(append_to, result), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_format_with_calendar_n
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_format_with_calendar passing invalid date_interval_format
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_format_with_calendar_n(void)
{
    i18n_ucalendar_h from = NULL;
    i18n_ucalendar_h to = NULL;
    char *append_to = malloc(sizeof(char) * BUFSIZE);
    snprintf(append_to, BUFSIZE, "Date: ");

    ret = i18n_ucalendar_create(NULL, -1, locale, I18N_UCALENDAR_DEFAULT, &from);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(from, NULL);

    i18n_ucalendar_set_date_time(from, 2000, 1, 1, 1, 1, 1);

    ret = i18n_ucalendar_create(NULL, -1, locale, I18N_UCALENDAR_DEFAULT, &to);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(to, NULL);

    i18n_ucalendar_set_date_time(to, 2015, 1, 1, 1, 1, 1);

    ret = i18n_field_position_create(&field_pos);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(field_pos, NULL);

    ret = i18n_date_interval_fmt_format_with_calendar(NULL,
                                                      from, to,
                                                      &append_to,
                                                      field_pos);
    i18n_ucalendar_destroy(from);
    i18n_ucalendar_destroy(to);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_format_with_calendar_n2
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_format_with_calendar passing invalid from_cal
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_format_with_calendar_n2(void)
{
    i18n_ucalendar_h to = NULL;
    char *append_to = malloc(sizeof(char) * BUFSIZE);
    snprintf(append_to, BUFSIZE, "Date: ");

    ret = i18n_ucalendar_create(NULL, -1, locale, I18N_UCALENDAR_DEFAULT, &to);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(to, NULL);

    i18n_ucalendar_set_date_time(to, 2015, 1, 1, 1, 1, 1);

    ret = i18n_field_position_create(&field_pos);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(field_pos, NULL);

    ret = i18n_date_interval_fmt_format_with_calendar(date_int_fmt,
                                                      NULL, to,
                                                      &append_to,
                                                      field_pos);

    i18n_ucalendar_destroy(to);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_format_with_calendar_n3
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_format_with_calendar passing invalid to_cal
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_format_with_calendar_n3(void)
{
    i18n_ucalendar_h from = NULL;
    char *append_to = malloc(sizeof(char) * BUFSIZE);
    snprintf(append_to, BUFSIZE, "Date: ");

    ret = i18n_ucalendar_create(NULL, -1, locale, I18N_UCALENDAR_DEFAULT, &from);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(from, NULL);

    i18n_ucalendar_set_date_time(from, 2000, 1, 1, 1, 1, 1);

    ret = i18n_field_position_create(&field_pos);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(field_pos, NULL);

    ret = i18n_date_interval_fmt_format_with_calendar(date_int_fmt,
                                                      from, NULL,
                                                      &append_to,
                                                      field_pos);

    i18n_ucalendar_destroy(from);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_format_with_calendar_n4
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_format_with_calendar passing invalid append_to
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_format_with_calendar_n4(void)
{
    i18n_ucalendar_h from = NULL;
    i18n_ucalendar_h to = NULL;

    ret = i18n_ucalendar_create(NULL, -1, locale, I18N_UCALENDAR_DEFAULT, &from);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(from, NULL);

    i18n_ucalendar_set_date_time(from, 2000, 1, 1, 1, 1, 1);

    ret = i18n_ucalendar_create(NULL, -1, locale, I18N_UCALENDAR_DEFAULT, &to);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(to, NULL);

    i18n_ucalendar_set_date_time(to, 2015, 1, 1, 1, 1, 1);

    ret = i18n_field_position_create(&field_pos);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(field_pos, NULL);

    ret = i18n_date_interval_fmt_format_with_calendar(date_int_fmt,
                                                      from, to,
                                                      NULL,
                                                      field_pos);

    i18n_ucalendar_destroy(from);
    i18n_ucalendar_destroy(to);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_fmt_format_with_calendar_n5
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_fmt_format_with_calendar passing invalid field_pos
 *               and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_fmt_format_with_calendar_n5(void)
{
    i18n_ucalendar_h from = NULL;
    i18n_ucalendar_h to = NULL;
    char *append_to = malloc(sizeof(char) * BUFSIZE);
    snprintf(append_to, BUFSIZE, "Date: ");

    ret = i18n_ucalendar_create(NULL, -1, locale, I18N_UCALENDAR_DEFAULT, &from);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(from, NULL);

    i18n_ucalendar_set_date_time(from, 2000, 1, 1, 1, 1, 1);

    ret = i18n_ucalendar_create(NULL, -1, locale, I18N_UCALENDAR_DEFAULT, &to);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(to, NULL);

    i18n_ucalendar_set_date_time(to, 2015, 1, 1, 1, 1, 1);

    ret = i18n_date_interval_fmt_format_with_calendar(date_int_fmt,
                                                      from, to,
                                                      &append_to,
                                                      NULL);

    i18n_ucalendar_destroy(from);
    i18n_ucalendar_destroy(to);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
