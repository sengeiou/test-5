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

static GMainLoop *g_pCallbackLoop;
int g_nErrorCount1, g_nErrorCount2;
int g_nPreconditionError = 0;
connection_h g_hConnection;
connection_profile_h g_hConnectionProfileCellular;
char* g_pszCellularProfileName = "CellularConnectionProfile";
bool g_bConnectionCallbackResult = false;
bool g_bConnectionOpenCallbackResult = false;
bool g_bConnectionCloseCallbackResult = false;

bool g_bTelFeatureSupported = true;
bool g_bWifiFeatureSupported = true;
bool g_bBtFeatureSupported = true;
bool g_bEthernetFeatureSupported = true;

gboolean fn_WaitingCallbackResponse(gpointer data)
{
	g_main_loop_quit((GMainLoop *)data);
	return false;
}

void ConnectionInternetStateChangedCB(connection_internet_state_e state, void* user_data)
{
	FPRINTF("[Line : %d][%s]Inside ConnectionInternetStateChangedCB callback\n", __LINE__, API_NAMESPACE);
}
void test_network_state_changed_cb(connection_type_e state, void* user_data)
{
	FPRINTF("[Line : %d][%s]Inside test_network_state_changed_cb\\n", __LINE__, API_NAMESPACE);
	g_bConnectionCallbackResult = true;
	if (g_pCallbackLoop)
	{
		g_main_loop_quit(g_pCallbackLoop);
	}
}

void test_connection_opened_callback_cb(connection_error_e result, void* user_data)
{
	FPRINTF("[Line : %d][%s]Inside callback \"test_connection_opened_callback_cb\"\\n", __LINE__, API_NAMESPACE);
	g_bConnectionOpenCallbackResult = true;
	if (g_pCallbackLoop)
	{
		g_main_loop_quit(g_pCallbackLoop);
	}
}

void test_connection_closed_callback_cb(connection_error_e result, void* user_data)
{
	FPRINTF("[Line : %d][%s]Inside callback \"test_connection_closed_callback_cb\"\\n", __LINE__, API_NAMESPACE);
	g_bConnectionCloseCallbackResult = true;
	if (g_pCallbackLoop)
	{
		g_main_loop_quit(g_pCallbackLoop);
	}
}

void test_ip_address_changed_cb(const char* ipv4_address, const char* ipv6_address, void* user_data)
{
	FPRINTF("[Line : %d][%s]Inside callback \"test_ip_address_changed_cb\"\\n", __LINE__, API_NAMESPACE);
}

void test_proxy_address_changed_cb(const char* ipv4_address, const char* ipv6_address, void* user_data)
{
	FPRINTF("[Line : %d][%s]Inside callback \"test_proxy_address_changed_cb\"\\n", __LINE__, API_NAMESPACE);
}


bool test_connection_ipv6_address_callback(char *ipv6_address, void *user_data)
{
	FPRINTF("[Line : %d][%s]Inside callback \"test_connection_ipv6_address_callback\"\\n", __LINE__, API_NAMESPACE);
	return true;
}

void ITs_connection_startup(void)
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

	g_bTelFeatureSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE, API_NAMESPACE);
	g_bWifiFeatureSupported = TCTCheckSystemInfoFeatureSupported(WIFI_FEATURE, API_NAMESPACE);
	g_bBtFeatureSupported = TCTCheckSystemInfoFeatureSupported(TETHERING_BLUETOOTH_FEATURE, API_NAMESPACE);
	g_bEthernetFeatureSupported = TCTCheckSystemInfoFeatureSupported(ETHERNET_FEATURE, API_NAMESPACE);


	g_nErrorCount1 = 0;
	g_nErrorCount2 = 0;
	g_bConnectionCallbackResult = false;
	g_hConnectionProfileCellular = NULL;
	g_bConnectionOpenCallbackResult = false;
	g_bConnectionCloseCallbackResult = false;
	g_hConnection = NULL;

	int nRet = connection_create(&g_hConnection);

	if ( false == g_bTelFeatureSupported && false == g_bWifiFeatureSupported && false == g_bBtFeatureSupported && false == g_bEthernetFeatureSupported)
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

	if (( nRet != CONNECTION_ERROR_NONE ) ||(g_hConnection == NULL ))
	{
		g_nPreconditionError = 1;
		g_hConnection = NULL;
		return;
	}

	nRet = connection_get_current_profile(g_hConnection,  &g_hConnectionProfileCellular);
	if (( nRet != CONNECTION_ERROR_NONE ) || (g_hConnectionProfileCellular == NULL ))
	{
		g_nPreconditionError = 2;
		g_hConnectionProfileCellular = NULL;
		return;
	}

}

