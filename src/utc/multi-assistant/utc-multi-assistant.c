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
#include <stdlib.h>
#include <system_info.h>
#include <multi_assistant.h>
#include <multi_assistant_common.h>
#include <Ecore.h>

static int g_ma_init = false;
static ma_state_e g_ma_state = MA_STATE_NONE;
static bool g_ma_supported = false;
static ma_active_state_e g_ma_active_state = MA_ACTIVE_STATE_INACTIVE;
static ma_assistant_info_h g_ma_assistant_handle = NULL;

static void __ma_state_changed_cb(ma_state_e previous, ma_state_e current, void* user_data)
{
	g_ma_state = current;
}

static void __ma_error_cb(ma_error_e reason, void* user_data)
{
}

static void __ma_language_changed_cb(const char* previous, const char* current, void* user_data)
{
}


static void __ma_audio_streaming_cb(ma_audio_streaming_event_e event, char* buffer, int len, void* user_data)
{
}

static void __ma_active_state_changed_cb(ma_active_state_e previous, ma_active_state_e current, void* user_data)
{
	g_ma_active_state = current;
}

static void __ma_set_wakeup_engine_command_changed_cb(const char *command, void* user_data)
{
}

static int __ma_assistant_info_list_cb(ma_assistant_info_h handle, void* user_data)
{
	g_ma_assistant_handle = handle;
}

static void __ma_preprocessing_information_changed_cb(const char* app_id, void* user_data)
{
}

static void __ma_audio_streaming_data_section_changed_cb(ma_audio_streaming_data_section_e section, void* user_data)
{
}

static void __ma_service_state_changed_cb(ma_service_state_e previous, ma_service_state_e current, void* user_data)
{
}

static void __ma_voice_key_status_changed_cb(ma_voice_key_status_e status, void* user_data)
{
}

/**
 * @function		utc_multi_assistant_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_multi_assistant_startup(void)
{
	g_ma_supported = false;
	bool mic_supported = false;
	bool ma_supported = true;
	if (0 == system_info_get_platform_bool("http://tizen.org/feature/multi_assistant", &ma_supported)) {
		if (0 == system_info_get_platform_bool("http://tizen.org/feature/microphone", &mic_supported)) {
			if (true == ma_supported && true == mic_supported) {
				g_ma_supported = true;
			}
		}
	}

	g_ma_init = false;
	if (true == g_ma_supported) {
		int ret = MA_ERROR_NONE;
		ret = ma_initialize();
		if (MA_ERROR_NONE == ret) {
			ret = ma_set_state_changed_cb(__ma_state_changed_cb, NULL);
			if (MA_ERROR_NONE != ret) {
				g_ma_init = false;
			} else {
				g_ma_init = true;
			}
		} else {
			g_ma_init = false;
		}
	}

	g_ma_assistant_handle = NULL;
}

/**
 * @function		utc_multi_assistant_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_multi_assistant_cleanup(void)
{
	int ret = MA_ERROR_NONE;

	if (true == g_ma_supported) {
		ret = ma_unset_state_changed_cb();
		assert_eq(ret, MA_ERROR_NONE);
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);
	}

	g_ma_init = false;
}


/**
 * @testcase		utc_ma_initialize_p
 * @since_tizen		5.0
 * @description		Positive UTC for initialize multi-assistant handle
 */
int utc_ma_initialize_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);
	} else {
		assert_eq(g_ma_init, true);
	}

	return 0;
}

/**
 * @testcase		utc_ma_deinitialize_p
 * @since_tizen		5.0
 * @description		Positive UTC for deinitialize multi-assistant handle
 */
int utc_ma_deinitialize_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_deinitialize_n
 * @since_tizen		5.0
 * @description		Negative UTC for deinitialize multi-assistant handle (Already deinitialized)
 */
int utc_ma_deinitialize_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_prepare_p
 * @since_tizen		5.0
 * @description		Positive UTC for connect multi-assistant service
 */
int utc_ma_prepare_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_prepare_n
 * @since_tizen		5.0
 * @description		Negative UTC for connect multi-assistant service (Invalid state)
 */
int utc_ma_prepare_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		ma_deinitialize();

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unprepare_p
 * @since_tizen		5.0
 * @description		Positive UTC for disconnect multi-assistant service
 */
int utc_ma_unprepare_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unprepare_n
 * @since_tizen		5.0
 * @description		Negative UTC for disconnect multi-assistant service (Invalid state)
 */
int utc_ma_unprepare_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_get_state_p
 * @since_tizen		5.0
 * @description		Positive UTC for get current state
 */
