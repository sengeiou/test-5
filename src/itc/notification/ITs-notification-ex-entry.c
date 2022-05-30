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
* @function		ITs_notification_ex_entry_startup
* @description		Called before each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_entry_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_notification_ex_entry_startup \\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

/**
* @function		ITs_notification_ex_entry_cleanup
* @description		Called after each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_entry_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_notification_ex_entry_cleanup \\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
//& type : auto
//& purpose: Creates the notification_ex item handle for an entry item.
/**
* @testcase			ITc_noti_ex_item_entry_create_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates the notification_ex item handle for an entry item.
* @scenario			Creates the notification_ex item handle for an entry item \n
*				Check handle and check for return value \n
*				and check for Pass/Fail.
* @apicovered			noti_ex_item_entry_create
* @passcase			noti_ex_item_entry_create is successful and return correct value
* @failcase			noti_ex_item_entry_create failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_entry_create_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemEntry = NULL;
	const char *pszEntryID = "entry_id";

	//Target API
	nRet = noti_ex_item_entry_create(&hItemEntry, pszEntryID);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_entry_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemEntry, "noti_ex_item_entry_create");

	nRet = noti_ex_item_destroy(hItemEntry);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Set text to and get text from notification_ex item handle for an entry item.
/**
* @testcase			ITc_noti_ex_item_entry_set_get_text_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Set text to and get text from notification_ex item handle for an entry item.
* @scenario			Set text and get text for entry item \n
*				Compare set and returned text and check for Pass/Fail.
* @apicovered			noti_ex_item_entry_set_text, noti_ex_item_entry_get_text
* @passcase			noti_ex_item_entry_set_text, noti_ex_item_entry_get_text are successful and return correct value
* @failcase			noti_ex_item_entry_set_text, noti_ex_item_entry_get_text failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_entry_set_get_text_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemEntry = NULL;
	const char *pszEntryText = "entry_id";
	char *pszEntryGetText = NULL;

	nRet = noti_ex_item_entry_create(&hItemEntry, pszEntryText);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_entry_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemEntry, "noti_ex_item_entry_create");

	//Target API
	nRet = noti_ex_item_entry_set_text(hItemEntry, pszEntryText);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_entry_set_text", NotificationExGetError(nRet), noti_ex_item_destroy(hItemEntry));

	//Target API
	nRet = noti_ex_item_entry_get_text(hItemEntry, &pszEntryGetText);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_entry_get_text", NotificationExGetError(nRet), noti_ex_item_destroy(hItemEntry));
	CHECK_HANDLE_CLEANUP(pszEntryGetText, "noti_ex_item_entry_get_text", noti_ex_item_destroy(hItemEntry));

	if( strncmp(pszEntryText, pszEntryGetText, strlen(pszEntryGetText) + 1) )
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_entry_get_text: return entry text is different from set entry text [%s]\\n", __LINE__, API_NAMESPACE, pszEntryGetText);
		FREE_MEMORY(pszEntryGetText);

		nRet = noti_ex_item_destroy(hItemEntry);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

		return 1;
	}

	FREE_MEMORY(pszEntryGetText);

	nRet = noti_ex_item_destroy(hItemEntry);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}
//& type : auto
//& purpose: Sets the multi-language handle for entry.
/**
* @testcase			ITc_noti_ex_item_entry_set_multi_language_p
* @since_tizen			5.5
* @author			SRID(manu.tiwari)
* @reviewer			SRID(j.abhishek)
* @type				auto
* @description			Sets the multi-language handle for entry.
* @scenario			Creates the notification_ex entry and multi langauge handle \n
*				Sets the multi-language handle for entry \n
*				and check for Pass/Fail.
* @apicovered			noti_ex_item_entry_set_multi_language
* @passcase			noti_ex_item_entry_set_multi_language is successful and return correct value
* @failcase			noti_ex_item_entry_set_multi_language failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_entry_set_multi_language_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;

	noti_ex_item_h hItemEntry = NULL;
	const char *pszEntryID = "entry_id";

	nRet = noti_ex_item_entry_create(&hItemEntry, pszEntryID);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_entry_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemEntry, "noti_ex_item_entry_create");

	nRet = CreateMultiLangHandle();
	PRINT_RESULT_CLEANUP(0, nRet, "noti_ex_multi_lang_create", "API failed or handle not created successfully", noti_ex_item_destroy(hItemEntry));

	//Target API
	nRet = noti_ex_item_entry_set_multi_language(hItemEntry, g_hMultiLang);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_entry_set_multi_language", NotificationExGetError(nRet), noti_ex_item_destroy(hItemEntry); noti_ex_multi_lang_destroy(g_hMultiLang));

	nRet = noti_ex_multi_lang_destroy(g_hMultiLang);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_multi_lang_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_item_destroy(hItemEntry);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}