void ITs_connection_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Connection_p\\n", __LINE__, API_NAMESPACE);
#endif
	int nRet = 0;

	if ( g_nPreconditionError)
	{
		g_nPreconditionError = 0;
		return;
	}

	if ( g_nPreconditionError == 2 && g_bFeatureSupported == true )
	{
		if ( g_hConnectionProfileCellular != NULL )
		{
			nRet = connection_profile_destroy(g_hConnectionProfileCellular);
			if ( nRet != CONNECTION_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] connection_destroy failed on post condition error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			}
		}

		nRet = connection_destroy(g_hConnection);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_destroy failed on post condition error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
		}
		g_nPreconditionError = 0;
		return;
	}
}


/** @addtogroup itc-connection-testcases
*  @brief 		Integration testcases for module connection
*  @ingroup 	itc-connection
*  @{
*/

//& purpose: To check creates/destroy a handle for managing data connections
//& type : auto
/**
* @testcase 			ITc_connection_create_destroy_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check creates/destroy a handle for managing data connections
* @scenario				Call API to create a handle for managing data connections\n
*						Call API to destroy the handle
* @apicovered			connection_create, connection_destroy
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_connection_create_destroy_p(void)
{
	START_TEST;

	int nRet = -1;
	// Initializing test variable
	connection_h hConenction = NULL;

	nRet = connection_create(&hConenction);
	if ( nRet != CONNECTION_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] connection_create failed, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
		return 1;
	}
	if (hConenction == NULL )
	{
		FPRINTF("[Line : %d][%s] connection_create failed, returned connection handle :: NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = connection_destroy(hConenction);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_destroy", ConnectionGetError(nRet));

	return 0;
}

//& purpose: To check state of Bluetooth
//& type : auto
/**
* @testcase 			ITc_connection_get_bt_state_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check state of Bluetooth
* @scenario				Call API to get state of bluetooth
* @apicovered			connection_get_bt_state
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Bluetooth must be disabled
* @postcondition		None
*/
int ITc_connection_get_bt_state_p(void)
{
	START_TEST;

	FPRINTF("[Line : %d][%s]Starting test : %s\\n", __LINE__, API_NAMESPACE,__FUNCTION__);

	if ( g_nPreconditionError == 1 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_get_bt_state_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	connection_bt_state_e eFindBluetoothState  = -1;
	eFindBluetoothState  = -1;

	int nRet = connection_get_bt_state(g_hConnection, &eFindBluetoothState);
	if (! g_bBtFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] connection_get_bt_state API call returned mismatch %s error for unsupported bluetooth feature\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			g_nErrorCount1++;
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] connection_get_bt_state API call correctly returned %s error for unsupported bluetooth feature\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			return 0;
		}

	}

	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_get_bt_state", ConnectionGetError(nRet));
	if ( eFindBluetoothState == -1 )
	{
		FPRINTF("[Line: %d][%s] connection_get_bt_state failed, returned invalid bluetooth state : %d\\n", __LINE__, API_NAMESPACE, eFindBluetoothState);
		return 1;
	}
	return 0;
}

