//
// Copyright (c) 2015 Samsung Electronics Co., Ltd.
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
#include <feedback.h>
#include <stdbool.h>
#include <stdlib.h>
#include "assert.h"
#include <unistd.h>

#define DELAY_TIME       100*1000 /* 100ms */

#define ARRAY_SIZE(name) (sizeof(name)/sizeof(name[0]))

#define HAPTIC_FEATURE                      "http://tizen.org/feature/feedback.vibration"

static bool is_supported;

static struct _utc_feedback_pattern {
	feedback_pattern_e pattern;
	const char *name;
} utc_feedback_pattern[] = {
	{ FEEDBACK_PATTERN_TAP, "FEEDBACK_PATTERN_TAP" },
	{ FEEDBACK_PATTERN_SIP, "FEEDBACK_PATTERN_SIP" },
	{ FEEDBACK_PATTERN_KEY0, "FEEDBACK_PATTERN_KEY0" },
	{ FEEDBACK_PATTERN_KEY1, "FEEDBACK_PATTERN_KEY1" },
	{ FEEDBACK_PATTERN_KEY2, "FEEDBACK_PATTERN_KEY2" },
	{ FEEDBACK_PATTERN_KEY3, "FEEDBACK_PATTERN_KEY3" },
	{ FEEDBACK_PATTERN_KEY4, "FEEDBACK_PATTERN_KEY4" },
	{ FEEDBACK_PATTERN_KEY5, "FEEDBACK_PATTERN_KEY5" },
	{ FEEDBACK_PATTERN_KEY6, "FEEDBACK_PATTERN_KEY6" },
	{ FEEDBACK_PATTERN_KEY7, "FEEDBACK_PATTERN_KEY7" },
	{ FEEDBACK_PATTERN_KEY8, "FEEDBACK_PATTERN_KEY8" },
	{ FEEDBACK_PATTERN_KEY9, "FEEDBACK_PATTERN_KEY9" },
	{ FEEDBACK_PATTERN_KEY_STAR, "FEEDBACK_PATTERN_KEY_STAR" },
	{ FEEDBACK_PATTERN_KEY_SHARP, "FEEDBACK_PATTERN_KEY_SHARP" },
	{ FEEDBACK_PATTERN_KEY_BACK, "FEEDBACK_PATTERN_KEY_BACK" },
	{ FEEDBACK_PATTERN_HOLD, "FEEDBACK_PATTERN_HOLD" },
	{ FEEDBACK_PATTERN_HW_TAP, "FEEDBACK_PATTERN_HW_TAP" },
	{ FEEDBACK_PATTERN_HW_HOLD, "FEEDBACK_PATTERN_HW_HOLD" },
	{ FEEDBACK_PATTERN_MESSAGE, "FEEDBACK_PATTERN_MESSAGE" },
	{ FEEDBACK_PATTERN_EMAIL, "FEEDBACK_PATTERN_EMAIL," },
	{ FEEDBACK_PATTERN_WAKEUP, "FEEDBACK_PATTERN_WAKEUP" },
	{ FEEDBACK_PATTERN_SCHEDULE, "FEEDBACK_PATTERN_SCHEDULE" },
	{ FEEDBACK_PATTERN_TIMER, "FEEDBACK_PATTERN_TIMER" },
	{ FEEDBACK_PATTERN_GENERAL, "FEEDBACK_PATTERN_GENERAL" },
	{ FEEDBACK_PATTERN_POWERON, "FEEDBACK_PATTERN_POWERON" },
	{ FEEDBACK_PATTERN_POWEROFF, "FEEDBACK_PATTERN_POWEROFF" },
	{ FEEDBACK_PATTERN_CHARGERCONN, "FEEDBACK_PATTERN_CHARGERCONN" },
	{ FEEDBACK_PATTERN_CHARGING_ERROR, "FEEDBACK_PATTERN_CHARGING_ERROR" },
	{ FEEDBACK_PATTERN_FULLCHARGED, "FEEDBACK_PATTERN_FULLCHARGED" },
	{ FEEDBACK_PATTERN_LOWBATT, "FEEDBACK_PATTERN_LOWBATT" },
	{ FEEDBACK_PATTERN_LOCK, "FEEDBACK_PATTERN_LOCK" },
	{ FEEDBACK_PATTERN_UNLOCK, "FEEDBACK_PATTERN_UNLOCK" },
	{ FEEDBACK_PATTERN_VIBRATION_ON, "FEEDBACK_PATTERN_VIBRATION_ON" },
	{ FEEDBACK_PATTERN_SILENT_OFF, "FEEDBACK_PATTERN_SILENT_OFF" },
	{ FEEDBACK_PATTERN_BT_CONNECTED, "FEEDBACK_PATTERN_BT_CONNECTED" },
	{ FEEDBACK_PATTERN_BT_DISCONNECTED, "FEEDBACK_PATTERN_BT_DISCONNECTED" },
	{ FEEDBACK_PATTERN_LIST_REORDER, "FEEDBACK_PATTERN_LIST_REORDER" },
	{ FEEDBACK_PATTERN_LIST_SLIDER, "FEEDBACK_PATTERN_LIST_SLIDER" },
	{ FEEDBACK_PATTERN_VOLUME_KEY, "FEEDBACK_PATTERN_VOLUME_KEY" },
};

