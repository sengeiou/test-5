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
#include <webrtc.h>

static void __webrtc_state_changed_cb(webrtc_h webrtc, webrtc_state_e previous, webrtc_state_e current, void *user_data)
{
}

static void __webrtc_error_cb(webrtc_h webrtc, webrtc_error_e error, webrtc_state_e state, void *user_data)
{
}

static void __webrtc_ice_candidate_cb(webrtc_h webrtc, const char *candidate, void *user_data)
{
}

static void __webrtc_negotiation_needed_cb(webrtc_h webrtc, void *user_data)
{
}

static void __webrtc_peer_connection_state_change_cb(webrtc_h webrtc, webrtc_peer_connection_state_e state, void *user_data)
{
}

static void __webrtc_signaling_state_change_cb(webrtc_h webrtc, webrtc_signaling_state_e state, void *user_data)
{
}

static void __webrtc_ice_gathering_state_change_cb(webrtc_h webrtc, webrtc_ice_gathering_state_e state, void *user_data)
{
}

static void __webrtc_ice_connection_state_change_cb(webrtc_h webrtc, webrtc_ice_connection_state_e state, void *user_data)
{
}

static void __webrtc_track_added_cb(webrtc_h webrtc, webrtc_media_type_e type, unsigned int track_id, void *user_data)
{
}

static void __webrtc_encoded_frame_cb(webrtc_h webrtc, webrtc_media_type_e type, unsigned int track_id, media_packet_h packet, void *user_data)
{
}

static void __webrtc_media_packet_source_buffer_state_changed_cb(unsigned int source_id, webrtc_media_packet_source_buffer_state_e state, void *user_data)
{
}

static void __webrtc_data_channel_cb(webrtc_h webrtc, webrtc_data_channel_h channel, void *user_data)
{
}

static void __webrtc_data_channel_open_cb(webrtc_data_channel_h channel, void *user_data)
{
}

static void __webrtc_data_channel_message_cb(webrtc_data_channel_h channel, webrtc_data_channel_type_e type, void *message, void *user_data)
{
}

static void __webrtc_data_channel_error_cb(webrtc_data_channel_h channel, webrtc_error_e error, void *user_data)
{
}

static void __webrtc_data_channel_close_cb(webrtc_data_channel_h channel, void *user_data)
{
}

/**
 * @testcase		utc_media_webrtc_set_state_changed_cb_p
 * @since_tizen		6.5
 * @description		Sets a callback function to be invoked when the state is changed
 */
int utc_media_webrtc_set_state_changed_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_state_changed_cb_n
 * @since_tizen		6.5
 * @description		Sets a callback function to be invoked when the state is changed
 *				- Sets the callback without callback function pointer to get negative result
 */
int utc_media_webrtc_set_state_changed_cb_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_state_changed_cb_p
 * @since_tizen		6.5
 * @description		Unsets the state changed callback
 */
