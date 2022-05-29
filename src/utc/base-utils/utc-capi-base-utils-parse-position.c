#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

static int ret = I18N_ERROR_NONE;
static i18n_parse_position_h parse_position = NULL;
static i18n_parse_position_h clone = NULL;

/**
 * @function        utc_capi_base_utils_parse_position_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_parse_position_startup(void)
{
    ret = i18n_parse_position_create(&parse_position);
}

/**
 * @function        utc_capi_base_utils_parse_position_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_parse_position_cleanup(void)
{
    if(parse_position != NULL) {
        i18n_parse_position_destroy(parse_position);
        parse_position = NULL;
    }

    if(clone != NULL) {
        i18n_parse_position_destroy(clone);
        clone = NULL;
    }
}

/**
 * @testcase utc_capi_base_utils_i18n_parse_position_get_error_index_p
 * @since_tizen 3.0
 * @description Calls i18n_parse_position_get_error_index and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_parse_position_get_error_index_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(parse_position, NULL);

    int32_t error_index_to_set = 13;
    ret = i18n_parse_position_set_error_index(parse_position, error_index_to_set);
    assert_eq(ret, I18N_ERROR_NONE);


    int32_t set_error_index = -1;
    ret = i18n_parse_position_get_error_index(parse_position, &set_error_index);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(set_error_index, error_index_to_set);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_parse_position_get_error_index_n
 * @since_tizen 3.0
 * @description Calls i18n_parse_position_get_error_index passing invalid
 *              parse_position and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_parse_position_get_error_index_n(void)
{
    i18n_parse_position_h local_parse_position = NULL; // Invalid parameter

    int32_t error_index = -1;

    ret = i18n_parse_position_get_error_index(local_parse_position, &error_index);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_parse_position_get_error_index_n2
 * @since_tizen 3.0
 * @description Calls i18n_parse_position_get_error_index passing invalid
 *              error_index and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_parse_position_get_error_index_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(parse_position, NULL);

    ret = i18n_parse_position_get_error_index(parse_position, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_parse_position_set_error_index_p
 * @since_tizen 3.0
 * @description Calls i18n_parse_position_set_error_index and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_parse_position_set_error_index_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(parse_position, NULL);

    int32_t error_index_to_set = 13;

    ret = i18n_parse_position_set_error_index(parse_position, error_index_to_set);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t set_error_index = -1;

    ret = i18n_parse_position_get_error_index(parse_position, &set_error_index);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(set_error_index, error_index_to_set);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_parse_position_set_error_index_n
 * @since_tizen 3.0
 * @description Calls i18n_parse_position_set_error_index passing invalid
 *              parse_position and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_parse_position_set_error_index_n(void)
{
    int32_t error_index = 13;

    ret = i18n_parse_position_set_error_index(NULL, error_index);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_parse_position_set_index_p
 * @since_tizen 3.0
 * @description Calls i18n_parse_position_set_index and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_parse_position_set_index_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(parse_position, NULL);

    int32_t index_to_set = 13;

    ret = i18n_parse_position_set_index(parse_position, index_to_set);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t set_index = -1;
    ret = i18n_parse_position_get_index(parse_position, &set_index);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(set_index, index_to_set);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_parse_position_set_index_n
 * @since_tizen 3.0
 * @description Calls i18n_parse_position_set_index passing invalid parse_position
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_parse_position_set_index_n(void)
{
    int32_t index = 13;

    ret = i18n_parse_position_set_index(NULL, index);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_parse_position_get_index_p
 * @since_tizen 3.0
 * @description Calls i18n_parse_position_get_index and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_parse_position_get_index_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(parse_position, NULL);

    int32_t index_to_set = 13;
    ret = i18n_parse_position_set_index(parse_position, index_to_set);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t set_index = -1;
    ret = i18n_parse_position_get_index(parse_position, &set_index);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(set_index, index_to_set);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_parse_position_get_index_n
 * @since_tizen 3.0
 * @description Calls i18n_parse_position_get_index passing invalid parse_position
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_parse_position_get_index_n(void)
{
    i18n_parse_position_h local_parse_position = NULL; // Invalid parameter

    int32_t index = -1;
    ret = i18n_parse_position_get_index(local_parse_position, &index);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_parse_position_get_index_n2
 * @since_tizen 3.0
 * @description Calls i18n_parse_position_get_index passing invalid index and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_parse_position_get_index_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(parse_position, NULL);

    ret = i18n_parse_position_get_index(parse_position, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_parse_position_clone_p
 * @since_tizen 3.0
 * @description Calls i18n_parse_position_clone and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_parse_position_clone_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(parse_position, NULL);

    int32_t error_index = 7;
    ret = i18n_parse_position_set_error_index(parse_position, error_index);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t index = 13;
    ret = i18n_parse_position_set_index(parse_position, index);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_parse_position_clone(parse_position, &clone);

    assert_neq(clone, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t ret_error_index = -2;
    ret = i18n_parse_position_get_error_index(clone, &ret_error_index);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t ret_index = -2;
    ret = i18n_parse_position_get_index(clone, &ret_index);
    assert_eq(ret, I18N_ERROR_NONE);

    assert_eq(ret_error_index, error_index);
    assert_eq(ret_index, index);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_parse_position_clone_n
 * @since_tizen 3.0
 * @description Calls i18n_parse_position_clone passing invalid parse_position and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_parse_position_clone_n(void)
{
    i18n_parse_position_h local_parse_position = NULL; // Invalid parameter

    i18n_parse_position_h clone = NULL;

    ret = i18n_parse_position_clone(local_parse_position, &clone);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_parse_position_clone_n2
 * @since_tizen 3.0
 * @description Calls i18n_parse_position_clone passing invalid clone and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_parse_position_clone_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(parse_position, NULL);

    ret = i18n_parse_position_clone(parse_position, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_parse_position_destroy_p
 * @since_tizen 3.0
 * @description Calls i18n_parse_position_destroy and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_parse_position_destroy_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(parse_position, NULL);

    ret = i18n_parse_position_destroy(parse_position);
    assert_eq(ret, I18N_ERROR_NONE);
    parse_position = NULL;

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_parse_position_destroy_n
 * @since_tizen 3.0
 * @description Calls i18n_parse_position_destroy passing invalid parse_position and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_parse_position_destroy_n(void)
{
    i18n_parse_position_h local_parse_position = NULL; // Invalid parameter

    ret = i18n_parse_position_destroy(local_parse_position);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_parse_position_create_with_index_p
 * @since_tizen 3.0
 * @description Calls i18n_parse_position_create_with_index and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_parse_position_create_with_index_p(void)
{
    i18n_parse_position_h local_parse_position = NULL;

    int32_t new_index = 13;

    ret = i18n_parse_position_create_with_index(new_index, &local_parse_position);

    assert_neq(local_parse_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t ret_index;
    ret = i18n_parse_position_get_index(local_parse_position, &ret_index);

    i18n_parse_position_destroy(local_parse_position);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(ret_index, new_index);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_parse_position_create_with_index_n
 * @since_tizen 3.0
 * @description Calls i18n_parse_position_create_with_index passing invalid
 *              parse_position and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_parse_position_create_with_index_n(void)
{
    int32_t new_index = 13;

    ret = i18n_parse_position_create_with_index(new_index, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_parse_position_create_p
 * @since_tizen 3.0
 * @description Calls i18n_parse_position_create and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_parse_position_create_p(void)
{
    i18n_parse_position_h local_parse_position = NULL;

    ret = i18n_parse_position_create(&local_parse_position);

    assert_neq(parse_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_parse_position_destroy(local_parse_position);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_parse_position_create_n
 * @since_tizen 3.0
 * @description Calls i18n_parse_position_create passing invalid parse_position and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_parse_position_create_n(void)
{
    ret = i18n_parse_position_create(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

