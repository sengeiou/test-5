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
#ifndef _ITS_CAMERA_COMMON_H_
#define _ITS_CAMERA_COMMON_H_

#include "tct_common.h"
#include "camera.h"

#include <glib.h>
#include <sys/types.h>
#include <Elementary.h>
#include <Evas.h>
/** @addtogroup itc-camera
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE				"CAMERA_ITC"
#define LOG							100
#define MICROSECONDS_PER_SECOND		1000000
#define TIMEOUT_CB					5000
#define IMAGECOUNT					5
#define IMAGE_INTERVAL				10
#define CAMERA_FEATURE				"http://tizen.org/feature/camera"
#define CAMERA_FEATURE_BACK			"http://tizen.org/feature/camera.back"
#define CAMERA_FEATURE_FRONT		"http://tizen.org/feature/camera.front"
#define CAMERA_FEATURE_BACK_FLASH	"http://tizen.org/feature/camera.back.flash"
#define CAMERA_FEATURE_FRONT_FLASH	"http://tizen.org/feature/camera.front.flash"

typedef struct Resolution{
	int nWidth;
	int nHeight;
} CameraResolution;

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bSkipExecutionWithPass == true )\
{\
	FPRINTF("[Line : %d][%s] Required feature of camera_create is not supported. So leaving test\\n", __LINE__, API_NAMESPACE);\
	return 0;\
}\
	if ( g_bSkipExecutionWithFail == true )\
{\
	FPRINTF("[Line : %d][%s] camera_create returned not supported, although feature supported as seen from model_config.xml So leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
	if ( !g_bCameraCreation )\
{\
	FPRINTF("[Line : %d][%s]Precondition of camera create failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
}

#define RUN_POLLING_LOOP {\
	g_pCameraMainLoop = g_main_loop_new(NULL, false);\
	nCameraTimeoutId = g_timeout_add(TIMEOUT_CB, CameraTimeout, g_pCameraMainLoop);\
	g_main_loop_run(g_pCameraMainLoop);\
	g_source_remove(nCameraTimeoutId);\
	g_pCameraMainLoop = NULL;\
}

#define CHECK_UNSUPPORTED_ERROR_RETURN(bSupported, szApi)\
	if ( !bSupported )\
{\
	if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )\
{\
	FPRINTF("[Line : %d][%s] %s returned %s for unsupported feature\\n", __LINE__, API_NAMESPACE, szApi, CameraGetError(nRet));\
	return 1;\
}\
		else\
{\
	FPRINTF("[Line : %d][%s] %s API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, szApi, CameraGetError(nRet));\
	return 0;\
}\
}\

#define CHECK_UNSUPPORTED_ERROR_CONTINUE(bSupported, szApi, nErrorCount)\
	if ( !bSupported )\
{\
	if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )\
{\
	FPRINTF("[Line : %d][%s] %s returned %s for unsupported feature\\n", __LINE__, API_NAMESPACE, szApi, CameraGetError(nRet));\
	nErrorCount++;\
}\
		else\
{\
	FPRINTF("[Line : %d][%s] %s API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, szApi, CameraGetError(nRet));\
}\
	continue;\
}\

char* CameraGetError(int nRet);
/** @} */
#endif  //_ITS_CAMERA_COMMON_H_
