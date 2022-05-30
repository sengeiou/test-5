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

/** @addtogroup itc-voice-control-elm
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		IterateEcoreLoop
* @description	 	Called to wait
* @parameter		NA
* @return 			NA
*/
void IterateEcoreLoop(void)
{
	while(g_CallBackHit != true)
	{
		ecore_main_loop_iterate();
	}
}

/**
* @function 		VoiceControlElmGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* VoiceControlElmGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case VC_ELM_ERROR_NONE:						szErrorVal = "VC_ELM_ERROR_NONE";					break;
		case VC_ELM_ERROR_OUT_OF_MEMORY:			szErrorVal = "VC_ELM_ERROR_OUT_OF_MEMORY";			break;
		case VC_ELM_ERROR_IO_ERROR:					szErrorVal = "VC_ELM_ERROR_IO_ERROR";				break;
		case VC_ELM_ERROR_INVALID_PARAMETER:		szErrorVal = "VC_ELM_ERROR_INVALID_PARAMETER";		break;
		case VC_ELM_ERROR_PERMISSION_DENIED:		szErrorVal = "VC_ELM_ERROR_PERMISSION_DENIED";		break;
		case VC_ELM_ERROR_NOT_SUPPORTED:			szErrorVal = "VC_ELM_ERROR_NOT_SUPPORTED";			break;
		case VC_ELM_ERROR_INVALID_STATE:			szErrorVal = "VC_ELM_ERROR_INVALID_STATE";			break;
		case VC_ELM_ERROR_INVALID_LANGUAGE:			szErrorVal = "VC_ELM_ERROR_INVALID_LANGUAGE";		break;
		case VC_ELM_ERROR_OPERATION_FAILED:			szErrorVal = "VC_ELM_ERROR_OPERATION_FAILED";		break;
		case VC_ELM_ERROR_OPERATION_REJECTED:		szErrorVal = "VC_ELM_ERROR_OPERATION_REJECTED";		break;
		default:									szErrorVal = "VC_ELM_ERROR_UNKNOWN";				break;
	}
	return szErrorVal;
}

/**
* @function 		WinDel
* @description 		Callback function registered by evas_object_smart_callback_add API
* @parameter[IN]	void*, Evas_Object*, void*
* @return 			NA.
*/
void WinDel(void *data, Evas_Object *obj, void *event)
{
	elm_exit();
}

/**
* @function 		CreateEvasWindow
* @description 		Creates an Evas window object
* @parameter[IN]	NA
* @return 			Evas_Object if successful, otherwise NULL.
*/
bool CreateEvasWindow(void)
{
	elm_config_accel_preference_set("3d");

	g_pEvasWindow = elm_win_util_standard_add(PACKAGE, PACKAGE);
	CHECK_HANDLE(g_pEvasWindow, "elm_win_util_standard_add");
	elm_win_borderless_set(g_pEvasWindow, EINA_TRUE);
	evas_object_smart_callback_add(g_pEvasWindow, "delete,request",WinDel, NULL);
	elm_win_autodel_set(g_pEvasWindow, EINA_TRUE);
	elm_win_activate(g_pEvasWindow);
	evas_object_show(g_pEvasWindow);

	g_pEvasButton = elm_button_add(g_pEvasWindow);
	CHECK_HANDLE_CLEANUP(g_pEvasButton, "elm_layout_add", DeleteEvasWindow());
	evas_object_show(g_pEvasButton);

	Elm_Genlist_Item_Class *pListClass = NULL;
	pListClass = elm_genlist_item_class_new();
	pListClass->item_style = "default";
	pListClass->func.text_get = NULL;
	pListClass->func.content_get = NULL;
	pListClass->func.state_get = NULL;
	pListClass->func.del = NULL;

	g_pGenList = elm_list_add(g_pEvasWindow);
	CHECK_HANDLE_CLEANUP(g_pGenList, "elm_list_add", DeleteEvasWindow());
	evas_object_show(g_pGenList);

	g_pEvasItem = elm_list_item_append(g_pGenList, TESTSTRING, NULL, NULL, NULL, NULL);
	CHECK_HANDLE_CLEANUP(g_pEvasItem, "elm_list_item_append", DeleteEvasWindow());

	return 0;
}

/**
* @function 		DeleteEvasWindow
* @description 		Delete Evas window object
* @parameter[IN]	NA
* @return 			NA
*/
void DeleteEvasWindow(void)
{
	if ( g_pEvasItem )
	{
		elm_object_item_del(g_pEvasItem);
		g_pEvasItem = NULL;
	}
	if ( g_pGenList )
	{
		evas_object_del(g_pGenList);
		g_pGenList = NULL;
	}
	if ( g_pEvasButton )
	{
		evas_object_del(g_pEvasButton);
		g_pEvasButton = NULL;
	}
	if ( g_pEvasWindow )
	{
		evas_object_del(g_pEvasWindow);
		g_pEvasWindow = NULL;
	}
}

