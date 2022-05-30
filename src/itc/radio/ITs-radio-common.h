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
#ifndef _ITS_RADIO_COMMON_H_
#define _ITS_RADIO_COMMON_H_

#include "tct_common.h"
#include <radio.h>
#include <glib.h>

/** @addtogroup itc-radio
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE				"RADIO_ITC"
#define GMAINTIMEOUT				25000
#define RADIO_FEATURE               "http://tizen.org/feature/fmradio"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE ,__FUNCTION__);\
	if ( g_bRadioNotSupported )\
	{\
	FPRINTF("[Line : %d][%s] Required feature of radio is not supported. So leaving test\\n", __LINE__, API_NAMESPACE);\
	return 0;\
	}\
	if ( g_bMismatch )\
	{\
	FPRINTF("[Line : %d][%s] Radio_Check_System_Info_Feature_Supported and radio_create returned different value. So leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
	}\
	if ( !g_nRadioCreated )\
	{\
	FPRINTF("[Line : %d][%s] Precondition of radio failed\\n", __LINE__, API_NAMESPACE);\
	return 1;\
	}\
}

#define RUN_POLLING_LOOP {\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(GMAINTIMEOUT, RadioTimeout, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pMainLoop = NULL;\
}

char* RadioGetError(int nRet);
char* RadioGetState(radio_state_e nRet);
/** @} */
#endif  //_ITS_RADIO_COMMON_H_
