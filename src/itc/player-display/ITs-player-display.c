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
#include "ITs-player-display-common.h"
#include <curl/curl.h>
#include "net_connection.h"
#include <Ecore_Wayland2.h>
#include <Ecore_Evas.h>

/** @addtogroup itc-player-display
*  @ingroup itc
*  @{
*/

//& set: Player
bool g_bPlayerCreation;
bool g_bPlayerVideoCaptureCallback;
bool g_bPlayerVideoStreamChanged;
bool g_bPlayerCallbackParameter;

int g_nTimeoutId;
GMainLoop *g_pMainLoop;
static connection_h g_connection = NULL;

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
//Callbacks
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

//Callbacks

/**
* @function				PlayerVideoCaptureCallback
* @description			Callback function which is invoked when the video is captured
* @parameter			unsigned char *data, int width, int height, unsigned int size, void *user_data
* @return				void
*/
static void PlayerVideoCaptureCallback(unsigned char *data, int width, int height, unsigned int size, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback PlayerVideoCaptureCallback Called\\n",__LINE__, API_NAMESPACE);
	g_bPlayerVideoCaptureCallback = true;
}

/**
* @function                             PlayerVideoStreamChangedCallback
* @description                  Called to notify the video stream changed.
* @parameter                    int width, int height, int fps, int bit_rate, void *user_data
* @return                               void
*/
static void PlayerVideoStreamChangedCallback(int width, int height, int fps, int bit_rate, void *user_data)
{
        FPRINTF("[Line : %d][%s] Callback PlayerVideoStreamChangedCallback Called\\n",__LINE__, API_NAMESPACE);
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
}

/**
* @function			ITs_player_startup_display
* @description		Called before each test, created player handle
* @parameter		NA
* @return			NA
*/
void ITs_player_display_startup(void)
{
	ecore_main_loop_glib_integrate();
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Player_p\\n", __LINE__, API_NAMESPACE);
#endif

	CreateEvasWindow();
	if ( g_pEvasObject == NULL )
	{
		FPRINTF("[Line : %d][%s] Evas window object is not created, failed in Precondition\\n", __LINE__, API_NAMESPACE);
		g_bPlayerCreation = false;
		return;
	}

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
* @function			ITs_player_cleanup_display
* @description		Called after each test, destroys player handle
* @parameter		NA
* @return			NA
*/
void ITs_player_display_cleanup(void)
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

	return;
}



/** @addtogroup itc-player-testcases
*  @brief		Integration testcases for module player
*  @ingroup		itc-player
*  @{
*/


//& purpose: Set and get ROI (Region Of Interest) area of the content video source
//& type: auto
/**
* @testcase				ITc_player_set_get_video_roi_area_p
* @author				SRID(s.rathi)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @since_tizen			5.0
* @description			Set and get ROI (Region Of Interest) area of the content video source
* @scenario				Create player handle\n
*						get player state\n
*						unprepare player\n
*						set player display\n
*						set video ROI\n
*						prepare player\n
*						get video ROI\n
*						check results\n
*						destroy the handler
* @apicovered			player_set_video_roi_area, player_get_video_roi_area
* @passcase				When it set and get video ROI area
* @failcase				When it does not set or get video ROI area
* @precondition			The player display must be set as PLAYER_DISPLAY_TYPE_OVERLAY
* @postcondition		N/A
*/
int ITc_player_set_get_video_roi_area_p(void) 
{
	START_TEST;

	double setX = 0.1, setY = 0.1, setWidth = 0.5, setHeight = 0.5;
	double getX = 0.0, getY = 0.0, getWidth = 0.0, getHeight = 0.0;
	int nRet = PLAYER_ERROR_NONE;
	player_state_e state;

	if ( InitializePlayerHandler(true, 1) != true )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}
	nRet = player_get_state(g_player,&state);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet));

	if ( state == PLAYER_STATE_READY )
	{
		nRet = player_unprepare(g_player);
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
	}

	nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_OVERLAY, GET_DISPLAY(g_pEvasWindow));
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));

	nRet = player_set_video_roi_area(g_player, setX, setY, setWidth, setHeight);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_video_roi_area", PlayerGetError(nRet));

	usleep(2000);

	nRet = player_prepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

	nRet = player_get_video_roi_area(g_player, &getX, &getY, &getWidth, &getHeight);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_video_roi_area", PlayerGetError(nRet), player_unprepare(g_player));

	if ( (setX != getX) || (setY != getY) || (setWidth != getWidth) || (setHeight != getHeight) )
	{
		FPRINTF("[Line : %d][%s] player_set_get_video_roi_area mismatched, error returned = %s", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_unprepare(g_player);
	PRINT_RESULT_NORETURN(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}


//& purpose: Set and get rotation of the x surface video display
//& type: auto
/**
* @testcase				ITc_player_set_get_display_rotation_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Set and get rotation of the x surface video display
* @scenario				Create player handle\n
*						set player display\n
*						set display rotation\n
*						get display rotation\n
*						check results\n
*						destroy the handler
* @apicovered			player_set_display, player_set_display_rotation, player_get_display_rotation
* @passcase				When it set and get x11 display rotation
* @failcase				When it does not set or get x11 display rotation
* @precondition			The player display must be set as PLAYER_DISPLAY_TYPE_OVERLAY
* @postcondition		N/A
*/
int ITc_player_set_get_display_rotation_p(void) 
{ 
	START_TEST;

	player_display_rotation_e rotation;

	int nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_OVERLAY, GET_DISPLAY(g_pEvasWindow));
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));

	nRet = player_set_display_rotation(g_player, PLAYER_DISPLAY_ROTATION_90);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display_rotation", PlayerGetError(nRet));

	usleep(2000);

	nRet = player_get_display_rotation(g_player, &rotation);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_display_rotation", PlayerGetError(nRet));

	if ( rotation != PLAYER_DISPLAY_ROTATION_90 )
	{
		FPRINTF("[Line : %d][%s] player_set_get_display_rotation mismatched, error returned = %s", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		return 1;
	}

	return 0;
}


