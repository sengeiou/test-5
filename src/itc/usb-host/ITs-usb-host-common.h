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
#ifndef _ITS_USBHOST_COMMON_H_
#define _ITS_USBHOST_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include "usb_host.h"
#include <dlog.h>
#include <system_info.h>
#include <glib.h>

bool g_bIsFeatureMismatched;
bool g_bFeatureUsb;
bool g_bUsbCreation;

#define TIMEOUT_CB                  20000
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
GMainLoop *g_pUsbHostMainLoop;
int nTimeoutId;
bool gUsbCallback;
/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/

//Add helper function declarations here

#define API_NAMESPACE			"USBHOST_ITC"
#define USBHOST_FEATURE			"http://tizen.org/feature/usb.host"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define START_TEST_FEATURE {\
        FPRINTF("[Line:%d][%s] Starting test check usb-host create : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
        dlog_print(DLOG_INFO, "NativeTCT", "[Line:%d][%s] Starting test check create : %s", __LINE__, API_NAMESPACE, __FUNCTION__);\
        START_TEST;\
        if ( g_bIsFeatureMismatched ) {\
                FPRINTF("[Line:%d][%s] Feature Mismatch Error\\n", __LINE__, API_NAMESPACE);\
                dlog_print(DLOG_ERROR, "NativeTCT", "[Line:%d][%s] Feature Mismatch Error", __LINE__, API_NAMESPACE);\
                return 1;\
        }\
        if ( !g_bFeatureUsb) {\
                FPRINTF("[Line : %d][%s] Feature Unsupported\\n", __LINE__, API_NAMESPACE);\
                dlog_print(DLOG_ERROR, "NativeTCT", "[Line:%d][%s] Feature Unsupported", __LINE__, API_NAMESPACE);\
                return 0;\
        }\
        if ( !g_bUsbCreation ) {\
                FPRINTF("[Line:%d][%s] Precondition Failed\\n", __LINE__, API_NAMESPACE);\
                dlog_print(DLOG_ERROR,"NativeTCT", "[Line:%d][%s] Precondition Failed", __LINE__, API_NAMESPACE);\
                return 1;\
        }\
}
#define RUN_POLLING_LOOP {\
        g_pUsbHostMainLoop = g_main_loop_new(NULL, false);\
        nTimeoutId = g_timeout_add(TIMEOUT_CB, UsbHostTimeout, g_pUsbHostMainLoop);\
        FPRINTF("[Line:%d][%s] Run mainloop [%p]\\n", __LINE__, __FUNCTION__, g_pUsbHostMainLoop);\
        dlog_print(DLOG_INFO, "NativeTCT", "[Line:%d][%s] Run mainloop [%p]", __LINE__, __FUNCTION__, g_pUsbHostMainLoop);\
        g_main_loop_run(g_pUsbHostMainLoop);\
        g_source_remove(nTimeoutId);\
        g_pUsbHostMainLoop = NULL;\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
        if ( Handle == NULL )\
{\
        FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
        FreeResource;\
        return 1;\
}\
}


bool g_bUsbIssupportedFeature;
bool g_bUsbNotSupported;
usb_host_context_h g_CtxHandle;
gboolean UsbHostTimeout(gpointer data);
char* UsbHostGetError(usb_host_error_e error);
/** @} */
#endif  //_ITS_USBHOST_COMMON_H_
