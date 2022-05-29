//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
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
#include "ITs-telephony-common.h"

/** @addtogroup itc-telephony
*  @ingroup itc
*  @{
*/
//& set: Telephony

bool g_bTelephonyInit;
telephony_handle_list_s g_stTelephonyHandleList = {0};
telephony_h g_pstTelephonySIMHandle = NULL;
bool g_bTelephonyIssupportedFeature = false;
bool g_bTelephonySkipExecutionWithPass = false;
bool g_bTelephonySkipExecutionWithFail = false;

/**
* @function			telephony_state_changed_callback
* @description		Callback function to indicate change in telephony state
* @parameter		telephony_state_e state - changed state, void* user_data - User data
* @return			NA
*/
static void telephony_state_changed_callback(telephony_state_e state, void* user_data)
{
}

/**
* @function 		ITs_telephony_startup
* @description	 	Called before each test, Acquire the list of available handles to use telephony API.
* @parameter		NA
* @return 			NA
*/
void ITs_telephony_startup(void)
{
	g_bTelephonyInit = false;
	g_bTelephonySkipExecutionWithPass = false;
	g_bTelephonySkipExecutionWithFail = false;
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Telephony_p\\n", __LINE__, API_NAMESPACE);
#endif

	IS_FEATURE_SUPPORTED(TELEPHONY_FEATURE, g_bTelephonyIssupportedFeature, API_NAMESPACE);

	int nRet = telephony_init(&g_stTelephonyHandleList);

	if ( (g_bTelephonyIssupportedFeature == false) && (nRet == TIZEN_ERROR_NOT_SUPPORTED) )
	{
		g_bTelephonySkipExecutionWithPass = true;
		FPRINTF("[Line : %d][%s] telephony_init returned TIZEN_ERROR_NOT_SUPPORTED, also feature %s value returned from model-config.xml is false \\n", __LINE__, API_NAMESPACE, TELEPHONY_FEATURE);
		return;
	}
	else if ( (g_bTelephonyIssupportedFeature == false) && (nRet != TIZEN_ERROR_NOT_SUPPORTED))
	{
		g_bTelephonySkipExecutionWithFail = true;
		FPRINTF("[Line : %d][%s] telephony_init did not return TIZEN_ERROR_NOT_SUPPORTED, although feature %s value returned from model-config.xml is false \\n", __LINE__, API_NAMESPACE, TELEPHONY_FEATURE);
		return;
	}

	else if ( nRet != TELEPHONY_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] telephony_init failed, error returned = %s \\n", __LINE__, API_NAMESPACE, TelephonyGetError(nRet));
		g_bTelephonyInit = false;
		return;
	}

	if ( !TelephonyGetSimHandle(g_stTelephonyHandleList.count) )
	{
		g_bTelephonyInit = false;
		return;
	}

	bool bWifiFeatureSupported = TCTCheckSystemInfoFeatureSupported(WIFI_FEATURE, API_NAMESPACE);
	bool bEthernetFeatureSupported = TCTCheckSystemInfoFeatureSupported(ETHERNET_FEATURE, API_NAMESPACE);
	bool bBtFeatureSupported = TCTCheckSystemInfoFeatureSupported(TETHERING_BLUETOOTH_FEATURE, API_NAMESPACE);
	
	connection_h hConenctionHandle = NULL;
	connection_cellular_state_e eState;
	
	nRet = connection_create(&hConenctionHandle);
	if ( false == g_bTelephonyIssupportedFeature && false == bWifiFeatureSupported && false == bBtFeatureSupported && false == bEthernetFeatureSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line: %d][%s] connection_create API call returned mismatch %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			g_bTelephonySkipExecutionWithFail = true;
		}
		else
		{
			FPRINTF("[Line: %d][%s] connection_create API call correctly returned %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			g_bTelephonySkipExecutionWithPass = true;
		}
		return;
	}

	if ( nRet != CONNECTION_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] Startup failed on connection create API returned error %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
		g_bTelephonyInit = false;
		return;
	}
	
	if ( hConenctionHandle == NULL )
	{
		FPRINTF("[Line: %d][%s] Startup failed on connection create returned handle = NULL\\n", __LINE__, API_NAMESPACE);
		g_bTelephonyInit = false;
		return;
	}
	
	nRet = connection_get_cellular_state(hConenctionHandle, &eState);
    if ( nRet != CONNECTION_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] Startup failed on get cellular state\\n", __LINE__, API_NAMESPACE);
		g_bTelephonyInit = false;
		return;
	}
    if (eState == CONNECTION_CELLULAR_STATE_OUT_OF_SERVICE)
	{
		FPRINTF("[Line: %d][%s] Cellular state is out of service\\n", __LINE__, API_NAMESPACE);
		g_bTelephonySkipExecutionWithPass = true;
		return;
	}
	
	if ( hConenctionHandle != NULL )
	{
		connection_destroy(hConenctionHandle);
	}
	
