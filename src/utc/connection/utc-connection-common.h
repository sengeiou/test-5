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

#ifndef _CONNECTION_COMMON_H_
#define _CONNECTION_COMMON_H_

#include <tct_common.h>
#include <system_info.h>
#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <net_connection.h>
#include <dlog.h>
#include "assert.h"

#define CONNECTION_DEBUG        1
#define GMAINTIMEOUT			20000
#define CUSTOM_PROFILE_NAME		"Net"

#define FEATURE_WIFI				"http://tizen.org/feature/network.wifi"
#define FEATURE_ETHERNET			"http://tizen.org/feature/network.ethernet"
#define FEATURE_TELEPHONY			"http://tizen.org/feature/network.telephony"
#define FEATURE_BT_TETHERING			"http://tizen.org/feature/network.tethering.bluetooth"
#define CALLBACK_RETURN				"callback return"

GMainLoop *g_pMainLoop;
guint g_nTimeoutId;
int g_CallbackRet;

bool wifi_supported;
bool telephony_supported;
bool bt_tethering_supported;
bool ethernet_supported;
bool all_features_not_supported;

connection_profile_h profile_cellular;
connection_profile_h profile_wifi;
connection_profile_h profile_temp;
connection_h connection;

#define RUN_GMAIN_LOOP {\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	g_nTimeoutId = g_timeout_add(GMAINTIMEOUT, test_connection_timeout_callback, g_pMainLoop);\
	FPRINTF("[Line:%d][%s] Run mainloop [%p]\\n", __LINE__, __FUNCTION__, g_pMainLoop);\
	dlog_print(DLOG_INFO, "NativeTCT", "[Line:%d][%s] Run mainloop [%p]", __LINE__, __FUNCTION__, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(g_nTimeoutId);\
	g_pMainLoop = NULL;\
}

#define QUIT_GMAIN_LOOP {\
	if (g_pMainLoop)\
{\
	FPRINTF("[Line:%d][%s] Quit mainloop [%p]\\n", __LINE__, __FUNCTION__, g_pMainLoop);\
	dlog_print(DLOG_INFO, "NativeTCT", "[Line:%d][%s] Quit mainloop [%p]", __LINE__, __FUNCTION__, g_pMainLoop);\
	g_main_loop_quit(g_pMainLoop);\
}\
}

#define FREE_RESOURCE(var)\
	if(var != NULL) {\
		g_free(var);\
		var = NULL;\
}

#define PRINT_RETURN(api, ret) {\
	if (CONNECTION_DEBUG) {\
		FPRINTF("[%s:%d] %s returned = %s\\n",\
			__FILE__, __LINE__, api, connection_get_error(ret));\
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] %s returned = %s",\
			__FILE__, __LINE__, api, connection_get_error(ret));\
	}\
}

#define CHECK_RETURN(api, ret, val) {\
	if (ret != val) {\
		FPRINTF("[%s:%d] %s failed, error returned = %s\\n",\
			__FILE__, __LINE__, api, connection_get_error(ret));\
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] %s failed, error returned = %s",\
			__FILE__, __LINE__, api, connection_get_error(ret));\
		return 1;\
	} else {\
		FPRINTF("[%s:%d] %s\\n",\
			__FILE__, __LINE__, api);\
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] %s",\
			__FILE__, __LINE__, api);\
	}\
}

gboolean test_connection_timeout_callback(gpointer data);
const char *connection_get_error(connection_error_e error);
bool connection_check_feature_supported(char *key);
int test_get_any_profile(connection_profile_h *profile);

#endif /* _CONNECTION_COMMON_H_ */