//& purpose: To check connection type
//& type : auto
/**
* @testcase 			ITc_connection_get_type_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check connection type
* @scenario				Call API to get connection type
* @apicovered			connection_get_type
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_connection_get_type_p(void)
{
	START_TEST;

	if ( g_nPreconditionError == 1 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_get_type_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	connection_type_e eFindConnectionType = -1;
	eFindConnectionType = -1;

	int nRet = connection_get_type(g_hConnection, &eFindConnectionType);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_get_type", ConnectionGetError(nRet));
	if ( eFindConnectionType == -1 )
	{
		return 1;
	}
	FPRINTF("[Line : %d][%s] connection_get_type, returned Connection Type :: %s \\n", __LINE__, API_NAMESPACE, ConnectionGetType(eFindConnectionType));

	return 0;
}

//& purpose: To check proxy address of the current connection
//& type : auto
/**
* @testcase 			ITc_connection_get_proxy_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check proxy address of the current connection
* @scenario				Call API to get proxy address
* @apicovered			connection_get_proxy
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_connection_get_proxy_p(void)
{
	START_TEST;

	if ( g_nPreconditionError == 1 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_get_proxy_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = -1, nEnumLoopCount = 0;
	connection_address_family_e eConnectionAddressFamily = -1;
	int arrConnectionAddressFamilyValues[] = {
		CONNECTION_ADDRESS_FAMILY_IPV4,  /**< IPV4 Address type */
		//CONNECTION_ADDRESS_FAMILY_IPV6   /**< IPV6 Address type */
	};
	int nConnectionFamilyCount = sizeof(arrConnectionAddressFamilyValues) / sizeof(arrConnectionAddressFamilyValues[0]);
	char* pszReceivedProxy = NULL;

	for ( nEnumLoopCount = 0; nEnumLoopCount < nConnectionFamilyCount; nEnumLoopCount++ )
	{
		eConnectionAddressFamily = arrConnectionAddressFamilyValues[nEnumLoopCount];

		nRet = connection_get_proxy(g_hConnection, eConnectionAddressFamily, &pszReceivedProxy);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_get_proxy failed for address family = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetAddressFamily(eConnectionAddressFamily), ConnectionGetError(nRet));
			return 1;
		}
		if ( pszReceivedProxy == NULL )
		{
			FPRINTF("[Line : %d][%s]  connection_get_proxy failed for address family = %s, returned proxy :: NULL", __LINE__, API_NAMESPACE, ConnectionGetAddressFamily(eConnectionAddressFamily));
			return 1;
		}

		FREE_MEMORY(pszReceivedProxy);
	}

	return 0;
}

//& purpose: To check IP address of the current connection.
//& type : auto
/**
* @testcase 			ITc_connection_get_ip_address_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			IP address of the current connection.
* @scenario				- call API to get IP address
* @apicovered			-connection_get_ip_address
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_connection_get_ip_address_p(void)
{
	START_TEST;

	if ( g_nPreconditionError == 1 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_get_ip_address_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = -1, nEnumLoopCount;
	connection_address_family_e eConnectionAddressFamily;

	int arrConnectionAddressFamilyValues[] = {
		CONNECTION_ADDRESS_FAMILY_IPV4,  /**< IPV4 Address type */
		//CONNECTION_ADDRESS_FAMILY_IPV6  /**< IPV6 Address type */
	};
	int nConnectionFamilyCount = sizeof(arrConnectionAddressFamilyValues) / sizeof(arrConnectionAddressFamilyValues[0]);
	char* pszReceivedIPAddress = NULL;

	for ( nEnumLoopCount = 0; nEnumLoopCount < nConnectionFamilyCount; nEnumLoopCount++ )
	{
		eConnectionAddressFamily = arrConnectionAddressFamilyValues[nEnumLoopCount];

		nRet = connection_get_ip_address(g_hConnection, eConnectionAddressFamily, &pszReceivedIPAddress);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_get_ip_address failed for address family = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetAddressFamily(eConnectionAddressFamily), ConnectionGetError(nRet));
			return 1;
		}
		if ( pszReceivedIPAddress == NULL )
		{
			FPRINTF("[Line : %d][%s] connection_get_ip_address failed for address family = %s, returned ip address :: NULL", __LINE__, API_NAMESPACE, ConnectionGetAddressFamily(eConnectionAddressFamily));
			return 1;
		}

		FREE_MEMORY(pszReceivedIPAddress);
	}

	return 0;
}

