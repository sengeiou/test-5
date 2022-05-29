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

extern void transfer_arg(int * argc, char ** argv[]);

static ttse_request_callback_s g_tts_engine_callback = {0, };

static int g_argc = 1;
static char **g_argv = NULL;


static int tts_engine_get_info(char** engine_uuid, char** engine_name, char** setting_ug_name, bool* use_network)
{
	*engine_uuid = strdup("23E456F7-ABC8-9DCA-XYZ1-D9876A5BCDE4");
	*engine_name = strdup("TTS engine sample");
	*setting_ug_name = strdup("libttsenginesample.so");
	*use_network = false;

	return 0;
}

static int tts_engine_initialize(void)
{
	return 0;
}

static int tts_engine_deinitialize(void)
{
	return 0;
}

static int tts_engine_foreach_voices(ttse_supported_voice_cb callback, void* user_data)
{
	char * lang = "en_US";
	int vctype = TTSE_VOICE_TYPE_FEMALE;

	bool ret = callback(lang, vctype, user_data);

	return 0;
}

static int tts_engine_is_valid_voice(const char* language, int type, bool* is_valid)
{
	*is_valid = true;

	return 0;
}

static int tts_engine_set_pitch(int pitch)
{
	return 0;
}

static int tts_engine_load_voice(const char* language, int type)
{
	return 0;
}

static int tts_engine_unload_voice(const char* language, int type)
{
	return 0;
}

static int tts_engine_start_synth(const char* language, int type, const char* text, int speed, const char* appid, const char* credential, void* user_data)
{
	return 0;
}

static int tts_engine_cancel_synth(void)
{
	return 0;
}

static int tts_engine_check_app_agreed(const char* appid, bool* is_agreed)
{
	return 0;
}

static bool tts_engine_need_app_credential(void)
{
	return false;
}

static int tts_engine_private_data_set_callback(const char* key, const char* data)
{
	return 0;
}

