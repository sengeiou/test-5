//
// Copyright (c) 2018 Samsung Electronics Co., Ltd.
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
#include "assert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <system_info.h>
#include <app_manager.h>
#include <watchface-complication-provider.h>
#include <watchface-editable.h>
#include <dlog.h>
#include <glib.h>
#include "ITs-watchface-complication-common.h"
#define TEST_PROVIDER_ID "org.tizen.watchface_sample_provider/test"
#define PROVIDER_ID "org.tizen.watchface-complication-native-itc/test"
#define EDITOR_CMD_KEY "EDITOR_CMD"
#define EDITOR_ID "org.tizen.watchface_sample_editor"
#define WATCHFACE_ID "org.tizen.watchface_sample"
#define COMPLICATION_TEST_APP "org.tizen.complication_test"
#define MAX_COUNTER 5
#define DATAISVALIDID 2
static int nWatchfaceId = 0;

/** @addtogroup itc-watchface-complication
*  @ingroup itc
*  @{
*/


//& set: watchface-complication

/**
* @function 		ITs_watchface_complication_provider_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @nReturn 		NA
*/
void ITs_watchface_complication_provider_startup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Watchface_Complication_Provider_p\\n", __LINE__, API_NAMESPACE);
#endif
	g_bWatchApp = TCTCheckSystemInfoFeatureSupported(FEATURE_WATCH_APP, API_NAMESPACE);
	g_bFeatureNotSupported = false;
	g_bIsFeatureMismatched = false;
	return;
}

/**
* @function 		ITs_watchface_complication_provider_cleanup
* @description	 	Called after each test
* @parameter		NA
* @nReturn 		NA
*/
void ITs_watchface_complication_provider_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Watchface_Complication_Provider_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/****************************************************Helper Functions Start****************************************************/
/**
* @function 		RunApp
* @description	 	Helper Function
* @parameters		char *pszTargetApp, char *pszKey, char *pszValue, int nCompId
* @return 		NA
*/
static void RunApp(char *pszTargetApp, char *pszKey, char *pszValue, int nCompId)
{
	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "RunApp");
	static app_control_h hAppControl;
	bool bIsRunning = false;
	char pszCompId[10];
	int nCounter = MAX_COUNTER;

	int nRet = app_control_create(&hAppControl);
	if(nRet != APP_CONTROL_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] app_control_create returned %s error\\n", __LINE__, API_NAMESPACE, AppControlGetError(nRet));
		return;
	}
	if(hAppControl == NULL)
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, "app_control_create");
		return;
	}

	nRet = app_control_set_app_id(hAppControl, pszTargetApp);
	if(nRet != APP_CONTROL_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] app_control_set_app_id returned %s error\\n", __LINE__, API_NAMESPACE, AppControlGetError(nRet));
		app_control_destroy(hAppControl);
		return;
	}

	if (pszKey && pszValue) {
		nRet = app_control_add_extra_data(hAppControl, pszKey, pszValue);
		if(nRet != APP_CONTROL_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] app_control_add_extra_data returned %s error\\n", __LINE__, API_NAMESPACE, AppControlGetError(nRet));
			app_control_destroy(hAppControl);
			return;
		}
	}
	snprintf(pszCompId, sizeof(pszCompId)-1, "%d", nCompId);
	nRet = app_control_add_extra_data(hAppControl, "COMP_ID", pszCompId);
	if(nRet != APP_CONTROL_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] app_control_add_extra_data returned %s error\\n", __LINE__, API_NAMESPACE, AppControlGetError(nRet));
		app_control_destroy(hAppControl);
		return;
	}

	char *id = NULL;
	nRet = app_get_id(&id);
	if(nRet != APP_ERROR_NONE) {
		FPRINTF("[Line : %d][%s] app_control_add_extra_data returned %d error\\n", __LINE__, API_NAMESPACE, nRet);
		app_control_destroy(hAppControl);
		return;
	}

	nRet = app_control_add_extra_data(hAppControl, "SENDER_ID", id);
	free(id);
	if(nRet != APP_CONTROL_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] app_control_add_extra_data returned %s error\\n", __LINE__, API_NAMESPACE, AppControlGetError(nRet));
		app_control_destroy(hAppControl);
		return;
	}

	do {
		nRet = app_control_send_launch_request(hAppControl, NULL, NULL);
		if (nRet != APP_CONTROL_ERROR_NONE)
			sleep(1);
		app_manager_is_running(pszTargetApp, &bIsRunning);
	} while (--nCounter > 0 && !bIsRunning);
	sleep(1);
	app_control_destroy(hAppControl);
}

/**
* @function 		ComplicationProviderUpdateRequestedCb
* @description	 	Callback Function
* @parameters		const char *pszProviderId, const char *pszReqAppid,
			watchface_complication_type_e eType, const bundle *pszContext,bundle *pszShareData, void *pszUserData
* @return 		NA
*/
static void ComplicationProviderUpdateRequestedCb(const char *pszProviderId, const char *pszReqAppid,
		watchface_complication_type_e eType, const bundle *pszContext,bundle *pszShareData, void *pszUserData)
{
	FPRINTF("[Line : %d][%s] %s invoked\\n", __LINE__, API_NAMESPACE, "ComplicationProviderUpdateRequestedCb");
	g_bCallBackHit = true;
	return;
}

/**
* @function 		UpdateRequestedCb
* @description	 	Callback Function
* @parameters		const watchface_editable_h hHandle, int nSelectedIdx, const watchface_editable_edit_state_e eState, void *pszUserData
* @return 		NA
*/
static void UpdateRequestedCb(const watchface_editable_h hHandle, int nSelectedIdx, const watchface_editable_edit_state_e eState, void *pszUserData)
{
	FPRINTF("[Line : %d][%s] %s invoked\\n", __LINE__, API_NAMESPACE, "UpdateRequestedCb");
	g_bCallBackHit = true;
	return;
}

