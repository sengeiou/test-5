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
#include "ITs-stt-common.h"
#include <Ecore.h>

/** @addtogroup itc-stt
*  @ingroup itc
*  @{
*/
//& set: Stt

char* g_szSupportedLanguages[100];
int g_nSupportedLanguageCount = 0;

bool g_bCallbackParameterCheck;
char* g_szSupportedEngineNames[100];
char* g_szSupportedEngineIDs[100];
int g_nSupportedEngineCount = 0;

stt_result_time_event_e g_resultEvents[100];
int g_nResultEventCount = 0;

bool bCallbackResult = false;
bool g_CallBackHit = false;
/**
* @function 		ITs_stt_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_stt_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_STT_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bFeatureSupported = true;
	g_bFeatureMismatch = false;
	g_bFeatureNotSupported = false;

	g_bFeatureSupported = TCTCheckSystemInfoFeatureSupported(MICROPHONE_FEATURE, API_NAMESPACE) &&
		TCTCheckSystemInfoFeatureSupported(SPEECH_RECOGNITION_FEATURE, API_NAMESPACE);

	//Create STT Handle
	int nRet = stt_create(&g_hStt);
	if ( !g_bFeatureSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] stt_create returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
			g_bFeatureMismatch = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] stt_create correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
			g_bFeatureNotSupported = true;
		}
		return;
	}

	if ( nRet == STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] STT handle created successfully in precondition\\n", __LINE__, API_NAMESPACE);

		//Check state after stt_create
		stt_state_e nState;
		nRet = stt_get_state(g_hStt, &nState);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Support API stt_get_state failed, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
			g_bSttCreation = false;
		}
		else if ( nState != STT_STATE_CREATED )
		{
			FPRINTF("[Line : %d][%s] Support API stt_get_state returned invalid state %s, expected state = STT_STATE_CREATED\\n", __LINE__, API_NAMESPACE, SttGetState(nState));
			g_bSttCreation = false;
		}
		else
		{
			g_bSttCreation = true;
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] Unable to create STT handle in precondition, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
		g_bSttCreation = false;
	}
	return;
}

/**
* @function 		ITs_stt_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_stt_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_STT_p\\n", __LINE__, API_NAMESPACE);
#endif

	//Destroy STT Handle
	if ( g_bFeatureSupported && g_bSttCreation && g_hStt != NULL )
	{
		int nRet = stt_destroy(g_hStt);
		if ( nRet == STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] STT handle destroyed successfully in postcondition\\n", __LINE__, API_NAMESPACE);
		}
		else
		{
			FPRINTF("[Line : %d][%s] Unable to destroy SST handle in postcondition, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
		}
	}
	return;
}


/**
* @function 		stt_default_language_changed_callback
* @description	 	Called when the default language is changed
* @parameter		[in] stt The STT handle
*					[in] previous_language A previous language
*					[in] current_language A current language
*					[in] user_data The user data passed from the callback registration function
* @return 			None
*/
void stt_default_language_changed_callback(stt_h stt, const char *previous_language, const char *current_language, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Reached stt_default_language_changed_callback\\n", __LINE__, API_NAMESPACE);
#endif

	g_bDefaultLanguageChangedCallbackOccurred = true;

	if ( g_szPreviousLanguage == NULL )
	{
		g_szPreviousLanguage = (char *) malloc(LANGUAGE_LEN * sizeof(char));
	}
	else
	{
		memset(g_szPreviousLanguage, 0, LANGUAGE_LEN);
	}
	strncpy(g_szPreviousLanguage, previous_language, LANGUAGE_LEN-1);

	if ( g_szCurrentLanguage == NULL )
	{
		g_szCurrentLanguage = (char *) malloc(LANGUAGE_LEN * sizeof(char));
	}
	else
	{
		memset(g_szCurrentLanguage, 0, LANGUAGE_LEN);
	}
	strncpy(g_szCurrentLanguage, current_language, LANGUAGE_LEN-1);
}

/**
* @function 		stt_error_callback
* @description	 	Called when an error occurs
* @parameter		[in] stt The STT handle
*					[in] reason The error type (e.g. STT_ERROR_OUT_OF_NETWORK, STT_ERROR_IO_ERROR)
*					[in] user_data The user data passed from the callback registration function
* @precondition	An application registers this callback using stt_set_error_cb() to detect error
* @return 			None
*/
void stt_error_callback(stt_h stt, stt_error_e reason, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Reached stt_error_callback\\n", __LINE__, API_NAMESPACE);
#endif

	g_bErrorCallbackOccurred = true;


	g_nErrorReason = reason;
}

/**
* @function 		sttStatusChangedcb
* @description	 	Called when an error occurs
* @parameter		[in] stt The STT handle
*					[in] the speech status
*					[in] user_data The user data passed from the callback registration function
* @return 			None
*/
void sttStatusChangedcb(stt_h stt, stt_speech_status_e status, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Reached sttStatusChangedcb\\n", __LINE__, API_NAMESPACE);
#endif

}



/**
* @function 		stt_recognition_result_callback
* @description	 	Called when STT gets the recognition result from the engine
* @remarks			After stt_stop() is called, silence is detected from recording, or partial result is occurred, this function is called
* @parameter		[in] stt The STT handle
*					[in] event The result event
*					[in] data Result texts
*					[in] data_count Result text count
*					[in] msg Engine message (e.g. STT_RESULT_MESSAGE_NONE, STT_RESULT_MESSAGE_ERROR_TOO_SHORT)
*					[in] user_data The user data passed from the callback registration function
* @precondition 	stt_stop() will invoke this callback if you register it using stt_set_result_cb()
* @postcondition	If this function is called and event is STT_RESULT_EVENT_FINAL_RESULT, the STT state will be STT_STATE_READY
* @return 			None
*/
void stt_recognition_result_callback(stt_h stt, stt_result_event_e event, const char **data, int data_count, const char *msg, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Reached stt_recognition_result_callback\\n", __LINE__, API_NAMESPACE);
#endif

	g_bResultCallbackOccurred = true;

	if(stt == NULL)
	{
		FPRINTF("[Line : %d][%s] Handle is NULL in callback function\\n", __LINE__, API_NAMESPACE);
		g_bCallbackParameterCheck = false;
	}
	else if((event<STT_RESULT_EVENT_FINAL_RESULT) || (event>STT_RESULT_EVENT_ERROR))
	{
		FPRINTF("[Line : %d][%s] event is not valid in callback function\\n", __LINE__, API_NAMESPACE);
		g_bCallbackParameterCheck = false;
	}
	else if(msg == NULL)
	{
		FPRINTF("[Line : %d][%s] msg is NULL in callback function\\n", __LINE__, API_NAMESPACE);
		g_bCallbackParameterCheck = false;
	}
	else if(data_count == -1)
	{
		FPRINTF("[Line : %d][%s] data count is invalid in callback function\\n", __LINE__, API_NAMESPACE);
		g_bCallbackParameterCheck = false;
	}
	else
	{
		g_bCallbackParameterCheck = true;
	}


	g_nResultEvent = event;
}

/**
* @function 		stt_result_time_callback
* @description	 	Called when STT get the result time stamp in free partial type
* @parameter		[in] stt The STT handle
*					[in] index The result index
*					[in] event The token event
*					[in] text The result text
*					[in] start_time The start time of result text
*					[in] end_time The end time of result text
*					[in] user_data The user data passed from the foreach function
* @precondition 	stt_recognition_result_cb() should be called
* @return 			true to continue with the next iteration of the loop , false to break out of the loop
*/
bool stt_result_time_callback(stt_h stt, int index, stt_result_time_event_e event, const char *text, long start_time, long end_time, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Reached stt_result_time_callback\\n", __LINE__, API_NAMESPACE);
#endif

	g_bResultTimeCallbackOccurred = true;


	g_resultEvents[g_nResultEventCount] = event;
	g_nResultEventCount++;

	return true;
}

/**
* @function 		stt_state_changed_callback
* @description	 	Called when the state of STT is changed
* @parameter		[in] stt The STT handle
*					[in] previous A previous state
*					[in] current A current state
*					[in] user_data The user data passed from the callback registration function
* @precondition	An application registers this callback using stt_set_state_changed_cb() to detect changing state
* @return 			None
*/
void stt_state_changed_callback(stt_h stt, stt_state_e previous, stt_state_e current, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Reached stt_state_changed_callback\\n", __LINE__, API_NAMESPACE);
#endif

	g_bStateCallbackOccurred = true;

	if(stt == NULL)
	{
		FPRINTF("[Line : %d][%s] Handle is NULL in callback function\\n", __LINE__, API_NAMESPACE);
		g_bCallbackParameterCheck = false;
	}
	else if((previous<STT_STATE_CREATED) || (previous>STT_STATE_PROCESSING))
	{
		FPRINTF("[Line : %d][%s] previous state is not valid in callback function\\n", __LINE__, API_NAMESPACE);
		g_bCallbackParameterCheck = false;
	}
	else if((current<STT_STATE_CREATED) || (current>STT_STATE_PROCESSING))
	{
		FPRINTF("[Line : %d][%s] current state is not valid in callback function\\n", __LINE__, API_NAMESPACE);
		g_bCallbackParameterCheck = false;
	}
	else
	{
		g_bCallbackParameterCheck = true;
	}
	g_nPreviousState = previous;
	g_nCurrentState = current;
}

/**
* @function 		stt_supported_engine_callback
* @description	 	Called to retrieve the supported languages
* @remarks			The language is specified as an ISO 3166 alpha-2 two letter country-code followed by ISO 639-1 for the two-letter language code.
*					For example, "ko_KR" for Korean, "en_US" for American English
* @parameter		[in] engine_id Engine id
*					[in] engine_name Engine name
*					[in] user_data User data passed from the stt_setting_foreach_supported_engines()
* @precondition	stt_foreach_supported_engines() will invoke this callback
* @return 			true to continue with the next iteration of the loop, false to break out of the loop
*/
bool stt_supported_engine_callback(stt_h stt, const char *engine_id, const char *engine_name, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Reached stt_supported_engine_callback\\n", __LINE__, API_NAMESPACE);
#endif

	g_bSupportedEngineCallbackOccured = true;

	if(stt == NULL)
	{
		FPRINTF("[Line : %d][%s] Handle is NULL in callback function\\n", __LINE__, API_NAMESPACE);
		g_bCallbackParameterCheck = false;
		return false;
	}
	else if(engine_id == NULL)
	{
		FPRINTF("[Line : %d][%s] engine id is not valid in callback function\\n", __LINE__, API_NAMESPACE);
		g_bCallbackParameterCheck = false;
		return false;
	}
	else if(engine_name == NULL)
	{
		FPRINTF("[Line : %d][%s] engine name is not valid in callback function\\n", __LINE__, API_NAMESPACE);
		g_bCallbackParameterCheck = false;
		return false;
	}
	else
	{
		g_bCallbackParameterCheck = true;
	}

	if ( g_szSupportedEngineIDs[g_nSupportedEngineCount] == NULL )
	{
		g_szSupportedEngineIDs[g_nSupportedEngineCount] = (char *) malloc(ENGINE_LEN * sizeof(char));
	}
	else
	{
		memset(g_szSupportedEngineIDs[g_nSupportedEngineCount], 0, ENGINE_LEN);
	}
	strncpy(g_szSupportedEngineIDs[g_nSupportedEngineCount], engine_id, ENGINE_LEN-1);

	if ( g_szSupportedEngineNames[g_nSupportedEngineCount] == NULL )
	{
		g_szSupportedEngineNames[g_nSupportedEngineCount] = (char *) malloc(ENGINE_LEN * sizeof(char));
	}
	else
	{
		memset(g_szSupportedEngineNames[g_nSupportedEngineCount], 0, ENGINE_LEN);
	}
	strncpy(g_szSupportedEngineNames[g_nSupportedEngineCount], engine_name, ENGINE_LEN-1);

	g_nSupportedEngineCount++;

	return true;
}

