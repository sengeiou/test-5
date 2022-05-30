//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-wifi-manager-common.h"

//& set: WifiManager

/** @addtogroup itc-wifi-manager
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_wifi_manager_ap_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_wifi_manager_ap_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	g_bIsFeatureMismatched = false;
	g_bWifiManagerCreation = false;
	g_bFeatureWifi = TCTCheckSystemInfoFeatureSupported(FEATURE_WIFI, API_NAMESPACE);

	int nRet = wifi_manager_initialize(&g_hWifi);
	if ( !g_bFeatureWifi)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] wifi_manager_initialize failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s (%d)\\n", __FILE__, __LINE__, WifiManagerGetError(nRet), nRet);
			dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] wifi_manager_initialize failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s (%d)", __FILE__, __LINE__, WifiManagerGetError(nRet), nRet);
			g_bIsFeatureMismatched = true;
			return;
		}

		FPRINTF("[%s:%d] wifi_manager_initialize is unsupported\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] wifi_manager_initialize is unsupported\\n", __FILE__, __LINE__);
		g_bIsFeatureMismatched = false;
	}
	else if ( nRet != WIFI_MANAGER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] wifi_manager_initialize failed, error returned = %s (%d)\\n", __FILE__, __LINE__, WifiManagerGetError(nRet), nRet);
		dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] wifi_manager_initialize failed, error returned = %s (%d)", __FILE__, __LINE__, WifiManagerGetError(nRet), nRet);
		g_bWifiManagerCreation = false;
	}
	else
	{
		g_bWifiManagerCreation = true;
		nRet = wifi_manager_ap_create(g_hWifi, WIFI_AP_NAME, &g_hWifiAP);
		if ( nRet != WIFI_MANAGER_ERROR_NONE )
		{
			FPRINTF("[%s:%d] wifi_manager_ap_create failed, error returned = %s (%d)\\n", __FILE__, __LINE__, WifiManagerGetError(nRet), nRet);
			dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] wifi_manager_ap_create failed, error returned = %s (%d)", __FILE__, __LINE__, WifiManagerGetError(nRet), nRet);
			g_bWifiManagerCreation = false;
		}
		if(g_hWifiAP == NULL)
		{
			FPRINTF("[%s:%d] wifi_manager_ap_create handle is NULL\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] wifi_manager_ap_create handle is NULLn", __FILE__, __LINE__);
			g_bWifiManagerCreation = false;
		}
	}

	return;
}


/**
 * @function 		ITs_wifi_manager_ap_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_wifi_manager_ap_cleanup(void)
{
	int nRet = WIFI_MANAGER_ERROR_NONE;

	if (g_hWifiAP) {
		nRet = wifi_manager_ap_destroy(g_hWifiAP);
		FPRINTF("[%s:%d] wifi_manager_ap_destroy\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT","[%s:%d] wifi_manager_ap_destroy", __FILE__, __LINE__);
		PRINT_RESULT_NORETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_destroy", WifiManagerGetError(nRet));
	}

	nRet = wifi_manager_deinitialize(g_hWifi);
	if(nRet !=0)
	{
		FPRINTF("[%s:%d] wifi_manager_deinitialize failed\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] wifi_manager_deinitialize failed", __FILE__, __LINE__);
	}

	return;
}

//& purpose: Creates/destroy the access point handle.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_create_destroy_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Creates/destroy the access point handle.
* @apicovered			wifi_manager_ap_create, wifi_manager_ap_destroy
* @passcase				When  wifi_manager_ap_create, wifi_manager_ap_destroy API returns 0
* @failcase				If  wifi_manager_ap_create, wifi_manager_ap_destroy returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_create_destroy_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_ap_h hAp;

	//Target API
	int nRet =  wifi_manager_ap_create(g_hWifi, WIFI_AP_NAME, &hAp);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_create", WifiManagerGetError(nRet));

	//Target API
	nRet = wifi_manager_ap_destroy(hAp);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_destroy", WifiManagerGetError(nRet));

	return 0;
}

//& purpose: Creates the hidden access point handle
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_hidden_create_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Creates the hidden access point handle
* @apicovered			wifi_manager_ap_hidden_create, wifi_manager_ap_destroy
* @passcase				When  wifi_manager_ap_hidden_create, wifi_manager_ap_destroy API returns 0
* @failcase				If  wifi_manager_ap_hidden_create, wifi_manager_ap_destroy returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_hidden_create_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_ap_h hAp;

	//Target API
	int nRet =  wifi_manager_ap_hidden_create(g_hWifi, WIFI_AP_NAME, &hAp);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_hidden_create", WifiManagerGetError(nRet));

	nRet = wifi_manager_ap_destroy(hAp);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_destroy", WifiManagerGetError(nRet));

	return 0;
}

//& purpose: Clones the access point handle.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_clone_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Clones the access point handle.
* @apicovered			wifi_manager_ap_clone, wifi_manager_ap_destroy
* @passcase				When  wifi_manager_ap_clone, wifi_manager_ap_destroy API returns 0
* @failcase				If wifi_manager_ap_clone, wifi_manager_ap_destroy returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_clone_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_ap_h hClonedAp;

	//Target API
	int nRet =  wifi_manager_ap_clone(&hClonedAp, g_hWifiAP);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_clone", WifiManagerGetError(nRet));

	nRet = wifi_manager_ap_destroy(hClonedAp);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_destroy", WifiManagerGetError(nRet));

	return 0;
}

//& purpose: Verify wifi_manager_ap_get_essid by passing invalid parameters(ap,essid)
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_get_essid_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Verify wifi_manager_ap_get_essid by passing invalid parameters(ap,essid)
* @apicovered			wifi_manager_ap_get_essid
* @passcase				When  wifi_manager_ap_get_essid API returns 0
* @failcase				If wifi_manager_ap_get_essid returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_get_essid_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *essid = NULL;

	//Target API
	int nRet =  wifi_manager_ap_get_essid(g_hWifiAP, &essid);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_essid", WifiManagerGetError(nRet));

	if(essid == NULL)
	{
		FPRINTF("[%s:%d] wifi_manager_ap_get_essid returned value in essid is not set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_ap_get_essid returned value in essid is not set!!", __FILE__, __LINE__);
		return 1;
	}
	FREE_MEMORY(essid);

	return 0;
}

//& purpose: Gets BSSID (Basic Service Set Identifier).
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_get_bssid_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Gets BSSID (Basic Service Set Identifier).
* @apicovered			wifi_manager_ap_get_bssid
* @passcase				When  wifi_manager_ap_get_bssid API returns 0
* @failcase				If wifi_manager_ap_get_bssid returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_get_bssid_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *bssid = NULL;

	//Target API
	int nRet =  wifi_manager_ap_get_bssid(g_hWifiAP, &bssid);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_bssid", WifiManagerGetError(nRet));

	if(bssid == NULL)
	{
		FPRINTF("[%s:%d] wifi_manager_ap_get_bssid returned value in bssid is not set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_ap_get_bssid returned value in bssid is not set!!", __FILE__, __LINE__);
		return 1;
	}
	FREE_MEMORY(bssid);

	return 0;
}

//& purpose: Gets the RSSI.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_get_rssi_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Gets the RSSI.
* @apicovered			wifi_manager_ap_get_rssi
* @passcase				When  wifi_manager_ap_get_rssi API returns 0
* @failcase				If wifi_manager_ap_get_rssi returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_get_rssi_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	int nRssi = -1;

	//Target API
	int nRet =  wifi_manager_ap_get_rssi(g_hWifiAP, &nRssi);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_rssi", WifiManagerGetError(nRet));

	if(nRssi == -1)
	{
		FPRINTF("[%s:%d] wifi_manager_ap_get_rssi returned value in nRssi is not set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_ap_get_rssi returned value in nRssi is not set!!", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

//& purpose: Gets the RSSI LEVEL.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_get_rssi_level_p
* @since				4.0
* @author				SRID(s.bhadula)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @scenario				Gets the RSSI LEVEL.
* @apicovered				wifi_manager_ap_get_rssi_level
* @passcase				When  wifi_manager_ap_get_rssi_level API returns 0
* @failcase				If wifi_manager_ap_get_rssi_level returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_get_rssi_level_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_rssi_level_e rssi_level;

	//Target API
	int nRet =  wifi_manager_ap_get_rssi_level(g_hWifiAP, &rssi_level);

	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_get_rssi", WifiManagerGetError(nRet));

	if( (rssi_level < WIFI_MANAGER_RSSI_LEVEL_0) || (rssi_level > WIFI_MANAGER_RSSI_LEVEL_4) )
	{
		FPRINTF("[%s:%d] wifi_manager_ap_get_rssi_level returned value is not within range of wifi_manager_rssi_level_e enum, value: %d!!\\n", __FILE__, __LINE__, rssi_level);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_ap_get_rssi_level returned value is not within range of wifi_manager_rssi_level_e enum, value: %d!!", __FILE__, __LINE__, rssi_level);
		return 1;
	}

	return 0;
}

//& purpose: Gets the frequency band (MHz).
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_get_frequency_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Gets the frequency band (MHz).
* @apicovered			wifi_manager_ap_get_frequency
* @passcase				When  wifi_manager_ap_get_frequency API returns 0
* @failcase				If wifi_manager_ap_get_frequency returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_get_frequency_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	int nFrequency = -1;

	//Target API
	int nRet =  wifi_manager_ap_get_frequency(g_hWifiAP, &nFrequency);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_frequency", WifiManagerGetError(nRet));

	if(nFrequency == -1)
	{
		FPRINTF("[%s:%d] wifi_manager_ap_get_frequency returned value in nFrequency is not set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_ap_get_frequency returned value in nFrequency is not set!!", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

//& purpose: Gets the max speed (Mbps)
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_get_max_speed_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Gets the max speed (Mbps)
* @apicovered			wifi_manager_ap_get_max_speed
* @passcase				When  wifi_manager_ap_get_max_speed API returns 0
* @failcase				If wifi_manager_ap_get_max_speed returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_get_max_speed_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	int nSpeed = -1;

	//Target API
	int nRet =  wifi_manager_ap_get_max_speed(g_hWifiAP, &nSpeed);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_max_speed", WifiManagerGetError(nRet));

	if(nSpeed == -1)
	{
		FPRINTF("[%s:%d] wifi_manager_ap_get_max_speed returned value in nSpeed is not set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_ap_get_max_speed returned value in nSpeed is not set!!", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

//& purpose: Checks whether the access point is favorite or not.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_is_favorite_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Checks whether the access point is favorite or not.
* @apicovered			wifi_manager_ap_is_favorite
* @passcase				When  wifi_manager_ap_is_favorite API returns 0
* @failcase				If wifi_manager_ap_is_favorite returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_is_favorite_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	bool bFavorite = false;

	//Target API
	int nRet =  wifi_manager_ap_is_favorite(g_hWifiAP, &bFavorite);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_is_favorite", WifiManagerGetError(nRet));

	return 0;
}

//& purpose: Checks whether the access point is passpoint or not.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_is_passpoint_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Checks whether the access point is passpoint or not.
* @apicovered			wifi_manager_ap_is_passpoint
* @passcase				When  wifi_manager_ap_is_passpoint API returns 0
* @failcase				If wifi_manager_ap_is_passpoint returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_is_passpoint_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	bool bPasspoint = false;

	//Target API
	int nRet =  wifi_manager_ap_is_passpoint(g_hWifiAP, &bPasspoint);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_is_passpoint", WifiManagerGetError(nRet));

	return 0;
}

//& purpose: Gets the connection state.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_get_connection_state_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Gets the connection state.
* @apicovered			wifi_manager_ap_get_connection_state
* @passcase				When  wifi_manager_ap_get_connection_state API returns 0
* @failcase				If wifi_manager_ap_get_connection_state returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_get_connection_state_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_connection_state_e eState;

	//Target API
	int nRet =  wifi_manager_ap_get_connection_state(g_hWifiAP, &eState);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_connection_state", WifiManagerGetError(nRet));

	return 0;
}

//& purpose: Gets the config type of IP
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_get_ip_config_type_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Gets the config type of IP
* @apicovered			wifi_manager_ap_get_ip_config_type
* @passcase				When  wifi_manager_ap_get_ip_config_type API returns 0
* @failcase				If wifi_manager_ap_get_ip_config_type returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_get_ip_config_type_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_ip_config_type_e eType;

	//Target API
	int nRet =  wifi_manager_ap_get_ip_config_type(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &eType);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_ip_config_type", WifiManagerGetError(nRet));

	return 0;
}

//& purpose: Sets the config type of IP.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_set_ip_config_type_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets the config type of IP.
* @apicovered			wifi_manager_ap_set_ip_config_type
* @passcase				When  wifi_manager_ap_set_ip_config_type API returns 0
* @failcase				If wifi_manager_ap_set_ip_config_type returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_set_ip_config_type_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	//Target API
	int nRet =  wifi_manager_ap_set_ip_config_type(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, WIFI_MANAGER_IP_CONFIG_TYPE_STATIC);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_ip_config_type", WifiManagerGetError(nRet));

	return 0;
}

//& purpose: Sets/Gets the IP address. the config type of IP.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_set_get_ip_address_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets the IP address. the config type of IP.
* @apicovered			wifi_manager_ap_set_ip_address, wifi_manager_ap_get_ip_address
* @passcase				When  wifi_manager_ap_set_ip_address, wifi_manager_ap_get_ip_address API returns 0
* @failcase				If wifi_manager_ap_set_ip_address/wifi_manager_ap_get_ip_address returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_set_get_ip_address_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *pIpAddr = NULL;
	char *pSetIP = "192.168.11.1";
	//Target API
	int nRet = wifi_manager_ap_set_ip_address(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, pSetIP);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_ip_address", WifiManagerGetError(nRet));

	//Target API
	nRet = wifi_manager_ap_get_ip_address(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &pIpAddr);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_ip_address", WifiManagerGetError(nRet));
	CHECK_HANDLE(pIpAddr, "wifi_manager_ap_get_ip_address");

	if(strcmp(pSetIP, pIpAddr) != 0)
	{
		FPRINTF("[%s:%d] returned value of pIpAddr is not as set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] returned value of pIpAddr is not as set!!", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

//& purpose: Sets/Gets the subnet mask.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_set_get_subnet_mask_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets the subnet mask.
* @apicovered			wifi_manager_ap_set_subnet_mask, wifi_manager_ap_get_subnet_mask
* @passcase				When  wifi_manager_ap_set_subnet_mask, wifi_manager_ap_get_subnet_mask API returns 0
* @failcase				If wifi_manager_ap_set_subnet_mask/wifi_manager_ap_get_subnet_mask returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_set_get_subnet_mask_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *pIpAddr = NULL;
	char *pSetSubnetMask = "255.255.255.0";
	//Target API
	int nRet = wifi_manager_ap_set_subnet_mask(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, pSetSubnetMask);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_subnet_mask", WifiManagerGetError(nRet));

	//Target API
	nRet = wifi_manager_ap_get_subnet_mask(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &pIpAddr);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_subnet_mask", WifiManagerGetError(nRet));
	CHECK_HANDLE(pIpAddr, "wifi_manager_ap_get_subnet_mask");

	if(strcmp(pSetSubnetMask, pIpAddr) != 0)
	{
		FPRINTF("[%s:%d] returned value of pIpAddr is not as set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] returned value of pIpAddr is not as set!!", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

//& purpose: Sets/Gets Gateway's IP address in AP info.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_set_get_gateway_address_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets Gateway's IP address in AP info.
* @apicovered			wifi_manager_ap_set_gateway_address, wifi_manager_ap_get_gateway_address
* @passcase				When  wifi_manager_ap_set_gateway_address, wifi_manager_ap_get_gateway_address API returns 0
* @failcase				If wifi_manager_ap_set_gateway_address/wifi_manager_ap_get_gateway_address returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_set_get_gateway_address_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *pIpAddr = NULL;
	char *pSetGateway = "192.168.11.1";
	//Target API
	int nRet = wifi_manager_ap_set_gateway_address(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, pSetGateway);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_gateway_address", WifiManagerGetError(nRet));

	//Target API
	nRet = wifi_manager_ap_get_gateway_address(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &pIpAddr);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_gateway_address", WifiManagerGetError(nRet));
	CHECK_HANDLE(pIpAddr, "wifi_manager_ap_get_gateway_address");

	if(strcmp(pSetGateway, pIpAddr) != 0)
	{
		FPRINTF("[%s:%d] returned value of pIpAddr is not as set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] returned value of pIpAddr is not as set!!", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

//& purpose: ets the DHCP server's IP address.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_get_dhcp_server_address_p
* @since				4.0
* @author				SRID(shilpa.j)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @scenario				Sets the DHCP server's IP address.
* @apicovered			wifi_manager_ap_get_dhcp_server_address, wifi_manager_ap_get_gateway_address
* @passcase				When  wifi_manager_ap_get_dhcp_server_address, API returns 0
* @failcase				If wifi_manager_ap_get_dhcp_server_address returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_get_dhcp_server_address_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *pIpAddr = NULL;

	//Target API
	int nRet = wifi_manager_ap_get_dhcp_server_address(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &pIpAddr);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_dhcp_server_address", WifiManagerGetError(nRet));
	CHECK_HANDLE(pIpAddr, "wifi_manager_ap_get_gateway_address");

	return 0;
}

//& purpose: Sets/Gets proxy address in AP info.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_set_get_proxy_address_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets proxy address in AP info.
* @apicovered			wifi_manager_ap_set_proxy_address, wifi_manager_ap_get_proxy_address
* @passcase				When  wifi_manager_ap_set_proxy_address, wifi_manager_ap_get_proxy_address API returns 0
* @failcase				If wifi_manager_ap_set_proxy_address/wifi_manager_ap_get_proxy_address returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_set_get_proxy_address_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *pProxy = NULL;
	char *pSetProxy = "192.168.11.1:8080";
	//Target API
	int nRet = wifi_manager_ap_set_proxy_address(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, pSetProxy);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_proxy_address", WifiManagerGetError(nRet));

	//Target API
	nRet = wifi_manager_ap_get_proxy_address(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &pProxy);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_proxy_address", WifiManagerGetError(nRet));
	CHECK_HANDLE(pProxy, "wifi_manager_ap_get_proxy_address");

	if(strcmp(pSetProxy, pProxy) != 0)
	{
		FPRINTF("[%s:%d] returned value of pProxy is not as set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] returned value of pProxy is not as set!!", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

//& purpose: Sets/Gets the Proxy address.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_set_get_proxy_type_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets the Proxy address.
* @apicovered			wifi_manager_ap_set_proxy_type, wifi_manager_ap_get_proxy_type
* @passcase				When  wifi_manager_ap_set_proxy_type, wifi_manager_ap_get_proxy_type API returns 0
* @failcase				If wifi_manager_ap_set_proxy_type/wifi_manager_ap_get_proxy_type returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_set_get_proxy_type_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_proxy_type_e eProxyType;

	wifi_manager_proxy_type_e eWifiManagerProxyType[] = {
		WIFI_MANAGER_PROXY_TYPE_DIRECT,			/**< Direct connection */
		WIFI_MANAGER_PROXY_TYPE_AUTO,			/**< Auto configuration(Use PAC file). If URL property is not set, DHCP/WPAD auto-discover will be tried */
		WIFI_MANAGER_PROXY_TYPE_MANUAL			/**< Manual configuration */
	};

	int nEnumSize = sizeof(eWifiManagerProxyType) / sizeof(eWifiManagerProxyType[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter=0;nEnumCounter<nEnumSize;nEnumCounter++)
	{
		//Target API
		int nRet = wifi_manager_ap_set_proxy_type(g_hWifiAP, eWifiManagerProxyType[nEnumCounter]);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_proxy_type", WifiManagerGetError(nRet));

		//Target API
		nRet = wifi_manager_ap_get_proxy_type(g_hWifiAP, &eProxyType);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_proxy_type", WifiManagerGetError(nRet));

		if(eProxyType != eWifiManagerProxyType[nEnumCounter])
		{
			FPRINTF("[%s:%d] returned value of eProxyType is not as set!!\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] returned value of eProxyType is not as set!!", __FILE__, __LINE__);
			return 1;
		}
	}

	return 0;
}