/**
* @function 		SetupOnEditReadyCb
* @description	 	Callback Function
* @parameters		watchface_editable_container_h hEdCon, const char *pszEditorAppid, void *pszUserData
* @return 		NA
*/
static void SetupOnEditReadyCb(watchface_editable_container_h hEdCon, const char *pszEditorAppid, void *pszUserData)
{
	FPRINTF("[Line : %d][%s] %s invoked\\n", __LINE__, API_NAMESPACE, "SetupOnEditReadyCb");
	int nEditableId = 1;
	complication_h hComp = NULL;
	watchface_editable_highlight_h hHighlight = NULL;
	complication_allowed_list_h allowed_list;

	int nRet = watchface_editable_highlight_create(&hHighlight, WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	CALLBACK_ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_editable_highlight_create");
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_create", WatchfaceComplicationGetError(nRet));
	CALLBACK_CHECK_HANDLE_EXIT(hHighlight, "watchface_editable_highlight_create");

	nRet = watchface_editable_highlight_set_geometry(hHighlight, 100, 100, 30, 30);
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_set_geometry", WatchfaceComplicationGetError(nRet), watchface_editable_highlight_destroy(hHighlight));

	nRet = watchface_complication_create(1, TEST_PROVIDER_ID,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT,
			WATCHFACE_COMPLICATION_EVENT_NONE, &hComp);
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet), watchface_editable_highlight_destroy(hHighlight));
	CALLBACK_CHECK_HANDLE_EXIT_CLEANUP(hComp, "watchface_complication_create", watchface_editable_highlight_destroy(hHighlight));

	nRet = watchface_complication_allowed_list_create(&allowed_list);
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_allowed_list_create", WatchfaceComplicationGetError(nRet),
				watchface_editable_highlight_destroy(hHighlight);watchface_complication_destroy(hComp););
	nRet = watchface_complication_allowed_list_add(allowed_list, TEST_PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT);
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_allowed_list_add", WatchfaceComplicationGetError(nRet),
				watchface_editable_highlight_destroy(hHighlight);watchface_complication_destroy(hComp);watchface_complication_allowed_list_destroy(allowed_list););
	nRet = watchface_complication_allowed_list_apply(hComp, allowed_list);
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_allowed_list_apply", WatchfaceComplicationGetError(nRet),
				watchface_editable_highlight_destroy(hHighlight);watchface_complication_destroy(hComp);watchface_complication_allowed_list_destroy(allowed_list););
	watchface_complication_allowed_list_destroy(allowed_list);

	nRet = watchface_editable_add_complication(hEdCon, nEditableId, hComp, hHighlight);
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_create", WatchfaceComplicationGetError(nRet), watchface_editable_highlight_destroy(hHighlight);watchface_complication_destroy(hComp));

	nRet = watchface_editable_request_edit(hEdCon, UpdateRequestedCb, NULL);
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_request_edit", WatchfaceComplicationGetError(nRet), watchface_editable_highlight_destroy(hHighlight);watchface_complication_destroy(hComp));

	watchface_editable_highlight_destroy(hHighlight);
	watchface_complication_destroy(hComp);
	return;
}

