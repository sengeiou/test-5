//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	 http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include <curl/curl.h>
#include "ITs-player-common.h"
#include "net_connection.h"

/** @addtogroup itc-player
*  @ingroup itc
*  @{
*/

//& set: Player
#define EXPORT_PCM_SAMPLERATE	44100
#define EXPORT_PCM_STEREO	2
#define EXPORT_PCM_MONO		1
#define TIMEOUT2		3000
#define LIMIT			10

bool g_bPlayerCreation;
bool g_bPlayerVideoCaptureCallback;
bool g_bPlayerAudioEffectSupportedEffectCallback;
bool g_bPlayerAudioEffectSupportedPresetCallback;
bool g_bPlayerAudioFrameDecodedCallback;
bool g_bPlayerBufferingCallback;
bool g_bPlayerCompletedCallback;
bool g_bPlayerErrorCallback;
bool g_bPlayerInterruptedCallback;
bool g_bPlayerMediaPacketVideoFrameDecodedCallback;
bool g_bPlayerSeekCompletedCallback;
bool g_bPlayerPreparedCallback;
bool g_bPlayerVideoStreamChanged;
bool g_bPlayerAudioStreamChanged;
bool g_bPlayerMediaStreamSeek;
bool g_bPlayerMediaStreamBufferStatus;
bool g_bPlayerCallbackParameter;
bool g_bPlayerInterruptCbCallback;
bool g_bPlayerAudioDecodedCallback;
bool g_bPlayerAudioOffloadFormatCallback;
bool g_bPlayerSupportedMediaFormatCallback;
player_audio_extract_option_e g_ePlayerAudioExtractOption;
media_format_mimetype_e g_eMediaFormatMimetype;

static connection_h g_connection = NULL;

#ifdef TIZENIOT // For TIZENIOT
	int g_nTimeoutId;
	GMainLoop *g_pMainLoop;
#endif // TIZENIOT

/**
* @function			ITs_player_startup
* @description		Called before each test, created player handle
* @parameter		NA
* @return			NA
*/
void ITs_player_startup(void)
{
#ifndef TIZENIOT // For Mobile or Wearable
	ecore_main_loop_glib_integrate();
#endif // Mobile or Wearable
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		int ret = remove(ERR_LOG);
		if(ret == -1)
		{
			FPRINTF("[Line: %d][%s] unlinking file name error =%s \\n", __LINE__, API_NAMESPACE,ERR_LOG);
			return;
		}
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Player_p\\n", __LINE__, API_NAMESPACE);
#endif

#ifndef TIZENIOT // For Mobile or Wearable
	CreateEvasWindow();
	if ( g_pEvasObject == NULL )
	{
		FPRINTF("[Line : %d][%s] Evas window object is not created, failed in Precondition\\n", __LINE__, API_NAMESPACE);
		g_bPlayerCreation = false;
		return;
	}
#endif // Mobile or Wearable

	int nRet = player_create(&g_player);
	if ( nRet != PLAYER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to create player, error returned = %s\\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		g_bPlayerCreation = false;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Player created successfully\\n",__LINE__, API_NAMESPACE);
		g_bPlayerCreation = true;
	}
	return;
}

/**
* @function			ITs_player_cleanup
* @description		Called after each test, destroys player handle
* @parameter		NA
* @return			NA
*/
void ITs_player_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Player_p\\n", __LINE__, API_NAMESPACE);
#endif
	if ( g_bPlayerCreation && g_player )
	{
		int nRet = player_destroy (g_player);
		if ( nRet != PLAYER_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] player_destroy failed, error returned = %s\\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		}
		g_player = NULL;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Player was not created\\n",__LINE__, API_NAMESPACE);
	}
#ifndef TIZENIOT // For Mobile or Wearable
	if ( g_pEvasObject )
	{
		evas_object_del(g_pEvasObject);
		g_pEvasObject = NULL;
	}
	if ( g_pEvasWindow )
	{
		evas_object_del(g_pEvasWindow);
		g_pEvasWindow = NULL;
	}
#endif // Mobile or Wearable
	return;
}

#ifdef TIZENIOT // For TIZENIOT
/**
* @function 		QuitGmainLoop
* @description	 	Called to quit
* @parameter		NA
* @return 			NA
*/
static void QuitGmainLoop(void)
{
	if(g_pMainLoop)
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

/**
* @function			PlayerTimeoutFunction
* @description		Called if some callback is not invoked for a particular Player Timeout
* @parameter		gpointer data
* @return			gboolean
*/
static gboolean PlayerTimeoutFunction(gpointer data)
{
	QuitGmainLoop();
	return FALSE;
}

/**
* @function			PlayerWaitForAsync
* @description		Called to wait
* @parameter		NA
* @return			NA
*/

static void PlayerWaitForAsync()
{
	if (!g_bPlayerBufferingCallback || !g_bPlayerCallbackParameter || !g_bPlayerCompletedCallback || !g_bPlayerMediaPacketVideoFrameDecodedCallback || !g_bPlayerPreparedCallback || !g_bPlayerSeekCompletedCallback || !g_bPlayerAudioOffloadFormatCallback)
	{
		g_pMainLoop = g_main_loop_new(NULL, false);
		g_nTimeoutId = g_timeout_add(TIMEOUT, PlayerTimeoutFunction, NULL);
		g_main_loop_run(g_pMainLoop);

		g_source_remove(g_nTimeoutId);
		g_nTimeoutId = 0;

		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function		PlayerWaitForAsync2
* @description		Called to wait
* @parameter		int timeout
* @return		NA
*/

static void PlayerWaitForAsync2(int timeout)
{
	if (!g_bPlayerAudioDecodedCallback)
	{
		g_pMainLoop = g_main_loop_new(NULL, false);
		g_nTimeoutId = g_timeout_add(timeout, PlayerTimeoutFunction, NULL);
		g_main_loop_run(g_pMainLoop);

		g_source_remove(g_nTimeoutId);
		g_nTimeoutId = 0;

		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}
#else // For Mobile or Wearable
/**
* @function			PlayerTimeoutFunction
* @description		Called if some callback is not invoked for a particular Player Timeout
* @parameter		gpointer data
* @return			gboolean
*/
static gboolean PlayerTimeoutFunction(gpointer data)
{
	ecore_main_loop_quit();
	return FALSE;
}

/**
* @function			PlayerWaitForAsync
* @description		Called to wait
* @parameter		NA
* @return			NA
*/
static void PlayerWaitForAsync()
{
	g_timeout_add(TIMEOUT, PlayerTimeoutFunction, NULL);
	ecore_main_loop_begin();
}

/**
* @function			PlayerWaitForAsync2
* @description		Called to wait
* @parameter		int timeout
* @return			NA
*/
static void PlayerWaitForAsync2(int timeout)
{
	g_timeout_add(timeout, PlayerTimeoutFunction, NULL);
	ecore_main_loop_begin();
}

//Callbacks

/**
* @function				PlayerVideoCaptureCallback
* @description			Callback function which is invoked when the video is captured
* @parameter			unsigned char *data, int width, int height, unsigned int size, void *user_data
* @return				void
*/
static void PlayerVideoCaptureCallback(unsigned char *data, int width, int height, unsigned int size, void *user_data)
{
	g_bPlayerVideoCaptureCallback = true;
	ecore_main_loop_quit();
}
#endif // End of Mobile or Wearable

//Callbacks


/**
* @function				PlayerInterruptCb
* @description			Called when the media player is interrupted.
* @parameter			void *user_data
* @parameter			player_interrupted_code_e code
* @return				void
*/
static void PlayerInterruptCb(player_interrupted_code_e code, void *user_data)
{
	g_bPlayerInterruptCbCallback = true;
}

/**
* @function				PlayerBufferingCallback
* @description			Callback function which is invoked when the buffering percentage of media playback is updated
* @parameter			int percent, void *user_data
* @return				void
*/
static void PlayerBufferingCallback(int percent, void *user_data)
{
	g_bPlayerBufferingCallback = true;
	if(percent < 0)
	{
		FPRINTF("[Line : %d][%s] percent is not valid\\n", __LINE__, API_NAMESPACE);
		g_bPlayerCallbackParameter = false;
	}
	else
	{
		g_bPlayerCallbackParameter = true;
	}
#ifndef TIZENIOT // For Mobile or Wearable
	ecore_main_loop_quit();
#endif // Mobile or Wearable
}

//Callbacks

/**
* @function				PlayerCompletedCallback
* @description			Callback function which is invoked when the media player is completed
* @parameter			void *user_data
* @return				void
*/
static void PlayerCompletedCallback(void *user_data)
{
	g_bPlayerCompletedCallback = true;
#ifndef TIZENIOT // For Mobile or Wearable
	ecore_main_loop_quit();
#endif // Mobile or Wearable
}

//Callbacks

/**
* @function				PlayerErrorCallback
* @description			Callback function which is invoked when the media player's error occurred
* @parameter			int error_code, void *user_data
* @return				void
*/
static void PlayerErrorCallback(int error_code, void *user_data)
{
	g_bPlayerErrorCallback = true;
#ifndef TIZENIOT // For Mobile or Wearable
	ecore_main_loop_quit();
#endif // Mobile or Wearable
}

//Callbacks

/**
* @function				PlayerSeekCompletedCallback
* @description			Callback function which is invoked when the progressive download is started or completed
* @parameter			void *user_data
* @return				void
*/
static void PlayerSeekCompletedCallback(void *user_data)
{
	g_bPlayerSeekCompletedCallback = true;
#ifndef TIZENIOT // For Mobile or Wearable
	ecore_main_loop_quit();
#endif // Mobile or Wearable
}

//Callbacks

/**
* @function			PlayerPreparedCallback
* @description			Callback function which is invoked when the media player is prepared
* @parameter			void *user_data
* @return				void
*/
static void PlayerPreparedCallback(void *user_data)
{
	g_bPlayerPreparedCallback = true;
#ifndef TIZENIOT // For Mobile or Wearable
	ecore_main_loop_quit();
#endif // Mobile or Wearable
}

//Callbacks

/**
* @function				PlayerMediaPacketVideoFrameDecodedCallback
* @description			Callback function which is invoked when the every video frame is decoded
* @parameter			unsigned char *data, int width, int height, unsigned int size, void *user_data
* @return				void
*/
static void PlayerMediaPacketVideoFrameDecodedCallback(media_packet_h pkt, void *user_data)
{
	g_bPlayerMediaPacketVideoFrameDecodedCallback = true;
	if(pkt == NULL)
	{
		FPRINTF("[Line : %d][%s] packet handle is not valid\\n", __LINE__, API_NAMESPACE);
		g_bPlayerCallbackParameter = false;
	}
	else
	{
		media_packet_destroy(pkt);
		g_bPlayerCallbackParameter = true;
	}
#ifndef TIZENIOT // For Mobile or Wearable
	ecore_main_loop_quit();
#endif // Mobile or Wearable
}

/**
* @function				PlayerAudioDecodedCb
* @description			Called to register for notifications about delivering media packet when audio frame is decoded.
* @parameter			media_packet_h pkt, void *user_data
* @return				void
*/
static void PlayerAudioDecodedCb(media_packet_h pkt, void *user_data)
{
	media_format_h hMediaFormat = NULL;
	unsigned int nMime = 0, nChannel = 0, nRate = 0;
	uint64_t tChannelMask = 0;
	static uint64_t tMask = 0;

	if (!pkt) {
		FPRINTF("[Line : %d][%s] invalid pkt\n", __LINE__, API_NAMESPACE);
		return;
	}

	int nRet = media_packet_get_format(pkt, &hMediaFormat);
	if(nRet != MEDIA_PACKET_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] media_packet_get_format failed.\n", __LINE__, API_NAMESPACE);
		return;
	}
	if(hMediaFormat == NULL)
	{
		FPRINTF("[Line : %d][%s] media_packet_get_format failed. Handle not set\n", __LINE__, API_NAMESPACE);
		return;
	}

	nRet = media_format_get_audio_info(hMediaFormat, (media_format_mimetype_e *)&nMime, &nChannel, &nRate, NULL, NULL);
	if(nRet != MEDIA_PACKET_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] media_format_get_audio_info failed.\n", __LINE__, API_NAMESPACE);
		return;
	}

	nRet = media_format_get_audio_channel_mask(hMediaFormat, &tChannelMask);
	if(nRet != MEDIA_PACKET_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] media_format_get_audio_channel_mask failed.\n", __LINE__, API_NAMESPACE);
		return;
	}

	if (tMask == 0) {
		tMask = tChannelMask;
	}

	if ((nMime == g_eMediaFormatMimetype) && (nRate == EXPORT_PCM_SAMPLERATE) && (tMask != tChannelMask) && (nChannel == EXPORT_PCM_MONO))
		g_bPlayerAudioDecodedCallback = true;

	media_packet_destroy(pkt);
#ifndef TIZENIOT // For Mobile or Wearable
	ecore_main_loop_quit();
#endif // Mobile or Wearable
}

//Callbacks

/**
* @function				PlayerMediaStreamBufferStatusCallback
* @description			Called to check media stream buffer status
* @parameter			player_media_stream_buffer_status_e status, void *user_data
* @return				void
*/

static void PlayerMediaStreamBufferStatusCallback(player_media_stream_buffer_status_e status, void *user_data)
{
	g_bPlayerMediaStreamBufferStatus = true;
#ifndef TIZENIOT // For Mobile or Wearable
	ecore_main_loop_quit();
#endif // Mobile or Wearable
}

//Callbacks

/**
* @function				PlayerVideoStreamChangedCallback
* @description			Called to notify the video stream changed.
* @parameter			int width, int height, int fps, int bit_rate, void *user_data
* @return				void
*/
static void PlayerVideoStreamChangedCallback(int width, int height, int fps, int bit_rate, void *user_data)
{
	g_bPlayerVideoStreamChanged = true;
	if(width < 0)
	{
		FPRINTF("[Line : %d][%s] width is not valid\\n", __LINE__, API_NAMESPACE);
		g_bPlayerCallbackParameter = false;
	}
	else if(height < 0)
	{
		FPRINTF("[Line : %d][%s] height is not valid\\n", __LINE__, API_NAMESPACE);
		g_bPlayerCallbackParameter = false;
	}
	else if(fps < 0)
	{
		FPRINTF("[Line : %d][%s] fps is not valid\\n", __LINE__, API_NAMESPACE);
		g_bPlayerCallbackParameter = false;
	}
	else if(bit_rate < 0)
	{
		FPRINTF("[Line : %d][%s] bit_rate is not valid\\n", __LINE__, API_NAMESPACE);
		g_bPlayerCallbackParameter = false;
	}
	else
	{
		g_bPlayerCallbackParameter = true;
	}
#ifndef TIZENIOT // For Mobile or Wearable
	ecore_main_loop_quit();
#endif
}


//Callbacks

/**
* @function				PlayerMediaStreamSeekCallBack
* @description			Called to notify the next push-buffer offset when seeking is occurred.
* @parameter			unsigned long long offset, void *user_data
* @return				void
*/

static void PlayerMediaStreamSeekCallBack(unsigned long long offset, void *user_data)
{
	g_bPlayerMediaStreamSeek = true;
#ifndef TIZENIOT // For Mobile or Wearable
	ecore_main_loop_quit();
#endif
}

/**
* @function				ByteStreamToNalUnit
* @description			Change byte stream to char pointer
* @parameter			FILE *fd, unsigned char* nal
* @return				void
*/
unsigned char sps[100] = {'\0'};
unsigned char pps[100] = {'\0'};
int sps_len = 0, pps_len = 0;

unsigned int ByteStreamToNalUnit(FILE *fd, unsigned char* nal)
{
	unsigned char tmp_buf[1000000] = {'\0'};
	int nal_length = 0;
	size_t result;
	int read_size = 1;
	unsigned char buffer[1000000];
	unsigned char val, zero_count, i;
	int nal_unit_type = 0;
	int init;

	zero_count = 0;
	if ( feof(fd) )
	{
		return -1;
	}

	result = fread(buffer, 1, read_size, fd);

	if ( result != read_size )
	{
		return -1;
	}

	val = buffer[0];
	while (!val)
	{
		zero_count++;
		result = fread(buffer, 1, read_size, fd);

		if ( result != read_size )
		{
			break;
		}
		val = buffer[0];
		if ((zero_count == 2 || zero_count == 3) && val == 1)
			break;
	}
	nal[nal_length++] = 0;
	nal[nal_length++] = 0;
	nal[nal_length++] = 0;
	nal[nal_length++] = 1;
	zero_count = 0;
	init = 1;
	while(1)
	{
		if (feof(fd))
		{
			return nal_length;
		}

		result = fread(buffer, 1, read_size, fd);
		if ( result != read_size )
		{
			break;
		}
		val = buffer[0];

		if ( init )
		{
			nal_unit_type = val & 0xf;
			init = 0;
		}
		if (!val)
		{
			zero_count++;
		}
		else
		{
			if ((zero_count == 2 || zero_count == 3 || zero_count == 4) && (val == 1))
				break;
			else
			{
				for (i = 0; i<zero_count; i++)
				{
					nal[nal_length++] = 0;
				}
				nal[nal_length++] = val;
				zero_count = 0;
			}
		}
	}

	fseek(fd, -(zero_count + 1), SEEK_CUR);

	if (nal_unit_type == 0x7)
	{
		sps_len = nal_length;
		memcpy(sps, nal, nal_length);
		return 0;
	}
	else if (nal_unit_type == 0x8)
	{
		pps_len = nal_length;
		memcpy(pps, nal, nal_length);
		return 0;
	}
	else if (nal_unit_type == 0x5)
	{
		memcpy(tmp_buf, nal, nal_length);
		memcpy(nal, sps, sps_len);
		memcpy(nal + sps_len, pps, pps_len);
		memcpy(nal + sps_len + pps_len, tmp_buf, nal_length);
		nal_length += sps_len + pps_len;
	}

	return nal_length;
}

/**
* @function				FeedVideoData
* @description			helper function to call player_push_media_stream api
* @parameter			void
* @return				void
*/
static void FeedVideoData(void)
{
	int read = 0;
	static guint64 pts = 0L;
	void *buf_data_ptr = NULL;
	media_packet_h hMediaPacket = NULL;

	int nRet = media_packet_create_alloc(g_hMediaFormat, NULL, NULL, &hMediaPacket);
	if ( nRet != MEDIA_PACKET_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] media_packet_create_alloc failed. Error Returned = %s\\n", __LINE__, API_NAMESPACE, MediaPacketGetError(nRet));
		return;
	}

	nRet = media_packet_get_buffer_data_ptr(hMediaPacket, &buf_data_ptr);
	if ( nRet != MEDIA_PACKET_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] media_packet_get_buffer_data_ptr failed. Error Returned = %s\\n", __LINE__, API_NAMESPACE, MediaPacketGetError(nRet));
		media_packet_destroy(hMediaPacket);
		return;
	}

	nRet = media_packet_set_pts(hMediaPacket, (uint64_t)(pts/1000000));
	if ( nRet != MEDIA_PACKET_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] media_packet_set_pts failed. Error Returned = %s\\n", __LINE__, API_NAMESPACE, MediaPacketGetError(nRet));
		media_packet_destroy(hMediaPacket);
		return;
	}

	read = ByteStreamToNalUnit(file_src, buf_data_ptr);
	if ( read == 0 )
	{
		media_packet_destroy(hMediaPacket);
		return;
	}


	nRet = media_packet_set_buffer_size(hMediaPacket, read);
	if ( nRet != MEDIA_PACKET_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] media_packet_set_buffer_size failed. Error Returned = %s\\n", __LINE__, API_NAMESPACE, MediaPacketGetError(nRet));
		media_packet_destroy(hMediaPacket);
		return;
	}

	//Target API
	g_nRet = player_push_media_stream(g_player, hMediaPacket);
	pts += ES_DEFAULT_VIDEO_PTS_OFFSET;

	media_packet_destroy(hMediaPacket);
	hMediaPacket = NULL;
	return;
}

