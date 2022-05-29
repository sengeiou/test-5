//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-capi-ui-inputmethod-common.h"

//& set: CapiUi-inputmethod

/** @addtogroup itc-capi-ui-inputmethod
*  @ingroup itc
*  @{
*/

ime_event_type_e eEventTypeArray[] = {
	IME_EVENT_TYPE_LANGUAGE,
	IME_EVENT_TYPE_SHIFT_MODE,
	IME_EVENT_TYPE_GEOMETRY};

/**
* @function			InputMethodCreateCb
* @description		Callback for app create
* @parameter		void *user_data
* @return			NA
*/
static void InputMethodCreateCb(void *user_data)
{
	FPRINTF("[Line : %d][%s] InputMethodCreateCb Callback called\\n", __LINE__, API_NAMESPACE);
	((void_f) user_data)();
}

/**
* @function			InputMethodTerminateCb
* @description		Callback for app terminate
* @parameter		void *user_data
* @return			NA
*/
static void InputMethodTerminateCb(void *user_data)
{
	FPRINTF("[Line : %d][%s] InputMethodTerminateCb Callback called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function			InputMethodShowCb
* @description		Callback for app show
* @parameter		void *user_data
* @return			NA
*/
static void InputMethodShowCb(int ic, ime_context_h context, void *user_data)
{
	FPRINTF("[Line : %d][%s] InputMethodShowCb Callback called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function			InputMethodHideCb
* @description		Callback for app hide
* @parameter		void *user_data
* @return			NA
*/
static void InputMethodHideCb(int ic, void *user_data)
{
	FPRINTF("[Line : %d][%s] InputMethodHideCb Callback called\\n", __LINE__, API_NAMESPACE);
}

static ime_callback_s basic_callback = {
	InputMethodCreateCb,
	InputMethodTerminateCb,
	InputMethodShowCb,
	InputMethodHideCb,
};

/**
* @function			ime_app_main
* @description		IME application MUST implement	main entry ime_app_main() function
* @parameter		int, char**
* @return			NA
*/
void ime_app_main(int argc, char **argv)
{
	FPRINTF("[Line : %d][%s] ime_app_main called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function			InputMethodSetFloatingModeCb
* @description		Callback for ime_run to Set Floating Mode
* @parameter		void *user_data
* @return			NA
*/
static void InputMethodSetFloatingModeCb(gpointer user_data)
{
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] InputMethodSetFloatingModeCb Callback called\\n", __LINE__, API_NAMESPACE);
	g_nRet = ime_set_floating_mode(true);
	PRINT_RESULT_NORETURN(IME_ERROR_NONE, g_nRet, "ime_set_floating_mode", InputGetError(g_nRet));
	elm_exit();
}

/**
* @function			InputMethodSetFloatingDragStartCb
* @description		Callback for ime_run to Start drag
* @parameter		void *user_data
* @return			NA
*/
static void InputMethodSetFloatingDragStartCb(gpointer user_data)
{
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] InputMethodSetFloatingDragStartCb Callback called\\n", __LINE__, API_NAMESPACE);
	g_nRet = ime_set_floating_drag_start();
	PRINT_RESULT_NORETURN(IME_ERROR_NONE, g_nRet, "ime_set_floating_drag_start", InputGetError(g_nRet));
	elm_exit();
}

/**
* @function			InputMethodSetFloatingDragEndCb
* @description		Callback for ime_run to Stop drag
* @parameter		void *user_data
* @return			NA
*/
static void InputMethodSetFloatingDragEndCb()
{
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] InputMethodSetFloatingDragEndCb Callback called\\n", __LINE__, API_NAMESPACE);
	g_nRet = ime_set_floating_drag_end();
	PRINT_RESULT_NORETURN(IME_ERROR_NONE, g_nRet, "ime_set_floating_drag_end", InputGetError(g_nRet));
	elm_exit();
}

/**
* @function			InputMethodGetSelectedTextCb
* @description		Callback for ime_run to Get Text
* @parameter		NA
* @return			NA
*/
static void InputMethodGetSelectedTextCb()
{
	char *cText = NULL;
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] InputMethodGetSelectedTextCb Callback called\\n", __LINE__, API_NAMESPACE);
	g_nRet = ime_get_selected_text(&cText);
	if(cText)
	{
		free(cText);
	}
	PRINT_RESULT_NORETURN(IME_ERROR_NONE, g_nRet, "ime_get_selected_text", InputGetError(g_nRet));
	elm_exit();
}

/**
* @function			InputMethodGetRequestHideCb
* @description		Callback for ime_run to send request to hide IME.
* @parameter		NA
* @return			NA
*/
static void InputMethodGetRequestHideCb()
{
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] InputMethodGetRequestHideCb Callback called\\n", __LINE__, API_NAMESPACE);
	g_nRet = ime_request_hide();
	PRINT_RESULT_NORETURN(IME_ERROR_NONE, g_nRet, "ime_request_hide", InputGetError(g_nRet));
	elm_exit();
}

/**
* @function			InputMethodUpdateInputPanelEventCb
* @description		Callback for ime_run to Updates the state of the input panel event.
* @parameter		NA
* @return			NA
*/
static void InputMethodUpdateInputPanelEventCb()
{
	unsigned int nValue = 0;
	int nEventTypeSize = sizeof(eEventTypeArray)/sizeof(eEventTypeArray[0]);

	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] InputMethodUpdateInputPanelEventCb Callback called\\n", __LINE__, API_NAMESPACE);

	for ( int nEventTypeCounter = 0; nEventTypeCounter < nEventTypeSize; nEventTypeCounter++ )
	{
		g_nRet = ime_update_input_panel_event(eEventTypeArray[nEventTypeCounter], nValue);
		PRINT_RESULT_NORETURN(IME_ERROR_NONE, g_nRet, "ime_update_input_panel_event", InputGetError(g_nRet));
		if(g_nRet != IME_ERROR_NONE)
			break;
	}
	elm_exit();
}

