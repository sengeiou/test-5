//
// Copyright (c) 2018 Samsung Electronics Co., Ltd.
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

#include <vce.h>
#include <stdlib.h>
#include <system_info.h>
#include <fcntl.h>
#include <unistd.h>
#include <dlog.h>

#include "assert.h"


extern void transfer_arg(int * argc, char ** argv[]);

static int g_argc = 1;
static char **g_argv = NULL;
static bool g_vce_supported = false;
static bool g_vce_init = false;
static vce_request_callback_s callback = {0,};
static int g_vce_command;

static int vce_default_initialize(void)
{
	return 0;
}
static int vce_default_deinitialize(void)
{
	return 0;
}
static int vce_default_get_info(char **engine_uuid, char **engine_name, char **engine_setting, bool *use_network)
{
	*engine_uuid = strdup("vce_engine_uuid");
	*engine_name = strdup("vce_engine_name");
	*engine_setting = NULL;
	*use_network = true;
	return 0;
}
static int vce_default_get_recording_format(const char *audio_id, vce_audio_type_e *types, int *rate, int *channels)
{
	*types = VCE_AUDIO_TYPE_PCM_S16_LE;
	*rate = 16000;
	*channels = 1;
	return 0;
}
static int vce_default_foreach_langs(vce_supported_language_cb callback, void *user_data)
{
	return 0;
}
static bool vce_default_is_lang_supported(const char *lang)
{
	return true;
}
static int vce_default_set_language(const char *language)
{
	return 0;
}
static int vce_default_set_commands(vce_cmd_h vc_command)
{
	return 0;
}
static int vce_default_unset_commands()
{
	return 0;
}
static int vce_default_start(bool stop_by_silence)
{
	return 0;
}
static int vce_default_set_recording(const void *data, unsigned int length, vce_speech_detect_e *silence_detected)
{
	return 0;
}
static int vce_default_stop()
{
	return 0;
}
static int vce_default_cancel(void)
{
	return 0;
}
static int vce_default_set_audio_type(const char *audio_type)
{
	return 0;
}
static int vce_default_set_domain(const char *domain)
{
	return 0;
}
static int vce_default_process_text(const char *text)
{
	return 0;
}
static int vce_default_process_list_event(const char *event)
{
	return 0;
}
static int vce_default_process_haptic_event(const char *event)
{
	return 0;
}
static int vce_private_data_set(const char* key, const char* data)
{
	return 0;
}
static int vce_private_data_requested(const char* key, char** data)
{
	return 0;
}
static int vce_nlu_base_info_requested(const char* key, char** value)
{
	return 0;
}
static int vce_specific_engine_request(const char* engine_app_id, const char* event, const char* request)
{
	return 0;
}
static bool vce_command(int id, int type, int format, const char *command, const char *param, int domain, void *user_data)
{
	return true;
}

static int vce_default_set_server_dialog(const char* app_id, const char* credential)
{
	return 0;
}
static int vce_request_tts(int pid, int utt_id, const char* text, const char* language, void* user_data)
{
	return 0;
}
static int vce_cancel_tts(int pid, int utt_id, void* user_data)
{
	return 0;
}
static int vce_tts_audio_format_request(int* rate, int* channel, int* audio_type, void* user_data)
{
	*rate = 16000;
	*channel = 0;
	*audio_type = 0;

	return 0;
}

static void vce_main_init()
{
	g_vce_init = false;
	if (true == g_vce_supported) {
		int ret = VCE_ERROR_NONE;
		ret = vce_main(g_argc, g_argv, &callback);
		if (VCE_ERROR_NONE == ret) {
			g_vce_init = true;
		} else {
			g_vce_init = false;
		}
	}
}

