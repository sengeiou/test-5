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
#include "ITs-voice-control-common.h"
#include <vce.h>
#include <stdlib.h>
#include <system_info.h>
#include <fcntl.h>
#include <unistd.h>
#include <dlog.h>


//& set: VoiceControl

/** @addtogroup itc-voice-control
*  @ingroup itc
*  @{
*/


static int nArgs = 1;
static char **pszArgv = NULL;
static vce_request_callback_s g_callback = {0,};
bool g_CallBackHit = false;

extern void transfer_arg(int * argc, char ** argv[]);
/****************************************************Callback Start****************************************************/

static int vce_default_initialize(void)
{
	return 0;
}
static int vce_default_deinitialize(void)
{
	return 0;
}
static int vce_default_get_info(char **engine_uuid, char **engine_name, char **engine_setting, bool *use_network)
{
	*engine_uuid = strdup("vce_engine_uuid");
	*engine_name = strdup("vce_engine_name");
	*engine_setting = NULL;
	*use_network = true;
	return 0;
}
static int vce_default_get_recording_format(const char *audio_id, vce_audio_type_e *types, int *rate, int *channels)
{
	*types = VCE_AUDIO_TYPE_PCM_S16_LE;
	*rate = 16000;
	*channels = 1;
	return 0;
}
static int vce_default_foreach_langs(vce_supported_language_cb callback, void *user_data)
{
	return 0;
}
static bool vce_default_is_lang_supported(const char *lang)
{
	return true;
}
static int vce_default_set_language(const char *language)
{
	return 0;
}
static int vce_default_set_commands(vce_cmd_h vc_command)
{
	return 0;
}
static int vce_default_unset_commands()
{
	return 0;
}
static int vce_default_start(bool stop_by_silence)
{
	return 0;
}
static int vce_default_set_recording(const void *data, unsigned int length, vce_speech_detect_e *silence_detected)
{
	return 0;
}
static int vce_default_stop()
{
	return 0;
}
static int vce_default_cancel(void)
{
	return 0;
}
static int vce_default_set_audio_type(const char *audio_type)
{
	return 0;
}
static int vce_default_set_domain(const char *domain)
{
	return 0;
}
static int vce_default_process_text(const char *text)
{
	return 0;
}
static int vce_default_process_list_event(const char *event)
{
	return 0;
}
static int vce_default_process_haptic_event(const char *event)
{
	return 0;
}
static int vce_default_set_server_dialog(const char* app_id, const char* credential)
{
	return 0;
}
static int VceSetPrivateDataCallback(const char* key, const char* data)
{
	#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "VceSetPrivateDataCallback");
	#endif

	g_CallBackHit = true;
	return 0;
}
static int VcePrivateDataRequestedCallback(const char* key, char** data)
{
	#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "VcePrivateDataRequestedCallback");
	#endif

	g_CallBackHit = true;
	return 0;
}
static int VceNluBasedInfoRequestedCallback(const char* key, char** value)
{
	#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "VceNluBasedInfoRequestedCallback");
	#endif

	g_CallBackHit = true;
	return 0;
}
static int VceSpecificEngineRequestCB(const char* engine_app_id, const char* event, const char* request)
{
	#if DEBUG
		FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "VceSpecificEngineRequestCB");
	#endif

	g_CallBackHit = true;
	return 0;
}

static int VceRequestTtsCB (int pid, int utt_id, const char* text, const char* language, void* user_data)
{
	#if DEBUG
		FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "VceRequestTtsCB");
	#endif

	g_CallBackHit = true;
	return 0;
}

static int VceCancelTtsCB(int pid, int utt_id, void* user_data)
{
	#if DEBUG
		FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "VceCancelTtsCB");
	#endif

	g_CallBackHit = true;
	return 0;
}

static int VceTtsAudioFormatRequestCB(int* rate, int* channel, int* audio_type, void* user_data)
{
	#if DEBUG
		FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "VceTtsAudioFormatRequestCB");
	#endif

	g_CallBackHit = true;
	return 0;
}

/*****************************************************Callback End*****************************************************/

