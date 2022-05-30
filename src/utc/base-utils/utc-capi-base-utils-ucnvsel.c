#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

#define I18N_UPRV_LENGTHOF(array) (int32_t)(sizeof(array)/sizeof((array)[0]))

static int ret = I18N_ERROR_NONE;
static int i;
static i18n_uconverter_selector_h g_sel;

/**
 * @function        utc_capi_base_utils_ucnvsel_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_ucnvsel_startup(void)
{
}

/**
 * @function        utc_capi_base_utils_ucnvsel_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_ucnvsel_cleanup(void)
{
}

static const char **g_available_names = NULL;
static int32_t g_count_available = 0;

static const char ** get_encodings(int32_t start, int32_t step, int32_t count, int32_t *pCount)
{
	const char **names;
	int32_t i;

	*pCount = 0;
	if (count <= 0) {
		return NULL;
	}
	names = (const char **)malloc(count * sizeof(char *));
	if (names == NULL) return NULL;

	if (step == 0 && count > 0)
		step = 1;

	return names;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnvsel_create_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnvsel_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnvsel_create_p(void)
{
	int32_t num_encodings;
	const char **encodings = get_encodings(1, 0, 1, &num_encodings);

	i18n_uset_h excluded_set = NULL;
	ret = i18n_uset_create_empty(&excluded_set);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnvsel_create(encodings, num_encodings, excluded_set, I18N_UCNV_ROUNDTRIP_SET, &g_sel);
	assert_eq(ret, I18N_ERROR_NONE);

	free(encodings);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnvsel_create_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnvsel_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnvsel_create_n1(void)
{
	int32_t num_encodings;
	const char **encodings = get_encodings(1, 0, 1, &num_encodings);

	i18n_uset_h excluded_set = NULL;
	ret = i18n_uset_create_empty(&excluded_set);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnvsel_create(encodings, -1, excluded_set, I18N_UCNV_ROUNDTRIP_SET, &g_sel);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	free(encodings);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnvsel_create_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnvsel_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnvsel_create_n2(void)
{
	int32_t num_encodings;

	i18n_uset_h excluded_set = NULL;
	ret = i18n_uset_create_empty(&excluded_set);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnvsel_create(NULL, 1, excluded_set, I18N_UCNV_ROUNDTRIP_SET, &g_sel);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnvsel_destroy_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnvsel_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnvsel_destroy_p(void)
{
	int32_t num_encodings;
	const char **encodings = get_encodings(1, 0, 1, &num_encodings);

	i18n_uset_h excluded_set = NULL;
	ret = i18n_uset_create_empty(&excluded_set);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnvsel_create(encodings, num_encodings, excluded_set, I18N_UCNV_ROUNDTRIP_SET, &g_sel);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnvsel_destroy(g_sel);
	assert_eq(ret, I18N_ERROR_NONE);

	free(encodings);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnvsel_destroy_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnvsel_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnvsel_destroy_n(void)
{
	ret = i18n_ucnvsel_destroy(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnvsel_create_from_serialized_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnvsel_create_from_serialized and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnvsel_create_from_serialized_p(void)
{
	i18n_uset_h excluded_set = NULL;
	ret = i18n_uset_create_empty(&excluded_set);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnvsel_create(NULL, 0, excluded_set, I18N_UCNV_ROUNDTRIP_AND_FALLBACK_SET, &g_sel);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t ser_len, ser_len2;
	char *new_buffer;

	ret = i18n_ucnvsel_serialize(g_sel, NULL, 0, &ser_len);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

	new_buffer = (char *)malloc(ser_len);
	ret = i18n_ucnvsel_serialize(g_sel, new_buffer, ser_len, &ser_len2);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnvsel_destroy(g_sel);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnvsel_create_from_serialized(new_buffer, ser_len, &g_sel);
	assert_eq(ret, I18N_ERROR_NONE);

	free(new_buffer);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnvsel_create_from_serialized_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnvsel_create_from_serialized and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnvsel_create_from_serialized_n1(void)
{
	char *new_buffer = NULL;

	ret = i18n_ucnvsel_create_from_serialized(new_buffer, 10, &g_sel);
	assert_eq(ret, I18N_ERROR_OUT_OF_MEMORY);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnvsel_create_from_serialized_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnvsel_create_from_serialized and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnvsel_create_from_serialized_n2(void)
{
	char *new_buffer = NULL;

	ret = i18n_ucnvsel_create_from_serialized(new_buffer, -1, &g_sel);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnvsel_serialize_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnvsel_serialize and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnvsel_serialize_p(void)
{
	char *new_buffer;
	int32_t len, len2;

	i18n_uset_h excluded_set = NULL;
	ret = i18n_uset_create_empty(&excluded_set);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnvsel_create(NULL, 0, excluded_set, I18N_UCNV_ROUNDTRIP_SET, &g_sel);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnvsel_serialize(g_sel, NULL, 0, &len);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

	new_buffer = (char *)malloc(sizeof(char) * len);
	ret = i18n_ucnvsel_serialize(g_sel, new_buffer, len, &len2);
	assert_eq(ret, I18N_ERROR_NONE);

	free(new_buffer);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnvsel_serialize_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnvsel_serialize and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnvsel_serialize_n(void)
{
	char *new_buffer = NULL;
	int32_t len;

	ret = i18n_ucnvsel_serialize(g_sel, new_buffer, -1, &len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnvsel_select_for_string_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnvsel_select_for_string and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnvsel_select_for_string_p(void)
{
	i18n_uenumeration_h enumeration;
	const char *char_str = "Hello World!";
	const i18n_uchar string[20] = {0,};
	int32_t len;
	i18n_error_code_e status;

	i18n_ustring_from_UTF8((i18n_uchar *)string, I18N_UPRV_LENGTHOF(string), &len, char_str, 5, &status);
	assert_eq(status, I18N_ERROR_NONE);

	i18n_uset_h excluded_set = NULL;
	ret = i18n_uset_create_empty(&excluded_set);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnvsel_create(NULL, 0, excluded_set, I18N_UCNV_ROUNDTRIP_AND_FALLBACK_SET, &g_sel);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnvsel_select_for_string(g_sel, string, len, &enumeration);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnvsel_select_for_string_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnvsel_select_for_string and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnvsel_select_for_string_n1(void)
{
	i18n_uenumeration_h enumeration;
	const i18n_uchar *string;

	ret = i18n_ucnvsel_select_for_string(NULL, string, 1, &enumeration);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;

}

/**
 * @testcase utc_capi_base_utils_i18n_ucnvsel_select_for_string_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnvsel_select_for_string and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnvsel_select_for_string_n2(void)
{
	i18n_uenumeration_h enumeration;

	i18n_uset_h excluded_set = NULL;
	ret = i18n_uset_create_empty(&excluded_set);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnvsel_create(NULL, 0, excluded_set, I18N_UCNV_ROUNDTRIP_AND_FALLBACK_SET, &g_sel);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnvsel_select_for_string(g_sel, NULL, 1, &enumeration);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;

}

/**
 * @testcase utc_capi_base_utils_i18n_ucnvsel_select_for_utf8_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnvsel_select_for_utf8 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnvsel_select_for_utf8_p(void)
{
	i18n_uenumeration_h enumeration;
	const char *string = "Hello world!";

	i18n_uset_h excluded_set = NULL;
	ret = i18n_uset_create_empty(&excluded_set);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnvsel_create(NULL, 0, excluded_set, I18N_UCNV_ROUNDTRIP_AND_FALLBACK_SET, &g_sel);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnvsel_select_for_utf8(g_sel, string, 5, &enumeration);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnvsel_select_for_utf8_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnvsel_select_for_utf8 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnvsel_select_for_utf8_n1(void)
{
	i18n_uenumeration_h enumeration;
	const char *string;

	ret = i18n_ucnvsel_select_for_utf8(NULL, string, 1, &enumeration);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnvsel_select_for_utf8_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnvsel_select_for_utf8 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnvsel_select_for_utf8_n2(void)
{
	i18n_uenumeration_h enumeration;

	i18n_uset_h excluded_set = NULL;
	ret = i18n_uset_create_empty(&excluded_set);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnvsel_create(NULL, 0, excluded_set, I18N_UCNV_ROUNDTRIP_AND_FALLBACK_SET, &g_sel);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnvsel_select_for_utf8(g_sel, NULL, 1, &enumeration);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}
