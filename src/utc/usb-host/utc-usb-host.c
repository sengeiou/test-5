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

#include <usb_host.h>
#include <string.h>
#include <linux/usb/ch9.h>
#include <system_info.h>
#include <unistd.h>

//& set: UsbHost

/* Values defined for test gadget */
#define TEST_BCD_USB 0x00
#define TEST_B_DEVICE_CLASS 0x0
#define TEST_B_DEVICE_SUB_CLASS 0x0
#define TEST_B_DEVICE_PROTOCOL 0x0
#define TEST_B_MAX_PACKET_SIZE_0 0x40
#define TEST_ID_VENDOR 0x1D6B
#define TEST_ID_PRODUCT 0x104
#define TEST_BCD_DEVICE 0x1

#define TEST_NUM_CONFIGURATIONS 1
#define TEST_MANUFACTURER "Foo Inc."
#define TEST_PRODUCT "Bar Gadget"
#define TEST_SERIAL_NUMBER "0123456789"
#define TEST_CFG_SELF_POWERED false
#define TEST_CFG_SUPPORT_REMOTE_WAKEUP false
#define TEST_CFG_MAX_POWER 0x2
#define TEST_CFG_STR "usb host API test config"

#define TEST_NUM_INTERFACES 1
#define TEST_IFACE_STR "loop input to output"

#define TEST_NUM_ENDPOINTS 4
#define TEST_EP_TRANSFER_TYPE USB_HOST_TRANSFER_TYPE_BULK
#define TEST_EP_SYNCH_TYPE USB_HOST_ISO_SYNC_TYPE_NONE
#define TEST_EP_USAGE_TYPE USB_HOST_USAGE_TYPE_DATA
#define TEST_EP_MAX_PACKET_SIZE 0x0200

#define TEST_DATA "Quick brown fox jumps over a lazy dog"

static usb_host_context_h ctx = NULL;
static usb_host_device_h dev = NULL;
static usb_host_config_h cfg = NULL;
static usb_host_interface_h iface = NULL;
static usb_host_endpoint_h ep1 = NULL; /**< Bulk in */
static usb_host_endpoint_h ep2 = NULL; /**< Bulk out */
static usb_host_endpoint_h ep3 = NULL; /**< Interrupt in */
static usb_host_endpoint_h ep4 = NULL; /**< Interrupt out */
static usb_host_transfer_h transfer1 = NULL;
static usb_host_transfer_h transfer_control = NULL;
static unsigned char transfer_buffer[sizeof(TEST_DATA)];
static int enabled = -1;
static int transfer_active = 0;

static int usb_host_feature_enabled(void)
{
	int ret;
	bool val;

	if (enabled >= 0)
		return enabled;

	ret = system_info_get_platform_bool("http://tizen.org/feature/usb.host", &val);
	if (ret == SYSTEM_INFO_ERROR_NONE && val)
		enabled = 1;
	else
		enabled = 0;

	return enabled;
}

#define assert_eq_supp(var, ref) \
	do { \
		if (usb_host_feature_enabled()) \
			assert_eq(var, ref); \
		else \
			assert_eq(var, USB_HOST_ERROR_NOT_SUPPORTED); \
	} while (0)

