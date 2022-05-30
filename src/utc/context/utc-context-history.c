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
#include "utc-context-common.h"
#include <stdio.h>
#include <time.h>
//#include <alarm.h>
#include <string.h>
#include <unistd.h>
#include <context_history.h>
#include "tct_app_common.h"

//& set: Context - History
#define HISTORY_FEATURE		"http://tizen.org/feature/app_history"
#if defined(MOBILE) || defined(TIZENIOT)
#define NUM_HISTORY_DATA_TYPE 12
#endif	//MOBILE
#ifdef WEARABLE
#define NUM_HISTORY_DATA_TYPE 4
#endif	//WEARABLE
static context_history_h handle = NULL;

bool history_checked = false;
bool is_history_supported = false;

static context_history_data_e history_data_enum[NUM_HISTORY_DATA_TYPE] = {
#if defined(MOBILE) || defined(TIZENIOT)
	CONTEXT_HISTORY_RECENTLY_USED_APP,
	CONTEXT_HISTORY_FREQUENTLY_USED_APP,
	CONTEXT_HISTORY_BATTERY_USAGE,
	CONTEXT_HISTORY_RECENT_BATTERY_USAGE,
	CONTEXT_HISTORY_RARELY_USED_APP,
	CONTEXT_HISTORY_PEAK_TIME_FOR_APP,
	CONTEXT_HISTORY_PEAK_TIME_FOR_MUSIC,
	CONTEXT_HISTORY_PEAK_TIME_FOR_VIDEO,
	CONTEXT_HISTORY_COMMON_SETTING_FOR_APP,
	CONTEXT_HISTORY_COMMON_SETTING_FOR_MUSIC,
	CONTEXT_HISTORY_COMMON_SETTING_FOR_VIDEO,
	CONTEXT_HISTORY_FREQUENTLY_COMMUNICATED_ADDRESS};
#endif	//MOBILE
#ifdef WEARABLE
	CONTEXT_HISTORY_RECENTLY_USED_APP,
	CONTEXT_HISTORY_FREQUENTLY_USED_APP,
	CONTEXT_HISTORY_BATTERY_USAGE,
	CONTEXT_HISTORY_RECENT_BATTERY_USAGE};
#endif	//WEARABLE

static const char *history_data_name[NUM_HISTORY_DATA_TYPE] = {
#if defined(MOBILE) || defined(TIZENIOT)
	"CONTEXT_HISTORY_RECENTLY_USED_APP",
	"CONTEXT_HISTORY_FREQUENTLY_USED_APP",
	"CONTEXT_HISTORY_BATTERY_USAGE",
	"CONTEXT_HISTORY_RECENT_BATTERY_USAGE",
	"CONTEXT_HISTORY_RARELY_USED_APP",
	"CONTEXT_HISTORY_PEAK_TIME_FOR_APP",
	"CONTEXT_HISTORY_PEAK_TIME_FOR_MUSIC",
	"CONTEXT_HISTORY_PEAK_TIME_FOR_VIDEO",
	"CONTEXT_HISTORY_COMMON_SETTING_FOR_APP",
	"CONTEXT_HISTORY_COMMON_SETTING_FOR_MUSIC",
	"CONTEXT_HISTORY_COMMON_SETTING_FOR_VIDEO",
	"CONTEXT_HISTORY_FREQUENTLY_COMMUNICATED_ADDRESS"};
#endif	//MOBILE
#ifdef WEARABLE
	"CONTEXT_HISTORY_RECENTLY_USED_APP",
	"CONTEXT_HISTORY_FREQUENTLY_USED_APP",
	"CONTEXT_HISTORY_BATTERY_USAGE",
	"CONTEXT_HISTORY_RECENT_BATTERY_USAGE"};
#endif	//WEARABLE