//& purpose: To check statistics information
//& type : auto
/**
* @testcase 			ITc_connection_get_statistics_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check statistics information
* @scenario				Call API to get statistics information
* @apicovered			connection_get_statistics
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_connection_get_statistics_p(void)
{
	START_TEST;

	if ( g_nPreconditionError == 1 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_get_statistics_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = -1, nEnumConnectionTypeLoop, nEnumConnectionStatisticsTypeLoop;
	connection_type_e eSetConnectionType;
	int arrConnectionType[] = {
		CONNECTION_TYPE_WIFI,  			/**< Wi-Fi type */
		CONNECTION_TYPE_CELLULAR,  			/**< Cellular type */
	};
	int nConnectionTypeCount = sizeof(arrConnectionType) / sizeof(arrConnectionType[0]);

	connection_statistics_type_e eSetStatisticsType;
	int arrConnectionStatisticsType[] = {
		CONNECTION_STATISTICS_TYPE_LAST_RECEIVED_DATA,  	 /**< Last received data */
		CONNECTION_STATISTICS_TYPE_LAST_SENT_DATA,  		 /**< Last sent data */
		CONNECTION_STATISTICS_TYPE_TOTAL_RECEIVED_DATA, 	 /**< Total received data */
		CONNECTION_STATISTICS_TYPE_TOTAL_SENT_DATA, 		 /**< Total sent data */
	};
	int nConnectionStatisticsTypeCount = sizeof(arrConnectionStatisticsType) / sizeof(arrConnectionStatisticsType[0]);

	long long lReceivedData = -1;
	for ( nEnumConnectionTypeLoop = 0; nEnumConnectionTypeLoop < nConnectionTypeCount; nEnumConnectionTypeLoop++ )
	{
		eSetConnectionType = arrConnectionType[nEnumConnectionTypeLoop];
		if ( eSetConnectionType == CONNECTION_TYPE_WIFI && g_bWifiFeatureSupported == false )
		{
			FPRINTF("[Line : %d][%s] Network wifi feature is not supported in target device\\n", __LINE__, API_NAMESPACE);
			continue;
		}
		if ( eSetConnectionType == CONNECTION_TYPE_CELLULAR && g_bTelFeatureSupported == false )
		{
			FPRINTF("[Line : %d][%s] Network telephony feature is not supported in target device\\n", __LINE__, API_NAMESPACE);
			continue;
		}

		for ( nEnumConnectionStatisticsTypeLoop = 0; nEnumConnectionStatisticsTypeLoop < nConnectionStatisticsTypeCount; nEnumConnectionStatisticsTypeLoop++ )
		{
			eSetStatisticsType = arrConnectionStatisticsType[nEnumConnectionStatisticsTypeLoop];

			nRet = connection_get_statistics(g_hConnection, eSetConnectionType, eSetStatisticsType, &lReceivedData);
			if ( nRet != CONNECTION_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] connection_get_statistics failed for connection type = %s and statistics type = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetType(eSetConnectionType), ConnectionGetStatisticTypeData(eSetStatisticsType), ConnectionGetError(nRet));
				return 1;
			}

			if ( lReceivedData == -1 )
			{
				FPRINTF("[Line : %d][%s] connection_get_statistics failed for connection type = %s and statistics type = %s, returned received data :: -1\\n", __LINE__, API_NAMESPACE, ConnectionGetType(eSetConnectionType), ConnectionGetStatisticTypeData(eSetStatisticsType));
				return 1;
			}

			lReceivedData = -1;
		}
	}

	return 0;
}

