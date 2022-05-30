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

#ifdef TIZENIOT // For TIZENIOT
	int g_nTimeoutId;
	GMainLoop *g_pMainLoop;
#endif // TIZENIOT
//& set: Player
bool g_bPlayerCreation;
bool g_bPlayerSubtitleUpdatedCallback;
bool g_bPlayerCallbackParameter;


/**
* @function			ITs_player_startup
* @description		Called before each test, created player handle
* @parameter		NA
* @return			NA
*/
void ITs_player_subtitle_startup(void)
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
void ITs_player_subtitle_cleanup(void)
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

#ifdef TIZENIOT // For TIZENIOT
/**
* @function 		QuitGmainLoop
* @description	 	Called to quit
* @parameter		NA
* @return 			NA
*/
void QuitGmainLoop(void)
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
		g_pMainLoop = g_main_loop_new(NULL, false);
		g_nTimeoutId = g_timeout_add(TIMEOUT, PlayerTimeoutFunction, NULL);
		g_main_loop_run(g_pMainLoop);

		g_source_remove(g_nTimeoutId);
		g_nTimeoutId = 0;

		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
}
#else
/**
* @function			PlayerTimeoutFunction
* @description		Called if some callback is not invoked for a particular Player Timeout
* @parameter		gpointer data
* @return			gboolean
*/
static gboolean PlayerTimeoutFunction(gpointer data)
{
	FPRINTF("[Line : %d][%s] Callback Player wait complete for 20 seconds. Timeout\\n",__LINE__, API_NAMESPACE);
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
#endif
//Callbacks

/**
* @function				PlayerSubtitleUpdatedCallback
* @description			Callback function which is invoked when the image tag is posted
* @parameter			char *buffer, int size, void *user_data
* @return				void
*/
static void PlayerSubtitleUpdatedCallback(unsigned long duration, char *text, void *user_data)
{
	g_bPlayerSubtitleUpdatedCallback = true;
	if(text == NULL)
	{
		FPRINTF("[Line : %d][%s] text is not valid\\n", __LINE__, API_NAMESPACE);
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

/** @addtogroup itc-player-testcases
*  @brief		Integration testcases for module player
*  @ingroup		itc-player
*  @{
*/


//& purpose: Test player_set_subtitle_position_offset
//& type : auto
/**
* @testcase				ITc_player_set_subtitle_position_offset_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3.1
* @description			Test player_set_subtitle_position_offset
* @scenario				Call player_set_subtitle_position_offset
* @apicovered			player_set_subtitle_path, player_set_subtitle_position_offset
* @passcase				IF API returns PASS
* @failcase				IF API FAILS
* @precondition			The subtitle must be set by player_set_subtitle_path()
* @postcondition		NA
*/
int ITc_player_set_subtitle_position_offset_p(void)
{
	START_TEST;

	player_state_e state;
	char pPath[PATH_LEN] = {0,};
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_SUBTITLE, pPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( InitializePlayerHandler(false, 1) == false )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}
	int nRet = -1;

	#ifndef TIZENIOT // For Mobile or Wearable
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_EVAS, g_pEvasObject);
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif	//End Mobile or Wearable

	nRet = player_set_subtitle_path(g_player, pPath);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_subtitle_path", PlayerGetError(nRet));

	nRet = player_set_subtitle_updated_cb(g_player, PlayerSubtitleUpdatedCallback, NULL);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_subtitle_updated_cb", PlayerGetError(nRet));

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

	nRet = player_start(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_start", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_stop(g_player); player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_start() call", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_set_subtitle_position_offset(g_player, 1000);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_subtitle_position_offset", PlayerGetError(nRet), player_stop(g_player); player_unprepare(g_player));

	PlayerWaitForAsync();
	if ( !g_bPlayerSubtitleUpdatedCallback )
	{
		FPRINTF("[Line : %d][%s] player_subtitle_updated_cb failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}
	else if(!g_bPlayerCallbackParameter)
	{
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_unset_subtitle_updated_cb(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_unset_subtitle_updated_cb", PlayerGetError(nRet), player_stop(g_player); player_unprepare(g_player));

	nRet = player_stop(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}


//& purpose: Registers a callback function to be invoked when subtitle is updated
//& type : auto
/**
* @testcase				ITc_player_set_unset_subtitle_updated_cb_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Registers a callback function to be invoked when subtitle is updated
* @scenario				call player_set_subtitle_updated_cb\n
*						check if callback is hit\n
*						destroy the handler
* @apicovered			player_set_subtitle_updated_cb, player_set_subtitle_path, player_unset_subtitle_updated_cb, player_prepare, player_unprepare, player_set_display, player_start, player_get_state, player_stop
* @passcase				Callback is hit
* @failcase				Callback is not hit
* @precondition			The subtitle must be set by player_set_subtitle_path()
* @postcondition		player_subtitle_updated_cb() will be invoked
*/
int ITc_player_set_unset_subtitle_updated_cb_p(void)
{
	START_TEST;

	player_state_e state;
	char pPath[PATH_LEN] = {0,};
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_SUBTITLE, pPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bPlayerSubtitleUpdatedCallback = false;
	g_bPlayerCallbackParameter = false;

	if ( InitializePlayerHandler(false, 1) == false )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}
	int nRet = -1;

	#ifndef TIZENIOT // For Mobile or Wearable
		nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_EVAS, g_pEvasObject);
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));
	#endif	//End Mobile or Wearable

	nRet = player_set_subtitle_path(g_player, pPath);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_subtitle_path", PlayerGetError(nRet));

	nRet = player_set_subtitle_updated_cb(g_player, PlayerSubtitleUpdatedCallback, NULL);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_subtitle_updated_cb", PlayerGetError(nRet));

	nRet = player_prepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_prepare() call", __LINE__, API_NAMESPACE);
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
	if ( !g_bPlayerSubtitleUpdatedCallback )
	{
		FPRINTF("[Line : %d][%s] player_subtitle_updated_cb failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}
	else if(!g_bPlayerCallbackParameter)
	{
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_unset_subtitle_updated_cb(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_unset_subtitle_updated_cb", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	nRet = player_stop(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}