/**
* @function 		stt_supported_language_callback
* @description	 	Called to retrieve the supported languages
* @remarks			The language is specified as an ISO 3166 alpha-2 two letter country-code followed by ISO 639-1 for the two-letter language code.
*					For example, "ko_KR" for Korean, "en_US" for American English
* @parameter		[in] stt The STT handle
*					[in] language The language
*					[in] user_data The user data passed from the foreach function
* @precondition	stt_foreach_supported_languages() will invoke this callback
* @return 			true to continue with the next iteration of the loop, false to break out of the loop
*/
bool stt_supported_language_callback(stt_h stt, const char *language, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Reached stt_supported_language_callback\\n", __LINE__, API_NAMESPACE);
#endif

	g_bSupportedLanguageCallbackOccured = true;

	if(stt == NULL)
	{
		FPRINTF("[Line : %d][%s] Handle is NULL in callback function\\n", __LINE__, API_NAMESPACE);
		g_bCallbackParameterCheck = false;
		return false;
	}
	else if(language == NULL)
	{
		FPRINTF("[Line : %d][%s] language is not valid in callback function\\n", __LINE__, API_NAMESPACE);
		g_bCallbackParameterCheck = false;
		return false;
	}
	else
	{
		g_bCallbackParameterCheck = true;
	}


	if ( g_szSupportedLanguages[g_nSupportedLanguageCount] == NULL )
	{
		g_szSupportedLanguages[g_nSupportedLanguageCount] = (char *) malloc(LANGUAGE_LEN * sizeof(char));
	}
	else
	{
		memset(g_szSupportedLanguages[g_nSupportedLanguageCount], 0, LANGUAGE_LEN);
	}
	strncpy(g_szSupportedLanguages[g_nSupportedLanguageCount], language, LANGUAGE_LEN-1);
	g_nSupportedLanguageCount++;

	return true;
}

/**
* @function 		stt_recognition_result_callback_check_detailed_result
* @description	 	Called when STT gets the recognition result from the engine
* @remarks			After stt_stop() is called, silence is detected from recording, or partial result is occurred, this function is called
* @parameter		[in] stt The STT handle
*					[in] event The result event
*					[in] data Result texts
*					[in] data_count Result text count
*					[in] msg Engine message (e.g. STT_RESULT_MESSAGE_NONE, STT_RESULT_MESSAGE_ERROR_TOO_SHORT)
*					[in] user_data The user data passed from the callback registration function
* @precondition 	stt_stop() will invoke this callback if you register it using stt_set_result_cb()
* @postcondition	If this function is called and event is STT_RESULT_EVENT_FINAL_RESULT, the STT state will be STT_STATE_READY
* @return 			None
*/
void stt_recognition_result_callback_check_detailed_result(stt_h stt, stt_result_event_e event, const char **data, int data_count, const char *msg, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Reached stt_recognition_result_callback_check_detailed_result\\n", __LINE__, API_NAMESPACE);
#endif

	g_bResultCallbackOccurred = true;

	if(stt == NULL)
	{
		FPRINTF("[Line : %d][%s] Handle is NULL in callback function\\n", __LINE__, API_NAMESPACE);
		g_bCallbackParameterCheck = false;
	}
	else if((event<STT_RESULT_EVENT_FINAL_RESULT) || (event>STT_RESULT_EVENT_ERROR))
	{
		FPRINTF("[Line : %d][%s] event is not valid in callback function\\n", __LINE__, API_NAMESPACE);
		g_bCallbackParameterCheck = false;
	}
	else if(data == NULL)
	{
		FPRINTF("[Line : %d][%s] data is NULL in callback function\\n", __LINE__, API_NAMESPACE);
		g_bCallbackParameterCheck = false;
	}
	else if(msg == NULL)
	{
		FPRINTF("[Line : %d][%s] msg is NULL in callback function\\n", __LINE__, API_NAMESPACE);
		g_bCallbackParameterCheck = false;
	}
	else if(data_count == -1)
	{
		FPRINTF("[Line : %d][%s] data count is invalid in callback function\\n", __LINE__, API_NAMESPACE);
		g_bCallbackParameterCheck = false;
	}
	else
	{
		g_bCallbackParameterCheck = true;
	}


	//Target API
	/**** Retrieve the time stamp of the current recognition result using the callback function ***/
	int nRet = stt_foreach_detailed_result(g_hStt, stt_result_time_callback, NULL);
	if ( nRet != STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] stt_foreach_detailed_result failed, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
		bCallbackResult = false;
	}
	else if ( !g_bResultTimeCallbackOccurred )
	{
		FPRINTF("[Line : %d][%s] stt_foreach_detailed_result failed to invoke stt_result_time_cb callback\\n", __LINE__, API_NAMESPACE);
		bCallbackResult = false;
	}
	else if ( g_nResultEventCount == 0 )
	{
		FPRINTF("[Line : %d][%s] stt_foreach_detailed_result failed to get any result event in callback\\n", __LINE__, API_NAMESPACE);
		bCallbackResult = false;
	}
	else if ( g_resultEvents[0] != STT_RESULT_TIME_EVENT_BEGINNING )
	{
		FPRINTF("[Line : %d][%s] stt_foreach_detailed_result invoked callback with invalid initial event %s, expected initial event = STT_RESULT_TIME_EVENT_BEGINNING\\n",
			__LINE__, API_NAMESPACE, SttGetResultTimeEvent(g_resultEvents[0]));
		bCallbackResult = false;
	}
	else if ( g_resultEvents[g_nResultEventCount/2] != STT_RESULT_TIME_EVENT_MIDDLE )
	{
		FPRINTF("[Line : %d][%s] stt_foreach_detailed_result invoked callback with invalid middle event %s, expected middle event = STT_RESULT_TIME_EVENT_MIDDLE\\n",
			__LINE__, API_NAMESPACE, SttGetResultTimeEvent(g_resultEvents[g_nResultEventCount/2]));
		bCallbackResult = false;
	}
	else if ( g_resultEvents[g_nResultEventCount - 1] != STT_RESULT_TIME_EVENT_END )
	{
		FPRINTF("[Line : %d][%s] stt_foreach_detailed_result invoked callback with invalid final event %s, expected final event = STT_RESULT_TIME_EVENT_END\\n",
			__LINE__, API_NAMESPACE, SttGetResultTimeEvent(g_resultEvents[g_nResultEventCount - 1]));
		bCallbackResult = false;
	}
}

/**
* @function 		initialize_setup_without_result_callback
* @description	 	Connect the STT daemon to make STT_STATE_READY state
* @parameter		None
* @precondition 	State is STT_STATE_CREATED
* @postcondition	State will be STT_STATE_READY
* @return 			None
*/
bool initialize_setup_without_result_callback()
{
	//Register a callback function to be called when STT state changes
	g_bStateCallbackOccurred = false;
	int nRet = stt_set_state_changed_cb(g_hStt, stt_state_changed_callback, NULL);
	if ( nRet != STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Support API stt_set_state_changed_cb failed on precondition, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
		return false;
	}

	//Connect the STT daemon asynchronously
	nRet = stt_prepare(g_hStt);
	if ( nRet != STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Support API stt_prepare failed on precondition, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
		nRet = stt_unset_state_changed_cb(g_hStt);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Support API stt_unset_state_changed_cb failed on postcondition, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
		}
		return false;
	}

	//Wait for the state change
	WAIT_FOR_CALLBACK(STT_STATE_READY);

	//Check state after stt_prepare
	stt_state_e nState;
	nRet = stt_get_state(g_hStt, &nState);
	if ( nRet != STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Support API stt_get_state failed on precondition, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
		nRet = stt_unset_state_changed_cb(g_hStt);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Support API stt_unset_state_changed_cb failed on postcondition, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
		}
		return false;
	}
	else if ( nState != STT_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] Support API stt_get_state returned invalid state %s, expected state = STT_STATE_READY\\n", __LINE__, API_NAMESPACE, SttGetState(nState));
		nRet = stt_unset_state_changed_cb(g_hStt);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Support API stt_unset_state_changed_cb failed on postcondition, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
		}
		return false;
	}

	nRet = stt_set_private_data(g_hStt, "stt_verification", "true");
	if ( nRet != STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] stt_set_private_data failed for TC mode, error returned = %s\\n",
			__LINE__, API_NAMESPACE,  SttGetError(nRet));
		return false;
	}

	nRet = stt_set_silence_detection(g_hStt, STT_OPTION_SILENCE_DETECTION_FALSE);
	if ( nRet != STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] stt_set_silence_detection failed for option type %s, error returned = %s\\n",
			__LINE__, API_NAMESPACE, SttGetOptionForSilenceDetection(STT_OPTION_SILENCE_DETECTION_FALSE), SttGetError(nRet));
		stt_set_private_data(g_hStt, "stt_verification", "false");
		return false;
	}

	g_bSupportedLanguageCallbackOccured = false;
	g_nSupportedLanguageCount = 0;
	nRet = stt_foreach_supported_languages(g_hStt, stt_supported_language_callback, NULL);
	if ( nRet != STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Support API stt_foreach_supported_languages failed on precondition, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
		nRet = stt_unset_state_changed_cb(g_hStt);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Support API stt_unset_state_changed_cb failed on postcondition, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
		}
		stt_set_private_data(g_hStt, "stt_verification", "false");
		return false;
	}

	return true;
}

/**
* @function 		initialize_setup_with_result_callback
* @description	 	Register the result callback and connect the STT daemon to make STT_STATE_READY state
* @parameter		None
* @precondition 	State is STT_STATE_CREATED
* @postcondition	State will be STT_STATE_READY
* @return 			None
*/
bool initialize_setup_with_result_callback()
{
	//Register a callback function to get the recognition result
	g_bResultCallbackOccurred = false;
	int nRet = stt_set_recognition_result_cb(g_hStt, stt_recognition_result_callback, NULL);
	if ( nRet != STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Support API stt_set_recognition_result_cb failed on precondition, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
		return false;
	}

	//Registers a callback function to be called when an error occurred
	nRet = stt_set_error_cb(g_hStt, stt_error_callback, NULL);
	if ( nRet != STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Support API stt_set_error_cb failed on precondition, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
		return false;
	}

	if ( !initialize_setup_without_result_callback() )
	{
		return false;
	}

	return true;
}

/**
* @function 		deinitialize_setup_without_result_callback
* @description	 	Disconnect the STT daemon to make STT_STATE_READY state
* @parameter		None
* @precondition 	State is STT_STATE_READY
* @postcondition	State will be STT_STATE_CREATED
* @return 			None
*/
void deinitialize_setup_without_result_callback()
{
	int nRet = stt_set_private_data(g_hStt, "stt_verification", "false");
	if ( nRet != STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] stt_set_private_data failed for reset TC mode, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
	}

	//Disconnect the STT daemon asynchronously
	nRet = stt_unprepare(g_hStt);
	if ( nRet != STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] stt_unprepare failed on postcondition, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
	}

	//Un-register the state callback function
	nRet = stt_unset_state_changed_cb(g_hStt);
	if ( nRet != STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Support API stt_unset_state_changed_cb failed on postcondition, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
	}
}

/**
* @function 		deinitialize_setup_with_result_callback
* @description	 	Unregister the result callback and disconnect the STT daemon to make STT_STATE_READY state
* @parameter		None
* @precondition 	State is STT_STATE_READY
* @postcondition	State will be STT_STATE_CREATED
* @return 			None
*/
void deinitialize_setup_with_result_callback()
{
	deinitialize_setup_without_result_callback();

	//Unregister the error callback function
	int nRet = stt_unset_error_cb(g_hStt);
	if ( nRet != STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Support API stt_unset_error_cb failed on postcondition, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
	}

	//Unregister the result callback function
	nRet = stt_unset_recognition_result_cb(g_hStt);
	if ( nRet != STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Support API stt_unset_recognition_result_cb failed on postcondition, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
	}
}

/**
* @function 		sttEngineChangedcb
* @description	 	callback function register by stt_set_engine_changed_cb
* @parameter
* @param[in] 		stt The STT handle
* @param[in] 		engine_id Engine id
* @param[in] 		language The default language
* @param[in] 		support_silence Whether the silence detection is supported or not
* @param[in] 		need_credential The necessity of credential
* @param[in] 		user_data The user data passed from the callback registration function
* @precondition 	NA
* @postcondition	NA
* @return 			bool
*/
bool sttEngineChangedcb(stt_h stt, const char* engine_id, const char* language, bool support_silence, bool need_credential, void* user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Reached sttEngineChangedcb\\n", __LINE__, API_NAMESPACE);
#endif

	if(stt == NULL)
	{
		FPRINTF("[Line : %d][%s] Handle is NULL in callback function\\n", __LINE__, API_NAMESPACE);
	}
	return true;
}