//& purpose: To check name of default profile
//& type : auto
/**
* @testcase 			ITc_connection_get_current_profile_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check name of default profile
* @scenario				Call API to get name of default profile
* @apicovered			connection_get_current_profile
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_get_current_profile_p(void)
{
	START_TEST;

	if ( g_nPreconditionError == 1 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_get_current_profile_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	connection_profile_h eFindConnectionProfile = NULL;
	int nRet = connection_get_current_profile(g_hConnection, &eFindConnectionProfile);

	if ( nRet == CONNECTION_ERROR_NO_CONNECTION ) {
		FPRINTF("[Line : %d][%s] ITc_connection_get_current_profile_p NO_CONNECTION\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_get_current_profile", ConnectionGetError(nRet));
	CHECK_HANDLE(eFindConnectionProfile, "connection_get_current_profile");

	return 0;
}

//& purpose: To check reset the statistics information
//& type : auto
/**
* @testcase 			ITc_connection_reset_statistics_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check reset the statistics information
* @scenario				Call API to reset the statistics information
* @apicovered			connection_reset_statistics
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_reset_statistics_p(void)
{
	START_TEST;

	if ( g_nPreconditionError == 1 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_reset_statistics_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = -1, nEnumConnectionTypeLoop, nEnumConnectionStatisticsTypeLoop;
	connection_type_e eConnectionType;
	int arrConnectionType[] = {
		CONNECTION_TYPE_WIFI,  				/**< Wi-Fi type */
		CONNECTION_TYPE_CELLULAR,	  		/**< Cellular type */
	};
	int nConnectionTypeCount = sizeof(arrConnectionType) / sizeof(arrConnectionType[0]);

	connection_statistics_type_e eStatisticsType;
	int arrConnectionStatisticsType[] = {
		CONNECTION_STATISTICS_TYPE_LAST_RECEIVED_DATA,	  	 /**< Last received data */
		CONNECTION_STATISTICS_TYPE_LAST_SENT_DATA,	  		 /**< Last sent data */
		CONNECTION_STATISTICS_TYPE_TOTAL_RECEIVED_DATA, 	 /**< Total received data */
		CONNECTION_STATISTICS_TYPE_TOTAL_SENT_DATA, 		 /**< Total sent data */
	};
	int nConnectionStatisticsTypeCount = sizeof(arrConnectionStatisticsType) / sizeof(arrConnectionStatisticsType[0]);

	for ( nEnumConnectionTypeLoop = 0; nEnumConnectionTypeLoop < nConnectionTypeCount; nEnumConnectionTypeLoop++ )
	{
		eConnectionType = arrConnectionType[nEnumConnectionTypeLoop];
		if ( eConnectionType == CONNECTION_TYPE_WIFI && g_bWifiFeatureSupported == false )
		{
			FPRINTF("[Line : %d][%s] Network wifi feature is not supported in target device\\n", __LINE__, API_NAMESPACE);
			continue;
		}
		if ( eConnectionType == CONNECTION_TYPE_CELLULAR && g_bTelFeatureSupported == false )
		{
			FPRINTF("[Line : %d][%s] Network telephony feature is not supported in target device\\n", __LINE__, API_NAMESPACE);
			continue;
		}

		for ( nEnumConnectionStatisticsTypeLoop = 0; nEnumConnectionStatisticsTypeLoop < nConnectionStatisticsTypeCount; nEnumConnectionStatisticsTypeLoop++ )
		{
			eStatisticsType = arrConnectionStatisticsType[nEnumConnectionStatisticsTypeLoop];

			nRet = connection_reset_statistics(g_hConnection ,eConnectionType, eStatisticsType);
			if ( nRet != CONNECTION_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] connection_reset_statistics failed for connection type = %s and statistic data type = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetType(eConnectionType), ConnectionGetStatisticTypeData(eStatisticsType), ConnectionGetError(nRet));
				return 1;
			}
		}
	}

	return 0;
}

