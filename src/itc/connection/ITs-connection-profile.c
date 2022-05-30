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

static int g_nConnectionErrorCount1, g_nConnectionErrorCount2;
static int g_nConnectionPreconditionError = 0;
static int g_nConnectionPreconditionMMSError = 0;
static connection_h g_hConenctionHandle = NULL;
static connection_profile_h g_hConnectionProfileHandleCellular = NULL;
static connection_profile_h g_hConnectionProfileHandleMMS= NULL;

static GMainLoop *g_pMainLoop;
static bool g_bCallbackResult = false;
static bool g_bCloseCallbackResult = false;
static bool g_bOpenCallbackResult = false;
gboolean Timeout_Function(gpointer data);

gboolean Timeout_Function(gpointer data)
{
	g_main_loop_quit((GMainLoop *)data);
	return false;
}

void test_connection_opened_callback(connection_error_e result, void* user_data)
{
	FPRINTF("[Line : %d][%s] Inside callback \"test_connection_opened_callback\"\\n", __LINE__, API_NAMESPACE);
	g_bOpenCallbackResult = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

void test_connection_closed_callback(connection_error_e result, void* user_data)
{
	FPRINTF("[Line : %d][%s] Inside callback \"test_connection_closed_callback\"\\n", __LINE__, API_NAMESPACE);
	g_bCloseCallbackResult = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

static void test_profile_state_changed_cb(connection_profile_state_e state, void* user_data)
{
	FPRINTF("[Line : %d][%s] Inside callback \"test_profile_state_changed_cb\"\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

#if (defined(MOBILE) || defined(WEARABLE)  || defined(TIZENIOT)) //Starts MOBILE or WEARABLE or TIZENIOT
void test_connection_reset_profile_callback_cb(connection_error_e result, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside callback \"test_connection_reset_profile_callback_cb\"\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}
#endif  // End MOBILE or WEARABLE or TIZENIOT

#ifdef TV	//Starts TV
#if 0
void test_connection_reset_profile_callback_cb(connection_error_e result, void *user_data)
{
	FPRINTF("[Line: %d][%s] Inside callback \"test_connection_reset_profile_callback_cb\"\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}
#endif
#endif  //TV	//End TV

void ITs_connection_profile_startup(void)
{
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Connection_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bFeatureSupported = true;
	g_bFeatureMismatch = false;
	g_bFeatureNotSupported = false;

	bool bTelFeatureSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE, API_NAMESPACE);
	bool bWifiFeatureSupported = TCTCheckSystemInfoFeatureSupported(WIFI_FEATURE, API_NAMESPACE);
	bool bBtFeatureSupported = TCTCheckSystemInfoFeatureSupported(TETHERING_BLUETOOTH_FEATURE, API_NAMESPACE);
	bool bEthernetFeatureSupported = TCTCheckSystemInfoFeatureSupported(ETHERNET_FEATURE, API_NAMESPACE);


	g_nConnectionErrorCount1 = 0;
	g_nConnectionErrorCount2 = 0;
	g_nConnectionPreconditionError = 0;
	g_nConnectionPreconditionMMSError =0;
	g_bCallbackResult = false;
	g_hConnectionProfileHandleCellular = NULL;
	g_hConnectionProfileHandleMMS = NULL;
	g_hConenctionHandle = NULL;
	connection_cellular_state_e eState;

	int nRet = connection_create(&g_hConenctionHandle);
	if ( false == bTelFeatureSupported && false == bWifiFeatureSupported && false == bBtFeatureSupported && false == bEthernetFeatureSupported )
	{
		g_bFeatureSupported = false;
		if ( nRet != CONNECTION_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] connection_create API call returned mismatch %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			g_bFeatureMismatch = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] connection_create API call correctly returned %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
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
				FPRINTF("[Line : %d][%s] Cellular profile handle is NULL, unsupported telephony feature\\n", __LINE__, API_NAMESPACE);
				g_bFeatureNotSupported = true;
			}
			else
			{
				FPRINTF("[Line : %d][%s] Cellular profile handle is not NULL, mismatch for unsupported telephony feature\\n", __LINE__, API_NAMESPACE);
				g_bFeatureMismatch = true;
			}
			return;
		}
		else
		{
			g_nConnectionPreconditionError = 1;
			FPRINTF("[Line : %d][%s] Startup failed on getting cellular profile\\n", __LINE__, API_NAMESPACE);
			return;
		}
	}

	if ( ConnectionManager_get_MMS_type(g_hConenctionHandle, &g_hConnectionProfileHandleMMS) == 0 )
	{
		if ( false == bTelFeatureSupported )
		{
			if ( g_hConnectionProfileHandleMMS == NULL )
			{
				FPRINTF("[Line: %d][%s] MMS service type handle is NULL, unsupported telephony feature\\n", __LINE__, API_NAMESPACE);
				g_bFeatureNotSupported = true;
			}
			else
			{
				FPRINTF("[Line: %d][%s] MMS service type handle is not NULL, mismatch for unsupported telephony feature\\n", __LINE__, API_NAMESPACE);
				g_bFeatureMismatch = true;
			}
			return;
		}
		else
		{
			g_nConnectionPreconditionMMSError = 1;
			FPRINTF("[Line: %d][%s] Startup failed on getting MMS service type\\n", __LINE__, API_NAMESPACE);
			return;
		}
	}

	if ( g_hConnectionProfileHandleCellular == NULL )
	{
		g_nConnectionPreconditionError = 1;
		FPRINTF("[Line : %d][%s] Startup failed on create cellular profile :: NULL\\n", __LINE__, API_NAMESPACE);
		return;
	}

	if ( g_hConnectionProfileHandleMMS == NULL )
	{
		g_nConnectionPreconditionMMSError = 1;
		FPRINTF("[Line: %d][%s] Startup failed on create MMS service :: NULL\\n", __LINE__, API_NAMESPACE);
		return;
	}
}

void ITs_connection_profile_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Connection_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet = 0;

	if ( g_nConnectionPreconditionError == 0 && g_bFeatureSupported == true )
	{
		if ( g_hConnectionProfileHandleCellular != NULL )
		{
			nRet = connection_profile_destroy(g_hConnectionProfileHandleCellular);
			if ( nRet != CONNECTION_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] connection_profile_destroy failed on post condition error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			}
		}

		if ( g_hConnectionProfileHandleMMS != NULL )
		{
			nRet = connection_profile_destroy(g_hConnectionProfileHandleMMS);
			if ( nRet != CONNECTION_ERROR_NONE )
			{
				FPRINTF("[Line: %d][%s] connection_profile_destroy failed on post condition error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			}
		}

		nRet = connection_destroy(g_hConenctionHandle);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_destroy failed on post condition error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
		}
	}

	g_nConnectionPreconditionError = 0;
}

/** @addtogroup itc-connection-profile-testcases
*  @brief 		Integration testcases for module connection-profile
*  @ingroup 	itc-connection-profile
*  @{
*/

//& purpose: To check create and destroy connection profile
//& type : auto
/**
* @testcase 			ITc_connection_profile_create_destroy_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check create and destroy connection profile
* @scenario				Call API to create connection profile\n
*						Call API to destroy the created connection profile
* @apicovered			connection_profile_create, connection_profile_destroy
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_connection_profile_create_destroy_p(void)
{
	START_TEST;

	// Initializing test variable
	connection_h hConenction = NULL;
	connection_profile_h hConnectionProfile = NULL;
	connection_profile_type_e eConnectionProfileType = CONNECTION_PROFILE_TYPE_CELLULAR;

	//creating conenction handler
	int nRet = connection_create(&hConenction);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_create", ConnectionGetError(nRet));

	nRet = connection_profile_create( eConnectionProfileType, "TestingCelluarProfile", &hConnectionProfile);
	PRINT_RESULT_CLEANUP(CONNECTION_ERROR_NONE, nRet, "connection_profile_create", ConnectionGetError(nRet), connection_destroy(hConenction));
	if ( hConnectionProfile == NULL )
	{
		FPRINTF("[Line : %d][%s] connection_profile_create failed, returned connection profile :: NULL\\n", __LINE__, API_NAMESPACE);
		connection_destroy(hConenction);
		return 1;
	}

	nRet = connection_profile_destroy(hConnectionProfile);
	PRINT_RESULT_CLEANUP(CONNECTION_ERROR_NONE, nRet, "connection_profile_destroy", ConnectionGetError(nRet), connection_destroy(hConenction));

	nRet = connection_destroy(hConenction);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_destroy", ConnectionGetError(nRet));

	return 0;
}

//& purpose: To check name of connection profile
//& type : auto
/**
* @testcase 			ITc_connection_profile_get_name_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check name of connection profile
* @scenario				Call API to get name
* @apicovered			connection_profile_get_name
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_get_name_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_get_name_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char *pszFindConnectionProfileName;
	int nRet = connection_profile_get_name(g_hConnectionProfileHandleCellular, &pszFindConnectionProfileName);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_name", ConnectionGetError(nRet));

	CHECK_VALUE_STRING(pszFindConnectionProfileName, "connection_profile_get_name");
	FREE_MEMORY(pszFindConnectionProfileName);

	return 0;
}

//& purpose: To check id of connection profile
//& type : auto
/**
* @testcase 			ITc_connection_profile_get_id_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check id of connection profile
* @scenario				Call API to get id
* @apicovered			connection_profile_get_id
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_get_id_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_get_id_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char* pszProfileId = NULL;
	int nRet = connection_profile_get_id(g_hConnectionProfileHandleCellular, &pszProfileId);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_id", ConnectionGetError(nRet));

	CHECK_VALUE_STRING(pszProfileId, "connection_profile_get_id");
	FPRINTF("[Line : %d][%s] connection_profile_get_id returned = %s\\n", __LINE__, API_NAMESPACE, pszProfileId);
	FREE_MEMORY(pszProfileId);

	return 0;
}

//& purpose: To check type of connection profile
//& type : auto
/**
* @testcase 			ITc_connection_profile_get_type_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check type of connection profile
* @scenario				Call API to get type
* @apicovered			connection_profile_get_type
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_get_type_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_get_type_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// Initializing test variable
	connection_profile_type_e eConnectionProfileType = CONNECTION_PROFILE_TYPE_CELLULAR;
	connection_profile_type_e eFindConnectionProfileType;

	int nRet = connection_profile_get_type(g_hConnectionProfileHandleCellular, &eFindConnectionProfileType);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_type", ConnectionGetError(nRet));

	if ( eConnectionProfileType != eFindConnectionProfileType )
	{
		FPRINTF("[Line : %d][%s] connection_profile_get_type failed, mismatch in connection type value", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: To check name of network interface
//& type : auto
/**
* @testcase 			ITc_connection_profile_get_network_interface_name_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check name of network interface
* @scenario				Call API to get name of network interface
* @apicovered			connection_profile_get_network_interface_name
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_get_network_interface_name_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_get_network_interface_name_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// Initializing test variable
	char* pszGetInterfaceName = NULL;
	int nRet = connection_profile_get_network_interface_name(g_hConnectionProfileHandleCellular, &pszGetInterfaceName);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_network_interface_name", ConnectionGetError(nRet));

	CHECK_VALUE_STRING(pszGetInterfaceName, "connection_profile_get_network_interface_name");
	FREE_MEMORY(pszGetInterfaceName);

	return 0;
}

//& purpose: To check clone of profile handler
//& type : auto
/**
* @testcase 			ITc_connection_profile_create_destroy_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check create and destroy connection profile
* @scenario				Call API to create clone of connection profile handle\n
*						Call API to destroy cloned connection profile
* @apicovered			connection_profile_clone, connection_profile_destroy
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_clone_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_clone_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// Initializing test variable
	connection_profile_h hConnectionProfileTemp = NULL;
	int nRet = connection_profile_clone(&hConnectionProfileTemp,g_hConnectionProfileHandleCellular);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_clone", ConnectionGetError(nRet));
	CHECK_HANDLE(hConnectionProfileTemp, "connection_profile_clone");

	nRet = connection_profile_destroy(hConnectionProfileTemp);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_destroy", ConnectionGetError(nRet));

	return 0;
}


//& purpose: To check state of profile
//& type : auto
/**
* @testcase 			ITc_connection_profile_get_state_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check state of profile
* @scenario				Call API to get state of profile
* @apicovered			connection_profile_get_state
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_get_state_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_get_state_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// Initializing test variable
	connection_profile_state_e eConnectionProfileState = -1;
	int nRet = connection_profile_get_state(g_hConnectionProfileHandleCellular, &eConnectionProfileState);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_state", ConnectionGetError(nRet));
	if ( eConnectionProfileState == -1 )
	{
		FPRINTF("[Line : %d][%s] connection_profile_get_state failed, invalid value\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: To check set/get dns address
//& type : auto
/**
* @testcase 			ITc_connection_profile_set_get_dns_address_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check set/get dns address
* @scenario				Call API to set dns address\n
*						Call API to get dns address
* @apicovered			connection_profile_set_dns_address, connection_profile_get_dns_address
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_set_get_dns_address_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_set_get_dns_address_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = -1, nEnumLoopCount;

	// Initializing test variable
	char* pszTestDns = NULL;
	char* pszFindDns = NULL;
	int arrConnectionAddressFamilyValues[] = {
		CONNECTION_ADDRESS_FAMILY_IPV4,  /**< IPV4 Address type */
		//CONNECTION_ADDRESS_FAMILY_IPV6  /**< IPV6 Address type */
	};
	int nConnectionFamilyCount = sizeof(arrConnectionAddressFamilyValues) / sizeof(arrConnectionAddressFamilyValues[0]);
	connection_address_family_e e_address_family;

	for ( nEnumLoopCount = 0; nEnumLoopCount < nConnectionFamilyCount; nEnumLoopCount++ )
	{
		e_address_family = arrConnectionAddressFamilyValues[nEnumLoopCount];
		if ( nEnumLoopCount == 0 )
		{
			pszTestDns = "192.168.127.11";
		}
		else
		{
			pszTestDns = "2001:0db8:0000:0000:0000:ff00:0042:8329";
		}

		nRet = connection_profile_set_dns_address(g_hConnectionProfileHandleCellular, 1, e_address_family, pszTestDns);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_profile_set_dns_address failed for address family = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetAddressFamily(e_address_family), ConnectionGetError(nRet));
			return 1;
		}

		nRet = connection_profile_get_dns_address(g_hConnectionProfileHandleCellular, 1, e_address_family, &pszFindDns);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_profile_get_dns_address failed for address family = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetAddressFamily(e_address_family), ConnectionGetError(nRet));
			return 1;
		}

		if ( strcmp(pszTestDns, pszFindDns) != 0 )
		{
			FPRINTF("[Line : %d][%s] connection_profile_get_dns_address failed, mismatch in dns address {(set : get)::(%s : %s)}\\n", __LINE__, API_NAMESPACE, pszTestDns, pszFindDns);
			FREE_MEMORY(pszFindDns);
			return 1;
		}

		FREE_MEMORY(pszFindDns);
	}

	return 0;
}

