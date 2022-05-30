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
* @function		ITs_notification_ex_progress_startup
* @description		Called before each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_progress_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_notification_ex_progress_startup \\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

/**
* @function		ITs_notification_ex_progress_cleanup
* @description		Called after each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_progress_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_notification_ex_progress_cleanup \\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
//& type : auto
//& purpose: Creates the notification_ex item handle with progress.
/**
* @testcase			ITc_noti_ex_item_progress_create_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates the notification_ex item handle with progress.
* @scenario			Creates notification_ex progress item and check handle\n
*				Check for Pass/Fail.
* @apicovered			noti_ex_item_progress_create
* @passcase			noti_ex_item_progress_create is successful and return correct value
* @failcase			noti_ex_item_progress_create failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_progress_create_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemProgress = NULL;

	const char *pszProgressID = "progressID";
	float fMin = 0.0;
	float fCurrent = 0.0;
	float fMax = 100.0;

	//Target API
	nRet = noti_ex_item_progress_create(&hItemProgress, pszProgressID, fMin, fCurrent, fMax);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_progress_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemProgress, "noti_ex_item_progress_create");

	nRet = noti_ex_item_destroy(hItemProgress);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets and gets the current value of progress.
/**
* @testcase			ITc_noti_ex_item_progress_set_get_current_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets and gets the current value of progress.
* @scenario			Creates notification_ex progress item and Set current progress\n
*				Get current progress, compare them and Check for Pass/Fail.
* @apicovered			noti_ex_item_progress_set_current, noti_ex_item_progress_get_current
* @passcase			noti_ex_item_progress_set_current, noti_ex_item_progress_get_current are successful and return correct value
* @failcase			noti_ex_item_progress_set_current, noti_ex_item_progress_get_current failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_progress_set_get_current_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemProgress = NULL;

	const char *pszProgressID = "progressID";
	float fMin = 0.0;
	float fCurrent = 0.0;
	float fMax = 100.0;
	float fSetCurrent = 50.0;
	float fGetCurrent = 0.0;

	nRet = noti_ex_item_progress_create(&hItemProgress, pszProgressID, fMin, fCurrent, fMax);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_progress_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemProgress, "noti_ex_item_progress_create");

	//Target API
	nRet = noti_ex_item_progress_set_current(hItemProgress, fSetCurrent);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_progress_set_current", NotificationExGetError(nRet), noti_ex_item_destroy(hItemProgress));

	//Target API
	nRet = noti_ex_item_progress_get_current(hItemProgress, &fGetCurrent);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_progress_get_current", NotificationExGetError(nRet), noti_ex_item_destroy(hItemProgress));
	if(fSetCurrent != fGetCurrent)
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_progress_get_current: return time is different from set_current\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = noti_ex_item_destroy(hItemProgress);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the minimum and maximum value of progress.
/**
* @testcase			ITc_noti_ex_item_progress_get_min_max_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the minimum and maximum value of progress.
* @scenario			Creates notification_ex progress item and with all progress value\n
*				Get minimum and maximum progress, compare them with set value and Check for Pass/Fail.
* @apicovered			noti_ex_item_progress_get_min, noti_ex_item_progress_get_max
* @passcase			noti_ex_item_progress_get_min, noti_ex_item_progress_get_max are successful and return correct value
* @failcase			noti_ex_item_progress_get_min, noti_ex_item_progress_get_max failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_progress_get_min_max_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemProgress = NULL;

	const char *pszProgressID = "progressID";
	float fMin = 0.0;
	float fCurrent = 0.0;
	float fMax = 100.0;
	float fGetMin = 100.0;
	float fGetMax = 0.0;

	nRet = noti_ex_item_progress_create(&hItemProgress, pszProgressID, fMin, fCurrent, fMax);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_progress_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemProgress, "noti_ex_item_progress_create");

	//Target API
	nRet = noti_ex_item_progress_get_min(hItemProgress, &fGetMin);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_progress_get_min", NotificationExGetError(nRet), noti_ex_item_destroy(hItemProgress));
	if(fGetMin != fMin)
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_progress_get_min: return fGetMin is different from fMin \\n", __LINE__, API_NAMESPACE);
		nRet = noti_ex_item_destroy(hItemProgress);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));
		return 1;
	}

	//Target API
	nRet = noti_ex_item_progress_get_max(hItemProgress, &fGetMax);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_progress_get_max", NotificationExGetError(nRet), noti_ex_item_destroy(hItemProgress));
	if(fGetMax != fMax)
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_progress_get_max: return fGetMax is different from fMax\\n", __LINE__, API_NAMESPACE);
		nRet = noti_ex_item_destroy(hItemProgress);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));
		return 1;
	}

	nRet = noti_ex_item_destroy(hItemProgress);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}
//& type : auto
//& purpose: Set and Get the type of progress.
/**
* @testcase			ITc_noti_ex_item_progress_set_get_type_p
* @since_tizen			5.5
* @author			SRID(manu.tiwari)
* @reviewer			SRID(j.abhishek)
* @type				auto
* @description			Set and Get the type of progress.
* @scenario			Creates the notification_ex item handle for the progress \n
*				Set the progress type and get and compare with set type \n
*				and check for Pass/Fail.
* @apicovered			noti_ex_item_progress_set_type, noti_ex_item_progress_get_type
* @passcase			noti_ex_item_progress_set_type, noti_ex_item_progress_get_type is successful and return correct value
* @failcase			noti_ex_item_progress_set_type, noti_ex_item_progress_get_type failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_progress_set_get_type_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;

	noti_ex_item_h hItemProgress = NULL;
	const char *pszProgressID = "progressID";
	float fMin = 0.0;
	float fCurrent = 50.0;
	float fMax = 100.0;

	nRet = noti_ex_item_progress_create(&hItemProgress, pszProgressID, fMin, fCurrent, fMax);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_progress_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemProgress, "noti_ex_item_progress_create");

	noti_ex_item_progress_type_e eProgressType[] = {
		NOTI_EX_ITEM_PROGRESS_TYPE_DEFAULT,
		NOTI_EX_ITEM_PROGRESS_TYPE_TIME,
		NOTI_EX_ITEM_PROGRESS_TYPE_PERCENT,
		NOTI_EX_ITEM_PROGRESS_TYPE_PENDING
	};

	int nEnumSize = sizeof(eProgressType) / sizeof(eProgressType[0]);
	int nEnumCounter;
	int nProgressType = NOTI_EX_ITEM_PROGRESS_TYPE_DEFAULT;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		//Taregt API
		nRet = noti_ex_item_progress_set_type(hItemProgress, eProgressType[nEnumCounter]);
		PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_progress_set_type", NotificationExGetError(nRet), noti_ex_item_destroy(hItemProgress));

		//Taregt API
		nRet = noti_ex_item_progress_get_type(hItemProgress, &nProgressType);
		PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_progress_get_type", NotificationExGetError(nRet), noti_ex_item_destroy(hItemProgress));
		PRINT_RESULT_CLEANUP(eProgressType[nEnumCounter], nProgressType, "noti_ex_item_progress_get_type", "get progress type is not same as set type", noti_ex_item_destroy(hItemProgress));
	}
	nRet = noti_ex_item_destroy(hItemProgress);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}
