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
#include <stte.h>
#include <stdlib.h>
#include <system_info.h>
#include <fcntl.h>
#include <unistd.h>
#include <dlog.h>

#include "assert.h"
#include "tct_common.h"

#define API_NAMESPACE				"STT_UTC"
#define MICROPHONE_FEATURE			"http://tizen.org/feature/microphone"
#define SPEECH_RECOGNITION_FEATURE	"http://tizen.org/feature/speech.recognition"


extern void transfer_arg(int * argc, char ** argv[]);

static stte_request_callback_s g_engine_callback = {0, };
static char **g_data = {"This", "is", "a", "test"};
static int g_data_count = 4;
static char *g_msg = NULL;	//STTE_RESULT_MESSAGE_NONE;
static char *g_time_info = NULL;

static int g_argc = 1;
static char **g_argv = NULL;

bool is_success = false;
bool g_is_supported = false;

static int engine_get_info(char** engine_uuid, char** engine_name, char** setting_ug_name, bool* use_network)
{
	*engine_uuid = strdup("1ABC23DF-GE45-67E8-ZYX1-12345A6BC789");
	*engine_name = strdup("STT engine sample");
	*setting_ug_name = strdup("libsttenginesample.so");
	*use_network = true;

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

static int engine_foreach_langs(stte_supported_language_cb callback, void* user_data)
{
	char * lang = "en_US";

	dlog_print(DLOG_INFO, "NativeTCT", "[engine_foreach_langs] lang = %s", (NULL == lang) ? "NULL" : lang);

	bool ret = callback((const char*)lang, user_data);

	return 0;
}

static int engine_is_valid_language(const char* language, bool* is_valid)
{
	*is_valid = true;
	return 0;
}

static bool engine_support_silence_detection(void)
{
	return true;
}

static int engine_support_recognition_type(const char* type, bool* is_supported)
{
	*is_supported = true;

	return 0;
}

static int engine_get_recording_format(stte_audio_type_e* types, int* rate, int* channels)
{
	*types = STTE_AUDIO_TYPE_PCM_S16_LE;
	*rate = 16000;
	*channels = 1;

	return 0;
}

static int engine_foreach_result_time(void* time_info, stte_result_time_cb callback, void* user_data)
{
	return 0;
}

static int engine_set_silence_detection(bool is_set)
{
	return 0;
}

static int engine_start(const char* language, const char* type, const char* appid, const char* credential, void *user_data)
{
	return 0;
}

static int engine_set_recording_data(const void* data, unsigned int length)
{
	return 0;
}

static int engine_stop(void)
{
	return 0;
}

static int engine_cancel(void)
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

static int __engine_audio_type_cb(const char* audio_type, void* user_data)
{
	return 0;
}

void utc_stte_startup(void)
{
	/* start of TC */
	g_is_supported = TCTCheckSystemInfoFeatureSupported(MICROPHONE_FEATURE, API_NAMESPACE) &&
		TCTCheckSystemInfoFeatureSupported(SPEECH_RECOGNITION_FEATURE, API_NAMESPACE);

	if (g_is_supported == false)
		return;

	transfer_arg(&g_argc, &g_argv);

	g_engine_callback.version = 1;
	g_engine_callback.get_info = engine_get_info;

	g_engine_callback.initialize = engine_initialize;
	g_engine_callback.deinitialize = engine_deinitialize;

	g_engine_callback.start = engine_start;
	g_engine_callback.set_recording = engine_set_recording_data;
	g_engine_callback.stop = engine_stop;
	g_engine_callback.cancel = engine_cancel;

	g_engine_callback.foreach_langs = engine_foreach_langs;
	g_engine_callback.is_valid_lang = engine_is_valid_language;

	g_engine_callback.support_silence = engine_support_silence_detection;
	g_engine_callback.support_recognition_type = engine_support_recognition_type;
	g_engine_callback.get_audio_format = engine_get_recording_format;
	g_engine_callback.foreach_result_time = engine_foreach_result_time;

	g_engine_callback.set_silence_detection = engine_set_silence_detection;

	g_engine_callback.check_app_agreed = engine_check_app_agreed;
	g_engine_callback.need_app_credential = engine_need_app_credential;
}

void utc_stte_cleanup(void)
{
	/* end of TC */
}

/**
 * @testcase		utc_stte_main_p
 * @since_tizen		3.0
 * @description		Positive UTC for stte main function
 */
int utc_stte_main_p(void)
{
	int ret = STTE_ERROR_NONE;

	if (false == is_success) {
		ret = stte_main(g_argc, g_argv, &g_engine_callback);
		assert_eq(ret, STTE_ERROR_NONE);
		if (0 == ret) {
			is_success = true;
		}
	}

	return 0;
}

/**
 * @testcase		utc_stte_main_n
 * @since_tizen		3.0
 * @description		Negative UTC for stte main function
 */

int utc_stte_main_n(void)
{
	int ret = STTE_ERROR_NONE;

	if (false == is_success) {
		ret = stte_main(g_argc, g_argv, NULL);
		assert_neq(ret, STTE_ERROR_NONE);
		if (0 == ret) {
			is_success = true;
		}
	}

	return 0;
}


/**
 * @testcase		utc_stte_send_result_n
 * @since_tizen		3.0
 * @description		Negative UTC for sending result (operation failure)
 */
int utc_stte_send_result_n(void)
{
	int ret = STTE_ERROR_NONE;

	if (false == is_success) {
		ret = stte_main(g_argc, g_argv, &g_engine_callback);
		assert_eq(ret, STTE_ERROR_NONE);
		if (0 == ret) {
			is_success = true;
		}
	}

	ret = stte_send_result(STTE_RESULT_EVENT_FINAL_RESULT, STTE_RECOGNITION_TYPE_FREE, g_data, g_data_count, g_msg, g_time_info, NULL);
	assert_eq(ret, STTE_ERROR_OPERATION_FAILED);
//	assert_eq(ret, STTE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_stte_send_speech_status_n
 * @since_tizen		3.0
 * @description		Negative UTC for sending speech status (operation failure)
 */
int utc_stte_send_speech_status_n(void)
{
	int ret = STTE_ERROR_NONE;

	if (false == is_success) {
		ret = stte_main(g_argc, g_argv, &g_engine_callback);
		assert_eq(ret, STTE_ERROR_NONE);
		if (0 == ret) {
			is_success = true;
		}
	}

	ret = stte_send_speech_status(STTE_SPEECH_STATUS_BEGINNING_POINT_DETECTED, NULL);
//	assert_eq(ret, STTE_ERROR_OPERATION_FAILED);
	assert_eq(ret, STTE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		 utc_stte_send_error_p
 * @since_tizen	 3.0
 * @description	 Positive UTC for sending error
 */
int utc_stte_send_error_p(void)
{
	int ret = STTE_ERROR_NONE;

	if (false == is_success) {
		ret = stte_main(g_argc, g_argv, &g_engine_callback);
		assert_eq(ret, STTE_ERROR_NONE);
		if (0 == ret) {
			is_success = true;
		}
	}

	ret = stte_send_error(STTE_ERROR_INVALID_STATE, "error");
	assert_eq(ret, STTE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_stte_set_private_data_set_cb_p
 * @since_tizen		3.0
 * @description		Positive UTC for setting a callback of setting private data
 */
int utc_stte_set_private_data_set_cb_p(void)
{
	int ret = STTE_ERROR_NONE;

	if (false == is_success) {
		ret = stte_main(g_argc, g_argv, &g_engine_callback);
		assert_eq(ret, STTE_ERROR_NONE);
		if (0 == ret) {
			is_success = true;
		}
	}

	ret = stte_set_private_data_set_cb(engine_set_private_data);
	assert_eq(ret, STTE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_stte_set_private_data_set_cb_n
 * @since_tizen		3.0
 * @description		Negative UTC for setting a callback of setting private data (invalid parameter)
 */
int utc_stte_set_private_data_set_cb_n(void)
{
	int ret = STTE_ERROR_NONE;

	if (false == is_success) {
		ret = stte_main(g_argc, g_argv, &g_engine_callback);
		assert_eq(ret, STTE_ERROR_NONE);
		if (0 == ret) {
			is_success = true;
		}
	}

	ret = stte_set_private_data_set_cb(NULL);
	assert_eq(ret, STTE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		 utc_stte_set_private_data_requested_cb_p
 * @since_tizen	 3.0
 * @description	 Positive UTC for setting a callback of requesting private data
 */
int utc_stte_set_private_data_requested_cb_p(void)
{
	int ret = STTE_ERROR_NONE;

	if (false == is_success) {
		ret = stte_main(g_argc, g_argv, &g_engine_callback);
		assert_eq(ret, STTE_ERROR_NONE);
		if (0 == ret) {
			is_success = true;
		}
	}

	ret = stte_set_private_data_requested_cb(engine_get_private_data);
	assert_eq(ret, STTE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		 utc_stte_set_private_data_requested_cb_n
 * @since_tizen	 3.0
 * @description	 Negative UTC for setting a callback of requesting private data (invalid parameter)
 */
int utc_stte_set_private_data_requested_cb_n(void)
{
	int ret = STTE_ERROR_NONE;

	if (false == is_success) {
		ret = stte_main(g_argc, g_argv, &g_engine_callback);
		assert_eq(ret, STTE_ERROR_NONE);
		if (0 == ret) {
			is_success = true;
		}
	}

	ret = stte_set_private_data_requested_cb(NULL);
	assert_eq(ret, STTE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_stte_set_audio_type_set_cb_p
 * @since_tizen		5.5
 * @description		Positive UTC for setting a callback of setting audio type
 */
int utc_stte_set_audio_type_set_cb_p(void)
{
	int ret = STTE_ERROR_NONE;

	if (false == is_success) {
		ret = stte_main(g_argc, g_argv, &g_engine_callback);
		assert_eq(ret, STTE_ERROR_NONE);
	}

	ret = stte_set_audio_type_set_cb(__engine_audio_type_cb, NULL);
	assert_eq(ret, STTE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_stte_set_audio_type_set_cb_n
 * @since_tizen		5.5
 * @description		Negative UTC for setting a callback of setting audio type (invalid parameter)
 */
int utc_stte_set_audio_type_set_cb_n(void)
{
	int ret = STTE_ERROR_NONE;

	if (false == is_success) {
		ret = stte_main(g_argc, g_argv, &g_engine_callback);
		assert_eq(ret, STTE_ERROR_NONE);
		if (0 == ret) {
			is_success = true;
		}
	}

	ret = stte_set_audio_type_set_cb(NULL, NULL);
	assert_eq(ret, STTE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_stte_unset_audio_type_set_cb_p
 * @since_tizen		5.5
 * @description		Positive UTC for setting a callback of setting audio type
 */
int utc_stte_unset_audio_type_set_cb_p(void)
{
	int ret = STTE_ERROR_NONE;

	if (false == is_success) {
		ret = stte_main(g_argc, g_argv, &g_engine_callback);
		assert_eq(ret, STTE_ERROR_NONE);
	}

	ret = stte_unset_audio_type_set_cb();
	assert_eq(ret, STTE_ERROR_NONE);

	return 0;
}
