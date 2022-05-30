#include "assert.h"
#include <utils_i18n.h>
#include <string.h>
#include <dlog.h>

static i18n_measure_format_h measure_format = NULL;
static int ret = I18N_ERROR_NONE;

static i18n_format_h format = NULL;
static i18n_formattable_h formattable = NULL;
static i18n_field_position_h field_position = NULL;
static i18n_parse_position_h parse_position = NULL;
static i18n_unumber_format_h num_format = NULL;

static char *ref_language = NULL;
static char *ref_country = NULL;
static const char *locale_id = "en_US";
static i18n_umeasure_format_width_e format_width = I18N_UMEASFMT_WIDTH_WIDE;

static char *clone_language = NULL;
static char *clone_country = NULL;
static char *append_to = NULL;

#define MAX_MEASURES 3
#define BUFSIZE 256

static int n_measures = 0;
static i18n_measure_h measure_array[MAX_MEASURES] = { NULL };
static i18n_measure_unit_h measure_unit = NULL;

typedef int (*create_measure_unit_cb)(i18n_measure_unit_h *measure_unit);

static int create_measure(create_measure_unit_cb cb, double number, i18n_measure_h *measure)
{
    i18n_measure_unit_h measure_unit = NULL;
    ret = cb(&measure_unit);
    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_formattable_h formattable = NULL;
    ret = i18n_formattable_create_with_double(number, &formattable);
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    *measure = NULL;
    ret = i18n_measure_create(formattable, measure_unit, measure);
    i18n_formattable_destroy(formattable);
    assert_neq(*measure, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

static int create_measures_for_length(void)
{
    assert_eq(create_measure(i18n_measure_unit_create_kilometer, 6378, &measure_array[0]), 0);
    assert_eq(create_measure(i18n_measure_unit_create_meter, 137, &measure_array[1]), 0);
    n_measures = 2;

    return 0;
}

static int create_measures_for_mass(void)
{
    assert_eq(create_measure(i18n_measure_unit_create_kilogram, 100, &measure_array[0]), 0);
    assert_eq(create_measure(i18n_measure_unit_create_gram, 10, &measure_array[1]), 0);
    n_measures = 2;

    return 0;
}

static int create_measures_per_unit(void)
{
    assert_eq(create_measure(i18n_measure_unit_create_kilometer, 300000, &measure_array[0]), 0);
    n_measures = 1;

    return 0;
}

/**
 * @function        utc_capi_base_utils_measure_format_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_measure_format_startup(void)
{
    i18n_umeasure_format_width_e format_width = I18N_UMEASFMT_WIDTH_WIDE;

    ret = i18n_measure_format_create_from_locale_id(locale_id, format_width, &measure_format);
}

/**
 * @function        utc_capi_base_utils_measure_format_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_measure_format_cleanup(void)
{
    if (measure_format != NULL) {
        i18n_measure_format_destroy(measure_format);
        measure_format = NULL;
    }
    if (format != NULL) {
        i18n_format_destroy(format);
        format = NULL;
    }
    if (formattable != NULL) {
        i18n_formattable_destroy(formattable);
        formattable = NULL;
    }
    if (parse_position != NULL) {
        i18n_parse_position_destroy(parse_position);
        parse_position = NULL;
    }
    if (field_position != NULL) {
        i18n_field_position_destroy(field_position);
        field_position = NULL;
    }
    if (num_format != NULL) {
        i18n_unumber_destroy(num_format);
        num_format = NULL;
    }
    int i = 0;
    for (; i < n_measures; ++i) {
        if (measure_array[i] != NULL) {
            i18n_measure_destroy(measure_array[i]);
            measure_array[i] = NULL;
        }
    }
    n_measures = 0;

    if (measure_unit != NULL) {
        i18n_measure_unit_destroy(measure_unit);
        measure_unit = NULL;
    }

    free(ref_language);
    ref_language = NULL;

    free(ref_country);
    ref_country = NULL;

    free(clone_language);
    clone_language = NULL;

    free(clone_country);
    clone_country = NULL;

    free(append_to);
    append_to = NULL;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_create_currency_format_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_create_currency_format and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_format_create_currency_format_p(void)
{
    utc_capi_base_utils_measure_format_cleanup();
    assert_eq(measure_format, NULL);

    ret = i18n_measure_format_create_currency_format(&measure_format);

    assert_neq(measure_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_create_currency_format_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_create_currency_format passing invalid
 *              measure_format and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_create_currency_format_n(void)
{
    ret = i18n_measure_format_create_currency_format(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase
 *           utc_capi_base_utils_i18n_measure_format_create_currency_format_from_locale_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_create_currency_format_from_locale and
 *              checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_format_create_currency_format_from_locale_p(void)
{
    utc_capi_base_utils_measure_format_cleanup();

    const char *language = I18N_ULOCALE_KOREAN;
    const char *country = "KR";

    ret = i18n_measure_format_create_currency_format_from_locale(language, country, &measure_format);

    assert_neq(measure_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase
 *           utc_capi_base_utils_i18n_measure_format_create_currency_format_from_locale_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_create_currency_format_from_locale passing
 *              invalid measure_format and checks for an invalid parameter error
 *              code.
 */
int utc_capi_base_utils_i18n_measure_format_create_currency_format_from_locale_n(void)
{
    const char *language = I18N_ULOCALE_KOREAN;
    const char *country = "KR";

    ret = i18n_measure_format_create_currency_format_from_locale(language, country, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_clone_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_clone and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_format_clone_p(void)
{
    assert_neq(measure_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(format, NULL);

    ret = i18n_measure_format_clone(measure_format, &format);

    assert_neq(format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ulocale_data_locale_type_e type = I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE;
    ret = i18n_format_get_locale(format, type, &clone_language, &clone_country);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_format_get_locale((i18n_format_h) measure_format, type, &ref_language, &ref_country);
    assert_eq(ret, I18N_ERROR_NONE);

    assert(!strcmp(clone_language, ref_language));
    assert(!strcmp(clone_country, ref_country));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_clone_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_clone passing invalid measure_format and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_clone_n(void)
{
    i18n_format_h clone = NULL;

    ret = i18n_measure_format_clone(NULL, &clone);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_clone_n2
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_clone passing invalid clone and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_clone_n2(void)
{
    assert_neq(measure_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_format_clone(measure_format, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_destroy_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_destroy and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_format_destroy_p(void)
{
    assert_neq(measure_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_format_destroy(measure_format);

    assert_eq(ret, I18N_ERROR_NONE);

    measure_format = NULL;

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_destroy_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_destroy passing invalid measure_format and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_destroy_n(void)
{
    ret = i18n_measure_format_destroy(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_create_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_create and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_format_create_p(void)
{
    utc_capi_base_utils_measure_format_cleanup();
    assert_eq(measure_format, NULL);

    const char *language = I18N_ULOCALE_KOREAN;
    const char *country = "KR";
    i18n_umeasure_format_width_e format_width = I18N_UMEASFMT_WIDTH_WIDE;

    ret = i18n_measure_format_create(language, country, format_width, &measure_format);

    assert_neq(measure_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_create_p2
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_create passing NULL language and checks
 *              whether function succeeded (as NULL is an acceptable value for
 *              the language parameter).
 */
int utc_capi_base_utils_i18n_measure_format_create_p2(void)
{
    utc_capi_base_utils_measure_format_cleanup();
    assert_eq(measure_format, NULL);

    const char *country = "KR";
    i18n_umeasure_format_width_e format_width = I18N_UMEASFMT_WIDTH_WIDE;

    ret = i18n_measure_format_create(NULL, country, format_width, &measure_format);

    assert_neq(measure_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_create_p3
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_create passing NULL country and checks
 *              whether function succeeded (as NULL is an acceptable value for
 *              the country parameter).
 */
int utc_capi_base_utils_i18n_measure_format_create_p3(void)
{
    utc_capi_base_utils_measure_format_cleanup();
    assert_eq(measure_format, NULL);

    const char *language = I18N_ULOCALE_KOREAN;
    i18n_umeasure_format_width_e format_width = I18N_UMEASFMT_WIDTH_WIDE;

    ret = i18n_measure_format_create(language, NULL, format_width, &measure_format);

    assert_neq(measure_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_create_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_create passing invalid hint and checks
 *              whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_format_create_n(void)
{
    i18n_measure_format_h measure_format = NULL;

    const char *language = I18N_ULOCALE_KOREAN;
    const char *country = "KR";

    i18n_umeasure_format_width_e format_width = I18N_UMEASFMT_WIDTH_WIDE - 1; // Invalid parameter

    ret = i18n_measure_format_create(language, country, format_width, &measure_format);

    assert_eq(measure_format, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_create_n2
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_create passing invalid measure_format and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_create_n2(void)
{
    const char *language = I18N_ULOCALE_KOREAN;
    const char *country = "KR";
    i18n_umeasure_format_width_e format_width = I18N_UMEASFMT_WIDTH_WIDE;

    ret = i18n_measure_format_create(language, country, format_width, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_format and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_format_format_p(void)
{
    utc_capi_base_utils_measure_format_cleanup();
    assert_eq(measure_format, NULL);

    const char *language = I18N_ULOCALE_ENGLISH;
    const char *country = "US";
    ret = i18n_measure_format_create_currency_format_from_locale(language, country, &measure_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure_format, NULL);

    double double_to_set = 13.0;
    i18n_formattable_create_with_double(double_to_set, &formattable);
    assert_neq(formattable, NULL);

    const char *input = "Price: ";
    int length = strlen(input);
    append_to = (char *) malloc (sizeof(input[0]) * (length + 1));
    strncpy(append_to, input, length + 1);

    i18n_field_position_create_for_field(0, &field_position);
    i18n_field_position_set_field(field_position, 1);
    assert_neq(field_position, NULL);

    ret = i18n_measure_format_format(measure_format, formattable, &append_to, field_position);

    assert_eq(ret, I18N_ERROR_NONE);
    dlog_print(DLOG_DEBUG, "BaseUtils", "Output buffer: %s", append_to);
    assert_eq(strcmp(append_to, "Price: $13.00"), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_format passing invalid measure_format and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_n(void)
{
    i18n_formattable_h formattable = NULL;
    double double_to_set = 13.0;
    i18n_formattable_create_with_double(double_to_set, &formattable);
    assert_neq(formattable, NULL);

    char *append_to = "Price: ";

    i18n_field_position_h field_position = NULL;
    i18n_field_position_create(&field_position);
    assert_neq(field_position, NULL);

    ret = i18n_measure_format_format(NULL, formattable, &append_to, field_position);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(strcmp(append_to, "Price: "), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_n2
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_format passing invalid formattable and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_n2(void)
{
    i18n_measure_format_h measure_format = NULL;
    ret = i18n_measure_format_create_currency_format(&measure_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure_format, NULL);

    char *append_to = "Price: ";

    i18n_field_position_h field_position = NULL;
    ret = i18n_field_position_create(&field_position);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(field_position, NULL);

    ret = i18n_measure_format_format(measure_format, NULL, &append_to, field_position);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_n3
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_format passing invalid append_to and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_n3(void)
{
    i18n_measure_format_h measure_format = NULL;
    ret = i18n_measure_format_create_currency_format(&measure_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure_format, NULL);

    i18n_formattable_h formattable = NULL;
    double double_to_set = 13.0;
    ret = i18n_formattable_create_with_double(double_to_set, &formattable);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(formattable, NULL);

    i18n_field_position_h field_position = NULL;
    ret = i18n_field_position_create(&field_position);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(field_position, NULL);

    ret = i18n_measure_format_format(measure_format, formattable, NULL, field_position);

    i18n_field_position_destroy(field_position);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_n4
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_format passing invalid field_position and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_n4(void)
{
    i18n_measure_format_h measure_format = NULL;
    ret = i18n_measure_format_create_currency_format(&measure_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure_format, NULL);

    i18n_formattable_h formattable = NULL;
    double double_to_set = 13.0;
    ret = i18n_formattable_create_with_double(double_to_set, &formattable);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(formattable, NULL);

    char *append_to = "Price: ";

    ret = i18n_measure_format_format(measure_format, formattable, &append_to, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_parse_object_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_parse_object and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_format_parse_object_p(void)
{
    ret = i18n_parse_position_create(&parse_position);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(parse_position, NULL);

    i18n_uparse_error_s parse_err;
    ret = i18n_unumber_create(I18N_UNUMBER_NUMBERING_SYSTEM, NULL, -1,
                              I18N_ULOCALE_US, &parse_err, &num_format);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *source = "X";
    ret = i18n_measure_format_parse_object(num_format, source, parse_position, &formattable);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_formattable_type_e type;
    ret = i18n_formattable_get_type(formattable, &type);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(type, I18N_FORMATTABLE_TYPE_LONG);

    int32_t number;
    ret = i18n_formattable_get_long(formattable, &number);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(number, 10);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_parse_object_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_parse_object passing invalid measure_format and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_parse_object_n(void)
{
    ret = i18n_parse_position_create(&parse_position);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(parse_position, NULL);

    const char *source = "X";
    ret = i18n_measure_format_parse_object(NULL, source, parse_position, &formattable);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_parse_object_n2
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_parse_object passing invalid source and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_parse_object_n2(void)
{
    ret = i18n_parse_position_create(&parse_position);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(parse_position, NULL);

    i18n_uparse_error_s parse_err;
    ret = i18n_unumber_create(I18N_UNUMBER_NUMBERING_SYSTEM, NULL, -1,
                              I18N_ULOCALE_US, &parse_err, &num_format);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_format_parse_object(num_format, NULL, parse_position, &formattable);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_parse_object_n3
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_parse_object passing invalid parse_position and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_parse_object_n3(void)
{
    i18n_uparse_error_s parse_err;
    ret = i18n_unumber_create(I18N_UNUMBER_NUMBERING_SYSTEM, NULL, -1,
                              I18N_ULOCALE_US, &parse_err, &num_format);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *source = "X";
    ret = i18n_measure_format_parse_object(num_format, source, NULL, &formattable);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_parse_object_n4
 * @since_tizen 3.0
 * @description Calls i18n_measure_format_parse_object passing invalid formattable and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_parse_object_n4(void)
{
    ret = i18n_parse_position_create(&parse_position);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(parse_position, NULL);

    i18n_uparse_error_s parse_err;
    ret = i18n_unumber_create(I18N_UNUMBER_NUMBERING_SYSTEM, NULL, -1,
                              I18N_ULOCALE_US, &parse_err, &num_format);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *source = "X";
    ret = i18n_measure_format_parse_object(num_format, source, parse_position, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_buff_p
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_buff and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_format_format_buff_p(void)
{
    const char *sample_string = "Price: ";
    const char *output_string = "Price: $13.00";

    assert_eq(create_measures_for_length(), 0);
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    utc_capi_base_utils_measure_format_cleanup();
    const char *language = I18N_ULOCALE_ENGLISH;
    const char *country = "US";
    ret = i18n_measure_format_create_currency_format_from_locale(language, country, &measure_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure_format, NULL);

    double double_to_set = 13.0;
    ret = i18n_formattable_create_with_double(double_to_set, &formattable);
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_measure_format_format_buff(measure_format, formattable, field_position,
                                          BUFSIZE, append_to, &output_length);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(output_buffer, output_string), 0);
    assert_eq(output_length, strnlen(output_string, BUFSIZE));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_buff_n
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_buff passing invalid measure_format and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_buff_n(void)
{
    const char *sample_string = "Price: ";

    assert_eq(create_measures_for_length(), 0);
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    double double_to_set = 13.0;
    ret = i18n_formattable_create_with_double(double_to_set, &formattable);
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_measure_format_format_buff(NULL, formattable, field_position,
                                          BUFSIZE, append_to, &output_length);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(strcmp(output_buffer, sample_string), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_buff_n2
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_buff passing invalid formattable and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_buff_n2(void)
{
    const char *sample_string = "Price: ";

    assert_eq(create_measures_for_length(), 0);
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    utc_capi_base_utils_measure_format_cleanup();
    const char *language = I18N_ULOCALE_ENGLISH;
    const char *country = "US";
    ret = i18n_measure_format_create_currency_format_from_locale(language, country, &measure_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure_format, NULL);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_measure_format_format_buff(measure_format, NULL, field_position,
                                          BUFSIZE, append_to, &output_length);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(strcmp(output_buffer, sample_string), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_buff_n3
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_buff passing invalid field_position and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_buff_n3(void)
{
    const char *sample_string = "Price: ";

    assert_eq(create_measures_for_length(), 0);
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    utc_capi_base_utils_measure_format_cleanup();
    const char *language = I18N_ULOCALE_ENGLISH;
    const char *country = "US";
    ret = i18n_measure_format_create_currency_format_from_locale(language, country, &measure_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure_format, NULL);

    double double_to_set = 13.0;
    ret = i18n_formattable_create_with_double(double_to_set, &formattable);
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_measure_format_format_buff(measure_format, formattable, NULL,
                                          BUFSIZE, append_to, &output_length);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(strcmp(output_buffer, sample_string), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_buff_n4
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_buff passing invalid append_to_size and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_buff_n4(void)
{
    const char *sample_string = "Price: ";

    assert_eq(create_measures_for_length(), 0);
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    utc_capi_base_utils_measure_format_cleanup();
    const char *language = I18N_ULOCALE_ENGLISH;
    const char *country = "US";
    ret = i18n_measure_format_create_currency_format_from_locale(language, country, &measure_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure_format, NULL);

    double double_to_set = 13.0;
    ret = i18n_formattable_create_with_double(double_to_set, &formattable);
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t output_length = -1;
    ret = i18n_measure_format_format_buff(measure_format, formattable, field_position,
                                          -1, append_to, &output_length);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);
    assert_eq(strcmp(output_buffer, sample_string), 0);
    assert_eq(output_length, strlen("$13.00"));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_buff_n5
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_buff passing invalid append_to and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_buff_n5(void)
{
    utc_capi_base_utils_measure_format_cleanup();
    const char *language = I18N_ULOCALE_ENGLISH;
    const char *country = "US";
    ret = i18n_measure_format_create_currency_format_from_locale(language, country, &measure_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure_format, NULL);

    double double_to_set = 13.0;
    ret = i18n_formattable_create_with_double(double_to_set, &formattable);
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_measure_format_format_buff(measure_format, formattable, field_position,
                                          BUFSIZE, NULL, &output_length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(output_length, -1);

    return 0;
}



/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_buff_n6
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_buff passing invalid output_length and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_buff_n6(void)
{
    const char *sample_string = "Price: ";

    assert_eq(create_measures_for_length(), 0);
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    utc_capi_base_utils_measure_format_cleanup();
    const char *language = I18N_ULOCALE_ENGLISH;
    const char *country = "US";
    ret = i18n_measure_format_create_currency_format_from_locale(language, country, &measure_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure_format, NULL);

    double double_to_set = 13.0;
    ret = i18n_formattable_create_with_double(double_to_set, &formattable);
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_format_format_buff(measure_format, formattable, field_position,
                                          BUFSIZE, append_to, NULL);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(strcmp(output_buffer, sample_string), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_measures_p
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_measures and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_format_format_measures_p(void)
{
    const char *sample_string = "The equatorial radius of the Earth is about ";
    const char *output_string = "The equatorial radius of the Earth is about "
                                "6,378 kilometers, 137 meters";

    assert_eq(create_measures_for_length(), 0);
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_measure_format_format_measures(measure_format, measure_array, n_measures,
                                              field_position, BUFSIZE, append_to, &output_length);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strncmp(output_buffer, output_string, strlen(output_string)), 0);
    assert_eq(output_length, strnlen(output_string, BUFSIZE));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_measures_p2
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_measures and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_format_format_measures_p2(void)
{
    const char *sample_string = "Weight: ";
    const char *output_string = "Weight: 100 kilograms, 10 grams";

    assert_eq(create_measures_for_mass(), 0);
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_measure_format_format_measures(measure_format, measure_array, n_measures,
                                              field_position, BUFSIZE, append_to, &output_length);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strncmp(output_buffer, output_string, strlen(output_string)), 0);
    assert_eq(output_length, strnlen(output_string, BUFSIZE));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_measures_n
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_measures passing invalid measure_format and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_measures_n(void)
{
    const char *sample_string = "The equatorial radius of the Earth is about ";

    assert_eq(create_measures_for_length(), 0);
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_measure_format_format_measures(NULL, measure_array, n_measures,
                                              field_position, BUFSIZE, append_to, &output_length);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(strncmp(output_buffer, sample_string, strlen(sample_string)), 0);
    assert_eq(output_length, -1);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_measures_n2
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_measures passing invalid measure_array and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_measures_n2(void)
{
    const char *sample_string = "The equatorial radius of the Earth is about ";

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_measure_format_format_measures(measure_format, NULL, n_measures,
                                              field_position, BUFSIZE, append_to, &output_length);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(strncmp(output_buffer, sample_string, strlen(sample_string)), 0);
    assert_eq(output_length, -1);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_measures_n3
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_measures passing invalid measures_count and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_measures_n3(void)
{
    const char *sample_string = "The equatorial radius of the Earth is about ";

    assert_eq(create_measures_for_length(), 0);
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_measure_format_format_measures(measure_format, measure_array, 0,
                                              field_position, BUFSIZE, append_to, &output_length);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(strncmp(output_buffer, sample_string, strlen(sample_string)), 0);
    assert_eq(output_length, -1);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_measures_n4
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_measures passing invalid field_position and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_measures_n4(void)
{
    const char *sample_string = "The equatorial radius of the Earth is about ";

    assert_eq(create_measures_for_length(), 0);
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    int output_length = -1;
    ret = i18n_measure_format_format_measures(measure_format, measure_array, n_measures,
                                              NULL, BUFSIZE, append_to, &output_length);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(strncmp(output_buffer, sample_string, strlen(sample_string)), 0);
    assert_eq(output_length, -1);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_measures_n5
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_measures passing invalid append_to_size and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_measures_n5(void)
{
    const char *sample_string = "The equatorial radius of the Earth is about ";

    assert_eq(create_measures_for_length(), 0);
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_measure_format_format_measures(measure_format, measure_array, n_measures,
                                              field_position, -1, append_to, &output_length);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);
    assert_eq(strncmp(output_buffer, sample_string, strlen(sample_string)), 0);
    assert_eq(output_length, strlen("6,378 kilometers, 137 meters"));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_measures_n6
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_measures passing invalid append_to and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_measures_n6(void)
{
    assert_eq(create_measures_for_length(), 0);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_measure_format_format_measures(measure_format, measure_array, n_measures,
                                              field_position, BUFSIZE, NULL, &output_length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(output_length, -1);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_measures_n7
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_measures passing invalid output_length and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_measures_n7(void)
{
    const char *sample_string = "The equatorial radius of the Earth is about ";

    assert_eq(create_measures_for_length(), 0);
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_format_format_measures(measure_format, measure_array, n_measures,
                                              field_position, BUFSIZE, append_to, NULL);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(strncmp(output_buffer, sample_string, strlen(sample_string)), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_measures_n8
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_measures passing uninitialized measure_array and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_measures_n8(void)
{
    const char *sample_string = "The equatorial radius of the Earth is about ";

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;

    /* measure_array is invalid, not initialized */
    ret = i18n_measure_format_format_measures(measure_format, measure_array, MAX_MEASURES,
                                              field_position, BUFSIZE, append_to, &output_length);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(strncmp(output_buffer, sample_string, strlen(sample_string)), 0);
    assert_eq(output_length, -1);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_measure_per_unit_p
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_measure_per_unit and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_format_format_measure_per_unit_p(void)
{
    const char *sample_string = "The speed of light in vacuum is approx. ";
    const char *output_string = "The speed of light in vacuum is approx. "
                                "300,000 kilometers per second";

    ret = i18n_measure_unit_create_second(&measure_unit);
    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    assert_eq(create_measures_per_unit(), 0);
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_measure_format_format_measure_per_unit(measure_format, measure_array[0],
                                                      measure_unit, field_position,
                                                      BUFSIZE, append_to, &output_length);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_NONE);
    dlog_print(DLOG_DEBUG, "BaseUtils", "Output buffer: %s", output_buffer);
    dlog_print(DLOG_DEBUG, "BaseUtils", "Output string: %s", output_string);
    assert_eq(strcmp(output_buffer, output_string), 0);
    assert_eq(output_length, strnlen(output_string, BUFSIZE));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_measure_per_unit_n
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_measure_per_unit passing invalid measure_format and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_measure_per_unit_n(void)
{
    const char *sample_string = "The speed of light in vacuum is approx. ";

    ret = i18n_measure_unit_create_second(&measure_unit);
    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    assert_eq(create_measures_per_unit(), 0);
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_measure_format_format_measure_per_unit(NULL, measure_array[0],
                                                      measure_unit, field_position,
                                                      BUFSIZE, append_to, &output_length);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(strcmp(output_buffer, sample_string), 0);
    assert_eq(output_length, -1);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_measure_per_unit_n2
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_measure_per_unit passing invalid measure and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_measure_per_unit_n2(void)
{
    const char *sample_string = "The speed of light in vacuum is approx. ";

    ret = i18n_measure_unit_create_second(&measure_unit);
    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_measure_format_format_measure_per_unit(measure_format, NULL,
                                                      measure_unit, field_position,
                                                      BUFSIZE, append_to, &output_length);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(strcmp(output_buffer, sample_string), 0);
    assert_eq(output_length, -1);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_measure_per_unit_n3
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_measure_per_unit passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_measure_per_unit_n3(void)
{
    const char *sample_string = "The speed of light in vacuum is approx. ";

    assert_eq(create_measures_per_unit(), 0);
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_measure_format_format_measure_per_unit(measure_format, measure_array[0],
                                                      NULL, field_position,
                                                      BUFSIZE, append_to, &output_length);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(strcmp(output_buffer, sample_string), 0);
    assert_eq(output_length, -1);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_measure_per_unit_n4
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_measure_per_unit passing invalid field_position and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_measure_per_unit_n4(void)
{
    const char *sample_string = "The speed of light in vacuum is approx. ";
    ret = i18n_measure_unit_create_second(&measure_unit);
    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    assert_eq(create_measures_per_unit(), 0);
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    int output_length = -1;
    ret = i18n_measure_format_format_measure_per_unit(measure_format, measure_array[0],
                                                      measure_unit, NULL,
                                                      BUFSIZE, append_to, &output_length);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(strcmp(output_buffer, sample_string), 0);
    assert_eq(output_length, -1);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_measure_per_unit_n5
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_measure_per_unit passing invalid append_to_size and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_measure_per_unit_n5(void)
{
    const char *sample_string = "The speed of light in vacuum is approx. ";

    ret = i18n_measure_unit_create_second(&measure_unit);
    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    assert_eq(create_measures_per_unit(), 0);
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_measure_format_format_measure_per_unit(measure_format, measure_array[0],
                                                      measure_unit, field_position,
                                                      -1, append_to, &output_length);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);
    assert_eq(strncmp(output_buffer, sample_string, strlen(sample_string)), 0);
    assert_eq(output_length, strlen("300,000 kilometers per second"));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_measure_per_unit_n6
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_measure_per_unit passing invalid append_to and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_measure_per_unit_n6(void)
{
    ret = i18n_measure_unit_create_second(&measure_unit);
    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    assert_eq(create_measures_per_unit(), 0);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int output_length = -1;
    ret = i18n_measure_format_format_measure_per_unit(measure_format, measure_array[0],
                                                      measure_unit, field_position,
                                                      BUFSIZE, NULL, &output_length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(output_length, -1);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_format_measure_per_unit_n7
 * @since_tizen 4.0
 * @description Calls i18n_measure_format_format_measure_per_unit passing invalid output_length and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_format_measure_per_unit_n7(void)
{
    const char *sample_string = "The speed of light in vacuum is approx. ";

    ret = i18n_measure_unit_create_second(&measure_unit);
    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    assert_eq(create_measures_per_unit(), 0);
    i18n_uchar append_to[BUFSIZE] = { 0 };
    i18n_ustring_copy_ua_n(append_to, sample_string, BUFSIZE);

    ret = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &field_position);
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_format_format_measure_per_unit(measure_format, measure_array[0],
                                                      measure_unit, field_position,
                                                      BUFSIZE, append_to, NULL);
    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(strcmp(output_buffer, sample_string), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_get_unit_display_name_p
 * @since_tizen 5.0
 * @description Calls i18n_measure_format_get_unit_display_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_format_get_unit_display_name_p(void)
{
    const char *output_string = "meters";
    ret = i18n_measure_unit_create_meter(&measure_unit);
    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar buffer[BUFSIZE] = { 0 };
    int32_t length = -1;
    ret = i18n_measure_format_get_unit_display_name(measure_format, measure_unit, BUFSIZE, buffer, &length);
    assert_eq(ret, I18N_ERROR_NONE);

    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, buffer, BUFSIZE);
    assert_eq(0, strcmp(output_buffer, output_string));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_get_unit_display_name_p2
 * @since_tizen 5.0
 * @description Calls i18n_measure_format_get_unit_display_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_format_get_unit_display_name_p2(void)
{
    const char *output_string = "seconds";
    ret = i18n_measure_unit_create_second(&measure_unit);
    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar buffer[BUFSIZE] = { 0 };
    int32_t length = -1;
    ret = i18n_measure_format_get_unit_display_name(measure_format, measure_unit, BUFSIZE, buffer, &length);
    assert_eq(ret, I18N_ERROR_NONE);

    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, buffer, BUFSIZE);
    assert_eq(0, strcmp(output_buffer, output_string));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_get_unit_display_name_p3
 * @since_tizen 5.0
 * @description Calls i18n_measure_format_get_unit_display_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_format_get_unit_display_name_p3(void)
{
    const char *output_string = "Sekunden";
    ret = i18n_measure_unit_create_second(&measure_unit);
    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_measure_format_h format_german;
    const char *language = "de";
    const char *country = "DE";
    i18n_umeasure_format_width_e format_width = I18N_UMEASFMT_WIDTH_WIDE;

    ret = i18n_measure_format_create(language, country, format_width, &format_german);

    i18n_uchar buffer[BUFSIZE] = { 0 };
    int32_t length = -1;
    ret = i18n_measure_format_get_unit_display_name(format_german, measure_unit, BUFSIZE, buffer, &length);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_format_destroy(format_german);
    assert_eq(ret, I18N_ERROR_NONE);

    char output_buffer[BUFSIZE] = { 0 };
    i18n_ustring_copy_au_n(output_buffer, buffer, BUFSIZE);
    assert_eq(0, strcmp(output_buffer, output_string));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_get_unit_display_name_n
 * @since_tizen 5.0
 * @description Calls i18n_measure_format_get_unit_display_name passing invalid measure_format and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_get_unit_display_name_n(void)
{
    ret = i18n_measure_unit_create_meter(&measure_unit);
    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar buffer[BUFSIZE] = { 0 };
    int32_t length = -1;
    ret = i18n_measure_format_get_unit_display_name(NULL, measure_unit, BUFSIZE, buffer, &length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_get_unit_display_name_n2
 * @since_tizen 5.0
 * @description Calls i18n_measure_format_get_unit_display_name passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_get_unit_display_name_n2(void)
{
    ret = i18n_measure_unit_create_meter(&measure_unit);
    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar buffer[BUFSIZE] = { 0 };
    int32_t length = -1;
    ret = i18n_measure_format_get_unit_display_name(measure_format, NULL, BUFSIZE, buffer, &length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_get_unit_display_name_n3
 * @since_tizen 5.0
 * @description Calls i18n_measure_format_get_unit_display_name passing invalid output_length and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_get_unit_display_name_n3(void)
{
    ret = i18n_measure_unit_create_meter(&measure_unit);
    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar buffer[BUFSIZE] = { 0 };
    ret = i18n_measure_format_get_unit_display_name(measure_unit, measure_unit, BUFSIZE, buffer, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_create_from_locale_id_p
 * @since_tizen 5.0
 * @description Calls i18n_measure_format_create_from_locale_id and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_format_create_from_locale_id_p(void)
{
    utc_capi_base_utils_measure_format_cleanup();
    assert_eq(measure_format, NULL);

    ret = i18n_measure_format_create_from_locale_id(locale_id, format_width, &measure_format);

    assert_neq(measure_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_create_from_locale_id_n
 * @since_tizen 5.0
 * @description Calls i18n_measure_format_create_from_locale_id passing invalid measure_format and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_create_from_locale_id_n(void)
{
    ret = i18n_measure_format_create_from_locale_id(locale_id, format_width, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_create_from_locale_id_n2
 * @since_tizen 5.0
 * @description Calls i18n_measure_format_create_from_locale_id passing invalid width and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_create_from_locale_id_n2(void)
{
    utc_capi_base_utils_measure_format_cleanup();
    assert_eq(measure_format, NULL);

    i18n_umeasure_format_width_e format_width = I18N_UMEASFMT_WIDTH_WIDE - 1; //invalid value

    ret = i18n_measure_format_create_from_locale_id(locale_id, format_width, &measure_format);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_create_currency_format_from_locale_id_p
 * @since_tizen 5.0
 * @description Calls i18n_measure_format_create_currency_format_from_locale_id and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_format_create_currency_format_from_locale_id_p(void)
{
    utc_capi_base_utils_measure_format_cleanup();
    assert_eq(measure_format, NULL);

    ret = i18n_measure_format_create_currency_format_from_locale_id(locale_id, &measure_format);

    assert_neq(measure_format, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_format_create_currency_format_from_locale_id_n
 * @since_tizen 5.0
 * @description Calls i18n_measure_format_create_currency_format_from_locale_id passing invalid measure_format and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_format_create_currency_format_from_locale_id_n(void)
{
    ret = i18n_measure_format_create_currency_format_from_locale_id(locale_id, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