//& purpose: Set x surface video display visible
//& type: auto

/**
* @testcase				ITc_player_set_display_visible_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Set x surface video display visible
* @scenario				Create player handle\n
*						set player display\n
*						set x surface video display visible\n
*						destroy the handler
* @apicovered			player_set_display, player_set_display_visible,
* @passcase				When it can set visibility of the x surface video display
* @failcase				When it can not set visibility of the x surface video display
* @precondition			N/A
* @postcondition		N/A
*/
int ITc_player_set_display_visible_p(void) 
{
	START_TEST;
	int nRet = -1;

	nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_EVAS, g_pEvasObject);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));

	nRet = player_set_display_visible(g_player, true);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display_visible", PlayerGetError(nRet));

	return 0;
}


//& purpose: Set and get video display mode
//& type : auto
/**
* @testcase				ITc_player_set_get_display_mode_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Set and get video display mode
* @scenario				Initialize player handle\n
*						set display mode\n
*						get display mode\n
*						check the result\n
*						destroy the handler
* @apicovered			player_set_display_mode, player_get_display_mode
* @passcase				When it can set and get player position
* @failcase				When it can not set or get player position
* @precondition			The player state must be one of these: PLAYER_STATE_READY, PLAYER_STATE_PLAYING, or PLAYER_STATE_PAUSED
* @postcondition		N/A
*/
int ITc_player_set_get_display_mode_p(void) 
{
	START_TEST;

	player_display_mode_e mode;

	if ( InitializePlayerHandler(true, 0) != true )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	int nRet = player_set_display_mode(g_player, PLAYER_DISPLAY_MODE_DST_ROI);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_set_display_mode", PlayerGetError(nRet), player_unprepare(g_player));

	usleep(2000);

	nRet = player_get_display_mode(g_player, &mode);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_display_mode", PlayerGetError(nRet), player_unprepare(g_player));

	if (mode != PLAYER_DISPLAY_MODE_DST_ROI)
	{
		FPRINTF("[Line : %d][%s] player_set_get_display_mode mismatched, error returned = %s", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}

//& purpose: Set the video display and checks if it is visible
//& type: auto
/**
* @testcase				ITc_player_is_display_visible_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Set the video display and checks if it is visible
* @scenario				Create player handle\n
*						set player display\n
*						check if display visible\n
*						destroy the handler
* @apicovered			player_set_display, player_is_display_visible
* @passcase				When it set the display successfully and checks if it is visible
* @failcase				When it set the display successfully and checks if it is visible
* @precondition			The player state must be one of these: PLAYER_STATE_IDLE, PLAYER_STATE_READY, PLAYER_STATE_PLAYING, or PLAYER_STATE_PAUSED for set_display
* @postcondition		N/A
*/
int ITc_player_is_display_visible_p(void) 
{
	START_TEST;

	bool visible;

	int nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_OVERLAY, GET_DISPLAY(g_pEvasWindow));
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));

	nRet = player_is_display_visible(g_player, &visible);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_is_display_visible", PlayerGetError(nRet));

	return 0;
}
//& purpose: Sets the ROI(Region Of Interest) area of display
//& type: auto
/**
* @testcase				ITc_player_set_display_roi_area_p
* @author				SRID(manu.tiwari)
* @reviewer				SRID(amritanshu.p1)
* @type					auto
* @since_tizen			3.0
* @description			Sets the ROI(Region Of Interest) area of display
* @scenario					set player display mode\n
*						set display roi area\n
* @apicovered			player_set_display_mode, player_set_display_roi_area
* @passcase				When player_set_display_roi_area api passed
* @failcase				When player_set_display_roi_area api failed
* @precondition			The player display mode must be set
* @postcondition		N/A
*/
int ITc_player_set_display_roi_area_p(void)  
{
	START_TEST;

	int nRet = player_set_display_mode(g_player, PLAYER_DISPLAY_MODE_DST_ROI);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display_mode", PlayerGetError(nRet));
	usleep(2000);

	nRet = player_set_display_roi_area(g_player, xVal, yVal, WIDTH, HEIGHT);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display_roi_area", PlayerGetError(nRet));

	return 0;
}

