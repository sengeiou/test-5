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
#ifndef _ITS_TTS_COMMON_H_
#define _ITS_TTS_COMMON_H_

#include "tct_common.h"
#include <tts.h>
#include <ttse.h>
#include <glib.h>
#include <glib-object.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <Ecore.h>

/** @addtogroup itc-tts
*  @ingroup itc
*  @{
*/
#define TIMEOUT_CB					5000
#define INPUT_TEXT					"1 2 3 4 5 6 7 8 9"
#define SLEEP_TIME					5
#define CONSTANT                    10
#define TIMEOUT						20000
#define API_NAMESPACE				"TTS_ITC"
#define SPEECH_SYNTHESIS_FEATURE	"http://tizen.org/feature/speech.synthesis"

/**********************************************************Golbal variables************************************************/
tts_h g_pstTts;
int g_nUixUttIdCmp;
int g_nUixUttId;
const char* g_pszUixLanguage;
tts_state_e g_eCurrent_state;
int g_eUixVoiceType;
bool g_bTtsCreation;
bool g_bTtsSupportedVoiceCallback;
bool g_bTtsStateChangedCallback;
bool g_bTtsDefaultVoiceChangedCallback;
bool g_bTtsErrorCallback;
bool g_bTtsUtteranceCompletedCallback;
bool g_bTtsUtteranceStartedCallback;
bool g_bFeatureSupported;
bool g_bFeatureMismatch;
bool g_bFeatureNotSupported;
GMainLoop *g_pMainLoop;
gboolean TimeoutFunction(gpointer data);

#define START_TEST {\
	FPRINTF("[Line : %d] [%s]  Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bFeatureMismatch )\
{\
	return 1;\
}\
	if ( g_bFeatureNotSupported )\
{\
	return 0;\
}\
	if ( !g_bTtsCreation )\
{\
	FPRINTF("[Line : %d] [%s] Precondition of tts create failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
}

#define START_TEST_TTSE {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bFeatureMismatch )\
{\
	return 1;\
}\
	if ( g_bFeatureNotSupported )\
{\
	return 0;\
}\
}

#define RUN_POLLING_LOOP {\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	nIotconTimeoutId = g_timeout_add(TIMEOUT_CB, TimeoutFunction, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nIotconTimeoutId);\
	g_pMainLoop = NULL;\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

/*******************************************************HELPER FUNCTIONS**************************************************/
char* TtsGetError(int nRet);
char* TtseGetError(int nRet);
void UixTtsPrintAPIErrorMSG(char *pszAPI, int nRet);
gboolean TtsTimeoutFunction(gpointer data);
void TtsWaitForAsync();
int TtsSetStateChangedCallBacks(tts_state_changed_cb StateChange);
void TtsUnSetStateChangedCallBacks(void);
int TtsSetUtteranceCallBacks(tts_utterance_started_cb StartCallBack, tts_utterance_completed_cb CompleteCallBack);
void TtsUnSetUtteranceCallBacks(void);
bool TtsPrepare(tts_state_changed_cb StateChange);
void TtsUnPrepare(void);
/** @} */
#endif  //_ITS_TTS_COMMON_H_
