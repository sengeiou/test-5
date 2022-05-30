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
#include "ITs-wav-player-common.h"

/** @addtogroup itc-wav-player
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

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

	strncpy(pAppDataPath, pPath, PATH_LEN-1);
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
	strncpy(pFinalPath, pAppDataPath, PATH_LEN-1);
	strncat(pFinalPath, pInputPath, strlen(pInputPath)+1);
	FPRINTF("[Line : %d][%s] result path returned = %s\\n", __LINE__, API_NAMESPACE, pFinalPath);
	return true;
}

/**
* @function 		SoundType
* @description	 	Maps error enums
* @parameter		nRet : error code returned
* @return 			error string
*/
char* SoundType(sound_type_e nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case SOUND_TYPE_SYSTEM: 			szErrorVal = "SOUND_TYPE_SYSTEM"; 			break;
	case SOUND_TYPE_NOTIFICATION:		szErrorVal = "SOUND_TYPE_NOTIFICATION"; 	break;
	case SOUND_TYPE_ALARM: 				szErrorVal = "SOUND_TYPE_ALARM"; 			break;
	case SOUND_TYPE_RINGTONE: 			szErrorVal = "SOUND_TYPE_RINGTONE"; 		break;
	case SOUND_TYPE_MEDIA:	 			szErrorVal = "SOUND_TYPE_MEDIA"; 			break;
	case SOUND_TYPE_CALL: 				szErrorVal = "SOUND_TYPE_CALL"; 			break;
	case SOUND_TYPE_VOIP: 				szErrorVal = "SOUND_TYPE_VOIP"; 			break;
	default: 							szErrorVal = "Unknown Error";				break;
	}
	return szErrorVal;
}

/** @} */