//& purpose: Sets/Gets the DNS address.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_set_get_dns_address_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets the DNS address.
* @apicovered			wifi_manager_ap_set_dns_address, wifi_manager_ap_get_dns_address
* @passcase				When  wifi_manager_ap_set_dns_address, wifi_manager_ap_get_dns_address API returns 0
* @failcase				If wifi_manager_ap_set_dns_address/wifi_manager_ap_get_dns_address returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_set_get_dns_address_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *pGetDns = NULL;
	char *pSetDns = "192.168.11.1";
	//Target API
	int nRet = wifi_manager_ap_set_dns_address(g_hWifiAP, 1, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, pSetDns);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_dns_address", WifiManagerGetError(nRet));

	//Target API
	nRet = wifi_manager_ap_get_dns_address(g_hWifiAP, 1, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &pGetDns);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_dns_address", WifiManagerGetError(nRet));
	CHECK_HANDLE(pGetDns, "wifi_manager_ap_get_dns_address");

	if(strcmp(pGetDns, pSetDns) != 0)
	{
		FPRINTF("[%s:%d] returned value of pGetDns is not as set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] returned value of pGetDns is not as set!!", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

//& purpose: Sets/Gets Wi-Fi security mode
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_set_get_security_type_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets Wi-Fi security mode
* @apicovered			wifi_manager_ap_set_security_type, wifi_manager_ap_get_security_type
* @passcase				When  wifi_manager_ap_set_security_type, wifi_manager_ap_get_security_type API returns 0
* @failcase				If wifi_manager_ap_set_security_type/wifi_manager_ap_get_security_type returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_set_get_security_type_p(void)
{
	START_TEST_CHECK_INITIALIZE;
	wifi_manager_security_type_e eSecurityType;

	wifi_manager_security_type_e eWifiManagerSecurityType[] = {
		WIFI_MANAGER_SECURITY_TYPE_NONE,		/**< Security disabled */
		WIFI_MANAGER_SECURITY_TYPE_WEP,			/**< WEP */
		WIFI_MANAGER_SECURITY_TYPE_WPA_PSK,		/**< WPA-PSK */
		WIFI_MANAGER_SECURITY_TYPE_WPA2_PSK,	/**< WPA2-PSK */
		WIFI_MANAGER_SECURITY_TYPE_EAP,			/**< EAP */
	        WIFI_MANAGER_SECURITY_TYPE_WPA_FT_PSK,  /**< FT-PSK(Since 5.0)*/
		WIFI_MANAGER_SECURITY_TYPE_SAE,		/**< SAE (Since 5.5)*/
		WIFI_MANAGER_SECURITY_TYPE_OWE,         /**< OWE (Since 5.5)*/
		WIFI_MANAGER_SECURITY_TYPE_DPP          /**< DPP (Since 5.5)*/
	};

	int nEnumSize = sizeof(eWifiManagerSecurityType) / sizeof(eWifiManagerSecurityType[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter=0;nEnumCounter<nEnumSize;nEnumCounter++)
	{
		//Target API
		int nRet = wifi_manager_ap_set_security_type(g_hWifiAP, eWifiManagerSecurityType[nEnumCounter] );
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_security_type", WifiManagerGetError(nRet));

		//Target API
		nRet = wifi_manager_ap_get_security_type(g_hWifiAP, &eSecurityType);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_security_type", WifiManagerGetError(nRet));

		if(eSecurityType != eWifiManagerSecurityType[nEnumCounter])
		{
			FPRINTF("[%s:%d] returned value of eSecurityType is not as set!!\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] returned value of eSecurityType is not as set!!", __FILE__, __LINE__);
			return 1;
		}
	}

	return 0;
}

//& purpose: Sets/Gets Wi-Fi encryption type.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_set_get_encryption_type_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets Wi-Fi encryption type.
* @apicovered			wifi_manager_ap_set_encryption_type, wifi_manager_ap_get_encryption_type
* @passcase				When  wifi_manager_ap_set_encryption_type, wifi_manager_ap_get_encryption_type API returns 0
* @failcase				If wifi_manager_ap_set_encryption_type/wifi_manager_ap_get_encryption_type returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_set_get_encryption_type_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_encryption_type_e eEncryptionType;

	wifi_manager_encryption_type_e eWifiManagerEncryptionType[] = {
		WIFI_MANAGER_ENCRYPTION_TYPE_NONE,		/**< Security disabled */
		WIFI_MANAGER_ENCRYPTION_TYPE_WEP,			/**< WEP */
		WIFI_MANAGER_ENCRYPTION_TYPE_TKIP,		/**< WPA-PSK */
		WIFI_MANAGER_ENCRYPTION_TYPE_AES,	/**< WPA2-PSK */
		WIFI_MANAGER_ENCRYPTION_TYPE_TKIP_AES_MIXED			/**< EAP */
	};

	int nEnumSize = sizeof(eWifiManagerEncryptionType) / sizeof(eWifiManagerEncryptionType[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		//Target API
		int nRet = wifi_manager_ap_set_encryption_type(g_hWifiAP, eWifiManagerEncryptionType[nEnumCounter] );
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_encryption_type", WifiManagerGetError(nRet));

		//Target API
		nRet = wifi_manager_ap_get_encryption_type(g_hWifiAP, &eEncryptionType);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_encryption_type", WifiManagerGetError(nRet));

		if(eEncryptionType != eWifiManagerEncryptionType[nEnumCounter])
		{
			FPRINTF("[%s:%d] returned value of eEncryptionType is not as set!!\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] returned value of eEncryptionType is not as set!!", __FILE__, __LINE__);
			return 1;
		}
	}

	return 0;
}

//& purpose: Checks whether the passphrase is required or not.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_is_passphrase_required_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Checks whether the passphrase is required or not.
* @apicovered			wifi_manager_ap_is_passphrase_required
* @passcase				When  wifi_manager_ap_is_passphrase_required API returns 0
* @failcase				If wifi_manager_ap_is_passphrase_required returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_is_passphrase_required_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	bool bRrequired;

	//Target API
	int nRet =  wifi_manager_ap_is_passphrase_required(g_hWifiAP, &bRrequired);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_is_passphrase_required", WifiManagerGetError(nRet));

	return 0;
}

//& purpose: Sets the passphrase.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_set_passphrase_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets the passphrase.
* @apicovered			wifi_manager_ap_set_passphrase, wifi_manager_ap_set_security_type
* @passcase				When  wifi_manager_ap_set_passphrase, wifi_manager_ap_set_security_type API returns 0
* @failcase				If wifi_manager_ap_set_passphrase, wifi_manager_ap_set_security_type returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_set_passphrase_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	//Target API
	int nRet =  wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_WPA2_PSK);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_set_passphrase", WifiManagerGetError(nRet));

	nRet = wifi_manager_ap_set_passphrase(g_hWifiAP, WIFI_AP_PASSPHRASE);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_set_passphrase", WifiManagerGetError(nRet));

	return 0;
}

