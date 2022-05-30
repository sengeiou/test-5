//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef _ITS_STC_COMMON_H_
#define _ITS_STC_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <app.h>
#include <stc.h>

#include <glib.h>
#include <glib-object.h>

/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE				"STC_ITC"
#define STC_FEATURE					"http://tizen.org/feature/network.traffic_control"
#define STC_ALL_APP					"TOTAL_WIFI"
#define CALLBACK_RETURN				"callback return"
#define GMAINTIMEOUT				20000

#define START_TEST {\
	CHECK_INIT;\
	CHECK_RULE_CREATION;\
}

#define CHECK_INIT {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if(g_bStcNotSupported)\
	{\
		FPRINTF("[Line : %d][%s] Feature =%s  not supported	 :success ", __LINE__, API_NAMESPACE, STC_FEATURE);\
		return 0;\
	}\
	else if (g_bStcMismatch)\
	{\
		FPRINTF("[Line : %d][%s] Precondition of Stc feature=%s:Mismatch,failure  ", __LINE__, API_NAMESPACE, STC_FEATURE);\
		return 1;\
	}\
	else if ( !g_bStcInit )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of Stc create failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define CHECK_RULE_CREATION {\
	if ( !g_bStcRuleCreation )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of Stc rule create failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define RUN_GMAIN_LOOP {\
	g_pStcMainLoop = g_main_loop_new(NULL, false);\
	g_nTimeoutId = g_timeout_add(GMAINTIMEOUT, StcTimeout, g_pStcMainLoop);\
	g_main_loop_run(g_pStcMainLoop);\
	g_source_remove(g_nTimeoutId);\
	g_pStcMainLoop = NULL;\
}

#define QUIT_GMAIN_LOOP {\
	if (g_pStcMainLoop)\
		g_main_loop_quit(g_pStcMainLoop);\
}


typedef enum {
	STATS_INFO_UNKNOWN,
	STATS_INFO_APPID,
	STATS_INFO_IFACE_NAME,
	STATS_INFO_TIME_INTERVAL,
	STATS_INFO_IFACE_TYPE,
	STATS_INFO_COUNTER,
	STATS_INFO_ROAMING_TYPE,
	STATS_INFO_PROTOCOL_TYPE,
	STATS_INFO_PROCESS_STATE,
	STATS_INFO_GET_ALL,
	STATS_INFO_FOREACH_ALL,
} stc_stats_info_e;

//Add helper function declarations here


GMainLoop *g_pStcMainLoop;
guint g_nTimeoutId;
bool g_bFeatureSTC;
bool g_bStcNotSupported;
bool g_bStcMismatch;
bool g_bStcInit;
bool g_bStcRuleCreation;
stc_h g_hSTC;
stc_stats_rule_h g_hRule;
bool g_bCallbackCalled;
bool g_bCallbackGetValue;
int  g_iTargetApiCallback;
stc_stats_info_e g_eStatsInfo;

gboolean StcTimeout(gpointer data);
char* StcGetError(int nRet);
time_t StcMakeTime(int year, int mon, int day, int hour, int min);
#define STC_YEAR 2000
#define STC_MONTH 1
#define STC_DAY 1
#define STC_HOUR 1
#define STC_MIN 1
/** @} */
#endif	//_ITS_STC_COMMON_H_
