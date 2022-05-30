#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

#define STR_LEN 64

static i18n_ucollator_h g_coll = NULL;
static i18n_uchar g_ustr[STR_LEN] = { 0, };
static i18n_uchar g_target[STR_LEN] = { 0, };
static int g_str_len = -1;
static char *g_astr = "Test String";

static const char *str1 = "First string";
static const char *str2 = "Second string";
static i18n_uchar str1_uchar[STR_LEN] = { 0, };
static i18n_uchar str2_uchar[STR_LEN] = { 0, };
static int32_t len1 = 0;
static int32_t len2 = 0;
static const char *rules = "&9 < a, A < b, B < c, C; ch, cH, Ch, CH < d, D, e, E";

static int ret;

/**
 * @function        utc_capi_base_utils_ucollator_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_ucollator_startup(void)
{
    i18n_ustring_copy_ua(str1_uchar, str1);
    i18n_ustring_copy_ua(str2_uchar, str2);

    len1 = i18n_ustring_get_length(str1_uchar);
    len2 = i18n_ustring_get_length(str2_uchar);

    i18n_ustring_copy_ua_n( g_ustr, g_astr, strlen(g_astr) );
    i18n_ustring_copy_ua_n( g_target, g_astr, strlen(g_astr) );
    g_str_len = i18n_ustring_get_length(g_ustr);

    ret = i18n_ucollator_create("en_US", &g_coll );
}

/**
 * @function        utc_capi_base_utils_ucollator_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_ucollator_cleanup(void)
{
    i18n_ucollator_destroy( g_coll );
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_create_p
 * @since_tizen     2.3
 * @description     Creates a collator handle for comparing strings,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_create_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(g_coll, NULL);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_create_n
 * @since_tizen     2.3
 * @description     Creates a collator handle for comparing strings,
 *                  passing invalid collator handle and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_create_n(void)
{
    int ret = I18N_ERROR_NONE;

    ret = i18n_ucollator_create( "en_US", NULL );
    assert_eq( ret, I18N_ERROR_INVALID_PARAMETER );

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_destroy_p
 * @since_tizen     2.3
 * @description     Closes a collator handle, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_destroy_p(void)
{
    int ret = I18N_ERROR_NONE;

    ret = i18n_ucollator_destroy( g_coll );
    assert_eq( ret, I18N_ERROR_NONE );

    ret = i18n_ucollator_create( "en_US", &g_coll );
    assert_eq( ret, I18N_ERROR_NONE );
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_create_rules_p
 * @since_tizen     4.0
 * @description     Creates a collator rule, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_create_rules_p(void)
{
	i18n_ucollator_h coll = NULL;
	i18n_uparse_error_s parse_error;
	i18n_uchar uchar_rules[128];

	i18n_ustring_copy_ua(uchar_rules, rules);
	ret = i18n_ucollator_create_rules(uchar_rules, -1, I18N_UCOLLATOR_ON, I18N_UCOLLATOR_DEFAULT_STRENGTH,
										&parse_error, &coll);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(coll, NULL);
	i18n_ucollator_destroy(coll);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_create_rules_n
 * @since_tizen     4.0
 * @description     Creates a collator rule, passing invalid rules and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_create_rules_n(void)
{
	i18n_ucollator_h coll = NULL;
	i18n_uparse_error_s parse_error;

	ret = i18n_ucollator_create_rules(NULL, -1, I18N_UCOLLATOR_ON, I18N_UCOLLATOR_DEFAULT_STRENGTH,
										&parse_error, &coll);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_create_rules_n2
 * @since_tizen     4.0
 * @description     Creates a collator rule, passing invalid rules' length and
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_create_rules_n2(void)
{
	i18n_ucollator_h coll = NULL;
	i18n_uparse_error_s parse_error;
	i18n_uchar uchar_rules[128];

	i18n_ustring_copy_ua(uchar_rules, rules);
	ret = i18n_ucollator_create_rules(uchar_rules, -2, I18N_UCOLLATOR_ON, I18N_UCOLLATOR_DEFAULT_STRENGTH,
										&parse_error, &coll);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_create_rules_n3
 * @since_tizen     4.0
 * @description     Creates a collator rule, passing invalid collator handle and
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_create_rules_n3(void)
{
	i18n_uparse_error_s parse_error;
	i18n_uchar uchar_rules[128];

	i18n_ustring_copy_ua(uchar_rules, rules);

	ret = i18n_ucollator_create_rules(uchar_rules, -1, I18N_UCOLLATOR_ON, I18N_UCOLLATOR_DEFAULT_STRENGTH,
										&parse_error, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_contractions_and_expansions_p
 * @since_tizen     4.0
 * @description     Gets contractions and expansions, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_contractions_and_expansions_p(void)
{
	i18n_uset_h contractions;
	i18n_uset_h expansions;

	ret = i18n_uset_create_empty(&contractions);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uset_create_empty(&expansions);
	assert_eq(ret ,I18N_ERROR_NONE);
	ret = i18n_ucollator_get_contractions_and_expansions(g_coll, true, contractions, expansions);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uset_destroy(contractions);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uset_destroy(expansions);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_contractions_and_expansions_n
 * @since_tizen     4.0
 * @description     Gets contractions and expansions, passing invalid collator handle and
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_contractions_and_expansions_n(void)
{
	ret = i18n_ucollator_get_contractions_and_expansions(NULL, true, NULL, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_str_collator_utf8_p
 * @since_tizen     4.0
 * @description     Compares two strings, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_str_collator_utf8_p(void)
{
	i18n_ucollator_result_e result;

	ret = i18n_ucollator_str_collator_utf8(g_coll, str1, strlen(str1), str2, strlen(str2), &result);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(result, I18N_UCOLLATOR_LESS);

	ret = i18n_ucollator_str_collator_utf8(g_coll, str1, strlen(str1), str1, strlen(str1), &result);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(result, I18N_UCOLLATOR_EQUAL);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_str_collator_utf8_n
 * @since_tizen     4.0
 * @description     Compares two strings, passing invalid collator handle and
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_str_collator_utf8_n(void)
{
	i18n_ucollator_result_e result;

	ret = i18n_ucollator_str_collator_utf8(NULL, str1, strlen(str1), str2, strlen(str2), &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_greater_p
 * @since_tizen     4.0
 * @description     Determines if one string is greater than another, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_greater_p(void)
{
	i18n_ubool is_greater;
	ret = i18n_ucollator_greater(g_coll, str1_uchar, len1, str2_uchar, len2, &is_greater);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(is_greater, false);

	ret = i18n_ucollator_greater(g_coll, str2_uchar, len2, str1_uchar, len1, &is_greater);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(is_greater, true);

	ret = i18n_ucollator_greater(g_coll, str1_uchar, len1, str1_uchar, len1, &is_greater);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(is_greater, false);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_greater_n
 * @since_tizen     4.0
 * @description     Determines if one string is greater than another, passing invalid
 *                  result and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_greater_n(void)
{
	ret = i18n_ucollator_greater(g_coll, str2_uchar, len2, str1_uchar, len1, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_greater_n2
 * @since_tizen     4.0
 * @description     Determines if one string is greater than another, passing invalid
 *                  collator handle and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_greater_n2(void)
{
	i18n_ubool is_greater;

	ret = i18n_ucollator_greater(NULL, str2_uchar, len2, str1_uchar, len1, &is_greater);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_greater_or_equal_p
 * @since_tizen     4.0
 * @description     Determines if one string is greater than or equal to another,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_greater_or_equal_p(void)
{
	i18n_ubool is_greater_equal;

	ret = i18n_ucollator_greater_or_equal(g_coll, str1_uchar, len1, str2_uchar, len2, &is_greater_equal);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(is_greater_equal, false);

	ret = i18n_ucollator_greater_or_equal(g_coll, str2_uchar, len2, str1_uchar, len1, &is_greater_equal);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(is_greater_equal, true);

	ret = i18n_ucollator_greater_or_equal(g_coll, str1_uchar, len1, str1_uchar, len1, &is_greater_equal);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(is_greater_equal, true);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_greater_or_equal_n
 * @since_tizen     4.0
 * @description     Determines if one string is greater than or equal to another,
 *                  passing invalid result and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_greater_or_equal_n(void)
{

	ret = i18n_ucollator_greater_or_equal(g_coll, str2_uchar, len2, str1_uchar, len1, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_greater_or_equal_n2
 * @since_tizen     4.0
 * @description     Determines if one string is greater than or equal to another,
 *                  passing invalid collator handle and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_greater_or_equal_n2(void)
{
	i18n_ubool is_greater_equal;

	ret = i18n_ucollator_greater_or_equal(NULL, str2_uchar, len2, str1_uchar, len1, &is_greater_equal);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_str_collator_iter_p
 * @since_tizen     4.0
 * @description     Compares two UTF-8 encoded strings, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_str_collator_iter_p(void)
{
	i18n_uchar_iter_h s_iter = NULL;
	i18n_uchar_iter_h t_iter = NULL;
	i18n_ucollator_result_e result;

	ret = i18n_uchar_iter_create(&s_iter);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_create(&t_iter);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_set_utf8(s_iter, str1, strlen(str1));
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_set_utf8(t_iter, str2, strlen(str2));
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucollator_str_collator_iter(g_coll, s_iter, t_iter, &result);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(result, I18N_UCOLLATOR_LESS);

	ret = i18n_uchar_iter_destroy(s_iter);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_destroy(t_iter);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_str_collator_iter_n
 * @since_tizen     4.0
 * @description     Compares two UTF-8 encoded strings, passing invalid collator
 *                  handle and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_str_collator_iter_n(void)
{
	i18n_uchar_iter_h s_iter = NULL;
	i18n_uchar_iter_h t_iter = NULL;
	i18n_ucollator_result_e result;

	ret = i18n_uchar_iter_create(&s_iter);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_create(&t_iter);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_set_utf8(s_iter, str1, strlen(str1));
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_set_utf8(t_iter, str2, strlen(str2));
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucollator_str_collator_iter(NULL, s_iter, t_iter, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uchar_iter_destroy(s_iter);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_destroy(t_iter);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_str_collator_iter_n2
 * @since_tizen     4.0
 * @description     Compares two UTF-8 encoded strings, passing invalid result
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_str_collator_iter_n2(void)
{
	i18n_uchar_iter_h s_iter = NULL;
	i18n_uchar_iter_h t_iter = NULL;

	ret = i18n_uchar_iter_create(&s_iter);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_create(&t_iter);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_set_utf8(s_iter, str1, strlen(str1));
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_set_utf8(t_iter, str2, strlen(str2));
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucollator_str_collator_iter(g_coll, s_iter, t_iter, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uchar_iter_destroy(s_iter);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_destroy(t_iter);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_strength_p
 * @since_tizen     4.0
 * @description     Gets the collation strength, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_strength_p(void)
{
	i18n_ucollator_strength_e strength;

	ret = i18n_ucollator_get_strength(g_coll, &strength);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_str_collator_iter_n2
 * @since_tizen     4.0
 * @description     Gets the collation strength, passing invalid result and
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_strength_n(void)
{
	ret = i18n_ucollator_get_strength(g_coll, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_str_collator_iter_n2
 * @since_tizen     4.0
 * @description     Gets the collation strength, passing invalid collator handle
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_strength_n2(void)
{
	i18n_ucollator_strength_e strength;

	ret = i18n_ucollator_get_strength(NULL, &strength);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_reorder_codes_p
 * @since_tizen     4.0
 * @description     Retrieves the reordering codes, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_reorder_codes_p(void)
{
	int32_t dest_size = 64;
	int32_t dest[dest_size];
	int32_t n_codes;

	ret = i18n_ucollator_get_reorder_codes(g_coll, dest_size, dest, &n_codes);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_reorder_codes_n
 * @since_tizen     4.0
 * @description     Retrieves the reordering codes, passing invalid result
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_reorder_codes_n(void)
{
	int32_t dest_size = 64;
	int32_t dest[dest_size];

	ret = i18n_ucollator_get_reorder_codes(g_coll, dest_size, dest, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_reorder_codes_n2
 * @since_tizen     4.0
 * @description     Retrieves the reordering codes, passing invalid collator handle
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_reorder_codes_n2(void)
{
	int32_t dest_size = 64;
	int32_t dest[dest_size];
	int32_t n_codes;

	ret = i18n_ucollator_get_reorder_codes(NULL, dest_size, dest, &n_codes);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_set_reorder_codes_p
 * @since_tizen     4.0
 * @description     Sets the reordering codes, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_set_reorder_codes_p(void)
{
	ret = i18n_ucollator_set_reorder_codes(g_coll, NULL, 0);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_set_reorder_codes_n
 * @since_tizen     4.0
 * @description     Sets the reordering codes, passing invalid collator handle
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_set_reorder_codes_n(void)
{
	ret = i18n_ucollator_set_reorder_codes(NULL, NULL, 0);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_equivalent_reorder_codes_p
 * @since_tizen     4.0
 * @description     Retrieves the grouped reorder codes, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_equivalent_reorder_codes_p(void)
{
	int32_t dest[64];
	int32_t n_codes;

	ret = i18n_ucollator_get_equivalent_reorder_codes(I18N_UCOLLATOR_REORDER_CODE_CURRENCY, 64,
														dest, &n_codes);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_equivalent_reorder_codes_n
 * @since_tizen     4.0
 * @description     Retrieves the grouped reorder codes, passing invalid result
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_equivalent_reorder_codes_n(void)
{
	int32_t dest[64];

	ret = i18n_ucollator_get_equivalent_reorder_codes(I18N_UCOLLATOR_REORDER_CODE_CURRENCY, 64,
														dest, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_display_name_p
 * @since_tizen     4.0
 * @description     Gets the display name, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_display_name_p(void)
{
	i18n_uchar dest[64];
	int32_t display_size;

	ret = i18n_ucollator_get_display_name("en_US", "en_US", 64, dest, &display_size);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_display_name_n
 * @since_tizen     4.0
 * @description     Gets the display name, passing invalid destination
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_display_name_n(void)
{
	int32_t display_size;

	ret = i18n_ucollator_get_display_name("en_US", "en_US", 64, NULL, &display_size);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_display_name_n2
 * @since_tizen     4.0
 * @description     Gets the display name, passing invalid display size
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_display_name_n2(void)
{
	i18n_uchar dest[64];

	ret = i18n_ucollator_get_display_name("en_US", "en_US", 64, dest, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_available_p
 * @since_tizen     4.0
 * @description     Gets a locale for which collation rules are available,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_available_p(void)
{
	const char *locale = NULL;
	int32_t locale_index = 0;

	ret = i18n_ucollator_get_available(locale_index, &locale);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(locale, NULL);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_display_name_n2
 * @since_tizen     4.0
 * @description     Gets a locale for which collation rules are available,
 *                  passing invalid locale and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_available_n(void)
{
	int32_t locale_index = 0;

	ret = i18n_ucollator_get_available(locale_index, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_count_available_p
 * @since_tizen     4.0
 * @description     Determines how many locales have collation rules available,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_count_available_p(void)
{
	int32_t n_available;

	ret = i18n_ucollator_count_available(&n_available);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_count_available_n
 * @since_tizen     4.0
 * @description     Determines how many locales have collation rules available,
 *                  passing invalid result and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_count_available_n(void)
{
	ret = i18n_ucollator_count_available(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_create_available_locales_p
 * @since_tizen     4.0
 * @description     Creates a string enumerator of all locales, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_create_available_locales_p(void)
{
	i18n_uenumeration_h locales;

	ret = i18n_ucollator_create_available_locales(&locales);
	assert_eq(ret, I18N_ERROR_NONE);
	i18n_uenumeration_destroy(locales);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_create_available_locales_n
 * @since_tizen     4.0
 * @description     Creates a string enumerator of all locales, passing invalid
 *                  locales and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_create_available_locales_n(void)
{
	ret = i18n_ucollator_create_available_locales(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_keywords_p
 * @since_tizen     4.0
 * @description     Creates a string enumerator of all possible keywords,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_keywords_p(void)
{
	i18n_uenumeration_h keywords;

	ret = i18n_ucollator_get_keywords(&keywords);
	assert_eq(ret, I18N_ERROR_NONE);
	i18n_uenumeration_destroy(keywords);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_keywords_n
 * @since_tizen     4.0
 * @description     Creates a string enumerator of all possible keywords, passing
 *                  invalid keywords and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_keywords_n(void)
{
	ret = i18n_ucollator_get_keywords(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_keyword_values_p
 * @since_tizen     4.0
 * @description     Creates a string enumeration of all values for the given keyword,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_keyword_values_p(void)
{
	i18n_uenumeration_h keyword_values;

	ret = i18n_ucollator_get_keyword_values("collation", &keyword_values);
	assert_eq(ret, I18N_ERROR_NONE);
	i18n_uenumeration_destroy(keyword_values);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_keyword_values_n
 * @since_tizen     4.0
 * @description     Creates a string enumeration of all values for the given keyword,
 *                  passing invalid keyword values and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_keyword_values_n(void)
{
	ret = i18n_ucollator_get_keyword_values("collation", NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_keyword_values_for_locale_p
 * @since_tizen     4.0
 * @description     Creates a string enumeration of all values for the given keyword and locale,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_keyword_values_for_locale_p(void)
{
	i18n_uenumeration_h keywords;

	ret = i18n_ucollator_get_keyword_values_for_locale("collation", "en_US", false, &keywords);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_keyword_values_n
 * @since_tizen     4.0
 * @description     Creates a string enumeration of all values for the given keyword and locale,
 *                  passing invalid keyword values and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_keyword_values_for_locale_n(void)
{
	ret = i18n_ucollator_get_keyword_values_for_locale("collation", "en_US", false, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_functional_equivalent_p
 * @since_tizen     4.0
 * @description     Gets functionally equivalent locale, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_functional_equivalent_p(void)
{
	char dest[128];
	int32_t buffer_size;

	ret = i18n_ucollator_get_functional_equivalent("collation", "en_US", 128, dest, NULL, &buffer_size);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_functional_equivalent_n
 * @since_tizen     4.0
 * @description     Gets functionally equivalent locale, passing invalid buffer size
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_functional_equivalent_n(void)
{
	char dest[128];

	ret = i18n_ucollator_get_functional_equivalent("collation", "en_US", 128, dest, NULL, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_rules_p
 * @since_tizen     4.0
 * @description     Gets the collation tailoring rules, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_rules_p(void)
{
	int32_t length;
	const i18n_uchar *rules = NULL;

	ret = i18n_ucollator_get_rules(g_coll, &length, &rules);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(rules, NULL);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_rules_n
 * @since_tizen     4.0
 * @description     Gets the collation tailoring rules, passing invalid rules
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_rules_n(void)
{
	int32_t length;

	ret = i18n_ucollator_get_rules(g_coll, &length, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_rules_n2
 * @since_tizen     4.0
 * @description     Gets the collation tailoring rules, passing invalid
 *                  collator handle and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_rules_n2(void)
{
	int32_t length;
	const i18n_uchar *rules = NULL;

	ret = i18n_ucollator_get_rules(NULL, &length, &rules);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_sort_key_p
 * @since_tizen     4.0
 * @description     Gets a sort key for a string, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_sort_key_p(void)
{
	i18n_uchar src[64];
	i18n_ustring_copy_ua(src, str1);
	uint8_t sort_key[64];
	int32_t result_length;

	ret = i18n_ucollator_get_sort_key(g_coll, src, -1, 64, sort_key, &result_length);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_sort_key_n
 * @since_tizen     4.0
 * @description     Gets a sort key for a string, passing invalid collator handle
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_sort_key_n(void)
{
	i18n_uchar src[64];
	i18n_ustring_copy_ua(src, str1);
	uint8_t sort_key[64];
	int32_t result_length;

	ret = i18n_ucollator_get_sort_key(NULL, src, -1, 64, sort_key, &result_length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_sort_key_n2
 * @since_tizen     4.0
 * @description     Gets a sort key for a string, passing invalid result length
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_sort_key_n2(void)
{
	i18n_uchar src[64];
	i18n_ustring_copy_ua(src, str1);
	uint8_t sort_key[64];

	ret = i18n_ucollator_get_sort_key(g_coll, src, -1, 64, sort_key, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_next_sort_key_part_p
 * @since_tizen     4.0
 * @description     Gets the next count bytes of a sort key, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_next_sort_key_part_p(void)
{
	uint32_t state[2];
	uint8_t dest[64];
	int32_t result_length;
	i18n_uchar_iter_h iter = NULL;

	ret = i18n_uchar_iter_create(&iter);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_set_utf8(iter, str1, strlen(str1));
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_ucollator_next_sort_key_part(g_coll, iter, state, dest, 1, &result_length);
	assert_eq(ret, I18N_ERROR_NONE);
	i18n_uchar_iter_destroy(iter);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_next_sort_key_part_n
 * @since_tizen     4.0
 * @description     Gets the next count bytes of a sort key, passing invalid collator handle
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_next_sort_key_part_n(void)
{
	uint32_t state[2];
	uint8_t dest[64];
	int32_t result_length;
	i18n_uchar_iter_h iter = NULL;

	ret = i18n_uchar_iter_create(&iter);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_set_utf8(iter, str1, strlen(str1));
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_ucollator_next_sort_key_part(NULL, iter, state, dest, 1, &result_length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	i18n_uchar_iter_destroy(iter);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_next_sort_key_part_n2
 * @since_tizen     4.0
 * @description     Gets the next count bytes of a sort key, passing invalid result length
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_next_sort_key_part_n2(void)
{
	uint32_t state[2];
	uint8_t dest[64];
	i18n_uchar_iter_h iter = NULL;

	ret = i18n_uchar_iter_create(&iter);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_set_utf8(iter, str1, strlen(str1));
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_ucollator_next_sort_key_part(g_coll, iter, state, dest, 1, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	i18n_uchar_iter_destroy(iter);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_bound_p
 * @since_tizen     4.0
 * @description     Produces a bound for a given sortkey and a number of levels, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_bound_p(void)
{
	i18n_uchar src[64];
	i18n_ustring_copy_ua(src, str1);
	uint8_t sort_key[64];
	int32_t result_length;
	uint8_t bound[128];
	int32_t bound_length;

	ret = i18n_ucollator_get_sort_key(g_coll, src, -1, 64, sort_key, &result_length);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_ucollator_get_bound(sort_key, result_length, I18N_UCOLLATOR_BOUND_UPPER, 1, bound,
									128, &bound_length);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_bound_n
 * @since_tizen     4.0
 * @description     Produces a bound for a given sortkey and a number of levels, passing invalid needed size
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_bound_n(void)
{
	i18n_uchar src[64];
	i18n_ustring_copy_ua(src, str1);
	uint8_t sort_key[64];
	int32_t result_length;
	uint8_t bound[128];

	ret = i18n_ucollator_get_sort_key(g_coll, src, -1, 64, sort_key, &result_length);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_ucollator_get_bound(sort_key, result_length, I18N_UCOLLATOR_BOUND_UPPER, 1, bound,
									128, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_version_p
 * @since_tizen     4.0
 * @description     Gets the version information for a Collator, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_version_p(void)
{
	i18n_uversion_info info;

	ret = i18n_ucollator_get_version(g_coll, info);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_version_n
 * @since_tizen     4.0
 * @description     Gets the version information for a Collator, passing invalid collator handle
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_version_n(void)
{
	i18n_uversion_info info;

	ret = i18n_ucollator_get_version(NULL, info);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_version_n2
 * @since_tizen     4.0
 * @description     Gets the version information for a Collator, passing invalid info array
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_version_n2(void)
{
	ret = i18n_ucollator_get_version(g_coll, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_uca_version_p
 * @since_tizen     4.0
 * @description     Gets the UCA version information for a Collator, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_uca_version_p(void)
{
	i18n_uversion_info info;

	ret = i18n_ucollator_get_uca_version(g_coll, info);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_uca_version_n
 * @since_tizen     4.0
 * @description     Gets the UCA version information for a Collator, passing invalid collator handle
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_uca_version_n(void)
{
	i18n_uversion_info info;

	ret = i18n_ucollator_get_uca_version(NULL, info);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_uca_version_n2
 * @since_tizen     4.0
 * @description     Gets the UCA version information for a Collator, passing invalid info array
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_uca_version_n2(void)
{
	ret = i18n_ucollator_get_uca_version(g_coll, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_merge_sort_keys_p
 * @since_tizen     4.0
 * @description     Merges two sort keys, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_merge_sort_keys_p(void)
{
	i18n_uchar src1[64];
	i18n_uchar src2[64];
	i18n_ustring_copy_ua(src1, str1);
	i18n_ustring_copy_ua(src2, str2);
	uint8_t sort_key1[64];
	uint8_t sort_key2[64];
	int32_t result_length1;
	int32_t result_length2;

	uint8_t merged[128];
	int32_t merged_length;

	ret = i18n_ucollator_get_sort_key(g_coll, src1, -1, 64, sort_key1, &result_length1);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucollator_get_sort_key(g_coll, src2, -1, 64, sort_key2, &result_length2);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucollator_merge_sort_keys(sort_key1, result_length1, sort_key2, result_length2,
											128, merged, &merged_length);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_merge_sort_keys_n
 * @since_tizen     4.0
 * @description     Gets the UCA version information for a Collator, passing invalid merged length
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_merge_sort_keys_n(void)
{
	i18n_uchar src1[64];
	i18n_uchar src2[64];
	i18n_ustring_copy_ua(src1, str1);
	i18n_ustring_copy_ua(src2, str2);
	uint8_t sort_key1[64];
	uint8_t sort_key2[64];
	int32_t result_length1;
	int32_t result_length2;

	uint8_t merged[128];

	ret = i18n_ucollator_get_sort_key(g_coll, src1, -1, 64, sort_key1, &result_length1);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucollator_get_sort_key(g_coll, src2, -1, 64, sort_key2, &result_length2);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucollator_merge_sort_keys(sort_key1, result_length1, sort_key2, result_length2,
											128, merged, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_attribute_p
 * @since_tizen     4.0
 * @description     Gets attribute, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_attribute_p(void)
{
	i18n_ucollator_attribute_value_e val;

	ret = i18n_ucollator_get_attribute(g_coll, I18N_UCOLLATOR_STRENGTH, &val);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_attribute_n
 * @since_tizen     4.0
 * @description     Gets attribute, passing invalid collator handle
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_attribute_n(void)
{
	i18n_ucollator_attribute_value_e val;

	ret = i18n_ucollator_get_attribute(NULL, I18N_UCOLLATOR_STRENGTH, &val);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_attribute_n2
 * @since_tizen     4.0
 * @description     Gets attribute, passing invalid value
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_attribute_n2(void)
{
	ret = i18n_ucollator_get_attribute(g_coll, I18N_UCOLLATOR_STRENGTH, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_set_max_variable_p
 * @since_tizen     4.0
 * @description     Sets the variable top to the top of the specified reordering group, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_set_max_variable_p(void)
{
	ret = i18n_ucollator_set_max_variable(g_coll, I18N_UCOLLATOR_REORDER_CODE_SYMBOL);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucollator_set_max_variable(g_coll, I18N_UCOLLATOR_REORDER_CODE_CURRENCY);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_set_max_variable_n
 * @since_tizen     4.0
 * @description     Sets the variable top to the top of the specified reordering group,
 *                  passing invalid collator handle and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_set_max_variable_n(void)
{
	ret = i18n_ucollator_set_max_variable(NULL, I18N_UCOLLATOR_REORDER_CODE_SYMBOL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_max_variable_p
 * @since_tizen     4.0
 * @description     Gets the maximum reordering group, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_max_variable_p(void)
{
	i18n_ucollator_reorder_code_e group;

	ret = i18n_ucollator_get_max_variable(g_coll, &group);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_max_variable_n
 * @since_tizen     4.0
 * @description     Gets the maximum reordering group, passing invalid collator handle
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_max_variable_n(void)
{
	i18n_ucollator_reorder_code_e group;

	ret = i18n_ucollator_get_max_variable(NULL, &group);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_max_variable_n2
 * @since_tizen     4.0
 * @description     Gets the maximum reordering group, passing invalid group
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_max_variable_n2(void)
{
	ret = i18n_ucollator_get_max_variable(g_coll, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_variable_top_p
 * @since_tizen     4.0
 * @description     Gets the variable top value of a Collator, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_variable_top_p(void)
{
	uint32_t weight;

	ret = i18n_ucollator_get_variable_top(g_coll, &weight);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_variable_top_n
 * @since_tizen     4.0
 * @description     Gets the variable top value of a Collator, passing invalid collator handle
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_variable_top_n(void)
{
	uint32_t weight;

	ret = i18n_ucollator_get_variable_top(NULL, &weight);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_variable_top_n2
 * @since_tizen     4.0
 * @description     Gets the variable top value of a Collator, passing invalid weight
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_variable_top_n2(void)
{
	ret = i18n_ucollator_get_variable_top(g_coll, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_safe_clone_p
 * @since_tizen     4.0
 * @description     Gets the clone of the given collator handle, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_safe_clone_p(void)
{
	i18n_ucollator_h clone_coll = NULL;

	ret = i18n_ucollator_safe_clone(g_coll, &clone_coll);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(clone_coll, NULL);

	ret = i18n_ucollator_destroy(clone_coll);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_safe_clone_n
 * @since_tizen     4.0
 * @description     Gets the clone of the given collator handle, passing invalid collator handle
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_safe_clone_n(void)
{
	i18n_ucollator_h clone_coll = NULL;

	ret = i18n_ucollator_safe_clone(NULL, &clone_coll);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_safe_clone_n2
 * @since_tizen     4.0
 * @description     Gets the clone of the given collator handle, passing invalid clone handle
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_safe_clone_n2(void)
{
	ret = i18n_ucollator_safe_clone(g_coll, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_rules_ex_p
 * @since_tizen     4.0
 * @description     Gets the current rules, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_rules_ex_p(void)
{
	int32_t dest_size = 64;
	i18n_uchar dest[dest_size];
	int32_t current_rules;

	ret = i18n_ucollator_get_rules_ex(g_coll, I18N_UCOLLATOR_TAILORING_ONLY, dest_size,
										dest, &current_rules);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucollator_get_rules_ex(g_coll, I18N_UCOLLATOR_FULL_RULES, dest_size,
										dest, &current_rules);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_rules_ex_n
 * @since_tizen     4.0
 * @description     Gets the current rules, passing invalid collator handle
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_rules_ex_n(void)
{
	int32_t dest_size = 64;
	i18n_uchar dest[dest_size];
	int32_t current_rules;

	ret = i18n_ucollator_get_rules_ex(NULL, I18N_UCOLLATOR_TAILORING_ONLY, dest_size,
										dest, &current_rules);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_rules_ex_n2
 * @since_tizen     4.0
 * @description     Gets the current rules, passing invalid current rules
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_rules_ex_n2(void)
{
	int32_t dest_size = 64;
	i18n_uchar dest[dest_size];

	ret = i18n_ucollator_get_rules_ex(g_coll, I18N_UCOLLATOR_TAILORING_ONLY, dest_size,
										dest, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_locale_by_type_p
 * @since_tizen     4.0
 * @description     Gets the locale name of the collator, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_locale_by_type_p(void)
{
	const char *locale = NULL;

	ret = i18n_ucollator_get_locale_by_type(g_coll, I18N_ULOCALE_DATA_LOCALE_TYPE_VALID_LOCALE,
											&locale);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_locale_by_type_n
 * @since_tizen     4.0
 * @description     Gets the locale name of the collator, passing invalid collator handle
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_locale_by_type_n(void)
{
	const char *locale = NULL;

	ret = i18n_ucollator_get_locale_by_type(NULL, I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE,
											&locale);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_locale_by_type_n2
 * @since_tizen     4.0
 * @description     Gets the locale name of the collator, passing invalid locale
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_locale_by_type_n2(void)
{
	ret = i18n_ucollator_get_locale_by_type(g_coll, I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE,
											NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_tailored_set_p
 * @since_tizen     4.0
 * @description     Gets a Unicode set that contains all the characters and sequences tailored
 *                  in this collator, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_tailored_set_p(void)
{
	i18n_uset_h uset = NULL;

	ret = i18n_ucollator_get_tailored_set(g_coll, &uset);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(uset, NULL);
	i18n_uset_destroy(uset);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_tailored_set_n
 * @since_tizen     4.0
 * @description     Gets a Unicode set that contains all the characters and sequences tailored,
 *                  passing invalid collator handle and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_tailored_set_n(void)
{
	i18n_uset_h uset = NULL;

	ret = i18n_ucollator_get_tailored_set(NULL, &uset);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_get_tailored_set_n2
 * @since_tizen     4.0
 * @description     Gets a Unicode set that contains all the characters and sequences tailored,
 *                  passing invalid uset and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_get_tailored_set_n2(void)
{
	ret = i18n_ucollator_get_tailored_set(g_coll, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_clone_binary_p
 * @since_tizen     4.0
 * @description     Creates a binary image of a collator, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_clone_binary_p(void)
{
	int32_t dest_size = 64;
	uint8_t dest[dest_size];
	int32_t image_size;

	ret = i18n_ucollator_clone_binary(g_coll, dest_size, dest, &image_size);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(image_size, 0);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_clone_binary_n
 * @since_tizen     4.0
 * @description     Creates a binary image of a collator, passing invalid collator handle
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_clone_binary_n(void)
{
	int32_t dest_size = 64;
	uint8_t dest[dest_size];
	int32_t image_size;

	ret = i18n_ucollator_clone_binary(NULL, dest_size, dest, &image_size);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_clone_binary_n2
 * @since_tizen     4.0
 * @description     Creates a binary image of a collator, passing invalid dest
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_clone_binary_n2(void)
{
	int32_t dest_size = 64;
	int32_t image_size;

	ret = i18n_ucollator_clone_binary(g_coll, dest_size, NULL, &image_size);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_clone_binary_n3
 * @since_tizen     4.0
 * @description     Creates a binary image of a collator, passing invalid image size
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_clone_binary_n3(void)
{
	int32_t dest_size = 64;
	uint8_t dest[dest_size];

	ret = i18n_ucollator_clone_binary(g_coll, dest_size, dest, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_create_binary_p
 * @since_tizen     4.0
 * @description     Creates a new binary image of a collator, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_create_binary_p(void)
{
	int32_t dest_size = 64;
	uint8_t dest[dest_size];
	int32_t image_size;
	i18n_ucollator_h bin_coll = NULL;

	ret = i18n_ucollator_clone_binary(g_coll, dest_size, dest, &image_size);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucollator_create_binary(dest, image_size, g_coll, &bin_coll);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(bin_coll, NULL);
	i18n_ucollator_destroy(bin_coll);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_create_binary_n
 * @since_tizen     4.0
 * @description     Creates a new binary image of a collator, passing invalid base handle
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_create_binary_n(void)
{
	int32_t dest_size = 64;
	uint8_t dest[dest_size];
	int32_t image_size;
	i18n_ucollator_h bin_coll = NULL;

	ret = i18n_ucollator_clone_binary(g_coll, dest_size, dest, &image_size);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucollator_create_binary(dest, image_size, NULL, &bin_coll);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_create_binary_n2
 * @since_tizen     4.0
 * @description     Creates a new binary image of a collator, passing invalid collator handle
 *                  and checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_create_binary_n2(void)
{
	int32_t dest_size = 64;
	uint8_t dest[dest_size];
	int32_t image_size;

	ret = i18n_ucollator_clone_binary(g_coll, dest_size, dest, &image_size);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucollator_create_binary(dest, image_size, g_coll, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_destroy_n
 * @since_tizen     2.3
 * @description     Closes an empty collator handle, so error is expected.
 */
