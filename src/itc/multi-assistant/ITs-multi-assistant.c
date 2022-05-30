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
#include "assert.h"
#include <stdlib.h>
#include <system_info.h>
#include <Ecore.h>
#include <multi_assistant.h>

#include "ITs-multi-assistant-common.h"

/** @addtogroup itc-multi-assistant
*  @ingroup itc
*  @{
*/

//& set: multi-assistant


/****************************************************Callback Start****************************************************/

/**
* @function 		MaLanguageChangedCb
* @description	 	Callback Function
* @parameters		const char* previous, const char* current, void* user_data
* @return 			NA
*/
void MaLanguageChangedCb(const char* previous, const char* current, void* user_data)
{
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "MaLanguageChangedCb");
	g_CallBackHit = true;
	return;
}

/**
* @function 		MaAudioStreamingCb
* @description	 	Callback Function
* @parameters		ma_audio_streaming_event_e event, char* buffer, int len, void* user_data
* @return 			NA
*/
void MaAudioStreamingCb(ma_audio_streaming_event_e event, char* buffer, int len, void* user_data)
{
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "MaAudioStreamingCb");
	g_CallBackHit = true;
	return;
}

/**
* @function 		MaStateChangedCb
* @description	 	Callback Function
* @parameters		ma_state_e previous, ma_state_e current, void* user_data
* @return 			NA
*/
void MaStateChangedCb(ma_state_e previous, ma_state_e current, void* user_data)
{
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "MaStateChangedCb");
	g_CallBackHit = true;
	g_nCurrentState = current;
	return;
}

/**
* @function 		MaErrorCb
* @description	 	Callback Function
* @parameters		ma_error_e reason, void* user_data
* @return 			NA
*/
void MaErrorCb(ma_error_e reason, void* user_data)
{
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "MaErrorCb");
	g_CallBackHit = true;
	return;
}

/**
* @function 		MaActiveStateChangedCb
* @description	 	Callback Function
* @parameters		ma_active_state_e previous, ma_active_state_e current, void* user_data
* @return 		NA
*/
void MaActiveStateChangedCb(ma_active_state_e previous, ma_active_state_e current, void* user_data)
{
	FPRINTF("[Line : %d][%s] MaActiveStateChangedCb Callback Invoked\\n", __LINE__, API_NAMESPACE);
	g_CallBackHit = true;
	g_nPreviousActiveState = previous;
	g_nCurrentActiveState = current;
	return;
}

/**
* @function 		MaWakeupEngineCmdCb
* @description	 	Callback Function
* @parameters		const char *command, void* user_data
* @return 		NA
*/
void MaWakeupEngineCmdCb(const char *command, void* user_data)
{
	FPRINTF("[Line : %d][%s] MaWakeupEngineCmdCb Callback Invoked\\n", __LINE__, API_NAMESPACE);
	g_CallBackHit = true;
	gpszWakeupCmd = command;
	return;
}

/**
* @function 		MaAudioStreamingDataSecChangedCb
* @description	 	Callback Function
* @parameters		ma_audio_streaming_event_e event, char* buffer, int len, void* user_data
* @return 			NA
*/
void MaAudioStreamingDataSecChangedCb(ma_audio_streaming_data_section_e eDataSection, void* pszData)
{
	FPRINTF("[Line : %d][%s] MaAudioStreamingDataSecChangedCb Callback Invoked\\n", __LINE__, API_NAMESPACE);
	g_CallBackHit = true;
	return;
}
/**
* @function 		MaPreprocessingCb
* @description	 	Callback Function
* @parameters		const char* app_id, void* user_data
* @return 		NA
*/
void MaPreprocessingCb(const char* app_id, void* user_data)
{
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "MaPreprocessingCb");
	g_bCallBackHitEx = true;
	return;
}
/**
* @function 		MaAssistantCb
* @description	 	Callback Function
* @parameters		ma_assistant_info_h handle, void* user_data
* @return 		0
*/
int MaAssistantCb(ma_assistant_info_h handle, void* user_data)
{
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "MaAssistantCb");
        g_CallBackHit = true;
        g_hAssistantInfoHandle = handle;
	return 0;
}
/**
* @function             MaServiceStateChangedCb
* @description          Callback Function
* @parameters           ma_service_state_e previous, ma_service_state_e current, void* user_data
* @return               NA
*/
void MaServiceStateChangedCb(ma_service_state_e previous, ma_service_state_e current, void* user_data)
{
        FPRINTF("[Line : %d][%s] MaServiceStateChangedCb Callback Invoked\\n", __LINE__, API_NAMESPACE);
        return;

}
/**
* @function             MaVoiceKeyStatusChangedCb
* @description          Callback Function
* @parameters           ma_voice_key_status_e status, void* user_data
* @return               NA
*/
void MaVoiceKeyStatusChangedCb(ma_voice_key_status_e status, void* user_data)
{
        FPRINTF("[Line : %d][%s] MaVoiceKeyStatusChangedCb Callback Invoked\\n", __LINE__, API_NAMESPACE);
        return;
}
/*****************************************************Callback End*****************************************************/

/**
* @testcase 			ITs_ma_startup
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(awadhesh1.s)
* @type 				auto
* @since_tizen 			5.0
* @description			NA
* @scenario				Called before each test, creates connection to push service
* @apicovered			NA
* @passcase				NA
* @failcase				NA
* @precondition			NA
* @postcondition		NA
*/
void ITs_ma_startup(void)
{
	int nRet = -1;
	g_bMAInit = true;
	g_bFeatureNotSupported = false;
	g_bIsFeatureMismatched = false;
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Multi_Assistant_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bMultiAssistant = TCTCheckSystemInfoFeatureSupported(FEATURE_MULTI_ASSISTANT, API_NAMESPACE);
	g_bMicrophone = TCTCheckSystemInfoFeatureSupported(FEATURE_MICROPHONE, API_NAMESPACE);

	nRet = ma_initialize();
	if(!g_bMultiAssistant || !g_bMicrophone)
	{
		if(nRet != MA_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] Feature mismatch.\\n", __LINE__, API_NAMESPACE);
			g_bIsFeatureMismatched = true;
			return;
		}
		else
		{
			g_bFeatureNotSupported = true;
			return;
		}
	}
	if (nRet != MA_ERROR_NONE)
		g_bMAInit = false;

	return;
}

