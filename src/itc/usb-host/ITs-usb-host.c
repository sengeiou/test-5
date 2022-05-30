//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-usb-host-common.h"


#define TEST_ID_VENDOR 0x1D6B
#define TEST_ID_PRODUCT 0x104
#define TEST_DATA "Quick brown fox jumps over a lazy dog"
#define DATA_SIZE 9
static unsigned char transfer_buffer[sizeof(TEST_DATA)];
//& set: Usbhost

/** @addtogroup itc-usbhost
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_usbhost_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_usbhost_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	g_bIsFeatureMismatched = false;
	g_bUsbCreation = false;
	g_bFeatureUsb = TCTCheckSystemInfoFeatureSupported(USBHOST_FEATURE, API_NAMESPACE);
	int nRet = usb_host_create(&g_CtxHandle);
	if ( !g_bFeatureUsb)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] usb_host_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s (%d)\\n", __FILE__, __LINE__, UsbHostGetError(nRet), nRet);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] usb_host_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s (%d)", __FILE__, __LINE__, UsbHostGetError(nRet), nRet);
			g_bIsFeatureMismatched = true;
			return;
		}

		FPRINTF("[%s:%d] usb_host_create is unsupported\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] usb_host_create is unsupported", __FILE__, __LINE__);
		g_bIsFeatureMismatched = false;
	}
	else if ( nRet != USB_HOST_ERROR_NONE )
	{
		FPRINTF("[%s:%d] usb_host_create failed, error returned = %s (%d)\\n", __FILE__, __LINE__, UsbHostGetError(nRet), nRet);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] usb_host_create failed, error returned = %s (%d)", __FILE__, __LINE__, UsbHostGetError(nRet), nRet);
		g_bUsbCreation = false;
	}
	else
	{
		g_bUsbCreation = true;
	}
	return;
}


/**
 * @function 		ITs_usbhost_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_usbhost_cleanup(void)
{
	int nRet = 0;
	if (g_CtxHandle) {
		nRet = usb_host_destroy(g_CtxHandle);
		if(nRet !=0)
		{
			FPRINTF("usb_host_destroy failed\\n");
			dlog_print(DLOG_ERROR, "NativeTCT", "usb_host_destroy failed");
		}
		g_CtxHandle = NULL;
	}
	return;
}

/**
* @function				UsbHostHotplugCB
* @description			To Call when usb hotplug connect or disconnect
* @return				NA
*/
void UsbHostHotplugCB(usb_host_device_h dev, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] UsbHostHotplugCB is called\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function				UsbHostTransferCB
* @description			To Call when usb Host Transfer Callback
* @return				NA
*/
static void UsbHostTransferCB(usb_host_transfer_h transfer, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] UsbHostTransferCB is called\\n", __LINE__, API_NAMESPACE);
#endif
}