//& purpose: Sets the audio only mode
//& type: auto
/**
* @testcase				ITc_player_set_audio_only_p
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @since_tizen			4.0
* @description			Sets the audio only mode
* @scenario				Sets the audio only mode\n
* @apicovered			player_set_audio_only
* @passcase				When player_set_audio_only api passed
* @failcase				When player_set_audio_only api failed
* @precondition			The player state must be one of: #PLAYER_STATE_READY, #PLAYER_STATE_PLAYING, or #PLAYER_STATE_READY
* @postcondition		N/A
*/
int ITc_player_set_audio_only_p(void) 
{
	START_TEST;

	int nRet = -1;
	player_state_e state;
	char pPath[PATH_LEN] = {0};

	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_VIDEO, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet));

	PlayerGetState(state);

	if ( state != PLAYER_STATE_IDLE )
	{
		FPRINTF("[Line : %d][%s] ITc_player_set_audio_only_p, failed as Player state is not PLAYER_STATE_IDLE to set uri",__LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_set_uri(g_player, pPath);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_OVERLAY, GET_DISPLAY(g_pEvasWindow));
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));

	nRet = player_prepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

	nRet = player_get_state(g_player, &state);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet));
	PlayerGetState(state);

	if (!(state == PLAYER_STATE_READY || state == PLAYER_STATE_PLAYING || state == PLAYER_STATE_PAUSED))
	{
		FPRINTF("[Line : %d][%s] ITc_player_set_audio_only_p, failed as Player state is not as precondition", __LINE__, API_NAMESPACE);
		return 1;
	}

	bool is = false;
	nRet = player_is_audio_only(g_player, &is);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_is_audio_only", PlayerGetError(nRet));

	bool audio_only = !is;
	nRet = player_set_audio_only(g_player, audio_only);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_audio_only", PlayerGetError(nRet));

	nRet = player_is_audio_only(g_player, &is);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_is_audio_only", PlayerGetError(nRet));

	if(is != audio_only)
	{
		FPRINTF("[Line : %d][%s] ITc_player_set_audio_only_p, failed as get audio only is not same as set audio only\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	audio_only = !audio_only;
	nRet = player_set_audio_only(g_player, audio_only);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_audio_only", PlayerGetError(nRet));

	nRet = player_is_audio_only(g_player, &is);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_is_audio_only", PlayerGetError(nRet));

	if(is != audio_only)
	{
		FPRINTF("[Line : %d][%s] ITc_player_set_audio_only_p, failed as get audio only is not same as set audio only\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets the audio only mode status
//& type: auto
/**
* @testcase				ITc_player_is_audio_only_p
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @since_tizen			4.0
* @description			Gets the audio only mode status
* @scenario				Gets the audio only mode status\n
* @apicovered			player_is_audio_only
* @passcase				When player_is_audio_only passed
* @failcase				When player_is_audio_only failed
* @precondition			The player state must be one of: #PLAYER_STATE_IDLE, #PLAYER_STATE_READY, #PLAYER_STATE_PLAYING, or #PLAYER_STATE_PAUSED
* @postcondition		N/A
*/
int ITc_player_is_audio_only_p(void) 
{
	START_TEST;

	int nRet = -1;
	player_state_e state;
	char pPath[PATH_LEN] = {0};

	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_VIDEO, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_IDLE )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_create() call",__LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_set_uri(g_player, pPath);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_OVERLAY, GET_DISPLAY(g_pEvasWindow));
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));

	nRet = player_prepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

	nRet = player_get_state(g_player, &state);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet));
	PlayerGetState(state);

	if (!(state == PLAYER_STATE_IDLE || state == PLAYER_STATE_READY || state == PLAYER_STATE_PLAYING || state == PLAYER_STATE_PAUSED))
	{
		FPRINTF("[Line : %d][%s] ITc_player_is_audio_only_p, failed as Player state is not as precondition", __LINE__, API_NAMESPACE);
		return 1;
	}

	bool is = false;
	nRet = player_is_audio_only(g_player, &is);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_is_audio_only", PlayerGetError(nRet));

	return 0;
}

