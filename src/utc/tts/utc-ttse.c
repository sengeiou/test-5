//
// Copyright (c) 2016 Samsung Electronics Co., Ltd.
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
#include <ttse.h>
#include <stdlib.h>
#include <Ecore.h>
#include <dlog.h>


extern void transfer_arg(int * argc, char ** argv[]);

static ttse_request_callback_s g_engine_callback = {0, };
static int g_rate = 24000;

static int g_argc = 1;
static char **g_argv = NULL;

bool g_is_supported = false;

static int engine_get_info(char** engine_uuid, char** engine_name, char** setting_ug_name, bool* use_network)
{
	*engine_uuid = strdup("23E456F7-ABC8-9DCA-XYZ1-D9876A5BCDE4");
	*engine_name = strdup("TTS engine sample");
	*setting_ug_name = strdup("libttsenginesample.so");
	*use_network = false;

	return 0;
}

static int engine_initialize(void)
{
	return 0;
}

static int engine_deinitialize(void)
{
	return 0;
}

static int engine_foreach_voices(ttse_supported_voice_cb callback, void* user_data)
{
	char * lang = "en_US";
	int vctype = TTSE_VOICE_TYPE_FEMALE;

	dlog_print(DLOG_INFO, "NativeTCT", "[engine_foreach_voices] lang = %s, vctype = %d", (NULL == lang) ? "NULL" : lang, vctype);

	bool ret = callback(lang, vctype, user_data);

	return 0;
}

static int engine_is_valid_voice(const char* language, int type, bool* is_valid)
{
	*is_valid = true;

	return 0;
}

static int engine_set_pitch(int pitch)
{
	return 0;
}

static int engine_load_voice(const char* language, int type)
{
	return 0;
}

static int engine_unload_voice(const char* language, int type)
{
	return 0;
}

static int engine_start_synth(const char* language, int type, const char* text, int speed, const char* appid, const char* credential, void* user_data)
{
	return 0;
}

static int engine_cancel_synth(void)
{
	return 0;
}

static int engine_check_app_agreed(const char* appid, bool* is_agreed)
{
	return 0;
}

static bool engine_need_app_credential(void)
{
	return false;
}

static int engine_set_private_data(const char* key, const char* data)
{
	return 0;
}

static int engine_get_private_data(const char* key, char** data)
{
	return 0;
}

/* ================================ */

void utc_ttse_startup(void)
{
	system_info_get_platform_bool("http://tizen.org/feature/speech.synthesis", &g_is_supported);
	/* start of TC */

	if (g_is_supported == false)
		return;

	transfer_arg(&g_argc, &g_argv);

	dlog_print(DLOG_INFO, "NativeTCT", "[startup2] argc = %d, argv[0] = %s", g_argc, (NULL == g_argv) ? "NULL" : g_argv[0]);

	g_engine_callback.version = 1;
	g_engine_callback.get_info = engine_get_info;

	g_engine_callback.initialize = engine_initialize;
	g_engine_callback.deinitialize = engine_deinitialize;

	g_engine_callback.start_synth = engine_start_synth;
	g_engine_callback.cancel_synth = engine_cancel_synth;

	g_engine_callback.foreach_voices = engine_foreach_voices;
	g_engine_callback.is_valid_voice = engine_is_valid_voice;

	g_engine_callback.set_pitch = engine_set_pitch;

	g_engine_callback.load_voice = engine_load_voice;
	g_engine_callback.unload_voice = engine_unload_voice;

	g_engine_callback.check_app_agreed = engine_check_app_agreed;
	g_engine_callback.need_app_credential = engine_need_app_credential;

}

void utc_ttse_cleanup(void)
{
    /* end of TC */
}

/**
 * @testcase		utc_ttse_main_p
 * @since_tizen		3.0
 * @description		Positive UTC for tts handle create
 */
int utc_ttse_main_p(void)
{
	int ret = TTSE_ERROR_NONE;

	ret = ttse_main(g_argc, g_argv, &g_engine_callback);
	assert_eq(ret, TTSE_ERROR_NONE);

	return 0;

}

/**
 * @testcase		utc_ttse_main_n
 * @since_tizen		3.0
 * @description		Positive UTC for tts handle create
 */
int utc_ttse_main_n(void)
{
	int ret = TTSE_ERROR_NONE;

	g_engine_callback.start_synth = NULL;

	ret = ttse_main(g_argc, g_argv, &g_engine_callback);
//	assert_neq(ret, TTSE_ERROR_NONE);
	assert_eq(ret, TTSE_ERROR_OPERATION_FAILED);

	return 0;
}

/**
 * @testcase		utc_ttse_main_n1
 * @since_tizen		3.0
 * @description		Positive UTC for tts handle create
 */
int utc_ttse_main_n1(void)
{
	int ret = TTSE_ERROR_NONE;

	ret = ttse_main(g_argc, g_argv, NULL);
//	assert_neq(ret, TTSE_ERROR_NONE);
	assert_eq(ret, TTSE_ERROR_OPERATION_FAILED);

	return 0;
}