/************************************************ Helper Function Start ***********************************************/
/**
* @function 		VoiceControlEngineGetError
* @description	 	Maps error enums to string values for voicecontrol engine
* @parameter		nRet : error code returned
* @return 			error string
*/
char* VoiceControlEngineGetError(int nRet)
{
	char *szErrorVal = "VC_ERROR_UNKNOWN";
	switch ( nRet )
	{

		case VCE_ERROR_NONE:			szErrorVal = "VCE_ERROR_NONE";				break;
		case VCE_ERROR_OUT_OF_MEMORY:			szErrorVal = "VCE_ERROR_OUT_OF_MEMORY";				break;
		case VCE_ERROR_IO_ERROR:			szErrorVal = "VCE_ERROR_IO_ERROR";				break;
		case VCE_ERROR_INVALID_PARAMETER:			szErrorVal = "VCE_ERROR_INVALID_PARAMETER";			break;
		case VCE_ERROR_OUT_OF_NETWORK:			szErrorVal = "VCE_ERROR_OUT_OF_NETWORK";					break;
		case VCE_ERROR_RECORDER_BUSY:			szErrorVal = "VCE_ERROR_RECORDER_BUSY";						break;
		case VCE_ERROR_INVALID_STATE:			szErrorVal = "VCE_ERROR_INVALID_STATE";						break;
		case VCE_ERROR_INVALID_LANGUAGE:			szErrorVal = "VCE_ERROR_INVALID_LANGUAGE";					break;
		case VCE_ERROR_OPERATION_FAILED:			szErrorVal = "VCE_ERROR_OPERATION_FAILED";					break;
		case VCE_ERROR_PERMISSION_DENIED:			szErrorVal = "VCE_ERROR_PERMISSION_DENIED";					break;
		case VCE_ERROR_NOT_SUPPORTED:			szErrorVal = "VCE_ERROR_NOT_SUPPORTED";						break;
	}
	return szErrorVal;
}

void transfer_arg(int * argc, char ** argv[])
{
	*argc = nArgs;
	*argv = pszArgv;
	dlog_print(DLOG_INFO, "NativeTCT", "[transfer_arg called] argc = %d, argv[0] = %s", *argc, (NULL == *argv) ? "NULL" : *argv[0]);
}

int VceStartMain()
{
	int nRet = vce_main(nArgs, pszArgv, &g_callback);
	if ( false == g_bIsVcFeatureSupported )
	{
		if ( nRet != VCE_ERROR_NOT_SUPPORTED )
		{
			g_bVCEFeatureMismatch = true;
		}
		else
		{
			g_bIsVCEFeatureNotSupported = true;
		}
	}

	return nRet;
}

/************************************************* Helper Function End ************************************************/

/**
 * @function 		ITs_voice_control_engine_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
 void ITs_voice_control_engine_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		int ret = remove(ERR_LOG);
		if(ret == -1)
		{
			FPRINTF("[Line: %d][%s] unlinking file name error =%s \\n", __LINE__, API_NAMESPACE,ERR_LOG);
			return;
		}
	}

	g_bIsVcFeatureSupported = TCTCheckSystemInfoFeatureSupported(MICROPHONEFEATURE, API_NAMESPACE) && TCTCheckSystemInfoFeatureSupported(SPEECHCONTROLFEATURE, API_NAMESPACE);

	transfer_arg(&nArgs, &pszArgv);

	g_callback.version = 1;

	g_callback.get_info	= vce_default_get_info;
	g_callback.get_recording_format	= vce_default_get_recording_format;
	g_callback.foreach_langs	= vce_default_foreach_langs;
	g_callback.is_lang_supported	= vce_default_is_lang_supported;

	g_callback.initialize	= vce_default_initialize;
	g_callback.deinitialize	= vce_default_deinitialize;

	g_callback.set_language	= vce_default_set_language;
	g_callback.set_commands	= vce_default_set_commands;
	g_callback.unset_commands	= vce_default_unset_commands;

	g_callback.start		= vce_default_start;
	g_callback.set_recording	= vce_default_set_recording;
	g_callback.stop		= vce_default_stop;
	g_callback.cancel		= vce_default_cancel;

	g_callback.set_audio_type	= vce_default_set_audio_type;
	g_callback.set_server_dialog	= vce_default_set_server_dialog;
	g_callback.set_domain	= vce_default_set_domain;
	g_callback.process_text	= vce_default_process_text;
	g_callback.process_list_event	= vce_default_process_list_event;
	g_callback.process_haptic_event	= vce_default_process_haptic_event;

	return;
}

/**
 * @function 		ITs_voice_control_engine_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_voice_control_engine_cleanup(void)
{
	return;
}

/** @addtogroup itc-voice-control-testcases
*  @brief 		Integration testcases for module voice-control
*  @ingroup 	itc-voice-control
*  @{
*/