//& purpose: Gets the video display's height and width
//& type : auto
/**
* @testcase				ITc_player_get_video_size_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Gets the video display's height and width
* @scenario				Initialize player handle\n
*						start player\n
*						get video display's height and width\n
*						check the result\n
*						destroy the handler
* @apicovered			player_start, player_get_video_size, player_unprepare
* @passcase				When it can get video display's height and width
* @failcase				When it can not get video display's height and width
* @precondition			The player state must be PLAYER_STATE_PLAYING or PLAYER_STATE_PAUSED
* @postcondition		N/A
*/
int ITc_player_get_video_size_p(void)   
{
	START_TEST;

	int nWidth;
	int nHeight;
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

	nRet = player_get_video_size(g_player, &nWidth, &nHeight);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_video_size", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	nRet = player_stop(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}

//& purpose: Gets the video stream information
//& type : auto
/**
* @testcase				ITc_player_get_video_stream_info_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Gets the video stream information
* @scenario				Initialize player handle\n
*						start player\n
*						get video stream info\n
*						check the result\n
*						destroy the handler
* @apicovered			player_start, player_get_video_stream_info, player_unprepare
* @passcase				When it can get video stream information
* @failcase				When it can not get video stream information
* @precondition			The player state must be PLAYER_STATE_PLAYING or PLAYER_STATE_PAUSED
* @postcondition		N/A
*/
int ITc_player_get_video_stream_info_p(void)  
{
	START_TEST;

	int nFps;
	int nBit_rate;
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

	nRet = player_get_video_stream_info(g_player, &nFps, &nBit_rate);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_video_stream_info", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	nRet = player_stop(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}

//& purpose: Captures the video frame, asynchronously
//& type: auto
/**
* @testcase				ITc_player_capture_video_p
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.3
* @description			Captures the video frame, asynchronously
* @scenario				Set player display\n
*						Initialize player handle\n
*						Start player\n
*						callback player capture video\n
*						check results\n
*						destroy the handler
* @apicovered			player_set_uri, player_prepare, player_start, player_capture_video, player_unprepare
* @passcase				When it captures video frame
* @failcase				When it does not captures video frame
* @precondition			The player state must be PLAYER_STATE_PLAYING by player_start() or PLAYER_STATE_PAUSED by player_pause()
* @postcondition		It invokes player_video_captured_cb() when capture completes, if you set a callback
*/
int ITc_player_capture_video_p(void) 
{
	START_TEST;

	player_state_e state;

	char pPath[PATH_LEN] = {0,};
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_VIDEO2, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = -1;

	nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_EVAS, g_pEvasObject);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));

	nRet = player_set_uri(g_player, pPath);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	nRet = player_prepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

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

	sleep(2);
	g_bPlayerVideoCaptureCallback = false;

	nRet = player_capture_video(g_player, PlayerVideoCaptureCallback, NULL);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_capture_video", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	PlayerWaitForAsync();

	if ( !g_bPlayerVideoCaptureCallback )
	{
		FPRINTF("[Line : %d][%s] player_video_captured_cb failed, error returned = callback not invoked", __LINE__, API_NAMESPACE);
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

//& purpose: Registers/Unregisters a callback function to be invoked when video stream is changed.
//& type : auto
/**
* @testcase				ITc_player_set_unset_video_stream_changed_cb_p
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @since_tizen			2.4
* @description			Registers/Unregisters a callback function to be invoked when video stream is changed.
* @scenario				Registers the callback using player_set_video_stream_changed_cb\n
*						Check if callback is hit\n
*						Unregisters the callback using player_unset_video_stream_changed_cb
* @apicovered			player_set_display, player_prepare, player_set_video_stream_changed_cb, player_start, player_unset_video_stream_changed_cb, player_stop, player_unprepare, player_get_state
* @passcase				if all covered apis are passed and Callback is hit
* @failcase				if any covered api is failed or Callback is not hit
* @precondition			NA
* @postcondition		NA
*/
int ITc_player_set_unset_video_stream_changed_cb_p(void) 
{
	START_TEST;

	bool bTelFeatureSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE, API_NAMESPACE);
	bool bWifiFeatureSupported = TCTCheckSystemInfoFeatureSupported(WIFI_FEATURE, API_NAMESPACE);
	if ( !bTelFeatureSupported && !bWifiFeatureSupported )
	{
		FPRINTF("[Line : %d][%s] Network is not working. Skipping Test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	player_state_e state;

	g_bPlayerVideoStreamChanged = false;
	g_bPlayerCallbackParameter = false;

	int nRet = -1;

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet));

	if ( state != PLAYER_STATE_IDLE )
	{
		FPRINTF("[Line : %d][%s] Player state is not idle", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( InitializePlayerHandler(false, 4) != true )
	{
		PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(InitializePlayerHandler);
		return 1;
	}

	nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_EVAS, g_pEvasObject);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));

	nRet = player_set_video_stream_changed_cb(g_player, PlayerVideoStreamChangedCallback, NULL);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_video_stream_changed_cb", PlayerGetError(nRet));

	nRet = player_prepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

	sleep(3);

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet), player_unprepare(g_player));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_prepare() call", __LINE__, API_NAMESPACE);
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

	PlayerWaitForAsync();

	if ( !g_bPlayerVideoStreamChanged )
	{
		FPRINTF("[Line : %d][%s] player_set_video_stream_changed_cb failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}
	else if ( !g_bPlayerCallbackParameter )
	{
		player_stop(g_player);
		player_unprepare(g_player);
		return 1;
	}

	nRet = player_unset_video_stream_changed_cb(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_unset_video_stream_changed_cb", PlayerGetError(nRet), player_stop(g_player);player_unprepare(g_player));

	nRet = player_stop(g_player);
	PRINT_RESULT_CLEANUP(PLAYER_ERROR_NONE, nRet, "player_stop", PlayerGetError(nRet), player_unprepare(g_player));

	nRet = player_unprepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));

	return 0;
}