//& purpose: Checks whether the WPS(Wi-Fi Protected Setup) is supported or not.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_is_wps_supported_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Checks whether the WPS(Wi-Fi Protected Setup) is supported or not.
* @apicovered			wifi_manager_ap_is_wps_supported
* @passcase				When  wifi_manager_ap_is_wps_supported API returns 0
* @failcase				If wifi_manager_ap_is_wps_supported returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_is_wps_supported_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	bool bSupported;

	//Target API
	int nRet =  wifi_manager_ap_is_wps_supported(g_hWifiAP, &bSupported);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_is_wps_supported", WifiManagerGetError(nRet));

	return 0;
}

//& purpose: Sets/Gets EAP passphrase.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_set_get_eap_passphrase_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets EAP passphrase.
* @apicovered			wifi_manager_ap_set_eap_passphrase, wifi_manager_ap_get_eap_passphrase
* @passcase				When  wifi_manager_ap_set_eap_passphrase, wifi_manager_ap_get_eap_passphrase API returns 0
* @failcase				If wifi_manager_ap_set_eap_passphrase/wifi_manager_ap_get_eap_passphrase returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_set_get_eap_passphrase_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *pUserName = NULL;
	bool bPassword;

	int nRet = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_security_type", WifiManagerGetError(nRet));

	//Target API
	nRet = wifi_manager_ap_set_eap_passphrase(g_hWifiAP, WIFI_EAP_USERNAME, WIFI_EAP_PASSPHRASE);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_eap_passphrase", WifiManagerGetError(nRet));

	//Target API
	nRet = wifi_manager_ap_get_eap_passphrase(g_hWifiAP, &pUserName, &bPassword);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_eap_passphrase", WifiManagerGetError(nRet));
	CHECK_HANDLE(pUserName, "wifi_manager_ap_get_eap_passphrase");
	if(!bPassword)
	{
		FPRINTF("[%s:%d]passwor not set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d]passwor not set!!", __FILE__, __LINE__);
		FREE_MEMORY(pUserName);
		return 1;
	}
	if(strcmp(WIFI_EAP_USERNAME, pUserName) != 0)
	{
		FPRINTF("[%s:%d] returned value of password or user name is not as matched!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] returned value of password or user name is not as matched!!", __FILE__, __LINE__);
		FREE_MEMORY(pUserName);
		return 1;
	}
	FREE_MEMORY(pUserName);

	return 0;
}

