#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

#define BUFLEN 255
#define L I18N_UCHAR_U_LEFT_TO_RIGHT
#define R I18N_UCHAR_U_RIGHT_TO_LEFT

static i18n_ubidi_h ubidi = NULL;
static i18n_ubidi_h ubidi_line = NULL;
static i18n_uchar *prologue = NULL;
static i18n_uchar *src = NULL;
static i18n_uchar *dst = NULL;
static int32_t src_length = -1;
static int32_t dst_size = -1;
static int ret = 0;

static int check_current_locale()
{
    const char *loc = NULL;
    i18n_ulocale_get_default(&loc);

    if (strcmp(loc, "en_US_POSIX") == 0)
        return 1;
    else
        return 0;

}

static i18n_uchar_direction_e new_class_cb(const void* context, i18n_uchar32 c)
{
    i18n_uchar_direction_e custom_classes[] = {
            R, R, R, R, R, R, R, R,
            L, L, L, L, L, L, L, L
            };

    return c >= 16 ? I18N_UBIDI_CLASS_DEFAULT : custom_classes[c];
}

static i18n_uchar_direction_e old_class_cb(const void* context, i18n_uchar32 c)
{
    i18n_uchar_direction_e custom_classes[] = {
            R, L
            };

    return c >= 2 ? I18N_UBIDI_CLASS_DEFAULT : custom_classes[c];
}

static int32_t get_uchar_length(const char *arr)
{
    int32_t ulen = strlen(arr);
    i18n_uchar _text[ulen + 1];
    i18n_ustring_copy_ua(_text, arr);

    return i18n_ustring_get_length(_text);
}

