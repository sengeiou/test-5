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

/** @addtogroup itc-stte
*  @ingroup itc
*  @{
*/

static stte_request_callback_s g_stt_engine_callback = {0, };

static int g_argc = 1;
static char **g_argv = NULL;

static void stt_engine_transfer_arg(int * argc, char ** argv[])
{
	*argc = g_argc;
	*argv = g_argv;
}

static int stt_engine_get_info(char** engine_uuid, char** engine_name, char** setting_ug_name, bool* use_network)
{
	*engine_uuid = strdup("1ABC23DF-GE45-67E8-ZYX1-12345A6BC789");
	*engine_name = strdup("STT engine sample");
	*setting_ug_name = strdup("libsttenginesample.so");
	*use_network = true;

	return 0;
}
static int stt_engine_initialize(void)
{
	return 0;
}

static int stt_engine_deinitialize(void)
{
	return 0;
}

static int stt_engine_start(const char* language, const char* type, const char* appid, const char* credential, void *user_data)
{
	return 0;
}

static int stt_engine_set_recording_data(const void* data, unsigned int length)
{
	return 0;
}

static int stt_engine_stop(void)
{
	return 0;
}

static int stt_engine_cancel(void)
{
	return 0;
}

static int stt_engine_foreach_langs(stte_supported_language_cb callback, void* user_data)
{
	char * lang = "en_US";
	bool ret = callback((const char*)lang, user_data);

	return 0;
}

static int stt_engine_is_valid_language(const char* language, bool* is_valid)
{
	*is_valid = true;
	return 0;
}

static bool stt_engine_support_silence_detection(void)
{
	return true;
}

static int stt_engine_support_recognition_type(const char* type, bool* is_supported)
{
	*is_supported = true;

	return 0;
}

static int stt_engine_get_recording_format(stte_audio_type_e* types, int* rate, int* channels)
{
	*types = STTE_AUDIO_TYPE_PCM_S16_LE;
	*rate = 16000;
	*channels = 1;

	return 0;
}

static int stt_engine_foreach_result_time(void* time_info, stte_result_time_cb callback, void* user_data)
{
	return 0;
}

static int stt_engine_set_silence_detection(bool is_set)
{
	return 0;
}
static int stt_engine_private_data_set_callback(const char* key, const char* data)
{
	return 0;
}
static int stt_engine_private_data_requested_callback(const char* key, char** data)
{
	return 0;
}
static int stt_engine_check_app_agreed(const char* appid, bool* is_agreed)
{
	return 0;
}
static bool stt_engine_need_app_credential(void)
{
	return false;
}

