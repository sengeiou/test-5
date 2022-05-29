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
* @function 		ITs_telephony_call_startup
* @description	 	Called before each test, Acquire the list of available handles to use telephony API.
* @parameter		NA
* @return 			NA
*/
void ITs_telephony_call_startup(void)
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
* @function 		ITs_telephony_call_cleanup
* @description	 	Called after each test, Deinitialize telephony handle list.
* @parameter		NA
* @return 			NA
*/
void ITs_telephony_call_cleanup(void)
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
//& purpose: get the current value for the preferred voice call subscription.
/**
* @testcase 			ITc_telephony_call_get_preferred_voice_subscription_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			Gets the current value for the preferred voice call subscription.
* @scenario				Gets the current value for the preferred voice call subscription.
* @apicovered			telephony_call_get_preferred_voice_subscription
* @passcase				if telephony_call_get_preferred_voice_subscription returns 0 on success
* @failcase				if telephony_call_get_preferred_voice_subscription returns negative error value
* @precondition			working SIM card must be present in device
* @postcondition		NA
*/
int ITc_telephony_call_get_preferred_voice_subscription_p(void)
{
	START_TEST;

	telephony_call_preferred_voice_subs_e call_sub = 0;
	int nRet = telephony_call_get_preferred_voice_subscription(g_pstTelephonySIMHandle , &call_sub);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_call_get_preferred_voice_subscription", TelephonyGetError(nRet));

	if ( call_sub == TELEPHONY_CALL_PREFERRED_VOICE_SUBS_UNKNOWN)
	{
		FPRINTF("[Line : %d][%s] TELEPHONY_CALL_PREFERRED_VOICE_SUBS_UNKNOWN telephony_call_get_preferred_voice_subscription failed,\\n", __LINE__, API_NAMESPACE);
		return 1;		
	}
	return 0;
}

