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
#include "ITs-connection-common.h"

/** @addtogroup itc-connection
*  @ingroup itc
*  @{
*/

//& set: Connection

static int g_nConnectionPreconditionError = 0;
static connection_h g_hConenctionHandle = NULL;
static connection_profile_h g_hConnectionProfileHandleCellular = NULL;

static GMainLoop *g_pMainLoop;
static bool g_bCallbackResult = false;
gboolean Timeout_Function_cellular(gpointer data);
bool bTelFeatureSupported;
connection_cellular_state_e eState;

gboolean Timeout_Function_cellular(gpointer data)
{
	g_main_loop_quit((GMainLoop *)data);
	return false;
}

static void test_connection_set_default_callback(connection_error_e result, void* user_data)
{
	FPRINTF("[Line: %d][%s] Inside test_connection_set_default_callback\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

void ITs_connection_cellular_profile_startup(void)
{
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT start-up: ITs_Connection_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bFeatureSupported = true;
	g_bFeatureMismatch = false;
	g_bFeatureNotSupported = false;

	bTelFeatureSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE, API_NAMESPACE);
	bool bWifiFeatureSupported = TCTCheckSystemInfoFeatureSupported(WIFI_FEATURE, API_NAMESPACE);
	bool bEthernetFeatureSupported = TCTCheckSystemInfoFeatureSupported(ETHERNET_FEATURE, API_NAMESPACE);
	bool bBtFeatureSupported = TCTCheckSystemInfoFeatureSupported(TETHERING_BLUETOOTH_FEATURE, API_NAMESPACE);



	g_nConnectionPreconditionError = 0;
	g_bCallbackResult = false;
	g_hConnectionProfileHandleCellular = NULL;
	g_hConenctionHandle = NULL;

	int nRet = connection_create(&g_hConenctionHandle);
	if ( false == bTelFeatureSupported && false == bWifiFeatureSupported && false == bBtFeatureSupported && false == bEthernetFeatureSupported )
	{
		g_bFeatureSupported = false;
		if ( nRet != CONNECTION_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line: %d][%s] connection_create API call returned mismatch %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			g_bFeatureMismatch = true;
		}
		else
		{
			FPRINTF("[Line: %d][%s] connection_create API call correctly returned %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			g_bFeatureNotSupported = true;
		}
		return;
	}

	if ( (nRet != CONNECTION_ERROR_NONE ) || (g_hConenctionHandle == NULL ) )
	{
		g_nConnectionPreconditionError = 1;
		g_hConenctionHandle = NULL;
		return;
	}

	nRet = connection_get_cellular_state(g_hConenctionHandle, &eState);
    if ( nRet != CONNECTION_ERROR_NONE && nRet != CONNECTION_ERROR_NOT_SUPPORTED)
	{
		FPRINTF("[Line: %d][%s] connection_get_cellular_state failed in startup, returned error %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
		g_nConnectionPreconditionError = 1;
		return;
	}
    if (eState == CONNECTION_CELLULAR_STATE_OUT_OF_SERVICE)
	{
		FPRINTF("[Line: %d][%s] Cellular state is out of service\\n", __LINE__, API_NAMESPACE);
		g_bFeatureNotSupported = true;
		return;
	}

	if ( ConnectionManager_get_celluar_profile(g_hConenctionHandle, &g_hConnectionProfileHandleCellular) == 0 )
	{
		if ( false == bTelFeatureSupported )
		{
			if ( g_hConnectionProfileHandleCellular == NULL )
			{
				FPRINTF("[Line: %d][%s] Cellular profile handle is NULL, unsupported telephony feature\\n", __LINE__, API_NAMESPACE);
				g_bFeatureNotSupported = true;
			}
			else
			{
				FPRINTF("[Line: %d][%s] Cellular profile handle is not NULL, mismatch for unsupported telephony feature\\n", __LINE__, API_NAMESPACE);
				g_bFeatureMismatch = true;
			}
			return;
		}
		else
		{
			g_nConnectionPreconditionError = 1;
			FPRINTF("[Line: %d][%s] Startup failed on getting cellular profile\\n", __LINE__, API_NAMESPACE);
			return;
		}
	}

	if ( g_hConnectionProfileHandleCellular == NULL )
	{
		g_nConnectionPreconditionError = 1;
		FPRINTF("[Line: %d][%s] Startup failed on create cellular profile :: NULL\\n", __LINE__, API_NAMESPACE);
		return;
	}
}

void ITs_connection_cellular_profile_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_Connection_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet = 0;

	if ( g_nConnectionPreconditionError == 0 && g_bFeatureSupported == true )
	{
		if ( g_hConnectionProfileHandleCellular != NULL )
		{
			nRet = connection_profile_destroy(g_hConnectionProfileHandleCellular);
			if ( nRet != CONNECTION_ERROR_NONE )
			{
				FPRINTF("[Line: %d][%s] connection_profile_destroy failed on post condition error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			}
		}

		nRet = connection_destroy(g_hConenctionHandle);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line: %d][%s] connection_destroy failed on post condition error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
		}
	}

	g_nConnectionPreconditionError = 0;
}

/** @addtogroup itc-connection-profile-testcases
*  @brief 		Integration testcases for module connection-profile
*  @ingroup 	itc-connection-profile
*  @{
*/

//& purpose: To check cellular profile
//& type : auto
/**
* @testcase 			ITc_connection_profile_set_get_cellular_apn_p
* @since_tizen			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check create and destroy connection profile
* @scenario				Call API to set the APN(Access Point Name)\n
*						Call API to get the APN
* @apicovered			connection_profile_set_cellular_apn, connection_profile_get_cellular_apn
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_set_get_cellular_apn_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_profile_set_get_cellular_apn_p precondition failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// Initializing test variable
	char *pszSetApnName = "profile.net";
	char *pszGetApnName = NULL;

	int nRet = connection_profile_set_cellular_apn(g_hConnectionProfileHandleCellular, pszSetApnName);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_set_cellular_apn", ConnectionGetError(nRet));

	nRet = connection_profile_get_cellular_apn(g_hConnectionProfileHandleCellular, &pszGetApnName);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_cellular_apn", ConnectionGetError(nRet));

	if ( strcmp(pszSetApnName, pszGetApnName ) != 0 )
	{
		FPRINTF("[Line: %d][%s] connection_profile_get_cellular_apn failed, mismatch in value", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszGetApnName);
		return 1;
	}

	FREE_MEMORY(pszGetApnName);
	return 0;
}

//& purpose: To check set/get the authentication information
//& type : auto
/**
* @testcase 			ITc_connection_profile_set_get_cellular_auth_info_p
* @since_tizen			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check set/get the authentication information
* @scenario				Call API to set authentication information\n
*						Call API to get authentication information
* @apicovered			connection_profile_set_cellular_auth_info, connection_profile_get_cellular_auth_info
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_set_get_cellular_auth_info_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_profile_set_get_cellular_auth_info_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = -1, nEnumLoopCount;

	// Initializing test variable
	char *pszUserName = "tizen";
	char *pszPassword = "flower";
	char *pszFindUserName = NULL;
	char *pszFindPassword = NULL;
	connection_cellular_auth_type_e eConnectionCellularAuthType;
	int arrConnectionCellularAuthTypeSet[] = {
		CONNECTION_CELLULAR_AUTH_TYPE_NONE,		/**< No authentication */
		CONNECTION_CELLULAR_AUTH_TYPE_PAP,		/**< PAP authentication */
		CONNECTION_CELLULAR_AUTH_TYPE_CHAP,		/**< CHAP authentication */
	};
	int nConenctionCellularAuthTypeCount = sizeof(arrConnectionCellularAuthTypeSet) / sizeof(arrConnectionCellularAuthTypeSet[0]);
	connection_cellular_auth_type_e eFindCellularAuthType = -1;

	for ( nEnumLoopCount = 0; nEnumLoopCount < nConenctionCellularAuthTypeCount; nEnumLoopCount++ )
	{
		eConnectionCellularAuthType = arrConnectionCellularAuthTypeSet[nEnumLoopCount];

		nRet = connection_profile_set_cellular_auth_info(g_hConnectionProfileHandleCellular, eConnectionCellularAuthType, pszUserName, pszPassword);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line: %d][%s] connection_profile_set_cellular_auth_info failed for cellular auth type = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetCellularAuthType(eConnectionCellularAuthType), ConnectionGetError(nRet));
			return 1;
		}

		nRet = connection_profile_get_cellular_auth_info(g_hConnectionProfileHandleCellular, &eFindCellularAuthType, &pszFindUserName, &pszFindPassword);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line: %d][%s] connection_profile_get_cellular_auth_info failed for cellular auth type = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetCellularAuthType(eConnectionCellularAuthType), ConnectionGetError(nRet));
			return 1;
		}

		if ( eFindCellularAuthType != eConnectionCellularAuthType )
		{
			FPRINTF("[Line: %d][%s] connection_profile_get_cellular_auth_info failed, mismatch in cellular auth type {set type :get type}::{%s : %s}\\n", __LINE__, API_NAMESPACE, ConnectionGetCellularAuthType(eConnectionCellularAuthType), ConnectionGetCellularAuthType(eFindCellularAuthType));
			return 1;
		}

		if ( strcmp(pszFindUserName, pszUserName) != 0 )
		{
			FPRINTF("[Line: %d][%s] connection_profile_get_cellular_auth_info failed, mismatch in user name {set user name : get user name} ::{ %s:%s }\\n", __LINE__, API_NAMESPACE, pszUserName, pszFindUserName);
			FREE_MEMORY(pszFindPassword);
			FREE_MEMORY(pszFindUserName);
			return 1;
		}

		if ( strcmp(pszFindPassword, pszPassword ) != 0 )
		{
			FPRINTF("[Line: %d][%s] connection_profile_get_cellular_auth_info failed, mismatch in password {set pswd : get pswd} ::{ %s:%s }\\n", __LINE__, API_NAMESPACE, pszPassword, pszFindPassword);
			FREE_MEMORY(pszFindPassword);
			FREE_MEMORY(pszFindUserName);
			return 1;
		}

		FREE_MEMORY(pszFindPassword);
		FREE_MEMORY(pszFindUserName);
	}

	return 0;
}