//& purpose: Registers and Unregisters the hotplug callback
//& type: auto
/**
* @testcase 			ITc_usb_host_set_unset_hotplug_cb_p
* @since_tizen			4.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Registers and Unregisters the hotplug callback
* @scenario				Registers and Unregisters the hotplug callback
* @apicovered			usb_host_set_hotplug_cb, usb_host_unset_hotplug_cb
* @passcase				If target API gets pass
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_usb_host_set_unset_hotplug_cb_p(void)
{
	START_TEST_FEATURE;

	usb_host_hotplug_h hHandle;

	//Callback is NULL as it require usb attach and detach event manually
	int nRet = usb_host_set_hotplug_cb(g_CtxHandle, UsbHostHotplugCB, USB_HOST_HOTPLUG_EVENT_ANY, NULL, &hHandle); 
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_set_hotplug_cb", UsbHostGetError(nRet));
	if(hHandle != NULL)
	{
		nRet = usb_host_unset_hotplug_cb(hHandle);
		PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_unset_hotplug_cb", UsbHostGetError(nRet));
	}
		return 0;
}

//& purpose: create and destroy usb-host handle
//& type: auto
/**
* @testcase 			ITc_usb_host_create_destroy_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			create and destroy usb-host handle
* @scenario			create and destroy usb-host handle
* @apicovered			usb_host_create, usb_host_destroy
* @passcase			If target API gets pass
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_usb_host_create_destroy_p(void)
{
	START_TEST_FEATURE;

	usb_host_context_h hCtxHandle;

	//Target API
	int nRet = usb_host_create(&hCtxHandle);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, " usb_host_create", UsbHostGetError(nRet));
	CHECK_HANDLE(hCtxHandle,"usb_host_create")

	//Target API
	nRet = usb_host_destroy(hCtxHandle);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_destroy", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb host device list
//& type: auto
/**
* @testcase 			ITc_usb_host_get_device_list_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			Get usb host device list
* @scenario			Get usb host device list
* @apicovered			usb_host_get_device_list
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_usb_host_get_device_list_p(void)
{
	START_TEST_FEATURE;
	usb_host_device_h *hDeviceList = NULL;
	int nDeviceLen = -1;

	//Target API
	int nRet = usb_host_get_device_list(g_CtxHandle, &hDeviceList, &nDeviceLen);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_get_device_list", UsbHostGetError(nRet));
	CHECK_HANDLE(hDeviceList,"usb_host_get_device_list")

	if(nDeviceLen < 0)
	{
		FPRINTF("[Line : %d][%s] nDeviceLen is invalid \\n", __LINE__, API_NAMESPACE);
		usb_host_free_device_list(hDeviceList, 1);
		return 1;
	}

	nRet = usb_host_free_device_list(hDeviceList, 1);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_free_device_list", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Open and Close usb host device
//& type: auto
/**
* @testcase 			ITc_usb_host_device_open_close_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 				uto
* @description			Open and Close usb host device
* @scenario			Open and Close usb host device
* @apicovered			usb_host_device_open, usb_host_device_close
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_usb_host_device_open_close_p(void)
{
	START_TEST_FEATURE;
	usb_host_device_h *hDeviceList = NULL;
	int nDeviceLen = -1;;
	int vendirID, productID ,index = 0;

	//Target API
	int nRet = usb_host_get_device_list(g_CtxHandle, &hDeviceList, &nDeviceLen);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_get_device_list", UsbHostGetError(nRet));
	CHECK_HANDLE(hDeviceList,"usb_host_get_device_list")

	if(nDeviceLen < 0)
	{
		FPRINTF("[Line : %d][%s] nDeviceLen is invalid \\n", __LINE__, API_NAMESPACE);
		usb_host_free_device_list(hDeviceList, 1);
		return 1;
	}
	for (index = 0; index < nDeviceLen; ++index)
	{
		nRet = usb_host_device_get_id_vendor(hDeviceList[index], &vendirID);
		PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_id_vendor", UsbHostGetError(nRet), usb_host_free_device_list(hDeviceList, 1));
		nRet = usb_host_device_get_id_product(hDeviceList[index], &productID);
		PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_id_product", UsbHostGetError(nRet), usb_host_free_device_list(hDeviceList, 1));

		if (productID == TEST_ID_PRODUCT && vendirID == TEST_ID_VENDOR) {
			nRet = usb_host_device_open(hDeviceList[index]);
			PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open", UsbHostGetError(nRet),usb_host_free_device_list(hDeviceList, 1));

			nRet = usb_host_device_close(hDeviceList[index]);
			PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet),usb_host_free_device_list(hDeviceList, 1));
		}
	}

	nRet = usb_host_free_device_list(hDeviceList, 1);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_free_device_list", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Open host device with vendor and product id
//& type: auto
/**
* @testcase 			ITc_usb_host_device_open_with_vid_pid_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Open host device with vendor and product id
* @scenario			Open host device with vendor and product id
* @apicovered			usb_host_device_open_with_vid_pid
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_open_with_vid_pid_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));
	return 0;
}

//& purpose: Ref and unref usb host devices
//& type: auto
/**
* @testcase 			ITc_usb_host_ref_unref_device_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			ref and unref usb host devices
* @scenario			ref and unref usb host devices
* @apicovered			usb_host_ref_device, usb_host_unref_device
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_ref_unref_device_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_ref_device(hHostDevice);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_ref_device", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));

	nRet = usb_host_unref_device(hHostDevice);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_unref_device", UsbHostGetError(nRet), usb_host_device_close(hHostDevice));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));
	return 0;
}

//& purpose: Get usb host device bus number
//& type: auto
/**
* @testcase 			ITc_usb_host_device_get_bus_number_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host device bus number
* @scenario			Get usb host device bus number
* @apicovered			usb_host_device_get_bus_number
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_get_bus_number_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	int nBusNumber = -1;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_bus_number(hHostDevice, &nBusNumber);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_bus_number", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb host device address
//& type: auto
/**
* @testcase 			ITc_usb_host_device_get_address_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host device address
* @scenario			Get usb host device address
* @apicovered			usb_host_device_get_address
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_get_address_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	int nAddress = -1;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_address(hHostDevice, &nAddress);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_address", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));
	return 0;
}

//& purpose: Get usb host device config
//& type: auto
/**
* @testcase 			ITc_usb_host_device_get_config_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host device config
* @scenario			Get usb host device config
* @apicovered			usb_host_device_get_config
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_get_config_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle = NULL;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice));

	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));
	return 0;
}

//& purpose: Get usb host device active config
//& type: auto
/**
* @testcase 			ITc_usb_host_get_active_config_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host device active config
* @scenario			Get usb host device active config
* @apicovered			usb_host_get_active_config
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_get_active_config_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_get_active_config(hHostDevice, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_get_active_config", UsbHostGetError(nRet), usb_host_device_close(hHostDevice));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_get_active_config", usb_host_device_close(hHostDevice));

	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));
	return 0;
}

//& purpose: Get usb host device bcd usb
//& type: auto
/**
* @testcase 			ITc_usb_host_device_get_bcd_usb_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host device bcd usb
* @scenario			Get usb host device bcd usb
* @apicovered			usb_host_device_get_bcd_usb
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_get_bcd_usb_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	int bcdUSB =-1;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_bcd_usb(hHostDevice, &bcdUSB);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_bcd_usb", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	if(bcdUSB == TEST_BCD_USB)
	{
		FPRINTF("[Line : %d][%s] bcdUSB is invalid \\n", __LINE__, API_NAMESPACE);
		usb_host_device_close(hHostDevice);
		return 1;
	}

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));
	return 0;
}

//& purpose: Get usb host device class
//& type: auto
/**
* @testcase 			ITc_usb_host_device_get_class_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host device class
* @scenario			Get usb host device class
* @apicovered			usb_host_device_get_class
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_get_class_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	int deviceClass = -1;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_class(hHostDevice, &deviceClass);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_class", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	PRINT_RESULT_CLEANUP(TEST_B_DEVICE_CLASS, deviceClass, "usb_host_device_get_class", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));
	return 0;
}

//& purpose: Get usb host device sub class
//& type: auto
/**
* @testcase 			ITc_usb_host_device_get_sub_class_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host device sub class
* @scenario			Get usb host device sub class
* @apicovered			usb_host_device_get_sub_class
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_get_sub_class_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	int deviceSubClass = -1;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_sub_class(hHostDevice, &deviceSubClass);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_sub_class", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	PRINT_RESULT_CLEANUP(TEST_B_DEVICE_SUB_CLASS, deviceSubClass, "usb_host_device_get_sub_class", UsbHostGetError(nRet), usb_host_device_close(hHostDevice));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));
	return 0;
}


//& purpose: Get usb host device protocol
//& type: auto
/**
* @testcase 			ITc_usb_host_device_get_protocol_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host device protocol
* @scenario			Get usb host device protocol
* @apicovered			usb_host_device_get_protocol
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_get_protocol_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	int deviceProtocol = -1;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_protocol(hHostDevice, &deviceProtocol);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_protocol", UsbHostGetError(nRet), usb_host_device_close(hHostDevice));
	PRINT_RESULT_CLEANUP(TEST_B_DEVICE_PROTOCOL, deviceProtocol, "usb_host_device_get_protocol", UsbHostGetError(nRet), usb_host_device_close(hHostDevice));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));
	return 0;
}

//& purpose: Get usb host device Max packet size
//& type: auto
/**
* @testcase 			ITc_usb_host_device_get_max_packet_size_0_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host device Max packet size
* @scenario			Get usb host device Max packet size
* @apicovered			usb_host_device_get_max_packet_size_0
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_get_max_packet_size_0_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	int deviceMaxPacketSize = -1;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_max_packet_size_0(hHostDevice, &deviceMaxPacketSize);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_max_packet_size_0", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	PRINT_RESULT_CLEANUP(TEST_B_MAX_PACKET_SIZE_0, deviceMaxPacketSize, "usb_host_device_get_max_packet_size_0", UsbHostGetError(nRet), usb_host_device_close(hHostDevice));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));
	return 0;
}

//& purpose: Get usb host device vendor ID
//& type: auto
/**
* @testcase 			ITc_usb_host_device_get_id_vendor_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host device vendor ID
* @scenario			Get usb host device vendor ID
* @apicovered			usb_host_device_get_id_vendor
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_get_id_vendor_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	int vendorID = -1;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_id_vendor(hHostDevice, &vendorID);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_id_vendor", UsbHostGetError(nRet), usb_host_device_close(hHostDevice));
	PRINT_RESULT_CLEANUP(TEST_ID_VENDOR, vendorID, "usb_host_device_get_id_vendor", UsbHostGetError(nRet), usb_host_device_close(hHostDevice));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));
	return 0;
}

//& purpose: Get usb host device product ID
//& type: auto
/**
* @testcase 			ITc_usb_host_device_get_id_product_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host device product ID
* @scenario			Get usb host device product ID
* @apicovered			usb_host_device_get_id_product
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_get_id_product_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	int productID = -1;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_id_product(hHostDevice, &productID);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_id_product", UsbHostGetError(nRet), usb_host_device_close(hHostDevice));
	PRINT_RESULT_CLEANUP(TEST_ID_PRODUCT, productID, "usb_host_device_get_id_product", UsbHostGetError(nRet), usb_host_device_close(hHostDevice));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb host device bcd device
//& type: auto
/**
* @testcase 			ITc_usb_host_device_get_bcd_device_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host device bcd device
* @scenario			Get usb host device bcd device
* @apicovered			usb_host_device_get_bcd_device
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_get_bcd_device_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	int bcdDevice = -1;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_bcd_device(hHostDevice, &bcdDevice);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_bcd_device", UsbHostGetError(nRet), usb_host_device_close(hHostDevice));
	PRINT_RESULT_CLEANUP(TEST_BCD_DEVICE, bcdDevice, "usb_host_device_get_bcd_device", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb host device num configurations
//& type: auto
/**
* @testcase 			ITc_usb_host_device_get_num_configurations_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host device num configurations
* @scenario			Get usb host device num configurations
* @apicovered			usb_host_device_get_num_configurations
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_get_num_configurations_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	int numConfiguration = -1;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_num_configurations(hHostDevice, &numConfiguration);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_num_configurations", UsbHostGetError(nRet), usb_host_device_close(hHostDevice));
	PRINT_RESULT_CLEANUP(TEST_NUM_CONFIGURATIONS, numConfiguration, "usb_host_device_get_num_configurations", UsbHostGetError(nRet), usb_host_device_close(hHostDevice));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}
//& purpose: Check weather usb host device is opened
//& type: auto
/**
* @testcase 			ITc_usb_host_device_usb_host_is_device_opened_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Check weather usb host device is opened
* @scenario			Check weather usb host device is opened
* @apicovered			usb_host_device_is_opened
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_usb_host_is_device_opened_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	bool bIsOpened = false;


	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_is_device_opened(hHostDevice, &bIsOpened);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_is_device_opened", UsbHostGetError(nRet), usb_host_device_close(hHostDevice));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb host device manufacturer str
//& type: auto
/**
* @testcase 			ITc_usb_host_device_get_manufacturer_str_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host device manufacturer str
* @scenario			Get usb host device manufacturer str
* @apicovered			usb_host_device_get_manufacturer_str
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_get_manufacturer_str_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	unsigned char pszBuffer[256];
	int manufacturerStrLen = 256;
	usb_host_context_h CtxHandle = NULL;


	nRet = usb_host_create(&CtxHandle);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create", UsbHostGetError(nRet));

	nRet = usb_host_device_open_with_vid_pid(CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet), usb_host_destroy(CtxHandle));
	CHECK_HANDLE_CLEANUP(hHostDevice,"usb_host_device_open_with_vid_pid", usb_host_destroy(CtxHandle););

	nRet = usb_host_device_get_manufacturer_str(hHostDevice, &manufacturerStrLen, pszBuffer);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_manufacturer_str", UsbHostGetError(nRet), usb_host_device_close(hHostDevice);usb_host_destroy(CtxHandle););
	if(strcmp((const char *)pszBuffer, TEST_MANUFACTURER) != 0 || manufacturerStrLen != strlen(TEST_MANUFACTURER))
	{
		FPRINTF("[Line : %d][%s] get manufacturer str is invalid  as output string is %s ,and len %d and original is %d \\n", __LINE__, API_NAMESPACE, pszBuffer, strlen(TEST_MANUFACTURER), manufacturerStrLen);
		usb_host_device_close(hHostDevice);
		usb_host_destroy(CtxHandle);
		return 1;
	}

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	nRet = usb_host_destroy(CtxHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_destroy", UsbHostGetError(nRet));


	return 0;
}

//& purpose: Get usb host device product str
//& type: auto
/**
* @testcase 			ITc_usb_host_device_get_product_str_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host device product str
* @scenario			Get usb host device product str
* @apicovered			usb_host_device_get_product_str
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_get_product_str_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	unsigned char pszBuffer[256];
	int productStrLen = 256;


	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_product_str(hHostDevice, &productStrLen, pszBuffer);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_product_str", UsbHostGetError(nRet), usb_host_device_close(hHostDevice));
	if(strcmp((const char *)pszBuffer, TEST_PRODUCT) != 0 || productStrLen != strlen(TEST_PRODUCT))
	{
		FPRINTF("[Line : %d][%s] get product str is invalid \\n", __LINE__, API_NAMESPACE);
		usb_host_device_close(hHostDevice);
		return 1;
	}

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb host device serial number str
//& type: auto
/**
* @testcase 			ITc_usb_host_device_get_serial_number_str_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host device serial number str
* @scenario			Get usb host device serial number str
* @apicovered			usb_host_device_get_serial_number_str
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_get_serial_number_str_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	unsigned char pszBuffer[256];
	int serialNumberStrLen = 256;


	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_serial_number_str(hHostDevice, &serialNumberStrLen, pszBuffer);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_serial_number_str", UsbHostGetError(nRet), usb_host_device_close(hHostDevice));
	if(strcmp((const char *)pszBuffer, TEST_SERIAL_NUMBER) != 0 || serialNumberStrLen != strlen(TEST_SERIAL_NUMBER))
	{
		FPRINTF("[Line : %d][%s] get serial number str is invalid \\n", __LINE__, API_NAMESPACE);
		usb_host_device_close(hHostDevice);
		return 1;
	}

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Set usb host device config
//& type: auto
/**
* @testcase 			ITc_usb_host_device_set_config_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Set usb host device config
* @scenario			Set usb host device config
* @apicovered			usb_host_device_set_config
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_set_config_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle;
	int numInterface = -1;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice));

	nRet = usb_host_set_config(hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, " usb_host_set_config", UsbHostGetError(nRet),usb_host_config_destroy(hConfigHandle);usb_host_device_close(hHostDevice));

	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get host device config str
//& type: auto
/**
* @testcase 			ITc_usb_host_device_get_config_str_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get host device config str
* @scenario			Get host device config str
* @apicovered			usb_host_device_get_config_str
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_get_config_str_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle;
	int configStrLen = 256;
	unsigned char pszBuffer[256];
	usb_host_context_h CtxHandle = NULL;

	nRet = usb_host_create(&CtxHandle);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create", UsbHostGetError(nRet));

	nRet = usb_host_device_open_with_vid_pid(CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet), usb_host_destroy(CtxHandle));
	CHECK_HANDLE_CLEANUP(hHostDevice,"usb_host_device_open_with_vid_pid",usb_host_destroy(CtxHandle));

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_destroy(CtxHandle));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice);usb_host_destroy(CtxHandle));

	nRet = usb_host_device_get_config_str(hConfigHandle, &configStrLen, pszBuffer);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config_str", UsbHostGetError(nRet),usb_host_config_destroy(hConfigHandle);usb_host_device_close(hHostDevice);usb_host_destroy(CtxHandle));
	if(strcmp((const char *)pszBuffer, TEST_CFG_STR) != 0 || configStrLen != strlen(TEST_CFG_STR))
	{
		FPRINTF("[Line : %d][%s] get config str is invalid  %s and len %d \\n", __LINE__, API_NAMESPACE, pszBuffer, configStrLen);
		usb_host_config_destroy(hConfigHandle);
		usb_host_device_close(hHostDevice);
		usb_host_destroy(CtxHandle);
		return 1;
	}

	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	nRet = usb_host_destroy(CtxHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_destroy", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb host device interfaces number
//& type: auto
/**
* @testcase 			ITc_usb_host_device_config_get_num_interfaces_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host device interfaces number
* @scenario			Get usb host device interfaces number
* @apicovered			usb_host_device_config_get_num_interfaces
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_config_get_num_interfaces_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle;
	int numInterface = -1;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice));

	nRet = usb_host_config_get_num_interfaces(hConfigHandle, &numInterface);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_num_interfaces", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	PRINT_RESULT_CLEANUP(TEST_NUM_INTERFACES, numInterface, "usb_host_config_get_num_interfaces", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));

	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: To check weather device config is self powered
//& type: auto
/**
* @testcase 			ITc_usb_host_device_config_is_self_powered_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			To check weather device config is self powered
* @scenario			To check weather device config is self powered
* @apicovered			usb_host_config_is_self_powered
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_config_is_self_powered_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle;
	bool isSelfPowered = false;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice));

	nRet = usb_host_config_is_self_powered(hConfigHandle, &isSelfPowered);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_config_is_self_powered", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	PRINT_RESULT_CLEANUP(TEST_CFG_SELF_POWERED, isSelfPowered, "usb_host_config_is_self_powered", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));


	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: To check weather device config is remote wakeup
//& type: auto
/**
* @testcase 			ITc_usb_host_device_config_support_remote_wakeup_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			To check weather device config is remote wakeup
* @scenario			To check weather device config is remote wakeup
* @apicovered			usb_host_config_support_remote_wakeup
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_config_support_remote_wakeup_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle;
	bool isRemoteBackup = false;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice));

	nRet = usb_host_config_support_remote_wakeup(hConfigHandle, &isRemoteBackup);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_config_support_remote_wakeup", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	PRINT_RESULT_CLEANUP(TEST_CFG_SUPPORT_REMOTE_WAKEUP, isRemoteBackup, "usb_host_config_support_remote_wakeup", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));


	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb host device config Max Power
//& type: auto
/**
* @testcase 			ITc_usb_host_device_config_get_config_max_power_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host device config Max Power
* @scenario			Get usb host device config Max Power
* @apicovered			usb_host_config_get_max_power
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_config_get_config_max_power_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle = NULL;
	int configMaxPower = 0;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice));

	nRet = usb_host_config_get_max_power(hConfigHandle, &configMaxPower);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_max_power", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	PRINT_RESULT_CLEANUP(TEST_CFG_MAX_POWER, configMaxPower, "usb_host_config_get_config_max_power", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));

	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb host device config interface
//& type: auto
/**
* @testcase 			ITc_usb_host_device_config_get_interface_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host device config interface
* @scenario			Get usb host device config interface
* @apicovered			usb_host_config_get_interface
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_device_config_get_interface_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle;
	usb_host_interface_h hInterfaceHandle = NULL;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice));

	nRet = usb_host_config_get_interface(hConfigHandle, 0, &hInterfaceHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	CHECK_HANDLE_CLEANUP(hInterfaceHandle,"usb_host_config_get_interface", usb_host_device_close(hHostDevice));

	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Clain and release usb host interface
//& type: auto
/**
* @testcase 			ITc_usb_host_claim_release_interface_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Clain and release usb host interface
* @scenario			Clain and release usb host interface
* @apicovered			usb_host_claim_interface, usb_host_release_interface
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_claim_release_interface_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle = NULL;
	usb_host_interface_h hInterfaceHandle = NULL;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice));

	nRet = usb_host_config_get_interface(hConfigHandle, 0, &hInterfaceHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	CHECK_HANDLE_CLEANUP(hInterfaceHandle,"usb_host_config_get_interface", usb_host_device_close(hHostDevice));

	nRet = usb_host_claim_interface(hInterfaceHandle, 1);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_claim_interface", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));

	nRet = usb_host_release_interface(hInterfaceHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_release_interface", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));

	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb host interface number
//& type: auto
/**
* @testcase 			ITc_usb_host_interface_get_number_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host interface number
* @scenario			Get usb host interface number
* @apicovered			usb_host_interface_get_number
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_interface_get_number_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle = NULL;
	usb_host_interface_h hInterfaceHandle = NULL;
	int interfaceNumber = 0;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice));

	nRet = usb_host_config_get_interface(hConfigHandle, 0, &hInterfaceHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	CHECK_HANDLE_CLEANUP(hInterfaceHandle,"usb_host_config_get_interface", usb_host_device_close(hHostDevice));

	nRet = usb_host_interface_get_number(hInterfaceHandle, &interfaceNumber);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_number", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	PRINT_RESULT_CLEANUP(0, interfaceNumber, "usb_host_interface_get_number", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));


	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb host interface endpoint
//& type: auto
/**
* @testcase 			ITc_usb_host_interface_get_endpoint_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host interface endpoint
* @scenario			Get usb host interface endpoint
* @apicovered			usb_host_interface_get_endpoint
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_interface_get_endpoint_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle = NULL;
	usb_host_interface_h hInterfaceHandle = NULL;
	int interfaceNumber = 0;
	usb_host_endpoint_h usbHostInterfaceEndPoint = NULL;
	usb_host_context_h CtxHandle = NULL;

	nRet = usb_host_create(&CtxHandle);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create", UsbHostGetError(nRet));

	nRet = usb_host_device_open_with_vid_pid(CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet), usb_host_destroy(CtxHandle));
	CHECK_HANDLE_CLEANUP(hHostDevice,"usb_host_device_open_with_vid_pid", usb_host_destroy(CtxHandle));

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_destroy(CtxHandle));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice);usb_host_destroy(CtxHandle));

	nRet = usb_host_config_get_interface(hConfigHandle, 0, &hInterfaceHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle);usb_host_destroy(CtxHandle));
	CHECK_HANDLE_CLEANUP(hInterfaceHandle,"usb_host_config_get_interface", usb_host_device_close(hHostDevice);usb_host_destroy(CtxHandle));

	nRet = usb_host_interface_get_endpoint(hInterfaceHandle, 1, &usbHostInterfaceEndPoint);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_endpoint", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle);usb_host_destroy(CtxHandle));
	CHECK_HANDLE_CLEANUP(usbHostInterfaceEndPoint,"usb_host_interface_get_endpoint", usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle);usb_host_destroy(CtxHandle));

	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	nRet = usb_host_destroy(CtxHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_destroy", UsbHostGetError(nRet));

	return 0;
}


//& purpose: Get usb host interface str
//& type: auto
/**
* @testcase 			ITc_usb_host_interface_get_str_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host interface str
* @scenario			Get usb host interface str
* @apicovered			usb_host_interface_get_str
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_interface_get_str_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle = NULL;
	usb_host_interface_h hInterfaceHandle = NULL;
	unsigned char pszBuffer[256];
	int interfaceStrLen = 256;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice));

	nRet = usb_host_config_get_interface(hConfigHandle, 0, &hInterfaceHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	CHECK_HANDLE_CLEANUP(hInterfaceHandle,"usb_host_config_get_interface", usb_host_device_close(hHostDevice));

	nRet = usb_host_interface_get_str(hInterfaceHandle, &interfaceStrLen, pszBuffer);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_str", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	PRINT_RESULT_CLEANUP(strlen(TEST_IFACE_STR), interfaceStrLen, "usb_host_interface_get_str", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));

	if(strcmp(TEST_IFACE_STR, pszBuffer) != 0)
	{
		FPRINTF("[Line : %d][%s] interface str valus is invalid \\n", __LINE__, API_NAMESPACE);
		usb_host_config_destroy(hConfigHandle);
		usb_host_device_close(hHostDevice);
		return 1;
	}


	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb host interface num of endpoints
//& type: auto
/**
* @testcase 			ITc_usb_host_interface_get_num_endpoints_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host interface num of endpoints
* @scenario			Get usb host interface num of endpoints
* @apicovered			usb_host_interface_get_num_endpoints
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_interface_get_num_endpoints_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle = NULL;
	usb_host_interface_h hInterfaceHandle = NULL;
	int numOdEndPoints = 0;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice));

	nRet = usb_host_config_get_interface(hConfigHandle, 0, &hInterfaceHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	CHECK_HANDLE_CLEANUP(hInterfaceHandle,"usb_host_config_get_interface", usb_host_device_close(hHostDevice));

	nRet = usb_host_interface_get_num_endpoints(hInterfaceHandle, &numOdEndPoints);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_num_endpoints", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	PRINT_RESULT_CLEANUP(TEST_NUM_ENDPOINTS, numOdEndPoints, "usb_host_interface_get_num_endpoints", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));

	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Set usb host interface altsetting
//& type: auto
/**
* @testcase 			ITc_usb_host_interface_get_endpoint_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host interface altsetting
* @scenario			Get usb host interface altsetting
* @apicovered			usb_host_interface_set_altsetting
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_interface_set_altsetting_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle = NULL;
	usb_host_interface_h hInterfaceHandle = NULL;
	int interfaceNumber = 0;
	usb_host_endpoint_h usbHostInterfaceEndPoint = NULL;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice));

	nRet = usb_host_config_get_interface(hConfigHandle, 0, &hInterfaceHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	CHECK_HANDLE_CLEANUP(hInterfaceHandle,"usb_host_config_get_interface", usb_host_device_close(hHostDevice));

	nRet = usb_host_interface_set_altsetting(hInterfaceHandle, 0);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_set_altsetting", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));

	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb host endpoint number
//& type: auto
/**
* @testcase 			ITc_usb_host_endpoint_get_number_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host endpoint number
* @scenario			Get usb host endpoint number
* @apicovered			usb_host_endpoint_get_number
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_endpoint_get_number_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle = NULL;
	usb_host_interface_h hInterfaceHandle = NULL;
	int numOdEndPoints = 1;;
	usb_host_endpoint_h usbHostInterfaceEndPoint = NULL;
	usb_host_context_h CtxHandle = NULL;

	nRet = usb_host_create(&CtxHandle);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create", UsbHostGetError(nRet));

	nRet = usb_host_device_open_with_vid_pid(CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet), usb_host_destroy(CtxHandle));
	CHECK_HANDLE_CLEANUP(hHostDevice,"usb_host_device_open_with_vid_pid", usb_host_destroy(CtxHandle));

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_destroy(CtxHandle));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice);usb_host_destroy(CtxHandle));

	nRet = usb_host_config_get_interface(hConfigHandle, 0, &hInterfaceHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle);usb_host_destroy(CtxHandle));
	CHECK_HANDLE_CLEANUP(hInterfaceHandle,"usb_host_config_get_interface", usb_host_device_close(hHostDevice);usb_host_destroy(CtxHandle));

	nRet = usb_host_interface_get_endpoint(hInterfaceHandle, 1, &usbHostInterfaceEndPoint);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_endpoint", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle);usb_host_destroy(CtxHandle));
	CHECK_HANDLE_CLEANUP(usbHostInterfaceEndPoint,"usb_host_interface_get_endpoint", usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle);usb_host_destroy(CtxHandle));

	nRet = usb_host_endpoint_get_number(usbHostInterfaceEndPoint, &numOdEndPoints);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_endpoint_get_number", UsbHostGetError(nRet),usb_host_config_destroy(hConfigHandle);usb_host_device_close(hHostDevice);usb_host_destroy(CtxHandle));
	if(numOdEndPoints < 0)
	{
		FPRINTF("[Line : %d][%s] endpoint number is invalid  \\n", __LINE__, API_NAMESPACE);
		usb_host_config_destroy(hConfigHandle);
		usb_host_device_close(hHostDevice);
		usb_host_destroy(CtxHandle);
		return 1;
	}

	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	nRet = usb_host_destroy(CtxHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_destroy", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb host endpoint direction
//& type: auto
/**
* @testcase 			ITc_usb_host_endpoint_get_direction_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host endpoint direction
* @scenario			Get usb host endpoint direction
* @apicovered			usb_host_endpoint_get_direction
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_endpoint_get_direction_p(void)
{
	START_TEST_FEATURE;
	int nRet = -1;;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle = NULL;
	usb_host_interface_h hInterfaceHandle = NULL;
	usb_host_endpoint_h usbHostInterfaceEndPoint = NULL;
	usb_host_endpoint_direction_e eEndPointDir;
	usb_host_context_h CtxHandle = NULL;

	nRet = usb_host_create(&CtxHandle);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create", UsbHostGetError(nRet));

	nRet = usb_host_device_open_with_vid_pid(CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet),usb_host_destroy(CtxHandle));
	CHECK_HANDLE_CLEANUP(hHostDevice,"usb_host_device_open_with_vid_pid",usb_host_destroy(CtxHandle));

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_destroy(CtxHandle));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice);usb_host_destroy(CtxHandle));

	nRet = usb_host_config_get_interface(hConfigHandle, 0, &hInterfaceHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle);usb_host_destroy(CtxHandle));
	CHECK_HANDLE_CLEANUP(hInterfaceHandle,"usb_host_config_get_interface", usb_host_device_close(hHostDevice);usb_host_destroy(CtxHandle));

	nRet = usb_host_interface_get_endpoint(hInterfaceHandle, 1, &usbHostInterfaceEndPoint);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_endpoint", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle);usb_host_destroy(CtxHandle));
	CHECK_HANDLE_CLEANUP(usbHostInterfaceEndPoint,"usb_host_interface_get_endpoint", usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle);usb_host_destroy(CtxHandle));

	nRet = usb_host_endpoint_get_direction(usbHostInterfaceEndPoint, &eEndPointDir);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_endpoint_get_direction", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle);usb_host_destroy(CtxHandle));
	if(eEndPointDir < 0)
	{
		FPRINTF("[Line : %d][%s] endpoint direction is invalid  \\n", __LINE__, API_NAMESPACE);
		usb_host_config_destroy(hConfigHandle);
		usb_host_device_close(hHostDevice);
		usb_host_destroy(CtxHandle);
		return 1;

	}

	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	nRet = usb_host_destroy(CtxHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_destroy", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb host endpoint transfer type
//& type: auto
/**
* @testcase 			ITc_usb_host_endpoint_get_transfer_type_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host endpoint transfer type
* @scenario			Get usb host endpoint transfer type
* @apicovered			usb_host_endpoint_get_transfer_type
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_endpoint_get_transfer_type_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle = NULL;
	usb_host_interface_h hInterfaceHandle = NULL;
	int numOdEndPoints = 0;
	usb_host_endpoint_h usbHostInterfaceEndPoint = NULL;
	usb_host_transfer_type_e eTransferType = -1;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice));

	nRet = usb_host_config_get_interface(hConfigHandle, 0, &hInterfaceHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	CHECK_HANDLE_CLEANUP(hInterfaceHandle,"usb_host_config_get_interface", usb_host_device_close(hHostDevice));

	nRet = usb_host_interface_get_endpoint(hInterfaceHandle, 1, &usbHostInterfaceEndPoint);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_endpoint", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	CHECK_HANDLE_CLEANUP(usbHostInterfaceEndPoint,"usb_host_interface_get_endpoint", usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));

	nRet = usb_host_endpoint_get_transfer_type(usbHostInterfaceEndPoint, &eTransferType);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_endpoint_get_transfer_type", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	PRINT_RESULT_CLEANUP(TEST_EP_TRANSFER_TYPE, eTransferType, "usb_host_endpoint_get_transfer_type", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));

	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb host endpoint usage type
//& type: auto
/**
* @testcase 			ITc_usb_host_endpoint_get_usage_type_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host endpoint usage type
* @scenario			Get usb host endpoint usage type
* @apicovered			usb_host_endpoint_get_usage_type
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_endpoint_get_usage_type_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle = NULL;
	usb_host_interface_h hInterfaceHandle = NULL;
	int numOdEndPoints = 0;
	usb_host_endpoint_h usbHostInterfaceEndPoint = NULL;
	usb_host_usage_type_e eUsageType = -1;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice));

	nRet = usb_host_config_get_interface(hConfigHandle, 0, &hInterfaceHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	CHECK_HANDLE_CLEANUP(hInterfaceHandle,"usb_host_config_get_interface", usb_host_device_close(hHostDevice));

	nRet = usb_host_interface_get_endpoint(hInterfaceHandle, 1, &usbHostInterfaceEndPoint);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_endpoint", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	CHECK_HANDLE_CLEANUP(usbHostInterfaceEndPoint,"usb_host_interface_get_endpoint", usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));

	nRet = usb_host_endpoint_get_usage_type(usbHostInterfaceEndPoint, &eUsageType);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_endpoint_get_usage_type", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	PRINT_RESULT_CLEANUP(TEST_EP_USAGE_TYPE, eUsageType, "usb_host_endpoint_get_usage_type", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));

	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb host endpoint synch type
//& type: auto
/**
* @testcase 			ITc_usb_host_endpoint_get_synch_type_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host endpoint synch type
* @scenario			Get usb host endpoint synch type
* @apicovered			usb_host_endpoint_get_synch_type
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_endpoint_get_synch_type_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle = NULL;
	usb_host_interface_h hInterfaceHandle = NULL;
	int numOdEndPoints = 0;
	usb_host_endpoint_h usbHostInterfaceEndPoint = NULL;
	usb_host_iso_sync_type_e eSynchType = -1;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice));

	nRet = usb_host_config_get_interface(hConfigHandle, 0, &hInterfaceHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	CHECK_HANDLE_CLEANUP(hInterfaceHandle,"usb_host_config_get_interface", usb_host_device_close(hHostDevice));

	nRet = usb_host_interface_get_endpoint(hInterfaceHandle, 1, &usbHostInterfaceEndPoint);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_endpoint", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	CHECK_HANDLE_CLEANUP(usbHostInterfaceEndPoint,"usb_host_interface_get_endpoint", usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));

	nRet = usb_host_endpoint_get_synch_type(usbHostInterfaceEndPoint, &eSynchType);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_endpoint_get_synch_type", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	PRINT_RESULT_CLEANUP(TEST_EP_SYNCH_TYPE, eSynchType, "usb_host_endpoint_get_synch_type", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));

	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb host endpoint max packet size
//& type: auto
/**
* @testcase 			ITc_usb_host_endpoint_get_max_packet_size_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host endpoint max packet size
* @scenario			Get usb host endpoint max packet size
* @apicovered			usb_host_endpoint_get_max_packet_size
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_endpoint_get_max_packet_size_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle;
	usb_host_interface_h hInterfaceHandle = NULL;
	int maxPacketSize = 0;
	usb_host_endpoint_h usbHostInterfaceEndPoint = NULL;
	usb_host_endpoint_direction_e eEndPointDir = -1;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice));

	nRet = usb_host_config_get_interface(hConfigHandle, 0, &hInterfaceHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	CHECK_HANDLE_CLEANUP(hInterfaceHandle,"usb_host_config_get_interface", usb_host_device_close(hHostDevice));

	nRet = usb_host_interface_get_endpoint(hInterfaceHandle, 1, &usbHostInterfaceEndPoint);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_endpoint", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	CHECK_HANDLE_CLEANUP(usbHostInterfaceEndPoint,"usb_host_interface_get_endpoint", usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));

	nRet = usb_host_endpoint_get_max_packet_size(usbHostInterfaceEndPoint, &maxPacketSize);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "uusb_host_endpoint_get_max_packet_size", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	PRINT_RESULT_CLEANUP(TEST_EP_MAX_PACKET_SIZE, maxPacketSize, "uusb_host_endpoint_get_max_packet_size", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));

	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb host endpoint interval
//& type: auto
/**
* @testcase 			ITc_usb_host_endpoint_get_interval_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			Get usb host endpoint interval
* @scenario			Get usb host endpoint interval
* @apicovered			usb_host_endpoint_get_interval
* @passcase			If target API and Precondition API gets pass
* @failcase			If target API and Precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_usb_host_endpoint_get_interval_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hConfigHandle;
	usb_host_interface_h hInterfaceHandle = NULL;
	int numOdEndPoints = 0;
	usb_host_endpoint_h usbHostInterfaceEndPoint = NULL;
	int endpointInterval = 0;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hConfigHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet),usb_host_device_close(hHostDevice));
	CHECK_HANDLE_CLEANUP(hConfigHandle,"usb_host_device_get_config", usb_host_device_close(hHostDevice));

	nRet = usb_host_config_get_interface(hConfigHandle, 0, &hInterfaceHandle);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	CHECK_HANDLE_CLEANUP(hInterfaceHandle,"usb_host_config_get_interface", usb_host_device_close(hHostDevice));

	nRet = usb_host_interface_get_endpoint(hInterfaceHandle, 1, &usbHostInterfaceEndPoint);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_endpoint", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	CHECK_HANDLE_CLEANUP(usbHostInterfaceEndPoint,"usb_host_interface_get_endpoint", usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));

	nRet = usb_host_endpoint_get_interval(usbHostInterfaceEndPoint, &endpointInterval);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "uusb_host_endpoint_get_interval", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));
	PRINT_RESULT_CLEANUP(0, endpointInterval, "uusb_host_endpoint_get_interval", UsbHostGetError(nRet),usb_host_device_close(hHostDevice);usb_host_config_destroy(hConfigHandle));

	nRet = usb_host_config_destroy(hConfigHandle);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_config_destroy", UsbHostGetError(nRet));

	nRet = usb_host_device_close(hHostDevice);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_device_close", UsbHostGetError(nRet));

	return 0;
}

//& purpose: create usb-host transfer handle
//& type: auto
/**
* @testcase 			ITc_usb_host_create_destroy_transfer_p
* @since_tizen			5.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			create and destroy usb-host transfer handle
* @scenario				create and destroy usb-host transfer handle
* @apicovered			usb_host_create_transfer,usb_host_transfer_destroy
* @passcase				If target API  and precondition API gets pass
* @failcase				If target API fails or any precondition API fails
* @precondition			ep must be a valid endpoint received from usb_host_interface_get_endpoint()
* @postcondition		ransfer should be destroyed by calling usb_host_transfer_destroy() when it's no longer needed
*/
int ITc_usb_host_create_destroy_transfer_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	unsigned char pszbuf[sizeof(TEST_DATA)];
	usb_host_transfer_h hHosttransfer;
	usb_host_interface_h hHostInterface = NULL;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hHostConfig = NULL;
	usb_host_endpoint_h hHostEndPoint = NULL;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hHostConfig);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostConfig,"usb_host_device_get_config");

	nRet = usb_host_config_get_interface(hHostConfig, 0, &hHostInterface);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostInterface,"usb_host_config_get_interface");

	nRet = usb_host_interface_get_endpoint(hHostInterface, 1, &hHostEndPoint);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_endpoint", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostEndPoint,"usb_host_interface_get_endpoint");

	nRet = usb_host_create_transfer(hHostEndPoint, UsbHostTransferCB, pszbuf, sizeof(TEST_DATA), NULL, 0, &hHosttransfer);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create_transfer", UsbHostGetError(nRet));
	CHECK_HANDLE(hHosttransfer,"usb_host_create_transfer");

	nRet = usb_host_transfer_destroy(hHosttransfer);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_destroy", UsbHostGetError(nRet));

	return 0;
}