//& purpose: To check set/get gatway
//& type : auto
/**
* @testcase 			ITc_connection_profile_set_get_gateway_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check set/get gatway
* @scenario				Call API to set gateway\n
*						Call API to get gateway
* @apicovered			connection_profile_set_gateway_address, connection_profile_get_gateway_address
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_set_get_gateway_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_set_get_gateway_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = -1, nEnumLoopCount;

	// Initializing test variable
	char* pszTestGateway = NULL;
	char* pszFindFGateway = NULL;

	int arrConnectionAddressFamilyValues[] = {
		CONNECTION_ADDRESS_FAMILY_IPV4,  /**< IPV4 Address type */
		//CONNECTION_ADDRESS_FAMILY_IPV6  /**< IPV6 Address type */
	};
	int nConnectionFamilyCount = sizeof(arrConnectionAddressFamilyValues) / sizeof(arrConnectionAddressFamilyValues[0]);
	connection_address_family_e e_address_family;

	for ( nEnumLoopCount = 0; nEnumLoopCount < nConnectionFamilyCount; nEnumLoopCount++ )
	{
		e_address_family = arrConnectionAddressFamilyValues[nEnumLoopCount];
		if ( nEnumLoopCount == 0 )
		{
			pszTestGateway = "192.168.127.1";
		}
		else
		{
			pszTestGateway = "2002:c0a8:7f01:0:0:0:0:0";
		}

		nRet = connection_profile_set_gateway_address(g_hConnectionProfileHandleCellular, e_address_family, pszTestGateway);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_profile_set_gateway_address failed for address family = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetAddressFamily(e_address_family), ConnectionGetError(nRet));
			return 1;
		}

		nRet = connection_profile_get_gateway_address(g_hConnectionProfileHandleCellular, e_address_family, &pszFindFGateway);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_profile_get_gateway_address failed for address family = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetAddressFamily(e_address_family), ConnectionGetError(nRet));
			return 1;
		}

		if ( strcmp(pszTestGateway, pszFindFGateway) != 0 )
		{
			FPRINTF("[Line : %d][%s] connection_profile_get_gateway_address failed, mismatch in gateway {(set:get)::(%s:%s)}\\n", __LINE__, API_NAMESPACE, pszTestGateway, pszFindFGateway);
			FREE_MEMORY(pszFindFGateway);
			return 1;
		}

		FREE_MEMORY(pszFindFGateway);
	}

	return 0;
}

