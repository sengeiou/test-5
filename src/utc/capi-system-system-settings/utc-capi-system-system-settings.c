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
#include "assert.h"
#include "system_settings.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>
#include <storage.h>
#include <dlog.h>

#define API_NAMESPACE   "SYSTEM_SETTINGS_UTC"
#define SYSTEM_SETTINGS_WERABLE_PROFILE "wearable"

#define SYSTEM_SETTINGS_PROFILE_FEATURE	"http://tizen.org/feature/profile"
#define SYSTEM_SETTINGS_NETWORK_WIFI_FEATURE  "http://tizen.org/feature/network.wifi"
#define SYSTEM_SETTINGS_WALLPAPER_HOME_SCREEN_FEATURE "http://tizen.org/feature/systemsetting.home_screen"
#define SYSTEM_SETTINGS_LOCK_SCREEN_FEATURE "http://tizen.org/feature/systemsetting.lock_screen"
#define SYSTEM_SETTINGS_NOTIFICATION_EMAIL_FEATURE "http://tizen.org/feature/systemsetting.notification_email"
#define SYSTEM_SETTINGS_TELEPHONY_FEATURE "http://tizen.org/feature/network.telephony"
#define SYSTEM_SETTINGS_INCOMING_CALL_FEATURE "http://tizen.org/feature/systemsetting.incoming_call"
#define SYSTEM_SETTINGS_FONT_FEATURE "http://tizen.org/feature/systemsetting.font"
#define SYSTEM_SETTINGS_GRAYSCALE_FEATURE "http://tizen.org/feature/accessibility.grayscale"
#define SYSTEM_SETTINGS_NEGATIVE_FEATURE "http://tizen.org/feature/accessibility.negative"
#define SYSTEM_SETTINGS_ROTATING_BEZEL_FEATURE "http://tizen.org/feature/input.rotating_bezel"


#define IF_FEATURE_CHECK_SKIP(VAR,SYSTEM_SETTING_KEY, FEATURE)  \
        if((VAR == SYSTEM_SETTING_KEY) && (!TCTCheckSystemInfoFeatureSupported(FEATURE,API_NAMESPACE))){ \
			continue; \
		}

#define IF_FEATURE_PROFILE_CHECK_SKIP(VAR, SYSTEM_SETTING_KEY, PROFILE, FEATURE)  \
        if((VAR == SYSTEM_SETTING_KEY) && ((profile_check(PROFILE) != true) || (!TCTCheckSystemInfoFeatureSupported(FEATURE,API_NAMESPACE)))){ \
			continue; \
		}

#define IF_FEATURE_CHECK_RETURN(VAR, FEATURE)  \
	if (VAR == SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED) { \
		if(TCTCheckSystemInfoFeatureSupported(FEATURE, API_NAMESPACE)) { \
			FPRINTF("[Line : %d][%s] Feature is supported but it returned SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED!! check it!!\\n", __LINE__, #FEATURE ); \
			return 1; \
		} \
	}

#define IF_PROFILE_CHECK_RETURN(VAR, PROFILE, FEATURE)  \
	if (VAR == SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED) { \
		if (profile_check(PROFILE) == true && TCTCheckSystemInfoFeatureSupported(FEATURE, API_NAMESPACE)) { \
			FPRINTF("[Line : %d] Wearable profile and %s Feature is supported but it returned SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED!! check it!!\\n", __LINE__, FEATURE); \
			return 1; \
		} else { \
			FPRINTF("[Line : %d] Wearable profile is not supported\\n", __LINE__); \
		} \
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


static int my_assert_ret(int retcode)
{
	if (retcode == SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED) {
		assert_eq(retcode, SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(retcode, SYSTEM_SETTINGS_ERROR_NONE);
	}
	return 1;
}

static bool _callback_called = false;

/**
 * @function		utc_system_settings_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_system_settings_startup(void)
{
}

/**
 * @function		utc_system_settings_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_system_settings_cleanup(void)
{
}


static void utc_system_settings_changed_callback(system_settings_key_e key, void *user_data)
{
	_callback_called = true;
}


/**
 * TEST GETTING SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE
 */
/**
 * @testcase		utc_system_settings_get_value_string_p1
 * @since_tizen		2.3
 * @description		check if SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE is able to get the property
 */
int utc_system_settings_get_value_string_p1(void)
{
	char *value = NULL;

	int retcode = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE, &value);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_FONT_FEATURE);
	my_assert_ret(retcode);
	if (retcode == SYSTEM_SETTINGS_ERROR_NONE) {
		assert(value != NULL);
		free(value);
	}

	return 0;
}

/**
 * TEST GETTING SYSTEM_SETTINGS_KEY_LOCALE_COUNTRY
 */
/**
 * @testcase		utc_system_settings_get_value_string_p2
 * @since_tizen		2.3
 * @description		check if SYSTEM_SETTINGS_KEY_LOCALE_COUNTRY is able to get the property
 */
int utc_system_settings_get_value_string_p2(void)
{
	char *value = NULL;

	int retcode = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_COUNTRY, &value);
	assert_eq(retcode, SYSTEM_SETTINGS_ERROR_NONE);
	assert(value != NULL);
	free(value);
	return 0;
}