//& purpose: create usb-host control transfer handle
//& type: auto
/**
* @testcase 			ITc_usb_host_create_control_transfer_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 				auto
* @description			create and destroy usb-host control transfer handle
* @scenario				create and destroy usb-host control transfer handle
* @apicovered			usb_host_create_control_transfer,usb_host_transfer_destroy
* @passcase				If target API  and precondition API gets pass
* @failcase				If target API fails or any precondition API fails
* @precondition			dev must be an opened device handle
* @postcondition		transfer should be destroyed by calling usb_host_transfer_destroy() when it's no longer needed
*/
int ITc_usb_host_create_control_transfer_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	unsigned char pszdata[DATA_SIZE];
	usb_host_transfer_h hHosttransfer = NULL;
	usb_host_device_h hHostDevice = NULL;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_create_control_transfer(hHostDevice, UsbHostTransferCB, pszdata, DATA_SIZE, NULL, 0, &hHosttransfer);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create_control_transfer", UsbHostGetError(nRet));
	CHECK_HANDLE(hHosttransfer,"usb_host_create_control_transfer")

	nRet = usb_host_transfer_destroy(hHosttransfer);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_destroy", UsbHostGetError(nRet));

	return 0;
}

//& purpose: submit and cancel usb-host control transfer
//& type: auto
/**
* @testcase 			ITc_usb_host_transfer_submit_cancel_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			submit and cancel usb-host control transfer
* @scenario			submit and cancel usb-host control transfer
* @apicovered			usb_host_transfer_submit,usb_host_transfer_cancel
* @passcase			If target API and precondition API gets pass
* @failcase			If target API fails or any precondition API fails
* @precondition			a transfer should be initialized by one of initialization functions:
* usb_host_create_transfer(), usb_host_create_isochronous_transfer() or usb_host_create_control_transfer().
* @postcondition		transfer should be destroyed by calling usb_host_transfer_destroy() when it's no longer needed
*/
int ITc_usb_host_transfer_submit_cancel_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	unsigned char pszdata[DATA_SIZE];
	usb_host_transfer_h hHosttransfer;
	usb_host_device_h hHostDevice = NULL;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_create_control_transfer(hHostDevice, UsbHostTransferCB, pszdata, DATA_SIZE, NULL, 0, &hHosttransfer);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create_control_transfer", UsbHostGetError(nRet));
	CHECK_HANDLE(hHosttransfer,"usb_host_create_control_transfer")

	nRet = usb_host_transfer_submit(hHosttransfer);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_submit", UsbHostGetError(nRet),usb_host_transfer_destroy(hHosttransfer));

	nRet = usb_host_transfer_cancel(hHosttransfer);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_cancel", UsbHostGetError(nRet),usb_host_transfer_destroy(hHosttransfer));

	nRet = usb_host_transfer_destroy(hHosttransfer);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_destroy", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Set usb-host transfer ep
