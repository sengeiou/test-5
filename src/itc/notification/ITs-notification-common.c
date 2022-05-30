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

#include "ITs-notification-common.h"

/**
* @function             ReporterEventsErrCB
* @description          CallBack function
* @parameter            noti_ex_reporter_h hExReporter, noti_ex_error_e eExError, int nReqID, void *data
* @return               NA
*/
void ReporterEventsErrCB(noti_ex_reporter_h hExReporter, noti_ex_error_e eExError, int nReqID, void *data)
{
        g_CallBackHit = true;
#if DEBUG
        FPRINTF("[Line : %d][%s] ReporterEventsErrCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
#endif
}


/**
* @function 		NotificationGetDataPath
* @description	 	Returns the application data path
* @parameter		pAppDataPath: application data path
* @return 			true if succeed else false
*/
bool NotificationGetDataPath(char* pAppDataPath)
{
	if ( NULL == pAppDataPath )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	memset(pAppDataPath, 0, PATH_LEN);

	char* pPath = NULL;
	pPath = app_get_data_path();
	if ( NULL == pPath )
	{
		FPRINTF("[Line : %d][%s] Unable to get application data path; app_get_data_path returned null value\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	strncpy(pAppDataPath, pPath, PATH_LEN-1);
	FPRINTF("[Line : %d][%s] application data path returned = %s\\n", __LINE__, API_NAMESPACE, pAppDataPath);
	return true;
}

/**
* @function 		NotificationAppendToAppDataPath
* @description	 	Appends the input string to application data path
* @parameter		pInputPath: path to append to data path; pFinalPath: final resultant path
* @return 			true if succeed else false
*/
bool NotificationAppendToAppDataPath(char* pInputPath, char* pFinalPath)
{
	if ( NULL == pInputPath || NULL == pFinalPath )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	char pAppDataPath[PATH_LEN] = {0,};
	if ( false == NotificationGetDataPath(pAppDataPath) )
	{
		return false;
	}

	memset(pFinalPath, 0, PATH_LEN);
	strncpy(pFinalPath, pAppDataPath, PATH_LEN-1);
	strncat(pFinalPath, pInputPath, strlen(pInputPath)+1);

	FPRINTF("[Line : %d][%s] result path returned = %s\\n", __LINE__, API_NAMESPACE, pFinalPath);

	return true;
}





/**
* @function 		Application_AppControlGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* Application_AppControlGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case APP_CONTROL_ERROR_NONE :					szErrorVal = "APP_CONTROL_ERROR_NONE";						break; 
	case APP_CONTROL_ERROR_INVALID_PARAMETER:		szErrorVal = "APP_CONTROL_ERROR_INVALID_PARAMETER";			break; 
	case APP_CONTROL_ERROR_OUT_OF_MEMORY:			szErrorVal = "APP_CONTROL_ERROR_OUT_OF_MEMORY";				break; 
	case APP_CONTROL_ERROR_APP_NOT_FOUND:			szErrorVal = "APP_CONTROL_ERROR_APP_NOT_FOUND";				break;
	case APP_CONTROL_ERROR_KEY_NOT_FOUND:			szErrorVal = "APP_CONTROL_ERROR_KEY_NOT_FOUND";				break;
	case APP_CONTROL_ERROR_KEY_REJECTED:			szErrorVal = "APP_CONTROL_ERROR_KEY_REJECTED";				break;
	case APP_CONTROL_ERROR_INVALID_DATA_TYPE:		szErrorVal = "APP_CONTROL_ERROR_INVALID_DATA_TYPE";			break;
	case APP_CONTROL_ERROR_LAUNCH_REJECTED:			szErrorVal = "APP_CONTROL_ERROR_LAUNCH_REJECTED";			break;
	case APP_CONTROL_ERROR_PERMISSION_DENIED:		szErrorVal = "APP_CONTROL_ERROR_PERMISSION_DENIED";			break;
	default:										szErrorVal = "Unknown Error";								break;
	}
	return szErrorVal;
}

/**
 * @function 		Timeout
 * @description	 	Called if some callback is not invoked for a particular timeout
 * @parameter		gpointer data
 * @return 			gboolean
 */ 
gboolean Timeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
	}
	return false;
}
/**
* @function		NotificationExGetError
* @description		Maps error enums to string values
* @parameter		nRet : error code returned
* @return		error string
*/
char* NotificationExGetError(int nRet)
{
	char *szErrorVal = "Unknown Error";
	switch ( nRet )
	{
	case NOTI_EX_ERROR_NONE:			szErrorVal = "NOTI_EX_ERROR_NONE";		break;
	case NOTI_EX_ERROR_INVALID_PARAMETER:		szErrorVal = "NOTI_EX_ERROR_INVALID_PARAMETER";		break;
	case NOTI_EX_ERROR_OUT_OF_MEMORY:		szErrorVal = "NOTI_EX_ERROR_OUT_OF_MEMORY";		break;
	case NOTI_EX_ERROR_IO_ERROR:		szErrorVal = "NOTI_EX_ERROR_IO_ERROR";		break;
	case NOTI_EX_ERROR_PERMISSION_DENIED:		szErrorVal = "NOTI_EX_ERROR_PERMISSION_DENIED";		break;
	case NOTI_EX_ERROR_FROM_DB:		szErrorVal = "NOTI_EX_ERROR_FROM_DB";		break;
	case NOTI_EX_ERROR_ALREADY_EXIST_ID:		szErrorVal = "NOTI_EX_ERROR_ALREADY_EXIST_ID";		break;
	case NOTI_EX_ERROR_FROM_DBUS:		szErrorVal = "NOTI_EX_ERROR_FROM_DBUS";		break;
	case NOTI_EX_ERROR_NOT_EXIST_ID:			szErrorVal = "NOTI_EX_ERROR_NOT_EXIST_ID";		break;
	case NOTI_EX_ERROR_SERVICE_NOT_READY:		szErrorVal = "NOTI_EX_ERROR_SERVICE_NOT_READY";		break;
	}
	return szErrorVal;
}

/**
* @function		SendNotification
* @description		Helper function, sends notification to invoke callback.
* @parameter  		None
* @return		'0' if pass, Error value in case any API fails.
*/
int SendNotification()
{
	int nRet = NOTI_EX_ERROR_NONE;
        int nReqID;

	noti_ex_item_h hGroupItem = NULL;
	noti_ex_item_h hButtonItem1 = NULL;
	noti_ex_item_h hButtonItem2 = NULL;

	nRet = noti_ex_item_group_create(&hGroupItem, "testgroup");
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_create", NotificationExGetError(nRet));

	nRet = noti_ex_item_button_create(&hButtonItem1, "testbtn1", "test1");
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	nRet = noti_ex_item_group_add_child(hGroupItem, hButtonItem1);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_add_child", NotificationExGetError(nRet));

	nRet = noti_ex_item_button_create(&hButtonItem2, "testbtn2", "test2");
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	nRet = noti_ex_item_group_add_child(hGroupItem, hButtonItem2);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_add_child", NotificationExGetError(nRet));

	nRet = noti_ex_item_set_channel(hGroupItem, "test_channel");
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_set_channel", NotificationExGetError(nRet));

	nRet = noti_ex_reporter_post(g_hEventinfoReporter, hGroupItem, &nReqID);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_reporter_post", NotificationExGetError(nRet));

	return nRet;
}

/**
* @function		CreateChatMsgAttributes
* @description		Helper function, create handles prior creation of chat message handle.
* @parameter  		None
* @return		'0' if pass, Error value in case any API fails.
*/
int CreateChatMsgAttributes()
{
	g_pszNameID = "name_id";
	g_pszNameText = "test_name";
	g_pszTextID = "text_id";
	g_pszTextText = "test_text";
	g_pszImageID = "text_id";
	g_pszImagePath = "test_image_path";
	g_pszTimeID = "time_id";
	g_pszChatID = "chat_id";
	g_eChatMsgType = NOTI_EX_ITEM_CHAT_MESSAGE_TYPE_USER;

	int nRet = NOTI_EX_ERROR_NONE;
	nRet = noti_ex_item_text_create(&g_hItemName, g_pszNameID, g_pszNameText, NULL);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_text_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemName, "noti_ex_item_text_create");

	nRet = noti_ex_item_text_create(&g_hItemText, g_pszTextID, g_pszTextText, NULL);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_text_create", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemName));
	CHECK_HANDLE_CLEANUP(g_hItemText, "noti_ex_item_text_create", noti_ex_item_destroy(g_hItemName));

	nRet = noti_ex_item_image_create(&g_hItemImage, g_pszImageID, g_pszImagePath);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_image_create", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemName); noti_ex_item_destroy(g_hItemText));
	CHECK_HANDLE_CLEANUP(g_hItemImage, "noti_ex_item_image_create", noti_ex_item_destroy(g_hItemName); noti_ex_item_destroy(g_hItemText));

	time(&g_tCurrTime);

	nRet = noti_ex_item_time_create(&g_hItemTime, g_pszTimeID, g_tCurrTime);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_time_create", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemName); noti_ex_item_destroy(g_hItemText); noti_ex_item_destroy(g_hItemImage));
	CHECK_HANDLE_CLEANUP(g_hItemName, "noti_ex_item_time_create", noti_ex_item_destroy(g_hItemName); noti_ex_item_destroy(g_hItemText); noti_ex_item_destroy(g_hItemImage));
	return nRet;
}

