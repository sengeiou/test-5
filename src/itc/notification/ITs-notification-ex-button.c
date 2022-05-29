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
* @function		ITs_notification_ex_button_startup
* @description		Called before each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_button_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_notification_ex_button_startup \\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

/**
* @function		ITs_notification_ex_button_cleanup
* @description		Called after each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_button_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_notification_ex_button_cleanup \\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
//& type : auto
//& purpose: Creates the notification_ex item handle with a button.
/**
* @testcase			ITc_noti_ex_item_button_create_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates the notification_ex item handle with a button.
* @scenario			Creates the notification_ex item handle with a button \n
*				Check for Pass/Fail.
* @apicovered			noti_ex_item_button_create
* @passcase			noti_ex_item_button_create is successful and return correct value
* @failcase			noti_ex_item_button_create failed or return null value
* @precondition			NA.
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_button_create_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;

	//Taregt API
	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the title of a button item.
/**
* @testcase			ITc_noti_ex_item_button_get_title_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the title of a button item.
* @scenario			Creates the notification_ex item handle with a button \n
*				Gets the title and compare with Set title. Check for Pass/Fail.
* @apicovered			noti_ex_item_button_get_title
* @passcase			noti_ex_item_button_get_title is successful and return correct value
* @failcase			noti_ex_item_button_get_title failed or return null value
* @precondition			NA.
* @postcondition		Free Title pointer memory and destroy handle.
*/
int ITc_noti_ex_item_button_get_title_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	char* pszGetTitle = NULL;

	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	//Taregt API
	nRet = noti_ex_item_button_get_title(g_hItemButton, &pszGetTitle);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_get_title", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	CHECK_HANDLE_CLEANUP(pszGetTitle, "noti_ex_item_button_get_title", noti_ex_item_destroy(g_hItemButton));

	if (strncmp(g_pszButtonTitle, pszGetTitle, strlen(pszGetTitle) + 1))
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_button_get_title: return title is different from set title [%s]\\n", __LINE__, API_NAMESPACE, pszGetTitle);
		FREE_MEMORY(pszGetTitle);

		nRet = noti_ex_item_destroy(g_hItemButton);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

		return 1;
	}

	FREE_MEMORY(pszGetTitle);

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}
//& type : auto
//& purpose: Sets the multi-language handle for button.
/**
* @testcase			ITc_noti_ex_item_button_set_multi_language_title_p
* @since_tizen			5.5
* @author			SRID(manu.tiwari)
* @reviewer			SRID(j.abhishek)
* @type				auto
* @description			Sets the multi-language handle for button.
* @scenario			Creates the notification_ex button and multi langauge handle \n
*				Sets the multi-language handle for button \n
*				and check for Pass/Fail.
* @apicovered			noti_ex_item_button_set_multi_language_title
* @passcase			noti_ex_item_button_set_multi_language_title is successful and return correct value
* @failcase			noti_ex_item_button_set_multi_language_title failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_button_set_multi_language_title_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;

	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	nRet = CreateMultiLangHandle();
	PRINT_RESULT_CLEANUP(0, nRet, "noti_ex_multi_lang_create", "API failed or handle not created successfully", noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_item_button_set_multi_language_title(g_hItemButton, g_hMultiLang);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_set_multi_language_title", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton); noti_ex_multi_lang_destroy(g_hMultiLang));

	nRet = noti_ex_multi_lang_destroy(g_hMultiLang);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_multi_lang_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}