//& purpose:  To check set/get IP address
//& type : auto
/**
* @testcase 			ITc_connection_profile_set_get_ip_address_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check set/get IP address
* @scenario				Call API to set ip address\n
*						Call API to get ip address
* @apicovered			connection_profile_set_ip_address, connection_profile_get_ip_address
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_set_get_ip_address_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] connection_profile_set_ip_address failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = -1, nEnumLoopCount;

	// Initializing test variable
	char* pszTestIPAddress = NULL;
	char* pszFindIPAddress = NULL;
	int arrConnectionAddressFamilyValues[] = {
		CONNECTION_ADDRESS_FAMILY_IPV4,		/**< IPV4 Address type */
		//CONNECTION_ADDRESS_FAMILY_IPV6  /**< IPV6 Address type */
	};
	int nConnectionFamilyCount = sizeof(arrConnectionAddressFamilyValues) / sizeof(arrConnectionAddressFamilyValues[0]);
	connection_address_family_e e_address_family;

	for ( nEnumLoopCount = 0; nEnumLoopCount < nConnectionFamilyCount; nEnumLoopCount++ )
	{
		e_address_family = arrConnectionAddressFamilyValues[nEnumLoopCount];
		if ( nEnumLoopCount == 0 )
		{
			pszTestIPAddress = "192.168.127.11";
		}
		else
		{
			pszTestIPAddress = "2002:c0a8:7f0b:0:0:0:0:0";
		}

		nRet = connection_profile_set_ip_address(g_hConnectionProfileHandleCellular, e_address_family, pszTestIPAddress);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_profile_set_ip_address failed for address family = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetAddressFamily(e_address_family), ConnectionGetError(nRet));
			return 1;
		}

		nRet = connection_profile_get_ip_address(g_hConnectionProfileHandleCellular, e_address_family, &pszFindIPAddress);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_profile_get_ip_address failed for address family = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetAddressFamily(e_address_family), ConnectionGetError(nRet));
			return 1;
		}

		if ( strcmp(pszTestIPAddress, pszFindIPAddress) != 0 )
		{
			FPRINTF("[Line : %d][%s] connection_profile_get_ip_address failed,mismatch in ip address {(set:get)::(%s:%s)}\\n", __LINE__, API_NAMESPACE, pszTestIPAddress, pszFindIPAddress);
			FREE_MEMORY(pszFindIPAddress);
			return 1;
		}

		FREE_MEMORY(pszFindIPAddress);
	}

	return 0;
}

