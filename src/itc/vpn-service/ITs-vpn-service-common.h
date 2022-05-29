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
#ifndef _ITS_VPN_SERVICE_COMMON_H_
#define _ITS_VPN_SERVICE_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <system_info.h>
#include <vpn_service.h>

/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE					"VPN_SERVICE_ITC"
#define VPNSVC_FEATURE					"http://tizen.org/feature/network.vpn"
#define VPNSVC_IFACE_NAME 				"vpnsvc_iface"
#define VPNSVC_IFACE_NAME1 				"vpnsvc_iface1"
#define VPNSVC_IP4_STRING_LEN 				16

bool g_bVPNSVCNotSupported;
bool g_bVPNSVCIsSupported;
bool g_bVPNSVCMismatch;
bool g_bVPNSVCInit;

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bVPNSVCMismatch )\
	{\
	FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by vpnsvc_init() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
	}\
	else if ( g_bVPNSVCNotSupported )\
	{\
	FPRINTF("[Line : %d][%s] VPNSVC feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);\
	return 0;\
	}\
	if ( !g_bVPNSVCInit )\
	{\
	FPRINTF("[Line : %d][%s] Precondition of VPNSVC initialization failed, Leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
	}\
}

char* VPNSVCGetError(int nRet);

/** @} */
#endif  //_ITS_VPN_SERVICE_COMMON_H_
