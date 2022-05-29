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
extern telephony_handle_list_s g_stTelephonyHandleList ;
extern telephony_h g_pstTelephonySIMHandle;
extern bool g_bTelephonyIssupportedFeature ;
extern bool g_bTelephonySkipExecutionWithPass ;
extern bool g_bTelephonySkipExecutionWithFail ;

/**
* @function 		ITs_telephony_startup
* @description	 	Called before each test, Acquire the list of available handles to use telephony API.
* @parameter		NA
* @return 			NA
*/
void ITs_telephony_network_startup(void)
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
void ITs_telephony_network_cleanup(void)
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
//& purpose: get the cell ID
/**
* @testcase 			ITc_telephony_network_get_cell_id_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			to get the cell ID
* @scenario				get the cell ID
* @apicovered			telephony_network_get_cell_id
* @passcase				if telephony_network_get_cell_id returns success and cell id returned is not zero
* @failcase				if telephony_network_get_cell_id returns failure or cell id returned is zero
* @precondition			working SIM card must be present in device, network service state of SIM must be TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE.
* @postcondition		NA
*/
int ITc_telephony_network_get_cell_id_p(void)
{
	START_TEST;

	int nGetValue = -1;

	// Target API
	int nRet = telephony_network_get_cell_id(g_pstTelephonySIMHandle, &nGetValue);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_cell_id", TelephonyGetError(nRet));
	if(nGetValue < 0)
	{
		FPRINTF("[Line : %d][%s] telephony_network_get_cell_id failed, output value is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: get the LAC (Location Area Code) of current network
/**
* @testcase 			ITc_telephony_network_get_lac_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			to get the LAC (Location Area Code) of current network
* @scenario				get the LAC (Location Area Code) of current network
* @apicovered			telephony_network_get_lac
* @passcase				if telephony_network_get_lac returns success and lac returned is not zero
* @failcase				if telephony_network_get_lac returns failure or lac returned is zero
* @precondition			working SIM card must be present in device, network service state of SIM must be TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE.
* @postcondition		NA
*/
int ITc_telephony_network_get_lac_p(void)
{
	START_TEST;

	int nGetValue = -1;
	telephony_network_type_e eNetworkInfoType;

	// Check current network is in GSM / WCDMA network
	int nRet = telephony_network_get_type(g_pstTelephonySIMHandle, &eNetworkInfoType);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_type", TelephonyGetError(nRet));
	if (eNetworkInfoType >= TELEPHONY_NETWORK_TYPE_GSM
			&& eNetworkInfoType <= TELEPHONY_NETWORK_TYPE_HSDPA) {
		// Target API
		nRet = telephony_network_get_lac(g_pstTelephonySIMHandle, &nGetValue);
		PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_lac", TelephonyGetError(nRet));
		if(nGetValue < 0)
		{
			FPRINTF("[Line : %d][%s] telephony_network_get_lac failed, output value is invalid\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	} else {
		FPRINTF("[Line : %d][%s] Current network is not in GSM / WCDMA network. So Leaving test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	return 0;
}

//& type: auto
//& purpose: get the RSSI (Received Signal Strength Indicator)
/**
* @testcase 			ITc_telephony_network_get_rssi_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			to get the RSSI (Received Signal Strength Indicator)
* @scenario				get the RSSI (Received Signal Strength Indicator)
* @apicovered			telephony_network_get_rssi
* @passcase				if telephony_network_get_rssi returns success and lac returned is not zero
* @failcase				if telephony_network_get_rssi returns failure or lac returned is zero
* @precondition			working SIM card must be present in device, network service state of SIM must be TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE.
* @postcondition		NA
*/
int ITc_telephony_network_get_rssi_p(void)
{
	START_TEST;

	telephony_network_rssi_e eNetworkRSSI = -1;
	int nRet = telephony_network_get_rssi(g_pstTelephonySIMHandle, &eNetworkRSSI);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_rssi", TelephonyGetError(nRet));
	if((eNetworkRSSI < TELEPHONY_NETWORK_RSSI_0) || (eNetworkRSSI > TELEPHONY_NETWORK_RSSI_6))
	{
		FPRINTF("[Line : %d][%s] RSSI returned value is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] RSSI value returned = %s\\n", __LINE__, API_NAMESPACE, TelephonyGetRSSIValue(eNetworkRSSI));
#endif

	return 0;
}

//& type: auto
//& purpose: get the roaming status
/**
* @testcase 			ITc_telephony_network_get_roaming_status_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			to get the roaming status
* @scenario				get the roaming status
* @apicovered			telephony_network_get_roaming_status
* @passcase				if telephony_network_get_roaming_status returns success
* @failcase				if telephony_network_get_roaming_status returns failure
* @precondition			working SIM card must be present in device, network service state of SIM must be TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE.
* @postcondition		NA
*/
int ITc_telephony_network_get_roaming_status_p(void)
{
	START_TEST;

	bool bIsRoaming = false;
	int nRet = telephony_network_get_roaming_status(g_pstTelephonySIMHandle, &bIsRoaming);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_roaming_status", TelephonyGetError(nRet));
	if(!((bIsRoaming == false) || (bIsRoaming == true)))
	{
		FPRINTF("[Line : %d][%s] telephony_network_get_roaming_status failed, Output value is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] Network type state is = %s\\n", __LINE__, API_NAMESPACE, bIsRoaming == true ? "Roaming" : "Not Roaming");
#endif

	return 0;
}

//& type: auto
//& purpose: get the MCC (Mobile Country Code) of the current network
/**
* @testcase 			ITc_telephony_network_get_mcc_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			to get the MCC (Mobile Country Code) of the current network
* @scenario				get the MCC (Mobile Country Code) of the current network
* @apicovered			telephony_network_get_mcc
* @passcase				if telephony_network_get_mcc returns success and mcc returned is not null
* @failcase				if telephony_network_get_mcc returns failure or mcc returned is null
* @precondition			working SIM card must be present in device, network service state of SIM must be TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE.
* @postcondition		NA
*/
int ITc_telephony_network_get_mcc_p(void)
{
	START_TEST;

	char *pszGetValue = NULL;

	// Target API
	int nRet = telephony_network_get_mcc(g_pstTelephonySIMHandle, &pszGetValue);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_mcc", TelephonyGetError(nRet));
	CHECK_VALUE_STRING(pszGetValue, "telephony_network_get_mcc");

	return 0;
}

//& type: auto
//& purpose: get the MNC (Mobile Network Code) of the current network
/**
* @testcase 			ITc_telephony_network_get_mnc_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			to get the MNC (Mobile Network Code) of the current network
* @scenario				get the MNC (Mobile Network Code) of the current network
* @apicovered			telephony_network_get_mnc
* @passcase				if telephony_network_get_mnc returns success and mnc returned is not null
* @failcase				if telephony_network_get_mnc returns failure or mnc returned is null
* @precondition			working SIM card must be present in device, network service state of SIM must be TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE.
* @postcondition		NA
*/
int ITc_telephony_network_get_mnc_p(void)
{
	START_TEST;

	char *pszGetValue = NULL;

	// Target API
	int nRet = telephony_network_get_mnc(g_pstTelephonySIMHandle, &pszGetValue);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_mnc", TelephonyGetError(nRet));
	CHECK_VALUE_STRING(pszGetValue, "telephony_network_get_mnc");
	return 0;
}

//& type: auto
//& purpose: get the current registered network
/**
* @testcase 			ITc_telephony_network_get_network_name_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			to get the current registered network
* @scenario				get the current registered network
* @apicovered			telephony_network_get_network_name
* @passcase				if telephony_network_get_network_name returns success and current registered network name returned is not null
* @failcase				if telephony_network_get_network_name returns failure or current registered network name returned is null
* @precondition			working SIM card must be present in device, network service state of SIM must be TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE.
* @postcondition		NA
*/
int ITc_telephony_network_get_network_name_p(void)
{
	START_TEST;

	char *pszGetValue = NULL;
	int nRet = telephony_network_get_network_name(g_pstTelephonySIMHandle, &pszGetValue);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_network_name", TelephonyGetError(nRet));
	CHECK_VALUE_STRING(pszGetValue, "telephony_network_get_network_name");
	return 0;
}

//& type: auto
//& purpose: get the service type of registered network
/**
* @testcase 			ITc_telephony_network_get_type_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			to get the service type of registered network
* @scenario				get the service type of registered network
* @apicovered			telephony_network_get_type
* @passcase				if telephony_network_get_type returns success
* @failcase				if telephony_network_get_type returns failure
* @precondition			working SIM card must be present in device, network service state of SIM must be TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE.
* @postcondition		NA
*/
int ITc_telephony_network_get_type_p(void)
{
	START_TEST;

	telephony_network_type_e eNetworkInfoType;

	// Target API
	int nRet = telephony_network_get_type(g_pstTelephonySIMHandle, &eNetworkInfoType);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_type", TelephonyGetError(nRet));
#if DEBUG
	FPRINTF("[Line : %d][%s] service type of registered network returned = %s\\n", __LINE__, API_NAMESPACE, TelephonyGetNetworkType(eNetworkInfoType));
#endif
	if ( eNetworkInfoType == TELEPHONY_NETWORK_TYPE_UNKNOWN )
	{
		FPRINTF("[Line : %d][%s] TELEPHONY_NETWORK_TYPE_UNKNOWN telephony_network_get_type failed,\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: get the current network state of the telephony service.
/**
* @testcase 			ITc_telephony_network_get_service_state_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			to get the current network state of the telephony service
* @scenario				get the current network state of the telephony service
* @apicovered			telephony_network_get_service_state
* @passcase				if telephony_network_get_service_state returns success
* @failcase				if telephony_network_get_service_state returns failure
* @precondition			working SIM card must be present in device, network service state of SIM must be TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE.
* @postcondition		NA
*/
int ITc_telephony_network_get_service_state_p(void)
{
	START_TEST;

	telephony_network_service_state_e eNetworkServiceState;
	int nRet = telephony_network_get_service_state(g_pstTelephonySIMHandle, &eNetworkServiceState);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_service_state", TelephonyGetError(nRet));
	if ( eNetworkServiceState != TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE )
	{
		FPRINTF("[Line : %d][%s] telephony_network_get_service_state returned state = %s \\n", __LINE__, API_NAMESPACE, TelephonyGetServiceState(eNetworkServiceState));
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: get the packet service type of the current registered network.
/**
* @testcase 			ITc_telephony_network_get_ps_type_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			Gets the packet service type of the current registered network.
* @scenario				Gets the packet service type of the current registered network.
* @apicovered			telephony_network_get_ps_type
* @passcase				if telephony_network_get_ps_type returns 0 on success
* @failcase				if telephony_network_get_ps_type returns negative error value
* @precondition			working SIM card must be present in device
* @postcondition		NA
*/
int ITc_telephony_network_get_ps_type_p(void)
{
	START_TEST;

	telephony_network_ps_type_e ps_type = 0;
	telephony_network_service_state_e eNetworkServiceState = 0;
	
	int nRet = telephony_network_get_service_state(g_pstTelephonySIMHandle, &eNetworkServiceState);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_service_state", TelephonyGetError(nRet));
	if ( eNetworkServiceState != TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE )
	{
		FPRINTF("[Line : %d][%s] telephony_network_get_service_state returned state = %s \\n", __LINE__, API_NAMESPACE, TelephonyGetServiceState(eNetworkServiceState));
		return 1;
	}
	
	nRet = telephony_network_get_ps_type(g_pstTelephonySIMHandle, &ps_type);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_ps_type", TelephonyGetError(nRet));
	if(!(ps_type == TELEPHONY_NETWORK_PS_TYPE_UNKNOWN || ps_type == TELEPHONY_NETWORK_PS_TYPE_HSDPA || ps_type == TELEPHONY_NETWORK_PS_TYPE_HSUPA ||
	ps_type == TELEPHONY_NETWORK_PS_TYPE_HSPA|| ps_type == TELEPHONY_NETWORK_PS_TYPE_HSPAP))
	{
		FPRINTF("[Line : %d][%s] telephony_network_get_ps_type failed, output value is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose: get the network name option of the current registered network.
/**
* @testcase 			ITc_telephony_network_get_network_name_option_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			Gets the network name option of the current registered network.
* @scenario				Gets the network name option of the current registered network.
* @apicovered			telephony_network_get_network_name_option
* @passcase				if telephony_network_get_network_name_option returns 0 on success
* @failcase				if telephony_network_get_network_name_option returns negative error value
* @precondition			working SIM card must be present in device
* @postcondition		NA
*/
int ITc_telephony_network_get_network_name_option_p(void)
{
	START_TEST;

	telephony_network_name_option_e network_name_option = 0;
	int nRet = telephony_network_get_network_name_option(g_pstTelephonySIMHandle, &network_name_option);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_network_name_option", TelephonyGetError(nRet));
	if ( network_name_option == TELEPHONY_NETWORK_NAME_OPTION_UNKNOWN )
	{
		FPRINTF("[Line : %d][%s] TELEPHONY_NETWORK_NAME_OPTION_UNKNOWN telephony_network_get_network_name_option failed,\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose: get the current default subscription for data service (Packet Switched).
/**
* @testcase 			ITc_telephony_network_get_default_data_subscription_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			Gets the current default subscription for data service (Packet Switched).
* @scenario				Gets the current default subscription for data service (Packet Switched).
* @apicovered			telephony_network_get_default_data_subscription
* @passcase				if telephony_network_get_default_data_subscription returns 0 on success
* @failcase				if telephony_network_get_default_data_subscription returns negative error value
* @precondition			working SIM card must be present in device
* @postcondition		NA
*/
int ITc_telephony_network_get_default_data_subscription_p(void)
{
	START_TEST;

	telephony_network_default_data_subs_e default_sub = 0;
	int nRet = telephony_network_get_default_data_subscription(g_pstTelephonySIMHandle, &default_sub);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_default_data_subscription", TelephonyGetError(nRet));
	if ( default_sub == TELEPHONY_NETWORK_DEFAULT_DATA_SUBS_UNKNOWN )
	{
		FPRINTF("[Line : %d][%s] TELEPHONY_NETWORK_DEFAULT_DATA_SUBS_UNKNOWN telephony_network_get_default_data_subscription failed,\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose: get the current default subscription for voice service (Circuit Switched).
/**
* @testcase 			ITc_telephony_network_get_default_subscription_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			Gets the current default subscription for voice service (Circuit Switched).
* @scenario				Gets the current default subscription for voice service (Circuit Switched).
* @apicovered			telephony_network_get_default_subscription
* @passcase				if telephony_network_get_default_subscription returns 0 on success
* @failcase				if telephony_network_get_default_subscription returns negative error value
* @precondition			working SIM card must be present in device
* @postcondition		NA
*/
int ITc_telephony_network_get_default_subscription_p(void)
{
	START_TEST;

	telephony_network_default_subs_e default_sub = -2;
	int nRet = telephony_network_get_default_subscription(g_pstTelephonySIMHandle, &default_sub);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_default_subscription", TelephonyGetError(nRet));
	if ( default_sub != TELEPHONY_NETWORK_DEFAULT_SUBS_UNKNOWN
			&& default_sub != TELEPHONY_NETWORK_DEFAULT_SUBS_SIM1
			&& default_sub != TELEPHONY_NETWORK_DEFAULT_SUBS_SIM2 )
	{
		FPRINTF("[Line : %d][%s] default_sub value not set!!! telephony_network_get_default_subscription failed,\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose: Gets the network selection mode.
/**
* @testcase 			ITc_telephony_network_get_selection_mode_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			Gets the network selection mode.
* @scenario				Gets the network selection mode.
* @apicovered			telephony_network_get_selection_mode
* @passcase				if telephony_network_get_selection_mode returns 0 on success
* @failcase				if telephony_network_get_selection_mode returns negative error value
* @precondition			working SIM card must be present in device
* @postcondition		NA
*/
int ITc_telephony_network_get_selection_mode_p(void)
{
	START_TEST;
	
	telephony_network_selection_mode_e mode = -1;
	
	//Target API
	int nRet = telephony_network_get_selection_mode(g_pstTelephonySIMHandle, &mode);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_selection_mode", TelephonyGetError(nRet));
	FPRINTF("[Line : %d][%s] telephony_network_get_selection_mode succeed, returned %s\\n", __LINE__, API_NAMESPACE, TelephonyGetNetworkSelMode(mode));
		
	return 0;
}

//& type: auto
//& purpose: Gets the TAC (Tracking Area Code) of the current location.
/**
* @testcase 			ITc_telephony_network_get_tac_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			Gets the TAC (Tracking Area Code) of the current location.
* @scenario				Gets the TAC (Tracking Area Code) of the current location.
* @apicovered			telephony_network_get_tac
* @passcase				if telephony_network_get_tac returns 0 on success
* @failcase				if telephony_network_get_tac returns negative error value
* @precondition			working SIM card must be present in device
* @postcondition		NA
*/
int ITc_telephony_network_get_tac_p(void)
{
	START_TEST;
	
	int nTac = -1;
	
	telephony_network_type_e eNetworkInfoType;

	//LTE network support check
	int nRet = telephony_network_get_type(g_pstTelephonySIMHandle, &eNetworkInfoType);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_type", TelephonyGetError(nRet));
	if ( eNetworkInfoType != TELEPHONY_NETWORK_TYPE_LTE )
	{
		FPRINTF("[Line : %d][%s] LTE network type not supported. So Leaving test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	
	//Target API
	nRet = telephony_network_get_tac(g_pstTelephonySIMHandle, &nTac);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_tac", TelephonyGetError(nRet));
	
	if(nTac < 0)
	{
		FPRINTF("[Line : %d][%s] telephony_network_get_tac failed, tac value returned %d\\n", __LINE__, API_NAMESPACE, nTac);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets the system ID of the current location.
/**
* @testcase 			ITc_telephony_network_get_system_id_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			Gets the system ID of the current location.
* @scenario				Gets the system ID of the current location.
* @apicovered			telephony_network_get_system_id
* @passcase				if telephony_network_get_system_id returns 0 on success
* @failcase				if telephony_network_get_system_id returns negative error value
* @precondition			working SIM card must be present in device
* @postcondition		NA
*/
int ITc_telephony_network_get_system_id_p(void)
{
	START_TEST;

	int nSid = -1;
	telephony_network_type_e eNetworkInfoType;
	
		//CDMA network support check
	int nRet = telephony_network_get_type(g_pstTelephonySIMHandle, &eNetworkInfoType);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_type", TelephonyGetError(nRet));
	if ( eNetworkInfoType != TELEPHONY_NETWORK_TYPE_CDMA_1X )
	{
		FPRINTF("[Line : %d][%s] CDMA not supported,Leaving TestCase\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	//Target API
	nRet = telephony_network_get_system_id(g_pstTelephonySIMHandle, &nSid);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_system_id", TelephonyGetError(nRet));
	
	if(nSid < 0)
	{
		FPRINTF("[Line : %d][%s] telephony_network_get_system_id failed, returned %d\\n", __LINE__, API_NAMESPACE, nSid);
		return 1;
	}	

	return 0;
}

//& type: auto
//& purpose: Gets the network ID of the current location.
/**
* @testcase 			ITc_telephony_network_get_network_id_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			Gets the network ID of the current location.
* @scenario				Gets the network ID of the current location.
* @apicovered			telephony_network_get_network_id
* @passcase				if telephony_network_get_network_id returns 0 on success
* @failcase				if telephony_network_get_network_id returns negative error value
* @precondition			working SIM card must be present in device and network should be TELEPHONY_NETWORK_TYPE_CDMA_1X
* @postcondition		NA
*/
int ITc_telephony_network_get_network_id_p(void)
{
	START_TEST;

	int nNid = -1;
	telephony_network_type_e eNetworkInfoType;
	
	//CDMA network support check
	int nRet = telephony_network_get_type(g_pstTelephonySIMHandle, &eNetworkInfoType);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_type", TelephonyGetError(nRet));
	if ( eNetworkInfoType != TELEPHONY_NETWORK_TYPE_CDMA_1X )
	{
		FPRINTF("[Line : %d][%s] CDMA not supported,Leaving TestCase\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	//Target API
	nRet = telephony_network_get_network_id(g_pstTelephonySIMHandle, &nNid);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_network_id", TelephonyGetError(nRet));
	
	if(nNid < 0)
	{
		FPRINTF("[Line : %d][%s] telephony_network_get_network_id failed, returned %d\\n", __LINE__, API_NAMESPACE, nNid);
		return 1;
	}
	return 0;

}

//& type: auto
//& purpose: Gets the base station ID of the current location
/**
* @testcase 			ITc_telephony_network_get_base_station_id_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			Gets the base station ID of the current location
* @scenario				Gets the base station ID of the current location
* @apicovered			telephony_network_get_base_station_id
* @passcase				if telephony_network_get_base_station_id returns 0 on success
* @failcase				if telephony_network_get_base_station_id returns negative error value
* @precondition			working SIM card must be present in device and network should be TELEPHONY_NETWORK_TYPE_CDMA_1X
* @postcondition		NA
*/
int ITc_telephony_network_get_base_station_id_p(void)
{
	START_TEST;

	int nBaseId = -1;
	telephony_network_type_e eNetworkInfoType;
	
	//CDMA network support check
	int nRet = telephony_network_get_type(g_pstTelephonySIMHandle, &eNetworkInfoType);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_type", TelephonyGetError(nRet));
	if ( eNetworkInfoType != TELEPHONY_NETWORK_TYPE_CDMA_1X )
	{
		FPRINTF("[Line : %d][%s] CDMA not supported,Leaving TestCase\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	//Target API
	nRet = telephony_network_get_base_station_id(g_pstTelephonySIMHandle, &nBaseId);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_base_station_id", TelephonyGetError(nRet));
	
	if(nBaseId < 0)
	{
		FPRINTF("[Line : %d][%s] telephony_network_get_base_station_id failed, returned %d\\n", __LINE__, API_NAMESPACE, nBaseId);
		return 1;
	}
	return 0;

}

//& type: auto
//& purpose:Gets the base station latitude of the current location.
/**
* @testcase 			ITc_telephony_network_get_base_station_latitude_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			Gets the base station latitude of the current location.
* @scenario				Gets the base station latitude of the current location.
* @apicovered			telephony_network_get_base_station_latitude
* @passcase				if telephony_network_get_base_station_latitude returns 0 on success
* @failcase				if telephony_network_get_base_station_latitude returns negative error value
* @precondition			working SIM card must be present in device and network should be TELEPHONY_NETWORK_TYPE_CDMA_1X
* @postcondition		NA
*/
int ITc_telephony_network_get_base_station_latitude_p(void)
{
	START_TEST;

	int nBaseLat = -1;
	telephony_network_type_e eNetworkInfoType;
	
	//CDMA network support check
	int nRet = telephony_network_get_type(g_pstTelephonySIMHandle, &eNetworkInfoType);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_type", TelephonyGetError(nRet));
	if ( eNetworkInfoType != TELEPHONY_NETWORK_TYPE_CDMA_1X )
	{
		FPRINTF("[Line : %d][%s] CDMA not supported,Leaving TestCase\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	//Target API
	nRet = telephony_network_get_base_station_latitude(g_pstTelephonySIMHandle, &nBaseLat);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_base_station_latitude", TelephonyGetError(nRet));
	
	if(nBaseLat == 0x7FFFFFFF)
	{
		FPRINTF("[Line : %d][%s] telephony_network_get_base_station_latitude failed, returned %d\\n", __LINE__, API_NAMESPACE, nBaseLat);
		return 1;
	}
	return 0;

}

//& type: auto
//& purpose:Gets the base station longitude of the current location.
/**
* @testcase 			ITc_telephony_network_get_base_station_longitude_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			Gets the base station longitude of the current location.
* @scenario				Gets the base station longitude of the current location.
* @apicovered			telephony_network_get_base_station_longitude
* @passcase				if telephony_network_get_base_station_longitude returns 0 on success
* @failcase				if telephony_network_get_base_station_longitude returns negative error value
* @precondition			working SIM card must be present in device and network should be TELEPHONY_NETWORK_TYPE_CDMA_1X
* @postcondition		NA
*/
int ITc_telephony_network_get_base_station_longitude_p(void)
{
	START_TEST;

	int nBaseLong = -1;
	telephony_network_type_e eNetworkInfoType;
	
	//CDMA network support check
	int nRet = telephony_network_get_type(g_pstTelephonySIMHandle, &eNetworkInfoType);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_type", TelephonyGetError(nRet));
	if ( eNetworkInfoType != TELEPHONY_NETWORK_TYPE_CDMA_1X )
	{
		FPRINTF("[Line : %d][%s] CDMA not supported,Leaving TestCase\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	//Target API
	nRet = telephony_network_get_base_station_longitude(g_pstTelephonySIMHandle, &nBaseLong);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_base_station_longitude", TelephonyGetError(nRet));
	
	if(nBaseLong == 0x7FFFFFFF)
	{
		FPRINTF("[Line : %d][%s] telephony_network_get_base_station_longitude failed, returned %d\\n", __LINE__, API_NAMESPACE, nBaseLong);
		return 1;
	}
	return 0;

}

//& type: auto
//& purpose:Gets the received signal strength (dBm).
/**
* @testcase 			ITc_telephony_network_get_signal_strength_p
* @author            	SRID(ankit.j)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @since_tizen 			4.0
* @description			Gets the received signal strength (dBm).
* @scenario				Gets the received signal strength (dBm).
* @apicovered			telephony_network_get_signal_strength
* @passcase				if telephony_network_get_signal_strength returns 0 on success
* @failcase				if telephony_network_get_signal_strength returns negative error value
* @precondition			NA
* @postcondition		NA
*/
int ITc_telephony_network_get_signal_strength_p(void)
{
	START_TEST;
	int nDBm=-1;

	//Target API
	int nRet=telephony_network_get_signal_strength(g_pstTelephonySIMHandle, &nDBm);
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_network_get_signal_strength", TelephonyGetError(nRet));

	if(nDBm==0)
	{
		FPRINTF("[Line : %d][%s] telephony_network_get_signal_strength returned unknown\\n", __LINE__, API_NAMESPACE);
	}

	return 0;

}