/**
* @function 		UpdateRequestedCb2
* @description	 	Callback Function
* @parameters		const char *pszProviderId, const char *pszReqAppid, watchface_complication_type_e eType, const bundle *pszContext,
			bundle *pszSharedData, void *pszUserData
* @return 		NA
*/
static void UpdateRequestedCb2(const char *pszProviderId, const char *pszReqAppid, watchface_complication_type_e eType, const bundle *pszContext,
		bundle *pszSharedData, void *pszUserData)
{
	FPRINTF("[Line : %d][%s] %s invoked\\n", __LINE__, API_NAMESPACE, "UpdateRequestedCb2");
	int nRet = WATCHFACE_COMPLICATION_ERROR_IO_ERROR;
	complication_time_info_h hTimeInfo = NULL;

	switch(eType)
	{
	case WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT :
		nRet = watchface_complication_provider_data_set_short_text(pszSharedData, "short text");
		CALLBACK_ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_provider_data_set_short_text");
		CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_data_set_short_text", WatchfaceComplicationGetError(nRet));
		nRet =  watchface_complication_provider_data_set_title(	pszSharedData, "title");
		CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_data_set_title", WatchfaceComplicationGetError(nRet));
		break;
	case WATCHFACE_COMPLICATION_TYPE_LONG_TEXT :
		nRet = watchface_complication_provider_data_set_long_text(pszSharedData, "long text");
		CALLBACK_ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_provider_data_set_long_text");
		CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_data_set_long_text", WatchfaceComplicationGetError(nRet));
		nRet = watchface_complication_provider_data_set_extra_data(pszSharedData, "extra data");
		CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_data_set_extra_data", WatchfaceComplicationGetError(nRet));
		break;
	case WATCHFACE_COMPLICATION_TYPE_RANGED_VALUE :
		nRet = watchface_complication_provider_data_set_ranged_value(
			pszSharedData, 50.0, 0.0, 100.0);
		CALLBACK_ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_provider_data_set_ranged_value");
		CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_data_set_ranged_value", WatchfaceComplicationGetError(nRet));
		break;
	case WATCHFACE_COMPLICATION_TYPE_ICON :
		nRet = watchface_complication_provider_data_set_icon_path(pszSharedData, "temp_icon_path");
		CALLBACK_ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_provider_data_set_icon_path");
		CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_data_set_icon_path", WatchfaceComplicationGetError(nRet));
		break;
	case WATCHFACE_COMPLICATION_TYPE_IMAGE :
		nRet = watchface_complication_provider_data_set_image_path(pszSharedData, "temp_image_path");
		CALLBACK_ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_provider_data_set_image_path");
		CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_data_set_image_path", WatchfaceComplicationGetError(nRet));
		break;
	case WATCHFACE_COMPLICATION_TYPE_TIME :
		nRet = watchface_complication_provider_timeinfo_create(&hTimeInfo);
		CALLBACK_ISFEATURE_SUPPORTED_EXIT(WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, nRet, "watchface_complication_provider_timeinfo_create");
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_provider_timeinfo_create", WatchfaceComplicationGetError(nRet));
		CHECK_HANDLE_EXIT(hTimeInfo, "watchface_complication_provider_timeinfo_create");

		nRet = watchface_complication_provider_timeinfo_set_timezone(hTimeInfo, "UTC+9");
		CALLBACK_EXIT_CLEANUP(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_provider_timeinfo_set_timezone", WatchfaceComplicationGetError(nRet), watchface_complication_provider_timeinfo_destroy(hTimeInfo));

		nRet = watchface_complication_provider_timeinfo_set_timezone_id(hTimeInfo, "Asia/Seoul");
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_provider_timeinfo_set_timezone_id", WatchfaceComplicationGetError(nRet));

		nRet = watchface_complication_provider_timeinfo_set_timezone_country(hTimeInfo, "Korea");
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_provider_timeinfo_set_timezone_country", WatchfaceComplicationGetError(nRet));

		nRet = watchface_complication_provider_timeinfo_set_timezone_city(hTimeInfo, "Seoul");
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_provider_timeinfo_set_timezone_city", WatchfaceComplicationGetError(nRet));

		nRet = watchface_complication_provider_data_set_timeinfo(pszSharedData, hTimeInfo);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_provider_data_set_timeinfo", WatchfaceComplicationGetError(nRet));

		nRet = watchface_complication_provider_timeinfo_destroy(hTimeInfo);
		PRINT_RESULT_NORETURN(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_provider_timeinfo_destroy", WatchfaceComplicationGetError(nRet));
		break;
	default :
		break;
	}
	g_bCallBackHit = true;
	QuitGmainLoop();
}

/**
* @function 		WatchfaceComplicationProviderDataIsValidCb
* @description	 	Callback Function
* @parameters		const char *pszProviderId, const char *pszReqAppid, watchface_complication_type_e eType, const bundle *pszContext, bundle *pszSharedData, 				void *pszUserData
* @return 		NA
*/
static void WatchfaceComplicationProviderDataIsValidCb(const char *pszProviderId, const char *pszReqAppid, watchface_complication_type_e eType, const bundle *pszContext, bundle *pszSharedData, void *pszUserData)
{
	FPRINTF("[Line : %d][%s] %s invoked\\n", __LINE__, API_NAMESPACE, "WatchfaceComplicationProviderDataIsValidCb");
	bool bIsValid = false;
	char *pszUserDataChar = (char *)pszUserData;
	int nRet;

	if (eType == WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT)
	{
		nRet = watchface_complication_provider_data_set_short_text(pszSharedData, "short_text");
		CALLBACK_ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_provider_data_set_short_text");
		CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_data_set_short_text", WatchfaceComplicationGetError(nRet));

		nRet = watchface_complication_provider_data_is_valid(pszSharedData, &bIsValid);
		CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_data_is_valid", WatchfaceComplicationGetError(nRet));
		if(bIsValid != true)
		{
			FPRINTF("[Line : %d][%s] %s failed. bIsValid = false\\n", __LINE__, API_NAMESPACE, "watchface_complication_provider_data_is_valid");
			app_control_destroy(g_hTestControl);
			QuitGmainLoop();
			return;
		}

		if(strncmp(pszUserDataChar, g_pszCheckUserData, strlen(g_pszCheckUserData)) != 0){
			app_control_destroy(g_hTestControl);
			QuitGmainLoop();
			return;
		}
		g_bCallBackHit = true;
	}
	app_control_destroy(g_hTestControl);
	QuitGmainLoop();
	return;
}

/**
* @function 		WatchfaceComplicationProviderSetupReplyToEditorChecker
* @description	 	Helper Function
* @parameters		NA
* @return 		NA
*/
void WatchfaceComplicationProviderSetupReplyToEditorChecker(void)
{
	bundle *pszContext = bundle_create();
	int nRet = get_last_result();
	PRINT_RESULT_EXIT(nRet, BUNDLE_ERROR_NONE, "bundle_create", BundleGetError(nRet));
	CALLBACK_CHECK_HANDLE_EXIT_CLEANUP(pszContext, "bundle_create", app_control_destroy(g_hTestControl));
	nRet = watchface_complication_provider_setup_reply_to_editor(g_hTestControl, pszContext);
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_setup_reply_to_editor", 					WatchfaceComplicationGetError(nRet), bundle_free(pszContext);app_control_destroy(g_hTestControl));
	bundle_free(pszContext);
	app_control_destroy(g_hTestControl);
	g_bCheckerHit = true;
	return;
}

/**
* @function 		WatchfaceComplicationProviderSetupIsEditingChecker
* @description	 	Helper Function
* @parameters		NA
* @return 		NA
*/
void WatchfaceComplicationProviderSetupIsEditingChecker(void)
{
	bool IsEditing = false;
	int nRet = watchface_complication_provider_setup_is_editing(g_hTestControl, &IsEditing);
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_setup_is_editing", WatchfaceComplicationGetError(nRet), app_control_destroy(g_hTestControl));
	if(IsEditing != true)
	{
		FPRINTF("[Line : %d][%s] %s failed. IsEditing = false\\n", __LINE__, API_NAMESPACE, "watchface_complication_provider_setup_is_editing");
		app_control_destroy(g_hTestControl);
		QuitGmainLoop();
		return;
	}
	app_control_destroy(g_hTestControl);
	g_bCheckerHit = true;
	return;
}

/**
* @function 		WatchfaceComplicationProviderSetupGetContextChecker
* @description	 	Helper Function
* @parameters		NA
* @return 		NA
*/
void WatchfaceComplicationProviderSetupGetContextChecker(void)
{
	bundle *pszContext = NULL;
	int nRet = watchface_complication_provider_setup_get_context(g_hTestControl, &pszContext);
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_setup_get_context", 					WatchfaceComplicationGetError(nRet), app_control_destroy(g_hTestControl));
	CALLBACK_CHECK_HANDLE_EXIT_CLEANUP(pszContext, "watchface_complication_provider_setup_get_context", app_control_destroy(g_hTestControl));
	bundle_free(pszContext);
	app_control_destroy(g_hTestControl);
	g_bCheckerHit = true;
	return;
}

/**
* @function 		WatchfaceComplicationProviderEventGetTypeChecker
* @description	 	Helper Function
* @parameters		NA
* @return 		NA
*/
void WatchfaceComplicationProviderEventGetTypeChecker(void)
{
	watchface_complication_event_type_e eEventType = WATCHFACE_COMPLICATION_EVENT_NONE;
	int nRet = watchface_complication_provider_event_get_type(g_hTestControl, &eEventType);
	CALLBACK_ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_provider_event_get_type");
	CALLBACK_EXIT_CLEANUP(eEventType, WATCHFACE_COMPLICATION_EVENT_TAP, "watchface_complication_provider_event_get_type", WatchfaceComplicationGetError(nRet), app_control_destroy(g_hTestControl));
	if(eEventType < WATCHFACE_COMPLICATION_EVENT_NONE || eEventType > WATCHFACE_COMPLICATION_EVENT_DOUBLE_TAP)
	{
		FPRINTF("[Line : %d][%s] %s failed. eType = %d\\n", __LINE__, API_NAMESPACE, "watchface_complication_provider_event_get_type", eEventType);
		app_control_destroy(g_hTestControl);
		return;
	}

	g_bCheckerHit = true;
	app_control_destroy(g_hTestControl);
	return;
}

/**
* @function 		WatchfaceComplicationProviderEventGetProviderIdChecker
* @description	 	Helper Function
* @parameters		NA
* @return 		NA
*/
void WatchfaceComplicationProviderEventGetProviderIdChecker(void)
{
	char *pszProviderId = NULL;

	int nRet = watchface_complication_provider_event_get_provider_id(g_hTestControl, &pszProviderId);
	CALLBACK_ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_provider_event_get_provider_id");
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_event_get_provider_id", WatchfaceComplicationGetError(nRet), app_control_destroy(g_hTestControl));
	CALLBACK_CHECK_HANDLE_EXIT_CLEANUP(pszProviderId, "watchface_complication_provider_event_get_provider_id", app_control_destroy(g_hTestControl));

	g_bCheckerHit = true;
	app_control_destroy(g_hTestControl);
	FREE_MEMORY(pszProviderId);
	QuitGmainLoop();
}

/**
* @function 		WatchfaceComplicationProviderEventGetComplicationTypeChecker
* @description	 	Helper Function
* @parameters		NA
* @return 		NA
*/
void WatchfaceComplicationProviderEventGetComplicationTypeChecker(void)
{
	watchface_complication_type_e eType;

	int nRet = watchface_complication_provider_event_get_complication_type(g_hTestControl, &eType);
	CALLBACK_ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_provider_event_get_complication_type");
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_event_get_complication_type", WatchfaceComplicationGetError(nRet), app_control_destroy(g_hTestControl));
	if(eType < WATCHFACE_COMPLICATION_TYPE_NO_DATA || eType > WATCHFACE_COMPLICATION_TYPE_IMAGE)
	{
		FPRINTF("[Line : %d][%s] %s failed. eType = %d\\n", __LINE__, API_NAMESPACE, "watchface_complication_provider_event_complication_type", eType);
		app_control_destroy(g_hTestControl);
		QuitGmainLoop();
		return;
	}
	g_bCheckerHit = true;
	app_control_destroy(g_hTestControl);
	QuitGmainLoop();
}

/**
* @function 		WatchfaceComplicationProviderEventGetContextChecker
* @description	 	Helper Function
* @parameters		NA
* @return 		NA
*/
void WatchfaceComplicationProviderEventGetContextChecker(void)
{
	watchface_complication_type_e eType;

	int nRet = watchface_complication_provider_event_get_complication_type(g_hTestControl, &eType);
	CALLBACK_ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_provider_event_get_complication_type");
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_event_get_context", WatchfaceComplicationGetError(nRet), app_control_destroy(g_hTestControl));
	if(eType < WATCHFACE_COMPLICATION_TYPE_NO_DATA || eType > WATCHFACE_COMPLICATION_TYPE_IMAGE)
	{
		FPRINTF("[Line : %d][%s] %s failed. eType = %d\\n", __LINE__, API_NAMESPACE, "watchface_complication_provider_event_get_complication_type", eType);
		app_control_destroy(g_hTestControl);
		QuitGmainLoop();
		return;
	}
	g_bCheckerHit = true;
	app_control_destroy(g_hTestControl);
	QuitGmainLoop();
}

/*****************************************************Helper Functions End*****************************************************/

//& purpose: To add and remove the callback function to be executed when the update requested
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_add_remove_update_requested_cb_p
* @since_tizen				5.0
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Add and remove the callback function to be executed when the update requested.
* @scenario				Add and remove the callback function to be executed when the update requested.
* @apicovered				watchface_complication_provider_add_update_requested_cb, watchface_complication_provider_remove_update_requested_cb
* @passcase				When add and remove requested cb returns 0
* @failcase				When either of add and remove requested cb returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_add_remove_update_requested_cb_p(void)
{
	START_TEST;
	int nRet = watchface_complication_provider_add_update_requested_cb(PROVIDER_ID, ComplicationProviderUpdateRequestedCb, NULL);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_provider_add_update_requested_cb");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_add_update_requested_cb", WatchfaceComplicationGetError(nRet));

	nRet = watchface_complication_provider_remove_update_requested_cb(PROVIDER_ID, ComplicationProviderUpdateRequestedCb);
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_remove_update_requested_cb", WatchfaceComplicationGetError(nRet));

	service_app_exit();
	return 0;
}

//& purpose: To notify to the complication that there is an update
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_notify_update_p
* @since_tizen				5.0
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Notifys to the complication that there is an update.
* @scenario				Complication automatically requests data when notify is received.
* @apicovered				watchface_complication_provider_notify_update
* @passcase				watchface_complication_provider_notify_update returns 0
* @failcase				watchface_complication_provider_notify_update returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_notify_update_p(void)
{
	START_TEST;
	g_bCallBackHit = false;
	int nRet = watchface_complication_provider_add_update_requested_cb(PROVIDER_ID, ComplicationProviderUpdateRequestedCb, NULL);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_provider_add_update_requested_cb");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_add_update_requested_cb", WatchfaceComplicationGetError(nRet));

	nWatchfaceId =  nWatchfaceId + 1;
	RunApp(COMPLICATION_TEST_APP, "COMP_TYPE", "SHORT_TEXT", nWatchfaceId);

	nRet = watchface_complication_provider_notify_update(PROVIDER_ID);
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_notify_update", WatchfaceComplicationGetError(nRet));

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "ComplicationProviderUpdateRequestedCb");
		WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
		return 1;
	}

	WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
	return 0;
}

