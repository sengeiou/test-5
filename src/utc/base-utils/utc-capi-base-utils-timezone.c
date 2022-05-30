//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

static int ret = I18N_ERROR_NONE;
static i18n_timezone_h timezone = NULL;

/**
 * @function        utc_capi_base_utils_timezone_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_timezone_startup(void)
{
}

/**
 * @function        utc_capi_base_utils_timezone_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_timezone_cleanup(void)
{
    if(NULL != timezone) {
        i18n_timezone_destroy(timezone);
        timezone = NULL;
    }
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_create_unknown_p
 * @since_tizen     2.3
 * @description     Creates unknown timezone, and checks error value.
 */
int utc_capi_base_utils_i18n_timezone_create_unknown_p(void)
{
    ret = i18n_timezone_create_unknown(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_create_unknown_n
 * @since_tizen     2.3
 * @description     Creates timezone with invalid handle.
 */
int utc_capi_base_utils_i18n_timezone_create_unknown_n(void)
{
    ret = i18n_timezone_create_unknown(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_create_gmt_p
 * @since_tizen     2.3
 * @description     Creates GMT timezone, and checks error value.
 */
int utc_capi_base_utils_i18n_timezone_create_gmt_p(void)
{
    ret = i18n_timezone_create_gmt(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_create_gmt_n
 * @since_tizen     2.3
 * @description     Creates timezone without handle and checks error value.
 */
int utc_capi_base_utils_i18n_timezone_create_gmt_n(void)
{
    ret = i18n_timezone_create_gmt(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_create_p
 * @since_tizen     2.3
 * @description     Creates GMT timezone for London and checks error value.
 */
int utc_capi_base_utils_i18n_timezone_create_p(void)
{
    ret = i18n_timezone_create(&timezone, "Europe/London");
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_create_p2
 * @since_tizen     2.3
 * @description     Creates GMT default timezone and checks error value.
 */
int utc_capi_base_utils_i18n_timezone_create_p2(void)
{
    ret = i18n_timezone_create(&timezone, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    char *timezone_id;
    ret = i18n_timezone_get_id(timezone, &timezone_id);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(strcmp(timezone_id, I18N_UCALENDAR_UNKNOWN_ZONE_ID), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_create_n
 * @since_tizen     2.3
 * @description     Creates timezone without handle, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_create_n(void)
{
    ret = i18n_timezone_create(NULL, "Europe/London");
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_destroy_p
 * @since_tizen     2.3
 * @description     Creates timezone, destroys it and checks error value.
 */
int utc_capi_base_utils_i18n_timezone_destroy_p(void)
{
    ret = i18n_timezone_create_gmt(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_destroy(timezone);
    timezone = NULL;
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_destroy_n
 * @since_tizen     2.3
 * @description     Destroys NULL timezone.
 */
int utc_capi_base_utils_i18n_timezone_destroy_n(void)
{
    ret = i18n_timezone_destroy(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

bool timezone_cb(const char *timezone_id, void *user_data)
{
    fprintf(stderr, "timezone_id : %s", timezone_id);
    return false;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_foreach_timezone_id_by_region_p
 * @since_tizen     2.3
 * @description     Gets all timezones with specified region
 *                  and checks error value.
 */
int utc_capi_base_utils_i18n_timezone_foreach_timezone_id_by_region_p(void)
{
    i18n_system_timezone_type_e type = I18N_UCALENDAR_ZONE_TYPE_ANY;

    for(; type <= I18N_UCALENDAR_ZONE_TYPE_CANONICAL_LOCATION; type++) {
        ret = i18n_timezone_foreach_timezone_id_by_region(type, "US", NULL, timezone_cb, NULL);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_foreach_timezone_id_by_region_n
 * @since_tizen     2.3
 * @description     Gets all timezones with false region, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_foreach_timezone_id_by_region_n(void)
{
    const char *region = "PST";
    int32_t raw_offset = 5 * 60 * 60 * 1000;

    ret = i18n_timezone_foreach_timezone_id_by_region(I18N_UCALENDAR_ZONE_TYPE_ANY, region, &raw_offset, NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_foreach_timezone_id_p
 * @since_tizen     2.3
 * @description     Gets all timezone and checks error value.
 */
int utc_capi_base_utils_i18n_timezone_foreach_timezone_id_p(void)
{
    ret = i18n_timezone_foreach_timezone_id(timezone_cb, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_foreach_timezone_id_n
 * @since_tizen     2.3
 * @description     Gets timezones with invalid callback, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_foreach_timezone_id_n(void)
{
    ret = i18n_timezone_foreach_timezone_id(NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_foreach_timezone_id_with_offset_p
 * @since_tizen     2.3
 * @description     Gets timezones with specified offset and checks error value.
 */
int utc_capi_base_utils_i18n_timezone_foreach_timezone_id_with_offset_p(void)
{
    int32_t raw_offset = 3600000;

    ret = i18n_timezone_foreach_timezone_id_with_offset(raw_offset, timezone_cb, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_foreach_timezone_id_with_offset_n
 * @since_tizen     2.3
 * @description     Gets timezones with offset without callback parameter,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_foreach_timezone_id_with_offset_n(void)
{
    int32_t raw_offset = 3600000;

    ret = i18n_timezone_foreach_timezone_id_with_offset(raw_offset, NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_foreach_timezone_id_by_country_p
 * @since_tizen     2.3
 * @description     Gets timezones of default country and checks error value.
 */
int utc_capi_base_utils_i18n_timezone_foreach_timezone_id_by_country_p(void)
{
    ret = i18n_timezone_foreach_timezone_id_by_country(NULL, timezone_cb, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_foreach_timezone_id_by_country_n
 * @since_tizen     2.3
 * @description     Gets all timezones of country without any parameter.
 */
int utc_capi_base_utils_i18n_timezone_foreach_timezone_id_by_country_n(void)
{
    ret = i18n_timezone_foreach_timezone_id_by_country(NULL, NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_count_equivalent_ids_p
 * @since_tizen     2.3
 * @description     Counts of IDs with the same zone is obtained and checks error value.
 */
int utc_capi_base_utils_i18n_timezone_count_equivalent_ids_p(void)
{
    const char *timezone_id = "Europe/London";
    int32_t count;

    ret = i18n_timezone_count_equivalent_ids(timezone_id, &count);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_count_equivalent_ids_n
 * @since_tizen     2.3
 * @description     Count of IDs with the same is obtained without timezone handle,
 *                  that's why I18N_ERROR_INVALID_PARAMETER is expected.
 */
int utc_capi_base_utils_i18n_timezone_count_equivalent_ids_n(void)
{
    int32_t count;

    ret = i18n_timezone_count_equivalent_ids(NULL, &count);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_equivalent_id_p
 * @since_tizen     2.3
 * @description     Gets IDs with the same timezone.
 */
int utc_capi_base_utils_i18n_timezone_get_equivalent_id_p(void)
{
    const char *timezone_id = "PST";
    int32_t index = 0;
    char *equivalent_timezone_id;

    ret = i18n_timezone_get_equivalent_id(timezone_id, index, &equivalent_timezone_id);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_equivalent_id_n
 * @since_tizen     2.3
 * @description     Gets IDs with the no timezone handle, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_equivalent_id_n(void)
{
    int32_t index = 0;
    char *equivalent_timezone_id;

    ret = i18n_timezone_get_equivalent_id(NULL, index, &equivalent_timezone_id);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_equivalent_id_n2
 * @since_tizen     2.3
 * @description     Gets IDs with the false timezone, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_equivalent_id_n2(void)
{
    const char *timezone_id = "PST";
    char *equivalent_timezone_id;

    ret = i18n_timezone_get_equivalent_id(timezone_id, -1, &equivalent_timezone_id);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_equivalent_id_n3
 * @since_tizen     2.3
 * @description     Gets IDs without count variable, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_equivalent_id_n3(void)
{
    const char *timezone_id = "PST";
    int32_t index = 0;

    ret = i18n_timezone_get_equivalent_id(timezone_id, index, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_create_default_p
 * @since_tizen     2.3
 * @description     Creates default timezone and checks error value.
 */
int utc_capi_base_utils_i18n_timezone_create_default_p(void)
{
    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_create_default_n
 * @since_tizen     2.3
 * @description     Creates default timezone without handle, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_create_default_n(void)
{
    ret = i18n_timezone_create_default(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_set_default_p
 * @since_tizen     2.3
 * @description     Create timezone handle for default timezone,
 *                  set it as default and checks error value.
 */
int utc_capi_base_utils_i18n_timezone_set_default_p(void)
{
    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_set_default(timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_set_default_n
 * @since_tizen     2.3
 * @description     Set invalid timezone as default, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_set_default_n(void)
{
    ret = i18n_timezone_set_default(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_tzdata_version_p
 * @since_tizen     2.3
 * @description     Gets timezone data version and checks whether no error occured.
 */
int utc_capi_base_utils_i18n_timezone_get_tzdata_version_p(void)
{
    const char *tzdata_version = i18n_timezone_get_tzdata_version();

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(tzdata_version, NULL);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_region_p
 * @since_tizen     2.3
 * @description     Gets timezone of specified region.
 */
int utc_capi_base_utils_i18n_timezone_get_region_p(void)
{
    const char *timezone_id = "Europe/London";
    int32_t region_capacity = 64;
    char region[region_capacity];
    int32_t region_len;

    ret = i18n_timezone_get_region(timezone_id, region, &region_len, region_capacity);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_region_n
 * @since_tizen     2.3
 * @description     Gets timezone of not specified region, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_region_n(void)
{
    int32_t region_capacity = 64;
    char region[region_capacity];
    int32_t region_len;

    ret = i18n_timezone_get_region(NULL, region, &region_len, region_capacity);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_region_n2
 * @since_tizen     2.3
 * @description     Gets timezone of specified region with invalid
 *                  output buffer, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_region_n2(void)
{
    const char *timezone_id = "Europe/London";
    int32_t region_len;
    int32_t region_capacity = 64;

    ret = i18n_timezone_get_region(timezone_id, NULL, &region_len, region_capacity);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_region_n3
 * @since_tizen     2.3
 * @description     Gets timezone of specified region with
 *                  invalid length of output buffer, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_region_n3(void)
{
    const char *timezone_id = "Europe/London";
    char region[64];
    int32_t region_capacity = 64;

    ret = i18n_timezone_get_region(timezone_id, region, NULL, region_capacity);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_region_n4
 * @since_tizen     2.3
 * @description     Gets timezone of specified region without output capacity parameter,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_region_n4(void)
{
    const char *timezone_id = "Europe/London";
    char region[64];
    int32_t region_len;

    ret = i18n_timezone_get_region(timezone_id, region, &region_len, -1);
    assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_offset_with_date_p
 * @since_tizen     2.3
 * @description     Gets the offset of timezone in specified date and
 *                  checks whether no error occurred.
 *
 */
int utc_capi_base_utils_i18n_timezone_get_offset_with_date_p(void)
{
    i18n_timezone_h timezone = NULL;
    char timezone_id[10];
    int gmt = -12;
    for(; gmt < 15; gmt++) {
        snprintf(timezone_id, 10, "GMT%d:00", gmt);
        ret = i18n_timezone_create(&timezone, timezone_id);
        assert_eq(ret, I18N_ERROR_NONE);

        i18n_udate now;
        ret = i18n_ucalendar_get_now(&now);
        assert_eq(ret, I18N_ERROR_NONE);

        int32_t raw_offset = 0;
        int32_t dst_offset = 0;

        i18n_udate udate = now / 2;
        i18n_udate end_udate = (3 * now) / 2;
        for(; udate < end_udate; udate += now / 4) {
            ret = i18n_timezone_get_offset_with_date(timezone, udate, true, &raw_offset, &dst_offset);
            assert_eq(ret, I18N_ERROR_NONE);

            ret = i18n_timezone_get_offset_with_date(timezone, udate, false, &raw_offset, &dst_offset);
            assert_eq(ret, I18N_ERROR_NONE);
        }
        ret = i18n_timezone_destroy(timezone);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_offset_with_date_n
 * @since_tizen     2.3
 * @description     Gets the offset of timezone in specified date
 *                  without known timezone, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_offset_with_date_n(void)
{
    i18n_udate udate;
    i18n_ubool local = false;
    int32_t raw_offset = 0;
    int32_t dst_offset = 0;

    ret = i18n_ucalendar_get_now(&udate);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_get_offset_with_date(NULL, udate, local, &raw_offset, &dst_offset);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_offset_with_date_n2
 * @since_tizen     2.3
 * @description     Gets the offset of timezone in specified date
 *                  without output parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_offset_with_date_n2(void)
{
    if(NULL != timezone) {
        ret = i18n_timezone_destroy(timezone);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    ret = i18n_timezone_create(&timezone, "GMT+1:00");
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_udate udate;
    i18n_ubool local = false;
    int32_t dst_offset = 0;

    ret = i18n_ucalendar_get_now(&udate);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_get_offset_with_date(timezone, udate, local, NULL, &dst_offset);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_offset_with_date_n3
 * @since_tizen     2.3
 * @description     Gets the offset of timezone in specified date
 *                  without output parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_offset_with_date_n3(void)
{
    if(NULL != timezone) {
        ret = i18n_timezone_destroy(timezone);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    ret = i18n_timezone_create(&timezone, "GMT+1:00");
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_udate udate;
    i18n_ubool local = false;
    int32_t raw_offset = 0;

    ret = i18n_ucalendar_get_now(&udate);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_get_offset_with_date(timezone, udate, local, &raw_offset, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_set_raw_offset_p
 * @since_tizen     2.3
 * @description     Set the raw offset of given timezone, and
 *                  check whether no error occurred.
 */
int utc_capi_base_utils_i18n_timezone_set_raw_offset_p(void)
{
    int32_t offset_milliseconds = 3600000;
    i18n_timezone_h timezone = NULL;
    char timezone_id[10];
    int gmt = -12;
    for(; gmt < 15; gmt++) {
        snprintf(timezone_id, 10, "GMT%d:00", gmt);
        ret = i18n_timezone_create(&timezone, timezone_id);
        assert_eq(ret, I18N_ERROR_NONE);

        ret = i18n_timezone_set_raw_offset(timezone, offset_milliseconds);
        assert_eq(ret, I18N_ERROR_NONE);

        ret = i18n_timezone_destroy(timezone);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_set_raw_offset_n
 * @since_tizen     2.3
 * @description     Set the raw offset of timezone
 *                  without timezone parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_set_raw_offset_n(void)
{
    int32_t offset_milliseconds = 3600000;

    ret = i18n_timezone_set_raw_offset(NULL, offset_milliseconds);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_raw_offset_p
 * @since_tizen     2.3
 * @description     Gets the raw offset of timezone
 *                  check whether no error occurred.
 */
int utc_capi_base_utils_i18n_timezone_get_raw_offset_p(void)
{
    int32_t offset_milliseconds;
    i18n_timezone_h timezone = NULL;
    char timezone_id[10];
    int gmt = -12;
    for(; gmt < 15; gmt++) {
        snprintf(timezone_id, 10, "GMT%d:00", gmt);
        ret = i18n_timezone_create(&timezone, timezone_id);
        assert_eq(ret, I18N_ERROR_NONE);

        ret = i18n_timezone_get_raw_offset(timezone, &offset_milliseconds);
        assert_eq(ret, I18N_ERROR_NONE);

        ret = i18n_timezone_destroy(timezone);
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_raw_offset_n
 * @since_tizen     2.3
 * @description     Gets the raw offset of timezone
 *                  without timezone parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_raw_offset_n(void)
{
    int32_t offset_milliseconds;

    ret = i18n_timezone_get_raw_offset(NULL, &offset_milliseconds);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_raw_offset_n2
 * @since_tizen     2.3
 * @description     Gets the raw offset of timezone
 *                  without output parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_raw_offset_n2(void)
{
    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_get_raw_offset(timezone, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_id_p
 * @since_tizen     2.3
 * @description     Gets the id of timezone
 *                  check whether no error occurred.
 */
int utc_capi_base_utils_i18n_timezone_get_id_p(void)
{
    char *timezone_id;

    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_get_id(timezone, &timezone_id);
    assert_eq(ret, I18N_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_id_n
 * @since_tizen     2.3
 * @description     Gets the id of timezone without timezone parameter,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_id_n(void)
{
    char *timezone_id;

    ret = i18n_timezone_get_id(NULL, &timezone_id);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_id_n2
 * @since_tizen     2.3
 * @description     Gets the id of timezone without output parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_id_n2(void)
{
    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_get_id(timezone, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_set_id_p
 * @since_tizen     2.3
 * @description     Set the id of timezone check whether no error occurred.
 */
int utc_capi_base_utils_i18n_timezone_set_id_p(void)
{
    const char *timezone_id = "Europe/London";

    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_set_id(timezone, timezone_id);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_set_id_n
 * @since_tizen     2.3
 * @description     Set the id of timezone without timezone parameter,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_set_id_n(void)
{
    const char *timezone_id = "2100";

    ret = i18n_timezone_set_id(NULL, timezone_id);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_set_id_n2
 * @since_tizen     2.3
 * @description     Set the id of timezone without timezone parameter,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_set_id_n2(void)
{
    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_set_id(timezone, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_display_name_p
 * @since_tizen     2.3
 * @description     Gets the display name of timezone and
 *                  check whether no error occurred.
 */
int utc_capi_base_utils_i18n_timezone_get_display_name_p(void)
{
    char *displayname;
    i18n_timezone_h timezone = NULL;
    char timezone_id[10];
    int gmt = -12;
    for(; gmt < 15; gmt++) {
        snprintf(timezone_id, 10, "GMT%d:00", gmt);
        ret = i18n_timezone_create(&timezone, timezone_id);
        assert_eq(ret, I18N_ERROR_NONE);

        ret = i18n_timezone_get_display_name(timezone, &displayname);
        assert_eq(ret, I18N_ERROR_NONE);

        ret = i18n_timezone_destroy(timezone);
        timezone = NULL;
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_display_name_n
 * @since_tizen     2.3
 * @description     Gets the display name of timezone
 *                  without timezone parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_display_name_n(void)
{
    char *displayname;

    ret = i18n_timezone_get_display_name(NULL, &displayname);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_display_name_n2
 * @since_tizen     2.3
 * @description     Gets the display name of timezone date
 *                  without output parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_display_name_n2(void)
{
    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_get_display_name(timezone, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_display_name_with_locale_p
 * @since_tizen     2.3
 * @description     Gets the display name with locale of timezone and
 *                  check whether no error occurred.
 */
int utc_capi_base_utils_i18n_timezone_get_display_name_with_locale_p(void)
{
    const char *language = I18N_ULOCALE_ENGLISH;
    const char *country = "US";
    char *displayname;
    i18n_timezone_h timezone = NULL;
    char timezone_id[10];
    int gmt = -12;
    for(; gmt < 15; gmt++) {
        snprintf(timezone_id, 10, "GMT%d:00", gmt);
        ret = i18n_timezone_create(&timezone, timezone_id);
        assert_eq(ret, I18N_ERROR_NONE);

        ret = i18n_timezone_get_display_name_with_locale(timezone, language, country, &displayname);
        assert_eq(ret, I18N_ERROR_NONE);

        ret = i18n_timezone_destroy(timezone);
        timezone = NULL;
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_display_name_with_locale_n
 * @since_tizen     2.3
 * @description     Gets the display name with locale of timezone
 *                  without timezone parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_display_name_with_locale_n(void)
{
    const char *language = I18N_ULOCALE_ENGLISH;
    const char *country = "US";
    char *displayname;

    ret = i18n_timezone_get_display_name_with_locale(NULL, language, country, &displayname);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_display_name_with_locale_n2
 * @since_tizen     2.3
 * @description     Gets the display name with locale of timezone
 *                  without output parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_display_name_with_locale_n2(void)
{
    const char *language = I18N_ULOCALE_ENGLISH;
    const char *country = "US";

    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_get_display_name_with_locale(timezone, language, country, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_display_name_with_type_p
 * @since_tizen     2.3
 * @description     Gets the display name with type of timezone and
 *                  check whether no error occurred.
 */
int utc_capi_base_utils_i18n_timezone_get_display_name_with_type_p(void)
{
    i18n_timezone_h timezone = NULL;
    i18n_ubool daylight = true;
    i18n_timezone_display_type_e type = I18N_TIMEZONE_DISPLAY_TYPE_SHORT;
    char *displayname;
    char timezone_id[10];
    int gmt = -12;
    for(; gmt < 15; gmt++) {
        snprintf(timezone_id, 10, "GMT%d:00", gmt);
        ret = i18n_timezone_create(&timezone, timezone_id);
        assert_eq(ret, I18N_ERROR_NONE);

        for(; type <= I18N_TIMEZONE_DISPLAY_TYPE_GENERIC_LOCATION; type++) {
            ret = i18n_timezone_get_display_name_with_type(timezone, daylight, type, &displayname);
            assert_eq(ret, I18N_ERROR_NONE);
        }

        ret = i18n_timezone_destroy(timezone);
        timezone = NULL;
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_display_name_with_type_n
 * @since_tizen     2.3
 * @description     Gets the display name with type of timezone
 *                  without timezone parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_display_name_with_type_n(void)
{
    i18n_ubool daylight = true;
    i18n_timezone_display_type_e style = I18N_TIMEZONE_DISPLAY_TYPE_LONG;
    char *displayname;

    ret = i18n_timezone_get_display_name_with_type(NULL, daylight, style, &displayname);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_display_name_with_type_n2
 * @since_tizen     2.3
 * @description     Gets the display name with type of timezone
 *                  without output parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_display_name_with_type_n2(void)
{
    i18n_ubool daylight = true;
    i18n_timezone_display_type_e style = I18N_TIMEZONE_DISPLAY_TYPE_LONG;

    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_get_display_name_with_type(timezone, daylight, style, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_display_name_with_type_locale_p
 * @since_tizen     2.3
 * @description     Gets the display name of timezone an with type
 *                  check whether no error occurred.
 */
int utc_capi_base_utils_i18n_timezone_get_display_name_with_type_locale_p(void)
{
    i18n_ubool daylight = true;
    i18n_timezone_display_type_e style = I18N_TIMEZONE_DISPLAY_TYPE_LONG;
    const char *language = I18N_ULOCALE_ENGLISH;
    const char *country = "US";
    char *displayname;

    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_get_display_name_with_type_locale(timezone, daylight, style, language, country, &displayname);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_display_name_with_type_locale_n
 * @since_tizen     2.3
 * @description     Gets the display name of timezon with type
 *                  without timezone parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_display_name_with_type_locale_n(void)
{
    i18n_ubool daylight = true;
    i18n_timezone_display_type_e style = I18N_TIMEZONE_DISPLAY_TYPE_SHORT;
    const char *language = I18N_ULOCALE_ENGLISH;
    const char *country = "US";
    char *displayname;

    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    for(; style <= I18N_TIMEZONE_DISPLAY_TYPE_GENERIC_LOCATION; style++) {
        ret = i18n_timezone_get_display_name_with_type_locale(NULL, daylight, style, language, country, &displayname);
        assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_display_name_with_type_locale_n2
 * @since_tizen     2.3
 * @description     Gets the display name of timezon with type
 *                  without output parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_display_name_with_type_locale_n2(void)
{
    i18n_ubool daylight = true;
    i18n_timezone_display_type_e style = I18N_TIMEZONE_DISPLAY_TYPE_SHORT;
    const char *language = I18N_ULOCALE_ENGLISH;
    const char *country = "US";

    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    for(; style <= I18N_TIMEZONE_DISPLAY_TYPE_GENERIC_LOCATION; style++) {
        ret = i18n_timezone_get_display_name_with_type_locale(timezone, daylight, style, language, country, NULL);
        assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_use_daylight_time_p
 * @since_tizen     2.3
 * @description     Use daylight time of timezone and
 *                  check whether no error occurred.
 */
int utc_capi_base_utils_i18n_timezone_use_daylight_time_p(void)
{
    i18n_ubool daylight_time;

    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_use_daylight_time(timezone, &daylight_time);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_use_daylight_time_n
 * @since_tizen     2.3
 * @description     Use daylight time of timezone
 *                  without timezone parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_use_daylight_time_n(void)
{
    i18n_ubool daylight_time;

    ret = i18n_timezone_use_daylight_time(NULL, &daylight_time);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_use_daylight_time_n2
 * @since_tizen     2.3
 * @description     Use daylight time of timezone
 *                  without output parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_use_daylight_time_n2(void)
{
    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_use_daylight_time(timezone, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_has_same_rule_p
 * @since_tizen     2.3
 * @description     Check whether the timezone have the same rule, and
 *                  whether no error occurred.
 */
int utc_capi_base_utils_i18n_timezone_has_same_rule_p(void)
{
    i18n_timezone_h other;
    i18n_ubool same_rule;

    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_create_default(&other);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_has_same_rule(timezone, other, &same_rule);
    i18n_timezone_destroy(other);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_has_same_rule_n
 * @since_tizen     2.3
 * @description     Check whether the timezone have the same rule
 *                  without timezone parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_has_same_rule_n(void)
{
    i18n_timezone_h other;
    i18n_ubool same_rule;

    ret = i18n_timezone_create_default(&other);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_has_same_rule(NULL, other, &same_rule);
    i18n_timezone_destroy(other);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_has_same_rule_n2
 * @since_tizen     2.3
 * @description     Check whether the timezone have the same rule
 *                  without other timezone parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_has_same_rule_n2(void)
{
    i18n_ubool same_rule;

    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_has_same_rule(timezone, NULL, &same_rule);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_has_same_rule_n3
 * @since_tizen     2.3
 * @description     Check whether the timezone have the same rule
 *                  without output parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_has_same_rule_n3(void)
{
    i18n_timezone_h other;

    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_create_default(&other);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_has_same_rule(timezone, other, NULL);
    i18n_timezone_destroy(other);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_clone_p
 * @since_tizen     2.3
 * @description     Clone timezone and check whether no error occurred.
 */
int utc_capi_base_utils_i18n_timezone_clone_p(void)
{
    i18n_timezone_h clone;

    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_clone(timezone, &clone);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_clone_n
 * @since_tizen     2.3
 * @description     Clone timezone and without timezone parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_clone_n(void)
{
    i18n_timezone_h clone;

    ret = i18n_timezone_clone(NULL, &clone);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_clone_n2
 * @since_tizen     2.3
 * @description     Clone timezone without output parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_clone_n2(void)
{
    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_clone(timezone, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_dst_savings_p
 * @since_tizen     2.3
 * @description     Gets the DST saving of timezone and
 *                  check whether no error occurred.
 */
int utc_capi_base_utils_i18n_timezone_get_dst_savings_p(void)
{
    int32_t dst_saving;

    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_get_dst_savings(timezone, &dst_saving);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_dst_savings_n
 * @since_tizen     2.3
 * @description     Gets the DST saving of timezone
 *                  without timezone parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_dst_savings_n(void)
{
    int32_t dst_saving;

    ret = i18n_timezone_get_dst_savings(NULL, &dst_saving);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_dst_savings_n2
 * @since_tizen     2.3
 * @description     Gets the DST saving of timezone
 *                  without output parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_dst_savings_n2(void)
{
    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_get_dst_savings(timezone, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_detect_host_timezone_p
 * @since_tizen     3.0
 * @description     Gets the time zone from the current host system configuration
 * 	                and checks whether no error occurred.
 */
int utc_capi_base_utils_i18n_timezone_detect_host_timezone_p(void)
{
    ret = i18n_timezone_detect_host_timezone(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(timezone, NULL);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_detect_host_timezone_n
 * @since_tizen     3.0
 * @description     Calls i18n_timezone_detect_host_timezone with invalid @a timezone
 *                  and checks whether the function returns an error code.
 */
int utc_capi_base_utils_i18n_timezone_detect_host_timezone_n(void)
{
    ret = i18n_timezone_detect_host_timezone(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_timezone_get_display_name_with_locale_id_p
 * @since_tizen 5.0
 * @description Calls i18n_timezone_get_display_name_with_locale_id and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_timezone_get_display_name_with_locale_id_p(void)
{
    const char *locale_id = "en_US";
    char *displayname = NULL;
    char timezone_id[10];
    int gmt = -12;
    for(; gmt < 15; gmt++) {
        snprintf(timezone_id, 10, "GMT%d:00", gmt);
        ret = i18n_timezone_create(&timezone, timezone_id);
        assert_eq(ret, I18N_ERROR_NONE);

        ret = i18n_timezone_get_display_name_with_locale_id(timezone, locale_id, &displayname);
        assert_eq(ret, I18N_ERROR_NONE);
        free(displayname);

        ret = i18n_timezone_destroy(timezone);
        timezone = NULL;
        assert_eq(ret, I18N_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_display_name_with_locale_id_n
 * @since_tizen     5.0
 * @description     Gets the display name of timezone
 *                  without timezone parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_display_name_with_locale_id_n(void)
{
    const char *locale_id = "en_US";
    char *displayname;

    ret = i18n_timezone_get_display_name_with_locale_id(NULL, locale_id, &displayname);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_display_name_with_locale_id_n2
 * @since_tizen     5.0
 * @description     Gets the display name of timezone
 *                  without displayname parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_display_name_with_locale_id_n2(void)
{
    const char *locale_id = "en_US";

    ret = i18n_timezone_get_display_name_with_locale_id(timezone, locale_id, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_timezone_get_display_name_with_type_locale_id_p
 * @since_tizen 5.0
 * @description Calls i18n_timezone_get_display_name_with_type_locale_id and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_timezone_get_display_name_with_type_locale_id_p(void)
{
    const char *locale_id = "en_US";
    i18n_ubool daylight = true;
    i18n_timezone_display_type_e style = I18N_TIMEZONE_DISPLAY_TYPE_LONG;
    char *displayname;

    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_timezone_get_display_name_with_type_locale_id(timezone, daylight, style, locale_id, &displayname);
    assert_eq(ret, I18N_ERROR_NONE);
    free(displayname);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_display_name_with_type_locale_id_n
 * @since_tizen     5.0
 * @description     Gets the display name of timezon with type
 *                  without timezone parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_display_name_with_type_locale_id_n(void)
{
    i18n_ubool daylight = true;
    i18n_timezone_display_type_e style = I18N_TIMEZONE_DISPLAY_TYPE_SHORT;
    const char *locale_id = "en_US";
    char *displayname;

    for(; style <= I18N_TIMEZONE_DISPLAY_TYPE_GENERIC_LOCATION; style++) {
        ret = i18n_timezone_get_display_name_with_type_locale_id(NULL, daylight, style, locale_id, &displayname);
        assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    }

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_timezone_get_display_name_with_type_locale_id_n2
 * @since_tizen     5.0
 * @description     Gets the display name of timezon with type
 *                  without displayname parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_timezone_get_display_name_with_type_locale_id_n2(void)
{
    i18n_ubool daylight = true;
    i18n_timezone_display_type_e style = I18N_TIMEZONE_DISPLAY_TYPE_SHORT;
    const char *locale_id = "en_US";

    ret = i18n_timezone_create_default(&timezone);
    assert_eq(ret, I18N_ERROR_NONE);

    for(; style <= I18N_TIMEZONE_DISPLAY_TYPE_GENERIC_LOCATION; style++) {
        ret = i18n_timezone_get_display_name_with_type_locale_id(timezone, daylight, style, locale_id, NULL);
        assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    }

    return 0;
}
