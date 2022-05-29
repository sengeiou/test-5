#include "CTs-platform-permission-common.h"
#include <system_info.h>
#include <vpn_service.h>

#define VPNSVC_FEATURE		"http://tizen.org/feature/network.vpn"
#define VPNSVC_IFACE_NAME	"vpnsvc_iface"

vpnsvc_h g_hVpnSvcHandle = NULL;

/**
* @function 		CTs_platform_permission_vpn_service_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_vpn_service_startup(void)
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
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_vpn_service_startup\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function 		CTs_platform_permission_vpn_service_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_vpn_service_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_vpn_service_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 			VPNSVCGetError
* @description 			print the error information
* @parameter[in]		nResult: the error code
* @return 				pszErrorMsg: return the error message
*/
char *VPNSVCGetError(int nResult)
{
	char *pszErrorMsg = "UNDEFINED ERROR \n";

	switch ( nResult )
	{
	case VPNSVC_ERROR_NONE :
		pszErrorMsg = "VPNSVC_ERROR_NONE  \n";
		break;
	case VPNSVC_ERROR_INVALID_PARAMETER :
		pszErrorMsg = "VPNSVC_ERROR_INVALID_PARAMETER  \n";
		break;
	case VPNSVC_ERROR_OUT_OF_MEMORY :
		pszErrorMsg = "VPNSVC_ERROR_OUT_OF_MEMORY  \n";
		break;
	case VPNSVC_ERROR_PERMISSION_DENIED :
		pszErrorMsg = "VPNSVC_ERROR_PERMISSION_DENIED  \n";
		break;
	case VPNSVC_ERROR_NO_SUCH_FILE :
		pszErrorMsg = "VPNSVC_ERROR_NO_SUCH_FILE  \n";
		break;
	case VPNSVC_ERROR_IO_ERROR :
		pszErrorMsg = "VPNSVC_ERROR_IO_ERROR  \n";
		break;
	case VPNSVC_ERROR_TIMEOUT :
		pszErrorMsg = "VPNSVC_ERROR_TIMEOUT  \n";
		break;
	case VPNSVC_ERROR_IPC_FAILED :
		pszErrorMsg = "VPNSVC_ERROR_IPC_FAILED  \n";
		break;
	case VPNSVC_ERROR_NOT_SUPPORTED :
		pszErrorMsg = "VPNSVC_ERROR_NOT_SUPPORTED  \n";
		break;
	}
	return pszErrorMsg;
}

//& purpose: checking http://tizen.org/privilege/vpnservice && http://tizen.org/privilege/internet
//& type: auto
/**
* @testcase			CTc_VpnService_PrivilegeVpnsvc_init
* @since_tizen		3.0
* @author			SRID(arvin.mittal)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			To Initialize VPN interface
* @apicovered		vpnsvc_init, vpnsvc_deinit
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_VpnService_PrivilegeVpnsvc_init(void)
{ 
	START_TEST;
	
	bool bIsSupported = false;
	IS_FEATURE_SUPPORTED(VPNSVC_FEATURE, bIsSupported, API_NAMESPACE);
	if ( false == bIsSupported )
	{
		FPRINTF("[Line : %d][%s] %s Feature is not supported\\n", __LINE__, API_NAMESPACE, VPNSVC_FEATURE);
		return 0;
	}

	int nRetVal = vpnsvc_init(VPNSVC_IFACE_NAME, &g_hVpnSvcHandle);
	if(nRetVal == VPNSVC_ERROR_NONE)
	{
		nRetVal = vpnsvc_deinit(g_hVpnSvcHandle);
		PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRetVal, "vpnsvc_deinit", VPNSVCGetError(nRetVal));		
	}	
	else
	{
		PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRetVal, "vpnsvc_init", VPNSVCGetError(nRetVal));		
	}
	
	return 0;
}