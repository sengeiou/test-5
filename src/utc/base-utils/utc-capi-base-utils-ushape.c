#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

#define LENGTHOF(array) (sizeof(array)/sizeof((array)[0]))

static const i18n_uchar en_digits[] = {
        0x30,   /* Unicode Digit Zero */
        0x31,   /* Unicode Digit One */
        0x32,   /* Unicode Digit Two */
        0x33,   /* Unicode Digit Three */
        0x34,   /* Unicode Digit Four */
        0x35,   /* Unicode Digit Five */
        0x36,   /* Unicode Digit Six */
        0x37,   /* Unicode Digit Seven */
        0x38,   /* Unicode Digit Eight */
        0x39,   /* Unicode Digit Nine */
        0
};

static const i18n_uchar an_digits[] = {
        0x660,   /* Arabic-Indic Digit Zero */
        0x661,   /* Arabic-Indic Digit One */
        0x662,   /* Arabic-Indic Digit Two */
        0x663,   /* Arabic-Indic Digit Three */
        0x664,   /* Arabic-Indic Digit Four */
        0x665,   /* Arabic-Indic Digit Five */
        0x666,   /* Arabic-Indic Digit Six */
        0x667,   /* Arabic-Indic Digit Seven */
        0x668,   /* Arabic-Indic Digit Eight */
        0x669,   /* Arabic-Indic Digit Nine */
        0
};

static const i18n_uchar extended_an_digits[] = {
        0x6F0,   /* Extended Arabic-Indic Digit Zero */
        0x6F1,   /* Extended Arabic-Indic Digit One */
        0x6F2,   /* Extended Arabic-Indic Digit Two */
        0x6F3,   /* Extended Arabic-Indic Digit Three */
        0x6F4,   /* Extended Arabic-Indic Digit Four */
        0x6F5,   /* Extended Arabic-Indic Digit Five */
        0x6F6,   /* Extended Arabic-Indic Digit Six */
        0x6F7,   /* Extended Arabic-Indic Digit Seven */
        0x6F8,   /* Extended Arabic-Indic Digit Eight */
        0x6F9,   /* Extended Arabic-Indic Digit Nine */
        0
};

static const i18n_uchar mixed[] = {
        0x31,   /* en:1 */
        0x627,  /* arabic:alef */
        0x32,   /* en:2 */
        0x6f3,  /* ex an:3 */
        0x61,   /* latin:a */
        0x34,   /* en:4 */
        0x664,  /* an: 4 */
        0x668,  /* an: 8 */
        0x6F9,  /* ex an: 9 */
        0
};

static const i18n_uchar mixed_en2an[] = {
        0x661, 0x627, 0x662, 0x6f3, 0x61, 0x664, 0x664, 0x668, 0x6F9, 0
};

static const i18n_uchar mixed_an2en[] = {
        0x31, 0x627, 0x32, 0x6f3, 0x61, 0x34, 0x34, 0x38, 0x6F9, 0
};

static const i18n_uchar mixed_exan2en[] = {
        0x31, 0x627, 0x32, 0x33, 0x61, 0x34, 0x664, 0x668, 0x39, 0
};

static const i18n_uchar mixed_alen2an_al[] = {
        0x661, 0x627, 0x662, 0x6f3, 0x61, 0x34, 0x664, 0x668, 0x6F9, 0
};

static const i18n_uchar mixed_alen2an_lr[] = {
        0x31, 0x627, 0x662, 0x6f3, 0x61, 0x34, 0x664, 0x668, 0x6F9, 0
};

static const i18n_uchar persian_letters_source[] = {
        0x0020, 0x0698, 0x067E, 0x0686, 0x06AF, 0x0020, 0
};

static const i18n_uchar persian_letters_source_2[] = {
        0x0020, 0x06d0, 0x67B, 0x06d0, 0x0020, 0
};

static const i18n_uchar persian_letters_ltr[] = {
        0x0020, 0xFB8B, 0xFB59, 0xFB7D, 0xFB94, 0x0020, 0
};

static const i18n_uchar persian_letters_ltr_2[] = {
        0x0020, 0xfbe5, 0xfb55, 0xfbe6, 0x0020, 0
};

