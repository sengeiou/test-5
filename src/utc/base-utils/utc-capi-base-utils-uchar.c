#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

//& set: capi-base-utils-uchar

static int ret = I18N_ERROR_NONE;

const static int buf_size = 50;

static i18n_ubool do_sample(void *context, i18n_uchar32 code, i18n_uchar_u_char_name_choice_e name_choice, const char *name, int32_t length)
{
    int *counter = (int *) context;
    ++(*counter);
    return true;
}

static i18n_ubool count_titlecase_letters(const void *context, i18n_uchar32 start, i18n_uchar32 limit, i18n_uchar_category_e type)
{
    int *counter = (int *) context;
    if (I18N_UCHAR_U_TITLECASE_LETTER == type) {
        int i = start;
        for(; i < limit ; ++i)
            ++(*counter);
    }

    return true;
}

/**
 * @function        utc_capi_base_utils_uchar_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_uchar_startup(void)
{
}
/**
 * @function        utc_capi_base_utils_uchar_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_uchar_cleanup(void)
{
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_int_property_value_p
 * @since_tizen     2.3
 * @description     Gets the property value of a code point for all binary properties,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_uchar_get_int_property_value_p(void)
{
    i18n_uchar_uproperty_e which = I18N_UCHAR_BINARY_START;
    i18n_uchar32 c = 0xA;
    int32_t property_val = 0;

    for(; which < I18N_UCHAR_BINARY_LIMIT; which++) {
        ret = i18n_uchar_get_int_property_value(c, which, &property_val);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_int_property_value_p2
 * @since_tizen     2.3
 * @description     Gets the property value of a code point for all int properties,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_uchar_get_int_property_value_p2(void)
{
    i18n_uchar_uproperty_e which = I18N_UCHAR_INT_START;
    i18n_uchar32 c = 0xA;
    int32_t property_val = 0;

    for(; which < I18N_UCHAR_INT_LIMIT; which++) {
        ret = i18n_uchar_get_int_property_value(c, which, &property_val);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_int_property_value_p3
 * @since_tizen     2.3
 * @description     Gets the property value of a code point for all char properties,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_uchar_get_int_property_value_p3(void)
{
    i18n_uchar_uproperty_e which = I18N_UCHAR_MASK_START;
    i18n_uchar32 c = 0xA;
    int32_t property_val = 0;

    for(; which < I18N_UCHAR_MASK_LIMIT; which++) {
        ret = i18n_uchar_get_int_property_value(c, which, &property_val);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_int_property_value_n
 * @since_tizen     2.3
 * @description     Gets the property value of a code point passing invalid
 *                  output pointer, so error is expected.
 */
