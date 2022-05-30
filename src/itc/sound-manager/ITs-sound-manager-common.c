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

gboolean TimeoutFunction(gpointer data)
{
	g_main_loop_quit((GMainLoop *)data);
	return false;
}

/**
* @function 		SoundManagerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* SoundManagerGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case SOUND_MANAGER_ERROR_NONE:					szErrorVal = "SOUND_MANAGER_ERROR_NONE";					break;
	case SOUND_MANAGER_ERROR_OUT_OF_MEMORY:			szErrorVal = "SOUND_MANAGER_ERROR_OUT_OF_MEMORY";			break;
	case SOUND_MANAGER_ERROR_INVALID_PARAMETER:		szErrorVal = "SOUND_MANAGER_ERROR_INVALID_PARAMETER";		break;
	case SOUND_MANAGER_ERROR_INVALID_OPERATION:		szErrorVal = "SOUND_MANAGER_ERROR_INVALID_OPERATION";		break;
	case SOUND_MANAGER_ERROR_PERMISSION_DENIED:		szErrorVal = "SOUND_MANAGER_ERROR_PERMISSION_DENIED";		break;
	case SOUND_MANAGER_ERROR_NOT_SUPPORTED:			szErrorVal = "SOUND_MANAGER_ERROR_NOT_SUPPORTED";			break;
	case SOUND_MANAGER_ERROR_NO_DATA:				szErrorVal = "SOUND_MANAGER_ERROR_NO_DATA";					break;
	case SOUND_MANAGER_ERROR_NO_PLAYING_SOUND:		szErrorVal = "SOUND_MANAGER_ERROR_NO_PLAYING_SOUND";		break;
	case SOUND_MANAGER_ERROR_INTERNAL:				szErrorVal = "SOUND_MANAGER_ERROR_INTERNAL";				break;
	case SOUND_MANAGER_ERROR_POLICY:				szErrorVal = "SOUND_MANAGER_ERROR_POLICY";					break;
	default:										szErrorVal = "Unknown Error";								break;
	}
	return szErrorVal;
}

/**
* @function 		SoundManagerGetSoundType
* @description	 	Maps SoundType enums to string values
* @parameter		nRet : SoundType code returned
* @return 			SoundType string
*/
char* SoundManagerGetSoundType(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case SOUND_TYPE_SYSTEM:					szErrorVal = "SOUND_TYPE_SYSTEM";			break;
	case SOUND_TYPE_NOTIFICATION:			szErrorVal = "SOUND_TYPE_NOTIFICATION";		break;
	case SOUND_TYPE_ALARM:					szErrorVal = "SOUND_TYPE_ALARM";			break;
	case SOUND_TYPE_MEDIA:					szErrorVal = "SOUND_TYPE_MEDIA";			break;
	case SOUND_TYPE_RINGTONE:				szErrorVal = "SOUND_TYPE_RINGTONE";			break;
	case SOUND_TYPE_CALL:					szErrorVal = "SOUND_TYPE_CALL";				break;
	case SOUND_TYPE_VOIP:					szErrorVal = "SOUND_TYPE_VOIP";				break;
	case SOUND_TYPE_VOICE:					szErrorVal = "SOUND_TYPE_VOICE";			break;
	default:								szErrorVal = "Unknown Type";				break;
	}
	return szErrorVal;
}
/**
* @function 		SoundManagerGetSoundStreamType
* @description	 	Maps SoundStreamType enums to string values
* @parameter		nRet : SoundStreamType code returned
* @return 			SoundStreamType string
*/
char* SoundManagerGetSoundStreamType(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case SOUND_STREAM_TYPE_MEDIA:				szErrorVal = "SOUND_STREAM_TYPE_MEDIA";				break;
	case SOUND_STREAM_TYPE_SYSTEM:				szErrorVal = "SOUND_STREAM_TYPE_SYSTEM";			break;
	case SOUND_STREAM_TYPE_ALARM:				szErrorVal = "SOUND_STREAM_TYPE_ALARM";				break;
	case SOUND_STREAM_TYPE_NOTIFICATION:		szErrorVal = "SOUND_STREAM_TYPE_NOTIFICATION";		break;
	case SOUND_STREAM_TYPE_EMERGENCY:			szErrorVal = "SOUND_STREAM_TYPE_EMERGENCY";			break;
	case SOUND_STREAM_TYPE_VOICE_INFORMATION:	szErrorVal = "SOUND_STREAM_TYPE_VOICE_INFORMATION";	break;
	case SOUND_STREAM_TYPE_VOICE_RECOGNITION:	szErrorVal = "SOUND_STREAM_TYPE_VOICE_RECOGNITION";	break;
	case SOUND_STREAM_TYPE_RINGTONE_VOIP:		szErrorVal = "SOUND_STREAM_TYPE_RINGTONE_VOIP";		break;
	case SOUND_STREAM_TYPE_VOIP:				szErrorVal = "SOUND_STREAM_TYPE_VOIP";				break;
    case SOUND_STREAM_TYPE_MEDIA_EXTERNAL_ONLY:     szErrorVal = "SOUND_STREAM_TYPE_MEDIA_EXTERNAL_ONLY";                   break;
	default:									szErrorVal = "Unknown Type";						break;
	}
	return szErrorVal;
}
#if defined(MOBILE) ||  defined(TIZENIOT) || defined(WEARABLE) //Starts MOBILE or  TIZENIOT and WEARABLE

