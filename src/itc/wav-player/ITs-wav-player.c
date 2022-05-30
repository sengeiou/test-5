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
#include "ITs-wav-player-common.h"

/** @addtogroup itc-wav-player
*  @ingroup itc
*  @{
*/
static GMainLoop *g_pMainLoop;
bool g_bWavPlayerPlaybackCompletedCallback;

/*****************************************************Enum Definition Start*****************************************************/

sound_stream_type_e eStreamType[] = {
	SOUND_STREAM_TYPE_MEDIA,				/**< Sound stream type for media */
	SOUND_STREAM_TYPE_SYSTEM,				/**< Sound stream type for system */
	SOUND_STREAM_TYPE_ALARM,				/**< Sound stream type for alarm */
	SOUND_STREAM_TYPE_NOTIFICATION,			/**< Sound stream type for notification */
	SOUND_STREAM_TYPE_EMERGENCY,			/**< Sound stream type for emergency */
	SOUND_STREAM_TYPE_VOICE_INFORMATION,	/**< Sound stream type for voice information */
};


/*****************************************************Enum Definition End*****************************************************/

/****************************************************Callback Start****************************************************/

/**
* @function				WavPlayerPlaybackCompletedCallback
* @description			To Call when transcoding is finished just before storing in the file
* @parameter	[IN]	Wav Player ID
* @parameter	[IN]	The user data passed from the callback registration function
* @return				NA
*/
void WavPlayerPlaybackCompletedCallback(int nId, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] WavPlayerPlaybackCompletedCallback is called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bWavPlayerPlaybackCompletedCallback = true;

	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/****************************************************Callback End****************************************************/

/**
* @function 		ITs_wav_player_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_wav_player_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Wav_Player_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		ITs_wav_player_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_wav_player_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Wav_Player_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup itc-wav-player-testcases
*  @brief 		Integration testcases for module wav-player
*  @ingroup 	itc-wav-player
*  @{
*/

//& purpose: To start and stop playing a wav
//& type: auto
/**
* @testcase 			ITc_wav_player_start_new_stop_p
* @author				SRID(manu.tiwari)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			3.0
* @description			To start and stop playing a wav
* @scenario				Start the wav playing\n
*						Stop the wav playing
* @apicovered			wav_player_start_new, wav_player_stop
* @passcase				When wav_player_start_new and wav_player_stop is successful.
* @failcase				If target api wav_player_start_new or wav_player_stop fails or any precondition api fails.
* @precondition			We have to provide sleep according to length of the wav player file.
* @postcondition		NA
*/
int ITc_wav_player_start_new_stop_p(void)
{
	START_TEST;

	int nRet = -1;
	int nId = -1;
	sound_stream_info_h hStreamInfo = NULL;

	int enum_size1 = sizeof(eStreamType) / sizeof(eStreamType[0]);
	int enum_counter1 = 0;

	char pPath[PATH_LEN] = {0,};

	if ( false == WavPlayerAppendToAppDataPath(TESTFILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__,API_NAMESPACE);
		return 1;
	}

	for ( enum_counter1 = 0; enum_counter1 < enum_size1; enum_counter1++)
	{
		nId = -1;
		nRet = sound_manager_create_stream_information(eStreamType[enum_counter1], NULL, NULL, &hStreamInfo);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));
		CHECK_HANDLE(hStreamInfo, "sound_manager_create_stream_information");

		// Target API
		g_bWavPlayerPlaybackCompletedCallback = false;
		nRet = wav_player_start_new(pPath, hStreamInfo, WavPlayerPlaybackCompletedCallback, NULL, &nId);
		PRINT_RESULT(WAV_PLAYER_ERROR_NONE, nRet, "wav_player_start_new", WavPlayerGetError(nRet));
		if ( nId < 0 )
		{
			FPRINTF("[Line : %d][%s] wav_player_start_new failed, output parameter is having invalid value\\n", __LINE__, API_NAMESPACE);
			sound_manager_destroy_stream_information(hStreamInfo);
			return 1;
		}
		nRet = wav_player_stop(nId);
		PRINT_RESULT(WAV_PLAYER_ERROR_NONE, nRet, "wav_player_stop", WavPlayerGetError(nRet));

		nRet = sound_manager_destroy_stream_information(hStreamInfo);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information\\n", SoundManagerGetError(nRet));
	}
	return 0;
}

//& purpose: Plays a wav file multiple times
//& type: auto
/**
* @testcase 			ITc_wav_player_start_loop_p
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @since_tizen 			6.0
* @description			To play a wav file multiple times
* @scenario				Create stream info with sound-manager API
* 						start wav player loop
* @apicovered			wav_player_start_loop
* @passcase				When wav_player_start_loop is successful.
* @failcase				If target api wav_player_start_loop or any precondition api fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_wav_player_start_loop_p(void)
{
	START_TEST;

	int nRet = -1;
	int nId;
	int nLoopCount = 1;
	sound_stream_info_h hStreamInfo = NULL;

	int nSize = sizeof(eStreamType) / sizeof(eStreamType[0]);
	char pszPath[PATH_LEN] = {0,};

	if ( false == WavPlayerAppendToAppDataPath(TESTFILE, pszPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__,API_NAMESPACE);
		return 1;
	}

	for ( int nCount = 0; nCount < nSize; nCount++)
	{
		nId = -1;

		nRet = sound_manager_create_stream_information(eStreamType[nCount], NULL, NULL , &hStreamInfo);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));
		CHECK_HANDLE(hStreamInfo, "sound_manager_create_stream_information");

		// Target API
		g_bWavPlayerPlaybackCompletedCallback = false;
		nRet = wav_player_start_loop(pszPath, hStreamInfo, nLoopCount, WavPlayerPlaybackCompletedCallback, NULL, &nId);

		PRINT_RESULT(WAV_PLAYER_ERROR_NONE, nRet, "wav_player_start_loop", WavPlayerGetError(nRet));

		if ( nId < 0 )
		{
			FPRINTF("[Line : %d][%s] wav_player_start_loop failed, output parameter is having invalid value, nID = %d \\n", __LINE__, API_NAMESPACE, nId);
			sound_manager_destroy_stream_information(hStreamInfo);
			return 1;
		}

		g_pMainLoop = g_main_loop_new(NULL, false);
		g_main_loop_run(g_pMainLoop);

		PRINT_RESULT_CLEANUP(true, g_bWavPlayerPlaybackCompletedCallback, "WavPlayerPlaybackCompletedCallback", "CallBack Not Invoked", wav_player_stop(nId);sound_manager_destroy_stream_information(hStreamInfo));

		nRet = sound_manager_destroy_stream_information(hStreamInfo);
		PRINT_RESULT_NORETURN(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information\\n", SoundManagerGetError(nRet));
	}
	return 0;
}

/** @} */
/** @} */
