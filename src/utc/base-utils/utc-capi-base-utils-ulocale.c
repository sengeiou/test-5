#include "assert.h"
#include <string.h>
#include <utils_i18n.h>

//& set: capi-base-utils-ulocale

#define I18N_LANG_CAPACITY      12
#define SKELETON_LEN            6
#define BEST_PATTERN_CAPACITY   12
#define I18N_RESULT_LEN         100

static i18n_error_code_e ret = I18N_ERROR_NONE;
static const char *locale_id = I18N_ULOCALE_US;

/**
 * @function        utc_capi_base_utils_ulocale_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_ulocale_startup(void)
{
}

/**
 * @function        utc_capi_base_utils_ulocale_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_ulocale_cleanup(void)
{
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_script_p
 * @since_tizen     2.3
 * @description     Gets the script code for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_script_p(void)
{
    char script[12] = { 0, };
    int32_t script_capacity = sizeof(script) / sizeof(script[0]);

    i18n_ulocale_get_script(locale_id, script, script_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_script_n
 * @since_tizen     2.3.1
 * @description     Gets the script code for the specified locale,
 *                  passing invalid string output, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_script_n(void)
{
    char script[12] = { 0, };
    int32_t script_capacity = sizeof(script) / sizeof(script[0]);

    i18n_ulocale_get_script(locale_id, NULL, script_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_script_n2
 * @since_tizen     2.3.1
 * @description     Gets the script code for the specified locale,
 *                  passing invalid string capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_script_n2(void)
{
    char script[12] = { 0, };

    i18n_ulocale_get_script(locale_id, script, -2);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_variant_p
 * @since_tizen     2.3.1
 * @description     Gets the variant code for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_variant_p(void)
{
    char variant[12] = { 0, };
    int32_t variant_capacity = sizeof(variant) / sizeof(variant[0]);

    i18n_ulocale_get_variant(locale_id, variant, variant_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_variant_n
 * @since_tizen     2.3.1
 * @description     Gets the variant code for the specified locale,
 *                  passing invalid output parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_variant_n(void)
{
    char variant[12] = { 0, };
    int32_t variant_capacity = sizeof(variant) / sizeof(variant[0]);

    i18n_ulocale_get_variant(locale_id, NULL, variant_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_variant_n2
 * @since_tizen     2.3.1
 * @description     Gets the variant code for the specified locale,
 *                  passing invalid capacity parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_variant_n2(void)
{
    char variant[12] = { 0, };

    i18n_ulocale_get_variant(locale_id, variant, -2);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_name_p
 * @since_tizen     2.3.1
 * @description     Gets the full name for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_name_p(void)
{
    char name[24] = { 0, };
    int32_t name_capacity = sizeof(name) / sizeof(name[0]);

    i18n_ulocale_get_name(locale_id, name, name_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_name_n
 * @since_tizen     2.3.1
 * @description     Gets the full name for the specified locale,
 *                  passing too short buffer, so buffer overflow is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_name_n(void)
{
    char name[4] = { 0, };  // buffer overflow
    int32_t name_capacity = sizeof(name) / sizeof(name[0]);

    i18n_ulocale_get_name(locale_id, name, name_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_canonicalize_p
 * @since_tizen     2.3.1
 * @description     Gets the full name for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_canonicalize_p(void)
{
    char name[12] = { 0, };
    int32_t name_capacity = sizeof(name) / sizeof(name[0]);

    i18n_ulocale_canonicalize(locale_id, name, name_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_canonicalize_n
 * @since_tizen     2.3.1
 * @description     Gets the full name for the specified locale,
 *                  passing too short buffer, so buffer overflow is expected.
 */