#if DEBUG
	FPRINTF("[Line : %d][%s] telephony_init successful in startup\\n", __LINE__, API_NAMESPACE);
#endif
	g_bTelephonyInit = true;
}

/**
* @function 		ITs_telephony_cleanup
* @description	 	Called after each test, Deinitialize telephony handle list.
* @parameter		NA
* @return 			NA
*/
void ITs_telephony_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Telephony_p\\n", __LINE__, API_NAMESPACE);
#endif

	if ( g_bTelephonyInit == true )
	{
		int nRet = telephony_deinit(&g_stTelephonyHandleList);
		if ( nRet != TELEPHONY_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] telephony_init failed, error returned = %s \\n", __LINE__, API_NAMESPACE, TelephonyGetError(nRet));
			return;
		}
#if DEBUG
		FPRINTF("[Line : %d][%s] telephony_deinit successful in cleanup\\n", __LINE__, API_NAMESPACE);
#endif
	}
}

/** @addtogroup itc-telephony-testcases
*  @brief 		Integration testcases for module telephony
*  @ingroup 	itc-telephony
*  @{
*/

//& purpose: To acquire the list of available handles and Deinitialize telephony handle list
//& type: auto
/**
* @testcase 			ITc_telephony_init_deinit_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To acquire the list of available handles and Deinitialize telephony handle list
* @scenario				acquire the list of available handles and verify output\n
*						Deinitialize telephony handle list and verify output
* @apicovered			telephony_init, telephony_deinit
* @passcase				When telephony_init, telephony_deinit return success
* @failcase				When telephony_init or telephony_deinit return failure
* @precondition			telephony service should be initialized
* @postcondition		NA
*/
int ITc_telephony_init_deinit_p(void)
{
	START_TEST;

	telephony_handle_list_s stTelephonyHandleListLocal = {0};
	int nRetVal = telephony_init(&stTelephonyHandleListLocal);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRetVal, "telephony_init", TelephonyGetError(nRetVal));

	if ( stTelephonyHandleListLocal.count <= 0 )
	{
		FPRINTF("[Line : %d][%s] telephony_init failed, error returned = list returned is empty \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = telephony_deinit(&stTelephonyHandleListLocal);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRetVal, "telephony_deinit", TelephonyGetError(nRetVal));

	return 0;
}


//& purpose: To set and unset a callback function to be invoked when the telephony state changes.
//& type: auto
/**
* @testcase 			ITc_telephony_set_unset_noti_cb_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			to set and unset a callback function to be invoked when the telephony state changes.
* @scenario				set a callback function to be invoked when the telephony state changes\n
*						unset the callback function
* @apicovered			telephony_set_noti_cb, telephony_unset_noti_cb
* @passcase				When telephony_set_noti_cb, telephony_unset_noti_cb return success
* @failcase				When telephony_set_noti_cb or telephony_unset_noti_cb return failure
* @precondition			telephony service should be initialized
* @postcondition		NA
*/
int ITc_telephony_set_unset_noti_cb_p(void)
{
	START_TEST;

	int nRetVal = telephony_set_noti_cb(g_pstTelephonySIMHandle, TELEPHONY_NOTI_NETWORK_SERVICE_STATE, NULL, NULL);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRetVal, "telephony_set_noti_cb", TelephonyGetError(nRetVal));
	nRetVal = telephony_unset_noti_cb(g_pstTelephonySIMHandle, TELEPHONY_NOTI_NETWORK_SERVICE_STATE);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRetVal, "telephony_unset_noti_cb", TelephonyGetError(nRetVal));
	return 0;
}

