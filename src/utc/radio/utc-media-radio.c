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
#include <media/radio.h>
#include <glib.h>
#include "assert.h"

radio_h radio;
int sRet;
static bool radio_supported = true;
static GMainLoop *g_mainloop = NULL;

static gboolean timeout_func(gpointer data)
{
	fprintf(stderr, "waited 2 seconds\n");
	g_main_loop_quit((GMainLoop *)data);
	return FALSE;
}

static void wait_for_async()
{
	GMainContext *context = g_main_context_new();
	GSource *source = g_timeout_source_new(2000);

	/* attach source to context */
	g_source_attach(source, context);

	g_mainloop = g_main_loop_new(context, FALSE);

	/* set the callback for this source */
	g_source_set_callback(source, timeout_func, g_mainloop, NULL);

	g_main_loop_run(g_mainloop);

	/* after attaching with the GSource, destroy() is needed */
	g_source_destroy(source);

	/* unref the last reference we got for GSource */
	g_source_unref(source);

	/* main loop should be destroyed before unref the context */
	g_main_loop_unref(g_mainloop);
	g_main_context_unref(context);
}

static void radio_completed_cb(int frequency, void *data)
{

}

static void radio_interrupt_cb(radio_interrupted_code_e code, void *data)
{

}

/**
 * @function		utc_media_radio_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_radio_startup(void)
{
	system_info_get_platform_bool("http://tizen.org/feature/fmradio", &radio_supported);
	sRet = radio_create(&radio);
}

/**
 * @function		utc_media_radio_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_radio_cleanup(void)
{
	if (radio) {
		radio_destroy(radio);
		radio = NULL;
	}
}

/**
 * @testcase		utc_media_radio_get_state_p
 * @since_tizen		2.3
 * @description		Gets the radio's current state.
 */