/**
* @function 		sttErrorCallback
* @description	 	Called when an error occurs
* @parameter		[in] stt The STT handle
*					[in] reason The error type (e.g. STT_ERROR_OUT_OF_NETWORK, STT_ERROR_IO_ERROR)
*					[in] user_data The user data passed from the callback registration function
* @precondition	An application registers this callback using stt_set_error_cb() to detect error
* @return 			None
*/
void sttErrorCallback(stt_h stt, stt_error_e reason, void *user_data)
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


/** @addtogroup itc-stt-testcases
*  @brief 		Integration testcases for module stt
*  @ingroup 	itc-stt
*  @{
*/
//& purpose Create and destroy an STT handle
//& type: auto
/**
* @testcase				ITc_stt_create_destroy_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Create and destroy an STT handle
* @scenario				Creates an STT handle\n
* 						Destroys an STT handle
* @apicovered			stt_create, stt_destroy, stt_get_state
* @passcase				If creates and destroys an STT handle
* @failcase				If fails to create and destroy the STT handle
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_create_destroy_p(void)
{
	START_TEST;

	stt_h hStt = NULL;
	//Target API
	/**** Create STT Handle ****/
	int nRet = stt_create(&hStt);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_create", SttGetError(nRet));
	CHECK_HANDLE(hStt, "stt_create");

	//Postcondition of stt_create; Check state
	stt_state_e nState;
	nRet = stt_get_state(hStt, &nState);
	PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_get_state", SttGetError(nRet), stt_destroy(hStt));
	if ( nState != STT_STATE_CREATED )
	{
		FPRINTF("[Line : %d][%s] Support API stt_get_state returned invalid state %s, expected state = STT_STATE_CREATED\\n", __LINE__, API_NAMESPACE, SttGetState(nState));
		stt_destroy(hStt);
		return 1;;
	}

	//Target API
	/**** Destroy STT Handle ****/
	nRet = stt_destroy(hStt);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_destroy", SttGetError(nRet));
	return 0;
}


//& purpose Connect & disconnect the daemon asynchronously
//& type: auto
/**
* @testcase				ITc_stt_prepare_unprepare_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Connect & disconnect the daemon asynchronously
* @scenario				Creates an STT handle\n
* 						Connect the daemon asynchronously\n
* 						Disconnect the daemon asynchronously\n
* 						Destroys an STT handle
* @apicovered			stt_set_state_changed_cb, stt_prepare, stt_unprepare, stt_unset_state_changed_cb
* @passcase				If connects and disconnects the STT daemon successfully
* @failcase				If fails to connect and disconnect the STT daemon
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_prepare_unprepare_p(void)
{
	START_TEST;

	//Register a callback function to be called when STT state changes
	int nRet = stt_set_state_changed_cb(g_hStt, stt_state_changed_callback, NULL);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_set_state_changed_cb", SttGetError(nRet));

	g_bStateCallbackOccurred = false;
	g_bCallbackParameterCheck = false;

	//Target API
	/**** Connect the STT daemon asynchronously ****/
	nRet = stt_prepare(g_hStt);
	PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_prepare", SttGetError(nRet), stt_unset_state_changed_cb(g_hStt));

	WAIT_FOR_CALLBACK(STT_STATE_READY);

	if ( !g_bStateCallbackOccurred )
	{
		FPRINTF("[Line : %d][%s] stt_prepare failed to invoke callback\\n", __LINE__, API_NAMESPACE);
		stt_unprepare(g_hStt);
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}
	else if(!g_bCallbackParameterCheck)
	{
		stt_unprepare(g_hStt);
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}
	else if ( g_nPreviousState != STT_STATE_CREATED )
	{
		FPRINTF("[Line : %d][%s] stt_prepare invoked callback with invalid previous state %s, expected state = STT_STATE_CREATED\\n", __LINE__, API_NAMESPACE, SttGetState(g_nPreviousState));
		stt_unprepare(g_hStt);
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}
	else if ( g_nCurrentState != STT_STATE_READY )	//This is precondition of stt_unprepare
	{
		FPRINTF("[Line : %d][%s] stt_prepare invoked callback with invalid current state %s, expected state = STT_STATE_READY\\n", __LINE__, API_NAMESPACE, SttGetState(g_nCurrentState));
		stt_unprepare(g_hStt);
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}

	g_bStateCallbackOccurred = false;

	//Target API
	/**** Disconnect the STT daemon asynchronously ****/
	nRet = stt_unprepare(g_hStt);
	PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_unprepare", SttGetError(nRet), stt_unset_state_changed_cb(g_hStt));

	WAIT_FOR_CALLBACK(STT_STATE_CREATED);

	if ( !g_bStateCallbackOccurred )
	{
		FPRINTF("[Line : %d][%s] stt_unprepare failed to invoke callback\\n", __LINE__, API_NAMESPACE);
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}
	else if ( g_nPreviousState != STT_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] stt_unprepare invoked callback with invalid previous state %s, expected state = STT_STATE_READY\\n", __LINE__, API_NAMESPACE, SttGetState(g_nPreviousState));
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}
	else if ( g_nCurrentState != STT_STATE_CREATED )
	{
		FPRINTF("[Line : %d][%s] stt_unprepare invoked callback with invalid current state %s, expected state = STT_STATE_CREATED\\n", __LINE__, API_NAMESPACE, SttGetState(g_nCurrentState));
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}

	nRet = stt_unset_state_changed_cb(g_hStt);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_unset_state_changed_cb", SttGetError(nRet));
	return 0;
}

//& purpose Start recording and recognition asynchronously and then finish the recording and start recognition processing in engine asynchronously
//& type: auto
/**
* @testcase				ITc_stt_start_stop_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Start and then stop recording & recognition asynchronously
* @scenario				Creates an STT handle\n
* 						Connect the daemon asynchronously\n
* 						Start recording and recognition asynchronously\n
* 						Finish the recording and start recognition processing in engine asynchronously\n
* 						Disconnect the daemon asynchronously\n
* 						Destroys an STT handle
* @apicovered			stt_start, stt_stop
* @passcase				If starts and stops the recording successfully
* @failcase				If fails to start and stop the recording
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_start_stop_p(void)
{
	START_TEST;

	if ( !initialize_setup_with_result_callback() )
	{
		return 1;
	}

	const char* szRecognitionTypes[] = { STT_RECOGNITION_TYPE_FREE, STT_RECOGNITION_TYPE_FREE_PARTIAL };
	int nRecognitionTypeCount = sizeof(szRecognitionTypes) / sizeof(szRecognitionTypes[0]);
	int nLanguageCounter = 0, nTypeCounter = 0;
	int nRet = 0;
	for ( nTypeCounter=0; nTypeCounter<nRecognitionTypeCount; nTypeCounter++ )
	{
		g_bStateCallbackOccurred = false;

		//Target API
		/**** Start recording and recognition asynchronously ****/
		nRet = stt_start(g_hStt, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] stt_start failed for language %s and type %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter], SttGetError(nRet));
			deinitialize_setup_with_result_callback();
			return 1;
		}

		WAIT_FOR_CALLBACK(STT_STATE_RECORDING);

		if ( !g_bStateCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] stt_start failed to invoke callback for language %s and type %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			deinitialize_setup_with_result_callback();
			return 1;
		}
		else if ( g_nPreviousState != STT_STATE_READY )
		{
			FPRINTF("[Line : %d][%s] stt_start invoked callback with invalid previous state %s for language %s and type %s, expected state = STT_STATE_READY\\n",
			__LINE__, API_NAMESPACE, SttGetState(g_nPreviousState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
		stt_cancel(g_hStt);
				deinitialize_setup_with_result_callback();
				return 1;
		}
		else if ( g_nCurrentState != STT_STATE_RECORDING )	//This is precondition of stt_stop
		{
			FPRINTF("[Line : %d][%s] stt_start invoked callback with invalid current state %s for language %s and type %s, expected state = STT_STATE_RECORDING\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nCurrentState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			deinitialize_setup_with_result_callback();
			return 1;
		}

		g_bStateCallbackOccurred = false;
		g_bResultCallbackOccurred = false;

		usleep(1000000);
		//Target API
		/**** Finish the recording and start recognition processing in engine asynchronously ****/
		nRet = stt_stop(g_hStt);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] stt_stop failed for language %s and type %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter], SttGetError(nRet));
			deinitialize_setup_with_result_callback();
			return 1;
		}

		//Wait for the state change
		WAIT_FOR_CALLBACK(STT_STATE_PROCESSING);

		if ( !g_bStateCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] stt_stop failed to invoke callback for language %s and type %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			deinitialize_setup_with_result_callback();
			return 1;
		}
		else if ( g_nPreviousState != STT_STATE_RECORDING )
		{
			FPRINTF("[Line : %d][%s] stt_stop invoked callback with invalid previous state %s for language %s and type %s, expected state = STT_STATE_RECORDING\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nPreviousState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			deinitialize_setup_with_result_callback();
			return 1;
		}
		else if ( g_nCurrentState != STT_STATE_PROCESSING )
		{
			FPRINTF("[Line : %d][%s] stt_stop invoked callback with invalid current state %s for language %s and type %s, expected state = STT_STATE_PROCESSING\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nCurrentState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			deinitialize_setup_with_result_callback();
			return 1;
		}

		//Wait for the result to complete
		WAIT_FOR_CALLBACK(STT_STATE_READY);

		if ( !g_bResultCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] stt_stop failed to invoke result callback for language %s and type %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			deinitialize_setup_with_result_callback();
			return 1;
		}
		else if ( g_nResultEvent == STT_RESULT_EVENT_ERROR )
		{
			FPRINTF("[Line : %d][%s] stt_stop invoked result callback with invalid result %s for language %s and type %s\\n",
				__LINE__, API_NAMESPACE, SttGetResultEvent(g_nResultEvent), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
		}
	}
	deinitialize_setup_with_result_callback();
	return 0;
}

//& purpose Start recording and recognition asynchronously and then cancel recording
//& type: auto
/**
* @testcase				ITc_stt_start_cancel_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Start and then cancel recording & recognition asynchronously
* @scenario				Creates an STT handle\n
* 						Connect the daemon asynchronously\n
* 						Start recording and recognition asynchronously\n
* 						Cancel recording\n
* 						Disconnect the daemon asynchronously\n
* 						Destroys an STT handle
* @apicovered			stt_start, stt_cancel
* @passcase				If starts and cancels the recording successfully
* @failcase				If fails to start and cancel the recording
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_start_cancel_p(void)
{
	START_TEST;

	if ( !initialize_setup_with_result_callback() )
	{
		return 1;
	}

	const char* szRecognitionTypes[] = { STT_RECOGNITION_TYPE_FREE, STT_RECOGNITION_TYPE_FREE_PARTIAL };
	int nRecognitionTypeCount = sizeof(szRecognitionTypes) / sizeof(szRecognitionTypes[0]);
	int nLanguageCounter = 0, nTypeCounter = 0;

	for ( nTypeCounter=0; nTypeCounter<nRecognitionTypeCount; nTypeCounter++ )
	{
		g_bStateCallbackOccurred = false;

		//Target API
		/**** Start recording and recognition asynchronously ****/
		int nRet = stt_start(g_hStt, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] stt_start failed for language %s and type %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter], SttGetError(nRet));
			deinitialize_setup_with_result_callback();
			return 1;
		}

		WAIT_FOR_CALLBACK(STT_STATE_RECORDING);

		if ( !g_bStateCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] stt_start failed to invoke callback for language %s and type %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			deinitialize_setup_with_result_callback();
			return 1;
		}
		else if ( g_nPreviousState != STT_STATE_READY )
		{
			FPRINTF("[Line : %d][%s] stt_start invoked callback with invalid previous state %s for language %s and type %s, expected state = STT_STATE_READY\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nPreviousState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			deinitialize_setup_with_result_callback();
			return 1;
		}
		else if ( g_nCurrentState != STT_STATE_RECORDING )	//This is precondition of stt_cancel
		{
			FPRINTF("[Line : %d][%s] stt_start invoked callback with invalid current state %s for language %s and type %s, expected state = STT_STATE_RECORDING\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nCurrentState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			deinitialize_setup_with_result_callback();
			return 1;
		}

		g_bStateCallbackOccurred = false;

		//Target API
		/**** Cancel the recording and start recognition processing in engine asynchronously ****/
		nRet = stt_cancel(g_hStt);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] stt_cancel failed for language %s and type %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter], SttGetError(nRet));
			deinitialize_setup_with_result_callback();
			return 1;
		}

		//Wait for the state change
		WAIT_FOR_CALLBACK(STT_STATE_READY);

		if ( !g_bStateCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] stt_cancel failed to invoke callback for language %s and type %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			deinitialize_setup_with_result_callback();
			return 1;
		}
		else if ( g_nPreviousState != STT_STATE_RECORDING )
		{
			FPRINTF("[Line : %d][%s] stt_cancel invoked callback with invalid previous state %s for language %s and type %s, expected state = STT_STATE_RECORDING\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nPreviousState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			deinitialize_setup_with_result_callback();
			return 1;
		}
		else if ( g_nCurrentState != STT_STATE_READY )
		{
			FPRINTF("[Line : %d][%s] stt_cancel invoked callback with invalid current state %s for language %s and type %s, expected state = STT_STATE_READY\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nCurrentState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			deinitialize_setup_with_result_callback();
			return 1;
		}
	}

	deinitialize_setup_with_result_callback();
	return 0;
}

