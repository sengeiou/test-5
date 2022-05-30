#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

static i18n_field_position_h field_position = NULL;
static int ret = I18N_ERROR_NONE;

/**
 * @function        utc_capi_base_utils_field_position_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_field_position_startup(void)
{
    ret = i18n_field_position_create(&field_position);
}

/**
 * @function        utc_capi_base_utils_field_position_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_field_position_cleanup(void)
{
    if (field_position != NULL) {
        i18n_field_position_destroy(field_position);
        field_position = NULL;
    }
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_set_end_index_p
 * @since_tizen 3.0
 * @description Calls i18n_field_position_set_end_index and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_field_position_set_end_index_p(void)
{
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t end_index = 13;

    ret = i18n_field_position_set_end_index(field_position, end_index);

    assert_eq(ret, I18N_ERROR_NONE);

    int32_t ret_end_index;
    ret = i18n_field_position_get_end_index(field_position, &ret_end_index);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(ret_end_index, end_index);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_set_end_index_n
 * @since_tizen 3.0
 * @description Calls i18n_field_position_set_end_index passing invalid
 *              field_position and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_field_position_set_end_index_n(void)
{
    int32_t end_index = 13;

    ret = i18n_field_position_set_end_index(NULL, end_index);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_set_begin_index_p
 * @since_tizen 3.0
 * @description Calls i18n_field_position_set_begin_index and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_field_position_set_begin_index_p(void)
{
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t begin_index = 10;

    ret = i18n_field_position_set_begin_index(field_position, begin_index);

    assert_eq(ret, I18N_ERROR_NONE);

    int32_t ret_begin_index;
    ret = i18n_field_position_get_begin_index(field_position, &ret_begin_index);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(ret_begin_index, begin_index);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_set_begin_index_n
 * @since_tizen 3.0
 * @description Calls i18n_field_position_set_begin_index passing invalid
 *              field_position and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_field_position_set_begin_index_n(void)
{
    int32_t begin_index = 10;

    ret = i18n_field_position_set_begin_index(NULL, begin_index);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_set_field_p
 * @since_tizen 3.0
 * @description Calls i18n_field_position_set_field and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_field_position_set_field_p(void)
{
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t field = 13;

    ret = i18n_field_position_set_field(field_position, field);

    assert_eq(ret, I18N_ERROR_NONE);

    int32_t ret_field;

    ret = i18n_field_position_get_field(field_position, &ret_field);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(ret_field, field);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_set_field_n
 * @since_tizen 3.0
 * @description Calls i18n_field_position_set_field passing invalid field_position
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_field_position_set_field_n(void)
{
    int32_t field = 0;

    ret = i18n_field_position_set_field(NULL, field);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_get_end_index_p
 * @since_tizen 3.0
 * @description Calls i18n_field_position_get_end_index and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_field_position_get_end_index_p(void)
{
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t end_index_to_set = 13;

    ret = i18n_field_position_set_end_index(field_position, end_index_to_set);

    assert_eq(ret, I18N_ERROR_NONE);

    int32_t end_index;

    ret = i18n_field_position_get_end_index(field_position, &end_index);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(end_index, end_index_to_set);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_get_end_index_n
 * @since_tizen 3.0
 * @description Calls i18n_field_position_get_end_index passing invalid
 *              field_position and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_field_position_get_end_index_n(void)
{
    i18n_field_position_h field_position = NULL; // Invalid parameter

    int32_t end_index;

    ret = i18n_field_position_get_end_index(field_position, &end_index);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_get_end_index_n2
 * @since_tizen 3.0
 * @description Calls i18n_field_position_get_end_index passing invalid end_index
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_field_position_get_end_index_n2(void)
{
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_field_position_get_end_index(field_position, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_get_begin_index_p
 * @since_tizen 3.0
 * @description Calls i18n_field_position_get_begin_index and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_field_position_get_begin_index_p(void)
{
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t begin_index_to_set = 13;

    ret = i18n_field_position_set_begin_index(field_position, begin_index_to_set);

    assert_eq(ret, I18N_ERROR_NONE);

    int32_t begin_index = 0;

    ret = i18n_field_position_get_begin_index(field_position, &begin_index);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(begin_index, begin_index_to_set);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_get_begin_index_n
 * @since_tizen 3.0
 * @description Calls i18n_field_position_get_begin_index passing invalid
 *              field_position and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_field_position_get_begin_index_n(void)
{
    i18n_field_position_h field_position = NULL; // Invalid parameter

    int32_t begin_index;

    ret = i18n_field_position_get_begin_index(field_position, &begin_index);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_get_begin_index_n2
 * @since_tizen 3.0
 * @description Calls i18n_field_position_get_begin_index passing invalid
 *              begin_index and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_field_position_get_begin_index_n2(void)
{
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_field_position_get_begin_index(field_position, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_get_field_p
 * @since_tizen 3.0
 * @description Calls i18n_field_position_get_field and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_field_position_get_field_p(void)
{
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t field_to_set = 13;

    ret = i18n_field_position_set_field(field_position, field_to_set);

    assert_eq(ret, I18N_ERROR_NONE);

    int32_t field = 0;

    ret = i18n_field_position_get_field(field_position, &field);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(field_to_set, field);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_get_field_n
 * @since_tizen 3.0
 * @description Calls i18n_field_position_get_field passing invalid field_position
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_field_position_get_field_n(void)
{
    i18n_field_position_h field_position = NULL; // Invalid parameter

    int32_t field = 0;

    ret = i18n_field_position_get_field(field_position, &field);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_get_field_n2
 * @since_tizen 3.0
 * @description Calls i18n_field_position_get_field passing invalid field and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_field_position_get_field_n2(void)
{
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_field_position_get_field(field_position, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_clone_p
 * @since_tizen 3.0
 * @description Calls i18n_field_position_clone and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_field_position_clone_p(void)
{
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_field_position_h clone = NULL;

    int32_t begin_index = 10;
    ret = i18n_field_position_set_begin_index(field_position, begin_index);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t field = 12;
    ret = i18n_field_position_set_field(field_position, field);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t end_index = 15;
    ret = i18n_field_position_set_end_index(field_position, end_index);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_field_position_clone(field_position, &clone);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(clone, NULL);

    int32_t ret_begin_index = -1;
    ret = i18n_field_position_get_begin_index(clone, &ret_begin_index);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t ret_field = -1;
    ret = i18n_field_position_get_field(clone, &ret_field);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t ret_end_index = -1;
    ret = i18n_field_position_get_end_index(clone, &ret_end_index);
    assert_eq(ret, I18N_ERROR_NONE);

    assert_eq(ret_begin_index, begin_index);
    assert_eq(ret_field, field);
    assert_eq(ret_end_index, end_index);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_clone_n
 * @since_tizen 3.0
 * @description Calls i18n_field_position_clone passing invalid field_position and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_field_position_clone_n(void)
{
    i18n_field_position_h field_position = NULL; // Invalid parameter

    i18n_field_position_h clone = NULL;

    ret = i18n_field_position_clone(field_position, &clone);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_clone_n2
 * @since_tizen 3.0
 * @description Calls i18n_field_position_clone passing invalid clone and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_field_position_clone_n2(void)
{
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_field_position_clone(field_position, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_destroy_p
 * @since_tizen 3.0
 * @description Calls i18n_field_position_destroy and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_field_position_destroy_p(void)
{
    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_field_position_destroy(field_position);
    assert_eq(ret, I18N_ERROR_NONE);
    field_position = NULL;

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_destroy_n
 * @since_tizen 3.0
 * @description Calls i18n_field_position_destroy passing invalid field_position and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_field_position_destroy_n(void)
{
    i18n_field_position_h field_position = NULL; // Invalid parameter

    ret = i18n_field_position_destroy(field_position);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_create_for_field_p
 * @since_tizen 3.0
 * @description Calls i18n_field_position_create_for_field and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_field_position_create_for_field_p(void)
{
    i18n_field_position_h field_position = NULL;

    int32_t field = 13;

    ret = i18n_field_position_create_for_field(field, &field_position);

    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t ret_field = -1;

    ret = i18n_field_position_get_field(field_position, &ret_field);

    i18n_field_position_destroy(field_position);
    field_position = NULL;

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(ret_field, field);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_create_for_field_n
 * @since_tizen 3.0
 * @description Calls i18n_field_position_create_for_field passing invalid
 *              field_position and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_field_position_create_for_field_n(void)
{
    int32_t field = 0;

    ret = i18n_field_position_create_for_field(field, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_create_p
 * @since_tizen 3.0
 * @description Calls i18n_field_position_create and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_field_position_create_p(void)
{
    i18n_field_position_h field_position = NULL;

    ret = i18n_field_position_create(&field_position);

    assert_neq(field_position, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_field_position_destroy(field_position);
    field_position = NULL;

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_field_position_create_n
 * @since_tizen 3.0
 * @description Calls i18n_field_position_create passing invalid field_position and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_field_position_create_n(void)
{
    ret = i18n_field_position_create(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

