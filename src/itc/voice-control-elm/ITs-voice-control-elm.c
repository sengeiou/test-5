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
#include "ITs-voice-control-elm-common.h"

//& set: VoiceControl-elm

/** @addtogroup itc-voice-control-elm
*  @ingroup itc
*  @{
*/

/****************************************************Callback Start****************************************************/

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
		FPRINTF("[Line : %d][%s] Invalid parameter in callback LanguageChangedCallBack\\n", __LINE__, API_NAMESPACE);
		return;
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "LanguageChangedCallBack");
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

/**
 * @function 		WidgetSupportedCallback
 * @description	 	Callback Function
 * @parameter		const char* widget, void* user_data
 * @return 			NA
 */
bool WidgetSupportedCallback(const char* widget, void* user_data)
{
	if ( widget == NULL )
	{
		FPRINTF("[Line : %d][%s] Invalid parameter in callback WidgetSupportedCallback\\n", __LINE__, API_NAMESPACE);
		return false;
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "WidgetSupportedCallback");
#endif

	g_CallBackHit = true;
	strncpy(g_szWidget, widget, PATH_LEN - 1 );
	return false;
}

/**
 * @function 		ActionSupportedCallback
 * @description	 	Callback Function
 * @parameter		const char* action, void* user_data
 * @return 			NA
 */
