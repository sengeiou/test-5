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
#ifndef _ITS_NNSTREAMER_COMMON_H_
#define _ITS_NNSTREAMER_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <fcntl.h>
#include <dlog.h>
#include <glib.h>
#include <glib/gstdio.h> /* GStatBuf */
#include <nnstreamer.h>
#include <nnstreamer-single.h>
#include <stdint.h>

/** @addtogroup itc-nnstreamer
*  @ingroup itc
*  @{
*/

bool g_bNnstreamerCreation;
bool g_bIsFeatureMismatched;
bool g_bFeatureML;
bool g_bFeatureMLInterference;
bool g_bFeatureIsSupported;
bool g_bCallbackHit;
bool g_bFeatureMLService;
GMainLoop *g_pNnStreamerMainLoop;

typedef struct
{
  gboolean paused;
  gboolean playing;
} TestPipeState;

gchar * pszNnpipeline;
ml_pipeline_h g_hPipelinehandle;
ml_pipeline_state_e state;
guint * g_unsinkCount;
TestPipeState * g_pipePipeLineState;

char* NnStreamerGetError(int nRet);
gboolean Timeout(gpointer data);
void FreeCustomTensorMemory(gchar **t_pszNnpipeline,guint **t_unsinkCount,gchar ***t_psz_fullpath,gchar **t_psz_file);
void TensorInfoDataDestroy(ml_tensors_info_h hTensorinfo,ml_tensors_data_h hTensorData);
void TensorInfoPipelineStop(ml_pipeline_h hPipelinehandle,ml_pipeline_src_h hPipeSrcHandle, ml_pipeline_sink_h hPipeSinkHandle,ml_tensors_info_h hTensorinfo);


#define API_NAMESPACE			"NNSTREAMER_ITC"
#define MAXENUMSIZE				50
#define SETENUM					1
#define GETENUM					0
#define TIMEOUT_CB			10000
#define LIMIT				10
#define PIPELINE_STREAM		"appsrc name=appsrc ! other/tensor,dimension=(string)4:1:1:1, type=(string)uint8,framerate=(fraction)0/1 ! "  "tensor_if name=tif compared-value=CUSTOM compared-value-option=tif_custom_cb_name then=PASSTHROUGH else=PASSTHROUGH "  "tif.src_0 ! queue ! filesink location=\"%s\" buffer-mode=unbuffered "  "tif.src_1 ! queue ! tensor_sink name=sink_false sync=false async=false"

#define FEATURE_ML					"http://tizen.org/feature/machine_learning"
#define FEATURE_ML_INTERFACE		"http://tizen.org/feature/machine_learning.inference"
#define FEATURE_ML_SERVICE    "http://tizen.org/feature/machine_learning.service"

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
	if ( !g_bNnstreamerCreation ) {\
		FPRINTF("[Line:%d][%s] Precondition Failed\\n", __LINE__, API_NAMESPACE);\
		dlog_print(DLOG_ERROR,"NativeTCT", "[Line:%d][%s] Precondition Failed", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define START_TEST_ML_SERVICE {\
    FPRINTF("[Line:%d][%s] Starting test check initialize : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	dlog_print(DLOG_INFO, "NativeTCT", "[Line:%d][%s] Starting test check initialize : %s", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define ML_SERVICE_FEATURE_CHECK {\
    if ( !g_bFeatureML || !g_bFeatureMLService ) \
    {\
        if (nRetVal == TIZEN_ERROR_NOT_SUPPORTED){\
             FPRINTF("[Line:%d][%s] Feature is not supported \\n", __LINE__, API_NAMESPACE);\
             return 0;\
        }\
        else{\
             FPRINTF("[Line:%d][%s] Feature mismatch error \\n", __LINE__, API_NAMESPACE);\
             return 1;\
		}\
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
	g_pNnStreamerMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, Timeout, g_pNnStreamerMainLoop);\
	g_main_loop_run(g_pNnStreamerMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pNnStreamerMainLoop = NULL;\
}




#endif  //_ITS_NNSTREAMER_COMMON_H_
/** @} */
