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
#include "CTs-player-common.h"

/** @addtogroup ctc-player
* @ingroup		ctc
* @{
*/

//& set: Player

/**
* @function 		CTs_capi_media_player_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_capi_media_player_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Player_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function 		CTs_capi_media_player_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_capi_media_player_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Player_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup	ctc-player-testcases
* @brief 		Integration testcases for module player
* @ingroup		ctc-player
* @{
*/

//& purpose: check whether the device is speaker supported or not
//& type : auto
/**
* @testcase			CTc_Player_IsSupportedSpeaker_p
* @since_tizen		2.3
* @author			SRID(anshul1.jain)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @scenario			Gets the boolean value from the runtime information. 
* 					Creates a player handle for playing multimedia content.
* 					Gets the player's current state. 
* 					Sets the data source (file-path, http or rtsp URI) to use. 
* 					Prepares the media player for playback.
* 					get the volume for preservation
* 					Sets the player's volume.
* 					player starts while GMainLoop starts.
* 					player stops while GMainLoop stops.
* 					set the preserved volume
* 					Resets the media player.
* 					Destroys the media player handle and releases all its resources.
* @apicovered		runtime_info_get_value_bool, player_create, player_get_state, player_set_uri, player_prepare, player_get_volume, player_set_volume, player_start, player_stop, player_unprepare, player_destroy
* @passcase			covered API should return zero success value or earphone is connected not to test speaker
* @failcase			covered API returns negative error value 
* @precondition		Earphone should be removed from the device
* @postcondition	NA
* @remarks			NA
*/
int CTc_Player_IsSupportedSpeaker_p(void)
{
	START_TEST;
	g_PlayerHandler = NULL;

	if ( PlayerInitialization(true, MeidaType_Audio) != true ) 
	{
		if ( g_PlayerHandler )
		{
			PlayerDestroy(false);
		}
		return 1;
	}
	
	float fLeft = 1.0, fRight = 1.0, fPreserveLeftVol = 0.0, fPreserveRightVol = 0.0;
	if ( PlayerSetVolume(&fPreserveLeftVol, &fPreserveRightVol, fLeft, fRight) != true )
	{
		PlayerDestroy(true);
		return 1;
	}
	
	RUN_POLLING_LOOP;

	// restore the volume
	int nRet = player_set_volume(g_PlayerHandler, fPreserveLeftVol, fPreserveRightVol);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_volume", PlayerGetError(nRet), CLEAR_GLOOP;PlayerDestroy(true));
	
	CLEAR_GLOOP;
	if ( PlayerDestroy(true) != true )
	{
		return 1;
	}	
	return 0;
}

