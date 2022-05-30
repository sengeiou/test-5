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
#include <tts.h>
#include <stdlib.h>
#include <Ecore.h>

//& set: TTS

tts_h g_tts = NULL;
static char *g_language = NULL;
static int g_voice_type;
static tts_state_e g_current_state;
static int is_created_hndl = -1;
static int is_destroyed_hndl = -1;
static void __tts_state_changed_cb(tts_h tts, tts_state_e previous, tts_state_e current, void* user_data);
bool g_supported = false;
static tts_state_e g_current_state;
static bool g_utterance_started_cb = false;
static bool g_utterance_completed_cb = false;
static int g_utt_id = -1;
static char *g_text = "Speech Synthesis is the artificial production of human speech. A computer system used for this purpose is called a speech computer or speech synthesizer,\
	and can be implemented in software or hardware products. A text-to-speech (TTS) system converts normal language text into speech; other systems render symbolic linguistic\
	representations like phonetic transcriptions into speech.\
	Synthesized speech can be created by concatenating pieces of recorded speech that are stored in a database. Systems differ in the size of the stored speech units; \
	a system that stores phones or diphones provides the largest output range, but may lack clarity. For specific usage domains, the storage of entire words or sentences allows \
	for high-quality output. Alternatively, a synthesizer can incorporate a model of the vocal tract and other human voice characteristics to create a completely synthetic voice output.\
	The quality of a speech synthesizer is judged by its similarity to the human voice and by its ability to be understood clearly. An intelligible text-to-speech program allows people \
	with visual impairments or reading disabilities to listen to written works on a home computer. Many computer operating systems have included speech synthesizers since the early 1990s.\
	A text-to-speech system is composed of two parts:[3] a front-end and a back-end. The front-end has two major tasks. First, it converts raw text containing symbols like numbers and \
	abbreviations into the equivalent of written-out words. This process is often called text normalization, pre-processing, or tokenization. The front-end then assigns phonetic \
	transcriptions to each word, and divides and marks the text into prosodic units, like phrases, clauses, and sentences. The process of assigning phonetic transcriptions to words is \
	called text-to-phoneme or grapheme-to-phoneme conversion. Phonetic transcriptions and prosody information together make up the symbolic linguistic representation that is output by \
	the front-end. The back-end?often referred to as the synthesizer?then converts the symbolic linguistic representation into sound. In certain systems, this part includes the computation \
	of the target prosody (pitch contour, phoneme durations),[4] which is then imposed on the output speech. From Wikipedia";

void utc_tts_startup(void)
{
	system_info_get_platform_bool("http://tizen.org/feature/speech.synthesis",&g_supported);
	g_current_state = 0;
	/* start of TC */
	int ret = TTS_ERROR_NONE;
	ret = tts_create(&g_tts);
	is_created_hndl = ret;

	if(g_supported == false){
		g_tts = NULL;
		return;
	}

	ret = tts_set_state_changed_cb(g_tts, __tts_state_changed_cb, NULL);
	assert_eq(ret, TTS_ERROR_NONE);
	ret = tts_get_default_voice(g_tts, &g_language, &g_voice_type);
	assert_eq(ret, TTS_ERROR_NONE);
}

void utc_tts_cleanup(void)
{
	/* end of TC */
	free (g_language);
	g_language = NULL;

	int ret = TTS_ERROR_NONE;
	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	g_tts = NULL;
	is_created_hndl = -1;
}

static bool __tts_supported_voice_cb(tts_h tts, const char* language, int voice_type, void* user_data)
{
	return true;
}
static void __tts_state_changed_cb(tts_h tts, tts_state_e previous, tts_state_e current, void* user_data)
{
	g_current_state = current;
}
static void __tts_utterance_started_cb(tts_h tts, int utt_id, void* user_data)
{
	g_utterance_started_cb = true;
}
static void __tts_utterance_completed_cb(tts_h tts, int utt_id, void *user_data)
{
	g_utterance_completed_cb = true;
	g_utt_id = utt_id;
}

static void __tts_error_cb(tts_h tts, int utt_id, tts_error_e reason, void* user_data)
{
}

static void __tts_default_voice_changed_cb(tts_h tts, const char* previous_language, int previous_voice_type, const char* current_language, int current_voice_type, void* user_data)
{
}

static void __tts_screen_reader_changed_cb(tts_h tts, bool is_on, void* user_data)
{
}

static void __tts_engine_changed_cb(tts_h tts, const char* engine_id, const char* language, int voice_type, bool need_credential, void* user_data)
{
}

static void __state_changed_cb_for_destroy_n3(tts_h tts, tts_state_e previous, tts_state_e current, void* user_data)
{
	is_destroyed_hndl = tts_destroy(tts);
	g_current_state = current;
}


static bool __is_state_changed(tts_state_e state, int wait_delay)
{
	int max_count = wait_delay * 10;
	int count = 0;
	while (max_count > count && state != g_current_state) {
		ecore_main_loop_iterate();
		usleep(100000);
		count++;
	}

	if (state != g_current_state) {
		return false;
	}

	return true;
}

/**
 * @testcase		utc_tts_create_p
 * @since_tizen		2.3
 * @description		test whether tts handle is created properly
 */
