//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
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
#include "ITs-capi-network-ua-common.h"

//& set: CapiNetwork-ua

/** @addtogroup itc-capi-network-ua
*  @ingroup itc
*  @{
*/
ua_mac_type_e g_eMacType[] = {/*UA_MAC_TYPE_NONE,*/
			UA_MAC_TYPE_BT,
			UA_MAC_TYPE_BLE,
			UA_MAC_TYPE_WIFI,
			UA_MAC_TYPE_P2P
			/*UA_MAC_TYPE_INVALID*/
			};

int g_nEnumSize1 = sizeof(g_eMacType) / sizeof(g_eMacType[0]);

/**
 * @function 		ITs_capi_network_ua_device_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_capi_network_ua_device_startup(void)
{
	g_bUaInit = false;
	g_bIsUaFeatureSupported = false;
	g_bFeatureByPass = false;

	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	int nRet = UA_ERROR_NONE;

	g_bIsUaFeatureSupported = TCTCheckSystemInfoFeatureSupported(UA_FEATURE, API_NAMESPACE);

	nRet = ua_initialize();
	if(!g_bIsUaFeatureSupported)
	{
		if ( nRet != UA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] ua_initialize failed to return UA_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)\\n", __FILE__, __LINE__,nRet);
			return;
		}

		FPRINTF("[%s:%d] feature and ua_initialize is unsupported\\n", __FILE__, __LINE__);
		g_bFeatureByPass = true;
		return;
	}
	else if (nRet == UA_ERROR_NONE || nRet == UA_ERROR_ALREADY_DONE)
		g_bUaInit = true;
	else
	{
		FPRINTF("[%s:%d] ua_initialize failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		g_bUaInit = false;
	}
}


/**
 * @function 		ITs_capi_network_ua_device_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_capi_network_ua_device_cleanup(void)
{
	int nRet = UA_ERROR_NONE;

	if (g_bIsUaFeatureSupported && g_bUaInit)
	{
		nRet = ua_deinitialize();
		if ( nRet != UA_ERROR_NONE )
		{
			FPRINTF("[%s:%d] ua_deinitialize failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		}
	}
	return;
}

//& purpose: Creates and destroys the device handle
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_device_create_destroy_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates and destroys the device handle
* @scenario				Creates and destroys the device handle
* @apicovered			ua_device_create, ua_device_destroy
* @passcase				If ua_device_create, ua_device_destroy is successfull
* @failcase 			If ua_device_create, ua_device_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_device_create_destroy_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	ua_device_h hDevice = NULL;
	char pszMacAddrStr[] = {"30:AB:6A:09:1B:4C"};
	char pszDeviceIdStr[] = {"18:54:CF:06:37:FE"};
	int nEnumCounter1 = 0;
	for ( nEnumCounter1 = 0; nEnumCounter1 < g_nEnumSize1; nEnumCounter1++)
	{
		//Target API
		nRet = ua_device_create(g_eMacType[nEnumCounter1], pszMacAddrStr, pszDeviceIdStr, &hDevice);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_device_create", UaGetError(nRet));
		CHECK_HANDLE(hDevice, "ua_device_create");
		//Target API
		nRet = ua_device_destroy(hDevice);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_device_destroy", UaGetError(nRet));
	}

	return 0;
}
//& purpose: Gets device type info.
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_device_get_mac_type_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets device type info.
* @scenario				Gets device type info.
* @apicovered			ua_device_get_mac_type
* @passcase				If ua_device_get_mac_type is successfull
* @failcase 			If ua_device_get_mac_type fails
* @precondition			call ua_device_create API
* @postcondition		call ua_device_destroy API
*/
int ITc_capi_network_ua_device_get_mac_type_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	ua_device_h hDevice = NULL;
	char pszMacAddrStr[] = {"30:AB:6A:09:1B:4C"};
	char pszDeviceIdStr[] = {"18:54:CF:06:37:FE"};
	ua_mac_type_e eMacType = UA_MAC_TYPE_INVALID;
	int nEnumCounter1 = 0;
	for ( nEnumCounter1 = 0; nEnumCounter1 < g_nEnumSize1; nEnumCounter1++)
	{
		FPRINTF("[Line : %d][%s] Device:[%s]\\n", __LINE__, API_NAMESPACE, UaGetEnumMacTypeString(g_eMacType[nEnumCounter1]));
		nRet = ua_device_create(g_eMacType[nEnumCounter1], pszMacAddrStr, pszDeviceIdStr, &hDevice);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_device_create", UaGetError(nRet));
		CHECK_HANDLE(hDevice, "ua_device_create");
		//Target API
		nRet = ua_device_get_mac_type(hDevice, &eMacType);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_device_get_mac_type", UaGetError(nRet), ua_device_destroy(hDevice));
		PRINT_RESULT_CLEANUP(g_eMacType[nEnumCounter1], eMacType, "ua_device_get_mac_type", "get value is wrong", ua_device_destroy(hDevice));

		nRet = ua_device_destroy(hDevice);
		PRINT_RESULT_NORETURN(UA_ERROR_NONE, nRet, "ua_device_destroy", UaGetError(nRet));
	}
	return 0;
}

