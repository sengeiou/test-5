#include "assert.h"
#include <string.h>
#include <utils_i18n.h>

//& set: capi-base-utils-udate

static i18n_udate_format_h format = NULL;
static int ret = I18N_ERROR_NONE;

/**
 * @function        utc_capi_base_utils_udate_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_udate_startup(void)
{
    i18n_udate_format_style_e time_style = I18N_UDATE_DEFAULT, date_style = I18N_UDATE_DEFAULT;
    const char *locale = I18N_ULOCALE_US;
    const i18n_uchar *tz_id = 0; // use the default timezone
    int32_t tz_id_length = -1;
    const i18n_uchar *pattern = NULL;
    int32_t pattern_length = 0;

    ret = i18n_udate_create(time_style, date_style, locale, tz_id, tz_id_length, pattern, pattern_length, &format);
    if(I18N_ERROR_NONE != ret)
    {
        fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
        fprintf(stderr, "i18n_uenumeration_open_uchar_strings_enumeration ( code : %d )\n", ret);
    }
}

/**
 * @function        utc_capi_base_utils_udate_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_udate_cleanup(void)
{
    if(NULL != format)
    {
        i18n_udate_destroy(format);
        format = NULL;
    }
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_create_p
 * @since_tizen     2.3
 * @description     Creates a new i18n_udate_format_h for formatting and parsing
 *                  dates and times using different data style and time style values.
 */
