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

//& set: BluetoothAVRCPControlNegative

static int startup_flag = BT_ERROR_NONE;
static bool bt_supported = false;
static bool control_supported = false;

#ifndef TV
static void __bt_avrcp_control_connection_state_changed_cb(bool connected,
	const char *remote_address, void *user_data)
{

}

/**
 * @function		utc_bluetooth_avrcp_control_negative_startup
 * @description 	check if bluetooth is supported, initialize bluetooth.
 *				check if media or call feature is supported, then initialize the avrcp control profiles.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_avrcp_control_negative_startup(void)
{
	int ret = BT_ERROR_NONE;
	startup_flag = BT_ERROR_NONE;

	bt_supported = false;
	system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth", &bt_supported);

	control_supported = false;
	system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.audio.controller", &control_supported);

	if (bt_supported) {
		ret = bt_initialize();
		if (BT_ERROR_NONE != ret) {
			fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
			fprintf(stderr, "bt_initialize failed (code: %d)\n", ret);
			startup_flag = ret;
			return;
		}

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
	}
}

/**
 * @function		utc_bluetooth_avrcp_control_negative_cleanup
 * @description 	check if audio controller feature is supported, then de-initialize the avrcp control profiles
 *				check if bluetooth is supported, de-initialize bluetooth.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_avrcp_control_negative_cleanup(void)
{
	if (control_supported)
		bt_avrcp_control_deinitialize();

    if(bt_supported)
        bt_deinitialize();
}


/**
 * @testcase		utc_bluetooth_bt_avrcp_control_connect_n
 * @since_tizen	3.0
 * @description 	check if avrcp control profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				connect to the remote device with given avrcp control profile and check for errors.
 * @scenario		Try to connect the remote device with the given avrcp control profile, asynchronously,
 *				after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_control_connect_n(void)
{
	int ret = BT_ERROR_NONE;
	char remote_addr[18] = "F6:FB:8F:D8:C8:7C";

	if (control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_control_connect(remote_addr);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_control_connect(remote_addr);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_control_disconnect_n
 * @since_tizen	3.0
 * @description 	check if avrcp control profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				connect to the remote device with given avrcp control profile and check for errors.
 * @scenario		Try to disconnect the remote device with the given avrcp control profile, asynchronously,
 *				after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_control_disconnect_n(void)
{
	int ret = BT_ERROR_NONE;
	char remote_addr[18] = "F6:FB:8F:D8:C8:7C";

	if (control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_control_disconnect(remote_addr);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_control_disconnect(remote_addr);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_control_send_player_command_n
 * @since_tizen	3.0
 * @description 	check if avrcp control profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				call the given avrcp control profile API and check for errors.
 * @scenario		Try to call the given avrcp control API, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_control_send_player_command_n(void)
{
	int ret = BT_ERROR_NONE;

	if (control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_control_send_player_command(BT_AVRCP_CONTROL_PLAY);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_control_send_player_command(BT_AVRCP_CONTROL_PLAY);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_control_set_equalizer_state_n
 * @since_tizen	3.0
 * @description 	check if avrcp control profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				call the given avrcp control profile API and check for errors.
 * @scenario		Try to call the given avrcp control API, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_control_set_equalizer_state_n(void)
{
	int ret = BT_ERROR_NONE;

	if (control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_control_set_equalizer_state(BT_AVRCP_EQUALIZER_STATE_ON);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_control_set_equalizer_state(BT_AVRCP_EQUALIZER_STATE_ON);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_control_get_equalizer_state_n
 * @since_tizen	3.0
 * @description 	check if avrcp control profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				call the given avrcp control profile API and check for errors.
 * @scenario		Try to call the given avrcp control API, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_control_get_equalizer_state_n(void)
{
	int ret = BT_ERROR_NONE;
	bt_avrcp_equalizer_state_e state = BT_AVRCP_EQUALIZER_STATE_ON;

	if (control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_control_get_equalizer_state(&state);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_control_get_equalizer_state(&state);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_control_set_repeat_mode_n
 * @since_tizen	3.0
 * @description 	check if avrcp control profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				call the given avrcp control profile API and check for errors.
 * @scenario		Try to call the given avrcp control API, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_control_set_repeat_mode_n(void)
{
	int ret = BT_ERROR_NONE;

	if (control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_control_set_repeat_mode(BT_AVRCP_REPEAT_MODE_SINGLE_TRACK);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_control_set_repeat_mode(BT_AVRCP_REPEAT_MODE_SINGLE_TRACK);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_control_get_repeat_mode_n
 * @since_tizen	3.0
 * @description 	check if avrcp control profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				call the given avrcp control profile API and check for errors.
 * @scenario		Try to call the given avrcp control API, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_control_get_repeat_mode_n(void)
{
	int ret = BT_ERROR_NONE;
	bt_avrcp_repeat_mode_e mode = BT_AVRCP_REPEAT_MODE_SINGLE_TRACK;

	if (control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_control_get_repeat_mode(&mode);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_control_get_repeat_mode(&mode);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_control_set_shuffle_mode_n
 * @since_tizen	3.0
 * @description 	check if avrcp control profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				call the given avrcp control profile API and check for errors.
 * @scenario		Try to call the given avrcp control API, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_control_set_shuffle_mode_n(void)
{
	int ret = BT_ERROR_NONE;

	if (control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_control_set_shuffle_mode(BT_AVRCP_SHUFFLE_MODE_ALL_TRACK);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_control_set_shuffle_mode(BT_AVRCP_SHUFFLE_MODE_ALL_TRACK);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_control_get_shuffle_mode_n
 * @since_tizen	3.0
 * @description 	check if avrcp control profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				call the given avrcp control profile API and check for errors.
 * @scenario		Try to call the given avrcp control API, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_control_get_shuffle_mode_n(void)
{
	int ret = BT_ERROR_NONE;
	bt_avrcp_shuffle_mode_e mode = BT_AVRCP_SHUFFLE_MODE_ALL_TRACK;

	if (control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_control_get_shuffle_mode(&mode);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_control_get_shuffle_mode(&mode);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_control_set_scan_mode_n
 * @since_tizen	3.0
 * @description 	check if avrcp control profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				call the given avrcp control profile API and check for errors.
 * @scenario		Try to call the given avrcp control API, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_control_set_scan_mode_n(void)
{
	int ret = BT_ERROR_NONE;

	if (control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_control_set_scan_mode(BT_AVRCP_SCAN_MODE_GROUP);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_control_set_scan_mode(BT_AVRCP_SCAN_MODE_GROUP);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_control_get_scan_mode_n
 * @since_tizen	3.0
 * @description 	check if avrcp control profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				call the given avrcp control profile API and check for errors.
 * @scenario		Try to call the given avrcp control API, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_control_get_scan_mode_n(void)
{
	int ret = BT_ERROR_NONE;
	bt_avrcp_scan_mode_e mode = BT_AVRCP_SCAN_MODE_GROUP;

	if (control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_control_get_scan_mode(&mode);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_control_get_scan_mode(&mode);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_control_get_position_n
 * @since_tizen	3.0
 * @description 	check if avrcp control profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				call the given avrcp control profile API and check for errors.
 * @scenario		Try to call the given avrcp control API, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_control_get_position_n(void)
{
	int ret = BT_ERROR_NONE;
	unsigned int position = 0;

	if (control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_control_get_position(&position);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_control_get_position(&position);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_control_get_play_status_n
 * @since_tizen	3.0
 * @description 	check if avrcp control profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				call the given avrcp control profile API and check for errors.
 * @scenario		Try to call the given avrcp control API, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_control_get_play_status_n(void)
{
	int ret = BT_ERROR_NONE;
	bt_avrcp_player_state_e status = BT_AVRCP_PLAYER_STATE_STOPPED;

	if (control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_control_get_play_status(&status);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_control_get_play_status(&status);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_control_get_track_info_n
 * @since_tizen	3.0
 * @description 	check if avrcp control profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				call the given avrcp control profile API and check for errors.
 * @scenario		Try to call the given avrcp control API, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_avrcp_control_get_track_info_n(void)
{
	int ret = BT_ERROR_NONE;
	bt_avrcp_metadata_attributes_info_s *track_info = NULL;

	if (control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_control_get_track_info(&track_info);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_avrcp_control_get_track_info(&track_info);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	if (track_info)
		ret = bt_avrcp_control_free_track_info(track_info);

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_control_free_track_info_n
 * @since_tizen	3.0
 * @description 	Call to free track information by setting the track info param as "NULL" and check the "ret" flag
 *				with BT_ERROR_INVALID_PARAMETER if le	is supported otherwise just try to free device information
 *				by setting the device info param as "NULL" and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to free device information with "NULL" parameter.
 */
int utc_bluetooth_bt_avrcp_control_free_track_info_n(void)
{
	int ret = BT_ERROR_NONE;

	if (control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_avrcp_control_free_track_info(NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_avrcp_control_free_track_info(NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}
#endif
