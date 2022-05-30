#include "assert.h"
#include <utils_i18n.h>

i18n_loc_disp_names_h loc_disp = NULL;
const char *locale = "en_US";
const char *language = "en";
const char *script = "Hant";
const char *region = "US";
const char *variant = "PRE_EURO";
const char *key = "calendar";
const char *value = "gregorian";
char *name = NULL;
int ret = I18N_ERROR_NONE;

/**
* @function        utc_capi_base_utils_loc_disp_names_startup
* @description     Called before each test
* @parameter       NA
* @return          NA
*/
void utc_capi_base_utils_loc_disp_names_startup(void)
{
	ret = i18n_loc_disp_names_create(locale, &loc_disp);
}

/**
* @function        utc_capi_base_utils_loc_disp_names_cleanup
* @description     Called after each test
* @parameter       NA
* @return          NA
*/
void utc_capi_base_utils_loc_disp_names_cleanup(void)
{
    if (loc_disp != NULL) {
        i18n_loc_disp_names_destroy(loc_disp);
        loc_disp = NULL;
    }
    if (name != NULL) {
        free(name);
        name = NULL;
    }
}

/**
 * @testcase utc_capi_base_utils_i18n_loc_disp_names_create_p
 * @since_tizen 5.0
 * @description Calls i18n_loc_disp_names_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_loc_disp_names_create_p(void)
{
    utc_capi_base_utils_loc_disp_names_cleanup();
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(loc_disp, NULL);

    ret = i18n_loc_disp_names_create(locale, &loc_disp);

	assert_eq(ret, I18N_ERROR_NONE);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_create_n
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_create passing invalid loc_disp_names
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_create_n(void)
{
    ret = i18n_loc_disp_names_create(locale, NULL);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_loc_disp_names_create_from_dialect_p
 * @since_tizen 5.0
 * @description Calls i18n_loc_disp_names_create_from_dialect and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_loc_disp_names_create_from_dialect_p(void)
{
    utc_capi_base_utils_loc_disp_names_cleanup();
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(loc_disp, NULL);

    ret = i18n_loc_disp_names_create_from_dialect(locale, I18N_ULDN_STANDARD_NAMES, &loc_disp);

	assert_eq(ret, I18N_ERROR_NONE);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_create_from_dialect_n
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_create_from_dialect passing invalid loc_disp
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_create_from_dialect_n(void)
{
    ret = i18n_loc_disp_names_create_from_dialect(locale, I18N_ULDN_STANDARD_NAMES, NULL);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_loc_disp_names_create_from_context_p
 * @since_tizen 5.0
 * @description Calls i18n_loc_disp_names_create_from_context and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_loc_disp_names_create_from_context_p(void)
{
    utc_capi_base_utils_loc_disp_names_cleanup();
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(loc_disp, NULL);

    i18n_udisplay_context_e contexts[] = {I18N_UDISPLAY_CONTEXT_STANDARD_NAMES, I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_UI_LIST_OR_MENU };

    ret = i18n_loc_disp_names_create_from_context(locale, contexts, 2, &loc_disp);

	assert_eq(ret, I18N_ERROR_NONE);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_create_from_context_n
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_create_from_context passing invalid loc_disp
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_create_from_context_n(void)
{
    ret = i18n_loc_disp_names_create_from_context(locale, NULL, 0, NULL);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_loc_disp_names_get_locale_p
 * @since_tizen 5.0
 * @description Calls i18n_loc_disp_names_get_locale and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_loc_disp_names_get_locale_p(void)
{
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(loc_disp, NULL);

    char *output = NULL;

    ret = i18n_loc_disp_names_get_locale(loc_disp, &output);

	assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp("en_US", output), 0);

	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_locale_n
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_locale passing invalid loc_disp
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_locale_n(void)
{
    char *output = NULL;
    ret = i18n_loc_disp_names_get_locale(NULL, &output);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_locale_n2
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_locale passing invalid locale
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_locale_n2(void)
{
    ret = i18n_loc_disp_names_get_locale(loc_disp, NULL);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_loc_disp_names_get_dialect_handling_p
 * @since_tizen 5.0
 * @description Calls i18n_loc_disp_names_get_dialect_handling and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_loc_disp_names_get_dialect_handling_p(void)
{
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(loc_disp, NULL);
    i18n_udialect_handling_e dialect = 0;

    ret = i18n_loc_disp_names_get_dialect_handling(loc_disp, &dialect);

	assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(dialect, I18N_ULDN_STANDARD_NAMES);

	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_dialect_handling_n
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_dialect_handling passing invalid loc_disp
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_dialect_handling_n(void)
{
    i18n_udialect_handling_e dialect = 0;

    ret = i18n_loc_disp_names_get_dialect_handling(NULL, &dialect);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_dialect_handling_n2
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_dialect_handling passing invalid dialect
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_dialect_handling_n2(void)
{
    ret = i18n_loc_disp_names_get_dialect_handling(loc_disp, NULL);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_loc_disp_names_get_context_p
 * @since_tizen 5.0
 * @description Calls i18n_loc_disp_names_get_context and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_loc_disp_names_get_context_p(void)
{
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(loc_disp, NULL);

    i18n_udisplay_context_type_e type = I18N_UDISPCTX_TYPE_DIALECT_HANDLING;
    i18n_udisplay_context_e context = 0;

    ret = i18n_loc_disp_names_get_context(loc_disp, type, &context);

	assert_eq(ret, I18N_ERROR_NONE);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_context_n
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_context passing invalid loc_disp
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_context_n(void)
{
    i18n_udisplay_context_type_e type = I18N_UDISPCTX_TYPE_DIALECT_HANDLING;
    i18n_udisplay_context_e context = 0;

    ret = i18n_loc_disp_names_get_context(NULL, type, &context);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_context_n2
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_context passing invalid context
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_context_n2(void)
{
    i18n_udisplay_context_type_e type = I18N_UDISPCTX_TYPE_DIALECT_HANDLING;

    ret = i18n_loc_disp_names_get_context(loc_disp, type, NULL);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_loc_disp_names_get_loc_disp_name_p
 * @since_tizen 5.0
 * @description Calls i18n_loc_disp_names_get_loc_disp_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_loc_disp_names_get_loc_disp_name_p(void)
{
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(loc_disp, NULL);
    const char *expected = "English (United States)";

    ret = i18n_loc_disp_names_get_loc_disp_name(loc_disp, locale, &name);

	assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(name, expected), 0);

	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_loc_disp_name_n
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_loc_disp_name passing invalid loc_disp
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_loc_disp_name_n(void)
{
    ret = i18n_loc_disp_names_get_loc_disp_name(NULL, locale, &name);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_loc_disp_name_n2
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_loc_disp_name passing invalid locale
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_loc_disp_name_n2(void)
{
    ret = i18n_loc_disp_names_get_loc_disp_name(loc_disp, NULL, &name);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_loc_disp_name_n3
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_loc_disp_name passing invalid name
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_loc_disp_name_n3(void)
{
    ret = i18n_loc_disp_names_get_loc_disp_name(loc_disp, locale, NULL);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_loc_disp_names_get_language_disp_name_p
 * @since_tizen 5.0
 * @description Calls i18n_loc_disp_names_get_language_disp_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_loc_disp_names_get_language_disp_name_p(void)
{
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(loc_disp, NULL);
    const char *expected = "English";

    ret = i18n_loc_disp_names_get_language_disp_name(loc_disp, language, &name);

	assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(name, expected), 0);

	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_language_disp_name_n
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_language_disp_name passing invalid loc_disp
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_language_disp_name_n(void)
{
    ret = i18n_loc_disp_names_get_language_disp_name(NULL, language, &name);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_language_disp_name_n2
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_language_disp_name passing invalid language
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_language_disp_name_n2(void)
{
    ret = i18n_loc_disp_names_get_language_disp_name(loc_disp, NULL, &name);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_language_disp_name_n3
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_language_disp_name passing invalid name
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_language_disp_name_n3(void)
{
    ret = i18n_loc_disp_names_get_language_disp_name(loc_disp, language, NULL);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_loc_disp_names_get_script_disp_name_p
 * @since_tizen 5.0
 * @description Calls i18n_loc_disp_names_get_script_disp_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_loc_disp_names_get_script_disp_name_p(void)
{
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(loc_disp, NULL);
    const char *expected = "Traditional";

    ret = i18n_loc_disp_names_get_script_disp_name(loc_disp, script, &name);

	assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(name, expected), 0);

	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_script_disp_name_n
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_script_disp_name passing invalid loc_disp
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_script_disp_name_n(void)
{
    ret = i18n_loc_disp_names_get_script_disp_name(NULL, script, &name);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_script_disp_name_n2
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_script_disp_name passing invalid script
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_script_disp_name_n2(void)
{
    ret = i18n_loc_disp_names_get_script_disp_name(loc_disp, NULL, &name);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_script_disp_name_n3
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_script_disp_name passing invalid name
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_script_disp_name_n3(void)
{
    ret = i18n_loc_disp_names_get_script_disp_name(loc_disp, script, NULL);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_loc_disp_names_get_script_disp_name_with_script_code_p
 * @since_tizen 5.0
 * @description Calls i18n_loc_disp_names_get_script_disp_name_with_script_code and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_loc_disp_names_get_script_disp_name_with_script_code_p(void)
{
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(loc_disp, NULL);
    i18n_uscript_code_e code = I18N_USCRIPT_BATAK;
    const char *expected = "Batak";

    ret = i18n_loc_disp_names_get_script_disp_name_with_script_code(loc_disp, code, &name);

	assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(name, expected), 0);

	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_script_disp_name_with_script_code_n
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_script_disp_name_with_script_code passing invalid loc_disp
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_script_disp_name_with_script_code_n(void)
{
    i18n_uscript_code_e code = I18N_USCRIPT_BATAK;
    ret = i18n_loc_disp_names_get_script_disp_name_with_script_code(NULL, code, &name);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_script_disp_name_with_script_code_n2
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_script_disp_name_with_script_code passing invalid name
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_script_disp_name_with_script_code_n2(void)
{
    i18n_uscript_code_e code = I18N_USCRIPT_BATAK;
    ret = i18n_loc_disp_names_get_script_disp_name_with_script_code(loc_disp, code, NULL);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_loc_disp_names_get_region_disp_name_p
 * @since_tizen 5.0
 * @description Calls i18n_loc_disp_names_get_region_disp_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_loc_disp_names_get_region_disp_name_p(void)
{
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(loc_disp, NULL);
    const char *expected = "United States";

    ret = i18n_loc_disp_names_get_region_disp_name(loc_disp, region, &name);

	assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(name, expected), 0);

	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_region_disp_name_n
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_region_disp_name passing invalid loc_disp
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_region_disp_name_n(void)
{
    ret = i18n_loc_disp_names_get_region_disp_name(NULL, region, &name);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_region_disp_name_n2
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_region_disp_name passing invalid region
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_region_disp_name_n2(void)
{
    ret = i18n_loc_disp_names_get_region_disp_name(loc_disp, NULL, &name);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_region_disp_name_n3
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_region_disp_name passing invalid name
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_region_disp_name_n3(void)
{
    ret = i18n_loc_disp_names_get_region_disp_name(loc_disp, region, NULL);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_loc_disp_names_get_variant_disp_name_p
 * @since_tizen 5.0
 * @description Calls i18n_loc_disp_names_get_variant_disp_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_loc_disp_names_get_variant_disp_name_p(void)
{
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(loc_disp, NULL);
    const char *expected = "PRE_EURO";

    ret = i18n_loc_disp_names_get_variant_disp_name(loc_disp, variant, &name);

	assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(name, expected), 0);

	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_variant_disp_name_n
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_variant_disp_name passing invalid loc_disp
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_variant_disp_name_n(void)
{
    ret = i18n_loc_disp_names_get_variant_disp_name(NULL, variant, &name);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_variant_disp_name_n2
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_variant_disp_name passing invalid variant
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_variant_disp_name_n2(void)
{
    ret = i18n_loc_disp_names_get_variant_disp_name(loc_disp, NULL, &name);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_variant_disp_name_n3
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_variant_disp_name passing invalid name
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_variant_disp_name_n3(void)
{
    ret = i18n_loc_disp_names_get_variant_disp_name(loc_disp, variant, NULL);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_loc_disp_names_get_key_disp_name_p
 * @since_tizen 5.0
 * @description Calls i18n_loc_disp_names_get_key_disp_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_loc_disp_names_get_key_disp_name_p(void)
{
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(loc_disp, NULL);
    const char *expected = "Calendar";

    ret = i18n_loc_disp_names_get_key_disp_name(loc_disp, key, &name);

	assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(name, expected), 0);

	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_key_disp_name_n
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_key_disp_name passing invalid loc_disp
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_key_disp_name_n(void)
{
    ret = i18n_loc_disp_names_get_key_disp_name(NULL, key, &name);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_key_disp_name_n2
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_key_disp_name passing invalid key
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_key_disp_name_n2(void)
{
    ret = i18n_loc_disp_names_get_key_disp_name(loc_disp, NULL, &name);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_key_disp_name_n3
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_key_disp_name passing invalid name
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_key_disp_name_n3(void)
{
    ret = i18n_loc_disp_names_get_key_disp_name(loc_disp, key, NULL);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_loc_disp_names_get_key_value_disp_name_p
 * @since_tizen 5.0
 * @description Calls i18n_loc_disp_names_get_key_value_disp_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_loc_disp_names_get_key_value_disp_name_p(void)
{
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(loc_disp, NULL);
    const char *expected = "Gregorian Calendar";

    ret = i18n_loc_disp_names_get_key_value_disp_name(loc_disp, key, value, &name);

	assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(name, expected), 0);

	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_key_value_disp_name_n
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_key_value_disp_name passing invalid loc_disp
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_key_value_disp_name_n(void)
{
    ret = i18n_loc_disp_names_get_key_value_disp_name(NULL, key, value, &name);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_key_value_disp_name_n2
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_key_value_disp_name passing invalid key
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_key_value_disp_name_n2(void)
{
    ret = i18n_loc_disp_names_get_key_value_disp_name(loc_disp, NULL, value, &name);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_key_value_disp_name_n3
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_key_value_disp_name passing invalid value
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_key_value_disp_name_n3(void)
{
    ret = i18n_loc_disp_names_get_key_value_disp_name(loc_disp, key, NULL, &name);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
* @testcase utc_capi_base_utils_i18n_loc_disp_names_get_key_value_disp_name_n4
* @since_tizen 5.0
* @description Calls i18n_loc_disp_names_get_key_value_disp_name passing invalid name
*               and checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_loc_disp_names_get_key_value_disp_name_n4(void)
{
    ret = i18n_loc_disp_names_get_key_value_disp_name(loc_disp, key, value, NULL);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}
