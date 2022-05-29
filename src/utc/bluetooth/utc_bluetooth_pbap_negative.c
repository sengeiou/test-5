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

//& set: BluetoothPBAPNegative

static int startup_flag = BT_ERROR_NONE;
static bool pbap_supported = false;
static bool bt_supported = false;


void get_phonebook_size_cb_for_pbap_n(int result, const char *remote_address,
	int size, void *user_data)
{

}

void get_phonebook_pull_cb_pbap_n(int result, const char *remote_address,
	const char *vcf_file, void *user_data)
{

}

void get_phonebook_list_cb_pbap_n(int result, const char *remote_address,
	const bt_pbap_vcard_info_s *vcard_info, int count, void *user_data)
{

}

/**
 * @function		utc_bluetooth_pbap_negative_startup
 * @description 	check if bluetooth is supported and PBAP is supported, initialize bluetooth
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_pbap_negative_startup(void)
{
	int ret = BT_ERROR_NONE;

	bt_supported = false;
	system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth", &bt_supported);

	pbap_supported = false;
	system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.phonebook.client", &pbap_supported);

	if(bt_supported) {
		startup_flag = BT_ERROR_NONE;
		ret = bt_initialize();
		if(BT_ERROR_NONE != ret) {
			fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
			fprintf(stderr, "bt_initialize failed (code: %d)\n", ret);
			startup_flag = ret;
			return;
		}
	}
}

/**
 * @function		utc_bluetooth_pbap_negative_cleanup
 * @description 	If bluetooth is supported and release all the bluetooth resources.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_pbap_negative_cleanup(void)
{
	if (bt_supported)
		bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_pbap_client_initialize_n
 * @since_tizen	3.0
 * @description 	check if pbap client profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				initialize the pbap client profiles and check for errors.
 * scenario 		Try to initialize the Bluetooth profiles related with pbap client. after bluetooth de-initialization.
 */