//& type: auto
//& purpose: get the power status of the modem
/**
* @testcase 			ITc_telephony_modem_get_power_status_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			Gets the power status of the modem
* @scenario				Gets the power status of the modem
* @apicovered			telephony_modem_get_power_status
* @passcase				if telephony_modem_get_power_status returns 0 on success
* @failcase				if telephony_modem_get_power_status returns negative error value
* @precondition			working SIM card must be present in device
* @postcondition		NA
*/
int ITc_telephony_modem_get_power_status_p(void)
{
	START_TEST;

	telephony_modem_power_status_e status = 0;
	int nRet = telephony_modem_get_power_status(g_pstTelephonySIMHandle, &status);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_modem_get_power_status", TelephonyGetError(nRet));
	if ( status == TELEPHONY_MODEM_POWER_STATUS_UNKNOWN )
	{
		FPRINTF("[Line : %d][%s] TELEPHONY_MODEM_POWER_STATUS_UNKNOWN telephony_modem_get_power_status failed,\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& type: auto
//& purpose: get the telephony state
/**
* @testcase				ITc_telephony_get_state_p
* @author				HQ SQE(sangwoo7.lee)
* @reviewer				HQ SQE(jk79.lee)
* @type					auto
* @since_tizen			2.4
* @description			Gets the telephony state
* @scenario				Gets the telephony state
* @apicovered			telephony_get_state
* @passcase				if telephony_get_state returns 0 and returned state is valid
* @failcase				if telephony_get_state returns negative error value or returned state is invalid
* @precondition			working SIM card must be present in device
* @postcondition		NA
*/
int ITc_telephony_get_state_p(void)
{
	START_TEST;

	telephony_state_e state = -1;
	int nRet = telephony_get_state(&state);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_get_state", TelephonyGetError(nRet));
	if ( state == TELEPHONY_STATE_NOT_READY || state == TELEPHONY_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] telephony_get_state succeed, returned %s\\n", __LINE__, API_NAMESPACE, TelephonyGetState(state));
	}
	else
	{
		FPRINTF("[Line : %d][%s] telephony_get_state failed, returned unknown state\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& type: auto
//& purpose: To set and unset a callback function to be invoked when the telephony state changes.
/**
* @testcase				ITc_telephony_set_unset_state_changed_cb_p
* @author				HQ SQE(sangwoo7.lee)
* @reviewer				HQ SQE(jk79.lee)
* @type					auto
* @since_tizen			2.4
* @description			to set and unset a callback function to be invoked when the telephony state changes.
* @scenario				set a callback function to be invoked when the telephony state changes\n
*						unset the callback function
* @apicovered			telephony_set_state_changed_cb, telephony_unset_state_changed_cb
* @passcase				When telephony_set_state_changed_cb and telephony_unset_state_changed_cb return 0
* @failcase				When telephony_set_state_changed_cb or telephony_unset_state_changed_cb returns negative error value
* @precondition			working SIM card must be present in device
* @postcondition		NA
*/
int ITc_telephony_set_unset_state_changed_cb_p(void)
{
	START_TEST;

	int nRetVal = telephony_set_state_changed_cb(telephony_state_changed_callback, NULL);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRetVal, "telephony_set_state_changed_cb", TelephonyGetError(nRetVal));
	nRetVal = telephony_unset_state_changed_cb(telephony_state_changed_callback);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRetVal, "telephony_unset_state_changed_cb", TelephonyGetError(nRetVal));
	return 0;
}

/** @} */
/** @} */
