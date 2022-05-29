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
* @function		ITs_notification_ex_time_startup
* @description		Called before each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_time_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_notification_ex_time_startup \\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

/**
* @function		ITs_notification_ex_time_cleanup
* @description		Called after each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_time_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_notification_ex_time_cleanup \\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
//& type : auto
//& purpose: Creates the notification_ex item handle with time.
/**
* @testcase			ITc_noti_ex_item_time_create_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates the notification_ex item handle with time.
* @scenario			Creates notification_ex time item \n
*				Check for handle and Check for Pass/Fail.
* @apicovered			noti_ex_item_time_create
* @passcase			noti_ex_item_time_create is successful and return correct value
* @failcase			noti_ex_item_time_create failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_time_create_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemTime = NULL;
	const char *pszTimeID = "time_id";
	time_t tCurTime;

	time(&tCurTime);

	//Target API
	nRet = noti_ex_item_time_create(&hItemTime, pszTimeID, tCurTime);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_time_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemTime, "noti_ex_item_time_create");

	nRet = noti_ex_item_destroy(hItemTime);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Creates the notification_ex item handle with time.
/**
* @testcase			ITc_noti_ex_item_time_get_time_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates the notification_ex item handle with time.
* @scenario			Creates notification_ex time item \n
*				get time and should bot be zero and Check for Pass/Fail.
* @apicovered			noti_ex_item_time_get_time
* @passcase			noti_ex_item_time_get_time is successful and return correct value
* @failcase			noti_ex_item_time_get_time failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_time_get_time_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemTime = NULL;
	const char *pszTimeID = "time_id";
	time_t tCurTime;
	time_t tGetCurTime = 0;

	time(&tCurTime);

	nRet = noti_ex_item_time_create(&hItemTime, pszTimeID, tCurTime);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_time_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemTime, "noti_ex_item_time_create");

	//Target API
	nRet = noti_ex_item_time_get_time(hItemTime, &tGetCurTime);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_time_get_time", NotificationExGetError(nRet), noti_ex_item_destroy(hItemTime));

	if(tGetCurTime == 0)
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_time_get_time: return time [%ld]\\n", __LINE__, API_NAMESPACE, tGetCurTime);

		nRet = noti_ex_item_destroy(hItemTime);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

		return 1;
	}

	nRet = noti_ex_item_destroy(hItemTime);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}
