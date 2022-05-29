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
* @function		ITs_notification_ex_visibility_action_startup
* @description		Called before each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_visibility_action_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_notification_ex_visibility_action_startup \\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

/**
* @function		ITs_notification_ex_visibility_action_cleanup
* @description		Called after each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_visibility_action_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_notification_ex_visibility_action_cleanup \\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& type : auto
//& purpose: Creates and delete the notification_ex action handle to control visibility
/**
* @testcase			ITc_noti_ex_action_visibility_create_destroy_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates and delete  the notification_ex action handle to control visibility.
* @scenario			Creates the notification_ex action handle to control visibility\n
*				and delete created handle, check handle for Pass/Fail.
* @apicovered			noti_ex_action_visibility_create, noti_ex_action_destroy
* @passcase			noti_ex_action_visibility_create, noti_ex_action_destroy is successful and return correct value
* @failcase			noti_ex_action_visibility_create, noti_ex_action_destroy failed or return null value
* @precondition			NA.
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_action_visibility_create_destroy_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_action_h hAction = NULL;
	const char* pszExtra = "extra";

	//Target API
	nRet = noti_ex_action_visibility_create(&hAction, pszExtra);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_visibility_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hAction, "noti_ex_action_visibility_create");

	nRet = noti_ex_action_destroy(hAction);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_destroy", NotificationExGetError(nRet));

	return 0;
}


//& type : auto
//& purpose: Sets the visibility state for notification_ex item.
/**
* @testcase			ITc_noti_ex_action_visibility_set_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets the visibility state for notification_ex item.
* @scenario			Creates the notification_ex action handle to control visibility\n
*				Sets the visibility state for notification_ex item and check for Pass/Fail.
* @apicovered			noti_ex_action_visibility_set
* @passcase			noti_ex_action_visibility_set is successful and return correct value
* @failcase			noti_ex_action_visibility_set failed or return null value
* @precondition			NA.
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_action_visibility_set_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_action_h hAction = NULL;
	const char* pszExtra = "extra";
	const char* pszID = "textID";
	bool bIsVisible = true;

	nRet = noti_ex_action_visibility_create(&hAction, pszExtra);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_visibility_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hAction, "noti_ex_action_visibility_create");

	//Target API
	nRet = noti_ex_action_visibility_set(hAction, pszID, bIsVisible);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_visibility_set", NotificationExGetError(nRet), noti_ex_action_destroy(hAction));

	nRet = noti_ex_action_destroy(hAction);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_destroy", NotificationExGetError(nRet));

	return 0;
}
