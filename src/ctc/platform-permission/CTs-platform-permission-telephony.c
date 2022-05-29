#include "CTs-platform-permission-common.h"

#define CHECK_SIM_STATE {\
	telephony_sim_state_e eSimState;\
	nRet = telephony_sim_get_state(g_pstTelephonySIMHandle, &eSimState);\
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_sim_get_state", TelServicePrintAPIErrorMSG(nRet));\
	if ( eSimState != TELEPHONY_SIM_STATE_AVAILABLE )\
	{\
	FPRINTF("[Line : %d][%s] telephony_sim_get_state returned state = %s \\n", __LINE__, API_NAMESPACE, TelephonyGetSimState(eSimState));\
	return 1;\
	}\
}

telephony_handle_list_s g_handle_list;
telephony_h g_pstTelephonySIMHandle;
char *TelephonyGetSimState(telephony_sim_state_e eRet);

/**
* @function 		TelephonyGetSimState
* @description	 	Maps enums values to string values
* @parameter		eRet : sim state
* @return 			State string
*/
char *TelephonyGetSimState(telephony_sim_state_e eRet)
{
	char *szErrorVal = "Unknown State";
	switch ( eRet )
	{
	case TELEPHONY_SIM_STATE_UNAVAILABLE:		szErrorVal = "TELEPHONY_SIM_STATE_UNAVAILABLE";		break;
	case TELEPHONY_SIM_STATE_LOCKED:		szErrorVal = "TELEPHONY_SIM_STATE_LOCKED";		break;
	case TELEPHONY_SIM_STATE_AVAILABLE:		szErrorVal = "TELEPHONY_SIM_STATE_AVAILABLE";		break;
	case TELEPHONY_SIM_STATE_UNKNOWN:		szErrorVal = "TELEPHONY_SIM_STATE_UNKNOWN";		break;
	}
	return szErrorVal;
}

