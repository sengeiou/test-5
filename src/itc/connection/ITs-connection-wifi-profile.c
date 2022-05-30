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
int g_nConnectionWifiErrorCount1, g_nConnectionWifiErrorCount2;
int g_nConnectionWifiPreconditionError = 0;
connection_h g_hConenctionHandleWifi;
connection_profile_h g_hConnectionProfileHandleWifi;
char* g_pszConnectionWifiProfileName = "WifiConnectionProfile";


void ITs_connection_wifi_profile_startup(void)
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
	bool bEthernetFeatureSupported = TCTCheckSystemInfoFeatureSupported(ETHERNET_FEATURE, API_NAMESPACE);
	bool bBtFeatureSupported = TCTCheckSystemInfoFeatureSupported(TETHERING_BLUETOOTH_FEATURE, API_NAMESPACE);



	g_nConnectionWifiErrorCount1 = 0;
	g_nConnectionWifiErrorCount2 = 0;
	g_nConnectionWifiPreconditionError = 0;
	g_hConenctionHandleWifi = NULL;
	g_hConnectionProfileHandleWifi = NULL;

	int nRet = connection_create(&g_hConenctionHandleWifi);

	if ( false == bTelFeatureSupported && false == bWifiFeatureSupported && false == bBtFeatureSupported && false == bEthernetFeatureSupported)
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

	if ( (nRet != CONNECTION_ERROR_NONE ) || (g_hConenctionHandleWifi == NULL) )
	{
		g_nConnectionWifiPreconditionError = 1;
		g_hConenctionHandleWifi = NULL;
		return;
	}

	if ( ConnectionManager_get_wifi_profile(g_hConenctionHandleWifi, &g_hConnectionProfileHandleWifi) == 0 )
	{
		if ( false == bWifiFeatureSupported) 
		{
			if ( g_hConnectionProfileHandleWifi == NULL )
			{
				FPRINTF("[Line : %d][%s] Wifi profile handle is NULL, unsupported wifi feature\\n", __LINE__, API_NAMESPACE);
				g_bFeatureNotSupported = true;
			}
			else
			{
				FPRINTF("[Line : %d][%s] Wifi profile handle is not NULL, mismatch for unsupported wifi feature\\n", __LINE__, API_NAMESPACE);
				g_bFeatureMismatch = true;
			}
			return;
		}
		else
		{
			g_nConnectionWifiPreconditionError = 1;
			FPRINTF("[Line : %d][%s] Startup failed on getting wifi profile\\n", __LINE__, API_NAMESPACE);
			return;
		}
	}

	if ( g_hConnectionProfileHandleWifi == NULL )
	{
		g_nConnectionWifiPreconditionError = 1;
		FPRINTF("[Line : %d][%s] Startup failed on create wifi profile :: NULL\\n", __LINE__, API_NAMESPACE);
		return;
	}
}

void ITs_connection_wifi_profile_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Connection_p\\n", __LINE__, API_NAMESPACE);
#endif

	// Null initialization of pointer
	int nRet = 0;
	if ( g_nConnectionWifiPreconditionError == 0 && g_bFeatureSupported == true )
	{
		if ( g_hConnectionProfileHandleWifi != NULL )
		{
			nRet = connection_profile_destroy(g_hConnectionProfileHandleWifi);
			if ( nRet != CONNECTION_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] connection_profile_destroy failed on post condition error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			}
		}
		nRet = connection_destroy(g_hConenctionHandleWifi);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] connection_destroy failed on post condition error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
		}
	}

	g_nConnectionWifiPreconditionError = 0;
	g_hConenctionHandleWifi = NULL;
	g_hConnectionProfileHandleWifi = NULL;
}

/** @addtogroup itc-connection-wifi-profile-testcases
*  @brief 		Integration testcases for module connection-wifi-profile
*  @ingroup 	itc-connection-wifi-profile
*  @{
*/

