#include "assert.h"
#include <string.h>
#include <utils_i18n.h>

static int ret = I18N_ERROR_NONE;
static i18n_utext_h uta;
static i18n_utext_h utb;

/**
* @function        utc_capi_base_utils_utext_startup
* @description     Called before each test
* @parameter       NA
* @return          NA
*/
void utc_capi_base_utils_utext_startup(void)
{
}

/**
* @function        utc_capi_base_utils_utext_cleanup
* @description     Called after each test
* @parameter       NA
* @return          NA
*/
void utc_capi_base_utils_utext_cleanup(void)
{
	if(uta != NULL) {
		i18n_utext_destroy(uta);
		uta = NULL;
	}

	if(utb != NULL) {
		i18n_utext_destroy(utb);
		utb = NULL;
	}

}

/**
 * @testcase utc_capi_base_utils_i18n_utext_create_for_UTF8_p
 * @since_tizen 6.0
 * @description Calls i18n_utext_create_for_UTF8 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_create_for_UTF8_p(void)
{
	i18n_utext_h *utLoc;
	i18n_uchar32 c;

	ret = i18n_utext_create_for_UTF8(NULL, NULL, 0, &uta);
	assert_eq(ret, I18N_ERROR_NONE);
	c = i18n_utext_next32(uta);
	assert_eq(c, I18N_SENTINEL);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_create_for_UTF8_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_create_for_UTF8 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_create_for_UTF8_n(void)
{
	i18n_utext_h *utLoc;
	i18n_uchar32 c;

	ret = i18n_utext_create_for_UTF8(NULL, NULL, 0, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_create_for_uchars_p
 * @since_tizen 6.0
 * @description Calls i18n_utext_create_for_uchars and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_create_for_uchars_p(void)
{
	i18n_uchar  uString[]  = {0x41, 0x42, 0x43, 0}; //ABC

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(uta, NULL);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_create_for_uchars_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_create_for_uchars and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_create_for_uchars_n(void)
{
	i18n_uchar	uString[]  = {0x41, 0x42, 0x43, 0}; //ABC

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_clone_p
 * @since_tizen 6.0
 * @description Calls i18n_utext_clone and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_clone_p(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_utext_clone(NULL, uta, false, false, &utb);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(utb, NULL);
	assert_neq(utb, uta);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_clone_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_clone and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_clone_n(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_utext_clone(NULL, NULL, false, false, &utb);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_equals_p
 * @since_tizen 6.0
 * @description Calls i18n_utext_equals and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_equals_p(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC
	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &utb);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ubool result = i18n_utext_equals(uta, utb);
	assert_eq(result, true);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_equals_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_equals and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_equals_n(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC
	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &utb);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ubool result = i18n_utext_equals(NULL, utb);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	assert_eq(result, false);

	result = i18n_utext_equals(uta, NULL);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	assert_eq(result, false);

	result = i18n_utext_equals(NULL, NULL);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	assert_eq(result, false);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_native_length_p
 * @since_tizen 6.0
 * @description Calls i18n_utext_native_length and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_native_length_p(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC
	int64_t len;

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_utext_clone(NULL, uta, false, false, &utb);
	assert_eq(ret, I18N_ERROR_NONE);

	len = i18n_utext_native_length(uta);
	assert_eq(len, i18n_ustring_get_length(uString));

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_native_length_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_native_length and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_native_length_n(void)
{
	int64_t len;

	len = i18n_utext_native_length(NULL);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_is_length_expensive_p
 * @since_tizen 6.0
 * @description Calls i18n_utext_is_length_expensive and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_is_length_expensive_p(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC
	i18n_ubool b;

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	b = i18n_utext_is_length_expensive(uta);
	assert_eq(b, true);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_is_length_expensive_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_is_length_expensive and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_is_length_expensive_n(void)
{
	i18n_ubool b;

	b = i18n_utext_is_length_expensive(NULL);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_char32_at_p
 * @since_tizen 6.0
 * @description Calls i18n_utext_char32_at and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_char32_at_p(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC
	i18n_uchar32 c;

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	c = i18n_utext_char32_at(uta, 0);
	assert_eq(c, uString[0]);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_char32_at_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_char32_at and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_char32_at_n(void)
{
	i18n_uchar32 c;

	c = i18n_utext_char32_at(NULL, 0);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_current32_p
 * @since_tizen 6.0
 * @description Calls i18n_utext_current32 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_current32_p(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC
	i18n_uchar32 c;

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	c = i18n_utext_current32(uta);
	assert_eq(c, uString[0]);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_current32_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_current32 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_current32_n(void)
{
	i18n_uchar32 c;

	c = i18n_utext_current32(NULL);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_next32_p
 * @since_tizen 6.0
 * @description Calls i18n_utext_next32 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_next32_p(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC
	i18n_uchar32 c;

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	c = i18n_utext_next32(uta);
	assert_eq(c, uString[0]);
	c = i18n_utext_current32(uta);
	assert_eq(c, uString[1]);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_next32_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_next32 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_next32_n(void)
{
	i18n_uchar32 c;

	c = i18n_utext_current32(NULL);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_previous32_p
 * @since_tizen 6.0
 * @description Calls i18n_utext_previous32 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_previous32_p(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC
	i18n_uchar32 c;

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_utext_set_native_index(uta, 0);
	c = i18n_utext_previous32(uta);
	assert_eq(c, I18N_SENTINEL);
	c = i18n_utext_current32(uta);
	assert_eq(c, uString[0]);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_previous32_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_previous32 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_previous32_n(void)
{
	i18n_uchar32 c;
	c = i18n_utext_current32(NULL);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_next32_from_p
 * @since_tizen 6.0
 * @description Calls i18n_utext_next32_from and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_next32_from_p(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC
	i18n_uchar32 c;

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	c = i18n_utext_next32_from(uta, 1);
	assert_eq(c, uString[1]);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_next32_from_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_next32_from and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_next32_from_n(void)
{
	i18n_uchar32 c;
	c = i18n_utext_next32_from(NULL, 1);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_previous32_from_p
 * @since_tizen 6.0
 * @description Calls i18n_utext_previous32_from and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_previous32_from_p(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC
	i18n_uchar32 c;

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	c = i18n_utext_previous32_from(uta, 2);
	assert_eq(c, uString[1]);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_previous32_from_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_previous32_from and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_previous32_from_n(void)
{
	i18n_uchar32 c;
	c = i18n_utext_previous32_from(NULL, 2);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;

}

/**
 * @testcase utc_capi_base_utils_i18n_utext_set_get_native_index_p
 * @since_tizen 6.0
 * @description Calls i18n_utext_get_native_index and i18n_utext_set_native_index and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_set_get_native_index_p(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC
	int64_t i;

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_utext_set_native_index(uta, 2);
	i = i18n_utext_get_native_index(uta);
	assert_eq(i, 2);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_set_native_index_n1
 * @since_tizen 6.0
 * @description Calls i18n_utext_set_native_index and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_set_native_index_n1(void)
{
	i18n_utext_set_native_index(NULL, 2);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_get_native_index_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_get_native_index and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_get_native_index_n(void)
{
	int64_t i = i18n_utext_get_native_index(NULL);

	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_move_index32_p
 * @since_tizen 6.0
 * @description Calls i18n_utext_move_index32 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_move_index32_p(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC
	i18n_ubool b;

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_utext_set_native_index(uta, 0);
	b = i18n_utext_move_index32(uta, 1);
	assert_eq(b, true);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_move_index32_n1
 * @since_tizen 6.0
 * @description Calls i18n_utext_move_index32 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_move_index32_n1(void)
{
	i18n_utext_move_index32(NULL, 1);

	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_get_previous_native_index_p
 * @since_tizen 6.0
 * @description Calls i18n_utext_get_previous_native_index and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_get_previous_native_index_p(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC
	int64_t i;

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_utext_set_native_index(uta, 1);
	i = i18n_utext_get_previous_native_index(uta);
	assert_eq(i, 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_get_previous_native_index_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_get_previous_native_index and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_get_previous_native_index_n(void)
{
 	int64_t i = i18n_utext_get_previous_native_index(NULL);

	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_extract_p
 * @since_tizen 6.0
 * @description Calls i18n_utext_extract and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_extract_p(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC
	int32_t len;

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar buf[100];
	memset(buf, 0, sizeof(buf));
	ret = i18n_utext_extract(uta, 0, 100, buf, 100, &len);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(len, i18n_ustring_get_length(uString));

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_extract_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_extract and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_extract_n(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC
	int32_t len;

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_utext_extract(uta, 0, 100, NULL, 0, &len);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_is_writable_p
 * @since_tizen 6.0
 * @description Calls i18n_utext_is_writable and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_is_writable_p(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC
	i18n_ubool b;

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	b = i18n_utext_is_writable(uta);
	assert_eq(b, false);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_is_writable_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_is_writable and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_is_writable_n(void)
{
	i18n_ubool b = i18n_utext_is_writable(NULL);
	assert_eq(b, false);

	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_has_meta_data_p
 * @since_tizen 6.0
 * @description Calls i18n_utext_has_meta_data and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_has_meta_data_p(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC
	i18n_ubool b;

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	b = i18n_utext_has_meta_data(uta);
	assert_eq(b, false);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_has_meta_data_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_has_meta_data and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_has_meta_data_n(void)
{
	i18n_ubool b = i18n_utext_has_meta_data(NULL);

	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_replace_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_replace and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_replace_n(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC
	int32_t number;

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_utext_replace(uta, 0, 1, uString, -1, &number);
	assert_eq(ret, I18N_ERROR_NO_WRITE_PERMISSION);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_copy_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_copy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_copy_n(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_utext_copy(uta, 0, 1, 2, false);
	assert_eq(ret, I18N_ERROR_NO_WRITE_PERMISSION);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_freeze_p
 * @since_tizen 6.0
 * @description Calls i18n_utext_freeze and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_freeze_p(void)
{
	i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0}; //ABC
	i18n_ubool b;

	ret = i18n_utext_create_for_uchars(NULL, uString, -1, &uta);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_utext_freeze(uta);

	b = i18n_utext_is_writable(uta);
	assert_eq(b, false);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utext_freeze_n
 * @since_tizen 6.0
 * @description Calls i18n_utext_freeze and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_utext_freeze_n(void)
{
	i18n_utext_freeze(NULL);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}