static const i18n_uchar persian_letters_rtl[] = {
        0x0020, 0xfb8a, 0xFB58, 0xFB7D, 0xFB93, 0x0020, 0
};

static const i18n_uchar persian_letters_rtl2[] = {
        0x0020, 0xfbe6, 0xfb55, 0xfbe5, 0x0020, 0
};

static const i18n_uchar untouched_presentation_source[] = {
        0x0020 ,0x0627, 0xfe90, 0x0020, 0
};

static const i18n_uchar untouched_presentation[] = {
        0x0020,0xfe8D, 0xfe90, 0x0020, 0
};

static const i18n_uchar untouched_presentation_r_source[] = {
        0x0020 ,0xfe90, 0x0627, 0x0020, 0
};

static const i18n_uchar untouched_presentation_r[] = {
        0x0020, 0xfe90, 0xfe8D, 0x0020, 0
};

static const i18n_uchar tashkeel_aggregation_source[] = {
        0x0020, 0x0628, 0x0651, 0x064E, 0x062A, 0x0631, 0x0645, 0x0020,
        0x0628, 0x064E, 0x0651, 0x062A, 0x0631, 0x0645, 0x0020, 0
};

static const i18n_uchar tashkeel_aggregation_source_2[] = {
        0x0020, 0x67B, 0x0651, 0x064C, 0x0651, 0x064F, 0x0631, 0x0645, 0x0020, 0
};

static const i18n_uchar tashkeel_aggregation[] = {
        0x0020, 0xFE90, 0xFC60, 0xFE97, 0xFEAE, 0xFEE3,
        0x0020, 0xFE90, 0xFC60, 0xFE97, 0xFEAE, 0xFEE3, 0x0020, 0
};

static const i18n_uchar tashkeel_aggregation_2[] = {
        0x0020, 0xfb52, 0xFC5E, 0xFC61, 0xFEAE, 0xFEE3, 0x0020, 0
};

static const i18n_uchar tashkeel_begin_end_source_1[] = {
        0x0634, 0x0651, 0x0645, 0x0652, 0x0633, 0x064C
};

static const i18n_uchar tashkeel_begin_end_source_2[] = {
        0x0633, 0x0652, 0x0645, 0x0651, 0x0634, 0x064F
};

static const i18n_uchar tashkeel_begin_1[] = {
        0x0020, 0x0020, 0xFEB7, 0xFE7D, 0xFEE4, 0xFEB2
};

static const i18n_uchar tashkeel_begin_2[] = {
        0x0020, 0x0020, 0xFEB2, 0xFEE4, 0xFE7D, 0xFEB7
};

static const i18n_uchar tashkeel_end_1[] = {
        0xFEB7, 0xFE7D, 0xFEE4, 0xFEB2, 0x0020, 0x0020
};

static const i18n_uchar tashkeel_end_2[] = {
        0xFEB2, 0xFEE4, 0xFE7D, 0xFEB7, 0x0020, 0x0020
};

static const i18n_uchar tashkeel_resize_1[] = {
        0xFEB7, 0xFE7D, 0xFEE4, 0xFEB2
};

static const i18n_uchar tashkeel_resize_2[] = {
        0xFEB2 ,0xFEE4, 0xFE7D, 0xFEB7
};

static const i18n_uchar tashkeel_replace_1[] = {
        0x0020, 0xFEB7, 0xFE7D, 0xFEE4, 0x0640, 0xFEB2
};

static const i18n_uchar tashkeel_replace_2[] = {
        0xFEB2, 0x0640, 0xFEE4, 0xFE7D, 0xFEB7, 0x0020
};

static const i18n_uchar yehhamza_source_1[] = {
        0x0651, 0x0626, 0x0020, 0x0634, 0x064E, 0xFEB7, 0
};

static const i18n_uchar yehhamza_source_2[] = {
        0x0626, 0x0020, 0x0633, 0x0626, 0x0020, 0xFEE4, 0
};

static const i18n_uchar yehhamza_1[] = {
        0xfe7c, 0xfeef, 0xfe80, 0xfeb7, 0xfe77, 0xfeb6, 0
};