int utc_capi_base_utils_i18n_ucollator_destroy_n(void)
{
    int ret = I18N_ERROR_NONE;

    ret = i18n_ucollator_destroy( NULL );
    assert_eq( ret, I18N_ERROR_INVALID_PARAMETER );
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_str_collator_p
 * @since_tizen     2.3
 * @description     Compares two strings, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_str_collator_p(void)
{
    int ret = I18N_ERROR_NONE;
    i18n_ucollator_result_e result = I18N_UCOLLATOR_EQUAL;

    ret = i18n_ucollator_str_collator( g_coll, g_ustr, g_str_len, g_target, g_str_len, &result );
    assert_eq( ret, I18N_ERROR_NONE );
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_str_collator_n
 * @since_tizen     2.3
 * @description     Compares two strings passing invalid arguments,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_ucollator_str_collator_n(void)
{
    int ret = I18N_ERROR_NONE;
    i18n_ucollator_result_e result = I18N_UCOLLATOR_EQUAL;

    ret = i18n_ucollator_str_collator( NULL, NULL, -1, NULL, -1, &result );
    assert_eq( ret, I18N_ERROR_INVALID_PARAMETER );
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_equal_p
 * @since_tizen     2.3
 * @description     Compares two strings for equality, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_equal_p(void)
{
    int ret = I18N_ERROR_NONE;
    i18n_ubool equal = false;

    ret = i18n_ucollator_equal( g_coll, g_ustr, g_str_len, g_target, g_str_len, &equal );
    assert_eq( ret, I18N_ERROR_NONE );
    assert_eq( equal, true );
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_equal_n
 * @since_tizen     2.3
 * @description     Compares two invalid strings for equality, so error is expected.
 */
int utc_capi_base_utils_i18n_ucollator_equal_n(void)
{
    int ret = I18N_ERROR_NONE;

    ret = i18n_ucollator_equal( NULL, NULL, -1, NULL, -1, NULL);
    assert_eq( ret, I18N_ERROR_INVALID_PARAMETER );
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_set_strength_p
 * @since_tizen     2.3
 * @description     Sets the collation strength used in a collator,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_set_strength_p(void)
{
    int ret = I18N_ERROR_NONE;
    i18n_ucollator_strength_e strength = I18N_UCOLLATOR_DEFAULT;

    ret = i18n_ucollator_set_strength( g_coll, strength );
    assert_eq( ret, I18N_ERROR_NONE );
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_set_strength_n
 * @since_tizen     2.3
 * @description     Sets the collation strength to invalid collator handle,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_ucollator_set_strength_n(void)
{
    int ret = I18N_ERROR_NONE;
    i18n_ucollator_strength_e strength = I18N_UCOLLATOR_DEFAULT;

    ret = i18n_ucollator_set_strength( NULL, strength );
    assert_eq( ret, I18N_ERROR_INVALID_PARAMETER );

    ret = i18n_ucollator_set_strength( NULL, -1 );
    assert_eq( ret, I18N_ERROR_INVALID_PARAMETER );
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_set_attribute_p
 * @since_tizen     2.3
 * @description     Sets a universal attribute setter, checks error code.
 */
int utc_capi_base_utils_i18n_ucollator_set_attribute_p(void)
{
    int ret = I18N_ERROR_NONE;
    i18n_ucollator_attribute_e attr = I18N_UCOLLATOR_STRENGTH;
    i18n_ucollator_attribute_value_e val = I18N_UCOLLATOR_DEFAULT;

    ret = i18n_ucollator_set_attribute( g_coll, attr, val );
    assert_eq( ret, I18N_ERROR_NONE );

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ucollator_set_attribute_n
 * @since_tizen     2.3
 * @description     Sets a universal attribute setter to invalid collator,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_ucollator_set_attribute_n(void)
{
    int ret = I18N_ERROR_NONE;
    i18n_ucollator_attribute_e attr = I18N_UCOLLATOR_STRENGTH;
    i18n_ucollator_attribute_value_e val = I18N_UCOLLATOR_DEFAULT;

    ret = i18n_ucollator_set_attribute( NULL, attr, val );
    assert_eq( ret, I18N_ERROR_INVALID_PARAMETER );

    ret = i18n_ucollator_set_attribute( NULL, -1, -1 );
    assert_eq( ret, I18N_ERROR_INVALID_PARAMETER );

    return 0;
}
