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
* @function		ITs_notification_ex_input_selector_startup
* @description		Called before each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_input_selector_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_notification_ex_input_selector_startup \\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

/**
* @function		ITs_notification_ex_input_selector_cleanup
* @description		Called after each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_input_selector_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_notification_ex_input_selector_cleanup \\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
//& type : auto
//& purpose: Creates the notification_ex item handle with input selector.
/**
* @testcase			ITc_noti_ex_item_input_selector_create_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates the notification_ex item handle with input selector.
* @scenario			Creates the notification_ex item handle with input selector\n
*				Check for handle and check for Pass/Fail.
* @apicovered			noti_ex_item_input_selector_create
* @passcase			noti_ex_item_input_selector_create is successful and return correct value
* @failcase			noti_ex_item_input_selector_create failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_input_selector_create_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemInputSel = NULL;
	const char *pszInputSelID = "input_selector_id";

	//Target API
	nRet = noti_ex_item_input_selector_create(&hItemInputSel, pszInputSelID);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_input_selector_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemInputSel, "noti_ex_item_input_selector_create");

	nRet = noti_ex_item_destroy(hItemInputSel);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets and gets the contents for input selector item.
/**
* @testcase			ITc_noti_ex_item_input_selector_set_get_contents_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets and gets the contents for input selector item.
* @scenario			Creates the notification_ex item handle with input selector\n
*				Set input selector item content and get content\n
*				Compare set and get contents and check for Pass/Fail.
* @apicovered			noti_ex_item_input_selector_set_contents, noti_ex_item_input_selector_get_contents
* @passcase			noti_ex_item_input_selector_set_contents, noti_ex_item_input_selector_get_contents are successful and return correct value
* @failcase			noti_ex_item_input_selector_set_contents, noti_ex_item_input_selector_get_contents failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_input_selector_set_get_contents_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemInputSel = NULL;

	int nSetCount = 2;
	int nGetCount = 0;

	const char *pszSetContents[] = {"content_1", "content_2"};
	char **pszGetContents = NULL;

	const char *pszInputSelID = "input_selector_id";

	nRet = noti_ex_item_input_selector_create(&hItemInputSel, pszInputSelID);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_input_selector_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemInputSel, "noti_ex_item_input_selector_create");

	//Target API
	nRet = noti_ex_item_input_selector_set_contents(hItemInputSel, pszSetContents, nSetCount);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_input_selector_set_contents", NotificationExGetError(nRet), noti_ex_item_destroy(hItemInputSel));

	//Target API
	nRet = noti_ex_item_input_selector_get_contents(hItemInputSel, &pszGetContents, &nGetCount);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_input_selector_get_contents", NotificationExGetError(nRet), noti_ex_item_destroy(hItemInputSel); FREE_MEMORY(pszGetContents));
	CHECK_HANDLE_CLEANUP(pszGetContents, "noti_ex_item_input_selector_get_contents", noti_ex_item_destroy(hItemInputSel));
	PRINT_RESULT_CLEANUP(nSetCount, nGetCount, "noti_ex_item_input_selector_get_contents", "count revcieved is not same and set count", noti_ex_item_destroy(hItemInputSel); FREE_MEMORY(pszGetContents));

	FREE_MEMORY(pszGetContents);

	nRet = noti_ex_item_destroy(hItemInputSel);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}
//& type : auto
//& purpose: Sets the multi-language contents for input selector item.
/**
* @testcase			ITc_noti_ex_item_input_selector_set_multi_language_contents_p
* @since_tizen			5.5
* @author			SRID(manu.tiwari)
* @reviewer			SRID(j.abhishek)
* @type				auto
* @description			Sets the multi-language contents for input selector item.
* @scenario			Creates the notification_ex item handle for the checkbox \n
*				Get checkbox title and compare with set title \n
*				and check for Pass/Fail.
* @apicovered			noti_ex_item_input_selector_set_multi_language_contents
* @passcase			noti_ex_item_input_selector_set_multi_language_contents is successful and return correct value
* @failcase			noti_ex_item_input_selector_set_multi_language_contents failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_input_selector_set_multi_language_contents_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_multi_lang_h *hMultiLangARR = NULL;
	noti_ex_item_h hItemInputSel = NULL;

	const char *pszInputSelID = "input_selector_id";
	char **hOutMultiLangARR = NULL;
	char ARRBuf[256];
	int nCnt;
	int nLoopSize = 3;
	int nLoopCounter;

	hMultiLangARR = (noti_ex_multi_lang_h *)calloc(3, sizeof(noti_ex_multi_lang_h));
	if(!hMultiLangARR)
	{
		FPRINTF("[Line : %d][%s] calloc failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = noti_ex_item_input_selector_create(&hItemInputSel, pszInputSelID);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_input_selector_create", NotificationExGetError(nRet), FREE_MEMORY(hMultiLangARR));
	CHECK_HANDLE_CLEANUP(hItemInputSel, "noti_ex_item_input_selector_create", FREE_MEMORY(hMultiLangARR));

	for (nLoopCounter = 0; nLoopCounter < nLoopSize; nLoopCounter++)
	{
		nRet = noti_ex_multi_lang_create(&hMultiLangARR[nLoopCounter], "TEST_ID", "test string(test) integer(%d) float(0.77)", nLoopCounter);
		PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_multi_lang_create", NotificationExGetError(nRet), noti_ex_item_destroy(hItemInputSel); FREE_MEMORY(hMultiLangARR));
		CHECK_HANDLE_CLEANUP(hMultiLangARR[nLoopCounter], "noti_ex_multi_lang_create", noti_ex_item_destroy(hItemInputSel); FREE_MEMORY(hMultiLangARR));
	}

	//Target API
	nRet = noti_ex_item_input_selector_set_multi_language_contents(hItemInputSel, hMultiLangARR, nLoopSize);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_input_selector_set_multi_language_contents", NotificationExGetError(nRet), noti_ex_item_destroy(hItemInputSel); FREE_MEMORY(hMultiLangARR));

	nRet = noti_ex_item_input_selector_get_contents(hItemInputSel, &hOutMultiLangARR, &nCnt);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_input_selector_get_contents", NotificationExGetError(nRet), noti_ex_item_destroy(hItemInputSel));
	PRINT_RESULT_CLEANUP(3, nCnt, "noti_ex_item_input_selector_get_contents", "Return count is not same as set count", noti_ex_item_destroy(hItemInputSel); FREE_MEMORY(hOutMultiLangARR));

	for (nLoopCounter = 0; nLoopCounter < nLoopSize; nLoopCounter++)
	{
		snprintf(ARRBuf, sizeof(ARRBuf), "test string(test) integer(%d) float(0.77)", nLoopCounter);
		PRINT_RESULT_CLEANUP(0, strcmp(hOutMultiLangARR[nLoopCounter], ARRBuf), "noti_ex_multi_lang_create", NotificationExGetError(nRet), noti_ex_item_destroy(hItemInputSel); FREE_MEMORY(hOutMultiLangARR));
	}

	for (nLoopCounter = 0; nLoopCounter < nLoopSize; nLoopCounter++)
	{
		nRet = noti_ex_multi_lang_destroy(hMultiLangARR[nLoopCounter]);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_multi_lang_destroy", NotificationExGetError(nRet));
		FREE_MEMORY(hOutMultiLangARR[nLoopCounter]);
	}

	FREE_MEMORY(hOutMultiLangARR);

	nRet = noti_ex_item_destroy(hItemInputSel);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

