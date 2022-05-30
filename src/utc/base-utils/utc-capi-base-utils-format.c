#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

static i18n_format_h format = NULL;
static int ret = I18N_ERROR_NONE;

/**
 * @function        utc_capi_base_utils_format_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_format_startup(void)
{
    i18n_measure_format_h measure_format = NULL;
    const char *language = I18N_ULOCALE_ENGLISH;
    const char *country = "US";

    ret = i18n_measure_format_create_currency_format_from_locale(language, country, &measure_format);
    if (ret == I18N_ERROR_NONE) {
        ret = i18n_measure_format_clone(measure_format, &format);

        i18n_measure_format_destroy(measure_format);
    }
}

/**
 * @function        utc_capi_base_utils_format_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_format_cleanup(void)
{
    if (format != NULL) {
        i18n_format_destroy(format);
        format = NULL;
    }
}

/**
 * @testcase utc_capi_base_utils_i18n_format_get_locale_p
 * @since_tizen 3.0
 * @description Calls i18n_format_get_locale and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_format_get_locale_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    i18n_ulocale_data_locale_type_e type = I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE;

    char *language = NULL;
    char *country = NULL;

    ret = i18n_format_get_locale(format, type, &language, &country);

    assert_eq(ret, I18N_ERROR_NONE);
    assert(!strcmp(language, I18N_ULOCALE_ENGLISH));
    assert(!strcmp(country, "US"));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_get_locale_n
 * @since_tizen 3.0
 * @description Calls i18n_format_get_locale passing invalid format and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_get_locale_n(void)
{
    i18n_ulocale_data_locale_type_e type = I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE;

    char *language = NULL;
    char *country = NULL;

    ret = i18n_format_get_locale(NULL, type, &language, &country);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_get_locale_n2
 * @since_tizen 3.0
 * @description Calls i18n_format_get_locale passing invalid type and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_get_locale_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    i18n_ulocale_data_locale_type_e type = I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE - 1; // Invalid parameter

    char *language = NULL;
    char *country = NULL;

    ret = i18n_format_get_locale(format, type, &language, &country);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_get_locale_n3
 * @since_tizen 3.0
 * @description Calls i18n_format_get_locale passing invalid language and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_get_locale_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    i18n_ulocale_data_locale_type_e type = I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE;

    char *country = NULL;

    ret = i18n_format_get_locale(format, type, NULL, &country);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_get_locale_n4
 * @since_tizen 3.0
 * @description Calls i18n_format_get_locale passing invalid country and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_get_locale_n4(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    i18n_ulocale_data_locale_type_e type = I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE;

    char *language = NULL;

    ret = i18n_format_get_locale(format, type, &language, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_parse_object_p
 * @since_tizen 3.0
 * @description Calls i18n_format_parse_object and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_format_parse_object_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    const char *source = "$1,234.56";

    i18n_formattable_h result = NULL;

    ret = i18n_format_parse_object(format, source, &result);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(result, NULL);

    double value = 0;
    ret = i18n_formattable_get_double(result, &value);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(value, 1234.56);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_parse_object_n
 * @since_tizen 3.0
 * @description Calls i18n_format_parse_object passing invalid format and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_parse_object_n(void)
{
    const char *source = "$1,234.56";

    i18n_formattable_h result = NULL;

    ret = i18n_format_parse_object(NULL, source, &result);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(result, NULL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_parse_object_n2
 * @since_tizen 3.0
 * @description Calls i18n_format_parse_object passing invalid source and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_parse_object_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    i18n_formattable_h result = NULL;

    ret = i18n_format_parse_object(format, NULL, &result);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(result, NULL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_parse_object_n3
 * @since_tizen 3.0
 * @description Calls i18n_format_parse_object passing invalid result and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_parse_object_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    const char *source = "$1,234.56";

    ret = i18n_format_parse_object(format, source, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_format_p
 * @since_tizen 3.0
 * @description Calls i18n_format_format and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_format_format_p(void)
{
    double double_to_set = 13.0;
    i18n_formattable_h formattable = NULL;
    ret = i18n_formattable_create_with_double(double_to_set, &formattable);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(formattable, NULL);

    char *append_to = "Price: ";

    ret = i18n_format_format(format, formattable, &append_to);

    i18n_formattable_destroy(formattable);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(append_to, "Price: $13.00"), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_format_n
 * @since_tizen 3.0
 * @description Calls i18n_format_format passing invalid format and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_format_n(void)
{
    double double_to_set = 13.0;
    i18n_formattable_h formattable = NULL;
    ret = i18n_formattable_create_with_double(double_to_set, &formattable);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(formattable, NULL);

    char *append_to = "Price: ";

    ret = i18n_format_format(NULL, formattable, &append_to);

    i18n_formattable_destroy(formattable);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_format_n2
 * @since_tizen 3.0
 * @description Calls i18n_format_format passing invalid formattable and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_format_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    char *append_to = "Price: ";

    ret = i18n_format_format(format, NULL, &append_to);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_format_n3
 * @since_tizen 3.0
 * @description Calls i18n_format_format passing invalid append_to and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_format_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    double double_to_set = 13.0;
    i18n_formattable_h formattable = NULL;
    ret = i18n_formattable_create_with_double(double_to_set, &formattable);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(formattable, NULL);

    ret = i18n_format_format(format, formattable, NULL);

    i18n_formattable_destroy(formattable);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_clone_p
 * @since_tizen 3.0
 * @description Calls i18n_format_clone and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_format_clone_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    i18n_format_h clone = NULL;

    ret = i18n_format_clone(format, &clone);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(clone, NULL);

    i18n_format_destroy(clone);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_clone_n
 * @since_tizen 3.0
 * @description Calls i18n_format_clone passing invalid format and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_clone_n(void)
{
    i18n_format_h clone = NULL;

    ret = i18n_format_clone(NULL, &clone);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(clone, NULL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_clone_n2
 * @since_tizen 3.0
 * @description Calls i18n_format_clone passing invalid clone and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_clone_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    ret = i18n_format_clone(format, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_destroy_p
 * @since_tizen 3.0
 * @description Calls i18n_format_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_format_destroy_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    ret = i18n_format_destroy(format);

    assert_eq(ret, I18N_ERROR_NONE);
    format = NULL;

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_destroy_n
 * @since_tizen 3.0
 * @description Calls i18n_format_destroy passing invalid format and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_destroy_n(void)
{
    ret = i18n_format_destroy(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_format_p
 * @since_tizen 3.0
 * @description Calls i18n_format_format_with_field_position and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_format_format_with_field_position_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    double double_to_set = 13.0;
    i18n_formattable_h formattable = NULL;
    ret = i18n_formattable_create_with_double(double_to_set, &formattable);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(formattable, NULL);

    char *append_to = "Price: ";

    i18n_field_position_h field_position = NULL;
    i18n_field_position_create(&field_position);
    assert_neq(field_position, NULL);

    ret = i18n_format_format_with_field_position(format, formattable, &append_to, field_position);

    i18n_formattable_destroy(formattable);
    i18n_field_position_destroy(field_position);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(append_to, "Price: $13.00"), 0);

    free(append_to);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_format_n
 * @since_tizen 3.0
 * @description Calls i18n_format_format_with_field_position passing invalid format and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_format_with_field_position_n(void)
{
    double double_to_set = 13.0;
    i18n_formattable_h formattable = NULL;
    ret = i18n_formattable_create_with_double(double_to_set, &formattable);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(formattable, NULL);

    char *append_to = "Price: ";

    i18n_field_position_h field_position = NULL;
    i18n_field_position_create(&field_position);
    assert_neq(field_position, NULL);

    ret = i18n_format_format_with_field_position(NULL, formattable, &append_to, field_position);

    i18n_formattable_destroy(formattable);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_format_n2
 * @since_tizen 3.0
 * @description Calls i18n_format_format_with_field_position passing invalid formattable and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_format_with_field_position_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    char *append_to = "Price: ";

    i18n_field_position_h field_position = NULL;
    i18n_field_position_create(&field_position);
    assert_neq(field_position, NULL);

    ret = i18n_format_format_with_field_position(format, NULL, &append_to, field_position);

    i18n_field_position_destroy(field_position);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_format_n3
 * @since_tizen 3.0
 * @description Calls i18n_format_format_with_field_position passing invalid append_to and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_format_with_field_position_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    double double_to_set = 13.0;
    i18n_formattable_h formattable = NULL;
    ret = i18n_formattable_create_with_double(double_to_set, &formattable);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(formattable, NULL);

    i18n_field_position_h field_position = NULL;
    i18n_field_position_create(&field_position);
    assert_neq(field_position, NULL);

    ret = i18n_format_format_with_field_position(format, formattable, NULL, field_position);

    i18n_formattable_destroy(formattable);
    i18n_field_position_destroy(field_position);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_format_n4
 * @since_tizen 3.0
 * @description Calls i18n_format_format_with_field_position passing invalid field_position and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_format_with_field_position_n4(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    double double_to_set = 13.0;
    i18n_formattable_h formattable = NULL;
    ret = i18n_formattable_create_with_double(double_to_set, &formattable);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(formattable, NULL);

    char *append_to = "Price: ";

    ret = i18n_format_format_with_field_position(format, formattable, &append_to, NULL);

    i18n_formattable_destroy(formattable);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_parse_object_with_parse_position_p
 * @since_tizen 3.0
 * @description Calls i18n_format_parse_object_with_parse_position and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_format_parse_object_with_parse_position_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    char *source = "$1,234.56";

    i18n_formattable_h result = NULL;

    i18n_parse_position_h parse_position = NULL;
    i18n_parse_position_create(&parse_position);
    assert_neq(parse_position, NULL);

    ret = i18n_format_parse_object_with_parse_position(format, source, parse_position, &result);

    i18n_parse_position_destroy(parse_position);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(result, NULL);

    double value = 0;
    ret = i18n_formattable_get_double(result, &value);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(value, 1234.56);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_parse_object_with_parse_position_n
 * @since_tizen 3.0
 * @description Calls i18n_format_parse_object_with_parse_position passing invalid format and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_parse_object_with_parse_position_n(void)
{
    char *source = "$1,234.56";

    i18n_formattable_h result = NULL;

    i18n_parse_position_h parse_position = NULL;
    i18n_parse_position_create(&parse_position);
    assert_neq(parse_position, NULL);

    ret = i18n_format_parse_object_with_parse_position(NULL, source, parse_position, &result);

    i18n_parse_position_destroy(parse_position);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(result, NULL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_parse_object_with_parse_position_n2
 * @since_tizen 3.0
 * @description Calls i18n_format_parse_object_with_parse_position passing invalid source and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_parse_object_with_parse_position_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    i18n_formattable_h result = NULL;

    i18n_parse_position_h parse_position = NULL;
    i18n_parse_position_create(&parse_position);
    assert_neq(parse_position, NULL);

    ret = i18n_format_parse_object_with_parse_position(format, NULL, parse_position, &result);

    i18n_parse_position_destroy(parse_position);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(result, NULL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_parse_object_with_parse_position_n3
 * @since_tizen 3.0
 * @description Calls i18n_format_parse_object_with_parse_position passing invalid result and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_parse_object_with_parse_position_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    char *source = "$1,234.56";

    i18n_parse_position_h parse_position = NULL;
    i18n_parse_position_create(&parse_position);
    assert_neq(parse_position, NULL);

    ret = i18n_format_parse_object_with_parse_position(format, source, parse_position, NULL);

    i18n_parse_position_destroy(parse_position);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_parse_object_with_parse_position_n4
 * @since_tizen 3.0
 * @description Calls i18n_format_parse_object_with_parse_position passing invalid parse_position and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_parse_object_with_parse_position_n4(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    char *source = "$1,234.56";

    i18n_formattable_h result = NULL;

    ret = i18n_format_parse_object_with_parse_position(format, source, NULL, &result);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_get_locale_id_p
 * @since_tizen 5.0
 * @description Calls i18n_format_get_locale_id and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_format_get_locale_id_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    i18n_ulocale_data_locale_type_e type = I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE;

    char *locale_id = NULL;

    ret = i18n_format_get_locale_id(format, type, &locale_id);

    assert_eq(ret, I18N_ERROR_NONE);
    assert(!strcmp(locale_id, "en_US"));;

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_get_locale_id_n
 * @since_tizen 5.0
 * @description Calls i18n_format_get_locale_id passing invalid format and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_get_locale_id_n(void)
{
    i18n_ulocale_data_locale_type_e type = I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE;
    char *locale_id = NULL;

    ret = i18n_format_get_locale_id(NULL, type, &locale_id);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_get_locale_id_n2
 * @since_tizen 5.0
 * @description Calls i18n_format_get_locale_id passing invalid type and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_get_locale_id_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    i18n_ulocale_data_locale_type_e type = I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE - 1; // Invalid parameter
    char *locale_id = NULL;

    ret = i18n_format_get_locale_id(format, type, &locale_id);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_format_get_locale_id_n3
 * @since_tizen 5.0
 * @description Calls i18n_format_get_locale_id passing invalid locale_id and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_format_get_locale_id_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    i18n_ulocale_data_locale_type_e type = I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE;

    ret = i18n_format_get_locale_id(format, type, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