/**
* @function			InputMethodSetCandidateVisibilityStateCb
* @description		Callback for ime_run to set the candidate visibility state
* @parameter		NA
* @return			NA
*/
static void InputMethodSetCandidateVisibilityStateCb()
{
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] InputMethodSetCandidateVisibilityStateCb Callback called\\n", __LINE__, API_NAMESPACE);

	bool bVisible = false;
	g_nRet = ime_set_candidate_visibility_state(bVisible);
	if(g_nRet != IME_ERROR_NONE)
	{
		elm_exit();
		return;
	}

	bVisible = true;
	g_nRet = ime_set_candidate_visibility_state(bVisible);
	PRINT_RESULT_NORETURN(IME_ERROR_NONE, g_nRet, "ime_set_candidate_visibility_state", InputGetError(g_nRet));
	elm_exit();
}

/**
* @function			ProcessKeyEventWithKeycodeCb
* @description		Callback for ime_run to Set key event callback function for keycode.
* @parameter		unsigned int key_code, ime_key_code_e key_sym, ime_key_mask_e key_mask, ime_device_info_h dev_info, void *user_data
* @return			bool
*/
static bool ProcessKeyEventWithKeycodeCb(unsigned int key_code, ime_key_code_e key_sym, ime_key_mask_e key_mask, ime_device_info_h dev_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] ProcessKeyEventWithKeycodeCb Callback called\\n", __LINE__, API_NAMESPACE);
	return true;
}

/**
* @function			InputMethodSetProcessKeyEventWithKeycodeCb
* @description		Callback for ime_run to Set key event callback function for keycode.
* @parameter		NA
* @return			NA
*/
static void InputMethodSetProcessKeyEventWithKeycodeCb()
{
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] InputMethodSetProcessKeyEventWithKeycodeCb Callback called\\n", __LINE__, API_NAMESPACE);
	g_nRet = ime_event_set_process_key_event_with_keycode_cb(ProcessKeyEventWithKeycodeCb, NULL);
	PRINT_RESULT_NORETURN(IME_ERROR_NONE, g_nRet, "ime_request_hide", InputGetError(g_nRet));

	elm_exit();
}

