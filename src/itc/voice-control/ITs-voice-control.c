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

//& set: VoiceControl

/** @addtogroup itc-voice-control
*  @ingroup itc
*  @{
*/

static int g_vcState = -1;
/****************************************************Callback Start****************************************************/

/**
 * @function 		CommandListCallBack
 * @description	 	Callback Function
 * @parameter		vc_cmd_h vc_command, void* user_data
 * @return 			NA
 */
static bool CommandListCallBack(vc_cmd_h vc_command, void* user_data)
{
	if ( vc_command == NULL )
	{
		FPRINTF("[Line : %d][%s] Invalid vc_command handle in callback CommandListCallBack \\n", __LINE__, API_NAMESPACE);
		return false;
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "CommandListCallBack");
#endif

	g_CallBackHit = true;
	return false;
}

/**
 * @function 		StateChangedCallBack
 * @description	 	Callback Function
 * @parameter		vc_state_e previous, vc_state_e current, void* user_data
 * @return 			NA
 */
void StateChangedCallBack(vc_state_e previous, vc_state_e current, void* user_data)
{
	if ( previous < 0 || previous > 2 || current < 0 || current > 2 )
	{
		FPRINTF("[Line : %d][%s] Invalid previous or current state in callback StateChangedCallBack\\n", __LINE__, API_NAMESPACE);
		return;
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "StateChangedCallBack");
#endif

	g_vcState = current;
	FPRINTF("[Line : %d][%s] Current state = %d\\n", __LINE__, API_NAMESPACE, g_vcState);
	g_CallBackHit = true;
	return;
}

/**
 * @function 		ErrorCallBack
 * @description	 	Callback Function
 * @parameter		vc_error_e reason, void *user_data
 * @return 			NA
 */
