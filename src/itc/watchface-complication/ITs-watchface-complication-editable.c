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
#include "ITs-watchface-complication-common.h"
#include <app_manager.h>
#define PROVIDER_ID "org.tizen.watchface_sample_provider/test"
#define EDITOR_ID "org.tizen.watchface_sample_editor"
#define MAX_COUNTER 5
#define GEO_X 100
#define GEO_Y 100
#define GEO_W 100
#define GEO_H 100

/** @addtogroup itc-watchface-complication
*  @ingroup itc
*  @{
*/

//& set: watchface-complication

/**
* @function 		ITs_watchface_editable_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @nReturn 		NA
*/
void ITs_watchface_editable_startup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Watchface_Editable_p\\n", __LINE__, API_NAMESPACE);
#endif
	g_bWatchApp = TCTCheckSystemInfoFeatureSupported(FEATURE_WATCH_APP, API_NAMESPACE);
	g_bFeatureNotSupported = false;
	g_bIsFeatureMismatched = false;
	return;
}

/**
* @function 		ITs_watchface_editable_cleanup
* @description	 	Called after each test
* @parameter		NA
* @nReturn 		NA
*/
void ITs_watchface_editable_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Watchface_Editable_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}


/****************************************************Callback Start****************************************************/
/**
* @function 		RunEditorApp
* @description	 	Helper Function
* @parameters		N/A
* @return 		N/A
*/
static void RunEditorApp()
{
	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "RunEditorApp");

	static app_control_h hAppControl;
	bool bIsRunning = false;
	int nCounter = MAX_COUNTER;
	int nRet;

	nRet = app_control_create(&hAppControl);
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

	nRet = app_control_set_app_id(hAppControl, EDITOR_ID);
	if(nRet != APP_CONTROL_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] app_control_set_app_id returned %s error\\n", __LINE__, API_NAMESPACE, AppControlGetError(nRet));
		app_control_destroy(hAppControl);
		return;
	}

	char *id = NULL;
	nRet = app_get_id(&id);
	if (nRet != APP_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] app_get_id returned %d error\\n", __LINE__, API_NAMESPACE, nRet);
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
		app_manager_is_running(EDITOR_ID, &bIsRunning);
	} while (--nCounter > 0 && !bIsRunning);
	sleep(1);

	return;
}


/**
* @function 		RequestEditWithDesignElements
* @description	 	Helper Function
* @parameters		hEdCon, updateCb
* @return 		0, 1
*/
static int RequestEditWithDesignElements(watchface_editable_container_h hEdCon, watchface_editable_update_requested_cb updateCb)
{
	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "RequestEditWithDesignElements");
	int nRet;
	complication_candidates_list_h hListHandle = NULL;
	bundle *candidate1;
	bundle *candidate2;
	watchface_editable_highlight_h hHighlight = NULL;

	nRet = watchface_editable_candidates_list_create(&hListHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_editable_candidates_list_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_candidates_list_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hListHandle, "watchface_editable_candidates_list_create");

	candidate1 = bundle_create();
	nRet = get_last_result();
	PRINT_RESULT_EXIT_CLEANUP(nRet, BUNDLE_ERROR_NONE, "bundle_create", BundleGetError(nRet), watchface_editable_candidates_list_destroy(hListHandle));
	CHECK_HANDLE_EXIT_CLEANUP(candidate1, "bundle_create", watchface_editable_candidates_list_destroy(hListHandle));
	bundle_add_str(candidate1, "COLOR", "RED");
	nRet = watchface_editable_candidates_list_add(hListHandle, candidate1);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_candidates_list_add", WatchfaceComplicationGetError(nRet), watchface_editable_candidates_list_destroy(hListHandle); bundle_free(candidate1));

	candidate2 = bundle_create();
	nRet = get_last_result();
	PRINT_RESULT_EXIT_CLEANUP(nRet, BUNDLE_ERROR_NONE, "bundle_create", BundleGetError(nRet), watchface_editable_candidates_list_destroy(hListHandle);bundle_free(candidate1));
	CHECK_HANDLE_EXIT_CLEANUP(candidate2, "bundle_create", watchface_editable_candidates_list_destroy(hListHandle); bundle_free(candidate1));
	bundle_add_str(candidate2, "COLOR", "BLUE");
	nRet = watchface_editable_candidates_list_add(hListHandle, candidate2);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_candidates_list_add", WatchfaceComplicationGetError(nRet), watchface_editable_candidates_list_destroy(hListHandle); bundle_free(candidate1); bundle_free(candidate2));

	nRet = watchface_editable_highlight_create(&hHighlight,	WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_create", WatchfaceComplicationGetError(nRet), watchface_editable_candidates_list_destroy(hListHandle); bundle_free(candidate1); bundle_free(candidate2));
	CHECK_HANDLE_EXIT_CLEANUP(hHighlight, "watchface_editable_highlight_create", watchface_editable_candidates_list_destroy(hListHandle); bundle_free(candidate1); bundle_free(candidate2));

	nRet = watchface_editable_highlight_set_geometry(hHighlight, GEO_X, GEO_Y, GEO_W, GEO_H);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_set_geometry", WatchfaceComplicationGetError(nRet), bundle_free(candidate1); bundle_free(candidate2); watchface_editable_candidates_list_destroy(hListHandle); watchface_editable_highlight_destroy(hHighlight));

	nRet = watchface_editable_add_design_element(hEdCon, 0, 0, hListHandle,	hHighlight, "Color");
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_add_design_element", WatchfaceComplicationGetError(nRet), bundle_free(candidate1); bundle_free(candidate2); watchface_editable_candidates_list_destroy(hListHandle); watchface_editable_highlight_destroy(hHighlight));

	nRet = watchface_editable_request_edit(hEdCon, updateCb, NULL);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_request_edit", WatchfaceComplicationGetError(nRet), bundle_free(candidate1); bundle_free(candidate2); watchface_editable_candidates_list_destroy(hListHandle); watchface_editable_highlight_destroy(hHighlight));

	bundle_free(candidate1);
	bundle_free(candidate2);
	watchface_editable_highlight_destroy(hHighlight);
	watchface_editable_candidates_list_destroy(hListHandle);

	return nRet;
}