/**
* @function 		SoundManagerGetSoundStreamFocusChanged
* @description	 	Maps SoundStreamFocusChanged enums to string values
* @parameter		nRet : SoundStreamFocusChanged code returned
* @return 			SoundStreamFocusChanged string
*/
char* SoundManagerGetSoundStreamFocusChanged(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case SOUND_STREAM_FOCUS_CHANGED_BY_MEDIA:				szErrorVal = "SOUND_STREAM_FOCUS_CHANGED_BY_MEDIA";				break;
	case SOUND_STREAM_FOCUS_CHANGED_BY_SYSTEM:				szErrorVal = "SOUND_STREAM_FOCUS_CHANGED_BY_SYSTEM";			break;
	case SOUND_STREAM_FOCUS_CHANGED_BY_ALARM:				szErrorVal = "SOUND_STREAM_FOCUS_CHANGED_BY_ALARM";				break;
	case SOUND_STREAM_FOCUS_CHANGED_BY_NOTIFICATION:		szErrorVal = "SOUND_STREAM_FOCUS_CHANGED_BY_NOTIFICATION";		break;
	case SOUND_STREAM_FOCUS_CHANGED_BY_EMERGENCY:			szErrorVal = "SOUND_STREAM_FOCUS_CHANGED_BY_EMERGENCY";			break;
	case SOUND_STREAM_FOCUS_CHANGED_BY_VOICE_INFORMATION:	szErrorVal = "SOUND_STREAM_FOCUS_CHANGED_BY_VOICE_INFORMATION";	break;
	case SOUND_STREAM_FOCUS_CHANGED_BY_VOICE_RECOGNITION:	szErrorVal = "SOUND_STREAM_FOCUS_CHANGED_BY_VOICE_RECOGNITION";	break;
	case SOUND_STREAM_FOCUS_CHANGED_BY_RINGTONE:			szErrorVal = "SOUND_STREAM_FOCUS_CHANGED_BY_RINGTONE";			break;
	case SOUND_STREAM_FOCUS_CHANGED_BY_VOIP:				szErrorVal = "SOUND_STREAM_FOCUS_CHANGED_BY_VOIP";				break;
	case SOUND_STREAM_FOCUS_CHANGED_BY_CALL:				szErrorVal = "SOUND_STREAM_FOCUS_CHANGED_BY_CALL";				break;
	default:												szErrorVal = "Unknown Type";									break;
	}
	return szErrorVal;
}