//& purpose: Sets/Gets the CA Certificate of EAP.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_set_get_eap_ca_cert_file_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets the CA Certificate of EAP.
* @apicovered			wifi_manager_ap_set_eap_ca_cert_file, wifi_manager_ap_get_eap_ca_cert_file
* @passcase				When  wifi_manager_ap_set_eap_ca_cert_file, wifi_manager_ap_get_eap_ca_cert_file API returns 0
* @failcase				If wifi_manager_ap_set_eap_ca_cert_file/wifi_manager_ap_get_eap_ca_cert_file returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_set_get_eap_ca_cert_file_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *pCertFile = NULL;

	int nRet = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_security_type", WifiManagerGetError(nRet));

	//Target API
	nRet = wifi_manager_ap_set_eap_ca_cert_file(g_hWifiAP, WIFI_EAP_CA_CERT);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_eap_ca_cert_file", WifiManagerGetError(nRet));

	//Target API
	nRet = wifi_manager_ap_get_eap_ca_cert_file(g_hWifiAP, &pCertFile);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_eap_ca_cert_file", WifiManagerGetError(nRet));
	CHECK_HANDLE(pCertFile, "wifi_manager_ap_get_eap_ca_cert_file");

	if(strcmp(WIFI_EAP_CA_CERT, pCertFile) != 0)
	{
		FPRINTF("[%s:%d] returned value of pCertFile is not matched to set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] returned value of pCertFile is not matched to set!!", __FILE__, __LINE__);
		FREE_MEMORY(pCertFile);
		return 1;
	}
	FREE_MEMORY(pCertFile);

	return 0;
}


//& purpose: Sets/Gets Client Certificate of EAP.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_set_get_eap_client_cert_file_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets Client Certificate of EAP.
* @apicovered			wifi_manager_ap_set_eap_client_cert_file, wifi_manager_ap_get_eap_client_cert_file
* @passcase				When  wifi_manager_ap_set_eap_client_cert_file, wifi_manager_ap_get_eap_client_cert_file API returns 0
* @failcase				If wifi_manager_ap_set_eap_client_cert_file/wifi_manager_ap_get_eap_client_cert_file returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_set_get_eap_client_cert_file_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *pCertFile = NULL;

	int nRet = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_security_type", WifiManagerGetError(nRet));

	//Target API
	nRet = wifi_manager_ap_set_eap_client_cert_file(g_hWifiAP, WIFI_EAP_CA_CERT);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_eap_client_cert_file", WifiManagerGetError(nRet));

	//Target API
	nRet = wifi_manager_ap_get_eap_client_cert_file(g_hWifiAP, &pCertFile);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_eap_client_cert_file", WifiManagerGetError(nRet));
	CHECK_HANDLE(pCertFile, "wifi_manager_ap_get_eap_client_cert_file");

	if(strcmp(WIFI_EAP_CA_CERT, pCertFile) != 0)
	{
		FPRINTF("[%s:%d] returned value of pCertFile is not matched to set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] returned value of pCertFile is not matched to set!!", __FILE__, __LINE__);
		FREE_MEMORY(pCertFile);
		return 1;
	}
	FREE_MEMORY(pCertFile);

	return 0;
}

//& purpose: Sets/Gets the private key file of EAP.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_set_get_eap_private_key_info_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets the private key file of EAP.
* @apicovered			wifi_manager_ap_set_eap_private_key_info, wifi_manager_ap_get_eap_private_key_file
* @passcase				When  wifi_manager_ap_set_eap_private_key_info, wifi_manager_ap_get_eap_private_key_file API returns 0
* @failcase				If wifi_manager_ap_set_eap_private_key_info/wifi_manager_ap_get_eap_private_key_file returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_set_get_eap_private_key_info_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *pKeyFile = NULL;

	int nRet = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_security_type", WifiManagerGetError(nRet));

	//Target API
	nRet = wifi_manager_ap_set_eap_private_key_info(g_hWifiAP, WIFI_EAP_CA_CERT, WIFI_EAP_PASSPHRASE);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_set_eap_private_key_info", WifiManagerGetError(nRet));

	//Target API
	nRet = wifi_manager_ap_get_eap_private_key_file(g_hWifiAP, &pKeyFile);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_eap_private_key_file", WifiManagerGetError(nRet));
	CHECK_HANDLE(pKeyFile, "wifi_manager_ap_get_eap_private_key_file");
/*
	if(strcmp(WIFI_EAP_CA_CERT, pKeyFile) != 0)
	{
		FPRINTF("[%s:%d] returned value of pKeyFile is not matched to set!!\\n", __FILE__, __LINE__);
		FREE_MEMORY(pKeyFile);
		return 1;
	}
*/
	FREE_MEMORY(pKeyFile);

	return 0;
}


