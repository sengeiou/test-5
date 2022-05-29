#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

#define I18N_UPRV_LENGTHOF(array) (int32_t)(sizeof(array)/sizeof((array)[0]))

static int32_t preflight(const i18n_uchar *src, int32_t length, i18n_ucnv_h cnv);
static char *extract_bytes(const i18n_uchar *src, int32_t length, const char *codepage, int32_t *byte_length);

static int ret = I18N_ERROR_NONE;
static int i;
i18n_ucharset_detector_h ucsd;

/**
 * @function        utc_capi_base_utils_ucsdet_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_ucsdet_startup(void)
{
}

/**
 * @function        utc_capi_base_utils_ucsdet_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_ucsdet_cleanup(void)
{
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_create_p
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_create_p(void)
{
	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	if(ucsd != NULL)
		i18n_ucsdet_destroy(ucsd);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_create_n
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_create_n(void)
{
	ret = i18n_ucsdet_create(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_destroy_p
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_destroy_p(void)
{
	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	if(ucsd != NULL) {
		ret = i18n_ucsdet_destroy(ucsd);
		assert_eq(ret, I18N_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_destroy_n
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_destroy_n(void)
{
	ret = i18n_ucsdet_destroy(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_set_text_p
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_set_text and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_set_text_p(void)
{
	static const char ss[] = "This is a string with some non-ascii characters that will "
		"be converted to UTF-8, then showed through the detection process.  "
		"\\u0391\\u0392\\u0393\\u0394\\u0395"
		"Sure would be nice if our source could contain Unicode directly!";

	int32_t byte_length = 0, s_length = 0, d_length = 0;
	i18n_uchar s[sizeof(ss)];
	char *bytes;

	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	s_length = i18n_ustring_unescape(ss, s, sizeof(ss));

	bytes = extract_bytes(s, s_length, "UTF-8", &byte_length);

	ret = i18n_ucsdet_set_text(ucsd, bytes, byte_length);
	assert_eq(ret, I18N_ERROR_NONE);

	free(bytes);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_set_text_n
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_set_text and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_set_text_n(void)
{
	ret = i18n_ucsdet_set_text(NULL, NULL, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_set_declared_encoding_p
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_set_declared_encoding and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_set_declared_encoding_p(void)
{
	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucsdet_set_declared_encoding(ucsd, "ISO-2022-JP", -1);
	assert_eq(ret, I18N_ERROR_NONE);

	if(ucsd != NULL)
		i18n_ucsdet_destroy(ucsd);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_set_declared_encoding_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_set_declared_encoding and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_set_declared_encoding_n1(void)
{
	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucsdet_set_declared_encoding(NULL, "ISO-2022-JP", -1);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_set_declared_encoding_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_set_declared_encoding and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_set_declared_encoding_n2(void)
{
	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucsdet_set_declared_encoding(ucsd, NULL, -1);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_detect_p
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_detect and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_detect_p(void)
{
	static const char ss[] = "This is a string with some non-ascii characters that will "
		"be converted to UTF-8, then showed through the detection process.  "
		"\\u0391\\u0392\\u0393\\u0394\\u0395"
		"Sure would be nice if our source could contain Unicode directly!";

	int32_t byte_length = 0, s_length = 0, d_length = 0;
	i18n_uchar s[sizeof(ss)];
	char *bytes;

	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	s_length = i18n_ustring_unescape(ss, s, sizeof(ss));

	bytes = extract_bytes(s, s_length, "UTF-8", &byte_length);

	ret = i18n_ucsdet_set_text(ucsd, bytes, byte_length);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ucharset_match_h ucsm;
	ret = i18n_ucsdet_detect(ucsd, &ucsm);
	assert_eq(ret, I18N_ERROR_NONE);

	free(bytes);
	return 0;
}


/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_detect_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_detect and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_detect_n1(void)
{
	int32_t matches_found = 0;
	i18n_ucharset_match_h ucsm = NULL;

	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucsdet_detect(NULL, &ucsm);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_detect_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_detect and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_detect_n2(void)
{
	int32_t matches_found = 0;
	i18n_ucharset_match_h ucsm = NULL;

	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucsdet_detect(ucsd, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_detect_all_p
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_detect_all and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_detect_all_p(void)
{
	static const char ss[] = "<a> <lot> <of> <English> <inside> <the> <markup> Un tr\\u00E8s petit peu de Fran\\u00E7ais. <to> <confuse> <the> <detector>";
	int32_t s_length = 0;
	i18n_uchar s[sizeof(ss)];
	int32_t byte_length = 0;
	char *bytes;

	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	const char *lang, *name;
	s_length = i18n_ustring_unescape(ss, s, sizeof(ss));
	bytes = extract_bytes(s, s_length, "ISO-8859-1", &byte_length);

	i18n_ubool result;
	ret = i18n_ucsdet_enable_input_filter(ucsd, true, &result);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucsdet_is_input_filter_enabled(ucsd, &result);
	assert_eq(result, true);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucsdet_set_text(ucsd, bytes, byte_length);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ucharset_match_h *ucsms;
	int32_t matches_found = 0;
	ret = i18n_ucsdet_detect_all(ucsd, &matches_found, &ucsms);
	assert_eq(ret, I18N_ERROR_NONE);

	free(bytes);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_detect_all_n
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_detect_all and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_detect_all_n(void)
{
	int32_t matches_found = 0;
	i18n_ucharset_match_h *ucsm = NULL;

	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucsdet_detect_all(NULL, &matches_found, &ucsm);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_get_name_p
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_get_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_get_name_p(void)
{
	static const char ss[] = "<a> <lot> <of> <English> <inside> <the> <markup> Un tr\\u00E8s petit peu de Fran\\u00E7ais. <to> <confuse> <the> <detector>";
	int32_t s_length = 0;
	i18n_uchar s[sizeof(ss)];
	int32_t byte_length = 0;
	char *bytes;

	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	const char *lang, *name;
	s_length = i18n_ustring_unescape(ss, s, sizeof(ss));
	bytes = extract_bytes(s, s_length, "ISO-8859-1", &byte_length);

	i18n_ubool result;
	ret = i18n_ucsdet_enable_input_filter(ucsd, true, &result);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucsdet_is_input_filter_enabled(ucsd, &result);
	assert_eq(result, true);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucsdet_set_text(ucsd, bytes, byte_length);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ucharset_match_h *ucsms;
	int32_t matches_found = 0;
	ret = i18n_ucsdet_detect_all(ucsd, &matches_found, &ucsms);
	assert_eq(ret, I18N_ERROR_NONE);

	for(int i = 0; i<matches_found; ++i) {
		i18n_ucharset_match_h ucsm;
		ret = i18n_ucsdet_detect(ucsd, &ucsm);
		assert_neq(ucsm, NULL);
		assert_eq(ret, I18N_ERROR_NONE);

		ret = i18n_ucsdet_get_name(ucsm, &name);
		assert_eq(ret, I18N_ERROR_NONE);
		assert_neq(name, NULL);
		assert_eq(strcmp(name, "ISO-8859-1"), 0);
	}

	free(bytes);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_get_name_n
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_get_name and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_get_name_n(void)
{
	const char *name;

	ret = i18n_ucsdet_get_name(NULL, &name);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_get_confidence_p
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_get_confidence and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_get_confidence_p(void)
{
	static const char ss[] = "<a> <lot> <of> <English> <inside> <the> <markup> Un tr\\u00E8s petit peu de Fran\\u00E7ais. <to> <confuse> <the> <detector>";
	int32_t s_length = 0;
	i18n_uchar s[sizeof(ss)];
	int32_t byte_length = 0;
	char *bytes;

	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	const char *lang, *name;
	s_length = i18n_ustring_unescape(ss, s, sizeof(ss));
	bytes = extract_bytes(s, s_length, "ISO-8859-1", &byte_length);

	i18n_ubool result;
	ret = i18n_ucsdet_enable_input_filter(ucsd, true, &result);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucsdet_is_input_filter_enabled(ucsd, &result);
	assert_eq(result, true);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucsdet_set_text(ucsd, bytes, byte_length);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ucharset_match_h *ucsms;
	int32_t matches_found = 0;
	ret = i18n_ucsdet_detect_all(ucsd, &matches_found, &ucsms);
	assert_eq(ret, I18N_ERROR_NONE);

	for(int i = 0; i<matches_found; ++i) {
		i18n_ucharset_match_h ucsm;
		ret = i18n_ucsdet_detect(ucsd, &ucsm);
		assert_neq(ucsm, NULL);
		assert_eq(ret, I18N_ERROR_NONE);

		int32_t number;
		ret = i18n_ucsdet_get_confidence(ucsm, &number);
		assert_eq(ret, I18N_ERROR_NONE);
		assert_eq(number, 56);
	}

	if(ucsd != NULL)
		i18n_ucsdet_destroy(ucsd);

	free(bytes);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_get_confidence_n
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_get_confidence and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_get_confidence_n(void)
{
	int32_t number;
	ret = i18n_ucsdet_get_confidence(NULL, &number);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_get_language_p
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_get_language and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_get_language_p(void)
{
	static const char ss[] = "<a> <lot> <of> <English> <inside> <the> <markup> Un tr\\u00E8s petit peu de Fran\\u00E7ais. <to> <confuse> <the> <detector>";
	int32_t s_length = 0;
	i18n_uchar s[sizeof(ss)];
	int32_t byte_length = 0;
	char *bytes;

	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	const char *lang, *name;
	s_length = i18n_ustring_unescape(ss, s, sizeof(ss));
	bytes = extract_bytes(s, s_length, "ISO-8859-1", &byte_length);

	i18n_ubool result;
	ret = i18n_ucsdet_enable_input_filter(ucsd, true, &result);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucsdet_is_input_filter_enabled(ucsd, &result);
	assert_eq(result, true);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucsdet_set_text(ucsd, bytes, byte_length);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ucharset_match_h *ucsms;
	int32_t matches_found = 0;
	ret = i18n_ucsdet_detect_all(ucsd, &matches_found, &ucsms);
	assert_eq(ret, I18N_ERROR_NONE);

	for(int i = 0; i<matches_found; ++i) {
		i18n_ucharset_match_h ucsm;
		ret = i18n_ucsdet_detect(ucsd, &ucsm);
		assert_neq(ucsm, NULL);
		assert_eq(ret, I18N_ERROR_NONE);

		ret = i18n_ucsdet_get_language(ucsm, &lang);
		assert_eq(ret, I18N_ERROR_NONE);
		assert_neq(lang, NULL);
		assert_eq(strcmp(lang, "fr"), 0);
	}

	if(ucsd != NULL)
		i18n_ucsdet_destroy(ucsd);

	free(bytes);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_get_language_n
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_get_language and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_get_language_n(void)
{
	const char *name;

	ret = i18n_ucsdet_get_name(NULL, &name);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_get_uchars_p
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_get_uchars and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_get_uchars_p(void)
{
	static const char ss[] = "This is a string with some non-ascii characters that will "
		"be converted to UTF-8, then showed through the detection process.  "
		"\\u0391\\u0392\\u0393\\u0394\\u0395"
		"Sure would be nice if our source could contain Unicode directly!";

	int32_t byte_length = 0, s_length = 0, d_length = 0;
	i18n_uchar s[sizeof(ss)];
	char *bytes;

	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	s_length = i18n_ustring_unescape(ss, s, sizeof(ss));

	bytes = extract_bytes(s, s_length, "UTF-8", &byte_length);

	ret = i18n_ucsdet_set_text(ucsd, bytes, byte_length);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ucharset_match_h ucsm;
	ret = i18n_ucsdet_detect(ucsd, &ucsm);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar detected[sizeof(ss)];
	ret = i18n_ucsdet_get_uchars(ucsm, detected, s_length, &d_length);
	assert_eq(ret, I18N_ERROR_NONE);

	if(ucsd != NULL)
		i18n_ucsdet_destroy(ucsd);

	free(bytes);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_get_uchars_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_get_uchars and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_get_uchars_n1(void)
{
	static const char ss[] = "This is a string with some non-ascii characters that will "
		"be converted to UTF-8, then showed through the detection process.  "
		"\\u0391\\u0392\\u0393\\u0394\\u0395"
		"Sure would be nice if our source could contain Unicode directly!";

	int32_t byte_length = 0, s_length = 0, d_length = 0;
	i18n_uchar s[sizeof(ss)];
	char *bytes;

	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	s_length = i18n_ustring_unescape(ss, s, sizeof(ss));

	bytes = extract_bytes(s, s_length, "UTF-8", &byte_length);

	ret = i18n_ucsdet_set_text(ucsd, bytes, byte_length);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ucharset_match_h ucsm;
	ret = i18n_ucsdet_detect(ucsd, &ucsm);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar detected[sizeof(ss)];
	ret = i18n_ucsdet_get_uchars(NULL, detected, s_length, &d_length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	free(bytes);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_get_uchars_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_get_uchars and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_get_uchars_n2(void)
{
	static const char ss[] = "This is a string with some non-ascii characters that will "
		"be converted to UTF-8, then showed through the detection process.  "
		"\\u0391\\u0392\\u0393\\u0394\\u0395"
		"Sure would be nice if our source could contain Unicode directly!";

	int32_t byte_length = 0, s_length = 0, d_length = 0;
	i18n_uchar s[sizeof(ss)];
	char *bytes;

	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	s_length = i18n_ustring_unescape(ss, s, sizeof(ss));

	bytes = extract_bytes(s, s_length, "UTF-8", &byte_length);

	ret = i18n_ucsdet_set_text(ucsd, bytes, byte_length);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ucharset_match_h ucsm;
	ret = i18n_ucsdet_detect(ucsd, &ucsm);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucsdet_get_uchars(ucsm, NULL, s_length, &d_length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	free(bytes);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_get_uchars_n3
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_get_uchars and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_get_uchars_n3(void)
{
	static const char ss[] = "This is a string with some non-ascii characters that will "
		"be converted to UTF-8, then showed through the detection process.  "
		"\\u0391\\u0392\\u0393\\u0394\\u0395"
		"Sure would be nice if our source could contain Unicode directly!";

	int32_t byte_length = 0, s_length = 0, d_length = 0;
	i18n_uchar s[sizeof(ss)];
	char *bytes;

	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	s_length = i18n_ustring_unescape(ss, s, sizeof(ss));

	bytes = extract_bytes(s, s_length, "UTF-8", &byte_length);

	ret = i18n_ucsdet_set_text(ucsd, bytes, byte_length);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ucharset_match_h ucsm;
	ret = i18n_ucsdet_detect(ucsd, &ucsm);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar detected[sizeof(ss)];
	ret = i18n_ucsdet_get_uchars(ucsm, detected, -2, &d_length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	free(bytes);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_get_all_detectable_charsets_p
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_get_all_detectable_charsets and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_get_all_detectable_charsets_p(void)
{
	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uenumeration_h iterator;
	ret = i18n_ucsdet_get_all_detectable_charsets(ucsd, &iterator);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(iterator, 0);

	if(ucsd != NULL)
		i18n_ucsdet_destroy(ucsd);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_get_all_detectable_charsets_n
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_get_all_detectable_charsets and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_get_all_detectable_charsets_n(void)
{
	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucsdet_get_all_detectable_charsets(ucsd, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_is_input_filter_enabled_p
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_is_input_filter_enabled and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_is_input_filter_enabled_p(void)
{
	static const char ss[] = "<a> <lot> <of> <English> <inside> <the> <markup> Un tr\\u00E8s petit peu de Fran\\u00E7ais. <to> <confuse> <the> <detector>";
	int32_t s_length = 0;
	i18n_uchar s[sizeof(ss)];
	int32_t byte_length = 0;
	char *bytes;

	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	const char *lang, *name;
	s_length = i18n_ustring_unescape(ss, s, sizeof(ss));
	bytes = extract_bytes(s, s_length, "ISO-8859-1", &byte_length);

	i18n_ubool result;
	ret = i18n_ucsdet_enable_input_filter(ucsd, true, &result);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucsdet_is_input_filter_enabled(ucsd, &result);
	assert_eq(result, true);
	assert_eq(ret, I18N_ERROR_NONE);

	free(bytes);
	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_is_input_filter_enabled_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_is_input_filter_enabled and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_is_input_filter_enabled_n1(void)
{
	i18n_ubool result;

	ret = i18n_ucsdet_is_input_filter_enabled(NULL, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_is_input_filter_enabled_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_is_input_filter_enabled and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_is_input_filter_enabled_n2(void)
{
	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucsdet_is_input_filter_enabled(ucsd, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_enable_input_filter_p
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_enable_input_filter and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_enable_input_filter_p(void)
{
	ret = i18n_ucsdet_create(&ucsd);

	i18n_ubool result;
	ret = i18n_ucsdet_enable_input_filter(ucsd, true, &result);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_enable_input_filter_n1
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_enable_input_filter and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_enable_input_filter_n1(void)
{
	i18n_ubool result;
	ret = i18n_ucsdet_enable_input_filter(NULL, true, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_ucsdet_enable_input_filter_n2
 * @since_tizen 6.0
 * @description Calls i18n_ucsdet_enable_input_filter and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_ucsdet_enable_input_filter_n2(void)
{
	ret = i18n_ucsdet_create(&ucsd);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_ucsdet_enable_input_filter(ucsd, true, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

static int32_t preflight(const i18n_uchar *src, int32_t length, i18n_ucnv_h cnv)
{
	int status;
	char buffer[1024];
	char *dest, *dest_limit = buffer + sizeof(buffer);
	const i18n_uchar *src_limit = src + length;
	int32_t result = 0;

	do {
		dest = buffer;
		status = I18N_ERROR_NONE;
		status = i18n_ucnv_from_unicode(cnv, &dest, dest_limit, &src, src_limit, 0, true);
		result += (int32_t) (dest - buffer);
	} while (status == I18N_ERROR_BUFFER_OVERFLOW);

	return result;
}

static char *extract_bytes(const i18n_uchar *src, int32_t length, const char *codepage, int32_t *byte_length)
{
	i18n_ucnv_h cnv;
	ret = i18n_ucnv_create(codepage, &cnv);
	int32_t byte_count = preflight(src, length, cnv);
	const i18n_uchar *src_limit = src + length;
	char *bytes = (char *) malloc((byte_count+1) * sizeof(char));
	char *dest = bytes, *dest_limit = bytes + byte_count + 1;

	ret = i18n_ucnv_from_unicode(cnv, &dest, dest_limit, &src, src_limit, 0, true);
	i18n_ucnv_destroy(cnv);

	*byte_length = byte_count;
	return bytes;
}
