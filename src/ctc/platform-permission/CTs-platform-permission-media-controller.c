#include "CTs-platform-permission-common.h"

#include <media_controller_client.h>
#include <media_controller_server.h>
#include <media_controller_type.h>
#include <glib.h>
#include <Ecore.h>
#include <string.h>

/**
* @function 		MediaControllerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
/*char* MediaControllerGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch(nRet)
	{
		case MEDIA_CONTROLLER_ERROR_NONE:						szErrorVal = "MEDIA_CONTROLLER_ERROR_NONE";						break;
		case MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER:			szErrorVal = "MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER";		break;
		case MEDIA_CONTROLLER_ERROR_OUT_OF_MEMORY:				szErrorVal = "MEDIA_CONTROLLER_ERROR_OUT_OF_MEMORY";			break;
		case MEDIA_CONTROLLER_ERROR_INVALID_OPERATION:			szErrorVal = "MEDIA_CONTROLLER_ERROR_INVALID_OPERATION";		break;
		case MEDIA_CONTROLLER_ERROR_FILE_NO_SPACE_ON_DEVICE:	szErrorVal = "MEDIA_CONTROLLER_ERROR_FILE_NO_SPACE_ON_DEVICE";	break;
		case MEDIA_CONTROLLER_ERROR_PERMISSION_DENIED:			szErrorVal = "MEDIA_CONTROLLER_ERROR_PERMISSION_DENIED";		break;
		default: 												szErrorVal = "MEDIA_CONTROLLER_ERROR_UNKNOWN";					break;
	}
	return szErrorVal;
}*/

/**
* @function         CTs_platform_permission_MediaController_startup
* @description      Called before each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_MediaController_startup(void)
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
    FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_MediaController_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function         CTs_platform_permission_MediaController_cleanup
* @description      Called after each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_MediaController_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_MediaController_p\\n", __LINE__, API_NAMESPACE);
#endif
    return;
}

//& purpose:Checking tizen.org/privilege/mediacontroller.client privilege
//& type: auto
/**
* @testcase			CTc_MediaController_PrivilegeMediaControllerClient
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			To test mc_client_create and mc_client_destroy				
* @apicovered		Call mc_client_create, mc_client_destroy
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_MediaController_PrivilegeMediaControllerClient(void)
{
	START_TEST;
	int nRet = -1;
	mc_client_h hMcClient= NULL;
	
	nRet = mc_client_create(&hMcClient);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "mc_client_create", MediaControllerGetError(nRet), mc_client_destroy(hMcClient), MEDIA_CONTROLLER_ERROR_NONE);
	
	return 0;
}

