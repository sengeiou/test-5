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
* @function 		ITs_app_manager_context_startup
* @description	 	Called before each test, opens pre-defined app
* @parameter		NA
* @return 			NA
*/
void ITs_app_manager_context_startup(void)
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

	TCT_CheckInstalledApp(2, TEST_TESTAPPLICATION_APPID, TEST_APPMANAGERTESTFILE_APPID);
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
* @function 		ITs_app_manager_context_cleanup
* @description	 	Called after each test, terminates the app opened in startup
* @parameter		NA
* @return 			NA
*/
void ITs_app_manager_context_cleanup(void)
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
//& purpose: To clone and destroy the application context handle
/**
* @testcase 			ITc_app_manager_app_context_clone_destroy_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To clone the application context handle
* @scenario				Get the application context\n
* 						clone the application context\n
* 						Terminate the cloned application context\n
* 						Terminate the get application context
* @apicovered			app_manager_get_app_context, app_context_clone, app_context_destroy
* @passcase				If app_manager_get_app_context, app_context_clone and app_context_destroy returns success and handle returned is not NULL
* @failcase				If app_manager_get_app_context or app_context_clone or app_context_destroy returns false or handle returned is NULL
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_context_clone_destroy_p(void)
{
	START_TEST;

	app_context_h pstAppContextToCloneHandle = NULL, pstAppContextFromCloneHandle = NULL;

	int nRet = app_manager_get_app_context((const char *)TEST_TESTAPPLICATION_APPID, &pstAppContextFromCloneHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_context", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppContextFromCloneHandle, "app_manager_get_app_context");

	//Target API
	nRet = app_context_clone(&pstAppContextToCloneHandle, pstAppContextFromCloneHandle);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_context_clone", AppManagerGetError(nRet), app_context_destroy(pstAppContextFromCloneHandle));
	if ( pstAppContextToCloneHandle == NULL )
	{
		FPRINTF("[Line : %d][%s] app_context_clone error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE);
		app_context_destroy(pstAppContextFromCloneHandle);
		return 1;
	}

	nRet = app_context_destroy(pstAppContextToCloneHandle);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_context_destroy", AppManagerGetError(nRet), app_context_destroy(pstAppContextFromCloneHandle));

	nRet = app_context_destroy(pstAppContextFromCloneHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_context_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: To get the ID of the application for the given process ID
/**
* @testcase 			ITc_app_manager_app_context_get_app_id_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To get the ID of the application for the given process ID
* @scenario				Get the application context\n
* 						Get the ID of the application for the given process ID\n
* 						Terminate the application context
* @apicovered			app_manager_get_app_context, app_context_get_app_id, app_context_destroy
* @passcase				If app_manager_get_app_context, app_context_get_app_id and app_context_destroy returns success and handle returned is not NULL
* @failcase				If app_manager_get_app_context or app_context_get_app_id or app_context_destroy returns false or handle returned is NULL
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_context_get_app_id_p(void)
{
	START_TEST;

	app_context_h pstAppContextHandle = NULL;
	char *pszAppID = NULL;

	int nRet = app_manager_get_app_context((const char *)TEST_TESTAPPLICATION_APPID, &pstAppContextHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_context", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppContextHandle, "app_manager_get_app_context");

	//Target API
	nRet = app_context_get_app_id(pstAppContextHandle, &pszAppID);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_context_get_app_id", AppManagerGetError(nRet), app_context_destroy(pstAppContextHandle));
	if ( pszAppID == NULL )
	{
		FPRINTF("[Line : %d][%s] app_context_get_app_id error returned = App ID returned is NULL\\n", __LINE__, API_NAMESPACE);
		app_context_destroy(pstAppContextHandle);
		return 1;
	}
	FREE_MEMORY(pszAppID);	
	nRet = app_context_destroy(pstAppContextHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_context_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: To get the package with the given application context
/**
* @testcase 			ITc_app_manager_app_context_get_package_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To get the package with the given application context
* @scenario				Get the application context\n
* 						Get the package with the given application context\n
* 						Terminate the application context
* @apicovered			app_manager_get_app_context, app_context_get_package, app_context_destroy
* @passcase				If app_manager_get_app_context, app_context_get_package and app_context_destroy returns success and handle returned is not NULL
* @failcase				If app_manager_get_app_context or app_context_get_package or app_context_destroy returns false or handle returned is NULL
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_context_get_package_p(void)
{
	START_TEST;

	app_context_h pstAppContextHandle = NULL;
	char *pszAppID = NULL;

	int nRet = app_manager_get_app_context((const char *)TEST_TESTAPPLICATION_APPID, &pstAppContextHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_context", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppContextHandle, "app_manager_get_app_context");

	//Target API
	nRet = app_context_get_package(pstAppContextHandle, &pszAppID);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_context_get_package", AppManagerGetError(nRet), app_context_destroy(pstAppContextHandle));
	if ( pszAppID == NULL )
	{
		FPRINTF("[Line : %d][%s] app_context_get_package error returned = Package returned is NULL\\n", __LINE__, API_NAMESPACE);
		app_context_destroy(pstAppContextHandle);
		return 1;
	}
	FREE_MEMORY(pszAppID);	
	nRet = app_context_destroy(pstAppContextHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_context_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: To get the process ID with the given application context
/**
* @testcase 			ITc_app_manager_app_context_get_pid_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To get the package with the given application context
* @scenario				Get the application context\n
* 						Get the process ID with the given application context\n
* 						Terminate the application context
* @apicovered			app_manager_get_app_context, app_context_get_pid, app_context_destroy
* @passcase				If app_manager_get_app_context, app_context_get_pid and app_context_destroy returns success and handle returned is not NULL
* @failcase				If app_manager_get_app_context or app_context_get_pid or app_context_destroy returns false or handle returned is NULL
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_context_get_pid_p(void)
{
	START_TEST;

	app_context_h pstAppContextHandle = NULL;
	pid_t nAppID = 0;

	int nRet = app_manager_get_app_context((const char *)TEST_TESTAPPLICATION_APPID, &pstAppContextHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_context", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppContextHandle, "app_manager_get_app_context");

	//Target API
	nRet = app_context_get_pid(pstAppContextHandle, &nAppID);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_context_get_pid", AppManagerGetError(nRet), app_context_destroy(pstAppContextHandle));
	if ( nAppID < 0 )
	{
		FPRINTF("[Line : %d][%s] app_context_get_pid error returned = PID returned is Negative\\n", __LINE__, API_NAMESPACE);
		app_context_destroy(pstAppContextHandle);
		return 1;
	}

	nRet = app_context_destroy(pstAppContextHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_context_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: To get the process ID with the given application context
/**
* @testcase 			ITc_app_manager_app_context_is_terminated_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To get the package with the given application context
* @scenario				Get the application context\n
* 						Terminate the application context\n
* 						Check if application context is terminated
* @apicovered			app_control_create, app_control_set_app_id, app_control_send_launch_request, app_manager_get_app_context, app_context_is_terminated, app_context_destroy, app_control_send_terminate_request
* @passcase				If app_manager_get_app_context, app_context_is_terminated and app_context_destroy returns success and handle returned is not NULL
* @failcase				If app_manager_get_app_context or app_context_is_terminated or app_context_destroy returns false or handle returned is NULL
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_context_is_terminated_p(void)
{
	START_TEST;

	app_context_h pstAppContextHandle = NULL;
	bool bStatus = true;
	app_control_h app_control_handler = NULL;

	int nRet = app_control_create(&app_control_handler);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));
	CHECK_HANDLE(app_control_handler, "app_control_create");

	nRet = app_control_set_app_id(app_control_handler, TEST_APPMANAGERTESTFILE_APPID);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(app_control_handler));

	nRet = app_control_add_extra_data(app_control_handler, "Term_SECONDARYAPP", "Term_Value");
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_add_extra_data", AppControlGetError(nRet), app_control_destroy(app_control_handler));

	nRet = app_control_send_launch_request(app_control_handler , NULL , NULL);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_send_launch_request", AppControlGetError(nRet), app_control_destroy(app_control_handler));

	sleep(1);//sleep for app to open

	nRet = app_manager_get_app_context(TEST_APPMANAGERTESTFILE_APPID, &pstAppContextHandle);
	if ( nRet != APP_MANAGER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_manager_get_app_context error returned = %s\\n", __LINE__, API_NAMESPACE, AppManagerGetError(nRet));
		app_control_send_terminate_request(app_control_handler);
		app_control_destroy(app_control_handler);
		return 1;
	}
	if ( pstAppContextHandle == NULL )
	{
		FPRINTF("[Line : %d][%s] app_manager_get_app_context error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE);
		app_control_send_terminate_request(app_control_handler);
		app_control_destroy(app_control_handler);
		return 1;
	}
	sleep(10);
	//Target API
	nRet = app_context_is_terminated(pstAppContextHandle, &bStatus);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_context_is_terminated", AppManagerGetError(nRet), app_control_destroy(app_control_handler));
	if ( bStatus == false )
	{
		FPRINTF("[Line : %d][%s] app_context_is_terminated error returned = Application is running\\n", __LINE__, API_NAMESPACE);
		app_control_destroy(app_control_handler);
		return 1;
	}

	nRet = app_context_destroy(pstAppContextHandle);
	if ( nRet != APP_MANAGER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_context_destroy error returned = %s\\n", __LINE__, API_NAMESPACE, AppManagerGetError(nRet));
		app_control_send_terminate_request(app_control_handler);
		app_control_destroy(app_control_handler);
		return 1;
	}


	nRet = app_control_destroy(app_control_handler);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: To get the process ID with the given application context
/**
* @testcase 			ITc_app_manager_app_context_is_equal_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To get the package with the given application context
* @scenario				Get the application context\n
* 						Get the application context in another handle\n
* 						Compare the two context\n
* 						Terminate the application context\n
* 						Terminate the application context for compared application
* @apicovered			app_manager_get_app_context, app_context_is_equal, app_context_destroy
* @passcase				If app_manager_get_app_context, app_context_is_equal and app_context_destroy returns success and handle returned is not NULL
* @failcase				If app_manager_get_app_context or app_context_is_equal or app_context_destroy returns false or handle returned is NULL
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_context_is_equal_p(void)
{
	START_TEST;

	app_context_h pstAppContextHandle = NULL, pstAppContextDupHandle = NULL;
	bool bStatus = false;

	int nRet = app_manager_get_app_context((const char *)TEST_TESTAPPLICATION_APPID, &pstAppContextHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_context", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppContextHandle, "app_manager_get_app_context");

	nRet = app_manager_get_app_context((const char *)TEST_TESTAPPLICATION_APPID, &pstAppContextDupHandle);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_context", AppManagerGetError(nRet), app_context_destroy(pstAppContextHandle));
	if ( pstAppContextDupHandle == NULL )
	{
		FPRINTF("[Line : %d][%s] app_manager_get_app_context error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE);
		app_context_destroy(pstAppContextHandle);
		return 1;
	}

	//Target API
	nRet = app_context_is_equal(pstAppContextHandle, pstAppContextDupHandle, &bStatus);
	if ( nRet != APP_MANAGER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_context_is_equal error returned = Application contexts are not equal\\n", __LINE__, API_NAMESPACE);
		app_context_destroy(pstAppContextHandle);
		app_context_destroy(pstAppContextDupHandle);
		return 1;
	}
	if ( bStatus != true )
	{
		FPRINTF("[Line : %d][%s] app_context_is_equal error returned = Application contexts are not equal\\n", __LINE__, API_NAMESPACE);
		app_context_destroy(pstAppContextHandle);
		app_context_destroy(pstAppContextDupHandle);
		return 1;
	}

	nRet = app_context_destroy(pstAppContextHandle);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_context", AppManagerGetError(nRet), app_context_destroy(pstAppContextDupHandle));

	nRet = app_context_destroy(pstAppContextDupHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_context_destroy", AppManagerGetError(nRet));
	return 0;
}


//& type: auto
//& purpose: Retrieves all application contexts of running applications
/**
* @testcase 			ITc_app_manager_foreach_running_app_context_p
* @author				SRID(shilpa.j)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			To get the application contexts of running applications
* @scenario				To get the application contexts of running applications* 						
* @apicovered			app_manager_foreach_running_app_context,app_context_destroy
* @passcase				If app_manager_foreach_running_app_contex returns success and handle returned is not NULL
* @failcase				If app_manager_foreach_running_app_context or app_context_destroy returns false or handle returned is NULL
* @precondition			
* @postcondition		app manager instance should be destroyed
*/
int ITc_app_manager_foreach_running_app_context_p(void)
{
	START_TEST;
	g_bAppManagerCallback = false;
	int nDelay = 0;
	int nRet = app_manager_foreach_running_app_context(AppManagerAppContextCallback, NULL);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_foreach_running_app_context", AppManagerGetError(nRet));
	do
	{
		nDelay = nDelay + 2;
		if ( nDelay >= TIME_DELAY )
		{
			break;
		}
		usleep(USLEEPDELAY);
	} while(!g_bAppManagerCallback);
	
	if(!g_bAppManagerCallback)
	{
		FPRINTF("[Line : %d][%s] app_manager_foreach_running_app_context callback app_manager_app_context_cb_p not invoked \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
		
	return 0;
}
//& purpose: To get the package ID with the given application context
/**
* @testcase 			ITc_app_manager_app_context_get_package_id_p
* @author				SRID(shilpa.j)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			To get the package ID with the given application context
* @scenario				Get the application context\n
* 						Get the package ID with the given application context
* 						Terminate the application context
* @apicovered			app_manager_get_app_context, app_context_get_package_id, app_context_destroy
* @passcase				If app_manager_get_app_context, app_context_get_package_id and app_context_destroy returns success and handle returned is not NULL
* @failcase				If app_manager_get_app_context or app_context_get_package_id or app_context_destroy returns false or handle returned is NULL
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_context_get_package_id_p(void)
{
	START_TEST;

	app_context_h pstAppContextHandle = NULL;
	char*pszPackageID = NULL;

	int nRet = app_manager_get_app_context((const char *)TEST_TESTAPPLICATION_APPID, &pstAppContextHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_context", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppContextHandle, "app_manager_get_app_context");

	//Target API
	nRet = app_context_get_package_id(pstAppContextHandle, &pszPackageID);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_context_get_package_id", AppManagerGetError(nRet), app_context_destroy(pstAppContextHandle));
	if ( pszPackageID == NULL )
	{
		FPRINTF("[Line : %d][%s] app_context_get_package_id error returned = PID returned is NULL\\n", __LINE__, API_NAMESPACE);
		app_context_destroy(pstAppContextHandle);
		return 1;
	}

	free(pszPackageID);	
	nRet = app_context_destroy(pstAppContextHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_context_destroy", AppManagerGetError(nRet));
	return 0;
}

//& purpose: To get the application state with the given application context
/**
* @testcase 			ITc_app_manager_app_context_get_app_state_p
* @author				SRID(shilpa.j)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			To get the application state with the given application context
* @scenario				Get the application context\n
* 						Get the application state with the given application context
* 						Terminate the application context
* @apicovered			app_manager_get_app_context, app_context_get_app_state, app_context_destroy
* @passcase				If app_manager_get_app_context, app_context_get_app_state and app_context_destroy returns success and handle returned is not NULL
* @failcase				If app_manager_get_app_context or app_context_get_app_state or app_context_destroy returns false or handle returned is NULL
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_context_get_app_state_p(void)
{
	START_TEST;

	app_context_h pstAppContextHandle = NULL;
	app_state_e state = -1;

	int nRet = app_manager_get_app_context((const char *)TEST_TESTAPPLICATION_APPID, &pstAppContextHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_context", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppContextHandle, "app_manager_get_app_context");

	//Target API
	nRet = app_context_get_app_state(pstAppContextHandle, &state);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_context_get_app_state", AppManagerGetError(nRet), app_context_destroy(pstAppContextHandle));
	if ( state == -1)
	{
		FPRINTF("[Line : %d][%s] app_context_get_app_state error returned = state returned is Not valid\\n", __LINE__, API_NAMESPACE);
		app_context_destroy(pstAppContextHandle);
		return 1;
	}

	nRet = app_context_destroy(pstAppContextHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_context_destroy", AppManagerGetError(nRet));
	return 0;
}
//& purpose: To check the application for subApp with the given application context
/**
* @testcase 			ITc_app_manager_app_context_is_sub_app_p
* @author				SRID(shilpa.j)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			To get the application state with the given application context
* @scenario				Get the application context\n
* 						Get the application state with the given application context
* 						Terminate the application context
* @apicovered			app_manager_get_app_context, app_context_is_sub_app, app_context_destroy
* @passcase				If app_manager_get_app_context, app_context_is_sub_app and app_context_destroy returns success and handle returned is not NULL
* @failcase				If app_manager_get_app_context or app_context_is_sub_app or app_context_destroy returns false or handle returned is NULL
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_app_context_is_sub_app_p(void)
{
	START_TEST;

	app_context_h pstAppContextHandle = NULL;
	bool bIsSubApp;
	int nRet = app_manager_get_app_context((const char *)TEST_TESTAPPLICATION_APPID, &pstAppContextHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_context", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppContextHandle, "app_manager_get_app_context");

	//Target API
	nRet = app_context_is_sub_app(pstAppContextHandle, &bIsSubApp);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_context_is_sub_app", AppManagerGetError(nRet), app_context_destroy(pstAppContextHandle));
	if ( bIsSubApp != true && bIsSubApp != false)
	{
		FPRINTF("[Line : %d][%s] app_context_is_sub_app  returned invalid value\\n", __LINE__, API_NAMESPACE);
		app_context_destroy(pstAppContextHandle);
		return 1;
	}

	nRet = app_context_destroy(pstAppContextHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_context_destroy", AppManagerGetError(nRet));
	return 0;
}

/** @} */
/** @} */
