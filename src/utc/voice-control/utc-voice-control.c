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
#include <voice_control.h>
#include <voice_control_command.h>
#include <voice_control_common.h>
#include <Ecore.h>

static int g_vc_init = false;
static vc_state_e g_vc_state = VC_STATE_NONE;
static bool g_vc_supported = false;

static void __vc_result_cb(vc_result_event_e event, vc_cmd_list_h vc_cmd_list, const char* result, void* user_data)
{
}

static void __vc_current_language_changed_cb(const char* previous, const char* current, void* user_data)
{
}

static bool __vc_supported_language_cb(const char* language, void* user_data)
{
	return true;
}

static void __vc_state_changed_cb(vc_state_e previous, vc_state_e current, void* user_data)
{
	g_vc_state = current;
}

static void __vc_service_state_changed_cb(vc_service_state_e previous, vc_service_state_e current, void* user_data)
{
}

static void __vc_error_cb(vc_error_e reason, void* user_data)
{
}

static bool __vc_cmd_list_cb(vc_cmd_h vc_command, void* user_data)
{
	return true;
}

/**
 * @function		utc_voice_control_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_voice_control_startup(void)
{
	g_vc_supported = false;
	bool mic_supported = false;
	bool vc_supported = false;
	if (0 == system_info_get_platform_bool("http://tizen.org/feature/speech.control", &vc_supported)) {
		if (0 == system_info_get_platform_bool("http://tizen.org/feature/microphone", &mic_supported)) {
			if (true == vc_supported && true == mic_supported) {
				g_vc_supported = true;
			}
		}
	}

	g_vc_init = false;
	if (true == g_vc_supported) {
		int ret = VC_ERROR_NONE;
		ret = vc_initialize();
		if (VC_ERROR_NONE == ret) {
			ret = vc_set_state_changed_cb(__vc_state_changed_cb, NULL);
			if (VC_ERROR_NONE != ret) {
				g_vc_init = false;
			} else {
				g_vc_init = true;
			}
		} else {
			g_vc_init = false;
		}
	}
}

/**
 * @function		utc_voice_control_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_voice_control_cleanup(void)
{
	int ret = VC_ERROR_NONE;

	if (true == g_vc_supported) {
		ret = vc_unset_state_changed_cb();
		assert_eq(ret, VC_ERROR_NONE);
		ret = vc_deinitialize();
		assert_eq(ret, VC_ERROR_NONE);
	}

	g_vc_init = false;
}


/**
 * @testcase		utc_vc_initialize_p
 * @since_tizen		2.4
 * @description		Positive UTC for initialize voice control handle
 */
int utc_vc_initialize_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);
	} else {
		assert_eq(g_vc_init, true);
	}

	return 0;
}

/**
 * @testcase		utc_vc_deinitialize_p
 * @since_tizen		2.4
 * @description		Positive UTC for deinitialize voice control handle
 */
int utc_vc_deinitialize_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_deinitialize();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_deinitialize();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_deinitialize_n
 * @since_tizen		2.4
 * @description		Negative UTC for deinitialize voice control handle (Already deinitialized)
 */
int utc_vc_deinitialize_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_deinitialize();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_deinitialize();
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_deinitialize();
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_prepare_p
 * @since_tizen		2.4
 * @description		Positive UTC for connect service daemon
 */
int utc_vc_prepare_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_prepare_n
 * @since_tizen		2.4
 * @description		Negative UTC for connect service daemon (Invalid state)
 */
int utc_vc_prepare_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		vc_deinitialize();

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unprepare_p
 * @since_tizen		2.4
 * @description		Positive UTC for disconnect service daemon
 */
int utc_vc_unprepare_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unprepare_n
 * @since_tizen		2.4
 * @description		Negative UTC for disconnect service daemon (Invalid state)
 */
int utc_vc_unprepare_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unprepare_n2
 * @since_tizen		2.4
 * @description		Negative UTC for disconnect service daemon (Invalid state)
 */
