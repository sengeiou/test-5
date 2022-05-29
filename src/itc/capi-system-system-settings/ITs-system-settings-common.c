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
#include "ITs-system-settings-common.h"

/** @addtogroup itc-system-settings
*  @ingroup itc
*  @{
*/

/**
* @function 		SystemSettingsGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* SystemSettingsGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case SYSTEM_SETTINGS_ERROR_NONE:				szErrorVal = "SYSTEM_SETTINGS_ERROR_NONE";				break;
	case SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER:	szErrorVal = "SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER";	break;
	case SYSTEM_SETTINGS_ERROR_IO_ERROR:			szErrorVal = "SYSTEM_SETTINGS_ERROR_IO_ERROR";			break;
	default:										szErrorVal = "Unknown Error";							break;
	}
	return szErrorVal;
}

/**
* @function 		SystemSettingsGetKey
* @description	 	return string for settings key
* @parameter		nVal - enum value
* @return 			string
*/
char* SystemSettingsGetKey(int nVal)
{
	char *pszText = NULL;
	switch ( nVal )
	{
	case SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION:				pszText = "SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION or SYSTEM_SETTINGS_KEY_MOTION_ENABLED";	break;
		//case SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED:		pszText = "SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED";			break;
	case SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED:		pszText = "SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED";		break;
	case SYSTEM_SETTINGS_KEY_LOCALE_TIMEFORMAT_24HOUR:		pszText = "SYSTEM_SETTINGS_KEY_LOCALE_TIMEFORMAT_24HOUR";		break;
	case SYSTEM_SETTINGS_KEY_SOUND_LOCK:					pszText = "SYSTEM_SETTINGS_KEY_SOUND_LOCK";						break;
	case SYSTEM_SETTINGS_KEY_SOUND_SILENT_MODE:				pszText = "SYSTEM_SETTINGS_KEY_SOUND_SILENT_MODE";				break;
	case SYSTEM_SETTINGS_KEY_SOUND_TOUCH:					pszText = "SYSTEM_SETTINGS_KEY_SOUND_TOUCH";					break;
	case SYSTEM_SETTINGS_KEY_DISPLAY_SCREEN_ROTATION_AUTO:	pszText = "SYSTEM_SETTINGS_KEY_DISPLAY_SCREEN_ROTATION_AUTO";	break;
		//case SYSTEM_SETTINGS_KEY_LOCALE_UPDATE_AUTO:			pszText = "SYSTEM_SETTINGS_KEY_LOCALE_UPDATE_AUTO";				break;
		//case SYSTEM_SETTINGS_KEY_MOTION_ENABLED:				pszText = "SYSTEM_SETTINGS_KEY_MOTION_ENABLED";					break;
	case SYSTEM_SETTINGS_KEY_NETWORK_WIFI_NOTIFICATION:		pszText = "SYSTEM_SETTINGS_KEY_NETWORK_WIFI_NOTIFICATION";		break;
	case SYSTEM_SETTINGS_KEY_NETWORK_FLIGHT_MODE:			pszText = "SYSTEM_SETTINGS_KEY_NETWORK_FLIGHT_MODE";			break;

	case SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE:		pszText = "SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE";			break;
	case SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN:			pszText = "SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN";			break;
	case SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN:			pszText = "SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN";			break;
	case SYSTEM_SETTINGS_KEY_FONT_TYPE:						pszText = "SYSTEM_SETTINGS_KEY_FONT_TYPE";						break;
	case SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE:			pszText = "SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE";			break;
	case SYSTEM_SETTINGS_KEY_LOCKSCREEN_APP:				pszText = "SYSTEM_SETTINGS_KEY_LOCKSCREEN_APP";					break;
	case SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE:				pszText = "SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE";				break;
	case SYSTEM_SETTINGS_KEY_LOCALE_COUNTRY:				pszText = "SYSTEM_SETTINGS_KEY_LOCALE_COUNTRY";					break;
	case SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE:				pszText = "SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE";				break;
	case SYSTEM_SETTINGS_KEY_LOCALE_TIMEZONE:				pszText = "SYSTEM_SETTINGS_KEY_LOCALE_TIMEZONE";				break;
		//case SYSTEM_SETTINGS_KEY_DISPLAY_SCREEN_MODE:			pszText = "SYSTEM_SETTINGS_KEY_DISPLAY_SCREEN_MODE";			break;
	case SYSTEM_SETTINGS_KEY_DEVICE_NAME:					pszText = "SYSTEM_SETTINGS_KEY_DEVICE_NAME";					break;
	case SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION:			pszText = "SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION";				break;
	case SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION_REPETITION_PERIOD:	pszText = "SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION_REPETITION_PERIOD";		break;

	case SYSTEM_SETTINGS_KEY_FONT_SIZE:						pszText = "SYSTEM_SETTINGS_KEY_FONT_SIZE";						break;
		//case SYSTEM_SETTINGS_KEY_TAP_AND_HOLD_DELAY:			pszText = "SYSTEM_SETTINGS_KEY_TAP_AND_HOLD_DELAY";				break;
	case SYSTEM_SETTINGS_KEY_TIME_CHANGED:					pszText = "SYSTEM_SETTINGS_KEY_TIME_CHANGED";					break;
	case SYSTEM_SETTINGS_KEY_SCREEN_BACKLIGHT_TIME:			pszText = "SYSTEM_SETTINGS_KEY_SCREEN_BACKLIGHT_TIME";			break;
	case SYSTEM_SETTINGS_KEY_ADS_ID:						pszText = "SYSTEM_SETTINGS_KEY_ADS_ID";							break;
	case SYSTEM_SETTINGS_KEY_ACCESSIBILITY_TTS:				pszText = "SYSTEM_SETTINGS_KEY_ACCESSIBILITY_TTS";				break;
	case SYSTEM_SETTINGS_KEY_VIBRATION:						pszText = "SYSTEM_SETTINGS_KEY_VIBRATION";						break;
	case SYSTEM_SETTINGS_KEY_AUTOMATIC_TIME_UPDATE:                          pszText= "SYSTEM_SETTINGS_KEY_AUTOMATIC_TIME_UPDATE";
	break;
	case SYSTEM_SETTINGS_KEY_DEVELOPER_OPTION_STATE:			pszText="SYSTEM_SETTINGS_KEY_DEVELOPER_OPTION_STATE";			break;
	case SYSTEM_SETTINGS_KEY_ACCESSIBILITY_GRAYSCALE:			pszText="SYSTEM_SETTINGS_KEY_ACCESSIBILITY_GRAYSCALE";			break;
	case SYSTEM_SETTINGS_KEY_ACCESSIBILITY_NEGATIVE_COLOR:			pszText="SYSTEM_SETTINGS_KEY_ACCESSIBILITY_NEGATIVE_COLOR";			break;
	}	
	return pszText;
}
/** @} */