/**
* @function 		RequestEditWithComplicationCb
* @description	 	Callback Function
* @parameters		hHandle, nSelectedIdx, eState, pszUserData
* @return 		NA
*/
static void RequestEditWithComplicationCb(const watchface_editable_h hHandle, int nSelectedIdx, const watchface_editable_edit_state_e eState, void *pszUserData)
{
	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "RequestEditWithComplicationCb");
	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		AddComplicationOnEditReadyCb
* @description	 	Callback Function
* @parameters		hEdCon, pszEditorAppid, pszUserData
* @return 		NA
*/
static void AddComplicationOnEditReadyCb(watchface_editable_container_h hEdCon,const char *pszEditorAppid,void *pszUserData)
{
	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "AddComplicationOnEditReadyCb");
	int nRet;
	int nEditableId = 1;
	complication_h hHandle;
	watchface_editable_highlight_h hHighlight;
	char *pszXUserData = (char *)pszUserData;

	if(strncmp(pszXUserData, g_pszCheckUserData, strlen(g_pszCheckUserData)) != 0){
		QuitGmainLoop();
		return;
	}
	nRet = watchface_editable_highlight_create(&hHighlight,	WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	CALLBACK_ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_editable_highlight_create");
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_create", WatchfaceComplicationGetError(nRet));
	CALLBACK_CHECK_HANDLE_EXIT_CLEANUP(hHighlight, "watchface_complication_create", watchface_editable_highlight_destroy(hHighlight));

	nRet = watchface_editable_highlight_set_geometry(hHighlight, GEO_X, GEO_Y, GEO_W, GEO_H);
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_set_geometry", WatchfaceComplicationGetError(nRet), watchface_editable_highlight_destroy(hHighlight));

	nRet = watchface_complication_create(1, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT, WATCHFACE_COMPLICATION_EVENT_TAP, &hHandle);
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet), watchface_editable_highlight_destroy(hHighlight));
	CALLBACK_CHECK_HANDLE_EXIT_CLEANUP(hHandle, "watchface_complication_create", watchface_editable_highlight_destroy(hHighlight));

	nRet = watchface_editable_add_complication(hEdCon, pszEditorAppid, hHandle, hHighlight);
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_add_complication", WatchfaceComplicationGetError(nRet), watchface_editable_highlight_destroy(hHighlight);watchface_complication_destroy(hHandle));

	nRet = watchface_editable_request_edit(hEdCon, RequestEditWithComplicationCb, g_pszCheckUserData);
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_request_edit", WatchfaceComplicationGetError(nRet), watchface_editable_highlight_destroy(hHighlight);watchface_complication_destroy(hHandle));

	watchface_editable_highlight_destroy(hHighlight);
	watchface_complication_destroy(hHandle);
	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		GetNthUpdateRequestedCb
* @description	 	Callback Function
* @parameters		hHandle, nSelectedIdx, eState, pszUserData
* @return 		NA
*/
static void GetNthUpdateRequestedCb(const watchface_editable_h hHandle, int nSelectedIdx, const watchface_editable_edit_state_e eState, void *pszUserData)
{
	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "GetNthUpdateRequestedCb");
	int nRet;
	int n = 0;
	bundle *pszNthData = NULL;

	nRet = watchface_editable_get_nth_data(hHandle, n, &pszNthData);
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_get_nth_data", WatchfaceComplicationGetError(nRet));
	CALLBACK_CHECK_HANDLE_EXIT(pszNthData, "watchface_editable_get_nth_data");
	bundle_free(pszNthData);
	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		GetNthOnEditReadyCb
* @description	 	Callback Function
* @parameters		hEdCon, pszEditorAppid, pszUserData
* @return 		NA
*/
static void GetNthOnEditReadyCb(watchface_editable_container_h hEdCon, const char *pszEditorAppid, void *pszUserData)
{
	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "GetNthOnEditReadyCb");
	int nRet = RequestEditWithDesignElements(hEdCon, GetNthUpdateRequestedCb);
	if(g_bFeatureNotSupported || g_bIsFeatureMismatched)
		return;
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "RequestEditWithDesignElements", WatchfaceComplicationGetError(nRet));
	return;
}

/**
* @function 		UpdateRequestedCb
* @description	 	Callback Function
* @parameters		hHandle, nSelectedIdx, eState, pszUserData
* @return 		NA
*/
static void UpdateRequestedCb(const watchface_editable_h hHandle,int nSelectedIdx,const watchface_editable_edit_state_e eState,void *pszUserData)
{
	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "UpdateRequestedCb");
	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		DesignElementOnEditReadyCb
* @description	 	Callback Function
* @parameters		hEdCon, pszEditorAppid, pszUserData
* @return 		NA
*/
static void DesignElementOnEditReadyCb(watchface_editable_container_h hEdCon,const char *pszEditorAppId,void *pszUserData)
{
	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "DesignElementOnEditReadyCb");
	int nRet;
	nRet = RequestEditWithDesignElements(hEdCon, UpdateRequestedCb);
	if(g_bFeatureNotSupported || g_bIsFeatureMismatched)
		return;
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "RequestEditWithDesignElements", WatchfaceComplicationGetError(nRet));
	g_bCallBackHit = true;
	return;
}

