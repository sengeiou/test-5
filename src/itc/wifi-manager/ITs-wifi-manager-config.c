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
#define PREFIX_LENGTH 8

//& set: WifiManager

/** @addtogroup itc-wifi-manager
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_wifi_manager_config_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_wifi_manager_config_startup(void)
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
		nRet = wifi_manager_config_create(g_hWifi, WIFI_CONFIG_NAME, WIFI_CONFIG_PASSWORD, WIFI_MANAGER_SECURITY_TYPE_EAP, &g_hWifiConfig);
		if ( nRet != WIFI_MANAGER_ERROR_NONE )
		{
			FPRINTF("[%s:%d] wifi_manager_initialize failed, error returned = %s (%d)\\n", __FILE__, __LINE__, WifiManagerGetError(nRet), nRet);
			dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] wifi_manager_initialize failed, error returned = %s (%d)", __FILE__, __LINE__, WifiManagerGetError(nRet), nRet);
			g_bWifiManagerCreation = false;
		}
		if(g_hWifiConfig == NULL)
		{
			FPRINTF("[%s:%d] wifi_manager_config_create handle is NULL\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] wifi_manager_config_create handle is NULL", __FILE__, __LINE__);
			g_bWifiManagerCreation = false;
		}
	}
	return;
}


/**
 * @function 		ITs_wifi_manager_config_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_wifi_manager_config_cleanup(void)
{
	int nRet = 0;
	if (g_hWifiConfig) {
		nRet = wifi_manager_config_destroy(g_hWifiConfig);
		PRINT_RESULT_NORETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_config_destroy", WifiManagerGetError(nRet));
	}

	nRet = wifi_manager_deinitialize(g_hWifi);
	if(nRet !=0)
	{
		FPRINTF("[%s:%d] wifi_manager_deinitialize failed\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] wifi_manager_deinitialize failed", __FILE__, __LINE__);
	}

	return;
}

/** @addtogroup itc-wifi-manager-testcases
*  @brief 		Integration testcases for module wifi-manager
*  @ingroup 	itc-wifi-manager
*  @{
*/