/**
* @testcase 			ITs_ma_cleanup
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(awadhesh1.s)
* @type 				auto
* @since_tizen 			5.0
* @description			NA
* @scenario				Called after each test, Closes the connection and releases all its resources
* @apicovered			NA
* @passcase				NA
* @failcase				NA
* @precondition			NA
* @postcondition		NA
*/
void ITs_ma_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Multi_Assistant_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet = -1;
	if(g_bMAInit)
	{
		nRet = ma_deinitialize();
		PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_deinitialize", MaGetError(nRet));
	}
}

/**
* @testcase				ITc_ma_initialize_deinitialize_p
* @since_tizen				5.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(awadhesh1.s)
* @type					auto
* @description				Initializes and deinitializes multi-assistant client.
* @scenario				Initializes and deinitializes multi-assistant client.
* @apicovered				ma_initialize, ma_deinitialize
* @passcase				ma_initialize, ma_deinitialize returns 0
* @failcase				ma_initialize, ma_deinitialize returns 1
* @precondition				N/A
* @postcondition			If this function is called, the state will be #MA_STATE_INITIALIZED.
* */
int ITc_ma_initialize_deinitialize_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = ma_deinitialize();
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_deinitialize", MaGetError(nRet));

	nRet = ma_initialize();
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_initialize", MaGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_ma_get_state_p
* @since_tizen				5.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(awadhesh1.s)
* @type					auto
* @description				Gets the current state of the multi-assistant client.
* @scenario				Gets the current state of the multi-assistant client.
* @apicovered				ma_get_state
* @passcase				ma_get_state returns 0
* @failcase				ma_get_state returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_ma_get_state_p(void)
{
	START_TEST;
	int nRet = -1;
	ma_state_e eState = -1;

	nRet = ma_get_state(&eState);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_get_state", MaGetError(nRet));
	if( eState < MA_STATE_NONE || eState > MA_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] %s failed. eState = %d\\n", __LINE__, API_NAMESPACE, "ma_get_state", eState);
		return 1;
	}

	return 0;
}