//& purpose: Sets/Gets EAP type of Wi-Fi
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_set_get_eap_type_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets EAP type of Wi-Fi
* @apicovered			wifi_manager_ap_set_eap_type, wifi_manager_ap_get_eap_type
* @passcase				When  wifi_manager_ap_set_eap_type, wifi_manager_ap_get_eap_type API returns 0
* @failcase				If wifi_manager_ap_set_eap_type/wifi_manager_ap_get_eap_type returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_set_get_eap_type_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_eap_type_e eEapType;

	wifi_manager_eap_type_e eWifiManagerEapType[] = {
		WIFI_MANAGER_EAP_TYPE_PEAP,         /**< EAP PEAP type */
		WIFI_MANAGER_EAP_TYPE_TLS,          /**< EAP TLS type */
		WIFI_MANAGER_EAP_TYPE_TTLS,         /**< EAP TTLS type */
		WIFI_MANAGER_EAP_TYPE_SIM,          /**< EAP SIM type */
		WIFI_MANAGER_EAP_TYPE_AKA           /**< EAP */
	};

	int nEnumSize = sizeof(eWifiManagerEapType) / sizeof(eWifiManagerEapType[0]);
	int nEnumCounter = 0;

	int nRet = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_security_type", WifiManagerGetError(nRet));

	for ( nEnumCounter=0;nEnumCounter<nEnumSize;nEnumCounter++)
	{
		//Target API
		nRet = wifi_manager_ap_set_eap_type(g_hWifiAP, eWifiManagerEapType[nEnumCounter] );
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_eap_type", WifiManagerGetError(nRet));

		//Target API
		nRet = wifi_manager_ap_get_eap_type(g_hWifiAP, &eEapType);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_eap_type", WifiManagerGetError(nRet));

		if(eEapType != eWifiManagerEapType[nEnumCounter])
		{
			FPRINTF("[%s:%d] returned value of eEapType is not as set!!\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] returned value of eEapType is not as set!!", __FILE__, __LINE__);
			return 1;
		}
	}

	return 0;
}

//& purpose: Sets/Gets EAP auth type of Wi-Fi.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_set_get_eap_auth_type_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets EAP auth type of Wi-Fi.
* @apicovered			wifi_manager_ap_set_eap_auth_type, wifi_manager_ap_get_eap_auth_type
* @passcase				When  wifi_manager_ap_set_eap_auth_type, wifi_manager_ap_get_eap_auth_type API returns 0
* @failcase				If wifi_manager_ap_set_eap_auth_type/wifi_manager_ap_get_eap_auth_type returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_set_get_eap_auth_type_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_eap_auth_type_e eAutType;

	wifi_manager_eap_auth_type_e eWifiManagerEapAuthType[] = {
		WIFI_MANAGER_EAP_AUTH_TYPE_NONE,	/**< EAP phase2 authentication none */
		WIFI_MANAGER_EAP_AUTH_TYPE_PAP,		/**< EAP phase2 authentication PAP */
		WIFI_MANAGER_EAP_AUTH_TYPE_MSCHAP,	/**< EAP phase2 authentication MSCHAP */
		WIFI_MANAGER_EAP_AUTH_TYPE_MSCHAPV2,	/**< EAP phase2 authentication MSCHAPv2 */
		WIFI_MANAGER_EAP_AUTH_TYPE_GTC,		/**< EAP phase2 authentication GTC */
		WIFI_MANAGER_EAP_AUTH_TYPE_MD5		/**< EAP phase2 authentication MD5 */
	};

	int nEnumSize = sizeof(eWifiManagerEapAuthType) / sizeof(eWifiManagerEapAuthType[0]);
	int nEnumCounter = 0;

	int nRet = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_security_type", WifiManagerGetError(nRet));

	for ( nEnumCounter=0;nEnumCounter<nEnumSize;nEnumCounter++)
	{
		//Target API
		nRet = wifi_manager_ap_set_eap_auth_type(g_hWifiAP, eWifiManagerEapAuthType[nEnumCounter] );
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_eap_auth_type", WifiManagerGetError(nRet));

		//Target API
		nRet = wifi_manager_ap_get_eap_auth_type(g_hWifiAP, &eAutType);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_eap_auth_type", WifiManagerGetError(nRet));

		if(eAutType != eWifiManagerEapAuthType[nEnumCounter])
		{
			FPRINTF("[%s:%d] returned value of eAutType is not as set!!\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] returned value of eAutType is not as set!!", __FILE__, __LINE__);
			return 1;
		}
	}

	return 0;
}