/**
* @function 		RequestEditOnEditReadyCb
* @description	 	Callback Function
* @parameters		hEdCon, pszEditorAppid, pszUserData
* @return 		NA
*/
static void RequestEditOnEditReadyCb(watchface_editable_container_h hEdCon,const char *pszEditorAppid,void *pszUserData)
{
	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "RequestEditOnEditReadyCb");
	int nRet;
	complication_h hHandle;
	watchface_editable_highlight_h hHighlight;

	nRet = watchface_editable_highlight_create(&hHighlight,WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	CALLBACK_ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_editable_highlight_create");
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_create", WatchfaceComplicationGetError(nRet));
	CALLBACK_CHECK_HANDLE_EXIT(hHighlight, "watchface_editable_highlight_create");

	nRet = watchface_editable_highlight_set_geometry(hHighlight, GEO_X, GEO_Y, GEO_W, GEO_H);
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_set_geometry", WatchfaceComplicationGetError(nRet), watchface_editable_highlight_destroy(hHighlight));

	nRet = watchface_complication_create(0, "org.tizen.sample_provider", WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT, WATCHFACE_COMPLICATION_EVENT_TAP, &hHandle);
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet), watchface_editable_highlight_destroy(hHighlight));
	CALLBACK_CHECK_HANDLE_EXIT_CLEANUP(hHandle, "watchface_complication_create", watchface_editable_highlight_destroy(hHighlight));

	nRet = watchface_editable_add_complication(hEdCon, 0, hHandle, hHighlight);
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_add_complication", WatchfaceComplicationGetError(nRet), watchface_editable_highlight_destroy(hHighlight);watchface_complication_destroy(hHandle));

	nRet = watchface_editable_request_edit(hEdCon, UpdateRequestedCb, NULL);
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_request_edit", WatchfaceComplicationGetError(nRet), watchface_editable_highlight_destroy(hHighlight);watchface_complication_destroy(hHandle));

	watchface_editable_highlight_destroy(hHighlight);
	watchface_complication_destroy(hHandle);
	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		WatchfaceEditableEditReadyCb
* @description	 	Callback Function
* @parameters		hEdCon, pszEditorAppid, pszUserData
* @return 		NA
*/
static void WatchfaceEditableEditReadyCb(watchface_editable_container_h hEdCon, const char *pszEditorAppid, void *pszUserData)
{
	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "WatchfaceEditableEditReadyCb");
	g_bCallBackHit = true;
	return;
}

/**
* @function 		GetCurDataUpdateRequestedCb
* @description	 	Callback Function
* @parameters		hHandle, nSelectedIdx, eState, pszUserData
* @return 		NA
*/
static void GetCurDataUpdateRequestedCb(const watchface_editable_h hHandle, int nSelectedIdx, const watchface_editable_edit_state_e eState, void *pszUserData) {

	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "GetCurDataUpdateRequestedCb");
	bundle *pszCurrData = NULL;

	int nRet = watchface_editable_get_current_data(hHandle, &pszCurrData);
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_get_current_data", WatchfaceComplicationGetError(nRet));
	CALLBACK_CHECK_HANDLE_EXIT(pszCurrData, "watchface_editable_get_current_data");

	bundle_free(pszCurrData);
	g_bCallBackHit = true;
	return;
}

/**
* @function 		GetCurDataOnEditReadyCb
* @description	 	Callback Function
* @parameters		hEdCon, pszEditorAppid, pszUserData
* @return 		NA
*/
static void GetCurDataOnEditReadyCb(watchface_editable_container_h hEdCon, const char *pszEditorAppid, void *pszUserData) {

	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "GetCurDataOnEditReadyCb");
	int nRet = RequestEditWithDesignElements(hEdCon, GetCurDataUpdateRequestedCb);
	if(g_bFeatureNotSupported || g_bIsFeatureMismatched)
		return;
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "RequestEditWithDesignElements", WatchfaceComplicationGetError(nRet));
	g_bCallBackHit = true;
	return;
}

/**
* @function 		GetCurDataIdxUpdateRequestedCb
* @description	 	Callback Function
* @parameters		hHandle, nSelectedIdx, eState, pszUserData
* @return 		NA
*/
static void GetCurDataIdxUpdateRequestedCb(const watchface_editable_h hHandle, int nSelectedIdx, const watchface_editable_edit_state_e eState, void *pszUserData)
{
	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "GetCurDataIdxUpdateRequestedCb");
	int nRet;
	int nIdx = -1;

	nRet = watchface_editable_get_current_data_idx(hHandle, &nIdx);
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_get_current_data_idx", WatchfaceComplicationGetError(nRet));
	if(nIdx < 0)
	{
		FPRINTF("[Line : %d][%s] %s failed. nIdx = %d\\n", __LINE__, API_NAMESPACE, "watchface_editable_get_current_data_idx", nIdx);
		QuitGmainLoop();
		return;
	}

	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		GetCurDataIdxOnEditReadyCb
* @description	 	Callback Function
* @parameters		hEdCon, pszEditorAppid, pszUserData
* @return 		NA
*/
static void GetCurDataIdxOnEditReadyCb(watchface_editable_container_h hEdCon, const char *pszEditorAppid, void *pszUserData) {

	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "GetCurDataIdxOnEditReadyCb");
	int nRet = RequestEditWithDesignElements(hEdCon, GetCurDataIdxUpdateRequestedCb);
	if(g_bFeatureNotSupported || g_bIsFeatureMismatched)
		return;
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "RequestEditWithDesignElements", WatchfaceComplicationGetError(nRet));
	return;
}