/**
 * TEST GETTING SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE
 */
/**
 * @testcase		utc_system_settings_get_value_string_p3
 * @since_tizen		2.3
 * @description		check if SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE is able to get the property
 */
int utc_system_settings_get_value_string_p3(void)
{
	char *value = NULL;

	int retcode = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &value);
	assert_eq(retcode, SYSTEM_SETTINGS_ERROR_NONE);
	assert(value != NULL);
	free(value);
	return 0;
}

/**
 * TEST GETTING SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE
 */
/**
 * @testcase		utc_system_settings_get_value_string_p4
 * @since_tizen		2.3
 * @description		check if SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE is able to get the property
 */
int utc_system_settings_get_value_string_p4(void)
{
	char *value = NULL;

	int retcode = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE, &value);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_INCOMING_CALL_FEATURE);
	my_assert_ret(retcode);
	free(value);
	return 0;
}

/**
 * TEST SETTING SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN
 */
/**
 * @testcase		utc_system_settings_get_value_string_p5
 * @since_tizen		2.3
 * @description		check if SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN is able to get the property.
 */
int utc_system_settings_get_value_string_p5(void)
{
	char *value = NULL;

	int retcode = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN, &value);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_WALLPAPER_HOME_SCREEN_FEATURE);
	my_assert_ret(retcode);
	free(value);
	return 0;
}

/**
 * @testcase		utc_system_settings_get_value_string_p11
 * @since_tizen		2.3
 * @description		check if SYSTEM_SETTINGS_KEY_DEVICE_NAME is able to get the property.
 */
int utc_system_settings_get_value_string_p11(void)
{
	char *value = NULL;

	int retcode = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_DEVICE_NAME, &value);
	assert_eq(retcode, SYSTEM_SETTINGS_ERROR_NONE);
	assert(value != NULL);
	free(value);
	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_string_p7
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION is able to get the property.
 */
int utc_system_settings_get_value_string_p7(void)
{
	char *value = NULL;

	int retcode = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION, &value);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_INCOMING_CALL_FEATURE);
	my_assert_ret(retcode);
	free(value);
	return 0;
}

/**
 * @testcase		utc_system_settings_get_value_string_p6
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_LOCALE_TIMEZON is able to get the property.
 */
int utc_system_settings_get_value_string_p6(void)
{
	char *value = NULL;
	int retcode = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_TIMEZONE, &value);
	my_assert_ret(retcode);
	free(value);
	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_string_p10
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN is able to get the property.
 */
int utc_system_settings_get_value_string_p10(void)
{
	char *value = NULL;

	int retcode = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN, &value);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_LOCK_SCREEN_FEATURE);
	my_assert_ret(retcode);
	free(value);
	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_string_p8
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_FONT_TYPE is able to get the property.
 */
int utc_system_settings_get_value_string_p8(void)
{
	char *value = NULL;

	int retcode = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_FONT_TYPE, &value);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_FONT_FEATURE);

	my_assert_ret(retcode);
	if (retcode == SYSTEM_SETTINGS_ERROR_NONE) {
		assert(value != NULL);
		free(value);
	}

	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_string_p9
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE is able to get the property.
 */
int utc_system_settings_get_value_string_p9(void)
{
	char *value = NULL;

	int retcode = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE, &value);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_NOTIFICATION_EMAIL_FEATURE);
	my_assert_ret(retcode);
	free(value);
	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_string_n
 * @since_tizen		2.3
 * @description		check if system_settings_get_value_string is able to handle invalid parameters.
 */