//& purpose: check whether the speaker volume control up is working or not 
//& type : auto
/**
* @testcase			CTc_Player_SpeakerVolumeControlUp_p
* @since_tizen		2.3
* @author			SRID(anshul1.jain)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @scenario			Gets the boolean value from the runtime information\n
* 					Creates a player handle for playing multimedia content\n
* 					Gets the player's current state\n
* 					Sets the data source (file-path, http or rtsp URI) to use\n
* 					Prepares the media player for playback\n
* 					get the volume for preservation\n
* 					Sets the player's volume\n
* 					Starts or resumes playback\n
* 					Get the volume of the player\n
* 					Set the volume of that player with get-value + 0.1\n
* 					Match those values\n
* 					Stops playing media content\n
* 					set the preserved volume\n
* 					Resets the media player\n
* 					Destroys the media player handle and releases all its resources
* @apicovered		runtime_info_get_value_bool, player_create, player_get_state, player_set_uri, player_prepare, player_get_volume, player_set_volume, player_start, player_stop, player_unprepare, player_destroy
* @passcase			Covered API should return zero success value or earphone is connected not to test speaker
* @failcase			Covered API returns negative error value 
* @precondition		Earphone should be removed from the device
* @postcondition	NA
* @remarks			Volume sets min(0.0) in loop and increases by .1 in each iteration. 
*/
int CTc_Player_SpeakerVolumeControlUp_p(void)
{
	START_TEST;
	
	g_PlayerHandler = NULL;
	if ( PlayerInitialization(true, MeidaType_Audio) != true ) 
	{
		if ( g_PlayerHandler )
		{
			PlayerDestroy(false);
		}
		return 1;
	}
	
	float fLeft = 0.0, fRight = 0.0, fGetLeftVol1 = 0.0, fGetRightVol1 = 0.0, fGetLeftVol2 = 0.0, fGetRightVol2 = 0.0, fPreserveLeftVol = 0.0, fPreserveRightVol = 0.0;
	if ( PlayerSetVolume(&fPreserveLeftVol, &fPreserveRightVol, fLeft, fRight) != true )
	{
		PlayerDestroy(true);
		return 1;
	}

	RUN_POLLING_LOOP;

	int nRet, nLoopCount;
	for ( nLoopCount = 1; nLoopCount < MAX_SPEAKER_VOLUME_CONTROL; nLoopCount++ )
	{
		nRet = player_set_volume(g_PlayerHandler,fGetLeftVol1,fGetRightVol1);
		PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_volume", PlayerGetError(nRet), CLEAR_GLOOP;PlayerDestroy(true));

		fGetLeftVol2 = fGetRightVol2 = 0.0;

		nRet = player_get_volume(g_PlayerHandler,&fGetLeftVol2,&fGetRightVol2);
		PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_volume", PlayerGetError(nRet), CLEAR_GLOOP;PlayerDestroy(true));
		
		if ( (fGetLeftVol2 != fGetLeftVol1 ) || (fGetRightVol2 != fGetRightVol1) )
		{
			FPRINTF("[Line : %d][%s] set and get values are mismatch ! \n\\n", __LINE__, API_NAMESPACE);
			CLEAR_GLOOP;
			PlayerDestroy(true);
			return 1;
		}
		fGetLeftVol1 = fGetLeftVol1 + 0.1;
		fGetRightVol1 = fGetRightVol1 + 0.1;
	}
	CLEAR_GLOOP;
	
	// restore the volume
	nRet = player_set_volume(g_PlayerHandler,fPreserveLeftVol,fPreserveRightVol);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_volume", PlayerGetError(nRet), PlayerDestroy(true));
	
	if ( PlayerDestroy(true) != true )
	{
		return 1;
	}
	return 0;
}

//& purpose: check whether the speaker volume control Down is working or not 
//& type : auto
/**
* @testcase			CTc_Player_SpeakerVolumeControlDown_p
* @since_tizen		2.3
* @author			SRID(anshul1.jain)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @scenario			Gets the boolean value from the runtime information\n
* 					Creates a player handle for playing multimedia content\n
* 					Gets the player's current state\n
* 					Sets the data source (file-path, http or rtsp URI) to use\n
* 					Prepares the media player for playback\n
* 					Get the volume for preservation\n
* 					Sets the player's volume\n
* 					Starts or resumes playback\n
* 					Get the volume of the player\n
* 					Set the volume of that player with get-value - 0.1\n
* 					Match those values\n
* 					Stops playing media content\n
* 					Set the preserved volume\n
* 					Resets the media player\n
* 					Destroys the media player handle and releases all its resources
* @apicovered		runtime_info_get_value_bool, player_create, player_get_state, player_set_uri, player_prepare, player_get_volume, player_set_volume, player_start, player_stop, player_unprepare, player_destroy
* @passcase			Covered API should return zero success value or earphone is connected not to test speaker
* @failcase			Covered API returns negative error value 
* @precondition		Earphone should be removed from the device
* @postcondition	NA
* @remarks			Volume sets max(1.0) in loop and decreases by .1 in each iteration.
*/
int CTc_Player_SpeakerVolumeControlDown_p(void)
{
	START_TEST;
	
	g_PlayerHandler = NULL;
	if ( PlayerInitialization(true, MeidaType_Audio) != true ) 
	{
		if ( g_PlayerHandler )
		{
			PlayerDestroy(false);
		}
		return 1;
	}
	
	float fLeft = 1.0, fRight = 1.0, fGetLeftVol1 = 1.0, fGetRightVol1 = 1.0, fGetLeftVol2 = 0.0, fGetRightVol2 = 0.0, fPreserveLeftVol = 0.0, fPreserveRightVol = 0.0;
	if ( PlayerSetVolume(&fPreserveLeftVol, &fPreserveRightVol, fLeft, fRight) != true )
	{
		PlayerDestroy(true);
		return 1;
	}
	
	RUN_POLLING_LOOP;

	int nRet, nLoopCount;
	for ( nLoopCount = 1; nLoopCount < MAX_SPEAKER_VOLUME_CONTROL; nLoopCount++ )
	{
		nRet = player_set_volume(g_PlayerHandler, fGetLeftVol1, fGetRightVol1);
		PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_volume", PlayerGetError(nRet), CLEAR_GLOOP;PlayerDestroy(true));
		
		nRet = player_get_volume(g_PlayerHandler, &fGetLeftVol2, &fGetRightVol2);
		PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_volume", PlayerGetError(nRet), CLEAR_GLOOP;PlayerDestroy(true));

		if ( (fabs(fGetLeftVol2 - fGetLeftVol1) > 0.0000005) || (fabs(fGetRightVol2 - fGetRightVol1) > 0.0000005) )
		{
			FPRINTF("[Line : %d][%s] set and get values are mismatch ! \n\\n", __LINE__, API_NAMESPACE);
			CLEAR_GLOOP;
			PlayerDestroy(true);
			return 1;
		}
		fGetLeftVol1 = fGetLeftVol1 - 0.1;
		fGetRightVol1 = fGetRightVol1 - 0.1;
	}
	CLEAR_GLOOP;

	// restore the volume
	nRet = player_set_volume(g_PlayerHandler, fPreserveLeftVol, fPreserveRightVol);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_volume", PlayerGetError(nRet), PlayerDestroy(true));

	if ( PlayerDestroy(true) != true )
	{
		return 1;
	}
	return 0;
}

