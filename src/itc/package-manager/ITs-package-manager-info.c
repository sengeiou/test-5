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

/** @addtogroup itc-package-manager-info
*  @ingroup itc
*  @{
*/

//Callbacks

/**
* @function 		PackageManagerPackageInfoCertInfoCB
* @description	 	Callback function which is invoked when package_info_foreach_cert_info is called
* @parameter		package_info_h handle, package_cert_type_e cert_type, const char *cert_value, void *user_data
* @return 			bool
*/
static bool PackageManagerPackageInfoCertInfoCB(package_info_h handle, package_cert_type_e cert_type, const char *cert_value, void *user_data)
{
	g_bCallbackReturnValue = false;
#if DEBUG
	FPRINTF("[Line : %d][%s] PackageManagerPackageInfoCertInfoCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	if ( handle == NULL || cert_value == NULL )
	{
		FPRINTF("[Line : %d][%s] PackageManagerPackageInfoCertInfoCB callback returned null package info and cert value\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = false;
	}
	else
	{
		g_bCallbackReturnValue = true;
	}
	switch ( cert_type )
	{
	case PACKAGE_INFO_AUTHOR_ROOT_CERT:
		FPRINTF("[Line : %d][%s] Cert Type: PACKAGE_INFO_AUTHOR_ROOT_CERT\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	case PACKAGE_INFO_AUTHOR_INTERMEDIATE_CERT:
		FPRINTF("[Line : %d][%s] Cert Type: PACKAGE_INFO_AUTHOR_INTERMEDIATE_CERT\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	case PACKAGE_INFO_AUTHOR_SIGNER_CERT:
		FPRINTF("[Line : %d][%s] Cert Type: PACKAGE_INFO_AUTHOR_SIGNER_CERT\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	case PACKAGE_INFO_DISTRIBUTOR_ROOT_CERT:
		FPRINTF("[Line : %d][%s] Cert Type: PACKAGE_INFO_DISTRIBUTOR_ROOT_CERT\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	case PACKAGE_INFO_DISTRIBUTOR_INTERMEDIATE_CERT:
		FPRINTF("[Line : %d][%s] Cert Type: PACKAGE_INFO_DISTRIBUTOR_INTERMEDIATE_CERT\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	case PACKAGE_INFO_DISTRIBUTOR_SIGNER_CERT:
		FPRINTF("[Line : %d][%s] Cert Type: PACKAGE_INFO_DISTRIBUTOR_SIGNER_CERT\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	case PACKAGE_INFO_DISTRIBUTOR2_ROOT_CERT:
		FPRINTF("[Line : %d][%s] Cert Type: PACKAGE_INFO_DISTRIBUTOR2_ROOT_CERT\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	case PACKAGE_INFO_DISTRIBUTOR2_INTERMEDIATE_CERT:
		FPRINTF("[Line : %d][%s] Cert Type: PACKAGE_INFO_DISTRIBUTOR2_INTERMEDIATE_CERT\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	case PACKAGE_INFO_DISTRIBUTOR2_SIGNER_CERT:
		FPRINTF("[Line : %d][%s] Cert Type: PACKAGE_INFO_DISTRIBUTOR2_SIGNER_CERT\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	}
	if ( g_pPacakageManagerMainLoop )
	{
		g_main_loop_quit(g_pPacakageManagerMainLoop);
	}
	return false;
}


/**
* @function 		PackageManagerPackageInfoAppCB
* @description	 	Called to get the application id once for each installed package.
* @parameter		package_info_app_component_type_e comp_type, const char *app_id, void *user_data
* @return 			NA
*/
static bool PackageManagerPackageInfoAppCB(package_info_app_component_type_e comp_type, const char *app_id, void *user_data)
{
	g_bCallbackReturnValue = false;
#if DEBUG
	FPRINTF("[Line : %d][%s] PackageManagerPackageInfoAppCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	if ( app_id == NULL )
	{
		FPRINTF("[Line : %d][%s] PackageManagerPackageInfoAppCB callback returned null app id\\n", __LINE__, API_NAMESPACE);
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
* @function 		PackageManagerPackageInfoPrivilegeInfoCB
* @description	 	Callback function which retrieves privilege information of package
* @parameter		const char *privilege_name, void *user_data
* @return 			bool
*/
static bool PackageManagerPackageInfoPrivilegeInfoCB(const char *privilege_name, void *user_data)
{
	g_bCallbackReturnValue = false;
#if DEBUG
	FPRINTF("[Line : %d][%s] PackageManagerPackageInfoPrivilegeInfoCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	if ( privilege_name == NULL )
	{
		FPRINTF("[Line : %d][%s] PackageManagerPackageInfoPrivilegeInfoCB callback returned null privilege name\\n", __LINE__, API_NAMESPACE);
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
* @function 		PackageManagerPackageInfoUpdateInfoCB
* @description	 	Callback function which retrieves privilege information of package
* @parameter		package_updateinfo_type_e updateInfoType, package_updateinfo_h hUpdateInfo, void *user_data
* @return 		bool
*/
static bool PackageManagerPackageInfoUpdateInfoCB(package_updateinfo_h hPkgUpdateInfo, void *pUserData)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] PackageManagerPackageInfoUpdateInfoCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;

	if ( g_pPacakageManagerMainLoop )
	{
		g_main_loop_quit(g_pPacakageManagerMainLoop);
	}
	return false;
}


/**
* @function 		PackageInfoDependencyInfoCB
* @description	 	Callback function which retrieves dependency information of package
* @parameter		const char *pszFrom, const char *pszTo, const char *pszType, const char *pszRequiredVersion, void *pszUsrData
* @return 		bool
*/
static bool PackageInfoDependencyInfoCB(const char *pszFrom, const char *pszTo, const char *pszType, const char *pszRequiredVersion, void *pszUsrData)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] PackageInfoDependencyInfoCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;

	if ( g_pPacakageManagerMainLoop )
	{
		g_main_loop_quit(g_pPacakageManagerMainLoop);
	}
	return false;
}


/**
* @function 		ITs_package_manager_info_startup
* @description	 	Called before each test, created package manager handle
* @parameter		NA
* @return 			NA
*/ 
void ITs_package_manager_info_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Package_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif

	TCT_CheckInstalledApp(2, TEST_NATIVETESTAPP_APPID, TEST_TESTAPP_APPID);
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
* @function 		ITs_package_manager_info_cleanup
* @description	 	Called after each test, destroys package manager handle
* @parameter		NA
* @return 			NA
*/ 
void ITs_package_manager_info_cleanup(void)
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

/** @addtogroup itc-package-manager-info-testcases
*  @brief 		Integration testcases for module package-manager
*  @ingroup 	itc-package-manager
*  @{
*/



//& purpose: Retrieves all application id of each package. 
//& type: auto

/**
* @testcase	 			ITc_package_info_foreach_app_from_package_p
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves all package information of installed packages
* @scenario				Get package info from package id\n
*						Retrieves all application id of each package\n 
* 						Check if callback is thrown or not\n
* 						Check the package is invalid or not\n
* 						Destroys the package information handle and releases all its resources\n 
* 						Cleanup all resources
* @apicovered			package_info_foreach_app_from_package
* @precondition			NA
* @postcondition		NA
* @passcase				If all the pre conditions are met and packages should be traversed first
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_foreach_app_from_package_p(void)
{
	START_TEST;
	int nRet = -1, nTimeoutId = 0;
	char *pszPkgId = NULL;
	package_info_h hPkgInfo = NULL;

	nRet = package_manager_get_package_id_by_app_id(TEST_TESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Package ID is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	// we do not have any service app available so not checking for PACKAGE_INFO_SERVICEAPP
	package_info_app_component_type_e component_type[] = { PACKAGE_INFO_APP_COMPONENT_TYPE_ALL, PACKAGE_INFO_APP_COMPONENT_TYPE_UI};

	int nEnumSize = sizeof(component_type) / sizeof(component_type[0]);
	int nEnumCounter = 0;
	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		g_bCallbackHit = false;
		//target API
		nRet = package_info_foreach_app_from_package(hPkgInfo,component_type[nEnumCounter],PackageManagerPackageInfoAppCB, USER_DATA);
		PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_foreach_app_from_package", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));
		if ( g_bCallbackHit == false || g_bCallbackReturnValue == false )
		{
			FPRINTF("[Line : %d][%s] package_manager_foreach_package_info failed, error = callback not invoked for Enum %s\\n", __LINE__, API_NAMESPACE, PackageManagerGetEnumForComponent(component_type[nEnumCounter]));
			package_info_destroy(hPkgInfo);
			return 1;
		}
	}

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Clones the package information handle./ Checks whether two package information are equal. 
//& type: auto

/**
* @testcase 			ITc_package_info_clone_is_equal_p
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Clones and checks whether two package information are equal.
* @scenario				Get packaged id by application id\n
* 						Get a package info\n
* 						Clones the package information handle\n
* 						Checks whether two package information are equal\n
* 						Destroys the package information handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_info_clone, package_info_is_equal
* @precondition			none
* @postcondition		NA
* @passcase				When package_info_clone is successful and package_info_is_equal returns true
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_clone_is_equal_p(void)
{
	START_TEST;

	bool bIsEql = false;
	char *pszPkgId = NULL;
	package_info_h hPackInfoCloned = NULL;
	package_info_h hPkgInfo = NULL;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	//target API
	nRet = package_info_clone(&hPackInfoCloned, hPkgInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_clone", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));

	//target API
	nRet = package_info_is_equal(hPkgInfo, hPackInfoCloned, &bIsEql);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_is_equal", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));
	if ( bIsEql != true )
	{
		FPRINTF("[Line : %d][%s] package_info_is_equal failed for unequal package info\\n", __LINE__, API_NAMESPACE);
		return 1;
	}			

	nRet = package_info_destroy(hPackInfoCloned);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Retrieves certification information of the package
//& type: auto

/**
* @testcase 			ITc_package_info_foreach_cert_info_p
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Retrieves certification information of the package
* @scenario				Gets package id by app id\n
* 						Get a package info\n
* 						Retrieves certification information of the package\n
* 						Checks the callback is thrown\n
* 						Checks if a certification is found or not\n
* 						Destroys the package information handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_info_foreach_cert_info
* @precondition			none
* @postcondition		NA
* @passcase				package_info_foreach_cert_info is successful and callback is invoked
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_foreach_cert_info_p(void)
{
	START_TEST;

	int nTimeoutId = 0;
	char *pszPkgId = NULL;
	package_info_h hPkgInfo = NULL;

	int nRet = package_manager_get_package_id_by_app_id(TEST_TESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_TESTAPP_APPID);
		return 1;
	}

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	g_bCallbackHit = false;
	//target API
	nRet = package_info_foreach_cert_info(hPkgInfo, PackageManagerPackageInfoCertInfoCB, USER_DATA);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_foreach_cert_info", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));

	if ( g_bCallbackHit == false || g_bCallbackReturnValue == false )
	{
		FPRINTF("[Line : %d][%s] package_info_foreach_cert_info failed, error = callback not invoked\\n", __LINE__, API_NAMESPACE);
		package_info_destroy(hPkgInfo);
		return 1;
	}

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Gets the absolute path to the icon image
//& type: auto

/**
* @testcase 			ITc_package_info_get_icon_p
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets the absolute path to the icon image
* @scenario				Gets packaged id by app id\n
* 						Get a package info\n
* 						Gets the absolute path to the icon image\n
* 						Destroys the package information handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_info_get_icon
* @precondition			none
* @postcondition		NA
* @passcase				If all the pre conditions are met and package_info_get_icon is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_get_icon_p(void)
{
	START_TEST;

	char *pszPkgIcon = NULL;
	char *pszPkgId = NULL;
	package_info_h hPkgInfo = NULL;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	//target API
	nRet = package_info_get_icon(hPkgInfo, &pszPkgIcon);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_get_icon", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));
	FREE_MEMORY(pszPkgIcon);

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Gets the label of the package
//& type: auto

/**
* @testcase 			ITc_package_info_get_label_p
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 			Gets the label of the package
* @scenario				Gets packaged id by app id\n
* 						Get a package info\n
* 						Gets the label of the package\n
* 						Destroys the package information handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_info_get_label
* @precondition			none
* @postcondition		NA
* @passcase				If all the pre conditions are met and package_info_get_label is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_get_label_p(void)
{
	START_TEST;

	char *pszPkgLabel = NULL;
	char *pszPkgId = NULL;
	package_info_h hPkgInfo = NULL;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	//target API
	nRet = package_info_get_label(hPkgInfo, &pszPkgLabel);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_get_label", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));
	FREE_MEMORY(pszPkgLabel);

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Get the package name
//& type: auto

/**
* @testcase 			ITc_package_info_get_package_p
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Get the package name
* @scenario				Gets packaged id by app id\n
* 						Get a package info\n
* 						Get the package name\n
* 						Destroys the package information handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_info_get_package
* @precondition			none
* @postcondition		NA
* @passcase				If all the pre conditions are met and package_info_get_package is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_get_package_p(void)
{
	START_TEST;

	char *pszPkgName = NULL;
	char *pszPkgId = NULL;
	package_info_h hPkgInfo = NULL;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	//target API
	nRet = package_info_get_package(hPkgInfo, &pszPkgName);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_get_package", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));
	FREE_MEMORY(pszPkgName);

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Gets the installed storage for the given package
//& type: auto

/**
* @testcase 			ITc_package_info_get_installed_storage_p
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets the installed storage for the given package
* @scenario				Gets packaged id by app id\n
* 						Get a package info\n
* 						Gets the installed storage for the given package\n
* 						Destroys the package information handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_info_get_installed_storage
* @precondition			none
* @postcondition		NA
* @passcase				If all the pre conditions are met and package_info_get_installed_storage is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_get_installed_storage_p(void)
{
	START_TEST;

	package_info_installed_storage_type_e eStorType = -1;
	char *pszPkgId = NULL;
	package_info_h hPkgInfo = NULL;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	//target API
	nRet = package_info_get_installed_storage(hPkgInfo, &eStorType);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_get_installed_storage", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Gets the type of the package
//& type: auto

/**
* @testcase 			ITc_package_info_get_type_p
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets the type of the package
* @scenario				Gets packaged id by app id\n
* 						Get a package info\n
* 						Gets the type of the package\n
* 						Destroys the package information handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_info_get_type
* @precondition			none
* @postcondition		NA
* @passcase				If all the pre conditions are met and package_info_get_type is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_get_type_p(void)
{
	START_TEST;

	char *pszPkgType = NULL;
	char *pszPkgId = NULL;
	package_info_h hPkgInfo = NULL;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	//target API
	nRet = package_info_get_type(hPkgInfo, &pszPkgType);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_get_type", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));
	FREE_MEMORY(pszPkgType);

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Gets the version of the package
//& type: auto

/**
* @testcase 			ITc_package_info_get_version_p
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets the version of the package
* @scenario				Gets packaged id by app id\n
* 						Get a package info\n
* 						Gets the version of the package\n
* 						Destroys the package information handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_info_get_version
* @precondition			none
* @postcondition		NA
* @passcase				If all the pre conditions are met and package_info_get_version is successful
* @failcase				If API fails to complete the scenario cycle in pass case 
*/
int ITc_package_info_get_version_p(void)
{
	START_TEST;

	char *pszPkgVer = NULL;
	char *pszPkgId = NULL;
	package_info_h hPkgInfo = NULL;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	//target API
	nRet = package_info_get_version(hPkgInfo, &pszPkgVer);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_get_version", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));
	FREE_MEMORY(pszPkgVer);

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Gets the package accessible for the given package. 
//& type: auto

/**
* @testcase 			ITc_package_info_is_accessible_p
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets the package accessible for the given package. 
* @scenario				Gets packaged id by app id\n
* 						Get a package info\n
* 						Gets the package accessible for the given package\n
* 						Destroys the package information handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_info_is_accessible
* @precondition			none
* @postcondition		NA
* @passcase				If all the pre conditions are met and package_info_is_accessible is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_is_accessible_p(void)
{
	START_TEST;

	bool bIsAccessiblePkg = false;
	char *pszPkgId = NULL;
	package_info_h hPkgInfo = NULL;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	//target API
	nRet = package_info_is_accessible(hPkgInfo, &bIsAccessiblePkg);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_is_accessible", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Gets whether the package is preload or not
//& type: auto

/**
* @testcase 			ITc_package_info_is_preload_package_p
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets whether the package is preload or not
* @scenario				Gets packaged id by app id\n
* 						Retrieves all application id of each package\n
* 						Gets whether the package is preload or not\n
* 						Gets whether the package is preload or not by app_id\n
* 						Check if both values are same\n
* 						Destroys the package information handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_info_is_preload_package
* @precondition			none
* @postcondition		NA
* @passcase				If all the pre conditions are met and package_info_is_preload_package is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_is_preload_package_p(void)
{
	START_TEST;

	bool bIsPreloadPkg = false, bIsPreloadPkgByAppId = false;
	char *pszPkgId = NULL;
	package_info_h hPkgInfo = NULL;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	//target API
	nRet = package_info_is_preload_package (hPkgInfo, &bIsPreloadPkg);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_is_preload_package", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));

	nRet = package_manager_is_preload_package_by_app_id(TEST_NATIVETESTAPP_APPID, &bIsPreloadPkgByAppId);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_is_preload_package_by_app_id", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Gets whether the package is removable or not.
//& type: auto

/**
* @testcase 			ITc_package_info_is_removable_package_p
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets whether the package is removable or not.
* @scenario				Get a package info\n
* 						Gets whether the package is removable or not\n
* 						Destroys the package information handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_info_is_removable_package
* @precondition			none
* @postcondition		NA
* @passcase				If all the pre conditions are met and package_info_is_removable_package is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_is_removable_package_p(void)
{
	START_TEST;
	int nRet = -1;
	bool bIsRemPkg = false;
	char *pszPkgId = NULL;
	package_info_h hPkgInfo = NULL;

	nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	//target API
	nRet = package_info_is_removable_package(hPkgInfo, &bIsRemPkg);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_is_removable_package", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Gets whether the package is system package or not
//& type: auto

/**
* @testcase 			ITc_package_info_is_system_package_p
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets whether the package is system package or not
* @scenario				Get a package info\n
* 						Gets whether the package is system package or not\n
* 						Destroys the package information handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_info_is_system_package
* @precondition			none
* @postcondition		NA
* @passcase				If all the pre conditions are met and package_info_is_system_package is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_is_system_package_p(void)
{
	START_TEST;
	int nRet = -1;
	bool bIsSysPkg = false;
	char *pszPkgId = NULL;
	package_info_h hPkgInfo = NULL;

	nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");
	//target API
	nRet = package_info_is_system_package(hPkgInfo, &bIsSysPkg);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_is_system_package", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Gets the root path of the package.
//& type: auto

/**
* @testcase 			ITc_package_info_get_root_path_p
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets the root path of the package.
* @scenario				Get a package info\n
* 						Get he root path of the package\n
* 						Destroys the package information handle and releases all its resources\n
* 						Cleanup all resources
* @apicovered			package_info_get_root_path
* @precondition			none
* @postcondition		NA
* @passcase				If all the pre conditions are met and package_info_get_root_path is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_get_root_path_p(void)
{
	START_TEST;
	int nRet = -1;
	char *pszRootPath = NULL;
	char *pszPkgId = NULL;
	package_info_h hPkgInfo = NULL;

	nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	//target API
	nRet = package_info_get_root_path(hPkgInfo, &pszRootPath);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_is_system_package", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));
	FREE_MEMORY(pszRootPath);

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Creates package info
//& type: auto

/**
* @testcase	 			ITc_package_info_create_p
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates package info
* @scenario				Creates a request handle to the package manager\n
*						Get packaged id from app id\n
* 						Get package info\n
*						Create package info\n
*						destroy package info\n
* 						Destroys the request handle to the package manager\n
* 						Cleanup all resources
* @apicovered			package_info_create
* @precondition			Insert an external storage micro SD/ SD Card.
* @postcondition		NA
* @passcase				If package_info_create is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_create_p(void)
{
	START_TEST;
	int nRet = -1;
	char *pszPkgId = NULL;
	package_info_h 	hPkgInfo;

	nRet = package_manager_get_package_id_by_app_id(TEST_TESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_TESTAPP_APPID);
		return 1;
	}

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	//target API
	nRet = package_info_create(TEST_TESTAPP_APPID, &hPkgInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_create", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));
	return 0;
}


//& purpose: Retrieves privilege information of the package
//& type: auto

/**
* @since_tizen 2.3
* @testcase 			ITc_package_info_foreach_privilege_info_p
* @author             	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 			Retrieves privilege information of the package
* @scenario				Gets package id by app id
* 						Get a package info.
* 						Retrieves privilege information of the package
* 						Checks the callback is thrown.
* 						Checks if a certification is found or not.
* 						Destroys the package information handle and releases all its resources. 
* 						Cleanup all resources
* @apicovered			package_info_foreach_privilege_info()
* @precondition			none
* @postcondition		NA
* @passcase				package_info_foreach_privilege_info is successful and callback is invoked
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_foreach_privilege_info_p(void)
{
	START_TEST;
	int nRet = -1, nTimeoutId = 0;
	char *pszPkgId = NULL;
	package_info_h hPkgInfo = NULL;
	nRet = package_manager_get_package_id_by_app_id(TEST_TESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_TESTAPP_APPID);
		return 1;
	}

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	g_bCallbackHit = false;
	//target API
	nRet = package_info_foreach_privilege_info(hPkgInfo, PackageManagerPackageInfoPrivilegeInfoCB, USER_DATA);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_foreach_privilege_info", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));
	if(g_bCallbackHit == false || g_bCallbackReturnValue == false )
	{

		FPRINTF("[Line : %d][%s] package_info_foreach_privilege_info failed, error = callback not invoked\\n", __LINE__, API_NAMESPACE);
		package_info_destroy(hPkgInfo);
		return 1;
	}

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));
	return 0;
}

//& purpose: Gets the main application ID of the package.
//& type: auto
/**
* @since_tizen 4.0
* @testcase				ITc_package_info_get_main_app_id_p
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Gets the main application ID of the package.
* @scenario				Gets package id by app id
* 						Get a package info.
* 						Gets the main application ID of the package.
* 						Destroys the package information handle and releases all its resources. 
* 						Cleanup all resources
* @apicovered			package_info_get_main_app_id()
* @precondition			none
* @postcondition		NA
* @passcase				package_info_get_main_app_id is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_get_main_app_id_p(void)
{
	START_TEST;
	int nRet = -1;
	char *pszPkgId = NULL;
	package_info_h hPkgInfo = NULL;
	char *pszPkgInfo = NULL;
	nRet = package_manager_get_package_id_by_app_id(TEST_TESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_TESTAPP_APPID);
		return 1;
	}

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	//target API
	nRet = package_info_get_main_app_id(hPkgInfo, &pszPkgInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_get_main_app_id", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo));
	if ( pszPkgInfo == NULL )
	{
		FPRINTF("[Line : %d][%s] package_info_get_main_app_id failed, error = Null Package Info\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));

	free(pszPkgInfo);

	return 0;
}

//& purpose: Gets the installed time for the given package.
//& type: auto
/**
* @testcase 			ITc_package_info_get_installed_time_p
* @author             	SRID(nibha.sharma)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description	 		Gets the installed time for the given package.
* @scenario				Gets the installed time for the given package.
* @apicovered			package_info_get_installed_time
* @precondition			none
* @postcondition		NA
* @passcase				If all the pre conditions are met and package_info_get_installed_time is successful
* @failcase				If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_get_installed_time_p(void)
{
	START_TEST;

	int nGetTime = 0;
	char *pszPkgId = NULL;
	package_info_h hPkgInfo = NULL;

	int nRet = package_manager_get_package_id_by_app_id(TEST_NATIVETESTAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	if ( pszPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_manager_get_package_id_by_app_id failed, error = Null Package ID for %s\\n", __LINE__, API_NAMESPACE, TEST_NATIVETESTAPP_APPID);
		return 1;
	}

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet),FREE_MEMORY(pszPkgId));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	//target API
	nRet = package_info_get_installed_time(hPkgInfo, &nGetTime);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_get_installed_time", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo);FREE_MEMORY(pszPkgId));
	if(nGetTime <= 0)
	{
		FPRINTF("[Line : %d][%s] package_info_get_installed_time returned invalid time %d\\n", __LINE__, API_NAMESPACE, nGetTime);
		package_info_destroy(hPkgInfo);
		FREE_MEMORY(pszPkgId);
		return 1;
	}

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet),FREE_MEMORY(pszPkgId));

	FREE_MEMORY(pszPkgId);
	return 0;
}

//& purpose: Creates/Destroys the package update information request
//& type: auto
/**
* @testcase 		ITc_package_info_updateinfo_create_destroy_p
* @since_tizen 		4.0
* @author             	SRID(j.abhishek)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @description		Creates/Destroys the package update information request
* @scenario		Create package update information request handle\n
* 			Destroy the package update information request handle\n
* 			Cleanup all resources
* @apicovered		package_info_updateinfo_create, package_info_updateinfo_destroy
* @precondition		NA
* @postcondition	NA
* @passcase		If all the pre conditions are met and package update information request handler created
* @failcase		If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_updateinfo_create_destroy_p(void)
{
	START_TEST;

	int nRet = PACKAGE_MANAGER_ERROR_NONE;
	package_updateinfo_h hPkgUpdateInfo = NULL;

	// Target API
	nRet = package_info_updateinfo_create(TESTAPP_PACKAGE_ID, &hPkgUpdateInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_updateinfo_create", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgUpdateInfo, "package_info_updateinfo_create");

	// Target API
	nRet = package_info_updateinfo_destroy(hPkgUpdateInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_updateinfo_destroy", PackageManagerGetError(nRet));

	return 0;
}


//& purpose: Get the package ID for the package update information request
//& type: auto
/**
* @testcase 		ITc_package_info_updateinfo_get_pkgid_p
* @since_tizen 		4.0
* @author             	SRID(j.abhishek)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @description		Get the package ID for the package update information request
* @scenario		Create package update information request handle\n
*			Get the package ID for package update information request\n
* 			Destroy the package update information request handle\n
* 			Cleanup all resources
* @apicovered		package_info_updateinfo_get_pkgid
* @precondition		package_info_updateinfo_create
* @postcondition	package_info_updateinfo_destroy
* @passcase		If all the pre conditions are met and package update information request package id can be obtained
* @failcase		If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_updateinfo_get_pkgid_p(void)
{
	START_TEST;

	int nRet = PACKAGE_MANAGER_ERROR_NONE;
	char *pszUpdateInfoPkgId = NULL;
	package_updateinfo_h hPkgUpdateInfo = NULL;

	nRet = package_info_updateinfo_create(TESTAPP_PACKAGE_ID, &hPkgUpdateInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_updateinfo_create", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgUpdateInfo, "package_info_updateinfo_create");

	// Target API
	nRet = package_info_updateinfo_get_pkgid(hPkgUpdateInfo, &pszUpdateInfoPkgId);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_updateinfo_get_pkgid", PackageManagerGetError(nRet), package_info_updateinfo_destroy(hPkgUpdateInfo));

	if ( pszUpdateInfoPkgId == NULL )
	{
		FPRINTF("[Line : %d][%s] package_info_updateinfo_get_pkgid failed, error = NULL Package ID for %s\\n", __LINE__, API_NAMESPACE, TESTAPP_PACKAGE_ID);
		package_info_updateinfo_destroy(hPkgUpdateInfo);
		return 1;
	}

	if(strcmp(TESTAPP_PACKAGE_ID, pszUpdateInfoPkgId))
	{
		FPRINTF("[Line : %d][%s] package_info_updateinfo_get_pkgid returned wrong ID, error = %s  Package Update Info package ID for %s\\n", __LINE__, API_NAMESPACE, pszUpdateInfoPkgId, TESTAPP_PACKAGE_ID);
		package_info_updateinfo_destroy(hPkgUpdateInfo);
		FREE_MEMORY(pszUpdateInfoPkgId);
		return 1;
	}

	nRet = package_info_updateinfo_destroy(hPkgUpdateInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_updateinfo_destroy", PackageManagerGetError(nRet), FREE_MEMORY(pszUpdateInfoPkgId));
	FREE_MEMORY(pszUpdateInfoPkgId);

	return 0;
}

//& purpose: Get the package version for the package update information request
//& type: auto
/**
* @testcase 		ITc_package_info_updateinfo_get_version_p
* @since_tizen 		4.0
* @author             	SRID(j.abhishek)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @description		Get the package version for the package update information request
* @scenario		Create package update information request handle\n
*			Get the package version for package update information request\n
* 			Destroy the package update information request handle\n
* 			Cleanup all resources
* @apicovered		package_info_updateinfo_get_version
* @precondition		package_info_updateinfo_create
* @postcondition	package_info_updateinfo_destroy
* @passcase		If all the pre conditions are met and package update information request package version can be obtained and matches with the version set.
* @failcase		If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_updateinfo_get_version_p(void)
{
	START_TEST;

	int nRet = PACKAGE_MANAGER_ERROR_NONE;
	char *pszUpdateInfoVersion = NULL;
	package_updateinfo_h hPkgUpdateInfo = NULL;

	nRet = package_info_updateinfo_create(TESTAPP_PACKAGE_ID, &hPkgUpdateInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_updateinfo_create", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgUpdateInfo, "package_info_updateinfo_create");

	// Target API
	nRet = package_info_updateinfo_get_version(hPkgUpdateInfo, &pszUpdateInfoVersion);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_updateinfo_get_version", PackageManagerGetError(nRet), package_info_updateinfo_destroy(hPkgUpdateInfo));

	if ( pszUpdateInfoVersion == NULL )
	{
		FPRINTF("[Line : %d][%s] package_info_updateinfo_get_version failed, error = NULL Package Version for %s\\n", __LINE__, API_NAMESPACE, TESTAPP_PACKAGE_ID);
		package_info_updateinfo_destroy(hPkgUpdateInfo);
		return 1;
	}

	if(strcmp(TESTAPP_VERSION, pszUpdateInfoVersion))
	{
		FPRINTF("[Line : %d][%s] package_info_updateinfo_get_version returned wrong ID, error = %s  Package Update Info package ID for %s\\n", __LINE__, API_NAMESPACE, pszUpdateInfoVersion, TESTAPP_PACKAGE_ID);
		package_info_updateinfo_destroy(hPkgUpdateInfo);
		FREE_MEMORY(pszUpdateInfoVersion);
		return 1;
	}

	nRet = package_info_updateinfo_destroy(hPkgUpdateInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_updateinfo_destroy", PackageManagerGetError(nRet), FREE_MEMORY(pszUpdateInfoVersion));
	FREE_MEMORY(pszUpdateInfoVersion);
	return 0;
}

//& purpose: Get the package type for the package update information request
//& type: auto
/**
* @testcase 		ITc_package_info_updateinfo_get_type_p
* @since_tizen 		4.0
* @author             	SRID(j.abhishek)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @description		Get the package type for the package update information request
* @scenario		Create package update information request handle\n
*			Get the package type for package update information request\n
* 			Destroy the package update information request handle\n
* 			Cleanup all resources
* @apicovered		package_info_updateinfo_get_type
* @precondition		package_info_updateinfo_create
* @postcondition	package_info_updateinfo_destroy
* @passcase		If all the pre conditions are met and package update information request package type can be obtained
* @failcase		If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_updateinfo_get_type_p(void)
{
	START_TEST;

	int nRet = PACKAGE_MANAGER_ERROR_NONE;
	package_updateinfo_type_e pszUpdateInfoType;
	package_updateinfo_h hPkgUpdateInfo = NULL;

	nRet = package_info_updateinfo_create(TESTAPP_PACKAGE_ID, &hPkgUpdateInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_updateinfo_create", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgUpdateInfo, "package_info_updateinfo_create");

	// Target API
	nRet = package_info_updateinfo_get_type(hPkgUpdateInfo, &pszUpdateInfoType);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_updateinfo_get_type", PackageManagerGetError(nRet), package_info_updateinfo_destroy(hPkgUpdateInfo));

	nRet = package_info_updateinfo_destroy(hPkgUpdateInfo);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_updateinfo_destroy", PackageManagerGetError(nRet));

	return 0;
}

//& purpose: Get the package ID for the package update information request
//& type: auto
/**
* @testcase 		ITc_package_info_updateinfo_foreach_info_p
* @since_tizen 		4.0
* @author             	SRID(j.abhishek)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @description		Get the package ID for the package update information request
* @scenario		Create package update information request handle\n
*			Get the package ID for package update information request\n
* 			Destroy the package update information request handle\n
* 			Cleanup all resources
* @apicovered		package_info_updateinfo_foreach_info
* @precondition		package_info_updateinfo_create
* @postcondition	package_info_updateinfo_destroy
* @passcase		If all the pre conditions are met and package update information request package id can be obtained
* @failcase		If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_updateinfo_foreach_info_p(void)
{
	START_TEST;
	int nRet = PACKAGE_MANAGER_ERROR_NONE;

	package_updateinfo_h hPkgUpdateInfo = NULL;
	g_bCallbackHit = false;

	//target API
	nRet = package_info_updateinfo_foreach_info(PackageManagerPackageInfoUpdateInfoCB, USER_DATA);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_updateinfo_foreach_info", PackageManagerGetError(nRet));

	if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] package_info_updateinfo_foreach_info failed, error = callback not invoked \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}


//& purpose: Creates/Destroys the package manager update information request
//& type: auto
/**
* @testcase 		ITc_package_manager_updateinfo_request_create_destroy_p
* @since_tizen 		4.0
* @author             	SRID(j.abhishek)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @description		Creates/Destroys the package manager update information request
* @scenario		Create package update information request handle\n
* 			Destroy the package update information request handle\n
* 			Cleanup all resources
* @apicovered		package_manager_updateinfo_request_create, package_manager_updateinfo_request_destroy
* @precondition		NA
* @postcondition	NA
* @passcase		If all the pre conditions are met and package update information request handle is obtained
* @failcase		If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_updateinfo_request_create_destroy_p(void)
{
	START_TEST;

	int nRet = PACKAGE_MANAGER_ERROR_NONE;
	package_updateinfo_request_h hPkgUpdateInfoRequest = NULL;

	// Target API
	nRet = package_manager_updateinfo_request_create(&hPkgUpdateInfoRequest);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_updateinfo_request_create", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgUpdateInfoRequest, "package_manager_updateinfo_request_create");

	// Target API
	nRet = package_manager_updateinfo_request_destroy(hPkgUpdateInfoRequest);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_updateinfo_request_destroy", PackageManagerGetError(nRet));

	return 0;
}


//& purpose: Set the package ID for the package manager update information request
//& type: auto
/**
* @testcase 		ITc_package_manager_updateinfo_set_pkgid_p
* @since_tizen 		4.0
* @author             	SRID(j.abhishek)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @description		Set the package ID for the package manager update information request
* @scenario		Create package manager update information request handle\n
*			Set the package ID for package manager update information request\n
* 			Destroy the package manager update information request handle\n
* 			Cleanup all resources
* @apicovered		package_manager_updateinfo_set_pkgid
* @precondition		package_manager_updateinfo_request_create
* @postcondition	package_manager_updateinfo_request_destroy
* @passcase		If all the pre conditions are met and package manager update information request package id can be set
* @failcase		If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_updateinfo_set_pkgid_p(void)
{
	START_TEST;

	int nRet = PACKAGE_MANAGER_ERROR_NONE;
	package_updateinfo_request_h hPkgUpdateInfoRequest = NULL;
	const char *pszUpdateInfoSetPkgId = TESTAPP_PACKAGE_ID;

	nRet = package_manager_updateinfo_request_create(&hPkgUpdateInfoRequest);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_updateinfo_request_create", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgUpdateInfoRequest, "package_manager_updateinfo_request_create");

	// Target API
	nRet = package_manager_updateinfo_set_pkgid(hPkgUpdateInfoRequest, pszUpdateInfoSetPkgId);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_updateinfo_set_pkgid", PackageManagerGetError(nRet), package_manager_updateinfo_request_destroy(hPkgUpdateInfoRequest));

	nRet = package_manager_updateinfo_request_destroy(hPkgUpdateInfoRequest);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_updateinfo_request_destroy", PackageManagerGetError(nRet));

	return 0;
}


//& purpose: Set the package version for the package manager update information request
//& type: auto
/**
* @testcase 		ITc_package_manager_updateinfo_set_version_p
* @since_tizen 		4.0
* @author             	SRID(j.abhishek)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @description		Set the package version for the package manager update information request
* @scenario		Create package manager update information request handle\n
*			Set the package version for package manager update information request\n
* 			Destroy the package manager update information request handle\n
* 			Cleanup all resources
* @apicovered		package_manager_updateinfo_set_version
* @precondition		package_manager_updateinfo_request_create
* @postcondition	package_manager_updateinfo_request_destroy
* @passcase		If all the pre conditions are met and package manager update information request package version can be set
* @failcase		If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_updateinfo_set_version_p(void)
{
	START_TEST;

	int nRet = PACKAGE_MANAGER_ERROR_NONE;
	package_updateinfo_request_h hPkgUpdateInfoRequest = NULL;
	const char *pszUpdateInfoSetPkgId = TESTAPP_PACKAGE_ID;
	const char *pszUpdateInfoSetPkgVersion = "1.1.0";

	nRet = package_manager_updateinfo_request_create(&hPkgUpdateInfoRequest);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_updateinfo_request_create", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgUpdateInfoRequest, "package_manager_updateinfo_request_create");

	// Need to set the package ID first..
	nRet = package_manager_updateinfo_set_pkgid(hPkgUpdateInfoRequest, pszUpdateInfoSetPkgId);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_updateinfo_set_pkgid", PackageManagerGetError(nRet), package_manager_updateinfo_request_destroy(hPkgUpdateInfoRequest));

	// Target API
	nRet = package_manager_updateinfo_set_version(hPkgUpdateInfoRequest, pszUpdateInfoSetPkgVersion);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_updateinfo_set_version", PackageManagerGetError(nRet), package_manager_updateinfo_request_destroy(hPkgUpdateInfoRequest));

	nRet = package_manager_updateinfo_request_destroy(hPkgUpdateInfoRequest);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_updateinfo_destroy", PackageManagerGetError(nRet));

	return 0;
}


//& purpose: Set the package type for the package manager update information request
//& type: auto
/**
* @testcase 		ITc_package_manager_updateinfo_set_type_p
* @since_tizen 		4.0
* @author             	SRID(j.abhishek)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @description		Set the package type for the package manager update information request
* @scenario		Create package manager update information request handle\n
*			Set the package type for package manager update information request\n
* 			Destroy the package manager update information request handle\n
* 			Cleanup all resources
* @apicovered		package_manager_updateinfo_set_type
* @precondition		package_manager_updateinfo_request_create
* @postcondition	package_manager_updateinfo_request_destroy
* @passcase		If all the pre conditions are met and package manager update information request package type can be set
* @failcase		If API fails to complete the scenario cycle in pass case
*/
int ITc_package_manager_updateinfo_set_type_p(void)
{
	START_TEST;

	int nRet = PACKAGE_MANAGER_ERROR_NONE;
	package_updateinfo_request_h hPkgUpdateInfoRequest = NULL;

	package_updateinfo_type_e nPackageUpdateInfoType[] =
	{
		PACKAGE_UPDATEINFO_TYPE_NONE,   /**< None type */
		PACKAGE_UPDATEINFO_TYPE_FORCE,      /**< Force type */
		PACKAGE_UPDATEINFO_TYPE_OPTIONAL    /**< Optional type */
	};


	int nEnumSize = sizeof(nPackageUpdateInfoType) / sizeof(nPackageUpdateInfoType[0]);
	int nEnumCounter = 0;

	nRet = package_manager_updateinfo_request_create(&hPkgUpdateInfoRequest);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_updateinfo_request_create", PackageManagerGetError(nRet));
	CHECK_HANDLE(hPkgUpdateInfoRequest, "package_manager_updateinfo_request_create");

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		// Target API
		nRet = package_manager_updateinfo_set_type(hPkgUpdateInfoRequest, nPackageUpdateInfoType[nEnumCounter]);
		PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_updateinfo_set_type", PackageManagerGetError(nRet), package_manager_updateinfo_request_destroy(hPkgUpdateInfoRequest));
	}

	nRet = package_manager_updateinfo_request_destroy(hPkgUpdateInfoRequest);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_updateinfo_destroy", PackageManagerGetError(nRet));

	return 0;
}

//& purpose: Retrieves dependency information of the package.
//& type: auto
/**
* @testcase			ITc_package_info_foreach_dependency_info_p
* @author			SRID(j.abhishek)
* @reviewer			SRID(manoj.g2)
* @type			auto
* @description			Retrieves dependency information of the package.
* @scenario			Retrieves dependency information of the package.
* @apicovered			package_info_foreach_dependency_info
* @precondition			get package info handler from package_manager_get_package_info.
* @postcondition			NA
* @passcase			If all the pre conditions are met and package_info_foreach_dependency_info is successful
* @failcase			If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_foreach_dependency_info_p(void)
{
	START_TEST;

	int nTimeoutId = 0;
	char *pszPkgId = NULL;
	package_info_h hPkgInfo = NULL;

	int nRet = package_manager_get_package_id_by_app_id(TEST_HELLO_WORLDAPP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	CHECK_HANDLE(pszPkgId, "package_manager_get_package_id_by_app_id");

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet),FREE_MEMORY(pszPkgId));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	g_bCallbackHit = false;
	//target API
	nRet = package_info_foreach_dependency_info(hPkgInfo, PackageInfoDependencyInfoCB, USER_DATA);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_foreach_dependency_info", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo);FREE_MEMORY(pszPkgId));

	PRINT_RESULT_CLEANUP(true, g_bCallbackHit, "package_info_foreach_dependency_info", "callback not invoked", package_info_destroy(hPkgInfo); FREE_MEMORY(pszPkgId));
	FREE_MEMORY(pszPkgId);

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT_NORETURN(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));

	return 0;
}

//& purpose: Retrieves information about which packages depend on a given package.
//& type: auto
/**
* @testcase			ITc_package_info_foreach_dependency_info_depends_on_p
* @author			SRID(j.abhishek)
* @reviewer			SRID(manoj.g2)
* @type			auto
* @description			Retrieves information about which packages depend on a given package.
* @scenario			Retrieves information about which packages depend on a given package.
* @apicovered			package_info_foreach_dependency_info_depends_on
* @precondition			get package info handler from package_manager_get_package_info.
* @postcondition			NA
* @passcase			If all the pre conditions are met and package_info_foreach_dependency_info_depends_on is successful
* @failcase			If API fails to complete the scenario cycle in pass case
*/
int ITc_package_info_foreach_dependency_info_depends_on_p(void)
{
	START_TEST;

	int nTimeoutId = 0;
	char *pszPkgId = NULL;
	package_info_h hPkgInfo = NULL;

	int nRet = package_manager_get_package_id_by_app_id(TEST_HELLO_WORLD2APP_APPID, &pszPkgId);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_id_by_app_id", PackageManagerGetError(nRet));
	CHECK_HANDLE(pszPkgId, "package_manager_get_package_id_by_app_id");

	nRet = package_manager_get_package_info(pszPkgId, &hPkgInfo);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_manager_get_package_info", PackageManagerGetError(nRet),FREE_MEMORY(pszPkgId));
	CHECK_HANDLE(hPkgInfo, "package_manager_get_package_info");

	g_bCallbackHit = false;
	//target API
	nRet = package_info_foreach_dependency_info_depends_on(hPkgInfo, PackageInfoDependencyInfoCB, USER_DATA);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_foreach_dependency_info_depends_on", PackageManagerGetError(nRet), package_info_destroy(hPkgInfo); FREE_MEMORY(pszPkgId));

	PRINT_RESULT_CLEANUP(true, g_bCallbackHit, "package_info_foreach_dependency_info_depends_on", "callback not invoked", package_info_destroy(hPkgInfo); FREE_MEMORY(pszPkgId));
	FREE_MEMORY(pszPkgId);

	nRet = package_info_destroy(hPkgInfo);
	PRINT_RESULT_NORETURN(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_info_destroy", PackageManagerGetError(nRet));

	return 0;
}

//& purpose: Retrieves direct dependencoes of a given package.
//& type: auto
/**
* @testcase			ITc_package_archive_info_foreach_direct_dependency_p
* @since_tizen 			5.5
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Retrieves direct dependencoes of a given package.
* @scenario			Retrieves direct dependencoes of a given package.
* @apicovered			package_archive_info_foreach_direct_dependency
* @precondition			get package info handler from ppackage_archive_info_foreach_direct_dependency.
* @postcondition			NA
* @passcase			If all the pre conditions are met and package_archive_info_foreach_direct_dependency is successful
* @failcase			If API fails to complete the scenario cycle in pass case
*/
int ITc_package_archive_info_foreach_direct_dependency_p(void)
{
	START_TEST;

	int nRet = -1;
	int nTimeoutId = 0;
	const char tpkName[] = "org.example.sampletpk.tpk";
	char *pszResPath = NULL;
	char pszPath[128] ={};
	package_archive_info_h hArchiveInfoHandle = NULL;

	pszResPath = app_get_shared_resource_path();
	CHECK_HANDLE(pszResPath, "app_get_shared_resource_path");

	snprintf(pszPath, sizeof(pszPath), "%s/%s", pszResPath, tpkName);
	FREE_MEMORY(pszResPath);

	nRet = package_archive_info_create(pszPath, &hArchiveInfoHandle);
	PRINT_RESULT(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_create", PackageManagerGetError(nRet));
	CHECK_HANDLE(hArchiveInfoHandle, "apackage_archive_info_create");

	nRet = package_archive_info_foreach_direct_dependency(hArchiveInfoHandle, PackageInfoDependencyInfoCB, NULL);
	PRINT_RESULT_CLEANUP(PACKAGE_MANAGER_ERROR_NONE, nRet, " package_archive_info_foreach_direct_dependency", PackageManagerGetError(nRet),package_archive_info_destroy(hArchiveInfoHandle));

	PRINT_RESULT_CLEANUP(true, g_bCallbackHit, "package_archive_info_foreach_direct_dependency", "callback not invoked", package_archive_info_destroy(hArchiveInfoHandle));

	nRet = package_archive_info_destroy(hArchiveInfoHandle);
	PRINT_RESULT_NORETURN(PACKAGE_MANAGER_ERROR_NONE, nRet, "package_archive_info_destroy", PackageManagerGetError(nRet));

	return 0;
}
/** @} */
/** @} */