//& purpose: To check iterator of the profiles
//& type : auto
/**
* @testcase 			ITc_connection_get_destroy_profile_iterator_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check iterator of the profiles
* @scenario				Call API to get iterator of the profile\n
* 						verify return value of API\n
*						Call API to destroy iterator of the profile\n
*						verify return value of api
* @apicovered			connection_get_profile_iterator, connection_destroy_profile_iterator
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_get_destroy_profile_iterator_p(void)
{
	START_TEST;

	if ( g_nPreconditionError == 1 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_get_destroy_profile_iterator_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = -1, nEnumLoopCount;
	connection_profile_iterator_h hConnectionProfileHandleIterator;
	connection_iterator_type_e eConnectionIteratortype;
	int arrConnectionIteratorTypeValues[] = {
		CONNECTION_ITERATOR_TYPE_REGISTERED,   /**< The iterator of registered profile  */
		CONNECTION_ITERATOR_TYPE_CONNECTED,  	/**< The iterator of connected profile  */
	};
	int nConnectionIteratorTypeCount = sizeof(arrConnectionIteratorTypeValues) / sizeof(arrConnectionIteratorTypeValues[0]);

	for ( nEnumLoopCount = 0; nEnumLoopCount < nConnectionIteratorTypeCount; nEnumLoopCount++ )
	{
		eConnectionIteratortype = arrConnectionIteratorTypeValues[nEnumLoopCount];

		nRet = connection_get_profile_iterator(g_hConnection, eConnectionIteratortype, &hConnectionProfileHandleIterator);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_get_profile_iterator failed for iterator type = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetIteratorType(eConnectionIteratortype), ConnectionGetError(nRet));
			return 1;
		}

		if ( hConnectionProfileHandleIterator == NULL )
		{
			FPRINTF("[Line : %d][%s] connection_get_profile_iterator failed for iterator type = %s, returned connection profile iterator :: NULL\\n", __LINE__, API_NAMESPACE, ConnectionGetIteratorType(eConnectionIteratortype));
			connection_destroy_profile_iterator(hConnectionProfileHandleIterator);
			return 1;
		}

		nRet = connection_destroy_profile_iterator(hConnectionProfileHandleIterator);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_get_profile_iterator failed for iterator type = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetIteratorType(eConnectionIteratortype), ConnectionGetError(nRet));
			return 1;
		}
	}

	return 0;
}