int utc_media_webrtc_unset_state_changed_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_state_changed_cb(webrtc, __webrtc_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_state_changed_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_state_changed_cb_n
 * @since_tizen		6.5
 * @description		Unsets the state changed callback
 *				- Unsets the callback without handle to get negative result
 */
int utc_media_webrtc_unset_state_changed_cb_n(void)
{
	int ret = webrtc_unset_state_changed_cb(NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_error_cb_p
 * @since_tizen		6.5
 * @description		Sets a callback function to be invoked when an error occurs
 */
int utc_media_webrtc_set_error_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_error_cb(webrtc, __webrtc_error_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_error_cb_n
 * @since_tizen		6.5
 * @description		Sets a callback function to be invoked when an error occurs
 *				- Sets the callback without callback function pointer to get negative result
 */
int utc_media_webrtc_set_error_cb_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_error_cb(webrtc, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_error_cb_p
 * @since_tizen		6.5
 * @description		Unsets the error callback
 */
int utc_media_webrtc_unset_error_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_error_cb(webrtc, __webrtc_error_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_error_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_error_cb_n
 * @since_tizen		6.5
 * @description		Unsets the error callback
 *				- Unsets the callback without handle to get negative result
 */
int utc_media_webrtc_unset_error_cb_n(void)
{
	int ret = webrtc_unset_error_cb(NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_ice_candidate_cb_p
 * @since_tizen		6.5
 * @description		Sets an ICE candidate callback function
 */
int utc_media_webrtc_set_ice_candidate_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_ice_candidate_cb_n
 * @since_tizen		6.5
 * @description		Sets an ICE candidate callback function
*				- Sets the callback without callback function pointer to get negative result
 */
int utc_media_webrtc_set_ice_candidate_cb_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_ice_candidate_cb_p
 * @since_tizen		6.5
 * @description		Unsets the ice candidate callback
 */
int utc_media_webrtc_unset_ice_candidate_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_candidate_cb(webrtc, __webrtc_ice_candidate_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_ice_candidate_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_ice_candidate_cb_n
 * @since_tizen		6.5
 * @description		Unsets the state changed callback
 *				- Unsets the callback without handle to get negative result
 */
int utc_media_webrtc_unset_ice_candidate_cb_n(void)
{
	int ret = webrtc_unset_ice_candidate_cb(NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_negotiation_needed_cb_p
 * @since_tizen		6.5
 * @description		Sets a negotiation needed callback
 */
int utc_media_webrtc_set_negotiation_needed_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_negotiation_needed_cb(webrtc, __webrtc_negotiation_needed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_negotiation_needed_cb_n
 * @since_tizen		6.5
 * @description		Sets a negotiation needed callback
 *				- Sets the callback without callback function pointer to get negative result
 */
int utc_media_webrtc_set_negotiation_needed_cb_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_negotiation_needed_cb(webrtc, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_negotiation_needed_cb_p
 * @since_tizen		6.5
 * @description		Unsets the negotiation needed callback
 */
int utc_media_webrtc_unset_negotiation_needed_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_negotiation_needed_cb(webrtc, __webrtc_negotiation_needed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_negotiation_needed_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_negotiation_needed_cb_n
 * @since_tizen		6.5
 * @description		Unsets the negotiation needed callback
 *				- Unsets the callback without handle to get negative result
 */
int utc_media_webrtc_unset_negotiation_needed_cb_n(void)
{
	int ret = webrtc_unset_negotiation_needed_cb(NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_peer_connection_state_change_cb_p
 * @since_tizen		6.5
 * @description		Sets a peer connection state change callback
 */
int utc_media_webrtc_set_peer_connection_state_change_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_peer_connection_state_change_cb(webrtc, __webrtc_peer_connection_state_change_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_peer_connection_state_change_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_peer_connection_state_change_cb_n
 * @since_tizen		6.5
 * @description		Sets a peer connection state change callback
 *				- Sets the callback without callback function pointer to get negative result
 */
int utc_media_webrtc_set_peer_connection_state_change_cb_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_peer_connection_state_change_cb(webrtc, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_peer_connection_state_change_cb_p
 * @since_tizen		6.5
 * @description		Unsets the peer connection state change callback
 */
int utc_media_webrtc_unset_peer_connection_state_change_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_peer_connection_state_change_cb(webrtc, __webrtc_peer_connection_state_change_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_peer_connection_state_change_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_peer_connection_state_change_cb_n
 * @since_tizen		6.5
 * @description		Unsets the peer connection state change callback
 *				- Unsets the callback without handle to get negative result
 */
int utc_media_webrtc_unset_peer_connection_state_change_cb_n(void)
{
	int ret = webrtc_unset_peer_connection_state_change_cb(NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_signaling_state_change_cb_p
 * @since_tizen		6.5
 * @description		Sets a signaling state change callback
 */
int utc_media_webrtc_set_signaling_state_change_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_signaling_state_change_cb(webrtc, __webrtc_signaling_state_change_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_signaling_state_change_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_signaling_state_change_cb_n
 * @since_tizen		6.5
 * @description		Sets a signaling state change callback
 *				- Sets the callback without callback function pointer to get negative result
 */
int utc_media_webrtc_set_signaling_state_change_cb_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_signaling_state_change_cb(webrtc, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_signaling_state_change_cb_p
 * @since_tizen		6.5
 * @description		Unsets the signaling state change callback
 */
int utc_media_webrtc_unset_signaling_state_change_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_signaling_state_change_cb(webrtc, __webrtc_signaling_state_change_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_signaling_state_change_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_signaling_state_change_cb_n
 * @since_tizen		6.5
 * @description		Unsets the signaling state change callback
 *				- Unsets the callback without handle to get negative result
 */
int utc_media_webrtc_unset_signaling_state_change_cb_n(void)
{
	int ret = webrtc_unset_signaling_state_change_cb(NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_ice_gathering_state_change_cb_p
 * @since_tizen		6.5
 * @description		Sets a ice gathering state change callback
 */
int utc_media_webrtc_set_ice_gathering_state_change_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_gathering_state_change_cb(webrtc, __webrtc_ice_gathering_state_change_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_ice_gathering_state_change_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_ice_gathering_state_change_cb_n
 * @since_tizen		6.5
 * @description		Sets a ice gathering state change callback
 *				- Sets the callback without callback function pointer to get negative result
 */
int utc_media_webrtc_set_ice_gathering_state_change_cb_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_gathering_state_change_cb(webrtc, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_ice_gathering_state_change_cb_p
 * @since_tizen		6.5
 * @description		Unsets the ice gathering state change callback
 */
int utc_media_webrtc_unset_ice_gathering_state_change_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_gathering_state_change_cb(webrtc, __webrtc_ice_gathering_state_change_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_ice_gathering_state_change_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_ice_gathering_state_change_cb_n
 * @since_tizen		6.5
 * @description		Unsets the ice gathering state change callback
 *				- Unsets the callback without handle to get negative result
 */
int utc_media_webrtc_unset_ice_gathering_state_change_cb_n(void)
{
	int ret = webrtc_unset_ice_gathering_state_change_cb(NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_ice_connection_state_change_cb_p
 * @since_tizen		6.5
 * @description		Sets a ice connection state change callback
 */
int utc_media_webrtc_set_ice_connection_state_change_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_connection_state_change_cb(webrtc, __webrtc_ice_connection_state_change_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_ice_connection_state_change_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_ice_connection_state_change_cb_n
 * @since_tizen		6.5
 * @description		Sets a ice connection state change callback
 *				- Sets the callback without callback function pointer to get negative result
 */
int utc_media_webrtc_set_ice_connection_state_change_cb_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_connection_state_change_cb(webrtc, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_ice_connection_state_change_cb_p
 * @since_tizen		6.5
 * @description		Unsets the ice connection state change callback
 */
int utc_media_webrtc_unset_ice_connection_state_change_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_ice_connection_state_change_cb(webrtc, __webrtc_ice_connection_state_change_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_ice_connection_state_change_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_ice_connection_state_change_cb_n
 * @since_tizen		6.5
 * @description		Unsets the ice connection state change callback
 *				- Unsets the callback without handle to get negative result
 */
int utc_media_webrtc_unset_ice_connection_state_change_cb_n(void)
{
	int ret = webrtc_unset_ice_connection_state_change_cb(NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_track_added_cb_p
 * @since_tizen		6.5
 * @description		Sets a track added callback
 */
int utc_media_webrtc_set_track_added_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_track_added_cb(webrtc, __webrtc_track_added_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_track_added_cb_n
 * @since_tizen		6.5
 * @description		Sets a track added callback
 *				- Sets the callback without callback function pointer to get negative result
 */
int utc_media_webrtc_set_track_added_cb_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_track_added_cb(webrtc, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_track_added_cb_p
 * @since_tizen		6.5
 * @description		Unsets the track added callback
 */
int utc_media_webrtc_unset_track_added_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_track_added_cb(webrtc, __webrtc_track_added_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_track_added_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_track_added_cb_n
 * @since_tizen		6.5
 * @description		Unsets the track added callback
 *				- Unsets the callback without setting it to get negative result
 */
int utc_media_webrtc_unset_track_added_cb_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_track_added_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_INVALID_OPERATION);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_encoded_audio_frame_cb_p
 * @since_tizen		6.5
 * @description		Sets an encoded audio frame callback
 */
int utc_media_webrtc_set_encoded_audio_frame_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_encoded_audio_frame_cb(webrtc, __webrtc_encoded_frame_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_encoded_audio_frame_cb_n
 * @since_tizen		6.5
 * @description		Sets an encoded audio frame callback
 *				- Sets the callback without callback function pointer to get negative result
 */
int utc_media_webrtc_set_encoded_audio_frame_cb_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_encoded_audio_frame_cb(webrtc, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_encoded_audio_frame_cb_p
 * @since_tizen		6.5
 * @description		Unsets the encoded audio frame callback
 */
int utc_media_webrtc_unset_encoded_audio_frame_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_encoded_audio_frame_cb(webrtc, __webrtc_encoded_frame_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_encoded_audio_frame_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_encoded_audio_frame_cb_n
 * @since_tizen		6.5
 * @description		Unsets the encoded audio frame callback
 *				- Unsets the callback without setting it to get negative result
 */
int utc_media_webrtc_unset_encoded_audio_frame_cb_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_encoded_audio_frame_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_INVALID_OPERATION);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_encoded_video_frame_cb_p
 * @since_tizen		6.5
 * @description		Sets an encoded video frame callback
 */
int utc_media_webrtc_set_encoded_video_frame_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_encoded_video_frame_cb(webrtc, __webrtc_encoded_frame_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_encoded_video_frame_cb_n
 * @since_tizen		6.5
 * @description		Sets an encoded video frame callback
 *				- Sets the callback without callback function pointer to get negative result
 */
int utc_media_webrtc_set_encoded_video_frame_cb_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_encoded_video_frame_cb(webrtc, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_encoded_video_frame_cb_p
 * @since_tizen		6.5
 * @description		Unsets the encoded video frame callback
 */
int utc_media_webrtc_unset_encoded_video_frame_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_encoded_video_frame_cb(webrtc, __webrtc_encoded_frame_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_encoded_video_frame_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_encoded_video_frame_cb_n
 * @since_tizen		6.5
 * @description		Unsets the encoded video frame callback
 *				- Unsets the callback without setting it to get negative result
 */
int utc_media_webrtc_unset_encoded_video_frame_cb_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_encoded_video_frame_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_INVALID_OPERATION);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_packet_source_set_buffer_state_changed_cb_p
 * @since_tizen		6.5
 * @description		Sets a buffer state changed callback to media packet source
 */
int utc_media_webrtc_media_packet_source_set_buffer_state_changed_cb_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_MEDIA_PACKET, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_packet_source_set_buffer_state_changed_cb(webrtc, id, __webrtc_media_packet_source_buffer_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_packet_source_set_buffer_state_changed_cb_n1
 * @since_tizen		6.5
 * @description		Sets a buffer state changed callback to media packet source
 *				- Create a webrtc handle\n
 *				- Add a media packet source\n
 *				- Sets the callback without callback function pointer to get negative result
 */
int utc_media_webrtc_media_packet_source_set_buffer_state_changed_cb_n1(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_MEDIA_PACKET, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_packet_source_set_buffer_state_changed_cb(webrtc, id, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_packet_source_set_buffer_state_changed_cb_n2
 * @since_tizen		6.5
 * @description		Sets a buffer state changed callback to media packet source
 *				- Create a webrtc handle\n
 *				- Pass invalid parameter to get negative result
 */
int utc_media_webrtc_media_packet_source_set_buffer_state_changed_cb_n2(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_packet_source_set_buffer_state_changed_cb(webrtc, 1, __webrtc_media_packet_source_buffer_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_packet_source_unset_buffer_state_changed_cb_p
 * @since_tizen		6.5
 * @description		Unsets the buffer state changed callback from media packet source
 */
int utc_media_webrtc_media_packet_source_unset_buffer_state_changed_cb_p(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_MEDIA_PACKET, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_packet_source_set_buffer_state_changed_cb(webrtc, id, __webrtc_media_packet_source_buffer_state_changed_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_packet_source_unset_buffer_state_changed_cb(webrtc, id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_media_packet_source_unset_buffer_state_changed_cb_n
 * @since_tizen		6.5
 * @description		Unsets the buffer state changed callback from media packet source
 *				- Create a webrtc handle\n
 *				- Add a media packet source\n
 *				- Unsets the callback without setting it to get negative result
 */
int utc_media_webrtc_media_packet_source_unset_buffer_state_changed_cb_n(void)
{
	int ret;
	webrtc_h webrtc;
	unsigned int id;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_add_media_source(webrtc, WEBRTC_MEDIA_SOURCE_TYPE_MEDIA_PACKET, &id);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_media_packet_source_unset_buffer_state_changed_cb(webrtc, id);
	assert_eq(ret, WEBRTC_ERROR_INVALID_OPERATION);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_data_channel_cb_p
 * @since_tizen		6.5
 * @description		Sets a data channel callback
 */
int utc_media_webrtc_set_data_channel_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_data_channel_cb(webrtc, __webrtc_data_channel_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_set_data_channel_cb_n
 * @since_tizen		6.5
 * @description		Sets a data channel callback
 *				- Sets the callback without callback function pointer to get negative result
 */
int utc_media_webrtc_set_data_channel_cb_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_data_channel_cb(webrtc, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_data_channel_cb_p
 * @since_tizen		6.5
 * @description		Unsets the data channel callback
 */
int utc_media_webrtc_unset_data_channel_cb_p(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_set_data_channel_cb(webrtc, __webrtc_data_channel_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_data_channel_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_unset_data_channel_cb_n
 * @since_tizen		6.5
 * @description		Unsets the data channel callback
*				- Unsets the callback without setting it to get negative result
 */
int utc_media_webrtc_unset_data_channel_cb_n(void)
{
	int ret;
	webrtc_h webrtc;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_unset_data_channel_cb(webrtc);
	assert_eq(ret, WEBRTC_ERROR_INVALID_OPERATION);

	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_set_open_cb_p
 * @since_tizen		6.5
 * @description		Sets an open callback to a data channel
 *				- Create a webrtc handle\n
 *				- Create a data channel\n
 *				- Set a data channel open callback
 */
int utc_media_webrtc_data_channel_set_open_cb_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, "test channel", NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_set_open_cb(channel, __webrtc_data_channel_open_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_set_open_cb_n
 * @since_tizen		6.5
 * @description		Sets an open callback to a data channel
 *				- Sets the callback without callback function pointer to get negative result
 */
int utc_media_webrtc_data_channel_set_open_cb_n(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, "test channel", NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_set_open_cb(channel, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_unset_open_cb_p
 * @since_tizen		6.5
 * @description		Unsets the data channel open callback
 */
int utc_media_webrtc_data_channel_unset_open_cb_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, "test channel", NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_set_open_cb(channel, __webrtc_data_channel_open_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_unset_open_cb(channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_unset_open_cb_n
 * @since_tizen		6.5
 * @description		Unsets the data channel open callback
*				- Unsets the callback without setting it to get negative result
 */
int utc_media_webrtc_data_channel_unset_open_cb_n(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, "test channel", NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_unset_open_cb(channel);
	assert_eq(ret, WEBRTC_ERROR_INVALID_OPERATION);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_set_message_cb_p
 * @since_tizen		6.5
 * @description		Sets a message callback to a data channel
 *				- Create a webrtc handle\n
 *				- Create a data channel\n
 *				- Set a data channel message callback
 */
int utc_media_webrtc_data_channel_set_message_cb_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, "test channel", NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_set_message_cb(channel, __webrtc_data_channel_message_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_set_message_cb_n
 * @since_tizen		6.5
 * @description		Sets a message callback to a data channel
 *				- Sets the callback without callback function pointer to get negative result
 */
int utc_media_webrtc_data_channel_set_message_cb_n(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, "test channel", NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_set_message_cb(channel, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_unset_message_cb_p
 * @since_tizen		6.5
 * @description		Unsets the data channel message callback
 */
int utc_media_webrtc_data_channel_unset_message_cb_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, "test channel", NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_set_message_cb(channel, __webrtc_data_channel_message_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_unset_message_cb(channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_unset_message_cb_n
 * @since_tizen		6.5
 * @description		Unsets the data channel message callback
*				- Unsets the callback without setting it to get negative result
 */
int utc_media_webrtc_data_channel_unset_message_cb_n(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, "test channel", NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_unset_message_cb(channel);
	assert_eq(ret, WEBRTC_ERROR_INVALID_OPERATION);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_set_error_cb_p
 * @since_tizen		6.5
 * @description		Sets an error callback to a data channel
 *				- Create a webrtc handle\n
 *				- Create a data channel\n
 *				- Set a data channel error callback
 */
int utc_media_webrtc_data_channel_set_error_cb_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, "test channel", NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_set_error_cb(channel, __webrtc_data_channel_error_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_set_error_cb_n
 * @since_tizen		6.5
 * @description		Sets an error callback to a data channel
 *				- Sets the callback without callback function pointer to get negative result
 */
int utc_media_webrtc_data_channel_set_error_cb_n(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, "test channel", NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_set_error_cb(channel, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_unset_error_cb_p
 * @since_tizen		6.5
 * @description		Unsets the data channel error callback
 */
int utc_media_webrtc_data_channel_unset_error_cb_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, "test channel", NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_set_error_cb(channel, __webrtc_data_channel_error_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_unset_error_cb(channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_unset_error_cb_n
 * @since_tizen		6.5
 * @description		Unsets the data channel error callback
*				- Unsets the callback without setting it to get negative result
 */
int utc_media_webrtc_data_channel_unset_error_cb_n(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, "test channel", NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_unset_error_cb(channel);
	assert_eq(ret, WEBRTC_ERROR_INVALID_OPERATION);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_set_close_cb_p
 * @since_tizen		6.5
 * @description		Sets a close callback to a data channel
 *				- Create a webrtc handle\n
 *				- Create a data channel\n
 *				- Set a data channel close callback
 */
int utc_media_webrtc_data_channel_set_close_cb_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, "test channel", NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_set_close_cb(channel, __webrtc_data_channel_close_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_set_close_cb_n
 * @since_tizen		6.5
 * @description		Sets a close callback to a data channel
 *				- Sets the callback without callback function pointer to get negative result
 */
int utc_media_webrtc_data_channel_set_close_cb_n(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, "test channel", NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_set_close_cb(channel, NULL, NULL);
	assert_eq(ret, WEBRTC_ERROR_INVALID_PARAMETER);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_unset_close_cb_p
 * @since_tizen		6.5
 * @description		Unsets the data channel close callback
 */
int utc_media_webrtc_data_channel_unset_close_cb_p(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, "test channel", NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_set_close_cb(channel, __webrtc_data_channel_close_cb, NULL);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_unset_close_cb(channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}

/**
 * @testcase		utc_media_webrtc_data_channel_unset_close_cb_n
 * @since_tizen		6.5
 * @description		Unsets the data channel close callback
*				- Unsets the callback without setting it to get negative result
 */
int utc_media_webrtc_data_channel_unset_close_cb_n(void)
{
	int ret;
	webrtc_h webrtc;
	webrtc_data_channel_h channel;

	ret = webrtc_create(&webrtc);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_create_data_channel(webrtc, "test channel", NULL, &channel);
	assert_eq(ret, WEBRTC_ERROR_NONE);

	ret = webrtc_data_channel_unset_close_cb(channel);
	assert_eq(ret, WEBRTC_ERROR_INVALID_OPERATION);

	webrtc_destroy_data_channel(channel);
	webrtc_destroy(webrtc);

	return 0;
}
