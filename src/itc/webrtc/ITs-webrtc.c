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

#define TEST_DATA_CHANNEL_LABEL "test data channel"
#define TEST_STRING_DATA        "test string"
#define TEST_BUFFER_SIZE        16
#define TEST_FPS		        30
char g_test_buffer[TEST_BUFFER_SIZE] = {'t', 'e', 's', 't', 'b', 'u', 'f', '\0', };

#include "ITs-webrtc-common.h"
#include <Elementary.h>
static Evas_Object *g_win = NULL;
static void winDeleteCB(void *data, Evas_Object *obj, void *event)
{
	elm_exit();
}

static void createWindow()
{
	int w = 0;
	int h = 0;

	g_win = elm_win_util_standard_add("webrtc_itc", "webrtc_itc");
	if (g_win) {
		elm_win_borderless_set(g_win, EINA_TRUE);
		evas_object_smart_callback_add(g_win, "delete,request", winDeleteCB, NULL);
		elm_win_screen_size_get(g_win, NULL, NULL, &w, &h);
		evas_object_resize(g_win, w, h);
		elm_win_autodel_set(g_win, EINA_TRUE);
	}

}

static void destroyWindow()
{

	if (g_win) {
		evas_object_del(g_win);
		g_win = NULL;
	}
}

//& set: Webrtc

/** @addtogroup itc-webrtc
*  @ingroup itc
*  @{
*/
#define TEST_ICE_CANDIDATE     "{'ice':{'candidate':'candidate:3600539631 1 tcp 1518149375 192.168.0.127 9 typ host tcptype active generation 0 ufrag l4kk network-id 3 network-cost 10','sdpMid':'video0','sdpMLineIndex':0}}"

/**
* @function             webrtcStatsCB
* @parameter            webrtc_stats_type_e type, const webrtc_stats_prop_info_s *prop_info, void *user_data
* @return               @c true to continue with the next iteration of the loop, otherwise @c false to break out of the loop
*/
static bool webrtcStatsCB(webrtc_stats_type_e type, const webrtc_stats_prop_info_s *prop_info, void *user_data)
{
	callback_data *cb_data = (callback_data *)user_data;
	FPRINTF("[Line : %d][%s] Callback webrtcStatsCB called type[0x%x] prop[%s, 0x%08x, value:%d]\\n", __LINE__, API_NAMESPACE, type, prop_info->name, prop_info->prop, prop_info->type);
	if (!cb_data)
		return false;
	cb_data->is_invoked = true;
	QUIT_LOOP(cb_data->mainloop);
	return false;
}

/**
* @function				webrtcSessionDescriptionCreatedCB
* @parameter			webrtc_h webrtc, const char *description, void *user_data
* @return				NA
*/
static void webrtcSessionDescriptionCreatedCB(webrtc_h webrtc, const char *description, void *user_data)
{
	callback_data *cb_data = (callback_data *)user_data;

	FPRINTF("[Line : %d][%s] Callback webrtcSessionDescriptionCreatedCB called\\n", __LINE__, API_NAMESPACE);

	if (!cb_data)
		return;
	cb_data->is_invoked = true;
	QUIT_LOOP(cb_data->mainloop);
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
* @function				webrtcIceCandidateCB
* @parameter			webrtc_h webrtc, const char *candidate, void *user_data
* @return				NA
*/
static void webrtcIceCandidateCB(webrtc_h webrtc, const char *candidate, void *user_data)
{
	GList **candidates = (GList **)user_data;

	FPRINTF("[Line : %d][%s] Callback webrtcIceCandidateCB called\\n", __LINE__, API_NAMESPACE);
	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] webrtc[%p], candidate[%p]", __FUNCTION__, __LINE__, webrtc, candidates);

	if (candidates)
		*candidates = g_list_append(*candidates, strdup(candidate));
}

/**
* @function				webrtcStateChangedCB
* @parameter			webrtc_h webrtc, webrtc_state_e previous, webrtc_state_e current, void *user_data
* @return				NA
*/
static void webrtcStateChangedCB(webrtc_h webrtc, webrtc_state_e previous, webrtc_state_e current, void *user_data)
{
	callback_data *cb_data = (callback_data *)user_data;

	FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB called webrtc[%p], state[%d -> %d]\\n", __LINE__, API_NAMESPACE, webrtc, previous, current);
	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] webrtc[%p], state[%d -> %d]", __FUNCTION__, __LINE__, webrtc, previous, current);

	if (!cb_data)
		return;
	cb_data->is_invoked = true;
	QUIT_LOOP(cb_data->mainloop);
}

/**
* @function				webrtcTrackAddedCB
* @parameter			webrtc_h webrtc, webrtc_media_type_e type, unsigned int track_id, void *user_data
* @return				NA
*/
static void webrtcTrackAddedCB(webrtc_h webrtc, webrtc_media_type_e type, unsigned int track_id, void *user_data)
{
	callback_data *cb_data = (callback_data *)user_data;

	FPRINTF("[Line : %d][%s] Callback webrtcTrackAddedCB called\\n", __LINE__, API_NAMESPACE);
	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] webrtc[%p], track_id[%u]", __FUNCTION__, __LINE__, webrtc, track_id);

	if (!cb_data)
		return;
	cb_data->is_invoked = true;
	QUIT_LOOP(cb_data->mainloop);
}

/**
* @function				webrtcSignalingStateChangeCB
* @parameter			webrtc_h webrtc, webrtc_signaling_state_e state, void *user_data
* @return				NA
*/
static void webrtcSignalingStateChangeCB(webrtc_h webrtc, webrtc_signaling_state_e state, void *user_data)
{
	callback_data *cb_data = (callback_data *)user_data;

	FPRINTF("[Line : %d][%s] Callback webrtcSignalingStateChangeCB called\\n", __LINE__, API_NAMESPACE);
	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] webrtc[%p], state[%d]", __FUNCTION__, __LINE__, webrtc, state);

	if (!cb_data || state != WEBRTC_SIGNALING_STATE_HAVE_REMOTE_OFFER)
		return;

	cb_data->is_invoked = true;
	QUIT_LOOP(cb_data->mainloop);
}

static void __foreach_ice_candidate(gpointer data, gpointer user_data)
{
	webrtc_add_ice_candidate((webrtc_h)user_data, (const char *)data);
	FPRINTF("[Line : %d][%s] add ice candidate: %s\\n", __LINE__, API_NAMESPACE, (const char *)data);
	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] add ice candidate: %s", __FUNCTION__, __LINE__, (const char *)data);
}

/**
* @function				webrtcIceGatheringStateChangeCB
* @parameter			webrtc_h webrtc, webrtc_ice_gathering_state_e state, void *user_data
* @return				NA
*/
static void webrtcIceGatheringStateChangeCB(webrtc_h webrtc, webrtc_ice_gathering_state_e state, void *user_data)
{
	callback_data *cb_data = (callback_data *)user_data;

	FPRINTF("[Line : %d][%s] Callback webrtcIceGatheringStateChangeCB called, state[%d]\\n", __LINE__, API_NAMESPACE, state);
	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] webrtc[%p], state[%d]", __FUNCTION__, __LINE__, webrtc, state);

	if (!cb_data)
		return;
	if (state != WEBRTC_ICE_GATHERING_STATE_COMPLETE)
		return;
	cb_data->is_invoked = true;
	QUIT_LOOP(cb_data->mainloop);
}

/**
* @function				webrtcDataChannelOpenCB
* @parameter			webrtc_data_channel_h channel, void *user_data
* @return				NA
*/
static void webrtcDataChannelOpenCB(webrtc_data_channel_h channel, void *user_data)
{
	callback_data *cb_data = (callback_data *)user_data;

	FPRINTF("[Line : %d][%s] Callback webrtcDataChannelOpenCB called\\n", __LINE__, API_NAMESPACE);
	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] channel[%p]", __FUNCTION__, __LINE__, channel);

	if (!cb_data)
		return;
	cb_data->is_invoked = true;
	QUIT_LOOP(cb_data->mainloop);
}

/**
* @function				webrtcDataChannelCloseCB
* @parameter			webrtc_data_channel_h channel, void *user_data
* @return				NA
*/
static void webrtcDataChannelCloseCB(webrtc_data_channel_h channel, void *user_data)
{
	callback_data *cb_data = (callback_data *)user_data;

	FPRINTF("[Line : %d][%s] Callback webrtcDataChannelCloseCB called\\n", __LINE__, API_NAMESPACE);
	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] channel[%p]", __FUNCTION__, __LINE__, channel);

	if (!cb_data)
		return;
	cb_data->is_invoked = true;
	QUIT_LOOP(cb_data->mainloop);
}

/**
* @function				webrtcDataChannelMessageCB
* @parameter			webrtc_data_channel_h channel, webrtc_data_channel_type_e type, void *message, void *user_data
* @return				NA
*/
static void webrtcDataChannelMessageCB(webrtc_data_channel_h channel, webrtc_data_channel_type_e type, void *message, void *user_data)
{
	callback_data *cb_data = (callback_data *)user_data;

	FPRINTF("[Line : %d][%s] Callback webrtcDataChannelMessageCB called\\n", __LINE__, API_NAMESPACE);
	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] channel[%p], type[%d], message[%p]", __FUNCTION__, __LINE__, channel, type, message);

	if (!cb_data || !message)
		return;

	if (type == WEBRTC_DATA_CHANNEL_TYPE_STRING) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] channel[%p], received string message[%s]", __FUNCTION__, __LINE__, channel, (const char *)message);
		if (!strcmp(TEST_STRING_DATA, message)) {
			cb_data->is_invoked = true;
			QUIT_LOOP(cb_data->mainloop);
		}
	} else if (type == WEBRTC_DATA_CHANNEL_TYPE_BYTES) {
		webrtc_bytes_data_h *data = message;
		const char *data_p;
		unsigned long size;
		int nRet = webrtc_get_data(data, &data_p, &size);
		PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_get_data", WebRtcGetError(nRet));

		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] channel[%p], received bytes message[%s] size[%lu]", __FUNCTION__, __LINE__, channel, data_p, size);
		if (!memcmp(g_test_buffer, data_p, TEST_BUFFER_SIZE)) {
			cb_data->is_invoked = true;
			QUIT_LOOP(cb_data->mainloop);
		}
	}
}

