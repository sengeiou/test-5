#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

static int ret = I18N_ERROR_NONE;
static i18n_date_interval_h interval = NULL;
static i18n_udate from_date = 1000000000.0;
static i18n_udate to_date = 1500000000.0;


/**
 * @function        utc_capi_base_utils_date_interval_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_date_interval_startup(void)
{
    ret = i18n_date_interval_create(from_date, to_date, &interval);
}

/**
 * @function        utc_capi_base_utils_date_interval_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_date_interval_cleanup(void)
{
   if (interval) {
       ret = i18n_date_interval_destroy(interval);
       interval = NULL;
   }
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_create_p
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_date_interval_create_p(void)
{
    utc_capi_base_utils_date_interval_cleanup();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(interval, NULL);

    ret = i18n_date_interval_create(from_date, to_date, &interval);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(interval, NULL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_create_n
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_create passing invalid interval
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_create_n(void)
{
    ret = i18n_date_interval_create(from_date, to_date, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_destroy_p
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_date_interval_destroy_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(interval, NULL);

    ret = i18n_date_interval_destroy(interval);
    assert_eq(ret, I18N_ERROR_NONE);
    interval = NULL;

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_destroy_n
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_destroy() passing invalid interval
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_destroy_n(void)
{
    ret = i18n_date_interval_destroy(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_clone_p
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_clone and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_date_interval_clone_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(interval, NULL);

    i18n_date_interval_h clone = NULL;

    ret = i18n_date_interval_clone(interval, &clone);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(clone, NULL);

    i18n_date_interval_destroy(clone);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_clone_n
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_clone passing invalid interval
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_clone_n(void)
{
    i18n_date_interval_h clone = NULL;

    ret = i18n_date_interval_clone(NULL, &clone);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_clone_n2
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_clone passing invalid clone
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_clone_n2(void)
{
    ret = i18n_date_interval_clone(interval, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_get_from_date_p
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_get_from_date and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_date_interval_get_from_date_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(interval, NULL);

    double output = 0.0;

    ret = i18n_date_interval_get_from_date(interval, &output);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(output, from_date);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_get_from_date_n
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_get_from_date passing invalid interval
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_get_from_date_n(void)
{
    double output = 0.0;

    ret = i18n_date_interval_get_from_date(NULL, &output);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_get_from_date_n2
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_get_from_date passing invalid from_date
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_get_from_date_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(interval, NULL);

    ret = i18n_date_interval_get_from_date(interval, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_get_to_date_p
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_get_to_date and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_date_interval_get_to_date_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(interval, NULL);

    double output = 0.0;

    ret = i18n_date_interval_get_to_date(interval, &output);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(output, to_date);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_get_to_date_n
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_get_to_date passing invalid interval
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_get_to_date_n(void)
{
    double output = 0.0;

    ret = i18n_date_interval_get_to_date(NULL, &output);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_get_to_date_n2
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_get_to_date passing invalid to_date
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_get_to_date_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(interval, NULL);

    ret = i18n_date_interval_get_to_date(interval, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_equals_p
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_equals and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_date_interval_equals_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(interval, NULL);

    i18n_ubool is_equal = false;

    i18n_date_interval_equals(interval, interval, &is_equal);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_equal, true);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_equals_p2
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_equals and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_date_interval_equals_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(interval, NULL);

    i18n_ubool is_equal = true;
    i18n_date_interval_h second_interval = NULL;
    ret = i18n_date_interval_create(from_date + 10.0, to_date + 20.0, &second_interval);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(second_interval, NULL);

    i18n_date_interval_equals(interval, second_interval, &is_equal);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_equal, false);

    i18n_date_interval_destroy(second_interval);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_equals_n
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_equals passing invalid first date interval
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_equals_n(void)
{
    i18n_ubool is_equal = false;

    ret = i18n_date_interval_equals(NULL, interval, &is_equal);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_equals_n2
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_equals passing invalid second date interval
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_equals_n2(void)
{
    i18n_ubool is_equal = false;

    ret = i18n_date_interval_equals(interval, NULL, &is_equal);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_date_interval_equals_n3
 * @since_tizen 5.0
 * @description Calls i18n_date_interval_equals passing invalid equals
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_date_interval_equals_n3(void)
{
    ret = i18n_date_interval_equals(interval, interval, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
