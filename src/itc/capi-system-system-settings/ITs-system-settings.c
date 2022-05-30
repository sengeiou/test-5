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
//& set: SystemSettings

bool g_bSystemSettingsNotSupported = false;
bool g_bSystemSettingsFontNotSupported = false;
bool g_bSystemSettingsTelyphoneyNotSupported = false;
bool g_bSystemSettingsIncomingCallNotSupported = false;
bool g_bSystemSettingsGrayscaleNotSupported = false;
bool g_bSystemSettingsNegativeNotSupported = false;
bool g_bSystemSettingsRotaryNotSupported = false;
/**
* @function 		ITs_system_settings_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_system_settings_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_System_Settings_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bSystemSettingsNotSupported = false;
	g_bSystemSettingsFontNotSupported = false;
	g_bSystemSettingsTelyphoneyNotSupported = false;
	g_bSystemSettingsIncomingCallNotSupported = false;
	g_bSystemSettingsGrayscaleNotSupported = false;
	g_bSystemSettingsNegativeNotSupported = false;
	g_bSystemSettingsRotaryNotSupported = false;

	if ( !TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_FEATURE, API_NAMESPACE) )
	{
		g_bSystemSettingsNotSupported = true;
	}
	if ( !TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_FONT_FEATURE, API_NAMESPACE) )
	{
		g_bSystemSettingsFontNotSupported = true;
	}
	if ( !TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_TELEPHONY_FEATURE, API_NAMESPACE) )
	{
		g_bSystemSettingsTelyphoneyNotSupported = true;
	}
	if (!TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_INCOMING_CALL_FEATURE, API_NAMESPACE) )
	{
		g_bSystemSettingsIncomingCallNotSupported = true;
	}
	if (!TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_ACCESSIBILITY_GRAYSCALE_FEATURE, API_NAMESPACE) )
	{
		g_bSystemSettingsGrayscaleNotSupported = true;
	}
	if (!TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_ACCESSIBILITY_NEGATIVE_FEATURE, API_NAMESPACE) )
	{
		g_bSystemSettingsNegativeNotSupported = true;
	}
	if (!TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_ROTATING_BEZEL_FEATURE, API_NAMESPACE) )
	{
		g_bSystemSettingsRotaryNotSupported = true;
	}
	return;
}

/**
 * @function 		ITs_system_settings_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_system_settings_cleanup(void)
{

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_System_Settings_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

static bool profile_check(char * in_profile)
{
	char *profile_data;
	bool ret_bool = false;
	int ret = system_info_get_platform_string(SYSTEM_SETTINGS_PROFILE_FEATURE, &profile_data);
	if (ret != SYSTEM_INFO_ERROR_NONE)
		return false;

	if (profile_data && !strcmp(profile_data, in_profile))
		ret_bool = true;
	else
		ret_bool = false;

	if (profile_data)
		free(profile_data);

	return ret_bool;

}

/**
 * @function			System_settings_changed_cb_p
 * @description		callback function, called when the system settings change
 * @parameter[IN]	system_settings_key_e key - key name for which settings are changes\n
 *					void *user_data - user data
 * @return			NA
 */
void System_settings_changed_cb_p(system_settings_key_e key, void *user_data)
{
	/*without set, callback wil not hit*/
	/*all setter in under non public api so we are not using in TCs*/
}

/** @addtogroup itc-system-settings-testcases
 *  @brief 		Integration testcases for module system-settings
 *  @ingroup 	itc-system-settings
 *  @{
 */

//& purpose: Get the system settings value associated with the given key as a boolean.
//& type: auto
/**
 * @testcase 			ITc_system_settings_get_value_bool_p
 * @since_tizen			2.3
 * @author            	SRID(parshant.v)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Get the system settings value associated with the given key as a boolean
 * @scenario				Get the system settings value associated with the given key as a boolean
 * @apicovered			system_settings_get_value_bool
 * @passcase				If system_settings_get_value_bool return 0
 * @failcase				If system_settings_get_value_bool return non zero
 * @precondition			NA
 * @postcondition		NA
 */
