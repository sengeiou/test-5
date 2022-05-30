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
#ifndef _CTS_CAMERA_COMMON_H_
#define _CTS_CAMERA_COMMON_H_

#include "tct_common.h"
#include <camera.h>

/** @addtogroup ctc-camera
* @ingroup		ctc
* @{
*/

#define API_NAMESPACE				"CAMERA_CTC"
#define CAMERA_MAX_BLOCK_SIZE		20
#define CAMERA_MEMLOG				25
#define CAMERA_FEAUTRE				"http://tizen.org/feature/camera"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

char* CameraPixelFormat(int format);
char* CameraGetError(int nRet);

/** @} */ //end of ctc-camera

#endif  //_CTS_CAMERA_COMMON_H_