/**
* @function 		GetEditableIdUpdateRequestedCb
* @description	 	Callback Function
* @parameters		hHandle, nSelectedIdx, eState, pszUserData
* @return 		NA
*/
static void GetEditableIdUpdateRequestedCb(const watchface_editable_h hHandle, int nSelectedIdx, const watchface_editable_edit_state_e eState, void *pszUserData){

	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "GetEditableIdUpdateRequestedCb");
	int nEditableId = -1;
	int nRet = watchface_editable_get_editable_id(hHandle, &nEditableId);
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_get_editable_id", WatchfaceComplicationGetError(nRet));
	if(nEditableId < 0)
	{
		FPRINTF("[Line : %d][%s] %s failed. nEditableId = %d\\n", __LINE__, API_NAMESPACE, "watchface_editable_get_editable_id", nEditableId);
		QuitGmainLoop();
		return;
	}
	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		GetEditableIdOnEditReadyCb
* @description	 	Callback Function
* @parameters		hEdCon, pszEditorAppid, pszUserData
* @return 		NA
*/
static void GetEditableIdOnEditReadyCb(watchface_editable_container_h hEdCon, const char *pszEditorAppid, void *pszUserData) {

	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "GetEditableIdOnEditReadyCb");
	int nRet = RequestEditWithDesignElements(hEdCon, GetEditableIdUpdateRequestedCb);
	if(g_bFeatureNotSupported || g_bIsFeatureMismatched)
		return;
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "RequestEditWithDesignElements", WatchfaceComplicationGetError(nRet));
	return;
}

/**
* @function 		LoadCurrentDataUpdateRequestedCb
* @description	 	Callback Function
* @parameters		hHandle, nSelectedIdx, eState, pszUserData
* @return 		NA
*/
static void LoadCurrentDataUpdateRequestedCb(const watchface_editable_h hHandle,int nSelectedIdx,const watchface_editable_edit_state_e eState,void *pszUserData)
{
	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "LoadCurrentDataUpdateRequestedCb");
	int nEditableId = -1;
	int nRet;
	bundle *pszCurrentData = NULL;

	if(eState == WATCHFACE_EDITABLE_EDIT_STATE_COMPLETE){
		nRet = watchface_editable_get_editable_id(hHandle, &nEditableId);
		CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_get_editable_id", WatchfaceComplicationGetError(nRet));
		if(nEditableId < 0)
		{
			FPRINTF("[Line : %d][%s] %s failed. nEditableId = %d\\n", __LINE__, API_NAMESPACE, "watchface_editable_get_editable_id", nEditableId);
			QuitGmainLoop();
			return;
		}
		nRet = watchface_editable_load_current_data(nEditableId, &pszCurrentData);
		CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_load_current_data", WatchfaceComplicationGetError(nRet));
		CALLBACK_CHECK_HANDLE_EXIT(pszCurrentData, "watchface_editable_load_current_data");
		FREE_MEMORY(pszCurrentData);
		g_bCallBackHit = true;
		QuitGmainLoop();
	}
	return;
}

/**
* @function 		LoadCurrentDataOnEditReadyCb
* @description	 	Callback Function
* @parameters		hEdCon, pszEditorAppid, pszUserData
* @return 		NA
*/
static void LoadCurrentDataOnEditReadyCb(watchface_editable_container_h hEdCon,const char *pszEditorAppid,void *pszUserData)	{

	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "LoadCurrentDataOnEditReadyCb");
	int nRet = RequestEditWithDesignElements(hEdCon, LoadCurrentDataUpdateRequestedCb);
	if(g_bFeatureNotSupported || g_bIsFeatureMismatched)
		return;
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "RequestEditWithDesignElements", WatchfaceComplicationGetError(nRet));
	return;
}

/**
* @function 		EditableSetNameUpdateRequestedCb
* @description	 	Callback Function
* @parameters		hHandle, nSelectedIdx, eState, pszUserData
* @return 		NA
*/
static void EditableSetNameUpdateRequestedCb(const watchface_editable_h hHandle,int nSelectedIdx,const watchface_editable_edit_state_e eState,void *pszUserData)
{
	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "EditableSetNameUpdateRequestedCb");
	int nRet = watchface_editable_set_editable_name(hHandle, pszEditableSetName);
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_set_editable_name", WatchfaceComplicationGetError(nRet));
	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		EditableSetNameOnEditReadyCb
* @description	 	Callback Function
* @parameters		hEdCon, pszEditorAppid, pszUserData
* @return 		NA
*/
static void EditableSetNameOnEditReadyCb(watchface_editable_container_h hEdCon,const char *pszEditorAppid,void *pszUserData)	{

	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "EditableSetNameOnEditReadyCb");
	int nRet = RequestEditWithDesignElements(hEdCon, EditableSetNameUpdateRequestedCb);
	if(g_bFeatureNotSupported || g_bIsFeatureMismatched)
		return;
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "RequestEditWithDesignElements", WatchfaceComplicationGetError(nRet));
	return;
}

/**
* @function 		EditableGetNameUpdateRequestedCb
* @description	 	Callback Function
* @parameters		hHandle, nSelectedIdx, eState, pszUserData
* @return 		NA
*/
static void EditableGetNameUpdateRequestedCb(const watchface_editable_h hHandle,int nSelectedIdx,const watchface_editable_edit_state_e eState,void *pszUserData)	{

	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "EditableGetNameUpdateRequestedCb");
	int nRet = watchface_editable_set_editable_name(hHandle, pszEditableSetName);
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_set_editable_name", WatchfaceComplicationGetError(nRet));

	nRet = watchface_editable_get_editable_name(hHandle, &g_pszEditableGetName);
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_get_editable_name", WatchfaceComplicationGetError(nRet));
	CALLBACK_CHECK_HANDLE_EXIT(g_pszEditableGetName, "watchface_editable_get_editable_name");

	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		EditableGetNameOnEditReadyCb
* @description	 	Callback Function
* @parameters		hEdCon, pszEditorAppid, pszUserData
* @return 		NA
*/
static void EditableGetNameOnEditReadyCb(watchface_editable_container_h hEdCon,const char *pszEditorAppid,void *pszUserData)	{

	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "EditableGetNameOnEditReadyCb");
	int nRet = RequestEditWithDesignElements(hEdCon, EditableGetNameUpdateRequestedCb);
	if(g_bFeatureNotSupported || g_bIsFeatureMismatched)
		return;
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "RequestEditWithDesignElements", WatchfaceComplicationGetError(nRet));
	return;
}

