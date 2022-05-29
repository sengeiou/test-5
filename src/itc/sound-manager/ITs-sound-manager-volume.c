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
#include "ITs-sound-manager-common.h"
/** @addtogroup itc-sound-manager
*  @ingroup itc
*  @{
*/
//& set: SoundManager

static GMainLoop *g_pMainLoop;
static bool g_bCallbackResult ;
static bool g_bSupportedFeatureMicrophone ;

/**
* @function 		ITs_sound_manager_device_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_sound_manager_volume_startup(void)
{
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Sound_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bCallbackResult = false;
	g_bSupportedFeatureMicrophone = TCTCheckSystemInfoFeatureSupported(FEATURE_MICROPHONE, API_NAMESPACE);

	return;
}

/**
* @function 		ITs_sound_manager_device_cleanup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_sound_manager_volume_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Sound_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		test_sound_manager_volume_changed_cb
* @description	 	callback function for volume change
* @parameter		type : sound type, volume: volume, user_data : user data
* @return 			NA
*/
static void test_sound_manager_volume_changed_cb(sound_type_e type, unsigned int volume, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside callback \"test_sound_manager_volume_changed_cb\"\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
	FPRINTF("[Line : %d][%s] Outside from callback \"test_sound_manager_volume_changed_cb\"\\n", __LINE__, API_NAMESPACE);
}

