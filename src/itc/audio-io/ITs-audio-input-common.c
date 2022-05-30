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
#include "ITs-audio-input-common.h"

/** @addtogroup itc-audio-input
*  @ingroup itc
*  @{
*/

/**
* @function 		AudioInputGetError
* @description	 	Maps error enums to string values
* @parameter		nRet: error code returned
* @return 			error string
*/
char* AudioInputGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case AUDIO_IO_ERROR_INVALID_PARAMETER:		  		szErrorVal = "AUDIO_IO_ERROR_INVALID_PARAMETER";			break;
	case AUDIO_IO_ERROR_OUT_OF_MEMORY: 			 		szErrorVal = "AUDIO_IO_ERROR_OUT_OF_MEMORY";				break;
	case AUDIO_IO_ERROR_DEVICE_NOT_OPENED: 			 	szErrorVal = "AUDIO_IO_ERROR_DEVICE_NOT_OPENED";			break;
	case AUDIO_IO_ERROR_INVALID_OPERATION: 			 	szErrorVal = "AUDIO_IO_ERROR_INVALID_OPERATION";			break;
	case AUDIO_IO_ERROR_DEVICE_NOT_CLOSED:			 	szErrorVal = "AUDIO_IO_ERROR_DEVICE_NOT_CLOSED";			break;
	case AUDIO_IO_ERROR_INVALID_BUFFER: 		 		szErrorVal = "AUDIO_IO_ERROR_INVALID_BUFFER";				break;
	case AUDIO_IO_ERROR_SOUND_POLICY: 					szErrorVal = "AUDIO_IO_ERROR_SOUND_POLICY";					break;
	case AUDIO_IO_ERROR_NONE: 					 		szErrorVal = "AUDIO_IO_ERROR_NONE";							break;
	case AUDIO_IO_ERROR_DEVICE_POLICY_RESTRICTION :		szErrorVal = "AUDIO_IO_ERROR_DEVICE_POLICY_RESTRICTION ";	break;
	case AUDIO_IO_ERROR_PERMISSION_DENIED:				szErrorVal = "AUDIO_IO_ERROR_PERMISSION_DENIED ";			break;
	case AUDIO_IO_ERROR_NOT_SUPPORTED :					szErrorVal = "AUDIO_IO_ERROR_NOT_SUPPORTED ";				break;
	case AUDIO_IO_ERROR_INVALID_STATE :					szErrorVal = "AUDIO_IO_ERROR_INVALID_STATE ";				break;
	default: 									 		szErrorVal = "Unknown Error";								break;
	}
	return szErrorVal;
}

/**
* @function 		AudioChannel
* @description	 	Maps error enums
* @parameter		nRet: error code returned
* @return 			error string
*/
char* AudioChannel(audio_channel_e nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case AUDIO_CHANNEL_STEREO:		szErrorVal = "AUDIO_CHANNEL_STEREO";	break;
	case AUDIO_CHANNEL_MONO:		szErrorVal = "AUDIO_CHANNEL_MONO";		break;
	case AUDIO_CHANNEL_MULTI_4:		szErrorVal = "AUDIO_CHANNEL_MULTI_4";	break;
	case AUDIO_CHANNEL_MULTI_5:		szErrorVal = "AUDIO_CHANNEL_MULTI_5";	break;
	case AUDIO_CHANNEL_MULTI_6:		szErrorVal = "AUDIO_CHANNEL_MULTI_6";	break;
	case AUDIO_CHANNEL_MULTI_7:		szErrorVal = "AUDIO_CHANNEL_MULTI_7";	break;
	case AUDIO_CHANNEL_MULTI_8:		szErrorVal = "AUDIO_CHANNEL_MULTI_8";	break;
	case AUDIO_CHANNEL_MULTI_9:		szErrorVal = "AUDIO_CHANNEL_MULTI_9";	break;
	case AUDIO_CHANNEL_MULTI_10:	szErrorVal = "AUDIO_CHANNEL_MULTI_10";	break;
	case AUDIO_CHANNEL_MULTI_11:	szErrorVal = "AUDIO_CHANNEL_MULTI_11";	break;
	case AUDIO_CHANNEL_MULTI_12:	szErrorVal = "AUDIO_CHANNEL_MULTI_12";	break;
	case AUDIO_CHANNEL_MULTI_13:	szErrorVal = "AUDIO_CHANNEL_MULTI_13";	break;
	case AUDIO_CHANNEL_MULTI_14:	szErrorVal = "AUDIO_CHANNEL_MULTI_14";	break;
	case AUDIO_CHANNEL_MULTI_15:	szErrorVal = "AUDIO_CHANNEL_MULTI_15";	break;
	case AUDIO_CHANNEL_MULTI_16:	szErrorVal = "AUDIO_CHANNEL_MULTI_16";	break;
	default:						szErrorVal = "Unknown Error";			break;
	}
	return szErrorVal;
}
/**
* @function 		AudioSampleRate
* @description	 	Maps error enums
* @parameter		nRet: error code returned
* @return 			error string
*/
char* AudioSampleRate(audio_sample_type_e nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case AUDIO_SAMPLE_TYPE_U8:			szErrorVal = "AUDIO_SAMPLE_TYPE_U8";		break;
	case AUDIO_SAMPLE_TYPE_S16_LE:		szErrorVal = "AUDIO_SAMPLE_TYPE_S16_LE";	break;
	case AUDIO_SAMPLE_TYPE_S24_LE:		szErrorVal = "AUDIO_SAMPLE_TYPE_S24_LE";	break;
	case AUDIO_SAMPLE_TYPE_S24_32_LE:	szErrorVal = "AUDIO_SAMPLE_TYPE_S24_32_LE";	break;
	case AUDIO_SAMPLE_TYPE_S32_LE:		szErrorVal = "AUDIO_SAMPLE_TYPE_S32_LE";	break;
	default:							szErrorVal = "Unknown Error";				break;
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
/** @} */
//Add helper function definitions here
