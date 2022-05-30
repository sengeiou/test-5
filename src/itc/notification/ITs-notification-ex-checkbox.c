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
* @function		ITs_notification_ex_checkbox_startup
* @description		Called before each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_checkbox_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_notification_ex_checkbox_startup \\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

/**
* @function		ITs_notification_ex_checkbox_cleanup
* @description		Called after each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_checkbox_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_notification_ex_checkbox_cleanup \\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
//& type : auto
//& purpose: Creates the notification_ex item handle with checkbox.
/**
* @testcase			ITc_noti_ex_item_checkbox_create_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates the notification_ex item handle with checkbox.
* @scenario			Creates the notification_ex item handle for the checkbox \n
*				Check for handle and check for Pass/Fail.
* @apicovered			noti_ex_item_checkbox_create
* @passcase			noti_ex_item_checkbox_create is successful and return correct value
* @failcase			noti_ex_item_checkbox_create failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_checkbox_create_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemCheckBox = NULL;
	const char *pszCheckBoxID = "checkbox_id";
	const char *pszCheckBoxTitle = "checkbox_title";
	bool bChecked = false;

	nRet = noti_ex_item_checkbox_create(&hItemCheckBox, pszCheckBoxID, pszCheckBoxTitle, bChecked);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_checkbox_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemCheckBox, "noti_ex_item_checkbox_create");

	nRet = noti_ex_item_destroy(hItemCheckBox);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the title of a checkbox.
/**
* @testcase			ITc_noti_ex_item_checkbox_get_title_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the title of a checkbox.
* @scenario			Creates the notification_ex item handle for the checkbox \n
*				Get checkbox title and compare with set title \n
*				and check for Pass/Fail.
* @apicovered			noti_ex_item_checkbox_get_title
* @passcase			noti_ex_item_checkbox_get_title is successful and return correct value
* @failcase			noti_ex_item_checkbox_get_title failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_checkbox_get_title_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemCheckBox = NULL;
	const char *pszCheckBoxID = "checkbox_id";
	const char *pszCheckBoxTitle = "checkbox_title";
	bool bChecked = false;

	char *pszGetCheckBoxTitle = NULL;

	nRet = noti_ex_item_checkbox_create(&hItemCheckBox, pszCheckBoxID, pszCheckBoxTitle, bChecked);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_checkbox_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemCheckBox, "noti_ex_item_checkbox_create");

	//Target API
	nRet = noti_ex_item_checkbox_get_title(hItemCheckBox, &pszGetCheckBoxTitle);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_checkbox_get_title", NotificationExGetError(nRet), noti_ex_item_destroy(hItemCheckBox));
	CHECK_HANDLE_CLEANUP(pszGetCheckBoxTitle, "noti_ex_item_checkbox_get_title", noti_ex_item_destroy(hItemCheckBox));

	if( strncmp(pszGetCheckBoxTitle, pszCheckBoxTitle, strlen(pszCheckBoxTitle) + 1) )
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_checkbox_get_title: return checkbox title is different from set checkbox title [%s]\\n", __LINE__, API_NAMESPACE, pszGetCheckBoxTitle);
		FREE_MEMORY(pszGetCheckBoxTitle);
		nRet = noti_ex_item_destroy(hItemCheckBox);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

		return 1;
	}

	FREE_MEMORY(pszGetCheckBoxTitle);

	nRet = noti_ex_item_destroy(hItemCheckBox);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}
//& type : auto
//& purpose: Sets the multi-language handle for checkbox.
/**
* @testcase			ITc_noti_ex_item_checkbox_set_multi_language_title_p
* @since_tizen			5.5
* @author			SRID(manu.tiwari)
* @reviewer			SRID(j.abhishek)
* @type				auto
* @description			Sets the multi-language handle for checkbox.
* @scenario			Creates the notification_ex checkbox and multi langauge handle \n
*				Sets the multi-language handle for checkbox \n
*				and check for Pass/Fail.
* @apicovered			noti_ex_item_checkbox_set_multi_language_title
* @passcase			noti_ex_item_checkbox_set_multi_language_title is successful and return correct value
* @failcase			noti_ex_item_checkbox_set_multi_language_title failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_checkbox_set_multi_language_title_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;

	noti_ex_item_h hItemCheckBox = NULL;
	const char *pszCheckBoxID = "checkbox_id";
	const char *pszCheckBoxTitle = "checkbox_title";

	nRet = noti_ex_item_checkbox_create(&hItemCheckBox, pszCheckBoxID, pszCheckBoxTitle, false);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_checkbox_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemCheckBox, "noti_ex_item_checkbox_create");

	nRet = CreateMultiLangHandle();
	PRINT_RESULT_CLEANUP(0, nRet, "noti_ex_multi_lang_create", "API failed or handle not created successfully", noti_ex_item_destroy(hItemCheckBox));

	//Target API
	nRet = noti_ex_item_checkbox_set_multi_language_title(hItemCheckBox, g_hMultiLang);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_checkbox_set_multi_language_title", NotificationExGetError(nRet), noti_ex_item_destroy(hItemCheckBox); noti_ex_multi_lang_destroy(g_hMultiLang));

	nRet = noti_ex_multi_lang_destroy(g_hMultiLang);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_multi_lang_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_item_destroy(hItemCheckBox);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}
//& type : auto
//& purpose: Set and Get the check state of a checkbox.
/**
* @testcase			ITc_noti_ex_item_checkbox_set_get_check_state_p
* @since_tizen			5.5
* @author			SRID(manu.tiwari)
* @reviewer			SRID(j.abhishek)
* @type				auto
* @description			Set and Get the check state of a checkbox.
* @scenario			Creates the notification_ex item handle for the checkbox \n
*				Gets the check state of a checkbox and compare with set title \n
*				and check for Pass/Fail.
* @apicovered			noti_ex_item_checkbox_set_check_state, noti_ex_item_checkbox_get_check_state
* @passcase			noti_ex_item_checkbox_set_check_state, noti_ex_item_checkbox_get_check_state are successful and return correct value
* @failcase			noti_ex_item_checkbox_set_check_state, noti_ex_item_checkbox_get_check_state failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_checkbox_set_get_check_state_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemCheckBox = NULL;
	const char *pszCheckBoxID = "checkbox_id";
	const char *pszCheckBoxTitle = "checkbox_title";
	bool bChecked = true;
	bool bIsChecked = false;

	nRet = noti_ex_item_checkbox_create(&hItemCheckBox, pszCheckBoxID, pszCheckBoxTitle, false);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_checkbox_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemCheckBox, "noti_ex_item_checkbox_create");

	//Target API
	nRet = noti_ex_item_checkbox_set_check_state(hItemCheckBox, bChecked);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_checkbox_set_check_state", NotificationExGetError(nRet), noti_ex_item_destroy(hItemCheckBox));

	//Target API
	nRet = noti_ex_item_checkbox_get_check_state(hItemCheckBox, &bIsChecked);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_checkbox_get_check_state", NotificationExGetError(nRet), noti_ex_item_destroy(hItemCheckBox));
	PRINT_RESULT_CLEANUP(bChecked, bIsChecked, "noti_ex_item_checkbox_get_check_state", "Checkbox checked API returned wrong value", noti_ex_item_destroy(hItemCheckBox));

	nRet = noti_ex_item_destroy(hItemCheckBox);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}