int utc_ma_get_state_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ma_state_e state = -1;
		ret = ma_get_state(&state);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ma_state_e state = -1;
		ret = ma_get_state(&state);
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_get_state_n1
 * @since_tizen		5.0
 * @description		Negative UTC for get current state (Invalid parameter)
 */
int utc_ma_get_state_n1(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_get_state(NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_get_state(NULL);
		assert_eq(ret, MA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_ma_get_state_n2
 * @since_tizen		5.0
 * @description		Negative UTC for get current state (Invalid state)
 */
int utc_ma_get_state_n2(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ma_state_e state = -1;
		ret = ma_get_state(&state);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ma_state_e state = -1;
		ret = ma_get_state(&state);
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_get_current_language_p
 * @since_tizen		5.0
 * @description		Positive UTC for get current language
 */
int utc_ma_get_current_language_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		char *lang = NULL;
		ret = ma_get_current_language(&lang);
		if (NULL != lang) {
				free(lang);
				lang = NULL;
		}
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		char *lang = NULL;
		ret = ma_get_current_language(&lang);
		if (NULL != lang) {
			free(lang);
			lang = NULL;
		}
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_get_current_language_n
 * @since_tizen		5.0
 * @description		Negative UTC for get current language (Invalid parameter)
 */
int utc_ma_get_current_language_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_get_current_language(NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_get_current_language(NULL);
		assert_eq(ret, MA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_ma_get_recording_audio_format_p
 * @since_tizen		3.0
 * @description		Positive UTC for getting the recording audio format
 */
int utc_ma_get_recording_audio_format_p(void)
{
	int rate;
	ma_audio_channel_e channel;
	ma_audio_type_e audio_type;

	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_get_recording_audio_format(&rate, &channel, &audio_type);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_get_recording_audio_format(&rate, &channel, &audio_type);
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_get_recording_audio_format_n1
 * @since_tizen		3.0
 * @description		Negative UTC for getting the recording audio format (Invalid parameter)
 */
int utc_ma_get_recording_audio_format_n1(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_get_recording_audio_format(NULL, NULL, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_get_recording_audio_format(NULL, NULL, NULL);
		assert_eq(ret, MA_ERROR_INVALID_PARAMETER);

		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_get_recording_audio_format_n2
 * @since_tizen		3.0
 * @description		Negative UTC for getting the recording audio format (Invalid state)
 */
int utc_ma_get_recording_audio_format_n2(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_get_recording_audio_format(NULL, NULL, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		int rate;
		ma_audio_channel_e channel;
		ma_audio_type_e audio_type;

		ret = ma_get_recording_audio_format(&rate, &channel, &audio_type);
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_state_changed_cb_p
 * @since_tizen		5.0
 * @description		Positive UTC for set state changed callback
 */
int utc_ma_set_state_changed_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);
		int ret = MA_ERROR_NONE;
		ret = ma_set_state_changed_cb(__ma_state_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_state_changed_cb_n1
 * @since_tizen		5.0
 * @description		Negative UTC for set state changed callback (Invalid parameter)
 */
int utc_ma_set_state_changed_cb_n1(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_state_changed_cb(NULL, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_state_changed_cb(NULL, NULL);
		assert_eq(ret, MA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_state_changed_cb_n2
 * @since_tizen		5.0
 * @description		Negative UTC for set state changed callback (Invalid state)
 */
int utc_ma_set_state_changed_cb_n2(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_state_changed_cb(__ma_state_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_set_state_changed_cb(__ma_state_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_state_changed_cb_p
 * @since_tizen		5.0
 * @description		Positive UTC for unset state changed callback
 */
int utc_ma_unset_state_changed_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_state_changed_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_state_changed_cb();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_state_changed_cb_n
 * @since_tizen		5.0
 * @description		Negative UTC for unset state changed callback (Invalid state)
 */
int utc_ma_unset_state_changed_cb_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_state_changed_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unset_state_changed_cb();
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_error_cb_p
 * @since_tizen		5.0
 * @description		Positive UTC for set error callback
 */
int utc_ma_set_error_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_error_cb(__ma_error_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_error_cb(__ma_error_cb, NULL);
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_error_cb_n1
 * @since_tizen		5.0
 * @description		Negative UTC for set error callback (Invalid parameter)
 */
int utc_ma_set_error_cb_n1(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_error_cb(NULL, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_error_cb(NULL, NULL);
		assert_eq(ret, MA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_error_cb_n2
 * @since_tizen		5.0
 * @description		Negative UTC for set error callback (Invalid state)
 */
int utc_ma_set_error_cb_n2(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_error_cb(__ma_error_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_set_error_cb(__ma_error_cb, NULL);
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_error_cb_p
 * @since_tizen		5.0
 * @description		Positive UTC for unset error callback
 */
int utc_ma_unset_error_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_error_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_error_cb(__ma_error_cb, NULL);
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unset_error_cb();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_error_cb_n
 * @since_tizen		5.0
 * @description		Negative UTC for unset error callback (Invalid state)
 */
int utc_ma_unset_error_cb_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_error_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unset_error_cb();
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_language_changed_cb_p
 * @since_tizen		5.0
 * @description		Positive UTC for set language changed callback
 */
int utc_ma_set_language_changed_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_language_changed_cb(__ma_language_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_language_changed_cb(__ma_language_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_language_changed_cb_n1
 * @since_tizen		5.0
 * @description		Negative UTC for set language changed callback (invalid parameter)
 */
int utc_ma_set_language_changed_cb_n1(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_language_changed_cb(NULL, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_language_changed_cb(NULL, NULL);
		assert_eq(ret, MA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_language_changed_cb_n2
 * @since_tizen		5.0
 * @description		Negative UTC for set language changed callback (Invalid state)
 */
int utc_ma_set_language_changed_cb_n2(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_language_changed_cb(__ma_language_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_set_language_changed_cb(__ma_language_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_language_changed_cb_p
 * @since_tizen		5.0
 * @description		Positive UTC for unset language changed callback
 */
int utc_ma_unset_language_changed_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_language_changed_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_language_changed_cb(__ma_language_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unset_language_changed_cb();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_language_changed_cb_n
 * @since_tizen		5.0
 * @description		Negative UTC for unset language changed callback (Invalid state)
 */
int utc_ma_unset_language_changed_cb_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_language_changed_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unset_language_changed_cb();
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_audio_streaming_cb_p
 * @since_tizen		5.0
 * @description		Positive UTC for set audio streaming callback
 */
int utc_ma_set_audio_streaming_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_audio_streaming_cb(__ma_audio_streaming_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_audio_streaming_cb(__ma_audio_streaming_cb, NULL);
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_audio_streaming_cb_n1
 * @since_tizen		5.0
 * @description		Negative UTC for set audio streaming callback (invalid parameter)
 */
int utc_ma_set_audio_streaming_cb_n1(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_audio_streaming_cb(NULL, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_audio_streaming_cb(NULL, NULL);
		assert_eq(ret, MA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_audio_streaming_cb_n2
 * @since_tizen		5.0
 * @description		Negative UTC for set audio streaming callback (Invalid state)
 */
int utc_ma_set_audio_streaming_cb_n2(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_audio_streaming_cb(__ma_audio_streaming_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_set_audio_streaming_cb(__ma_audio_streaming_cb, NULL);
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_audio_streaming_cb_p
 * @since_tizen		5.0
 * @description		Positive UTC for unset audio streaming callback
 */
int utc_ma_unset_audio_streaming_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_audio_streaming_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_audio_streaming_cb(__ma_audio_streaming_cb, NULL);
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unset_audio_streaming_cb();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_audio_streaming_cb_n
 * @since_tizen		5.0
 * @description		Negative UTC for unset audio streaming callback (Invalid state)
 */
int utc_ma_unset_audio_streaming_cb_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_audio_streaming_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unset_audio_streaming_cb();
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_send_asr_result_p
 * @since_tizen		5.0
 * @description		Positive UTC for send asr result
 */
int utc_ma_send_asr_result_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_send_asr_result(MA_ASR_RESULT_EVENT_PARTIAL_RESULT, "Hello");
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_send_asr_result(MA_ASR_RESULT_EVENT_PARTIAL_RESULT, "Hello");
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_send_asr_result_n1
 * @since_tizen		5.0
 * @description		Negative UTC for send asr result (invalid parameter)
 */
int utc_ma_send_asr_result_n1(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_send_asr_result(100, "Hello");
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_send_asr_result(100, "Hello");
		assert_eq(ret, MA_ERROR_INVALID_PARAMETER);

		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_send_asr_result_n2
 * @since_tizen		5.0
 * @description		Negative UTC for send asr result (invalid state)
 */
int utc_ma_send_asr_result_n2(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_send_asr_result(MA_ASR_RESULT_EVENT_PARTIAL_RESULT, "Hello");
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_send_asr_result(MA_ASR_RESULT_EVENT_PARTIAL_RESULT, "Hello");
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_send_result_p
 * @since_tizen		5.0
 * @description		Positive UTC for send result
 */
int utc_ma_send_result_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_send_result("display text", "utterance text", "json result");
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_send_result("display text", "utterance text", "json result");
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_send_result_n
 * @since_tizen		5.0
 * @description		Negative UTC for send result (invalid state)
 */
int utc_ma_send_result_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_send_result("display text", "utterance text", "json result");
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_send_result("display text", "utterance text", "json result");
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_send_recognition_result_p
 * @since_tizen		5.5
 * @description		Positive UTC for send recognition result
 */
int utc_ma_send_recognition_result_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_send_recognition_result(MA_RECOGNITION_RESULT_EVENT_SUCCESS);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_send_recognition_result(MA_RECOGNITION_RESULT_EVENT_SUCCESS);
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_send_recognition_result_n
 * @since_tizen		5.5
 * @description		Negative UTC for send recognition result
 */
int utc_ma_send_recognition_result_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_send_recognition_result(MA_RECOGNITION_RESULT_EVENT_EMPTY_TEXT);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_send_recognition_result(MA_RECOGNITION_RESULT_EVENT_EMPTY_TEXT);
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_active_state_changed_cb_p
 * @since_tizen		5.5
 * @description		Positive UTC for set active state changed callback
 */
int utc_ma_set_active_state_changed_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);
		int ret = MA_ERROR_NONE;
		ret = ma_set_active_state_changed_cb(__ma_active_state_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_active_state_changed_cb_n1
 * @since_tizen		5.5
 * @description		Negative UTC for set active state changed callback (Invalid parameter)
 */
int utc_ma_set_active_state_changed_cb_n1(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_active_state_changed_cb(NULL, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_active_state_changed_cb(NULL, NULL);
		assert_eq(ret, MA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_active_state_changed_cb_n2
 * @since_tizen		5.5
 * @description		Negative UTC for set active state changed callback (Invalid state)
 */
int utc_ma_set_active_state_changed_cb_n2(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_active_state_changed_cb(__ma_active_state_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_set_active_state_changed_cb(__ma_active_state_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_active_state_changed_cb_p
 * @since_tizen		5.5
 * @description		Positive UTC for unset active state changed callback
 */
int utc_ma_unset_active_state_changed_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_active_state_changed_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_active_state_changed_cb();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_active_state_changed_cb_n
 * @since_tizen		5.5
 * @description		Negative UTC for unset state changed callback (Invalid state)
 */
int utc_ma_unset_active_state_changed_cb_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_active_state_changed_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unset_active_state_changed_cb();
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_start_receiving_audio_streaming_data_p
 * @since_tizen		5.5
 * @description		Positive UTC for start receiving audio stream data
 */
int utc_ma_start_receiving_audio_streaming_data_p(void)
{
	ma_audio_streaming_data_type_e type = MA_AUDIO_STREAMING_DATA_TYPE_CURRENT_UTTERANCE;

	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_start_receiving_audio_streaming_data(type);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_start_receiving_audio_streaming_data(type);
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_start_receiving_audio_streaming_data_n
 * @since_tizen		5.5
 * @description		Negative UTC for start receiving audio stream data
 */
int utc_ma_start_receiving_audio_streaming_data_n(void)
{
	ma_audio_streaming_data_type_e type = MA_AUDIO_STREAMING_DATA_TYPE_CURRENT_UTTERANCE;
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_start_receiving_audio_streaming_data(type);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_start_receiving_audio_streaming_data(type);
		assert_eq(ret, MA_ERROR_INVALID_STATE);

	}

	return 0;
}

/**
 * @testcase		utc_ma_stop_receiving_audio_streaming_data_p
 * @since_tizen		5.5
 * @description		Positive UTC for stop receiving audio stream data
 */
int utc_ma_stop_receiving_audio_streaming_data_p(void)
{
	ma_audio_streaming_data_type_e type = MA_AUDIO_STREAMING_DATA_TYPE_CURRENT_UTTERANCE;

	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_stop_receiving_audio_streaming_data(type);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_stop_receiving_audio_streaming_data(type);
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_stop_receiving_audio_streaming_data_n
 * @since_tizen		5.5
 * @description		Negative UTC for stop receiving audio stream data
 */
int utc_ma_stop_receiving_audio_streaming_data_n(void)
{
	ma_audio_streaming_data_type_e type = MA_AUDIO_STREAMING_DATA_TYPE_CURRENT_UTTERANCE;
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_stop_receiving_audio_streaming_data(type);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_stop_receiving_audio_streaming_data(type);
		assert_eq(ret, MA_ERROR_INVALID_STATE);

	}

	return 0;
}

/**
 * @testcase		utc_ma_update_voice_feedback_state_p
 * @since_tizen		5.5
 * @description		Positive UTC for ma update voice feedback state
 */
int utc_ma_update_voice_feedback_state_p(void)
{
	ma_voice_feedback_state_e feedback_state = MA_VOICE_FEEDBACK_STATE_NONE;

	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_update_voice_feedback_state(feedback_state);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_update_voice_feedback_state(feedback_state);
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_update_voice_feedback_state_n
 * @since_tizen		5.5
 * @description		Negative UTC for update voice feedback state
 */
int utc_ma_update_voice_feedback_state_n(void)
{
	ma_voice_feedback_state_e feedback_state = MA_VOICE_FEEDBACK_STATE_NONE;
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_update_voice_feedback_state(feedback_state);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_update_voice_feedback_state(feedback_state);
		assert_eq(ret, MA_ERROR_INVALID_STATE);

	}

	return 0;
}

/**
 * @testcase		utc_ma_send_assistant_specific_command_p
 * @since_tizen		5.5
 * @description		Positive UTC for ma send assistant specific command
 */
int utc_ma_send_assistant_specific_command_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_send_assistant_specific_command("hello");
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_send_assistant_specific_command("hello");
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_send_assistant_specific_command_n
 * @since_tizen		5.5
 * @description		Negative UTC for  ma send assistant specific command
 */
int utc_ma_send_assistant_specific_command_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_send_assistant_specific_command("hello");
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_send_assistant_specific_command("hello");
		assert_eq(ret, MA_ERROR_INVALID_STATE);

	}

	return 0;
}

/**
 * @testcase		utc_ma_set_wakeup_engine_command_cb_p
 * @since_tizen		5.5
 * @description		Positive UTC for set wakeup engine command callback
 */
int utc_ma_set_wakeup_engine_command_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);
		int ret = MA_ERROR_NONE;
		ret = ma_set_wakeup_engine_command_cb(__ma_set_wakeup_engine_command_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_wakeup_engine_command_cb_n1
 * @since_tizen		5.5
 * @description		Negative UTC for set wakeup engine command callback (Invalid parameter)
 */
int utc_ma_set_wakeup_engine_command_cb_n1(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_wakeup_engine_command_cb(NULL, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_wakeup_engine_command_cb(NULL, NULL);
		assert_eq(ret, MA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_wakeup_engine_command_cb_n2
 * @since_tizen		5.5
 * @description		Negative UTC for set wakeup engine command callback (Invalid state)
 */
int utc_ma_set_wakeup_engine_command_cb_n2(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_wakeup_engine_command_cb(__ma_set_wakeup_engine_command_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_set_wakeup_engine_command_cb(__ma_set_wakeup_engine_command_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_wakeup_engine_command_cb_p
 * @since_tizen		5.5
 * @description		Positive UTC for unset wakeup engine command callback
 */
int utc_ma_unset_wakeup_engine_command_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_wakeup_engine_command_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_wakeup_engine_command_cb();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_wakeup_engine_command_cb_n
 * @since_tizen		5.5
 * @description		Negative UTC for unset wakeup engine command callback (Invalid state)
 */
int utc_ma_unset_wakeup_engine_command_cb_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_wakeup_engine_command_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unset_wakeup_engine_command_cb();
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_assistant_info_foreach_assistants_p
 * @since_tizen		5.5
 * @description		Positive UTC for assistant info foreach assistants
 */
int utc_ma_assistant_info_foreach_assistants_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_assistant_info_foreach_assistants(__ma_assistant_info_list_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_assistant_info_foreach_assistants(__ma_assistant_info_list_cb, NULL);
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_assistant_info_foreach_assistants_n
 * @since_tizen		5.5
 * @description		Negative UTC for  ma assistant info foreach assistants (Invalid parameter)
 */
int utc_ma_assistant_info_foreach_assistants_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_assistant_info_foreach_assistants(NULL, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_assistant_info_foreach_assistants(NULL, NULL);
		assert_eq(ret, MA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		ma_assistant_info_get_app_id_p
 * @since_tizen		5.5
 * @description		Positive UTC for assistant info get app id
 */
int utc_ma_assistant_info_get_app_id_p(void)
{
	char* app_id = NULL;
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_assistant_info_get_app_id(NULL, &app_id);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_assistant_info_foreach_assistants(__ma_assistant_info_list_cb, NULL);
		if (NULL == g_ma_assistant_handle) {
			ret = ma_assistant_info_get_app_id(g_ma_assistant_handle, &app_id);
			assert_eq(ret, MA_ERROR_INVALID_PARAMETER);
		} else {
			ret = ma_assistant_info_get_app_id(g_ma_assistant_handle, &app_id);
			assert_eq(ret, MA_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_ma_assistant_info_get_app_id_n
 * @since_tizen		5.5
 * @description		Negative UTC for assistant info get app id (Invalid parameter)
 */
int utc_ma_assistant_info_get_app_id_n(void)
{
	char* app_id = NULL;
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_assistant_info_get_app_id(NULL, &app_id);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_assistant_info_get_app_id(NULL, &app_id);
		assert_eq(ret, MA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_ma_assistant_info_get_enabled_status_p
 * @since_tizen		5.5
 * @description		Positive UTC for assistant info get enabled status
 */
int utc_ma_assistant_info_get_enabled_status_p(void)
{
	bool status = false;
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_assistant_info_get_enabled_status(NULL, &status);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_assistant_info_foreach_assistants(__ma_assistant_info_list_cb, NULL);
		if (NULL == g_ma_assistant_handle) {
			ret = ma_assistant_info_get_enabled_status(g_ma_assistant_handle, &status);
			assert_eq(ret, MA_ERROR_INVALID_PARAMETER);
		} else {
			ret = ma_assistant_info_get_enabled_status(g_ma_assistant_handle, &status);
			assert_eq(ret, MA_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_ma_assistant_info_get_enabled_status_n
 * @since_tizen		5.5
 * @description		Negative UTC for assistant info get enabled status (Invalid parameter)
 */
int utc_ma_assistant_info_get_enabled_status_n(void)
{
	bool status = false;
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_assistant_info_get_enabled_status(NULL, &status);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_assistant_info_get_enabled_status(NULL, &status);
		assert_eq(ret, MA_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase		utc_ma_get_recording_audio_source_type_p
 * @since_tizen		5.5
 * @description		Positive UTC for get recording audio source type
 */
int utc_ma_get_recording_audio_source_type_p(void)
{
	char* type = NULL;
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_get_recording_audio_source_type(&type);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_get_recording_audio_source_type(&type);
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NONE);
	}
	if (type) {
		free(type);
		type = NULL;
	}

	return 0;
}

/**
 * @testcase		utc_ma_get_recording_audio_source_type_n1
 * @since_tizen		5.5
 * @description		Negative UTC for get recording audio source type (Invalid parameter)
 */
int utc_ma_get_recording_audio_source_type_n1(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_get_recording_audio_source_type(NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_get_recording_audio_source_type(NULL);
		assert_eq(ret, MA_ERROR_INVALID_PARAMETER);

		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_get_recording_audio_source_type_n2
 * @since_tizen		5.5
 * @description		Negative UTC for get recording audio source type (Invalid state)
 */
int utc_ma_get_recording_audio_source_type_n2(void)
{
	char* type = NULL;
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_get_recording_audio_source_type(&type);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_get_recording_audio_source_type(&type);
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}
	if (type) {
		free(type);
		type = NULL;
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_background_volume_p
 * @since_tizen		5.5
 * @description		Positive UTC for set background volume
 */
int utc_ma_set_background_volume_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_background_volume(1.0);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_set_background_volume(1.0);
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_background_volume_n
 * @since_tizen		5.5
 * @description		Negative UTC for set background volume (Invalid state)
 */
int utc_ma_set_background_volume_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_background_volume(1.0);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_background_volume(1.0);
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_preprocessing_allow_mode_p
 * @since_tizen		5.5
 * @description		Positive UTC for set preprocessing allow mode
 */
int utc_ma_set_preprocessing_allow_mode_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_preprocessing_allow_mode(MA_PREPROCESSING_ALLOW_NONE, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_set_preprocessing_allow_mode(MA_PREPROCESSING_ALLOW_NONE, NULL);
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_preprocessing_allow_mode_n
 * @since_tizen		5.5
 * @description		Negative UTC for set preprocessing allow mode (Invalid state)
 */
int utc_ma_set_preprocessing_allow_mode_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_preprocessing_allow_mode(MA_PREPROCESSING_ALLOW_NONE, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_preprocessing_allow_mode(MA_PREPROCESSING_ALLOW_NONE, NULL);
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_preprocessing_information_changed_cb_p
 * @since_tizen		5.5
 * @description		Positive UTC for set preprocessing information changed callback
 */
int utc_ma_set_preprocessing_information_changed_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);
		int ret = MA_ERROR_NONE;
		ret = ma_set_preprocessing_information_changed_cb(__ma_preprocessing_information_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_preprocessing_information_changed_cb(__ma_preprocessing_information_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_preprocessing_information_changed_cb_n1
 * @since_tizen		5.5
 * @description		Negative UTC for set preprocessing information changed callback (Invalid parameter)
 */
int utc_ma_set_preprocessing_information_changed_cb_n1(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_preprocessing_information_changed_cb(NULL, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_preprocessing_information_changed_cb(NULL, NULL);
		assert_eq(ret, MA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_preprocessing_information_changed_cb_n2
 * @since_tizen		5.5
 * @description		Negative UTC for set preprocessing information changed callback (Invalid state)
 */
int utc_ma_set_preprocessing_information_changed_cb_n2(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_preprocessing_information_changed_cb(__ma_preprocessing_information_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_set_preprocessing_information_changed_cb(__ma_preprocessing_information_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_preprocessing_information_changed_cb_p
 * @since_tizen		5.5
 * @description		Positive UTC for unset preprocessing information changed callback
 */
int utc_ma_unset_preprocessing_information_changed_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_preprocessing_information_changed_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_preprocessing_information_changed_cb();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_preprocessing_information_changed_cb_n
 * @since_tizen		5.5
 * @description		Negative UTC for unset preprocessing information changed callback (Invalid state)
 */
int utc_ma_unset_preprocessing_information_changed_cb_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_preprocessing_information_changed_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unset_preprocessing_information_changed_cb();
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_send_preprocessing_result_p
 * @since_tizen		5.5
 * @description		Positive UTC for send preprocessing result
 */
int utc_ma_send_preprocessing_result_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_send_preprocessing_result(false);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_send_preprocessing_result(false);
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_send_preprocessing_result_n
 * @since_tizen		5.5
 * @description		Negative UTC for send preprocessing result (Invalid state)
 */
int utc_ma_send_preprocessing_result_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_send_preprocessing_result(false);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_send_preprocessing_result(false);
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_wake_word_audio_require_flag_p
 * @since_tizen		5.5
 * @description		Positive UTC for set wake word audio require flag
 */
int utc_ma_set_wake_word_audio_require_flag_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_wake_word_audio_require_flag(false);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_set_wake_word_audio_require_flag(false);
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unprepare();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_wake_word_audio_require_flag_n
 * @since_tizen		5.5
 * @description		Negative UTC for set wake word audio require flag (Invalid state)
 */
int utc_ma_set_wake_word_audio_require_flag_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_wake_word_audio_require_flag(false);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_wake_word_audio_require_flag(false);
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_audio_streaming_data_section_changed_cb_p
 * @since_tizen		5.5
 * @description		Positive UTC for set audio streaming data section changed callback
 */
int utc_ma_set_audio_streaming_data_section_changed_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);
		int ret = MA_ERROR_NONE;
		ret = ma_set_audio_streaming_data_section_changed_cb(__ma_audio_streaming_data_section_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_preprocessing_information_changed_cb(__ma_preprocessing_information_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_audio_streaming_data_section_changed_cb_n1
 * @since_tizen		5.5
 * @description		Negative UTC for set audio streaming data section changed callback (Invalid parameter)
 */
int utc_ma_set_audio_streaming_data_section_changed_cb_n1(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_audio_streaming_data_section_changed_cb(NULL, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_audio_streaming_data_section_changed_cb(NULL, NULL);
		assert_eq(ret, MA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_audio_streaming_data_section_changed_cb_n2
 * @since_tizen		5.5
 * @description		Negative UTC for set audio streaming data section changed callback (Invalid state)
 */
int utc_ma_set_audio_streaming_data_section_changed_cb_n2(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_audio_streaming_data_section_changed_cb(__ma_audio_streaming_data_section_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_set_audio_streaming_data_section_changed_cb(__ma_audio_streaming_data_section_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_audio_streaming_data_section_changed_cb_p
 * @since_tizen		5.5
 * @description		Positive UTC for unset audio streaming data section changed callback
 */
int utc_ma_unset_audio_streaming_data_section_changed_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_audio_streaming_data_section_changed_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_audio_streaming_data_section_changed_cb();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_audio_streaming_data_section_changed_cb_n
 * @since_tizen		5.5
 * @description		Negative UTC for unset audio streaming data section changed callback (Invalid state)
 */
int utc_ma_unset_audio_streaming_data_section_changed_cb_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_audio_streaming_data_section_changed_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unset_audio_streaming_data_section_changed_cb();
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_assistant_wakeup_language_p
 * @since_tizen		6.0
 * @description		Positive UTC for set assistant wakeup language
 */
int utc_ma_set_assistant_wakeup_language_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_assistant_wakeup_language("en_US");
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_set_assistant_wakeup_language("en_US");
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_assistant_wakeup_language_n
 * @since_tizen		6.0
 * @description		Negative UTC for set assistant wakeup language (Invalid parameter)
 */
int utc_ma_set_assistant_wakeup_language_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_assistant_wakeup_language(NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = ma_set_assistant_wakeup_language(NULL);
		assert_eq(ret, MA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_service_state_changed_cb_p
 * @since_tizen		6.0
 * @description		Positive UTC for set service state changed callback
 */
int utc_ma_set_service_state_changed_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_service_state_changed_cb(__ma_service_state_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_service_state_changed_cb(__ma_service_state_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_service_state_changed_cb_n
 * @since_tizen		6.0
 * @description		Negative UTC for set service state changed callback (Invalid state)
 */
int utc_ma_set_service_state_changed_cb_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_service_state_changed_cb(__ma_service_state_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_set_service_state_changed_cb(__ma_service_state_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_service_state_changed_cb_p
 * @since_tizen		6.0
 * @description		Positive UTC for unset service state changed callback
 */
int utc_ma_unset_service_state_changed_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_service_state_changed_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_service_state_changed_cb();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_service_state_changed_cb_n
 * @since_tizen		6.0
 * @description		Negative UTC for unset service state changed callback (Invalid state)
 */
int utc_ma_unset_service_state_changed_cb_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_service_state_changed_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unset_service_state_changed_cb();
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_voice_key_status_changed_cb_p
 * @since_tizen		6.0
 * @description		Positive UTC for set voice key status changed callback
 */
int utc_ma_set_voice_key_status_changed_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_voice_key_status_changed_cb(__ma_voice_key_status_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_set_voice_key_status_changed_cb(__ma_voice_key_status_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_set_voice_key_status_changed_cb_n
 * @since_tizen		6.0
 * @description		Negative UTC for set voice key status changed callback (Invalid state)
 */
int utc_ma_set_voice_key_status_changed_cb_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_set_voice_key_status_changed_cb(__ma_voice_key_status_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_set_voice_key_status_changed_cb(__ma_voice_key_status_changed_cb, NULL);
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_voice_key_status_changed_cb_p
 * @since_tizen		6.0
 * @description		Positive UTC for unset voice key status changed callback
 */
int utc_ma_unset_voice_key_status_changed_cb_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_voice_key_status_changed_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_voice_key_status_changed_cb();
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_unset_voice_key_status_changed_cb_n
 * @since_tizen		6.0
 * @description		Negative UTC for unset voice key status changed callback (Invalid state)
 */
int utc_ma_unset_voice_key_status_changed_cb_n(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_unset_voice_key_status_changed_cb();
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_unset_voice_key_status_changed_cb();
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_add_wake_word_p
 * @since_tizen		6.0
 * @description		Positive UTC for add wake word
 */
int utc_ma_add_wake_word_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_add_wake_word("Hi Tizen", "en_US");
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_add_wake_word("Hi Tizen", "en_US");
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_add_wake_word_n1
 * @since_tizen		6.0
 * @description		Negative UTC for add wake word (Invalid parameter)
 */
int utc_ma_add_wake_word_n1(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_add_wake_word("Hi Tizen", "en_US");
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_add_wake_word(NULL, NULL);
		assert_eq(ret, MA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_ma_add_wake_word_n2
 * @since_tizen		6.0
 * @description		Negative UTC for add wake word (Invalid state)
 */
int utc_ma_add_wake_word_n2(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_add_wake_word("Hi Tizen", "en_US");
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_add_wake_word("Hi Tizen", "en_US");
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_remove_wake_word_p
 * @since_tizen		6.0
 * @description		Positive UTC for add wake word
 */
int utc_ma_remove_wake_word_p(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_remove_wake_word("Hi Tizen", "en_US");
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_remove_wake_word("Hi Tizen", "en_US");
		assert_eq(ret, MA_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_ma_remove_wake_word_n1
 * @since_tizen		6.0
 * @description		Negative UTC for remove wake word (Invalid parameter)
 */
int utc_ma_remove_wake_word_n1(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_remove_wake_word("Hi Tizen", "en_US");
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_prepare();
		assert_eq(ret, MA_ERROR_NONE);

		while (MA_STATE_READY != g_ma_state) {
			ecore_main_loop_iterate();
		}

		ret = ma_remove_wake_word(NULL, NULL);
		assert_eq(ret, MA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_ma_remove_wake_word_n2
 * @since_tizen		6.0
 * @description		Negative UTC for remove wake word (Invalid state)
 */
int utc_ma_remove_wake_word_n2(void)
{
	if (false == g_ma_supported) {
		assert_eq(g_ma_init, false);

		int ret = MA_ERROR_NONE;
		ret = ma_remove_wake_word("Hi Tizen", "en_US");
		assert_eq(ret, MA_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_ma_init, true);

		int ret = MA_ERROR_NONE;
		ret = ma_deinitialize();
		assert_eq(ret, MA_ERROR_NONE);

		ret = ma_remove_wake_word("Hi Tizen", "en_US");
		assert_eq(ret, MA_ERROR_INVALID_STATE);
	}

	return 0;
}