//& purpose: Gets device's MAC address.
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_device_get_mac_type_address_device_id_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets device's MAC address.
* @scenario				Gets device's MAC address.
* @apicovered			ua_device_get_mac_address
* @passcase				If ua_device_get_mac_address is successfull
* @failcase 			If ua_device_get_mac_address fails
* @precondition			call ua_device_create API
* @postcondition		call ua_device_destroy API
*/
int ITc_capi_network_ua_device_get_mac_address_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	ua_device_h hDevice = NULL;
	char pszMacAddrStr[] = {"30:AB:6A:09:1B:4C"};
	char pszDeviceIdStr[] = {"18:54:CF:06:37:FE"};
	char *pszMac = NULL;
	char *pszDeviceId = NULL;
	ua_mac_type_e eMacType = UA_MAC_TYPE_INVALID;
	int nEnumCounter1 = 0;
	for ( nEnumCounter1 = 0; nEnumCounter1 < g_nEnumSize1; nEnumCounter1++)
	{
		FPRINTF("[Line : %d][%s] Device:[%s]\\n", __LINE__, API_NAMESPACE, UaGetEnumMacTypeString(g_eMacType[nEnumCounter1]));
		nRet = ua_device_create(g_eMacType[nEnumCounter1], pszMacAddrStr, pszDeviceIdStr, &hDevice);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_device_create", UaGetError(nRet));
		CHECK_HANDLE(hDevice, "ua_device_create");

		//Target API
		nRet = ua_device_get_mac_address(hDevice, &pszMac);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_device_get_mac_address", UaGetError(nRet), ua_device_destroy(hDevice));
		CHECK_HANDLE_CLEANUP(pszMac, "ua_device_get_mac_address", ua_device_destroy(hDevice));
		FREE_MEMORY(pszMac);

		nRet = ua_device_destroy(hDevice);
		PRINT_RESULT_NORETURN(UA_ERROR_NONE, nRet, "ua_device_destroy", UaGetError(nRet));
	}
	return 0;
}

//& purpose: Gets device ID from the device.
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_device_get_device_id_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets device ID from the device.
* @scenario				Gets device ID from the device.
* @apicovered			ua_device_get_device_id
* @passcase				If ua_device_get_device_id is successfull
* @failcase 			If ua_device_get_device_id fails
* @precondition			call ua_device_create API
* @postcondition		call ua_device_destroy API
*/
int ITc_capi_network_ua_device_get_device_id_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	ua_device_h hDevice = NULL;
	char pszMacAddrStr[] = {"30:AB:6A:09:1B:4C"};
	char pszDeviceIdStr[] = {"18:54:CF:06:37:FE"};
	char *pszDeviceId = NULL;
	ua_mac_type_e eMacType = UA_MAC_TYPE_INVALID;
	int nEnumCounter1 = 0;
	for ( nEnumCounter1 = 0; nEnumCounter1 < g_nEnumSize1; nEnumCounter1++)
	{
		FPRINTF("[Line : %d][%s] Device:[%s]\\n", __LINE__, API_NAMESPACE, UaGetEnumMacTypeString(g_eMacType[nEnumCounter1]));
		nRet = ua_device_create(g_eMacType[nEnumCounter1], pszMacAddrStr, pszDeviceIdStr, &hDevice);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_device_create", UaGetError(nRet));
		CHECK_HANDLE(hDevice, "ua_device_create");

		//Target API
		nRet = ua_device_get_device_id(hDevice, &pszDeviceId);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_device_get_device_id", UaGetError(nRet), ua_device_destroy(hDevice));
		CHECK_HANDLE_CLEANUP(pszDeviceId, "ua_device_get_device_id", ua_device_destroy(hDevice));
		FREE_MEMORY(pszDeviceId);

		nRet = ua_device_destroy(hDevice);
		PRINT_RESULT_NORETURN(UA_ERROR_NONE, nRet, "ua_device_destroy", UaGetError(nRet));
	}
	return 0;
}

