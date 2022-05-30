#include "CTs-platform-permission-common.h"
#include "inputmethod_manager.h"
#include <glib.h>

/**
 * @function 		InputmethodManagerGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
/*char* InputmethodManagerGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case IME_MANAGER_ERROR_NONE:szErrorVal = "IME_MANAGER_ERROR_NONE";									break;
		case IME_MANAGER_ERROR_INVALID_PARAMETER:szErrorVal = "IME_MANAGER_ERROR_INVALID_PARAMETER";		break;
		case IME_MANAGER_ERROR_PERMISSION_DENIED:szErrorVal = "IME_MANAGER_ERROR_PERMISSION_DENIED";		break;
		case IME_MANAGER_ERROR_OPERATION_FAILED:szErrorVal = "IME_MANAGER_ERROR_OPERATION_FAILED";			break;
		default:szErrorVal = "Unknown Error";																break;
	}

	return szErrorVal;
}*/
/**
* @function         CTs_platform_permission_inputmethodmanager_startup
* @description         Called before each test
* @parameter        NA
* @return             NA
*/
void CTs_platform_permission_inputmethodmanager_startup(void)
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
    FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function         CTs_platform_permission_inputmethodmanager_cleanup
* @description         Called after each test
* @parameter        NA
* @return             NA
*/
void CTs_platform_permission_inputmethodmanager_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
    return;
}

//& purpose: Checks which IME is the current activated IME.
//& type: auto
/**
* @testcase			CTc_IME_Manager_GetActiveIME 
* @since_tizen		2.4
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @description		Checks which IME is the current activated IME.
* @scenario			Get the the current activated IME
* @apicovered		ime_manager_get_active_ime
* @passcase			If target privileged API returns IME_MANAGER_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_MANAGER_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_Manager_GetActiveIME(void)
{
	START_TEST;

	char *pszAppid = NULL;

	//Target API
	int nRet = ime_manager_get_active_ime(&pszAppid);
	PRINT_RESULT(IME_MANAGER_ERROR_PERMISSION_DENIED, nRet, "ime_manager_get_active_ime",InputmethodManagerGetError(nRet));
	if ( pszAppid != NULL )
	{
		FPRINTF("[Line : %d][%s] current activated IME appid = %s\\n", __LINE__, API_NAMESPACE, pszAppid);
		FREE_MEMORY(pszAppid);
	}
	
	return 0;
}

//& purpose: Checks requests to open the IME selector menu.
//& type: auto
/**
* @testcase			CTc_IME_Manager_Show_IME_Selector 
* @since_tizen		2.4
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @description		Checks requests to open the IME selector menu.
* @scenario			Checks requests to open the IME selector menu.
* @apicovered		ime_manager_show_ime_selector
* @passcase			If target privileged API returns IME_MANAGER_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_MANAGER_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_Manager_Show_IME_Selector(void)
{
	START_TEST;

	//Target API
	int nRet = ime_manager_show_ime_selector();
	PRINT_RESULT(IME_MANAGER_ERROR_PERMISSION_DENIED, nRet, "ime_manager_show_ime_selector",InputmethodManagerGetError(nRet));

	return 0;
}

//& purpose: Checks requests to open the installed IME list menu.
//& type: auto
/**
* @testcase			CTc_IME_Manager_Show_IME_List 
* @since_tizen		2.4
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @description		Checks requests to open the installed IME list menu
* @scenario			Checks requests to open the installed IME list menu
* @apicovered		ime_manager_show_ime_list
* @passcase			If target privileged API returns IME_MANAGER_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_MANAGER_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_Manager_Show_IME_List(void)
{
	START_TEST;

	//Target API
	int nRet = ime_manager_show_ime_list();
	PRINT_RESULT(IME_MANAGER_ERROR_PERMISSION_DENIED, nRet, "ime_manager_show_ime_list",InputmethodManagerGetError(nRet));

	return 0;
}

//& purpose: Checks requests to open the installed IME list menu.
//& type: auto
/**
* @testcase			CTc_IME_MANAGER_GET_ENABLED_IME_COUNT 
* @since_tizen		3.0
* @author			SRID(arvin.mittal)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description		gets the number of IMEs which are enabled(usable)
* @scenario			returns the number of enabled IMEs on success, otherwise 0
* @apicovered		ime_manager_get_enabled_ime_count
* @passcase			If target privileged API returns IME_MANAGER_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return IME_MANAGER_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_IME_MANAGER_GET_ENABLED_IME_COUNT(void)
{
	START_TEST;

	int nNumberOfEnabledIMEs = ime_manager_get_enabled_ime_count();
    int nRet = get_last_result();
	PRINT_RESULT(IME_MANAGER_ERROR_PERMISSION_DENIED, nRet, "ime_manager_get_enabled_ime_count",InputmethodManagerGetError(nRet));

    return 0;
}













