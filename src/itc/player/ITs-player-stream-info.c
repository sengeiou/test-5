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
#include "ITs-player-common.h"

/** @addtogroup itc-player
*  @ingroup itc
*  @{
*/

//& set: Player
bool g_bPlayerCreation;
sound_stream_info_h g_stream_info_h = NULL;
bool g_bCallbackHit;

static bool _check_sound_stream_feature(void)
{
    bool supported = FALSE;

    system_info_get_platform_bool(SOUND_STREAM_FEATURE, &supported);

    if (supported)
        return true;

    FPRINTF("[Line : %d][%s] sound_stream is not supportable.\\n", __LINE__, API_NAMESPACE);
    return false;
}

/**
* @function			ITs_player_startup
* @description		Called before each test, created player handle
* @parameter		NA
* @return			NA
*/
void ITs_player_stream_info_startup(void)
{
#ifndef TIZENIOT // For Mobile or Wearable
	ecore_main_loop_glib_integrate();
#endif // For Mobile or Wearable

	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
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
#endif // For Mobile or Wearable

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
void ITs_player_stream_info_cleanup(void)
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
#endif // For Mobile or Wearable

	return;
}

/**
* @function			focus_callback
* @description
* @parameter		NA
* @return			NA
*/
void focus_callback (sound_stream_info_h stream_info,
					sound_stream_focus_mask_e focus_mask,
					sound_stream_focus_state_e focus_state,
					sound_stream_focus_change_reason_e reason,
					int sound_behavior,
					const char *extra_info,
					void *user_data)
{
	g_print("FOCUS callback is called, mask(%d), state(%d), reason(%d), sound_behavior(%d), extra_info(%s), userdata(%p)",
			focus_mask, focus_state, reason, sound_behavior, extra_info, user_data);
	return;
}

/**
* @function			player_adaptive_variant_callback
* @description		Called to notify the streaming variant information
* @parameter		int bandwidth, int width, int height, void *user_data
* @return			NA
*/
void player_adaptive_variant_callback(int bandwidth, int width, int height, void *user_data)
{
	FPRINTF("Inside player_adaptive_variant_callback\n");
	g_bCallbackHit = true;
	return;
}

/** @addtogroup itc-player-testcases
*  @brief		Integration testcases for module player
*  @ingroup		itc-player
*  @{
*/


//& purpose: Provides the audio stream information
//& type : auto
/**
* @testcase				ITc_player_get_audio_stream_info_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Provides the audio stream information
* @scenario				Initialize player handle\n
*						start player\n
*						call player get audio stream info\n
*						check the result\n
*						destroy the handler
* @apicovered			player_get_audio_stream_info, player_unprepare
* @passcase				When it gets audio stream information
* @failcase				When it can not get audio stream information
* @precondition			The player state must be one of: PLAYER_STATE_PLAYING, or PLAYER_STATE_PAUSED
* @postcondition		N/A
*/
int ITc_player_get_audio_stream_info_p(void)
{
	START_TEST;

	int nSample_rate;
	int nChannel;
	int nBit_rate;
	player_state_e state;

	if ( InitializePlayerHandler(true, 0) != true )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	int nRet = player_start(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player) );

	PlayerGetState(state);
	if ( state != PLAYER_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_start() call",__LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_get_audio_stream_info(g_player,&nSample_rate,&nChannel,&nBit_rate);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_audio_stream_info", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	nRet = player_stop(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
	return 0;
}



//& purpose: Provides the audio stream information
//& type : auto
/**
* @testcase				ITc_player_set_sound_stream_info_p
* @author				SRID(sk.pal)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			3.0
* @description			Provides the audio stream information
* @scenario				Initialize player handle\n
*						start player\n
*						call player set audio policy info\n
*						check the result\n
*						destroy the handler
* @apicovered			player_get_audio_stream_info, player_unprepare
* @passcase				When it gets audio stream information
* @failcase				When it can not get audio stream information
* @precondition			The player state must be one of: PLAYER_STATE_PLAYING, or PLAYER_STATE_PAUSED
* @postcondition		N/A
*/
int ITc_player_set_sound_stream_info_p(void)
{
	START_TEST;

	player_state_e state;
	int nRet = -1, nEnumCount = 0;
	sound_type_e e_set_sound_type = SOUND_TYPE_SYSTEM;
	int arrSoundTypeValue[] = {
		SOUND_TYPE_SYSTEM,			/**< Sound type for system */
		SOUND_TYPE_NOTIFICATION,	/**< Sound type for notifications */
		SOUND_TYPE_ALARM,			/**< Sound type for alarm */
		SOUND_TYPE_RINGTONE,		/**< @internal Sound type for ringtones */
		SOUND_TYPE_MEDIA,			/**< Sound type for media */
		SOUND_TYPE_CALL			/**< @internal Sound type for call */
		//SOUND_TYPE_VOIP,			  /**< @internal Sound type for voip */
	};
	int nSoundTypeCount = sizeof(arrSoundTypeValue) / sizeof(arrSoundTypeValue[0]);
	if ( InitializePlayerHandler(false, 0) != true )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet));

	PlayerGetState(state);
	if (g_stream_info_h)
	{
		FPRINTF("stream information is already set, please destory handle and try again\n");
		return 1;
	}

	for ( nEnumCount = 0;nEnumCount < nSoundTypeCount;nEnumCount++ )
	{
		e_set_sound_type = arrSoundTypeValue[nEnumCount];
		if (sound_manager_create_stream_information( e_set_sound_type, focus_callback, g_player, &g_stream_info_h))
		{
			FPRINTF("failed to create stream_information()\n");
			return 1;
		}
		nRet = player_set_sound_stream_info(g_player, g_stream_info_h);
		if (!_check_sound_stream_feature())
		{
			PRINT_RESULT(PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE, nRet, "player_set_sound_stream_info", PlayerGetError(nRet));
			/*in case of err, above macro return err(1) */
			return 0;
		}

		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_sound_stream_info", PlayerGetError(nRet));
	}

	return 0;
}

