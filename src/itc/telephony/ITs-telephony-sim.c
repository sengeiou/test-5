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

extern bool g_bTelephonyInit;
extern telephony_handle_list_s g_stTelephonyHandleList;
extern telephony_h g_pstTelephonySIMHandle;
extern bool g_bTelephonyIssupportedFeature ;
extern bool g_bTelephonySkipExecutionWithPass ;
extern bool g_bTelephonySkipExecutionWithFail ;

/**
* @function 		ITs_telephony_sim_startup
* @description	 	Called before each test, Acquire the list of available handles to use telephony API.
* @parameter		NA
* @return 			NA
*/
void ITs_telephony_sim_startup(void)
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
* @function 		ITs_telephony_sim_cleanup
* @description	 	Called after each test, Deinitialize telephony handle list.
* @parameter		NA
* @return 			NA
*/
void ITs_telephony_sim_cleanup(void)
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

//& type: auto
//& purpose: get the SIM Operator (MCC + MNC)
/**
* @testcase 			ITc_telephony_sim_get_operator_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			to get the SIM Operator (MCC + MNC)
* @scenario				get the SIM Operator (MCC + MNC)
* @apicovered			telephony_sim_get_operator
* @passcase				if telephony_sim_get_operator returns success
* @failcase				if telephony_sim_get_operator returns failure
* @precondition			working SIM card must be present in device, network service state of SIM must be TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE and SIM state must be TELEPHONY_SIM_STATE_AVAILABLE.
* @postcondition		NA
*/
int ITc_telephony_sim_get_operator_p(void)
{
	START_TEST;

	char *pszGetValue = NULL;
	int nRet = 0;
	CHECK_SIM_STATE;

	// Target API
	nRet = telephony_sim_get_operator(g_pstTelephonySIMHandle, &pszGetValue);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_sim_get_operator", TelephonyGetError(nRet));
	CHECK_VALUE_STRING(pszGetValue, "telephony_sim_get_operator");
	return 0;
}

//& type: auto
//& purpose: get Mobile Subscription Identification Number (MSIN) of SIM provider
/**
* @testcase 			ITc_telephony_sim_get_msin_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			to get the Mobile Subscription Identification Number (MSIN) of SIM provider
* @scenario				get the Mobile Subscription Identification Number (MSIN) of SIM provider
* @apicovered			telephony_sim_get_msin
* @passcase				if telephony_sim_get_msin returns success
* @failcase				if telephony_sim_get_msin returns failure
* @precondition			working SIM card must be present in device, network service state of SIM must be TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE and SIM state must be TELEPHONY_SIM_STATE_AVAILABLE.
* @postcondition		NA
*/
int ITc_telephony_sim_get_msin_p(void)
{
	START_TEST;

	char *pszGetValue = NULL;
	int nRet = 0;
	CHECK_SIM_STATE;

	// Target API
	nRet = telephony_sim_get_msin(g_pstTelephonySIMHandle, &pszGetValue);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_sim_get_msin", TelephonyGetError(nRet));
	CHECK_VALUE_STRING(pszGetValue, "telephony_sim_get_msin");
	return 0;
}

//& type: auto
//& purpose: get the Service Provider Name (SPN) of SIM card.
/**
* @testcase 			ITc_telephony_sim_get_spn_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			to get the Service Provider Name (SPN) of SIM card.
* @scenario				get the Service Provider Name (SPN) of SIM card.
* @apicovered			telephony_sim_get_spn
* @passcase				if telephony_sim_get_spn returns success
* @failcase				if telephony_sim_get_spn returns failure
* @precondition			working SIM card must be present in device, network service state of SIM must be TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE and SIM state must be TELEPHONY_SIM_STATE_AVAILABLE.
* @postcondition		NA
*/
int ITc_telephony_sim_get_spn_p(void)
{
	START_TEST;

	char *pszGetValue = NULL;
	int nRet = 0;
	CHECK_SIM_STATE;

	// Target API
	nRet = telephony_sim_get_spn(g_pstTelephonySIMHandle, &pszGetValue);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_sim_get_spn", TelephonyGetError(nRet));
	CHECK_VALUE_STRING(pszGetValue, "telephony_sim_get_spn");
	return 0;
}

