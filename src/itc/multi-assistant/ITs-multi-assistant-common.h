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

#ifndef _MULTI_ASSISTANT_COMMON_H_
#define _MULTI_ASSISTANT_H_

#include <stdio.h>
#include <string.h>
#include "tct_common.h"
#include <bundle.h>
#include <multi_assistant.h>
#include <multi_assistant_common.h>

/** @addtogroup itc-dlog
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE					"MULTI_ASSISTANT_ITC"
#define FEATURE_MULTI_ASSISTANT				"http://tizen.org/feature/multi_assistant"
#define FEATURE_MICROPHONE				"http://tizen.org/feature/microphone"
#define TIME_LIMIT					20
static bool g_CallBackHit = false;
static bool g_bMultiAssistant = false;
static bool g_bMicrophone = false;
static bool g_bIsFeatureMismatched = false;
static bool g_bFeatureNotSupported = false;
static bool g_bMAInit = false;
static ma_state_e g_nCurrentState = MA_STATE_NONE;
static ma_active_state_e g_nCurrentActiveState = MA_ACTIVE_STATE_INACTIVE;
static ma_active_state_e g_nPreviousActiveState = MA_ACTIVE_STATE_INACTIVE;
static char *gpszWakeupCmd = NULL;
static ma_assistant_info_h g_hAssistantInfoHandle = NULL;
static bool g_bCallBackHitEx = false;

void MaLanguageChangedCb(const char* previous, const char* current, void* user_data);
void MaAudioStreamingCb(ma_audio_streaming_event_e event, char* buffer, int len, void* user_data);
void MaStateChangedCb(ma_state_e previous, ma_state_e current, void* user_data);
void MaErrorCb(ma_error_e reason, void* user_data);
void MaServiceStateChangedCb(ma_service_state_e previous, ma_service_state_e current, void* user_data);
void MaVoiceKeyStatusChangedCb(ma_voice_key_status_e status, void* user_data);
char *MaGetError(int error);


#define START_TEST {\
	if(g_bFeatureNotSupported)\
	{\
		FPRINTF("[Line:%d][%s] Feature Multi-Assistant not supported\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
\
	if( g_bIsFeatureMismatched )\
	{\
		FPRINTF("[Line:%d][%s] Feature Mismatch Error\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
\
	if ( !g_bMAInit )\
	{\
		FPRINTF("[Line : %d] [API_NAMESPACE] Precondition of multi-assistant failed\\n", __LINE__);\
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

#define WAIT_FOR_CALLBACK(state) {\
	time_t time1 = time(NULL);\
	while(state != g_nCurrentState)\
	{\
		time_t time2 = time(NULL);\
		int diff = (int)difftime(time2, time1);\
		if ( diff > TIME_LIMIT )\
		{\
			break;\
		}\
		ecore_main_loop_iterate();\
	}\
}\

/** @} */
#endif  //_ITS_MULTI_ASSISTANT_COMMON_H_
