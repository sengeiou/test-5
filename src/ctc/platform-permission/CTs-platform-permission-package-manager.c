#include "CTs-platform-permission-common.h"


#define PACKAGE_NAME					"org.tizen.testapplication"
#define APPID1							"native-testapp-itc"

bool g_bCallbackReturnValue = false;
bool g_bCallbackHit =false;
package_size_info_h g_hSizeInfo;
GMainLoop *g_pPacakageManagerMainLoop;
package_manager_h g_hPackageManager;


/**
* @function 		PackageManagerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
/*char* PackageManagerGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case PACKAGE_MANAGER_ERROR_INVALID_PARAMETER:	szErrorVal = "PACKAGE_MANAGER_ERROR_INVALID_PARAMETER";		break;
	case PACKAGE_MANAGER_ERROR_OUT_OF_MEMORY:		szErrorVal = "PACKAGE_MANAGER_ERROR_OUT_OF_MEMORY";			break;
	case PACKAGE_MANAGER_ERROR_IO_ERROR:			szErrorVal = "PACKAGE_MANAGER_ERROR_IO_ERROR";				break;
	case PACKAGE_MANAGER_ERROR_NO_SUCH_PACKAGE:		szErrorVal = "PACKAGE_MANAGER_ERROR_NO_SUCH_PACKAGE";		break;
	default:										szErrorVal = "Unknown Error";								break;
	}
	return szErrorVal;
}*/

/**
* @function 		CTs_platform_permission_packagemanager_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_packagemanager_startup(void)
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
* @function 		CTs_platform_permission_packagemanager_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_packagemanager_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		PackageManagerPackageInfoCB
* @description	 	Callback function which is invoked when package_manager_foreach_package_info is called
* @parameter		package_info_s * package_info_h : package info , void *user_data: user data to be passed
* @return 			bool
*/
static bool PackageManagerPackageInfoCB(package_info_h hPackInfo,void *pUserData)
{
	g_bCallbackReturnValue = false;
	#if DEBUG
	FPRINTF("[Line : %d][%s] PackageManagerPackageInfoCB callback called\\n", __LINE__, API_NAMESPACE);
	#endif
	g_bCallbackHit = true;
	if ( hPackInfo == NULL )
	{
		FPRINTF("[Line : %d][%s] PackageManagerPackageInfoCB callback returned null package info\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = false;
	}
	else
	{
		g_bCallbackReturnValue = true;
	}
	if ( g_pPacakageManagerMainLoop )
	{
		g_main_loop_quit(g_pPacakageManagerMainLoop);
	}
	return false;
}
//& purpose: Checking tizen.org/privilege/packagemanager.info privilege
//& type: auto
/**
* @testcase			CTc_PackageInfo_PrivilegePackagemanagerInfo_create
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Creates a package manager handle\n
* 					Gets the package_id for the given app_id\n
* 					Gets the package information for the given package\n
* 					Destroys the package manager handle
* @apicovered		package_manager_create
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_PackageInfo_PrivilegePackagemanagerInfo_create(void)
{
	START_TEST;
	g_hPackageManager = NULL;

	int nRet = package_manager_create(&g_hPackageManager);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "package_manager_create", PackageManagerGetError(nRet), package_manager_destroy(g_hPackageManager), PACKAGE_MANAGER_ERROR_NONE);

	return 0;
}
//& purpose: Checking tizen.org/privilege/packagemanager.info privilege
//& type: auto
/**
* @testcase			CTc_PackageInfo_PrivilegePackagemanagerInfor_filter_create
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Creates a package manager handle\n
* 					Gets the package_id for the given app_id\n
* 					Gets the package information for the given package\n
* 					Destroys the package manager handle
* @apicovered		package_manager_filter_create
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_PackageInfo_PrivilegePackagemanagerInfor_filter_create(void)
{
	START_TEST;
	package_manager_filter_h hAppfwPackageManagerFilterHandler;

	int nRet = package_manager_filter_create(&hAppfwPackageManagerFilterHandler);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "package_manager_filter_create", PackageManagerGetError(nRet),package_manager_filter_destroy(hAppfwPackageManagerFilterHandler), PACKAGE_MANAGER_ERROR_NONE);

	return 0;
}
//& purpose: Checking tizen.org/privilege/packagemanager.info privilege
//& type: auto
/**
* @testcase			CTc_PackageInfo_PrivilegePackagemanagerInfo_get_package_id_by_app_id
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Creates a package manager handle\n
* 					Gets the package_id for the given app_id\n
* 					Gets the package information for the given package\n
* 					Destroys the package manager handle
* @apicovered		 package_manager_get_package_id_by_app_id
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_PackageInfo_PrivilegePackagemanagerInfo_get_package_id_by_app_id(void)
{
	START_TEST;
	char *pszPkgId = NULL;
	
	int nRet = package_manager_get_package_id_by_app_id (PACKAGE_NAME, &pszPkgId);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));

	return 0;
}
//& purpose: Checking tizen.org/privilege/packagemanager.info privilege
//& type: auto
/**
* @testcase	 			CTc_PackageInfo_PrivilegePackagemanagerInfo_foreach_package_info
* @author             	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Retrieves all package information of installed packages
* @scenario				Retrieve all package information of installed packages\n
* 						forreach package info
* 						Cleanup all resources
* @apicovered			package_manager_foreach_package_info
* @precondition			NA
* @postcondition		NA
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
*/
int CTc_PackageInfo_PrivilegePackagemanagerInfo_foreach_package_info(void)
{
	START_TEST;
	
	//target API
	int nRet = package_manager_foreach_package_info(PackageManagerPackageInfoCB, NULL);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "package_manager_foreach_package_info", PackageManagerGetError(nRet));
	
	return 0;
}
//& purpose: Checking tizen.org/privilege/packagemanager.info privilege
//& type: auto
/**
* @testcase	 			CTc_PackageInfo_PrivilegePackagemanagerInfo_preload_package_by_app_id
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves all package information of installed packages
* @scenario				Retrieve all package information of installed packages\n
* 						preload package by app id
* 						Cleanup all resources
* @apicovered			package_manager_is_preload_package_by_app_id
* @precondition			NA
* @postcondition		NA
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
*/
int CTc_PackageInfo_PrivilegePackagemanagerInfo_preload_package_by_app_id(void)
{
	START_TEST;
	bool bPreload = false;

	//target API
	int nRet =  package_manager_is_preload_package_by_app_id(APPID1,&bPreload);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "package_manager_is_preload_package_by_app_id", PackageManagerGetError(nRet));

	return 0;
}
	
//& purpose: Checking tizen.org/privilege/packagemanager.info privilege
//& type: auto
/**
* @testcase	 			CTc_PackageInfo_PrivilegePackagemanagerInfo_get_permission_type
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves all package information of installed packages
* @scenario				Retrieve all package information of installed packages\n
*						get package permission type
* @apicovered			package_manager_get_permission_type
* @precondition			NA
* @postcondition		NA
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
*/
int CTc_PackageInfo_PrivilegePackagemanagerInfo_get_permission_type(void)
{
	START_TEST;
	package_manager_permission_type_e ePermission = -1;

	//target API
	int nRet =   package_manager_get_permission_type(APPID1,&ePermission);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "package_manager_get_permission_type", PackageManagerGetError(nRet));
	return 0;
}