/**
* @function		DestroyChatMsgAttributes
* @description		Helper function, Destroys chat message related handles.
* @parameter  		None
* @return		'0' if pass, Error value in case any API fails.
*/
int DestroyChatMsgAttributes()
{
	int nRet = NOTI_EX_ERROR_NONE;
	nRet = noti_ex_item_destroy(g_hItemName);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_item_destroy(g_hItemText);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_item_destroy(g_hItemImage);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_item_destroy(g_hItemTime);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_item_destroy(g_hItemChatMsg);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));
	return nRet;
}

/**
* @function		CreateStyleAttributes
* @description		Helper function, create all required handles for style handle creation.
* @parameter  		None
* @return		'0' if pass, Error value in case any API fails.
*/
int CreateStyleAttributes()
{
	g_cAlpha = 1;
	g_cRed = 2;
	g_cGreen = 3;
	g_cBlue = 4;
	g_nLeft = 1;
	g_nTop = 2;
	g_nRight = 3;
	g_nBottom = 4;
	g_nX = 1;
	g_nY = 2;
	g_nW = 3;
	g_nH = 4;
	int nRet = NOTI_EX_ERROR_NONE;

	nRet = noti_ex_color_create(&g_hColor, g_cAlpha, g_cRed, g_cGreen, g_cBlue);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hColor, "noti_ex_color_create");

	nRet = noti_ex_padding_create(&g_hPadding, g_nLeft, g_nTop, g_nRight, g_nBottom);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_create", NotificationExGetError(nRet), noti_ex_color_destroy(g_hColor));
	CHECK_HANDLE_CLEANUP(g_hPadding, "noti_ex_padding_create", noti_ex_color_destroy(g_hColor));

	nRet = noti_ex_geometry_create(&g_hGeometry, g_nX, g_nY, g_nW, g_nH);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_create", NotificationExGetError(nRet), noti_ex_color_destroy(g_hColor); noti_ex_padding_destroy(g_hPadding));
	CHECK_HANDLE_CLEANUP(g_hGeometry, "noti_ex_geometry_create", noti_ex_color_destroy(g_hColor); noti_ex_padding_destroy(g_hPadding));

	nRet = noti_ex_style_create(&g_hStyle, g_hColor, g_hPadding, g_hGeometry);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_style_create", NotificationExGetError(nRet), noti_ex_color_destroy(g_hColor); noti_ex_padding_destroy(g_hPadding); noti_ex_geometry_destroy(g_hGeometry));
	CHECK_HANDLE_CLEANUP(g_hStyle, "noti_ex_style_create", noti_ex_color_destroy(g_hColor); noti_ex_padding_destroy(g_hPadding); noti_ex_geometry_destroy(g_hGeometry));

	return nRet;
}