/**
 * @function		utc_feedback_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_feedback_startup(void)
{
	int ret;
	/* initialize feedback */
	feedback_initialize();

	ret = system_info_get_platform_bool(HAPTIC_FEATURE, &is_supported);
	if (ret < 0)
		is_supported = false;
}

/**
 * @function		utc_feedback_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_feedback_cleanup(void)
{
	/* deinitialize feedback */
	feedback_deinitialize();
}

/**
 * @testcase		utc_system_feedback_initialize_p
 * @since_tizen		2.4
 * @description		Positive test case of feedback_initialize()
 */
int utc_system_feedback_initialize_p(void)
{
	int ret;

	ret = feedback_initialize();
	assert_eq(ret, FEEDBACK_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_system_feedback_deinitialize_p
 * @since_tizen		2.4
 * @description		Positive test case of feedback_deinitialize()
 */
int utc_system_feedback_deinitialize_p(void)
{
	int ret;

	ret = feedback_deinitialize();
	assert_eq(ret, FEEDBACK_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_system_feedback_deinitialize_n
 * @since_tizen		2.4
 * @description		Nagative test case of feedback_deinitialize()
 */
int utc_system_feedback_deinitialize_n(void)
{
	int ret;

	ret = feedback_deinitialize();
	assert_eq(ret, FEEDBACK_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase		utc_system_feedback_play_p
 * @since_tizen		2.4
 * @description		Positive test case of feedback_play()
 */
int utc_system_feedback_play_p(void)
{
	int i;
	int ret;

	if (!is_supported)
		return 0;

	for (i = 0 ; i < ARRAY_SIZE(utc_feedback_pattern) ; ++i) {
		ret = feedback_play(utc_feedback_pattern[i].pattern);
		assert_eq(ret, FEEDBACK_ERROR_NONE);
		usleep(DELAY_TIME);
	}
	return 0;
}

/**
 * @testcase		utc_system_feedback_play_n
 * @since_tizen		2.4
 * @description		Negative test case of feedback_play()
 */
int utc_system_feedback_play_n(void)
{
	int ret = feedback_play(-1);
	assert_neq(ret, FEEDBACK_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_system_feedback_play_type_p_1
 * @since_tizen		2.4
 * @description		Positive test case of feedback_play_type()
 */
int utc_system_feedback_play_type_p_1(void)
{
	int i;
	int ret;
	bool status;

	ret = feedback_is_supported_pattern(FEEDBACK_TYPE_SOUND,
			0, &status);
	/* not supported sound device */
	if (ret == FEEDBACK_ERROR_NOT_SUPPORTED)
		return 0;

	for (i = 0 ; i < ARRAY_SIZE(utc_feedback_pattern) ; ++i) {
		ret = feedback_is_supported_pattern(FEEDBACK_TYPE_SOUND,
				utc_feedback_pattern[i].pattern, &status);
		assert_eq(ret, FEEDBACK_ERROR_NONE);

		/* not supported pattern */
		if (!status)
			continue;

		ret = feedback_play_type(FEEDBACK_TYPE_SOUND,
				utc_feedback_pattern[i].pattern);
		assert_eq(ret, FEEDBACK_ERROR_NONE);
		usleep(DELAY_TIME);
	}
	return 0;
}

/**
 * @testcase		utc_system_feedback_play_type_p_2
 * @since_tizen		2.4
 * @description		Positive test case of feedback_play_type()
 */
int utc_system_feedback_play_type_p_2(void)
{
	int i;
	int ret;
	bool status;

	if (!is_supported)
		return 0;

	ret = feedback_is_supported_pattern(FEEDBACK_TYPE_VIBRATION,
			0, &status);
	/* not supported vibration device */
	if (ret == FEEDBACK_ERROR_NOT_SUPPORTED)
		return 0;

	for (i = 0 ; i < ARRAY_SIZE(utc_feedback_pattern) ; ++i) {
		ret = feedback_is_supported_pattern(FEEDBACK_TYPE_VIBRATION,
				utc_feedback_pattern[i].pattern, &status);
		assert_eq(ret, FEEDBACK_ERROR_NONE);

		/* not supported pattern */
		if (!status)
			continue;

		ret = feedback_play_type(FEEDBACK_TYPE_VIBRATION,
				utc_feedback_pattern[i].pattern);
		assert_eq(ret, FEEDBACK_ERROR_NONE);
		usleep(DELAY_TIME);
	}
	return 0;
}

/**
 * @testcase		utc_system_feedback_play_type_n_1
 * @since_tizen		2.4
 * @description		Negative test case of feedback_play_type()
 */
int utc_system_feedback_play_type_n_1(void)
{
	int ret;

	ret = feedback_play_type(-1, 0);
	assert_neq(ret, FEEDBACK_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_system_feedback_play_type_n_2
 * @since_tizen		2.4
 * @description		Negative test case of feedback_play_type()
 */
int utc_system_feedback_play_type_n_2(void)
{
	int ret;

	ret = feedback_play_type(FEEDBACK_TYPE_SOUND, -1);
	assert_neq(ret, FEEDBACK_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_system_feedback_stop_p
 * @since_tizen		2.4
 * @description		Positive test case of feedback_stop()
 */
int utc_system_feedback_stop_p(void)
{
	int ret;

	if (!is_supported)
		return 0;

	ret = feedback_stop();
	assert_eq(ret, FEEDBACK_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_system_feedback_is_supported_pattern_p
 * @since_tizen		2.4
 * @description		Positive test case of feedback_is_supported_pattern()
 */
int utc_system_feedback_is_supported_pattern_p(void)
{
	int ret;
	bool status;

	ret = feedback_is_supported_pattern(FEEDBACK_TYPE_SOUND,
			utc_feedback_pattern[0].pattern, &status);
	assert_eq(ret, FEEDBACK_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_system_feedback_is_supported_pattern_n_1
 * @since_tizen		2.4
 * @description		Negative test case of feedback_is_supported_pattern()
 */
int utc_system_feedback_is_supported_pattern_n_1(void)
{
	int ret;
	bool status;

	ret = feedback_is_supported_pattern(-1,
			utc_feedback_pattern[0].pattern, &status);
	assert_neq(ret, FEEDBACK_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_system_feedback_is_supported_pattern_n_2
 * @since_tizen		2.4
 * @description		Negative test case of feedback_is_supported_pattern()
 */
int utc_system_feedback_is_supported_pattern_n_2(void)
{
	int ret;
	bool status;

	ret = feedback_is_supported_pattern(FEEDBACK_TYPE_SOUND,
			-1, &status);
	assert_neq(ret, FEEDBACK_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_system_feedback_is_supported_pattern_n_3
 * @since_tizen		2.4
 * @description		Negative test case of feedback_is_supported_pattern()
 */
int utc_system_feedback_is_supported_pattern_n_3(void)
{
	int ret;

	ret = feedback_is_supported_pattern(FEEDBACK_TYPE_SOUND,
			utc_feedback_pattern[0].pattern, NULL);
	assert_neq(ret, FEEDBACK_ERROR_NONE);
	return 0;
}
