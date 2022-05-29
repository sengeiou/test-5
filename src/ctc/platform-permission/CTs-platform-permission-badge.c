#include "CTs-platform-permission-common.h"
#include <badge.h>
//#define BUFFER 					512

bool g_bCallBackHit =false;
/**
* @function 		QuitGmainLoop
* @description	 	Called to quit
* @parameter		NA
* @return 			NA
*/
void QuitGmainLoop(void)
{
	if(g_pMainLoop != NULL)
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		CTs_platform_permission_badge_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_badge_startup(void)
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
* @function 		CTs_platform_permission_badge_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_badge_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
/**
* @function 		BadgeGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char *BadgeGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case BADGE_ERROR_NONE:		szErrorVal = "BADGE_ERROR_NONE";		break;
	case BADGE_ERROR_INVALID_PARAMETER:		szErrorVal = "BADGE_ERROR_INVALID_PARAMETER";		break;
	case BADGE_ERROR_OUT_OF_MEMORY:			szErrorVal = "BADGE_ERROR_OUT_OF_MEMORY";			break;
	case BADGE_ERROR_IO_ERROR:				szErrorVal = "BADGE_ERROR_IO_ERROR";				break;
	case BADGE_ERROR_FROM_DB:				szErrorVal = "BADGE_ERROR_FROM_DB";					break;
	case BADGE_ERROR_ALREADY_EXIST:			szErrorVal = "BADGE_ERROR_ALREADY_EXIST";			break;
	case BADGE_ERROR_FROM_DBUS:				szErrorVal = "BADGE_ERROR_FROM_DBUS";				break;
	case BADGE_ERROR_NOT_EXIST:				szErrorVal = "BADGE_ERROR_NOT_EXIST";				break;
	case BADGE_ERROR_PERMISSION_DENIED:		szErrorVal = "BADGE_ERROR_PERMISSION_DENIED";		break;
	case BADGE_ERROR_SERVICE_NOT_READY:		szErrorVal = "BADGE_ERROR_SERVICE_NOT_READY";		break;
	case BADGE_ERROR_INVALID_PACKAGE:		szErrorVal = "BADGE_ERROR_INVALID_PACKAGE";			break;
	default:								szErrorVal = "Unknown Error";						break;
	}

	return szErrorVal;
}
//& purpose: checking tizen.org/privilege/badge privilege
//& type: auto
/**
* @testcase			CTc_Badge_PrivilegeNotification_add
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Creates a badge for the application itself\n
* 					Removes the badge for the designated application
* @apicovered		badge_remove,badge_add
* @passcase			If all privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If all privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Badge_PrivilegeNotification_add(void)
{
	START_TEST;

	int nRet =  badge_add(/*BADGE_PACKAGE*/NULL);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "badge_add", BadgeGetError(nRet),badge_remove(BADGE_PACKAGE), BADGE_ERROR_NONE);

	return 0;
}
//& purpose: checking tizen.org/privilege/badge privilege
//& type: auto
/**
* @testcase			CTc_Badge_PrivilegeNotification_new
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Creates a badge for the application itself\n
* 					Removes the badge for the designated application
* @apicovered		badge_new, badge_remove
* @passcase			If all privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If all privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Badge_PrivilegeNotification_new(void)
{
	START_TEST;
	char *pszAppData = app_get_data_path(),*pszImgPath = NULL;
	if ( pszAppData == NULL || strlen(pszAppData) == 0 )
	{
		FPRINTF("[Line : %d][%s] app_get_data_path() is failed invalid path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	pszImgPath = (char*) calloc(1, strlen(pszAppData) + strlen(BADGE_PACKAGE)+1);
	if ( pszImgPath == NULL )
	{
		FPRINTF("[Line : %d][%s] memory allocation of pszImgPath failed \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	snprintf(pszImgPath, "%s%s",pszAppData, BADGE_PACKAGE, strlen(pszAppData) + strlen(BADGE_PACKAGE));
	FREE_MEMORY(pszAppData);

	
	int nRet = badge_new(pszImgPath);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "badge_new", BadgeGetError(nRet), badge_remove(pszImgPath);FREE_MEMORY(pszImgPath), BADGE_ERROR_NONE);
	
	
	
	FREE_MEMORY(pszImgPath);
	return 0;
}



