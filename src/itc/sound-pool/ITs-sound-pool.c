//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
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
#include "ITs-sound-pool-common.h"

//& set: SoundPool

/**
* @function			SoundPoolStreamStateChanged
* @description		callback for Sound Pool Stream State Changed
* @parameter		The sound pool handle
* @parameter		Unique stream identifier
* @parameter		Previous stream state
* @parameter		Current stream state
* @parameter		user data passed to the callback
* @return			void
*/
void SoundPoolStreamStateChanged(sound_pool_h pool, unsigned id, sound_pool_stream_state_e prev_state, sound_pool_stream_state_e cur_state, void *user_data)
{
	if (DEBUG)
	{
		FPRINTF("[Line : %d][%s] Callback invoked\\n", __LINE__, API_NAMESPACE);
	}

	g_bCallbackCalled = true;
	QUIT_GMAIN_LOOP;
}

/**
* @function			SoundPoolTimeout
* @description		Called if some callback is not invoked for a particular SoundPoolTimeout
* @parameter		gpointer data
* @return			gboolean
*/
gboolean SoundPoolTimeout(gpointer data)
{
	FPRINTF("[Line : %d][%s] Callback Time-out\\n", __LINE__, API_NAMESPACE);
	QUIT_GMAIN_LOOP;
	return false;
}
/**
 * @function		ITs_sound_pool_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void ITs_sound_pool_startup(void)
{
	struct stat stBuff;
	g_bSoundPoolInit = false;
	g_bSoundPoolCreate = false;
	g_bSoundPoolLoaded = false;
	g_bSoundPoolActivated = false;
	g_pFile_path = NULL;

	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	char pszValue[MAX_PATH] = {0,};
	bool bRet = GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE);

	if(true == bRet)
	{
		unsigned int nullCharLen = 1;
		unsigned int size_of_path = strlen(pszValue) + strlen(test_file) + strlen("/res/res/") + nullCharLen;
		g_pFile_path = (char*)malloc(size_of_path);
		if( g_pFile_path == NULL)
                {
                        FPRINTF("[Line : %d][%s] Memory Allocation failed for g_pFile_path \\n", __LINE__, API_NAMESPACE);
                        return;
                }
		snprintf(g_pFile_path, size_of_path, "%s/res/res/%s", pszValue, test_file);
	}
	else
	{
		FPRINTF("[Line: %d][%s] GetValueFromConfigFile returned false\\n", __LINE__, API_NAMESPACE);
		return;
	}

	int nRet = sound_pool_create(&g_hPool);

	if(nRet != SOUND_POOL_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] Unable to create Sound pool handle, error returned = %s\\n", __LINE__, API_NAMESPACE, SoundPoolGetError(nRet));
		return;
	}

	if(g_hPool == NULL)
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, "sound_pool_create");
		return;
	}

	g_bSoundPoolCreate = true;

	nRet = sound_pool_load_source_from_file(g_hPool, g_pFile_path, DEFAULT_SAMPLE_TAG);

	if(nRet != SOUND_POOL_ERROR_NONE)
	{
		 FPRINTF("[Line : %d][%s] Unable to load Sound pool, error returned = %s\\n", __LINE__, API_NAMESPACE, SoundPoolGetError(nRet));
		 return;
	}

	g_bSoundPoolLoaded = true;

	nRet = sound_pool_activate(g_hPool);

	if(nRet != SOUND_POOL_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] Unable to activate Sound pool, error returned = %s\\n", __LINE__, API_NAMESPACE, SoundPoolGetError(nRet));
		return;
	}

	sound_pool_state_e state = SOUND_POOL_STATE_INACTIVE;
	nRet = sound_pool_get_state(g_hPool, &state);

	if(nRet != SOUND_POOL_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] Unable to get Sound pool state, error returned = %s\\n", __LINE__, API_NAMESPACE, SoundPoolGetError(nRet));
		return;
	}

	if(state != SOUND_POOL_STATE_ACTIVE)
	{
		FPRINTF("[Line : %d][%s] Sound pool State is not active after sound_pool_activate\\n", __LINE__, API_NAMESPACE);
		return;
	}

	g_bSoundPoolActivated = true;
	g_bSoundPoolInit = true;
	return;
}


/**
 * @function		ITs_sound_pool_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void ITs_sound_pool_cleanup(void)
{
	int nRet = SOUND_POOL_ERROR_NONE;

	if(true == g_bSoundPoolActivated)
	{
		nRet = sound_pool_deactivate(g_hPool);
		PRINT_RESULT_NORETURN(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_deactivate", SoundPoolGetError(nRet));
	}

	if(true == g_bSoundPoolLoaded)
	{
		nRet = sound_pool_unload_source(g_hPool, DEFAULT_SAMPLE_TAG);
		PRINT_RESULT_NORETURN(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_unload_source", SoundPoolGetError(nRet));
	}

	if(true == g_bSoundPoolCreate)
	{
		nRet = sound_pool_destroy(g_hPool);
		PRINT_RESULT_NORETURN(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_destroy", SoundPoolGetError(nRet));
	}

	if(NULL != g_pFile_path)
	{
		free(g_pFile_path);
	}
	return;
}

/** @addtogroup itc-sound-pool
*  @ingroup itc
*  @{
*/

