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
#include <stdbool.h>
#include <system_info.h>

//& set: BluetoothPBAPPositive

static int startup_flag = BT_ERROR_NONE;
static bool pbap_supported = false;
static bool bt_supported = false;

void connection_state_changed_cb_for_pbap_p(int result, bool connected, const char *remote_address, void *user_data)
{

}

/**
 * @function		utc_bluetooth_pbap_positive_startup
 * @description 	check if bluetooth is supported and PABP is supported, Initialize bluetooth and check the adapter state and
 *				store adapter state for further use.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_pbap_positive_startup(void)
{
	int ret = BT_ERROR_NONE;
	bt_adapter_state_e adapter_state = BT_ADAPTER_DISABLED;
	startup_flag = BT_ERROR_NONE;

	bt_supported = false;
	system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth", &bt_supported);

	pbap_supported = false;
	system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.phonebook.client", &pbap_supported);

	if (bt_supported) {
		ret = bt_initialize();
		if (BT_ERROR_NONE != ret) {
			fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
			fprintf(stderr, "bt_initialize failed (code: %d)\n", ret);
			startup_flag = ret;
			return;
		}

		ret = bt_adapter_get_state(&adapter_state);
		if (adapter_state != BT_ADAPTER_ENABLED) {
			fprintf(stdout, "BT is not enabled!!");
			startup_flag = BT_ERROR_NOT_ENABLED;
		}
	}

	if (pbap_supported) {
		ret = bt_pbap_client_initialize();
		if (BT_ERROR_NONE != ret && BT_ERROR_ALREADY_DONE != ret) {
			fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
			fprintf(stderr, "bt_pbap_client_initialize failed (code: %d)\n", ret);
			startup_flag = ret;
			return;
		}
	}
}

/**
 * @function		utc_bluetooth_pbap_positive_cleanup
 * @description 	check If bluetooth is supported release all the bluetooth resources.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_pbap_positive_cleanup(void)
{
	int ret = BT_ERROR_NONE;

	if (pbap_supported)
		ret = bt_pbap_client_deinitialize();

	if (bt_supported)
		bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_pbap_client_initialize_p
 * @since_tizen	3.0
 * @description Check if bt, pbap features are supported. If yes, deinitialize pbap and initialize pbap and ensure there is no error.
 *			   Else, initialize pbap and verify result as BT_ERROR_NOT_SUPPORTED.
 * @senario	   Check if BT and pbap is supported and then call bt_pbap_client_initialize on the device and check for BT_ERROR_NONE.
 */

int utc_bluetooth_bt_pbap_client_initialize_p(void)
{
	int ret = BT_ERROR_NONE;

	if (pbap_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_pbap_client_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_pbap_client_initialize();
		assert_eq(ret, BT_ERROR_NONE);
	} else {
		ret = bt_pbap_client_initialize();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_pbap_client_deinitialize_p
 * @since_tizen	3.0
 * @description Check if bt, pbap features are supported. If yes, deinitialize audio and ensure there is no error.
 *			   Else, deinitialize pbap and verify result as BT_ERROR_NOT_SUPPORTED.
 * @senario	   Positive case to check for pbap deinitialize. Check if BT and pbap is supported and then deinitialize pbap.
 *			   Check for BT_ERROR_NONE.
 */

int utc_bluetooth_bt_pbap_client_deinitialize_p(void)
{
	int ret = BT_ERROR_NONE;

	if (pbap_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_pbap_client_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);
	} else {
		ret = bt_pbap_client_deinitialize();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


/**
 * @testcase		utc_bluetooth_bt_pbap_client_set_connection_state_changed_cb_p
 * @since_tizen	3.0
 * @description 	check if PBAP is supported and startup_flag is asserted then register a callback that will be
 *				called when PBAP connection state is changed and check for errors.
 * scenario 		Registers a callback function that will be invoked when the PBAP connection state is changed.
 */
int utc_bluetooth_bt_pbap_client_set_connection_state_changed_cb_p(void)
{
	int ret = BT_ERROR_NONE;

	if (pbap_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_pbap_client_set_connection_state_changed_cb(connection_state_changed_cb_for_pbap_p, NULL);
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_pbap_client_unset_connection_state_changed_cb();
		/* Don't check the error in this position */
	} else {
		ret = bt_pbap_client_set_connection_state_changed_cb(connection_state_changed_cb_for_pbap_p, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_pbap_client_unset_connection_state_changed_cb_p
 * @since_tizen	3.0
 * @description 	check if PBAP is supported and startup_flag is asserted then unregister the callback set for
 *				PBAP connection state change and check for errors.
 * scenario 		Unregisters a callback function that will be invoked when the PBAP connection state is changed.
 */
int utc_bluetooth_bt_pbap_client_unset_connection_state_changed_cb_p(void)
{
	int ret = BT_ERROR_NONE;

	if (pbap_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_pbap_client_set_connection_state_changed_cb(connection_state_changed_cb_for_pbap_p, NULL);
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_pbap_client_unset_connection_state_changed_cb();
		assert_eq(ret, BT_ERROR_NONE);
	} else {
		ret = bt_pbap_client_unset_connection_state_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