//& purpose: To check next element of profile iterator exists or not
//& type : auto
/**
* @testcase 			ITc_connection_profile_iterator_has_next_next_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check next element of profile iterator exists or not
* @scenario				Call API to get next element of profile iterator exists or not\n
* 						Call API to get next profile\n
*						verify return value of apis
* @apicovered			connection_profile_iterator_has_next, connection_profile_iterator_next
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_iterator_has_next_next_p(void)
{
	START_TEST;

	if ( g_nPreconditionError == 1 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_get_destroy_profile_iterator_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	connection_profile_iterator_h hConnectionProfileHandleIterator;
	connection_iterator_type_e eConnectionIteratortype = CONNECTION_ITERATOR_TYPE_REGISTERED;
	connection_profile_h hTempProfile;

	int nRet = connection_get_profile_iterator(g_hConnection, eConnectionIteratortype, &hConnectionProfileHandleIterator);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_get_profile_iterator", ConnectionGetError(nRet));

	bool bRetVal = connection_profile_iterator_has_next(hConnectionProfileHandleIterator);
	FPRINTF("[Line : %d][%s] connection_profile_iterator_has_next returned = %s\\n", __LINE__, API_NAMESPACE, bRetVal ? "true": "false");

	if ( bRetVal )
	{
		nRet = connection_profile_iterator_next(hConnectionProfileHandleIterator, &hTempProfile);
		PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_iterator_next", ConnectionGetError(nRet));
		CHECK_HANDLE(hTempProfile, "connection_profile_iterator_next");
	}
	else
	{
		nRet = connection_profile_iterator_next(hConnectionProfileHandleIterator, &hTempProfile);
		PRINT_RESULT(CONNECTION_ERROR_ITERATOR_END, nRet, "connection_profile_iterator_next", ConnectionGetError(nRet));
		if ( hTempProfile != NULL )
		{
			FPRINTF("[Line : %d][%s] connection_profile_iterator_has_next failed, returned next connection profile  :: not NULL", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	nRet = connection_destroy_profile_iterator(hConnectionProfileHandleIterator);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_destroy_profile_iterator", ConnectionGetError(nRet));

	return 0;
}

//& purpose: To check register/ unregister network type change callback
//& type : auto
/**
* @testcase 			ITc_connection_set_unset_type_changed_cb_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check next element of profile iterator exists or not
* @scenario				Call API to register network type changes callback and verify\n
* 						Call API to unregister network type changes callback and verify
* @apicovered			connection_set_type_changed_cb, connection_unset_type_changed_cb
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_connection_set_unset_type_changed_cb_p(void)
{
	START_TEST;

	if ( g_nPreconditionError == 1 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_set_unset_type_changed_cb_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = connection_set_type_changed_cb(g_hConnection, test_network_state_changed_cb, NULL);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_set_type_changed_cb", ConnectionGetError(nRet));

	nRet = connection_unset_type_changed_cb(g_hConnection);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_unset_type_changed_cb", ConnectionGetError(nRet));

	return 0;
}

//& purpose: To check register/ unregister callback on IP address change
//& type : auto
/**
* @testcase 			ITc_connection_set_unset_ip_address_changed_cb_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check register/ unregister callback on IP address change
* @scenario				Call API to register callback on IP address change\n
* 						Call API to unregister callback on IP address change
* @apicovered			connection_set_ip_address_changed_cb, connection_unset_ip_address_changed_cb
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_connection_set_unset_ip_address_changed_cb_p(void)
{
	START_TEST;

	if ( g_nPreconditionError == 1 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_set_unset_ip_address_changed_cb_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = connection_set_ip_address_changed_cb(g_hConnection, test_ip_address_changed_cb, NULL);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_set_ip_address_changed_cb", ConnectionGetError(nRet));

	nRet = connection_unset_ip_address_changed_cb(g_hConnection);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_unset_ip_address_changed_cb", ConnectionGetError(nRet));

	return 0;
}

//& purpose: To check register/ unregister callback on Proxy address change
//& type : auto
/**
* @testcase 			ITc_connection_set_unset_proxy_address_changed_cb_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check register/ unregister callback on Proxy address change
* @scenario				Call API to register callback on Proxy address change\n
* 						Call API to unregister callback on Proxy address change
* @apicovered			connection_set_proxy_address_changed_cb, connection_unset_proxy_address_changed_cb
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_connection_set_unset_proxy_address_changed_cb_p(void)
{
	START_TEST;

	if ( g_nPreconditionError == 1 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_set_unset_proxy_address_changed_cb_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = connection_set_proxy_address_changed_cb(g_hConnection, test_proxy_address_changed_cb, NULL);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_unset_ip_address_changed_cb", ConnectionGetError(nRet));

	nRet = connection_unset_proxy_address_changed_cb(g_hConnection);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_unset_ip_address_changed_cb", ConnectionGetError(nRet));

	return 0;
}



//& purpose: To get IPv6 addresses
//& type : auto
/**
* @testcase 		ITc_connection_foreach_ipv6_address_p
* @since_tizen		4.0
* @author            	SRID(maneesha.k)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @description		To get IPv6 addresses
* @scenario		Invoking connection_foreach_ipv6_address with valid parameter.
* @apicovered		ITc_connection_foreach_ipv6_address
* @passcase		When ITc_connection_foreach_ipv6_address returns CONNECTION_ERROR_NONE
* @failcase		When ITc_connection_foreach_ipv6_address does not return CONNECTION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_connection_foreach_ipv6_address_p(void)
{
	START_TEST;
	int nRet = CONNECTION_ERROR_NONE;

	if (g_bTelFeatureSupported)
	{
		nRet = connection_foreach_ipv6_address(g_hConnection, CONNECTION_TYPE_CELLULAR,test_connection_ipv6_address_callback, NULL);
		PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_foreach_ipv6_address(CONNECTION_TYPE_CELLULAR)", ConnectionGetError(nRet));
	}
	else if (g_bWifiFeatureSupported)
	{
		nRet = connection_foreach_ipv6_address(g_hConnection, CONNECTION_TYPE_WIFI,test_connection_ipv6_address_callback, NULL);
		PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_foreach_ipv6_address(CONNECTION_TYPE_WIFI)", ConnectionGetError(nRet));
	}
	else if (g_bEthernetFeatureSupported)
	{
		nRet = connection_foreach_ipv6_address(g_hConnection, CONNECTION_TYPE_ETHERNET,test_connection_ipv6_address_callback, NULL);
		PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_foreach_ipv6_address(CONNECTION_TYPE_ETHERNET)", ConnectionGetError(nRet));
	}
	else
	{
		nRet = connection_foreach_ipv6_address(g_hConnection, CONNECTION_TYPE_WIFI,test_connection_ipv6_address_callback, NULL);
		PRINT_RESULT(CONNECTION_ERROR_NOT_SUPPORTED, nRet, "connection_foreach_ipv6_address(CONNECTION_TYPE_WIFI)", ConnectionGetError(nRet));
	}

    return 0;
}

//& purpose: To check whether network state is connected
// also if the connection type is cellular
//& type : auto
/**
* @testcase                     ITc_connection_is_metered_network_p
* @since_tizen                  4.0
* @author                               SRID(j.abhishek)
* @reviewer                             SRID(maneesha.k)
* @type                                 auto
* @description                  connection_is_metered_network should pass with valid parameter.
* @scenario
*				Get State from connection_is_metered_network API.
*				Get connection type using API connection_get_type.
* @apicovered                   connection_is_metered_network
* @passcase                             When APIs return CONNECTION_ERROR_NONE
* @failcase                             When APIs not return CONNECTION_ERROR_NONE
* @precondition                 None
* @postcondition                None
*/