//& purpose: Verifies wether set and get of the variant limit is being done correctly or not
//& type : auto
/**
* @testcase				ITc_player_set_get_adaptive_variant_limit_p
* @author				SRID(bipin.k)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @since_tizen			4.0
* @description			Provides set get variant limit
* @scenario				Initialize player handle\n
*						start player\n
*						call set adaptive variant limit \n
*						get adaptive variant limit \n
*						destroy the handler
* @apicovered			player_set_max_adaptive_variant_limit,
*						player_get_max_adaptive_variant_limit, player_unprepare
* @passcase				When bandwidth ,height and width are set and get correctly.
* @failcase				When bandwidth ,height and width any of them is not set and get properly
* @precondition			The player state must be one of: PLAYER_STATE_IDLE, PLAYER_STATE_READY, PLAYER_STATE_PLAYING or PLAYER_STATE_PAUSED.
* @postcondition		N/A
*/
int ITc_player_set_get_adaptive_variant_limit_p(void)
{
	START_TEST;

	int nSetBandwidth = 500000, nSetWidth = 1920, nSetHeight = 1080;
	int nGetBandwidth = 0, nGetWidth = 0, nGetHeight = 0;

	if ( InitializePlayerHandler(true, 5) != true )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	int nRet =	player_set_max_adaptive_variant_limit(g_player, nSetBandwidth, nSetWidth, nSetHeight);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_max_adaptive_variant_limit", PlayerGetError(nRet));

	nRet = player_get_max_adaptive_variant_limit(g_player, &nGetBandwidth, &nGetWidth, &nGetHeight);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_max_adaptive_variant_limit", PlayerGetError(nRet));
	if(nSetBandwidth != nGetBandwidth)
	{
		FPRINTF("[Line : %d][%s] Value Mismatch nSetBandwidth = %d	nGetBandwidth = %d\\n", __LINE__, API_NAMESPACE,nSetBandwidth,nGetBandwidth);
		return 1;
	}
	if(nSetWidth != nGetWidth)
	{
		FPRINTF("[Line : %d][%s] Value Mismatch nSetWidth = %d	nGetWidth = %d\\n", __LINE__, API_NAMESPACE,nSetWidth,nGetWidth);
		return 1;
	}
	if(nSetHeight != nGetHeight)
	{
		FPRINTF("[Line : %d][%s] Value Mismatch nSetHeight = %d	 nGetHeight = %d\\n", __LINE__, API_NAMESPACE,nSetHeight,nGetHeight);
		return 1;
	}
	FPRINTF("[Line : %d][%s] nSetBandwidth = %d	 nGetBandwidth = %d nSetWidth = %d	nGetWidth = %d nSetHeight = %d	nGetHeight = %d\\n", __LINE__, API_NAMESPACE,nSetBandwidth,nGetBandwidth,nSetWidth,nGetWidth,nSetHeight,nGetHeight);
	return 0;
}

