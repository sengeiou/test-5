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

//Add helper function definitions here

/**
* @function 			PlayerGetError
* @description			Display the details error information
* @parameter	[IN]	nResult, API return error code
* @return 				error code
*/
char* PlayerGetError(int nResult)
{
	char* pszErrInfo = "Unknown Error";
	switch ( nResult )
	{
	case PLAYER_ERROR_OUT_OF_MEMORY:						pszErrInfo = "PLAYER_ERROR_OUT_OF_MEMORY";						break;
	case PLAYER_ERROR_INVALID_PARAMETER:					pszErrInfo = "PLAYER_ERROR_INVALID_PARAMETER";					break;
	case PLAYER_ERROR_NO_SUCH_FILE:							pszErrInfo = "PLAYER_ERROR_NO_SUCH_FILE";						break;
	case PLAYER_ERROR_INVALID_OPERATION:					pszErrInfo = "PLAYER_ERROR_INVALID_OPERATION";					break;
	case PLAYER_ERROR_FILE_NO_SPACE_ON_DEVICE:				pszErrInfo = "PLAYER_ERROR_FILE_NO_SPACE_ON_DEVICE";			break;
	case PLAYER_ERROR_SEEK_FAILED:							pszErrInfo = "PLAYER_ERROR_SEEK_FAILED";						break;
	case PLAYER_ERROR_INVALID_STATE:						pszErrInfo = "PLAYER_ERROR_INVALID_STATE";						break;
	case PLAYER_ERROR_NOT_SUPPORTED_FILE:					pszErrInfo = "PLAYER_ERROR_NOT_SUPPORTED_FILE";					break;
	case PLAYER_ERROR_INVALID_URI:							pszErrInfo = "PLAYER_ERROR_INVALID_URI";						break;
	case PLAYER_ERROR_PERMISSION_DENIED: 					pszErrInfo = "PLAYER_ERROR_PERMISSION_DENIED";					break;
	case PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE: 		pszErrInfo = "PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE";	break;
	}
	return pszErrInfo;
}

//Print Player State Code
/**
* @function 			PlayerGetState
* @description 			Print the current state of the player
* @parameter	[IN]	eState : the current state
* @return 				string value of player state
*/
char* PlayerGetState(player_state_e eState)
{
	char* pszState = "Unknown State";
	switch ( eState )
	{
	case PLAYER_STATE_NONE:			pszState = "PLAYER_STATE_NONE";			break;
	case PLAYER_STATE_IDLE:			pszState = "PLAYER_STATE_IDLE";			break;
	case PLAYER_STATE_READY:		pszState = "PLAYER_STATE_READY";		break;
	case PLAYER_STATE_PLAYING:		pszState = "PLAYER_STATE_PLAYING";		break;
	case PLAYER_STATE_PAUSED: 		pszState = "PLAYER_STATE_PAUSED";		break;
	}

	return pszState;
}