//& purpose Creates and Destroys a sound pool instance that can be used for sound sources loading/unloading
//& type: auto
/**
* @testcase				ITs_sound_pool_create_destroy_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Creates and Destroys a sound pool instance
* @scenario				Creates and Destroys a sound pool instance\n
* @apicovered			sound_pool_create, sound_pool_destroy
* @passcase				If Creation and Destruction successfully
* @failcase				If fails to Create and/or Destroy
* @precondition			NA
* @postcondition		NA
*/
int ITs_sound_pool_create_destroy_p(void)
{
	START_TEST;

	int nRet = SOUND_POOL_ERROR_NONE;
	sound_pool_h hTestPool[MAX_POOLS-1] = {NULL}; // 1 sound_pool_h is created in startup
	int maxPoolCount = MAX_POOLS-1;
	int poolCount = 0;
	bool bCreateDestroyFailed = false;

	for (poolCount = 0; poolCount < maxPoolCount; poolCount++)
	{
		nRet = sound_pool_create(&hTestPool[poolCount]);
		PRINT_RESULT_NORETURN(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_create", SoundPoolGetError(nRet));

		if(hTestPool[poolCount] == NULL)
		{
			bCreateDestroyFailed = true;
			break;
		}
	}

	// Destroy
	for (poolCount = 0; poolCount < maxPoolCount && hTestPool[poolCount] != NULL; poolCount++)
	{
		nRet = sound_pool_destroy(hTestPool[poolCount]);
		PRINT_RESULT_NORETURN(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_destroy", SoundPoolGetError(nRet));

		if(nRet != SOUND_POOL_ERROR_NONE)
		{
			bCreateDestroyFailed = true;
		}

		hTestPool[poolCount] = NULL;
	}

	if(bCreateDestroyFailed == true)
	{
		return 1;
	}

	return 0;
}

//& purpose Loads and Unloads sound source data from a file to the pool
//& type: auto
/**
* @testcase				ITs_sound_pool_load_unload_source_from_file_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Loads and Unloads sound source data from a file
* @scenario				Loads and Unloads sound source data from a file\n
* @apicovered			sound_pool_load_source_from_file, sound_pool_unload_source
* @passcase				If Load and Unload successfully
* @failcase				If fails to Load and/or Unload
* @precondition			NA
* @postcondition		NA
*/
int ITs_sound_pool_load_unload_source_from_file_p(void)
{
	START_TEST;

	int nRet = 0;

	if(g_bSoundPoolLoaded == true)
	{
		nRet = sound_pool_unload_source(g_hPool, DEFAULT_SAMPLE_TAG);
		PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_unload_source", SoundPoolGetError(nRet));
		g_bSoundPoolLoaded = false;
	}

	nRet = sound_pool_load_source_from_file(g_hPool, g_pFile_path, DEFAULT_SAMPLE_TAG);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_load_source_from_file", SoundPoolGetError(nRet));

	nRet = sound_pool_unload_source(g_hPool, DEFAULT_SAMPLE_TAG);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_unload_source", SoundPoolGetError(nRet));

	nRet = sound_pool_load_source_from_file(g_hPool, g_pFile_path, DEFAULT_SAMPLE_TAG);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_load_source_from_file", SoundPoolGetError(nRet));
	g_bSoundPoolLoaded = true;

	return 0;
}

//& purpose Plays and Stops a source by a tag
//& type: auto
/**
* @testcase				ITs_sound_pool_stream_play_stop_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Play and Stop
* @scenario				Play and Stop\n
* @apicovered			sound_pool_stream_play, sound_pool_stream_resume
* @passcase				If Play and Stop successfull
* @failcase				If fails to Play and/or Stop
* @precondition			sound pool handle should be created and source should be loaded
* @postcondition		NA
*/
int ITs_sound_pool_stream_play_stop_p(void)
{
	START_TEST;

	int nRet = SOUND_POOL_ERROR_NONE;
	unsigned int loop = 2;
	float volume = 0.5;
	unsigned int priority = DEFAULT_PRIORITY;
	sound_pool_stream_priority_policy_e priority_policy = SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED;
	sound_pool_stream_state_changed_cb callback = NULL;
	void *data = NULL;
	unsigned int id = 0;
	sound_pool_stream_priority_policy_e priority_type[] = {SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED, SOUND_POOL_STREAM_PRIORITY_POLICY_MUTE};
	int enum_size = sizeof(priority_type) / sizeof(priority_type[0]);
	int enum_counter = 0;
	sound_pool_stream_state_e state = SOUND_POOL_STREAM_STATE_NONE;

	for ( enum_counter=0; enum_counter < enum_size; enum_counter++)
	{
		id = 0;
		//Target API
		nRet = sound_pool_stream_play(g_hPool, DEFAULT_SAMPLE_TAG, loop, volume, priority, priority_type[enum_counter], callback, data, &id);
		PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_stream_play", SoundPoolGetError(nRet));

		if(id == 0)
		{
			FPRINTF("[Line : %d][%s] %s failed to return a valid id\\n", __LINE__, API_NAMESPACE, "sound_pool_stream_play");
			return 1;
		}

		state = SOUND_POOL_STREAM_STATE_NONE;
		nRet = sound_pool_stream_get_state(g_hPool, id, &state);
		PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_stream_get_state", SoundPoolGetError(nRet));
		PRINT_RESULT(SOUND_POOL_STREAM_STATE_PLAYING, state, "sound_pool_stream_get_state", " Sound pool stream State is not SOUND_POOL_STREAM_STATE_PLAYING after sound_pool_stream_play");

		//Target API
		nRet = sound_pool_stream_stop(g_hPool, id);
		PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_stream_stop", SoundPoolGetError(nRet));
	}

	return 0;
}

//& purpose Pause and Resume a stream by a tag
//& type: auto
/**
* @testcase				ITs_sound_pool_stream_pause_resume_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Pause and Resume a stream
* @scenario				Pause and Resume a stream\n
* @apicovered			sound_pool_stream_pause, sound_pool_stream_resume
* @passcase				If Pause and Resume successfull
* @failcase				If fails to Pause and/or Resume
* @precondition			sound pool handle should be created and source should be loaded
* @postcondition		NA
*/
int ITs_sound_pool_stream_pause_resume_p(void)
{
	START_TEST;

	int nRet = SOUND_POOL_ERROR_NONE;
	sound_pool_stream_state_e state = SOUND_POOL_STREAM_STATE_NONE;
	unsigned int loop = 2;
	float volume = 0.5;
	unsigned int priority = DEFAULT_PRIORITY;
	sound_pool_stream_priority_policy_e priority_policy = SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED;
	sound_pool_stream_state_changed_cb callback = NULL;
	void *data = NULL;
	unsigned int id = 0;

	nRet = sound_pool_stream_play(g_hPool, DEFAULT_SAMPLE_TAG, loop, volume, DEFAULT_PRIORITY, priority_policy, callback, data, &id);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_stream_play", SoundPoolGetError(nRet));

	if(id == 0)
	{
		FPRINTF("[Line : %d][%s] %s failed to return a valid id\\n", __LINE__, API_NAMESPACE, "sound_pool_stream_play");
		return 1;
	}

	nRet = sound_pool_stream_get_state(g_hPool, id, &state);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_stream_get_state", SoundPoolGetError(nRet));
	PRINT_RESULT(SOUND_POOL_STREAM_STATE_PLAYING, state, "sound_pool_stream_get_state", " Sound pool stream State is not SOUND_POOL_STREAM_STATE_PLAYING after sound_pool_stream_play");

	nRet = sound_pool_stream_pause(g_hPool, id);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_stream_pause", SoundPoolGetError(nRet));

	nRet = sound_pool_stream_get_state(g_hPool, id, &state);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_stream_get_state", SoundPoolGetError(nRet));
	PRINT_RESULT(SOUND_POOL_STREAM_STATE_PAUSED, state, "sound_pool_stream_get_state", " Sound pool stream State is not SOUND_POOL_STREAM_STATE_PAUSED after sound_pool_stream_pause");

	nRet = sound_pool_stream_resume(g_hPool, id);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_stream_resume", SoundPoolGetError(nRet));

	nRet = sound_pool_stream_get_state(g_hPool, id, &state);
	PRINT_RESULT_NORETURN(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_stream_get_state", SoundPoolGetError(nRet));
	PRINT_RESULT_NORETURN(SOUND_POOL_STREAM_STATE_PLAYING, state, "sound_pool_stream_get_state", " Sound pool stream State is not SOUND_POOL_STREAM_STATE_PLAYING after sound_pool_stream_resume");

	return 0;
}

//& purpose Gets the current state of a pool
//& type: auto
/**
* @testcase				ITs_sound_pool_get_state_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Gets the current state of a pool
* @scenario				Gets the current state of a pool\n
* @apicovered			sound_pool_get_state
* @passcase				If api returns SOUND_POOL_ERROR_NONE and correct state
* @failcase				If api does not return SOUND_POOL_ERROR_NONE and/or correct state
* @precondition			sound pool handle should be created and source should be loaded
* @postcondition		NA
*/
int ITs_sound_pool_get_state_p(void)
{
	START_TEST;

	int nRet = SOUND_POOL_ERROR_NONE;
	sound_pool_state_e state = SOUND_POOL_STATE_INACTIVE;

	nRet = sound_pool_get_state(g_hPool, &state);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_get_state", SoundPoolGetError(nRet));
	PRINT_RESULT(SOUND_POOL_STATE_ACTIVE, state, "sound_pool_stream_get_state", " Sound pool State is not SOUND_POOL_STATE_ACTIVE after sound_pool_activate");

	return 0;
}

//& purpose Activate and Deactivate a sound pool
//& type: auto
/**
* @testcase				ITs_sound_pool_activate_deactivate_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Activate and Deactivate a sound pool
* @scenario				Activate and Deactivate a sound pool\n
* @apicovered			sound_pool_activate, sound_pool_deactivate, sound_pool_create, sound_pool_destroy
* @passcase				If Activate and Deactivate successfull
* @failcase				If fails to Activate and/or Deactivate
* @precondition			Sound Pool must be created
* @postcondition		NA
*/
int ITs_sound_pool_activate_deactivate_p(void)
{
	START_TEST;

	int nRet = SOUND_POOL_ERROR_NONE;
	sound_pool_h hTestPool[MAX_POOLS-1] = {NULL}; // 1 sound_pool_h already is created in startup
	int macPoolCount = MAX_POOLS-1;
	int poolCount = 0;
	bool bActivateDeactivateFailed = false;
	sound_pool_state_e state = SOUND_POOL_STATE_INACTIVE;

	for (poolCount = 0; poolCount < macPoolCount; poolCount++)
	{
		nRet = sound_pool_create(&hTestPool[poolCount]);
		PRINT_RESULT_NORETURN(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_create", SoundPoolGetError(nRet));

		if(SOUND_POOL_ERROR_NONE == nRet && hTestPool[poolCount] != NULL)
		{
			nRet = sound_pool_activate(hTestPool[poolCount]);

			if(nRet == SOUND_POOL_ERROR_NONE)
			{
				state = SOUND_POOL_STATE_INACTIVE;
				nRet = sound_pool_get_state(hTestPool[poolCount], &state);
				PRINT_RESULT_NORETURN(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_get_state", SoundPoolGetError(nRet));

				if(nRet != SOUND_POOL_ERROR_NONE || state != SOUND_POOL_STATE_ACTIVE)
				{
					FPRINTF("[Line : %d][%s] Sound pool State is not active after sound_pool_activate\\n", __LINE__, API_NAMESPACE);
					bActivateDeactivateFailed = true;
					nRet = sound_pool_destroy(hTestPool[poolCount]);
					PRINT_RESULT_NORETURN(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_destroy", SoundPoolGetError(nRet));
					hTestPool[poolCount] = NULL;
					break;
				}
			}
			else
			{
				FPRINTF("[Line : %d][%s] Unable to activate Sound pool, error returned = %s\\n", __LINE__, API_NAMESPACE, SoundPoolGetError(nRet));
				bActivateDeactivateFailed = true;
				nRet = sound_pool_destroy(hTestPool[poolCount]);
				PRINT_RESULT_NORETURN(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_destroy", SoundPoolGetError(nRet));
				hTestPool[poolCount] = NULL;
				break;
			}
		}
	}

	// Deactivate
	for (poolCount = 0; poolCount < macPoolCount && hTestPool[poolCount] != NULL; poolCount++)
	{
		nRet = sound_pool_deactivate(hTestPool[poolCount]);
		PRINT_RESULT_NORETURN(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_deactivate", SoundPoolGetError(nRet));

		if(nRet == SOUND_POOL_ERROR_NONE)
		{
			state = SOUND_POOL_STATE_ACTIVE;
			nRet = sound_pool_get_state(hTestPool[poolCount], &state);
			PRINT_RESULT_NORETURN(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_get_state", SoundPoolGetError(nRet));
			PRINT_RESULT_NORETURN(SOUND_POOL_STATE_INACTIVE, state, "sound_pool_get_state", "Sound pool State is not inactive after sound_pool_deactivate");
		}
		else
		{
			bActivateDeactivateFailed = true;
		}

		nRet = sound_pool_destroy(hTestPool[poolCount]);
		PRINT_RESULT_NORETURN(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_destroy", SoundPoolGetError(nRet));
	}

	if(bActivateDeactivateFailed == true)
	{
		return 1;
	}

	return 0;
}

//& purpose Sets/Gets the pool's global volume
//& type: auto
/**
* @testcase				ITs_sound_pool_set_get_volume_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Sets/Gets the pool's global volume
* @scenario				Sets/Gets the pool's global volume\n
* @apicovered			sound_pool_set_volume, sound_pool_get_volume
* @passcase				If apis returns SOUND_POOL_ERROR_NONE and correct volume
* @failcase				If api does not return SOUND_POOL_ERROR_NONE and/or correct volume
* @precondition			sound pool handle should be created and source should be loaded
* @postcondition		NA
*/
int ITs_sound_pool_set_get_volume_p(void)
{
	START_TEST;

	float setVolume = 1.0;
	int nRet = sound_pool_set_volume(g_hPool, setVolume);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_set_volume", SoundPoolGetError(nRet));

	float volume = 0.0;
	nRet = sound_pool_get_volume(g_hPool, &volume);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_get_volume", SoundPoolGetError(nRet));

	return 0;
}

//& purpose Sets/Gets the stream's volume
//& type: auto
/**
* @testcase				ITs_sound_pool_stream_set_get_volume_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Sets/Gets the stream's volume
* @scenario				Sets/Gets the stream's volume\n
* @apicovered			sound_pool_stream_set_volume, sound_pool_stream_get_volume
* @passcase				If apis returns SOUND_POOL_ERROR_NONE and correct volume
* @failcase				If api does not return SOUND_POOL_ERROR_NONE and/or correct volume
* @precondition			sound pool handle should be created and source should be loaded
* @postcondition		NA
*/
int ITs_sound_pool_stream_set_get_volume_p(void)
{
	START_TEST;

	int nRet = SOUND_POOL_ERROR_NONE;
	unsigned int id = 0;
	sound_pool_stream_state_e state = SOUND_POOL_STREAM_STATE_NONE;
	unsigned int loop = 3;
	float setVolume = 0.5;
	unsigned int priority = DEFAULT_PRIORITY;
	sound_pool_stream_priority_policy_e priority_policy = SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED;
	sound_pool_stream_state_changed_cb callback = NULL;
	void *data = NULL;

	nRet = sound_pool_stream_play(g_hPool, DEFAULT_SAMPLE_TAG, loop, setVolume, priority, priority_policy, callback, data, &id);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_stream_play", SoundPoolGetError(nRet));

	if(id == 0)
	{
		FPRINTF("[Line : %d][%s] %s failed to return a valid id\\n", __LINE__, API_NAMESPACE, "sound_pool_stream_play");
		return 1;
	}

	float volume = 0.0;
	nRet = sound_pool_stream_get_volume(g_hPool, id, &volume);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_stream_get_volume", SoundPoolGetError(nRet));

	//Setting volume with set API
	setVolume = 0.9;
	nRet = sound_pool_stream_set_volume(g_hPool, id, setVolume);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_stream_set_volume", SoundPoolGetError(nRet));

	volume = 0.0;
	nRet = sound_pool_stream_get_volume(g_hPool, id, &volume);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_stream_get_volume", SoundPoolGetError(nRet));

	return 0;
}

//& purpose Sets/Gets the stream's priority by id
//& type: auto
/**
* @testcase				ITs_sound_pool_stream_set_get_priority_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Sets/Gets the stream's priority
* @scenario				Sets/Gets the stream's priority\n
* @apicovered			sound_pool_stream_set_priority, sound_pool_stream_get_priority
* @passcase				If apis returns SOUND_POOL_ERROR_NONE and correct priority
* @failcase				If api does not return SOUND_POOL_ERROR_NONE and/or correct priority
* @precondition			sound pool handle should be created and source should be loaded
* @postcondition		NA
*/
int ITs_sound_pool_stream_set_get_priority_p(void)
{
	START_TEST;

	int nRet = SOUND_POOL_ERROR_NONE;
	unsigned int id = 0;
	sound_pool_stream_state_e state = SOUND_POOL_STREAM_STATE_NONE;
	unsigned int loop = 2;
	float setVolume = 0.5;
	unsigned int setPriority = DEFAULT_PRIORITY;
	sound_pool_stream_priority_policy_e priority_policy = SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED;
	sound_pool_stream_state_changed_cb callback = NULL;
	void *data = NULL;

	nRet = sound_pool_stream_play(g_hPool, DEFAULT_SAMPLE_TAG, loop, setVolume, setPriority, priority_policy, callback, data, &id);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_stream_play", SoundPoolGetError(nRet));

	if(id == 0)
	{
		FPRINTF("[Line : %d][%s] %s failed to return a valid id\\n", __LINE__, API_NAMESPACE, "sound_pool_stream_play");
		return 1;
	}

	int priority = 0;
	nRet = sound_pool_stream_get_priority(g_hPool, id, &priority);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_stream_get_priority", SoundPoolGetError(nRet));
	PRINT_RESULT(setPriority, priority, "sound_pool_stream_get_priority", "Sound pool stream priority is not same as set value");

	//Changing priority by set priority api
	setPriority = 10;
	nRet = sound_pool_stream_set_priority(g_hPool, id, setPriority);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_stream_set_priority", SoundPoolGetError(nRet));

	priority = 0;
	nRet = sound_pool_stream_get_priority(g_hPool, id, &priority);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_stream_get_priority", SoundPoolGetError(nRet));
	PRINT_RESULT(setPriority, priority, "sound_pool_stream_get_priority", "Sound pool stream priority is not same as set value");

	return 0;
}

//& purpose Gets the current state of stream by id.
//& type: auto
/**
* @testcase				ITs_sound_pool_stream_get_state_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Gets the current state of a pool
* @scenario				Gets the current state of a pool\n
* @apicovered			sound_pool_stream_get_state
* @passcase				If api returns SOUND_POOL_ERROR_NONE
* @failcase				If api does not return SOUND_POOL_ERROR_NONE
* @precondition			sound pool handle should be created and source should be loaded
* @postcondition		NA
*/
int ITs_sound_pool_stream_get_state_p(void)
{
	START_TEST;

	unsigned int id = 1;
	sound_pool_stream_state_e state = SOUND_POOL_STREAM_STATE_NONE;
	unsigned int loop = 2;
	float setVolume = 0.5;
	unsigned int setPriority = DEFAULT_PRIORITY;
	sound_pool_stream_priority_policy_e priority_policy = SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED;
	sound_pool_stream_state_changed_cb callback = NULL;
	void *data = NULL;

	int nRet = sound_pool_stream_play(g_hPool, DEFAULT_SAMPLE_TAG, loop, setVolume, setPriority, priority_policy, callback, data, &id);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_stream_play", SoundPoolGetError(nRet));

	if(id == 0)
	{
		FPRINTF("[Line : %d][%s] %s failed to return a valid id\\n", __LINE__, API_NAMESPACE, "sound_pool_stream_play");
		return 1;
	}

	nRet = sound_pool_stream_get_state(g_hPool, id, &state);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_stream_get_state", SoundPoolGetError(nRet));
	PRINT_RESULT(SOUND_POOL_STREAM_STATE_PLAYING, state, "sound_pool_stream_get_state", " Sound pool stream State is not SOUND_POOL_STREAM_STATE_PLAYING after sound_pool_stream_play");

	return 0;
}

//& purpose Sets/Unsets the callback for handling sound pool state change
//& type: auto
/**
* @testcase				ITs_sound_pool_set_unset_state_changed_cb_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Sets/Unsets the callback
* @scenario				Sets/Unsets the callback\n
* @apicovered			sound_pool_set_state_changed_cb, sound_pool_unset_state_changed_cb
* @passcase				If apis returns SOUND_POOL_ERROR_NONE
* @failcase				If api does not return SOUND_POOL_ERROR_NONE
* @precondition			NA
* @postcondition		NA
*/
int ITs_sound_pool_set_unset_state_changed_cb_p(void)
{
	START_TEST;

	void *data = NULL;
	sound_pool_stream_state_changed_cb callback = SoundPoolStreamStateChanged;
	int nRet = sound_pool_set_state_changed_cb(g_hPool, callback, data);

	g_bCallbackCalled = false;
	nRet = sound_pool_deactivate(g_hPool);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_deactivate", SoundPoolGetError(nRet));

	//callback gets called asynchronously, so it may be already called for play if not so, wait for it
	if(g_bCallbackCalled == false)
	{
		RUN_GMAIN_LOOP;
	}

	PRINT_RESULT(true, g_bCallbackCalled, "sound_pool_deactivate", "Callback not invoked for sound_pool_deactivate");

	nRet = sound_pool_unset_state_changed_cb(g_hPool);
	PRINT_RESULT(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_unset_state_changed_cb", SoundPoolGetError(nRet));

	//activating again as it should be deactivated from cleanup
	nRet = sound_pool_activate(g_hPool);
	PRINT_RESULT_NORETURN(SOUND_POOL_ERROR_NONE, nRet, "sound_pool_activate", SoundPoolGetError(nRet));
	return 0;
}
/** @} */
/** @} */
