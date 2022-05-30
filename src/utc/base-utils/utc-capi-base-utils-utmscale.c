#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

static int ret = I18N_ERROR_NONE;

/**
 * @function        utc_capi_base_utils_utmscale_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
*/
void utc_capi_base_utils_utmscale_startup(void)
{
}

/**
 * @function        utc_capi_base_utils_utmscale_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
*/
void utc_capi_base_utils_utmscale_cleanup(void)
{
}

/**
 * @testcase utc_capi_base_utils_i18n_utmscale_get_time_scale_value_p
 * @since_tizen 3.0
 * @description Calls i18n_utmscale_get_time_scale_value and checks whether function
 *              succeeded.
*/
int utc_capi_base_utils_i18n_utmscale_get_time_scale_value_p(void)
{
	int64_t value = 0;
	ret = i18n_utmscale_get_time_scale_value(I18N_UTMSCALE_JAVA_TIME, I18N_UTMSCALE_VALUE_UNITS, &value);

	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(value, 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utmscale_get_time_scale_value_n
 * @since_tizen 3.0
 * @description Calls i18n_utmscale_get_time_scale_value passing invalid index and
 *              checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_utmscale_get_time_scale_value_n(void)
{
	int64_t value = 0;
	ret = i18n_utmscale_get_time_scale_value(-1, I18N_UTMSCALE_VALUE_UNITS, &value);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utmscale_get_time_scale_value_n2
 * @since_tizen 3.0
 * @description Calls i18n_utmscale_get_time_scale_value passing invalid index and
 *              checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_utmscale_get_time_scale_value_n2(void)
{
	int64_t value = 0;
	ret = i18n_utmscale_get_time_scale_value(I18N_UTMSCALE_JAVA_TIME, -1, &value);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utmscale_get_time_scale_value_n3
 * @since_tizen 3.0
 * @description Calls i18n_utmscale_get_time_scale_value passing invalid index and
 *              checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_utmscale_get_time_scale_value_n3(void)
{
	ret = i18n_utmscale_get_time_scale_value(I18N_UTMSCALE_JAVA_TIME, I18N_UTMSCALE_VALUE_UNITS, NULL);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utmscale_from_int64_p
 * @since_tizen 3.0
 * @description Calls i18n_utmscale_from_int64 and checks whether function
 *              succeeded.
*/
int utc_capi_base_utils_i18n_utmscale_from_int64_p(void)
{
	int64_t value = 0;
	ret = i18n_utmscale_get_time_scale_value(I18N_UTMSCALE_ICU4C_TIME, I18N_UTMSCALE_VALUE_FROM_MIN, &value);

	int64_t universal_time = 0;
	ret = i18n_utmscale_from_int64(value, I18N_UTMSCALE_ICU4C_TIME, &universal_time);

	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(universal_time, 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utmscale_from_int64_n
 * @since_tizen 3.0
 * @description Calls i18n_utmscale_from_int64 passing invalid index and
 *              checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_utmscale_from_int64_n(void)
{
	int64_t value = 0;
	ret = i18n_utmscale_get_time_scale_value(I18N_UTMSCALE_ICU4C_TIME, I18N_UTMSCALE_VALUE_FROM_MIN, &value);

	int64_t universal_time = 0;
	ret = i18n_utmscale_from_int64(value, -1, &universal_time);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utmscale_from_int64_n2
 * @since_tizen 3.0
 * @description Calls i18n_utmscale_from_int64 passing invalid index and
 *              checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_utmscale_from_int64_n2(void)
{
	int64_t value = 0;
	ret = i18n_utmscale_get_time_scale_value(I18N_UTMSCALE_ICU4C_TIME, I18N_UTMSCALE_VALUE_FROM_MIN, &value);

	//int64_t universal_time = 0;
	ret = i18n_utmscale_from_int64(value, I18N_UTMSCALE_JAVA_TIME, NULL);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utmscale_to_int64_p
 * @since_tizen 3.0
 * @description Calls i18n_utmscale_to_int64 and checks whether function
 *              succeeded.
*/
int utc_capi_base_utils_i18n_utmscale_to_int64_p(void)
{
	int64_t value = 0;
	ret = i18n_utmscale_get_time_scale_value(I18N_UTMSCALE_ICU4C_TIME, I18N_UTMSCALE_VALUE_FROM_MIN, &value);

	int64_t other_time = 0;
	ret = i18n_utmscale_to_int64(value, I18N_UTMSCALE_ICU4C_TIME, &other_time);

	assert_eq(ret, I18N_ERROR_NONE);
	assert_neq(other_time, 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utmscale_to_int64_n
 * @since_tizen 3.0
 * @description Calls i18n_utmscale_to_int64 passing invalid index and
 *              checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_utmscale_to_int64_n(void)
{
	int64_t value = 0;
	ret = i18n_utmscale_get_time_scale_value(I18N_UTMSCALE_ICU4C_TIME, I18N_UTMSCALE_VALUE_FROM_MIN, &value);

	int64_t other_time = 0;
	ret = i18n_utmscale_to_int64(value, -1, &other_time);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_utmscale_to_int64_n2
 * @since_tizen 3.0
 * @description Calls i18n_utmscale_to_int64 passing invalid index and
 *              checks for an invalid parameter error code.
*/
int utc_capi_base_utils_i18n_utmscale_to_int64_n2(void)
{
	int64_t value = 0;
	ret = i18n_utmscale_get_time_scale_value(I18N_UTMSCALE_ICU4C_TIME, I18N_UTMSCALE_VALUE_FROM_MIN, &value);

	ret = i18n_utmscale_to_int64(value, I18N_UTMSCALE_JAVA_TIME, NULL);

	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}