//& purpose: Sets and Gets device's operating system info
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_device_set_get_os_info_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets device's operating system info
* @scenario				Sets and Gets device's operating system info
* @apicovered			ua_device_set_os_info, ua_device_get_os_info
* @passcase				If ua_device_set_os_info, ua_device_get_os_info is successfull
* @failcase 			If ua_device_set_os_info, ua_device_get_os_info fails
* @precondition			call ua_device_create API
* @postcondition		call ua_device_destroy API
*/
int ITc_capi_network_ua_device_set_get_os_info_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	ua_device_h hDevice = NULL;
	char pszMacAddrStr[] = {"30:AB:6A:09:1B:4C"};
	char pszDeviceIdStr[] = {"18:54:CF:06:37:FE"};
	ua_os_type_e eOsType = UA_OS_TYPE_NOT_DEFINED;

	nRet = ua_device_create(UA_MAC_TYPE_WIFI, pszMacAddrStr, pszDeviceIdStr, &hDevice);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_device_create", UaGetError(nRet));
	CHECK_HANDLE(hDevice, "ua_device_create");

	//Target API
	nRet = ua_device_set_os_info(hDevice, UA_OS_TYPE_TIZEN);
	PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_device_set_os_info", UaGetError(nRet), ua_device_destroy(hDevice));

	//Target API
	nRet = ua_device_get_os_info(hDevice, &eOsType);
	PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_device_get_os_info", UaGetError(nRet), ua_device_destroy(hDevice));
	PRINT_RESULT_CLEANUP(UA_OS_TYPE_TIZEN, eOsType, "ua_device_get_os_info", "set get value mismatch", ua_device_destroy(hDevice));

	nRet = ua_device_destroy(hDevice);
	PRINT_RESULT_NORETURN(UA_ERROR_NONE, nRet, "ua_device_destroy", UaGetError(nRet));

	return 0;
}
//& purpose: Sets and Gets device's Wi-Fi BSSID
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_device_set_get_wifi_bssid_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets device's Wi-Fi BSSID.
* @scenario				Sets and Gets device's Wi-Fi BSSID.
* @apicovered			ua_device_set_wifi_bssid, ua_device_get_wifi_bssid
* @passcase				If ua_device_set_wifi_bssid, ua_device_get_wifi_bssid is successfull
* @failcase 			If ua_device_set_wifi_bssid, ua_device_get_wifi_bssid fails
* @precondition			call ua_device_create API
* @postcondition		call ua_device_destroy API and must release bssid
*/
int ITc_capi_network_ua_device_set_get_wifi_bssid_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	ua_device_h hDevice = NULL;
	char pszMacAddrStr[] = {"30:AB:6A:09:1B:4C"};
	char pszDeviceIdStr[] = {"18:54:CF:06:37:FE"};
	char pszSetWifiBssid[] = {"30:AB:6A:09:1B:4C"};
	char *pszGetWifiBssid = NULL;

	nRet = ua_device_create(UA_MAC_TYPE_WIFI, pszMacAddrStr, pszDeviceIdStr, &hDevice);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_device_create", UaGetError(nRet));
	CHECK_HANDLE(hDevice, "ua_device_create");
	//Target API
	nRet = ua_device_set_wifi_bssid(hDevice, pszSetWifiBssid);
	PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_device_set_wifi_bssid", UaGetError(nRet), ua_device_destroy(hDevice));

	//Target API
	nRet = ua_device_get_wifi_bssid(hDevice, &pszGetWifiBssid);
	PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_device_get_wifi_bssid", UaGetError(nRet), ua_device_destroy(hDevice));
	if(strcmp(pszSetWifiBssid, pszGetWifiBssid) != 0)
	{
		FPRINTF("[Line : %d][%s] Mismatch in value, set = %s, get = %s\\n", __LINE__, API_NAMESPACE, pszSetWifiBssid, pszGetWifiBssid);
		FREE_MEMORY(pszGetWifiBssid);
		ua_device_destroy(hDevice);
		return 1;
	}

	FREE_MEMORY(pszGetWifiBssid);
	nRet = ua_device_destroy(hDevice);
	PRINT_RESULT_NORETURN(UA_ERROR_NONE, nRet, "ua_device_destroy", UaGetError(nRet));

	return 0;
}
//& purpose: Sets and Gets device's Wi-Fi IPv4 address
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_device_set_get_wifi_ipv4_address
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets device's Wi-Fi IPv4 address.
* @scenario				Sets and Gets device's Wi-Fi IPv4 address.
* @apicovered			ua_device_set_wifi_ipv4_address, ua_device_get_wifi_ipv4_address
* @passcase				If ua_device_set_wifi_ipv4_address, ua_device_get_wifi_ipv4_address is successfull
* @failcase 			If ua_device_set_wifi_ipv4_address, ua_device_get_wifi_ipv4_address fails
* @precondition			call ua_device_create API
* @postcondition		call ua_device_destroy API and must release ipv4_address
*/
int ITc_capi_network_ua_device_set_get_wifi_ipv4_address(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	ua_device_h hDevice = NULL;
	char pszMacAddrStr[] = {"30:AB:6A:09:1B:4C"};
	char pszDeviceIdStr[] = {"18:54:CF:06:37:FE"};
	char pszSetIpv4Address[] = {"192.168.107.10"};
	char *pszGetIpv4Address = NULL;

	nRet = ua_device_create(UA_MAC_TYPE_WIFI, pszMacAddrStr, pszDeviceIdStr, &hDevice);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_device_create", UaGetError(nRet));
	CHECK_HANDLE(hDevice, "ua_device_create");
	//Target API
	nRet = ua_device_set_wifi_ipv4_address(hDevice, pszSetIpv4Address);
	PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_device_set_wifi_ipv4_address", UaGetError(nRet), ua_device_destroy(hDevice));

	//Target API
	nRet = ua_device_get_wifi_ipv4_address(hDevice, &pszGetIpv4Address);
	PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_device_get_wifi_ipv4_address", UaGetError(nRet), ua_device_destroy(hDevice));
	if(strcmp(pszSetIpv4Address, pszGetIpv4Address) != 0)
	{
		FPRINTF("[Line : %d][%s] Mismatch in value, set = %s, get = %s\\n", __LINE__, API_NAMESPACE, pszSetIpv4Address, pszGetIpv4Address);
		FREE_MEMORY(pszGetIpv4Address);
		ua_device_destroy(hDevice);
		return 1;
	}
	FREE_MEMORY(pszGetIpv4Address);

	nRet = ua_device_destroy(hDevice);
	PRINT_RESULT_NORETURN(UA_ERROR_NONE, nRet, "ua_device_destroy", UaGetError(nRet));

	return 0;
}
//& purpose: Gets last presence time for device handle
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_device_get_last_presence_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets last presence time for device handle.
* @scenario				Gets last presence time for device handle
* @apicovered			ua_device_get_last_presence
* @passcase				If ua_device_get_last_presence is successfull
* @failcase 			If ua_device_get_last_presence fails
* @precondition			call ua_device_create API
* @postcondition		call ua_device_destroy API
*/
int ITc_capi_network_ua_device_get_last_presence_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	ua_device_h hDevice = NULL;
	char pszMacAddrStr[] = {"30:AB:6A:09:1B:4C"};
	char pszDeviceIdStr[] = {"18:54:CF:06:37:FE"};
	unsigned long long ullLastSeen = 0;

	nRet = ua_device_create(UA_MAC_TYPE_WIFI, pszMacAddrStr, pszDeviceIdStr, &hDevice);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_device_create", UaGetError(nRet));
	CHECK_HANDLE(hDevice, "ua_device_create");

	//Target API
	nRet = ua_device_get_last_presence(hDevice, &ullLastSeen);
	PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_device_get_last_presence", UaGetError(nRet), ua_device_destroy(hDevice));

	nRet = ua_device_destroy(hDevice);
	PRINT_RESULT_NORETURN(UA_ERROR_NONE, nRet, "ua_device_destroy", UaGetError(nRet));

	return 0;
}

