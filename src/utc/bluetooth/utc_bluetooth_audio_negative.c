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

//& set: BluetoothAudioNegative

static int startup_flag = BT_ERROR_NONE;
static int ret = BT_ERROR_NONE;
static bool bt_supported = false;
static bool media_supported = false;
static bool call_supported = false;
static bool control_supported = false;

/**
 * @function		utc_bluetooth_bt_audio_negative_startup
 * @description 	check if bluetooth is supported, initialize bluetooth.
 *				check if media or call feature is supported, then initialize the audio profiles.
 * @scenario		initializes the bluetooth API and audio profiles, this needs to be called before each test.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_bt_audio_negative_startup(void)
{
#ifdef TV
    bt_supported = true;
    media_supported = true;
    call_supported = false;
	control_supported = false;
#else
    bt_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth", &bt_supported);

    media_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.audio.media", &media_supported);

    call_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.audio.call", &call_supported);

	control_supported = false;
	system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.audio.controller", &control_supported);
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
    }
}

/**
 * @function		utc_bluetooth_bt_audio_negative_cleanup
 * @description 	check if media or call feature is supported, then de-initialize the audio profiles
 *				check if bluetooth is supported, de-initialize bluetooth.
 * @scenario		de-initializes the audio profiles and Rrelease all resources of bluetooth, this needs to be called after each test.

 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_bt_audio_negative_cleanup(void)
{
    if (media_supported || call_supported)
        bt_audio_deinitialize();

    if (bt_supported)
        bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_audio_connect_n
 * @since_tizen		2.3
 * @description 	check if audio profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				connect to the remote device with given audio profile and check for errors.
 * @scenario		Try to connect the remote device with the given audio profile, asynchronously,
 *				after bluetooth de-initialization.
 */