#define SKIP_TEST_CONTINUE(Error, CaseIdx, MaxIdx, DataName) {\
	if (is_history_supported && Error == CONTEXT_HISTORY_ERROR_NOT_SUPPORTED) {\
		PRINT_INFO("(%d/%d) Skipping this test for %s. Not supported",\
				CaseIdx, MaxIdx, DataName);\
		continue;\
	} else if (is_history_supported && Error == CONTEXT_HISTORY_ERROR_NO_DATA) {\
		PRINT_INFO("(%d/%d) Skipping this test for %s. Data not exist",\
				CaseIdx, MaxIdx, DataName);\
		continue;\
	}\
}

#define SKIP_TEST(Error, CaseIdx, MaxIdx, DataName) \
	if (is_history_supported && Error == CONTEXT_HISTORY_ERROR_NOT_SUPPORTED) {\
		PRINT_INFO("(%d/%d) Skipping this test for %s. Not supported",\
				CaseIdx, MaxIdx, DataName);\
	} else if (is_history_supported && Error == CONTEXT_HISTORY_ERROR_NO_DATA) {\
		PRINT_INFO("(%d/%d) Skipping this test for %s. Data not exist",\
				CaseIdx, MaxIdx, DataName);\
	}

/**
 * @function		utc_context_history_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_context_history_startup(void)
{
	TCT_UTCCheckInstalledApp(2, "org.tizen.testapplication", "org.tizen.helloworld");

	context_history_create(&handle);

	if (!history_checked) {
		system_info_get_platform_bool(HISTORY_FEATURE, &is_history_supported);
		history_checked = true;
	}

	if (!is_history_supported)
		PRINT_INFO("Feature(%s) is not supported", HISTORY_FEATURE);
}

/**
 * @function		utc_context_history_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_context_history_cleanup(void)
{
	if (handle) {
		context_history_destroy(handle);
		handle = NULL;
	}
}

/**
 * @testcase		utc_context_history_create_p
 * @since_tizen		2.4
 * @description		Positive test case of context_history_create()
 */
int utc_context_history_create_p(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	context_history_h history_h = NULL;

	error = context_history_create(&history_h);

	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
	context_history_destroy(history_h);

	return 0;
}

/**
 * @testcase		utc_context_history_create_n
 * @since_tizen		2.4
 * @description		Negative test case of context_history_create()
 */
int utc_context_history_create_n(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;

	error = context_history_create(NULL);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_context_history_destroy_p
 * @since_tizen		2.4
 * @description		Positive test case of context_history_destroy()
 */
int utc_context_history_destroy_p(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	context_history_h history_h;

	context_history_create(&history_h);
	error = context_history_destroy(history_h);

	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_context_history_destroy_n
 * @since_tizen		2.4
 * @description		Negative test case of context_history_destroy()
 */
int utc_context_history_destroy_n(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;

	error = context_history_destroy(NULL);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_context_history_filter_create_p
 * @since_tizen		2.4
 * @description		Positive test case of context_history_filter_create()
 */
int utc_context_history_filter_create_p(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	context_history_filter_h filter = NULL;

	error = context_history_filter_create(&filter);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);

	context_history_filter_destroy(filter);

	return 0;
}

/**
 * @testcase		utc_context_history_filter_create_n
 * @since_tizen		2.4
 * @description		Negative test case of context_history_filter_create()
 */
int utc_context_history_filter_create_n(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;

	error = context_history_filter_create(NULL);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_context_history_filter_destroy_p
 * @since_tizen		2.4
 * @description		Positive test case of context_history_filter_destroy()
 */
int utc_context_history_filter_destroy_p(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	context_history_filter_h filter;

	context_history_filter_create(&filter);
	error = context_history_filter_destroy(filter);

	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_context_history_filter_destroy_n
 * @since_tizen		2.4
 * @description		Negative test case of context_history_filter_destroy()
 */
int utc_context_history_filter_destroy_n(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;

	error = context_history_filter_destroy(NULL);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_context_history_filter_set_int_p
 * @since_tizen		2.4
 * @description		Positive test case of context_history_filter_set_int()
 */
int utc_context_history_filter_set_int_p(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	context_history_filter_h filter = NULL;

	context_history_filter_create(&filter);

	error = context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_TIME_SPAN, 10);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);

	error = context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_RESULT_SIZE, 10);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);

	error = context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_START_TIME, 1433116800); // 2015.06.01 00:00:00
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);

	error = context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_END_TIME, 1433548800); // 2015.06.06. 00:00:00
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);