/**
 * @function        utc_capi_base_utils_ubidi_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_ubidi_startup(void)
{
    ret = i18n_ubidi_create(&ubidi);

    char test_string[] = "<Paragraph1> <اختبار> paragraph1\n"
                         "<Paragraph2> <اختبار> paragraph2";

    src_length = get_uchar_length(test_string);

    src = (i18n_uchar *) malloc(sizeof(i18n_uchar) * (src_length + 1));
    i18n_ustring_copy_ua(src, test_string);

    dst_size = src_length + 1;
    dst = (i18n_uchar *) malloc(sizeof(i18n_uchar) * (dst_size));

    ret |= i18n_ubidi_set_para(ubidi, src, src_length, I18N_UBIDI_DEFAULT_LTR, NULL);
    ret |= i18n_ubidi_set_reordering_options(ubidi, I18N_UBIDI_OPTION_DEFAULT);
    ret |= i18n_ubidi_set_reordering_mode(ubidi, I18N_UBIDI_REORDER_DEFAULT);
    ret |= i18n_ubidi_set_class_cb(ubidi, old_class_cb, NULL, NULL, NULL);
}

/**
 * @function        utc_capi_base_utils_ubidi_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_ubidi_cleanup(void)
{
    if(ubidi != NULL)
    {
        i18n_ubidi_destroy(ubidi);
        ubidi = NULL;
    }
    if(ubidi_line != NULL)
    {
        i18n_ubidi_destroy(ubidi_line);
        ubidi_line = NULL;
    }

    free(src);
    src = NULL;

    free(dst);
    dst = NULL;

    free(prologue);
    prologue = NULL;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_write_reverse_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_write_reverse and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_write_reverse_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    uint16_t options = I18N_UBIDI_DO_MIRRORING;

    int32_t output_length = -1;
    ret = i18n_ubidi_write_reverse(src, src_length, options, dst_size,
                                   dst, &output_length);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(output_length, -1);

    char tmp[BUFLEN];
    i18n_ustring_copy_au(tmp, dst);
    int cmp = strcmp(tmp, "2hpargarap <رابتخا> <2hpargaraP>\n"
                          "1hpargarap <رابتخا> <1hpargaraP>");

    assert_eq(cmp, 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_write_reverse_p2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_write_reverse and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_write_reverse_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    uint16_t options = I18N_UBIDI_KEEP_BASE_COMBINING;

    int32_t output_length = -1;
    ret = i18n_ubidi_write_reverse(src, src_length, options, dst_size,
                                   dst, &output_length);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(output_length, -1);

    char tmp[BUFLEN];
    i18n_ustring_copy_au(tmp, dst);
    int cmp = strcmp(tmp, "2hpargarap >رابتخا< >2hpargaraP<\n"
                          "1hpargarap >رابتخا< >1hpargaraP<");

    assert_eq(cmp, 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_write_reverse_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_write_reverse passing invalid src and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_write_reverse_n(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar *src = NULL; // Invalid parameter

    uint16_t options = I18N_UBIDI_KEEP_BASE_COMBINING;

    int32_t output_length = -1;

    ret = i18n_ubidi_write_reverse(src, src_length, options, dst_size,
                                   dst, &output_length);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_write_reverse_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_write_reverse passing invalid src_length and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_write_reverse_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t invalid_src_length = -2; // Invalid parameter
    uint16_t options = I18N_UBIDI_KEEP_BASE_COMBINING;

    int32_t output_length = -1;

    ret = i18n_ubidi_write_reverse(src, invalid_src_length, options, dst_size,
                                   dst, &output_length);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_write_reverse_n3
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_write_reverse passing invalid dst_size and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_write_reverse_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t dst_size = -2; // Invalid parameter
    uint16_t options = I18N_UBIDI_KEEP_BASE_COMBINING;

    int32_t output_length = -1;

    ret = i18n_ubidi_write_reverse(src, src_length, options, dst_size,
                                   dst, &output_length);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_write_reverse_n4
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_write_reverse passing invalid dst and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_write_reverse_n4(void)
{
    uint16_t options = I18N_UBIDI_KEEP_BASE_COMBINING;

    int32_t output_length = -1;

    ret = i18n_ubidi_write_reverse(src, src_length, options, dst_size,
                                   NULL, &output_length);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_write_reverse_n5
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_write_reverse passing invalid output_length and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_write_reverse_n5(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    uint16_t options = I18N_UBIDI_KEEP_BASE_COMBINING;

    ret = i18n_ubidi_write_reverse(src, src_length, dst_size, options,
                                   dst, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_write_reordered_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_write_reordered and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_write_reordered_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    uint16_t options = I18N_UBIDI_KEEP_BASE_COMBINING;

    int32_t output_length = -1;

    ret = i18n_ubidi_write_reordered(ubidi, options, dst_size,
                                     dst, &output_length);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(output_length, src_length);

    char tmp[BUFLEN];
    i18n_ustring_copy_au(tmp, dst);
    int cmp = strcmp(tmp, "<Paragraph1> <رابتخا> paragraph1\n"
                          "<Paragraph2> <رابتخا> paragraph2");

    assert_eq(cmp, 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_write_reordered_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_write_reordered passing invalid ubidi and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_write_reordered_n(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    uint16_t options = I18N_UBIDI_KEEP_BASE_COMBINING;

    int32_t output_length = -1;

    ret = i18n_ubidi_write_reordered(ubidi, options, dst_size,
                                     dst, &output_length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_write_reordered_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_write_reordered passing invalid dst_size and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_write_reordered_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t dst_size = -2; // Invalid parameter
    uint16_t options = I18N_UBIDI_KEEP_BASE_COMBINING;

    int32_t output_length = -1;

    ret = i18n_ubidi_write_reordered(ubidi, options, dst_size,
                                     dst, &output_length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_write_reordered_n3
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_write_reordered passing invalid dst and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_write_reordered_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar *dst = NULL; // Invalid parameter

    uint16_t options = I18N_UBIDI_KEEP_BASE_COMBINING;

    int32_t output_length = -1;

    ret = i18n_ubidi_write_reordered(ubidi, options, dst_size,
                                     dst, &output_length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_write_reordered_n4
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_write_reordered passing invalid output_length and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_write_reordered_n4(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    uint16_t options = I18N_UBIDI_KEEP_BASE_COMBINING;

    ret = i18n_ubidi_write_reordered(ubidi, options, dst_size,
                                     dst, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_reordering_options_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_reordering_options and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_set_reordering_options_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubidi_reordering_option_e options = I18N_UBIDI_OPTION_INSERT_MARKS;
    ret = i18n_ubidi_get_reordering_options(ubidi, &options);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(options, I18N_UBIDI_OPTION_DEFAULT);

    ret = i18n_ubidi_set_reordering_options(ubidi, I18N_UBIDI_OPTION_INSERT_MARKS);
    assert_eq(ret, I18N_ERROR_NONE);

    options = I18N_UBIDI_OPTION_DEFAULT;
    ret = i18n_ubidi_get_reordering_options(ubidi, &options);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(options, I18N_UBIDI_OPTION_INSERT_MARKS);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_reordering_options_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_reordering_options passing invalid ubidi and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_reordering_options_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    uint32_t reordering_options = 0;

    ret = i18n_ubidi_set_reordering_options(ubidi, reordering_options);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_reordering_mode_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_reordering_mode and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_set_reordering_mode_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubidi_reordering_mode_e mode = I18N_UBIDI_REORDER_NUMBERS_SPECIAL;

    ret = i18n_ubidi_get_reordering_mode(ubidi, &mode);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(mode, I18N_UBIDI_REORDER_DEFAULT);

    ret = i18n_ubidi_set_reordering_mode(ubidi, I18N_UBIDI_REORDER_NUMBERS_SPECIAL);
    assert_eq(ret, I18N_ERROR_NONE);

    mode = I18N_UBIDI_REORDER_DEFAULT;

    ret = i18n_ubidi_get_reordering_mode(ubidi, &mode);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(mode, I18N_UBIDI_REORDER_NUMBERS_SPECIAL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_reordering_mode_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_reordering_mode passing invalid ubidi and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_reordering_mode_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    i18n_ubidi_reordering_mode_e reordering_mode = I18N_UBIDI_REORDER_DEFAULT;

    ret = i18n_ubidi_set_reordering_mode(ubidi, reordering_mode);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_para_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_para and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_set_para_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    char test_text[] = "<Test> <اختبار> test";

    /* Create new text */
    int32_t text_length = get_uchar_length(test_text);
    i18n_uchar text[text_length + 1];
    i18n_ustring_copy_ua(text, test_text);

    ret = i18n_ubidi_set_para(ubidi, text, text_length, I18N_UBIDI_DEFAULT_LTR, NULL);

    assert_eq(ret, I18N_ERROR_NONE);

    /* Check if the text was set. */
    char *ret_text = NULL;
    ret = i18n_ubidi_get_text(ubidi, &ret_text);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ret_text, NULL);

    int cmp = strcmp(ret_text, test_text);
    assert_eq(cmp, 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_para_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_para passing invalid ubidi and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_para_n(void)
{
    char test_text[] = "<Test> <اختبار> test";

    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    int32_t text_length = get_uchar_length(test_text);
    i18n_uchar text[text_length + 1];
    i18n_ustring_copy_ua(text, test_text);

    i18n_ubidi_level_t para_level = 0;

    ret = i18n_ubidi_set_para(ubidi, text, text_length, para_level, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_para_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_para passing invalid text and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_para_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar *text = NULL;
    int text_length = 0;

    i18n_ubidi_level_t para_level = 0;

    ret = i18n_ubidi_set_para(ubidi, text, text_length, para_level, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_para_n3
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_para passing invalid length and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_para_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    char test_text[] = "<Test> <اختبار> test";

    int32_t text_length = get_uchar_length(test_text);
    i18n_uchar text[text_length + 1];
    i18n_ustring_copy_ua(text, test_text);

    text_length = -2;

    i18n_ubidi_level_t para_level = 0;

    ret = i18n_ubidi_set_para(ubidi, text, text_length, para_level, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_line_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_line and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_set_line_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    i18n_ubidi_level_t valid_levels[] = {0, 0, 0, 0, 1, 1};

    ret = i18n_ubidi_create(&ubidi_line);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_set_line(ubidi, 10, 16, ubidi_line);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t processed_length = 0;
    ret = i18n_ubidi_get_processed_length(ubidi_line, &processed_length);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(processed_length, 6);

    const i18n_ubidi_level_t *levels = NULL;
    ret = i18n_ubidi_get_levels(ubidi_line, &levels);
    assert_eq(ret, I18N_ERROR_NONE);

    int i;
    for(i = 0; i < processed_length; ++i)
    {
        assert_eq(levels[i], valid_levels[i]);
    }

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_line_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_line passing invalid ubidi and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_line_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    int32_t start = 0;
    int32_t limit = 1;

    i18n_ubidi_h ubidi_line = NULL;
    ret = i18n_ubidi_create(&ubidi_line);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_set_line(ubidi, start, limit, ubidi_line);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_line_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_line passing invalid start and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_line_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t start = -1; // Invalid parameter
    int32_t limit = 1;

    i18n_ubidi_h ubidi_line = NULL;
    ret = i18n_ubidi_create(&ubidi_line);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_set_line(ubidi, start, limit, ubidi_line);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_line_n3
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_line passing invalid limit and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_line_n3(void)
{
    int32_t start = 0;
    int32_t limit = -1; // Invalid parameter

    i18n_ubidi_h ubidi_line = NULL;
    ret = i18n_ubidi_create(&ubidi_line);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_set_line(ubidi, start, limit, ubidi_line);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_line_n4
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_line passing invalid limit (equal to start)
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_line_n4(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t start = 10;

    /* limit is equal to start parameter */
    int32_t limit = 10;

    i18n_ubidi_h ubidi_line = NULL;
    ret = i18n_ubidi_create(&ubidi_line);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_set_line(ubidi, start, limit, ubidi_line);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_line_n5
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_line passing invalid limit (lower than start)
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_line_n5(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t start = 10;

    /* limit is lower than start parameter */
    int32_t limit = 5;

    i18n_ubidi_h ubidi_line = NULL;
    ret = i18n_ubidi_create(&ubidi_line);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_set_line(ubidi, start, limit, ubidi_line);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_line_n6
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_line passing invalid limit
 *              (greater than ubidi processed length) and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_line_n6(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t start = 0;

    /* limit is greater than ubidi processed length */
    int32_t limit = 80;

    i18n_ubidi_h ubidi_line = NULL;
    ret = i18n_ubidi_create(&ubidi_line);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_set_line(ubidi, start, limit, ubidi_line);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_line_n7
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_line passing invalid ubidi_line and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_line_n7(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t start = 0;
    int32_t limit = 1;

    i18n_ubidi_h ubidi_line = NULL; // Invalid parameter

    ret = i18n_ubidi_set_line(ubidi, start, limit, ubidi_line);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_inverse_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_inverse and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_set_inverse_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubool is_inverse = true;
    ret = i18n_ubidi_set_inverse(ubidi, is_inverse);
    assert_eq(ret, I18N_ERROR_NONE);

    is_inverse = false;
    ret = i18n_ubidi_is_inverse(ubidi, &is_inverse);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_inverse, true);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_inverse_p2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_inverse and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_set_inverse_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubool is_inverse = false;
    ret = i18n_ubidi_set_inverse(ubidi, is_inverse);
    assert_eq(ret, I18N_ERROR_NONE);

    is_inverse = true;
    ret = i18n_ubidi_is_inverse(ubidi, &is_inverse);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_inverse, false);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_inverse_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_inverse passing invalid ubidi and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_inverse_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter
    i18n_ubool is_inverse = true;

    ret = i18n_ubidi_set_inverse(ubidi, is_inverse);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_context_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_context with the prologue in Arabic
 *              and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_set_context_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    char test_prologue[] = "اختبار";

    int32_t pro_length = get_uchar_length(test_prologue);
    prologue = (i18n_uchar *) malloc(sizeof(i18n_uchar) * (pro_length + 1));
    i18n_ustring_copy_ua(prologue, test_prologue);

    ret = i18n_ubidi_set_context(ubidi, prologue, pro_length, NULL, 0);
    assert_eq(ret, I18N_ERROR_NONE);

    /* Create new text */
    char test_text[] = "<Test> <اختبار> test";

    int32_t text_length = get_uchar_length(test_text);
    i18n_uchar text[text_length + 1];
    i18n_ustring_copy_ua(text, test_text);

    ret = i18n_ubidi_set_para(ubidi, text, text_length, I18N_UBIDI_DEFAULT_LTR, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t dst_size = text_length + 1;
    uint16_t options = I18N_UBIDI_KEEP_BASE_COMBINING;

    int32_t output_length = -1;

    ret = i18n_ubidi_write_reordered(ubidi, options, dst_size,
                                     dst, &output_length);
    assert_eq(ret, I18N_ERROR_NONE);

    char tmp[BUFLEN];
    i18n_ustring_copy_au(tmp, dst);
    int cmp = strcmp(tmp, "test >رابتخا< >Test<");

    assert_eq(cmp, 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_context_p2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_context with the prologue in English
 *              and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_set_context_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    char test_prologue[] = "Test";

    int32_t pro_length = get_uchar_length(test_prologue);
    prologue = (i18n_uchar *) malloc(sizeof(i18n_uchar) * (pro_length + 1));
    i18n_ustring_copy_ua(prologue, test_prologue);

    ret = i18n_ubidi_set_context(ubidi, prologue, pro_length, NULL, 0);
    assert_eq(ret, I18N_ERROR_NONE);

    /* Create new text */
    char test_text[] = "<Test> <اختبار> test";

    int32_t text_length = get_uchar_length(test_text);
    i18n_uchar text[text_length + 1];
    i18n_ustring_copy_ua(text, test_text);

    ret = i18n_ubidi_set_para(ubidi, text, text_length, I18N_UBIDI_DEFAULT_LTR, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t dst_size = text_length + 1;
    uint16_t options = I18N_UBIDI_KEEP_BASE_COMBINING;

    int32_t output_length = -1;

    ret = i18n_ubidi_write_reordered(ubidi, options, dst_size,
                                     dst, &output_length);
    assert_eq(ret, I18N_ERROR_NONE);

    char tmp[BUFLEN];
    i18n_ustring_copy_au(tmp, dst);
    int cmp = strcmp(tmp, "<Test> <رابتخا> test");

    assert_eq(cmp, 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_context_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_context passing invalid ubidi and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_context_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    int32_t pro_length = 0;
    int32_t epi_length = 0;

    ret = i18n_ubidi_set_context(ubidi, NULL, pro_length, NULL, epi_length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_context_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_context passing invalid prologue and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_context_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t pro_length = 1; // Invalid parameter
    int32_t epi_length = 0;

    ret = i18n_ubidi_set_context(ubidi, NULL, pro_length, NULL, epi_length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_context_n3
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_context passing invalid pro_length and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_context_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    prologue = (i18n_uchar *) malloc(sizeof(i18n_uchar) * (BUFLEN));
    i18n_ustring_copy_ua(prologue, "Prologue");

    int32_t pro_length = -2; // Invalid parameter
    int32_t epi_length = 0;

    ret = i18n_ubidi_set_context(ubidi, prologue, pro_length, NULL, epi_length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_context_n4
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_context passing invalid epilogue and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_context_n4(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t pro_length = 0;
    int32_t epi_length = 1; // Invalid parameter

    ret = i18n_ubidi_set_context(ubidi, NULL, pro_length, NULL, epi_length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_context_n5
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_context passing invalid epi_length and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_context_n5(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t pro_length = 0;
    i18n_uchar *epilogue = (i18n_uchar *) malloc(sizeof(i18n_uchar) * (BUFLEN));
    i18n_ustring_copy_ua(epilogue, "Epilogue");

    int32_t epi_length = -2; // Invalid parameter

    ret = i18n_ubidi_set_context(ubidi, NULL, pro_length, epilogue, epi_length);
    free(epilogue);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_class_cb_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_class_cb and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_set_class_cb_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubidi_class_cb new_fn = new_class_cb;

    i18n_ubidi_class_cb old_fn = NULL;

    ret = i18n_ubidi_set_class_cb(ubidi, new_fn, NULL, &old_fn, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    assert_neq(old_fn, NULL);
    assert_eq(old_fn, old_class_cb);

    i18n_ubidi_class_cb ret_fn = NULL;
    const void *context = NULL;

    ret = i18n_ubidi_get_class_cb(ubidi, &ret_fn, &context);
    assert_eq(ret, I18N_ERROR_NONE);

    assert_neq(ret_fn, NULL);
    assert_eq(ret_fn, new_fn);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_class_cb_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_class_cb passing invalid ubidi and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_class_cb_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    i18n_ubidi_class_cb new_fn = new_class_cb;

    ret = i18n_ubidi_set_class_cb(ubidi, new_fn, NULL, NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_set_class_cb_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_set_class_cb passing invalid new_fn and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_set_class_cb_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubidi_class_cb new_fn = NULL; // Invalid parameter

    ret = i18n_ubidi_set_class_cb(ubidi, new_fn, NULL, NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_reorder_visual_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_reorder_visual and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_reorder_visual_p(void)
{
    i18n_ubidi_level_t levels[] = {1, 1, 1, 1, 0, 0, 0, 1, 1, 1};
    int32_t length = 10;
    int32_t valid_index_map[] = {3, 2, 1, 0, 4, 5, 6, 9, 8, 7};

    int32_t index_map[length + 1];

    ret = i18n_ubidi_reorder_visual(levels, length, index_map);
    assert_eq(ret, I18N_ERROR_NONE);

    int i;
    for(i = 0; i < length; ++i)
    {
        assert_eq(index_map[i], valid_index_map[i]);
    }

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_reorder_visual_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_reorder_visual passing invalid levels and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_reorder_visual_n(void)
{
    int32_t length = 10;
    int32_t index_map[length + 1];

    ret = i18n_ubidi_reorder_visual(NULL, length, index_map);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_reorder_visual_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_reorder_visual passing invalid length and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_reorder_visual_n2(void)
{
    i18n_ubidi_level_t levels[] = {1, 1, 1, 1, 0, 0, 0, 1, 1, 1};
    int32_t valid_length = 10;
    int32_t length = -2; // Invalid parameter

    int32_t index_map[valid_length + 1];

    ret = i18n_ubidi_reorder_visual(levels, length, index_map);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_reorder_visual_n3
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_reorder_visual passing invalid index_map and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_reorder_visual_n3(void)
{
    i18n_ubidi_level_t levels[] = {1, 1, 1, 1, 0, 0, 0, 1, 1, 1};
    int32_t length = 10;

    ret = i18n_ubidi_reorder_visual(levels, length, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_reorder_logical_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_reorder_logical and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_reorder_logical_p(void)
{
    i18n_ubidi_level_t levels[] = {1, 1, 1, 1, 0, 0, 0, 1, 1, 1};
    int32_t length = 10;
    int32_t valid_index_map[] = {3, 2, 1, 0, 4, 5, 6, 9, 8, 7};

    int32_t index_map[length + 1];

    ret = i18n_ubidi_reorder_logical(levels, length, index_map);
    assert_eq(ret, I18N_ERROR_NONE);

    int i;
    for(i = 0; i < length; ++i)
    {
        assert_eq(index_map[i], valid_index_map[i]);
    }

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_reorder_logical_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_reorder_logical passing invalid levels and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_reorder_logical_n(void)
{
    int32_t length = 10;
    int32_t index_map[length + 1];

    ret = i18n_ubidi_reorder_logical(NULL, length, index_map);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_reorder_logical_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_reorder_logical passing invalid length and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_reorder_logical_n2(void)
{
    i18n_ubidi_level_t levels[] = {1, 1, 1, 1, 0, 0, 0, 1, 1, 1};

    int32_t length = -2; // Invalid parameter
    int32_t valid_length = 10;
    int32_t index_map[valid_length + 1];

    ret = i18n_ubidi_reorder_logical(levels, length, index_map);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_reorder_logical_n3
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_reorder_logical passing invalid index_map and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_reorder_logical_n3(void)
{
    i18n_ubidi_level_t levels[] = {1, 1, 1, 1, 0, 0, 0, 1, 1, 1};

    int32_t length = 10;

    ret = i18n_ubidi_reorder_logical(levels, length, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_order_paragraphs_ltr_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_order_paragraphs_ltr and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_order_paragraphs_ltr_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubool ret_order_paragraph_ltr = true;
    ret = i18n_ubidi_is_order_paragraphs_ltr(ubidi, &ret_order_paragraph_ltr);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(ret_order_paragraph_ltr, false);

    i18n_ubool order_paragraph_ltr = true;

    ret = i18n_ubidi_order_paragraphs_ltr(ubidi, order_paragraph_ltr);
    assert_eq(ret, I18N_ERROR_NONE);

    int src_length = i18n_ustring_get_length(src);
    ret = i18n_ubidi_set_para(ubidi, src, src_length, I18N_UBIDI_DEFAULT_RTL, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret_order_paragraph_ltr = false;
    ret = i18n_ubidi_is_order_paragraphs_ltr(ubidi, &ret_order_paragraph_ltr);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(ret_order_paragraph_ltr, true);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_order_paragraphs_ltr_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_order_paragraphs_ltr passing invalid ubidi and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_order_paragraphs_ltr_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    i18n_ubool order_paragraph_ltr = true;

    ret = i18n_ubidi_order_paragraphs_ltr(ubidi, order_paragraph_ltr);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_create_sized_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_create_sized and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_create_sized_p(void)
{
    int32_t max_length = 10;
    int32_t max_run_count = 3;

    i18n_ubidi_h ubidi = NULL;
    ret = i18n_ubidi_create_sized(max_length, max_run_count, &ubidi);

    assert_neq(ubidi, NULL);
    i18n_ubidi_destroy(ubidi);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_create_sized_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_create_sized passing invalid max_length and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_create_sized_n(void)
{
    int32_t max_length = -2; // Invalid parameter
    int32_t max_run_count = 3;

    i18n_ubidi_h ubidi = NULL;

    ret = i18n_ubidi_create_sized(max_length, max_run_count, &ubidi);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_create_sized_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_create_sized passing invalid max_run_count and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_create_sized_n2(void)
{
    int32_t max_length = 10;
    int32_t max_run_count = -2; // Invalid parameter

    i18n_ubidi_h ubidi = NULL;

    ret = i18n_ubidi_create_sized(max_length, max_run_count, &ubidi);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_create_sized_n3
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_create_sized passing invalid ubidi and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_create_sized_n3(void)
{
    int32_t max_length = 10;
    int32_t max_run_count = 0;

    ret = i18n_ubidi_create_sized(max_length, max_run_count, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_create_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_create_p(void)
{
    i18n_ubidi_h ubidi = NULL;

    ret = i18n_ubidi_create(&ubidi);

    assert_neq(ubidi, NULL);
    i18n_ubidi_destroy(ubidi);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_create_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_create passing invalid ubidi and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_create_n(void)
{
    ret = i18n_ubidi_create(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_is_order_paragraphs_ltr_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_is_order_paragraphs_ltr and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_is_order_paragraphs_ltr_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubool order_paragraph_ltr = true;

    ret = i18n_ubidi_order_paragraphs_ltr(ubidi, order_paragraph_ltr);
    assert_eq(ret, I18N_ERROR_NONE);

    int src_length = i18n_ustring_get_length(src);
    ret = i18n_ubidi_set_para(ubidi, src, src_length, I18N_UBIDI_DEFAULT_LTR, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubool ret_order_paragraph_ltr = false;
    ret = i18n_ubidi_is_order_paragraphs_ltr(ubidi, &ret_order_paragraph_ltr);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(ret_order_paragraph_ltr, true);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_is_order_paragraphs_ltr_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_is_order_paragraphs_ltr passing invalid ubidi and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_is_order_paragraphs_ltr_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    i18n_ubool is_order = true;

    ret = i18n_ubidi_is_order_paragraphs_ltr(ubidi, &is_order);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_is_order_paragraphs_ltr_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_is_order_paragraphs_ltr passing invalid is_order and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_is_order_paragraphs_ltr_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_is_order_paragraphs_ltr(ubidi, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_is_inverse_p
 * @since_tizen 3.0
 * @description Sets reordering mode to I18N_UBIDI_REORDER_INVERSE_NUMBERS_AS_L,
 *              calls i18n_ubidi_is_inverse and checks whether is_inverse is true.
 */
int utc_capi_base_utils_i18n_ubidi_is_inverse_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubidi_reordering_mode_e mode = I18N_UBIDI_REORDER_INVERSE_NUMBERS_AS_L;
    ret = i18n_ubidi_set_reordering_mode(ubidi, mode);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubool is_inverse = false;
    ret = i18n_ubidi_is_inverse(ubidi, &is_inverse);
    assert_eq(is_inverse, true);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_is_inverse_p2
 * @since_tizen 3.0
 * @description Sets reordering mode to I18N_UBIDI_REORDER_DEFAULT,
 *              calls i18n_ubidi_is_inverse and checks whether is_inverse is false.
 */
int utc_capi_base_utils_i18n_ubidi_is_inverse_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubidi_reordering_mode_e mode = I18N_UBIDI_REORDER_DEFAULT;
    ret = i18n_ubidi_set_reordering_mode(ubidi, mode);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubool is_inverse = true;
    ret = i18n_ubidi_is_inverse(ubidi, &is_inverse);
    assert_eq(is_inverse, false);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_is_inverse_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_is_inverse passing invalid ubidi and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_is_inverse_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    i18n_ubool is_inverse = false;

    ret = i18n_ubidi_is_inverse(ubidi, &is_inverse);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_is_inverse_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_is_inverse passing invalid is_inverse and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_is_inverse_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_is_inverse(ubidi, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_invert_map_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_invert_map and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_invert_map_p(void)
{
    int32_t length = 10;
    int32_t src_map[] = {0, 1, 11, 12, 6, 5, 4, 13, 9, -1};
    int32_t valid_dst_map[] = {0, 1, -1, -1, 6, 5, 4, -1, -1, 8, -1, 2, 3, 7};

    int32_t dst_length = 14;
    int32_t dst_map[dst_length+1];

    ret = i18n_ubidi_invert_map(src_map, length, dst_map);
    assert_eq(ret, I18N_ERROR_NONE);

    int i;
    for(i = 0; i < dst_length; ++i)
    {
        assert_eq(dst_map[i], valid_dst_map[i]);
    }

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_invert_map_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_invert_map passing invalid src_map and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_invert_map_n(void)
{
    int32_t dst_length = 14;
    int32_t dst_map[dst_length+1];
    int32_t length = 10;

    ret = i18n_ubidi_invert_map(NULL, length, dst_map);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_invert_map_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_invert_map passing invalid length and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_invert_map_n2(void)
{
    int32_t src_map[] = {0, 1, 11, 12, 6, 5, 4, 13, 9, -1};
    int32_t dst_length = 14;
    int32_t dst_map[dst_length+1];
    int32_t length = -2; // Invalid parameter

    ret = i18n_ubidi_invert_map(src_map, length, dst_map);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_invert_map_n3
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_invert_map passing invalid dst_map and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_invert_map_n3(void)
{
    int32_t src_map[] = {0, 1, 11, 12, 6, 5, 4, 13, 9, -1};;
    int32_t length = 10;

    ret = i18n_ubidi_invert_map(src_map, length, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_visual_run_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_visual_run and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_visual_run_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    int logical_ind[] = {0, 14, 20, 47, 53};
    int length[] = {14, 6, 27, 6, 12};
    i18n_ubidi_direction_e dir[] = {I18N_UBIDI_LTR, I18N_UBIDI_RTL,
            I18N_UBIDI_LTR, I18N_UBIDI_RTL, I18N_UBIDI_LTR};

    int runs_counter = -1;
    ret = i18n_ubidi_count_runs(ubidi, &runs_counter);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t run_index;
    for(run_index = 0; run_index < runs_counter; ++run_index)
    {
        int32_t p_logical_index = -1;
        int32_t p_length = -1;
        i18n_ubidi_direction_e direction = I18N_UBIDI_MIXED;

        ret = i18n_ubidi_get_visual_run(ubidi, run_index, &p_logical_index, &p_length, &direction);

        assert_eq(p_logical_index, logical_ind[run_index]);
        assert_eq(p_length, length[run_index]);
        assert_eq(direction, dir[run_index]);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_visual_run_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_visual_run passing invalid ubidi and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_visual_run_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    int32_t run_index = 0;
    i18n_ubidi_direction_e direction = I18N_UBIDI_LTR;

    ret = i18n_ubidi_get_visual_run(ubidi, run_index, NULL, NULL, &direction);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_visual_run_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_visual_run passing invalid run_index and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_visual_run_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t run_index = -2; //Invalid parameter
    i18n_ubidi_direction_e direction = I18N_UBIDI_LTR;

    ret = i18n_ubidi_get_visual_run(ubidi, run_index, NULL, NULL, &direction);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_visual_run_n3
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_visual_run passing invalid direction and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_visual_run_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t run_index = 0;

    ret = i18n_ubidi_get_visual_run(ubidi, run_index, NULL, NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_visual_map_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_visual_map and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_visual_map_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    int32_t valid_map[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                           19, 18, 17, 16, 15, 14,
                           20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
                           32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
                           44, 45, 46,
                           52, 51, 50, 49, 48, 47,
                           53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64};

    int32_t length = -1;
    ret = i18n_ubidi_get_result_length(ubidi, &length);
    assert_eq(ret, I18N_ERROR_NONE);
    int32_t index_map[length];

    ret = i18n_ubidi_get_visual_map(ubidi, index_map);

    assert_eq(ret, I18N_ERROR_NONE);
    int i;
    for(i = 0; i < length; ++i)
    {
        assert_eq(index_map[i], valid_map[i]);
    }

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_visual_map_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_visual_map passing invalid ubidi and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_visual_map_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    int32_t length = 1;
    int32_t index_map[length];

    ret = i18n_ubidi_get_visual_map(ubidi, index_map);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_visual_map_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_visual_map passing invalid index_map and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_visual_map_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_get_visual_map(ubidi, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_visual_index_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_visual_index and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_visual_index_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    int32_t valid_map[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                           19, 18, 17, 16, 15, 14,
                           20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
                           32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
                           44, 45, 46,
                           52, 51, 50, 49, 48, 47,
                           53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64};

    int32_t length = -1;
    ret = i18n_ubidi_get_result_length(ubidi, &length);
    assert_eq(ret, I18N_ERROR_NONE);

    int i;
    for(i = 0; i < length; ++i)
    {
        int32_t visual_index = -1;
        ret = i18n_ubidi_get_visual_index(ubidi, i, &visual_index);
        assert_eq(ret, I18N_ERROR_NONE);
        assert_eq(visual_index, valid_map[i]);
    }

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_visual_index_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_visual_index passing invalid ubidi and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_visual_index_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    int32_t logical_index = 0;

    int32_t visual_index = -1;

    ret = i18n_ubidi_get_visual_index(ubidi, logical_index, &visual_index);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_visual_index_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_visual_index passing invalid logical_index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_visual_index_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t logical_index = -2; // Invalid parameter

    int32_t visual_index = -1;

    ret = i18n_ubidi_get_visual_index(ubidi, logical_index, &visual_index);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_visual_index_n3
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_visual_index passing invalid visual_index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_visual_index_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t logical_index = 0;

    ret = i18n_ubidi_get_visual_index(ubidi, logical_index, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_text_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_text and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_text_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    char *text = NULL;

    ret = i18n_ubidi_get_text(ubidi, &text);
    assert_eq(ret, I18N_ERROR_NONE);

    int cmp = strcmp(text, "<Paragraph1> <اختبار> paragraph1\n"
                           "<Paragraph2> <اختبار> paragraph2");
    assert_eq(cmp, 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_text_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_text passing invalid ubidi and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_text_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    char *text = NULL;

    ret = i18n_ubidi_get_text(ubidi, &text);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_text_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_text passing invalid text and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_text_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_get_text(ubidi, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_text_n3
 * @since_tizen 3.0
 * @description Creates ubidi without text and calls i18n_ubidi_get_text for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_text_n3(void)
{
    i18n_ubidi_h ubidi = NULL;
    ret = i18n_ubidi_create(&ubidi);
    assert_eq(ret, I18N_ERROR_NONE);

    char *text = NULL;

    ret = i18n_ubidi_get_text(ubidi, &text);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_result_length_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_result_length and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_result_length_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t length = -1;

    ret = i18n_ubidi_get_result_length(ubidi, &length);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(length, src_length);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_result_length_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_result_length passing invalid ubidi and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_result_length_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    int32_t length = -1;

    ret = i18n_ubidi_get_result_length(ubidi, &length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_result_length_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_result_length passing invalid length and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_result_length_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_get_result_length(ubidi, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_reordering_options_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_reordering_options and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_reordering_options_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_set_reordering_options(ubidi, I18N_UBIDI_OPTION_INSERT_MARKS);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubidi_reordering_option_e options = I18N_UBIDI_OPTION_DEFAULT;
    ret = i18n_ubidi_get_reordering_options(ubidi, &options);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(options, I18N_UBIDI_OPTION_INSERT_MARKS);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_reordering_options_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_reordering_options passing invalid ubidi and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_reordering_options_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    i18n_ubidi_reordering_option_e options = I18N_UBIDI_OPTION_DEFAULT;

    ret = i18n_ubidi_get_reordering_options(ubidi, &options);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_reordering_options_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_reordering_options passing invalid options and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_reordering_options_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_get_reordering_options(ubidi, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_reordering_mode_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_reordering_mode and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_reordering_mode_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_set_reordering_mode(ubidi, I18N_UBIDI_REORDER_NUMBERS_SPECIAL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubidi_reordering_mode_e mode = I18N_UBIDI_REORDER_DEFAULT;

    ret = i18n_ubidi_get_reordering_mode(ubidi, &mode);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(mode, I18N_UBIDI_REORDER_NUMBERS_SPECIAL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_reordering_mode_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_reordering_mode passing invalid ubidi and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_reordering_mode_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    i18n_ubidi_reordering_mode_e mode = I18N_UBIDI_REORDER_DEFAULT;

    ret = i18n_ubidi_get_reordering_mode(ubidi, &mode);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_reordering_mode_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_reordering_mode passing invalid mode and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_reordering_mode_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_get_reordering_mode(ubidi, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_processed_length_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_processed_length and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_processed_length_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t length = -1;

    ret = i18n_ubidi_get_processed_length(ubidi, &length);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(length, src_length);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_processed_length_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_processed_length passing invalid ubidi and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_processed_length_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    int32_t length = -1;

    ret = i18n_ubidi_get_processed_length(ubidi, &length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_processed_length_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_processed_length passing invalid length and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_processed_length_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_get_processed_length(ubidi, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_para_level_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_para_level and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_para_level_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    i18n_ubidi_level_t level = 1;
    ret = i18n_ubidi_get_para_level(ubidi, &level);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(level, 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_para_level_p2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_para_level and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_para_level_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    free(src);
    char test_text[] = "اختبار paragraph1";
    src_length = get_uchar_length(test_text);
    src = (i18n_uchar *) malloc(sizeof(i18n_uchar) * (src_length + 1));
    i18n_ustring_copy_ua(src, test_text);

    ret = i18n_ubidi_set_para(ubidi, src, src_length, I18N_UBIDI_DEFAULT_LTR, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubidi_level_t level = 0;
    ret = i18n_ubidi_get_para_level(ubidi, &level);
    assert_eq(ret, I18N_ERROR_NONE);

    assert_eq(level, 1);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_para_level_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_para_level passing invalid ubidi and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_para_level_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    i18n_ubidi_level_t level = 0;

    ret = i18n_ubidi_get_para_level(ubidi, &level);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_para_level_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_para_level passing invalid level and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_para_level_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_get_para_level(ubidi, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_paragraph_by_index_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_paragraph_by_index and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_paragraph_by_index_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    int32_t valid_para_start[] = {0, 33};
    int32_t valid_para_limit[] = {33, 65};
    i18n_ubidi_level_t valid_para_level[] = {0, 0};

    int32_t count = -1;
    ret = i18n_ubidi_count_paragraphs(ubidi, &count);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t para_index;
    for(para_index = 0; para_index < count; ++para_index)
    {
        int32_t p_para_start = -1;
        int32_t p_para_limit = -1;
        i18n_ubidi_level_t p_para_level = 1;

        ret = i18n_ubidi_get_paragraph_by_index(ubidi, para_index, &p_para_start, &p_para_limit, &p_para_level);

        assert_eq(ret, I18N_ERROR_NONE);
        assert_eq(p_para_start, valid_para_start[para_index]);
        assert_eq(p_para_limit, valid_para_limit[para_index]);
        assert_eq(p_para_level, valid_para_level[para_index]);
    }

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_paragraph_by_index_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_paragraph_by_index passing invalid ubidi and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_paragraph_by_index_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    int32_t para_index = 0;

    ret = i18n_ubidi_get_paragraph_by_index(ubidi, para_index, NULL, NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_paragraph_by_index_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_paragraph_by_index passing invalid para_index
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_paragraph_by_index_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t para_index = -2; // Invalid parameter

    ret = i18n_ubidi_get_paragraph_by_index(ubidi, para_index, NULL, NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_paragraph_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_paragraph and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_paragraph_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    int32_t valid_para_start[] = {0, 33};
    int32_t valid_para_limit[] = {33, 65};
    i18n_ubidi_level_t valid_para_level[] = {0, 0};

    int32_t length = -1;
    ret = i18n_ubidi_get_processed_length(ubidi, &length);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t char_index;
    for(char_index = 0; char_index < length; ++char_index)
    {
        int32_t paragraph_index = -1;
        int32_t p_para_start = -1;
        int32_t p_para_limit = -1;
        i18n_ubidi_level_t p_para_level = 1;

        ret = i18n_ubidi_get_paragraph(ubidi, char_index,
                                       &p_para_start, &p_para_limit,
                                       &p_para_level, &paragraph_index);
        assert_eq(ret, I18N_ERROR_NONE);

        assert_eq(p_para_start, valid_para_start[paragraph_index]);
        assert_eq(p_para_limit, valid_para_limit[paragraph_index]);
        assert_eq(p_para_level, valid_para_level[paragraph_index]);
    }

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_paragraph_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_paragraph passing invalid ubidi and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_paragraph_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    int32_t char_index = 0;
    int32_t paragraph_index = -1;

    ret = i18n_ubidi_get_paragraph(ubidi, char_index, NULL, NULL, NULL, &paragraph_index);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_paragraph_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_paragraph passing invalid char_index and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_paragraph_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t char_index = -1; // Invalid parameter
    int32_t paragraph_index = -1;

    ret = i18n_ubidi_get_paragraph(ubidi, char_index, NULL, NULL, NULL, &paragraph_index);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_paragraph_n3
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_paragraph passing invalid index and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_paragraph_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t char_index = 0;

    ret = i18n_ubidi_get_paragraph(ubidi, char_index, NULL, NULL, NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_logical_run_p
 * @since_tizen 3.0
 * @description Calls i18n_get_logical_run and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_logical_run_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    int valid_p_logical_position[] = {14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
                                      20, 20, 20, 20, 20, 20,
                                      47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
                                      47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
                                      53, 53, 53, 53, 53, 53,
                                      65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65};
    i18n_ubidi_level_t valid_levels[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                         1, 1, 1, 1, 1, 1,
                                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                         1, 1, 1, 1, 1, 1,
                                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    int32_t processed_length = -1;
    ret = i18n_ubidi_get_processed_length(ubidi, &processed_length);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t logical_position;
    for(logical_position = 0; logical_position < processed_length; ++logical_position)
    {
        int32_t p_logical_position = -2;
        i18n_ubidi_level_t level = 2;

        ret = i18n_ubidi_get_logical_run(ubidi, logical_position, &p_logical_position, &level);

        assert_eq(ret, I18N_ERROR_NONE);
        assert_eq(p_logical_position, valid_p_logical_position[logical_position]);
        assert_eq(level, valid_levels[logical_position]);
    }

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_logical_run_n
 * @since_tizen 3.0
 * @description Calls i18n_get_logical_run passing invalid ubidi and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_logical_run_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    int32_t logical_position = 0;

    ret = i18n_ubidi_get_logical_run(ubidi, logical_position, NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_logical_map_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_logical_map and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_logical_map_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    int32_t valid_map[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                           19, 18, 17, 16, 15, 14,
                           20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
                           32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
                           44, 45, 46,
                           52, 51, 50, 49, 48, 47,
                           53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64};

    int32_t length = -1;
    ret = i18n_ubidi_get_result_length(ubidi, &length);
    assert_eq(ret, I18N_ERROR_NONE);
    int32_t index_map[length];

    ret = i18n_ubidi_get_logical_map(ubidi, index_map);

    assert_eq(ret, I18N_ERROR_NONE);
    int i;
    for(i = 0; i < length; ++i)
    {
        assert_eq(index_map[i], valid_map[i]);
    }

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_logical_map_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_logical_map passing invalid ubidi and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_logical_map_n(void)
{
    i18n_ubidi_h invalid_ubidi = NULL; // Invalid parameter

    int32_t length = -1;
    ret = i18n_ubidi_get_result_length(ubidi, &length);
    assert_eq(ret, I18N_ERROR_NONE);
    assert(length > 0);
    int32_t index_map[length];

    ret = i18n_ubidi_get_logical_map(invalid_ubidi, index_map);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_logical_map_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_logical_map passing invalid index_map and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_logical_map_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_get_logical_map(ubidi, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_logical_index_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_logical_index and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_logical_index_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    int32_t valid_map[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                           19, 18, 17, 16, 15, 14,
                           20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
                           32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
                           44, 45, 46,
                           52, 51, 50, 49, 48, 47,
                           53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64};

    int32_t length = -1;
    ret = i18n_ubidi_get_result_length(ubidi, &length);
    assert_eq(ret, I18N_ERROR_NONE);

    int i;
    for(i = 0; i < length; ++i)
    {
        int32_t logical_index = -1;
        ret = i18n_ubidi_get_logical_index(ubidi, i, &logical_index);
        assert_eq(ret, I18N_ERROR_NONE);
        assert_eq(logical_index, valid_map[i]);
    }

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_logical_index_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_logical_index passing invalid ubidi and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_logical_index_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    int32_t visual_index = 0;

    int32_t logical_index = -1;

    ret = i18n_ubidi_get_logical_index(ubidi, visual_index, &logical_index);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_logical_index_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_logical_index passing invalid visual_index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_logical_index_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t visual_index = -2; // Invalid parameter

    int32_t logical_index = -1;

    ret = i18n_ubidi_get_logical_index(ubidi, visual_index, &logical_index);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_logical_index_n3
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_logical_index passing invalid logical_index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_logical_index_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t visual_index = 0;
    ret = i18n_ubidi_get_logical_index(ubidi, visual_index, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_levels_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_levels and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_levels_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    i18n_ubidi_level_t valid_levels[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                         1, 1, 1, 1, 1, 1,
                                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                         1, 1, 1, 1, 1, 1,
                                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    int32_t processed_length = -1;
    ret = i18n_ubidi_get_processed_length(ubidi, &processed_length);
    assert_eq(ret, I18N_ERROR_NONE);

    const i18n_ubidi_level_t *levels = NULL;

    ret = i18n_ubidi_get_levels(ubidi, &levels);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t char_index;
    for(char_index = 0; char_index < processed_length; ++char_index)
    {
        assert_eq(levels[char_index], valid_levels[char_index]);
    }

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_levels_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_levels passing invalid ubidi and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_levels_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    const i18n_ubidi_level_t *levels = NULL;

    ret = i18n_ubidi_get_levels(ubidi, &levels);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_levels_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_levels passing invalid level and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_levels_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_get_levels(ubidi, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_level_at_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_level_at and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_level_at_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    i18n_ubidi_level_t valid_levels[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                         1, 1, 1, 1, 1, 1,
                                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                         1, 1, 1, 1, 1, 1,
                                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    int32_t processed_length = -1;
    ret = i18n_ubidi_get_processed_length(ubidi, &processed_length);
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t char_index;
    i18n_ubidi_level_t levels[processed_length];
    for(char_index = 0; char_index < processed_length; ++char_index)
    {
        ret = i18n_ubidi_get_level_at(ubidi, char_index, &levels[char_index]);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    int i;
    for(i = 0; i < processed_length; ++i)
    {
        assert_eq(levels[i], valid_levels[i]);
    }

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_level_at_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_level_at passing invalid ubidi and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_level_at_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter
    int32_t char_index = 0;

    i18n_ubidi_level_t level = 0;

    ret = i18n_ubidi_get_level_at(ubidi, char_index, &level);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_level_at_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_level_at passing invalid level and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_level_at_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t char_index = 0;

    ret = i18n_ubidi_get_level_at(ubidi, char_index, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_length_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_length and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_length_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t length = -1;

    ret = i18n_ubidi_get_length(ubidi, &length);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(length, src_length);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_length_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_length passing invalid ubidi and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_length_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    int32_t length = -1;

    ret = i18n_ubidi_get_length(ubidi, &length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_length_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_length passing invalid length and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_length_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_get_length(ubidi, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_direction_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_direction and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_direction_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    i18n_ubidi_direction_e direction = I18N_UBIDI_LTR;

    ret = i18n_ubidi_get_direction(ubidi, &direction);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(direction, I18N_UBIDI_MIXED);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_direction_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_direction passing invalid ubidi and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_direction_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    i18n_ubidi_direction_e direction = I18N_UBIDI_LTR;

    ret = i18n_ubidi_get_direction(ubidi, &direction);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_direction_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_direction passing invalid direction and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_direction_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_get_direction(ubidi, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_customized_class_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_customized_class and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_customized_class_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar32 c = 0;
    i18n_uchar_direction_e direction = L;

    ret = i18n_ubidi_get_customized_class(ubidi, c, &direction);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(direction, R);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_customized_class_p2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_customized_class and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_customized_class_p2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar32 c = 1;
    i18n_uchar_direction_e direction = R;

    ret = i18n_ubidi_get_customized_class(ubidi, c, &direction);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(direction, L);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_customized_class_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_customized_class passing invalid ubidi and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_customized_class_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    i18n_uchar32 c = 0;

    i18n_uchar_direction_e direction;

    ret = i18n_ubidi_get_customized_class(ubidi, c, &direction);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_customized_class_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_customized_class passing invalid direction and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_customized_class_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar32 c = 0;

    ret = i18n_ubidi_get_customized_class(ubidi, c, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_class_cb_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_class_cb and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_class_cb_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ubidi_class_cb new_fn = new_class_cb;

    i18n_ubidi_class_cb old_fn = NULL;

    ret = i18n_ubidi_set_class_cb(ubidi, new_fn, NULL, &old_fn, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    assert_neq(old_fn, NULL);
    assert_eq(old_fn, old_class_cb);

    i18n_ubidi_class_cb ret_fn = NULL;
    const void *context = NULL;

    ret = i18n_ubidi_get_class_cb(ubidi, &ret_fn, &context);
    assert_eq(ret, I18N_ERROR_NONE);

    assert_neq(ret_fn, NULL);
    assert_eq(ret_fn, new_fn);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_class_cb_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_class_cb passing invalid ubidi and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_class_cb_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    i18n_ubidi_class_cb fn = NULL;
    const void *context = NULL;

    ret = i18n_ubidi_get_class_cb(ubidi, &fn, &context);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_base_direction_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_base_direction and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_get_base_direction_p(void)
{
    i18n_ubidi_direction_e direction = I18N_UBIDI_LTR;

    ret = i18n_ubidi_get_base_direction(src, src_length, &direction);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(direction, I18N_UBIDI_LTR);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_base_direction_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_base_direction passing invalid text and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_base_direction_n(void)
{
    i18n_uchar *text = NULL; // Invalid parameter

    i18n_ubidi_direction_e direction = I18N_UBIDI_LTR;

    ret = i18n_ubidi_get_base_direction(text, src_length, &direction);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_base_direction_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_base_direction passing invalid length and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_base_direction_n2(void)
{
    int32_t length = -2; // Invalid parameter

    i18n_ubidi_direction_e direction = I18N_UBIDI_LTR;

    ret = i18n_ubidi_get_base_direction(src, length, &direction);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_get_base_direction_n3
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_get_base_direction passing invalid direction and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_get_base_direction_n3(void)
{
    ret = i18n_ubidi_get_base_direction(src, src_length, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_count_runs_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_count_runs and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_count_runs_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    if (check_current_locale())
        return 0;

    int32_t count = -1;

    ret = i18n_ubidi_count_runs(ubidi, &count);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(count, 5);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_count_runs_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_count_runs passing invalid ubidi and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_count_runs_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    int32_t count = -1;

    ret = i18n_ubidi_count_runs(ubidi, &count);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_count_runs_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_count_runs passing invalid count and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_count_runs_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_count_runs(ubidi, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_count_paragraphs_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_count_paragraphs and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_count_paragraphs_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t count = -1;

    ret = i18n_ubidi_count_paragraphs(ubidi, &count);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(count, 2);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_count_paragraphs_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_count_paragraphs passing invalid ubidi and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_count_paragraphs_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    int32_t count = -1;

    ret = i18n_ubidi_count_paragraphs(ubidi, &count);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_count_paragraphs_n2
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_count_paragraphs passing invalid count and checks
 *              for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_count_paragraphs_n2(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_count_paragraphs(ubidi, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_destroy_p
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ubidi_destroy_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubidi_destroy(ubidi);
    assert_eq(ret, I18N_ERROR_NONE);
    ubidi = NULL;

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ubidi_destroy_n
 * @since_tizen 3.0
 * @description Calls i18n_ubidi_destroy passing invalid ubidi and checks for an
 *              invalid parameter error code.
 */
int utc_capi_base_utils_i18n_ubidi_destroy_n(void)
{
    i18n_ubidi_h ubidi = NULL; // Invalid parameter

    ret = i18n_ubidi_destroy(ubidi);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