/**
* @function				webrtcDataChannelCB
* @parameter			webrtc_h webrtc, webrtc_data_channel_h channel, void *user_data
* @return				NA
*/
static void webrtcDataChannelCB(webrtc_h webrtc, webrtc_data_channel_h channel, void *user_data)
{
	int nRet;

	FPRINTF("[Line : %d][%s] Callback webrtcDataChannelCB called\\n", __LINE__, API_NAMESPACE);
	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] webrtc[%p], channel[%p]", __FUNCTION__, __LINE__, webrtc, channel);

	nRet = webrtc_data_channel_set_open_cb(channel, webrtcDataChannelOpenCB, user_data);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_data_channel_set_open_cb", WebRtcGetError(nRet));

	nRet = webrtc_data_channel_set_message_cb(channel, webrtcDataChannelMessageCB, user_data);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_data_channel_set_message_cb", WebRtcGetError(nRet));

	nRet = webrtc_data_channel_set_close_cb(channel, webrtcDataChannelCloseCB, user_data);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_data_channel_set_close_cb", WebRtcGetError(nRet));
}

/**
* @function				webrtcTurnServerCB
* @parameter			const char *turn_server, void *user_data
* @return				NA
*/
static bool webrtcTurnServerCB(const char *turn_server, void *user_data)
{
	int *nCount = (int*)user_data;
	FPRINTF("[Line : %d][%s] Callback webrtcTurnServerCB called\\n", __LINE__, API_NAMESPACE);
	(*nCount)--;

	return true;
}

/**
* @function				dataChannelBufferedAmountLowCB
* @parameter			webrtc_data_channel_h channel, void *user_data
* @return				NA
*/
static void dataChannelBufferedAmountLowCB(webrtc_data_channel_h channel, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback checking\\n", __LINE__, API_NAMESPACE);
}