//& purpose: Gets whether pairing is required for the user device
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_device_get_pairing_required_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets whether pairing is required for the user device
* @scenario				Gets whether pairing is required for the user device
* @apicovered			ua_device_get_pairing_required
* @passcase				If ua_device_get_pairing_required is successfull
* @failcase 			If ua_device_get_pairing_required fails
* @precondition			call ua_device_create API
* @postcondition		call ua_device_destroy API
*/
int ITc_capi_network_ua_device_get_pairing_required_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	ua_device_h hDevice = NULL;
	char pszMacAddrStr[] = {"30:AB:6A:09:1B:4C"};
	char pszDeviceIdStr[] = {"18:54:CF:06:37:FE"};
	bool bRequired = false;
	int nEnumCounter1 = 0;
	for ( nEnumCounter1 = 0; nEnumCounter1 < g_nEnumSize1; nEnumCounter1++)
	{
		FPRINTF("[Line : %d][%s] Device:[%s]\\n", __LINE__, API_NAMESPACE, UaGetEnumMacTypeString(g_eMacType[nEnumCounter1]));
		nRet = ua_device_create(g_eMacType[nEnumCounter1], pszMacAddrStr, pszDeviceIdStr, &hDevice);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_device_create", UaGetError(nRet));
		CHECK_HANDLE(hDevice, "ua_device_create");
		//Target API
		nRet = ua_device_get_pairing_required(hDevice, &bRequired);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_device_get_pairing_required", UaGetError(nRet), ua_device_destroy(hDevice));
		PRINT_RESULT_CLEANUP(true, bRequired, "ua_device_get_pairing_required", "pairing required returning wrong value", ua_device_destroy(hDevice));

		nRet = ua_device_destroy(hDevice);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_device_destroy", UaGetError(nRet));
	}
	return 0;
}

