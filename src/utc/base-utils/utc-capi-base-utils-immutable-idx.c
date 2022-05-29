#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

#define STARTUP_CLEANUP_ERROR(error, message) {\
    if(error != I18N_ERROR_NONE) \
    {\
        fprintf(stderr, message); \
        return; \
    }\
}

static int ret = I18N_ERROR_NONE;
i18n_alpha_idx_h alpha_idx = NULL;
static i18n_immutable_idx_h immutable_idx = NULL;

/**
 * @function        utc_capi_base_utils_immutable_idx_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_immutable_idx_startup(void)
{
    const char *language = "en";
    const char *country = "US";

    ret = i18n_alpha_idx_create(language, country, &alpha_idx);
    STARTUP_CLEANUP_ERROR(ret, "alpha_idx_create() failed in startup.\n");
    ret = i18n_alpha_idx_add_labels(alpha_idx, language, country);
    STARTUP_CLEANUP_ERROR(ret, "alpha_idx_add_labels() failed in startup.\n");
    ret = i18n_immutable_idx_create(alpha_idx, &immutable_idx);
    STARTUP_CLEANUP_ERROR(ret, "i18n_immutable_idx_create() failed in startup.\n");
}

/**
 * @function        utc_capi_base_utils_immutable_idx_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_immutable_idx_cleanup(void)
{
    if (alpha_idx != NULL)
    {
        ret = i18n_alpha_idx_destroy(alpha_idx);
        STARTUP_CLEANUP_ERROR(ret, "i18n_alpha_idx_destroy() failed in startup.\n");
        alpha_idx = NULL;
    }

    if (immutable_idx != NULL)
    {
        ret = i18n_immutable_idx_destroy(immutable_idx);
        STARTUP_CLEANUP_ERROR(ret, "i18n_immutable_idx_destroy() failed in startup.\n");
        immutable_idx = NULL;
    }
}

/**
 * @testcase utc_capi_base_utils_i18n_immutable_idx_create_p
 * @since_tizen 5.0
 * @description Calls i18n_immutable_idx_create and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_immutable_idx_create_p(void)
{
    utc_capi_base_utils_immutable_idx_cleanup();

    const char *language = "en";
    const char *country = "US";

    ret = i18n_alpha_idx_create(language, country, &alpha_idx);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_immutable_idx_create(alpha_idx, &immutable_idx);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(immutable_idx, NULL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_immutable_idx_create_n
 * @since_tizen 5.0
 * @description Calls i18n_immutable_idx_create passing invalid alphabetic index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_immutable_idx_create_n(void)
{
    utc_capi_base_utils_immutable_idx_cleanup();

    ret = i18n_immutable_idx_create(NULL, &immutable_idx);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_immutable_idx_create_n2
 * @since_tizen 5.0
 * @description Calls i18n_immutable_idx_create passing invalid immutable index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_immutable_idx_create_n2(void)
{
    utc_capi_base_utils_immutable_idx_cleanup();

    const char *language = "en";
    const char *country = "US";

    ret = i18n_alpha_idx_create(language, country, &alpha_idx);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_immutable_idx_create(alpha_idx, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_immutable_idx_destroy_p
 * @since_tizen 5.0
 * @description Calls i18n_immutable_idx_destroy and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_immutable_idx_destroy_p(void)
{
    ret = i18n_immutable_idx_destroy(immutable_idx);
    immutable_idx = NULL;
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_immutable_idx_destroy_n
 * @since_tizen 5.0
 * @description Calls i18n_immutable_idx_destroy passing invalid immutable index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_immutable_idx_destroy_n(void)
{
    ret = i18n_immutable_idx_destroy(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_immutable_idx_get_bucket_count_p
 * @since_tizen 5.0
 * @description Calls i18n_immutable_idx_get_bucket_count and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_immutable_idx_get_bucket_count_p(void)
{
    int32_t bucket_count = -1;

    ret = i18n_immutable_idx_get_bucket_count(immutable_idx, &bucket_count);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(bucket_count, 28);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_immutable_idx_get_bucket_count_n
 * @since_tizen 5.0
 * @description Calls i18n_immutable_idx_get_bucket_count passing invalid immutable index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_immutable_idx_get_bucket_count_n(void)
{
    int32_t bucket_count = -1;

    ret = i18n_immutable_idx_get_bucket_count(NULL, &bucket_count);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_immutable_idx_get_bucket_count_n2
 * @since_tizen 5.0
 * @description Calls i18n_immutable_idx_get_bucket_count passing invalid count and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_immutable_idx_get_bucket_count_n2(void)
{
    ret = i18n_immutable_idx_get_bucket_count(immutable_idx, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_immutable_idx_get_bucket_index_p
 * @since_tizen 5.0
 * @description Calls i18n_immutable_idx_get_bucket_index and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_immutable_idx_get_bucket_index_p(void)
{
    int32_t bucket_index = -1;
    char *name = "C";

    ret = i18n_immutable_idx_get_bucket_index(immutable_idx, name, &bucket_index);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(bucket_index, 3);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_immutable_idx_get_bucket_index_n
 * @since_tizen 5.0
 * @description Calls i18n_immutable_idx_get_bucket_index passing invalid immutable index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_immutable_idx_get_bucket_index_n(void)
{
    int32_t bucket_index = -1;
    char *name = "C";

    ret = i18n_immutable_idx_get_bucket_index(NULL, name, &bucket_index);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_immutable_idx_get_bucket_index_n2
 * @since_tizen 5.0
 * @description Calls i18n_immutable_idx_get_bucket_index passing invalid name and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_immutable_idx_get_bucket_index_n2(void)
{
    int32_t bucket_index = -1;

    ret = i18n_immutable_idx_get_bucket_index(immutable_idx, NULL, &bucket_index);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_immutable_idx_get_bucket_index_n3
 * @since_tizen 5.0
 * @description Calls i18n_immutable_idx_get_bucket_index passing invalid number and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_immutable_idx_get_bucket_index_n3(void)
{
    char *name = "C";

    ret = i18n_immutable_idx_get_bucket_index(immutable_idx, name, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_immutable_idx_get_bucket_label_p
 * @since_tizen 5.0
 * @description Calls i18n_immutable_idx_get_bucket_label and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_immutable_idx_get_bucket_label_p(void)
{
    int32_t position = 3;
    char *bucket_label = NULL;

    ret = i18n_immutable_idx_get_bucket_label(immutable_idx, position, &bucket_label);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(0, strcmp(bucket_label, "C"));

    free(bucket_label);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_immutable_idx_get_bucket_label_n
 * @since_tizen 5.0
 * @description Calls i18n_immutable_idx_get_bucket_label passing invalid immutable index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_immutable_idx_get_bucket_label_n(void)
{
    int32_t position = 2;
    char *bucket_label = NULL;

    ret = i18n_immutable_idx_get_bucket_label(NULL, position, &bucket_label);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_immutable_idx_get_bucket_label_n2
 * @since_tizen 5.0
 * @description Calls i18n_immutable_idx_get_bucket_label passing invalid label and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_immutable_idx_get_bucket_label_n2(void)
{
    int32_t position = 2;

    ret = i18n_immutable_idx_get_bucket_label(immutable_idx, position, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_immutable_idx_get_bucket_label_type_p
 * @since_tizen 5.0
 * @description Calls i18n_immutable_idx_get_bucket_label_type and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_immutable_idx_get_bucket_label_type_p(void)
{
    i18n_alpha_idx_label_type_e type;
    int32_t position = 0;

    ret = i18n_immutable_idx_get_bucket_label_type(immutable_idx, position, &type);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(type, I18N_ALPHA_IDX_UNDERFLOW);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_immutable_idx_get_bucket_label_type_n
 * @since_tizen 5.0
 * @description Calls i18n_immutable_idx_get_bucket_label_type passing invalid immutable index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_immutable_idx_get_bucket_label_type_n(void)
{
    i18n_alpha_idx_label_type_e type;
    int32_t position = 0;

    ret = i18n_immutable_idx_get_bucket_label_type(NULL, position, &type);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_immutable_idx_get_bucket_label_type_n2
 * @since_tizen 5.0
 * @description Calls i18n_immutable_idx_get_bucket_label_type passing invalid type and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_immutable_idx_get_bucket_label_type_n2(void)
{
    int32_t position = 0;

    ret = i18n_immutable_idx_get_bucket_label_type(immutable_idx, position, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