int utc_vc_unprepare_n2(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_deinitialize();
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_foreach_supported_languages_p
 * @since_tizen		2.4
 * @description		Positive UTC for get supported language list
 */
int utc_vc_foreach_supported_languages_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_foreach_supported_languages(__vc_supported_language_cb, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_foreach_supported_languages(__vc_supported_language_cb, NULL);
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_foreach_supported_languages_n
 * @since_tizen		2.4
 * @description		Negative UTC for get supported language list (Invalid parameter)
 */
int utc_vc_foreach_supported_languages_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_foreach_supported_languages(NULL, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_foreach_supported_languages(NULL, NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_foreach_supported_languages_n2
 * @since_tizen		2.4
 * @description		Negative UTC for get supported language list (Invalid state)
 */
int utc_vc_foreach_supported_languages_n2(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_foreach_supported_languages(__vc_supported_language_cb, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_deinitialize();
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_foreach_supported_languages(__vc_supported_language_cb, NULL);
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_get_current_language_p
 * @since_tizen		2.4
 * @description		Positive UTC for get current language
 */
int utc_vc_get_current_language_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		char *lang = NULL;
		ret = vc_get_current_language(&lang);
		if (NULL != lang) {
				free(lang);
				lang = NULL;
		}
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		char *lang = NULL;
		ret = vc_get_current_language(&lang);
		if (NULL != lang) {
				free(lang);
				lang = NULL;
		}
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_get_current_language_n
 * @since_tizen		2.4
 * @description		Negative UTC for get current language (Invalid parameter)
 */
int utc_vc_get_current_language_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_get_current_language(NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_get_current_language(NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_get_current_language_n2
 * @since_tizen		2.4
 * @description		Negative UTC for get current language (Invalid state)
 */
int utc_vc_get_current_language_n2(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		char *lang = NULL;
		ret = vc_get_current_language(&lang);
		if (NULL != lang) {
				free(lang);
				lang = NULL;
		}
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		char *lang = NULL;
		ret = vc_deinitialize();
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_get_current_language(&lang);
		if (NULL != lang) {
				free(lang);
				lang = NULL;
		}
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_get_state_p
 * @since_tizen		2.4
 * @description		Positive UTC for get current state
 */
int utc_vc_get_state_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_state_e state = -1;
		ret = vc_get_state(&state);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_state_e state = -1;
		ret = vc_get_state(&state);
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_get_state_p2
 * @since_tizen		2.4
 * @description		Positive UTC for get current state after connection
 */
int utc_vc_get_state_p2(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_state_e state = -1;
		ret = vc_get_state(&state);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		vc_state_e state = -1;
		ret = vc_get_state(&state);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_get_state_n
 * @since_tizen		2.4
 * @description		Negative UTC for get current state (Invalid parameter)
 */
int utc_vc_get_state_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_get_state(NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_get_state(NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_get_state_n2
 * @since_tizen		2.4
 * @description		Negative UTC for get current state (Invalid state)
 */
int utc_vc_get_state_n2(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_state_e state = -1;
		ret = vc_get_state(&state);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_deinitialize();
		assert_eq(ret, VC_ERROR_NONE);

		vc_state_e state = -1;
		ret = vc_get_state(&state);
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_get_service_state_p
 * @since_tizen		2.4
 * @description		Positive UTC for get current state of service daemon
 */
int utc_vc_get_service_state_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_service_state_e state = -1;
		ret = vc_get_service_state(&state);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		vc_service_state_e state = -1;
		ret = vc_get_service_state(&state);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_get_service_state_n
 * @since_tizen		2.4
 * @description		Negative UTC for get current state of service daemon (Invalid parameter)
 */
int utc_vc_get_service_state_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_get_service_state(NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_get_service_state(NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_get_service_state_n2
 * @since_tizen		2.4
 * @description		Negative UTC for get current state of service daemon (Invalid state)
 */
int utc_vc_get_service_state_n2(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_service_state_e state = -1;
		ret = vc_get_service_state(&state);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_deinitialize();
		assert_eq(ret, VC_ERROR_NONE);

		vc_service_state_e state = -1;
		ret = vc_get_service_state(&state);
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_get_system_command_list_p
 * @since_tizen		3.0
 * @description		Positive UTC for get the system command list
 */
int utc_vc_get_system_command_list_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_get_system_command_list(&list);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		vc_cmd_list_h list = NULL;
		ret = vc_get_system_command_list(&list);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_get_system_command_list_n
 * @since_tizen		3.0
 * @description		Negative UTC for get the system command list (Invalid parameter)
 */
int utc_vc_get_system_command_list_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_get_system_command_list(NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_get_system_command_list(NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_get_system_command_list_n2
 * @since_tizen		3.0
 * @description		Negative UTC for get the system command list (Invalid state)
 */
int utc_vc_get_system_command_list_n2(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_get_system_command_list(&list);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_deinitialize();
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_list_h list = NULL;
		ret = vc_get_system_command_list(&list);
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_command_list_p
 * @since_tizen		2.4
 * @description		Positive UTC for set command list used as candidate set
 */
int utc_vc_set_command_list_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_set_command_list(list, VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_create(&list);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_h cmd = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_set_command(cmd, "voice");
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_set_type(cmd, VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_list_add(list, cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_set_command_list(list, VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_list_destroy(list, true);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_command_list_n
 * @since_tizen		2.4
 * @description		Negative UTC for set command list used as candidate set (Invalid parameter)
 */
int utc_vc_set_command_list_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_command_list(NULL, VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_set_command_list(NULL, VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_command_list_n2
 * @since_tizen		2.4
 * @description		Negative UTC for set command list used as candidate set (Invalid state)
 */
int utc_vc_set_command_list_n2(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_set_command_list(list, VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_deinitialize();
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_create(&list);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_set_command_list(list, VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_INVALID_STATE);

		ret = vc_cmd_list_destroy(list, true);
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_command_list_n3
 * @since_tizen		2.4
 * @description		Negative UTC for set command list used as candidate set (Invalid state)
 */
int utc_vc_set_command_list_n3(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_set_command_list(list, VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_create(&list);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_set_command_list(list, VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_INVALID_STATE);

		ret = vc_cmd_list_destroy(list, true);
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unset_command_list_p
 * @since_tizen		2.4
 * @description		Positive UTC for unset command list used as candidate set
 */
int utc_vc_unset_command_list_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unset_command_list(VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_create(&list);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_h cmd = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_set_command(cmd, "voice");
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_set_type(cmd, VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_list_add(list, cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_set_command_list(list, VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_unset_command_list(VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_list_destroy(list, true);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unset_command_list_n
 * @since_tizen		2.4
 * @description		Negative UTC for unset command list used as candidate set (Invalid state)
 */
int utc_vc_unset_command_list_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unset_command_list(VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_unset_command_list(VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unset_command_list_n2
 * @since_tizen		2.4
 * @description		Negative UTC for unset command list used as candidate set (Invalid state)
 */
int utc_vc_unset_command_list_n2(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unset_command_list(VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_deinitialize();
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_unset_command_list(VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_get_result_p
 * @since_tizen		3.0
 * @description		Positive UTC for getting the recognition result
 */
int utc_vc_get_result_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_get_result(__vc_result_cb, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		ret = vc_get_result(__vc_result_cb, NULL);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_get_result_n
 * @since_tizen		3.0
 * @description		Negative UTC for getting the recognition result (Invalid parameter)
 */
int utc_vc_get_result_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_get_result(NULL, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		ret = vc_get_result(NULL, NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_result_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC for set result callback
 */
int utc_vc_set_result_cb_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_result_cb(__vc_result_cb, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_set_result_cb(__vc_result_cb, NULL);
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_result_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC for set result callback (Invalid parameter)
 */
int utc_vc_set_result_cb_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_result_cb(NULL, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_set_result_cb(NULL, NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_result_cb_n2
 * @since_tizen		2.4
 * @description		Negative UTC for set result callback (Invalid state)
 */
int utc_vc_set_result_cb_n2(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_result_cb(__vc_result_cb, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_deinitialize();
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_set_result_cb(__vc_result_cb, NULL);
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_result_cb_n3
 * @since_tizen		2.4
 * @description		Negative UTC for set result callback (Invalid state)
 */
int utc_vc_set_result_cb_n3(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_result_cb(__vc_result_cb, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		ret = vc_set_result_cb(__vc_result_cb, NULL);
		assert_eq(ret, VC_ERROR_INVALID_STATE);

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unset_result_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC for unset result callback
 */
int utc_vc_unset_result_cb_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unset_result_cb();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_set_result_cb(__vc_result_cb, NULL);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_unset_result_cb();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unset_result_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC for unset result callback (Invalid state)
 */
int utc_vc_unset_result_cb_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unset_result_cb();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_deinitialize();
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_unset_result_cb();
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unset_result_cb_n2
 * @since_tizen		2.4
 * @description		Negative UTC for unset result callback (Invalid state)
 */
int utc_vc_unset_result_cb_n2(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unset_result_cb();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		ret = vc_unset_result_cb();
		assert_eq(ret, VC_ERROR_INVALID_STATE);

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_service_state_changed_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC for set service state changed callback
 */
int utc_vc_set_service_state_changed_cb_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_service_state_changed_cb(__vc_service_state_changed_cb, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_set_service_state_changed_cb(__vc_service_state_changed_cb, NULL);
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_service_state_changed_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC for set service state changed callback (Invalid parameter)
 */
int utc_vc_set_service_state_changed_cb_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_service_state_changed_cb(NULL, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_set_service_state_changed_cb(NULL, NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_service_state_changed_cb_n2
 * @since_tizen		2.4
 * @description		Negative UTC for set service state changed callback (Invalid state)
 */
int utc_vc_set_service_state_changed_cb_n2(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_service_state_changed_cb(__vc_service_state_changed_cb, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_deinitialize();
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_set_service_state_changed_cb(__vc_service_state_changed_cb, NULL);
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_service_state_changed_cb_n3
 * @since_tizen		2.4
 * @description		Nagative UTC for set service state changed callback (Invalid state)
 */
int utc_vc_set_service_state_changed_cb_n3(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_service_state_changed_cb(__vc_service_state_changed_cb, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		ret = vc_set_service_state_changed_cb(__vc_service_state_changed_cb, NULL);
		assert_eq(ret, VC_ERROR_INVALID_STATE);

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unset_service_state_changed_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC for unset service state changed callback
 */
int utc_vc_unset_service_state_changed_cb_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unset_service_state_changed_cb();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_set_service_state_changed_cb(__vc_service_state_changed_cb, NULL);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_unset_service_state_changed_cb();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unset_service_state_changed_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC for unset service state changed callback (Invalid state)
 */
int utc_vc_unset_service_state_changed_cb_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unset_service_state_changed_cb();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		vc_deinitialize();

		int ret = VC_ERROR_NONE;
		ret = vc_unset_service_state_changed_cb();
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unset_service_state_changed_cb_n2
 * @since_tizen		2.4
 * @description		Negative UTC for unset service state changed callback (Invalid state)
 */
int utc_vc_unset_service_state_changed_cb_n2(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unset_service_state_changed_cb();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		ret = vc_unset_service_state_changed_cb();
		assert_eq(ret, VC_ERROR_INVALID_STATE);

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_state_changed_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC for set state changed callback
 */
int utc_vc_set_state_changed_cb_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);
		int ret = VC_ERROR_NONE;
		ret = vc_set_state_changed_cb(__vc_state_changed_cb, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_state_changed_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC for set state changed callback (Invalid parameter)
 */
int utc_vc_set_state_changed_cb_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_state_changed_cb(NULL, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_set_state_changed_cb(NULL, NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_state_changed_cb_n2
 * @since_tizen		2.4
 * @description		Nagative UTC for set state changed callback (Invalid state)
 */
int utc_vc_set_state_changed_cb_n2(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_state_changed_cb(__vc_state_changed_cb, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_deinitialize();
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_set_state_changed_cb(__vc_state_changed_cb, NULL);
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_state_changed_cb_n3
 * @since_tizen		2.4
 * @description		Negative UTC for set state changed callback (Invalid state)
 */
int utc_vc_set_state_changed_cb_n3(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_state_changed_cb(__vc_state_changed_cb, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		ret = vc_set_state_changed_cb(__vc_state_changed_cb, NULL);
		assert_eq(ret, VC_ERROR_INVALID_STATE);

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unset_state_changed_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC for unset state changed callback
 */
int utc_vc_unset_state_changed_cb_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unset_state_changed_cb();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_unset_state_changed_cb();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unset_state_changed_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC for unset state changed callback (Invalid state)
 */
int utc_vc_unset_state_changed_cb_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unset_state_changed_cb();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		vc_deinitialize();

		int ret = VC_ERROR_NONE;
		ret = vc_unset_state_changed_cb();
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_current_language_changed_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC for set current language changed callback
 */
int utc_vc_set_current_language_changed_cb_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_current_language_changed_cb(__vc_current_language_changed_cb, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_set_current_language_changed_cb(__vc_current_language_changed_cb, NULL);
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_current_language_changed_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC for set current language changed callback (invalid parameter)
 */
int utc_vc_set_current_language_changed_cb_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_current_language_changed_cb(NULL, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_set_current_language_changed_cb(NULL, NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_current_language_changed_cb_n2
 * @since_tizen		2.4
 * @description		Negative UTC for set current language changed callback (Invalid state)
 */
int utc_vc_set_current_language_changed_cb_n2(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_current_language_changed_cb(__vc_current_language_changed_cb, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		ret = vc_set_current_language_changed_cb(__vc_current_language_changed_cb, NULL);
		assert_eq(ret, VC_ERROR_INVALID_STATE);

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_current_language_changed_cb_n3
 * @since_tizen		2.4
 * @description		Negative UTC for set current language changed callback (Invalid state)
 */
int utc_vc_set_current_language_changed_cb_n3(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_current_language_changed_cb(__vc_current_language_changed_cb, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_deinitialize();
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_set_current_language_changed_cb(__vc_current_language_changed_cb, NULL);
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unset_current_language_changed_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC for unset current language changed callback
 */
int utc_vc_unset_current_language_changed_cb_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unset_current_language_changed_cb();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_set_current_language_changed_cb(__vc_current_language_changed_cb, NULL);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_unset_current_language_changed_cb();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unset_current_language_changed_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC for unset current language changed callback (Invalid state)
 */
int utc_vc_unset_current_language_changed_cb_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unset_current_language_changed_cb();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		vc_deinitialize();

		int ret = VC_ERROR_NONE;
		ret = vc_unset_current_language_changed_cb();
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unset_current_language_changed_cb_n2
 * @since_tizen		2.4
 * @description		Negative UTC for unset current language changed callback (Invalid state)
 */
int utc_vc_unset_current_language_changed_cb_n2(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unset_current_language_changed_cb();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		ret = vc_unset_current_language_changed_cb();
		assert_eq(ret, VC_ERROR_INVALID_STATE);

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_error_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC for set error callback
 */
int utc_vc_set_error_cb_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_error_cb(__vc_error_cb, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_set_error_cb(__vc_error_cb, NULL);
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_error_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC for set error callback (Invalid parameter)
 */
int utc_vc_set_error_cb_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_error_cb(NULL, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_set_error_cb(NULL, NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_error_cb_n2
 * @since_tizen		2.4
 * @description		Negative UTC for set error callback (Invalid state)
 */
int utc_vc_set_error_cb_n2(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_error_cb(__vc_error_cb, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_deinitialize();
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_set_error_cb(__vc_error_cb, NULL);
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_error_cb_n3
 * @since_tizen		2.4
 * @description		Negative UTC for set error callback (Invalid state)
 */
int utc_vc_set_error_cb_n3(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_set_error_cb(__vc_error_cb, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		ret = vc_set_error_cb(__vc_error_cb, NULL);
		assert_eq(ret, VC_ERROR_INVALID_STATE);

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unset_error_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC for unset error callback
 */
int utc_vc_unset_error_cb_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unset_error_cb();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_set_error_cb(__vc_error_cb, NULL);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_unset_error_cb();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unset_error_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC for unset error callback (Invalid state)
 */
int utc_vc_unset_error_cb_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unset_error_cb();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		vc_deinitialize();

		int ret = VC_ERROR_NONE;
		ret = vc_unset_error_cb();
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_unset_error_cb_n2
 * @since_tizen		2.4
 * @description		Negatice UTC for unset error callback (Invalid state)
 */
int utc_vc_unset_error_cb_n2(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_unset_error_cb();
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		ret = vc_unset_error_cb();
		assert_eq(ret, VC_ERROR_INVALID_STATE);

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_invocation_name_p
 * @since_tizen		3.0
 * @description		Positive UTC for setting the invocation name
 */
int utc_vc_set_invocation_name_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		const char* invoc_name = "testapp";
		ret = vc_set_invocation_name(invoc_name);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		const char* invoc_name = "testapp";

		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		ret = vc_set_invocation_name(invoc_name);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_set_invocation_name_n
 * @since_tizen		3.0
 * @description		Negative UTC for setting the invocation name (Invalid state)
 */
int utc_vc_set_invocation_name_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		const char* invoc_name = "testapp";
		ret = vc_set_invocation_name(invoc_name);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		const char* invoc_name = "testapp";

		ret = vc_set_invocation_name(invoc_name);
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_request_dialog_p
 * @since_tizen		3.0
 * @description		Positive UTC for requesting the dialog
 */
int utc_vc_request_dialog_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		const char* disp_txt = "test";
		const char* utt_txt = "test";
		bool is_auto_start = true;
		ret = vc_request_dialog(disp_txt, utt_txt, is_auto_start);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		const char* disp_txt = "test";
		const char* utt_txt = "test";
		bool is_auto_start = true;

		ret = vc_prepare();
		assert_eq(ret, VC_ERROR_NONE);

		while (VC_STATE_READY != g_vc_state) {
			ecore_main_loop_iterate();
		}

		ret = vc_request_dialog(disp_txt, utt_txt, is_auto_start);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_unprepare();
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_request_dialog_n
 * @since_tizen		3.0
 * @description		Negative UTC for requesting the dialog (Invalid state)
 */
int utc_vc_request_dialog_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		const char* disp_txt = "voice control test";
		const char* utt_txt = "This is a test for requesting the dialog";
		bool is_auto_start = true;
		ret = vc_request_dialog(disp_txt, utt_txt, is_auto_start);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		vc_deinitialize();

		int ret = VC_ERROR_NONE;
		const char* disp_txt = "voice control test";
		const char* utt_txt = "This is a test for requesting the dialog";
		bool is_auto_start = true;
		ret = vc_request_dialog(disp_txt, utt_txt, is_auto_start);
		assert_eq(ret, VC_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_create_p
 * @since_tizen		2.4
 * @description		Positive UTC for create command list handle
 */
int utc_vc_cmd_list_create_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_create(&list);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_create(&list);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_list_destroy(list, false);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_create_n
 * @since_tizen		2.4
 * @description		Negative UTC for create command list handle (Invalid parameter)
 */
int utc_vc_cmd_list_create_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_create(NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_create(NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_destroy_p
 * @since_tizen		2.4
 * @description		Positive UTC for destroy command list handle
 */
int utc_vc_cmd_list_destroy_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_destroy(list, false);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_create(&list);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_list_destroy(list, false);
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_destroy_n
 * @since_tizen		2.4
 * @description		Negative UTC for destroy command list handle (Invalid parameter)
 */
int utc_vc_cmd_list_destroy_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_destroy(NULL, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_destroy(NULL, NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_get_count_p
 * @since_tizen		2.4
 * @description		Positive UTC for get count of command in command list
 */
int utc_vc_cmd_list_get_count_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		int cnt = -1;
		ret = vc_cmd_list_get_count(list, &cnt);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_create(&list);
		assert_eq(ret, VC_ERROR_NONE);

		int cnt = -1;
		ret = vc_cmd_list_get_count(list, &cnt);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_list_destroy(list, false);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_get_count_n
 * @since_tizen		2.4
 * @description		Negative UTC for get count of command in command list (Invalid parameter)
 */
int utc_vc_cmd_list_get_count_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_get_count(NULL, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_get_count(NULL, NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_add_p
 * @since_tizen		2.4
 * @description		Positive UTC for add command in command list
 */
int utc_vc_cmd_list_add_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		vc_cmd_h cmd = NULL;
		ret = vc_cmd_list_add(list, cmd);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_create(&list);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_h cmd = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_list_add(list, cmd);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_list_destroy(list, true);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_add_n
 * @since_tizen		2.4
 * @description		Negative UTC for add command in command list (Invalid parameter)
 */
int utc_vc_cmd_list_add_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_add(NULL, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_add(NULL, NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_remove_p
 * @since_tizen		2.4
 * @description		Positive UTC for remove command in command list
 */
int utc_vc_cmd_list_remove_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		vc_cmd_h cmd = NULL;
		ret = vc_cmd_list_remove(list, cmd);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_create(&list);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_h cmd = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_list_add(list, cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_list_remove(list, cmd);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_list_destroy(list, true);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_remove_n
 * @since_tizen		2.4
 * @description		Negative UTC for remove command in command list (Invalid parameter)
 */
int utc_vc_cmd_list_remove_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_remove(NULL, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_remove(NULL, NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_foreach_commands_p
 * @since_tizen		2.4
 * @description		Positive UTC for get whole command in command list
 */
int utc_vc_cmd_list_foreach_commands_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_foreach_commands(list, __vc_cmd_list_cb, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_create(&list);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_h cmd = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_list_add(list, cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_list_foreach_commands(list, __vc_cmd_list_cb, NULL);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_list_destroy(list, true);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_foreach_commands_n
 * @since_tizen		2.4
 * @description		Negative UTC for get whole command in command list (Invalid parameter)
 */
int utc_vc_cmd_list_foreach_commands_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_foreach_commands(NULL, NULL, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_foreach_commands(NULL, NULL, NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_first_p
 * @since_tizen		2.4
 * @description		Positive UTC for move pointer to the first of command list
 */
int utc_vc_cmd_list_first_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_first(list);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_create(&list);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_h cmd = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_list_add(list, cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_list_first(list);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_list_destroy(list, true);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_first_n
 * @since_tizen		2.4
 * @description		Negative UTC for move pointer to the first of command list (Invalid parameter)
 */
int utc_vc_cmd_list_first_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_first(NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_first(NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_last_p
 * @since_tizen		2.4
 * @description		Positive UTC for move pointer to the last of command list
 */
int utc_vc_cmd_list_last_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_last(list);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_create(&list);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_h cmd = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_list_add(list, cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_list_last(list);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_list_destroy(list, true);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_last_n
 * @since_tizen		2.4
 * @description		Negative UTC for move pointer to the last of command list (Invalid parameter)
 */
int utc_vc_cmd_list_last_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_last(NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_last(NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_next_p
 * @since_tizen		2.4
 * @description		Positive UTC for move pointer to next command in command list
 */
int utc_vc_cmd_list_next_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_next(list);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_create(&list);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_h cmd = NULL;
		int i;
		for (i = 0; i < 2; i++) {
			ret = vc_cmd_create(&cmd);
			assert_eq(ret, VC_ERROR_NONE);

			ret = vc_cmd_list_add(list, cmd);
			assert_eq(ret, VC_ERROR_NONE);
		}

		ret = vc_cmd_list_first(list);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_list_next(list);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_list_destroy(list, true);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_next_n
 * @since_tizen		2.4
 * @description		Negative UTC for move pointer to next command in command list (Invalid parameter)
 */
int utc_vc_cmd_list_next_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_next(NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_next(NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_prev_p
 * @since_tizen		2.4
 * @description		Positive UTC for move pointer to previous command in command list
 */
int utc_vc_cmd_list_prev_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_prev(list);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_create(&list);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_h cmd = NULL;
		int i;
		for (i = 0; i < 2; i++) {
			ret = vc_cmd_create(&cmd);
			assert_eq(ret, VC_ERROR_NONE);

			ret = vc_cmd_list_add(list, cmd);
			assert_eq(ret, VC_ERROR_NONE);
		}

		ret = vc_cmd_list_last(list);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_list_prev(list);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_list_destroy(list, true);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_prev_n
 * @since_tizen		2.4
 * @description		Negative UTC for move pointer to previous command in command list (Invalid parameter)
 */
int utc_vc_cmd_list_prev_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_prev(NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_prev(NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_get_current_p
 * @since_tizen		2.4
 * @description		Positive UTC for get command handle of current pointer
 */
int utc_vc_cmd_list_get_current_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		vc_cmd_h cur = NULL;
		ret = vc_cmd_list_get_current(list, &cur);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_list_h list = NULL;
		ret = vc_cmd_list_create(&list);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_h cmd = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_list_add(list, cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_list_first(list);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_h cur = NULL;
		ret = vc_cmd_list_get_current(list, &cur);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_list_destroy(list, true);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_list_get_current_n
 * @since_tizen		2.4
 * @description		Negative UTC for get command handle of current pointer (Invalid parameter)
 */
int utc_vc_cmd_list_get_current_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_get_current(NULL, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_list_get_current(NULL, NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_create_p
 * @since_tizen		2.4
 * @description		Positive UTC for create command handle
 */
int utc_vc_cmd_create_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_h cmd = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_h cmd = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_destroy(cmd);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_create_n
 * @since_tizen		2.4
 * @description		Negative UTC for create command handle
 */
int utc_vc_cmd_create_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_create(NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_create(NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_destroy_p
 * @since_tizen		2.4
 * @description		Positive UTC for destroy command handle
 */
int utc_vc_cmd_destroy_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_h cmd = NULL;
		ret = vc_cmd_destroy(cmd);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_h cmd = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_destroy(cmd);
		assert_eq(ret, VC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_destroy_n
 * @since_tizen		2.4
 * @description		Negative UTC for destroy command handle (Invalid parameter)
 */
int utc_vc_cmd_destroy_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_destroy(NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_destroy(NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_set_command_p
 * @since_tizen		2.4
 * @description		Positive UTC for set command text in handle
 */
int utc_vc_cmd_set_command_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_h cmd = NULL;
		ret = vc_cmd_set_command(cmd, "voice");
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_h cmd = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_set_command(cmd, "voice");
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_destroy(cmd);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_set_command_n
 * @since_tizen		2.4
 * @description		Negative UTC for set command text in handle (Invalid parameter)
 */
int utc_vc_cmd_set_command_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_set_command(NULL, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_set_command(NULL, NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_get_command_p
 * @since_tizen		2.4
 * @description		Positive UTC for get command text in handle
 */
int utc_vc_cmd_get_command_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_h cmd = NULL;
		char *text = NULL;
		ret = vc_cmd_get_command(cmd, &text);
		if (NULL != text) {
				free(text);
				text = NULL;
		}
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_h cmd = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_set_command(cmd, "voice");
		assert_eq(ret, VC_ERROR_NONE);

		char *text = NULL;
		ret = vc_cmd_get_command(cmd, &text);
		if (NULL != text) {
				free(text);
				text = NULL;
		}
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_destroy(cmd);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_get_command_n
 * @since_tizen		2.4
 * @description		Negative UTC for get command text in handle (Invalid parameter)
 */
int utc_vc_cmd_get_command_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_get_command(NULL, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_get_command(NULL, NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_get_unfixed_command_p
 * @since_tizen		3.0
 * @description		Positive UTC for getting the unfixed command text in handle
 */
int utc_vc_cmd_get_unfixed_command_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_h cmd = NULL;
		char *text = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);

		ret = vc_cmd_get_unfixed_command(cmd, &text);
		if (NULL != text) {
			free(text);
			text = NULL;
		}
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_h cmd = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NONE);

		char *text = NULL;
		ret = vc_cmd_get_unfixed_command(cmd, &text);
		if (NULL != text) {
			free(text);
			text = NULL;
		}
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_destroy(cmd);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_get_unfixed_command_n
 * @since_tizen		3.0
 * @description		Negative UTC for getting the unfixed command text in handle (Invalid parameter)
 */
int utc_vc_cmd_get_unfixed_command_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_get_unfixed_command(NULL, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_get_unfixed_command(NULL, NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_set_type_p
 * @since_tizen		2.4
 * @description		Positive UTC for set command type in handle
 */
int utc_vc_cmd_set_type_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_h cmd = NULL;
		ret = vc_cmd_set_type(cmd, VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_h cmd = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_set_type(cmd, VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_destroy(cmd);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_set_type_n
 * @since_tizen		2.4
 * @description		Negative UTC for set command type in handle (Invalid parameter)
 */
int utc_vc_cmd_set_type_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_set_type(NULL, VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_set_type(NULL, VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_get_type_p
 * @since_tizen		2.4
 * @description		Positive UTC for get command type in handle
 */
int utc_vc_cmd_get_type_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_h cmd = NULL;
		int type;
		ret = vc_cmd_get_type(cmd, &type);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_h cmd = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_set_type(cmd, VC_COMMAND_TYPE_BACKGROUND);
		assert_eq(ret, VC_ERROR_NONE);

		int type;
		ret = vc_cmd_get_type(cmd, &type);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_destroy(cmd);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_get_type_n
 * @since_tizen		2.4
 * @description		Negative UTC for get command type in handle (invalid parameter)
 */
int utc_vc_cmd_get_type_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_get_type(NULL, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_get_type(NULL, NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_set_format_p
 * @since_tizen		3.0
 * @description		Positive UTC for setting command format in handle
 */
int utc_vc_cmd_set_format_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_h cmd = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);

		ret = vc_cmd_set_format(cmd, VC_COMMAND_FORMAT_FIXED);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);

		vc_cmd_destroy(cmd);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_h cmd = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_set_format(cmd, VC_COMMAND_FORMAT_FIXED);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_destroy(cmd);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_set_format_n
 * @since_tizen		3.0
 * @description		Negative UTC for setting command format in handle (Invalid parameter)
 */
int utc_vc_cmd_set_format_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_set_format(NULL, VC_COMMAND_FORMAT_FIXED);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_set_format(NULL, VC_COMMAND_FORMAT_FIXED);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_get_format_p
 * @since_tizen		3.0
 * @description		Positive UTC for getting command format in handle
 */
int utc_vc_cmd_get_format_p(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		vc_cmd_h cmd = NULL;
		int format;
		ret = vc_cmd_get_format(cmd, &format);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		vc_cmd_h cmd = NULL;
		ret = vc_cmd_create(&cmd);
		assert_eq(ret, VC_ERROR_NONE);

		ret = vc_cmd_set_format(cmd, VC_COMMAND_FORMAT_FIXED);
		assert_eq(ret, VC_ERROR_NONE);

		int format;
		ret = vc_cmd_get_format(cmd, &format);
		assert_eq(ret, VC_ERROR_NONE);

		vc_cmd_destroy(cmd);
	}

	return 0;
}

/**
 * @testcase		utc_vc_cmd_get_format_n
 * @since_tizen		3.0
 * @description		Negative UTC for getting command format in handle(invalid parameter)
 */
int utc_vc_cmd_get_format_n(void)
{
	if (false == g_vc_supported) {
		assert_eq(g_vc_init, false);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_get_format(NULL, NULL);
		assert_eq(ret, VC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_init, true);

		int ret = VC_ERROR_NONE;
		ret = vc_cmd_get_format(NULL, NULL);
		assert_eq(ret, VC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