//& type: auto
/**
* @testcase 			ITc_usb_host_transfer_set_ep_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 				auto
* @description			Set usb-host transfer epe
* @scenario				Set usb-host transfer ep
* @apicovered			usb_host_transfer_set_ep,usb_host_interface_get_endpoint,usb_host_config_get_interface,usb_host_device_open_with_vid_pid
* @passcase				If target API   and precondition API gets pass
* @failcase				If target API fails or any precondition API fails
* @precondition			dev must be an opened device handle
* @postcondition		transfer should be destroyed by calling usb_host_transfer_destroy() when it's no longer needed
*/
int ITc_usb_host_transfer_set_ep_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	unsigned char pszbuf[sizeof(TEST_DATA)];
	usb_host_transfer_h hHosttransfer = NULL;
	usb_host_interface_h hHostInterface = NULL;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hHostConfig = NULL;
	usb_host_endpoint_h hHostEndPoint = NULL;
	usb_host_endpoint_h hHostEndPoint2 = NULL;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hHostConfig);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostConfig,"usb_host_device_get_config");

	nRet = usb_host_config_get_interface(hHostConfig, 0, &hHostInterface);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostInterface,"usb_host_config_get_interface");


	nRet = usb_host_interface_get_endpoint(hHostInterface, 1, &hHostEndPoint);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_endpoint", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostEndPoint,"usb_host_interface_get_endpoint")

	nRet = usb_host_interface_get_endpoint(hHostInterface, 2, &hHostEndPoint2);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_endpoint", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostEndPoint,"usb_host_interface_get_endpoint");

	nRet = usb_host_create_transfer(hHostEndPoint, UsbHostTransferCB, pszbuf, sizeof(TEST_DATA), NULL, 0, &hHosttransfer);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create_transfer", UsbHostGetError(nRet));
	CHECK_HANDLE(hHosttransfer,"usb_host_create_transfer");

	//Target API
	nRet = usb_host_transfer_set_ep(hHosttransfer, hHostEndPoint2);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_set_ep", UsbHostGetError(nRet),  usb_host_transfer_destroy(hHosttransfer));

	nRet = usb_host_transfer_destroy(hHosttransfer);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_destroy", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get and Set usb-host data