//& type: auto
//& purpose: get the SIM card subscriber number
/**
* @testcase 			ITc_telephony_sim_get_subscriber_number_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			to get the SIM card subscriber number
* @scenario				get the SIM card subscriber number
* @apicovered			telephony_sim_get_subscriber_number
* @passcase				if telephony_sim_get_subscriber_number returns success
* @failcase				if telephony_sim_get_subscriber_number returns failure
* @precondition			working SIM card must be present in device, network service state of SIM must be TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE and SIM state must be TELEPHONY_SIM_STATE_AVAILABLE.
* @postcondition		NA
*/
int ITc_telephony_sim_get_subscriber_number_p(void)
{
	START_TEST;

	char *pszGetValue = NULL;
	int nRet = 0;
	CHECK_SIM_STATE;

	nRet = telephony_sim_get_subscriber_number(g_pstTelephonySIMHandle, &pszGetValue);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_sim_get_subscriber_number", TelephonyGetError(nRet));
	CHECK_VALUE_STRING(pszGetValue, "telephony_sim_get_subscriber_number");
	FREE_MEMORY(pszGetValue);
	return 0;
}


//& type: auto
//& purpose: check if current SIM card is different from previous SIM card or not
/**
* @testcase 			ITc_telephony_sim_is_changed_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			to check if current SIM card is different from previous SIM card or not
* @scenario				check if current SIM card is different from previous SIM card or not
* @apicovered			telephony_sim_is_changed
* @passcase				if telephony_sim_is_changed returns success
* @failcase				if telephony_sim_is_changed returns failure
* @precondition			working SIM card must be present in device, network service state of SIM must be TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE and SIM state must be TELEPHONY_SIM_STATE_AVAILABLE.
* @postcondition		NA
*/
int ITc_telephony_sim_is_changed_p(void)
{
	START_TEST;

	bool bIsChanged = false;
	int nRet = 0;
	CHECK_SIM_STATE;

	// Target API
	nRet = telephony_sim_is_changed(g_pstTelephonySIMHandle, &bIsChanged);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_sim_is_changed", TelephonyGetError(nRet));
#if DEBUG
	FPRINTF("[Line : %d][%s] Network type state is = %s\\n", __LINE__, API_NAMESPACE, bIsChanged == true ? "Changed" : "Not Changed");
#endif
	return 0;
}

//& type: auto
//& purpose: get the state of SIM.
/**
* @testcase 			ITc_telephony_sim_get_state_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			to get the state of SIM.
* @scenario				get the state of SIM.
* @apicovered			CHECK_SIM_STATE
* @passcase				if telephony_sim_get_state returns success
* @failcase				if telephony_sim_get_state returns failure
* @precondition			working SIM card must be present in device, network service state of SIM must be TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE and SIM state must be TELEPHONY_SIM_STATE_AVAILABLE.
* @postcondition		NA
*/
int ITc_telephony_sim_get_state_p(void)
{
	START_TEST;

	int nRet = 0;
	CHECK_SIM_STATE;
	return 0;
}

//& type: auto
//& purpose: get the list of application on UICC.
/**
* @testcase 			ITc_telephony_sim_get_application_list_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			Gets the list of application on UICC.
* @scenario				Gets the list of application on UICC.
* @apicovered			telephony_sim_get_application_list
* @passcase				if telephony_sim_get_application_list returns 0 on success
* @failcase				if telephony_sim_get_application_list returns negative error value
* @precondition			working SIM card must be present in device
* @postcondition		NA
*/
int ITc_telephony_sim_get_application_list_p(void)
{
	START_TEST;

	unsigned int app_list  = 0;
	int nRet = telephony_sim_get_application_list(g_pstTelephonySIMHandle,&app_list);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_sim_get_application_list", TelephonyGetError(nRet));
	CHECK_VALUE_INT(app_list, "telephony_sim_get_application_list");
	return 0;
}

//& type: auto
//& purpose: get subscriber ID encoded.
/**
* @testcase 			ITc_telephony_sim_get_subscriber_id_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			Gets subscriber ID encoded.
* @scenario				Gets subscriber ID encoded.
* @apicovered			telephony_sim_get_subscriber_id
* @passcase				if telephony_sim_get_subscriber_id returns 0 on success
* @failcase				if telephony_sim_get_subscriber_id returns negative error value
* @precondition			working SIM card must be present in device
* @postcondition		NA
*/
int ITc_telephony_sim_get_subscriber_id_p(void)
{
	START_TEST;

	char *subscriber_id = NULL;
	int nRet = telephony_sim_get_subscriber_id(g_pstTelephonySIMHandle, &subscriber_id);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_sim_get_subscriber_id", TelephonyGetError(nRet));
	CHECK_VALUE_STRING(subscriber_id, "telephony_sim_get_subscriber_id");
	return 0;
}