void utc_vce_startup(void)
{
	/* start of TC */
	g_vce_supported = false;
	bool mic_supported = false;
	bool vc_supported = false;
	if (0 == system_info_get_platform_bool("http://tizen.org/feature/speech.control", &vc_supported)) {
		if (0 == system_info_get_platform_bool("http://tizen.org/feature/microphone", &mic_supported)) {
			if (true == vc_supported && true == mic_supported) {
				g_vce_supported = true;
			}
		}
	}

	transfer_arg(&g_argc, &g_argv);

	callback.version = 1;

	callback.initialize	= vce_default_initialize;
	callback.deinitialize	= vce_default_deinitialize;

	callback.get_info	= vce_default_get_info;
	callback.get_recording_format	= vce_default_get_recording_format;
	callback.foreach_langs	= vce_default_foreach_langs;
	callback.is_lang_supported	= vce_default_is_lang_supported;

	callback.set_language	= vce_default_set_language;
	callback.set_commands	= vce_default_set_commands;
	callback.unset_commands	= vce_default_unset_commands;

	callback.start		= vce_default_start;
	callback.set_recording	= vce_default_set_recording;
	callback.stop		= vce_default_stop;
	callback.cancel		= vce_default_cancel;

	callback.set_audio_type	= vce_default_set_audio_type;
	callback.set_server_dialog = vce_default_set_server_dialog;
	callback.set_domain	= vce_default_set_domain;
	callback.process_text	= vce_default_process_text;
	callback.process_list_event	= vce_default_process_list_event;
	callback.process_haptic_event	= vce_default_process_haptic_event;
}

void utc_vce_cleanup(void)
{
	/* end of TC */
}

/**
 * @testcase		utc_vce_main_p
 * @since_tizen		4.0
 * @description		Positive UTC for vce main function
 */
int utc_vce_main_p(void)
{
	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);
	} else {
		assert_eq(g_vce_init, true);
	}

	return 0;
}

/**
 * @testcase		utc_vce_main_n
 * @since_tizen		4.0
 * @description		Negative UTC for vce main function
 */
int utc_vce_main_n(void)
{
	int ret = VCE_ERROR_NONE;

	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_main(g_argc, g_argv, &callback);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		ret = vce_main(g_argc, g_argv, NULL);
		assert_eq(ret, VCE_ERROR_OPERATION_FAILED);
	}

	return 0;
}

/**
 * @testcase		utc_vce_send_result_p
 * @since_tizen		4.0
 * @description		Positive UTC for sending result
 */
