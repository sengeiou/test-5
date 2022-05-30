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
#include "CTs-platform-permission-common.h"

/** @addtogroup ctc-platform-permission
* @ingroup		ctc
* @{
*/

#include <inputmethod.h>
#include <glib.h>

//& set: PlatformPermission

Evas_Object *win = NULL;

void ime_app_main(int argc, char **argv)
{
}


/**
* @function 		CTs_platform_permission_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_ime_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}
	
    win = elm_win_add(NULL, "test", ELM_WIN_BASIC);

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function 		CTs_platform_permission_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_ime_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
 * @function 		InputmethodGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
/*char* InputmethodGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case IME_ERROR_NONE: 							szErrorVal = "IME_ERROR_NONE";						break;
		case IME_ERROR_INVALID_PARAMETER: 				szErrorVal = "IME_ERROR_INVALID_PARAMETER";			break;
		case IME_ERROR_PERMISSION_DENIED: 				szErrorVal = "IME_ERROR_PERMISSION_DENIED";			break;
		case IME_ERROR_NO_CALLBACK_FUNCTION: 			szErrorVal = "IME_ERROR_NO_CALLBACK_FUNCTION";		break;
		case IME_ERROR_NOT_RUNNING: 					szErrorVal = "IME_ERROR_NOT_RUNNING";				break;
		case IME_ERROR_OPERATION_FAILED: 				szErrorVal = "IME_ERROR_OPERATION_FAILED";			break;
	}
	
	return szErrorVal;
}*/

/**
* @function 			ime_exit
* @description 			Called to exit callback
* @parameter			gpointer user_data
* @return				bool value
*/
gboolean Ime_Exit(gpointer user_data)
{
    elm_exit();
    return FALSE;
}

