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
#include "ITs-tone-player-common.h"

/** @addtogroup itc-tone-player
*  @ingroup itc
*  @{
*/

/**
* @function 		TonePlayerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* TonePlayerGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case TONE_PLAYER_ERROR_NONE:				szErrorVal = "TONE_PLAYER_ERROR_NONE";					break; 
	case TONE_PLAYER_ERROR_INVALID_PARAMETER:	szErrorVal = "TONE_PLAYER_ERROR_INVALID_PARAMETER";		break; 
	case TONE_PLAYER_ERROR_INVALID_OPERATION:	szErrorVal = "TONE_PLAYER_ERROR_INVALID_OPERATION";		break; 
	case TONE_PLAYER_ERROR_NOT_SUPPORTED_TYPE:  szErrorVal = "TONE_PLAYER_ERROR_NOT_SUPPORTED_TYPE";    break;
	default:									szErrorVal = "Unknown Error";							break;
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
* @function 		SoundManagerGetStreamType
* @description	 	Maps StreamType enums to string values
* @parameter		nRet : StreamType code returned
* @return 			StreamType string
*/
char* SoundManagerGetStreamType(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case SOUND_STREAM_TYPE_MEDIA:				szErrorVal = "SOUND_STREAM_TYPE_MEDIA";					break;
	case SOUND_STREAM_TYPE_SYSTEM:				szErrorVal = "SOUND_STREAM_TYPE_SYSTEM";				break;
	case SOUND_STREAM_TYPE_ALARM:				szErrorVal = "SOUND_STREAM_TYPE_ALARM";					break;
	case SOUND_STREAM_TYPE_NOTIFICATION:		szErrorVal = "SOUND_STREAM_TYPE_NOTIFICATION";			break;
	case SOUND_STREAM_TYPE_EMERGENCY:			szErrorVal = "SOUND_STREAM_TYPE_EMERGENCY";				break;
	case SOUND_STREAM_TYPE_VOICE_INFORMATION:	szErrorVal = "SOUND_STREAM_TYPE_VOICE_INFORMATION";		break;
	case SOUND_STREAM_TYPE_VOICE_RECOGNITION:	szErrorVal = "SOUND_STREAM_TYPE_VOICE_RECOGNITION";		break;
	case SOUND_STREAM_TYPE_RINGTONE_VOIP:		szErrorVal = "SOUND_STREAM_TYPE_RINGTONE_VOIP";			break;
	case SOUND_STREAM_TYPE_VOIP:				szErrorVal = "SOUND_STREAM_TYPE_VOIP";					break;
	default:									szErrorVal = "Unknown Type";							break;
	}
	return szErrorVal;
}