/**
* @function 		GetHighlightUpdateRequestedCb
* @description	 	Callback Function
* @parameters		hHandle, nSelectedIdx, eState, pszUserData
* @return 		NA
*/
static void GetHighlightUpdateRequestedCb(const watchface_editable_h hHandle, int nSelectedIdx, const watchface_editable_edit_state_e eState, void *pszUserData)	{

	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "GetHighlightUpdateRequestedCb");
	watchface_editable_highlight_h highlight;
	int nX;
	int nY;
	int nW;
	int nH;

	int nRet = watchface_editable_get_highlight(hHandle, &highlight);
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_get_highlight", WatchfaceComplicationGetError(nRet));
	CALLBACK_CHECK_HANDLE_EXIT(highlight, "watchface_editable_get_highlight");

	nRet = watchface_editable_highlight_get_geometry(highlight, &nX, &nY, &nW, &nH);
	CALLBACK_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_get_geometry", WatchfaceComplicationGetError(nRet), watchface_editable_highlight_destroy(highlight));

	if( nX != GEO_X || nY != GEO_Y || nW != GEO_W || nH != GEO_H)
	{
		FPRINTF("[Line : %d][%s] %s failed. \\nnX = %d\\nnY = %d\\nnW = %d\\nnH = %d\\n", __LINE__, API_NAMESPACE, 				"watchface_editable_highlight_get_geometry", nX, nY, nH, nW);
		watchface_editable_highlight_destroy(highlight);
		QuitGmainLoop();
		return;
	}

	watchface_editable_highlight_destroy(highlight);
	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		GetHighlightOnEditReadyCb
* @description	 	Callback Function
* @parameters		hEdCon, pszEditorAppid, pszUserData
* @return 		NA
*/
static void GetHighlightOnEditReadyCb(watchface_editable_container_h hEdCon, const char *pszEditorAppid, void *pszUserData)
{
	FPRINTF("[Line : %d][%s] entered %s.\\n", __LINE__, API_NAMESPACE, "GetHighlightOnEditReadyCb");
	int nRet = RequestEditWithDesignElements(hEdCon, GetHighlightUpdateRequestedCb);
	if(g_bFeatureNotSupported || g_bIsFeatureMismatched)
		return;
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "RequestEditWithDesignElements", WatchfaceComplicationGetError(nRet));
	return;
}

/*****************************************************Callback End*****************************************************/

//& purpose: To create candidate list and adds candidate data to the candidate list and destroy candidates list
//& type: auto
/**
* @testcase				ITc_watchface_editable_candidates_list_create_add_destroy_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Creates candidates list, Adds candidate data to the candidates list and Destroys candidates list.
* @scenario				Creates candidates list, Adds candidate data to the candidates list and Destroys candidates list.
* @apicovered				watchface_editable_candidates_list_create, watchface_editable_candidates_list_add, 						watchface_editable_candidates_list_destroy
* @passcase				Target APIs return 0
* @failcase				Target APIs return 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_editable_candidates_list_create_add_destroy_p(void)
{
	START_TEST;
	complication_candidates_list_h hHandle = NULL;
	bundle *pszCandidate = NULL;

	int nRet = watchface_editable_candidates_list_create(&hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_editable_candidates_list_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_candidates_list_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_editable_candidates_list_create");

	pszCandidate = bundle_create();
	nRet = get_last_result();
	PRINT_RESULT_EXIT_CLEANUP(nRet, BUNDLE_ERROR_NONE, "bundle_create", BundleGetError(nRet), watchface_editable_candidates_list_destroy(hHandle));
	CHECK_HANDLE_EXIT_CLEANUP(pszCandidate, "bundle_create", watchface_editable_candidates_list_destroy(hHandle));
	bundle_add_str(pszCandidate, "COLOR", "RED");
	nRet = watchface_editable_candidates_list_add(hHandle, pszCandidate);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_candidates_list_add", WatchfaceComplicationGetError(nRet), watchface_editable_candidates_list_destroy(hHandle));
	CHECK_HANDLE_EXIT_CLEANUP(pszCandidate, "watchface_editable_candidates_list_add", watchface_editable_candidates_list_destroy(hHandle));
	bundle_free(pszCandidate);

	nRet = watchface_editable_candidates_list_destroy(hHandle);
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_candidates_list_destroy", WatchfaceComplicationGetError(nRet));

	service_app_exit();
	return 0;
}

//& purpose: To add complication to editable container
//& type: auto
/**
* @testcase				ITc_watchface_editable_add_complication_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Adds complication to editable container.
* @scenario				Adds complication to editable container.
* @apicovered				watchface_editable_highlight_create, watchface_editable_highlight_set_geometry, watchface_complication_create, 						watchface_editable_add_complication, watchface_editable_request_edit
* @passcase				Target APIs return 0
* @failcase				Target APIs return 1
* @precondition				Editable handle should be created by watchface_editable_highlight_create().
* @postcondition			N/A
* */
int ITc_watchface_editable_add_complication_p(void)
{
	START_TEST;
	int nRet = watchface_editable_add_edit_ready_cb(AddComplicationOnEditReadyCb, g_pszCheckUserData);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_add_edit_ready_cb", WatchfaceComplicationGetError(nRet));

	g_bCallBackHit = false;
	RunEditorApp();
	IterateGmainLoop();

	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "RequestEditWithComplicationCb");
		nRet = watchface_editable_remove_edit_ready_cb(AddComplicationOnEditReadyCb);
		PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
		return 1;
	}
	nRet = watchface_editable_remove_edit_ready_cb(AddComplicationOnEditReadyCb);
	PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
	service_app_exit();
	return 0;
}