//& purpose Start recording and recognition asynchronously, finish the recording and then cancel processing recognition
//& type: auto
/**
* @testcase				ITc_stt_start_stop_cancel_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Start, stop and then cancel recording & recognition asynchronously
* @scenario				Creates an STT handle\n
* 						Connect the daemon asynchronously\n
* 						Start recording and recognition asynchronously\n
* 						Finish the recording and start recognition processing in engine asynchronously\n
* 						Cancel recording\n
* 						Disconnect the daemon asynchronously\n
* 						Destroys an STT handle
* @apicovered			stt_start, stt_stop, stt_cancel
* @passcase				If starts and stops the recording and cancels the processing
* @failcase				If fails to start or stop the recording or fails to cancel the processing
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_start_stop_cancel_p(void)
{
	START_TEST;

	if ( !initialize_setup_with_result_callback() )
	{
		return 1;
	}

	const char* szRecognitionTypes[] = { STT_RECOGNITION_TYPE_FREE, STT_RECOGNITION_TYPE_FREE_PARTIAL };
	int nRecognitionTypeCount = sizeof(szRecognitionTypes) / sizeof(szRecognitionTypes[0]);
	int nLanguageCounter = 0, nTypeCounter = 0;
	int nRet = 0;

	for ( nTypeCounter=0; nTypeCounter<nRecognitionTypeCount; nTypeCounter++ )
	{
		g_bStateCallbackOccurred = false;

		//Target API
		/**** Start recording and recognition asynchronously ****/
		nRet = stt_start(g_hStt, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] stt_start failed for language %s and type %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter], SttGetError(nRet));
			deinitialize_setup_with_result_callback();
			return 1;
		}

		WAIT_FOR_CALLBACK(STT_STATE_RECORDING);

		if ( !g_bStateCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] stt_start failed to invoke callback for language %s and type %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			deinitialize_setup_with_result_callback();
			return 1;
		}
		else if ( g_nPreviousState != STT_STATE_READY )
		{
			FPRINTF("[Line : %d][%s] stt_start invoked callback with invalid previous state %s for language %s and type %s, expected state = STT_STATE_READY\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nPreviousState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			deinitialize_setup_with_result_callback();
			return 1;
		}
		else if ( g_nCurrentState != STT_STATE_RECORDING )	//This is precondition of stt_stop
		{
			FPRINTF("[Line : %d][%s] stt_start invoked callback with invalid current state %s for language %s and type %s, expected state = STT_STATE_RECORDING\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nCurrentState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			deinitialize_setup_with_result_callback();
			return 1;
		}

		g_bStateCallbackOccurred = false;

		usleep(1000000);
		//Target API
		/**** Finish the recording and start recognition processing in engine asynchronously ****/
		nRet = stt_stop(g_hStt);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] stt_stop failed for language %s and type %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter], SttGetError(nRet));
			stt_cancel(g_hStt);
			deinitialize_setup_with_result_callback();
			return 1;
		}

		//Wait for the state change
		WAIT_FOR_CALLBACK(STT_STATE_PROCESSING);

		if ( !g_bStateCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] stt_stop failed to invoke callback for language %s and type %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			deinitialize_setup_with_result_callback();
			return 1;
		}
		else if ( g_nPreviousState != STT_STATE_RECORDING )
		{
			FPRINTF("[Line : %d][%s] stt_stop invoked callback with invalid previous state %s for language %s and type %s, expected state = STT_STATE_RECORDING\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nPreviousState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			deinitialize_setup_with_result_callback();
			return 1;
		}
		else if ( g_nCurrentState != STT_STATE_PROCESSING )	//This is precondition of stt_cancel
		{
			FPRINTF("[Line : %d][%s] stt_stop invoked callback with invalid current state %s for language %s and type %s, expected state = STT_STATE_PROCESSING\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nCurrentState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			deinitialize_setup_with_result_callback();
			return 1;
		}

		g_bStateCallbackOccurred = false;

		//Target API
		/**** Cancel the recording and start recognition processing in engine asynchronously ****/
		nRet = stt_cancel(g_hStt);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] stt_cancel failed for language %s and type %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter], SttGetError(nRet));
			deinitialize_setup_with_result_callback();
			return 1;
		}

		//Wait for the state change
		WAIT_FOR_CALLBACK(STT_STATE_READY);

		if ( !g_bStateCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] stt_cancel failed to invoke callback for language %s and type %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			deinitialize_setup_with_result_callback();
			return 1;
		}
		else if ( g_nPreviousState != STT_STATE_PROCESSING )
		{
			FPRINTF("[Line : %d][%s] stt_cancel invoked callback with invalid previous state %s for language %s and type %s, expected state = STT_STATE_PROCESSING\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nPreviousState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			deinitialize_setup_with_result_callback();
			return 1;
		}
		else if ( g_nCurrentState != STT_STATE_READY )
		{
			FPRINTF("[Line : %d][%s] stt_cancel invoked callback with invalid current state %s for language %s and type %s, expected state = STT_STATE_READY\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nCurrentState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			deinitialize_setup_with_result_callback();
			return 1;
		}
	}

	deinitialize_setup_with_result_callback();
	return 0;
}

//& purpose Get the current STT state
//& type: auto
/**
* @testcase				ITc_stt_get_state_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Get the current STT state
* @scenario				Creates an STT handle\n
* 						Get the current STT state\n
*							Destroys an STT handle
* @apicovered			stt_create, stt_get_state, stt_destroy
* @passcase				If gets the current STT state successfully
* @failcase				If fails to get the current STT state
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_get_state_p(void)
{
	START_TEST;

	stt_h stt;
	stt_state_e nState;

	//Create STT Handle
	int nRet = stt_create(&stt);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_create", SttGetError(nRet));
	CHECK_HANDLE(stt, "stt_create");

	//Target API
	/**** Get current STT state ****/
	nRet = stt_get_state(stt, &nState);
	PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_get_state", SttGetError(nRet), stt_destroy(stt));
	if ( nState != STT_STATE_CREATED )
	{
		FPRINTF("[Line : %d][%s] stt_get_state returned invalid state %s, expected state = STT_STATE_CREATED\\n", __LINE__, API_NAMESPACE, SttGetState(nState));
		stt_destroy(stt);
		return 1;
	}

	//Destroy STT Handle
	nRet = stt_destroy(stt);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_destroy", SttGetError(nRet));

	return 0;
}

//& purpose Get the default language set by the user
//& type: auto
/**
* @testcase				ITc_stt_get_default_language_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Get the default language set by the user
* @scenario				Creates an STT handle\n
* 						Get the default language set by the user\n
*							Destroys an STT handle
* @apicovered			stt_get_default_language, stt_foreach_supported_languages
* @passcase				If gets the default language set by the user successfully
* @failcase				If fails to get the default language set by the user
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_get_default_language_p(void)
{
	START_TEST;

	g_bSupportedLanguageCallbackOccured = false;
	g_nSupportedLanguageCount = 0;
	g_bCallbackParameterCheck = false;

	int nRet = stt_foreach_supported_languages(g_hStt, stt_supported_language_callback, NULL);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_foreach_supported_languages", SttGetError(nRet));

	if ( !g_bSupportedLanguageCallbackOccured )
	{
		FPRINTF("[Line : %d][%s] Support API stt_foreach_supported_languages failed to invoke stt_supported_language_cb on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	else if(!g_bCallbackParameterCheck)
	{
		return 1;
	}
	else if ( g_nSupportedLanguageCount == 0 )
	{
		FPRINTF("[Line : %d][%s] Support API stt_foreach_supported_languages returned no language on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char* lanugauge;

	//Target API
	/**** Get the default language set by the user ****/
	nRet = stt_get_default_language(g_hStt, &lanugauge);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_get_default_language", SttGetError(nRet));

	bool matching = false;
	int nLanguageCounter;
	for ( nLanguageCounter=0; nLanguageCounter<g_nSupportedLanguageCount; nLanguageCounter++ )
	{
		if ( strcmp(lanugauge, g_szSupportedLanguages[nLanguageCounter]) == 0 )
		{
			FPRINTF("[Line : %d][%s] stt_get_default_language return value exists in supported language list\\n", __LINE__, API_NAMESPACE);
			matching = true;
			break;
		}
	}

	//Free the language variable
	FREE_MEMORY(lanugauge);

	if ( !matching )
	{
		FPRINTF("[Line : %d][%s] stt_get_default_language return value doesn't exist in supported language list\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose Set & get the current engine id
//& type: auto
/**
* @testcase				ITc_stt_set_get_engine_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Set & get the current engine id
* @scenario				Creates an STT handle\n
* 						Set the engine id\n
*							Get the current engine id\n
*							Destroys an STT handle
* @apicovered			stt_set_engine, stt_get_engine, stt_foreach_supported_engines
* @passcase				If sets & gets the current engine id successfully
* @failcase				If fails to set & get the current engine id
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_set_get_engine_p(void)
{
	START_TEST;

	g_bSupportedEngineCallbackOccured = false;
	g_bCallbackParameterCheck = false;
	g_nSupportedEngineCount = 0;

	int nRet = stt_foreach_supported_engines(g_hStt, stt_supported_engine_callback, NULL);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_foreach_supported_engines", SttGetError(nRet));

	if ( !g_bSupportedEngineCallbackOccured )
	{
		FPRINTF("[Line : %d][%s] Support API stt_foreach_supported_engines failed to invoke stt_supported_engineon precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	else if(!g_bCallbackParameterCheck)
	{
		return 1;
	}
	else if ( g_nSupportedEngineCount == 0 )
	{
		FPRINTF("[Line : %d][%s] Support API stt_foreach_supported_engines returned no engine on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	char* pGetEngineId = NULL;
	int nEngineCounter;
	for ( nEngineCounter=0; nEngineCounter < g_nSupportedEngineCount; nEngineCounter++ )
	{
		//Target API
		/**** Set the engine id ****/
		nRet = stt_set_engine(g_hStt, g_szSupportedEngineIDs[nEngineCounter]);
		PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_set_engine", SttGetError(nRet));

		//Target API
		/**** Get the current engine id ****/

		nRet = stt_get_engine(g_hStt, &pGetEngineId);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] stt_get_engine failed for engine id %s and engine name %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedEngineIDs[nEngineCounter], g_szSupportedEngineNames[nEngineCounter], SttGetError(nRet));
			FREE_MEMORY(pGetEngineId);
			return 1;
		}

		if ( strcmp(pGetEngineId, g_szSupportedEngineIDs[nEngineCounter]) != 0 )
		{
			FPRINTF("[Line : %d][%s] stt_get_engine return value %s mismatched with value %s set using stt_set_engine\\n",
				__LINE__, API_NAMESPACE, pGetEngineId, g_szSupportedEngineIDs[nEngineCounter]);
			FREE_MEMORY(pGetEngineId);
			return 1;
		}

		//Free the pGetEngineId variable
		FREE_MEMORY(pGetEngineId);
	}

	return 0;
}

