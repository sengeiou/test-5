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

#include "ITs-notification-common.h"
/**
* @function		ITs_notification_ex_action_app_control_startup
* @description		Called before each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_action_app_control_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_notification_ex_action_app_control_startup \\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

/**
* @function		ITs_notification_ex_action_app_control_cleanup
* @description		Called after each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_action_app_control_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_notification_ex_action_app_control_cleanup \\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
//& type : auto
//& purpose: Creates a notification app control.
/**
* @testcase			ITc_noti_ex_action_app_control_create_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates notification-ex app control handler.
* @scenario			Create notification\n
*				Check return value and also check handle is null or not.
* @apicovered			noti_ex_action_app_control_create
* @passcase			noti_ex_action_app_control_create is successful and return correct value
* @failcase			noti_ex_action_app_control_create gets failed or return null value
* @precondition			Create app control and set app id to a dummy app id.
* @postcondition		Destroy app control and app control action handler.
*/
int ITc_noti_ex_action_app_control_create_p(void)
{
	START_TEST;

	int nRet = APP_CONTROL_ERROR_NONE;
	app_control_h hAppControl;
	noti_ex_action_h hAction = NULL;

	nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", Application_AppControlGetError(nRet));
	CHECK_HANDLE(hAppControl, "app_control_create");

	const char* pszSetAppID = "org.tizen.app"; //dummy app id
	nRet = app_control_set_app_id(hAppControl, pszSetAppID);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", Application_AppControlGetError(nRet), app_control_destroy(hAppControl));

	//Target API
	nRet = noti_ex_action_app_control_create(&hAction, hAppControl, NULL);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_app_control_create", NotificationExGetError(nRet), app_control_destroy(hAppControl));
	CHECK_HANDLE_CLEANUP(hAction, "noti_ex_action_app_control_create", app_control_destroy(hAppControl));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT_NORETURN(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", Application_AppControlGetError(nRet));

	nRet = noti_ex_action_destroy(hAction);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets and Gets new app control handle from action
/**
* @testcase			ITc_noti_ex_action_app_control_set_get_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets and Gets new app control handle from action.
* @scenario			Create notification\n
*				Gets new app control from action handler and check for Pass/Fail.
* @apicovered			noti_ex_action_app_control_set, noti_ex_action_app_control_get
* @passcase			noti_ex_action_app_control_set, noti_ex_action_app_control_get are successful and return correct value
* @failcase			noti_ex_action_app_control_set, noti_ex_action_app_control_get gets failed or return null value
* @precondition			Create app control and set app id to a dummy app id.
* @postcondition		Destroy app control and app control action handler.
*/
int ITc_noti_ex_action_app_control_set_get_p(void)
{
	START_TEST;

	int nRet = APP_CONTROL_ERROR_NONE;
	app_control_h hAppControl;
	app_control_h hAppControlSet;
	app_control_h hAppControlGet = NULL;
	noti_ex_action_h hAction = NULL;

	nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", Application_AppControlGetError(nRet));
	CHECK_HANDLE(hAppControl, "app_control_create");

	const char* pszSetAppID = "org.tizen.app"; //dummy app id
	nRet = app_control_set_app_id(hAppControl, pszSetAppID);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", Application_AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = noti_ex_action_app_control_create(&hAction, hAppControl, NULL);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_app_control_create", NotificationExGetError(nRet), app_control_destroy(hAppControl));
	CHECK_HANDLE_CLEANUP(hAction, "noti_ex_action_app_control_creat", app_control_destroy(hAppControl));

	nRet = app_control_create(&hAppControlSet);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", Application_AppControlGetError(nRet), app_control_destroy(hAppControl); noti_ex_action_destroy(hAction));
	CHECK_HANDLE_CLEANUP(hAppControlSet, "app_control_create", app_control_destroy(hAppControl); noti_ex_action_destroy(hAction));

	const char* pNewAppID = "org.tizen.newapp"; //dummy app id
	nRet = app_control_set_app_id(hAppControlSet, pNewAppID);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", Application_AppControlGetError(nRet), app_control_destroy(hAppControl); noti_ex_action_destroy(hAction));

	//Target API
	nRet = noti_ex_action_app_control_set(hAction, hAppControlSet);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_app_control_set", NotificationExGetError(nRet), app_control_destroy(hAppControl); noti_ex_action_destroy(hAction));

	//Target API
	nRet = noti_ex_action_app_control_get(hAction, &hAppControlGet);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_app_control_get", NotificationExGetError(nRet), app_control_destroy(hAppControl); noti_ex_action_destroy(hAction));
	CHECK_HANDLE_CLEANUP(hAppControlGet, "noti_ex_action_app_control_get", app_control_destroy(hAppControl); noti_ex_action_destroy(hAction));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT_NORETURN(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", Application_AppControlGetError(nRet));

	nRet = noti_ex_action_destroy(hAction);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_destroy", NotificationExGetError(nRet));

	return 0;
}