//& purpose: To send reply to the editor
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_setup_reply_to_editor_p
* @since_tizen				5.0
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Sends reply to the editor.
* @scenario				Using this function, setup app can sends new context data to the editor
* @apicovered				watchface_complication_provider_setup_reply_to_editor
* @passcase				watchface_complication_provider_setup_reply_to_editor returns 0
* @failcase				watchface_complication_provider_setup_reply_to_editor returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_setup_reply_to_editor_p(void)
{
	START_TEST;
	g_bCallBackHit = false;
	g_bCheckerHit = false;

	int nRet = watchface_editable_add_edit_ready_cb(SetupOnEditReadyCb, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_add_edit_ready_cb", WatchfaceComplicationGetError(nRet));

	nWatchfaceId++;
	RunApp(EDITOR_ID, EDITOR_CMD_KEY, SETUP_REPLY_TO_EDITOR_TEST_VAL, nWatchfaceId);

	IterateGmainLoop();
	if(!g_bCheckerHit)
	{
		nRet = watchface_editable_remove_edit_ready_cb(SetupOnEditReadyCb);
		PRINT_RESULT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "SetupOnEditReadyCb");
		nRet = watchface_editable_remove_edit_ready_cb(SetupOnEditReadyCb);
		PRINT_RESULT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}

	nRet = watchface_editable_remove_edit_ready_cb(SetupOnEditReadyCb);
	PRINT_RESULT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
	service_app_exit();
	return 0;
}