//& type: auto
/**
* @testcase 			ITc_usb_host_transfer_set_get_data_p
* @since_tizen			5.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Get and Set usb-host data
* @scenario				Get and Set usb-host data
* @apicovered			usb_host_transfer_set_ep,usb_host_interface_get_endpoint,usb_host_config_get_interface,usb_host_device_open_with_vid_pid
* @passcase				If target API and precondition API gets pass
* @failcase				If target API fails or any precondition API fails
* @precondition			dev must be an opened device handle
* @postcondition		transfer should be destroyed by calling usb_host_transfer_destroy() when it's no longer needed
*/
int ITc_usb_host_transfer_set_get_data_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	unsigned char pszbuf[sizeof(TEST_DATA)];
	usb_host_transfer_h hHosttransfer;
	usb_host_interface_h hHostInterface = NULL;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hHostConfig = NULL;
	usb_host_endpoint_h hHostEndPoint = NULL;
	unsigned int len;
	unsigned char *pszgHostData;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hHostConfig);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostConfig,"usb_host_device_get_config");

	nRet = usb_host_config_get_interface(hHostConfig, 0, &hHostInterface);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostInterface,"usb_host_config_get_interface");


	nRet = usb_host_interface_get_endpoint(hHostInterface, 1, &hHostEndPoint);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_endpoint", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostEndPoint,"usb_host_interface_get_endpoint")


	nRet = usb_host_create_transfer(hHostEndPoint, UsbHostTransferCB, pszbuf, sizeof(TEST_DATA), NULL, 0, &hHosttransfer);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create_transfer", UsbHostGetError(nRet));
	CHECK_HANDLE(hHosttransfer,"usb_host_create_transfer");

	nRet = usb_host_transfer_set_data(hHosttransfer, pszbuf, sizeof(TEST_DATA));
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_set_data", UsbHostGetError(nRet), usb_host_transfer_destroy(hHosttransfer));

	nRet = usb_host_transfer_get_data(hHosttransfer, &pszgHostData, &len);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_get_data", UsbHostGetError(nRet), usb_host_transfer_destroy(hHosttransfer));

	if(strcmp(pszgHostData,pszbuf) != 0)
	{
		usb_host_transfer_destroy(hHosttransfer);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] usb_host_transfer_get_data data mismatch with get %s and set %s data, error returned = %s (%d)", __FILE__, __LINE__, pszgHostData, pszbuf, UsbHostGetError(nRet), nRet);
		return 1;
	}

	nRet = usb_host_transfer_destroy(hHosttransfer);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_destroy", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb-host transfer length