//& purpose: connected forget and refreshes the access point information.
//& type: auto
/**
* @testcase				ITc_wifi_manager_get_connected_forget_refresh_ap_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				connected forget and refreshes the access point information.
* @apicovered			wifi_manager_get_connected_ap, wifi_manager_forget_ap, wifi_manager_ap_refresh
* @passcase				When  wifi_manager_get_connected_ap, wifi_manager_forget_ap, wifi_manager_ap_refresh API returns 0
* @failcase				If wifi_manager_get_connected_ap, wifi_manager_forget_ap, wifi_manager_ap_refresh returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_get_connected_forget_refresh_ap_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_ap_h hAP = NULL;
	int scan_retry_count = 2;

	int nRet =  wifi_manager_pre_connect();
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_pre_connect", WifiManagerGetError(nRet));

	//Target API
	nRet =  wifi_manager_get_connected_ap(g_hWifi, &hAP);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_get_connected_ap", WifiManagerGetError(nRet));

	//Target API
	nRet =  wifi_manager_forget_ap(g_hWifi, hAP);
	PRINT_RESULT_CLEANUP(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_forget_ap", WifiManagerGetError(nRet), wifi_manager_ap_destroy(hAP));
	sleep(5);

	// Note: Retry scan when AP is not found because
	// scan does not guranttee that AP will be found.
	for (int i = 0; i < scan_retry_count; i++)
	{
		nRet = wifi_manager_scan(g_hWifi, wifi_manager_scanned_callback, NULL);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_scan", WifiManagerGetError(nRet));
		RUN_POLLING_LOOP;

		//Target API
		nRet =  wifi_manager_ap_refresh(hAP);
		if (nRet == WIFI_MANAGER_ERROR_NONE)
			break;
	}
	PRINT_RESULT_CLEANUP(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_refresh", WifiManagerGetError(nRet),wifi_manager_ap_destroy(hAP));

	wifi_manager_ap_destroy(hAP);

	return 0;
}


//& purpose: Connect/Disconnects to the access point asynchronously
//& type: auto
/**
* @testcase				ITc_wifi_manager_connect_disconnect_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Connect/Disconnects to the access point asynchronously
* @apicovered			wifi_manager_connect, wifi_manager_disconnect
* @passcase				When  wifi_manager_connect, wifi_manager_disconnect API returns 0
* @failcase				If wifi_manager_connect, wifi_manager_disconnect returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_connect_disconnect_p(void)
{
	START_TEST_CHECK_INITIALIZE;
	nTimeoutId = 0;
	g_bWifiManagerCB = false;
	wifi_manager_ap_h hAP = NULL;
	int nRet ;

	//Target API Inside calling wifi_manager_connect
	if (wifi_manager_pre_connect() != WIFI_MANAGER_ERROR_NONE)
	{
		return 1;
	}

	nRet = wifi_manager_get_connected_ap(g_hWifi, &hAP);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_get_connected_ap", WifiManagerGetError(nRet));

	//Target API
	nRet = wifi_manager_disconnect(g_hWifi, hAP, wifi_manager_disconnected_callback, NULL);
	PRINT_RESULT_CLEANUP(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_disconnect", WifiManagerGetError(nRet),wifi_manager_pre_connect());
	RUN_POLLING_LOOP;
	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_disconnected_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_disconnected_callback not invoked!!", __FILE__, __LINE__);
		wifi_manager_pre_connect();
		return 1;
	}
	wifi_manager_pre_connect();

	return 0;
}

//& purpose: Connects to the access point with WPS PBC asynchronously.
//& type: auto
/**
* @testcase				ITc_wifi_manager_connect_by_wps_pbc_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Connects to the access point with WPS PBC asynchronously.
* @apicovered			wifi_manager_connect_by_wps_pbc
* @passcase				When  wifi_manager_connect_by_wps_pbc API returns 0
* @failcase				If wifi_manager_connect_by_wps_pbc returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_connect_by_wps_pbc_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	nTimeoutId = 0;
	g_bWifiManagerCB = false;
	bool bSupported = false;

	int nRet =  wifi_manager_ap_is_wps_supported(g_hWifiAP, &bSupported);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_is_wps_supported", WifiManagerGetError(nRet));

	if(!bSupported)
	{
		FPRINTF("[%s:%d] wifi_manager_ap_is_wps_supported wps not supported!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_ap_is_wps_supported wps not supported!!", __FILE__, __LINE__);
		return 0;
	}
	//Target API
	nRet =  wifi_manager_connect_by_wps_pbc(g_hWifi, g_hWifiAP, wifi_manager_connected_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_connect_by_wps_pbc", WifiManagerGetError(nRet));
	RUN_POLLING_LOOP;
	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_connected_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_connected_callback not invoked!!", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

//& purpose: Connects to the access point with WPS PIN asynchronously.
//& type: auto
/**
* @testcase				ITc_wifi_manager_connect_by_wps_pin_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Connects to the access point with WPS PIN asynchronously.
* @apicovered			wifi_manager_connect_by_wps_pin
* @passcase				When  wifi_manager_connect_by_wps_pin API returns 0
* @failcase				If wifi_manager_connect_by_wps_pin returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_connect_by_wps_pin_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	nTimeoutId = 0;
	g_bWifiManagerCB = false;
	const char *pin = "pin";
	bool bSupported;

	int nRet =  wifi_manager_ap_is_wps_supported(g_hWifiAP, &bSupported);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_is_wps_supported", WifiManagerGetError(nRet));
	if(!bSupported)
	{
		FPRINTF("[%s:%d] wifi_manager_ap_is_wps_supported wps not supported!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_ap_is_wps_supported wps not supported!!", __FILE__, __LINE__);
		return 0;
	}

	//Target API
	nRet =  wifi_manager_connect_by_wps_pin(g_hWifi, g_hWifiAP, pin, wifi_manager_connected_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_connect_by_wps_pin", WifiManagerGetError(nRet));
	RUN_POLLING_LOOP;
	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_connected_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_connected_callback not invoked!!", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

//& purpose: Updates an existing AP
//& type: auto
/**
* @testcase		ITc_wifi_manager_update_ap_p
* @since			3.0
* @author		SRID(gaurav.m2)
* @reviewer		SRID(a.pandia1)
* @type			auto
* @scenario		When a AP is changed, these changes will be not applied to the Connection Manager immediately.
* 			When you call this function, your changes affect the Connection Manager and the existing AP is updated
* @apicovered		wifi_manager_update_ap
* @passcase		When  wifi_manager_update_ap API returns 0
* @failcase		If wifi_manager_update_ap returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_update_ap_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	nTimeoutId = 0;
	g_bWifiManagerCB = false;

	//Target API
	int nRet =  wifi_manager_update_ap(g_hWifi, g_hWifiAP);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_update_ap", WifiManagerGetError(nRet));

	return 0;
}


//& purpose: Connects the hidden access point asynchronously.
//& type: auto
/**
* @testcase			int ITc_wifi_manager_connect_hidden_ap_p
* @since			4.0
* @author			SRID(maneesha.k)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @scenario			Connect hidden AP. When AP is found the callback is triggered.
* @apicovered			wifi_manager_connect_hidden_ap
* @passcase			When wifi_manager_connect_hidden_ap API returns 0
* @failcase			If wifi_manager_connect_hidden_ap returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_connect_hidden_ap_p(void)
{
	START_TEST_CHECK_INITIALIZE;
	nTimeoutId = 0;
	int nRet = WIFI_MANAGER_ERROR_NONE;
	char ap_name[CONFIG_VALUE_LEN_MAX] = {0,};
	char ap_passphrase[CONFIG_VALUE_LEN_MAX] = {0,};
	wifi_manager_ap_h hAPTemp = NULL;
	wifi_manager_security_type_e sec_type = WIFI_MANAGER_SECURITY_TYPE_NONE;

	if (GetValueFromConfigFile("WIFI_WPSACCESSPOINTNAME", ap_name, API_NAMESPACE)
		&& GetValueFromConfigFile("WIFI_ACCESSPOINTPIN", ap_passphrase, API_NAMESPACE)) {
		FPRINTF("[%s:%d] Values Received ap_name = %s, ap_passphrase = %s\\n", __FILE__, __LINE__, ap_name, ap_passphrase);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Values Received ap_name = %s, ap_passphrase = %s", __FILE__, __LINE__, ap_name, ap_passphrase);
	} else {
		FPRINTF("[%s:%d] GetValueFromConfigFile returned error\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Values Received = %s", __FILE__, __LINE__);
		return 1;
	}

    // Start of making AP Hidden using wifi_manager_disconnect() if already connected.
	nRet = wifi_manager_get_connected_ap(g_hWifi, &hAPTemp);
	if (nRet != WIFI_MANAGER_ERROR_NO_CONNECTION && nRet != WIFI_MANAGER_ERROR_NONE)
	{
		FPRINTF("[%s:%d] wifi_manager_get_connected_ap failed. Error: %s \\n", __FILE__, __LINE__, WifiManagerGetError(nRet));
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_get_connected_ap failed. Error: %s", __FILE__, __LINE__, WifiManagerGetError(nRet));
		return 1;
	}

	// If already connected then disconnect
	if(hAPTemp != NULL)
	{
		g_bWifiManagerCB = false;
		nRet = wifi_manager_disconnect(g_hWifi, hAPTemp, wifi_manager_disconnected_callback, NULL);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_disconnect", WifiManagerGetError(nRet));
		RUN_POLLING_LOOP;

		if (!g_bWifiManagerCB || (g_nCallbackRet != WIFI_MANAGER_ERROR_NONE) )
		{
			FPRINTF("[%s:%d] Callback issue for wifi_manager_disconnect\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Callback issue for wifi_manager_disconnectn", __FILE__, __LINE__);
			return 1;
		}
	}
	//End of wifi_manager_disconnect code

	//Retry several times to reduce the impact of environmental problems
	for (int i = 0; i < PRE_CONNECT_RETRY; i++) {
		g_bWifiManagerCB = false;
		nRet = wifi_manager_scan(g_hWifi, wifi_manager_scanned_callback, NULL);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_scan", WifiManagerGetError(nRet));
		RUN_POLLING_LOOP;
		if (!g_bWifiManagerCB || (g_nCallbackRet != WIFI_MANAGER_ERROR_NONE) )
		{
			FPRINTF("[%s:%d] Callback issue for wifi_manager_scan api\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Callback issue for wifi_manager_scan api", __FILE__, __LINE__);
			return 1;
		}

		nRet = wifi_manager_foreach_found_ap(g_hWifi, wifi_manager_found_ap_callback, ap_name);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_foreach_found_ap", WifiManagerGetError(nRet));

		nRet = wifi_manager_ap_get_security_type(g_hWifiAP, &sec_type);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_get_security_type", WifiManagerGetError(nRet));

		FPRINTF("[%s:%d] Security type : %d\\n", __FILE__, __LINE__, sec_type);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Security type : %d", __FILE__, __LINE__, sec_type);

		g_bWifiManagerCB = false;
		if (sec_type == WIFI_MANAGER_SECURITY_TYPE_WPA2_PSK || sec_type == WIFI_MANAGER_SECURITY_TYPE_WPA_PSK) {
			nRet = wifi_manager_connect_hidden_ap(g_hWifi, ap_name, 2, ap_passphrase, wifi_manager_connected_callback, NULL);
			CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_connect_hidden_ap", WifiManagerGetError(nRet));
		} else if (sec_type == WIFI_MANAGER_SECURITY_TYPE_WEP) {
			nRet = wifi_manager_connect_hidden_ap(g_hWifi, ap_name, 1, ap_passphrase, wifi_manager_connected_callback, NULL);
			CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_connect_hidden_ap", WifiManagerGetError(nRet));
		} else if (sec_type == WIFI_MANAGER_SECURITY_TYPE_NONE) {
			nRet = wifi_manager_connect_hidden_ap(g_hWifi, ap_name, 0, ap_passphrase, wifi_manager_connected_callback, NULL);
			CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_connect_hidden_ap", WifiManagerGetError(nRet));
		} else {
			FPRINTF("[%s:%d] Security type %d is not supported\\n", __FILE__, __LINE__, sec_type);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Security type %d is not supported", __FILE__, __LINE__, sec_type);
			return 1;
		}
		RUN_POLLING_LOOP;

		if (!g_bWifiManagerCB || (g_nCallbackRet != WIFI_MANAGER_ERROR_NONE) ) {
			FPRINTF("[%s:%d] Callback issue for wifi_manager_connect_hidden_ap api\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Callback issue for wifi_manager_connect_hidden_ap api", __FILE__, __LINE__);
			continue;
		} else {
			return 0;
		}
	}
	return 1;
}

//& purpose: Verify  wifi_manager_ap_set_prefix_length and wifi_manager_ap_get_prefix_length by passing valid parameters
//& type: auto
/**
* @testcase			ITc_wifi_manager_ap_set_get_prefix_length_p
* @since			4.0
* @author			SRID(maneesha.k)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @scenario			Invoking wifi_manager_ap_set_prefix_length and wifi_manager_ap_get_prefix_length with valid parameter
* @apicovered			wifi_manager_ap_set_prefix_length and wifi_manager_ap_get_prefix_length
* @passcase			When  wifi_manager_ap_set_prefix_length and wifi_manager_ap_get_prefix_length APIs returns 0
				and set and retrieved prefix length match
* @failcase			If wifi_manager_ap_set_prefix_length and wifi_manager_ap_get_prefix_length return non zero value
* @precondition			NA
* @postcondition		NA
*/

