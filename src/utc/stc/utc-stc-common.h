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

#ifndef _STC_COMMON_H_
#define _STC_COMMON_H_

#include <tct_common.h>
#include <stc.h>
#include <system_info.h>
#include <glib.h>

#define STC_DEBUG					1
#define CONFIG_VALUE_LEN_MAX		1024
#define GMAINTIMEOUT 				20000

#define STC_FEATURE					"http://tizen.org/feature/network.traffic_control"
#define STC_ALL_APP					"TOTAL_DATACALL"
#define CALLBACK_RETURN				"callback return"

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
	STATS_INFO_CLONE,
	STATS_INFO_DESTROY,
	STATS_INFO_GET_ALL,
	STATS_INFO_FOREACH_ALL
} stc_stats_info_e;

GMainLoop *g_pMainLoop;
guint g_nTimeoutId;
int g_nCallbackRet;

bool g_bFeatureSTC;

stc_h g_hSTC;
stc_stats_rule_h g_hRule;
stc_error_e g_nCallbackRet;
stc_stats_info_e g_eStatsInfo;

#define RUN_GMAIN_LOOP {\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	g_nTimeoutId = g_timeout_add(GMAINTIMEOUT, stc_callback_timeut, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(g_nTimeoutId);\
	g_pMainLoop = NULL;\
}

#define QUIT_GMAIN_LOOP {\
	if (g_pMainLoop)\
		g_main_loop_quit(g_pMainLoop);\
}

#define PRINT_RETURN(api, ret) {\
	if (STC_DEBUG) {\
		FPRINTF("[%s:%d] %s returned = %s\\n",\
			__FILE__, __LINE__, api, stc_get_error(ret));\
	}\
}

#define CHECK_RETURN(api, ret, val) {\
	if (ret != val) {\
		FPRINTF("[%s:%d] %s failed, error returned = %s\\n",\
			__FILE__, __LINE__, api, stc_get_error(ret));\
		return 1;\
	} else {\
		PRINT_RETURN(api, ret);\
	}\
}

gboolean stc_callback_timeut(gpointer data);
const char *stc_get_error(int err);
bool stc_check_feature_supported(char *key);
time_t stc_make_time(int year, int mon, int day, int hour, int min);
stc_error_e stc_get_all_stats_info(stc_stats_info_e e);
void stc_get_stats_finished_cb(stc_error_e result,
		stc_all_stats_info_h info, void *user_data);
stc_error_e stc_get_statistics_information(stc_stats_info_e e);
stc_callback_ret_e stc_stats_info_callback(stc_error_e result,
		stc_stats_info_h info, void *user_data);


#endif  /* _STC_COMMON_H_ */

