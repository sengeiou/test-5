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
#include "ITs-app-manager-common.h"

/** @addtogroup itc-app-manager
*  @ingroup itc
*  @{
*/

/**
* @function 		ITs_app_manager_info_startup
* @description	 	Called before each test, opens pre-defined app
* @parameter		NA
* @return 			NA
*/
void ITs_app_manager_info_startup(void)
{
	pstAppContext = NULL;
	g_bAppManagerOpen = false;

	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_App_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif

	//TCT_CheckInstalledApp(2, TEST_TESTAPPLICATION_APPID, TEST_APPMANAGERTESTFILE_APPID);
	TCT_CheckInstalledApp(3, TEST_TESTAPPLICATION_APPID, TEST_APPMANAGERTESTFILE_APPID, TEST_COMPONENTBASED_APPID);
	sleep(2);
	int nRet = APP_MANAGER_ERROR_NONE;

	nRet = app_control_create(&g_app_control_handler);
	if ( nRet != APP_CONTROL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_control_create fail in startup error returned : %s\\n", __LINE__, API_NAMESPACE , AppControlGetError(nRet));
		return;
	}

	if ( g_app_control_handler == NULL )
	{
		FPRINTF("[Line : %d][%s] app_control_create fail in startup created handle value null\\n", __LINE__, API_NAMESPACE);
		app_control_destroy(g_app_control_handler);
		return;
	}


	nRet = app_control_set_app_id(g_app_control_handler , TEST_TESTAPPLICATION_APPID);
	if ( nRet != APP_CONTROL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_control_set_app_id fail in startup error returned : %s\\n", __LINE__, API_NAMESPACE , AppControlGetError(nRet));
		app_control_destroy(g_app_control_handler);
		return ;
	}

	nRet = app_control_send_launch_request(g_app_control_handler , NULL , NULL);
	if ( nRet != APP_CONTROL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_control_send_launch_request fail in startup error returned : %s\\n", __LINE__, API_NAMESPACE , AppControlGetError(nRet));
		app_control_destroy(g_app_control_handler);
		return ;
	}

	nRet = app_manager_get_app_context((const char *)TEST_TESTAPPLICATION_APPID , &pstAppContext);
	if ( nRet != APP_MANAGER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_manager_get_app_context failed in startup, error returned = %s\\n", __LINE__, API_NAMESPACE, AppManagerGetError(nRet));
		app_control_send_terminate_request(g_app_control_handler);
		app_control_destroy(g_app_control_handler);
		return ;
	}

	// set precondition value
	g_bAppManagerOpen = true;
}

/**
* @function 		ITs_app_manager_info_cleanup
* @description	 	Called after each test, terminates the app opened in startup
* @parameter		NA
* @return 			NA
*/
void ITs_app_manager_info_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_App_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet = -1;
	if ( g_bAppManagerOpen )
	{
		nRet = app_context_destroy(pstAppContext);
		if ( nRet != APP_MANAGER_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] app_context_destroy() is failed in cleanup. returned error = %s\\n", __LINE__, API_NAMESPACE , AppManagerGetError(nRet));
		}

		nRet = app_control_send_terminate_request(g_app_control_handler);
		if ( nRet != APP_CONTROL_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] app_control_send_terminate_request() is failed cleanup. err = %s\\n", __LINE__, API_NAMESPACE , AppControlGetError(nRet));
		}

		nRet = app_control_destroy(g_app_control_handler);
		if ( nRet != APP_CONTROL_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] app_control_destroy() is failed cleanup. err = %s\\n", __LINE__, API_NAMESPACE , AppControlGetError(nRet));
		}
	}
}