int utc_vce_send_result_p(void)
{
	int ret = VCE_ERROR_NONE;
	int is_consumed;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_send_result(VCE_RESULT_EVENT_SUCCESS, NULL, 0, "text", NULL, NULL, VC_RESULT_MESSAGE_NONE, &is_consumed, NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_send_result(VCE_RESULT_EVENT_SUCCESS, NULL, 0, "text", NULL, NULL, VC_RESULT_MESSAGE_NONE, &is_consumed, NULL);
		assert_eq(ret, VCE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vce_send_result_n
 * @since_tizen		4.0
 * @description		Negative UTC for sending result (invalid parameter failure)
 */
int utc_vce_send_result_n(void)
{
	int ret = VCE_ERROR_NONE;
	int is_consumed;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_send_result(1234, NULL, 0, "text", NULL, NULL, VC_RESULT_MESSAGE_NONE, &is_consumed, NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_send_result(1234, NULL, 0, "text", NULL, NULL, VC_RESULT_MESSAGE_NONE, &is_consumed, NULL);
		assert_eq(ret, VCE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vce_send_asr_result_n1
 * @since_tizen		4.0
 * @description		Negative UTC for sending result (operation failure)
 */
int utc_vce_send_asr_result_n1(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_send_asr_result(VCE_ASR_RESULT_EVENT_FINAL_RESULT, "asr_result", NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_send_asr_result(VCE_ASR_RESULT_EVENT_FINAL_RESULT, "asr_result", NULL);
		assert_eq(ret, VCE_ERROR_OPERATION_FAILED);
	}

	return 0;
}

/**
 * @testcase		utc_vce_send_asr_result_n2
 * @since_tizen		4.0
 * @description		Negative UTC for sending result (invalid parameter failure)
 */
int utc_vce_send_asr_result_n2(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_send_asr_result(1234, "asr_result", NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_send_asr_result(1234, "asr_result", NULL);
		assert_eq(ret, VCE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vce_send_nlg_result_n
 * @since_tizen		4.0
 * @description		Negative UTC for sending nlg result (operation failure)
 */
int utc_vce_send_nlg_result_n(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_send_nlg_result("nlg_result", NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_send_nlg_result("nlg_result", NULL);
		assert_eq(ret, VCE_ERROR_OPERATION_FAILED);
	}

	return 0;
}

/**
 * @testcase		utc_vce_send_specific_engine_result_p
 * @since_tizen		4.0
 * @description		Positive UTC for sending specific engine result
 */
int utc_vce_send_specific_engine_result_p(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_send_specific_engine_result("org.tizen.vc-engine-default", "sendTTS", "Success", NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_send_specific_engine_result("org.tizen.vc-engine-default", "sendTTS", "Success", NULL);
		assert_eq(ret, VCE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vce_send_specific_engine_result_n
 * @since_tizen		4.0
 * @description		Negative UTC for sending specific engine result (invalid parameter failure)
 */
int utc_vce_send_specific_engine_result_n(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_send_specific_engine_result(NULL, NULL, NULL, NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_send_specific_engine_result(NULL, NULL, NULL, NULL);
		assert_eq(ret, VCE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vce_send_error_p
 * @since_tizen		4.0
 * @description		Positive UTC for sending error
 */
int utc_vce_send_error_p(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_send_error(VCE_ERROR_NONE, "msg", NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_send_error(VCE_ERROR_NONE, "msg", NULL);
		assert_eq(ret, VCE_ERROR_NONE);
	}

	return 0;
}


/**
 * @testcase		utc_vce_set_private_data_set_cb_p
 * @since_tizen		4.0
 * @description		Positive UTC for setting private data cb
 */
int utc_vce_set_private_data_set_cb_p(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_set_private_data_set_cb(vce_private_data_set);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);
	
		ret = vce_set_private_data_set_cb(vce_private_data_set);
		assert_eq(ret, VCE_ERROR_NONE);	
	}

	return 0;
}

/**
 * @testcase		utc_vce_set_private_data_set_cb_n
 * @since_tizen		4.0
 * @description		Negative UTC for setting private data cb (invalid parameter failure)
 */
int utc_vce_set_private_data_set_cb_n(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_set_private_data_set_cb(NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_set_private_data_set_cb(NULL);
		assert_eq(ret, VCE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vce_set_private_data_requested_cb_p
 * @since_tizen		4.0
 * @description		Positive UTC for setting private data requested cb
 */
int utc_vce_set_private_data_requested_cb_p(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_set_private_data_requested_cb(vce_private_data_requested);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_set_private_data_requested_cb(vce_private_data_requested);
		assert_eq(ret, VCE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vce_set_private_data_requested_cb_n
 * @since_tizen		4.0
 * @description		Negative UTC for setting private data requested cb (invalid parameter failure)
 */
int utc_vce_set_private_data_requested_cb_n(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_set_private_data_requested_cb(NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_set_private_data_requested_cb(NULL);
		assert_eq(ret, VCE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vce_set_nlu_base_info_requested_cb_p
 * @since_tizen		4.0
 * @description		Positive UTC for setting nlu base info requested cb
 */
int utc_vce_set_nlu_base_info_requested_cb_p(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_set_nlu_base_info_requested_cb(vce_nlu_base_info_requested);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_set_nlu_base_info_requested_cb(vce_nlu_base_info_requested);
		assert_eq(ret, VCE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vce_set_nlu_base_info_requested_cb_n
 * @since_tizen		4.0
 * @description		Negative UTC for setting nlu base info requested cb (invalid parameter failure)
 */
int utc_vce_set_nlu_base_info_requested_cb_n(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_set_nlu_base_info_requested_cb(NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_set_nlu_base_info_requested_cb(NULL);
		assert_eq(ret, VCE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vce_set_specific_engine_request_cb_p
 * @since_tizen		4.0
 * @description		Positive UTC for setting specific engine request cb
 */
int utc_vce_set_specific_engine_request_cb_p(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_set_specific_engine_request_cb(vce_specific_engine_request);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_set_specific_engine_request_cb(vce_specific_engine_request);
		assert_eq(ret, VCE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vce_set_specific_engine_request_cb_n
 * @since_tizen		4.0
 * @description		Negative UTC for setting specific engine request cb (invalid parameter failure)
 */
int utc_vce_set_specific_engine_request_cb_n(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_set_specific_engine_request_cb(NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_set_specific_engine_request_cb(NULL);
		assert_eq(ret, VCE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vce_unset_specific_engine_request_cb_p
 * @since_tizen		4.0
 * @description		Positive UTC for unsetting specific engine request cb
 */
int utc_vce_unset_specific_engine_request_cb_p(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_unset_specific_engine_request_cb();
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_unset_specific_engine_request_cb();
		assert_eq(ret, VCE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vce_get_foreach_command_n
 * @since_tizen		4.0
 * @description		Negative UTC for getting foreach command (invalid parameter failure)
 */
int utc_vce_get_foreach_command_n(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_get_foreach_command(g_vce_command, NULL, NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_get_foreach_command(g_vce_command, NULL, NULL);
		assert_eq(ret, VCE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vce_get_command_count_p
 * @since_tizen		4.0
 * @description		Positive UTC for getting command count
 */
int utc_vce_get_command_count_p(void)
{
	int ret = VCE_ERROR_NONE;
	int count = 0;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_get_command_count(g_vce_command, &count);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_get_command_count(g_vce_command, &count);
		assert_eq(ret, VCE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vce_get_command_count_n
 * @since_tizen		4.0
 * @description		Negative UTC for getting command count (invalid parameter failure)
 */
int utc_vce_get_command_count_n(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_get_command_count(g_vce_command, NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_get_command_count(g_vce_command, NULL);
		assert_eq(ret, VCE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vce_get_audio_type_p
 * @since_tizen		4.0
 * @description		Positive UTC for getting audio type
 */
int utc_vce_get_audio_type_p(void)
{
	int ret = VCE_ERROR_NONE;
	char *audio_type = NULL;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_get_audio_type(&audio_type);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_get_audio_type(&audio_type);
		assert_eq(ret, VCE_ERROR_NONE);
	}

	if (NULL != audio_type) {
		free(audio_type);
	}

	return 0;
}

/**
 * @testcase		utc_vce_get_audio_type_n
 * @since_tizen		4.0
 * @description		Negative UTC for getting audio type (invalid parameter failure)
 */
int utc_vce_get_audio_type_n(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_get_audio_type(NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_get_audio_type(NULL);
		assert_eq(ret, VCE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vce_set_private_data_p
 * @since_tizen		4.0
 * @description		Positive UTC for setting private data
 */
int utc_vce_set_private_data_p(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_set_private_data("key", "data");
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_set_private_data("key", "data");
		assert_eq(ret, VCE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vce_set_private_data_n
 * @since_tizen		4.0
 * @description		Negative UTC for setting private data (invalid parameter failure)
 */
int utc_vce_set_private_data_n(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_set_private_data(NULL, NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_set_private_data(NULL, NULL);
		assert_eq(ret, VCE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vce_get_private_data_p
 * @since_tizen		4.0
 * @description		Positive UTC for getting private data
 */
int utc_vce_get_private_data_p(void)
{
	int ret = VCE_ERROR_NONE;
	char *data = NULL;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_get_private_data("key", &data);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_get_private_data("key", &data);
		assert_eq(ret, VCE_ERROR_NONE);
	}

	if (NULL != data) {
		free(data);
	}

	return 0;
}

/**
 * @testcase		utc_vce_get_private_data_n
 * @since_tizen		4.0
 * @description		Negative UTC for getting private data (invalid parameter failure)
 */
int utc_vce_get_private_data_n(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_get_private_data(NULL, NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_get_private_data(NULL, NULL);
		assert_eq(ret, VCE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vce_start_recording_p
 * @since_tizen		4.0
 * @description		Positive UTC for starting recording
 */
int utc_vce_start_recording_p(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_start_recording();
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_start_recording();
		assert_eq(ret, VCE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vce_stop_recording_p
 * @since_tizen		4.0
 * @description		Positive UTC for stopping recording
 */
int utc_vce_stop_recording_p(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_start_recording();
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);

		ret = vce_stop_recording();
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_start_recording();
		assert_eq(ret, VCE_ERROR_NONE);

		ret = vce_stop_recording();
		assert_eq(ret, VCE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vce_send_feedback_audio_format_p
 * @since_tizen		4.0
 * @description		Positive UTC for sending feedback audio format
 */
int utc_vce_send_feedback_audio_format_p(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_send_feedback_audio_format(16000, VCE_AUDIO_CHANNEL_MONO, VCE_AUDIO_TYPE_PCM_S16_LE);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_send_feedback_audio_format(16000, VCE_AUDIO_CHANNEL_MONO, VCE_AUDIO_TYPE_PCM_S16_LE);
		assert_eq(ret, VCE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vce_send_feedback_audio_format_n
 * @since_tizen		4.0
 * @description		Negative UTC for sending feedback audio format (invalid parameter failure)
 */
int utc_vce_send_feedback_audio_format_n(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_send_feedback_audio_format(16000, -1, -1);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_send_feedback_audio_format(16000, -1, -1);
		assert_eq(ret, VCE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vce_send_feedback_streaming_p
 * @since_tizen		4.0
 * @description		Positive UTC for sending feedback streaming
 */
int utc_vce_send_feedback_streaming_p(void)
{
	int ret = VCE_ERROR_NONE;
	char* txt_feedback = "Start sending feedback streaming";

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_send_feedback_streaming(1, txt_feedback, strlen(txt_feedback));
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_send_feedback_streaming(1, txt_feedback, strlen(txt_feedback));
		assert_eq(ret, VCE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vce_send_feedback_streaming_n
 * @since_tizen		4.0
 * @description		Negative UTC for sending feedback streaming (invalid parameter failure)
 */
int utc_vce_send_feedback_streaming_n(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_send_feedback_streaming(1, NULL, 0);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_send_feedback_streaming(1, NULL, 0);
		assert_eq(ret, VCE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vce_set_request_tts_cb_p
 * @since_tizen		5.0
 * @description		Positive UTC for setting request tts cb
 */
int utc_vce_set_request_tts_cb_p(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_set_request_tts_cb(vce_request_tts, NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_set_request_tts_cb(vce_request_tts, NULL);
		assert_eq(ret, VCE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vce_set_request_tts_cb_n
 * @since_tizen		5.0
 * @description		Negative UTC for setting request tts cb (invalid parameter failure)
 */
int utc_vce_set_request_tts_cb_n(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_set_request_tts_cb(NULL, NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_set_request_tts_cb(NULL, NULL);
		assert_eq(ret, VCE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vce_unset_request_tts_cb_p
 * @since_tizen		5.0
 * @description		Positive UTC for unsetting request tts cb
 */
int utc_vce_unset_request_tts_cb_p(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_unset_request_tts_cb();
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_unset_request_tts_cb();
		assert_eq(ret, VCE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vce_set_cancel_tts_cb_p
 * @since_tizen		5.0
 * @description		Positive UTC for setting cancel tts cb
 */
int utc_vce_set_cancel_tts_cb_p(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_set_cancel_tts_cb(vce_cancel_tts, NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_set_cancel_tts_cb(vce_cancel_tts, NULL);
		assert_eq(ret, VCE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vce_set_cancel_tts_cb_n
 * @since_tizen		5.0
 * @description		Negative UTC for setting cancel tts cb (invalid parameter failure)
 */
int utc_vce_set_cancel_tts_cb_n(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_set_cancel_tts_cb(NULL, NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_set_cancel_tts_cb(NULL, NULL);
		assert_eq(ret, VCE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vce_unset_cancel_tts_cb_p
 * @since_tizen		5.0
 * @description		Positive UTC for unsetting cancel tts cb
 */
int utc_vce_unset_cancel_tts_cb_p(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_unset_cancel_tts_cb();
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_unset_cancel_tts_cb();
		assert_eq(ret, VCE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vce_set_tts_audio_format_request_cb_p
 * @since_tizen		5.0
 * @description		Positive UTC for setting request tts audio format cb
 */
int utc_vce_set_tts_audio_format_request_cb_p(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_set_tts_audio_format_request_cb(vce_tts_audio_format_request, NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_set_tts_audio_format_request_cb(vce_tts_audio_format_request, NULL);
		assert_eq(ret, VCE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vce_set_tts_audio_format_request_cb_n
 * @since_tizen		5.0
 * @description		Negative UTC for setting request tts audio format cb (invalid parameter failure)
 */
int utc_vce_set_tts_audio_format_request_cb_n(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_set_tts_audio_format_request_cb(NULL, NULL);
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_set_tts_audio_format_request_cb(NULL, NULL);
		assert_eq(ret, VCE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vce_unset_get_tts_audio_format_cb_p
 * @since_tizen		5.0
 * @description		Positive UTC for unsetting get tts audio format cb
 */
int utc_vce_unset_get_tts_audio_format_cb_p(void)
{
	int ret = VCE_ERROR_NONE;

	vce_main_init();
	if (false == g_vce_supported) {
		assert_eq(g_vce_init, false);

		ret = vce_unset_get_tts_audio_format_cb();
		assert_eq(ret, VCE_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vce_init, true);

		ret = vce_unset_get_tts_audio_format_cb();
		assert_eq(ret, VCE_ERROR_NONE);
	}

	return 0;
}