//& purpose:  To check set/get IP config type
//& type : auto
/**
* @testcase 			ITc_connection_profile_set_get_ip_config_type_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check set/get ip config type
* @scenario				Call API to set ip config type\n
*						Call API to get ip config type
* @apicovered			connection_profile_set_ip_config_type, connection_profile_get_ip_config_type
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_set_get_ip_config_type_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_set_get_ip_config_type_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = -1, nEnumConfigLoopCount,nEnumLoopCount;

	// Initializing test variable
	connection_ip_config_type_e eConnectionIPConfigType = CONNECTION_IP_CONFIG_TYPE_STATIC;
	connection_address_family_e e_address_family;
	int arrConnectionAddressFamilyValues[] = {
		CONNECTION_ADDRESS_FAMILY_IPV4,		/**< IPV4 Address type */
		//CONNECTION_ADDRESS_FAMILY_IPV6  /**< IPV6 Address type */
	};
	int nConnectionFamilyCount = sizeof(arrConnectionAddressFamilyValues) / sizeof(arrConnectionAddressFamilyValues[0]);

	int arrConnectionIpConfigTypeValues[] = {
		CONNECTION_IP_CONFIG_TYPE_NONE,  		/**< Not defined */
		CONNECTION_IP_CONFIG_TYPE_STATIC ,  	/**< Manual IP configuration */
		CONNECTION_IP_CONFIG_TYPE_DYNAMIC,  	/**< Config IP using DHCP client*/
		CONNECTION_IP_CONFIG_TYPE_AUTO, 		/**< Config IP from Auto IP pool (169.254/16). Later with DHCP client, if available */
		CONNECTION_IP_CONFIG_TYPE_FIXED,  		/**< Indicates an IP address that can not be modified */
	};
	int nConnectionIPConfigCount = sizeof(arrConnectionIpConfigTypeValues) / sizeof(arrConnectionIpConfigTypeValues[0]);

	connection_ip_config_type_e eFindConnectionIPConfigType;

	for ( nEnumLoopCount = 0; nEnumLoopCount < nConnectionFamilyCount; nEnumLoopCount++ )
	{
		e_address_family = arrConnectionAddressFamilyValues[nEnumLoopCount];
		for ( nEnumConfigLoopCount = 0; nEnumConfigLoopCount < nConnectionIPConfigCount; nEnumConfigLoopCount++)
		{
			eConnectionIPConfigType = arrConnectionIpConfigTypeValues[nEnumConfigLoopCount];

			nRet = connection_profile_set_ip_config_type(g_hConnectionProfileHandleCellular, e_address_family, eConnectionIPConfigType);
			if ( nRet != CONNECTION_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] connection_profile_set_ip_config_type failed for address family = %s and config type = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetAddressFamily(e_address_family), ConnectionGetIpConfigType(eConnectionIPConfigType), ConnectionGetError(nRet));
				return 1;
			}

			nRet = connection_profile_get_ip_config_type(g_hConnectionProfileHandleCellular, e_address_family, &eFindConnectionIPConfigType);
			if ( nRet != CONNECTION_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] connection_profile_get_ip_config_type failed for address family = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetAddressFamily(e_address_family), ConnectionGetError(nRet));
				return 1;
			}

			if ( eConnectionIPConfigType != eFindConnectionIPConfigType )
			{
				FPRINTF("[Line : %d][%s] connection_profile_get_ip_config_type failed, mismatch in config type {(set:get)::(%s:%s)}\\n", __LINE__, API_NAMESPACE, ConnectionGetIpConfigType(eConnectionIPConfigType), ConnectionGetIpConfigType(eFindConnectionIPConfigType));
				g_nConnectionErrorCount2++;
			}
		}
	}

	return 0;
}