/**
* @testcase				ITc_ma_get_current_language_p
* @since_tizen				5.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(awadhesh1.s)
* @type					auto
* @description				Gets the current language of multi-assistant client.
* @scenario				Gets the current language of multi-assistant client.
* @apicovered				ma_get_current_language
* @passcase				ma_get_current_language returns 0
* @failcase				ma_get_current_language returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_ma_get_current_language_p(void)
{
	START_TEST;
	char *pszGetCurrentLanguage = NULL;
	int nRet = -1;

	nRet = ma_get_current_language(&pszGetCurrentLanguage);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_get_current_language", MaGetError(nRet));
	CHECK_HANDLE(pszGetCurrentLanguage, "ma_get_current_language");

	FREE_MEMORY(pszGetCurrentLanguage);

	return 0;
}

/**
* @testcase				ITc_ma_get_recording_audio_format_p
* @since_tizen				5.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(awadhesh1.s)
* @type					auto
* @description				Gets the recording audio format.
* @scenario				Gets the recording audio format.
* @apicovered				ma_get_recording_audio_format
* @passcase				ma_get_recording_audio_format returns 0
* @failcase				ma_get_recording_audio_format returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_ma_get_recording_audio_format_p(void)
{
	START_TEST;

	int nRate = -1;
	int nRet = -1;
	ma_audio_channel_e eChannel = -1;
	ma_audio_type_e eAudioType = -1;
	void* user_data = NULL;
	g_CallBackHit = false;

	nRet = ma_set_state_changed_cb(MaStateChangedCb, user_data);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_state_changed_cb", MaGetError(nRet));

	nRet = ma_prepare();
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_prepare", MaGetError(nRet), ma_unset_state_changed_cb());
	WAIT_FOR_CALLBACK(MA_STATE_READY);
	PRINT_RESULT_CLEANUP(g_CallBackHit, true, "MaStateChangedCb", "Callback not invoked", ma_unprepare(); ma_unset_state_changed_cb());

	nRet = ma_get_recording_audio_format(&nRate, &eChannel, &eAudioType);
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_get_recording_audio_format", MaGetError(nRet), ma_unprepare(); ma_unset_state_changed_cb());
	if( nRate < 0 )
	{
		FPRINTF("[Line : %d][%s] %s failed. nRate = %d\\n", __LINE__, API_NAMESPACE, "ma_get_recording_audio_format", nRate);
		ma_unprepare();
		ma_unset_state_changed_cb();
		return 1;
	}
	if( eChannel < MA_AUDIO_CHANNEL_MONO || eChannel > MA_AUDIO_CHANNEL_STEREO )
	{
		FPRINTF("[Line : %d][%s] %s failed. eChannel = %d\\n", __LINE__, API_NAMESPACE, "ma_get_recording_audio_format", eChannel);
		ma_unprepare();
		ma_unset_state_changed_cb();
		return 1;
	}
	if( eAudioType < MA_AUDIO_TYPE_PCM_S16_LE || eAudioType > MA_AUDIO_TYPE_PCM_U8 )
	{
		FPRINTF("[Line : %d][%s] %s failed. eAudioType = %d\\n", __LINE__, API_NAMESPACE, "ma_get_recording_audio_format", eAudioType);
		ma_unprepare();
		ma_unset_state_changed_cb();
		return 1;
	}

	nRet = ma_unprepare();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unprepare", MaGetError(nRet));

	nRet = ma_unset_state_changed_cb();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unset_state_changed_cb", MaGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_ma_prepare_unprepare_set_unset_state_changed_cb_p
* @since_tizen				5.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(awadhesh1.s)
* @type					auto
* @description				Prepares/unprepares multi-assistant client and sets and unsets a state changed callback.
* @scenario				Prepares/unprepares multi-assistant client and sets and unsets a state changed callback.
* @apicovered				ma_set_state_changed_cb, ma_unset_state_changed_cb, ma_prepare, ma_unprepare
* @passcase				ma_set_state_changed_cb, ma_unset_state_changed_cb returns, ma_prepare, ma_unprepare 0
* @failcase				either of ma_set_state_changed_cb, ma_unset_state_changed_cb, ma_prepare, ma_unprepare returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_ma_prepare_unprepare_set_unset_state_changed_cb_p(void)
{
	START_TEST;

	int nRet = -1;
	void* user_data = NULL;
	g_CallBackHit = false;

	nRet = ma_set_state_changed_cb(MaStateChangedCb, user_data);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_state_changed_cb", MaGetError(nRet));

	nRet = ma_prepare();
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_prepare", MaGetError(nRet), ma_unset_state_changed_cb());
	WAIT_FOR_CALLBACK(MA_STATE_READY);
	PRINT_RESULT_CLEANUP(g_CallBackHit, true, "MaStateChangedCb", "Callback not invoked", ma_unprepare();ma_unset_state_changed_cb());

	nRet = ma_unprepare();
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_unprepare", MaGetError(nRet), ma_unset_state_changed_cb());

	nRet = ma_unset_state_changed_cb();
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_unset_state_changed_cb", MaGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_ma_set_unset_error_cb_p
* @since_tizen				5.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(awadhesh1.s)
* @type					auto
* @description				Sets and unsets an error callback.
* @scenario				Sets and unsets an error callback.
* @apicovered				ma_set_error_cb, ma_unset_error_cb
* @passcase				ma_set_error_cb, ma_unset_error_cb returns 0
* @failcase				ma_set_error_cb, ma_unset_error_cb returns 1
* @precondition				The state should be #MA_STATE_INITIALIZED.
* @postcondition			N/A
* */
int ITc_ma_set_unset_error_cb_p(void)
{
	START_TEST;

	int nRet = -1;
	void* user_data = NULL;

	nRet = ma_set_error_cb(MaErrorCb, user_data);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_error_cb", MaGetError(nRet));

	nRet = ma_unset_error_cb();
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_unset_error_cb", MaGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_ma_set_unset_language_changed_cb_p
* @since_tizen				5.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(awadhesh1.s)
* @type					auto
* @description				Sets and unsets a language changed callback.
* @scenario				Sets and unsets a language changed callback.
* @apicovered				ma_set_language_changed_cb, ma_unset_language_changed_cb
* @passcase				ma_set_language_changed_cb, ma_unset_language_changed_cb returns 0
* @failcase				ma_set_language_changed_cb, ma_unset_language_changed_cb returns 1
* @precondition				The state should be #MA_STATE_INITIALIZED.
* @postcondition			N/A
* */
int ITc_ma_set_unset_language_changed_cb_p(void)
{
	START_TEST;

	int nRet = -1;
	void* user_data = NULL;

	nRet = ma_set_language_changed_cb(MaLanguageChangedCb, user_data);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_language_changed_cb", MaGetError(nRet));

	nRet = ma_unset_language_changed_cb();
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_unset_language_changed_cb", MaGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_ma_set_unset_audio_streaming_cb_p
* @since_tizen				5.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(awadhesh1.s)
* @type					auto
* @description				Sets and unsets an audio streaming callback.
* @scenario				Sets and unsets an audio streaming callback.
* @apicovered				ma_set_audio_streaming_cb, ma_unset_audio_streaming_cb
* @passcase				ma_set_audio_streaming_cb, ma_unset_audio_streaming_cb returns 0
* @failcase				ma_set_audio_streaming_cb, ma_unset_audio_streaming_cb returns 1
* @precondition				The state should be #MA_STATE_INITIALIZED.
* @postcondition			N/A
* */
int ITc_ma_set_unset_audio_streaming_cb_p(void)
{
	START_TEST;

	int nRet = -1;
	void* user_data = NULL;

	nRet = ma_set_audio_streaming_cb(MaAudioStreamingCb, user_data);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_audio_streaming_cb", MaGetError(nRet));

	nRet = ma_unset_audio_streaming_cb();
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_unset_audio_streaming_cb", MaGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_ma_send_asr_result_p
* @since_tizen				5.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(awadhesh1.s)
* @type					auto
* @description				Sends ASR(auto speech recognition) results to the multi-assistant service.
* @scenario				Sends ASR(auto speech recognition) results to the multi-assistant service.
* @apicovered				ma_send_asr_result
* @passcase				ma_send_asr_result returns 0
* @failcase				ma_send_asr_result returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_ma_send_asr_result_p(void)
{
	START_TEST;

	char *pszAsrResult = "Hello";
	int nRet = -1;
	void* user_data = NULL;
	g_CallBackHit = false;

	ma_asr_result_event_e eEvent[] = {
		MA_ASR_RESULT_EVENT_PARTIAL_RESULT,
		MA_ASR_RESULT_EVENT_FINAL_RESULT,
		MA_ASR_RESULT_EVENT_ERROR,
	};

	nRet = ma_set_state_changed_cb(MaStateChangedCb, user_data);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_state_changed_cb", MaGetError(nRet));

	nRet = ma_prepare();
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_prepare", MaGetError(nRet), ma_unset_state_changed_cb());
	WAIT_FOR_CALLBACK(MA_STATE_READY);
	PRINT_RESULT_CLEANUP(g_CallBackHit, true, "MaStateChangedCb", "Callback not invoked", ma_unprepare(); ma_unset_state_changed_cb());

	int nEventSize = sizeof(eEvent)/sizeof(eEvent[0]);
	for(int nEvent = 0; nEvent<nEventSize; nEvent++)
	{
		nRet = ma_send_asr_result(eEvent[nEvent], pszAsrResult);
		PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_send_asr_result", MaGetError(nRet), ma_unprepare(); ma_unset_state_changed_cb());
	}

	nRet = ma_unprepare();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unprepare", MaGetError(nRet));

	nRet = ma_unset_state_changed_cb();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unset_state_changed_cb", MaGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_ma_send_result_p
* @since_tizen				5.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(awadhesh1.s)
* @type					auto
* @description				Sends results to the multi-assistant service.
* @scenario				Sends results to the multi-assistant service.
* @apicovered				ma_send_result
* @passcase				ma_send_result returns 0
* @failcase				ma_send_result returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_ma_send_result_p(void)
{
	START_TEST;

	char *pszDisplayText = "display text";
	char *pszUtteranceText = "utterance text";
	char *pszResultJson = "json result";
	int nRet = -1;
	void* user_data = NULL;
	g_CallBackHit = false;

	nRet = ma_set_state_changed_cb(MaStateChangedCb, user_data);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_state_changed_cb", MaGetError(nRet));

	nRet = ma_prepare();
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_prepare", MaGetError(nRet), ma_unset_state_changed_cb());
	WAIT_FOR_CALLBACK(MA_STATE_READY);
	PRINT_RESULT_CLEANUP(g_CallBackHit, true, "MaStateChangedCbf", "Callback not invoked", ma_unprepare(); ma_unset_state_changed_cb());

	nRet = ma_send_result(pszDisplayText, pszUtteranceText, pszResultJson);
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_send_result", MaGetError(nRet), ma_unprepare(); ma_unset_state_changed_cb());

	nRet = ma_unprepare();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unprepare", MaGetError(nRet));

	nRet = ma_unset_state_changed_cb();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unset_state_changed_cb", MaGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_ma_send_recognition_result_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(manoj.g2)
* @type				auto
* @description				Sends Recognition results to multi-assistant service.
* @scenario				Sends Recognition results to multi-assistant service.
* @apicovered				ma_send_recognition_result
* @passcase				ma_send_recognition_result returns 0
* @failcase				ma_send_recognition_result returns 1
* @precondition			The state should be #MA_STATE_INITIALIZED. and MA should be prepared.
* @postcondition			N/A
* */
int ITc_ma_send_recognition_result_p(void)
{
	START_TEST;

	int nRet = -1;
	void* pszData = NULL;
	g_CallBackHit = false;

	ma_recognition_result_event_e eResult[] = {
		MA_RECOGNITION_RESULT_EVENT_SUCCESS,
		MA_RECOGNITION_RESULT_EVENT_EMPTY_TEXT,
		MA_RECOGNITION_RESULT_EVENT_ERROR
	};

	nRet = ma_set_state_changed_cb(MaStateChangedCb, pszData);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_state_changed_cb", MaGetError(nRet));

	nRet = ma_prepare();
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_prepare", MaGetError(nRet), ma_unset_state_changed_cb());
	WAIT_FOR_CALLBACK(MA_STATE_READY);
	PRINT_RESULT_CLEANUP(g_CallBackHit, true, "MaStateChangedCb", "Callback not invoked", ma_unprepare(); ma_unset_state_changed_cb());

	int nResultSize = sizeof(eResult)/sizeof(eResult[0]);
	for(int nResult = 0; nResult < nResultSize; nResult++)
	{
		nRet = ma_send_recognition_result(eResult[nResult]);
		PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_send_recognition_result", MaGetError(nRet), ma_unprepare(); ma_unset_state_changed_cb());
	}

	nRet = ma_unprepare();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unprepare", MaGetError(nRet));

	nRet = ma_unset_state_changed_cb();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unset_state_changed_cb", MaGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_ma_set_unset_active_state_changed_cb_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(manoj.g2)
* @type				auto
* @description				Sets and unsets active state callback.
* @scenario				Sets and unsets active state callback.
* @apicovered				ma_set_active_state_changed_cb, ma_unset_active_state_changed_cb
* @passcase				ma_set_active_state_changed_cb, ma_unset_active_state_changed_cb returns 0
* @failcase				ma_set_active_state_changed_cb, ma_unset_active_state_changed_cb returns 1
* @precondition			The state should be #MA_STATE_INITIALIZED.
* @postcondition			N/A
* */
int ITc_ma_set_unset_active_state_changed_cb_p(void)
{
	START_TEST;

	int nRet = -1;
	void* pszData = NULL;

	nRet = ma_set_active_state_changed_cb(MaActiveStateChangedCb, pszData);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_active_state_changed_cb", MaGetError(nRet));

	nRet = ma_unset_active_state_changed_cb();
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_unset_active_state_changed_cb", MaGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_ma_start_stop_receiving_audio_streaming_data_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(manoj.g2)
* @type				auto
* @description				Starts and Stops recieving audio streaming data.
* @scenario				Starts and Stops recieving audio streaming data.
* @apicovered				ma_start_receiving_audio_streaming_data, ma_stop_receiving_audio_streaming_data
* @passcase				ma_start_receiving_audio_streaming_data, ma_stop_receiving_audio_streaming_data returns 0
* @failcase				ma_start_receiving_audio_streaming_data, ma_stop_receiving_audio_streaming_data returns 1
* @precondition			The state should be #MA_STATE_INITIALIZED. and MA should be prepared.
* @postcondition			N/A
* */
int ITc_ma_start_stop_receiving_audio_streaming_data_p(void)
{
	START_TEST;

	int nRet = -1;
	void* pszData = NULL;
	g_CallBackHit = false;

	ma_audio_streaming_data_type_e eDataType[] = {
		MA_AUDIO_STREAMING_DATA_TYPE_CURRENT_UTTERANCE,
		MA_AUDIO_STREAMING_DATA_TYPE_PREVIOUS_UTTERANCE,
		MA_AUDIO_STREAMING_DATA_TYPE_FOLLOW_UP_SPEECH
	};

	nRet = ma_set_state_changed_cb(MaStateChangedCb, pszData);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_state_changed_cb", MaGetError(nRet));

	nRet = ma_prepare();
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_prepare", MaGetError(nRet), ma_unset_state_changed_cb());
	WAIT_FOR_CALLBACK(MA_STATE_READY);
	PRINT_RESULT_CLEANUP(g_CallBackHit, true, "MaStateChangedCb", "Callback not invoked", ma_unprepare(); ma_unset_state_changed_cb());

	int nDataSize = sizeof(eDataType)/sizeof(eDataType[0]);
	for(int nData = 0; nData < nDataSize; nData++)
	{
		nRet = ma_start_receiving_audio_streaming_data(eDataType[nData]);
		PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_start_receiving_audio_streaming_data", MaGetError(nRet), ma_unprepare(); ma_unset_state_changed_cb());

		nRet = ma_stop_receiving_audio_streaming_data(eDataType[nData]);
		PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_stop_receiving_audio_streaming_data", MaGetError(nRet), ma_unprepare(); ma_unset_state_changed_cb());
	}

	nRet = ma_unprepare();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unprepare", MaGetError(nRet));

	nRet = ma_unset_state_changed_cb();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unset_state_changed_cb", MaGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_ma_update_voice_feedback_state_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(manoj.g2)
* @type				auto
* @description				Updates voice feedback state.
* @scenario				Updates voice feedback state.
* @apicovered				ma_update_voice_feedback_state
* @passcase				ma_update_voice_feedback_state returns 0
* @failcase				ma_update_voice_feedback_state returns 1
* @precondition			The state should be #MA_STATE_INITIALIZED. and MA should be prepared.
* @postcondition			N/A
* */
int ITc_ma_update_voice_feedback_state_p(void)
{
	START_TEST;

	int nRet = -1;
	void* pszData = NULL;
	g_CallBackHit = false;

	ma_voice_feedback_state_e eFeedbackState[] = {
		MA_VOICE_FEEDBACK_STATE_NONE,
		MA_VOICE_FEEDBACK_STATE_STARTED
	};

	nRet = ma_set_state_changed_cb(MaStateChangedCb, pszData);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_state_changed_cb", MaGetError(nRet));

	nRet = ma_prepare();
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_prepare", MaGetError(nRet), ma_unset_state_changed_cb());
	WAIT_FOR_CALLBACK(MA_STATE_READY);
	PRINT_RESULT_CLEANUP(g_CallBackHit, true, "MaStateChangedCb", "Callback not invoked", ma_unprepare(); ma_unset_state_changed_cb());

	int nFeedbackSize = sizeof(eFeedbackState)/sizeof(eFeedbackState[0]);
	for(int nFeedback = 0; nFeedback < nFeedbackSize; nFeedback++)
	{
		nRet = ma_update_voice_feedback_state(eFeedbackState[nFeedback]);
		PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_update_voice_feedback_state", MaGetError(nRet), ma_unprepare(); ma_unset_state_changed_cb());
	}

	nRet = ma_unprepare();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unprepare", MaGetError(nRet));

	nRet = ma_unset_state_changed_cb();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unset_state_changed_cb", MaGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_ma_send_assistant_specific_command_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(manoj.g2)
* @type				auto
* @description				Sends assistant specific command.
* @scenario				Sends assistant specific command.
* @apicovered				ma_send_assistant_specific_command
* @passcase				ma_send_assistant_specific_command returns 0
* @failcase				ma_send_assistant_specific_command returns 1
* @precondition			The state should be #MA_STATE_INITIALIZED. and MA should be prepared.
* @postcondition			N/A
* */
int ITc_ma_send_assistant_specific_command_p(void)
{
	START_TEST;

	int nRet = -1;
	void* pszData = NULL;
	g_CallBackHit = false;
	const char *pszCmd = "hello";

	nRet = ma_set_state_changed_cb(MaStateChangedCb, pszData);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_state_changed_cb", MaGetError(nRet));

	nRet = ma_prepare();
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_prepare", MaGetError(nRet), ma_unset_state_changed_cb());
	WAIT_FOR_CALLBACK(MA_STATE_READY);
	PRINT_RESULT_CLEANUP(g_CallBackHit, true, "MaStateChangedCb", "Callback not invoked", ma_unprepare(); ma_unset_state_changed_cb());

	nRet = ma_send_assistant_specific_command(pszCmd);
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_send_assistant_specific_command", MaGetError(nRet), ma_unprepare(); ma_unset_state_changed_cb());

	nRet = ma_unprepare();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unprepare", MaGetError(nRet));

	nRet = ma_unset_state_changed_cb();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unset_state_changed_cb", MaGetError(nRet));

	return 0;
}


/**
* @testcase				ITc_ma_set_unset_wakeup_engine_command_cb_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(manoj.g2)
* @type				auto
* @description				Sets and unsets wakeup engine callback.
* @scenario				Sets and unsets wakeup engine callback.
* @apicovered				ma_set_wakeup_engine_command_cb, ma_unset_wakeup_engine_command_cb
* @passcase				ma_set_wakeup_engine_command_cb, ma_unset_wakeup_engine_command_cb returns 0
* @failcase				ma_set_wakeup_engine_command_cb, ma_unset_wakeup_engine_command_cb returns 1
* @precondition			The state should be #MA_STATE_INITIALIZED.
* @postcondition			N/A
* */
int ITc_ma_set_unset_wakeup_engine_command_cb_p(void)
{
	START_TEST;

	int nRet = -1;
	void* pszData = NULL;

	nRet = ma_set_wakeup_engine_command_cb(MaWakeupEngineCmdCb, pszData);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_wakeup_engine_command_cb", MaGetError(nRet));

	nRet = ma_unset_wakeup_engine_command_cb();
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_unset_wakeup_engine_command_cb", MaGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_ma_set_wake_word_audio_require_flag_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Sets whether multi-assistant service should send wake word audio data.
* @scenario				create multi-assistant and set ma_set_wake_word_audio_require_flag
* @apicovered				ma_set_wake_word_audio_require_flag
* @passcase				ma_set_wake_word_audio_require_flag returns 0
* @failcase				ma_set_wake_word_audio_require_flag returns 1
* @precondition			The state should be #MA_STATE_INITIALIZED.
* @postcondition			N/A
* */
int ITc_ma_set_wake_word_audio_require_flag_p(void)
{
	START_TEST;

	int nRet = -1;
	bool bIsRequired = false;

	nRet = ma_prepare();
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_prepare", MaGetError(nRet));

	nRet = ma_set_wake_word_audio_require_flag(bIsRequired);
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_set_wake_word_audio_require_flag", MaGetError(nRet), ma_unprepare());

	bIsRequired = true;
	nRet = ma_set_wake_word_audio_require_flag(bIsRequired);
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_set_wake_word_audio_require_flag", MaGetError(nRet), ma_unprepare());

	nRet = ma_unprepare();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unprepare", MaGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_ma_set_unset_audio_streaming_data_section_changed_cb_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Sets and Unset the section changed callback for audio streaming data.
* @scenario				create multi-assistant and call set ma_set_audio_streaming_data_section_changed_cb
*					and ma_unset_audio_streaming_data_section_changed_cb and check for Pass/Fail.
* @apicovered				ma_set_audio_streaming_data_section_changed_cb, ma_unset_audio_streaming_data_section_changed_cb
* @passcase				ma_set_audio_streaming_data_section_changed_cb, ma_unset_audio_streaming_data_section_changed_cb returns 0
* @failcase				ma_set_audio_streaming_data_section_changed_cb, ma_unset_audio_streaming_data_section_changed_cb returns 1
* @precondition			The state should be #MA_STATE_INITIALIZED.
* @postcondition			N/A
* */
int ITc_ma_set_unset_audio_streaming_data_section_changed_cb_p(void)
{

	START_TEST;

	int nRet = -1;
	void* pszData = NULL;

	nRet = ma_set_audio_streaming_data_section_changed_cb(MaAudioStreamingDataSecChangedCb, pszData);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_audio_streaming_data_section_changed_cb", MaGetError(nRet));

	nRet = ma_unset_audio_streaming_data_section_changed_cb();
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_unset_audio_streaming_data_section_changed_cb", MaGetError(nRet));

	return 0;
}



/**
* @testcase				ITc_ma_assistant_info_foreach_assistants_p
* @since_tizen				5.5
* @author				SRID(mohit.m)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Retrieves the information about all installed voice assistant applications.
* @scenario				call ma_assistant_info_foreach_assistants and check for Pass/Fail
* @apicovered				ma_assistant_info_foreach_assistants
* @passcase				ma_assistant_info_foreach_assistants,  returns 0
* @failcase				ma_assistant_info_foreach_assistants,  returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_ma_assistant_info_foreach_assistants_p(void)
{
	START_TEST;
        int nRet = -1;
	g_CallBackHit = false;

	//Target API
	nRet = ma_assistant_info_foreach_assistants(MaAssistantCb, NULL);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_assistant_info_foreach_assistants", MaGetError(nRet));
	return 0;
}
/**
* @testcase				ITc_ma_assistant_info_get_app_id_p
* @since_tizen				5.5
* @author				SRID(mohit.m)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Gets the app id of the specified handle.
* @scenario				call ma_assistant_info_foreach_assistants and ma_assistant_info_get_app_id and check for Pass/Fail
* @apicovered				ma_assistant_info_foreach_assistants, ma_assistant_info_get_app_id
* @passcase				ma_assistant_info_foreach_assistants, ma_assistant_info_get_app_id returns 0
* @failcase				ma_assistant_info_foreach_assistants, ma_assistant_info_get_app_id returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_ma_assistant_info_get_app_id_p(void)
{
	START_TEST;
        int nRet = -1;
	void* pszData = NULL;
	g_CallBackHit = false;
	char* pszAppId = NULL;

	nRet = ma_assistant_info_foreach_assistants(MaAssistantCb, pszData);
        PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_assistant_info_foreach_assistants", MaGetError(nRet));

	//Target API
	nRet = ma_assistant_info_get_app_id(g_hAssistantInfoHandle, &pszAppId);
	if(g_hAssistantInfoHandle == NULL)
	{
        	PRINT_RESULT(nRet, MA_ERROR_INVALID_PARAMETER, "ma_assistant_info_get_app_id", MaGetError(nRet));
	}
	else
	{
		PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_assistant_info_get_app_id", MaGetError(nRet));
	}
	return 0;
}
/**
* @testcase				ITc_ma_assistant_info_get_enabled_status_p
* @since_tizen				5.5
* @author				SRID(mohit.m)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Gets the app id of the specified handle.
* @scenario				call ma_assistant_info_foreach_assistants and ma_assistant_info_get_enabled_status and check for Pass/Fail
* @apicovered				ma_assistant_info_foreach_assistants, ma_assistant_info_get_enabled_status
* @passcase				ma_assistant_info_foreach_assistants, ma_assistant_info_get_enabled_status returns 0
* @failcase				ma_assistant_info_foreach_assistants, ma_assistant_info_get_enabled_status returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_ma_assistant_info_get_enabled_status_p(void)
{
	START_TEST;
        int nRet = -1;
	void* pszData = NULL;
	g_CallBackHit = false;
	bool bEnabledStatus;

	nRet = ma_assistant_info_foreach_assistants(MaAssistantCb, pszData);
        PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_assistant_info_foreach_assistants", MaGetError(nRet));

	//Target API
	nRet = ma_assistant_info_get_enabled_status(g_hAssistantInfoHandle, &bEnabledStatus);
	if(g_hAssistantInfoHandle == NULL)
	{
        	PRINT_RESULT(nRet, MA_ERROR_INVALID_PARAMETER, "ma_assistant_info_get_enabled_status", MaGetError(nRet));
	}
	else
	{
		PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_assistant_info_get_enabled_status", MaGetError(nRet));
	}
	return 0;
}
/**
* @testcase				ITc_ma_get_recording_audio_source_type_p
* @since_tizen				5.5
* @author				SRID(mohit.m)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Gets the recording audio source type..
* @scenario				call ma_get_recording_audio_source_type and check for Pass/Fail
* @apicovered				ma_set_state_changed_cb, ma_get_recording_audio_source_type
* @passcase				ma_set_state_changed_cb, ma_get_recording_audio_source_type returns 0
* @failcase				ma_set_state_changed_cb, ma_get_recording_audio_source_type returns 1
* @precondition				The state should be MA_STATE_READY and MA should be prepared
* @postcondition			N/A
* */
int ITc_ma_get_recording_audio_source_type_p(void)
{
	START_TEST;
	int nRet = -1;
        char *pszType = NULL;
	void* pszData = NULL;
	g_CallBackHit = false;

	nRet = ma_set_state_changed_cb(MaStateChangedCb, pszData);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_state_changed_cb", MaGetError(nRet));

	nRet = ma_prepare();
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_prepare", MaGetError(nRet), ma_unset_state_changed_cb());
	WAIT_FOR_CALLBACK(MA_STATE_READY);
	PRINT_RESULT_CLEANUP(g_CallBackHit, true, "MaStateChangedCb", "Callback not invoked", ma_unprepare(); ma_unset_state_changed_cb());

	//Target API
        nRet = ma_get_recording_audio_source_type(&pszType);
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_get_recording_audio_source_type", MaGetError(nRet), ma_unprepare(); ma_unset_state_changed_cb());

        if(pszType != NULL)
	{
		FREE_MEMORY(pszType);
	}

        nRet = ma_unprepare();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unprepare", MaGetError(nRet));
	nRet = ma_unset_state_changed_cb();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unset_state_changed_cb", MaGetError(nRet));
	return 0;
}
/**
* @testcase				ITc_ma_set_background_volume_p
* @since_tizen				5.5
* @author				SRID(mohit.m)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Sets the background volume.
* @scenario				call ma_set_background_volume and check for Pass/Fail
* @apicovered				ma_set_state_changed_cb, ma_set_background_volume
* @passcase				ma_set_state_changed_cb, ma_set_background_volume returns 0
* @failcase				ma_set_state_changed_cb, ma_set_background_volume returns 1
* @precondition				The state should be MA_STATE_READY and MA should be prepared
* @postcondition			N/A
* */
int ITc_ma_set_background_volume_p(void)
{
        START_TEST;
        int nRet = -1;
        char *pszType = NULL;
	void* pszData = NULL;
	g_CallBackHit = false;

	nRet = ma_set_state_changed_cb(MaStateChangedCb, pszData);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_state_changed_cb", MaGetError(nRet));

	nRet = ma_prepare();
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_prepare", MaGetError(nRet), ma_unset_state_changed_cb());
	WAIT_FOR_CALLBACK(MA_STATE_READY);
	PRINT_RESULT_CLEANUP(g_CallBackHit, true, "MaStateChangedCb", "Callback not invoked", ma_unprepare(); ma_unset_state_changed_cb());

	//Target API
        nRet = ma_set_background_volume(0.0);
        PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_set_background_volume", MaGetError(nRet), ma_unprepare(); ma_unset_state_changed_cb());

	//Target API
        nRet = ma_set_background_volume(1.0);
        PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_set_background_volume", MaGetError(nRet),ma_unprepare(); ma_unset_state_changed_cb());

        nRet = ma_unprepare();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unprepare", MaGetError(nRet));

	nRet = ma_unset_state_changed_cb();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unset_state_changed_cb", MaGetError(nRet));
        return 0;
}
/**
* @testcase				ITc_ma_set_preprocessing_allow_mode_p
* @since_tizen				5.5
* @author				SRID(mohit.m)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Sets the preprocessing allow mode.
* @scenario				call ma_set_preprocessing_allow_mode for different preprocessing allow modes and check for Pass/Fail
* @apicovered				ma_set_state_changed_cb, ma_set_preprocessing_allow_mode
* @passcase				ma_set_state_changed_cb, ma_set_preprocessing_allow_mode returns 0
* @failcase				ma_set_state_changed_cb, ma_set_preprocessing_allow_mode returns 1
* @precondition				The state should be MA_STATE_READY and MA should be prepared
* @postcondition			N/A
* */
int ITc_ma_set_preprocessing_allow_mode_p(void)
{
	START_TEST;
	int nRet = -1;
	void* pszData = NULL;
	g_CallBackHit = false;
	ma_preprocessing_allow_mode_e ePreprocessingMode[] = {
		MA_PREPROCESSING_ALLOW_NONE,
		MA_PREPROCESSING_ALLOW_UTTERANCE,
		MA_PREPROCESSING_ALLOW_FOLLOW_UP,
		MA_PREPROCESSING_ALLOW_ALL
	};

	nRet = ma_set_state_changed_cb(MaStateChangedCb, pszData);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_state_changed_cb", MaGetError(nRet));

	nRet = ma_prepare();
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_prepare", MaGetError(nRet), ma_unset_state_changed_cb());
	WAIT_FOR_CALLBACK(MA_STATE_READY);
	PRINT_RESULT_CLEANUP(g_CallBackHit, true, "MaStateChangedCb", "Callback not invoked", ma_unprepare(); ma_unset_state_changed_cb());

	int nPreprocessingModeSize = sizeof(ePreprocessingMode)/sizeof(ePreprocessingMode[0]);
	for(int nPreprocessing = 0; nPreprocessing < nPreprocessingModeSize; nPreprocessing++)
	{
		//Target API
		nRet = ma_set_preprocessing_allow_mode(ePreprocessingMode[nPreprocessing], NULL);
		PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_set_preprocessing_allow_mode", MaGetError(nRet), ma_unprepare(); ma_unset_state_changed_cb());
	}

	nRet = ma_unprepare();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unprepare", MaGetError(nRet));
	nRet = ma_unset_state_changed_cb();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unset_state_changed_cb", MaGetError(nRet));
	return 0;
}
/**
* @testcase				ITc_ma_set_unset_preprocessing_information_changed_cb_p
* @since_tizen				5.5
* @author				SRID(mohit.m)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Sets and Unsets the preprocessing information changed callback.
* @scenario				call ma_set_preprocessing_information_changed_cb, ma_unset_preprocessing_information_changed_cb and check for Pass/Fail
* @apicovered				ma_set_preprocessing_information_changed_cb, ma_unset_preprocessing_information_changed_cb
* @passcase				ma_set_preprocessing_information_changed_cb, ma_unset_preprocessing_information_changed_cb returns 0
* @failcase				ma_set_preprocessing_information_changed_cb, ma_unset_preprocessing_information_changed_cb returns 1
* @precondition				The state should be MA_STATE_INITIALIZED
* @postcondition			N/A
* */
int ITc_ma_set_unset_preprocessing_information_changed_cb_p(void)
{
	START_TEST;
	int nRet = -1;
	g_bCallBackHitEx = false;
	void* pszData = NULL;

	//Target API
	nRet = ma_set_preprocessing_information_changed_cb(MaPreprocessingCb, pszData);
        PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_preprocessing_information_changed_cb", MaGetError(nRet));

	//Target API
        nRet = ma_unset_preprocessing_information_changed_cb();
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_unset_preprocessing_information_changed_cb", MaGetError(nRet));
	return 0;
}
/**
* @testcase				ITc_ma_send_preprocessing_result_p
* @since_tizen				5.5
* @author				SRID(mohit.m)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Sends the preprocessing result
* @scenario				call ma_send_preprocessing_result and check for Pass/Fail for true or false value
* @apicovered				ma_set_state_changed_cb, ma_send_preprocessing_result
* @passcase				ma_set_state_changed_cb, ma_send_preprocessing_result returns 0
* @failcase				ma_set_state_changed_cb, ma_send_preprocessing_result returns 1
* @precondition				The state should be MA_STATE_READY and MA should be prepared
* @postcondition			N/A
* */
int ITc_ma_send_preprocessing_result_p(void)
{
	START_TEST;
	int nRet = -1;
	void* pszData = NULL;
	g_CallBackHit = false;

	nRet = ma_set_state_changed_cb(MaStateChangedCb, pszData);
	PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_state_changed_cb", MaGetError(nRet));

	nRet = ma_prepare();
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_prepare", MaGetError(nRet), ma_unset_state_changed_cb());
	WAIT_FOR_CALLBACK(MA_STATE_READY);
	PRINT_RESULT_CLEANUP(g_CallBackHit, true, "MaStateChangedCb", "Callback not invoked", ma_unprepare(); ma_unset_state_changed_cb());

	//Target API
	nRet = ma_send_preprocessing_result(false);
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_send_preprocessing_result", MaGetError(nRet), ma_unprepare(); ma_unset_state_changed_cb());

	//Target API
	nRet = ma_send_preprocessing_result(true);
	PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_send_preprocessing_result", MaGetError(nRet), ma_unprepare(); ma_unset_state_changed_cb());

	nRet = ma_unprepare();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unprepare", MaGetError(nRet));
	nRet = ma_unset_state_changed_cb();
	PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unset_state_changed_cb", MaGetError(nRet));
	return 0;
}
/**
* @testcase                             ITc_ma_set_assistant_wakeup_language_p
* @since_tizen                          6.0
* @author                               SRID(mohit.m)
* @reviewer                             SRID(shobhit.v)
* @type                                 auto
* @description                          sets the assistant wakeup language
* @scenario                             calls ma_set_assistant_wakeup_language and check for Pass/Fail
* @apitarget                            ma_set_assistant_wakeup_language
* @apicovered                           ma_set_state_changed_cb, ma_set_assistant_wakeup_language
* @passcase                             ma_set_state_changed_cb, ma_set_assistant_wakeup_language returns MA_ERROR_NONE
* @failcase                             ma_set_state_changed_cb, ma_set_assistant_wakeup_language do not return MA_ERROR_NONE
* @precondition                         The state should be MA_STATE_READY and MA should be prepared
* @postcondition                        N/A
* */

int ITc_ma_set_assistant_wakeup_language_p(void)
{
        START_TEST;
        int nRet = -1;
        char *pszLanguage = "en_US";
        void* pszData = NULL;
        g_CallBackHit = false;

        nRet = ma_set_state_changed_cb(MaStateChangedCb, pszData);
        PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_state_changed_cb", MaGetError(nRet));

        nRet = ma_prepare();
        PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_prepare", MaGetError(nRet), ma_unset_state_changed_cb());
        WAIT_FOR_CALLBACK(MA_STATE_READY);
        PRINT_RESULT_CLEANUP(g_CallBackHit, true, "MaStateChangedCb", "Callback not invoked", ma_unprepare(); ma_unset_state_changed_cb());

        //Target API
        nRet = ma_set_assistant_wakeup_language(pszLanguage);
        PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_set_assistant_wakeup_language", MaGetError(nRet), ma_unprepare(); ma_unset_state_changed_cb());

        nRet = ma_unprepare();
        PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unprepare", MaGetError(nRet));

        nRet = ma_unset_state_changed_cb();
        PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unset_state_changed_cb", MaGetError(nRet));

        return 0;
}
/**
* @testcase                             ITc_ma_set_unset_service_state_changed_cb_p
* @since_tizen                          6.0
* @author                               SRID(mohit.m)
* @reviewer                             SRID(shobhit.v)
* @type                                 auto
* @description                          Sets and unsets service state changed callback
* @scenario                             Sets and unsets service state changed callback
* @apicovered                           ma_set_service_state_changed_cb, ma_unset_service_state_changed_cb
* @passcase                             ma_set_service_state_changed_cb, ma_unset_service_state_changed_cb return MA_ERROR_NONE
* @failcase                             ma_set_service_state_changed_cb, ma_unset_service_state_changed_cb do not return MA_ERROR_NONE
* @precondition                         The state should be #MA_STATE_INITIALIZED.
* @postcondition                        N/A
* */
int ITc_ma_set_unset_service_state_changed_cb_p(void)
{
        START_TEST;

        int nRet = -1;
        void* pszData = NULL;

        //Target API
        nRet = ma_set_service_state_changed_cb(MaServiceStateChangedCb, pszData);
        PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_service_state_changed_cb", MaGetError(nRet));

        //Target API
        nRet = ma_unset_service_state_changed_cb();
        PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_unset_service_state_changed_cb", MaGetError(nRet));

        return 0;
}
/**
* @testcase                             ITc_ma_set_unset_voice_key_status_changed_cb_p
* @since_tizen                          6.0
* @author                               SRID(mohit.m)
* @reviewer                             SRID(shobhit.v)
* @type                                 auto
* @description                          Sets and unsets voice key status changed callback
* @scenario                             Sets and unsets voice key status changed callback
* @apicovered                           ma_set_voice_key_status_changed_cb, ma_unset_voice_key_status_changed_cb
* @passcase                             ma_set_voice_key_status_changed_cb, ma_unset_voice_key_status_changed_cb return MA_ERROR_NONE
* @failcase                             ma_set_voice_key_status_changed_cb, ma_unset_voice_key_status_changed_cb do not return MA_ERROR_NONE
* @precondition                         The state should be #MA_STATE_INITIALIZED.
* @postcondition                        N/A
* */
int ITc_ma_set_unset_voice_key_status_changed_cb_p(void)
{
        START_TEST;

        int nRet = -1;
        void* pszData = NULL;

        //Target API
        nRet = ma_set_voice_key_status_changed_cb(MaVoiceKeyStatusChangedCb, pszData);
        PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_voice_key_status_changed_cb", MaGetError(nRet));

        //Target API
        nRet = ma_unset_voice_key_status_changed_cb();
        PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_unset_voice_key_status_changed_cb", MaGetError(nRet));

        return 0;
}
/**
* @testcase                             ITc_ma_add_remove_wake_word_p
* @since_tizen                          6.0
* @author                               SRID(mohit.m)
* @reviewer                             SRID(shobhit.v)
* @type                                 auto
* @description                          adds and removes the wakeup word
* @scenario                             adds and removes the wakeup word
* @apitarget                            ma_add_wake_word, ma_remove_wake_word
* @apicovered                           ma_set_state_changed_cb, ma_add_wake_word, ma_remove_wake_word
* @passcase                             ma_set_state_changed_cb, ma_add_wake_word, ma_remove_wake_word returns MA_ERROR_NONE
* @failcase                             ma_set_state_changed_cb, ma_add_wake_word, ma_remove_wake_word do not return MA_ERROR_NONE
* @precondition                         The state should be MA_STATE_READY and MA should be prepared
* @postcondition                        N/A
* */
int ITc_ma_add_remove_wake_word_p(void)
{
        START_TEST;

        int nRet = -1;
        char *pszWakeWord = "Hi Tizen";
        char *pszLanguage = "en_US";
        void* pszData = NULL;
        g_CallBackHit = false;

        nRet = ma_set_state_changed_cb(MaStateChangedCb, pszData);
        PRINT_RESULT(nRet, MA_ERROR_NONE, "ma_set_state_changed_cb", MaGetError(nRet));

        nRet = ma_prepare();
        PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_prepare", MaGetError(nRet), ma_unset_state_changed_cb());
        WAIT_FOR_CALLBACK(MA_STATE_READY);
        PRINT_RESULT_CLEANUP(g_CallBackHit, true, "MaStateChangedCb", "Callback not invoked", ma_unprepare(); ma_unset_state_changed_cb());

        //Target API
        nRet = ma_add_wake_word(pszWakeWord, pszLanguage);
        PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_add_wake_word", MaGetError(nRet), ma_unprepare(); ma_unset_state_changed_cb());

        //Target API
        nRet = ma_remove_wake_word(pszWakeWord, pszLanguage);
        PRINT_RESULT_CLEANUP(nRet, MA_ERROR_NONE, "ma_remove_wake_word", MaGetError(nRet), ma_unprepare(); ma_unset_state_changed_cb());

        nRet = ma_unprepare();
        PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unprepare", MaGetError(nRet));

        nRet = ma_unset_state_changed_cb();
        PRINT_RESULT_NORETURN(nRet, MA_ERROR_NONE, "ma_unset_state_changed_cb", MaGetError(nRet));

        return 0;
}
