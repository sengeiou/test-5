#include "assert.h"
#include <utils_i18n.h>
#include <string.h>
#include <dlog.h>

#define STARTUP_ERROR(error, message) {\
    if(error != I18N_ERROR_NONE) \
    {\
        fprintf(stderr, message); \
        return; \
    }\
}

static int ret = I18N_ERROR_NONE;
static i18n_alpha_idx_h alpha_idx = NULL;
static int record_data = 7;
static const char *locale_id = "en_US";

/**
 * @function        utc_capi_base_utils_alpha_idx_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_alpha_idx_startup(void)
{
    record_data = 7;

    ret = i18n_alpha_idx_create_from_locale_id(locale_id, &alpha_idx);
    STARTUP_ERROR(ret, "alpha_idx_create() failed in startup.\n");
    ret = i18n_alpha_idx_add_labels_with_locale_id(alpha_idx, locale_id);
    STARTUP_ERROR(ret, "alpha_idx_add_labels() failed in startup.\n");

    bool available;
    ret = i18n_alpha_idx_add_record(alpha_idx, "AAA", &record_data);
    STARTUP_ERROR(ret, "alpha_idx_add_record() failed in startup.\n");

    ret = i18n_alpha_idx_get_next_bucket(alpha_idx, &available);
    STARTUP_ERROR(ret, "alpha_idx_get_next_bucket() failed in startup.\n");
    ret = i18n_alpha_idx_get_next_bucket(alpha_idx, &available);
    STARTUP_ERROR(ret, "alpha_idx_get_next_bucket() failed in startup.\n");
    ret = i18n_alpha_idx_get_next_record(alpha_idx, &available);
    STARTUP_ERROR(ret, "alpha_idx_get_next_record() failed in startup.\n");
}

/**
 * @function        utc_capi_base_utils_alpha_idx_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_alpha_idx_cleanup(void)
{
    if (alpha_idx != NULL) {
        i18n_alpha_idx_destroy(alpha_idx);
    }
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_reset_record_iter_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_reset_record_iter and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_reset_record_iter_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    ret = i18n_alpha_idx_reset_record_iter(alpha_idx);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_reset_record_iter_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_reset_record_iter passing invalid index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_reset_record_iter_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    ret = i18n_alpha_idx_reset_record_iter(index);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_reset_bucket_iter_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_reset_bucket_iter and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_reset_bucket_iter_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    ret = i18n_alpha_idx_reset_bucket_iter(alpha_idx);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_reset_bucket_iter_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_reset_bucket_iter passing invalid index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_reset_bucket_iter_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    ret = i18n_alpha_idx_reset_bucket_iter(index);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_record_name_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_record_name and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_record_name_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    char *record_name = NULL;

    ret = i18n_alpha_idx_get_record_name(alpha_idx, &record_name);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(record_name, NULL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_record_name_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_record_name passing invalid index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_record_name_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    char *record_name = NULL;

    ret = i18n_alpha_idx_get_record_name(index, &record_name);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_record_name_n2
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_record_name passing invalid record_name and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_record_name_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    char **record_name = NULL; // Invalid parameter

    ret = i18n_alpha_idx_get_record_name(alpha_idx, record_name);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_bucket_label_type_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_bucket_label_type and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_bucket_label_type_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    i18n_alpha_idx_label_type_e type;

    ret = i18n_alpha_idx_get_bucket_label_type(alpha_idx, &type);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_bucket_label_type_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_bucket_label_type passing invalid index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_bucket_label_type_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    i18n_alpha_idx_label_type_e type;

    ret = i18n_alpha_idx_get_bucket_label_type(index, &type);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_bucket_label_type_n2
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_bucket_label_type passing invalid type and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_bucket_label_type_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    ret = i18n_alpha_idx_get_bucket_label_type(alpha_idx, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_current_bucket_index_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_current_bucket_index and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_current_bucket_index_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    int32_t bucket_index = -1;

    ret = i18n_alpha_idx_get_current_bucket_index(alpha_idx, &bucket_index);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_current_bucket_index_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_current_bucket_index passing invalid index
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_current_bucket_index_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    int32_t bucket_index = -1;

    ret = i18n_alpha_idx_get_current_bucket_index(index, &bucket_index);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_current_bucket_index_n2
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_current_bucket_index passing invalid
 *              bucket_index and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_current_bucket_index_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    ret = i18n_alpha_idx_get_current_bucket_index(alpha_idx, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_bucket_index_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_bucket_index and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_bucket_index_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    const char *item_name = "Test string";
    int32_t bucket_index = -1;

    ret = i18n_alpha_idx_get_bucket_index(alpha_idx, item_name, &bucket_index);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_bucket_index_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_bucket_index passing invalid index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_bucket_index_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    const char *item_name = "Test string";

    int32_t bucket_index = -1;

    ret = i18n_alpha_idx_get_bucket_index(index, item_name, &bucket_index);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_bucket_index_n2
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_bucket_index passing invalid item_name and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_bucket_index_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    const char *item_name = NULL; // Invalid parameter

    int32_t bucket_index = -1;

    ret = i18n_alpha_idx_get_bucket_index(alpha_idx, item_name, &bucket_index);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_bucket_index_n3
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_bucket_index passing invalid bucket_index
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_bucket_index_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    const char *item_name = "Test string";

    ret = i18n_alpha_idx_get_bucket_index(alpha_idx, item_name, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_record_count_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_record_count and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_record_count_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    int32_t record_count = -1;

    ret = i18n_alpha_idx_get_record_count(alpha_idx, &record_count);

    assert_eq(record_count, 1);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_record_count_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_record_count passing invalid index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_record_count_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    int32_t record_count = -1;

    ret = i18n_alpha_idx_get_record_count(index, &record_count);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_record_count_n2
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_record_count passing invalid record_count
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_record_count_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    ret = i18n_alpha_idx_get_record_count(alpha_idx, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_bucket_count_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_bucket_count and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_bucket_count_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    int32_t bucket_count = -1;

    ret = i18n_alpha_idx_get_bucket_count(alpha_idx, &bucket_count);

    assert_eq(bucket_count, 28);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_bucket_count_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_bucket_count passing invalid index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_bucket_count_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    int32_t bucket_count = -1;

    ret = i18n_alpha_idx_get_bucket_count(index, &bucket_count);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_bucket_count_n2
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_bucket_count passing invalid bucket_count
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_bucket_count_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    ret = i18n_alpha_idx_get_bucket_count(alpha_idx, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_clear_records_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_clear_records and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_clear_records_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    ret = i18n_alpha_idx_clear_records(alpha_idx);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t record_count = -1;
    ret = i18n_alpha_idx_get_record_count(alpha_idx, &record_count);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(record_count, 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_clear_records_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_clear_records passing invalid index and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_clear_records_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    ret = i18n_alpha_idx_clear_records(index);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_set_max_label_count_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_set_max_label_count and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_set_max_label_count_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    int32_t max_label_count = 10;

    ret = i18n_alpha_idx_set_max_label_count(alpha_idx, max_label_count);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_set_max_label_count_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_set_max_label_count passing invalid index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_set_max_label_count_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    int32_t max_label_count = 0;

    ret = i18n_alpha_idx_set_max_label_count(index, max_label_count);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_set_max_label_count_n2
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_set_max_label_count passing invalid
 *              max_label_count and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_set_max_label_count_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    int32_t max_label_count = -1; // Invalid parameter

    ret = i18n_alpha_idx_set_max_label_count(alpha_idx, max_label_count);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_max_label_count_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_max_label_count and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_max_label_count_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    int32_t max_label_count_to_set = 10;
    ret = i18n_alpha_idx_set_max_label_count(alpha_idx, max_label_count_to_set);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t max_label_count = 0;

    ret = i18n_alpha_idx_get_max_label_count(alpha_idx, &max_label_count);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(max_label_count, max_label_count_to_set);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_max_label_count_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_max_label_count passing invalid index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_max_label_count_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    int32_t max_label_count = 1;

    ret = i18n_alpha_idx_get_max_label_count(index, &max_label_count);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_max_label_count_n2
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_max_label_count passing invalid
 *              max_label_count and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_max_label_count_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    ret = i18n_alpha_idx_get_max_label_count(alpha_idx, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_set_underflow_label_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_set_underflow_label and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_set_underflow_label_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    const char *label = "Test string";

    ret = i18n_alpha_idx_set_underflow_label(alpha_idx, label);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_set_underflow_label_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_set_underflow_label passing invalid index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_set_underflow_label_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    const char *label = "Test string";

    ret = i18n_alpha_idx_set_underflow_label(index, label);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_set_underflow_label_n2
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_set_underflow_label passing invalid label and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_set_underflow_label_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    const char *label = NULL; // Invalid parameter

    ret = i18n_alpha_idx_set_underflow_label(alpha_idx, label);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_underflow_label_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_underflow_label and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_underflow_label_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    char *label = NULL;

    ret = i18n_alpha_idx_get_underflow_label(alpha_idx, &label);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(label, NULL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_underflow_label_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_underflow_label passing invalid index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_underflow_label_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    char *label = NULL;

    ret = i18n_alpha_idx_get_underflow_label(index, &label);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_underflow_label_n2
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_underflow_label passing invalid label and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_underflow_label_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    char **label = NULL; // Invalid parameter

    ret = i18n_alpha_idx_get_underflow_label(alpha_idx, label);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_set_overflow_label_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_set_overflow_label and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_set_overflow_label_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    const char *label = "Test string";

    ret = i18n_alpha_idx_set_overflow_label(alpha_idx, label);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_set_overflow_label_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_set_overflow_label passing invalid index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_set_overflow_label_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    const char *label = "Test string";

    ret = i18n_alpha_idx_set_overflow_label(index, label);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_set_overflow_label_n2
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_set_overflow_label passing invalid label and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_set_overflow_label_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    char *label = NULL; // Invalid parameter

    ret = i18n_alpha_idx_set_overflow_label(alpha_idx, label);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_overflow_label_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_overflow_label and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_overflow_label_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    char *label = NULL;

    ret = i18n_alpha_idx_get_overflow_label(alpha_idx, &label);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(label, NULL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_overflow_label_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_overflow_label passing invalid index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_overflow_label_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    char *label = NULL;

    ret = i18n_alpha_idx_get_overflow_label(index, &label);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_overflow_label_n2
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_overflow_label passing invalid label and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_overflow_label_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    char **label = NULL; // Invalid parameter

    ret = i18n_alpha_idx_get_overflow_label(alpha_idx, label);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_set_inflow_label_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_set_inflow_label and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_set_inflow_label_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    const char *label = "Test string";

    ret = i18n_alpha_idx_set_inflow_label(alpha_idx, label);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_set_inflow_label_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_set_inflow_label passing invalid index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_set_inflow_label_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    const char *label = "Test string";

    ret = i18n_alpha_idx_set_inflow_label(index, label);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_set_inflow_label_n2
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_set_inflow_label passing invalid label and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_set_inflow_label_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    char *label = NULL; // Invalid parameter

    ret = i18n_alpha_idx_set_inflow_label(alpha_idx, label);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_inflow_label_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_inflow_label and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_inflow_label_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    char *label = NULL;

    ret = i18n_alpha_idx_get_inflow_label(alpha_idx, &label);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(label, NULL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_inflow_label_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_inflow_label passing invalid index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_inflow_label_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    char *label = NULL;

    ret = i18n_alpha_idx_get_inflow_label(index, &label);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_inflow_label_n2
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_inflow_label passing invalid label and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_inflow_label_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    char **label = NULL; // Invalid parameter

    ret = i18n_alpha_idx_get_inflow_label(alpha_idx, label);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_record_data_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_record_data and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_record_data_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    const void *data = NULL;

    data = i18n_alpha_idx_get_record_data(alpha_idx);
    ret = get_last_result();

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(data, NULL);
    assert_eq(*((const int *) data), 7);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_record_data_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_record_data passing invalid index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_record_data_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    i18n_alpha_idx_get_record_data(index);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_bucket_label_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_bucket_label and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_bucket_label_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    char *label = NULL;

    ret = i18n_alpha_idx_get_bucket_label(alpha_idx, &label);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(label, NULL);
    assert_eq(strcmp(label, "A"), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_bucket_label_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_bucket_label passing invalid index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_bucket_label_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    char *label = NULL;

    ret = i18n_alpha_idx_get_bucket_label(index, &label);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_bucket_label_n2
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_bucket_label passing invalid label and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_bucket_label_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    char **label = NULL; // Invalid parameter

    ret = i18n_alpha_idx_get_bucket_label(alpha_idx, label);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_bucket_record_count_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_bucket_record_count and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_bucket_record_count_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    int32_t records_count = -1;

    ret = i18n_alpha_idx_get_bucket_record_count(alpha_idx, &records_count);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(records_count, 1);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_bucket_record_count_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_bucket_record_count passing invalid index
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_bucket_record_count_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    int32_t records_count = -1;

    ret = i18n_alpha_idx_get_bucket_record_count(index, &records_count);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_bucket_record_count_n2
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_bucket_record_count passing invalid
 *              records_count and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_bucket_record_count_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    ret = i18n_alpha_idx_get_bucket_record_count(alpha_idx, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_next_record_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_next_record and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_next_record_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    i18n_alpha_idx_reset_record_iter(alpha_idx);

    bool available = false;
    ret = i18n_alpha_idx_get_next_record(alpha_idx, &available);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(available, true);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_next_record_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_next_record passing invalid index and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_next_record_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    bool available = false;

    ret = i18n_alpha_idx_get_next_record(index, &available);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_next_bucket_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_next_bucket and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_next_bucket_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    bool available = false;

    ret = i18n_alpha_idx_get_next_bucket(alpha_idx, &available);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(available, true);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_get_next_bucket_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_get_next_bucket passing invalid index and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_get_next_bucket_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    bool is_bucket = false;

    ret = i18n_alpha_idx_get_next_bucket(index, &is_bucket);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_add_record_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_add_record and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_add_record_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    const char *name = "Test string";

    ret = i18n_alpha_idx_add_record(alpha_idx, name, &record_data);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_add_record_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_add_record passing invalid index and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_add_record_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    const char *name = "Test string";

    const void *data = NULL;

    ret = i18n_alpha_idx_add_record(index, name, data);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_add_record_n2
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_add_record passing invalid name and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_add_record_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    const char *name = NULL; // Invalid parameter

    const void *data = NULL;

    ret = i18n_alpha_idx_add_record(alpha_idx, name, data);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_add_labels_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_add_labels and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_add_labels_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    const char *language = "ko";

    const char *country = "KR";

    ret = i18n_alpha_idx_add_labels(alpha_idx, language, country);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_add_labels_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_add_labels passing invalid index and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_add_labels_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    const char *language = "en";

    const char *country = "US";

    ret = i18n_alpha_idx_add_labels(index, language, country);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_destroy_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_destroy_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    ret = i18n_alpha_idx_destroy(alpha_idx);

    assert_eq(ret, I18N_ERROR_NONE);

    alpha_idx = NULL;

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_destroy_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_destroy passing invalid index and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_destroy_n(void)
{
    i18n_alpha_idx_h index = NULL; // Invalid parameter

    ret = i18n_alpha_idx_destroy(index);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_create_p
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_create_p(void)
{
    const char *language = "ko";
    const char *country = "KR";
    i18n_alpha_idx_h index = NULL;

    ret = i18n_alpha_idx_create(language, country, &index);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(index, NULL);

    i18n_alpha_idx_destroy(index);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_create_n
 * @since_tizen 3.0
 * @description Calls i18n_alpha_idx_create passing invalid index and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_create_n(void)
{
    const char *language = "ko";
    const char *country = "KR";

    ret = i18n_alpha_idx_create(language, country, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_create_from_locale_id_p
 * @since_tizen 5.0
 * @description Calls i18n_alpha_idx_create_from_locale_id and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_create_from_locale_id_p(void)
{
    i18n_alpha_idx_h index = NULL;

    ret = i18n_alpha_idx_create_from_locale_id(locale_id, &index);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(index, NULL);

    i18n_alpha_idx_destroy(index);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_create_from_locale_id_n
 * @since_tizen 5.0
 * @description Calls i18n_alpha_idx_create_from_locale_id passing invalid index and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_create_from_locale_id_n(void)
{
    ret = i18n_alpha_idx_create_from_locale_id(locale_id, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_add_labels_with_locale_id_p
 * @since_tizen 5.0
 * @description Calls i18n_alpha_idx_add_labels_with_locale_id and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_alpha_idx_add_labels_with_locale_id_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    ret = i18n_alpha_idx_add_labels_with_locale_id(alpha_idx, locale_id);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_alpha_idx_add_labels_with_locale_id_n
 * @since_tizen 5.0
 * @description Calls i18n_alpha_idx_add_labels_with_locale_id passing invalid index and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_alpha_idx_add_labels_with_locale_id_n(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(alpha_idx, NULL);

    ret = i18n_alpha_idx_add_labels_with_locale_id(NULL, locale_id);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