/**
* @function				FeedVideoDataThreadFunc
* @description			Thread funbction to call function to call feed_video_data function
* @parameter			void
* @return				void
*/
static void FeedVideoDataThreadFunc()
{
	gboolean exit = FALSE;

	while (!exit)
	{
		static int frame_count = 0;

		if (frame_count < ES_NUMBER_OF_FEED)
		{
			FeedVideoData();
			frame_count++;
		}
		else
		{
			exit = TRUE;
		}
	}
	pthread_exit(0);
}

//Callbacks

/**
* @function				PlayerPreparedCB
* @description			Called to check media player for playback, asynchronously
* @parameter			void *user_data
* @return				void
*/
static void PlayerPreparedCB(void *user_data)
{
	int nRet = player_start(g_player);
	if ( PLAYER_ERROR_NONE != nRet )
	{
		FPRINTF("[Line : %d][%s] player_start is failed\\n", __LINE__, API_NAMESPACE);
	}
}

bool CheckOnlineStatus(char *media_path)
{
	bool ret = true;
	CURL *curl = NULL;
	CURLcode res = CURLE_OK;

	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, media_path);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT_MS, 4500L);
		curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
		curl_easy_setopt(curl, CURLOPT_IPRESOLVE, 1L);

		res = curl_easy_perform(curl);
		if(res != CURLE_OK) {
			FPRINTF("[Line : %d][%s] curl_easy_perform() failed: %s\n", __LINE__, API_NAMESPACE, curl_easy_strerror(res));
			ret = false;
		}

		curl_easy_cleanup(curl);
	}

	return ret;

}