int utc_media_radio_get_state_p(void)
{
	int ret;
	radio_state_e state;

	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_get_state(radio, &state);
		assert_eq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_get_state(radio, &state);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_media_radio_get_state_n
 * @since_tizen		2.3
 * @description		Gets the radio's current state with invalid parameter.
 */
int utc_media_radio_get_state_n(void)
{
	int ret;
	radio_state_e state;

	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_get_state(NULL, &state);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
	} else {
		ret = radio_get_state(NULL, &state);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_start_p
 * @since_tizen		2.3
 * @description		Starts playing the radio.
 */
int utc_media_radio_start_p(void)
{
	int ret;

	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_start(radio);
		assert_eq(ret, RADIO_ERROR_NONE);
		ret = radio_stop(radio);
		assert_eq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_start(radio);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_start_n
 * @since_tizen		2.3
 * @description		Starts playing the radio with invalid parameter.
 */
int utc_media_radio_start_n(void)
{
	int ret;

	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_start(NULL);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
	} else {
		ret = radio_start(NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_set_frequency_p
 * @since_tizen		2.3
 * @description		Sets the radio frequency.
 */
int utc_media_radio_set_frequency_p(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_set_frequency(radio, 91900);
		assert_eq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_set_frequency(radio, 91900);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_set_frequency_n
 * @since_tizen		2.3
 * @description		Sets the radio frequency with invalid parameter.
 */
int utc_media_radio_set_frequency_n(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_set_frequency(radio, 100);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
	} else {
		ret = radio_set_frequency(radio, 100);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_get_frequency_p
 * @since_tizen		2.3
 * @description		Gets the current frequency of the radio.
 */
int utc_media_radio_get_frequency_p(void)
{
	int ret;
	int frequency;

	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_get_frequency(radio, &frequency);
		assert_eq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_get_frequency(radio, &frequency);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_get_frequency_n
 * @since_tizen		2.3
 * @description		Gets the current frequency of the radio with invalid parameter.
 */
int utc_media_radio_get_frequency_n(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_get_frequency(NULL, NULL);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
	} else {
		ret = radio_get_frequency(NULL, NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);

	}
	return 0;
}

/**
 * @testcase		utc_media_radio_seek_up_p
 * @since_tizen		2.3
 * @description		Seeks up the effective frequency of the radio, asynchronously.
 */
int utc_media_radio_seek_up_p(void)
{
	int ret;

	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_start(radio);
		assert_eq(ret, RADIO_ERROR_NONE);
		ret = radio_seek_up(radio, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_NONE);
		wait_for_async();
		ret = radio_stop(radio);
		assert_eq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_seek_up(radio, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_media_radio_seek_up_n
 * @since_tizen		2.3
 * @description		Seeks up the effective frequency of the radio, asynchronously with invalid parameter.
 */
int utc_media_radio_seek_up_n(void)
{
	int ret;
	if (radio_supported) {
		ret = radio_start(radio);
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_seek_up(NULL, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
		ret = radio_stop(radio);
		assert_eq(sRet, RADIO_ERROR_NONE);
	} else {
		ret = radio_seek_up(NULL, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_seek_down_p
 * @since_tizen		2.3
 * @description		Seeks down the effective frequency of the radio, asynchronously.
 */
int utc_media_radio_seek_down_p(void)
{
	int ret;

	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_start(radio);
		assert_eq(ret, RADIO_ERROR_NONE);
		ret = radio_seek_down(radio, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_NONE);
		wait_for_async();
		ret = radio_stop(radio);
		assert_eq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_seek_down(radio, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_seek_down_n
 * @since_tizen		2.3
 * @description		Seeks down the effective frequency of the radio, asynchronously with invalid parameter.
 */
int utc_media_radio_seek_down_n(void)
{
	int ret;

	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_start(radio);
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_seek_down(NULL, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
		ret = radio_stop(radio);
		assert_eq(sRet, RADIO_ERROR_NONE);
	} else {
		ret = radio_seek_down(radio, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_media_radio_scan_start_p
 * @since_tizen		2.3
 * @description		Starts scanning radio signals, asynchronously
 */
int utc_media_radio_scan_start_p(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_scan_start(radio, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_NONE);
		radio_scan_stop(radio, NULL, NULL);
	} else {
		radio_stop(radio);
		ret = radio_scan_start(radio, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_scan_start_n
 * @since_tizen		2.3
 * @description		Starts scanning radio signals, asynchronously with invalid parameter
 */
int utc_media_radio_scan_start_n(void)
{
	int ret;

	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_scan_start(NULL, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
	} else {
		ret = radio_scan_start(NULL, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);

	}
	return 0;
}

/**
 * @testcase		utc_media_radio_scan_stop_p
 * @since_tizen		2.3
 * @description		Stops scanning radio signals, asynchronously.
 */
int utc_media_radio_scan_stop_p(void)
{
	int ret;

	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_scan_start(radio, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_NONE);
		radio_scan_stop(radio, NULL, NULL);
	} else {
		ret = radio_scan_stop(radio, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);

	}
	return 0;
}

/**
 * @testcase		utc_media_radio_scan_stop_n
 * @since_tizen		2.3
 * @description		Stops scanning radio signals, asynchronously with invalid parameter.
 */
int utc_media_radio_scan_stop_n(void)
{
	int ret;

	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_scan_stop(NULL, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
	} else {
		ret = radio_scan_stop(NULL, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);

	}
	return 0;
}

/**
 * @testcase		utc_media_radio_set_mute_p
 * @since_tizen		2.3
 * @description		Sets the radio's mute status.
 */
int utc_media_radio_set_mute_p(void)
{
	int ret;
	bool mute = true;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_set_mute(radio, mute);
		assert_eq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_set_mute(radio, mute);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);

	}
	return 0;
}

/**
 * @testcase		utc_media_radio_set_mute_n
 * @since_tizen		2.3
 * @description		Sets the radio's mute status with invalid parameter.
 */
int utc_media_radio_set_mute_n(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_set_mute(NULL, true);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
	} else {
		ret = radio_set_mute(NULL, true);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_is_muted_p
 * @since_tizen		2.3
 * @description		Gets the radio's mute status.
 */
int utc_media_radio_is_muted_p(void)
{
	int ret;
	bool mute;

	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_is_muted(radio, &mute);
		assert_eq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_is_muted(radio, &mute);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_is_muted_n
 * @since_tizen		2.3
 * @description		Gets the radio's mute status with invalid parameter.
 */
int utc_media_radio_is_muted_n(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_is_muted(NULL, NULL);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
	} else {
		ret = radio_is_muted(NULL, NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_set_scan_completed_cb_p
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked when the scan finishes.
 */
int utc_media_radio_set_scan_completed_cb_p(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_set_scan_completed_cb(radio, radio_completed_cb, NULL);
		assert_eq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_set_scan_completed_cb(radio, radio_completed_cb, NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_set_scan_completed_cb_n
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked when the scan finishes with invalid parameter.
 */
int utc_media_radio_set_scan_completed_cb_n(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_set_scan_completed_cb(radio, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
	} else {
		ret = radio_set_scan_completed_cb(radio, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_unset_scan_completed_cb_p
 * @since_tizen		2.3
 * @description		Unregisters the callback function.
 */
int utc_media_radio_unset_scan_completed_cb_p(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_unset_scan_completed_cb(radio);
		assert_eq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_unset_scan_completed_cb(radio);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_unset_scan_completed_cb_n
 * @since_tizen		2.3
 * @description		Unregisters the callback function with invalid parameter.
 */
int utc_media_radio_unset_scan_completed_cb_n(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_unset_scan_completed_cb(NULL);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
	} else {
		ret = radio_unset_scan_completed_cb(NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_set_interrupted_cb_p
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked when the radio is interrupted.
 */
int utc_media_radio_set_interrupted_cb_p(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_set_interrupted_cb(radio, radio_interrupt_cb, NULL);
		assert_eq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_set_interrupted_cb(radio, radio_interrupt_cb, NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_set_interrupted_cb_n
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked when the radio is interrupted with invalid parameter.
 */
int utc_media_radio_set_interrupted_cb_n(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_set_interrupted_cb(radio, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
	} else {
		ret = radio_set_interrupted_cb(radio, NULL, NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_unset_interrupted_cb_p
 * @since_tizen		2.3
 * @description		Unregisters the callback function.
 */
int utc_media_radio_unset_interrupted_cb_p(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_unset_interrupted_cb(radio);
		assert_eq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_unset_interrupted_cb(radio);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_unset_interrupted_cb_n
 * @since_tizen		2.3
 * @description		Unregisters the callback function with invalid parameter.
 */
int utc_media_radio_unset_interrupted_cb_n(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_unset_interrupted_cb(NULL);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
	} else {
		ret = radio_unset_interrupted_cb(NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_get_signal_strength_p
 * @since_tizen		2.3
 * @description		Gets the current signal strength of the radio.
 */
int utc_media_radio_get_signal_strength_p(void)
{
	int strength = 0;
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_get_signal_strength(radio, &strength);
		assert_eq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_get_signal_strength(radio, &strength);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_get_signal_strength_n
 * @since_tizen		2.3
 * @description		Gets the current signal strength of the radio with invalid parameter.
 */
int utc_media_radio_get_signal_strength_n(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_get_signal_strength(NULL, NULL);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
	} else {
		ret = radio_get_signal_strength(NULL, NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_stop_p
 * @since_tizen		2.3
 * @description		Stops playing the radio.
 */
int utc_media_radio_stop_p(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		radio_state_e state;
		ret = radio_get_state(radio, &state);
		assert_eq(ret, RADIO_ERROR_NONE);
		if (state != RADIO_STATE_PLAYING)
			radio_start(radio);
		ret = radio_stop(radio);
		assert_eq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_stop(radio);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_stop_n
 * @since_tizen		2.3
 * @description		Stops playing the radio with invalid parameter.
 */
int utc_media_radio_stop_n(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_stop(NULL);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
	} else {
		ret = radio_stop(NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_destroy_p
 * @since_tizen		2.3
 * @description		Destroys the radio handle and releases all its resources.
 */
int utc_media_radio_destroy_p(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_destroy(radio);
		assert_eq(ret, RADIO_ERROR_NONE);
		radio = NULL;
	} else {
		ret = radio_destroy(radio);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
		radio = NULL;
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_destroy_n
 * @since_tizen		2.3
 * @description		Destroys the radio handle and releases all its resources with invalid parameter.
 */
int utc_media_radio_destroy_n(void)
{
	int ret;

	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_destroy(NULL);
		assert_neq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_destroy(NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_create_p
 * @since_tizen		2.3
 * @description		Creates a radio handle.
 */
int utc_media_radio_create_p(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		if (radio)
			radio_destroy(radio);
		ret = radio_create(&radio);
		assert_eq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_create(&radio);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_create_n
 * @since_tizen		2.3
 * @description		Creates a radio handle with invalid parameter.
 */
int utc_media_radio_create_n(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_create(NULL);
		assert_neq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_create(NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_get_frequency_range_p
 * @since_tizen		2.4
 * @description		Gets the current frequency of the radio.
 */
int utc_media_radio_get_frequency_range_p(void)
{
	int ret;
	int min, max;

	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_get_frequency_range(radio, &min, &max);
		assert_eq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_get_frequency_range(radio, &min, &max);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_get_frequency_range_n
 * @since_tizen		2.4
 * @description		Gets the current frequency of the radio with invalid parameter.
 */
int utc_media_radio_get_frequency_range_n(void)
{
	int ret;
	int min, max;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_get_frequency_range(NULL, &min, &max);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
	} else {
		ret = radio_get_frequency_range(NULL, &min, &max);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_get_channel_spacing_p
 * @since_tizen		2.4
 * @description		Gets channel spacing.
 */
int utc_media_radio_get_channel_spacing_p(void)
{
	int ret;
	int spacing;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_get_channel_spacing(radio, &spacing);
		assert_eq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_get_channel_spacing(radio, &spacing);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_get_channel_spacing_n
 * @since_tizen		2.4
 * @description		Gets channel spacing with invalid parameter.
 */
int utc_media_radio_get_channel_spacing_n(void)
{
	int ret;
	int spacing;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_get_channel_spacing(radio, NULL);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
	} else {
		ret = radio_get_channel_spacing(radio, NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_set_volume_p
 * @since_tizen		3.0
 * @description		Sets the radio volume.
 */
int utc_media_radio_set_volume_p(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_set_volume(radio, 0.5);
		assert_eq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_set_volume(radio, 0.5);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_set_volume_n
 * @since_tizen		3.0
 * @description		Sets the radio volume with invalid parameter.
 */
int utc_media_radio_set_volume_n(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_set_volume(radio, 2.0);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
	} else {
		ret = radio_set_volume(radio, 2.0);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_get_volume_p
 * @since_tizen		3.0
 * @description		Gets the current volume of the radio.
 */
int utc_media_radio_get_volume_p(void)
{
	int ret;
	float volume;

	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_get_volume(radio, &volume);
		assert_eq(ret, RADIO_ERROR_NONE);
	} else {
		ret = radio_get_volume(radio, &volume);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_media_radio_get_volume_n
 * @since_tizen		3.0
 * @description		Gets the current volume of the radio with invalid parameter.
 */
int utc_media_radio_get_volume_n(void)
{
	int ret;
	if (radio_supported) {
		assert_eq(sRet, RADIO_ERROR_NONE);
		ret = radio_get_volume(NULL, NULL);
		assert_eq(ret, RADIO_ERROR_INVALID_PARAMETER);
	} else {
		ret = radio_get_volume(NULL, NULL);
		assert_eq(ret, RADIO_ERROR_NOT_SUPPORTED);

	}
	return 0;
}

