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
#include "ITs-tts-common.h"
#include <Ecore.h>

/** @addtogroup itc-tts
*  @ingroup itc
*  @{
*/

static bool g_CallBackValue = true;
bool g_CallBackHit = false;

static bool TtsIsStateChanged(tts_state_e state, int sleep_time)
{
	int max_count = sleep_time * CONSTANT;
	int count = 0;
	while (max_count > count && state != g_eCurrent_state) {
		ecore_main_loop_iterate();
		usleep(TIMEOUT);
		count++;
	}

	if (state != g_eCurrent_state) {
		return false;
	}

	return true;
}

/**
* @function 		ITs_tts_startup
* @description	 	Called before each test, created tts handle
* @parameter		NA
* @return 			NA
*/
void ITs_tts_startup(void)
{

	g_bTtsCreation = false;
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT start-up: ITs_TTS_p\\n", __LINE__, API_NAMESPACE);
#endif
	g_bFeatureSupported = true;
	g_bFeatureMismatch = false;
	g_bFeatureNotSupported = false;

	g_bFeatureSupported = TCTCheckSystemInfoFeatureSupported(SPEECH_SYNTHESIS_FEATURE, API_NAMESPACE);
	int nRet = tts_create(&g_pstTts);

	if ( !g_bFeatureSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] tts_create returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, TtsGetError(nRet));
			g_bFeatureMismatch = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] tts_create correctly returned TIZEN_ERROR_NOT_SUPPORTED for unsupported feature\\n", __LINE__, API_NAMESPACE);
			g_bFeatureNotSupported = true;
		}
		return;
	}

	usleep(20000);
	if ( nRet != TTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to create tts, error returned = %s \\n", __LINE__, API_NAMESPACE, TtsGetError(nRet));
	}
	else
	{
		FPRINTF("[Line : %d][%s] tts created successfully \\n", __LINE__, API_NAMESPACE);
		g_bTtsCreation = true;
	}
	return;
}
/**
* @function 		ITs_tts_cleanup
* @description	 	Called after each test, destroys tts handle
* @parameter		NA
* @return 			NA
*/
void ITs_tts_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_TTS_p\\n", __LINE__, API_NAMESPACE);
#endif

	if ( g_bTtsCreation )
	{
		int nRet = tts_destroy(g_pstTts);
		usleep(20000);
		if ( nRet != TTS_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] tts_destroy failed, error returned = %s \\n", __LINE__, API_NAMESPACE, TtsGetError(nRet));
		}
	}

	sleep(SLEEP_TIME);
	return;
}

/***************************************************************CallBack Start************************************/

/**
* @function            TtsSupportedVoiceCallback
* @description         Callback function which is invoked once for each supported voices
* @parameter[in]		tts, the error type
* 			[in]		language
* 			[in]		voice_type
* 			[in]		user_data	The user data passed
* @return 				true or false
*/
static bool TtsSupportedVoiceCallback(tts_h tts, const char *language, int voice_type, void *user_data)
{
	g_bTtsSupportedVoiceCallback = true;
	g_CallBackValue = true;
	if(tts == NULL || language == NULL || voice_type < 0)
	{
		g_CallBackValue = false;
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] Language: %s, Voice type: %d \\n", __LINE__, API_NAMESPACE, language, voice_type);
#endif
	return false;
}

/**
* @function 					TtsUtteranceStartedCallback
* @description 					callback is called by the tts_foreach_supported_voices API
* @parameter[in]				tts, the tts handler
* 			[in]				previous, previous state
* 			[in]				current, current state
* 			[in]				user_data	The user data passed
* @return 						true or false
*/
static void TtsUtteranceStartedCallback(tts_h tts, int utt_id, void *user_data)
{
	g_bTtsUtteranceStartedCallback = true;
	g_nUixUttId = utt_id;
#if DEBUG
	FPRINTF("[Line : %d][%s] func_tts_utterance_started_cb is called. \\n", __LINE__, API_NAMESPACE);
	FPRINTF("[Line : %d][%s] utterance ID is: %d \\n", __LINE__, API_NAMESPACE, utt_id);
#endif
	return;
}

/**
* @function 					TtsUtteranceCompletedCallback
* @description 					callback is called by the  tts_set_utterance_completed_cb() API
* @parameter[in]				tts, the tts handler
* 			[in]				previous, previous state
* 			[in]				current, current state
* 			[in]				user_data	The user data passed
* @return 						true or false
*/

static void TtsUtteranceCompletedCallback(tts_h tts, int utt_id, void *user_data)
{
	g_bTtsUtteranceCompletedCallback = true;
	g_nUixUttIdCmp = utt_id;
#if DEBUG
	FPRINTF("[Line : %d][%s] func_tts_utterance_completed_cb is called. \\n", __LINE__, API_NAMESPACE);
	FPRINTF("[Line : %d][%s] utterance ID: %d, is completed. \\n", __LINE__, API_NAMESPACE, utt_id);
#endif

	return;
}

/**
* @function 					func_tts_state_changed_cb
* @description 					callback is called by the tts_foreach_supported_voices API
* @parameter[in]				tts, the tts handler
* 			[in]				previous, previous state
* 			[in]				current, current state
* 			[in]				user_data	The user data passed
* @return 						true or false
*/
static void TtsStateChangedCallback(tts_h tts, tts_state_e previous, tts_state_e current, void *user_data)
{
	g_bTtsStateChangedCallback = true;
	g_CallBackValue = true;
	g_eCurrent_state = current;
	if(tts == NULL || (previous < TTS_STATE_CREATED || previous > TTS_STATE_PAUSED) || (current < TTS_STATE_CREATED || current > TTS_STATE_PAUSED))
	{
		g_CallBackValue = false;
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] func_tts_state_changed_cb is called. \\n", __LINE__, API_NAMESPACE);
	FPRINTF("[Line : %d][%s] previous state is: %d, current state is: %d \\n", __LINE__, API_NAMESPACE, previous, current);
#endif

	return;
}

