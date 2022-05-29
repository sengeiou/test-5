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
int g_nConnectionEthernetPreconditionError = 0;
connection_h g_hConenctionHandleEth;
bool bEthFeatureSupported = false;


void ITs_connection_ethernet_profile_startup(void)
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

	bool bTelFeatureSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE, API_NAMESPACE);
	bool bWifiFeatureSupported = TCTCheckSystemInfoFeatureSupported(WIFI_FEATURE, API_NAMESPACE);
	bool bBtFeatureSupported = TCTCheckSystemInfoFeatureSupported(TETHERING_BLUETOOTH_FEATURE, API_NAMESPACE);
	bEthFeatureSupported = TCTCheckSystemInfoFeatureSupported(ETHERNET_FEATURE, API_NAMESPACE);

	g_nConnectionEthernetPreconditionError = 0;
	g_hConenctionHandleEth = NULL;

	int nRet = connection_create(&g_hConenctionHandleEth);

	if ( false == bTelFeatureSupported && false == bWifiFeatureSupported && false == bBtFeatureSupported && false == bEthFeatureSupported)
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

	if ( (nRet != CONNECTION_ERROR_NONE ) || (g_hConenctionHandleEth == NULL) )
	{
		FPRINTF("[Line: %d][%s] connection_create fail, returned error : %s or returned connection handle :: null\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet) );
		g_nConnectionEthernetPreconditionError = 1;
		g_hConenctionHandleEth = NULL;
		return;
	}
}

void ITs_connection_ethernet_profile_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_Connection_p\\n", __LINE__, API_NAMESPACE);
#endif

	// Null initialization of pointer
	int nRet = 0;

	if ( !g_nConnectionEthernetPreconditionError && (g_hConenctionHandleEth != NULL) )
	{
		nRet = connection_destroy(g_hConenctionHandleEth);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line: %d][%s] connection_destroy failed on post condition error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
		}
	}

	g_nConnectionEthernetPreconditionError = 0;
	g_hConenctionHandleEth = NULL;
}

static void test_connection_ethernet_cable_state_changed_cb( connection_ethernet_cable_state_e state, void* user_data){
	FPRINTF("[Line: %d][%s]Inside callback \"test_connection_ethernet_cable_state_changed_cb\"\\n", __LINE__, API_NAMESPACE);
}


/** @addtogroup itc-connection-wifi-profile-testcases
*  @brief 		Integration testcases for module connection-wifi-profile
*  @ingroup 	itc-connection-wifi-profile
*  @{
*/