//& purpose: To check whether watch app request editing or not
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_setup_is_editing_p
* @since_tizen				5.0
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Checks whether watch app request editing or not.
* @scenario				Using this function, setup app can tell what kind of UI should be displayed.
* @apicovered				watchface_complication_provider_setup_is_editing
* @passcase				watchface_complication_provider_setup_is_editing returns 0
* @failcase				watchface_complication_provider_setup_is_editing returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_setup_is_editing_p(void)
{
	START_TEST;
	g_bCallBackHit = false;
	g_bCheckerHit = false;

	int nRet = watchface_editable_add_edit_ready_cb(SetupOnEditReadyCb, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_add_edit_ready_cb", WatchfaceComplicationGetError(nRet));

	nWatchfaceId++;
	RunApp(EDITOR_ID, EDITOR_CMD_KEY, SETUP_IS_EDITING_TEST_VAL, nWatchfaceId);

	IterateGmainLoop();
	if(!g_bCheckerHit)
	{
		nRet = watchface_editable_remove_edit_ready_cb(SetupOnEditReadyCb);
		PRINT_RESULT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "SetupOnEditReadyCb");
		nRet = watchface_editable_remove_edit_ready_cb(SetupOnEditReadyCb);
		PRINT_RESULT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}
	nRet = watchface_editable_remove_edit_ready_cb(SetupOnEditReadyCb);
	PRINT_RESULT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
	service_app_exit();
	return 0;
}

//& purpose: To get provider app's setup context data
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_setup_get_context_p
* @since_tizen				5.0
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets provider app's setup context data.
* @scenario				Context data will be passed to the complication provider application.
* @apicovered				watchface_complication_provider_setup_get_context
* @passcase				watchface_complication_provider_setup_get_context returns 0
* @failcase				watchface_complication_provider_setup_get_context returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_setup_get_context_p(void)
{
	START_TEST;
	g_bCallBackHit = false;
	int nRet = watchface_editable_add_edit_ready_cb(SetupOnEditReadyCb, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_add_edit_ready_cb", WatchfaceComplicationGetError(nRet));

	nWatchfaceId++;
	RunApp(EDITOR_ID, EDITOR_CMD_KEY, SETUP_GET_CONTEXT_TEST_VAL, nWatchfaceId);

	IterateGmainLoop();
	if(!g_bCheckerHit)
	{
		watchface_editable_remove_edit_ready_cb(SetupOnEditReadyCb);
		PRINT_RESULT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "SetupOnEditReadyCb");
		nRet = watchface_editable_remove_edit_ready_cb(SetupOnEditReadyCb);
		PRINT_RESULT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}
	nRet = watchface_editable_remove_edit_ready_cb(SetupOnEditReadyCb);
	PRINT_RESULT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
	service_app_exit();
	return 0;
}

//& purpose: To set short text data for shared data
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_data_set_short_text_p
* @since_tizen				5.0
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Sets short text data for shared data.
* @scenario				Sets short text data for shared data.
* @apicovered				watchface_complication_provider_data_set_short_text
* @passcase				watchface_complication_provider_data_set_short_text returns 0
* @failcase				watchface_complication_provider_data_set_short_text returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_data_set_short_text_p(void)
{
	START_TEST;
	int nRet = watchface_complication_provider_add_update_requested_cb(PROVIDER_ID, UpdateRequestedCb2, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_add_update_requested_cb", WatchfaceComplicationGetError(nRet));
	g_bCallBackHit = false;
	nWatchfaceId++;
	RunApp(COMPLICATION_TEST_APP, "COMP_TYPE", "SHORT_TEXT", nWatchfaceId);

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "UpdateRequestedCb2");
		WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
	return 0;
}

