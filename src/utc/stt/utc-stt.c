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
#include <stt.h>
#include <stdlib.h>
#include <system_info.h>
#include <fcntl.h>
#include <unistd.h>
#include <dlog.h>
#include <Ecore.h>

#include "assert.h"

//& set: Stt

stt_h g_stt = NULL;
static char *g_engine_id = NULL;
static char *g_language = NULL;
static stt_state_e g_current_state;
static stt_state_e g_temp_current_state;
static bool g_stt_supported = false;
static stt_error_e g_error;

static void __stt_state_changed_cb(stt_h stt, stt_state_e previous, stt_state_e current, void* user_data);
static void __stt_error_cb(stt_h stt, stt_error_e reason, void *user_data);

void utc_stt_startup(void)
{
	/* start of TC */
	int ret = -1;
	g_stt_supported = false;
	system_info_get_platform_bool("http://tizen.org/feature/speech.recognition", &g_stt_supported);
	g_current_state = 0;
	g_error = TIZEN_ERROR_NONE;

	if (g_stt_supported) {
		g_stt = NULL;
		ret = stt_create(&g_stt);
		assert_eq(ret, STT_ERROR_NONE);
		ret = stt_set_state_changed_cb(g_stt, __stt_state_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);
		ret = stt_set_error_cb(g_stt, __stt_error_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);
	}
}