//& type: auto
/**
* @testcase 			ITc_usb_host_transfer_get_length_p
* @since_tizen			5.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Get usb-host transfer length
* @scenario				Get usb-host transfer length
* @apicovered			usb_host_create_control_transfer,usb_host_transfer_get_length,usb_host_transfer_destroy
* @passcase				If target API and precondition API gets pass
* @failcase				If target API fails or any precondition API fails
* @precondition			dev must be an opened device handle
* @postcondition		transfer should be destroyed by calling usb_host_transfer_destroy() when it's no longer needed
*/
int ITc_usb_host_transfer_get_length_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	unsigned char pszdata[DATA_SIZE];
	usb_host_transfer_h hHosttransfer;
	usb_host_device_h hHostDevice = NULL;
	unsigned int len = -1;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_create_control_transfer(hHostDevice, UsbHostTransferCB, pszdata, DATA_SIZE, NULL, 0, &hHosttransfer);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create_control_transfer", UsbHostGetError(nRet));
	CHECK_HANDLE(hHosttransfer,"usb_host_create_control_transfer")

	nRet = usb_host_transfer_get_length(hHosttransfer, &len);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_get_length", UsbHostGetError(nRet), usb_host_transfer_destroy(hHosttransfer));

	if(len < 0)
	{
		usb_host_transfer_destroy(hHosttransfer);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] usb_host_transfer_get_length is invalid %d", __FILE__, __LINE__, len);
		return 1;
	}

	nRet = usb_host_transfer_destroy(hHosttransfer);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_destroy", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Set usb-host transfer value