/**
* @function 			PlayerInitialization
* @description 			Creates a player handler, sets an uri and prepares the handler
* @parameter	[IN]	bool bPrepare 	[if it is true, player would be prepared. Otherwise, player would not be prepared]
* 				[IN]	int eMediaType	[if it is 0, player_set_uri would be set with an audio file. Otherwise, player_set_uri would be set with a video file]
* @return 				true if successful, otherwise false. 
*/
bool PlayerInitialization(bool bPrepare, MediaTypeEnumeration eMediaType)
{
	int nRet = PLAYER_ERROR_INVALID_PARAMETER;
	player_state_e eState;

	nRet = player_create(&g_PlayerHandler);
	if ( nRet != PLAYER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] player_create failed, error returned = %s\\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		return false;
	}	

	if ( g_PlayerHandler == NULL )
	{
		FPRINTF("[Line : %d][%s] player handler is NULL\\n", __LINE__, API_NAMESPACE);
		return false;
	}	

	nRet = player_get_state(g_PlayerHandler, &eState);
	if ( nRet != PLAYER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] player_get_state failed, error returned = %s\\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		PlayerDestroy(false);
		return false;
	}

	FPRINTF("[Line : %d][%s] player_get_state returned = %s\\n", __LINE__, API_NAMESPACE, PlayerGetState(eState));
	if ( eState != PLAYER_STATE_IDLE )
	{
		FPRINTF("[Line : %d][%s] Player state is not in PLAYER_STATE_IDLE after player_creation\\n", __LINE__, API_NAMESPACE);
		PlayerDestroy(false);
		return false;
	}

	if ( eMediaType == MeidaType_Audio )
	{
		char *pszAudioPath = MediaPlayerGetDataPath(MEDIA_AUDIO);
		
		nRet = player_set_uri(g_PlayerHandler, pszAudioPath);
		#if defined(WEARABLE)
	    bool bValue = false;
		system_info_get_platform_bool(INTERNET_FEATURE, &bValue);
		if(bValue == false)
		{
			if(nRet != PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE)
			{
				FPRINTF("[Line : %d][%s] player_set_uri API call returned mismatch %s error for unsupported internet feature\\n", __LINE__, API_NAMESPACE,  PlayerGetError(nRet));
				FREE_MEMORY(pszAudioPath);
				return false;
			}
		}
		#endif
		FREE_MEMORY(pszAudioPath);
	}

	if ( nRet != PLAYER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] player_set_uri failed, error returned = %s\\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		PlayerDestroy(false);
		return false;
	}
	if ( bPrepare )
	{
		nRet = player_prepare(g_PlayerHandler);
		if ( nRet != PLAYER_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] player_prepare failed, error returned = %s\\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
			PlayerDestroy(false);
			return false;
		}	

		nRet = player_get_state(g_PlayerHandler, &eState);
		if ( nRet != PLAYER_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] player_get_state failed, error returned = %s\\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
			PlayerDestroy(false);
			return false;
		}
		
		FPRINTF("[Line : %d][%s] player_get_state returned = %s\\n", __LINE__, API_NAMESPACE, PlayerGetState(eState));
		if ( eState != PLAYER_STATE_READY )
		{
			FPRINTF("[Line : %d][%s] Player state is not in in PLAYER_STATE_READY after player_prepare\\n", __LINE__, API_NAMESPACE);
			PlayerDestroy(true);
			return false;
		}
	}
	return true;
}
/**
* @function 			PlayerDestroy
* @description 			Unprepare and destroy the player handler
* @parameter	[IN]	bIsUnprepare, whether unprepare needed or not
* @return 				true if successful, else false 
*/
bool PlayerDestroy(bool bIsUnprepare)
{
	int nRet = PLAYER_ERROR_NONE;

	if ( bIsUnprepare )
	{
		nRet = player_unprepare(g_PlayerHandler); 
		if ( nRet != PLAYER_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] player_unprepare failed, error returned = %s\\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
			return false;
		}
	}
	nRet = player_destroy(g_PlayerHandler);
	if ( nRet != PLAYER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] player_destroy failed, error returned = %s\\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		return false;
	}

	g_PlayerHandler = NULL;
	return true;
}

/**
* @function 			PlayerSetVolume
* @description 			Get the volume to preserve, and set a new volume of the player
* @parameter	[OUT]	pfPreserveLeftVol, save the left vol
* 				[OUT]	pfPreserveRightVol, save the right vol
* 				[IN]	fSetLeftVol, set the current left vol
* 				[IN]	fSetRightVol, set the current right vol
* @return 				true if successful, else false 
*/
bool PlayerSetVolume(float *pfPreserveLeftVol, float *pfPreserveRightVol, float fSetLeftVol, float fSetRightVol)
{
	int nRet = PLAYER_ERROR_NONE;

	// to preserve the volume
	nRet = player_get_volume(g_PlayerHandler, pfPreserveLeftVol, pfPreserveRightVol);
	if ( nRet != PLAYER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] player_get_volume failed, error returned = %s\\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		PlayerDestroy(true);
		return false;
	}

	nRet = player_set_volume(g_PlayerHandler, fSetLeftVol, fSetRightVol);
	if ( nRet != PLAYER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] player_set_volume failed, error returned = %s\\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		PlayerDestroy(true);
		return false;
	}

	return true;
}