/**
 * @function 		ITs_webrtc_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_webrtc_startup(void)
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
 * @function 		ITs_webrtc_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_webrtc_cleanup(void)
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

//& purpose: Creates and Destroy an instance of WebRTC
//& type: auto
/**
* @testcase 			ITc_webrtc_create_destroy_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates and Destroy an instance of WebRTC
* @scenario				Creates and Destroy an instance of WebRTC
* @apicovered			webrtc_create,webrtc_destroy
* @passcase				If webrtc_create,webrtc_destroy is successful
* @failcase 			If webrtc_create,webrtc_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_create_destroy_p(void)
{
	START_TEST;

	int nRet = webrtc_destroy(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy", WebRtcGetError(nRet));

	nRet = webrtc_create(&g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create", WebRtcGetError(nRet));
	CHECK_HANDLE(g_hWebRtcHandle, "webrtc_create");

	nRet = webrtc_destroy(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy", WebRtcGetError(nRet));

	nRet = webrtc_create(&g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create", WebRtcGetError(nRet));
	CHECK_HANDLE(g_hWebRtcHandle, "webrtc_create");

	return 0;
}

//& purpose: Starts and Stops the WebRTC.
//& type: auto
/**
* @testcase 			ITc_webrtc_start_stop_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Starts and Stops the WebRTC.
* @scenario				Starts and Stops the WebRTC.
* @apicovered			webrtc_start,webrtc_stop
* @passcase				If webrtc_start,webrtc_stop is successful
* @failcase 			If webrtc_start,webrtc_stop fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_start_stop_p(void)
{
	START_TEST;
	callback_data cb_data = { .mainloop = NULL, .is_invoked = false };

	int nRet = webrtc_set_ice_candidate_cb(g_hWebRtcHandle, webrtcIceCandidateCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(g_hWebRtcHandle, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_start(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = webrtc_stop(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Gets the WebRTC state.
//& type: auto
/**
* @testcase 			ITc_webrtc_get_state_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the WebRTC state.
* @scenario				Gets the WebRTC state.
* @apicovered			webrtc_get_state
* @passcase				If webrtc_get_state is successful
* @failcase 			If webrtc_get_state fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_get_state_p(void)
{
	START_TEST;
	webrtc_state_e eGetState;

	int nRet = webrtc_get_state(g_hWebRtcHandle, &eGetState);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_get_state", WebRtcGetError(nRet));
	if(eGetState != WEBRTC_STATE_IDLE)
	{
		FPRINTF("[Line : %d][%s] eGetState is not idle\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose:  Adds and Removes a media source.
//& type: auto
/**
* @testcase 			ITc_webrtc_add_remove_media_source_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Adds and Removes a media source.
* @scenario				Adds and Removes a media source.
* @apicovered			webrtc_add_media_source, webrtc_remove_media_source
* @passcase				If webrtc_add_media_source, webrtc_remove_media_source is successful
* @failcase 			If webrtc_add_media_source,webrtc_remove_media_source fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_add_remove_media_source_p(void)
{
	START_TEST;
	unsigned int nId;

	int nRet = webrtc_add_media_source(g_hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_MIC, &nId);
	if (nRet == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] microphone feature is not supported, skip it", __FUNCTION__, __LINE__);
		return 0;
	}
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

	nRet = webrtc_remove_media_source(g_hWebRtcHandle, nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_remove_media_source", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Gets the peer connection state.
//& type: auto
/**
* @testcase 			ITc_webrtc_get_peer_connection_state_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the peer connection state.
* @scenario				Gets the peer connection state.
* @apicovered			webrtc_get_peer_connection_state
* @passcase				If webrtc_get_peer_connection_state is successful
* @failcase 			If webrtc_get_peer_connection_state fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_get_peer_connection_state_p(void)
{
	START_TEST;
	webrtc_peer_connection_state_e eState;

	int nRet = webrtc_get_peer_connection_state(g_hWebRtcHandle, &eState);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_get_peer_connection_state", WebRtcGetError(nRet));
	if(eState != WEBRTC_PEER_CONNECTION_STATE_NEW)
	{
		FPRINTF("[Line : %d][%s] eState is not new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets the signaling state.
//& type: auto
/**
* @testcase 			ITc_webrtc_get_signaling_state_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the signaling state.
* @scenario				Gets the signaling state.
* @apicovered			webrtc_get_signaling_state
* @passcase				If webrtc_get_signaling_state is successful
* @failcase 			If webrtc_get_signaling_state fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_get_signaling_state_p(void)
{
	START_TEST;
	webrtc_signaling_state_e eState;

	int nRet = webrtc_get_signaling_state(g_hWebRtcHandle, &eState);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_get_signaling_state", WebRtcGetError(nRet));
	if(eState != WEBRTC_SIGNALING_STATE_STABLE)
	{
		FPRINTF("[Line : %d][%s] eState is not stable\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets the ICE gathering state.
//& type: auto
/**
* @testcase 			ITc_webrtc_get_ice_gathering_state_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the ICE gathering state.
* @scenario				Gets the ICE gathering state.
* @apicovered			webrtc_get_ice_gathering_state
* @passcase				If webrtc_get_ice_gathering_state is successful
* @failcase 			If webrtc_get_ice_gathering_state fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_get_ice_gathering_state_p(void)
{
	START_TEST;
	webrtc_ice_gathering_state_e eState;

	int nRet = webrtc_get_ice_gathering_state(g_hWebRtcHandle, &eState);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_get_ice_gathering_state", WebRtcGetError(nRet));
	if(eState != WEBRTC_ICE_GATHERING_STATE_NEW)
	{
		FPRINTF("[Line : %d][%s] eState is not new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets the ICE connection state
//& type: auto
/**
* @testcase 			ITc_webrtc_get_ice_connection_state_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the ICE connection state
* @scenario				Gets the ICE connection state
* @apicovered			webrtc_get_ice_connection_state
* @passcase				If webrtc_get_ice_connection_state is successful
* @failcase 			If webrtc_get_ice_connection_state fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_get_ice_connection_state_p(void)
{
	START_TEST;
	webrtc_ice_connection_state_e eState;

	int nRet = webrtc_get_ice_connection_state(g_hWebRtcHandle, &eState);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_get_ice_connection_state", WebRtcGetError(nRet));
	if(eState != WEBRTC_ICE_CONNECTION_STATE_NEW)
	{
		FPRINTF("[Line : %d][%s] eState is not new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Sets and Gets the transceiver direction to the media source with specified media type.
//& type: auto
/**
* @testcase 			ITc_webrtc_media_source_set_get_transceiver_direction_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets the transceiver direction to the media source with specified media type.
* @scenario				Sets and Gets the transceiver direction to the media source with specified media type.
* @apicovered			webrtc_media_source_set_transceiver_direction,webrtc_media_source_get_transceiver_direction
* @passcase				If webrtc_media_source_set_transceiver_direction,webrtc_media_source_get_transceiver_direction is successful
* @failcase 			If webrtc_media_source_set_transceiver_direction,webrtc_media_source_get_transceiver_direction fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_media_source_set_get_transceiver_direction_p(void)
{
	START_TEST;
	unsigned int nId;
	webrtc_transceiver_direction_e eGetDirection;

	int nRet = webrtc_add_media_source(g_hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

	nRet = webrtc_media_source_set_transceiver_direction(g_hWebRtcHandle, nId, WEBRTC_MEDIA_TYPE_AUDIO, WEBRTC_TRANSCEIVER_DIRECTION_RECVONLY);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_media_source_set_transceiver_direction", WebRtcGetError(nRet));

	nRet = webrtc_media_source_get_transceiver_direction(g_hWebRtcHandle, nId, WEBRTC_MEDIA_TYPE_AUDIO, &eGetDirection);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_media_source_get_transceiver_direction", WebRtcGetError(nRet));
	if(eGetDirection != WEBRTC_TRANSCEIVER_DIRECTION_RECVONLY)
	{
		FPRINTF("[Line : %d][%s] direction set get mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Sets and Gets pause to the media source.
//& type: auto
/**
* @testcase 			ITc_webrtc_media_source_set_get_pause_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets pause to the media source.
* @scenario				Sets and Gets pause to the media source.
* @apicovered			webrtc_media_source_set_pause,webrtc_media_source_get_pause
* @passcase				If webrtc_media_source_set_pause,webrtc_media_source_get_pause is successful
* @failcase 			If webrtc_media_source_set_pause,webrtc_media_source_get_pause fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_media_source_set_get_pause_p(void)
{
	START_TEST;
	unsigned int nId;
	bool bGetPause, bSetPause = true;

	int nRet = webrtc_add_media_source(g_hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

	nRet = webrtc_media_source_set_pause(g_hWebRtcHandle, nId, WEBRTC_MEDIA_TYPE_AUDIO, bSetPause);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_media_source_set_pause", WebRtcGetError(nRet));

	nRet = webrtc_media_source_get_pause(g_hWebRtcHandle, nId, WEBRTC_MEDIA_TYPE_AUDIO, &bGetPause);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_media_source_get_pause", WebRtcGetError(nRet));
	if(bSetPause != bGetPause)
	{
		FPRINTF("[Line : %d][%s] pause set get mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Sets and Gets mute to the media source.
//& type: auto
/**
* @testcase 			ITc_webrtc_media_source_set_get_mute_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets mute to the media source.
* @scenario				Sets and Gets mute to the media source.
* @apicovered			webrtc_media_source_set_mute,webrtc_media_source_get_mute
* @passcase				If webrtc_media_source_set_mute,webrtc_media_source_get_mute is successful
* @failcase 			If webrtc_media_source_set_mute,webrtc_media_source_get_mute fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_media_source_set_get_mute_p(void)
{
	START_TEST;
	unsigned int nId;
	bool bGetMute, bSetMute = true;
	int nRet;
	int i;
	webrtc_media_source_type_e valid_types[] = {
		WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST,
		WEBRTC_MEDIA_SOURCE_TYPE_CAMERA,
		WEBRTC_MEDIA_SOURCE_TYPE_SCREEN,
	};

	for (i = 0; i < sizeof(valid_types) / sizeof(valid_types[0]); i++) {
		nRet = webrtc_add_media_source(g_hWebRtcHandle, valid_types[i], &nId);
		if (nRet == WEBRTC_ERROR_NOT_SUPPORTED) {
			dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] camera feature is not supported, skip it", __FUNCTION__, __LINE__);
			continue;
		}
		PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

		nRet = webrtc_media_source_set_mute(g_hWebRtcHandle, nId, WEBRTC_MEDIA_TYPE_VIDEO, bSetMute);
		PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_media_source_set_mute", WebRtcGetError(nRet));

		nRet = webrtc_media_source_get_mute(g_hWebRtcHandle, nId, WEBRTC_MEDIA_TYPE_VIDEO, &bGetMute);
		PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_media_source_get_mute", WebRtcGetError(nRet));
		if (bSetMute != bGetMute) {
			FPRINTF("[Line : %d][%s] mute set get mismatch\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	return 0;
}

//& purpose: Sets and Gets the video resolution of the media source.
//& type: auto
/**
* @testcase 			ITc_webrtc_media_source_set_get_video_resolution_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets the video resolution of the media source.
* @scenario				Sets and Gets the video resolution of the media source.
* @apicovered			webrtc_media_source_set_video_resolution,webrtc_media_source_get_video_resolution
* @passcase				If webrtc_media_source_set_video_resolution,webrtc_media_source_get_video_resolution is successful
* @failcase 			If webrtc_media_source_set_video_resolution,webrtc_media_source_get_video_resolution fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_media_source_set_get_video_resolution_p(void)
{
	START_TEST;
	unsigned int nId;
	int nSetWidth = 640, nSetHeight = 640;
	int nGetHeight, nGetWidth;

	int nRet = webrtc_add_media_source(g_hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

	nRet = webrtc_media_source_set_video_resolution(g_hWebRtcHandle, nId, nSetWidth, nSetHeight);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_media_source_set_video_resolution", WebRtcGetError(nRet));

	nRet = webrtc_media_source_get_video_resolution(g_hWebRtcHandle, nId, &nGetWidth, &nGetHeight);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_media_source_get_video_resolution", WebRtcGetError(nRet));
	if(nSetWidth != nGetWidth)
	{
		FPRINTF("[Line : %d][%s] width set get mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(nSetHeight != nGetHeight)
	{
		FPRINTF("[Line : %d][%s] height set get mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Sets the mic source's sound manager stream information.
//& type: auto
/**
* @testcase 			ITc_webrtc_mic_source_set_sound_stream_info_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets the mic source's sound manager stream information.
* @scenario				Sets the mic source's sound manager stream information.
* @apicovered			webrtc_mic_source_set_sound_stream_info
* @passcase				If webrtc_mic_source_set_sound_stream_info is successful
* @failcase 			If webrtc_mic_source_set_sound_stream_info fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_mic_source_set_sound_stream_info_p(void)
{
	START_TEST;
	unsigned int nId;
	sound_stream_info_h hStreamInfo;

	int nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, NULL, NULL, &hStreamInfo);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "sound_manager_create_stream_information", WebRtcGetError(nRet));
	CHECK_HANDLE(hStreamInfo, "sound_manager_create_stream_information");

	nRet = webrtc_add_media_source(g_hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_MIC, &nId);
	if (nRet == WEBRTC_ERROR_NOT_SUPPORTED) {
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] microphone feature is not supported, skip it", __FUNCTION__, __LINE__);
		sound_manager_destroy_stream_information(hStreamInfo);
		return 0;
	}
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet),sound_manager_destroy_stream_information(hStreamInfo));

	nRet = webrtc_mic_source_set_sound_stream_info(g_hWebRtcHandle, nId, hStreamInfo);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_mic_source_set_sound_stream_info", WebRtcGetError(nRet),sound_manager_destroy_stream_information(hStreamInfo));

	nRet = sound_manager_destroy_stream_information(hStreamInfo);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Sets media format to the media packet source.
//& type: auto
/**
* @testcase 			ITc_webrtc_media_packet_source_set_format_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets media format to the media packet source.
* @scenario				Sets media format to the media packet source.
* @apicovered			webrtc_media_packet_source_set_format
* @passcase				If webrtc_media_packet_source_set_format is successful
* @failcase 			If webrtc_media_packet_source_set_format fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_media_packet_source_set_format_p(void)
{
	START_TEST;
	unsigned int nId;
	media_format_h hMediaFormat;
	int nChannel = 1, nSampleRate = 8000 , nAudioBit = 16;

	int nRet = media_format_create(&hMediaFormat);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "media_format_create", WebRtcGetError(nRet));
	CHECK_HANDLE(hMediaFormat, "media_format_create");

	nRet = webrtc_add_media_source(g_hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_MEDIA_PACKET, &nId);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet),media_format_unref(hMediaFormat));

	nRet = media_format_set_audio_mime(hMediaFormat, MEDIA_FORMAT_PCM_S16LE);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "media_format_set_audio_mime", WebRtcGetError(nRet),media_format_unref(hMediaFormat));

	nRet |= media_format_set_audio_channel(hMediaFormat, nChannel);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "media_format_set_audio_channel", WebRtcGetError(nRet),media_format_unref(hMediaFormat));

	nRet |= media_format_set_audio_samplerate(hMediaFormat, nSampleRate);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "media_format_set_audio_samplerate", WebRtcGetError(nRet),media_format_unref(hMediaFormat));

	nRet |= media_format_set_audio_bit(hMediaFormat, nAudioBit);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "media_format_set_audio_bit", WebRtcGetError(nRet),media_format_unref(hMediaFormat));

	nRet = webrtc_media_packet_source_set_format(g_hWebRtcHandle, nId, hMediaFormat);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_media_packet_source_set_format", WebRtcGetError(nRet),media_format_unref(hMediaFormat));

	nRet = media_format_unref(hMediaFormat);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "media_format_unref", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Pushes media packet to the media packet source.
//& type: auto
/**
* @testcase 			ITc_webrtc_media_packet_source_push_packet_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Pushes media packet to the media packet source.
* @scenario				Pushes media packet to the media packet source.
* @apicovered			webrtc_media_packet_source_push_packet
* @passcase				If webrtc_media_packet_source_push_packet is successful
* @failcase 			If webrtc_media_packet_source_push_packet fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_media_packet_source_push_packet_p(void)
{
	START_TEST;
	unsigned int nId;
	media_format_h hMediaFormat;
	media_packet_h hMediaPacket;
	int setVideoHeight = 480, nSetVideoWidth = 640;

	int nRet = media_format_create(&hMediaFormat);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "media_format_create", WebRtcGetError(nRet));
	CHECK_HANDLE(hMediaFormat, "media_format_create");

	nRet = webrtc_add_media_source(g_hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_MEDIA_PACKET, &nId);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet),media_format_unref(hMediaFormat));

	nRet = media_format_set_video_mime(hMediaFormat, MEDIA_FORMAT_I420);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "media_format_set_video_mime", WebRtcGetError(nRet),media_format_unref(hMediaFormat));

	nRet |= media_format_set_video_width(hMediaFormat, nSetVideoWidth);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "media_format_set_video_width", WebRtcGetError(nRet),media_format_unref(hMediaFormat));

	nRet |= media_format_set_video_height(hMediaFormat, setVideoHeight);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "media_format_set_video_height", WebRtcGetError(nRet),media_format_unref(hMediaFormat));

	nRet = webrtc_media_packet_source_set_format(g_hWebRtcHandle, nId, hMediaFormat);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_media_packet_source_set_format", WebRtcGetError(nRet),media_format_unref(hMediaFormat));

	nRet = webrtc_media_packet_source_set_buffer_state_changed_cb(g_hWebRtcHandle, nId, webrtcMediaPacketSourceBufferStateChangedCB, NULL);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_media_packet_source_set_buffer_state_changed_cb", WebRtcGetError(nRet),media_format_unref(hMediaFormat));

	nRet = media_packet_new_alloc(hMediaFormat, NULL, NULL, &hMediaPacket);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "media_packet_new_alloc", WebRtcGetError(nRet),media_format_unref(hMediaFormat));

	nRet = webrtc_media_packet_source_push_packet(g_hWebRtcHandle, nId, hMediaPacket);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_media_packet_source_push_packet", WebRtcGetError(nRet),media_packet_unref(hMediaPacket);media_format_unref(hMediaFormat));

	nRet = media_packet_unref(hMediaPacket);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "media_packet_unref", WebRtcGetError(nRet));

	nRet = media_format_unref(hMediaFormat);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "media_format_unref", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Sets and Gets the STUN server URL.
//& type: auto
/**
* @testcase 			ITc_webrtc_set_get_stun_server_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets the STUN server URL.
* @scenario				Sets and Gets the STUN server URL.
* @apicovered			webrtc_set_stun_server,webrtc_get_stun_server
* @passcase				If webrtc_set_stun_server,webrtc_get_stun_server is successful
* @failcase 			If webrtc_set_stun_server,webrtc_get_stun_server fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_set_get_stun_server_p(void)
{
	START_TEST;
	char *pszSetServer= "stun://stun.testurl.com:19302" , *pszGetServer = NULL;

	int nRet = webrtc_set_stun_server(g_hWebRtcHandle, pszSetServer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_stun_server", WebRtcGetError(nRet));

	nRet = webrtc_get_stun_server(g_hWebRtcHandle, &pszGetServer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_get_stun_server", WebRtcGetError(nRet));

	if (strcmp(pszGetServer, pszSetServer))
	{
		FPRINTF("[Line : %d][%s] set get server mismatch\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszGetServer);
		return 1;
	}

	FREE_MEMORY(pszGetServer);

	return 0;
}

//& purpose:  Adds a TURN server URL.
//& type: auto
/**
* @testcase 			ITc_webrtc_add_turn_server_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Adds a TURN server URL.
* @scenario				Adds a TURN server URL.
* @apicovered			webrtc_add_turn_server
* @passcase				If webrtc_add_turn_server is successful
* @failcase 			If webrtc_add_turn_server fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_add_turn_server_p(void)
{
	START_TEST;
	char *pszSetServer= "turn://turn.testurl.com:19303";

	int nRet = webrtc_add_turn_server(g_hWebRtcHandle, pszSetServer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_turn_server", WebRtcGetError(nRet));

	return 0;
}

//& purpose:  Retrieves all the TURN server URLs.
//& type: auto
/**
* @testcase 			ITc_webrtc_foreach_turn_server_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Retrieves all the TURN server URLs.
* @scenario				Retrieves all the TURN server URLs.
* @apicovered			webrtc_foreach_turn_server
* @passcase				If webrtc_foreach_turn_server is successful
* @failcase 			If webrtc_foreach_turn_server fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_foreach_turn_server_p(void)
{
	START_TEST;
	int nCount = 0;
	char *pszSetServer= "turn://turn.testurl.com:19303", *pszSetServer2 = "turn://turn2.testurl.com:19303";

	int nRet = webrtc_add_turn_server(g_hWebRtcHandle, pszSetServer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_turn_server", WebRtcGetError(nRet));
	nCount++;

	nRet = webrtc_add_turn_server(g_hWebRtcHandle, pszSetServer2);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_turn_server", WebRtcGetError(nRet));
	nCount++;

	nRet = webrtc_foreach_turn_server(g_hWebRtcHandle, webrtcTurnServerCB, (void *)&nCount);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_foreach_turn_server", WebRtcGetError(nRet));
	if(nCount != 0)
	{
		FPRINTF("[Line : %d][%s] nCount is not 0\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose:  Creates SDP offer and answer to start a new WebRTC connection to a remote peer.
//& type: auto
/**
* @testcase 			ITc_webrtc_create_offer_answer_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates SDP offer and answer to start a new WebRTC connection to a remote peer.
* @scenario				Creates SDP offer and answer to start a new WebRTC connection to a remote peer.
* @apicovered			webrtc_create_offer,webrtc_create_answer
* @passcase				If webrtc_create_offer,webrtc_create_answer is successful
* @failcase 			If webrtc_create_offer,webrtc_create_answer fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_create_offer_answer_p(void)
{
	START_TEST;
	unsigned int nId;
	char *pszOffer, *pszAnswer;
	webrtc_h hLocalWebRtcHandle,hWebRtcHandle;
	callback_data cb_data = { .mainloop = NULL, .is_invoked = false };

	int nRet = webrtc_create(&hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create", WebRtcGetError(nRet));
	CHECK_HANDLE(hWebRtcHandle, "webrtc_create");

	nRet = webrtc_add_media_source(hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_SCREEN, &nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_candidate_cb(hWebRtcHandle, webrtcIceCandidateCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(hWebRtcHandle, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_start(hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	nRet = webrtc_create_offer(hWebRtcHandle, NULL, &pszOffer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_offer", WebRtcGetError(nRet));

	nRet = webrtc_create(&hLocalWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create", WebRtcGetError(nRet));
	CHECK_HANDLE(hLocalWebRtcHandle, "webrtc_create");

	nRet = webrtc_set_ice_candidate_cb(hLocalWebRtcHandle, webrtcIceCandidateCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(hLocalWebRtcHandle, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_signaling_state_change_cb(hLocalWebRtcHandle, webrtcSignalingStateChangeCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_signaling_state_change_cb", WebRtcGetError(nRet));

	nRet = webrtc_start(hLocalWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	nRet = webrtc_set_remote_description(hLocalWebRtcHandle, pszOffer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_remote_description", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcSignalingStateChangeCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = webrtc_create_answer(hLocalWebRtcHandle, NULL, &pszAnswer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_answer", WebRtcGetError(nRet));

	FREE_MEMORY(pszOffer);
	FREE_MEMORY(pszAnswer);

#if 0
	nRet = webrtc_stop(hWebRtcHandle);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));

	nRet = webrtc_destroy(hWebRtcHandle);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy", WebRtcGetError(nRet));

	nRet = webrtc_stop(hLocalWebRtcHandle);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));

	nRet = webrtc_destroy(hLocalWebRtcHandle);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy", WebRtcGetError(nRet));
#endif

	return 0;
}

//& purpose: Sets the session description for a local peer associated with a WebRTC connection.
//& type: auto
/**
* @testcase 			ITc_webrtc_set_local_description_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets the session description for a local peer associated with a WebRTC connection.
* @scenario				Sets the session description for a local peer associated with a WebRTC connection.
* @apicovered			webrtc_set_local_description
* @passcase				If webrtc_set_local_description is successful
* @failcase 			If webrtc_set_local_description fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_set_local_description_p(void)
{
	START_TEST;
	unsigned int nId;
	char *pszOffer;
	callback_data cb_data = { .mainloop = NULL, .is_invoked = false };

	int nRet = webrtc_add_media_source(g_hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_candidate_cb(g_hWebRtcHandle, webrtcIceCandidateCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(g_hWebRtcHandle, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_start(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = webrtc_create_offer(g_hWebRtcHandle, NULL, &pszOffer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_offer", WebRtcGetError(nRet));

	nRet = webrtc_set_local_description(g_hWebRtcHandle, pszOffer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_local_description", WebRtcGetError(nRet));

	FREE_MEMORY(pszOffer);

	nRet = webrtc_stop(g_hWebRtcHandle);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));

	return 0;
}

//& purpose:  Sets the session description of the remote peer's current offer or answer.
//& type: auto
/**
* @testcase 			ITc_webrtc_set_remote_description_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets the session description of the remote peer's current offer or answer.
* @scenario				Sets the session description of the remote peer's current offer or answer.
* @apicovered			webrtc_set_remote_description
* @passcase				If webrtc_set_remote_description is successful
* @failcase 			If webrtc_set_remote_description fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_set_remote_description_p(void)
{
	START_TEST;
	webrtc_h hLocalWebRtcHandle;
	unsigned int nId;
	char *pszOffer;
	callback_data cb_data = { .mainloop = NULL, .is_invoked = false };

	int nRet = webrtc_add_media_source(g_hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_candidate_cb(g_hWebRtcHandle, webrtcIceCandidateCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(g_hWebRtcHandle, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_start(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	nRet = webrtc_create_offer(g_hWebRtcHandle, NULL, &pszOffer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_offer", WebRtcGetError(nRet));

	nRet = webrtc_create(&hLocalWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_candidate_cb(hLocalWebRtcHandle, webrtcIceCandidateCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(hLocalWebRtcHandle, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_start(hLocalWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = webrtc_set_remote_description(hLocalWebRtcHandle, pszOffer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_remote_description", WebRtcGetError(nRet));

	FREE_MEMORY(pszOffer);

	nRet = webrtc_stop(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));

	nRet = webrtc_stop(hLocalWebRtcHandle);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));

	nRet = webrtc_destroy(hLocalWebRtcHandle);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Adds a new ICE candidate from the remote peer over its signaling channel.
//& type: auto
/**
* @testcase 			ITc_webrtc_add_ice_candidate_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Adds a new ICE candidate from the remote peer over its signaling channel.
* @scenario				Adds a new ICE candidate from the remote peer over its signaling channel.
* @apicovered			webrtc_add_ice_candidate
* @passcase				If webrtc_add_ice_candidate is successful
* @failcase 			If webrtc_add_ice_candidate fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_add_ice_candidate_p(void)
{
	START_TEST;
	callback_data cb_data = { .mainloop = NULL, .is_invoked = false };

	int nRet = webrtc_set_ice_candidate_cb(g_hWebRtcHandle, webrtcIceCandidateCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(g_hWebRtcHandle, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_start(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = webrtc_add_ice_candidate(g_hWebRtcHandle, TEST_ICE_CANDIDATE);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_ice_candidate", WebRtcGetError(nRet));

	nRet = webrtc_stop(g_hWebRtcHandle);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Creates and Destroys the data channel.
//& type: auto
/**
* @testcase 			ITc_webrtc_create_destroy_data_channel_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates and Destroys the data channel.
* @scenario				Creates and Destroys the data channel.
* @apicovered			webrtc_create_data_channel,webrtc_destroy_data_channel
* @passcase				If webrtc_create_data_channel,webrtc_destroy_data_channel is successful
* @failcase 			If webrtc_create_data_channel,webrtc_destroy_data_channel fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_create_destroy_data_channel_p(void)
{
	START_TEST;
	webrtc_data_channel_h hChannel;
	char *pszChannel = "test channel";

	int nRet = webrtc_create_data_channel(g_hWebRtcHandle, pszChannel, NULL, &hChannel);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_data_channel", WebRtcGetError(nRet));
	CHECK_HANDLE(hChannel, "webrtc_create_data_channel");

	nRet = webrtc_destroy_data_channel(hChannel);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy_data_channel", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Gets the channel label.
//& type: auto
/**
* @testcase 			ITc_webrtc_data_channel_get_label_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the channel label.
* @scenario				Gets the channel label.
* @apicovered			webrtc_data_channel_get_label
* @passcase				If webrtc_data_channel_get_label is successful
* @failcase 			If webrtc_data_channel_get_label fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_data_channel_get_label_p(void)
{
	START_TEST;
	webrtc_data_channel_h hChannel;
	char *pszChannel = "test channel";
	char *pszGetLabel;

	int nRet = webrtc_create_data_channel(g_hWebRtcHandle, pszChannel, NULL, &hChannel);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_data_channel", WebRtcGetError(nRet));
	CHECK_HANDLE(hChannel,"webrtc_create_data_channel");

	nRet = webrtc_data_channel_get_label(hChannel, &pszGetLabel);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_data_channel_get_label", WebRtcGetError(nRet),webrtc_destroy_data_channel(hChannel));

	FREE_MEMORY(pszGetLabel);
	nRet = webrtc_destroy_data_channel(hChannel);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy_data_channel", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Creates SDP offer asynchronously to start a new WebRTC connection to a remote peer.
//& type: auto
/**
* @testcase 			ITc_webrtc_create_offer_async_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates SDP offer asynchronously to start a new WebRTC connection to a remote peer.
* @scenario				Creates SDP offer asynchronously to start a new WebRTC connection to a remote peer.
* @apicovered			webrtc_create_offer_async
* @passcase				If webrtc_create_offer_async is successful
* @failcase 			If webrtc_create_offer_async fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_create_offer_async_p(void)
{
	START_TEST;
	unsigned int nId;
	callback_data cb_data = { .mainloop = NULL, .is_invoked = false };

	int nRet = webrtc_add_media_source(g_hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_candidate_cb(g_hWebRtcHandle, webrtcIceCandidateCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(g_hWebRtcHandle, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_start(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	nRet = webrtc_create_offer_async(g_hWebRtcHandle, NULL, webrtcSessionDescriptionCreatedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_offer_async", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcSessionDescriptionCreatedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = webrtc_stop(g_hWebRtcHandle);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Creates SDP answer asynchronously to an offer received from a remote peer during the negotiation of a WebRTC connection.
//& type: auto
/**
* @testcase 			ITc_webrtc_create_answer_async_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates SDP answer asynchronously to an offer received from a remote peer during the negotiation of a WebRTC connection.
* @scenario				Creates SDP answer asynchronously to an offer received from a remote peer during the negotiation of a WebRTC connection.
* @apicovered			webrtc_create_answer_async
* @passcase				If webrtc_create_answer_async is successful
* @failcase 			If webrtc_create_answer_async fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_create_answer_async_p(void)
{
	START_TEST;
	unsigned int nId;
	char *pszOffer;
	webrtc_h hLocalWebRtcHandle;
	callback_data cb_data = { .mainloop = NULL, .is_invoked = false };

	int nRet = webrtc_add_media_source(g_hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_candidate_cb(g_hWebRtcHandle, webrtcIceCandidateCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(g_hWebRtcHandle, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_start(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	nRet = webrtc_create_offer(g_hWebRtcHandle, NULL, &pszOffer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_offer", WebRtcGetError(nRet));

	nRet = webrtc_create(&hLocalWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_candidate_cb(hLocalWebRtcHandle, webrtcIceCandidateCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(hLocalWebRtcHandle, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_signaling_state_change_cb(hLocalWebRtcHandle, webrtcSignalingStateChangeCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_signaling_state_change_cb", WebRtcGetError(nRet));

	nRet = webrtc_start(hLocalWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	nRet = webrtc_set_remote_description(hLocalWebRtcHandle, pszOffer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_remote_description", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcSignalingStateChangeCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	nRet = webrtc_create_answer_async(hLocalWebRtcHandle, NULL, webrtcSessionDescriptionCreatedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_answer_async", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcSessionDescriptionCreatedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	FREE_MEMORY(pszOffer);

	nRet = webrtc_stop(g_hWebRtcHandle);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));

	nRet = webrtc_stop(hLocalWebRtcHandle);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));

	nRet = webrtc_destroy(hLocalWebRtcHandle);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Sets , Unsets and Gets an audio loopback to render the audio frames of the media source.
//& type: auto
/**
* @testcase 			ITc_webrtc_media_source_set_unset_audio_loopback_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets, Unsets and Gets an audio loopback to render the audio frames of the media source.
* @scenario				Sets, Unsets and Gets an audio loopback to render the audio frames of the media source.
* @apicovered			webrtc_media_source_set_audio_loopback
* @passcase				If webrtc_media_source_set_audio_loopback and webrtc_media_source_unset_audio_loopback is successfull
* @failcase 			If webrtc_media_source_set_audio_loopback or webrtc_media_source_unset_audio_loopback fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_media_source_set_unset_audio_loopback_p(void)
{
	START_TEST;
	unsigned int nId;
	sound_stream_info_h hStreamInfo;
	callback_data cb_data = { .mainloop = NULL, .is_invoked = false };

	createWindow();
	int nRet = webrtc_add_media_source(g_hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_AUDIOTEST, &nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_candidate_cb(g_hWebRtcHandle, webrtcIceCandidateCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(g_hWebRtcHandle, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, NULL, NULL, &hStreamInfo);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "sound_manager_create_stream_information", WebRtcGetError(nRet));

	nRet = webrtc_media_source_set_audio_loopback(g_hWebRtcHandle, nId, hStreamInfo, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_media_source_set_audio_loopback", WebRtcGetError(nRet));

	nRet = webrtc_start(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	nRet = webrtc_stop(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));

	nRet = webrtc_media_source_unset_audio_loopback(g_hWebRtcHandle,nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_media_source_unset_audio_loopback", WebRtcGetError(nRet));

	nRet = sound_manager_destroy_stream_information(hStreamInfo);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", WebRtcGetError(nRet));
	destroyWindow();

	return 0;
}

//& purpose: Sets,Unsets a video loopback to render the video frames of the media source.
//& type: auto
/**
* @testcase 			ITc_webrtc_media_source_set_unset_video_loopback_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets,Unsets a video loopback to render the video frames of the media source.
* @scenario				Sets,Unsets a video loopback to render the video frames of the media source.
* @apicovered			webrtc_media_source_set_video_loopback
* @passcase				If webrtc_media_source_set_video_loopback and webrtc_media_source_unset_video_loopback is successfull
* @failcase 			If webrtc_media_source_set_video_loopback or webrtc_media_source_unset_video_loopback fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_media_source_set_unset_video_loopback_p(void)
{
	START_TEST;
	unsigned int nId;
	callback_data cb_data = { .mainloop = NULL, .is_invoked = false };

	createWindow();
	int nRet = webrtc_add_media_source(g_hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_candidate_cb(g_hWebRtcHandle, webrtcIceCandidateCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(g_hWebRtcHandle, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_media_source_set_video_loopback(g_hWebRtcHandle, nId, WEBRTC_DISPLAY_TYPE_OVERLAY, g_win, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_media_source_set_video_loopback", WebRtcGetError(nRet));

	nRet = webrtc_start(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = webrtc_stop(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));

	 nRet = webrtc_media_source_unset_video_loopback(g_hWebRtcHandle, nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_media_source_unset_video_loopback", WebRtcGetError(nRet));

	destroyWindow();

	return 0;
}

//& purpose: Sets and Gets the display mode of the video track.
//& type: auto
/**
* @testcase 			ITc_webrtc_set_get_display_mode_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets the display mode of the video track.
* @scenario				Sets and Gets the display mode of the video track.
* @apicovered			webrtc_set_display_mode,webrtc_get_display_mode
* @passcase				If webrtc_set_display_mode,webrtc_get_display_mode is successful
* @failcase 			If webrtc_set_display_mode,webrtc_get_display_mode fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_set_get_display_mode_p(void)
{
	START_TEST;
	unsigned int nId,nTrackId;
	webrtc_display_mode_e eMode;
	callback_data cb_data = { .mainloop = NULL, .is_invoked = false };

	createWindow();
	int nRet = webrtc_add_media_source(g_hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_candidate_cb(g_hWebRtcHandle, webrtcIceCandidateCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(g_hWebRtcHandle, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_media_source_set_video_loopback(g_hWebRtcHandle, nId, WEBRTC_DISPLAY_TYPE_OVERLAY, g_win, &nTrackId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_media_source_set_video_loopback", WebRtcGetError(nRet));

	nRet = webrtc_start(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = webrtc_set_display_mode(g_hWebRtcHandle, nTrackId, WEBRTC_DISPLAY_MODE_FULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_display_mode", WebRtcGetError(nRet));

	nRet = webrtc_get_display_mode(g_hWebRtcHandle, nTrackId, &eMode);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_get_display_mode", WebRtcGetError(nRet));
	PRINT_RESULT(WEBRTC_DISPLAY_MODE_FULL, eMode, "webrtc_get_display_mode", WebRtcGetError(nRet));

	nRet = webrtc_stop(g_hWebRtcHandle);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));
	destroyWindow();
	return 0;
}

//& purpose: Sets and Gets the display visibleness of the video track.
//& type: auto
/**
* @testcase 			ITc_webrtc_set_get_display_visible_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets the display visibleness of the video track.
* @scenario				Sets and Gets the display visibleness of the video track.
* @apicovered			webrtc_set_display_visible,webrtc_get_display_visible
* @passcase				If webrtc_set_display_visible,webrtc_get_display_visible is successful
* @failcase 			If webrtc_set_display_visible,webrtc_get_display_visible fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_set_get_display_visible_p(void)
{
	START_TEST;
	unsigned int nId,nTrackId;
	bool bGetVisible, bSetVisible = false;
	callback_data cb_data = { .mainloop = NULL, .is_invoked = false };

	int nRet = webrtc_add_media_source(g_hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_candidate_cb(g_hWebRtcHandle, webrtcIceCandidateCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(g_hWebRtcHandle, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	createWindow();

	nRet = webrtc_media_source_set_video_loopback(g_hWebRtcHandle, nId, WEBRTC_DISPLAY_TYPE_OVERLAY, g_win, &nTrackId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_media_source_set_video_loopback", WebRtcGetError(nRet));

	nRet = webrtc_start(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = webrtc_set_display_visible(g_hWebRtcHandle, nTrackId, bSetVisible);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_display_visible", WebRtcGetError(nRet));

	nRet = webrtc_get_display_visible(g_hWebRtcHandle, nTrackId, &bGetVisible);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_get_display_visible", WebRtcGetError(nRet));
	PRINT_RESULT(bGetVisible, bSetVisible, "webrtc_get_display_visible", WebRtcGetError(nRet));

	nRet = webrtc_stop(g_hWebRtcHandle);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));
	destroyWindow();
	return 0;
}

//& purpose: Sets and Gets a ICE transport policy that represents which candidates the ICE Agent is allowed to use.
//& type: auto
/**
* @testcase 			ITc_webrtc_set_get_ice_transport_policy_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets a ICE transport policy that represents which candidates the ICE Agent is allowed to use.
* @scenario				Sets and Gets a ICE transport policy that represents which candidates the ICE Agent is allowed to use.
* @apicovered			webrtc_set_ice_transport_policy,webrtc_get_ice_transport_policy
* @passcase				If webrtc_set_ice_transport_policy,webrtc_get_ice_transport_policy is successful
* @failcase 			If webrtc_set_ice_transport_policy,webrtc_get_ice_transport_policy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_set_get_ice_transport_policy_p(void)
{
	START_TEST;
	webrtc_ice_transport_policy_e eGetPolicy;
	createWindow();

	int nRet = webrtc_set_ice_transport_policy(g_hWebRtcHandle, WEBRTC_ICE_TRANSPORT_POLICY_RELAY);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_transport_policy", WebRtcGetError(nRet));

	nRet = webrtc_get_ice_transport_policy(g_hWebRtcHandle, &eGetPolicy);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_get_ice_transport_policy", WebRtcGetError(nRet));
	PRINT_RESULT(WEBRTC_ICE_TRANSPORT_POLICY_RELAY, eGetPolicy, "webrtc_get_ice_transport_policy", WebRtcGetError(nRet));
	destroyWindow();
	return 0;
}

//& purpose: Sets and Gets looping mode of the file source.
//& type: auto
/**
* @testcase 			ITc_webrtc_file_source_set_get_looping_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets looping mode of the file source.
* @scenario				Sets and Gets looping mode of the file source.
* @apicovered			webrtc_file_source_set_looping,webrtc_file_source_get_looping
* @passcase				If webrtc_file_source_set_looping,webrtc_file_source_get_looping is successfull
* @failcase 			If webrtc_file_source_set_looping,webrtc_file_source_get_looping fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_file_source_set_get_looping_p(void)
{
	START_TEST;
	unsigned int nId;
	bool isGetLooping, isSetLooping=true;

	int nRet = webrtc_add_media_source(g_hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_FILE, &nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

	nRet = webrtc_file_source_set_looping(g_hWebRtcHandle, nId, isSetLooping);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_file_source_set_looping", WebRtcGetError(nRet));

	nRet = webrtc_file_source_get_looping(g_hWebRtcHandle, nId, &isGetLooping);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_file_source_get_looping", WebRtcGetError(nRet));

	if(isSetLooping != isGetLooping)
	{
		FPRINTF("[Line : %d][%s] set get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Sets media path of the file source.
//& type: auto
/**
* @testcase 			ITc_webrtc_file_source_set_path_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets media path of the file source.
* @scenario				Sets media path of the file source.
* @apicovered			webrtc_file_source_set_path
* @passcase				If webrtc_file_source_set_path is successfull
* @failcase 			If webrtc_file_source_set_path fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_file_source_set_path_p(void)
{
	START_TEST;
	unsigned int nId;
	callback_data cb_data = { .mainloop = NULL, .is_invoked = false };

	int nRet = GetDataFromFile();
	if(nRet != 0)
	{
		FPRINTF("[Line : %d][%s] Media file path not found\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = webrtc_add_media_source(g_hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_FILE, &nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_candidate_cb(g_hWebRtcHandle, webrtcIceCandidateCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(g_hWebRtcHandle, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	FPRINTF("[Line : %d][%s] g_pszFilePath = %s\\n", __LINE__, API_NAMESPACE,  g_pszFilePath);

	nRet = webrtc_file_source_set_path(g_hWebRtcHandle, nId, g_pszFilePath);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_file_source_set_path", WebRtcGetError(nRet));

	nRet = webrtc_start(g_hWebRtcHandle);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = webrtc_stop(g_hWebRtcHandle);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));
	FREE_MEMORY(g_pszFilePath);
	return 0;
}

//& purpose: Starts and finishes negotiation by setting local and remote descriptions to two handles.
//& type: auto
/**
* @testcase 			ITc_webrtc_start_and_finish_negotiation_p
* @since_tizen 			6.5
* @author				SR(sc11.lee)
* @reviewer				SR(seungbae.shin)
* @type 				auto
* @description			Starts and finishes negotiation by setting local and remote descriptions to two handles.
* @scenario				Starts and finishes negotiation by setting local and remote descriptions to two handles.
* @apicovered			webrtc_start,webrtc_create_offer,webrtc_create_answer,webrtc_set_local_description,webrtc_set_remote_description
* @passcase				If webrtc_start,webrtc_create_offer,webrtc_create_answer,webrtc_set_local_description,webrtc_set_remote_description is successful
* @failcase 			If webrtc_start,webrtc_create_offer,webrtc_create_answer,webrtc_set_local_description,webrtc_set_remote_description fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_start_and_finish_negotiation_p(void)
{
	webrtc_h webrtcOfferer;
	webrtc_h webrtcAnswerer;
	int nRet;
	unsigned int nId;
	char *offerSDP;
	char *answerSDP;
	GList *offerICECandidates = NULL;
	GList *answerICECandidates = NULL;
	callback_data cb_data = { .mainloop = NULL, .is_invoked = false };
	callback_data cb_data2 = { .mainloop = NULL, .is_invoked = false };

	START_TEST;

	nRet = webrtc_create(&webrtcOfferer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create", WebRtcGetError(nRet));

	nRet = webrtc_add_media_source(webrtcOfferer, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_candidate_cb(webrtcOfferer, webrtcIceCandidateCB, &offerICECandidates);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(webrtcOfferer, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_signaling_state_change_cb(webrtcOfferer, webrtcSignalingStateChangeCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_signaling_state_change_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_gathering_state_change_cb(webrtcOfferer, webrtcIceGatheringStateChangeCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_gathering_state_change_cb", WebRtcGetError(nRet));

	nRet = webrtc_start(webrtcOfferer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	nRet = webrtc_create(&webrtcAnswerer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_candidate_cb(webrtcAnswerer, webrtcIceCandidateCB, &answerICECandidates);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(webrtcAnswerer, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_signaling_state_change_cb(webrtcAnswerer, webrtcSignalingStateChangeCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_signaling_state_change_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_gathering_state_change_cb(webrtcAnswerer, webrtcIceGatheringStateChangeCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_gathering_state_change_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_track_added_cb(webrtcAnswerer, webrtcTrackAddedCB, &cb_data2);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_track_added_cb", WebRtcGetError(nRet));

	nRet = webrtc_start(webrtcAnswerer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	nRet = webrtc_create_offer(webrtcOfferer, NULL, &offerSDP);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_offer", WebRtcGetError(nRet));

	nRet = webrtc_set_local_description(webrtcOfferer, offerSDP);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_local_description", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcIceGatheringStateChangeCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	nRet = webrtc_set_remote_description(webrtcAnswerer, offerSDP);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_remote_description", WebRtcGetError(nRet));
	FREE_MEMORY(offerSDP);

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcSignalingStateChangeCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	nRet = webrtc_create_answer(webrtcAnswerer, NULL, &answerSDP);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_answer", WebRtcGetError(nRet));

	nRet = webrtc_set_local_description(webrtcAnswerer, answerSDP);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_local_description", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcIceGatheringStateChangeCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_list_foreach(offerICECandidates, __foreach_ice_candidate, webrtcAnswerer);
	g_list_foreach(answerICECandidates, __foreach_ice_candidate, webrtcOfferer);

	nRet = webrtc_set_remote_description(webrtcOfferer, answerSDP);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_remote_description", WebRtcGetError(nRet));
	FREE_MEMORY(answerSDP);

	/* wait for track added callback of answerer */
	RUN_POLLING_LOOP(cb_data2.mainloop, cb_data2.is_invoked);
	if (!cb_data2.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcTrackAddedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = webrtc_stop(webrtcOfferer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));

	nRet = webrtc_destroy(webrtcOfferer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy", WebRtcGetError(nRet));

	nRet = webrtc_stop(webrtcAnswerer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));

	nRet = webrtc_destroy(webrtcAnswerer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy", WebRtcGetError(nRet));

	g_list_free_full(offerICECandidates, free);
	g_list_free_full(answerICECandidates, free);

	return 0;
}