bool CheckConnectionStatistics(connection_h connection, long long *size)
{
	long long rv = 0;
	int err = CONNECTION_ERROR_NONE;
	connection_type_e type = CONNECTION_TYPE_DISCONNECTED;
	bool wifi_supported = false;
	bool telepony_supported = false;

	system_info_get_platform_bool(WIFI_FEATURE, &wifi_supported);
	system_info_get_platform_bool(TELEPHONY_FEATURE, &telepony_supported);

	if (wifi_supported) {
		type = CONNECTION_TYPE_WIFI;
	} else if (telepony_supported) {
		type = CONNECTION_TYPE_CELLULAR;
	} else {
		FPRINTF("[Line : %d][%s] network is not supportable.\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	err = connection_get_statistics(connection, type, CONNECTION_STATISTICS_TYPE_TOTAL_RECEIVED_DATA, &rv);

	if (err != CONNECTION_ERROR_NONE) {
		FPRINTF("[Line : %d][%s] Failed to check connection statistics.\\n", __LINE__, API_NAMESPACE);
		return false;
	} else {
		FPRINTF("[Line : %d][%s] WiFi last recv data size [%lld]\\n", __LINE__, API_NAMESPACE, rv);
	}

	*size = rv;
	return true;
}


int PlayerPrepareWithConnectionCheck(player_h g_player)
{
	int ret = PLAYER_ERROR_NONE;
	long long before = 0, after = 0;

	if (connection_create(&g_connection) != CONNECTION_ERROR_NONE) {
		FPRINTF("[Line : %d][%s] Failed to create connection handle\\n", __LINE__, API_NAMESPACE);
	} else {
		FPRINTF("[Line : %d][%s] Success to create connection handle %p\\n", __LINE__, API_NAMESPACE, g_connection);
	}

	if (g_connection && !CheckConnectionStatistics(g_connection, &before)) {
		FPRINTF("[Line : %d][%s] Failed to get connection statistics\\n", __LINE__, API_NAMESPACE);
	}

	ret = player_prepare(g_player);
	if (g_connection) {
		if (!CheckConnectionStatistics(g_connection, &after)) {
			FPRINTF("[Line : %d][%s] Failed to get connection statistics\\n", __LINE__, API_NAMESPACE);
		} else {
			FPRINTF("[Line : %d][%s][Reference] total received data [%lld]\\n",
									__LINE__, API_NAMESPACE, (after-before));
		}
	}

	if (g_connection && connection_destroy(g_connection) != CONNECTION_ERROR_NONE) {
		FPRINTF("[Line : %d][%s] Failed to destroy connection handle\\n", __LINE__, API_NAMESPACE);
	}

	return ret;
}


static int PlayerStartWithConnectionCheck(player_h g_player, char* media_path)
{
	int ret = PLAYER_ERROR_NONE;
	long long before = 0, after = 0;

	if (!CheckOnlineStatus(media_path)) {
		FPRINTF("[Line : %d][%s][Reference] network is disconnected\\n", __LINE__, API_NAMESPACE);
	}

	if (connection_create(&g_connection) != CONNECTION_ERROR_NONE) {
		FPRINTF("[Line : %d][%s] Failed to create connection handle\\n", __LINE__, API_NAMESPACE);
	} else {
		FPRINTF("[Line : %d][%s] Success to create connection handle %p\\n", __LINE__, API_NAMESPACE, g_connection);
	}

	if (g_connection && !CheckConnectionStatistics(g_connection, &before)) {
		FPRINTF("[Line : %d][%s] Failed to get connection statistics\\n", __LINE__, API_NAMESPACE);
	}

	ret = player_prepare(g_player);
	if (ret != PLAYER_ERROR_NONE) {
		if (g_connection) {
			if (!CheckConnectionStatistics(g_connection, &after)) {
				FPRINTF("[Line : %d][%s] Failed to get connection statistics\\n", __LINE__, API_NAMESPACE);
			} else {
				FPRINTF("[Line : %d][%s][Reference] total received data [%lld]\\n",
									__LINE__, API_NAMESPACE, (after-before));
			}
		}

		FPRINTF("[Line : %d][%s] player_prepare failed, error returned = %s\\n",
							__LINE__, API_NAMESPACE, PlayerGetError(ret));
		goto EXIT;
	}

	sleep(3);

	/* progressive download case have to include player_start for checking network env */
	ret = player_start(g_player);

	if (g_connection) {
		if (!CheckConnectionStatistics(g_connection, &after)) {
			FPRINTF("[Line : %d][%s] Failed to get connection statistics\\n", __LINE__, API_NAMESPACE);
		} else {
			FPRINTF("[Line : %d][%s][Reference] total received data [%lld]\\n", __LINE__, API_NAMESPACE, (after-before));
		}
	}

	if (ret != PLAYER_ERROR_NONE) {
		FPRINTF("[Line : %d][%s] player_start failed, error returned = %s\\n",
							__LINE__, API_NAMESPACE, PlayerGetError(ret));
	}

EXIT:
	if (g_connection && connection_destroy(g_connection) != CONNECTION_ERROR_NONE) {
		FPRINTF("[Line : %d][%s] Failed to destroy connection handle\\n", __LINE__, API_NAMESPACE);
	}

	return ret;
}

/**
* @function			AudioOffloadFormatCB
* @description			Callback function which is invoked when foreach_supported foramt is called
* @parameter			media_format_mimetype_e eMediaFormat, void *pszData
* @return			void
*/
static bool AudioOffloadFormatCB(media_format_mimetype_e eMediaFormat, void *pszData)
{
	g_bPlayerAudioOffloadFormatCallback = true;
#ifndef TIZENIOT // For Mobile or Wearable
	ecore_main_loop_quit();
#endif // Mobile or Wearable
	return true;
}

/**
* @function			PlayerSupportedMediaFormatCB
* @description			Called when player_foreach_media_stream_supported_format is called.
* @parameter			media_format_mimetype_e eMediaFormat
* @parameter			void *pszData
* @return			bool true/false
*/
static bool PlayerSupportedMediaFormatCB(media_format_mimetype_e eMediaFormat, void *pszData)
{
	g_bPlayerSupportedMediaFormatCallback = true;
#if DEBUG
	FPRINTF("[Line : %d][%s] PlayerSupportedMediaFormatCB callback called \\n", __LINE__, API_NAMESPACE);
#endif
	return true;
}


/** @addtogroup itc-player-testcases
*  @brief		Integration testcases for module player
*  @ingroup		itc-player
*  @{
*/


//& purpose: Starts or resumes playback.
//& type : auto
/**
* @testcase				ITc_player_start_p
* @author				SRID(priya.kohli)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @since_tizen			2.3
* @description			Plays current media content, or resumes playback if the player is paused or buffering during HTTP streaming play.
* @scenario				Starts player.
* @apicovered			player_prepare, player_unprepare, player_get_state, player_start
* @passcase				If player is started successfully.
* @failcase				If player is not started successfully.
* @precondition			Before 5.0: The player state must be #PLAYER_STATE_READY or #PLAYER_STATE_PAUSED.
*						Since 5.0: The player state must be one of #PLAYER_STATE_READY, #PLAYER_STATE_PLAYING, or #PLAYER_STATE_PAUSED
* @postcondition		N/A
*/
int ITc_player_start_p(void)
{
	START_TEST;
	player_state_e state;

	char pPath[PATH_LEN] = {0};
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_AUDIO, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = player_get_state(g_player,&state);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_IDLE )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_create() call",__LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_set_uri(g_player, pPath);

	#if defined(WEARABLE)
		bool bValue = false;
		system_info_get_platform_bool(INTERNET_FEATURE, &bValue);
		if(bValue == false)
		{
			if(nRet != PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE)
			{
				FPRINTF("[Line : %d][%s] player_set_uri API call returned mismatch %s error for unsupported internet feature\\n", __LINE__, API_NAMESPACE,	PlayerGetError(nRet));
				return 1;
			}
		}
	#endif
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	nRet = player_prepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_prepare() call", __LINE__, API_NAMESPACE);
		player_unprepare(g_player);
		return 1;
	}

	sleep(3);

	nRet = player_start(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_start() call", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_start(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	nRet = player_stop(g_player);
	PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	nRet = player_unprepare(g_player);
	PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

    return 0;
}

//& purpose: create and destroy player
//& type : auto
/**
* @testcase				ITc_player_create_destroy_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			create and destroy player
* @scenario				Create player\n
*						destroy player
* @apicovered			player_create, player_destroy
* @passcase				When it can create and destroy player
* @failcase				When it can not create and destroy player
* @precondition			N/A
* @postcondition		N/A
*/
int ITc_player_create_destroy_p(void)
{
	START_TEST;
	usleep(2000);

	int nRet = player_destroy(g_player);
	if (nRet != PLAYER_ERROR_NONE) {
		FPRINTF("[Line : %d][%s] destroy return %s error \\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		return 1;
	}

	usleep(2000);

	// Target API
	nRet = player_create(&g_player);
	if (nRet != PLAYER_ERROR_NONE) {
		FPRINTF("[Line : %d][%s] create return %s error \\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		return 1;
	}

	usleep(2000);

	// Target API
	nRet = player_destroy(g_player);
	if (nRet != PLAYER_ERROR_NONE) {
		FPRINTF("[Line : %d][%s] destroy return %s error \\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		return 1;
	}

	nRet = player_create(&g_player);
	if (nRet != PLAYER_ERROR_NONE) {
		FPRINTF("[Line : %d][%s] create return %s error \\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		return 1;
	}

	return 0;
}

//& purpose: Initialize player
//& type : auto
/**
* @testcase				ITc_player_initialize_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			create and destroy player
* @scenario				Create player\n
*						destroy player
* @apicovered			player_create, player_state, player_set_uri, player_prepare, player_unprepare
* @passcase				When it can initialize player
* @failcase				When it can not create and destroy player
* @precondition			N/A
* @postcondition		N/A
*/
int ITc_player_initialize_p(void)
{
	START_TEST;
	player_state_e state;

	char pPath[PATH_LEN] = {0};
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_AUDIO, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	//Target API
	int nRet = player_get_state(g_player,&state);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_IDLE )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_create() call",__LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_set_uri(g_player, pPath);

	#if defined(WEARABLE)
		bool bValue = false;
		system_info_get_platform_bool(INTERNET_FEATURE, &bValue);
		if(bValue == false)
		{
			if(nRet != PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE)
			{
				FPRINTF("[Line : %d][%s] player_set_uri API call returned mismatch %s error for unsupported internet feature\\n", __LINE__, API_NAMESPACE,	PlayerGetError(nRet));
				return 1;
			}
		}
	#endif
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	nRet = player_prepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}

//& purpose: Registers a callback function to be invoked when there is a change in the buffering status of a media stream
//& type : auto
/**
* @testcase				ITc_player_set_unset_buffering_cb_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Registers a callback function to be invoked when there is a change in the buffering status of a media stream
* @scenario				call player_set_buffering_cb\n
*						check if callback is hit\n
*						destroy the handler\n
* @apicovered			player_set_buffering_cb, player_unset_buffering_cb, player_prepare, player_unprepare, player_get_state, player_start, player_stop.
* @passcase				Callback is hit
* @failcase				Callback is not hit
* @precondition			NA
* @postcondition		player_buffering_cb() will be invoked
*/
int ITc_player_set_unset_buffering_cb_p(void)
{
	START_TEST;

	bool bTelFeatureSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE, API_NAMESPACE);
	bool bWifiFeatureSupported = TCTCheckSystemInfoFeatureSupported(WIFI_FEATURE, API_NAMESPACE);
	bool bEthFeatureSupported = TCTCheckSystemInfoFeatureSupported(ETHERNET_FEATURE, API_NAMESPACE);
	if ( !bTelFeatureSupported && !bWifiFeatureSupported && !bEthFeatureSupported)
	{
		FPRINTF("[Line : %d][%s] Network is not working. Skipping Test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	player_state_e state;

	if ( InitializePlayerHandler(false, 2) != true )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	g_bPlayerBufferingCallback = false;
	g_bPlayerCallbackParameter = false;

	int nRet = player_set_buffering_cb(g_player, PlayerBufferingCallback, NULL);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_buffering_cb", PlayerGetError(nRet));

	usleep(2000);

	nRet = PlayerPrepareWithConnectionCheck(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_prepare() call", __LINE__, API_NAMESPACE);
		return 1;
	}

	usleep(2000);

	PlayerWaitForAsync();
	if ( !g_bPlayerBufferingCallback )
	{
		FPRINTF("[Line : %d][%s] player_buffering_cb failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		player_unprepare(g_player);
		return 1;
	}
	else if(!g_bPlayerCallbackParameter)
	{
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_unset_buffering_cb(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_unset_buffering_cb", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}

//& purpose: Registers a callback function to be invoked when error occurred
//& type : auto
/**
* @testcase				ITc_player_set_unset_error_cb_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Registers a callback function to be invoked when error occurred
* @scenario				call player_set_error_cb\n
*						check if callback is hit\n
*						destroy the handler
* @apicovered			player_set_error_cb, player_unset_error_cb
* @passcase				Callback is hit
* @failcase				Callback is not hit
* @precondition			NA
* @postcondition		player_error_cb() will be invoked
*/
int ITc_player_set_unset_error_cb_p(void)
{
	START_TEST;

	int nRet = player_set_error_cb(g_player, PlayerErrorCallback, NULL);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_error_cb", PlayerGetError(nRet));

	/** Manual Interruption needed to hit Callback so callback hit check is ignored **/

	nRet = player_unset_error_cb(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unset_error_cb", PlayerGetError(nRet));

	return 0;
}

//& purpose: Gets the download progress for streaming playback
//& type: auto
/**
* @testcase				ITc_player_get_streaming_download_progress_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Gets the download progress for streaming playback
* @scenario				Initialize player handle\n
*						set progressive download path\n
*						prepare the player\n
*						start the player\n
*						get download progress for streaming playback\n
*						check results\n
*						destroy the handler
* @apicovered			player_set_uri, player_prepare, player_get_streaming_download_progress, player_unprepare
* @passcase				When it set progressive download path and get download progress for streaming playback
* @failcase				When it does not set progressive download path or get download progress for streaming playback
* @precondition			The player state must be one of these: PLAYER_STATE_PLAYING or PLAYER_STATE_PAUSED or PLAYER_STATE_READY
* @postcondition		N/A
*/
int ITc_player_get_streaming_download_progress_p(void)
{
	START_TEST;

	bool bTelFeatureSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE, API_NAMESPACE);
	bool bWifiFeatureSupported = TCTCheckSystemInfoFeatureSupported(WIFI_FEATURE, API_NAMESPACE);
	bool bEthFeatureSupported = TCTCheckSystemInfoFeatureSupported(ETHERNET_FEATURE, API_NAMESPACE);
	if ( !bTelFeatureSupported && !bWifiFeatureSupported && !bEthFeatureSupported)
	{
		FPRINTF("[Line : %d][%s] Network is not working. Skipping Test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	int nStart, nEnd;
	player_state_e state;

	int nRet = -1;
	#ifndef TIZENIOT // For Mobile or Wearable
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_EVAS, g_pEvasObject);
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif //End MOBILE or WEARABLE

	char pstrValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == GetValueFromConfigFile("PLAYER_HTTP_STREAMING_URL", pstrValue, API_NAMESPACE))
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE, pstrValue);
#endif
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueFromConfigFile returned error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	nRet = player_set_uri(g_player, pstrValue);
	#if defined(WEARABLE)
		bool bValue = false;
		system_info_get_platform_bool(INTERNET_FEATURE, &bValue);
		if(bValue == false)
		{
			if(nRet != PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE)
			{
				FPRINTF("[Line : %d][%s] player_set_uri API call returned mismatch %s error for unsupported internet feature\\n", __LINE__, API_NAMESPACE,	PlayerGetError(nRet));
				return 1;
			}
		}
	#endif
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	nRet = PlayerStartWithConnectionCheck(g_player, pstrValue);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "start playback", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	PlayerGetState(state);

	if ( state != PLAYER_STATE_PLAYING && state != PLAYER_STATE_PAUSED && state != PLAYER_STATE_READY)
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_start() call", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_get_streaming_download_progress(g_player, &nStart, &nEnd);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_streaming_download_progress", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	if (nStart < 0 || nStart > 100 || nEnd < 0 || nEnd > 100) {
		FPRINTF("[Line : %d][%s] Start and end position are not in range. nStart = %d, nEnd = %d ", __LINE__, API_NAMESPACE, nStart, nEnd);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_stop(g_player);
	PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet));

	nRet = player_unprepare(g_player);
	PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}

//& purpose: Sets memory as the data source
//& type : auto
/**
* @testcase				ITc_player_set_memory_buffer_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Sets memory as the data source
* @scenario				call player_set_memory_buffer\n
*						destroy the handler
* @apicovered			player_set_memory_buffer, player_prepare, player_unprepare
* @passcase				If it sets memory buffer successfully
* @failcase				If it does not sets memory buffer successfully
* @precondition			The player state should be PLAYER_STATE_IDLE by player_create() or player_unprepare()
* @postcondition		NA
*/
int ITc_player_set_memory_buffer_p(void)
{
	START_TEST;

	player_state_e state;
	GMappedFile* file;
	gsize file_size;
	guint8* g_media_mem = NULL;

	char pPath[PATH_LEN] = {0,};
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_VIDEO, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	file = g_mapped_file_new (pPath, FALSE,NULL);
	file_size = g_mapped_file_get_length (file);
	g_media_mem = (guint8 *) g_mapped_file_get_contents (file);

	int nRet = player_set_memory_buffer(g_player, (void*)g_media_mem,file_size);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_memory_buffer", PlayerGetError(nRet));

	nRet = player_prepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_prepare() call", __LINE__, API_NAMESPACE);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}


//& purpose: set and get the audio latency mode
//& type : auto
/**
* @testcase				ITc_player_set_get_audio_latency_mode_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Set and get the audio latency mode
* @scenario				Create a handle for player\n
*						Set audio latency mode\n
*						get audio latency mode\n
*						check the result\n
*						destroy the handler
* @apicovered			player_set_audio_latency_mode, player_get_audio_latency_mode
* @passcase				When it can get audio latency mode
* @failcase				When it can not get audio latency mode
* @precondition			N/A
* @postcondition		N/A
*/
int ITc_player_set_get_audio_latency_mode_p(void)
{
	START_TEST;

	audio_latency_mode_e eLatencyMode;

	int nRet = player_set_audio_latency_mode(g_player, AUDIO_LATENCY_MODE_LOW);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_audio_latency_mode", PlayerGetError(nRet));

	usleep(2000);

	nRet = player_get_audio_latency_mode(g_player, &eLatencyMode);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_audio_latency_mode", PlayerGetError(nRet));

	if (eLatencyMode != AUDIO_LATENCY_MODE_LOW)
	{
		FPRINTF("[Line : %d][%s] player_set_get_audio_latency_mode mismatched, error returned = %s", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		return 1;
	}

	return 0;
}

//& purpose: set and get the player's volume
//& type : auto
/**
* @testcase				ITc_player_set_get_volume_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Set and get the player's volume
* @scenario				Initialize player handle\n
*						set volume\n
*						get volume\n
*						check the result\n
*						destroy the handler
* @apicovered			player_set_volume, player_get_volume
* @passcase				When it can get volume
* @failcase				When it can not get volume
* @precondition			N/A
* @postcondition		N/A
*/
int ITc_player_set_get_volume_p(void)
{
	START_TEST;

	float fSetLeft = 0.4;
	float fSetRight = 0.4;
	float fGetLeft = -1.0;
	float fGetRight = -1.0;

	if ( InitializePlayerHandler(true, 0) != true )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	int nRet = player_set_volume(g_player, fSetLeft, fSetRight);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_volume", PlayerGetError(nRet));
	FPRINTF("[Line : %d][%s] player_set_volume, left value = %f, right value = %f", __LINE__, API_NAMESPACE, fSetLeft, fSetRight);

	usleep(2000);

	nRet = player_get_volume(g_player, &fGetLeft, &fGetRight);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_volume", PlayerGetError(nRet));
	FPRINTF("[Line : %d][%s] player_get_volume, left value = %f, right value = %f", __LINE__, API_NAMESPACE, fGetLeft, fGetRight);

	if (fGetLeft != fSetLeft || fGetRight != fSetRight)
	{
		FPRINTF("[Line : %d][%s] player_set_get_volume mismatched, error returned = %s", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		return 1;
	}

	return 0;
}

//& purpose: Sets the player's looping status
//& type : auto
/**
* @testcase				ITc_player_set_looping_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Sets the player's looping status
* @scenario				Initialize player handle\n
*						prepare player\n
*						set player looping\n
*						check the result\n
*						destroy the handler
* @apicovered			player_set_looping, player_is_looping, player_unprepare
* @passcase				When it can set player looping
* @failcase				When it can not set player looping
* @precondition			The player state must be one of these: PLAYER_STATE_READY, PLAYER_STATE_PLAYING, or PLAYER_STATE_PAUSED
* @postcondition		N/A
*/
int ITc_player_set_looping_p(void)
{
	START_TEST;

	bool bIsLooping;
	player_state_e state;

	if ( InitializePlayerHandler(true, 0) != true )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	int nRet = player_start(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_start() call", __LINE__, API_NAMESPACE);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_set_looping(g_player, true);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_looping", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	nRet = player_is_looping(g_player, &bIsLooping);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_is_looping", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	if ( bIsLooping != true )
	{
		FPRINTF("[Line : %d][%s] player_is_looping false, error returned = %s", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_stop(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}

//& purpose: Sets the player's mute status
//& type : auto
/**
* @testcase				ITc_player_set_mute_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Sets the player's mute status
* @scenario				Initialize player handle\n
*						set player mute\n
*						check player mute\n
*						destroy the handler
* @apicovered			player_set_mute, player_is_muted, player_unprepare ,player_start, player_stop, player_get_state
* @passcase				When it can set player mute
* @failcase				When it can not set player mute
* @precondition			The player state must be one of these: PLAYER_STATE_READY, PLAYER_STATE_PLAYING, or PLAYER_STATE_PAUSED
* @postcondition		N/A
*/
int ITc_player_set_mute_p(void)
{
	START_TEST;

	bool bIsMuted = true;
	player_state_e state;

	if ( InitializePlayerHandler(true, 0) != true )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	int nRet = player_start(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_start() call", __LINE__, API_NAMESPACE);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_set_mute(g_player, true);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_mute", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	nRet = player_is_muted(g_player, &bIsMuted);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_is_muted", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	if ( bIsMuted != true )
	{
		FPRINTF("[Line : %d][%s] player_is_muted false, error returned = %s", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_stop(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}


//& purpose: pause playback
//& type : auto
/**
* @testcase				ITc_player_pause_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			pause playback
* @scenario				Initialize player handle\n
*						start player\n
*						pause player\n
*						check the result\n
*						stop the player\n
*						destroy the handler
* @apicovered			player_start, player_pause, player_stop, player_unprepare
* @passcase				When it can stop player
* @failcase				When it can not stop player
* @precondition			the player state should be PLAYER_STATE_PLAYING
* @postcondition		N/A
*/
int ITc_player_pause_p(void)
{
	START_TEST;

	player_state_e state;
	int nRet = -1;

	#ifndef TIZENIOT // For Mobile or Wearable
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_EVAS, g_pEvasObject);
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif //End MOBILE or WEARABLE

	sleep(2);

	if ( InitializePlayerHandler(true, 1) != true )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	nRet = player_start(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_start() call", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	sleep(4);

	nRet = player_pause(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_pause", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_PAUSED )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_pause() call", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_stop(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}

//& purpose: Sets the playback rate
//& type : auto
/**
* @testcase				ITc_player_set_playback_rate_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Sets the playback rate
* @scenario				Initialize player handle\n
*						start player\n
*						set playback rate\n
*						check the result\n
*						destroy the handler
* @apicovered			player_start, player_set_playback_rate, player_unprepare
* @passcase				When it can set playback rate
* @failcase				When it can not set playback rate
* @precondition			The player state must be PLAYER_STATE_PLAYING
* @postcondition		N/A
*/
int ITc_player_set_playback_rate_p(void)
{
	START_TEST;

	float fRate = 1.5;
	player_state_e state;

	if ( InitializePlayerHandler(true, 0) != true )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	int nRet = player_start(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_start() call", __LINE__, API_NAMESPACE);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_set_playback_rate(g_player, fRate);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_playback_rate", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	nRet = player_stop(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
	return 0;
}

//& purpose: Sets the cookie for streaming playback
//& type : auto
/**
* @testcase				ITc_player_set_streaming_cookie_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Sets the cookie for streaming playback
* @scenario				Initialize player handle\n
*						set streaming cookie\n
*						check the result\n
*						destroy the handler
* @apicovered			player_set_streaming_cookie
* @passcase				When it can Set the cookie for streaming playback
* @failcase				When it can not set the cookie for streaming playback
* @precondition			The player state must be PLAYER_STATE_IDLE
* @postcondition		N/A
*/
int ITc_player_set_streaming_cookie_p(void)
{
	START_TEST;

	const char* pszCookie = "Cookie";

	if ( InitializePlayerHandler(false, 0) == false )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	int nRet = player_set_streaming_cookie(g_player, pszCookie, (strlen(pszCookie) +1));
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_streaming_cookie", PlayerGetError(nRet));

	return 0;
}

//& purpose: Sets the streaming user agent for playback
//& type : auto
/**
* @testcase				ITc_player_set_streaming_user_agent_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Sets the streaming user agent for playback
* @scenario				Initialize player handle\n
*						set streaming user agent\n
*						check the result\n
*						destroy the handler
* @apicovered			player_set_streaming_user_agent
* @passcase				When it can set the streaming user agent for playback
* @failcase				When it can not set the streaming user agent for playback
* @precondition			The player state must be PLAYER_STATE_IDLE
* @postcondition		N/A
*/
int ITc_player_set_streaming_user_agent_p(void)
{
	START_TEST;

	const char* pszUserAgent = "UserAgent";

	if ( InitializePlayerHandler(false, 0) == false )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	int nRet = player_set_streaming_user_agent(g_player, pszUserAgent, (strlen(pszUserAgent) +1));
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_streaming_user_agent", PlayerGetError(nRet));

	return 0;
}

//& purpose: Registers a callback function to be invoked when the playback is finished
//& type : auto
/**
* @testcase				ITc_player_set_unset_completed_cb_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Registers a callback function to be invoked when the playback is finished
* @scenario				call player_set_completed_cb\n
*						check if callback is hit\n
*						destroy the handler
* @apicovered			player_set_completed_cb, player_unset_completed_cb, player_unprepare, player_set_display, player_get_state ,player_start, player_stop.
* @passcase				Callback is hit
* @failcase				Callback is not hit
* @precondition			NA
* @postcondition		player_completed_cb() will be invoked
*/
int ITc_player_set_unset_completed_cb_p(void)
{
	START_TEST;

	player_state_e state;
	g_bPlayerCompletedCallback = false;

	int nRet = player_set_completed_cb(g_player, PlayerCompletedCallback, NULL);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_completed_cb", PlayerGetError(nRet));

	#ifndef TIZENIOT // For Mobile or Wearable
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_EVAS, GET_DISPLAY(g_pEvasObject));
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif //End MOBILE or WEARABLE

	if ( InitializePlayerHandler(true, 1) == false )
	{
		FPRINTF("[Line : %d][%s] InitializePlayerHandler failed in precondition", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_start(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_start() call", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	PlayerWaitForAsync();

	if ( !g_bPlayerCompletedCallback )
	{
		FPRINTF("[Line : %d][%s] player_completed_cb failed, error returned = callback not invoked\n", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_unset_completed_cb(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_unset_completed_cb", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	nRet = player_stop(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
	return 0;
}

//& purpose: Registers a callback function to be invoked when every video frame is decoded
//& type : auto
/**
* @testcase				ITc_player_set_unset_media_packet_video_frame_decoded_cb_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Registers a callback function to be invoked when every video frame is decoded
* @scenario				all player_set_media_packet_video_frame_decoded_cb\n
*						heck if callback is hit\n
*						estroy the handler
* @apicovered			player_set_media_packet_video_frame_decoded_cb, player_unset_media_packet_video_frame_decoded_cb, player_unprepare, player_set_display, player_get_state ,player_start, player_stop
* @passcase				Callback is hit
* @failcase				Callback is not hit
* @precondition			The player state must be PLAYER_STATE_IDLE by player_create() or player_unprepare()
* @postcondition		player_media_packet_video_frame_decoded_cb() will be invoked
*/
int ITc_player_set_unset_media_packet_video_frame_decoded_cb_p(void)
{
	START_TEST;

	player_state_e state;
	g_bPlayerPreparedCallback = false;
	g_bPlayerMediaPacketVideoFrameDecodedCallback = false;
	g_bPlayerCallbackParameter = false;

	int nRet = player_set_media_packet_video_frame_decoded_cb(g_player, PlayerMediaPacketVideoFrameDecodedCallback, NULL);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_media_packet_video_frame_decoded_cb", PlayerGetError(nRet));

	#ifndef TIZENIOT // For Mobile or Wearable
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_NONE, GET_DISPLAY(g_pEvasObject));
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif

	if ( InitializePlayerHandler(true, 1) == false )
	{
		FPRINTF("[Line : %d][%s] InitializePlayerHandler failed in precondition", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_start(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_start() call", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	PlayerWaitForAsync();

	if (!g_bPlayerMediaPacketVideoFrameDecodedCallback)
	{
		FPRINTF("[Line : %d][%s] player_media_packet_video_frame_decoded_cb failed, callback not invoked\\n", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}
	else if (!g_bPlayerCallbackParameter)
	{
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	PlayerGetState(state);

	if ( state == PLAYER_STATE_READY )
	{
		nRet = player_unset_media_packet_video_frame_decoded_cb(g_player);
		PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));
	}

	nRet = player_stop(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
	return 0;
}


//& purpose: Prepares the media player for playback, asynchronously
//& type: auto
/**
* @testcase				ITc_player_prepare_async_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Prepares the media player for playback, asynchronously
* @scenario				initizlize player handler\n
*						call player_prepare_async\n
*						check results\n
*						destroy the handler
* @apicovered			player_prepare_async
* @passcase				When it can prepare player asynchronously
* @failcase				When it can not prepare player asynchronously
* @precondition			The player state should be PLAYER_STATE_IDLE
* @postcondition		N/A
*/
int ITc_player_prepare_async_p(void)
{
	START_TEST;

	if ( InitializePlayerHandler(false, 1) == false )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	int nRet = -1;

	#ifndef TIZENIOT // For Mobile or Wearable
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_EVAS, g_pEvasObject);
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif //End MOBILE or WEARABLE
	g_bPlayerPreparedCallback = false;

	nRet = player_prepare_async(g_player, PlayerPreparedCallback, NULL);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare_async", PlayerGetError(nRet));

	PlayerWaitForAsync();

	if (!g_bPlayerPreparedCallback)
	{
		FPRINTF("[Line : %d][%s] player_prepared_cb failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}


//& purpose: set and get the play position for playback
//& type : auto
/**
* @testcase				ITc_player_set_get_play_position_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @scenario				Initialize player handle
* @description			Set and get the play position for playback\n
*						set player position\n
*						get player position\n
*						check the result\n
*						destroy the handler
* @apicovered			player_set_play_position, player_get_play_position, player_unprepare
* @passcase				When it can set and get player position
* @failcase				When it can not set and get player position
* @precondition			The player state must be one of these: PLAYER_STATE_READY, PLAYER_STATE_PLAYING, or PLAYER_STATE_PAUSED
* @postcondition		N/A
*/
int ITc_player_set_get_play_position_p(void)
{
	START_TEST;

	int nSetMillisecond = 6000;
	int nGetMillisecond = -1;
	bool accurate = false;

	if ( InitializePlayerHandler(true, 1) == false )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	player_start(g_player);
	g_bPlayerSeekCompletedCallback = false;

	int nRet = player_set_play_position(g_player, nSetMillisecond, accurate, PlayerSeekCompletedCallback, NULL);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_play_position", PlayerGetError(nRet), player_unprepare(g_player));

	PlayerWaitForAsync();

	if (!g_bPlayerSeekCompletedCallback)
	{
		printf("[Line : %d][%s] player_seek_completed_cb failed, error returned = callback not invoked\n", __LINE__, API_NAMESPACE);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_get_play_position(g_player, &nGetMillisecond);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_play_position", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
	return 0;
}

//& purpose: Sets contents information for media stream
//& type : auto
/**
* @testcase				ITc_player_set_media_stream_info_p
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.4
* @description			Sets contents information for media stream
* @scenario				Create media format using media_format_create api\n
*						Set audio mime, channel, samplerate for the craeted media format\n
*						Sets contents information for media stream\n
*						destroy the media format
* @apicovered			media_format_create, media_format_set_audio_mime, media_format_set_audio_channel, media_format_set_audio_samplerate, player_set_media_stream_info, media_format_unref
* @passcase				player_set_media_stream_info and all precondition api is successful
* @failcase				player_set_media_stream_info or any precondition api failed
* @precondition			NA
* @postcondition		NA
*/
int ITc_player_set_media_stream_info_p(void)
{
	START_TEST;
	media_format_h hMediaFormat = NULL;

	//get media format
	int nRet = media_format_create(&hMediaFormat);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaFormatGetError(nRet));

	//set audio format
	nRet = media_format_set_audio_mime(hMediaFormat, MEDIA_FORMAT_AAC);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

	nRet = media_format_set_audio_channel(hMediaFormat, 2);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_channel", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

	nRet = media_format_set_audio_samplerate(hMediaFormat, 48000);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_samplerate", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

	//Target API
	nRet = player_set_media_stream_info(g_player, PLAYER_STREAM_TYPE_AUDIO, hMediaFormat);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_stream_info", PlayerGetError(nRet), media_format_unref(hMediaFormat));

	nRet = media_format_unref(hMediaFormat);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaFormatGetError(nRet));

	return 0;
}


//& purpose: Sets/Gets the max size bytes of buffer.
//& type : auto
/**
* @testcase				ITc_player_set_get_media_stream_buffer_max_size_p
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.4
* @description			Sets/Gets the max size bytes of buffer.
* @scenario				Check player state is idle or not\n
*						Sets the max size bytes of buffer\n
*						Gets the max size bytes of buffer\n
*						Compare set and get value
* @apicovered			player_set_media_stream_buffer_max_size, player_get_media_stream_buffer_max_size
* @passcase				player_set_media_stream_buffer_max_size and player_get_media_stream_buffer_max_size are successful
* @failcase				player_set_media_stream_buffer_max_size or player_get_media_stream_buffer_max_size is failed
* @precondition			The player state must be set to PLAYER_STATE_IDLE
* @postcondition		NA
*/
int ITc_player_set_get_media_stream_buffer_max_size_p(void)
{
	START_TEST;

	int nRet = -1;
	player_state_e state;
	unsigned long long nSetSize = 10;
	unsigned long long nGetSize;

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_IDLE )
	{
		FPRINTF("[Line : %d][%s] Player state is not idle", __LINE__, API_NAMESPACE);
		return 1;
	}

	//Target API
	nRet = player_set_media_stream_buffer_max_size(g_player, PLAYER_STREAM_TYPE_AUDIO, nSetSize);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_media_stream_buffer_max_size", PlayerGetError(nRet));

	nRet = player_get_media_stream_buffer_max_size(g_player, PLAYER_STREAM_TYPE_AUDIO, &nGetSize);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_media_stream_buffer_max_size", PlayerGetError(nRet));

	if ( nSetSize != nGetSize )
	{
		FPRINTF("[Line : %d][%s] Set and Get value not matched. Set value = %llu and Get value = %llu\\n", __LINE__, API_NAMESPACE, nSetSize, nGetSize);
		return 1;
	}
	return 0;
}

//& purpose: Sets/Gets the buffer threshold percent of buffer.
//& type : auto
/**
* @testcase				ITc_player_set_get_media_stream_buffer_min_threshold_p
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.4
* @description			Sets/Gets the buffer threshold percent of buffer.
* @scenario				Sets the buffer threshold percent of buffer\n
*						Gets the buffer threshold percent of buffer\n
*						Compare the set and get value
* @apicovered			player_get_state, player_set_media_stream_buffer_min_threshold, player_get_media_stream_buffer_min_threshold
* @passcase				player_set_media_stream_buffer_min_threshold and player_get_media_stream_buffer_min_threshold are successful
* @failcase				player_set_media_stream_buffer_min_threshold or player_get_media_stream_buffer_min_threshold is failed
* @precondition			player state must be set to PLAYER_STATE_IDLE
* @postcondition		NA
*/
int ITc_player_set_get_media_stream_buffer_min_threshold_p(void)
{
	START_TEST;

	unsigned int nSetSize = 10;
	unsigned int nGetSize;
	int nRet = -1;
	player_state_e state;

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_IDLE )
	{
		FPRINTF("[Line : %d][%s] Player state is not idle", __LINE__, API_NAMESPACE);
		return 1;
	}

	//Target API
	nRet = player_set_media_stream_buffer_min_threshold(g_player, PLAYER_STREAM_TYPE_AUDIO, nSetSize);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_media_stream_buffer_min_threshold", PlayerGetError(nRet));

	nRet = player_get_media_stream_buffer_min_threshold(g_player, PLAYER_STREAM_TYPE_AUDIO, &nGetSize);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_media_stream_buffer_min_threshold", PlayerGetError(nRet));

	if ( nSetSize != nGetSize )
	{
		FPRINTF("[Line : %d][%s] Set and Get value not matched. Set value = %d and Get value = %d\\n", __LINE__, API_NAMESPACE, nSetSize, nGetSize);
		return 1;
	}
	return 0;
}

//& purpose: Gets the track count.
//& type : auto
/**
* @testcase				ITc_player_get_track_count_p
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.4
* @description			Gets the track count.
* @scenario				Gets the track count
* @apicovered			player_get_track_count
* @passcase				player_get_track_count is successful
* @failcase				player_get_track_count is failed
* @precondition			The player state must be one of these: #PLAYER_STATE_READY, #PLAYER_STATE_PLAYING, or #PLAYER_STATE_PAUSED
* @postcondition		NA
*/
int ITc_player_get_track_count_p(void)
{
	START_TEST;

	player_state_e state;
	int nCount = 0;
	int nRet = -1;

	#ifndef TIZENIOT // For Mobile or Wearable
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_EVAS, g_pEvasObject);
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif	//End MOBILE or WEARABLE
	sleep(2);

	if ( InitializePlayerHandler(true, 1) != true )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	nRet = player_start(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_start() call", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	sleep(4);

	//Target API
	nRet = player_get_track_count(g_player, PLAYER_STREAM_TYPE_TEXT, &nCount);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_track_count", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	nRet = player_stop(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}

//& purpose: Gets current track index.
//& type : auto
/**
* @testcase				ITc_player_get_current_track_p
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.4
* @description			Gets current track index.
* @scenario				Gets the current track
* @apicovered			player_get_current_track
* @passcase				player_get_current_track is successful
* @failcase				player_get_current_track is failed
* @precondition			The player state must be one of these: #PLAYER_STATE_READY, #PLAYER_STATE_PLAYING, or #PLAYER_STATE_PAUSED
* @postcondition		NA
*/
int ITc_player_get_current_track_p(void)
{
	START_TEST;

	player_state_e state;
	int nCount = 0, nIndex = 0;
	int nRet = -1;

	#ifndef TIZENIOT // For Mobile or Wearable
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_EVAS, g_pEvasObject);
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif	//End MOBILE or WEARABLE
	sleep(2);

	if ( InitializePlayerHandler(true, 1) != true )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	nRet = player_start(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_start() call", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	sleep(4);

	nRet = player_get_track_count(g_player, PLAYER_STREAM_TYPE_AUDIO, &nCount);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_track_count", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	if ( nCount != 0 )
	{
		//Target API
		nRet = player_get_current_track(g_player, PLAYER_STREAM_TYPE_AUDIO, &nIndex);
		PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_current_track", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));
	}
	else
	{
		FPRINTF("[Line : %d][%s] No track available.\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_stop(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}


//& purpose: Gets language code of a track.
//& type : auto
/**
* @testcase				ITc_player_get_track_language_code_p
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.4
* @description			Gets language code of a track
* @scenario				Gets language code
* @apicovered			player_set_display, player_start, player_get_state, player_get_track_count, player_get_current_track, player_get_track_language_code, player_stop, player_unprepare
* @passcase				player_get_track_language_code is successful
* @failcase				player_get_track_language_code is failed
* @precondition			The player state must be one of these: #PLAYER_STATE_READY, #PLAYER_STATE_PLAYING, or #PLAYER_STATE_PAUSED
* @postcondition		NA
*/
int ITc_player_get_track_language_code_p(void)
{
	START_TEST;

	player_state_e state;
	int nCount = 0, nIndex = 0;
	char *pszLangCode = NULL;
	int nRet = -1;

	#ifndef TIZENIOT // For Mobile or Wearable
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_EVAS, g_pEvasObject);
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif	//End MOBILE or WEARABLE
	sleep(2);

	if ( InitializePlayerHandler(true, 1) != true )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	nRet = player_start(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_start() call", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	sleep(4);

	nRet = player_get_track_count(g_player, PLAYER_STREAM_TYPE_AUDIO, &nCount);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_track_count", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	if ( nCount != 0 )
	{
		nRet = player_get_current_track(g_player, PLAYER_STREAM_TYPE_AUDIO, &nIndex);
		PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_current_track", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

		//Target API
		nRet = player_get_track_language_code(g_player, PLAYER_STREAM_TYPE_AUDIO, nIndex, &pszLangCode);
		PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_track_language_code", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));
		FREE_MEMORY(pszLangCode);
	}
	else
	{
		FPRINTF("[Line : %d][%s] No track available.\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	player_stop(g_player);
	player_unprepare(g_player);
	return 0;
}


//& purpose: Selects a track to play.
//& type : auto
/**
* @testcase				ITc_player_select_track_p
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.4
* @description			Selects a track to play
* @scenario				Selects a track to play
* @apicovered			player_select_track
* @passcase				player_select_track is successful
* @failcase				player_select_track is failed
* @precondition			The player state must be one of these: #PLAYER_STATE_READY, #PLAYER_STATE_PLAYING, or #PLAYER_STATE_PAUSED
* @postcondition		NA
*/
int ITc_player_select_track_p(void)
{
	START_TEST;

	player_state_e state;
	int nCount = 0, nIndex = 0;
	int nRet = -1;

	#ifndef TIZENIOT // For Mobile or Wearable
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_EVAS, g_pEvasObject);
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif	//End MOBILE or WEARABLE
	sleep(2);

	if ( InitializePlayerHandler(true, 1) != true )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	nRet = player_start(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_start() call", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	sleep(4);

	nRet = player_get_track_count(g_player, PLAYER_STREAM_TYPE_AUDIO, &nCount);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_track_count", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	if ( nCount != 0 )
	{
		nRet = player_get_current_track(g_player, PLAYER_STREAM_TYPE_AUDIO, &nIndex);
		PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_current_track", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

		//Target API
		nRet = player_select_track(g_player, PLAYER_STREAM_TYPE_AUDIO, nIndex);
		PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_select_track", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));
	}
	else
	{
		FPRINTF("[Line : %d][%s] No track available.\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_stop(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}

//& purpose: Registers/Unregisters a callback function to be invoked when buffer underrun or overflow is occurred.
//& type : auto
/**
* @testcase				ITc_player_set_unset_media_stream_buffer_status_cb_p
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.4
* @description			Registers/Unregisters a callback function to be invoked when buffer underrun or overflow is occurred.
* @scenario				Registers the callback using player_set_media_stream_buffer_status_cb\n
*						Check if callback is hit\n
*						Unregisters the callback using player_unset_media_stream_buffer_status_cb
* @apicovered			player_set_uri, media_format_create, media_format_set_video_mime, media_format_set_video_width, media_format_set_video_height, player_set_media_stream_buffer_status_cb, player_unset_media_stream_buffer_status_cb, media_format_unref, player_stop, player_unprepare
* @passcase				Callback is hit
* @failcase				Callback is not hit
* @precondition			NA
* @postcondition		NA
*/
int ITc_player_set_unset_media_stream_buffer_status_cb_p(void)
{
	START_TEST;
	player_state_e state;
	char pPath[PATH_LEN] = {0};

	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_H264, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int nRet = player_set_uri(g_player, ES_FEEDING_PATH);

	#if defined(WEARABLE)
		bool bValue = false;
		system_info_get_platform_bool(INTERNET_FEATURE, &bValue);
		if(bValue == false)
		{
			if(nRet != PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE)
			{
				FPRINTF("[Line : %d][%s] player_set_uri API call returned mismatch %s error for unsupported internet feature\\n", __LINE__, API_NAMESPACE,	PlayerGetError(nRet));
				return 1;
			}
		}
	#endif
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	nRet = media_format_create(&g_hMediaFormat);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaFormatGetError(nRet));

	if(g_hMediaFormat == NULL)
	{
		FPRINTF("[Line : %d][%s] media_format_create failed.  g_hMediaFormat is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}


	nRet = media_format_set_video_mime(g_hMediaFormat, MEDIA_FORMAT_H264_SP);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet), media_format_unref(g_hMediaFormat));

	nRet = media_format_set_video_width(g_hMediaFormat, 640);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_width", MediaFormatGetError(nRet), media_format_unref(g_hMediaFormat));

	nRet = media_format_set_video_height(g_hMediaFormat, 480);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_height", MediaFormatGetError(nRet), media_format_unref(g_hMediaFormat));

	nRet = player_get_state (g_player, &state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), media_format_unref(g_hMediaFormat));

	if (state != PLAYER_STATE_IDLE)
	{
		player_unprepare(g_player);
	}

	g_bPlayerMediaStreamBufferStatus = false;
	//Target API
	nRet = player_set_media_stream_buffer_status_cb(g_player, PLAYER_STREAM_TYPE_VIDEO, PlayerMediaStreamBufferStatusCallback, NULL);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_stream_buffer_status_cb", PlayerGetError(nRet), media_format_unref(g_hMediaFormat));

	//Target API
	nRet = player_unset_media_stream_buffer_status_cb(g_player, PLAYER_STREAM_TYPE_VIDEO);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_unset_media_stream_buffer_status_cb", PlayerGetError(nRet), media_format_unref(g_hMediaFormat));

	media_format_unref(g_hMediaFormat);
	player_stop(g_player);
	player_unprepare(g_player);

	return 0;
}

//& purpose: Registers a callback function to be invoked when the playback is interrupted or the interrupt is completed.
//& type: auto
/**
* @testcase					ITc_player_in_set_unset_interrupted_cb_p
* @since_tizen				2.3
* @author					SRID(pushpa.singh)
* @reviewer					SRID(gupta.sanjay)
* @type						auto
* @description				Registers a callback function to be invoked when the audio input handle is interrupted or the interrupt is completed.
* @scenario					Registers a callback function \n
							UnRegisters a callback function
* @apicovered				player_set_interrupted_cb, player_unset_interrupted_cb
* @passcase					When player_set_interrupted_cb	is successful.
* @failcase					If target api player_set_interrupted_cb fails or any precondition api fails.
* @precondition				Audio handle must be created
* @postcondition			Audio handle must be released
*
*/
int ITc_player_in_set_unset_interrupted_cb_p(void)
{
	START_TEST;

	int nRet = player_set_interrupted_cb(g_player, PlayerInterruptCb, NULL);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_interrupted_cb", PlayerGetError(nRet));

	nRet = player_unset_interrupted_cb(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unset_interrupted_cb", PlayerGetError(nRet));

	return 0;
}

//& purpose: to check and set the replaygain status
//& type : auto
/**
* @testcase			ITc_player_set_get_replayagain_status_p
* @author			SRID(manoj.g2)
* @reviewer			SRID(a.pandia)
* @type				auto
* @since_tizen			5.0
* @description			to check and set the replayagain status
* @scenario			call player_set_replaygain_enabled\n
*					call player_is_replaygain_enabled\n
*						check status is what we set\n
* @apicovered			player_set_replaygain_enabled,player_set_replaygain_enabled.
* @passcase			on SUCCESS return to else negative value
* @failcase			on SUCCESS return to else negative value
* @precondition			player state must be one of the PLAYER_STATE_IDLE,PLAYER_STATE_START,PLAYER_STATE_READY,PLAYER_STATE_PLAYING,PLAYER_STATE_PAUSED
* @postcondition		NA
*/
int ITc_player_set_get_replaygain_status_p(void)
{
	START_TEST;

	int nRet = -1;
	bool bStatus = true;

	nRet = player_set_replaygain_enabled(g_player,bStatus);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_replaygain_enabled", PlayerGetError(nRet));

	bStatus = false;

	nRet = player_is_replaygain_enabled(g_player,&bStatus);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_is_replaygain_enabled", PlayerGetError(nRet));

	if(!bStatus)
	{
		FPRINTF("[Line : %d][%s] player_is_replaygain_enabled is failed as status value is mismatched = %s", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		return 1;
	}

	return 0;
}

#if (defined(_MEDIA_STREAM_API ))
//& purpose: Pushes elementary stream to decode audio or video
//& type : auto
/**
* @testcase				ITc_player_push_media_stream_p
* @author				SRID(pushpa.singh)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.4
* @description			Pushes elementary stream to decode audio or video
* @scenario				Create media format\n
*						Sets audio information for decoding audio elementary stream
*						Push elementary stream to decode audio or video
* @apicovered			media_format_create, media_format_set_audio_mime, media_format_set_audio_channel, media_format_set_audio_samplerate \n
*						player_push_media_stream, media_format_unref
* @passcase				When it can create media format and push audio stream for decoding
* @failcase				When it can not create media format or can not push audio stream for decoding
* @precondition			The player state must be PLAYER_STATE_READY or PLAYER_STATE_PLAYING or PLAYER_STATE_PAUSED.
* @postcondition		N/A
*/
int ITc_player_push_media_stream_p(void)
{
	START_TEST;s
	media_format_h hMediaFormat = NULL;
	media_packet_h hMediaPacket = NULL;

	guint8 *buff_ptr = NULL;
	void *src = NULL;
	guint64 pts = 0L;
	uint64_t nSize = 1024;

	//get media format
	int nRet = media_format_create(&hMediaFormat);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaFormatGetError(nRet));

	//set audio format
	nRet = media_format_set_audio_mime(hMediaFormat, MEDIA_FORMAT_AAC);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

	nRet = media_format_set_audio_channel(hMediaFormat, 2);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_channel", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

	nRet = media_format_set_audio_samplerate(hMediaFormat, 48000);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_samplerate", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

	nRet = media_packet_create_alloc(hMediaFormat, NULL, NULL, &hMediaPacket);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_create_alloc", MediaPacketGetError(nRet), media_format_unref(hMediaFormat));

	nRet = media_packet_get_buffer_data_ptr(hMediaPacket, &src);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_create_alloc", MediaPacketGetError(nRet), media_format_unref(hMediaFormat));

	nRet = media_packet_set_pts(hMediaPacket, (uint64_t)(pts/1000000));
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_create_alloc", MediaPacketGetError(nRet), media_format_unref(hMediaFormat));

	nRet = media_packet_set_buffer_size(hMediaPacket, nSize);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_create_alloc", MediaPacketGetError(nRet), media_format_unref(hMediaFormat));

	buff_ptr = (guint8 *) g_malloc0(nSize);
	memcpy(src, buff_ptr, nSize);

	//Target API
	nRet = player_push_media_stream(g_player, hMediaPacket);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_stream_video_info", PlayerGetError(nRet), g_free(buff_ptr);media_format_unref(hMediaFormat));

	if ( buff_ptr )
	{
		g_free(buff_ptr);
		buff_ptr = NULL;
	}

	nRet = media_format_unref(hMediaFormat);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaFormatGetError(nRet));

	return 0;
}
#endif

#if defined(MOBILE) || defined(WEARABLE) || defined(TIZENIOT) //Starts MOBILE or WEARABLE
//& purpose: Pushes elementary stream to decode audio or video
//& type : auto
/**
* @testcase				ITc_player_push_media_stream_p
* @author				SRID(pushpa.singh)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.4
* @description			Pushes elementary stream to decode audio or video
* @scenario				Create media format\n
*						Sets video information for decoding video elementary stream
*						Push elementary stream to decode audio or video
* @apicovered			media_format_create, media_format_set_video_mime, media_format_set_video_width, media_format_set_video_height, player_set_uri,player_get_state,player_set_media_stream_buffer_status_cb, player_set_display, player_prepare_async
*						media_packet_create_alloc, media_packet_get_buffer_data_ptr, media_packet_set_pts, player_push_media_stream, media_format_unref,player_set_media_stream_buffer_max_size, player_set_media_stream_seek_cb, player_set_media_stream_info
* @passcase				When it can create media format and push audio stream for decoding
* @failcase				When it can not create media format or can not push audio stream for decoding
* @precondition			The player state must be PLAYER_STATE_READY or PLAYER_STATE_PLAYING or PLAYER_STATE_PAUSED.
* @postcondition		N/A
*/
int ITc_player_push_media_stream_p(void)
{
	START_TEST;
	player_state_e state;
	pthread_t feeding_thread_id = 0;

	char pPath[PATH_LEN] = {0};
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_H264, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	file_src = fopen(pPath, "r");
	if (!file_src)
	{
		FPRINTF("[Line : %d][%s] Fail to open file\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = player_set_uri(g_player, ES_FEEDING_PATH);
	#if defined(WEARABLE)
		bool bValue = false;
		system_info_get_platform_bool(INTERNET_FEATURE, &bValue);
		if(bValue == false)
		{
			if(nRet != PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE)
			{
				FPRINTF("[Line : %d][%s] player_set_uri API call returned mismatch %s error for unsupported internet feature\\n", __LINE__, API_NAMESPACE,	PlayerGetError(nRet));
				fclose(file_src);
				return 1;
			}
		}
	#endif
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet), fclose(file_src));

	nRet = media_format_create(&g_hMediaFormat);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaFormatGetError(nRet), fclose(file_src));

	nRet = media_format_set_video_mime(g_hMediaFormat, MEDIA_FORMAT_H264_SP);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet), media_format_unref(g_hMediaFormat); fclose(file_src));

	nRet = media_format_set_video_width(g_hMediaFormat, 640);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_width", MediaFormatGetError(nRet), media_format_unref(g_hMediaFormat); fclose(file_src));

	nRet = media_format_set_video_height(g_hMediaFormat, 480);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_height", MediaFormatGetError(nRet), media_format_unref(g_hMediaFormat); fclose(file_src));


	nRet = player_get_state (g_player, &state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), media_format_unref(g_hMediaFormat); fclose(file_src));
	if (state != PLAYER_STATE_IDLE)
	{
		player_unprepare(g_player);
	}

	g_bPlayerMediaStreamBufferStatus = false;
	nRet = player_set_media_stream_buffer_status_cb(g_player, PLAYER_STREAM_TYPE_VIDEO, PlayerMediaStreamBufferStatusCallback, NULL);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_stream_buffer_status_cb", PlayerGetError(nRet), media_format_unref(g_hMediaFormat); fclose(file_src));

	nRet = player_set_media_stream_buffer_max_size(g_player, PLAYER_STREAM_TYPE_VIDEO, 3*1024*1024);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_stream_buffer_max_size", PlayerGetError(nRet), media_format_unref(g_hMediaFormat); fclose(file_src));

	nRet = player_set_media_stream_seek_cb(g_player, PLAYER_STREAM_TYPE_VIDEO, PlayerMediaStreamSeekCallBack, NULL);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_stream_seek_cb", PlayerGetError(nRet), media_format_unref(g_hMediaFormat); fclose(file_src));

	#ifndef TIZENIOT // For Mobile or Wearable
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_OVERLAY, g_pEvasWindow);
		PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet), media_format_unref(g_hMediaFormat); fclose(file_src));
	#endif

	nRet = player_set_media_stream_info(g_player, PLAYER_STREAM_TYPE_VIDEO, g_hMediaFormat);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_stream_info", PlayerGetError(nRet), media_format_unref(g_hMediaFormat); fclose(file_src));

	nRet = player_prepare_async(g_player, PlayerPreparedCB, (void*)g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_prepare_async", PlayerGetError(nRet), media_format_unref(g_hMediaFormat); fclose(file_src));

	g_nRet = -1;
	if ( pthread_create(&feeding_thread_id, NULL, (void*)FeedVideoDataThreadFunc, NULL) < 0 )
	{
		FPRINTF("[Line : %d][%s] pthread_create failed\\n", __LINE__, API_NAMESPACE);
		media_format_unref(g_hMediaFormat);
		player_stop(g_player);
		player_unprepare(g_player);
		fclose(file_src);
		return 1;
	}

	usleep(1000);
	pthread_join(feeding_thread_id, NULL);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, g_nRet, "player_push_media_stream", PlayerGetError(g_nRet), player_stop(g_player); player_unprepare(g_player); media_format_unref(g_hMediaFormat); fclose(file_src));
	usleep(1000);

	player_stop(g_player);
	player_unprepare(g_player);
	media_format_unref(g_hMediaFormat);
	fclose(file_src);
	feeding_thread_id = 0;
	return 0;
}
#endif //Ends MOBILE or WEARABLE

//& purpose: Registers/Unregisters a callback function to be invoked when seeking is occurred.
//& type : auto
/**
* @testcase				ITc_player_set_unset_media_stream_seek_cb_p
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.4
* @description			Registers/Unregisters a callback function to be invoked when seeking is occurred.
* @scenario				Registers the callback using player_set_media_stream_seek_cb\n
*						Check if callback is hit\n
*						Unregisters the callback using player_unset_media_stream_seek_cb
* @apicovered			player_set_display, player_set_media_stream_seek_cb, player_unset_media_stream_seek_cb, media_format_create, media_format_set_video_mime, media_format_set_video_width, media_format_set_video_height, player_get_state, player_set_media_stream_buffer_status_cb
						player_set_media_stream_buffer_max_size, player_set_media_stream_seek_cb, player_set_media_stream_info, player_prepare_async, player_stop, player_start, player_set_uri
* @passcase				if all covered apis are passed and Callback is hit
* @failcase				if any covered api is failed or Callback is not hit
* @precondition			NA
* @postcondition		NA
*/
int ITc_player_set_unset_media_stream_seek_cb_p(void)
{
	START_TEST;
	player_state_e state;
	char pPath[PATH_LEN] = {0};

	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_H264, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int nRet = player_set_uri(g_player, ES_FEEDING_PATH);

	#if defined(WEARABLE)
		bool bValue = false;
		system_info_get_platform_bool(INTERNET_FEATURE, &bValue);
		if(bValue == false)
		{
			if(nRet != PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE)
			{
				FPRINTF("[Line : %d][%s] player_set_uri API call returned mismatch %s error for unsupported internet feature\\n", __LINE__, API_NAMESPACE,	PlayerGetError(nRet));
				return 1;
			}
		}
	#endif
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	nRet = media_format_create(&g_hMediaFormat);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaFormatGetError(nRet));

	nRet = media_format_set_video_mime(g_hMediaFormat, MEDIA_FORMAT_H264_SP);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet), media_format_unref(g_hMediaFormat));

	nRet = media_format_set_video_width(g_hMediaFormat, 640);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_width", MediaFormatGetError(nRet), media_format_unref(g_hMediaFormat));

	nRet = media_format_set_video_height(g_hMediaFormat, 480);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_height", MediaFormatGetError(nRet), media_format_unref(g_hMediaFormat));

	nRet = player_get_state (g_player, &state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), media_format_unref(g_hMediaFormat));

	if (state != PLAYER_STATE_IDLE)
	{
		player_unprepare(g_player);
	}

	g_bPlayerMediaStreamSeek = false;
	nRet = player_set_media_stream_buffer_status_cb(g_player, PLAYER_STREAM_TYPE_VIDEO, PlayerMediaStreamBufferStatusCallback, NULL);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_stream_buffer_status_cb", PlayerGetError(nRet), media_format_unref(g_hMediaFormat));

	nRet = player_set_media_stream_buffer_max_size(g_player, PLAYER_STREAM_TYPE_VIDEO, 10000);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_stream_buffer_max_size", PlayerGetError(nRet), media_format_unref(g_hMediaFormat));

	nRet = player_set_media_stream_seek_cb(g_player, PLAYER_STREAM_TYPE_VIDEO, PlayerMediaStreamSeekCallBack, NULL);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_stream_seek_cb", PlayerGetError(nRet), media_format_unref(g_hMediaFormat));

	#ifndef TIZENIOT // For Mobile or Wearable
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_OVERLAY, g_pEvasWindow);
		PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet), media_format_unref(g_hMediaFormat));
	#endif

	nRet = player_set_media_stream_info(g_player, PLAYER_STREAM_TYPE_VIDEO, g_hMediaFormat);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_stream_info", PlayerGetError(nRet), media_format_unref(g_hMediaFormat));

	nRet = player_prepare_async(g_player, PlayerPreparedCB, (void*)g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_prepare_async", PlayerGetError(nRet), media_format_unref(g_hMediaFormat));

	PlayerWaitForAsync();

	if ( g_bPlayerMediaStreamSeek == false )
	{
		FPRINTF("[Line : %d][%s] player_set_media_stream_seek_cb failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		media_format_unref(g_hMediaFormat);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_unset_media_stream_seek_cb(g_player, PLAYER_STREAM_TYPE_VIDEO);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_unset_media_stream_seek_cb", PlayerGetError(nRet), media_format_unref(g_hMediaFormat); player_stop(g_player);player_unprepare(g_player));

	media_format_unref(g_hMediaFormat);
	player_stop(g_player);
	player_unprepare(g_player);
	return 0;
}

//& purpose: set and get the play position for playback
//& type : auto
/**
* @testcase				ITc_player_set_get_play_position_nsec_p
* @author				SRID(manoj.g2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @since_tizen			5.0
* @scenario				Initialize player handle
* @description			Set and get the play position for playback\n
*						set player position\n
*						get player position\n
*						check the result\n
*						destroy the handler
* @apicovered			player_set_play_position_nsec, player_get_play_position_nsec, player_unprepare
* @passcase				When it can set and get player position
* @failcase				When it can not set and get player position
* @precondition			The player state must be one of these: PLAYER_STATE_READY, PLAYER_STATE_PLAYING, or PLAYER_STATE_PAUSED
* @postcondition		N/A
*/
int ITc_player_set_get_play_position_nsec_p(void)
{
	START_TEST;

	int64_t nSetNanosecond = 1000*1000*1000;
	int64_t nGetNanosecond = 0;
	bool accurate = true;

	if ( InitializePlayerHandler(true, 1) == false )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	int nRet = player_start(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet), player_unprepare(g_player));
	g_bPlayerSeekCompletedCallback = false;

	nRet = player_set_play_position_nsec(g_player, nSetNanosecond, accurate, PlayerSeekCompletedCallback, NULL);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_play_position_nsec", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	PlayerWaitForAsync();

	if (!g_bPlayerSeekCompletedCallback)
	{
		FPRINTF("[Line : %d][%s] player_seek_completed_cb failed, error returned = callback not invoked\n", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_get_play_position_nsec(g_player, &nGetNanosecond);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_play_position_nsec", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	CHECK_VALUE_INT(nGetNanosecond, "player_get_play_position_nsec");

	nRet = player_stop(g_player);
	PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet));

	nRet = player_unprepare(g_player);
	PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
	return 0;
}


//& purpose: Gets the total running time of the associated media
//& type : auto
/**
* @testcase				ITc_player_get_duration_nsec_p
* @author				SRID(manoj.g2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @since_tizen			5.0
* @description			Gets the total running time of the associated media
* @scenario				Initialize player handle\n
*						start player\n
*						get player duration\n
*						check the result\n
*						destroy the handler
* @apicovered			player_start, player_get_state, player_get_duration_nsec, player_start, player_unprepare
* @passcase				When it can get player duration
* @failcase				When it can not get player duration
* @precondition			The player state must be PLAYER_STATE_PLAYING
* @postcondition		N/A
*/
int ITc_player_get_duration_nsec_p(void)
{
	START_TEST;

	int64_t nDuration = 0;
	player_state_e state;

	if ( InitializePlayerHandler(true, 1) != true )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	int nRet = player_start(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_start() call", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_get_duration_nsec(g_player, &nDuration);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_duration_nsec", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	CHECK_VALUE_INT(nDuration, "player_get_duration_nsec");

	nRet = player_stop(g_player);
	PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet));

	nRet = player_unprepare(g_player);
	PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}
//& purpose: To enable the audio pitch control fucntion
//& type : auto
/**
* @testcase				ITc_player_audio_pitch_set_get_enabled_p
* @author				SRID(shilpa.j)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @since_tizen			5.5
* @description			Check the state of audio pitch and sets audio pitch
* @scenario				Initialize player handle\n
*						start player\n
*						get player audio pitch\n
*						check the result\n
*						destroy the handler
* @apicovered			player_start, player_get_state, player_audio_pitch_is_enabled,player_audio_pitch_set_enabled player_start, player_unprepare
* @passcase				When it can set player audio pitch
* @failcase				When it can not set player audio pitch
* @precondition			The player state must be PLAYER_STATE_IDLE
* @postcondition		N/A
*/
int ITc_player_audio_pitch_set_get_enabled_p(void)
{
	START_TEST;

	bool bIsEnable= false;
	bool bPitchEnableState;
	player_state_e state;

	int nRet = player_get_state(g_player,&state);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet));

	PlayerGetState(state);
	if(state != PLAYER_STATE_IDLE)
	{
		FPRINTF("[Line : %d][%s] Player state is not idle", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_audio_pitch_is_enabled(g_player, &bIsEnable);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_pitch_is_enabled", PlayerGetError(nRet));

	if(bIsEnable)
	{
		bPitchEnableState = false;
	}
	else
	{
		bPitchEnableState = true;
	}

	nRet = player_audio_pitch_set_enabled(g_player, bPitchEnableState);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_pitch_set_enabled", PlayerGetError(nRet));

	nRet = player_audio_pitch_is_enabled(g_player, &bIsEnable);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_pitch_is_enabled", PlayerGetError(nRet));

	if(bIsEnable != bPitchEnableState)
	{
		FPRINTF("[Line : %d][%s] Mismatch of Player audio pitch  ", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: To get and set the audio pitch value
//& type : auto
/**
* @testcase				ITc_player_audio_pitch_set_get_value_p
* @author				SRID(shilpa.j)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @since_tizen			5.5
* @description			Gets and sets the audio pitch value
* @scenario				Initialize player handle\n
*						start player\n
						set player audio pitch value\n
*						get player audio pitch value\n
*						check the result\n
*						destroy the handler
* @apicovered			player_start, player_get_state, player_audio_pitch_is_enabled,player_audio_pitch_set_value,player_audio_pitch_get_value, player_start, player_unprepare
* @passcase				When it can get and set  audio pitch value
* @failcase				When it can not get and set  audio pitch value
* @precondition			The player state must be PLAYER_STATE_IDLE
* @postcondition		N/A
*/
int ITc_player_audio_pitch_set_get_value_p(void)
{
	START_TEST;

	float fPitchVal = 0.9f;
	float fPitchGetVal;
	bool bPitchEnableState = true;
	player_state_e state;

	int nRet = player_get_state(g_player,&state);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet));

	PlayerGetState(state);
	if(state != PLAYER_STATE_IDLE)
	{
		FPRINTF("[Line : %d][%s] Player state is not idle", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_audio_pitch_set_enabled(g_player, bPitchEnableState);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_pitch_set_enabled", PlayerGetError(nRet));

	nRet = player_audio_pitch_set_value(g_player, fPitchVal);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_pitch_set_value", PlayerGetError(nRet));

	nRet = player_audio_pitch_get_value(g_player, &fPitchGetVal);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_pitch_get_value", PlayerGetError(nRet));

	if(fPitchVal != fPitchGetVal)
	{
		FPRINTF("[Line : %d][%s] Mismatch of Player audio pitch value ", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Sets and unsets a media packet audio decoded callback function.
//& type : auto
/**
* @testcase			ITc_player_set_unset_media_packet_audio_frame_decoded_cb_signed_le_deinterleave_p
* @author			SRID(karanam.s)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @since_tizen			5.5
* @description			Sets and unsets a media packet audio decoded callback function.
* @scenario			Sets and unsets a media packet audio decoded callback function.
* @apicovered			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb
* @passcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb and all precondition apis are 					successful
* @failcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb or any precondition api fails
* @precondition			media_format_create
* @postcondition		NA
*/
int ITc_player_set_unset_media_packet_audio_frame_decoded_cb_signed_le_deinterleave_p(void)
{
	START_TEST;
	media_format_h hMediaFormat = NULL;
	player_state_e state;

	player_audio_extract_option_e EXTRACT_OPTION_ARR[]=
	{
		PLAYER_AUDIO_EXTRACT_DEINTERLEAVE,
	};

	media_format_mimetype_e FORMAT_MIMETYPE_ARR[]=
	{
		MEDIA_FORMAT_PCM_S16LE,
		MEDIA_FORMAT_PCM_S24LE,
		MEDIA_FORMAT_PCM_S32LE,
	};

	int nSize = sizeof(EXTRACT_OPTION_ARR)/sizeof(EXTRACT_OPTION_ARR[0]);
	int nSize2 = sizeof(FORMAT_MIMETYPE_ARR)/sizeof(FORMAT_MIMETYPE_ARR[0]);
        int nCounter = 0, nInnerCounter = 0;
	int nRet = -1;
	int nRepeat = 0;

	char pPath[PATH_LEN] = {0,};
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_VIDEO2, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	#if defined(MOBILE) || defined (WEARABLE)	//Starts MOBILE or WEARABLE
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_NONE, GET_DISPLAY(g_pEvasObject));
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif //End MOBILE or WEARABLE

	nRet = player_set_uri(g_player, pPath);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	for(nInnerCounter = 0; nInnerCounter < nSize2; nInnerCounter++)
	{
		g_eMediaFormatMimetype = FORMAT_MIMETYPE_ARR[nInnerCounter];

		for( nCounter = 0; nCounter < nSize; nCounter++)
		{
			g_bPlayerAudioDecodedCallback = false;

			//get media format
			nRet = media_format_create(&hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaFormatGetError(nRet));
			CHECK_HANDLE(hMediaFormat, "media_format_create");

			//set audio format
			nRet = media_format_set_audio_mime(hMediaFormat, g_eMediaFormatMimetype);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_channel(hMediaFormat, EXPORT_PCM_STEREO);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_channel", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_samplerate(hMediaFormat, EXPORT_PCM_SAMPLERATE);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_samplerate", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			g_ePlayerAudioExtractOption = EXTRACT_OPTION_ARR[nCounter];
			nRet = player_set_media_packet_audio_frame_decoded_cb(g_player, hMediaFormat, g_ePlayerAudioExtractOption, PlayerAudioDecodedCb, NULL);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_unref(hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaFormatGetError(nRet));

			nRet = player_prepare(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

			nRet = player_start(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet));

			for(nRepeat = 0; nRepeat < LIMIT; nRepeat++) {
				PlayerWaitForAsync2(TIMEOUT2);
				if(g_bPlayerAudioDecodedCallback)
					break;
			}

			if (!g_bPlayerAudioDecodedCallback)
			{
				FPRINTF("[Line : %d][%s] player_audio_decoded_cb failed, error returned = callback not invoked\n", __LINE__, API_NAMESPACE);
				media_format_unref(hMediaFormat);
				player_stop(g_player);
				player_unprepare(g_player);
				return 1;
			}

			nRet = player_get_state(g_player, &state);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

			PlayerGetState(state);

			if ( state == PLAYER_STATE_READY || state == PLAYER_STATE_IDLE )
			{
				nRet = player_unset_media_packet_audio_frame_decoded_cb(g_player);
				PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_unset_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));
			}

			nRet = player_stop(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet));

			nRet = player_unprepare(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
		}

	}

	return 0;
}

//& purpose: Sets and unsets a media packet audio decoded callback function.
//& type : auto
/**
* @testcase			ITc_player_set_unset_media_packet_audio_frame_decoded_cb_signed_le_no_sync_and_deinterleave_p
* @author			SRID(karanam.s)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @since_tizen			5.5
* @description			Sets and unsets a media packet audio decoded callback function.
* @scenario			Sets and unsets a media packet audio decoded callback function.
* @apicovered			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb
* @passcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb and all precondition apis are 					successful
* @failcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb or any precondition api fails
* @precondition			media_format_create
* @postcondition		NA
*/
int ITc_player_set_unset_media_packet_audio_frame_decoded_cb_signed_le_no_sync_and_deinterleave_p(void)
{
	START_TEST;
	media_format_h hMediaFormat = NULL;
	player_state_e state;

	player_audio_extract_option_e EXTRACT_OPTION_ARR[]=
	{
		PLAYER_AUDIO_EXTRACT_NO_SYNC_AND_DEINTERLEAVE
	};

	media_format_mimetype_e FORMAT_MIMETYPE_ARR[]=
	{
		MEDIA_FORMAT_PCM_S16LE,
		MEDIA_FORMAT_PCM_S24LE,
		MEDIA_FORMAT_PCM_S32LE,
	};

	int nSize = sizeof(EXTRACT_OPTION_ARR)/sizeof(EXTRACT_OPTION_ARR[0]);
	int nSize2 = sizeof(FORMAT_MIMETYPE_ARR)/sizeof(FORMAT_MIMETYPE_ARR[0]);
        int nCounter = 0, nInnerCounter = 0;
	int nRet = -1;
	int nRepeat = 0;

	char pPath[PATH_LEN] = {0,};
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_VIDEO2, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	#if defined(MOBILE) || defined (WEARABLE)	//Starts MOBILE or WEARABLE
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_NONE, GET_DISPLAY(g_pEvasObject));
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif //End MOBILE or WEARABLE

	nRet = player_set_uri(g_player, pPath);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	for(nInnerCounter = 0; nInnerCounter < nSize2; nInnerCounter++)
	{
		g_eMediaFormatMimetype = FORMAT_MIMETYPE_ARR[nInnerCounter];

		for( nCounter = 0; nCounter < nSize; nCounter++)
		{
			g_bPlayerAudioDecodedCallback = false;

			//get media format
			nRet = media_format_create(&hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaFormatGetError(nRet));
			CHECK_HANDLE(hMediaFormat, "media_format_create");

			//set audio format
			nRet = media_format_set_audio_mime(hMediaFormat, g_eMediaFormatMimetype);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_channel(hMediaFormat, EXPORT_PCM_STEREO);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_channel", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_samplerate(hMediaFormat, EXPORT_PCM_SAMPLERATE);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_samplerate", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			g_ePlayerAudioExtractOption = EXTRACT_OPTION_ARR[nCounter];
			nRet = player_set_media_packet_audio_frame_decoded_cb(g_player, hMediaFormat, g_ePlayerAudioExtractOption, PlayerAudioDecodedCb, NULL);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_unref(hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaFormatGetError(nRet));

			nRet = player_prepare(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

			nRet = player_start(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet));

			for(nRepeat = 0; nRepeat < LIMIT; nRepeat++) {
				PlayerWaitForAsync2(TIMEOUT2);
				if(g_bPlayerAudioDecodedCallback)
					break;
			}

			if (!g_bPlayerAudioDecodedCallback)
			{
				FPRINTF("[Line : %d][%s] player_audio_decoded_cb failed, error returned = callback not invoked\n", __LINE__, API_NAMESPACE);
				media_format_unref(hMediaFormat);
				player_stop(g_player);
				player_unprepare(g_player);
				return 1;
			}

			nRet = player_get_state(g_player, &state);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

			PlayerGetState(state);

			if ( state == PLAYER_STATE_READY || state == PLAYER_STATE_IDLE )
			{
				nRet = player_unset_media_packet_audio_frame_decoded_cb(g_player);
				PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_unset_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));
			}

			nRet = player_stop(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet));

			nRet = player_unprepare(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
		}

	}

	return 0;
}

//& purpose: Sets and unsets a media packet audio decoded callback function.
//& type : auto
/**
* @testcase			ITc_player_set_unset_media_packet_audio_frame_decoded_cb_signed_be_deinterleave_p
* @author			SRID(karanam.s)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @since_tizen			5.5
* @description			Sets and unsets a media packet audio decoded callback function.
* @scenario			Sets and unsets a media packet audio decoded callback function.
* @apicovered			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb
* @passcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb and all precondition apis are 					successful
* @failcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb or any precondition api fails
* @precondition			media_format_create
* @postcondition		NA
*/
int ITc_player_set_unset_media_packet_audio_frame_decoded_cb_signed_be_deinterleave_p(void)
{
	START_TEST;
	media_format_h hMediaFormat = NULL;
	player_state_e state;

	player_audio_extract_option_e EXTRACT_OPTION_ARR[]=
	{
		PLAYER_AUDIO_EXTRACT_DEINTERLEAVE
	};

	media_format_mimetype_e FORMAT_MIMETYPE_ARR[]=
	{
		MEDIA_FORMAT_PCM_S16BE,
		MEDIA_FORMAT_PCM_S24BE,
		MEDIA_FORMAT_PCM_S32BE,
	};

	int nSize = sizeof(EXTRACT_OPTION_ARR)/sizeof(EXTRACT_OPTION_ARR[0]);
	int nSize2 = sizeof(FORMAT_MIMETYPE_ARR)/sizeof(FORMAT_MIMETYPE_ARR[0]);
        int nCounter = 0, nInnerCounter = 0;
	int nRet = -1;
	int nRepeat = 0;

	char pPath[PATH_LEN] = {0,};
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_VIDEO2, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	#if defined(MOBILE) || defined(WEARABLE)	//Starts MOBILE or WEARABLE
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_NONE, GET_DISPLAY(g_pEvasObject));
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif //End MOBILE or WEARABLE

	nRet = player_set_uri(g_player, pPath);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	for(nInnerCounter = 0; nInnerCounter < nSize2; nInnerCounter++)
	{
		g_eMediaFormatMimetype = FORMAT_MIMETYPE_ARR[nInnerCounter];

		for( nCounter = 0; nCounter < nSize; nCounter++)
		{
			g_bPlayerAudioDecodedCallback = false;

			//get media format
			nRet = media_format_create(&hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaFormatGetError(nRet));
			CHECK_HANDLE(hMediaFormat, "media_format_create");

			//set audio format
			nRet = media_format_set_audio_mime(hMediaFormat, g_eMediaFormatMimetype);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_channel(hMediaFormat, EXPORT_PCM_STEREO);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_channel", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_samplerate(hMediaFormat, EXPORT_PCM_SAMPLERATE);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_samplerate", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			g_ePlayerAudioExtractOption = EXTRACT_OPTION_ARR[nCounter];
			nRet = player_set_media_packet_audio_frame_decoded_cb(g_player, hMediaFormat, g_ePlayerAudioExtractOption, PlayerAudioDecodedCb, NULL);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_unref(hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaFormatGetError(nRet));

			nRet = player_prepare(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

			nRet = player_start(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet));

			for(nRepeat = 0; nRepeat < LIMIT; nRepeat++) {
				PlayerWaitForAsync2(TIMEOUT2);
				if(g_bPlayerAudioDecodedCallback)
					break;
			}

			if (!g_bPlayerAudioDecodedCallback)
			{
				FPRINTF("[Line : %d][%s] player_audio_decoded_cb failed, error returned = callback not invoked\n", __LINE__, API_NAMESPACE);
				media_format_unref(hMediaFormat);
				player_stop(g_player);
				player_unprepare(g_player);
				return 1;
			}

			nRet = player_get_state(g_player, &state);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

			PlayerGetState(state);

			if ( state == PLAYER_STATE_READY || state == PLAYER_STATE_IDLE )
			{
				nRet = player_unset_media_packet_audio_frame_decoded_cb(g_player);
				PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_unset_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));
			}

			nRet = player_stop(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet));

			nRet = player_unprepare(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
		}

	}

	return 0;
}

//& purpose: Sets and unsets a media packet audio decoded callback function.
//& type : auto
/**
* @testcase			ITc_player_set_unset_media_packet_audio_frame_decoded_cb_signed_be_no_sync_and_deinterleave_p
* @author			SRID(karanam.s)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @since_tizen			5.5
* @description			Sets and unsets a media packet audio decoded callback function.
* @scenario			Sets and unsets a media packet audio decoded callback function.
* @apicovered			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb
* @passcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb and all precondition apis are 					successful
* @failcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb or any precondition api fails
* @precondition			media_format_create
* @postcondition		NA
*/
int ITc_player_set_unset_media_packet_audio_frame_decoded_cb_signed_be_no_sync_and_deinterleave_p(void)
{
	START_TEST;
	media_format_h hMediaFormat = NULL;
	player_state_e state;

	player_audio_extract_option_e EXTRACT_OPTION_ARR[]=
	{
		PLAYER_AUDIO_EXTRACT_NO_SYNC_AND_DEINTERLEAVE
	};

	media_format_mimetype_e FORMAT_MIMETYPE_ARR[]=
	{
		MEDIA_FORMAT_PCM_S16BE,
		MEDIA_FORMAT_PCM_S24BE,
		MEDIA_FORMAT_PCM_S32BE,
	};

	int nSize = sizeof(EXTRACT_OPTION_ARR)/sizeof(EXTRACT_OPTION_ARR[0]);
	int nSize2 = sizeof(FORMAT_MIMETYPE_ARR)/sizeof(FORMAT_MIMETYPE_ARR[0]);
        int nCounter = 0, nInnerCounter = 0;
	int nRet = -1;
	int nRepeat = 0;

	char pPath[PATH_LEN] = {0,};
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_VIDEO2, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	#if defined(MOBILE) || defined(WEARABLE)	//Starts MOBILE or WEARABLE
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_NONE, GET_DISPLAY(g_pEvasObject));
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif //End MOBILE or WEARABLE

	nRet = player_set_uri(g_player, pPath);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	for(nInnerCounter = 0; nInnerCounter < nSize2; nInnerCounter++)
	{
		g_eMediaFormatMimetype = FORMAT_MIMETYPE_ARR[nInnerCounter];

		for( nCounter = 0; nCounter < nSize; nCounter++)
		{
			g_bPlayerAudioDecodedCallback = false;

			//get media format
			nRet = media_format_create(&hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaFormatGetError(nRet));
			CHECK_HANDLE(hMediaFormat, "media_format_create");

			//set audio format
			nRet = media_format_set_audio_mime(hMediaFormat, g_eMediaFormatMimetype);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_channel(hMediaFormat, EXPORT_PCM_STEREO);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_channel", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_samplerate(hMediaFormat, EXPORT_PCM_SAMPLERATE);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_samplerate", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			g_ePlayerAudioExtractOption = EXTRACT_OPTION_ARR[nCounter];
			nRet = player_set_media_packet_audio_frame_decoded_cb(g_player, hMediaFormat, g_ePlayerAudioExtractOption, PlayerAudioDecodedCb, NULL);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_unref(hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaFormatGetError(nRet));

			nRet = player_prepare(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

			nRet = player_start(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet));

			for(nRepeat = 0; nRepeat < LIMIT; nRepeat++) {
				PlayerWaitForAsync2(TIMEOUT2);
				if(g_bPlayerAudioDecodedCallback)
					break;
			}

			if (!g_bPlayerAudioDecodedCallback)
			{
				FPRINTF("[Line : %d][%s] player_audio_decoded_cb failed, error returned = callback not invoked\n", __LINE__, API_NAMESPACE);
				media_format_unref(hMediaFormat);
				player_stop(g_player);
				player_unprepare(g_player);
				return 1;
			}

			nRet = player_get_state(g_player, &state);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

			PlayerGetState(state);

			if ( state == PLAYER_STATE_READY || state == PLAYER_STATE_IDLE )
			{
				nRet = player_unset_media_packet_audio_frame_decoded_cb(g_player);
				PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_unset_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));
			}

			nRet = player_stop(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet));

			nRet = player_unprepare(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
		}

	}

	return 0;
}

//& purpose: Sets and unsets a media packet audio decoded callback function.
//& type : auto
/**
* @testcase			ITc_player_set_unset_media_packet_audio_frame_decoded_cb_float_deinterleave_p
* @author			SRID(karanam.s)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @since_tizen			5.5
* @description			Sets and unsets a media packet audio decoded callback function.
* @scenario			Sets and unsets a media packet audio decoded callback function.
* @apicovered			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb
* @passcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb and all precondition apis are 					successful
* @failcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb or any precondition api fails
* @precondition			media_format_create
* @postcondition		NA
*/
int ITc_player_set_unset_media_packet_audio_frame_decoded_cb_float_deinterleave_p(void)
{
	START_TEST;
	media_format_h hMediaFormat = NULL;
	player_state_e state;

	player_audio_extract_option_e EXTRACT_OPTION_ARR[]=
	{
		PLAYER_AUDIO_EXTRACT_DEINTERLEAVE
	};

	media_format_mimetype_e FORMAT_MIMETYPE_ARR[]=
	{
		MEDIA_FORMAT_PCM_F32LE,
		MEDIA_FORMAT_PCM_F32BE,
	};

	int nSize = sizeof(EXTRACT_OPTION_ARR)/sizeof(EXTRACT_OPTION_ARR[0]);
	int nSize2 = sizeof(FORMAT_MIMETYPE_ARR)/sizeof(FORMAT_MIMETYPE_ARR[0]);
        int nCounter = 0, nInnerCounter = 0;
	int nRet = -1;
	int nRepeat = 0;

	char pPath[PATH_LEN] = {0,};
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_VIDEO2, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	#if defined(MOBILE) || defined(WEARABLE)	//Starts MOBILE or WEARABLE
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_NONE, GET_DISPLAY(g_pEvasObject));
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif //End MOBILE or WEARABLE

	nRet = player_set_uri(g_player, pPath);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	for(nInnerCounter = 0; nInnerCounter < nSize2; nInnerCounter++)
	{
		g_eMediaFormatMimetype = FORMAT_MIMETYPE_ARR[nInnerCounter];

		for( nCounter = 0; nCounter < nSize; nCounter++)
		{
			g_bPlayerAudioDecodedCallback = false;

			//get media format
			nRet = media_format_create(&hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaFormatGetError(nRet));
			CHECK_HANDLE(hMediaFormat, "media_format_create");

			//set audio format
			nRet = media_format_set_audio_mime(hMediaFormat, g_eMediaFormatMimetype);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_channel(hMediaFormat, EXPORT_PCM_STEREO);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_channel", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_samplerate(hMediaFormat, EXPORT_PCM_SAMPLERATE);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_samplerate", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			g_ePlayerAudioExtractOption = EXTRACT_OPTION_ARR[nCounter];
			nRet = player_set_media_packet_audio_frame_decoded_cb(g_player, hMediaFormat, g_ePlayerAudioExtractOption, PlayerAudioDecodedCb, NULL);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_unref(hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaFormatGetError(nRet));

			nRet = player_prepare(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

			nRet = player_start(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet));

			for(nRepeat = 0; nRepeat < LIMIT; nRepeat++) {
				PlayerWaitForAsync2(TIMEOUT2);
				if(g_bPlayerAudioDecodedCallback)
					break;
			}

			if (!g_bPlayerAudioDecodedCallback)
			{
				FPRINTF("[Line : %d][%s] player_audio_decoded_cb failed, error returned = callback not invoked\n", __LINE__, API_NAMESPACE);
				media_format_unref(hMediaFormat);
				player_stop(g_player);
				player_unprepare(g_player);
				return 1;
			}

			nRet = player_get_state(g_player, &state);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

			PlayerGetState(state);

			if ( state == PLAYER_STATE_READY || state == PLAYER_STATE_IDLE )
			{
				nRet = player_unset_media_packet_audio_frame_decoded_cb(g_player);
				PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_unset_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));
			}

			nRet = player_stop(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet));

			nRet = player_unprepare(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
		}

	}

	return 0;
}

//& purpose: Sets and unsets a media packet audio decoded callback function.
//& type : auto
/**
* @testcase			ITc_player_set_unset_media_packet_audio_frame_decoded_cb_float_no_sync_and_deinterleave_p
* @author			SRID(karanam.s)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @since_tizen			5.5
* @description			Sets and unsets a media packet audio decoded callback function.
* @scenario			Sets and unsets a media packet audio decoded callback function.
* @apicovered			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb
* @passcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb and all precondition apis are 					successful
* @failcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb or any precondition api fails
* @precondition			media_format_create
* @postcondition		NA
*/
int ITc_player_set_unset_media_packet_audio_frame_decoded_cb_float_no_sync_and_deinterleave_p(void)
{
	START_TEST;
	media_format_h hMediaFormat = NULL;
	player_state_e state;

	player_audio_extract_option_e EXTRACT_OPTION_ARR[]=
	{
		PLAYER_AUDIO_EXTRACT_NO_SYNC_AND_DEINTERLEAVE
	};

	media_format_mimetype_e FORMAT_MIMETYPE_ARR[]=
	{
		MEDIA_FORMAT_PCM_F32LE,
		MEDIA_FORMAT_PCM_F32BE,
	};

	int nSize = sizeof(EXTRACT_OPTION_ARR)/sizeof(EXTRACT_OPTION_ARR[0]);
	int nSize2 = sizeof(FORMAT_MIMETYPE_ARR)/sizeof(FORMAT_MIMETYPE_ARR[0]);
        int nCounter = 0, nInnerCounter = 0;
	int nRet = -1;
	int nRepeat = 0;

	char pPath[PATH_LEN] = {0,};
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_VIDEO2, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	#if defined(MOBILE) || defined(WEARABLE)	//Starts MOBILE or WEARABLE
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_NONE, GET_DISPLAY(g_pEvasObject));
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif //End MOBILE or WEARABLE

	nRet = player_set_uri(g_player, pPath);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	for(nInnerCounter = 0; nInnerCounter < nSize2; nInnerCounter++)
	{
		g_eMediaFormatMimetype = FORMAT_MIMETYPE_ARR[nInnerCounter];

		for( nCounter = 0; nCounter < nSize; nCounter++)
		{
			g_bPlayerAudioDecodedCallback = false;

			//get media format
			nRet = media_format_create(&hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaFormatGetError(nRet));
			CHECK_HANDLE(hMediaFormat, "media_format_create");

			//set audio format
			nRet = media_format_set_audio_mime(hMediaFormat, g_eMediaFormatMimetype);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_channel(hMediaFormat, EXPORT_PCM_STEREO);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_channel", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_samplerate(hMediaFormat, EXPORT_PCM_SAMPLERATE);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_samplerate", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			g_ePlayerAudioExtractOption = EXTRACT_OPTION_ARR[nCounter];
			nRet = player_set_media_packet_audio_frame_decoded_cb(g_player, hMediaFormat, g_ePlayerAudioExtractOption, PlayerAudioDecodedCb, NULL);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_unref(hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaFormatGetError(nRet));

			nRet = player_prepare(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

			nRet = player_start(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet));

			for(nRepeat = 0; nRepeat < LIMIT; nRepeat++) {
				PlayerWaitForAsync2(TIMEOUT2);
				if(g_bPlayerAudioDecodedCallback)
					break;
			}

			if (!g_bPlayerAudioDecodedCallback)
			{
				FPRINTF("[Line : %d][%s] player_audio_decoded_cb failed, error returned = callback not invoked\n", __LINE__, API_NAMESPACE);
				media_format_unref(hMediaFormat);
				player_stop(g_player);
				player_unprepare(g_player);
				return 1;
			}

			nRet = player_get_state(g_player, &state);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

			PlayerGetState(state);

			if ( state == PLAYER_STATE_READY || state == PLAYER_STATE_IDLE )
			{
				nRet = player_unset_media_packet_audio_frame_decoded_cb(g_player);
				PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_unset_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));
			}

			nRet = player_stop(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet));

			nRet = player_unprepare(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
		}

	}

	return 0;
}

//& purpose: Sets and unsets a media packet audio decoded callback function.
//& type : auto
/**
* @testcase			ITc_player_set_unset_media_packet_audio_frame_decoded_cb_unsigned_le_deinterleave_p
* @author			SRID(karanam.s)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @since_tizen			5.5
* @description			Sets and unsets a media packet audio decoded callback function.
* @scenario			Sets and unsets a media packet audio decoded callback function.
* @apicovered			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb
* @passcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb and all precondition apis are 					successful
* @failcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb or any precondition api fails
* @precondition			media_format_create
* @postcondition		NA
*/
int ITc_player_set_unset_media_packet_audio_frame_decoded_cb_unsigned_le_deinterleave_p(void)
{
	START_TEST;
	media_format_h hMediaFormat = NULL;
	player_state_e state;

	player_audio_extract_option_e EXTRACT_OPTION_ARR[]=
	{
		PLAYER_AUDIO_EXTRACT_DEINTERLEAVE
	};

	media_format_mimetype_e FORMAT_MIMETYPE_ARR[]=
	{
		MEDIA_FORMAT_PCM_U16LE,
		MEDIA_FORMAT_PCM_U24LE,
		MEDIA_FORMAT_PCM_U32LE,
	};

	int nSize = sizeof(EXTRACT_OPTION_ARR)/sizeof(EXTRACT_OPTION_ARR[0]);
	int nSize2 = sizeof(FORMAT_MIMETYPE_ARR)/sizeof(FORMAT_MIMETYPE_ARR[0]);
        int nCounter = 0, nInnerCounter = 0;
	int nRet = -1;
	int nRepeat = 0;

	char pPath[PATH_LEN] = {0,};
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_VIDEO2, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	#if defined(MOBILE) || defined(WEARABLE)	//Starts MOBILE or WEARABLE
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_NONE, GET_DISPLAY(g_pEvasObject));
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif //End MOBILE or WEARABLE

	nRet = player_set_uri(g_player, pPath);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	for(nInnerCounter = 0; nInnerCounter < nSize2; nInnerCounter++)
	{
		g_eMediaFormatMimetype = FORMAT_MIMETYPE_ARR[nInnerCounter];

		for( nCounter = 0; nCounter < nSize; nCounter++)
		{
			g_bPlayerAudioDecodedCallback = false;

			//get media format
			nRet = media_format_create(&hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaFormatGetError(nRet));
			CHECK_HANDLE(hMediaFormat, "media_format_create");

			//set audio format
			nRet = media_format_set_audio_mime(hMediaFormat, g_eMediaFormatMimetype);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_channel(hMediaFormat, EXPORT_PCM_STEREO);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_channel", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_samplerate(hMediaFormat, EXPORT_PCM_SAMPLERATE);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_samplerate", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			g_ePlayerAudioExtractOption = EXTRACT_OPTION_ARR[nCounter];
			nRet = player_set_media_packet_audio_frame_decoded_cb(g_player, hMediaFormat, g_ePlayerAudioExtractOption, PlayerAudioDecodedCb, NULL);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_unref(hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaFormatGetError(nRet));

			nRet = player_prepare(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

			nRet = player_start(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet));

			for(nRepeat = 0; nRepeat < LIMIT; nRepeat++) {
				PlayerWaitForAsync2(TIMEOUT2);
				if(g_bPlayerAudioDecodedCallback)
					break;
			}

			if (!g_bPlayerAudioDecodedCallback)
			{
				FPRINTF("[Line : %d][%s] player_audio_decoded_cb failed, error returned = callback not invoked\n", __LINE__, API_NAMESPACE);
				media_format_unref(hMediaFormat);
				player_stop(g_player);
				player_unprepare(g_player);
				return 1;
			}

			nRet = player_get_state(g_player,&state);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

			PlayerGetState(state);

			if ( state == PLAYER_STATE_READY || state == PLAYER_STATE_IDLE )
			{
				nRet = player_unset_media_packet_audio_frame_decoded_cb(g_player);
				PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_unset_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));
			}

			nRet = player_stop(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet));

			nRet = player_unprepare(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
		}

	}

	return 0;
}

//& purpose: Sets and unsets a media packet audio decoded callback function.
//& type : auto
/**
* @testcase			ITc_player_set_unset_media_packet_audio_frame_decoded_cb_unsigned_le_no_sync_and_deinterleave_p
* @author			SRID(karanam.s)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @since_tizen			5.5
* @description			Sets and unsets a media packet audio decoded callback function.
* @scenario			Sets and unsets a media packet audio decoded callback function.
* @apicovered			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb
* @passcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb and all precondition apis are 					successful
* @failcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb or any precondition api fails
* @precondition			media_format_create
* @postcondition		NA
*/
int ITc_player_set_unset_media_packet_audio_frame_decoded_cb_unsigned_le_no_sync_and_deinterleave_p(void)
{
	START_TEST;
	media_format_h hMediaFormat = NULL;
	player_state_e state;

	player_audio_extract_option_e EXTRACT_OPTION_ARR[]=
	{
		PLAYER_AUDIO_EXTRACT_NO_SYNC_AND_DEINTERLEAVE
	};

	media_format_mimetype_e FORMAT_MIMETYPE_ARR[]=
	{
		MEDIA_FORMAT_PCM_U16LE,
		MEDIA_FORMAT_PCM_U24LE,
		MEDIA_FORMAT_PCM_U32LE,
	};

	int nSize = sizeof(EXTRACT_OPTION_ARR)/sizeof(EXTRACT_OPTION_ARR[0]);
	int nSize2 = sizeof(FORMAT_MIMETYPE_ARR)/sizeof(FORMAT_MIMETYPE_ARR[0]);
        int nCounter = 0, nInnerCounter = 0;
	int nRet = -1;
	int nRepeat = 0;

	char pPath[PATH_LEN] = {0,};
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_VIDEO2, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	#if defined(MOBILE) || defined(WEARABLE)	//Starts MOBILE or WEARABLE
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_NONE, GET_DISPLAY(g_pEvasObject));
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif //End MOBILE or WEARABLE

	nRet = player_set_uri(g_player, pPath);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	for(nInnerCounter = 0; nInnerCounter < nSize2; nInnerCounter++)
	{
		g_eMediaFormatMimetype = FORMAT_MIMETYPE_ARR[nInnerCounter];

		for( nCounter = 0; nCounter < nSize; nCounter++)
		{
			g_bPlayerAudioDecodedCallback = false;

			//get media format
			nRet = media_format_create(&hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaFormatGetError(nRet));
			CHECK_HANDLE(hMediaFormat, "media_format_create");

			//set audio format
			nRet = media_format_set_audio_mime(hMediaFormat, g_eMediaFormatMimetype);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_channel(hMediaFormat, EXPORT_PCM_STEREO);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_channel", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_samplerate(hMediaFormat, EXPORT_PCM_SAMPLERATE);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_samplerate", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			g_ePlayerAudioExtractOption = EXTRACT_OPTION_ARR[nCounter];
			nRet = player_set_media_packet_audio_frame_decoded_cb(g_player, hMediaFormat, g_ePlayerAudioExtractOption, PlayerAudioDecodedCb, NULL);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_unref(hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaFormatGetError(nRet));

			nRet = player_prepare(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

			nRet = player_start(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet));

			for(nRepeat = 0; nRepeat < LIMIT; nRepeat++) {
				PlayerWaitForAsync2(TIMEOUT2);
				if(g_bPlayerAudioDecodedCallback)
					break;
			}

			if (!g_bPlayerAudioDecodedCallback)
			{
				FPRINTF("[Line : %d][%s] player_audio_decoded_cb failed, error returned = callback not invoked\n", __LINE__, API_NAMESPACE);
				media_format_unref(hMediaFormat);
				player_stop(g_player);
				player_unprepare(g_player);
				return 1;
			}

			nRet = player_get_state(g_player,&state);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

			PlayerGetState(state);

			if ( state == PLAYER_STATE_READY || state == PLAYER_STATE_IDLE )
			{
				nRet = player_unset_media_packet_audio_frame_decoded_cb(g_player);
				PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_unset_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));
			}

			nRet = player_stop(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet));

			nRet = player_unprepare(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
		}

	}

	return 0;
}

//& purpose: Sets and unsets a media packet audio decoded callback function.
//& type : auto
/**
* @testcase			ITc_player_set_unset_media_packet_audio_frame_decoded_cb_unsigned_be_no_sync_and_deinterleave_p
* @author			SRID(karanam.s)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @since_tizen			5.5
* @description			Sets and unsets a media packet audio decoded callback function.
* @scenario			Sets and unsets a media packet audio decoded callback function.
* @apicovered			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb
* @passcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb and all precondition apis are 					successful
* @failcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb or any precondition api fails
* @precondition			media_format_create
* @postcondition		NA
*/
int ITc_player_set_unset_media_packet_audio_frame_decoded_cb_unsigned_be_no_sync_and_deinterleave_p(void)
{
	START_TEST;
	media_format_h hMediaFormat = NULL;
	player_state_e state;

	player_audio_extract_option_e EXTRACT_OPTION_ARR[]=
	{
		PLAYER_AUDIO_EXTRACT_NO_SYNC_AND_DEINTERLEAVE
	};

	media_format_mimetype_e FORMAT_MIMETYPE_ARR[]=
	{
		MEDIA_FORMAT_PCM_U16BE,
		MEDIA_FORMAT_PCM_U24BE,
		MEDIA_FORMAT_PCM_U32BE,
	};

	int nSize = sizeof(EXTRACT_OPTION_ARR)/sizeof(EXTRACT_OPTION_ARR[0]);
	int nSize2 = sizeof(FORMAT_MIMETYPE_ARR)/sizeof(FORMAT_MIMETYPE_ARR[0]);
        int nCounter = 0, nInnerCounter = 0;
	int nRet = -1;
	int nRepeat = 0;

	char pPath[PATH_LEN] = {0,};
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_VIDEO2, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	#if defined(MOBILE) || defined(WEARABLE)	//Starts MOBILE or WEARABLE
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_NONE, GET_DISPLAY(g_pEvasObject));
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif //End MOBILE or WEARABLE

	nRet = player_set_uri(g_player, pPath);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	for(nInnerCounter = 0; nInnerCounter < nSize2; nInnerCounter++)
	{
		g_eMediaFormatMimetype = FORMAT_MIMETYPE_ARR[nInnerCounter];

		for( nCounter = 0; nCounter < nSize; nCounter++)
		{
			g_bPlayerAudioDecodedCallback = false;

			//get media format
			nRet = media_format_create(&hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaFormatGetError(nRet));
			CHECK_HANDLE(hMediaFormat, "media_format_create");

			//set audio format
			nRet = media_format_set_audio_mime(hMediaFormat, g_eMediaFormatMimetype);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_channel(hMediaFormat, EXPORT_PCM_STEREO);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_channel", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_samplerate(hMediaFormat, EXPORT_PCM_SAMPLERATE);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_samplerate", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			g_ePlayerAudioExtractOption = EXTRACT_OPTION_ARR[nCounter];
			nRet = player_set_media_packet_audio_frame_decoded_cb(g_player, hMediaFormat, g_ePlayerAudioExtractOption, PlayerAudioDecodedCb, NULL);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_unref(hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaFormatGetError(nRet));

			nRet = player_prepare(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

			nRet = player_start(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet));

			for(nRepeat = 0; nRepeat < LIMIT; nRepeat++) {
				PlayerWaitForAsync2(TIMEOUT2);
				if(g_bPlayerAudioDecodedCallback)
					break;
			}

			if (!g_bPlayerAudioDecodedCallback)
			{
				FPRINTF("[Line : %d][%s] player_audio_decoded_cb failed, error returned = callback not invoked\n", __LINE__, API_NAMESPACE);
				media_format_unref(hMediaFormat);
				player_stop(g_player);
				player_unprepare(g_player);
				return 1;
			}

			nRet = player_get_state(g_player,&state);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

			PlayerGetState(state);

			if ( state == PLAYER_STATE_READY || state == PLAYER_STATE_IDLE )
			{
				nRet = player_unset_media_packet_audio_frame_decoded_cb(g_player);
				PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_unset_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));
			}

			nRet = player_stop(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet));

			nRet = player_unprepare(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
		}

	}

	return 0;
}

//& purpose: Sets and unsets a media packet audio decoded callback function.
//& type : auto
/**
* @testcase			ITc_player_set_unset_media_packet_audio_frame_decoded_cb_unsigned_be_deinterleave_p
* @author			SRID(karanam.s)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @since_tizen			5.5
* @description			Sets and unsets a media packet audio decoded callback function.
* @scenario			Sets and unsets a media packet audio decoded callback function.
* @apicovered			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb
* @passcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb and all precondition apis are 					successful
* @failcase			player_set_media_packet_audio_frame_decoded_cb, player_unset_media_packet_audio_frame_decoded_cb or any precondition api fails
* @precondition			media_format_create
* @postcondition		NA
*/
int ITc_player_set_unset_media_packet_audio_frame_decoded_cb_unsigned_be_deinterleave_p(void)
{
	START_TEST;
	media_format_h hMediaFormat = NULL;
	player_state_e state;

	player_audio_extract_option_e EXTRACT_OPTION_ARR[]=
	{
		PLAYER_AUDIO_EXTRACT_DEINTERLEAVE
	};

	media_format_mimetype_e FORMAT_MIMETYPE_ARR[]=
	{
		MEDIA_FORMAT_PCM_U16BE,
		MEDIA_FORMAT_PCM_U24BE,
		MEDIA_FORMAT_PCM_U32BE,
	};

	int nSize = sizeof(EXTRACT_OPTION_ARR)/sizeof(EXTRACT_OPTION_ARR[0]);
	int nSize2 = sizeof(FORMAT_MIMETYPE_ARR)/sizeof(FORMAT_MIMETYPE_ARR[0]);
        int nCounter = 0, nInnerCounter = 0;
	int nRet = -1;
	int nRepeat = 0;

	char pPath[PATH_LEN] = {0,};
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_VIDEO2, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	#if defined(MOBILE) || defined(WEARABLE)	//Starts MOBILE or WEARABLE
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_NONE, GET_DISPLAY(g_pEvasObject));
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif //End MOBILE or WEARABLE

	nRet = player_set_uri(g_player, pPath);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	for(nInnerCounter = 0; nInnerCounter < nSize2; nInnerCounter++)
	{
		g_eMediaFormatMimetype = FORMAT_MIMETYPE_ARR[nInnerCounter];

		for( nCounter = 0; nCounter < nSize; nCounter++)
		{
			g_bPlayerAudioDecodedCallback = false;

			//get media format
			nRet = media_format_create(&hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaFormatGetError(nRet));
			CHECK_HANDLE(hMediaFormat, "media_format_create");

			//set audio format
			nRet = media_format_set_audio_mime(hMediaFormat, g_eMediaFormatMimetype);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_channel(hMediaFormat, EXPORT_PCM_STEREO);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_channel", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_set_audio_samplerate(hMediaFormat, EXPORT_PCM_SAMPLERATE);
			PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_samplerate", MediaFormatGetError(nRet), media_format_unref(hMediaFormat));

			g_ePlayerAudioExtractOption = EXTRACT_OPTION_ARR[nCounter];
			nRet = player_set_media_packet_audio_frame_decoded_cb(g_player, hMediaFormat, g_ePlayerAudioExtractOption, PlayerAudioDecodedCb, NULL);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), media_format_unref(hMediaFormat));

			nRet = media_format_unref(hMediaFormat);
			PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaFormatGetError(nRet));

			nRet = player_prepare(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

			nRet = player_start(g_player);
			PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet));

			for(nRepeat = 0; nRepeat < LIMIT; nRepeat++) {
				PlayerWaitForAsync2(TIMEOUT2);
				if(g_bPlayerAudioDecodedCallback)
					break;
			}

			if (!g_bPlayerAudioDecodedCallback)
			{
				FPRINTF("[Line : %d][%s] player_audio_decoded_cb failed, error returned = callback not invoked\n", __LINE__, API_NAMESPACE);
				media_format_unref(hMediaFormat);
				player_stop(g_player);
				player_unprepare(g_player);
				return 1;
			}

			nRet = player_get_state(g_player,&state);
			PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

			PlayerGetState(state);

			if ( state == PLAYER_STATE_READY || state == PLAYER_STATE_IDLE )
			{
				nRet = player_unset_media_packet_audio_frame_decoded_cb(g_player);
				PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_unset_media_packet_audio_frame_decoded_cb", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));
			}

			nRet = player_stop(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet));

			nRet = player_unprepare(g_player);
			PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
		}

	}

	return 0;
}