/**
 * @testcase		utc_ttse_get_speed_range_p
 * @since_tizen		3.0
 * @description		Positive UTC for getting speed range
 */
int utc_ttse_get_speed_range_p(void)
{
	int ret = TTSE_ERROR_NONE;

	int min = 0;
	int normal = 0;
	int max = 0;

	ret = ttse_get_speed_range(&min, &normal, &max);
	assert_eq(ret, TTSE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_ttse_get_speed_range_n
 * @since_tizen		3.0
 * @description		Negative UTC for getting speed range
 */
int utc_ttse_get_speed_range_n(void)
{
	int ret = TTSE_ERROR_NONE;

	int min = 0;
	int normal = 0;

	ret = ttse_get_speed_range(&min, &normal, NULL);
	assert_eq(ret, TTSE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_ttse_get_pitch_range_p
 * @since_tizen		3.0
 * @description		Positive UTC for getting pitch range
 */
int utc_ttse_get_pitch_range_p(void)
{
	int ret = TTSE_ERROR_NONE;

	int min = 0;
	int normal = 0;
	int max = 0;

	ret = ttse_get_pitch_range(&min, &normal, &max);
	assert_eq(ret, TTSE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_ttse_get_pitch_range_n
 * @since_tizen		3.0
 * @description		Negative UTC for getting pitch range
 */
int utc_ttse_get_pitch_range_n(void)
{
	int ret = TTSE_ERROR_NONE;

	int min = 0;
	int normal = 0;

	ret = ttse_get_pitch_range(&min, &normal, NULL);
	assert_eq(ret, TTSE_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase		utc_ttse_send_result_n
 * @since_tizen		3.0
 * @description		Negative UTC for sending result
 */
int utc_ttse_send_result_n(void)
{
	int ret = TTSE_ERROR_NONE;

	ret = ttse_main(g_argc, g_argv, &g_engine_callback);
	assert_eq(ret, TTSE_ERROR_NONE);

	dlog_print(DLOG_INFO, "NativeTCT", "[utc_ttse_send_result_n] ttse_main SUCCESS");
	ret = ttse_send_result(TTSE_RESULT_EVENT_START, NULL, 0, TTSE_AUDIO_TYPE_RAW_S16, g_rate, NULL);
	assert_neq(ret, TTSE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		 utc_ttse_send_error_p
 * @since_tizen	 3.0
 * @description	 Positive UTC for sending error
 */
int utc_ttse_send_error_p(void)
{
	int ret = TTSE_ERROR_NONE;

	ret = ttse_main(g_argc, g_argv, &g_engine_callback);
	assert_eq(ret, TTSE_ERROR_NONE);

	ret = ttse_send_error(TTSE_ERROR_INVALID_STATE, "error");
	assert_eq(ret, TTSE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_ttse_set_private_data_set_cb_p
 * @since_tizen		3.0
 * @description		Positive UTC for setting a callback of setting private data
 */
int utc_ttse_set_private_data_set_cb_p(void)
{
	int ret = TTSE_ERROR_NONE;

	ret = ttse_main(g_argc, g_argv, &g_engine_callback);
	assert_eq(ret, TTSE_ERROR_NONE);

	ret = ttse_set_private_data_set_cb(engine_set_private_data);
	assert_eq(ret, TTSE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_ttse_set_private_data_set_cb_n
 * @since_tizen		3.0
 * @description		Negative UTC for setting a callback of setting private data (invalid parameter)
 */
int utc_ttse_set_private_data_set_cb_n(void)
{
	int ret = TTSE_ERROR_NONE;

	ret = ttse_main(g_argc, g_argv, &g_engine_callback);
	assert_eq(ret, TTSE_ERROR_NONE);

	ret = ttse_set_private_data_set_cb(NULL);
	assert_eq(ret, TTSE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		 utc_ttse_set_private_data_requested_cb_p
 * @since_tizen	 3.0
 * @description	 Positive UTC for setting a callback of requesting private data
 */
int utc_ttse_set_private_data_requested_cb_p(void)
{
	int ret = TTSE_ERROR_NONE;

	ret = ttse_main(g_argc, g_argv, &g_engine_callback);
	assert_eq(ret, TTSE_ERROR_NONE);

	ret = ttse_set_private_data_requested_cb(engine_get_private_data);
	assert_eq(ret, TTSE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		 utc_ttse_set_private_data_requested_cb_n
 * @since_tizen	 3.0
 * @description	 Negative UTC for setting a callback of requesting private data (invalid parameter)
 */
int utc_ttse_set_private_data_requested_cb_n(void)
{
	int ret = TTSE_ERROR_NONE;

	ret = ttse_main(g_argc, g_argv, &g_engine_callback);
	assert_eq(ret, TTSE_ERROR_NONE);

	ret = ttse_set_private_data_requested_cb(NULL);
	assert_eq(ret, TTSE_ERROR_INVALID_PARAMETER);

	return 0;
}


