#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

static int ret = I18N_ERROR_NONE;
static i18n_unumsys_h unumsys;

/**
* @function        utc_capi_base_utils_unumsys_startup
* @description     Called before each test
* @parameter       NA
* @return          NA
*/
void utc_capi_base_utils_unumsys_startup(void)
{
}

/**
* @function        utc_capi_base_utils_unumsys_cleanup
* @description     Called after each test
* @parameter       NA
* @return          NA
*/
void utc_capi_base_utils_unumsys_cleanup(void)
{
}

/**
 * @testcase utc_capi_base_utils_i18n_unumsys_create_p
 * @since_tizen 6.0
 * @description Calls i18n_unumsys_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unumsys_create_p(void)
{
	ret = i18n_unumsys_create("en@numbers=roman", &unumsys);
	assert_eq(ret, I18N_ERROR_NONE);

	if(unumsys != NULL)
		i18n_unumsys_destroy(unumsys);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unumsys_create_n1
 * @since_tizen 6.0
 * @description Calls i18n_unumsys_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unumsys_create_n(void)
{
	ret = i18n_unumsys_create("en@numbers=xyz", &unumsys);
	assert_eq(ret, I18N_ERROR_NOT_SUPPORTED);

	if(unumsys != NULL)
		i18n_unumsys_destroy(unumsys);

	return 0;
}


/**
 * @testcase utc_capi_base_utils_i18n_unumsys_create_by_name_p
 * @since_tizen 6.0
 * @description Calls i18n_unumsys_create_by_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unumsys_create_by_name_p(void)
{
	ret = i18n_unumsys_create("latn", &unumsys);
	assert_eq(ret, I18N_ERROR_NONE);

	if(unumsys != NULL)
		i18n_unumsys_destroy(unumsys);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unumsys_create_by_name_n1
 * @since_tizen 6.0
 * @description Calls i18n_unumsys_create_by_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unumsys_create_by_name_n1(void)
{
	ret = i18n_unumsys_create_by_name("xyz", &unumsys);
	assert_eq(ret, I18N_ERROR_NOT_SUPPORTED);

	if(unumsys != NULL)
		i18n_unumsys_destroy(unumsys);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unumsys_create_by_name_n2
 * @since_tizen 6.0
 * @description Calls i18n_unumsys_create_by_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unumsys_create_by_name_n2(void)
{
	ret = i18n_unumsys_create_by_name(NULL, &unumsys);
	assert_eq(ret, I18N_ERROR_NOT_SUPPORTED);

	if(unumsys != NULL)
		i18n_unumsys_destroy(unumsys);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unumsys_get_available_names_p
 * @since_tizen 6.0
 * @description Calls i18n_unumsys_get_available_names and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unumsys_get_available_names_p(void)
{
	static i18n_uenumeration_h uenum;
	ret = i18n_unumsys_get_available_names(&uenum);
	assert_eq(ret, I18N_ERROR_NONE);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unumsys_get_available_names_n
 * @since_tizen 6.0
 * @description Calls i18n_unumsys_get_available_names and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unumsys_get_available_names_n(void)
{
	ret = i18n_unumsys_get_available_names(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unumsys_get_name_p
 * @since_tizen 6.0
 * @description Calls i18n_unumsys_get_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unumsys_get_name_p(void)
{
	ret = i18n_unumsys_create("en", &unumsys);
	assert_eq(ret, I18N_ERROR_NONE);

	const char *numsys;
	ret = i18n_unumsys_get_name(unumsys, &numsys);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(strcmp(numsys, "latn"), 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unumsys_get_name_n
 * @since_tizen 6.0
 * @description Calls i18n_unumsys_get_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unumsys_get_name_n(void)
{
	const char *numsys;
	ret = i18n_unumsys_get_name(NULL, &numsys);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unumsys_is_algorithmic_p1
 * @since_tizen 6.0
 * @description Calls i18n_unumsys_is_algorithmic and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unumsys_is_algorithmic_p1(void)
{
	ret = i18n_unumsys_create("en", &unumsys);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ubool result;
	ret = i18n_unumsys_is_algorithmic(unumsys, &result);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(result, false);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unumsys_is_algorithmic_p2
 * @since_tizen 6.0
 * @description Calls i18n_unumsys_is_algorithmic and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unumsys_is_algorithmic_p2(void)
{
	ret = i18n_unumsys_create("en@numbers=roman", &unumsys);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ubool result;
	ret = i18n_unumsys_is_algorithmic(unumsys, &result);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(result, true);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unumsys_is_algorithmic_n
 * @since_tizen 6.0
 * @description Calls i18n_unumsys_is_algorithmic and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unumsys_is_algorithmic_n(void)
{
	i18n_ubool result;
	ret = i18n_unumsys_is_algorithmic(NULL, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unumsys_get_radix_p
 * @since_tizen 6.0
 * @description Calls i18n_unumsys_get_radix and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unumsys_get_radix_p(void)
{
	ret = i18n_unumsys_create("en", &unumsys);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t result;
	ret = i18n_unumsys_get_radix(unumsys, &result);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(result, 10);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unumsys_get_radix_n
 * @since_tizen 6.0
 * @description Calls i18n_unumsys_get_radix and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unumsys_get_radix_n(void)
{
	int32_t result;
	ret = i18n_unumsys_get_radix(NULL, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unumsys_get_description_p
 * @since_tizen 6.0
 * @description Calls i18n_unumsys_get_description and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unumsys_get_description_p(void)
{
	static const i18n_uchar latn_desc[]	 = {0x0030,0x0031,0x0032,0x0033,0x0034,0x0035,0x0036,0x0037,0x0038,0x0039,0}; // 0123456789

	ret = i18n_unumsys_create("en", &unumsys);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t ulen;
	i18n_uchar result[64];
	ret = i18n_unumsys_get_description(unumsys, result, 64, &ulen);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(i18n_ustring_compare(result, latn_desc), 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unumsys_get_description_n1
 * @since_tizen 6.0
 * @description Calls i18n_unumsys_get_description and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unumsys_get_description_n1(void)
{
	ret = i18n_unumsys_create("en", &unumsys);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t ulen;
	ret = i18n_unumsys_get_description(unumsys, NULL, 64, &ulen);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unumsys_get_description_n2
 * @since_tizen 6.0
 * @description Calls i18n_unumsys_get_description and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unumsys_get_description_n2(void)
{
	ret = i18n_unumsys_create("en", &unumsys);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar result[64];
	int32_t ulen;
	ret = i18n_unumsys_get_description(unumsys, result, -1, &ulen);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unumsys_get_description_n3
 * @since_tizen 6.0
 * @description Calls i18n_unumsys_get_description and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unumsys_get_description_n3(void)
{
	i18n_uchar result[64];
	int32_t ulen;
	ret = i18n_unumsys_get_description(NULL, result, 64, &ulen);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

