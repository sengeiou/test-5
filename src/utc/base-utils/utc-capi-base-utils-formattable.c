#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

#define count 3

static i18n_formattable_h formattable = NULL;
static int ret = I18N_ERROR_NONE;

static i18n_formattable_h array_to_set[count];

/**
 * @function        utc_capi_base_utils_formattable_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_formattable_startup(void)
{
    ret = i18n_formattable_create_default(&formattable);

    int i;
    for (i = 0; i < count; ++i) {
        array_to_set[i] = NULL;
    }
}

/**
 * @function        utc_capi_base_utils_formattable_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_formattable_cleanup(void)
{
    if (formattable != NULL) {
        i18n_formattable_destroy(formattable);
        formattable = NULL;
    }

    int i;
    for (i = 0; i < count; ++i) {
        if (array_to_set[i] != NULL) {
            i18n_formattable_destroy(array_to_set[i]);
            array_to_set[i] = NULL;
        }
    }
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_set_string_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_set_string and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_formattable_set_string_p(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *string_to_set = "Test string";

    ret = i18n_formattable_set_string(formattable, string_to_set);

    char *set_string = NULL;
    i18n_formattable_get_string(formattable, &set_string);

    i18n_formattable_type_e type;
    i18n_formattable_get_type(formattable, &type);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strncmp(set_string, string_to_set, strlen(string_to_set)), 0);
    assert_eq(type, I18N_FORMATTABLE_TYPE_STRING);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_set_string_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_set_string passing invalid formattable
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_set_string_n(void)
{
    i18n_formattable_h formattable = NULL; // Invalid parameter

    const char *string_to_set = "Test string";

    ret = i18n_formattable_set_string(formattable, string_to_set);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_set_long_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_set_long and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_formattable_set_long_p(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t long_to_set = 13;

    ret = i18n_formattable_set_long(formattable, long_to_set);

    int32_t set_long = 0;
    i18n_formattable_get_long(formattable, &set_long);

    i18n_formattable_type_e type;
    i18n_formattable_get_type(formattable, &type);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(set_long, long_to_set);
    assert_eq(type, I18N_FORMATTABLE_TYPE_LONG);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_set_long_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_set_long passing invalid formattable and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_set_long_n(void)
{
    i18n_formattable_h formattable = NULL; // Invalid parameter

    int32_t long_to_set = 0;

    ret = i18n_formattable_set_long(formattable, long_to_set);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_set_int64_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_set_int64 and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_formattable_set_int64_p(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int64_t long_long_to_set = 13;

    ret = i18n_formattable_set_int64(formattable, long_long_to_set);

    int64_t set_long_long = 0;
    i18n_formattable_get_int64(formattable, &set_long_long);

    i18n_formattable_type_e type;
    i18n_formattable_get_type(formattable, &type);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(set_long_long, long_long_to_set);
    assert_eq(type, I18N_FORMATTABLE_TYPE_INT64);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_set_int64_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_set_int64 passing invalid formattable and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_set_int64_n(void)
{
    i18n_formattable_h formattable = NULL; // Invalid parameter

    int64_t long_long_to_set = 0;

    ret = i18n_formattable_set_int64(formattable, long_long_to_set);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_set_double_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_set_double and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_formattable_set_double_p(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    double double_to_set = 13.0;

    ret = i18n_formattable_set_double(formattable, double_to_set);

    double set_double = 0.0;
    i18n_formattable_get_double(formattable, &set_double);

    i18n_formattable_type_e type;
    i18n_formattable_get_type(formattable, &type);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(set_double, double_to_set);
    assert_eq(type, I18N_FORMATTABLE_TYPE_DOUBLE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_set_double_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_set_double passing invalid formattable and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_set_double_n(void)
{
    i18n_formattable_h formattable = NULL; // Invalid parameter

    double double_to_set = 0.0;

    ret = i18n_formattable_set_double(formattable, double_to_set);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_set_date_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_set_date and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_formattable_set_date_p(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_udate date_to_set = 13.0;

    ret = i18n_formattable_set_date(formattable, date_to_set);

    double set_date = 0.0;
    i18n_formattable_get_date(formattable, &set_date);

    i18n_formattable_type_e type;
    i18n_formattable_get_type(formattable, &type);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(set_date, date_to_set);
    assert_eq(type, I18N_FORMATTABLE_TYPE_DATE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_set_date_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_set_date passing invalid formattable and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_set_date_n(void)
{
    i18n_formattable_h formattable = NULL; // Invalid parameter

    i18n_udate date_to_set = 0.0;

    ret = i18n_formattable_set_date(formattable, date_to_set);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_set_array_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_set_array and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_formattable_set_array_p(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int i;
    for (i = 0; i < count; ++i) {
        double value = i;
        ret = i18n_formattable_create_with_double(value, &array_to_set[i]);

        assert_neq(array_to_set[i], NULL);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    ret = i18n_formattable_set_array(formattable, array_to_set, count);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_formattable_type_e type;
    ret = i18n_formattable_get_type(formattable, &type);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(type, I18N_FORMATTABLE_TYPE_ARRAY);

    i18n_formattable_h *set_array;
    int32_t set_count = 0;
    ret = i18n_formattable_get_array(formattable, &set_array, &set_count);
    assert_eq(ret, I18N_ERROR_NONE);

    if (set_count != count) {
        free(set_array);
        assert_eq(set_count, count);
    }

    for (i = 0; i < set_count; ++i) {
        bool equal = false;
        ret = i18n_formattable_equal(array_to_set[i], set_array[i], &equal);

        if (ret != I18N_ERROR_NONE || !equal) {
            free(set_array);

            assert_eq(ret, I18N_ERROR_NONE);
            assert_eq(equal, true);
        }
    }

    free(set_array);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_set_array_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_set_array passing invalid formattable and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_set_array_n(void)
{
    int i;
    for (i = 0; i < count; ++i) {
        ret = i18n_formattable_create_default(&array_to_set[i]);

        assert_neq(array_to_set[i], NULL);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    ret = i18n_formattable_set_array(NULL, array_to_set, count);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_set_array_n2
 * @since_tizen 3.0
 * @description Calls i18n_formattable_set_array passing invalid array and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_set_array_n2(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_formattable_set_array(formattable, NULL, count);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_set_array_n3
 * @since_tizen 3.0
 * @description Calls i18n_formattable_set_array passing invalid count and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_set_array_n3(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int i;
    for (i = 0; i < count; ++i) {
        ret = i18n_formattable_create_default(&array_to_set[i]);

        assert_neq(array_to_set[i], NULL);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    ret = i18n_formattable_set_array(formattable, array_to_set, -1);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_element_at_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_element_at and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_formattable_element_at_p(void)
{
    int i;
    for (i = 0; i < count; ++i) {
        double value = i;
        ret = i18n_formattable_create_with_double(value, &array_to_set[i]);

        assert_neq(array_to_set[i], NULL);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    ret = i18n_formattable_destroy(formattable);
    assert_eq(ret, I18N_ERROR_NONE);
    formattable = NULL;

    ret = i18n_formattable_create_with_formattable_array(array_to_set, count, &formattable);
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t index = 1;
    i18n_formattable_h element;
    ret = i18n_formattable_element_at(formattable, index, &element);
    assert_neq(element, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    bool equal = false;
    ret = i18n_formattable_equal(array_to_set[index], element, &equal);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(equal, true);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_element_at_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_element_at passing invalid formattable and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_element_at_n(void)
{
    i18n_formattable_h formattable = NULL; // Invalid parameter

    int32_t index = 0;

    i18n_formattable_h element = NULL;

    ret = i18n_formattable_element_at(formattable, index, &element);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_element_at_n2
 * @since_tizen 3.0
 * @description Calls i18n_formattable_element_at passing invalid index and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_element_at_n2(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t index = -1; // Invalid parameter

    i18n_formattable_h element = NULL;

    ret = i18n_formattable_element_at(formattable, index, &element);

    assert_eq(ret, I18N_ERROR_INDEX_OUTOFBOUNDS);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_element_at_n3
 * @since_tizen 3.0
 * @description Calls i18n_formattable_element_at passing invalid element and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_element_at_n3(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t index = 0;

    ret = i18n_formattable_element_at(formattable, index, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_equal_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_equal and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_formattable_equal_p(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_formattable_h other = NULL;
    double value = 7;
    ret = i18n_formattable_create_with_double(value, &other);
    assert_neq(other, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    bool equal;
    ret = i18n_formattable_equal(formattable, other, &equal);

    i18n_formattable_destroy(other);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(equal, false);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_equal_p2
 * @since_tizen 3.0
 * @description Calls i18n_formattable_equal and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_formattable_equal_p2(void)
{
    assert_neq(formattable, NULL);

    i18n_formattable_h other = NULL;
    ret = i18n_formattable_clone(formattable, &other);
    assert_neq(other, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    bool equal;
    ret = i18n_formattable_equal(formattable, other, &equal);

    i18n_formattable_destroy(other);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(equal, true);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_equal_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_equal passing invalid formattable and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_equal_n(void)
{
    i18n_formattable_h formattable = NULL; // Invalid parameter

    i18n_formattable_h other = NULL;

    ret = i18n_formattable_create_default(&other);

    assert_neq(other, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    bool equal;
    ret = i18n_formattable_equal(formattable, other, &equal);

    i18n_formattable_destroy(other);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_equal_n2
 * @since_tizen 3.0
 * @description Calls i18n_formattable_equal passing invalid other and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_equal_n2(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_formattable_h other = NULL; // Invalid parameter

    bool equal;

    ret = i18n_formattable_equal(formattable, other, &equal);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_equal_n3
 * @since_tizen 3.0
 * @description Calls i18n_formattable_equal passing invalid equal argument and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_equal_n3(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_formattable_h other = NULL;

    ret = i18n_formattable_create_default(&other);

    assert_neq(other, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_formattable_equal(formattable, other, NULL);

    i18n_formattable_destroy(other);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_not_equal_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_not_equal and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_formattable_not_equal_p(void)
{
    double value = 7;
    i18n_formattable_h other = NULL;
    ret = i18n_formattable_create_with_double(value, &other);
    assert_neq(other, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    bool not_equal = false;
    ret = i18n_formattable_not_equal(formattable, other, &not_equal);

    i18n_formattable_destroy(other);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(not_equal, true);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_not_equal_p2
 * @since_tizen 3.0
 * @description Calls i18n_formattable_not_equal and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_formattable_not_equal_p2(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    bool not_equal;
    ret = i18n_formattable_not_equal(formattable, formattable, &not_equal);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(not_equal, false);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_not_equal_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_not_equal passing invalid formattable and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_not_equal_n(void)
{
    i18n_formattable_h formattable = NULL; // Invalid parameter

    i18n_formattable_h other = NULL;
    ret = i18n_formattable_create_default(&other);
    assert_neq(other, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    bool not_equal;
    ret = i18n_formattable_not_equal(formattable, other, &not_equal);

    i18n_formattable_destroy(other);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_not_equal_n2
 * @since_tizen 3.0
 * @description Calls i18n_formattable_not_equal passing invalid other and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_not_equal_n2(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_formattable_h other = NULL; // Invalid parameter

    bool not_equal;

    ret = i18n_formattable_not_equal(formattable, other, &not_equal);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_not_equal_n3
 * @since_tizen 3.0
 * @description Calls i18n_formattable_not_equal passing invalid not_equal
 *              argument and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_not_equal_n3(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_formattable_h other = NULL;
    ret = i18n_formattable_create_default(&other);
    assert_neq(other, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_formattable_not_equal(formattable, other, NULL);

    i18n_formattable_destroy(other);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_is_numeric_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_is_numeric and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_formattable_is_numeric_p(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    bool is_numeric;
    ret = i18n_formattable_is_numeric(formattable, &is_numeric);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(is_numeric, false);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_is_numeric_p2
 * @since_tizen 3.0
 * @description Calls i18n_formattable_is_numeric and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_formattable_is_numeric_p2(void)
{
    i18n_formattable_destroy(formattable);

    double value = 7;
    ret = i18n_formattable_create_with_double(value, &formattable);
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    bool is_numeric;
    ret = i18n_formattable_is_numeric(formattable, &is_numeric);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_numeric, true);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_is_numeric_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_is_numeric passing invalid formattable and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_is_numeric_n(void)
{
    i18n_formattable_h formattable = NULL; // Invalid parameter

    bool is_numeric;

    ret = i18n_formattable_is_numeric(formattable, &is_numeric);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_is_numeric_n2
 * @since_tizen 3.0
 * @description Calls i18n_formattable_is_numeric passing invalid is_numeric
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_is_numeric_n2(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_formattable_is_numeric(formattable, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_type_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_type and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_formattable_get_type_p(void)
{
    i18n_formattable_destroy(formattable);

    const char *test_string = "Test string";
    ret = i18n_formattable_create_with_char_string(test_string, &formattable);
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_formattable_type_e type;

    ret = i18n_formattable_get_type(formattable, &type);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(type, I18N_FORMATTABLE_TYPE_STRING);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_type_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_type passing invalid formattable and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_get_type_n(void)
{
    i18n_formattable_h formattable = NULL; // Invalid parameter

    i18n_formattable_type_e type;

    ret = i18n_formattable_get_type(formattable, &type);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_type_n2
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_type passing invalid type and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_get_type_n2(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_formattable_get_type(formattable, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_string_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_string and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_formattable_get_string_p(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *test_string = "Test string";
    ret = i18n_formattable_set_string(formattable, test_string);
    assert_eq(ret, I18N_ERROR_NONE);

    char *value = NULL;

    ret = i18n_formattable_get_string(formattable, &value);

    assert_eq(ret, I18N_ERROR_NONE);
    assert(!strcmp(value, test_string));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_string_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_string passing invalid formattable and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_get_string_n(void)
{
    i18n_formattable_h formattable = NULL; // Invalid parameter

    char *value = NULL;

    ret = i18n_formattable_get_string(formattable, &value);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_string_n2
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_string passing invalid value and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_get_string_n2(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *test_string = "Test string";
    ret = i18n_formattable_set_string(formattable, test_string);
    assert_eq(ret, I18N_ERROR_NONE);

    char **value = NULL; // Invalid parameter

    ret = i18n_formattable_get_string(formattable, value);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_long_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_long and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_formattable_get_long_p(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t l = 13;
    ret = i18n_formattable_set_long(formattable, l);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t value;

    ret = i18n_formattable_get_long(formattable, &value);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(value, l);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_long_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_long passing invalid formattable and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_get_long_n(void)
{
    i18n_formattable_h formattable = NULL; // Invalid parameter

    int32_t value;

    ret = i18n_formattable_get_long(formattable, &value);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_long_n2
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_long passing invalid value and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_get_long_n2(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t l = 13;
    ret = i18n_formattable_set_long(formattable, l);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_formattable_get_long(formattable, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_int64_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_int64 and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_formattable_get_int64_p(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int64_t ll = 13;
    ret = i18n_formattable_set_int64(formattable, ll);
    assert_eq(ret, I18N_ERROR_NONE);

    int64_t value = 0;

    ret = i18n_formattable_get_int64(formattable, &value);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(value, ll);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_int64_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_int64 passing invalid formattable and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_get_int64_n(void)
{
    i18n_formattable_h formattable = NULL; // Invalid parameter

    int64_t value;

    ret = i18n_formattable_get_int64(formattable, &value);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_int64_n2
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_int64 passing invalid value and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_get_int64_n2(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int64_t ll = 13;
    ret = i18n_formattable_set_int64(formattable, ll);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_formattable_get_int64(formattable, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_double_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_double and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_formattable_get_double_p(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    double value_to_set = 7;
    ret = i18n_formattable_set_double(formattable, value_to_set);
    assert_eq(ret, I18N_ERROR_NONE);

    double value;

    ret = i18n_formattable_get_double(formattable, &value);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(value, value_to_set);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_double_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_double passing invalid formattable and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_get_double_n(void)
{
    i18n_formattable_h formattable = NULL; // Invalid parameter

    double value;

    ret = i18n_formattable_get_double(formattable, &value);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_double_n2
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_double passing invalid pointer as a
 *              second parameter and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_get_double_n2(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    double value_to_set = 7;
    ret = i18n_formattable_set_double(formattable, value_to_set);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_formattable_get_double(formattable, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_date_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_date and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_formattable_get_date_p(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_udate d = 13.0;
    ret = i18n_formattable_set_date(formattable, d);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_udate date;

    ret = i18n_formattable_get_date(formattable, &date);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(date, d);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_date_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_date passing invalid formattable and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_get_date_n(void)
{
    i18n_formattable_h formattable = NULL; // Invalid parameter

    i18n_udate date;

    ret = i18n_formattable_get_date(formattable, &date);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_date_n2
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_date passing invalid date and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_get_date_n2(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_udate d = 13.0;
    ret = i18n_formattable_set_date(formattable, d);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_formattable_get_date(formattable, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_array_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_array and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_formattable_get_array_p(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int i;
    for (i = 0; i < count; ++i) {
        double value = i;
        ret = i18n_formattable_create_with_double(value, &array_to_set[i]);

        assert_neq(array_to_set[i], NULL);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    ret = i18n_formattable_set_array(formattable, array_to_set, count);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_formattable_h *ret_array;
    int32_t ret_count = 0;
    ret = i18n_formattable_get_array(formattable, &ret_array, &ret_count);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ret_array, NULL);

    if (ret_count != count) {
        free(ret_array);
        assert_eq(ret_count, count);
    }

    for (i = 0; i < ret_count; ++i) {
        bool equal = false;
        ret = i18n_formattable_equal(array_to_set[i], ret_array[i], &equal);

        if (ret != I18N_ERROR_NONE || !equal) {
            free(ret_array);

            assert_eq(ret, I18N_ERROR_NONE);
            assert_eq(equal, true);
        }
    }

    free(ret_array);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_array_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_array passing invalid formattable and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_get_array_n(void)
{
    i18n_formattable_h formattable = NULL; // Invalid parameter

    i18n_formattable_h *ret_array = NULL;

    int32_t ret_count = 0;

    ret = i18n_formattable_get_array(formattable, &ret_array, &ret_count);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_array_n2
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_array passing invalid array and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_get_array_n2(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int i;
    for (i = 0; i < count; ++i) {
        double value = i;
        ret = i18n_formattable_create_with_double(value, &array_to_set[i]);

        assert_neq(array_to_set[i], NULL);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    ret = i18n_formattable_set_array(formattable, array_to_set, count);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t ret_count = 0;

    ret = i18n_formattable_get_array(formattable, NULL, &ret_count);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_get_array_n3
 * @since_tizen 3.0
 * @description Calls i18n_formattable_get_array passing invalid count and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_get_array_n3(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int i;
    for (i = 0; i < count; ++i) {
        double value = i;
        ret = i18n_formattable_create_with_double(value, &array_to_set[i]);

        assert_neq(array_to_set[i], NULL);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    ret = i18n_formattable_set_array(formattable, array_to_set, count);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_formattable_h *ret_array = NULL;

    ret = i18n_formattable_get_array(formattable, &ret_array, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_clone_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_clone and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_formattable_clone_p(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_formattable_h clone = NULL;

    ret = i18n_formattable_clone(formattable, &clone);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(clone, NULL);

    bool equal = false;
    ret = i18n_formattable_equal(formattable, clone, &equal);

    i18n_formattable_destroy(clone);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(equal, true);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_clone_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_clone passing invalid formattable and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_clone_n(void)
{
    i18n_formattable_h formattable = NULL; // Invalid parameter

    i18n_formattable_h clone = NULL;

    ret = i18n_formattable_clone(formattable, &clone);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_clone_n2
 * @since_tizen 3.0
 * @description Calls i18n_formattable_clone passing invalid clone and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_clone_n2(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_formattable_clone(formattable, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_destroy_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_formattable_destroy_p(void)
{
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_formattable_destroy(formattable);

    assert_eq(ret, I18N_ERROR_NONE);
    formattable = NULL;

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_destroy_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_destroy passing invalid formattable and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_destroy_n(void)
{
    i18n_formattable_h formattable = NULL; // Invalid parameter

    ret = i18n_formattable_destroy(formattable);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_create_with_formattable_array_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_create_with_formattable_array and checks
 *              whether function succeeded.
 */