#if defined(MOBILE) || defined(TIZENIOT)
	error = context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_DAY_OF_WEEK, CONTEXT_HISTORY_FILTER_DAY_OF_WEEK_WEEKDAYS);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);

	error = context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_AUDIO_JACK, CONTEXT_HISTORY_FILTER_AUDIO_JACK_CONNECTED);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);

	error = context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_COMMUNICATION_TYPE, CONTEXT_HISTORY_FILTER_COMMUNICATION_TYPE_CALL);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
#endif	//MOBILE

	context_history_filter_destroy(filter);

	return 0;
}

/**
 * @testcase		utc_context_history_filter_set_int_n
 * @since_tizen		2.4
 * @description		Negative test case of context_history_filter_set_int()
 */
int utc_context_history_filter_set_int_n(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	context_history_filter_h filter = NULL;

	context_history_filter_create(&filter);

	error = context_history_filter_set_int(NULL, CONTEXT_HISTORY_FILTER_TIME_SPAN, 10);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

#if defined(MOBILE) || defined(TIZENIOT)
	// Invalid filter data type
	error = context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_APP_ID, 0);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);
#endif	//MOBILE

	// Invalid filter data
	error = context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_TIME_SPAN, -1);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

	error = context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_RESULT_SIZE, -1);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

	error = context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_START_TIME, -1);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

	error = context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_END_TIME, -1);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

#if defined(MOBILE) || defined(TIZENIOT)
	error = context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_DAY_OF_WEEK, -1);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

	error = context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_AUDIO_JACK, -1);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

	error = context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_COMMUNICATION_TYPE, -1);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);
#endif	//MOBILE

	context_history_filter_destroy(filter);

	return 0;
}

#if defined(MOBILE) || defined(TIZENIOT)
/**
 * @testcase		utc_context_history_filter_set_string_p
 * @since_tizen		2.4
 * @description		Positive test case of context_history_filter_set_string()
 */
int utc_context_history_filter_set_string_p(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	context_history_filter_h filter = NULL;

	context_history_filter_create(&filter);

	error = context_history_filter_set_string(filter, CONTEXT_HISTORY_FILTER_APP_ID, "org.tizen.testapplication");
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);

	error = context_history_filter_set_string(filter, CONTEXT_HISTORY_FILTER_WIFI_BSSID, "office");
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);

	context_history_filter_destroy(filter);

	return 0;
}

/**
 * @testcase		utc_context_history_filter_set_string_n
 * @since_tizen		2.4
 * @description		Negative test case of context_history_filter_set_string()
 */
int utc_context_history_filter_set_string_n(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	context_history_filter_h filter = NULL;

	context_history_filter_create(&filter);

	error = context_history_filter_set_string(NULL, CONTEXT_HISTORY_FILTER_APP_ID, "org.tizen.testapplication");
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

	// Invalid filter data type
	error = context_history_filter_set_string(filter, CONTEXT_HISTORY_FILTER_TIME_SPAN, "10");
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

	// Invalid filter data
	error = context_history_filter_set_string(filter, CONTEXT_HISTORY_FILTER_APP_ID, NULL);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

	error = context_history_filter_set_string(filter, CONTEXT_HISTORY_FILTER_WIFI_BSSID, NULL);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

	context_history_filter_destroy(filter);

	return 0;
}
#endif	//MOBILE

/**
 * @testcase		utc_context_history_is_supported_p
 * @since_tizen		4.0
 * @description		Positive test case of context_history_is_supported()
 */
