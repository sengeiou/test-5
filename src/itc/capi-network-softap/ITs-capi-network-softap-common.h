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
#ifndef _ITS_CAPI_NETWORK_SOFTAP_COMMON_H_
#define _ITS_CAPI_NETWORK_SOFTAP_COMMON_H_

#include "tct_common.h"
#include <softap.h>
#include <system_info.h>
#include <glib.h>
#include <dlog.h>

#define API_NAMESPACE 	      "SOFTAP_ITC"
#define SOFTAP_FEATURE        "http://tizen.org/feature/network.wifi.softap"
#define PASSPHRASE_MAX 10

bool g_bIsFeatureSupported;
bool g_bSoftapFetaureSupported;
bool g_bIsFeatureMismatched;
bool g_bIsSoftapHandleCreated;

#define START_TEST_CHECK_INITIALIZE {\
        FPRINTF("[Line:%d][%s] Starting test check initialize : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
        dlog_print(DLOG_INFO, "NativeTCT", "[Line:%d][%s] Starting test check initialize : %s", __LINE__, API_NAMESPACE, __FUNCTION__);\
        if ( g_bIsFeatureMismatched ) {\
                FPRINTF("[Line:%d][%s] Feature Mismatch Error\\n", __LINE__, API_NAMESPACE);\
                dlog_print(DLOG_ERROR, "NativeTCT", "[Line:%d][%s] Feature Mismatch Error", __LINE__, API_NAMESPACE);\
                return 1;\
        }\
        if ( !g_bSoftapFetaureSupported) {\
                FPRINTF("[Line : %d][%s] Feature Unsupported\\n", __LINE__, API_NAMESPACE);\
                dlog_print(DLOG_ERROR, "NativeTCT", "[Line:%d][%s] Feature Unsupported", __LINE__, API_NAMESPACE);\
                return 0;\
        }\
	else if ( !g_bIsSoftapHandleCreated )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of softap create failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}
char* SoftApGetError(int nRet);
#endif //_ITS_CAPI_NETWORK_SOFTAP_COMMON_H_