//& purpose: To set long text data for shared data
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_data_set_long_text_p
* @since_tizen				5.0
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Sets long text data for shared data.
* @scenario				Sets long text data for shared data.
* @apicovered				watchface_complication_provider_data_set_long_text
* @passcase				watchface_complication_provider_data_set_long_text returns 0
* @failcase				watchface_complication_provider_data_set_long_text returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_data_set_long_text_p(void)
{
	START_TEST;
	g_bCallBackHit = false;
	int nRet = watchface_complication_provider_add_update_requested_cb(PROVIDER_ID, UpdateRequestedCb2, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_add_update_requested_cb", WatchfaceComplicationGetError(nRet));

	nWatchfaceId++;
	RunApp(COMPLICATION_TEST_APP, "COMP_TYPE", "LONG_TEXT", nWatchfaceId);
	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "UpdateRequestedCb2");
		WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
	return 0;
}

//& purpose: To set title data for shared data
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_data_set_title_p
* @since_tizen				5.0
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Sets title data for shared data.
* @scenario				Sets title data for shared data.
* @apicovered				watchface_complication_provider_data_set_title
* @passcase				watchface_complication_provider_data_set_title returns 0
* @failcase				watchface_complication_provider_data_set_title returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_data_set_title_p(void)
{
	START_TEST;
	int nRet = watchface_complication_provider_add_update_requested_cb(PROVIDER_ID, UpdateRequestedCb2, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_add_update_requested_cb", WatchfaceComplicationGetError(nRet));
	g_bCallBackHit = false;
	nWatchfaceId++;
	RunApp(COMPLICATION_TEST_APP, "COMP_TYPE", "SHORT_TEXT", nWatchfaceId);

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "UpdateRequestedCb2");
		WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
	return 0;
}

//& purpose: To set image path data for shared data
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_data_set_image_path_p
* @since_tizen				5.0
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Sets image path data for shared data.
* @scenario				Sets image path data for shared data.
* @apicovered				watchface_complication_provider_data_set_image_path
* @passcase				watchface_complication_provider_data_set_image_path returns 0
* @failcase				watchface_complication_provider_data_set_image_path returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_data_set_image_path_p(void)
{
	START_TEST;
	int nRet = watchface_complication_provider_add_update_requested_cb(PROVIDER_ID, UpdateRequestedCb2, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_add_update_requested_cb", WatchfaceComplicationGetError(nRet));
	g_bCallBackHit = false;
	nWatchfaceId++;
	RunApp(COMPLICATION_TEST_APP, "COMP_TYPE", "IMAGE", nWatchfaceId);

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "UpdateRequestedCb2");
		WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
	return 0;
}

//& purpose: To set ranged value data for shared data
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_data_set_ranged_value_p
* @since_tizen				5.0
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Sets ranged value data for shared data.
* @scenario				Sets ranged value data for shared data.
* @apicovered				watchface_complication_provider_data_set_ranged_value
* @passcase				watchface_complication_provider_data_set_ranged_value returns 0
* @failcase				watchface_complication_provider_data_set_ranged_value returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_data_set_ranged_value_p(void)
{
	START_TEST;
	int nRet = watchface_complication_provider_add_update_requested_cb(PROVIDER_ID, UpdateRequestedCb2, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_add_update_requested_cb", WatchfaceComplicationGetError(nRet));
	g_bCallBackHit = false;
	nWatchfaceId++;
	RunApp(COMPLICATION_TEST_APP, "COMP_TYPE", "RANGED_VALUE", nWatchfaceId);

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "UpdateRequestedCb2");
		WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
	return 0;
}

//& purpose: To set icon path data for shared data
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_data_set_icon_path_p
* @since_tizen				5.0
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Sets icon path data for shared data.
* @scenario				Sets icon path data for shared data.
* @apicovered				watchface_complication_provider_data_set_icon_path
* @passcase				watchface_complication_provider_data_set_icon_path returns 0
* @failcase				watchface_complication_provider_data_set_icon_path returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_data_set_icon_path_p(void)
{
	START_TEST;
	int nRet = watchface_complication_provider_add_update_requested_cb(PROVIDER_ID, UpdateRequestedCb2, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_add_update_requested_cb", WatchfaceComplicationGetError(nRet));
	g_bCallBackHit = false;
	nWatchfaceId++;
	RunApp(COMPLICATION_TEST_APP, "COMP_TYPE", "ICON", nWatchfaceId);
	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "UpdateRequestedCb2");
		WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
	return 0;
}

//& purpose: To set extra data for shared data
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_data_set_extra_data_p
* @since_tizen				5.0
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Sets extra data for shared data.
* @scenario				Sets extra data for shared data.
* @apicovered				watchface_complication_provider_data_set_extra_data
* @passcase				watchface_complication_provider_data_set_extra_data returns 0
* @failcase				watchface_complication_provider_data_set_extra_data returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_data_set_extra_data_p(void)
{
	START_TEST;
	int nRet = watchface_complication_provider_add_update_requested_cb(PROVIDER_ID, UpdateRequestedCb2, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_add_update_requested_cb", WatchfaceComplicationGetError(nRet));
	g_bCallBackHit = false;
	nWatchfaceId =  nWatchfaceId + 1;
	RunApp(COMPLICATION_TEST_APP, "COMP_TYPE", "LONG_TEXT", nWatchfaceId);
	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "UpdateRequestedCb2");
		WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
	service_app_exit();
	return 0;
}