//& purpose: Gets access point configuration handle.
//& type: auto
/**
* @testcase				ITc_wifi_manager_config_create_destroy_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Gets access point configuration handle.
* @apicovered			wifi_manager_config_create, wifi_manager_config_destroy
* @passcase				When  wifi_manager_config_create, wifi_manager_config_destroy API returns 0
* @failcase				If  wifi_manager_config_create, wifi_manager_config_destroy returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_config_create_destroy_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_config_h hConfig = NULL;

	int nRet =  wifi_manager_config_create(g_hWifi, WIFI_CONFIG_NAME, WIFI_CONFIG_PASSWORD, WIFI_MANAGER_SECURITY_TYPE_WPA2_PSK, &hConfig);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_create", WifiManagerGetError(nRet));
	CHECK_HANDLE(hConfig, "wifi_manager_config_create");

	nRet = wifi_manager_config_destroy(hConfig);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_config_destroy", WifiManagerGetError(nRet));

	return 0;
}

//& purpose: Saves Wi-Fi configuration of access point
//& type: auto
/**
* @testcase				ITc_wifi_manager_config_save_remove_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Saves Wi-Fi configuration of access point
* @apicovered			wifi_manager_config_save, wifi_manager_config_remove
* @passcase				When  wifi_manager_config_save, wifi_manager_config_remove API returns 0
* @failcase				If  wifi_manager_config_save, wifi_manager_config_remove returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_config_save_remove_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	int nRet =  wifi_manager_config_save(g_hWifi, g_hWifiConfig);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_save", WifiManagerGetError(nRet));

	nRet = wifi_manager_config_remove(g_hWifi, g_hWifiConfig);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_config_remove", WifiManagerGetError(nRet));

	return 0;
}

//& purpose: Load Wi-Fi configuration of access point.
//& type: auto
/**
* @testcase				ITc_wifi_manager_config_foreach_configuration_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Load Wi-Fi configuration of access point.
* @apicovered			wifi_manager_config_foreach_configuration, wifi_manager_config_save, wifi_manager_config_remove
* @passcase				When wifi_manager_config_foreach_configuration, wifi_manager_config_save, wifi_manager_config_remove API returns 0
* @failcase				If wifi_manager_config_foreach_configuration, wifi_manager_config_save, wifi_manager_config_remove returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_config_foreach_configuration_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	g_bWifiManagerCB = false;
	nTimeoutId = 0;
	int nRet = wifi_manager_config_save(g_hWifi, g_hWifiConfig);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_save", WifiManagerGetError(nRet));

	//Target Api
	nRet = wifi_manager_config_foreach_configuration(g_hWifi, wifi_manager_foreach_configuration_cb, NULL);
	PRINT_RESULT_CLEANUP(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_config_foreach_configuration", WifiManagerGetError(nRet),wifi_manager_config_remove(g_hWifi, g_hWifiConfig));

	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_foreach_configuration_cb not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] wifi_manager_foreach_configuration_cb not invoked!!", __FILE__, __LINE__);
		wifi_manager_config_remove(g_hWifi, g_hWifiConfig);
		return 1;
	}

	nRet = wifi_manager_config_remove(g_hWifi, g_hWifiConfig);
	PRINT_RESULT_NORETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_config_remove", WifiManagerGetError(nRet));

	return 0;
}

//& purpose: Clones the access point configuration handle
//& type: auto
/**
* @testcase				ITc_wifi_manager_config_clone_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Clones the access point configuration handle
* @apicovered			wifi_manager_config_clone, wifi_manager_config_destroy
* @passcase				When  wifi_manager_config_clone, wifi_manager_config_destroy API returns 0
* @failcase				If  wifi_manager_config_clone, wifi_manager_config_destroy returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_config_clone_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_config_h hClonedConfig = NULL;

	int nRet =  wifi_manager_config_clone(g_hWifiConfig, &hClonedConfig);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_clone", WifiManagerGetError(nRet));
	CHECK_HANDLE(hClonedConfig, "wifi_manager_config_clone");

	nRet = wifi_manager_config_destroy(hClonedConfig);
	PRINT_RESULT_NORETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_config_destroy", WifiManagerGetError(nRet));

	return 0;
}

//& purpose: Gets the name of access point from configuration.
//& type: auto
/**
* @testcase				ITc_wifi_manager_config_get_name_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Gets the name of access point from configuration.
* @apicovered			wifi_manager_config_get_name
* @passcase				When  wifi_manager_config_get_name API returns 0
* @failcase				If  wifi_manager_config_get_name returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_config_get_name_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *pConfigName = NULL;

	int nRet =  wifi_manager_config_get_name(g_hWifiConfig, &pConfigName);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_get_name", WifiManagerGetError(nRet));

	if(pConfigName == NULL)
	{
		FPRINTF("[%s:%d] wifi_manager_config_get_name value returned is NULL!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] wifi_manager_config_get_name value returned is NULL!!", __FILE__, __LINE__);
		return 1;
	}

	FREE_MEMORY(pConfigName);

	return 0;
}

//& purpose: Gets the security type of access point from configuration.
//& type: auto
/**
* @testcase				ITc_wifi_manager_config_get_security_type_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Gets the security type of access point from configuration.
* @apicovered			wifi_manager_config_get_security_type
* @passcase				When  wifi_manager_config_get_security_type API returns 0
* @failcase				If  wifi_manager_config_get_security_type returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_config_get_security_type_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_security_type_e eConfigSecurityType = -1;

	int nRet =  wifi_manager_config_get_security_type(g_hWifiConfig, &eConfigSecurityType);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_get_security_type", WifiManagerGetError(nRet));
	if(eConfigSecurityType == -1)
	{
		FPRINTF("[%s:%d] wifi_manager_config_get_security_type value returned is not set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] wifi_manager_config_get_security_type value returned is not set!!", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

//& purpose: Sets/Gets access point proxy address configuration.
//& type: auto
/**
* @testcase				ITc_wifi_manager_config_set_get_proxy_address_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets access point proxy address configuration.
* @apicovered			wifi_manager_config_set_proxy_address, wifi_manager_config_get_proxy_address
* @passcase				When  wifi_manager_config_set_proxy_address, wifi_manager_config_get_proxy_address API returns 0
* @failcase				If  wifi_manager_config_set_proxy_address, wifi_manager_config_get_proxy_address returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_config_set_get_proxy_address_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *proxy;
	wifi_manager_address_family_e eAddressFamily = WIFI_MANAGER_ADDRESS_FAMILY_IPV4;

	int nRet =  wifi_manager_config_set_proxy_address(g_hWifiConfig, WIFI_MANAGER_ADDRESS_FAMILY_IPV4, WIFI_CONFIG_PROXY);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_set_proxy_address", WifiManagerGetError(nRet));

	nRet =  wifi_manager_config_get_proxy_address(g_hWifiConfig, &eAddressFamily, &proxy);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_get_proxy_address", WifiManagerGetError(nRet));

	if(strcmp(WIFI_CONFIG_PROXY, proxy) != 0)
	{
		FPRINTF("[%s:%d] returned value of proxy is not matched to set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] returned value of proxy is not matched to set!!", __FILE__, __LINE__);
		FREE_MEMORY(proxy);
		return 1;
	}
	FREE_MEMORY(proxy);

	return 0;
}

//& purpose: Sets/Gets access point hidden ssid configuration.
//& type: auto
/**
* @testcase				ITc_wifi_manager_config_set_get_hidden_ap_property_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets access point hidden ssid configuration.
* @apicovered			wifi_manager_config_set_hidden_ap_property, wifi_manager_config_get_hidden_ap_property
* @passcase				When  wifi_manager_config_set_hidden_ap_property, wifi_manager_config_get_hidden_ap_property API returns 0
* @failcase				If  wifi_manager_config_set_hidden_ap_property, wifi_manager_config_get_hidden_ap_property returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_config_set_get_hidden_ap_property_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	bool bHiddenSsid = FALSE;

	int nRet =  wifi_manager_config_set_hidden_ap_property(g_hWifiConfig, TRUE);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_set_hidden_ap_property", WifiManagerGetError(nRet));

	nRet =  wifi_manager_config_get_hidden_ap_property(g_hWifiConfig, &bHiddenSsid);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_get_hidden_ap_property", WifiManagerGetError(nRet));

	if(!bHiddenSsid)
	{
		FPRINTF("[%s:%d] returned value of bHiddenSsid is not matched set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] returned value of bHiddenSsid is not matched set!!", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

//& purpose: Sets/Gets access point anonymous identity from configuration.
//& type: auto
/**
* @testcase				ITc_wifi_manager_config_set_get_eap_anonymous_identity_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets access point anonymous identity from configuration.
* @apicovered			wifi_manager_config_set_eap_anonymous_identity, wifi_manager_config_get_eap_anonymous_identity
* @passcase				When  wifi_manager_config_set_eap_anonymous_identity, wifi_manager_config_get_eap_anonymous_identity API returns 0
* @failcase				If  wifi_manager_config_set_eap_anonymous_identity, wifi_manager_config_get_eap_anonymous_identity returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_config_set_get_eap_anonymous_identity_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *pAnonymousIdentity = NULL;

	int nRet = wifi_manager_config_set_eap_anonymous_identity(g_hWifiConfig, WIFI_CONFIG_AN_ID);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_set_eap_anonymous_identity", WifiManagerGetError(nRet));

	nRet =  wifi_manager_config_get_eap_anonymous_identity(g_hWifiConfig, &pAnonymousIdentity);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_get_eap_anonymous_identity", WifiManagerGetError(nRet));

	if(strcmp(WIFI_CONFIG_AN_ID, pAnonymousIdentity) != 0)
	{
		FPRINTF("[%s:%d] returned value of pAnonymousIdentity is not matched to set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] returned value of pAnonymousIdentity is not matched to set!!", __FILE__, __LINE__);
		FREE_MEMORY(pAnonymousIdentity);
		return 1;
	}
	FREE_MEMORY(pAnonymousIdentity);

	return 0;
}

//& purpose: Sets/Gets access point cacert file from configuration.
//& type: auto
/**
* @testcase				ITc_wifi_manager_config_set_get_eap_ca_cert_file_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets access point cacert file from configuration.
* @apicovered			wifi_manager_config_set_eap_ca_cert_file, wifi_manager_config_get_eap_ca_cert_file
* @passcase				When  wifi_manager_config_set_eap_ca_cert_file, wifi_manager_config_get_eap_ca_cert_file API returns 0
* @failcase				If  wifi_manager_config_set_eap_ca_cert_file, wifi_manager_config_get_eap_ca_cert_file returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_config_set_get_eap_ca_cert_file_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *pCaCert = NULL;

	int nRet = wifi_manager_config_set_eap_ca_cert_file(g_hWifiConfig, WIFI_CONFIG_CA_CERT_FILE);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_set_eap_ca_cert_file", WifiManagerGetError(nRet));

	nRet =  wifi_manager_config_get_eap_ca_cert_file(g_hWifiConfig, &pCaCert);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_get_eap_ca_cert_file", WifiManagerGetError(nRet));

	if(strcmp(WIFI_CONFIG_CA_CERT_FILE, pCaCert) != 0)
	{
		FPRINTF("[%s:%d] returned value of pCaCert is not matched to set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] returned value of pCaCert is not matched to set!!", __FILE__, __LINE__);
		FREE_MEMORY(pCaCert);
		return 1;
	}
	FREE_MEMORY(pCaCert);

	return 0;
}

//& purpose: Sets/Gets access point client cert file to configuration.
//& type: auto
/**
* @testcase				ITc_wifi_manager_config_set_get_eap_client_cert_file_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets access point client cert file to configuration.
* @apicovered			wifi_manager_config_set_eap_client_cert_file, wifi_manager_config_get_eap_client_cert_file
* @passcase				When  wifi_manager_config_set_eap_client_cert_file, wifi_manager_config_get_eap_client_cert_file API returns 0
* @failcase				If  wifi_manager_config_set_eap_client_cert_file, wifi_manager_config_get_eap_client_cert_file returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_config_set_get_eap_client_cert_file_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *pClientCert = NULL;

	int nRet = wifi_manager_config_set_eap_client_cert_file(g_hWifiConfig, WIFI_CONFIG_PRIVATE_KEY, WIFI_CONFIG_CLIENT_CERT);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_set_eap_client_cert_file", WifiManagerGetError(nRet));

	nRet =  wifi_manager_config_get_eap_client_cert_file(g_hWifiConfig, &pClientCert);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_get_eap_client_cert_file", WifiManagerGetError(nRet));

	if(strcmp(WIFI_CONFIG_CLIENT_CERT, pClientCert) != 0)
	{
		FPRINTF("[%s:%d] returned value of pClientCert is not matched to set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] returned value of pClientCert is not matched to set!!", __FILE__, __LINE__);
		FREE_MEMORY(pClientCert);
		return 1;
	}
	FREE_MEMORY(pClientCert);

	return 0;
}

//& purpose: Sets/Gets access point identity from configuration.
//& type: auto
/**
* @testcase				ITc_wifi_manager_config_set_get_eap_identity_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets access point identity from configuration.
* @apicovered			wifi_manager_config_set_eap_identity, wifi_manager_config_get_eap_identity
* @passcase				When  wifi_manager_config_set_eap_identity, wifi_manager_config_get_eap_identity API returns 0
* @failcase				If  wifi_manager_config_set_eap_identity, wifi_manager_config_get_eap_identity returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_config_set_get_eap_identity_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *pIdentity = NULL;

	int nRet = wifi_manager_config_set_eap_identity(g_hWifiConfig, WIFI_CONFIG_IDENTITY);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_set_eap_identity", WifiManagerGetError(nRet));

	nRet =  wifi_manager_config_get_eap_identity(g_hWifiConfig, &pIdentity);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_get_eap_identity", WifiManagerGetError(nRet));

	if(strcmp(WIFI_CONFIG_IDENTITY, pIdentity) != 0)
	{
		FPRINTF("[%s:%d] returned value of pIdentity is not matched to set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] returned value of pIdentity is not matched to set!!", __FILE__, __LINE__);
		FREE_MEMORY(pIdentity);
		return 1;
	}
	FREE_MEMORY(pIdentity);

	return 0;
}

//& purpose: Sets/Gets access point eap type from configuration.
//& type: auto
/**
* @testcase				ITc_wifi_manager_config_set_get_eap_type_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets access point eap type from configuration.
* @apicovered			wifi_manager_config_set_eap_type, wifi_manager_config_get_eap_type
* @passcase				When  wifi_manager_config_set_eap_type, wifi_manager_config_get_eap_type API returns 0
* @failcase				If wifi_manager_config_set_eap_type/wifi_manager_config_get_eap_type returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_config_set_get_eap_type_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_eap_type_e eEapType;
	int nRet = 0;

	wifi_manager_eap_type_e eWifiManagerEapType[] = {
		WIFI_MANAGER_EAP_TYPE_PEAP,			/**< EAP PEAP type */
		WIFI_MANAGER_EAP_TYPE_TLS,			/**< EAP TLS type */
		WIFI_MANAGER_EAP_TYPE_TTLS,			/**< EAP TTLS type */
		WIFI_MANAGER_EAP_TYPE_SIM,			/**< EAP SIM type */
		WIFI_MANAGER_EAP_TYPE_AKA				/**< EAP */
	};

	int nEnumSize = sizeof(eWifiManagerEapType) / sizeof(eWifiManagerEapType[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter=0;nEnumCounter<nEnumSize;nEnumCounter++)
	{
		//Target API
		nRet = wifi_manager_config_set_eap_type(g_hWifiConfig, eWifiManagerEapType[nEnumCounter] );
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_set_eap_type", WifiManagerGetError(nRet));

		//Target API
		nRet = wifi_manager_config_get_eap_type(g_hWifiConfig, &eEapType);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_get_eap_type", WifiManagerGetError(nRet));

		if(eEapType != eWifiManagerEapType[nEnumCounter])
		{
			FPRINTF("[%s:%d] returned value of eEapType is not as set!!\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] returned value of eEapType is not as set!!", __FILE__, __LINE__);
			return 1;
		}
	}

	return 0;
}