//& purpose:  To check set/get proxy type
//& type : auto
/**
* @testcase 			ITc_connection_profile_set_get_proxy_type_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check set/get proxy type
* @scenario				Call API to set proxy type\n
*						Call API to get proxy type
* @apicovered			connection_profile_set_proxy_type, connection_profile_get_proxy_type
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_set_get_proxy_type_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_set_get_proxy_type_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = -1,nEnumLoopCount;
	// Initializing test variable
	connection_proxy_type_e eConnectionProxyType;
	int arrConnectionProxyTypeValues [] = {
		CONNECTION_PROXY_TYPE_DIRECT,  /**< Direct connection */
		CONNECTION_PROXY_TYPE_AUTO,  /**< Auto configuration(Use PAC file). If URL property is not set, DHCP/WPAD auto-discover will be tried */
		CONNECTION_PROXY_TYPE_MANUAL ,  /**< Manual configuration */
	};
	int nConnectionProxyCount = sizeof(arrConnectionProxyTypeValues) / sizeof(arrConnectionProxyTypeValues[0]);
	connection_proxy_type_e eFindConnectionProxyType  = -1;

	for ( nEnumLoopCount = 0; nEnumLoopCount < nConnectionProxyCount; nEnumLoopCount++ )
	{
		eConnectionProxyType = arrConnectionProxyTypeValues[nEnumLoopCount];

		nRet = connection_profile_set_proxy_type(g_hConnectionProfileHandleCellular, eConnectionProxyType);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_profile_set_proxy_type failed for proxy type = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetProxyType(eConnectionProxyType), ConnectionGetError(nRet));
			return 1;
		}

		nRet = connection_profile_get_proxy_type(g_hConnectionProfileHandleCellular, &eFindConnectionProxyType);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_profile_get_proxy_type failed, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			return 1;
		}

		if ( eConnectionProxyType != eFindConnectionProxyType )
		{
			FPRINTF("[Line : %d][%s] connection_profile_get_proxy_type failed, mismatch in proxy type {(set:get)::(%s : %s)}\\n", __LINE__, API_NAMESPACE, ConnectionGetProxyType(eConnectionProxyType), ConnectionGetProxyType(eFindConnectionProxyType));
			return 1;
		}
		eFindConnectionProxyType  = -1;
	}

	return 0;
}

//& purpose:  To check set/get proxy address
//& type : auto
/**
* @testcase 			ITc_connection_profile_set_get_proxy_address_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check set/get proxy address
* @scenario				Call API to set proxy address\n
*						Call API to get proxy address
* @apicovered			connection_profile_set_proxy_address, connection_profile_get_proxy_address
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_set_get_proxy_address_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_set_get_proxy_address_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = -1,nEnumLoopCount;

	// Initializing test variable
	connection_address_family_e e_address_family;
	char* pszTestProxyAddress = NULL;
	char* pszFindProxyAddress = NULL;
	int arrConnectionAddressFamilyValues[] = {
		CONNECTION_ADDRESS_FAMILY_IPV4,  /**< IPV4 Address type */
		//CONNECTION_ADDRESS_FAMILY_IPV6  /**< IPV6 Address type */
	};
	int nConnectionFamilyCount = sizeof(arrConnectionAddressFamilyValues) / sizeof(arrConnectionAddressFamilyValues[0]);

	for ( nEnumLoopCount = 0; nEnumLoopCount < nConnectionFamilyCount; nEnumLoopCount++ )
	{
		e_address_family = arrConnectionAddressFamilyValues[nEnumLoopCount];
		if ( nEnumLoopCount == 0 )
		{
			pszTestProxyAddress = "192.128.1.1:8000";
		}
		else
		{
			pszTestProxyAddress = "2002:c080:0101:0:0:0:0:0:8000";
		}

		nRet = connection_profile_set_proxy_address(g_hConnectionProfileHandleCellular,e_address_family, pszTestProxyAddress);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_profile_set_proxy_address failed for address family = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetAddressFamily(e_address_family), ConnectionGetError(nRet));
			return 1;
		}

		nRet = connection_profile_get_proxy_address(g_hConnectionProfileHandleCellular, e_address_family, &pszFindProxyAddress);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_profile_get_proxy_address failed for address family = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetAddressFamily(e_address_family), ConnectionGetError(nRet));
			return 1;
		}

		if ( strcmp(pszFindProxyAddress, pszTestProxyAddress) != 0 )
		{
			FPRINTF("[Line : %d][%s] connection_profile_get_proxy_address failed, mismatch in proxy address {(set:get)::(%s:%s)}\\n", __LINE__, API_NAMESPACE, pszTestProxyAddress, pszFindProxyAddress);
			FREE_MEMORY(pszFindProxyAddress);
			return 1;
		}

		FREE_MEMORY(pszFindProxyAddress);
	}

	return 0;
}