int utc_system_settings_get_value_string_n(void)
{
	int retcode = system_settings_get_value_string(-1, NULL);
	assert_neq(retcode, SYSTEM_SETTINGS_ERROR_NONE);
	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_bool_p1
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_NETWORK_WIFI_NOTIFICATION is able to get the property.
 */
int utc_system_settings_get_value_bool_p1(void)
{
	bool value = false;

	int retcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_NETWORK_WIFI_NOTIFICATION, &value);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_NETWORK_WIFI_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_bool_p2
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED is able to get the property.
 */
int utc_system_settings_get_value_bool_p2(void)
{
	bool value = false;

	int retcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED, &value);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_bool_p3
 * @since_tizen		2.3
 * @description
 * @description     check if SYSTEM_SETTINGS_KEY_SOUND_LOCK is able to get the property.
 */
int utc_system_settings_get_value_bool_p3(void)
{
	bool value = false;

	int retcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_SOUND_LOCK, &value);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_bool_p4
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_DISPLAY_SCREEN_ROTATION_AUTO is able to get the property.
 */
int utc_system_settings_get_value_bool_p4(void)
{
	bool value = false;

	int retcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_DISPLAY_SCREEN_ROTATION_AUTO, &value);
	my_assert_ret(retcode);
	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_bool_p5
 * @since_tizen		2.3
 * 					check if SYSTEM_SETTINGS_KEY_SOUND_TOUCH is able to get the property.
 */
int utc_system_settings_get_value_bool_p5(void)
{
	bool value = false;

	int retcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_SOUND_TOUCH, &value);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_bool_p6
 * @since_tizen		2.3
 * 					check if SYSTEM_SETTINGS_KEY_SOUND_SILENT_MODE is able to get the property.
 */
int utc_system_settings_get_value_bool_p6(void)
{
	bool value = false;

	int retcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_SOUND_SILENT_MODE, &value);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_bool_p7
 * @since_tizen		2.3
 * 					check if SYSTEM_SETTINGS_KEY_NETWORK_FLIGHT_MODE is able to get the property.
 */
int utc_system_settings_get_value_bool_p7(void)
{
	bool value = false;

	int retcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_NETWORK_FLIGHT_MODE, &value);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_bool_p8
 * @since_tizen		2.3
 * 					check if SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION is able to get the property.
 */
int utc_system_settings_get_value_bool_p8(void)
{
	bool value = false;

	int retcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION, &value);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_bool_p9
 * @since_tizen		2.3
 * @description		check if SYSTEM_SETTINGS_KEY_MOTION_ENABLED is able to get the property.
 */
int utc_system_settings_get_value_bool_p9(void)
{
	bool value = false;

	int retcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_MOTION_ENABLED, &value);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_bool_p10
 * @since_tizen		2.3
 * @description		check if SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED is able to get the property.
 */
int utc_system_settings_get_value_bool_p10(void)
{
	bool value = false;

	int retcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED, &value);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_bool_n
 * @since_tizen		2.3
 * @description		check if system_settings_get_value_bool is able to handle invalid parameters.
 */
int utc_system_settings_get_value_bool_n(void)
{
	int retcode = system_settings_get_value_bool(-1, NULL);
	assert_neq(retcode, SYSTEM_SETTINGS_ERROR_NONE);
	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_int_p1
 * @since_tizen		2.3
 * @description		check if SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION_REPETITION_PERIOD is able to get the property.
 */
int utc_system_settings_get_value_int_p1(void)
{
	int value = 0;

	int retcode = system_settings_get_value_int(SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION_REPETITION_PERIOD, &value);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_int_p2
 * @since_tizen		2.3
 * @description		check if SYSTEM_SETTINGS_KEY_FONT_SIZE is able to get the property.
 */
int utc_system_settings_get_value_int_p2(void)
{
	int font_size = 0;

	int retcode = system_settings_get_value_int(SYSTEM_SETTINGS_KEY_FONT_SIZE, &font_size);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_FONT_FEATURE);

	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_n
 * @since_tizen		2.3
 * @description		check if system_settings_get_value_int is able to handle invalid parameters.
 */
int utc_system_settings_get_value_n(void)
{
	int retcode = system_settings_get_value_int(-1, NULL);
	assert_neq(retcode, SYSTEM_SETTINGS_ERROR_NONE);
	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_int_p3
 * @since_tizen		2.3
 * @description		check if SYSTEM_SETTINGS_KEY_SCREEN_BACKLIGHT_TIME is able to get the property.
 */
int utc_system_settings_get_value_int_p3(void)
{
	int value;
	int nRetVal =  system_settings_get_value_int(SYSTEM_SETTINGS_KEY_SCREEN_BACKLIGHT_TIME, &value);
	my_assert_ret(nRetVal);
	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_bool_p11
 * @since_tizen		2.3
 * @description		check if SYSTEM_SETTINGS_KEY_LOCALE_TIMEFORMAT_24HOUR is able to get the property
 */
int utc_system_settings_get_value_bool_p11(void)
{
	bool value = false;

	int retcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_LOCALE_TIMEFORMAT_24HOUR, &value);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_bool_p12
 * @since_tizen		4.0
 * @description		check if SYSTEM_SETTINGS_KEY_ACCESSIBILITY_TTS is able to get the property
 */
int utc_system_settings_get_value_bool_p12(void)
{
	bool value = false;

	int retcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_ACCESSIBILITY_TTS, &value);
	my_assert_ret(retcode);

	return 0;
}

/**
 * @testcase		utc_system_settings_get_value_bool_p13
 * @since_tizen		4.0
 * @description		check if SYSTEM_SETTINGS_KEY_VIBRATION is able to get the property
 */
int utc_system_settings_get_value_bool_p13(void)
{
	bool value = false;

	int retcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_VIBRATION, &value);
	my_assert_ret(retcode);

	return 0;
}

/**
 * @testcase		utc_system_settings_get_value_bool_p14
 * @since_tizen		5.0
 * @description		check if SYSTEM_SETTINGS_KEY_AUTOMATIC_TIME_UPDATE is able to get the property
 */
int utc_system_settings_get_value_bool_p14(void)
{
	bool value = false;

	int retcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_AUTOMATIC_TIME_UPDATE, &value);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_TELEPHONY_FEATURE);
	my_assert_ret(retcode);

	return 0;
}

/**
 * @testcase		utc_system_settings_get_value_bool_p15
 * @since_tizen		5.0
 * @description		check if SYSTEM_SETTINGS_KEY_DEVELOPER_OPTION_STATE is able to get the property
 */
int utc_system_settings_get_value_bool_p15(void)
{
	bool value = false;

	int retcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_DEVELOPER_OPTION_STATE, &value);
	my_assert_ret(retcode);

	return 0;
}