//& purpose Check whether the recognition type is supported
//& type: auto
/**
* @testcase				ITc_stt_is_recognition_type_supported_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Check whether the recognition type is supported
* @scenario				Creates an STT handle\n
*							Connect the daemon asynchronously\n
* 						Check whether the recognition type is supported\n
* 						Disconnect the daemon asynchronously\n
*							Destroys an STT handle
* @apicovered			stt_is_recognition_type_supported
* @passcase				If checks whether the recognition type is supported successfully
* @failcase				If fails to check whether the recognition type is supported
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_is_recognition_type_supported_p(void)
{
	START_TEST;

	if ( !initialize_setup_without_result_callback() )
	{
		return 1;
	}

	const char* szRecognitionTypes[] = { STT_RECOGNITION_TYPE_FREE, STT_RECOGNITION_TYPE_FREE_PARTIAL };
	int nRecognitionTypeCount = sizeof(szRecognitionTypes) / sizeof(szRecognitionTypes[0]);
	int nTypeCounter = 0;
	bool bSupported;
	int nRet  = 0;
	for ( nTypeCounter=0; nTypeCounter<nRecognitionTypeCount; nTypeCounter++ )
	{
		//Target API
		/**** Check whether the recognition type is supported ****/
		nRet = stt_is_recognition_type_supported(g_hStt, szRecognitionTypes[nTypeCounter], &bSupported);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] stt_is_recognition_type_supported failed for recognition type %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, szRecognitionTypes[nTypeCounter], SttGetError(nRet));
			deinitialize_setup_without_result_callback();
			return 1;
		}
		else if((bSupported != true) && (bSupported != false))
		{
			FPRINTF("[Line : %d][%s] stt_is_recognition_type_supported failed for recognition type %s,output value is invalid\\n",
				__LINE__, API_NAMESPACE, szRecognitionTypes[nTypeCounter]);
			deinitialize_setup_without_result_callback();
			return 1;
		}
		else
		{
#if DEBUG
			FPRINTF("[Line : %d][%s] stt_is_recognition_type_supported returned %s for recognition type %s\\n",
				__LINE__, API_NAMESPACE, (bSupported ? "true" : "false"), szRecognitionTypes[nTypeCounter]);
#endif
		}
	}

	deinitialize_setup_without_result_callback();
	return 0;
}

//& purpose Get the microphone volume during recording
//& type: auto
/**
* @testcase				ITc_stt_get_recording_volume_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Get the microphone volume during recording
* @scenario				Creates an STT handle\n
* 						Connect the daemon asynchronously\n
* 						Start recording and recognition asynchronously\n
* 						Finish the recording and start recognition processing in engine asynchronously\n
*							Get the microphone volume during recording\n
* 						Disconnect the daemon asynchronously\n
* 						Destroys an STT handle\n
* 						Finish recording
* @apicovered			stt_start, stt_get_recording_volume, stt_cancel
* @passcase				If gets the microphone volume during recording successfully
* @failcase				If fails to get the microphone volume during recording
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_get_recording_volume_p(void)
{
	START_TEST;

	if ( !initialize_setup_with_result_callback() )
	{
		return 1;
	}

	const char* szRecognitionTypes[] = { STT_RECOGNITION_TYPE_FREE, STT_RECOGNITION_TYPE_FREE_PARTIAL };
	int nRecognitionTypeCount = sizeof(szRecognitionTypes) / sizeof(szRecognitionTypes[0]);
	int nLanguageCounter = 0, nTypeCounter = 0;
	float fVolume = -1.0;
	int nRet = 0;

	for ( nTypeCounter=0; nTypeCounter<nRecognitionTypeCount; nTypeCounter++ )
	{
		//Start recording and recognition asynchronously
		g_bStateCallbackOccurred = false;
		nRet = stt_start(g_hStt, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Support API stt_start failed for language %s and type %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter], SttGetError(nRet));
			deinitialize_setup_with_result_callback();
			return 1;
		}

		WAIT_FOR_CALLBACK(STT_STATE_RECORDING);

		if ( !g_bStateCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] Support API stt_start failed to invoke callback for language %s and type %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			deinitialize_setup_with_result_callback();
			return 1;
		}
		else if ( g_nPreviousState != STT_STATE_READY )
		{
			FPRINTF("[Line : %d][%s] Support API stt_start invoked callback with invalid previous state %s for language %s and type %s, expected state = STT_STATE_READY\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nPreviousState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			deinitialize_setup_with_result_callback();
			return 1;
		}
		else if ( g_nCurrentState != STT_STATE_RECORDING )	//This is precondition of stt_get_recording_volume
		{
			FPRINTF("[Line : %d][%s] Support API stt_start invoked callback with invalid current state %s for language %s and type %s, expected state = STT_STATE_RECORDING\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nCurrentState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			deinitialize_setup_with_result_callback();
			return 1;
		}

		//Target API
		/**** Get the microphone volume during recording ****/
		nRet = stt_get_recording_volume(g_hStt, &fVolume);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] stt_get_recording_volume failed for language %s and type %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter], SttGetError(nRet));
			stt_cancel(g_hStt);
			deinitialize_setup_with_result_callback();
			return 1;
		}
		else if(fVolume == -1.0)
		{
			FPRINTF("[Line : %d][%s] stt_get_recording_volume failed for language %s and type %s, volume is invalid\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			deinitialize_setup_with_result_callback();
			return 1;
		}

		//Cancel Recording
		nRet = stt_cancel(g_hStt);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Support API stt_cancel failed in postcondition for language %s and type %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter], SttGetError(nRet));
			deinitialize_setup_with_result_callback();
			return 1;
		}

		//Wait for the state change
		WAIT_FOR_CALLBACK(STT_STATE_READY);

		if ( !g_bStateCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] stt_cancel failed to invoke callback for language %s and type %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			deinitialize_setup_with_result_callback();
			return 1;
		}
		else if ( g_nPreviousState != STT_STATE_RECORDING )
		{
			FPRINTF("[Line : %d][%s] stt_cancel invoked callback with invalid previous state %s for language %s and type %s, expected state = STT_STATE_RECORDING\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nPreviousState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			deinitialize_setup_with_result_callback();
			return 1;
		}
		else if ( g_nCurrentState != STT_STATE_READY )
		{
			FPRINTF("[Line : %d][%s] stt_cancel invoked callback with invalid current state %s for language %s and type %s, expected state = STT_STATE_READY\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nCurrentState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			deinitialize_setup_with_result_callback();
			return 1;
		}
	}

	deinitialize_setup_with_result_callback();
	return 0;
}

//& purpose Set the silence detection
//& type: auto
/**
* @testcase				ITc_stt_set_silence_detection_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Set the silence detection
* @scenario				Creates an STT handle\n
*							Connect the daemon asynchronously\n
* 						Set the silence detection\n
* 						Disconnect the daemon asynchronously\n
*							Destroys an STT handle
* @apicovered			stt_set_silence_detection
* @passcase				If sets the silence detection successfully
* @failcase				If fails to set the silence detection
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_set_silence_detection_p(void)
{
	START_TEST;

	if ( !initialize_setup_without_result_callback() )
	{
		return 1;
	}

	stt_option_silence_detection_e nDetectionOptions[] = { STT_OPTION_SILENCE_DETECTION_FALSE, STT_OPTION_SILENCE_DETECTION_TRUE, STT_OPTION_SILENCE_DETECTION_AUTO };
	int nDetectionOptionCount = sizeof(nDetectionOptions) / sizeof(nDetectionOptions[0]);
	int nDetectionOptionCounter = 0;
	int nRet = 0;
	for ( nDetectionOptionCounter=0; nDetectionOptionCounter<nDetectionOptionCount; nDetectionOptionCounter++ )
	{
		//Target API
		/**** Set the silence detection ****/
		nRet = stt_set_silence_detection(g_hStt, nDetectionOptions[nDetectionOptionCounter]);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] stt_set_silence_detection failed for option type %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, SttGetOptionForSilenceDetection(nDetectionOptions[nDetectionOptionCounter]), SttGetError(nRet));
			deinitialize_setup_without_result_callback();
			return 1;
		}
	}

	deinitialize_setup_without_result_callback();
	return 0;
}

//& purpose Set and unset the sound to start recording
//& type: auto
/**
* @testcase				ITc_stt_set_unset_start_sound_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Set and unset the sound to start recording
* @scenario				Set the sound to start recording\n
* 						Unset the sound to start recording\n
* @apicovered			stt_set_start_sound, stt_unset_start_sound
* @passcase				If sets and unsets the sound to start recording successfully
* @failcase				If fails to set and unset the sound to start recording
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_set_unset_start_sound_p(void)
{
	START_TEST;

	//Get the application's data path
	char pPath[PATH_LEN] = {0,};
	if ( false == SttAppendToAppDataPath(START_SOUND, pPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	if ( !initialize_setup_with_result_callback() )
	{
		return 1;
	}

	//Target API
	/**** Set the sound to start recording ***/
	int nRet = stt_set_start_sound(g_hStt, pPath);
	PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_set_start_sound", SttGetError(nRet), deinitialize_setup_with_result_callback());

	//Target API
	/**** Unset the sound to start recording ****/
	nRet = stt_unset_start_sound(g_hStt);
	PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_unset_start_sound", SttGetError(nRet), deinitialize_setup_with_result_callback());

	deinitialize_setup_with_result_callback();
	return 0;
}

//& purpose Set and unset the sound to stop recording
//& type: auto
/**
* @testcase				ITc_stt_set_unset_stop_sound_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Set and unset the sound to stop recording
* @scenario				Set the sound to stop recording\n
* 						Unset the sound to stop recording
* @apicovered			stt_set_stop_sound , stt_unset_stop_sound
* @passcase				If sets and unsets the sound to stop recording successfully
* @failcase				If fails to set and unset the sound to stop recording
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_set_unset_stop_sound_p(void)
{
	START_TEST;

	//Get the application's data path
	char pPath[PATH_LEN] = {0,};
	if ( false == SttAppendToAppDataPath(STOP_SOUND, pPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	if ( !initialize_setup_with_result_callback() )
	{
		return 1;
	}

	//Target API
	/**** Set the sound to stop recording ***/
	int nRet = stt_set_stop_sound(g_hStt, pPath);
	PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_set_stop_sound", SttGetError(nRet), deinitialize_setup_with_result_callback());

	//Target API
	/**** Unset the sound to stop recording ****/
	nRet = stt_unset_stop_sound(g_hStt);
	PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_unset_stop_sound", SttGetError(nRet), deinitialize_setup_with_result_callback());

	deinitialize_setup_with_result_callback();
	return 0;
}