//& purpose: Gets device handle by MAC address
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_device_get_by_mac_address_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets device handle by MAC address
* @scenario				Gets device handle by MAC address
* @apicovered			ua_device_get_by_mac_address
* @passcase				If ua_device_get_by_mac_address is successfull
* @failcase 			If ua_device_get_by_mac_address fails
* @precondition			call ua_device_create API
* @postcondition		call ua_device_destroy API
*/
int ITc_capi_network_ua_device_get_by_mac_address_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	ua_device_h hDevice = NULL;
	char pszMacAddrStr[] = {"30:AB:6A:09:1B:4C"};
	char pszDeviceIdStr[] = {"18:54:CF:06:37:FE"};
	bool bRequired = false;
	ua_device_h hGetDevice = NULL;
	int nEnumCounter1 = 0;
	for ( nEnumCounter1 = 0; nEnumCounter1 < g_nEnumSize1; nEnumCounter1++)
	{
		FPRINTF("[Line : %d][%s] Device:[%s]\\n", __LINE__, API_NAMESPACE, UaGetEnumMacTypeString(g_eMacType[nEnumCounter1]));
		nRet = ua_device_create(g_eMacType[nEnumCounter1], pszMacAddrStr, pszDeviceIdStr, &hDevice);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_device_create", UaGetError(nRet));
		CHECK_HANDLE(hDevice, "ua_device_create");

		//Target API
		nRet = ua_device_get_by_mac_address(pszMacAddrStr, &hGetDevice);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_device_get_by_mac_address", UaGetError(nRet), ua_device_destroy(hDevice));
		CHECK_HANDLE_CLEANUP(hGetDevice, "ua_device_get_by_mac_address", ua_device_destroy(hDevice));

		nRet = ua_device_destroy(hDevice);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_device_destroy", UaGetError(nRet));
	}
	return 0;
}

//& purpose: Gets device handle by device ID.
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_device_get_by_device_id_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets device handle by device ID
* @scenario				Gets device handle by device ID
* @apicovered			ua_device_get_by_device_id
* @passcase				If ua_device_get_by_device_id is successfull
* @failcase 			If ua_device_get_by_device_id fails
* @precondition			call ua_device_create API
* @postcondition		call ua_device_destroy API
*/
int ITc_capi_network_ua_device_get_by_device_id_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	ua_device_h hDevice = NULL;
	char pszMacAddrStr[] = {"30:AB:6A:09:1B:4C"};
	char pszDeviceIdStr[] = {"18:54:CF:06:37:FE"};
	bool bRequired = false;
	ua_device_h hGetDevice = NULL;
	ua_mac_type_e eMacType = UA_MAC_TYPE_INVALID;
	int nEnumCounter1 = 0;
	for ( nEnumCounter1 = 0; nEnumCounter1 < g_nEnumSize1; nEnumCounter1++)
	{
		FPRINTF("[Line : %d][%s] Device:[%s]\\n", __LINE__, API_NAMESPACE, UaGetEnumMacTypeString(g_eMacType[nEnumCounter1]));
		nRet = ua_device_create(g_eMacType[nEnumCounter1], pszMacAddrStr, pszDeviceIdStr, &hDevice);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_device_create", UaGetError(nRet));
		CHECK_HANDLE(hDevice, "ua_device_create");

		nRet = ua_device_get_by_mac_address(pszMacAddrStr, &hGetDevice);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_device_get_by_mac_address", UaGetError(nRet), ua_device_destroy(hDevice));
		CHECK_HANDLE_CLEANUP(hGetDevice, "ua_device_get_by_mac_address", ua_device_destroy(hDevice));

		//Target API
		nRet = ua_device_get_by_device_id(pszDeviceIdStr, g_eMacType[nEnumCounter1], &hGetDevice);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_device_get_by_device_id", UaGetError(nRet), ua_device_destroy(hDevice));
		CHECK_HANDLE_CLEANUP(hGetDevice, "ua_device_get_by_device_id", ua_device_destroy(hDevice));

		nRet = ua_device_destroy(hDevice);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_device_destroy", UaGetError(nRet));
	}
	return 0;
}