/*
 * Copyright (c) 2021 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "assert.h"
#include <glib.h>
#include <webrtc.h>
#include <dlog.h>
#include <Elementary.h>

#define API_NAMESPACE                 "WEBRTC_UTC"
#define TIMEOUT_MS                     1000
#define TEST_WIDTH                     640
#define TEST_HEIGHT                    480
#define TEST_FPS                       30
#define TEST_STUN_SERVER_URL           "stun://stun.testurl.com:19302"
#define TEST_TURN_SERVER_URL           "turn://turn.testurl.com:19303"
#define TEST_TURN_SERVER_URL2          "turn://turn2.testurl.com:19303"
#define TEST_ICE_CANDIDATE             "{'ice':{'candidate':'candidate:3600539631 1 tcp 1518149375 192.168.0.127 9 typ host tcptype active generation 0 ufrag l4kk network-id 3 network-cost 10','sdpMid':'video0','sdpMLineIndex':0}}"
#define TEST_DATA_CHANNEL_LABEL        "test data channel"
#define TEST_STRING_DATA               "test string"
#define TEST_BUFFER_SIZE               16
#define TEST_BUFFERED_AMOUNT_THRESHOLD 65535

static GMainLoop *g_mainloop = NULL;
static int g_timeout_id = 0;
static Evas_Object *g_win = NULL;

static gboolean __timeout_func(gpointer data)
{
	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] g_main_loop_quit()", __FUNCTION__, __LINE__);

	g_main_loop_quit((GMainLoop *) data);
	return FALSE;
}

static void __quit_mainloop()
{
	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] g_main_loop_quit()", __FUNCTION__, __LINE__);

	if (g_timeout_id > 0) {
		g_source_remove(g_timeout_id);
		g_timeout_id = 0;
	}
	if (g_mainloop != NULL)
		g_main_loop_quit(g_mainloop);
}

static void __run_mainloop()
{
	g_mainloop = g_main_loop_new(NULL, FALSE);
	g_timeout_id = g_timeout_add(TIMEOUT_MS, __timeout_func, g_mainloop);

	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] call g_main_loop_run()", __FUNCTION__, __LINE__);

	g_main_loop_run(g_mainloop);

	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] quit g_main_loop_run()", __FUNCTION__, __LINE__);

	g_main_loop_unref(g_mainloop);
	g_mainloop = NULL;
}

static void __win_del(void *data, Evas_Object *obj, void *event)
{
	elm_exit();
}

static void __create_window()
{
	int w = 0;
	int h = 0;

	g_win = elm_win_util_standard_add("webrtc_utc", "webrtc_utc");
	if (g_win) {
		elm_win_borderless_set(g_win, EINA_TRUE);
		evas_object_smart_callback_add(g_win, "delete,request", __win_del, NULL);
		elm_win_screen_size_get(g_win, NULL, NULL, &w, &h);
		evas_object_resize(g_win, w, h);
		elm_win_autodel_set(g_win, EINA_TRUE);
	}

	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s:%d] g_win[%p]", __FUNCTION__, __LINE__, g_win);
}

static void __destroy_window()
{
	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s:%d] g_win[%p]", __FUNCTION__, __LINE__, g_win);

	if (g_win) {
		evas_object_del(g_win);
		g_win = NULL;
	}
}

static void __webrtc_media_packet_source_buffer_state_changed_cb(unsigned int source_id, webrtc_media_packet_source_buffer_state_e state, void *user_data)
{
}

static void __webrtc_ice_candidate_cb(webrtc_h webrtc, const char *candidate, void *user_data)
{
}

static void __webrtc_state_changed_cb(webrtc_h webrtc, webrtc_state_e previous, webrtc_state_e current, void *user_data)
{
	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s:%d] current state[%d]", __FUNCTION__, __LINE__, current);

	__quit_mainloop();
}

static void __webrtc_signaling_state_change_cb(webrtc_h webrtc, webrtc_signaling_state_e state, void *user_data)
{
	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s:%d] current state[%d]", __FUNCTION__, __LINE__, state);

	__quit_mainloop();
}

static bool __webrtc_turn_server_cb(const char *turn_server, void *user_data)
{
	int *count = (int*)user_data;

	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s:%d] turn_server[%s]", __FUNCTION__, __LINE__, turn_server);

	(*count)--;

	return true;
}

static bool __webrtc_stats_cb(webrtc_stats_type_e type, const webrtc_stats_prop_info_s *prop_info, void *user_data)
{
	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s:%d] type[%d] prop_info->name[%s]", __FUNCTION__, __LINE__, type, prop_info->name);

	return true;
}

static void __webrtc_session_description_created_cb(webrtc_h webrtc, const char *description, void *user_data)
{
	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s:%d] description[%s]", __FUNCTION__, __LINE__, description);

	__quit_mainloop();
}

static void __data_channel_buffered_amount_low_cb(webrtc_data_channel_h channel, void *user_data)
{
}

/**
 * @function		utc_media_webrtc_startup_create_win
 * @description		Should be called before a test using a window
 */
void utc_media_webrtc_startup_create_win(void)
{
	__create_window();
}

/**
 * @function		utc_media_webrtc_cleanup_destroy_win
 * @description		Should be called after the test with the window
 */
void utc_media_webrtc_cleanup_destroy_win(void)
{
	__destroy_window();
}

/**
 * @testcase		utc_media_webrtc_create_p
 * @since_tizen		6.5
 * @description		Creates a webrtc handle
 */
