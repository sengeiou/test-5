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
#ifndef _ITS_VOICE_CONTROL_ELM_COMMON_H_
#define _ITS_VOICE_CONTROL_ELM_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <voice_control_elm.h>
#include <glib.h>
#include <Ecore.h>

/** @addtogroup itc-voice-control-elm
*  @ingroup itc
*  @{
*/

//Add test package related defines here
#define API_NAMESPACE			"VOICE_CONTROL_ELM_ITC"
#define MICROPHONEFEATURE		"http://tizen.org/feature/microphone"
#define SPEECHCONTROLFEATURE	"http://tizen.org/feature/speech.control"
#define TESTSTRING				"test"
#define PACKAGE 				"VOICE_CONTROL_ELM_ITC"
#define PATH_LEN				1024
#define COMMANDHINT				"TestHint"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bVoiceControlStartup )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of voice-control-elm failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
	else if ( g_bVoiceControlStartup == true && g_bIsVcFeatureSupported == false )\
	{\
		FPRINTF("[Line : %d][%s] Microphone/SpeechControl feature is not supported and api also returned not supported so leaving test\\n", __LINE__, API_NAMESPACE);\
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
bool g_CallBackHit;
Evas_Object *g_pEvasWindow;
Evas_Object *g_pEvasButton;
Evas_Object *g_pGenList;
Elm_Object_Item *g_pEvasItem;
char g_szWidget[PATH_LEN];
char g_szAction[PATH_LEN];
char g_szCommand[PATH_LEN];
vc_elm_h g_hVcElm;

//Add callback function declarations here
bool WidgetSupportedCallback(const char* widget, void* user_data);
bool ActionSupportedCallback(const char* action, void* user_data);

//Add test package function declarations here
void IterateEcoreLoop(void);
char* VoiceControlElmGetError(int nRet);
void WinDel(void *data, Evas_Object *obj, void *event);
bool CreateEvasWindow(void);
void DeleteEvasWindow(void);
bool GetWidgetName(void);
bool GetActionName(void);
bool GetCommandName(void);
bool CreateVcElmObject(void);
bool DeleteVcElmObject(void);
bool CreateVcElmObjectWithCommand(void);
bool DeleteVcElmObjectWithCommand(void);
bool CreateVcElmObjectWithCommandHint(void);
bool DeleteVcElmObjectWithCommandHint(void);

/** @} */
#endif  //_ITS_VOICE_CONTROL_ELM_COMMON_H_
