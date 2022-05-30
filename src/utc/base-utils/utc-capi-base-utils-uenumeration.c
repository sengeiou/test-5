#include "assert.h"
#include <utils_i18n.h>

//& set: capi-base-utils-uenumeration

static const i18n_uchar ustring_1[] = { 't', 0 }, ustring_2[] = { 'i', 0 }, ustring_3[] = { 'z', 0 }, ustring_4[] = { 'e', 0 }, ustring_5[] = { 'n', 0 };
static const i18n_uchar* ustrings[] = { ustring_1, ustring_2, ustring_3, ustring_4, ustring_5 };
static i18n_uenumeration_h uenum = NULL;

/**
 * @function        utc_capi_base_utils_uenumeration_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_uenumeration_startup(void)
{
    int status = i18n_uenumeration_uchar_strings_enumeration_create(ustrings, sizeof(ustrings)/sizeof(ustrings[0]), &uenum);
    if (status != I18N_ERROR_NONE)
    {
        fprintf( stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
        fprintf( stderr, "i18n_uenumeration_uchar_strings_enumeration_create ( code : %d )\n", status );
    }
}

/**
 * @function        utc_capi_base_utils_uenumeration_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_uenumeration_cleanup(void)
{
    int status = i18n_uenumeration_destroy(uenum);
    uenum = NULL;

    if (status != I18N_ERROR_NONE)
    {
        fprintf( stderr, "Cleanup error at %s:%d\n", __FILE__, __LINE__);
        fprintf( stderr, "i18n_uenumeration_destroy ( code : %d )\n", status );
    }
}

/**
 * @testcase        utc_capi_base_utils_i18n_uenumeration_destroy_p
 * @since_tizen     2.3.1
 * @description     Destroys enumeration handle,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_uenumeration_destroy_p(void)
{
    int status = i18n_uenumeration_destroy(uenum);
    uenum = NULL;

    assert_eq(status, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uenumeration_destroy_n
 * @since_tizen     2.3.1
 * @description     Destroys empty enumeration handle,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_uenumeration_destroy_n(void)
{
    int status = i18n_uenumeration_destroy(NULL);
    assert_neq(status, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uenumeration_count_p
 * @since_tizen     2.3.1
 * @description     Returns the number of elements that the iterator traverses,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_uenumeration_count_p(void)
{
    i18n_uenumeration_count(uenum);

    i18n_error_code_e status = get_last_result();
    assert_eq(status, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uenumeration_count_n
 * @since_tizen     2.3.1
 * @description     Returns the number of elements that the iterator traverses,
 *                  passing invalid enumeration handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uenumeration_count_n(void)
{
    i18n_uenumeration_count(NULL);

    i18n_error_code_e status = get_last_result();
    assert_neq(status, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uenumeration_unext_p
 * @since_tizen     2.3.1
 * @description     Returns the next element from the iterator's list,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_uenumeration_unext_p(void)
{
    int32_t result_length = 0;

    i18n_uenumeration_unext(uenum, &result_length);

    i18n_error_code_e status = get_last_result();
    assert_eq(status, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uenumeration_unext_n
 * @since_tizen     2.3.1
 * @description     Returns the next element from invalid iterator's list,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_uenumeration_unext_n(void)
{
    int32_t result_length = 0;

    i18n_uenumeration_unext(NULL, &result_length);

    i18n_error_code_e status = get_last_result();
    assert_neq(status, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uenumeration_next_p
 * @since_tizen     2.3.1
 * @description     Returns the next element from the iterator's list,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_uenumeration_next_p(void)
{
    int32_t result_length = 0;

    i18n_uenumeration_next(uenum, &result_length);

    i18n_error_code_e status = get_last_result();
    assert_eq(status, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uenumeration_next_n
 * @since_tizen     2.3.1
 * @description     Returns the next element from the iterator's list,
 *                  passing invalid enumeration handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uenumeration_next_n(void)
{
    int32_t result_length = 0;

    i18n_uenumeration_next(NULL, &result_length);

    i18n_error_code_e status = get_last_result();
    assert_neq(status, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uenumeration_reset_p
 * @since_tizen     2.3.1
 * @description     Resets the iterator,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_uenumeration_reset_p(void)
{
    int status = i18n_uenumeration_reset(uenum);
    assert_eq(status, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uenumeration_reset_n
 * @since_tizen     2.3.1
 * @description     Resets the iterator, passing invalid enumeration handle,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_uenumeration_reset_n(void)
{
    int status = i18n_uenumeration_reset(NULL);
    assert_neq(status, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uenumeration_uchar_strings_enumeration_create_p
 * @since_tizen     2.3.1
 * @description     Create enumeration handle from uchar strings,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_uenumeration_uchar_strings_enumeration_create_p(void)
{
    const i18n_uchar ustring_1[] = { 't', 0 }, ustring_2[] = { 'e', 0 }, ustring_3[] = { 's', 0 }, ustring_4[] = { 't', 0 };
    const i18n_uchar* ustrings[] = { ustring_1, ustring_2, ustring_3, ustring_4 };

    i18n_uenumeration_h local_uenum;
    int status = i18n_uenumeration_uchar_strings_enumeration_create(ustrings, sizeof(ustrings)/sizeof(ustrings[0]), &local_uenum);
    assert_eq(status, I18N_ERROR_NONE);

    i18n_uenumeration_destroy(local_uenum);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uenumeration_uchar_strings_enumeration_create_n
 * @since_tizen     2.3.1
 * @description     Create enumeration handle from uchar strings, passing
 *                  invalid outputs handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uenumeration_uchar_strings_enumeration_create_n(void)
{
    const i18n_uchar ustring_1[] = { 't', 0 }, ustring_2[] = { 'e', 0 }, ustring_3[] = { 's', 0 }, ustring_4[] = { 't', 0 };
    const i18n_uchar* ustrings[] = { ustring_1, ustring_2, ustring_3, ustring_4 };

    int status = i18n_uenumeration_uchar_strings_enumeration_create(ustrings, -1, NULL);
    assert_neq(status, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uenumeration_char_strings_enumeration_create_p
 * @since_tizen     2.3.1
 * @description     Create enumeration handle from char strings,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_uenumeration_char_strings_enumeration_create_p(void)
{
    const char string_1[] = { 't', 0 }, string_2[] = { 'e', 0 }, string_3[] = { 's', 0 }, string_4[] = { 't', 0 };
    const char* strings[] = { string_1, string_2, string_3, string_4 };

    i18n_uenumeration_h local_uenum;
    int status = i18n_uenumeration_char_strings_enumeration_create(strings, sizeof(strings)/sizeof(strings[0]), &local_uenum);

    assert_eq(status, I18N_ERROR_NONE);

    i18n_uenumeration_destroy(local_uenum);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uenumeration_char_strings_enumeration_create_n
 * @since_tizen     2.3.1
 * @description     Create enumeration handle from uchar strings, passing
 *                  invalid outputs handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uenumeration_char_strings_enumeration_create_n(void)
{
    const char string_1[] = { 't', 0 }, string_2[] = { 'e', 0 }, string_3[] = { 's', 0 }, string_4[] = { 't', 0 };
    const char* strings[] = { string_1, string_2, string_3, string_4 };

    int status = i18n_uenumeration_char_strings_enumeration_create(strings, -1, NULL);
    assert_neq(status, I18N_ERROR_NONE);

    return 0;
}
