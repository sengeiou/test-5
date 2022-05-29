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
#include "ITs-usb-host-common.h"

/** @addtogroup itc-usbhost
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		UsbHostGetError
* @description	 	Maps usb_host_error_e enums 
* @parameter		error : error level
* @return 			error string
*/
char* UsbHostGetError(usb_host_error_e error)
{
	char *szErrorVal = NULL;
	switch ( error )
	{
	case USB_HOST_ERROR_NONE:				szErrorVal = "USB_HOST_ERROR_NONE";					break;
	case USB_HOST_ERROR_IO_ERROR:				szErrorVal = "USB_HOST_ERROR_IO_ERROR";					break;
	case USB_HOST_ERROR_INVALID_PARAMETER:				szErrorVal = "USB_HOST_ERROR_INVALID_PARAMETER";					break;
	case USB_HOST_ERROR_PERMISSION_DENIED:				szErrorVal = "USB_HOST_ERROR_PERMISSION_DENIED";					break;
	case USB_HOST_ERROR_NO_SUCH_DEVICE:				szErrorVal = "USB_HOST_ERROR_NO_SUCH_DEVICE";					break;
	case USB_HOST_ERROR_NOT_FOUND:				szErrorVal = "USB_HOST_ERROR_NOT_FOUND";					break;
	case USB_HOST_ERROR_RESOURCE_BUSY:				szErrorVal = "USB_HOST_ERROR_RESOURCE_BUSY";					break;
	case USB_HOST_ERROR_TIMED_OUT:				szErrorVal = "USB_HOST_ERROR_TIMED_OUT";					break;
	case USB_HOST_ERROR_OVERFLOW:				szErrorVal = "USB_HOST_ERROR_OVERFLOW";					break;
	case USB_HOST_ERROR_DEVICE_NOT_OPENED:				szErrorVal = "USB_HOST_ERROR_DEVICE_NOT_OPENED";					break;
	case USB_HOST_ERROR_BROKEN_PIPE:				szErrorVal = "USB_HOST_ERROR_BROKEN_PIPE";					break;
	case USB_HOST_ERROR_INTERRUPTED_SYS_CALL:				szErrorVal = "USB_HOST_ERROR_INTERRUPTED_SYS_CALL";					break;
	case USB_HOST_ERROR_OUT_OF_MEMORY:				szErrorVal = "USB_HOST_ERROR_OUT_OF_MEMORY";					break;
	case USB_HOST_ERROR_NOT_SUPPORTED:				szErrorVal = "USB_HOST_ERROR_NOT_SUPPORTED";					break;
	default:							szErrorVal = "Unknown Error";					break;
	}

	return szErrorVal;
}

/**
* @function         UsbHostTimeout
* @description      Called if some callback is not invoked for a particular timeout
* @parameter        gpointer data
* @return           gboolean
*/
gboolean UsbHostTimeout(gpointer data)
{
        GMainLoop *pMainLoop = NULL;
        pMainLoop = (GMainLoop *)data;
        if ( pMainLoop != NULL )
        {
                dlog_print(DLOG_INFO, "NativeTCT", "[%d:%s] Quit mainloop(timeout)[%p]", __LINE__, __FUNCTION__, pMainLoop);
                g_main_loop_quit(pMainLoop);
        }
        FPRINTF("[%d:%s] Callback Timeout\\n", __LINE__, __FUNCTION__);
        dlog_print(DLOG_ERROR, "NativeTCT", "[%d:%s] Callback Timeout", __LINE__, __FUNCTION__);
        return false;
}

/** @} */