/**	
* @function 			PlayerGmainLoopCallBack
* @description	 		Callback for GmainLoop and player start during callback time.
* @parameter	[IN]	data, user data
* @return 				true (recommended)
*/
gboolean PlayerGmainLoopCallBack(gpointer data)
{
	g_nPlayerWaitLoopCounter++;
	int nRet = PLAYER_ERROR_NONE;
	player_state_e eState = PLAYER_STATE_NONE;

	if ( g_nPlayerWaitLoopCounter == 1 )
	{
		nRet = player_start(g_PlayerHandler);
		if ( nRet != PLAYER_ERROR_NONE )
		{		
			FPRINTF("[Line : %d][%s] player_start failed, error returned = %s\\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
			PlayerDestroy(true);
		}
	}
	if ( g_nPlayerWaitLoopCounter == WAIT_TIME )
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] g_MainLoop quit for timeout\\n", __LINE__, API_NAMESPACE);
#endif
		nRet = player_get_state(g_PlayerHandler, &eState);
		if ( nRet != PLAYER_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] player_get_state failed, error returned = %s\\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
			PlayerDestroy(true);
		}
		//Checks the player status is PLAYER_STATE_PLAYING because of player_start called in 1st loop counter
		if ( eState == PLAYER_STATE_PLAYING )
		{
			nRet = player_stop(g_PlayerHandler);
			if ( nRet != PLAYER_ERROR_NONE )
			{		
				FPRINTF("[Line : %d][%s] player_stop failed, error returned = %s\\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
				PlayerDestroy(true);
			}
		}
		g_main_loop_quit(g_MainLoopPlayer);

	}
	else
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] GmainLoop runs with wait loop counter: [%d]\\n", __LINE__, API_NAMESPACE, g_nPlayerWaitLoopCounter);
#endif
	}
	return true;
}

/**
* @function 			RuntimeErrorInfo
* @description 			Print the error of runtime information
* @parameter	[IN]	nResult, the error code
* 				[IN]	pszApiName, API name
* @return 				NA
*/

void RuntimeErrorInfo(char *pszApiName, int nResult)
{
	char* pszErrInfo = "UNKNOWN";
	switch ( nResult )
	{
	case RUNTIME_INFO_ERROR_INVALID_PARAMETER:		pszErrInfo = "RUNTIME_INFO_ERROR_INVALID_PARAMETER";		break;
	case RUNTIME_INFO_ERROR_OUT_OF_MEMORY:			pszErrInfo = "RUNTIME_INFO_ERROR_OUT_OF_MEMORY";			break;
	case RUNTIME_INFO_ERROR_IO_ERROR:				pszErrInfo = "RUNTIME_INFO_ERROR_IO_ERROR";				break;
	case RUNTIME_INFO_ERROR_PERMISSION_DENIED:		pszErrInfo = "RUNTIME_INFO_ERROR_PERMISSION_DENIED";		break; 
	}

	FPRINTF("[Line : %d][%s] %s is failed, error returned = %s\\n", __LINE__, API_NAMESPACE, pszApiName, pszErrInfo);
}

/**
* @function 			MediaPlayerGetDataPath
* @description 			Get the path to application data directory
* @parameter	[IN]	char* pszFileName [file name]
* @return 				NA
*/
char* MediaPlayerGetDataPath(char *pszFileName)
{
	char *pszAppData =  app_get_data_path(),*pszImgPath = NULL;
	if ( pszAppData == NULL || strlen(pszAppData) == 0 )
	{
		FPRINTF("[Line : %d][%s] app_get_resource_path() returned invalid path\\n", __LINE__, API_NAMESPACE);
		return pszImgPath;
	}
	
	pszImgPath = (char*) calloc(1, strlen(pszAppData) + strlen(pszFileName)+1);
	if (pszImgPath == NULL)
		return pszImgPath;
	
	snprintf(pszImgPath, strlen(pszAppData) + strlen(pszFileName)+2, "%s%s",pszAppData, pszFileName);
	FPRINTF("[Line : %d][%s] app_get_resource_path() is %s\\n", __LINE__, API_NAMESPACE,pszImgPath);
	return pszImgPath;
}

/** @} */ //end of ctc-player