//& purpose: To get touch event type that is transferred from watchface
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_event_get_type_p
* @since_tizen				5.0
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets touch event type that is transferred from watchface.
* @scenario				Gets touch event type that is transferred from watchface.
* @apicovered				watchface_complication_provider_event_get_type
* @passcase				watchface_complication_provider_event_get_type returns 0
* @failcase				watchface_complication_provider_event_get_type returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_event_get_type_p(void)
{
	START_TEST;
	g_bCheckerHit = false;
	g_pszEventCmd = EVENT_GET_EVENT_TYPE_TEST_VAL;
	nWatchfaceId =  nWatchfaceId + 1;
	RunApp(COMPLICATION_TEST_APP, "EVENT_TEST", EVENT_GET_EVENT_TYPE_TEST_VAL, nWatchfaceId);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	IterateGmainLoop();

	if(!g_bCheckerHit)
	{
		service_app_exit();
		return 1;
	}
	service_app_exit();
	return 0;
}

//& purpose: To get provider id of touched complication
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_event_get_provider_id_p
* @since_tizen				5.0
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets provider id of touched complication.
* @scenario				Gets provider id of touched complication.
* @apicovered				watchface_complication_provider_event_get_provider_id
* @passcase				watchface_complication_provider_event_get_provider_id returns 0
* @failcase				watchface_complication_provider_event_get_provider_id returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_event_get_provider_id_p(void)
{
	START_TEST;
	g_bCheckerHit = false;
	g_pszEventCmd = EVENT_GET_PROVIDER_ID_TEST_VAL;
	nWatchfaceId =  nWatchfaceId + 1;
	RunApp(COMPLICATION_TEST_APP, "EVENT_TEST", EVENT_GET_PROVIDER_ID_TEST_VAL, nWatchfaceId);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;

	IterateGmainLoop();
	if(!g_bCheckerHit)
	{
		return 1;
	}
	return 0;
}

//& purpose: To get complication type of touched complication
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_event_get_complication_type_p
* @since_tizen				5.0
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets complication type of touched complication.
* @scenario				Gets complication type of touched complication.
* @apicovered				watchface_complication_provider_event_get_complication_type
* @passcase				watchface_complication_provider_event_get_complication_type returns 0
* @failcase				watchface_complication_provider_event_get_complication_type returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_event_get_complication_type_p(void)
{
	START_TEST;
	g_bCheckerHit = false;
	g_pszEventCmd = EVENT_GET_COMP_TYPE_TEST_VAL;
	nWatchfaceId =  nWatchfaceId + 1;
	RunApp(COMPLICATION_TEST_APP, "EVENT_TEST", EVENT_GET_COMP_TYPE_TEST_VAL, nWatchfaceId);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;

	IterateGmainLoop();
	if(!g_bCheckerHit)
	{
		return 1;
	}
	return 0;
}

//& purpose: To get complication context of touched complication
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_event_get_context_p
* @since_tizen				5.0
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets complication context of touched complication.
* @scenario				Gets complication context of touched complication.
* @apicovered				watchface_complication_provider_event_get_context
* @passcase				watchface_complication_provider_event_get_context returns 0
* @failcase				watchface_complication_provider_event_get_context returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_event_get_context_p(void)
{
	START_TEST;
	g_bCheckerHit = false;
	g_pszEventCmd = EVENT_GET_CONTEXT_TEST_VAL;
	nWatchfaceId =  nWatchfaceId + 1;
	RunApp(COMPLICATION_TEST_APP, "EVENT_TEST", EVENT_GET_CONTEXT_TEST_VAL, nWatchfaceId);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;

	IterateGmainLoop();
	if(!g_bCheckerHit)
	{
		return 1;
	}
	return 0;
}

//& purpose: To set screen reader text for shared data
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_data_set_screen_reader_text_p
* @since_tizen				5.0
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Sets screen reader text for shared data.
* @scenario				Sets screen reader text for shared data.
* @apicovered				watchface_complication_provider_data_set_screen_reader_text
* @passcase				watchface_complication_provider_data_set_screen_reader_text returns 0
* @failcase				watchface_complication_provider_data_set_screen_reader_text returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_data_set_screen_reader_text_p(void)
{
	START_TEST;
	bundle *pszSharedData = bundle_create();
	int nRet = get_last_result();
	PRINT_RESULT_EXIT(nRet, BUNDLE_ERROR_NONE, "bundle_create", BundleGetError(nRet));
	CALLBACK_CHECK_HANDLE_EXIT_CLEANUP(pszSharedData, "bundle_create", app_control_destroy(g_hTestControl));
	nRet = watchface_complication_provider_data_set_screen_reader_text(pszSharedData, "screen_reader_text test");
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_provider_data_set_screen_reader_text");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_data_set_screen_reader_text", WatchfaceComplicationGetError(nRet));

	bundle_free(pszSharedData);
	service_app_exit();
	return 0;
}

//& purpose: To check whether shared data is valid or not
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_data_is_valid_p
* @since_tizen				5.0
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Check whether shared data is valid or not.
* @scenario				Check whether shared data is valid or not.
* @apicovered				ITc_watchface_complication_provider_data_is_valid_p
* @passcase				ITc_watchface_complication_provider_data_is_valid_p returns 0
* @failcase				ITc_watchface_complication_provider_data_is_valid_p returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_data_is_valid_p(void)
{
	START_TEST;
	g_bCallBackHit = false;
	int nRet = watchface_complication_provider_add_update_requested_cb(PROVIDER_ID, WatchfaceComplicationProviderDataIsValidCb, g_pszCheckUserData);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_data_is_valid", WatchfaceComplicationGetError(nRet));

	RunApp(COMPLICATION_TEST_APP, "COMP_TYPE", "SHORT_TEXT", DATAISVALIDID);
	IterateGmainLoop();

	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "WatchfaceComplicationProviderDataIsValidCb");
		WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
		return 1;
	}

	WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
	return 0;
}