static const i18n_uchar yehhamza_2[] = {
        0xfeef, 0xfe80, 0xfeb3, 0xfef0, 0xfe80, 0xfee1, 0
};

static const i18n_uchar seen_source_1[] = {
        0x064E, 0x0651, 0xFEB7, 0x0633, 0x0020, 0
};

static const i18n_uchar seen_1[] = {
        0xfe76, 0xfe7c, 0xfeb7, 0xfeb2, 0x200b, 0
};

static const i18n_uchar seen_new_unicode[] = {
        0xfe76, 0xfe7c, 0xfeb7, 0xfeb2, 0xFE73, 0
};

static int ret = I18N_ERROR_NONE;

/**
 * @function        utc_capi_base_utils_ushape_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_ushape_startup(void)
{
}

/**
 * @function        utc_capi_base_utils_ushape_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_ushape_cleanup(void)
{
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_p
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with the #I18N_USHAPE_DIGITS_NOOP option to check
 *              whether no changes will be made to the digits.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_p(void)
{
    i18n_uchar dest[12];
    int32_t dest_len;


    ret = i18n_ushape_shape_arabic(en_digits, LENGTHOF(en_digits),
            I18N_USHAPE_DIGITS_NOOP,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(en_digits));
    assert_eq(memcmp(dest, en_digits, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(an_digits, LENGTHOF(an_digits),
            I18N_USHAPE_DIGITS_NOOP,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(an_digits));
    assert_eq(memcmp(dest, an_digits, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(extended_an_digits, LENGTHOF(extended_an_digits),
            I18N_USHAPE_DIGITS_NOOP,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(extended_an_digits));
    assert_eq(memcmp(dest, extended_an_digits, dest_len*U_SIZEOF_UCHAR), 0);

    ret = i18n_ushape_shape_arabic(mixed, LENGTHOF(mixed),
            I18N_USHAPE_DIGITS_NOOP,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(mixed));
    assert_eq(memcmp(dest, mixed, dest_len*U_SIZEOF_UCHAR), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_p2
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with the #I18N_USHAPE_DIGITS_EN2AN option to check
 *              whether the European digits will be replaced by Arabic-Indic digits.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_p2(void)
{
    i18n_uchar dest[12];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(en_digits, LENGTHOF(en_digits),
            I18N_USHAPE_DIGITS_EN2AN,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(an_digits));
    assert_eq(memcmp(dest, an_digits, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(an_digits, LENGTHOF(an_digits),
            I18N_USHAPE_DIGITS_EN2AN,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(an_digits));
    assert_eq(memcmp(dest, an_digits, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(extended_an_digits, LENGTHOF(extended_an_digits),
            I18N_USHAPE_DIGITS_EN2AN,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(extended_an_digits));
    assert_eq(memcmp(dest, extended_an_digits, dest_len*U_SIZEOF_UCHAR), 0);

    ret = i18n_ushape_shape_arabic(mixed, LENGTHOF(mixed),
            I18N_USHAPE_DIGITS_EN2AN,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(mixed_en2an));
    assert_eq(memcmp(dest, mixed_en2an, dest_len*U_SIZEOF_UCHAR), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_p3
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with the #I18N_USHAPE_DIGITS_AN2EN option to check
 *              whether the Arabic-Indic digits will be replaced by European digits.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_p3(void)
{
    i18n_uchar dest[12];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(en_digits, LENGTHOF(en_digits),
            I18N_USHAPE_DIGITS_AN2EN,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(en_digits));
    assert_eq(memcmp(dest, en_digits, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(an_digits, LENGTHOF(an_digits),
            I18N_USHAPE_DIGITS_AN2EN,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(en_digits));
    assert_eq(memcmp(dest, en_digits, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(extended_an_digits, LENGTHOF(extended_an_digits),
            I18N_USHAPE_DIGITS_AN2EN,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(extended_an_digits));
    assert_eq(memcmp(dest, extended_an_digits, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(mixed, LENGTHOF(mixed),
            I18N_USHAPE_DIGITS_AN2EN,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(mixed_an2en));
    assert_eq(memcmp(dest, mixed_an2en, dest_len*U_SIZEOF_UCHAR), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_p4
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with the #I18N_USHAPE_DIGITS_AN2EN, #I18N_USHAPE_DIGIT_TYPE_AN_EXTENDED option to check
 *              whether the Extended Arabic-Indic digits will be replaced by European digits.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_p4(void)
{
    i18n_uchar dest[12];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(en_digits, LENGTHOF(en_digits),
            I18N_USHAPE_DIGITS_AN2EN | I18N_USHAPE_DIGIT_TYPE_AN_EXTENDED,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(en_digits));
    assert_eq(memcmp(dest, en_digits, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(an_digits, LENGTHOF(an_digits),
            I18N_USHAPE_DIGITS_AN2EN | I18N_USHAPE_DIGIT_TYPE_AN_EXTENDED,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(an_digits));
    assert_eq(memcmp(dest, an_digits, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(extended_an_digits, LENGTHOF(extended_an_digits),
            I18N_USHAPE_DIGITS_AN2EN | I18N_USHAPE_DIGIT_TYPE_AN_EXTENDED,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(en_digits));
    assert_eq(memcmp(dest, en_digits, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(mixed, LENGTHOF(mixed),
            I18N_USHAPE_DIGITS_AN2EN | I18N_USHAPE_DIGIT_TYPE_AN_EXTENDED,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(mixed_exan2en));
    assert_eq(memcmp(dest, mixed_exan2en, dest_len*U_SIZEOF_UCHAR), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_p5
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with the #I18N_USHAPE_DIGITS_ALEN2AN_INIT_AL option to check
 *              whether the European digits will be replaced by Arabic-Indic digits if the most recent strongly
 *              directional character is an Arabic letter. For the first characters, the preceding strongly directional
 *              character (initial state) is assumed to be an Arabic letter.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_p5(void)
{
    i18n_uchar dest[12];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(en_digits, LENGTHOF(en_digits),
            I18N_USHAPE_DIGITS_ALEN2AN_INIT_AL,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(an_digits));
    assert_eq(memcmp(dest, an_digits, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(an_digits, LENGTHOF(an_digits),
            I18N_USHAPE_DIGITS_ALEN2AN_INIT_AL,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(an_digits));
    assert_eq(memcmp(dest, an_digits, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(extended_an_digits, LENGTHOF(extended_an_digits),
            I18N_USHAPE_DIGITS_ALEN2AN_INIT_AL,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(extended_an_digits));
    assert_eq(memcmp(dest, extended_an_digits, dest_len*U_SIZEOF_UCHAR), 0);

    ret = i18n_ushape_shape_arabic(mixed, LENGTHOF(mixed),
            I18N_USHAPE_DIGITS_ALEN2AN_INIT_AL,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(mixed_alen2an_al));
    assert_eq(memcmp(dest, mixed_alen2an_al, dest_len*U_SIZEOF_UCHAR), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_p6
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with the #I18N_USHAPE_DIGITS_ALEN2AN_INIT_LR option to check
 *              whether the European digits will be replaced by Arabic-Indic digits if the most recent strongly
 *              directional character is an Arabic letter. For the first characters, the preceding strongly directional
 *              character (initial state) is assumed to be not an Arabic letter.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_p6(void)
{
    i18n_uchar dest[12];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(en_digits, LENGTHOF(en_digits),
            I18N_USHAPE_DIGITS_ALEN2AN_INIT_LR,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(en_digits));
    assert_eq(memcmp(dest, en_digits, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(an_digits, LENGTHOF(an_digits),
            I18N_USHAPE_DIGITS_ALEN2AN_INIT_LR,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(an_digits));
    assert_eq(memcmp(dest, an_digits, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(extended_an_digits, LENGTHOF(extended_an_digits),
            I18N_USHAPE_DIGITS_ALEN2AN_INIT_LR,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(extended_an_digits));
    assert_eq(memcmp(dest, extended_an_digits, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(mixed, LENGTHOF(mixed),
            I18N_USHAPE_DIGITS_ALEN2AN_INIT_LR,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(mixed_alen2an_lr));
    assert_eq(memcmp(dest, mixed_alen2an_lr, dest_len*U_SIZEOF_UCHAR), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_p7
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with the #I18N_USHAPE_TEXT_DIRECTION_VISUAL_LTR, #I18N_USHAPE_LETTERS_SHAPE
 *              option to check whether all letters will be shaped properly with LTR direction.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_p7(void)
{
    i18n_uchar dest[12];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(persian_letters_source, LENGTHOF(persian_letters_source),
            I18N_USHAPE_TEXT_DIRECTION_VISUAL_LTR | I18N_USHAPE_LETTERS_SHAPE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(persian_letters_ltr));
    assert_eq(memcmp(dest, persian_letters_ltr, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(persian_letters_source_2, LENGTHOF(persian_letters_source_2),
            I18N_USHAPE_TEXT_DIRECTION_VISUAL_LTR | I18N_USHAPE_LETTERS_SHAPE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(persian_letters_ltr_2));
    assert_eq(memcmp(dest, persian_letters_ltr_2, dest_len*U_SIZEOF_UCHAR), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_p8
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with the #I18N_USHAPE_TEXT_DIRECTION_VISUAL_RTL, #I18N_USHAPE_LETTERS_SHAPE
 *              option to check whether all letters will be shaped properly with RTL direction.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_p8(void)
{
    i18n_uchar dest[12];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(persian_letters_source, LENGTHOF(persian_letters_source),
            I18N_USHAPE_TEXT_DIRECTION_VISUAL_RTL | I18N_USHAPE_LETTERS_SHAPE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(persian_letters_rtl));
    assert_eq(memcmp(dest, persian_letters_rtl, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(persian_letters_source_2, LENGTHOF(persian_letters_source_2),
            I18N_USHAPE_TEXT_DIRECTION_VISUAL_RTL | I18N_USHAPE_LETTERS_SHAPE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(persian_letters_rtl2));
    assert_eq(memcmp(dest, persian_letters_rtl2, dest_len*U_SIZEOF_UCHAR), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_p9
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with the #I18N_USHAPE_PRESERVE_PRESENTATION, #I18N_USHAPE_LETTERS_SHAPE,
 *              #I18N_USHAPE_TEXT_DIRECTION_VISUAL_LTR, #I18N_USHAPE_TEXT_DIRECTION_LOGICAL option to check whether Arabic Presentation
 *              Forms-A and Arabic Presentation Forms-B characters will not be replaced with 0+06xx characters before shaping.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_p9(void)
{
    i18n_uchar dest[12];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(untouched_presentation_source, LENGTHOF(untouched_presentation_source),
            I18N_USHAPE_PRESERVE_PRESENTATION | I18N_USHAPE_LETTERS_SHAPE | I18N_USHAPE_TEXT_DIRECTION_VISUAL_LTR,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(untouched_presentation));
    assert_eq(memcmp(dest, untouched_presentation, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(untouched_presentation_r_source, LENGTHOF(untouched_presentation_r_source),
            I18N_USHAPE_PRESERVE_PRESENTATION | I18N_USHAPE_LETTERS_SHAPE | I18N_USHAPE_TEXT_DIRECTION_LOGICAL,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(untouched_presentation_r));
    assert_eq(memcmp(dest, untouched_presentation_r, dest_len*U_SIZEOF_UCHAR), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_p10
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with the #I18N_USHAPE_LETTERS_NOOP option to check
 *              whether no changes will be made to the letters.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_p10(void)
{
    i18n_uchar dest[12];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(persian_letters_source, LENGTHOF(persian_letters_source),
            I18N_USHAPE_LETTERS_NOOP,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(persian_letters_source));
    assert_eq(memcmp(dest, persian_letters_source, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(persian_letters_source_2, LENGTHOF(persian_letters_source_2),
            I18N_USHAPE_LETTERS_NOOP,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(persian_letters_source_2));
    assert_eq(memcmp(dest, persian_letters_source_2, dest_len*U_SIZEOF_UCHAR), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_p11
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with the #I18N_USHAPE_LETTERS_UNSHAPE, #I18N_USHAPE_TEXT_DIRECTION_VISUAL_LTR,
 *              #I18N_USHAPE_TEXT_DIRECTION_VISUAL_RTL option to check whether all shaped letters will be replaced by abstract ones.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_p11(void)
{
    i18n_uchar dest[12];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(persian_letters_ltr, LENGTHOF(persian_letters_ltr),
            I18N_USHAPE_TEXT_DIRECTION_VISUAL_LTR | I18N_USHAPE_LETTERS_UNSHAPE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(persian_letters_source));
    assert_eq(memcmp(dest, persian_letters_source, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(persian_letters_rtl2, LENGTHOF(persian_letters_rtl2),
            I18N_USHAPE_TEXT_DIRECTION_VISUAL_RTL | I18N_USHAPE_LETTERS_UNSHAPE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(persian_letters_source_2));
    assert_eq(memcmp(dest, persian_letters_source_2, dest_len*U_SIZEOF_UCHAR), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_p12
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with the #I18N_USHAPE_AGGREGATE_TASHKEEL, #I18N_USHAPE_PRESERVE_PRESENTATION,
 *              #I18N_USHAPE_LETTERS_SHAPE_TASHKEEL_ISOLATED, #I18N_USHAPE_TEXT_DIRECTION_VISUAL_LTR option to check
 *              whether any combination of U+0651 with one of U+064C, U+064D, U+064E, U+064F, U+0650 will be replaced
 *              with U+FC5E, U+FC5F, U+FC60, U+FC61, U+FC62 consecutively.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_p12(void)
{
    i18n_uchar dest[20];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(tashkeel_aggregation_source, LENGTHOF(tashkeel_aggregation_source),
            I18N_USHAPE_AGGREGATE_TASHKEEL|I18N_USHAPE_PRESERVE_PRESENTATION|
            I18N_USHAPE_LETTERS_SHAPE_TASHKEEL_ISOLATED|I18N_USHAPE_TEXT_DIRECTION_VISUAL_LTR,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(tashkeel_aggregation));
    assert_eq(memcmp(dest, tashkeel_aggregation, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(tashkeel_aggregation_source_2, LENGTHOF(tashkeel_aggregation_source_2),
            I18N_USHAPE_AGGREGATE_TASHKEEL|I18N_USHAPE_PRESERVE_PRESENTATION|
            I18N_USHAPE_LETTERS_SHAPE_TASHKEEL_ISOLATED|I18N_USHAPE_TEXT_DIRECTION_VISUAL_LTR,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(tashkeel_aggregation_2));
    assert_eq(memcmp(dest, tashkeel_aggregation_2, dest_len*U_SIZEOF_UCHAR), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_p13
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with the #I18N_USHAPE_TEXT_DIRECTION_VISUAL_RTL, #I18N_USHAPE_TEXT_DIRECTION_VISUAL_LTR,
 *              #I18N_USHAPE_TASHKEEL_BEGIN, #I18N_USHAPE_LETTERS_SHAPE option to check whether all tashkeel
 *              characters will be replaced by spaces. Spaces should be placed at the beginning of the buffer.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_p13(void)
{
    i18n_uchar dest[15];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(tashkeel_begin_end_source_1, LENGTHOF(tashkeel_begin_end_source_1),
            I18N_USHAPE_TEXT_DIRECTION_VISUAL_RTL | I18N_USHAPE_TASHKEEL_BEGIN | I18N_USHAPE_LETTERS_SHAPE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(tashkeel_begin_1));
    assert_eq(memcmp(dest, tashkeel_begin_1, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(tashkeel_begin_end_source_2, LENGTHOF(tashkeel_begin_end_source_2),
            I18N_USHAPE_TEXT_DIRECTION_VISUAL_LTR | I18N_USHAPE_TASHKEEL_BEGIN | I18N_USHAPE_LETTERS_SHAPE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(tashkeel_begin_2));
    assert_eq(memcmp(dest, tashkeel_begin_2, dest_len*U_SIZEOF_UCHAR), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_p14
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with the #I18N_USHAPE_TEXT_DIRECTION_VISUAL_RTL, #I18N_USHAPE_TEXT_DIRECTION_VISUAL_LTR,
 *              #I18N_USHAPE_TASHKEEL_END, #I18N_USHAPE_LETTERS_SHAPE option to check whether all tashkeel
 *              characters will be replaced by spaces. Spaces should be placed at the end of the buffer.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_p14(void)
{
    i18n_uchar dest[15];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(tashkeel_begin_end_source_1, LENGTHOF(tashkeel_begin_end_source_1),
            I18N_USHAPE_TEXT_DIRECTION_VISUAL_RTL | I18N_USHAPE_TASHKEEL_END | I18N_USHAPE_LETTERS_SHAPE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(tashkeel_end_1));
    assert_eq(memcmp(dest, tashkeel_end_1, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(tashkeel_begin_end_source_2, LENGTHOF(tashkeel_begin_end_source_2),
            I18N_USHAPE_TEXT_DIRECTION_VISUAL_LTR | I18N_USHAPE_TASHKEEL_END | I18N_USHAPE_LETTERS_SHAPE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(tashkeel_end_2));
    assert_eq(memcmp(dest, tashkeel_end_2, dest_len*U_SIZEOF_UCHAR), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_p15
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with the #I18N_USHAPE_TEXT_DIRECTION_VISUAL_RTL, #I18N_USHAPE_TEXT_DIRECTION_VISUAL_LTR,
 *              #I18N_USHAPE_TASHKEEL_RESIZE, #I18N_USHAPE_LETTERS_SHAPE option to check whether all tashkeel
 *              characters will be removed. Buffer length should shrink.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_p15(void)
{
    i18n_uchar dest[15];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(tashkeel_begin_end_source_1, LENGTHOF(tashkeel_begin_end_source_1),
            I18N_USHAPE_TEXT_DIRECTION_VISUAL_RTL | I18N_USHAPE_TASHKEEL_RESIZE | I18N_USHAPE_LETTERS_SHAPE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(tashkeel_resize_1));
    assert_eq(memcmp(dest, tashkeel_resize_1, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(tashkeel_begin_end_source_2, LENGTHOF(tashkeel_begin_end_source_2),
            I18N_USHAPE_TEXT_DIRECTION_VISUAL_LTR | I18N_USHAPE_TASHKEEL_RESIZE | I18N_USHAPE_LETTERS_SHAPE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(tashkeel_resize_2));
    assert_eq(memcmp(dest, tashkeel_resize_2, dest_len*U_SIZEOF_UCHAR), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_p16
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with the #I18N_USHAPE_TEXT_DIRECTION_VISUAL_RTL, #I18N_USHAPE_TEXT_DIRECTION_VISUAL_LTR,
 *              #I18N_USHAPE_TASHKEEL_REPLACE_BY_TATWEEL, #I18N_USHAPE_LETTERS_SHAPE option to check whether all tashkeel
 *              characters will be replaced by tatweel if they were connected to adjacent characters(i.e. shaped on Tatweel) or replaced
 *              by space if they were not connected.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_p16(void)
{
    i18n_uchar dest[15];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(tashkeel_begin_end_source_1, LENGTHOF(tashkeel_begin_end_source_1),
            I18N_USHAPE_TEXT_DIRECTION_VISUAL_RTL | I18N_USHAPE_TASHKEEL_REPLACE_BY_TATWEEL | I18N_USHAPE_LETTERS_SHAPE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(tashkeel_replace_1));
    assert_eq(memcmp(dest, tashkeel_replace_1, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(tashkeel_begin_end_source_2, LENGTHOF(tashkeel_begin_end_source_2),
            I18N_USHAPE_TEXT_DIRECTION_VISUAL_LTR | I18N_USHAPE_TASHKEEL_REPLACE_BY_TATWEEL | I18N_USHAPE_LETTERS_SHAPE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(tashkeel_replace_2));
    assert_eq(memcmp(dest, tashkeel_replace_2, dest_len*U_SIZEOF_UCHAR), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_p17
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with the #I18N_USHAPE_YEHHAMZA_TWOCELL_NEAR, #I18N_USHAPE_LETTERS_SHAPE
 *              option to check whether YEHHAMZA characters will expand into two characters using space near it.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_p17(void)
{
    i18n_uchar dest[15];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(yehhamza_source_1, LENGTHOF(yehhamza_source_1),
            I18N_USHAPE_YEHHAMZA_TWOCELL_NEAR | I18N_USHAPE_LETTERS_SHAPE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(yehhamza_1));
    assert_eq(memcmp(dest, yehhamza_1, dest_len*U_SIZEOF_UCHAR), 0);


    ret = i18n_ushape_shape_arabic(yehhamza_source_2, LENGTHOF(yehhamza_source_2),
            I18N_USHAPE_YEHHAMZA_TWOCELL_NEAR | I18N_USHAPE_LETTERS_SHAPE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(yehhamza_2));
    assert_eq(memcmp(dest, yehhamza_2, dest_len*U_SIZEOF_UCHAR), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_p18
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with the #I18N_USHAPE_SEEN_TWOCELL_NEAR, #I18N_USHAPE_LETTERS_SHAPE
 *              option to check whether SEEN family characters will expand into two characters using space near the SEEN family character.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_p18(void)
{
    i18n_uchar dest[15];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(seen_source_1, LENGTHOF(seen_source_1),
            I18N_USHAPE_SEEN_TWOCELL_NEAR  | I18N_USHAPE_LETTERS_SHAPE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(seen_1));
    assert_eq(memcmp(dest, seen_1, dest_len*U_SIZEOF_UCHAR), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_p19
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with the #I18N_USHAPE_SEEN_TWOCELL_NEAR, #I18N_USHAPE_LETTERS_SHAPE
 *              #I18N_USHAPE_TAIL_NEW_UNICODE option to check whether shaping will use new Unicode code point for TAIL.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_p19(void)
{
    i18n_uchar dest[15];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(seen_source_1, LENGTHOF(seen_source_1),
            I18N_USHAPE_LETTERS_SHAPE | I18N_USHAPE_SEEN_TWOCELL_NEAR | I18N_USHAPE_TAIL_NEW_UNICODE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dest_len, LENGTHOF(seen_new_unicode));
    assert_eq(memcmp(dest, seen_new_unicode, dest_len*U_SIZEOF_UCHAR), 0);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_n
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with invalid @a source and checks whether
 *              the function returns an error code.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_n(void)
{
    i18n_uchar dest[15];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(NULL, LENGTHOF(en_digits),
            I18N_USHAPE_LETTERS_SHAPE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_n2
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with invalid @a source_len and checks whether
 *              the function returns an error code.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_n2(void)
{
    i18n_uchar dest[15];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(en_digits, -2,
            I18N_USHAPE_LETTERS_SHAPE,
            LENGTHOF(dest),
            dest, &dest_len);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_n3
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with invalid @a dest and checks whether
 *              the function returns an error code.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_n3(void)
{
    i18n_uchar dest[15];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(en_digits, LENGTHOF(en_digits),
            I18N_USHAPE_LETTERS_SHAPE,
            LENGTHOF(dest),
            NULL, &dest_len);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_n4
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with invalid @a dest_size and checks whether
 *              the function returns an error code.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_n4(void)
{
    i18n_uchar dest[15];
    int32_t dest_len;

    ret = i18n_ushape_shape_arabic(en_digits, LENGTHOF(en_digits),
            I18N_USHAPE_LETTERS_SHAPE,
            -5, dest, &dest_len);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ushape_shape_arabic_n5
 * @since_tizen 3.0
 * @description Calls i18n_ushape_shape_arabic with invalid @a dest and @a dest_len
 * 	            and checks whether the function returns an error code.
 */
int utc_capi_base_utils_i18n_ushape_shape_arabic_n5(void)
{
    i18n_uchar dest[15];

    ret = i18n_ushape_shape_arabic(en_digits, LENGTHOF(en_digits),
            I18N_USHAPE_LETTERS_SHAPE,
            LENGTHOF(dest),
            NULL, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