int utc_bluetooth_bt_audio_connect_n(void)
{
    if (media_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();

        ret = bt_audio_connect("DummyAddress", BT_AUDIO_PROFILE_TYPE_A2DP);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_audio_connect("DummyAddress", BT_AUDIO_PROFILE_TYPE_A2DP);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_audio_disconnect_n
 * @since_tizen		2.3
 * @description 	check if audio profile are supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				disconnect to the remote device with given audio profile and check for errors.
 * @scenario		Try to disconnect the remote device with the given audio profile, asynchronously,
 *				after bluetooth de-initialization.
 */
int utc_bluetooth_bt_audio_disconnect_n(void)
{
    if (media_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();

        ret = bt_audio_disconnect(NULL, BT_AUDIO_PROFILE_TYPE_A2DP);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_audio_disconnect(NULL, BT_AUDIO_PROFILE_TYPE_A2DP);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_audio_set_connection_state_changed_cb_n
 * @since_tizen		2.3
 * @description 	check if audio profile or call profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				register a callback for change in connection state and check for errors.
 * scenario 		Try to register a callback function to be invoked when the connection state is changed after bluetooth de-initialization.
 */
int utc_bluetooth_bt_audio_set_connection_state_changed_cb_n(void)
{
    if (media_supported || call_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();

        ret = bt_audio_set_connection_state_changed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_audio_set_connection_state_changed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_audio_set_connection_state_changed_cb_n1
 * @since_tizen		2.3
 * @description 	check if audio profile or call profile is supported and startup_flag is asserted, then register a callback for change
 *				in connection state by using invalid parameters and check for errors.
 * scenario 		Try to register a callback function to be invoked when the connection state is changed by using invalid parameters.
 */
int utc_bluetooth_bt_audio_set_connection_state_changed_cb_n1(void)
{
    if (media_supported || call_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_audio_set_connection_state_changed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_audio_set_connection_state_changed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_audio_deinitialize_n
 * @since_tizen		2.3
 * @description 	check if audio profile or call profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				de-initialize the audio profiles and check for errors.
 * scenario 		Try to deinitialize the Bluetooth profiles related with audio. after bluetooth de-initialization.
 */
int utc_bluetooth_bt_audio_deinitialize_n(void)
{
    if (media_supported || call_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();

        ret = bt_audio_deinitialize();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_audio_deinitialize();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_audio_initialize_n
 * @since_tizen		2.3
 * @description 	check if audio profile or call profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				initialize the audio profiles and check for errors.
 * scenario 		Try to initialize the Bluetooth profiles related with audio. after bluetooth de-initialization.
 */
int utc_bluetooth_bt_audio_initialize_n(void)
{
    if (media_supported || call_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();

        ret = bt_audio_initialize();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_audio_initialize();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_audio_unset_connection_state_changed_cb_n
 * @since_tizen		2.3
 * @description 	check if audio profile or call profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				unregister the callback set for connection state changes and check for errors.
 * scenario 		Try to unregister a callback function to be invoked when the connection state is changed after bluetooth de-initialization.
 */
int utc_bluetooth_bt_audio_unset_connection_state_changed_cb_n(void)
{
    if (media_supported || call_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();

        ret = bt_audio_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_audio_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

static void __bt_avrcp_equalizer_state_changed_cb(bt_avrcp_equalizer_state_e equalizer, void *user_data)
{

}

/**
 * @testcase		utc_bluetooth_bt_avrcp_set_equalizer_state_changed_cb_n
 * @since_tizen		2.4
 * @description 	check if audio profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				register the callback function that will be invoked when the equalizer state is changed by the remote control device
 *				and check for errors.
 * scenario 		Try to register a callback function that will be invoked when the equalizer state is changed by the remote control device
 *				after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_set_equalizer_state_changed_cb_n(void)
{
	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_set_equalizer_state_changed_cb(__bt_avrcp_equalizer_state_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_set_equalizer_state_changed_cb(__bt_avrcp_equalizer_state_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

    return 0;
}

static void __bt_avrcp_repeat_mode_changed_cb(bt_avrcp_repeat_mode_e repeat, void *user_data)
{

}

/**
 * @testcase		utc_bluetooth_bt_avrcp_set_repeat_mode_changed_cb_n
 * @since_tizen		2.4
 * @description 	check if audio profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				register the callback function that will be invoked when the repeat mode is changed by the remote control device and check for errors.
 * scenario 		Try to register a callback function that will be invoked when repeat mode is changed by the remote control device after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_set_repeat_mode_changed_cb_n(void)
{
	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_set_repeat_mode_changed_cb(__bt_avrcp_repeat_mode_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_set_repeat_mode_changed_cb(__bt_avrcp_repeat_mode_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

static void __bt_avrcp_scan_mode_changed_cb(bt_avrcp_scan_mode_e scan, void *user_data)
{

}

/**
 * @testcase		utc_bluetooth_bt_avrcp_set_scan_mode_changed_cb_n
 * @since_tizen		2.4
 * @description 	check if audio profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				register the callback function that will be invoked when the scan mode is changed by the remote control device and check for errors.
 * scenario 		Try to register a callback function that will be invoked when scan mode is changed by the remote control device after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_set_scan_mode_changed_cb_n(void)
{
	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_set_scan_mode_changed_cb(__bt_avrcp_scan_mode_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_set_scan_mode_changed_cb(__bt_avrcp_scan_mode_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

static void __bt_avrcp_set_shuffle_mode_changed_cb(bt_avrcp_scan_mode_e scan, void *user_data)
{

}

/**
 * @testcase		utc_bluetooth_bt_avrcp_set_shuffle_mode_changed_cb_n
 * @since_tizen		2.4
 * @description 	check if audio profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				register the callback function that will be invoked when the shuffle mode is changed by the remote control device and check for errors.
 * scenario 		Try to register a callback function that will be invoked when shuffle mode is changed by the remote control device after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_set_shuffle_mode_changed_cb_n(void)
{
	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_set_shuffle_mode_changed_cb(__bt_avrcp_set_shuffle_mode_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_set_shuffle_mode_changed_cb(__bt_avrcp_set_shuffle_mode_changed_cb, NULL);
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
 * @testcase		utc_bluetooth_bt_avrcp_set_position_changed_cb_n
 * @since_tizen	3.0
 * @description 	check if audio profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				register the callback function that will be invoked when the position is changed by the remote control device and check for errors.
 * scenario 		Try to register a callback function that will be invoked when position is changed by the remote control device after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_set_position_changed_cb_n(void)
{
	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_set_position_changed_cb(__bt_avrcp_song_position_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_set_position_changed_cb(__bt_avrcp_song_position_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

static void __bt_avrcp_player_state_changed_cb(bt_avrcp_player_state_e state,
	void *user_data)
{

}

/**
 * @testcase		utc_bluetooth_bt_avrcp_set_play_status_changed_cb_n
 * @since_tizen	3.0
 * @description 	check if audio profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				register the callback function that will be invoked when the play status is changed by the remote control device and check for errors.
 * scenario 		Try to register a callback function that will be invoked when play status is changed by the remote control device after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_set_play_status_changed_cb_n(void)
{
	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_set_play_status_changed_cb(__bt_avrcp_player_state_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_set_play_status_changed_cb(__bt_avrcp_player_state_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

static void __bt_avrcp_track_info_changed_cb(bt_avrcp_metadata_attributes_info_s *metadata,
	void *user_data)
{

}

/**
 * @testcase		utc_bluetooth_bt_avrcp_set_track_info_changed_cb_n
 * @since_tizen	3.0
 * @description 	check if audio profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				register the callback function that will be invoked when the track info is changed by the remote control device and check for errors.
 * scenario 		Try to register a callback function that will be invoked when track info is changed by the remote control device after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_set_track_info_changed_cb_n(void)
{
	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_set_track_info_changed_cb(__bt_avrcp_track_info_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_set_track_info_changed_cb(__bt_avrcp_track_info_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


#endif

/**
 * @testcase		utc_bluetooth_bt_avrcp_target_deinitialize_n
 * @since_tizen		2.4
 * @description 	check if audio profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				de-initialize the AVRCP(Audio/Video Remote Control Profile) service and check for errors.
 * scenario 		Try to deinitialize the Bluetooth AVRCP(Audio/Video Remote Control Profile) service after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_target_deinitialize_n(void)
{
	if (media_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_target_deinitialize();
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_target_deinitialize();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

static void __bt_avrcp_target_connection_state_changed_cb(bool connected, const char *remote_address, void *user_data)
{

}

/**
 * @testcase		utc_bluetooth_bt_avrcp_target_initialize_n
 * @since_tizen		2.4
 * @description 	check if audio profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				initialize the AVRCP(Audio/Video Remote Control Profile) service and check for errors.
 * scenario 		Try to initialize the Bluetooth AVRCP(Audio/Video Remote Control Profile) service after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_target_initialize_n(void)
{
	if (media_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_target_initialize(__bt_avrcp_target_connection_state_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_target_initialize(__bt_avrcp_target_connection_state_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_target_notify_equalizer_state_n
 * @since_tizen		2.4
 * @description 	check if audio profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				send equalizer notification to the remote device and check for errors.
 * @scenario		Try to notify the equalize state to the remote device after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_target_notify_equalizer_state_n(void)
{
	if (media_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_target_notify_equalizer_state(0x01);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_target_notify_equalizer_state(0x01);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_target_notify_player_state_n
 * @since_tizen		2.4
 * @description 	check if audio profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				send player state notification to the remote device and check for errors.
 * @scenario		Try to notify the player state to the remote device after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_target_notify_player_state_n(void)
{
	if (media_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_target_notify_player_state(0x01);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_target_notify_player_state(0x01);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_target_notify_position_n
 * @since_tizen		2.4
 * @description 	check if audio profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				send song's current position notification to the remote device and check for errors.
 * @scenario		Try to notify the current position of song to the remote device after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_target_notify_position_n(void)
{
	if (media_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_target_notify_position(0x01);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_target_notify_position(0x01);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_target_notify_repeat_mode_n
 * @since_tizen		2.4
 * @description 	check if audio profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				send repeat mode notification to the remote device and check for errors.
 * @scenario		Try to notify the repeat mode to the remote device after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_target_notify_repeat_mode_n(void)
{
	if (media_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_target_notify_repeat_mode(0x01);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_target_notify_repeat_mode(0x01);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_target_notify_scan_mode_n
 * @since_tizen		2.4
 * @description 	check if audio profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				send scan mode notification to the remote device and check for errors.
 * @scenario		Try to notify the scan mode to the remote device after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_target_notify_scan_mode_n(void)
{
	if (media_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_target_notify_scan_mode(0x01);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_target_notify_scan_mode(0x01);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_target_notify_shuffle_mode_n
 * @since_tizen		2.4
 * @description 	check if audio profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				send shuffle mode notification to the remote device and check for errors.
 * @scenario		Try to notify the shuffle mode to the remote device after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_target_notify_shuffle_mode_n(void)
{
	if (media_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_target_notify_shuffle_mode(0x01);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_target_notify_shuffle_mode(0x01);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_target_notify_track_n
 * @since_tizen		2.4
 * @description 	check if audio profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				send track notification to the remote device and check for errors.
 * @scenario		Try to notify the track details to the remote device after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_target_notify_track_n(void)
{
	if (media_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_target_notify_track("title", "artist", "album", "genre", 5, 20, 2);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_target_notify_track("title", "artist", "album", "genre", 5, 20, 2);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_unset_equalizer_state_changed_cb_n
 * @since_tizen		2.4
 * @description 	check if audio profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				unregister the callback function set for equalizer state changes 	and check for errors.
 * scenario 		Try to unregister a callback function that will be invoked when the equalizer state is changed by the remote control device
 *				after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_unset_equalizer_state_changed_cb_n(void)
{
	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_unset_equalizer_state_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_unset_equalizer_state_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_unset_repeat_mode_changed_cb_n
 * @since_tizen		2.4
 * @description 	check if audio profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				unregister the callback function set for repeat mode changes and check for errors.
 * scenario 		Try to unregister a callback function that will be invoked when the repeat mode is changed by the remote control device
 *				after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_unset_repeat_mode_changed_cb_n(void)
{
	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_unset_repeat_mode_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_unset_repeat_mode_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_unset_scan_mode_changed_cb_n
 * @since_tizen		2.4
 * @description 	check if audio profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				unregister the callback function set for scan mode changes and check for errors.
 * scenario 		Try to unregister a callback function that will be invoked when the scan mode is changed by the remote control device
 *				after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_unset_scan_mode_changed_cb_n(void)
{
	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_unset_scan_mode_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_unset_scan_mode_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_unset_shuffle_mode_changed_cb_n
 * @since_tizen		2.4
 * @description 	check if audio profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				unregister the callback function set for shuffle mode changes and check for errors.
 * scenario 		Try to unregister a callback function that will be invoked when the shuffle mode is changed by the remote control device
 *				after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_unset_shuffle_mode_changed_cb_n(void)
{
	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_unset_shuffle_mode_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_unset_shuffle_mode_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

#ifndef TV
/**
 * @testcase		utc_bluetooth_bt_avrcp_unset_position_changed_cb_n
 * @since_tizen	3.0
 * @description 	check if audio profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				unregister the callback function set for position changes and check for errors.
 * scenario 		Try to unregister a callback function that will be invoked when the position is changed by the remote control device
 *				after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_unset_position_changed_cb_n(void)
{
	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_unset_position_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_unset_position_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_unset_play_status_changed_cb_n
 * @since_tizen	3.0
 * @description 	check if audio profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				unregister the callback function set for play status changes and check for errors.
 * scenario 		Try to unregister a callback function that will be invoked when the play status is changed by the remote control device
 *				after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_unset_play_status_changed_cb_n(void)
{
	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_unset_play_status_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_unset_play_status_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_unset_track_info_changed_cb_n
 * @since_tizen	3.0
 * @description 	check if audio profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				unregister the callback function set for track info changes and check for errors.
 * scenario 		Try to unregister a callback function that will be invoked when the track info is changed by the remote control device
 *				after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_unset_track_info_changed_cb_n(void)
{
	if (media_supported || control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

		ret = bt_avrcp_unset_track_info_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_unset_track_info_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}
#endif