static void ErrorCallBack(vc_error_e reason, void *user_data)
{
	if ( reason < VC_ERROR_NONE || reason > VC_ERROR_EMPTY )
	{
		FPRINTF("[Line : %d][%s] Invalid reason code in callback ErrorCallBack\\n", __LINE__, API_NAMESPACE);
		return;
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ErrorCallBack");
#endif

	g_CallBackHit = true;
	return;
}

/**
 * @function 		LanguageChangedCallBack
 * @description	 	Callback Function
 * @parameter		const char* previous, const char* current, void* user_data
 * @return 			NA
 */
static void LanguageChangedCallBack(const char* previous, const char* current, void* user_data)
{
	if ( previous == NULL || current == NULL )
	{
		FPRINTF("[Line : %d][%s] Invalid argument in callback LanguageChangedCallBack\\n", __LINE__, API_NAMESPACE);
		return;
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "LanguageChangedCallBack");
#endif

	g_CallBackHit = true;
	return;
}

/**
 * @function 		ServiceStateChangedCallBack
 * @description	 	Callback Function
 * @parameter		vc_service_state_e previous, vc_service_state_e current, void* user_data
 * @return 			NA
 */
static void ServiceStateChangedCallBack(vc_service_state_e previous, vc_service_state_e current, void* user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ServiceStateChangedCallBack");
#endif

	g_CallBackHit = true;
	return;
}

/**
 * @function 		ResultCallBack
 * @description	 	Callback Function
 * @parameter		vc_result_event_e event, vc_cmd_list_h vc_cmd_list, const char* result, void *user_data
 * @return 			NA
 */
static void ResultCallBack(vc_result_event_e event, vc_cmd_list_h vc_cmd_list, const char* result, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ResultCallBack");
#endif

	g_CallBackHit = true;
	return;
}

/**
 * @function 		LanguageSupportedCallback
 * @description	 	Callback Function
 * @parameter		const char* language, void* user_data
 * @return 			NA
 */
static bool LanguageSupportedCallback(const char* language, void* user_data)
{
	if ( language == NULL )
	{	
		FPRINTF("[Line : %d][%s] Invalid parameter in callback LanguageSupportedCallback\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "LanguageSupportedCallback");
#endif

	g_CallBackHit = true;
	return false;
}

/*****************************************************Callback End*****************************************************/

/**
 * @function 		ITs_voice_control_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_voice_control_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}


	g_bVoiceControlStartup = false;
	g_bIsVcFeatureSupported = TCTCheckSystemInfoFeatureSupported(MICROPHONEFEATURE, API_NAMESPACE) && TCTCheckSystemInfoFeatureSupported(SPEECHCONTROLFEATURE, API_NAMESPACE);

	int nRet = vc_initialize();
	if ( !g_bIsVcFeatureSupported )
	{
		FPRINTF("[Line : %d][%s] Microphone/SpeechControl feature not supported\\n", __LINE__, API_NAMESPACE);
		PRINT_RESULTNONE_CLEANUP(VC_ERROR_NOT_SUPPORTED, nRet, "vc_initialize", VoiceControlGetError(nRet), vc_deinitialize());
	}
	else
	{
		PRINT_RESULTNONE(VC_ERROR_NONE, nRet, "vc_initialize", VoiceControlGetError(nRet));
	}
	g_bVoiceControlStartup = true;
	return;
}


/**
 * @function 		ITs_voice_control_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_voice_control_cleanup(void)
{
	if ( g_bVoiceControlStartup == true && g_bIsVcFeatureSupported == true )
	{
		vc_deinitialize();
	}

	return;
}

/** @addtogroup itc-voice-control-testcases
*  @brief 		Integration testcases for module voice-control
*  @ingroup 	itc-voice-control
*  @{
*/

/**
 * @testcase 				ITc_vc_cmd_create_destroy_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_cmd_create and vc_cmd_destroy
 * @scenario				Call vc_cmd_create, vc_cmd_destroy
 * @apicovered				vc_cmd_create, vc_cmd_destroy
 * @passcase				If vc_cmd_create and vc_cmd_destroy returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_cmd_create and vc_cmd_destroy
int ITc_vc_cmd_create_destroy_p(void)
{
	START_TEST;
	int nRet = -1;
	vc_cmd_h hVcCommand = NULL;

	nRet = vc_cmd_create(&hVcCommand);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_cmd_create", VoiceControlGetError(nRet));

	if ( hVcCommand == NULL )
	{
		FPRINTF("[Line : %d][%s] vc_cmd_create failed. hVcCommand is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRet = vc_cmd_destroy(hVcCommand);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_cmd_destroy", VoiceControlGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vc_cmd_set_get_command_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_cmd_set_command and vc_cmd_get_command
 * @scenario				Call vc_cmd_set_command, vc_cmd_get_command
 * @apicovered				vc_cmd_create, vc_cmd_set_command, vc_cmd_get_command, vc_cmd_destroy
 * @passcase				If vc_cmd_set_command and vc_cmd_get_command returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_cmd_set_command and vc_cmd_get_command
int ITc_vc_cmd_set_get_command_p(void)
{
	START_TEST;
	int nRet = -1;
	vc_cmd_h hVcCommand = NULL;
	char *szVoiceCommand = NULL;

	nRet = vc_cmd_create(&hVcCommand);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_cmd_create", VoiceControlGetError(nRet));

	if ( hVcCommand == NULL )
	{
		FPRINTF("[Line : %d][%s] vc_cmd_create failed. hVcCommand is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRet = vc_cmd_set_command(hVcCommand, VOICECOMMAND);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_set_command", VoiceControlGetError(nRet), vc_cmd_destroy(hVcCommand));

	nRet = vc_cmd_get_command(hVcCommand, &szVoiceCommand);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_get_command", VoiceControlGetError(nRet), vc_cmd_destroy(hVcCommand));
	CHECK_HANDLE_CLEANUP(szVoiceCommand, "vc_cmd_get_command", vc_cmd_destroy(hVcCommand));
	PRINT_RESULT_CLEANUP(0, strcmp(szVoiceCommand, VOICECOMMAND), "vc_cmd_get_command", "String Mismatch", FREE_MEMORY(szVoiceCommand); vc_cmd_destroy(hVcCommand););

	FREE_MEMORY(szVoiceCommand);
	
	nRet = vc_cmd_destroy(hVcCommand);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_cmd_destroy", VoiceControlGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vc_cmd_set_get_type_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_cmd_set_type and vc_cmd_get_type
 * @scenario				Call vc_cmd_set_type, vc_cmd_get_type
 * @apicovered				vc_cmd_set_type, vc_cmd_get_type
 * @passcase				If vc_cmd_set_type and vc_cmd_get_type returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_cmd_set_type and vc_cmd_get_type
int ITc_vc_cmd_set_get_type_p(void)
{
	START_TEST;
	int nRet = -1;
	vc_cmd_h hVcCommand = NULL;
	int nVoiceType = VC_COMMAND_TYPE_FOREGROUND;

	nRet = vc_cmd_create(&hVcCommand);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_cmd_create", VoiceControlGetError(nRet));

	nRet = vc_cmd_set_type(hVcCommand, VC_COMMAND_TYPE_BACKGROUND);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_set_type", VoiceControlGetError(nRet), vc_cmd_destroy(hVcCommand));

	nRet = vc_cmd_get_type(hVcCommand, &nVoiceType);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_get_type", VoiceControlGetError(nRet), vc_cmd_destroy(hVcCommand));
	PRINT_RESULT_CLEANUP(VC_COMMAND_TYPE_BACKGROUND, nVoiceType, "vc_cmd_get_type", "Type Mismatch", vc_cmd_destroy(hVcCommand));

	nRet = vc_cmd_destroy(hVcCommand);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_cmd_destroy", VoiceControlGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vc_cmd_list_create_destroy_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_cmd_list_create and vc_cmd_list_destroy
 * @scenario				Call vc_cmd_list_create, vc_cmd_list_destroy
 * @apicovered				vc_cmd_list_create, vc_cmd_list_destroy
 * @passcase				If vc_cmd_list_create and vc_cmd_list_destroy returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_cmd_list_create and vc_cmd_list_destroy
int ITc_vc_cmd_list_create_destroy_p(void)
{
	START_TEST;
	int nRet = -1;
	vc_cmd_list_h hVcCommandList = NULL;

	nRet = vc_cmd_list_create(&hVcCommandList);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_cmd_list_create", VoiceControlGetError(nRet));

	
	if ( hVcCommandList == NULL )
	{
		FPRINTF("[Line : %d][%s] vc_cmd_list_create failed. hVcCommandList is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRet = vc_cmd_list_destroy(hVcCommandList, false);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_cmd_list_destroy", VoiceControlGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vc_cmd_list_add_remove_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_cmd_list_add and vc_cmd_list_remove
 * @scenario				Call vc_cmd_list_add, vc_cmd_list_remove
 * @apicovered				vc_cmd_list_create, vc_cmd_list_add, vc_cmd_list_remove, vc_cmd_list_destroy
 * @passcase				If vc_cmd_list_add and vc_cmd_list_remove returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_cmd_list_add and vc_cmd_list_remove
int ITc_vc_cmd_list_add_remove_p(void)
{
	START_TEST;
	int nRet = -1;
	vc_cmd_list_h hVcCommandList = NULL;

	nRet = CreateCommands();
	PRINT_RESULT(0, nRet, "CreateCommands", "Returned Value Not Correct");

	nRet = vc_cmd_list_create(&hVcCommandList);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_list_create", VoiceControlGetError(nRet), DestroyCommands());

	if ( hVcCommandList == NULL )
	{
		FPRINTF("[Line : %d][%s] vc_cmd_list_create failed. hVcCommandList is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRet = vc_cmd_list_add(hVcCommandList, g_arrhVcCommand[0]);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_list_add", VoiceControlGetError(nRet), vc_cmd_list_destroy(hVcCommandList, false); DestroyCommands());

	nRet = vc_cmd_list_remove(hVcCommandList, g_arrhVcCommand[0]);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_list_remove", VoiceControlGetError(nRet), vc_cmd_list_destroy(hVcCommandList, false); DestroyCommands());

	nRet = vc_cmd_list_destroy(hVcCommandList, false);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_list_destroy", VoiceControlGetError(nRet), DestroyCommands());

	nRet = DestroyCommands();
	PRINT_RESULT(0, nRet, "DestroyCommands", "Returned Value Not Correct");

	return 0;
}

/**
 * @testcase 				ITc_vc_cmd_list_first_last_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_cmd_list_first and vc_cmd_list_last
 * @scenario				Call vc_cmd_list_first, vc_cmd_list_last
 * @apicovered				vc_cmd_list_first, vc_cmd_list_last
 * @passcase				If vc_cmd_list_first and vc_cmd_list_last returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_cmd_list_first and vc_cmd_list_last
int ITc_vc_cmd_list_first_last_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = CreateCommandList();
	PRINT_RESULT(0, nRet, "CreateCommandList", "Returned Value Not Correct");

	nRet = vc_cmd_list_first(g_hVcCommandList);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_list_first", VoiceControlGetError(nRet), DestroyCommandList());

	nRet = vc_cmd_list_last(g_hVcCommandList);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_list_last", VoiceControlGetError(nRet), DestroyCommandList());

	nRet = DestroyCommandList();
	PRINT_RESULT(0, nRet, "DestroyCommandList", "Returned Value Not Correct");

	return 0;
}

/**
 * @testcase 				ITc_vc_cmd_list_next_prev_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_cmd_list_next and vc_cmd_list_prev
 * @scenario				Call vc_cmd_list_next, vc_cmd_list_prev
 * @apicovered				vc_cmd_list_next, vc_cmd_list_prev
 * @passcase				If vc_cmd_list_next and vc_cmd_list_prev returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_cmd_list_next and vc_cmd_list_prev
int ITc_vc_cmd_list_next_prev_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = CreateCommandList();
	PRINT_RESULT(0, nRet, "CreateCommandList", "Returned Value Not Correct");

	nRet = vc_cmd_list_first(g_hVcCommandList);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_list_first", VoiceControlGetError(nRet), DestroyCommandList());

	nRet = vc_cmd_list_next(g_hVcCommandList);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_list_next", VoiceControlGetError(nRet), DestroyCommandList());

	nRet = vc_cmd_list_prev(g_hVcCommandList);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_list_prev", VoiceControlGetError(nRet), DestroyCommandList());

	nRet = DestroyCommandList();
	PRINT_RESULT(0, nRet, "DestroyCommandList", "Returned Value Not Correct");

	return 0;
}

/**
 * @testcase 				ITc_vc_cmd_list_get_current_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_cmd_list_get_current
 * @scenario				Call vc_cmd_list_get_current
 * @apicovered				vc_cmd_list_first, vc_cmd_list_get_current
 * @passcase				If vc_cmd_list_get_current returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_cmd_list_get_current
int ITc_vc_cmd_list_get_current_p(void)
{
	START_TEST;
	int nRet = -1;
	vc_cmd_h hVcCommand = NULL;

	nRet = CreateCommandList();
	PRINT_RESULT(0, nRet, "CreateCommandList", "Returned Value Not Correct");

	nRet = vc_cmd_list_first(g_hVcCommandList);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_list_first", VoiceControlGetError(nRet), DestroyCommandList());

	nRet = vc_cmd_list_get_current(g_hVcCommandList, &hVcCommand);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_list_get_current", VoiceControlGetError(nRet), DestroyCommandList());
	CHECK_HANDLE_CLEANUP(hVcCommand, "vc_cmd_list_get_current", DestroyCommandList());

	nRet = DestroyCommandList();
	PRINT_RESULT(0, nRet, "DestroyCommandList", "Returned Value Not Correct");

	return 0;
}

/**
 * @testcase 				ITc_vc_cmd_list_get_count_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_cmd_list_get_count
 * @scenario				Call vc_cmd_list_get_count
 * @apicovered				vc_cmd_list_get_count
 * @passcase				If vc_cmd_list_get_count returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_cmd_list_get_count
int ITc_vc_cmd_list_get_count_p(void)
{
	START_TEST;
	int nRet = -1;
	int nCount = -1;

	nRet = CreateCommandList();
	PRINT_RESULT(0, nRet, "CreateCommandList", "Returned Value Not Correct");

	nRet = vc_cmd_list_get_count(g_hVcCommandList, &nCount);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_list_get_count", VoiceControlGetError(nRet), DestroyCommandList());

	if ( nCount == -1)
	{
		FPRINTF("[Line : %d][%s] vc_cmd_list_get_count failed. nCount is -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRet = DestroyCommandList();
	PRINT_RESULT(0, nRet, "DestroyCommandList", "Returned Value Not Correct");

	return 0;
}

/**
 * @testcase 				ITc_vc_cmd_list_foreach_commands_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_cmd_list_foreach_commands
 * @scenario				Call vc_cmd_list_foreach_commands
 * @apicovered				vc_cmd_list_foreach_commands
 * @passcase				If vc_cmd_list_foreach_commands returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_cmd_list_foreach_commands
int ITc_vc_cmd_list_foreach_commands_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = CreateCommandList();
	PRINT_RESULT(0, nRet, "CreateCommandList", "Returned Value Not Correct");

	g_CallBackHit = false;
	nRet = vc_cmd_list_foreach_commands(g_hVcCommandList, CommandListCallBack, NULL);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_list_foreach_commands", VoiceControlGetError(nRet), DestroyCommandList());
	IterateEcoreLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "vc_cmd_list_foreach_commands", "CallBack Not Invoked", DestroyCommandList());

	nRet = DestroyCommandList();
	PRINT_RESULT(0, nRet, "DestroyCommandList", "Returned Value Not Correct");

	return 0;
}

/**
 * @testcase 				ITc_vc_initialize_deinitialize_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_initialize and vc_deinitialize
 * @scenario				Call vc_initialize, vc_deinitialize
 * @apicovered				vc_initialize, vc_deinitialize
 * @passcase				If vc_initialize and vc_deinitialize returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_initialize and vc_deinitialize
int ITc_vc_initialize_deinitialize_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = vc_deinitialize();
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_deinitialize", VoiceControlGetError(nRet));

	nRet = vc_initialize();
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_initialize", VoiceControlGetError(nRet));

	nRet = vc_deinitialize();
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_deinitialize", VoiceControlGetError(nRet));

	nRet = vc_initialize();
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_initialize", VoiceControlGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vc_set_unset_state_changed_cb_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_set_state_changed_cb and vc_unset_state_changed_cb
 * @scenario				Call vc_set_state_changed_cb, vc_unset_state_changed_cb
 * @apicovered				vc_set_state_changed_cb, vc_prepare, vc_unprepare, vc_unset_state_changed_cb
 * @passcase				If vc_set_state_changed_cb and vc_unset_state_changed_cb returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_set_state_changed_cb and vc_unset_state_changed_cb
int ITc_vc_set_unset_state_changed_cb_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = vc_set_state_changed_cb(StateChangedCallBack, NULL);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_set_state_changed_cb", VoiceControlGetError(nRet));

	g_CallBackHit = false;
	nRet = vc_prepare();
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_prepare", VoiceControlGetError(nRet), vc_unset_state_changed_cb());
	IterateEcoreLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "vc_prepare", "CallBack Not Invoked", vc_unset_state_changed_cb());

	g_CallBackHit = false;
	nRet = vc_unprepare();
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_unprepare", VoiceControlGetError(nRet), vc_unset_state_changed_cb());
	IterateEcoreLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "vc_unprepare", "CallBack Not Invoked", vc_unset_state_changed_cb());

	nRet = vc_unset_state_changed_cb();
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_unset_state_changed_cb", VoiceControlGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vc_prepare_unprepare_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_prepare and vc_unprepare
 * @scenario				Call vc_prepare, vc_unprepare
 * @apicovered				vc_set_state_changed_cb, vc_prepare, vc_unprepare, vc_unset_state_changed_cb
 * @passcase				If vc_prepare and vc_unprepare returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_prepare and vc_unprepare
int ITc_vc_prepare_unprepare_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = vc_set_state_changed_cb(StateChangedCallBack, NULL);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_set_state_changed_cb", VoiceControlGetError(nRet));

	g_CallBackHit = false;
	nRet = vc_prepare();
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_prepare", VoiceControlGetError(nRet), vc_unset_state_changed_cb());
	IterateEcoreLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "vc_prepare", "CallBack Not Invoked", vc_unset_state_changed_cb());

	g_CallBackHit = false;
	nRet = vc_unprepare();
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_unprepare", VoiceControlGetError(nRet), vc_unset_state_changed_cb());
	IterateEcoreLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "vc_unprepare", "CallBack Not Invoked", vc_unset_state_changed_cb());

	nRet = vc_unset_state_changed_cb();
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_unset_state_changed_cb", VoiceControlGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vc_get_state_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_get_state
 * @scenario				Call vc_get_state
 * @apicovered				vc_get_state
 * @passcase				If vc_get_state returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_get_state
int ITc_vc_get_state_p(void)
{
	START_TEST;
	int nRet = -1;
	vc_state_e eVcState = VC_STATE_READY;

	nRet = vc_get_state(&eVcState);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_get_state", VoiceControlGetError(nRet));
	PRINT_RESULT(VC_STATE_INITIALIZED, eVcState, "vc_get_state", "State Mismatch");

	return 0;
}

/**
 * @testcase 				ITc_vc_get_service_state_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_get_service_state
 * @scenario				Call vc_get_service_state
 * @apicovered				vc_get_service_state
 * @passcase				If vc_get_service_state returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			vc_set_state_changed_cb,vc_prepare
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_get_service_state
int ITc_vc_get_service_state_p(void)
{
	START_TEST;
	int nRet = -1;
	vc_service_state_e eVcServiceState = -1;
	vc_state_e eVcState = -1;
	
	nRet = vc_set_state_changed_cb(StateChangedCallBack, NULL);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_set_state_changed_cb", VoiceControlGetError(nRet));

	g_CallBackHit = false;
	nRet = vc_prepare();
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_prepare", VoiceControlGetError(nRet), vc_unset_state_changed_cb());
	IterateEcoreLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "vc_prepare", "CallBack Not Invoked", vc_unset_state_changed_cb());
	
	nRet = vc_get_state(&eVcState);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_get_state", VoiceControlGetError(nRet), vc_unprepare();vc_unset_state_changed_cb());
	PRINT_RESULT_CLEANUP(VC_STATE_READY, eVcState, "vc_get_state", "State Mismatch", vc_unprepare();vc_unset_state_changed_cb());

	nRet = vc_get_service_state(&eVcServiceState);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_get_service_state", VoiceControlGetError(nRet), vc_unprepare();vc_unset_state_changed_cb());

	if ( eVcServiceState < VC_SERVICE_STATE_NONE || eVcServiceState > VC_SERVICE_STATE_PROCESSING)
	{
		FPRINTF("[Line : %d][%s] vc_get_service_state failed, giving invalid state\\n", __LINE__, API_NAMESPACE);
		vc_unprepare();
		vc_unset_state_changed_cb();
		return 1;
	}
	//vc_unprepare();
	g_CallBackHit = false;
	nRet = vc_unprepare();
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_unprepare", VoiceControlGetError(nRet), vc_unset_state_changed_cb());
	IterateEcoreLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "vc_unprepare", "CallBack Not Invoked", vc_unset_state_changed_cb());

	nRet = vc_unset_state_changed_cb();
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_unset_state_changed_cb", VoiceControlGetError(nRet));
	
	return 0;
}

/**
 * @testcase 				ITc_vc_set_unset_command_list_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_set_command_list and vc_unset_command_list
 * @scenario				Call vc_set_command_list, vc_unset_command_list
 * @apicovered				vc_set_command_list, vc_unset_command_list
 * @passcase				If vc_set_command_list and vc_unset_command_list returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_set_command_list and vc_unset_command_list
int ITc_vc_set_unset_command_list_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = CreateCommandList();
	PRINT_RESULT(0, nRet, "CreateCommandList", "Returned Value Not Correct");

	nRet = PrepareVoiceControl();
	PRINT_RESULT(0, nRet, "PrepareVoiceControl", "Returned Value Not Correct");

	nRet = vc_set_command_list(g_hVcCommandList, VC_COMMAND_TYPE_BACKGROUND);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_set_command_list", VoiceControlGetError(nRet), UnPrepareVoiceControl(); DestroyCommandList());

	nRet = vc_unset_command_list(VC_COMMAND_TYPE_BACKGROUND);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_unset_command_list", VoiceControlGetError(nRet), UnPrepareVoiceControl(); DestroyCommandList());

	nRet = UnPrepareVoiceControl();
	PRINT_RESULT_CLEANUP(0, nRet, "UnPrepareVoiceControl", "Returned Value Not Correct", DestroyCommandList());

	nRet = DestroyCommandList();
	PRINT_RESULT(0, nRet, "DestroyCommandList", "Returned Value Not Correct");

	return 0;
}

/**
 * @testcase 				ITc_vc_set_unset_error_cb_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_set_error_cb and vc_unset_error_cb
 * @scenario				Call vc_set_error_cb, vc_unset_error_cb
 * @apicovered				vc_set_error_cb, vc_unset_error_cb
 * @passcase				If vc_set_error_cb and vc_unset_error_cb returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_set_error_cb and vc_unset_error_cb
int ITc_vc_set_unset_error_cb_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = vc_set_error_cb(ErrorCallBack, NULL);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_set_error_cb", VoiceControlGetError(nRet));

	nRet = vc_unset_error_cb();
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_unset_error_cb", VoiceControlGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vc_set_unset_current_language_changed_cb_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_set_current_language_changed_cb and vc_unset_current_language_changed_cb
 * @scenario				Call vc_set_current_language_changed_cb, vc_unset_current_language_changed_cb
 * @apicovered				vc_set_current_language_changed_cb, vc_unset_current_language_changed_cb
 * @passcase				If vc_set_current_language_changed_cb and vc_unset_current_language_changed_cb returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_set_current_language_changed_cb and vc_unset_current_language_changed_cb
int ITc_vc_set_unset_current_language_changed_cb_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = vc_set_current_language_changed_cb(LanguageChangedCallBack, NULL);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_set_current_language_changed_cb", VoiceControlGetError(nRet));

	nRet = vc_unset_current_language_changed_cb();
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_unset_current_language_changed_cb", VoiceControlGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vc_set_unset_service_state_changed_cb_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_set_service_state_changed_cb and vc_unset_service_state_changed_cb
 * @scenario				Call vc_set_service_state_changed_cb, vc_unset_service_state_changed_cb
 * @apicovered				vc_set_service_state_changed_cb, vc_unset_service_state_changed_cb
 * @passcase				If vc_set_service_state_changed_cb and vc_unset_service_state_changed_cb returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_set_service_state_changed_cb and vc_unset_service_state_changed_cb
int ITc_vc_set_unset_service_state_changed_cb_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = vc_set_service_state_changed_cb(ServiceStateChangedCallBack, NULL);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_set_service_state_changed_cb", VoiceControlGetError(nRet));

	nRet = vc_unset_service_state_changed_cb();
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_unset_service_state_changed_cb", VoiceControlGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vc_set_unset_result_cb_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_set_result_cb and vc_unset_result_cb
 * @scenario				Call vc_set_result_cb, vc_unset_result_cb
 * @apicovered				vc_set_result_cb, vc_unset_result_cb
 * @passcase				If vc_set_result_cb and vc_unset_result_cb returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_set_result_cb and vc_unset_result_cb
int ITc_vc_set_unset_result_cb_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = vc_set_result_cb(ResultCallBack, NULL);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_set_result_cb", VoiceControlGetError(nRet));

	nRet = vc_unset_result_cb();
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_unset_result_cb", VoiceControlGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vc_get_current_language_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_get_current_language
 * @scenario				Call vc_get_current_language
 * @apicovered				vc_get_current_language
 * @passcase				If vc_get_current_language returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_get_current_language
int ITc_vc_get_current_language_p(void)
{
	START_TEST;
	int nRet = -1;
	char *szLanguage = NULL;

	nRet = vc_get_current_language(&szLanguage);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_get_current_language", VoiceControlGetError(nRet));
	
	if ( szLanguage == NULL )
	{
		FPRINTF("[Line : %d][%s] vc_get_current_language failed. szLanguage is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	FREE_MEMORY(szLanguage);

	return 0;
}

/**
 * @testcase 				ITc_vc_foreach_supported_languages_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_foreach_supported_languages
 * @scenario				Call vc_foreach_supported_languages
 * @apicovered				vc_foreach_supported_languages
 * @passcase				If vc_foreach_supported_languages returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_foreach_supported_languages
int ITc_vc_foreach_supported_languages_p(void)
{
	START_TEST;
	int nRet = -1;

	g_CallBackHit = false;
	nRet = vc_foreach_supported_languages(LanguageSupportedCallback, NULL);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_foreach_supported_languages", VoiceControlGetError(nRet));
	IterateEcoreLoop();
	PRINT_RESULT(true, g_CallBackHit, "vc_foreach_supported_languages", "CallBack Not Invoked");

	return 0;
}

/**
 * @testcase 				ITc_vc_get_system_command_list_p
 * @author					SRID(a.pandia1)
 * @reviewer				SRID(shilpa.j)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				Gets the system command list
 * @scenario				Gets the system command list
 * @apicovered				vc_get_system_command_list, vc_set_state_changed_cb, vc_prepare, vc_unprepare, vc_unset_state_changed_cb
 * @passcase				If vc_get_system_command_list and precondition APIS returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: Gets the system command list
int ITc_vc_get_system_command_list_p(void)
{
	START_TEST;
	int nRet = -1;
	vc_cmd_list_h h_List = NULL;
	
	nRet = vc_set_state_changed_cb(StateChangedCallBack, NULL);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_set_state_changed_cb", VoiceControlGetError(nRet));

	g_CallBackHit = false;
	nRet = vc_prepare();
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_prepare", VoiceControlGetError(nRet), vc_unset_state_changed_cb());
	IterateEcoreLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "vc_prepare", "CallBack Not Invoked", vc_unset_state_changed_cb());

	if(VC_STATE_READY != g_vcState) 
	{
		FPRINTF("[Line : %d][%s] Current state is not VC_STATE_READY so exiting TC\\n", __LINE__, API_NAMESPACE);
		vc_unprepare();
		vc_unset_state_changed_cb();
		return 1;
	}
	
	// Target API
	nRet = vc_get_system_command_list(&h_List);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_get_system_command_list", VoiceControlGetError(nRet), vc_unprepare();vc_unset_state_changed_cb());
	vc_unprepare();
	vc_unset_state_changed_cb();
	
	FREE_MEMORY(h_List);
	
	nRet = vc_unprepare();
	PRINT_RESULT_NORETURN(VC_ERROR_NONE, nRet, "vc_unprepare", VoiceControlGetError(nRet));

	nRet = vc_unset_state_changed_cb();
	PRINT_RESULT_NORETURN(VC_ERROR_NONE, nRet, "vc_unset_state_changed_cb", VoiceControlGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vc_set_invocation_name_p
 * @author					SRID(a.pandia1)
 * @reviewer				SRID(shilpa.j)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				Sets invocation name
 * @scenario				Sets invocation name
 * @apicovered				vc_set_invocation_name, vc_set_state_changed_cb, vc_prepare, vc_unprepare, vc_unset_state_changed_cb
 * @passcase				If vc_set_invocation_name and precondition APIS returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: Sets invocation name
int ITc_vc_set_invocation_name_p(void)
{
	START_TEST;
	int nRet = -1;
	const char* pszInvocName = "Test Name";
	
	nRet = vc_set_state_changed_cb(StateChangedCallBack, NULL);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_set_state_changed_cb", VoiceControlGetError(nRet));

	g_CallBackHit = false;
	nRet = vc_prepare();
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_prepare", VoiceControlGetError(nRet), vc_unset_state_changed_cb());
	IterateEcoreLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "vc_prepare", "CallBack Not Invoked", vc_unset_state_changed_cb());

	if(VC_STATE_READY != g_vcState) 
	{
		FPRINTF("[Line : %d][%s] Current state is not VC_STATE_READY so exiting TC\\n", __LINE__, API_NAMESPACE);
		vc_unprepare();
		vc_unset_state_changed_cb();
		return 1;
	}
	
	// Target API
	nRet = vc_set_invocation_name(pszInvocName);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_set_invocation_name", VoiceControlGetError(nRet), vc_unprepare();vc_unset_state_changed_cb());
	
	nRet = vc_unprepare();
	PRINT_RESULT_NORETURN(VC_ERROR_NONE, nRet, "vc_unprepare", VoiceControlGetError(nRet));

	nRet = vc_unset_state_changed_cb();
	PRINT_RESULT_NORETURN(VC_ERROR_NONE, nRet, "vc_unset_state_changed_cb", VoiceControlGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vc_request_dialog_p
 * @author					SRID(a.pandia1)
 * @reviewer				SRID(shilpa.j)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				Requests to start the dialogue
 * @scenario				Requests to start the dialogue
 * @apicovered				vc_request_dialog, vc_set_state_changed_cb, vc_prepare, vc_unprepare, vc_unset_state_changed_cb
 * @passcase				If vc_request_dialog and precondition APIS returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: Requests to start the dialogue
int ITc_vc_request_dialog_p(void)
{
	START_TEST;
	int nRet = -1;
	const char* pszDispTxt = "Display Name";
	const char* pszUttTxt = "Spoken Text";
	bool bAutoStart = true;
		
	nRet = vc_set_state_changed_cb(StateChangedCallBack, NULL);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_set_state_changed_cb", VoiceControlGetError(nRet));

	g_CallBackHit = false;
	nRet = vc_prepare();
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_prepare", VoiceControlGetError(nRet), vc_unset_state_changed_cb());
	IterateEcoreLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "vc_prepare", "CallBack Not Invoked", vc_unset_state_changed_cb());

	if(VC_STATE_READY != g_vcState) 
	{
		FPRINTF("[Line : %d][%s] Current state is not VC_STATE_READY so exiting TC\\n", __LINE__, API_NAMESPACE);
		vc_unprepare();
		vc_unset_state_changed_cb();
		return 1;
	}
	
	// Target API
	nRet = vc_request_dialog(pszDispTxt, pszUttTxt, bAutoStart);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_request_dialog", VoiceControlGetError(nRet), vc_unprepare();vc_unset_state_changed_cb());
	
	nRet = vc_unprepare();
	PRINT_RESULT_NORETURN(VC_ERROR_NONE, nRet, "vc_unprepare", VoiceControlGetError(nRet));

	nRet = vc_unset_state_changed_cb();
	PRINT_RESULT_NORETURN(VC_ERROR_NONE, nRet, "vc_unset_state_changed_cb", VoiceControlGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vc_cmd_get_unfixed_command_p
 * @author					SRID(a.pandia1)
 * @reviewer				SRID(shilpa.j)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				Gets the unfixed command
 * @scenario				Gets the unfixed command
 * @apicovered				vc_cmd_get_unfixed_command, vc_cmd_create, vc_cmd_destroy
 * @passcase				If vc_cmd_create, vc_cmd_get_unfixed_command and vc_cmd_destroy returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: Gets the unfixed command
int ITc_vc_cmd_get_unfixed_command_p(void)
{
	START_TEST;
	int nRet = -1;
	vc_cmd_h hVcCommand = NULL;
	char *pszCmd = NULL;
	
	nRet = vc_cmd_create(&hVcCommand);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_cmd_create", VoiceControlGetError(nRet));
	CHECK_HANDLE(hVcCommand, "vc_cmd_create");
	
	// Target API
	nRet = vc_cmd_get_unfixed_command(hVcCommand, &pszCmd);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_get_unfixed_command", VoiceControlGetError(nRet),FREE_MEMORY(pszCmd);vc_cmd_destroy(hVcCommand));
	FREE_MEMORY(pszCmd);
		
	nRet = vc_cmd_destroy(hVcCommand);
	PRINT_RESULT_NORETURN(VC_ERROR_NONE, nRet, "vc_cmd_destroy", VoiceControlGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vc_cmd_set_get_format_p
 * @author					SRID(a.pandia1)
 * @reviewer				SRID(shilpa.j)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				Sets and gets the command format
 * @scenario				Sets and gets the command format
 * @apicovered				vc_cmd_set_format, vc_cmd_get_format, vc_cmd_create, vc_cmd_destroy
 * @passcase				If vc_cmd_create, vc_cmd_set_format, vc_cmd_get_format and vc_cmd_destroy returns VC_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: Sets and gets the command format
int ITc_vc_cmd_set_get_format_p(void)
{
	START_TEST;
	int nRet = -1;
	vc_cmd_h hVcCommand = NULL;
	int nGetFormat = -1;
	
	nRet = vc_cmd_create(&hVcCommand);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_cmd_create", VoiceControlGetError(nRet));
	CHECK_HANDLE(hVcCommand, "vc_cmd_create");
	
	// Target API
	nRet = vc_cmd_set_format(hVcCommand, VC_COMMAND_FORMAT_FIXED);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_set_format", VoiceControlGetError(nRet), vc_cmd_destroy(hVcCommand));
	
	nRet = vc_cmd_get_format(hVcCommand, &nGetFormat);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_get_format", VoiceControlGetError(nRet), vc_cmd_destroy(hVcCommand));
	
	if(nGetFormat != VC_COMMAND_FORMAT_FIXED)
	{
		FPRINTF("[Line : %d][%s] Set and get format values mismatch\\n", __LINE__, API_NAMESPACE);
		vc_cmd_destroy(hVcCommand);
		return 1;
	}
	
	nRet = vc_cmd_destroy(hVcCommand);
	PRINT_RESULT_NORETURN(VC_ERROR_NONE, nRet, "vc_cmd_destroy", VoiceControlGetError(nRet));

	return 0;
}
/** @} */
/** @} */
