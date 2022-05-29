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
#ifndef _ITS_MTP_COMMON_H_
#define _ITS_MTP_COMMON_H_

#include "tct_common.h"
#include <mtp.h>
#include <app.h>
#include <glib-2.0/glib.h>
#include <math.h>

/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/


#define API_NAMESPACE					"MTP_ITC"
#define MTP_FEATURE						"http://tizen.org/feature/network.mtp"

bool g_bMTPNotSupported;
bool g_bMTPIsSupported;
bool g_bMTPMismatch;
bool g_bMTPInit;

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bMTPMismatch )\
	{\
	FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by mtp_initialize() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
	}\
	else if ( g_bMTPNotSupported )\
	{\
	FPRINTF("[Line : %d][%s] MTP feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);\
	return 0;\
	}\
	if ( !g_bMTPInit )\
	{\
	FPRINTF("[Line : %d][%s] Precondition of MTP initialization failed, Leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
	}\
}

char* MTPGetError(int nRet);

/** @} */
#endif  //_ITS_MTP_COMMON_H_