//& purpose: To get the nth data of the editable
//& type: auto
/**
* @testcase				ITc_watchface_editable_get_nth_data_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets the nth data of the editable.
* @scenario				Gets the nth data of the editable.
* @apicovered				watchface_editable_get_nth_data
* @passcase				watchface_editable_get_nth_data returns 0
* @failcase				watchface_editable_get_nth_data returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_editable_get_nth_data_p(void)
{
	START_TEST;
	int nRet = 0;
	g_bCallBackHit = false;
	nRet = watchface_editable_add_edit_ready_cb(GetNthOnEditReadyCb, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_add_edit_ready_cb", WatchfaceComplicationGetError(nRet));

	RunEditorApp();
	IterateGmainLoop();

	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "GetNthUpdateRequestedCb");
		nRet = watchface_editable_remove_edit_ready_cb(GetNthOnEditReadyCb);
		PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
		return 1;
	}
	nRet = watchface_editable_remove_edit_ready_cb(GetNthOnEditReadyCb);
	PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
	service_app_exit();
	return 0;
}

//& purpose: To add the design element to the editable container handle
//& type: auto
/**
* @testcase				ITc_watchface_editable_add_design_element_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Adds the design element to the editable container handle.
* @scenario				Adds the design element to the editable container handle.
* @apicovered				watchface_editable_add_design_element
* @passcase				returns 0
* @failcase				returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_editable_add_design_element_p(void)
{
	START_TEST;
	g_bCallBackHit = false;
	int nRet = watchface_editable_add_edit_ready_cb(DesignElementOnEditReadyCb, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_add_edit_ready_cb", WatchfaceComplicationGetError(nRet));

	RunEditorApp();
	IterateGmainLoop();

	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "UpdateRequestedCb");
		nRet = watchface_editable_remove_edit_ready_cb(DesignElementOnEditReadyCb);
		PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}
	nRet = watchface_editable_remove_edit_ready_cb(DesignElementOnEditReadyCb);
	PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
	service_app_exit();
	return 0;
}

//& purpose: To request editor to edit
//& type: auto
/**
* @testcase				ITc_watchface_editable_request_edit_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Requests editor to edit.
* @scenario				Requests editor to edit.
* @apicovered				watchface_editable_request_edit
* @passcase				Target APIs return 0
* @failcase				Target APIs return 1
* @precondition				Editable handle should be created by watchface_editable_highlight_create().
* @postcondition			N/A
* */
int ITc_watchface_editable_request_edit_p(void)
{
	START_TEST;
	int nRet = watchface_editable_add_edit_ready_cb(RequestEditOnEditReadyCb, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_add_edit_ready_cb", WatchfaceComplicationGetError(nRet));

	RunEditorApp();
	IterateGmainLoop();

	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "UpdateRequestedCb");
		nRet = watchface_editable_remove_edit_ready_cb(DesignElementOnEditReadyCb);
		PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}
	nRet = watchface_editable_remove_edit_ready_cb(RequestEditOnEditReadyCb);
	PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
	return 0;
}

