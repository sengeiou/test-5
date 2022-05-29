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
#ifndef _ITS_NOTIFICATION_COMMON_H_
#define _ITS_NOTIFICATION_COMMON_H_

#include "tct_common.h"
#include <app.h>

#include <glib.h>
#include <glib-object.h>
#include <notification_ex.h>
#include <app_manager.h>
#include <app_control.h>


#define API_NAMESPACE           			"NOTIFICATION_ITC"
#define MICROSECONDS_PER_SECOND 			1000000
#define APP_IMAGE_FULL_PATH         		"file:///tmp/info.png"
#define BASIC_TEXT                  		"I'm Title"
#define TEXT_KEY_FOR_LOCALIZATION   		"IDS_APP_BODY_IM_TITLE"
#define DEFAULT_FILE_PATH					"path"
#define NOTIFICATION_LED_COLOR				0
#define NOTIFICATION_SET_PROGRESS_VAL		0.5
#define NOTIFICATION_SET_SIZE_VAL			1000.0
#define WAIT_CALLBACK						5
#define NOTIFICATION_TAG					"notification_tag"
#define PATH_LEN							1024
#define GROUP_NOTI_ID			"test_group"
#define TIMEOUT_CB					20000

#define FREE_NOTIFICATION(notification)  		if(notification != NULL) {notification_free(notification);}
#define DELETE_NOTIFICATION(notification)		if(notification != NULL) {notification_delete(notification);}
#define START_TEST								FPRINTF("[Line No : %d][%s] Starting test : %s\\n",__LINE__, API_NAMESPACE, __FUNCTION__);

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

#define RUN_POLLING_LOOP {\
	g_pNotificationMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, Timeout, g_pNotificationMainLoop);\
	g_main_loop_run(g_pNotificationMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pNotificationMainLoop = NULL;\
}

#define PRINT_RESULT_CALLBACK_NORETURN(eCompare, eRetVal, API, Error) {\
	if ( eRetVal == eCompare )\
{\
	if ( DEBUG )\
{\
	FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
}\
}\
	else \
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, Error, eRetVal);\
	g_bAPIFailed = true;\
}\
}

typedef enum ExEventInfoAPI
{
	EX_EVENT_INFO_CLONE = 0,
	EX_EVENT_INFO_DESTROY,
	EX_EVENT_INFO_GET_EVENT_TYPE,
	EX_EVENT_INFO_GET_OWNER,
	EX_EVENT_INFO_GET_CHANNEL,
	EX_EVENT_INFO_GET_ITEM_ID,
	EX_EVENT_INFO_GET_REQUEST_ID
}eExEventInfoAPI;

eExEventInfoAPI g_eEventInfoAPI;

bool g_bFeatureSupported;

GMainLoop *g_pNotificationMainLoop;
bool g_CallBackHit;
bool g_bAPIFailed;
time_t g_tCurrTime;

const char *g_pszNameID;
const char *g_pszNameText;
const char *g_pszTextID;
const char *g_pszTextText;
const char *g_pszImageID;
const char *g_pszImagePath;
const char *g_pszTimeID;
const char *g_pszChatID;
const char *g_pszButtonID;
const char *g_pszButtonTitle;
const char *g_pszMsgID;
const char *g_pszText;
const char *g_pszArg1;
noti_ex_reporter_h g_hEventinfoReporter;
noti_ex_manager_h g_hEventinfoManager;
noti_ex_manager_h g_hExManager;
noti_ex_item_h g_hItemButton;
noti_ex_item_h g_hItemChatMsg;
noti_ex_item_h g_hItemName;
noti_ex_item_h g_hItemText;
noti_ex_item_h g_hItemImage;
noti_ex_item_h g_hItemTime;
noti_ex_style_h g_hStyle;
noti_ex_color_h g_hColor;
noti_ex_padding_h g_hPadding;
noti_ex_geometry_h g_hGeometry;
noti_ex_multi_lang_h g_hMultiLang;
noti_ex_item_chat_message_type_e g_eChatMsgType;

unsigned char g_cAlpha, g_cRed, g_cGreen, g_cBlue;
int g_nLeft, g_nTop, g_nRight, g_nBottom, g_nX, g_nY, g_nW, g_nH, g_nArg2;
float g_fArg3;

char* NotificationExGetError(int nRet);
int SendNotification(void);
gboolean Timeout(gpointer data);
void FreeAndDeleteNotificationResourceHandle();
char* NotificationGetError(int nRet);
char* Application_AppControlGetError(int nRet);
int CreateChatMsgAttributes();
int DestroyChatMsgAttributes();
int CreateStyleAttributes();
int DestroyStyleAttributes();
int CreateButton();
int CreateMultiLangHandle();
int CreateNotificationList(noti_ex_item_h **pszhItemList);

//This function outputs the application data path
bool NotificationGetDataPath(char* pPath);

//This function appends the input string to app data path and outputs the final resultant path
bool NotificationAppendToAppDataPath(char* pInputPath, char* pFinalPath);

int NotificationAppCreate();

/** @} */ //end of itc-notification

#endif  //_ITS_NOTIFICATION_COMMON_H_