int ITc_wifi_manager_ap_set_get_prefix_length_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	int setLength = 32, getLength;

	int nRet = wifi_manager_ap_set_prefix_length(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, setLength);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_prefix_length(IPV4)", WifiManagerGetError(nRet));

	nRet = wifi_manager_ap_get_prefix_length(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &getLength);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_prefix_length(IPV4)", WifiManagerGetError(nRet));

	if(setLength != getLength)
	{
		FPRINTF("[%s:%d] Error in ITs_wifi_manager_ap_set_get_prefix_length_p: set prefix length(%d) not equal to retrieved prefix length(%d)!!\\n", __FILE__, __LINE__, setLength, getLength);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Error in ITs_wifi_manager_ap_set_get_prefix_length_p: set prefix length(%d) not equal to retrieved prefix length(%d)!!", __FILE__, __LINE__, setLength, getLength);
		return 1;
	}

	nRet = wifi_manager_ap_set_prefix_length(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV6, setLength);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_prefix_length(IPV6)", WifiManagerGetError(nRet));

	nRet = wifi_manager_ap_get_prefix_length(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV6, &getLength);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_prefix_length(IPV6)", WifiManagerGetError(nRet));

	if(setLength != getLength)
	{
		FPRINTF("[%s:%d] Error in ITs_wifi_manager_ap_set_get_prefix_length_p: set prefix length(%d) not equal to retrieved prefix length(%d)!!\\n", __FILE__, __LINE__, setLength, getLength);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Error in ITs_wifi_manager_ap_set_get_prefix_length_p: set prefix length(%d) not equal to retrieved prefix length(%d)!!", __FILE__, __LINE__, setLength, getLength);
		return 1;
	}

	return 0;
}




//& purpose: Verify  wifi_manager_ap_set_dns_config_type and wifi_manager_ap_get_dns_config_type by passing valid parameters
//& type: auto
/**
* @testcase			ITc_wifi_manager_ap_set_get_dns_config_type_p
* @since			4.0
* @author			SRID(maneesha.k)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @scenario			Invoking wifi_manager_ap_set_dns_config_type and wifi_manager_ap_get_dns_config_type with valid parameter
* @apicovered			wifi_manager_ap_set_dns_config_type and wifi_manager_ap_get_dns_config_type
* @passcase			When  wifi_manager_ap_set_dns_config_type and wifi_manager_ap_get_dns_config_type APIs return 0 and set and retrieved dns configuration match
* @failcase			If wifi_manager_ap_set_dns_config_type and wifi_manager_ap_get_dns_config_type return non zero values or
				set and retrieved DNS configuration do not match
* @precondition			NA
* @postcondition		NA
*/

int ITc_wifi_manager_ap_set_get_dns_config_type_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_dns_config_type_e getDnsType;
	wifi_manager_dns_config_type_e setDnsType[] = { WIFI_MANAGER_DNS_CONFIG_TYPE_DYNAMIC,
							WIFI_MANAGER_DNS_CONFIG_TYPE_STATIC};

	int nRet, enumCntr = 0, enumSize;
	enumSize = sizeof(setDnsType)/sizeof(setDnsType[0]);

	for(enumCntr = 0; enumCntr < enumSize; enumCntr++)
	{

		nRet = wifi_manager_ap_set_dns_config_type(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, setDnsType[enumCntr]);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_set_dns_config_type(IPV4)", WifiManagerGetError(nRet));

		nRet = wifi_manager_ap_get_dns_config_type(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &getDnsType);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_get_dns_config_type(IPV4)", WifiManagerGetError(nRet));

		if(setDnsType[enumCntr] != getDnsType)
		{
			FPRINTF("[%s:%d] Error in ITc_wifi_manager_ap_set_get_dns_config_type_p: set DNS Config type not equal to retrieved DNS Config type!!\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Error in ITc_wifi_manager_ap_set_get_dns_config_type_p: set DNS Config type not equal to retrieved DNS Config type!!", __FILE__, __LINE__);
			return 1;
		}

		nRet = wifi_manager_ap_set_dns_config_type(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV6, setDnsType[enumCntr]);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_set_dns_config_type(IPV6)", WifiManagerGetError(nRet));

		nRet = wifi_manager_ap_get_dns_config_type(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV6, &getDnsType);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_get_dns_config_type(IPV6)", WifiManagerGetError(nRet));

		if(setDnsType[enumCntr] != getDnsType)
		{
			FPRINTF("[%s:%d] Error in ITc_wifi_manager_ap_set_get_dns_config_type_p: set DNS Config type not equal to retrieved DNS Config type!!\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Error in ITc_wifi_manager_ap_set_get_dns_config_type_p: set DNS Config type not equal to retrieved DNS Config type!!", __FILE__, __LINE__);
			return 1;
		}
	}

	return 0;
}





//& purpose: Verify  wifi_manager_ap_foreach_ipv6_address by passing valid parameters
//& type: auto
/**
* @testcase			ITc_wifi_manager_ap_foreach_ipv6_address_p
* @since			4.0
* @author			SRID(maneesha.k)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @scenario			Invoking wifi_manager_ap_foreach_ipv6_address with valid parameter
* @apicovered			wifi_manager_ap_foreach_ipv6_address
* @passcase			When  wifi_manager_ap_foreach_ipv6_address return 0 and set and retrieved dns configuration match
* @failcase			If wifi_manager_ap_foreach_ipv6_address return non zero values or
* @precondition			NA
* @postcondition		NA
*/

int ITc_wifi_manager_ap_foreach_ipv6_address_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	g_bWifiManagerCB = false;

	int nRet = wifi_manager_ap_foreach_ipv6_address(g_hWifiAP, wifi_manager_ap_ipv6_address_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_foreach_ipv6_address", WifiManagerGetError(nRet));

	if(!g_bWifiManagerCB)
	{
		FPRINTF("[%s:%d] wifi_manager_ap_foreach_ipv6_address not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_ap_foreach_ipv6_address not invoked!!", __FILE__, __LINE__);
		return 1;
	}
	return 0;
}


//& purpose: Gets Raw SSID Bytes
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_get_raw_ssid_p
* @since				4.0
* @author				SRID(a.pandia1)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @scenario				Gets Raw SSID Bytes
* @apicovered			wifi_manager_ap_get_raw_ssid
* @passcase				When  wifi_manager_ap_get_raw_ssid API returns 0
* @failcase				If  wifi_manager_ap_get_raw_ssid returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_get_raw_ssid_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *pszRawSsid = NULL;
	int nRawSsidLen;

	//Target API
	int nRet =  wifi_manager_ap_get_raw_ssid(g_hWifiAP, &pszRawSsid, &nRawSsidLen);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_get_raw_ssid", WifiManagerGetError(nRet));
	CHECK_HANDLE(pszRawSsid, "wifi_manager_ap_get_raw_ssid");

	FREE_MEMORY(pszRawSsid);
	return 0;
}

//& purpose: Gets the error state
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_get_error_state_p
* @since				4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @scenario				Gets the error state
* @apicovered			wifi_manager_ap_get_error_state
* @passcase				When  wifi_manager_ap_get_error_state API returns 0
* @failcase				If  wifi_manager_ap_get_error_state returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_get_error_state_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_error_e error_state;
	int nRet = wifi_manager_ap_get_error_state(g_hWifiAP, &error_state);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_get_error_state", WifiManagerGetError(nRet));
	FPRINTF("[%s:%d] wifi_manager_ap_get_error_state return value=%d\\n", __FILE__, __LINE__, error_state);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] wifi_manager_ap_get_error_state return value=%d", __FILE__, __LINE__, error_state);

	return 0;
}