/**
 * @testcase		utc_system_settings_get_value_bool_p16
 * @since_tizen		5.5
 * @description		check if SYSTEM_SETTINGS_KEY_ACCESSIBILITY_GRAYSCALE is able to get the property
 */
int utc_system_settings_get_value_bool_p16(void)
{
	bool value = false;

	int retcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_ACCESSIBILITY_GRAYSCALE, &value);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_GRAYSCALE_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_get_value_bool_p17
 * @since_tizen		5.5
 * @description		check if SYSTEM_SETTINGS_KEY_ACCESSIBILITY_NEGATIVE_COLOR is able to get the property
 */
int utc_system_settings_get_value_bool_p17(void)
{
	bool value = false;

	int retcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_ACCESSIBILITY_NEGATIVE_COLOR, &value);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_NEGATIVE_FEATURE);
	my_assert_ret(retcode);

	return 0;
}

/**
 * @testcase		utc_system_settings_get_value_bool_p18
 * @since_tizen		5.5
 * @description		check if SYSTEM_SETTINGS_KEY_ROTARY_EVENT_ENABLED is able to get the property
 */
int utc_system_settings_get_value_bool_p18(void)
{
	bool value = false;

	int retcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_ROTARY_EVENT_ENABLED, &value);
	IF_PROFILE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_WERABLE_PROFILE, SYSTEM_SETTINGS_ROTATING_BEZEL_FEATURE);

	my_assert_ret(retcode);

	return 0;
}

/**
 * @testcase		utc_system_settings_set_changed_cb_p1
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p1(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_INCOMING_CALL_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p1
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION is able to set the callback for change-notification.
 * 				    check if SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p1(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p2
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p2(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_INCOMING_CALL_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p2
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE is able to set the callback for change-notification.
 * 				    check if SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p2(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE,
												 utc_system_settings_changed_callback, NULL);

	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_INCOMING_CALL_FEATURE);
	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE);

	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_INCOMING_CALL_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p3
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p3(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_WALLPAPER_HOME_SCREEN_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p3
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN is able to set the callback for change-notification.
 * 				    check if SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p3(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN,
												 utc_system_settings_changed_callback, NULL);

	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_WALLPAPER_HOME_SCREEN_FEATURE);
	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_WALLPAPER_HOME_SCREEN_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p4
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p4(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_LOCK_SCREEN_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_LOCK_SCREEN_unset_changed_cb_p
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_WALLPAPER is able to set the callback for change-notification.
 * 				    check if SYSTEM_SETTINGS_KEY_WALLPAPER is able to unset the callback for change-notification.
 */