static int tts_engine_private_data_requested_callback(const char* key, char** data)
{
	return 0;
}
/**
* @function 		ITs_ttse_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_ttse_startup(void)
{
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
	if ( !g_bFeatureSupported )
	{
		g_bFeatureNotSupported = true;
		return;
	}
	transfer_arg(&g_argc, &g_argv);

	g_tts_engine_callback.version = 1;
	g_tts_engine_callback.get_info = tts_engine_get_info;

	g_tts_engine_callback.initialize = tts_engine_initialize;
	g_tts_engine_callback.deinitialize = tts_engine_deinitialize;

	g_tts_engine_callback.start_synth = tts_engine_start_synth;
	g_tts_engine_callback.cancel_synth = tts_engine_cancel_synth;

	g_tts_engine_callback.foreach_voices = tts_engine_foreach_voices;
	g_tts_engine_callback.is_valid_voice = tts_engine_is_valid_voice;

	g_tts_engine_callback.set_pitch = tts_engine_set_pitch;

	g_tts_engine_callback.load_voice = tts_engine_load_voice;
	g_tts_engine_callback.unload_voice = tts_engine_unload_voice;

	g_tts_engine_callback.check_app_agreed = tts_engine_check_app_agreed;
	g_tts_engine_callback.need_app_credential = tts_engine_need_app_credential;
}
/**
* @function 		ITs_ttse_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_ttse_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_TTSE_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& purpose stte main function
//& type: auto
/**
* @testcase				ITc_ttse_main_p
* @since_tizen			3.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			ttse main function
* @scenario				call ttse_main
* @apicovered			ttse_main
* @passcase				If ttse_main api gets pass
* @failcase				If ttse_main api gets fail
* @precondition			NA
* @postcondition		NA
*/
int ITc_ttse_main_p(void)
{
	START_TEST_TTSE;

	int nRet = ttse_main(g_argc, g_argv, &g_tts_engine_callback);
	PRINT_RESULT(TTSE_ERROR_NONE, nRet, "ttse_main", TtseGetError(nRet));

	return 0;
}
/**
* @testcase				ITc_ttse_get_speed_range_p
* @since_tizen			3.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			getting speed range
* @scenario				call ttse_get_speed_range
* @apicovered			ttse_get_speed_range
* @passcase				If ttse_get_speed_range api gets pass
* @failcase				If ttse_get_speed_range api gets fail
* @precondition			NA
* @postcondition		NA
*/
int ITc_ttse_get_speed_range_p(void)
{
	START_TEST_TTSE;

	int min = -1;
	int normal = -1;
	int max = -1;

	int nRet = ttse_get_speed_range(&min, &normal, &max);
	PRINT_RESULT(TTSE_ERROR_NONE, nRet, "ttse_get_speed_range", TtseGetError(nRet));

	if((min < 0)||(normal < 0)||(max < 0))
	{
		FPRINTF("[Line : %d][%s] wrong speed value \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}
/**
* @testcase				ITc_ttse_get_pitch_range_p
* @since_tizen			3.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			getting pitch range
* @scenario				call ttse_get_pitch_range
* @apicovered			ttse_get_pitch_range
* @passcase				If ttse_get_pitch_range api gets pass
* @failcase				If ttse_get_pitch_range api gets fail
* @precondition			NA
* @postcondition		NA
*/
int ITc_ttse_get_pitch_range_p(void)
{
	START_TEST_TTSE;

	int min = -1;
	int normal = -1;
	int max = -1;

	int nRet = ttse_get_pitch_range(&min, &normal, &max);
	PRINT_RESULT(TTSE_ERROR_NONE, nRet, "ttse_get_pitch_range", TtseGetError(nRet));

	if((min < 0)||(normal < 0)||(max < 0))
	{
		FPRINTF("[Line : %d][%s] wrong pitch value \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}
/**
* @testcase				ITc_ttse_set_private_data_set_cb_p
* @since_tizen			3.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Sets a callback function for setting the private data
* @scenario				call ttse_set_private_data_set_cb
* @apicovered			ttse_set_private_data_set_cb
* @passcase				If ttse_set_private_data_set_cb api gets pass
* @failcase				If ttse_set_private_data_set_cb api gets fail
* @precondition			NA
* @postcondition		NA
*/
int ITc_ttse_set_private_data_set_cb_p(void)
{
	START_TEST_TTSE;

	int nRet = ttse_main(g_argc, g_argv, &g_tts_engine_callback);
	PRINT_RESULT(TTSE_ERROR_NONE, nRet, "ttse_main", TtseGetError(nRet));
	//As per developer ttse_set_private_data_set_cb API is just for setting callback so can't check callback hit in this case
	nRet = ttse_set_private_data_set_cb(tts_engine_private_data_set_callback);
	PRINT_RESULT(TTSE_ERROR_NONE, nRet, "ttse_set_private_data_set_cb", TtseGetError(nRet));

	return 0;
}
/**
* @testcase				ITc_ttse_set_private_data_requested_cb_p
* @since_tizen			3.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Sets a callback of requesting private data
* @scenario				call ttse_set_private_data_requested_cb
* @apicovered			ttse_set_private_data_requested_cb
* @passcase				If ttse_set_private_data_requested_cb api gets pass
* @failcase				If ttse_set_private_data_requested_cb api gets fail
* @precondition			NA
* @postcondition		NA
*/
int ITc_ttse_set_private_data_requested_cb_p(void)
{
	START_TEST_TTSE;

	int nRet = ttse_main(g_argc, g_argv, &g_tts_engine_callback);
	PRINT_RESULT(TTSE_ERROR_NONE, nRet, "ttse_main", TtseGetError(nRet));
	//As per developer ttse_set_private_data_requested_cb API is just for setting callback so can't check callback hit in this case
	nRet = ttse_set_private_data_requested_cb(tts_engine_private_data_requested_callback);
	PRINT_RESULT(TTSE_ERROR_NONE, nRet, "ttse_set_private_data_requested_cb", TtseGetError(nRet));

	return 0;
}
/** @} */
/** @} */