int utc_media_webrtc_create_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_create_n
 * @since_tizen		6.5
 * @description		Creates a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_create_n(void)
{
	int ret = webrtc_create(NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_destroy_p
 * @since_tizen		6.5
 * @description		Destroys the webrtc handle\n
 *				- Create a webrtc handle\n
 *				- Pass the webrtc handle to destroy
 */
int utc_media_webrtc_destroy_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_destroy(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_destroy_n
 * @since_tizen		6.5
 * @description		Destroys the webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_destroy_n(void)
{
	int ret = webrtc_destroy(NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_start_p
 * @since_tizen		6.5
 * @description		Starts the webrtc handle\n
 *				- Create a webrtc handle\n
 *				- Set ICE candidate callback\n
 *				- Start the handle
 */
int utc_media_webrtc_start_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_start_n1
 * @since_tizen		6.5
 * @description		Starts the webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_start_n1(void)
{
	int ret = webrtc_start(NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_start_n2
 * @since_tizen		6.5
 * @description		Starts the webrtc handle\n
 *				- Create a webrtc handle\n
 *				- Start the handle without setting ice candidate callback to get negative result
 */
int utc_media_webrtc_start_n2(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_INVALID_OPERATION);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_stop_p
 * @since_tizen		6.5
 * @description		Stops the webrtc handle\n
 *				- Create a webrtc handle\n
 *				- Set ICE candidate callback\n
 *				- Start the handle\n
 *				- Stop the handle
 */
int utc_media_webrtc_stop_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_stop(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_stop_n1
 * @since_tizen		6.5
 * @description		Stops the webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_stop_n1(void)
{
	int ret = webrtc_stop(NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_stop_n2
 * @since_tizen		6.5
 * @description		Stops the webrtc handle\n
 *				- Create a webrtc handle\n
 *				- Stop the handle without start to get negative result
 */
int utc_media_webrtc_stop_n2(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_stop(webrtc);
	assert_eq(ret, WEBRTC_ERROR_INVALID_STATE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_state_p
 * @since_tizen		6.5
 * @description		Gets the webrtc state\n
 *				- Create a webrtc handle\n
 *				- Get state of the handle
 */
int utc_media_webrtc_get_state_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_state_e state;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_state(webrtc, &state);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(state, WEBRTC_STATE_IDLE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_state_n1
 * @since_tizen		6.5
 * @description		Gets the webrtc state\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_get_state_n1(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_state(webrtc, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_state_n2
 * @since_tizen		6.5
 * @description		Gets the webrtc state\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_get_state_n2(void)
{
	webrtc_state_e state;
	int ret = webrtc_get_state(NULL, &state);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_add_media_source_p
 * @since_tizen		6.5
 * @description		Adds a media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source
 */
int utc_media_webrtc_add_media_source_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_add_media_source_n1
 * @since_tizen		6.5
 * @description		Adds a media source\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_add_media_source_n1(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_add_media_source_n2
 * @since_tizen		6.5
 * @description		Adds a media source\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_add_media_source_n2(void)
{
	unsigned int id;

	int ret = webrtc_add_media_source(NULL, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_remove_media_source_p
 * @since_tizen		6.5
 * @description		Removes the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Remove the media source
 */
int utc_media_webrtc_remove_media_source_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_CAMERA, &id);
	if (ret == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] camera feature is not supported, skip it", __FUNCTION__, __LINE__);
		webrtc_destroy(webrtc);
		return 0;
	}
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_remove_media_source(webrtc, id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_remove_media_source_n1
 * @since_tizen		6.5
 * @description		Removes the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_remove_media_source_n1(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_SCREEN, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_remove_media_source(webrtc, id + 1);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_remove_media_source_n2
 * @since_tizen		6.5
 * @description		Removes the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_remove_media_source_n2(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_FILE, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_remove_media_source(webrtc, id - 1);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_transceiver_direction_p
 * @since_tizen		6.5
 * @description		Sets a transceiver direction\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Set a direction
 */
int utc_media_webrtc_media_source_set_transceiver_direction_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	webrtc_transceiver_direction_e direction;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_transceiver_direction(webrtc, id, WEBRTC_MEDIA_TYPE_AUDIO, WEBRTC_TRANSCEIVER_DIRECTION_RECVONLY);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_get_transceiver_direction(webrtc, id, WEBRTC_MEDIA_TYPE_AUDIO, &direction);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(direction, WEBRTC_TRANSCEIVER_DIRECTION_RECVONLY);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_transceiver_direction_n
 * @since_tizen		6.5
 * @description		Sets a transceiver direction\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Set an invalid direction to get negative result
 */
int utc_media_webrtc_media_source_set_transceiver_direction_n(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_transceiver_direction(webrtc, id, WEBRTC_MEDIA_TYPE_AUDIO, WEBRTC_TRANSCEIVER_DIRECTION_SENDRECV + 1);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_get_transceiver_direction_p
 * @since_tizen		6.5
 * @description		Gets the transceiver direction\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Get the direction
 */
int utc_media_webrtc_media_source_get_transceiver_direction_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	webrtc_transceiver_direction_e direction;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_get_transceiver_direction(webrtc, id, WEBRTC_MEDIA_TYPE_VIDEO, &direction);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(direction, WEBRTC_TRANSCEIVER_DIRECTION_SENDRECV); /* check the default value */

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_get_transceiver_direction_n
 * @since_tizen		6.5
 * @description		Gets the transceiver direction\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_media_source_get_transceiver_direction_n(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	webrtc_transceiver_direction_e direction;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_get_transceiver_direction(webrtc, id + 1, WEBRTC_MEDIA_TYPE_VIDEO, &direction);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_pause_p
 * @since_tizen		6.5
 * @description		Sets pause to the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Set pause
 */
int utc_media_webrtc_media_source_set_pause_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	bool paused;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_pause(webrtc, id, WEBRTC_MEDIA_TYPE_AUDIO, true);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_get_pause(webrtc, id, WEBRTC_MEDIA_TYPE_AUDIO, &paused);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(paused, true);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_pause_n
 * @since_tizen		6.5
 * @description		Sets pause to the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_media_source_set_pause_n(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_pause(webrtc, id, WEBRTC_MEDIA_TYPE_VIDEO, true);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_get_pause_p
 * @since_tizen		6.5
 * @description		Gets pause from the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Get pause
 */
int utc_media_webrtc_media_source_get_pause_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	bool paused;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_get_pause(webrtc, id, WEBRTC_MEDIA_TYPE_AUDIO, &paused);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(paused, false); /* check the default value */

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_get_pause_n
 * @since_tizen		6.5
 * @description		Gets pause from the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_media_source_get_pause_n(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_get_pause(webrtc, id, WEBRTC_MEDIA_TYPE_AUDIO, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_mute_p
 * @since_tizen		6.5
 * @description		Sets mute to the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Set mute
 */
int utc_media_webrtc_media_source_set_mute_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	bool muted;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_mute(webrtc, id, WEBRTC_MEDIA_TYPE_VIDEO, true);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_get_mute(webrtc, id, WEBRTC_MEDIA_TYPE_VIDEO, &muted);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(muted, true);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_mute_n
 * @since_tizen		6.5
 * @description		Sets mute to the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_media_source_set_mute_n(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_FILE, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_mute(webrtc, id, WEBRTC_MEDIA_TYPE_VIDEO, true);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_get_mute_p
 * @since_tizen		6.5
 * @description		Gets mute from the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Get mute
 */
int utc_media_webrtc_media_source_get_mute_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	bool muted;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_get_mute(webrtc, id, WEBRTC_MEDIA_TYPE_VIDEO, &muted);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(muted, false); /* check the default value */

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_get_mute_n
 * @since_tizen		6.5
 * @description		Gets mute from the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_media_source_get_mute_n(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	bool muted;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_FILE, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_get_mute(webrtc, id, WEBRTC_MEDIA_TYPE_VIDEO, &muted);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_video_resolution_p
 * @since_tizen		6.5
 * @description		Sets video resolution to the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Set video resolution
 */
int utc_media_webrtc_media_source_set_video_resolution_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	int width;
	int height;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_video_resolution(webrtc, id, TEST_WIDTH, TEST_HEIGHT);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_get_video_resolution(webrtc, id, &width, &height);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(width, TEST_WIDTH);
	assert_eq(height, TEST_HEIGHT);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_video_resolution_n1
 * @since_tizen		6.5
 * @description		Sets video resolution to the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_media_source_set_video_resolution_n1(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_CAMERA, &id);
	if (ret == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] camera feature is not supported, skip it", __FUNCTION__, __LINE__);
		webrtc_destroy(webrtc);
		return 0;
	}
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_video_resolution(webrtc, id, 0, 0);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_video_resolution_n2
 * @since_tizen		6.5
 * @description		Sets video resolution to the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source for audio\n
 *				- Set a video resolution to get negative result
 */
int utc_media_webrtc_media_source_set_video_resolution_n2(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_video_resolution(webrtc, id, TEST_WIDTH, TEST_HEIGHT);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_get_video_resolution_p
 * @since_tizen		6.5
 * @description		Gets video resolution from the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Get the video resolution
 */
int utc_media_webrtc_media_source_get_video_resolution_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	int width;
	int height;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_CAMERA, &id);
	if (ret == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] camera feature is not supported, skip it", __FUNCTION__, __LINE__);
		webrtc_destroy(webrtc);
		return 0;
	}
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_get_video_resolution(webrtc, id, &width, &height);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_get_video_resolution_n1
 * @since_tizen		6.5
 * @description		Gets video resolution from the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_media_source_get_video_resolution_n1(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_CAMERA, &id);
	if (ret == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] camera feature is not supported, skip it", __FUNCTION__, __LINE__);
		webrtc_destroy(webrtc);
		return 0;
	}
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_get_video_resolution(webrtc, id, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_get_video_resolution_n2
 * @since_tizen		6.5
 * @description		Gets video resolution from the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source for audio\n
 *				- Get the video resolution to get negative result
 */
int utc_media_webrtc_media_source_get_video_resolution_n2(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	int width;
	int height;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_get_video_resolution(webrtc, id, &width, &height);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_video_framerate_p
 * @since_tizen		7.0
 * @description		Sets video framerate to the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Set video framerate
 */
int utc_media_webrtc_media_source_set_video_framerate_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	int fps;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_video_framerate(webrtc, id, TEST_FPS);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_get_video_framerate(webrtc, id, &fps);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(fps, TEST_FPS);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_video_framerate_n1
 * @since_tizen		7.0
 * @description		Sets video framerate to the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_media_source_set_video_framerate_n1(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_CAMERA, &id);
	if (ret == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] camera feature is not supported, skip it", __FUNCTION__, __LINE__);
		webrtc_destroy(webrtc);
		return 0;
	}
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_video_framerate(webrtc, id, 0);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_video_framerate_n2
 * @since_tizen		7.0
 * @description		Sets video framerate to the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source for audio\n
 *				- Set a video framerate to get negative result
 */
int utc_media_webrtc_media_source_set_video_framerate_n2(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_video_framerate(webrtc, id, TEST_FPS);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_get_video_framerate_p
 * @since_tizen		7.0
 * @description		Gets video framerate from the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Get the video framerate
 */
int utc_media_webrtc_media_source_get_video_framerate_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	int fps;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_CAMERA, &id);
	if (ret == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] camera feature is not supported, skip it", __FUNCTION__, __LINE__);
		webrtc_destroy(webrtc);
		return 0;
	}
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_get_video_framerate(webrtc, id, &fps);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_get_video_framerate_n1
 * @since_tizen		7.0
 * @description		Gets video framerate from the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_media_source_get_video_framerate_n1(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_CAMERA, &id);
	if (ret == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] camera feature is not supported, skip it", __FUNCTION__, __LINE__);
		webrtc_destroy(webrtc);
		return 0;
	}
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_get_video_framerate(webrtc, id, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_get_video_framerate_n2
 * @since_tizen		7.0
 * @description		Gets video framerate from the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source for audio\n
 *				- Get the video framerate to get negative result
 */
int utc_media_webrtc_media_source_get_video_framerate_n2(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	int fps;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_get_video_framerate(webrtc, id, &fps);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_mic_source_set_sound_stream_info_p
 * @since_tizen		6.5
 * @description		Sets sound stream info to the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Set sound stream info
 */
int utc_media_webrtc_mic_source_set_sound_stream_info_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	sound_stream_info_h stream_info;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, NULL, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_MIC, &id);
	if (ret == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] microphone feature is not supported, skip it", __FUNCTION__, __LINE__);
		webrtc_destroy(webrtc);
		return 0;
	}
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_mic_source_set_sound_stream_info(webrtc, id, stream_info);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	sound_manager_destroy_stream_information(stream_info);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_mic_source_set_sound_stream_info_n1
 * @since_tizen		6.5
 * @description		Sets sound stream info to the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_mic_source_set_sound_stream_info_n1(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_MIC, &id);
	if (ret == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] microphone feature is not supported, skip it", __FUNCTION__, __LINE__);
		webrtc_destroy(webrtc);
		return 0;
	}
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_mic_source_set_sound_stream_info(webrtc, id, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_mic_source_set_sound_stream_info_n2
 * @since_tizen		6.5
 * @description		Sets sound stream info to the media source\n
 *				- Create a webrtc handle\n
 *				- Add a media source not for mic\n
 *				- Set sound stream info to get negative result
 */
int utc_media_webrtc_mic_source_set_sound_stream_info_n2(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	sound_stream_info_h stream_info;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, NULL, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_mic_source_set_sound_stream_info(webrtc, id, stream_info);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	sound_manager_destroy_stream_information(stream_info);
	webrtc_destroy(webrtc);

	return 0;
}

static int __set_audio_format(media_format_h format)
{
	int ret;

	if (!format)
		return -1;

	ret = media_format_set_audio_mime(format, MEDIA_FORMAT_PCM_S16LE);
	ret |= media_format_set_audio_channel(format, 1);
	ret |= media_format_set_audio_samplerate(format, 8000);
	ret |= media_format_set_audio_bit(format, 16);

	return ret;
}

static int __set_video_format(media_format_h format)
{
	int ret;

	if (!format)
		return -1;

	ret = media_format_set_video_mime(format, MEDIA_FORMAT_I420);
	ret |= media_format_set_video_width(format, 640);
	ret |= media_format_set_video_height(format, 480);

	return ret;
}

/**
 * @testcase		utc_media_webrtc_media_packet_source_set_format_p
 * @since_tizen		6.5
 * @description		Sets media format to the media packet source\n
 *				- Create a webrtc handle\n
 *				- Add a media packet source\n
 *				- Set media format
 */
int utc_media_webrtc_media_packet_source_set_format_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	media_format_h format;

	ret = media_format_create(&format);
	assert_eq(ret, MEDIA_FORMAT_ERROR_NONE);

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_MEDIA_PACKET, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = __set_audio_format(format);
	assert_eq(ret, MEDIA_FORMAT_ERROR_NONE);

	ret = webrtc_media_packet_source_set_format(webrtc, id, format);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	media_format_unref(format);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_packet_source_set_format_n
 * @since_tizen		6.5
 * @description		Sets media format to the media packet source\n
 *				- Create a webrtc handle\n
 *				- Add a media packet source\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_media_packet_source_set_format_n(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	media_format_h format;

	ret = media_format_create(&format);
	assert_eq(ret, MEDIA_FORMAT_ERROR_NONE);

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_MEDIA_PACKET, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_packet_source_set_format(webrtc, id, format);
	assert_eq(ret, WEBRTC_ERROR_INVALID_OPERATION);

	media_format_unref(format);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_packet_source_push_packet_p
 * @since_tizen		6.5
 * @description		Pushes media packet to the media packet source\n
 *				- Create a webrtc handle\n
 *				- Add a media packet source\n
 *				- Set media format\n
 *				- Set buffer state changed callback\n
 *				- Push media packet
 */
int utc_media_webrtc_media_packet_source_push_packet_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	media_format_h format;
	media_packet_h packet;

	ret = media_format_create(&format);
	assert_eq(ret, MEDIA_FORMAT_ERROR_NONE);

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_MEDIA_PACKET, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = __set_video_format(format);
	assert_eq(ret, MEDIA_FORMAT_ERROR_NONE);

	ret = webrtc_media_packet_source_set_format(webrtc, id, format);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_packet_source_set_buffer_state_changed_cb(webrtc, id, __webrtc_media_packet_source_buffer_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = media_packet_new_alloc(format, NULL, NULL, &packet);
	assert_eq(ret, MEDIA_PACKET_ERROR_NONE);

	ret = webrtc_media_packet_source_push_packet(webrtc, id, packet);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	media_format_unref(format);
	media_packet_unref(packet);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_packet_source_push_packet_n1
 * @since_tizen		6.5
 * @description		Pushes media packet to the media packet source\n
 *				- Create a webrtc handle\n
 *				- Add a media packet source\n
 *				- Set buffer state changed callback\n
 *				- Push media packet without setting format to get negative result
 */
int utc_media_webrtc_media_packet_source_push_packet_n1(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	media_format_h format;
	media_packet_h packet;

	ret = media_format_create(&format);
	assert_eq(ret, MEDIA_FORMAT_ERROR_NONE);

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_MEDIA_PACKET, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = __set_video_format(format);
	assert_eq(ret, MEDIA_FORMAT_ERROR_NONE);

	ret = webrtc_media_packet_source_set_buffer_state_changed_cb(webrtc, id, __webrtc_media_packet_source_buffer_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = media_packet_new_alloc(format, NULL, NULL, &packet);
	assert_eq(ret, MEDIA_PACKET_ERROR_NONE);

	ret = webrtc_media_packet_source_push_packet(webrtc, id, packet);
	assert_eq(ret, WEBRTC_ERROR_INVALID_OPERATION);

	media_format_unref(format);
	media_packet_unref(packet);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_packet_source_push_packet_n2
 * @since_tizen		6.5
 * @description		Pushes media packet to the media packet source\n
 *				- Create a webrtc handle\n
 *				- Add a media packet source\n
 *				- Set media format\n
 *				- Set buffer state changed callback\n
 *				- Push media packet with invalid source id to get negative result
 */
int utc_media_webrtc_media_packet_source_push_packet_n2(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	media_format_h format;
	media_packet_h packet;

	ret = media_format_create(&format);
	assert_eq(ret, MEDIA_FORMAT_ERROR_NONE);

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_MEDIA_PACKET, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = __set_video_format(format);
	assert_eq(ret, MEDIA_FORMAT_ERROR_NONE);

	ret = webrtc_media_packet_source_set_format(webrtc, id, format);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_packet_source_set_buffer_state_changed_cb(webrtc, id, __webrtc_media_packet_source_buffer_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = media_packet_new_alloc(format, NULL, NULL, &packet);
	assert_eq(ret, MEDIA_PACKET_ERROR_NONE);

	ret = webrtc_media_packet_source_push_packet(webrtc, id + 1, packet);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	media_format_unref(format);
	media_packet_unref(packet);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_packet_source_push_packet_n3
 * @since_tizen		6.5
 * @description		Pushes media packet to the media packet source\n
 *				- Create a webrtc handle\n
 *				- Add a media packet source\n
 *				- Set media format\n
 *				- Push media packet without setting buffer state changed callback to get negative result
 */
int utc_media_webrtc_media_packet_source_push_packet_n3(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	media_format_h format;
	media_packet_h packet;

	ret = media_format_create(&format);
	assert_eq(ret, MEDIA_FORMAT_ERROR_NONE);

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_MEDIA_PACKET, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = __set_video_format(format);
	assert_eq(ret, MEDIA_FORMAT_ERROR_NONE);

	ret = webrtc_media_packet_source_set_format(webrtc, id, format);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = media_packet_new_alloc(format, NULL, NULL, &packet);
	assert_eq(ret, MEDIA_PACKET_ERROR_NONE);

	ret = webrtc_media_packet_source_push_packet(webrtc, id, packet);
	assert_eq(ret, WEBRTC_ERROR_INVALID_OPERATION);

	media_format_unref(format);
	media_packet_unref(packet);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_file_source_set_path_p
 * @since_tizen		7.0
 * @description		Sets media path of the file source\n
 *				- Create a webrtc handle\n
 *				- Add a file source\n
 *				- Set required callbacks\n
 *				- Set media path
 */
int utc_media_webrtc_file_source_set_path_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	char video_path[256] = {0, };
	char pszValue[CONFIG_VALUE_LEN_MAX] = { 0, };

	if (GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE)) {
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE, pszValue);

		snprintf(video_path, PATH_MAX, "%s/res/movie.mp4", pszValue);
	} else {
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_FILE, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_file_source_set_path(webrtc, id, video_path);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	webrtc_stop(webrtc);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_file_source_set_path_n1
 * @since_tizen		7.0
 * @description		Sets media path of the file source\n
 *				- Create a webrtc handle\n
 *				- Add a audio test source\n
 *				- Pass invalid source id to get negative result
 */
int utc_media_webrtc_file_source_set_path_n1(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	char video_path[256] = {0, };
	char pszValue[CONFIG_VALUE_LEN_MAX] = { 0, };

	if (GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE)) {
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE, pszValue);

		snprintf(video_path, PATH_MAX, "%s/res/movie.mp4", pszValue);
	} else {
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_file_source_set_path(webrtc, id, video_path);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_file_source_set_path_n2
 * @since_tizen		7.0
 * @description		Sets media path of the file source\n
 *				- Create a webrtc handle\n
 *				- Add a file source\n
 *				- Pass invalid media path to get negative result
 */
int utc_media_webrtc_file_source_set_path_n2(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_FILE, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_file_source_set_path(webrtc, id, "test.mp4");
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_file_source_set_looping_p
 * @since_tizen		7.0
 * @description		Sets looping mode of the file source\n
 *				- Create a webrtc handle\n
 *				- Add a file source\n
 *				- Set looping mode
 */
int utc_media_webrtc_file_source_set_looping_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_FILE, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_file_source_set_looping(webrtc, id, true);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_file_source_set_looping_n
 * @since_tizen		7.0
 * @description		Sets looping mode of the file source\n
 *				- Create a webrtc handle\n
 *				- Add a video test source\n
 *				- Pass invalid source id to get negative result
 */
int utc_media_webrtc_file_source_set_looping_n(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_file_source_set_looping(webrtc, id, true);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_file_source_get_looping_p
 * @since_tizen		7.0
 * @description		Gets looping mode of the file source\n
 *				- Create a webrtc handle\n
 *				- Add a file source\n
 *				- Set looping mode
 *				- Get looping mode
 */
int utc_media_webrtc_file_source_get_looping_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	bool looping;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_FILE, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_file_source_set_looping(webrtc, id, true);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_file_source_get_looping(webrtc, id, &looping);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	assert_eq(looping, true);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_file_source_get_looping_n1
 * @since_tizen		7.0
 * @description		Gets looping mode of the file source\n
 *				- Create a webrtc handle\n
 *				- Add a video test source\n
 *				- Pass invalid source id to get negative result
 */
int utc_media_webrtc_file_source_get_looping_n1(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	bool looping;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_file_source_get_looping(webrtc, id, &looping);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_file_source_get_looping_n2
 * @since_tizen		7.0
 * @description		Sets looping mode of the file source\n
 *				- Create a webrtc handle\n
 *				- Add a file source\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_file_source_get_looping_n2(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_FILE, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_file_source_get_looping(webrtc, id, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_audio_loopback_p
 * @since_tizen		6.5
 * @description		Sets audio loopback of particular source id\n
 *				- Create a webrtc handle\n
 *				- Add a media source for audio\n
 *				- Set required callbacks\n
 *				- Create stream info\n
 *				- Set audio loopback
 */
int utc_media_webrtc_media_source_set_audio_loopback_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	sound_stream_info_h stream_info;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_MIC, &id);
	if (ret == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] microphone feature is not supported, skip it", __FUNCTION__, __LINE__);
		webrtc_destroy(webrtc);
		return 0;
	}
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, NULL, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = webrtc_media_source_set_audio_loopback(webrtc, id, stream_info, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	webrtc_stop(webrtc);
	sound_manager_destroy_stream_information(stream_info);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_audio_loopback_n1
 * @since_tizen		6.5
 * @description		Sets audio loopback of particular source id\n
 *				- Create a webrtc handle\n
 *				- Add a media source for audio\n
 *				- Set audio loopback without stream info to get negative result
 */
int utc_media_webrtc_media_source_set_audio_loopback_n1(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_audio_loopback(webrtc, id, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_audio_loopback_n2
 * @since_tizen		6.5
 * @description		Sets audio loopback of particular source id\n
 *				- Create a webrtc handle\n
 *				- Add a media source for audio\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_media_source_set_audio_loopback_n2(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_audio_loopback(webrtc, 0, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_audio_loopback_n3
 * @since_tizen		6.5
 * @description		Sets audio loopback of particular source id\n
 *				- Create a webrtc handle\n
 *				- Add a media source for audio\n
 *				- Set audio loopback with unsupported stream info to get negative result
 */
int utc_media_webrtc_media_source_set_audio_loopback_n3(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	sound_stream_info_h stream_info;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_MIC, &id);
	if (ret == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] microphone feature is not supported, skip it", __FUNCTION__, __LINE__);
		webrtc_destroy(webrtc);
		return 0;
	}
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_ALARM, NULL, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = webrtc_media_source_set_audio_loopback(webrtc, id, stream_info, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	sound_manager_destroy_stream_information(stream_info);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_unset_audio_loopback_p
 * @since_tizen		7.0
 * @description		Unsets audio loopback of particular source id\n
 *				- Create a webrtc handle\n
 *				- Add a media source for audio\n
 *				- Create stream info\n
 *				- Set audio loopback\n
 *				- Unset audio loopback
 */
int utc_media_webrtc_media_source_unset_audio_loopback_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	sound_stream_info_h stream_info;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_MIC, &id);
	if (ret == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] microphone feature is not supported, skip it", __FUNCTION__, __LINE__);
		webrtc_destroy(webrtc);
		return 0;
	}
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, NULL, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = webrtc_media_source_set_audio_loopback(webrtc, id, stream_info, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_unset_audio_loopback(webrtc, id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	sound_manager_destroy_stream_information(stream_info);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_unset_audio_loopback_n1
 * @since_tizen		7.0
 * @description		Unsets audio loopback of particular source id\n
 *				- Create a webrtc handle\n
 *				- Add a media source for audio\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_media_source_unset_audio_loopback_n1(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_unset_audio_loopback(webrtc, 0);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_unset_audio_loopback_n2
 * @since_tizen		7.0
 * @description		Unsets audio loopback of particular source id\n
 *				- Create a webrtc handle\n
 *				- Add a media source for audio\n
 *				- Unset audio loopback without prior setting to get negative result
 */
int utc_media_webrtc_media_source_unset_audio_loopback_n2(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_unset_audio_loopback(webrtc, id);
	assert_eq(ret, WEBRTC_ERROR_INVALID_OPERATION);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_video_loopback_p
 * @since_tizen		6.5
 * @description		Sets video loopback of particular source id\n
 *				- Create a webrtc handle\n
 *				- Add a media source for video\n
 *				- Set required callbacks\n
 *				- Set video loopback
 */
int utc_media_webrtc_media_source_set_video_loopback_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_video_loopback(webrtc, id, WEBRTC_DISPLAY_TYPE_OVERLAY, g_win, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	webrtc_stop(webrtc);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_video_loopback_n1
 * @since_tizen		6.5
 * @description		Sets video loopback of particular source id\n
 *				- Create a webrtc handle\n
 *				- Add a media source for video\n
 *				- Set video loopback without display to get negative result
 */
int utc_media_webrtc_media_source_set_video_loopback_n1(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_CAMERA, &id);
	if (ret == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] camera feature is not supported, skip it", __FUNCTION__, __LINE__);
		webrtc_destroy(webrtc);
		return 0;
	}
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_video_loopback(webrtc, id, WEBRTC_DISPLAY_TYPE_EVAS, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_video_loopback_n2
 * @since_tizen		6.5
 * @description		Sets video loopback of particular source id\n
 *				- Create a webrtc handle\n
 *				- Add a media source for video\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_media_source_set_video_loopback_n2(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_video_loopback(webrtc, 0, WEBRTC_DISPLAY_TYPE_EVAS, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_set_video_loopback_n3
 * @since_tizen		6.5
 * @description		Sets video loopback of particular source id\n
 *				- Create a webrtc handle\n
 *				- Add a media source for video\n
 *				- Set video loopback with invalid display type to get negative result
 */
int utc_media_webrtc_media_source_set_video_loopback_n3(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_SCREEN, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_video_loopback(webrtc, id, WEBRTC_DISPLAY_TYPE_EVAS + 1, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_unset_video_loopback_p
 * @since_tizen		7.0
 * @description		Sets video loopback of particular source id\n
 *				- Create a webrtc handle\n
 *				- Add a media source for video\n
 *				- Set required callbacks\n
 *				- Set video loopback
 *				- Unset video loopback
 */
int utc_media_webrtc_media_source_unset_video_loopback_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_video_loopback(webrtc, id, WEBRTC_DISPLAY_TYPE_OVERLAY, g_win, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_unset_video_loopback(webrtc, id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_unset_video_loopback_n1
 * @since_tizen		7.0
 * @description		Sets video loopback of particular source id\n
 *				- Create a webrtc handle\n
 *				- Add a media source for video\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_media_source_unset_video_loopback_n1(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_CAMERA, &id);
	if (ret == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] camera feature is not supported, skip it", __FUNCTION__, __LINE__);
		webrtc_destroy(webrtc);
		return 0;
	}
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_unset_video_loopback(webrtc, 0);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_source_unset_video_loopback_n2
 * @since_tizen		7.0
 * @description		Sets video loopback of particular source id\n
 *				- Create a webrtc handle\n
 *				- Add a media source for video\n
 *				- Unset video loopback without prior setting to get negative result
 */
int utc_media_webrtc_media_source_unset_video_loopback_n2(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_CAMERA, &id);
	if (ret == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] camera feature is not supported, skip it", __FUNCTION__, __LINE__);
		webrtc_destroy(webrtc);
		return 0;
	}
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_unset_video_loopback(webrtc, id);
	assert_eq(ret, WEBRTC_ERROR_INVALID_OPERATION);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_sound_stream_info_n
 * @since_tizen		6.5
 * @description		Sets sound stream info\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_set_sound_stream_info_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_sound_stream_info(webrtc, 0, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_display_n
 * @since_tizen		6.5
 * @description		Sets display\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_set_display_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_display(webrtc, 0, WEBRTC_DISPLAY_TYPE_EVAS, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_display_mode_p
 * @since_tizen		6.5
 * @description		Sets display mode\n
 *				- Create a webrtc handle\n
 *				- Add a media source for video\n
 *				- Set video loopback\n
 *				- Set display mode
 */
int utc_media_webrtc_set_display_mode_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	unsigned int track_id;
	webrtc_display_mode_e mode;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_video_loopback(webrtc, id, WEBRTC_DISPLAY_TYPE_OVERLAY, g_win, &track_id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_set_display_mode(webrtc, track_id, WEBRTC_DISPLAY_MODE_FULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_display_mode(webrtc, track_id, &mode);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(mode, WEBRTC_DISPLAY_MODE_FULL);

	webrtc_stop(webrtc);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_display_mode_n
 * @since_tizen		6.5
 * @description		Sets display mode\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_set_display_mode_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_display_mode(webrtc, 0, WEBRTC_DISPLAY_MODE_ORIGIN_SIZE);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_display_mode_p
 * @since_tizen		6.5
 * @description		Sets display mode\n
 *				- Create a webrtc handle\n
 *				- Add a media source for video\n
 *				- Set video loopback\n
 *				- Get display mode
 */
int utc_media_webrtc_get_display_mode_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	unsigned int track_id;
	webrtc_display_mode_e mode;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_video_loopback(webrtc, id, WEBRTC_DISPLAY_TYPE_OVERLAY, g_win, &track_id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_get_display_mode(webrtc, track_id, &mode);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(mode, WEBRTC_DISPLAY_MODE_LETTER_BOX); /* check the default value */

	webrtc_stop(webrtc);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_display_mode_n
 * @since_tizen		6.5
 * @description		Gets display mode\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_get_display_mode_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_display_mode(webrtc, 0, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_display_visible_p
 * @since_tizen		6.5
 * @description		Sets display visible\n
 *				- Create a webrtc handle\n
 *				- Add a media source for video\n
 *				- Set video loopback\n
 *				- Set display visible
 */
int utc_media_webrtc_set_display_visible_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	unsigned int track_id;
	bool visible;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_video_loopback(webrtc, id, WEBRTC_DISPLAY_TYPE_OVERLAY, g_win, &track_id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_set_display_visible(webrtc, track_id, false);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_display_visible(webrtc, track_id, &visible);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(visible, false);

	webrtc_stop(webrtc);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_display_visible_n
 * @since_tizen		6.5
 * @description		Sets display visible\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_set_display_visible_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_display_visible(webrtc, 0, true);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_display_visible_p
 * @since_tizen		6.5
 * @description		Sets display visible\n
 *				- Create a webrtc handle\n
 *				- Add a media source for video\n
 *				- Set video loopback\n
 *				- Get display visible
 */
int utc_media_webrtc_get_display_visible_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	unsigned int track_id;
	bool visible;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_source_set_video_loopback(webrtc, id, WEBRTC_DISPLAY_TYPE_OVERLAY, g_win, &track_id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_get_display_visible(webrtc, track_id, &visible);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(visible, true); /* check the default value */

	webrtc_stop(webrtc);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_display_visible_n
 * @since_tizen		6.5
 * @description		Gets display visible\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_get_display_visible_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_display_visible(webrtc, 0, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_stun_server_p
 * @since_tizen		6.5
 * @description		Sets STUN server\n
 *				- Create a webrtc handle\n
 *				- Set STUN server
 */
int utc_media_webrtc_set_stun_server_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_stun_server(webrtc, TEST_STUN_SERVER_URL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_stun_server_n1
 * @since_tizen		6.5
 * @description		Sets STUN server\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_set_stun_server_n1(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_stun_server(webrtc, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_stun_server_n2
 * @since_tizen		6.5
 * @description		Sets STUN server\n
 *				- Create a webrtc handle\n
 *				- Start the webrtc handle and set it to get negative result
 */
int utc_media_webrtc_set_stun_server_n2(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_set_stun_server(webrtc, TEST_STUN_SERVER_URL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_STATE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_stun_server_p
 * @since_tizen		6.5
 * @description		Gets STUN server\n
 *				- Create a webrtc handle\n
 *				- Set STUN server
 *				- Get the server
 */
int utc_media_webrtc_get_stun_server_p(void)
{
	int ret;
	webrtc_h webrtc;
	char *result = NULL;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_stun_server(webrtc, TEST_STUN_SERVER_URL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_stun_server(webrtc, &result);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] %s %s", __FUNCTION__, __LINE__, result, TEST_STUN_SERVER_URL);

	ret = strcmp(result, TEST_STUN_SERVER_URL);
	free(result);
	assert_eq(ret, 0);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_stun_server_n
 * @since_tizen		6.5
 * @description		Gets STUN server\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_get_stun_server_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_stun_server(webrtc, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}


/**
 * @testcase		utc_media_webrtc_add_turn_server_p
 * @since_tizen		6.5
 * @description		Adds TURN server\n
 *				- Create a webrtc handle\n
 *				- Add TURN server
 */
int utc_media_webrtc_add_turn_server_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_turn_server(webrtc, TEST_TURN_SERVER_URL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_add_turn_server_n1
 * @since_tizen		6.5
 * @description		Adds TURN server\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_add_turn_server_n1(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_turn_server(webrtc, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_add_turn_server_n2
 * @since_tizen		6.5
 * @description		Adds TURN server\n
 *				- Create a webrtc handle\n
 *				- Start the webrtc handle and set it to get negative result
 */
int utc_media_webrtc_add_turn_server_n2(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_add_turn_server(webrtc, TEST_TURN_SERVER_URL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_STATE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_foreach_turn_server_p
 * @since_tizen		6.5
 * @description		Retrieves TURN servers\n
 *				- Create a webrtc handle\n
 *				- Add TURN server\n
 *				- Foreach TURN server
 */
int utc_media_webrtc_foreach_turn_server_p(void)
{
	int ret;
	webrtc_h webrtc;
	int count = 0;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_turn_server(webrtc, TEST_TURN_SERVER_URL);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	count++;

	ret = webrtc_add_turn_server(webrtc, TEST_TURN_SERVER_URL2);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	count++;

	ret = webrtc_foreach_turn_server(webrtc, __webrtc_turn_server_cb, (void *)&count);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(count, 0);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_foreach_turn_server_n
 * @since_tizen		6.5
 * @description		Adds TURN server\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_foreach_turn_server_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_foreach_turn_server(webrtc, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_bundle_policy_p
 * @since_tizen		7.0
 * @description		Sets bundle policy\n
 *				- Create a webrtc handle\n
 *				- Set a bundle policy
 */
int utc_media_webrtc_set_bundle_policy_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_bundle_policy_e policy;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_bundle_policy(webrtc, WEBRTC_BUNDLE_POLICY_NONE);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_bundle_policy(webrtc, &policy);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(policy, WEBRTC_BUNDLE_POLICY_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_bundle_policy_n
 * @since_tizen		7.0
 * @description		Sets bundle policy\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_set_bundle_policy_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_bundle_policy(webrtc, WEBRTC_BUNDLE_POLICY_MAX_BUNDLE + 1);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_bundle_policy_p
 * @since_tizen		7.0
 * @description		Gets bundle policy\n
 *				- Create a webrtc handle\n
 *				- Get a bundle policy
 */
int utc_media_webrtc_get_bundle_policy_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_bundle_policy_e policy;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_bundle_policy(webrtc, &policy);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(policy, WEBRTC_BUNDLE_POLICY_MAX_BUNDLE); /* check the default value */

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_bundle_policy_n
 * @since_tizen		7.0
 * @description		Gets bundle policy\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_get_bundle_policy_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_bundle_policy(webrtc, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_ice_transport_policy_p
 * @since_tizen		6.5
 * @description		Sets ICE transport policy\n
 *				- Create a webrtc handle\n
 *				- Set a ICE transport policy
 */
int utc_media_webrtc_set_ice_transport_policy_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_ice_transport_policy_e policy;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_transport_policy(webrtc, WEBRTC_ICE_TRANSPORT_POLICY_RELAY);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_ice_transport_policy(webrtc, &policy);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(policy, WEBRTC_ICE_TRANSPORT_POLICY_RELAY);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_ice_transport_policy_n
 * @since_tizen		6.5
 * @description		Sets ICE transport policy\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_set_ice_transport_policy_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_transport_policy(webrtc, WEBRTC_ICE_TRANSPORT_POLICY_RELAY + 1);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_ice_transport_policy_p
 * @since_tizen		6.5
 * @description		Gets ICE transport policy\n
 *				- Create a webrtc handle\n
 *				- Get a ICE transport policy
 */
int utc_media_webrtc_get_ice_transport_policy_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_ice_transport_policy_e policy;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_ice_transport_policy(webrtc, &policy);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(policy, WEBRTC_ICE_TRANSPORT_POLICY_ALL); /* check the default value */

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_ice_transport_policy_n
 * @since_tizen		6.5
 * @description		Gets ICE transport policy\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_get_ice_transport_policy_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_ice_transport_policy(webrtc, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_create_offer_p
 * @since_tizen		6.5
 * @description		Creates an offer message\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Start the webrtc handle\n
 *				- Create an offer message
 */
int utc_media_webrtc_create_offer_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	char *offer;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_create_offer(webrtc, NULL, &offer);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	free(offer);

	webrtc_stop(webrtc);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_create_offer_n1
 * @since_tizen		6.5
 * @description		Creates an offer message\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_create_offer_n1(void)
{
	int ret = webrtc_create_offer(NULL, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_create_offer_n2
 * @since_tizen		6.5
 * @description		Creates an offer message\n
 *				- Create a webrtc handle\n
 *				- Create an offer in IDLE state to get negative result
 */
int utc_media_webrtc_create_offer_n2(void)
{
	int ret;
	webrtc_h webrtc;
	char *offer;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_offer(webrtc, NULL, &offer);
	assert_eq(ret, WEBRTC_ERROR_INVALID_STATE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_create_answer_p
 * @since_tizen		6.5
 * @description		Creates an answer message\n
 *				- handle1 : Create a webrtc handle\n
 *				- handle1 : Add a media source\n
 *				- handle1 : Start the webrtc handle\n
 *				- handle1 : Create an offer message\n
 *				- handle2 : Create a webrtc handle\n
  *				- handle2 : Start the webrtc handle\n
 *				- handle2 : Set the remote description\n
 *				- handle2 : Create an answer message
 */
int utc_media_webrtc_create_answer_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_h webrtc2;
	unsigned int id;
	char *offer;
	char *answer;

	/* handle 1: offerer */
	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_SCREEN, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_create_offer(webrtc, NULL, &offer);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] offer[%s]", __FUNCTION__, __LINE__, offer);

	/* handle 2: answerer */
	ret = webrtc_create(&webrtc2);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc2, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc2, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_signaling_state_change_cb(webrtc2, __webrtc_signaling_state_change_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc2);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_set_remote_description(webrtc2, offer);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_create_answer(webrtc2, NULL, &answer);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] answer[%s]", __FUNCTION__, __LINE__, answer);

	free(offer);
	free(answer);

#if 0 /* FIXME: blocking issue */
	webrtc_stop(webrtc);
	webrtc_destroy(webrtc);

	webrtc_stop(webrtc2);
	webrtc_destroy(webrtc2);
#endif
	return 0;
}

/**
 * @testcase		utc_media_webrtc_create_answer_n1
 * @since_tizen		6.5
 * @description		Creates an answer message\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_create_answer_n1(void)
{
	int ret = webrtc_create_answer(NULL, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_create_answer_n2
 * @since_tizen		6.5
 * @description		Creates an answer message\n
 *				- Create a webrtc handle\n
 *				- Create an answer in IDLE state to get negative result
 */
int utc_media_webrtc_create_answer_n2(void)
{
	int ret;
	webrtc_h webrtc;
	char *offer;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_answer(webrtc, NULL, &offer);
	assert_eq(ret, WEBRTC_ERROR_INVALID_STATE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_create_answer_n3
 * @since_tizen		6.5
 * @description		Creates an answer message\n
 *				- Create a webrtc handle\n
  *				- Start the webrtc handle\n
 *				- Create an answer without setting a remote description to get negative result
 */
int utc_media_webrtc_create_answer_n3(void)
{
	int ret;
	webrtc_h webrtc;
	char *offer;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_create_answer(webrtc, NULL, &offer);
	assert_eq(ret, WEBRTC_ERROR_INVALID_STATE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_create_offer_async_p
 * @since_tizen		6.5
 * @description		Creates an offer message asynchronously\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Start the webrtc handle\n
 *				- Create an offer message asynchronously
 */
int utc_media_webrtc_create_offer_async_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_CAMERA, &id);
	if (ret == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] camera feature is not supported, skip it", __FUNCTION__, __LINE__);
		webrtc_destroy(webrtc);
		return 0;
	}
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_create_offer_async(webrtc, NULL, __webrtc_session_description_created_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	webrtc_stop(webrtc);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_create_offer_async_n1
 * @since_tizen		6.5
 * @description		Creates an offer message asynchronously\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_create_offer_async_n1(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_offer_async(webrtc, NULL, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_create_offer_async_n2
 * @since_tizen		6.5
 * @description		Creates an offer message asynchronously\n
 *				- Create a webrtc handle\n
 *				- Create an offer in IDLE state to get negative result
 */
int utc_media_webrtc_create_offer_async_n2(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_offer_async(webrtc, NULL, __webrtc_session_description_created_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_STATE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_create_answer_async_p
 * @since_tizen		6.5
 * @description		Creates an answer message asynchronously\n
 *				- handle1 : Create a webrtc handle\n
 *				- handle1 : Add a media source\n
 *				- handle1 : Start the webrtc handle\n
 *				- handle1 : Create an offer message\n
 *				- handle2 : Create a webrtc handle\n
 *				- handle2 : Start the webrtc handle\n
 *				- handle2 : Set the remote description\n
 *				- handle2 : Create an answer message asynchronously
 */
int utc_media_webrtc_create_answer_async_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_h webrtc2;
	unsigned int id;
	char *offer;

	/* handle 1: offerer */
	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_create_offer(webrtc, NULL, &offer);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] offer[%s]", __FUNCTION__, __LINE__, offer);

	/* handle 2: answerer */
	ret = webrtc_create(&webrtc2);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc2, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc2, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_signaling_state_change_cb(webrtc2, __webrtc_signaling_state_change_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc2);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_set_remote_description(webrtc2, offer);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_create_answer_async(webrtc2, NULL, __webrtc_session_description_created_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	free(offer);

	webrtc_stop(webrtc);
	webrtc_destroy(webrtc);

	webrtc_stop(webrtc2);
	webrtc_destroy(webrtc2);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_create_answer_async_n1
 * @since_tizen		6.5
 * @description		Creates an answer message asynchronously\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_create_answer_async_n1(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_answer_async(webrtc, NULL, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_create_answer_async_n2
 * @since_tizen		6.5
 * @description		Creates an answer message asynchronously\n
 *				- Create a webrtc handle\n
 *				- Create an answer in IDLE state to get negative result
 */
int utc_media_webrtc_create_answer_async_n2(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_answer_async(webrtc, NULL, __webrtc_session_description_created_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_STATE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_create_answer_async_n3
 * @since_tizen		6.5
 * @description		Creates an answer message asynchronously\n
 *				- Create a webrtc handle\n
 *				- Start the webrtc handle\n
 *				- Create an answer without setting a remote description to get negative result
 */
int utc_media_webrtc_create_answer_async_n3(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_create_answer_async(webrtc, NULL, __webrtc_session_description_created_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_STATE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_local_description_p
 * @since_tizen		6.5
 * @description		Creates an offer message\n
 *				- Create a webrtc handle\n
 *				- Add a media source\n
 *				- Start the webrtc handle\n
 *				- Create an offer message\n
 *				- Set the offer message as local description
 */
int utc_media_webrtc_set_local_description_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;
	char *offer;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_CAMERA, &id);
	if (ret == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] camera feature is not supported, skip it", __FUNCTION__, __LINE__);
		webrtc_destroy(webrtc);
		return 0;
	}
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_create_offer(webrtc, NULL, &offer);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_local_description(webrtc, offer);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	free(offer);

	webrtc_stop(webrtc);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_local_description_n
 * @since_tizen		6.5
 * @description		Sets a local description\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_set_local_description_n(void)
{
	int ret = webrtc_set_local_description(NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_remote_description_p
 * @since_tizen		6.5
 * @description		Creates an answer message\n
 *				- handle1 : Create a webrtc handle\n
 *				- handle1 : Add a media source\n
 *				- handle1 : Start the webrtc handle\n
 *				- handle1 : Create an offer message\n
 *				- handle2 : Create a webrtc handle\n
  *				- handle2 : Start the webrtc handle\n
 *				- handle2 : Set the remote description
 */
int utc_media_webrtc_set_remote_description_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_h webrtc2;
	unsigned int id;
	char *offer;

	/* handle 1: offerer */
	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_MIC, &id);
	if (ret == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] microphone feature is not supported, skip it", __FUNCTION__, __LINE__);
		webrtc_destroy(webrtc);
		return 0;
	}
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_create_offer(webrtc, NULL, &offer);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] offer[%s]", __FUNCTION__, __LINE__, offer);

	/* handle 2: answerer */
	ret = webrtc_create(&webrtc2);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc2, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc2, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc2);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_set_remote_description(webrtc2, offer);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	free(offer);

	webrtc_stop(webrtc);
	webrtc_destroy(webrtc);

	webrtc_stop(webrtc2);
	webrtc_destroy(webrtc2);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_remote_description_n
 * @since_tizen		6.5
 * @description		Sets a remote description\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_set_remote_description_n(void)
{
	int ret = webrtc_set_remote_description(NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_add_ice_candidate_p
 * @since_tizen		6.5
 * @description		Adds an ICE candidate\n
 *				- Create a webrtc handle\n
 *				- Set ICE candidate callback\n
 *				- Start the handle\n
 *				- Add an ICE candidate
 */
int utc_media_webrtc_add_ice_candidate_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_start(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	__run_mainloop();

	ret = webrtc_add_ice_candidate(webrtc, TEST_ICE_CANDIDATE);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_stop(webrtc);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_add_ice_candidate_n1
 * @since_tizen		6.5
 * @description		Adds an ICE candidate\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_add_ice_candidate_n1(void)
{
	int ret = webrtc_add_ice_candidate(NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_add_ice_candidate_n2
 * @since_tizen		6.5
 * @description		Adds an ICE candidate\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_add_ice_candidate_n2(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_ice_candidate(webrtc, TEST_ICE_CANDIDATE);
	assert_eq(ret, WEBRTC_ERROR_INVALID_STATE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_peer_connection_state_p
 * @since_tizen		6.5
 * @description		Gets the webrtc peer connection state\n
 *				- Create a webrtc handle\n
 *				- Get the state
 */
int utc_media_webrtc_get_peer_connection_state_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_peer_connection_state_e state;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_peer_connection_state(webrtc, &state);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(state, WEBRTC_PEER_CONNECTION_STATE_NEW);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_peer_connection_state_n
 * @since_tizen		6.5
 * @description		Gets the webrtc peer connection state\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_get_peer_connection_state_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_peer_connection_state(webrtc, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_signaling_state_p
 * @since_tizen		6.5
 * @description		Gets the webrtc signaling state\n
 *				- Create a webrtc handle\n
 *				- Get the state
 */
int utc_media_webrtc_get_signaling_state_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_signaling_state_e state;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_signaling_state(webrtc, &state);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(state, WEBRTC_SIGNALING_STATE_STABLE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_signaling_state_n
 * @since_tizen		6.5
 * @description		Gets the webrtc signaling state\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_get_signaling_state_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_signaling_state(webrtc, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_ice_gathering_state_p
 * @since_tizen		6.5
 * @description		Gets the webrtc ice gathering state\n
 *				- Create a webrtc handle\n
 *				- Get the state
 */
int utc_media_webrtc_get_ice_gathering_state_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_ice_gathering_state_e state;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_ice_gathering_state(webrtc, &state);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(state, WEBRTC_ICE_GATHERING_STATE_NEW);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_ice_gathering_state_n
 * @since_tizen		6.5
 * @description		Gets the webrtc ice gathering state\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_get_ice_gathering_state_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_ice_gathering_state(webrtc, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_ice_connection_state_p
 * @since_tizen		6.5
 * @description		Gets the webrtc ice connection state\n
 *				- Create a webrtc handle\n
 *				- Get the state
 */
int utc_media_webrtc_get_ice_connection_state_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_ice_connection_state_e state;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_ice_connection_state(webrtc, &state);
	assert_eq(ret, WEBRTC_ERROR_NONE);
	assert_eq(state, WEBRTC_ICE_CONNECTION_STATE_NEW);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_ice_connection_state_n
 * @since_tizen		6.5
 * @description		Gets the webrtc ice connection state\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_get_ice_connection_state_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_get_ice_connection_state(webrtc, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_create_data_channel_p
 * @since_tizen		6.5
 * @description		Creates a data channel\n
 *				- Create a webrtc handle\n
 *				- Create a data channel
 */
int utc_media_webrtc_create_data_channel_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, TEST_DATA_CHANNEL_LABEL, NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_create_data_channel_n
 * @since_tizen		6.5
 * @description		Creates a data channel\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_create_data_channel_n(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, NULL, NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_destroy_data_channel_p
 * @since_tizen		6.5
 * @description		Destroys the data channel\n
 *				- Create a webrtc handle\n
 *				- Create a data channel\n
 *				- Destroy the data channel
 */
int utc_media_webrtc_destroy_data_channel_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, TEST_DATA_CHANNEL_LABEL, NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy_data_channel(channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_destroy_data_channel_n
 * @since_tizen		6.5
 * @description		Destroys the data channel\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_destroy_data_channel_n(void)
{
	int ret = webrtc_destroy_data_channel(NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_get_label_p
 * @since_tizen		6.5
 * @description		Gets the data channel label\n
 *				- Create a webrtc handle\n
 *				- Create a data channel\n
 *				- Get the data channel label
 */
int utc_media_webrtc_data_channel_get_label_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;
	char *label;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, TEST_DATA_CHANNEL_LABEL, NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_get_label(channel, &label);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	ret = strcmp(label, TEST_DATA_CHANNEL_LABEL);
	free(label);
	assert_eq(ret, 0);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_get_label_n
 * @since_tizen		6.5
 * @description		Gets the data channel label\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_data_channel_get_label_n(void)
{
	int ret = webrtc_data_channel_get_label(NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_send_string_p
 * @since_tizen		6.5
 * @description		Sends string data to the data channel\n
 *				- Create a webrtc handle\n
 *				- Create a data channel\n
 *				- Send a string data
 */
int utc_media_webrtc_data_channel_send_string_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, TEST_DATA_CHANNEL_LABEL, NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	/* FIXME: It's not ready to send data before negotiation success with remote peer.
	 * For now, we don't handle a remote peer, therefore here just check the invalid
	 * state return value temporarily. */
	ret = webrtc_data_channel_send_string(channel, TEST_STRING_DATA);
	assert_eq(ret, WEBRTC_ERROR_INVALID_STATE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_send_string_n
 * @since_tizen		6.5
 * @description		Sends string data to the data channel\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_data_channel_send_string_n(void)
{
	int ret = webrtc_data_channel_send_string(NULL, TEST_STRING_DATA);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_send_bytes_p
 * @since_tizen		6.5
 * @description		Sends bytes data to the data channel\n
 *				- Create a webrtc handle\n
 *				- Create a data channel\n
 *				- Send bytes data
 */
int utc_media_webrtc_data_channel_send_bytes_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;
	char buffer[TEST_BUFFER_SIZE] = {0, };

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, TEST_DATA_CHANNEL_LABEL, NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	/* FIXME: It's not ready to send data before negotiation success with remote peer.
	 * For now, we don't handle a remote peer, therefore here just check the invalid
	 * state return value temporarily. */
	ret = webrtc_data_channel_send_bytes(channel, buffer, TEST_BUFFER_SIZE);
	assert_eq(ret, WEBRTC_ERROR_INVALID_STATE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_send_bytes_n
 * @since_tizen		6.5
 * @description		Sends bytes data to the data channel\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_data_channel_send_bytes_n(void)
{
	int ret = webrtc_data_channel_send_bytes(NULL, NULL, 0);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_data_p
 * @since_tizen		6.5
 * @description		Gets the data\n
 *				- Get the data
 */
int utc_media_webrtc_get_data_p(void)
{
	/* simulate data structure */
	typedef struct _bytes_data_s {
		void *data;
		unsigned long size;
	} bytes_data_s;

	int ret;
	char buf[] = {'a', 'b', 'c', 'd'};
	bytes_data_s bytes = {buf, sizeof(buf)};
	const char *data;
	unsigned long size;

	ret = webrtc_get_data((webrtc_bytes_data_h)&bytes, &data, &size);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_get_data_n
 * @since_tizen		6.5
 * @description		Gets the data\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_get_data_n(void)
{
	int ret = webrtc_get_data(NULL, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_get_buffered_amount_p
 * @since_tizen		7.0
 * @description		Gets the number of bytes of data currently queued to be sent through the data channel\n
 *				- Create a webrtc handle\n
 *				- Create a data channel\n
 *				- Get buffered amount
 */
int utc_media_webrtc_data_channel_get_buffered_amount_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;
	unsigned int buffered_amount;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, TEST_DATA_CHANNEL_LABEL, NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	/* FIXME: Buffered amount should be checked while sending data over the data channel.
	 * But, it's not ready to send data before negotiation success with remote peer.
	 * For now, we don't handle a remote peer, therefore here just check the API usage. */
	ret = webrtc_data_channel_get_buffered_amount(channel, &buffered_amount);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_get_buffered_amount_n
 * @since_tizen		7.0
 * @description		Gets the number of bytes of data currently queued to be sent through the data channel\n
 *				- Create a webrtc handle\n
 *				- Create a data channel\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_data_channel_get_buffered_amount_n(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, TEST_DATA_CHANNEL_LABEL, NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_get_buffered_amount(channel, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_set_buffered_amount_low_cb_p
 * @since_tizen		7.0
 * @description		Sets the threshold at which the buffered amount is considered low and callback function\n
 *				- Create a webrtc handle\n
 *				- Create a data channel\n
 *				- Set the threshold and callback
 */
int utc_media_webrtc_data_channel_set_buffered_amount_low_cb_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, TEST_DATA_CHANNEL_LABEL, NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_set_buffered_amount_low_cb(channel, TEST_BUFFERED_AMOUNT_THRESHOLD, __data_channel_buffered_amount_low_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_set_buffered_amount_low_cb_n
 * @since_tizen		7.0
 * @description		Sets the threshold at which the buffered amount is considered low and callback function\n
 *				- Create a webrtc handle\n
 *				- Create a data channel\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_data_channel_set_buffered_amount_low_cb_n(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, TEST_DATA_CHANNEL_LABEL, NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_set_buffered_amount_low_cb(channel, TEST_BUFFERED_AMOUNT_THRESHOLD, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_get_buffered_amount_low_threshold_p
 * @since_tizen		7.0
 * @description		Gets the threshold at which the buffered amount is considered low\n
 *				- Create a webrtc handle\n
 *				- Create a data channel\n
 *				- Set the threshold and callback\n
 *				- Get the threshold
 */
int utc_media_webrtc_data_channel_get_buffered_amount_low_threshold_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;
	unsigned int threshold;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, TEST_DATA_CHANNEL_LABEL, NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_set_buffered_amount_low_cb(channel, TEST_BUFFERED_AMOUNT_THRESHOLD, __data_channel_buffered_amount_low_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_get_buffered_amount_low_threshold(channel, &threshold);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	assert_eq(threshold, TEST_BUFFERED_AMOUNT_THRESHOLD);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_get_buffered_amount_low_threshold_n
 * @since_tizen		7.0
 * @description		Gets the threshold at which the buffered amount is considered low\n
 *				- Create a webrtc handle\n
 *				- Create a data channel\n
 *				- Set the threshold and callback\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_data_channel_get_buffered_amount_low_threshold_n(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, TEST_DATA_CHANNEL_LABEL, NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_set_buffered_amount_low_cb(channel, TEST_BUFFERED_AMOUNT_THRESHOLD, __data_channel_buffered_amount_low_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_get_buffered_amount_low_threshold(channel, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_unset_buffered_amount_low_cb_p
 * @since_tizen		7.0
 * @description		Unsets the data channel buffered amount low callback function\n
 *				- Create a webrtc handle\n
 *				- Create a data channel\n
 *				- Set the threshold and callback\n
 *				- Unset the callback
 */
int utc_media_webrtc_data_channel_unset_buffered_amount_low_cb_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, TEST_DATA_CHANNEL_LABEL, NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_set_buffered_amount_low_cb(channel, TEST_BUFFERED_AMOUNT_THRESHOLD, __data_channel_buffered_amount_low_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_unset_buffered_amount_low_cb(channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_unset_buffered_amount_low_cb_n
 * @since_tizen		7.0
 * @description		Unsets the data channel buffered amount low callback function\n
 *				- Create a webrtc handle\n
 *				- Create a data channel\n
 *				- Unset the callback without setting it to get negative result
 */
int utc_media_webrtc_data_channel_unset_buffered_amount_low_cb_n(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, TEST_DATA_CHANNEL_LABEL, NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_unset_buffered_amount_low_cb(channel);
	assert_eq(ret, WEBRTC_ERROR_INVALID_OPERATION);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_foreach_stats_p
 * @since_tizen		7.0
 * @description		Retrieves statistics properties\n
 *				- Create a webrtc handle\n
 *				- Foreach stats
 */
int utc_media_webrtc_foreach_stats_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_foreach_stats(webrtc, WEBRTC_STATS_TYPE_ALL, __webrtc_stats_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_STATE); /* actual operation will be checked in ITC */

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_foreach_stats_n
 * @since_tizen		7.0
 * @description		Retrieves statistics properties\n
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_foreach_stats_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_foreach_stats(webrtc, WEBRTC_STATS_TYPE_ALL, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}