//& purpose: Retrieves all supported media formats for audio offload.
//& type : auto
/**
* @testcase			ITc_player_audio_offload_foreach_supported_format_p
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @since_tizen			5.5
* @description			Retrieves all supported media formats for audio offload.
* @scenario			Hit AudioOffloadFormatCB callback function and check for return value.
* @apicovered			player_audio_offload_foreach_supported_format
* @passcase			player_audio_offload_foreach_supported_format and all precondition apis are successful
* @failcase			player_audio_offload_foreach_supported_format or any precondition api fails
* @precondition			player_create
* @postcondition		NA
*/
int ITc_player_audio_offload_foreach_supported_format_p(void)
{
	START_TEST;

	int nRet = PLAYER_ERROR_NONE;
	bool bIsAudioOffloadSupported;
	g_bPlayerAudioOffloadFormatCallback = false;

	if(TCTCheckSystemInfoFeatureSupported(AUDIO_OFFLOAD_FEATURE, API_NAMESPACE))
	{
		bIsAudioOffloadSupported = true;
	}
	else
	{
		FPRINTF("[Line : %d][%s] AUDIO_OFFLOAD_FEATURE feature not supported for this device \\n", __LINE__, API_NAMESPACE);
		bIsAudioOffloadSupported = false;
	}

	//Target API
	nRet = player_audio_offload_foreach_supported_format(g_player, AudioOffloadFormatCB, NULL);
	if ( false == bIsAudioOffloadSupported )
	{
		FPRINTF("[Line : %d][%s] This feature is supported in specific device which has audio dsp to decode the content \\n", __LINE__, API_NAMESPACE);
		PRINT_RESULT(PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE, nRet, "player_audio_offload_foreach_supported_format", PlayerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_offload_foreach_supported_format", PlayerGetError(nRet));

	PlayerWaitForAsync();
	if(!g_bPlayerAudioOffloadFormatCallback)
	{
		FPRINTF("[Line : %d][%s] AudioOffloadFormatCB failed, error returned = callback not invoked\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Enables or disables the audio offload and gets the enabling status of audio offload.
//& type : auto
/**
* @testcase			ITc_player_audio_offload_set_is_enabled_p
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @since_tizen			5.5
* @description			Enables or disables the audio offload and gets the enabling status of audio offload.
* @scenario			Enable the audio offload and check whether it is set or not.
* @apicovered			player_audio_offload_set_enabled, player_audio_offload_is_enabled
* @passcase			player_audio_offload_set_enabled, player_audio_offload_is_enabled and all precondition apis are successful
* @failcase			player_audio_offload_set_enabled, player_audio_offload_is_enabled or any precondition api fails
* @precondition			player_create
* @postcondition		NA
*/

int ITc_player_audio_offload_set_is_enabled_p(void)
{
	START_TEST;

	int nRet = PLAYER_ERROR_NONE;
	bool bSetEnabled = true;
	bool bIsEnabled = false;
	bool bIsAudioOffloadSupported;
	player_state_e ePlayerState = PLAYER_STATE_NONE;

	if(TCTCheckSystemInfoFeatureSupported(AUDIO_OFFLOAD_FEATURE, API_NAMESPACE))
	{
		bIsAudioOffloadSupported = true;
	}
	else
	{
		FPRINTF("[Line : %d][%s] AUDIO_OFFLOAD_FEATURE feature not supported for this device \\n", __LINE__, API_NAMESPACE);
		bIsAudioOffloadSupported = false;
	}

	nRet = player_get_state(g_player, &ePlayerState);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet));

	if (ePlayerState != PLAYER_STATE_IDLE)
	{
		player_unprepare(g_player);
	}

	//Target API
	nRet = player_audio_offload_set_enabled(g_player, bSetEnabled);
	if ( false == bIsAudioOffloadSupported )
	{
		FPRINTF("[Line : %d][%s] This feature is supported in specific device which has audio dsp to decode the content \\n", __LINE__, API_NAMESPACE);
		PRINT_RESULT(PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE, nRet, "player_audio_offload_set_enabled", PlayerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_offload_set_enabled", PlayerGetError(nRet));

	//Target API
	nRet = player_audio_offload_is_enabled(g_player, &bIsEnabled);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_offload_is_enabled", PlayerGetError(nRet));
	PRINT_RESULT(bSetEnabled, bIsEnabled, "player_audio_offload_is_enabled", "Set enable and is enabled values are not matching");

	return 0;
}

//& purpose: Gets the activation status of audio offload.
//& type : auto
/**
* @testcase			ITc_player_audio_offload_is_activated_p
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @since_tizen			5.5
* @description			Gets the activation status of audio offload.
* @scenario			Check default activation state, later set and check the activation state.
* @apicovered			player_audio_offload_is_activated
* @passcase			player_audio_offload_is_activated and all precondition apis are successful
* @failcase			player_audio_offload_is_activated or any precondition api fails
* @precondition			player_create
* @postcondition		NA
*/
int ITc_player_audio_offload_is_activated_p(void)
{
	START_TEST;

	int nRet = PLAYER_ERROR_NONE;
	bool bSetEnabled = true;
	bool bIsActivated = true;
	bool bSetActivated = false;
	bool bIsAudioOffloadSupported = false;
	player_state_e ePlayerState = PLAYER_STATE_NONE;
	char pPath[PATH_LEN] = {0};

	if(TCTCheckSystemInfoFeatureSupported(AUDIO_OFFLOAD_FEATURE, API_NAMESPACE))
	{
		bIsAudioOffloadSupported = true;
	}
	else
	{
		FPRINTF("[Line : %d][%s] AUDIO_OFFLOAD_FEATURE feature not supported for this device \\n", __LINE__, API_NAMESPACE);
		bIsAudioOffloadSupported = false;
	}

	nRet = player_get_state(g_player, &ePlayerState);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet));

	if (ePlayerState != PLAYER_STATE_IDLE)
	{
		//Target API
		nRet = player_audio_offload_is_activated(g_player, &bIsActivated);
		if ( false == bIsAudioOffloadSupported )
		{
			FPRINTF("[Line : %d][%s] This feature is supported in specific device which has audio dsp to decode the content \\n", __LINE__, API_NAMESPACE);
			PRINT_RESULT(PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE, nRet, "player_audio_offload_is_activated", PlayerGetError(nRet));
			return 0;
		}
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_offload_is_activated", PlayerGetError(nRet));
		PRINT_RESULT(bSetActivated, bIsActivated, "player_audio_offload_is_activated", PlayerGetError(nRet));

		nRet = player_unprepare(g_player);
		PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
	}

	bSetActivated = true;
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_AUDIO, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	nRet = player_set_uri(g_player, pPath);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	//Target API
	nRet = player_audio_offload_set_enabled(g_player, bSetEnabled);
	if ( false == bIsAudioOffloadSupported )
	{
		FPRINTF("[Line : %d][%s] This feature is supported in specific device which has audio dsp to decode the content \\n", __LINE__, API_NAMESPACE);
		PRINT_RESULT(PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE, nRet, "player_audio_offload_is_activated", PlayerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_offload_set_enabled", PlayerGetError(nRet));

	nRet = player_prepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

	//Target API
	nRet = player_audio_offload_is_activated(g_player, &bIsActivated);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_offload_is_activated", PlayerGetError(nRet));
	PRINT_RESULT(bSetActivated, bIsActivated, "player_audio_offload_is_activated", PlayerGetError(nRet));

	return 0;
}

//& purpose: Retrieves all supported media format for playback of external media stream.
//& type : auto
/**
* @testcase			ITc_player_foreach_media_stream_supported_format_p
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type			auto
* @since_tizen			5.5
* @description			Retrieves all supported media format for playback of external media stream.
* @scenario			Hit PlayerSupportedMediaFormatCB callback function and check for API return value.
* @apicovered			player_foreach_media_stream_supported_format
* @passcase			player_foreach_media_stream_supported_format and all precondition apis are successful
* @failcase			player_foreach_media_stream_supported_format or any precondition api fails
* @precondition		player_create
* @postcondition		NA
*/
int ITc_player_foreach_media_stream_supported_format_p(void)
{
	START_TEST;

	int nRet = PLAYER_ERROR_NONE;
	g_bPlayerSupportedMediaFormatCallback = false;

	//Target API
	nRet = player_foreach_media_stream_supported_format(g_player, PlayerSupportedMediaFormatCB, NULL);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_foreach_media_stream_supported_format", PlayerGetError(nRet));

	if(!g_bPlayerSupportedMediaFormatCallback)
	{
		FPRINTF("[Line : %d][%s] player_foreach_media_stream_supported_format failed, error returned = PlayerSupportedMediaFormatCB callback not invoked\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

/** @} */
/** @} */