int ITc_system_settings_get_value_bool_p(void)
{
	START_TEST;
	int nRetVal = SYSTEM_SETTINGS_ERROR_NONE;
	system_settings_key_e eSystem_Settings_Key[]=
	{
		SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION,
		#if IS_DEVICE
		SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED,
		#endif
		SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED,
		SYSTEM_SETTINGS_KEY_LOCALE_TIMEFORMAT_24HOUR,
		SYSTEM_SETTINGS_KEY_SOUND_LOCK,//GET
		SYSTEM_SETTINGS_KEY_SOUND_SILENT_MODE,//GET
		SYSTEM_SETTINGS_KEY_SOUND_TOUCH,
		SYSTEM_SETTINGS_KEY_DISPLAY_SCREEN_ROTATION_AUTO,
		SYSTEM_SETTINGS_KEY_MOTION_ENABLED,
		SYSTEM_SETTINGS_KEY_NETWORK_WIFI_NOTIFICATION,
		SYSTEM_SETTINGS_KEY_NETWORK_FLIGHT_MODE,
		SYSTEM_SETTINGS_KEY_ACCESSIBILITY_TTS,//GET
		SYSTEM_SETTINGS_KEY_VIBRATION,//GET
		SYSTEM_SETTINGS_KEY_AUTOMATIC_TIME_UPDATE, //GET
		SYSTEM_SETTINGS_KEY_DEVELOPER_OPTION_STATE,
		SYSTEM_SETTINGS_KEY_ACCESSIBILITY_GRAYSCALE,
		SYSTEM_SETTINGS_KEY_ACCESSIBILITY_NEGATIVE_COLOR,
		SYSTEM_SETTINGS_KEY_ROTARY_EVENT_ENABLED
	};
	int nEnumSize = sizeof(eSystem_Settings_Key) / sizeof(eSystem_Settings_Key[0]);
	int enum_counter=0;
	bool bGetValue;
	system_settings_key_e key;
	for ( enum_counter=0; enum_counter<nEnumSize; enum_counter++ )
	{
		key = eSystem_Settings_Key[enum_counter];
		nRetVal = system_settings_get_value_bool(key, &bGetValue);// Target APIs
		if(key == SYSTEM_SETTINGS_KEY_NETWORK_WIFI_NOTIFICATION && (!TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_NETWORK_WIFI_FEATURE,API_NAMESPACE)) && (nRetVal == SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED))
		{
			continue;

		}
		if(g_bSystemSettingsNotSupported)
		{
			if ( nRetVal == SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("\\n[Line : %d][%s] Feature Not Supported , error returned = %s", __LINE__, API_NAMESPACE, SystemSettingsGetError(nRetVal));
				return 0;
			}
			else
			{
				FPRINTF("\\n[Line : %d][%s] Feature mismatch , error returned = %s", __LINE__, API_NAMESPACE, SystemSettingsGetError(nRetVal));
				return 1;
			}
		}

		if(g_bSystemSettingsTelyphoneyNotSupported && eSystem_Settings_Key[enum_counter] == SYSTEM_SETTINGS_KEY_AUTOMATIC_TIME_UPDATE)
		{
			if ( nRetVal == SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("\\n[Line : %d][%s] Feature Not Supported , error returned = %s", __LINE__, API_NAMESPACE, SystemSettingsGetError(nRetVal));
				return 0;
			}
			else
			{
				FPRINTF("\\n[Line : %d][%s] Feature mismatch , error returned = %s", __LINE__, API_NAMESPACE, SystemSettingsGetError(nRetVal));
				return 1;
			}
		}

		if(g_bSystemSettingsGrayscaleNotSupported && eSystem_Settings_Key[enum_counter] == SYSTEM_SETTINGS_KEY_ACCESSIBILITY_GRAYSCALE)
		{
			if ( nRetVal == SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("\\n[Line : %d][%s] Feature Not Supported , error returned = %s", __LINE__, API_NAMESPACE, SystemSettingsGetError(nRetVal));
				return 0;
			}
			else
			{
				FPRINTF("\\n[Line : %d][%s] Feature mismatch , error returned = %s", __LINE__, API_NAMESPACE, SystemSettingsGetError(nRetVal));
				return 1;
			}
		}

		if(g_bSystemSettingsNegativeNotSupported && eSystem_Settings_Key[enum_counter] == SYSTEM_SETTINGS_KEY_ACCESSIBILITY_NEGATIVE_COLOR)
		{
			if ( nRetVal == SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("\\n[Line : %d][%s] Feature Not Supported , error returned = %s", __LINE__, API_NAMESPACE, SystemSettingsGetError(nRetVal));
				return 0;
			}
			else
			{
				FPRINTF("\\n[Line : %d][%s] Feature mismatch , error returned = %s", __LINE__, API_NAMESPACE, SystemSettingsGetError(nRetVal));
				return 1;
			}
		}
		if((g_bSystemSettingsRotaryNotSupported || (profile_check(SYSTEM_SETTINGS_WEARABLE_PROFILE) != true)) && eSystem_Settings_Key[enum_counter] == SYSTEM_SETTINGS_KEY_ROTARY_EVENT_ENABLED)
		{
			if ( nRetVal == SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("\\n[Line : %d][%s] Feature Not Supported , error returned = %s", __LINE__, API_NAMESPACE, SystemSettingsGetError(nRetVal));
				return 0;
			}
			else
			{
				FPRINTF("\\n[Line : %d][%s] Feature mismatch , error returned = %s", __LINE__, API_NAMESPACE, SystemSettingsGetError(nRetVal));
				return 1;
			}
		}

		PRINT_RESULT(SYSTEM_SETTINGS_ERROR_NONE, nRetVal, "system_settings_get_value_bool", SystemSettingsGetError(nRetVal));
	}
	return 0;
}

