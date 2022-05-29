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
#include "ITs-vpn-service-common.h"

vpnsvc_h g_hVpnSvcHandle = NULL;
#define VPNSVC_IP4_STRING_LEN 16

//& set: VpnService

/** @addtogroup itc-vpn-service
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_vpn_service_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_vpn_service_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Vpn_Service_p\\n", __LINE__, API_NAMESPACE);
#endif

	//Feature check for feature network.vpn
	IS_FEATURE_SUPPORTED(VPNSVC_FEATURE, g_bVPNSVCIsSupported, API_NAMESPACE);
	
	//Initialize the VPN-Service
	int nRetVal = vpnsvc_init(VPNSVC_IFACE_NAME, &g_hVpnSvcHandle);
	if ( false == g_bVPNSVCIsSupported )
	{
		if ( nRetVal != TIZEN_ERROR_NOT_SUPPORTED )
		{
			g_bVPNSVCMismatch = true;
		}
		else
		{
			g_bVPNSVCNotSupported = true;
		}
		return;
	}
	
	if ( (nRetVal != VPNSVC_ERROR_NONE ) || (g_hVpnSvcHandle == NULL))
	{
		FPRINTF("[Line : %d][%s] VPNSVC initialization failed, error returned = %s\\n", __LINE__, API_NAMESPACE, VPNSVCGetError(nRetVal));
		g_bVPNSVCInit = false;
	}
	else
	{
		FPRINTF("[Line : %d][%s] VPNSVC initialized successfully\\n", __LINE__, API_NAMESPACE);
		g_bVPNSVCInit = true;
	}
	return;
}


/**
 * @function 		ITs_vpn_service_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_vpn_service_cleanup(void)
{
	if ( g_bVPNSVCInit )
	{
		if(g_hVpnSvcHandle)
		{
			//De-Initialize the VPN-Service
			int nRetVal = vpnsvc_deinit(g_hVpnSvcHandle);
			if ( nRetVal != VPNSVC_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] VPNSVC de-initialization failed, error returned = %s\\n", __LINE__, API_NAMESPACE, VPNSVCGetError(nRetVal));
			}
			else
			{
				FPRINTF("[Line : %d][%s] VPNSVC de-initialized successfully\\n", __LINE__, API_NAMESPACE);
				g_hVpnSvcHandle = NULL;
			}
		}
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Vpn_Service_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup itc-vpn-service-testcases
*  @brief 		Integration testcases for module vpn-service
*  @ingroup 	itc-vpn-service
*  @{
*/

//& type: auto
//& purpose: To Initialize and De-Initialize VPN interface
/**
* @testcase 			ITc_vpnsvc_init_deinit_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			To Initialize and De-Initialize VPN interface
* @scenario				De-Initialize the vpn-service initialized in startup\n
* 						Initialize the vpn-service\n
* 						De-Initialize the vpn-service\n
* 						Initialize the vpn-service to be de-initialize in cleanup
* @apicovered			vpnsvc_init, vpnsvc_deinit
* @passcase				If vpnsvc_init and vpnsvc_deinit returns success
* @failcase				If vpnsvc_init or vpnsvc_deinit returns false
* @precondition			none
* @postcondition		none
*/
int ITc_vpnsvc_init_deinit_p(void)
{
	START_TEST;
	
	vpnsvc_h hVpnSvcHandle = NULL;

	// Target API
	int nRetValue = vpnsvc_init(VPNSVC_IFACE_NAME1, &hVpnSvcHandle);
	PRINT_RESULT(VPNSVC_ERROR_NONE, nRetValue, "vpnsvc_init", VPNSVCGetError(nRetValue));
	CHECK_HANDLE(hVpnSvcHandle, "vpnsvc_init");

	// Target API
	nRetValue = vpnsvc_deinit(hVpnSvcHandle);
	PRINT_RESULT(VPNSVC_ERROR_NONE, nRetValue, "vpnsvc_deinit", VPNSVCGetError(nRetValue));

	return 0;
}