//& purpose:  To check set/get subnet mask
//& type : auto
/**
* @testcase 			ITc_connection_profile_set_get_subnet_mask_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check set/get subnet mask
* @scenario				Call API to set subnet mask\n
*						Call API to get subnet mask
* @apicovered			connection_profile_set_subnet_mask, connection_profile_get_subnet_mask
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_set_get_subnet_mask_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_set_get_subnet_mask_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = -1, nEnumLoopCount;

	// Initializing test variable
	connection_address_family_e e_address_family;
	char* pszTestSubnetMask = NULL;
	char* pszFindSubnetMask = NULL;
	int arrConnectionAddressFamilyValues[] = {
		CONNECTION_ADDRESS_FAMILY_IPV4,  /**< IPV4 Address type */
		//CONNECTION_ADDRESS_FAMILY_IPV6  /**< IPV6 Address type */
	};
	int nConnectionFamilyCount = sizeof(arrConnectionAddressFamilyValues) / sizeof(arrConnectionAddressFamilyValues[0]);

	for ( nEnumLoopCount = 0; nEnumLoopCount < nConnectionFamilyCount; nEnumLoopCount++ )
	{
		e_address_family = arrConnectionAddressFamilyValues[nEnumLoopCount];
		if ( nEnumLoopCount == 0 )
		{
			pszTestSubnetMask = "255.255.255.0";
		}
		else
		{
			pszTestSubnetMask = "2002:ffff:ff00:0:0:0:0:0";
		}

		nRet = connection_profile_set_subnet_mask(g_hConnectionProfileHandleCellular,e_address_family, pszTestSubnetMask);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_profile_set_subnet_mask failed for address family = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetAddressFamily(e_address_family), ConnectionGetError(nRet));
			return 1;
		}

		nRet = connection_profile_get_subnet_mask(g_hConnectionProfileHandleCellular, e_address_family, &pszFindSubnetMask);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_profile_get_subnet_mask failed for address family = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetAddressFamily(e_address_family), ConnectionGetError(nRet));
			return 1;
		}

		if ( strcmp(pszFindSubnetMask, pszTestSubnetMask) != 0 )
		{
			FPRINTF("[Line : %d][%s] connection_profile_get_subnet_mask failed, mismatch in subnet mask{(set:get)::(%s:%s)}\\n", __LINE__, API_NAMESPACE, pszTestSubnetMask, pszFindSubnetMask);
			return 1;
		}

		FREE_MEMORY(pszFindSubnetMask);
	}

	pszTestSubnetMask = NULL;
	return 0;
}