//& purposeRegister a callback function to be called when STT state changes and unregister it
//& type: auto
/**
* @testcase				ITc_stt_set_unset_state_changed_cb_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Register a callback function to be called when STT state changes and unregister it
* @scenario				Register a callback function to be called when STT state changes\n
* 						Unregister the callback function
* @apicovered			stt_prepare, stt_set_state_changed_cb, stt_unset_state_changed_cb, stt_unprepare
* @passcase				If registers and unregisters the callback function successfully and callback is invoked after stt_prepare and stt_unprepare
* @failcase				If fails to register and unregister the callback function or callback is not invoked after stt_prepare and stt_unprepare
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_set_unset_state_changed_cb_p(void)
{
	START_TEST;

	//Target API
	/****Register a callback function to be called when STT state changes ***/
	int nRet = stt_set_state_changed_cb(g_hStt, stt_state_changed_callback, NULL);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_set_state_changed_cb", SttGetError(nRet));

	//Connect the STT daemon asynchronously to invoke callback
	g_bStateCallbackOccurred = false;
	nRet = stt_prepare(g_hStt);
	PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_prepare", SttGetError(nRet), stt_unset_state_changed_cb(g_hStt));

	WAIT_FOR_CALLBACK(STT_STATE_READY);

	if ( !g_bStateCallbackOccurred )
	{
		FPRINTF("[Line : %d][%s] stt_set_state_changed_cb failed to invoke callback\\n", __LINE__, API_NAMESPACE);
		stt_unprepare(g_hStt);
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}
	else if ( g_nPreviousState != STT_STATE_CREATED )
	{
		FPRINTF("[Line : %d][%s] stt_set_state_changed_cb invoked callback with invalid previous state %s, expected state = STT_STATE_CREATED\\n",
			__LINE__, API_NAMESPACE, SttGetState(g_nPreviousState));
		stt_unprepare(g_hStt);
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}
	else if ( g_nCurrentState != STT_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] stt_set_state_changed_cb invoked callback with invalid current state %s, expected state = STT_STATE_READY\\n",
			__LINE__, API_NAMESPACE, SttGetState(g_nCurrentState));
		stt_unprepare(g_hStt);
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}

	//Disconnect the STT daemon asynchronously to check callback invoke for stt_unprepare
	g_bStateCallbackOccurred = false;
	nRet = stt_unprepare(g_hStt);
	PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_unprepare", SttGetError(nRet), stt_unset_state_changed_cb(g_hStt));

	WAIT_FOR_CALLBACK(STT_STATE_CREATED);

	if ( !g_bStateCallbackOccurred )
	{
		FPRINTF("[Line : %d][%s] stt_unprepare failed to invoke callback\\n", __LINE__, API_NAMESPACE);
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}
	else if ( g_nPreviousState != STT_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] stt_unprepare invoked callback with invalid previous state %s, expected state = STT_STATE_READY\\n", __LINE__, API_NAMESPACE, SttGetState(g_nPreviousState));
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}
	else if ( g_nCurrentState != STT_STATE_CREATED )
	{
		FPRINTF("[Line : %d][%s] stt_unprepare invoked callback with invalid current state %s, expected state = STT_STATE_CREATED\\n", __LINE__, API_NAMESPACE, SttGetState(g_nCurrentState));
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}

	//Target API
	/**** Unregister the callback function ***/
	nRet = stt_unset_state_changed_cb(g_hStt);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_unset_state_changed_cb", SttGetError(nRet));

	return 0;
}

//& purposeRegister a callback function to get the recognition result and unregister it
//& type: auto
/**
* @testcase				ITc_stt_set_unset_recognition_result_cb_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Registers a callback function to get the recognition result and unregister it
* @scenario				Register callback function to get the recognition result\n
* 						Unregister the callback function
* @apicovered			stt_set_recognition_result_cb, stt_unset_recognition_result_cb, stt_start
* @passcase				If registers and unregisters the callback function successfully
* @failcase				If fails to register and unregister the callback function
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_set_unset_recognition_result_cb_p(void)
{
	START_TEST;

	if ( !initialize_setup_without_result_callback() )
	{
		return 1;
	}

	const char* szRecognitionTypes[] = { STT_RECOGNITION_TYPE_FREE, STT_RECOGNITION_TYPE_FREE_PARTIAL };
	int nRecognitionTypeCount = sizeof(szRecognitionTypes) / sizeof(szRecognitionTypes[0]);
	int nLanguageCounter = 0, nTypeCounter = 0;
	int nRet = 0;

	for ( nTypeCounter=0; nTypeCounter<nRecognitionTypeCount; nTypeCounter++ )
	{
		g_bStateCallbackOccurred = false;
		//Target API
		/**** Disconnect the STT daemon asynchronously ****/
		nRet = stt_unprepare(g_hStt);
		PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_unprepare", SttGetError(nRet), stt_unset_state_changed_cb(g_hStt));

		WAIT_FOR_CALLBACK(STT_STATE_CREATED);

		if ( !g_bStateCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] stt_unprepare failed to invoke callback\\n", __LINE__, API_NAMESPACE);
			stt_unset_state_changed_cb(g_hStt);
			return 1;
		}
		else if ( g_nPreviousState != STT_STATE_READY )
		{
			FPRINTF("[Line : %d][%s] stt_unprepare invoked callback with invalid previous state %s, expected state = STT_STATE_READY\\n", __LINE__, API_NAMESPACE, SttGetState(g_nPreviousState));
			stt_unset_state_changed_cb(g_hStt);
			return 1;
		}
		else if ( g_nCurrentState != STT_STATE_CREATED )
		{
			FPRINTF("[Line : %d][%s] stt_unprepare invoked callback with invalid current state %s, expected state = STT_STATE_CREATED\\n", __LINE__, API_NAMESPACE, SttGetState(g_nCurrentState));
			stt_unset_state_changed_cb(g_hStt);
			return 1;
		}

		//Target API
		/****Register a callback function to get the recognition result ***/
		nRet = stt_set_recognition_result_cb(g_hStt, stt_recognition_result_callback, NULL);
		PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_set_recognition_result_cb", SttGetError(nRet), deinitialize_setup_without_result_callback());

		g_bStateCallbackOccurred = false;
		//Target API
		/**** Connect the STT daemon asynchronously ****/
		nRet = stt_prepare(g_hStt);
		PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_prepare", SttGetError(nRet), stt_unset_state_changed_cb(g_hStt));

		WAIT_FOR_CALLBACK(STT_STATE_READY);


		if ( !g_bStateCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] stt_prepare failed to invoke callback\\n", __LINE__, API_NAMESPACE);
			stt_unprepare(g_hStt);
			stt_unset_state_changed_cb(g_hStt);
			return 1;
		}
		else if(!g_bCallbackParameterCheck)
		{
			stt_unprepare(g_hStt);
			stt_unset_state_changed_cb(g_hStt);
			return 1;
		}
		else if ( g_nPreviousState != STT_STATE_CREATED )
		{
			FPRINTF("[Line : %d][%s] stt_prepare invoked callback with invalid previous state %s, expected state = STT_STATE_CREATED\\n", __LINE__, API_NAMESPACE, SttGetState(g_nPreviousState));
			stt_unprepare(g_hStt);
			stt_unset_state_changed_cb(g_hStt);
			return 1;
		}
		else if ( g_nCurrentState != STT_STATE_READY )	//This is precondition of stt_unprepare
		{
			FPRINTF("[Line : %d][%s] stt_prepare invoked callback with invalid current state %s, expected state = STT_STATE_READY\\n", __LINE__, API_NAMESPACE, SttGetState(g_nCurrentState));
			stt_unprepare(g_hStt);
			stt_unset_state_changed_cb(g_hStt);
			return 1;
		}

		nRet = stt_set_private_data(g_hStt, "stt_verification", "true");
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] stt_set_private_data failed for TC mode, error returned = %s\\n",
				__LINE__, API_NAMESPACE,  SttGetError(nRet));
			stt_unprepare(g_hStt);
			stt_unset_state_changed_cb(g_hStt);
			return 1;
		}

		//Start recording and recognition asynchronously to invoke callback
		g_bStateCallbackOccurred = false;
		g_bCallbackParameterCheck = false;
		nRet = stt_start(g_hStt, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Support API stt_start failed for language %s and type %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter], SttGetError(nRet));
			stt_unset_recognition_result_cb(g_hStt);
			deinitialize_setup_without_result_callback();
			return 1;
		}

		//Wait for the state change
		WAIT_FOR_CALLBACK(STT_STATE_RECORDING);

		if ( !g_bStateCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] Support API stt_start failed to invoke callback for language %s and type %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			stt_unset_recognition_result_cb(g_hStt);
			deinitialize_setup_without_result_callback();
			return 1;
		}
		else if ( !g_bCallbackParameterCheck )
		{
			stt_cancel(g_hStt);
			stt_unset_recognition_result_cb(g_hStt);
			deinitialize_setup_without_result_callback();
			return 1;
		}
		else if ( g_nPreviousState != STT_STATE_READY )
		{
			FPRINTF("[Line : %d][%s] Support API stt_start invoked callback with invalid previous state %s for language %s and type %s, expected state = STT_STATE_READY\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nPreviousState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			stt_unset_recognition_result_cb(g_hStt);
			deinitialize_setup_without_result_callback();
			return 1;
		}
		else if ( g_nCurrentState != STT_STATE_RECORDING )	//This is precondition of stt_stop
		{
			FPRINTF("[Line : %d][%s] Support API stt_start invoked callback with invalid current state %s for language %s and type %s, expected state = STT_STATE_RECORDING\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nCurrentState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			stt_unset_recognition_result_cb(g_hStt);
			deinitialize_setup_without_result_callback();
			return 1;
		}

		g_bStateCallbackOccurred = false;
		g_bResultCallbackOccurred = false;

		usleep(1000000);
		//Finish the recording and start recognition processing in engine asynchronously to invoke result callback
		nRet = stt_stop(g_hStt);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Support API stt_stop failed for language %s and type %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter], SttGetError(nRet));
			stt_unset_recognition_result_cb(g_hStt);
			deinitialize_setup_without_result_callback();
			return 1;
		}

		//Wait for the state change
		WAIT_FOR_CALLBACK(STT_STATE_PROCESSING);

		if ( !g_bStateCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] Support API stt_stop failed to invoke callback for language %s and type %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_unset_recognition_result_cb(g_hStt);
			deinitialize_setup_without_result_callback();
			return 1;
		}
		else if ( g_nPreviousState != STT_STATE_RECORDING )
		{
			FPRINTF("[Line : %d][%s] Support API stt_stop invoked callback with invalid previous state %s for language %s and type %s, expected state = STT_STATE_RECORDING\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nPreviousState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_unset_recognition_result_cb(g_hStt);
			deinitialize_setup_without_result_callback();
			return 1;
		}
		else if ( g_nCurrentState != STT_STATE_PROCESSING )
		{
			FPRINTF("[Line : %d][%s] Support API stt_stop invoked callback with invalid current state %s for language %s and type %s, expected state = STT_STATE_PROCESSING\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nCurrentState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_unset_recognition_result_cb(g_hStt);
			deinitialize_setup_without_result_callback();
			return 1;
		}

		//Wait for the result to complete
		WAIT_FOR_CALLBACK(STT_STATE_READY);

		if ( !g_bResultCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] stt_set_recognition_result_cb failed to invoke result callback for language %s and type %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_unset_recognition_result_cb(g_hStt);
			deinitialize_setup_without_result_callback();
			return 1;
		}
		else if ( g_nResultEvent == STT_RESULT_EVENT_ERROR )
		{
			FPRINTF("[Line : %d][%s] stt_set_recognition_result_cb invoked result callback with invalid result %s for language %s and type %s\\n",
				__LINE__, API_NAMESPACE, SttGetResultEvent(g_nResultEvent), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
		}

		g_bStateCallbackOccurred = false;
		//Target API
		/**** Disconnect the STT daemon asynchronously ****/
		nRet = stt_unprepare(g_hStt);
		PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_unprepare", SttGetError(nRet), stt_unset_state_changed_cb(g_hStt));

		WAIT_FOR_CALLBACK(STT_STATE_CREATED);

		if ( !g_bStateCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] stt_unprepare failed to invoke callback\\n", __LINE__, API_NAMESPACE);
			stt_unset_state_changed_cb(g_hStt);
			return 1;
		}
		else if ( g_nPreviousState != STT_STATE_READY )
		{
			FPRINTF("[Line : %d][%s] stt_unprepare invoked callback with invalid previous state %s, expected state = STT_STATE_READY\\n", __LINE__, API_NAMESPACE, SttGetState(g_nPreviousState));
			stt_unset_state_changed_cb(g_hStt);
			return 1;
		}
		else if ( g_nCurrentState != STT_STATE_CREATED )
		{
			FPRINTF("[Line : %d][%s] stt_unprepare invoked callback with invalid current state %s, expected state = STT_STATE_CREATED\\n", __LINE__, API_NAMESPACE, SttGetState(g_nCurrentState));
			stt_unset_state_changed_cb(g_hStt);
			return 1;
		}

		//Target API
		/**** Unregister the callback function ***/
		nRet = stt_unset_recognition_result_cb(g_hStt);
		PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_unset_recognition_result_cb", SttGetError(nRet), deinitialize_setup_without_result_callback());

		g_bStateCallbackOccurred = false;
		//Target API
		/**** Connect the STT daemon asynchronously ****/
		nRet = stt_prepare(g_hStt);
		PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_prepare", SttGetError(nRet), stt_unset_state_changed_cb(g_hStt));

		WAIT_FOR_CALLBACK(STT_STATE_READY);


		if ( !g_bStateCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] stt_prepare failed to invoke callback\\n", __LINE__, API_NAMESPACE);
			stt_unprepare(g_hStt);
			stt_unset_state_changed_cb(g_hStt);
			return 1;
		}
		else if(!g_bCallbackParameterCheck)
		{
			stt_unprepare(g_hStt);
			stt_unset_state_changed_cb(g_hStt);
			return 1;
		}
		else if ( g_nPreviousState != STT_STATE_CREATED )
		{
			FPRINTF("[Line : %d][%s] stt_prepare invoked callback with invalid previous state %s, expected state = STT_STATE_CREATED\\n", __LINE__, API_NAMESPACE, SttGetState(g_nPreviousState));
			stt_unprepare(g_hStt);
			stt_unset_state_changed_cb(g_hStt);
			return 1;
		}
		else if ( g_nCurrentState != STT_STATE_READY )	//This is precondition of stt_unprepare
		{
			FPRINTF("[Line : %d][%s] stt_prepare invoked callback with invalid current state %s, expected state = STT_STATE_READY\\n", __LINE__, API_NAMESPACE, SttGetState(g_nCurrentState));
			stt_unprepare(g_hStt);
			stt_unset_state_changed_cb(g_hStt);
			return 1;
		}

		nRet = stt_set_private_data(g_hStt, "stt_verification", "true");
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] stt_set_private_data failed for TC mode, error returned = %s\\n",
				__LINE__, API_NAMESPACE,  SttGetError(nRet));
			stt_unprepare(g_hStt);
			stt_unset_state_changed_cb(g_hStt);
			return 1;
		}

		//Start recording and recognition asynchronously to invoke callback
		g_bStateCallbackOccurred = false;
		nRet = stt_start(g_hStt, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Support API stt_start failed for language %s and type %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter], SttGetError(nRet));
			deinitialize_setup_without_result_callback();
			return 1;
		}

		//Wait for the state change
		WAIT_FOR_CALLBACK(STT_STATE_RECORDING);
		//usleep(1000000);

		if ( !g_bStateCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] Support API stt_start failed to invoke callback for language %s and type %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			deinitialize_setup_without_result_callback();
			return 1;
		}
		else if ( g_nPreviousState != STT_STATE_READY )
		{
			FPRINTF("[Line : %d][%s] Support API stt_start invoked callback with invalid previous state %s for language %s and type %s, expected state = STT_STATE_READY\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nPreviousState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			deinitialize_setup_without_result_callback();
			return 1;
		}
		else if ( g_nCurrentState != STT_STATE_RECORDING )	//This is precondition of stt_stop
		{
			FPRINTF("[Line : %d][%s] Support API stt_start invoked callback with invalid current state %s for language %s and type %s, expected state = STT_STATE_RECORDING\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nCurrentState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			stt_cancel(g_hStt);
			deinitialize_setup_without_result_callback();
			return 1;
		}

		g_bStateCallbackOccurred = false;
		g_bResultCallbackOccurred = false;

		usleep(1000000);
		//Finish the recording and start recognition processing in engine asynchronously to invoke result callback
		nRet = stt_stop(g_hStt);
		if ( nRet != STT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Support API stt_stop failed for language %s and type %s, error returned = %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter], SttGetError(nRet));
			deinitialize_setup_without_result_callback();
			return 1;
		}

		//Wait for the state change
		WAIT_FOR_CALLBACK(STT_STATE_PROCESSING);

		if ( !g_bStateCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] Support API stt_stop failed to invoke callback for language %s and type %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			deinitialize_setup_without_result_callback();
			return 1;
		}
		else if ( g_nPreviousState != STT_STATE_RECORDING )
		{
			FPRINTF("[Line : %d][%s] Support API stt_stop invoked callback with invalid previous state %s for language %s and type %s, expected state = STT_STATE_RECORDING\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nPreviousState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			deinitialize_setup_without_result_callback();
			return 1;
		}
		else if ( g_nCurrentState != STT_STATE_PROCESSING )
		{
			FPRINTF("[Line : %d][%s] Support API stt_stop invoked callback with invalid current state %s for language %s and type %s, expected state = STT_STATE_PROCESSING\\n",
				__LINE__, API_NAMESPACE, SttGetState(g_nCurrentState), g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			deinitialize_setup_without_result_callback();
			return 1;
		}

		//Wait for the result to complete
		WAIT_FOR_CALLBACK(STT_STATE_READY);

		if ( g_bResultCallbackOccurred )
		{
			FPRINTF("[Line : %d][%s] stt_unset_recognition_result_cb failed to stop result callback invocation for language %s and type %s\\n",
				__LINE__, API_NAMESPACE, g_szSupportedLanguages[nLanguageCounter], szRecognitionTypes[nTypeCounter]);
			deinitialize_setup_without_result_callback();
			return 1;
		}
	}

	deinitialize_setup_without_result_callback();
	return 0;
}

