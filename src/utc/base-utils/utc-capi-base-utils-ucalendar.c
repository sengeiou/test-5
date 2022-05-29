#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

#define I18N_RESULT_LEN 100

static i18n_ucalendar_h g_cal = NULL;
static int ret = I18N_ERROR_NONE;

/**
 * @function        utc_capi_base_utils_ucalendar_startup
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_ucalendar_startup(void)
{
    ret = i18n_ucalendar_create(NULL, -1, I18N_ULOCALE_US, I18N_UCALENDAR_DEFAULT, &g_cal);
    i18n_ucalendar_set_date_time(g_cal, 2000, 1, 1, 1, 1, 1);
}

/**
 * @function        utc_capi_base_utils_ucalendar_cleanup
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_ucalendar_cleanup(void)
{
    if(NULL != g_cal) {
        i18n_ucalendar_destroy(g_cal);
    }
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_set_default_timezone_p
 * @since_tizen     2.3
 * @description     Sets the default time zone,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_set_default_timezone_p(void)
{
    const char *tzid = "Etc/GMT";
    i18n_uchar *_tzid = NULL;
    _tzid = (i18n_uchar*)calloc(strlen(tzid) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_tzid, tzid);

    ret = i18n_ucalendar_set_default_timezone(_tzid);
    free(_tzid);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_set_default_timezone_n
 * @since_tizen     2.3
 * @description     Sets the default time zone to invalid one,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_set_default_timezone_n(void)
{
    ret = i18n_ucalendar_set_default_timezone(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_now_p
 * @since_tizen     2.3
 * @description     Gets the current date and time,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_now_p(void)
{
    i18n_udate date;

    ret = i18n_ucalendar_get_now(&date);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_now_n
 * @since_tizen     2.3
 * @description     Gets the current date and time to invalid handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_get_now_n(void)
{
    ret = i18n_ucalendar_get_now(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_create_p
 * @since_tizen     2.3
 * @description     Creates a calendar handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_create_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_create_n
 * @since_tizen     2.3
 * @description     Creates a calendar with invalid handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_create_n(void)
{
    ret = i18n_ucalendar_create(NULL, -1, I18N_ULOCALE_US, I18N_UCALENDAR_DEFAULT, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_destroy_p
 * @since_tizen     2.3
 * @description     Destroys a calendar handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_destroy_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    ret = i18n_ucalendar_destroy(g_cal);
    g_cal = NULL;
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_destroy_n
 * @since_tizen     2.3
 * @description     Destroys an empty calendar handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_destroy_n(void)
{
    ret = i18n_ucalendar_destroy(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_clone_p
 * @since_tizen     2.3
 * @description     Creates a copy of a calendar handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_clone_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    i18n_ucalendar_h identical_to_cal = NULL;

    ret = i18n_ucalendar_clone(g_cal, &identical_to_cal);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ucalendar_destroy(identical_to_cal);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_clone_n
 * @since_tizen     2.3
 * @description     Creates a copy of a invalid calendar handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_clone_n(void)
{
    i18n_ucalendar_h identical_to_cal = NULL;

    ret = i18n_ucalendar_clone(NULL, &identical_to_cal);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_timezone_displayname_p
 * @since_tizen     2.3
 * @description     Gets the display name for a calendar's TimeZone,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_timezone_displayname_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    i18n_ucalendar_displayname_type_e type = I18N_UCALENDAR_STANDARD;
    i18n_uchar result[I18N_RESULT_LEN];
    int buf_size_needed = 0;

    for(; type <= I18N_UCALENDAR_SHORT_DST; type++) {
        ret = i18n_ucalendar_get_timezone_displayname(g_cal, type, I18N_ULOCALE_US, result, I18N_RESULT_LEN, &buf_size_needed);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_timezone_displayname_n
 * @since_tizen     2.3
 * @description     Gets the display name for a invalid calendar's timezone,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_get_timezone_displayname_n(void)
{
    int buf_size_needed = 0;

    ret = i18n_ucalendar_get_timezone_displayname(NULL, -1, NULL, NULL, -1, &buf_size_needed);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_is_in_daylight_time_p
 * @since_tizen     2.3
 * @description     Determines if an calendar handle is currently in daylight savings time,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_is_in_daylight_time_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    i18n_ubool is_in = false;

    ret = i18n_ucalendar_is_in_daylight_time(g_cal, &is_in);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_is_in_daylight_time_n
 * @since_tizen     2.3
 * @description     Determines if an invalid calendar handle is currently in daylight savings time,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_is_in_daylight_time_n(void)
{
    ret = i18n_ucalendar_is_in_daylight_time(NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_set_p
 * @since_tizen     2.3
 * @description     Sets the value of a field in a calendar handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_set_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    ret = i18n_ucalendar_set(g_cal, I18N_UCALENDAR_YEAR, 2014);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_set_n
 * @since_tizen     2.3
 * @description     Sets the value of a field in a invalid calendar handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_set_n(void)
{
    ret = i18n_ucalendar_set(NULL, I18N_UCALENDAR_YEAR, 2014);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_set_attribute_p
 * @since_tizen     2.3
 * @description     Sets a numeric attribute associated with an calendar handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_set_attribute_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    i18n_ucalendar_attribute_e attribute = I18N_UCALENDAR_LENIENT;

    for(; attribute <= I18N_UCALENDAR_MINIMAL_DAYS_IN_FIRST_WEEK; attribute++) {
        ret = i18n_ucalendar_set_attribute(g_cal, attribute, 1);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_set_attribute_n
 * @since_tizen     2.3
 * @description     Sets a numeric attribute associated with an invalid calendar handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_set_attribute_n(void)
{
    ret = i18n_ucalendar_set_attribute(NULL, -1, -1);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_attribute_p
 * @since_tizen     2.3
 * @description     Gets a numeric attribute associated with an calendar handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_attribute_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    i18n_ucalendar_attribute_e attribute = I18N_UCALENDAR_LENIENT;
    int val = 0;

    for(; attribute <= I18N_UCALENDAR_MINIMAL_DAYS_IN_FIRST_WEEK; attribute++) {
        ret = i18n_ucalendar_get_attribute(g_cal, attribute, &val);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_attribute_n
 * @since_tizen     2.3
 * @description     Gets a numeric attribute associated with an invalid calendar handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_get_attribute_n(void)
{
    int val = 0;

    ret = i18n_ucalendar_get_attribute(NULL, I18N_UCALENDAR_FIRST_DAY_OF_WEEK, &val);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_milliseconds_p
 * @since_tizen     2.3
 * @description     Gets a calendar's current time in milliseconds,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_milliseconds_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    i18n_udate date;

    ret = i18n_ucalendar_get_milliseconds(g_cal, &date);
    assert_eq(ret, I18N_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_milliseconds_n
 * @since_tizen     2.3
 * @description     Gets a calendar's current time in milliseconds,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_get_milliseconds_n(void)
{
    ret = i18n_ucalendar_get_milliseconds(NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_set_milliseconds_p
 * @since_tizen     2.3
 * @description     Sets a calendar's current time in milliseconds,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_set_milliseconds_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    ret = i18n_ucalendar_set_milliseconds(g_cal, 1000000000.0);
    assert_eq(ret, I18N_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_set_milliseconds_n
 * @since_tizen     2.3
 * @description     Sets an invalid calendar's current time in milliseconds,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_set_milliseconds_n(void)
{
    ret = i18n_ucalendar_set_milliseconds(NULL, -99999999.0);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_set_date_time_p
 * @since_tizen     2.3
 * @description     Sets a calendar's current date,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_set_date_time_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    ret = i18n_ucalendar_set_date_time(g_cal, 1988, 1, 3, 11, 44, 21);
    assert_eq(ret, I18N_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_set_date_time_n
 * @since_tizen     2.3
 * @description     Sets a calendar's current date using invalid handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_set_date_time_n(void)
{
    ret = i18n_ucalendar_set_date_time(NULL, -1, -1, -1, -1, -1, -1);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_is_equivalent_to_p
 * @since_tizen     2.3
 * @description     Checks equivalency of two calendars,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_is_equivalent_to_p(void)
{
    i18n_ucalendar_h cal1 = NULL, cal2 = NULL;
    i18n_ubool equiv = false;

    ret = i18n_ucalendar_create(NULL, -1, I18N_ULOCALE_US, I18N_UCALENDAR_DEFAULT, &cal1);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ucalendar_create(NULL, -1, I18N_ULOCALE_US, I18N_UCALENDAR_DEFAULT, &cal2);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ucalendar_set_date_time(cal1, 2000, 1, 2, 3, 4, 5);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ucalendar_set_date_time(cal2, 2000, 1, 2, 3, 4, 5);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ucalendar_is_equivalent_to(cal1, cal2, &equiv);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(equiv, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_is_equivalent_to_p2
 * @since_tizen     2.3
 * @description     Checks equivalency of two calendars,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_is_equivalent_to_p2(void)
{
    i18n_ucalendar_h cal1 = NULL, cal2 = NULL;
    i18n_ubool equiv = false;

    ret = i18n_ucalendar_create(NULL, -1, I18N_ULOCALE_US, I18N_UCALENDAR_DEFAULT, &cal1);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ucalendar_create(NULL, -1, I18N_ULOCALE_US, I18N_UCALENDAR_DEFAULT, &cal2);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ucalendar_set_date_time(cal1, 2000, 1, 2, 3, 4, 5);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ucalendar_set_date_time(cal2, 2015, 1, 2, 3, 4, 5);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ucalendar_is_equivalent_to(cal1, cal2, &equiv);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(equiv, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_is_equivalent_to_p3
 * @since_tizen     2.3
 * @description     Checks equivalency of two calendars,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_is_equivalent_to_p3(void)
{
    i18n_ucalendar_h cal1 = NULL, cal2 = NULL;
    i18n_ubool equiv = false;

    ret = i18n_ucalendar_create(NULL, -1, I18N_ULOCALE_US, I18N_UCALENDAR_DEFAULT, &cal1);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ucalendar_create(NULL, -1, I18N_ULOCALE_FRANCE, I18N_UCALENDAR_DEFAULT, &cal2);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ucalendar_set_date_time(cal1, 2000, 1, 2, 3, 4, 5);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ucalendar_set_date_time(cal2, 2015, 1, 2, 3, 4, 5);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ucalendar_is_equivalent_to(cal1, cal2, &equiv);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(equiv, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_is_equivalent_to_n
 * @since_tizen     2.3
 * @description     Checks equivalency of two invalid calendars,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_is_equivalent_to_n(void)
{
    ret = i18n_ucalendar_is_equivalent_to(NULL, NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_add_p
 * @since_tizen     2.3
 * @description     Adds a specified signed amount to a particular field in a calendar handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_add_p(void)
{
    i18n_ucalendar_date_fields_e field = I18N_UCALENDAR_ERA;

    for(; field <= I18N_UCALENDAR_MILLISECOND; field++) {
        ret = i18n_ucalendar_add(g_cal, field, 1);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_add_n
 * @since_tizen     2.3
 * @description     Adds a specified signed amount to a particular field in an invalid calendar handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_add_n(void)
{
    i18n_ucalendar_date_fields_e field = I18N_UCALENDAR_ERA;

    ret = i18n_ucalendar_add(NULL, field, 1);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_p
 * @since_tizen     2.3
 * @description     Gets the current value of a field from an calendar handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    int val = -1;

    ret = i18n_ucalendar_get(g_cal, I18N_UCALENDAR_YEAR, &val);
    assert_eq(ret, I18N_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_n
 * @since_tizen     2.3
 * @description     Gets the current value of a field from an invalid calendar handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_get_n(void)
{
    ret = i18n_ucalendar_get(NULL, -1, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_field_difference_p
 * @since_tizen     2.3
 * @description     Gets the difference between the target time and the time this calendar object is currently set to,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_field_difference_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    i18n_udate target = 1000000000000.0;
    i18n_ucalendar_date_fields_e field = I18N_UCALENDAR_YEAR;
    i18n_error_code_e status = I18N_ERROR_NONE;

    for(; field < I18N_UCALENDAR_MILLISECOND; field++) {
        i18n_ucalendar_get_field_difference(g_cal, target, field, &status);
        assert_eq(status, I18N_ERROR_NONE);

        status = i18n_ucalendar_set_date_time(g_cal, 2000, 1, 1, 1, 1, 1);
        assert_eq(status, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_field_difference_p2
 * @since_tizen     2.3
 * @description     Gets the difference between the target time and the time this calendar object is currently set to,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_field_difference_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    i18n_udate date;
    ret = i18n_ucalendar_get_milliseconds(g_cal, &date);
    assert_eq(ret, I18N_ERROR_NONE);

    const int MAX_INT32_T = 2147483647;
    i18n_udate target = date + MAX_INT32_T;
    i18n_error_code_e status = I18N_ERROR_NONE;

    i18n_ucalendar_get_field_difference(g_cal, target, I18N_UCALENDAR_MILLISECOND, &status);
    assert_eq(status, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_field_difference_n
 * @since_tizen     2.3
 * @description     Gets the difference between the target time and a invalid time,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_get_field_difference_n(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    i18n_udate target = 0;

    i18n_error_code_e status = I18N_ERROR_NONE;
    i18n_ucalendar_get_field_difference(NULL, target, I18N_UCALENDAR_DATE, &status);
    assert_eq(status, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_timezone_id_enumeration_create_p
 * @since_tizen     2.3
 * @description     Creates an enumeration over system time zone IDs with the given filter conditions,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_timezone_id_enumeration_create_p(void)
{
    i18n_uenumeration_h enumeration = NULL;

    ret = i18n_ucalendar_timezone_id_enumeration_create(I18N_UCALENDAR_ZONE_TYPE_ANY, "US", NULL, &enumeration);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_timezone_id_enumeration_create_n
 * @since_tizen     2.3
 * @description     Creates an enumeration over system time zone IDs with the given filter conditions
 *                  with invalid region, so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_timezone_id_enumeration_create_n(void)
{
    ret = i18n_ucalendar_timezone_id_enumeration_create(I18N_UCALENDAR_ZONE_TYPE_ANY, "WRONGCOUNTRYCODE", NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_timezones_create_p
 * @since_tizen     2.3
 * @description     Creates an enumeration over all time zones,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_timezones_create_p(void)
{
    i18n_uenumeration_h enumeration = NULL;
    ret = i18n_ucalendar_timezones_create(&enumeration);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_timezones_create_n
 * @since_tizen     2.3
 * @description     Creates an enumeration over all time zones using
 *                  invalid enumeration output, so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_timezones_create_n(void)
{
    ret = i18n_ucalendar_timezones_create(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_country_timezones_create_p
 * @since_tizen     2.3
 * @description     Creates an enumeration over all time zones associated with the given country,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_country_timezones_create_p(void)
{
    i18n_uenumeration_h enumeration;
    ret = i18n_ucalendar_country_timezones_create("US", &enumeration);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_country_timezones_create_n
 * @since_tizen     2.3
 * @description     Creates an enumeration over all time zones associated with the given country
 *                  using invalid enumeration output, so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_country_timezones_create_n(void)
{
    ret = i18n_ucalendar_country_timezones_create("US", NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_default_timezone_p
 * @since_tizen     2.3
 * @description     Gets the default time zone,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_default_timezone_p(void)
{
    i18n_uchar result[64] = { 0, };
    int result_capacity = 64;

    i18n_ucalendar_get_default_timezone(result, result_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_default_timezone_n
 * @since_tizen     2.3
 * @description     Gets the default time zone with negative capacity
 *                  parameter, so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_get_default_timezone_n(void)
{
    i18n_uchar result[64] = { 0, };
    int result_capacity = -1;

    i18n_ucalendar_get_default_timezone(result, result_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_set_timezone_p
 * @since_tizen     2.3
 * @description     Sets the TimeZone used by a calendar handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_set_timezone_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    i18n_uchar result[64] = { 0, };
    int result_capacity = 64;

    int length = i18n_ucalendar_get_timezone_id(g_cal, result, result_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ucalendar_set_timezone(g_cal, 0, length);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_set_timezone_n
 * @since_tizen     2.3
 * @description     Sets the TimeZone used by a calendar handle with invalid
 *                  output, so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_set_timezone_n(void)
{
    ret = i18n_ucalendar_set_timezone(NULL, 0, -1);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_timezone_id_p
 * @since_tizen     2.3
 * @description     Gets the ID of the calendar's time zone,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_timezone_id_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    i18n_uchar result[64] = { 0, };
    int result_capacity = 64;

    i18n_ucalendar_get_timezone_id(g_cal, result, result_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_timezone_id_n
 * @since_tizen     2.3
 * @description     Gets the ID of the calendar's time zone to invalid handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_get_timezone_id_n(void)
{
    i18n_uchar result[64] = { 0, };
    int result_capacity = -1;

    i18n_ucalendar_get_timezone_id(NULL, result, result_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_set_gregorian_change_p
 * @since_tizen     2.3
 * @description     Sets the Gregorian Calendar change date,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_set_gregorian_change_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    ret = i18n_ucalendar_set_gregorian_change(g_cal, 1000);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_set_gregorian_change_n
 * @since_tizen     2.3
 * @description     Sets the Gregorian Calendar change date to invalid one,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_set_gregorian_change_n(void)
{
    ret = i18n_ucalendar_set_gregorian_change(NULL, 1000);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_gregorian_change_p
 * @since_tizen     2.3
 * @description     Gets the Gregorian Calendar change date,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_gregorian_change_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);
    i18n_udate date;
    ret = i18n_ucalendar_get_gregorian_change(g_cal, &date);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_gregorian_change_n
 * @since_tizen     2.3
 * @description     Gets the Gregorian Calendar change date to invalid
 *                  output parameter, so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_get_gregorian_change_n(void)
{
    ret = i18n_ucalendar_get_gregorian_change(NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_available_p
 * @since_tizen     2.3
 * @description     Gets a locale for which calendars are available,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_available_p(void)
{
    i18n_ucalendar_get_available(0);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_available_n
 * @since_tizen     2.3
 * @description     Gets a locale with invalid index,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_get_available_n(void)
{
    i18n_ucalendar_get_available(-1);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_count_available_p
 * @since_tizen     2.3
 * @description     Determines how many locales have calendars available,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_count_available_p(void)
{
    int available_no;
    available_no = i18n_ucalendar_count_available();
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_geq(available_no, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_set_date_p
 * @since_tizen     2.3
 * @description     Sets a calendar's current date,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_set_date_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    ret = i18n_ucalendar_set_date(g_cal, 2014, 11, 11);
    assert_eq(ret, I18N_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_set_date_n
 * @since_tizen     2.3
 * @description     Sets an invalid calendar's current date,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_set_date_n(void)
{
    ret = i18n_ucalendar_set_date(NULL, 2014, 11, 11);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_roll_p
 * @since_tizen     2.3
 * @description     Adds a specified signed amount to a particular field in a calendar handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_roll_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    i18n_ucalendar_date_fields_e field = I18N_UCALENDAR_ERA;

    for(; field < I18N_UCALENDAR_MILLISECOND; field++) {
        ret = i18n_ucalendar_roll(g_cal, field, 2);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_roll_n
 * @since_tizen     2.3
 * @description     Adds a specified signed amount to a particular field in an invalid calendar handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_roll_n(void)
{
    ret = i18n_ucalendar_roll(NULL, I18N_UCALENDAR_DATE, 2);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_is_set_p
 * @since_tizen     2.3
 * @description     Determines if a field in a calendar handle is set,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_is_set_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    i18n_ucalendar_date_fields_e field = I18N_UCALENDAR_ERA;

    for(; field < I18N_UCALENDAR_FIELD_COUNT; field++) {
        i18n_ucalendar_is_set(g_cal, field);
        ret = get_last_result();
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_is_set_n
 * @since_tizen     2.3
 * @description     Determines if a field in an invalid calendar handle is set,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_is_set_n(void)
{
    i18n_ucalendar_is_set(NULL, I18N_UCALENDAR_HOUR);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_clear_field_p
 * @since_tizen     2.3
 * @description     Clears a field in a calendar handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_clear_field_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    i18n_ucalendar_date_fields_e field = I18N_UCALENDAR_ERA;

    for(; field < I18N_UCALENDAR_FIELD_COUNT; field++) {
        ret = i18n_ucalendar_clear_field(g_cal, field);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_clear_field_n
 * @since_tizen     2.3
 * @description     Clears a field in an invalid calendar handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_clear_field_n(void)
{
    ret = i18n_ucalendar_clear_field(NULL, I18N_UCALENDAR_HOUR);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_clear_p
 * @since_tizen     2.3
 * @description     Clears all fields in a calendar handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_clear_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    ret = i18n_ucalendar_clear(g_cal);
    assert_eq(ret, I18N_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_clear_n
 * @since_tizen     2.3
 * @description     Clears all fields in an invalid calendar handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_clear_n(void)
{
    ret = i18n_ucalendar_clear(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_limit_p
 * @since_tizen     2.3
 * @description     Determines a limit for a field using an calendar handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_limit_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    i18n_ucalendar_date_fields_e field = I18N_UCALENDAR_ERA;

    for(; field < I18N_UCALENDAR_FIELD_COUNT; field++) {
        i18n_ucalendar_limit_type_e limit = I18N_UCALENDAR_MINIMUM;

        for(; limit <= I18N_UCALENDAR_ACTUAL_MAXIMUM; limit++) {
            i18n_ucalendar_get_limit(g_cal, field, limit);
            ret = get_last_result();
            assert_eq(ret, I18N_ERROR_NONE);
        }
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_limit_n
 * @since_tizen     2.3
 * @description     Determines a limit for a field using invalid calendar handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_get_limit_n(void)
{
    i18n_ucalendar_get_limit(NULL, I18N_UCALENDAR_DATE, I18N_UCALENDAR_MINIMUM);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_locale_by_type_p
 * @since_tizen     2.3
 * @description     Gets the locale for calendar object,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_locale_by_type_p(void)
{
    i18n_ucalendar_get_locale_by_type(g_cal, I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_locale_by_type_p2
 * @since_tizen     2.3
 * @description     Gets the locale for calendar object,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_locale_by_type_p2(void)
{
    i18n_ucalendar_get_locale_by_type(g_cal, I18N_ULOCALE_DATA_LOCALE_TYPE_VALID_LOCALE);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_locale_by_type_n
 * @since_tizen     2.3
 * @description     Gets the locale for calendar object using invalid handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_get_locale_by_type_n(void)
{
    i18n_ucalendar_get_locale_by_type(NULL, I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_tz_data_version_p
 * @since_tizen     2.3
 * @description     Gets the timezone data version currently used by ICU,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_tz_data_version_p(void)
{
    const char *version;
    version = i18n_ucalendar_get_tz_data_version();
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(version, NULL);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_canonical_timezone_id_p
 * @since_tizen     2.3
 *                  custom time zone ID for the given time zone ID.
 * @description     Gets the canonical system timezone ID or the normalized
 *                  custom time zone ID for the given time zone ID,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_canonical_timezone_id_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    i18n_uchar timezone[64] = { 0, };
    int timezone_capacity = 64;
    i18n_uchar result[64] = { 0, };
    int result_capacity = 64;
    i18n_ubool is_system_id;

    int timezone_id_length = i18n_ucalendar_get_timezone_id(g_cal, timezone, timezone_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ucalendar_get_canonical_timezone_id(timezone, timezone_id_length, result, result_capacity, &is_system_id);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_canonical_timezone_id_n
 * @since_tizen     2.3
 *                  custom time zone ID for the given time zone ID with invalid handle.
 * @description     Gets the canonical system timezone ID or the normalized
 *                  custom time zone ID for the given time zone ID using
 *                  invalid timezone handle, so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_get_canonical_timezone_id_n(void)
{
    i18n_uchar result[64] = { 0, };
    int result_capacity = 64;
    i18n_ubool is_system_id;

    i18n_ucalendar_get_canonical_timezone_id(NULL, -2, result, result_capacity, &is_system_id);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_type_p
 * @since_tizen     2.3
 * @description     Gets the resource keyword value string designating the calendar type for the calendar handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_type_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    i18n_ucalendar_get_type(g_cal);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_type_n
 * @since_tizen     2.3
 *                  so the error is expected.
 * @description     Gets the resource keyword value string designating the calendar type for the calendar handle.
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_get_type_n(void)
{
    i18n_ucalendar_get_type(NULL);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_keyword_values_for_locale_p
 * @since_tizen     2.3
 * @description     Given a key and a locale, returns an array of string values in a preferred order that would make a difference,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_keyword_values_for_locale_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    const char *key = i18n_ucalendar_get_type(g_cal);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    const char *locale = i18n_ucalendar_get_available(1);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uenumeration_h enumeration;

    ret = i18n_ucalendar_get_keyword_values_for_locale(key, locale, 0, &enumeration);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_keyword_values_for_locale_n
 * @since_tizen     2.3
 * @description     Given a key and a locale, returns an array of string values in a preferred order that would make a difference,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_get_keyword_values_for_locale_n(void)
{
    ret = i18n_ucalendar_get_keyword_values_for_locale(NULL, NULL, 0, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_day_of_week_type_p
 * @since_tizen     2.3
 * @description     Gets whether the given day of the week is a weekday, a weekend day,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_day_of_week_type_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);
    i18n_ucalendar_weekday_type_e weekday_type;
    ret = i18n_ucalendar_get_day_of_week_type(g_cal, I18N_UCALENDAR_MONDAY, &weekday_type);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_day_of_week_type_n
 * @since_tizen     2.3
 * @description     Gets whether the given day of the week is a weekday, a weekend day,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_get_day_of_week_type_n(void)
{
    ret = i18n_ucalendar_get_day_of_week_type(NULL, I18N_UCALENDAR_MONDAY, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_weekend_transition_p
 * @since_tizen     2.3
 * @description     Gets the time during the day at which the weekend begins or ends in this calendar system,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_weekend_transition_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    i18n_ucalendar_get_weekend_transition(g_cal, I18N_UCALENDAR_SATURDAY);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_weekend_transition_n
 * @since_tizen     2.3
 * @description     Gets the time during the day at which the weekend begins or ends in this calendar system,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_get_weekend_transition_n(void)
{
    i18n_ucalendar_get_weekend_transition(NULL, I18N_UCALENDAR_MONDAY);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_is_weekend_p
 * @since_tizen     2.3
 * @description     Gets if the given date is in the weekend in this calendar system,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_is_weekend_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    ret = i18n_ucalendar_clear(g_cal);
    assert_eq(ret, I18N_ERROR_NONE);

    // Set date to the non-weekend date e.g. Fri 16:34 12 June 2015
    i18n_ucalendar_set_date_time(g_cal, 2015, I18N_UCALENDAR_JUNE, 12, 16, 34, 0);

    i18n_udate date;
    ret = i18n_ucalendar_get_milliseconds(g_cal, &date);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubool is_weekend = i18n_ucalendar_is_weekend(g_cal, date);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_weekend, false);

    ret = i18n_ucalendar_clear(g_cal);
    assert_eq(ret, I18N_ERROR_NONE);

    // Set date to the weekend date e.g. Sat 16:34 13 June 2015
    i18n_ucalendar_set_date_time(g_cal, 2015, I18N_UCALENDAR_JUNE, 13, 16, 34, 0);

    ret = i18n_ucalendar_get_milliseconds(g_cal, &date);
    assert_eq(ret, I18N_ERROR_NONE);

    is_weekend = i18n_ucalendar_is_weekend(g_cal, date);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_weekend, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_is_weekend_n
 * @since_tizen     2.3
 * @description     Gets if the given date is in the weekend in this calendar system,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_is_weekend_n(void)
{
    i18n_udate date = 0.0;

    i18n_ucalendar_is_weekend(NULL, date);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_timezone_transition_date_p
 * @since_tizen     2.3
 * @description     Get the date for the next/previous time zone transition relative,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ucalendar_get_timezone_transition_date_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_cal, NULL);

    i18n_utimezone_transition_type_e type = I18N_UCALENDAR_TZ_TRANSITION_NEXT;
    i18n_udate transition;

    for(; type <= I18N_UCALENDAR_TZ_TRANSITION_PREVIOUS_INCLUSIVE; type++) {
        i18n_ucalendar_get_timezone_transition_date(g_cal, type, &transition);
        ret = get_last_result();
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucalendar_get_timezone_transition_date_n
 * @since_tizen     2.3
 * @description     Get the date for the next/previous time zone transition relative
 *                  with invalid calendar handle, so the error is expected.
 */
int utc_capi_base_utils_i18n_ucalendar_get_timezone_transition_date_n(void)
{
    i18n_udate transition;

    i18n_ucalendar_get_timezone_transition_date(NULL, 5, &transition);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