//& purpose: To add and remove the callback function to request edit
//& type: auto
/**
* @testcase				ITc_watchface_editable_add_remove_edit_ready_cb_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Adds and removes the callback function to request edit.
* @scenario				Adds and removes the callback function to request edit.
* @apicovered				watchface_editable_add_edit_ready_cb,  watchface_editable_remove_edit_ready_cb
* @passcase				Target APIs return 0
* @failcase				target APIs return 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_editable_add_remove_edit_ready_cb_p(void)
{
	START_TEST;
	g_bCallBackHit = false;
	int nRet = watchface_editable_add_edit_ready_cb(WatchfaceEditableEditReadyCb, NULL);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_editable_add_edit_ready_cb");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_add_edit_ready_cb", WatchfaceComplicationGetError(nRet));
	RunEditorApp();
	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "WatchfaceEditableEditReadyCb");
		nRet = watchface_editable_remove_edit_ready_cb(WatchfaceEditableEditReadyCb);
		PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}
	nRet = watchface_editable_remove_edit_ready_cb(WatchfaceEditableEditReadyCb);
	PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
	service_app_exit();
	return 0;
}

//& purpose: To get the current data in editable
//& type: auto
/**
* @testcase				ITc_watchface_editable_get_current_data_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets the current data in editable.
* @scenario				Gets the current data in editable.
* @apicovered				watchface_editable_get_current_data
* @passcase				watchface_editable_get_current_data returns 0
* @failcase				watchface_editable_get_current_data returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_editable_get_current_data_p(void)
{
	START_TEST;
	watchface_editable_h hHandle = NULL;
	g_bCallBackHit = false;

	int nRet = watchface_editable_add_edit_ready_cb(GetCurDataOnEditReadyCb, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_add_edit_ready_cb", WatchfaceComplicationGetError(nRet));

	RunEditorApp();
	IterateGmainLoop();

	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "GetCurDataUpdateRequestedCb");
		nRet = watchface_editable_remove_edit_ready_cb(GetCurDataOnEditReadyCb);
		PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}
	nRet = watchface_editable_remove_edit_ready_cb(GetCurDataOnEditReadyCb);
	PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
	service_app_exit();
	return 0;
}

//& purpose: To get the index of current data
//& type: auto
/**
* @testcase				ITc_watchface_editable_get_current_data_idx_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets the index of current data.
* @scenario				Gets the index of current data.
* @apicovered				watchface_editable_get_current_data_idx
* @passcase				watchface_editable_get_current_data_idx returns 0
* @failcase				watchface_editable_get_current_data_idx returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_editable_get_current_data_idx_p(void)
{
	START_TEST;
	watchface_editable_h hHandle = NULL;
	g_bCallBackHit = false;

	int nRet = watchface_editable_add_edit_ready_cb(GetCurDataIdxOnEditReadyCb, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_add_edit_ready_cb", WatchfaceComplicationGetError(nRet));

	RunEditorApp();
	IterateGmainLoop();

	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "GetCurDataIdxUpdateRequestedCb");
		nRet = watchface_editable_remove_edit_ready_cb(GetCurDataIdxOnEditReadyCb);
		PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}
	nRet = watchface_editable_remove_edit_ready_cb(GetCurDataIdxOnEditReadyCb);
	PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
	service_app_exit();
	return 0;
}

//& purpose: To get the id of editable
//& type: auto
/**
* @testcase				ITc_watchface_editable_get_editable_id_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets the id of editable.
* @scenario				Gets the id of editable.
* @apicovered				watchface_editable_get_editable_id
* @passcase				watchface_editable_get_editable_id returns 0
* @failcase				watchface_editable_get_editable_id returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_editable_get_editable_id_p(void)
{
	START_TEST;
	watchface_editable_h hHandle = NULL;
	g_bCallBackHit = false;

	int nRet = watchface_editable_add_edit_ready_cb(GetEditableIdOnEditReadyCb, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_add_edit_ready_cb", WatchfaceComplicationGetError(nRet));

	RunEditorApp();
	IterateGmainLoop();

	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "GetEditableIdUpdateRequestedCb");
		nRet = watchface_editable_remove_edit_ready_cb(GetEditableIdOnEditReadyCb);
		PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}
	nRet = watchface_editable_remove_edit_ready_cb(GetEditableIdOnEditReadyCb);
	PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
	service_app_exit();
	return 0;
}

//& purpose: To get the editable information of the specified Id
//& type: auto
/**
* @testcase				ITc_watchface_editable_load_current_data_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets the editable information of the specified Id.
* @scenario				Gets the editable information of the specified Id.
* @apicovered				watchface_editable_get_editable_id, watchface_editable_load_current_data
* @passcase				Target APIs return 0
* @failcase				Target APIs return 1
* @precondition				Get specified Id by watchface_editable_get_editable_id()
* @postcondition			N/A
* */
int ITc_watchface_editable_load_current_data_p(void)
{
	START_TEST;
	g_bCallBackHit = false;
	int nRet = watchface_editable_add_edit_ready_cb(LoadCurrentDataOnEditReadyCb, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_add_edit_ready_cb", WatchfaceComplicationGetError(nRet));

	RunEditorApp();
	IterateGmainLoop();

	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "LoadCurrentDataUpdateRequestedCb");
		nRet = watchface_editable_remove_edit_ready_cb(LoadCurrentDataOnEditReadyCb);
		PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}

	nRet = watchface_editable_remove_edit_ready_cb(LoadCurrentDataOnEditReadyCb);
	PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
	service_app_exit();
	return 0;
}

//& purpose: To set the name in editable
//& type: auto
/**
* @testcase				ITc_watchface_editable_set_editable_name_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Sets the name in editable.
* @scenario				Sets the name in editable.
* @apicovered				watchface_editable_set_editable_name
* @passcase				watchface_editable_set_editable_name returns 0
* @failcase				watchface_editable_set_editable_name returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_editable_set_editable_name_p(void)
{
	START_TEST;
	int nRet = 0;
	g_bCallBackHit = false;
	nRet = watchface_editable_add_edit_ready_cb(EditableSetNameOnEditReadyCb, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_add_edit_ready_cb", WatchfaceComplicationGetError(nRet));

	RunEditorApp();
	IterateGmainLoop();

	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "EditableSetNameUpdateRequestedCb");
		nRet = watchface_editable_remove_edit_ready_cb(EditableSetNameOnEditReadyCb);
		PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}
	nRet = watchface_editable_remove_edit_ready_cb(EditableSetNameOnEditReadyCb);
	PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
	service_app_exit();
	return 0;
}

//& purpose: To get the name of editable
//& type: auto
/**
* @testcase				ITc_watchface_editable_get_editable_name_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets the id of editable.
* @scenario				Gets the id of editable.
* @apicovered				watchface_editable_set_editable_name,watchface_editable_get_editable_name
* @passcase				Target APIs return 0
* @failcase				Target APIs return 1
* @precondition				Set Id by watchface_editable_set_editable_name()
* @postcondition			N/A
* */
int ITc_watchface_editable_get_editable_name_p(void)
{
	START_TEST;
	int nRet;
	g_bCallBackHit = false;

	nRet = watchface_editable_add_edit_ready_cb(EditableGetNameOnEditReadyCb, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_add_edit_ready_cb", WatchfaceComplicationGetError(nRet));

	RunEditorApp();
	IterateGmainLoop();

	if(strncmp(g_pszEditableGetName, pszEditableSetName, strlen(pszEditableSetName))!= 0)
	{
		FPRINTF("[Line : %d][%s] %s failed. g_pszEditableGetName = %s\\n", __LINE__, API_NAMESPACE, "watchface_editable_get_editable_name", g_pszEditableGetName);
		nRet = watchface_editable_remove_edit_ready_cb(EditableGetNameOnEditReadyCb);
		PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}
	FREE_MEMORY(g_pszEditableGetName);

	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "EditableGetNameUpdateRequestedCb");
		nRet = watchface_editable_remove_edit_ready_cb(EditableGetNameOnEditReadyCb);
		PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}

	nRet = watchface_editable_remove_edit_ready_cb(EditableGetNameOnEditReadyCb);
	PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
	service_app_exit();
	return 0;
}