//& purpose: Sets player display
//& type: auto
/**
* @testcase				ITc_player_set_display_p
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @since_tizen			6.5
* @description			Sets player display
* @scenario				Sets player display
* @apicovered			player_set_display
* @passcase				When player_set_display api passed
* @failcase				When player_set_display api failed
* @precondition			Evas window should be created
* @postcondition		N/A
*/
int ITc_player_set_display_p(void)
{
	START_TEST;
	player_state_e state;
	const char *pszExportedShellHandle = NULL;
	Ecore_Evas *ecore_evas;
	Ecore_Wl2_Window *ecore_wl2_win;
	Ecore_Wl2_Subsurface *ecore_wl2_subsurface;
	char pPath[PATH_LEN] = {0};

	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_VIDEO, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = player_get_state(g_player,&state);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet));
	if ( state == PLAYER_STATE_READY )
	{
		nRet = player_unprepare(g_player);
		PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_unprepare", PlayerGetError(nRet));
	}

	createWindow();

	ecore_evas = ecore_evas_ecore_evas_get(evas_object_evas_get(g_pElmWindow));
	ecore_wl2_win = ecore_evas_wayland2_window_get(ecore_evas);
	ecore_wl2_subsurface = ecore_wl2_subsurface_new(ecore_wl2_win);
	ecore_wl2_subsurface_export(ecore_wl2_subsurface);
	pszExportedShellHandle = ecore_wl2_subsurface_exported_surface_handle_get(ecore_wl2_subsurface);

	nRet = player_set_uri(g_player, pPath);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_OVERLAY_SYNC_UI, GET_DISPLAY(pszExportedShellHandle));
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));

	return 0;
}
/** @} */
/** @} */