int utc_system_settings_LOCK_SCREEN_unset_changed_cb_p(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN,
												 utc_system_settings_changed_callback, NULL);

	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_LOCK_SCREEN_FEATURE);
	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_LOCK_SCREEN_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p5
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_FONT_SIZE is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p5(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_FONT_SIZE,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_FONT_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p4
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_FONT_SIZE is able to set the callback for change-notification.
 * 				    check if SYSTEM_SETTINGS_KEY_FONT_SIZE is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p4(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_FONT_SIZE,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_FONT_FEATURE);

	my_assert_ret(retcode);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_FONT_SIZE);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_FONT_FEATURE);

	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p6
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_FONT_TYPE is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p6(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_FONT_TYPE,
												 utc_system_settings_changed_callback, NULL);

	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_FONT_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p5
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_FONT_TYPE is able to set the callback for change-notification.
 * 				    check if SYSTEM_SETTINGS_KEY_FONT_TYPE is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p5(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_FONT_TYPE,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_FONT_FEATURE);

	my_assert_ret(retcode);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_FONT_TYPE);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_FONT_FEATURE);


	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p7
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p7(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_NOTIFICATION_EMAIL_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p6
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p6(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE,
												 utc_system_settings_changed_callback, NULL);

	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_NOTIFICATION_EMAIL_FEATURE);
	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_NOTIFICATION_EMAIL_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p8
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p8(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p7
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p7(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p9
 * @since_tizen		2.3
 * @description		check if SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED is able to set callback for getting notification of change
 */
int utc_system_settings_set_changed_cb_p9(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p8
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p8(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p10
 * @since_tizen		2.3
 * @description		check if SYSTEM_SETTINGS_KEY_LOCKSCREEN_APP is able to set callback for getting notification of change
 */
int utc_system_settings_set_changed_cb_p10(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_LOCKSCREEN_APP,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_LOCK_SCREEN_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p9
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_LOCKSCREEN_APP is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_LOCKSCREEN_APP is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p9(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_LOCKSCREEN_APP,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_LOCK_SCREEN_FEATURE);
	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_LOCKSCREEN_APP);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_LOCK_SCREEN_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p11
 * @since_tizen		2.3
 * @description		check if SYSTEM_SETTINGS_KEY_LOCALE_COUNTRY is able to set callback for getting notification of change
 */
int utc_system_settings_set_changed_cb_p11(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_LOCALE_COUNTRY,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p10
 * @since_tizen		2.3
 * @description		check if SYSTEM_SETTINGS_KEY_LOCALE_COUNTRY is able to set callback for getting notification of change and unset doing
 */
int utc_system_settings_unset_changed_cb_p10(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_LOCALE_COUNTRY,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_LOCALE_COUNTRY);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p12
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p12(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p11
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p11(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p13
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_LOCALE_TIMEFORMAT_24HOUR is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p13(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_LOCALE_TIMEFORMAT_24HOUR,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * SYSTEM_SETTINGS_KEY_LOCALE_TIMEFORMAT_24HOUR
 */
/**
 * @testcase		utc_system_settings_unset_changed_cb_p12
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_LOCALE_TIMEFORMAT_24HOUR is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_LOCALE_TIMEFORMAT_24HOUR is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p12(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_LOCALE_TIMEFORMAT_24HOUR,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_LOCALE_TIMEFORMAT_24HOUR);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p14
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_TIME_CHANGED is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p14(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_TIME_CHANGED,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p13
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_TIME_CHANGED is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_TIME_CHANGED is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p13(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_TIME_CHANGED,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_TIME_CHANGED);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p15
 * @since_tizen		2.3
 * @description     check if  SYSTEM_SETTINGS_KEY_SOUND_LOCK is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p15(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_SOUND_LOCK,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p14
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_SOUND_LOCK is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_SOUND_LOCK is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p14(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_SOUND_LOCK,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_SOUND_LOCK);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p16
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_SOUND_SILENT_MODE is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p16(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_SOUND_SILENT_MODE,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p15
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_SOUND_SILENT_MODE is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_SOUND_SILENT_MODE is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p15(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_SOUND_SILENT_MODE,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_SOUND_SILENT_MODE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p17
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_SOUND_TOUCH is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p17(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_SOUND_TOUCH,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p16
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_SOUND_TOUCH is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_SOUND_TOUCH is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p16(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_SOUND_TOUCH,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_SOUND_TOUCH);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p18
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_DISPLAY_SCREEN_ROTATION_AUTO is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p18(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_DISPLAY_SCREEN_ROTATION_AUTO,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p17
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_DISPLAY_SCREEN_ROTATION_AUTO is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_DISPLAY_SCREEN_ROTATION_AUTO is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p17(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_DISPLAY_SCREEN_ROTATION_AUTO,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_DISPLAY_SCREEN_ROTATION_AUTO);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p19
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_SCREEN_BACKLIGHT_TIME is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p19(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_SCREEN_BACKLIGHT_TIME,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p18
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_SCREEN_BACKLIGHT_TIME is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_SCREEN_BACKLIGHT_TIME is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p18(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_SCREEN_BACKLIGHT_TIME,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_SCREEN_BACKLIGHT_TIME);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p20
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p20(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_INCOMING_CALL_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p19
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p19(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_INCOMING_CALL_FEATURE);
	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_INCOMING_CALL_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p21
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION_REPETITION_PERIOD is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p21(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION_REPETITION_PERIOD,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p20
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION_REPETITION_PERIOD is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION_REPETITION_PERIOD is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p20(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION_REPETITION_PERIOD,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION_REPETITION_PERIOD);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p22
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_DEVICE_NAME is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p22(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_DEVICE_NAME,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p21
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_DEVICE_NAME is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_DEVICE_NAME  is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p21(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_DEVICE_NAME,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_DEVICE_NAME);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p23
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_MOTION_ENABLED is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p23(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_MOTION_ENABLED,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p22
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_MOTION_ENABLED is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_MOTION_ENABLED is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p22(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_MOTION_ENABLED,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_MOTION_ENABLED);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p24
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_NETWORK_FLIGHT_MODE is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p24(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_NETWORK_FLIGHT_MODE,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p23
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_NETWORK_FLIGHT_MODE is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_NETWORK_FLIGHT_MODE is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p23(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_NETWORK_FLIGHT_MODE,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_NETWORK_FLIGHT_MODE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p25
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_NETWORK_WIFI_NOTIFICATION is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p25(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_NETWORK_WIFI_NOTIFICATION,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_NETWORK_WIFI_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p24
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_NETWORK_WIFI_NOTIFICATION is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_NETWORK_WIFI_NOTIFICATION is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p24(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_NETWORK_WIFI_NOTIFICATION,
												 utc_system_settings_changed_callback, NULL);

	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_NETWORK_WIFI_FEATURE);
	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_NETWORK_WIFI_NOTIFICATION);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_NETWORK_WIFI_FEATURE);
	my_assert_ret(retcode);

	return 0;
}

/**
 * @testcase		utc_system_settings_set_changed_cb_p27
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_LOCK_STATE is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p27(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_LOCK_STATE,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p26
 * @since_tizen		2.3
 * @description     check if SYSTEM_SETTINGS_KEY_LOCK_STATE is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_LOCK_STATE is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p26(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_LOCK_STATE,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_LOCK_STATE);
	my_assert_ret(retcode);

	return 0;
}

/**
 * @testcase		utc_system_settings_set_changed_cb_p29
 * @since_tizen		3.0
 * @description     check if SYSTEM_SETTINGS_KEY_ADS_ID is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p29(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_ADS_ID,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p28
 * @since_tizen		3.0
 * @description     check if SYSTEM_SETTINGS_KEY_ADS_ID is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_ADS_ID is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p28(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_ADS_ID,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_ADS_ID);
	my_assert_ret(retcode);

	return 0;
}

/**
 * @testcase		utc_system_settings_set_changed_cb_p31
 * @since_tizen		3.0
 * @description     check if SYSTEM_SETTINGS_KEY_ULTRA_DATA_SAVE is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p31(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_ULTRA_DATA_SAVE,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_TELEPHONY_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p30
 * @since_tizen		3.0
 * @description     check if SYSTEM_SETTINGS_KEY_ULTRA_DATA_SAVE is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_ULTRA_DATA_SAVE is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p30(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_ULTRA_DATA_SAVE,
												 utc_system_settings_changed_callback, NULL);

	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_TELEPHONY_FEATURE);
	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_ULTRA_DATA_SAVE);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_TELEPHONY_FEATURE);
	my_assert_ret(retcode);

	return 0;
}

/**
 * @testcase		utc_system_settings_set_changed_cb_p33
 * @since_tizen		3.0
 * @description     check if SYSTEM_SETTINGS_KEY_ULTRA_DATA_SAVE_PKG_LIST is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p33(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_ULTRA_DATA_SAVE_PKG_LIST,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_TELEPHONY_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p32
 * @since_tizen		3.0
 * @description     check if SYSTEM_SETTINGS_KEY_ULTRA_DATA_SAVE_PKG_LIST is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_ULTRA_DATA_SAVE_PKG_LIST is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p32(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_ULTRA_DATA_SAVE_PKG_LIST,
												 utc_system_settings_changed_callback, NULL);

	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_TELEPHONY_FEATURE);
	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_ULTRA_DATA_SAVE_PKG_LIST);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_TELEPHONY_FEATURE);
	my_assert_ret(retcode);

	return 0;
}

/**
 * @testcase		utc_system_settings_set_changed_cb_p35
 * @since_tizen		4.0
 * @description     check if SYSTEM_SETTINGS_KEY_ACCESSIBILITY_TTS is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p35(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_ACCESSIBILITY_TTS,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p34
 * @since_tizen		4.0
 * @description     check if SYSTEM_SETTINGS_KEY_ACCESSIBILITY_TTS is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_ACCESSIBILITY_TTS is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p34(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_ACCESSIBILITY_TTS,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_ACCESSIBILITY_TTS);
	my_assert_ret(retcode);

	return 0;
}

/**
 * @testcase		utc_system_settings_set_changed_cb_p37
 * @since_tizen		4.0
 * @description     check if SYSTEM_SETTINGS_KEY_VIBRATION is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p37(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_VIBRATION,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p36
 * @since_tizen		4.0
 * @description     check if SYSTEM_SETTINGS_KEY_VIBRATION is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_VIBRATION is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p36(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_VIBRATION,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_VIBRATION);
	my_assert_ret(retcode);

	return 0;
}

/**
 * @testcase		utc_system_settings_set_changed_cb_p39
 * @since_tizen		5.0
 * @description     check if SYSTEM_SETTINGS_KEY_AUTOMATIC_TIME_UPDATE is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p39(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_AUTOMATIC_TIME_UPDATE,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_TELEPHONY_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p38
 * @since_tizen		5.0
 * @description     check if SYSTEM_SETTINGS_KEY_AUTOMATIC_TIME_UPDATE is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_AUTOMATIC_TIME_UPDATE is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p38(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_AUTOMATIC_TIME_UPDATE,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_TELEPHONY_FEATURE);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_AUTOMATIC_TIME_UPDATE);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_TELEPHONY_FEATURE);
	my_assert_ret(retcode);

	return 0;
}

/**
 * @testcase		utc_system_settings_set_changed_cb_p41
 * @since_tizen		5.0
 * @description     check if SYSTEM_SETTINGS_KEY_DEVELOPER_OPTION_STATE is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p41(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_DEVELOPER_OPTION_STATE,
												 utc_system_settings_changed_callback, NULL);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p40
 * @since_tizen		5.0
 * @description     check if SYSTEM_SETTINGS_KEY_DEVELOPER_OPTION_STATE is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_DEVELOPER_OPTION_STATE is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p40(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_DEVELOPER_OPTION_STATE,
												 utc_system_settings_changed_callback, NULL);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_DEVELOPER_OPTION_STATE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p43
 * @since_tizen		5.5
 * @description     check if SYSTEM_SETTINGS_KEY_ACCESSIBILITY_GRAYSCALE is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p43(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_ACCESSIBILITY_GRAYSCALE,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_GRAYSCALE_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p42
 * @since_tizen		5.5
 * @description     check if SYSTEM_SETTINGS_KEY_ACCESSIBILITY_GRAYSCALE is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_ACCESSIBILITY_GRAYSCALE is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p42(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_ACCESSIBILITY_GRAYSCALE,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_GRAYSCALE_FEATURE);
	my_assert_ret(retcode);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_ACCESSIBILITY_GRAYSCALE);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_GRAYSCALE_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_set_changed_cb_p45
 * @since_tizen		5.5
 * @description     check if SYSTEM_SETTINGS_KEY_ACCESSIBILITY_NEGATIVE_COLOR is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p45(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_ACCESSIBILITY_NEGATIVE_COLOR,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_NEGATIVE_FEATURE);
	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p44
 * @since_tizen		5.5
 * @description     check if SYSTEM_SETTINGS_KEY_ACCESSIBILITY_NEGATIVE_COLOR is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_ACCESSIBILITY_NEGATIVE_COLOR is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p44(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_ACCESSIBILITY_NEGATIVE_COLOR,
												 utc_system_settings_changed_callback, NULL);
	IF_FEATURE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_NEGATIVE_FEATURE);
	my_assert_ret(retcode);

	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_ACCESSIBILITY_NEGATIVE_COLOR);
	my_assert_ret(retcode);

	return 0;
}

/**
 * @testcase		utc_system_settings_set_changed_cb_p47
 * @since_tizen		5.5
 * @description     check if SYSTEM_SETTINGS_KEY_ROTARY_EVENT_ENABLED is able to set the callback for change-notification.
 */
int utc_system_settings_set_changed_cb_p47(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_ROTARY_EVENT_ENABLED,
												 utc_system_settings_changed_callback, NULL);
	IF_PROFILE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_WERABLE_PROFILE, SYSTEM_SETTINGS_ROTATING_BEZEL_FEATURE);

	my_assert_ret(retcode);

	return 0;
}


/**
 * @testcase		utc_system_settings_unset_changed_cb_p46
 * @since_tizen		5.5
 * @description     check if SYSTEM_SETTINGS_KEY_ROTARY_EVENT_ENABLED is able to set the callback for change-notification.
 *                  check if SYSTEM_SETTINGS_KEY_ROTARY_EVENT_ENABLED is able to unset the callback for change-notification.
 */
int utc_system_settings_unset_changed_cb_p46(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_ROTARY_EVENT_ENABLED,
												 utc_system_settings_changed_callback, NULL);
	IF_PROFILE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_WERABLE_PROFILE, SYSTEM_SETTINGS_ROTATING_BEZEL_FEATURE); my_assert_ret(retcode);
	retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_ROTARY_EVENT_ENABLED);
	IF_PROFILE_CHECK_RETURN(retcode, SYSTEM_SETTINGS_WERABLE_PROFILE, SYSTEM_SETTINGS_ROTATING_BEZEL_FEATURE);
	my_assert_ret(retcode);

	return 0;
}

static void utc_system_settings_changed_callback_1(system_settings_key_e key, void *user_data)
{
	_callback_called = true;
}

static void utc_system_settings_changed_callback_2(system_settings_key_e key, void *user_data)
{
	_callback_called = true;
}

/**
 * @testcase		utc_system_settings_add_remove_changed_cb_p1
 * @since_tizen		5.0
 * @description     check if system setting keys are able to add the callback for change-notification.
 *                  check if system setting keys are able to remove the callback for change-notification.
 */
int utc_system_settings_add_remove_changed_cb_p1(void)
{
	int retcode = 0;
	int key_idx = 0;

	for (key_idx = SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE; key_idx < SYSTEM_SETTINGS_KEY_MAX ; key_idx++) {

		if ( key_idx == SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED + 1)
			continue; /* skip removed system-setting key */

		if ( key_idx == SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE)
			continue; /* skip removed system-setting key */

		/* skip when feature is false about each system_settings_key */
		IF_FEATURE_CHECK_SKIP(key_idx, SYSTEM_SETTINGS_KEY_NETWORK_WIFI_NOTIFICATION, SYSTEM_SETTINGS_NETWORK_WIFI_FEATURE);
		IF_FEATURE_CHECK_SKIP(key_idx, SYSTEM_SETTINGS_KEY_LOCKSCREEN_APP, SYSTEM_SETTINGS_LOCK_SCREEN_FEATURE);
		IF_FEATURE_CHECK_SKIP(key_idx, SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN, SYSTEM_SETTINGS_LOCK_SCREEN_FEATURE);
		IF_FEATURE_CHECK_SKIP(key_idx, SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE, SYSTEM_SETTINGS_INCOMING_CALL_FEATURE);
		IF_FEATURE_CHECK_SKIP(key_idx, SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION, SYSTEM_SETTINGS_INCOMING_CALL_FEATURE);
		IF_FEATURE_CHECK_SKIP(key_idx, SYSTEM_SETTINGS_KEY_ULTRA_DATA_SAVE_PKG_LIST, SYSTEM_SETTINGS_TELEPHONY_FEATURE);
		IF_FEATURE_CHECK_SKIP(key_idx, SYSTEM_SETTINGS_KEY_ULTRA_DATA_SAVE, SYSTEM_SETTINGS_TELEPHONY_FEATURE);
		IF_FEATURE_CHECK_SKIP(key_idx, SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN, SYSTEM_SETTINGS_WALLPAPER_HOME_SCREEN_FEATURE);
		IF_FEATURE_CHECK_SKIP(key_idx, SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE, SYSTEM_SETTINGS_NOTIFICATION_EMAIL_FEATURE);
		IF_FEATURE_CHECK_SKIP(key_idx, SYSTEM_SETTINGS_KEY_AUTOMATIC_TIME_UPDATE, SYSTEM_SETTINGS_TELEPHONY_FEATURE);
		IF_FEATURE_CHECK_SKIP(key_idx, SYSTEM_SETTINGS_KEY_ACCESSIBILITY_GRAYSCALE, SYSTEM_SETTINGS_GRAYSCALE_FEATURE);
		IF_FEATURE_CHECK_SKIP(key_idx, SYSTEM_SETTINGS_KEY_ACCESSIBILITY_NEGATIVE_COLOR, SYSTEM_SETTINGS_NEGATIVE_FEATURE);
		IF_FEATURE_CHECK_SKIP(key_idx, SYSTEM_SETTINGS_KEY_FONT_SIZE, SYSTEM_SETTINGS_FONT_FEATURE);

		IF_FEATURE_CHECK_SKIP(key_idx, SYSTEM_SETTINGS_KEY_FONT_TYPE, SYSTEM_SETTINGS_FONT_FEATURE);
		IF_FEATURE_PROFILE_CHECK_SKIP(key_idx, SYSTEM_SETTINGS_KEY_ROTARY_EVENT_ENABLED, SYSTEM_SETTINGS_WERABLE_PROFILE, SYSTEM_SETTINGS_ROTATING_BEZEL_FEATURE);

		retcode = system_settings_add_changed_cb(key_idx,
													utc_system_settings_changed_callback_1, NULL);

		if (retcode != SYSTEM_SETTINGS_ERROR_NONE)
			FPRINTF("ERROR !! key =%d , ret = %d\n", key_idx, retcode);

		retcode = system_settings_remove_changed_cb(key_idx,
													utc_system_settings_changed_callback_1);

		if (retcode != SYSTEM_SETTINGS_ERROR_NONE)
			FPRINTF("ERROR !! key =%d , ret = %d\n", key_idx, retcode);

		retcode = system_settings_add_changed_cb(key_idx,
													 utc_system_settings_changed_callback_1, NULL);
		my_assert_ret(retcode);

		retcode = system_settings_add_changed_cb(key_idx,
													 utc_system_settings_changed_callback_2, NULL);
		my_assert_ret(retcode);

		retcode = system_settings_remove_changed_cb(key_idx,
													utc_system_settings_changed_callback_1);
		my_assert_ret(retcode);

		retcode = system_settings_remove_changed_cb(key_idx,
													utc_system_settings_changed_callback_2);
		my_assert_ret(retcode);
	}

	return 0;
}