/**
 * @testcase 				ITc_vce_main_p
 * @author					SRID(manoj.g2)
 * @reviewer				SRID(nibha.sharma)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				To test vce_main
 * @scenario				Call vce_main
 * @apicovered				vce_main
 * @passcase				If vce_main return VCE_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vce_main
int ITc_vce_main_p(void)
{
	int nRet = VceStartMain();
	START_TEST_VCE;

	PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_main", VoiceControlEngineGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vce_send_error_p
 * @author					SRID(manoj.g2)
 * @reviewer				SRID(nibha.sharma)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				To test vce_send_error
 * @scenario				Call vce_main,vce_send_error
 * @apicovered				vce_main, vce_send_error
 * @passcase				If vce_main return VCE_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vce_send_error
int ITc_vce_send_error_p(void)
{
	int nRet = VceStartMain();
	START_TEST_VCE;

	PRINT_RESULT(VCE_ERROR_NONE, nRet, "VceStartMain", VoiceControlEngineGetError(nRet));

	nRet = vce_send_error(VCE_ERROR_NONE, "msg", NULL);
	PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_send_error", VoiceControlEngineGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vce_set_private_data_set_cb_p
 * @author					SRID(manoj.g2)
 * @reviewer				SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				To test vce_set_private_data_set_cb
 * @scenario				Call vce_main, vce_set_private_data_set_cb
 * @apicovered				vce_main, vce_set_private_data_set_cb
 * @passcase				If vce_set_private_data_set_cb return VCE_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vce_set_private_data_set_cb
int ITc_vce_set_private_data_set_cb_p(void)
{
	int nRet = VceStartMain();
	START_TEST_VCE;

	PRINT_RESULT(VCE_ERROR_NONE, nRet, "VceStartMain", VoiceControlEngineGetError(nRet));

	nRet = vce_set_private_data_set_cb(VceSetPrivateDataCallback);
	PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_set_private_data_set_cb", VoiceControlEngineGetError(nRet));

	return 0;
}


/**
 * @testcase 				ITc_vce_set_nlu_base_info_requested_cb_p
 * @author					SRID(manoj.g2)
 * @reviewer				SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				To test vce_set_nlu_base_info_requested_cb
 * @scenario				Call vce_main, vce_set_nlu_base_info_requested_cb
 * @apicovered				vce_main, vce_set_nlu_base_info_requested_cb
 * @passcase				If vce_set_nlu_base_info_requested_cb return VCE_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vce_set_nlu_base_info_requested_cb
int ITc_vce_set_nlu_base_info_requested_cb_p(void)
{
	int nRet = VceStartMain();
	START_TEST_VCE;

	PRINT_RESULT(VCE_ERROR_NONE, nRet, "VceStartMain", VoiceControlEngineGetError(nRet));

	nRet = vce_set_nlu_base_info_requested_cb(VceNluBasedInfoRequestedCallback);
	PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_set_nlu_base_info_requested_cb", VoiceControlEngineGetError(nRet));

	return 0;
}


/**
 * @testcase 				ITc_vce_get_command_count_p
 * @author					SRID(manoj.g2)
 * @reviewer				SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				To test vce_get_command_count
 * @scenario				Call vce_main, vce_get_command_count
 * @apicovered				vce_main, vce_get_command_count
 * @passcase				If vce_get_command_count return VCE_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vce_get_command_count
int ITc_vce_get_command_count_p(void)
{
	int nRet = VceStartMain();
	START_TEST_VCE;

	PRINT_RESULT(VCE_ERROR_NONE, nRet, "VceStartMain", VoiceControlEngineGetError(nRet));

	int nCount = -1;
	vce_cmd_h hVCEcommand = NULL;

	nRet = vce_get_command_count(hVCEcommand, &nCount);
	PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_get_command_count", VoiceControlEngineGetError(nRet));

	if( nCount < 0)
	{
		FPRINTF("[Line : %d][%s] nCount value is not set : value is %d \\n", __LINE__, API_NAMESPACE, nCount);
		return 1;
	}

	return 0;
}

/**
 * @testcase 				ITc_vce_get_audio_type_p
 * @author					SRID(manoj.g2)
 * @reviewer				SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				To test vce_get_audio_type
 * @scenario				Call vce_get_audio_type
 * @apicovered				vce_main, vce_get_audio_type
 * @passcase				If vce_get_audio_type return VCE_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vce_get_audio_type
int ITc_vce_get_audio_type_p(void)
{
	int nRet = VceStartMain();
	START_TEST_VCE;

	PRINT_RESULT(VCE_ERROR_NONE, nRet, "VceStartMain", VoiceControlEngineGetError(nRet));

	char *audioType = NULL;

	nRet = vce_get_audio_type(&audioType);
	PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_get_audio_type", VoiceControlEngineGetError(nRet));
	CHECK_HANDLE(audioType, "vce_get_audio_type");

	return 0;
}


/**
 * @testcase 				ITc_vce_start_stop_recording_p
 * @author					SRID(manoj.g2)
 * @reviewer				SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				To test vce_main, vce_start_recording, vce_stop_recording
 * @scenario				Call vce_main, vce_start_recording, vce_stop_recording
 * @apicovered				vce_main, vce_start_recording, vce_stop_recording
 * @passcase				If vce_start_recording, vce_stop_recording return VCE_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vce_start_recording, vce_stop_recording
int ITc_vce_start_stop_recording_p(void)
{
	int nRet = VceStartMain();
	START_TEST_VCE;

	PRINT_RESULT(VCE_ERROR_NONE, nRet, "VceStartMain", VoiceControlEngineGetError(nRet));

	nRet = vce_start_recording();
	PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_start_recording", VoiceControlEngineGetError(nRet));

	nRet = vce_stop_recording();
	PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_stop_recording", VoiceControlEngineGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vce_set_private_data_requested_cb_p
 * @author					SRID(manoj.g2)
 * @reviewer				SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				To test vce_main, vce_set_private_data_requested_cb
 * @scenario				Call vce_main, vce_set_private_data_requested_cb
 * @apicovered				vce_main, vce_set_private_data_requested_cb
 * @passcase				If vce_set_private_data_requested_cb return VCE_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vce_set_private_data_requested_cb
int ITc_vce_set_private_data_requested_cb_p(void)
{
	int nRet = VceStartMain();
	START_TEST_VCE;

	PRINT_RESULT(VCE_ERROR_NONE, nRet, "VceStartMain", VoiceControlEngineGetError(nRet));

	nRet = vce_set_private_data_requested_cb(VcePrivateDataRequestedCallback);
	PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_set_private_data_requested_cb", VoiceControlEngineGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vce_send_specific_engine_result_p
 * @author					SRID(manoj.g2)
 * @reviewer				SRID(nibha.sharma)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				To test vce_main, vce_send_specific_engine_result
 * @scenario				Call vce_main, vce_send_specific_engine_result
 * @apicovered				vce_main, vce_send_specific_engine_result
 * @passcase				If vce_send_specific_engine_result return VCE_ERROR_NONE
 * @failcase				If Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vce_send_specific_engine_result
int ITc_vce_send_specific_engine_result_p(void)
{
	int nRet = VceStartMain();
	START_TEST_VCE;

	PRINT_RESULT(VCE_ERROR_NONE, nRet, "VceStartMain", VoiceControlEngineGetError(nRet));

	const char *pszEngineAppID = "org.tizen.vc-engine-default";
	const char *pszEvent = "sendTTS";
	const char *pszResult = "Success";
	void *UserInfo = NULL;

	nRet = vce_send_specific_engine_result(pszEngineAppID, pszEvent, pszResult, UserInfo);
	PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_send_specific_engine_result", VoiceControlEngineGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vce_set_unset_specific_engine_request_cb_p
 * @author					SRID(manoj.g2)
 * @reviewer				SRID(nibha.sharma)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				To test vce_main, vce_set_specific_engine_request_cb, vce_unset_specific_engine_request_cb
 * @scenario				Call vce_main, vce_set_specific_engine_request_cb, vce_unset_specific_engine_request_cb
 * @apicovered				vce_main, vce_set_specific_engine_request_cb, vce_unset_specific_engine_request_cb
 * @passcase				If vce_set_specific_engine_request_cb, vce_unset_specific_engine_request_cb return VCE_ERROR_NONE
 * @failcase				If Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vce_set_specific_engine_request_cb, vce_unset_specific_engine_request_cb
int ITc_vce_set_unset_specific_engine_request_cb_p(void)
{
	int nRet = VceStartMain();
	START_TEST_VCE;

	PRINT_RESULT(VCE_ERROR_NONE, nRet, "VceStartMain", VoiceControlEngineGetError(nRet));

	nRet = vce_set_specific_engine_request_cb(VceSpecificEngineRequestCB);
	PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_set_specific_engine_request_cb", VoiceControlEngineGetError(nRet));

	nRet = vce_unset_specific_engine_request_cb();
	PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_unset_specific_engine_request_cb", VoiceControlEngineGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vce_send_feedback_audio_format_p
 * @author					SRID(manoj.g2)
 * @reviewer				SRID(nibha.sharma)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				To test vce_main, vce_send_feedback_audio_format
 * @scenario				Call vce_main, vce_send_feedback_audio_format
 * @apicovered				vce_main, vce_send_feedback_audio_format
 * @passcase				If vce_send_feedback_audio_format return VCE_ERROR_NONE
 * @failcase				If Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vce_send_feedback_audio_format
int ITc_vce_send_feedback_audio_format_p(void)
{
	int nRet = VceStartMain();
	START_TEST_VCE;

	PRINT_RESULT(VCE_ERROR_NONE, nRet, "VceStartMain", VoiceControlEngineGetError(nRet));

	vce_audio_channel_e eVCEAudioChannelArr[] = {
		VCE_AUDIO_CHANNEL_MONO,
		VCE_AUDIO_CHANNEL_STEREO,
	};

	vce_audio_type_e eVCEAudioTypeArr[] = {
		VCE_AUDIO_TYPE_PCM_S16_LE,
		VCE_AUDIO_TYPE_PCM_U8,
	};

	int nRate = 16000;
	int nChannelEnumCount = sizeof(eVCEAudioChannelArr)/ sizeof(eVCEAudioChannelArr[0]);
	int nTypeEnumCount = sizeof(eVCEAudioTypeArr)/ sizeof(eVCEAudioTypeArr[0]);

	int nChannelCount, nTypeCount;

	for(nChannelCount = 0; nChannelCount < nChannelEnumCount; nChannelCount++)
	{
		for(nTypeCount = 0; nTypeCount < nTypeEnumCount; nTypeCount++)
		{
			nRet = vce_send_feedback_audio_format(nRate, eVCEAudioChannelArr[nChannelCount], eVCEAudioTypeArr[nTypeCount]);
			PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_send_feedback_audio_format", VoiceControlEngineGetError(nRet));
		}
	}

	return 0;
}

/**
 * @testcase 				ITc_vce_send_feedback_streaming_p
 * @author					SRID(manoj.g2)
 * @reviewer				SRID(nibha.sharma)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				To test vce_main, vce_send_feedback_streaming
 * @scenario				Call vce_main, vce_send_feedback_streaming
 * @apicovered				vce_main, vce_send_feedback_streaming
 * @passcase				If vce_send_feedback_streaming return VCE_ERROR_NONE
 * @failcase				If Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vce_send_feedback_audio_format
int ITc_vce_send_feedback_streaming_p(void)
{
	int nRet = VceStartMain();
	START_TEST_VCE;

	PRINT_RESULT(VCE_ERROR_NONE, nRet, "VceStartMain", VoiceControlEngineGetError(nRet));

	char* szTxtFeedback = "Start sending feedback streaming";

	vce_feedback_event_e eVCEFeedbackEventARR[] = {
		VCE_FEEDBACK_EVENT_FAIL,
		VCE_FEEDBACK_EVENT_START,
		VCE_FEEDBACK_EVENT_CONTINUE,
		VCE_FEEDBACK_EVENT_FINISH
	};

	int nEnumCount = sizeof(eVCEFeedbackEventARR)/ sizeof(eVCEFeedbackEventARR[0]);
	int nCount;

	for(nCount = 0; nCount < nEnumCount; nCount++)
	{
		nRet = vce_send_feedback_streaming(eVCEFeedbackEventARR[nCount], szTxtFeedback, strlen(szTxtFeedback));
		PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_send_feedback_streaming", VoiceControlEngineGetError(nRet));
	}
	return 0;
}

/**
 * @testcase 				ITc_vce_set_unset_request_tts_cb_p
 * @author				SRID(p.chauhan)
 * @reviewer				SRID(priya.kohli)
 * @type 				auto
 * @since_tizen 			5.0
 * @description				To set and unset the TTS feedback request callback function
 * @scenario				Call vce_main, vce_set_request_tts_cb, vce_unset_request_tts_cb
 * @apicovered				vce_main, vce_set_request_tts_cb, vce_unset_request_tts_cb
 * @passcase				If vce_set_request_tts_cb, vce_unset_request_tts_cb return VCE_ERROR_NONE
 * @failcase				If Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vce_set_request_tts_cb, vce_unset_request_tts_cb
int ITc_vce_set_unset_request_tts_cb_p(void)
{
	int nRet = VceStartMain();
	START_TEST_VCE;

	PRINT_RESULT(VCE_ERROR_NONE, nRet, "VceStartMain", VoiceControlEngineGetError(nRet));

	void *UserInfo = NULL;
	nRet = vce_set_request_tts_cb(VceRequestTtsCB, UserInfo);
	PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_set_request_tts_cb", VoiceControlEngineGetError(nRet));

	nRet = vce_unset_request_tts_cb();
	PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_unset_request_tts_cb", VoiceControlEngineGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vce_set_unset_cancel_tts_cb_p
 * @author				SRID(p.chauhan)
 * @reviewer				SRID(priya.kohli)
 * @type 				auto
 * @since_tizen 			5.0
 * @description				To set and unset the TTS feedback cancellation callback function
 * @scenario				Call vce_main, vce_set_cancel_tts_cb, vce_unset_cancel_tts_cb
 * @apicovered				vce_main, vce_set_cancel_tts_cb, vce_unset_cancel_tts_cb
 * @passcase				If vce_set_cancel_tts_cb, vce_unset_cancel_tts_cb return VCE_ERROR_NONE
 * @failcase				If Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vce_set_cancel_tts_cb, vce_unset_cancel_tts_cb
int ITc_vce_set_unset_cancel_tts_cb_p(void)
{
	int nRet = VceStartMain();
	START_TEST_VCE;

	PRINT_RESULT(VCE_ERROR_NONE, nRet, "VceStartMain", VoiceControlEngineGetError(nRet));

	void *UserInfo = NULL;
	nRet = vce_set_cancel_tts_cb(VceCancelTtsCB, UserInfo);
	PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_set_cancel_tts_cb", VoiceControlEngineGetError(nRet));

	nRet = vce_unset_cancel_tts_cb();
	PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_unset_cancel_tts_cb", VoiceControlEngineGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vce_set_unset_tts_audio_format_request_cb_p
 * @author				SRID(p.chauhan)
 * @reviewer				SRID(priya.kohli)
 * @type 				auto
 * @since_tizen 			5.0
 * @description				To set and unset the TTS audio format request callback function
 * @scenario				Call vce_main, vce_set_tts_audio_format_request_cb, vce_unset_get_tts_audio_format_cb
 * @apicovered				vce_main, vce_set_cancel_tts_cb, vce_unset_cancel_tts_cb
 * @passcase				If vce_set_tts_audio_format_request_cb, vce_unset_get_tts_audio_format_cb return VCE_ERROR_NONE
 * @failcase				If Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vce_set_tts_audio_format_request_cb, vce_unset_get_tts_audio_format_cb
int ITc_vce_set_unset_tts_audio_format_request_cb_p(void)
{
	int nRet = VceStartMain();
	START_TEST_VCE;

	PRINT_RESULT(VCE_ERROR_NONE, nRet, "VceStartMain", VoiceControlEngineGetError(nRet));

	void *UserInfo = NULL;
	nRet = vce_set_tts_audio_format_request_cb(VceTtsAudioFormatRequestCB, UserInfo);
	PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_set_tts_audio_format_request_cb", VoiceControlEngineGetError(nRet));

	nRet = vce_unset_get_tts_audio_format_cb();
	PRINT_RESULT(VCE_ERROR_NONE, nRet, "vce_unset_get_tts_audio_format_cb", VoiceControlEngineGetError(nRet));

	return 0;
}
