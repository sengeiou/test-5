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
#ifndef _ITS_BADGE_COMMON_H_
#define _ITS_BADGE_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <badge.h>
#include <glib.h>

/** @addtogroup itc-badge
*  @ingroup itc
*  @{
*/

#define BUFFER 					512
#define BADGE_PACKAGE			"native.badge-itc"
#define API_NAMESPACE			"BADGE_ITC"
#define TIMEOUT_CB				15000
#define BADGE_FEATURE			"http://tizen.org/feature/badge"

//Add helper function declarations here
#define START_TEST {\
	FPRINTF("[Line : %d] Starting test : %s\\n", __LINE__ ,__FUNCTION__);\
	if(g_bBadgeNotSupported)\
	{\
		FPRINTF("[Line : %d][%s] Feature =%s  not supported	 :success ", __LINE__, API_NAMESPACE, BADGE_FEATURE);\
		return 0;\
	}\
	else if (g_bBadgeMismatch)\
	{\
		FPRINTF("[Line : %d][%s] Precondition of badge create feature=%s:Mismatch,failure  ", __LINE__, API_NAMESPACE, BADGE_FEATURE);\
		return 1;\
	}\
	if ( !g_bBadgeInit )\
	{\
		FPRINTF("[Line : %d] [badge_ITC] Precondition of badge create failed\\n", __LINE__);\
		return 1;\
	}\
}

int g_nTimeoutId;
GMainLoop *g_pMainLoop;
bool g_bCallBackHit;
bool g_bBadgeNotSupported;
bool g_bBadgeMismatch;

char *BadgeGetError(int nRet);
gboolean TimeoutFunction(gpointer data);
void IterateGmainLoop(void);
void QuitGmainLoop(void);

/** @} */
#endif  //_ITS_BADGE_COMMON_H_