//& purpose: Verifies wether callback of adaptive_variant is being called correctly or not
//& type : auto
/**
* @testcase				ITc_player_foreach_adaptive_variant_p
* @author				SRID(bipin.k)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @since_tizen			4.0
* @description			adaptive variant callback is being set and called
* @scenario				Initialize player handle\n
*						start player\n
*						set adaptive variant callback \n
*						check wether adaptive variant callback is called or not \n
*						destroy the handler\n
* @apicovered			player_foreach_adaptive_variant, player_unprepare
* @passcase				Callback set is being called correctly.
* @failcase				When set callback is not being called.
* @precondition			The player state must be one of: PLAYER_STATE_READY, PLAYER_STATE_PLAYING or PLAYER_STATE_PAUSED
* @postcondition		N/A
*/
int ITc_player_foreach_adaptive_variant_p(void)
{
START_TEST;

	g_bCallbackHit =false;

	if( InitializePlayerHandler(true, 5) != true )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	int nRet = player_foreach_adaptive_variant(g_player,player_adaptive_variant_callback, NULL);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet,"player_foreach_adaptive_variant", PlayerGetError(nRet));
	if(g_bCallbackHit == false)
	{
		FPRINTF("[Line : %d][%s] Callback not hit\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets the album art in media resource
//& type : auto
/**
* @testcase				ITc_player_get_album_art_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Gets the album art in media resource
* @scenario				Initialize player handle\n
*						start player\n
*						get album art\n
*						check the result\n
*						destroy the handler
* @apicovered			player_start, player_get_album_art, player_unprepare
* @passcase				When it can get the album art
* @failcase				When it can not get the album art
* @precondition			The player state must be PLAYER_STATE_PLAYING
* @postcondition		N/A
*/
int ITc_player_get_album_art_p(void)
{
	START_TEST;

	void* pAlbum_Art;
	int nSize;
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
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_get_album_art(g_player, &pAlbum_Art, &nSize);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_album_art", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	nRet = player_stop(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
	return 0;
}

//& purpose: Gets the audio codec information
//& type : auto
/**
* @testcase				ITc_player_get_codec_info_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Gets the audio codec information
* @scenario				Initialize player handle\n
*						start player\n
*						get audio codec information\n
*						check the result\n
*						destroy the handler
* @apicovered			player_start, player_get_codec_info, player_unprepare
* @passcase				When it can get audio codec information
* @failcase				When it can not get audio codec information
* @precondition			The player state must be PLAYER_STATE_PLAYING
* @postcondition		N/A
*/
int ITc_player_get_codec_info_p(void)
{
	START_TEST;

	char *pszAudio_Codec;
	char *pszVideo_Codec;
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
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_get_codec_info(g_player, &pszAudio_Codec, &pszVideo_Codec);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_codec_info", PlayerGetError(nRet), FREE_MEMORY(pszAudio_Codec);FREE_MEMORY(pszVideo_Codec);player_stop(g_player);player_unprepare(g_player));

	nRet = player_stop(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
	return 0;
}


//& purpose: Gets the media content information
//& type : auto
/**
* @testcase				ITc_player_get_content_info_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Gets the media content information
* @scenario				initilize player\n
*						call player_get_content_info\n
*						destroy the handler
* @apicovered			player_start, player_get_content_info, player_unprepare ,player_stop, player_get_state
* @passcase				If it gets the media content information successfully
* @failcase				If it does not gets the media content information successfully
* @precondition			The player state must be one of: PLAYER_STATE_PLAYING, or PLAYER_STATE_PAUSED
* @postcondition		NA
*/
int ITc_player_get_content_info_p(void)
{
	START_TEST;

	char *pszValue = NULL;
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
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_get_content_info(g_player, PLAYER_CONTENT_INFO_ALBUM, &pszValue);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_content_info", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player);FREE_MEMORY(pszValue));
	if(pszValue == NULL)
	{
		FPRINTF("[Line : %d][%s] Output value is not valid", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_get_content_info(g_player, PLAYER_CONTENT_INFO_ARTIST, &pszValue);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_content_info", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player);FREE_MEMORY(pszValue));
	if(pszValue == NULL)
	{
		FPRINTF("[Line : %d][%s] Output value is not valid", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_get_content_info(g_player, PLAYER_CONTENT_INFO_AUTHOR, &pszValue);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_content_info", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player);FREE_MEMORY(pszValue));
	if(pszValue == NULL)
	{
		FPRINTF("[Line : %d][%s] Output value is not valid", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_get_content_info(g_player, PLAYER_CONTENT_INFO_GENRE, &pszValue);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_content_info", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player);FREE_MEMORY(pszValue));
	if(pszValue == NULL)
	{
		FPRINTF("[Line : %d][%s] Output value is not valid", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_get_content_info(g_player, PLAYER_CONTENT_INFO_TITLE, &pszValue);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_content_info", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player);FREE_MEMORY(pszValue));
	if(pszValue == NULL)
	{
		FPRINTF("[Line : %d][%s] Output value is not valid", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_get_content_info(g_player, PLAYER_CONTENT_INFO_YEAR, &pszValue);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_content_info", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player);FREE_MEMORY(pszValue));
	if(pszValue == NULL)
	{
		FPRINTF("[Line : %d][%s] Output value is not valid", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_stop(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet), player_unprepare(g_player);FREE_MEMORY(pszValue));

	nRet = player_unprepare(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet),FREE_MEMORY(pszValue));

	FREE_MEMORY(pszValue);

	return 0;
}

//& purpose: Gets the total running time of the associated media
//& type : auto
/**
* @testcase				ITc_player_get_duration_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Gets the total running time of the associated media
* @scenario				Initialize player handle\n
*						start player\n
*						get player duration\n
*						check the result\n
*						destroy the handler
* @apicovered			player_start, player_get_duration, player_unprepare
* @passcase				When it can get player duration
* @failcase				When it can not get player duration
* @precondition			The player state must be PLAYER_STATE_PLAYING
* @postcondition		N/A
*/
int ITc_player_get_duration_p(void)
{
	START_TEST;

	int nDuration = -1;
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

	nRet = player_get_duration(g_player, &nDuration);
	FPRINTF("[Line : %d][%s] Media file duration = %d",__LINE__, API_NAMESPACE, nDuration);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_duration", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	nRet = player_stop(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}

//& purpose: To Sets/Gets streaming buffering time
//& type : auto
/**
* @testcase				ITc_media_player_set_get_streaming_buffering_time_p
* @author				SRID(priya.kohli)
* @reviewer				SRID(maneesha.k)
* @type					auto
* @since_tizen			4.0
* @description			Sets/Gets streaming buffering time
* @scenario				Sets/Gets streaming buffering time
* @apicovered			player_set_streaming_buffering_time, player_get_streaming_buffering_time
* @passcase				If get value is same as set value & both APIs return PLAYER_ERROR_NONE
* @failcase				If get value is not same as set value or either APIs return other than PLAYER_ERROR_NONE
* @precondition			Player State should be PLAYER_STATE_IDLE
* @postcondition		NA
*/
int ITc_media_player_set_get_streaming_buffering_time_p(void)
{
	START_TEST;
	int nSetBtime = 50000;
	int nSetRbtime = 100000;
	int nGetBtime = 0;
	int nGetRbtime = 0;
	player_state_e state;

	char pPath[PATH_LEN] = {0};
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_VIDEO, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player); player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_IDLE)
	{
		FPRINTF("[Line: %d][%s] Could not create player", __LINE__, API_NAMESPACE);
		nRet = player_stop(g_player);
		PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet));
		nRet = player_unprepare(g_player);
		PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
		return 1;
	}

	nRet = player_set_uri(g_player, pPath);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	nRet = player_set_streaming_buffering_time(g_player, nSetBtime, nSetRbtime);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_streaming_buffering_time", PlayerGetError(nRet), player_stop(g_player); player_unprepare(g_player));

	nRet = player_get_streaming_buffering_time(g_player, &nGetBtime, &nGetRbtime);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_streaming_buffering_time", PlayerGetError(nRet), player_stop(g_player); player_unprepare(g_player));

	if(nSetBtime != nGetBtime)
	{
		FPRINTF("[Line : %d][%s] Value Mismatch nSetBtime = %d	nGetBtime = %d\\n", __LINE__, API_NAMESPACE,nSetBtime,nGetBtime);
		nRet = player_stop(g_player);
		PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet));
		nRet = player_unprepare(g_player);
		PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
		return 1;
	}

	if(nSetRbtime != nGetRbtime)
	{
		FPRINTF("[Line : %d][%s] Value Mismatch nSetRbtime = %d	nGetRbtime = %d\\n", __LINE__, API_NAMESPACE,nSetRbtime,nGetRbtime);
		nRet = player_stop(g_player);
		PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet));
		nRet = player_unprepare(g_player);
		PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
		return 1;
	}

	nRet = player_stop(g_player);
	PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet));

	nRet = player_unprepare(g_player);
	PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}