int utc_tts_create_p(void)
{
	if(g_supported == false){
		assert_eq(is_created_hndl, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_create_n
 * @since_tizen		2.3
 * @description		test whether tts handle is not created with NULL parameter
 */
int utc_tts_create_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_create(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = tts_create(NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;

}

/**
 * @testcase		utc_tts_destroy_p
 * @since_tizen		2.3
 * @description		test whether tts handle is destroyed properly
 */
int utc_tts_destroy_p(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_destroy(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_destroy(g_tts);
	g_tts = NULL;
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_destroy_p2
 * @since_tizen		2.3
 * @description		test whether tts handle is destroyed properly when tts is ready state with deafult mode
 */
int utc_tts_destroy_p2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
	ret = tts_destroy(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_set_mode(g_tts, TTS_MODE_DEFAULT);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_destroy(g_tts);
	g_tts = NULL;
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_destroy_p3
 * @since_tizen		2.3
 * @description		test whether tts handle is destroyed properly when tts is ready state with notification mode
 */
int utc_tts_destroy_p3(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
	ret = tts_destroy(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_set_mode(g_tts, TTS_MODE_NOTIFICATION);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_destroy(g_tts);
	g_tts = NULL;
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_destroy_p4
 * @since_tizen		2.3
 * @description		test whether multiple tts handles are destroyed properly
 */
int utc_tts_destroy_p4(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_destroy(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	tts_h tts = NULL;
	ret = tts_create(&tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_destroy(tts);
	tts = NULL;
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	g_tts = NULL;
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_destroy_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter
 */
int utc_tts_destroy_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_destroy(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = tts_destroy(NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_destroy_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when destroy after handle is already destroyed.
 */
int utc_tts_destroy_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
	ret = tts_destroy(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);
	ret = tts_destroy(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_tts_destroy_n3
 * @since_tizen		2.3
 * @description		test whether function returns error when destroy on callback function.
 */
int utc_tts_destroy_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
	ret = tts_destroy(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = tts_set_state_changed_cb(g_tts, __state_changed_cb_for_destroy_n3, NULL);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	assert_neq(is_destroyed_hndl, TTS_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_tts_set_mode_p
 * @since_tizen		2.3
 * @description		test whether mode is set properly with default mode.
 */
int utc_tts_set_mode_p(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_mode(g_tts, TTS_MODE_DEFAULT);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_set_mode(g_tts, TTS_MODE_DEFAULT);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_mode_p2
 * @since_tizen		2.3
 * @description		test whether mode is set properly with screen reader mode.
 */
int utc_tts_set_mode_p2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_mode(g_tts, TTS_MODE_SCREEN_READER);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_set_mode(g_tts, TTS_MODE_SCREEN_READER);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_mode_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_set_mode_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_mode(NULL, TTS_MODE_DEFAULT);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = tts_set_mode(NULL, TTS_MODE_DEFAULT);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_mode_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts is ready state, not create state.
 */
int utc_tts_set_mode_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_mode(NULL, TTS_MODE_DEFAULT);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_set_mode(g_tts, TTS_MODE_DEFAULT);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_mode_n3
 * @since_tizen		2.3
 * @description		test whether function returns error with abnormal mode as 100.
 */
int utc_tts_set_mode_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_mode(NULL, TTS_MODE_DEFAULT);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_set_mode(g_tts, 100);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_get_mode_p
 * @since_tizen		2.3
 * @description		test whether mode is gotten properly.
 */
int utc_tts_get_mode_p(void)
{
	tts_mode_e mode;
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_get_mode(g_tts, &mode);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_get_mode(g_tts, &mode);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_get_mode_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_get_mode_n(void)
{
	tts_mode_e mode;
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_get_mode(NULL, &mode);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = tts_get_mode(NULL, &mode);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_get_mode(g_tts, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_get_mode_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts is ready state, not create state.
 */
int utc_tts_get_mode_n2(void)
{
	tts_mode_e mode;
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_get_mode(g_tts, &mode);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_get_mode(g_tts, &mode);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_tts_get_speed_range_p
 * @since_tizen		2.3
 * @description		test whether speed range is gotten properly.
 */
int utc_tts_get_speed_range_p(void)
{
	int min;
	int normal;
	int max;
	int ret = TTS_ERROR_NONE;

	if(g_supported == false){
		ret = tts_get_speed_range(g_tts, &min, &normal, &max);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_get_speed_range(g_tts, &min, &normal, &max);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_get_speed_range_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_get_speed_range_n(void)
{
	int min;
	int normal;
	int max;
	int ret = TTS_ERROR_NONE;

	if(g_supported == false){
		ret = tts_get_speed_range(NULL, &min, &normal, &max);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_get_speed_range(g_tts, NULL, NULL, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_get_speed_range(NULL, &min, &normal, &max);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_get_speed_range_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_get_speed_range_n2(void)
{
	int min;
	int normal;
	int max;
	int ret = TTS_ERROR_NONE;

	if(g_supported == false){
		ret = tts_get_speed_range(NULL, &min, &normal, &max);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_get_speed_range(g_tts, &min, &normal, &max);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_tts_prepare_p
 * @since_tizen		2.3
 * @description		test whether tts daemon is prepared properly.
 */
int utc_tts_prepare_p(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_prepare(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
	ecore_main_loop_iterate();
	}

	tts_unprepare(g_tts);

	return 0;
}

/**
 * @testcase		utc_tts_prepare_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_prepare_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_prepare(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = tts_prepare(NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_prepare_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts is ready state, not create state.
 */
int utc_tts_prepare_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_prepare(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_prepare(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	tts_unprepare(g_tts);

	return 0;
}

/**
 * @testcase		utc_tts_prepare_sync_p
 * @since_tizen		7.0
 * @description		test whether tts daemon is prepared properly.
 */
int utc_tts_prepare_sync_p(void)
{
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_prepare_sync(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_prepare_sync(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	assert_eq(true, __is_state_changed(TTS_STATE_READY, 5));
	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_prepare_sync_n
 * @since_tizen		7.0
 * @description		test whether function returns error when tts is not created.
 */
int utc_tts_prepare_sync_n(void)
{
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_prepare_sync(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = tts_prepare_sync(NULL);
	assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_tts_prepare_sync_n2
 * @since_tizen		7.0
 * @description		test whether function returns error when tts is ready state, not create state.
 */
int utc_tts_prepare_sync_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_prepare_sync(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = tts_prepare_sync(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	assert_eq(true, __is_state_changed(TTS_STATE_READY, 5));

	ret = tts_prepare_sync(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_tts_foreach_supported_voices_p
 * @since_tizen		2.3
 * @description		test whether each supported voices are gotten properly.
 */
int utc_tts_foreach_supported_voices_p(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_foreach_supported_voices(g_tts, __tts_supported_voice_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_foreach_supported_voices(g_tts, __tts_supported_voice_cb, NULL);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_foreach_supported_voices_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_foreach_supported_voices_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_foreach_supported_voices(NULL, __tts_supported_voice_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = tts_foreach_supported_voices(NULL, __tts_supported_voice_cb, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_foreach_supported_voices_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_foreach_supported_voices_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_foreach_supported_voices(NULL, __tts_supported_voice_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_foreach_supported_voices(g_tts, __tts_supported_voice_cb, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_foreach_supported_voices_n3
 * @since_tizen		2.3
 * @description		test whether function returns error when callback is NULL
 */
int utc_tts_foreach_supported_voices_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_foreach_supported_voices(NULL, __tts_supported_voice_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_foreach_supported_voices(g_tts, NULL, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_tts_get_default_voice_p
 * @since_tizen		2.3
 * @description		test whether default voice is gotten properly.
 */
int utc_tts_get_default_voice_p(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_get_default_voice(g_tts, &g_language, &g_voice_type);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	free (g_language);
	g_language = NULL;
	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_get_default_voice(g_tts, &g_language, &g_voice_type);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_get_default_voice_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_get_default_voice_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_get_default_voice(NULL, &g_language, &g_voice_type);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	free (g_language);
	g_language = NULL;
	ret = tts_get_default_voice(NULL, &g_language, &g_voice_type);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_get_default_voice_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_get_default_voice_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_get_default_voice(NULL, &g_language, &g_voice_type);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	free (g_language);
	g_language = NULL;
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_get_default_voice(g_tts, &g_language, &g_voice_type);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_get_default_voice_n3
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter as type.
 */
int utc_tts_get_default_voice_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_get_default_voice(NULL, &g_language, &g_voice_type);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	free (g_language);
	g_language = NULL;
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_get_default_voice(g_tts, &g_language, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_tts_get_max_text_size_p
 * @since_tizen		2.3
 * @description		test whether max text size is gotten properly.
 */
int utc_tts_get_max_text_size_p(void)
{
	unsigned int size;
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_get_max_text_size(g_tts, &size);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_get_max_text_size(g_tts, &size);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_get_max_text_size_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_get_max_text_size_n(void)
{
	unsigned int size;
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_get_max_text_size(NULL, &size);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_get_max_text_size(g_tts, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_get_max_text_size(NULL, &size);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_get_max_text_size_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_get_max_text_size_n2(void)
{
	unsigned int size;
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_get_max_text_size(NULL, &size);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_get_max_text_size(g_tts, &size);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_get_max_text_size_n3
 * @since_tizen		2.3
 * @description		test whether function returns error when tts is in create state.
 */
int utc_tts_get_max_text_size_n3(void)
{
	unsigned int size;
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_get_max_text_size(NULL, &size);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_get_max_text_size(g_tts, &size);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_tts_get_state_p
 * @since_tizen		2.3
 * @description		test whether state is gotten properly in create state.
 */
int utc_tts_get_state_p(void)
{
	tts_state_e state;
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_get_state(g_tts, &state);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_get_state(g_tts, &state);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_get_state_p2
 * @since_tizen		2.3
 * @description		test whether state is gotten properly in ready state.
 */
int utc_tts_get_state_p2(void)
{
	tts_state_e state;
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_get_state(g_tts, &state);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_get_state(g_tts, &state);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_get_state_p3
 * @since_tizen		2.3
 * @description		test whether state is gotten properly in play state.
 */
int utc_tts_get_state_p3(void)
{
	tts_state_e state;
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_get_state(g_tts, &state);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_play(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_PLAYING!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_get_state(g_tts, &state);
	assert_eq(ret, TTS_ERROR_NONE);

	tts_stop(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_get_state_p4
 * @since_tizen		2.3
 * @description		test whether state is gotten properly in pause state.
 */
int utc_tts_get_state_p4(void)
{
	tts_state_e state;
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_get_state(g_tts, &state);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_play(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_PLAYING!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_pause(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_PAUSED!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_get_state(g_tts, &state);
	assert_eq(ret, TTS_ERROR_NONE);

	tts_stop(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_get_state_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_get_state_n(void)
{
	tts_state_e state;
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_get_state(NULL, &state);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_get_state(g_tts, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_get_state(NULL, &state);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_get_state_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_get_state_n2(void)
{
	tts_state_e state;
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_get_state(g_tts, &state);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_get_state(g_tts, &state);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_tts_add_text_p
 * @since_tizen		2.3
 * @description		test whether text is added properly.
 */
int utc_tts_add_text_p(void)
{
	int utt_id;
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_add_text(g_tts, "1 2 3", g_language, g_voice_type, TTS_SPEED_AUTO, &utt_id);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_add_text(g_tts, "1 2 3", g_language, g_voice_type, TTS_SPEED_AUTO, &utt_id);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_add_text_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_add_text_n(void)
{
	int utt_id;
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_add_text(NULL, "1 2 3", g_language, g_voice_type, TTS_SPEED_AUTO, &utt_id);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_add_text(g_tts, "1 2 3", g_language, g_voice_type, TTS_SPEED_AUTO, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_add_text(NULL, "1 2 3", g_language, g_voice_type, TTS_SPEED_AUTO, &utt_id);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_add_text_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_add_text_n2(void)
{
	int utt_id;
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_add_text(NULL, "1 2 3", g_language, g_voice_type, TTS_SPEED_AUTO, &utt_id);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_add_text(g_tts, "1 2 3", g_language, g_voice_type, TTS_SPEED_AUTO, &utt_id);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_add_text_n3
 * @since_tizen		2.3
 * @description		test whether function returns error when tts is in create state.
 */
int utc_tts_add_text_n3(void)
{
	int utt_id;
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_add_text(NULL, "1 2 3", g_language, g_voice_type, TTS_SPEED_AUTO, &utt_id);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_add_text(g_tts, "1 2 3", g_language, g_voice_type, TTS_SPEED_AUTO, &utt_id);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_add_text_n4
 * @since_tizen		2.3
 * @description		test whether function returns error when text is over max text size.
 */
int utc_tts_add_text_n4(void)
{
	int utt_id;
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_add_text(g_tts, "1 2 3", g_language, g_voice_type, TTS_SPEED_AUTO, &utt_id);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_add_text(g_tts, g_text, g_language, g_voice_type, TTS_SPEED_AUTO, &utt_id);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_add_text_n5
 * @since_tizen		2.3
 * @description		test whether function returns error when tts speed is abnormal.
 */
int utc_tts_add_text_n5(void)
{
	int utt_id;
	int speed = -1;
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_add_text(g_tts, "1 2 3", g_language, g_voice_type, TTS_SPEED_AUTO, &utt_id);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_add_text(g_tts, "1 2 3", g_language, g_voice_type, speed, &utt_id);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_tts_play_p
 * @since_tizen		2.3
 * @description		test whether tts is played properly.
 */
int utc_tts_play_p(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_play(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_play(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_PLAYING!=g_current_state){
		ecore_main_loop_iterate();
	}

	tts_stop(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_play_p2
 * @since_tizen		2.3
 * @description		test whether tts is played all text properly.
 */
int utc_tts_play_p2(void)
{
	int utt_id;
	int ret = TTS_ERROR_NONE;

	if(g_supported == false){
		ret = tts_play(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_set_utterance_started_cb(g_tts, __tts_utterance_started_cb, NULL);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_set_utterance_completed_cb(g_tts, __tts_utterance_completed_cb, NULL);
	assert_eq(ret, TTS_ERROR_NONE);

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	g_utterance_completed_cb = false;

	ret = tts_add_text(g_tts, "1 2 3", g_language, g_voice_type, TTS_SPEED_AUTO, &utt_id);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_play(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_PLAYING!=g_current_state){
		ecore_main_loop_iterate();
	}

	while(true != g_utterance_completed_cb) {
		ecore_main_loop_iterate();
	}

	tts_stop(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_play_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_play_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_play(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_play(NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_play_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_play_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_play(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_play(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_play_n3
 * @since_tizen		2.3
 * @description		test whether function returns error when tts is in create state.
 */
int utc_tts_play_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_play(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_play(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_pause_p
 * @since_tizen		2.3
 * @description		test whether tts is paused properly.
 */
int utc_tts_pause_p(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_pause(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_play(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_PLAYING!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_pause(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_PAUSED!=g_current_state){
		ecore_main_loop_iterate();
	}

	tts_stop(g_tts);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	tts_unprepare(g_tts);

	return 0;
}

/**
 * @testcase		utc_tts_pause_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_pause_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_pause(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_pause(NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_pause_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_pause_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_pause(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_pause(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_pause_n3
 * @since_tizen		2.3
 * @description		test whether function returns error when tts is in create state.
 */
int utc_tts_pause_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_pause(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_pause(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_stop_p
 * @since_tizen		2.3
 * @description		test whether tts is stopped properly.
 */
int utc_tts_stop_p(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_stop(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_play(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_PLAYING!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_stop(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	tts_unprepare(g_tts);

	return 0;
}

/**
 * @testcase		utc_tts_stop_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_stop_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_stop(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_stop(NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_stop_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_stop_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_stop(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_stop(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_stop_n3
 * @since_tizen		2.3
 * @description		test whether function returns error when tts is in create state.
 */
int utc_tts_stop_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_stop(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_stop(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_repeat_p
 * @since_tizen		5.0
 * @description		test whether tts is repeated properly.
 */
int utc_tts_repeat_p(void)
{
	int ret = TTS_ERROR_NONE;
	char* text_repeat = NULL;
	int utt_id = -1;

	if (g_supported == false){
		ret = tts_repeat(g_tts, &text_repeat, &utt_id);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_set_utterance_started_cb(g_tts, __tts_utterance_started_cb, NULL);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_set_utterance_completed_cb(g_tts, __tts_utterance_completed_cb, NULL);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY != g_current_state) {
		ecore_main_loop_iterate();
	}

	g_utterance_completed_cb = false;

	ret = tts_add_text(g_tts, "repeat success", g_language, g_voice_type, TTS_SPEED_AUTO, &utt_id);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_play(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_PLAYING != g_current_state) {
		ecore_main_loop_iterate();
	}

	while(true != g_utterance_completed_cb) {
		ecore_main_loop_iterate();
	}

	ret = tts_stop(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY != g_current_state) {
		ecore_main_loop_iterate();
	}

	g_utterance_completed_cb = false;

	ret = tts_repeat(g_tts, &text_repeat, &utt_id);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = strncmp(text_repeat, "repeat success", strlen(text_repeat));
	assert_eq(ret, 0);

	while(TTS_STATE_PLAYING != g_current_state) {
		ecore_main_loop_iterate();
	}

	while(true != g_utterance_completed_cb) {
		ecore_main_loop_iterate();
	}

	assert_eq(utt_id, g_utt_id);

	ret = tts_stop(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY != g_current_state) {
		ecore_main_loop_iterate();
	}

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_repeat_n
 * @since_tizen		5.0
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_repeat_n(void)
{
	int ret = TTS_ERROR_NONE;
	char* text_repeat = NULL;
	int utt_id = -1;

	if (g_supported == false){
		ret = tts_repeat(g_tts, NULL, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_repeat(g_tts, NULL, NULL);
	assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);

	ret = tts_repeat(NULL, &text_repeat, &utt_id);
	assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_tts_repeat_n2
 * @since_tizen		5.0
 * @description		test whether function returns error with invalid state.
 */
int utc_tts_repeat_n2(void)
{
	int ret = TTS_ERROR_NONE;
	char* text_repeat = NULL;
	int utt_id = -1;

	if (g_supported == false){
		ret = tts_repeat(g_tts, &text_repeat, &utt_id);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_repeat(g_tts, &text_repeat, &utt_id);
	assert_eq(ret, TTS_ERROR_INVALID_STATE);

	return 0;
}

/**
 * @testcase		utc_tts_repeat_n3
 * @since_tizen		5.0
 * @description		test whether function returns error with operation failed when there is no previous text.
 */
int utc_tts_repeat_n3(void)
{
	int ret = TTS_ERROR_NONE;
	char* text_repeat = NULL;
	int utt_id = -1;

	if (g_supported == false){
		ret = tts_repeat(g_tts, &text_repeat, &utt_id);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY != g_current_state) {
		ecore_main_loop_iterate();
	}

	ret = tts_repeat(g_tts, &text_repeat, &utt_id);
	assert_eq(ret, TTS_ERROR_OPERATION_FAILED);

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unprepare_p
 * @since_tizen		2.3
 * @description		test whether tts is unprepared properly.
 */
int utc_tts_unprepare_p(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unprepare(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unprepare_p2
 * @since_tizen		2.3
 * @description		test whether tts is unprepared properly when tts is in notification mode.
 */
int utc_tts_unprepare_p2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unprepare(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_set_mode(g_tts, TTS_MODE_NOTIFICATION);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unprepare_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_unprepare_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unprepare(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_unprepare(NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unprepare_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_unprepare_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unprepare(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);


	return 0;
}

/**
 * @testcase		utc_tts_unprepare_n3
 * @since_tizen		2.3
 * @description		test whether function returns error when tts is in create state.
 */
int utc_tts_unprepare_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unprepare(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_tts_set_state_changed_cb_p
 * @since_tizen		2.3
 * @description		test whether state_changed callback function is set properly.
 */
int utc_tts_set_state_changed_cb_p(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_state_changed_cb(g_tts, __tts_state_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_set_state_changed_cb(g_tts, __tts_state_changed_cb, NULL);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_state_changed_cb_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_set_state_changed_cb_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_state_changed_cb(NULL, __tts_state_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_set_state_changed_cb(g_tts, NULL, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_set_state_changed_cb(NULL, __tts_state_changed_cb, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_state_changed_cb_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_set_state_changed_cb_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_state_changed_cb(NULL, __tts_state_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_set_state_changed_cb(g_tts, __tts_state_changed_cb, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_state_changed_cb_n3
 * @since_tizen		2.3
 * @description		test whether function returns error when tts is not in create state.
 */
int utc_tts_set_state_changed_cb_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_state_changed_cb(NULL, __tts_state_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_set_state_changed_cb(g_tts, __tts_state_changed_cb, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_tts_unset_state_changed_cb_p
 * @since_tizen		2.3
 * @description		test whether state_changed callback function is unset properly.
 */
int utc_tts_unset_state_changed_cb_p(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_state_changed_cb(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_unset_state_changed_cb(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unset_state_changed_cb_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_unset_state_changed_cb_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_state_changed_cb(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = tts_unset_state_changed_cb(NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unset_state_changed_cb_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_unset_state_changed_cb_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_state_changed_cb(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_unset_state_changed_cb(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unset_state_changed_cb_n3
 * @since_tizen		2.3
 * @description		test whether function returns error when tts is not in create state.
 */
int utc_tts_unset_state_changed_cb_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_state_changed_cb(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_unset_state_changed_cb(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_tts_set_utterance_started_cb_p
 * @since_tizen		2.3
 * @description		test whether utterance_started callback function is set properly.
 */
int utc_tts_set_utterance_started_cb_p(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_utterance_started_cb(g_tts, __tts_utterance_started_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_set_utterance_started_cb(g_tts, __tts_utterance_started_cb, NULL);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_utterance_started_cb_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_set_utterance_started_cb_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_utterance_started_cb(NULL, __tts_utterance_started_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_set_utterance_started_cb(g_tts, NULL, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_set_utterance_started_cb(NULL, __tts_utterance_started_cb, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_utterance_started_cb_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_set_utterance_started_cb_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_utterance_started_cb(NULL, __tts_utterance_started_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_set_utterance_started_cb(g_tts, __tts_utterance_started_cb, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_utterance_started_cb_n3
 * @since_tizen		2.3
 * @description		test whether function returns error when tts is not in create state.
 */
int utc_tts_set_utterance_started_cb_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_utterance_started_cb(NULL, __tts_utterance_started_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_set_utterance_started_cb(g_tts, __tts_utterance_started_cb, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unset_utterance_started_cb_p
 * @since_tizen		2.3
 * @description		test whether utterance_started callback function is unset properly.
 */
int utc_tts_unset_utterance_started_cb_p(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_utterance_started_cb(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_unset_utterance_started_cb(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unset_utterance_started_cb_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_unset_utterance_started_cb_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_utterance_started_cb(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = tts_unset_utterance_started_cb(NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unset_utterance_started_cb_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_unset_utterance_started_cb_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_utterance_started_cb(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_unset_utterance_started_cb(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unset_utterance_started_cb_n3
 * @since_tizen		2.3
 * @description		test whether function returns error when tts is not in create state.
 */
int utc_tts_unset_utterance_started_cb_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_utterance_started_cb(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_unset_utterance_started_cb(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_utterance_completed_cb_p
 * @since_tizen		2.3
 * @description		test whether utterance_completed callback function is set properly.
 */
int utc_tts_set_utterance_completed_cb_p(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_utterance_completed_cb(g_tts, __tts_utterance_completed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_set_utterance_completed_cb(g_tts, __tts_utterance_completed_cb, NULL);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_utterance_completed_cb_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_set_utterance_completed_cb_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_utterance_completed_cb(NULL, __tts_utterance_completed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_set_utterance_completed_cb(g_tts, NULL, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_set_utterance_completed_cb(NULL, __tts_utterance_completed_cb, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_utterance_completed_cb_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_set_utterance_completed_cb_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_utterance_completed_cb(NULL, __tts_utterance_completed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_set_utterance_completed_cb(g_tts, __tts_utterance_completed_cb, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_utterance_completed_cb_n3
 * @since_tizen		2.3
 * @description		test whether function returns error when tts is not in create state.
 */
int utc_tts_set_utterance_completed_cb_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_utterance_completed_cb(NULL, __tts_utterance_completed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_set_utterance_completed_cb(g_tts, __tts_utterance_completed_cb, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unset_utterance_completed_cb_p
 * @since_tizen		2.3
 * @description		test whether utterance_completed callback function is unset properly.
 */
int utc_tts_unset_utterance_completed_cb_p(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_utterance_completed_cb(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_unset_utterance_completed_cb(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unset_utterance_completed_cb_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_unset_utterance_completed_cb_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_utterance_completed_cb(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = tts_unset_utterance_completed_cb(NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unset_utterance_completed_cb_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_unset_utterance_completed_cb_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_utterance_completed_cb(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_unset_utterance_completed_cb(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unset_utterance_completed_cb_n3
 * @since_tizen		2.3
 * @description		test whether function returns error when tts is in create state.
 */
int utc_tts_unset_utterance_completed_cb_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_utterance_completed_cb(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_unset_utterance_completed_cb(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_error_cb_p
 * @since_tizen		2.3
 * @description		test whether error callback function is set properly.
 */
int utc_tts_set_error_cb_p(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_error_cb(g_tts, __tts_error_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_set_error_cb(g_tts, __tts_error_cb, NULL);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_error_cb_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_set_error_cb_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_error_cb(NULL, __tts_error_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_set_error_cb(g_tts, NULL, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_set_error_cb(NULL, __tts_error_cb, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_error_cb_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_set_error_cb_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_error_cb(NULL, __tts_error_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_set_error_cb(g_tts, __tts_error_cb, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_error_cb_n3
 * @since_tizen		2.3
 * @description		test whether function returns error when tts is not in create state.
 */
int utc_tts_set_error_cb_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_error_cb(NULL, __tts_error_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_set_error_cb(g_tts, __tts_error_cb, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);


	return 0;
}

/**
 * @testcase		utc_tts_unset_error_cb_p
 * @since_tizen		2.3
 * @description		test whether error callback function is unset properly.
 */
int utc_tts_unset_error_cb_p(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_error_cb(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_unset_error_cb(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unset_error_cb_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_unset_error_cb_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_error_cb(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = tts_unset_error_cb(NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unset_error_cb_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_unset_error_cb_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_error_cb(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_unset_error_cb(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unset_error_cb_n3
 * @since_tizen		2.3
 * @description		test whether function returns error when tts is not in create state.
 */
int utc_tts_unset_error_cb_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_error_cb(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_unset_error_cb(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_default_voice_changed_cb_p
 * @since_tizen		2.3
 * @description		test whether default_voice_changed callback function is set properly.
 */
int utc_tts_set_default_voice_changed_cb_p(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_default_voice_changed_cb(g_tts, __tts_default_voice_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_set_default_voice_changed_cb(g_tts, __tts_default_voice_changed_cb, NULL);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_default_voice_changed_cb_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_set_default_voice_changed_cb_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_default_voice_changed_cb(NULL, __tts_default_voice_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_set_default_voice_changed_cb(g_tts, NULL, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_set_default_voice_changed_cb(NULL, __tts_default_voice_changed_cb, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_default_voice_changed_cb_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_set_default_voice_changed_cb_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_default_voice_changed_cb(NULL, __tts_default_voice_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_set_default_voice_changed_cb(g_tts, __tts_default_voice_changed_cb, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_default_voice_changed_cb_n3
 * @since_tizen		2.3
 * @description		test whether function returns error when tts is not in create state.
 */
int utc_tts_set_default_voice_changed_cb_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_set_default_voice_changed_cb(NULL, __tts_default_voice_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_set_default_voice_changed_cb(g_tts, __tts_default_voice_changed_cb, NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unset_default_voice_changed_cb_p
 * @since_tizen		2.3
 * @description		test whether default_voice_changed callback function is unset properly.
 */
int utc_tts_unset_default_voice_changed_cb_p(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_default_voice_changed_cb(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);
	ret = tts_unset_default_voice_changed_cb(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unset_default_voice_changed_cb_n
 * @since_tizen		2.3
 * @description		test whether function returns error with NULL parameter.
 */
int utc_tts_unset_default_voice_changed_cb_n(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_default_voice_changed_cb(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = tts_unset_default_voice_changed_cb(NULL);
	assert_neq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unset_default_voice_changed_cb_n2
 * @since_tizen		2.3
 * @description		test whether function returns error when tts handle is already destroyed.
 */
int utc_tts_unset_default_voice_changed_cb_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_default_voice_changed_cb(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_destroy(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_unset_default_voice_changed_cb(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_create(&g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_unset_default_voice_changed_cb_n3
 * @since_tizen		2.3
 * @description		test whether function returns error when tts is not in create state.
 */
int utc_tts_unset_default_voice_changed_cb_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if(g_supported == false){
		ret = tts_unset_default_voice_changed_cb(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY!=g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_unset_default_voice_changed_cb(g_tts);
	assert_neq(ret, TTS_ERROR_NONE);

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_tts_get_error_message_p
 * @since_tizen		3.0
 * @description		Positive UTC for get error message
 */
int utc_tts_get_error_message_p(void)
{
	char* error_message = NULL;
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_get_error_message(g_tts, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_get_error_message(g_tts, &error_message);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_get_error_message_n
 * @since_tizen		3.0
 * @description		Negative UTC for get error message (invalid parameter)
 */
int utc_tts_get_error_message_n(void)
{
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_get_error_message(g_tts, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_get_error_message(g_tts, NULL);
	assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_tts_get_error_message_n1
 * @since_tizen		3.0
 * @description		Negative UTC for get error message (invalid parameter)
 */
int utc_tts_get_error_message_n1(void)
{
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_get_error_message(g_tts, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_get_error_message(NULL, NULL);
	assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase		utc_tts_get_private_data_p
 * @since_tizen		3.0
 * @description		Positive UTC for get private data
 */
int utc_tts_get_private_data_p(void)
{
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_get_private_data(g_tts, NULL, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	tts_prepare(g_tts);

	while (TTS_STATE_READY != g_current_state) {
		ecore_main_loop_iterate();
	}

	char *data = NULL;
	ret = tts_get_private_data(g_tts, "version", &data);
	assert_eq(ret, TTS_ERROR_NONE);
	free(data);

	tts_unprepare(g_tts);

	return 0;
}

/**
 * @testcase		utc_tts_get_private_data_n
 * @since_tizen		3.0
 * @description		Negative UTC for get private data (invalid parameter)
 */
int utc_tts_get_private_data_n(void)
{
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_get_private_data(g_tts, NULL, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_get_private_data(NULL, NULL, NULL);
	assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_tts_get_private_data_n1
 * @since_tizen		3.0
 * @description		Negative UTC for get private data (invalid parameter)
 */
int utc_tts_get_private_data_n1(void)
{
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_get_private_data(g_tts, NULL, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_get_private_data(g_tts, "version", NULL);
	assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_tts_get_private_data_n2
 * @since_tizen		3.0
 * @description		Negative UTC for get private data (invalid state)
 */
int utc_tts_get_private_data_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_get_private_data(g_tts, NULL, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	char* data = NULL;
	ret = tts_get_private_data(g_tts, "version", &data);
	assert_eq(ret, TTS_ERROR_INVALID_STATE);

	return 0;
}

/**
 * @testcase		utc_tts_get_private_data_n3
 * @since_tizen		3.0
 * @description		Negative UTC for get private data (invalid parameter)
 */
int utc_tts_get_private_data_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_get_private_data(g_tts, NULL, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	char* data = NULL;
	ret = tts_get_private_data(g_tts, NULL, &data);
	assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_tts_set_private_data_p
 * @since_tizen		3.0
 * @description		Positive UTC for set private data
 */
int utc_tts_set_private_data_p(void)
{
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_set_private_data(g_tts, NULL, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while (TTS_STATE_READY != g_current_state) {
		ecore_main_loop_iterate();
	}

	ret = tts_set_private_data(g_tts, "version", "2.0");
	assert_eq(ret, TTS_ERROR_NONE);

	tts_unprepare(g_tts);

	return 0;
}

/**
 * @testcase		utc_tts_set_private_data_n
 * @since_tizen		3.0
 * @description		Negative UTC for set private data (invalid parameter)
 */
int utc_tts_set_private_data_n(void)
{
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_set_private_data(g_tts, NULL, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_set_private_data(NULL, NULL, NULL);
	assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_tts_set_private_data_n1
 * @since_tizen		3.0
 * @description		Negative UTC for set private data (invalid parameter)
 */
int utc_tts_set_private_data_n1(void)
{
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_set_private_data(g_tts, NULL, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_set_private_data(g_tts, "version", NULL);
	assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_tts_set_private_data_n2
 * @since_tizen		3.0
 * @description		Negative UTC for set private data (invalid state)
 */
int utc_tts_set_private_data_n2(void)
{
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_set_private_data(g_tts, NULL, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_set_private_data(g_tts, "version", "2.0");
	assert_eq(ret, TTS_ERROR_INVALID_STATE);

	return 0;
}

/**
 * @testcase		utc_tts_set_private_data_n3
 * @since_tizen		3.0
 * @description		Negative UTC for set private data (invalid parameter)
 */
int utc_tts_set_private_data_n3(void)
{
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_set_private_data(g_tts, NULL, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while (TTS_STATE_READY != g_current_state) {
		ecore_main_loop_iterate();
	}

	ret = tts_set_private_data(g_tts, "EnableServerTTS", "2.0");
	assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);

	ret = tts_set_private_data(g_tts, NULL, "2.0");
	assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_tts_set_credential_p
 * @since_tizen		3.0
 * @description		Positive UTC for set credential
 */
int utc_tts_set_credential_p(void)
{
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_set_credential(g_tts, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_set_credential(g_tts, "test");
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_set_credential_n
 * @since_tizen		3.0
 * @description		Negative UTC for set credential (invalid parameter)
 */
int utc_tts_set_credential_n(void)
{
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_set_credential(g_tts, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_set_credential(NULL, NULL);
	assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_tts_set_credential_n1
 * @since_tizen		3.0
 * @description		Negative UTC for set credential (invalid parameter)
 */
int utc_tts_set_credential_n1(void)
{
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_set_credential(g_tts, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_set_credential(g_tts, NULL);
	assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_tts_set_credential_n2
 * @since_tizen		3.0
 * @description		Negative UTC for set credential (invalid state)
 */
int utc_tts_set_credential_n2(void)
{
	int utt_id;
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_set_credential(g_tts, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_prepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY != g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_add_text(g_tts, "1 2 3", g_language, g_voice_type, TTS_SPEED_AUTO, &utt_id);
	assert_eq(ret, TTS_ERROR_NONE);

	ret = tts_play(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while (TTS_STATE_PLAYING != g_current_state) {
		ecore_main_loop_iterate();
	}

	char* credential = "test";
	ret = tts_set_credential(g_tts, credential);
	assert_eq(ret, TTS_ERROR_INVALID_STATE);

	ret = tts_stop(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	while(TTS_STATE_READY != g_current_state){
		ecore_main_loop_iterate();
	}

	ret = tts_unprepare(g_tts);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_check_screen_reader_on_p
 * @since_tizen		6.5
 * @description		Positive UTC for checking screen reader on
 */
int utc_tts_check_screen_reader_on_p(void)
{
	int ret = TTS_ERROR_NONE;
	bool is_on = false;
	if (g_supported == false) {
		ret = tts_check_screen_reader_on(g_tts, &is_on);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_check_screen_reader_on(g_tts, &is_on);
	assert_eq(ret, TTS_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_tts_check_screen_reader_on_n
 * @since_tizen		6.5
 * @description		Negative UTC for checking screen reader on (invalid parameter)
 */
int utc_tts_check_screen_reader_on_n(void)
{
	int ret = TTS_ERROR_NONE;
	if (g_supported == false) {
		ret = tts_check_screen_reader_on(g_tts, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(is_created_hndl, TTS_ERROR_NONE);

	ret = tts_check_screen_reader_on(NULL, NULL);
	assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_tts_set_screen_reader_changed_cb_p
 * @since_tizen		6.5
 * @description		Positive UTC for set screen reader changed callback
 */
int utc_tts_set_screen_reader_changed_cb_p(void)
{
	int ret = TTS_ERROR_NONE;

	if (g_supported == false) {
		ret = tts_set_screen_reader_changed_cb(g_tts, __tts_screen_reader_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(is_created_hndl, TTS_ERROR_NONE);
		ret = tts_set_screen_reader_changed_cb(g_tts, __tts_screen_reader_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NONE);

		ret = tts_unset_screen_reader_changed_cb(g_tts);
		assert_eq(ret, TTS_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_tts_set_screen_reader_changed_cb_n
 * @since_tizen		6.5
 * @description		Negative UTC for set screen reader changed callback (Invalid handle)
 */
int utc_tts_set_screen_reader_changed_cb_n(void)
{
	int ret = TTS_ERROR_NONE;

	if (g_supported == false) {
		ret = tts_set_screen_reader_changed_cb(NULL, __tts_screen_reader_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
	} else {
		ret = tts_set_screen_reader_changed_cb(NULL, __tts_screen_reader_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_tts_set_screen_reader_changed_cb_n1
 * @since_tizen		6.5
 * @description		Negative UTC for set screen reader changed callback (Invalid parameter)
 */
int utc_tts_set_screen_reader_changed_cb_n1(void)
{
	int ret = TTS_ERROR_NONE;

	if (g_supported == false) {
		ret = tts_set_screen_reader_changed_cb(g_tts, NULL, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
	} else {
		ret = tts_set_screen_reader_changed_cb(g_tts, NULL, NULL);
		assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_tts_set_screen_reader_changed_cb_n2
 * @since_tizen		6.5
 * @description		Negative UTC for set screen reader changed callback (Invalid state)
 */
int utc_tts_set_screen_reader_changed_cb_n2(void)
{
	int ret = TTS_ERROR_NONE;

	if (g_supported == false) {
		ret = tts_set_screen_reader_changed_cb(NULL, __tts_screen_reader_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(is_created_hndl, TTS_ERROR_NONE);

		ret = tts_prepare(g_tts);
		assert_eq(ret, TTS_ERROR_NONE);

		while (TTS_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = tts_set_screen_reader_changed_cb(g_tts, __tts_screen_reader_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_INVALID_STATE);

		ret = tts_unprepare(g_tts);
		assert_eq(ret, TTS_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_tts_unset_screen_reader_changed_cb_p
 * @since_tizen		6.5
 * @description		Positive UTC for unset screen reader changed callback
 */
int utc_tts_unset_screen_reader_changed_cb_p(void)
{
	int ret = TTS_ERROR_NONE;

	if (g_supported == false) {
		ret = tts_unset_screen_reader_changed_cb(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(is_created_hndl, TTS_ERROR_NONE);
		ret = tts_set_screen_reader_changed_cb(g_tts, __tts_screen_reader_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NONE);
		ret = tts_unset_screen_reader_changed_cb(g_tts);
		assert_eq(ret, TTS_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_tts_unset_screen_reader_changed_cb_n
 * @since_tizen		6.5
 * @description		Negative UTC for unset screen reader changed callback (Invalid handle)
 */
int utc_tts_unset_screen_reader_changed_cb_n(void)
{
	int ret = TTS_ERROR_NONE;

	if (g_supported == false) {
		ret = tts_unset_screen_reader_changed_cb(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
	} else {
		ret = tts_unset_screen_reader_changed_cb(NULL);
		assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_tts_unset_screen_reader_changed_cb_n1
 * @since_tizen		6.5
 * @description		Negative UTC for unset screen reader changed callback (Invalid state)
 */
int utc_tts_unset_screen_reader_changed_cb_n1(void)
{
	int ret = TTS_ERROR_NONE;

	if (g_supported == false) {
		ret = tts_unset_screen_reader_changed_cb(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq(is_created_hndl, TTS_ERROR_NONE);
		ret = tts_set_screen_reader_changed_cb(g_tts, __tts_screen_reader_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NONE);

		ret = tts_prepare(g_tts);
		assert_eq(ret, TTS_ERROR_NONE);

		while (TTS_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = tts_unset_screen_reader_changed_cb(g_tts);
		assert_eq(ret, TTS_ERROR_INVALID_STATE);

		ret = tts_unprepare(g_tts);
		assert_eq(ret, TTS_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_tts_set_engine_changed_cb_p
 * @since_tizen		3.0
 * @description		Positive UTC for set current engine changed callback
 */
int utc_tts_set_engine_changed_cb_p(void)
{
	int ret = TTS_ERROR_NONE;

	if (g_supported == false) {
		ret = tts_set_engine_changed_cb(g_tts, __tts_engine_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(is_created_hndl, TTS_ERROR_NONE);
		ret = tts_set_engine_changed_cb(g_tts, __tts_engine_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NONE);

		ret = tts_unset_engine_changed_cb(g_tts);
		assert_eq(ret, TTS_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_tts_set_engine_changed_cb_n
 * @since_tizen		3.0
 * @description		Negative UTC for set current engine changed callback (Invalid handle)
 */
int utc_tts_set_engine_changed_cb_n(void)
{
	int ret = TTS_ERROR_NONE;

	if (g_supported == false) {
		ret = tts_set_engine_changed_cb(NULL, __tts_engine_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
	} else {
		ret = tts_set_engine_changed_cb(NULL, __tts_engine_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_tts_set_engine_changed_cb_n1
 * @since_tizen		3.0
 * @description		Negative UTC for set current engine changed callback (Invalid state)
 */
int utc_tts_set_engine_changed_cb_n1(void)
{
	int ret = TTS_ERROR_NONE;

	if (g_supported == false) {
		ret = tts_set_engine_changed_cb(NULL, __tts_engine_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(is_created_hndl, TTS_ERROR_NONE);

		ret = tts_prepare(g_tts);
		assert_eq(ret, TTS_ERROR_NONE);

		while (TTS_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = tts_set_engine_changed_cb(g_tts, __tts_engine_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_INVALID_STATE);

		ret = tts_unprepare(g_tts);
		assert_eq(ret, TTS_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_tts_unset_engine_changed_cb_p
 * @since_tizen		3.0
 * @description		Positive UTC for unset current engine changed callback
 */
int utc_tts_unset_engine_changed_cb_p(void)
{
	int ret = TTS_ERROR_NONE;

	if (g_supported == false) {
		ret = tts_unset_engine_changed_cb(g_tts);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(is_created_hndl, TTS_ERROR_NONE);
		ret = tts_set_engine_changed_cb(g_tts, __tts_engine_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NONE);
		ret = tts_unset_engine_changed_cb(g_tts);
		assert_eq(ret, TTS_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_tts_unset_engine_changed_cb_n
 * @since_tizen		3.0
 * @description		Negative UTC for unset current engine changed callback (Invalid handle)
 */
int utc_tts_unset_engine_changed_cb_n(void)
{
	int ret = TTS_ERROR_NONE;

	if (g_supported == false) {
		ret = tts_unset_engine_changed_cb(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
	} else {
		ret = tts_unset_engine_changed_cb(NULL);
		assert_eq(ret, TTS_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_tts_unset_engine_changed_cb_n1
 * @since_tizen		3.0
 * @description		Negative UTC for unset current engine changed callback (Invalid state)
 */
int utc_tts_unset_engine_changed_cb_n1(void)
{
	int ret = TTS_ERROR_NONE;

	if (g_supported == false) {
		ret = tts_unset_engine_changed_cb(NULL);
		assert_eq(ret, TTS_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq(is_created_hndl, TTS_ERROR_NONE);
		ret = tts_set_engine_changed_cb(g_tts, __tts_engine_changed_cb, NULL);
		assert_eq(ret, TTS_ERROR_NONE);

		ret = tts_prepare(g_tts);
		assert_eq(ret, TTS_ERROR_NONE);

		while (TTS_STATE_READY != g_current_state){
			ecore_main_loop_iterate();
		}

		ret = tts_unset_engine_changed_cb(g_tts);
		assert_eq(ret, TTS_ERROR_INVALID_STATE);

		ret = tts_unprepare(g_tts);
		assert_eq(ret, TTS_ERROR_NONE);
	}

	return 0;
}