//& type: auto
/**
* @testcase 			ITc_host_control_transfer_set_value_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 				auto
* @description			Set usb-host transfer value
* @scenario				Set usb-host transfer value
* @apicovered			usb_host_create_control_transfer,usb_host_control_transfer_set_value,usb_host_transfer_destroy
* @passcase				If target API and precondition API  gets pass
* @failcase				If target API fails or any precondition API fails
* @precondition			dev must be an opened device handle
* @postcondition		transfer should be destroyed by calling usb_host_transfer_destroy() when it's no longer needed
*/
int ITc_host_control_transfer_set_value_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	unsigned char pszdata[DATA_SIZE];
	usb_host_transfer_h hHosttransfer;
	usb_host_device_h hHostDevice = NULL;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_create_control_transfer(hHostDevice, UsbHostTransferCB, pszdata, DATA_SIZE, NULL, 0, &hHosttransfer);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create_control_transfer", UsbHostGetError(nRet));
	CHECK_HANDLE(hHosttransfer,"usb_host_create_control_transfer")

	nRet = usb_host_control_transfer_set_value(hHosttransfer, 0x0100);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_control_transfer_set_value", UsbHostGetError(nRet), usb_host_transfer_destroy(hHosttransfer));

	nRet = usb_host_transfer_destroy(hHosttransfer);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_destroy", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Set usb-host transfer request
//& type: auto
/**
* @testcase 			ITc_usb_host_control_transfer_set_request_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 				auto
* @description			Set usb-host transfer request
* @scenario				Set usb-host transfer request
* @apicovered			usb_host_create_control_transferusb_host_control_transfer_set_request,usb_host_transfer_destroy
* @passcase				If target API and precondition API gets pass
* @failcase				If target API fails or any precondition API fails
* @precondition			dev must be an opened device handle
* @postcondition		transfer should be destroyed by calling usb_host_transfer_destroy() when it's no longer needed
*/
int ITc_usb_host_control_transfer_set_request_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	unsigned char pszdata[DATA_SIZE];
	usb_host_transfer_h hHosttransfer;
	usb_host_device_h hHostDevice = NULL;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_create_control_transfer(hHostDevice, UsbHostTransferCB, pszdata, DATA_SIZE, NULL, 0, &hHosttransfer);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create_control_transfer", UsbHostGetError(nRet));
	CHECK_HANDLE(hHosttransfer,"usb_host_create_control_transfer")

	nRet = usb_host_control_transfer_set_request(hHosttransfer, 0x06);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_control_transfer_set_request", UsbHostGetError(nRet), usb_host_transfer_destroy(hHosttransfer));

	nRet = usb_host_transfer_destroy(hHosttransfer);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_destroy", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Set usb-host transfer request type
//& type: auto
/**
* @testcase 			ITc_usb_host_control_transfer_set_request_type_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 				auto
* @description			Set usb-host transfer request type
* @scenario				Set usb-host transfer request type
* @apicovered			usb_host_create_control_transfer,usb_host_control_transfer_set_request_type,usb_host_transfer_destroy
* @passcase				If target API and precondition API  gets pass
* @failcase				If target API fails or any precondition API fails
* @precondition			dev must be an opened device handle
* @postcondition		transfer should be destroyed by calling usb_host_transfer_destroy() when it's no longer needed
*/
int ITc_usb_host_control_transfer_set_request_type_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	unsigned char pszdata[DATA_SIZE];
	usb_host_transfer_h hHosttransfer;
	usb_host_device_h hHostDevice = NULL;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_create_control_transfer(hHostDevice, UsbHostTransferCB, pszdata, DATA_SIZE, NULL, 0, &hHosttransfer);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create_control_transfer", UsbHostGetError(nRet));
	CHECK_HANDLE(hHosttransfer,"usb_host_create_control_transfer")

	nRet = usb_host_control_transfer_set_request_type(hHosttransfer, 0x06);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_control_transfer_set_request_type", UsbHostGetError(nRet), usb_host_transfer_destroy(hHosttransfer));

	nRet = usb_host_transfer_destroy(hHosttransfer);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_destroy", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Set usb-host transfer request index
//& type: auto
/**
* @testcase 			ITc_usb_host_control_transfer_set_index_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 				auto
* @description			Set usb-host transfer request type
* @scenario				Set usb-host transfer request type
* @apicovered			usb_host_create_control_transfer,usb_host_control_transfer_set_index,usb_host_transfer_destroy
* @passcase				If target API and precondition API gets pass
* @failcase				If target API fails or any precondition API fails
* @precondition			dev must be an opened device handle
* @postcondition		transfer should be destroyed by calling usb_host_transfer_destroy() when it's no longer needed
*/
int ITc_usb_host_control_transfer_set_index_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	unsigned char pszdata[DATA_SIZE];
	usb_host_transfer_h hHosttransfer;
	usb_host_device_h hHostDevice = NULL;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_create_control_transfer(hHostDevice, UsbHostTransferCB, pszdata, DATA_SIZE, NULL, 0, &hHosttransfer);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create_control_transfer", UsbHostGetError(nRet));
	CHECK_HANDLE(hHosttransfer,"usb_host_create_control_transfer")

	nRet = usb_host_control_transfer_set_index(hHosttransfer, 0x0000);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_control_transfer_set_index", UsbHostGetError(nRet), usb_host_transfer_destroy(hHosttransfer));

	nRet = usb_host_transfer_destroy(hHosttransfer);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_destroy", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Set usb-host transfer timeout
//& type: auto
/**
* @testcase 			ITc_usb_host_transfer_set_timeout_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 				auto
* @description			Set usb-host transfer timeout
* @scenario				Set usb-host transfer timeout
* @apicovered			usb_host_create_transfer,usb_host_transfer_set_timeout,usb_host_transfer_destroy
* @passcase				If target API and precondition API gets pass
* @failcase				If target API fails or any precondition API fails
* @precondition			ep must be a valid endpoint received from usb_host_interface_get_endpoint()
* @postcondition		ransfer should be destroyed by calling usb_host_transfer_destroy() when it's no longer needed
*/
int ITc_usb_host_transfer_set_timeout_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	unsigned char pszbuf[sizeof(TEST_DATA)];
	usb_host_transfer_h hHosttransfer;
	usb_host_interface_h hHostInterface = NULL;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hHostConfig = NULL;
	usb_host_endpoint_h hHostEndPoint = NULL;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hHostConfig);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostConfig,"usb_host_device_get_config");

	nRet = usb_host_config_get_interface(hHostConfig, 0, &hHostInterface);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostInterface,"usb_host_config_get_interface");

	nRet = usb_host_interface_get_endpoint(hHostInterface, 1, &hHostEndPoint);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_endpoint", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostEndPoint,"usb_host_interface_get_endpoint")

	nRet = usb_host_create_transfer(hHostEndPoint, UsbHostTransferCB, pszbuf, sizeof(TEST_DATA), NULL, 0, &hHosttransfer);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create_transfer", UsbHostGetError(nRet));
	CHECK_HANDLE(hHosttransfer,"usb_host_create_transfer")

	nRet = usb_host_transfer_set_timeout(hHosttransfer, 2000);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_set_timeout", UsbHostGetError(nRet), usb_host_transfer_destroy(hHosttransfer));

	nRet = usb_host_transfer_destroy(hHosttransfer);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_destroy", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb-host transfer Status
//& type: auto
/**
* @testcase 			ITc_usb_host_transfer_get_status_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 				auto
* @description			Get usb-host transfer Status
* @scenario				Get usb-host transfer Status
* @apicovered			usb_host_create_transfer,usb_host_transfer_get_status,usb_host_transfer_destroy
* @passcase				If target API and precondition API  gets pass
* @failcase				If target API fails or any precondition API fails
* @precondition			ep must be a valid endpoint received from usb_host_interface_get_endpoint()
* @postcondition		ransfer should be destroyed by calling usb_host_transfer_destroy() when it's no longer needed
*/
int ITc_usb_host_transfer_get_status_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	unsigned char pszbuf[sizeof(TEST_DATA)];
	usb_host_transfer_h hHosttransfer;
	usb_host_interface_h hHostInterface = NULL;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hHostConfig = NULL;
	usb_host_endpoint_h hHostEndPoint = NULL;
	int status;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hHostConfig);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostConfig,"usb_host_device_get_config");

	nRet = usb_host_config_get_interface(hHostConfig, 0, &hHostInterface);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostInterface,"usb_host_config_get_interface");

	nRet = usb_host_interface_get_endpoint(hHostInterface, 1, &hHostEndPoint);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_endpoint", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostEndPoint,"usb_host_interface_get_endpoint")

	nRet = usb_host_create_transfer(hHostEndPoint, UsbHostTransferCB, pszbuf, sizeof(TEST_DATA), NULL, 0, &hHosttransfer);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create_transfer", UsbHostGetError(nRet));
	CHECK_HANDLE(hHosttransfer,"usb_host_create_transfer")

	nRet = usb_host_transfer_get_status(hHosttransfer, &status);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_get_status", UsbHostGetError(nRet), usb_host_transfer_destroy(hHosttransfer));

	nRet = usb_host_transfer_destroy(hHosttransfer);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_destroy", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb-host transfer type
