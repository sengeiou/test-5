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
#include "ITs-tone-player-common.h"

/** @addtogroup itc-tone-player
*  @ingroup itc
*  @{
*/

//& set: TonePlayer
/**
* @function 		ITs_tone_player_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_tone_player_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Tone_Player_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		ITs_tone_player_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_tone_player_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Tone_Player_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		test_sound_manager_stream_focus_state_changed_cb
* @description	 	callback function
* @parameter		sound_stream_info_h stream_info, sound_stream_focus_mask_e focus_mask, sound_stream_focus_state_e focus_state, sound_stream_focus_change_reason_e reason, int sound_behavior, const char *extra_info, void *user_data
* @return 			NA
*/
static void test_sound_manager_stream_focus_state_changed_cb(sound_stream_info_h stream_info,
															sound_stream_focus_mask_e focus_mask,
															sound_stream_focus_state_e focus_state,
															sound_stream_focus_change_reason_e reason,
															int sound_behavior,
															const char *extra_info,
															void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside callback \"test_sound_manager_stream_focus_state_changed_cb\"\\n", __LINE__, API_NAMESPACE);
}

/** @addtogroup itc-tone-player-testcases
*  @brief 		Integration testcases for module tone-player
*  @ingroup 	itc-tone-player
*  @{
*/

//& purpose: To start and stop playing a tone
//& type: auto
/**
* @testcase 			ITc_tone_player_start_new_stop_p
* @since_tizen 			3.0
* @author				SRID(manu.tiwari)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			To start and stop playing a tone
* @scenario				Start the tone playing\n
*						Stop the tone playing
* @apicovered			tone_player_start_new, tone_player_stop
* @passcase				When tone_player_start_new and tone_player_stop is successful
* @failcase				If target API tone_player_start_new or tone_player_stop fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_tone_player_start_new_stop_p(void)
{
	START_TEST;

	int nRet, nId;
	int nDurationMs = DURATION;
	sound_stream_info_h hStreamInfo = NULL;

	sound_stream_type_e arrStreamType[] = {
		SOUND_STREAM_TYPE_MEDIA,
		SOUND_STREAM_TYPE_SYSTEM,
		SOUND_STREAM_TYPE_ALARM,
		SOUND_STREAM_TYPE_NOTIFICATION,
		SOUND_STREAM_TYPE_EMERGENCY,
		SOUND_STREAM_TYPE_RINGTONE_VOIP,
	};

	tone_type_e g_eToneType[] = {
		TONE_TYPE_DTMF_0,
		TONE_TYPE_ANSI_DIAL,
		TONE_TYPE_SUP_BUSY,
		TONE_TYPE_CDMA_CONFIRM,
	};

	int enum_size1 = sizeof(arrStreamType) / sizeof(arrStreamType[0]);
	int enum_counter1 = 0;
	int enum_size2 = sizeof(g_eToneType) / sizeof(g_eToneType[0]);
	int enum_counter2 = 0;

	for ( enum_counter1=0; enum_counter1<enum_size1; enum_counter1++)
	{
		nRet = sound_manager_create_stream_information(arrStreamType[enum_counter1], test_sound_manager_stream_focus_state_changed_cb, NULL, &hStreamInfo);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));
		CHECK_HANDLE(hStreamInfo, "sound_manager_create_stream_information");

		for ( enum_counter2=0; enum_counter2<enum_size2; enum_counter2++)
		{
			nId = -1;
			// Target API
			nRet = tone_player_start_new(g_eToneType[enum_counter2], hStreamInfo, nDurationMs, &nId);
			if ( nRet != TONE_PLAYER_ERROR_NONE )
			{
				FPRINTF("[line : %d][%s] tone_player_start_new failed for StreamType = %s and ToneType = %s, error returned = %s\\n",
						__LINE__, API_NAMESPACE, SoundManagerGetStreamType(arrStreamType[enum_counter1]), TonePlayerGetType(g_eToneType[enum_counter2]), TonePlayerGetError(nRet));
				sound_manager_destroy_stream_information(hStreamInfo);
				return 1;
			}
			if ( nId < 0 )
			{
				FPRINTF("[Line : %d][%s] tone_player_start_new failed, invalid tone player id returned p\\n", __LINE__, API_NAMESPACE);
				sound_manager_destroy_stream_information(hStreamInfo);
				return 1;
			}
			nRet = tone_player_stop(nId);
			if ( nRet != TONE_PLAYER_ERROR_NONE )
			{
				FPRINTF("[line : %d][%s] tone_player_stop failed for StreamType = %s and ToneType = %s, error returned = %s\\n",
						__LINE__, API_NAMESPACE, SoundManagerGetStreamType(arrStreamType[enum_counter1]), TonePlayerGetType(g_eToneType[enum_counter2]), TonePlayerGetError(nRet));
				sound_manager_destroy_stream_information(hStreamInfo);
				return 1;
			}
		}

		nRet = sound_manager_destroy_stream_information(hStreamInfo);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information\\n", SoundManagerGetError(nRet));
	}

	return 0;
}

/** @} */
/** @} */