/**
* @function 		GetWidgetName
* @description	 	Get Widget Name
* @parameter		NA
* @return 			NA
*/
bool GetWidgetName(void)
{
	int nRet = -1;

	g_CallBackHit = false;
	nRet = vc_elm_foreach_supported_widgets(WidgetSupportedCallback, NULL);
	PRINT_RESULT(VC_ELM_ERROR_NONE, nRet, "vc_elm_foreach_supported_widgets", VoiceControlElmGetError(nRet));
	IterateEcoreLoop();
	PRINT_RESULT(true, g_CallBackHit, "vc_elm_foreach_supported_widgets", "CallBack Not Invoked");

	return 0;
}

/**
* @function 		GetActionName
* @description	 	Get Action Name
* @parameter		NA
* @return 			NA
*/
bool GetActionName(void)
{
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
* @function 		GetCommandName
* @description	 	Get Command Name
* @parameter		NA
* @return 			NA
*/
bool GetCommandName(void)
{
	int nRet = -1;
	char *pszCommand = NULL;

	nRet = GetActionName();
	PRINT_RESULT(0, nRet, "GetActionName", "Return Value Not Correct");

	nRet = vc_elm_get_action_command(g_szAction, &pszCommand);
	PRINT_RESULT(VC_ELM_ERROR_NONE, nRet, "vc_elm_get_action_command", VoiceControlElmGetError(nRet));
	CHECK_HANDLE(pszCommand, "vc_elm_get_action_command");
	strncpy(g_szCommand, pszCommand, PATH_LEN);
	FREE_MEMORY(pszCommand);

	return 0;
}

/**
* @function 		CreateVcElmObject
* @description	 	create a vc elm object
* @parameter		NA
* @return 			NA
*/
bool CreateVcElmObject(void)
{
	int nRet = -1;
	nRet = CreateEvasWindow();
	PRINT_RESULT(0, nRet, "CreateEvasWindow", "Return Value Not Correct");

	nRet = vc_elm_create_object(g_pEvasButton, &g_hVcElm);
	PRINT_RESULT_CLEANUP(VC_ELM_ERROR_NONE, nRet, "vc_elm_create_object", VoiceControlElmGetError(nRet), DeleteVcElmObject());

	return 0;
}

/**
* @function 		DeleteVcElmObject
* @description	 	delete a vc elm object
* @parameter		NA
* @return 			NA
*/
bool DeleteVcElmObject(void)
{
	int nRet = -1;
	if ( g_hVcElm )
	{
		nRet = vc_elm_destroy(g_hVcElm);
		PRINT_RESULT_CLEANUP(VC_ELM_ERROR_NONE, nRet, "vc_elm_destroy", VoiceControlElmGetError(nRet), DeleteEvasWindow());
		g_hVcElm = NULL;
	}

	DeleteEvasWindow();

	return 0;
}

/**
* @function 		CreateVcElmObjectWithCommand
* @description	 	create a vc elm object with command
* @parameter		NA
* @return 			NA
*/
bool CreateVcElmObjectWithCommand(void)
{
	int nRet = -1;

	nRet = GetCommandName();
	PRINT_RESULT(0, nRet, "GetCommandName", "Return Value Not Correct");

	nRet = CreateVcElmObject();
	PRINT_RESULT(0, nRet, "CreateVcElmObject", "Return Value Not Correct");

	nRet = vc_elm_set_command(g_hVcElm, g_szCommand);
	PRINT_RESULT_CLEANUP(VC_ELM_ERROR_NONE, nRet, "vc_elm_set_command", VoiceControlElmGetError(nRet), DeleteVcElmObjectWithCommand());

	return 0;
}

/**
* @function 		DeleteVcElmObjectWithCommand
* @description	 	delete a vc elm object with command
* @parameter		NA
* @return 			NA
*/
bool DeleteVcElmObjectWithCommand(void)
{
	int nRet = -1;

	nRet = vc_elm_unset_command(g_hVcElm);
	PRINT_RESULT_CLEANUP(VC_ELM_ERROR_NONE, nRet, "vc_elm_unset_command", VoiceControlElmGetError(nRet), DeleteVcElmObject());

	DeleteVcElmObject();

	return 0;
}

/**
* @function 		CreateVcElmObjectWithCommandHint
* @description	 	create a vc elm object with command hint
* @parameter		NA
* @return 			NA
*/
bool CreateVcElmObjectWithCommandHint(void)
{
	int nRet = -1;

	nRet = CreateVcElmObjectWithCommand();
	PRINT_RESULT(0, nRet, "CreateVcElmObjectWithCommand", "Return Value Not Correct");

	nRet = vc_elm_set_command_hint(g_hVcElm, COMMANDHINT);
	PRINT_RESULT_CLEANUP(VC_ELM_ERROR_NONE, nRet, "vc_elm_set_command_hint", VoiceControlElmGetError(nRet), DeleteVcElmObjectWithCommandHint());

	return 0;
}

/**
* @function 		DeleteVcElmObjectWithCommandHint
* @description	 	delete a vc elm object with command
* @parameter		NA
* @return 			NA
*/
bool DeleteVcElmObjectWithCommandHint(void)
{
	int nRet = -1;

	nRet = vc_elm_unset_command_hint(g_hVcElm);
	PRINT_RESULT_CLEANUP(VC_ELM_ERROR_NONE, nRet, "vc_elm_unset_command_hint", VoiceControlElmGetError(nRet), DeleteVcElmObjectWithCommand());

	DeleteVcElmObjectWithCommand();

	return 0;
}

/** @} */