#define assert_streq(var, ref) \
    do { \
        if (strcmp(var, ref)) { \
            fprintf(stderr, \
                "\\n[TCT][%s][Line : %d] Assert fail; Values (%s == %s) is not equal to (%s == %s)\\n", \
                __FILE__, __LINE__,  #var, var, #ref, ref); \
            return 1; \
        } \
    } while (0)

static void transfer_callback(usb_host_transfer_h transfer, void *user_data)
{
	transfer_active = 0;
	usb_host_transfer_destroy(transfer);
}

/**
 * @testcase		utc_usb_host_create_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Initialize context of usb-host
 * @scenario  		Calling usb_host_create should create intialized context of library.
 */
int utc_usb_host_create_p(void)
{
	int ret;

	ret = usb_host_create(&ctx);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_neq(ctx, NULL);

	usb_host_destroy(ctx);

	return 0;
}

/**
 * @testcase		utc_usb_host_create_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Initialize context of usb-host
 * @scenario  		Calling usb_host_create with NULL parameter should end with error.
 */
int utc_usb_host_create_n(void)
{
	int ret;

	ret = usb_host_create(NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_get_device_list_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get list of all connected devices
 * @scenario  		Calling usb_host_get_device_list should return positive number
 * 	of devices.
 */
int utc_usb_host_get_device_list_p(void)
{
	usb_host_device_h *devs;
	int len;
	int ret;

	ret = usb_host_get_device_list(ctx, &devs, &len);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_gt(len, 0);

	usb_host_free_device_list(devs, 1);

	return 0;
}

/**
 * @testcase		utc_usb_host_get_device_list_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get list of all connected devices
 * @scenario  		Calling usb_host_get_device_list with NULL should result
 * in INVALID_PARAMETER error.
 */
int utc_usb_host_get_device_list_n(void)
{
	int ret;

	ret = usb_host_get_device_list(NULL, NULL, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_free_device_list_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Free list of devices
 * @scenario  		Calling usb_host_free_device_list with NULL should result
 * in INVALID_PARAMETER error.
 */
int utc_usb_host_free_device_list_n(void)
{
	int ret;

	ret = usb_host_free_device_list(NULL, 0);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_open_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Open a device
 * @scenario  		Opening previously prepared device should end with success.
 */
int utc_usb_host_device_open_p(void)
{
	usb_host_device_h *devs;
	int len;
	int ret;
	int i;
	int vid, pid;

	ret = usb_host_get_device_list(ctx, &devs, &len);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE) {
		for (i = 0; i < len; ++i) {
			ret = usb_host_device_get_id_vendor(devs[i], &vid);
			assert_eq_supp(ret, USB_HOST_ERROR_NONE);
			ret = usb_host_device_get_id_product(devs[i], &pid);
			assert_eq_supp(ret, USB_HOST_ERROR_NONE);

			if (pid == TEST_ID_PRODUCT && vid == TEST_ID_VENDOR) {
				ret = usb_host_device_open(devs[i]);
				assert_eq_supp(ret, USB_HOST_ERROR_NONE);

				usb_host_device_close(devs[i]);
				goto out;
			}
		}
	}

out:
	usb_host_free_device_list(devs, 1);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_open_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Open a device
 * @scenario  		Opening NULL device should end with ERROR_INVALID
 */
int utc_usb_host_device_open_n(void)
{
	int ret;

	ret = usb_host_device_open(NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_close_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Close a device
 * @scenario  		Closing an opened device should be possible and end with success.
 */
int utc_usb_host_device_close_p(void)
{
	usb_host_device_h dev1;
	int ret;

	ret = usb_host_device_open_with_vid_pid(ctx, TEST_ID_VENDOR, TEST_ID_PRODUCT, &dev1);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	ret = usb_host_device_close(dev1);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_close_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Close a device
 * @scenario  		Closing NULL shoud end with ERROR_INVALID_PARAMETER
 */
int utc_usb_host_device_close_n(void)
{
	int ret;

	ret = usb_host_device_close(NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_open_with_vid_pid_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Open a device with given vid and pid
 * @scenario  		Device with these values is created in test environment and
 * it should be possible to open it
 */
int utc_usb_host_device_open_with_vid_pid_p(void)
{
	usb_host_device_h dev1;
	int ret;

	ret = usb_host_device_open_with_vid_pid(ctx, TEST_ID_VENDOR, TEST_ID_PRODUCT, &dev1);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE) {
		ret = usb_host_device_close(dev1);
		if (ret < 0)
			return ret;
	}

	return 0;
}

/**
 * @testcase		utc_usb_host_device_open_with_vid_pid_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Open a device with give vid and pid
 * @scenario  		Opening device with NULL parameter should result in error
 */
int utc_usb_host_device_open_with_vid_pid_n(void)
{
	int ret;

	ret = usb_host_device_open_with_vid_pid(NULL, 0, 0, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_open_with_vid_pid(NULL, TEST_ID_VENDOR, TEST_ID_PRODUCT, &dev);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_open_with_vid_pid(ctx, TEST_ID_VENDOR, TEST_ID_PRODUCT, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_ref_device_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Increase device refcount
 * @scenario  		Check if operation is successful
 */
int utc_usb_host_ref_device_p(void)
{
	int ret;

	ret = usb_host_ref_device(dev);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	ret = usb_host_unref_device(dev);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_ref_device_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Increase device refcount
 * @scenario  		Check if passing NULL as parameter ends with INVALID_PARAMETER error
 */
int utc_usb_host_ref_device_n(void)
{
	int ret;

	ret = usb_host_ref_device(NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_unref_device_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Decrease device refcount
 * @scenario  		Check if operation is successful
 */
int utc_usb_host_unref_device_p(void)
{
	int ret;

	ret = usb_host_ref_device(dev);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	ret = usb_host_unref_device(dev);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_unref_device_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Decrease device refcount
 * @scenario  		Check if passing NULL as parameter ends with INVALID_PARAMETER error
 */
int utc_usb_host_unref_device_n(void)
{
	int ret;

	ret = usb_host_unref_device(NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_bus_number_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get device bus number
 * @scenario  		Device bus number should be retrieved successfully
 */
int utc_usb_host_device_get_bus_number_p(void)
{
	int ret;
	int bus_number;

	ret = usb_host_device_get_bus_number(dev, &bus_number);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_bus_number_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get device bus number
 * @scenario  		Function should end with error when NULL is passed as parameter
 */
int utc_usb_host_device_get_bus_number_n(void)
{
	int ret;
	int bus_number;

	ret = usb_host_device_get_bus_number(NULL, &bus_number);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_bus_number(dev, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_address_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get device address
 * @scenario  		Device bus number should be retrieved successfully
 */
int utc_usb_host_device_get_address_p(void)
{
	int ret;
	int addr;

	ret = usb_host_device_get_address(dev, &addr);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_address_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get device address
 * @scenario  		Function should end with error when NULL is passed as parameter
 */
int utc_usb_host_device_get_address_n(void)
{
	int ret;
	int addr;

	ret = usb_host_device_get_address(NULL, &addr);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_address(dev, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_config_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get configuration
 * @scenario  		Non-null configuration should be retrieved form index 0
 */
int utc_usb_host_device_get_config_p(void)
{
	usb_host_config_h config;
	int ret;

	ret = usb_host_device_get_config(dev, 0, &config);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);
	assert_neq(config, NULL);

	usb_host_config_destroy(config);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_config_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get configuration
 * @scenario  		Function should return error when NULL parameter is passed
 */
int utc_usb_host_device_get_config_invalid_n(void)
{
	usb_host_config_h config;
	int ret;

	ret = usb_host_device_get_config(NULL, 0, &config);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_config(dev, 0, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_config_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get configuration
 * @scenario  		Function should return error when there is no such configuration
 */
int utc_usb_host_device_get_config_not_found_n(void)
{
	usb_host_config_h config;
	int ret;

	ret = usb_host_device_get_config(dev, 0xff, &config);
	assert_eq_supp(ret, USB_HOST_ERROR_NOT_FOUND);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_active_config_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get configuration
 * @scenario  		Non-null configuration should be retrieved as active config
 */
int utc_usb_host_get_active_config_p(void)
{
	usb_host_config_h config;
	int ret;

	ret = usb_host_get_active_config(dev, &config);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);
	assert_neq(config, NULL);

	usb_host_config_destroy(config);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_active_config_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get configuration
 * @scenario  		Function should return error when NULL parameter is passed
 */
int utc_usb_host_get_active_config_n(void)
{
	usb_host_config_h config;
	int ret;

	ret = usb_host_get_active_config(NULL, &config);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_get_active_config(dev, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_config_destroy_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Destroy configuration
 * @scenario  		Non-null configuration should be destroyed successfuly
 */
int utc_usb_host_config_destroy_p(void)
{
	usb_host_config_h config;
	int ret;

	ret = usb_host_device_get_config(dev, 0, &config);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);
	assert_neq(config, NULL);

	usb_host_config_destroy(config);

	return 0;
}

/**
 * @testcase		utc_usb_host_config_destroy_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Destroy configuration
 * @scenario  		Passing NULL configuration should end with ERROR_INVALID_PARAMETER
 */
int utc_usb_host_config_destroy_n(void)
{
	usb_host_config_h config;
	int ret;

	ret = usb_host_device_get_config(NULL, 0, &config);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_config(dev, 0, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_set_config_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Set given config
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_set_config_n(void)
{
	int ret;

	ret = usb_host_set_config(NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_set_config_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Set given config
 * @scenario  		Checks if passing valid parameter results in USB_HOST_ERROR_NONE
 */
int utc_usb_host_set_config_p(void)
{
	int ret;

	ret = usb_host_set_config(cfg);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_bcd_usb_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get bcdUSB field from device
 * @scenario  		Retrieved bcdUSB should be equal to expected one
 */
int utc_usb_host_device_get_bcd_usb_p(void)
{
	int bcd_usb;
	int ret;

	ret = usb_host_device_get_bcd_usb(dev, &bcd_usb);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_neq(bcd_usb, TEST_BCD_USB);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_bcd_usb_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get bcdUSB field from device
 * @scenario  		Function should end with error when NULL parameter is passed
 */
int utc_usb_host_device_get_bcd_usb_n(void)
{
	int bcd_usb;
	int ret;

	ret = usb_host_device_get_bcd_usb(NULL, &bcd_usb);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_class_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get bDeviceClass value from device
 * @scenario  		Checks if retrieved class value matches expected one
 */
int utc_usb_host_device_get_class_p(void)
{
	int device_class;
	int ret;

	ret = usb_host_device_get_class(dev, &device_class);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(device_class, TEST_B_DEVICE_CLASS);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_class_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get bDeviceClass value from device
 * @scenario  		Checks if passing NULL as parameter result in INVALID_PARAMETER error
 */
int utc_usb_host_device_get_class_n(void)
{
	int ret;
	int device_class;

	ret = usb_host_device_get_class(dev, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_class(NULL, &device_class);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_sub_class_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get bDeviceSubClass value from device
 * @scenario  		Checks if retrieved subclass value matches expected one
 */
int utc_usb_host_device_get_sub_class_p(void)
{
	int ret;
	int sub_class;

	ret = usb_host_device_get_class(dev, &sub_class);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(sub_class, TEST_B_DEVICE_SUB_CLASS);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_sub_class_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get bDeviceSubClass value from device
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_device_get_sub_class_n(void)
{
	int ret;
	int sub_class;

	ret = usb_host_device_get_sub_class(NULL, &sub_class);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_sub_class(dev, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_protocol_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get bDeviceProtocol value from device
 * @scenario  		Checks if retrieved value matches expected value
 */
int utc_usb_host_device_get_protocol_p(void)
{
	int ret;
	int protocol;

	ret = usb_host_device_get_protocol(dev, &protocol);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(protocol, TEST_B_DEVICE_PROTOCOL);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_protocol_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get bDeviceProtocol value from device
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_device_get_protocol_n(void)
{
	int ret;
	int protocol;

	ret = usb_host_device_get_class(NULL, &protocol);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_class(dev, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_max_packet_size_0_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get bDeviceMaxPacketSize0 value from device
 * @scenario  		Checks if max packet size is returned correctly.
 */
int utc_usb_host_device_get_max_packet_size_0_p(void)
{
	int ret;
	int size;

	ret = usb_host_device_get_max_packet_size_0(dev, &size);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(size, TEST_B_MAX_PACKET_SIZE_0);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_max_packet_size_0_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get bDeviceMaxPacketSize0 value from device
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_device_get_max_packet_size_0_n(void)
{
	int ret;
	int size;

	ret = usb_host_device_get_max_packet_size_0(dev, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_max_packet_size_0(NULL, &size);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_id_vendor_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get idVendor value from device
 * @scenario  		Checks if returned value matches expected value
 */
int utc_usb_host_device_get_id_vendor_p(void)
{
	int ret;
	int vid;

	ret = usb_host_device_get_id_vendor(dev, &vid);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(vid, TEST_ID_VENDOR);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_id_vendor_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get idVendor value from device
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_device_get_id_vendor_n(void)
{
	int ret;
	int vid;

	ret = usb_host_device_get_id_vendor(dev, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_id_vendor(NULL, &vid);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_id_product_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get idProduct value from device
 * @scenario  		Checks if returned value matches expected value
 */
int utc_usb_host_device_get_id_product_p(void)
{
	int ret;
	int pid;

	ret = usb_host_device_get_id_product(dev, &pid);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(pid, TEST_ID_PRODUCT);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_id_product_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get idProduct value from device
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_device_get_id_product_n(void)
{
	int ret;
	int pid;

	ret = usb_host_device_get_id_product(dev, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_id_product(NULL, &pid);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_bcd_device_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get bcdDevice value from device
 * @scenario  		Checks if returned value matches expected value
 */
int utc_usb_host_device_get_bcd_device_p(void)
{
	int ret;
	int bcd;

	ret = usb_host_device_get_bcd_device(dev, &bcd);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(bcd, TEST_BCD_DEVICE);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_bcd_device_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get bcdDevice value from device
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_device_get_bcd_device_n(void)
{
	int ret;
	int bcd;

	ret = usb_host_device_get_bcd_device(dev, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_bcd_device(NULL, &bcd);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_num_configurations_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get number of configurations from device
 * @scenario  		Checks if returned value matches expected value
 */
int utc_usb_host_device_get_num_configurations_p(void)
{
	int ret;
	int num;

	ret = usb_host_device_get_num_configurations(dev, &num);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(num, TEST_NUM_CONFIGURATIONS);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_num_configurations_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get number of configurations from device
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_device_get_num_configurations_n(void)
{
	int ret;
	int num;

	ret = usb_host_device_get_num_configurations(NULL, &num);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_num_configurations(dev, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_is_device_opened_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Check if device is opened
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_is_device_opened_p(void)
{
	int ret;
	bool opened;

	ret = usb_host_device_open_with_vid_pid(ctx, TEST_ID_VENDOR, TEST_ID_PRODUCT, &dev);

	if (ret == USB_HOST_ERROR_NONE) {
		ret = usb_host_is_device_opened(dev, &opened);
		assert_eq_supp(ret, USB_HOST_ERROR_NONE);
		assert(opened);

		usb_host_device_close(dev);
		ret = usb_host_is_device_opened(dev, &opened);
		assert_eq_supp(ret, USB_HOST_ERROR_NONE);
		assert(!opened);
	}

	return 0;
}

/**
 * @testcase		utc_usb_host_device_is_device_opened_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Check if device is opened
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_is_device_opened_n(void)
{
	int ret;
	bool opened;

	ret = usb_host_is_device_opened(dev, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_is_device_opened(NULL, &opened);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_manufacturer_str_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get manufacturer string
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_device_get_manufacturer_str_p(void)
{
	int ret;
	unsigned char buffer[256];
	int len = 256;

	ret = usb_host_device_get_manufacturer_str(dev, &len, buffer);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE) {
		assert_streq((const char *)buffer, TEST_MANUFACTURER);
		assert_eq(len, strlen(TEST_MANUFACTURER));
	}

	return 0;
}

/**
 * @testcase		utc_usb_host_get_manufacturer_str_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get manufacturer string
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_device_get_manufacturer_str_n(void)
{
	int ret;
	unsigned char buffer[256];
	int len = 256;

	ret = usb_host_device_get_manufacturer_str(NULL, &len, buffer);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_manufacturer_str(dev, NULL, buffer);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_manufacturer_str(dev, &len, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_product_str_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get product string
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_device_get_product_str_p(void)
{
	int ret;
	unsigned char buffer[256];
	int len = 256;

	ret = usb_host_device_get_product_str(dev, &len, buffer);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE) {
		assert_streq((const char *)buffer, TEST_PRODUCT);
		assert_eq(len, strlen(TEST_PRODUCT));
	}

	return 0;
}

/**
 * @testcase		utc_usb_host_get_product_str_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get product string
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_device_get_product_str_n(void)
{
	int ret;
	unsigned char buffer[256];
	int len = 256;

	ret = usb_host_device_get_product_str(NULL, &len, buffer);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_product_str(dev, NULL, buffer);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_product_str(dev, &len, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_serial_number_str_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get serial number string
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_device_get_serial_number_str_p(void)
{
	int ret;
	unsigned char buffer[256];
	int len = 256;

	ret = usb_host_device_get_serial_number_str(dev, &len, buffer);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE) {
		assert_streq((const char *)buffer, TEST_SERIAL_NUMBER);
		assert_eq(len, strlen(TEST_SERIAL_NUMBER));
	}

	return 0;
}

/**
 * @testcase		utc_usb_host_get_product_str_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get product string
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_device_get_serial_number_str_n(void)
{
	int ret;
	unsigned char buffer[256];
	int len = 256;

	ret = usb_host_device_get_serial_number_str(NULL, &len, buffer);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_serial_number_str(dev, NULL, buffer);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_serial_number_str(dev, &len, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_get_num_interfaces_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get number of interfaces
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_config_get_num_interfaces_p(void)
{
	int ret;
	int num;

	ret = usb_host_config_get_num_interfaces(cfg, &num);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(num, TEST_NUM_INTERFACES);

	return 0;
}

/**
 * @testcase		utc_usb_host_get_num_interfaces_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get number of interfaces
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_config_get_num_interfaces_n(void)
{
	int ret;
	int num;

	ret = usb_host_config_get_num_interfaces(NULL, &num);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_config_get_num_interfaces(cfg, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_is_self_powered_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Check if device is self-powered
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_config_is_self_powered_p(void)
{
	int ret;
	bool self_powered;

	ret = usb_host_config_is_self_powered(cfg, &self_powered);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(self_powered, TEST_CFG_SELF_POWERED);

	return 0;
}

/**
 * @testcase		utc_usb_host_is_self_powered_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Check if device is self-powered
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_config_is_self_powered_n(void)
{
	int ret;
	bool self_powered;

	ret = usb_host_config_is_self_powered(NULL, &self_powered);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_config_is_self_powered(cfg, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_config_support_remote_wakeup_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Check if device supports remote wakeup
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_config_support_remote_wakeup_p(void)
{
	int ret;
	bool support;

	ret = usb_host_config_support_remote_wakeup(cfg, &support);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(support, TEST_CFG_SUPPORT_REMOTE_WAKEUP);

	return 0;
}

/**
 * @testcase		utc_usb_host_config_support_remote_wakeup_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Check if device supports remote wakeup
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_config_support_remote_wakeup_n(void)
{
	int ret;
	bool support;

	ret = usb_host_config_support_remote_wakeup(NULL, &support);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_config_support_remote_wakeup(cfg, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_config_get_max_power_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get max power in given configuration
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_config_get_max_power_p(void)
{
	int ret;
	int max_power;

	ret = usb_host_config_get_max_power(cfg, &max_power);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(max_power, TEST_CFG_MAX_POWER);

	return 0;
}

/**
 * @testcase		utc_usb_host_config_get_max_power_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get max power in given configuration
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_config_get_max_power_n(void)
{
	int ret;
	int max_power;

	ret = usb_host_config_get_max_power(NULL, &max_power);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_config_get_max_power(cfg, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_config_get_str_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get config string
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_config_get_str_p(void)
{
	int ret;
	unsigned char buffer[256];
	int len = 256;

	ret = usb_host_device_get_config_str(cfg, &len, buffer);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE) {
		assert_streq((const char *)buffer, TEST_CFG_STR);
		assert_eq(len, strlen(TEST_CFG_STR));
	}

	return 0;
}

/**
 * @testcase		utc_usb_host_interface_get_altsetting_n
 * @since_tizen		4.0
 * @type		negative
 * @description		Get interface altsetting
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_interface_get_altsetting_n(void)
{
	int ret;
	int setting;

	ret = usb_host_interface_get_altsetting(NULL, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_interface_get_altsetting(NULL, &setting);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_config_get_str_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get config string
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_config_get_str_n(void)
{
	int ret;
	unsigned char buffer[256];
	int len = 256;

	ret = usb_host_device_get_config_str(NULL, &len, buffer);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_config_str(cfg, NULL, buffer);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_device_get_config_str(cfg, &len, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_get_port_numbers_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get device port numbers
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_device_get_port_numbers_n(void)
{
	int ret;

	ret = usb_host_device_get_port_numbers(NULL, NULL, 1, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_config_get_interface_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get an interface
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_config_get_interface_p(void)
{
	int ret;
	usb_host_interface_h iface;

	ret = usb_host_config_get_interface(cfg, 0, &iface);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_neq(iface, NULL);

	return 0;
}

/**
 * @testcase		utc_usb_host_config_get_interface_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get an interface
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_config_get_interface_n(void)
{
	int ret;
	usb_host_interface_h iface;

	ret = usb_host_config_get_interface(NULL, 0, &iface);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_config_get_interface(cfg, 0, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_claim_interface_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Claim an interface
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_claim_interface_p(void)
{
	int ret;

	ret = usb_host_claim_interface(iface, 1);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		usb_host_release_interface(iface);

	return 0;
}

/**
 * @testcase		utc_usb_host_claim_interface_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Claim an interface
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_claim_interface_n(void)
{
	int ret;

	ret = usb_host_claim_interface(NULL, 0);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_release_interface_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Release an interface
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_release_interface_p(void)
{
	int ret;

	ret = usb_host_claim_interface(iface, 1);

	if (ret == USB_HOST_ERROR_NONE) {
		ret = usb_host_release_interface(iface);
		assert_eq_supp(ret, USB_HOST_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_usb_host_release_interface_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Release an interface
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_release_interface_n(void)
{
	int ret;

	ret = usb_host_release_interface(NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_interface_get_number_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get an interface number
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_interface_get_number_p(void)
{
	int ret;
	int number;

	ret = usb_host_interface_get_number(iface, &number);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(number, 0);

	return 0;
}

/**
 * @testcase		utc_usb_host_interface_get_number_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get an interface number
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_interface_get_number_n(void)
{
	int ret;
	int number;

	ret = usb_host_interface_get_number(NULL, &number);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_interface_get_number(iface, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_interface_get_num_endpoints_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get number of endpoints in interface
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_interface_get_num_endpoints_p(void)
{
	int ret;
	int num;

	ret = usb_host_interface_get_num_endpoints(iface, &num);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(num, TEST_NUM_ENDPOINTS);

	return 0;
}

/**
 * @testcase		utc_usb_host_interface_get_num_endpoints_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get number of endpoints in interface
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_interface_get_num_endpoints_n(void)
{
	int ret;
	int num;

	ret = usb_host_interface_get_num_endpoints(NULL, &num);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_interface_get_num_endpoints(iface, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_interface_get_endpoint_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get an endpoint from interface
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_interface_get_endpoint_p(void)
{
	int ret;

	ret = usb_host_interface_get_endpoint(iface, 1, &ep1);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_neq(ep1, NULL);

	return 0;
}

/**
 * @testcase		utc_usb_host_interface_get_endpoint_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get an endpoint from interface
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_interface_get_endpoint_n(void)
{
	int ret;

	ret = usb_host_interface_get_endpoint(NULL, 1, &ep1);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_interface_get_endpoint(iface, 1, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_interface_get_str_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get an interface string
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_interface_get_str_p(void)
{
	int ret;
	unsigned char buffer[256];
	int len = 256;

	ret = usb_host_interface_get_str(iface, &len, buffer);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE) {
		assert_streq((const char *)buffer, TEST_IFACE_STR);
		assert_eq(len, strlen(TEST_IFACE_STR));
	}

	return 0;
}

/**
 * @testcase		utc_usb_host_interface_get_str_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get an interface string
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_interface_get_str_n(void)
{
	int ret;
	unsigned char buffer[256];
	int len = 256;

	ret = usb_host_interface_get_str(NULL, &len, buffer);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_interface_get_str(iface, NULL, buffer);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_interface_get_str(iface, &len, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_endpoint_get_number_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get an endpoint number
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_endpoint_get_number_p(void)
{
	int ret;
	int num;

	ret = usb_host_endpoint_get_number(ep1, &num);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(num, 1);

	return 0;
}

/**
 * @testcase		utc_usb_host_endpoint_get_number_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get an endpoint number
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_endpoint_get_number_n(void)
{
	int ret;
	int num;

	ret = usb_host_endpoint_get_number(NULL, &num);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_endpoint_get_number(ep1, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_endpoint_get_direction_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get an endpoint direction
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_endpoint_get_direction_p(void)
{
	int ret;
	usb_host_endpoint_direction_e dir;

	ret = usb_host_endpoint_get_direction(ep1, &dir);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(dir, USB_HOST_DIRECTION_IN);

	return 0;
}

/**
 * @testcase		utc_usb_host_endpoint_get_direction_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get an endpoint direction
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_endpoint_get_direction_n(void)
{
	int ret;
	usb_host_endpoint_direction_e dir;

	ret = usb_host_endpoint_get_direction(NULL, &dir);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_endpoint_get_direction(ep1, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_endpoint_get_transfer_type_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get an endpoint transfer type
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_endpoint_get_transfer_type_p(void)
{
	int ret;
	usb_host_transfer_type_e type;

	ret = usb_host_endpoint_get_transfer_type(ep1, &type);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(type, TEST_EP_TRANSFER_TYPE);

	return 0;
}

/**
 * @testcase		utc_usb_host_endpoint_get_transfer_type_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get an endpoint transfer type
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_endpoint_get_transfer_type_n(void)
{
	int ret;
	usb_host_transfer_type_e type;

	ret = usb_host_endpoint_get_transfer_type(NULL, &type);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_endpoint_get_transfer_type(ep1, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_endpoint_get_synch_type_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get an endpoint synchronization type
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_endpoint_get_synch_type_p(void)
{
	int ret;
	usb_host_iso_sync_type_e type;

	ret = usb_host_endpoint_get_synch_type(ep1, &type);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(type, TEST_EP_SYNCH_TYPE);

	return 0;
}

/**
 * @testcase		utc_usb_host_endpoint_get_synch_type_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get an endpoint synchronization type
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_endpoint_get_synch_type_n(void)
{
	int ret;
	usb_host_iso_sync_type_e type;

	ret = usb_host_endpoint_get_synch_type(NULL, &type);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_endpoint_get_synch_type(ep1, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_endpoint_get_usage_type_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get an endpoint usage type
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_endpoint_get_usage_type_p(void)
{
	int ret;
	usb_host_usage_type_e type;

	ret = usb_host_endpoint_get_usage_type(ep1, &type);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(type, TEST_EP_USAGE_TYPE);

	return 0;
}

/**
 * @testcase		utc_usb_host_endpoint_get_usage_type_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get an endpoint usage type
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_endpoint_get_usage_type_n(void)
{
	int ret;
	usb_host_usage_type_e type;

	ret = usb_host_endpoint_get_usage_type(NULL, &type);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_endpoint_get_usage_type(ep1, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_endpoint_get_max_packet_size_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get an endpoint max packet size
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_endpoint_get_max_packet_size_p(void)
{
	int ret;
	int size;

	ret = usb_host_endpoint_get_max_packet_size(ep1, &size);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(size, TEST_EP_MAX_PACKET_SIZE);

	return 0;
}

/**
 * @testcase		utc_usb_host_endpoint_get_max_packet_size_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get an endpoint max packet size
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_endpoint_get_max_packet_size_n(void)
{
	int ret;
	int size;

	ret = usb_host_endpoint_get_max_packet_size(NULL, &size);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_endpoint_get_max_packet_size(ep1, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_endpoint_get_interval_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Get an endpoint interval
 * @scenario  		Checks if returned value is correct
 */
int utc_usb_host_endpoint_get_interval_p(void)
{
	int ret;
	int interval;

	ret = usb_host_endpoint_get_interval(ep1, &interval);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(interval, 0);

	return 0;
}

/**
 * @testcase		utc_usb_host_endpoint_get_interval_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Get an endpoint interval
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_endpoint_get_interval_n(void)
{
	int ret;
	int interval;

	ret = usb_host_endpoint_get_interval(NULL, &interval);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_endpoint_get_interval(ep1, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

static int test_loopback_transfer(usb_host_endpoint_h in, usb_host_endpoint_h out)
{
	int ret;
	int transfered;
	unsigned char buf[sizeof(TEST_DATA)];
	int retry = 10;
	int timeout = 2000;

	ret = usb_host_claim_interface(iface, 1);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	while (retry--) {
		ret = usb_host_transfer(out, TEST_DATA, sizeof(TEST_DATA), &transfered, timeout);
		if (ret == USB_HOST_ERROR_TIMED_OUT)
			continue;

		assert_eq_supp(ret, USB_HOST_ERROR_NONE);

		if (ret == USB_HOST_ERROR_NONE)
			assert_eq(transfered, sizeof(TEST_DATA));

		ret = usb_host_transfer(in, buf, sizeof(TEST_DATA), &transfered, timeout);
		if (ret == USB_HOST_ERROR_TIMED_OUT)
			continue;

		assert_eq_supp(ret, USB_HOST_ERROR_NONE);

		if (ret == USB_HOST_ERROR_NONE) {
			assert_eq(transfered, sizeof(TEST_DATA));
			assert_streq((const char *)buf, TEST_DATA);
		}

		ret = usb_host_release_interface(iface);
		assert_eq_supp(ret, USB_HOST_ERROR_NONE);

		return 0;
	}

	ret = usb_host_release_interface(iface);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 1;
}

/**
 * @testcase		utc_usb_host_interrupt_transfer_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Performs an interrupt transfer
 * @scenario  		Send test data to loopback device on OUT endpoint, expecting the same data returned on IN endpoint.
 */
int utc_usb_host_interrupt_transfer_p(void)
{
	return test_loopback_transfer(ep3, ep4);
}

/**
 * @testcase		utc_usb_host_transfer_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Performs a transfer
 * @scenario  		Send test data to loopback device on OUT endpoint, expecting the same data returned on IN endpoint.
 */
int utc_usb_host_transfer_p(void)
{
	return test_loopback_transfer(ep1, ep2);
}

/**
 * @testcase		utc_usb_host_transfer_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Performs a transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_transfer_n(void)
{
	int ret;
	int transfered;

	ret = usb_host_transfer(NULL, TEST_DATA, sizeof(TEST_DATA), &transfered, 0);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_transfer(ep2, NULL, sizeof(TEST_DATA), &transfered, 0);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_transfer(ep2, TEST_DATA, sizeof(TEST_DATA), NULL, 0);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_usb_host_control_transfer_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Performs a control transfer
 * @scenario  		Check if device return expected data
 */
int utc_usb_host_control_transfer_p(void)
{
	int ret;
	int transfered;
	struct usb_device_descriptor desc;

	ret = usb_host_control_transfer(dev, 0x80, 0x06, 0x0100, 0x0000, (unsigned char *)&desc, sizeof(desc), 0, &transfered);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	if (ret == USB_HOST_ERROR_NONE) {
		assert_eq(transfered, sizeof(desc));
		assert_neq(desc.bcdUSB, TEST_BCD_USB);
		assert_eq(desc.bDeviceClass, TEST_B_DEVICE_CLASS);
		assert_eq(desc.bDeviceSubClass, TEST_B_DEVICE_SUB_CLASS);
		assert_eq(desc.bDeviceProtocol, TEST_B_DEVICE_PROTOCOL);
		assert_eq(desc.bMaxPacketSize0, TEST_B_MAX_PACKET_SIZE_0);
		assert_eq(desc.idVendor, TEST_ID_VENDOR);
		assert_eq(desc.idProduct, TEST_ID_PRODUCT);
		assert_eq(desc.bcdDevice, TEST_BCD_DEVICE);
	}

	return 0;
}

/**
 * @testcase		utc_usb_host_control_transfer_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Performs a control transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_control_transfer_n(void)
{
	int ret;
	int transfered;
	struct usb_device_descriptor desc;

	ret = usb_host_control_transfer(NULL, 0x80, 0x06, 0x0100, 0x0000, (unsigned char *)&desc, 12, 0, &transfered);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_control_transfer(dev, 0x80, 0x06, 0x0100, 0x0000, NULL, 12, 0, &transfered);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	ret = usb_host_control_transfer(dev, 0x80, 0x06, 0x0100, 0x0000, (unsigned char *)&desc, 12, 0, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_set_altsetting_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Set an altsetting
 * @scenario  		Setting altsetting 0 should always be possible
 */
int utc_usb_host_set_altsetting_p(void)
{
	int ret;

	ret = usb_host_interface_set_altsetting(iface, 0);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_set_altsetting_n
 * @since_tizen		3.0
 * @type		negative
 * @description		Set an altsetting
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_set_altsetting_n(void)
{
	int ret;

	ret = usb_host_interface_set_altsetting(NULL, 0);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_device_unconfigure_n
 * @since_tizen		4.0
 * @type		negative
 * @description		Set device in unconfigured state
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_device_unconfigure_n(void)
{
	int ret;

	ret = usb_host_device_unconfigure(NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_create_transfer_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Create transfer handle
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_create_transfer_n(void)
{
	int ret;

	ret = usb_host_create_transfer(NULL, NULL, NULL, 0, NULL, 0, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_create_transfer_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Create isochronous transfer handle
 * @scenario  		Checks if the result is USB_HOST_ERROR_NONE
 */
int utc_usb_host_create_transfer_p(void)
{
	int ret;
	unsigned char buf[sizeof(TEST_DATA)];
	usb_host_transfer_h transfer;

	ret = usb_host_create_transfer(ep2, transfer_callback, buf, sizeof(TEST_DATA), NULL, 0, &transfer);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_create_isochronous_transfer_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Create isochronous transfer handle
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_create_isochronous_transfer_n(void)
{
	int ret;

	ret = usb_host_create_isochronous_transfer(NULL, NULL, NULL, 0, 0, NULL, 0, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_create_control_transfer_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Create control transfer handle
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_create_control_transfer_n(void)
{
	int ret;

	ret = usb_host_create_control_transfer(NULL, NULL, NULL, 0, NULL, 0, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_create_control_transfer_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Create control transfer handle
 * @scenario  		Checks if passing corrent parameters results ERROR_NONE
 */
int utc_usb_host_create_control_transfer_p(void)
{
	int ret;
	unsigned char data[9];
	usb_host_transfer_h transfer;

	ret = usb_host_create_control_transfer(dev, transfer_callback, data, 9, NULL, 0, &transfer);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);
	usb_host_transfer_destroy(transfer);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_set_ep_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Sets endpoint for transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_transfer_set_ep_n(void)
{
	int ret;

	ret = usb_host_transfer_set_ep(NULL, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_set_ep_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Sets endpoint for transfer
 * @scenario  		Checks if functions succeeds
 */
int utc_usb_host_transfer_set_ep_p(void)
{
	int ret;

	ret = usb_host_transfer_set_ep(transfer1, ep2);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_set_callback_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Sets callback for transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_transfer_set_callback_n(void)
{
	int ret;

	ret = usb_host_transfer_set_callback(NULL, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_set_callback_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Sets callback for transfer
 * @scenario  		Checks if functions succeeds
 */
int utc_usb_host_transfer_set_callback_p(void)
{
	int ret;

	ret = usb_host_transfer_set_callback(transfer1, transfer_callback);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_set_data_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Sets data for transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_transfer_set_data_n(void)
{
	int ret;

	ret = usb_host_transfer_set_data(NULL, NULL, 0);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_set_data_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Sets data for transfer
 * @scenario  		Checks if function succeeds
 */
int utc_usb_host_transfer_set_data_p(void)
{
	int ret;

	ret = usb_host_transfer_set_data(transfer1, transfer_buffer, sizeof(transfer_buffer));
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_set_timeout_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Sets timeout for transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_transfer_set_timeout_n(void)
{
	int ret;

	ret = usb_host_transfer_set_timeout(NULL, 0);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_set_timeout_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Sets timeout for transfer
 * @scenario  		Checks if function succeeds
 */
int utc_usb_host_transfer_set_timeout_p(void)
{
	int ret;

	ret = usb_host_transfer_set_timeout(transfer1, 2000);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_set_num_iso_packets_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Sets num_iso_packets for transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_transfer_set_num_iso_packets_n(void)
{
	int ret;

	ret = usb_host_transfer_set_num_iso_packets(NULL, 0);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_set_num_iso_packets_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Sets num_iso_packets for transfer
 * @scenario  		Checks if function succeeds
 */
int utc_usb_host_transfer_set_num_iso_packets_p(void)
{
	int ret;

	ret = usb_host_transfer_set_num_iso_packets(transfer1, 0);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_control_transfer_set_request_type_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Sets request_type field in control transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_control_transfer_set_request_type_n(void)
{
	int ret;

	ret = usb_host_control_transfer_set_request_type(NULL, 0);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_control_transfer_set_request_type_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Sets request_type field in control transfer
 * @scenario  		Checks if function succeeds
 */
int utc_usb_host_control_transfer_set_request_type_p(void)
{
	int ret;

	ret = usb_host_control_transfer_set_request_type(transfer_control, 0x80);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_control_transfer_set_request_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Sets request field in control transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_control_transfer_set_request_n(void)
{
	int ret;

	ret = usb_host_control_transfer_set_request(NULL, 0);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_control_transfer_set_request_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Sets request field in control transfer
 * @scenario  		Check if function succeeds
 */
int utc_usb_host_control_transfer_set_request_p(void)
{
	int ret;

	ret = usb_host_control_transfer_set_request(transfer_control, 0x06);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_control_transfer_set_value_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Sets value field in control transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_control_transfer_set_value_n(void)
{
	int ret;

	ret = usb_host_control_transfer_set_value(NULL, 0);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_control_transfer_set_value_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Sets value field in control transfer
 * @scenario  		Checks if function succeeds
 */
int utc_usb_host_control_transfer_set_value_p(void)
{
	int ret;

	ret = usb_host_control_transfer_set_value(transfer_control, 0x0100);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_control_transfer_set_index_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Sets index field in control transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_control_transfer_set_index_n(void)
{
	int ret;

	ret = usb_host_control_transfer_set_index(NULL, 0);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_control_transfer_set_index_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Sets index field in control transfer
 * @scenario  		Checks if function succeeds
 */
int utc_usb_host_control_transfer_set_index_p(void)
{
	int ret;

	ret = usb_host_control_transfer_set_index(transfer_control, 0x0000);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_get_status_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Gets status of a transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_transfer_get_status_n(void)
{
	int ret;

	ret = usb_host_transfer_get_status(NULL, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_get_status_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Gets status of a transfer
 * @scenario  		Checks if function succeeds
 */
int utc_usb_host_transfer_get_status_p(void)
{
	int ret;
	int status;

	ret = usb_host_transfer_get_status(transfer1, &status);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_get_data_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Gets data of a transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_transfer_get_data_n(void)
{
	int ret;

	ret = usb_host_transfer_get_data(NULL, NULL, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_get_data_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Gets data of a transfer
 * @scenario  		Checks if function succeeds
 */
int utc_usb_host_transfer_get_data_p(void)
{
	int ret;
	unsigned int len;
	unsigned char *data;

	ret = usb_host_transfer_get_data(transfer1, &data, &len);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_control_transfer_get_data_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Gets data of a control_transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_control_transfer_get_data_n(void)
{
	int ret;

	ret = usb_host_control_transfer_get_data(NULL, NULL, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_control_transfer_get_data_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Gets data of a control_transfer
 * @scenario  		Checks if function succeeds
 */
int utc_usb_host_control_transfer_get_data_p(void)
{
	int ret;
	unsigned int len;
	unsigned char *data;

	ret = usb_host_control_transfer_get_data(transfer_control, &data, &len);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_get_length_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Gets length of a transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_transfer_get_length_n(void)
{
	int ret;

	ret = usb_host_transfer_get_length(NULL, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_get_length_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Gets length of a transfer
 * @scenario  		Checks if proper length is returned
 */
int utc_usb_host_transfer_get_length_p(void)
{
	int ret;
	unsigned int len;

	ret = usb_host_transfer_get_length(transfer1, &len);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_get_num_iso_packets_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Gets num_iso_packets of a transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_transfer_get_num_iso_packets_n(void)
{
	int ret;

	ret = usb_host_transfer_get_num_iso_packets(NULL, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_get_num_iso_packets_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Gets num_iso_packets of a transfer
 * @scenario  		Checks if valid number is returned
 */
int utc_usb_host_transfer_get_num_iso_packets_p(void)
{
	int ret;
	unsigned int num;

	ret = usb_host_transfer_get_num_iso_packets(transfer1, &num);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);
	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(num, 0);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_set_iso_packet_length_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Sets iso_packet_length of a transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_transfer_set_iso_packet_length_n(void)
{
	int ret;

	ret = usb_host_transfer_set_iso_packet_length(NULL, 0, 0);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_get_iso_packet_status_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Gets iso_packet_status of a transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_transfer_get_iso_packet_status_n(void)
{
	int ret;

	ret = usb_host_transfer_get_iso_packet_status(NULL, 0, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_get_iso_packet_data_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Gets iso_packet_data of a transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_transfer_get_iso_packet_data_n(void)
{
	int ret;

	ret = usb_host_transfer_get_iso_packet_data(NULL, 0, NULL, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_get_iso_packet_length_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Gets iso_packet_length of a transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_transfer_get_iso_packet_length_n(void)
{
	int ret;

	ret = usb_host_transfer_get_iso_packet_length(NULL, 0, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_get_type_n
 * @since_tizen		5.0
 * @type		negative
 * @description		Gets type of a transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_transfer_get_type_n(void)
{
	int ret;

	ret = usb_host_transfer_get_type(NULL, NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_get_type_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Gets type of a transfer
 * @scenario  		Check if transfer type is returned
 */
int utc_usb_host_transfer_get_type_p(void)
{
	int ret;
	usb_host_transfer_type_e type;

	ret = usb_host_transfer_get_type(transfer1, &type);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);
	if (ret == USB_HOST_ERROR_NONE)
		assert_eq(type, USB_HOST_TRANSFER_TYPE_BULK);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_destroy_n
 * @since_tizen		5.0
 * @type		negative
 * @description		destroy a transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_transfer_destroy_n(void)
{
	int ret;

	ret = usb_host_transfer_destroy(NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_destroy_p
 * @since_tizen		5.0
 * @type		positive
 * @description		destroy a transfer
 * @scenario  		Checks if transfer is correctly destroyed
 */
int utc_usb_host_transfer_destroy_p(void)
{
	int ret;

	ret = usb_host_transfer_destroy(transfer1);
	transfer1 = NULL;
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_submit_n
 * @since_tizen		5.0
 * @type		negative
 * @description		submit a transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_transfer_submit_n(void)
{
	int ret;

	ret = usb_host_transfer_submit(NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_submit_p
 * @since_tizen		5.0
 * @type		positive
 * @description		submit a transfer
 * @scenario  		Checks if transfer is submitted
 */
int utc_usb_host_transfer_submit_p(void)
{
	int ret;

	transfer_active = 1;
	ret = usb_host_transfer_submit(transfer1);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	sleep(1);

	(void)usb_host_transfer_cancel(transfer1);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_cancel_n
 * @since_tizen		5.0
 * @type		negative
 * @description		cancel a transfer
 * @scenario  		Checks if passing NULL as parameter results in INVALID_PARAMETER error
 */
int utc_usb_host_transfer_cancel_n(void)
{
	int ret;

	ret = usb_host_transfer_cancel(NULL);
	assert_eq_supp(ret, USB_HOST_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_usb_host_transfer_cancel_p
 * @since_tizen		5.0
 * @type		positive
 * @description		cancel a transfer
 * @scenario  		Checks if passing correct transfer handle results in cancelation
 */
int utc_usb_host_transfer_cancel_p(void)
{
	int ret;

	transfer_active = 1;
	ret = usb_host_transfer_submit(transfer1);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	sleep(1);

	ret = usb_host_transfer_cancel(transfer1);
	assert_eq_supp(ret, USB_HOST_ERROR_NONE);

	return 0;
}


/**
 * @function            utc_usb_host_context_startup
 * @description         Called before tests that require only context
 * @parameter           NA
 * @return              NA
 */
void utc_usb_host_context_startup(void)
{
	/* TODO handle errors */
	usb_host_create(&ctx);
}

/**
 * @function            utc_usb_host_context_cleanup
 * @description         Called after tests that require only context
 * @parameter           NA
 * @return              NA
 */
void utc_usb_host_context_cleanup(void)
{
	/* TODO handle errors */
	usb_host_destroy(ctx);
	ctx = NULL;
}

/**
 * @function            utc_usb_host_device_startup
 * @description         Called before tests that require opened device
 * @parameter           NA
 * @return              NA
 */
void utc_usb_host_device_startup(void)
{
	/* TODO handle errors */
	usb_host_create(&ctx);
	usb_host_device_open_with_vid_pid(ctx, TEST_ID_VENDOR, TEST_ID_PRODUCT, &dev);
}

/**
 * @function            utc_usb_host_device_cleanup
 * @description         Called after tests that require opened device
 * @parameter           NA
 * @return              NA
 */
void utc_usb_host_device_cleanup(void)
{
	/* TODO handle errors */
	usb_host_device_close(dev);
	dev = NULL;
	usb_host_destroy(ctx);
	ctx = NULL;
}

/**
 * @function            utc_usb_host_config_startup
 * @description         Called before tests that require configuration
 * @parameter           NA
 * @return              NA
 */
void utc_usb_host_config_startup(void)
{
	utc_usb_host_device_startup();
	usb_host_device_get_config(dev, 0, &cfg);
	usb_host_config_get_interface(cfg, 0, &iface);
	usb_host_interface_get_endpoint(iface, 0, &ep1);
	usb_host_interface_get_endpoint(iface, 1, &ep2);
	usb_host_interface_get_endpoint(iface, 2, &ep3);
	usb_host_interface_get_endpoint(iface, 3, &ep4);
}

/**
 * @function            utc_usb_host_config_cleanup
 * @description         Called after tests that require configuration
 * @parameter           NA
 * @return              NA
 */
void utc_usb_host_config_cleanup(void)
{
	utc_usb_host_device_cleanup();
	usb_host_config_destroy(cfg);
	cfg = NULL;
	iface = NULL;
	ep1 = NULL;
	ep2 = NULL;
	ep3 = NULL;
	ep4 = NULL;
}

/**
 * @function            utc_usb_host_async_transfer_startup
 * @description         Called before tests that require asynchronous transfer handler
 * @parameter           NA
 * @return              NA
 */
void utc_usb_host_async_transfer_startup(void)
{
	utc_usb_host_config_startup();
	usb_host_create_transfer(ep1, transfer_callback, transfer_buffer, sizeof(TEST_DATA), NULL, 0, &transfer1);
}

/**
 * @function            utc_usb_host_control_transfer_startup
 * @description         Called before tests that require asynchronous control transfer handler
 * @parameter           NA
 * @return              NA
 */
void utc_usb_host_control_transfer_startup(void)
{
	utc_usb_host_config_startup();
	usb_host_create_control_transfer(dev, transfer_callback, transfer_buffer, sizeof(TEST_DATA), NULL, 0, &transfer_control);
}

/**
 * @function            utc_usb_host_async_transfer_cleanup
 * @description         Called after tests that require asynchronous transfer handler
 * @parameter           NA
 * @return              NA
 */
void utc_usb_host_async_transfer_cleanup(void)
{
	utc_usb_host_config_cleanup();
}

/**
 * @function            utc_usb_host_control_transfer_cleanup
 * @description         Called after tests that require asynchronous control transfer handler
 * @parameter           NA
 * @return              NA
 */
void utc_usb_host_control_transfer_cleanup(void)
{
	utc_usb_host_config_cleanup();
}
