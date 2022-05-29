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
#ifndef _ITS_NNTRAINER_COMMON_H_
#define _ITS_NNTRAINER_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <system_info.h>
#include <app_common.h>
#include <dlog.h>
#include <nntrainer.h>

/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE		"NNTRAINER_ITC"
#define ML_TRAIN_FEATURE	"http://tizen.org/feature/machine_learning.training"
#define LABEL_PATH			"label.dat"
#define CONF_PATH			"model.ini"
#define TESTSET_PATH		"trainingSet.dat"
#define TRAININGSET_PATH	"trainingSet.dat"
#define VALSET_PATH			"trainingSet.dat"
#define PATH_LEN			1024
#define FEATURE_SIZE		62720
#define PATH_MAX			4096
#define BIN_PATH			"bin.bin"

static char bin_path[PATH_MAX];
char* NnTrainerGetError(int nRet);
bool GetResourceDataPath(const char *pFilePath, const char *pFinalPath);
int Set_Layer_Property(ml_train_layer_h hTrainLayer, int nLayerEnum);

bool g_bIsMLTrainFeatureSupported;
bool g_bNntrainerCreation;
bool g_bIsFeatureMismatched;
bool g_CallBackHit;

#define START_TEST {\
	FPRINTF("[Line:%d][%s] Starting test check initialize : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	dlog_print(DLOG_INFO, "NativeTCT", "[Line:%d][%s] Starting test check initialize : %s", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bIsFeatureMismatched ) {\
		FPRINTF("[Line:%d][%s] Feature Mismatch Error\\n", __LINE__, API_NAMESPACE);\
		dlog_print(DLOG_ERROR, "NativeTCT", "[Line:%d][%s] Feature Mismatch Error", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
	if ( !g_bIsMLTrainFeatureSupported) {\
		FPRINTF("[Line : %d][%s] Feature Unsupported\\n", __LINE__, API_NAMESPACE);\
		dlog_print(DLOG_ERROR, "NativeTCT", "[Line:%d][%s] Feature Unsupported", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
	if ( !g_bNntrainerCreation ) {\
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

/** @} */
#endif  //_ITS_NNTRAINER_COMMON_H_
