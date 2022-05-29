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
#include "ITs-package-manager-common.h"

/** @addtogroup itc-package-manager
*  @ingroup itc
*  @{
*/

static bool g_packageManagerAllowed;
static bool g_isAllowedPackageCBHit;

//& set: PackageInfoForeachRequiredPrivilege

static bool PackageManagerPrivilegeCB(const char *privilege_name, void *user_data)
{
	FPRINTF("[Line : %d][%s] PackageManagerPrivilegeCB callback called\\n", __LINE__, API_NAMESPACE);
	return true;
}

static bool PackageManagerAllowedPackageCB(const char *allowed_package, allowed_package_required_privilege_h privilege_handle, void *user_data)
{
	g_isAllowedPackageCBHit = true;
	FPRINTF("[Line : %d][%s] PackageManagerAllowedPackageCB callback called\\n", __LINE__, API_NAMESPACE);
	int nRet = package_info_foreach_required_privilege(privilege_handle, PackageManagerPrivilegeCB, NULL);
	if( nRet == PACKAGE_MANAGER_ERROR_NONE)
	{
		g_packageManagerAllowed = true;
	}
	return true;
}
//Callbacks

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

/**
* @function 		PackageManagerEventCB
* @description	 	Callback function to be invoked when the package is installed, uninstalled or updated.
* @parameter		const char *pszType,const char *pszPkg, package_manager_event_type_e eEventType,package_manager_event_state_e eEventState,int progress,package_manager_error_e eErr,void *pUserData
* @return 			NA
*/
static void PackageManagerEventCB(const char *pszType,const char *pszPkg, package_manager_event_type_e eEventType,
								  package_manager_event_state_e eEventState,
								  int progress,
								  package_manager_error_e eErr,
								  void *pUserData)
{
	g_bCallbackReturnValue = false;
#if DEBUG
	FPRINTF("[Line : %d][%s] PackageManagerEventCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	if ( pszType == NULL || pszPkg == NULL || progress< 0 || progress > 100 )
	{
		FPRINTF("[Line : %d][%s] PackageManagerEventCB callback returned null package type and package\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = false;
	}
	else
	{
		g_bCallbackReturnValue = true;
	}
	switch ( eEventType )
	{
	case PACKAGE_MANAGER_EVENT_TYPE_INSTALL:
		FPRINTF("[Line : %d][%s] Event type: PACKAGE_MANAGER_EVENT_TYPE_INSTALL\\n", __LINE__, API_NAMESPACE);
		if (g_bEventTypeInstall == true)
		{
			g_bCallbackReturnValue = true;
		}
		break;
	case PACKAGE_MANAGER_EVENT_TYPE_UNINSTALL:
		FPRINTF("[Line : %d][%s] Event type: PACKAGE_MANAGER_EVENT_TYPE_UNINSTALL\\n", __LINE__, API_NAMESPACE);
		if (g_bEventTypeInstall == false )
		{
			g_bCallbackReturnValue = true;
		}
		break;
	case PACKAGE_MANAGER_EVENT_TYPE_UPDATE:
		FPRINTF("[Line : %d][%s] Event type: PACKAGE_MANAGER_EVENT_TYPE_UPDATE\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	case PACKAGE_MANAGER_EVENT_TYPE_MOVE:
		FPRINTF("[Line : %d][%s] Event type: PACKAGE_MANAGER_EVENT_TYPE_MOVE\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	case PACKAGE_MANAGER_EVENT_TYPE_CLEAR:
		FPRINTF("[Line : %d][%s] Event type: PACKAGE_MANAGER_EVENT_TYPE_CLEAR\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	}
	switch ( eEventState )
	{
	case PACKAGE_MANAGER_EVENT_STATE_STARTED:
		FPRINTF("[Line : %d][%s] Event State: PACKAGE_MANAGER_EVENT_STATE_STARTED\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	case PACKAGE_MANAGER_EVENT_STATE_PROCESSING:
		FPRINTF("[Line : %d][%s] Event State: PACKAGE_MANAGER_EVENT_STATE_PROCESSING\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	case PACKAGE_MANAGER_EVENT_STATE_COMPLETED:
		FPRINTF("[Line : %d][%s] Event State: PACKAGE_MANAGER_EVENT_STATE_COMPLETED\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	case PACKAGE_MANAGER_EVENT_STATE_FAILED:
		FPRINTF("[Line : %d][%s] Event State: PACKAGE_MANAGER_EVENT_STATE_FAILED\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	}

	if ( g_pPacakageManagerMainLoop )
	{
		g_main_loop_quit(g_pPacakageManagerMainLoop);
	}
	return;
}


/**
* @function 		PackageManagerSizeInfoCB
* @description	 	Called to get the size info.
* @parameter		const char *package_id, const package_size_info_h size_info, void *user_data
* @return 			NA
*/
static void PackageManagerSizeInfoCB(const char *package_id, const package_size_info_h size_info, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] PackageManagerSizeInfoCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	g_hSizeInfo = size_info;
	
	if ( g_pPacakageManagerMainLoop )
	{
		g_main_loop_quit(g_pPacakageManagerMainLoop);
	}
}

/**
* @function 		PackageManagerTotalSizeInfoCB
* @description	 	Called to get the size info.
* @parameter		const package_size_info_h size_info, void *user_data
* @return 			NA
*/
static void PackageManagerTotalSizeInfoCB(const package_size_info_h size_info, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] PackageManagerTotalSizeInfoCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	g_hSizeInfo = size_info;
	if ( g_pPacakageManagerMainLoop )
	{
		g_main_loop_quit(g_pPacakageManagerMainLoop);
	}
}


/**
* @function 		ITs_package_manager_startup
* @description	 	Called before each test, created package manager handle
* @parameter		NA
* @return 			NA
*/ 
void ITs_package_manager_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Package_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(3, TEST_NATIVETESTAPP_APPID, TEST_TESTAPP_APPID, TEST_SAMPLE_TESTAPP_APPID);
	int nRet = package_manager_create(&g_hAppfwPackageManagerHandler);
	if ( nRet != PACKAGE_MANAGER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] package_manager_create failed, error returned = %s\\n", __LINE__, API_NAMESPACE, PackageManagerGetError(nRet));
		g_bPackageManagerCreation = false;
	}
	else
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] Package Manager created successfully\\n", __LINE__, API_NAMESPACE);
#endif
		g_bPackageManagerCreation = true;
	}
	return;
}

/**
* @function 		ITs_package_manager_cleanup
* @description	 	Called after each test, destroys package manager handle
* @parameter		NA
* @return 			NA
*/ 
void ITs_package_manager_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Package_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet = package_manager_destroy(g_hAppfwPackageManagerHandler);
	if ( nRet != PACKAGE_MANAGER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] package_manager_destroy failed, error returned = %s\\n", __LINE__, API_NAMESPACE, PackageManagerGetError(nRet));
	}
	sleep(SLEEP_TIME);
	return;
}

/** @addtogroup itc-package-manager-testcases
*  @brief 		Integration testcases for module package-manager
*  @ingroup 	itc-package-manager
*  @{
*/


//& purpose: This API executes the user supplied callback function for each package that satisfy the filter conditions
//& type: auto

/**
* @testcase	 			ITc_package_manager_filter_foreach_package_info_p
* @since_tizen 			2.3
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This API executes the user supplied callback function for each package that satisfy the filter conditions
* @scenario				Create filter\n
* 						Check if callback is thrown or not\n
* 						Destroys the package information filter handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_manager_filter_foreach_package_info
* @precondition			NA
* @postcondition		NA
* @passcase				If all the pre conditions are met and packages should be traversed first
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_filter_foreach_package_info_p(void)
{
	START_TEST;
	int nRet = -1, nTimeoutId = 0;
	package_manager_filter_h hAppfwPackageManagerFilterHandler;

	nRet = package_manager_filter_create(&hAppfwPackageManagerFilterHandler);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_filter_create", PackageManagerGetError(nRet));
	CHECK_HANDLE(hAppfwPackageManagerFilterHandler, "package_manager_filter_create");

	nRet = package_manager_filter_add_bool(hAppfwPackageManagerFilterHandler,FILTER_PROPERTY, true);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_filter_add_bool", PackageManagerGetError(nRet), package_manager_filter_destroy(hAppfwPackageManagerFilterHandler));

	g_bCallbackHit = false;
	g_bCallbackReturnValue = false;

	//target API
	nRet = package_manager_filter_foreach_package_info (hAppfwPackageManagerFilterHandler,PackageManagerPackageInfoCB, USER_DATA);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_filter_foreach_package_info", PackageManagerGetError(nRet), package_manager_filter_destroy(hAppfwPackageManagerFilterHandler));

	nRet = package_manager_foreach_package_info(PackageManagerPackageInfoCB, USER_DATA);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_foreach_package_info", PackageManagerGetError(nRet), package_manager_filter_destroy(hAppfwPackageManagerFilterHandler));
	if ( g_bCallbackHit == false || g_bCallbackReturnValue == false )
	{
		FPRINTF("[Line : %d][%s] package_manager_foreach_package_info failed, error = callback not invoked\\n", __LINE__, API_NAMESPACE);
		package_manager_filter_destroy(hAppfwPackageManagerFilterHandler);
		return 1;
	}

	nRet = package_manager_filter_destroy(hAppfwPackageManagerFilterHandler);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_filter_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Retrieves all package information of installed packages. 
//& type: auto

/**
* @testcase	 			ITc_package_manager_foreach_package_info_p
* @since_tizen 			2.3
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves all package information of installed packages
* @scenario				Retrieve all package information of installed packages\n
* 						Check if callback is thrown or not\n
* 						Get a package info\n
* 						Check the package is invalid or not\n
* 						Destroys the package information handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_manager_foreach_package_info
* @precondition			NA
* @postcondition		NA
* @passcase				If all the pre conditions are met and packages should be traversed first
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_foreach_package_info_p(void)
{
	START_TEST;
	int nRet = -1, nTimeoutId = 0;
	g_bCallbackHit = false;
	g_bCallbackReturnValue = false;

	//target API
	nRet = package_manager_foreach_package_info (PackageManagerPackageInfoCB, USER_DATA);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_foreach_package_info", PackageManagerGetError(nRet));

	if ( g_bCallbackHit == false || g_bCallbackReturnValue == false )
	{
		FPRINTF("[Line : %d][%s] package_manager_foreach_package_info failed, error = callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Creates/Destroys a package manager handle.
//& type: auto

/**
* @testcase 			ITc_package_manager_create_destroy_p
* @since_tizen 			2.3
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates/Destroys a package manager handle.
* @scenario				Creates a package manager handle\n
* 						Destroys the package manager handle\n
* 						Cleanup all resources
* @apicovered			package_manager_create, package_manager_destroy
* @precondition			NA
* @postcondition		NA
* @passcase				If all the pre conditions are met and package handler created
* @failcase				If API fails to complete the scenario cycle in pass case
* @remarks				The manager must be released using package_manager_destroy
*/
int ITc_package_manager_create_destroy_p(void)
{
	START_TEST;

	package_manager_h hAppfwPackageManagerHandler;

	// Target API
	int nRet = package_manager_create(&hAppfwPackageManagerHandler);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_create", PackageManagerGetError(nRet));

	// Target API
	nRet = package_manager_destroy(hAppfwPackageManagerHandler);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Compares whether two app certification are matched.
//& type: auto

/**
* @testcase				ITc_package_manager_compare_app_cert_info_p
* @since_tizen 			2.3
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Compares whether two app certification are matched
* @scenario				compare whether two app certification are matched\n
* 						Cleanup all resources
* @apicovered			package_manager_compare_app_cert_info
* @precondition			none
* @postcondition		NA
* @passcase				When package_manager_compare_app_cert_info successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_compare_app_cert_info_p(void)
{
	START_TEST;
	int nRet = -1;
	package_manager_compare_result_type_e eCompResult = -1;
	//target API
	nRet = package_manager_compare_app_cert_info(TEST_NATIVETESTAPP_APPID, TEST_TESTAPP_APPID, &eCompResult);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_compare_app_cert_info", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Compares whether two package certifications are matched
//& type: auto

/**
* @testcase 			ITc_package_manager_compare_package_cert_info_p
* @since_tizen 			2.3
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Compares whether two package certifications are matched
* @scenario				Compares whether two package certifications are matched\n
* 						Destroys the package information handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_manager_compare_package_cert_info
* @precondition			none
* @postcondition		NA
* @passcase				When package_manager_compare_package_cert_info is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_compare_package_cert_info_p(void)
{
	START_TEST;

	char *pszPkgId1 = NULL;
	char *pszPkgId2 = NULL;
	package_manager_compare_result_type_e eCompResult = -1;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId1);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId1 == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}

	nRet = package_manager_get_package_id_by_app_id(TEST_TESTAPP_APPID, &pszPkgId2);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId2 == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_TESTAPP_APPID);
		return 1;
	}

	//target API
	nRet = package_manager_compare_package_cert_info (pszPkgId1, pszPkgId2, &eCompResult);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_compare_package_cert_info", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Gets the package_id for the given app_id.
//& type: auto

/**
* @testcase 			ITc_package_manager_get_package_id_by_app_id_p
* @since_tizen 			2.3
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the package_id for the given app_id.
* @scenario				Gets the package_id for the given app_id\n
* 						Destroys the package information handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_manager_get_package_id_by_app_id
* @precondition			none
* @postcondition		NA
* @passcase				When package_manager_get_package_id_by_app_id is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_get_package_id_by_app_id_p(void)
{
	START_TEST;

	char *pszPkgId = NULL;

	//target API
	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if (pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}
	return 0;
}

//& purpose: Gets/Destroys the package information for the given package. 
//& type: auto

/**
* @testcase 			ITc_package_manager_get_destroy_package_info_p
* @since_tizen 			2.3
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets/Destroys the package information for the given package.
* @scenario				Gets the package_id for the given app_id.
* 						Gets the package information for the given package.
* 						Destroys the package information handle and releases all its resources. 
* 						Cleanup all resources
* @apicovered			package_manager_get_package_info, package_info_destroy
* @precondition			none
* @postcondition		package_info must be released using package_info_destroy
* @passcase				If all the pre conditions are met and package by app id should be traversed first
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_get_destroy_package_info_p(void)
{
	START_TEST;

	char *pszPkgId = NULL;
	package_info_h 	hPkgInfo;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}

	//target API
	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	//target API
	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));
	FREE_MEMORY(pszPkgId);
	return 0;
}

//& purpose: Checks whether the package is preload or not by app_id. 
//& type: auto

/**
* @testcase	 			ITc_package_manager_is_preload_package_by_app_id_p
* @since_tizen 			2.3
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Checks whether the package is preload or not by app_id. 
* @scenario				Checks whether the package is preload or not by app_id.
* @apicovered			package_manager_is_preload_package_by_app_id
* @precondition			none
* @postcondition		NA
* @passcase				If API returns PACKAGE_MANAGER_ERROR_NONE
* @failcase				If API returns negative error value
*/
int ITc_package_manager_is_preload_package_by_app_id_p(void)
{
	START_TEST;

	bool bPreload = false;

	//target API
	int nRet =  package_manager_is_preload_package_by_app_id(TEST_NATIVETESTAPP_APPID,&bPreload);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_is_preload_package_by_app_id", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Gets the package permission type by app_id.
//& type: auto

/**
* @testcase				ITc_package_manager_get_permission_type_p
* @since_tizen 			2.3
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the package permission type by app_id.
* @scenario				Gets the package permission type by app_id.
* 						Destroys the package information handle and releases all its resources.
* 						Cleanup all resources
* @apicovered			package_manager_get_permission_type
* @precondition			none
* @postcondition		NA
* @passcase				If all the pre conditions are met and package by app id should be traversed first
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_get_permission_type_p(void)
{
	START_TEST;

	package_manager_permission_type_e ePermission = -1;

	//target API
	int nRet =   package_manager_get_permission_type(TEST_TESTAPP_APPID,&ePermission);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_permission_type", PackageManagerGetError(nRet));
	if ( ePermission == -1 )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_permission_type failed, error = invalid permission type\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Registers/Unregisters a callback function to be invoked when the package is installed, uninstalled or updated.
//& type: auto

/**
* @testcase				ITc_package_manager_set_unset_event_cb_p
* @since_tizen 			2.3
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Registers/Unregisters a callback function to be invoked when the package is installed, uninstalled or updated.
* @scenario				Registers a callback function to be invoked when the package is installed, uninstalled or updated\n
* 						Unregisters the callback function\n
* 						Cleanup all resources
* @apicovered			package_manager_set_event_cb ,package_manager_unset_event_cb
* @precondition			NA
* @postcondition		NA
* @passcase				If all the pre conditions are met
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_set_unset_event_cb_p(void)
{
	START_TEST;
	int nRet = -1;
	// target API
	nRet = package_manager_set_event_cb(g_hAppfwPackageManagerHandler, PackageManagerEventCB, USER_DATA);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_set_event_cb", PackageManagerGetError(nRet));

	// target API
	nRet = package_manager_unset_event_cb(g_hAppfwPackageManagerHandler);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_unset_event_cb", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Set the event of status of package when the package is installed, uninstalled or updated
//& type: auto

/**
* @testcase 			ITc_package_manager_set_event_status_p
* @since_tizen 			2.3
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description 			Set the event of status of package when the package is installed, uninstalled or updated
* @scenario				Creates package manager handle\n
* 						Set the event of status of package\n
* 						Destroys the package manager handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_manager_set_event_status
* @precondition			NA
* @postcondition		NA
* @passcase				If package_manager_set_event_status is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_set_event_status_p(void)
{
	START_TEST;
	int nRet = -1;
	int nStatusType = 1;

	//target API
	nRet = package_manager_set_event_status(g_hAppfwPackageManagerHandler, nStatusType);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_set_event_status", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Creates/Destroys the package information filter handle from db.
//& type: auto

/**
* @testcase 			ITc_package_manager_filter_create_destroy_p
* @since_tizen 			2.3
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates/Destroys the package information filter handle from db.
* @scenario				Create package information filter handle\n
* 						Destroy the package information filter handle\n
* 						Cleanup all resources
* @apicovered			package_manager_filter_create, package_manager_filter_destroy
* @precondition			NA
* @postcondition		NA
* @passcase				If all the pre conditions are met and package information filter handler created
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_filter_create_destroy_p(void)
{
	START_TEST;
	int nRet = -1;
	package_manager_filter_h hAppfwPackageManagerFilterHandler;
	// Target API
	nRet = package_manager_filter_create(&hAppfwPackageManagerFilterHandler);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_filter_create", PackageManagerGetError(nRet));

	// Target API
	nRet = package_manager_filter_destroy(hAppfwPackageManagerFilterHandler);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_filter_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Counts the package that satisfy the filter conditions
//& type: auto

/**
* @testcase	 			ITc_package_manager_filter_count_p
* @since_tizen 			2.3
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Counts the package that satisfy the filter conditions
* @scenario				Create filter
* 						Check count
* 						Destroys the package information filter handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_manager_filter_count()
* @precondition			NA
* @postcondition		NA
* @passcase				If it returns 0
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_filter_count_p(void)
{
	START_TEST;
	int nRet = -1;
	package_manager_filter_h hAppfwPackageManagerFilterHandler;
	int nCount = -1;

	nRet = package_manager_filter_create(&hAppfwPackageManagerFilterHandler);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_filter_create", PackageManagerGetError(nRet));

	nRet = package_manager_filter_add_bool(hAppfwPackageManagerFilterHandler,FILTER_PROPERTY, true);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_filter_add_bool", PackageManagerGetError(nRet), package_manager_filter_destroy(hAppfwPackageManagerFilterHandler));

	//target API
	nRet = package_manager_filter_count(hAppfwPackageManagerFilterHandler,&nCount);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_filter_count", PackageManagerGetError(nRet), package_manager_filter_destroy(hAppfwPackageManagerFilterHandler));

	nRet = package_manager_filter_destroy(hAppfwPackageManagerFilterHandler);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_filter_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Counts the package that satisfy the filter conditions
//& type: auto

/**
* @testcase	 			ITc_package_manager_filter_add_bool_p
* @since_tizen 			2.3
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Counts the package that satisfy the filter conditions
* @scenario				Create filter\n
* 						Check count\n
* 						Destroys the package information filter handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_manager_filter_add_bool
* @precondition			NA
* @postcondition		NA
* @passcase				If it returns 0
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_filter_add_bool_p(void)
{
	START_TEST;
	int nRet = -1;
	package_manager_filter_h hAppfwPackageManagerFilterHandler;

	nRet = package_manager_filter_create(&hAppfwPackageManagerFilterHandler);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_filter_create", PackageManagerGetError(nRet));

	//target API
	nRet = package_manager_filter_add_bool(hAppfwPackageManagerFilterHandler,FILTER_PROPERTY, true);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_filter_add_bool", PackageManagerGetError(nRet), package_manager_filter_destroy(hAppfwPackageManagerFilterHandler));

	nRet = package_manager_filter_destroy(hAppfwPackageManagerFilterHandler);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_filter_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Test-case for package_manager_clear_cache_dir
//& type: auto

/**
* @testcase 			ITc_package_manager_clear_cache_dir_p
* @since_tizen 			2.4
* @author             	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		clear_cache_dir
* @scenario				Call package_manager_clear_cache_dir
* @apicovered			package_manager_clear_cache_dir
* @precondition			none
* @postcondition		NA
* @passcase				When package_manager_clear_cache_dir is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_clear_cache_dir_p(void)
{
	START_TEST;

	char *pszPkgId = NULL;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}
	
	nRet = package_manager_clear_cache_dir(pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_clear_cache_dir", PackageManagerGetError(nRet));
	
	return 0;
}

//& purpose: Test-case for package_manager_get_package_size_info
//& type: auto

/**
* @testcase 			ITc_package_manager_get_package_size_info_p
* @since_tizen 			2.4
* @author             	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Test package_manager_get_package_size_info
* @scenario				Call package_manager_get_package_size_info
* @apicovered			package_manager_get_package_size_info
* @precondition			none
* @postcondition		NA
* @passcase				When package_manager_get_package_size_info is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_get_package_size_info_p(void)
{
	START_TEST;

	char *pszPkgId = NULL;
	int nTimeoutId = 0;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}
	
	g_bCallbackHit  = false;
	nRet = package_manager_get_package_size_info(pszPkgId, PackageManagerSizeInfoCB, NULL);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_size_info", PackageManagerGetError(nRet));
	RUN_POLLING_LOOP;
	if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_size_info failed, error = callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& purpose: Test-case for package_size_info_get_data_size
//& type: auto

/**
* @testcase 			ITc_package_size_info_get_data_size_p
* @since_tizen 			2.4
* @author             	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Test package_size_info_get_data_size
* @scenario				Call package_size_info_get_data_size
* @apicovered			package_size_info_get_data_size
* @precondition			none
* @postcondition		NA
* @passcase				When package_size_info_get_data_size is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_size_info_get_data_size_p(void)
{
	START_TEST;
	
	long long llSize;
	char *pszPkgId = NULL;
	int nTimeoutId = 0;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}
	
	g_bCallbackHit  = false;
	nRet = package_manager_get_package_size_info(pszPkgId, PackageManagerSizeInfoCB, NULL);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_size_info", PackageManagerGetError(nRet));
	RUN_POLLING_LOOP;
	if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_size_info failed, error = callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	CHECK_HANDLE(g_hSizeInfo, "package_manager_get_package_size_info");
	
	nRet = package_size_info_get_data_size(g_hSizeInfo, &llSize);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_size_info_get_data_size", PackageManagerGetError(nRet));
	
	return 0;
}

//& purpose: Test-case for package_size_info_get_cache_size
//& type: auto

/**
* @testcase 			ITc_package_size_info_get_cache_size_p
* @since_tizen 			2.4
* @author             	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Test package_size_info_get_cache_size
* @scenario				Call package_size_info_get_cache_size
* @apicovered			package_size_info_get_cache_size
* @precondition			none
* @postcondition		NA
* @passcase				When package_size_info_get_cache_size is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_size_info_get_cache_size_p(void)
{
	START_TEST;
	
	long long llSize;
	char *pszPkgId = NULL;
	int nTimeoutId = 0;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}
	
	g_bCallbackHit  = false;
	nRet = package_manager_get_package_size_info(pszPkgId, PackageManagerSizeInfoCB, NULL);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_size_info", PackageManagerGetError(nRet));
	RUN_POLLING_LOOP;
	if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_size_info failed, error = callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	CHECK_HANDLE(g_hSizeInfo, "package_manager_get_package_size_info");
	
	nRet = package_size_info_get_cache_size(g_hSizeInfo, &llSize);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_size_info_get_cache_size", PackageManagerGetError(nRet));
	
	return 0;
}

//& purpose: Test-case for package_size_info_get_app_size
//& type: auto

/**
* @testcase 			ITc_package_size_info_get_app_size_p
* @since_tizen 			2.4
* @author             	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Test package_size_info_get_app_size
* @scenario				Call package_size_info_get_app_size
* @apicovered			package_size_info_get_app_size
* @precondition			none
* @postcondition		NA
* @passcase				When package_size_info_get_app_size is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_size_info_get_app_size_p(void)
{
	START_TEST;
	
	long long llSize;
	char *pszPkgId = NULL;
	int nTimeoutId = 0;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}
	
	g_bCallbackHit  = false;
	nRet = package_manager_get_package_size_info(pszPkgId, PackageManagerSizeInfoCB, NULL);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_size_info", PackageManagerGetError(nRet));
	RUN_POLLING_LOOP;
	if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_size_info failed, error = callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	CHECK_HANDLE(g_hSizeInfo, "package_manager_get_package_size_info");
	
	nRet = package_size_info_get_app_size(g_hSizeInfo, &llSize);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_size_info_get_app_size", PackageManagerGetError(nRet));
	
	return 0;
}

//& purpose: Test-case for package_size_info_get_external_data_size
//& type: auto

/**
* @testcase 			ITc_package_size_info_get_external_data_size_p
* @since_tizen 			2.4
* @author             	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Test package_size_info_get_external_data_size
* @scenario				Call package_size_info_get_external_data_size
* @apicovered			package_size_info_get_external_data_size
* @precondition			none
* @postcondition		NA
* @passcase				When package_size_info_get_external_data_size is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_size_info_get_external_data_size_p(void)
{
	START_TEST;
	
	long long llSize;
	char *pszPkgId = NULL;
	int nTimeoutId = 0;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}
	
	g_bCallbackHit  = false;
	nRet = package_manager_get_package_size_info(pszPkgId, PackageManagerSizeInfoCB, NULL);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_size_info", PackageManagerGetError(nRet));
	RUN_POLLING_LOOP;
	if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_size_info failed, error = callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	CHECK_HANDLE(g_hSizeInfo, "package_manager_get_package_size_info");
	
	nRet = package_size_info_get_external_data_size(g_hSizeInfo, &llSize);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_size_info_get_external_data_size", PackageManagerGetError(nRet));
	
	return 0;
}

//& purpose: Test-case for package_size_info_get_external_cache_size
//& type: auto

/**
* @testcase 			ITc_package_size_info_get_external_cache_size_p
* @since_tizen 			2.4
* @author             	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Test package_size_info_get_external_cache_size
* @scenario				Call package_size_info_get_external_cache_size
* @apicovered			package_size_info_get_external_cache_size
* @precondition			none
* @postcondition		NA
* @passcase				When package_size_info_get_external_cache_size is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_size_info_get_external_cache_size_p(void)
{
	START_TEST;
	
	long long llSize;
	char *pszPkgId = NULL;
	int nTimeoutId = 0;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}
	
	g_bCallbackHit  = false;
	nRet = package_manager_get_package_size_info(pszPkgId, PackageManagerSizeInfoCB, NULL);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_size_info", PackageManagerGetError(nRet));
	RUN_POLLING_LOOP;
	if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_size_info failed, error = callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	CHECK_HANDLE(g_hSizeInfo, "package_manager_get_package_size_info");
	
	nRet = package_size_info_get_external_cache_size(g_hSizeInfo, &llSize);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_size_info_get_external_cache_size", PackageManagerGetError(nRet));
	
	return 0;
}

//& purpose: Test-case for package_size_info_get_external_app_size
//& type: auto

/**
* @testcase 			ITc_package_size_info_get_external_app_size_p
* @since_tizen 			2.4
* @author             	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Test package_size_info_get_external_app_size
* @scenario				Call package_size_info_get_external_app_size
* @apicovered			package_size_info_get_external_app_size
* @precondition			none
* @postcondition		NA
* @passcase				When package_size_info_get_external_app_size is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_size_info_get_external_app_size_p(void)
{
	START_TEST;
	
	long long llSize;
	char *pszPkgId = NULL;
	int nTimeoutId = 0;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}
	
	g_bCallbackHit  = false;
	nRet = package_manager_get_package_size_info(pszPkgId, PackageManagerSizeInfoCB, NULL);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_size_info", PackageManagerGetError(nRet));
	RUN_POLLING_LOOP;
	if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_size_info failed, error = callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	CHECK_HANDLE(g_hSizeInfo, "package_manager_get_package_size_info");
	
	nRet = package_size_info_get_external_app_size(g_hSizeInfo, &llSize);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_size_info_get_external_app_size", PackageManagerGetError(nRet));
	
	return 0;
}

//& purpose: Test-case for package_archive_info_create and package_archive_info_destroy
//& type: auto

/**
* @testcase 		ITc_package_archive_info_create_destroy_p
* @since_tizen 		4.0
* @author             	SRID(j.abhishek)
* @reviewer         	SRID(nibha.sharma)
* @type 		auto
* @description	 	Test package_archive_info_create and package_archive_info_destroy
* @scenario		Call package_archive_info_create and then call package_archive_info_destroy
* @apicovered		package_archive_info_create, package_archive_info_destroy
* @precondition		resource path must be opted using app_get_shared_resource_path
* @postcondition	NA
* @passcase		When package_archive_info_create and package_archive_info_destroy are successful
* @failcase		If API fails to complete the scenario cycle in pass case
*/

int ITc_package_archive_info_create_destroy_p(void)
{
	START_TEST;
	
	char fileName[] = TEST_TESTAPP_NAME;
	char *pszResPath = NULL;
	char filePath[128];
	package_archive_info_h hArchiveInfo;

	int nRet = PACKAGE_MANAGER_ERROR_NONE;

	pszResPath = app_get_shared_resource_path();
	if ( pszResPath == NULL )
	{
		FPRINTF("[Line : %d][%s] app_get_shared_resource_path failed, error = NULL resource path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	snprintf(filePath, sizeof(filePath), "%s/%s", pszResPath, fileName);

	nRet = package_archive_info_create(filePath, &hArchiveInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_create", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath));

	if ( hArchiveInfo == NULL )
	{
		FPRINTF("[Line : %d][%s] package_archive_info_create failed to create, error = NULL  for [%s]\\n", __LINE__, API_NAMESPACE, TEST_TESTAPP_NAME);
		FREE_MEMORY(pszResPath);
		return 1;
	}

	nRet = package_archive_info_destroy(hArchiveInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath));

	FREE_MEMORY(pszResPath);
	return 0;
}


//& purpose: Test-case for package_archive_info_get_api_version
//& type: auto

/**
* @testcase 		ITc_package_archive_info_get_api_version_p
* @since_tizen 		4.0
* @author             	SRID(j.abhishek)
* @reviewer         	SRID(nibha.sharma)
* @type 		auto
* @description	 	Test package_archive_info_get_api_version
* @scenario		Call package_archive_info_get_api_version
* @apicovered		package_archive_info_get_api_version
* @precondition		archieve info must be created using package_archive_info_create API
* @postcondition	archieve info must be destroyed using package_archive_info_destroy API
* @passcase		When package_archive_info_get_api_version is successful
* @failcase		If API fails to complete the scenario cycle in pass case
*/
int ITc_package_archive_info_get_api_version_p(void)
{
	START_TEST;
	
	char fileName[] = TEST_TESTAPP_NAME;
	char *pszResPath = NULL;
	char filePath[128];
	package_archive_info_h hArchiveInfo;
	
	char *pszAPIVersion = NULL;
	const char *TargetAPIVersion = TESTAPP_API_VESION;

	int nRet = PACKAGE_MANAGER_ERROR_NONE;

	pszResPath = app_get_shared_resource_path();
	if ( pszResPath == NULL )
	{
		FPRINTF("[Line : %d][%s] app_get_shared_resource_path failed, error = NULL resource path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	snprintf(filePath, sizeof(filePath), "%s/%s", pszResPath, fileName);

	nRet = package_archive_info_create(filePath, &hArchiveInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_create", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath));

	if ( hArchiveInfo == NULL )
	{
		FPRINTF("[Line : %d][%s] package_archive_info_create failed to create, error = NULL for [%s]\\n", __LINE__, API_NAMESPACE, TEST_TESTAPP_NAME);
		FREE_MEMORY(pszResPath);
		return 1;
	}

	nRet = package_archive_info_get_api_version(hArchiveInfo, &pszAPIVersion);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_get_api_version", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath); package_archive_info_destroy(hArchiveInfo));

	if ( pszAPIVersion == NULL )
	{
		FPRINTF("[Line : %d][%s] package_archive_info_get_api_version failed to get API version, error = NULL\\n", __LINE__, API_NAMESPACE);
		package_archive_info_destroy(hArchiveInfo);
		FREE_MEMORY(pszResPath);
		return 1;
	}

	if(strcmp(TargetAPIVersion, pszAPIVersion))
	{
		FPRINTF("[Line : %d][%s] package_archive_info_get_api_version returned, error for API version [%s] \\n", __LINE__, API_NAMESPACE, pszAPIVersion);
		package_archive_info_destroy(hArchiveInfo);
		FREE_MEMORY(pszResPath);
		FREE_MEMORY(pszAPIVersion);
		return 1;
	}

	nRet = package_archive_info_destroy(hArchiveInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_destroy", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath); FREE_MEMORY(pszAPIVersion));

	FREE_MEMORY(pszAPIVersion);
	FREE_MEMORY(pszResPath);
	return 0;
}

//& purpose: Test-case for package_archive_info_get_author
//& type: auto

/**
* @testcase 		ITc_package_archive_info_get_author_p
* @since_tizen 		4.0
* @author             	SRID(j.abhishek)
* @reviewer         	SRID(nibha.sharma)
* @type 		auto
* @description	 	Test package_archive_info_get_author
* @scenario		Call package_archive_info_get_author
* @apicovered		package_archive_info_get_author
* @precondition		archieve info must be created using package_archive_info_create API
* @postcondition	archieve info must be destroyed using package_archive_info_destroy API
* @passcase		When package_archive_info_get_author is successful
* @failcase		If API fails to complete the scenario cycle in pass case
*/
int ITc_package_archive_info_get_author_p(void)
{
	START_TEST;
	
	char fileName[] = TEST_TESTAPP_SAMPLE_NAME;
	char *pszResPath = NULL;
	char filePath[128];
	package_archive_info_h hArchiveInfo;
	
	char *pszAuthorName = NULL;
	const char *TargetAuthorName = TESTAPP_SAMPLE_AUTHOR_NAME;

	int nRet = PACKAGE_MANAGER_ERROR_NONE;

	pszResPath = app_get_shared_resource_path();
	if ( pszResPath == NULL )
	{
		FPRINTF("[Line : %d][%s] app_get_shared_resource_path failed, error = NULL resource path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	snprintf(filePath, sizeof(filePath), "%s/%s", pszResPath, fileName);

	nRet = package_archive_info_create(filePath, &hArchiveInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_create", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath));

	if ( hArchiveInfo == NULL )
	{
		FPRINTF("[Line : %d][%s] package_archive_info_create failed to create, error = NULL for [%s]\\n", __LINE__, API_NAMESPACE, TEST_TESTAPP_NAME);
		FREE_MEMORY(pszResPath);
		return 1;
	}

	nRet = package_archive_info_get_author(hArchiveInfo, &pszAuthorName);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_get_author", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath); package_archive_info_destroy(hArchiveInfo));

	if ( pszAuthorName == NULL )
	{
		FPRINTF("[Line : %d][%s] package_archive_info_get_author failed to get author, error = NULL\\n", __LINE__, API_NAMESPACE);
		package_archive_info_destroy(hArchiveInfo);
		FREE_MEMORY(pszResPath);
		return 1;
	}

	if(strcmp(TargetAuthorName, pszAuthorName))
	{
		FPRINTF("[Line : %d][%s] package_archive_info_get_author returned, error [%s] API version \\n", __LINE__, API_NAMESPACE, pszAuthorName);
		package_archive_info_destroy(hArchiveInfo);
		FREE_MEMORY(pszResPath);
		FREE_MEMORY(pszAuthorName);
		return 1;
	}


	nRet = package_archive_info_destroy(hArchiveInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_destroy", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath); FREE_MEMORY(pszAuthorName));

	FREE_MEMORY(pszResPath);
	FREE_MEMORY(pszAuthorName);
	return 0;
}

//& purpose: Test-case for package_archive_info_get_description
//& type: auto

/**
* @testcase 		ITc_package_archive_info_get_description_p
* @since_tizen 		4.0
* @author             	SRID(j.abhishek)
* @reviewer         	SRID(nibha.sharma)
* @type 		auto
* @description	 	Test package_archive_info_get_description
* @scenario		Call package_archive_info_get_description
* @apicovered		package_archive_info_get_description
* @precondition		archieve info must be created using package_archive_info_create API
* @postcondition	archieve info must be destroyed using package_archive_info_destroy API
* @passcase		When package_archive_info_get_description is successful
* @failcase		If API fails to complete the scenario cycle in pass case
*/
int ITc_package_archive_info_get_description_p(void)
{
	START_TEST;
	
	char fileName[] = TEST_TESTAPP_SAMPLE_NAME;
	char *pszResPath = NULL;
	char filePath[128];
	package_archive_info_h hArchiveInfo;
	
	char *pszDescription = NULL;
	const char *TargetDescription = TESTAPP_SAMPLE_API_DESCRIPTION;

	int nRet = PACKAGE_MANAGER_ERROR_NONE;

	pszResPath = app_get_shared_resource_path();
	if ( pszResPath == NULL )
	{
		FPRINTF("[Line : %d][%s] app_get_shared_resource_path failed, error = NULL resource path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	snprintf(filePath, sizeof(filePath), "%s/%s", pszResPath, fileName);

	nRet = package_archive_info_create(filePath, &hArchiveInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_create", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath));

	if ( hArchiveInfo == NULL )
	{
		FPRINTF("[Line : %d][%s] package_archive_info_create failed to create, error = NULL for [%s]\\n", __LINE__, API_NAMESPACE, TEST_TESTAPP_NAME);
		FREE_MEMORY(pszResPath);
		return 1;
	}

	nRet = package_archive_info_get_description(hArchiveInfo, &pszDescription);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_get_description", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath); package_archive_info_destroy(hArchiveInfo));

	if ( pszDescription == NULL )
	{
		FPRINTF("[Line : %d][%s] package_archive_info_get_description failed to get description, error = NULL\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszResPath);
		package_archive_info_destroy(hArchiveInfo);
		return 1;
	}

	if(strcmp(TargetDescription, pszDescription))
	{
		FPRINTF("[Line : %d][%s] package_archive_info_get_description returned, error [%s] API version \\n", __LINE__, API_NAMESPACE, pszDescription);
		FREE_MEMORY(pszResPath);
		FREE_MEMORY(pszDescription);
		package_archive_info_destroy(hArchiveInfo);
		return 1;
	}

	nRet = package_archive_info_destroy(hArchiveInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_destroy", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath); FREE_MEMORY(pszDescription));
	
	FREE_MEMORY(pszResPath);
	FREE_MEMORY(pszDescription);
	return 0;
}

//& purpose: Test-case for package_archive_info_get_icon
//& type: auto

/**
* @testcase 		ITc_package_archive_info_get_icon_p
* @since_tizen 		4.0
* @author             	SRID(j.abhishek)
* @reviewer         	SRID(nibha.sharma)
* @type 		auto
* @description	 	Test package_archive_info_get_icon
* @scenario		Call package_archive_info_get_icon
* @apicovered		package_archive_info_get_icon
* @precondition		archieve info must be created using package_archive_info_create API
* @postcondition	archieve info must be destroyed using package_archive_info_destroy API
* @passcase		When package_archive_info_get_icon is successful
* @failcase		If API fails to complete the scenario cycle in pass case
*/
int ITc_package_archive_info_get_icon_p(void)
{
	START_TEST;
	
	char fileName[] = TEST_TESTAPP_NAME;
	char *pszResPath = NULL;
	char filePath[128];
	package_archive_info_h hArchiveInfo;
	
	unsigned char *pszIcon = NULL;
	size_t icon_size = 0;

	int nRet = PACKAGE_MANAGER_ERROR_NONE;

	pszResPath = app_get_shared_resource_path();
	if ( pszResPath == NULL )
	{
		FPRINTF("[Line : %d][%s] app_get_shared_resource_path failed, error = NULL resource path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	snprintf(filePath, sizeof(filePath), "%s/%s", pszResPath, fileName);

	nRet = package_archive_info_create(filePath, &hArchiveInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_create", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath));

	if ( hArchiveInfo == NULL )
	{
		FPRINTF("[Line : %d][%s] package_archive_info_create failed to create, error = NULL for [%s]\\n", __LINE__, API_NAMESPACE, TEST_TESTAPP_NAME);
		FREE_MEMORY(pszResPath);
		return 1;
	}

	nRet = package_archive_info_get_icon(hArchiveInfo, &pszIcon, &icon_size);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_get_icon", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath); package_archive_info_destroy(hArchiveInfo));

	if(pszIcon == NULL)
	{
		FPRINTF("[Line : %d][%s] package_archive_info_get_icon returned, error Icon = [%s] \\n", __LINE__, API_NAMESPACE, pszIcon);
		package_archive_info_destroy(hArchiveInfo);
		FREE_MEMORY(pszResPath);
		return 1;
	}

	if(!icon_size)
	{
		FPRINTF("[Line : %d][%s] package_archive_info_get_icon returned, error Icon Size = [%d] \\n", __LINE__, API_NAMESPACE, icon_size);
		package_archive_info_destroy(hArchiveInfo);
		FREE_MEMORY(pszResPath);
		return 1;
	}

	nRet = package_archive_info_destroy(hArchiveInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_destroy", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath); FREE_MEMORY(pszIcon));

	FREE_MEMORY(pszResPath);
	FREE_MEMORY(pszIcon);
	return 0;
}


//& purpose: Test-case for package_archive_info_get_label
//& type: auto

/**
* @testcase 		ITc_package_archive_info_get_label_p
* @since_tizen 		4.0
* @author             	SRID(j.abhishek)
* @reviewer         	SRID(nibha.sharma)
* @type 		auto
* @description	 	Test package_archive_info_get_label
* @scenario		Call package_archive_info_get_label
* @apicovered		package_archive_info_get_label
* @precondition		archieve info must be created using package_archive_info_create API
* @postcondition	archieve info must be destroyed using package_archive_info_destroy API
* @passcase		When package_archive_info_get_label is successful
* @failcase		If API fails to complete the scenario cycle in pass case
*/
int ITc_package_archive_info_get_label_p(void)
{
	START_TEST;
	
	char fileName[] = TEST_TESTAPP_NAME;
	char *pszResPath = NULL;
	char filePath[128];
	package_archive_info_h hArchiveInfo;
	
	char *pszLabelName = NULL;
	const char *TargetLabelName = TESTAPP_LABEL_NAME;

	int nRet = PACKAGE_MANAGER_ERROR_NONE;

	pszResPath = app_get_shared_resource_path();
	if ( pszResPath == NULL )
	{
		FPRINTF("[Line : %d][%s] app_get_shared_resource_path failed, error = NULL resource path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	snprintf(filePath, sizeof(filePath), "%s/%s", pszResPath, fileName);

	nRet = package_archive_info_create(filePath, &hArchiveInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_create", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath));

	if ( hArchiveInfo == NULL )
	{
		FPRINTF("[Line : %d][%s] package_archive_info_create failed to create, error = NULL for [%s]\\n", __LINE__, API_NAMESPACE, TEST_TESTAPP_NAME);
		FREE_MEMORY(pszResPath);
		return 1;
	}

	nRet = package_archive_info_get_label(hArchiveInfo, &pszLabelName);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_get_label", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath); package_archive_info_destroy(hArchiveInfo));

	if ( pszLabelName == NULL )
	{
		FPRINTF("[Line : %d][%s] package_archive_info_get_label failed to get label, error = NULL\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszResPath);
		package_archive_info_destroy(hArchiveInfo);
		return 1;
	}

	if(strcmp(TargetLabelName, pszLabelName))
	{
		FPRINTF("[Line : %d][%s] package_archive_info_get_label returned, error [%s] API version \\n", __LINE__, API_NAMESPACE, pszLabelName);
		FREE_MEMORY(pszResPath);
		FREE_MEMORY(pszLabelName);
		package_archive_info_destroy(hArchiveInfo);
		return 1;
	}

	nRet = package_archive_info_destroy(hArchiveInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_destroy", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath); FREE_MEMORY(pszLabelName));
	
	FREE_MEMORY(pszResPath);
	FREE_MEMORY(pszLabelName);
	return 0;
}


//& purpose: Test-case for package_archive_info_get_package
//& type: auto

/**
* @testcase 		ITc_package_archive_info_get_package_p
* @since_tizen 		4.0
* @author             	SRID(j.abhishek)
* @reviewer         	SRID(nibha.sharma)
* @type 		auto
* @description	 	Test package_archive_info_get_package
* @scenario		Call package_archive_info_get_package
* @apicovered		package_archive_info_get_package
* @precondition		archieve info must be created using package_archive_info_create API
* @postcondition	archieve info must be destroyed using package_archive_info_destroy API
* @passcase		When package_archive_info_get_package is successful
* @failcase		If API fails to complete the scenario cycle in pass case
*/
int ITc_package_archive_info_get_package_p(void)
{
	START_TEST;
	
	char fileName[] = TEST_TESTAPP_NAME;
	char *pszResPath = NULL;
	char filePath[128];
	package_archive_info_h hArchiveInfo;
	
	char *pszPackageID = NULL;
	const char *TargetPackageID = TESTAPP_PACKAGE_ID;

	int nRet = PACKAGE_MANAGER_ERROR_NONE;

	pszResPath = app_get_shared_resource_path();
	if ( pszResPath == NULL )
	{
		FPRINTF("[Line : %d][%s] app_get_shared_resource_path failed, error = NULL resource path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	snprintf(filePath, sizeof(filePath), "%s/%s", pszResPath, fileName);

	nRet = package_archive_info_create(filePath, &hArchiveInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_create", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath));

	if ( hArchiveInfo == NULL )
	{
		FPRINTF("[Line : %d][%s] package_archive_info_create failed to create, error = NULL for [%s]\\n", __LINE__, API_NAMESPACE, TEST_TESTAPP_NAME);
		FREE_MEMORY(pszResPath);
		return 1;
	}

	nRet = package_archive_info_get_package(hArchiveInfo, &pszPackageID);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_get_package", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath); package_archive_info_destroy(hArchiveInfo));

	if ( pszPackageID == NULL )
	{
		FPRINTF("[Line : %d][%s] package_archive_info_get_package failed to get Package id version, error = NULL\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszResPath);
		package_archive_info_destroy(hArchiveInfo);
		return 1;
	}

	if(strcmp(TargetPackageID, pszPackageID))
	{
		FPRINTF("[Line : %d][%s] package_archive_info_get_package returned, error for Package ID [%s] \\n", __LINE__, API_NAMESPACE, pszPackageID);
		FREE_MEMORY(pszPackageID);
		FREE_MEMORY(pszResPath);
		package_archive_info_destroy(hArchiveInfo);
		return 1;
	}

	nRet = package_archive_info_destroy(hArchiveInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_destroy", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath); FREE_MEMORY(pszPackageID));
	
	FREE_MEMORY(pszResPath);
	FREE_MEMORY(pszPackageID);
	return 0;
}


//& purpose: Test-case for package_archive_info_get_type
//& type: auto

/**
* @testcase 		ITc_package_archive_info_get_type_p
* @since_tizen 		4.0
* @author             	SRID(j.abhishek)
* @reviewer         	SRID(nibha.sharma)
* @type 		auto
* @description	 	Test package_archive_info_get_type
* @scenario		Call package_archive_info_get_type
* @apicovered		package_archive_info_get_type
* @precondition		archieve info must be created using package_archive_info_create API
* @postcondition	archieve info must be destroyed using package_archive_info_destroy API
* @passcase		When package_archive_info_get_type is successful
* @failcase		If API fails to complete the scenario cycle in pass case
*/
int ITc_package_archive_info_get_type_p(void)
{
	START_TEST;
	
	char fileName[] = TEST_TESTAPP_NAME;
	char *pszResPath = NULL;
	char filePath[128];
	package_archive_info_h hArchiveInfo;
	
	char *pszType = NULL;
	const char *TargetType = TESTAPP_TYPE;

	int nRet = PACKAGE_MANAGER_ERROR_NONE;

	pszResPath = app_get_shared_resource_path();
	if ( pszResPath == NULL )
	{
		FPRINTF("[Line : %d][%s] app_get_shared_resource_path failed, error = NULL resource path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	snprintf(filePath, sizeof(filePath), "%s/%s", pszResPath, fileName);

	nRet = package_archive_info_create(filePath, &hArchiveInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_create", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath));

	if ( hArchiveInfo == NULL )
	{
		FPRINTF("[Line : %d][%s] package_archive_info_create failed to create, error = NULL for [%s]\\n", __LINE__, API_NAMESPACE, TEST_TESTAPP_NAME);
		FREE_MEMORY(pszResPath);
		return 1;
	}

	nRet = package_archive_info_get_type(hArchiveInfo, &pszType);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_get_type", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath); package_archive_info_destroy(hArchiveInfo));

	if ( pszType == NULL )
	{
		FPRINTF("[Line : %d][%s] package_archive_info_get_type failed to get Package Type version, error = NULL\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszResPath);
		package_archive_info_destroy(hArchiveInfo);
		return 1;
	}

	if(strcmp(TargetType, pszType))
	{
		FPRINTF("[Line : %d][%s] package_archive_info_get_type returned, error [%s] API version \\n", __LINE__, API_NAMESPACE, pszType);
		FREE_MEMORY(pszResPath);
		FREE_MEMORY(pszType);
		package_archive_info_destroy(hArchiveInfo);
		return 1;
	}

	nRet = package_archive_info_destroy(hArchiveInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_destroy", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath); FREE_MEMORY(pszType));
	
	FREE_MEMORY(pszResPath);
	FREE_MEMORY(pszType);
	return 0;
}


//& purpose: Test-case for package_archive_info_get_version
//& type: auto

/**
* @testcase 		ITc_package_archive_info_get_version_p
* @since_tizen 		4.0
* @author             	SRID(j.abhishek)
* @reviewer         	SRID(nibha.sharma)
* @type 		auto
* @description	 	Test package_archive_info_get_version
* @scenario		Call package_archive_info_get_version
* @apicovered		package_archive_info_get_version
* @precondition		archieve info must be created using package_archive_info_create API
* @postcondition	archieve info must be destroyed using package_archive_info_destroy API
* @passcase		When package_archive_info_get_version is successful
* @failcase		If API fails to complete the scenario cycle in pass case
*/
int ITc_package_archive_info_get_version_p(void)
{
	START_TEST;
	
	char fileName[] = TEST_TESTAPP_NAME;
	char *pszResPath = NULL;
	char filePath[128];
	package_archive_info_h hArchiveInfo;
	
	char *pszVersion = NULL;
	const char *TargetVersion = TESTAPP_VERSION;

	int nRet = PACKAGE_MANAGER_ERROR_NONE;

	pszResPath = app_get_shared_resource_path();
	if ( pszResPath == NULL )
	{
		FPRINTF("[Line : %d][%s] app_get_shared_resource_path failed, error = NULL resource path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	snprintf(filePath, sizeof(filePath), "%s/%s", pszResPath, fileName);

	nRet = package_archive_info_create(filePath, &hArchiveInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_create", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath));

	if ( hArchiveInfo == NULL )
	{
		FPRINTF("[Line : %d][%s] package_archive_info_create failed to create, error = NULL for [%s]\\n", __LINE__, API_NAMESPACE, TEST_TESTAPP_NAME);
		FREE_MEMORY(pszResPath);
		return 1;
	}

	nRet = package_archive_info_get_version(hArchiveInfo, &pszVersion);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_get_version", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath); package_archive_info_destroy(hArchiveInfo));

	if ( pszVersion == NULL )
	{
		FPRINTF("[Line : %d][%s] package_archive_info_get_version failed to get APP version, error = NULL\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszResPath);
		package_archive_info_destroy(hArchiveInfo);
		return 1;
	}

	if(strcmp(TargetVersion, pszVersion))
	{
		FPRINTF("[Line : %d][%s] package_archive_info_get_version returned, error [%s] API version \\n", __LINE__, API_NAMESPACE, pszVersion);
		FREE_MEMORY(pszResPath);
		FREE_MEMORY(pszVersion);
		package_archive_info_destroy(hArchiveInfo);
		return 1;
	}

	nRet = package_archive_info_destroy(hArchiveInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_destroy", PackageManagerGetError(nRet), FREE_MEMORY(pszResPath); FREE_MEMORY(pszVersion));
	
	FREE_MEMORY(pszResPath);
	FREE_MEMORY(pszVersion);
	return 0;
}

//& purpose: Test-case for package_manager_get_total_package_size_info
//& type: auto

/**
* @testcase                     ITc_package_manager_get_total_package_size_info_p
* @since_tizen                  5.5
* @author               SRID(manoj.g2)
* @reviewer             SRID(shobhit.v)
* @type                                 auto
* @description                  Test package_manager_get_total_package_size_info
* @scenario                             Call package_manager_get_total_package_size_info
* @apicovered                   package_manager_get_total_package_size_info
* @precondition                 none
* @postcondition                NA
* @passcase                             When package_manager_get_total_package_size_info is successful
* @failcase                             If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_get_total_package_size_info_p(void)
{
        START_TEST;

        int nTimeoutId = 0;

        g_bCallbackHit  = false;
        int nRet = package_manager_get_total_package_size_info(PackageManagerTotalSizeInfoCB, NULL);
        PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_total_package_size_info", PackageManagerGetError(nRet));
        RUN_POLLING_LOOP;
        if ( g_bCallbackHit == false )
        {
                FPRINTF("[Line : %d][%s] package_manager_get_total_package_size_info failed, error = callback not invoked\\n", __LINE__, API_NAMESPACE);
                return 1;
        }
	CHECK_HANDLE(g_hSizeInfo, "package_manager_get_total_package_size_info")

        return 0;
}

//& purpose: Retrieves required privilege information of the allowed package
//& type: auto

/**
* @testcase	 			ITc_package_info_foreach_required_privilege_p
* @since_tizen 			6.5
* @author             	SRID(nibha.sharma)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Retrieves required privilege information of the allowed package
* @scenario				Retrieves required privilege information of the allowed package
* @apicovered			package_info_foreach_required_privilege
* @precondition			NA
* @postcondition		NA
* @passcase				If it returns 0
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_foreach_required_privilege_p(void)
{
	START_TEST;
	int nRet;
	const char *pszPkgId = "org.tizen.hellorpk";
	package_info_h hPackageInfo = NULL;
	g_packageManagerAllowed = false;
	g_isAllowedPackageCBHit = false;

	nRet = package_manager_get_package_info(pszPkgId, &hPackageInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPackageInfo, "package_manager_get_package_info");

	nRet = package_info_foreach_res_allowed_package(hPackageInfo, PackageManagerAllowedPackageCB, NULL);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_foreach_res_allowed_package", PackageManagerGetError(nRet),package_info_destroy(hPackageInfo));
	if(g_isAllowedPackageCBHit == false)
	{
		FPRINTF("[Line : %d][%s] PackageManagerAllowedPackageCB callback not hit, failed!!!\\n", __LINE__, API_NAMESPACE);
		package_info_destroy(hPackageInfo);
		return 1;
	}
	if(g_packageManagerAllowed == false)
	{
		FPRINTF("[Line : %d][%s] package_info_foreach_required_privilege api failed!!!\\n", __LINE__, API_NAMESPACE);
		package_info_destroy(hPackageInfo);
		return 1;
	}

	nRet = package_info_destroy(hPackageInfo);
	PRINT_RESULT_NORETURN(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));

	return 0;
}

//& purpose: Retrieves allowed package information of the resource package
//& type: auto

/**
* @testcase	 			ITc_package_manager_package_info_foreach_res_allowed_package_p
* @since_tizen 			6.5
* @author             	SRID(nibha.sharma)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Retrieves allowed package information of the resource package
* @scenario				Retrieves allowed package information of the resource package
* @apicovered			package_info_foreach_res_allowed_package
* @precondition			NA
* @postcondition		NA
* @passcase				If it returns 0
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_package_info_foreach_res_allowed_package_p(void)
{
	START_TEST;
	int nRet;
	const char *pszPkgId = "org.tizen.hellorpk";
	package_info_h hPackageInfo = NULL;
	g_isAllowedPackageCBHit = false;

	nRet = package_manager_get_package_info(pszPkgId, &hPackageInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPackageInfo, "package_manager_get_package_info");

	nRet = package_info_foreach_res_allowed_package(hPackageInfo, PackageManagerAllowedPackageCB, NULL);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_foreach_res_allowed_package", PackageManagerGetError(nRet),package_info_destroy(hPackageInfo));
	if(g_isAllowedPackageCBHit == false)
	{
		FPRINTF("[Line : %d][%s] PackageManagerAllowedPackageCB callback not hit, failed!!!\\n", __LINE__, API_NAMESPACE);
		package_info_destroy(hPackageInfo);
		return 1;
	}

	nRet = package_info_destroy(hPackageInfo);
	PRINT_RESULT_NORETURN(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));


	return 0;
}

//& purpose:  Gets the resource type of the package
//& type: auto

/**
* @testcase	 			ITc_package_manager_package_info_get_res_type_p
* @since_tizen 			6.5
* @author             	SRID(nibha.sharma)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Gets the resource type of the package
* @scenario				Gets the resource type of the package
* @apicovered			package_info_get_res_type
* @precondition			NA
* @postcondition		NA
* @passcase				If it returns 0
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_package_info_get_res_type_p(void)
{
	START_TEST;
	int nRet;
	const char *pszPkgId = "org.tizen.hellorpk";
	package_info_h hPackageInfo = NULL;
	char *hInfo = NULL;

	nRet = package_manager_get_package_info(pszPkgId, &hPackageInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPackageInfo, "package_manager_get_package_info");


	nRet = package_info_get_res_type(hPackageInfo, &hInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_get_res_type", PackageManagerGetError(nRet),package_info_destroy(hPackageInfo));
	CHECK_HANDLE_CLEANUP(hInfo, "package_info_get_res_type",package_info_destroy(hPackageInfo));

	FREE_MEMORY(hInfo);
	nRet = package_info_destroy(hPackageInfo);
	PRINT_RESULT_NORETURN(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));

	return 0;
}

//& purpose: Gets the resource version of the package
//& type: auto

/**
* @testcase	 			ITc_package_manager_package_info_get_res_version_p
* @since_tizen 			6.5
* @author             	SRID(nibha.sharma)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Gets the resource version of the package
* @scenario				Gets the resource version of the package
* @apicovered			package_info_get_res_version
* @precondition			NA
* @postcondition		NA
* @passcase				If it returns 0
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_package_info_get_res_version_p(void)
{
	START_TEST;
	int nRet;
	const char *pszPkgId = "org.tizen.hellorpk";
	package_info_h hPackageInfo = NULL;
	char *hInfo = NULL;

	nRet = package_manager_get_package_info(pszPkgId, &hPackageInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPackageInfo, "package_manager_get_package_info");

	nRet = package_info_get_res_version(hPackageInfo, &hInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_get_res_version", PackageManagerGetError(nRet),package_info_destroy(hPackageInfo));
	CHECK_HANDLE_CLEANUP(hInfo, "package_info_get_res_version",package_info_destroy(hPackageInfo));

	FREE_MEMORY(hInfo);
	nRet = package_info_destroy(hPackageInfo);
	PRINT_RESULT_NORETURN(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));

	return 0;
}

//& purpose: Gets the resource version of the package
//& type: auto

/**
* @testcase	 			ITc_package_manager_package_manager_filter_add_string_p
* @since_tizen 			6.5
* @author             	SRID(nibha.sharma)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Gets the resource version of the package
* @scenario				Gets the resource version of the package
* @apicovered			package_manager_filter_add_string
* @precondition			NA
* @postcondition		NA
* @passcase				If it returns 0
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_package_manager_filter_add_string_p(void)
{
	START_TEST;
	int nRet = PACKAGE_MANAGER_ERROR_NONE;
	package_manager_filter_h hFilter = NULL;

	nRet = package_manager_filter_create(&hFilter);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_filter_create", PackageManagerGetError(nRet));
	CHECK_HANDLE(hFilter, "package_manager_filter_create");

	nRet = package_manager_filter_add_string(hFilter, PACKAGE_MANAGER_PKGINFO_PROP_RES_TYPE, "ai_model");
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_filter_add_string", PackageManagerGetError(nRet),package_manager_filter_destroy(hFilter));

	nRet = package_manager_filter_destroy(hFilter);
	PRINT_RESULT_NORETURN(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_filter_destroy", PackageManagerGetError(nRet));

	return 0;
}
/** @} */
/** @} */