void Imdata_Requested_cb(void *user_data, void **data, unsigned int *data_length)
{
	FPRINTF("[Line : %d][%s] Terminate_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Create_cb
* @description 			Called to create callback
* @parameter			void *user_data
* @return				NA
*/
void Create_cb(void *user_data)
{
    g_idle_add((GSourceFunc)user_data, NULL);
}

/**
* @function 			Terminate_cb
* @description 			Called to terminate callback
* @parameter			void *user_data
* @return				NA
*/
void Terminate_cb(void *user_data)
{
	FPRINTF("[Line : %d][%s] Terminate_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Show_cb
* @description 			Called to show callback
* @parameter			int ic, ime_context_h context, void *user_data
* @return				NA
*/
void Show_cb(int ic, ime_context_h context, void *user_data)
{
	FPRINTF("[Line : %d][%s] Show_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Hide_cb
* @description 			Called to hide callback
* @parameter			int ic, void *user_data
* @return				NA
*/
void Hide_cb(int ic, void *user_data)
{
	FPRINTF("[Line : %d][%s] Hide_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Focus_In_cb
* @description 			Called to Set Focus In
* @parameter			int context_id, void *user_data
* @return				NA
*/
void Focus_In_cb(int context_id, void *user_data)
{
	FPRINTF("[Line : %d][%s] Focus_In_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Focus_Out_cb
* @description 			Called to Set Focus out
* @parameter			int context_id, void *user_data
* @return				NA
*/
void Focus_Out_cb(int context_id, void *user_data)
{
	FPRINTF("[Line : %d][%s] Focus_Out_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Surrounding_Text_Updated_cb
* @description 			Called to update surrounding text
* @parameter			int context_id, const char *text, int cursor_pos, void *user_data
* @return				NA
*/
void Surrounding_Text_Updated_cb(int context_id, const char *text, int cursor_pos, void *user_data)
{
	FPRINTF("[Line : %d][%s] Surrounding_Text_Updated_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Input_Context_Reset_cb
* @description 			Called to reset input context
* @parameter			void *user_data
* @return				NA
*/
void Input_Context_Reset_cb(void *user_data)
{
	FPRINTF("[Line : %d][%s] Input_Context_Reset_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Cursor_Position_Updated_cb
* @description 			Called to update cursor position
* @parameter			int cursor_pos, void *user_data
* @return				NA
*/
void Cursor_Position_Updated_cb(int cursor_pos, void *user_data)
{
	FPRINTF("[Line : %d][%s] Cursor_Position_Updated_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Language_Requested_cb
* @description 			Called to request language
* @parameter			void *user_data, char **lang_code
* @return				NA
*/
void Language_Requested_cb(void *user_data, char **lang_code)
{
	FPRINTF("[Line : %d][%s] Language_Requested_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Language_Set_cb
* @description 			Called to set language
* @parameter			Ecore_IMF_Input_Panel_Lang language, void *user_data
* @return				NA
*/
void Language_Set_cb(Ecore_IMF_Input_Panel_Lang language, void *user_data)
{
	FPRINTF("[Line : %d][%s] Language_Set_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Imdata_Set_cb
* @description 			Called to set input manager data
* @parameter			void *data, unsigned int data_length, void *user_data
* @return				NA
*/
void Imdata_Set_cb(void *data, unsigned int data_length, void *user_data)
{
	FPRINTF("[Line : %d][%s] Imdata_Set_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Layout_Set_cb
* @description 			Called to set layout
* @parameter			Ecore_IMF_Input_Panel_Layout layout, void *user_data
* @return				NA
*/
void Layout_Set_cb(Ecore_IMF_Input_Panel_Layout layout, void *user_data)
{
	FPRINTF("[Line : %d][%s] Layout_Set_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Return_Key_Type_Set_cb
* @description 			Called to set return type of key
* @parameter			Ecore_IMF_Input_Panel_Return_Key_Type type, void *user_data
* @return				NA
*/
void Return_Key_Type_Set_cb(Ecore_IMF_Input_Panel_Return_Key_Type type, void *user_data)
{
	FPRINTF("[Line : %d][%s] Return_Key_Type_Set_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Return_Key_State_Set_cb
* @description 			Called to set return state of key
* @parameter			bool disabled, void *user_data
* @return				NA
*/
void Return_Key_State_Set_cb(bool disabled, void *user_data)
{
	FPRINTF("[Line : %d][%s] Return_Key_State_Set_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Geometry_Requested_cb
* @description 			Called to request geometry
* @parameter			void *user_data, int *x, int *y, int *w, int *h
* @return				NA
*/
void Geometry_Requested_cb(void *user_data, int *x, int *y, int *w, int *h)
{
	FPRINTF("[Line : %d][%s] Geometry_Requested_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Process_Key_Event_cb
* @description 			Called to process key event
* @parameter			ime_key_code_e keycode, ime_key_mask_e keymask, ime_device_info_h dev_info, void *user_data
* @return				NA
*/
bool Process_Key_Event_cb(ime_key_code_e keycode, ime_key_mask_e keymask, ime_device_info_h dev_info, void *user_data)
{
    return true;
}

/**
* @function 			Display_Language_Changed_cb
* @description 			Called to dispaly language change
* @parameter			const char *language, void *user_data
* @return				NA
*/
void Display_Language_Changed_cb(const char *language, void *user_data)
{
	FPRINTF("[Line : %d][%s] Display_Language_Changed_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Rotation_Degree_Changed_cb
* @description 			Called to change rotation degree
* @parameter			int degree, void *user_data
* @return				NA
*/
void Rotation_Degree_Changed_cb(int degree, void *user_data)
{
	FPRINTF("[Line : %d][%s] Rotation_Degree_Changed_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Accessibility_State_Changed_cb
* @description 			Called to change accessibility state
* @parameter			bool state, void *user_data
* @return				NA
*/
void Accessibility_State_Changed_cb(bool state, void *user_data)
{
	FPRINTF("[Line : %d][%s] Accessibility_State_Changed_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Option_Window_Created_cb
* @description 			Called to create option window
* @parameter			Evas_Object *window, ime_option_window_type_e type, void *user_dat
* @return				NA
*/
 void Option_Window_Created_cb(Evas_Object *window, ime_option_window_type_e type, void *user_data)
{
	FPRINTF("[Line : %d][%s] Option_Window_Created_cb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 			Option_Window_Destroyed_cb
* @description 			Called to destroy option window
* @parameter			Evas_Object *window, void *user_data
* @return				NA
*/
void Option_Window_Destroyed_cb(Evas_Object *window, void *user_data)
{
	FPRINTF("[Line : %d][%s] Option_Window_Destroyed_cb\\n", __LINE__, API_NAMESPACE);
}

/** @addtogroup	ctc-platform-permission-testcases
* @brief 		Integration testcases for module platform-permission
* @ingroup		ctc-platform-permission
* @{
*/

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Run
* @since_tizen		2.4
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			Runs the main loop of IME application
* @apicovered		ime_run 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Run(void)
{
	START_TEST;

	ime_callback_s basic_cb = {
    Create_cb,
    Terminate_cb,
    Show_cb,
    Hide_cb,
	};
	
	int nRet = ime_run(&basic_cb, (void *)Ime_Exit);
	PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_run", InputmethodGetError(nRet));
	
	return 0;	
}

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Event_Set_Focus_In_cb
* @since_tizen		2.4
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			sets focus_in event callback function
* @apicovered		ime_event_set_focus_in_cb 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Event_Set_Focus_In_cb(void)
{
	START_TEST;
	
    int nRet = ime_event_set_focus_in_cb(Focus_In_cb, NULL);
	PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_event_set_focus_in_cb", InputmethodGetError(nRet));
	
    return 0;
}

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Event_Set_Focus_Out_cb
* @since_tizen		2.4
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			sets focus_out event callback function.
* @apicovered		ime_event_set_focus_out_cb 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Event_Set_Focus_Out_cb(void)
{
	START_TEST;
	
    int nRet = ime_event_set_focus_out_cb(Focus_Out_cb, NULL);
	PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_event_set_focus_out_cb", InputmethodGetError(nRet));
	
    return 0;
}

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Event_Set_Surrounding_Text_Updated_cb
* @since_tizen		2.4
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			sets surrounding_text_updated event callback function.
* @apicovered		ime_event_set_surrounding_text_updated_cb 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Event_Set_Surrounding_Text_Updated_cb(void)
{
	START_TEST;
	
    int nRet = ime_event_set_surrounding_text_updated_cb(Surrounding_Text_Updated_cb, NULL);
	PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_event_set_surrounding_text_updated_cb", InputmethodGetError(nRet));
	
    return 0;
}

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Event_Set_Input_Context_Reset_cb
* @since_tizen		2.4
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			sets input_context_reset event callback function.
* @apicovered		ime_event_set_input_context_reset_cb 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Event_Set_Input_Context_Reset_cb(void)
{
	START_TEST;
	
    int nRet = ime_event_set_input_context_reset_cb(Input_Context_Reset_cb, NULL);
    PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_event_set_input_context_reset_cb", InputmethodGetError(nRet));
	
    return 0;
}

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Event_Set_Cursor_Position_Updated_cb
* @since_tizen		2.4
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			sets cursor_position_updated event callback function.
* @apicovered		ime_event_set_cursor_position_updated_cb 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Event_Set_Cursor_Position_Updated_cb(void)
{
	START_TEST;
	
    int nRet = ime_event_set_cursor_position_updated_cb(Cursor_Position_Updated_cb, NULL);
    PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_event_set_cursor_position_updated_cb", InputmethodGetError(nRet));
	
    return 0;
}

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Event_Set_Language_Requested_cb
* @since_tizen		2.4
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			sets language_requested event callback function.
* @apicovered		ime_event_set_language_requested_cb 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Event_Set_Language_Requested_cb(void)
{
	START_TEST;
    
	int nRet = ime_event_set_language_requested_cb(Language_Requested_cb, NULL);
    PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_event_set_language_requested_cb", InputmethodGetError(nRet));
	
    return 0;
}

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Event_Set_Language_Set_cb
* @since_tizen		2.4
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			sets language_set event callback function.
* @apicovered		ime_event_set_language_set_cb 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Event_Set_Language_Set_cb(void)
{
	START_TEST;
	
    int nRet = ime_event_set_language_set_cb(Language_Set_cb, NULL);
    PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_event_set_language_set_cb", InputmethodGetError(nRet));
	
    return 0;
}

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Event_Set_Imdata_Set_cb
* @since_tizen		2.4
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			sets imdata_set event callback function.
* @apicovered		ime_event_set_imdata_set_cb 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Event_Set_Imdata_Set_cb(void)
{
	START_TEST;
	
    int nRet = ime_event_set_imdata_set_cb(Imdata_Set_cb, NULL);
	PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_event_set_imdata_set_cb", InputmethodGetError(nRet));
	
    return 0;
}

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Event_Set_Layout_Set_cb
* @since_tizen		2.4
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			sets layout_set event callback function.
* @apicovered		ime_event_set_layout_set_cb 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Event_Set_Layout_Set_cb(void)
{
	START_TEST;
	
    int nRet = ime_event_set_layout_set_cb(Layout_Set_cb, NULL);
	PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_event_set_layout_set_cb", InputmethodGetError(nRet));
	
    return 0;
}

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Event_Set_Return_Key_Type_Set_cb
* @since_tizen		2.4
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			sets return_key_type_set event callback function.
* @apicovered		ime_event_set_return_key_type_set_cb 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Event_Set_Return_Key_Type_Set_cb(void)
{
	START_TEST;
	
    int nRet = ime_event_set_return_key_type_set_cb(Return_Key_Type_Set_cb, NULL);
    PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_event_set_return_key_type_set_cb", InputmethodGetError(nRet));
	
    return 0;
}

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Event_Set_Return_Key_State_Set_cb
* @since_tizen		2.4
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			sets return_key_state_set event callback function.
* @apicovered		ime_event_set_return_key_state_set_cb 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Event_Set_Return_Key_State_Set_cb(void)
{
	START_TEST;
	
    int nRet = ime_event_set_return_key_state_set_cb(Return_Key_State_Set_cb, NULL);
	PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_event_set_return_key_state_set_cb", InputmethodGetError(nRet));
	
    return 0;
}

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Event_Set_Geometry_Requested_cb
* @since_tizen		2.4
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			sets geometry_requested event callback function.
* @apicovered		ime_event_set_geometry_requested_cb 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Event_Set_Geometry_Requested_cb(void)
{
	START_TEST;
	
    int nRet = ime_event_set_geometry_requested_cb(Geometry_Requested_cb, NULL);
    PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_event_set_geometry_requested_cb", InputmethodGetError(nRet));
	
    return 0;
}

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Event_Set_Process_Key_Event_cb
* @since_tizen		2.4
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			sets process_key_event event callback function.
* @apicovered		ime_event_set_process_key_event_cb 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Event_Set_Process_Key_Event_cb(void)
{
	START_TEST;
	
    int nRet = ime_event_set_process_key_event_cb(Process_Key_Event_cb, NULL);
    PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_event_set_process_key_event_cb", InputmethodGetError(nRet));
	
    return 0;
}

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Event_Set_Display_Language_Changed_cb
* @since_tizen		2.4
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			sets display_language_changed event callback function.
* @apicovered		ime_event_set_display_language_changed_cb 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Event_Set_Display_Language_Changed_cb(void)
{
	START_TEST;
	
    int nRet = ime_event_set_display_language_changed_cb(Display_Language_Changed_cb, NULL);
    PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_event_set_display_language_changed_cb", InputmethodGetError(nRet));
	
    return 0;
}

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Event_Rotation_Degree_Changed_cb
* @since_tizen		2.4
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			sets rotation_degree_changed event callback function.
* @apicovered		ime_event_set_rotation_degree_changed_cb 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Event_Rotation_Degree_Changed_cb(void)
{
	START_TEST;
	
    int nRet = ime_event_set_rotation_degree_changed_cb(Rotation_Degree_Changed_cb, NULL);
    PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_event_set_rotation_degree_changed_cb", InputmethodGetError(nRet));
	
    return 0;
}

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Event_Set_Accessibility_State_Changed_cb
* @since_tizen		2.4
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			sets accessibility_state_changed event callback function.
* @apicovered		ime_event_set_accessibility_state_changed_cb 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Event_Set_Accessibility_State_Changed_cb(void)
{
	START_TEST;
	
    int nRet = ime_event_set_accessibility_state_changed_cb(Accessibility_State_Changed_cb, NULL);
    PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_event_set_accessibility_state_changed_cb", InputmethodGetError(nRet));
	
    return 0;
}

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Event_Set_Option_Window_Created_cb
* @since_tizen		2.4
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			sets option_window_created event callback function.
* @apicovered		ime_event_set_option_window_created_cb 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Event_Set_Option_Window_Created_cb(void)
{
	START_TEST;
	
    int nRet = ime_event_set_option_window_created_cb(Option_Window_Created_cb, NULL);
	PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_event_set_option_window_created_cb", InputmethodGetError(nRet));
	
    return 0;
}

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Event_Set_Option_Window_Destroyed_cb
* @since_tizen		2.4
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			sets option_window_destroyed event callback function.
* @apicovered		ime_event_set_option_window_destroyed_cb 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Event_Set_Option_Window_Destroyed_cb(void)
{
	START_TEST;
	
    int nRet = ime_event_set_option_window_destroyed_cb(Option_Window_Destroyed_cb, NULL);
	PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_event_set_option_window_destroyed_cb", InputmethodGetError(nRet));
	
    return 0;
}

//& purpose:Checking tizen.org/privilege/ime privilege
//& type: auto
/**
* @testcase			CTc_IME_PrivilegeIME_IME_Event_Set_Imdata_Requested_cb
* @since_tizen		2.4
* @author			SRID(gaurav.m2)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			function sets imdata_requested event callback function.
* @apicovered		ime_event_set_imdata_requested_cb 
* @passcase			If target privileged API returns IME_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_PrivilegeIME_IME_Event_Set_Imdata_Requested_cb(void)
{
	START_TEST;
	
	int nRet = ime_event_set_imdata_requested_cb(Imdata_Requested_cb, NULL);
    PRINT_RESULT(IME_ERROR_PERMISSION_DENIED, nRet, "ime_event_set_imdata_requested_cb", InputmethodGetError(nRet));
	    
    return 0;
}
/** @} */ //end of ctc-platform-permission
/** @} */ //end of ctc-platform-permission-testcases