int utc_context_history_is_supported_p(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	bool supported;
	int i;

	for (i = 0; i < NUM_HISTORY_DATA_TYPE; ++i) {
		error = context_history_is_supported(history_data_enum[i], &supported);
		if (is_history_supported && !supported)
			PRINT_INFO("(%d/%d) %s is not supported.", i + 1, NUM_HISTORY_DATA_TYPE, history_data_name[i]);

		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_context_history_is_supported_n
 * @since_tizen		4.0
 * @description		Negative test case of context_history_is_supported()
 */
int utc_context_history_is_supported_n(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;

	error = context_history_is_supported(history_data_enum[0], NULL);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_context_history_get_list_p
 * @since_tizen		2.4
 * @description		Positive test case of context_history_get_list()
 */
int utc_context_history_get_list_p(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	int i;
	context_history_list_h list;

	for (i = 0; i < NUM_HISTORY_DATA_TYPE; ++i) {
		list = NULL;

		error = context_history_get_list(handle, history_data_enum[i], NULL, &list);
		SKIP_TEST_CONTINUE(error, i + 1, NUM_HISTORY_DATA_TYPE, history_data_name[i]);

		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		HISTORY_ASSERT_IF_SUPPORTED(is_history_supported, list);

		context_history_list_destroy(list);
	}

	return 0;
}

/**
 * @testcase		utc_context_history_get_list_n
 * @since_tizen		2.4
 * @description		Negative test case of context_history_get_list()
 */
int utc_context_history_get_list_n(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	context_history_filter_h filter = NULL;
	context_history_list_h list = NULL;

	error = context_history_get_list(NULL, CONTEXT_HISTORY_FREQUENTLY_USED_APP, NULL, &list);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

	error = context_history_get_list(handle, CONTEXT_HISTORY_FREQUENTLY_USED_APP, NULL, NULL);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

#if defined(MOBILE) || defined(TIZENIOT)
	// Invalid filter
	context_history_filter_create(&filter);
	context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_TIME_SPAN, 30);
	context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_RESULT_SIZE, 10);
	context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_DAY_OF_WEEK, CONTEXT_HISTORY_FILTER_DAY_OF_WEEK_WEEKDAYS);

	error = context_history_get_list(handle, CONTEXT_HISTORY_FREQUENTLY_USED_APP, filter, &list);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);
#endif	//MOBILE

	context_history_list_destroy(list);
	context_history_filter_destroy(filter);

	return 0;
}

/**
 * @testcase		utc_context_history_list_get_count_p
 * @since_tizen		2.4
 * @description		Positive test case of context_history_list_get_count()
 */
int utc_context_history_list_get_count_p(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	int count;
	int i;
	context_history_list_h list;

	for (i = 0; i < NUM_HISTORY_DATA_TYPE; ++i) {
		list = NULL;
		count = -1;

		error = context_history_get_list(handle, history_data_enum[i], NULL, &list);
		SKIP_TEST_CONTINUE(error, i + 1, NUM_HISTORY_DATA_TYPE, history_data_name[i]);

		error = context_history_list_get_count(list, &count);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		HISTORY_ASSERT_GEQ_IF_SUPPORTED(is_history_supported, count, 0);

		context_history_list_destroy(list);
	}

	return 0;
}

/**
 * @testcase		utc_context_history_list_get_count_n
 * @since_tizen		2.4
 * @description		Negative test case of context_history_list_get_count()
 */
int utc_context_history_list_get_count_n(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	int i;
	context_history_list_h list;

	for (i = 0; i < NUM_HISTORY_DATA_TYPE; ++i) {
		list = NULL;

		error = context_history_get_list(handle, history_data_enum[i], NULL, &list);
		SKIP_TEST_CONTINUE(error, i + 1, NUM_HISTORY_DATA_TYPE, history_data_name[i]);

		error = context_history_list_get_count(list, NULL);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

		context_history_list_destroy(list);
	}

	return 0;
}

/**
 * @testcase		utc_context_history_list_get_current_p
 * @since_tizen		2.4
 * @description		Positive test case of context_history_list_get_current()
 */