/**
* @function 		SoundManagerGetSoundStreamFocusFor
* @description	 	Maps SoundStreamFocusFor enums to string values
* @parameter		nRet : SoundStreamFocusFor code returned
* @return 			SoundStreamFocusFor string
*/
char* SoundManagerGetSoundStreamFocusFor(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case SOUND_STREAM_FOCUS_FOR_PLAYBACK:				szErrorVal = "SOUND_STREAM_FOCUS_FOR_PLAYBACK";				break;
	case SOUND_STREAM_FOCUS_FOR_RECORDING:				szErrorVal = "SOUND_STREAM_FOCUS_FOR_RECORDING";			break;
	default:											szErrorVal = "Unknown Type";								break;
	}
	return szErrorVal;
}

/**
* @function 		SoundManagerGetSoundStreamFocusState
* @description	 	Maps SoundStreamFocusState enums to string values
* @parameter		nRet : SoundStreamFocusState code returned
* @return 			SoundStreamFocusState string
*/
char* SoundManagerGetSoundStreamFocusState(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case SOUND_STREAM_FOCUS_STATE_RELEASED:				szErrorVal = "SOUND_STREAM_FOCUS_STATE_RELEASED";			break;
	case SOUND_STREAM_FOCUS_STATE_ACQUIRED:				szErrorVal = "SOUND_STREAM_FOCUS_STATE_ACQUIRED";			break;
	default:											szErrorVal = "Unknown Type";								break;
	}
	return szErrorVal;
}
#endif // End MOBILE or COMMON_IOT and WEARABLE

/**
* @function 		WavPlayerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* WavPlayerGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case WAV_PLAYER_ERROR_NONE:						szErrorVal = "WAV_PLAYER_ERROR_NONE";					break;
	case WAV_PLAYER_ERROR_INVALID_PARAMETER:		szErrorVal = "WAV_PLAYER_ERROR_INVALID_PARAMETER";		break;
	case WAV_PLAYER_ERROR_INVALID_OPERATION:		szErrorVal = "WAV_PLAYER_ERROR_INVALID_OPERATION";		break;
	case WAV_PLAYER_ERROR_FORMAT_NOT_SUPPORTED:		szErrorVal = "WAV_PLAYER_ERROR_FORMAT_NOT_SUPPORTED";	break;
	case WAV_PLAYER_ERROR_NOT_SUPPORTED_TYPE: 		szErrorVal = "WAV_PLAYER_ERROR_NOT_SUPPORTED_TYPE"; 	break;
	default:										szErrorVal = "Unknown Error";							break;
	}
	return szErrorVal;
}

/**
* @function 		WavPlayerGetDataPath
* @description	 	Returnes the application data path
* @parameter		pAppDataPath: application data path
* @return 			true if succeed else false
*/
bool WavPlayerGetDataPath(char* pAppDataPath)
{
	if ( NULL == pAppDataPath )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	memset(pAppDataPath, 0, PATH_LEN);

	char* pPath = NULL;
	pPath = app_get_data_path();
	if ( NULL == pPath )
	{
		FPRINTF("[Line : %d][%s] Unable to get application data path; app_get_data_path returned null value\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	strncpy(pAppDataPath, pPath, strlen(pPath)+1);
	FPRINTF("[Line : %d][%s] application data path returned = %s\\n", __LINE__, API_NAMESPACE, pAppDataPath);
	return true;
}
/**
* @function 		WavPlayerAppendToAppDataPath
* @description	 	Appends the input string to application data path
* @parameter		pInputPath: path to append to data path; pFinalPath: final resultant path
* @return 			true if succeed else false
*/
bool WavPlayerAppendToAppDataPath(char* pInputPath, char* pFinalPath)
{
	if ( NULL == pInputPath || NULL == pFinalPath )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	char pAppDataPath[PATH_LEN] = {0,};
	if ( false == WavPlayerGetDataPath(pAppDataPath) )
	{
		return false;
	}

	memset(pFinalPath, 0, PATH_LEN);
	strncpy(pFinalPath, pAppDataPath, strlen(pAppDataPath)+1);
	strncat(pFinalPath, pInputPath, strlen(pInputPath)+1);
	FPRINTF("[Line : %d][%s] result path returned = %s\\n", __LINE__, API_NAMESPACE, pFinalPath);
	return true;
}

/** @} */
