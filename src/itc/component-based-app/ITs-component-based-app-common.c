//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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

#include "ITs-component-based-app-common.h"

/** @addtogroup itc-component-based-app
* @ingroup		itc
* @{
*/

/**
* @function		AppControlSend
* @description		Helper function, to create multilang handle.
* @parameter  		const char *pszAppID, const char *pszCompID, const char *pszExtraData
* @return		nRet, API result value.
*/
int AppControlSend(const char *pszAppID, const char *pszCompID, const char *pszExtraData)
{
	app_control_h hAppCtrl = NULL;
	app_control_h hReplyAppCtrl = NULL;
	app_control_result_e eAppCtrlResult = APP_CONTROL_RESULT_FAILED;
	int nRet;

	nRet = app_control_create(&hAppCtrl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));
	CHECK_HANDLE(hAppCtrl, "app_control_create");

	nRet = app_control_set_app_id(hAppCtrl, TEST_COMPONENTBASED_APPID);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppCtrl));

	if(pszCompID)
	{
		nRet = app_control_set_component_id(hAppCtrl, pszCompID);
		PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_component_id", AppControlGetError(nRet), app_control_destroy(hAppCtrl));
	}

	nRet = app_control_add_extra_data(hAppCtrl, TEST_COMP_EXTRA_KEY, pszExtraData);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_add_extra_data", AppControlGetError(nRet), app_control_destroy(hAppCtrl));

	nRet = app_control_send_launch_request_sync(hAppCtrl, &hReplyAppCtrl, &eAppCtrlResult);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_send_launch_request_sync", AppControlGetError(nRet), app_control_destroy(hAppCtrl));
	CHECK_HANDLE_CLEANUP(hReplyAppCtrl, "app_control_send_launch_request_sync", app_control_destroy(hAppCtrl));

	return eAppCtrlResult;
}

/**
* @function 		ResultCallBack
* @description	 	Callback Function
* @parameters		app_control_h hAppCtrl, app_control_error_e eErrorResult, void *pszData
* @return 		N/A
*/
static void ResultCallBack(app_control_h hAppCtrl, app_control_error_e eErrorResult, void *pszData)
{
	FPRINTF("[Line : %d][%s] ResultCallBack invoked \\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ReplyCallBack
* @description	 	Callback Function
* @parameters		app_control_h hAppCtrlReq, app_control_h hAppCtrlReply, app_control_result_e eErrorResult, void *pszData
* @return 		N/A
*/
static void ReplyCallBack(app_control_h hAppCtrlReq, app_control_h hAppCtrlReply, app_control_result_e eErrorResult, void *pszData)
{
	FPRINTF("[Line : %d][%s] ReplyCallBack invoked recieved \\n", __LINE__, API_NAMESPACE);
	if (eErrorResult != APP_CONTROL_RESULT_SUCCEEDED)
	{
		FPRINTF("[Line : %d][%s] ReplyCallBack invoked recieved result is not success \\n", __LINE__, API_NAMESPACE);
	}
}

/**
* @function		AppControlSendAsync
* @description		Helper function, to create multilang handle.
* @parameter  		const char *pszAppID, const char *pszCompID, const char *pszExtraData
* @return		nRet, API return value.
*/
int AppControlSendAsync(const char *pszAppID, const char *pszCompID, const char *pszExtraData)
{
	app_control_h hAppCtrl = NULL;
	int nRet = APP_CONTROL_ERROR_NONE;

	nRet = app_control_create(&hAppCtrl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));
	CHECK_HANDLE(hAppCtrl, "app_control_create");

	nRet = app_control_set_app_id(hAppCtrl, TEST_COMPONENTBASED_APPID);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppCtrl));

	if(pszCompID)
	{
		nRet = app_control_set_component_id(hAppCtrl, pszCompID);
		PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_component_id", AppControlGetError(nRet), app_control_destroy(hAppCtrl));
	}

	nRet = app_control_add_extra_data(hAppCtrl, TEST_COMP_EXTRA_KEY, pszExtraData);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_add_extra_data", AppControlGetError(nRet), app_control_destroy(hAppCtrl));

	nRet = app_control_send_launch_request_async(hAppCtrl, ResultCallBack, ReplyCallBack, NULL);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_send_launch_request_sync", AppControlGetError(nRet), app_control_destroy(hAppCtrl));

	return nRet;
}

/**
* @function			AppGetError
* @description			Maps error enums to string values
* @parameter			nRet : error code returned
* @return			error string
*/
char* AppGetError(int nRet)
{
	char *pszErrorVal = "Unknown Error";
	switch ( nRet )
	{
		case APP_ERROR_NONE:			pszErrorVal = "APP_CONTROL_ERROR_NONE";				break;
		case APP_ERROR_INVALID_PARAMETER:			pszErrorVal = "APP_CONTROL_ERROR_INVALID_PARAMETER";			break;
		case APP_ERROR_OUT_OF_MEMORY:			pszErrorVal = "APP_CONTROL_ERROR_OUT_OF_MEMORY";			break;
		case APP_ERROR_INVALID_CONTEXT:			pszErrorVal = "APP_ERROR_INVALID_CONTEXT";			break;
		case APP_ERROR_NO_SUCH_FILE:			pszErrorVal = "APP_ERROR_NO_SUCH_FILE";			break;
		case APP_ERROR_NOT_SUPPORTED:			pszErrorVal = "APP_ERROR_NOT_SUPPORTED";			break;
		case APP_ERROR_ALREADY_RUNNING:			pszErrorVal = "APP_ERROR_ALREADY_RUNNING";			break;
		case APP_ERROR_PERMISSION_DENIED:			pszErrorVal = "APP_ERROR_PERMISSION_DENIED";			break;
	}
	return pszErrorVal;
}

