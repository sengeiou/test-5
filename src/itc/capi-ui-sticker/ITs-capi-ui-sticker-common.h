//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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
#ifndef _ITS_CAPI_UI_STICKER_COMMON_H_
#define _ITS_CAPI_UI_STICKER_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <fcntl.h>
#include <dlog.h>
#include <glib.h>
#include <glib/gstdio.h> /* GStatBuf */
#include <stdint.h>
#include <stdbool.h>
#include <system_info.h>
#include <sticker_data.h>
#include <sticker_provider.h>
#include <sticker_consumer.h>


/** @addtogroup itc-capi-ui-sticker
*  @ingroup itc
*  @{
*/

bool g_bStickerCreation;
bool g_bIsFeatureMismatched;
bool g_bFeatureIsSupported;
bool g_bCallbackHit;
GMainLoop *g_pStickerMainLoop;


char* StickerGetError(int nRet);
gboolean Timeout(gpointer data);


#define API_NAMESPACE			"CAPI_UI_STICKER_ITC"
#define MAXENUMSIZE				50
#define SETENUM					1
#define GETENUM					0
#define TIMEOUT_CB			10000

#define FEATURE_STICKER					"http://tizen.org/feature/ui_service.sticker"

#define START_TEST {\
        FPRINTF("[Line:%d][%s] Starting test check initialize : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
        dlog_print(DLOG_INFO, "NativeTCT", "[Line:%d][%s] Starting test check initialize : %s", __LINE__, API_NAMESPACE, __FUNCTION__);\
        if ( g_bIsFeatureMismatched ) {\
                FPRINTF("[Line:%d][%s] Feature Mismatch Error\\n", __LINE__, API_NAMESPACE);\
                dlog_print(DLOG_ERROR, "NativeTCT", "[Line:%d][%s] Feature Mismatch Error", __LINE__, API_NAMESPACE);\
                return 1;\
        }\
        if ( !g_bFeatureIsSupported) {\
                FPRINTF("[Line : %d][%s] Feature Unsupported\\n", __LINE__, API_NAMESPACE);\
                dlog_print(DLOG_ERROR, "NativeTCT", "[Line:%d][%s] Feature Unsupported", __LINE__, API_NAMESPACE);\
                return 0;\
        }\
        if ( !g_bStickerCreation ) {\
                FPRINTF("[Line:%d][%s] Precondition Failed\\n", __LINE__, API_NAMESPACE);\
                dlog_print(DLOG_ERROR,"NativeTCT", "[Line:%d][%s] Precondition Failed", __LINE__, API_NAMESPACE);\
                return 1;\
        }\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

#define RUN_POLLING_LOOP {\
	g_pStickerMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, Timeout, g_pStickerMainLoop);\
	g_main_loop_run(g_pStickerMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pStickerMainLoop = NULL;\
}

#define QUIT_GMAIN_LOOP { \
    if (g_pStickerMainLoop) { \
        g_main_loop_quit(g_pStickerMainLoop); \
        g_pStickerMainLoop = NULL; \
    } \
}

sticker_provider_h g_hStickerProviderHandle;
sticker_data_h g_hStickerDataHandle;
sticker_consumer_h g_hStickerConsumerHandle;

#endif  //_ITS_CAPI_UI_STICKER_COMMON_H_
/** @} */
