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
#include "ITs-player-display-common.h"

extern bool PlayerPrepareWithConnectionCheck(player_h g_player);
extern bool CheckOnlineStatus(char *media_path);

/** @addtogroup itc-player-display
*  @ingroup itc
*  @{
*/

//Print Player State Code
void PlayerGetState(player_state_e state)
{
	switch ( state )
	{
	case PLAYER_STATE_NONE:		FPRINTF("[Line: %d][%s] PLAYER_STATE_NONE\\n", __LINE__, API_NAMESPACE);		break;
	case PLAYER_STATE_IDLE:		FPRINTF("[Line: %d][%s] PLAYER_STATE_IDLE\\n", __LINE__, API_NAMESPACE);		break;
	case PLAYER_STATE_READY:	FPRINTF("[Line: %d][%s] PLAYER_STATE_READY\\n", __LINE__, API_NAMESPACE);		break;
	case PLAYER_STATE_PLAYING:	FPRINTF("[Line: %d][%s] PLAYER_STATE_PLAYING\\n", __LINE__, API_NAMESPACE);		break;
	case PLAYER_STATE_PAUSED:	FPRINTF("[Line: %d][%s] PLAYER_STATE_PAUSED\\n", __LINE__, API_NAMESPACE);		break;
	}
}

/**
* @function 		PlayerGetDataPath
* @description	 	Returns the application data path
* @parameter		pAppDataPath: application data path
* @return 			true if succeed else false
*/
bool PlayerGetDataPath(char* pAppDataPath)
{
	if ( NULL == pAppDataPath )
	{
		FPRINTF("[Line: %d][%s] Null Path provided;Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	memset(pAppDataPath, 0, PATH_LEN);

	char* pPath = NULL;
	pPath = app_get_data_path();
	if ( NULL == pPath )
	{
		FPRINTF("[Line: %d][%s] Unable to get application data path;app_get_data_path returned null value\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	strncpy(pAppDataPath, pPath, PATH_LEN-1);
	FPRINTF("[Line: %d][%s] application data path returned = %s\\n", __LINE__, API_NAMESPACE, pAppDataPath);
	return true;
}

/**
* @function 		PlayerAppendToAppDataPath
* @description	 	Appends the input string to application data path
* @parameter		pInputPath: path to append to data path;pFinalPath: final resultant path
* @return 			true if succeed else false
*/
bool PlayerAppendToAppDataPath(char* pInputPath, char* pFinalPath)
{
	if ( (NULL == pInputPath) || (NULL == pFinalPath) )
	{
		FPRINTF("[Line: %d][%s] Null Path provided;Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	char pAppDataPath[PATH_LEN] = {0,};
	if ( false == PlayerGetDataPath(pAppDataPath) )
	{
		return false;
	}

	memset(pFinalPath, 0, PATH_LEN);
	strncpy(pFinalPath, pAppDataPath, strlen(pAppDataPath)+1);
	strncat(pFinalPath, pInputPath, strlen(pInputPath)+1);

	FPRINTF("[Line: %d][%s] result path returned = %s\\n", __LINE__, API_NAMESPACE, pFinalPath);
	return true;
}

/**
* @function 		PlayerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet: error code returned
* @return 			error string
*/
char* PlayerGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case PLAYER_ERROR_NONE: 								szErrorVal = "PLAYER_ERROR_NONE";								break;
	case PLAYER_ERROR_OUT_OF_MEMORY: 						szErrorVal = "PLAYER_ERROR_OUT_OF_MEMORY";						break;
	case PLAYER_ERROR_INVALID_PARAMETER: 					szErrorVal = "PLAYER_ERROR_INVALID_PARAMETER";					break;
	case PLAYER_ERROR_NO_SUCH_FILE: 						szErrorVal = "PLAYER_ERROR_NO_SUCH_FILE";						break;
	case PLAYER_ERROR_INVALID_OPERATION: 					szErrorVal = "PLAYER_ERROR_INVALID_OPERATION";					break;
	case PLAYER_ERROR_FILE_NO_SPACE_ON_DEVICE: 				szErrorVal = "PLAYER_ERROR_FILE_NO_SPACE_ON_DEVICE";			break;
	case PLAYER_ERROR_SEEK_FAILED: 							szErrorVal = "PLAYER_ERROR_SEEK_FAILED";						break;
	case PLAYER_ERROR_INVALID_STATE: 						szErrorVal = "PLAYER_ERROR_INVALID_STATE";						break;
	case PLAYER_ERROR_NOT_SUPPORTED_FILE: 					szErrorVal = "PLAYER_ERROR_NOT_SUPPORTED_FILE";					break;
	case PLAYER_ERROR_INVALID_URI: 							szErrorVal = "PLAYER_ERROR_INVALID_URI";						break;
	case PLAYER_ERROR_SOUND_POLICY: 						szErrorVal = "PLAYER_ERROR_SOUND_POLICY";						break;
	case PLAYER_ERROR_CONNECTION_FAILED: 					szErrorVal = "PLAYER_ERROR_CONNECTION_FAILED";					break;
	case PLAYER_ERROR_VIDEO_CAPTURE_FAILED: 				szErrorVal = "PLAYER_ERROR_VIDEO_CAPTURE_FAILED";				break;
	case PLAYER_ERROR_DRM_EXPIRED: 							szErrorVal = "PLAYER_ERROR_DRM_EXPIRED";						break;
	case PLAYER_ERROR_DRM_NO_LICENSE: 						szErrorVal = "PLAYER_ERROR_DRM_NO_LICENSE";						break;
	case PLAYER_ERROR_DRM_FUTURE_USE: 						szErrorVal = "PLAYER_ERROR_DRM_NO_LICENSE";						break;
	case PLAYER_ERROR_DRM_NOT_PERMITTED: 					szErrorVal = "PLAYER_ERROR_DRM_NOT_PERMITTED";					break;
	case PLAYER_ERROR_RESOURCE_LIMIT: 						szErrorVal = "PLAYER_ERROR_RESOURCE_LIMIT";						break;
	case PLAYER_ERROR_PERMISSION_DENIED: 					szErrorVal = "PLAYER_ERROR_PERMISSION_DENIED";					break;
	case PLAYER_ERROR_BUFFER_SPACE:							szErrorVal = "PLAYER_ERROR_BUFFER_SPACE";						break;
	case PLAYER_ERROR_NOT_AVAILABLE:							szErrorVal = "PLAYER_ERROR_NOT_ABAILABLE";						break;
	case PLAYER_ERROR_NOT_SUPPORTED_AUDIO_CODEC:							szErrorVal = "PLAYER_ERROR_NOT_SUPPORTED_AUDIO_CODEC";						break;
	default: 												szErrorVal = "Unknown Error";									break;
	}

	return szErrorVal;
}

/**
* @function 		InitializePlayerHandler
* @description 		Creates a player handler, sets an uri and prepares the handler
* @parameter[IN]	bool bPrepare 	[if it is true, player would be prepared. Otherwise, player would not be prepared]
* 			[IN]	int nMediaType	[if it is 0, player_set_uri would be set with an audio file. if it is 1, player_set_uri would be set with a video file. Otherwise, player_set_uri would be set with a download source file]
* @return 			true if successful, otherwise false.
*/
bool InitializePlayerHandler(bool bPrepare, int nMediaType)
{
	int nRet = -1;
	player_state_e state;

	char pPath1[PATH_LEN] = {0,};
	char pPath2[PATH_LEN] = {0,};
	char pPath3[PATH_LEN] = {0,};

	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_AUDIO, pPath1) )
	{
		FPRINTF("[Line: %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_VIDEO, pPath2) )
	{
		FPRINTF("[Line: %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	if ( false == PlayerAppendToAppDataPath(MEDIA_PATH_DRC, pPath3) )
	{
		FPRINTF("[Line: %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	nRet=player_get_state(g_player,&state);
	PlayerGetState(state);
	if ( state != PLAYER_STATE_IDLE )
	{
		FPRINTF("[Line: %d][%s] Could not create player", __LINE__, API_NAMESPACE);
		return false;
	}

	if ( nMediaType == 0 )
	{
		nRet = player_set_uri(g_player, pPath1);
	}
	else if ( nMediaType == 1 )
	{
		nRet = player_set_uri(g_player, pPath2);
	}
	else if ( nMediaType == 4 )
	{
		nRet = player_set_uri(g_player, pPath3);
	}
	if ( nRet != PLAYER_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] Could not set player uri", __LINE__, API_NAMESPACE);
		return false;
	}

	if ( bPrepare )
	{
		nRet = player_prepare(g_player);
		player_get_state(g_player,&state);
		PlayerGetState(state);
		if ( nRet != PLAYER_ERROR_NONE )
		{
			FPRINTF("[Line: %d][%s] Could not prepare player", __LINE__, API_NAMESPACE);
			return false;
		}

		if ( state != PLAYER_STATE_READY )
		{
			FPRINTF("[Line: %d][%s] Player state does not change after player_prepare() call", __LINE__, API_NAMESPACE);
			return false;
		}
	}
	return true;
}

/**
* @function 		WinDel
* @description 		Callback function registered by evas_object_smart_callback_add API
* @parameter[IN]	void*, Evas_Object*, void*
* @return 			NA.
*/
void WinDel(void *data, Evas_Object *obj, void *event)
{
	elm_exit();
}

/**
* @function 		CreateEvasWindow
* @description 		Creates an Evas window object
* @parameter[IN]	NA
* @return 			Evas_Object if successful, otherwise NULL.
*/
void CreateEvasWindow()
{
	int w = 0;
	int h = 0;
	/* use gl backend */
	elm_config_accel_preference_set("3d");

	/* create window */
	g_pEvasWindow = elm_win_util_standard_add(PACKAGE, PACKAGE);
	if ( g_pEvasWindow )
	{
		elm_win_borderless_set(g_pEvasWindow, EINA_TRUE);
		evas_object_smart_callback_add(g_pEvasWindow, "delete,request",WinDel, NULL);
		elm_win_screen_size_get(g_pEvasWindow,NULL,NULL,&w,&h);
		evas_object_resize(g_pEvasWindow,w,h);
		elm_win_autodel_set(g_pEvasWindow, EINA_TRUE);
	}

	if ( !g_pEvasWindow )
	{
		FPRINTF("[Line: %d][%s] Evas object window not created", __LINE__, API_NAMESPACE);
		return;
	}

	g_pEvasCore = evas_object_evas_get(g_pEvasWindow);
	if ( !g_pEvasCore )
	{
		FPRINTF("[Line: %d][%s] evas_object_evas_get failed , Evas created is NULL", __LINE__, API_NAMESPACE);
		return;
	}

	g_pEvasObject = evas_object_image_add(g_pEvasCore);

	evas_object_image_size_set(g_pEvasObject, w, h);
	evas_object_image_fill_set(g_pEvasObject, 0, 0, w, h);
	evas_object_resize(g_pEvasObject, w, h);

	elm_win_activate(g_pEvasWindow);
	evas_object_show(g_pEvasWindow);
}

/**
* @function 		createWindow
* @description 		Creates an elm window object
* @parameter[IN]	NA
* @return 			NA
*/
void createWindow()
{
    int w = 0;
    int h = 0;

    if (g_pElmWindow) {
        evas_object_del(g_pElmWindow);
        g_pElmWindow = NULL;
    }

    g_pElmWindow = elm_win_util_standard_add("player_display_tc", "player_display_tc");
    if (g_pElmWindow) {
        elm_win_borderless_set(g_pElmWindow, EINA_TRUE);
        evas_object_smart_callback_add(g_pElmWindow, "delete, request", WinDel, NULL);
        elm_win_screen_size_get(g_pElmWindow, NULL, NULL, &w, &h);
        evas_object_resize(g_pElmWindow, w, h);
        elm_win_autodel_set(g_pElmWindow, EINA_TRUE);
    } else {
        FPRINTF("[Line: %d][%s] createWindow failed , g_pElmWindow created is NULL", __LINE__, API_NAMESPACE);
    }
}

/** @} */