//& purpose: Sets/Gets access point eap auth type from configuration.
//& type: auto
/**
* @testcase				ITc_wifi_manager_config_set_get_eap_auth_type_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets access point eap auth type from configuration.
* @apicovered			wifi_manager_config_set_eap_auth_type, wifi_manager_config_get_eap_auth_type
* @passcase				When  wifi_manager_config_set_eap_auth_type, wifi_manager_config_get_eap_auth_type API returns 0
* @failcase				If wifi_manager_config_set_eap_auth_type/wifi_manager_config_get_eap_auth_type returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_config_set_get_eap_auth_type_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_eap_auth_type_e eAutType;
	int nRet = 0;

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

	for ( nEnumCounter=0;nEnumCounter<nEnumSize;nEnumCounter++)
	{
		//Target API
		nRet = wifi_manager_config_set_eap_auth_type(g_hWifiConfig, eWifiManagerEapAuthType[nEnumCounter] );
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_set_eap_auth_type", WifiManagerGetError(nRet));

		//Target API
		nRet = wifi_manager_config_get_eap_auth_type(g_hWifiConfig, &eAutType);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_get_eap_auth_type", WifiManagerGetError(nRet));

		if(eAutType != eWifiManagerEapAuthType[nEnumCounter])
		{
			FPRINTF("[%s:%d] returned value of eAutType is not as set!!\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] returned value of eAutType is not as set!!", __FILE__, __LINE__);
			return 1;
		}
	}

	return 0;
}

//& purpose: Sets/Gets access point subject match from configuration.
//& type: auto
/**
* @testcase				ITc_wifi_manager_config_set_get_eap_subject_match_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Sets/Gets access point subject match from configuration.
* @apicovered			wifi_manager_config_set_eap_subject_match, wifi_manager_config_get_eap_subject_match
* @passcase				When  wifi_manager_config_set_eap_subject_match, wifi_manager_config_get_eap_subject_match API returns 0
* @failcase				If  wifi_manager_config_set_eap_subject_match, wifi_manager_config_get_eap_subject_match returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_config_set_get_eap_subject_match_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *pSubjectMatch = NULL;

	int nRet = wifi_manager_config_set_eap_subject_match(g_hWifiConfig, WIFI_CONFIG_SUBJECT_MATCH);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_set_eap_subject_match", WifiManagerGetError(nRet));

	nRet =  wifi_manager_config_get_eap_subject_match(g_hWifiConfig, &pSubjectMatch);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_get_eap_subject_match", WifiManagerGetError(nRet));

	if(strcmp(WIFI_CONFIG_SUBJECT_MATCH, pSubjectMatch) != 0)
	{
		FPRINTF("[%s:%d] returned value of pSubjectMatch is not matched to set!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] returned value of pSubjectMatch is not matched to set!!", __FILE__, __LINE__);
		FREE_MEMORY(pSubjectMatch);
		return 1;
	}
	FREE_MEMORY(pSubjectMatch);

	return 0;
}
//& purpose: Sets/Gets the private key file of EAP.
//& type: auto
/**
* @testcase				ITc_wifi_manager_config_set_get_eap_private_key_info_p
* @since				5.0
* @author				SRID(awadhesh1.s)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @scenario				Sets/Gets the private key file of EAP.
* @apicovered				wifi_manager_config_set_eap_private_key_info, wifi_manager_config_get_eap_private_key_file
* @passcase				returns 0
* @failcase				returns non zero value
* @precondition			NA
* @postcondition		NA
*/


