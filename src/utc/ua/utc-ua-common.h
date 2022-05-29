/*
 * Copyright (c) 2021 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef _UA_UTC_COMMON_H_
#define _UA_UTC_COMMON_H_

#include <tct_common.h>
#include <system_info.h>
#include <user-awareness.h>
#include <glib.h>
#include <dlog.h>

#define GMAINTIMEOUT 10000
#define UA_FEATURE "http://tizen.org/feature/user_awareness"
#define UA_LOCATION_FEATURE "http://tizen.org/feature/user_awareness.location"

#define CASE_TO_STR(x) case x: return #x;

#define RUN_GMAIN_LOOP {\
	guint g_nTimeoutId = 0;\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	g_nTimeoutId = g_timeout_add(GMAINTIMEOUT, __ua_callback_timeout, g_pMainLoop);\
	FPRINTF("[Line:%5d][%s] Run mainloop [%p]\\n", __LINE__, __FUNCTION__, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(g_nTimeoutId);\
	g_pMainLoop = NULL;\
}

#define QUIT_GMAIN_LOOP {\
	FPRINTF("[Line:%5d][%s] Quit mainloop [%p]\\n", __LINE__, __FUNCTION__, g_pMainLoop);\
	g_main_loop_quit(g_pMainLoop);\
}

#define GFREE(var) {\
	if(var != NULL) {\
		g_free(var);\
		var = NULL;\
	}\
}

#define PRINT_RETURN(api, ret) {\
	FPRINTF("[Line:%5d][%s] %s returned = %s(0x%X)\\n", \
		__LINE__, __FUNCTION__, api, ua_error_to_string(ret), ret);\
}

#define CHECK_INIT_RETURN() {\
	if (!ua_is_initialized()) {\
		FPRINTF("[Line:%5d][%s] UA is not initialized\\n", __LINE__, __FUNCTION__);\
		return 1;\
	}\
}

#define CHECK_RETURN(api, ret, val) {\
	if (ret != val) {\
		FPRINTF("[Line:%5d][%s] %s failed, error returned = %s(0x%X)\\n",\
			__LINE__, __FUNCTION__, api, ua_error_to_string(ret), ret);\
		return 1;\
	} else {\
		FPRINTF("[Line:%5d][%s] %s\\n", __LINE__, __FUNCTION__, api);\
	}\
}

#define CHECK2_RETURN(api, ret, val1, val2) {\
	if (ret != val1 && ret != val2) {\
		FPRINTF("[Line:%5d][%s] %s failed, error returned = %s(0x%X)\\n",\
			__LINE__, __FUNCTION__, api, ua_error_to_string(ret), ret);\
		return 1;\
	} else {\
		FPRINTF("[Line:%5d][%s] %s\\n", __LINE__, __FUNCTION__, api);\
	}\
}

#define DEBUG_LOG(str) {\
	FPRINTF("[Line:%5d][%s] ***** DEBUG [%s] *****\\n", __LINE__, __FUNCTION__, str);\
}

#define PRINT_LOG(str1, str2) {\
	FPRINTF("[Line:%5d][%s] %s [%s]\\n", __LINE__, __FUNCTION__, str1, str2);\
}

const char *ua_error_to_string(ua_error_e err);

void utc_ua_startup(void);
void utc_ua_cleanup(void);
bool ua_is_initialized(void);
int ua_is_feature_supported(void);
int ua_is_feature_location_supported(void);

#endif  /* _UA_UTC_COMMON_H_ */