int utc_context_history_list_get_current_p(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	int i;
	context_history_list_h list;
	context_history_record_h record;

	for (i = 0; i < NUM_HISTORY_DATA_TYPE; ++i) {
		list = NULL;
		record = NULL;

		error = context_history_get_list(handle, history_data_enum[i], NULL, &list);
		SKIP_TEST_CONTINUE(error, i + 1, NUM_HISTORY_DATA_TYPE, history_data_name[i]);

		error = context_history_list_get_current(list, &record);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		HISTORY_ASSERT_IF_SUPPORTED(is_history_supported, record);

		context_history_list_destroy(list);
		context_history_record_destroy(record);
	}

	return 0;
}

/**
 * @testcase		utc_context_history_list_get_current_n
 * @since_tizen		2.4
 * @description		Negative test case of context_history_list_get_current()
 */
int utc_context_history_list_get_current_n(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	int i;
	context_history_list_h list;
	context_history_record_h record;

	for (i = 0; i < NUM_HISTORY_DATA_TYPE; ++i) {
		list = NULL;
		record = NULL;

		error = context_history_get_list(handle, history_data_enum[i], NULL, &list);
		SKIP_TEST_CONTINUE(error, i + 1, NUM_HISTORY_DATA_TYPE, history_data_name[i]);

		error = context_history_list_get_current(list, NULL);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

		context_history_list_destroy(list);
		context_history_record_destroy(record);
	}

	return 0;
}

/**
 * @testcase		utc_context_history_list_move_first_p
 * @since_tizen		2.4
 * @description		Positive test case of context_history_list_move_first()
 */
int utc_context_history_list_move_first_p(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	int i;
	context_history_list_h list;

	for (i = 0; i < NUM_HISTORY_DATA_TYPE; ++i) {
		list = NULL;

		error = context_history_get_list(handle, history_data_enum[i], NULL, &list);
		SKIP_TEST_CONTINUE(error, i + 1, NUM_HISTORY_DATA_TYPE, history_data_name[i]);

		error = context_history_list_move_first(list);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);

		context_history_list_destroy(list);
	}

	return 0;
}

/**
 * @testcase		utc_context_history_list_move_first_n
 * @since_tizen		2.4
 * @description		Negative test case of context_history_list_move_first()
 */
int utc_context_history_list_move_first_n(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;

	error = context_history_list_move_first(NULL);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_context_history_list_move_next_p
 * @since_tizen		2.4
 * @description		Positive test case of context_history_list_move_next()
 */
int utc_context_history_list_move_next_p(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	int i;
	int count;
	context_history_list_h list;

	for (i = 0; i < NUM_HISTORY_DATA_TYPE; ++i) {
		list = NULL;
		count = -1;

		error = context_history_get_list(handle, history_data_enum[i], NULL, &list);
		SKIP_TEST_CONTINUE(error, i + 1, NUM_HISTORY_DATA_TYPE, history_data_name[i]);

		error = context_history_list_get_count(list, &count);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		if (is_history_supported && count < 2) {
			PRINT_INFO("(%d/%d) Skipping this test for %s. The number of records is %d.",
					i + 1, NUM_HISTORY_DATA_TYPE, history_data_name[i], count);
			context_history_list_destroy(list);
			list = NULL;
			continue;
		}

		error = context_history_list_move_next(list);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);

		context_history_list_destroy(list);
	}

	return 0;
}

/**
 * @testcase		utc_context_history_list_move_next_n
 * @since_tizen		2.4
 * @description		Negative test case of context_history_list_move_next()
 */
