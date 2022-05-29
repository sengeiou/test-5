#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

#define I18N_UPRV_LENGTHOF(array) (int32_t)(sizeof(array)/sizeof((array)[0]))

static int ret = I18N_ERROR_NONE;
static int i;
static i18n_uidna_h uidna;

/**
* @function        utc_capi_base_utils_uidna_startup
* @description     Called before each test
* @parameter       NA
* @return          NA
*/
void utc_capi_base_utils_uidna_startup(void)
{
}

/**
* @function        utc_capi_base_utils_uidna_cleanup
* @description     Called after each test
* @parameter       NA
* @return          NA
*/
void utc_capi_base_utils_uidna_cleanup(void)
{
	if (!uidna)
		i18n_uidna_destroy(uidna);
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_label_to_ascii_p
 * @since_tizen 6.0
 * @description Calls i18n_uidna_label_to_ASCII and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_label_to_ascii_p(void)
{
    static const i18n_uchar fA_sharps16[] = { 0x66, 0x41, 0xdf, 0 };
    static const i18n_uchar fa_sharps16[] = { 0x66, 0x61, 0xdf, 0 };

	i18n_uchar dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_label_to_ascii(uidna, fA_sharps16, -1, dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(length, 4);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_label_to_ascii_n
 * @since_tizen 6.0
 * @description Calls i18n_uidna_label_to_ASCII and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_label_to_ascii_n(void)
{
    static const i18n_uchar fA_sharps16[] = { 0x66, 0x41, 0xdf, 0 };
	i18n_uchar dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_label_to_ascii(uidna, NULL, -3, dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uidna_label_to_ascii(uidna, fA_sharps16, -1, NULL, 0, &info, &length);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

	ret = i18n_uidna_label_to_ascii(uidna, fA_sharps16, -1, NULL, -2, &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uidna_label_to_ascii(uidna, fA_sharps16, -1, (i18n_uchar *)fA_sharps16, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_label_to_unicode_p
 * @since_tizen 6.0
 * @description Calls i18n_uidna_label_to_unicode and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_label_to_unicode_p(void)
{
    static const i18n_uchar fA_sharps16[] = { 0x66, 0x41, 0xdf, 0 };
	i18n_uchar dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_label_to_unicode(uidna, fA_sharps16, i18n_ustring_get_length(fA_sharps16), dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(length, 4);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_label_to_unicode_n
 * @since_tizen 6.0
 * @description Calls i18n_uidna_label_to_unicode and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_label_to_unicode_n(void)
{
    static const i18n_uchar fA_sharps16[] = { 0x66, 0x41, 0xdf, 0 };
	i18n_uchar dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_label_to_unicode(uidna, NULL, -3, dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uidna_label_to_unicode(uidna, fA_sharps16, -1, NULL, 0, &info, &length);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

	ret = i18n_uidna_label_to_unicode(uidna, fA_sharps16, -1, NULL, -2, &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uidna_label_to_unicode(uidna, fA_sharps16, -1, (i18n_uchar *)fA_sharps16, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_name_to_ascii_p
 * @since_tizen 6.0
 * @description Calls i18n_uidna_name_to_ASCII and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_name_to_ascii_p(void)
{
    static const i18n_uchar fA_sharps16[] = { 0x66, 0x41, 0xdf, 0 };

	i18n_uchar dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_name_to_ascii(uidna, fA_sharps16, i18n_ustring_get_length(fA_sharps16), dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(length, 4);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_name_to_ascii_n
 * @since_tizen 6.0
 * @description Calls i18n_uidna_name_to_ASCII and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_name_to_ascii_n(void)
{
    static const i18n_uchar fA_sharps16[] = { 0x66, 0x41, 0xdf, 0 };
	i18n_uchar dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_name_to_ascii(uidna, NULL, -3, dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uidna_name_to_ascii(uidna, fA_sharps16, -1, NULL, 0, &info, &length);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

	ret = i18n_uidna_name_to_ascii(uidna, fA_sharps16, -1, NULL, -2, &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uidna_name_to_ascii(uidna, fA_sharps16, -1, (i18n_uchar *)fA_sharps16, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_name_to_unicode_p
 * @since_tizen 6.0
 * @description Calls i18n_uidna_name_to_unicode and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_name_to_unicode_p(void)
{
    static const i18n_uchar fA_sharps16[] = { 0x66, 0x41, 0xdf, 0 };
	i18n_uchar dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_name_to_unicode(uidna, fA_sharps16, -1, dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(length, 4);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_name_to_unicode_n
 * @since_tizen 6.0
 * @description Calls i18n_uidna_name_to_unicode and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_name_to_unicode_n(void)
{
    static const i18n_uchar fA_sharps16[] = { 0x66, 0x41, 0xdf, 0 };
	i18n_uchar dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_name_to_unicode(uidna, NULL, -3, dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uidna_name_to_unicode(uidna, fA_sharps16, -1, NULL, 0, &info, &length);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

	ret = i18n_uidna_name_to_unicode(uidna, fA_sharps16, -1, NULL, -2, &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uidna_name_to_unicode(uidna, fA_sharps16, -1, (i18n_uchar *)fA_sharps16, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_label_to_ascii_UTF8_p
 * @since_tizen 6.0
 * @description Calls i18n_uidna_label_to_ascii_UTF8 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_label_to_ascii_UTF8_p(void)
{
    static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };
	char dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_label_to_ascii_UTF8(uidna, fA_sharps8, -1, dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(length, 4);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_label_to_ascii_UTF8_n
 * @since_tizen 6.0
 * @description Calls i18n_uidna_label_to_ascii_UTF8 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_label_to_ascii_UTF8_n(void)
{
    static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };
	char dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_label_to_ascii_UTF8(uidna, NULL, -3, dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uidna_label_to_ascii_UTF8(uidna, fA_sharps8, -1, NULL, 0, &info, &length);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

	ret = i18n_uidna_label_to_ascii_UTF8(uidna, fA_sharps8, -1, NULL, -2, &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uidna_label_to_ascii_UTF8(uidna, fA_sharps8, -1, (char *)fA_sharps8, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_label_to_unicode_UTF8_p
 * @since_tizen 6.0
 * @description Calls i18n_uidna_label_to_unicode_UTF8 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_label_to_unicode_UTF8_p(void)
{
    static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };
	char dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_label_to_unicode_UTF8(uidna, fA_sharps8, (int32_t)strlen(fA_sharps8), dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(length, 4);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_label_to_unicode_UTF8_n
 * @since_tizen 6.0
 * @description Calls i18n_uidna_label_to_unicode_UTF8 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_label_to_unicode_UTF8_n(void)
{
    static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };
	char dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_label_to_unicode_UTF8(uidna, NULL, -3, dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uidna_label_to_unicode_UTF8(uidna, fA_sharps8, (int32_t)strlen(fA_sharps8), NULL, 0, &info, &length);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

	ret = i18n_uidna_label_to_unicode_UTF8(uidna, fA_sharps8, (int32_t)strlen(fA_sharps8), NULL, -2, &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uidna_label_to_unicode_UTF8(uidna, fA_sharps8, (int32_t)strlen(fA_sharps8), (char *)fA_sharps8, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_name_to_ascii_UTF8_p
 * @since_tizen 6.0
 * @description Calls i18n_uidna_label_to_unicode_UTF8 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_name_to_ascii_UTF8_p(void)
{
    static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };
	char dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_name_to_ascii_UTF8(uidna, fA_sharps8, (int32_t)strlen(fA_sharps8), dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(length, 4);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_name_to_ascii_UTF8_n
 * @since_tizen 6.0
 * @description Calls i18n_uidna_label_to_unicode_UTF8 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_name_to_ascii_UTF8_n(void)
{
    static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };
	char dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_name_to_ascii_UTF8(uidna, NULL, -3, dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uidna_name_to_ascii_UTF8(uidna, fA_sharps8, (int32_t)strlen(fA_sharps8), NULL, 0, &info, &length);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

	ret = i18n_uidna_name_to_ascii_UTF8(uidna, fA_sharps8, (int32_t)strlen(fA_sharps8), NULL, -2, &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uidna_name_to_ascii_UTF8(uidna, fA_sharps8, (int32_t)strlen(fA_sharps8), (char *)fA_sharps8, 4, &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_name_to_unicode_UTF8_p
 * @since_tizen 6.0
 * @description Calls i18n_uidna_name_to_unicode_UTF8 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_name_to_unicode_UTF8_p(void)
{
    static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };
	char dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_name_to_unicode_UTF8(uidna, fA_sharps8, -1, dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(length, 4);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_name_to_unicode_UTF8_n
 * @since_tizen 6.0
 * @description Calls i18n_uidna_name_to_unicode_UTF8 and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_name_to_unicode_UTF8_n(void)
{
    static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };
	char dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_name_to_unicode_UTF8(uidna, NULL, -3, dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uidna_name_to_unicode_UTF8(uidna, fA_sharps8, -1, NULL, 0, &info, &length);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

	ret = i18n_uidna_name_to_unicode_UTF8(uidna, fA_sharps8, -1, NULL, -2, &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uidna_name_to_unicode_UTF8(uidna, fA_sharps8, -1, (char *)fA_sharps8, 4, &info, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_info_get_is_trans_different_p
 * @since_tizen 6.0
 * @description Calls i18n_uidna_info_get_is_trans_different and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_info_get_is_trans_different_p(void)
{
    static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };
	char dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_name_to_unicode_UTF8(uidna, fA_sharps8, -1, dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ubool is_trans_different;
	ret = i18n_uidna_info_get_is_trans_different(info, &is_trans_different);
	assert_eq(is_trans_different, true);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_info_get_is_trans_different_n
 * @since_tizen 6.0
 * @description Calls i18n_uidna_info_get_is_trans_different and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_info_get_is_trans_different_n(void)
{
    static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };
	char dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_name_to_unicode_UTF8(uidna, fA_sharps8, -1, dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ubool is_trans_different;
	ret = i18n_uidna_info_get_is_trans_different(NULL, &is_trans_different);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uidna_info_get_is_trans_different(info, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_info_get_errors_p
 * @since_tizen 6.0
 * @description Calls i18n_uidna_info_get_errors and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_info_get_errors_p(void)
{
    static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };
	char dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_name_to_unicode_UTF8(uidna, fA_sharps8, -1, dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_NONE);

	uint32_t errors;
	ret = i18n_uidna_info_get_errors(info, &errors);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_info_get_errors_n
 * @since_tizen 6.0
 * @description Calls i18n_uidna_info_get_errors and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_info_get_errors_n(void)
{
    static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };
	char dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_name_to_unicode_UTF8(uidna, fA_sharps8, -1, dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_NONE);

	uint32_t errors;
	ret = i18n_uidna_info_get_errors(NULL, &errors);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uidna_info_get_errors(info, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_info_destroy_p
 * @since_tizen 6.0
 * @description Calls i18n_uidna_info_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_info_destroy_p(void)
{
    static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };
	char dest[10];
	i18n_uidna_info_h info;
	int32_t length;

	ret = i18n_uidna_create(I18N_UIDNA_DEFAULT, &uidna);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_name_to_unicode_UTF8(uidna, fA_sharps8, -1, dest, I18N_UPRV_LENGTHOF(dest), &info, &length);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uidna_info_destroy(info);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uidna_info_destroy_n
 * @since_tizen 6.0
 * @description Calls i18n_uidna_info_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uidna_info_destroy_n(void)
{
	ret = i18n_uidna_info_destroy(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

