#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

static i18n_measure_h measure = NULL;
static i18n_formattable_h formattable = NULL;
static i18n_measure_unit_h measure_unit = NULL;
static char *ref_type;

static i18n_measure_h measure_clone = NULL;
static i18n_formattable_h formattable_clone = NULL;
static i18n_measure_unit_h measure_unit_clone = NULL;
static char *type = NULL;

static int ret = I18N_ERROR_NONE;

/**
 * @function        utc_capi_base_utils_measure_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_measure_startup(void)
{
    int32_t value = 7;
    ret = i18n_formattable_create_with_long(value, &formattable);
    if (ret != I18N_ERROR_NONE) return;

    ret = i18n_measure_unit_create_gigabit(&measure_unit);
    if (ret != I18N_ERROR_NONE) return;

    ret = i18n_measure_create(formattable, measure_unit, &measure);
}

/**
 * @function        utc_capi_base_utils_measure_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_measure_cleanup(void)
{
    if (measure != NULL) {
        i18n_measure_destroy(measure);
        measure = NULL;

        measure_unit = NULL;
        formattable = NULL;
    }

    if (measure_unit != NULL) {
        i18n_measure_unit_destroy(measure_unit);
        measure_unit = NULL;
    }

    if (formattable != NULL) {
        i18n_formattable_destroy(formattable);
        formattable = NULL;
    }

    if (ref_type != NULL) {
        free(ref_type);
        ref_type = NULL;
    }

    if (measure_clone != NULL) {
        i18n_measure_destroy(measure_clone);
        measure_clone = NULL;

        measure_unit_clone = NULL;
        formattable_clone = NULL;
    }

    if (measure_unit_clone != NULL) {
        i18n_measure_unit_destroy(measure_unit_clone);
        measure_unit_clone = NULL;
    }

    if (formattable_clone != NULL) {
        i18n_formattable_destroy(formattable_clone);
        formattable_clone = NULL;
    }

    if (type != NULL) {
        free(type);
        type = NULL;
    }
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_get_unit_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_get_unit and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_get_unit_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure, NULL);

    ret = i18n_measure_get_unit(measure, &measure_unit_clone);
    assert_neq(measure_unit_clone, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit_clone, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &ref_type);
    assert_eq(ret, I18N_ERROR_NONE);

    assert_eq(strncmp(type, ref_type, strlen(ref_type)), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_get_unit_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_get_unit passing invalid measure and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_get_unit_n(void)
{
    i18n_measure_unit_h mu = NULL;

    ret = i18n_measure_get_unit(NULL, &mu);

    assert_eq(mu, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_get_unit_n2
 * @since_tizen 3.0
 * @description Calls i18n_measure_get_unit passing invalid measure_unit and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_get_unit_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure, NULL);

    ret = i18n_measure_get_unit(measure, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_get_number_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_get_number and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_get_number_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure, NULL);
    assert_eq(formattable_clone, NULL);

    ret = i18n_measure_get_number(measure, &formattable_clone);
    assert_neq(formattable_clone, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    bool equal = false;
    ret = i18n_formattable_equal(formattable_clone, formattable, &equal);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(equal, true);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_get_number_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_get_number passing invalid measure and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_get_number_n(void)
{
    i18n_formattable_h f = NULL;

    ret = i18n_measure_get_number(NULL, &f);

    assert_eq(f, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_get_number_n2
 * @since_tizen 3.0
 * @description Calls i18n_measure_get_number passing invalid formattable and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_get_number_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure, NULL);

    ret = i18n_measure_get_number(measure, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_destroy_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_destroy_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure, NULL);

    ret = i18n_measure_destroy(measure);
    assert_eq(ret, I18N_ERROR_NONE);

    measure_unit = NULL;
    formattable = NULL;
    measure = NULL;

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_destroy_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_destroy passing invalid measure and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_destroy_n(void)
{
    ret = i18n_measure_destroy(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_clone_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_clone and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_clone_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure, NULL);
    assert_eq(measure_clone, NULL);

    ret = i18n_measure_clone(measure, &measure_clone);
    assert_neq(measure_clone, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    assert_eq(measure_unit_clone, NULL);
    ret = i18n_measure_get_unit(measure_clone, &measure_unit_clone);
    assert_neq(measure_unit_clone, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    assert_eq(formattable_clone, NULL);
    ret = i18n_measure_get_number(measure_clone, &formattable_clone);
    assert_neq(formattable_clone, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit_clone, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &ref_type);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strncmp(type, ref_type, strlen(ref_type)), 0);

    bool equal = false;
    ret = i18n_formattable_equal(formattable_clone, formattable, &equal);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(equal, true);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_clone_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_clone passing invalid measure and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_clone_n(void)
{
    i18n_measure_h clone = NULL;

    ret = i18n_measure_clone(NULL, &clone);

    assert_eq(clone, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_clone_n2
 * @since_tizen 3.0
 * @description Calls i18n_measure_clone passing invalid clone and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_clone_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure, NULL);

    ret = i18n_measure_clone(measure, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_create_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_create_p(void)
{
    utc_capi_base_utils_measure_cleanup();

    ret = i18n_measure_unit_create(&measure_unit);
    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_formattable_create_default(&formattable);
    assert_neq(formattable, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_create(formattable, measure_unit, &measure);
    assert_neq(measure, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_create_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_create passing invalid measure and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_create_n(void)
{
    assert_neq(formattable, NULL);
    assert_neq(measure_unit, NULL);

    ret = i18n_measure_create(NULL, formattable, measure_unit);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