//& purpose: Get the system settings value associated with the given key as a string.
//& type: auto
/**
 * @testcase 			ITc_system_settings_get_value_string_p
 * @since_tizen			2.3
 * @author            	SRID(parshant.v)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Gets the system settings value associated with the given key as a string.
 * @scenario				Gets the system settings value associated with the given key as a string.
 * @apicovered			system_settings_get_value_string
 * @passcase				If system_settings_get_value_string return 0
 * @failcase				If system_settings_get_value_string return non zero
 * @precondition			NA
 * @postcondition		NA
 */
int ITc_system_settings_get_value_string_p(void)
{
	START_TEST;
	int nRetVal = 0;
	char *pszGetPath = NULL;
	system_settings_key_e e_System_Settings_Key[]=
	{
		SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE,
		SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN,
		SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN,
		SYSTEM_SETTINGS_KEY_FONT_TYPE,
		SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE,
		SYSTEM_SETTINGS_KEY_LOCKSCREEN_APP,
		SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE, //GET
		SYSTEM_SETTINGS_KEY_LOCALE_COUNTRY,
		SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE,
		SYSTEM_SETTINGS_KEY_LOCALE_TIMEZONE,
		SYSTEM_SETTINGS_KEY_DEVICE_NAME, //GET
		SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION,
		SYSTEM_SETTINGS_KEY_ADS_ID
			//SYSTEM_SETTINGS_KEY_ULTRA_DATA_SAVE_PKG_LIST

	};
	int nEnumSize = sizeof(e_System_Settings_Key) / sizeof(e_System_Settings_Key[0]);
	int enum_counter=0;
	system_settings_key_e key;
	for ( enum_counter=0; enum_counter<nEnumSize; enum_counter++ )
	{
		key = e_System_Settings_Key[enum_counter];
		nRetVal = system_settings_get_value_string(key, &pszGetPath);// Target APIs

		if(key == SYSTEM_SETTINGS_KEY_LOCKSCREEN_APP || key == SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN && (!TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_LOCK_SCREEN_FEATURE, API_NAMESPACE)) )
		{
			continue;
		}

		if(key == SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE && (!TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_NOTIFICATION_EMAIL_FEATURE, API_NAMESPACE)) )
		{
			continue;
		}

		if( g_bSystemSettingsNotSupported ||
				(g_bSystemSettingsFontNotSupported && (key == SYSTEM_SETTINGS_KEY_FONT_TYPE || key == SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE)) ||
				(g_bSystemSettingsIncomingCallNotSupported && (key == SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE))
		  )
		{
			if ( nRetVal == SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("\\n[Line : %d][%s] Feature Not Supported , error returned = %s", __LINE__, API_NAMESPACE, SystemSettingsGetError(nRetVal));
				FREE_MEMORY(pszGetPath);
				return 0;
			}
			else
			{
				FPRINTF("\\n[Line : %d][%s] Feature mismatch , error returned = %s", __LINE__, API_NAMESPACE, SystemSettingsGetError(nRetVal));
				FREE_MEMORY(pszGetPath);
				return 1;
			}
		}
		PRINT_RESULT(SYSTEM_SETTINGS_ERROR_NONE, nRetVal, "system_settings_get_value_string", SystemSettingsGetError(nRetVal));
		CHECK_VALUE_STRING(pszGetPath, "system_settings_get_value_string"); //It will free string also
	}
	return 0;
}