int utc_capi_base_utils_i18n_uchar_get_int_property_value_n(void)
{
    i18n_uchar_uproperty_e which = I18N_UCHAR_ASCII_HEX_DIGIT;

    ret = i18n_uchar_get_int_property_value(0, which, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_ublock_code_p
 * @since_tizen     2.3
 * @description     Gets the Unicode allocation block that contains the given character,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_uchar_get_ublock_code_p(void)
{
    i18n_uchar32 c = 0xA;
    i18n_uchar_ublock_code_e block_val;

    ret = i18n_uchar_get_ublock_code(c, &block_val);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_ublock_code_n
 * @since_tizen     2.3
 * @description     Gets the Unicode allocation block that contains the character,
 *                  passing invalid output pointer, so error is expected.
 */
int utc_capi_base_utils_i18n_uchar_get_ublock_code_n(void)
{
    ret = i18n_uchar_get_ublock_code(-1, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_has_binary_property_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_has_binary_property and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_has_binary_property_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_uchar_uproperty_e which = I18N_UCHAR_ALPHABETIC;
    i18n_ubool has_binary_property = false;

    ret = i18n_uchar_has_binary_property(c, which, &has_binary_property);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(has_binary_property, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_has_binary_property_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_has_binary_property and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_has_binary_property_p2(void)
{
    i18n_uchar32 c = 0x25;
    i18n_uchar_uproperty_e which = I18N_UCHAR_ALPHABETIC;
    i18n_ubool has_binary_property = true;

    ret = i18n_uchar_has_binary_property(c, which, &has_binary_property);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(has_binary_property, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_has_binary_property_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_has_binary_property passing invalid has_binary_property
 *                  and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_has_binary_property_n(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_uchar_uproperty_e which = I18N_UCHAR_ALPHABETIC;

    ret = i18n_uchar_has_binary_property(c, which, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_alphabetic_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_alphabetic and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_alphabetic_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_alphabetic = false;

    ret = i18n_uchar_is_alphabetic(c, &is_alphabetic);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_alphabetic, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_alphabetic_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_alphabetic and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_alphabetic_p2(void)
{
    i18n_uchar32 c = 0x25;
    i18n_ubool is_alphabetic = true;

    ret = i18n_uchar_is_alphabetic(c, &is_alphabetic);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_alphabetic, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_alphabetic_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_alphabetic passing invalid is_alphabetic and
 *                  checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_alphabetic_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_alphabetic(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_lowercase_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_lowercase and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_lowercase_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_lowercase = false;

    ret = i18n_uchar_is_lowercase(c, &is_lowercase);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_lowercase, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_lowercase_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_lowercase and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_lowercase_p2(void)
{
    i18n_uchar32 c = 0x41;
    i18n_ubool is_lowercase = true;

    ret = i18n_uchar_is_lowercase(c, &is_lowercase);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_lowercase, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_lowercase_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_lowercase passing invalid is_lowercase and
 *                  checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_lowercase_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_lowercase(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_uppercase_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_uppercase and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_uppercase_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_uppercase = true;

    ret = i18n_uchar_is_uppercase(c, &is_uppercase);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_uppercase, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_uppercase_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_uppercase and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_uppercase_p2(void)
{
    i18n_uchar32 c = 0x41;
    i18n_ubool is_uppercase = false;

    ret = i18n_uchar_is_uppercase(c, &is_uppercase);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_uppercase, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_uppercase_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_uppercase passing invalid is_uppercase and
 *                  checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_uppercase_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_uppercase(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_white_space_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_white_space and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_white_space_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_white_space = true;

    ret = i18n_uchar_is_white_space(c, &is_white_space);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_white_space, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_white_space_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_white_space and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_white_space_p2(void)
{
    i18n_uchar32 c = 0x20;
    i18n_ubool is_white_space = false;

    ret = i18n_uchar_is_white_space(c, &is_white_space);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_white_space, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_white_space_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_white_space passing invalid is_white_space and
 *                  checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_white_space_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_white_space(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_int_property_min_value_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_int_property_min_value and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_int_property_min_value_p(void)
{
    i18n_uchar_uproperty_e which = I18N_UCHAR_BIDI_CLASS;
    int32_t int_property_min_value;

    ret = i18n_uchar_get_int_property_min_value(which, &int_property_min_value);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(int_property_min_value, 0x0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_int_property_min_value_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_int_property_min_value and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_int_property_min_value_p2(void)
{
    i18n_uchar_uproperty_e which = I18N_UCHAR_SCRIPT;
    int32_t int_property_min_value;

    ret = i18n_uchar_get_int_property_min_value(which, &int_property_min_value);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(int_property_min_value, 0x0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_int_property_min_value_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_int_property_min_value passing invalid int_min_value
 *                  and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_get_int_property_min_value_n(void)
{
    i18n_uchar_uproperty_e which = I18N_UCHAR_NUMERIC_TYPE;

    ret = i18n_uchar_get_int_property_min_value(which, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_int_property_max_value_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_int_property_max_value and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_int_property_max_value_p(void)
{
    i18n_uchar_uproperty_e which = I18N_UCHAR_BIDI_CLASS;
    int32_t int_property_max_value = 0;

    ret = i18n_uchar_get_int_property_max_value(which, &int_property_max_value);
    assert_eq(ret, I18N_ERROR_NONE);
    assert(int_property_max_value > 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_int_property_max_value_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_int_property_max_value and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_int_property_max_value_p2(void)
{
    i18n_uchar_uproperty_e which = I18N_UCHAR_SCRIPT;
    int32_t int_property_max_value = 0;

    ret = i18n_uchar_get_int_property_max_value(which, &int_property_max_value);
    assert_eq(ret, I18N_ERROR_NONE);
    assert(int_property_max_value > 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_int_property_max_value_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_int_property_max_value passing invalid int_max_value
 *                  and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_get_int_property_max_value_n(void)
{
    i18n_uchar_uproperty_e which = I18N_UCHAR_NUMERIC_TYPE;

    ret = i18n_uchar_get_int_property_max_value(which, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_numeric_value_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_numeric_value and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_numeric_value_p(void)
{
    i18n_uchar32 c = 0x09E7;
    double numeric_value = 0;

    ret = i18n_uchar_get_numeric_value(c, &numeric_value);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(numeric_value, 1);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_numeric_value_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_numeric_value and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_numeric_value_p2(void)
{
    i18n_uchar32 c = 0x0AEA;
    double numeric_value = 0;

    ret = i18n_uchar_get_numeric_value(c, &numeric_value);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(numeric_value, 4);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_numeric_value_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_numeric_value passing invalid numeric_val and checks
 *                  for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_get_numeric_value_n(void)
{
    i18n_uchar32 c = 0x09E7;

    ret = i18n_uchar_get_numeric_value(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_lower_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_lower and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_lower_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_lower = false;

    ret = i18n_uchar_is_lower(c, &is_lower);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_lower, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_lower_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_lower and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_lower_p2(void)
{
    i18n_uchar32 c = 0x42;
    i18n_ubool is_lower = true;

    ret = i18n_uchar_is_lower(c, &is_lower);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_lower, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_lower_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_lower passing invalid islower and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_lower_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_lower(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_upper_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_upper and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_upper_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_upper = true;

    ret = i18n_uchar_is_upper(c, &is_upper);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_upper, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_upper_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_upper and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_upper_p2(void)
{
    i18n_uchar32 c = 0x42;
    i18n_ubool is_upper = false;

    ret = i18n_uchar_is_upper(c, &is_upper);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_upper, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_upper_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_upper passing invalid isupper and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_upper_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_upper(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_title_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_title and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_title_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_title = true;

    ret = i18n_uchar_is_title(c, &is_title);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_title, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_title_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_title and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_title_p2(void)
{
    i18n_uchar32 c = 0x01C8;
    i18n_ubool is_title = false;

    ret = i18n_uchar_is_title(c, &is_title);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_title, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_title_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_title passing invalid istitle and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_title_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_title(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_digit_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_digit and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_digit_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_digit = true;

    ret = i18n_uchar_is_digit(c, &is_digit);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_digit, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_digit_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_digit and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_digit_p2(void)
{
    i18n_uchar32 c = 0x37;
    i18n_ubool is_digit = false;

    ret = i18n_uchar_is_digit(c, &is_digit);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_digit, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_digit_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_digit passing invalid isdigit and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_digit_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_digit(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_alpha_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_alpha and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_alpha_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_alpha = false;

    ret = i18n_uchar_is_alpha(c, &is_alpha);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_alpha, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_alpha_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_alpha and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_alpha_p2(void)
{
    i18n_uchar32 c = 0x37;
    i18n_ubool is_alpha = true;

    ret = i18n_uchar_is_alpha(c, &is_alpha);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_alpha, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_alpha_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_alpha passing invalid isalpha and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_alpha_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_alpha(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_alnum_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_alnum and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_alnum_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_alnum = false;

    ret = i18n_uchar_is_alnum(c, &is_alnum);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_alnum, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_alnum_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_alnum and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_alnum_p2(void)
{
    i18n_uchar32 c = 0x20;
    i18n_ubool is_alnum = true;

    ret = i18n_uchar_is_alnum(c, &is_alnum);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_alnum, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_alnum_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_alnum passing invalid isalnum and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_alnum_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_alnum(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_xdigit_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_xdigit and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_xdigit_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_xdigit = true;

    ret = i18n_uchar_is_xdigit(c, &is_xdigit);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_xdigit, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_xdigit_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_xdigit and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_xdigit_p2(void)
{
    i18n_uchar32 c = 0x37;
    i18n_ubool is_xdigit = false;

    ret = i18n_uchar_is_xdigit(c, &is_xdigit);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_xdigit, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_xdigit_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_xdigit passing invalid isxdigit and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_xdigit_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_xdigit(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_punct_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_punct and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_punct_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_punct = true;

    ret = i18n_uchar_is_punct(c, &is_punct);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_punct, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_punct_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_punct and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_punct_p2(void)
{
    i18n_uchar32 c = 0x2018;
    i18n_ubool is_punct = false;

    ret = i18n_uchar_is_punct(c, &is_punct);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_punct, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_punct_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_punct passing invalid ispunct and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_punct_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_punct(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_graph_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_graph and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_graph_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_graph = false;

    ret = i18n_uchar_is_graph(c, &is_graph);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_graph, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_graph_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_graph and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_graph_p2(void)
{
    i18n_uchar32 c = 0x20;
    i18n_ubool is_graph = true;

    ret = i18n_uchar_is_graph(c, &is_graph);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_graph, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_graph_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_graph passing invalid isgraph and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_graph_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_graph(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_blank_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_blank and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_blank_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_blank = true;

    ret = i18n_uchar_is_blank(c, &is_blank);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_blank, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_blank_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_blank and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_blank_p2(void)
{
    i18n_uchar32 c = 0x09;
    i18n_ubool is_blank = false;

    ret = i18n_uchar_is_blank(c, &is_blank);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_blank, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_blank_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_blank passing invalid isblank and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_blank_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_blank(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_defined_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_defined and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_defined_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_defined = false;

    ret = i18n_uchar_is_defined(c, &is_defined);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_defined, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_defined_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_defined and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_defined_p2(void)
{
    i18n_uchar32 c = 0xFDD0;
    i18n_ubool is_defined = true;

    ret = i18n_uchar_is_defined(c, &is_defined);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_defined, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_defined_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_defined passing invalid isdefined and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_defined_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_defined(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_space_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_space and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_space_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_space = true;

    ret = i18n_uchar_is_space(c, &is_space);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_space, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_space_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_space and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_space_p2(void)
{
    i18n_uchar32 c = 0x20;
    i18n_ubool is_space = false;

    ret = i18n_uchar_is_space(c, &is_space);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_space, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_space_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_space passing invalid isspace and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_space_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_space(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_java_space_char_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_java_space_char and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_java_space_char_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_java_space_char = true;

    ret = i18n_uchar_is_java_space_char(c, &is_java_space_char);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_java_space_char, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_java_space_char_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_java_space_char and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_java_space_char_p2(void)
{
    i18n_uchar32 c = 0x2028;
    i18n_ubool is_java_space_char = false;

    ret = i18n_uchar_is_java_space_char(c, &is_java_space_char);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_java_space_char, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_java_space_char_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_java_space_char passing invalid is_java_space_char
 *                  and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_java_space_char_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_java_space_char(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_whitespace_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_whitespace and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_whitespace_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_whitespace = true;

    ret = i18n_uchar_is_whitespace(c, &is_whitespace);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_whitespace, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_whitespace_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_whitespace and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_whitespace_p2(void)
{
    i18n_uchar32 c = 0x20;
    i18n_ubool is_whitespace = false;

    ret = i18n_uchar_is_whitespace(c, &is_whitespace);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_whitespace, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_whitespace_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_whitespace passing invalid is_whitespace and checks
 *                  for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_whitespace_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_whitespace(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_control_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_control and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_control_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_control = true;

    ret = i18n_uchar_is_control(c, &is_control);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_control, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_control_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_control and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_control_p2(void)
{
    i18n_uchar32 c = 0x7F;
    i18n_ubool is_control = false;

    ret = i18n_uchar_is_control(c, &is_control);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_control, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_control_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_control passing invalid iscntrl and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_control_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_control(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_iso_control_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_iso_control and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_iso_control_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_iso_control = true;

    ret = i18n_uchar_is_iso_control(c, &is_iso_control);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_iso_control, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_iso_control_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_iso_control and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_iso_control_p2(void)
{
    i18n_uchar32 c = 0x1F;
    i18n_ubool is_iso_control = false;

    ret = i18n_uchar_is_iso_control(c, &is_iso_control);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_iso_control, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_iso_control_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_iso_control passing invalid is_iso_control and checks
 *                  for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_iso_control_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_iso_control(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_printable_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_printable and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_printable_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_print = false;

    ret = i18n_uchar_is_printable(c, &is_print);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_print, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_printable_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_printable and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_printable_p2(void)
{
    i18n_uchar32 c = 0x01;
    i18n_ubool is_print = true;

    ret = i18n_uchar_is_printable(c, &is_print);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_print, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_printable_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_printable passing invalid isprint and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_printable_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_printable(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_base_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_base and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_base_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_base = false;

    ret = i18n_uchar_is_base(c, &is_base);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_base, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_base_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_base and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_base_p2(void)
{
    i18n_uchar32 c = 0x20;
    i18n_ubool is_base = true;

    ret = i18n_uchar_is_base(c, &is_base);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_base, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_base_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_base passing invalid isbase and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_base_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_base(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_direction_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_direction and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_char_direction_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_uchar_direction_e char_direction = I18N_UCHAR_U_RIGHT_TO_LEFT;

    ret = i18n_uchar_char_direction(c, &char_direction);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(char_direction, I18N_UCHAR_U_LEFT_TO_RIGHT);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_direction_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_direction and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_char_direction_p2(void)
{
    i18n_uchar32 c = 0x06FF;
    i18n_uchar_direction_e char_direction = I18N_UCHAR_U_LEFT_TO_RIGHT;

    ret = i18n_uchar_char_direction(c, &char_direction);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(char_direction, I18N_UCHAR_U_RIGHT_TO_LEFT_ARABIC);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_direction_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_direction passing invalid direction and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_char_direction_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_char_direction(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_mirrored_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_mirrored and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_mirrored_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_mirrored = true;

    ret = i18n_uchar_is_mirrored(c, &is_mirrored);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_mirrored, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_mirrored_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_mirrored and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_mirrored_p2(void)
{
    i18n_uchar32 c = 0x7D;
    i18n_ubool is_mirrored = false;

    ret = i18n_uchar_is_mirrored(c, &is_mirrored);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_mirrored, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_mirrored_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_mirrored passing invalid is_mirrored and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_mirrored_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_mirrored(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_mirror_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_mirror and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_char_mirror_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_uchar32 char_mirror = 0x019C;

    ret = i18n_uchar_char_mirror(c, &char_mirror);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(char_mirror, c);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_mirror_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_mirror and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_char_mirror_p2(void)
{
    i18n_uchar32 c = 0x7D;
    i18n_uchar32 char_mirror = 0x0250;
    i18n_uchar32 result = 0x7B;

    ret = i18n_uchar_char_mirror(c, &char_mirror);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(char_mirror, result);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_mirror_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_mirror passing invalid char_mirror and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_char_mirror_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_char_mirror(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_bidi_paired_bracket_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_bidi_paired_bracket and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_bidi_paired_bracket_p(void)
{
    i18n_uchar32 c = 0x28;
    i18n_uchar32 bidi_paired_bracket = c;

    ret = i18n_uchar_get_bidi_paired_bracket(c, &bidi_paired_bracket);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(bidi_paired_bracket, 0x29);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_bidi_paired_bracket_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_bidi_paired_bracket and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_bidi_paired_bracket_p2(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_uchar32 bidi_paired_bracket = c;

    ret = i18n_uchar_get_bidi_paired_bracket(c, &bidi_paired_bracket);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(bidi_paired_bracket, 0x6D);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_bidi_paired_bracket_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_bidi_paired_bracket passing invalid bidi_paired_bracket and checks
 *                  for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_get_bidi_paired_bracket_n(void)
{
    i18n_uchar32 c = 0x28;

    ret = i18n_uchar_get_bidi_paired_bracket(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_type_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_type and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_char_type_p(void)
{
    i18n_uchar32 c = 0x6D;
    int8_t char_type = 0;

    ret = i18n_uchar_char_type(c, &char_type);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(char_type, 0x2);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_type_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_type and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_char_type_p2(void)
{
    i18n_uchar32 c = 0x24;
    int8_t char_type = 0;

    ret = i18n_uchar_char_type(c, &char_type);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(char_type, 0x19);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_type_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_type passing invalid char_type and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_char_type_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_char_type(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_types_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_enum_char_types and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_enum_char_types_p(void)
{
    int sample_counter = 0;
    int titlecase_quantity = 31;

    ret = i18n_uchar_enum_char_types(count_titlecase_letters, (void *)(&sample_counter));
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(sample_counter, titlecase_quantity);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_enum_char_types_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_enum_char_types passing invalid enum_char_type_cb and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_enum_char_types_n(void)
{
    ret = i18n_uchar_enum_char_types(NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_combining_class_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_combining_class and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_combining_class_p(void)
{
    i18n_uchar32 c = 0x6D;
    uint8_t combining_class = 1;

    ret = i18n_uchar_get_combining_class(c, &combining_class);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(combining_class, 0x0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_combining_class_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_combining_class and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_combining_class_p2(void)
{
    i18n_uchar32 c = 0x1BAB;
    uint8_t combining_class = 1;

    ret = i18n_uchar_get_combining_class(c, &combining_class);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(combining_class, 0x9);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_combining_class_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_combining_class passing invalid combining_class and checks for
 *                  an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_get_combining_class_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_get_combining_class(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_digit_value_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_digit_value and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_char_digit_value_p(void)
{
    i18n_uchar32 c = 0x39;
    int32_t char_digit_value = 0;

    ret = i18n_uchar_char_digit_value(c, &char_digit_value);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(char_digit_value, 9);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_digit_value_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_digit_value and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_char_digit_value_p2(void)
{
    i18n_uchar32 c = 0x0663;
    int32_t char_digit_value = 0;

    ret = i18n_uchar_char_digit_value(c, &char_digit_value);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(char_digit_value, 3);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_digit_value_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_digit_value passing invalid char_digit_value and checks
 *                  for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_char_digit_value_n(void)
{
    i18n_uchar32 c = 0x39;

    ret = i18n_uchar_char_digit_value(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_name_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_char_name_p(void)
{
    i18n_uchar32 c = 0x03B1;
    i18n_uchar_u_char_name_choice_e name_choice = I18N_UCHAR_U_UNICODE_CHAR_NAME;
    char buffer[buf_size];
    int32_t name_length;

    ret = i18n_uchar_char_name(c, name_choice, buffer, buf_size, &name_length);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(buffer, "GREEK SMALL LETTER ALPHA"), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_name_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_char_name_p2(void)
{
    i18n_uchar32 c = 0x0E9D;
    i18n_uchar_u_char_name_choice_e name_choice = I18N_UCHAR_U_CHAR_NAME_ALIAS;
    char buffer[buf_size];
    int32_t name_length;

    ret = i18n_uchar_char_name(c, name_choice, buffer, buf_size, &name_length);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(buffer, "LAO LETTER FO FON"), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_name_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_name passing invalid name_length and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_char_name_n(void)
{
    i18n_uchar32 c = 0x03B1;
    i18n_uchar_u_char_name_choice_e name_choice = I18N_UCHAR_U_UNICODE_CHAR_NAME;
    char buffer[buf_size];

    ret = i18n_uchar_char_name(c, name_choice, buffer, buf_size, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_name_n2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_name passing invalid name_length and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_char_name_n2(void)
{
    i18n_uchar32 c = 0x03B1;
    i18n_uchar_u_char_name_choice_e name_choice = I18N_UCHAR_U_UNICODE_CHAR_NAME;
    int32_t name_lenght;

    ret = i18n_uchar_char_name(c, name_choice, NULL, buf_size, &name_lenght);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_from_name_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_from_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_char_from_name_p(void)
{
    i18n_uchar_u_char_name_choice_e name_choice = I18N_UCHAR_U_UNICODE_CHAR_NAME;
    const char *name = "GREEK SMALL LETTER ALPHA";
    i18n_uchar32 char_from_name;

    ret = i18n_uchar_char_from_name(name_choice, name, &char_from_name);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(char_from_name, 0x03B1);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_from_name_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_from_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_char_from_name_p2(void)
{
    i18n_uchar_u_char_name_choice_e name_choice = I18N_UCHAR_U_CHAR_NAME_ALIAS;
    const char *name = "LAO LETTER FO FON";
    i18n_uchar32 char_from_name;

    ret = i18n_uchar_char_from_name(name_choice, name, &char_from_name);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(char_from_name, 0x0E9D);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_from_name_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_from_name passing invalid char_from_name and checks
 *                  for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_char_from_name_n(void)
{
    i18n_uchar_u_char_name_choice_e name_choice = I18N_UCHAR_U_UNICODE_CHAR_NAME;
    const char *name = "GREEK SMALL LETTER ALPHA";

    ret = i18n_uchar_char_from_name(name_choice, name, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_from_name_n2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_from_name passing invalid char_from_name and checks
 *                  for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_char_from_name_n2(void)
{
    i18n_uchar_u_char_name_choice_e name_choice = I18N_UCHAR_U_CHAR_NAME_ALIAS;
    const char *name = "CAN";
    i18n_uchar32 char_from_name;

    ret = i18n_uchar_char_from_name(name_choice, name, &char_from_name);
    assert_eq(ret, I18N_ERROR_ILLEGAL_CHAR_FOUND);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_from_name_n3
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_from_name passing invalid char_from_name and checks
 *                  for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_char_from_name_n3(void)
{
    i18n_uchar_u_char_name_choice_e name_choice = I18N_UCHAR_U_UNICODE_CHAR_NAME;
    i18n_uchar32 char_from_name;

    ret = i18n_uchar_char_from_name(name_choice, NULL, &char_from_name);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_enum_char_names_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_enum_char_names and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_enum_char_names_p(void)
{
    i18n_uchar32 start = 0x6A;
    i18n_uchar32 limit = 0x6F;
    i18n_uchar_u_char_name_choice_e name_choice = I18N_UCHAR_U_UNICODE_CHAR_NAME;

    int sample_counter = 0;
    ret = i18n_uchar_enum_char_names(start, limit, do_sample, (void *)(&sample_counter), name_choice);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(sample_counter, 5);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_enum_char_names_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_name_char_types passing invalid enum_char_name_cb and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_enum_char_names_n(void)
{
    i18n_uchar32 start = 0x6A;
    i18n_uchar32 limit = 0x6F;
    i18n_uchar_u_char_name_choice_e name_choice = I18N_UCHAR_U_UNICODE_CHAR_NAME;

    int sample_counter = 0;
    ret = i18n_uchar_enum_char_names(start, limit, NULL, (void *)(&sample_counter), name_choice);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_property_name_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_property_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_property_name_p(void)
{
    i18n_uchar_uproperty_e property = I18N_UCHAR_GENERAL_CATEGORY_MASK;
    i18n_uchar_u_property_name_choice_e name_choice = I18N_UCHAR_U_LONG_PROPERTY_NAME;
    const char *name;

    ret = i18n_uchar_get_property_name(property, name_choice, &name);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(name, "General_Category_Mask"), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_property_name_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_property_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_property_name_p2(void)
{
    i18n_uchar_uproperty_e property = I18N_UCHAR_INVALID_CODE;
    i18n_uchar_u_property_name_choice_e name_choice = I18N_UCHAR_U_LONG_PROPERTY_NAME;
    const char *name;

    ret = i18n_uchar_get_property_name(property, name_choice, &name);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(name, NULL);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_property_name_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_property_name passing invalid *name and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_get_property_name_n(void)
{
    i18n_uchar_uproperty_e property = I18N_UCHAR_GENERAL_CATEGORY_MASK;
    i18n_uchar_u_property_name_choice_e name_choice = I18N_UCHAR_U_LONG_PROPERTY_NAME;

    ret = i18n_uchar_get_property_name(property, name_choice, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_property_enum_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_property_enum and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_property_enum_p(void)
{
    const char *alias = "General_Category_Mask";
    i18n_uchar_uproperty_e property_enum = I18N_UCHAR_ALPHABETIC;

    ret = i18n_uchar_get_property_enum(alias, &property_enum);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(property_enum, I18N_UCHAR_GENERAL_CATEGORY_MASK);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_property_enum_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_property_enum and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_property_enum_p2(void)
{
    const char *alias = "aaaaa";
    i18n_uchar_uproperty_e property_enum = I18N_UCHAR_ALPHABETIC;

    ret = i18n_uchar_get_property_enum(alias, &property_enum);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(property_enum, I18N_UCHAR_INVALID_CODE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_property_enum_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_property_enum passing invalid property_enum and checks
 *                  for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_get_property_enum_n(void)
{
    const char *alias = "General_Category_Mask";

    ret = i18n_uchar_get_property_enum(alias, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_property_value_name_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_property_value_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_property_value_name_p(void)
{
    i18n_uchar_uproperty_e property = I18N_UCHAR_WORD_BREAK;
    int32_t value = 3;
    i18n_uchar_u_property_name_choice_e name_choice = I18N_UCHAR_U_LONG_PROPERTY_NAME;
    const char *name;

    ret = i18n_uchar_get_property_value_name(property, value, name_choice, &name);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(name, "Katakana"), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_property_value_name_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_property_value_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_property_value_name_p2(void)
{
    i18n_uchar_uproperty_e property = I18N_UCHAR_GENERAL_CATEGORY;
    int32_t value = 0;
    i18n_uchar_u_property_name_choice_e name_choice = I18N_UCHAR_U_LONG_PROPERTY_NAME;
    const char *name;

    ret = i18n_uchar_get_property_value_name(property, value, name_choice, &name);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(name, "Unassigned"), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_property_value_name_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_property_value_name passing invalid *name and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_get_property_value_name_n(void)
{
    i18n_uchar_uproperty_e property = I18N_UCHAR_GENERAL_CATEGORY;
    int32_t value = 1;
    i18n_uchar_u_property_name_choice_e name_choice = I18N_UCHAR_U_LONG_PROPERTY_NAME;

    ret = i18n_uchar_get_property_value_name(property, value, name_choice, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_property_value_enum_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_property_value_enum and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_property_value_enum_p(void)
{
    i18n_uchar_uproperty_e property = I18N_UCHAR_GENERAL_CATEGORY;
    const char *alias = "Ll";
    int32_t value_enum = 0;

    ret = i18n_uchar_get_property_value_enum(property, alias, &value_enum);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(value_enum, 2);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_property_value_enum_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_property_value_enum and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_property_value_enum_p2(void)
{
    i18n_uchar_uproperty_e property = I18N_UCHAR_MASK_LIMIT;
    const char *alias = "Lc";
    int32_t value_enum = 0;

    ret = i18n_uchar_get_property_value_enum(property, alias, &value_enum);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(value_enum, I18N_UCHAR_INVALID_CODE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_property_value_enum_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_property_value_enum passing invalid value_enum and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_get_property_value_enum_n(void)
{
    i18n_uchar_uproperty_e property = I18N_UCHAR_GENERAL_CATEGORY_MASK;
    const char *alias = "Cased_Letter";

    ret = i18n_uchar_get_property_value_enum(property, alias, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_id_start_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_id_start and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_id_start_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_id_start = false;

    ret = i18n_uchar_is_id_start(c, &is_id_start);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_id_start, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_id_start_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_id_start and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_id_start_p2(void)
{
    i18n_uchar32 c = 0x5F;
    i18n_ubool is_id_start = true;

    ret = i18n_uchar_is_id_start(c, &is_id_start);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_id_start, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_id_start_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_id_start passing invalid is_id_start and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_id_start_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_id_start(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_id_part_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_id_part and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_id_part_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_id_part = false;

    ret = i18n_uchar_is_id_part(c, &is_id_part);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_id_part, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_id_part_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_id_part and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_id_part_p2(void)
{
    i18n_uchar32 c = 0x20;
    i18n_ubool is_id_part = true;

    ret = i18n_uchar_is_id_part(c, &is_id_part);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_id_part, false);

    return 0;
}


/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_id_part_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_id_part passing invalid is_id_part and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_id_part_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_id_part(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_id_ignorable_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_id_ignorable and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_id_ignorable_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_id_ignorable = true;

    ret = i18n_uchar_is_id_ignorable(c, &is_id_ignorable);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_id_ignorable, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_id_ignorable_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_id_ignorable and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_id_ignorable_p2(void)
{
    i18n_uchar32 c = 0x07;
    i18n_ubool is_id_ignorable = false;

    ret = i18n_uchar_is_id_ignorable(c, &is_id_ignorable);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_id_ignorable, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_id_ignorable_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_id_ignorable passing invalid is_id_ignorable and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_id_ignorable_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_id_ignorable(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_java_id_start_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_java_id_start and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_java_id_start_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_java_id_start = false;

    ret = i18n_uchar_is_java_id_start(c, &is_java_id_start);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_java_id_start, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_java_id_start_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_java_id_start and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_java_id_start_p2(void)
{
    i18n_uchar32 c = 0x37;
    i18n_ubool is_java_id_start = true;

    ret = i18n_uchar_is_java_id_start(c, &is_java_id_start);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_java_id_start, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_java_id_start_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_java_id_start passing invalid is_java_id_start and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_java_id_start_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_java_id_start(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_java_id_part_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_java_id_part and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_java_id_part_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_ubool is_java_id_part = false;

    ret = i18n_uchar_is_java_id_part(c, &is_java_id_part);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_java_id_part, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_java_id_part_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_java_id_part and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_is_java_id_part_p2(void)
{
    i18n_uchar32 c = 0x20;
    i18n_ubool is_java_id_part = true;

    ret = i18n_uchar_is_java_id_part(c, &is_java_id_part);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_java_id_part, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_is_java_id_part_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_is_java_id_part passing invalid is_java_id_part and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_is_java_id_part_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_is_java_id_part(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_to_lower_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_to_lower and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_to_lower_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_uchar32 to_lower;

    ret = i18n_uchar_to_lower(c, &to_lower);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(to_lower, c);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_to_lower_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_to_lower and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_to_lower_p2(void)
{
    i18n_uchar32 c = 0x4D;
    i18n_uchar32 to_lower;

    ret = i18n_uchar_to_lower(c, &to_lower);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(to_lower, 0x6D);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_to_lower_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_to_lower passing invalid lower and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_to_lower_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_to_lower(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_to_upper_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_to_upper and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_to_upper_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_uchar32 to_upper;

    ret = i18n_uchar_to_upper(c, &to_upper);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(to_upper, 0x4D);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_to_upper_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_to_upper and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_to_upper_p2(void)
{
    i18n_uchar32 c = 0x4D;
    i18n_uchar32 to_upper;

    ret = i18n_uchar_to_upper(c, &to_upper);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(to_upper, c);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_to_upper_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_to_upper passing invalid upper and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_to_upper_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_to_upper(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_to_title_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_to_title and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_to_title_p(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_uchar32 to_title;

    ret = i18n_uchar_to_title(c, &to_title);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(to_title, 0x4D);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_to_title_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_to_title and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_to_title_p2(void)
{
    i18n_uchar32 c = 0x2B;
    i18n_uchar32 to_title;

    ret = i18n_uchar_to_title(c, &to_title);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(to_title, c);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_to_title_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_to_title passing invalid title and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_to_title_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_to_title(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_fold_case_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_fold_case and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_fold_case_p(void)
{
    i18n_uchar32 c = 0x6D;
    uint32_t options = I18N_U_FOLD_CASE_DEFAULT;
    i18n_uchar32 code_point = 0;

    ret = i18n_uchar_fold_case(c, options, &code_point);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(code_point, c);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_fold_case_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_fold_case and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_fold_case_p2(void)
{
    i18n_uchar32 c = 0xCD;
    uint32_t options = I18N_U_FOLD_CASE_DEFAULT;
    i18n_uchar32 code_point = 0;

    ret = i18n_uchar_fold_case(c, options, &code_point);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(code_point, 0xED);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_fold_case_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_fold_case passing invalid code_point and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_fold_case_n(void)
{
    i18n_uchar32 c = 0x6D;
    uint32_t options = I18N_U_FOLD_CASE_DEFAULT;

    ret = i18n_uchar_fold_case(c, options, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_digit_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_digit and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_digit_p(void)
{
    i18n_uchar32 ch = 0x36;
    int8_t radix = 10;
    int32_t numerical_value = 0;

    ret = i18n_uchar_digit(ch, radix, &numerical_value);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(numerical_value, 0x6);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_digit_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_digit and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_digit_p2(void)
{
    i18n_uchar32 ch = 0x39;
    int8_t radix = 3;
    int32_t numerical_value = 0;

    ret = i18n_uchar_digit(ch, radix, &numerical_value);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(numerical_value, -1);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_digit_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_digit passing invalid numerical_value and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_digit_n(void)
{
    i18n_uchar32 ch = 0x36;
    int8_t radix = 10;

    ret = i18n_uchar_digit(ch, radix, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_for_digit_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_for_digit and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_for_digit_p(void)
{
    int32_t digit = 7;
    int8_t radix = 10;
    i18n_uchar32 representation = 0;

    ret = i18n_uchar_for_digit(digit, radix, &representation);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(representation, 0x37);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_for_digit_p2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_for_digit and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_for_digit_p2(void)
{
    int32_t digit = 14;
    int8_t radix = 16;
    i18n_uchar32 representation = 0;

    ret = i18n_uchar_for_digit(digit, radix, &representation);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(representation, 0x65);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_for_digit_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_for_digit passing invalid representation and checks for an invalid
 *                  parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_for_digit_n(void)
{
    int32_t digit = 7;
    int8_t radix = 10;

    ret = i18n_uchar_for_digit(digit, radix, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_age_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_age and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_char_age_p(void)
{
    i18n_uchar32 c = 0x1207;
    i18n_uversion_info char_age;
    i18n_uversion_info version = {4, 1, 0};


    ret = i18n_uchar_char_age(c, &char_age);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(memcmp(char_age, version, 3), 0);


    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_char_age_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_char_age passing invalid length and checks
 *                  for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_char_age_n(void)
{
    i18n_uchar32 c = 0x6D;

    ret = i18n_uchar_char_age(c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_unicode_version_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_unicode_version and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_unicode_version_p(void)
{
    i18n_uversion_info version_array;

    ret = i18n_uchar_get_unicode_version(version_array);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_unicode_version_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_unicode_version passing invalid length and checks
 *                  for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_get_unicode_version_n(void)
{
    ret = i18n_uchar_get_unicode_version(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_fc_nfkc_closure_p
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_fc_nfkc_closure and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uchar_get_fc_nfkc_closure_p(void)
{
    i18n_uchar32 c = 0x2121;
    i18n_uchar dest[buf_size];
    i18n_uchar result[buf_size];
    int32_t length;

    i18n_ustring_copy_ua(result, "tel");
    ret = i18n_uchar_get_fc_nfkc_closure(c, dest, buf_size, &length);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(i18n_ustring_mem_compare(dest, result, 4), 0);


    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_fc_nfkc_closure_n
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_fc_nfkc_closure passing invalid length and checks
 *                  for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_get_fc_nfkc_closure_n(void)
{
    i18n_uchar32 c = 0x6D;
    i18n_uchar dest[buf_size];

    ret = i18n_uchar_get_fc_nfkc_closure(c, dest, buf_size, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uchar_get_fc_nfkc_closure_n2
 * @since_tizen     4.0
 * @description     Calls i18n_uchar_get_fc_nfkc_closure passing invalid destination buffer and checks
 *                  for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_get_fc_nfkc_closure_n2(void)
{
    i18n_uchar32 c = 0x6D;
    int32_t length;

    ret = i18n_uchar_get_fc_nfkc_closure(c, NULL, buf_size, &length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