//& purpose: To check set/get home url
//& type : auto
/**
* @testcase 			ITc_connection_profile_set_get_cellular_home_url_p
* @since_tizen			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check set/get the authentication information
* @scenario				Call API to set home url\n
*						Call API to get home url
* @apicovered			connection_profile_set_cellular_home_url, connection_profile_get_cellular_home_url
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_set_get_cellular_home_url_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_profile_set_get_cellular_home_url_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// Initializing test variable
	char *pszURL = "tizen.org";
	char *pszFindURL= NULL;

	int nRet = connection_profile_set_cellular_home_url(g_hConnectionProfileHandleCellular, pszURL);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_set_cellular_home_url", ConnectionGetError(nRet));

	nRet = connection_profile_get_cellular_home_url(g_hConnectionProfileHandleCellular, &pszFindURL);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_cellular_home_url", ConnectionGetError(nRet));

	if ( strcmp(pszFindURL, pszURL) != 0 )
	{
		FPRINTF("[Line: %d][%s] connection_profile_get_cellular_home_url failed, mismatch in value\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	FREE_MEMORY(pszFindURL);
	return 0;
}

//& purpose: To check set/get service type
//& type : auto
/**
* @testcase 			ITc_connection_profile_set_get_cellular_service_type_p
* @since_tizen			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check set/get service type
* @scenario				Call API to set service type\n
*						Call API to get service type
* @apicovered			connection_profile_set_cellular_service_type, connection_profile_get_cellular_service_type
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_set_get_cellular_service_type_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_profile_set_get_cellular_service_type_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = -1, nEnumLoopCount;
	// Initializing test variable
	connection_cellular_service_type_e eSetServiceType;
	int arrConnectionCellularServiceTypeSet[] = {
		/*CONNECTION_CELLULAR_SERVICE_TYPE_UNKNOWN,*/			/**< Unknown */			//Invalid Type for API
		CONNECTION_CELLULAR_SERVICE_TYPE_INTERNET,				/**< Internet */
		CONNECTION_CELLULAR_SERVICE_TYPE_MMS,					/**< MMS */
		CONNECTION_CELLULAR_SERVICE_TYPE_PREPAID_INTERNET,		/**< Prepaid internet */
		CONNECTION_CELLULAR_SERVICE_TYPE_PREPAID_MMS,			/**< Prepaid MMS */
		CONNECTION_CELLULAR_SERVICE_TYPE_TETHERING,				/**< Tethering */
		CONNECTION_CELLULAR_SERVICE_TYPE_APPLICATION,			/**< Specific application */
	};
	int nConnectionCellularServiceTypeCount = sizeof(arrConnectionCellularServiceTypeSet) / sizeof(arrConnectionCellularServiceTypeSet[0]);
	connection_cellular_service_type_e eGetServiceType = -1;

	for ( nEnumLoopCount = 0; nEnumLoopCount < nConnectionCellularServiceTypeCount; nEnumLoopCount++ )
	{
		eSetServiceType = arrConnectionCellularServiceTypeSet[nEnumLoopCount];

		nRet = connection_profile_set_cellular_service_type(g_hConnectionProfileHandleCellular, eSetServiceType);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line: %d][%s] connection_profile_set_cellular_service_type failed for cellular service type = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetCellularServiceType(eSetServiceType), ConnectionGetError(nRet));
			return 1;
		}

		nRet = connection_profile_get_cellular_service_type(g_hConnectionProfileHandleCellular, &eGetServiceType);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line: %d][%s] connection_profile_get_cellular_service_type failed for cellular service type = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetCellularServiceType(eSetServiceType), ConnectionGetError(nRet));
			return 1;
		}

		if ( eSetServiceType != eGetServiceType )
		{
			FPRINTF("[Line: %d][%s] connection_profile_get_cellular_service_type failed, mismatch in service type {set:get}::{%s:%s}\\n", __LINE__, API_NAMESPACE, ConnectionGetCellularServiceType(eSetServiceType), ConnectionGetCellularServiceType(eGetServiceType));
			return 1;
		}
	}

	return 0;
}
#if (defined(MOBILE) || defined(WEARABLE)  || defined(TIZENIOT)) || defined(TV)
//& purpose: Gets the cellular pdn type.
//& type : auto
/**
* @testcase 			ITc_connection_profile_set_get_cellular_pdn_type_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Gets the cellular pdn type.
* @scenario				Gets the cellular pdn type.
* @apicovered			connection_profile_set_cellular_pdn_type, connection_profile_get_cellular_pdn_type
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_set_get_cellular_pdn_type_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_profile_set_get_cellular_apn_p precondition failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int  nEnumLoopCount;
	connection_cellular_pdn_type_e eSetPdnType;
	int arrConnectionCellularPdnTypeSet[] = {
		CONNECTION_CELLULAR_PDN_TYPE_IPV4 ,
		CONNECTION_CELLULAR_PDN_TYPE_IPV6 ,
		CONNECTION_CELLULAR_PDN_TYPE_IPV4_IPv6 ,
	};
	int nConnectionCellularPdnTypeCount = sizeof(arrConnectionCellularPdnTypeSet) / sizeof(arrConnectionCellularPdnTypeSet[0]);
	connection_cellular_pdn_type_e eGetPdnType = -1;

	for ( nEnumLoopCount = 0; nEnumLoopCount < nConnectionCellularPdnTypeCount; nEnumLoopCount++ )
	{
		eSetPdnType = arrConnectionCellularPdnTypeSet[nEnumLoopCount];

		int nRet = connection_profile_set_cellular_pdn_type(g_hConnectionProfileHandleCellular, eSetPdnType);
		if ( false == bTelFeatureSupported )
		{
			if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
			{

				FPRINTF("[Line: %d][%s] connection_profile_set_cellular_pdn_type API call returned mismatch %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
				return 1;
			}
			else
			{
				FPRINTF("[Line: %d][%s] connection_profile_set_cellular_pdn_type API call correctly returned %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
				return 0;
			}
		}
		PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_set_cellular_pdn_type", ConnectionGetError(nRet));

		nRet = connection_profile_get_cellular_pdn_type(g_hConnectionProfileHandleCellular, &eGetPdnType);
		PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_cellular_pdn_type", ConnectionGetError(nRet));

		if ( eSetPdnType != eGetPdnType )
		{
			FPRINTF("[Line: %d][%s] connection_profile_get_cellular_pdn_type failed, mismatch in service type {set:get}::{%s:%s}\\n", __LINE__, API_NAMESPACE, ConnectionGetCellularPdnType(eSetPdnType), ConnectionGetCellularPdnType(eGetPdnType));
			return 1;
		}
	}

	return 0;
}
#endif  // End MOBILE or WEARABLE or TIZENIOT

#if (defined(MOBILE) || defined(WEARABLE)  || defined(TIZENIOT)) //Starts MOBILE or WEARABLE or TIZENIOT
//& purpose: To check state of roaming
//& type : auto
/**
* @testcase 			ITc_connection_profile_is_cellular_roaming_p
* @since_tizen			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check state of roaming
* @scenario				Call API to get state of roaming
* @apicovered			connection_profile_is_cellular_roaming
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_is_cellular_roaming_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_profile_is_cellular_roaming_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// Initializing test variable
	bool bOutput;
	int nRet = connection_profile_is_cellular_roaming(g_hConnectionProfileHandleCellular, &bOutput);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_is_cellular_roaming", ConnectionGetError(nRet));
	FPRINTF("[Line: %d][%s] connection_profile_is_cellular_roaming returned = %s\\n", __LINE__, API_NAMESPACE, bOutput ? "true": "false");

	return 0;
}
#endif  // End MOBILE or WEARABLE or TIZENIOT

#ifdef TV	//Starts TV
//& purpose: To check state of roaming
//& type : auto
/**
* @testcase 			ITc_connection_profile_is_cellular_roaming_p
* @since_tizen			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check state of roaming
* @scenario				Call API to get state of roaming
* @apicovered			connection_profile_is_cellular_roaming
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_is_cellular_roaming_p(void)
{
#if 0
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_profile_is_cellular_roaming_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// Initializing test variable
	bool bOutput;
	int nRet = connection_profile_is_cellular_roaming(g_hConnectionProfileHandleCellular, &bOutput);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_is_cellular_roaming", ConnectionGetError(nRet));
	FPRINTF("[Line: %d][%s] connection_profile_is_cellular_roaming returned = %s\\n", __LINE__, API_NAMESPACE, bOutput ? "true": "false");
#endif
	return 0;
}
#endif  //TV	//End TV

#if (defined(MOBILE) || defined(WEARABLE)  || defined(TIZENIOT)) //Starts MOBILE or WEARABLE or TIZENIOT
//& purpose: To check the profile is editable
//& type : auto
/**
* @testcase 			ITc_connection_profile_is_cellular_editable_p
* @since_tizen			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check the profile is editable
* @scenario				check given profile is editable
* @apicovered			connection_profile_is_cellular_editable
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_is_cellular_editable_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_profile_is_cellular_editable_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	bool bFindResults = false;
	int nRet = connection_profile_is_cellular_editable(g_hConnectionProfileHandleCellular, &bFindResults);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_is_cellular_editable", ConnectionGetError(nRet));
	FPRINTF("[Line: %d][%s] connection_profile_is_cellular_editable returned = %s\\n", __LINE__, API_NAMESPACE, bFindResults ? "true": "false");

	return 0;
}
#endif  // End MOBILE or WEARABLE or TIZENIOT

#ifdef TV	//Starts TV
//& purpose: To check the profile is editable
//& type : auto
/**
* @testcase 			ITc_connection_profile_is_cellular_editable_p
* @since_tizen			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check the profile is editable
* @scenario				check given profile is editable
* @apicovered			connection_profile_is_cellular_editable
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_is_cellular_editable_p(void)
{
#if 0
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_profile_is_cellular_editable_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	bool bFindResults = false;
	int nRet = connection_profile_is_cellular_editable(g_hConnectionProfileHandleCellular, &bFindResults);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_is_cellular_editable", ConnectionGetError(nRet));
	FPRINTF("[Line: %d][%s] connection_profile_is_cellular_editable returned = %s\\n", __LINE__, API_NAMESPACE, bFindResults ? "true": "false");
#endif
	return 0;
}
#endif  //TV	//End TV

//& purpose: To check the profile is hidden
//& type : auto
/**
* @testcase 			ITc_connection_profile_is_cellular_hidden_p
* @since_tizen			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check the profile is hidden
* @scenario				check given profile is hidden
* @apicovered			connection_profile_is_cellular_hidden
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_is_cellular_hidden_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_profile_is_cellular_hidden_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	bool bFindResults = false;
	int nRet = connection_profile_is_cellular_hidden(g_hConnectionProfileHandleCellular, &bFindResults);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_is_cellular_hidden", ConnectionGetError(nRet));
	FPRINTF("[Line: %d][%s] connection_profile_is_cellular_hidden returned = %s\\n", __LINE__, API_NAMESPACE, bFindResults ? "true": "false");

	return 0;
}

//& purpose: To check state of celluar connection
//& type : auto
/**
* @testcase 			ITc_connection_get_cellular_state_p
* @since_tizen			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check state of celluar connection
* @scenario				Call API to get state of celluar connection
* @apicovered			connection_get_cellular_state
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_connection_get_cellular_state_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError == 1 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_get_cellular_state_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	connection_cellular_state_e eFindCellularState = -1;
	eFindCellularState = -1;

	int nRet = connection_get_cellular_state(g_hConenctionHandle, &eFindCellularState);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_get_cellular_state", ConnectionGetError(nRet));
	if ( eFindCellularState == -1 )
	{
		FPRINTF("[Line: %d][%s] connection_get_cellular_state failed, returned cellular state :: %s\\n", __LINE__, API_NAMESPACE, ConnectionGetCellularStateType(eFindCellularState));
		return 1;
	}

	return 0;
}

//& purpose: To check set/get default profile which provides the given cellular service
//& type : auto
/**
* @testcase 			ITc_connection_set_get_default_cellular_service_profile_p
* @since_tizen			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check set/get default profile which provides the given cellular service
* @scenario				Call API to set default profile\n
*						Call API to get default profile\n
*						verify the profile
* @apicovered			connection_set_default_cellular_service_profile, connection_get_default_cellular_service_profile
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_set_get_default_cellular_service_profile_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_set_get_default_cellular_service_profile_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// Initializing test variable
	connection_cellular_service_type_e eTestCellularType = -1;
	connection_profile_h hFindConnectionProfile = NULL;
	connection_profile_h hTestConnectionProfile = NULL;

	if ( ConnectionManager_get_celluar_profile(g_hConenctionHandle, &hTestConnectionProfile) == 0 )
	{
		FPRINTF("[Line: %d][%s]failed on precondition to clone cellular profile\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( hTestConnectionProfile == NULL )
	{
		FPRINTF("[Line: %d][%s]failed on precondition cellular profile :: NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = connection_profile_get_cellular_service_type(hTestConnectionProfile, &eTestCellularType);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_cellular_service_type", ConnectionGetError(nRet));
	FPRINTF("[Line: %d][%s] connection_profile_get_cellular_service_type return connection type :: %s\\n", __LINE__, API_NAMESPACE, ConnectionGetCellularServiceType(eTestCellularType));

	nRet = connection_set_default_cellular_service_profile(g_hConenctionHandle, eTestCellularType, hTestConnectionProfile);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_set_default_cellular_service_profile", ConnectionGetError(nRet));

	nRet = connection_get_default_cellular_service_profile(g_hConenctionHandle, eTestCellularType, &hFindConnectionProfile);
	if ( nRet != CONNECTION_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] connection_get_default_cellular_service_profile failed for service type = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetCellularServiceType(eTestCellularType), ConnectionGetError(nRet));
		return 1;
	}

	if ( hFindConnectionProfile == NULL )
	{
		FPRINTF("[Line: %d][%s] connection_get_default_cellular_service_profile, returned default connection profile :: NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = connection_profile_destroy(hFindConnectionProfile);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_destroy", ConnectionGetError(nRet));

	nRet = connection_profile_destroy(hTestConnectionProfile);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_destroy", ConnectionGetError(nRet));

	return 0;
}

//& purpose: To check set default profile(async)
//& type : auto
/**
* @testcase 			ITc_connection_set_get_default_cellular_service_profile_p
* @since_tizen			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check set/get default profile which provides the given cellular service
* @scenario				Call API to set default profile async\n
*						Call API to get default profile\n
*						verify the profile
* @apicovered			connection_set_default_cellular_service_profile_async
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_set_default_cellular_service_profile_async_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_set_get_default_cellular_service_profile_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// Initializing test variable
	int nTtimeoutId = 0;
	g_pMainLoop = g_main_loop_new(NULL, false);
	connection_cellular_service_type_e eCellularServiceType = -1;
	connection_profile_h hTestConnectionProfile = NULL;

	if ( ConnectionManager_get_celluar_profile(g_hConenctionHandle, &hTestConnectionProfile) == 0 )
	{
		FPRINTF("[Line: %d][%s]failed on precondition to clone cellular profile\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( hTestConnectionProfile == NULL )
	{
		FPRINTF("[Line: %d][%s]failed on precondition cellular profile :: NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = connection_profile_get_cellular_service_type(hTestConnectionProfile, &eCellularServiceType);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_cellular_service_type", ConnectionGetError(nRet));
	FPRINTF("[Line: %d][%s] connection_profile_get_cellular_service_type return connection type :: %s\\n", __LINE__, API_NAMESPACE, ConnectionGetCellularServiceType(eCellularServiceType));

	nRet = connection_set_default_cellular_service_profile_async(g_hConenctionHandle, eCellularServiceType, hTestConnectionProfile, test_connection_set_default_callback, NULL);
	if ( nRet != CONNECTION_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] connection_set_default_cellular_service_profile_async failed for cellular service type = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetCellularServiceType(eCellularServiceType), ConnectionGetError(nRet));
		return 1;
	}

	nTtimeoutId = g_timeout_add(10000, Timeout_Function_cellular, g_pMainLoop);
	g_main_loop_run(g_pMainLoop);
	g_source_remove(nTtimeoutId);
	if ( g_bCallbackResult == false )
	{
		FPRINTF("[Line: %d][%s] After connection_set_default_cellular_service_profile_async, getting no response from registered call back\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = connection_profile_destroy(hTestConnectionProfile);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_destroy", ConnectionGetError(nRet));

	return 0;
}

#if (defined(MOBILE) || defined(WEARABLE)  || defined(TIZENIOT)) //Starts MOBILE or WEARABLE or TIZENIOT
//& purpose: To check if profile is default
//& type : auto
/**
* @testcase 			ITc_connection_profile_is_cellular_default_p
* @since_tizen			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check if profile is default
* @scenario				check if profile is default
* @apicovered			connection_profile_is_cellular_default
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_connection_profile_is_cellular_default_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_profile_is_cellular_default_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	bool bIsDefault = true;
	int nRet = connection_profile_is_cellular_default(g_hConnectionProfileHandleCellular, &bIsDefault);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_is_cellular_default", ConnectionGetError(nRet));
	FPRINTF("[Line: %d][%s] connection_profile_is_cellular_default returned = %s\\n", __LINE__, API_NAMESPACE, bIsDefault ? "true": "false");

	return 0;
}
#endif // End MOBILE or WEARABLE or TIZENIOT

#ifdef TV
//& purpose: To check if profile is default
//& type : auto
/**
* @testcase 			ITc_connection_profile_is_cellular_default_p
* @since_tizen			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check if profile is default
* @scenario				check if profile is default
* @apicovered			connection_profile_is_cellular_default
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_connection_profile_is_cellular_default_p(void)
{
#if 0
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_profile_is_cellular_default_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	bool bIsDefault = true;
	int nRet = connection_profile_is_cellular_default(g_hConnectionProfileHandleCellular, &bIsDefault);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_is_cellular_default", ConnectionGetError(nRet));
	FPRINTF("[Line: %d][%s] connection_profile_is_cellular_default returned = %s\\n", __LINE__, API_NAMESPACE, bIsDefault ? "true": "false");
#endif
	return 0;
}
#endif  //TV	//End TV

#if (defined(MOBILE) || defined(WEARABLE)  || defined(TIZENIOT)) || defined(TV) //Starts MOBILE or WEARABLE or TIZENIOT
//& purpose: Gets the cellular roam pdn type
//& type : auto
/**
* @testcase 			ITc_connection_profile_set_get_cellular_roam_pdn_type_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Gets the cellular roam pdn type
* @scenario				Gets the cellular roam pdn type
* @apicovered			connection_profile_set_cellular_roam_pdn_type, connection_profile_get_cellular_roam_pdn_type
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_set_get_cellular_roam_pdn_type_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_profile_set_get_cellular_apn_p precondition failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = -1, nEnumLoopCount;
	// Initializing test variable
	connection_cellular_pdn_type_e eSetPdnType;
	int arrConnectionCellularPdnTypeSet[] = {
		CONNECTION_CELLULAR_PDN_TYPE_IPV4 ,
		CONNECTION_CELLULAR_PDN_TYPE_IPV6 ,
		CONNECTION_CELLULAR_PDN_TYPE_IPV4_IPv6 ,
	};
	int nConnectionCellularPdnTypeCount = sizeof(arrConnectionCellularPdnTypeSet) / sizeof(arrConnectionCellularPdnTypeSet[0]);
	connection_cellular_pdn_type_e eGetPdnType = -1;

	for ( nEnumLoopCount = 0; nEnumLoopCount < nConnectionCellularPdnTypeCount; nEnumLoopCount++ )
	{
		eSetPdnType = arrConnectionCellularPdnTypeSet[nEnumLoopCount];

		nRet = connection_profile_set_cellular_roam_pdn_type(g_hConnectionProfileHandleCellular, eSetPdnType);
		if ( false == bTelFeatureSupported )
		{
			if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
			{

				FPRINTF("[Line: %d][%s] connection_profile_set_cellular_roam_pdn_type API call returned mismatch %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
				return 1;
			}
			else
			{
				FPRINTF("[Line: %d][%s] connection_profile_set_cellular_roam_pdn_type API call correctly returned %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
				return 0;
			}
		}
		PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_set_cellular_roam_pdn_type", ConnectionGetError(nRet));

		nRet = connection_profile_get_cellular_roam_pdn_type(g_hConnectionProfileHandleCellular, &eGetPdnType);
		PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_cellular_roam_pdn_type", ConnectionGetError(nRet));

		if ( eSetPdnType != eGetPdnType )
		{
			FPRINTF("[Line: %d][%s] connection_profile_get_cellular_roam_pdn_type failed, mismatch in service type {set:get}::{%s:%s}\\n", __LINE__, API_NAMESPACE, ConnectionGetCellularPdnType(eSetPdnType), ConnectionGetCellularPdnType(eGetPdnType));
			return 1;
		}
	}

	return 0;
}
#endif  // End MOBILE or WEARABLE or TIZENIOT
/** @} */
/** @} */
