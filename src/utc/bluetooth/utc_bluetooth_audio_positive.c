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
#include <bluetooth.h>
#include <glib.h>
#include <string.h>
#include <system_info.h>

//& set: BluetoothAudioPositive

static int startup_flag = BT_ERROR_NONE;
static bool bt_supported = false;
static bool media_supported = false;
static bool call_supported = false;
static bool control_supported = false;

static void __bt_avrcp_target_connection_state_changed_cb(bool connected,
	const char *remote_address, void *user_data)
{

}

static void __bt_avrcp_control_connection_state_changed_cb(bool connected,
	const char *remote_address, void *user_data)
{

}


/**
 * @function            utc_bluetooth_audio_positive_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_bluetooth_audio_positive_startup(void)
{
	int ret = BT_ERROR_NONE;
    bt_adapter_state_e adapter_state = BT_ADAPTER_DISABLED;

#ifndef TV
		bt_supported = false;
		system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth", &bt_supported);

		media_supported = false;
		system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.audio.media", &media_supported);

		call_supported = false;
		system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.audio.call", &call_supported);
#else
		bt_supported = true;
		media_supported = true;
		call_supported = false;
#endif

    if (bt_supported) {
        startup_flag = BT_ERROR_NONE;
        ret = bt_initialize();
        if(BT_ERROR_NONE != ret) {
            fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
            fprintf(stderr, "bt_initialize failed (code: %d)\n", ret);
            startup_flag = ret;
            return;
        }

        if (media_supported || call_supported) {
            ret = bt_audio_initialize();
            if(BT_ERROR_NONE != ret) {
                fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
                fprintf(stderr, "bt_audio_initialize failed (code: %d)\n", ret);
                startup_flag = ret;
                return;
            }
        }

        ret = bt_adapter_get_state(&adapter_state);
        if (adapter_state != BT_ADAPTER_ENABLED) {
                fprintf(stdout, "BT is not enabled!!");
                startup_flag = BT_ERROR_NOT_ENABLED;
        }
    }
}

/**
 * @function            utc_bluetooth_audio_positive_cleanup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_bluetooth_audio_positive_cleanup(void)
{
    if (media_supported || call_supported)
        bt_audio_deinitialize();

    if (bt_supported)
        bt_deinitialize();
}

/**
 * @function            utc_bluetooth_avrcp_callback_positive_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_bluetooth_avrcp_callback_positive_startup(void)
{
	int ret = BT_ERROR_NONE;

#ifndef TV
		bt_supported = false;
		system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth", &bt_supported);

		media_supported = false;
		system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.audio.media", &media_supported);

		call_supported = false;
		system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.audio.call", &call_supported);

		control_supported = false;
		system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.audio.controller", &control_supported);
#else
		bt_supported = true;
		media_supported = true;
		call_supported = false;
		control_supported = false;
#endif

    if (bt_supported) {
        startup_flag = BT_ERROR_NONE;
        ret = bt_initialize();
        if(BT_ERROR_NONE != ret) {
            fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
            fprintf(stderr, "bt_initialize failed (code: %d)\n", ret);
            startup_flag = ret;
            return;
        }

		if (media_supported) {
			ret = bt_avrcp_target_initialize(
							__bt_avrcp_target_connection_state_changed_cb,
							NULL);
            if(BT_ERROR_NONE != ret) {
                fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
                fprintf(stderr, "bt_avrcp_target_initialize failed (code: %d)\n", ret);
                startup_flag = ret;
                return;
            }
		}

#ifndef TV
		if (control_supported) {
			ret = bt_avrcp_control_initialize(
					__bt_avrcp_control_connection_state_changed_cb,
					NULL);
            if(BT_ERROR_NONE != ret) {
                fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
                fprintf(stderr, "bt_avrcp_control_initialize failed (code: %d)\n", ret);
                startup_flag = ret;
                return;
            }
		}
#endif
    }
}

/**
 * @function            utc_bluetooth_avrcp_callback_positive_cleanup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_bluetooth_avrcp_callback_positive_cleanup(void)
{
	if (media_supported)
		bt_avrcp_target_deinitialize();

#ifndef TV
	if (control_supported)
		bt_avrcp_control_deinitialize();
#endif

    if (bt_supported)
        bt_deinitialize();
}

static void connection_state_changed_cb_for_audio_p(int result, bool connected,
                        const char *remote_address,
                        bt_audio_profile_type_e type,
                        void *user_data)
{

}

/**
 * @testcase		utc_bluetooth_bt_audio_initialize_p
 * @since_tizen	2.3
 * @description	Check if bt, media or call features are supported. If yes, deinitialize audio and initialize audio and ensure there is no error.
 * 				Else, initialize bt audio and verify result as BT_ERROR_NOT_SUPPORTED.
 * @senario		Check if BT and media/call is supported and then call bt_audio_initialize on the device and check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_audio_initialize_p(void)
{
	int ret = BT_ERROR_NONE;

    if (media_supported || call_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_audio_deinitialize();

        ret = bt_audio_initialize();
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_audio_initialize();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_audio_set_connection_state_changed_cb_p
 * @since_tizen	2.3
 * @description	Check if bt, media or call features are supported. If yes, set audio connection state change callback and ensure there is no error.
 * 				Else, set audio connection state change callback and verify result as BT_ERROR_NOT_SUPPORTED.
 * @senario		Check if BT and media/call is supported and then call bt_audio_set_connection_state_changed_cb and check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_audio_set_connection_state_changed_cb_p(void)
{
	int ret = BT_ERROR_NONE;

    if (media_supported || call_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_audio_set_connection_state_changed_cb
            (connection_state_changed_cb_for_audio_p, NULL);
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_audio_set_connection_state_changed_cb
            (connection_state_changed_cb_for_audio_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_audio_unset_connection_state_changed_cb_p
 * @since_tizen	2.3
 * @description	Check if bt, media or call features are supported. If yes, set and unset audio connection state change callback and ensure there is no error.
 * 				Else, unset audio connection state change callback and verify result as BT_ERROR_NOT_SUPPORTED.
 * @senario		Check if BT and media/call is supported and then set and unset audio connection state changed cb. Check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_audio_unset_connection_state_changed_cb_p(void)
{
	int ret = BT_ERROR_NONE;

    if (media_supported || call_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_audio_set_connection_state_changed_cb
            (connection_state_changed_cb_for_audio_p, NULL);

        ret = bt_audio_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_audio_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_audio_deinitialize_p
 * @since_tizen	2.3
 * @description	Check if bt, media or call features are supported. If yes, deinitialize audio and ensure there is no error.
 * 				Else, deinitialize audio  and verify result as BT_ERROR_NOT_SUPPORTED.
 * @senario		Positive case to check for audio deinitialize. Check if BT and media/call is supported and then deinitialize audio.
 *				Check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_audio_deinitialize_p(void)
{
	int ret = BT_ERROR_NONE;

    if (media_supported || call_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_audio_deinitialize();
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_audio_deinitialize();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_target_initialize_p
 * @since_tizen	2.3
 * @description	Assert bt is initialized. Initialize avrcp target and check for BT_ERROR_NONE. Then deinitialize avrcp target.
 * @senario		Positive case to check for audio initialize. Check if BT and media/call is supported and then initialize audio.
 *				Check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_target_initialize_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_avrcp_target_initialize(
				__bt_avrcp_target_connection_state_changed_cb,
				NULL);
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_avrcp_target_deinitialize();
	} else {
		ret = bt_avrcp_target_initialize(
						__bt_avrcp_target_connection_state_changed_cb,
						NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_target_deinitialize_p
 * @since_tizen	2.3
 * @description	Assert bt is initialized. Initialize avrcp target and check for BT_ERROR_NONE. Then deinitialize avrcp target.
 * @senario		Positive case to check for audio deinitialize. Check if BT and media/call is supported and then deinitialize audio.
 *				Check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_target_deinitialize_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_avrcp_target_initialize(
					__bt_avrcp_target_connection_state_changed_cb,
					NULL);
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_target_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);
	} else {
		ret = bt_avrcp_target_deinitialize();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_target_notify_equalizer_state_p
 * @since_tizen	2.3
 * @description	Assert bt is initialized. Initialize avrcp target and check for BT_ERROR_NONE. Call bt_avrcp_target_notify_equalizer_state
 *				with BT_AVRCP_EQUALIZER_STATE_ON as parameter and check there is no error. Then deinitialize avrcp target.
 * @senario		Positive case to check for bt_avrcp_target_notify_equalizer_state(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_target_notify_equalizer_state_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_avrcp_target_initialize(
						__bt_avrcp_target_connection_state_changed_cb,
					NULL);
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_target_notify_equalizer_state(BT_AVRCP_EQUALIZER_STATE_ON);
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_avrcp_target_deinitialize();
	} else {
		ret = bt_avrcp_target_notify_equalizer_state(BT_AVRCP_EQUALIZER_STATE_ON);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_target_notify_repeat_mode_p
 * @since_tizen	2.3
 * @description	Assert bt is initialized. Initialize avrcp target and check for BT_ERROR_NONE. Call bt_avrcp_target_notify_repeat_mode
 *				with BT_AVRCP_REPEAT_MODE_SINGLE_TRACK as parameter and check there is no error. Then deinitialize avrcp target.
 * @senario		Positive case to check for bt_avrcp_target_notify_repeat_mode(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_target_notify_repeat_mode_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_avrcp_target_initialize(
						__bt_avrcp_target_connection_state_changed_cb,
						NULL);
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_target_notify_repeat_mode(BT_AVRCP_REPEAT_MODE_SINGLE_TRACK);
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_avrcp_target_deinitialize();
	} else {
		ret = bt_avrcp_target_notify_repeat_mode(BT_AVRCP_REPEAT_MODE_SINGLE_TRACK);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_target_notify_shuffle_mode_p
 * @since_tizen	2.3
 * @description	Assert bt is initialized. Initialize avrcp target and check for BT_ERROR_NONE. Call bt_avrcp_target_notify_shuffle_mode
 *				with BT_AVRCP_SHUFFLE_MODE_ALL_TRACK as parameter and check there is no error. Then deinitialize avrcp target.
 * @senario		Positive case to check for bt_avrcp_target_notify_shuffle_mode(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_target_notify_shuffle_mode_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_avrcp_target_initialize(
						__bt_avrcp_target_connection_state_changed_cb,
						NULL);
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_target_notify_shuffle_mode(BT_AVRCP_SHUFFLE_MODE_ALL_TRACK);
		assert_eq(ret, BT_ERROR_NONE);
		ret = bt_avrcp_target_deinitialize();
	} else {
		ret = bt_avrcp_target_notify_shuffle_mode(BT_AVRCP_SHUFFLE_MODE_ALL_TRACK);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_target_notify_scan_mode_p
 * @since_tizen	2.3
 * @description	Assert bt is initialized. Initialize avrcp target and check for BT_ERROR_NONE. Call bt_avrcp_target_notify_scan_mode
 *				with BT_AVRCP_SCAN_MODE_ALL_TRACK as parameter and check there is no error. Then deinitialize avrcp target.
 * @senario		Positive case to check for bt_avrcp_target_notify_scan_mode(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_target_notify_scan_mode_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_avrcp_target_initialize(
						__bt_avrcp_target_connection_state_changed_cb,
						NULL);
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_target_notify_scan_mode(BT_AVRCP_SCAN_MODE_ALL_TRACK);
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_avrcp_target_deinitialize();
	} else {
		ret = bt_avrcp_target_notify_scan_mode(BT_AVRCP_SCAN_MODE_ALL_TRACK);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_target_notify_player_state_p
 * @since_tizen	2.3
 * @description	Assert bt is initialized. Initialize avrcp target and check for BT_ERROR_NONE. Call bt_avrcp_target_notify_player_state
 *				with BT_AVRCP_PLAYER_STATE_STOPPED as parameter and check there is no error. Then deinitialize avrcp target
 * @senario		Positive case to check for bt_avrcp_target_notify_player_state(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_target_notify_player_state_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_avrcp_target_initialize(
						__bt_avrcp_target_connection_state_changed_cb,
						NULL);
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_target_notify_player_state(BT_AVRCP_PLAYER_STATE_STOPPED);
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_avrcp_target_deinitialize();
	} else {
		ret = bt_avrcp_target_notify_player_state(BT_AVRCP_PLAYER_STATE_STOPPED);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_target_notify_position_p
 * @since_tizen	2.3
 * @description	Assert bt is initialized. Initialize avrcp target and check for BT_ERROR_NONE. Call bt_avrcp_target_notify_position
 *				and check there is no error. Then deinitialize avrcp target.
 * @senario		Positive case to check for bt_avrcp_target_notify_position(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_target_notify_position_p(void)
{
	int ret = BT_ERROR_NONE;
	unsigned int position = 0;

	if (media_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_avrcp_target_initialize(
						__bt_avrcp_target_connection_state_changed_cb,
						NULL);
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_target_notify_position(position);
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_avrcp_target_deinitialize();
	} else {
		ret = bt_avrcp_target_notify_position(position);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_target_notify_track_p
 * @since_tizen	2.3
 * @description	Assert bt is initialized. Initialize avrcp target and check for BT_ERROR_NONE. Call bt_avrcp_target_notify_track
 *				with valid input details and check there is no error. Then deinitialize avrcp target.
 * @senario		Positive case to check for bt_avrcp_target_notify_track(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_target_notify_track_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_avrcp_target_initialize(
						__bt_avrcp_target_connection_state_changed_cb,
						NULL);
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_target_notify_track("title", "artist", "album", "genre", 5, 20, 2);
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_avrcp_target_deinitialize();
	} else {
		ret = bt_avrcp_target_notify_track("title", "artist", "album", "genre", 5, 20, 2);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

static void __bt_avrcp_set_equalizer_state_changed_cb(
		bt_avrcp_equalizer_state_e equalizer, void *user_data)
{

}


/**
 * @testcase		utc_bluetooth_bt_avrcp_set_equalizer_state_changed_p
 * @since_tizen	2.3
 * @description	Assert bt is initialized. Initialize avrcp target and check for BT_ERROR_NONE. Call set avrcp equalizer state changed callback
 *				with valid input details and check there is no error. Then unset the avrcp equalizer state changed callback.
 *				Deinitialize avrcp target.
 * @senario		Positive case to check for bt_avrcp_set_equalizer_state_changed_cb(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_set_equalizer_state_changed_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_avrcp_set_equalizer_state_changed_cb(__bt_avrcp_set_equalizer_state_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NONE);
		ret = bt_avrcp_unset_equalizer_state_changed_cb();
	} else {
		ret = bt_avrcp_set_equalizer_state_changed_cb(__bt_avrcp_set_equalizer_state_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_unset_equalizer_state_changed_p
 * @since_tizen	2.3
 * @description	Assert bt is initialized. Initialize avrcp target and check for BT_ERROR_NONE. Call set avrcp equalizer state changed callback
 *				with valid input details and check there is no error. Then unset the avrcp equalizer state changed callback and verify there is no error.
 *				Deinitialize avrcp target.
 * @senario		Positive case to check for bt_avrcp_unset_equalizer_state_changed_cb(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_unset_equalizer_state_changed_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_avrcp_set_equalizer_state_changed_cb(__bt_avrcp_set_equalizer_state_changed_cb, NULL);
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_unset_equalizer_state_changed_cb();
		assert_eq(ret, BT_ERROR_NONE);
	} else {
		ret = bt_avrcp_unset_equalizer_state_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

static void __bt_avrcp_set_repeat_mode_changed_cb(bt_avrcp_repeat_mode_e repeat, void *user_data)
{

}


/**
 * @testcase		utc_bluetooth_bt_avrcp_set_repeat_mode_changed_p
 * @since_tizen	2.3
 * @description	Assert bt is initialized. Initialize avrcp target and check for BT_ERROR_NONE. Call set avrcp repeat mode changed callback
 *				with valid input details and check there is no error. Then unset the avrcp repeat mode changed callback.
 *				Deinitialize avrcp target.
 * @senario		Positive case to check for bt_avrcp_set_repeat_mode_changed_cb(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_set_repeat_mode_changed_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_avrcp_set_repeat_mode_changed_cb(__bt_avrcp_set_repeat_mode_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NONE);
		ret = bt_avrcp_unset_repeat_mode_changed_cb();
	} else {
		ret = bt_avrcp_set_repeat_mode_changed_cb(__bt_avrcp_set_repeat_mode_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_unset_repeat_mode_changed_p
 * @since_tizen	2.3
 * @description	Assert bt is initialized. Initialize avrcp target and check for BT_ERROR_NONE. Call set avrcp repeat mode changed callback
 *				with valid input details and check there is no error. Then unset the avrcp repeat mode changed callback and verify there is no error.
 *				Deinitialize avrcp target.
 * @senario		Positive case to check for bt_avrcp_unset_repeat_mode_changed_cb(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_unset_repeat_mode_changed_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_avrcp_set_repeat_mode_changed_cb(__bt_avrcp_set_repeat_mode_changed_cb, NULL);
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_unset_repeat_mode_changed_cb();
		assert_eq(ret, BT_ERROR_NONE);
	} else {
		ret = bt_avrcp_unset_repeat_mode_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

static void __bt_avrcp_set_shuffle_mode_changed_cb(bt_avrcp_shuffle_mode_e shuffle, void *user_data)
{

}

/**
 * @testcase		utc_bluetooth_bt_avrcp_set_shuffle_mode_changed_p
 * @since_tizen	2.3
 * @description	Assert bt is initialized. Initialize avrcp target and check for BT_ERROR_NONE. Call set avrcp shuffle mode changed callback
 *				with valid input details and check there is no error. Then unset the avrcp shuffle mode changed callback.
 *				Deinitialize avrcp target.
 * @senario		Positive case to check for bt_avrcp_set_shuffle_mode_changed_cb(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_set_shuffle_mode_changed_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_avrcp_set_shuffle_mode_changed_cb(__bt_avrcp_set_shuffle_mode_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NONE);
		ret = bt_avrcp_unset_shuffle_mode_changed_cb();
	} else {
		ret = bt_avrcp_set_shuffle_mode_changed_cb(__bt_avrcp_set_shuffle_mode_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_unset_shuffle_mode_changed_p
 * @since_tizen	2.3
 * @description	Assert bt is initialized. Initialize avrcp target and check for BT_ERROR_NONE. Call set avrcp shuffle mode changed callback
 *				with valid input details and check there is no error. Then unset the avrcp shuffle mode changed callback and verify there is no error.
 *				Deinitialize avrcp target.
 * @senario		Positive case to check for bt_avrcp_unset_shuffle_mode_changed_cb(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_unset_shuffle_mode_changed_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_avrcp_set_shuffle_mode_changed_cb(__bt_avrcp_set_shuffle_mode_changed_cb, NULL);
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_unset_shuffle_mode_changed_cb();
		assert_eq(ret, BT_ERROR_NONE);
	} else {
		ret = bt_avrcp_unset_shuffle_mode_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

static void __bt_avrcp_set_scan_mode_changed_cb(bt_avrcp_scan_mode_e scan,
					void *user_data)
{

}

/**
 * @testcase		utc_bluetooth_bt_avrcp_set_scan_mode_changed_p
 * @since_tizen	2.3
 * @description	Assert bt is initialized. Initialize avrcp target and check for BT_ERROR_NONE. Call set avrcp scan mode changed callback
 *				with valid input details and check there is no error. Then unset the avrcp scan mode changed callback.
 *				Deinitialize avrcp target.
 * @senario		Positive case to check for bt_avrcp_set_scan_mode_changed_cb(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_set_scan_mode_changed_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_avrcp_set_scan_mode_changed_cb(
				__bt_avrcp_set_scan_mode_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NONE);
		ret = bt_avrcp_unset_scan_mode_changed_cb();
	} else {
		ret = bt_avrcp_set_scan_mode_changed_cb(
				__bt_avrcp_set_scan_mode_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_unset_scan_mode_changed_p
 * @since_tizen	2.3
 * @description	Assert bt is initialized. Initialize avrcp target and check for BT_ERROR_NONE. Call set avrcp scan mode changed callback
 *				with valid input details and check there is no error. Then unset the avrcp scan mode changed callback and verify there is no error.
 *				Deinitialize avrcp target.
 * @senario		Positive case to check for bt_avrcp_unset_scan_mode_changed_cb(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_unset_scan_mode_changed_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_avrcp_set_scan_mode_changed_cb(
				__bt_avrcp_set_scan_mode_changed_cb, NULL);
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_unset_scan_mode_changed_cb();
		assert_eq(ret, BT_ERROR_NONE);
	} else {
		ret = bt_avrcp_unset_scan_mode_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


#ifndef TV
static void __bt_avrcp_song_position_changed_cb(unsigned int postion,
	void *user_data)
{

}

/**
 * @testcase		utc_bluetooth_bt_avrcp_set_position_changed_cb_p
 * @since_tizen	3.0
 * @description	Assert bt is initialized. Call set avrcp position changed callback
 *				with valid input details and check there is no error. Then unset the avrcp position changed callback.
 * @senario		Positive case to check for bt_avrcp_set_position_changed_cb(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_set_position_changed_cb_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_avrcp_set_position_changed_cb(
				__bt_avrcp_song_position_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NONE);
		ret = bt_avrcp_unset_position_changed_cb();
	} else {
		ret = bt_avrcp_set_position_changed_cb(
				__bt_avrcp_song_position_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_unset_position_changed_cb_p
 * @since_tizen	3.0
 * @description	Assert bt is initialized. Call set avrcp position changed callback
 *				with valid input details and check there is no error. Then unset the avrcp position changed callback and verify there is no error.
 * @senario		Positive case to check for bt_avrcp_unset_position_changed_cb(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_unset_position_changed_cb_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_avrcp_set_position_changed_cb(
				__bt_avrcp_song_position_changed_cb, NULL);
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_unset_position_changed_cb();
		assert_eq(ret, BT_ERROR_NONE);
	} else {
		ret = bt_avrcp_unset_position_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

static void __bt_avrcp_player_state_changed_cb(bt_avrcp_player_state_e state,
	void *user_data)
{

}


/**
 * @testcase		utc_bluetooth_bt_avrcp_set_play_status_changed_cb_p
 * @since_tizen	3.0
 * @description	Assert bt is initialized. Call set avrcp play status changed callback
 *				with valid input details and check there is no error. Then unset the avrcp play status changed callback.
 * @senario		Positive case to check for bt_avrcp_set_play_status_changed_cb(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_set_play_status_changed_cb_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_avrcp_set_play_status_changed_cb(
				__bt_avrcp_player_state_changed_cb, NULL);

		assert_eq(ret, BT_ERROR_NONE);
		ret = bt_avrcp_unset_play_status_changed_cb();
	} else {
		ret = bt_avrcp_set_play_status_changed_cb(
				__bt_avrcp_player_state_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_unset_play_status_changed_cb_p
 * @since_tizen	3.0
 * @description	Assert bt is initialized. Call set avrcp play status changed callback
 *				with valid input details and check there is no error. Then unset the avrcp play status changed callback and verify there is no error.
 * @senario		Positive case to check for bt_avrcp_unset_play_status_changed_cb(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_unset_play_status_changed_cb_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_avrcp_set_play_status_changed_cb(
				__bt_avrcp_player_state_changed_cb, NULL);
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_unset_play_status_changed_cb();
		assert_eq(ret, BT_ERROR_NONE);
	} else {
		ret = bt_avrcp_unset_play_status_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

static void __bt_avrcp_track_info_changed_cb(bt_avrcp_metadata_attributes_info_s *metadata,
	void *user_data)
{

}



/**
 * @testcase		utc_bluetooth_bt_avrcp_set_track_info_changed_cb_p
 * @since_tizen	3.0
 * @description	Assert bt is initialized. Call set avrcp track info changed callback
 *				with valid input details and check there is no error. Then unset the avrcp track info changed callback.
 * @senario		Positive case to check for bt_avrcp_set_track_info_changed_cb(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_set_track_info_changed_cb_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_avrcp_set_track_info_changed_cb(
				__bt_avrcp_track_info_changed_cb, NULL);

		assert_eq(ret, BT_ERROR_NONE);
		ret = bt_avrcp_unset_track_info_changed_cb();
	} else {
		ret = bt_avrcp_set_track_info_changed_cb(
				__bt_avrcp_track_info_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_unset_track_info_changed_cb_p
 * @since_tizen	3.0
 * @description	Assert bt is initialized. Call set avrcp play status changed callback
 *				with valid input details and check there is no error. Then unset the avrcp play status changed callback and verify there is no error.
 * @senario		Positive case to check for bt_avrcp_unset_track_info_changed_cb(). Verify result is BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_unset_track_info_changed_cb_p(void)
{
	int ret = BT_ERROR_NONE;

	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_avrcp_set_track_info_changed_cb(
				__bt_avrcp_track_info_changed_cb, NULL);
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_unset_track_info_changed_cb();
		assert_eq(ret, BT_ERROR_NONE);
	} else {
		ret = bt_avrcp_unset_track_info_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

#endif