//& type: auto
//& purpose: Get the list of the current call and release the list
/**
* @testcase 			ITc_telephony_call_get_release_call_list_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			Gets the list of the current call and releases the list
* @scenario				Get the list of the current call
*						Release the list allocated from #telephony_call_get_call_list()
* @apicovered			telephony_call_get_call_list
* @passcase				if telephony_call_get_call_list returns 0 on success
* @failcase				if telephony_call_get_call_list returns negative error value
* @precondition			working SIM card must be present in device
* @postcondition		NA
*/
int ITc_telephony_call_get_release_call_list_p(void)
{
	START_TEST;

	unsigned int count = 0;
	telephony_call_h *call_list = NULL;

	int nRet = telephony_call_get_call_list(g_pstTelephonySIMHandle, &count, &call_list);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_call_get_call_list", TelephonyGetError(nRet));
	
	nRet = telephony_call_release_call_list(count, &call_list);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_call_release_call_list", TelephonyGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: get the call handle ID.
/**
* @testcase 			ITc_telephony_call_get_handle_id_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			Gets the call handle ID
* @scenario				Gets the call handle ID
* @apicovered			telephony_call_get_handle_id
* @passcase				if telephony_call_get_handle_id returns 0 on success
* @failcase				if telephony_call_get_handle_id returns negative error value
* @precondition			The call handle should be obtained from #telephony_call_get_call_list()
* @postcondition		The call list should be released by using #telephony_call_release_call_list()
*/
int ITc_telephony_call_get_handle_id_p(void)
{
	START_TEST;

	unsigned int count = 0;
	telephony_call_h *call_list = NULL;
	unsigned int handle_id = 0;
	int i = 0;
	int nRet = telephony_call_get_call_list(g_pstTelephonySIMHandle, &count, &call_list);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_call_get_call_list", TelephonyGetError(nRet));
	
	for ( i = 0; i < count; i++ )
	{
		CHECK_HANDLE(call_list[i], "telephony_call_get_handle_id");
		//Target API
		nRet = telephony_call_get_handle_id(call_list[i], &handle_id);
		PRINT_RESULT_CLEANUP(TELEPHONY_ERROR_NONE, nRet, "telephony_call_get_handle_id", TelephonyGetError(nRet),telephony_call_release_call_list(count, &call_list));
	}

	nRet = telephony_call_release_call_list(count, &call_list);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_call_release_call_list", TelephonyGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: get the call number.
/**
* @testcase 			ITc_telephony_call_get_number_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			Gets the call number.
* @scenario				Gets the call number.
* @apicovered			telephony_call_get_number
* @passcase				if telephony_call_get_number returns 0 on success
* @failcase				if telephony_call_get_number returns negative error value
* @precondition			The call handle should be obtained from #telephony_call_get_call_list()
* @postcondition		The call list should be released by using #telephony_call_release_call_list()
*/
int ITc_telephony_call_get_number_p(void)
{
	START_TEST;

	char *number = NULL;
	unsigned int count = 0;
	telephony_call_h *call_list = NULL;
	int i = 0;
	int nRet = telephony_call_get_call_list(g_pstTelephonySIMHandle, &count, &call_list);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_call_get_call_list", TelephonyGetError(nRet));
	
	for ( i = 0; i < count; i++ )
	{
		CHECK_HANDLE(call_list[i], "telephony_call_get_number");
		//Target API
		nRet = telephony_call_get_number(call_list[i], &number);
		FREE_MEMORY(number);
		PRINT_RESULT_CLEANUP(TELEPHONY_ERROR_NONE, nRet, "telephony_call_get_number", TelephonyGetError(nRet),telephony_call_release_call_list(count, &call_list));
	}

	nRet = telephony_call_release_call_list(count, &call_list);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_call_release_call_list", TelephonyGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: get the call type.
/**
* @testcase 			ITc_telephony_call_get_type_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			Gets the call type.
* @scenario				Gets the call type.
* @apicovered			telephony_call_get_call_list, telephony_call_get_type, telephony_call_release_call_list
* @passcase				if telephony_call_get_type returns 0 on success
* @failcase				if telephony_call_get_type returns negative error value
* @precondition			The call handle should be obtained from #telephony_call_get_call_list()
* @postcondition		The call list should be released by using #telephony_call_release_call_list()
*/
int ITc_telephony_call_get_type_p(void)
{
	START_TEST;

	telephony_call_type_e type = -1;
	unsigned int count = 0;
	telephony_call_h *call_list = NULL;
	int i = 0;
	int nRet = telephony_call_get_call_list(g_pstTelephonySIMHandle, &count, &call_list);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_call_get_call_list", TelephonyGetError(nRet));
	
	for ( i = 0; i < count; i++ )
	{
		CHECK_HANDLE(call_list[i], "telephony_call_get_type");
		//Target API
		nRet = telephony_call_get_type(call_list[i], &type);
		PRINT_RESULT_CLEANUP(TELEPHONY_ERROR_NONE, nRet, "telephony_call_get_type", TelephonyGetError(nRet),telephony_call_release_call_list(count, &call_list));
		if((type < TELEPHONY_CALL_TYPE_VOICE) || (type > TELEPHONY_CALL_TYPE_E911))
		{
			FPRINTF("[Line : %d][%s] returned type is invalid\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	nRet = telephony_call_release_call_list(count, &call_list);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_call_release_call_list", TelephonyGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: get the call status.
/**
* @testcase 			ITc_telephony_call_get_status_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			Gets the call status.
* @scenario				Gets the call status.
* @apicovered			telephony_call_get_call_list, telephony_call_get_status, telephony_call_release_call_list
* @passcase				if telephony_call_get_status returns 0 on success
* @failcase				if telephony_call_get_status returns negative error value
* @precondition			The call handle should be obtained from #telephony_call_get_call_list()
* @postcondition		The call list should be released by using #telephony_call_release_call_list()
*/
int ITc_telephony_call_get_status_p(void)
{
	START_TEST;

	telephony_call_status_e status = -1;
	unsigned int count = 0;
	telephony_call_h *call_list = NULL;
	int i = 0;
	int nRet = telephony_call_get_call_list(g_pstTelephonySIMHandle, &count, &call_list);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_call_get_call_list", TelephonyGetError(nRet));
	
	for ( i = 0; i < count; i++ )
	{
		CHECK_HANDLE(call_list[i], "telephony_call_get_status");
		//Target API
		nRet = telephony_call_get_status(call_list[i], &status);
		PRINT_RESULT_CLEANUP(TELEPHONY_ERROR_NONE, nRet, "telephony_call_get_status", TelephonyGetError(nRet),telephony_call_release_call_list(count, &call_list));
		if((status < TELEPHONY_CALL_STATUS_IDLE) || (status > TELEPHONY_CALL_STATUS_INCOMING
))
		{
			FPRINTF("[Line : %d][%s] status is invalid\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	nRet = telephony_call_release_call_list(count, &call_list);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_call_release_call_list", TelephonyGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: get the call direction.
/**
* @testcase 			ITc_telephony_call_get_direction_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			Gets the call direction.
* @scenario				Gets the call direction.
* @apicovered			telephony_call_get_call_list, telephony_call_get_direction, telephony_call_release_call_list
* @passcase				if telephony_call_get_direction returns 0 on success
* @failcase				if telephony_call_get_direction returns negative error value
* @precondition			The call handle should be obtained from #telephony_call_get_call_list()
* @postcondition		The call list should be released by using #telephony_call_release_call_list()
*/
int ITc_telephony_call_get_direction_p(void)
{
	START_TEST;

	telephony_call_direction_e direction = -1;
	unsigned int count = 0;
	telephony_call_h *call_list = NULL;
	int i = 0;
	int nRet = telephony_call_get_call_list(g_pstTelephonySIMHandle, &count, &call_list);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_call_get_call_list", TelephonyGetError(nRet));
	
	for ( i = 0; i < count; i++ )
	{
		CHECK_HANDLE(call_list[i], "telephony_call_get_direction");
		//Target API
		nRet = telephony_call_get_direction(call_list[i], &direction);
		PRINT_RESULT_CLEANUP(TELEPHONY_ERROR_NONE, nRet, "telephony_call_get_direction", TelephonyGetError(nRet),telephony_call_release_call_list(count, &call_list));
		if((direction < TELEPHONY_CALL_DIRECTION_MO) || (direction > TELEPHONY_CALL_DIRECTION_MT))
		{
			FPRINTF("[Line : %d][%s] direction is invalid\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	nRet = telephony_call_release_call_list(count, &call_list);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_call_release_call_list", TelephonyGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: get the conference status.
/**
* @testcase 			ITc_telephony_call_get_conference_status_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			Gets the conference status.
* @scenario				Gets the conference status.
* @apicovered			telephony_call_get_conference_status
* @passcase				if telephony_call_get_conference_status returns 0 on success
* @failcase				if telephony_call_get_conference_status returns negative error value
* @precondition			The call handle should be obtained from #telephony_call_get_call_list()
* @postcondition		The call list should be released by using #telephony_call_release_call_list()
*/
int ITc_telephony_call_get_conference_status_p(void)
{
	START_TEST;

	bool conference_status;
	unsigned int count = 0;
	telephony_call_h *call_list = NULL;
	int i = 0;
	int nRet = telephony_call_get_call_list(g_pstTelephonySIMHandle, &count, &call_list);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_call_get_call_list", TelephonyGetError(nRet));
	
	for ( i = 0; i < count; i++ )
	{
		CHECK_HANDLE(call_list[i], "telephony_call_get_conference_status");
		//Target API
		nRet = telephony_call_get_conference_status(call_list[i], &conference_status);
		PRINT_RESULT_CLEANUP(TELEPHONY_ERROR_NONE, nRet, "telephony_call_get_conference_status", TelephonyGetError(nRet),telephony_call_release_call_list(count, &call_list));
	}

	nRet = telephony_call_release_call_list(count, &call_list);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_call_release_call_list", TelephonyGetError(nRet));

	return 0;
}
