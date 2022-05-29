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

//& set: BluetoothAVRCPControlPositive

static int startup_flag = BT_ERROR_NONE;
static bool bt_supported = false;
static bool control_supported = false;

#ifndef TV
static void __bt_avrcp_control_connection_state_changed_cb(bool connected,
	const char *remote_address, void *user_data)
{

}

/**
 * @function            utc_bluetooth_avrcp_control_positive_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_bluetooth_avrcp_control_positive_startup(void)
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
 * @function            utc_bluetooth_avrcp_control_positive_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_bluetooth_avrcp_control_positive_cleanup(void)
{
	if (control_supported)
		bt_avrcp_control_deinitialize();

	if (bt_supported)
		bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_control_initialize_p
 * @since_tizen	3.0
 * @description	Assert bt is initialized. Initialize avrcp control and check for BT_ERROR_NONE. Then deinitialize avrcp control.
 * @senario		Positive case to check for avrcp control initialize. Check if BT and controller is supported and then initialize avrcp control.
 *				Check for BT_ERROR_NONE.
 */

int utc_bluetooth_bt_avrcp_control_initialize_p(void)
{
	int ret = BT_ERROR_NONE;

	if (control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_avrcp_control_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_avrcp_control_initialize(
				__bt_avrcp_control_connection_state_changed_cb,
				NULL);
		assert_eq(ret, BT_ERROR_NONE);
	} else {
		ret = bt_avrcp_control_initialize(
				__bt_avrcp_control_connection_state_changed_cb,
				NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_avrcp_control_deinitialize_p
 * @since_tizen	3.0
 * @description	Assert bt is initialized. Initialize avrcp control and check for BT_ERROR_NONE. Then deinitialize avrcp control.
 * @senario		Positive case to check for avrcp control deinitialize. Check if BT and controller is supported and then deinitialize avrcp control.
 *				Check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_avrcp_control_deinitialize_p(void)
{
	int ret = BT_ERROR_NONE;

	if (control_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_avrcp_control_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);
	} else {
		ret = bt_avrcp_control_deinitialize();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}
#endif