int ITc_connection_is_metered_network_p(void)
{
        START_TEST;

        if (g_nPreconditionError == 1)
        {
                FPRINTF("[Line: %d][%s] ITc_connection_is_metered_network_p failed on precondition\\n", __LINE__, API_NAMESPACE);
                return 1;
        }

	int nRet = -1, nErr;
	bool bState = false;
	connection_type_e eGetConnectionType;

	nRet = connection_is_metered_network(g_hConnection, &bState);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_is_metered_network", ConnectionGetError(nRet));

	nErr = connection_get_type(g_hConnection, &eGetConnectionType);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nErr, "connection_get_type", ConnectionGetError(nErr));

	if(bState)
	{
		if (CONNECTION_TYPE_CELLULAR != eGetConnectionType)
		{
			FPRINTF("[Line : %d][%s]connection_get_type returned [%d] but expected type is CONNECTION_TYPE_CELLULAR\\n", __LINE__, API_NAMESPACE, eGetConnectionType);
			return 1;
		}
	}

	if(eGetConnectionType != CONNECTION_TYPE_WIFI &&
	eGetConnectionType != CONNECTION_TYPE_CELLULAR &&
	eGetConnectionType != CONNECTION_TYPE_ETHERNET &&
	eGetConnectionType != CONNECTION_TYPE_BT &&
	eGetConnectionType != CONNECTION_TYPE_DISCONNECTED &&
	eGetConnectionType != CONNECTION_TYPE_NET_PROXY)
	{
		FPRINTF("[Line : %d][%s] CONNECTION_ERROR_NOT_SUPPORTED in target device\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

        return 0;
}

//& purpose: To check whether internet state changed
//& type : auto
/**
* @testcase                     ITc_connection_set_unset_internet_state_changed_cb_p
* @since_tizen                  5.5
* @author                       SRID(manoj.g2)
* @reviewer                     SRID(shobhit.v)
* @description                  To check for internet state changed callback .
* @apicovered			connection_set_internet_state_changed_cb, connection_unset_internet_state_changed_cb
* @passcase                     When connection_set_internet_state_changed_cb, connection_unset_internet_state_changed_cb return CONNECTION_ERROR_NONE
* @failcase                     When connection_set_internet_state_changed_cb, connection_unset_internet_state_changed_cb not return CONNECTION_ERROR_NONE
* @precondition                 None
* @postcondition                None
*/

int ITc_connection_set_unset_internet_state_changed_cb_p(void)
{
        START_TEST;

        if (g_nPreconditionError == 1)
        {
                FPRINTF("[Line: %d][%s] ITc_connection_set_unset_internet_state_changed_cb_p failed\\n", __LINE__, API_NAMESPACE);
                return 1;
        }

	int nRet = -1;

	nRet = connection_set_internet_state_changed_cb(g_hConnection, ConnectionInternetStateChangedCB, NULL);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_set_internet_state_changed_cb", ConnectionGetError(nRet));

	nRet = connection_unset_internet_state_changed_cb(g_hConnection);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_unset_internet_state_changed_cb", ConnectionGetError(nRet));

        return 0;
}
/** @} */
/** @} */
