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

/**
* @function			ITs_player_startup
* @description		Called before each test, created player handle
* @parameter		NA
* @return			NA
*/
void ITs_player_audio_effect_startup(void)
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
#endif //For Mobile or Wearable

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
void ITs_player_audio_effect_cleanup(void)
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


/** @addtogroup itc-player-testcases
*  @brief		Integration testcases for module player
*  @ingroup		itc-player
*  @{
*/


//& purpose: Checks whether the custom equalizer effect is available or not
//& type: auto
/**
* @testcase				ITc_player_audio_effect_equalizer_is_available_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Checks whether the custom equalizer effect is available or not
* @scenario				call player_audio_effect_equalizer_is_available\n
*						check results\n
*						destroy the handler
* @apicovered			player_audio_effect_equalizer_is_available
* @passcase				When specified audio effect is available
* @failcase				When specified audio effect is not available
* @precondition			The player state should be PLAYER_STATE_IDLE
* @postcondition		N/A
*/
int ITc_player_audio_effect_equalizer_is_available_p(void)
{
	START_TEST;

	bool bAvailable;
	int nRet = player_audio_effect_equalizer_is_available(g_player, &bAvailable);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_effect_equalizer_is_available", PlayerGetError(nRet));

	if ( bAvailable != true )
	{
		FPRINTF("[Line : %d][%s] player_audio_effect_equalizer_is_available false", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets the bands number of equalizer
//& type: auto
/**
* @testcase				ITc_player_audio_effect_get_equalizer_bands_count_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Gets the bands number of equalizer
* @scenario				check player_audio_effect_equalizer_is_available\n
*						player_audio_effect_get_equalizer_bands_count\n
*						check results\n
*						destroy the handler
* @apicovered			player_audio_effect_equalizer_is_available, player_audio_effect_get_equalizer_bands_count
* @passcase				player_audio_effect_get_equalizer_bands_count is Passed
* @failcase				player_audio_effect_get_equalizer_bands_count is Failed
* @precondition			The player state should be PLAYER_STATE_IDLE
* @postcondition		N/A
*/
int ITc_player_audio_effect_get_equalizer_bands_count_p(void)
{
	START_TEST;

	bool bAvailable;
	int nBandCount = -1;

	int nRet = player_audio_effect_equalizer_is_available(g_player, &bAvailable);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_effect_equalizer_is_available", PlayerGetError(nRet));

	if ( bAvailable != true )
	{
		FPRINTF("[Line : %d][%s] player_audio_effect_equalizer_is_available false", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_audio_effect_get_equalizer_bands_count(g_player, &nBandCount);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_effect_get_equalizer_bands_count", PlayerGetError(nRet));

	if ( nBandCount < 0 )
	{
		FPRINTF("[Line : %d][%s] player_audio_effect_get_equalizer_bands_count return wrong value", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets the band frequency range of equalizer
//& type: auto
/**
* @testcase				ITc_player_audio_effect_get_equalizer_band_frequency_range_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Gets the band frequency range of equalizer
* @scenario				check player_audio_effect_equalizer_is_available\n
*						player_audio_effect_get_equalizer_band_frequency_range\n
*						check results\n
*						destroy the handler
* @apicovered			player_audio_effect_equalizer_is_available, player_audio_effect_get_equalizer_band_frequency_range
* @passcase				player_audio_effect_get_equalizer_band_frequency_range is Passed
* @failcase				player_audio_effect_get_equalizer_band_frequency_range is Failed
* @precondition			The player state should be PLAYER_STATE_IDLE
* @postcondition		N/A
*/
int ITc_player_audio_effect_get_equalizer_band_frequency_range_p(void)
{
	START_TEST;

	bool bAvailable;
	int nRange = -1;
	int index = 0;

	int nRet = player_audio_effect_equalizer_is_available(g_player, &bAvailable);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_effect_equalizer_is_available", PlayerGetError(nRet));

	if ( bAvailable != true )
	{
		FPRINTF("[Line : %d][%s] player_audio_effect_equalizer_is_available false", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_audio_effect_get_equalizer_band_frequency_range(g_player, index, &nRange);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_effect_get_equalizer_band_frequency_range", PlayerGetError(nRet));

	if ( nRange < 0 )
	{
		FPRINTF("[Line : %d][%s] player_audio_effect_get_equalizer_band_frequency_range return wrong value", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets the band frequency of equalizer
//& type: auto
/**
* @testcase				ITc_player_audio_effect_get_equalizer_band_frequency_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Gets the band frequency of equalizer
* @scenario				check player_audio_effect_equalizer_is_available\n
*						player_audio_effect_get_equalizer_band_frequency\n
*						check results\n
*						destroy the handler
* @apicovered			player_audio_effect_equalizer_is_available, player_audio_effect_get_equalizer_band_frequency
* @passcase				player_audio_effect_get_equalizer_band_frequency is Passed
* @failcase				player_audio_effect_get_equalizer_band_frequency is Failed
* @precondition			The player state should be PLAYER_STATE_IDLE
* @postcondition		N/A
*/
int ITc_player_audio_effect_get_equalizer_band_frequency_p(void)
{
	START_TEST;

	bool bAvailable;
	int nFrequency = -1;
	int index = 0;

	int nRet = player_audio_effect_equalizer_is_available(g_player, &bAvailable);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_effect_equalizer_is_available", PlayerGetError(nRet));

	if ( bAvailable != true )
	{
		FPRINTF("[Line : %d][%s] player_audio_effect_equalizer_is_available false", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_audio_effect_get_equalizer_band_frequency(g_player, index, &nFrequency);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_effect_get_equalizer_band_frequency", PlayerGetError(nRet));

	if ( nFrequency < 0 )
	{
		FPRINTF("[Line : %d][%s] player_audio_effect_get_equalizer_band_frequency return wrong value", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets the valid band level range of equalizer
//& type: auto
/**
* @testcase				ITc_player_audio_effect_get_equalizer_level_range_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Gets the valid band level range of equalizer
* @scenario				check player_audio_effect_equalizer_is_available\n
*						player_audio_effect_get_equalizer_level_range\n
*						check results\n
*						destroy the handler
* @apicovered			player_audio_effect_equalizer_is_available, player_audio_effect_get_equalizer_level_range
* @passcase				player_audio_effect_get_equalizer_level_range is Passed
* @failcase				player_audio_effect_get_equalizer_level_range is Failed
* @precondition			The player state should be PLAYER_STATE_IDLE
* @postcondition		N/A
*/
int ITc_player_audio_effect_get_equalizer_level_range_p(void)
{
	START_TEST;

	bool bAvailable;
	int nMin, nMax;

	int nRet = player_audio_effect_equalizer_is_available(g_player, &bAvailable);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_effect_equalizer_is_available", PlayerGetError(nRet));

	if ( bAvailable != true )
	{
		FPRINTF("[Line : %d][%s] player_audio_effect_equalizer_is_available false", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_audio_effect_get_equalizer_level_range(g_player, &nMin, &nMax);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_effect_get_equalizer_level_range", PlayerGetError(nRet));

	return 0;
}

//& purpose: Set and get the gain set for the given equalizer band
//& type: auto
/**
* @testcase				ITc_player_audio_effect_set_get_equalizer_band_level_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Set and get the gain set for the given equalizer band
* @scenario				check player_audio_effect_equalizer_is_available\n
*						player_audio_effect_get_equalizer_level_range\n
*						player_audio_effect_set_equalizer_band_level\n
*						player_audio_effect_get_equalizer_band_level\n
*						check results
*						destroy the handler
* @apicovered			player_audio_effect_equalizer_is_available, player_audio_effect_get_equalizer_level_range,\n
						player_audio_effect_set_equalizer_band_level, player_audio_effect_get_equalizer_band_level
* @passcase				player_audio_effect_set_equalizer_band_level and player_audio_effect_get_equalizer_band_level are Passed
* @failcase				player_audio_effect_set_equalizer_band_level or player_audio_effect_get_equalizer_band_level are Failed
* @precondition			The player state should be PLAYER_STATE_IDLE
* @postcondition		N/A
*/
int ITc_player_audio_effect_set_get_equalizer_band_level_p(void)
{
	START_TEST;

	bool bAvailable;
	int nMin, nMax;
	int index = 0;
	int nSetLevel = -1;
	int nGetLevel = -1;

	int nRet = player_audio_effect_equalizer_is_available(g_player, &bAvailable);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_effect_equalizer_is_available", PlayerGetError(nRet));

	if ( bAvailable != true )
	{
		FPRINTF("[Line : %d][%s] player_audio_effect_equalizer_is_available false", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_audio_effect_get_equalizer_level_range(g_player, &nMin, &nMax);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_effect_get_equalizer_level_range", PlayerGetError(nRet));

	usleep(2000);
	nSetLevel = (nMin + nMax) / 2;
	usleep(2000);

	nRet = player_audio_effect_set_equalizer_band_level(g_player, index, nSetLevel);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_effect_set_equalizer_band_level", PlayerGetError(nRet));

	usleep(2000);

	nRet = player_audio_effect_get_equalizer_band_level(g_player, index, &nGetLevel);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_effect_get_equalizer_band_level", PlayerGetError(nRet));

	if ( nGetLevel != nSetLevel )
	{
		FPRINTF("[Line : %d][%s] player_audio_effect_set_get_equalizer_band_level mismatched", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Sets the all bands of equalizer
//& type: auto
/**
* @testcase				ITc_player_audio_effect_set_equalizer_all_bands_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Sets the all bands of equalizer
* @scenario				check player_audio_effect_equalizer_is_available\n
*						player_audio_effect_get_equalizer_bands_count\n
*						player_audio_effect_get_equalizer_level_range\n
*						player_audio_effect_set_equalizer_all_bands\n
*						check results\n
*						destroy the handler
* @apicovered			player_audio_effect_equalizer_is_available, player_audio_effect_get_equalizer_bands_count,\n
*						player_audio_effect_get_equalizer_level_range, player_audio_effect_set_equalizer_all_bands
* @passcase				player_audio_effect_set_equalizer_all_bands is Passed
* @failcase				player_audio_effect_set_equalizer_all_bands is Failed
* @precondition			The player state should be PLAYER_STATE_IDLE
* @postcondition		N/A
*/
int ITc_player_audio_effect_set_equalizer_all_bands_p(void)
{
	START_TEST;

	bool bAvailable;
	int nBandCount = -1;
	int nMin, nMax;
	int i;

	int nRet = player_audio_effect_equalizer_is_available(g_player, &bAvailable);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_effect_equalizer_is_available", PlayerGetError(nRet));

	if ( bAvailable != true )
	{
		FPRINTF("[Line : %d][%s] player_audio_effect_equalizer_is_available false", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_audio_effect_get_equalizer_bands_count(g_player, &nBandCount);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_effect_get_equalizer_bands_count", PlayerGetError(nRet));

	if ( nBandCount < 0 )
	{
		FPRINTF("[Line : %d][%s] player_audio_effect_get_equalizer_bands_count return wrong value", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_audio_effect_get_equalizer_level_range(g_player, &nMin, &nMax);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_effect_get_equalizer_level_range", PlayerGetError(nRet));

	int *nBandLevels = (int*)malloc(sizeof(int) * nBandCount);
	if(NULL == nBandLevels)
	{
		FPRINTF("[Line : %d][%s] memory allocation of  nBandLevels failed", __LINE__, API_NAMESPACE);
		return 1;
	}
	for ( i=0; i<nBandCount; i++ )
	{
		nBandLevels[i] = (nMin + nMax) / 2;
	}

	nRet = player_audio_effect_set_equalizer_all_bands(g_player, nBandLevels, nBandCount);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_audio_effect_set_equalizer_all_bands", PlayerGetError(nRet),FREE_MEMORY(nBandLevels));

	FREE_MEMORY(nBandLevels);

	return 0;
}

//& purpose: Clears the equalizer effect
//& type: auto
/**
* @testcase				ITc_player_audio_effect_equalizer_clear_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Clears the equalizer effect
* @scenario				check player_audio_effect_equalizer_is_available\n
*						player_audio_effect_get_equalizer_bands_count\n
*						player_audio_effect_get_equalizer_level_range\n
*						player_audio_effect_set_equalizer_all_bands\n
*						player_audio_effect_equalizer_clear\n
*						check results\n
*						destroy the handler
* @apicovered			player_audio_effect_equalizer_is_available, player_audio_effect_get_equalizer_bands_count,\n
*						player_audio_effect_get_equalizer_level_range, player_audio_effect_set_equalizer_all_bands,\n
*						player_audio_effect_equalizer_clear
* @passcase				player_audio_effect_equalizer_clear is Passed
* @failcase				player_audio_effect_equalizer_clear is Failed
* @precondition			The player state should be PLAYER_STATE_IDLE
* @postcondition		N/A
*/
int ITc_player_audio_effect_equalizer_clear_p(void)
{
	START_TEST;

	bool bAvailable;
	int nBandCount = -1;
	int nMin, nMax;
	int i;

	int nRet = player_audio_effect_equalizer_is_available(g_player, &bAvailable);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_effect_equalizer_is_available", PlayerGetError(nRet));

	if ( bAvailable != true )
	{
		FPRINTF("[Line : %d][%s] player_audio_effect_equalizer_is_available false", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_audio_effect_get_equalizer_bands_count(g_player, &nBandCount);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_effect_get_equalizer_bands_count", PlayerGetError(nRet));

	if ( nBandCount < 0 )
	{
		FPRINTF("[Line : %d][%s] player_audio_effect_get_equalizer_bands_count return wrong value", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_audio_effect_get_equalizer_level_range(g_player, &nMin, &nMax);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_audio_effect_get_equalizer_level_range", PlayerGetError(nRet));

	int *nBandLevels = (int*)malloc(sizeof(int) * nBandCount);
	if(NULL == nBandLevels)
	{
		FPRINTF("[Line : %d][%s] memory allocation of  nBandLevels failed", __LINE__, API_NAMESPACE);
		return 1;
	}
	for ( i=0; i<nBandCount; i++ )
	{
		nBandLevels[i] = (nMin + nMax) / 2;
	}

	nRet = player_audio_effect_set_equalizer_all_bands(g_player, nBandLevels, nBandCount);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_audio_effect_set_equalizer_all_bands", PlayerGetError(nRet),FREE_MEMORY(nBandLevels));

	nRet = player_audio_effect_equalizer_clear(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_audio_effect_equalizer_clear", PlayerGetError(nRet),FREE_MEMORY(nBandLevels));

	FREE_MEMORY(nBandLevels);

	return 0;
}

//& purpose: Set and get the player audio codec type
//& type: auto
/**
* @testcase				ITc_player_audio_set_get_audio_codec_type_p
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @since_tizen				5.5
* @description				Set and get the player audio codec type
* @scenario				check player_set_audio_codec_type, player_get_audio_codec_type API
* @apicovered				player_set_audio_codec_type, player_get_audio_codec_type
* @passcase				player_set_audio_codec_type, player_get_audio_codec_type and Precondition APi's are Passed
* @failcase				player_set_audio_codec_type, player_get_audio_codec_type and Precondition APi's are Failed
* @precondition				The player state should be PLAYER_STATE_IDLE
* @postcondition			N/A
*/
int ITc_player_audio_set_get_audio_codec_type_p(void)
{
	START_TEST;
	int nRet = PLAYER_ERROR_NONE;
	player_state_e ePlayerState = PLAYER_STATE_NONE;
	player_codec_type_e ePlayerCodecType = -1;

	nRet = player_get_state(g_player, &ePlayerState);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet));

	if (ePlayerState != PLAYER_STATE_IDLE)
	{
		FPRINTF("[Line : %d][%s] Player state is invalid ", __LINE__, API_NAMESPACE);
		return 1;
	}
	nRet = player_set_audio_codec_type(g_player, PLAYER_CODEC_TYPE_SW);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_audio_codec_type", PlayerGetError(nRet));

	nRet = player_get_audio_codec_type(g_player, &ePlayerCodecType);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_audio_codec_type", PlayerGetError(nRet));
	PRINT_RESULT(ePlayerCodecType, PLAYER_CODEC_TYPE_SW, "codec get and set value is not same", PlayerGetError(nRet));

	return 0;
}
/** @} */
/** @} */