bool ActionSupportedCallback(const char* action, void* user_data)
{
	if ( action == NULL )
	{
		FPRINTF("[Line : %d][%s] Invalid parameter in callback ActionSupportedCallback\\n", __LINE__, API_NAMESPACE);
		return false;
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ActionSupportedCallback");
#endif

	g_CallBackHit = true;
	strncpy(g_szAction, action, PATH_LEN - 1);
	return false;
}

/*****************************************************Callback End*****************************************************/

/**
 * @function 		ITs_voice_control_elm_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_voice_control_elm_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	g_bVoiceControlStartup = false;
	g_bIsVcFeatureSupported = TCTCheckSystemInfoFeatureSupported(MICROPHONEFEATURE, API_NAMESPACE) && TCTCheckSystemInfoFeatureSupported(SPEECHCONTROLFEATURE, API_NAMESPACE);
	int nRet = vc_elm_initialize();
	if ( !g_bIsVcFeatureSupported)
	{
		FPRINTF("[Line : %d][%s] Microphone/SpeechControl feature not supported\\n", __LINE__, API_NAMESPACE);
		PRINT_RESULTNONE_CLEANUP(VC_ELM_ERROR_NOT_SUPPORTED, nRet, "vc_elm_initialize", VoiceControlElmGetError(nRet), vc_elm_deinitialize());
	}
	else
	{
		PRINT_RESULTNONE(VC_ELM_ERROR_NONE, nRet, "vc_elm_initialize", VoiceControlElmGetError(nRet));
	}

	g_bVoiceControlStartup = true;
	return;
}


/**
 * @function 		ITs_voice_control_elm_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_voice_control_elm_cleanup(void)
{
	if ( g_bVoiceControlStartup == true && g_bIsVcFeatureSupported == true )
	{
		vc_elm_deinitialize();
	}
	return;
}

/** @addtogroup itc-voice-control-elm-testcases
*  @brief 		Integration testcases for module voice-control-elm
*  @ingroup 	itc-voice-control-elm
*  @{
*/

/**
 * @testcase 				ITc_vc_elm_initialize_deinitialize_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_elm_initialize and vc_elm_deinitialize
 * @scenario				Call vc_elm_initialize, vc_elm_deinitialize
 * @apicovered				vc_elm_initialize, vc_elm_deinitialize
 * @passcase				If vc_elm_initialize and vc_elm_deinitialize returns VC_ELM_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_elm_initialize and vc_elm_deinitialize
int ITc_vc_elm_initialize_deinitialize_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = vc_elm_deinitialize();
	PRINT_RESULT(VC_ELM_ERROR_NONE, nRet, "vc_elm_deinitialize", VoiceControlElmGetError(nRet));

	nRet = vc_elm_initialize();
	PRINT_RESULT(VC_ELM_ERROR_NONE, nRet, "vc_elm_initialize", VoiceControlElmGetError(nRet));

	nRet = vc_elm_deinitialize();
	PRINT_RESULT(VC_ELM_ERROR_NONE, nRet, "vc_elm_deinitialize", VoiceControlElmGetError(nRet));

	nRet = vc_elm_initialize();
	PRINT_RESULT(VC_ELM_ERROR_NONE, nRet, "vc_elm_initialize", VoiceControlElmGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vc_elm_get_current_language_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_elm_get_current_language
 * @scenario				Call vc_elm_get_current_language
 * @apicovered				vc_elm_get_current_language
 * @passcase				If vc_elm_get_current_language returns VC_ELM_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_elm_get_current_language
int ITc_vc_elm_get_current_language_p(void)
{
	START_TEST;
	int nRet = -1;
	char *szLanguage = NULL;

	nRet = vc_elm_get_current_language(&szLanguage);
	PRINT_RESULT(VC_ELM_ERROR_NONE, nRet, "vc_elm_get_current_language", VoiceControlElmGetError(nRet));
	
	if ( szLanguage == NULL )
	{
		FPRINTF("[Line : %d][%s] vc_elm_get_current_language failed. szLanguage is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	FREE_MEMORY(szLanguage);

	return 0;
}

/**
 * @testcase 				ITc_vc_elm_set_unset_current_language_changed_cb_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_elm_set_current_language_changed_cb and vc_elm_unset_current_language_changed_cb
 * @scenario				Call vc_elm_set_current_language_changed_cb, vc_elm_unset_current_language_changed_cb
 * @apicovered				vc_elm_set_current_language_changed_cb, vc_elm_unset_current_language_changed_cb
 * @passcase				If vc_elm_set_current_language_changed_cb and vc_elm_unset_current_language_changed_cb returns VC_ELM_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_elm_set_current_language_changed_cb and vc_elm_unset_current_language_changed_cb
int ITc_vc_elm_set_unset_current_language_changed_cb_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = vc_elm_set_current_language_changed_cb(LanguageChangedCallBack, NULL);
	PRINT_RESULT(VC_ELM_ERROR_NONE, nRet, "vc_elm_set_current_language_changed_cb", VoiceControlElmGetError(nRet));

	nRet = vc_elm_unset_current_language_changed_cb();
	PRINT_RESULT(VC_ELM_ERROR_NONE, nRet, "vc_elm_unset_current_language_changed_cb", VoiceControlElmGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_vc_elm_foreach_supported_languages_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_elm_foreach_supported_languages
 * @scenario				Call vc_elm_foreach_supported_languages
 * @apicovered				vc_elm_foreach_supported_languages
 * @passcase				If vc_elm_foreach_supported_languages returns VC_ELM_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_elm_foreach_supported_languages
int ITc_vc_elm_foreach_supported_languages_p(void)
{
	START_TEST;
	int nRet = -1;

	g_CallBackHit = false;
	nRet = vc_elm_foreach_supported_languages(LanguageSupportedCallback, NULL);
	PRINT_RESULT(VC_ELM_ERROR_NONE, nRet, "vc_elm_foreach_supported_languages", VoiceControlElmGetError(nRet));
	IterateEcoreLoop();
	PRINT_RESULT(true, g_CallBackHit, "vc_elm_foreach_supported_languages", "CallBack Not Invoked");

	return 0;
}

/**
 * @testcase 				ITc_vc_elm_foreach_supported_widgets_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_elm_foreach_supported_widgets
 * @scenario				Call vc_elm_foreach_supported_widgets
 * @apicovered				vc_elm_foreach_supported_widgets
 * @passcase				If vc_elm_foreach_supported_widgets returns VC_ELM_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_elm_foreach_supported_widgets
int ITc_vc_elm_foreach_supported_widgets_p(void)
{
	START_TEST;
	int nRet = -1;

	g_CallBackHit = false;
	nRet = vc_elm_foreach_supported_widgets(WidgetSupportedCallback, NULL);
	PRINT_RESULT(VC_ELM_ERROR_NONE, nRet, "vc_elm_foreach_supported_widgets", VoiceControlElmGetError(nRet));
	IterateEcoreLoop();
	PRINT_RESULT(true, g_CallBackHit, "vc_elm_foreach_supported_widgets", "CallBack Not Invoked");

	return 0;
}

/**
 * @testcase 				ITc_vc_elm_create_destroy_object_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_elm_create_object and vc_elm_destroy
 * @scenario				Call vc_elm_create_object, vc_elm_destroy
 * @apicovered				vc_elm_create_object, vc_elm_destroy
 * @passcase				If vc_elm_create_object and vc_elm_destroy returns VC_ELM_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_elm_create_object and vc_elm_destroy
int ITc_vc_elm_create_destroy_object_p(void)
{
	START_TEST;
	int nRet = -1;
	vc_elm_h hVcElm = NULL;

	nRet = CreateEvasWindow();
	PRINT_RESULT(0, nRet, "CreateEvasWindow", "Return Value Not Correct");

	nRet = vc_elm_create_object(g_pEvasButton, &hVcElm);
	PRINT_RESULT_CLEANUP(VC_ELM_ERROR_NONE, nRet, "vc_elm_create_object", VoiceControlElmGetError(nRet), DeleteEvasWindow());

	if ( hVcElm == NULL )
	{
		FPRINTF("[Line : %d][%s] vc_elm_create_object failed. hVcElm is NULL\\n", __LINE__, API_NAMESPACE);
		DeleteEvasWindow();
		return 1;
	}
	
	nRet = vc_elm_destroy(hVcElm);
	PRINT_RESULT_CLEANUP(VC_ELM_ERROR_NONE, nRet, "vc_elm_destroy", VoiceControlElmGetError(nRet), DeleteEvasWindow());

	DeleteEvasWindow();

	return 0;
}

/**
 * @testcase 				ITc_vc_elm_create_destroy_item_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_elm_create_item and vc_elm_destroy
 * @scenario				Call vc_elm_create_item, vc_elm_destroy
 * @apicovered				vc_elm_create_item, vc_elm_destroy
 * @passcase				If vc_elm_create_item and vc_elm_destroy returns VC_ELM_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_elm_create_item and vc_elm_destroy
int ITc_vc_elm_create_destroy_item_p(void)
{
	START_TEST;
	int nRet = -1;
	vc_elm_h hVcElm = NULL;

	nRet = CreateEvasWindow();
	PRINT_RESULT(0, nRet, "CreateEvasWindow", "Return Value Not Correct");

	nRet = vc_elm_create_item(g_pEvasItem, &hVcElm);
	PRINT_RESULT_CLEANUP(VC_ELM_ERROR_NONE, nRet, "vc_elm_create_item", VoiceControlElmGetError(nRet), DeleteEvasWindow());

	if ( hVcElm == NULL )
	{
		FPRINTF("[Line : %d][%s] vc_elm_create_item failed. hVcElm is NULL\\n", __LINE__, API_NAMESPACE);
		DeleteEvasWindow();
		return 1;
	}
	
	nRet = vc_elm_destroy(hVcElm);
	PRINT_RESULT_CLEANUP(VC_ELM_ERROR_NONE, nRet, "vc_elm_destroy", VoiceControlElmGetError(nRet), DeleteEvasWindow());

	DeleteEvasWindow();

	return 0;
}

/**
 * @testcase 				ITc_vc_elm_foreach_supported_actions_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_elm_foreach_supported_actions
 * @scenario				Call vc_elm_foreach_supported_actions
 * @apicovered				vc_elm_foreach_supported_actions
 * @passcase				If vc_elm_foreach_supported_actions returns VC_ELM_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_elm_foreach_supported_actions
int ITc_vc_elm_foreach_supported_actions_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = GetWidgetName();
	PRINT_RESULT(0, nRet, "GetWidgetName", "Return Value Not Correct");

	g_CallBackHit = false;
	nRet = vc_elm_foreach_supported_actions(g_szWidget, ActionSupportedCallback, NULL);
	PRINT_RESULT(VC_ELM_ERROR_NONE, nRet, "vc_elm_foreach_supported_actions", VoiceControlElmGetError(nRet));
	IterateEcoreLoop();
	PRINT_RESULT(true, g_CallBackHit, "vc_elm_foreach_supported_actions", "CallBack Not Invoked");

	return 0;
}

/**
 * @testcase 				ITc_vc_elm_get_action_command_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_elm_get_action_command
 * @scenario				Call vc_elm_get_action_command
 * @apicovered				vc_elm_get_action_command
 * @passcase				If vc_elm_get_action_command returns VC_ELM_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_elm_get_action_command
int ITc_vc_elm_get_action_command_p(void)
{
	START_TEST;
	int nRet = -1;
	char *pszCommand = NULL;

	nRet = GetActionName();
	PRINT_RESULT(0, nRet, "GetActionName", "Return Value Not Correct");

	nRet = vc_elm_get_action_command(g_szAction, &pszCommand);
	PRINT_RESULT(VC_ELM_ERROR_NONE, nRet, "vc_elm_get_action_command", VoiceControlElmGetError(nRet));
	CHECK_HANDLE(pszCommand, "vc_elm_get_action_command");
	FREE_MEMORY(pszCommand);

	return 0;
}

/**
 * @testcase 				ITc_vc_elm_set_unset_command_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_elm_set_command and vc_elm_unset_command
 * @scenario				Call vc_elm_set_command, vc_elm_unset_command
 * @apicovered				vc_elm_set_command, vc_elm_unset_command
 * @passcase				If vc_elm_set_command and vc_elm_unset_command returns VC_ELM_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_elm_set_command and vc_elm_unset_command
int ITc_vc_elm_set_unset_command_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = GetCommandName();
	PRINT_RESULT(0, nRet, "GetCommandName", "Return Value Not Correct");

	nRet = CreateVcElmObject();
	PRINT_RESULT(0, nRet, "CreateVcElmObject", "Return Value Not Correct");

	nRet = vc_elm_set_command(g_hVcElm, g_szCommand);
	PRINT_RESULT_CLEANUP(VC_ELM_ERROR_NONE, nRet, "vc_elm_set_command", VoiceControlElmGetError(nRet), DeleteVcElmObject());

	nRet = vc_elm_unset_command(g_hVcElm);
	PRINT_RESULT_CLEANUP(VC_ELM_ERROR_NONE, nRet, "vc_elm_unset_command", VoiceControlElmGetError(nRet), DeleteVcElmObject());

	DeleteVcElmObject();

	return 0;
}

/**
 * @testcase 				ITc_vc_elm_set_unset_command_hint_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_elm_set_command_hint and vc_elm_unset_command_hint
 * @scenario				Call vc_elm_set_command_hint, vc_elm_unset_command_hint
 * @apicovered				vc_elm_set_command_hint, vc_elm_unset_command_hint
 * @passcase				If vc_elm_set_command_hint and vc_elm_unset_command_hint returns VC_ELM_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_elm_set_command_hint and vc_elm_unset_command_hint
int ITc_vc_elm_set_unset_command_hint_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = CreateVcElmObjectWithCommand();
	PRINT_RESULT(0, nRet, "CreateVcElmObjectWithCommand", "Return Value Not Correct");

	nRet = vc_elm_set_command_hint(g_hVcElm, COMMANDHINT);
	PRINT_RESULT_CLEANUP(VC_ELM_ERROR_NONE, nRet, "vc_elm_set_command_hint", VoiceControlElmGetError(nRet), DeleteVcElmObjectWithCommand());

	nRet = vc_elm_unset_command_hint(g_hVcElm);
	PRINT_RESULT_CLEANUP(VC_ELM_ERROR_NONE, nRet, "vc_elm_unset_command_hint", VoiceControlElmGetError(nRet), DeleteVcElmObjectWithCommand());

	DeleteVcElmObjectWithCommand();

	return 0;
}

/**
 * @testcase 				ITc_vc_elm_set_get_command_hint_direction_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_elm_set_command_hint_direction and vc_elm_get_command_hint_direction
 * @scenario				Call vc_elm_set_command_hint_direction, vc_elm_get_command_hint_direction
 * @apicovered				vc_elm_set_command_hint_direction, vc_elm_get_command_hint_direction
 * @passcase				If vc_elm_set_command_hint_direction and vc_elm_get_command_hint_direction returns VC_ELM_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_elm_set_command_hint_direction and vc_elm_get_command_hint_direction
int ITc_vc_elm_set_get_command_hint_direction_p(void)
{
	START_TEST;
	int nRet = -1;
	vc_elm_direction_e eDirection = VC_ELM_DIRECTION_RIGHT;

	nRet = CreateVcElmObjectWithCommandHint();
	PRINT_RESULT(0, nRet, "CreateVcElmObjectWithCommandHint", "Return Value Not Correct");

	nRet = vc_elm_set_command_hint_direction(g_hVcElm, VC_ELM_DIRECTION_CENTER);
	PRINT_RESULT_CLEANUP(VC_ELM_ERROR_NONE, nRet, "vc_elm_set_command_hint_direction", VoiceControlElmGetError(nRet), DeleteVcElmObjectWithCommandHint());

	nRet = vc_elm_get_command_hint_direction(g_hVcElm, &eDirection);
	PRINT_RESULT_CLEANUP(VC_ELM_ERROR_NONE, nRet, "vc_elm_get_command_hint_direction", VoiceControlElmGetError(nRet), DeleteVcElmObjectWithCommandHint());
	PRINT_RESULT_CLEANUP(VC_ELM_DIRECTION_CENTER, eDirection, "vc_elm_get_command_hint_direction", "Direction Mismatch", DeleteVcElmObjectWithCommandHint());

	DeleteVcElmObjectWithCommandHint();

	return 0;
}

/**
 * @testcase 				ITc_vc_elm_set_get_command_hint_offset_p
 * @author					SRID(abhishek1.g)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test vc_elm_set_command_hint_offset and vc_elm_get_command_hint_offset
 * @scenario				Call vc_elm_set_command_hint_offset, vc_elm_get_command_hint_offset
 * @apicovered				vc_elm_set_command_hint_offset, vc_elm_get_command_hint_offset
 * @passcase				If vc_elm_set_command_hint_offset and vc_elm_get_command_hint_offset returns VC_ELM_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test vc_elm_set_command_hint_offset and vc_elm_get_command_hint_offset
int ITc_vc_elm_set_get_command_hint_offset_p(void)
{
	START_TEST;
	int nRet = -1;
	int nXoffset = 1, nYoffset = 1;

	nRet = CreateVcElmObjectWithCommandHint();
	PRINT_RESULT(0, nRet, "CreateVcElmObjectWithCommandHint", "Return Value Not Correct");

	nRet = vc_elm_set_command_hint_offset(g_hVcElm, 0, 0);
	PRINT_RESULT_CLEANUP(VC_ELM_ERROR_NONE, nRet, "vc_elm_set_command_hint_offset", VoiceControlElmGetError(nRet), DeleteVcElmObjectWithCommandHint());

	nRet = vc_elm_get_command_hint_offset(g_hVcElm, &nXoffset, &nYoffset);
	PRINT_RESULT_CLEANUP(VC_ELM_ERROR_NONE, nRet, "vc_elm_get_command_hint_offset", VoiceControlElmGetError(nRet), DeleteVcElmObjectWithCommandHint());
	PRINT_RESULT_CLEANUP(0, nXoffset, "vc_elm_get_command_hint_offset", "X Offset Mismatch", DeleteVcElmObjectWithCommandHint());
	PRINT_RESULT_CLEANUP(0, nYoffset, "vc_elm_get_command_hint_offset", "Y Offset Mismatch", DeleteVcElmObjectWithCommandHint());

	DeleteVcElmObjectWithCommandHint();

	return 0;
}

/** @} */
/** @} */