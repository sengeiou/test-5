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
#include "ITs-autofill-common.h"

/** @addtogroup itc-autofill
*  @ingroup itc
*  @{
*/

autofill_hint_e eHint[] = {
		AUTOFILL_HINT_CREDIT_CARD_EXPIRATION_DATE,
		AUTOFILL_HINT_CREDIT_CARD_EXPIRATION_DAY,
		AUTOFILL_HINT_CREDIT_CARD_EXPIRATION_MONTH,
		AUTOFILL_HINT_CREDIT_CARD_EXPIRATION_YEAR,
		AUTOFILL_HINT_CREDIT_CARD_NUMBER,
		AUTOFILL_HINT_EMAIL_ADDRESS,
		AUTOFILL_HINT_NAME,
		AUTOFILL_HINT_PHONE,
		AUTOFILL_HINT_POSTAL_ADDRESS,
		AUTOFILL_HINT_POSTAL_CODE,
		AUTOFILL_HINT_ID,
		AUTOFILL_HINT_PASSWORD,
		AUTOFILL_HINT_CREDIT_CARD_SECURITY_CODE,
};

void ITs_autofill_startup(void)
{
	struct stat stBuff;

	if(stat(ERR_LOG, &stBuff) == 0)
	{
		int nRet = remove(ERR_LOG);
		if(nRet == -1)
		{
			FPRINTF("[Line: %d][%s] unlinking file name error =%s \\n", __LINE__, API_NAMESPACE, ERR_LOG);
			return;
		}
	}

	#if DEBUG
		FPRINTF("[Line: %d][%s] TEST SUIT start-up: ITs_autofill_startup\n", __LINE__, API_NAMESPACE);
	#endif

	return;
}

void ITs_autofill_cleanup(void)
{
	return;
}

/****************************************************Callback Start****************************************************/

/**
* @function 		AutofillFillResponseReceivedCb
* @description	 	Callback Function to receive response.
* @parameters		autofill_h hAutofill, autofill_fill_response_h hAutofillFillResponse, void *user_data
* @return 		NA
*/
void AutofillFillResponseReceivedCb(autofill_h hAutofill, autofill_fill_response_h hAutofillFillResponse, void *user_data)
{
	FPRINTF("[Line: %d][%s] AutofillFillResponseReceivedCb Callback invoked\\n", __LINE__, API_NAMESPACE);
	g_bCallBackHit = true;
	return;
}

/**
* @function 		AutofillAuthInfoReceivedCb
* @description	 	Callback Function to receive auth info.
* @parameters		autofill_h hAutofill, autofill_auth_info_h hAuthInfo, void *user_data
* @return 		NA
*/
void AutofillAuthInfoReceivedCb(autofill_h hAutofill, autofill_auth_info_h hAuthInfo, void *user_data)
{
	FPRINTF("[Line: %d][%s] AutofillAuthInfoReceivedCb Callback invoked\\n", __LINE__, API_NAMESPACE);
	g_bCallBackHit = true;
	return;
}
/**
* @function 		AutofillConnectionStatusChangedCb
* @description	 	Callback Function to receive change status of connection.
* @parameters		autofill_h hAutofill, autofill_connection_status_e eAutofillConnectionStatus, void * user_data
* @return 		NA
*/
void AutofillConnectionStatusChangedCb(autofill_h hAutofill, autofill_connection_status_e eAutofillConnectionStatus, void * user_data)
{
        FPRINTF("[Line: %d][%s] AutofillConnectionStatusChangedCb Callback invoked\\n", __LINE__, API_NAMESPACE);
        g_bCallBackHit = true;
        if (g_mainloop)
        {
                g_main_loop_quit(g_mainloop);
                g_mainloop = NULL;
        }
}
/**
* @function 		AutofillItemCb
* @description	 	Callback Function to check item.
* @parameters		autofill_item_h hItem, void* user_data
* @return 		NA
*/
void AutofillItemCb(autofill_item_h hItem, void* user_data)
{
        FPRINTF("[Line: %d][%s] AutofillItemCb Callback invoked\\n", __LINE__, API_NAMESPACE);
        g_bCallBackHit = true;
        return;
}
/**
* @function 		AutofillSaveItemCb
* @description	 	Callback Function to receive save item.
* @parameters		autofill_save_item_h hSaveItem, void * user_data
* @return 		NA
*/
void AutofillSaveItemCb(autofill_save_item_h hSaveItem, void *user_data)
{
	FPRINTF("[Line: %d][%s] AutofillSaveItemCb Callback invoked\\n", __LINE__, API_NAMESPACE);
        g_bCallBackHit = true;
        return;
}
/**
* @function 		AutofillFillResponseGroupCb
* @description	 	Callback Function to get response.
* @parameters		autofill_fill_response_item_h hFillResponseItem, void *user_data
* @return 		NA
*/
void AutofillFillResponseGroupCb(autofill_fill_response_item_h hFillResponseItem, void *user_data)
{
	FPRINTF("[Line: %d][%s] AutofillFillResponseGroupCb Callback invoked\\n", __LINE__, API_NAMESPACE);
        g_bCallBackHit = true;
        return;
}
/**
* @function 		AutofillFillResponseItemCb
* @description	 	Callback Function to get fill response.
* @parameters		autofill_fill_response_item_h hFillResponseItem, void *user_data
* @return 		NA
*/
void AutofillFillResponseItemCb(autofill_fill_response_item_h hFillResponseItem, void *user_data)
{
	FPRINTF("[Line: %d][%s] AutofillFillResponseItemCb Callback invoked\\n", __LINE__, API_NAMESPACE);
        g_bCallBackHit = true;
        return;
}

/**
* @function 			AutofillErrorInfoReceivedCb
* @description	 		Callback Function to receive Autofill Error info.
* @parameters			autofill_h hAutofill, autofill_error_info_h hAutofillErrorInfo, void *user_data
* @return 			NA
*/
void AutofillErrorInfoReceivedCb(autofill_h hAutofill, autofill_error_info_h hAutofillErrorInfo, void *user_data)
{
	FPRINTF("[Line: %d][%s] %s Callback invoked\\n", __LINE__, API_NAMESPACE, "AutofillErrorInfoReceivedCb");
	return;
}

/****************************************************Callback End***********************************************************/