//& type: auto
//& purpose: To Set and Get the session name for the VPN
/** 
* @testcase 			ITc_vpnsvc_set_get_session_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			To Set and Get the session name for the VPN
* @scenario				Set the session name for the VPN\n
* 						Get the session name for the VPN\n
* 						Compare set and get values
* @apicovered			vpnsvc_set_session, vpnsvc_get_session
* @passcase				If vpnsvc_set_session and vpnsvc_get_session returns success
* @failcase				If vpnsvc_set_session or vpnsvc_get_session returns false
* @precondition			vpn-service should be initialized
* @postcondition		vpn-service should be de-initialized
*/
int ITc_vpnsvc_set_get_session_p(void)
{
	START_TEST;
	
	char *pszSetSession = "vpnsvc_session";
	char *pszGetSession = NULL;

	// Target API
	int nRetValue = vpnsvc_set_session(g_hVpnSvcHandle, pszSetSession);
	PRINT_RESULT(VPNSVC_ERROR_NONE, nRetValue, "vpnsvc_set_session", VPNSVCGetError(nRetValue));

	// Target API
	nRetValue = vpnsvc_get_session(g_hVpnSvcHandle, &pszGetSession);
	PRINT_RESULT(VPNSVC_ERROR_NONE, nRetValue, "vpnsvc_get_session", VPNSVCGetError(nRetValue));
	
	//Compare Set and Get Value
	if ( strcmp(pszSetSession, pszGetSession) != 0 )
	{
		FPRINTF("[Line : %d][%s] vpnsvc_get_session return value %s mismatched with set value %s\\n", __LINE__, API_NAMESPACE, pszSetSession, pszGetSession);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: To Get the fd of the VPN interface
/** 
* @testcase 			ITc_vpnsvc_get_iface_fd_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			To Get the fd of the VPN interface
* @scenario				Get the fd of the VPN\n
* 						Check the get value
* @apicovered			vpnsvc_get_iface_fd
* @passcase				If vpnsvc_get_iface_fd returns success
* @failcase				If vpnsvc_get_iface_fd returns false
* @precondition			vpn-service should be initialized
* @postcondition		vpn-service should be de-initialized
*/
int ITc_vpnsvc_get_iface_fd_p(void)
{
	START_TEST;
	
	int nIfaceFDVal = -1;

	// Target API
	int nRetValue = vpnsvc_get_iface_fd(g_hVpnSvcHandle, &nIfaceFDVal);
	PRINT_RESULT(VPNSVC_ERROR_NONE, nRetValue, "vpnsvc_get_iface_fd", VPNSVCGetError(nRetValue));
	
	//Check Get Value
	if (nIfaceFDVal < 0 )
	{
		FPRINTF("[Line : %d][%s] vpnsvc_get_iface_fd return invalid value %d \\n", __LINE__, API_NAMESPACE, nIfaceFDVal);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: To Get the index of VPN interface
/** 
* @testcase 			ITc_vpnsvc_get_iface_index_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			To Get the index of VPN interface
* @scenario				Get the index of VPN\n
* 						Check the get value
* @apicovered			vpnsvc_get_iface_index
* @passcase				If vpnsvc_get_iface_index returns success
* @failcase				If vpnsvc_get_iface_index returns false
* @precondition			vpn-service should be initialized
* @postcondition		vpn-service should be de-initialized
*/
int ITc_vpnsvc_get_iface_index_p(void)
{
	START_TEST;
	
	int nIfaceIndxVal = -1;

	// Target API
	int nRetValue = vpnsvc_get_iface_index(g_hVpnSvcHandle, &nIfaceIndxVal);
	PRINT_RESULT(VPNSVC_ERROR_NONE, nRetValue, "vpnsvc_get_iface_index", VPNSVCGetError(nRetValue));
	
	//Check Get Value
	if (nIfaceIndxVal < 0 )
	{
		FPRINTF("[Line : %d][%s] vpnsvc_get_iface_index return invalid value %d \\n", __LINE__, API_NAMESPACE, nIfaceIndxVal);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: To Get the name of VPN interface
/** 
* @testcase 			ITc_vpnsvc_get_iface_name_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			To Get the name of VPN interface
* @scenario				Get the name of VPN\n
* 						Check the get value
* @apicovered			vpnsvc_get_iface_name
* @passcase				If vpnsvc_get_iface_name returns success
* @failcase				If vpnsvc_get_iface_name returns false
* @precondition			vpn-service should be initialized
* @postcondition		vpn-service should be de-initialized
*/
int ITc_vpnsvc_get_iface_name_p(void)
{
	START_TEST;
	
	char* pszIfaceName = NULL;

	// Target API
	int nRetValue = vpnsvc_get_iface_name(g_hVpnSvcHandle, &pszIfaceName);
	PRINT_RESULT(VPNSVC_ERROR_NONE, nRetValue, "vpnsvc_get_iface_name", VPNSVCGetError(nRetValue));
	
	//Check Get Value
	if (pszIfaceName == NULL )
	{
		FPRINTF("[Line : %d][%s] vpnsvc_get_iface_name return null value %s \\n", __LINE__, API_NAMESPACE, pszIfaceName);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: To Set the MTU of the VPN interface
/** 
* @testcase 			ITc_vpnsvc_set_mtu_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			To Set the MTU of the VPN interface
* @scenario				Set the MTU of the VPN
* @apicovered			vpnsvc_set_mtu
* @passcase				If vpnsvc_set_mtu returns success
* @failcase				If vpnsvc_set_mtu returns false
* @precondition			vpn-service should be initialized
* @postcondition		vpn-service should be de-initialized
*/
int ITc_vpnsvc_set_mtu_p(void)
{
	START_TEST;
	
	int nSetMtuVal = 9000;

	// Target API
	int nRetValue = vpnsvc_set_mtu(g_hVpnSvcHandle, nSetMtuVal);
	PRINT_RESULT(VPNSVC_ERROR_NONE, nRetValue, "vpnsvc_set_mtu", VPNSVCGetError(nRetValue));
	
	return 0;
}

//& type: auto
//& purpose: To Set blocking mode of the file descriptor of VPN interface
/** 
* @testcase 			ITc_vpnsvc_set_blocking_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			To Set blocking mode of the file descriptor of VPN interface
* @scenario				Set blocking mode of the file descriptor of VPN
* @apicovered			vpnsvc_set_blocking
* @passcase				If vpnsvc_set_blocking returns success
* @failcase				If vpnsvc_set_blocking returns false
* @precondition			vpn-service should be initialized
* @postcondition		vpn-service should be de-initialized
*/
int ITc_vpnsvc_set_blocking_p(void)
{
	START_TEST;
	
	bool bSetBlock = true;

	// Target API
	int nRetValue = vpnsvc_set_blocking(g_hVpnSvcHandle, bSetBlock);
	PRINT_RESULT(VPNSVC_ERROR_NONE, nRetValue, "vpnsvc_set_blocking", VPNSVCGetError(nRetValue));
	
	return 0;
}

//& type: auto
//& purpose: To Block all traffics except specified allowing networks and Removes any restrictions imposed by vpnsvc_block_networks()
/** 
* @testcase 			ITc_vpnsvc_block_unblock_networks_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			To Block all traffics except specified allowing networks and Removes any restrictions imposed by vpnsvc_block_networks()
* @scenario				Block all traffics except specified allowing networks\n
* 						Removes any restrictions imposed by vpnsvc_block_networks()
* @apicovered			vpnsvc_block_networks, vpnsvc_unblock_networks
* @passcase				If vpnsvc_block_networks and vpnsvc_unblock_networks returns success
* @failcase				If vpnsvc_block_networks or vpnsvc_unblock_networks returns false
* @precondition			vpn-service should be initialized
* @postcondition		vpn-service should be de-initialized
*/
int ITc_vpnsvc_block_unblock_networks_p(void)
{
	START_TEST;
	
	const char *pszBlockNet[1];
	const char *pszAllowNet[1];
	int nBlockPrefix[1],nAllowPrefix[1];
	int nBlockNumRoutes = 1,nAllowNumRoutes = 1;

	pszBlockNet[0] = malloc(sizeof(char) * VPNSVC_IP4_STRING_LEN);
	memset(pszBlockNet[0], 0, sizeof(char) * VPNSVC_IP4_STRING_LEN);
	strncpy(pszBlockNet[0], "125.209.222.141", VPNSVC_IP4_STRING_LEN);
	nBlockPrefix[0] = 32;

	pszAllowNet[0] = malloc(sizeof(char) * VPNSVC_IP4_STRING_LEN);
	memset(pszAllowNet[0], 0, sizeof(char) * VPNSVC_IP4_STRING_LEN);
	strncpy(pszAllowNet[0], "216.58.221.142", VPNSVC_IP4_STRING_LEN);
	nAllowPrefix[0] = 32;

	// Target API
	int nRetValue = vpnsvc_block_networks(g_hVpnSvcHandle, pszBlockNet, nBlockPrefix, nBlockNumRoutes, pszAllowNet, nAllowPrefix, nAllowNumRoutes);
	PRINT_RESULT_CLEANUP(VPNSVC_ERROR_NONE, nRetValue, "vpnsvc_block_networks", VPNSVCGetError(nRetValue),FREE_MEMORY(pszAllowNet[0]);FREE_MEMORY(pszBlockNet[0]));

	// Target API
	nRetValue = vpnsvc_unblock_networks(g_hVpnSvcHandle);
	PRINT_RESULT_CLEANUP(VPNSVC_ERROR_NONE, nRetValue, "vpnsvc_unblock_networks", VPNSVCGetError(nRetValue),FREE_MEMORY(pszAllowNet[0]);FREE_MEMORY(pszBlockNet[0]));
	
	FREE_MEMORY(pszAllowNet[0]);
	FREE_MEMORY(pszBlockNet[0]);

	return 0;
}


//& type: auto
//& purpose: To Protect a socket from VPN connections
/** 
* @testcase 			ITc_vpnsvc_protect_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			To Protect a socket from VPN connections
* @scenario				Protect a socket from VPN connections
* @apicovered			vpnsvc_protect
* @passcase				If vpnsvc_protect returns success
* @failcase				If vpnsvc_protect returns false
* @precondition			vpn-service should be initialized
* @postcondition		vpn-service should be de-initialized
*/
int ITc_vpnsvc_protect_p(void)
{
	START_TEST;
	
	char *pszIfaceName = "wlan0";
	
	int nSocketFd = socket(PF_UNIX, SOCK_STREAM, 0);
	if (nSocketFd < 0)
	{
		FPRINTF("[Line : %d][%s] socket failed with return value %d \\n", __LINE__, API_NAMESPACE, nSocketFd);
		return 1;
	}

	// Target API
	int nRetValue = vpnsvc_protect(g_hVpnSvcHandle, nSocketFd, pszIfaceName);
	PRINT_RESULT_CLEANUP(VPNSVC_ERROR_NONE, nRetValue, "vpnsvc_protect", VPNSVCGetError(nRetValue),close(nSocketFd));
	
	close(nSocketFd);
	return 0;
}

//& type: auto
//& purpose: To Set local IP for VPN
/** 
* @testcase 			ITc_vpnsvc_set_local_ip_address_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			To Set local IP for VPN
* @scenario				To Set local IP for VPN
* @apicovered			vpnsvc_set_local_ip_address
* @passcase				If vpnsvc_set_local_ip_address returns success
* @failcase				If vpnsvc_set_local_ip_address returns false
* @precondition			vpn-service should be initialized
* @postcondition		vpn-service should be de-initialized
*/
int ITc_vpnsvc_set_local_ip_address_p(void)
{
	START_TEST;
	
	char *pszLocalIp = "192.168.123.45";

	// Target API
	int nRetValue = vpnsvc_set_local_ip_address(g_hVpnSvcHandle, pszLocalIp);
	PRINT_RESULT(VPNSVC_ERROR_NONE, nRetValue, "vpnsvc_set_local_ip_address", VPNSVCGetError(nRetValue));
	
	return 0;
}

//& type: auto
//& purpose: To Set remote IP for VPN
/** 
* @testcase 			ITc_vpnsvc_set_remote_ip_address_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			To Set remote IP for VPN
* @scenario				To Set remote IP for VPN
* @apicovered			vpnsvc_set_remote_ip_address
* @passcase				If vpnsvc_set_remote_ip_address returns success
* @failcase				If vpnsvc_set_remote_ip_address returns false
* @precondition			vpn-service should be initialized
* @postcondition		vpn-service should be de-initialized
*/
int ITc_vpnsvc_set_remote_ip_address_p(void)
{
	START_TEST;
	
	char *pszRemoteIp = "192.168.123.123";

	// Target API
	int nRetValue = vpnsvc_set_remote_ip_address(g_hVpnSvcHandle, pszRemoteIp);
	PRINT_RESULT(VPNSVC_ERROR_NONE, nRetValue, "vpnsvc_set_remote_ip_address", VPNSVCGetError(nRetValue));
	
	return 0;
}

//& type: auto
//& purpose: To update vpn settings
/** 
* @testcase 			ITc_vpnsvc_update_settings_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			 To update vpn settings
* @scenario				 To update vpn settings
* @apicovered			vpnsvc_update_settings
* @passcase				If vpnsvc_update_settings returns success
* @failcase				If vpnsvc_update_settings returns false
* @precondition			vpn-service should be initialized
* @postcondition		vpn-service should be de-initialized
*/
int ITc_vpnsvc_update_settings_p(void)
{
	START_TEST;
	
	char *pszLocalIp = "192.168.123.45";
	char *pszRemoteIp = "192.168.123.123";

	int nRetValue = vpnsvc_set_local_ip_address(g_hVpnSvcHandle, pszLocalIp);
	PRINT_RESULT(VPNSVC_ERROR_NONE, nRetValue, "vpnsvc_set_local_ip_address", VPNSVCGetError(nRetValue));
	
	nRetValue = vpnsvc_set_remote_ip_address(g_hVpnSvcHandle, pszRemoteIp);
	PRINT_RESULT(VPNSVC_ERROR_NONE, nRetValue, "vpnsvc_set_remote_ip_address", VPNSVCGetError(nRetValue));
	
	// Target API
	nRetValue = vpnsvc_update_settings(g_hVpnSvcHandle);
	PRINT_RESULT(VPNSVC_ERROR_NONE, nRetValue, "vpnsvc_update_settings", VPNSVCGetError(nRetValue));

	return 0;
}

/** @} */
/** @} */