//& purpose: To get editable's highlight handle
//& type: auto
/**
* @testcase				ITc_watchface_editable_get_highlight_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets editable's highlight handle.
* @scenario				Gets editable's highlight handle.
* @apicovered				watchface_editable_get_highlight, watchface_editable_highlight_get_geometry
* @passcase				Target APIs return 0
* @failcase				Target APIs return 1
* @precondition				Gets highlight by watchface_editable_get_highlight()
* @postcondition			N/A
* */
int ITc_watchface_editable_get_highlight_p(void)
{
	START_TEST;
	int nRet = watchface_editable_add_edit_ready_cb(GetHighlightOnEditReadyCb, NULL);
	if(g_bFeatureNotSupported)
		return 0;
	if(g_bIsFeatureMismatched)
		return 1;
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_add_edit_ready_cb", WatchfaceComplicationGetError(nRet));

	g_bCallBackHit = false;
	RunEditorApp();
	IterateGmainLoop();

	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "GetHighlightUpdateRequestedCb");
		nRet = watchface_editable_remove_edit_ready_cb(GetHighlightOnEditReadyCb);
		PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}

	nRet = watchface_editable_remove_edit_ready_cb(GetHighlightOnEditReadyCb);
	PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_remove_edit_ready_cb", WatchfaceComplicationGetError(nRet));
	service_app_exit();
	return 0;
}

//& purpose: To set and get editable's highlight geometry info
//& type: auto
/**
* @testcase				ITc_watchface_editable_set_get_geometry_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Sets and gets editable's highlight geometry info.
* @scenario				Sets and gets editable's highlight geometry info.
* @apicovered				watchface_editable_highlight_set_geometry, watchface_editable_highlight_get_geometry
* @passcase				Target APIs return 0
* @failcase				Target APIs return 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_editable_set_get_geometry_p(void)
{
	START_TEST;
	int nRet = 0;
	int nX;
	int nY;
	int nW;
	int nH;
	watchface_editable_highlight_h hHandle;

	nRet = watchface_editable_highlight_create(&hHandle, WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_editable_highlight_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_editable_highlight_create");

	nRet = watchface_editable_highlight_set_geometry(hHandle, GEO_X, GEO_Y, GEO_W, GEO_H);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_set_geometry", WatchfaceComplicationGetError(nRet), watchface_editable_highlight_destroy(hHandle));

	nRet = watchface_editable_highlight_get_geometry(hHandle, &nX, &nY, &nW, &nH);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_get_geometry", WatchfaceComplicationGetError(nRet), watchface_editable_highlight_destroy(hHandle));

	if( nX != GEO_X || nY != GEO_Y || nW != GEO_W || nH != GEO_H)
	{
		FPRINTF("[Line : %d][%s] %s failed. \\nnX = %d\\nnY = %d\\nnW = %d\\nnH = %d\\n", __LINE__, API_NAMESPACE, "watchface_editable_highlight_get_geometry", nX, nY, nH, nW);
		nRet = watchface_editable_highlight_destroy(hHandle);
		PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_destroy", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}

	nRet = watchface_editable_highlight_destroy(hHandle);
	PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_destroy", WatchfaceComplicationGetError(nRet));
	service_app_exit();
	return 0;
}

//& purpose: To set and get editable's highlight shape type
//& type: auto
/**
* @testcase				ITc_watchface_editable_highlight_set_get_shape_type_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Sets and Gets editable's highlight shape type.
* @scenario				Sets and Gets editable's highlight shape type.
* @apicovered				watchface_editable_highlight_set_shape_type, watchface_editable_highlight_get_shape_type
* @passcase				Target APIs return 0
* @failcase				Target APIs return 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_editable_highlight_set_get_shape_type_p(void)
{
	START_TEST;
	int nRet;
	watchface_editable_highlight_h hHandle;
	watchface_editable_shape_type_e eShape;

	nRet = watchface_editable_highlight_create(&hHandle, WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_editable_highlight_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_create", WatchfaceComplicationGetError(nRet));

	nRet = watchface_editable_highlight_set_shape_type(hHandle, WATCHFACE_EDITABLE_SHAPE_TYPE_RECT);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_set_shape_type", WatchfaceComplicationGetError(nRet), watchface_editable_highlight_destroy(hHandle));

	nRet = watchface_editable_highlight_get_shape_type(hHandle, &eShape);
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_get_shape_type", WatchfaceComplicationGetError(nRet));

	if(eShape != WATCHFACE_EDITABLE_SHAPE_TYPE_RECT)
	{
		FPRINTF("[Line : %d][%s] %s failed. eShape = %d\\n", __LINE__, API_NAMESPACE, "watchface_editable_highlight_get_geometry", eShape);
		nRet = watchface_editable_highlight_destroy(hHandle);
		PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_destroy", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}

	nRet = watchface_editable_highlight_destroy(hHandle);
	PRINT_RESULT_EXIT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_destroy", WatchfaceComplicationGetError(nRet));
	service_app_exit();
	return 0;
}

//& purpose: To create and destroy editables highlight
//& type: auto
/**
* @testcase				ITc_watchface_editable_highlight_create_destroy_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Creates and destroys editables highlight
* @scenario				Creates and destroys editables highlight
* @apicovered				watchface_editable_highlight_create, watchface_editable_highlight_destroy
* @passcase				Target APIs return 0
* @failcase				Target APIs return 1
* @precondition				N/A
* @postcondition			N/A;
* */
int ITc_watchface_editable_highlight_create_destroy_p(void)
{
	START_TEST;
	int nRet;
	watchface_editable_highlight_h hHandle;
	nRet = watchface_editable_highlight_create(&hHandle, WATCHFACE_EDITABLE_SHAPE_TYPE_CIRCLE);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_editable_highlight_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_editable_highlight_create");

	nRet = watchface_editable_highlight_destroy(hHandle);
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_editable_highlight_destroy", WatchfaceComplicationGetError(nRet));
	service_app_exit();
	return 0;
}

