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
void ITs_autofill_service_startup(void)
{
	g_bAutofillServiceCreation = false;
	int nRet = autofill_service_initialize();

	if ( nRet != AUTOFILL_ERROR_NONE)
	{
		FPRINTF("[%s:%d] autofill_service_initialize failed in startup, error returned = %s (%d)\\n", __FILE__, __LINE__, AutofillGetError(nRet), nRet);
		g_bAutofillServiceCreation = true;
	}
	return;
}

void ITs_autofill_service_cleanup(void)
{
	autofill_service_deinitialize();
}


/**
* @function 		AutofillServiceTerminateReceivedCb
* @description	 	Callback Function to receive the terminate request.
* @parameters		void *user_data
* @return 		NA
*/
void AutofillServiceTerminateReceivedCb(void *user_data)
{
	FPRINTF("[Line: %d][%s] AutofillServiceTerminateReceivedCb Callback invoked\\n", __LINE__, API_NAMESPACE);
	g_bCallBackHit = true;
	return;
}

/**
* @function 		AutofillServiceCancelFillRequestCb
* @description	 	Callback Function to cancel fill request.
* @parameters		int nContextId, autofill_save_view_info_h hAutofillSaveViewInfo, void *user_data
* @return 		NA
*/
void AutofillServiceCancelFillRequestCb(int nContextId, autofill_view_info_h hAutofillViewInfo, void *user_data)
{
	FPRINTF("[Line: %d][%s] AutofillServiceCancelFillRequestCb Callback invoked\\n", __LINE__, API_NAMESPACE);
	g_bCallBackHit = true;
	return;
}

/**
* @function 		AutofillServiceCommittedCb
* @description	 	Callback Function to receive the commit request.
* @parameters		int nContextId, autofill_save_view_info_h hAutofillSaveViewInfo, void *user_data
* @return 		NA
*/
void AutofillServiceCommittedCb(int nContextId, autofill_save_view_info_h hAutofillSaveViewInfo, void *user_data)
{
	FPRINTF("[Line: %d][%s] AutofillServiceCommittedCb Callback invoked\\n", __LINE__, API_NAMESPACE);
	g_bCallBackHit = true;
	return;
}

/**
* @function 		AutofillServiceFillRequestedCb
* @description	 	Callback Function to receive the fill request.
* @parameters		int nContextId, autofill_view_info_h hAutofillViewInfo, void *user_data
* @return 		NA
*/
void AutofillServiceFillRequestedCb(int nContextId, autofill_view_info_h hAutofillViewInfo, void *user_data)
{
	FPRINTF("[Line: %d][%s] AutofillServiceFillRequestedCb Callback invoked\\n", __LINE__, API_NAMESPACE);
	g_bCallBackHit = true;
	return;
}

/**
* @function 		AutofillServiceAuthInfoRequestedCb
* @description	 	Callback Function to receive the request of authentication information.
* @parameters		int nContextId, autofill_view_info_h hAutofillViewInfo, void *user_data
* @return 		NA
*/
void AutofillServiceAuthInfoRequestedCb(int nContextId, autofill_view_info_h hAutofillViewInfo, void *user_data)
{
	FPRINTF("[Line: %d][%s] AutofillServiceAuthInfoRequestedCb Callback invoked\\n", __LINE__, API_NAMESPACE);
	g_bCallBackHit = true;
	return;
}

/**
* @function 		AutofillConnectionStatusChangedCb
* @description	 	Callback Function to receive change status of connection.
* @parameters		autofill_h hAutofill, autofill_connection_status_e eAutofillConnectionStatus, void * user_data
* @return 		NA
*/
void AutofillConnectionstatusChangedCb(autofill_h hAutofill, autofill_connection_status_e eAutofillConnectionStatus, void * user_data)
{
        FPRINTF("[Line: %d][%s] AutofillConnectionStatusChangedCb Callback invoked\\n", __LINE__, API_NAMESPACE);
        g_bCallBackHit = true;
}

