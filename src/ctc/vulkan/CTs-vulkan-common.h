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
#ifndef _VULKAN_COMMON_H_
#define _VULKAN_COMMON_H_

#include "tct_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <vulkan/vulkan.h>
#include <SDL.h>

/** @addtogroup ctc-%{MODULE_NAME}
* @ingroup		ctc
* @{
*/

#define APP_SHORT_NAME "instance"
#define MAX_BLOCK_SIZE          	25
#define TIME_DELAY					3
#define MAX_FRAME_COUNT				500
#define API_NAMESPACE			"VULKAN_CTC"
bool g_bCheckStarup;


#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bCheckStarup )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of vulkan failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

char* VulkanGetError(int nRet);

/** @} */
#endif  //_VULKAN_COMMON_H_