int utc_context_history_list_move_next_n(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;

	error = context_history_list_move_next(NULL);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_context_history_list_destroy_p
 * @since_tizen		2.4
 * @description		Positive test case of context_history_list_destroy()
 */
int utc_context_history_list_destroy_p(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	int i;
	context_history_list_h list;

	for (i = 0; i < NUM_HISTORY_DATA_TYPE; ++i) {
		list = NULL;

		error = context_history_get_list(handle, history_data_enum[i], NULL, &list);
		SKIP_TEST_CONTINUE(error, i + 1, NUM_HISTORY_DATA_TYPE, history_data_name[i]);

		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		HISTORY_ASSERT_IF_SUPPORTED(is_history_supported, list);

		error = context_history_list_destroy(list);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_context_history_list_destroy_n
 * @since_tizen		2.4
 * @description		Negative test case of context_history_list_destroy()
 */
int utc_context_history_list_destroy_n(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;

	error = context_history_list_destroy(NULL);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_context_history_record_get_int_p
 * @since_tizen		2.4
 * @description		Positive test case of context_history_record_get_int()
 */
int utc_context_history_record_get_int_p(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	int value;
	context_history_filter_h filter = NULL;
	context_history_list_h list = NULL;
	context_history_record_h record = NULL;

	context_history_filter_create(&filter);
	context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_TIME_SPAN, 30);

	error = context_history_get_list(handle, CONTEXT_HISTORY_FREQUENTLY_USED_APP, filter, &list);
	SKIP_TEST(error, 1, 4, history_data_name[1]) else {
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		context_history_list_get_current(list, &record);

		value = -1;
		error = context_history_record_get_int(record, CONTEXT_HISTORY_TOTAL_COUNT, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		HISTORY_ASSERT_GEQ_IF_SUPPORTED(is_history_supported, value, 0);

		value = -1;
		error = context_history_record_get_int(record, CONTEXT_HISTORY_TOTAL_DURATION, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		HISTORY_ASSERT_GEQ_IF_SUPPORTED(is_history_supported, value, 0);

		value = -3;
		error = context_history_record_get_int(record, CONTEXT_HISTORY_LAST_TIME, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		HISTORY_ASSERT_GEQ_IF_SUPPORTED(is_history_supported, value, -1);

		context_history_record_destroy(record);
		context_history_list_destroy(list);
	}

#if defined(MOBILE) || defined(TIZENIOT)
	error = context_history_get_list(handle, CONTEXT_HISTORY_RARELY_USED_APP, filter, &list);
	SKIP_TEST(error, 2, 4, history_data_name[4]) else {
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		context_history_list_get_current(list, &record);

		value = -1;
		error = context_history_record_get_int(record, CONTEXT_HISTORY_TOTAL_COUNT, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		HISTORY_ASSERT_GEQ_IF_SUPPORTED(is_history_supported, value, 0);

		value = -1;
		error = context_history_record_get_int(record, CONTEXT_HISTORY_TOTAL_DURATION, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		HISTORY_ASSERT_GEQ_IF_SUPPORTED(is_history_supported, value, 0);

		value = -3;
		error = context_history_record_get_int(record, CONTEXT_HISTORY_LAST_TIME, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		HISTORY_ASSERT_GEQ_IF_SUPPORTED(is_history_supported, value, -1);

		context_history_record_destroy(record);
		context_history_list_destroy(list);
	}

	error = context_history_get_list(handle, CONTEXT_HISTORY_COMMON_SETTING_FOR_APP, filter, &list);
	SKIP_TEST(error, 3, 4, history_data_name[8]) else {
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		error = context_history_list_get_current(list, &record);

		value = -1;
		error = context_history_record_get_int(record, CONTEXT_HISTORY_AUDIO_JACK, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		HISTORY_ASSERT_GEQ_IF_SUPPORTED(is_history_supported, value, 0);

		value = -1;
		error = context_history_record_get_int(record, CONTEXT_HISTORY_SYSTEM_VOLUME, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		HISTORY_ASSERT_GEQ_IF_SUPPORTED(is_history_supported, value, 0);

		value = -1;
		error = context_history_record_get_int(record, CONTEXT_HISTORY_MEDIA_VOLUME, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		HISTORY_ASSERT_GEQ_IF_SUPPORTED(is_history_supported, value, 0);

		context_history_record_destroy(record);
		context_history_list_destroy(list);
	}

	error = context_history_get_list(handle, CONTEXT_HISTORY_PEAK_TIME_FOR_APP, filter, &list);
	SKIP_TEST(error, 4, 4, history_data_name[5]) else {
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		context_history_list_get_current(list, &record);

		value = -1;
		error = context_history_record_get_int(record, CONTEXT_HISTORY_HOUR_OF_DAY, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		HISTORY_ASSERT_GEQ_IF_SUPPORTED(is_history_supported, value, 0);

		context_history_record_destroy(record);
		context_history_list_destroy(list);
	}
#endif	//MOBILE

	context_history_filter_destroy(filter);

	return 0;
}

/**
 * @testcase		utc_context_history_record_get_int_n
 * @since_tizen		2.4
 * @description		Negative test case of context_history_record_get_int()
 */
int utc_context_history_record_get_int_n(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	int value;
	context_history_list_h list = NULL;
	context_history_record_h record = NULL;

	error = context_history_get_list(handle, CONTEXT_HISTORY_FREQUENTLY_USED_APP, NULL, &list);
	SKIP_TEST(error, 1, 1, history_data_name[1]) else {
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		context_history_list_get_current(list, &record);

		error = context_history_record_get_int(record, CONTEXT_HISTORY_TOTAL_COUNT, NULL);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

		// Invalid record data type
		error = context_history_record_get_int(record, CONTEXT_HISTORY_APP_ID, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

#if defined(MOBILE) || defined(TIZENIOT)
		// Invalid record key
		error = context_history_record_get_int(record, CONTEXT_HISTORY_HOUR_OF_DAY, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);
#endif	//MOBILE

		context_history_record_destroy(record);
		context_history_list_destroy(list);
	}

	return 0;
}

/**
 * @testcase		utc_context_history_record_get_string_p
 * @since_tizen		2.4
 * @description		Positive test case of context_history_record_get_string()
 */
int utc_context_history_record_get_string_p(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	char *value = NULL;
	context_history_filter_h filter = NULL;
	context_history_list_h list = NULL;
	context_history_record_h record = NULL;

	context_history_filter_create(&filter);
	context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_TIME_SPAN, 30);

	error = context_history_get_list(handle, CONTEXT_HISTORY_FREQUENTLY_USED_APP, filter, &list);
	SKIP_TEST(error, 1, 3, history_data_name[1]) else {
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		context_history_list_get_current(list, &record);

		value = NULL;
		error = context_history_record_get_string(record, CONTEXT_HISTORY_APP_ID, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		HISTORY_ASSERT_IF_SUPPORTED(is_history_supported, strlen(value) > 0);

		free(value);
		context_history_record_destroy(record);
		context_history_list_destroy(list);
	}
#if defined(MOBILE) || defined(TIZENIOT)
	error = context_history_get_list(handle, CONTEXT_HISTORY_RARELY_USED_APP, filter, &list);
	SKIP_TEST(error, 2, 3, history_data_name[4]) else {
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		context_history_list_get_current(list, &record);

		value = NULL;
		error = context_history_record_get_string(record, CONTEXT_HISTORY_APP_ID, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		HISTORY_ASSERT_IF_SUPPORTED(is_history_supported, strlen(value) > 0);

		free(value);
		context_history_record_destroy(record);
		context_history_list_destroy(list);
	}

	error = context_history_get_list(handle, CONTEXT_HISTORY_FREQUENTLY_COMMUNICATED_ADDRESS, filter, &list);
	SKIP_TEST(error, 3, 3, history_data_name[11]) else {
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		context_history_list_get_current(list, &record);

		value = NULL;
		error = context_history_record_get_string(record, CONTEXT_HISTORY_ADDRESS, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		HISTORY_ASSERT_IF_SUPPORTED(is_history_supported, strlen(value) > 0);

		free(value);
		context_history_record_destroy(record);
		context_history_list_destroy(list);
	}
#endif	//MOBILE

	context_history_filter_destroy(filter);

	return 0;
}

/**
 * @testcase		utc_context_history_record_get_string_n
 * @since_tizen		2.4
 * @description		Negative test case of context_history_get_string()
 */
int utc_context_history_record_get_string_n(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	char* value;
	context_history_list_h list = NULL;
	context_history_record_h record = NULL;

	error = context_history_get_list(handle, CONTEXT_HISTORY_BATTERY_USAGE, NULL, &list);
	SKIP_TEST(error, 1, 1, history_data_name[2]) else {
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		context_history_list_get_current(list, &record);

		error = context_history_record_get_string(record, CONTEXT_HISTORY_APP_ID, NULL);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

		// Invalid record data type
		error = context_history_record_get_string(record, CONTEXT_HISTORY_TOTAL_AMOUNT, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);
#if defined(MOBILE) || defined(TIZENIOT)
		// Invalid record key
		error = context_history_record_get_string(record, CONTEXT_HISTORY_ADDRESS, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);
#endif	//MOBILE

		context_history_record_destroy(record);
		context_history_list_destroy(list);
	}

	return 0;
}

/**
 * @testcase		utc_context_history_record_get_double_p
 * @since_tizen		3.0
 * @description		Positive test case of context_history_record_get_double()
 */
int utc_context_history_record_get_double_p(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	double value;
	context_history_filter_h filter = NULL;
	context_history_list_h list = NULL;
	context_history_record_h record = NULL;

	context_history_filter_create(&filter);
	context_history_filter_set_int(filter, CONTEXT_HISTORY_FILTER_TIME_SPAN, 30);

	error = context_history_get_list(handle, CONTEXT_HISTORY_BATTERY_USAGE, filter, &list);
	SKIP_TEST(error, 1, 1, history_data_name[2]) else {
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		context_history_list_get_current(list, &record);

		value = -1;
		error = context_history_record_get_double(record, CONTEXT_HISTORY_TOTAL_AMOUNT, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		HISTORY_ASSERT_GEQ_IF_SUPPORTED(is_history_supported, value, 0);

		context_history_record_destroy(record);
		context_history_list_destroy(list);
	}

	context_history_filter_destroy(filter);

	return 0;
}

/**
 * @testcase		utc_context_history_record_get_double_n
 * @since_tizen		3.0
 * @description		Negative test case of context_history_record_get_double()
 */
int utc_context_history_record_get_double_n(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	double value;
	context_history_list_h list = NULL;
	context_history_record_h record = NULL;

	error = context_history_get_list(handle, CONTEXT_HISTORY_BATTERY_USAGE, NULL, &list);
	SKIP_TEST(error, 1, 1, history_data_name[2]) else {
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		context_history_list_get_current(list, &record);

		error = context_history_record_get_double(record, CONTEXT_HISTORY_TOTAL_AMOUNT, NULL);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

		// Invalid record data type
		error = context_history_record_get_double(record, CONTEXT_HISTORY_APP_ID, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);
#if defined(MOBILE) || defined(TIZENIOT)
		// Invalid record key
		error = context_history_record_get_double(record, CONTEXT_HISTORY_HOUR_OF_DAY, &value);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);
#endif	//MOBILE

		context_history_record_destroy(record);
		context_history_list_destroy(list);
	}

	return 0;
}

/**
 * @testcase		utc_context_history_record_destroy_p
 * @since_tizen		2.4
 * @description		Positive test case of context_history_record_destroy()
 */
int utc_context_history_record_destroy_p(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;
	int i;
	context_history_list_h list;
	context_history_record_h record;

	for (i = 0; i < NUM_HISTORY_DATA_TYPE; ++i) {
		list = NULL;
		record = NULL;

		error = context_history_get_list(handle, history_data_enum[i], NULL, &list);
		SKIP_TEST_CONTINUE(error, i + 1, NUM_HISTORY_DATA_TYPE, history_data_name[i]);

		error = context_history_list_get_current(list, &record);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);
		HISTORY_ASSERT_IF_SUPPORTED(is_history_supported, record);

		error = context_history_record_destroy(record);
		HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_NONE);

		context_history_list_destroy(list);
	}

	return 0;
}

/**
 * @testcase		utc_context_history_record_destroy_n
 * @since_tizen		2.4
 * @description		Negative test case of context_history_record_destroy()
 */
int utc_context_history_record_destroy_n(void)
{
	int error = CONTEXT_HISTORY_ERROR_NONE;

	error = context_history_record_destroy(NULL);
	HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_history_supported, error, CONTEXT_HISTORY_ERROR_INVALID_PARAMETER);

	return 0;
}
