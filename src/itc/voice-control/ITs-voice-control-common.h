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
#ifndef _ITS_VOICE_CONTROL_COMMON_H_
#define _ITS_VOICE_CONTROL_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <voice_control.h>
#include <voice_control_command.h>
#include <voice_control_common.h>
#include <glib.h>
#include <Ecore.h>


/** @addtogroup itc-voice-control
*  @ingroup itc
*  @{
*/

//Add test package related defines here
#define API_NAMESPACE			"VOICE_CONTROL_ITC"
#define MICROPHONEFEATURE		"http://tizen.org/feature/microphone"
#define SPEECHCONTROLFEATURE	"http://tizen.org/feature/speech.control"
#define VOICECOMMAND			"voice"
#define VOICECOMMANDNEW			"newvoice"

bool g_bIsVcFeatureSupported;
bool g_bIsVCEFeatureNotSupported;
bool g_bVCEFeatureMismatch;

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bVoiceControlStartup )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of voice-control failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
	else if ( g_bVoiceControlStartup == true && g_bIsVcFeatureSupported == false )\
	{\
		FPRINTF("[Line : %d][%s] Microphone/SpeechControl feature is not supported and api also returned not supported so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
}

#define START_TEST_VCE {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bVCEFeatureMismatch )\
	{\
		FPRINTF("[Line : %d][%s] Feature support as returned and error code as returned by vce_main() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
	else if ( g_bIsVCEFeatureNotSupported )\
	{\
		FPRINTF("[Line : %d][%s] voice-control engine feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
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

#define PRINT_RESULTNONE_CLEANUP(eCompare, eRetVal, API, Error, FreeResource) {\
	if ( eRetVal == eCompare )\
	{\
		if ( DEBUG )\
		{\
			FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
		}\
	}\
	else \
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, Error, eRetVal);\
		FreeResource;\
		return;\
	}\
}

#define PRINT_RESULTNONE(eCompare, eRetVal, API, Error) {\
	if ( eRetVal == eCompare )\
	{\
		if ( DEBUG )\
		{\
			FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
		}\
	}\
	else \
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, Error, eRetVal);\
		return;\
	}\
}

//Add test package related global variables here
bool g_bVoiceControlStartup;
bool g_bIsVcFeatureSupported;
vc_cmd_h g_arrhVcCommand[2];
vc_cmd_list_h g_hVcCommandList;
bool g_CallBackHit;

//Add CallBack Function declarations here
void StateChangedCallBack(vc_state_e previous, vc_state_e current, void* user_data);

//Add test package function declarations here
void IterateEcoreLoop(void);
char* VoiceControlGetError(int nRet);
bool CreateCommands(void);
bool DestroyCommands(void);
bool CreateCommandList(void);
bool DestroyCommandList(void);
bool PrepareVoiceControl(void);
bool UnPrepareVoiceControl(void);

/** @} */
#endif  //_ITS_VOICE_CONTROL_COMMON_H_
