#include "assert.h"
#include <string.h>
#include <utils_i18n.h>

#define BUF_SIZE 64

static int ret = I18N_ERROR_NONE;
static i18n_unumber_format_h num_format = NULL;

static i18n_uchar test_variable[] = { '1', ',', '9', '9', '4', 0x00 };
static i18n_uchar test_variable2[] = { '-', '1', ',', '9', '9', '4', 0x00 };
static i18n_uchar test_variable3[] = { '-', '6', '4', '3', 0x00 };
static i18n_uchar test_variable4[] = { '2', ',', '0', '1', '4', 0x00 };
static i18n_uchar test_variable5[] = { '-', '2', ',', '0', '1', '4', 0x00 };

/**
 * @function        utc_capi_base_utils_unumber_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_unumber_startup(void)
{
    ret = i18n_unumber_create(I18N_UNUMBER_DECIMAL, NULL, -1, I18N_ULOCALE_US, NULL, &num_format);
}

/**
 * @function        utc_capi_base_utils_unumber_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_unumber_cleanup(void)
{
    if(NULL != num_format) {
        i18n_unumber_destroy(num_format);
    }
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_create_p
 * @since_tizen     2.3
 * @description     Creates and returns a new number handle for formatting
 *                  and parsing numbers.
 */
int utc_capi_base_utils_i18n_unumber_create_p(void)
{
    if(NULL != num_format) {
        i18n_unumber_destroy(num_format);
    }

    i18n_unumber_format_style_e style = I18N_UNUMBER_PATTERN_DECIMAL;
    i18n_uchar pattern[5] = { '#', ',', '#', '#', 0 };

    for(; style <= I18N_UNUMBER_PATTERN_RULEBASED; style++) {
        ret = i18n_unumber_create(style, pattern, -1, NULL, NULL, &num_format);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_create_n
 * @since_tizen     2.3
 * @description     Creates and returns a new number handle for formatting
 *                  and parsing numbers without output parameter,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_create_n(void)
{
    ret = i18n_unumber_create(I18N_UNUMBER_PATTERN_DECIMAL, NULL, -1, NULL, NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_destroy_p
 * @since_tizen     2.3
 * @description     Destroys a number handle, checks error code.
 */
int utc_capi_base_utils_i18n_unumber_destroy_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    ret = i18n_unumber_destroy(num_format);

    assert_eq(ret, I18N_ERROR_NONE);
    num_format = NULL;

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_destroy_n
 * @since_tizen     2.3
 * @description     Destroys an invalid number handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_destroy_n(void)
{
    ret = i18n_unumber_destroy(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_symbol_p
 * @since_tizen     2.3
 * @description     Gets a symbol associated with a number handle,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_unumber_get_symbol_p(void)
{
    i18n_unumber_format_style_e style = I18N_UNUMBER_PATTERN_DECIMAL;
    i18n_uchar buffer[BUF_SIZE];
    int len_symbol = 0;

    if(NULL != num_format) {
        i18n_unumber_destroy(num_format);
    }

    for(; style <= I18N_UNUMBER_SCIENTIFIC; style++) {
        ret = i18n_unumber_create(style, NULL, -1, I18N_ULOCALE_US, NULL, &num_format);
        assert_eq(ret, I18N_ERROR_NONE);
        assert_neq(num_format, NULL);

        i18n_unumber_format_symbol_e symbol = I18N_UNUMBER_DECIMAL_SEPARATOR_SYMBOL;

        for(; symbol < I18N_UNUMBER_FORMAT_SYMBOL_COUNT; symbol++) {
            ret = i18n_unumber_get_symbol(num_format, symbol, buffer, BUF_SIZE, &len_symbol);
            assert_eq(ret, I18N_ERROR_NONE);
            assert_geq(len_symbol, 0);
        }

        i18n_unumber_destroy(num_format);
        num_format = NULL;
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_symbol_n
 * @since_tizen     2.3
 * @description     Gets a symbol associated with an invalid number handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_get_symbol_n(void)
{
    int len_symbol = 0;
    i18n_uchar buffer[BUF_SIZE];

    ret = i18n_unumber_get_symbol(NULL, I18N_UNUMBER_DIGIT_SYMBOL, buffer, BUF_SIZE, &len_symbol);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_symbol_n2
 * @since_tizen     2.3
 * @description     Gets a symbol associated with a number passing invalid symbol,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_get_symbol_n2(void)
{
    int len_symbol = 0;
    i18n_uchar buffer[BUF_SIZE];

    ret = i18n_unumber_get_symbol(num_format, -1, buffer, BUF_SIZE, &len_symbol);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_symbol_n3
 * @since_tizen     2.3
 * @description     Gets a symbol associated with a number passing invalid buffer,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_get_symbol_n3(void)
{
    int len_symbol = 0;

    ret = i18n_unumber_get_symbol(num_format, I18N_UNUMBER_DIGIT_SYMBOL, NULL, BUF_SIZE, &len_symbol);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_symbol_n4
 * @since_tizen     2.3
 * @description     Gets a symbol associated with a number passing invalid size,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_get_symbol_n4(void)
{
    int len_symbol = 0;
    i18n_uchar buffer[BUF_SIZE];

    ret = i18n_unumber_get_symbol(num_format, I18N_UNUMBER_DIGIT_SYMBOL, buffer, -1, &len_symbol);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_symbol_n5
 * @since_tizen     2.3
 * @description     Gets a symbol associated with a number passing invalid symbol length,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_get_symbol_n5(void)
{
    i18n_uchar buffer[BUF_SIZE];

    ret = i18n_unumber_get_symbol(num_format, I18N_UNUMBER_DIGIT_SYMBOL, buffer, BUF_SIZE, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_clone_p
 * @since_tizen     2.3.1
 * @description     Creates a copy of a number handle,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_unumber_clone_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_unumber_format_h num_format_clone;

    ret = i18n_unumber_clone(num_format, &num_format_clone);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_unumber_destroy(num_format_clone);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_clone_n
 * @since_tizen     2.3.1
 * @description     Creates a copy of an invalid number handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_clone_n(void)
{
    i18n_unumber_format_h num_format_clone;

    ret = i18n_unumber_clone(NULL, &num_format_clone);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_clone_n2
 * @since_tizen     2.3.1
 * @description     Creates a copy of an invalid number handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_clone_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    ret = i18n_unumber_clone(num_format, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_p
 * @since_tizen     2.3.1
 * @description     Formats an integer using a i18n_unumber_format_h,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_unumber_format_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar result[BUF_SIZE] = { 0, };
    i18n_error_code_e status = I18N_ERROR_NONE;

    i18n_unumber_format(num_format, 1994, result, BUF_SIZE, NULL, &status);

    assert_eq(status, I18N_ERROR_NONE);
    assert_eq(i18n_ustring_compare(result, test_variable), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_p2
 * @since_tizen     2.3.1
 * @description     Formats an negative integer using a number format handle,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_unumber_format_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_error_code_e status = I18N_ERROR_NONE;
    i18n_unumber_format(num_format, -643, result, BUF_SIZE, NULL, &status);

    assert_eq(status, I18N_ERROR_NONE);
    assert_eq(i18n_ustring_compare(result, test_variable3), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_i18n_unumber_format_n
 * @since_tizen     2.3.1
 * @description     Formats an integer using an invalid format handle,
 *                  so the error is expected.
 */
int utc_capi_base_i18n_unumber_format_n(void)
{
    i18n_uchar result[BUF_SIZE] = { 0, };
    i18n_error_code_e status = I18N_ERROR_NONE;

    i18n_unumber_format(NULL, 1994, result, BUF_SIZE, NULL, &status);
    assert_eq(status, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_i18n_unumber_format_n2
 * @since_tizen     2.3.1
 * @description     Formats an integer using a format passing invalid buffer,
 *                  so the error is expected.
 */
int utc_capi_base_i18n_unumber_format_n2(void)
{
    i18n_error_code_e status = I18N_ERROR_NONE;

    i18n_unumber_format(num_format, 1994, NULL, BUF_SIZE, NULL, &status);
    assert_eq(status, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_i18n_unumber_format_n3
 * @since_tizen     2.3.1
 * @description     Formats an integer using a number format passing invalid position,
 *                  so the error is expected.
 */
int utc_capi_base_i18n_unumber_format_n3(void)
{
    i18n_uchar result[BUF_SIZE] = { 0, };
    i18n_error_code_e status = I18N_ERROR_NONE;

    i18n_unumber_format(num_format, 1994, result, -1, NULL, &status);
    assert_eq(status, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_int64_p
 * @since_tizen     2.3.1
 * @description     Formats an int64 using an number handle,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_unumber_format_int64_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_format_int64(num_format, 1994, result, BUF_SIZE, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(i18n_ustring_compare(result, test_variable), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_int64_p2
 * @since_tizen     2.3.1
 * @description     Formats an negative int64 using an invalid number handle,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_unumber_format_int64_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_format_int64(num_format, -1994, result, BUF_SIZE, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(i18n_ustring_compare(result, test_variable2), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_int64_n
 * @since_tizen     2.3.1
 * @description     Formats an int64 using an invalid number handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_format_int64_n(void)
{
    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_format_int64(NULL, 1994, result, BUF_SIZE, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_int64_n2
 * @since_tizen     2.3.1
 * @description     Formats an int64 using an number handle passing invalid output buffer,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_format_int64_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_unumber_format_int64(num_format, 1994, NULL, BUF_SIZE, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_int64_n3
 * @since_tizen     2.3.1
 * @description     Formats an int64 using an number handle passing invalid position,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_format_int64_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_format_int64(num_format, 1994, result, -1, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_double_p
 * @since_tizen     2.3.1
 * @scenario        Formats a double using an number handle,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_unumber_format_double_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_format_double(num_format, 2014.0, result, BUF_SIZE, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(i18n_ustring_compare(result, test_variable4), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_double_p2
 * @since_tizen     2.3.1
 * @description     Formats an int64 using a negative number,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_unumber_format_double_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_format_double(num_format, -2014.0, result, BUF_SIZE, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(i18n_ustring_compare(result, test_variable5), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_double_n
 * @since_tizen     2.3.1
 * @description     Formats a double using an invalid number handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_format_double_n(void)
{
    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_format_double(NULL, 2014.0, result, BUF_SIZE, NULL);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_double_n2
 * @since_tizen     2.3.1
 * @description     Formats a double using a number handle passing invalid buffer,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_format_double_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_unumber_format_double(num_format, 2014.0, NULL, BUF_SIZE, NULL);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_double_n3
 * @since_tizen     2.3.1
 * @description     Formats a double using a number handle passing invalid position,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_format_double_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_format_double(num_format, 2014.0, result, -1, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_decimal_p
 * @since_tizen     2.3.1
 * @description     Formats a decimal number using a number handle,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_unumber_format_decimal_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_format_decimal(num_format, "2014.0", 6, result, BUF_SIZE, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(i18n_ustring_compare(result, test_variable4), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_decimal_p2
 * @since_tizen     2.3.1
 * @description     Formats a negative decimal number using a number,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_unumber_format_decimal_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_format_decimal(num_format, "-2014.0", 7, result, BUF_SIZE, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(i18n_ustring_compare(result, test_variable5), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_decimal_n
 * @since_tizen     2.3.1
 * @description     Formats a decimal number using an invalid number handle.
 */
int utc_capi_base_utils_i18n_unumber_format_decimal_n(void)
{
    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_format_decimal(NULL, "2014.0", 6, result, BUF_SIZE, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_decimal_n2
 * @since_tizen     2.3.1
 * @description     Formats a decimal number using a number handle,
 *                  passing false number string.
 */
int utc_capi_base_utils_i18n_unumber_format_decimal_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_format_decimal(num_format, NULL, 6, result, BUF_SIZE, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_decimal_n3
 * @since_tizen     2.3.1
 * @description     Formats a decimal number using a number handle,
 *                  passing invalid output buffer.
 */
int utc_capi_base_utils_i18n_unumber_format_decimal_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_unumber_format_decimal(num_format, "2014.0", 6, NULL, BUF_SIZE, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_decimal_n4
 * @since_tizen     2.3.1
 * @description     Formats a decimal number using a number handle,
 *                  passing invalid maximum size.
 */
int utc_capi_base_utils_i18n_unumber_format_decimal_n4(void)
{
    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_format_decimal(num_format, "2014.0", 6, result, -1, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_double_currency_p
 * @since_tizen     2.3.1
 * @description     Formats a double currency amount using a number.
 */
int utc_capi_base_utils_i18n_unumber_format_double_currency_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar result[BUF_SIZE] = { 0, };
    const char *currency = "USD";
    i18n_uchar *_currency = NULL;
    _currency = (i18n_uchar*)calloc(strlen(currency) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_currency, currency);

    i18n_unumber_format_double_currency(num_format, 2014.0, _currency, result, BUF_SIZE, NULL);
    ret = get_last_result();
    free(_currency);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_double_currency_p2
 * @since_tizen     2.3.1
 * @description     Formats a double currency amount using a number.
 */
int utc_capi_base_utils_i18n_unumber_format_double_currency_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar result[BUF_SIZE] = { 0, };
    const char *currency = "USD";
    i18n_uchar *_currency = NULL;
    _currency = (i18n_uchar*)calloc(strlen(currency) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_currency, currency);

    i18n_unumber_format_double_currency(num_format, 2014.0, _currency, result, BUF_SIZE, NULL);
    ret = get_last_result();
    free(_currency);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_double_currency_n
 * @since_tizen     2.3.1
 * @description     Formats a double currency amount using an invalid number handle.
 */
int utc_capi_base_utils_i18n_unumber_format_double_currency_n(void)
{
    i18n_uchar result[BUF_SIZE] = { 0, };
    const char *currency = "USD";
    i18n_uchar *_currency = NULL;
    _currency = (i18n_uchar*)calloc(strlen(currency) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_currency, currency);

    i18n_unumber_format_double_currency(NULL, 2014.0, _currency, result, BUF_SIZE, NULL);
    ret = get_last_result();
    free(_currency);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_double_currency_n2
 * @since_tizen     2.3.1
 * @description     Formats a double currency amount using a number handle,
 *                  passing invalid output buffer.
 */
int utc_capi_base_utils_i18n_unumber_format_double_currency_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    const char *currency = "USD";
    i18n_uchar *_currency = NULL;
    _currency = (i18n_uchar*)calloc(strlen(currency) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_currency, currency);

    i18n_unumber_format_double_currency(num_format, 2014.0, _currency, NULL, BUF_SIZE, NULL);
    ret = get_last_result();
    free(_currency);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_format_double_currency_n3
 * @since_tizen     2.3.1
 * @description     Formats a double currency amount using a number handle,
 *                  passing invalid maximum size.
 */
int utc_capi_base_utils_i18n_unumber_format_double_currency_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar result[BUF_SIZE] = { 0, };
    const char *currency = "USD";
    i18n_uchar *_currency = NULL;
    _currency = (i18n_uchar*)calloc(strlen(currency) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_currency, currency);

    i18n_unumber_format_double_currency(num_format, 2014.0, _currency, result, -1, NULL);
    ret = get_last_result();
    free(_currency);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_p
 * @since_tizen     2.3.1
 * @description     Parses a string into an integer,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_parse_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    const i18n_uchar text[] = { '2', '3', '2', '3', '1', '0', 0x00 };

    int32_t value = i18n_unumber_parse(num_format, text, i18n_ustring_get_length(text), NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(value, 232310);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_p2
 * @since_tizen     2.3.1
 * @description     Parses a string into a negative integer.
 */
int utc_capi_base_utils_i18n_unumber_parse_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    const i18n_uchar text[] = { '-', '2', '3', '2', '3', '1', '0', 0x00 };

    int32_t value = i18n_unumber_parse(num_format, text, i18n_ustring_get_length(text), NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(value, -232310);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_n
 * @since_tizen     2.3.1
 * @description     Parses a string into an integer using an invalid number handle.
 */
int utc_capi_base_utils_i18n_unumber_parse_n(void)
{
    const i18n_uchar text[] = { '2', '3', '2', '3', '1', '0', 0x00 };

    i18n_unumber_parse(NULL, text, i18n_ustring_get_length(text), NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_n2
 * @since_tizen     2.3.1
 * @description     Parses a string into an integer using a number handle,
 *                  passing invalid input string.
 */
int utc_capi_base_utils_i18n_unumber_parse_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    const i18n_uchar text[] = { '2', '3', '2', '3', '1', '0', 0x00 };

    i18n_unumber_parse(num_format, NULL, i18n_ustring_get_length(text), NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_n3
 * @since_tizen     2.3.1
 * @description     Parses a string into an integer using a number handle,
 *                  passing invalid length.
 */
int utc_capi_base_utils_i18n_unumber_parse_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    const i18n_uchar text[] = { '2', '3', '2', '3', '1', '0', 0x00 };

    i18n_unumber_parse(num_format, text, -2, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_int64_p
 * @since_tizen     2.3.1
 * @description     Parses a string into an int64 using a number.
 */
int utc_capi_base_utils_i18n_unumber_parse_int64_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    int32_t len = i18n_ustring_get_length(test_variable);
    int32_t value = i18n_unumber_parse_int64(num_format, test_variable, len, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(value, 1994);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_int64_p2
 * @since_tizen     2.3.1
 * @description     Parses a string into an negative int64 using a number.
 */
int utc_capi_base_utils_i18n_unumber_parse_int64_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    int32_t len = i18n_ustring_get_length(test_variable2);
    int32_t value = i18n_unumber_parse_int64(num_format, test_variable2, len, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(value, -1994);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_int64_n
 * @since_tizen     2.3.1
 * @description     Parses a string into an int64 using an invalid number handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_parse_int64_n(void)
{
    int32_t len = i18n_ustring_get_length(test_variable);
    i18n_unumber_parse_int64(NULL, test_variable, len, NULL);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_int64_n2
 * @since_tizen     2.3.1
 * @description     Parses a string into an int64 using a number handle,
 *                  passing input buffer.
 */
int utc_capi_base_utils_i18n_unumber_parse_int64_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_unumber_parse_int64(num_format, NULL, 16, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_int64_n3
 * @since_tizen     2.3.1
 * @description     Parses a string into an int64 using a number handle,
 *                  passing invalid text length.
 */
int utc_capi_base_utils_i18n_unumber_parse_int64_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_unumber_parse_int64(num_format, test_variable, -2, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_double_p
 * @since_tizen     2.3.1
 * @description     Parses a string into a double using a number.
 */
int utc_capi_base_utils_i18n_unumber_parse_double_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar parse_double[] = { '1', '2', '2', '3', '.', '1', '1', 0 };

    int32_t len = i18n_ustring_get_length(parse_double);
    double value = i18n_unumber_parse_double(num_format, parse_double, len, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(value, 1223.11);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_double_p2
 * @since_tizen     2.3.1
 * @description     Parses a string into a negative double using a number.
 */
int utc_capi_base_utils_i18n_unumber_parse_double_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar parse_double[] = { '-', '1', '2', '2', '3', '.', '1', '1', 0 };

    int32_t len = i18n_ustring_get_length(parse_double);
    double value = i18n_unumber_parse_double(num_format, parse_double, len, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(value, -1223.11);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_double_n
 * @since_tizen     2.3.1
 * @description     Parses a string into a double using an invalid number handle.
 */
int utc_capi_base_utils_i18n_unumber_parse_double_n(void)
{
    i18n_uchar parse_double[] = { '1', '2', '2', '3', '.', '1', '1', 0 };

    int32_t len = i18n_ustring_get_length(parse_double);
    i18n_unumber_parse_double(NULL, parse_double, len, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_double_n2
 * @since_tizen     2.3.1
 * @description     Parses a string into a double using a number handle,
 *                  passing invalid input string.
 */
int utc_capi_base_utils_i18n_unumber_parse_double_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_unumber_parse_double(num_format, NULL, 8, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_double_n3
 * @since_tizen     2.3.1
 * @description     Parses a string into a double using a number handle,
 *                  passing invalid text length parameter.
 */
int utc_capi_base_utils_i18n_unumber_parse_double_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar parse_double[] = { '1', '2', '2', '3', '.', '1', '1', 0 };

    i18n_unumber_parse_double(num_format, parse_double, -2, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_decimal_p
 * @since_tizen     2.3.1
 * @description     Parses a number from a string into an unformatted numeric string using a number.
 * @scenario        Parses a number from a string into an unformatted numeric string using a number,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_unumber_parse_decimal_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    char result[BUF_SIZE] = { 0, };
    i18n_uchar *_text = NULL;
    char *text = "12,345.678";
    _text = (i18n_uchar*)calloc(strlen(text) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_text, text);

    int32_t _text_length = i18n_ustring_get_length(_text);
    i18n_unumber_parse_decimal(num_format, _text, _text_length, NULL, result, BUF_SIZE);
    ret = get_last_result();
    free(_text);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(result, "12345.678"), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_decimal_p2
 * @since_tizen     2.3.1
 * @description     Parses a number from a string into an unformatted numeric
 *                  string using a fraction number.
 */
int utc_capi_base_utils_i18n_unumber_parse_decimal_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    char result[BUF_SIZE] = { 0, };
    i18n_uchar *_text = NULL;
    char *text = ".1234";
    _text = (i18n_uchar*)calloc(strlen(text) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_text, text);

    int32_t _text_length = i18n_ustring_get_length(_text);
    i18n_unumber_parse_decimal(num_format, _text, _text_length, NULL, result, BUF_SIZE);

    ret = get_last_result();
    free(_text);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(result, "0.1234"), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_decimal_n
 * @since_tizen     2.3.1
 * @description     Parses an invalid number handle from a string into an unformatted numeric string using an invalid number handle.
 * @scenario        Parses a number from a string into an unformatted numeric string using a number,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_unumber_parse_decimal_n(void)
{
    char result[BUF_SIZE] = { 0, };
    i18n_uchar *_text = NULL;
    char *text = "12,345,678.1234";
    _text = (i18n_uchar*)calloc(strlen(text) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_text, text);

    int32_t _text_length = i18n_ustring_get_length(_text);
    i18n_unumber_parse_decimal(NULL, _text, _text_length, NULL, result, BUF_SIZE);

    ret = get_last_result();
    free(_text);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_decimal_n2
 * @since_tizen     2.3.1
 * @description     Parses a number handle from a string into
 *                  an unformatted numeric string using an invalid number handle,
 *                  passing invalid text input.
 */
int utc_capi_base_utils_i18n_unumber_parse_decimal_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    char result[BUF_SIZE] = { 0, };

    i18n_unumber_parse_decimal(num_format, NULL, 16, NULL, result, BUF_SIZE);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_decimal_n3
 * @since_tizen     2.3.1
 * @description     Parses a number handle from a string into an unformatted
 *                  numeric string using a number handle,
 *                  passing invalid text length.
 */
int utc_capi_base_utils_i18n_unumber_parse_decimal_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    char result[BUF_SIZE] = { 0, };
    i18n_uchar *_text = NULL;
    char *text = "12,345,678.1234";
    _text = (i18n_uchar*)calloc(strlen(text) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_text, text);

    i18n_unumber_parse_decimal(num_format, _text, -2, NULL, result, BUF_SIZE);

    ret = get_last_result();
    free(_text);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_decimal_n4
 * @since_tizen     2.3.1
 * @description     Parses a number handle from a string into an unformatted
 *                  numeric string using a number handle, passing invalid
 *                  output buffer.
 */
int utc_capi_base_utils_i18n_unumber_parse_decimal_n4(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar *_text = NULL;
    char *text = "12,345,678.1234";
    _text = (i18n_uchar*)calloc(strlen(text) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_text, text);

    int32_t _text_length = i18n_ustring_get_length(_text);
    i18n_unumber_parse_decimal(num_format, _text, _text_length, NULL, NULL, BUF_SIZE);

    ret = get_last_result();
    free(_text);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_decimal_n5
 * @since_tizen     2.3.1
 * @description     Parses a number handle from a string into an
 *                  unformatted numeric string using an invalid number handle,
 *                  passing invalid output length
 */
int utc_capi_base_utils_i18n_unumber_parse_decimal_n5(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    char result[BUF_SIZE] = { 0, };
    i18n_uchar *_text = NULL;
    char *text = "12,345,678.1234";
    _text = (i18n_uchar*)calloc(strlen(text) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_text, text);

    int32_t _text_length = i18n_ustring_get_length(_text);
    i18n_unumber_parse_decimal(num_format, _text, _text_length, NULL, result, -1);

    ret = get_last_result();
    free(_text);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_double_currency_p
 * @since_tizen     2.3.1
 * @description     Creates US number handle, parses a string into a double
 *                  and a currency using it, and checks whether error occurred.
 */
int utc_capi_base_utils_i18n_unumber_parse_double_currency_p(void)
{
    i18n_uchar *pattern = NULL;
    i18n_uchar currency[BUF_SIZE] = { 0, };
    i18n_uchar _text[] = { 0x0024, 0x0031, 0x0032, 0x002E, 0x0030, 0x0030, 0 };

    if(NULL != num_format) {
        i18n_unumber_destroy(num_format);
    }

    ret = i18n_unumber_create(I18N_UNUMBER_CURRENCY, pattern, -1, I18N_ULOCALE_US, NULL, &num_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    int32_t _text_length = i18n_ustring_get_length(_text);
    i18n_unumber_parse_double_currency(num_format, _text, _text_length, NULL, currency);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_double_currency_p2
 * @since_tizen     2.3.1
 * @description     Creates UK number handle, parses a string into a double
 *                  and a currency using it, and checks whether error occurred.
 */
int utc_capi_base_utils_i18n_unumber_parse_double_currency_p2(void)
{
    i18n_uchar *pattern = NULL;
    i18n_uchar currency[BUF_SIZE] = { 0, };
    i18n_uchar _text[] = { 0x00A3, 0x0031, 0x0032, 0x002E, 0x0030, 0x0030, 0 };

    if(NULL != num_format) {
        i18n_unumber_destroy(num_format);
    }

    ret = i18n_unumber_create(I18N_UNUMBER_CURRENCY, pattern, -1, I18N_ULOCALE_UK, NULL, &num_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    int32_t _text_length = i18n_ustring_get_length(_text);
    i18n_unumber_parse_double_currency(num_format, _text, _text_length, NULL, currency);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_double_currency_n
 * @since_tizen     2.3.1
 * @description     Parses a string into a double and a currency
 *                  using an invalid number handle.
 */
int utc_capi_base_utils_i18n_unumber_parse_double_currency_n(void)
{
    i18n_uchar currency[BUF_SIZE] = { 0, };
    i18n_uchar _text[] = { 0x0024, 0x0031, 0x0032, 0x002E, 0x0030, 0x0030, 0 };

    int32_t _text_length = i18n_ustring_get_length(_text);
    i18n_unumber_parse_double_currency(NULL, _text, _text_length, NULL, currency);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_double_currency_n2
 * @since_tizen     2.3.1
 * @description     Parses a string into a double and a currency, passing
 *                  invalid input text.
 */
int utc_capi_base_utils_i18n_unumber_parse_double_currency_n2(void)
{
    i18n_uchar *pattern = NULL;
    i18n_uchar currency[BUF_SIZE] = { 0, };

    if(NULL != num_format) {
        i18n_unumber_destroy(num_format);
    }

    ret = i18n_unumber_create(I18N_UNUMBER_CURRENCY, pattern, -1, I18N_ULOCALE_US, NULL, &num_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_unumber_parse_double_currency(num_format, NULL, 16, NULL, currency);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_double_currency_n3
 * @since_tizen     2.3.1
 * @description     Creates format handle, then parses a string into a double using it,
 *                  passing invalid text length argument. Error is expected.
 */
int utc_capi_base_utils_i18n_unumber_parse_double_currency_n3(void)
{
    i18n_uchar *pattern = NULL;
    i18n_uchar currency[BUF_SIZE] = { 0, };
    i18n_uchar _text[] = { 0x0024, 0x0031, 0x0032, 0x002E, 0x0030, 0x0030, 0 };

    if(NULL != num_format) {
        i18n_unumber_destroy(num_format);
    }

    ret = i18n_unumber_create(I18N_UNUMBER_CURRENCY, pattern, -1, I18N_ULOCALE_US, NULL, &num_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_unumber_parse_double_currency(num_format, _text, -2, NULL, currency);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_parse_double_currency_n4
 * @since_tizen     2.3.1
 * @description     Creates format handle, then parses a string into a double using it,
 *                  passing invalid output parameter. Error is expected.
 */
int utc_capi_base_utils_i18n_unumber_parse_double_currency_n4(void)
{
    i18n_uchar *pattern = NULL;
    i18n_uchar _text[] = { 0x0024, 0x0031, 0x0032, 0x002E, 0x0030, 0x0030, 0 };

    if(NULL != num_format) {
        i18n_unumber_destroy(num_format);
    }

    ret = i18n_unumber_create(I18N_UNUMBER_CURRENCY, pattern, -1, I18N_ULOCALE_US, NULL, &num_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    int32_t _text_length = i18n_ustring_get_length(_text);
    i18n_unumber_parse_double_currency(num_format, _text, _text_length, NULL, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_apply_pattern_p
 * @since_tizen     2.3.1
 * @description     Creates number format handle, sets a localized pattern
 *                  used by the number, and checks whether an error occurred.
 */
int utc_capi_base_utils_i18n_unumber_apply_pattern_p(void)
{
    i18n_unumber_format_h num_format;
    i18n_uchar pattern1[4] = { '#', ',', '#', '#' };
    int length1 = 4;
    i18n_uchar pattern2[8] = { '#', ',', '#', '#', ',', '#', '#', '#' };
    int length2 = 8;

    ret = i18n_unumber_create(I18N_UNUMBER_DECIMAL, pattern1, length1, I18N_ULOCALE_US, NULL, &num_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    ret = i18n_unumber_apply_pattern(num_format, true, pattern2, length2, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_unumber_destroy(num_format);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_apply_pattern_p2
 * @since_tizen     2.3.1
 * @description     Creates number format handle, sets a localized pattern
 *                  used by the number, and checks whether an error occurred.
 */
int utc_capi_base_utils_i18n_unumber_apply_pattern_p2(void)
{
    i18n_unumber_format_h num_format;
    i18n_uchar pattern1[4] = { '#', ',', '#', '#' };
    int length1 = 4;
    i18n_uchar pattern2[8] = { '#', ',', '#', '#', ',', '#', '#', '#' };
    int length2 = 8;

    ret = i18n_unumber_create(I18N_UNUMBER_DECIMAL, pattern1, length1, I18N_ULOCALE_US, NULL, &num_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    ret = i18n_unumber_apply_pattern(num_format, false, pattern2, length2, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_unumber_destroy(num_format);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_apply_pattern_n
 * @since_tizen     2.3.1
 * @description     Sets the pattern used by an invalid number handle.
 */
int utc_capi_base_utils_i18n_unumber_apply_pattern_n(void)
{
    i18n_unumber_format_h num_format;
    i18n_uchar pattern1[4] = { '#', ',', '#', '#' };
    int length1 = 4;
    i18n_uchar pattern2[8] = { '#', ',', '#', '#', ',', '#', '#', '#' };
    int length2 = 8;

    ret = i18n_unumber_create(I18N_UNUMBER_DECIMAL, pattern1, length1, I18N_ULOCALE_US, NULL, &num_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    ret = i18n_unumber_apply_pattern(NULL, false, pattern2, length2, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    i18n_unumber_destroy(num_format);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_apply_pattern_n2
 * @since_tizen     2.3.1
 * @description     Sets a invalid pattern used by created number format handle.
 */
int utc_capi_base_utils_i18n_unumber_apply_pattern_n2(void)
{
    i18n_unumber_format_h num_format;
    i18n_uchar pattern1[4] = { '#', ',', '#', '#' };
    int length1 = 4;
    int length2 = 8;

    ret = i18n_unumber_create(I18N_UNUMBER_DECIMAL, pattern1, length1, I18N_ULOCALE_US, NULL, &num_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    ret = i18n_unumber_apply_pattern(num_format, false, NULL, length2, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    i18n_unumber_destroy(num_format);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_apply_pattern_n3
 * @since_tizen     2.3.1
 * @description     Sets the pattern used by an invalid number handle,
 *                  passing invalid length.
 */
int utc_capi_base_utils_i18n_unumber_apply_pattern_n3(void)
{
    i18n_unumber_format_h num_format;
    i18n_uchar pattern1[4] = { '#', ',', '#', '#' };
    int length1 = 4;
    i18n_uchar pattern2[8] = { '#', ',', '#', '#', ',', '#', '#', '#' };

    ret = i18n_unumber_create(I18N_UNUMBER_DECIMAL, pattern1, length1, I18N_ULOCALE_US, NULL, &num_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    ret = i18n_unumber_apply_pattern(num_format, false, pattern2, -2, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    i18n_unumber_destroy(num_format);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_available_p
 * @since_tizen     2.3.1
 * @description     Gets a locale for which decimal formatting patterns are available.
 *                  Checks whether there is no error and returned value is not empty.
 */
int utc_capi_base_utils_i18n_unumber_get_available_p(void)
{
    const char *value = i18n_unumber_get_available(0);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(value, NULL);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_available_n
 * @since_tizen     2.3.1
 * @description     Gets a locale for which decimal formatting patterns are available,
 *                  passing invalid index and expecting error.
 */
int utc_capi_base_utils_i18n_unumber_get_available_n(void)
{
    const char *value = i18n_unumber_get_available(-1);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(value, NULL);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_count_available_p
 * @since_tizen     2.3.1
 * @description     Determines how many locales have decimal formatting
 *                  patterns available.  Checks whether there is no error
 *                  and returned value is greater then or equal 0.
 */
int utc_capi_base_utils_i18n_unumber_count_available_p(void)
{
    int no_locales = i18n_unumber_count_available();
    assert_geq(no_locales, 0);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_attribute_p
 * @since_tizen     2.3.1
 * @description     Gets a numeric attribute associated with a number handle
 *                  for every attribute. Check whether no error occurred.
 */
int utc_capi_base_utils_i18n_unumber_get_attribute_p(void)
{
    i18n_unumber_format_attribute_e attribute = I18N_UNUMBER_PARSE_INT_ONLY;

    for(; attribute <= I18N_UNUMBER_LENIENT_PARSE; attribute++) {
        i18n_unumber_get_attribute(num_format, attribute);
        ret = get_last_result();
        assert_eq(ret, I18N_ERROR_NONE);
    }

    i18n_unumber_get_attribute(num_format, I18N_UNUM_SCALE);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_attribute_n
 * @since_tizen     2.3.1
 * @description     Gets a numeric attribute associated with an invalid number handle.
 *                  Error is expected.
 */
int utc_capi_base_utils_i18n_unumber_get_attribute_n(void)
{
    i18n_unumber_get_attribute(NULL, I18N_UNUMBER_PARSE_INT_ONLY);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_set_attribute_p
 * @since_tizen     2.3.1
 * @description     Sets a numeric attribute associated with a number.
 *                  Checks whether there is no errors.
 */
int utc_capi_base_utils_i18n_unumber_set_attribute_p(void)
{
    i18n_unumber_format_attribute_e attribute = I18N_UNUMBER_PARSE_INT_ONLY;

    for(; attribute <= I18N_UNUMBER_LENIENT_PARSE; attribute++) {
        if(I18N_UNUMBER_ROUNDING_INCREMENT != attribute) {
            ret = i18n_unumber_set_attribute(num_format, attribute, 0);
            assert_eq(ret, I18N_ERROR_NONE);
        }
    }

    ret = i18n_unumber_set_attribute(num_format, I18N_UNUM_SCALE, 0);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_set_attribute_n
 * @since_tizen     2.3.1
 * @description     Sets a numeric attribute associated with an invalid number handle,
 *                  so an error is expected.
 */
int utc_capi_base_utils_i18n_unumber_set_attribute_n(void)
{
    ret = i18n_unumber_set_attribute(NULL, I18N_UNUMBER_PARSE_INT_ONLY, 0);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_set_attribute_n2
 * @since_tizen     2.3.1
 * @description     Sets a numeric attribute associated with a number handle,
 *                  passing invalid attribute, so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_set_attribute_n2(void)
{
    ret = i18n_unumber_set_attribute(num_format, I18N_UNUMBER_ROUNDING_INCREMENT, 0);
    assert_eq(ret, I18N_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_double_attribute_p
 * @since_tizen     2.3.1
 * @description     Gets a numeric attribute associated with a number.
 *                  Checks result and error code.
 */
int utc_capi_base_utils_i18n_unumber_get_double_attribute_p(void)
{
    i18n_unumber_get_double_attribute(num_format, I18N_UNUMBER_ROUNDING_INCREMENT);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_double_attribute_n
 * @since_tizen     2.3.1
 * @description     Gets a numeric attribute associated with an invalid number handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_get_double_attribute_n(void)
{
    i18n_unumber_get_double_attribute(NULL, I18N_UNUMBER_PARSE_INT_ONLY);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_set_double_attribute_p
 * @since_tizen     2.3.1
 * @description     Sets a numeric attribute associated with a number handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_set_double_attribute_p(void)
{
    ret = i18n_unumber_set_double_attribute(num_format, I18N_UNUMBER_ROUNDING_INCREMENT, 0.0);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_set_double_attribute_n
 * @since_tizen     2.3.1
 * @description     Sets a numeric attribute associated with an invalid number handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_set_double_attribute_n(void)
{
    ret = i18n_unumber_set_double_attribute(NULL, I18N_UNUMBER_ROUNDING_INCREMENT, 0.0);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_text_attribute_p
 * @since_tizen     2.3.1
 * @description     Gets a text attribute associated with a number
 *                  for each attribute, checks error code.
 */
int utc_capi_base_utils_i18n_unumber_get_text_attribute_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar result[BUF_SIZE] = { 0, };
    i18n_unumber_format_text_attribute_e attribute = I18N_UNUMBER_POSITIVE_PREFIX;

    for(; attribute <= I18N_UNUMBER_CURRENCY_CODE; attribute++) {
        i18n_unumber_get_text_attribute(num_format, attribute, result, BUF_SIZE);
        ret = get_last_result();
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_text_attribute_p2
 * @since_tizen     2.3.1
 * @description     Gets a text attribute associated with a number,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_unumber_get_text_attribute_p2(void)
{
    if(NULL != num_format) {
        i18n_unumber_destroy(num_format);
    }

    i18n_uchar pattern[4] = { '#', ',', '#', '#' };

    ret = i18n_unumber_create(I18N_UNUMBER_PATTERN_RULEBASED, pattern, -1, I18N_ULOCALE_US, NULL, &num_format);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_get_text_attribute(num_format, I18N_UNUMBER_DEFAULT_RULESET, result, BUF_SIZE);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_unumber_get_text_attribute(num_format, I18N_UNUMBER_PUBLIC_RULESETS, result, BUF_SIZE);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_text_attribute_n
 * @since_tizen     2.3.1
 * @description     Gets a text attribute associated with an invalid number format,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_get_text_attribute_n(void)
{
    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_get_text_attribute(NULL, I18N_UNUMBER_CURRENCY_CODE, result, BUF_SIZE);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_text_attribute_n2
 * @since_tizen     2.3.1
 * @description     Gets a text attribute associated with a number handle,
 *                  passing invalid attribute, so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_get_text_attribute_n2(void)
{
    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_get_text_attribute(num_format, -1, result, BUF_SIZE);
    ret = get_last_result();
    assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_text_attribute_n3
 * @since_tizen     2.3.1
 * @description     Gets a text attribute associated with a number handle,
 *                  passing invalid output buffer.
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_unumber_get_text_attribute_n3(void)
{
    i18n_unumber_get_text_attribute(num_format, I18N_UNUMBER_CURRENCY_CODE, NULL, BUF_SIZE);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_text_attribute_n4
 * @since_tizen     2.3.1
 * @description     Gets a text attribute associated with a number handle,
 *                  passing invalid result length, so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_get_text_attribute_n4(void)
{
    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_get_text_attribute(num_format, I18N_UNUMBER_CURRENCY_CODE, result, -1);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_set_text_attribute_p
 * @since_tizen     2.3.1
 * @description     Sets a text attribute associated with a number for every attribute.
 *                  Checks result and error code.
 */
int utc_capi_base_utils_i18n_unumber_set_text_attribute_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar new_value[BUF_SIZE] = { 0, };
    i18n_unumber_format_text_attribute_e attribute = I18N_UNUMBER_POSITIVE_PREFIX;

    for(; attribute <= I18N_UNUMBER_CURRENCY_CODE; attribute++) {
        ret = i18n_unumber_set_text_attribute(num_format, attribute, new_value, 8);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_set_text_attribute_p2
 * @since_tizen     2.3.1
 * @description     Creates rule based pattern, sets a text attribute
 *                  associated with a number. Checks result and error code.
 */
int utc_capi_base_utils_i18n_unumber_set_text_attribute_p2(void)
{
    if(NULL != num_format) {
        i18n_unumber_destroy(num_format);
    }

    i18n_uchar pattern[5] = { '#', ',', '#', '#', 0 };

    ret = i18n_unumber_create(I18N_UNUMBER_PATTERN_RULEBASED, pattern, -1, I18N_ULOCALE_US, NULL, &num_format);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar result[BUF_SIZE];
    i18n_unumber_get_text_attribute(num_format, I18N_UNUMBER_DEFAULT_RULESET, result, BUF_SIZE);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_unumber_set_text_attribute(num_format, I18N_UNUMBER_DEFAULT_RULESET, result, -1);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_set_text_attribute_n
 * @since_tizen     2.3.1
 * @description     Sets a text attribute associated with an invalid number handle,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_unumber_set_text_attribute_n(void)
{
    i18n_uchar new_value[BUF_SIZE] = { 0, };

    ret = i18n_unumber_set_text_attribute(NULL, I18N_UNUMBER_CURRENCY_CODE, new_value, BUF_SIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_set_text_attribute_n2
 * @since_tizen     2.3.1
 * @description     Sets a text attribute associated with a number handle,
 *                  passing invalid tag attribute, so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_set_text_attribute_n2(void)
{
    i18n_uchar new_value[BUF_SIZE] = { 0, };

    ret = i18n_unumber_set_text_attribute(num_format, -1, new_value, BUF_SIZE);
    assert_eq(ret, TIZEN_ERROR_NOT_SUPPORTED);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_set_text_attribute_n3
 * @since_tizen     2.3.1
 * @description     Sets a text attribute associated with a number handle,
 *                  passing invalid value, so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_set_text_attribute_n3(void)
{
    ret = i18n_unumber_set_text_attribute(num_format, I18N_UNUMBER_CURRENCY_CODE, NULL, BUF_SIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_set_text_attribute_n4
 * @since_tizen     2.3.1
 * @description     Sets a text attribute associated with a number handle,
 *                  passing invalid value length, so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_set_text_attribute_n4(void)
{
    i18n_uchar new_value[BUF_SIZE] = { 0, };

    ret = i18n_unumber_set_text_attribute(num_format, I18N_UNUMBER_CURRENCY_CODE, new_value, -2);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_to_pattern_p
 * @since_tizen     2.3.1
 * @description     Extracts the pattern from a number,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_unumber_to_pattern_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_to_pattern(num_format, 0, result, BUF_SIZE);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_to_pattern_p2
 * @since_tizen     2.3.1
 * @description     Creates number format handle with another pattern,
 *                  extracts the pattern from a number. Checks result and error code.
 */
int utc_capi_base_utils_i18n_unumber_to_pattern_p2(void)
{
    if(NULL != num_format) {
        i18n_unumber_destroy(num_format);
    }

    i18n_uchar pattern[9] = { '#', ',', '#', '#', ',', '#', '#', '#', '\n' };
    ret = i18n_unumber_create(I18N_UNUMBER_DECIMAL, pattern, 0, I18N_ULOCALE_US, NULL, &num_format);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_to_pattern(num_format, 0, result, BUF_SIZE);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_to_pattern_n
 * @since_tizen     2.3.1
 * @description     Extracts the pattern from an invalid number handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_to_pattern_n(void)
{
    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_to_pattern(NULL, 0, result, BUF_SIZE);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_to_pattern_n2
 * @since_tizen     2.3.1
 * @description     Extracts the pattern from a number handle passing
 *                  invalid output buffer, so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_to_pattern_n2(void)
{
    i18n_unumber_to_pattern(num_format, 0, NULL, BUF_SIZE);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_to_pattern_n3
 * @since_tizen     2.3.1
 * @description     Extracts the pattern from a number handle passing
 *                  invalid output buffer size, so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_to_pattern_n3(void)
{
    i18n_uchar result[BUF_SIZE] = { 0, };

    i18n_unumber_to_pattern(num_format, 0, result, -1);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_set_symbol_p
 * @since_tizen     2.3.1
 * @description     Sets a symbol associated with a number handle for each symbol.
 *                  There is check, whether there is no error.
 */
int utc_capi_base_utils_i18n_unumber_set_symbol_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_uchar result[BUF_SIZE] = { 0, };
    i18n_unumber_format_symbol_e symbol = I18N_UNUMBER_DECIMAL_SEPARATOR_SYMBOL;

    for(; symbol < I18N_UNUMBER_FORMAT_SYMBOL_COUNT; symbol++) {
        ret = i18n_unumber_set_symbol(num_format, symbol, result, BUF_SIZE);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_set_symbol_n
 * @since_tizen     2.3.1
 * @description     Sets a symbol associated with an invalid number handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_set_symbol_n(void)
{
    i18n_uchar result[BUF_SIZE] = { 0, };

    ret = i18n_unumber_set_symbol(NULL, I18N_UNUMBER_CURRENCY_SYMBOL, result, BUF_SIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_set_symbol_n2
 * @since_tizen     2.3.1
 * @description     Sets a symbol associated with a number handle,
 *                  passing invalid symbol, so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_set_symbol_n2(void)
{
    i18n_uchar result[BUF_SIZE] = { 0, };

    ret = i18n_unumber_set_symbol(num_format, -1, result, BUF_SIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_set_symbol_n3
 * @since_tizen     2.3.1
 * @description     Sets a symbol associated with a number handle,
 *                  passing invalid value, so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_set_symbol_n3(void)
{
    ret = i18n_unumber_set_symbol(num_format, I18N_UNUMBER_CURRENCY_SYMBOL, NULL, BUF_SIZE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_set_symbol_n4
 * @since_tizen     2.3.1
 * @description     Sets a symbol associated with a number handle,
 *                  passing invalid length argument, so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_set_symbol_n4(void)
{
    i18n_uchar result[BUF_SIZE] = { 0, };

    ret = i18n_unumber_set_symbol(num_format, I18N_UNUMBER_CURRENCY_SYMBOL, result, -2);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_locale_by_type_p
 * @since_tizen     2.3.1
 * @description     Gets the locale from this number format object from actual locale,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_unumber_get_locale_by_type_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_unumber_get_locale_by_type(num_format, I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_locale_by_type_p2
 * @since_tizen     2.3.1
 * @description     Gets the locale from number format from valid locale,
 *                  checks error code.
 */
int utc_capi_base_utils_i18n_unumber_get_locale_by_type_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_unumber_get_locale_by_type(num_format, I18N_ULOCALE_DATA_LOCALE_TYPE_VALID_LOCALE);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_locale_by_type_n
 * @since_tizen     2.3.1
 * @description     Gets the locale from invalid number handle,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_get_locale_by_type_n(void)
{
    i18n_unumber_get_locale_by_type(NULL, I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unumber_get_locale_by_type_n2
 * @since_tizen     2.3.1
 * @description     Gets the locale from number format passing invalid type,
 *                  so the error is expected.
 */
int utc_capi_base_utils_i18n_unumber_get_locale_by_type_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(num_format, NULL);

    i18n_unumber_get_locale_by_type(num_format, -1);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