int utc_capi_base_utils_i18n_udate_create_p(void)
{
    i18n_udate_format_style_e time_style, date_style;
    const char *locale = I18N_ULOCALE_US;
    const i18n_uchar *tz_id = 0; // use the default timezone
    int32_t tz_id_length = -1;
    i18n_uchar pattern[128];
    i18n_ustring_copy_ua(pattern, "EEE MMM dd HH:mm:ss.SSS zzz yyyy G");
    int32_t pattern_length = -1;

    for(time_style = I18N_UDATE_NONE; time_style<=I18N_UDATE_SHORT; time_style++)
    {
        for(date_style = I18N_UDATE_NONE; date_style<=I18N_UDATE_SHORT; date_style++)
        {
            ret = i18n_udate_create(time_style, date_style, locale, tz_id, tz_id_length, pattern, pattern_length, &format);
            assert_eq(ret, I18N_ERROR_NONE);
        }

        for(date_style = I18N_UDATE_RELATIVE; date_style<=I18N_UDATE_SHORT_RELATIVE; date_style++)
        {
            ret = i18n_udate_create(time_style, date_style, locale, tz_id, tz_id_length, pattern, pattern_length, &format);
            assert_eq(ret, I18N_ERROR_NONE);
        }
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_create_n
 * @since_tizen     2.3
 * @description     Creates a new i18n_udate_format_h for formatting and parsing
 *                  dates and times passing NULL to format parameter.
 */
int utc_capi_base_utils_i18n_udate_create_n(void)
{
    i18n_udate_format_style_e time_style = I18N_UDATE_DEFAULT, date_style = I18N_UDATE_DEFAULT;
    const char *locale = "en_US";
    const i18n_uchar *tz_id = 0; // use the default timezone
    int32_t tz_id_length = 0;
    const i18n_uchar *pattern = NULL;
    int32_t pattern_length = 0;

    ret = i18n_udate_create(time_style, date_style, locale, tz_id, tz_id_length, pattern, pattern_length, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_destroy_p
 * @since_tizen     2.3
 * @description     Creates a new i18n_udate_format_h for formatting and
 *                  parsing dates and times and destroys it.
 */
int utc_capi_base_utils_i18n_udate_destroy_p(void)
{
    i18n_udate_format_h dfmt = NULL;

    ret = i18n_udate_create(I18N_UDATE_DEFAULT, I18N_UDATE_DEFAULT, NULL, NULL, -1, NULL, -1, &dfmt);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_udate_destroy(dfmt);
    assert_eq(ret, I18N_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_destroy_n
 * @since_tizen     2.3
 * @description     Destroys an i18n_udate_format_h with NULL value.
 */
int utc_capi_base_utils_i18n_udate_destroy_n(void)
{
    ret = i18n_udate_destroy(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_format_date_p
 * @since_tizen     2.3
 * @description     Formats a date using an i18n_udate_format_h.
 */
int utc_capi_base_utils_i18n_udate_format_date_p(void)
{
    i18n_udate date = 1000000.0;
    i18n_uchar *str;
    int len = 0;
    int buf_size_needed = -1;

    ret = i18n_udate_format_date(format, date, NULL, len, NULL, &buf_size_needed);
    if(I18N_ERROR_BUFFER_OVERFLOW == ret)
    {
        len = buf_size_needed+1;
        str = (i18n_uchar*)malloc(sizeof(i18n_uchar)*len);
        ret = i18n_udate_format_date(format, date, str, len+1, NULL, &buf_size_needed);
        free(str);
    }
    assert_eq(ret, I18N_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_format_date_p2
 * @since_tizen     2.3
 * @description     Creates and formats a date with an i18n_udate_format_h
 *                  handle using different time style and date style values.
 */
int utc_capi_base_utils_i18n_udate_format_date_p2(void)
{
    i18n_udate_format_style_e time_style, date_style;
    i18n_udate date = 1000000.0;
    int len = 0;
    int buf_size_needed = -1;
    i18n_uchar *str;
    i18n_uchar pattern[128];
    i18n_ustring_copy_ua(pattern, "EEE MMM dd HH:mm:ss.SSS zzz yyyy G");
    int32_t pattern_length = -1;

    for(time_style = I18N_UDATE_NONE; time_style<=I18N_UDATE_SHORT; time_style++)
    {
        for(date_style = I18N_UDATE_NONE; date_style<=I18N_UDATE_SHORT; date_style++)
        {
            ret = i18n_udate_create(time_style, date_style, I18N_ULOCALE_US, 0, -1, pattern, pattern_length, &format);
            assert_eq(ret, I18N_ERROR_NONE);

            ret = i18n_udate_format_date(format, date, NULL, len, NULL, &buf_size_needed);
            if(I18N_ERROR_BUFFER_OVERFLOW == ret)
            {
                len = buf_size_needed+1;
                str = (i18n_uchar*)malloc(sizeof(i18n_uchar)*len);
                ret = i18n_udate_format_date(format, date, str, len+1, NULL, &buf_size_needed);
                len = 0;
                free(str);
            }
            i18n_udate_destroy(format);
            format = NULL;
            assert_eq(ret, I18N_ERROR_NONE);
        }

        for(date_style = I18N_UDATE_RELATIVE; date_style<=I18N_UDATE_SHORT_RELATIVE; date_style++)
        {
            ret = i18n_udate_create(time_style, date_style, I18N_ULOCALE_US, 0, -1, pattern, pattern_length, &format);
            assert_eq(ret, I18N_ERROR_NONE);

            ret = i18n_udate_format_date(format, date, NULL, len, NULL, &buf_size_needed);
            if(I18N_ERROR_BUFFER_OVERFLOW == ret)
            {
                len = buf_size_needed+1;
                str = (i18n_uchar*)malloc(sizeof(i18n_uchar)*len);
                ret = i18n_udate_format_date(format, date, str, len+1, NULL, &buf_size_needed);
                len = 0;
                free(str);
            }
            i18n_udate_destroy(format);
            format = NULL;
            assert_eq(ret, I18N_ERROR_NONE);
        }
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_format_date_p3
 * @since_tizen     2.3
 * @description     Formats a date using an i18n_udate_format_h.
 */
int utc_capi_base_utils_i18n_udate_format_date_p3(void)
{
    i18n_udate date = -10.0;
    int len = 100;
    i18n_uchar str[len];
    int buf_size_needed = -1;

    ret = i18n_udate_format_date(format, date, str, len, NULL, &buf_size_needed);
    assert_eq(ret, I18N_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_format_date_n
 * @since_tizen     2.3
 * @description     Formats a date using an i18n_udate_format_h with invalid
 *                  format parameter.
 */
int utc_capi_base_utils_i18n_udate_format_date_n(void)
{
    i18n_udate date = 1000000.0;
    int len = 100;
    i18n_uchar str[len];
    int buf_size_needed = -1;

    ret = i18n_udate_format_date(NULL, date, str, len, NULL, &buf_size_needed);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_format_date_n2
 * @since_tizen     2.3
 * @description     Formats a date using an i18n_udate_format_h with too small
 *                  result_len passed.
 */
int utc_capi_base_utils_i18n_udate_format_date_n2(void)
{
    i18n_udate date = 1000000.0;
    int len = 0;
    int buf_size_needed = -1;

    ret = i18n_udate_format_date(format, date, NULL, len, NULL, &buf_size_needed);
    assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_format_date_n3
 * @since_tizen     2.3
 * @description     Formats a date using an i18n_udate_format_h with invalid
 *                  result_len parameter.
 */
int utc_capi_base_utils_i18n_udate_format_date_n3(void)
{
    i18n_udate date = 1000000.0;
    int len = 100;
    i18n_uchar str[len];
    int buf_size_needed = -1;

    ret = i18n_udate_format_date(format, date, str, -2, NULL, &buf_size_needed);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_format_date_n4
 * @since_tizen     2.3
 * @description     Formats a date using an i18n_udate_format_h with invalid
 *                  buf_size_needed parameter.
 */
int utc_capi_base_utils_i18n_udate_format_date_n4(void)
{
    i18n_udate date = 1000000.0;
    int len = 100;
    i18n_uchar str[len];

    ret = i18n_udate_format_date(format, date, str, len, NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_to_calendar_date_field_p
 * @since_tizen     2.3.1
 * @description     Maps from an i18n_udate_format_h to the corresponding
 *                  i18n_ucalendar_date_fields_e.
 */
int utc_capi_base_utils_i18n_udate_to_calendar_date_field_p(void)
{
    i18n_udate_format_field_e field = I18N_UDATE_FORMAT_ERA_FIELD;
    i18n_ucalendar_date_fields_e calendar_field;

    ret = i18n_udate_to_calendar_date_field(field, &calendar_field);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(calendar_field, I18N_UCALENDAR_ERA);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_to_calendar_date_field_n
 * @since_tizen     2.3.1
 * @description     Maps from an i18n_udate_format_h to the corresponding
 *                  i18n_ucalendar_date_fields_e with invalid date_field_type
 *                  parameter and different field values.
 */
int utc_capi_base_utils_i18n_udate_to_calendar_date_field_n(void)
{
    i18n_udate_format_field_e field = I18N_UDATE_FORMAT_ERA_FIELD;

    for(; field<I18N_UDATE_FORMAT_TIMEZONE_LOCALIZED_GMT_OFFSET_FIELD; field++)
    {
        ret = i18n_udate_to_calendar_date_field(field, NULL);
        assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_to_calendar_date_field_n2
 * @since_tizen     2.3.1
 * @description     Maps from an i18n_udate_format_h to the corresponding
 *                  i18n_ucalendar_date_fields_e with unsupported field
 *                  parameter values.
 */
int utc_capi_base_utils_i18n_udate_to_calendar_date_field_n2(void)
{
    i18n_udate_format_field_e field = I18N_UDATE_FORMAT_TIMEZONE_LOCALIZED_GMT_OFFSET_FIELD;
    i18n_ucalendar_date_fields_e calendar_field;

    for(; field<=I18N_UDATE_FORMAT_TIMEZONE_ISO_LOCAL_FIELD; field++)
    {
        ret = i18n_udate_to_calendar_date_field(field, &calendar_field);
        assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    }

    ret = i18n_udate_to_calendar_date_field(I18N_UDATE_FORMAT_FIELD_COUNT, &calendar_field);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_clone_p
 * @since_tizen     2.3.1
 * @description     Creates a copy of an i18n_udate_format_h.
 */
int utc_capi_base_utils_i18n_udate_clone_p(void)
{
    i18n_udate_format_h clone = NULL;

    ret = i18n_udate_clone(format, &clone);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(clone, NULL);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_clone_n
 * @since_tizen     2.3.1
 * @description     Creates a copy of an i18n_udate_format_h with NULL format
 *                  clone parameter.
 */
int utc_capi_base_utils_i18n_udate_clone_n(void)
{
    ret = i18n_udate_clone(format, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_clone_n2
 * @since_tizen     2.3.1
 * @description     Creates a copy of an i18n_udate_format_h with NULL format
 *                  parameter.
 */
int utc_capi_base_utils_i18n_udate_clone_n2(void)
{
    i18n_udate_format_h clone = NULL;

    ret = i18n_udate_clone(NULL, &clone);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(clone, NULL);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_parse_p
 * @since_tizen     2.3.1
 * @description     Parses a string into an date/time using an
 *                  i18n_udate_format_h.
 */
int utc_capi_base_utils_i18n_udate_parse_p(void)
{
    i18n_uchar text[24] = {0,};
    int32_t text_length = -1;
    int32_t parse_pos = 0;
    i18n_udate parsed_date;

    ret = i18n_udate_parse(format, i18n_ustring_copy_ua(text, "Jan 1, 1970, 9:00:00 AM"), text_length, &parse_pos, &parsed_date);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_parse_n
 * @since_tizen     2.3.1
 * @description     Parses a string into an date/time using an i18n_udate_format_h with NULL format parameter.
 */
int utc_capi_base_utils_i18n_udate_parse_n(void)
{
    i18n_uchar text[24] = {0,};
    int32_t text_length = -1;
    int32_t parse_pos = 0;
    i18n_udate parsed_date;

    ret = i18n_udate_parse(NULL, i18n_ustring_copy_ua(text, "Jan 1, 1970, 9:00:00 AM"), text_length, &parse_pos, &parsed_date);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_parse_n2
 * @since_tizen     2.3.1
 * @description     Parses a string into an date/time using an
 *                  i18n_udate_format_h with NULL text parameter.
 */
int utc_capi_base_utils_i18n_udate_parse_n2(void)
{
    int32_t text_length = -1;
    int32_t parse_pos = 0;
    i18n_udate parsed_date;

    ret = i18n_udate_parse(format, NULL, text_length, &parse_pos, &parsed_date);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_parse_n3
 * @since_tizen     2.3.1
 * @description     Parses a string into an date/time using an
 *                  i18n_udate_format_h with invalid text_length parameter.
 */
int utc_capi_base_utils_i18n_udate_parse_n3(void)
{
    i18n_uchar text[24] = {0,};
    int32_t parse_pos = 0;
    i18n_udate parsed_date;

    ret = i18n_udate_parse(format, i18n_ustring_copy_ua(text, "Jan 1, 1970, 9:00:00 AM"), -2, &parse_pos, &parsed_date);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_parse_n4
 * @since_tizen     2.3.1
 * @description     Parses a string into an date/time using an
 *                  i18n_udate_format_h with NULL parsed_date parameter.
 */
int utc_capi_base_utils_i18n_udate_parse_n4(void)
{
    i18n_uchar text[24] = {0,};
    int32_t text_length = -1;
    int32_t parse_pos = 0;

    ret = i18n_udate_parse(format, i18n_ustring_copy_ua(text, "Jan 1, 1970, 9:00:00 AM"), text_length, &parse_pos, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_parse_calendar_p
 * @since_tizen     2.3
 * @description     Parses a ucalendar into an date/time using an
 *                  i18n_udate_format_h.
 */
int utc_capi_base_utils_i18n_udate_parse_calendar_p(void)
{
    i18n_ucalendar_h ucal = NULL;
    i18n_uchar timezone_id[24] = {0,};
    int32_t len = -1;
    const char *locale;
    ret = i18n_ulocale_get_default(&locale);
    assert_eq(ret, I18N_ERROR_NONE);
    i18n_ucalendar_type_e type = I18N_UCALENDAR_DEFAULT;

    ret = i18n_ucalendar_create(i18n_ustring_copy_ua(timezone_id, "Asia/Seoul"), len, locale, type, &ucal);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar text[24] = {0,};
    int32_t text_length = -1;
    int32_t parse_pos = 0;

    ret = i18n_udate_parse_calendar(format, ucal, i18n_ustring_copy_ua(text, "Jan 1, 1970, 9:00:00 AM"), text_length, &parse_pos);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ucalendar_destroy(ucal);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_parse_calendar_p2
 * @since_tizen     2.3
 * @description     Parses a ucalendar into an date/time using an
 *                  i18n_udate_format_h using different locale.
 */
int utc_capi_base_utils_i18n_udate_parse_calendar_p2(void)
{
    i18n_uchar timezone_id[24] = {0,};
    int32_t len = -1;
    const char *locale = I18N_ULOCALE_US;
    i18n_ucalendar_type_e type = I18N_UCALENDAR_TRADITIONAL;
    i18n_ucalendar_h ucal = NULL;

    for(; type<=I18N_UCALENDAR_GREGORIAN; type++)
    {
        ret = i18n_ucalendar_create(i18n_ustring_copy_ua(timezone_id, "Asia/Seoul"), len, locale, type, &ucal);
        assert_eq(ret, I18N_ERROR_NONE);

        i18n_uchar text[24] = {0,};
        int32_t text_length = -1;
        int32_t parse_pos = 0;

        ret = i18n_udate_parse_calendar(format, ucal, i18n_ustring_copy_ua(text, "Jan 1, 1970, 9:00:00 AM"), text_length, &parse_pos);
        i18n_ucalendar_destroy(ucal);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_parse_calendar_n
 * @since_tizen     2.3
 * @description     Parses a ucalendar into an date/time using an
 *                  i18n_udate_format_h with NULL format parameter.
 */
int utc_capi_base_utils_i18n_udate_parse_calendar_n(void)
{
    i18n_ucalendar_h ucal = NULL;
    i18n_uchar timezone_id[24] = {0,};
    int32_t len = -1;
    const char *locale;
    ret = i18n_ulocale_get_default(&locale);
    assert_eq(ret, I18N_ERROR_NONE);
    i18n_ucalendar_type_e type = I18N_UCALENDAR_DEFAULT;

    ret = i18n_ucalendar_create(i18n_ustring_copy_ua(timezone_id, "Asia/Seoul"), len, locale, type, &ucal);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar text[24] = {0,};
    int32_t text_length = -1;
    int32_t parse_pos = 0;

    ret = i18n_udate_parse_calendar(NULL, ucal, i18n_ustring_copy_ua(text, "Jan 1, 1970, 9:00:00 AM"), text_length, &parse_pos);
    i18n_ucalendar_destroy(ucal);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_parse_calendar_n2
 * @since_tizen     2.3
 * @description     Parses a ucalendar into an date/time using an
 *                  i18n_udate_format_h with NULL format parameter.
 */
int utc_capi_base_utils_i18n_udate_parse_calendar_n2(void)
{
    i18n_uchar text[24] = {0,};
    int32_t text_length = -1;
    int32_t parse_pos = 0;

    ret = i18n_udate_parse_calendar(format, NULL, i18n_ustring_copy_ua(text, "Jan 1, 1970, 9:00:00 AM"), text_length, &parse_pos);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_parse_calendar_n3
 * @since_tizen     2.3
 * @description     Parses a ucalendar into an date/time using an
 *                  i18n_udate_format_h with NULL text parameter.
 */
int utc_capi_base_utils_i18n_udate_parse_calendar_n3(void)
{
    i18n_ucalendar_h ucal = NULL;
    i18n_uchar timezone_id[24] = {0,};
    int32_t len = -1;
    const char *locale;
    ret = i18n_ulocale_get_default(&locale);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ucalendar_type_e type = I18N_UCALENDAR_DEFAULT;

    ret = i18n_ucalendar_create(i18n_ustring_copy_ua(timezone_id, "Asia/Seoul"), len, locale, type, &ucal);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t text_length = -1;
    int32_t parse_pos = 0;

    ret = i18n_udate_parse_calendar(format, ucal, NULL, text_length, &parse_pos);
    i18n_ucalendar_destroy(ucal);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_parse_calendar_n4
 * @since_tizen     2.3
 * @description     Parses a ucalendar into an date/time using an
 *                  i18n_udate_format_h with invalid text_lenght parameter.
 */
int utc_capi_base_utils_i18n_udate_parse_calendar_n4(void)
{
    i18n_ucalendar_h ucal = NULL;
    i18n_uchar timezone_id[24] = {0,};
    int32_t len = -1;
    const char *locale;
    ret = i18n_ulocale_get_default(&locale);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ucalendar_type_e type = I18N_UCALENDAR_DEFAULT;

    ret = i18n_ucalendar_create(i18n_ustring_copy_ua(timezone_id, "Asia/Seoul"), len, locale, type, &ucal);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar text[24] = {0,};
    int32_t parse_pos = 0;

    ret = i18n_udate_parse_calendar(format, ucal, i18n_ustring_copy_ua(text, "Jan 1, 1970, 9:00:00 AM"), -2, &parse_pos);

    i18n_ucalendar_destroy(ucal);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_is_lenient_p
 * @since_tizen     2.3.1
 * @description     Determines if an i18n_udate_format_h will perform lenient
 *                  parsing.
 */
int utc_capi_base_utils_i18n_udate_is_lenient_p(void)
{
    i18n_udate_is_lenient(format);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_is_lenient_n
 * @since_tizen     2.3.1
 * @description     Determines if an i18n_udate_format_h will perform lenient
 *                  parsing passing NULL to parameter.
 */
int utc_capi_base_utils_i18n_udate_is_lenient_n(void)
{
    i18n_udate_is_lenient(NULL);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_lenient_p
 * @since_tizen     2.3.1
 * @description     Specifies that an i18n_udate_format_h will perform lenient
 *                  parsing.
 */
int utc_capi_base_utils_i18n_udate_set_lenient_p(void)
{
    ret = i18n_udate_set_lenient(format, true);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_lenient_p2
 * @since_tizen     2.3.1
 * @description     Specifies that an i18n_udate_format_h will not perform
 *                  lenient parsing.
 */
int utc_capi_base_utils_i18n_udate_set_lenient_p2(void)
{
    ret = i18n_udate_set_lenient(format, false);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_lenient_n
 * @since_tizen     2.3.1
 * @description     Specifies that an i18n_udate_format_h will perform
 *                  lenient parsing passing NULL to format parameter.
 */
int utc_capi_base_utils_i18n_udate_set_lenient_n(void)
{
    ret = i18n_udate_set_lenient(NULL, true);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_lenient_n2
 * @since_tizen     2.3.1
 * @description     Specifies that an i18n_udate_format_h will not perform
 *                  lenient parsing passing NULL to format parameter.
 */
int utc_capi_base_utils_i18n_udate_set_lenient_n2(void)
{
    ret = i18n_udate_set_lenient(NULL, false);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_calendar_p
 * @since_tizen     2.3.1
 * @description     Gets the i18n_ucalendar_h associated with an
 *                  i18n_udate_format_h.
 */
int utc_capi_base_utils_i18n_udate_get_calendar_p(void)
{
    i18n_ucalendar_h calendar = NULL;

    ret = i18n_udate_get_calendar(format, &calendar);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_calendar_n
 * @since_tizen     2.3.1
 * @description     Gets the i18n_ucalendar_h associated with an
 *                  i18n_udate_format_h passing NULL format parameter.
 */
int utc_capi_base_utils_i18n_udate_get_calendar_n(void)
{
    i18n_ucalendar_h calendar = NULL;

    ret = i18n_udate_get_calendar(NULL, &calendar);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_calendar_n2
 * @since_tizen     2.3.1
 * @description     Gets the i18n_ucalendar_h associated with an
 *                  i18n_udate_format_h passing NULL calendar parameter.
 */
int utc_capi_base_utils_i18n_udate_get_calendar_n2(void)
{
    ret = i18n_udate_get_calendar(format, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_calendar_p
 * @since_tizen     2.3.1
 * @description     Gets and sets the i18n_ucalendar_h associated with an
 *                  i18n_udate_format_h.
 */
int utc_capi_base_utils_i18n_udate_set_calendar_p(void)
{
    i18n_ucalendar_h calendar = NULL;

    ret = i18n_udate_get_calendar(format, &calendar);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_udate_set_calendar(format, calendar);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_calendar_n
 * @since_tizen     2.3.1
 * @description     Gets and sets the i18n_ucalendar_h associated with an
 *                  i18n_udate_format_h passing NULL to format parameter.
 */
int utc_capi_base_utils_i18n_udate_set_calendar_n(void)
{
    i18n_ucalendar_h calendar = NULL;

    ret = i18n_udate_get_calendar(format, &calendar);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_udate_set_calendar(NULL, calendar);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_calendar_n2
 * @since_tizen     2.3.1
 * @description     Sets the i18n_ucalendar_h associated with an
 *                  i18n_udate_format_h passing NULL to calendar_to_set parameter.
 */
int utc_capi_base_utils_i18n_udate_set_calendar_n2(void)
{
    ret = i18n_udate_set_calendar(format, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_number_format_p
 * @since_tizen     2.3.1
 * @description     Gets the i18n_unumber_format_h associated with an
 *                  i18n_udate_format_h.
 */
int utc_capi_base_utils_i18n_udate_get_number_format_p(void)
{
    i18n_unumber_format_h number_format = NULL;

    ret = i18n_udate_get_number_format(format, &number_format);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_number_format_n
 * @since_tizen     2.3.1
 * @description     Gets the i18n_unumber_format_h associated with an
 *                  i18n_udate_format_h passing NULL to format parameter.
 */
int utc_capi_base_utils_i18n_udate_get_number_format_n(void)
{
    i18n_unumber_format_h number_format = NULL;

    ret = i18n_udate_get_number_format(NULL, &number_format);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_number_format_n2
 * @since_tizen     2.3.1
 * @description     Gets the i18n_unumber_format_h associated with an
 *                  i18n_udate_format_h passing NULL to number_format parameter.
 */
int utc_capi_base_utils_i18n_udate_get_number_format_n2(void)
{
    ret = i18n_udate_get_number_format(format, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_number_format_p
 * @since_tizen     2.3.1
 * @description     Gets and sets the i18n_unumber_format_h associated with an
 *                  i18n_udate_format_h.
 */
int utc_capi_base_utils_i18n_udate_set_number_format_p(void)
{
    i18n_unumber_format_h number_format = NULL;

    ret = i18n_udate_get_number_format(format, &number_format);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_udate_set_number_format(format, number_format);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_number_format_n
 * @since_tizen     2.3.1
 * @description     Gets and sets the i18n_unumber_format_h associated with an
 *                  i18n_udate_format_h passing NULL to format parameter.
 */
int utc_capi_base_utils_i18n_udate_set_number_format_n(void)
{
    i18n_unumber_format_h number_format = NULL;

    ret = i18n_udate_get_number_format(format, &number_format);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_udate_set_number_format(NULL, number_format);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_number_format_n2
 * @since_tizen     2.3.1
 * @description     Sets the i18n_unumber_format_h associated with an
 *                  i18n_udate_format_h passing NULL to number_format parameter.
 */
int utc_capi_base_utils_i18n_udate_set_number_format_n2(void)
{
    ret = i18n_udate_set_number_format(format, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_available_p
 * @since_tizen     2.3.1
 * @description     Gets a locale for which date/time formatting patterns are
 *                  available.
 */
int utc_capi_base_utils_i18n_udate_get_available_p(void)
{
    int32_t locale_index = 1;

    i18n_udate_get_available(locale_index);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_available_n
 * @since_tizen     2.3.1
 * @description     Gets a locale for which date/time formatting patterns are
 *                  available passing invalid locale_index parameter.
 */
int utc_capi_base_utils_i18n_udate_get_available_n(void)
{
    int32_t locale_index = -1;

    i18n_udate_get_available(locale_index);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_count_available_p
 * @since_tizen     2.3.1
 * @description     Determines how many locales have date/time formatting
 *                  patterns available.
 */
int utc_capi_base_utils_i18n_udate_count_available_p(void)
{
    int32_t count;

    count = i18n_udate_count_available();
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_geq(count , 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_2digit_year_start_p
 * @since_tizen     2.3.1
 * @description     Gets the year relative to which all 2-digit years are
 *                  interpreted.
 */
int utc_capi_base_utils_i18n_udate_get_2digit_year_start_p(void)
{
    i18n_udate year;
    ret = i18n_udate_get_2digit_year_start(format, &year);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_2digit_year_start_n
 * @since_tizen     2.3.1
 * @description     Gets the year relative to which all 2-digit years are
 *                  interpreted passing NULL to format parameter.
 */
int utc_capi_base_utils_i18n_udate_get_2digit_year_start_n(void)
{
    i18n_udate year;

    ret = i18n_udate_get_2digit_year_start(NULL, &year);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_2digit_year_start_n2
 * @since_tizen     2.3.1
 * @description     Gets the year relative to which all 2-digit years are
 *                  interpreted passing NULL to year parameter.
 */
int utc_capi_base_utils_i18n_udate_get_2digit_year_start_n2(void)
{
    ret = i18n_udate_get_2digit_year_start(format, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_2digit_year_start_p
 * @since_tizen     2.3.1
 * @description     Gets and sets the year relative to which all 2-digit years
 *                  will be interpreted.
 */
int utc_capi_base_utils_i18n_udate_set_2digit_year_start_p(void)
{
    i18n_udate date = 0;

    ret = i18n_udate_get_2digit_year_start(format, &date);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_udate_set_2digit_year_start(format, date);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_2digit_year_start_n
 * @since_tizen     2.3.1
 * @description     Gets and sets the year relative to which all 2-digit years
 *                  will be interpreted passing NULL to format parameter.
 */
int utc_capi_base_utils_i18n_udate_set_2digit_year_start_n(void)
{
    i18n_udate date = 0;

    ret = i18n_udate_get_2digit_year_start(format, &date);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_udate_set_2digit_year_start(NULL, date);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_to_pattern_p
 * @since_tizen     2.3.1
 * @description     Extracts the pattern from an i18n_udate_format_h.
 */
int utc_capi_base_utils_i18n_udate_to_pattern_p(void)
{
    i18n_ubool localized = true;
    i18n_uchar buffer[32] = {0,};
    int32_t buffer_size = sizeof(buffer)/sizeof(buffer[0]);

    i18n_udate_to_pattern(format, localized, buffer, buffer_size);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_to_pattern_p2
 * @since_tizen     2.3.1
 * @description     Extracts the pattern from an i18n_udate_format_h.
 */
int utc_capi_base_utils_i18n_udate_to_pattern_p2(void)
{
    i18n_ubool localized = false;
    i18n_uchar buffer[32] = {0,};
    int32_t buffer_size = sizeof(buffer)/sizeof(buffer[0]);

    i18n_udate_to_pattern(format, localized, buffer, buffer_size);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_to_pattern_n
 * @since_tizen     2.3.1
 * @description     Extracts the pattern from an i18n_udate_format_h passing
 *                  NULL to format parameter.
 */
int utc_capi_base_utils_i18n_udate_to_pattern_n(void)
{
    i18n_ubool localized = true;
    i18n_uchar buffer[32] = {0,};
    int32_t buffer_size = sizeof(buffer)/sizeof(buffer[0]);

    i18n_udate_to_pattern(NULL, localized, buffer, buffer_size);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_to_pattern_n2
 * @since_tizen     2.3.1
 * @description     Extracts the pattern from an i18n_udate_format_h passing
 *                  NULL to result parameter.
 */
int utc_capi_base_utils_i18n_udate_to_pattern_n2(void)
{
    i18n_ubool localized = true;
    i18n_uchar buffer[32] = {0,};
    int32_t buffer_size = sizeof(buffer)/sizeof(buffer[0]);

    i18n_udate_to_pattern(format, localized, NULL, buffer_size);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_to_pattern_n3
 * @since_tizen     2.3.1
 * @description     Extracts the pattern from an i18n_udate_format_h passing
 *                  invalid result_length parameter.
 */
int utc_capi_base_utils_i18n_udate_to_pattern_n3(void)
{
    i18n_ubool localized = true;
    i18n_uchar buffer[32] = {0,};

    i18n_udate_to_pattern(format, localized, buffer, -1);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_apply_pattern_p
 * @since_tizen     2.3.1
 * @description     Sets the pattern used by an i18n_udate_format_h.
 */
int utc_capi_base_utils_i18n_udate_apply_pattern_p(void)
{
    i18n_ubool localized = true;
    const char *pattern = "MMM d, y,";
    i18n_uchar buffer[32] = {0,};
    int32_t pattern_length = -1;

    ret = i18n_udate_apply_pattern(format, localized, i18n_ustring_copy_ua(buffer, pattern), pattern_length);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_apply_pattern_p2
 * @since_tizen     2.3.1
 * @description     Sets the pattern used by an i18n_udate_format_h.
 */
int utc_capi_base_utils_i18n_udate_apply_pattern_p2(void)
{
    i18n_ubool localized = false;
    const char *pattern = "MMM d, y,";
    i18n_uchar buffer[32] = {0,};
    int32_t pattern_length = -1;

    ret = i18n_udate_apply_pattern(format, localized, i18n_ustring_copy_ua(buffer, pattern), pattern_length);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_apply_pattern_n
 * @since_tizen     2.3.1
 * @description     Sets the pattern used by an i18n_udate_format_h passing NULL
 *                  to format parameter.
 */
int utc_capi_base_utils_i18n_udate_apply_pattern_n(void)
{
    i18n_ubool localized = true;
    const char *pattern = "MMM d, y,";
    i18n_uchar buffer[32] = {0,};
    int32_t pattern_length = -1;

    ret = i18n_udate_apply_pattern(NULL, localized, i18n_ustring_copy_ua(buffer, pattern), pattern_length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_symbols_p
 * @since_tizen     2.3.1
 * @description     Gets the symbols associated with an i18n_udate_format_h for
 *                  different type parameter values.
 */
int utc_capi_base_utils_i18n_udate_get_symbols_p(void)
{
    i18n_udate_format_symbol_type_e type = I18N_UDATE_FORMAT_SYMBOL_TYPE_ERAS;
    int32_t symbol_index = 0;
    i18n_uchar buffer[64] = {0,};
    int32_t buffer_size = sizeof(buffer)/sizeof(buffer[0]);

    for(; type<=I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_SHORTER_WEEKDAYS; type++)
    {
        i18n_udate_get_symbols(format, type, symbol_index, buffer, buffer_size);
        ret = get_last_result();
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_symbols_n
 * @since_tizen     2.3.1
 * @description     Gets the symbols associated with an i18n_udate_format_h
 *                  passing NULL to format parameter.
 */
int utc_capi_base_utils_i18n_udate_get_symbols_n(void)
{
    i18n_udate_format_symbol_type_e type = I18N_UDATE_FORMAT_SYMBOL_TYPE_MONTHS;
    int32_t symbol_index = 0;
    i18n_uchar buffer[32] = {0,};
    int32_t buffer_size = sizeof(buffer)/sizeof(buffer[0]);

    i18n_udate_get_symbols(NULL, type, symbol_index, buffer, buffer_size);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_symbols_n2
 * @since_tizen     2.3.1
 * @description     Gets the symbols associated with an i18n_udate_format_h
 *                  passing invalid type parameter.
 */
int utc_capi_base_utils_i18n_udate_get_symbols_n2(void)
{
    int32_t symbol_index = 0;
    i18n_uchar buffer[32] = {0,};
    int32_t buffer_size = sizeof(buffer)/sizeof(buffer[0]);

    i18n_udate_get_symbols(format, -1, symbol_index, buffer, buffer_size);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_symbols_n3
 * @since_tizen     2.3.1
 * @description     Gets the symbols associated with an i18n_udate_format_h
 *                  passing invalid symbol_index parameter.
 */
int utc_capi_base_utils_i18n_udate_get_symbols_n3(void)
{
    i18n_udate_format_symbol_type_e type = I18N_UDATE_FORMAT_SYMBOL_TYPE_MONTHS;
    i18n_uchar buffer[32] = {0,};
    int32_t buffer_size = sizeof(buffer)/sizeof(buffer[0]);

    i18n_udate_get_symbols(format, type, -1, buffer, buffer_size);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_symbols_n4
 * @since_tizen     2.3.1
 * @description     Gets the symbols associated with an i18n_udate_format_h
 *                  passing NULL to result parameter.
 */
int utc_capi_base_utils_i18n_udate_get_symbols_n4(void)
{
    i18n_udate_format_symbol_type_e type = I18N_UDATE_FORMAT_SYMBOL_TYPE_MONTHS;
    int32_t symbol_index = 0;
    i18n_uchar buffer[32] = {0,};
    int32_t buffer_size = sizeof(buffer)/sizeof(buffer[0]);

    i18n_udate_get_symbols(format, type, symbol_index, NULL, buffer_size);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_symbols_n5
 * @since_tizen     2.3.1
 * @description     Gets the symbols associated with an i18n_udate_format_h
 *                  passing invalid result_length parameter.
 */
int utc_capi_base_utils_i18n_udate_get_symbols_n5(void)
{
    i18n_udate_format_symbol_type_e type = I18N_UDATE_FORMAT_SYMBOL_TYPE_MONTHS;
    int32_t symbol_index = 0;
    i18n_uchar buffer[32] = {0,};

    i18n_udate_get_symbols(format, type, symbol_index, buffer, -1);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_count_symbols_p
 * @since_tizen     2.3.1
 * @description     Counts the number of particular symbols for an
 *                  i18n_udate_format_h for different type parameter values.
 */
int utc_capi_base_utils_i18n_udate_count_symbols_p(void)
{
    i18n_udate_format_symbol_type_e type = I18N_UDATE_FORMAT_SYMBOL_TYPE_ERAS;

    for(; type<=I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_SHORTER_WEEKDAYS; type++)
    {
        i18n_udate_count_symbols(format, type);
        ret = get_last_result();
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_count_symbols_n
 * @since_tizen     2.3.1
 * @description     Counts the number of particular symbols for an
 *                  i18n_udate_format_h passing NULL to format parameter.
 */
int utc_capi_base_utils_i18n_udate_count_symbols_n(void)
{
    i18n_udate_format_symbol_type_e type = I18N_UDATE_FORMAT_SYMBOL_TYPE_MONTHS;

    i18n_udate_count_symbols(NULL, type);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_symbols_p
 * @since_tizen     2.3.1
 * @description     Sets the symbols associated with an i18n_udate_format_h for
 *                  different type parameter values.
 */
int utc_capi_base_utils_i18n_udate_set_symbols_p(void)
{
    i18n_udate_format_symbol_type_e type = I18N_UDATE_FORMAT_SYMBOL_TYPE_ERAS;
    int32_t symbol_index = 0;
    const char *symbol = "tizenary";
    i18n_uchar buffer[32] = {0,};
    int32_t buffer_size = sizeof(buffer)/sizeof(buffer[0]);

    for(; type<=I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_SHORTER_WEEKDAYS; type++)
    {
        ret = i18n_udate_set_symbols(format, type, symbol_index, i18n_ustring_copy_ua(buffer, symbol), buffer_size);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_symbols_n
 * @since_tizen     2.3.1
 * @description     Sets the symbols associated with an i18n_udate_format_h
 *                  passing NULL to format parameter.
 */
int utc_capi_base_utils_i18n_udate_set_symbols_n(void)
{
    i18n_udate_format_symbol_type_e type = I18N_UDATE_FORMAT_SYMBOL_TYPE_MONTHS;
    int32_t symbol_index = 0;
    const char *symbol = "tizenary";
    i18n_uchar buffer[32] = {0,};
    int32_t buffer_size = sizeof(buffer)/sizeof(buffer[0]);

    ret = i18n_udate_set_symbols(NULL, type, symbol_index, i18n_ustring_copy_ua(buffer, symbol), buffer_size);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_symbols_n2
 * @since_tizen     2.3.1
 * @description     Sets the symbols associated with an i18n_udate_format_h
 *                  passing invalid type parameter value.
 */
int utc_capi_base_utils_i18n_udate_set_symbols_n2(void)
{
    int32_t symbol_index = 0;
    const char *symbol = "tizenary";
    i18n_uchar buffer[32] = {0,};
    int32_t buffer_size = sizeof(buffer)/sizeof(buffer[0]);

    ret = i18n_udate_set_symbols(format, -1, symbol_index, i18n_ustring_copy_ua(buffer, symbol), buffer_size);
    assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_symbols_n3
 * @since_tizen     2.3.1
 * @description     Sets the symbols associated with an i18n_udate_format_h
 *                  passing invalid symbol_index parameter value.
 */
int utc_capi_base_utils_i18n_udate_set_symbols_n3(void)
{
    i18n_udate_format_symbol_type_e type = I18N_UDATE_FORMAT_SYMBOL_TYPE_MONTHS;
    const char *symbol = "tizenary";
    i18n_uchar buffer[32] = {0,};
    int32_t buffer_size = sizeof(buffer)/sizeof(buffer[0]);

    ret = i18n_udate_set_symbols(format, type, -1, i18n_ustring_copy_ua(buffer, symbol), buffer_size);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_symbols_n4
 * @since_tizen     2.3.1
 * @description     Sets the symbols associated with an i18n_udate_format_h
 *                  passing NULL to value parameter.
 */
int utc_capi_base_utils_i18n_udate_set_symbols_n4(void)
{
    i18n_udate_format_symbol_type_e type = I18N_UDATE_FORMAT_SYMBOL_TYPE_MONTHS;
    int32_t symbol_index = 0;
    i18n_uchar buffer[32] = {0,};
    int32_t buffer_size = sizeof(buffer)/sizeof(buffer[0]);

    ret = i18n_udate_set_symbols(format, type, symbol_index, NULL, buffer_size);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_symbols_n5
 * @since_tizen     2.3.1
 * @description     Sets the symbols associated with an i18n_udate_format_h
 *                  passing invalid value_length parameter value.
 */
int utc_capi_base_utils_i18n_udate_set_symbols_n5(void)
{
    i18n_udate_format_symbol_type_e type = I18N_UDATE_FORMAT_SYMBOL_TYPE_MONTHS;
    int32_t symbol_index = 0;
    const char *symbol = "tizenary";
    i18n_uchar buffer[32] = {0,};

    ret = i18n_udate_set_symbols(format, type, symbol_index, i18n_ustring_copy_ua(buffer, symbol), -2);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_locale_by_type_p
 * @since_tizen     2.3.1
 * @description     Gets the locale for this date format object.
 */
int utc_capi_base_utils_i18n_udate_get_locale_by_type_p(void)
{
    i18n_udate_get_locale_by_type(format, I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_locale_by_type_p2
 * @since_tizen     2.3.1
 * @description     Gets the locale for this date format object.
 */
int utc_capi_base_utils_i18n_udate_get_locale_by_type_p2(void)
{
    i18n_udate_get_locale_by_type(format, I18N_ULOCALE_DATA_LOCALE_TYPE_VALID_LOCALE);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_locale_by_type_n
 * @since_tizen     2.3.1
 * @description     Gets the locale for this date format object passing NULL to
 *                  format parameter.
 */
int utc_capi_base_utils_i18n_udate_get_locale_by_type_n(void)
{
    i18n_ulocale_data_locale_type_e type = I18N_ULOCALE_DATA_LOCALE_TYPE_VALID_LOCALE;

    i18n_udate_get_locale_by_type(NULL, type);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_get_locale_by_type_n2
 * @since_tizen     2.3.1
 * @description     Gets the locale for this date format object passing invalid
 *                  type parameter.
 */
int utc_capi_base_utils_i18n_udate_get_locale_by_type_n2(void)
{
    i18n_udate_get_locale_by_type(format, -1);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_context_p
 * @since_tizen     2.3.1
 * @description     Sets different i18n_udisplay_context_e values in the formatter.
 */
int utc_capi_base_utils_i18n_udate_set_context_p(void)
{
    i18n_udisplay_context_e value = I18N_UDISPLAY_CONTEXT_CAPITALIZATION_NONE;

    for(; value<=I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_STANDALONE; value++)
    {
        ret = i18n_udate_set_context(format, value);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_context_n
 * @since_tizen     2.3.1
 * @description     Sets a particular i18n_udisplay_context_e value in the
 *                  formatter passing NULL to format parameter.
 */
int utc_capi_base_utils_i18n_udate_set_context_n(void)
{
    i18n_udisplay_context_e value = I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_STANDALONE;

    ret = i18n_udate_set_context(NULL, value);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_context_n2
 * @since_tizen     2.3.1
 * @description     Sets a particular i18n_udisplay_context_e value in the
 *                  formatter passing invalid value parameter.
 */
int utc_capi_base_utils_i18n_udate_set_context_n2(void)
{
    ret = i18n_udate_set_context(format, -1);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_context_n3
 * @since_tizen     2.3.1
 * @description     Sets a particular i18n_udisplay_context_e value in the
 *                  formatter passing not supported value parameter.
 */
int utc_capi_base_utils_i18n_udate_set_context_n3(void)
{
    ret = i18n_udate_set_context(format, I18N_UDISPLAY_CONTEXT_STANDARD_NAMES);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udate_set_context_n4
 * @since_tizen     2.3.1
 * @description     Sets a particular i18n_udisplay_context_e value in the
 *                  formatter passing not supported value parameter.
 */
int utc_capi_base_utils_i18n_udate_set_context_n4(void)
{
    ret = i18n_udate_set_context(format, I18N_UDISPLAY_CONTEXT_DIALECT_NAMES);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