//& type: auto
//& purpose: Gets Group Identifier Level 1(GID1) embedded in the SIM card.
/**
* @testcase 			ITc_telephony_sim_get_group_id1_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			Gets Group Identifier Level 1(GID1) embedded in the SIM card
* @scenario				Gets Group Identifier Level 1(GID1) embedded in the SIM card
* @apicovered			telephony_sim_get_group_id1
* @passcase				if telephony_sim_get_group_id1 returns 0 on success
* @failcase				if telephony_sim_get_group_id1 returns negative error value
* @precondition			working SIM card must be present in device and SIM state must be TELEPHONY_SIM_STATE_AVAILABLE.
* @postcondition		NA
*/
int ITc_telephony_sim_get_group_id1_p(void)
{
	START_TEST;
	
	int nRet = 0;
	CHECK_SIM_STATE;
	
	char *pszGId1 = NULL;
	
	//Target API
	nRet = telephony_sim_get_group_id1(g_pstTelephonySIMHandle,&pszGId1);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_sim_get_group_id1", TelephonyGetError(nRet));
	
	FREE_MEMORY(pszGId1);
			
	return 0;
}

//& type: auto
//& purpose: Gets the call fowarding indicator state of the SIM.
/**
* @testcase 			ITc_telephony_sim_get_call_forwarding_indicator_state_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			Gets the call fowarding indicator state of the SIM.
* @scenario				Gets the call fowarding indicator state of the SIM.
* @apicovered			telephony_sim_get_call_forwarding_indicator_state
* @passcase				if telephony_sim_get_call_forwarding_indicator_state returns 0 on success
* @failcase				if telephony_sim_get_call_forwarding_indicator_state returns negative error value
* @precondition			working SIM card must be present in device and SIM state must be TELEPHONY_SIM_STATE_AVAILABLE.
* @postcondition		NA
*/
int ITc_telephony_sim_get_call_forwarding_indicator_state_p(void)
{
	START_TEST;
	
	bool bIndState = false;
	int nRet = 0;
	CHECK_SIM_STATE;
	
	//Target API
	nRet = telephony_sim_get_call_forwarding_indicator_state(g_pstTelephonySIMHandle,&bIndState);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_sim_get_call_forwarding_indicator_state", TelephonyGetError(nRet));
	
	//The value of bIndState indicates whether incoming call will be forwarded or not (true: forwarded, false: not forwarded)
	FPRINTF("[Line : %d][%s] Network type state is = %s\\n", __LINE__, API_NAMESPACE, bIndState == true ? "forwarded" : "Not forwarded");
	
	return 0;
}

//& type: auto
//& purpose: Gets the lock state of the SIM.
/**
* @testcase 			ITc_telephony_sim_get_lock_state_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 					auto
* @since_tizen 			3.0
* @description			Gets the lock state of the SIM
* @scenario				Gets the lock state of the SIM
* @apicovered			telephony_sim_get_lock_state
* @passcase				if telephony_sim_get_lock_state returns 0 on success
* @failcase					if telephony_sim_get_lock_state returns negative error value
* @precondition			working SIM card must be present in device and SIM state must be TELEPHONY_SIM_STATE_LOCKED.
* @postcondition		NA
*/
int ITc_telephony_sim_get_lock_state_p(void)
{
	START_TEST;
	telephony_sim_state_e eSimState = -1;
	telephony_sim_lock_state_e eSimLockState = -1 ;
	int nRet = 0;
	CHECK_SIM_STATE;
	//@pre The SIM state must be #TELEPHONY_SIM_STATE_LOCKED.
	if ( eSimState != TELEPHONY_SIM_STATE_LOCKED )
	{
		FPRINTF("[Line : %d][%s] telephony_sim_get_state returned state = %s \\n", __LINE__, API_NAMESPACE, TelephonyGetSimState(eSimState));\
		return 0;
	}
	nRet =  telephony_sim_get_lock_state(g_pstTelephonySIMHandle, &eSimLockState);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_sim_get_lock_state", TelephonyGetError(nRet));
	
	// when locked sim insert in phone, eSimLockState will not be TELEPHONY_SIM_LOCK_STATE_UNKNOWN
	if(eSimLockState == TELEPHONY_SIM_LOCK_STATE_UNKNOWN)
	{
		FPRINTF("[Line : %d][%s] eSimLockState is wrong. eSimLockState = %s\\n", __LINE__, API_NAMESPACE, TelephonyGetSimLockState(eSimLockState));
		return 1;
	}
	
	return 0;
}
