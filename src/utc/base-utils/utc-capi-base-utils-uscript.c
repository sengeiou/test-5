#include "assert.h"
#include <string.h>
#include <utils_i18n.h>

#define LENGTHOF(array) (int32_t)(sizeof(array)/sizeof((array)[0]))

static int ret = I18N_ERROR_NONE;

/**
* @function        utc_capi_base_utils_uscript_startup
* @description     Called before each test
* @parameter       NA
* @return          NA
*/
void utc_capi_base_utils_uscript_startup(void)
{
}

/**
* @function        utc_capi_base_utils_uscript_cleanup
* @description     Called after each test
* @parameter       NA
* @return          NA
*/
void utc_capi_base_utils_uscript_cleanup(void)
{
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_get_codes_p
 * @since_tizen 6.0
 * @description Calls i18n_uscript_get_codes and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_get_codes_p(void)
{
	static const i18n_uscript_code_e KOREAN[2] = { I18N_USCRIPT_HANGUL, I18N_USCRIPT_HAN };
	i18n_uscript_code_e scripts[2];
	int32_t len = 0;

	ret = i18n_uscript_get_codes("ko", scripts, 2, &len);
	assert_eq(ret, I18N_ERROR_NONE);

	int i;
	for(i = 0; i<2; ++i)
		assert_eq(KOREAN[i], scripts[i]);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_get_codes_n
 * @since_tizen 6.0
 * @description Calls i18n_uscript_get_codes and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_get_codes_n(void)
{
	static const i18n_uscript_code_e KOREAN[2] = { I18N_USCRIPT_HANGUL, I18N_USCRIPT_HAN };
	i18n_uscript_code_e scripts[2];
	int32_t len = 0;

	ret = i18n_uscript_get_codes(NULL, scripts, 2, &len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uscript_get_codes("ko", scripts, -1, &len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uscript_get_codes("ko", scripts, 2, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_get_name_p
 * @since_tizen 6.0
 * @description Calls i18n_uscript_get_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_get_name_p(void)
{
	const char * name = i18n_uscript_get_name(I18N_USCRIPT_HANGUL);
	assert_eq(strcmp(name, "Hangul"), 0);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_get_name_n
 * @since_tizen 6.0
 * @description Calls i18n_uscript_get_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_get_name_n(void)
{
	const char * name = i18n_uscript_get_name(I18N_USCRIPT_INVALID_CODE);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	name = i18n_uscript_get_name(I18N_USCRIPT_CODE_LIMIT);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_get_short_name_p
 * @since_tizen 6.0
 * @description Calls i18n_uscript_get_short_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_get_short_name_p(void)
{
	const char * name = i18n_uscript_get_short_name(I18N_USCRIPT_HANGUL);
	assert_eq(strcmp(name, "Hang"), 0);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_get_short_name_n
 * @since_tizen 6.0
 * @description Calls i18n_uscript_get_short_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_get_short_name_n(void)
{
	const char * name = i18n_uscript_get_short_name(I18N_USCRIPT_INVALID_CODE);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	name = i18n_uscript_get_short_name(I18N_USCRIPT_CODE_LIMIT);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase utc_capi_base_utils_i18n_uscript_get_script_p
 * @since_tizen 6.0
 * @description Calls i18n_uscript_get_script and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_get_script_p(void)
{
	i18n_uscript_code_e script_code = I18N_USCRIPT_INVALID_CODE;

	static uint32_t codepoints[] = {
		0x0000FFBE, /* I18N_USCRIPT_HANGUL*/
		0x0000FFCF, /* I18N_USCRIPT_HANGUL*/
		0x0000FFD7, /* I18N_USCRIPT_HANGUL*/
		0x0000FFDC, /* I18N_USCRIPT_HANGUL*/
		0x00010330, /* I18N_USCRIPT_GOTHIC*/
	};

	static i18n_uscript_code_e expected[] = {
		I18N_USCRIPT_HANGUL,
		I18N_USCRIPT_HANGUL,
		I18N_USCRIPT_HANGUL,
		I18N_USCRIPT_HANGUL,
		I18N_USCRIPT_GOTHIC,
	};

	static int cnt;
	for(cnt = 0; cnt <5; ++cnt) {
		ret = i18n_uscript_get_script(codepoints[cnt], &script_code);
		assert_eq(ret, I18N_ERROR_NONE);
		assert_eq(script_code, expected[cnt]);
	}
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_get_script_n
 * @since_tizen 6.0
 * @description Calls i18n_uscript_get_script and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_get_script_n(void)
{
	i18n_uscript_code_e script_code = I18N_USCRIPT_INVALID_CODE;

	ret = i18n_uscript_get_script((i18n_uscript_code_e)(I18N_USCRIPT_INVALID_CODE-1), &script_code);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uscript_get_script((i18n_uscript_code_e)(I18N_USCRIPT_INVALID_CODE), NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_has_script_p
 * @since_tizen 6.0
 * @description Calls i18n_uscript_has_script and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_has_script_p(void)
{
	i18n_ubool b = i18n_uscript_has_script(0x063f, I18N_USCRIPT_ARABIC);
	assert_eq(b, true);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_has_script_n
 * @since_tizen 6.0
 * @description Calls i18n_uscript_has_script and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_has_script_n(void)
{
	i18n_ubool b = i18n_uscript_has_script(0x063f, I18N_USCRIPT_INVALID_CODE);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	b = i18n_uscript_has_script(0x063f, I18N_USCRIPT_CODE_LIMIT);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_get_script_extensions_p
 * @since_tizen 6.0
 * @description Calls i18n_uscript_get_script_extensions and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_get_script_extensions_p(void)
{
	i18n_uscript_code_e scripts[20];
	int32_t len = 0;

	ret = i18n_uscript_get_script_extensions(0x0640, scripts, LENGTHOF(scripts), &len);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_get_script_extensions_n
 * @since_tizen 6.0
 * @description Calls i18n_uscript_get_script_extensions and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_get_script_extensions_n(void)
{
	i18n_uscript_code_e scripts[20];
	int32_t len = 0;

	ret = i18n_uscript_get_script_extensions(0x0640, scripts, -1, &len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_uscript_get_script_extensions(0x0640, scripts, LENGTHOF(scripts), NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}


/**
 * @testcase utc_capi_base_utils_i18n_uscript_get_sample_string_p
 * @since_tizen 6.0
 * @description Calls i18n_uscript_get_sample_string and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_get_sample_string_p(void)
{
	i18n_uchar sample[8];
	int32_t len = 0;

	ret = i18n_uscript_get_sample_string(I18N_USCRIPT_LATIN, sample, LENGTHOF(sample), &len);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_get_sample_string_n
 * @since_tizen 6.0
 * @description Calls i18n_uscript_get_sample_string and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_get_sample_string_n(void)
{
	i18n_uchar sample[8];
	int32_t len = 0;

	ret = i18n_uscript_get_sample_string(I18N_USCRIPT_LATIN, sample, 0, &len);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

	ret = i18n_uscript_get_sample_string(I18N_USCRIPT_INVALID_CODE, sample, LENGTHOF(sample), &len);
	assert_eq(ret, I18N_USCRIPT_INVALID_CODE);

	ret = i18n_uscript_get_sample_string(I18N_USCRIPT_CODE_LIMIT, sample, 0, &len);
	assert_eq(ret, I18N_USCRIPT_INVALID_CODE);

	ret = i18n_uscript_get_sample_string(I18N_USCRIPT_LATIN, sample, LENGTHOF(sample), NULL);
	assert_eq(ret, I18N_USCRIPT_INVALID_CODE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_get_usage_p
 * @since_tizen 6.0
 * @description Calls i18n_uscript_getUsage and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_get_usage_p(void)
{
	i18n_uscript_usage_e usage = i18n_uscript_get_usage(I18N_USCRIPT_KOREAN);
	assert_eq(usage, I18N_USCRIPT_USAGE_RECOMMENDED);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_get_usage_n
 * @since_tizen 6.0
 * @description Calls i18n_uscript_get_usage and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_get_usage_n(void)
{
	i18n_uscript_usage_e usage = i18n_uscript_get_usage(I18N_USCRIPT_INVALID_CODE);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	assert_eq(usage, I18N_USCRIPT_USAGE_NOT_ENCODED);

	usage = i18n_uscript_get_usage(I18N_USCRIPT_CODE_LIMIT);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	assert_eq(usage, I18N_USCRIPT_USAGE_NOT_ENCODED);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_is_right_to_left_p
 * @since_tizen 6.0
 * @description Calls i18n_uscript_is_right_to_left and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_is_right_to_left_p(void)
{
	i18n_ubool b = i18n_uscript_is_right_to_left(I18N_USCRIPT_KOREAN);
	assert_eq(b, false);

	b = i18n_uscript_is_right_to_left(I18N_USCRIPT_ARABIC);
	assert_eq(b, true);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_is_right_to_left_n
 * @since_tizen 6.0
 * @description Calls i18n_uscript_is_right_to_left and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_is_right_to_left_n(void)
{
	i18n_ubool b = i18n_uscript_is_right_to_left(I18N_USCRIPT_INVALID_CODE);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	b = i18n_uscript_is_right_to_left(I18N_USCRIPT_CODE_LIMIT);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_breaks_between_letters_p
 * @since_tizen 6.0
 * @description Calls i18n_uscript_breaks_between_letters and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_breaks_between_letters_p(void)
{
	i18n_ubool b = i18n_uscript_breaks_between_letters(I18N_USCRIPT_KOREAN);
	assert_eq(b, false);

	b = i18n_uscript_breaks_between_letters(I18N_USCRIPT_THAI);
	assert_eq(b, true);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_breaks_between_letters_n
 * @since_tizen 6.0
 * @description Calls i18n_uscript_breaks_between_letters and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_breaks_between_letters_n(void)
{
	i18n_ubool b = i18n_uscript_breaks_between_letters(I18N_USCRIPT_INVALID_CODE);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	b = i18n_uscript_breaks_between_letters(I18N_USCRIPT_CODE_LIMIT);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_is_cased_p
 * @since_tizen 6.0
 * @description Calls i18n_uscript_is_cased and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_is_cased_p(void)
{
	i18n_ubool b = i18n_uscript_is_cased(I18N_USCRIPT_KOREAN);
	assert_eq(b, false);

	b = i18n_uscript_is_cased(I18N_USCRIPT_LATIN);
	assert_eq(b, true);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uscript_is_cased_n
 * @since_tizen 6.0
 * @description Calls i18n_uscript_is_cased and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_uscript_is_cased_n(void)
{
	i18n_ubool b = i18n_uscript_is_cased(I18N_USCRIPT_INVALID_CODE);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	b = i18n_uscript_is_cased(I18N_USCRIPT_CODE_LIMIT);
	ret = get_last_result();
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}