//& purpose: check whether the speaker volume control mute is working or not
//& type : auto
/**
* @testcase			CTc_Player_SpeakerVolumeControlMute_p
* @since_tizen		2.3
* @author			SRID(anshul1.jain)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @scenario			Gets the boolean value from the runtime information\n
* 					Creates a player handle for playing multimedia content\n
* 					Gets the player's current state\n
* 					Sets the data source (file-path, http or rtsp URI) to use\n
* 					Prepares the media player for playback\n
* 					Get the volume for preservation\n
* 					Sets the player's volume\n
* 					Starts or resumes playback\n
* 					Sets the player's mute status\n
* 					Gets the player's mute status\n
* 					Stops playing media content\n
* 					Set the preserved volume\n
* 					Resets the media player\n
* 					Destroys the media player handle and releases all its resources
* @apicovered		runtime_info_get_value_bool, player_create, player_get_state, player_set_uri, player_prepare, player_get_volume, player_set_volume, player_start, player_stop, player_set_mute, player_is_muted, player_unprepare, player_destroy
* @passcase			Covered API should return zero success value or earphone is connected not to test speaker
* @failcase			Covered API returns negative error value 
* @precondition		Earphone should be removed from the device
* @postcondition	NA
* @remarks			NA 
*/
int CTc_Player_SpeakerVolumeControlMute_p(void)
{
	START_TEST;
	
	g_PlayerHandler = NULL;
	if ( PlayerInitialization(true, MeidaType_Audio) != true ) 
	{
		if ( g_PlayerHandler )
		{
			PlayerDestroy(false);
		}
		return 1;
	}

	float fLeft = 1.0, fRight = 1.0, fPreserveLeftVol = 0.0, fPreserveRightVol = 0.0;
	if ( PlayerSetVolume(&fPreserveLeftVol, &fPreserveRightVol, fLeft, fRight) != true )
	{
		PlayerDestroy(true);
		return 1;
	}

	RUN_POLLING_LOOP;

	int nRet, nLoopCount;
	bool bMute = false, bIsMuted = true;
	for ( nLoopCount = 1; nLoopCount < 9; nLoopCount++ )
	{
		bIsMuted = !bIsMuted;
		bMute = !bMute;

		nRet = player_set_mute(g_PlayerHandler, bMute);
		PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_mute", PlayerGetError(nRet), CLEAR_GLOOP;PlayerDestroy(true));
		
		nRet = player_is_muted(g_PlayerHandler, &bIsMuted);
		PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_is_muted", PlayerGetError(nRet), CLEAR_GLOOP;PlayerDestroy(true));		
		if ( bIsMuted != bMute )
		{
			FPRINTF("[Line : %d][%s] set and get values are mismatched!\\n", __LINE__, API_NAMESPACE);
			CLEAR_GLOOP;
			PlayerDestroy(true);
			return 1;
		}
	}

	CLEAR_GLOOP;

	// restore the volume
	nRet = player_set_volume(g_PlayerHandler, fPreserveLeftVol, fPreserveRightVol);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_volume", PlayerGetError(nRet), PlayerDestroy(true));

	if ( PlayerDestroy(true) != true )
	{
		return 1;
	}
	return 0;
}

/** @} */ //end of ctc-player
/** @} */ //end of ctc-player-testcases