//& purposeRegister a callback function to detect the default language change and unregister it
//& type: auto
/**
* @testcase				ITc_stt_set_unset_default_language_changed_cb_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Register a callback function to detect the default language change and unregister it
* @scenario				Register a callback function to detect the default language change\n
* 						Unregister the callback function
* @apicovered			stt_set_default_language_changed_cb, stt_unset_default_language_changed_cb
* @passcase				If registers and unregisters the callback function successfully
* @failcase				If fails to register and unregister the callback function
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_set_unset_default_language_changed_cb_p(void)
{
	START_TEST;

	//Target API
	/****Register a callback function to detect the default language change ***/
	int nRet = stt_set_default_language_changed_cb(g_hStt, stt_default_language_changed_callback, NULL);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_set_default_language_changed_cb", SttGetError(nRet));

	//Target API
	/**** Unregister the callback function ***/
	nRet = stt_unset_default_language_changed_cb(g_hStt);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_unset_default_language_changed_cb", SttGetError(nRet));

	return 0;
}

//& purposeRegister a callback function to be called when an error occurred and then unregister the callback
//& type: auto
/**
* @testcase				ITc_stt_set_unset_error_cb_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Register a callback function to be called when an error occurred and then unregister the callback
* @scenario				Register a callback function to be called when an error occurred\n
* 						Unregister the callback function
* @apicovered			stt_set_error_cb, stt_unset_error_cb
* @passcase				If registers and unregisters the callback function successfully
* @failcase				If fails to register and unregister the callback function
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_set_unset_error_cb_p(void)
{
	START_TEST;

	//Target API
	/****Register a callback function to be called when an error occurred ***/
	int nRet = stt_set_error_cb(g_hStt, stt_error_callback, NULL);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_set_error_cb", SttGetError(nRet));

	//Target API
	/**** Unregister the callback function ***/
	nRet = stt_unset_error_cb(g_hStt);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_unset_error_cb", SttGetError(nRet));

	return 0;
}

//& purpose Retrieve the time stamp of the current recognition result using the callback function
//& type: auto
/**
* @testcase				ITc_stt_foreach_detailed_result_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Retrieve the time stamp of the current recognition result using the callback function
* @scenario				Retrieve the time stamp of the current recognition result using the callback function
* @apicovered			stt_unset_recognition_result_cb, stt_unprepare, stt_unset_state_changed_cb, stt_set_recognition_result_cb, stt_prepare, stt_start, stt_cancel, stt_stop
* @passcase				If retrieves the time stamp of the current recognition result using the callback function
* @failcase				If fails to retrieve the time stamp of the current recognition result using the callback function
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_foreach_detailed_result_p(void)
{
	START_TEST;

	if ( !initialize_setup_without_result_callback() )
	{
		return 1;
	}

	g_bStateCallbackOccurred = false;

	//Target API
	/**** Disconnect the STT daemon asynchronously ****/
	int nRet = stt_unprepare(g_hStt);
	PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_unprepare", SttGetError(nRet), stt_unset_state_changed_cb(g_hStt));

	WAIT_FOR_CALLBACK(STT_STATE_CREATED);

	if ( !g_bStateCallbackOccurred )
	{
		FPRINTF("[Line : %d][%s] stt_unprepare failed to invoke callback\\n", __LINE__, API_NAMESPACE);
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}
	else if ( g_nPreviousState != STT_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] stt_unprepare invoked callback with invalid previous state %s, expected state = STT_STATE_READY\\n", __LINE__, API_NAMESPACE, SttGetState(g_nPreviousState));
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}
	else if ( g_nCurrentState != STT_STATE_CREATED )
	{
		FPRINTF("[Line : %d][%s] stt_unprepare invoked callback with invalid current state %s, expected state = STT_STATE_CREATED\\n", __LINE__, API_NAMESPACE, SttGetState(g_nCurrentState));
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}

	//Register a callback function to get the recognition result
	nRet = stt_set_recognition_result_cb(g_hStt, stt_recognition_result_callback_check_detailed_result, NULL);
	if ( nRet != STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Support API stt_set_recognition_result_cb failed on precondition, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
		deinitialize_setup_without_result_callback();
		return 1;
	}

	g_bStateCallbackOccurred = false;
	//Target API
	/**** Connect the STT daemon asynchronously ****/
	nRet = stt_prepare(g_hStt);
	PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_prepare", SttGetError(nRet), stt_unset_state_changed_cb(g_hStt));

	WAIT_FOR_CALLBACK(STT_STATE_READY);


	if ( !g_bStateCallbackOccurred )
	{
		FPRINTF("[Line : %d][%s] stt_prepare failed to invoke callback\\n", __LINE__, API_NAMESPACE);
		stt_unprepare(g_hStt);
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}
	else if(!g_bCallbackParameterCheck)
	{
		stt_unprepare(g_hStt);
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}
	else if ( g_nPreviousState != STT_STATE_CREATED )
	{
		FPRINTF("[Line : %d][%s] stt_prepare invoked callback with invalid previous state %s, expected state = STT_STATE_CREATED\\n", __LINE__, API_NAMESPACE, SttGetState(g_nPreviousState));
		stt_unprepare(g_hStt);
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}
	else if ( g_nCurrentState != STT_STATE_READY )	//This is precondition of stt_unprepare
	{
		FPRINTF("[Line : %d][%s] stt_prepare invoked callback with invalid current state %s, expected state = STT_STATE_READY\\n", __LINE__, API_NAMESPACE, SttGetState(g_nCurrentState));
		stt_unprepare(g_hStt);
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}

	nRet = stt_set_private_data(g_hStt, "stt_verification", "true");
	if ( nRet != STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] stt_set_private_data failed for TC mode, error returned = %s\\n",
			__LINE__, API_NAMESPACE,  SttGetError(nRet));
		stt_unprepare(g_hStt);
		stt_unset_state_changed_cb(g_hStt);
		return 1;
	}

	//Start recording and recognition asynchronously to invoke callback
	g_bStateCallbackOccurred = false;
	g_bCallbackParameterCheck = false;
	nRet = stt_start(g_hStt, "en_US", STT_RECOGNITION_TYPE_FREE);
	if ( nRet != STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Support API stt_start failed on precondition, error returned = %s\\n", __LINE__, API_NAMESPACE,  SttGetError(nRet));
		stt_unset_recognition_result_cb(g_hStt);
		deinitialize_setup_without_result_callback();
		return 1;
	}

	//Wait for the state change
	WAIT_FOR_CALLBACK(STT_STATE_RECORDING);

	if ( !g_bStateCallbackOccurred )
	{
		FPRINTF("[Line : %d][%s] Support API stt_start failed to invoke callback\\n", __LINE__, API_NAMESPACE);
		stt_cancel(g_hStt);
		stt_unset_recognition_result_cb(g_hStt);
		deinitialize_setup_without_result_callback();
		return 1;
	}
	else if ( !g_bCallbackParameterCheck )
	{
		stt_cancel(g_hStt);
		stt_unset_recognition_result_cb(g_hStt);
		deinitialize_setup_without_result_callback();
		return 1;
	}
	else if ( g_nPreviousState != STT_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] Support API stt_start invoked callback with invalid previous state %s, expected state = STT_STATE_READY\\n", __LINE__, API_NAMESPACE, SttGetState(g_nPreviousState));
		stt_cancel(g_hStt);
		stt_unset_recognition_result_cb(g_hStt);
		deinitialize_setup_without_result_callback();
		return 1;
	}
	else if ( g_nCurrentState != STT_STATE_RECORDING )	//This is precondition of stt_stop
	{
		FPRINTF("[Line : %d][%s] Support API stt_start invoked callback with invalid current state %s, expected state = STT_STATE_RECORDING\\n", __LINE__, API_NAMESPACE, SttGetState(g_nCurrentState));
		stt_cancel(g_hStt);
		stt_unset_recognition_result_cb(g_hStt);
		deinitialize_setup_without_result_callback();
		return 1;
	}

	g_bStateCallbackOccurred = false;
	g_bResultCallbackOccurred = false;

	usleep(1000000);
	//Finish the recording and start recognition processing in engine asynchronously to invoke result callback
	nRet = stt_stop(g_hStt);
	if ( nRet != STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Support API stt_stop failed, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
		stt_unset_recognition_result_cb(g_hStt);
		deinitialize_setup_without_result_callback();
		return 1;
	}

	//Wait for the state change
	WAIT_FOR_CALLBACK(STT_STATE_PROCESSING);

	if ( !g_bStateCallbackOccurred )
	{
		FPRINTF("[Line : %d][%s] Support API stt_stop failed to invoke callback\\n", __LINE__, API_NAMESPACE);
		stt_unset_recognition_result_cb(g_hStt);
		deinitialize_setup_without_result_callback();
		return 1;
	}
	else if ( g_nPreviousState != STT_STATE_RECORDING )
	{
		FPRINTF("[Line : %d][%s] Support API stt_stop invoked callback with invalid previous state %s, expected state = STT_STATE_RECORDING\\n", __LINE__, API_NAMESPACE, SttGetState(g_nPreviousState));
		stt_unset_recognition_result_cb(g_hStt);
		deinitialize_setup_without_result_callback();
		return 1;
	}
	else if ( g_nCurrentState != STT_STATE_PROCESSING )
	{
		FPRINTF("[Line : %d][%s] Support API stt_stop invoked callback with invalid current state %s, expected state = STT_STATE_PROCESSING\\n", __LINE__, API_NAMESPACE, SttGetState(g_nCurrentState));
		stt_unset_recognition_result_cb(g_hStt);
		deinitialize_setup_without_result_callback();
		return 1;
	}

	//Wait for the result to complete
	WAIT_FOR_CALLBACK(STT_STATE_READY);

	if ( !g_bResultCallbackOccurred )
	{
		FPRINTF("[Line : %d][%s] stt_set_recognition_result_cb failed to invoke result callback\\n", __LINE__, API_NAMESPACE);
		stt_unset_recognition_result_cb(g_hStt);
		deinitialize_setup_without_result_callback();
		return 1;
	}
	else if ( g_nResultEvent == STT_RESULT_EVENT_ERROR )
	{
		FPRINTF("[Line : %d][%s] stt_set_recognition_result_cb invoked result callback with invalid result %s\\n", __LINE__, API_NAMESPACE, SttGetResultEvent(g_nResultEvent));
	}

	//Unregister the callback function
	nRet = stt_unset_recognition_result_cb(g_hStt);
	if ( nRet != STT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Support API stt_unset_recognition_result_cb failed on postcondition, error returned = %s\\n", __LINE__, API_NAMESPACE, SttGetError(nRet));
		deinitialize_setup_without_result_callback();
	}

	deinitialize_setup_without_result_callback();
	return 0;
}