//& purpose: To check BSSID on wifi connection profile
//& type : auto
/**
* @testcase 			ITc_connection_profile_get_wifi_bssid_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check BSSID
* @scenario				Call API to get BSSID
* @apicovered			connection_profile_get_wifi_bssid
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Wifi data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_get_wifi_bssid_p(void)
{
	START_TEST;

	if ( g_nConnectionWifiPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_get_wifi_bssid_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char *pszFindBSSID = NULL;
	int nRet = connection_profile_get_wifi_bssid(g_hConnectionProfileHandleWifi, &pszFindBSSID);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_wifi_bssid", ConnectionGetError(nRet));

	CHECK_VALUE_STRING(pszFindBSSID, "connection_profile_get_wifi_essid");
	FPRINTF("[Line : %d][%s] Find BSSID : %s\\n", __LINE__, API_NAMESPACE, pszFindBSSID);
	FREE_MEMORY(pszFindBSSID);

	return 0;
}

//& purpose: To check ESSID on wifi connection profile
//& type : auto
/**
* @testcase 			ITc_connection_profile_get_wifi_essid_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check ESSID
* @scenario				Call API to get ESSID
* @apicovered			connection_profile_get_wifi_essid
* @passcase				When APIs return CONNECTION_ERROR_NONE
* @failcase				When APIs not return CONNECTION_ERROR_NONE
* @precondition			Wifi data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_get_wifi_essid_p(void)
{
	START_TEST;

	if ( g_nConnectionWifiPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_get_wifi_essid_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char *pszFindESSID = NULL;
	int nRet = connection_profile_get_wifi_essid(g_hConnectionProfileHandleWifi, &pszFindESSID);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_wifi_essid", ConnectionGetError(nRet));

	CHECK_VALUE_STRING(pszFindESSID, "connection_profile_get_wifi_essid");
	FREE_MEMORY(pszFindESSID);

	return 0;
}

//& purpose: To check frequency of wifi connection profile
//& type : auto
/**
* @testcase 			ITc_connection_profile_get_wifi_frequency_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check frequency of wifi connection profile
* @scenario				Call API to get frequency of wifi profile
* @apicovered			connection_profile_get_wifi_frequency
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Wifi data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_get_wifi_frequency_p(void)
{
	START_TEST;

	if ( g_nConnectionWifiPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_get_wifi_frequency_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nfindFrequency = -1;
	int nRet = connection_profile_get_wifi_frequency(g_hConnectionProfileHandleWifi, &nfindFrequency);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_wifi_frequency", ConnectionGetError(nRet));
	if ( nfindFrequency == -1 )
	{
		FPRINTF("[Line : %d][%s] connection_profile_get_wifi_frequency failed, returned Frequency:: -1\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: To check max speed of wifi connection profile
//& type : auto
/**
* @testcase 			ITc_connection_profile_get_wifi_max_speed_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check max speed of wifi connection profile
* @scenario				Call API to get max speed of wifi profile
* @apicovered			connection_profile_get_wifi_max_speed
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Wifi data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_get_wifi_max_speed_p(void)
{
	START_TEST;

	if ( g_nConnectionWifiPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_get_wifi_max_speed_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nfindSpeed = -1;
	int nRet = connection_profile_get_wifi_max_speed(g_hConnectionProfileHandleWifi, &nfindSpeed);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_wifi_max_speed", ConnectionGetError(nRet));
	if ( nfindSpeed == -1 )
	{
		FPRINTF("[Line : %d][%s] connection_profile_get_wifi_max_speed failed, returned Max Speed:: -1\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: To check RSSI of wifi connection profile
//& type : auto
/**
* @testcase 			ITc_connection_profile_get_wifi_max_speed_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check RSSI of wifi connection profile
* @scenario				Call API to get RSSI of wifi profile
* @apicovered			connection_profile_get_wifi_rssi
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Wifi data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_get_wifi_rssi_p(void)
{
	START_TEST;

	if ( g_nConnectionWifiPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_get_wifi_rssi_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nfindRSSI = -1;
	int nRet = connection_profile_get_wifi_rssi(g_hConnectionProfileHandleWifi, &nfindRSSI);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_wifi_rssi", ConnectionGetError(nRet));
	if ( nfindRSSI == -1 )
	{
		FPRINTF("[Line : %d][%s] connection_profile_get_wifi_rssi failed, returned RSSI:: -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: To check security type of wifi connection profile
//& type : auto
/**
* @testcase 			ITc_connection_profile_get_wifi_security_type_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check security type of wifi connection profile
* @scenario				Call API to get security type of wifi profile
* @apicovered			connection_profile_get_wifi_security_type
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Wifi data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_get_wifi_security_type_p(void)
{
	START_TEST;

	if ( g_nConnectionWifiPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_get_wifi_security_type_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	connection_wifi_security_type_e eFindWifiSecurityType = -1;
	int nRet = connection_profile_get_wifi_security_type(g_hConnectionProfileHandleWifi, &eFindWifiSecurityType);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_wifi_security_type", ConnectionGetError(nRet));
	if ( (eFindWifiSecurityType < 0) || (eFindWifiSecurityType > 4) )
	{
		FPRINTF("[Line : %d][%s] connection_profile_get_wifi_security_type failed, returned Security Type :: Unknown\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: To check encryption type of wifi connection profile
//& type : auto
/**
* @testcase 			ITc_connection_profile_get_wifi_encryption_type_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check encryption type of wifi connection profile
* @scenario				Call API to get security type of wifi profile
* @apicovered			connection_profile_get_wifi_encryption_type
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Wifi data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_get_wifi_encryption_type_p(void)
{
	START_TEST;

	if ( g_nConnectionWifiPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_get_wifi_encryption_type_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	connection_wifi_encryption_type_e eFindWifiEncryptionType = -1;
	int nRet = connection_profile_get_wifi_encryption_type(g_hConnectionProfileHandleWifi, &eFindWifiEncryptionType);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_wifi_encryption_type", ConnectionGetError(nRet));
	if ( eFindWifiEncryptionType < 0)
	{
		FPRINTF("[Line: %d][%s] connection_profile_get_wifi_encryption_type failed, returned Encryption Type :: Unknown\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: To check passphrase is required
//& type : auto
/**
* @testcase 			ITc_connection_profile_is_wifi_passphrase_required_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Check passphrase is required
* @scenario				Call API to passphrase require
* @apicovered			connection_profile_is_wifi_passphrase_required
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Wifi data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_is_wifi_passphrase_required_p(void)
{
	START_TEST;

	if ( g_nConnectionWifiPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_is_wifi_passphrase_required_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	bool bIsPassPhraseRequired;
	int nRet = connection_profile_is_wifi_passphrase_required(g_hConnectionProfileHandleWifi, &bIsPassPhraseRequired);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_is_wifi_passphrase_required", ConnectionGetError(nRet));
	FPRINTF("[Line : %d][%s] connection_profile_is_wifi_passphrase_required returned = %s\\n", __LINE__, API_NAMESPACE, bIsPassPhraseRequired ? "true": "false");

	return 0;
}

//& purpose: To check WPS supported on wifi connection profile
//& type : auto
/**
* @testcase 			ITc_connection_profile_is_wifi_wps_supported_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Check WPS supported on wifi connection profile
* @scenario				Call API to check wps supported on wifi connection profile
* @apicovered			connection_profile_is_wifi_wps_supported
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Wifi data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_is_wifi_wps_supported_p(void)
{
	START_TEST;

	if ( g_nConnectionWifiPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_is_wifi_wps_supported_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	bool bWPSSupported;
	int nRet = connection_profile_is_wifi_wps_supported (g_hConnectionProfileHandleWifi, &bWPSSupported);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_is_wifi_wps_supported", ConnectionGetError(nRet));
	FPRINTF("[Line : %d][%s] connection_profile_is_wifi_wps_supported returned = %s\\n", __LINE__, API_NAMESPACE, bWPSSupported ? "true": "false");

	return 0;
}

//& purpose: To check set the passphrase of Wi-Fi WPA
//& type : auto
/**
* @testcase 			ITc_connection_profile_set_wifi_passphrase_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check sTo check set the passphrase of Wi-Fi WPA
* @scenario				Call API to set the passphrase of Wi-Fi WPA
* @apicovered			connection_profile_set_wifi_passphrase
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Wifi data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_set_wifi_passphrase_p(void)
{
	START_TEST;

	if ( g_nConnectionWifiPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_set_wifi_passphrase_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char *pszSetPassPhrase = "1234";
	int nRet = connection_profile_set_wifi_passphrase (g_hConnectionProfileHandleWifi, pszSetPassPhrase);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_set_wifi_passphrase", ConnectionGetError(nRet));

	return 0;
}

//& purpose: To check update existing profile
//& type : auto
/**
* @testcase 			ITc_connection_update_profile_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check update existing profile
* @scenario				Call API to update existing profile
* @apicovered			connection_update_profile
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			Wifi data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_update_profile_p(void)
{
	START_TEST;

	if ( g_nConnectionWifiPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_update_profile_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = connection_update_profile(g_hConenctionHandleWifi, g_hConnectionProfileHandleWifi);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_update_profile", ConnectionGetError(nRet));
	sleep(1);

	return 0;
}

//& purpose: To check state of wifi
//& type : auto
/**
* @testcase 			ITc_connection_get_wifi_state_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check state of wifi
* @scenario				Call API to get state of wifi
* @apicovered			connection_get_wifi_state
* @passcase				When API return CONNECTION_ERROR_NONE
* @failcase				When API not return CONNECTION_ERROR_NONE
* @precondition			wifi must be turn-off/disabled.
* @postcondition		None
*/
int ITc_connection_get_wifi_state_p(void)
{
	START_TEST;

	if ( g_nConnectionWifiPreconditionError == 1 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_get_wifi_state_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	connection_wifi_state_e eFindWifiState = -1;
	int nRet = connection_get_wifi_state(g_hConenctionHandleWifi, &eFindWifiState);
	PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_get_wifi_state", ConnectionGetError(nRet));
	if ( eFindWifiState == -1 )
	{
		FPRINTF("[Line : %d][%s] connection_get_wifi_state failed, returned invalid wifi state\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}



//& purpose: Gets IPv6 state
//& type : auto
/**
* @testcase 		ITc_connection_profile_get_ipv6_state_p
* @since_tizen		4.0
* @author            	SRID(maneesha.k)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @description		To get IPv6 state
* @scenario		Invoking connection_profile_get_ipv6_state with valid parameter.
* @apicovered		connection_profile_get_ipv6_state
* @passcase		When connection_profile_get_ipv6_state return CONNECTION_ERROR_NONE
* @failcase		When connection_profile_get_ipv6_state does not return CONNECTION_ERROR_NONE
* @precondition		Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_get_ipv6_state_p(void)
{

	START_TEST;

	if ( g_nConnectionWifiPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_get_ipv6_state_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	connection_profile_state_e state;
	int nRet = CONNECTION_ERROR_NONE;
	bool bWifiFeatureSupported = TCTCheckSystemInfoFeatureSupported(WIFI_FEATURE, API_NAMESPACE);

	if(bWifiFeatureSupported)
	{
		nRet = connection_profile_get_ipv6_state(g_hConnectionProfileHandleWifi, &state);
		PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_ipv6_state", ConnectionGetError(nRet));
	}
	else
	{
		nRet = connection_profile_get_ipv6_state(g_hConnectionProfileHandleWifi, &state);
		PRINT_RESULT(CONNECTION_ERROR_NOT_SUPPORTED, nRet, "connection_profile_get_ipv6_state", ConnectionGetError(nRet));
	}
	return 0;
}

//& purpose: Sets and Gets prefix length
//& type : auto
/**
* @testcase 		ITc_connection_profile_set_get_prefix_length_p
* @since_tizen		4.0
* @author            	SRID(maneesha.k)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @description		Sets and Gets prefix length
* @scenario		Invoking connection_profile_set_prefix_length and connection_profile_get_prefix_length with valid parameter
* @apicovered		connection_profile_set_prefix_length, connection_profile_get_prefix_length
* @passcase		When APIs return CONNECTION_ERROR_NONE and the set prefix length matches the retrieved prefix length
* @failcase		When APIs do not return CONNECTION_ERROR_NONE and the set prefix length does not match the retrieved prefix length
* @precondition		Cellular data connection must be exist in the testing device
* @postcondition		None
*/
int ITc_connection_profile_set_get_prefix_length_p(void)
{
	START_TEST;

	if ( g_nConnectionWifiPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_set_get_prefix_length_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}


	int setLength = 32, getLength = 0;
	int nRet = CONNECTION_ERROR_NONE;
	bool bWifiFeatureSupported = TCTCheckSystemInfoFeatureSupported(WIFI_FEATURE, API_NAMESPACE);

	if(bWifiFeatureSupported)
	{

		nRet = connection_profile_set_prefix_length(g_hConnectionProfileHandleWifi, CONNECTION_ADDRESS_FAMILY_IPV4, setLength);
	        PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_prefix_length(IPV4)", ConnectionGetError(nRet));

		nRet = connection_profile_get_prefix_length(g_hConnectionProfileHandleWifi, CONNECTION_ADDRESS_FAMILY_IPV4, &getLength);
		PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_prefix_length(IPV4)", ConnectionGetError(nRet));

		if(setLength != getLength)
		{
			FPRINTF("[Line : %d][%s] Error in ITc_connection_profile_set_get_prefix_length_p(IPV4) setLength(%d) does not match getLength(%d) \\n", __LINE__, API_NAMESPACE, setLength, getLength);
			return 1;
		}
		nRet = connection_profile_set_prefix_length(g_hConnectionProfileHandleWifi, CONNECTION_ADDRESS_FAMILY_IPV6, setLength);
		PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_prefix_length(IPV6)", ConnectionGetError(nRet));

		nRet = connection_profile_get_prefix_length(g_hConnectionProfileHandleWifi, CONNECTION_ADDRESS_FAMILY_IPV6, &getLength);
		PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_prefix_length(IPV6)", ConnectionGetError(nRet));

		if(setLength != getLength)
		{
			FPRINTF("[Line : %d][%s] Error in ITc_connection_profile_set_get_prefix_length_p(IPV6) setLength(%d) does not match getLength(%d) \\n", __LINE__, API_NAMESPACE, setLength, getLength);
			return 1;
		}
	}
	else
	{
		nRet = connection_profile_get_prefix_length(g_hConnectionProfileHandleWifi, CONNECTION_ADDRESS_FAMILY_IPV4, &getLength);
		PRINT_RESULT(CONNECTION_ERROR_NOT_SUPPORTED, nRet, "connection_profile_get_prefix_length(IPV4)", ConnectionGetError(nRet));

		nRet = connection_profile_get_prefix_length(g_hConnectionProfileHandleWifi, CONNECTION_ADDRESS_FAMILY_IPV6, &getLength);
		PRINT_RESULT(CONNECTION_ERROR_NOT_SUPPORTED, nRet, "connection_profile_get_prefix_length(IPV6)", ConnectionGetError(nRet));

		nRet = connection_profile_set_prefix_length(g_hConnectionProfileHandleWifi, CONNECTION_ADDRESS_FAMILY_IPV4, setLength);
		PRINT_RESULT(CONNECTION_ERROR_NOT_SUPPORTED, nRet, "connection_profile_set_prefix_length(IPV4)", ConnectionGetError(nRet));

		nRet = connection_profile_set_prefix_length(g_hConnectionProfileHandleWifi, CONNECTION_ADDRESS_FAMILY_IPV6, setLength);
		PRINT_RESULT(CONNECTION_ERROR_NOT_SUPPORTED, nRet, "connection_profile_set_prefix_length(IPV6)", ConnectionGetError(nRet));
	}

    return 0;
}


//& purpose: Sets and Gets DNS configuration type
//& type : auto
/**
* @testcase 		ITc_connection_profile_set_get_dns_config_type_p
* @since_tizen		4.0
* @author            	SRID(maneesha.k)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @description		Sets and Gets DNS configuration type
* @scenario		Invoking connection_profile_set_dns_config_type and connection_profile_get_dns_config_type with valid parameter
* @apicovered		connection_profile_set_dns_config_type, connection_profile_get_dns_config_type
* @passcase		When APIs return CONNECTION_ERROR_NONE and the set DNS configuration type matches the retrieved DNS configuration type
* @failcase		When APIs do not return CONNECTION_ERROR_NONE and the DNS configuration type does not match the retrieved DNS configuration type
* @precondition		Cellular data connection must be exist in the testing device
* @postcondition		None
*/

int ITc_connection_profile_set_get_dns_config_type_p(void)
{
	START_TEST;

	if ( g_nConnectionWifiPreconditionError > 0 )
	{
		FPRINTF("[Line : %d][%s] ITc_connection_profile_set_get_prefix_length_p failed on precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}


	connection_dns_config_type_e setConfigType[] = {CONNECTION_DNS_CONFIG_TYPE_STATIC,
							CONNECTION_DNS_CONFIG_TYPE_DYNAMIC}, getConfigType;
	bool bWifiFeatureSupported = TCTCheckSystemInfoFeatureSupported(WIFI_FEATURE, API_NAMESPACE);
	int nRet = CONNECTION_ERROR_NONE;


	if(bWifiFeatureSupported)
	{
		int enum_counter, enum_size;
		enum_size = sizeof(setConfigType)/sizeof(setConfigType[0]);


		for(enum_counter = 0; enum_counter < enum_size; enum_counter++)
		{

			nRet = connection_profile_set_dns_config_type(g_hConnectionProfileHandleWifi, CONNECTION_ADDRESS_FAMILY_IPV4, setConfigType[enum_counter]);
			PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_prefix_length(IPV4)", ConnectionGetError(nRet));

			nRet = connection_profile_get_dns_config_type(g_hConnectionProfileHandleWifi, CONNECTION_ADDRESS_FAMILY_IPV4, &getConfigType);
			PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_prefix_length(IPV4)", ConnectionGetError(nRet));

			if(setConfigType[enum_counter] != getConfigType)
			{
				FPRINTF("[Line : %d][%s] Error in ITc_connection_profile_set_get_dns_config_type_p(IPV4) setConfigType does not match getConfigType \\n", __LINE__, API_NAMESPACE);
				return 1;
			}

			nRet = connection_profile_set_dns_config_type(g_hConnectionProfileHandleWifi, CONNECTION_ADDRESS_FAMILY_IPV6, setConfigType[enum_counter]);
			PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_prefix_length(IPV6)", ConnectionGetError(nRet));

			nRet = connection_profile_get_dns_config_type(g_hConnectionProfileHandleWifi, CONNECTION_ADDRESS_FAMILY_IPV6, &getConfigType);
			PRINT_RESULT(CONNECTION_ERROR_NONE, nRet, "connection_profile_get_prefix_length(IPV6)", ConnectionGetError(nRet));

			if(setConfigType[enum_counter] != getConfigType)
			{
				FPRINTF("[Line : %d][%s] Error in ITc_connection_profile_set_get_dns_config_type_p(IPV6) setConfigType does not match getConfigType \\n", __LINE__, API_NAMESPACE);
				return 1;
			}
		}
	}
	else
	{
		nRet = connection_profile_get_dns_config_type(g_hConnectionProfileHandleWifi, CONNECTION_ADDRESS_FAMILY_IPV4, &getConfigType);
		PRINT_RESULT(CONNECTION_ERROR_NOT_SUPPORTED, nRet, "connection_profile_get_dns_config_type(IPV4)", ConnectionGetError(nRet));

		nRet = connection_profile_set_dns_config_type(g_hConnectionProfileHandleWifi, CONNECTION_ADDRESS_FAMILY_IPV4, CONNECTION_DNS_CONFIG_TYPE_STATIC);
		PRINT_RESULT(CONNECTION_ERROR_NOT_SUPPORTED, nRet, "connection_profile_set_dns_config_type(IPV4)", ConnectionGetError(nRet));

		nRet = connection_profile_get_dns_config_type(g_hConnectionProfileHandleWifi, CONNECTION_ADDRESS_FAMILY_IPV6, &getConfigType);
		PRINT_RESULT(CONNECTION_ERROR_NOT_SUPPORTED, nRet, "connection_profile_get_dns_config_type(IPV6)", ConnectionGetError(nRet));

		nRet = connection_profile_set_dns_config_type(g_hConnectionProfileHandleWifi, CONNECTION_ADDRESS_FAMILY_IPV6, CONNECTION_DNS_CONFIG_TYPE_STATIC);
		PRINT_RESULT(CONNECTION_ERROR_NOT_SUPPORTED, nRet, "connection_profile_set_dns_config_type(IPV6)", ConnectionGetError(nRet));
	}

    return 0;
}


/** @} */ 
/** @} */
