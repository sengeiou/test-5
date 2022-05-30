//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-webrtc-common.h"

//& set: Webrtc

/** @addtogroup itc-webrtc
*  @ingroup itc
*  @{
*/
#define TEST_ICE_CANDIDATE     "{'ice':{'candidate':'candidate:3600539631 1 tcp 1518149375 192.168.0.127 9 typ host tcptype active generation 0 ufrag l4kk network-id 3 network-cost 10','sdpMid':'video0','sdpMLineIndex':0}}"

/**
* @function				webrtcStateChangedCB
* @parameter			webrtc_h webrtc, webrtc_state_e previous, webrtc_state_e current, void *user_data
* @return				NA
*/
static void webrtcStateChangedCB(webrtc_h webrtc, webrtc_state_e previous, webrtc_state_e current, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function				webrtcErrorCB
* @parameter			webrtc_h webrtc, webrtc_error_e error, webrtc_state_e state, void *user_data
* @return				NA
*/
static void webrtcErrorCB(webrtc_h webrtc, webrtc_error_e error, webrtc_state_e state, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback webrtcErrorCB called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function				webrtcIceCandidateCB
* @parameter			webrtc_h webrtc, const char *candidate, void *user_data
* @return				NA
*/
static void webrtcIceCandidateCB(webrtc_h webrtc, const char *candidate, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback webrtcIceCandidateCB called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function				webrtcNegotiationNeededCB
* @parameter			webrtc_h webrtc, void *user_data
* @return				NA
*/
static void webrtcNegotiationNeededCB(webrtc_h webrtc, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback webrtcNegotiationNeededCB called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function				webrtcPeerConnectionStateChangeCB
* @parameter			webrtc_h webrtc, webrtc_peer_connection_state_e state, void *user_data
* @return				NA
*/
static void webrtcPeerConnectionStateChangeCB(webrtc_h webrtc, webrtc_peer_connection_state_e state, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback webrtcPeerConnectionStateChangeCB called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function				webrtcSignalingStateChangeCB
* @parameter			webrtc_h webrtc, webrtc_signaling_state_e state, void *user_data)
* @return				NA
*/
static void webrtcSignalingStateChangeCB(webrtc_h webrtc, webrtc_signaling_state_e state, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback webrtcSignalingStateChangeCB called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function				webrtcIceGatheringStateChangeCB
* @parameter			webrtc_h webrtc, webrtc_ice_gathering_state_e state, void *user_data
* @return				NA
*/
static void webrtcIceGatheringStateChangeCB(webrtc_h webrtc, webrtc_ice_gathering_state_e state, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback webrtcIceGatheringStateChangeCB called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function				webrtcIceConnectionStateChangeCB
* @parameter			webrtc_h webrtc, webrtc_ice_connection_state_e state, void *user_data
* @return				NA
*/
static void webrtcIceConnectionStateChangeCB(webrtc_h webrtc, webrtc_ice_connection_state_e state, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback webrtcIceConnectionStateChangeCB called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function				webrtcEncodedFrameCB
* @parameter			webrtc_h webrtc, webrtc_media_type_e type, unsigned int track_id, media_packet_h packet, void *user_data
* @return				NA
*/
static void webrtcEncodedFrameCB(webrtc_h webrtc, webrtc_media_type_e type, unsigned int track_id, media_packet_h packet, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback webrtcEncodedFrameCB called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function				webrtcMediaPacketSourceBufferStateChangedCB
* @parameter			unsigned int source_id, webrtc_media_packet_source_buffer_state_e state, void *user_data
* @return				NA
*/
static void webrtcMediaPacketSourceBufferStateChangedCB(unsigned int source_id, webrtc_media_packet_source_buffer_state_e state, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback webrtcMediaPacketSourceBufferStateChangedCB called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function				webrtcDataChannelCB
* @parameter			webrtc_h webrtc, webrtc_data_channel_h channel, void *user_data
* @return				NA
*/
static void webrtcDataChannelCB(webrtc_h webrtc, webrtc_data_channel_h channel, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback webrtcDataChannelCB called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function				webrtcDataChannelOpenCB
* @parameter			webrtc_data_channel_h channel, void *user_data
* @return				NA
*/
static void webrtcDataChannelOpenCB(webrtc_data_channel_h channel, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback webrtcDataChannelOpenCB called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function				webrtcDataChannelMessageCB
* @parameter			webrtc_data_channel_h channel, webrtc_data_channel_type_e type, void *message, void *user_data
* @return				NA
*/
static void webrtcDataChannelMessageCB(webrtc_data_channel_h channel, webrtc_data_channel_type_e type, void *message, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback webrtcDataChannelMessageCB called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function				webrtcDataChannelErrorCB
* @parameter			webrtc_data_channel_h channel, webrtc_error_e error, void *user_data
* @return				NA
*/
static void webrtcDataChannelErrorCB(webrtc_data_channel_h channel, webrtc_error_e error, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback webrtcDataChannelErrorCB called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function				webrtcDataChannelCloseCB
* @parameter			webrtc_data_channel_h channel, void *user_data
* @return				NA
*/
static void webrtcDataChannelCloseCB(webrtc_data_channel_h channel, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback webrtcDataChannelCloseCB called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function				webrtcTrackAddedCB
* @parameter			webrtc_h webrtc, webrtc_media_type_e type, unsigned int track_id, void *user_data
* @return				NA
*/
static void webrtcTrackAddedCB(webrtc_h webrtc, webrtc_media_type_e type, unsigned int track_id, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback webrtcTrackAddedCB called\\n", __LINE__, API_NAMESPACE);
}
/**
 * @function 		ITs_webrtc_callback_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_webrtc_callback_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	g_bWebRTCCreation = false;
	int nRet = webrtc_create(&g_hWebRtcHandle);
	if( nRet != WEBRTC_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] webrtc_create api failed!!!\\n", __LINE__, API_NAMESPACE);
		return;
	}
	if(g_hWebRtcHandle == NULL)
	{
		FPRINTF("[Line : %d][%s] g_hWebRtcHandle is NULL!!!\\n", __LINE__, API_NAMESPACE);
		return;
	}
	g_bWebRTCCreation = true;

	return;
}


/**
 * @function 		ITs_webrtc_callback_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_webrtc_callback_cleanup(void)
{
	if(g_hWebRtcHandle)
	{
		int nRet = webrtc_destroy(g_hWebRtcHandle);
		if( nRet != WEBRTC_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] webrtc_destroy api failed!!!\\n", __LINE__, API_NAMESPACE);
		}
	}
	return;
}

//& purpose: Sets ans Unsets a callback function to be invoked when the WebRTC state is changed.
//& type: auto
/**
* @testcase 			ITc_webrtc_set_unset_state_changed_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets ans Unsets a callback function to be invoked when the WebRTC state is changed.
* @scenario				Sets ans Unsets a callback function to be invoked when the WebRTC state is changed.
* @apicovered			webrtc_set_state_changed_cb,webrtc_unset_state_changed_cb
* @passcase				If webrtc_set_state_changed_cb,webrtc_unset_state_changed_cb is successfull
* @failcase 			If webrtc_set_state_changed_cb,webrtc_unset_state_changed_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_set_unset_state_changed_cb_p(void)
{
	START_TEST;

	int nRet = webrtc_set_state_changed_cb(g_hWebRtcHandle, webrtcStateChangedCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_unset_state_changed_cb(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_unset_state_changed_cb", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Sets and Unsets a callback function to be invoked when an asynchronous operation error occurs.
//& type: auto
/**
* @testcase 			ITc_webrtc_set_unset_error_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Unsets a callback function to be invoked when an asynchronous operation error occurs.
* @scenario				Sets and Unsets a callback function to be invoked when an asynchronous operation error occurs.
* @apicovered			webrtc_set_error_cb,webrtc_unset_error_cb
* @passcase				If webrtc_set_error_cb,webrtc_unset_error_cb is successfull
* @failcase 			If webrtc_set_error_cb,webrtc_unset_error_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_set_unset_error_cb_p(void)
{
	START_TEST;

	int nRet = webrtc_set_error_cb(g_hWebRtcHandle, webrtcErrorCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_error_cb", WebRtcGetError(nRet));

	nRet = webrtc_unset_error_cb(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_unset_error_cb", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Sets and Unsets an ICE candidate callback function to be invoked when the WebRTC needs to send the ICE candidate message to the remote peer.
//& type: auto
/**
* @testcase 			ITc_webrtc_set_unset_ice_candidate_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Unsets an ICE candidate callback function to be invoked when the WebRTC needs to send the ICE candidate message to the remote peer.
* @scenario				Sets and Unsets an ICE candidate callback function to be invoked when the WebRTC needs to send the ICE candidate message to the remote peer.
* @apicovered			webrtc_set_ice_candidate_cb,webrtc_unset_ice_candidate_cb
* @passcase				If webrtc_set_ice_candidate_cb,webrtc_unset_ice_candidate_cb is successfull
* @failcase 			If webrtc_set_ice_candidate_cb,webrtc_unset_ice_candidate_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_set_unset_ice_candidate_cb_p(void)
{
	START_TEST;

	int nRet = webrtc_set_ice_candidate_cb(g_hWebRtcHandle, webrtcIceCandidateCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_unset_ice_candidate_cb(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_unset_ice_candidate_cb", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Sets and Unsets a negotiation needed callback function to be invoked when a change has occurred which requires session negotiation.
//& type: auto
/**
* @testcase 			ITc_webrtc_set_unset_negotiation_needed_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Unsets a negotiation needed callback function to be invoked when a change has occurred which requires session negotiation.
* @scenario				Sets and Unsets a negotiation needed callback function to be invoked when a change has occurred which requires session negotiation.
* @apicovered			webrtc_set_negotiation_needed_cb,webrtc_unset_negotiation_needed_cb
* @passcase				If webrtc_set_negotiation_needed_cb,webrtc_unset_negotiation_needed_cb is successfull
* @failcase 			If webrtc_set_negotiation_needed_cb,webrtc_unset_negotiation_needed_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_set_unset_negotiation_needed_cb_p(void)
{
	START_TEST;

	int nRet = webrtc_set_negotiation_needed_cb(g_hWebRtcHandle, webrtcNegotiationNeededCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_negotiation_needed_cb", WebRtcGetError(nRet));

	nRet = webrtc_unset_negotiation_needed_cb(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_unset_negotiation_needed_cb", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Sets and Unsets a callback function to be invoked when the WebRTC peer connection state is changed.
//& type: auto
/**
* @testcase 			ITc_webrtc_set_unset_peer_connection_state_change_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Unsets a callback function to be invoked when the WebRTC peer connection state is changed.
* @scenario				Sets and Unsets a callback function to be invoked when the WebRTC peer connection state is changed.
* @apicovered			webrtc_set_peer_connection_state_change_cb,webrtc_unset_peer_connection_state_change_cb
* @passcase				If webrtc_set_peer_connection_state_change_cb,webrtc_unset_peer_connection_state_change_cb is successfull
* @failcase 			If webrtc_set_peer_connection_state_change_cb,webrtc_unset_peer_connection_state_change_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_set_unset_peer_connection_state_change_cb_p(void)
{
	START_TEST;

	int nRet = webrtc_set_peer_connection_state_change_cb(g_hWebRtcHandle, webrtcPeerConnectionStateChangeCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_peer_connection_state_change_cb", WebRtcGetError(nRet));

	nRet = webrtc_unset_peer_connection_state_change_cb(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_unset_peer_connection_state_change_cb", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Sets and Unsets the signaling state change callback function.
//& type: auto
/**
* @testcase 			ITc_webrtc_set_unset_signaling_state_change_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Unsets the signaling state change callback function.
* @scenario				Sets and Unsets the signaling state change callback function.
* @apicovered			webrtc_set_signaling_state_change_cb,webrtc_unset_signaling_state_change_cb
* @passcase				If webrtc_set_signaling_state_change_cb,webrtc_unset_signaling_state_change_cb is successfull
* @failcase 			If webrtc_set_signaling_state_change_cb,webrtc_unset_signaling_state_change_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_set_unset_signaling_state_change_cb_p(void)
{
	START_TEST;

	int nRet = webrtc_set_signaling_state_change_cb(g_hWebRtcHandle, webrtcSignalingStateChangeCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_signaling_state_change_cb", WebRtcGetError(nRet));

	nRet = webrtc_unset_signaling_state_change_cb(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_unset_signaling_state_change_cb", WebRtcGetError(nRet));

	return 0;
}

//& purpose:  Sets and Unsets a callback function to be invoked when the WebRTC ICE gathering state is changed.
//& type: auto
/**
* @testcase 			ITc_webrtc_set_unset_ice_gathering_state_change_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Unsets a callback function to be invoked when the WebRTC ICE gathering state is changed.
* @scenario				Sets and Unsets a callback function to be invoked when the WebRTC ICE gathering state is changed.
* @apicovered			webrtc_set_ice_gathering_state_change_cb,webrtc_unset_signaling_state_change_cb
* @passcase				If webrtc_set_ice_gathering_state_change_cb,webrtc_unset_signaling_state_change_cb is successfull
* @failcase 			If webrtc_set_ice_gathering_state_change_cb,webrtc_unset_signaling_state_change_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_set_unset_ice_gathering_state_change_cb_p(void)
{
	START_TEST;

	int nRet = webrtc_set_ice_gathering_state_change_cb(g_hWebRtcHandle, webrtcIceGatheringStateChangeCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_gathering_state_change_cb", WebRtcGetError(nRet));

	nRet = webrtc_unset_ice_gathering_state_change_cb(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_unset_ice_gathering_state_change_cb", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Sets and Unsets a callback function to be invoked when the WebRTC ICE connection state is changed.
//& type: auto
/**
* @testcase 			ITc_webrtc_set_unset_ice_connection_state_change_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Unsets a callback function to be invoked when the WebRTC ICE connection state is changed.
* @scenario				Sets and Unsets a callback function to be invoked when the WebRTC ICE connection state is changed.
* @apicovered			webrtc_set_ice_connection_state_change_cb,webrtc_unset_ice_connection_state_change_cb
* @passcase				If webrtc_set_ice_connection_state_change_cb,webrtc_unset_ice_connection_state_change_cb is successfull
* @failcase 			If webrtc_set_ice_connection_state_change_cb,webrtc_unset_ice_connection_state_change_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_set_unset_ice_connection_state_change_cb_p(void)
{
	START_TEST;

	int nRet = webrtc_set_ice_connection_state_change_cb(g_hWebRtcHandle, webrtcIceConnectionStateChangeCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_connection_state_change_cb", WebRtcGetError(nRet));

	nRet = webrtc_unset_ice_connection_state_change_cb(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_unset_ice_connection_state_change_cb", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Sets and Unsets an encoded audio frame callback function to be invoked when each audio frame is ready to be rendered.
//& type: auto
/**
* @testcase 			ITc_webrtc_set_unset_encoded_audio_frame_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Unsets an encoded audio frame callback function to be invoked when each audio frame is ready to be rendered.
* @scenario				Sets and Unsets an encoded audio frame callback function to be invoked when each audio frame is ready to be rendered.
* @apicovered			webrtc_set_encoded_audio_frame_cb,webrtc_unset_encoded_audio_frame_cb
* @passcase				If webrtc_set_encoded_audio_frame_cb,webrtc_unset_encoded_audio_frame_cb is successfull
* @failcase 			If webrtc_set_encoded_audio_frame_cb,webrtc_unset_encoded_audio_frame_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_set_unset_encoded_audio_frame_cb_p(void)
{
	START_TEST;

	int nRet = webrtc_set_encoded_audio_frame_cb(g_hWebRtcHandle, webrtcEncodedFrameCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_encoded_audio_frame_cb", WebRtcGetError(nRet));

	nRet = webrtc_unset_encoded_audio_frame_cb(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_unset_encoded_audio_frame_cb", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Sets and Unsets an encoded video frame callback function to be invoked when each video frame is ready to be rendered.
//& type: auto
/**
* @testcase 			ITc_webrtc_set_unset_encoded_video_frame_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Unsets an encoded video frame callback function to be invoked when each video frame is ready to be rendered.
* @scenario				Sets and Unsets an encoded video frame callback function to be invoked when each video frame is ready to be rendered.
* @apicovered			webrtc_set_encoded_video_frame_cb,webrtc_unset_encoded_video_frame_cb
* @passcase				If webrtc_set_encoded_video_frame_cb,webrtc_unset_encoded_video_frame_cb is successfull
* @failcase 			If webrtc_set_encoded_video_frame_cb,webrtc_unset_encoded_video_frame_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_set_unset_encoded_video_frame_cb_p(void)
{
	START_TEST;

	int nRet = webrtc_set_encoded_video_frame_cb(g_hWebRtcHandle, webrtcEncodedFrameCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_encoded_video_frame_cb", WebRtcGetError(nRet));

	nRet = webrtc_unset_encoded_video_frame_cb(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_unset_encoded_video_frame_cb", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Sets and Unsets a callback function to be invoked when the buffer state of media packet source is changed.
//& type: auto
/**
* @testcase 			ITc_webrtc_media_packet_source_set_unset_buffer_state_changed_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Unsets a callback function to be invoked when the buffer state of media packet source is changed.
* @scenario				Sets and Unsets a callback function to be invoked when the buffer state of media packet source is changed.
* @apicovered			webrtc_media_packet_source_set_buffer_state_changed_cb,webrtc_media_packet_source_unset_buffer_state_changed_cb
* @passcase				If webrtc_media_packet_source_set_buffer_state_changed_cb,webrtc_media_packet_source_unset_buffer_state_changed_cb is successfull
* @failcase 			If webrtc_media_packet_source_set_buffer_state_changed_cb,webrtc_media_packet_source_unset_buffer_state_changed_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_media_packet_source_set_unset_buffer_state_changed_cb_p(void)
{
	START_TEST;
	unsigned int nId;

	int nRet = webrtc_add_media_source(g_hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_MEDIA_PACKET, &nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

	nRet = webrtc_media_packet_source_set_buffer_state_changed_cb(g_hWebRtcHandle, nId, webrtcMediaPacketSourceBufferStateChangedCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_media_packet_source_set_buffer_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_media_packet_source_unset_buffer_state_changed_cb(g_hWebRtcHandle, nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_media_packet_source_unset_buffer_state_changed_cb", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Sets and Unsets a data channel callback function to be invoked when the data channel is created to the connection by the remote peer.
//& type: auto
/**
* @testcase 			ITc_webrtc_set_unset_data_channel_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Unsets a data channel callback function to be invoked when the data channel is created to the connection by the remote peer.
* @scenario				Sets and Unsets a data channel callback function to be invoked when the data channel is created to the connection by the remote peer.
* @apicovered			webrtc_set_data_channel_cb,webrtc_unset_data_channel_cb
* @passcase				If webrtc_set_data_channel_cb,webrtc_unset_data_channel_cb is successfull
* @failcase 			If webrtc_set_data_channel_cb,webrtc_unset_data_channel_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_set_unset_data_channel_cb_p(void)
{
	START_TEST;

	int nRet = webrtc_set_data_channel_cb(g_hWebRtcHandle, webrtcDataChannelCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_data_channel_cb", WebRtcGetError(nRet));

	nRet = webrtc_unset_data_channel_cb(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_unset_data_channel_cb", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Sets and Unsets a data channel open callback function to be invoked when the data channel's underlying data transport is established.
//& type: auto
/**
* @testcase 			ITc_webrtc_data_channel_set_unset_open_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Unsets a data channel open callback function to be invoked when the data channel's underlying data transport is established.
* @scenario				Sets and Unsets a data channel open callback function to be invoked when the data channel's underlying data transport is established.
* @apicovered			webrtc_data_channel_set_open_cb,webrtc_data_channel_unset_open_cb
* @passcase				If webrtc_data_channel_set_open_cb,webrtc_data_channel_unset_open_cb is successfull
* @failcase 			If webrtc_data_channel_set_open_cb,webrtc_data_channel_unset_open_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_data_channel_set_unset_open_cb_p(void)
{
	START_TEST;
	webrtc_data_channel_h hChannel;

	int nRet = webrtc_create_data_channel(g_hWebRtcHandle, "test channel", NULL, &hChannel);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_data_channel", WebRtcGetError(nRet));
	CHECK_HANDLE(hChannel,"webrtc_create_data_channel");

	nRet = webrtc_data_channel_set_open_cb(hChannel, webrtcDataChannelOpenCB, NULL);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_data_channel_set_open_cb", WebRtcGetError(nRet),webrtc_destroy_data_channel(hChannel));

	nRet = webrtc_data_channel_unset_open_cb(hChannel);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_data_channel_unset_open_cb", WebRtcGetError(nRet),webrtc_destroy_data_channel(hChannel));

	nRet = webrtc_destroy_data_channel(hChannel);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy_data_channel", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Sets and Unsets a data channel message callback function to be invoked when a message is received from the remote peer.
//& type: auto
/**
* @testcase 			ITc_webrtc_data_channel_set_unset_message_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Unsets a data channel message callback function to be invoked when a message is received from the remote peer.
* @scenario				Sets and Unsets a data channel message callback function to be invoked when a message is received from the remote peer.
* @apicovered			webrtc_data_channel_set_message_cb,webrtc_data_channel_unset_message_cb
* @passcase				If webrtc_data_channel_set_message_cb,webrtc_data_channel_unset_message_cb is successfull
* @failcase 			If webrtc_data_channel_set_message_cb,webrtc_data_channel_unset_message_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_data_channel_set_unset_message_cb_p(void)
{
	START_TEST;
	webrtc_data_channel_h hChannel;

	int nRet = webrtc_create_data_channel(g_hWebRtcHandle, "test channel", NULL, &hChannel);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_data_channel", WebRtcGetError(nRet));
	CHECK_HANDLE(hChannel,"webrtc_create_data_channel");

	nRet = webrtc_data_channel_set_message_cb(hChannel, webrtcDataChannelMessageCB, NULL);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_data_channel_set_message_cb", WebRtcGetError(nRet),webrtc_destroy_data_channel(hChannel));

	nRet = webrtc_data_channel_unset_message_cb(hChannel);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_data_channel_unset_message_cb", WebRtcGetError(nRet),webrtc_destroy_data_channel(hChannel));

	nRet = webrtc_destroy_data_channel(hChannel);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy_data_channel", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Sets and Unsets a data channel error callback function to be invoked when an error occurs on the data channel.
//& type: auto
/**
* @testcase 			ITc_webrtc_data_channel_set_unset_error_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Unsets a data channel error callback function to be invoked when an error occurs on the data channel.
* @scenario				Sets and Unsets a data channel error callback function to be invoked when an error occurs on the data channel.
* @apicovered			webrtc_data_channel_set_error_cb,webrtc_data_channel_unset_error_cb
* @passcase				If webrtc_data_channel_set_error_cb,webrtc_data_channel_unset_error_cb is successfull
* @failcase 			If webrtc_data_channel_set_error_cb,webrtc_data_channel_unset_error_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_data_channel_set_unset_error_cb_p(void)
{
	START_TEST;
	webrtc_data_channel_h hChannel;

	int nRet = webrtc_create_data_channel(g_hWebRtcHandle, "test channel", NULL, &hChannel);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_data_channel", WebRtcGetError(nRet));
	CHECK_HANDLE(hChannel,"webrtc_create_data_channel");

	nRet = webrtc_data_channel_set_error_cb(hChannel, webrtcDataChannelErrorCB, NULL);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_data_channel_set_error_cb", WebRtcGetError(nRet),webrtc_destroy_data_channel(hChannel));

	nRet = webrtc_data_channel_unset_error_cb(hChannel);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_data_channel_unset_error_cb", WebRtcGetError(nRet),webrtc_destroy_data_channel(hChannel));

	nRet = webrtc_destroy_data_channel(hChannel);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy_data_channel", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Sets and Unsets a data channel close callback function to be invoked when the data channel has closed down.
//& type: auto
/**
* @testcase 			ITc_webrtc_data_channel_set_unset_close_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Unsets a data channel close callback function to be invoked when the data channel has closed down.
* @scenario				Sets and Unsets a data channel close callback function to be invoked when the data channel has closed down.
* @apicovered			webrtc_data_channel_set_close_cb,webrtc_data_channel_unset_close_cb
* @passcase				If webrtc_data_channel_set_close_cb,webrtc_data_channel_unset_close_cb is successfull
* @failcase 			If webrtc_data_channel_set_close_cb,webrtc_data_channel_unset_close_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_data_channel_set_unset_close_cb_p(void)
{
	START_TEST;
	webrtc_data_channel_h hChannel;

	int nRet = webrtc_create_data_channel(g_hWebRtcHandle, "test channel", NULL, &hChannel);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_data_channel", WebRtcGetError(nRet));
	CHECK_HANDLE(hChannel,"webrtc_create_data_channel");

	nRet = webrtc_data_channel_set_close_cb(hChannel, webrtcDataChannelCloseCB, NULL);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_data_channel_set_close_cb", WebRtcGetError(nRet),webrtc_destroy_data_channel(hChannel));

	nRet = webrtc_data_channel_unset_close_cb(hChannel);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_data_channel_unset_close_cb", WebRtcGetError(nRet),webrtc_destroy_data_channel(hChannel));

	nRet = webrtc_destroy_data_channel(hChannel);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy_data_channel", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Sets and Unsets a track added callback function to be invoked when a new track has been added to the WebRTC.
//& type: auto
/**
* @testcase 			ITc_webrtc_set_unset_track_added_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Unsets a track added callback function to be invoked when a new track has been added to the WebRTC.
* @scenario				Sets and Unsets a track added callback function to be invoked when a new track has been added to the WebRTC.
* @apicovered			webrtc_set_track_added_cb,webrtc_unset_track_added_cb
* @passcase				If webrtc_set_track_added_cb,webrtc_unset_track_added_cb is successfull
* @failcase 			If webrtc_set_track_added_cb,webrtc_unset_track_added_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_set_unset_track_added_cb_p(void)
{
	START_TEST;

	int nRet = webrtc_set_track_added_cb(g_hWebRtcHandle, webrtcTrackAddedCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_track_added_cb", WebRtcGetError(nRet));

	nRet = webrtc_unset_track_added_cb(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_unset_track_added_cb", WebRtcGetError(nRet));

	return 0;
}
/** @} */
/** @} */