//& purpose: To check get max volume level supported for a particular sound type
//& type : auto
/**
* @testcase 			ITc_sound_manager_get_max_volume_p
* @since_tizen 			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check get max volume level supported for a particular sound type
* @scenario				Call API to get maximum volume level
* @apicovered			sound_manager_get_max_volume
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_get_max_volume_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = -1, nEnumLoopCount = 0, nResultSoundLevel = -1;

	sound_type_e eSoundType;
	int arrSoundTypeValues[] = {
		SOUND_TYPE_SYSTEM,
		SOUND_TYPE_NOTIFICATION,
		SOUND_TYPE_ALARM,
		SOUND_TYPE_MEDIA,
		SOUND_TYPE_RINGTONE,
		SOUND_TYPE_CALL,
		SOUND_TYPE_VOIP,
		SOUND_TYPE_VOICE
	};
	int nSoundTypeIteration = sizeof(arrSoundTypeValues) /sizeof(arrSoundTypeValues[0]);

	for ( nEnumLoopCount = 0;nEnumLoopCount < nSoundTypeIteration;nEnumLoopCount++ )
	{
		eSoundType = arrSoundTypeValues[nEnumLoopCount];

		nRet = sound_manager_get_max_volume(eSoundType, &nResultSoundLevel);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_max_volume", SoundManagerGetError(nRet));

		if ( nResultSoundLevel < 0 )
		{
			FPRINTF("[Line : %d][%s] sound_manager_get_max_volume failed, invalid output parameter for sound level = %s\\n", __LINE__, API_NAMESPACE, SoundManagerGetSoundType(eSoundType));
			return 1;
		}
		nResultSoundLevel = -1;
	}
	return 0;
}

//& purpose: To check set/get volume level for a particular sound type
//& type : auto
/**
* @testcase 			ITc_sound_manager_set_get_volume_p
* @since_tizen 			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check set/get volume level for a particular sound type
* @scenario				Call API to set volume level and verify\n
* 						Call API to get volume level and verify\n
* 						check set volume level and get volume level
* @apicovered			sound_manager_set_volume, sound_manager_get_volume
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* 						If both volume level is equal
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* 						If both volume level is not equal
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_set_get_volume_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = -1, nEnumLoopCount = 0;
	int nSetSoundLevel = 1;
	int nFindSoundLevel = 0;
	sound_type_e eSoundType;
	int arrSoundTypeValues[] = {
		SOUND_TYPE_SYSTEM,
		SOUND_TYPE_NOTIFICATION,
		SOUND_TYPE_ALARM,
		SOUND_TYPE_MEDIA,
		SOUND_TYPE_RINGTONE,
		SOUND_TYPE_CALL,
		SOUND_TYPE_VOIP,
		SOUND_TYPE_VOICE
	};
	int nSoundTypeIteration = sizeof(arrSoundTypeValues) /sizeof(arrSoundTypeValues[0]);

	for ( nEnumLoopCount = 0;nEnumLoopCount < nSoundTypeIteration;nEnumLoopCount++ )
	{
		eSoundType = arrSoundTypeValues[nEnumLoopCount];
		nRet = sound_manager_set_volume(eSoundType, (nSetSoundLevel));
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_set_volume", SoundManagerGetError(nRet));

		nRet = sound_manager_get_volume(eSoundType, &nFindSoundLevel);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_volume", SoundManagerGetError(nRet));

		PRINT_RESULT(nFindSoundLevel, nSetSoundLevel, "sound_manager_get_volume", "Output parameter doesn't match the set value");
		nFindSoundLevel = 0;
	}
	return 0;
}

//& purpose: To check get current sound type
//& type: auto
/**
* @deprecated                   deprecated sound_manager_set_current_sound_type api since 3.0
* @testcase 			ITc_sound_manager_set_unset_current_sound_type_p
* @since_tizen 			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check get the type of the sound being currently played
* @scenario				Get the type of the sound being currently played and verify\n
* @apicovered			sound_manager_get_current_sound_type
* @passcase				When API return SOUND_MANAGER_ERROR_NONE or SOUND_MANAGER_ERROR_NO_PLAYING_SOUND
* @failcase				When API not return @passcase
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_get_current_sound_type_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = -1;

	sound_type_e e_find_sound_type = -1;
	nRet = sound_manager_get_current_sound_type(&e_find_sound_type);
	if ( nRet != SOUND_MANAGER_ERROR_NONE && nRet != SOUND_MANAGER_ERROR_NO_PLAYING_SOUND )
	{
		FPRINTF("[Line : %d][%s] sound_manager_get_current_sound_type failed, error returned = %s\\n", __LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		return 1;
	}

	return 0;
}

//& purpose: To check add/remove volume change callback
//& type : auto
/**
* @testcase 			ITc_sound_manager_add_remove_volume_changed_cb_p
* @since_tizen 			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			To check add/remove volume change callback
* @scenario				Call API to register callback and verify\n
* 						check response from call back\n
* 						Call API to unregister callback and verify\n
* 						check response from call back
* @apicovered			sound_manager_get_volume, sound_manager_get_max_volume, sound_manager_set_volume, sound_manager_add_volume_changed_cb, sound_manager_remove_volume_changed_cb
* @passcase				When APIs return SOUND_MANAGER_ERROR_NONE
* 						When response from callback on mute event
* @failcase				When APIs not return SOUND_MANAGER_ERROR_NONE
* 						When no response from callback
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_add_remove_volume_changed_cb_p(void)
{
	START_TEST;
	int nRet = -1;
	int nTtimeoutId = 0;
	g_pMainLoop = g_main_loop_new(NULL, false);

	sound_type_e eSoundType = SOUND_TYPE_NOTIFICATION;
	int nMaxSoundLevel = 0;
	int nFindSoundLevel = 0;
	int nGetId;

	nRet = sound_manager_get_max_volume(eSoundType, &nMaxSoundLevel);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_max_volume", SoundManagerGetError(nRet));

	nRet = sound_manager_get_volume(eSoundType, &nFindSoundLevel);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_volume", SoundManagerGetError(nRet));

	//Check to set less than max value
	if ( (nMaxSoundLevel-2) < nFindSoundLevel )
	{
		nFindSoundLevel = 1;
	}

	nRet = sound_manager_add_volume_changed_cb(test_sound_manager_volume_changed_cb, NULL, &nGetId);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_add_volume_changed_cb", SoundManagerGetError(nRet));

	nRet = sound_manager_set_volume(eSoundType, nFindSoundLevel++);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_set_volume", SoundManagerGetError(nRet), sound_manager_remove_volume_changed_cb(nGetId));

	nTtimeoutId = g_timeout_add(2000, TimeoutFunction, g_pMainLoop);
	g_main_loop_run(g_pMainLoop);
	g_source_remove(nTtimeoutId);
	if ( g_bCallbackResult == false )
	{
		FPRINTF("[Line : %d][%s] After sound_manager_add_volume_changed_cb, No response from callback\\n", __LINE__, API_NAMESPACE);
		sound_manager_remove_volume_changed_cb(nGetId);
		return 1;
	}
	
	nRet = sound_manager_remove_volume_changed_cb(nGetId);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_remove_volume_changed_cb", SoundManagerGetError(nRet));

	g_bCallbackResult = false;
	nRet = sound_manager_set_volume(eSoundType, nFindSoundLevel);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_set_volume", SoundManagerGetError(nRet));

	nTtimeoutId = g_timeout_add(2000, TimeoutFunction, g_pMainLoop);
	g_main_loop_run(g_pMainLoop);
	g_source_remove(nTtimeoutId);
	if ( g_bCallbackResult == true )
	{
		FPRINTF("[Line : %d][%s] After sound_manager_remove_volume_changed_cb,Getting response from callback\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}