/** @addtogroup itc-app-manager-testcases
*  @brief 		Integration testcases for module app-manager
*  @ingroup 	itc-app-manager
*  @{
*/
//& type: auto
//& purpose: Scenario to get event for applications with metadata
/**
* @testcase 			ITc_app_manager_app_info_metadata_filter_foreach_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			Scenario to get event for applications with metadata
* @scenario				Creates the application's metadata information filter handle from db\n
* 						Adds filter condition for the query API\n
* 						Register callback for each application with metadata\n
* 						Check if callback is invoked\n
* 						Destroys the application's metadata information filter handle
* @apicovered			app_info_metadata_filter_foreach, app_info_metadata_filter_create, app_info_metadata_filter_add, app_info_metadata_filter_destroy
* @passcase				If callback is invoked after app_info_metadata_filter_foreach is called
* @failcase				If callback is not invoked after app_info_metadata_filter_foreach is called or any other supporting function fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_info_metadata_filter_foreach_p(void)
{
	START_TEST;

	int nDelay = 0;
	app_info_metadata_filter_h pstFilterHandle = NULL;
	g_bAppManagerCallback = false;

	int nRet = app_info_metadata_filter_create(&pstFilterHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_metadata_filter_create", AppManagerGetError(nRet));
	CHECK_HANDLE(pstFilterHandle, "app_info_metadata_filter_create");

	nRet = app_info_metadata_filter_add(pstFilterHandle, MKEY, MVALUE);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_metadata_filter_add", AppManagerGetError(nRet), app_info_metadata_filter_destroy(pstFilterHandle));

	// Target API
	nRet = app_info_metadata_filter_foreach(pstFilterHandle, AppInfoMetaDataFilterForeachCallback, NULL);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_metadata_filter_foreach", AppManagerGetError(nRet), app_info_metadata_filter_destroy(pstFilterHandle));

	do
	{
		nDelay = nDelay + 2;
		if ( nDelay >= TIME_DELAY )
		{
			break;
		}
		usleep(USLEEPDELAY);
	} while(!g_bAppManagerCallback);

	if ( !g_bAppManagerCallback )
	{
		FPRINTF("[Line : %d][%s] app_info_metadata_filter_foreach error returned = callback function not invoked\\n", __LINE__, API_NAMESPACE);
		app_info_metadata_filter_destroy(pstFilterHandle);
		return 1;
	}

	nRet = app_info_metadata_filter_destroy(pstFilterHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_metadata_filter_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Scenario to get event for each applications with metadata
/**
* @testcase 			ITc_app_manager_app_info_foreach_metadata_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			Scenario to get event for each applications with metadata
* @scenario				Get application's metadata information handle\n
* 						Register callback application with metadata\n
* 						Check if callback is invoked\n
* 						Destroys the application's metadata information filter handle
* @apicovered			app_info_create, app_manager_get_app_info, app_info_foreach_metadata, app_info_destroy
* @passcase				If callback is invoked after app_info_metadata_filter_foreach is called
* @failcase				If callback is not invoked after app_info_metadata_filter_foreach is called or any other supporting function fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_info_foreach_metadata_p(void)
{
	START_TEST;

	int nDelay = 0;
	app_info_h pstAppInfoHandle = NULL;
	g_bAppManagerCallback = false;

	int nRet = app_info_create(TEST_TESTAPPLICATION_APPID, &pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_create", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppInfoHandle, "app_info_create");

	nRet = app_manager_get_app_info(TEST_TESTAPPLICATION_APPID, &pstAppInfoHandle);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_info", AppManagerGetError(nRet), app_info_destroy(pstAppInfoHandle));

	// Target API
	nRet = app_info_foreach_metadata(pstAppInfoHandle, AppInfoMetaDataCallback, NULL);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_foreach_metadata", AppManagerGetError(nRet), app_info_destroy(pstAppInfoHandle));

	do
	{
		nDelay = nDelay + 2;
		if ( nDelay >= TIME_DELAY )
		{
			break;
		}
		usleep(USLEEPDELAY);
	} while(!g_bAppManagerCallback);

	if ( !g_bAppManagerCallback )
	{
		FPRINTF("[Line : %d][%s] app_info_foreach_metadata error returned = callback function not invoked\\n", __LINE__, API_NAMESPACE);
		app_info_destroy(pstAppInfoHandle);
		return 1;
	}

	nRet = app_info_destroy(pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Scenario to get event for each applications with metadata
/**
* @testcase 			ITc_app_manager_app_info_filter_foreach_appinfo_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			Scenario to get event for each applications with metadata
* @scenario				Create filter handle from db\n
* 						Add boolean filter property to filter handle\n
* 						Add string filter property to the filter handle\n
* 						Register callback\n
* 						Check if callback is invoked\n
* 						Destroys filter handle
* @apicovered			app_info_filter_create, app_info_filter_destroy, app_info_filter_add_bool, app_info_filter_add_string, app_info_filter_foreach_appinfo
* @passcase				If callback is invoked after app_info_filter_foreach_appinfo is called
* @failcase				If callback is not invoked after app_info_filter_foreach_appinfo is called or any other supporting function fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_info_filter_foreach_appinfo_p(void)
{
	START_TEST;

	int nDelay = 0;
	app_info_filter_h pstAppInfoFilterHandle = NULL;
	g_bAppManagerCallback = false;

	int nRet = app_info_filter_create(&pstAppInfoFilterHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_filter_create", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppInfoFilterHandle, "app_info_filter_create");

	nRet = app_info_filter_add_string(pstAppInfoFilterHandle, PACKAGE_INFO_PROP_APP_TYPE, "capp");
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_filter_add_string", AppManagerGetError(nRet), app_info_filter_destroy(pstAppInfoFilterHandle));

	nRet = app_info_filter_add_bool(pstAppInfoFilterHandle, PACKAGE_INFO_PROP_APP_NODISPLAY, false);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_filter_add_bool", AppManagerGetError(nRet), app_info_filter_destroy(pstAppInfoFilterHandle));

	nRet = app_info_filter_add_bool(pstAppInfoFilterHandle, PACKAGE_INFO_PROP_APP_TASKMANAGE, false);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_filter_add_bool", AppManagerGetError(nRet), app_info_filter_destroy(pstAppInfoFilterHandle));

	nRet = app_info_filter_add_bool(pstAppInfoFilterHandle, PACKAGE_INFO_PROP_APP_DISABLED, false);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_filter_add_bool", AppManagerGetError(nRet), app_info_filter_destroy(pstAppInfoFilterHandle));

	// Target API
	nRet = app_info_filter_foreach_appinfo(pstAppInfoFilterHandle, AppInfoMetaDataFilterForeachCallback, NULL);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_filter_foreach_appinfo", AppManagerGetError(nRet), app_info_filter_destroy(pstAppInfoFilterHandle));

	do
	{
		nDelay = nDelay + 2;
		if ( nDelay >= TIME_DELAY )
		{
			break;
		}
		usleep(USLEEPDELAY);
	} while(!g_bAppManagerCallback);

	if ( !g_bAppManagerCallback )
	{
		FPRINTF("[Line : %d][%s] app_info_filter_foreach_appinfo error returned = callback function not invoked\\n", __LINE__, API_NAMESPACE);
		app_info_filter_destroy(pstAppInfoFilterHandle);
		return 1;
	}

	nRet = app_info_filter_destroy(pstAppInfoFilterHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_filter_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: To clone the application information handle
/**
* @testcase 			ITc_app_manager_app_info_create_clone_destroy_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To clone the application information handle
* @scenario				Create an application info\n
* 						Get the created application info\n
* 						clone the application info\n
* 						Terminate the cloned application info\n
* 						Terminate the open application info
* @apicovered			app_info_create, app_manager_get_app_info, app_info_clone, app_info_destroy
* @passcase				If app_info_create, app_manager_get_app_info, app_info_clone and app_info_destroy returns success and handle returned is not NULL
* @failcase				If app_info_create or app_manager_get_app_info or app_info_clone or app_info_destroy returns false or handle returned is NULL
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_info_create_clone_destroy_p(void)
{
	START_TEST;

	app_info_h pstAppInfoToCloneHandle = NULL, pstAppInfoFromCloneHandle = NULL;

	//Target API
	int nRet = app_info_create((const char *)TEST_TESTAPPLICATION_APPID, &pstAppInfoFromCloneHandle);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));
	CHECK_HANDLE(pstAppInfoFromCloneHandle, "app_control_create");

	nRet = app_manager_get_app_info((const char *)TEST_TESTAPPLICATION_APPID, &pstAppInfoFromCloneHandle);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_info", AppManagerGetError(nRet), app_info_destroy(pstAppInfoFromCloneHandle));

	//Target API
	nRet = app_info_clone(&pstAppInfoToCloneHandle, pstAppInfoFromCloneHandle);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_clone", AppManagerGetError(nRet), app_info_destroy(pstAppInfoFromCloneHandle));
	if (pstAppInfoToCloneHandle == NULL)
	{
		FPRINTF("[Line : %d][%s] app_info_clone error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE);
		app_info_destroy(pstAppInfoFromCloneHandle);
		return 1;
	}

	nRet = app_info_destroy(pstAppInfoToCloneHandle);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_destroy", AppManagerGetError(nRet), app_info_destroy(pstAppInfoFromCloneHandle));

	nRet = app_info_destroy(pstAppInfoFromCloneHandle);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_info_destroy", AppControlGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Scenario to add filter and check them
/**
* @testcase 			ITc_app_manager_app_info_filter_add_string_bool_count_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To add filter and check them
* @scenario				Create filter handle from db\n
* 						Add boolean filter property to filter handle\n
* 						Add string filter property to the filter handle\n
* 						counts the number of filtered apps\n
* 						Destroys filter handle
* @apicovered			app_info_filter_create, app_info_filter_add_bool, app_info_filter_add_string, app_info_filter_destroy, app_info_filter_count_appinfo
* @passcase				If app_info_filter_add_bool, app_info_filter_add_string and app_info_filter_count_appinfo returns success and Handle returned is not NULL also all supporting API are passed
* @failcase				If app_info_filter_add_bool or app_info_filter_add_string or app_info_filter_count_appinfo returns fail or any supporting API is failed or Handle returned is NULL
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_info_filter_add_string_bool_count_p(void)
{
	START_TEST;

	int nCount = 0;
	app_info_filter_h pstAppInfoFilterHandle = NULL;

	int nRet = app_info_filter_create(&pstAppInfoFilterHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_filter_create", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppInfoFilterHandle, "app_info_filter_create");

	//Target API
	nRet = app_info_filter_add_string(pstAppInfoFilterHandle, PACKAGE_INFO_PROP_APP_TYPE, "capp");
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_filter_add_string", AppManagerGetError(nRet), app_info_filter_destroy(pstAppInfoFilterHandle));

	//Target API
	nRet = app_info_filter_add_bool(pstAppInfoFilterHandle, PACKAGE_INFO_PROP_APP_NODISPLAY, false);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_filter_add_bool", AppManagerGetError(nRet), app_info_filter_destroy(pstAppInfoFilterHandle));

	//Target API
	nRet = app_info_filter_add_bool(pstAppInfoFilterHandle, PACKAGE_INFO_PROP_APP_TASKMANAGE, false);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_filter_add_bool", AppManagerGetError(nRet), app_info_filter_destroy(pstAppInfoFilterHandle));

	//Target API
	nRet = app_info_filter_add_bool(pstAppInfoFilterHandle, PACKAGE_INFO_PROP_APP_DISABLED, false);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_filter_add_bool", AppManagerGetError(nRet), app_info_filter_destroy(pstAppInfoFilterHandle));

	// Target API
	nRet = app_info_filter_count_appinfo(pstAppInfoFilterHandle, &nCount);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_filter_count_appinfo", AppManagerGetError(nRet), app_info_filter_destroy(pstAppInfoFilterHandle));
	if ( !nCount )
	{
		FPRINTF("[Line : %d][%s] app_info_filter_count_appinfo error returned = app info count is zero\\n", __LINE__, API_NAMESPACE);
		app_info_filter_destroy(pstAppInfoFilterHandle);
		return 1;
	}

	nRet = app_info_filter_destroy(pstAppInfoFilterHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_filter_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Scenario to create and destroy application info filter
/**
* @testcase 			ITc_app_manager_app_info_filter_create_destroy_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To create and destroy application info filter
* @scenario				Create filter handle from db\n
* 						destroys filter handle
* @apicovered			app_info_filter_create, app_info_filter_destroy
* @passcase				If app_info_filter_create and app_info_filter_destroy returns success and Handle returned is not NULL
* @failcase				If app_info_filter_create or app_info_filter_destroy or Handle returned is NULL
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_info_filter_create_destroy_p(void)
{
	START_TEST;

	app_info_filter_h pstAppInfoFilterHandle = NULL;

	//Target API
	int nRet = app_info_filter_create(&pstAppInfoFilterHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_filter_create", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppInfoFilterHandle, "app_info_filter_create");

	nRet = app_info_filter_destroy(pstAppInfoFilterHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_filter_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Scenario to get the application ID with the given application info
/**
* @testcase 			ITc_app_manager_app_info_get_app_id_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To get the application ID with the given application info
* @scenario				Get the application information for the given application ID\n
* 						Get the application ID with the given application info\n
* 						Destroys application info handle
* @apicovered			app_manager_get_app_info, app_info_get_app_id, app_info_destroy
* @passcase				If app_info_get_app_id returns success and ID returned is not NULL and supporting API are passed
* @failcase				If app_info_get_app_id returns fail or ID returned is NULL or any supporting API fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_info_get_app_id_p(void)
{
	START_TEST;

	app_info_h pstAppInfoHandle = NULL;
	char *pszAppID = NULL;

	int nRet = app_manager_get_app_info((const char *)TEST_TESTAPPLICATION_APPID, &pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_info", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppInfoHandle, "app_manager_get_app_info");

	//Target API
	nRet = app_info_get_app_id(pstAppInfoHandle, &pszAppID);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_get_app_id", AppManagerGetError(nRet), app_info_destroy(pstAppInfoHandle));
	if ( pszAppID == NULL )
	{
		FPRINTF("[Line : %d][%s] app_info_get_app_id failed, error returned = ID returned is NULL\\n", __LINE__, API_NAMESPACE);
		app_info_destroy(pstAppInfoHandle);
		return 1;
	}
	FREE_MEMORY(pszAppID);
	nRet = app_info_destroy(pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Scenario to get the executable path of the application
/**
* @testcase 			ITc_app_manager_app_info_get_exec_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To get the executable path of the application
* @scenario				Get the application information for the given application ID\n
* 						Get the executable path of the application\n
* 						Destroys application info handle
* @apicovered			app_manager_get_app_info, app_info_get_exec, app_info_destroy
* @passcase				If app_info_get_exec returns success and path returned is not NULL and supporting API are passed
* @failcase				If app_info_get_exec returns fail or path returned is NULL or any supporting API fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_info_get_exec_p(void)
{
	START_TEST;

	app_info_h pstAppInfoHandle = NULL;
	char *pszAppPath = NULL;

	int nRet = app_manager_get_app_info((const char *)TEST_TESTAPPLICATION_APPID, &pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_info", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppInfoHandle, "app_manager_get_app_info");

	//Target API
	nRet = app_info_get_exec(pstAppInfoHandle, &pszAppPath);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_get_exec", AppManagerGetError(nRet), app_info_destroy(pstAppInfoHandle));
	if ( pszAppPath == NULL )
	{
		FPRINTF("[Line : %d][%s] app_info_get_exec error returned = path returned is NULL\\n", __LINE__, API_NAMESPACE);
		app_info_destroy(pstAppInfoHandle);
		return 1;
	}
	FREE_MEMORY(pszAppPath);
	nRet = app_info_destroy(pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Scenario to get the absolute path to the icon image
/**
* @testcase 			ITc_app_manager_app_info_get_icon_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To get the absolute path to the icon image
* @scenario				Get the application information for the given application ID\n
* 						Get the absolute path to the icon image\n
* 						Destroys application info handle
* @apicovered			app_manager_get_app_info, app_info_get_icon, app_info_destroy
* @passcase				If app_info_get_icon returns success and path returned is not NULL and supporting API are passed
* @failcase				If app_info_get_icon returns fail or path returned is NULL or any supporting API fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_info_get_icon_p(void)
{
	START_TEST;

	app_info_h pstAppInfoHandle = NULL;
	char *pszAppPath = NULL;

	int nRet = app_manager_get_app_info((const char *)TEST_TESTAPPLICATION_APPID, &pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_info", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppInfoHandle, "app_manager_get_app_info");

	//Target API
	nRet = app_info_get_icon(pstAppInfoHandle, &pszAppPath);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_get_icon", AppManagerGetError(nRet), app_info_destroy(pstAppInfoHandle));
	if ( pszAppPath == NULL )
	{
		FPRINTF("[Line : %d][%s] app_info_get_icon error returned = path returned is NULL\\n", __LINE__, API_NAMESPACE);
		app_info_destroy(pstAppInfoHandle);
		return 1;
	}
	FREE_MEMORY(pszAppPath);	
	nRet = app_info_destroy(pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Scenario to get the name of the application
/**
* @testcase 			ITc_app_manager_app_info_get_label_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To get the name of the application
* @scenario				Get the application information for the given application ID\n
* 						Get the absolute path to the icon image\n
* 						Destroys application info handle
* @apicovered			app_manager_get_app_info, app_info_get_label, app_info_destroy
* @passcase				If app_info_get_label returns success and path returned is not NULL and supporting API are passed
* @failcase				If app_info_get_label returns fail or path returned is NULL or any supporting API fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_info_get_label_p(void)
{
	START_TEST;

	app_info_h pstAppInfoHandle = NULL;
	char *pszAppPath = NULL;

	int nRet = app_manager_get_app_info((const char *)TEST_TESTAPPLICATION_APPID, &pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_info", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppInfoHandle, "app_manager_get_app_info");

	//Target API
	nRet = app_info_get_label(pstAppInfoHandle, &pszAppPath);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_get_label", AppManagerGetError(nRet), app_info_destroy(pstAppInfoHandle));
	if ( pszAppPath == NULL )
	{
		FPRINTF("[Line : %d][%s] app_info_get_label error returned = path returned is NULL\\n", __LINE__, API_NAMESPACE);
		app_info_destroy(pstAppInfoHandle);
		return 1;
	}
	FREE_MEMORY(pszAppPath);	
	nRet = app_info_destroy(pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Scenario to get the package name.
/**
* @testcase 			ITc_app_manager_app_info_get_package_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To get the package name.
* @scenario				Get the application information for the given application ID\n
* 						Get the package name\n
* 						Destroys application info handle
* @apicovered			app_manager_get_app_info, app_info_get_package, app_info_destroy
* @passcase				If app_info_get_package returns success and path returned is not NULL and supporting API are passed
* @failcase				If app_info_get_package returns fail or path returned is NULL or any supporting API fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_info_get_package_p(void)
{
	START_TEST;

	app_info_h pstAppInfoHandle = NULL;
	char *pszAppPath = NULL;

	int nRet = app_manager_get_app_info((const char *)TEST_TESTAPPLICATION_APPID, &pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_info", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppInfoHandle, "app_manager_get_app_info");

	//Target API
	nRet = app_info_get_package(pstAppInfoHandle, &pszAppPath);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_get_package", AppManagerGetError(nRet), app_info_destroy(pstAppInfoHandle));
	if ( pszAppPath == NULL )
	{
		FPRINTF("[Line : %d][%s] app_info_get_package error returned = path returned is NULL\\n", __LINE__, API_NAMESPACE);
		app_info_destroy(pstAppInfoHandle);
		return 1;
	}
	FREE_MEMORY(pszAppPath);	
	nRet = app_info_destroy(pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Scenario to get the package type name.
/**
* @testcase 			ITc_app_manager_app_info_get_type_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To get the package type name.
* @scenario				Get the application information for the given application ID\n
* 						Get the package type name\n
* 						Destroys application info handle
* @apicovered			app_manager_get_app_info, app_info_get_type, app_info_destroy
* @passcase				If app_info_get_type returns success and path returned is not NULL and supporting API are passed
* @failcase				If app_info_get_type returns fail or path returned is NULL or any supporting API fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_info_get_type_p(void)
{
	START_TEST;

	app_info_h pstAppInfoHandle = NULL;
	char *pszAppPath = NULL;

	int nRet = app_manager_get_app_info((const char *)TEST_TESTAPPLICATION_APPID, &pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_info", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppInfoHandle, "app_manager_get_app_info");

	//Target API
	nRet = app_info_get_type(pstAppInfoHandle, &pszAppPath);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_get_type", AppManagerGetError(nRet), app_info_destroy(pstAppInfoHandle));
	if ( pszAppPath == NULL )
	{
		FPRINTF("[Line : %d][%s] app_info_get_type error returned = path returned is NULL\\n", __LINE__, API_NAMESPACE);
		app_info_destroy(pstAppInfoHandle);
		return 1;
	}
	FREE_MEMORY(pszAppPath);	
	nRet = app_info_destroy(pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Scenario to check whether application is enabled.

/**
* @testcase 			ITc_app_manager_app_info_is_enabled_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To check whether application is enabled.
* @scenario				Get the application information for the given application ID\n
* 						Check whether application is enabled.\n
* 						Destroys application info handle
* @apicovered			app_manager_get_app_info, app_info_is_enabled, app_info_destroy
* @passcase				If app_info_is_enabled returns success and bool returned is true and supporting API are passed
* @failcase				If app_info_is_enabled returns fail or bool returned is false or any supporting API fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_info_is_enabled_p(void)
{
	START_TEST;

	app_info_h pstAppInfoHandle = NULL;
	bool bStatus = false;

	int nRet = app_manager_get_app_info((const char *)TEST_TESTAPPLICATION_APPID, &pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_info", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppInfoHandle, "app_manager_get_app_info");

	//Target API
	nRet = app_info_is_enabled(pstAppInfoHandle, &bStatus);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_get_exec", AppManagerGetError(nRet), app_info_destroy(pstAppInfoHandle));
	if ( !bStatus )
	{
		FPRINTF("[Line : %d][%s] app_info_is_enabled error returned = status is false\\n", __LINE__, API_NAMESPACE);
		app_info_destroy(pstAppInfoHandle);
		return 1;
	}

	nRet = app_info_destroy(pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Scenario to check whether two application information are equal

/**
* @testcase 			ITc_app_manager_app_info_is_equal_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To check whether two application information are equal
* @scenario				Get the application information for the given application ID\n
* 						Get the application information for the given application ID to compare\n
* 						Check whether two information are equal\n
* 						Destroys application info handle\n
* 						Destroys compared application info handle
* @apicovered			app_manager_get_app_info, app_info_is_equal, app_info_destroy
* @passcase				If app_info_is_equal returns success and bool returned is true and supporting API are passed
* @failcase				If app_info_is_equal returns fail or bool returned is false or any supporting API fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_info_is_equal_p(void)
{
	START_TEST;

	app_info_h pstAppInfoHandle = NULL, pstAppInfoCompareHandle = NULL;
	bool bStatus = false;

	int nRet = app_manager_get_app_info((const char *)TEST_TESTAPPLICATION_APPID, &pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_info", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppInfoHandle, "app_manager_get_app_info");

	nRet = app_manager_get_app_info((const char *)TEST_TESTAPPLICATION_APPID, &pstAppInfoCompareHandle);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_info", AppManagerGetError(nRet), app_info_destroy(pstAppInfoHandle));
	if ( pstAppInfoCompareHandle == NULL )
	{
		FPRINTF("[Line : %d][%s] app_manager_get_app_info failed for compared app, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE);
		app_info_destroy(pstAppInfoHandle);
		return 1;
	}

	//Target API
	nRet = app_info_is_equal(pstAppInfoHandle, pstAppInfoCompareHandle, &bStatus);
	if ( nRet != APP_MANAGER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_info_is_equal error returned = %s\\n", __LINE__, API_NAMESPACE, AppManagerGetError(nRet));
		app_info_destroy(pstAppInfoCompareHandle);
		app_info_destroy(pstAppInfoHandle);
		return 1;
	}
	else if ( !bStatus )
	{
		FPRINTF("[Line : %d][%s] app_info_is_equal error returned = status is false\\n", __LINE__, API_NAMESPACE);
		app_info_destroy(pstAppInfoHandle);
		app_info_destroy(pstAppInfoCompareHandle);
		return 1;
	}

	nRet = app_info_destroy(pstAppInfoHandle);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_destroy", AppManagerGetError(nRet), app_info_destroy(pstAppInfoCompareHandle));

	nRet = app_info_destroy(pstAppInfoCompareHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Scenario to check whether application information is no display

/**
* @testcase 			ITc_app_manager_app_info_is_nodisplay_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To check whether application information is no display
* @scenario				Get the application information for the given application ID\n
* 						Check whether application information is no display\n
* 						Destroys application info handle
* @apicovered			app_manager_get_app_info, app_info_is_nodisplay, app_info_destroy
* @passcase				If app_info_is_nodisplay returns success and supporting API are passed
* @failcase				If app_info_is_nodisplay returns fail or any supporting API fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_info_is_nodisplay_p(void)
{
	START_TEST;

	app_info_h pstAppInfoHandle = NULL;
	bool bStatus = false;

	int nRet = app_manager_get_app_info((const char *)TEST_TESTAPPLICATION_APPID, &pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_info", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppInfoHandle, "app_manager_get_app_info");

	//Target API
	nRet = app_info_is_nodisplay(pstAppInfoHandle, &bStatus);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_is_nodisplay", AppManagerGetError(nRet), app_info_destroy(pstAppInfoHandle));

	nRet = app_info_destroy(pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Scenario to check whether application is launched on booting time

/**
* @testcase 			ITc_app_manager_app_info_is_onboot_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To check whether application is launched on booting time
* @scenario				Get the application information for the given application ID\n
* 						Check whether application is launched on booting time\n
* 						Destroys application info handle
* @apicovered			app_manager_get_app_info, app_info_is_onboot, app_info_destroy
* @passcase				If app_info_is_onboot returns success and supporting API are passed
* @failcase				If app_info_is_onboot returns fail or any supporting API fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_info_is_onboot_p(void)
{
	START_TEST;

	app_info_h pstAppInfoHandle = NULL;
	bool bStatus = false;

	int nRet = app_manager_get_app_info((const char *)TEST_TESTAPPLICATION_APPID, &pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_info", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppInfoHandle, "app_manager_get_app_info");

	//Target API
	nRet = app_info_is_onboot(pstAppInfoHandle, &bStatus);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_is_onboot", AppManagerGetError(nRet), app_info_destroy(pstAppInfoHandle));

	nRet = app_info_destroy(pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Scenario to check whether application is launched on booting time

/**
* @testcase 			ITc_app_manager_app_info_is_preload_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To check whether application is launched on booting time
* @scenario				Get the application information for the given application ID\n
* 						Check whether application is launched on booting time\n
* 						Destroys application info handle
* @apicovered			app_manager_get_app_info, app_info_is_preload, app_info_destroy
* @passcase				If app_info_is_preload returns success and supporting API are passed
* @failcase				If app_info_is_preload returns fail or any supporting API fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_info_is_preload_p(void)
{
	START_TEST;

	app_info_h pstAppInfoHandle = NULL;
	bool bStatus = false;

	int nRet = app_manager_get_app_info((const char *)TEST_TESTAPPLICATION_APPID, &pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_info", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppInfoHandle, "app_manager_get_app_info");

	//Target API
	nRet = app_info_is_preload(pstAppInfoHandle, &bStatus);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_is_preload", AppManagerGetError(nRet), app_info_destroy(pstAppInfoHandle));

	nRet = app_info_destroy(pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Scenario to check create add and destroy metadata filters
/**
* @testcase 			ITc_app_manager_app_info_metadata_filter_create_add_destroy_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To check create add and destroy metadata filters
* @scenario				Creates the application's metadata information filter handle from db\n
* 						Adds filter condition for the query API\n
* 						Destroys the application's metadata information filter handle
* @apicovered			app_info_metadata_filter_create, app_info_metadata_filter_add, app_info_metadata_filter_destroy
* @passcase				If app_info_metadata_filter_create and app_info_metadata_filter_add and app_info_metadata_filter_destroy returns success
* @failcase				If app_info_metadata_filter_create or app_info_metadata_filter_add or app_info_metadata_filter_destroy returns fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_info_metadata_filter_create_add_destroy_p(void)
{
	START_TEST;

	app_info_metadata_filter_h pstFilterHandle = NULL;

	int nRet = app_info_metadata_filter_create(&pstFilterHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_metadata_filter_create", AppManagerGetError(nRet));
	CHECK_HANDLE(pstFilterHandle, "app_info_metadata_filter_create");

	// Target API
	nRet = app_info_metadata_filter_add(pstFilterHandle, MKEY, MVALUE);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_metadata_filter_add", AppManagerGetError(nRet), app_info_metadata_filter_destroy(pstFilterHandle));

	// Target API
	nRet = app_info_metadata_filter_destroy(pstFilterHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_metadata_filter_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: To get the localed name of the application
/**
* @testcase 			ITc_app_manager_app_info_get_localed_label_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To get the localed name of the application
* @scenario				Get the application info\n
* 						Get the application ID\n
* 						Get the localed name of the application\n
* 						Destroy the application info
* @apicovered			app_manager_get_app_info, app_info_get_app_id, app_info_get_localed_label, app_info_destroy
* @passcase				If app_manager_get_app_info, app_info_get_app_id, app_info_get_localed_label, app_info_destroy returns success and returned handle is not NULL also the label and ID returned is not NULL
* @failcase				If app_manager_get_app_info or app_info_get_app_id or app_info_get_localed_label or app_info_destroy returns fail or returned handle is not NULL also the label or ID returned is NULL
* @precondition			app manager instance should be created
* @postcondition		app manager instance should be destroyed
*/
int ITc_app_manager_app_info_get_localed_label_p(void)
{
	START_TEST;

	app_info_h pstAppInfoHandle = NULL;
	char *pszAppID = NULL;
	char *pszLabel = NULL;

	int nRet = app_manager_get_app_info((const char *)TEST_TESTAPPLICATION_APPID, &pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_info", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppInfoHandle, "app_manager_get_app_info");

	nRet = app_info_get_app_id(pstAppInfoHandle, &pszAppID);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_get_app_id", AppManagerGetError(nRet), app_info_destroy(pstAppInfoHandle));
	if ( pszAppID == NULL )
	{
		FPRINTF("[Line : %d][%s] app_info_get_app_id failed, error returned = ID returned is NULL\\n", __LINE__, API_NAMESPACE);
		app_info_destroy(pstAppInfoHandle);
		return 1;
	}

	//Target API
	nRet = app_info_get_localed_label(pszAppID, (const char *)LOCALE, &pszLabel);
	if ( nRet != APP_MANAGER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_info_get_localed_label error returned = %s\\n", __LINE__, API_NAMESPACE, AppManagerGetError(nRet));
		FREE_MEMORY(pszAppID);
		app_info_destroy(pstAppInfoHandle);
		return 1;
	}

	if ( pszLabel == NULL )
	{
		FPRINTF("[Line : %d][%s] app_info_get_localed_label failed, error returned = ID returned is NULL\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszAppID);
		app_info_destroy(pstAppInfoHandle);
		return 1;
	}
	FREE_MEMORY(pszAppID);
	FREE_MEMORY(pszLabel);
	nRet = app_info_destroy(pstAppInfoHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Gets the application component type.
/**
* @testcase 			ITc_app_manager_app_info_get_app_component_type_p
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @since_tizen 			4.0
* @description			Gets the application component type.
* @scenario				Gets the application component type and compare with expected value.
* @apicovered			app_info_get_app_component_type
* @passcase				If app_info_get_app_component_type returns success or type matches
* @failcase				If app_info_get_app_component_type or any precondition api returns fail or type mismatch
* @precondition			app manager instance should be created
* @postcondition		app manager instance should be destroyed
*/
int ITc_app_manager_app_info_get_app_component_type_p(void)
{
	START_TEST;

	const char *AppIDs[] =
	{
		TEST_TESTAPPLICATION_APPID,
		TEST_COMPONENTBASED_APPID
	};

	app_info_app_component_type_e eAPP_COMP_TYPE[] =
	{
		APP_INFO_APP_COMPONENT_TYPE_UI_APP,
		APP_INFO_APP_COMPONENT_TYPE_COMPONENT_BASED_APP
	};

	app_info_h hAppInfo = NULL;
	app_info_app_component_type_e eGetComponent;
	int nRet = APP_MANAGER_ERROR_NONE;
	int nLoopCnt, nLoopSize;

	nLoopSize = sizeof(AppIDs)/sizeof(AppIDs[0]);

	for (nLoopCnt = 0; nLoopCnt < nLoopSize; nLoopCnt++)
	{
		nRet = app_manager_get_app_info((const char *)AppIDs[nLoopCnt], &hAppInfo);
		PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_info", AppManagerGetError(nRet));
		CHECK_HANDLE(hAppInfo, "app_manager_get_app_info");

		nRet = app_info_get_app_component_type(hAppInfo, &eGetComponent);
		PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_get_component_type", AppManagerGetError(nRet),app_info_destroy(hAppInfo));
		PRINT_RESULT_CLEANUP(eAPP_COMP_TYPE[nLoopCnt], eGetComponent, "app_info_get_component_type", AppManagerGetError(nRet),app_info_destroy(hAppInfo));

		nRet = app_info_destroy(hAppInfo);
		PRINT_RESULT_NORETURN(APP_MANAGER_ERROR_NONE, nRet, "app_info_destroy", AppManagerGetError(nRet));
	}
	return 0;
}

/** @} */
/** @} */
