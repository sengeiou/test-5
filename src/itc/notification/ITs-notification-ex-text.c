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
* @function		ITs_notification_ex_text_startup
* @description		Called before each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_text_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_notification_ex_text_startup \\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

/**
* @function		ITs_notification_ex_text_cleanup
* @description		Called after each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_text_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_notification_ex_text_cleanup \\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
//& type : auto
//& purpose: Creates the notification_ex item handle with text.
/**
* @testcase			ITc_noti_ex_item_text_create_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates the notification_ex item handle with text.
* @scenario			Creates notification_ex text item, check for handle and check for Pass/Fail.
* @apicovered			noti_ex_item_text_create
* @passcase			noti_ex_item_text_create is successful and return correct value
* @failcase			noti_ex_item_text_create failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_text_create_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemText = NULL;

	const char *pszTextID = "text_id";
	const char *pszTextTitle = "textTitle";
	const char *pszTextHyperLink = "testHyperLink";

	//Target API
	nRet = noti_ex_item_text_create(&hItemText, pszTextID, pszTextTitle, pszTextHyperLink);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_text_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemText, "noti_ex_item_text_create");

	nRet = noti_ex_item_destroy(hItemText);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets and Gets the text contents of the text item.
/**
* @testcase			ITc_noti_ex_item_text_set_get_contents_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets and Gets the text contents of the text item.
* @scenario			Creates notification_ex text item and with ID, Title and hyperlink\n
*				Set Content and Get content, compare get value with set value and Check for Pass/Fail.
* @apicovered			noti_ex_item_text_set_contents, noti_ex_item_text_get_contents
* @passcase			noti_ex_item_text_set_contents, noti_ex_item_text_get_contents are successful and return correct value
* @failcase			noti_ex_item_text_set_contents, noti_ex_item_text_get_contents failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_text_set_get_contents_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemText = NULL;

	const char *pszTextID = "text_id";
	const char *pszTextTitle = "textTitle";
	const char *pszTextHyperLink = "testHyperLink";

	const char *pszSetContents = "testContent";
	char *pszGetContents = NULL;

	nRet = noti_ex_item_text_create(&hItemText, pszTextID, pszTextTitle, pszTextHyperLink);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_text_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemText, "noti_ex_item_text_create");

	//Target API
	nRet = noti_ex_item_text_set_contents(hItemText, pszSetContents);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_text_set_contents", NotificationExGetError(nRet), noti_ex_item_destroy(hItemText));

	//Target API
	nRet = noti_ex_item_text_get_contents(hItemText, &pszGetContents);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_text_get_contents", NotificationExGetError(nRet), noti_ex_item_destroy(hItemText));
	CHECK_HANDLE_CLEANUP(pszGetContents, "noti_ex_item_text_get_contents", noti_ex_item_destroy(hItemText));

	if( strncmp(pszSetContents, pszGetContents, strlen(pszGetContents) + 1) )
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_text_get_contents: return content is different from set content [%s]\\n", __LINE__, API_NAMESPACE, pszGetContents);
		FREE_MEMORY(pszGetContents);

		nRet = noti_ex_item_destroy(hItemText);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

		return 1;
	}

	FREE_MEMORY(pszGetContents);

	nRet = noti_ex_item_destroy(hItemText);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the hyperlink of the text item.
/**
* @testcase			ITc_noti_ex_item_text_get_hyperlink_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the hyperlink of the text item.
* @scenario			Creates notification_ex text item and with ID, Title and hyperlink\n
*				Get hyperlink and compare with set value and Check for Pass/Fail.
* @apicovered			noti_ex_item_text_get_hyperlink
* @passcase			noti_ex_item_text_get_hyperlink is successful and return correct value
* @failcase			noti_ex_item_text_get_hyperlink failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_text_get_hyperlink_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemText = NULL;

	const char *pszTextID = "text_id";
	const char *pszTextTitle = "textTitle";
	const char *pszTextHyperLink = "testHyperLink";

	char *pszGetHyperLink = NULL;

	nRet = noti_ex_item_text_create(&hItemText, pszTextID, pszTextTitle, pszTextHyperLink);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_text_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemText, "noti_ex_item_text_create");

	//Target API
	nRet = noti_ex_item_text_get_hyperlink(hItemText, &pszGetHyperLink);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_text_get_hyperlink", NotificationExGetError(nRet), noti_ex_item_destroy(hItemText));
	CHECK_HANDLE_CLEANUP(pszGetHyperLink, "noti_ex_item_text_get_hyperlink", noti_ex_item_destroy(hItemText));

	if( strncmp(pszTextHyperLink, pszGetHyperLink, strlen(pszGetHyperLink) + 1) )
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_text_get_hyperlink: return hyperlink is different from set hyperlink [%s]\\n", __LINE__, API_NAMESPACE, pszGetHyperLink);
		FREE_MEMORY(pszGetHyperLink);

		nRet = noti_ex_item_destroy(hItemText);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

		return 1;
	}

	FREE_MEMORY(pszGetHyperLink);

	nRet = noti_ex_item_destroy(hItemText);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}
//& type : auto
//& purpose: Sets the multi-language handle for text.
/**
* @testcase			ITc_noti_ex_item_text_set_multi_language_p
* @since_tizen			5.5
* @author			SRID(manu.tiwari)
* @reviewer			SRID(j.abhishek)
* @type				auto
* @description			Sets the multi-language handle for text.
* @scenario			Creates the notification_ex text and multi langauge handle \n
*				Sets the multi-language handle for text \n
*				and check for Pass/Fail.
* @apicovered			noti_ex_item_text_set_multi_language
* @passcase			noti_ex_item_text_set_multi_language is successful and return correct value
* @failcase			noti_ex_item_text_set_multi_language failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_text_set_multi_language_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;

	noti_ex_item_h hItemText = NULL;
	const char *pszTextID = "text_id";
	const char *pszTextTitle = "textTitle";
	const char *pszTextHyperLink = "testHyperLink";

	nRet = noti_ex_item_text_create(&hItemText, pszTextID, pszTextTitle, pszTextHyperLink);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_text_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemText, "noti_ex_item_text_create");

	nRet = CreateMultiLangHandle();
	PRINT_RESULT_CLEANUP(0, nRet, "noti_ex_multi_lang_create", "API failed or handle not created successfully", noti_ex_item_destroy(hItemText));

	//Target API
	nRet = noti_ex_item_text_set_multi_language(hItemText, g_hMultiLang);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_text_set_multi_language", NotificationExGetError(nRet), noti_ex_item_destroy(hItemText); noti_ex_multi_lang_destroy(g_hMultiLang));

	nRet = noti_ex_multi_lang_destroy(g_hMultiLang);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_multi_lang_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_item_destroy(hItemText);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}