int utc_capi_base_utils_i18n_formattable_create_with_formattable_array_p(void)
{
    i18n_formattable_destroy(formattable);

    int32_t i;
    for (i = 0; i < count; ++i) {
        double value = i;
        ret = i18n_formattable_create_with_double(value, &array_to_set[i]);

        assert_neq(array_to_set[i], NULL);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    ret = i18n_formattable_create_with_formattable_array(array_to_set, count, &formattable);
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_formattable_h *ret_array;
    int32_t ret_count = 0;
    ret = i18n_formattable_get_array(formattable, &ret_array, &ret_count);
    assert_eq(ret, I18N_ERROR_NONE);

    if (ret_count != count) {
        free(ret_array);
        assert_eq(ret_count, count);
    }

    for (i = 0; i < ret_count; ++i) {
        bool equal = false;
        ret = i18n_formattable_equal(array_to_set[i], ret_array[i], &equal);

        if (ret != I18N_ERROR_NONE || !equal) {
            free(ret_array);

            assert_eq(ret, I18N_ERROR_NONE);
            assert_eq(equal, true);
        }
    }

    free(ret_array);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_create_with_formattable_array_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_create_with_formattable_array passing invalid
 *              array_to_copy and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_create_with_formattable_array_n(void)
{
    i18n_formattable_h formattable = NULL;

    ret = i18n_formattable_create_with_formattable_array(NULL, count, &formattable);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_create_with_formattable_array_n2
 * @since_tizen 3.0
 * @description Calls i18n_formattable_create_with_formattable_array passing invalid
 *              count and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_create_with_formattable_array_n2(void)
{
    int32_t i;
    for (i = 0; i < count; ++i) {
        array_to_set[i] = NULL;
        ret = i18n_formattable_create_default(&array_to_set[i]);

        assert_neq(array_to_set[i], NULL);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    int count_to_set = -1; // Invalid parameter

    i18n_formattable_h formattable = NULL;
    ret = i18n_formattable_create_with_formattable_array(array_to_set, count_to_set, &formattable);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_create_with_formattable_array_n3
 * @since_tizen 3.0
 * @description Calls i18n_formattable_create_with_formattable_array passing invalid
 *              formattable and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_create_with_formattable_array_n3(void)
{
    int32_t i;
    for (i = 0; i < count; ++i) {
        array_to_set[i] = NULL;
        ret = i18n_formattable_create_default(&array_to_set[i]);

        assert_neq(array_to_set[i], NULL);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    ret = i18n_formattable_create_with_formattable_array(array_to_set, count, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_create_with_char_string_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_create_with_char_string and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_formattable_create_with_char_string_p(void)
{
    i18n_formattable_destroy(formattable);

    const char *string_to_set = "Test string";

    ret = i18n_formattable_create_with_char_string(string_to_set, &formattable);

    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    char *set_string;
    i18n_formattable_get_string(formattable, &set_string);

    i18n_formattable_type_e type;
    i18n_formattable_get_type(formattable, &type);

    assert_eq(strncmp(set_string, string_to_set, strlen(string_to_set)), 0);
    assert_eq(type, I18N_FORMATTABLE_TYPE_STRING);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_create_with_char_string_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_create_with_char_string passing invalid
 *              formattable and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_create_with_char_string_n(void)
{
    const char *str_to_set = "Test string";

    ret = i18n_formattable_create_with_char_string(str_to_set, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_create_with_int64_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_create_with_int64 and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_formattable_create_with_int64_p(void)
{
    i18n_formattable_destroy(formattable);

    int64_t long_long_to_set = 13;

    ret = i18n_formattable_create_with_int64(long_long_to_set, &formattable);

    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int64_t set_long_long;
    i18n_formattable_get_int64(formattable, &set_long_long);

    i18n_formattable_type_e type;
    i18n_formattable_get_type(formattable, &type);

    assert_eq(set_long_long, long_long_to_set);
    assert_eq(type, I18N_FORMATTABLE_TYPE_INT64);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_create_with_int64_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_create_with_int64 passing invalid formattable
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_create_with_int64_n(void)
{

    int64_t long_long_to_set = 0;

    ret = i18n_formattable_create_with_int64(long_long_to_set, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_create_with_long_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_create_with_long and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_formattable_create_with_long_p(void)
{
    i18n_formattable_destroy(formattable);

    int32_t long_to_set = 13;

    ret = i18n_formattable_create_with_long(long_to_set, &formattable);

    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t set_long;
    i18n_formattable_get_long(formattable, &set_long);

    i18n_formattable_type_e type;
    i18n_formattable_get_type(formattable, &type);

    assert_eq(set_long, long_to_set);
    assert_eq(type, I18N_FORMATTABLE_TYPE_LONG);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_create_with_long_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_create_with_long passing invalid formattable
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_create_with_long_n(void)
{
    int32_t long_to_set = 0;

    ret = i18n_formattable_create_with_long(long_to_set, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_create_with_double_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_create_with_double and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_formattable_create_with_double_p(void)
{
    i18n_formattable_destroy(formattable);

    double double_to_set = 13.0;

    ret = i18n_formattable_create_with_double(double_to_set, &formattable);

    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    double set_double;
    i18n_formattable_get_double(formattable, &set_double);

    i18n_formattable_type_e type;
    i18n_formattable_get_type(formattable, &type);

    assert_eq(set_double, double_to_set);
    assert_eq(type, I18N_FORMATTABLE_TYPE_DOUBLE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_create_with_double_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_create_with_double passing invalid
 *              formattable and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_create_with_double_n(void)
{
    double double_to_set = 0.0;

    ret = i18n_formattable_create_with_double(double_to_set, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_create_with_udate_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_create_with_udate and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_formattable_create_with_udate_p(void)
{
    i18n_formattable_destroy(formattable);

    i18n_udate date_to_set = 13.0;

    ret = i18n_formattable_create_with_udate(date_to_set, &formattable);

    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_udate set_date;
    i18n_formattable_get_date(formattable, &set_date);

    i18n_formattable_type_e type;
    i18n_formattable_get_type(formattable, &type);

    assert_eq(set_date, date_to_set);
    assert_eq(type, I18N_FORMATTABLE_TYPE_DATE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_create_with_udate_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_create_with_udate passing invalid formattable
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_create_with_udate_n(void)
{
    i18n_udate date_to_set = 0.0;

    ret = i18n_formattable_create_with_udate(date_to_set, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_create_default_p
 * @since_tizen 3.0
 * @description Calls i18n_formattable_create_default and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_formattable_create_default_p(void)
{
    i18n_formattable_destroy(formattable);

    ret = i18n_formattable_create_default(&formattable);

    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_formattable_create_default_n
 * @since_tizen 3.0
 * @description Calls i18n_formattable_create_default passing invalid formattable
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_formattable_create_default_n(void)
{
    ret = i18n_formattable_create_default(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

