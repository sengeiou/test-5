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
#ifndef _ITS_STT_COMMON_H_
#define _ITS_STT_COMMON_H_

//Add test package related includes here
#include "tct_common.h"

#include <stt.h>
#include <stte.h>
#include <app.h>
#include <system_info.h>

#include <glib.h>
#include <glib-object.h>
#include <time.h>

/** @addtogroup itc-stt
*  @ingroup itc
*  @{
*/
#define TIMEOUT_CB					5000
#define API_NAMESPACE				"STT_ITC"
#define PATH_LEN					1024
#define LANGUAGE_LEN				256
#define ENGINE_LEN					256
#define START_SOUND					"start_sound.wav"
#define STOP_SOUND					"stop_sound.wav"
#define TIME_LIMIT					20

#define MICROPHONE_FEATURE			"http://tizen.org/feature/microphone"
#define SPEECH_RECOGNITION_FEATURE	"http://tizen.org/feature/speech.recognition"

bool g_bFeatureSupported;
bool g_bFeatureMismatch;
bool g_bFeatureNotSupported;

stt_h g_hStt;
bool g_bSttCreation;
bool g_bFeatureSupported;

bool g_bDefaultLanguageChangedCallbackOccurred;
char* g_szPreviousLanguage;
char* g_szCurrentLanguage;

bool g_bErrorCallbackOccurred;
stt_error_e g_nErrorReason;

bool g_bResultCallbackOccurred;
stt_result_event_e g_nResultEvent;

bool g_bResultTimeCallbackOccurred;
stt_result_time_event_e g_nResultTimeEvent;

bool g_bStateCallbackOccurred;
stt_state_e g_nPreviousState;
stt_state_e g_nCurrentState;

bool g_bSupportedEngineCallbackOccured;

bool g_bSupportedLanguageCallbackOccured;
GMainLoop *g_pMainLoop;
gboolean TimeoutFunction(gpointer data);

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bFeatureMismatch )\
{\
	return 1;\
}\
	if ( g_bFeatureNotSupported )\
{\
	return 0;\
}\
	if ( !g_bSttCreation )\
{\
	FPRINTF("[Line : %d][%s] Precondition of STT handle creation failed. So leaving test", __LINE__, API_NAMESPACE);\
	return 1;\
}\
}
#define START_TEST_STTE {\
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

#define RUN_POLLING_LOOP {\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	nIotconTimeoutId = g_timeout_add(TIMEOUT_CB, TimeoutFunction, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nIotconTimeoutId);\
	g_pMainLoop = NULL;\
}

/******************************************************* HELPER FUNCTIONS**************************************************/

// Maps stt_error_e enums to string values
char* SttGetError(stt_error_e nError);

// Maps stte_error_e enums to string values
char* StteGetError(stte_error_e nError);

// Maps stt_option_silence_detection_e enums to string values
char* SttGetOptionForSilenceDetection(stt_option_silence_detection_e nOption);

// Maps stt_result_event_e enums to string values
char* SttGetResultEvent(stt_result_event_e nEvent);

// Maps stt_result_time_event_e enums to string values
char* SttGetResultTimeEvent(stt_result_time_event_e nEvent);

// Maps stt_state_e enums to string values
char* SttGetState(stt_state_e nState);

// This function outputs the application data path
bool SttGetDataPath(char* pPath);

// This function appends the input string to app data path and outputs the final resultant path
bool SttAppendToAppDataPath(char* pInputPath, char* pFinalPath);

/** @} */
#endif  //_ITS_STT_COMMON_H_