int utc_bluetooth_bt_pbap_client_initialize_n(void)
{
	int ret = BT_ERROR_NONE;

	if (pbap_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_pbap_client_initialize();
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_pbap_client_initialize();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_pbap_client_deinitialize_n
 * @since_tizen	3.0
 * @description 	check if pbap client is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				de-initialize the pbap client profiles and check for errors.
 * scenario 		Try to deinitialize the Bluetooth profiles related with pbap client. after bluetooth de-initialization.
 */
int utc_bluetooth_bt_pbap_client_deinitialize_n(void)
{
	int ret = BT_ERROR_NONE;

	if (pbap_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_pbap_client_deinitialize();
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_pbap_client_deinitialize();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_pbap_client_set_connection_state_changed_cb_n
 * @since_tizen	3.0
 * @description 	check if pbap client profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				register a callback for change in connection state and check for errors.
 * scenario 		Try to register a callback function to be invoked when the connection state is changed after bluetooth de-initialization.
 */
int utc_bluetooth_bt_pbap_client_set_connection_state_changed_cb_n(void)
{
	int ret = BT_ERROR_NONE;

	if (pbap_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_pbap_client_set_connection_state_changed_cb(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_pbap_client_set_connection_state_changed_cb(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_pbap_client_unset_connection_state_changed_cb_n
 * @since_tizen	3.0
 * @description 	check if pbap client profile is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				unregister the callback set for connection state changes and check for errors.
 * scenario 		Try to unregister a callback function to be invoked when the connection state is changed after bluetooth de-initialization.
 */
int utc_bluetooth_bt_pbap_client_unset_connection_state_changed_cb_n(void)
{
	int ret = BT_ERROR_NONE;

	if (pbap_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_pbap_client_unset_connection_state_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_pbap_client_unset_connection_state_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_pbap_client_connect_n
 * @since_tizen	3.0
 * @description 	check if pbap client profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				connect to the remote device with given pbap client profile and check for errors.
 * @scenario		Try to connect the remote device with the given pbap client profile, asynchronously,
 *				after bluetooth de-initialization.
 */
int utc_bluetooth_bt_pbap_client_connect_n(void)
{
	int ret = BT_ERROR_NONE;
	char remote_addr[18] = "F6:FB:8F:D8:C8:7C";

	if (pbap_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_pbap_client_connect(remote_addr);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_pbap_client_connect(remote_addr);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_pbap_client_disconnect_n
 * @since_tizen		2.3
 * @description 	check if pbap client profile are supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				disconnect to the remote device with given pbap client profile and check for errors.
 * @scenario		Try to disconnect the remote device with the given pbap client profile, asynchronously,
 *				after bluetooth de-initialization.
 */
int utc_bluetooth_bt_pbap_client_disconnect_n(void)
{
	int ret = BT_ERROR_NONE;
	char remote_addr[18] = "F6:FB:8F:D8:C8:7C";

	if (pbap_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_pbap_client_disconnect(remote_addr);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_pbap_client_disconnect(remote_addr);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_pbap_client_get_phone_book_size_n
 * @since_tizen	3.0
 * @description 	check if pbap client profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				call the given pbap client profile API and check for errors.
 * @scenario		Try to call the given pbap client API asynchronously, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_pbap_client_get_phone_book_size_n(void)
{
	int ret = BT_ERROR_NONE;
	char remote_addr[18] = "F6:FB:8F:D8:C8:7C";

	if (pbap_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_pbap_client_get_phone_book_size(remote_addr, 0, 0, get_phonebook_size_cb_for_pbap_n, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_pbap_client_get_phone_book_size(remote_addr, 0, 0, get_phonebook_size_cb_for_pbap_n, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_pbap_client_get_phone_book_n
 * @since_tizen	3.0
 * @description 	check if pbap client profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				call the given pbap client profile API and check for errors.
 * @scenario		Try to call the given pbap client API asynchronously, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_pbap_client_get_phone_book_n(void)
{
	int ret = BT_ERROR_NONE;
	char remote_addr[18] = "F6:FB:8F:D8:C8:7C";
	unsigned int fields = BT_PBAP_FIELD_PHOTO | BT_PBAP_FIELD_EMAIL;

	if (pbap_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_pbap_client_get_phone_book(remote_addr, 0, 0, 0, 0, 0, 100, fields, get_phonebook_pull_cb_pbap_n, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_pbap_client_get_phone_book(remote_addr, 0, 0, 0, 0, 0, 100, fields, get_phonebook_pull_cb_pbap_n, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_pbap_client_get_list_n
 * @since_tizen	3.0
 * @description 	check if pbap client profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				call the given pbap client profile API and check for errors.
 * @scenario		Try to call the given pbap client API asynchronously, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_pbap_client_get_list_n(void)
{
	int ret = BT_ERROR_NONE;
	char remote_addr[18] = "F6:FB:8F:D8:C8:7C";

	if (pbap_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_pbap_client_get_list(remote_addr, 0, 0, 0, 0, 100, get_phonebook_list_cb_pbap_n, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_pbap_client_get_list(remote_addr, 0, 0, 0, 0, 100, get_phonebook_list_cb_pbap_n, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_pbap_client_pull_vcard_n
 * @since_tizen	3.0
 * @description 	check if pbap client profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				call the given pbap client profile API and check for errors.
 * @scenario		Try to call the given pbap client API asynchronously, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_pbap_client_pull_vcard_n(void)
{
	int ret = BT_ERROR_NONE;
	char remote_addr[18] = "F6:FB:8F:D8:C8:7C";
	unsigned int fields = BT_PBAP_FIELD_PHOTO | BT_PBAP_FIELD_EMAIL;

	if (pbap_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_pbap_client_pull_vcard(remote_addr, 0, 0, 0, 0, fields, get_phonebook_pull_cb_pbap_n, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_pbap_client_pull_vcard(remote_addr, 0, 0, 0, 0, fields, get_phonebook_pull_cb_pbap_n, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_pbap_client_search_phone_book_n
 * @since_tizen	3.0
 * @description 	check if pbap client profile is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				call the given pbap client profile API and check for errors.
 * @scenario		Try to call the given pbap client API asynchronously, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_pbap_client_search_phone_book_n(void)
{
	int ret = BT_ERROR_NONE;
	char remote_addr[18] = "F6:FB:8F:D8:C8:7C";

	if (pbap_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		/* Don't check the error in this position, because this is the precondition to verify */

		ret = bt_pbap_client_search_phone_book(remote_addr, 0, 0, 0, "ff", 0, 0, 100, get_phonebook_list_cb_pbap_n, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_pbap_client_search_phone_book(remote_addr, 0, 0, 0, "ff", 0, 0, 100, get_phonebook_list_cb_pbap_n, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