//& purpose: Gets the system settings value associated with the given key as an integer.
//& type: auto
/**
 * @testcase 			ITc_system_settings_get_value_int_p
 * @since_tizen			2.3
 * @author            	SRID(parshant.v)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Gets the system settings value associated with the given key as an integer.
 * @scenario				Gets the system settings value associated with the given key as an integer.
 * @apicovered			system_settings_get_value_int
 * @passcase				If system_settings_get_value_int return 0
 * @failcase				If system_settings_get_value_int return non zero
 * @precondition			NA
 * @postcondition		NA
 */
int ITc_system_settings_get_value_int_p(void)
{
	START_TEST;
	int nRetVal = 0, nGetValue = -1;
	system_settings_key_e e_System_Settings_Key[]=
	{
		SYSTEM_SETTINGS_KEY_FONT_SIZE,
		SYSTEM_SETTINGS_KEY_TIME_CHANGED,
		SYSTEM_SETTINGS_KEY_SCREEN_BACKLIGHT_TIME,
		SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION_REPETITION_PERIOD,
		SYSTEM_SETTINGS_KEY_LOCK_STATE,
		SYSTEM_SETTINGS_KEY_ULTRA_DATA_SAVE
	};
	int nEnumSize = sizeof(e_System_Settings_Key) / sizeof(e_System_Settings_Key[0]);
	int enum_counter=0;
	system_settings_key_e key;
	for ( enum_counter=0; enum_counter<nEnumSize; enum_counter++ )
	{
		key = e_System_Settings_Key[enum_counter];
		nGetValue=-1;
		nRetVal = system_settings_get_value_int(key, &nGetValue);// Target APIs
		if((g_bSystemSettingsFontNotSupported && e_System_Settings_Key[enum_counter] == SYSTEM_SETTINGS_KEY_FONT_SIZE) || (g_bSystemSettingsTelyphoneyNotSupported && e_System_Settings_Key[enum_counter] == SYSTEM_SETTINGS_KEY_ULTRA_DATA_SAVE))
		{
			if ( nRetVal == SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("\\n[Line : %d][%s] Feature Not Supported , error returned = %s", __LINE__, API_NAMESPACE, SystemSettingsGetError(nRetVal));
				continue;
			}
			else
			{
				FPRINTF("\\n[Line : %d][%s] Feature mismatch , error returned = %s", __LINE__, API_NAMESPACE, SystemSettingsGetError(nRetVal));
				return 1;
			}

		}
		PRINT_RESULT(SYSTEM_SETTINGS_ERROR_NONE, nRetVal, "system_settings_get_value_int", SystemSettingsGetError(nRetVal));

		if ( nGetValue == -1 )
		{
			FPRINTF("[Line : %d][%s] system_settings_get_value_int failed, output value is not valid\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	return 0;
}

//& purpose: Registers and Unregister a change event callback for the given system settings key
//& type: auto
/**
 * @testcase 			ITc_system_settings_set_unset_changed_cb_p
 * @since_tizen			2.3
 * @author				SRID(parshant.v)
 * @reviewer				SRID(gupta.sanjay)
 * @type 				auto
 * @description			Registers and Unregister a change event callback for the given system settings key
 * @scenario				Registers and Unregister a change event callback for the given system settings key
 * @apicovered			system_settings_set_changed_cb, system_settings_unset_changed_cb
 * @passcase				If system_settings_set_changed_cb and system_settings_unset_changed_cb return 0
 * @failcase				If system_settings_set_changed_cb or system_settings_unset_changed_cb return non zero
 * @precondition			NA
 * @postcondition		NA
 */
int ITc_system_settings_set_unset_changed_cb_p(void)
{
	START_TEST;

	int nRetVal = -1;
	void *pvUserData = "User data";

	system_settings_key_e e_System_Settings_Key[]=
	{
		SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION,
		SYSTEM_SETTINGS_KEY_ACCESSIBILITY_GRAYSCALE,
		SYSTEM_SETTINGS_KEY_ACCESSIBILITY_NEGATIVE_COLOR
	};
	int nEnumSize = sizeof(e_System_Settings_Key) / sizeof(e_System_Settings_Key[0]);
	int enum_counter=0;
	system_settings_key_e key;
	for ( enum_counter=0; enum_counter<nEnumSize; enum_counter++ )
	{
		key = e_System_Settings_Key[enum_counter];

		nRetVal = system_settings_set_changed_cb(key,System_settings_changed_cb_p, pvUserData);//target api//register callback
		if ( nRetVal != SYSTEM_SETTINGS_ERROR_NONE && nRetVal != SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("\\n[Line : %d][%s] system_settings_set_changed_cb failed , error returned = %s", __LINE__, API_NAMESPACE, SystemSettingsGetError(nRetVal));
			return 1;
		}
		//Unregisters the callback function.
		nRetVal = system_settings_unset_changed_cb(key);//target api//unregister callback
		if ( nRetVal != SYSTEM_SETTINGS_ERROR_NONE && nRetVal != SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("\\n[Line : %d][%s] system_settings_unset_changed_cb failed , error returned = %s", __LINE__, API_NAMESPACE, SystemSettingsGetError(nRetVal));
			return 1;
		}
	}

	return 0;
}

/**
 * @function			System_settings_changed_add_remove_cb
 * @description		callback function, called when the system settings change
 * @parameter[IN]	system_settings_key_e key - key name for which settings are changes\n
 *					void *user_data - user data
 * @return			NA
 */
void System_settings_changed_add_remove_cb(system_settings_key_e key, void *user_data)
{

}

//& purpose: Adds and remove a change event callback for the given system settings key
//& type: auto
/**
 * @testcase 			ITc_system_settings_set_unset_changed_cb_p
 * @since_tizen			5.0
 * @author				SRID(shilpa.j)
 * @reviewer				SRID(a.pandia1)
 * @type 				auto
 * @description			Add and Remove a change event callback for the given system settings key
 * @scenario				Add and Remove a change event callback for the given system settings key
 * @apicovered			system_settings_add_changed_cb, system_settings_remove_changed_cb
 * @passcase				If system_settings_add_changed_cb and system_settings_remove_changed_cb return 0
 * @failcase				If system_settings_add_changed_cb or system_settings_remove_changed_cb return non zero
 * @precondition			NA
 * @postcondition		NA
 */
int ITc_system_settings_add_remove_changed_cb_p(void)
{
	int nRetVal = 0;
	int nkey_idx = 0;

	for (nkey_idx = SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE; nkey_idx < SYSTEM_SETTINGS_KEY_MAX ; nkey_idx++)
	{

		if(nkey_idx == SYSTEM_SETTINGS_KEY_NETWORK_WIFI_NOTIFICATION && (!TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_NETWORK_WIFI_FEATURE,API_NAMESPACE)))
		{
			continue;
		}
		if(nkey_idx == SYSTEM_SETTINGS_KEY_FONT_TYPE  || nkey_idx == SYSTEM_SETTINGS_KEY_FONT_SIZE  && (!TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_FONT_FEATURE, API_NAMESPACE)) )
		{
			continue;
		}

		if(nkey_idx == SYSTEM_SETTINGS_KEY_LOCKSCREEN_APP || nkey_idx == SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN && (!TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_LOCK_SCREEN_FEATURE, API_NAMESPACE)) )
		{
			continue;
		}
		if(nkey_idx == SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE  || nkey_idx == SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION && (!TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_INCOMING_CALL_FEATURE, API_NAMESPACE)) )
		{
			continue;
		}

		if(nkey_idx == SYSTEM_SETTINGS_KEY_ULTRA_DATA_SAVE_PKG_LIST || nkey_idx == SYSTEM_SETTINGS_KEY_ULTRA_DATA_SAVE && (!TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_TELEPHONY_FEATURE, API_NAMESPACE)) )
		{
			continue;
		}

		if(nkey_idx == SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN && (!TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_WALLPAPER_HOME_SCREEN_FEATURE, API_NAMESPACE)) )
		{
			continue;
		}

		if(nkey_idx == SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE && (!TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_NOTIFICATION_EMAIL_FEATURE, API_NAMESPACE)) )
		{
			continue;
		}

		if ( nkey_idx == (SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED + 1) || nkey_idx == SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE )
			continue;

		if(nkey_idx == SYSTEM_SETTINGS_KEY_AUTOMATIC_TIME_UPDATE && ((!TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_TELEPHONY_FEATURE, API_NAMESPACE)) || (!TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_FONT_FEATURE, API_NAMESPACE) )))
		{
			continue;
		}
		if(nkey_idx == SYSTEM_SETTINGS_KEY_ACCESSIBILITY_GRAYSCALE && (!TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_ACCESSIBILITY_GRAYSCALE_FEATURE, API_NAMESPACE)) )
		{
			continue;
		}
		if(nkey_idx == SYSTEM_SETTINGS_KEY_ACCESSIBILITY_NEGATIVE_COLOR && (!TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_ACCESSIBILITY_NEGATIVE_FEATURE, API_NAMESPACE)) )
		{
			continue;
		}
		if(nkey_idx == SYSTEM_SETTINGS_KEY_ROTARY_EVENT_ENABLED && (((!TCTCheckSystemInfoFeatureSupported(SYSTEM_SETTINGS_ROTATING_BEZEL_FEATURE, API_NAMESPACE)) || (profile_check(SYSTEM_SETTINGS_WEARABLE_PROFILE) != true))))
		{
			continue;
		}

		nRetVal = system_settings_add_changed_cb(nkey_idx,System_settings_changed_add_remove_cb, NULL);

		if(g_bSystemSettingsNotSupported)
		{
			if ( nRetVal == SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("\\n[Line : %d][%s] Feature Not Supported , error returned = %s", __LINE__, API_NAMESPACE, SystemSettingsGetError(nRetVal));
				return 0;
			}
			else
			{
				FPRINTF("\\n[Line : %d][%s] Feature mismatch , error returned = %s", __LINE__, API_NAMESPACE, SystemSettingsGetError(nRetVal));
				return 1;
			}
		}
		PRINT_RESULT(SYSTEM_SETTINGS_ERROR_NONE, nRetVal, "system_settings_add_changed_cb", SystemSettingsGetError(nRetVal));

		nRetVal = system_settings_remove_changed_cb(nkey_idx,System_settings_changed_add_remove_cb);
		PRINT_RESULT(SYSTEM_SETTINGS_ERROR_NONE, nRetVal, "system_settings_remove_changed_cb", SystemSettingsGetError(nRetVal));
	}

	return 0;
}

/** @} */
/** @} */