/**
* @function			InputMethodPredictionHintDataSetCb
* @description		Callback for ime_run to set prediction hint data event callback.
* @parameter		char *key, char *value, char *user_data
* @return			NA
*/
static void InputMethodPredictionHintDataSetCb(char *key, char *value, char *user_data)
{
	FPRINTF("[Line : %d][%s] InputMethodPredictionHintDataSetCb Callback called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function			InputMethodEventSetPredictionHintDataSetCb
* @description		Callback for ime_run to set prediction hint data event callback.
* @parameter		NA
* @return			NA
*/
static void InputMethodEventSetPredictionHintDataSetCb()
{
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] InputMethodEventSetPredictionHintDataSetCb Callback called\\n", __LINE__, API_NAMESPACE);
	g_nRet = ime_event_set_prediction_hint_data_set_cb(InputMethodPredictionHintDataSetCb, NULL);
	PRINT_RESULT_NORETURN(IME_ERROR_NONE, g_nRet, "ime_event_set_prediction_hint_data_set_cb", InputGetError(g_nRet));
	elm_exit();
}

#ifndef TV
/**
* @function                     IMEInputHintSetCb
* @description          Callback, called when an associated text input UI control requests the input panel to set input hint.
* @parameter            Ecore_IMF_Input_Hints InputHint, void *pszUserData
* @return                       void
*/
static void IMEInputHintSetCb(Ecore_IMF_Input_Hints InputHint, void *pszUserData)
{
	FPRINTF("[Line : %d][%s] IMEInputHintSetCb Callback called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function                     InputMethodEventSetUnsetInputHintSetCb
* @description          Callback for ime_run to Set and Unset input hint event callback function.
* @parameter            NA
* @return                       NA
*/
static void InputMethodEventSetUnsetInputHintSetCb()
{
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] InputMethodEventSetUnsetInputHintSetCb Callback called\\n", __LINE__, API_NAMESPACE);

	Evas_Object *hWindow = NULL;
	hWindow = CreateNormalWin();
	if(!hWindow)
	{
		FPRINTF("[Line : %d][%s] CreateNormalWin() called from InputMethodEventSetUnsetInputHintSetCb callback is failed to create window inside InputMethodEventSetUnsetInputHintSetCb callback\\n", __LINE__, API_NAMESPACE);
		g_bSupportAPIFailed = true;
		return;
	}

	Evas_Object *hEntry = NULL;
	hEntry = elm_entry_add(hWindow);
	if(!hEntry)
	{
		FPRINTF("[Line : %d][%s] elm_entry_add function failed to add entry to hWindow inside InputMethodEventSetUnsetInputHintSetCb callback\\n", __LINE__, API_NAMESPACE);
		g_bSupportAPIFailed = true;
		evas_object_del(hWindow);
		return;
	}

	g_nRet = ime_event_set_input_hint_set_cb(IMEInputHintSetCb, NULL);
	PRINT_RESULT_NORETURN(IME_ERROR_NONE, g_nRet, "ime_event_set_input_hint_set_cb", InputGetError(g_nRet));

	g_nRetUnset = ime_event_unset_input_hint_set_cb();
	PRINT_RESULT_NORETURN(IME_ERROR_NONE, g_nRetUnset, "ime_event_unset_input_hint_set_cb", InputGetError(g_nRetUnset));

	elm_entry_single_line_set(hEntry, EINA_TRUE);

	evas_object_del(hWindow);
	evas_object_del(hEntry);

	elm_exit();
}

/**
* @function                     InputMethodUpdatePreeditCursorCb
* @description          Callback for ime_run to call preedit cursor function.
* @parameter            NA
* @return                       NA
*/
static void InputMethodUpdatePreeditCursorCb()
{
	g_bCallbackCalled = true;
	g_bSupportAPIFailed = false;
	FPRINTF("[Line : %d][%s] InputMethodUpdatePreeditCursorCb Callback called\\n", __LINE__, API_NAMESPACE);

	int nRet = -1;
	Eina_List *list = NULL;

	ime_preedit_attribute *attr = NULL;
	attr = (ime_preedit_attribute *)calloc(1, sizeof(ime_preedit_attribute));

	if(!attr)
	{
		FPRINTF("[Line : %d][%s] calloc is failed inside InputMethodUpdatePreeditCursorCb Callback\\n", __LINE__, API_NAMESPACE);
		g_bSupportAPIFailed = true;
		return;
	}

	attr->start = 0;
	attr->length = 1;
	attr->type = IME_ATTR_FONTSTYLE;
	attr->value = IME_ATTR_FONTSTYLE_UNDERLINE;
	list = eina_list_append(list, attr);

	attr = calloc(1, sizeof(ime_preedit_attribute));
	attr->start = 1;
	attr->length = 3;
	attr->type = IME_ATTR_FONTSTYLE;
	attr->value = IME_ATTR_FONTSTYLE_REVERSAL;
	list = eina_list_append(list, attr);

	nRet = ime_update_preedit_string("abcd", list);
	if (nRet != IME_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] ime_update_preedit_string API failed\\n", __LINE__, API_NAMESPACE);
		EINA_LIST_FREE(list, attr);
		free(attr);
	}

	g_nRet = ime_update_preedit_cursor(1);
	PRINT_RESULT_NORETURN(IME_ERROR_NONE, g_nRet, "ime_update_preedit_cursor", InputGetError(g_nRet));

	elm_exit();
}
#endif // Except for TV profile

/**
 * @function		ITs_capi_ui_inputmethod_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void ITs_capi_ui_inputmethod_startup(void)
{
	struct stat stBuff;

	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
}

/**
 * @function		ITs_capi_ui_inputmethod_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void ITs_capi_ui_inputmethod_cleanup(void)
{
	FPRINTF("[Line : %d][%s] Inside ITs_capi_ui_inputmethod_cleanup\\n", __LINE__, API_NAMESPACE);
}

//& purpose Sets the floating mode or not
//& type: auto
/**
* @testcase				ITc_ime_set_floating_mode_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Sets the floating mode or not
* @scenario				Sets the floating mode or notI \n
* @apicovered			ime_set_floating_mode
* @passcase				If callback gets called and Sets the floating mode successfully
* @failcase				If fails to called callback and/or Sets the floating mode
* @precondition			NA
* @postcondition		NA
*/
int ITc_ime_set_floating_mode_p(void)
{
	START_TEST;

	g_nRet = -1;
	g_bCallbackCalled = false;
	int nRet = ime_run(&basic_callback, (void *)InputMethodSetFloatingModeCb);
	PRINT_RESULT(IME_ERROR_NONE, nRet, "ime_run", InputGetError(nRet));
	PRINT_RESULT(true, g_bCallbackCalled, "ime_set_floating_mode", "Callback not invoked");
	PRINT_RESULT(IME_ERROR_NONE, g_nRet, "ime_set_floating_mode", InputGetError(g_nRet));

	return 0;
}

//& purpose Allows the floating input panel window to move along with the mouse pointer
//& type: auto
/**
* @testcase				ITc_ime_set_floating_drag_start_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Enable floating input panel window to move along with the mouse pointer
* @scenario				Enable floating input panel window to move along with the mouse pointer \n
* @apicovered			ime_set_floating_drag_start
* @passcase				If callback gets called and api returns IME_ERROR_NONE
* @failcase				If fails to called callback and/or api returns other than IME_ERROR_NONE
* @precondition			NA
* @postcondition		NA
*/
int ITc_ime_set_floating_drag_start_p(void)
{
	START_TEST;

	g_nRet = -1;
	g_bCallbackCalled = false;
	int nRet = ime_run(&basic_callback, (void *)InputMethodSetFloatingDragStartCb);
	PRINT_RESULT(IME_ERROR_NONE, nRet, "ime_run", InputGetError(nRet));
	PRINT_RESULT(true, g_bCallbackCalled, "ime_set_floating_drag_start", "Callback not invoked");
	PRINT_RESULT(IME_ERROR_NONE, g_nRet, "ime_set_floating_drag_start", InputGetError(g_nRet));

	return 0;
}

//& purpose Disallows the floating input panel window to move along with the mouse pointer
//& type: auto
/**
* @testcase				ITc_ime_set_floating_drag_end_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Disable floating input panel window to move along with the mouse pointer
* @scenario				Disable floating input panel window to move along with the mouse pointer \n
* @apicovered			ime_set_floating_drag_end
* @passcase				If callback gets called and api returns IME_ERROR_NONE
* @failcase				If fails to called callback and/or api returns other than IME_ERROR_NONE
* @precondition			NA
* @postcondition		NA
*/
int ITc_ime_set_floating_drag_end_p(void)
{
	START_TEST;

	g_nRet = -1;
	g_bCallbackCalled = false;

	int nRet = ime_run(&basic_callback, (void *)InputMethodSetFloatingDragEndCb);
	PRINT_RESULT(IME_ERROR_NONE, nRet, "ime_run", InputGetError(nRet));
	PRINT_RESULT(true, g_bCallbackCalled, "ime_set_floating_drag_end", "Callback not invoked");
	PRINT_RESULT(IME_ERROR_NONE, g_nRet, "ime_set_floating_drag_end", InputGetError(g_nRet));

	return 0;
}

//& purpose Get the Selected input text
//& type: auto
/**
* @testcase				ITc_ime_get_selected_text_p
* @since_tizen			4.0
* @author				SRID(j.abhishek)
* @reviewer				SRID(maneesha.k)
* @type					auto
* @description			Get the Selected input text
* @scenario				Get the Selected input text \n
* @apicovered			ime_get_selected_text
* @passcase				If callback gets called and api returns IME_ERROR_NONE
* @failcase				If fails to called callback and/or api returns other than IME_ERROR_NONE
* @precondition			NA
* @postcondition		NA
*/
int ITc_ime_get_selected_text_p(void)
{
	START_TEST;

	g_nRet = -1;
	g_bCallbackCalled = false;

	int nRet = ime_run(&basic_callback, (void *)InputMethodGetSelectedTextCb);
	PRINT_RESULT(IME_ERROR_NONE, nRet, "ime_run", InputGetError(nRet));
	PRINT_RESULT(true, g_bCallbackCalled, "ime_get_selected_text", "Callback not invoked");
	PRINT_RESULT(IME_ERROR_NONE, g_nRet, "ime_get_selected_text", InputGetError(g_nRet));

	return 0;
}

//& purpose Sends the request to hide IME.
//& type: auto
/**
* @testcase				ITc_ime_request_hide_p
* @since_tizen			5.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description			Sends the request to hide IME.
* @scenario				Sends the request to hide IME.
* @apicovered			ime_request_hide
* @passcase				If callback gets called and api returns IME_ERROR_NONE
* @failcase				If fails to called callback and/or api returns other than IME_ERROR_NONE
* @precondition			NA
* @postcondition		NA
*/
int ITc_ime_request_hide_p(void)
{
	START_TEST;

	g_nRet = -1;
	g_bCallbackCalled = false;

	int nRet = ime_run(&basic_callback, (void *)InputMethodGetRequestHideCb);
	PRINT_RESULT(IME_ERROR_NONE, nRet, "ime_run", InputGetError(nRet));
	PRINT_RESULT(true, g_bCallbackCalled, "ime_request_hide", "Callback not invoked");
	PRINT_RESULT(IME_ERROR_NONE, g_nRet, "ime_request_hide", InputGetError(g_nRet));

	return 0;
}

//& purpose Updates the state of the input panel event.
//& type: auto
/**
* @testcase				ITc_ime_update_input_panel_event_p
* @since_tizen			5.5
* @author				SRID(kanchan.m)
* @reviewer				SRID(priya.kohli)
* @type					auto
* @description			Updates the state of the input panel event
* @scenario				Update the state of the input panel event.
* @apicovered			ime_update_input_panel_event
* @passcase				If callback gets called and api returns IME_ERROR_NONE
* @failcase				If fails to called callback and/or api returns other than IME_ERROR_NONE
* @precondition			NA
* @postcondition		NA
*/
int ITc_ime_update_input_panel_event_p(void)
{
	START_TEST;

	g_nRet = -1;
	g_bCallbackCalled = false;

	int nRet = ime_run(&basic_callback, (void *)InputMethodUpdateInputPanelEventCb);
	PRINT_RESULT(IME_ERROR_NONE, nRet, "ime_run", InputGetError(nRet));
	PRINT_RESULT(true, g_bCallbackCalled, "ime_update_input_panel_event", "Callback not invoked");
	PRINT_RESULT(IME_ERROR_NONE, g_nRet, "ime_update_input_panel_event", InputGetError(g_nRet));

	return 0;
}

//& purpose Sets the candidate visibility state.
//& type: auto
/**
* @testcase				ITc_ime_set_candidate_visibility_state_p
* @since_tizen			5.5
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description			Sets the candidate visibility state.
* @scenario				Sets the candidate visibility state.
* @apicovered			ime_set_candidate_visibility_state
* @passcase				If callback gets called and api returns IME_ERROR_NONE
* @failcase				If fails to called callback and/or api returns other than IME_ERROR_NONE
* @precondition			NA
* @postcondition		NA
*/
int ITc_ime_set_candidate_visibility_state_p(void)
{
	START_TEST;

	g_nRet = -1;
	g_bCallbackCalled = false;

	int nRet = ime_run(&basic_callback, (void *)InputMethodSetCandidateVisibilityStateCb);
	PRINT_RESULT(IME_ERROR_NONE, nRet, "ime_run", InputGetError(nRet));
	PRINT_RESULT(true, g_bCallbackCalled, "ime_set_candidate_visibility_state", "Callback not invoked");
	PRINT_RESULT(IME_ERROR_NONE, g_nRet, "ime_set_candidate_visibility_state", InputGetError(g_nRet));

}

//& purpose Sets key event callback function for keycode.
//& type: auto
/**
* @testcase				ITc_ime_event_set_process_key_event_with_keycode_cb_p
* @since_tizen			5.5
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description			Sets key event callback function for keycode.
* @scenario				Sets key event callback function for keycode.
* @apicovered			ime_event_set_process_key_event_with_keycode_cb
* @passcase				If callback gets called and api returns IME_ERROR_NONE
* @failcase				If fails to called callback and/or api returns other than IME_ERROR_NONE
* @precondition			NA
* @postcondition		NA
*/

int ITc_ime_event_set_process_key_event_with_keycode_cb_p(void)
{
	START_TEST;

	g_nRet = -1;
	g_bCallbackCalled = false;

	int nRet = ime_run(&basic_callback, (void *)InputMethodSetProcessKeyEventWithKeycodeCb);
	PRINT_RESULT(IME_ERROR_NONE, nRet, "ime_run", InputGetError(nRet));
	PRINT_RESULT(true, g_bCallbackCalled, "ime_event_set_process_key_event_with_keycode_cb", "Callback not invoked");
	PRINT_RESULT(IME_ERROR_NONE, g_nRet, "ime_event_set_process_key_event_with_keycode_cb", InputGetError(g_nRet));
}

//& purpose Sets prediction hint data event callback function.
//& type: auto
/**
* @testcase				ITc_ime_event_set_prediction_hint_data_set_cb_p
* @since_tizen			5.0
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description			Sets prediction hint data event callback function.
* @scenario				Sets prediction hint data event callback function.
* @apicovered			ime_event_set_prediction_hint_data_set_cb
* @passcase				If callback gets called and api returns IME_ERROR_NONE
* @failcase				If fails to called callback and/or api returns other than IME_ERROR_NONE
* @precondition			NA
* @postcondition		The ime_run() function should be called to start to run IME application's main loop.
*/
int ITc_ime_event_set_prediction_hint_data_set_cb_p(void)
{
	START_TEST;

	g_nRet = -1;
	g_bCallbackCalled = false;

	int nRet = ime_run(&basic_callback, (void *)InputMethodEventSetPredictionHintDataSetCb);

	PRINT_RESULT(IME_ERROR_NONE, nRet, "ime_run", InputGetError(nRet));
	PRINT_RESULT(true, g_bCallbackCalled, "ime_event_set_prediction_hint_data_set_cb", "Callback not invoked");
	PRINT_RESULT(IME_ERROR_NONE, g_nRet, "ime_event_set_prediction_hint_data_set_cb", InputGetError(g_nRet));

}

#ifndef TV //This change need to be reverted, once 6.5 rootstrap is available for TV
//& purpose Sets and Unsets input_hint_set event callback function
//& type: auto
/**
* @testcase				ITc_ime_event_set_unset_input_hint_set_cb_p
* @since_tizen			6.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description			Sets and unset input_hint_set event callback function.
* @scenario				The callback function is called to set the input hint to deliver to the input panel.
* @apicovered			ime_event_set_input_hint_set_cb, ime_event_set_input_hint_unset_cb
* @passcase				If callback gets called and api returns IME_ERROR_NONE
* @failcase				If fails to called callback and/or api returns other than IME_ERROR_NONE
* @precondition			NA
* @postcondition		The ime_run() function should be called to start to run IME application's main loop.
*/
int ITc_ime_event_set_unset_input_hint_set_cb_p(void)
{
	START_TEST;

	g_nRet = -1;g_nRetUnset = -1;
	g_bCallbackCalled = false;
	g_bSupportAPIFailed = false;

	int nRet = ime_run(&basic_callback, (void *)InputMethodEventSetUnsetInputHintSetCb);

	PRINT_RESULT(IME_ERROR_NONE, nRet, "ime_run", InputGetError(nRet));
	PRINT_RESULT(true, g_bCallbackCalled, "InputMethodEventSetUnsetInputHintSetCb", "Callback not invoked");
	PRINT_RESULT(false, g_bSupportAPIFailed, "InputMethodEventSetUnsetInputHintSetCb", "Support APIs caled inside callback failed");
	PRINT_RESULT(IME_ERROR_NONE, g_nRet, "ime_event_set_input_hint_set_cb", InputGetError(g_nRet));
	PRINT_RESULT(IME_ERROR_NONE, g_nRetUnset, "ime_event_unset_input_hint_set_cb", InputGetError(g_nRetUnset));

	return 0;
}

//& purpose Updates the cursor position in the preedit string.
//& type: auto
/**
* @testcase				ITc_ime_update_preedit_cursor_p
* @since_tizen			6.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description			Updates the cursor position in the preedit string.
* @scenario				Create preedit list and update the cursor position followed by the list
* @apicovered			ime_update_preedit_cursor
* @passcase				If callback gets called and api returns IME_ERROR_NONE
* @failcase				If fails to called callback and/or api returns other than IME_ERROR_NONE
* @precondition			NA
* @postcondition		The ime_run() function should be called to start to run IME application's main loop.
*				This API is supposed to be followed by the ime_update_preedit_string() function.
*/
int ITc_ime_update_preedit_cursor_p(void)
{
	START_TEST;

	g_nRet = -1;
	g_bCallbackCalled = false;
	g_bSupportAPIFailed = false;

	int nRet = ime_run(&basic_callback, (void *)InputMethodUpdatePreeditCursorCb);

	PRINT_RESULT(IME_ERROR_NONE, nRet, "ime_run", InputGetError(nRet));
	PRINT_RESULT(true, g_bCallbackCalled, "ime_update_preedit_cursor", "Callback not invoked");
	PRINT_RESULT(false, g_bSupportAPIFailed, "ime_update_preedit_cursor", "Support APIs caled inside callback failed");
	PRINT_RESULT(IME_ERROR_NONE, g_nRet, "ime_update_preedit_cursor", InputGetError(g_nRet));

	return 0;
}
#endif // Except TV profile

/** @} */
/** @} */