//& type: auto
/**
* @testcase 			ITc_usb_host_transfer_get_type_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 				auto
* @description			Get usb-host transfer type
* @scenario				Get usb-host transfer type
* @apicovered			usb_host_create_transfer,usb_host_transfer_get_type,usb_host_transfer_destroy
* @passcase				If target API and precondition API  gets pass
* @failcase				If target API fails or any precondition API fails
* @precondition			ep must be a valid endpoint received from usb_host_interface_get_endpoint()
* @postcondition		ransfer should be destroyed by calling usb_host_transfer_destroy() when it's no longer needed
*/
int ITc_usb_host_transfer_get_type_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	unsigned char pszbuf[sizeof(TEST_DATA)];
	usb_host_transfer_h hHosttransfer;
	usb_host_interface_h hHostInterface = NULL;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hHostConfig = NULL;
	usb_host_endpoint_h hHostEndPoint = NULL;
	usb_host_transfer_type_e hHosttype;
	int status;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hHostConfig);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostConfig,"usb_host_device_get_config");

	nRet = usb_host_config_get_interface(hHostConfig, 0, &hHostInterface);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostInterface,"usb_host_config_get_interface");

	nRet = usb_host_interface_get_endpoint(hHostInterface, 1, &hHostEndPoint);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_endpoint", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostEndPoint,"usb_host_interface_get_endpoint");

	nRet = usb_host_create_transfer(hHostEndPoint, UsbHostTransferCB, pszbuf, sizeof(TEST_DATA), NULL, 0, &hHosttransfer);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create_transfer", UsbHostGetError(nRet));
	CHECK_HANDLE(hHosttransfer,"usb_host_create_transfer");

	nRet = usb_host_transfer_get_type(hHosttransfer, &hHosttype);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_get_type", UsbHostGetError(nRet), usb_host_transfer_destroy(hHosttransfer));

	nRet = usb_host_transfer_destroy(hHosttransfer);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_destroy", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb-host transfer callback
//& type: auto
/**
* @testcase 			ITc_usb_host_transfer_set_callback_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 				auto
* @description			Get usb-host transfer callback
* @scenario				Get usb-host transfer callback
* @apicovered			usb_host_create_transfer,usb_host_transfer_set_callback,usb_host_transfer_destroy
* @passcase				If target API and precondition API  gets pass
* @failcase				If target API fails or any precondition API fails
* @precondition			sep must be a valid endpoint received from usb_host_interface_get_endpoint()
* @postcondition		ransfer should be destroyed by calling usb_host_transfer_destroy() when it's no longer needed
*/
int ITc_usb_host_transfer_set_callback_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	unsigned char pszbuf[sizeof(TEST_DATA)];
	usb_host_transfer_h hHosttransfer;
	usb_host_interface_h hHostInterface = NULL;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hHostConfig = NULL;
	usb_host_endpoint_h hHostEndPoint = NULL;
	usb_host_transfer_type_e hHosttype;
	int status;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hHostConfig);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostConfig,"usb_host_device_get_config");

	nRet = usb_host_config_get_interface(hHostConfig, 0, &hHostInterface);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostInterface,"usb_host_config_get_interface");

	nRet = usb_host_interface_get_endpoint(hHostInterface, 1, &hHostEndPoint);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_endpoint", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostEndPoint,"usb_host_interface_get_endpoint");

	nRet = usb_host_create_transfer(hHostEndPoint, UsbHostTransferCB, pszbuf, sizeof(TEST_DATA), NULL, 0, &hHosttransfer);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create_transfer", UsbHostGetError(nRet));
	CHECK_HANDLE(hHosttransfer,"usb_host_create_transfer");

	nRet = usb_host_transfer_set_callback(hHosttransfer, UsbHostTransferCB);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_set_callback", UsbHostGetError(nRet), usb_host_transfer_destroy(hHosttransfer));

	nRet = usb_host_transfer_destroy(hHosttransfer);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_destroy", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Set and get usb-host transfer iso packets
//& type: auto
/**
* @testcase 			ITc_usb_host_transfer_set_get_num_iso_packets_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 				auto
* @description			Set and get usb-host transfer iso packets
* @scenario				Set and get usb-host transfer iso packets
* @apicovered			usb_host_create_transfer,usb_host_transfer_set_num_iso_packets,usb_host_transfer_set_num_iso_packets,usb_host_transfer_destroy
* @passcase				If target API and precondition API  gets pass
* @failcase				If target API fails or any precondition API fails
* @precondition			ep must be a valid endpoint received from usb_host_interface_get_endpoint()
* @postcondition		ransfer should be destroyed by calling usb_host_transfer_destroy() when it's no longer needed
*/
int ITc_usb_host_transfer_set_get_num_iso_packets_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	unsigned char pszbuf[sizeof(TEST_DATA)];
	usb_host_transfer_h hHosttransfer;
	usb_host_interface_h hHostInterface = NULL;
	usb_host_device_h hHostDevice = NULL;
	usb_host_config_h hHostConfig = NULL;
	usb_host_endpoint_h hHostEndPoint = NULL;
	usb_host_transfer_type_e hHosttype;
	unsigned int num;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_device_get_config(hHostDevice, 0, &hHostConfig);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_get_config", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostConfig,"usb_host_device_get_config");

	nRet = usb_host_config_get_interface(hHostConfig, 0, &hHostInterface);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_config_get_interface", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostInterface,"usb_host_config_get_interface");

	nRet = usb_host_interface_get_endpoint(hHostInterface, 1, &hHostEndPoint);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_interface_get_endpoint", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostEndPoint,"usb_host_interface_get_endpoint");

	nRet = usb_host_create_transfer(hHostEndPoint, UsbHostTransferCB, pszbuf, sizeof(TEST_DATA), NULL, 0, &hHosttransfer);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create_transfer", UsbHostGetError(nRet));
	CHECK_HANDLE(hHosttransfer,"usb_host_create_transfer");

	nRet = usb_host_transfer_set_num_iso_packets(hHosttransfer, 0);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_set_num_iso_packets", UsbHostGetError(nRet), usb_host_transfer_destroy(hHosttransfer));

	nRet = usb_host_transfer_get_num_iso_packets(hHosttransfer, &num);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_set_num_iso_packets", UsbHostGetError(nRet), usb_host_transfer_destroy(hHosttransfer));

	if(num != 0)
	{
		usb_host_transfer_destroy(hHosttransfer);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] usb_host_transfer_get_num_iso_packets data mismatch with get %d and set %d data, error returned = %s (%d)", __FILE__, __LINE__, num, 2, UsbHostGetError(nRet), nRet);
		return 1;
	}
	nRet = usb_host_transfer_destroy(hHosttransfer);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_destroy", UsbHostGetError(nRet));

	return 0;
}

//& purpose: Get usb-host control transfer data
//& type: auto
/**
* @testcase 			ITc_usb_host_control_transfer_get_data_p
* @since_tizen			5.0
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 				auto
* @description			Get usb-host control transfer data
* @scenario				Get usb-host control transfer data
* @apicovered			usb_host_create_control_transfer,usb_host_control_transfer_get_data,usb_host_transfer_destroy
* @passcase				If target API and precondition API  gets pass
* @failcase				If target API fails or any precondition API fails
* @precondition			dev must be an opened device handle
* @postcondition		transfer should be destroyed by calling usb_host_transfer_destroy() when it's no longer needed
*/
int ITc_usb_host_control_transfer_get_data_p(void)
{
	START_TEST_FEATURE;
	int nRet;
	unsigned char pszdata[DATA_SIZE];
	usb_host_transfer_h hHosttransfer;
	usb_host_device_h hHostDevice = NULL;
	unsigned int len;
	unsigned char *hHostData;

	nRet = usb_host_device_open_with_vid_pid(g_CtxHandle, TEST_ID_VENDOR, TEST_ID_PRODUCT, &hHostDevice);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_device_open_with_vid_pid", UsbHostGetError(nRet));
	CHECK_HANDLE(hHostDevice,"usb_host_device_open_with_vid_pid");

	nRet = usb_host_create_control_transfer(hHostDevice, UsbHostTransferCB, pszdata, DATA_SIZE, NULL, 0, &hHosttransfer);
	PRINT_RESULT(USB_HOST_ERROR_NONE, nRet, "usb_host_create_control_transfer", UsbHostGetError(nRet));
	CHECK_HANDLE(hHosttransfer,"usb_host_create_control_transfer");

	nRet = usb_host_control_transfer_get_data(hHosttransfer, &hHostData, &len);
	PRINT_RESULT_CLEANUP(USB_HOST_ERROR_NONE, nRet, "usb_host_control_transfer_get_data", UsbHostGetError(nRet), usb_host_transfer_destroy(hHosttransfer));

	nRet = usb_host_transfer_destroy(hHosttransfer);
	PRINT_RESULT_NORETURN(USB_HOST_ERROR_NONE, nRet, "usb_host_transfer_destroy", UsbHostGetError(nRet));

	return 0;
}

/** @} */
/** @} */