/**
* @testcase				ITc_autofill_error_info_create_destroy_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Creates and destroys autofill error information.
* @scenario				Creates and destroys autofill error information.
* @apicovered				autofill_error_info_create, autofill_error_info_destroy
* @passcase				autofill_error_info_create, autofill_error_info_destroy return(s) 0
* @failcase				autofill_error_info_create, autofill_error_info_destroy return(s) 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_autofill_error_info_create_destroy_p(void)
{
	START_TEST;

	autofill_error_info_h hAutofillErrorInfo = NULL;
	int nRet = 0;

	nRet = autofill_error_info_create(&hAutofillErrorInfo);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_error_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hAutofillErrorInfo, "autofill_error_info_create");

	nRet = autofill_error_info_destroy(hAutofillErrorInfo);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_error_info_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_error_info_set_get_app_id_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the app id in autofill error information.
* @scenario				Creates the handle and Sets and gets the app id in autofill error information and destroys it.
* @apicovered				autofill_error_info_set_app_id, autofill_error_info_get_app_id
* @passcase				autofill_error_info_set_app_id, autofill_error_info_get_app_id return(s) 0
* @failcase				autofill_error_info_set_app_id, autofill_error_info_get_app_id return(s) 1
* @precondition				autofill_error_info_create
* @postcondition			autofill_error_info_destroy
* */
int ITc_autofill_error_info_set_get_app_id_p(void)
{
	START_TEST;

	autofill_error_info_h hAutofillErrorInfo = NULL;
	char *pszAppId = NULL;
	int nRet = 0;

	nRet = autofill_error_info_create(&hAutofillErrorInfo);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_error_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hAutofillErrorInfo, "autofill_error_info_create");

	nRet = autofill_error_info_set_app_id(hAutofillErrorInfo, g_pszAppId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_error_info_set_app_id", AutofillGetError(nRet), autofill_error_info_destroy(hAutofillErrorInfo));

	nRet = autofill_error_info_get_app_id(hAutofillErrorInfo, &pszAppId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_error_info_get_app_id", AutofillGetError(nRet), autofill_error_info_destroy(hAutofillErrorInfo));
	CHECK_HANDLE_CLEANUP(pszAppId, "autofill_error_info_get_app_id", autofill_error_info_destroy(hAutofillErrorInfo));

	if(0 != strncmp(pszAppId, g_pszAppId, strlen(g_pszAppId)))
	{
		FPRINTF("[Line : %d][%s] autofill_error_info_get_app_id failed.pszAppId = %d\\n", __LINE__, API_NAMESPACE, pszAppId);
		FREE_MEMORY(pszAppId);
		autofill_error_info_destroy(hAutofillErrorInfo);
		return 1;
	}

	FREE_MEMORY(pszAppId);

	nRet = autofill_error_info_destroy(hAutofillErrorInfo);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_error_info_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_error_info_set_get_error_code_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the error code in autofill error information.
* @scenario				Creates handle and Sets and gets all error codes in autofill error information and destroys the handle.
* @apicovered				autofill_error_info_set_error_code, autofill_error_info_get_error_code
* @passcase				autofill_error_info_set_error_code, autofill_error_info_get_error_code return(s) 0
* @failcase				autofill_error_info_set_error_code, autofill_error_info_get_error_code return(s) 1
* @precondition				autofill_error_info_create
* @postcondition			autofill_error_info_destroy
* */
int ITc_autofill_error_info_set_get_error_code_p(void)
{
	START_TEST;

	autofill_error_info_h hAutofillErrorInfo = NULL;
	int nRet = 0;

	autofill_error_e eErrorCodeArr[] = {
		AUTOFILL_ERROR_NONE,
		AUTOFILL_ERROR_INVALID_PARAMETER,
		AUTOFILL_ERROR_PERMISSION_DENIED,
		AUTOFILL_ERROR_NOT_INITIALIZED,
		AUTOFILL_ERROR_OPERATION_FAILED,
		AUTOFILL_ERROR_OUT_OF_MEMORY,
		AUTOFILL_ERROR_AUTHENTICATION_FAILED,
		AUTOFILL_ERROR_COMMIT_FAILED,
		AUTOFILL_ERROR_FILL_RESPONSE_FAILED,
		AUTOFILL_ERROR_SERVICE_NOT_CONNECTED,
		AUTOFILL_ERROR_SERVICE_NOT_ALLOWED,
		AUTOFILL_ERROR_SERVICE_NOT_ACTIVATED,
		AUTOFILL_ERROR_SAVED_VALUES_NOT_FOUND,
	};

	int nErrorCodeSize = sizeof(eErrorCodeArr)/sizeof(eErrorCodeArr[0]);
	autofill_error_e eErrorCode;

	nRet = autofill_error_info_create(&hAutofillErrorInfo);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_error_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hAutofillErrorInfo, "autofill_error_info_create");

	for(int nErrorCodeCounter = 0; nErrorCodeCounter<nErrorCodeSize; nErrorCodeCounter++)
	{

		nRet = autofill_error_info_set_error_code(hAutofillErrorInfo, eErrorCodeArr[nErrorCodeCounter]);
		PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_error_info_set_error_code", AutofillGetError(nRet), autofill_error_info_destroy(hAutofillErrorInfo));

		nRet = autofill_error_info_get_error_code(hAutofillErrorInfo, &eErrorCode);
		PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_error_info_get_error_code", AutofillGetError(nRet), autofill_error_info_destroy(hAutofillErrorInfo));

		if( eErrorCode != eErrorCodeArr[nErrorCodeCounter])
		{
			FPRINTF("[Line : %d][%s] autofill_error_info_get_error_code failed. eErrorCode = %d\\n", __LINE__, API_NAMESPACE, eErrorCode);
			autofill_error_info_destroy(hAutofillErrorInfo);
			return 1;
		}
	}

	nRet = autofill_error_info_destroy(hAutofillErrorInfo);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_error_info_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_error_info_set_unset_received_cb_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and unsets the callback to receive the error information.
* @scenario				Creates handle and Sets and unsets the callback to receive the error information then destroys it.
* @apicovered				autofill_error_info_set_received_cb, autofill_error_info_unset_received_cb
* @passcase				autofill_error_info_set_received_cb, autofill_error_info_unset_received_cb return(s) 0
* @failcase				autofill_error_info_set_received_cb, autofill_error_info_unset_received_cb return(s) 1
* @precondition				autofill_create
* @postcondition			autofill_destroy
* */
int ITc_autofill_error_info_set_unset_received_cb_p(void)
{
	START_TEST;

	autofill_h hAutofill = NULL;
	int nRet = 0;

	nRet = autofill_create(&hAutofill);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_create", AutofillGetError(nRet));
	CHECK_HANDLE(hAutofill, "autofill_create");

	nRet = autofill_error_info_set_received_cb(hAutofill, AutofillErrorInfoReceivedCb, NULL);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_error_info_set_received_cb", AutofillGetError(nRet), autofill_destroy(hAutofill));

	nRet = autofill_error_info_unset_received_cb(hAutofill);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_error_info_unset_received_cb", AutofillGetError(nRet), autofill_destroy(hAutofill));

	nRet = autofill_destroy(hAutofill);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_destroy", AutofillGetError(nRet));

	return 0;
}
/**
* @testcase				ITc_autofill_item_create_destroy_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Creates and destroys an autofill item.
* @scenario				Creates and destroys an autofill item.
* @apicovered				autofill_item_create, autofill_item_destroy
* @passcase				autofill_item_create, autofill_item_destroy return(s) 0
* @failcase				autofill_item_create, autofill_item_destroy return(s) 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_autofill_item_create_destroy_p(void)
{
	START_TEST;

	autofill_item_h hItem = NULL;
	int nRet = 0;

	nRet = autofill_item_create(&hItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hItem, "autofill_item_create");

	nRet = autofill_item_destroy(hItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_item_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_item_clone_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Checks the Cloning of an autofill item.
* @scenario				Creates a handle then clones it to an autofill item and destroys handle.
* @apicovered				autofill_item_clone
* @passcase				autofill_item_clone return(s) 0
* @failcase				autofill_item_clone return(s) 1
* @precondition				autofill_item_create
* @postcondition			autofill_item_destroy
* */
int ITc_autofill_item_clone_p(void)
{
	START_TEST;

	autofill_item_h hItem = NULL;
	autofill_item_h hItemClone = NULL;
	int nRet = 0;

	nRet = autofill_item_create(&hItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hItem, "autofill_item_create");

	nRet = autofill_item_clone(hItem, &hItemClone);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_item_clone", AutofillGetError(nRet),autofill_item_destroy(hItem));
	CHECK_HANDLE_CLEANUP(hItemClone, "autofill_item_clone",autofill_item_destroy(hItem));
	FREE_MEMORY(hItemClone);

	nRet = autofill_item_destroy(hItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_item_destroy", AutofillGetError(nRet));

	return 0;
}
/**
* @testcase				ITc_autofill_item_set_get_autofill_hint_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the autofill hint (id (username), name, password, phone, credit card number, organization, so on) in an autofill item.
* @scenario				Creates handle then Sets and gets the autofill hint (id (username), name, password, phone, credit card number, organization, so on) in an autofill item and destroys it.
* @apicovered				autofill_item_set_autofill_hint, autofill_item_get_autofill_hint
* @passcase				autofill_item_set_autofill_hint, autofill_item_get_autofill_hint return(s) 0
* @failcase				autofill_item_set_autofill_hint, autofill_item_get_autofill_hint return(s) 1
* @precondition				autofill_item_create
* @postcondition			autofill_item_destroy
* */
int ITc_autofill_item_set_get_autofill_hint_p(void)
{
	START_TEST;

	autofill_item_h hItem = NULL;
	autofill_hint_e eHintAutofill;

	int enum_size = sizeof(eHint) / sizeof(eHint[0]);
	int enum_counter = 0;
	int nRet = 0;

	nRet = autofill_item_create(&hItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hItem, "autofill_item_create");

	for ( enum_counter=0;enum_counter<enum_size;enum_counter++)
	{
		autofill_hint_e eHintAutofillTest = eHint[enum_counter];

		nRet = autofill_item_set_autofill_hint(hItem, eHintAutofillTest);
		PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_item_set_autofill_hint", AutofillGetError(nRet),autofill_item_destroy(hItem));

		nRet = autofill_item_get_autofill_hint(hItem, &eHintAutofill);
		PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_item_get_autofill_hint", AutofillGetError(nRet),autofill_item_destroy(hItem));

		if( eHintAutofill != eHintAutofillTest)
		{
			FPRINTF("[Line : %d][%s] autofill_item_get_autofill_hint failed for %d. eHintAutofill = %d\\n", __LINE__, API_NAMESPACE, eHintAutofillTest, eHintAutofill);
			autofill_item_destroy(hItem);
			return 1;
		}
	}

	nRet = autofill_item_destroy(hItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_item_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_item_set_get_id_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the autofill ID in an autofill item.
* @scenario				Creates handle and sets and gets the autofill ID in an autofill item then destroys the handle.
* @apicovered				autofill_item_set_id, autofill_item_get_id
* @passcase				autofill_item_set_id, autofill_item_get_id return(s) 0
* @failcase				autofill_item_set_id, autofill_item_get_id return(s) 1
* @precondition				autofill_item_create
* @postcondition			autofill_item_destroy
* */
int ITc_autofill_item_set_get_id_p(void)
{
	START_TEST;

	autofill_item_h hItem = NULL;
	char *pszId= NULL;
	int nRet = 0;

	nRet = autofill_item_create(&hItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hItem, "autofill_item_create");

	nRet = autofill_item_set_id(hItem, g_pszId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_item_set_id", AutofillGetError(nRet), autofill_item_destroy(hItem));

	nRet = autofill_item_get_id(hItem, &pszId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_item_get_id", AutofillGetError(nRet), autofill_item_destroy(hItem));
	CHECK_HANDLE_CLEANUP(pszId, "autofill_item_get_id", autofill_item_destroy(hItem));

	if ( 0 != strncmp(pszId, g_pszId, strlen(g_pszId)) )
	{
		FPRINTF("[Line : %d][%s] autofill_item_get_id failed for pszId = %s\\n", __LINE__, API_NAMESPACE, pszId);
		FREE_MEMORY(pszId);
		autofill_item_destroy(hItem);
		return 1;
	}
	FREE_MEMORY(pszId);
	nRet = autofill_item_destroy(hItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_item_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_item_set_get_label_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the autofill label in an autofill item.
* @scenario				Creates handle and Sets and gets the autofill label in an autofill item then destroys handle.
* @apicovered				autofill_item_set_label, autofill_item_get_label
* @passcase				autofill_item_set_label, autofill_item_get_label return(s) 0
* @failcase				autofill_item_set_label, autofill_item_get_label return(s) 1
* @precondition				autofill_item_create
* @postcondition			autofill_item_destroy
* */
int ITc_autofill_item_set_get_label_p(void)
{
	START_TEST;

	autofill_item_h hItem = NULL;
	char *pszLabel= NULL;
	int nRet = 0;

	nRet = autofill_item_create(&hItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hItem, "autofill_item_create");

	nRet = autofill_item_set_label(hItem, g_pszLabel);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_item_set_label", AutofillGetError(nRet), autofill_item_destroy(hItem));

	nRet = autofill_item_get_label(hItem, &pszLabel);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_item_get_label", AutofillGetError(nRet), autofill_item_destroy(hItem));
	CHECK_HANDLE_CLEANUP(pszLabel, "autofill_item_get_label", autofill_item_destroy(hItem));

	if ( 0 != strncmp(pszLabel, g_pszLabel, strlen(g_pszLabel)) )
	{
		FPRINTF("[Line : %d][%s] autofill_item_get_label failed for pszLabel = %s\\n", __LINE__, API_NAMESPACE, pszLabel);
		FREE_MEMORY(pszLabel);
		autofill_item_destroy(hItem);
		return 1;
	}
	FREE_MEMORY(pszLabel);
	nRet = autofill_item_destroy(hItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_item_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase                             ITc_autofill_item_set_get_sensitive_data_p
* @since_tizen                          5.5
* @author                               SRID(p.chauhan)
* @reviewer                             SRID(nibha.sharma)
* @type                                 auto
* @description                          Sets and gets the sensitive data in an autofill item.
* @scenario                             Creates handle and Sets and gets the sensitive data in an autofill item then destroys handle.
* @apicovered                           autofill_item_set_sensitive_data, autofill_item_get_sensitive_data
* @passcase                             autofill_item_set_sensitive_data, autofill_item_get_sensitive_data return(s) 0
* @failcase                             autofill_item_set_sensitive_data, autofill_item_get_sensitive_data return(s) 1
* @precondition                         autofill_item_create
* @postcondition                        autofill_item_destroy
* */
int ITc_autofill_item_set_get_sensitive_data_p(void)
{
        START_TEST;

        autofill_item_h hItem = NULL;
	bool bSensitive = false;
        int nRet = 0;

	nRet = autofill_item_create(&hItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hItem, "autofill_item_create");

        nRet = autofill_item_set_sensitive_data(hItem,g_bSensitive);
        PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_item_set_sensitive_data", AutofillGetError(nRet),autofill_item_destroy(hItem));

        nRet = autofill_item_get_sensitive_data(hItem, &bSensitive);
        PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_item_get_sensitive_data", AutofillGetError(nRet),autofill_item_destroy(hItem));
	if( bSensitive != g_bSensitive)
        {
                FPRINTF("[Line : %d][%s] autofill_item_get_sensitive_data failed for bSensitive = %d\\n", __LINE__, API_NAMESPACE, bSensitive);
		autofill_item_destroy(hItem);
                return 1;
        }
	nRet = autofill_item_destroy(hItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_item_destroy", AutofillGetError(nRet));

        return 0;
}
/**
* @testcase                             ITc_autofill_item_set_get_value_p
* @since_tizen                          5.5
* @author                               SRID(p.chauhan)
* @reviewer                             SRID(nibha.sharma)
* @type                                 auto
* @description                          Sets and gets the autofill value in an autofill item.
* @scenario                             Creates handle and Sets and gets the autofill value in an autofill item then destroys handle.
* @apicovered                           autofill_item_set_value, autofill_item_get_value
* @passcase                             autofill_item_set_value, autofill_item_get_value return(s) 0
* @failcase                             autofill_item_set_value, autofill_item_get_value return(s) 1
* @precondition                         autofill_item_create
* @postcondition                        autofill_item_destroy
* */
int ITc_autofill_item_set_get_value_p(void)
{
        START_TEST;

        autofill_item_h hItem = NULL;
	char *pszValue= NULL;
        int nRet = 0;

	nRet = autofill_item_create(&hItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hItem, "autofill_item_create");

        nRet = autofill_item_set_value(hItem, g_pszValue);
        PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_item_set_value", AutofillGetError(nRet), autofill_item_destroy(hItem));

        nRet = autofill_item_get_value(hItem, &pszValue);
        PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_item_get_value", AutofillGetError(nRet), autofill_item_destroy(hItem));
        CHECK_HANDLE_CLEANUP(pszValue, "autofill_item_get_value", autofill_item_destroy(hItem));

	if ( 0 != strncmp(pszValue, g_pszValue, strlen(g_pszValue)) )
        {
                FPRINTF("[Line : %d][%s] autofill_item_get_value failed for pszValue = %s\\n", __LINE__, API_NAMESPACE, pszValue);
		FREE_MEMORY(pszValue);
		autofill_item_destroy(hItem);
                return 1;
        }
        FREE_MEMORY(pszValue);
	nRet = autofill_item_destroy(hItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_item_destroy", AutofillGetError(nRet));

        return 0;
}

/**
* @testcase                             ITc_autofill_auth_info_create_destroy_p
* @since_tizen                          5.5
* @author                               SRID(p.chauhan)
* @reviewer                             SRID(nibha.sharma)
* @type                                 auto
* @description                          Creates and destroys autofill authentication information.
* @scenario                             Creates handle and Creates and destroys autofill authentication information then destroys handle.
* @apicovered                           autofill_auth_info_create, autofill_auth_info_destroy
* @passcase                             autofill_auth_info_create, autofill_auth_info_destroy return(s) 0
* @failcase                             autofill_auth_info_create, autofill_auth_info_destroy return(s) 1
* @precondition                         N/A
* @postcondition                        N/A
* */
int ITc_autofill_auth_info_create_destroy_p(void)
{
        START_TEST;

        autofill_auth_info_h hAuthInfo = NULL;
        int nRet = 0;

        nRet = autofill_auth_info_create(&hAuthInfo);
        PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hAuthInfo, "autofill_auth_info_create");

        nRet = autofill_auth_info_destroy(hAuthInfo);
        PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_destroy", AutofillGetError(nRet));

        return 0;
}

/**
* @testcase                             ITc_autofill_auth_info_set_get_app_id_p
* @since_tizen                          5.5
* @author                               SRID(p.chauhan)
* @reviewer                             SRID(nibha.sharma)
* @type                                 auto
* @description                          Sets and gets the app id in autofill authentication information.
* @scenario                             Creates handle and Sets and gets the app id in autofill authentication information then destroys handle.
* @apicovered                           autofill_auth_info_set_app_id, autofill_auth_info_get_app_id
* @passcase                             autofill_auth_info_set_app_id, autofill_auth_info_get_app_id return(s) 0
* @failcase                             autofill_auth_info_set_app_id, autofill_auth_info_get_app_id return(s) 1
* @precondition                         autofill_auth_info_create
* @postcondition                        autofill_auth_info_destroy
* */
int ITc_autofill_auth_info_set_get_app_id_p(void)
{
        START_TEST;

        autofill_auth_info_h hAuthInfo = NULL;
	char *pszAppId= NULL;
        int nRet = 0;

        nRet = autofill_auth_info_create(&hAuthInfo);
        PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hAuthInfo, "autofill_auth_info_create");

        nRet = autofill_auth_info_set_app_id(hAuthInfo, g_pszAppId);
        PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_set_app_id", AutofillGetError(nRet), autofill_auth_info_destroy(hAuthInfo));

        nRet = autofill_auth_info_get_app_id(hAuthInfo, &pszAppId);
        PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_get_app_id", AutofillGetError(nRet), autofill_auth_info_destroy(hAuthInfo));
        CHECK_HANDLE_CLEANUP(pszAppId, "autofill_auth_info_get_app_id", autofill_auth_info_destroy(hAuthInfo));

	if ( 0 != strncmp(pszAppId, g_pszAppId, strlen(g_pszAppId)) )
        {
                FPRINTF("[Line : %d][%s] autofill_auth_info_get_app_id failed for pszAppId = %s\\n", __LINE__, API_NAMESPACE, pszAppId);
	        autofill_auth_info_destroy(hAuthInfo);
                return 1;
        }
        FREE_MEMORY(pszAppId);
        nRet = autofill_auth_info_destroy(hAuthInfo);
        PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_destroy", AutofillGetError(nRet));

        return 0;
}

/**
* @testcase                             ITc_autofill_auth_info_set_get_view_id_p
* @since_tizen                          5.5
* @author                               SRID(p.chauhan)
* @reviewer                             SRID(nibha.sharma)
* @type                                 auto
* @description                          Sets and gets the view id in autofill authentication information.
* @scenario                             Creates handle and Sets and gets the view id in autofill authentication information then destroys handle.
* @apicovered                           autofill_auth_info_set_view_id, autofill_auth_info_get_view_id
* @passcase                             autofill_auth_info_set_view_id, autofill_auth_info_get_view_id return(s) 0
* @failcase                             autofill_auth_info_set_view_id, autofill_auth_info_get_view_id return(s) 1
* @precondition                         autofill_auth_info_create
* @postcondition                        autofill_auth_info_destroy
* */
int ITc_autofill_auth_info_set_get_view_id_p(void)
{
        START_TEST;

        autofill_auth_info_h hAuthInfo = NULL;
	char *pszViewId= NULL;
        int nRet = 0;

        nRet = autofill_auth_info_create(&hAuthInfo);
        PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hAuthInfo, "autofill_auth_info_create");

        nRet = autofill_auth_info_set_view_id(hAuthInfo, g_pszViewId);
        PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_set_view_id", AutofillGetError(nRet), autofill_auth_info_destroy(hAuthInfo));

        nRet = autofill_auth_info_get_view_id(hAuthInfo, &pszViewId);
        PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_get_view_id", AutofillGetError(nRet), autofill_auth_info_destroy(hAuthInfo));
        CHECK_HANDLE_CLEANUP(pszViewId, "autofill_auth_info_get_view_id", autofill_auth_info_destroy(hAuthInfo));

	if ( 0 !=strncmp(pszViewId, g_pszViewId, strlen(g_pszViewId)) )
        {
                FPRINTF("[Line : %d][%s] autofill_auth_info_get_view_id failed for pszViewId = %s\\n", __LINE__, API_NAMESPACE, pszViewId);
                FREE_MEMORY(pszViewId);
	        autofill_auth_info_destroy(hAuthInfo);
                return 1;
        }
        FREE_MEMORY(pszViewId);
        nRet = autofill_auth_info_destroy(hAuthInfo);
        PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_destroy", AutofillGetError(nRet));

        return 0;
}


/**
* @testcase                             ITc_autofill_auth_info_set_get_autofill_data_present_p
* @since_tizen                          5.5
* @author                               SRID(p.chauhan)
* @reviewer                             SRID(nibha.sharma)
* @type                                 auto
* @description                          Sets and gets the 'autofill data present' attribute in autofill authentication information.
* @scenario                             Creates handle and Sets and gets the 'autofill data present' attribute in autofill authentication information then destroys handle.
* @apicovered                           autofill_auth_info_set_autofill_data_present, autofill_auth_info_get_autofill_data_present
* @passcase                             autofill_auth_info_set_autofill_data_present, autofill_auth_info_get_autofill_data_present return(s) 0
* @failcase                             autofill_auth_info_set_autofill_data_present, autofill_auth_info_get_autofill_data_present return(s) 1
* @precondition                         autofill_auth_info_create
* @postcondition                        autofill_auth_info_destroy
* */
int ITc_autofill_auth_info_set_get_autofill_data_present_p(void)
{
        START_TEST;

        autofill_auth_info_h hAuthInfo = NULL;
	bool bAutofillDataPresent = false;
        int nRet = 0;

        nRet = autofill_auth_info_create(&hAuthInfo);
        PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hAuthInfo, "autofill_auth_info_create");

        nRet = autofill_auth_info_set_autofill_data_present(hAuthInfo, g_bAutofillDataPresent);
        PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_set_autofill_data_present", AutofillGetError(nRet),autofill_auth_info_destroy(hAuthInfo));

        nRet = autofill_auth_info_get_autofill_data_present(hAuthInfo, &bAutofillDataPresent);
        PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_get_autofill_data_present", AutofillGetError(nRet),autofill_auth_info_destroy(hAuthInfo));
	if( bAutofillDataPresent != g_bAutofillDataPresent)
        {
                FPRINTF("[Line : %d][%s] autofill_auth_info_get_autofill_data_present failed for bAutofillDataPresent = %d\\n", __LINE__, API_NAMESPACE, bAutofillDataPresent);
	        autofill_auth_info_destroy(hAuthInfo);
                return 1;
        }
        nRet = autofill_auth_info_destroy(hAuthInfo);
        PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_destroy", AutofillGetError(nRet));

        return 0;
}

/**
* @testcase                             ITc_autofill_auth_info_set_get_authentication_needed_p
* @since_tizen                          5.5
* @author                               SRID(p.chauhan)
* @reviewer                             SRID(nibha.sharma)
* @type                                 auto
* @description                          Sets and gets the 'authentication needed' attribute in autofill authentication information.
* @scenario                             Creates handle and Sets and gets the 'authentication needed' attribute in autofill authentication information then destroys handle.
* @apicovered                           autofill_auth_info_set_authentication_needed, autofill_auth_info_get_authentication_needed
* @passcase                             autofill_auth_info_set_authentication_needed, autofill_auth_info_get_authentication_needed return(s) 0
* @failcase                             autofill_auth_info_set_authentication_needed, autofill_auth_info_get_authentication_needed return(s) 1
* @precondition                         autofill_auth_info_create
* @postcondition                        autofill_auth_info_destroy
* */
int ITc_autofill_auth_info_set_get_authentication_needed_p(void)
{
        START_TEST;

        autofill_auth_info_h hAuthInfo = NULL;
	bool bAuthenticationNeeded = false;

        int nRet = 0;

        nRet = autofill_auth_info_create(&hAuthInfo);
        PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hAuthInfo, "autofill_auth_info_create");

        nRet = autofill_auth_info_set_authentication_needed(hAuthInfo, g_bAuthenticationNeeded);
        PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_set_authentication_needed", AutofillGetError(nRet),autofill_auth_info_destroy(hAuthInfo));

        nRet = autofill_auth_info_get_authentication_needed(hAuthInfo, &bAuthenticationNeeded);
        PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_get_authentication_needed", AutofillGetError(nRet),autofill_auth_info_destroy(hAuthInfo));
	if( bAuthenticationNeeded != g_bAuthenticationNeeded )
        {
                FPRINTF("[Line : %d][%s] autofill_auth_info_get_authentication_needed failed for bAuthenticationNeeded = %d\\n", __LINE__, API_NAMESPACE, bAuthenticationNeeded);
	        autofill_auth_info_destroy(hAuthInfo);
                return 1;
        }
        nRet = autofill_auth_info_destroy(hAuthInfo);
        PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_destroy", AutofillGetError(nRet));

        return 0;
}

/**
* @testcase				ITc_autofill_auth_info_set_get_service_name_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the service name in autofill authentication information.
* @scenario				Creates handle and Sets and gets the service name in autofill authentication information then destroys handle.
* @apicovered				autofill_auth_info_set_service_name, autofill_auth_info_get_service_name
* @passcase				autofill_auth_info_set_service_name, autofill_auth_info_get_service_name return(s) 0
* @failcase				autofill_auth_info_set_service_name, autofill_auth_info_get_service_name return(s) 1
* @precondition				autofill_auth_info_create
* @postcondition			autofill_auth_info_destroy
* */
int ITc_autofill_auth_info_set_get_service_name_p(void)
{
	START_TEST;

	autofill_auth_info_h hAuthInfo = NULL;
	char *pszServiceName= NULL;
	int nRet = 0;

        nRet = autofill_auth_info_create(&hAuthInfo);
        PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hAuthInfo, "autofill_auth_info_create");

	nRet = autofill_auth_info_set_service_name(hAuthInfo, g_pszServiceName);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_set_service_name", AutofillGetError(nRet), autofill_auth_info_destroy(hAuthInfo));

	nRet = autofill_auth_info_get_service_name(hAuthInfo, &pszServiceName);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_get_service_name", AutofillGetError(nRet), autofill_auth_info_destroy(hAuthInfo));
	CHECK_HANDLE_CLEANUP(pszServiceName, "autofill_auth_info_get_service_name", autofill_auth_info_destroy(hAuthInfo));

	if ( 0 != strncmp(pszServiceName, g_pszServiceName, strlen(g_pszServiceName)) )
        {
                FPRINTF("[Line : %d][%s] autofill_auth_info_get_service_name failed for pszServiceName = %s\\n", __LINE__, API_NAMESPACE, pszServiceName);
                FREE_MEMORY(pszServiceName);
	        autofill_auth_info_destroy(hAuthInfo);
                return 1;
        }

	FREE_MEMORY(pszServiceName);
        nRet = autofill_auth_info_destroy(hAuthInfo);
        PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_auth_info_set_get_service_message_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the service message in autofill authentication information.
* @scenario				Creates handle and Sets and gets the service message in autofill authentication information then destroys handle.
* @apicovered				autofill_auth_info_set_service_message, autofill_auth_info_get_service_message
* @passcase				autofill_auth_info_set_service_message, autofill_auth_info_get_service_message return(s) 0
* @failcase				autofill_auth_info_set_service_message, autofill_auth_info_get_service_message return(s) 1
* @precondition				autofill_auth_info_create
* @postcondition			autofill_auth_info_destroy
* */
int ITc_autofill_auth_info_set_get_service_message_p(void)
{
	START_TEST;

	autofill_auth_info_h hAuthInfo = NULL;
	char *pszServiceMessage= NULL;
	int nRet = 0;

        nRet = autofill_auth_info_create(&hAuthInfo);
        PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hAuthInfo, "autofill_auth_info_create");

	nRet = autofill_auth_info_set_service_message(hAuthInfo, g_pszServiceMessage);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_set_service_message", AutofillGetError(nRet), autofill_auth_info_destroy(hAuthInfo));

	nRet = autofill_auth_info_get_service_message(hAuthInfo, &pszServiceMessage);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_get_service_message", AutofillGetError(nRet), autofill_auth_info_destroy(hAuthInfo));
	CHECK_HANDLE_CLEANUP(pszServiceMessage, "autofill_auth_info_get_service_message", autofill_auth_info_destroy(hAuthInfo));

	if ( 0 != strncmp(pszServiceMessage, g_pszServiceMessage, strlen(g_pszServiceMessage)) )
        {
                FPRINTF("[Line : %d][%s] autofill_auth_info_get_service_message failed for pszServiceMessage = %s\\n", __LINE__, API_NAMESPACE, pszServiceMessage);
                FREE_MEMORY(pszServiceMessage);
	        autofill_auth_info_destroy(hAuthInfo);
                return 1;
        }
	FREE_MEMORY(pszServiceMessage);
        nRet = autofill_auth_info_destroy(hAuthInfo);
        PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_auth_info_set_get_service_logo_image_path_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the service logo image path in autofill authentication information.
* @scenario				Creates handle and Sets and gets the service logo image path in autofill authentication information then destroys handle.
* @apicovered				autofill_auth_info_set_service_logo_image_path, autofill_auth_info_get_service_logo_image_path
* @passcase				autofill_auth_info_set_service_logo_image_path, autofill_auth_info_get_service_logo_image_path return(s) 0
* @failcase				autofill_auth_info_set_service_logo_image_path, autofill_auth_info_get_service_logo_image_path return(s) 1
* @precondition				autofill_auth_info_create
* @postcondition			autofill_auth_info_destroy
* */
int ITc_autofill_auth_info_set_get_service_logo_image_path_p(void)
{
	START_TEST;

	autofill_auth_info_h hAuthInfo = NULL;
	char *pszServiceLogoImagePath= NULL;
	int nRet = 0;
	char pszServiceLogoImagePathTest[PATH_LEN] = {0,};

	if( false == ApplicationGetDataPath(pszServiceLogoImagePathTest))
	{
		return 1;
	}

        nRet = autofill_auth_info_create(&hAuthInfo);
        PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hAuthInfo, "autofill_auth_info_create");

	nRet = autofill_auth_info_set_service_logo_image_path(hAuthInfo, pszServiceLogoImagePathTest);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_set_service_logo_image_path", AutofillGetError(nRet), autofill_auth_info_destroy(hAuthInfo));

	nRet = autofill_auth_info_get_service_logo_image_path(hAuthInfo, &pszServiceLogoImagePath);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_get_service_logo_image_path", AutofillGetError(nRet), autofill_auth_info_destroy(hAuthInfo));
	CHECK_HANDLE_CLEANUP(pszServiceLogoImagePath, "autofill_auth_info_get_service_logo_image_path", autofill_auth_info_destroy(hAuthInfo));

	if ( 0 != strncmp(pszServiceLogoImagePath, pszServiceLogoImagePathTest, strlen(pszServiceLogoImagePathTest)) )
        {
                FPRINTF("[Line : %d][%s] autofill_auth_info_get_service_logo_image_path failed for pszServiceLogoImagePath = %s\\n", __LINE__, API_NAMESPACE, pszServiceLogoImagePath);
                FREE_MEMORY(pszServiceLogoImagePath);
	        autofill_auth_info_destroy(hAuthInfo);
                return 1;
        }
	FREE_MEMORY(pszServiceLogoImagePath);

        nRet = autofill_auth_info_destroy(hAuthInfo);
        PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_destroy", AutofillGetError(nRet));

	return 0;
}


/**
* @testcase				ITc_autofill_view_info_create_destroy_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Creates and destroys autofill view information.
* @scenario				Creates and destroys autofill view information.
* @apicovered				autofill_view_info_create, autofill_view_info_destroy
* @passcase				autofill_view_info_create, autofill_view_info_destroy return(s) 0
* @failcase				autofill_view_info_create, autofill_view_info_destroy return(s) 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_autofill_view_info_create_destroy_p(void)
{
	START_TEST;

	autofill_view_info_h hViewInfo = NULL;
	int nRet = 0;

	nRet = autofill_view_info_create(&hViewInfo);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hViewInfo, "autofill_view_info_create");

	nRet = autofill_view_info_destroy(hViewInfo);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_destroy", AutofillGetError(nRet));

	return 0;
}


/**
* @testcase				ITc_autofill_view_info_set_get_app_id_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the app id in autofill view information.
* @scenario				Creates handle and Sets and gets the app id in autofill view information then destroys handle.
* @apicovered				autofill_view_info_set_app_id, autofill_view_info_get_app_id
* @passcase				autofill_view_info_set_app_id, autofill_view_info_get_app_id return(s) 0
* @failcase				autofill_view_info_set_app_id, autofill_view_info_get_app_id return(s) 1
* @precondition				autofill_view_info_create
* @postcondition			autofill_view_info_destroy
* */
int ITc_autofill_view_info_set_get_app_id_p(void)
{
	START_TEST;

	autofill_view_info_h hViewInfo = NULL;
	char* pszAppId = NULL;
	int nRet = 0;

	nRet = autofill_view_info_create(&hViewInfo);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hViewInfo, "autofill_view_info_create");

	nRet = autofill_view_info_set_app_id(hViewInfo, g_pszAppId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_set_app_id", AutofillGetError(nRet), autofill_view_info_destroy(hViewInfo));

	nRet = autofill_view_info_get_app_id(hViewInfo, &pszAppId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_get_app_id", AutofillGetError(nRet), autofill_view_info_destroy(hViewInfo));
	CHECK_HANDLE_CLEANUP(pszAppId, "autofill_view_info_get_app_id", autofill_view_info_destroy(hViewInfo));

	if ( 0 != strncmp(pszAppId, g_pszAppId, strlen(g_pszAppId)) )
        {
                FPRINTF("[Line : %d][%s] autofill_view_info_get_app_id failed for pszAppId = %s\\n", __LINE__, API_NAMESPACE, pszAppId);
                FREE_MEMORY(pszAppId);
		autofill_view_info_destroy(hViewInfo);
                return 1;
        }

	FREE_MEMORY(pszAppId);

	nRet = autofill_view_info_destroy(hViewInfo);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_view_info_set_get_view_id_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the view id in autofill view information.
* @scenario				Creates handle and Sets and gets the view id in autofill view information then destroys handle.
* @apicovered				autofill_view_info_set_view_id, autofill_view_info_get_view_id
* @passcase				autofill_view_info_set_view_id, autofill_view_info_get_view_id return(s) 0
* @failcase				autofill_view_info_set_view_id, autofill_view_info_get_view_id return(s) 1
* @precondition				autofill_view_info_create
* @postcondition			autofill_view_info_destroy
* */
int ITc_autofill_view_info_set_get_view_id_p(void)
{
	START_TEST;

	autofill_view_info_h hViewInfo = NULL;
	char *pszViewId= NULL;
	int nRet = 0;

	nRet = autofill_view_info_create(&hViewInfo);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hViewInfo, "autofill_view_info_create");

	nRet = autofill_view_info_set_view_id(hViewInfo, g_pszViewId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_set_view_id", AutofillGetError(nRet), autofill_view_info_destroy(hViewInfo));

	nRet = autofill_view_info_get_view_id(hViewInfo, &pszViewId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_get_view_id", AutofillGetError(nRet), autofill_view_info_destroy(hViewInfo));
	CHECK_HANDLE_CLEANUP(pszViewId, "autofill_view_info_get_view_id", autofill_view_info_destroy(hViewInfo));

	if ( 0 != strncmp(pszViewId, g_pszViewId, strlen(g_pszViewId)) )
        {
                FPRINTF("[Line : %d][%s] autofill_view_info_get_view_id failed for pszViewId = %s\\n", __LINE__, API_NAMESPACE, pszViewId);
                FREE_MEMORY(pszViewId);
		autofill_view_info_destroy(hViewInfo);
                return 1;
        }
	FREE_MEMORY(pszViewId);
	nRet = autofill_view_info_destroy(hViewInfo);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_view_info_add_item_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Adds autofill item in autofill view information.
* @scenario				Creates handle and Adds autofill item in autofill view information then destroys handle.
* @apicovered				autofill_view_info_add_item
* @passcase				autofill_view_info_add_item return(s) 0
* @failcase				autofill_view_info_add_item return(s) 1
* @precondition				autofill_view_info_create,autofill_view_info_create
* @postcondition			autofill_view_info_destroy, autofill_view_info_destroy
* */
int ITc_autofill_view_info_add_item_p(void)
{
	START_TEST;

	autofill_view_info_h hViewInfo = NULL;
	autofill_item_h hItem = NULL;
	int nRet = 0;

	nRet = autofill_item_create(&hItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hItem, "autofill_item_create");

	nRet = autofill_view_info_create(&hViewInfo);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_create", AutofillGetError(nRet), autofill_item_destroy(hItem));
	CHECK_HANDLE_CLEANUP(hViewInfo, "autofill_view_info_create", autofill_item_destroy(hItem));

	nRet = autofill_view_info_add_item(hViewInfo, hItem);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_add_item", AutofillGetError(nRet), autofill_view_info_destroy(hViewInfo);autofill_item_destroy(hItem));

	nRet = autofill_view_info_destroy(hViewInfo);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_destroy", AutofillGetError(nRet));

	nRet = autofill_item_destroy(hItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_item_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_view_info_foreach_item_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Retrieves all items in autofill view information.
* @scenario				Creates handle and Retrieves all items in autofill view information then destroys handle.
* @apicovered				autofill_view_info_foreach_item
* @passcase				autofill_view_info_foreach_item return(s) 0
* @failcase				autofill_view_info_foreach_item return(s) 1
* @precondition				autofill_view_info_create
* @postcondition			autofill_view_info_destroy
* */
int ITc_autofill_view_info_foreach_item_p(void)
{
	START_TEST;

	autofill_view_info_h hViewInfo = NULL;
	int nRet = 0;

	nRet = autofill_view_info_create(&hViewInfo);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hViewInfo, "autofill_view_info_create");

	nRet = autofill_view_info_foreach_item(hViewInfo, AutofillItemCb, NULL);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_foreach_item", AutofillGetError(nRet), autofill_view_info_destroy(hViewInfo));

	nRet = autofill_view_info_destroy(hViewInfo);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_destroy", AutofillGetError(nRet));
	return 0;
}

/**
* @testcase				ITc_autofill_save_view_info_create_destroy_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Creates and destroys autofill save view information.
* @scenario				Creates and destroys autofill save view information.
* @apicovered				autofill_save_view_info_create, autofill_save_view_info_destroy
* @passcase				autofill_save_view_info_create, autofill_save_view_info_destroy return(s) 0
* @failcase				autofill_save_view_info_create, autofill_save_view_info_destroy return(s) 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_autofill_save_view_info_create_destroy_p(void)
{
	START_TEST;

	autofill_save_view_info_h hSaveViewInfo = NULL;
	int nRet = 0;

	nRet = autofill_save_view_info_create(&hSaveViewInfo);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hSaveViewInfo, "autofill_save_view_info_create");

	nRet = autofill_save_view_info_destroy(hSaveViewInfo);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_save_view_info_set_get_app_id_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the app ID in autofill save view information.
* @scenario				Creates handle and Sets and gets the app ID in autofill save view information then destroys handle.
* @apicovered				autofill_save_view_info_set_app_id, autofill_save_view_info_get_app_id
* @passcase				autofill_save_view_info_set_app_id, autofill_save_view_info_get_app_id return(s) 0
* @failcase				autofill_save_view_info_set_app_id, autofill_save_view_info_get_app_id return(s) 1
* @precondition				autofill_save_view_info_create
* @postcondition			autofill_save_view_info_destroy
* */
int ITc_autofill_save_view_info_set_get_app_id_p(void)
{
	START_TEST;

	autofill_save_view_info_h hSaveViewInfo = NULL;
	char *pszAppId= NULL;
	int nRet = 0;

	nRet = autofill_save_view_info_create(&hSaveViewInfo);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hSaveViewInfo, "autofill_save_view_info_create");

	nRet = autofill_save_view_info_set_app_id(hSaveViewInfo, g_pszAppId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_set_app_id", AutofillGetError(nRet), autofill_save_view_info_destroy(hSaveViewInfo));

	nRet = autofill_save_view_info_get_app_id(hSaveViewInfo, &pszAppId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_get_app_id", AutofillGetError(nRet), autofill_save_view_info_destroy(hSaveViewInfo));
	CHECK_HANDLE_CLEANUP(pszAppId, "autofill_save_view_info_get_app_id", autofill_save_view_info_destroy(hSaveViewInfo));

	if ( 0 != strncmp(pszAppId, g_pszAppId, strlen(g_pszAppId)) )
        {
                FPRINTF("[Line : %d][%s] autofill_save_view_info_get_app_id failed for pszAppId = %s\\n", __LINE__, API_NAMESPACE, pszAppId);
                FREE_MEMORY(pszAppId);
		autofill_save_view_info_destroy(hSaveViewInfo);
                return 1;
        }

	FREE_MEMORY(pszAppId);
	nRet = autofill_save_view_info_destroy(hSaveViewInfo);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_destroy", AutofillGetError(nRet))

	return 0;
}

/**
* @testcase				ITc_autofill_save_view_info_set_get_view_id_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the view ID in autofill save view information.
* @scenario				Creates handle and Sets and gets the view ID in autofill save view information then destroys handle.
* @apicovered				autofill_save_view_info_set_view_id, autofill_save_view_info_get_view_id
* @passcase				autofill_save_view_info_set_view_id, autofill_save_view_info_get_view_id return(s) 0
* @failcase				autofill_save_view_info_set_view_id, autofill_save_view_info_get_view_id return(s) 1
* @precondition				autofill_save_view_info_create
* @postcondition			autofill_save_view_info_destroy
* */
int ITc_autofill_save_view_info_set_get_view_id_p(void)
{
	START_TEST;

	autofill_save_view_info_h hSaveViewInfo = NULL;
	char *pszViewId= NULL;
	int nRet = 0;

	nRet = autofill_save_view_info_create(&hSaveViewInfo);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hSaveViewInfo, "autofill_save_view_info_create");

	nRet = autofill_save_view_info_set_view_id(hSaveViewInfo, g_pszViewId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_set_view_id", AutofillGetError(nRet), autofill_save_view_info_destroy(hSaveViewInfo));

	nRet = autofill_save_view_info_get_view_id(hSaveViewInfo, &pszViewId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_get_view_id", AutofillGetError(nRet), autofill_save_view_info_destroy(hSaveViewInfo));
	CHECK_HANDLE_CLEANUP(pszViewId, "autofill_save_view_info_get_view_id", autofill_save_view_info_destroy(hSaveViewInfo));

	if ( 0 != strncmp(pszViewId, g_pszViewId, strlen(g_pszViewId)) )
        {
                FPRINTF("[Line : %d][%s] autofill_save_view_info_get_view_id failed for pszViewId = %s\\n", __LINE__, API_NAMESPACE, pszViewId);
                FREE_MEMORY(pszViewId);
		autofill_save_view_info_destroy(hSaveViewInfo);
                return 1;
        }
	FREE_MEMORY(pszViewId);
	nRet = autofill_save_view_info_destroy(hSaveViewInfo);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_destroy", AutofillGetError(nRet))

	return 0;
}

/**
* @testcase				ITc_autofill_save_view_info_add_item_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Adds autofill save item in autofill save view information.
* @scenario				Creates handle and Adds autofill save item in autofill save view information then destroys handle.
* @apicovered				autofill_save_view_info_add_item
* @passcase				autofill_save_view_info_add_item return(s) 0
* @failcase				autofill_save_view_info_add_item return(s) 1
* @precondition				autofill_save_item_create, autofill_save_view_info_create
* @postcondition			autofill_save_view_info_destroy, autofill_save_item_destroy
* */
int ITc_autofill_save_view_info_add_item_p(void)
{
	START_TEST;

	autofill_save_view_info_h hSaveViewInfo = NULL;
	autofill_save_item_h hSaveItem = NULL;
	int nRet = 0;

	nRet = autofill_save_item_create(&hSaveItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hSaveItem, "autofill_save_item_create");

	nRet = autofill_save_view_info_create(&hSaveViewInfo);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_create", AutofillGetError(nRet), autofill_save_item_destroy(hSaveItem));
	CHECK_HANDLE_CLEANUP(hSaveViewInfo, "autofill_save_view_info_create", autofill_save_item_destroy(hSaveItem));

	nRet = autofill_save_view_info_add_item(hSaveViewInfo, hSaveItem);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_add_item", AutofillGetError(nRet),autofill_save_view_info_destroy(hSaveViewInfo);autofill_save_item_destroy(hSaveItem));

	nRet = autofill_save_view_info_destroy(hSaveViewInfo);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_destroy", AutofillGetError(nRet));

	nRet = autofill_save_item_destroy(hSaveItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_destroy", AutofillGetError(nRet));

	return 0;
}


/**
* @testcase				ITc_autofill_save_view_info_foreach_item_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Retrieves all items in autofill save view information.
* @scenario				Creates handle and Retrieves all items in autofill save view information then destroys handle.
* @apicovered				autofill_save_view_info_foreach_item
* @passcase				autofill_save_view_info_foreach_item return(s) 0
* @failcase				autofill_save_view_info_foreach_item return(s) 1
* @precondition				autofill_save_view_info_create
* @postcondition			autofill_save_view_info_destroy
* */
int ITc_autofill_save_view_info_foreach_item_p(void)
{
	START_TEST;

	autofill_save_view_info_h hSaveViewInfo = NULL;
	int nRet = 0;

	nRet = autofill_save_view_info_create(&hSaveViewInfo);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hSaveViewInfo, "autofill_save_view_info_create");

	nRet = autofill_save_view_info_foreach_item(hSaveViewInfo, AutofillSaveItemCb, NULL);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_foreach_item", AutofillGetError(nRet), autofill_save_view_info_destroy(hSaveViewInfo));

	nRet = autofill_save_view_info_destroy(hSaveViewInfo);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_destroy", AutofillGetError(nRet))
	return 0;
}

/**
* @testcase				ITc_autofill_save_view_info_set_get_view_title_p
* @since_tizen				5.5
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description				Set and Get autofill save view title information.
* @scenario				Creates handle and set and get view title for autofill save view information then destroys handle.
* @apicovered				autofill_save_view_info_get_view_title, autofill_save_view_info_set_view_title
* @passcase				All target API's  return(s) 0
* @failcase				If any target API's return(s) 1
* @precondition				autofill_save_view_info_create
* @postcondition			autofill_save_view_info_destroy
* */
int ITc_autofill_save_view_info_set_get_view_title_p(void)
{
	START_TEST;

	autofill_save_view_info_h hSaveViewInfo = NULL;
	int nRet = 0;
	char *gpszViewTitle = NULL;
	char *spszViewTitle = "login";

	nRet = autofill_save_view_info_create(&hSaveViewInfo);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_create", AutofillGetError(nRet));
	CHECK_HANDLE(hSaveViewInfo, "autofill_save_view_info_create");

	nRet = autofill_save_view_info_set_view_title(hSaveViewInfo, spszViewTitle);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_set_view_title", AutofillGetError(nRet), autofill_save_view_info_destroy(hSaveViewInfo));

	nRet = autofill_save_view_info_get_view_title(hSaveViewInfo, &gpszViewTitle);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_get_view_title", AutofillGetError(nRet), autofill_save_view_info_destroy(hSaveViewInfo));
	CHECK_HANDLE_CLEANUP(gpszViewTitle, "autofill_save_view_info_get_view_title", autofill_save_view_info_destroy(hSaveViewInfo));

	if ( 0 != strncmp(spszViewTitle, gpszViewTitle, strlen(gpszViewTitle)) )
        {
                FPRINTF("[Line : %d][%s] mismatch between set and get value of title as sViewTitle =  %s and gViewTitle = %s\\n", __LINE__, API_NAMESPACE, spszViewTitle, gpszViewTitle);
		autofill_save_view_info_destroy(hSaveViewInfo);
                return 1;
        }

	nRet = autofill_save_view_info_destroy(hSaveViewInfo);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_destroy", AutofillGetError(nRet));
	return 0;
}


/**
* @testcase				ITc_autofill_fill_response_create_destroy_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Creates and destroys an autofill fill response.
* @scenario				Creates and destroys an autofill fill response.
* @apicovered				autofill_fill_response_create, autofill_fill_response_destroy
* @passcase				autofill_fill_response_create, autofill_fill_response_destroy return(s) 0
* @failcase				autofill_fill_response_create, autofill_fill_response_destroy return(s) 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_autofill_fill_response_create_destroy_p(void)
{
	START_TEST;

	autofill_fill_response_h hFillResponse = NULL;
	int nRet = 0;

	nRet = autofill_fill_response_create(&hFillResponse);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_create", AutofillGetError(nRet));
	CHECK_HANDLE(hFillResponse, "autofill_fill_response_create");

	nRet = autofill_fill_response_destroy(hFillResponse);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_fill_response_set_get_app_id_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the app ID in an autofill fill response.
* @scenario				Creates handle and Sets and gets the app ID in an autofill fill response then destroys handle.
* @apicovered				autofill_fill_response_set_app_id, autofill_fill_response_get_app_id
* @passcase				autofill_fill_response_set_app_id, autofill_fill_response_get_app_id return(s) 0
* @failcase				autofill_fill_response_set_app_id, autofill_fill_response_get_app_id return(s) 1
* @precondition				autofill_fill_response_create
* @postcondition			autofill_fill_response_destroy
* */
int ITc_autofill_fill_response_set_get_app_id_p(void)
{
	START_TEST;

	autofill_fill_response_h hFillResponse = NULL;
	char* pszAppId= NULL;
	int nRet = 0;

	nRet = autofill_fill_response_create(&hFillResponse);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_create", AutofillGetError(nRet));
	CHECK_HANDLE(hFillResponse, "autofill_fill_response_create");

	nRet = autofill_fill_response_set_app_id(hFillResponse, g_pszAppId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_set_app_id", AutofillGetError(nRet), autofill_fill_response_destroy(hFillResponse));

	nRet = autofill_fill_response_get_app_id(hFillResponse, &pszAppId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_get_app_id", AutofillGetError(nRet), autofill_fill_response_destroy(hFillResponse));
	CHECK_HANDLE_CLEANUP(pszAppId, "autofill_fill_response_get_app_id", autofill_fill_response_destroy(hFillResponse));

	if ( 0 != strncmp(pszAppId, g_pszAppId, strlen(g_pszAppId)) )
        {
                FPRINTF("[Line : %d][%s] autofill_fill_response_get_app_id failed for pszAppId = %s\\n", __LINE__, API_NAMESPACE, pszAppId);
                FREE_MEMORY(pszAppId);
		autofill_fill_response_destroy(hFillResponse);
                return 1;
        }

	FREE_MEMORY(pszAppId);
	nRet = autofill_fill_response_destroy(hFillResponse);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_destroy", AutofillGetError(nRet));
	return 0;
}

/**
* @testcase				ITc_autofill_fill_response_set_get_view_id_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the view ID in an autofill fill response.
* @scenario				Creates handle and Sets and gets the view ID in an autofill fill response then destroys handle.
* @apicovered				autofill_fill_response_set_view_id, autofill_fill_response_get_view_id
* @passcase				autofill_fill_response_set_view_id, autofill_fill_response_get_view_id return(s) 0
* @failcase				autofill_fill_response_set_view_id, autofill_fill_response_get_view_id return(s) 1
* @precondition				autofill_fill_response_create
* @postcondition			autofill_fill_response_destroy
* */
int ITc_autofill_fill_response_set_get_view_id_p(void)
{
	START_TEST;

	autofill_fill_response_h hFillResponse = NULL;
	char* pszViewId= NULL;
	int nRet = 0;

	nRet = autofill_fill_response_create(&hFillResponse);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_create", AutofillGetError(nRet));
	CHECK_HANDLE(hFillResponse, "autofill_fill_response_create");

	nRet = autofill_fill_response_set_view_id(hFillResponse, g_pszViewId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_set_view_id", AutofillGetError(nRet), autofill_fill_response_destroy(hFillResponse));

	nRet = autofill_fill_response_get_view_id(hFillResponse, &pszViewId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_get_view_id", AutofillGetError(nRet), autofill_fill_response_destroy(hFillResponse));
	CHECK_HANDLE_CLEANUP(pszViewId, "autofill_fill_response_get_view_id", autofill_fill_response_destroy(hFillResponse));

	if ( 0 != strncmp(pszViewId, g_pszViewId, strlen(g_pszViewId)) )
        {
                FPRINTF("[Line : %d][%s] autofill_fill_response_get_view_id failed for pszViewId = %s\\n", __LINE__, API_NAMESPACE, pszViewId);
                FREE_MEMORY(pszViewId);
		autofill_fill_response_destroy(hFillResponse);
                return 1;
        }

	FREE_MEMORY(pszViewId);
	nRet = autofill_fill_response_destroy(hFillResponse);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_destroy", AutofillGetError(nRet));
	return 0;
}

/**
* @testcase				ITc_autofill_fill_response_add_group_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Adds autofill fill response group.
* @scenario				Creates handle and Adds autofill fill response group then destroys handle.
* @apicovered				autofill_fill_response_add_group
* @passcase				autofill_fill_response_add_group return(s) 0
* @failcase				autofill_fill_response_add_group return(s) 1
* @precondition				autofill_fill_response_create, autofill_fill_response_group_create
* @postcondition			autofill_fill_response_group_destroy, autofill_fill_response_destroy
* */
int ITc_autofill_fill_response_add_group_p(void)
{
	START_TEST;

	autofill_fill_response_h hFillResponse = NULL;
	autofill_fill_response_group_h hFillResponseGroup = NULL;
	int nRet = 0;

	nRet = autofill_fill_response_create(&hFillResponse);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_create", AutofillGetError(nRet));
	CHECK_HANDLE(hFillResponse, "autofill_fill_response_create");

	nRet = autofill_fill_response_group_create(&hFillResponseGroup);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_group_create", AutofillGetError(nRet), autofill_fill_response_destroy(hFillResponse));
	CHECK_HANDLE_CLEANUP(hFillResponseGroup, "autofill_fill_response_group_create", autofill_fill_response_destroy(hFillResponse));

	nRet = autofill_fill_response_add_group(hFillResponse, hFillResponseGroup);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_add_group", AutofillGetError(nRet),autofill_fill_response_group_destroy(hFillResponseGroup);autofill_fill_response_destroy(hFillResponse));

	nRet = autofill_fill_response_group_destroy(hFillResponseGroup);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_group_destroy", AutofillGetError(nRet));

	nRet = autofill_fill_response_destroy(hFillResponse);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_fill_response_foreach_group_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Retrieves all groups of each fill response.
* @scenario				Creates handle and Retrieves all groups of each fill response then destroys handle.
* @apicovered				autofill_fill_response_foreach_group
* @passcase				autofill_fill_response_foreach_group return(s) 0
* @failcase				autofill_fill_response_foreach_group return(s) 1
* @precondition				autofill_fill_response_create
* @postcondition			autofill_fill_response_destroy
* */
int ITc_autofill_fill_response_foreach_group_p(void)
{
	START_TEST;

	autofill_fill_response_h hFillResponse = NULL;
	int nRet = 0;

	nRet = autofill_fill_response_create(&hFillResponse);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_create", AutofillGetError(nRet));
	CHECK_HANDLE(hFillResponse, "autofill_fill_response_create");

	nRet = autofill_fill_response_foreach_group(hFillResponse, AutofillFillResponseGroupCb, NULL);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_foreach_group", AutofillGetError(nRet), autofill_fill_response_destroy(hFillResponse));

	nRet = autofill_fill_response_destroy(hFillResponse);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_destroy", AutofillGetError(nRet));
	return 0;
}


/**
* @testcase				ITc_autofill_fill_response_get_group_count_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Gets the number of fill response group.
* @scenario				Creates handle and Gets the number of fill response group then destroys handle.
* @apicovered				autofill_fill_response_get_group_count
* @passcase				autofill_fill_response_get_group_count return(s) 0
* @failcase				autofill_fill_response_get_group_count return(s) 1
* @precondition				autofill_fill_response_create
* @postcondition			autofill_fill_response_destroy
* */
int ITc_autofill_fill_response_get_group_count_p(void)
{
	START_TEST;

	autofill_fill_response_h hFillResponse = NULL;
	int nCount = -1;
	int nRet = 0;

	nRet = autofill_fill_response_create(&hFillResponse);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_create", AutofillGetError(nRet));
	CHECK_HANDLE(hFillResponse, "autofill_fill_response_create");

	nRet = autofill_fill_response_get_group_count(hFillResponse, &nCount);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_get_group_count", AutofillGetError(nRet),autofill_fill_response_destroy(hFillResponse));
	if( nCount < 0 )
	{
		FPRINTF("[Line : %d][%s]  autofill_fill_response_get_group_count failed. nCount = %d\\n", __LINE__, API_NAMESPACE, nCount);
		autofill_fill_response_destroy(hFillResponse);
		return 1;
	}

	nRet = autofill_fill_response_destroy(hFillResponse);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_destroy", AutofillGetError(nRet));
	return 0;
}

/**
* @testcase				ITc_autofill_fill_response_group_create_destroy_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Creates and destroys an autofill fill response group.
* @scenario				Creates and destroys an autofill fill response group.
* @apicovered				autofill_fill_response_group_create, autofill_fill_response_group_destroy
* @passcase				autofill_fill_response_group_create, autofill_fill_response_group_destroy return(s) 0
* @failcase				autofill_fill_response_group_create, autofill_fill_response_group_destroy return(s) 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_autofill_fill_response_group_create_destroy_p(void)
{
	START_TEST;

	autofill_fill_response_group_h hFillResponseGroup = NULL;
	int nRet = 0;

	nRet = autofill_fill_response_group_create(&hFillResponseGroup);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_group_create", AutofillGetError(nRet));
	CHECK_HANDLE(hFillResponseGroup, "autofill_fill_response_group_create");

	nRet = autofill_fill_response_group_destroy(hFillResponseGroup);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_group_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_fill_response_group_clone_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Clones an autofill fill response group.
* @scenario				Creates handle and Clones an autofill fill response group then destroys handle.
* @apicovered				autofill_fill_response_group_clone
* @passcase				autofill_fill_response_group_clone return(s) 0
* @failcase				autofill_fill_response_group_clone return(s) 1
* @precondition				autofill_fill_response_group_create
* @postcondition			autofill_fill_response_group_destroy
* */
int ITc_autofill_fill_response_group_clone_p(void)
{
	START_TEST;

	autofill_fill_response_group_h hFillResponseGroup = NULL;
	autofill_fill_response_group_h hFillResponseGroupClone = NULL;
	int nRet = 0;

	nRet = autofill_fill_response_group_create(&hFillResponseGroup);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_group_create", AutofillGetError(nRet));
	CHECK_HANDLE(hFillResponseGroup, "autofill_fill_response_group_create");

	nRet = autofill_fill_response_group_clone(hFillResponseGroup, &hFillResponseGroupClone);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_group_clone", AutofillGetError(nRet),autofill_fill_response_group_destroy(hFillResponseGroup));
	CHECK_HANDLE_CLEANUP(hFillResponseGroupClone, "autofill_fill_response_group_clone", autofill_fill_response_group_destroy(hFillResponseGroup));

	FREE_MEMORY(hFillResponseGroupClone);
	nRet = autofill_fill_response_group_destroy(hFillResponseGroup);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_group_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_fill_response_group_add_item_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Adds autofill item in an autofill fil response group.
* @scenario				Creates handle and Adds autofill item in an autofill fil response group then destroys handle.
* @apicovered				autofill_fill_response_group_add_item
* @passcase				autofill_fill_response_group_add_item return(s) 0
* @failcase				autofill_fill_response_group_add_item return(s) 1
* @precondition				autofill_fill_response_group_create, autofill_fill_response_item_create
* @postcondition			autofill_fill_response_item_destroy, autofill_fill_response_group_destroy
* */
int ITc_autofill_fill_response_group_add_item_p(void)
{
	START_TEST;

	autofill_fill_response_group_h hFillResponseGroup = NULL;
	autofill_fill_response_item_h hFillResponseItem = NULL;
	int nRet = 0;

	nRet = autofill_fill_response_group_create(&hFillResponseGroup);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_group_create", AutofillGetError(nRet));
	CHECK_HANDLE(hFillResponseGroup, "autofill_fill_response_group_create");

	nRet = autofill_fill_response_item_create(&hFillResponseItem);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_create", AutofillGetError(nRet), autofill_fill_response_group_destroy(hFillResponseGroup));
	CHECK_HANDLE_CLEANUP(hFillResponseItem, "autofill_fill_response_item_create", autofill_fill_response_group_destroy(hFillResponseGroup));

	nRet = autofill_fill_response_group_add_item(hFillResponseGroup, hFillResponseItem);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_group_add_item", AutofillGetError(nRet),autofill_fill_response_item_destroy(hFillResponseItem);autofill_fill_response_group_destroy(hFillResponseGroup));

	nRet = autofill_fill_response_item_destroy(hFillResponseItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_destroy", AutofillGetError(nRet));

	nRet = autofill_fill_response_group_destroy(hFillResponseGroup);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_group_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_fill_response_group_foreach_item_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Retrieves all fill response items of each group.
* @scenario				Creates handle and Retrieves all fill response items of each group then destroys handle.
* @apicovered				autofill_fill_response_group_foreach_item
* @passcase				autofill_fill_response_group_foreach_item return(s) 0
* @failcase				autofill_fill_response_group_foreach_item return(s) 1
* @precondition				autofill_fill_response_group_create
* @postcondition			autofill_fill_response_group_destroy
* */
int ITc_autofill_fill_response_group_foreach_item_p(void)
{
	START_TEST;

	autofill_fill_response_group_h hFillResponseGroup = NULL;
	int nRet = 0;

	nRet = autofill_fill_response_group_create(&hFillResponseGroup);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_group_create", AutofillGetError(nRet));
	CHECK_HANDLE(hFillResponseGroup, "autofill_fill_response_group_create");

	nRet = autofill_fill_response_group_foreach_item(hFillResponseGroup, AutofillFillResponseItemCb, NULL);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_group_foreach_item", AutofillGetError(nRet), autofill_fill_response_group_destroy(hFillResponseGroup));

	nRet = autofill_fill_response_group_destroy(hFillResponseGroup);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_group_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_fill_response_item_create_destroy_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Creates and destroys autofill response item.
* @scenario				Creates and destroys autofill response item.
* @apicovered				autofill_fill_response_item_create, autofill_fill_response_item_destroy
* @passcase				autofill_fill_response_item_create, autofill_fill_response_item_destroy return(s) 0
* @failcase				autofill_fill_response_item_create, autofill_fill_response_item_destroy return(s) 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_autofill_fill_response_item_create_destroy_p(void)
{
	START_TEST;

	autofill_fill_response_item_h hFillResponseItem = NULL;
	int nRet = 0;

	nRet = autofill_fill_response_item_create(&hFillResponseItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hFillResponseItem, "autofill_fill_response_item_create");

	nRet = autofill_fill_response_item_destroy(hFillResponseItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_destroy", AutofillGetError(nRet));


	return 0;
}

/**
* @testcase				ITc_autofill_fill_response_item_clone_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Clones an autofill fill response item.
* @scenario				Creates handle and Clones an autofill fill response item then destroys handle.
* @apicovered				autofill_fill_response_item_clone
* @passcase				autofill_fill_response_item_clone return(s) 0
* @failcase				autofill_fill_response_item_clone return(s) 1
* @precondition				autofill_fill_response_item_create
* @postcondition			autofill_fill_response_item_destroy
* */
int ITc_autofill_fill_response_item_clone_p(void)
{
	START_TEST;

	autofill_fill_response_item_h hFillResponseItem = NULL;
	autofill_fill_response_item_h hFillResponseItemClone = NULL;
	int nRet = 0;

	nRet = autofill_fill_response_item_create(&hFillResponseItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hFillResponseItem, "autofill_fill_response_item_create");

	nRet = autofill_fill_response_item_clone(hFillResponseItem, &hFillResponseItemClone);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_clone", AutofillGetError(nRet), autofill_fill_response_item_destroy(hFillResponseItem));
	CHECK_HANDLE_CLEANUP(hFillResponseItemClone, "autofill_fill_response_item_clone", autofill_fill_response_item_destroy(hFillResponseItem));

	FREE_MEMORY(hFillResponseItemClone);
	nRet = autofill_fill_response_item_destroy(hFillResponseItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_destroy", AutofillGetError(nRet));


	return 0;
}

/**
* @testcase				ITc_autofill_fill_response_item_set_get_id_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the autofill ID in an autofill fill response item.
* @scenario				Creates handle and Sets and gets the autofill ID in an autofill fill response item then destroys handle.
* @apicovered				autofill_fill_response_item_set_id, autofill_fill_response_item_get_id
* @passcase				autofill_fill_response_item_set_id, autofill_fill_response_item_get_id return(s) 0
* @failcase				autofill_fill_response_item_set_id, autofill_fill_response_item_get_id return(s) 1
* @precondition				autofill_fill_response_item_create
* @postcondition			autofill_fill_response_item_destroy
* */
int ITc_autofill_fill_response_item_set_get_id_p(void)
{
	START_TEST;

	autofill_fill_response_item_h hFillResponseItem = NULL;
	char *pszId= NULL;
	int nRet = 0;

	nRet = autofill_fill_response_item_create(&hFillResponseItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hFillResponseItem, "autofill_fill_response_item_create");

	nRet = autofill_fill_response_item_set_id(hFillResponseItem, g_pszId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_set_id", AutofillGetError(nRet), autofill_fill_response_item_destroy(hFillResponseItem));

	nRet = autofill_fill_response_item_get_id(hFillResponseItem, &pszId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_get_id", AutofillGetError(nRet), autofill_fill_response_item_destroy(hFillResponseItem));
	CHECK_HANDLE_CLEANUP(pszId, "autofill_fill_response_item_get_id", autofill_fill_response_item_destroy(hFillResponseItem));

	if ( 0 != strncmp(pszId, g_pszId, strlen(g_pszId)) )
        {
                FPRINTF("[Line : %d][%s]autofill_fill_response_item_get_id failed for  pszId = %s\\n", __LINE__, API_NAMESPACE,  pszId);
                FREE_MEMORY(pszId);
		autofill_fill_response_item_destroy(hFillResponseItem);
                return 1;
        }

	FREE_MEMORY(pszId);
	nRet = autofill_fill_response_item_destroy(hFillResponseItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_destroy", AutofillGetError(nRet));


	return 0;
}

/**
* @testcase				ITc_autofill_fill_response_item_set_get_value_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the autofill value in an autofill fill response item.
* @scenario				Creates handle and Sets and gets the autofill value in an autofill fill response item then destroys handle.
* @apicovered				autofill_fill_response_item_set_value, autofill_fill_response_item_get_value
* @passcase				autofill_fill_response_item_set_value, autofill_fill_response_item_get_value return(s) 0
* @failcase				autofill_fill_response_item_set_value, autofill_fill_response_item_get_value return(s) 1
* @precondition				autofill_fill_response_item_create
* @postcondition			autofill_fill_response_item_destroy
* */
int ITc_autofill_fill_response_item_set_get_value_p(void)
{
	START_TEST;

	autofill_fill_response_item_h hFillResponseItem = NULL;
	char *pszValue= NULL;
	int nRet = 0;

	nRet = autofill_fill_response_item_create(&hFillResponseItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hFillResponseItem, "autofill_fill_response_item_create");

	nRet = autofill_fill_response_item_set_value(hFillResponseItem, g_pszValue);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_set_value", AutofillGetError(nRet), autofill_fill_response_item_destroy(hFillResponseItem));

	nRet = autofill_fill_response_item_get_value(hFillResponseItem, &pszValue);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_get_value", AutofillGetError(nRet), autofill_fill_response_item_destroy(hFillResponseItem));
	CHECK_HANDLE_CLEANUP(pszValue, "autofill_fill_response_item_get_value", autofill_fill_response_item_destroy(hFillResponseItem));

	if ( 0 != strncmp(pszValue, g_pszValue, strlen(g_pszValue)) )
        {
                FPRINTF("[Line : %d][%s]autofill_fill_response_item_get_value failed for  pszValue = %s\\n", __LINE__, API_NAMESPACE, pszValue);
                FREE_MEMORY(pszValue);
		autofill_fill_response_item_destroy(hFillResponseItem);
                return 1;
        }

	FREE_MEMORY(pszValue);
	nRet = autofill_fill_response_item_destroy(hFillResponseItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_destroy", AutofillGetError(nRet));


	return 0;
}

/**
* @testcase				ITc_autofill_fill_response_item_set_get_presentation_text_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the presentation text in an autofill fill response item.
* @scenario				Creates handle and Sets and gets the presentation text in an autofill fill response item then destroys handle.
* @apicovered				autofill_fill_response_item_set_presentation_text, autofill_fill_response_item_get_presentation_text
* @passcase				autofill_fill_response_item_set_presentation_text, autofill_fill_response_item_get_presentation_text return(s) 0
* @failcase				autofill_fill_response_item_set_presentation_text, autofill_fill_response_item_get_presentation_text return(s) 1
* @precondition				autofill_fill_response_item_create
* @postcondition			autofill_fill_response_item_destroy
* */
int ITc_autofill_fill_response_item_set_get_presentation_text_p(void)
{
	START_TEST;

	autofill_fill_response_item_h hFillResponseItem = NULL;
	char *pszPresentationText= NULL;
	int nRet = 0;

	nRet = autofill_fill_response_item_create(&hFillResponseItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hFillResponseItem, "autofill_fill_response_item_create");

	nRet = autofill_fill_response_item_set_presentation_text(hFillResponseItem, g_pszPresentationText);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_set_presentation_text", AutofillGetError(nRet), autofill_fill_response_item_destroy(hFillResponseItem));

	nRet = autofill_fill_response_item_get_presentation_text(hFillResponseItem, &pszPresentationText);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_get_presentation_text", AutofillGetError(nRet), autofill_fill_response_item_destroy(hFillResponseItem));
	CHECK_HANDLE_CLEANUP(pszPresentationText, "autofill_fill_response_item_get_presentation_text", autofill_fill_response_item_destroy(hFillResponseItem));

	if ( 0 != strncmp(pszPresentationText, g_pszPresentationText, strlen(g_pszPresentationText)) )
        {
                FPRINTF("[Line : %d][%s]autofill_fill_response_item_get_presentation_text failed for pszPresentationText = %s\\n", __LINE__, API_NAMESPACE, pszPresentationText);
                FREE_MEMORY(pszPresentationText);
		autofill_fill_response_item_destroy(hFillResponseItem);
                return 1;
        }


	FREE_MEMORY(pszPresentationText);
	nRet = autofill_fill_response_item_destroy(hFillResponseItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_save_item_create_destroy_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Creates and destroys autofill save item.
* @scenario				Creates and destroys autofill save item.
* @apicovered				autofill_save_item_create, autofill_save_item_destroy
* @passcase				autofill_save_item_create, autofill_save_item_destroy return(s) 0
* @failcase				autofill_save_item_create, autofill_save_item_destroy return(s) 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_autofill_save_item_create_destroy_p(void)
{
	START_TEST;

	autofill_save_item_h hSaveItem = NULL;
	int nRet = 0;

	nRet = autofill_save_item_create(&hSaveItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hSaveItem, "autofill_save_item_create");

	nRet = autofill_save_item_destroy(hSaveItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_save_item_clone_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Clones an autofill save item.
* @scenario				Creates handle and Clones an autofill save item then destroys handle.
* @apicovered				autofill_save_item_clone
* @passcase				autofill_save_item_clone return(s) 0
* @failcase				autofill_save_item_clone return(s) 1
* @precondition				autofill_save_item_create
* @postcondition			autofill_save_item_destroy
* */
int ITc_autofill_save_item_clone_p(void)
{
	START_TEST;

	autofill_save_item_h hSaveItem = NULL;
	autofill_save_item_h hSaveItemClone = NULL;
	int nRet = 0;

	nRet = autofill_save_item_create(&hSaveItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hSaveItem, "autofill_save_item_create");

	nRet = autofill_save_item_clone(hSaveItem, &hSaveItemClone);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_clone", AutofillGetError(nRet),autofill_save_item_destroy(hSaveItem));
	CHECK_HANDLE_CLEANUP(hSaveItemClone, "autofill_save_item_clone", autofill_save_item_destroy(hSaveItem));

	FREE_MEMORY(hSaveItemClone);

	nRet = autofill_save_item_destroy(hSaveItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_destroy", AutofillGetError(nRet));
	return 0;
}

/**
* @testcase				ITc_autofill_save_item_set_get_autofill_hint_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the autofill hint (id(username), name, password, phone, credit card number, organization, so on) in an autofill save item.
* @scenario				Creates handle and Sets and gets the autofill hint (id(username), name, password, phone, credit card number, organization, so on) in an autofill save item then destroys handle.
* @apicovered				autofill_save_item_set_autofill_hint, autofill_save_item_get_autofill_hint
* @passcase				autofill_save_item_set_autofill_hint, autofill_save_item_get_autofill_hint return(s) 0
* @failcase				autofill_save_item_set_autofill_hint, autofill_save_item_get_autofill_hint return(s) 1
* @precondition				autofill_save_item_create
* @postcondition			autofill_save_item_destroy
* */
int ITc_autofill_save_item_set_get_autofill_hint_p(void)
{
	START_TEST;

	autofill_save_item_h hSaveItem = NULL;
	int nRet = 0;

	nRet = autofill_save_item_create(&hSaveItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_create", AutofillGetError(nRet));

	autofill_hint_e eHintAutofill;
	int enum_size =  sizeof(eHint)/sizeof(eHint[0]);

	for(int enum_counter = 0; enum_counter < enum_size; enum_counter++)
	{
		autofill_hint_e eHintautofilltest = eHint[enum_counter];
		CHECK_HANDLE(hSaveItem, "autofill_save_item_create");

		nRet = autofill_save_item_set_autofill_hint(hSaveItem, eHintautofilltest);
		PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_set_autofill_hint", AutofillGetError(nRet),autofill_save_item_destroy(hSaveItem));

		nRet = autofill_save_item_get_autofill_hint(hSaveItem, &eHintAutofill);
		PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_get_autofill_hint", AutofillGetError(nRet),autofill_save_item_destroy(hSaveItem));

		if( eHintAutofill !=  eHintautofilltest )
		{
			FPRINTF("[Line : %d][%s] autofill_save_item_get_autofill_hint failed. eHintAutofill = %d\\n", __LINE__, API_NAMESPACE, eHintAutofill);
			autofill_save_item_destroy(hSaveItem);
			return 1;
		}
	}
	nRet = autofill_save_item_destroy(hSaveItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_destroy", AutofillGetError(nRet));
	return 0;
}

/**
* @testcase				ITc_autofill_save_item_set_get_id_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the autofill ID in an autofill save item.
* @scenario				Creates handle and Sets and gets the autofill ID in an autofill save item then destroys handle.
* @apicovered				autofill_save_item_set_id, autofill_save_item_get_id
* @passcase				autofill_save_item_set_id, autofill_save_item_get_id return(s) 0
* @failcase				autofill_save_item_set_id, autofill_save_item_get_id return(s) 1
* @precondition				autofill_save_item_create
* @postcondition			autofill_save_item_destroy
* */
int ITc_autofill_save_item_set_get_id_p(void)
{
	START_TEST;

	autofill_save_item_h hSaveItem = NULL;
	char *pszId= NULL;
	int nRet = 0;

	nRet = autofill_save_item_create(&hSaveItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hSaveItem, "autofill_save_item_create");

	nRet = autofill_save_item_set_id(hSaveItem, g_pszId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_set_id", AutofillGetError(nRet), autofill_save_item_destroy(hSaveItem));

	nRet = autofill_save_item_get_id(hSaveItem, &pszId);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_get_id", AutofillGetError(nRet), autofill_save_item_destroy(hSaveItem));
	CHECK_HANDLE_CLEANUP(pszId, "autofill_save_item_get_id", autofill_save_item_destroy(hSaveItem));

	if ( 0 != strncmp(pszId, g_pszId, strlen(g_pszId)) )
	{
		FPRINTF("[Line : %d][%s] autofill_save_item_get_id failed. pszId = %s\\n", __LINE__, API_NAMESPACE, pszId);
		FREE_MEMORY(pszId);
		autofill_save_item_destroy(hSaveItem);
		return 1;
	}

	FREE_MEMORY(pszId);
	nRet = autofill_save_item_destroy(hSaveItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_destroy", AutofillGetError(nRet));
	return 0;
}

/**
* @testcase				ITc_autofill_save_item_set_get_label_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the autofill label in an autofill save item.
* @scenario				Creates handle and Sets and gets the autofill label in an autofill save item then destroys handle.
* @apicovered				autofill_save_item_set_label, autofill_save_item_get_label
* @passcase				autofill_save_item_set_label, autofill_save_item_get_label return(s) 0
* @failcase				autofill_save_item_set_label, autofill_save_item_get_label return(s) 1
* @precondition				autofill_save_item_create
* @postcondition			autofill_save_item_destroy
* */
int ITc_autofill_save_item_set_get_label_p(void)
{
	START_TEST;

	autofill_save_item_h hSaveItem = NULL;
	char *pszLabel= NULL;
	int nRet = 0;

	nRet = autofill_save_item_create(&hSaveItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hSaveItem, "autofill_save_item_create");

	nRet = autofill_save_item_set_label(hSaveItem, g_pszLabel);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_set_label", AutofillGetError(nRet), autofill_save_item_destroy(hSaveItem));

	nRet = autofill_save_item_get_label(hSaveItem, &pszLabel);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_get_label", AutofillGetError(nRet), autofill_save_item_destroy(hSaveItem));
	CHECK_HANDLE_CLEANUP(pszLabel, "autofill_save_item_get_label", autofill_save_item_destroy(hSaveItem));

	if ( 0 != strncmp(pszLabel, g_pszLabel, strlen(g_pszLabel)) )
	{
		FPRINTF("[Line : %d][%s]autofill_save_item_get_label failed. pszLabel = %s\\n", __LINE__, API_NAMESPACE, pszLabel);
		FREE_MEMORY(pszLabel);
		autofill_save_item_destroy(hSaveItem);
		return 1;
	}

	FREE_MEMORY(pszLabel);
	nRet = autofill_save_item_destroy(hSaveItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_destroy", AutofillGetError(nRet));
	return 0;
}

/**
* @testcase				ITc_autofill_save_item_set_get_sensitive_data_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the sensitive data in an autofill save item.
* @scenario				Creates handle and Sets and gets the sensitive data in an autofill save item then destroys handle.
* @apicovered				autofill_save_item_set_sensitive_data, autofill_save_item_get_sensitive_data
* @passcase				autofill_save_item_set_sensitive_data, autofill_save_item_get_sensitive_data return(s) 0
* @failcase				autofill_save_item_set_sensitive_data, autofill_save_item_get_sensitive_data return(s) 1
* @precondition				autofill_save_item_create
* @postcondition			autofill_save_item_destroy
* */
int ITc_autofill_save_item_set_get_sensitive_data_p(void)
{
	START_TEST;

	autofill_save_item_h hSaveItem = NULL;
	bool bSensitive = false;

	int nRet = 0;

	nRet = autofill_save_item_create(&hSaveItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hSaveItem, "autofill_save_item_create");

	nRet = autofill_save_item_set_sensitive_data(hSaveItem, g_bSensitive);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_set_sensitive_data", AutofillGetError(nRet),autofill_save_item_destroy(hSaveItem));

	nRet = autofill_save_item_get_sensitive_data(hSaveItem, &bSensitive);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_get_sensitive_data", AutofillGetError(nRet),autofill_save_item_destroy(hSaveItem));
	if( bSensitive != g_bSensitive)
	{
		FPRINTF("[Line : %d][%s] autofill_save_item_get_sensitive_data failed. bSensitive = %d\\n", __LINE__, API_NAMESPACE, bSensitive);
		autofill_save_item_destroy(hSaveItem);
		return 1;
	}

	nRet = autofill_save_item_destroy(hSaveItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_save_item_set_get_value_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the autofill value in an autofill save item.
* @scenario				Creates handle and Sets and gets the autofill value in an autofill save item then destroys handle.
* @apicovered				autofill_save_item_set_value, autofill_save_item_get_value
* @passcase				autofill_save_item_set_value, autofill_save_item_get_value return(s) 0
* @failcase				autofill_save_item_set_value, autofill_save_item_get_value return(s) 1
* @precondition				autofill_save_item_create
* @postcondition			autofill_save_item_destroy
* */
int ITc_autofill_save_item_set_get_value_p(void)
{
	START_TEST;

	autofill_save_item_h hSaveItem = NULL;
	char *pszValue= NULL;
	int nRet = 0;

	nRet = autofill_save_item_create(&hSaveItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hSaveItem, "autofill_save_item_create");

	nRet = autofill_save_item_set_value(hSaveItem, g_pszValue);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_set_value", AutofillGetError(nRet), autofill_save_item_destroy(hSaveItem));

	nRet = autofill_save_item_get_value(hSaveItem, &pszValue);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_get_value", AutofillGetError(nRet), autofill_save_item_destroy(hSaveItem));
	CHECK_HANDLE_CLEANUP(pszValue, "autofill_save_item_get_value", autofill_save_item_destroy(hSaveItem));

	if ( 0 != strncmp(pszValue, g_pszValue, strlen(g_pszValue)) )
	{
		FPRINTF("[Line : %d][%s] autofill_save_item_get_value failed. pszValue = %s\\n", __LINE__, API_NAMESPACE, pszValue);
		FREE_MEMORY(pszValue);
		autofill_save_item_destroy(hSaveItem);
		return 1;
	}

	FREE_MEMORY(pszValue);
	nRet = autofill_save_item_destroy(hSaveItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_destroy", AutofillGetError(nRet));
	return 0;
}

/**
* @testcase				ITc_autofill_create_destroy_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Creates and destroys a handle for autofill.
* @scenario				Creates and destroys a handle for autofill.
* @apicovered				autofill_create, autofill_destroy
* @passcase				autofill_create, autofill_destroy return(s) 0
* @failcase				autofill_create, autofill_destroy return(s) 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_autofill_create_destroy_p(void)
{
	START_TEST;

	autofill_h hAutofillHandle = NULL;
	int nRet = 0;

	nRet = autofill_create(&hAutofillHandle);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_create", AutofillGetError(nRet));
	CHECK_HANDLE(hAutofillHandle, "autofill_create");

	nRet = autofill_destroy(hAutofillHandle);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_connect_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Connects to autofill daemon.
* @scenario				Creates handle and Connects to autofill daemon then destroys handle.
* @apicovered				autofill_connect
* @passcase				autofill_connect return(s) 0
* @failcase				autofill_connect return(s) 1
* @precondition				autofill_save_item_create
* @postcondition			autofill_destroy
* */
int ITc_autofill_connect_p(void)
{
	START_TEST;

	autofill_h hHandle = NULL;
	int nRet = 0;

	nRet = autofill_create(&hHandle);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_create", AutofillGetError(nRet));
	CHECK_HANDLE(hHandle, "autofill_create");

	nRet = autofill_connect(hHandle, AutofillConnectionStatusChangedCb, NULL);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_connect", AutofillGetError(nRet), autofill_destroy(hHandle));

	nRet = autofill_destroy(hHandle);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_destroy", AutofillGetError(nRet));
	return 0;
}

/**
* @testcase				ITc_autofill_auth_info_request_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Requests of authentication information.
* @scenario				Creates handles and Requests of authentication information then destroys handles.
* @apicovered				autofill_view_info_set_app_id,autofill_view_info_set_view_id,autofill_item_set_autofill_hint,autofill_item_set_id  autofill_item_set_label,autofill_item_set_sensitive_data,autofill_view_info_add_item,autofill_auth_info_request
* @passcase				APIs return(s) 0
* @failcase				APIs return(s) 1
* @precondition				autofill_create, autofill_view_info_create,autofill_item_create
* @postcondition			autofill_item_destroy, autofill_view_info_destroy, autofill_destroy
* */
int ITc_autofill_auth_info_request_p(void)
{
	START_TEST;

	char *pszAppId = NULL;
	autofill_h hAutoFillHandle = NULL;
	autofill_view_info_h hViewInfoHandle = NULL;
	autofill_item_h hItemHandle = NULL;
	g_bCallBackHit = false;

	int nRet = autofill_create(&hAutoFillHandle);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_create", AutofillGetError(nRet));
	CHECK_HANDLE(hAutoFillHandle, "autofill_create");

	nRet = autofill_connect(hAutoFillHandle, AutofillConnectionStatusChangedCb, NULL);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_connect", AutofillGetError(nRet), autofill_destroy(hAutoFillHandle));

	g_mainloop = g_main_loop_new(NULL, false);
	g_main_loop_run(g_mainloop);

	nRet = autofill_view_info_create(&hViewInfoHandle);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_create", AutofillGetError(nRet), autofill_destroy(hAutoFillHandle))
	CHECK_HANDLE_CLEANUP(hViewInfoHandle, "autofill_save_view_info_create", autofill_destroy(hAutoFillHandle));

	app_get_id(&pszAppId);

	if (pszAppId)
	{
		nRet = autofill_view_info_set_app_id(hViewInfoHandle, pszAppId);
		PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_set_view_id", AutofillGetError(nRet), FREE_MEMORY(pszAppId);autofill_view_info_destroy(hViewInfoHandle);autofill_destroy(hAutoFillHandle));
		FREE_MEMORY(pszAppId);
	}

	nRet = autofill_view_info_set_view_id(hViewInfoHandle, VIEW_ID);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_set_view_id", AutofillGetError(nRet), autofill_view_info_destroy(hViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_item_create(&hItemHandle);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_create", AutofillGetError(nRet), autofill_view_info_destroy(hViewInfoHandle);autofill_destroy(hAutoFillHandle));
	CHECK_HANDLE_CLEANUP(hItemHandle, "autofill_save_item_create", autofill_view_info_destroy(hViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_item_set_autofill_hint(hItemHandle, AUTOFILL_HINT_NAME);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_set_autofill_hint", AutofillGetError(nRet), autofill_item_destroy(hItemHandle);autofill_view_info_destroy(hViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_item_set_id(hItemHandle, "id");
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_set_id", AutofillGetError(nRet), autofill_item_destroy(hItemHandle);autofill_view_info_destroy(hViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_item_set_label(hItemHandle, "label");
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_set_label", AutofillGetError(nRet), autofill_item_destroy(hItemHandle);autofill_view_info_destroy(hViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_item_set_sensitive_data(hItemHandle, false);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_set_sensitive_data", AutofillGetError(nRet), autofill_item_destroy(hItemHandle);autofill_view_info_destroy(hViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_view_info_add_item(hViewInfoHandle, hItemHandle);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_add_item", AutofillGetError(nRet), autofill_item_destroy(hItemHandle);autofill_view_info_destroy(hViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_auth_info_request(hAutoFillHandle, hViewInfoHandle);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_request", AutofillGetError(nRet), autofill_item_destroy(hItemHandle);autofill_view_info_destroy(hViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_item_destroy(hItemHandle);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_item_destroy", AutofillGetError(nRet));

	nRet = autofill_view_info_destroy(hViewInfoHandle);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_destroy", AutofillGetError(nRet));

	if (hAutoFillHandle)
	{
		autofill_destroy(hAutoFillHandle);
	}
	hAutoFillHandle = NULL;

	return 0;
}

/**
* @testcase				ITc_autofill_auth_info_set_unset_received_cb_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and unsets the callback to receive the authentication information.
* @scenario				Creates handle and Sets and unsets the callback to receive the authentication information then destroys handle.
* @apicovered				autofill_auth_info_set_received_cb,autofill_auth_info_set_service_message, autofill_auth_info_unset_received_cb
* @passcase				autofill_auth_info_set_received_cb,autofill_auth_info_set_service_message, autofill_auth_info_unset_received_cb return(s) 0
* @failcase				autofill_auth_info_set_received_cb,autofill_auth_info_set_service_message, autofill_auth_info_unset_received_cb return(s) 1
* @precondition				autofill_create, autofill_auth_info_create
* @postcondition			autofill_auth_info_destroy, autofill_destroy
* */
int ITc_autofill_auth_info_set_unset_received_cb_p(void)
{
	START_TEST;

	autofill_h hHandle = NULL;
	int nRet = 0;
	autofill_auth_info_h hAuthInfo = NULL;

	nRet = autofill_create(&hHandle);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_create", AutofillGetError(nRet));
	CHECK_HANDLE(hHandle, "autofill_create");

        nRet = autofill_auth_info_create(&hAuthInfo);
        PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_create", AutofillGetError(nRet),autofill_destroy(hHandle));
	CHECK_HANDLE_CLEANUP(hAuthInfo, "autofill_auth_info_create", autofill_destroy(hHandle));

	nRet = autofill_auth_info_set_received_cb(hHandle, AutofillAuthInfoReceivedCb, NULL);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_set_received_cb", AutofillGetError(nRet), autofill_auth_info_destroy(hAuthInfo);autofill_destroy(hHandle));

	nRet = autofill_auth_info_set_service_message(hAuthInfo, g_pszServiceMessage);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_set_service_message", AutofillGetError(nRet),autofill_auth_info_destroy(hAuthInfo);autofill_destroy(hHandle));

	nRet = autofill_auth_info_unset_received_cb(hHandle);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_unset_received_cb", AutofillGetError(nRet), autofill_auth_info_destroy(hAuthInfo);autofill_destroy(hHandle));

        nRet = autofill_auth_info_destroy(hAuthInfo);
        PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_auth_info_destroy", AutofillGetError(nRet));

	nRet = autofill_destroy(hHandle);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_destroy", AutofillGetError(nRet));

	return 0;
}



/**
* @testcase				ITc_autofill_fill_request_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sends fill request to fill out each input form.
* @scenario				Creates handle and Sends fill request to fill out each input form then destroys handle.
* @apicovered				autofill_connect,autofill_save_view_info_set_app_id, autofill_save_view_info_set_view_id, autofill_item_set_autofill_hint, autofill_item_set_id, autofill_item_set_label,autofill_item_set_sensitive_data,autofill_save_view_info_add_item,autofill_fill_request
* @passcase				Target APIs return(s) 0
* @failcase				Target APIs return(s) 1
* @precondition				autofill_create, autofill_view_info_create, autofill_item_create
* @postcondition			autofill_item_destroy, autofill_save_view_info_destroy, autofill_destroy
* */
int ITc_autofill_fill_request_p(void)
{
	START_TEST;

	char *pszAppId = NULL;
	autofill_h hAutoFillHandle = NULL;
	autofill_save_view_info_h hSaveViewInfoHandle = NULL;
	autofill_save_item_h hItemHandle = NULL;
	g_bCallBackHit = false;

	int nRet = autofill_create(&hAutoFillHandle);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_create", AutofillGetError(nRet));
	CHECK_HANDLE(hAutoFillHandle, "autofill_create");

	nRet = autofill_connect(hAutoFillHandle, AutofillConnectionStatusChangedCb, NULL);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_connect", AutofillGetError(nRet), autofill_destroy(hAutoFillHandle));

	g_mainloop = g_main_loop_new(NULL, false);
	g_main_loop_run(g_mainloop);

	nRet = autofill_save_view_info_create(&hSaveViewInfoHandle);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_create", AutofillGetError(nRet), autofill_destroy(hAutoFillHandle))
	CHECK_HANDLE_CLEANUP(hSaveViewInfoHandle, "autofill_save_view_info_create", autofill_destroy(hAutoFillHandle));

	app_get_id(&pszAppId);

	if (pszAppId)
	{
		nRet = autofill_save_view_info_set_app_id(hSaveViewInfoHandle, pszAppId);
		PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_set_view_id", AutofillGetError(nRet), FREE_MEMORY(pszAppId);autofill_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));
		FREE_MEMORY(pszAppId);
	}

	nRet = autofill_save_view_info_set_view_id(hSaveViewInfoHandle, VIEW_ID);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_set_view_id", AutofillGetError(nRet), autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_item_create(&hItemHandle);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_item_create", AutofillGetError(nRet), autofill_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));
	CHECK_HANDLE_CLEANUP(hItemHandle, "autofill_save_item_create", autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_item_set_autofill_hint(hItemHandle, AUTOFILL_HINT_NAME);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_item_set_autofill_hint", AutofillGetError(nRet), autofill_item_destroy(hItemHandle);autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_item_set_id(hItemHandle, "id");
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_item_set_id", AutofillGetError(nRet), autofill_item_destroy(hItemHandle);autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_item_set_label(hItemHandle, "label");
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_item_set_label", AutofillGetError(nRet), autofill_item_destroy(hItemHandle);autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_item_set_sensitive_data(hItemHandle, false);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_item_set_sensitive_data", AutofillGetError(nRet), autofill_item_destroy(hItemHandle);autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_save_view_info_add_item(hSaveViewInfoHandle, hItemHandle);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_add_item", AutofillGetError(nRet), autofill_item_destroy(hItemHandle);autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_fill_request(hAutoFillHandle, hSaveViewInfoHandle);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_request", AutofillGetError(nRet), autofill_item_destroy(hItemHandle);autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_item_destroy(hItemHandle);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_item_destroy", AutofillGetError(nRet));

	nRet = autofill_save_view_info_destroy(hSaveViewInfoHandle);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_destroy", AutofillGetError(nRet));

	if (hAutoFillHandle)
	{
		autofill_destroy(hAutoFillHandle);
	}
	hAutoFillHandle = NULL;

	return 0;
}

/**
* @testcase				ITc_autofill_fill_response_set_unset_received_cb_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and unsets the callback to receive autofill fill response.
* @scenario				Creates handle and Sets and unsets the callback to receive autofill fill response then destroys handle.
* @apicovered				autofill_fill_response_set_received_cb, autofill_fill_response_unset_received_cb
* @passcase				autofill_fill_response_set_received_cb, autofill_fill_response_unset_received_cb return(s) 0
* @failcase				autofill_fill_response_set_received_cb, autofill_fill_response_unset_received_cb return(s) 1
* @precondition				autofill_create
* @postcondition			autofill_destroy
* */
int ITc_autofill_fill_response_set_unset_received_cb_p(void)
{
	START_TEST;

	autofill_h hHandle = NULL;
	int nRet = 0;

	nRet = autofill_create(&hHandle);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_create", AutofillGetError(nRet));
	CHECK_HANDLE(hHandle, "autofill_create");

	nRet = autofill_fill_response_set_received_cb(hHandle, AutofillFillResponseReceivedCb, NULL);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_set_received_cb", AutofillGetError(nRet), autofill_destroy(hHandle));

	nRet = autofill_fill_response_unset_received_cb(hHandle);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_unset_received_cb", AutofillGetError(nRet), autofill_destroy(hHandle));

	nRet = autofill_destroy(hHandle);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_destroy", AutofillGetError(nRet));
	return 0;
}

/**
* @testcase				ITc_autofill_commit_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sends the autofill save view info.
* @scenario				Creates handles and Sends the autofill save view info then destroys handles.
* @apicovered				autofill_connect, autofill_save_view_info_set_app_id, autofill_save_view_info_set_view_id, autofill_save_item_set_autofill_hint, autofill_save_item_set_id, autofill_save_item_set_label, autofill_save_item_set_sensitive_data, autofill_save_view_info_add_item, autofill_commit
* @passcase				Target APIs return(s) 0
* @failcase				Target APIs return(s) 1
* @precondition				autofill_create, autofill_save_view_info_create, autofill_save_item_create
* @postcondition			autofill_save_item_destroy, autofill_save_view_info_destroy, autofill_destroy
* */
int ITc_autofill_commit_p(void)
{
	START_TEST;

	char *pszAppId = NULL;
	autofill_h hAutoFillHandle = NULL;
	autofill_save_view_info_h hSaveViewInfoHandle = NULL;
	autofill_save_item_h hItemHandle = NULL;
	g_bCallBackHit = false;

	int nRet = autofill_create(&hAutoFillHandle);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_create", AutofillGetError(nRet));
	CHECK_HANDLE(hAutoFillHandle, "autofill_create");

	nRet = autofill_connect(hAutoFillHandle, AutofillConnectionStatusChangedCb, NULL);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_connect", AutofillGetError(nRet), autofill_destroy(hAutoFillHandle));

	g_mainloop = g_main_loop_new(NULL, false);
	g_main_loop_run(g_mainloop);

	nRet = autofill_save_view_info_create(&hSaveViewInfoHandle);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_create", AutofillGetError(nRet), autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));
	CHECK_HANDLE_CLEANUP(hSaveViewInfoHandle, "autofill_save_view_info_create", autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));

	app_get_id(&pszAppId);

	if (pszAppId)
	{
		nRet = autofill_save_view_info_set_app_id(hSaveViewInfoHandle, pszAppId);
		PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_set_view_id", AutofillGetError(nRet), FREE_MEMORY(pszAppId);autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));
		FREE_MEMORY(pszAppId);
	}

	nRet = autofill_save_view_info_set_view_id(hSaveViewInfoHandle, VIEW_ID);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_set_view_id", AutofillGetError(nRet), autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_save_item_create(&hItemHandle);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_create", AutofillGetError(nRet), autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));
	CHECK_HANDLE_CLEANUP(hItemHandle, "autofill_save_item_create", autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_save_item_set_autofill_hint(hItemHandle, AUTOFILL_HINT_NAME);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_set_autofill_hint", AutofillGetError(nRet), autofill_save_item_destroy(hItemHandle);autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_save_item_set_id(hItemHandle, "id");
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_set_id", AutofillGetError(nRet), autofill_save_item_destroy(hItemHandle);autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_save_item_set_label(hItemHandle, "label");
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_set_label", AutofillGetError(nRet), autofill_save_item_destroy(hItemHandle);autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_save_item_set_sensitive_data(hItemHandle, false);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_set_sensitive_data", AutofillGetError(nRet), autofill_save_item_destroy(hItemHandle);autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_save_view_info_add_item(hSaveViewInfoHandle, hItemHandle);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_add_item", AutofillGetError(nRet), autofill_save_item_destroy(hItemHandle);autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_commit(hAutoFillHandle, hSaveViewInfoHandle);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_commit", AutofillGetError(nRet), autofill_save_item_destroy(hItemHandle);autofill_save_view_info_destroy(hSaveViewInfoHandle);autofill_destroy(hAutoFillHandle));

	nRet = autofill_save_item_destroy(hItemHandle);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_save_item_destroy", AutofillGetError(nRet));

	nRet = autofill_save_view_info_destroy(hSaveViewInfoHandle);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_save_view_info_destroy", AutofillGetError(nRet));

	if (hAutoFillHandle)
	{
		autofill_destroy(hAutoFillHandle);
	}
	hAutoFillHandle = NULL;

	return 0;
}

/**
* @testcase			ITc_autofill_fill_response_item_set_get_autofill_hint_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(manoj.g2)
* @type			auto
* @description			Sets and Gets the autofill hint in an autofill fill response item.
* @scenario			Creates handle and Sets and gets the autofill hint in an autofill fill response item then destroys handle.
* @apicovered			autofill_fill_response_item_set_autofill_hint, autofill_fill_response_item_get_autofill_hint
* @passcase			autofill_fill_response_item_set_autofill_hint, autofill_fill_response_item_get_autofill_hint return(s) 0
* @failcase			autofill_fill_response_item_set_autofill_hint, autofill_fill_response_item_get_autofill_hint return(s) 1
* @precondition			autofill_fill_response_item_create
* @postcondition			autofill_fill_response_item_destroy
* */
int ITc_autofill_fill_response_item_set_get_autofill_hint_p(void)
{
	START_TEST;

	int nRet = 0;
	autofill_fill_response_item_h hFillResponseItem = NULL;

	autofill_hint_e eAutoFillHintArr[] =
	{
		AUTOFILL_HINT_CREDIT_CARD_EXPIRATION_DATE,
		AUTOFILL_HINT_CREDIT_CARD_EXPIRATION_DAY,
		AUTOFILL_HINT_CREDIT_CARD_EXPIRATION_MONTH,
		AUTOFILL_HINT_CREDIT_CARD_EXPIRATION_YEAR,
		AUTOFILL_HINT_CREDIT_CARD_NUMBER,
		AUTOFILL_HINT_EMAIL_ADDRESS,
		AUTOFILL_HINT_NAME,
		AUTOFILL_HINT_PHONE,
		AUTOFILL_HINT_POSTAL_ADDRESS,
		AUTOFILL_HINT_POSTAL_CODE,
		AUTOFILL_HINT_ID,
		AUTOFILL_HINT_PASSWORD,
		AUTOFILL_HINT_CREDIT_CARD_SECURITY_CODE
	};

	nRet = autofill_fill_response_item_create(&hFillResponseItem);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_create", AutofillGetError(nRet));
	CHECK_HANDLE(hFillResponseItem, "autofill_fill_response_item_create");

	int nFilHintSize = sizeof(eAutoFillHintArr)/sizeof(eAutoFillHintArr[0]);
	autofill_hint_e eAutoFillHint;
	int nAutoFillHintCnt;

	for(nAutoFillHintCnt = 0; nAutoFillHintCnt < nFilHintSize; nAutoFillHintCnt++)
	{
		nRet = autofill_fill_response_item_set_autofill_hint(hFillResponseItem, eAutoFillHintArr[nAutoFillHintCnt]);
		PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_set_autofill_hint", AutofillGetError(nRet), autofill_fill_response_item_destroy(hFillResponseItem));

		nRet = autofill_fill_response_item_get_autofill_hint(hFillResponseItem, &eAutoFillHint);
		PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_get_autofill_hint", AutofillGetError(nRet), autofill_fill_response_item_destroy(hFillResponseItem));

		PRINT_RESULT_CLEANUP(eAutoFillHint, eAutoFillHintArr[nAutoFillHintCnt], "autofill_fill_response_item_get_autofill_hint", "Get Hint and Set Hint values are not same", autofill_fill_response_item_destroy(hFillResponseItem));
	}

	nRet = autofill_fill_response_item_destroy(hFillResponseItem);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_fill_response_item_destroy", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase                     ITc_autofill_view_info_cancel_fill_request_p
* @since_tizen                  5.5
* @author                       SRID(manoj.g2)
* @reviewer                     SRID(shobhit.v)
* @type                 	auto
* @description                  API to check for cancelling auto fill request
* @scenario                     Creates handle and check for cancelling auto fill request 
* @apicovered                   autofill_cancel_fill_request
* @passcase                     autofill_cancel_fill_request and Precondition API return(s) 0
* @failcase                     autofill_cancel_fill_request or Precondition API return(s) 1
* @precondition                 NA
* @postcondition                NA
* */
int ITc_autofill_view_info_cancel_fill_request_p(void)
{
        START_TEST;
        autofill_h hAutoFillHandle = NULL;
        autofill_view_info_h hViewInfo = NULL;
        g_bCallBackHit = false;

        int nRet = autofill_create(&hAutoFillHandle);
        PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_create", AutofillGetError(nRet));
        CHECK_HANDLE(hAutoFillHandle, "autofill_create");

        nRet = autofill_connect(hAutoFillHandle, AutofillConnectionStatusChangedCb, NULL);
        PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_connect", AutofillGetError(nRet), autofill_destroy(hAutoFillHandle));

        g_mainloop = g_main_loop_new(NULL, false);
        g_main_loop_run(g_mainloop);

        PRINT_RESULT_CLEANUP(g_bCallBackHit, true, "autofill_connect", AutofillGetError(nRet), autofill_destroy(hAutoFillHandle));

	nRet = autofill_view_info_create(&hViewInfo);
        PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_create", AutofillGetError(nRet), autofill_destroy(hAutoFillHandle));
        CHECK_HANDLE_CLEANUP(hViewInfo, "autofill_view_info_create", autofill_destroy(hAutoFillHandle));

	nRet = autofill_view_info_set_app_id(hViewInfo, g_pszAppId);
        PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_set_app_id", AutofillGetError(nRet), autofill_view_info_destroy(hViewInfo);autofill_destroy(hAutoFillHandle));

	nRet = autofill_view_info_set_view_id(hViewInfo, g_pszViewId);
        PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_set_view_id", AutofillGetError(nRet), autofill_view_info_destroy(hViewInfo);autofill_destroy(hAutoFillHandle));

	nRet = autofill_cancel_fill_request(hAutoFillHandle, hViewInfo);
	PRINT_RESULT_CLEANUP(nRet, AUTOFILL_ERROR_NONE, "autofill_cancel_fill_request", AutofillGetError(nRet), autofill_view_info_destroy(hViewInfo);autofill_destroy(hAutoFillHandle));

	nRet = autofill_view_info_destroy(hViewInfo);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_view_info_destroy", AutofillGetError(nRet));

	nRet = autofill_destroy(hAutoFillHandle);
	PRINT_RESULT_NORETURN(nRet, AUTOFILL_ERROR_NONE, "autofill_destroy", AutofillGetError(nRet));
}
/** @} */
/** @} */
