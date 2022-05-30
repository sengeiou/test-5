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
#ifndef _ITS_URL_DOWNLOAD_COMMON_H_
#define _ITS_URL_DOWNLOAD_COMMON_H_

#include "tct_common.h"
#include <glib.h>
#include <glib-object.h>
#include <download.h>

/** @addtogroup itc-url-download
*  @ingroup itc
*  @{
*/

//& set: UrlDownload
bool g_bCheckCb;
bool g_bUrlDownloadOpen;
bool g_bDownloadingState;
bool g_bDownloadingComplete;
int g_nDownloadRequestID;
bool g_bDownloadNotSupported;
bool g_bDownloadMismatch;
GMainLoop *g_pMainLoop;

#define GMAINTIMEOUT			25000
#define API_NAMESPACE			"URL_DOWNLOAD_ITC"

#define TELEPHONY_FEATURE		"tizen.org/feature/network.telephony"
#define WIFI_FEATURE		    "tizen.org/feature/network.wifi"
#define WIFI_DIRECT_FEATURE		"tizen.org/feature/network.wifi.direct"
#define DOWNLOAD_FEATURE		"tizen.org/feature/download"

bool UrlDownloadCreateEnv(int nRequestId, bool bIsDownload);
gboolean UrlDownloadCallbackTimeout(gpointer data);
void DownloadProgressCallback (int download_id, unsigned long long received, void *user_data);
void DownloadStateCallback(int download_id, download_state_e state, void *user_data);

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if(g_bDownloadNotSupported)\
	{\
		FPRINTF("[Line : %d][%s] Feature =%s  not supported	 :success ", __LINE__, API_NAMESPACE, DOWNLOAD_FEATURE);\
		return 0;\
	}\
	else if (g_bDownloadMismatch)\
	{\
		FPRINTF("[Line : %d][%s] Precondition of url download feature=%s:Mismatch,failure  ", __LINE__, API_NAMESPACE, DOWNLOAD_FEATURE);\
		return 1;\
	}\
	if ( !g_bUrlDownloadOpen )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of url download Open failed\\n", __LINE__, API_NAMESPACE);\
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
	g_pMainLoop = g_main_loop_new(NULL, false);\
	nURLTimeoutId = g_timeout_add(GMAINTIMEOUT, UrlDownloadCallbackTimeout, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nURLTimeoutId);\
	g_pMainLoop = NULL;\
}
bool g_bIsTelephonyFeatureSupported;
bool g_bIsWifiFeatureSupported;
bool g_bIsWifiDirectFeatureSupported;
char *UrlDownloadGetError(int nRet);
char *UrlDownloadNetworkType(int nRet);
char* UrlDownloadNotificationType(int nRet);
char* UrlDownloadState(int nRet);
char* UrlDownloadAppControlGetError(int nRet);
char* UrlDownloadGetStorageDirectory(void);
/** @} */
#endif  //_ITS_URL_DOWNLOAD_COMMON_H_