//& purpose: To check set and unset callback for ethernet cable change event
//& type : auto
/**
* @testcase 			ITc_connection_set_unset_ethernet_cable_state_changed_cb_p
* @since_tizen			4.0
* @author				SRID(maneesha.k)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			check set and unset callback for ethernet cable change event
* @scenario				call api to set callback for cable event
* 						call api to unset callback for cable event
* @apicovered			connection_set_ethernet_cable_state_changed_cb, connection_unset_ethernet_cable_state_chaged_cb
* @passcase				When connection_set_ethernet_cable_state_changed_cb, connection_unset_ethernet_cable_state_chaged_cb return CONNECTION_ERROR_NONE
* @failcase				When connection_set_ethernet_cable_state_changed_cb, connection_unset_ethernet_cable_state_chaged_cb don't return CONNECTION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_connection_set_unset_ethernet_cable_state_changed_cb_p(void)
{
	START_TEST;

	if ( g_nConnectionEthernetPreconditionError > 0 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_set_unset_ethernet_cable_state_changed_cb_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = connection_set_ethernet_cable_state_changed_cb (g_hConenctionHandleEth, test_connection_ethernet_cable_state_changed_cb, NULL);

	if ( bEthFeatureSupported )
	{
		PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_set_ethernet_cable_state_changed_cb", ConnectionGetError(nRet));
	}
	else
	{
		PRINT_RESULT(CONNECTION_ERROR_NOT_SUPPORTED, nRet, "connection_set_ethernet_cable_state_changed_cb", ConnectionGetError(nRet));
	}

	nRet = connection_unset_ethernet_cable_state_chaged_cb (g_hConenctionHandleEth);

	if ( bEthFeatureSupported )
	{
		PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_unset_ethernet_cable_state_chaged_cb", ConnectionGetError(nRet));
	}
	else
	{
		PRINT_RESULT(CONNECTION_ERROR_NOT_SUPPORTED, nRet, "connection_unset_ethernet_cable_state_chaged_cb", ConnectionGetError(nRet));
	}

	return 0;
}

//& purpose: To check ethernet connection state
//& type : auto
/**
* @testcase 			ITc_connection_get_ethernet_cable_state_p
* @since_tizen			2.4
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check ethernet cable state
* @scenario				Call API to get ethernet state
* @apicovered			connection_get_ethernet_cable_state
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_connection_get_ethernet_cable_state_p(void)
{
	START_TEST;

	if ( g_nConnectionEthernetPreconditionError > 0 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_get_ethernet_cable_state_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	connection_ethernet_cable_state_e e_ethernet_con_state = -1;
	int nRet = connection_get_ethernet_cable_state(g_hConenctionHandleEth, &e_ethernet_con_state);
	if ( bEthFeatureSupported )
	{
		PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_get_ethernet_cable_state", ConnectionGetError(nRet));
		if ( e_ethernet_con_state == -1 )
		{
			FPRINTF("[Line: %d][%s] ITc_connection_get_ethernet_cable_state_p failed, returned connection state : %s\\n", __LINE__, API_NAMESPACE, (e_ethernet_con_state == CONNECTION_ETHERNET_CABLE_DETACHED ? "CONNECTION_ETHERNET_CABLE_DETACHED" : "CONNECTION_ETHERNET_CABLE_ATTACHED"));
			return 1;
		}
	}
	else
	{
		PRINT_RESULT(CONNECTION_ERROR_NOT_SUPPORTED, nRet, "connection_get_ethernet_cable_state", ConnectionGetError(nRet));
	}


	return 0;
}

//& purpose: To check state of ethernet
//& type : auto
/**
* @testcase 			ITc_connection_get_ethernet_state_p
* @since_tizen			2.4
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check state of ethernet
* @scenario				Call API to get state of ethernet
* @apicovered			connection_get_ethernet_state
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			None.
* @postcondition		None
*/
int ITc_connection_get_ethernet_state_p(void)
{
	START_TEST;

	if ( g_nConnectionEthernetPreconditionError == 1 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_get_ethernet_state_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	connection_ethernet_state_e eFindEthState = -1;
	int nRet = connection_get_ethernet_state(g_hConenctionHandleEth, &eFindEthState);
	if ( bEthFeatureSupported )
	{
		PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_get_ethernet_state", ConnectionGetError(nRet));
		if ( eFindEthState == -1 )
		{
			FPRINTF("[Line: %d][%s] connection_get_ethernet_state failed, returned invalid ethernet state\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	else
	{
		PRINT_RESULT(CONNECTION_ERROR_NOT_SUPPORTED, nRet, "connection_get_ethernet_state", ConnectionGetError(nRet));
	}

	return 0;
}

//& purpose: To check MAC address for wifi or ethernet connection type
//& type : auto
/**
* @testcase 			ITc_connection_get_mac_address_p
* @since_tizen			2.4
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To check MAC address
* @scenario				Call API to get MAC address
* @apicovered			connection_get_type, connection_get_mac_address
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			None.
* @postcondition		None
*/
int ITc_connection_get_mac_address_p(void)
{
	START_TEST;

	if ( g_nConnectionEthernetPreconditionError == 1 )
	{
		FPRINTF("[Line: %d][%s] ITc_connection_get_mac_address_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	connection_type_e e_con_type = -1;
	char* pstr_mac_address = NULL;

	int nRet = connection_get_type(g_hConenctionHandleEth, &e_con_type);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_get_type", ConnectionGetError(nRet));

	if ( e_con_type == -1 )
	{
		FPRINTF("[Line: %d][%s] connection_get_type, returned Connection Type :: %s\\n", __LINE__, API_NAMESPACE, ConnectionGetType(e_con_type));
		return 1;
	}

	if ( (e_con_type == CONNECTION_TYPE_WIFI) || (e_con_type == CONNECTION_TYPE_ETHERNET) )
	{
		nRet = connection_get_mac_address(g_hConenctionHandleEth, e_con_type, &pstr_mac_address);
		PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_get_mac_address", ConnectionGetError(nRet));
		CHECK_VALUE_STRING(pstr_mac_address, "connection_get_mac_address");
#ifdef TV	//Starts TV
		if ( pstr_mac_address != NULL )
		{
			free(pstr_mac_address);
			pstr_mac_address = NULL;
		}
#endif  //TV	//End TV
	}
	else
	{
		FPRINTF("[Line: %d][%s] ITc_connection_get_mac_address_p connection type (wifi /ethernet) required to check mac address\\n", __LINE__, API_NAMESPACE);
	}

	return 0;
}
/** @} */
/** @} */
