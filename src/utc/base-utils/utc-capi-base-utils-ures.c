#include "assert.h"
#include <app_common.h>
#include <utils_i18n.h>
#include <string.h>

#define API_NAMESPACE                                           "BASE_UTILS_UTC"
#define I18N_UPRV_LENGTHOF(array) (int32_t)(sizeof(array)/sizeof((array)[0]))

static int ret = I18N_ERROR_NONE;
static const char *locales = "en";
static int i;
static i18n_ures_h ures;

/**
* @function        utc_capi_base_utils_ures_startup
* @description     Called before each test
* @parameter       NA
* @return          NA
*/
void utc_capi_base_utils_ures_startup(void)
{
}

/**
* @function        utc_capi_base_utils_ures_cleanup
* @description     Called after each test
* @parameter       NA
* @return          NA
*/
void utc_capi_base_utils_ures_cleanup(void)
{
	if (ures != NULL) {
		i18n_ures_destroy(ures);
		ures = NULL;
	}
}

static void utc_base_utils_get_resource_path(char *path, int size)
{
	char *apps_root;
	if (NULL == path)
		return;

	apps_root = app_get_resource_path();
	assert_neq(apps_root, NULL);

	snprintf(path, size, "%s", apps_root);
	FPRINTF("resource path]: %s", path);
	free(apps_root);
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_create_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_create_p(void)
{
	ret = i18n_ures_create(NULL, locales, &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_create_n
 * @since_tizen 6.0
 * @description Calls i18n_ures_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_create_n(void)
{
	ret = i18n_ures_create("wrong", locales, &ures);
	assert_eq(ret, I18N_ERROR_MISSING_RESOURCE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_create_direct_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_create_direct and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_create_direct_p(void)
{
	ret = i18n_ures_create_direct(NULL, locales, &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_create_direct_n
 * @since_tizen 6.0
 * @description Calls i18n_ures_create_direct and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_create_direct_n(void)
{
	ret = i18n_ures_create_direct(NULL, "wrong", &ures);
	assert_eq(ret, I18N_ERROR_MISSING_RESOURCE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_create_unicode_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_create_unicode and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_create_unicode_p(void)
{

	ret = i18n_ures_create_unicode(NULL, locales, &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_create_unicode_n
 * @since_tizen 6.0
 * @description Calls i18n_ures_create_unicode and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_create_unicode_n(void)
{
	i18n_uchar buffer[1025];
	i18n_ustring_mem_set(buffer, 0x0030, I18N_UPRV_LENGTHOF(buffer));
	buffer[I18N_UPRV_LENGTHOF(buffer)-1] = 0;

	ret = i18n_ures_create_unicode(buffer, "root", &ures);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_destroy_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_destroy_p(void)
{
	ret = i18n_ures_create(NULL, locales, &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ures_destroy(ures);
	assert_eq(ret, I18N_ERROR_NONE);

	ures = NULL;

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_destroy_n
 * @since_tizen 6.0
 * @description Calls i18n_ures_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_destroy_n(void)
{
	ret = i18n_ures_destroy(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_version_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_version and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_version_p(void)
{
	ret = i18n_ures_create(NULL, locales, &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uversion_info version_array;
	ret = i18n_ures_get_version(ures, version_array);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_version_n
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_version and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_version_n(void)
{
	i18n_uversion_info version_array;
	ret = i18n_ures_get_version(NULL, version_array);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_locale_by_type_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_locale_by_type and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_locale_by_type_p(void)
{
	ret = i18n_ures_create(NULL, locales, &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	const char *locale = NULL;
	ret = i18n_ures_get_locale_by_type(ures, I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE, &locale);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_locale_by_type_n1
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_locale_by_type and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_locale_by_type_n1(void)
{
	const char *locale = NULL;
	ret = i18n_ures_get_locale_by_type(NULL, I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE, &locale);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_locale_by_type_n2
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_locale_by_type and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_locale_by_type_n2(void)
{
	ret = i18n_ures_create(NULL, locales, &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	const char *locale = NULL;
	ret = i18n_ures_get_locale_by_type(ures, (i18n_ulocale_data_locale_type_e)-1, &locale);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_locale_by_type_n3
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_locale_by_type and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_locale_by_type_n3(void)
{
	ret = i18n_ures_create(NULL, locales, &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	const char *locale = NULL;
	ret = i18n_ures_get_locale_by_type(ures, (i18n_ulocale_data_locale_type_e)4, &locale);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_string_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_string and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_string_p(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ures_h item = NULL;
	int32_t len;
	int count;
	const i18n_uchar *str_result;
	i18n_ures_type_e type_result;

	ret = i18n_ures_get_size(ures, &count);
	assert_eq(ret, I18N_ERROR_NONE);

	for(int i = 0; i<count; ++i) {
		ret = i18n_ures_get_by_index(ures, i, item, &item);
		assert_eq(ret, I18N_ERROR_NONE);

		ret = i18n_ures_get_type(item, &type_result);
		assert_eq(ret, I18N_ERROR_NONE);

		switch(type_result) {
			case I18N_URES_STRING:
				{
					ret = i18n_ures_get_string(item, &len, &str_result);
					assert_eq(ret, I18N_ERROR_NONE);

					break;
				}
			}
		}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_string_n
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_string and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_string_n(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ures_h item = NULL;
	int32_t len;
	int count;
	const i18n_uchar *str_result;
	i18n_ures_type_e type_result;

	ret = i18n_ures_get_size(ures, &count);
	assert_eq(ret, I18N_ERROR_NONE);

	for(int i = 0; i<count; ++i) {
		ret = i18n_ures_get_by_index(ures, i, item, &item);
		assert_eq(ret, I18N_ERROR_NONE);

		ret = i18n_ures_get_type(item, &type_result);
		assert_eq(ret, I18N_ERROR_NONE);

		switch(type_result) {
			case I18N_URES_STRING:
				{
					ret = i18n_ures_get_string(NULL, &len, &str_result);
					assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

					break;
				}
			}
		}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_UTF8_string_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_UTF8_string and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_UTF8_string_p(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ures_h item = NULL;
	int count;
	i18n_ures_type_e type_result;

	const char *result = NULL;
	char *p8;
	char buffer8[16];
	p8 = buffer8;
	int32_t result_len = (int32_t)sizeof(buffer8);

	ret = i18n_ures_get_size(ures, &count);
	assert_eq(ret, I18N_ERROR_NONE);

	if(count > 10)
		count = 10;

	for(int i = 0; i < count; ++i) {
		ret = i18n_ures_get_by_index(ures, i, item, &item);
		assert_eq(ret, I18N_ERROR_NONE);

		ret = i18n_ures_get_type(item, &type_result);
		assert_eq(ret, I18N_ERROR_NONE);

		switch(type_result) {
			case I18N_URES_STRING:
				{
					ret = i18n_ures_get_UTF8_string(item, p8, &result_len, true, &result);
					assert_eq(ret, I18N_ERROR_NONE);
					break;
				}
			}
		}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_UTF8_string_n1
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_UTF8_string and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_UTF8_string_n1(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ures_h item = NULL;
	int count;
	i18n_ures_type_e type_result;

	const char *result = NULL;
	char *p8;
	char buffer8[16];
	p8 = buffer8;
	int32_t result_len = (int32_t)sizeof(buffer8);

	ret = i18n_ures_get_size(ures, &count);
	assert_eq(ret, I18N_ERROR_NONE);

	if(count > 10)
		count = 10;

	for(int i = 0; i < count; ++i) {
		ret = i18n_ures_get_by_index(ures, i, item, &item);
		assert_eq(ret, I18N_ERROR_NONE);

		ret = i18n_ures_get_type(item, &type_result);
		assert_eq(ret, I18N_ERROR_NONE);

		switch(type_result) {
			case I18N_URES_STRING:
				{
					ret = i18n_ures_get_UTF8_string(NULL, p8, &result_len, true, &result);
					assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
					break;
				}
			}
		}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_binary_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_binary and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_binary_p(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t len;
	const uint8_t *binary_result;
	i18n_ures_h res = NULL;

	// get binary
	ret = i18n_ures_get_by_key(ures, "binarytest", res, &res);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ures_get_binary(res, &len, &binary_result);
	assert_eq(ret, I18N_ERROR_NONE);

	for(int i = 0; i < 15; ++i) {
		assert_eq(binary_result[i], i);
	}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_binary_n1
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_binary and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_binary_n1(void)
{
	int32_t len;
	const uint8_t *binary_result;

	ret = i18n_ures_get_binary(NULL, &len, &binary_result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_binary_n2
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_binary and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_binary_n2(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t len;
	i18n_ures_h res = NULL;

	// get binary
	ret = i18n_ures_get_by_key(ures, "binarytest", res, &res);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ures_get_binary(res, &len, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_int_vector_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_int_vector and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_int_vector_p(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t len;
	const int32_t *int_vector_result;
	i18n_ures_h res = NULL;

	//get int vector
	ret = i18n_ures_get_by_key(ures, "emptyintv", res, &res);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ures_get_int_vector(res, &len, &int_vector_result);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(len, 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_int_vector_n1
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_int_vector and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_int_vector_n1(void)
{
	int32_t len;
	const int32_t *int_vector_result;

	ret = i18n_ures_get_int_vector(NULL, &len, &int_vector_result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_int_vector_n2
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_int_vector and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_int_vector_n2(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t len;
	i18n_ures_h res = NULL;

	//get int vector
	ret = i18n_ures_get_by_key(ures, "emptyintv", res, &res);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ures_get_int_vector(res, &len, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_uint_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_uint and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_uint_p(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	uint32_t uint_result;
	i18n_ures_h res = NULL;

	ret = i18n_ures_get_by_key(ures, "one", res, &res);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ures_get_uint(res, &uint_result);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(uint_result, 1);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_uint_n1
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_uint and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_uint_n1(void)
{
	uint32_t uint_result;

	ret = i18n_ures_get_uint(NULL, &uint_result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_uint_n2
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_uint and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_uint_n2(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ures_h res = NULL;

	ret = i18n_ures_get_by_key(ures, "one", res, &res);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ures_get_uint(res, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_int_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_int and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_int_p(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ures_h item = NULL;
	int32_t int_result;
	int count;
	i18n_ures_type_e type_result;

	ret = i18n_ures_get_size(ures, &count);
	assert_eq(ret, I18N_ERROR_NONE);

	for(int i = 0; i<count; ++i) {
		ret = i18n_ures_get_by_index(ures, i, item, &item);
		assert_eq(ret, I18N_ERROR_NONE);

		ret = i18n_ures_get_type(item, &type_result);
		assert_eq(ret, I18N_ERROR_NONE);

		switch(type_result) {
			case I18N_URES_INT:
				{
					ret = i18n_ures_get_int(item, &int_result);
					assert_eq(ret, I18N_ERROR_NONE);
					break;
				}

			}
		}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_int_n1
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_int and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_int_n1(void)
{
	int32_t int_result;

	ret = i18n_ures_get_int(NULL, &int_result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_int_n2
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_int and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_int_n2(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ures_h res = NULL;

	ret = i18n_ures_get_by_key(ures, "one", res, &res);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ures_get_int(res, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_size_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_size and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_size_p(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	int count;
	ret = i18n_ures_get_size(ures, &count);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_size_n1
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_size and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_size_n1(void)
{
	int32_t size_result;

	ret = i18n_ures_get_size(NULL, &size_result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_size_n2
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_size and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_size_n2(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ures_get_size(ures, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_type_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_type and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_type_p(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ures_h item = NULL;
	int count;
	i18n_ures_type_e type_result;

	ret = i18n_ures_get_size(ures, &count);
	assert_eq(ret, I18N_ERROR_NONE);

	for(int i = 0; i < count; ++i) {
		ret = i18n_ures_get_by_index(ures, i, item, &item);
		assert_eq(ret, I18N_ERROR_NONE);

		ret = i18n_ures_get_type(item, &type_result);
		assert_eq(ret, I18N_ERROR_NONE);
		}

	return 0;
}
/**
 * @testcase utc_capi_base_utils_i18n_ures_get_type_n1
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_type and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_type_n1(void)
{
	i18n_ures_type_e type_result;

	ret = i18n_ures_get_type(NULL, &type_result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_type_n2
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_type and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_type_n2(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ures_get_type(ures, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_key_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_type and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_key_p(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ures_h item = NULL;
	int count;
	const char *key_result;

	ret = i18n_ures_get_size(ures, &count);
	assert_eq(ret, I18N_ERROR_NONE);

	for(int i = 0; i < count; ++i) {
		ret = i18n_ures_get_by_index(ures, i, item, &item);
		assert_eq(ret, I18N_ERROR_NONE);

		ret = i18n_ures_get_key(item, &key_result);
		assert_eq(ret, I18N_ERROR_NONE);
		}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_key_n1
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_key and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_key_n1(void)
{
	const char *key_result;

	ret = i18n_ures_get_key(NULL, &key_result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_key_n2
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_key and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_key_n2(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ures_get_key(ures, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_reset_iterator_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_reset_iterator and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_reset_iterator_p(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ures_reset_iterator(ures);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_reset_iterator_n
 * @since_tizen 6.0
 * @description Calls i18n_ures_reset_iterator and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_reset_iterator_n(void)
{
	ret = i18n_ures_reset_iterator(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_has_next_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_has_next and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_has_next_p(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	bool has_next;
	ret = i18n_ures_has_next(ures, &has_next);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(has_next, true);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_has_next_n1
 * @since_tizen 6.0
 * @description Calls i18n_ures_has_next and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_has_next_n1(void)
{
	bool has_next;
	ret = i18n_ures_has_next(NULL, &has_next);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_has_next_n2
 * @since_tizen 6.0
 * @description Calls i18n_ures_has_next and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_has_next_n2(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ures_has_next(ures, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_next_resource_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_next_resource and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_next_resource_p(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ures_h res = NULL;

	ret = i18n_ures_get_next_resource(ures, res, &res);
	assert_eq(ret, I18N_ERROR_NONE);

	const char *key_result;
	ret = i18n_ures_get_key(res, &key_result);
	assert_eq(strcmp(key_result, "binarytest"), 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_next_resource_n
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_next_resource and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_next_resource_n(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ures_h res = NULL;

	ret = i18n_ures_get_next_resource(NULL, res, &res);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_next_string_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_next_string and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_next_string_p(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	const i18n_uchar *result = NULL;
	int32_t result_len = NULL;
	const char *key;

	ret = i18n_ures_get_next_string(ures, &result_len, &key, &result);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_next_string_n1
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_next_string and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_next_string_n1(void)
{
	const i18n_uchar *result = NULL;
	int32_t result_len = NULL;
	const char *key;

	ret = i18n_ures_get_next_string(NULL, &result_len, &key, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_next_string_n2
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_next_string and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_next_string_n2(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	const i18n_uchar *result = NULL;
	const char *key;

	ret = i18n_ures_get_next_string(ures, NULL, &key, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_next_string_n3
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_next_string and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_next_string_n3(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	const i18n_uchar *result = NULL;
	int32_t result_len = NULL;

	ret = i18n_ures_get_next_string(ures, &result_len, NULL, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_next_string_n4
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_next_string and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_next_string_n4(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t result_len = NULL;
	const char *key;

	ret = i18n_ures_get_next_string(ures, &result_len, &key, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_by_index_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_by_index and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_by_index_p(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ures_h item = NULL;
	int count;
	ret = i18n_ures_get_size(ures, &count);
	assert_eq(ret, I18N_ERROR_NONE);

	for(int i = 0; i < count; ++i) {
		ret = i18n_ures_get_by_index(ures, i, item, &item);
		assert_eq(ret, I18N_ERROR_NONE);

	}

	return 0;
}
/**
 * @testcase utc_capi_base_utils_i18n_ures_get_by_index_n1
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_by_index and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_by_index_n1(void)
{
	i18n_ures_h item = NULL;

	ret = i18n_ures_get_by_index(NULL, i, item, &item);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_by_index_n2
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_by_index and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_by_index_n2(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "testtypes", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ures_h item = NULL;

	ret = i18n_ures_get_by_index(ures, i, item, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_string_by_index_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_string_by_index and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_string_by_index_p(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ures_h res = NULL;
	ret = i18n_ures_get_by_key(ures, "array_only_in_te", res, &res);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t len;
	const i18n_uchar *str_result = NULL;
	ret = i18n_ures_get_string_by_index(res, 0, &len, &str_result);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_string_by_index_n1
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_string_by_index and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_string_by_index_n1(void)
{
	int32_t len;
	const i18n_uchar *str_result = NULL;
	ret = i18n_ures_get_string_by_index(NULL, 0, &len, &str_result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_string_by_index_n2
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_string_by_index and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_string_by_index_n2(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ures_h res = NULL;
	ret = i18n_ures_get_by_key(ures, "array_only_in_te", res, &res);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t len;

	ret = i18n_ures_get_string_by_index(res, 0, &len, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase utc_capi_base_utils_i18n_ures_get_UTF8_string_by_index_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_UTF8_string_by_index and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_UTF8_string_by_index_p(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	const char *str_result = NULL;
	char *p8;
	char buffer8[16];
	p8 = buffer8;
	int32_t len = (int32_t)sizeof(buffer8);

	ret = i18n_ures_get_UTF8_string_by_index(ures, 1, p8, &len, false, &str_result);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_UTF8_string_by_index_n1
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_UTF8_string_by_index and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_UTF8_string_by_index_n1(void)
{
	const char *str_result = NULL;
	char *p8;
	char buffer8[16];
	p8 = buffer8;
	int32_t len = (int32_t)sizeof(buffer8);

	ret = i18n_ures_get_UTF8_string_by_index(NULL, 0, p8, &len, false, &str_result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_UTF8_string_by_index_n2
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_UTF8_string_by_index and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_UTF8_string_by_index_n2(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	const char *str_result = NULL;
	char *p8;
	char buffer8[16];
	p8 = buffer8;
	int32_t len = (int32_t)sizeof(buffer8);

	ret = i18n_ures_get_UTF8_string_by_index(ures, -1, p8, &len, false, &str_result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_UTF8_string_by_index_n3
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_UTF8_string_by_index and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_UTF8_string_by_index_n3(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	const char *str_result = NULL;
	char *p8;
	char buffer8[16];
	p8 = buffer8;
	int32_t len = (int32_t)sizeof(buffer8);

	ret = i18n_ures_get_UTF8_string_by_index(ures, 0, NULL, &len, false, &str_result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_UTF8_string_by_index_n4
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_UTF8_string_by_index and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_UTF8_string_by_index_n4(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	const char *str_result = NULL;
	char *p8;
	char buffer8[16];
	p8 = buffer8;
	int32_t len = (int32_t)sizeof(buffer8);

	ret = i18n_ures_get_UTF8_string_by_index(ures, 0, p8, &len, -1, &str_result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_UTF8_string_by_index_n5
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_UTF8_string_by_index and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_UTF8_string_by_index_n5(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	char *p8;
	char buffer8[16];
	p8 = buffer8;
	int32_t len = (int32_t)sizeof(buffer8);

	ret = i18n_ures_get_UTF8_string_by_index(ures, 0, p8, &len, false, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_by_key_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_by_key and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_by_key_p(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ures_h res = NULL;
	ret = i18n_ures_get_by_key(ures, "array_only_in_te", res, &res);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_by_key_n1
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_by_key and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_by_key_n1(void)
{
	i18n_ures_h res = NULL;
	ret = i18n_ures_get_by_key(NULL, "array_only_in_te", res, &res);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_by_key_n2
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_by_key and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_by_key_n2(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ures_h res = NULL;
	ret = i18n_ures_get_by_key(ures, NULL, res, &res);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_by_key_n3
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_by_key and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_by_key_n3(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ures_h res = NULL;
	ret = i18n_ures_get_by_key(ures, "array_only_in_te", res, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase utc_capi_base_utils_i18n_ures_get_string_by_key_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_string_by_key and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_string_by_key_p(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	const i18n_uchar *result = NULL;
	int32_t result_len = NULL;

	ret = i18n_ures_get_string_by_key(ures, "string_only_in_te", &result_len, &result);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_string_by_key_n1
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_string_by_key and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_string_by_key_n1(void)
{
	const i18n_uchar *result = NULL;
	int32_t result_len = NULL;

	ret = i18n_ures_get_string_by_key(NULL, "string_only_in_te", &result_len, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_string_by_key_n2
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_string_by_key and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_string_by_key_n2(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	const i18n_uchar *result = NULL;
	int32_t result_len = NULL;

	ret = i18n_ures_get_string_by_key(ures, NULL, &result_len, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_string_by_key_n3
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_string_by_key and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_string_by_key_n3(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t result_len = NULL;

	ret = i18n_ures_get_string_by_key(ures, "string_only_in_te", &result_len, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_UTF8_string_by_key_p
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_UTF8_string_by_key and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_UTF8_string_by_key_p(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	const char *result = NULL;
	char *p8;
	char buffer8[16];
	p8 = buffer8;
	int32_t result_len = (int32_t)sizeof(buffer8);

	ret = i18n_ures_get_UTF8_string_by_key(ures, "string_only_in_te", p8, &result_len, false, &result);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(strcmp(result, "TE"), 0);

	ret = i18n_ures_get_UTF8_string_by_key(ures, "string_only_in_te", p8, &result_len, true, &result);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_UTF8_string_by_key_n1
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_UTF8_string_by_key and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_UTF8_string_by_key_n1(void)
{
	const char *result = NULL;
	char *p8;
	char buffer8[16];
	p8 = buffer8;
	int32_t result_len = (int32_t)sizeof(buffer8);

	ret = i18n_ures_get_UTF8_string_by_key(NULL, "string_only_in_te", p8, &result_len, false, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_UTF8_string_by_key_n2
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_UTF8_string_by_key and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_UTF8_string_by_key_n2(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	const char *result = NULL;
	char *p8;
	char buffer8[16];
	p8 = buffer8;
	int32_t result_len = (int32_t)sizeof(buffer8);

	ret = i18n_ures_get_UTF8_string_by_key(ures, NULL, p8, &result_len, false, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_UTF8_string_by_key_n3
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_UTF8_string_by_key and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_UTF8_string_by_key_n3(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	const char *result = NULL;
	char *p8;
	char buffer8[16];
	p8 = buffer8;
	int32_t result_len = (int32_t)sizeof(buffer8);

	ret = i18n_ures_get_UTF8_string_by_key(ures, "string_only_in_te", NULL, &result_len, false, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_UTF8_string_by_key_n4
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_UTF8_string_by_key and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_UTF8_string_by_key_n4(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	const char *result = NULL;
	char *p8;
	char buffer8[16];
	p8 = buffer8;

	ret = i18n_ures_get_UTF8_string_by_key(ures, "string_only_in_te", p8, NULL, false, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ures_get_UTF8_string_by_key_n5
 * @since_tizen 6.0
 * @description Calls i18n_ures_get_UTF8_string_by_key and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ures_get_UTF8_string_by_key_n5(void)
{
	char res_path[CONFIG_VALUE_LEN_MAX] = {0,};
	utc_base_utils_get_resource_path(res_path, CONFIG_VALUE_LEN_MAX - 1);
	ret = i18n_ures_create(res_path, "te", &ures);
	assert_eq(ret, I18N_ERROR_NONE);

	char *p8;
	char buffer8[16];
	p8 = buffer8;
	int32_t result_len = (int32_t)sizeof(buffer8);

	ret = i18n_ures_get_UTF8_string_by_key(ures, "string_only_in_te", p8, &result_len, false, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