//& purpose: Gets the buffered amount of the data channel.
//& type: auto
/**
* @testcase 			ITc_webrtc_data_channel_get_buffered_amount_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the buffered amount of the data channel.
* @scenario				Sets and Gets the display mode of the video track.
* @apicovered			webrtc_create_data_chanel,webrtc_data_channel_get_buffered_amount, webrtc_destroy_data_channel
* @passcase				If webrtc_data_channel_get_buffered_amount is successful
* @failcase 			If webrtc_data_channel_get_buffered_amount is unsuccessful
* @precondition			NA
* @postcondition		NA
*/

int ITc_webrtc_data_channel_get_buffered_amount_p(void)
{
	START_TEST;

	webrtc_data_channel_h hChannel;
	char *pszChannel = "test data channel label";
	unsigned int nBufferedAmount;

	int nRet = webrtc_create_data_channel(g_hWebRtcHandle, pszChannel, NULL, &hChannel);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_data_channel", WebRtcGetError(nRet));
	CHECK_HANDLE(hChannel, "webrtc_create_data_channel");

	nRet = webrtc_data_channel_get_buffered_amount(hChannel, &nBufferedAmount);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_data_channel_get_buffered_amount", WebRtcGetError(nRet), webrtc_destroy_data_channel(hChannel));

	nRet = webrtc_destroy_data_channel(hChannel);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy_data_channel", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Set and unset the buffered amount of the data channel.
//& type: auto
/**
* @testcase 			ITc_webrtc_data_channel_set_unset_buffered_amount_low_cb_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and unsets the buffered amount of the data channel.
* @scenario				Sets and Gets the display mode of the video track.
* @apicovered			webrtc_create_data_chanel,webrtc_data_channel_set_buffered_amount_low_cb, webrtc_data_channel_unset_buffered_amount_low_cb, webrtc_destroy_data_channel
* @passcase				If webrtc_data_channel_set_buffered_amount_low_cb and webrtc_data_channel_unset_buffered_amount_low_cb is successful
* @failcase 			If webrtc_data_channel_set_buffered_amount_low_cb or webrtc_data_channel_unset_buffered_amount_low_cb fails
* @precondition			NA
* @postcondition		NA
*/

int ITc_webrtc_data_channel_set_unset_buffered_amount_low_cb_p(void)
{
	START_TEST;

	webrtc_data_channel_h hChannel;
	char *pszChannel = "test data channel label";

	int nRet = webrtc_create_data_channel(g_hWebRtcHandle, pszChannel, NULL, &hChannel);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_data_channel", WebRtcGetError(nRet));
	CHECK_HANDLE(hChannel, "webrtc_create_data_channel");

	nRet = webrtc_data_channel_set_buffered_amount_low_cb(hChannel, TEST_BUFFERED_AMOUNT_THRESHOLD, dataChannelBufferedAmountLowCB, NULL);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_data_channel_set_buffered_amount_low_cb", WebRtcGetError(nRet), webrtc_destroy_data_channel(hChannel));

	nRet = webrtc_data_channel_unset_buffered_amount_low_cb(hChannel);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_data_channel_unset_buffered_amount_low_cb", WebRtcGetError(nRet), webrtc_destroy_data_channel(hChannel));

	nRet = webrtc_destroy_data_channel(hChannel);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy_data_channel", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Get the buffered amount of the low threshold data channel.
//& type: auto
/**
* @testcase 			ITc_webrtc_data_channel_get_buffered_amount_low_threshold_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Get the buffered amount of the low threshold data channel.
* @scenario				Get the buffered amount of the low threshold data channel.
* @apicovered			webrtc_create_data_chanel,webrtc_data_channel_set_buffered_amount_low_cb,webrtc_data_channel_get_buffered_amount_low_threshold, webrtc_destroy_data_channel
* @passcase				If webrtc_data_channel_set_buffered_amount_low_cb and webrtc_data_channel_get_buffered_amount_low_threshold is successful
* @failcase 			If webrtc_data_channel_set_buffered_amount_low_cb or webrtc_data_channel_get_buffered_amount_low_threshold fails
* @precondition			NA
* @postcondition		NA
*/

int ITc_webrtc_data_channel_get_buffered_amount_low_threshold_p(void)
{
	START_TEST;

	webrtc_data_channel_h hChannel;
	char *pszChannel = "test data channel label";
	unsigned int nThreshold;

	int nRet = webrtc_create_data_channel(g_hWebRtcHandle, pszChannel, NULL, &hChannel);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_data_channel", WebRtcGetError(nRet));
	CHECK_HANDLE(hChannel, "webrtc_create_data_channel");

	nRet = webrtc_data_channel_set_buffered_amount_low_cb(hChannel, TEST_BUFFERED_AMOUNT_THRESHOLD, dataChannelBufferedAmountLowCB, NULL);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_data_channel_set_buffered_amount_low_cb", WebRtcGetError(nRet), webrtc_destroy_data_channel(hChannel));

	nRet = webrtc_data_channel_get_buffered_amount_low_threshold(hChannel, &nThreshold);
	PRINT_RESULT_CLEANUP(WEBRTC_ERROR_NONE, nRet, "webrtc_data_channel_get_buffered_amount_low_threshold", WebRtcGetError(nRet), webrtc_destroy_data_channel(hChannel));

	PRINT_RESULT_CLEANUP(TEST_BUFFERED_AMOUNT_THRESHOLD, nThreshold, "webrtc_data_channel_get_buffered_amount_low_threshold", WebRtcGetError(nRet), webrtc_destroy_data_channel(hChannel));

	nRet = webrtc_destroy_data_channel(hChannel);
	PRINT_RESULT_NORETURN(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy_data_channel", WebRtcGetError(nRet));

	return 0;
}

//& purpose: Sends and receives data via data channel between two handles.
//& type: auto
/**
* @testcase 			ITc_webrtc_data_channel_send_and_receive_p
* @since_tizen 			7.0
* @author				SR(sc11.lee)
* @reviewer				SR(seungbae.shin)
* @type 				auto
* @description			Sends and receives data via data channel between two handles.
* @scenario				Sends and receives data via data channel between two handles.
* @apicovered			webrtc_start,webrtc_create_offer,webrtc_create_answer,webrtc_data_channel_send_string,webrtc_data_channel_send_bytes
* @passcase				If webrtc_start,webrtc_create_offer,webrtc_create_answer,webrtc_data_channel_send_string,webrtc_data_channel_send_bytes is successful
* @failcase 			If webrtc_start,webrtc_create_offer,webrtc_create_answer,webrtc_data_channel_send_string,webrtc_data_channel_send_bytes fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_webrtc_data_channel_send_and_receive_p(void)
{
	webrtc_h webrtcOfferer;
	webrtc_h webrtcAnswerer;
	webrtc_data_channel_h datachannelOfferer;
	int nRet;
	char *offerSDP;
	char *answerSDP;
	GList *offerICECandidates = NULL;
	GList *answerICECandidates = NULL;
	callback_data cb_data = { .mainloop = NULL, .is_invoked = false };
	callback_data cb_data2 = { .mainloop = NULL, .is_invoked = false };

	START_TEST;

	/* initialize and start offerer */
	nRet = webrtc_create(&webrtcOfferer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_candidate_cb(webrtcOfferer, webrtcIceCandidateCB, &offerICECandidates);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(webrtcOfferer, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_signaling_state_change_cb(webrtcOfferer, webrtcSignalingStateChangeCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_signaling_state_change_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_gathering_state_change_cb(webrtcOfferer, webrtcIceGatheringStateChangeCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_gathering_state_change_cb", WebRtcGetError(nRet));

	nRet = webrtc_create_data_channel(webrtcOfferer, TEST_DATA_CHANNEL_LABEL, NULL, &datachannelOfferer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_data_channel", WebRtcGetError(nRet));

	nRet = webrtc_start(webrtcOfferer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	/* initialize and start answerer */
	nRet = webrtc_create(&webrtcAnswerer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_candidate_cb(webrtcAnswerer, webrtcIceCandidateCB, &answerICECandidates);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(webrtcAnswerer, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_signaling_state_change_cb(webrtcAnswerer, webrtcSignalingStateChangeCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_signaling_state_change_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_gathering_state_change_cb(webrtcAnswerer, webrtcIceGatheringStateChangeCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_gathering_state_change_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_data_channel_cb(webrtcAnswerer, webrtcDataChannelCB, &cb_data2);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_data_channel_cb", WebRtcGetError(nRet));

	nRet = webrtc_start(webrtcAnswerer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));
	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	/* do negotiate */
	nRet = webrtc_create_offer(webrtcOfferer, NULL, &offerSDP);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_offer", WebRtcGetError(nRet));

	nRet = webrtc_set_local_description(webrtcOfferer, offerSDP);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_local_description", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcIceGatheringStateChangeCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	nRet = webrtc_set_remote_description(webrtcAnswerer, offerSDP);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_remote_description", WebRtcGetError(nRet));
	FREE_MEMORY(offerSDP);

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcSignalingStateChangeCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	nRet = webrtc_create_answer(webrtcAnswerer, NULL, &answerSDP);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_answer", WebRtcGetError(nRet));

	nRet = webrtc_set_local_description(webrtcAnswerer, answerSDP);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_local_description", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcIceGatheringStateChangeCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_list_foreach(offerICECandidates, __foreach_ice_candidate, webrtcAnswerer);
	g_list_foreach(answerICECandidates, __foreach_ice_candidate, webrtcOfferer);

	nRet = webrtc_set_remote_description(webrtcOfferer, answerSDP);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_remote_description", WebRtcGetError(nRet));
	FREE_MEMORY(answerSDP);

	/* wait for channel open of answerer */
	RUN_POLLING_LOOP(cb_data2.mainloop, cb_data2.is_invoked);
	if (!cb_data2.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcDataChannelOpenCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data2.is_invoked = false;

	/* send data to answerer */
	nRet = webrtc_data_channel_send_string(datachannelOfferer, TEST_STRING_DATA);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_data_channel_send_string", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data2.mainloop, cb_data2.is_invoked);
	if (!cb_data2.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcDataChannelMessageCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data2.is_invoked = false;

	nRet = webrtc_data_channel_send_bytes(datachannelOfferer, g_test_buffer, TEST_BUFFER_SIZE);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_data_channel_send_bytes", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data2.mainloop, cb_data2.is_invoked);
	if (!cb_data2.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcDataChannelMessageCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data2.is_invoked = false;

	nRet = webrtc_destroy_data_channel(datachannelOfferer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy_data_channel", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data2.mainloop, cb_data2.is_invoked);
	if (!cb_data2.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcDataChannelCloseCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	/* Stop and de-initialize the both handles */
	nRet = webrtc_stop(webrtcOfferer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));

	nRet = webrtc_destroy(webrtcOfferer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy", WebRtcGetError(nRet));

	nRet = webrtc_stop(webrtcAnswerer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));

	nRet = webrtc_destroy(webrtcAnswerer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy", WebRtcGetError(nRet));

	g_list_free_full(offerICECandidates, free);
	g_list_free_full(answerICECandidates, free);

	return 0;
}

//& purpose: Set and Get the video framerate of the media source.
//& type: auto
/**
* @testcase 			ITc_webrtc_media_source_set_get_video_framerate_p
* @since_tizen 			7.0
* @author			SRID(ankit.sri1)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			Set and Get the video framerate of the media source.
* @scenario			Set and Get the video framerate of the media source.
* @apicovered			webrtc_create_data_chanel,webrtc_data_channel_set_buffered_amount_low_cb,webrtc_data_channel_get_buffered_amount_low_threshold, webrtc_destroy_data_channel
* @passcase			If webrtc_media_source_set_video_framerate and webrtc_media_source_get_video_framerate is successful
* @failcase 			If webrtc_media_source_set_video_framerate or webrtc_media_source_get_video_framerate fails
* @precondition			NA
* @postcondition		NA
*/

int ITc_webrtc_media_source_set_get_video_framerate_p(void)
{
	START_TEST;
	unsigned int nId;
	int fps;

	int nRet = webrtc_add_media_source(g_hWebRtcHandle, WEBRTC_MEDIA_SOURCE_TYPE_CAMERA, &nId);
	if (nRet == WEBRTC_ERROR_NOT_SUPPORTED) {
		FPRINTF("[Line : %d][%s] camera feature is not supported, skip it\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

	nRet = webrtc_media_source_set_video_framerate(g_hWebRtcHandle, nId, TEST_FPS);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_media_source_set_framerate", WebRtcGetError(nRet));

	nRet = webrtc_media_source_get_video_framerate(g_hWebRtcHandle, nId, &fps);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_media_source_get_framerate", WebRtcGetError(nRet));

	if (fps != TEST_FPS)
	{
		FPRINTF("[Line : %d][%s] fps set get mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Sets and Gets the bundle policy
//& type: auto
/**
* @testcase 			ITc_webrtc_set_get_bundle_policy_p
* @since_tizen 			7.0
* @author			SRID(ankit.sri1)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			Sets and Gets the bundle policy
* @scenario			Sets and Gets the bundle policy
* @apicovered			webrtc_set_bundle_policy,webrtc_get_bundle_policy
* @passcase			If webrtc_set_bundle_policy and webrtc_get_bundle_policy is successful
* @failcase 			If webrtc_set_ice_bundle_policy or webrtc_get_bundle_policy fails
* @precondition			NA
* @postcondition		NA
*/

int ITc_webrtc_set_get_bundle_policy_p(void)
{
	START_TEST;
	webrtc_bundle_policy_e eGetPolicy;

	int nRet = webrtc_set_bundle_policy(g_hWebRtcHandle, WEBRTC_BUNDLE_POLICY_NONE);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_bundle_policy", WebRtcGetError(nRet));

	nRet = webrtc_get_bundle_policy(g_hWebRtcHandle, &eGetPolicy);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_get_bundle_policy", WebRtcGetError(nRet));
	PRINT_RESULT(WEBRTC_BUNDLE_POLICY_NONE, eGetPolicy, "webrtc_get_bundle_policy", WebRtcGetError(nRet));
	return 0;
}

/**
* @testcase                     ITc_webrtc_foreach_stats_p
* @since_tizen                  7.0
* @author                       SRID(manu.tiwari)
* @reviewer                     SRID(shobhit.v)
* @type                         auto
* @description                  Retrieves all the statistics properties, asynchronously.
* @scenario                     Create a webrtc handle, Foreach stats
* @apicovered                   webrtc_foreach_stats
* @passcase                     When webrtc_foreach_stats is successful
* @failcase                     If webrtc_foreach_stats fail
* @precondition                 na
* @postcondition                na
*/
int ITc_webrtc_foreach_stats_p(void)
{
	webrtc_h webrtcOfferer;
	webrtc_h webrtcAnswerer;
	int nRet;
	unsigned int nId;
	char *offerSDP;
	char *answerSDP;
	GList *offerICECandidates = NULL;
	GList *answerICECandidates = NULL;
	callback_data cb_data = { .mainloop = NULL, .is_invoked = false };
	callback_data cb_data2 = { .mainloop = NULL, .is_invoked = false };

	START_TEST;

	nRet = webrtc_create(&webrtcOfferer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create", WebRtcGetError(nRet));

	nRet = webrtc_add_media_source(webrtcOfferer, WEBRTC_MEDIA_SOURCE_TYPE_VIDEOTEST, &nId);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_add_media_source", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_candidate_cb(webrtcOfferer, webrtcIceCandidateCB, &offerICECandidates);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(webrtcOfferer, webrtcStateChangedCB, &cb_data2);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_signaling_state_change_cb(webrtcOfferer, webrtcSignalingStateChangeCB, NULL);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_signaling_state_change_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_gathering_state_change_cb(webrtcOfferer, webrtcIceGatheringStateChangeCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_gathering_state_change_cb", WebRtcGetError(nRet));

	nRet = webrtc_start(webrtcOfferer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data2.mainloop, cb_data2.is_invoked);
	if (!cb_data2.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data2.is_invoked = false;

	nRet = webrtc_create(&webrtcAnswerer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_candidate_cb(webrtcAnswerer, webrtcIceCandidateCB, &answerICECandidates);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_candidate_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_state_changed_cb(webrtcAnswerer, webrtcStateChangedCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_state_changed_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_signaling_state_change_cb(webrtcAnswerer, webrtcSignalingStateChangeCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_signaling_state_change_cb", WebRtcGetError(nRet));

	nRet = webrtc_set_ice_gathering_state_change_cb(webrtcAnswerer, webrtcIceGatheringStateChangeCB, &cb_data);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_ice_gathering_state_change_cb", WebRtcGetError(nRet));

	nRet = webrtc_start(webrtcAnswerer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_start", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	nRet = webrtc_create_offer(webrtcOfferer, NULL, &offerSDP);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_offer", WebRtcGetError(nRet));

	nRet = webrtc_set_local_description(webrtcOfferer, offerSDP);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_local_description", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcIceGatheringStateChangeCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	nRet = webrtc_set_remote_description(webrtcAnswerer, offerSDP);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_remote_description", WebRtcGetError(nRet));
	FREE_MEMORY(offerSDP);

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcSignalingStateChangeCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	nRet = webrtc_create_answer(webrtcAnswerer, NULL, &answerSDP);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_create_answer", WebRtcGetError(nRet));

	nRet = webrtc_set_local_description(webrtcAnswerer, answerSDP);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_local_description", WebRtcGetError(nRet));

	RUN_POLLING_LOOP(cb_data.mainloop, cb_data.is_invoked);
	if (!cb_data.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcIceGatheringStateChangeCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data.is_invoked = false;

	g_list_foreach(offerICECandidates, __foreach_ice_candidate, webrtcAnswerer);
	g_list_foreach(answerICECandidates, __foreach_ice_candidate, webrtcOfferer);

	nRet = webrtc_set_remote_description(webrtcOfferer, answerSDP);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_set_remote_description", WebRtcGetError(nRet));
	FREE_MEMORY(answerSDP);

	/* wait for PLAYING state */
	RUN_POLLING_LOOP(cb_data2.mainloop, cb_data2.is_invoked);
	if (!cb_data2.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStateChangedCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	cb_data2.is_invoked = false;
	nRet = webrtc_foreach_stats(webrtcOfferer, WEBRTC_STATS_TYPE_ALL, webrtcStatsCB, &cb_data2);

	RUN_POLLING_LOOP(cb_data2.mainloop, cb_data2.is_invoked);
	if (!cb_data2.is_invoked) {
		FPRINTF("[Line : %d][%s] Callback webrtcStatsCB not invoked for WEBRTC_STATS_TYPE_ALL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_foreach_stats", WebRtcGetError(nRet));

	nRet = webrtc_stop(webrtcOfferer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));

	nRet = webrtc_destroy(webrtcOfferer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy", WebRtcGetError(nRet));

	nRet = webrtc_stop(webrtcAnswerer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_stop", WebRtcGetError(nRet));

	nRet = webrtc_destroy(webrtcAnswerer);
	PRINT_RESULT(WEBRTC_ERROR_NONE, nRet, "webrtc_destroy", WebRtcGetError(nRet));

	g_list_free_full(offerICECandidates, free);
	g_list_free_full(answerICECandidates, free);

	return 0;
}

/** @} */
/** @} */