/**
* @testcase				ITc_autofill_service_initialize_deinitialize_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Initializes and deinitializes autofill service library.
* @scenario				Initializes and deinitializes autofill service library.
* @apicovered				autofill_service_initialize, autofill_service_deinitialize
* @passcase				autofill_service_initialize, autofill_service_deinitialize return(s) 0
* @failcase				autofill_service_initialize, autofill_service_deinitialize return(s) 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_autofill_service_initialize_deinitialize_p(void)
{
	START_TEST_CHECK_INITIALIZE;
	int nRet = 0;

	nRet = autofill_service_deinitialize();
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_service_deinitialize", AutofillGetError(nRet));

	nRet = autofill_service_initialize();
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_service_initialize", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_service_set_unset_auth_info_requested_cb_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and unsets the callback to receive the request of authentication information.
* @scenario				Sets and unsets the callback to receive the request of authentication information.
* @apicovered				autofill_service_set_auth_info_requested_cb, autofill_service_unset_auth_info_requested_cb
* @passcase				autofill_service_set_auth_info_requested_cb, autofill_service_unset_auth_info_requested_cb return(s) 0
* @failcase				autofill_service_set_auth_info_requested_cb, autofill_service_unset_auth_info_requested_cb return(s) 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_autofill_service_set_unset_auth_info_requested_cb_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	int nRet = 0;
	nRet = autofill_service_set_auth_info_requested_cb(AutofillServiceAuthInfoRequestedCb, NULL);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_service_set_auth_info_requested_cb", AutofillGetError(nRet));

	nRet = autofill_service_unset_auth_info_requested_cb();
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_service_unset_auth_info_requested_cb", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_service_set_unset_fill_requested_cb_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and unsets the callback to receive the fill request.
* @scenario				Sets and unsets the callback to receive the fill request.
* @apicovered				autofill_service_set_fill_requested_cb, autofill_service_unset_fill_requested_cb
* @passcase				autofill_service_set_fill_requested_cb, autofill_service_unset_fill_requested_cb return(s) 0
* @failcase				autofill_service_set_fill_requested_cb, autofill_service_unset_fill_requested_cb return(s) 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_autofill_service_set_unset_fill_requested_cb_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	int nRet = 0;

	nRet = autofill_service_set_fill_requested_cb(AutofillServiceFillRequestedCb, NULL);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_service_set_fill_requested_cb", AutofillGetError(nRet));

	nRet = autofill_service_unset_fill_requested_cb();
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_service_unset_fill_requested_cb", AutofillGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_autofill_service_set_unset_committed_cb_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and unsets the callback to receive the commit request.
* @scenario				Sets and unsets the callback to receive the commit request.
* @apicovered				autofill_service_set_committed_cb, autofill_service_unset_commited_cb
* @passcase				autofill_service_set_committed_cb, autofill_service_unset_commited_cb return(s) 0
* @failcase				autofill_service_set_committed_cb, autofill_service_unset_commited_cb return(s) 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_autofill_service_set_unset_committed_cb_p(void)
{
	START_TEST_CHECK_INITIALIZE;
	int nRet = 0;

	nRet = autofill_service_set_committed_cb(AutofillServiceCommittedCb, NULL);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_service_set_committed_cb", AutofillGetError(nRet));

	nRet = autofill_service_unset_committed_cb();
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_service_unset_committed_cb", AutofillGetError(nRet));


	return 0;
}

/**
* @testcase				ITc_autofill_service_set_unset_terminate_received_cb_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and unsets the callback to receive the terminate request.
* @scenario				Sets and unsets the callback to receive the terminate request.
* @apicovered				autofill_service_set_terminate_received_cb, autofill_service_unset_terminate_received_cb
* @passcase				autofill_service_set_terminate_received_cb, autofill_service_unset_terminate_received_cb return(s) 0
* @failcase				autofill_service_set_terminate_received_cb, autofill_service_unset_terminate_received_cb return(s) 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_autofill_service_set_unset_terminate_received_cb_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	int nRet = 0;
	nRet = autofill_service_set_terminate_received_cb(AutofillServiceTerminateReceivedCb, NULL);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_service_set_terminate_received_cb", AutofillGetError(nRet));

	nRet = autofill_service_unset_terminate_received_cb();
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_service_unset_terminate_received_cb", AutofillGetError(nRet));

	return 0;
}


/**
* @testcase				ITc_autofill_service_set_unset_cancel_fill_requested_cb_p
* @since_tizen				5.5
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description				Sets and unsets the callback to cancel fill request.
* @scenario				Sets and unsets the callback to cancel fill request.
* @apicovered				autofill_service_set_terminate_received_cb, autofill_service_unset_terminate_received_cb
* @passcase				autofill_service_set_terminate_received_cb, autofill_service_unset_terminate_received_cb return(s) 0
* @failcase				autofill_service_set_terminate_received_cb, autofill_service_unset_terminate_received_cb return(s) 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_autofill_service_set_unset_cancel_fill_requested_cb_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	int nRet = -1;
	nRet = autofill_service_set_cancel_fill_requested_cb(AutofillServiceCancelFillRequestCb, NULL);
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_service_set_cancel_fill_requested_cb", AutofillGetError(nRet));

	nRet = autofill_service_unset_cancel_fill_requested_cb();
	PRINT_RESULT(nRet, AUTOFILL_ERROR_NONE, "autofill_service_unset_cancel_fill_requested_cb", AutofillGetError(nRet));

	return 0;
}
