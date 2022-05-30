#include "assert.h"
#include <string.h>
#include <utils_i18n.h>

//& set: capi-base-utils-usearch

static int ret = I18N_ERROR_NONE;
static i18n_usearch_h search = NULL;
static const i18n_uchar search_pattern[] = { 'i', 0x0 };

/**
 * @function        utc_capi_base_utils_usearch_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_usearch_startup(void)
{
}
/**
 * @function        utc_capi_base_utils_usearch_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_usearch_cleanup(void)
{
    if(search != NULL) {
        i18n_usearch_destroy(search);
        search = NULL;
    }
}

/**
 * @testcase        utc_capi_base_utils_i18n_usearch_create_new_p
 * @since_tizen     2.3.1
 * @description     Creates an i18n_usearch_h using the argument locale language
 *                  rule set.
 */
int utc_capi_base_utils_i18n_usearch_create_new_p(void)
{
    static i18n_usearch_h search_h;
    const i18n_uchar pattern[] = { 'i', 0x0 };
    int32_t pattern_length = -1;
    const i18n_uchar text[] = { 't', 'i', 'z', 'e', 'n', 0x0 };
    int32_t text_length = -1;
    i18n_ubreak_iterator_h break_iter = NULL;

    ret = i18n_usearch_create_new(pattern, pattern_length, text, text_length, "en_US", break_iter, &search_h);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(search_h, NULL);

    i18n_usearch_destroy(search_h);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_usearch_create_new_n
 * @since_tizen     2.3.1
 * @description     Creates an i18n_usearch_h using the argument locale language
 *                  rule set passing NULL to search_iter parameter.
 */
int utc_capi_base_utils_i18n_usearch_create_new_n(void)
{
    const i18n_uchar *pattern = NULL;
    int32_t pattern_length = -10;
    const i18n_uchar *text = NULL;
    int32_t text_length = -10;
    i18n_ubreak_iterator_h break_iter = NULL;

    ret = i18n_usearch_create_new(pattern, pattern_length, text, text_length, "en_US", break_iter, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_usearch_destroy_p
 * @since_tizen     2.3.1
 * @description     Creates, destroys and cleans up the i18n_usearch_h.
 */
int utc_capi_base_utils_i18n_usearch_destroy_p(void)
{
    int32_t pattern_length = -1;
    const i18n_uchar text[] = { 't', 'i', 'z', 'e', 'n', 0x0 };
    int32_t text_length = -1;
    i18n_ubreak_iterator_h breakiter = NULL;

    ret = i18n_usearch_create_new(search_pattern, pattern_length, text, text_length, "en_US", breakiter, &search);

    assert_neq(search, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_usearch_destroy(search);

    assert_eq(ret, I18N_ERROR_NONE);
    search = NULL;

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_usearch_destroy_n
 * @since_tizen     2.3
 * @description     Creates, destroys and cleans up the i18n_usearch_h passing
 *                  NULL to parameter.
 */
int utc_capi_base_utils_i18n_usearch_destroy_n(void)
{
    ret = i18n_usearch_destroy(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_usearch_get_matched_text_p
 * @since_tizen     2.3
 * @description     Searches for pattern and get matches
 */
int utc_capi_base_utils_i18n_usearch_get_matched_text_p(void)
{
    i18n_uchar result[64] = { 0, };
    int result_capacity = 64;
    int len_matched_text;

    int32_t index_first = 0;

    int32_t pattern_length = -1;
    const i18n_uchar text[] = { 't', 'i', 'z', 'e', 'n', 0x0 };
    int32_t text_length = -1;
    i18n_ubreak_iterator_h breakiter = NULL;

    ret = i18n_usearch_create_new(search_pattern, pattern_length, text, text_length, "en_US", breakiter, &search);
    assert_neq(search, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_usearch_first(search, &index_first);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_usearch_get_matched_text(search, result, result_capacity, &len_matched_text);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_usearch_get_matched_text_n
 * @since_tizen     2.3
 * @description    Get matches passing NULL to search_iter parameter.
 */
int utc_capi_base_utils_i18n_usearch_get_matched_text_n(void)
{
    i18n_uchar result[64] = { 0, };
    int result_capacity = -1;
    int len_matched_text;

    ret = i18n_usearch_get_matched_text(NULL, result, result_capacity, &len_matched_text);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_usearch_get_collator_p
 * @since_tizen     2.3
 * @description     Gets the collator used for the language rules.
 */
int utc_capi_base_utils_i18n_usearch_get_collator_p(void)
{
    i18n_ucollator_h collator;

    int32_t pattern_length = -1;
    const i18n_uchar text[] = { 't', 'i', 'z', 'e', 'n', 0x0 };
    int32_t text_length = -1;
    i18n_ubreak_iterator_h breakiter = NULL;

    ret = i18n_usearch_create_new(search_pattern, pattern_length, text, text_length, "en_US", breakiter, &search);
    assert_neq(search, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_usearch_get_collator(search, &collator);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(collator, NULL);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_usearch_get_collator_n
 * @since_tizen     2.3
 * @description     Gets the collator used for the language rules passing NULL
 *                  to search_iter and callator parameters.
 */
int utc_capi_base_utils_i18n_usearch_get_collator_n(void)
{
    ret = i18n_usearch_get_collator(NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_usearch_first_p
 * @since_tizen     2.3
 * @description     Gets the first index at which the string text matches the
 *                  search pattern.
 */
int utc_capi_base_utils_i18n_usearch_first_p(void)
{
    int32_t index_first = 0;

    int32_t pattern_length = -1;
    const i18n_uchar text[] = { 't', 'i', 'z', 'e', 'n', 0x0 };
    int32_t text_length = -1;
    i18n_ubreak_iterator_s *breakiter = NULL;

    ret = i18n_usearch_create_new(search_pattern, pattern_length, text, text_length, "en_US", breakiter, &search);
    assert_neq(search, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_usearch_first(search, &index_first);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(index_first, 1);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_usearch_first_n
 * @since_tizen     2.3
 * @description     Gets the first index at which the string text matches the
 *                  search pattern passing NULL to search_iter and callator
 *                  parameters.
 */
int utc_capi_base_utils_i18n_usearch_first_n(void)
{
    ret = i18n_usearch_first(NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