//& purpose: Gets the DHCP lease duration
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_get_dhcp_lease_duration_p
* @since				4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @scenario				Gets the DHCP lease duration
* @apicovered			wifi_manager_ap_get_dhcp_lease_duration
* @passcase				When  wifi_manager_ap_get_dhcp_lease_duration API returns 0
* @failcase				If  wifi_manager_ap_get_dhcp_lease_duration non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_get_dhcp_lease_duration_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	int dhcp_lease_duration = 0;
	int nRet = wifi_manager_ap_get_dhcp_lease_duration(g_hWifiAP, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, &dhcp_lease_duration);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_get_dhcp_lease_duration", WifiManagerGetError(nRet));
	FPRINTF("[%s:%d] wifi_manager_ap_get_dhcp_lease_duration return value=%d\\n", __FILE__, __LINE__, dhcp_lease_duration);
	dlog_print(DLOG_INFO, "NativeTCT", "[Line : %d][%d] wifi_manager_ap_get_dhcp_lease_duration return value=%d", __FILE__, __LINE__, dhcp_lease_duration);

	return 0;
}
//& purpose: To get association status code.
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_get_assoc_status_code_p
* @since				5.0
* @author				SRID(bipin.k)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Invoke wifi_manager_ap_get_assoc_status_code() with valid parameter
* @apicovered			wifi_manager_ap_get_assoc_status_code
* @passcase				When  wifi_manager_ap_get_assoc_status_code returns 0 on success
* @failcase				If  wifi_manager_ap_get_assoc_status_code returns negative value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_get_assoc_status_code_p(void)
{
	START_TEST_CHECK_INITIALIZE;
	int nRet;
	wifi_manager_assoc_status_code_e status_code;

	nRet = wifi_manager_ap_get_assoc_status_code(g_hWifiAP, &status_code);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_get_assoc_status_code", WifiManagerGetError(nRet));

	return 0;
}

//& purpose:Gets all VSIE of AP
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_foreach_vsie_p
* @since				5.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Gets all VSIE of AP
* @apicovered			wifi_manager_ap_foreach_vsie
* @passcase				When API get pass
* @failcase				If wifi_manager_ap_foreach_vsie API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_foreach_vsie_p(void)
{
	START_TEST_CHECK_INITIALIZE;
	char ap_name[CONFIG_VALUE_LEN_MAX] = {0,};

	if (GetValueFromConfigFile("WIFI_WPSACCESSPOINTNAME", ap_name, API_NAMESPACE)) {
		FPRINTF("[%s:%d] Values Received ap_name = %s", __FILE__, __LINE__, ap_name);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Values Received ap_name = %s", __FILE__, __LINE__, ap_name);
	} else {
		FPRINTF("[%s:%d] GetValueFromConfigFile returned error\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d]", __FILE__, __LINE__);
		return 1;
	}

	g_bWifiManagerCB = false;
	int ret = wifi_manager_scan(g_hWifi, wifi_manager_scanned_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, ret, "wifi_manager_scan", WifiManagerGetError(ret));
	RUN_POLLING_LOOP;
	if (!g_bWifiManagerCB || (g_nCallbackRet != WIFI_MANAGER_ERROR_NONE) )
	{
		FPRINTF("[%s:%d] Callback issue for wifi_manager_scan api\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Callback issue for wifi_manager_scan api", __FILE__, __LINE__);
		return 1;
	}

	ret = wifi_manager_foreach_found_ap(g_hWifi, wifi_manager_found_ap_callback, ap_name);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, ret, "wifi_manager_foreach_found_ap", WifiManagerGetError(ret));

	g_bWifiManagerVsieCB = false;
	int nRet = wifi_manager_ap_foreach_vsie(g_hWifiAP, wifi_manager_ap_foreach_vsie_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_foreach_vsie", WifiManagerGetError(nRet));

	/* Not all APs provide VSIE information.
	 * So callbacks may not be called.
	 */
	if(!g_bWifiManagerVsieCB)
	{
		FPRINTF("[%s:%d] wifi_manager_ap_foreach_vsie_callback not invoked, %s has no VSIE\\n", __FILE__, __LINE__, ap_name);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_ap_foreach_vsie_callback not invoked, %s has no VSIE", __FILE__, __LINE__, ap_name);
	}

	return 0;
}
//& purpose: Gets the raw country code
//& type: auto
/**
* @testcase				ITc_wifi_manager_ap_get_countrycode_p
* @since				5.0
* @author				SRID(manu.tiwari)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Gets the raw country code
* @apicovered			wifi_manager_ap_get_countrycode
* @passcase				When  wifi_manager_ap_get_countrycode API returns 0
* @failcase				If wifi_manager_ap_get_countrycode returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_ap_get_countrycode_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *country_code = NULL;

	//Target API
	int nRet =  wifi_manager_ap_get_countrycode(g_hWifiAP, &country_code);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_get_countrycode", WifiManagerGetError(nRet));

	if(country_code == NULL)
	{
		FPRINTF("[%s:%d] wifi_manager_ap_get_countrycode returned value is not set in M/W!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_ap_get_countrycode returned value is not set in M/W!!", __FILE__, __LINE__);
	}
	FREE_MEMORY(country_code);

	return 0;
}
//& purpose:Gets the BSSID list
//& type: auto
/**
* @testcase				ITc_wifi_manager_foreach_found_bssid_p
* @since				5.0
* @author				SRID(manu.tiwari)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Gets the BSSID list
* @apicovered			wifi_manager_foreach_found_bssid
* @passcase				When API get pass
* @failcase				If wifi_manager_foreach_found_bssid API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_foreach_found_bssid_p(void)
{
	START_TEST_CHECK_INITIALIZE;
	char ap_name[CONFIG_VALUE_LEN_MAX] = {0,};

	if (GetValueFromConfigFile("WIFI_WPSACCESSPOINTNAME", ap_name, API_NAMESPACE)) {
		FPRINTF("[%s:%d] Values Received ap_name = %s", __FILE__, __LINE__, ap_name);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Values Received ap_name = %s", __FILE__, __LINE__, ap_name);
	} else {
		FPRINTF("[%s:%d] GetValueFromConfigFile returned error\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d]", __FILE__, __LINE__);
		return 1;
	}

	g_bWifiManagerCB = false;
	g_nCallbackRet = WIFI_MANAGER_ERROR_NONE;
	int ret = wifi_manager_scan(g_hWifi, wifi_manager_scanned_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, ret, "wifi_manager_scan", WifiManagerGetError(ret));
	RUN_POLLING_LOOP;
	if (!g_bWifiManagerCB || (g_nCallbackRet != WIFI_MANAGER_ERROR_NONE) )
	{
		FPRINTF("[%s:%d] Callback issue for wifi_manager_scan api\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Callback issue for wifi_manager_scan api", __FILE__, __LINE__);
		return 1;
	}

	ret = wifi_manager_foreach_found_ap(g_hWifi, wifi_manager_found_ap_callback, ap_name);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, ret, "wifi_manager_foreach_found_ap", WifiManagerGetError(ret));

	g_bWifiManagerCB = false;
	int nRet = wifi_manager_foreach_found_bssid(g_hWifiAP, wifi_manager_foreach_found_bssid_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_foreach_found_bssid", WifiManagerGetError(nRet));

	if(!g_bWifiManagerCB)
	{
		FPRINTF("[%s:%d] wifi_manager_foreach_found_bssid_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_foreach_found_bssid_callback not invoked!!", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

//& purpose: Verify  wifi_manager_ap_get_eap_anonymous_identity and wifi_manager_ap_set_eap_anonymous_identity by passing valid parameters
//& type: auto
/**
* @testcase			ITc_wifi_manager_ap_set_get_eap_anonymous_identity_p
* @since			5.5
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @scenario			Invoking wifi_manager_ap_get_eap_anonymous_identity and wifi_manager_ap_set_eap_anonymous_identity with valid parameter
* @apicovered			ifi_manager_ap_get_eap_anonymous_identity and wifi_manager_ap_set_eap_anonymous_identity
* @passcase			When  ifi_manager_ap_get_eap_anonymous_identity and wifi_manager_ap_set_eap_anonymous_identity APIs returns 0
* @failcase			If ifi_manager_ap_get_eap_anonymous_identity or wifi_manager_ap_set_eap_anonymous_identity return non zero value
* @precondition			NA
* @postcondition		NA
*/

int ITc_wifi_manager_ap_set_get_eap_anonymous_identity_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char  *spszIdentity = "Manoj";
	char  *gpszIdentity = NULL;

	int nRet = wifi_manager_ap_set_security_type(g_hWifiAP, WIFI_MANAGER_SECURITY_TYPE_EAP);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_security_type", WifiManagerGetError(nRet));

	nRet = wifi_manager_ap_set_eap_anonymous_identity(g_hWifiAP, spszIdentity);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_ap_set_eap_anonymous_identity", WifiManagerGetError(nRet));

	nRet = wifi_manager_ap_get_eap_anonymous_identity(g_hWifiAP, &gpszIdentity);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "  wifi_manager_ap_get_eap_anonymous_identity", WifiManagerGetError(nRet));
	CHECK_HANDLE(gpszIdentity, "wifi_manager_ap_get_eap_anonymous_identity");

	if ( 0 != strncmp(spszIdentity, gpszIdentity, strlen(gpszIdentity)))
        {
                FPRINTF("[Line : %d][%s] mismatch between set and get value of anonymous identity as spszIdentity =  %s and gpszIdentity = %s\\n", __LINE__, API_NAMESPACE, spszIdentity, gpszIdentity);
                return 1;
        }

	return 0;
}

/** @} */