//& purpose: To Creates and Destroy timeinfo data.
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_timeinfo_create_destroy_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description				Creates and Destroy timeinfo data.
* @scenario				Creates and Destroy timeinfo data.
* @apicovered				watchface_complication_provider_timeinfo_create, watchface_complication_provider_timeinfo_destroy
* @passcase				Target APIs returns 0
* @failcase				Target APIs returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_timeinfo_create_destroy_p(void)
{
	START_TEST;

	int nRet = WATCHFACE_COMPLICATION_ERROR_NONE;
	complication_time_info_h hTimeInfo = NULL;

	nRet = watchface_complication_provider_timeinfo_create(&hTimeInfo);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_provider_timeinfo_create");
	PRINT_RESULT_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_provider_timeinfo_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hTimeInfo, "watchface_complication_provider_timeinfo_create");

	nRet = watchface_complication_provider_timeinfo_destroy(hTimeInfo);
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_timeinfo_destroy", WatchfaceComplicationGetError(nRet));

	service_app_exit();
	return 0;
}

//& purpose: To Set timezone information.
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_timeinfo_set_timezone_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description				Set timezone information.
* @scenario				Set timezone information.
* @apicovered				watchface_complication_provider_timeinfo_set_timezone
* @passcase				watchface_complication_provider_timeinfo_set_timezone returns 0
* @failcase				watchface_complication_provider_timeinfo_set_timezone returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_timeinfo_set_timezone_p(void)
{
	START_TEST;
	int nRet = WATCHFACE_COMPLICATION_ERROR_NONE;

	nRet = watchface_complication_provider_add_update_requested_cb(PROVIDER_ID, UpdateRequestedCb2, NULL);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_provider_add_update_requested_cb");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_add_update_requested_cb", WatchfaceComplicationGetError(nRet));

	g_bCallBackHit = false;
	nWatchfaceId++;

	RunApp(COMPLICATION_TEST_APP, "COMP_TYPE", "TIME_ZONE", nWatchfaceId);

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "UpdateRequestedCb2");
		WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
	return 0;
}

//& purpose: To set timezone id.
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_timeinfo_set_timezone_id_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description				Set timezone id.
* @scenario				Set timezone id.
* @apicovered				watchface_complication_provider_timeinfo_set_timezone_id
* @passcase				watchface_complication_provider_timeinfo_set_timezone_id returns 0
* @failcase				watchface_complication_provider_timeinfo_set_timezone_id returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_timeinfo_set_timezone_id_p(void)
{
	START_TEST;
	int nRet = WATCHFACE_COMPLICATION_ERROR_NONE;

	nRet = watchface_complication_provider_add_update_requested_cb(PROVIDER_ID, UpdateRequestedCb2, NULL);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_provider_add_update_requested_cb");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_add_update_requested_cb", WatchfaceComplicationGetError(nRet));

	g_bCallBackHit = false;
	nWatchfaceId++;
	RunApp(COMPLICATION_TEST_APP, "COMP_TYPE", "TIME_ZONE_ID", nWatchfaceId);

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "UpdateRequestedCb2");
		WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
		return 1;
	}

	WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
	return 0;
}

//& purpose: To set timezone country information.
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_timeinfo_set_timezone_country_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description				Set timezone country information.
* @scenario				Set timezone country information.
* @apicovered				watchface_complication_provider_timeinfo_set_timezone_country
* @passcase				watchface_complication_provider_timeinfo_set_timezone_country returns 0
* @failcase				watchface_complication_provider_timeinfo_set_timezone_country returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_timeinfo_set_timezone_country_p(void)
{
	START_TEST;
	int nRet = WATCHFACE_COMPLICATION_ERROR_NONE;

	nRet = watchface_complication_provider_add_update_requested_cb(PROVIDER_ID, UpdateRequestedCb2, NULL);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_provider_add_update_requested_cb");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_add_update_requested_cb", WatchfaceComplicationGetError(nRet));

	g_bCallBackHit = false;
	nWatchfaceId++;
	RunApp(COMPLICATION_TEST_APP, "COMP_TYPE", "TIME_ZONE_COUNTRY", nWatchfaceId);

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "UpdateRequestedCb2");
		WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
		return 1;
	}

	WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
	return 0;
}

//& purpose: To set timezone city information.
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_timeinfo_set_timezone_city_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description				Set timezone city information.
* @scenario				Set timezone city information.
* @apicovered				watchface_complication_provider_timeinfo_set_timezone_city
* @passcase				watchface_complication_provider_timeinfo_set_timezone_city returns 0
* @failcase				watchface_complication_provider_timeinfo_set_timezone_city returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_timeinfo_set_timezone_city_p(void)
{
	START_TEST;
	int nRet = WATCHFACE_COMPLICATION_ERROR_NONE;

	nRet = watchface_complication_provider_add_update_requested_cb(PROVIDER_ID, UpdateRequestedCb2, NULL);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_provider_add_update_requested_cb");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_add_update_requested_cb", WatchfaceComplicationGetError(nRet));

	g_bCallBackHit = false;
	nWatchfaceId++;
	RunApp(COMPLICATION_TEST_APP, "COMP_TYPE", "TIME_ZONE_CITY", nWatchfaceId);

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "UpdateRequestedCb2");
		WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
	return 0;
}

//& purpose: To set time information data to shared data..
//& type: auto
/**
* @testcase				ITc_watchface_complication_provider_data_set_timeinfo_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description				Sets time information data to shared data.
* @scenario				Sets time information data to shared data.
* @apicovered				watchface_complication_provider_data_set_timeinfo
* @passcase				watchface_complication_provider_data_set_timeinfo returns 0
* @failcase				watchface_complication_provider_data_set_timeinfo returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_provider_data_set_timeinfo_p(void)
{
	START_TEST;
	int nRet = WATCHFACE_COMPLICATION_ERROR_NONE;

	nRet = watchface_complication_provider_add_update_requested_cb(PROVIDER_ID, UpdateRequestedCb2, NULL);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_provider_add_update_requested_cb");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_add_update_requested_cb", WatchfaceComplicationGetError(nRet));

	g_bCallBackHit = false;
	nWatchfaceId++;
	RunApp(COMPLICATION_TEST_APP, "COMP_TYPE", "TIME_INFO", nWatchfaceId);

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "UpdateRequestedCb2");
		WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet);
	return 0;
}

