#include "CTs-platform-permission-common.h"
#include <app.h>
#include <app_manager.h>

#define APPID1 "org.tizen.testapplication"
#define TEST_TESTAPPLICATION_APPID	"org.tizen.testapplication"
#define TEST_APPMANAGERTESTFILE_APPID	"org.tizen.appmanagertestfile"

bool g_bAppManagerCallback = false;


/**
* @function 		AppManagerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
/*char* AppManagerGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case APP_MANAGER_ERROR_NONE:					szErrorVal = "APP_MANAGER_ERROR_NONE";						break;
	case APP_MANAGER_ERROR_INVALID_PARAMETER:		szErrorVal = "APP_MANAGER_ERROR_INVALID_PARAMETE";			break;
	case APP_MANAGER_ERROR_OUT_OF_MEMORY:			szErrorVal = "APP_MANAGER_ERROR_OUT_OF_MEMORY";				break;
	case APP_MANAGER_ERROR_IO_ERROR:				szErrorVal = "APP_MANAGER_ERROR_IO_ERROR";					break;
	case APP_MANAGER_ERROR_NO_SUCH_APP:				szErrorVal = "APP_MANAGER_ERROR_NO_SUCH_APP";				break;
	case APP_MANAGER_ERROR_DB_FAILED:				szErrorVal = "APP_MANAGER_ERROR_DB_FAILED";					break;
	case APP_MANAGER_ERROR_INVALID_PACKAGE:			szErrorVal = "APP_MANAGER_ERROR_INVALID_PACKAGE";			break;
	case APP_MANAGER_ERROR_APP_NO_RUNNING:			szErrorVal = "APP_MANAGER_ERROR_APP_NO_RUNNING";			break;
	case APP_MANAGER_ERROR_REQUEST_FAILED:			szErrorVal = "APP_MANAGER_ERROR_REQUEST_FAILED";			break;
	case APP_MANAGER_ERROR_PERMISSION_DENIED:		szErrorVal = "APP_MANAGER_ERROR_PERMISSION_DENIED";			break;
	default:										szErrorVal = "Unknown Error";								break;
	}

	return szErrorVal;
}
*/
/**
* @function 		AppManagerAppContextCallback
* @description	 	callback function to get the application context once for each running application
* @parameter		app_context : app context handle ,user_data : user data sent to callback
* @return 			NA
*/
bool AppManagerAppContextCallback(app_context_h app_context, void *user_data)
{
#if DEGUG
	FPRINTF("[Line : %d][%s] Callback AppManagerAppContextCallback is called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bAppManagerCallback = true;
	return g_bAppManagerCallback;
}
/**
* @function 		AppManagerAppContextChangeCallback
* @description	 	callback function for capturing context event change callbacks
* @parameter		app_context_h app_context, app_context_event_e event, void *user_data
* @return 			NA
*/
void AppManagerAppContextChangeCallback(app_context_h app_context, app_context_event_e event, void *user_data)
{
#if DEGUG
	FPRINTF("[Line : %d][%s] Callback AppManagerAppContextChangeCallback is called\\n", __LINE__, API_NAMESPACE);
#endif

	g_bAppManagerCallback = true;
}

/**
* @function 		AppInfoMetaDataFilterForeachCallback
* @description	 	callback function for capturing application filter metadata event callbacks
* @parameter		app_info : application info handle ,user_data : user data sent to callback
* @return 			NA
*/
bool AppInfoMetaDataFilterForeachCallback (app_info_h app_info, void *user_data)
{
#if DEGUG
	FPRINTF("[Line : %d][%s] Callback AppInfoMetaDataFilterForeachCallback is called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bAppManagerCallback = true;
	return g_bAppManagerCallback;
}
/**
* @function         CTs_platform_permission_appmanager_startup
* @description         Called before each test
* @parameter        NA
* @return             NA
*/
void CTs_platform_permission_appmanager_startup(void)
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
* @function         CTs_platform_permission_appmanager_cleanup
* @description         Called after each test
* @parameter        NA
* @return             NA
*/
void CTs_platform_permission_appmanager_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
    return;
}

//& purpose: checking http://tizen.org/privilege/packagemanager.info
//& type: auto
/**
* @testcase			CTc_AppManager_Privilege_PackagemanagerInfo_app_control_send_launch_request
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			app control send launch request
* @apicovered		app control send launch request
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_AppManager_Privilege_PackagemanagerInfo_app_control_send_launch_request(void)
{
	START_TEST;
	app_control_h app_control_handler = NULL;
	
	int nRet = app_control_create(&app_control_handler);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlPrintErrorInfo(nRet));
	if ( app_control_handler == NULL )
	{
		FPRINTF("[Line : %d][%s] app_control_create fail in startup created handle value null\\n", __LINE__, API_NAMESPACE);
		app_control_destroy(app_control_handler);
		return 1;
	}
	nRet = app_control_set_app_id(app_control_handler , APPID1);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlPrintErrorInfo(nRet), app_control_destroy(app_control_handler));	
	
	nRet = app_control_send_launch_request(app_control_handler , NULL , NULL);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "app_control_send_launch_request", AppControlPrintErrorInfo(nRet), app_control_destroy(app_control_handler));	

	app_control_destroy(app_control_handler);
	return 0;
}