/**
* @function         CTs_platform_permission_telephony_startup
* @description      Called before each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_telephony_startup(void)
{
    struct stat stBuff;
    if ( stat(ERR_LOG, &stBuff) == 0 )
    {
	if (remove(ERR_LOG))
	{
		FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
	}
    }

#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_telephony_startup\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function         CTs_platform_permission_telephony_cleanup
* @description      Called after each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_telephony_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_telephony_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
    return;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_get_state
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			Acquire the list of available handles to use telephony API\n
* 					Checks the device whether the SIM card is available or not\n
* 					Gets the IMEI (International Mobile Station Equipment Identity) of a mobile phone\n
* 					Deinitialize telephony handle list
* @apicovered		telephony_sim_get_state
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_get_state(void)
{
	START_TEST;
	telephony_sim_state_e eSimState = TELEPHONY_SIM_STATE_UNKNOWN;
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}

	int nRet = telephony_sim_get_state(g_hTelephony, &eSimState);
	TelServiceDeInitializeHandler();
	
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_sim_get_state", TelServicePrintAPIErrorMSG(nRet));
	
	return 0;
}

//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_PrefVoiceSubscription
* @since_tizen		2.4
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			Gets the current value for the preferred voice call subscription.
* @apicovered		telephony_init, telephony_call_get_preferred_voice_subscription,telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_PrefVoiceSubscription(void)
{
	START_TEST;
	
    telephony_call_preferred_voice_subs_e call_sub = 0;
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}

	int nRet = telephony_call_get_preferred_voice_subscription(g_hTelephony , &call_sub);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_call_get_preferred_voice_subscription", TelServicePrintAPIErrorMSG(nRet));
	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_GetCallList
* @since_tizen		2.4
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			Gets the call list
* @apicovered		telephony_init, telephony_call_get_call_list, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_GetCallList(void)
{
	START_TEST;
	
	unsigned int count = 0;
    telephony_call_h *call_list = NULL;
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	int nRet = telephony_call_get_call_list(g_hTelephony, &count, &call_list);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_call_get_call_list", TelServicePrintAPIErrorMSG(nRet));
	
	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_ModemGetPowerStatus
* @since_tizen		2.4
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			Gets the power status of the modem
* @apicovered		telephony_init, telephony_modem_get_power_status, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_ModemGetPowerStatus(void)
{
	START_TEST;
	
	telephony_modem_power_status_e status = 0;
   
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	int nRet = telephony_modem_get_power_status(g_hTelephony, &status);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_modem_get_power_status", TelServicePrintAPIErrorMSG(nRet));

	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_NetworkGetCellId
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			to get the cell ID
* @apicovered		telephony_init, telephony_network_get_cell_id, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_NetworkGetCellId(void)
{
	START_TEST;
	
	int nGetValue = -1;
   
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	int nRet = telephony_network_get_cell_id(g_hTelephony, &nGetValue);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_network_get_cell_id", TelServicePrintAPIErrorMSG(nRet));
	
	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_NetworkGetLac
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			to get the LAC (Location Area Code) of current network
* @apicovered		telephony_init, telephony_network_get_lac, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_NetworkGetLac(void)
{
	START_TEST;
	
	int nGetValue = -1;
   
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	int nRet = telephony_network_get_lac(g_hTelephony, &nGetValue);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_network_get_lac", TelServicePrintAPIErrorMSG(nRet));
	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_NetworkGetMcc
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			to get the MCC (Mobile Country Code) of the current network
* @apicovered		telephony_init, telephony_network_get_mcc, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_NetworkGetMcc(void)
{
	START_TEST;
	
	char *pszGetValue = NULL;
   
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	int nRet = telephony_network_get_mcc(g_hTelephony, &pszGetValue);
	TelServiceDeInitializeHandler();
    PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_network_get_mcc", TelServicePrintAPIErrorMSG(nRet));
	
	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_NetworkGetMnc
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			to get the MNC (Mobile Network Code) of the current network
* @apicovered		telephony_init, telephony_network_get_mnc, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_NetworkGetMnc(void)
{
	START_TEST;
	
	char *pszGetValue = NULL;
   
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	int nRet = telephony_network_get_mnc(g_hTelephony, &pszGetValue);
	TelServiceDeInitializeHandler();
    PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_network_get_mnc", TelServicePrintAPIErrorMSG(nRet));
	
	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_NetworkName
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			to get the current registered network
* @apicovered		telephony_init, telephony_network_get_network_name, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_NetworkName(void)
{
	START_TEST;
	
	char *pszGetValue = NULL;
   
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	int nRet = telephony_network_get_network_name(g_hTelephony, &pszGetValue);
	TelServiceDeInitializeHandler();
    PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_network_get_network_name", TelServicePrintAPIErrorMSG(nRet));
	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_RoamingStatus
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			to get the roaming status
* @apicovered		telephony_init, telephony_network_get_roaming_status, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_RoamingStatus(void)
{
	START_TEST;
	
	bool bIsRoaming = false;
   
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}

	int nRet = telephony_network_get_roaming_status(g_hTelephony, &bIsRoaming);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_network_get_roaming_status", TelServicePrintAPIErrorMSG(nRet));
	
	return 0;
}	
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_GetRssi
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			to get the RSSI (Received Signal Strength Indicator)
* @apicovered		telephony_init, telephony_network_get_rssi, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_GetRssi(void)
{
	START_TEST;
	
	telephony_network_rssi_e eNetworkRSSI;
	
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}

	int nRet = telephony_network_get_rssi(g_hTelephony, &eNetworkRSSI);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_network_get_rssi", TelServicePrintAPIErrorMSG(nRet));
	
	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_GetServiceState
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			Gets the packet service type of the current registered network.
* @apicovered		telephony_init, telephony_network_get_service_state, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_GetServiceState(void)
{
	START_TEST;
	
	telephony_network_service_state_e eNetworkServiceState = 0;
	
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	int nRet = telephony_network_get_service_state(g_hTelephony, &eNetworkServiceState);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_network_get_service_state", TelServicePrintAPIErrorMSG(nRet));
	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_GetType
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			to get the service type of registered network
* @apicovered		telephony_init, telephony_network_get_type, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_GetType(void)
{
	START_TEST;
	
	telephony_network_type_e eNetworkInfoType;
	
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	int nRet = telephony_network_get_type(g_hTelephony, &eNetworkInfoType);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_network_get_type", TelServicePrintAPIErrorMSG(nRet));
	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_GetPsType
* @since_tizen		2.4
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			Gets the packet service type of the current registered network.
* @apicovered		telephony_init, telephony_network_get_ps_type, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_GetPsType(void)
{
	START_TEST;
	
	telephony_network_ps_type_e ps_type = 0;
	
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	int nRet = telephony_network_get_ps_type(g_hTelephony, &ps_type);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_network_get_ps_type", TelServicePrintAPIErrorMSG(nRet));
	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_GetNetworkNameOption
* @since_tizen		2.4
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			Gets the network name option of the current registered network.
* @apicovered		telephony_init, telephony_network_get_network_name_option, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_GetNetworkNameOption(void)
{
	START_TEST;
	
	telephony_network_name_option_e network_name_option = 0;
	
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	
	int nRet = telephony_network_get_network_name_option(g_hTelephony, &network_name_option);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_network_get_network_name_option", TelServicePrintAPIErrorMSG(nRet));
	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_GetDefaultDataSubs
* @since_tizen		2.4
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			Gets the current default subscription for data service (Packet Switched).
* @apicovered		telephony_init, telephony_network_get_default_data_subscription, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_GetDefaultDataSubs(void)
{
	START_TEST;
	
	telephony_network_default_data_subs_e default_sub = 0;
	
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	int nRet = telephony_network_get_default_data_subscription(g_hTelephony, &default_sub);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_network_get_default_data_subscription", TelServicePrintAPIErrorMSG(nRet));
	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_GetDefaultSubs
* @since_tizen		2.4
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			Gets the current default subscription for voice service (Circuit Switched).
* @apicovered		telephony_init, telephony_network_get_default_subscription, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_GetDefaultSubs(void)
{
	START_TEST;
	
	telephony_network_default_subs_e default_sub = -2;
	
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	int nRet = telephony_network_get_default_subscription(g_hTelephony, &default_sub);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_network_get_default_subscription", TelServicePrintAPIErrorMSG(nRet));
	return 0;
}

//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_SimGetMsin
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			to get the Mobile Subscription Identification Number (MSIN) of SIM provider
* @apicovered		telephony_init, telephony_sim_get_msin, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_SimGetMsin(void)
{
	START_TEST;
	
	char *pszGetValue = NULL;
	
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	int nRet = telephony_sim_get_msin(g_hTelephony, &pszGetValue);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_sim_get_msin", TelServicePrintAPIErrorMSG(nRet));
	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_SimGetOperator
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			to get the SIM Operator (MCC + MNC)
* @apicovered		telephony_init, telephony_sim_get_operator, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_SimGetOperator(void)
{
	START_TEST;
	
	char *pszGetValue = NULL;
	
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	int nRet = telephony_sim_get_operator(g_hTelephony, &pszGetValue);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_sim_get_operator", TelServicePrintAPIErrorMSG(nRet));
	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_SimGetSpn
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			get the Service Provider Name (SPN) of SIM card.
* @apicovered		telephony_init, telephony_sim_get_spn, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_SimGetSpn(void)
{
	START_TEST;
	
	char *pszGetValue = NULL;
	
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	int nRet = telephony_sim_get_spn(g_hTelephony, &pszGetValue);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_sim_get_spn", TelServicePrintAPIErrorMSG(nRet));
	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_SimGetSubscriptionNo
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			get the SIM card subscriber number
* @apicovered		telephony_init, telephony_sim_get_subscriber_number, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_SimGetSubscriptionNo(void)
{
	START_TEST;
	
	char *pszGetValue = NULL;
	
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	int nRet = telephony_sim_get_subscriber_number(g_hTelephony, &pszGetValue);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_sim_get_subscriber_number", TelServicePrintAPIErrorMSG(nRet));
	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_SimIsChanged
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			check if current SIM card is different from previous SIM card or not
* @apicovered		telephony_init, telephony_sim_is_changed, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_SimIsChanged(void)
{
	START_TEST;
	
	bool bIsChanged = false;
	
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	int nRet = telephony_sim_is_changed(g_hTelephony, &bIsChanged);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_sim_is_changed", TelServicePrintAPIErrorMSG(nRet));
	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_SimGetSubscriptionId
* @since_tizen		2.4
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			Gets subscriber ID encoded.
* @apicovered		telephony_init, telephony_sim_get_subscriber_id, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_SimGetSubscriptionId(void)
{
	START_TEST;
	
	char *subscriber_id = NULL;
	
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	int nRet = telephony_sim_get_subscriber_id(g_hTelephony, &subscriber_id);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_sim_get_subscriber_id", TelServicePrintAPIErrorMSG(nRet));
	return 0;
}
//& purpose: Checks tizen.org/privilege/telephony
//&type: auto
/**
* @testcase			CTc_Telephony_Privilege_Telephony_SimGetApplicationList
* @since_tizen		2.4
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			Gets the list of application on UICC.
* @apicovered		telephony_init, telephony_sim_get_application_list, telephony_deinit.
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		SIM card must available in device.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_SimGetApplicationList(void)
{
	START_TEST;
	
	unsigned int app_list  = 0;
	
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}

	if ( false == TelServiceInitializeHandler())
	{
		return 1;
	}
	
	int nRet = telephony_sim_get_application_list(g_hTelephony,&app_list);
	TelServiceDeInitializeHandler();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_sim_get_application_list", TelServicePrintAPIErrorMSG(nRet));
	return 0;
}

//& type: auto
//& purpose: Checks tizen.org/privilege/telephony
/**
* @testcase 		CTc_Telephony_Privilege_Telephony_sim_get_lock_state
* @author           SRID(arvin.mittal)
* @reviewer         SRID(shobhit.v)
* @type 			auto
* @since_tizen 		3.0
* @description		Gets the lock state of the SIM
* @scenario			Gets the lock state of the SIM
* @apicovered		telephony_sim_get_lock_state
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		working SIM card must be present in device and SIM state must be TELEPHONY_SIM_STATE_LOCKED.
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_sim_get_lock_state(void)
{
	START_TEST;
	
	int nRet;
	telephony_sim_lock_state_e eSimLockState = -1 ;

	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}
	if(telephony_init(&g_handle_list) == TELEPHONY_ERROR_NONE && g_handle_list.count > 0)
	{
		g_pstTelephonySIMHandle = g_handle_list.handle[0];
		nRet =  telephony_sim_get_lock_state(g_pstTelephonySIMHandle, &eSimLockState);
		PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_sim_get_lock_state", TelServicePrintAPIErrorMSG(nRet));
	}
	else
	{
		FPRINTF("[Line : %d][%s] telephony_init failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
		
	return 0;
}

//& type: auto
//& purpose: Checks tizen.org/privilege/telephony
/**
* @testcase 		CTc_Telephony_Privilege_Telephony_network_get_selection_mode
* @author           SRID(arvin.mittal)
* @reviewer         SRID(shobhit.v)
* @type 			auto
* @since_tizen 		3.0
* @description		Gets the network selection mode.
* @scenario			Gets the network selection mode.
* @apicovered		telephony_network_get_selection_mode
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		working SIM card must be present in device
* @postcondition	NA
*/
int CTc_Telephony_Privilege_Telephony_network_get_selection_mode(void)
{
	START_TEST;
	
	telephony_network_selection_mode_e mode = -1;
	
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}
	
	if(telephony_init(&g_handle_list) == TELEPHONY_ERROR_NONE && g_handle_list.count > 0)
	{
		g_pstTelephonySIMHandle = g_handle_list.handle[0];
		int nRet = telephony_network_get_selection_mode(g_pstTelephonySIMHandle, &mode);
		PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "telephony_network_get_selection_mode", TelServicePrintAPIErrorMSG(nRet));
	}
	else
	{
		FPRINTF("[Line : %d][%s] telephony_init failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}
