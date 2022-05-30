#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

#define I18N_UPRV_LENGTHOF(array) (int32_t)(sizeof(array)/sizeof((array)[0]))

static int ret = I18N_ERROR_NONE;
static int i;
static i18n_ucnv_h cnv;

/**
 * @function        utc_capi_base_utils_ucnv_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_ucnv_startup(void)
{
}

/**
 * @function        utc_capi_base_utils_ucnv_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_ucnv_cleanup(void)
{
	if (!cnv) {
		i18n_ucnv_destroy(cnv);
		cnv = NULL;
	}
}


/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_max_bytes_for_string_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_max_bytes_for_string and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_max_bytes_for_string_p(void)
{
	int result = i18n_ucnv_get_max_bytes_for_string(1, 2);
	assert_eq(result, 22);

	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_max_bytes_for_string_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_max_bytes_for_string and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_max_bytes_for_string_n1(void)
{
	int result = i18n_ucnv_get_max_bytes_for_string(1, -1);
	ret = get_last_result();
	assert_eq(result, -1);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_max_bytes_for_string_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_max_bytes_for_string and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_max_bytes_for_string_n2(void)
{
	int result = i18n_ucnv_get_max_bytes_for_string(-1, 1);
	ret = get_last_result();
	assert_eq(result, -1);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_compare_names_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_compare_names and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_compare_names_p(void)
{
	static const char *equalUTF8[]={ "UTF-8", "utf_8", "u*T@f08", "Utf 8" };

	const char *name1, *name2;
	int result;

	for(i = 0; i<3; ++i) {
		result = i18n_ucnv_compare_names(equalUTF8[i], equalUTF8[i+1]);
		assert_eq(result, 0);
	}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_compare_names_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_compare_names and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_compare_names_n1(void)
{
	static const char equalUTF8[]={ "UTF-8" };
	int result;

	result = i18n_ucnv_compare_names(equalUTF8, NULL);
	ret = get_last_result();
	assert_eq(result, -1);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_compare_names_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_compare_names and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_compare_names_n2(void)
{
	static const char equalUTF8[]={ "UTF-8" };
	int result;

	result = i18n_ucnv_compare_names(NULL, equalUTF8);
	ret = get_last_result();
	assert_eq(result, -1);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_create_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_create_p(void)
{
	ret = i18n_ucnv_create("ibm-949", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_create_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_create_n(void)
{
	ret = i18n_ucnv_create("abc", &cnv);
	assert_eq(ret, I18N_ERROR_FILE_ACCESS);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_create_unicode_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_create_unicode and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_create_unicode_p(void)
{
	i18n_uchar converter_name[] = {0x0069, 0x0062, 0x006d, 0x002d, 0x0039, 0x0034, 0x0033, 0x0000}; /*ibm-943*/

	ret = i18n_ucnv_create_unicode(converter_name, &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_create_unicode(NULL, &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_create_unicode_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_create_unicode and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_create_unicode_n1(void)
{
	const char *illegal_name_chars={ "ibm-943 ibm-943 ibm-943 ibm-943 ibm-943 ibm-943 ibm-943 ibm-943 ibm-943 ibm-943"};
	i18n_uchar illegal_name[100];
	i18n_ustring_copy_ua(illegal_name, "");
	i18n_ustring_copy_ua(illegal_name, illegal_name_chars);

	ret = i18n_ucnv_create_unicode(illegal_name, &cnv);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_create_unicode_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_create_unicode and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_create_unicode_n2(void)
{
	i18n_uchar first_sorted_name[]={ 0x0021, 0x0000}; /* ! */

	ret = i18n_ucnv_create_unicode(first_sorted_name, &cnv);
	assert_eq(ret, I18N_ERROR_FILE_ACCESS);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_create_ccsid_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_create_ccsid and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_create_ccsid_p(void)
{
	int32_t ccsids[]={ 37, 850, 943, 949, 950, 1047, 1252, 1392, 33722 };

	for(int i = 0; i<9; ++i) {
		ret = i18n_ucnv_create_ccsid(ccsids[i], I18N_UCNV_IBM, &cnv);
		assert_eq(ret, I18N_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_create_ccsid_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_create_ccsid and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_create_ccsid_n1(void)
{
	ret = i18n_ucnv_create_ccsid(37, (i18n_ucnv_platform_e) (I18N_UCNV_IBM + 1), &cnv);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_create_ccsid_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_create_ccsid and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_create_ccsid_n2(void)
{
	ret = i18n_ucnv_create_ccsid(37, (i18n_ucnv_platform_e) (I18N_UCNV_UNKNOWN - 1), &cnv);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_safe_clone_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_safe_clone and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_safe_clone_p(void)
{
	ret = i18n_ucnv_create("iso-8859-3", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ucnv_h cnv2;
	ret = i18n_ucnv_safe_clone(cnv, &cnv2);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_safe_clone_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_safe_clone and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_safe_clone_n(void)
{
	i18n_ucnv_h cnv2;
	ret = i18n_ucnv_safe_clone(NULL, &cnv2);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_destroy_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_destroy_p(void)
{
	ret = i18n_ucnv_create("ibm-949", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_destroy(cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_destroy_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_destroy_n(void)
{
	ret = i18n_ucnv_destroy(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_subst_chars_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_subst_chars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_subst_chars_p(void)
{
	char buffer[16];
	int8_t len8;
	static const i18n_uchar sub[5] = { 0x61, 0x62, 0x63, 0x64, 0x65 };

	ret = i18n_ucnv_create("ISO-8859-1", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_set_subst_string(cnv, sub, I18N_UPRV_LENGTHOF(sub));
	assert_eq(ret, I18N_ERROR_NONE);

	len8 = sizeof(buffer);
	ret = i18n_ucnv_get_subst_chars(cnv, buffer, &len8);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_subst_chars_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_subst_chars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_subst_chars_n(void)
{
	char buffer[16];
	int8_t len8;

	len8 = sizeof(buffer);
	ret = i18n_ucnv_get_subst_chars(NULL, buffer, &len8);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_set_subst_chars_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_set_subst_chars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_set_subst_chars_p(void)
{
	char new_subchars[] = {0x7F};
	char get_subchars[10];
	int8_t len = sizeof(new_subchars);

	ret = i18n_ucnv_create(NULL, &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_set_subst_chars(cnv, new_subchars, len);

	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_get_subst_chars(cnv, get_subchars, &len);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(len, 1);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_set_subst_chars_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_set_subst_chars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_set_subst_chars_n(void)
{
	char new_subchars[] = {0x7F};
	char get_subchars[1];
	int8_t len = sizeof(get_subchars);

	ret = i18n_ucnv_set_subst_chars(NULL, new_subchars, len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_set_subst_string_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_set_subst_string and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_set_subst_string_p(void)
{
	char buffer[16];
	int8_t len8;
	static const i18n_uchar sub[5] = { 0x61, 0x62, 0x63, 0x64, 0x65 };

	ret = i18n_ucnv_create("ISO-8859-1", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_set_subst_string(cnv, sub, I18N_UPRV_LENGTHOF(sub));
	assert_eq(ret, I18N_ERROR_NONE);

	len8 = sizeof(buffer);
	ret = i18n_ucnv_get_subst_chars(cnv, buffer, &len8);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_set_subst_string_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_set_subst_string and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_set_subst_string_n1(void)
{
	static const i18n_uchar sub[5] = { 0x61, 0x62, 0x63, 0x64, 0x65 };

	ret = i18n_ucnv_set_subst_string(NULL, sub, I18N_UPRV_LENGTHOF(sub));
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_set_subst_string_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_set_subst_string and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_set_subst_string_n2(void)
{
	static const i18n_uchar sub[5] = { 0x61, 0x62, 0x63, 0x64, 0x65 };

	ret = i18n_ucnv_create("ISO-8859-1", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_set_subst_string(cnv, NULL, I18N_UPRV_LENGTHOF(sub));
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_invalid_chars_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_invalid_chars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_invalid_chars_p(void)
{
	ret = i18n_ucnv_create(NULL, &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	char result_invalid_chars[50];
	int8_t result_invalid_len = I18N_UPRV_LENGTHOF(result_invalid_chars);

	ret = i18n_ucnv_get_invalid_chars(cnv, result_invalid_chars, &result_invalid_len);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_invalid_chars_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_invalid_chars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_invalid_chars_n1(void)
{
	char result_invalid_chars[10];
	int8_t result_invalid_len = I18N_UPRV_LENGTHOF(result_invalid_chars);

	ret = i18n_ucnv_get_invalid_chars(NULL, result_invalid_chars, &result_invalid_len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_invalid_chars_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_invalid_chars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_invalid_chars_n2(void)
{
	ret = i18n_ucnv_create(NULL, &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	char result_invalid_chars[10];
	int8_t result_invalid_len = I18N_UPRV_LENGTHOF(result_invalid_chars);

	ret = i18n_ucnv_get_invalid_chars(cnv, NULL, &result_invalid_len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_invalid_chars_n3
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_invalid_chars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_invalid_chars_n3(void)
{
	ret = i18n_ucnv_create(NULL, &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	char result_invalid_chars[10];
	ret = i18n_ucnv_get_invalid_chars(cnv, result_invalid_chars, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_invalid_uchars_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_invalid_uchars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_invalid_uchars_p(void)
{
	ret = i18n_ucnv_create(NULL, &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar result_invalid_chars[10];
	int8_t result_invalid_len = I18N_UPRV_LENGTHOF(result_invalid_chars);

	ret = i18n_ucnv_get_invalid_uchars(cnv, result_invalid_chars, &result_invalid_len);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_invalid_uchars_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_invalid_uchars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_invalid_uchars_n1(void)
{
	i18n_uchar result_invalid_chars[10];
	int8_t result_invalid_len = I18N_UPRV_LENGTHOF(result_invalid_chars);

	ret = i18n_ucnv_get_invalid_uchars(NULL, result_invalid_chars, &result_invalid_len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_invalid_uchars_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_invalid_uchars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_invalid_uchars_n2(void)
{
	ret = i18n_ucnv_create(NULL, &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar result_invalid_chars[10];
	int8_t result_invalid_len = I18N_UPRV_LENGTHOF(result_invalid_chars);

	ret = i18n_ucnv_get_invalid_uchars(cnv, NULL, &result_invalid_len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_invalid_uchars_n3
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_invalid_uchars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_invalid_uchars_n3(void)
{
	ret = i18n_ucnv_create(NULL, &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar result_invalid_chars[10];
	ret = i18n_ucnv_get_invalid_uchars(cnv, result_invalid_chars, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_reset_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_reset and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_reset_p(void)
{
	ret = i18n_ucnv_create(NULL, &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_reset(cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_reset_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_reset and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_reset_n(void)
{
	ret = i18n_ucnv_reset(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_reset_to_unicode_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_reset_to_unicode and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_reset_to_unicode_p(void)
{
	ret = i18n_ucnv_create(NULL, &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_reset_to_unicode(cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_reset_to_unicode_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_reset_to_unicode and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_reset_to_unicode_n(void)
{
	ret = i18n_ucnv_reset_to_unicode(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_reset_from_unicode_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_reset_from_unicode and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_reset_from_unicode_p(void)
{
	ret = i18n_ucnv_create(NULL, &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_reset_from_unicode(cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_reset_from_unicode_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_reset_from_unicode and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_reset_from_unicode_n(void)
{
	ret = i18n_ucnv_reset_from_unicode(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_max_char_size_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_max_char_size and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_max_char_size_p(void)
{
	ret = i18n_ucnv_create("UTF-16", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	int8_t size;
	ret = i18n_ucnv_get_max_char_size(cnv, &size);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(size, 2);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_max_char_size_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_max_char_size and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_max_char_size_n(void)
{
	int8_t size;
	ret = i18n_ucnv_get_max_char_size(NULL, &size);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_min_char_size_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_min_char_size and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_min_char_size_p(void)
{
	ret = i18n_ucnv_create("ibm-949_P110-1999", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	int8_t size;
	ret = i18n_ucnv_get_min_char_size(cnv, &size);

	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(size, 1);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_min_char_size_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_min_char_size and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_min_char_size_n(void)
{
	int8_t size;
	ret = i18n_ucnv_get_min_char_size(NULL, &size);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_display_name_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_display_name and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_display_name_p(void)
{
	ret = i18n_ucnv_create("ibm-949", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar *display_name = 0;
	int32_t capacity = 0;
	int32_t display_name_len;
	ret = i18n_ucnv_get_display_name(cnv, "ko_KR", display_name, capacity, &display_name_len);
	if(I18N_ERROR_BUFFER_OVERFLOW == ret) {
		display_name = (i18n_uchar *)malloc((display_name_len + 1) * sizeof(i18n_uchar));
		ret = i18n_ucnv_get_display_name(cnv, "ko_KR", display_name, display_name_len + 1, &display_name_len);
		assert_eq(ret, I18N_ERROR_NONE);

		free(display_name);
		display_name = NULL;
	}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_display_name_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_display_name and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_display_name_n1(void)
{
	ret = i18n_ucnv_create("ibm-949", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar *display_name = 0;
	int32_t capacity = 0;
	int32_t display_name_len = 0;
	ret = i18n_ucnv_get_display_name(cnv, "ko_KR", display_name, capacity, &display_name_len);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_display_name_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_display_name and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_display_name_n2(void)
{
	i18n_uchar *display_name = 0;
	int32_t capacity = 0;
	int32_t display_name_len = 0;

	ret = i18n_ucnv_get_display_name(NULL, "ko_KR", display_name, capacity, &display_name_len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_display_name_n3
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_display_name and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_display_name_n3(void)
{
	ret = i18n_ucnv_create("ibm-949", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar *display_name = 0;
	int32_t display_name_len = 0;

	ret = i18n_ucnv_get_display_name(cnv, "ko_KR", display_name, -1, &display_name_len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_display_name_n4
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_display_name and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_display_name_n4(void)
{
	ret = i18n_ucnv_create("ibm-949", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t display_name_len = 0;

	ret = i18n_ucnv_get_display_name(cnv, "ko_KR", NULL, 1, &display_name_len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_name_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_name and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_name_p(void)
{
	static const char *const names[] = {
		"Unicode",					"UTF-16",
		"UnicodeBigUnmarked",		"UTF-16BE",
		"UnicodeBig",				"UTF-16BE,version=1",
		"UnicodeLittleUnmarked",	"UTF-16LE",
		"UnicodeLittle",			"UTF-16LE,version=1",
		"x-UTF-16LE-BOM",			"UTF-16LE,version=1"
	};

	for(int i = 0; i < I18N_UPRV_LENGTHOF(names); i += 2) {
		ret = i18n_ucnv_create(names[i], &cnv);
		assert_eq(ret, I18N_ERROR_NONE);

		const char *name;
		ret = i18n_ucnv_get_name(cnv, &name);
		assert_eq(ret, I18N_ERROR_NONE);
		assert_eq(strcmp(name, names[i+1]), 0);
	}
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_name_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_name and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_name_n(void)
{
	const char *name;
	ret = i18n_ucnv_get_name(NULL, &name);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_ccsid_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_ccsid and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_ccsid_p(void)
{
	int32_t ccsids[]={ 37, 850, 943, 949, 950, 1047, 1252, 1392, 33722 };

	for(int i = 0; i < I18N_UPRV_LENGTHOF(ccsids); ++i) {
		ret = i18n_ucnv_create_ccsid(ccsids[i], I18N_UCNV_IBM, &cnv);
		assert_eq(ret, I18N_ERROR_NONE);

		int32_t ccsid = 0;
		ret = i18n_ucnv_get_ccsid(cnv, &ccsid);
		assert_eq(ret, I18N_ERROR_NONE);
		assert_eq(ccsid, ccsids[i]);
	}
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_ccsid_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_ccsid and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_ccsid_n(void)
{
	int32_t ccsid = 0;
	ret = i18n_ucnv_get_ccsid(NULL, &ccsid);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_platform_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_platform and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_platform_p(void)
{
	ret = i18n_ucnv_create("utf-8", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ucnv_platform_e platform;
	ret = i18n_ucnv_get_platform(cnv, &platform);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(platform, I18N_UCNV_IBM);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_platform_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_platform and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_platform_n(void)
{
	i18n_ucnv_platform_e platform;
	ret = i18n_ucnv_get_platform(NULL, &platform);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_type_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_type and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_type_p(void)
{
	ret = i18n_ucnv_create("utf-8", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ucnv_type_e type;
	ret = i18n_ucnv_get_type(cnv, &type);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(type, I18N_UCNV_UTF8);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_type_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_type and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_type_n(void)
{
	i18n_ucnv_type_e type;
	ret = i18n_ucnv_get_type(NULL, &type);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_starters_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_starters and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_starters_p(void)
{
	ret = i18n_ucnv_create("ksc", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ubool starters[256];
	ret = i18n_ucnv_get_starters(cnv, starters);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_starters_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_starters and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_starters_n(void)
{
	i18n_ubool starters[256];
	ret = i18n_ucnv_get_starters(NULL, starters);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_unicode_set_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_unicode_set and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_unicode_set_p(void)
{
	i18n_uset_h set;
	ret = i18n_uset_create(1, 0, &set);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_create("ksc", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_get_unicode_set(cnv, set, I18N_UCNV_ROUNDTRIP_SET);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_unicode_set_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_unicode_set and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_unicode_set_n1(void)
{
	i18n_uset_h set;
	ret = i18n_uset_create(1, 0, &set);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_create("ksc", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_get_unicode_set(NULL, set, I18N_UCNV_ROUNDTRIP_SET);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_unicode_set_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_unicode_set and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_unicode_set_n2(void)
{
	i18n_uset_h set;
	ret = i18n_uset_create(1, 0, &set);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_create("ksc", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_get_unicode_set(cnv, NULL, I18N_UCNV_ROUNDTRIP_SET);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_unicode_set_n3
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_unicode_set and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_unicode_set_n3(void)
{
	i18n_uset_h set;
	ret = i18n_uset_create(1, 0, &set);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_create("ksc", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_get_unicode_set(cnv, set, (i18n_ucnv_unicode_set_e)-1);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_unicode_set_n4
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_unicode_set and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_unicode_set_n4(void)
{
	i18n_uset_h set;
	ret = i18n_uset_create(1, 0, &set);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_create("ksc", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_get_unicode_set(cnv, set, (i18n_ucnv_unicode_set_e)2);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_unicode_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_unicode and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_unicode_p(void)
{
	char char_buffer[2] = {1, 1};
	i18n_uchar uchar_as_char_buffer[2] = {2, 2};
	char *chars_ptr = char_buffer;
	i18n_uchar *uchars_ptr = (i18n_uchar *)uchar_as_char_buffer;
	i18n_uchar *uchars_bad_ptr = (i18n_uchar *)(uchar_as_char_buffer + 1);

	ret = i18n_ucnv_create("UTF-8", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_from_unicode(cnv, &chars_ptr, chars_ptr, (const i18n_uchar **)&uchars_ptr, uchars_ptr, NULL, true);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_unicode_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_unicode and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_unicode_n1(void)
{
	char char_buffer[2] = {1, 1};
	i18n_uchar uchar_as_char_buffer[2] = {2, 2};
	char *chars_ptr = char_buffer;
	i18n_uchar *uchars_ptr = (i18n_uchar *)uchar_as_char_buffer;
	i18n_uchar *uchars_bad_ptr = (i18n_uchar *)(uchar_as_char_buffer + 1);

	ret = i18n_ucnv_create("UTF-8", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_from_unicode(cnv, &chars_ptr, chars_ptr, (const i18n_uchar **)&uchars_ptr, uchars_bad_ptr, NULL, true);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_unicode_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_unicode and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_unicode_n2(void)
{
	char char_buffer[2] = {1, 1};
	i18n_uchar uchar_as_char_buffer[2] = {2, 2};
	char *chars_ptr = char_buffer;
	i18n_uchar *uchars_ptr = (i18n_uchar *)uchar_as_char_buffer;
	i18n_uchar *uchars_bad_ptr = (i18n_uchar *)(uchar_as_char_buffer + 1);

	ret = i18n_ucnv_create("UTF-8", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_from_unicode(cnv, &chars_ptr, chars_ptr, (const i18n_uchar **)&uchars_bad_ptr, uchars_ptr, NULL, true);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_unicode_n3
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_unicode and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_unicode_n3(void)
{
	char char_buffer[2] = {1, 1};
	i18n_uchar uchar_as_char_buffer[2] = {2, 2};
	char *chars_ptr = char_buffer;
	i18n_uchar *uchars_ptr = (i18n_uchar *)uchar_as_char_buffer;
	i18n_uchar *uchars_bad_ptr = (i18n_uchar *)(uchar_as_char_buffer + 1);

	ret = i18n_ucnv_create("UTF-8", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_from_unicode(NULL, &chars_ptr, chars_ptr, (const i18n_uchar **)&uchars_ptr, uchars_ptr, NULL, true);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_unicode_n4
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_unicode and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_unicode_n4(void)
{
	char char_buffer[2] = {1, 1};
	i18n_uchar uchar_as_char_buffer[2] = {2, 2};
	char *chars_ptr = char_buffer;
	i18n_uchar *uchars_ptr = (i18n_uchar *)uchar_as_char_buffer;
	i18n_uchar *uchars_bad_ptr = (i18n_uchar *)(uchar_as_char_buffer + 1);

	ret = i18n_ucnv_create("UTF-8", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_from_unicode(cnv, NULL, chars_ptr, (const i18n_uchar **)&uchars_ptr, uchars_ptr, NULL, true);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_unicode_n5
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_unicode and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_unicode_n5(void)
{
	char char_buffer[2] = {1, 1};
	i18n_uchar uchar_as_char_buffer[2] = {2, 2};
	char *chars_ptr = char_buffer;
	i18n_uchar *uchars_ptr = (i18n_uchar *)uchar_as_char_buffer;
	i18n_uchar *uchars_bad_ptr = (i18n_uchar *)(uchar_as_char_buffer + 1);

	ret = i18n_ucnv_create("UTF-8", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_from_unicode(cnv, &chars_ptr, chars_ptr, NULL, uchars_ptr, NULL, true);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_unicode_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_unicode and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_unicode_p(void)
{
	char char_buffer[2] = {1, 1};
	i18n_uchar uchar_as_char_buffer[2] = {2, 2};
	char *chars_ptr = char_buffer;
	i18n_uchar *uchars_ptr = (i18n_uchar *)uchar_as_char_buffer;
	i18n_uchar *uchars_bad_ptr = (i18n_uchar *)(uchar_as_char_buffer + 1);

	ret = i18n_ucnv_create("UTF-8", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_to_unicode(cnv, &uchars_ptr, uchars_ptr, (const char **)&chars_ptr, chars_ptr, NULL, true);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_unicode_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_unicode and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_unicode_n1(void)
{
	char char_buffer[2] = {1, 1};
	i18n_uchar uchar_as_char_buffer[2] = {2, 2};
	char *chars_ptr = char_buffer;
	i18n_uchar *uchars_ptr = (i18n_uchar *)uchar_as_char_buffer;
	i18n_uchar *uchars_bad_ptr = (i18n_uchar *)(uchar_as_char_buffer + 1);

	ret = i18n_ucnv_create("UTF-8", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_to_unicode(cnv, &uchars_bad_ptr, uchars_ptr, (const char **)&chars_ptr, chars_ptr, NULL, true);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_unicode_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_unicode and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_unicode_n2(void)
{
	char char_buffer[2] = {1, 1};
	i18n_uchar uchar_as_char_buffer[2] = {2, 2};
	char *chars_ptr = char_buffer;
	i18n_uchar *uchars_ptr = (i18n_uchar *)uchar_as_char_buffer;
	i18n_uchar *uchars_bad_ptr = (i18n_uchar *)(uchar_as_char_buffer + 1);

	ret = i18n_ucnv_create("UTF-8", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_to_unicode(NULL, &uchars_ptr, uchars_ptr, (const char **)&chars_ptr, chars_ptr, NULL, true);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_unicode_n3
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_unicode and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_unicode_n3(void)
{
	char char_buffer[2] = {1, 1};
	i18n_uchar uchar_as_char_buffer[2] = {2, 2};
	char *chars_ptr = char_buffer;
	i18n_uchar *uchars_ptr = (i18n_uchar *)uchar_as_char_buffer;
	i18n_uchar *uchars_bad_ptr = (i18n_uchar *)(uchar_as_char_buffer + 1);

	ret = i18n_ucnv_create("UTF-8", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_to_unicode(cnv, NULL, uchars_ptr, (const char **)&chars_ptr, chars_ptr, NULL, true);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_unicode_n4
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_unicode and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_unicode_n4(void)
{
	char char_buffer[2] = {1, 1};
	i18n_uchar uchar_as_char_buffer[2] = {2, 2};
	char *chars_ptr = char_buffer;
	i18n_uchar *uchars_ptr = (i18n_uchar *)uchar_as_char_buffer;
	i18n_uchar *uchars_bad_ptr = (i18n_uchar *)(uchar_as_char_buffer + 1);

	ret = i18n_ucnv_create("UTF-8", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_to_unicode(cnv, &uchars_ptr, uchars_ptr, NULL, chars_ptr, NULL, true);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_uchars_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_uchars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_uchars_p(void)
{
	static const i18n_uchar surrogate[1] = {0xd900};
	char buffer[16];
	int32_t len;

	ret = i18n_ucnv_create("UTF-16", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_from_uchars(cnv, buffer, (int32_t)sizeof(buffer), surrogate, 1, &len);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(len, 4);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_uchars_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_uchars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_uchars_n1(void)
{
	static const i18n_uchar surrogate[1] = {0xd900};
	char buffer[16];
	int32_t len = 0;

	ret = i18n_ucnv_create("UTF-16", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_from_uchars(NULL, buffer, (int32_t)sizeof(buffer), surrogate, 1, &len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_uchars_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_uchars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_uchars_n2(void)
{
	static const i18n_uchar surrogate[1] = {0xd900};
	char buffer[16];
	int32_t len;

	ret = i18n_ucnv_create("UTF-16", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_from_uchars(cnv, buffer, 0, surrogate, -1, &len);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

	return 0;
}


/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_uchars_n3
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_uchars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_uchars_n3(void)
{
	static const i18n_uchar surrogate[1] = {0xd900};
	char buffer[16];
	int32_t len;

	ret = i18n_ucnv_create("UTF-16", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_from_uchars(cnv, buffer, -1, surrogate, 1, &len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_uchars_n4
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_uchars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_uchars_n4(void)
{
	static const i18n_uchar surrogate[1] = {0xd900};
	char buffer[16];
	int32_t len;

	ret = i18n_ucnv_create("UTF-16", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_from_uchars(cnv, buffer, (int32_t)sizeof(buffer), surrogate, -2, &len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_uchars_n5
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_uchars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_uchars_n5(void)
{
	static const i18n_uchar surrogate[1] = {0xd900};
	char buffer[16];
	int32_t len;

	ret = i18n_ucnv_create("UTF-16", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_from_uchars(cnv, NULL, (int32_t)sizeof(buffer), surrogate, 1, &len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_uchars_n6
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_uchars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_uchars_n6(void)
{
	static const i18n_uchar surrogate[1] = {0xd900};
	char buffer[16];
	int32_t len;

	ret = i18n_ucnv_create("UTF-16", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_from_uchars(cnv, buffer, (int32_t)sizeof(buffer), NULL, 1, &len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_uchars_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_uchars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_uchars_p(void)
{
	static const char target[] = {
		/* "\\usr\\local\\share\\data\\icutest.txt" */
		0x5c, 0x75, 0x73, 0x72,
		0x5c, 0x6c, 0x6f, 0x63, 0x61, 0x6c,
		0x5c, 0x73, 0x68, 0x61, 0x72, 0x65,
		0x5c, 0x64, 0x61, 0x74, 0x61,
		0x5c, 0x69, 0x63, 0x75, 0x74, 0x65, 0x73, 0x74, 0x2e, 0x74, 0x78, 0x74,
		0
	};

	i18n_uchar result[200];
	int32_t len;

	ret = i18n_ucnv_create("ibm-943", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_to_uchars(cnv, result, I18N_UPRV_LENGTHOF(result), target, (int32_t)strlen(target), &len);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_uchars_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_uchars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_uchars_n1(void)
{
	static const char target[] = {
		/* "\\usr\\local\\share\\data\\icutest.txt" */
		0x5c, 0x75, 0x73, 0x72,
		0x5c, 0x6c, 0x6f, 0x63, 0x61, 0x6c,
		0x5c, 0x73, 0x68, 0x61, 0x72, 0x65,
		0x5c, 0x64, 0x61, 0x74, 0x61,
		0x5c, 0x69, 0x63, 0x75, 0x74, 0x65, 0x73, 0x74, 0x2e, 0x74, 0x78, 0x74,
		0
	};

	i18n_uchar result[200];
	int32_t len;

	ret = i18n_ucnv_create("ibm-943", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_to_uchars(cnv, result, -1, target, (int32_t)strlen(target), &len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_uchars_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_uchars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_uchars_n2(void)
{
	static const char target[] = {
		/* "\\usr\\local\\share\\data\\icutest.txt" */
		0x5c, 0x75, 0x73, 0x72,
		0x5c, 0x6c, 0x6f, 0x63, 0x61, 0x6c,
		0x5c, 0x73, 0x68, 0x61, 0x72, 0x65,
		0x5c, 0x64, 0x61, 0x74, 0x61,
		0x5c, 0x69, 0x63, 0x75, 0x74, 0x65, 0x73, 0x74, 0x2e, 0x74, 0x78, 0x74,
		0
	};

	i18n_uchar result[200];
	int32_t len;

	ret = i18n_ucnv_create("ibm-943", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_to_uchars(cnv, result, 0, target, 0, &len);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_uchars_n3
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_uchars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_uchars_n3(void)
{
	static const char target[] = {
		/* "\\usr\\local\\share\\data\\icutest.txt" */
		0x5c, 0x75, 0x73, 0x72,
		0x5c, 0x6c, 0x6f, 0x63, 0x61, 0x6c,
		0x5c, 0x73, 0x68, 0x61, 0x72, 0x65,
		0x5c, 0x64, 0x61, 0x74, 0x61,
		0x5c, 0x69, 0x63, 0x75, 0x74, 0x65, 0x73, 0x74, 0x2e, 0x74, 0x78, 0x74,
		0
	};

	i18n_uchar result[200];
	int32_t len;

	ret = i18n_ucnv_create("ibm-943", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_to_uchars(cnv, NULL, I18N_UPRV_LENGTHOF(result), target, (int32_t)strlen(target), &len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_uchars_n4
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_uchars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_uchars_n4(void)
{
	static const char target[] = {
		/* "\\usr\\local\\share\\data\\icutest.txt" */
		0x5c, 0x75, 0x73, 0x72,
		0x5c, 0x6c, 0x6f, 0x63, 0x61, 0x6c,
		0x5c, 0x73, 0x68, 0x61, 0x72, 0x65,
		0x5c, 0x64, 0x61, 0x74, 0x61,
		0x5c, 0x69, 0x63, 0x75, 0x74, 0x65, 0x73, 0x74, 0x2e, 0x74, 0x78, 0x74,
		0
	};

	i18n_uchar result[200];
	int32_t len;

	ret = i18n_ucnv_create("ibm-943", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_to_uchars(NULL, result, I18N_UPRV_LENGTHOF(result), target, (int32_t)strlen(target), &len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_uchars_n5
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_uchars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_uchars_n5(void)
{
	static const char target[] = {
		/* "\\usr\\local\\share\\data\\icutest.txt" */
		0x5c, 0x75, 0x73, 0x72,
		0x5c, 0x6c, 0x6f, 0x63, 0x61, 0x6c,
		0x5c, 0x73, 0x68, 0x61, 0x72, 0x65,
		0x5c, 0x64, 0x61, 0x74, 0x61,
		0x5c, 0x69, 0x63, 0x75, 0x74, 0x65, 0x73, 0x74, 0x2e, 0x74, 0x78, 0x74,
		0
	};

	i18n_uchar result[200];
	int32_t len;

	ret = i18n_ucnv_create("ibm-943", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_to_uchars(cnv, result, -1, target, (int32_t)strlen(target), &len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_uchars_n6
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_uchars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_uchars_n6(void)
{
	static const char target[] = {
		/* "\\usr\\local\\share\\data\\icutest.txt" */
		0x5c, 0x75, 0x73, 0x72,
		0x5c, 0x6c, 0x6f, 0x63, 0x61, 0x6c,
		0x5c, 0x73, 0x68, 0x61, 0x72, 0x65,
		0x5c, 0x64, 0x61, 0x74, 0x61,
		0x5c, 0x69, 0x63, 0x75, 0x74, 0x65, 0x73, 0x74, 0x2e, 0x74, 0x78, 0x74,
		0
	};

	i18n_uchar result[200];
	int32_t len;

	ret = i18n_ucnv_create("ibm-943", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_to_uchars(cnv, result, I18N_UPRV_LENGTHOF(result), target, -2, &len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_uchars_n7
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_uchars and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_uchars_n7(void)
{
	static const char target[] = {
		/* "\\usr\\local\\share\\data\\icutest.txt" */
		0x5c, 0x75, 0x73, 0x72,
		0x5c, 0x6c, 0x6f, 0x63, 0x61, 0x6c,
		0x5c, 0x73, 0x68, 0x61, 0x72, 0x65,
		0x5c, 0x64, 0x61, 0x74, 0x61,
		0x5c, 0x69, 0x63, 0x75, 0x74, 0x65, 0x73, 0x74, 0x2e, 0x74, 0x78, 0x74,
		0
	};

	i18n_uchar result[200];
	int32_t len;

	ret = i18n_ucnv_create("ibm-943", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_to_uchars(cnv, result, I18N_UPRV_LENGTHOF(result), NULL, (int32_t)strlen(target), &len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_next_uchar_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_next_uchar and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_next_uchar_p(void)
{
	const char source_data[] = { (char)0xa2, (char)0xae, (char)0xa2 };
	const char *source = source_data;
	const char *source_limit = source_data + sizeof(source_data);
	i18n_uchar32 result1, result2, result3;

	ret = i18n_ucnv_create("ibm-1363", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_get_next_uchar(cnv, &source, source_limit, &result1);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(result1, 0xa1);

	ret = i18n_ucnv_get_next_uchar(cnv, &source, source_limit, &result2);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(result2, 0x1a);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_next_uchar_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_next_uchar and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_next_uchar_n1(void)
{
	const char source_data[] = { (char)0xa2, (char)0xae, (char)0xa2 };
	const char *source = source_data;
	const char *source_limit = source_data + sizeof(source_data);
	i18n_uchar32 result1, result2, result3;

	ret = i18n_ucnv_create("ibm-1363", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_get_next_uchar(NULL, &source, source_limit, &result3);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_next_uchar_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_next_uchar and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_next_uchar_n2(void)
{
	const char source_data[] = { (char)0xa2, (char)0xae, (char)0xa2 };
	const char *source = source_data;
	const char *source_limit = source_data + sizeof(source_data);
	i18n_uchar32 result1, result2, result3;

	ret = i18n_ucnv_create("ibm-1363", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_get_next_uchar(cnv, NULL, source_limit, &result3);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_convert_ex_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_convert_ex and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_convert_ex_p(void)
{
	i18n_ucnv_h cnv1, cnv2;
	char target_buffer[100], src_buffer[100];
	char *target = target_buffer;
	const char *src = src_buffer;

	ret = i18n_ucnv_create("UTF-8", &cnv1);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_create("Shift-JIS", &cnv2);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_convert_ex(cnv2, cnv1, &target, target_buffer+sizeof(target_buffer), &src, NULL, NULL, NULL, NULL, NULL, true, true);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_convert_ex_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_convert_ex and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_convert_ex_n1(void)
{
	i18n_ucnv_h cnv1, cnv2;
	char target_buffer[100], src_buffer[100];
	char *target = target_buffer;
	const char *src = src_buffer;

	i18n_uchar pivot_buffer[100];
	i18n_uchar *pivot_source, *pivot_target;

	ret = i18n_ucnv_create("UTF-8", &cnv1);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_create("Shift-JIS", &cnv2);
	assert_eq(ret, I18N_ERROR_NONE);

	pivot_source = pivot_target = pivot_buffer;
	ret = i18n_ucnv_convert_ex(cnv2, cnv1, &target, target_buffer+sizeof(target_buffer), &src, NULL, pivot_buffer, &pivot_source, &pivot_target, pivot_buffer, true, true);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_convert_ex_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_convert_ex and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_convert_ex_n2(void)
{
	i18n_ucnv_h cnv1, cnv2;
	char target_buffer[100], src_buffer[100];
	char *target = target_buffer;
	const char *src = src_buffer;

	i18n_uchar pivot_buffer[100];
	i18n_uchar *pivot_source, *pivot_target;

	ret = i18n_ucnv_create("UTF-8", &cnv1);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_create("Shift-JIS", &cnv2);
	assert_eq(ret, I18N_ERROR_NONE);

	pivot_source = pivot_target = pivot_buffer;
	ret = i18n_ucnv_convert_ex(cnv2, cnv1, &target, target_buffer+sizeof(target_buffer), &src, NULL, pivot_buffer, NULL, &pivot_target, pivot_buffer+1, true, true);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_convert_ex_n3
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_convert_ex and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_convert_ex_n3(void)
{
	i18n_ucnv_h cnv1, cnv2;
	char target_buffer[100], src_buffer[100];
	char *target = target_buffer;
	const char *src = src_buffer;

	i18n_uchar pivot_buffer[100];
	i18n_uchar *pivot_source, *pivot_target;

	ret = i18n_ucnv_create("UTF-8", &cnv1);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_create("Shift-JIS", &cnv2);
	assert_eq(ret, I18N_ERROR_NONE);

	pivot_source = pivot_buffer;
	ret = i18n_ucnv_convert_ex(cnv2, cnv1, &target, target_buffer+sizeof(target_buffer), NULL, NULL, pivot_buffer, &pivot_source, &pivot_target, pivot_buffer+1, true, true);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_convert_ex_n4
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_convert_ex and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_convert_ex_n4(void)
{
	i18n_ucnv_h cnv1, cnv2;
	char target_buffer[100], src_buffer[100];
	char *target = target_buffer;
	const char *src = src_buffer;

	i18n_uchar pivot_buffer[100];
	i18n_uchar *pivot_source, *pivot_target;

	ret = i18n_ucnv_create("UTF-8", &cnv1);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_create("Shift-JIS", &cnv2);
	assert_eq(ret, I18N_ERROR_NONE);

	src = src_buffer;
	pivot_source = pivot_buffer;
	ret = i18n_ucnv_convert_ex(cnv2, cnv1, &target, target_buffer+sizeof(target_buffer), &src, NULL, NULL, &pivot_source, &pivot_target, pivot_buffer+1, true, false);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_convert_ex_n5
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_convert_ex and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_convert_ex_n5(void)
{
	i18n_ucnv_h cnv1, cnv2;
	char target_buffer[100], src_buffer[100];
	char *target = target_buffer;
	const char *src = src_buffer;

	i18n_uchar pivot_buffer[100];
	i18n_uchar *pivot_source, *pivot_target;

	ret = i18n_ucnv_create("UTF-8", &cnv1);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_create("Shift-JIS", &cnv2);
	assert_eq(ret, I18N_ERROR_NONE);

	src = src_buffer;
	pivot_source = pivot_buffer;
	ret = i18n_ucnv_convert_ex(cnv2, cnv1, NULL, target_buffer+sizeof(target_buffer), &src, NULL, pivot_buffer, &pivot_source, &pivot_target, pivot_buffer, true, true);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_convert_ex_n6
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_convert_ex and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_convert_ex_n6(void)
{
	i18n_ucnv_h cnv1, cnv2;
	char target_buffer[100], src_buffer[100];
	char *target = target_buffer;
	const char *src = src_buffer;

	i18n_uchar pivot_buffer[100];
	i18n_uchar *pivot_source, *pivot_target;

	ret = i18n_ucnv_create("UTF-8", &cnv1);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_create("Shift-JIS", &cnv2);
	assert_eq(ret, I18N_ERROR_NONE);

	src = src_buffer;
	pivot_source = pivot_buffer;
	ret = i18n_ucnv_convert_ex(NULL, cnv1, &target, target_buffer+sizeof(target_buffer), &src, NULL, pivot_buffer, &pivot_source, &pivot_target, pivot_buffer, true, true);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_convert_ex_n7
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_convert_ex and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_convert_ex_n7(void)
{
	i18n_ucnv_h cnv1, cnv2;
	char target_buffer[100], src_buffer[100];
	char *target = target_buffer;
	const char *src = src_buffer;

	i18n_uchar pivot_buffer[100];
	i18n_uchar *pivot_source, *pivot_target;

	ret = i18n_ucnv_create("UTF-8", &cnv1);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_create("Shift-JIS", &cnv2);
	assert_eq(ret, I18N_ERROR_NONE);

	src = src_buffer;
	pivot_source = pivot_buffer;
	ret = i18n_ucnv_convert_ex(cnv2, NULL, &target, target_buffer+sizeof(target_buffer), &src, NULL, pivot_buffer, &pivot_source, &pivot_target, pivot_buffer, true, true);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_convert_ex_n8
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_convert_ex and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_convert_ex_n8(void)
{
	i18n_ucnv_h cnv1, cnv2;
	char target_buffer[100], src_buffer[100];
	char *target = target_buffer;
	const char *src = src_buffer;

	i18n_uchar pivot_buffer[100];
	i18n_uchar *pivot_source, *pivot_target;

	ret = i18n_ucnv_create("UTF-8", &cnv1);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_create("Shift-JIS", &cnv2);
	assert_eq(ret, I18N_ERROR_NONE);

	src = src_buffer;
	pivot_source = pivot_buffer;
	ret = i18n_ucnv_convert_ex(cnv2, cnv1, &target, NULL, &src, NULL, pivot_buffer, &pivot_source, &pivot_target, pivot_buffer, true, true);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_convert_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_convert and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_convert_p(void)
{
	int32_t target_limit = 0, source_limit = 0, target_capacity = 0;

	const uint8_t source[]={ 0x00, 0x04, 0x05, 0x06, 0xa2, 0xb4, 0x00};
	const uint8_t expected_target[]={ 0x00, 0x37, 0x2d, 0x2e, 0x0e, 0x49, 0x62, 0x0f, 0x00};
	char *target=0;
	source_limit=I18N_UPRV_LENGTHOF(source);

	ret = i18n_ucnv_convert("ibm-1364", "ibm-1363", NULL, target_limit, (const char*)source, source_limit, &target_capacity);
	if(ret == I18N_ERROR_BUFFER_OVERFLOW) {
		target_limit = target_capacity + 1;
		target = (char *)malloc(sizeof(char) *target_limit);
		ret = i18n_ucnv_convert("ibm-1364", "ibm-1363", target, target_limit, (const char*)source, source_limit, &target_capacity);
	}
	assert_eq(ret, I18N_ERROR_NONE);

	for(int i = 0; i < target_capacity; ++i)
		assert_eq(target[i], expected_target[i]);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_convert_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_convert and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_convert_n1(void)
{
	int32_t target_limit = 0, source_limit = 0, target_capacity = 0;

	const uint8_t source[]={ 0x00, 0x04, 0x05, 0x06, 0xa2, 0xb4, 0x00};
	const uint8_t expected_target[]={ 0x00, 0x37, 0x2d, 0x2e, 0x0e, 0x49, 0x62, 0x0f, 0x00};
	char *target=0;
	source_limit=I18N_UPRV_LENGTHOF(source);

	ret = i18n_ucnv_convert("ibm-1364", "ibm-1363", NULL, target_limit, (const char*)source, source_limit, &target_capacity);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_convert_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_convert and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_convert_n2(void)
{
	int32_t target_limit = 0, source_limit = 0, target_capacity = 0;

	const uint8_t source[]={ 0x00, 0x04, 0x05, 0x06, 0xa2, 0xb4, 0x00};
	const uint8_t expected_target[]={ 0x00, 0x37, 0x2d, 0x2e, 0x0e, 0x49, 0x62, 0x0f, 0x00};
	char *target=0;
	source_limit=I18N_UPRV_LENGTHOF(source);

	target_limit = target_capacity + 1;
	target = (char *)malloc(sizeof(char) * target_limit);

	ret = i18n_ucnv_convert("ibm-1364", "ibm-1363", target, target_limit, NULL, source_limit, &target_capacity);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_convert_n3
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_convert and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_convert_n3(void)
{
	int32_t target_limit = 0, source_limit = 0, target_capacity = 0;

	const uint8_t source[]={ 0x00, 0x04, 0x05, 0x06, 0xa2, 0xb4, 0x00};
	const uint8_t expected_target[]={ 0x00, 0x37, 0x2d, 0x2e, 0x0e, 0x49, 0x62, 0x0f, 0x00};
	char *target=0;
	source_limit=I18N_UPRV_LENGTHOF(source);

	target_limit = target_capacity + 1;
	target = (char *)malloc(sizeof(char) * target_limit);

	ret = i18n_ucnv_convert("ibm-1364", "ibm-1363", target, target_limit, (const char*)source, -2, &target_capacity);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_convert_n4
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_convert and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_convert_n4(void)
{
	int32_t source_limit = 0, target_capacity = 0;

	const uint8_t source[]={ 0x00, 0x04, 0x05, 0x06, 0xa2, 0xb4, 0x00};
	const uint8_t expected_target[]={ 0x00, 0x37, 0x2d, 0x2e, 0x0e, 0x49, 0x62, 0x0f, 0x00};
	char *target=0;
	source_limit=I18N_UPRV_LENGTHOF(source);

	ret = i18n_ucnv_convert("ibm-1364", "ibm-1363", target, -1, (const char*)source, source_limit, &target_capacity);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_convert_n5
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_convert and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_convert_n5(void)
{
	int32_t target_limit = 0, source_limit = 0, target_capacity = 0;

	const uint8_t source[]={ 0x00, 0x04, 0x05, 0x06, 0xa2, 0xb4, 0x00};
	const uint8_t expected_target[]={ 0x00, 0x37, 0x2d, 0x2e, 0x0e, 0x49, 0x62, 0x0f, 0x00};
	source_limit=I18N_UPRV_LENGTHOF(source);

	target_limit = target_capacity + 1;
	ret = i18n_ucnv_convert("ibm-1364", "ibm-1363", NULL, target_limit, (const char*)source, source_limit, &target_capacity);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_algorithmic_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_algorithmic and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_algorithmic_p(void)
{
	static const uint8_t
		utf8[]={
			/* 4e00 		  30a1				ff61			  0410 */
			0xe4, 0xb8, 0x80, 0xe3, 0x82, 0xa1, 0xef, 0xbd, 0xa1, 0xd0, 0x90
		},
		shiftJIS[]={
			0x88, 0xea, 0x83, 0x40, 0xa1, 0x84, 0x40
		};

	int32_t length;
	char target[100];

	ret = i18n_ucnv_create("shift-JIS", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_from_algorithmic(cnv, I18N_UCNV_UTF8, target, sizeof(shiftJIS), (const char *)utf8, sizeof(utf8), &length);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(length, sizeof(shiftJIS));

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_algorithmic_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_algorithmic and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_algorithmic_n1(void)
{
	static const uint8_t
		utf8[]={
			/* 4e00 		  30a1				ff61			  0410 */
			0xe4, 0xb8, 0x80, 0xe3, 0x82, 0xa1, 0xef, 0xbd, 0xa1, 0xd0, 0x90
		},
		shiftJIS[]={
			0x88, 0xea, 0x83, 0x40, 0xa1, 0x84, 0x40
		};

	int32_t length;
	char target[100];

	memset(target, 0x55, sizeof(target));
	ret = i18n_ucnv_from_algorithmic(NULL, I18N_UCNV_UTF8, target, sizeof(shiftJIS), (const char *)utf8, sizeof(utf8), &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_algorithmic_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_algorithmic and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_algorithmic_n2(void)
{
	static const uint8_t
		utf8[]={
			/* 4e00 		  30a1				ff61			  0410 */
			0xe4, 0xb8, 0x80, 0xe3, 0x82, 0xa1, 0xef, 0xbd, 0xa1, 0xd0, 0x90
		},
		shiftJIS[]={
			0x88, 0xea, 0x83, 0x40, 0xa1, 0x84, 0x40
		};

	int32_t length;
	char target[100];

	ret = i18n_ucnv_create("shift-JIS", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	memset(target, 0x55, sizeof(target));
	ret = i18n_ucnv_from_algorithmic(cnv, (i18n_ucnv_type_e)99, target, sizeof(shiftJIS), (const char *)utf8, sizeof(utf8), &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_algorithmic_n3
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_algorithmic and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_algorithmic_n3(void)
{
	static const uint8_t
		utf8[]={
			/* 4e00 		  30a1				ff61			  0410 */
			0xe4, 0xb8, 0x80, 0xe3, 0x82, 0xa1, 0xef, 0xbd, 0xa1, 0xd0, 0x90
		},
		shiftJIS[]={
			0x88, 0xea, 0x83, 0x40, 0xa1, 0x84, 0x40
		};

	int32_t length;

	ret = i18n_ucnv_create("shift-JIS", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_from_algorithmic(cnv, I18N_UCNV_UTF8, NULL, sizeof(shiftJIS), (const char *)utf8, sizeof(utf8), &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_algorithmic_n4
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_algorithmic and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_algorithmic_n4(void)
{
	static const uint8_t
		utf8[]={
			/* 4e00 		  30a1				ff61			  0410 */
			0xe4, 0xb8, 0x80, 0xe3, 0x82, 0xa1, 0xef, 0xbd, 0xa1, 0xd0, 0x90
		};

	int32_t length;
	char target[100];

	ret = i18n_ucnv_create("shift-JIS", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	memset(target, 0x55, sizeof(target));
	ret = i18n_ucnv_from_algorithmic(cnv, I18N_UCNV_UTF8, target, -1, (const char *)utf8, sizeof(utf8), &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_algorithmic_n5
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_algorithmic and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_algorithmic_n5(void)
{
	static const uint8_t
		utf8[]={
			/* 4e00 		  30a1				ff61			  0410 */
			0xe4, 0xb8, 0x80, 0xe3, 0x82, 0xa1, 0xef, 0xbd, 0xa1, 0xd0, 0x90
		},
		shiftJIS[]={
			0x88, 0xea, 0x83, 0x40, 0xa1, 0x84, 0x40
		};

	int32_t length;
	char target[100];

	ret = i18n_ucnv_create("shift-JIS", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	memset(target, 0x55, sizeof(target));
	ret = i18n_ucnv_from_algorithmic(cnv, I18N_UCNV_UTF8, target, sizeof(shiftJIS), NULL, sizeof(utf8), &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_algorithmic_n6
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_algorithmic and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_algorithmic_n6(void)
{
	static const uint8_t
		utf8[]={
			/* 4e00 		  30a1				ff61			  0410 */
			0xe4, 0xb8, 0x80, 0xe3, 0x82, 0xa1, 0xef, 0xbd, 0xa1, 0xd0, 0x90
		},
		shiftJIS[]={
			0x88, 0xea, 0x83, 0x40, 0xa1, 0x84, 0x40
		};

	int32_t length;
	char target[100];

	ret = i18n_ucnv_create("shift-JIS", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	memset(target, 0x55, sizeof(target));
	ret = i18n_ucnv_from_algorithmic(cnv, I18N_UCNV_UTF8, target, sizeof(shiftJIS), (const char *)utf8, -2, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_algorithmic_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_algorithmic and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_algorithmic_p(void)
{
	static const uint8_t
		utf8[]={
			/* 4e00 		  30a1				ff61			  0410 */
			0xe4, 0xb8, 0x80, 0xe3, 0x82, 0xa1, 0xef, 0xbd, 0xa1, 0xd0, 0x90
		},
		shiftJIS[]={
			0x88, 0xea, 0x83, 0x40, 0xa1, 0x84, 0x40
		};

	int32_t length;
	char target[100], shiftJIS_nul[100];

	memcpy(shiftJIS_nul, shiftJIS, sizeof(shiftJIS));
	shiftJIS_nul[sizeof(shiftJIS)] = 0;

	ret = i18n_ucnv_create("shift-JIS", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	memset(target, 0x55, sizeof(target));
	ret = i18n_ucnv_to_algorithmic(I18N_UCNV_UTF8, cnv, target, sizeof(target), shiftJIS_nul, -1, &length);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(length, sizeof(utf8));
	return 0;
}


/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_algorithmic_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_algorithmic and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_algorithmic_n1(void)
{
	static const uint8_t
		shiftJIS[]={
			0x88, 0xea, 0x83, 0x40, 0xa1, 0x84, 0x40
		};

	int32_t length;
	char target[100], shiftJIS_nul[100];

	memcpy(shiftJIS_nul, shiftJIS, sizeof(shiftJIS));
	shiftJIS_nul[sizeof(shiftJIS)] = 0;

	memset(target, 0x55, sizeof(target));
	ret = i18n_ucnv_to_algorithmic(I18N_UCNV_UTF8, NULL, target, sizeof(target), shiftJIS_nul, -1, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_algorithmic_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_algorithmic and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_algorithmic_n2(void)
{
	static const uint8_t
		shiftJIS[]={
			0x88, 0xea, 0x83, 0x40, 0xa1, 0x84, 0x40
		};

	int32_t length;
	char target[100], shiftJIS_nul[100];

	memcpy(shiftJIS_nul, shiftJIS, sizeof(shiftJIS));
	shiftJIS_nul[sizeof(shiftJIS)] = 0;

	ret = i18n_ucnv_create("shift-JIS", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	memset(target, 0x55, sizeof(target));
	ret = i18n_ucnv_to_algorithmic(I18N_UCNV_UTF8, cnv, NULL, sizeof(target), shiftJIS_nul, -1, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_algorithmic_n3
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_algorithmic and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_algorithmic_n3(void)
{
	static const uint8_t
		shiftJIS[]={
			0x88, 0xea, 0x83, 0x40, 0xa1, 0x84, 0x40
		};

	int32_t length;
	char target[100], shiftJIS_nul[100];

	memcpy(shiftJIS_nul, shiftJIS, sizeof(shiftJIS));
	shiftJIS_nul[sizeof(shiftJIS)] = 0;

	ret = i18n_ucnv_create("shift-JIS", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	memset(target, 0x55, sizeof(target));
	ret = i18n_ucnv_to_algorithmic(I18N_UCNV_UTF8, cnv, target, -1, shiftJIS_nul, -1, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_algorithmic_n4
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_algorithmic and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_algorithmic_n4(void)
{
	static const uint8_t
		shiftJIS[]={
			0x88, 0xea, 0x83, 0x40, 0xa1, 0x84, 0x40
		};

	int32_t length;
	char target[100];

	ret = i18n_ucnv_create("shift-JIS", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	memset(target, 0x55, sizeof(target));
	ret = i18n_ucnv_to_algorithmic(I18N_UCNV_UTF8, cnv, target, sizeof(target), NULL, -1, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_algorithmic_n5
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_algorithmic and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_algorithmic_n5(void)
{
	static const uint8_t
		shiftJIS[]={
			0x88, 0xea, 0x83, 0x40, 0xa1, 0x84, 0x40
		};

	int32_t length;
	char target[100], shiftJIS_nul[100];

	memcpy(shiftJIS_nul, shiftJIS, sizeof(shiftJIS));
	shiftJIS_nul[sizeof(shiftJIS)] = 0;

	ret = i18n_ucnv_create("shift-JIS", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	memset(target, 0x55, sizeof(target));
	ret = i18n_ucnv_to_algorithmic(I18N_UCNV_UTF8, cnv, target, sizeof(target), shiftJIS_nul, -2, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_flush_cache_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_flush_cache and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_flush_cache_p(void)
{
	i18n_ucnv_h converters[4];
	int flush_count = 0;

	i18n_ucnv_flush_cache();

	ret = i18n_ucnv_create("ibm-1047", &converters[0]);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_create("ibm-1047", &converters[1]);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_create("ibm-1047", &converters[2]);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_create("ibm-954", &converters[3]);
	assert_eq(ret, I18N_ERROR_NONE);

	flush_count = i18n_ucnv_flush_cache();
	assert_eq(flush_count, 0);

	i18n_ucnv_destroy(converters[0]);
	i18n_ucnv_destroy(converters[1]);

	flush_count = i18n_ucnv_flush_cache();
	assert_eq(flush_count, 0);

	i18n_ucnv_destroy(converters[2]);
	i18n_ucnv_destroy(converters[3]);

	flush_count = i18n_ucnv_flush_cache();
	assert_eq(flush_count, 1);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_count_available_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_count_available and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_count_available_p(void)
{
	int32_t count = 0;
	const char *result;

	count = i18n_ucnv_count_available();
	assert_neq(count, 0);

	for(int i = 0; i<count; ++i) {
		ret = i18n_ucnv_get_available_name(i, &result);
		assert_eq(ret, I18N_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_available_name_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_available_name and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_available_name_p(void)
{
	const char *result;

	ret = i18n_ucnv_get_available_name(1, &result);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_available_name_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_available_name and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_available_name_n1(void)
{
	const char *result;

	ret = i18n_ucnv_get_available_name(-1, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_available_name_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_available_name and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_available_name_n2(void)
{
	const char *result;

	ret = i18n_ucnv_get_available_name(0xffff+1, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_create_all_names_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_create_all_names and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_create_all_names_p(void)
{
	i18n_uenumeration_h enumeration;

	ret = i18n_ucnv_create_all_names(&enumeration);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_create_all_names_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_create_all_names and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_create_all_names_n(void)
{
	i18n_uenumeration_h enumeration;

	ret = i18n_ucnv_create_all_names(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_count_aliases_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_count_aliases and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_count_aliases_p(void)
{
	uint16_t number;
	ret = i18n_ucnv_count_aliases("utf-8", &number);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_count_aliases_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_count_aliases and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_count_aliases_n1(void)
{
	uint16_t number;
	ret = i18n_ucnv_count_aliases(NULL, &number);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_count_aliases_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_count_aliases and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_count_aliases_n2(void)
{
	ret = i18n_ucnv_count_aliases("utf-8", NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_alias_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_aliases and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_alias_p(void)
{
	uint16_t number;
	ret = i18n_ucnv_count_aliases("utf-8", &number);
	assert_eq(ret, I18N_ERROR_NONE);

	const char **aliases;
	aliases = (const char **)malloc(number * sizeof(const char *));
	ret = i18n_ucnv_get_aliases("utf-8", aliases);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_alias_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_alias and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_alias_n(void)
{
	const char *alias;
	ret = i18n_ucnv_get_alias(NULL, 0, &alias);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_aliases_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_alias and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_aliases_p(void)
{
	uint16_t number;
	ret = i18n_ucnv_count_aliases("utf-8", &number);
	assert_eq(ret, I18N_ERROR_NONE);

	const char **aliases;
	aliases = (const char **)malloc(number * sizeof(const char *));
	ret = i18n_ucnv_get_aliases("utf-8", aliases);
	assert_eq(ret, I18N_ERROR_NONE);

	const char *alias;
	uint16_t alias_num;
	for(alias_num = 0; alias_num < number; ++alias_num) {
		ret = i18n_ucnv_get_alias("utf-8", alias_num, &alias);
		assert_eq(ret, I18N_ERROR_NONE);
		assert_eq(strcmp(aliases[alias_num], alias), 0);
	}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_aliases_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_alias and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_aliases_n(void)
{
	const char **aliases;
	ret = i18n_ucnv_get_aliases(NULL, aliases);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_create_standard_names_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_create_standard_names and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_create_standard_names_p(void)
{
	i18n_uenumeration_h enumeration;
	ret = i18n_ucnv_create_standard_names("ASCII", "IANA", &enumeration);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_create_standard_names_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_create_standard_names and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_create_standard_names_n1(void)
{
	i18n_uenumeration_h enumeration;
	ret = i18n_ucnv_create_standard_names(NULL, "IANA", &enumeration);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_create_standard_names_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_create_standard_names and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_create_standard_names_n2(void)
{
	i18n_uenumeration_h enumeration;
	ret = i18n_ucnv_create_standard_names("ASCII", NULL, &enumeration);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_count_standards_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_count_standards and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_count_standards_p(void)
{
	uint16_t count = i18n_ucnv_count_standards();
	assert_geq(count, 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_standard_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_standard and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_standard_p(void)
{
	uint16_t count = i18n_ucnv_count_standards();
	for(int i = 0; i < count -1; ++i) {
		const char *standard;
		ret = i18n_ucnv_get_standard(i, &standard);
		assert_eq(ret, I18N_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_standard_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_standard and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_standard_n(void)
{
	const char *standard;
	ret = i18n_ucnv_get_standard(-1, &standard);
	assert_eq(ret, I18N_ERROR_INDEX_OUTOFBOUNDS);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_standard_name_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_standard_name and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_standard_name_p(void)
{
	const char *tag;
	ret =i18n_ucnv_get_standard_name("ascii", "IANA", &tag);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(strcmp(tag, "ANSI_X3.4-1968"), 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_standard_name_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_standard_name and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_standard_name_n1(void)
{
	const char *tag;
	ret =i18n_ucnv_get_standard_name(NULL, "IANA", &tag);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_standard_name_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_standard_name and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_standard_name_n2(void)
{
	const char *tag;
	ret =i18n_ucnv_get_standard_name("ascii", NULL, &tag);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_canonical_name_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_canonical_name and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_canonical_name_p(void)
{
	const char *tag;
	ret = i18n_ucnv_get_canonical_name("UTF-8", "IANA", &tag);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(strcmp(tag, "UTF-8"), 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_canonical_name_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_canonical_name and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_canonical_name_n1(void)
{
	const char *tag;
	ret = i18n_ucnv_get_canonical_name(NULL, "IANA", &tag);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_canonical_name_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_canonical_name and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_canonical_name_n2(void)
{
	const char *tag;
	ret = i18n_ucnv_get_canonical_name("UTF-8", NULL, &tag);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_get_default_name_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_get_default_name and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_get_default_name_p(void)
{
	i18n_ucnv_set_default_name("UTF-8");
	const char *name = i18n_ucnv_get_default_name();
	assert_eq(strcmp(name, "UTF-8"), 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_set_default_name_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_set_default_name and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_set_default_name_p(void)
{
	i18n_ucnv_set_default_name("UTF-8");
	const char *name = i18n_ucnv_get_default_name();
	assert_eq(strcmp(name, "UTF-8"), 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_fix_file_separator_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_fix_file_separator and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_fix_file_separator_p(void)
{
	static const char target[] = {
		/* "\\usr\\local\\share\\data\\icutest.txt" */
		0x5c, 0x75, 0x73, 0x72,
		0x5c, 0x6c, 0x6f, 0x63, 0x61, 0x6c,
		0x5c, 0x73, 0x68, 0x61, 0x72, 0x65,
		0x5c, 0x64, 0x61, 0x74, 0x61,
		0x5c, 0x69, 0x63, 0x75, 0x74, 0x65, 0x73, 0x74, 0x2e, 0x74, 0x78, 0x74,
		0
	};

	i18n_uchar result[200], ascii_result[200];
	int32_t len, ascii_len;
	i18n_ucnv_h ascii_cnv;

	ret = i18n_ucnv_create("ibm-943", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_create("LATIN-1", &ascii_cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_to_uchars(cnv, result, I18N_UPRV_LENGTHOF(result), target, (int32_t)strlen(target), &len);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_to_uchars(ascii_cnv, ascii_result, I18N_UPRV_LENGTHOF(ascii_result), target, (int32_t)strlen(target), &ascii_len);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_fix_file_separator(cnv, result, len);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(i18n_ustring_compare(result, ascii_result), 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_fix_file_separator_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_fix_file_separator and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_fix_file_separator_n1(void)
{
	static const char target[] = {
		/* "\\usr\\local\\share\\data\\icutest.txt" */
		0x5c, 0x75, 0x73, 0x72,
		0x5c, 0x6c, 0x6f, 0x63, 0x61, 0x6c,
		0x5c, 0x73, 0x68, 0x61, 0x72, 0x65,
		0x5c, 0x64, 0x61, 0x74, 0x61,
		0x5c, 0x69, 0x63, 0x75, 0x74, 0x65, 0x73, 0x74, 0x2e, 0x74, 0x78, 0x74,
		0
	};

	i18n_uchar result[200];
	int32_t len;

	ret = i18n_ucnv_create("ibm-943", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_to_uchars(cnv, result, I18N_UPRV_LENGTHOF(result), target, (int32_t)strlen(target), &len);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_fix_file_separator(NULL, result, len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_fix_file_separator_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_fix_file_separator and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_fix_file_separator_n2(void)
{
	static const char target[] = {
		/* "\\usr\\local\\share\\data\\icutest.txt" */
		0x5c, 0x75, 0x73, 0x72,
		0x5c, 0x6c, 0x6f, 0x63, 0x61, 0x6c,
		0x5c, 0x73, 0x68, 0x61, 0x72, 0x65,
		0x5c, 0x64, 0x61, 0x74, 0x61,
		0x5c, 0x69, 0x63, 0x75, 0x74, 0x65, 0x73, 0x74, 0x2e, 0x74, 0x78, 0x74,
		0
	};

	i18n_uchar result[200];
	int32_t len;

	ret = i18n_ucnv_create("ibm-943", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_to_uchars(cnv, result, I18N_UPRV_LENGTHOF(result), target, (int32_t)strlen(target), &len);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_fix_file_separator(cnv, NULL, len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_fix_file_separator_n3
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_fix_file_separator and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_fix_file_separator_n3(void)
{
	static const char target[] = {
		/* "\\usr\\local\\share\\data\\icutest.txt" */
		0x5c, 0x75, 0x73, 0x72,
		0x5c, 0x6c, 0x6f, 0x63, 0x61, 0x6c,
		0x5c, 0x73, 0x68, 0x61, 0x72, 0x65,
		0x5c, 0x64, 0x61, 0x74, 0x61,
		0x5c, 0x69, 0x63, 0x75, 0x74, 0x65, 0x73, 0x74, 0x2e, 0x74, 0x78, 0x74,
		0
	};

	i18n_uchar result[200];
	int32_t len;

	ret = i18n_ucnv_create("ibm-943", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_to_uchars(cnv, result, I18N_UPRV_LENGTHOF(result), target, (int32_t)strlen(target), &len);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_fix_file_separator(cnv, result, 0);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_is_ambiguous_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_is_ambiguous and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_is_ambiguous_p(void)
{
	ret = i18n_ucnv_create("UTF-8", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ubool result;
	ret = i18n_ucnv_is_ambiguous(cnv, &result);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_is_ambiguous_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_is_ambiguous and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_is_ambiguous_n(void)
{
	i18n_ubool result;
	ret = i18n_ucnv_is_ambiguous(NULL, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_set_fallback_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_set_fallback and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_set_fallback_p(void)
{
	ret = i18n_ucnv_create("ibm-1371", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_set_fallback(cnv, true);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ubool result;
	ret = i18n_ucnv_uses_fallback(cnv, &result);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(result, true);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_set_fallback_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_set_fallback and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_set_fallback_n(void)
{
	ret = i18n_ucnv_set_fallback(NULL, true);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_uses_fallback_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_uses_fallback and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_uses_fallback_p(void)
{
	ret = i18n_ucnv_create("ibm-1371", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucnv_set_fallback(cnv, true);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ubool result;
	ret = i18n_ucnv_uses_fallback(cnv, &result);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(result, true);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_uses_fallback_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_uses_fallback and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_uses_fallback_n(void)
{
	i18n_ubool result;
	ret = i18n_ucnv_uses_fallback(NULL, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_detect_unicode_signature_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_detect_unicode_signature and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_detect_unicode_signature_p(void)
{
	static const char* data[] = {
		"\xFE\xFF\x00\x00", 	/* UTF-16BE */
		"\xFF\xFE\x00\x00", 	/* UTF-16LE */
		"\xEF\xBB\xBF\x00", 	/* UTF-8	*/
		"\x0E\xFE\xFF\x00", 	/* SCSU 	*/

		"\xFE\xFF", 			/* UTF-16BE */
		"\xFF\xFE", 			/* UTF-16LE */
		"\xEF\xBB\xBF", 		/* UTF-8	*/
		"\x0E\xFE\xFF", 		/* SCSU 	*/

		"\xFE\xFF\x41\x42", 	/* UTF-16BE */
		"\xFF\xFE\x41\x41", 	/* UTF-16LE */
		"\xEF\xBB\xBF\x41", 	/* UTF-8	*/
		"\x0E\xFE\xFF\x41", 	/* SCSU 	*/

		"\x2B\x2F\x76\x38\x2D", /* UTF-7	*/
		"\x2B\x2F\x76\x38\x41", /* UTF-7	*/
		"\x2B\x2F\x76\x39\x41", /* UTF-7	*/
		"\x2B\x2F\x76\x2B\x41", /* UTF-7	*/
		"\x2B\x2F\x76\x2F\x41",  /* UTF-7	 */

		"\xDD\x73\x66\x73"		/* UTF-EBCDIC */
	};

	static const char* expected[] = {
		"UTF-16BE",
		"UTF-16LE",
		"UTF-8",
		"SCSU",

		"UTF-16BE",
		"UTF-16LE",
		"UTF-8",
		"SCSU",

		"UTF-16BE",
		"UTF-16LE",
		"UTF-8",
		"SCSU",

		"UTF-7",
		"UTF-7",
		"UTF-7",
		"UTF-7",
		"UTF-7",

		"UTF-EBCDIC"
	};

	static const int32_t expected_len[] ={
		2, 2, 3, 3,
		2, 2, 3, 3,
		2, 2, 3, 3,
		5, 4, 4, 4, 4,
		4
	};

	const char *source = NULL;
	const char *name = NULL;
	int32_t signature_length = -1;

	for(int i = 0; i<I18N_UPRV_LENGTHOF(data); ++i) {
		source = data[i];
		ret = i18n_ucnv_detect_unicode_signature(source, -1, &signature_length, &name);
		assert_eq(ret, I18N_ERROR_NONE);
		assert_eq(signature_length, expected_len[i]);
		assert_eq(strcmp(name, expected[i]), 0);
	}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_detect_unicode_signature_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_detect_unicode_signature and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_detect_unicode_signature_n1(void)
{
	const char *name = NULL;
	int32_t signature_length = -1;

	ret = i18n_ucnv_detect_unicode_signature("\xEF\xBB\xBF", -2, &signature_length, &name);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_detect_unicode_signature_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_detect_unicode_signature and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_detect_unicode_signature_n2(void)
{
	const char *name = NULL;
	int32_t signature_length = -1;

	ret = i18n_ucnv_detect_unicode_signature(NULL, -1, &signature_length, &name);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_ucount_pending_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_ucount_pending and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_ucount_pending_p(void)
{
	static const struct {
		i18n_uchar input[6];
		int32_t len;
		int32_t exp;
	}from_unicode_tests[] = {
		{{ 0xdbc4},1,1},
		{{ 0xdbc4, 0xde34, 0xd84d},3,1},
	};

	ret = i18n_ucnv_create("UTF-8", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	for(int i = 0; i<I18N_UPRV_LENGTHOF(from_unicode_tests); ++i) {
		char tgt[10];
		char *target = tgt;
		char *target_limit = target + 10;
		const i18n_uchar *source = from_unicode_tests[i].input;
		const i18n_uchar *source_limit = source + from_unicode_tests[i].len;
		int32_t len = 0;

		ret = i18n_ucnv_from_unicode(cnv, &target, target_limit, &source, source_limit, NULL, false);
		assert_eq(ret, I18N_ERROR_NONE);

		ret = i18n_ucnv_from_ucount_pending(cnv, &len);
		assert_eq(ret, I18N_ERROR_NONE);
		assert_eq(len, from_unicode_tests[i].exp);
	}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_from_ucount_pending_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_from_ucount_pending and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_from_ucount_pending_n(void)
{
	int32_t len = 0;

	ret = i18n_ucnv_from_ucount_pending(NULL, &len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_ucount_pending_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_ucount_pending and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_ucount_pending_p(void)
{
	static const struct {
		char input[6];
		int32_t len;
		int32_t exp;
	}to_unicode_tests[] = {
		{{0x05, 0x01, 0x02},3,3},
		{{0x01, 0x02},2,2},
		{{0x07,  0x00, 0x01, 0x02},4,4},
	};

	ret = i18n_ucnv_create("UTF-8", &cnv);
	assert_eq(ret, I18N_ERROR_NONE);

	for(int i = 0; i<I18N_UPRV_LENGTHOF(to_unicode_tests); ++i) {
		i18n_uchar tgt[10];
		i18n_uchar *target = tgt;
		i18n_uchar *target_limit = target + 10;
		const char *source = to_unicode_tests[i].input;
		const char *source_limit = source + to_unicode_tests[i].len;
		int32_t len = 0;

		ret = i18n_ucnv_to_unicode(cnv, &target, target_limit, &source, source_limit, NULL, false);
		assert_eq(ret, I18N_ERROR_NONE);

		ret = i18n_ucnv_to_ucount_pending(cnv, &len);
		assert_eq(ret, I18N_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_to_ucount_pending_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_to_ucount_pending and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_to_ucount_pending_n(void)
{
	int32_t len = 0;

	ret = i18n_ucnv_to_ucount_pending(NULL, &len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_is_fixed_width_p
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_is_fixed_width and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_is_fixed_width_p(void)
{
	const char *fixed_width[] = {
		"US-ASCII",
		"UTF32",
		"ibm-5478_P100-1995"
	};

	const char *not_fixed_width[] = {
		"GB18030",
		"UTF8",
		"windows-949-2000",
		"UTF16"
	};

	for(int i = 0; i<I18N_UPRV_LENGTHOF(fixed_width); ++i) {
		ret = i18n_ucnv_create(fixed_width[i], &cnv);
		assert_eq(ret, I18N_ERROR_NONE);

		i18n_ubool result;
		ret = i18n_ucnv_is_fixed_width(cnv, &result);
		assert_eq(ret, I18N_ERROR_NONE);
		assert_eq(result, true);
	}

	for(int i = 0; i<I18N_UPRV_LENGTHOF(not_fixed_width); ++i) {
		ret = i18n_ucnv_create(not_fixed_width[i], &cnv);
		assert_eq(ret, I18N_ERROR_NONE);

		i18n_ubool result;
		ret = i18n_ucnv_is_fixed_width(cnv, &result);
		assert_eq(ret, I18N_ERROR_NONE);
		assert_eq(result, false);
	}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucnv_is_fixed_width_n
 * @since_tizen 6.0
 * @description Calls i18n_ucnv_is_fixed_width and check whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucnv_is_fixed_width_n(void)
{
	i18n_ubool result;
	ret = i18n_ucnv_is_fixed_width(NULL, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}