void utc_stt_cleanup(void)
{
	/* end of TC */
	int ret = -1;
	if (true == g_stt_supported) {
		ret = stt_unset_state_changed_cb(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
		ret = stt_unset_error_cb(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
		ret = stt_destroy(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}
	g_stt = NULL;

}

static bool __stt_supported_engine_cb(stt_h stt, const char* engine_id, const char* engine_name, void* user_data)
{
	return true;
}

static bool __stt_supported_language_cb(stt_h stt, const char* lang, void* user_data)
{
	return true;
}

static void __stt_state_changed_cb(stt_h stt, stt_state_e previous, stt_state_e current, void* user_data)
{
	g_current_state = current;
}

static void __stt_temp_state_changed_cb(stt_h stt, stt_state_e previous, stt_state_e current, void* user_data)
{
	g_temp_current_state = current;
}

static void __stt_error_cb(stt_h stt, stt_error_e reason, void *user_data)
{
	g_error = reason;
	dlog_print(DLOG_ERROR, "NativeTCT", "ERROR(%d)", g_error);

	return;
}

static void __stt_recognition_result_cb(stt_h stt, stt_result_event_e event, const char** data, int data_count, const char* msg, void *user_data)
{
}

static bool __stt_result_time_cb(stt_h stt, int index, stt_result_time_event_e event, const char* text, long start_time, long end_time, void *user_data)
{
	return true;
}

static void __stt_default_language_changed_cb(stt_h stt, const char* previous, const char* current, void *user_data)
{
}

static void __stt_engine_changed_cb(stt_h stt, const char* engine_id, const char* language, bool support_silence, bool need_credential, void *user_data)
{
}

static void __stt_speech_status_cb(stt_h stt, stt_speech_status_e status, void *user_data)
{
}

/**
 * @testcase		utc_stt_create_p
 * @since_tizen		2.3
 * @description		Positive UTC for stt handle create
 */
int utc_stt_create_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		assert_eq(g_stt, NULL);
	} else {
		assert_neq(g_stt, NULL);

		stt_h stt = NULL;
		ret = stt_create(&stt);
		assert_eq(ret, STT_ERROR_NONE);
		assert_neq(stt, NULL);

		ret = stt_destroy(stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_create_n
 * @since_tizen		2.3
 * @description		Negative UTC for stt handle create
 */
int utc_stt_create_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_create(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_create(NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_destroy_p
 * @since_tizen		2.3
 * @description		Positive UTC for stt handle destroy
 */
int utc_stt_destroy_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_destroy(g_stt);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_destroy(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_create(&g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_destroy_p1
 * @since_tizen		2.3
 * @description		Positive UTC for stt handle destroy at READY state
 */
int utc_stt_destroy_p1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_destroy(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		stt_h stt = NULL;
		ret = stt_create(&stt);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_set_state_changed_cb(stt, __stt_temp_state_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_get_state(stt, &g_temp_current_state);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_prepare(stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_temp_current_state){
			ecore_main_loop_iterate();
		}

		/* Destroy stt on ready state */
		ret = stt_destroy(stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_destroy_p2
 * @since_tizen		2.3
 * @description		Positive UTC for stt handle destroy before connection
 */
int utc_stt_destroy_p2(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_destroy(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		/* Check to remove timer */
		stt_h stt = NULL;
		ret = stt_create(&stt);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_prepare(stt);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_destroy(stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_destroy_n
 * @since_tizen		2.3
 * @description		Negative UTC for stt handle destroy
 */
int utc_stt_destroy_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_destroy(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_destroy(NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_destroy_n1
 * @since_tizen		2.3
 * @description		Negative UTC for destroy stt handle which is not created
 */
int utc_stt_destroy_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_destroy(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		stt_h stt = NULL;
		ret = stt_destroy(stt);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

static int g_n2_state_changed_ret = STT_ERROR_NONE;
static void __stt_n2_state_changed_cb(stt_h stt, stt_state_e previous, stt_state_e current, void* user_data)
{
	g_temp_current_state = current;

	/* Fail to destroy in callback function */
	g_n2_state_changed_ret = stt_destroy(stt);
}

/**
 * @testcase		utc_stt_destroy_n2
 * @since_tizen		2.3
 * @description		Negative UTC for stt handle destroy (Fail to destroy in callback function)
 */
int utc_stt_destroy_n2(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_destroy(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		/* Fail to destroy in callback function */
		stt_h stt = NULL;
		ret = stt_create(&stt);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_set_state_changed_cb(stt, __stt_n2_state_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_get_state(stt, &g_temp_current_state);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_prepare(stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_temp_current_state){
			ecore_main_loop_iterate();
		}

		assert_eq(g_n2_state_changed_ret, STT_ERROR_OPERATION_FAILED);

		ret = stt_destroy(stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_prepare_p
 * @since_tizen		2.3
 * @description		Positive UTC for connect service daemon
 */
int utc_stt_prepare_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state){
		        ecore_main_loop_iterate();
		}
		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_prepare_n
 * @since_tizen		2.3
 * @description		Negative UTC for connect service daemon
 */
int utc_stt_prepare_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_prepare(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_prepare(NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_prepare_n1
 * @since_tizen		2.3
 * @description		Negative UTC for connect service daemon (Already connected)
 */
int utc_stt_prepare_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_prepare(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		/* Check invalid state */
		stt_h stt = NULL;
		ret = stt_create(&stt);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_set_state_changed_cb(stt, __stt_temp_state_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_get_state(stt, &g_temp_current_state);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_prepare(stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_temp_current_state){
			ecore_main_loop_iterate();
		}

		ret = stt_prepare(stt);
		assert_eq(ret, STT_ERROR_INVALID_STATE);

		/* Destroy stt on ready state */
		ret = stt_destroy(stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unprepare_p
 * @since_tizen		2.3
 * @description		Positive UTC for disconnect service deaemon
 */
int utc_stt_unprepare_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

                while(STT_STATE_READY!=g_current_state){
                        ecore_main_loop_iterate();
                }

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unprepare_n
 * @since_tizen		2.3
 * @description		Negative UTC for disconnect service daemon (Not connected)
 */
int utc_stt_unprepare_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unprepare(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_unprepare(NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unprepare_n1
 * @since_tizen		2.3
 * @description		Negative UTC for disconnect service daemon (Not connected)
 */
int utc_stt_unprepare_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unprepare(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		/* Check invalid state */
		stt_h stt = NULL;
		ret = stt_create(&stt);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_unprepare(stt);
		assert_eq(ret, STT_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_foreach_supported_engines_p
 * @since_tizen		2.3
 * @description		Positive UTC for get supported engine list
 */
int utc_stt_foreach_supported_engines_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_foreach_supported_engines(g_stt, __stt_supported_engine_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_foreach_supported_engines(g_stt, __stt_supported_engine_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_foreach_supported_engines_n
 * @since_tizen		2.3
 * @description		Negative UTC for get supported engine list (Invalid parameter)
 */
int utc_stt_foreach_supported_engines_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_foreach_supported_engines(NULL, NULL, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_foreach_supported_engines(NULL, NULL, NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_foreach_supported_engines_n1
 * @since_tizen		2.3
 * @description		Negative UTC for get supported engine list (Invalid state)
 */
int utc_stt_foreach_supported_engines_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_foreach_supported_engines(NULL, NULL, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		/* Check invalid state */
		assert_neq(g_stt, NULL);

		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = stt_foreach_supported_engines(g_stt, __stt_supported_engine_cb, NULL);
		assert_eq(ret, STT_ERROR_INVALID_STATE);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_get_engine_p
 * @since_tizen		2.3
 * @description		Positive UTC for get current engine
 */
int utc_stt_get_engine_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_get_engine(g_stt, &g_engine_id);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_get_engine(g_stt, &g_engine_id);
		assert_eq(ret, STT_ERROR_NONE);

		if (NULL != g_engine_id) {
			free(g_engine_id);
			g_engine_id = NULL;
		}
	}

	return 0;
}

/**
 * @testcase		utc_stt_get_engine_n
 * @since_tizen		2.3
 * @description		Negative UTC for get current engine (Invalid handle)
 */
int utc_stt_get_engine_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_get_engine(NULL, &g_engine_id);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_get_engine(NULL, &g_engine_id);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);

		if (NULL != g_engine_id) {
			free(g_engine_id);
			g_engine_id = NULL;
		}

	}

	return 0;
}

/**
 * @testcase		utc_stt_get_engine_n1
 * @since_tizen		2.3
 * @description		Negative UTC for get current engine (Invalid state)
 */
int utc_stt_get_engine_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_get_engine(NULL, &g_engine_id);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		/* Check invalid state */
		assert_neq(g_stt, NULL);

		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = stt_get_engine(g_stt, &g_engine_id);
		assert_eq(ret, STT_ERROR_INVALID_STATE);

		if (NULL != g_engine_id) {
			free(g_engine_id);
			g_engine_id = NULL;
		}

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_engine_p
 * @since_tizen		2.3
 * @description		Positive UTC for set current engine
 */
int utc_stt_set_engine_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_engine(g_stt, g_engine_id);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_get_engine(g_stt, &g_engine_id);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_set_engine(g_stt, g_engine_id);
		assert_eq(ret, STT_ERROR_NONE);

		if (NULL != g_engine_id) {
			free(g_engine_id);
			g_engine_id = NULL;
		}
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_engine_n
 * @since_tizen		2.3
 * @description		Negative UTC for set current engine (Invalid parameter)
 */
int utc_stt_set_engine_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_engine(NULL, g_engine_id);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_set_engine(NULL, NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_engine_n1
 * @since_tizen		2.3
 * @description		Negative UTC for set current engine (Invalid state)
 */
int utc_stt_set_engine_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_engine(NULL, g_engine_id);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		/* Check invalid state */
		assert_neq(g_stt, NULL);
		ret = stt_get_engine(g_stt, &g_engine_id);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = stt_set_engine(g_stt, g_engine_id);
		assert_eq(ret, STT_ERROR_INVALID_STATE);

		if (NULL != g_engine_id) {
			free(g_engine_id);
			g_engine_id = NULL;
		}

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_foreach_supported_languages_p
 * @since_tizen		2.3
 * @description		Positive UTC for get supported language list
 */
int utc_stt_foreach_supported_languages_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_foreach_supported_languages(g_stt, __stt_supported_language_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_foreach_supported_languages(g_stt, __stt_supported_language_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_foreach_supported_languages_n
 * @since_tizen		2.3
 * @description		Negative UTC for get supported language list (Invalid parameter)
 */
int utc_stt_foreach_supported_languages_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_foreach_supported_languages(NULL, NULL, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_foreach_supported_languages(NULL, NULL, NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_get_default_language_p
 * @since_tizen		2.3
 * @description		Positive UTC for get current language
 */
int utc_stt_get_default_language_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_get_default_language(g_stt, &g_language);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_get_default_language(g_stt, &g_language);
		assert_eq(ret, STT_ERROR_NONE);

		if (NULL != g_language) {
			free(g_language);
			g_language = NULL;
		}
	}

	return 0;
}

/**
 * @testcase		utc_stt_get_default_language_n
 * @since_tizen		2.3
 * @description		Negative UTC for get current language (Invalid handle)
 */
int utc_stt_get_default_language_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_get_default_language(NULL, &g_language);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_get_default_language(NULL, &g_language);
		free (g_language);
		g_language = NULL;
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_get_state_p
 * @since_tizen		2.3
 * @description		Positive UTC for get current state
 */
int utc_stt_get_state_p(void)
{
	stt_state_e state;
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_get_state(g_stt, &state);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_get_state(g_stt, &state);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_get_state_n
 * @since_tizen		2.3
 * @description		Negative UTC for get current state (Invalid handle)
 */
int utc_stt_get_state_n(void)
{
	stt_state_e state;
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_get_state(NULL, &state);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_get_state(NULL, &state);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_is_recognition_type_supported_p
 * @since_tizen		2.3
 * @description		Positive UTC for check recognition type is supported
 */
int utc_stt_is_recognition_type_supported_p(void)
{
	bool support;
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_is_recognition_type_supported(g_stt, STT_RECOGNITION_TYPE_FREE, &support);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state) {
                        ecore_main_loop_iterate();
                }
		ret = stt_is_recognition_type_supported(g_stt, STT_RECOGNITION_TYPE_FREE, &support);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_is_recognition_type_supported_p1
 * @since_tizen		2.3
 * @description		Positive UTC for check recognition type is supported
 */
int utc_stt_is_recognition_type_supported_p1(void)
{
	bool support;
	int ret = STT_ERROR_NONE;
	const char* type = "STT_RECOGNITION_TYPE_TEST";

	if (false == g_stt_supported) {
		ret = stt_is_recognition_type_supported(g_stt, type, &support);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);

		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

                while (STT_STATE_READY != g_current_state) {
                        ecore_main_loop_iterate();
                }

		support = true;
		ret = stt_is_recognition_type_supported(g_stt, type, &support);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_is_recognition_type_supported_n
 * @since_tizen		2.3
 * @description		Negative UTC for check recognition type is supported (Invalid handle)
 */
int utc_stt_is_recognition_type_supported_n(void)
{
	bool support;
	int ret = STT_ERROR_NONE;
	const char* type = "STT_RECOGNITION_TYPE_NOT_SUPPORTED";

	if (false == g_stt_supported) {
		ret = stt_is_recognition_type_supported(g_stt, type, &support);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		/* Check invalid state */
		assert_neq(g_stt, NULL);
		ret = stt_is_recognition_type_supported(NULL, type, &support);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_is_recognition_type_supported_n1
 * @since_tizen		2.3
 * @description		Negative UTC for check recognition type is supported (Invalid state)
 */
int utc_stt_is_recognition_type_supported_n1(void)
{
	bool support;
	int ret = STT_ERROR_NONE;
	const char* type = "STT_RECOGNITION_TYPE_NOT_SUPPORTED";

	if (false == g_stt_supported) {
		ret = stt_is_recognition_type_supported(g_stt, type, &support);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		/* Check invalid state */
		assert_neq(g_stt, NULL);
		ret = stt_is_recognition_type_supported(g_stt, type, &support);
		assert_eq(ret, STT_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_is_recognition_type_supported_n2
 * @since_tizen		2.3
 * @description		Negative UTC for check recognition type is supported (Invalid parameter)
 */
int utc_stt_is_recognition_type_supported_n2(void)
{
	bool support;
	int ret = STT_ERROR_NONE;
	const char* type = "STT_RECOGNITION_TYPE_NOT_SUPPORTED";

	if (false == g_stt_supported) {
		ret = stt_is_recognition_type_supported(g_stt, type, &support);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		/* Check invalid state */
		assert_neq(g_stt, NULL);
		ret = stt_is_recognition_type_supported(NULL, NULL, NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_silence_detection_p
 * @since_tizen		2.3
 * @description		Positive UTC for set silence detection option
 */
int utc_stt_set_silence_detection_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_silence_detection(g_stt, STT_OPTION_SILENCE_DETECTION_AUTO);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

                while (STT_STATE_READY != g_current_state) {
                        ecore_main_loop_iterate();
                }
		ret = stt_set_silence_detection(g_stt, STT_OPTION_SILENCE_DETECTION_AUTO);
		assert(STT_ERROR_NONE == ret || STT_ERROR_NOT_SUPPORTED_FEATURE == ret);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_silence_detection_n
 * @since_tizen		2.3
 * @description		Negative UTC for set silence detection option (Invalid handle)
 */
int utc_stt_set_silence_detection_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_silence_detection(NULL, STT_OPTION_SILENCE_DETECTION_AUTO);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_set_silence_detection(NULL, STT_OPTION_SILENCE_DETECTION_AUTO);
		assert(STT_ERROR_NONE != ret && STT_ERROR_NOT_SUPPORTED_FEATURE != ret);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_silence_detection_n1
 * @since_tizen		2.3
 * @description		Negative UTC for set silence detection option (Invalid state)
 */
int utc_stt_set_silence_detection_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_silence_detection(NULL, STT_OPTION_SILENCE_DETECTION_AUTO);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		/* Check invalid state */
		assert_neq(g_stt, NULL);
		ret = stt_set_silence_detection(g_stt, STT_OPTION_SILENCE_DETECTION_AUTO);
		assert_eq(ret, STT_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_silence_detection_n2
 * @since_tizen		2.3
 * @description		Negative UTC for set silence detection option (Invalid parameter)
 */
int utc_stt_set_silence_detection_n2(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_silence_detection(NULL, STT_OPTION_SILENCE_DETECTION_AUTO);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		/* Check invalid parameter */
		assert_neq(g_stt, NULL);
		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state) {
			ecore_main_loop_iterate();
		}

		ret = stt_set_silence_detection(g_stt, -1);
		assert(STT_ERROR_INVALID_PARAMETER == ret || STT_ERROR_NOT_SUPPORTED_FEATURE == ret);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_start_p
 * @since_tizen		2.3
 * @description		Positive UTC for start recording for recognition
 */
int utc_stt_start_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_start(g_stt, g_language, STT_RECOGNITION_TYPE_FREE);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);

		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state) {
                        ecore_main_loop_iterate();
                }

		ret = stt_get_default_language(g_stt, &g_language);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_start(g_stt, g_language, STT_RECOGNITION_TYPE_FREE);
		assert_eq(ret, STT_ERROR_NONE);

		if (NULL != g_language) {
			free(g_language);
			g_language = NULL;
		}

		while (STT_STATE_RECORDING != g_current_state && STT_ERROR_OUT_OF_NETWORK != g_error){
			ecore_main_loop_iterate();
		}

		dlog_print(DLOG_INFO, "NativeTCT", "State(%d)", g_current_state);

		int count = 0;
		while (STT_STATE_RECORDING == g_current_state && STT_ERROR_OUT_OF_NETWORK != g_error){
			ecore_main_loop_iterate();
			usleep(100000);
			count++;

			if (100 == count) {
				ret = stt_cancel(g_stt);
				assert_eq(ret, STT_ERROR_NONE);
				break;
			}
		}

		while (STT_STATE_READY != g_current_state) {
                        ecore_main_loop_iterate();
                }

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_start_n
 * @since_tizen		2.3
 * @description		Negative UTC for start recording for recognition (Invalid state)
 */
int utc_stt_start_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_start(NULL, g_language, STT_RECOGNITION_TYPE_FREE);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_start(g_stt, NULL, STT_RECOGNITION_TYPE_FREE);
		assert_eq(ret, STT_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_start_n1
 * @since_tizen		2.3
 * @description		Negative UTC for start recording for recognition (Invalid handle)
 */
int utc_stt_start_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_start(NULL, g_language, STT_RECOGNITION_TYPE_FREE);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		ret = stt_start(NULL, NULL, STT_RECOGNITION_TYPE_FREE);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}


/**
 * @testcase		utc_stt_stop_p
 * @since_tizen		2.3
 * @description		Positive UTC for stop recording for processing
 */
int utc_stt_stop_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_stop(g_stt);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);

		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = stt_get_default_language(g_stt, &g_language);
		assert_eq(ret, STT_ERROR_NONE);


		ret = stt_start(g_stt, g_language, STT_RECOGNITION_TYPE_FREE);
		assert_eq(ret, STT_ERROR_NONE);

		if (NULL != g_language) {
			free(g_language);
			g_language = NULL;
		}

		int count = 0;
		while (STT_STATE_RECORDING != g_current_state && STT_ERROR_OUT_OF_NETWORK != g_error){
			ecore_main_loop_iterate();
		}

		count = 0;
		while (STT_STATE_RECORDING == g_current_state && STT_ERROR_OUT_OF_NETWORK != g_error){
			ecore_main_loop_iterate();
			usleep(100000);
			count++;

			if (5 == count) {
				ret = stt_stop(g_stt);
				assert_eq(ret, STT_ERROR_NONE);
				break;
			}
		}

		count = 0;
		while (STT_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
			usleep(100000);
			count++;

			if (100 == count) {
				ret = stt_cancel(g_stt);
				assert_eq(ret, STT_ERROR_NONE);
			}
		}

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_stop_n
 * @since_tizen		2.3
 * @description		Negative UTC for stop recording for processing (Invalid handle)
 */
int utc_stt_stop_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_stop(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_stop(NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_cancel_p
 * @since_tizen		2.3
 * @description		Positive UTC for cancel recording
 */
int utc_stt_cancel_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_cancel(g_stt);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);

		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = stt_start(g_stt, NULL, STT_RECOGNITION_TYPE_FREE);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_RECORDING != g_current_state && STT_ERROR_OUT_OF_NETWORK != g_error){
			ecore_main_loop_iterate();
		}

		int i = 0;
		for (i = 0; i < 10 && STT_ERROR_OUT_OF_NETWORK != g_error; i++) {
			ecore_main_loop_iterate();
		}

		if (STT_STATE_RECORDING == g_current_state || STT_STATE_PROCESSING == g_current_state) {
			ret = stt_cancel(g_stt);
			assert_eq(ret, STT_ERROR_NONE);

			while (STT_STATE_READY != g_current_state){
				ecore_main_loop_iterate();
			}
		}

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_cancel_n
 * @since_tizen		2.3
 * @description		Negative UTC for cancel recording (Invalid handle)
 */
int utc_stt_cancel_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_cancel(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_cancel(NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_cancel_n1
 * @since_tizen		2.3
 * @description		Negative UTC for cancel recording (Invalid state)
 */
int utc_stt_cancel_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_cancel(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_neq(g_stt, NULL);
		ret = stt_cancel(g_stt);
		assert_eq(ret, STT_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_get_recording_volume_p
 * @since_tizen		2.3
 * @description		Positive UTC for get recording volume
 */
int utc_stt_get_recording_volume_p(void)
{
	float vol;
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_get_recording_volume(g_stt, &vol);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);

		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = stt_start(g_stt, NULL, STT_RECOGNITION_TYPE_FREE);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_RECORDING != g_current_state && STT_ERROR_OUT_OF_NETWORK != g_error){
			ecore_main_loop_iterate();
		}

		int i = 0;
		for (i = 0; i < 10 && STT_ERROR_OUT_OF_NETWORK != g_error; i++) {
			ecore_main_loop_iterate();
		}

		if (STT_ERROR_OUT_OF_NETWORK != g_error) {
			ret = stt_get_recording_volume(g_stt, &vol);
			assert_eq(ret, STT_ERROR_NONE);

			ecore_main_loop_iterate();

			ret = stt_cancel(g_stt);
			assert_eq(ret, STT_ERROR_NONE);
		}

		while (STT_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_get_recording_volume_n
 * @since_tizen		2.3
 * @description		Negative UTC for get recording volume (Invalid handle)
 */
int utc_stt_get_recording_volume_n(void)
{
	float vol;
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_get_recording_volume(NULL, &vol);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_get_recording_volume(NULL, &vol);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_get_recording_volume_n1
 * @since_tizen		2.3
 * @description		Negative UTC for get recording volume (Invalid state)
 */
int utc_stt_get_recording_volume_n1(void)
{
	float vol;
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_get_recording_volume(NULL, &vol);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_neq(g_stt, NULL);
		ret = stt_get_recording_volume(g_stt, &vol);
		assert_eq(ret, STT_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_recognition_result_cb_p
 * @since_tizen		2.3
 * @description		Positive UTC for set recognition result callback
 */
int utc_stt_set_recognition_result_cb_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_recognition_result_cb(g_stt, __stt_recognition_result_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_set_recognition_result_cb(g_stt, __stt_recognition_result_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_recognition_result_cb_n
 * @since_tizen		2.3
 * @description		Negative UTC for set recognition result callback (Invalid handle)
 */
int utc_stt_set_recognition_result_cb_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_recognition_result_cb(NULL, __stt_recognition_result_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_set_recognition_result_cb(NULL, __stt_recognition_result_cb, NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_recognition_result_cb_n1
 * @since_tizen		2.3
 * @description		Nagative UTC for set recognition result callback (Invalid state)
 */
int utc_stt_set_recognition_result_cb_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_recognition_result_cb(NULL, __stt_recognition_result_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_neq(g_stt, NULL);
		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = stt_set_recognition_result_cb(g_stt, __stt_recognition_result_cb, NULL);
		assert_eq(ret, STT_ERROR_INVALID_STATE);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_recognition_result_cb_p
 * @since_tizen		2.3
 * @description		Positive UTC for unset recognition result callback
 */
int utc_stt_unset_recognition_result_cb_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_recognition_result_cb(g_stt);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_set_recognition_result_cb(g_stt, __stt_recognition_result_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_unset_recognition_result_cb(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_recognition_result_cb_n
 * @since_tizen		2.3
 * @description		Negative UTC for unset recognition result callback (Invalid handle)
 */
int utc_stt_unset_recognition_result_cb_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_recognition_result_cb(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_unset_recognition_result_cb(NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_recognition_result_cb_n1
 * @since_tizen		2.3
 * @description		Negative UTC for unset recognition result callback (Invalid state)
 */
int utc_stt_unset_recognition_result_cb_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_recognition_result_cb(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_neq(g_stt, NULL);
		ret = stt_set_recognition_result_cb(g_stt, __stt_recognition_result_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = stt_unset_recognition_result_cb(g_stt);
		assert_eq(ret, STT_ERROR_INVALID_STATE);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_state_changed_cb_p
 * @since_tizen		2.3
 * @description		Positive UTC for set state changed callback
 */
int utc_stt_set_state_changed_cb_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret  = stt_set_state_changed_cb(g_stt, __stt_state_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret  = stt_set_state_changed_cb(g_stt, __stt_state_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_state_changed_cb_n
 * @since_tizen		2.3
 * @description		Negative UTC for set state changed callback (Invalid handle)
 */
int utc_stt_set_state_changed_cb_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_state_changed_cb(NULL, __stt_state_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_set_state_changed_cb(NULL, __stt_state_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_state_changed_cb_n1
 * @since_tizen		2.3
 * @description		Negative UTC for set state changed callback (Invalid state)
 */
int utc_stt_set_state_changed_cb_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_state_changed_cb(NULL, __stt_state_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_neq(g_stt, NULL);

		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = stt_set_state_changed_cb(g_stt, __stt_state_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_INVALID_STATE);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_state_changed_cb_p
 * @since_tizen		2.3
 * @description		Positive UTC for unset state changed callback
 */
int utc_stt_unset_state_changed_cb_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_state_changed_cb(g_stt);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_unset_state_changed_cb(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_set_state_changed_cb(g_stt, __stt_state_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_state_changed_cb_n
 * @since_tizen		2.3
 * @description		Negative UTC for unset state changed callback (Invalid handle)
 */
int utc_stt_unset_state_changed_cb_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_state_changed_cb(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_unset_state_changed_cb(NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_state_changed_cb_n1
 * @since_tizen		2.3
 * @description		Negative UTC for unset state changed callback (Invalid state)
 */
int utc_stt_unset_state_changed_cb_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_state_changed_cb(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_neq(g_stt, NULL);
		ret = stt_set_state_changed_cb(g_stt, __stt_state_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = stt_unset_state_changed_cb(g_stt);
		assert_eq(ret, STT_ERROR_INVALID_STATE);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_set_state_changed_cb(g_stt, __stt_state_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_error_cb_p
 * @since_tizen		2.3
 * @description		Positive UTC for set error callback
 */
int utc_stt_set_error_cb_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_error_cb(g_stt, __stt_error_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_set_error_cb(g_stt, __stt_error_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_error_cb_n
 * @since_tizen		2.3
 * @description		Negative UTC for set error callback (Invalid handle)
 */
int utc_stt_set_error_cb_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_error_cb(NULL, __stt_error_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_set_error_cb(NULL, __stt_error_cb, NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_error_cb_n1
 * @since_tizen		2.3
 * @description		Negative UTC for set error callback (Invalid state)
 */
int utc_stt_set_error_cb_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_error_cb(NULL, __stt_error_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_neq(g_stt, NULL);

		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = stt_set_error_cb(g_stt, __stt_error_cb, NULL);
		assert_eq(ret, STT_ERROR_INVALID_STATE);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_error_cb_p
 * @since_tizen		2.3
 * @description		Positive UTC for unset error callback
 */
int utc_stt_unset_error_cb_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_error_cb(g_stt);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_set_error_cb(g_stt, __stt_error_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);
		ret = stt_unset_error_cb(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_error_cb_n
 * @since_tizen		2.3
 * @description		Negative UTC for unset error callback (Invalid handle)
 */
int utc_stt_unset_error_cb_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_error_cb(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_unset_error_cb(NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_error_cb_n1
 * @since_tizen		2.3
 * @description		Negative UTC for unset error callback (Invalid state)
 */
int utc_stt_unset_error_cb_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_error_cb(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_neq(g_stt, NULL);
		ret = stt_set_error_cb(g_stt, __stt_error_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = stt_unset_error_cb(g_stt);
		assert_eq(ret, STT_ERROR_INVALID_STATE);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_default_language_changed_cb_p
 * @since_tizen		2.3
 * @description		Positive UTC for set current language changed callback
 */
int utc_stt_set_default_language_changed_cb_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_default_language_changed_cb(g_stt, __stt_default_language_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_set_default_language_changed_cb(g_stt, __stt_default_language_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_default_language_changed_cb_n
 * @since_tizen		2.3
 * @description		Negative UTC for set current language changed callback (Invalid handle)
 */
int utc_stt_set_default_language_changed_cb_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_default_language_changed_cb(NULL, __stt_default_language_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_set_default_language_changed_cb(NULL, __stt_default_language_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_default_language_changed_cb_n1
 * @since_tizen		2.3
 * @description		Negative UTC for set current language changed callback (Invalid state)
 */
int utc_stt_set_default_language_changed_cb_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_default_language_changed_cb(NULL, __stt_default_language_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_neq(g_stt, NULL);

		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = stt_set_default_language_changed_cb(g_stt, __stt_default_language_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_INVALID_STATE);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_default_language_changed_cb_p
 * @since_tizen		2.3
 * @description		Positive UTC for unset current language changed callback
 */
int utc_stt_unset_default_language_changed_cb_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_default_language_changed_cb(g_stt);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_set_default_language_changed_cb(g_stt, __stt_default_language_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);
		ret = stt_unset_default_language_changed_cb(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_default_language_changed_cb_n
 * @since_tizen		2.3
 * @description		Negative UTC for unset current language changed callback (Invalid handle)
 */
int utc_stt_unset_default_language_changed_cb_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_default_language_changed_cb(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_unset_default_language_changed_cb(NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_default_language_changed_cb_n1
 * @since_tizen		2.3
 * @description		Negative UTC for unset current language changed callback (Invalid state)
 */
int utc_stt_unset_default_language_changed_cb_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_default_language_changed_cb(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_neq(g_stt, NULL);
		ret = stt_set_default_language_changed_cb(g_stt, __stt_default_language_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = stt_unset_default_language_changed_cb(g_stt);
		assert_eq(ret, STT_ERROR_INVALID_STATE);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_start_sound_p
 * @since_tizen		2.3
 * @description		Positive UTC for set start sound
 */
int utc_stt_set_start_sound_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_start_sound(g_stt, "/opt/usr/apps/core-stt-tests/data/ringtone.wav");
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		if (0 != access("/opt/usr/apps/core-stt-tests/data/ringtone.wav", F_OK)) {
			return 0;
		}

		assert_neq(g_stt, NULL);
		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state) {
                        ecore_main_loop_iterate();
                }

		ret = stt_set_start_sound(g_stt, "/opt/usr/apps/core-stt-tests/data/ringtone.wav");
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_start_sound_n
 * @since_tizen		2.3
 * @description		Negative UTC for set start sound (Invalid parameter)
 */
int utc_stt_set_start_sound_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_start_sound(g_stt, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_set_start_sound(NULL, NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_start_sound_n1
 * @since_tizen		2.3
 * @description		Negative UTC for set start sound (Invalid state)
 */
int utc_stt_set_start_sound_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_start_sound(g_stt, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		if (0 != access("/opt/usr/apps/core-stt-tests/data/ringtone.wav", F_OK)) {
			return 0;
		}

		/* check invalid state */
		assert_neq(g_stt, NULL);
		ret = stt_set_start_sound(g_stt, "/opt/usr/apps/core-stt-tests/data/ringtone.wav");
		assert_eq(ret, STT_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_start_sound_p
 * @since_tizen		2.3
 * @description		Positive UTC for unset start sound
 */
int utc_stt_unset_start_sound_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_start_sound(g_stt);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		if (0 != access("/opt/usr/apps/core-stt-tests/data/ringtone.wav", F_OK)) {
			return 0;
		}

		assert_neq(g_stt, NULL);
		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state) {
                        ecore_main_loop_iterate();
                }
		ret = stt_set_start_sound(g_stt, "/opt/usr/apps/core-stt-tests/data/ringtone.wav");
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_unset_start_sound(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_start_sound_n
 * @since_tizen		2.3
 * @description		Negative UTC for unset start sound (Invalid handle)
 */
int utc_stt_unset_start_sound_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_start_sound(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		assert_neq(STT_STATE_READY, g_current_state);

		ret = stt_unset_start_sound(NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_start_sound_n1
 * @since_tizen		2.3
 * @description		Negative UTC for unset start sound (Invalid state)
 */
int utc_stt_unset_start_sound_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_start_sound(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_neq(g_stt, NULL);
		assert_neq(STT_STATE_READY, g_current_state);

		ret = stt_unset_start_sound(g_stt);
		assert_eq(ret, STT_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_stop_sound_p
 * @since_tizen		2.3
 * @description		Positive UTC for set stop sound
 */
int utc_stt_set_stop_sound_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_stop_sound(g_stt, "test.wav");
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		if (0 != access("/opt/usr/apps/core-stt-tests/data/ringtone.wav", F_OK)) {
			return 0;
		}

		assert_neq(g_stt, NULL);
		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state) {
			ecore_main_loop_iterate();
		}

		ret = stt_set_stop_sound(g_stt, "/opt/usr/apps/core-stt-tests/data/ringtone.wav");
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_stop_sound_n
 * @since_tizen		2.3
 * @description		Negative UTC for set stop sound (Invalid handle)
 */
int utc_stt_set_stop_sound_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_stop_sound(g_stt, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		if (0 != access("/opt/usr/apps/core-stt-tests/data/ringtone.wav", F_OK)) {
			return 0;
		}

		assert_neq(g_stt, NULL);
		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state) {
			ecore_main_loop_iterate();
		}

		ret = stt_set_stop_sound(NULL, "/opt/usr/apps/core-stt-tests/data/ringtone.wav");
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_stop_sound_n1
 * @since_tizen		2.3
 * @description		Negative UTC for set stop sound (Invalid parameter)
 */
int utc_stt_set_stop_sound_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_stop_sound(g_stt, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		ret = stt_set_stop_sound(g_stt, NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_stop_sound_n2
 * @since_tizen		2.3
 * @description		Negative UTC for set stop sound (Invalid state)
 */
int utc_stt_set_stop_sound_n2(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_stop_sound(g_stt, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		if (0 != access("/opt/usr/apps/core-stt-tests/data/ringtone.wav", F_OK)) {
			return 0;
		}

		assert_neq(g_stt, NULL);
		ret = stt_set_stop_sound(g_stt, "/opt/usr/apps/core-stt-tests/data/ringtone.wav");
		assert_eq(ret, STT_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_stop_sound_p
 * @since_tizen		2.3
 * @description		Positive UTC for unset stop sound
 */
int utc_stt_unset_stop_sound_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_stop_sound(g_stt);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		if (0 != access("/opt/usr/apps/core-stt-tests/data/ringtone.wav", F_OK)) {
			return 0;
		}

		assert_neq(g_stt, NULL);
		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state) {
			ecore_main_loop_iterate();
		}

		ret = stt_set_stop_sound(g_stt, "/opt/usr/apps/core-stt-tests/data/ringtone.wav");
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_unset_stop_sound(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_stop_sound_n
 * @since_tizen		2.3
 * @description		Negative UTC for unset stop sound (Invalid handle)
 */
int utc_stt_unset_stop_sound_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_stop_sound(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		assert_neq(STT_STATE_READY, g_current_state);

		ret = stt_unset_stop_sound(NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_stop_sound_n1
 * @since_tizen		2.3
 * @description		Negative UTC for unset stop sound (Invalid state)
 */
int utc_stt_unset_stop_sound_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_stop_sound(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_neq(g_stt, NULL);
		assert_neq(STT_STATE_READY, g_current_state);

		ret = stt_unset_stop_sound(g_stt);
		assert_eq(ret, STT_ERROR_INVALID_STATE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_foreach_detailed_result_p
 * @since_tizen		2.3
 * @description		Positive UTC for get detailed result
 */
int utc_stt_foreach_detailed_result_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_foreach_detailed_result(g_stt, __stt_result_time_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_foreach_detailed_result(g_stt, __stt_result_time_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_foreach_detailed_result_n
 * @since_tizen		2.3
 * @description		Negative UTC for get detailed result (Invalid handle)
 */
int utc_stt_foreach_detailed_result_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_foreach_detailed_result(NULL, __stt_result_time_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_foreach_detailed_result(NULL, __stt_result_time_cb, NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_get_error_message_n
 * @since_tizen		3.0
 * @description			Negative UTC for get error message (invalid parameter)
 */
int utc_stt_get_error_message_n(void)
{
	int ret = STT_ERROR_NONE;
	if (false == g_stt_supported) {
		ret = stt_get_error_message(g_stt, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_neq(g_stt, NULL);

	ret = stt_get_error_message(g_stt, NULL);
	assert_eq(ret, STT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_stt_get_error_message_n1
 * @since_tizen		3.0
 * @description			Negative UTC for get error message (invalid parameter)
 */
int utc_stt_get_error_message_n1(void)
{
	int ret = STT_ERROR_NONE;
	if (false == g_stt_supported) {
		ret = stt_get_error_message(g_stt, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stt_get_error_message(NULL, NULL);
	assert_eq(ret, STT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_stt_get_error_message_n2
 * @since_tizen		3.0
 * @description			Negative UTC for get error message (operation failed)
 */
int utc_stt_get_error_message_n2(void)
{
	int ret = STT_ERROR_NONE;
	if (false == g_stt_supported) {
		ret = stt_get_error_message(g_stt, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_neq(g_stt, NULL);
	char* err_msg = NULL;
	ret = stt_get_error_message(g_stt, &err_msg);
	assert_eq(ret, STT_ERROR_OPERATION_FAILED);

	return 0;
}

/**
 * @testcase		utc_stt_set_private_data_p
 * @since_tizen		3.0
 * @description		Positive UTC for set private data
 */
int utc_stt_set_private_data_p(void)
{
	int ret = STT_ERROR_NONE;
	if (false == g_stt_supported) {
		ret = stt_set_private_data(g_stt, NULL, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_neq(g_stt, NULL);

	ret = stt_prepare(g_stt);
	assert_eq(ret, STT_ERROR_NONE);

	while (STT_STATE_READY != g_current_state) {
		ecore_main_loop_iterate();
	}

	ret = stt_set_private_data(g_stt, "gender", "data");
	assert_eq(ret, STT_ERROR_NONE);

	ret = stt_unprepare(g_stt);
	assert_eq(ret, STT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_stt_set_private_data_n
 * @since_tizen		3.0
 * @description		Negative UTC for set private data (invalid parameter)
 */
int utc_stt_set_private_data_n(void)
{
	int ret = STT_ERROR_NONE;
	if (false == g_stt_supported) {
		ret = stt_set_private_data(g_stt, NULL, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_neq(g_stt, NULL);

	ret = stt_set_private_data(NULL, NULL, NULL);
	assert_eq(ret, STT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_stt_set_private_data_n1
 * @since_tizen		3.0
 * @description		Negative UTC for set private data (invalid parameter)
 */
int utc_stt_set_private_data_n1(void)
{
	int ret = STT_ERROR_NONE;
	if (false == g_stt_supported) {
		ret = stt_set_private_data(g_stt, NULL, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_neq(g_stt, NULL);

	ret = stt_set_private_data(g_stt, "gender", NULL);
	assert_eq(ret, STT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_stt_set_private_data_n2
 * @since_tizen		3.0
 * @description		Negative UTC for set private data (invalid parameter)
 */
int utc_stt_set_private_data_n2(void)
{
	int ret = STT_ERROR_NONE;
	if (false == g_stt_supported) {
		ret = stt_set_private_data(g_stt, NULL, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_neq(g_stt, NULL);

	ret = stt_set_private_data(g_stt, NULL, "data");
	assert_eq(ret, STT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_stt_set_private_data_n3
 * @since_tizen		3.0
 * @description		Negative UTC for set private data (invalid state)
 */
int utc_stt_set_private_data_n3(void)
{
	int ret = STT_ERROR_NONE;
	if (false == g_stt_supported) {
		ret = stt_set_private_data(g_stt, NULL, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_neq(g_stt, NULL);

	ret = stt_set_private_data(g_stt, "gender", "data");
	assert_eq(ret, STT_ERROR_INVALID_STATE);

	return 0;
}

/**
 * @testcase		utc_stt_get_private_data_p
 * @since_tizen		3.0
 * @description		Positive UTC for get private data
 */
int utc_stt_get_private_data_p(void)
{
	int ret = STT_ERROR_NONE;
	if (false == g_stt_supported) {
		ret = stt_get_private_data(g_stt, NULL, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_neq(g_stt, NULL);

	ret = stt_prepare(g_stt);
	assert_eq(ret, STT_ERROR_NONE);

	while (STT_STATE_READY != g_current_state) {
		ecore_main_loop_iterate();
	}

	char *data = NULL;
	ret = stt_get_private_data(g_stt, "gender", &data);
	assert_eq(ret, STT_ERROR_NONE);
	free(data);

	ret = stt_unprepare(g_stt);
	assert_eq(ret, STT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_stt_get_private_data_n
 * @since_tizen		3.0
 * @description		Negative UTC for get private data
 */
int utc_stt_get_private_data_n(void)
{
	int ret = STT_ERROR_NONE;
	if (false == g_stt_supported) {
		ret = stt_get_private_data(g_stt, NULL, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_neq(g_stt, NULL);

	ret = stt_get_private_data(NULL, NULL, NULL);
	assert_neq(ret, STT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_stt_get_private_data_n1
 * @since_tizen		3.0
 * @description		Negative UTC for get private data (invalid parameter)
 */
int utc_stt_get_private_data_n1(void)
{
	int ret = STT_ERROR_NONE;
	if (false == g_stt_supported) {
		ret = stt_get_private_data(g_stt, NULL, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_neq(g_stt, NULL);

	ret = stt_get_private_data(g_stt, "gender", NULL);
	assert_eq(ret, STT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_stt_get_private_data_n2
 * @since_tizen		3.0
 * @description		Negative UTC for get private data (invalid parameter)
 */
int utc_stt_get_private_data_n2(void)
{
	int ret = STT_ERROR_NONE;
	if (false == g_stt_supported) {
		ret = stt_get_private_data(g_stt, NULL, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_neq(g_stt, NULL);

	char* data = NULL;
	ret = stt_get_private_data(g_stt, NULL, &data);
	assert_eq(ret, STT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_stt_get_private_data_n3
 * @since_tizen		3.0
 * @description		Negative UTC for get private data (invalid state)
 */
int utc_stt_get_private_data_n3(void)
{
	int ret = STT_ERROR_NONE;
	if (false == g_stt_supported) {
		ret = stt_get_private_data(g_stt, NULL, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_neq(g_stt, NULL);

	char* data = NULL;
	ret = stt_get_private_data(g_stt, "gender", &data);
	assert_eq(ret, STT_ERROR_INVALID_STATE);

	return 0;
}

/**
 * @testcase		utc_stt_set_credential_p
 * @since_tizen		3.0
 * @description		Positive UTC for set credential
 */
int utc_stt_set_credential_p(void)
{
	int ret = STT_ERROR_NONE;
	if (false == g_stt_supported) {
		ret = stt_set_credential(g_stt, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_neq(g_stt, NULL);

	ret = stt_set_credential(g_stt, "test");
	assert_eq(ret, STT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_stt_set_credential_n
 * @since_tizen		3.0
 * @description		Negative UTC for set credential
 */
int utc_stt_set_credential_n(void)
{
	int ret = STT_ERROR_NONE;
	if (false == g_stt_supported) {
		ret = stt_set_credential(g_stt, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_neq(g_stt, NULL);

	ret = stt_set_credential(NULL, NULL);
	assert_neq(ret, STT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_stt_set_credential_n1
 * @since_tizen		3.0
 * @description		Negative UTC for set credential
 */
int utc_stt_set_credential_n1(void)
{
	int ret = STT_ERROR_NONE;
	if (false == g_stt_supported) {
		ret = stt_set_credential(g_stt, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_neq(g_stt, NULL);

	ret = stt_set_credential(g_stt, NULL);
	assert_neq(ret, STT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_stt_set_engine_changed_cb_p
 * @since_tizen		3.0
 * @description		Positive UTC for set current engine changed callback
 */
int utc_stt_set_engine_changed_cb_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_engine_changed_cb(g_stt, __stt_engine_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_set_engine_changed_cb(g_stt, __stt_engine_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_unset_engine_changed_cb(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_engine_changed_cb_n
 * @since_tizen		3.0
 * @description		Negative UTC for set current engine changed callback (Invalid handle)
 */
int utc_stt_set_engine_changed_cb_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_engine_changed_cb(NULL, __stt_engine_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_set_engine_changed_cb(NULL, __stt_engine_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_engine_changed_cb_n1
 * @since_tizen		3.0
 * @description		Negative UTC for set current engine changed callback (Invalid state)
 */
int utc_stt_set_engine_changed_cb_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_engine_changed_cb(NULL, __stt_engine_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);

		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = stt_set_engine_changed_cb(g_stt, __stt_engine_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_INVALID_STATE);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_engine_changed_cb_p
 * @since_tizen		3.0
 * @description		Positive UTC for unset current engine changed callback
 */
int utc_stt_unset_engine_changed_cb_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_engine_changed_cb(g_stt);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_set_engine_changed_cb(g_stt, __stt_engine_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);
		ret = stt_unset_engine_changed_cb(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_engine_changed_cb_n
 * @since_tizen		3.0
 * @description		Negative UTC for unset current engine changed callback (Invalid handle)
 */
int utc_stt_unset_engine_changed_cb_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_engine_changed_cb(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_unset_engine_changed_cb(NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_engine_changed_cb_n1
 * @since_tizen		3.0
 * @description		Negative UTC for unset current engine changed callback (Invalid state)
 */
int utc_stt_unset_engine_changed_cb_n1(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_engine_changed_cb(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_neq(g_stt, NULL);
		ret = stt_set_engine_changed_cb(g_stt, __stt_engine_changed_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_prepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);

		while (STT_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = stt_unset_engine_changed_cb(g_stt);
		assert_eq(ret, STT_ERROR_INVALID_STATE);

		ret = stt_unprepare(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_speech_status_cb_p
 * @since_tizen		5.5
 * @description		Positive UTC for set speech status callback
 */
int utc_stt_set_speech_status_cb_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_speech_status_cb(g_stt, __stt_speech_status_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_set_speech_status_cb(g_stt, __stt_speech_status_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);

		ret = stt_unset_speech_status_cb(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_set_speech_status_cb_n
 * @since_tizen		5.5
 * @description		Negative UTC for set speech status callback (Invalid handle)
 */
int utc_stt_set_speech_status_cb_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_set_speech_status_cb(NULL, __stt_speech_status_cb, NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_set_speech_status_cb(NULL, __stt_speech_status_cb, NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_speech_status_cb_p
 * @since_tizen		5.5
 * @description		Positive UTC for unset speech status callback
 */
int utc_stt_unset_speech_status_cb_p(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_speech_status_cb(g_stt);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(g_stt, NULL);
		ret = stt_set_speech_status_cb(g_stt, __stt_speech_status_cb, NULL);
		assert_eq(ret, STT_ERROR_NONE);
		ret = stt_unset_speech_status_cb(g_stt);
		assert_eq(ret, STT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_stt_unset_speech_status_cb_n
 * @since_tizen		5.5
 * @description		Negative UTC for unset speech status callback (Invalid handle)
 */
int utc_stt_unset_speech_status_cb_n(void)
{
	int ret = STT_ERROR_NONE;

	if (false == g_stt_supported) {
		ret = stt_unset_speech_status_cb(NULL);
		assert_eq(ret, STT_ERROR_NOT_SUPPORTED);
	} else {
		ret = stt_unset_speech_status_cb(NULL);
		assert_eq(ret, STT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}