/**
* @function 		TonePlayerGetType
* @description	 	Maps error enums
* @parameter		nRet : error code returned
* @return 			error string
*/
char* TonePlayerGetType(tone_type_e nRet)
{
	char *szErrorVal = "Unknown Error";
	switch ( nRet )
	{
	case TONE_TYPE_DTMF_0:								szErrorVal = "TONE_TYPE_DTMF_0";							break;
	case TONE_TYPE_DTMF_1:								szErrorVal = "TONE_TYPE_DTMF_1";							break;
	case TONE_TYPE_DTMF_2:								szErrorVal = "TONE_TYPE_DTMF_2";							break;
	case TONE_TYPE_DTMF_3:								szErrorVal = "TONE_TYPE_DTMF_3";							break;
	case TONE_TYPE_DTMF_4:								szErrorVal = "TONE_TYPE_DTMF_4";							break;
	case TONE_TYPE_DTMF_5:								szErrorVal = "TONE_TYPE_DTMF_5";							break;
	case TONE_TYPE_DTMF_6:								szErrorVal = "TONE_TYPE_DTMF_6";							break;
	case TONE_TYPE_DTMF_7:								szErrorVal = "TONE_TYPE_DTMF_7";							break;
	case TONE_TYPE_DTMF_8:								szErrorVal = "TONE_TYPE_DTMF_8";							break;
	case TONE_TYPE_DTMF_9:								szErrorVal = "TONE_TYPE_DTMF_9";							break;
	case TONE_TYPE_DTMF_S:								szErrorVal = "TONE_TYPE_DTMF_S";							break;
	case TONE_TYPE_DTMF_P:								szErrorVal = "TONE_TYPE_DTMF_P";							break;
	case TONE_TYPE_DTMF_A:								szErrorVal = "TONE_TYPE_DTMF_A";							break;
	case TONE_TYPE_DTMF_B:								szErrorVal = "TONE_TYPE_DTMF_B";							break;
	case TONE_TYPE_DTMF_C:								szErrorVal = "TONE_TYPE_DTMF_C";							break;
	case TONE_TYPE_DTMF_D:								szErrorVal = "TONE_TYPE_DTMF_D";							break;
	case TONE_TYPE_SUP_DIAL:							szErrorVal = "TONE_TYPE_SUP_DIAL";							break;
	case TONE_TYPE_ANSI_DIAL:							szErrorVal = "TONE_TYPE_ANSI_DIAL";							break;
	case TONE_TYPE_JAPAN_DIAL:							szErrorVal = "TONE_TYPE_JAPAN_DIAL";						break;
	case TONE_TYPE_SUP_BUSY:							szErrorVal = "TONE_TYPE_SUP_BUSY";							break;
	case TONE_TYPE_ANSI_BUSY:							szErrorVal = "TONE_TYPE_ANSI_BUSY";							break;
	case TONE_TYPE_JAPAN_BUSY:							szErrorVal = "TONE_TYPE_JAPAN_BUSY";						break;
	case TONE_TYPE_SUP_CONGESTION:						szErrorVal = "TONE_TYPE_SUP_CONGESTION";					break;
	case TONE_TYPE_ANSI_CONGESTION:						szErrorVal = "TONE_TYPE_ANSI_CONGESTION";					break;
	case TONE_TYPE_SUP_RADIO_ACK:						szErrorVal = "TONE_TYPE_SUP_RADIO_ACK";						break;
	case TONE_TYPE_JAPAN_RADIO_ACK:						szErrorVal = "TONE_TYPE_JAPAN_RADIO_ACK";					break;
	case TONE_TYPE_SUP_RADIO_NOTAVAIL:					szErrorVal = "TONE_TYPE_SUP_RADIO_NOTAVAIL";				break;
	case TONE_TYPE_SUP_ERROR:							szErrorVal = "TONE_TYPE_SUP_ERROR";							break;
	case TONE_TYPE_SUP_CALL_WAITING:					szErrorVal = "TONE_TYPE_SUP_CALL_WAITING";					break;
	case TONE_TYPE_ANSI_CALL_WAITING:					szErrorVal = "TONE_TYPE_ANSI_CALL_WAITING";					break;
	case TONE_TYPE_SUP_RINGTONE:						szErrorVal = "TONE_TYPE_SUP_RINGTONE";						break;
	case TONE_TYPE_ANSI_RINGTONE:						szErrorVal = "TONE_TYPE_ANSI_RINGTONE";						break;
	case TONE_TYPE_PROP_BEEP:							szErrorVal = "TONE_TYPE_PROP_BEEP";							break;
	case TONE_TYPE_PROP_ACK:							szErrorVal = "TONE_TYPE_PROP_ACK";							break;
	case TONE_TYPE_PROP_NACK:							szErrorVal = "TONE_TYPE_PROP_NACK";							break;
	case TONE_TYPE_PROP_PROMPT:							szErrorVal = "TONE_TYPE_PROP_PROMPT";						break;
	case TONE_TYPE_PROP_BEEP2:							szErrorVal = "TONE_TYPE_PROP_BEEP2";						break;
	case TONE_TYPE_SUP_INTERCEPT:						szErrorVal = "TONE_TYPE_SUP_INTERCEPT";						break;
	case TONE_TYPE_SUP_INTERCEPT_ABBREV:				szErrorVal = "TONE_TYPE_SUP_INTERCEPT_ABBREV";				break;
	case TONE_TYPE_SUP_CONGESTION_ABBREV:				szErrorVal = "TONE_TYPE_SUP_CONGESTION_ABBREV";				break;
	case TONE_TYPE_SUP_CONFIRM:							szErrorVal = "TONE_TYPE_SUP_CONFIRM";						break;
	case TONE_TYPE_SUP_PIP:								szErrorVal = "TONE_TYPE_SUP_PIP";							break;
	case TONE_TYPE_CDMA_DIAL_TONE_LITE:					szErrorVal = "TONE_TYPE_CDMA_DIAL_TONE_LITE";				break;
	case TONE_TYPE_CDMA_NETWORK_USA_RINGBACK:			szErrorVal = "TONE_TYPE_CDMA_NETWORK_USA_RINGBACK";			break;
	case TONE_TYPE_CDMA_INTERCEPT:						szErrorVal = "TONE_TYPE_CDMA_INTERCEPT";					break;
	case TONE_TYPE_CDMA_ABBR_INTERCEPT:					szErrorVal = "TONE_TYPE_CDMA_ABBR_INTERCEPT";				break;
	case TONE_TYPE_CDMA_REORDER:						szErrorVal = "TONE_TYPE_CDMA_REORDER";						break;
	case TONE_TYPE_CDMA_ABBR_REORDER:					szErrorVal = "TONE_TYPE_CDMA_ABBR_REORDER";					break;
	case TONE_TYPE_CDMA_NETWORK_BUSY:					szErrorVal = "TONE_TYPE_CDMA_NETWORK_BUSY";					break;
	case TONE_TYPE_CDMA_CONFIRM:						szErrorVal = "TONE_TYPE_CDMA_CONFIRM";						break;
	case TONE_TYPE_CDMA_ANSWER:							szErrorVal = "TONE_TYPE_CDMA_ANSWER";						break;
	case TONE_TYPE_CDMA_NETWORK_CALLWAITING:			szErrorVal = "TONE_TYPE_CDMA_NETWORK_CALLWAITING";			break;
	case TONE_TYPE_CDMA_PIP:							szErrorVal = "TONE_TYPE_CDMA_PIP";							break;
	case TONE_TYPE_CDMA_CALL_SIGNAL_ISDN_NORMAL:		szErrorVal = "TONE_TYPE_CDMA_CALL_SIGNAL_ISDN_NORMAL";		break;
	case TONE_TYPE_CDMA_CALL_SIGNAL_ISDN_INTERGROUP:	szErrorVal = "TONE_TYPE_CDMA_CALL_SIGNAL_ISDN_INTERGROUP";	break;
	case TONE_TYPE_CDMA_CALL_SIGNAL_ISDN_SP_PRI:		szErrorVal = "TONE_TYPE_CDMA_CALL_SIGNAL_ISDN_SP_PRI";		break;
	case TONE_TYPE_CDMA_CALL_SIGNAL_ISDN_PAT3:			szErrorVal = "TONE_TYPE_CDMA_CALL_SIGNAL_ISDN_PAT3";		break;
	case TONE_TYPE_CDMA_CALL_SIGNAL_ISDN_PING_RING:		szErrorVal = "TONE_TYPE_CDMA_CALL_SIGNAL_ISDN_PING_RING";	break;
	case TONE_TYPE_CDMA_CALL_SIGNAL_ISDN_PAT5:			szErrorVal = "TONE_TYPE_CDMA_CALL_SIGNAL_ISDN_PAT5";		break;
	case TONE_TYPE_CDMA_CALL_SIGNAL_ISDN_PAT6:			szErrorVal = "TONE_TYPE_CDMA_CALL_SIGNAL_ISDN_PAT6";		break;
	case TONE_TYPE_CDMA_CALL_SIGNAL_ISDN_PAT7:			szErrorVal = "TONE_TYPE_CDMA_CALL_SIGNAL_ISDN_PAT7";		break;
	case TONE_TYPE_CDMA_HIGH_L:							szErrorVal = "TONE_TYPE_CDMA_HIGH_L";						break;
	case TONE_TYPE_CDMA_MED_L:							szErrorVal = "TONE_TYPE_CDMA_MED_L";						break;
	case TONE_TYPE_CDMA_LOW_L:							szErrorVal = "TONE_TYPE_CDMA_LOW_L";						break;
	case TONE_TYPE_CDMA_HIGH_SS:						szErrorVal = "TONE_TYPE_CDMA_HIGH_SS";						break;
	case TONE_TYPE_CDMA_MED_SS:							szErrorVal = "TONE_TYPE_CDMA_MED_SS";						break;
	case TONE_TYPE_CDMA_LOW_SS:							szErrorVal = "TONE_TYPE_CDMA_LOW_SS";						break;
	case TONE_TYPE_CDMA_HIGH_SSL:						szErrorVal = "TONE_TYPE_CDMA_HIGH_SSL";						break;
	case TONE_TYPE_CDMA_MED_SSL:						szErrorVal = "TONE_TYPE_CDMA_MED_SSL";						break;
	case TONE_TYPE_CDMA_LOW_SSL:						szErrorVal = "TONE_TYPE_CDMA_LOW_SSL";						break;
	case TONE_TYPE_CDMA_HIGH_SS_2:						szErrorVal = "TONE_TYPE_CDMA_HIGH_SS_2";					break;
	case TONE_TYPE_CDMA_MED_SS_2:						szErrorVal = "TONE_TYPE_CDMA_MED_SS_2";						break;
	case TONE_TYPE_CDMA_LOW_SS_2:						szErrorVal = "TONE_TYPE_CDMA_LOW_SS_2";						break;
	case TONE_TYPE_CDMA_HIGH_SLS:						szErrorVal = "TONE_TYPE_CDMA_HIGH_SLS";						break;
	case TONE_TYPE_CDMA_MED_SLS:						szErrorVal = "TONE_TYPE_CDMA_MED_SLS";						break;
	case TONE_TYPE_CDMA_LOW_SLS:						szErrorVal = "TONE_TYPE_CDMA_LOW_SLS";						break;
	case TONE_TYPE_CDMA_HIGH_S_X4:						szErrorVal = "TONE_TYPE_CDMA_HIGH_S_X4";					break;
	case TONE_TYPE_CDMA_MED_S_X4:						szErrorVal = "TONE_TYPE_CDMA_MED_S_X4";						break;
	case TONE_TYPE_CDMA_LOW_S_X4:						szErrorVal = "TONE_TYPE_CDMA_LOW_S_X4";						break;
	case TONE_TYPE_CDMA_HIGH_PBX_L:						szErrorVal = "TONE_TYPE_CDMA_HIGH_PBX_L";					break;
	case TONE_TYPE_CDMA_MED_PBX_L:						szErrorVal = "TONE_TYPE_CDMA_MED_PBX_L";					break;
	case TONE_TYPE_CDMA_LOW_PBX_L:						szErrorVal = "TONE_TYPE_CDMA_LOW_PBX_L";					break;
	case TONE_TYPE_CDMA_HIGH_PBX_SS:					szErrorVal = "TONE_TYPE_CDMA_HIGH_PBX_SS";					break;
	case TONE_TYPE_CDMA_MED_PBX_SS:						szErrorVal = "TONE_TYPE_CDMA_MED_PBX_SS";					break;
	case TONE_TYPE_CDMA_LOW_PBX_SS:						szErrorVal = "TONE_TYPE_CDMA_LOW_PBX_SS";					break;
	case TONE_TYPE_CDMA_HIGH_PBX_SSL:					szErrorVal = "TONE_TYPE_CDMA_HIGH_PBX_SSL";					break;
	case TONE_TYPE_CDMA_MED_PBX_SSL:					szErrorVal = "TONE_TYPE_CDMA_MED_PBX_SSL";					break;
	case TONE_TYPE_CDMA_LOW_PBX_SSL:					szErrorVal = "TONE_TYPE_CDMA_LOW_PBX_SSL";					break;
	case TONE_TYPE_CDMA_HIGH_PBX_SLS:					szErrorVal = "TONE_TYPE_CDMA_HIGH_PBX_SLS";					break;
	case TONE_TYPE_CDMA_MED_PBX_SLS:					szErrorVal = "TONE_TYPE_CDMA_MED_PBX_SLS";					break;
	case TONE_TYPE_CDMA_LOW_PBX_SLS:					szErrorVal = "TONE_TYPE_CDMA_LOW_PBX_SLS";					break;
	case TONE_TYPE_CDMA_HIGH_PBX_S_X4:					szErrorVal = "TONE_TYPE_CDMA_HIGH_PBX_S_X4";				break;
	case TONE_TYPE_CDMA_MED_PBX_S_X4:					szErrorVal = "TONE_TYPE_CDMA_MED_PBX_S_X4";					break;
	case TONE_TYPE_CDMA_LOW_PBX_S_X4:					szErrorVal = "TONE_TYPE_CDMA_LOW_PBX_S_X4";					break;
	case TONE_TYPE_CDMA_ALERT_NETWORK_LITE:				szErrorVal = "TONE_TYPE_CDMA_ALERT_NETWORK_LITE";			break;
	case TONE_TYPE_CDMA_ALERT_AUTOREDIAL_LITE:			szErrorVal = "TONE_TYPE_CDMA_ALERT_AUTOREDIAL_LITE";		break;
	case TONE_TYPE_CDMA_ONE_MIN_BEEP:					szErrorVal = "TONE_TYPE_CDMA_ONE_MIN_BEEP";					break;
	case TONE_TYPE_CDMA_KEYPAD_VOLUME_KEY_LITE:			szErrorVal = "TONE_TYPE_CDMA_KEYPAD_VOLUME_KEY_LITE";		break;
	case TONE_TYPE_CDMA_PRESSHOLDKEY_LITE:				szErrorVal = "TONE_TYPE_CDMA_PRESSHOLDKEY_LITE";			break;
	case TONE_TYPE_CDMA_ALERT_INCALL_LITE:				szErrorVal = "TONE_TYPE_CDMA_ALERT_INCALL_LITE";			break;
	case TONE_TYPE_CDMA_EMERGENCY_RINGBACK:				szErrorVal = "TONE_TYPE_CDMA_EMERGENCY_RINGBACK";			break;
	case TONE_TYPE_CDMA_ALERT_CALL_GUARD:				szErrorVal = "TONE_TYPE_CDMA_ALERT_CALL_GUARD";				break;
	case TONE_TYPE_CDMA_SOFT_ERROR_LITE:				szErrorVal = "TONE_TYPE_CDMA_SOFT_ERROR_LITE";				break;
	case TONE_TYPE_CDMA_CALLDROP_LITE:					szErrorVal = "TONE_TYPE_CDMA_CALLDROP_LITE";				break;
	case TONE_TYPE_CDMA_NETWORK_BUSY_ONE_SHOT:			szErrorVal = "TONE_TYPE_CDMA_NETWORK_BUSY_ONE_SHOT";		break;
	case TONE_TYPE_CDMA_ABBR_ALERT:						szErrorVal = "TONE_TYPE_CDMA_ABBR_ALERT";					break;
	case TONE_TYPE_CDMA_SIGNAL_OFF:						szErrorVal = "TONE_TYPE_CDMA_SIGNAL_OFF";					break;
	case TONE_TYPE_USER_DEFINED_LOW_FRE:				szErrorVal = "TONE_TYPE_USER_DEFINED_LOW_FRE";				break;
	case TONE_TYPE_USER_DEFINED_MED_FRE:				szErrorVal = "TONE_TYPE_USER_DEFINED_MED_FRE";				break;
	case TONE_TYPE_USER_DEFINED_HIGH_FRE:				szErrorVal = "TONE_TYPE_USER_DEFINED_HIGH_FRE";				break;
	}	
	return szErrorVal;
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
	case SOUND_TYPE_SYSTEM:			szErrorVal = "SOUND_TYPE_SYSTEM";		break;
	case SOUND_TYPE_NOTIFICATION:	szErrorVal = "SOUND_TYPE_NOTIFICATION";	break;
	case SOUND_TYPE_ALARM:			szErrorVal = "SOUND_TYPE_ALARM";		break;
	case SOUND_TYPE_RINGTONE:		szErrorVal = "SOUND_TYPE_RINGTONE";		break;
	case SOUND_TYPE_MEDIA:			szErrorVal = "SOUND_TYPE_MEDIA"; 		break;
	case SOUND_TYPE_CALL:			szErrorVal = "SOUND_TYPE_CALL"; 		break;
	case SOUND_TYPE_VOIP:			szErrorVal = "SOUND_TYPE_VOIP";			break;
	default:						szErrorVal = "Unknown Error";			break;
	}
	return szErrorVal;
}
/** @} */