/**
* @function 					func_tts_set_error_cb
* @description 					callback is called by the tts_foreach_supported_voices API
* @parameter[in]				tts, the error type
* 			[in]				language
* 			[in]				voice_type
* 			[in]				user_data	The user data passed
* @return 						true or false
*/
static void TtsErrorCallback(tts_h tts, int utt_id, tts_error_e reason, void *user_data)
{
	g_bTtsErrorCallback = true;
#if DEBUG
	FPRINTF("[Line : %d][%s] func_tts_set_error_cb callback is called. \\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 					func_tts_default_voice_change_cb
* @description 					callback is called by the tts_set_default_voice_changed_cb API
* @parameter[in] 				tts The TTS handle
*			[in] 				previous_language The previous language
*			[in] 				previous_voice_type The previous voice type
*			[in] 				current_language The current language
*			[in] 				current_voice_type The current voice type
*			[in] 				user_data The user data passed from the callback registration function

*/
static void TtsDefaultVoiceChangedCallback(tts_h tts, const char *previous_language, int previous_voice_type, const char *current_language, int current_voice_type, void *user_data)
{
	g_bTtsDefaultVoiceChangedCallback = true;
	g_pszUixLanguage = current_language;
	g_eUixVoiceType  = current_voice_type;
#if DEBUG
	FPRINTF("[Line : %d][%s] func_tts_default_voice_change_cb callback is called. \\n", __LINE__, API_NAMESPACE);
	FPRINTF("[Line : %d][%s] Current Language: %s , Voice type:%d \\n", __LINE__, API_NAMESPACE,current_language, current_voice_type);
#endif
	return;
}

static bool TtsEngineChangedcallback(tts_h tts, const char* engine_id, const char* language, int voice_type, bool need_credential, void* user_data)
{
	g_CallBackValue = true;
#if DEBUG
	FPRINTF("[Line : %d][%s] TtsEngineChangedcallback callback is called. \\n", __LINE__, API_NAMESPACE);
#endif
	return true;
}


/**
* @function 		ttsErrorCallback
* @description	 	Called when an error occurs
* @parameter		[in] tts The STT handle
*					[in] reason The error type (e.g. TTS_ERROR_OUT_OF_NETWORK, TTS_ERROR_IO_ERROR)
*					[in] user_data The user data passed from the callback registration function
* @precondition	An application registers this callback using stt_set_error_cb() to detect error
* @return 			None
*/
void ttsErrorCallback(tts_h stt, tts_error_e reason, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Reached sttErrorCallback\\n", __LINE__, API_NAMESPACE);
#endif

	g_CallBackHit = true;
	
	if(stt == NULL)
	{
		FPRINTF("[Line : %d][%s] Handle is NULL in callback function\\n", __LINE__, API_NAMESPACE);
	}
	
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}	
	
}
/**
* @function 					TtsScreenReaderChangedCallback
* @description 					callback is called when the option of screen reader is changed.
* @parameter[in]				tts, the tts handler
* 			[in]				engine_id, previous language
* 			[in]				voice_type, need_credential
* 			[in]				user_data	The user data passed
* @return 						true or false
*/
static void TtsScreenReaderChangedCallback(tts_h tts, const char* engine_id, const char* language, int voice_type, bool need_credential, void* user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TtsScreenReaderChangedCallback callback is called. \\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/***************************************************************CallBack End************************************/

/** @addtogroup itc-tts-testcases
*  @brief 		Integration testcases for module tts
*  @ingroup 	itc-tts
*  @{
*/

//& purpose: create and destroy tts
//& type : auto
/**
* @testcase 				ITc_tts_create_destroy_p
* @since_tizen 				2.3
* @author					SRID(anshul1.jain)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    create and destroy tts
* @scenario					Create tts\n
* 							destroy tts
* @apicovered				tts_create, tts_destroy
* @passcase					When it can create and destroy tts.
* @failcase					When it can not create and destroy tts.
* @precondition				NA
* @postcondition			NA
*/
int ITc_tts_create_destroy_p(void)
{
	START_TEST;

	int nRet = tts_destroy(g_pstTts);
	usleep(20000);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_destroy", TtsGetError(nRet));

	// Target API
	nRet =  tts_create(&g_pstTts);
	usleep(20000);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_create", TtsGetError(nRet));
	CHECK_HANDLE(g_pstTts, "tts_create");

	// Target API
	nRet = tts_destroy(g_pstTts);
	usleep(20000);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_destroy", TtsGetError(nRet), tts_create(&g_pstTts));

	tts_create(&g_pstTts);
	usleep(20000);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_create", TtsGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: To set and get the tts mode.
/**
* @testcase 				ITc_tts_set_get_mode_p
* @since_tizen 				2.3
* @author					SRID(anshul1.jain)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @scenario					create a tts handler\n
* 							set different mode\n
* 							get that mode\n
* 							match those values\n
* 							destroy that handler
* @apicovered				tts_set_mode, tts_get_mode
* @passcase					if API is successful
* @failcase					if API is not successful
* @precondition				The state should be TTS_STATE_CREATED.
* @postcondition			NA
*/
int ITc_tts_set_get_mode_p(void)
{
	START_TEST;

	tts_mode_e eGetMode;

	//Target API
	int nRet = tts_set_mode(g_pstTts, TTS_MODE_NOTIFICATION);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_set_mode", TtsGetError(nRet));

	//Target API
	nRet = tts_get_mode(g_pstTts, &eGetMode);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_get_mode", TtsGetError(nRet));
	if ( eGetMode != TTS_MODE_NOTIFICATION )
	{
		FPRINTF("[Line : %d][%s] tts_set_get_mode mismatched, error returned = %s \\n", __LINE__, API_NAMESPACE, TtsGetError(nRet));
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: To get the dafault voice
/**
* @testcase 				ITc_tts_get_default_voice_p
* @since_tizen 				2.3
* @author            		SRID(anshul1.jain)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @scenario					create a tts handler\n
* 							get the default voice set by the user\n
* 							destroy that handler
* @apicovered				tts_get_default_voice
* @passcase					if API is successful
* @failcase					if API is not successful
* @precondition				NA
* @postcondition			NA
*/
int ITc_tts_get_default_voice_p(void)
{
	START_TEST;

	int eGetvoicetype;
	char* pszGetLanguage = NULL;

	//Target API
	int nRet =  tts_get_default_voice(g_pstTts, &pszGetLanguage, &eGetvoicetype);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_get_default_voice", TtsGetError(nRet));
	if ( pszGetLanguage == NULL )
	{
		FPRINTF("[Line : %d][%s] tts_get_default_voice API fails because get language is NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	FREE_MEMORY(pszGetLanguage);
	return 0;
}

//& type: auto
//& purpose: To get the current state a tts handler
/**
* @testcase 				ITc_tts_get_state_p
* @since_tizen 				2.3
* @author            		SRID(anshul1.jain)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @scenario					create a tts handler\n
* 							get the state of the tts\n
* 							match the state and check that it is in TTS_STATE_CREATED state\n
* 							destroy that handler
* @apicovered				tts_get_state
* @passcase					if API is successful
* @failcase					if API is not successful
* @precondition				NA
* @postcondition			NA
*/
int ITc_tts_get_state_p(void)
{
	START_TEST;

	tts_state_e state;

	//Target API
	int nRet =  tts_get_state(g_pstTts, &state);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_get_state", TtsGetError(nRet));
	if ( state != TTS_STATE_CREATED )
	{
		FPRINTF("[Line : %d][%s] get state is not matched \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Prepare and unprepare the tts.
//& type: auto
/*
* @testcase 				ITc_tts_prepare_unprepare_p
* @since_tizen 				2.3
* @author					SRID(anshul1.jain)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				to prepare and unprepare tts
* @scenario					Create audio tts\n
*							Prepares tts\n
*							Destroy tts
* @apicovered 				tts_prepare, tts_unprepare
* @passcase					If tts gets prepared successfully
* @failcase 				If tts does not get prepared successfully
* @precondition				The tts state should be TTS_STATE_CREATED by tts_create(), tts_create() or tts_unprepare().
* @postcondition			The tts state will be TTS_STATE_READY. If tts handle is created by tts_create_videotts(), camera state will be changed to CAMERA_STATE_PREVIEW.
*/
int ITc_tts_prepare_unprepare_p(void)
{
	START_TEST;

	if ( TtsSetStateChangedCallBacks(TtsStateChangedCallback) == 1 )
	{
		return 1;
	}

	//Target API
	int nRet = tts_prepare(g_pstTts);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_prepare", TtsGetError(nRet),TtsUnSetStateChangedCallBacks());

	while(TTS_STATE_READY != g_eCurrent_state){
		ecore_main_loop_iterate();
	}

	if ( !g_bTtsStateChangedCallback )
	{
		FPRINTF("[Line : %d][%s] tts_set_state_changed_cb failed, error returned = callback not invoked\\n \\n", __LINE__, API_NAMESPACE);
		tts_unprepare(g_pstTts);
		TtsUnSetStateChangedCallBacks();
		return 1;
	}
	if(!g_CallBackValue)
	{
		FPRINTF("[Line : %d][%s] Callback input values are invalid \n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bTtsStateChangedCallback = false;
	//Target API
	nRet = tts_unprepare(g_pstTts);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_unprepare", TtsGetError(nRet), TtsUnSetStateChangedCallBacks());

	if ( !g_bTtsStateChangedCallback )
	{
		FPRINTF("[Line : %d][%s] tts_set_state_changed_cb failed, error returned = callback not invoked\\n \\n", __LINE__, API_NAMESPACE);
		TtsUnSetStateChangedCallBacks();
		return 1;
	}
	if(!g_CallBackValue)
	{
		FPRINTF("[Line : %d][%s] Callback input values are invalid \n", __LINE__, API_NAMESPACE);
		return 1;
	}

	TtsUnSetStateChangedCallBacks();
	return 0;
}
//& purpose: Connects the daemon synchronously.
//& type: auto
/*
* @testcase 				ITc_tts_prepare_sync_p
* @since_tizen 				7.0
* @author					SRID(manu.tiwari)
* @reviewer         		SRID(shobhit.v)
* @type 					auto
* @description				Connects the daemon synchronously.
* @scenario					Prepares tts\n
*							Destroy tts
* @apicovered 				tts_prepare_sync, tts_unprepare
* @passcase					If tts_prepare_sync pass
* @failcase 				If tts_prepare_sync failes
* @precondition				The tts state should be TTS_STATE_CREATED by tts_create(), tts_create() or tts_unprepare().
* @postcondition			The tts state will be TTS_STATE_READY. If tts handle is created by tts_create_videotts(), camera state will be changed to CAMERA_STATE_PREVIEW.
*/
int ITc_tts_prepare_sync_p(void)
{
	START_TEST;

	if ( TtsSetStateChangedCallBacks(TtsStateChangedCallback) == 1 )
	{
		return 1;
	}

	//Target API
	int nRet = tts_prepare_sync(g_pstTts);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_prepare_sync", TtsGetError(nRet),TtsUnSetStateChangedCallBacks());

	if ( TtsIsStateChanged(TTS_STATE_READY, SLEEP_TIME) == false ){
		FPRINTF("[Line : %d][%s] TtsIsStateChanged failed \\n", __LINE__, API_NAMESPACE);
		tts_unprepare(g_pstTts);
		TtsUnSetStateChangedCallBacks();
	}

	if ( !g_bTtsStateChangedCallback )
	{
		FPRINTF("[Line : %d][%s] tts_set_state_changed_cb failed, error returned = callback not invoked\\n \\n", __LINE__, API_NAMESPACE);
		tts_unprepare(g_pstTts);
		TtsUnSetStateChangedCallBacks();
		return 1;
	}
	if(!g_CallBackValue)
	{
		FPRINTF("[Line : %d][%s] Callback input values are invalid \n", __LINE__, API_NAMESPACE);
		tts_unprepare(g_pstTts);
		TtsUnSetStateChangedCallBacks();
		return 1;
	}

	g_bTtsStateChangedCallback = false;

	nRet = tts_unprepare(g_pstTts);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_unprepare", TtsGetError(nRet), TtsUnSetStateChangedCallBacks());

	if ( !g_bTtsStateChangedCallback )
	{
		FPRINTF("[Line : %d][%s] tts_set_state_changed_cb failed, error returned = callback not invoked\\n \\n", __LINE__, API_NAMESPACE);
		TtsUnSetStateChangedCallBacks();
		return 1;
	}
	if(!g_CallBackValue)
	{
		FPRINTF("[Line : %d][%s] Callback input values are invalid \n", __LINE__, API_NAMESPACE);
		TtsUnSetStateChangedCallBacks();
		return 1;
	}

	TtsUnSetStateChangedCallBacks();
	return 0;
}
//& type: auto
//& purpose: To register a callback function for state change
/**
* @testcase 				ITc_tts_setunset_state_changed_cb_p
* @since_tizen 				2.3
* @author					SRID(anshul1.jain)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @scenario					create a tts handler\n
* 							register a state change callback function\n
* 							prepare for the tts\n
* 							check the state changed callback\n
* 							unprepare the tts\n
* 							unregister the state change callback\n
* 							destroy that handler
* @apicovered				tts_prepare, tts_unprepare, tts_set_state_changed_cb, tts_unset_state_changed_cb
* @passcase					if API is successful
* @failcase					if API is not successful
* @precondition
* @postcondition			NA
*/
int ITc_tts_setunset_state_changed_cb_p(void)
{
	START_TEST;

	// Target API
	int nRet =  tts_set_state_changed_cb(g_pstTts, TtsStateChangedCallback, NULL);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_set_state_changed_cb", TtsGetError(nRet));

	g_bTtsStateChangedCallback = false;
	nRet = tts_prepare(g_pstTts);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_prepare", TtsGetError(nRet), tts_unset_state_changed_cb(g_pstTts));

	while(TTS_STATE_READY != g_eCurrent_state){
		ecore_main_loop_iterate();
	}

	if ( !g_bTtsStateChangedCallback )
	{
		FPRINTF("[Line : %d][%s] tts_state_changed_cb failed, error returned = callback not invoked, time out  \\n", __LINE__, API_NAMESPACE);
		tts_unset_state_changed_cb(g_pstTts);
		return 1;
	}
	if(!g_CallBackValue)
	{
		FPRINTF("[Line : %d][%s] Callback input values are invalid \n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bTtsStateChangedCallback = false ;
	nRet = tts_unprepare(g_pstTts);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_unprepare", TtsGetError(nRet), tts_unset_state_changed_cb(g_pstTts));

	if ( !g_bTtsStateChangedCallback )
	{
		FPRINTF("[Line : %d][%s] tts_state_changed_cb failed, error returned = callback not invoked, time out  \\n", __LINE__, API_NAMESPACE);
		tts_unset_state_changed_cb(g_pstTts);
		return 1;
	}
	if(!g_CallBackValue)
	{
		FPRINTF("[Line : %d][%s] Callback input values are invalid \n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// Target API
	nRet =  tts_unset_state_changed_cb(g_pstTts);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_unset_state_changed_cb", TtsGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: to get max text count of the current engine
/**
* @testcase 				ITc_tts_get_max_text_size_p
* @since_tizen 				2.3
* @author					SRID(anshul1.jain)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @scenario					create a tts handler and prepare for the tts\n
* 							add text to the queue\n
* 							get the max text count of the current engine\n
* 							unprepare the tts\n
* 							destroy that handler
* @apicovered				tts_get_max_text_size
* @passcase					if API is successful
* @failcase					if API is not successful
* @precondition
* @postcondition			NA
*/
int ITc_tts_get_max_text_size_p(void)
{
	START_TEST;

	unsigned int nGetTextCount = 0;

	if ( TtsPrepare(TtsStateChangedCallback) == false )
	{
		return 1;
	}

	while(TTS_STATE_READY != g_eCurrent_state){
		ecore_main_loop_iterate();
	}

	// Target API
	int nRet =  tts_get_max_text_size(g_pstTts, &nGetTextCount);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_get_max_text_size", TtsGetError(nRet), TtsUnPrepare());
	if ( nGetTextCount <= 0 )
	{
		FPRINTF("[Line : %d][%s] tts_get_max_text_size API fails because get count does not change \\n", __LINE__, API_NAMESPACE);
		TtsUnPrepare();
		return 1;
	}
	TtsUnPrepare();
	return 0;
}

//& type: auto
//& purpose: to get max text count of the current engine
/**
* @testcase 				ITc_tts_get_speed_range_p
* @since_tizen 				2.3
* @author					SRID(anshul1.jain)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @scenario					create a tts handler and prepare for the tts\n
* 							get the max text count of the current engine\n
* 							unprepare the tts\n
* 							destroy that handler
* @apicovered				tts_unprepare , tts_get_speed_range
* @passcase					if API is successful
* @failcase					if API is not successful
* @precondition
* @postcondition			NA
*/
int ITc_tts_get_speed_range_p(void)
{
	START_TEST;

	int nMin =-1;
	int nNormal =-1;
	int nMax =-1;

	// Target API
	int nRet =  tts_get_speed_range(g_pstTts, &nMin, &nNormal, &nMax);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_get_speed_range", TtsGetError(nRet), tts_unprepare(g_pstTts));
	if ( nMin < 0 || nNormal < 0 || nMax < 0 )
	{
		FPRINTF("[Line : %d][%s] tts_get_speed_range API fails because nMin or nNormal or nMax does not change \\n", __LINE__, API_NAMESPACE);
		TtsUnPrepare();
		return 1;
	}
	TtsUnPrepare();
	return 0;
}

//& purpose: play playback
//& type : auto
/**
* @testcase 				ITc_tts_add_test_play_p
* @since_tizen 				2.3
* @author					SRID(anshul1.jain)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    start playback
* @scenario					Initialize tts handle\n
* 							play tts\n
* 							destroy the handler
* @apicovered				tts_add_text, tts_play, tts_get_default_voice, tts_stop
* @passcase					When API pass
* @failcase					When API fails
* @precondition				the tts state should be TTS_STATE_PLAYING
* @postcondition			NA
*/
int ITc_tts_add_text_play_p(void)
{
	START_TEST;

	int nGetUtteranceId;
	int eGetvoicetype;
	char* pszGetLanguage = NULL;

	if ( TtsSetUtteranceCallBacks(TtsUtteranceStartedCallback, TtsUtteranceCompletedCallback) == 1 )
	{
		return 1;
	}

	if ( TtsPrepare(TtsStateChangedCallback) == false )
	{
		TtsUnSetUtteranceCallBacks();
		return 1;
	}

	while(TTS_STATE_READY != g_eCurrent_state){
		ecore_main_loop_iterate();
	}

	int nRet = tts_get_default_voice(g_pstTts, &pszGetLanguage, &eGetvoicetype);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_get_default_voice", TtsGetError(nRet), TtsUnPrepare();TtsUnSetUtteranceCallBacks());

	// Target API
	nRet = tts_add_text(g_pstTts, INPUT_TEXT, pszGetLanguage, eGetvoicetype, TTS_SPEED_AUTO , &nGetUtteranceId);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_add_text", TtsGetError(nRet), TtsUnPrepare();TtsUnSetUtteranceCallBacks());

	g_bTtsUtteranceStartedCallback = false;
	g_bTtsUtteranceCompletedCallback = false;

	// Target API
	nRet = tts_play(g_pstTts);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_play", TtsGetError(nRet), TtsUnPrepare();TtsUnSetUtteranceCallBacks());

	while(TTS_STATE_PLAYING != g_eCurrent_state){
		ecore_main_loop_iterate();
	}

	while(true != g_bTtsUtteranceCompletedCallback){
		ecore_main_loop_iterate();
	}

	nRet = tts_stop(g_pstTts);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_stop", TtsGetError(nRet), TtsUnPrepare();TtsUnSetUtteranceCallBacks());

	if ( (g_bTtsUtteranceStartedCallback == false) || (g_bTtsUtteranceCompletedCallback == false) )
	{
		FPRINTF("[Line : %d][%s] tts_play API fails with return value: %d, error code is: CallBack not invoked \\n", __LINE__, API_NAMESPACE, nRet);
		TtsUnPrepare();
		TtsUnSetUtteranceCallBacks();
		return 1;
	}

	TtsUnPrepare();
	TtsUnSetUtteranceCallBacks();
	return 0;
}

//& purpose: pause stop playback
//& type : auto
/**
* @testcase 				ITc_tts_pause_stop_p
* @since_tizen 				2.3
* @author					SRID(anshul1.jain)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    pause stop playback
* @scenario					Initialize tts handle\n
* 							pause tts\n
*							stop tts\n
* 							destroy the handler
* @apicovered				tts_pause, tts_stop, tts_get_default_voice, tts_add_text, tts_play
* @passcase					When API pass
* @failcase					When API fails
* @precondition				the tts state should be TTS_STATE_READY
* @postcondition			NA
*/
int ITc_tts_pause_stop_p(void)
{
	START_TEST;

	int nGetUtteranceId;
	int eGetvoicetype;
	char* pszGetLanguage = NULL;

	if ( TtsSetUtteranceCallBacks(TtsUtteranceStartedCallback, TtsUtteranceCompletedCallback) == 1 )
	{
		return 1;
	}

	if ( TtsPrepare(TtsStateChangedCallback) == false )
	{
		TtsUnSetUtteranceCallBacks();
		return 1;
	}

	while(TTS_STATE_READY != g_eCurrent_state){
		ecore_main_loop_iterate();
	}

	if ( !g_bTtsStateChangedCallback )
	{
		FPRINTF("[Line : %d][%s] tts_set_state_changed_cb failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		tts_unprepare(g_pstTts);
		TtsUnSetStateChangedCallBacks();
		return 1;
	}

	int nRet = tts_get_default_voice(g_pstTts, &pszGetLanguage, &eGetvoicetype);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_get_default_voice", TtsGetError(nRet), TtsUnPrepare();TtsUnSetUtteranceCallBacks());

	nRet = tts_add_text(g_pstTts, INPUT_TEXT, pszGetLanguage, eGetvoicetype, TTS_SPEED_AUTO , &nGetUtteranceId);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_add_text", TtsGetError(nRet), TtsUnPrepare();TtsUnSetUtteranceCallBacks());

	g_bTtsUtteranceStartedCallback = false;
	g_bTtsUtteranceCompletedCallback = false;

	nRet = tts_play(g_pstTts);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_play", TtsGetError(nRet));

	while(TTS_STATE_PLAYING != g_eCurrent_state){
		ecore_main_loop_iterate();
	}

	// Target API
	nRet = tts_pause(g_pstTts);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_pause", TtsGetError(nRet), TtsUnPrepare();TtsUnSetUtteranceCallBacks());

	while(TTS_STATE_PAUSED != g_eCurrent_state){
		ecore_main_loop_iterate();
	}

	if ( g_bTtsUtteranceCompletedCallback == true )
	{
		FPRINTF("[Line : %d][%s] tts_pause API fails with return value: %d, error code is: CallBack was invoked even after pause\\n", __LINE__, API_NAMESPACE, nRet);
		TtsUnPrepare();
		TtsUnSetUtteranceCallBacks();
		return 1;
	}

	// Target API
	nRet = tts_stop(g_pstTts);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_stop", TtsGetError(nRet), TtsUnPrepare();TtsUnSetUtteranceCallBacks());

	while(TTS_STATE_READY != g_eCurrent_state){
		ecore_main_loop_iterate();
	}

	TtsUnPrepare();
	TtsUnSetUtteranceCallBacks();
	return 0;
}

//& type: auto
//& purpose: To register a callback function to detect utterance started and completed
/**
* @testcase 				ITc_tts_setunset_utterance_started_completed_cb_p
* @since_tizen 				2.3
* @author					SRID(anshul1.jain)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @scenario					create a tts handler and register all the callbacks\n
* 							prepare the tts\n
* 							get the dafult language and voice type\n
* 							add text to queue for voice data\n
* 							play the text\n
* 							Check whether the utterance callback is called\n
* 							Stop the text\n
* 							unset the callbacks and destroy handlers
* @apicovered				tts_add_text, tts_play, tts_stop,
* 							tts_set_utterance_started_cb,tts_get_default_voice,tts_unset_utterance_started_cb, tts_set_utterance_completed_cb, tts_unset_utterance_completed_cb
* @passcase					if API is successful
* @failcase					if API is not successful
* @precondition				The state should be TTS_STATE_CREATED
* @postcondition			NA
*/
int ITc_tts_setunset_utterance_started_completed_cb_p(void)
{
	START_TEST;

	int nGetUtteranceId;
	int eGetvoicetype;
	char *pszGetLanguage = NULL;

	// Target API
	int nRet =  tts_set_utterance_started_cb(g_pstTts, TtsUtteranceStartedCallback, NULL);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_set_utterance_started_cb", TtsGetError(nRet));

	// Target API
	nRet =  tts_set_utterance_completed_cb(g_pstTts, TtsUtteranceCompletedCallback, NULL);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_set_utterance_completed_cb", TtsGetError(nRet), tts_unset_utterance_started_cb(g_pstTts));

	if ( TtsPrepare(TtsStateChangedCallback) == false )
	{
		tts_unset_utterance_completed_cb(g_pstTts);
		tts_unset_utterance_started_cb(g_pstTts);
		return 1;
	}

	while(TTS_STATE_READY != g_eCurrent_state){
		ecore_main_loop_iterate();
	}

	if ( !g_bTtsStateChangedCallback )
	{
		FPRINTF("[Line : %d][%s] tts_set_state_changed_cb failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		tts_unprepare(g_pstTts);
		tts_unset_utterance_completed_cb(g_pstTts);
		tts_unset_utterance_started_cb(g_pstTts);
		TtsUnSetStateChangedCallBacks();
		return 1;
	}

	nRet = tts_get_default_voice(g_pstTts, &pszGetLanguage, &eGetvoicetype);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_get_default_voice", TtsGetError(nRet), tts_unset_utterance_completed_cb(g_pstTts);tts_unset_utterance_started_cb(g_pstTts));

	nRet = tts_add_text(g_pstTts, INPUT_TEXT, pszGetLanguage, eGetvoicetype, TTS_SPEED_AUTO, &nGetUtteranceId);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_add_text", TtsGetError(nRet), tts_unset_utterance_completed_cb(g_pstTts);tts_unset_utterance_started_cb(g_pstTts));

	g_bTtsUtteranceStartedCallback = false;
	g_bTtsUtteranceCompletedCallback = false;

	nRet = tts_play(g_pstTts);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_play", TtsGetError(nRet), tts_unset_utterance_completed_cb(g_pstTts);tts_unset_utterance_started_cb(g_pstTts));

	while(true != g_bTtsUtteranceCompletedCallback){
		ecore_main_loop_iterate();
	}

	if ( (g_bTtsUtteranceStartedCallback == false) || (g_bTtsUtteranceCompletedCallback == false) )
	{
		FPRINTF("[Line : %d][%s] tts_play API fails with return value: %d, error code is: CallBack not invoked \\n", __LINE__, API_NAMESPACE, nRet);
		tts_unset_utterance_completed_cb(g_pstTts);
		tts_unset_utterance_started_cb(g_pstTts);
		return 1;
	}

	nRet = tts_stop(g_pstTts);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_stop", TtsGetError(nRet), TtsUnPrepare();TtsUnSetUtteranceCallBacks());

	while(TTS_STATE_READY != g_eCurrent_state){
		ecore_main_loop_iterate();
	}

	TtsUnPrepare();

	// Target API
	nRet = tts_unset_utterance_completed_cb(g_pstTts);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_unset_utterance_completed_cb", TtsGetError(nRet), tts_unset_utterance_started_cb(g_pstTts));

	// Target API
	nRet = tts_unset_utterance_started_cb(g_pstTts);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_unset_utterance_started_cb", TtsGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: To register a callback function to detect errors.
/**
* @testcase 				ITc_tts_setunset_error_cb_p
* @since_tizen 				2.3
* @author					SRID(anshul1.jain)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @scenario					create a tts handler\n
* 							register a error change callback function\n
* 							play the tts to invoke an error\n
* 							check the error detect callback callback\n
* 							unregister the error change callback\n
* 							destroy that handler
* @apicovered				tts_set_error_cb, tts_unset_error_cb
* @passcase					if API is successful
* @failcase					if API is not successful
* @precondition				the state should be TTS_STATE_CREATED.
* @postcondition			NA
*/
int ITc_tts_setunset_error_cb_p(void)
{
	START_TEST;

	// Target API
	int nRet =  tts_set_error_cb(g_pstTts, TtsErrorCallback, NULL);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_set_error_cb", TtsGetError(nRet));

	// Target API
	nRet =  tts_unset_error_cb(g_pstTts);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_unset_error_cb", TtsGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: To register a callback function to detect default voice change.
/**
* @testcase 				ITc_tts_setunset_default_voice_changed_cb_p
* @since_tizen 				2.3
* @author					SRID(anshul1.jain)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @scenario					create a tts handler\n
* 							get the dafault voice\n
* 							register a default voice change callback function\n
* 							change the dafault voice from device\n
* 							check whether the dafault voice callback invoked or not\n
* 							unregister the default voice change callback\n
* 							destroy that handler
* @apicovered				tts_set_default_voice_changed_cb, tts_unset_default_voice_changed_cb
* @passcase					if API is successful
* @failcase					if API is not successful
* @precondition				The state should be TTS_STATE_CREATED.
* @postcondition			NA
*/
int ITc_tts_setunset_default_voice_changed_cb_p(void)
{
	START_TEST;

	// Target API
	int nRet = tts_set_default_voice_changed_cb (g_pstTts, TtsDefaultVoiceChangedCallback, NULL);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_set_default_voice_changed_cb", TtsGetError(nRet));

	// Target API
	nRet =  tts_unset_default_voice_changed_cb(g_pstTts);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_unset_default_voice_changed_cb", TtsGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: To get the list of supported voices.
/**
* @testcase 				ITc_tts_foreach_supported_voices_p
* @since_tizen 				2.3
* @author					SRID(anshul1.jain)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @scenario					create a tts handler\n
* 							tts_foreach_supported_voices\n
* 							check whether the callback is called or not\n
* 							destroy that handler
* @apicovered				tts_foreach_supported_voices,
* @passcase					if API is successful
* @failcase					if API is not successful
* @precondition				tts_foreach_supported_voices() will invoke this callback function.
* @postcondition			NA
*/
int ITc_tts_foreach_supported_voices_p(void)
{
	START_TEST;

	g_bTtsSupportedVoiceCallback = false;

	// Target API
	int nRet =  tts_foreach_supported_voices(g_pstTts, TtsSupportedVoiceCallback, NULL);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_foreach_supported_voices", TtsGetError(nRet));

	if ( !g_bTtsSupportedVoiceCallback )
	{
		FPRINTF("[Line : %d][%s] tts_foreach_supported_voices failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(!g_CallBackValue)
	{
		FPRINTF("[Line : %d][%s] Callback input values are invalid \n", __LINE__, API_NAMESPACE);
		return 1;
	}
		
	return 0;
}

//& type: auto
//& purpose: To get the list of supported voices.
/**
* @testcase 				ITc_tts_set_credential_p
* @since_tizen 				3.0
* @author					SRID(asit.s)
* @reviewer         		SRID(a.pandia1)
* @type 					auto
* @scenario					create a tts handler\n
* 							call set credentials\n
* @apicovered				tts_set_credential,
* @passcase					if API is successful
* @failcase					if API is not successful
* @precondition				NA
* @postcondition			NA
*/
int ITc_tts_set_credential_p(void)
{
	START_TEST;

	tts_state_e state;
	const char* credential = "TizenApp";
	
	int nRet =  tts_get_state(g_pstTts, &state);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_get_state", TtsGetError(nRet));
	if ( state != TTS_STATE_CREATED )
	{
		FPRINTF("[Line : %d][%s] get state is not matched state is :: %d \\n", __LINE__, API_NAMESPACE,state);
		return 1;
	}
	
	//Target API
	nRet = tts_set_credential(g_pstTts,credential);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_set_credential", TtsGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: To get the list of supported voices.
/**
* @testcase 				ITc_tts_set_get_private_data_p
* @since_tizen 				3.0
* @author					SRID(asit.s)
* @reviewer         		SRID(a.pandia1)
* @type 					auto
* @scenario					create a tts handler\n
* 							call tts_set_private_data\n
*							call tts_get_private_data\n
* @apicovered				tts_set_private_data,tts_get_private_data
* @passcase					if API is successful
* @failcase					if API is not successful
* @precondition				NA
* @postcondition			NA
*/
int ITc_tts_set_get_private_data_p(void)
{
	START_TEST;
	char* Getdata = NULL;

	if ( TtsSetStateChangedCallBacks(TtsStateChangedCallback) == 1 )
	{
		return 1;
	}
	
	int nRet = tts_prepare(g_pstTts);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_prepare", TtsGetError(nRet),TtsUnSetStateChangedCallBacks());

	while(TTS_STATE_READY != g_eCurrent_state){
		ecore_main_loop_iterate();
	}

	nRet = tts_set_private_data(g_pstTts,"version","1.0");
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_set_private_data", TtsGetError(nRet), tts_unprepare(g_pstTts);TtsUnSetStateChangedCallBacks());
	
	nRet = tts_get_private_data(g_pstTts,"version",&Getdata);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_get_private_data", TtsGetError(nRet), tts_unprepare(g_pstTts);TtsUnSetStateChangedCallBacks();FREE_MEMORY(Getdata));
	
	if( 0 != strcmp("1.0",Getdata) )
	{
		FPRINTF("[Line : %d][%s] get data is not matched \\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(Getdata);
		tts_unprepare(g_pstTts);
		TtsUnSetStateChangedCallBacks();
		return 1;
	}
	
	FREE_MEMORY(Getdata);
		
	nRet = tts_unprepare(g_pstTts);
	PRINT_RESULT_NORETURN(TTS_ERROR_NONE, nRet, "tts_unprepare", TtsGetError(nRet));

	TtsUnSetStateChangedCallBacks();
	
	return 0;
}

//& type: auto
//& purpose: To get the list of supported voices.
/**
* @testcase 				ITc_tts_set_unset_engine_changed_cb_p
* @since_tizen 				3.0
* @author					SRID(asit.s)
* @reviewer         		SRID(a.pandia1)
* @type 					auto
* @scenario					create a tts handler\n
* 							call tts_set_engine_changed_cb and register callback function\n
*							call tts_unset_engine_changed_cb to deregister.
* @apicovered				tts_set_engine_changed_cb,tts_unset_engine_changed_cb
* @passcase					if API is successful
* @failcase					if API is not successful
* @precondition				NA
* @postcondition			NA
*/
int ITc_tts_set_unset_engine_changed_cb_p(void)
{
	START_TEST;
	
	g_CallBackValue = false;
	
	int nRet = tts_set_engine_changed_cb(g_pstTts,TtsEngineChangedcallback,NULL);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_set_engine_changed_cb", TtsGetError(nRet));
	
	if(g_CallBackValue != true)
	{
		FPRINTF("[Line : %d][%s] callback hit failed \\n", __LINE__, API_NAMESPACE);
	}
	nRet = tts_unset_engine_changed_cb(g_pstTts);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_unset_engine_changed_cb", TtsGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: To repeat the last played text
/**
* @testcase 				ITc_tts_repeat
* @since_tizen 				5.0
* @author				SRID(samuel.peter)
* @reviewer         			SRID(nibha.sharma)
* @type 				auto
* @scenario				add text using tts_add_text()
					play the text using tts_play()
					stop the text using tts_stop()
					repeat the text using tts_repeat()
* @apicovered				tts_repeat
* @passcase				if API is successful
* @failcase				if API is not successful
* @precondition				curent state should be TTS_STATE_READY
* @postcondition			free any additional memory used with the command FREE_MEMORY().
*/
int ITc_tts_repeat(void)
{
	START_TEST;

	int nRet = TTS_ERROR_NONE;
	char* pszRepeat = NULL;
	int nGetUtteranceId = -1;
	int nGetvoicetype = -1;
	char* pszGetLanguage = NULL;

	if ( TtsSetStateChangedCallBacks(TtsStateChangedCallback) == 1 )
	{
		FPRINTF("[Line: %d][%s] TtsSetStateChangedCallBacks failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = tts_prepare(g_pstTts);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_prepare", TtsGetError(nRet),TtsUnSetStateChangedCallBacks());

	while(TTS_STATE_READY != g_eCurrent_state)
	{
		ecore_main_loop_iterate();
	}

	nRet = tts_get_default_voice(g_pstTts, &pszGetLanguage, &nGetvoicetype);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_get_default_voice", TtsGetError(nRet),TtsUnSetStateChangedCallBacks();tts_unprepare(g_pstTts));
	CHECK_HANDLE_CLEANUP(pszGetLanguage, "tts_get_default_voice", tts_unprepare(g_pstTts);TtsUnSetStateChangedCallBacks());
	if(nGetvoicetype<0 || nGetvoicetype>3)
	{
		FPRINTF("[Line: %d][%s] tts_get_default_voice returned incorrect value of voice type.\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszGetLanguage);
		tts_unprepare(g_pstTts);
		TtsUnSetStateChangedCallBacks();
		return 1;
	}

	nRet = tts_add_text(g_pstTts, "repeat success", pszGetLanguage, nGetvoicetype, TTS_SPEED_AUTO, &nGetUtteranceId);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_add_text", TtsGetError(nRet),TtsUnSetStateChangedCallBacks();tts_unprepare(g_pstTts); FREE_MEMORY(pszGetLanguage));
	if(nGetUtteranceId<=0)
	{
		FPRINTF("[Line: %d][%s] tts_add_text returned incorrect value of utterance ID.\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszGetLanguage);
		tts_unprepare(g_pstTts);
		TtsUnSetStateChangedCallBacks();
		return 1;
	}

	nRet = tts_play(g_pstTts);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_play", TtsGetError(nRet),TtsUnSetStateChangedCallBacks();tts_unprepare(g_pstTts); FREE_MEMORY(pszGetLanguage));

	while(TTS_STATE_PLAYING != g_eCurrent_state)
	{
		ecore_main_loop_iterate();
	}

	nRet = tts_stop(g_pstTts);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_stop", TtsGetError(nRet),TtsUnSetStateChangedCallBacks();tts_unprepare(g_pstTts); FREE_MEMORY(pszGetLanguage));

	while(TTS_STATE_READY != g_eCurrent_state)
	{
		ecore_main_loop_iterate();
	}

	nGetUtteranceId = -1;
	nRet = tts_repeat(g_pstTts, &pszRepeat, &nGetUtteranceId);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_repeat", TtsGetError(nRet),TtsUnSetStateChangedCallBacks();tts_unprepare(g_pstTts); FREE_MEMORY(pszGetLanguage));

	if(strncmp(pszRepeat, "repeat success", strlen(pszRepeat)) != 0)
	{
		FPRINTF("[Line: %d][%s] tts_repeat returned incorrect value of repeat text.\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszGetLanguage);
		FREE_MEMORY(pszRepeat);
		tts_unprepare(g_pstTts);
		TtsUnSetStateChangedCallBacks();
		return 1;
	}
	else if(nGetUtteranceId<0)
	{
		FPRINTF("[Line: %d][%s] tts_repeat returned incorrect value of utterance ID.\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszGetLanguage);
		FREE_MEMORY(pszRepeat);
		tts_unprepare(g_pstTts);
		TtsUnSetStateChangedCallBacks();
		return 1;
	}


	while(TTS_STATE_PLAYING != g_eCurrent_state)
	{
		ecore_main_loop_iterate();
	}

	nRet = tts_stop(g_pstTts);
	PRINT_RESULT_CLEANUP(TTS_ERROR_NONE, nRet, "tts_stop", TtsGetError(nRet),TtsUnSetStateChangedCallBacks();FREE_MEMORY(pszRepeat);tts_unprepare(g_pstTts); FREE_MEMORY(pszGetLanguage));

	while(TTS_STATE_READY != g_eCurrent_state)
	{
		ecore_main_loop_iterate();
	}

	FREE_MEMORY(pszRepeat);
	FREE_MEMORY(pszGetLanguage);
	TtsUnSetStateChangedCallBacks();

	nRet = tts_unprepare(g_pstTts);
	PRINT_RESULT_NORETURN(TTS_ERROR_NONE, nRet, "tts_unprepare", TtsGetError(nRet));

	return 0;
}
//& type: auto
//& purpose: To check status of screen reader (on or off)
/**
* @testcase 				ITc_tts_check_screen_reader_on_p
* @since_tizen 				6.5
* @author            		SRID(manu.tiwari)
* @reviewer         		SRID(shobhit.v)
* @type 					auto
* @scenario					check screen reader on\n
* @apicovered				tts_check_screen_reader_on
* @passcase					if API is successful
* @failcase					if API is not successful
* @precondition				NA
* @postcondition			NA
*/
int ITc_tts_check_screen_reader_on_p(void)
{
	START_TEST;

	int nRet = TTS_ERROR_NONE;
	bool bIsOn = false;
	//Target API
	nRet = tts_check_screen_reader_on(g_pstTts, &bIsOn);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_check_screen_reader_on", TtsGetError(nRet));
	if ( bIsOn == false )
	{
		FPRINTF("[Line : %d][%s] status of screen reader is off\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] status of screen reader is on\\n", __LINE__, API_NAMESPACE);
	}

	return 0;
}
//& type: auto
//& purpose: To detect the option of screen reader is changed or not
/**
* @testcase 				ITc_tts_set_unset_screen_reader_changed_cb_p
* @since_tizen 				6.5
* @author            		SRID(manu.tiwari)
* @reviewer         		SRID(shobhit.v)
* @type 					auto
* @scenario					Registers and Unregisters a callback function to detect the option of screen reader is changed or not
* @apicovered				tts_set_screen_reader_changed_cb, tts_unset_screen_reader_changed_cb
* @passcase					if API is successful
* @failcase					if API is not successful
* @precondition				NA
* @postcondition			NA
*/
int ITc_tts_set_unset_screen_reader_changed_cb_p(void)
{
	START_TEST;

	int nRet = TTS_ERROR_NONE;
	//Target API
	nRet = tts_set_screen_reader_changed_cb(g_pstTts, TtsScreenReaderChangedCallback, NULL);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_set_screen_reader_changed_cb", TtsGetError(nRet));

	nRet = tts_unset_screen_reader_changed_cb(g_pstTts);
	PRINT_RESULT(TTS_ERROR_NONE, nRet, "tts_unset_screen_reader_changed_cb", TtsGetError(nRet));

	return 0;
}

/** @} */ 
/** @} */ 