int ITc_wifi_manager_config_set_get_eap_private_key_info_p(void)
{
	START_TEST_CHECK_INITIALIZE;
	char *pszfile;
	int nRet = WIFI_MANAGER_ERROR_NONE;

	nRet = wifi_manager_config_set_eap_private_key_info(g_hWifiConfig, WIFI_CONFIG_PRIVATE_KEY_FILE, WIFI_CONFIG_PRIVATE_KEY);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_set_eap_private_key", WifiManagerGetError(nRet));

	nRet = wifi_manager_config_get_eap_private_key_file(g_hWifiConfig, &pszfile);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_config_get_eap_private_key_file", WifiManagerGetError(nRet));

	if(strncmp(pszfile,WIFI_CONFIG_PRIVATE_KEY_FILE,sizeof(WIFI_CONFIG_PRIVATE_KEY_FILE)) != 0 )
	{
		FPRINTF("[%s:%d] returned value of Private key File is not as set!! file name = %s\\n", __FILE__, __LINE__,pszfile);
		dlog_print(DLOG_ERROR, "NativeTCT","[%s:%d] returned value of Private key File is not as set!!", __FILE__, __LINE__);
		return 1;
	}
	FREE_MEMORY(pszfile);
	return 0;
}

/** @} */


/**
* @testcase				ITc_wifi_manager_config_set_get_ip_config_type_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets access point IP config type from configuration.
* @scenario				Sets and gets access point IP config type from configuration.
* @apicovered				wifi_manager_config_get_ip_config_type, wifi_manager_config_set_ip_config_type
* @passcase				When wifi_manager_config_get_ip_config_type, wifi_manager_config_set_ip_config_type returns 0
* @failcase				If wifi_manager_config_get_ip_config_type, wifi_manager_config_set_ip_config_type returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_wifi_manager_config_set_get_ip_config_type_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	int nRet = 0;

	wifi_manager_address_family_e eAddressFamily[] = {
		WIFI_MANAGER_ADDRESS_FAMILY_IPV4,
		WIFI_MANAGER_ADDRESS_FAMILY_IPV6,
	};

	int nAddressFamilyCountSize = sizeof(eAddressFamily) / sizeof(eAddressFamily[0]);

	wifi_manager_ip_config_type_e eType[] = {
		WIFI_MANAGER_IP_CONFIG_TYPE_STATIC,
		WIFI_MANAGER_IP_CONFIG_TYPE_DYNAMIC,
		WIFI_MANAGER_IP_CONFIG_TYPE_AUTO,
		WIFI_MANAGER_IP_CONFIG_TYPE_FIXED,
	};
	wifi_manager_ip_config_type_e eGetType;

	int nTypeCountSize = sizeof(eType) / sizeof(eType[0]);

	for (int nAddressFamilyCount = 0; nAddressFamilyCount < nAddressFamilyCountSize; nAddressFamilyCount++)
	{

		for (int nTypeCount = 0; nTypeCount < nTypeCountSize; nTypeCount++)
		{
			nRet = wifi_manager_config_set_ip_config_type(g_hWifiConfig, eAddressFamily[nAddressFamilyCount], eType[nTypeCount]);
			PRINT_RESULT(nRet, WIFI_MANAGER_ERROR_NONE, "wifi_manager_config_set_ip_config_type", WifiManagerGetError(nRet));

			nRet = wifi_manager_config_get_ip_config_type(g_hWifiConfig, eAddressFamily[nAddressFamilyCount], &eGetType);
			PRINT_RESULT(nRet, WIFI_MANAGER_ERROR_NONE, "wifi_manager_config_get_ip_config_type", WifiManagerGetError(nRet));
			if (eType[nTypeCount] != eGetType)
			{
				FPRINTF("[Line : %d][%s] %s failed. eType = %d and returned eType = %d\\n", __LINE__, API_NAMESPACE, "wifi_manager_config_get_ip_config_type", eType[nTypeCount], eGetType);
				return 1;
			}
		}
	}


	return 0;
}

/**
* @testcase				ITc_wifi_manager_config_set_get_ip_address_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets access point IP address from configuration.
* @scenario				Sets and gets access point IP address from configuration.
* @apicovered				wifi_manager_config_get_ip_address, wifi_manager_config_set_ip_address
* @passcase				When wifi_manager_config_get_ip_address, wifi_manager_config_set_ip_address returns 0
* @failcase				If wifi_manager_config_get_ip_address, wifi_manager_config_set_ip_address returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_wifi_manager_config_set_get_ip_address_p(void)
{
	START_TEST_CHECK_INITIALIZE;
	char pszSetIpAddress[] = "192.168.11.10";
	char *pszGetIpAddress = NULL;
	int nRet = 0;

	wifi_manager_address_family_e eAddressFamily[] = {
		WIFI_MANAGER_ADDRESS_FAMILY_IPV4,
		WIFI_MANAGER_ADDRESS_FAMILY_IPV6,
	};

	int nAddressFamilyCountSize = sizeof(eAddressFamily) / sizeof(eAddressFamily[0]);

	for (int nAddressFamilyCount = 0; nAddressFamilyCount < nAddressFamilyCountSize; nAddressFamilyCount++)
	{

		nRet = wifi_manager_config_set_ip_address(g_hWifiConfig, eAddressFamily[nAddressFamilyCount], pszSetIpAddress);
		PRINT_RESULT(nRet, WIFI_MANAGER_ERROR_NONE, "wifi_manager_config_set_ip_address", WifiManagerGetError(nRet));

		nRet = wifi_manager_config_get_ip_address(g_hWifiConfig, eAddressFamily[nAddressFamilyCount], &pszGetIpAddress);
		PRINT_RESULT(nRet, WIFI_MANAGER_ERROR_NONE, "wifi_manager_config_get_ip_address", WifiManagerGetError(nRet));
		CHECK_HANDLE(pszGetIpAddress, "wifi_manager_config_get_ip_address");

		if( strncmp(pszGetIpAddress, pszSetIpAddress, sizeof(pszSetIpAddress)) !=0)
		{
			FPRINTF("[Line : %d][%s] %s failed. mismatch in Expected: %s and returned: %s\\n", __LINE__, API_NAMESPACE, "wifi_manager_config_set_get_ip_address", pszSetIpAddress, pszGetIpAddress);
			FREE_MEMORY(pszGetIpAddress);
			return 1;
		}
		FREE_MEMORY(pszGetIpAddress);
	}
	return 0;
}

/**
* @testcase				ITc_wifi_manager_config_set_get_subnet_mask_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets access point subnet mask from configuration.
* @scenario				Sets and gets access point subnet mask from configuration.
* @apicovered				wifi_manager_config_get_subnet_mask, wifi_manager_config_set_subnet_mask
* @passcase				When wifi_manager_config_get_subnet_mask, wifi_manager_config_set_subnet_mask returns 0
* @failcase				If wifi_manager_config_get_subnet_mask, wifi_manager_config_set_subnet_mask returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_wifi_manager_config_set_get_subnet_mask_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char pszSetSubnetMask[] = "255.255.255.0";
	char *pszGetSubnetMask = NULL;
	int nRet = 0;

	wifi_manager_address_family_e eAddressFamily[] = {
		WIFI_MANAGER_ADDRESS_FAMILY_IPV4,
		//WIFI_MANAGER_ADDRESS_FAMILY_IPV6   // This API is not supported for WIFI_MANAGER_ADDRESS_FAMILY_IPV6
	};

	int nAddressFamilyCountSize = sizeof(eAddressFamily) / sizeof(eAddressFamily[0]);

	for (int nAddressFamilyCount = 0; nAddressFamilyCount < nAddressFamilyCountSize; nAddressFamilyCount++)
	{

		nRet = wifi_manager_config_set_subnet_mask(g_hWifiConfig, eAddressFamily[nAddressFamilyCount], pszSetSubnetMask);
		PRINT_RESULT(nRet, WIFI_MANAGER_ERROR_NONE, "wifi_manager_config_set_subnet_mask", WifiManagerGetError(nRet));

		nRet = wifi_manager_config_get_subnet_mask(g_hWifiConfig, eAddressFamily[nAddressFamilyCount], &pszGetSubnetMask);
		PRINT_RESULT(nRet, WIFI_MANAGER_ERROR_NONE, "wifi_manager_config_get_subnet_mask", WifiManagerGetError(nRet));
		CHECK_HANDLE(pszGetSubnetMask, "wifi_manager_config_get_subnet_mask");

		if(strncmp(pszGetSubnetMask, pszSetSubnetMask, sizeof(pszSetSubnetMask))!=0)
		{
			FPRINTF("[Line : %d][%s] %s failed. mismathc in expected: %s and returned: %s \\n", __LINE__, API_NAMESPACE, "wifi_manager_config_set_get_subnet_mask", pszSetSubnetMask, pszGetSubnetMask);
			FREE_MEMORY(pszGetSubnetMask);
			return 1;
		}
		FREE_MEMORY(pszGetSubnetMask);
	}


	return 0;
}

/**
* @testcase				ITc_wifi_manager_config_set_get_prefix_length_p
* @since_tizen				5.0
* @author				SRID(awadhesh1.s)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets the network prefix length from configuration.
* @scenario				Sets and gets the network prefix length from configuration.
* @apicovered				wifi_manager_config_get_prefix_length, wifi_manager_config_set_prefix_length
* @passcase				When wifi_manager_config_get_prefix_length, wifi_manager_config_set_prefix_length returns 0
* @failcase				If wifi_manager_config_get_prefix_length, wifi_manager_config_set_prefix_length returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_wifi_manager_config_set_get_prefix_length_p(void)
{
	START_TEST_CHECK_INITIALIZE;
	int nPrefixLen = PREFIX_LENGTH;
	int nGetPrefixLen;
	int nRet = 0;
	wifi_manager_address_family_e eAddressFamily[] = {
		// WIFI_MANAGER_ADDRESS_FAMILY_IPV4,    //For IPV4 subnet mask will be called to set the prefix length.This API is not supported for IPV4.
		WIFI_MANAGER_ADDRESS_FAMILY_IPV6,
	};

	int nAddressFamilyCountSize = sizeof(eAddressFamily) / sizeof(eAddressFamily[0]);

	for(int nCount = 1 ; nCount <= 4 ; nCount++)
	{
		for(int  nAddressFamilyCount = 0; nAddressFamilyCount < nAddressFamilyCountSize; nAddressFamilyCount++)
		{
			nRet = wifi_manager_config_set_prefix_length(g_hWifiConfig,  eAddressFamily[nAddressFamilyCount], nCount*nPrefixLen);
			PRINT_RESULT(nRet, WIFI_MANAGER_ERROR_NONE, "wifi_manager_config_get_prefix_length", WifiManagerGetError(nRet));

			nRet = wifi_manager_config_get_prefix_length(g_hWifiConfig,  eAddressFamily[nAddressFamilyCount], &nGetPrefixLen);
			PRINT_RESULT(nRet, WIFI_MANAGER_ERROR_NONE, "wifi_manager_config_get_prefix_length", WifiManagerGetError(nRet));

			if (nCount*nPrefixLen != nGetPrefixLen)
			{
				FPRINTF("[Line : %d][%s] %s failed. nPrefixLen = %d and returned PrefixLength = %d \\n", __LINE__, API_NAMESPACE, "wifi_manager_config_get_prefix_length", nCount* nPrefixLen, nGetPrefixLen);
				return 1;
			}
		}
	}
	return 0;
}

/**
* @testcase				ITc_wifi_manager_config_set_get_gateway_address_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets access point gateway address from configuration.
* @scenario				Sets and gets access point gateway address from configuration.
* @apicovered				wifi_manager_config_get_gateway_address, wifi_manager_config_set_gateway_address
* @passcase				When wifi_manager_config_get_gateway_address, wifi_manager_config_set_gateway_address returns 0
* @failcase				If wifi_manager_config_get_gateway_address, wifi_manager_config_set_gateway_address returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_wifi_manager_config_set_get_gateway_address_p(void)
{
	START_TEST_CHECK_INITIALIZE;
	char pszSetGatewayAddress[] = "192.168.11.1";
	char *pszGetGatewayAddress = NULL;
	int nRet = 0;

	wifi_manager_address_family_e eAddressFamily[] = {
		WIFI_MANAGER_ADDRESS_FAMILY_IPV4,
		// WIFI_MANAGER_ADDRESS_FAMILY_IPV6    // This api is not supported for WIFI_MANAGER_ADDRESS_FAMILY_IPV6.
	};

	int nAddressFamilyCountSize = sizeof(eAddressFamily) / sizeof(eAddressFamily[0]);

	for (int nAddressFamilyCount = 0; nAddressFamilyCount < nAddressFamilyCountSize; nAddressFamilyCount++)
	{

		nRet = wifi_manager_config_set_gateway_address(g_hWifiConfig, eAddressFamily[nAddressFamilyCount], pszSetGatewayAddress);
		PRINT_RESULT(nRet, WIFI_MANAGER_ERROR_NONE, "wifi_manager_config_set_gateway_address", WifiManagerGetError(nRet));

		nRet = wifi_manager_config_get_gateway_address(g_hWifiConfig, eAddressFamily[nAddressFamilyCount], &pszGetGatewayAddress);
		PRINT_RESULT(nRet, WIFI_MANAGER_ERROR_NONE, "wifi_manager_config_get_gateway_address", WifiManagerGetError(nRet));
		CHECK_HANDLE(pszGetGatewayAddress, "wifi_manager_config_get_gateway_address");

		if( strncmp(pszGetGatewayAddress, pszSetGatewayAddress, sizeof (pszSetGatewayAddress)) != 0)
		{
			FPRINTF("[Line : %d][%s] %s failed. mismatch in expected: %s and returned: %s\\n", __LINE__, API_NAMESPACE, "wifi_manager_config_set_get_gateway_address", pszSetGatewayAddress, pszGetGatewayAddress);
			FREE_MEMORY(pszGetGatewayAddress);
			return 1;
		}
		FREE_MEMORY(pszGetGatewayAddress);
	}


	return 0;
}

/**
* @testcase				ITc_wifi_manager_config_set_get_dns_config_type_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets access point dns config type from configuration.
* @scenario				Sets and gets access point dns config type from configuration.
* @apicovered				wifi_manager_config_get_dns_config_type, wifi_manager_config_set_dns_config_type
* @passcase				When wifi_manager_config_get_dns_config_type, wifi_manager_config_set_dns_config_type returns 0
* @failcase				If wifi_manager_config_get_dns_config_type, wifi_manager_config_set_dns_config_type returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_wifi_manager_config_set_get_dns_config_type_p(void)
{
	START_TEST_CHECK_INITIALIZE;
	int nRet = 0;

	wifi_manager_address_family_e eAddressFamily[] = {
		WIFI_MANAGER_ADDRESS_FAMILY_IPV4,
		WIFI_MANAGER_ADDRESS_FAMILY_IPV6,
	};

	int nAddressFamilyCountSize = sizeof(eAddressFamily) / sizeof(eAddressFamily[0]);

	wifi_manager_dns_config_type_e eType[] = {
		WIFI_MANAGER_DNS_CONFIG_TYPE_STATIC,
		WIFI_MANAGER_DNS_CONFIG_TYPE_DYNAMIC,
	};
	wifi_manager_dns_config_type_e eGetType;
	int nTypeCountSize = sizeof(eType) / sizeof(eType[0]);

	for (int nAddressFamilyCount = 0; nAddressFamilyCount < nAddressFamilyCountSize; nAddressFamilyCount++)
	{

		for (int nTypeCount = 0; nTypeCount < nTypeCountSize; nTypeCount++)
		{

			nRet = wifi_manager_config_set_dns_config_type(g_hWifiConfig, eAddressFamily[nAddressFamilyCount], eType[nTypeCount]);
			PRINT_RESULT(nRet, WIFI_MANAGER_ERROR_NONE, "wifi_manager_config_set_dns_config_type", WifiManagerGetError(nRet));

			nRet = wifi_manager_config_get_dns_config_type(g_hWifiConfig, eAddressFamily[nAddressFamilyCount], &eGetType);
			PRINT_RESULT(nRet, WIFI_MANAGER_ERROR_NONE, "wifi_manager_config_get_dns_config_type", WifiManagerGetError(nRet));
			if (eType[nTypeCount] != eGetType)
			{
				FPRINTF("[Line : %d][%s] %s failed. eType = %d and returned eType = %d \\n", __LINE__, API_NAMESPACE, "wifi_manager_config_get_dns_config_type", eType[nTypeCount], eGetType);
				return 1;
			}
		}
	}


	return 0;
}

/**
* @testcase				ITc_wifi_manager_config_set_get_dns_address_p
* @since_tizen				5.0
* @author				SRID(p.chauhan)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @description				Sets and gets access point dns address from configuration.
* @scenario				Sets and gets access point dns address from configuration.
* @apicovered				wifi_manager_config_get_dns_address, wifi_manager_config_set_dns_address
* @passcase				When wifi_manager_config_get_dns_address, wifi_manager_config_set_dns_address returns 0
* @failcase				If wifi_manager_config_get_dns_address, wifi_manager_config_set_dns_address returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_wifi_manager_config_set_get_dns_address_p(void)
{
	START_TEST_CHECK_INITIALIZE;
	int nOrder[2] = {1,2};
	char pszSetDnsAddress[2][12] = {"192.168.11.1", "192.168.11.2"};
	int nRet = 0;
	char *pszGetdnsAddress= NULL;

	wifi_manager_address_family_e eAddressFamily[] = {
		WIFI_MANAGER_ADDRESS_FAMILY_IPV4,
		// WIFI_MANAGER_ADDRESS_FAMILY_IPV6	// This API is not supported for WIFI_MANAGER_ADDRESS_FAMILY_IPV6
	};

	int nAddressFamilyCountSize = sizeof(eAddressFamily) / sizeof(eAddressFamily[0]);
	for(int nOrderIndex = 0; nOrderIndex < 2; nOrderIndex++)
	{
		for (int nAddressFamilyCount = 0; nAddressFamilyCount < nAddressFamilyCountSize; nAddressFamilyCount++)
		{
			nRet = wifi_manager_config_set_dns_address(g_hWifiConfig, nOrder[nOrderIndex], eAddressFamily[nAddressFamilyCount], pszSetDnsAddress[nOrderIndex]);
			PRINT_RESULT(nRet, WIFI_MANAGER_ERROR_NONE, "wifi_manager_config_set_dns_address", WifiManagerGetError(nRet));
			nRet = wifi_manager_config_get_dns_address(g_hWifiConfig, nOrder[nOrderIndex], eAddressFamily[nAddressFamilyCount], &pszGetdnsAddress);
			PRINT_RESULT(nRet, WIFI_MANAGER_ERROR_NONE, "wifi_manager_config_get_dns_address", WifiManagerGetError(nRet));
			CHECK_HANDLE(pszGetdnsAddress, "wifi_manager_config_get_dns_address");

			if( strncmp(pszSetDnsAddress[nOrderIndex], pszGetdnsAddress, sizeof(pszSetDnsAddress[nOrderIndex])) != 0)
			{
				FPRINTF("[Line : %d][%s] %s failed. mismatch in expected: %s and returned: %s\\n", __LINE__,API_NAMESPACE, "wifi_manager_config_set_get_dns_address", pszSetDnsAddress[nOrderIndex], pszGetdnsAddress);
				FREE_MEMORY(pszGetdnsAddress);
				return 1;
			}
			FREE_MEMORY(pszGetdnsAddress);
		}
	}
	return 0;
}