/**
* @function			AppControlGetError
* @description			Maps error enums to string values
* @parameter			nRet : error code returned
* @return			error string
*/
char* AppControlGetError(int nRet)
{
	char *pszErrorVal = "Unknown Error";
	switch ( nRet )
	{
		case APP_CONTROL_ERROR_NONE:			pszErrorVal = "APP_CONTROL_ERROR_NONE";				break;
		case APP_CONTROL_ERROR_INVALID_PARAMETER:			pszErrorVal = "APP_CONTROL_ERROR_INVALID_PARAMETER";			break;
		case APP_CONTROL_ERROR_OUT_OF_MEMORY:			pszErrorVal = "APP_CONTROL_ERROR_OUT_OF_MEMORY";			break;
		case APP_CONTROL_ERROR_APP_NOT_FOUND:			pszErrorVal = "APP_CONTROL_ERROR_APP_NOT_FOUND";			break;
		case APP_CONTROL_ERROR_KEY_NOT_FOUND:			pszErrorVal = "APP_CONTROL_ERROR_KEY_NOT_FOUND";			break;
		case APP_CONTROL_ERROR_KEY_REJECTED:			pszErrorVal = "APP_CONTROL_ERROR_KEY_REJECTED";			break;
		case APP_CONTROL_ERROR_INVALID_DATA_TYPE:			pszErrorVal = "APP_CONTROL_ERROR_INVALID_DATA_TYPE";			break;
		case APP_CONTROL_ERROR_LAUNCH_REJECTED:			pszErrorVal = "APP_CONTROL_ERROR_LAUNCH_REJECTED";			break;
		case APP_CONTROL_ERROR_PERMISSION_DENIED:			pszErrorVal = "APP_CONTROL_ERROR_PERMISSION_DENIED";			break;
		case APP_CONTROL_ERROR_LAUNCH_FAILED:			pszErrorVal = "APP_CONTROL_ERROR_LAUNCH_FAILED";			break;
		case APP_CONTROL_ERROR_TIMED_OUT:			pszErrorVal = "APP_CONTROL_ERROR_TIMED_OUT";			break;
		case APP_CONTROL_ERROR_IO_ERROR:			pszErrorVal = "APP_CONTROL_ERROR_IO_ERROR"; 			break;
	}
	return pszErrorVal;
}

/**
* @function			CompManagerAppGetError
* @description			Maps error enums to string values
* @parameter			nRet : error code returned
* @return			error string
*/
char* CompManagerAppGetError(int nRet)
{
	char *pszErrorVal = "Unknown Error";
	switch ( nRet )
	{
		case COMPONENT_MANAGER_ERROR_NONE:			pszErrorVal = "COMPONENT_MANAGER_ERROR_NONE";	break;
		case COMPONENT_MANAGER_ERROR_INVALID_PARAMETER:			pszErrorVal = "COMPONENT_MANAGER_ERROR_INVALID_PARAMETER";	break;
		case COMPONENT_MANAGER_ERROR_OUT_OF_MEMORY:			pszErrorVal = "COMPONENT_MANAGER_ERROR_OUT_OF_MEMORY";	break;
		case COMPONENT_MANAGER_ERROR_IO_ERROR:			pszErrorVal = "COMPONENT_MANAGER_ERROR_IO_ERROR";	break;
		case COMPONENT_MANAGER_ERROR_NO_SUCH_COMPONENT:			pszErrorVal = "COMPONENT_MANAGER_ERROR_NO_SUCH_COMPONENT";	break;
		case COMPONENT_MANAGER_ERROR_DB_FAILED:			pszErrorVal = "COMPONENT_MANAGER_ERROR_DB_FAILED";	break;
		case COMPONENT_MANAGER_ERROR_INVALID_APPLICATION:			pszErrorVal = "COMPONENT_MANAGER_ERROR_INVALID_APPLICATION";	break;
		case COMPONENT_MANAGER_ERROR_NOT_RUNNING:			pszErrorVal = "COMPONENT_MANAGER_ERROR_NOT_RUNNING";	break;
		case COMPONENT_MANAGER_ERROR_LABEL_NOT_FOUND:			pszErrorVal = "COMPONENT_MANAGER_ERROR_LABEL_NOT_FOUND";	break;
		case COMPONENT_MANAGER_ERROR_PERMISSION_DENIED:			pszErrorVal = "COMPONENT_MANAGER_ERROR_PERMISSION_DENIED";	break;
	}
	return pszErrorVal;
}

/**
* @function			AppControlGetResult
* @description			Maps error enums to string values
* @parameter			nRet : error code returned
* @return			error string
*/
char* AppControlGetResult(int nRet)
{
	char *pszErrorVal = "Unknown Result";
	switch ( nRet )
	{
		case APP_CONTROL_RESULT_APP_STARTED:			pszErrorVal = "APP_CONTROL_RESULT_APP_STARTED";	break;
		case APP_CONTROL_RESULT_SUCCEEDED:			pszErrorVal = "APP_CONTROL_RESULT_SUCCEEDED";	break;
		case APP_CONTROL_RESULT_FAILED:			pszErrorVal = "APP_CONTROL_RESULT_FAILED";	break;
		case APP_CONTROL_RESULT_CANCELED:			pszErrorVal = "APP_CONTROL_RESULT_CANCELED";	break;
	}
	return pszErrorVal;
}

/** @} */ //end of itc-component-based-app