int utc_capi_base_utils_i18n_ulocale_canonicalize_n(void)
{
    char name[4] = { 0, };  // buffer overflow
    int32_t name_capacity = sizeof(name) / sizeof(name[0]);

    i18n_ulocale_canonicalize(locale_id, name, name_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_iso3_language_p
 * @since_tizen     2.3.1
 * @description     Gets the ISO language code for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_iso3_language_p(void)
{
    const char *iso_language = i18n_ulocale_get_iso3_language(locale_id);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(iso_language, "eng"), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_iso3_country_p
 * @since_tizen     2.3.1
 * @description     Gets the ISO country code for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_iso3_country_p(void)
{
    const char *iso_country = i18n_ulocale_get_iso3_country(locale_id);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(iso_country, "USA"), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_lcid_p
 * @since_tizen     2.3.1
 * @description     Gets the Win32 LCID value for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_lcid_p(void)
{
    i18n_ulocale_get_lcid(locale_id);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_display_language_p
 * @since_tizen     2.3.1
 * @description     Gets the language name suitable for display for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_display_language_p(void)
{
    const char *display_locale = I18N_ULOCALE_US;
    i18n_uchar language[12] = { 0, };
    int32_t language_capacity = sizeof(language) / sizeof(language[0]);

    i18n_ulocale_get_display_language(locale_id, display_locale, language, language_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_display_language_n
 * @since_tizen     2.3.1
 * @description     Gets the language name suitable for display for the specified locale,
 *                  passing invalid language capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_display_language_n(void)
{
    const char *display_locale = I18N_ULOCALE_US;
    i18n_uchar language[12] = { 0, };
    int32_t language_capacity = -1;  // invalid parameter

    i18n_ulocale_get_display_language(locale_id, display_locale, language, language_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_display_script_p
 * @since_tizen     2.3.1
 * @description     Gets the script name suitable for display for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_display_script_p(void)
{
    const char *display_locale = I18N_ULOCALE_US;
    i18n_uchar script[24] = { 0, };
    int32_t script_capacity = sizeof(script) / sizeof(script[0]);

    i18n_ulocale_get_display_script(locale_id, display_locale, script, script_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_display_script_n
 * @since_tizen     2.3.1
 * @description     Gets the script name suitable for display for the specified locale,
 *                  passing invalid language capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_display_script_n(void)
{
    const char *display_locale = I18N_ULOCALE_US;
    i18n_uchar script[12] = { 0, };
    int32_t script_capacity = -1;  // invalid parameter

    i18n_ulocale_get_display_script(locale_id, display_locale, script, script_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_display_country_p
 * @since_tizen     2.3.1
 * @description     Gets the country name suitable for display for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_display_country_p(void)
{
    const char *display_locale = I18N_ULOCALE_US;
    i18n_uchar country[64] = { 0, };
    int32_t country_capacity = sizeof(country) / sizeof(country[0]);

    i18n_ulocale_get_display_country(locale_id, display_locale, country, country_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_display_country_n
 * @since_tizen     2.3.1
 * @description     Gets the country name suitable for display for the specified locale,
 *                  passing invalid country capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_display_country_n(void)
{
    const char *display_locale = I18N_ULOCALE_US;
    i18n_uchar country[12] = { 0, };
    int32_t country_capacity = -1;  // invalid parameter

    i18n_ulocale_get_display_country(locale_id, display_locale, country, country_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_display_variant_p
 * @since_tizen     2.3.1
 * @description     Gets the variant name suitable for display for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_display_variant_p(void)
{
    const char *display_locale = I18N_ULOCALE_US;
    i18n_uchar variant[12] = { 0, };
    int32_t variant_capacity = sizeof(variant) / sizeof(variant[0]);

    i18n_ulocale_get_display_variant(locale_id, display_locale, variant, variant_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_display_variant_n
 * @since_tizen     2.3.1
 * @description     Gets the variant name suitable for display for the specified locale,
 *                  passing invalid variant capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_display_variant_n(void)
{
    const char *display_locale = I18N_ULOCALE_US;
    i18n_uchar variant[12] = { 0, };
    int32_t variant_capacity = -1;  // invalid parameter

    i18n_ulocale_get_display_variant(locale_id, display_locale, variant, variant_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_display_keyword_p
 * @since_tizen     2.3.1
 * @description     Gets the keyword name suitable for display for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_display_keyword_p(void)
{
    const char *keyword = "currency";
    const char *display_locale = I18N_ULOCALE_US;
    i18n_uchar dest[12] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);

    i18n_ulocale_get_display_keyword(keyword, display_locale, dest, dest_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_display_keyword_n
 * @since_tizen     2.3.1
 * @description     Gets the keyword name suitable for display for the specified locale,
 *                  passing invalid destination capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_display_keyword_n(void)
{
    const char *keyword = "currency";
    const char *display_locale = I18N_ULOCALE_US;
    i18n_uchar dest[12] = { 0, };
    int32_t dest_capacity = -1;  // invalid parameter

    i18n_ulocale_get_display_keyword(keyword, display_locale, dest, dest_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_display_keyword_value_p
 * @since_tizen     2.3.1
 * @description     Gets the value of the keyword suitable for display for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_display_keyword_value_p(void)
{
    const char *locale_id = "en_US@currency=USD";
    const char *keyword = "currency";
    const char *display_locale = I18N_ULOCALE_US;
    i18n_uchar dest[12] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);

    i18n_ulocale_get_display_keyword_value(locale_id, keyword, display_locale, dest, dest_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_display_keyword_value_n
 * @since_tizen     2.3.1
 * @description     Gets the value of the keyword suitable for display for the specified locale,
 *                  passing invalid destination capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_display_keyword_value_n(void)
{
    const char *locale_id = "en_US@currency=USD";
    const char *keyword = "currency";
    const char *display_locale = I18N_ULOCALE_US;
    i18n_uchar dest[12] = { 0, };
    int32_t dest_capacity = -1;  // invalid parameter

    i18n_ulocale_get_display_keyword_value(locale_id, keyword, display_locale, dest, dest_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_iso_languages_p
 * @since_tizen     2.3.1
 * @description     Gets a list of all available 2-letter language codes defined in ISO 639,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_iso_languages_p(void)
{
    const char * const *languages = i18n_ulocale_get_iso_languages();

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(languages, NULL);

    while(*languages != NULL) {
        const char *language_code = *languages;

        int code_len = strlen(language_code);

        assert_leq(code_len, 3);

        int i;
        for(i = 0; i < code_len; i++) {
            assert_geq(language_code[i], 'a');
            assert_leq(language_code[i], 'z');
        }

        languages++;
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_iso_countries_p
 * @since_tizen     2.3.1
 * @description     Gets a list of all available 2-letter country codes defined in ISO 639,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_iso_countries_p(void)
{
    const char * const *countries = i18n_ulocale_get_iso_countries();

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(countries, NULL);

    while(*countries != NULL) {
        const char *country_code = *countries;
        assert_eq(strlen(country_code), 2);
        assert_geq(country_code[0], 'A');
        assert_leq(country_code[1], 'Z');
        countries++;
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_parent_p
 * @since_tizen     2.3.1
 * @description     Truncates the locale ID string to get the parent locale ID,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_parent_p(void)
{
    char parent[12] = { 0, };
    int32_t parent_capacity = sizeof(parent) / sizeof(parent[0]);

    i18n_ulocale_get_parent(locale_id, parent, parent_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_parent_n
 * @since_tizen     2.3.1
 * @description     Truncates the locale ID string to get the parent locale ID,
 *                  passing invalid output buffer, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_parent_n(void)
{
    char parent[12] = { 0, };
    int32_t parent_capacity = sizeof(parent) / sizeof(parent[0]);

    i18n_ulocale_get_parent(locale_id, NULL, parent_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_parent_n2
 * @since_tizen     2.3.1
 * @description     Truncates the locale ID string to get the parent locale ID,
 *                  passing invalid buffer length parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_parent_n2(void)
{
    char parent[12] = { 0, };

    i18n_ulocale_get_parent(locale_id, parent, -2);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_parent_n3
 * @since_tizen     2.3.1
 * @description     Truncates the locale ID string to get the parent locale ID,
 *                  passing too low capacity parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_parent_n3(void)
{
    char parent[12] = { 0, };
    int32_t parent_capacity = 1;  // buffer overflow error - the capacity is lower than the number of characters between the beginning of the locale_id string and the last underscore found in that string.

    i18n_ulocale_get_parent(locale_id, parent, parent_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_base_name_p
 * @since_tizen     2.3.1
 * @description     Gets the full name for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_base_name_p(void)
{
    const char *locale_id = "en_US@currency=USD;president=WHO";
    char name[24] = { 0, };
    int32_t name_capacity = sizeof(name) / sizeof(name[0]);

    i18n_ulocale_get_base_name(locale_id, name, name_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_base_name_n
 * @since_tizen     2.3.1
 * @description     Gets the full name for the specified locale,
 *                  passing too short output buffer, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_base_name_n(void)
{
    const char *locale_id = "en_US@currency=USD;president=WHO";
    char name[4] = { 0, };  // buffer overflow
    int32_t name_capacity = sizeof(name) / sizeof(name[0]);

    i18n_ulocale_get_base_name(locale_id, name, name_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_keywords_create_p
 * @since_tizen     2.3.1
 * @description     Gets an enumeration of keywords for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_keywords_create_p(void)
{
    const char *locale_id = "en_US@currency=USD;president=WHO";

    i18n_uenumeration_h keywords = NULL;
    ret = i18n_ulocale_keywords_create(locale_id, &keywords);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(keywords, NULL);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_keywords_create_n
 * @since_tizen     2.3.1
 * @description     Gets an enumeration of keywords for the specified locale,
 *                  passing invalid parameters, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_keywords_create_n(void)
{
    ret = i18n_ulocale_keywords_create(NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_keyword_value_p
 * @since_tizen     2.3.1
 * @description     Gets the value for a keyword,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_keyword_value_p(void)
{
    const char *locale_id = "en_US@currency=USD";
    const char *keyword_name = "currency";
    char buffer[12] = { 0, };
    int32_t buffer_capacity = sizeof(buffer) / sizeof(buffer[0]);

    i18n_ulocale_get_keyword_value(locale_id, keyword_name, buffer, buffer_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_keyword_value_n
 * @since_tizen     2.3.1
 * @description     Gets the value for a keyword,
 *                  passing invalid locale id, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_keyword_value_n(void)
{
    const char *keyword_name = "currency";
    char buffer[12] = { 0, };
    int32_t buffer_capacity = sizeof(buffer) / sizeof(buffer[0]);

    i18n_ulocale_get_keyword_value(NULL, keyword_name, buffer, buffer_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_keyword_value_n2
 * @since_tizen     2.3.1
 * @description     Gets the value for a keyword,
 *                  passing invalid keyword name, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_keyword_value_n2(void)
{
    const char *locale_id = "en_US@currency=USD";
    char buffer[12] = { 0, };
    int32_t buffer_capacity = sizeof(buffer) / sizeof(buffer[0]);

    i18n_ulocale_get_keyword_value(locale_id, NULL, buffer, buffer_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_keyword_value_n3
 * @since_tizen     2.3.1
 * @description     Gets the value for a keyword,
 *                  passing invalid output buffer, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_keyword_value_n3(void)
{
    const char *locale_id = "en_US@currency=USD";
    const char *keyword_name = "currency";
    char buffer[12] = { 0, };
    int32_t buffer_capacity = sizeof(buffer) / sizeof(buffer[0]);

    i18n_ulocale_get_keyword_value(locale_id, keyword_name, NULL, buffer_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_keyword_value_n4
 * @since_tizen     2.3.1
 * @description     Gets the value for a keyword,
 *                  passing invalid buffer capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_keyword_value_n4(void)
{
    const char *locale_id = "en_US@currency=USD";
    const char *keyword_name = "currency";
    char buffer[12] = { 0, };

    i18n_ulocale_get_keyword_value(locale_id, keyword_name, buffer, -2);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_set_keyword_value_p
 * @since_tizen     2.3.1
 * @description     Sets the value of the specified keyword,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_set_keyword_value_p(void)
{
    const char *keyword_name = "currency";
    const char *keyword_value = "USD";
    char buffer[24] = { 0, };
    int32_t buffer_capacity = sizeof(buffer) / sizeof(buffer[0]);

    i18n_ulocale_set_keyword_value(keyword_name, keyword_value, buffer, buffer_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_set_keyword_value_n
 * @since_tizen     2.3.1
 * @description     Sets the value of the specified keyword,
 *                  passing invalid keyword name, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_set_keyword_value_n(void)
{
    const char *keyword_value = "USD";
    char buffer[24] = { 0, };
    int32_t buffer_capacity = sizeof(buffer) / sizeof(buffer[0]);

    i18n_ulocale_set_keyword_value(NULL, keyword_value, buffer, buffer_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_set_keyword_value_n2
 * @since_tizen     2.3.1
 * @description     Sets the value of the specified keyword,
 *                  passing invalid output buffer, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_set_keyword_value_n2(void)
{
    const char *keyword_name = "currency";
    const char *keyword_value = "USD";
    char buffer[24] = { 0, };
    int32_t buffer_capacity = sizeof(buffer) / sizeof(buffer[0]);

    i18n_ulocale_set_keyword_value(keyword_name, keyword_value, NULL, buffer_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_set_keyword_value_n3
 * @since_tizen     2.3.1
 * @description     Sets the value of the specified keyword,
 *                  passing invalid output capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_set_keyword_value_n3(void)
{
    const char *keyword_name = "currency";
    const char *keyword_value = "USD";
    char buffer[24] = { 0, };

    i18n_ulocale_set_keyword_value(keyword_name, keyword_value, buffer, -2);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_character_orientation_p
 * @since_tizen     2.3.1
 * @description     Gets the layout character orientation for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_character_orientation_p(void)
{
    const char *locale_id = "en_US@currency=USD";

    i18n_ulocale_layout_type_e layout_type;
    ret = i18n_ulocale_get_character_orientation(locale_id, &layout_type);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_character_orientation_n
 * @since_tizen     2.3.1
 * @description     Gets the layout character orientation for the specified locale,
 *                  passing invalid parameters, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_character_orientation_n(void)
{
    ret = i18n_ulocale_get_character_orientation(NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_line_orientation_p
 * @since_tizen     2.3.1
 * @description     Gets the layout line orientation for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_line_orientation_p(void)
{
    const char *locale_id = "en_US@currency=USD";

    i18n_ulocale_layout_type_e layout_type;

    ret = i18n_ulocale_get_line_orientation(locale_id, &layout_type);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_line_orientation_n
 * @since_tizen     2.3.1
 * @description     Gets the layout line orientation for the specified locale,
 *                  passing invalid parameters, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_line_orientation_n(void)
{
    ret = i18n_ulocale_get_line_orientation(NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_locale_for_lcid_p
 * @since_tizen     2.3.1
 * @description     Gets the I18N locale ID for the specified Win32 LCID value,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_locale_for_lcid_p(void)
{
    char locale[12] = { 0, };
    int32_t locale_capacity = sizeof(locale) / sizeof(locale[0]);

    uint32_t lcid = i18n_ulocale_get_lcid(locale_id);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ulocale_get_locale_for_lcid(lcid, locale, locale_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_locale_for_lcid_n
 * @since_tizen     2.3.1
 * @description     Gets the I18N locale ID for the specified Win32 LCID value,
 *                  passing invalid locale capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_locale_for_lcid_n(void)
{
    char locale[12] = { 0, };
    int32_t locale_capacity = -1;  // invalid parameter

    uint32_t lcid = i18n_ulocale_get_lcid(locale_id);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_ulocale_get_locale_for_lcid(lcid, locale, locale_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_add_likely_subtags_p
 * @since_tizen     2.3.1
 * @description     Adds the likely subtags,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_add_likely_subtags_p(void)
{
    char maximized_locale_id[24] = { 0, };
    int32_t maximized_locale_id_capacity = sizeof(maximized_locale_id) / sizeof(maximized_locale_id[0]);

    i18n_ulocale_add_likely_subtags(locale_id, maximized_locale_id, maximized_locale_id_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_add_likely_subtags_n
 * @since_tizen     2.3.1
 * @description     Adds the likely subtags,
 *                  passing invalid buffer capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_add_likely_subtags_n(void)
{
    char maximized_locale_id[24] = { 0, };
    int32_t maximized_locale_id_capacity = -1;  // invalid parameter

    i18n_ulocale_add_likely_subtags(locale_id, maximized_locale_id, maximized_locale_id_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_minimize_subtags_p
 * @since_tizen     2.3.1
 * @description     Minimizes the subtags for a provided locale ID, per the algorithm describe,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_minimize_subtags_p(void)
{
    char minimized_locale_id[24] = { 0, };
    int32_t minimized_locale_id_capacity = sizeof(minimized_locale_id) / sizeof(minimized_locale_id[0]);

    i18n_ulocale_minimize_subtags(locale_id, minimized_locale_id, minimized_locale_id_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_minimize_subtags_n
 * @since_tizen     2.3.1
 * @description     Minimizes the subtags for a provided locale ID, per the algorithm describe,
 *                  passing invalid buffer capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_minimize_subtags_n(void)
{
    char minimized_locale_id[24] = { 0, };
    int32_t minimized_locale_id_capacity = -1;  // invalid parameter

    i18n_ulocale_minimize_subtags(locale_id, minimized_locale_id, minimized_locale_id_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_for_language_tag_p
 * @since_tizen     2.3.1
 * @description     Returns a locale ID for the specified BCP47 language tag string,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_for_language_tag_p(void)
{
    const char *langtag = "en";
    char locale_id[24] = { 0, };
    int32_t locale_id_capacity = sizeof(locale_id) / sizeof(locale_id[0]);
    int32_t parsed_length;

    i18n_ulocale_for_language_tag(langtag, locale_id, locale_id_capacity, &parsed_length);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_for_language_tag_n
 * @since_tizen     2.3.1
 * @description     Returns a locale ID for the specified BCP47 language tag string,
 *                  passing invalid language tag, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_for_language_tag_n(void)
{
    char locale_id[24] = { 0, };
    int32_t locale_id_capacity = sizeof(locale_id) / sizeof(locale_id[0]);
    int32_t parsed_length;

    i18n_ulocale_for_language_tag(NULL, locale_id, locale_id_capacity, &parsed_length);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_for_language_tag_n2
 * @since_tizen     2.3.1
 * @description     Returns a locale ID for the specified BCP47 language tag string,
 *                  passing invalid locale id, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_for_language_tag_n2(void)
{
    const char *langtag = "en";
    char locale_id[24] = { 0, };
    int32_t locale_id_capacity = sizeof(locale_id) / sizeof(locale_id[0]);
    int32_t parsed_length;

    i18n_ulocale_for_language_tag(langtag, NULL, locale_id_capacity, &parsed_length);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_for_language_tag_n3
 * @since_tizen     2.3.1
 * @description     Returns a locale ID for the specified BCP47 language tag string,
 *                  passing invalid buffer capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_for_language_tag_n3(void)
{
    const char *langtag = "en";
    char locale_id[24] = { 0, };
    int32_t parsed_length;

    i18n_ulocale_for_language_tag(langtag, locale_id, -2, &parsed_length);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_to_language_tag_p
 * @since_tizen     2.3.1
 * @description     Returns a well-formed language tag for this locale ID,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_to_language_tag_p(void)
{
    char langtag[24] = { 0, };
    int32_t langtag_capacity = sizeof(langtag) / sizeof(langtag[0]);
    i18n_ubool strict = true;

    i18n_ulocale_to_language_tag(locale_id, langtag, langtag_capacity, strict);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_to_language_tag_n
 * @since_tizen     2.3.1
 * @description     Returns a well-formed language tag for this locale ID,
 *                  passing invalid locale id, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_to_language_tag_n(void)
{
    char langtag[24] = { 0, };
    int32_t langtag_capacity = sizeof(langtag) / sizeof(langtag[0]);
    i18n_ubool strict = true;

    i18n_ulocale_to_language_tag(NULL, langtag, langtag_capacity, strict);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_to_language_tag_n2
 * @since_tizen     2.3.1
 * @description     Returns a well-formed language tag for this locale ID,
 *                  passing invalid language tag, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_to_language_tag_n2(void)
{
    char langtag[24] = { 0, };
    int32_t langtag_capacity = sizeof(langtag) / sizeof(langtag[0]);
    i18n_ubool strict = true;

    i18n_ulocale_to_language_tag(locale_id, NULL, langtag_capacity, strict);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_to_language_tag_n3
 * @since_tizen     2.3.1
 * @description     Returns a well-formed language tag for this locale ID,
 *                  passing invalid buffer capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_to_language_tag_n3(void)
{
    char langtag[24] = { 0, };
    i18n_ubool strict = true;

    i18n_ulocale_to_language_tag(locale_id, langtag, -2, strict);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_default_p
 * @since_tizen     2.3
 * @description     Gets I18N's default locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_default_p(void)
{
    const char *loc = NULL;

    ret = i18n_ulocale_get_default(&loc);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_default_n
 * @since_tizen     2.3
 * @description     Gets I18N's default locale,
 *                  passing invalid locale output, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_default_n(void)
{
    ret = i18n_ulocale_get_default(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_set_default_p
 * @since_tizen     2.3
 * @description     Sets default locale, checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_set_default_p(void)
{
    char *i18n_id = NULL;

    ret = i18n_ulocale_set_default(i18n_id);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_language_p
 * @since_tizen     2.3
 * @description     Gets the language code for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_language_p(void)
{
    const char *loc = NULL;
    char language[I18N_LANG_CAPACITY] = { 0, };
    int buf_size_language = 0;

    ret = i18n_ulocale_get_default(&loc);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ulocale_get_language(loc, language, I18N_LANG_CAPACITY, &buf_size_language);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_language_n
 * @since_tizen     2.3
 * @description     Gets the language code for the specified locale,
 *                  passing invalid language, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_language_n(void)
{
    int32_t buf_size_language;

    ret = i18n_ulocale_get_language(NULL, NULL, I18N_LANG_CAPACITY, &buf_size_language);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_language_n2
 * @since_tizen     2.3
 * @description     Gets the language code for the specified locale,
 *                  passing invalid language capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_language_n2(void)
{
    char language[I18N_LANG_CAPACITY];
    int32_t buf_size_language;

    ret = i18n_ulocale_get_language(NULL, language, 0, &buf_size_language);
    assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_language_n3
 * @since_tizen     2.3
 * @description     Gets the language code for the specified locale,
 *                  passing invalid buffer size output, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_language_n3(void)
{
    char language[I18N_LANG_CAPACITY];

    ret = i18n_ulocale_get_language(NULL, language, I18N_LANG_CAPACITY, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_country_p
 * @since_tizen     2.3
 * @description     Gets the country code for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_country_p(void)
{
    int error = 0;
    char country[64] = { 0, };

    i18n_ulocale_get_country("en_US", country, 64, &error);
    assert_eq(error, I18N_ERROR_NONE);
    assert_eq(strcmp(country, "US"),0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_country_n
 * @since_tizen     2.3
 * @description     Gets the country code for the specified locale,
 *                  passing invalid country parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_country_n(void)
{
    int error = 0;

    i18n_ulocale_get_country("en_US", NULL, 64, &error);
    assert_eq(error, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_country_n2
 * @since_tizen     2.3
 * @description     Gets the country code for the specified locale,
 *                  passing invalid buffer capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_country_n2(void)
{
    int error = 0;
    char country[64] = { 0, };

    i18n_ulocale_get_country("en_US", country, -1, &error);
    assert_eq(error, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_display_name_p
 * @since_tizen     2.3
 * @description     Gets the full name suitable for display for the specified locale,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_display_name_p(void)
{
    char *i18n_id = NULL; // Use default locale.
    char *in_i18n_id = NULL; // Use default locale.
    i18n_uchar result_w[I18N_RESULT_LEN] = { 0, };
    int max_result_size = I18N_RESULT_LEN;
    int buf_size_display_name;

    ret = i18n_ulocale_get_display_name(i18n_id, in_i18n_id, result_w, max_result_size, &buf_size_display_name);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_display_name_n
 * @since_tizen     2.3
 * @description     Gets the full name suitable for display for the specified locale,
 *                  passing invalid buffer capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_display_name_n(void)
{
    char *i18n_id = NULL; // Use default locale.
    char *in_i18n_id = NULL; // Use default locale.
    int max_result_size = I18N_RESULT_LEN;
    int buf_size_display_name;

    ret = i18n_ulocale_get_display_name(i18n_id, in_i18n_id, NULL, max_result_size, &buf_size_display_name);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_display_name_n2
 * @since_tizen     2.3
 * @description     Gets the full name suitable for display for the specified locale,
 *                  passing invalid maximum size, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_display_name_n2(void)
{
    char *i18n_id = NULL; // Use default locale.
    char *in_i18n_id = NULL; // Use default locale.
    i18n_uchar result_w[I18N_RESULT_LEN] = { 0, };
    int buf_size_display_name;

    ret = i18n_ulocale_get_display_name(i18n_id, in_i18n_id, result_w, -1, &buf_size_display_name);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_display_name_n3
 * @since_tizen     2.3
 * @description     Gets the full name suitable for display for the specified locale,
 *                  passing invalid output buffer, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_display_name_n3(void)
{
    char *i18n_id = NULL; // Use default locale.
    char *in_i18n_id = NULL; // Use default locale.
    i18n_uchar result_w[I18N_RESULT_LEN] = { 0, };
    int max_result_size = I18N_RESULT_LEN;

    ret = i18n_ulocale_get_display_name(i18n_id, in_i18n_id, result_w, max_result_size, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_available_p
 * @since_tizen     2.3
 * @description     Gets the specified locale from a list of all available locales,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_get_available_p(void)
{
    const char *result = i18n_ulocale_get_available(0);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(result, NULL);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_get_available_n
 * @since_tizen     2.3
 * @description     Gets the specified locale from a list of all available locales,
 *                  passing invalid index, so error is expected.
 */
int utc_capi_base_utils_i18n_ulocale_get_available_n(void)
{
    i18n_ulocale_get_available(-1);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_count_available_p
 * @since_tizen     2.3
 * @description     Gets the size of the all available locale list,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_ulocale_count_available_p(void)
{
    int32_t result = -1;
    result = i18n_ulocale_count_available();
    assert_gt(result, -1);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_is_bogus_p
 * @since_tizen     4.0
 * @description     Checks if given locale is bogus and error code.
 */
int utc_capi_base_utils_i18n_ulocale_is_bogus_p(void)
{
    int result = -1;
    i18n_ubool is_bogus = true;

    result = i18n_ulocale_is_bogus(locale_id, &is_bogus);
    assert_eq(result, I18N_ERROR_NONE);
    assert_eq(is_bogus, false);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_is_bogus_p2
 * @since_tizen     4.0
 * @description     Checks if given locale is bogus and error code.
 */
int utc_capi_base_utils_i18n_ulocale_is_bogus_p2(void)
{
    const char *locale = "aaaaaaaaaaaa";
    int result = -1;
    i18n_ubool is_bogus = false;

    result = i18n_ulocale_is_bogus(locale, &is_bogus);
    assert_eq(result, I18N_ERROR_NONE);
    assert_eq(is_bogus, true);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ulocale_is_bogus_n
 * @since_tizen     4.0
 * @description     Checks if given locale is bogus and error code.
 *                  Passing invalid argument, so error is expected
 */
int utc_capi_base_utils_i18n_ulocale_is_bogus_n(void)
{
    int result = -1;

    result = i18n_ulocale_is_bogus(locale_id,  NULL);
    assert_eq(result, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