static int SttAudioTypeCB(const char *audioType, void *user_data)
{
	FPRINTF("[Line : %d][%s] inside SttAudioTypeCB callback \\n", __LINE__, API_NAMESPACE);
	return 0;
}
/**
* @function 		ITs_stte_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_stte_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_STTE_p\\n", __LINE__, API_NAMESPACE);
#endif
	g_bFeatureSupported = true;
	g_bFeatureMismatch = false;
	g_bFeatureNotSupported = false;

	g_bFeatureSupported = TCTCheckSystemInfoFeatureSupported(MICROPHONE_FEATURE, API_NAMESPACE) &&
		TCTCheckSystemInfoFeatureSupported(SPEECH_RECOGNITION_FEATURE, API_NAMESPACE);
	if ( !g_bFeatureSupported )
	{
		g_bFeatureNotSupported = true;
		return;
	}
	stt_engine_transfer_arg(&g_argc, &g_argv);

	g_stt_engine_callback.version = 1;
	g_stt_engine_callback.get_info = stt_engine_get_info;

	g_stt_engine_callback.initialize = stt_engine_initialize;
	g_stt_engine_callback.deinitialize = stt_engine_deinitialize;

	g_stt_engine_callback.start = stt_engine_start;
	g_stt_engine_callback.set_recording = stt_engine_set_recording_data;
	g_stt_engine_callback.stop = stt_engine_stop;
	g_stt_engine_callback.cancel = stt_engine_cancel;

	g_stt_engine_callback.foreach_langs = stt_engine_foreach_langs;
	g_stt_engine_callback.is_valid_lang = stt_engine_is_valid_language;

	g_stt_engine_callback.support_silence = stt_engine_support_silence_detection;
	g_stt_engine_callback.support_recognition_type = stt_engine_support_recognition_type;
	g_stt_engine_callback.get_audio_format = stt_engine_get_recording_format;
	g_stt_engine_callback.foreach_result_time = stt_engine_foreach_result_time;

	g_stt_engine_callback.set_silence_detection = stt_engine_set_silence_detection;

	g_stt_engine_callback.check_app_agreed = stt_engine_check_app_agreed;
	g_stt_engine_callback.need_app_credential = stt_engine_need_app_credential;
}

/**
* @function 		ITs_stte_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_stte_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_STTE_p\\n", __LINE__, API_NAMESPACE);
#endif

	return;
}
//& purpose stte main function
//& type: auto
/**
* @testcase				ITc_stte_main_p
* @since_tizen			3.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			stte main function
* @scenario				call stte_main
* @apicovered			stte_main
* @passcase				If stte_main api gets pass
* @failcase				If stte_main api gets fail
* @precondition			NA
* @postcondition		NA
*/
int ITc_stte_main_p(void)
{
	START_TEST_STTE;

	int nRet = stte_main(g_argc, g_argv, &g_stt_engine_callback);
	PRINT_RESULT(STTE_ERROR_NONE, nRet, "stte_main", StteGetError(nRet));

	return 0;
}
//& purpose stte main function
//& type: auto
/**
* @testcase				ITc_stte_set_private_data_set_cb_p
* @since_tizen			3.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			setting a callback of setting private data
* @scenario				call stte_set_private_data_set_cb
* @apicovered			stte_set_private_data_set_cb
* @passcase				If stte_set_private_data_set_cb api gets pass
* @failcase				If stte_set_private_data_set_cb api gets fail
* @precondition			NA
* @postcondition		NA
*/
int ITc_stte_set_private_data_set_cb_p(void)
{
	START_TEST_STTE;

	int nRet = stte_main(g_argc, g_argv, &g_stt_engine_callback);
	PRINT_RESULT(STTE_ERROR_NONE, nRet, "stte_main", StteGetError(nRet));
	//As per developer stte_set_private_data_set_cb API is just for setting callback so can't check callback hit in this case
	nRet = stte_set_private_data_set_cb(stt_engine_private_data_set_callback);
	PRINT_RESULT(STTE_ERROR_NONE, nRet, "stte_set_private_data_set_cb", StteGetError(nRet));

	return 0;
}
//& purpose stte main function
//& type: auto
/**
* @testcase				ITc_stte_set_private_data_requested_cb_p
* @since_tizen			3.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			setting a callback of setting private data
* @scenario				call stte_set_private_data_requested_cb
* @apicovered			stte_set_private_data_requested_cb
* @passcase				If stte_set_private_data_requested_cb api gets pass
* @failcase				If stte_set_private_data_requested_cb api gets fail
* @precondition			NA
* @postcondition		NA
*/
int ITc_stte_set_private_data_requested_cb_p(void)
{
	START_TEST_STTE;

	int nRet = stte_main(g_argc, g_argv, &g_stt_engine_callback);
	PRINT_RESULT(STTE_ERROR_NONE, nRet, "stte_main", StteGetError(nRet));
	//As per developer stte_set_private_data_requested_cb API is just for setting callback so can't check callback hit in this case
	nRet = stte_set_private_data_requested_cb(stt_engine_private_data_requested_callback);
	PRINT_RESULT(STTE_ERROR_NONE, nRet, "stte_set_private_data_requested_cb", StteGetError(nRet));

	return 0;
}


//& purpose Setting a callback of setting audio type callback
//& type: auto
/**
* @testcase			ITc_stte_set_unset_audio_type_set_cb_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			setting a callback of setting audio type callback
* @scenario			setting a callback of setting audio type callback
* @apicovered			stte_set_private_data_requested_cb
* @passcase			If stte_set_audio_type_set_cb,stte_unset_audio_type_set_cb and precondition API are successful
* @failcase			If stte_set_audio_type_set_cb,stte_unset_audio_type_set_cb and precondition API are fail
* @precondition			NA
* @postcondition		NA
*/
int ITc_stte_set_unset_audio_type_set_cb_p(void)
{
	START_TEST_STTE;

	int nRet = stte_main(g_argc, g_argv, &g_stt_engine_callback);
	PRINT_RESULT(STTE_ERROR_NONE, nRet, "stte_main", StteGetError(nRet));

	nRet = stte_set_audio_type_set_cb(SttAudioTypeCB, NULL);
	PRINT_RESULT(STTE_ERROR_NONE, nRet, "stte_set_audio_type_set_cb", StteGetError(nRet));

	nRet = stte_unset_audio_type_set_cb();
	PRINT_RESULT(STTE_ERROR_NONE, nRet, "stte_unset_audio_type_set_cb", StteGetError(nRet));

	return 0;
}
/** @} */
/** @} */