//& purpose:  To check set/unset state change callback
//& type : auto
/**
* @testcase 			ITc_connection_profile_set_unset_state_changed_cb_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check set/get subnet mask
* @scenario				Call API to set state change callback for profile\n
* 						generate event that trigger callback\n
*						Call API to unset state change callback for profile\n
*						generate event that trigger callback
* @apicovered			connection_profile_set_state_changed_cb
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_set_unset_state_changed_cb_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionMMSError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_set_get_subnet_mask_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nTtimeoutId = 0;
	g_pMainLoop = g_main_loop_new(NULL, false);

	int nRet = connection_profile_set_state_changed_cb(g_hConnectionProfileHandleMMS, test_profile_state_changed_cb, NULL);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_set_state_changed_cb", ConnectionGetError(nRet));

	nRet = connection_open_profile(g_hConenctionHandle, g_hConnectionProfileHandleMMS, test_connection_opened_callback, NULL);
	PRINT_RESULT_CLEANUP(CONNECTION_ERROR_NONE, nRet, "connection_open_profile", ConnectionGetError(nRet), connection_profile_unset_state_changed_cb(g_hConnectionProfileHandleMMS));

	/* Wating test_profile_state_changed_cb() */
	nTtimeoutId = g_timeout_add(50000, Timeout_Function, g_pMainLoop);
	g_main_loop_run(g_pMainLoop);
	g_source_remove(nTtimeoutId);

	if ( g_bCallbackResult == false )
	{
		FPRINTF("[Line : %d][%s] After connection_profile_set_state_changed_cb, no response from register call back\\n", __LINE__, API_NAMESPACE);
		connection_close_profile(g_hConenctionHandle, g_hConnectionProfileHandleMMS, test_connection_closed_callback, NULL);
		connection_profile_unset_state_changed_cb(g_hConnectionProfileHandleMMS);
		return 1;
	}

	nRet = connection_profile_unset_state_changed_cb(g_hConnectionProfileHandleMMS);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_unset_state_changed_cb", ConnectionGetError(nRet));

	/* Wating test_connection_opened_callback() */
	nTtimeoutId = g_timeout_add(50000, Timeout_Function, g_pMainLoop);
	g_main_loop_run(g_pMainLoop);
	g_source_remove(nTtimeoutId);

	g_bCallbackResult = false;
	nRet = connection_close_profile(g_hConenctionHandle, g_hConnectionProfileHandleMMS, test_connection_closed_callback, NULL);
	PRINT_RESULT_CLEANUP(CONNECTION_ERROR_NONE, nRet, "connection_profile_unset_state_changed_cb", ConnectionGetError(nRet), connection_profile_unset_state_changed_cb(g_hConnectionProfileHandleMMS));

	/* Wating test_connection_closed_callback() */
	nTtimeoutId = g_timeout_add(50000, Timeout_Function, g_pMainLoop);
	g_main_loop_run(g_pMainLoop);
	g_source_remove(nTtimeoutId);

	if ( g_bCallbackResult == true )
	{
		FPRINTF("[Line : %d][%s] After connection_profile_unset_state_changed_cb, getting response from register call back\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose:  To check open/close connection profile
//& type : auto
/**
* @testcase 			ITc_connection_open_close_profile_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check open/close connection profile
* @scenario				Call API to open connection profile\n
* 						check response from callback\n
*						Call API to close connection profile\n
*						check response from callback
* @apicovered			connection_open_profile, connection_close_profile
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_open_close_profile_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_open_close_profile_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nTtimeoutId = 0;
	g_pMainLoop = g_main_loop_new(NULL, false);

	int nRet = connection_open_profile(g_hConenctionHandle, g_hConnectionProfileHandleCellular, test_connection_opened_callback, NULL);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_unset_state_changed_cb", ConnectionGetError(nRet));

	nTtimeoutId = g_timeout_add(50000, Timeout_Function, g_pMainLoop);
	g_main_loop_run(g_pMainLoop);
	g_source_remove(nTtimeoutId);

	if ( g_bOpenCallbackResult == false )
	{
		FPRINTF("[Line : %d][%s] After connection_open_profile, not getting response from register call back\\n", __LINE__, API_NAMESPACE);
		connection_close_profile(g_hConenctionHandle, g_hConnectionProfileHandleCellular, test_connection_closed_callback, NULL);
		return 1;
	}

	//if testcase getting fail in callback response
	g_bCloseCallbackResult = false;

	nRet = connection_close_profile(g_hConenctionHandle, g_hConnectionProfileHandleCellular, test_connection_closed_callback, NULL);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_close_profile", ConnectionGetError(nRet));

	nTtimeoutId = g_timeout_add(50000, Timeout_Function, g_pMainLoop);
	g_main_loop_run(g_pMainLoop);
	g_source_remove(nTtimeoutId);

	if ( g_bCloseCallbackResult == false )
	{
		FPRINTF("[Line : %d][%s] After connection_close_profile, getting response from register call back\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: To check refresh the profile information
//& type : auto
/**
* @testcase 			ITc_connection_profile_refresh_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check refresh the profile information
* @scenario				Call API to refresh connection profile
* @apicovered			connection_profile_refresh
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_refresh_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_refresh_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char* pszTestIPAddress = "192.168.128.11";
	int nRet = connection_profile_set_ip_address(g_hConnectionProfileHandleCellular, CONNECTION_ADDRESS_FAMILY_IPV4, pszTestIPAddress);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_set_ip_address", ConnectionGetError(nRet));

	nRet = connection_profile_refresh(g_hConnectionProfileHandleCellular);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_refresh", ConnectionGetError(nRet));

	return 0;
}

#if (defined(MOBILE) || defined(WEARABLE)  || defined(TIZENIOT)) //Starts MOBILE or WEARABLE or TIZENIOT
//& purpose: To check reset connection cellular profile
//& type : auto
/**
* @testcase 			ITc_connection_reset_profile_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check connection type
* @scenario				reset cellular profile
* @apicovered			connection_reset_profile
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_connection_reset_profile_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError == 1 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_reset_profile_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nEnumLoopCount = 0, nRet = -1, nTtimeoutId = 0;
	connection_reset_option_e eConnectionResetOption = -1;
	int nSimIndex = 0;		// Sim Index starts from 0 //

	int arrConnectionResetOptionSet [] = {
		CONNECTION_RESET_DEFAULT_PROFILE,
		CONNECTION_RESET_CLEAR_PROFILE
	};
	int nNumberOfResetOption = sizeof(arrConnectionResetOptionSet) / sizeof(arrConnectionResetOptionSet[0]);

	for ( nEnumLoopCount = 0; nEnumLoopCount < nNumberOfResetOption; nEnumLoopCount++ )
	{
		eConnectionResetOption = arrConnectionResetOptionSet[nEnumLoopCount];

		g_pMainLoop = g_main_loop_new(NULL, false);

		nRet = connection_reset_profile(g_hConenctionHandle, eConnectionResetOption, nSimIndex, test_connection_reset_profile_callback_cb, NULL);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_reset_profile failed for reset option = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ((nEnumLoopCount) == 0 ? "CONNECTION_RESET_DEFAULT_PROFILE" : "CONNECTION_RESET_CLEAR_PROFILE"), ConnectionGetError(nRet));
			return 1;
		}

		nTtimeoutId = g_timeout_add(50000, Timeout_Function, g_pMainLoop);
		g_main_loop_run(g_pMainLoop);
		g_source_remove(nTtimeoutId);
		if ( g_bCallbackResult == false )
		{
			FPRINTF("[Line : %d][%s] After connection_reset_profile, getting no response from registered call back\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	return 0;
}
#endif  // End MOBILE or WEARABLE or TIZENIOT

#ifdef TV	//Starts TV
//& purpose: To check reset connection cellular profile
//& type : auto
/**
* @testcase 			ITc_connection_reset_profile_p
* @since_tizen			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check connection type
* @scenario				reset cellular profile
* @apicovered			connection_reset_profile
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_connection_reset_profile_p(void)
{
#if 0
	START_TEST;

	if ( g_nConnectionPreconditionError == 1 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_reset_profile_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nEnumLoopCount = 0, nRet = -1, nTtimeoutId = 0;
	connection_reset_option_e eConnectionResetOption = -1;
	int nSimIndex = 0;		// Sim Index starts from 0 //

	int arrConnectionResetOptionSet [] = {
		CONNECTION_RESET_DEFAULT_PROFILE,
		CONNECTION_RESET_CLEAR_PROFILE
	};
	int nNumberOfResetOption = sizeof(arrConnectionResetOptionSet) / sizeof(arrConnectionResetOptionSet[0]);

	for ( nEnumLoopCount = 0; nEnumLoopCount < nNumberOfResetOption; nEnumLoopCount++ )
	{
		eConnectionResetOption = arrConnectionResetOptionSet[nEnumLoopCount];

		g_pMainLoop = g_main_loop_new(NULL, false);

		nRet = connection_reset_profile(g_hConenctionHandle, eConnectionResetOption, nSimIndex, test_connection_reset_profile_callback_cb, NULL);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line: %d][%s] connection_reset_profile failed for reset option = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ((nEnumLoopCount) == 0 ? "CONNECTION_RESET_DEFAULT_PROFILE" : "CONNECTION_RESET_CLEAR_PROFILE"), ConnectionGetError(nRet));
			return 1;
		}

		nTtimeoutId = g_timeout_add(30000, Timeout_Function, g_pMainLoop);
		g_main_loop_run(g_pMainLoop);
		g_source_remove(nTtimeoutId);
		if ( g_bCallbackResult == false )
		{
			FPRINTF("[Line: %d][%s] After connection_reset_profile, getting no response from registered call back\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
#endif
	return 0;
}
#endif  //TV	//End TV

//& purpose: To check add /remove connection profile
//& type : auto
/**
* @testcase 			ITc_connection_add_remove_profile_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check add /remove connection profile
* @scenario				Call API to add connection profile\n
*						Call API to remove connection profile
* @apicovered			connection_remove_profile, connection_add_profile
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_add_remove_profile_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_add_remove_profile_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	connection_profile_h hConnectionProfile = NULL;
	connection_profile_h hCloneConnectionProfile = NULL;
	char* pszProfileName = "testprofile";
	connection_profile_type_e eConnectionProfileType = CONNECTION_PROFILE_TYPE_CELLULAR;

	int nRet = connection_profile_create( eConnectionProfileType, pszProfileName, &hConnectionProfile);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_create", ConnectionGetError(nRet));

	nRet = connection_profile_set_cellular_service_type(hConnectionProfile, CONNECTION_CELLULAR_SERVICE_TYPE_INTERNET);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_set_cellular_service_type", ConnectionGetError(nRet));

	nRet = connection_add_profile(g_hConenctionHandle, hConnectionProfile);
	if ( nRet != CONNECTION_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] connection_add_profile failed, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
		return 1;
	}

	if ( ConnectionManager_get_celluar_profile_by_name(g_hConenctionHandle, pszProfileName, &hCloneConnectionProfile) == 0 )
	{
		FPRINTF("[Line : %d][%s] connection_add_profile failed to set profile on profile iterator in, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
		return 1;
	}

	if ( hCloneConnectionProfile == NULL )
	{
		FPRINTF("[Line : %d][%s] connection_add_profile failed to set profile on profile iterator in\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = connection_remove_profile(g_hConenctionHandle, hCloneConnectionProfile);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_remove_profile", ConnectionGetError(nRet));

	nRet = connection_profile_destroy(hCloneConnectionProfile);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_destroy", ConnectionGetError(nRet));

	nRet = connection_profile_destroy(hConnectionProfile);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_destroy", ConnectionGetError(nRet));

	return 0;
}
//& purpose:  To check get DHCP server address
//& type : auto
/**
* @testcase 			ITc_connection_profile_get_dhcp_server_address_p
* @since_tizen			4.0
* @author            	SRID(mandadi.mr)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @description			To check get DHCP address
* @scenario				Call API to get DHCP address
* @apicovered			connection_profile_get_dhcp_address
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_get_dhcp_server_address_p(void)
{
	START_TEST;

	if ( g_nConnectionPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] connection_profile_get_dhcp_server_address failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = -1;
	char* pszFindDHCPAddress = NULL;
	connection_address_family_e e_address_family;
	e_address_family = CONNECTION_ADDRESS_FAMILY_IPV4;

	nRet = connection_profile_get_dhcp_server_address(g_hConnectionProfileHandleCellular, e_address_family, &pszFindDHCPAddress);

	if ( nRet != CONNECTION_ERROR_NONE )
	{
		FREE_MEMORY(pszFindDHCPAddress);
		FPRINTF("[Line : %d][%s] connection_profile_get_dhcp_server_address failed for address family = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetAddressFamily(e_address_family), ConnectionGetError(nRet));

		return 1;
	}

	FREE_MEMORY(pszFindDHCPAddress);

	return 0;
}

//& purpose:  Gets the DHCP lease duration
//& type : auto
/**
* @testcase 			ITc_connection_profile_get_dhcp_lease_duration_p
* @since_tizen			4.0
* @author            	SRID(manmohan.k)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			To Gets the DHCP lease duration
* @scenario				Call API to get the DHCP lease duration
* @apicovered			connection_profile_get_dhcp_lease_duration
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_connection_profile_get_dhcp_lease_duration_p(void)
{
	START_TEST;

	int dhcp_lease_duration = 0;
	int nRet = connection_profile_get_dhcp_lease_duration(g_hConnectionProfileHandleCellular, CONNECTION_ADDRESS_FAMILY_IPV4, &dhcp_lease_duration);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_dhcp_lease_duration", ConnectionGetError(nRet));
	FPRINTF("[Line : %d][%s] connection_profile_get_dhcp_lease_duration return value=%d\\n", __LINE__, API_NAMESPACE, dhcp_lease_duration);

	nRet = connection_profile_get_dhcp_lease_duration(g_hConnectionProfileHandleMMS, CONNECTION_ADDRESS_FAMILY_IPV4, &dhcp_lease_duration);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_dhcp_lease_duration", ConnectionGetError(nRet));
	FPRINTF("[Line : %d][%s] connection_profile_get_dhcp_lease_duration return value=%d\\n", __LINE__, API_NAMESPACE, dhcp_lease_duration);

	return 0;
}

//& purpose:  To get profile connection internet state
//& type : auto
/**
* @testcase 			ITc_connection_profile_get_internet_state_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @description			To get profile connection internet state
* @apicovered			connection_profile_get_internet_state
* @passcase			When connection_profile_get_internet_state return CONNECTION_ERROR_NONE
* @failcase			When connection_profile_get_internet_state not return CONNECTION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_connection_profile_get_internet_state_p(void)
{
	START_TEST;

	connection_internet_state_e eConectionState = -1;
	int nRet = connection_profile_get_internet_state(g_hConnectionProfileHandleCellular, &eConectionState);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_internet_state", ConnectionGetError(nRet));

	if(eConectionState > CONNECTION_INTERNET_STATE_ONLINE || eConectionState < CONNECTION_INTERNET_STATE_OFFLINE)
	{
		FPRINTF("[Line : %d][%s] connection state is invalid=%d\\n", __LINE__, API_NAMESPACE, eConectionState);
		return 1;
	}
	return 0;
}