/**
* @function		DestroyStyleAttributes
* @description		Helper function, destroys style and its related handle created.
* @parameter  		None
* @return		'0' if pass, Error value in case any API fails.
*/
int DestroyStyleAttributes()
{
	int nRet = NOTI_EX_ERROR_NONE;

	nRet = noti_ex_style_destroy(g_hStyle);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_style_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_color_destroy(g_hColor);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_padding_destroy(g_hPadding);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_geometry_destroy(g_hGeometry);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_destroy", NotificationExGetError(nRet));

	return nRet;
}

/**
* @function		CreateButton
* @description		Helper function, to create button ex-item.
* @parameter  		None
* @return		nRet, API return value.
*/
int CreateButton()
{
	int nRet = NOTI_EX_ERROR_NONE;
	g_hItemButton = NULL;
	g_pszButtonID = "buttonID";
	g_pszButtonTitle = "buttonTitle";

	nRet = noti_ex_item_button_create(&g_hItemButton, g_pszButtonID, g_pszButtonTitle);
	return nRet;
}

/**
* @function		CreateMultiLangHandle
* @description		Helper function, to create multilang handle.
* @parameter  		None
* @return		nRet, API return value.
*/
int CreateMultiLangHandle()
{
	int nRet = 0;
	g_hMultiLang = NULL;
	g_pszMsgID = "TEST_ID";
	g_pszText = "test string(%s) integer(%d) float(%f)";
	g_pszArg1 = "test";
	g_nArg2 = 777;
	g_fArg3 = 0.77;

	nRet = noti_ex_multi_lang_create(&g_hMultiLang, g_pszMsgID, g_pszText, g_pszArg1, g_nArg2, g_fArg3);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_multi_lang_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hMultiLang, "noti_ex_multi_lang_create");

	return nRet;
}
/**
* @function		CreateNotificationList
* @description		Helper function, create notification and update list.
* @parameter  		None
* @return		'0' if pass, Error value in case any API fails.
*/
int CreateNotificationList(noti_ex_item_h **pszhItemList)
{
	int nRet = NOTI_EX_ERROR_NONE;

	if (g_hEventinfoReporter == NULL) {
		noti_ex_reporter_events_s hReporterEvent = {0};
		hReporterEvent.error = ReporterEventsErrCB;
		nRet = noti_ex_reporter_create(&g_hEventinfoReporter, hReporterEvent, NULL);
		PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_reporter_create", NotificationExGetError(nRet));
	}
	noti_ex_item_h *hItemlist = (noti_ex_item_h*)calloc(2, sizeof(noti_ex_item_h));

	noti_ex_item_h hGroupItem = NULL;
	noti_ex_item_h hButtonItem1 = NULL;
	noti_ex_item_h hButtonItem2 = NULL;

	nRet = noti_ex_item_group_create(&hGroupItem, "testgroup");
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_create", NotificationExGetError(nRet), FREE_MEMORY(hItemlist));

	nRet = noti_ex_item_button_create(&hButtonItem1, "testbtn1", "test1");
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet), FREE_MEMORY(hItemlist));
	nRet = noti_ex_item_group_add_child(hGroupItem, hButtonItem1);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_add_child", NotificationExGetError(nRet), FREE_MEMORY(hItemlist));


	nRet = noti_ex_item_button_create(&hButtonItem2, "testbtn2", "test2");
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet), FREE_MEMORY(hItemlist));
	nRet = noti_ex_item_group_add_child(hGroupItem, hButtonItem2);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_add_child", NotificationExGetError(nRet), FREE_MEMORY(hItemlist));
	hItemlist[0] = hGroupItem;

	nRet = noti_ex_item_group_create(&hGroupItem, "testgroup2");
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_create", NotificationExGetError(nRet), FREE_MEMORY(hItemlist));

	nRet = noti_ex_item_button_create(&hButtonItem1, "testbtn3", "test3");
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet), FREE_MEMORY(hItemlist));
	nRet = noti_ex_item_group_add_child(hGroupItem, hButtonItem1);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_add_child", NotificationExGetError(nRet), FREE_MEMORY(hItemlist));


	nRet = noti_ex_item_button_create(&hButtonItem2, "testbtn4", "test4");
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet), FREE_MEMORY(hItemlist));
	nRet = noti_ex_item_group_add_child(hGroupItem, hButtonItem2);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_add_child", NotificationExGetError(nRet), FREE_MEMORY(hItemlist));
	hItemlist[1] = hGroupItem;

	*pszhItemList = hItemlist;
	return nRet;
}