//& purpose Retrieves supported engine information using a callback function
//& type: auto
/**
* @testcase				ITc_stt_foreach_supported_engines_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Retrieve supported engine information using a callback function
* @scenario				Retrieve supported  information using a callback function
* @apicovered			stt_foreach_supported_engines
* @passcase				If retrieves supported engine information using a callback function
* @failcase				If fails to retrieve supported engine information using a callback function
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_foreach_supported_engines_p(void)
{
	START_TEST;

	g_bSupportedEngineCallbackOccured = false;
	g_nSupportedEngineCount = 0;
	g_bCallbackParameterCheck = false;

	//Target API
	/**** Retrieve supported engine information using a callback function ***/
	int nRet = stt_foreach_supported_engines(g_hStt, stt_supported_engine_callback, NULL);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_foreach_supported_engines", SttGetError(nRet));

	if ( !g_bSupportedEngineCallbackOccured )
	{
		FPRINTF("[Line : %d][%s] stt_foreach_supported_engines failed to invoke stt_supported_engine_cb\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	else if ( !g_bCallbackParameterCheck )
	{
		return 1;
	}
	else if ( g_nSupportedEngineCount == 0 )
	{
		FPRINTF("[Line : %d][%s] stt_foreach_supported_engines returned no engine\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose Retrieve all supported languages of current engine using callback function
//& type: auto
/**
* @testcase				ITc_stt_foreach_supported_languages_p
* @since_tizen			2.3
* @author            	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Retrieve all supported languages of current engine using callback function
* @scenario				Retrieve all supported languages of current engine using callback function
* @apicovered			stt_foreach_supported_languages
* @passcase				If retrieves all supported languages of current engine
* @failcase				If fails to retrieve all supported languages of current engine
* @precondition			NA
* @postcondition		NA
*/
int ITc_stt_foreach_supported_languages_p(void)
{
	START_TEST;

	if ( !initialize_setup_without_result_callback() )
	{
		return 1;
	}

	g_bSupportedLanguageCallbackOccured = false;
	g_nSupportedLanguageCount = 0;
	g_bCallbackParameterCheck = false;

	//Target API
	/**** Retrieve all supported languages of current engine using callback function ***/
	int nRet = stt_foreach_supported_languages(g_hStt, stt_supported_language_callback, NULL);
	PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_foreach_supported_engines", SttGetError(nRet), deinitialize_setup_without_result_callback());

	if ( !g_bSupportedLanguageCallbackOccured )
	{
		FPRINTF("[Line : %d][%s] stt_foreach_supported_languages failed to invoke stt_supported_language_cb\\n", __LINE__, API_NAMESPACE);
		deinitialize_setup_without_result_callback();
		return 1;
	}
	else if ( !g_bCallbackParameterCheck )
	{
		deinitialize_setup_without_result_callback();
		return 1;
	}
	if ( g_nSupportedLanguageCount == 0 )
	{
		FPRINTF("[Line : %d][%s] stt_foreach_supported_languages returned no language\\n", __LINE__, API_NAMESPACE);
		deinitialize_setup_without_result_callback();
		return 1;
	}

	deinitialize_setup_without_result_callback();
	return 0;
}

//& type: auto
//& purpose: To get the list of supported voices.
/**
* @testcase 				ITc_stt_set_credential_p
* @since_tizen 				3.0
* @author					SRID(asit.s)
* @reviewer         		SRID(a.pandia1)
* @type 					auto
* @scenario					create a stt handler\n
* 							call set credentials\n
* @apicovered				stt_set_credential,
* @passcase					if API is successful
* @failcase					if API is not successful
* @precondition				NA
* @postcondition			NA
*/
int ITc_stt_set_credential_p(void)
{
	START_TEST;

	stt_state_e state;
	const char* credential = "TizenApp";

	int nRet =  stt_get_state(g_hStt, &state);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_get_state", SttGetError(nRet));
	if ( state != STT_STATE_CREATED )
	{
		FPRINTF("[Line : %d][%s] get state is not matched state is :: %d \\n", __LINE__, API_NAMESPACE,state);
		return 1;
	}

	//Target API
	nRet = stt_set_credential(g_hStt,credential);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_set_credential", SttGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To get the list of supported voices.
/**
* @testcase 				ITc_stt_set_get_private_data_p
* @since_tizen 				3.0
* @author					SRID(asit.s)
* @reviewer         		SRID(a.pandia1)
* @type 					auto
* @scenario					create a stt handler\n
* 							call stt_set_private_data\n
*							call stt_get_private_data\n
* @apicovered				stt_set_private_data,stt_get_private_data
* @passcase					if API is successful
* @failcase					if API is not successful
* @precondition				NA
* @postcondition			NA
*/
int ITc_stt_set_get_private_data_p(void)
{
	START_TEST;
	char* Getdata = NULL;

	int nRet = stt_prepare(g_hStt);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_prepare", SttGetError(nRet));

	WAIT_FOR_CALLBACK(STT_STATE_READY);

	nRet = stt_set_private_data(g_hStt,"test","data");
	PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_set_private_data", SttGetError(nRet), stt_unprepare(g_hStt));

	nRet = stt_get_private_data(g_hStt,"test",&Getdata);
	PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_get_private_data", SttGetError(nRet), stt_unprepare(g_hStt);FREE_MEMORY(Getdata));

	/*According to the developer, it is unnecessary to compare the key and result as stt_set_private_data() is for setting the key and not saving.*/

	FREE_MEMORY(Getdata);
	nRet = stt_unprepare(g_hStt);
	PRINT_RESULT_NORETURN(STT_ERROR_NONE, nRet, "stt_unprepare", SttGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: To get the list of supported voices.
/**
* @testcase 				ITc_stt_set_unset_engine_changed_cb_p
* @since_tizen 				3.0
* @author					SRID(asit.s)
* @reviewer         		SRID(a.pandia1)
* @type 					auto
* @scenario					create a stt handler\n
* 							call stt_set_engine_changed_cb and register callback function\n
*							call stt_unset_engine_changed_cb to deregister.
* @apicovered				stt_set_engine_changed_cb,stt_unset_engine_changed_cb
* @passcase					if API is successful
* @failcase					if API is not successful
* @precondition				NA
* @postcondition			NA
*/
int ITc_stt_set_unset_engine_changed_cb_p(void)
{
	START_TEST;
	g_CallBackHit = false;

	int nRet = stt_set_engine_changed_cb(g_hStt,sttEngineChangedcb,NULL);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_set_engine_changed_cb", SttGetError(nRet));

	/*According to the developer, it is impossible to change the STT Engine in the situation and hence callback cannot be checked.*/

	nRet = stt_unset_engine_changed_cb(g_hStt);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_unset_engine_changed_cb", SttGetError(nRet));

	return 0;
}


//& type: auto
//& purpose: Set and Unset speech status callback.
/**
* @testcase 				ITc_stt_set_unset_speech_status_cb_p
* @since_tizen 				5.5
* @author				SRID(manoj.g2)
* @reviewer         			SRID(shobhit.v)
* @type 				auto
* @scenario				create a stt handler\n
* @apicovered				stt_set_speech_status_cb,stt_unset_speech_status_cb
* @passcase				if stt_set_speech_status_cb,stt_unset_speech_status_cb and precondition API are successful
* @failcase				if stt_set_speech_status_cb,stt_unset_speech_status_cb and precondition API arenot successful
* @precondition				NA
* @postcondition			NA
*/
int ITc_stt_set_unset_speech_status_cb_p(void)
{
	START_TEST;
	stt_h hSttHandle = NULL;

	int nRet = stt_create(&hSttHandle);
	PRINT_RESULT(STT_ERROR_NONE, nRet, "stt_create", SttGetError(nRet));
	CHECK_HANDLE(hSttHandle, "stt_create");

	nRet = stt_set_speech_status_cb(hSttHandle, sttStatusChangedcb, NULL);
	PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_set_speech_status_cb", SttGetError(nRet), stt_destroy(&hSttHandle));

	nRet = stt_unset_speech_status_cb(hSttHandle);
	PRINT_RESULT_CLEANUP(STT_ERROR_NONE, nRet, "stt_unset_speech_status_cb", SttGetError(nRet), stt_destroy(&hSttHandle));

	nRet = stt_destroy(&hSttHandle);
	PRINT_RESULT_NORETURN(STT_ERROR_NONE, nRet, "stt_destroy", SttGetError(nRet));

	return 0;
}
/** @} */
/** @} */
