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

static bool ResourceControlCB(const char *res_type,const char *min_res_version, const char *max_res_version,const char *auto_close, void *user_data)
{
	g_bResCallBackIsHit = true;
	FPRINTF("[Line : %d][%s] ResourceControlCB callback is called\\n", __LINE__, API_NAMESPACE);
	return true;
}

/**
* @function 		ITs_app_manager_startup
* @description	 	Called before each test, opens pre-defined app
* @parameter		NA
* @return 			NA
*/
void ITs_app_manager_startup(void)
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
* @function 		ITs_app_manager_cleanup
* @description	 	Called after each test, terminates the app opened in startup
* @parameter		NA
* @return 			NA
*/
void ITs_app_manager_cleanup(void)
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
//& purpose: Test app_manager_request_terminate_bg_app
/**
* @testcase 			ITc_app_manager_request_terminate_bg_app_p
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			Test app_manager_request_terminate_bg_app
* @scenario				Call app_manager_request_terminate_bg_app
* @apicovered			app_manager_request_terminate_bg_app
* @passcase				If API returns APP_MANAGER_ERROR_NONE
* @failcase				If API fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_request_terminate_bg_app_p(void)
{
	START_TEST;
	
	int nRet = APP_MANAGER_ERROR_NONE;
	app_context_h pAppContext;
	app_control_h hAppControl = NULL;

	nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_control_create", AppManagerGetError(nRet));
	CHECK_HANDLE(hAppControl, "app_control_create");

	nRet = app_control_set_app_id(hAppControl , TEST_APPMANAGERTESTFILE_APPID);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_control_set_app_id", AppManagerGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_send_launch_request(hAppControl , NULL , NULL);
	sleep(1);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_control_send_launch_request", AppManagerGetError(nRet), app_control_destroy(hAppControl));
	
	nRet = app_manager_get_app_context((const char *)TEST_APPMANAGERTESTFILE_APPID , &pAppContext);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_context", AppManagerGetError(nRet), app_control_send_terminate_request(hAppControl);app_control_destroy(hAppControl));
	if(NULL == pAppContext)
	{
		FPRINTF("[Line : %d][%s]app_manager_get_app_context returned NULL handle\\n", __LINE__, API_NAMESPACE);
		app_control_send_terminate_request(hAppControl);
		app_control_destroy(hAppControl);
		return 1;
	}
	
	nRet = app_control_send_terminate_request(hAppControl);
	sleep(1);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_control_send_terminate_request", AppManagerGetError(nRet), app_control_destroy(hAppControl));	
	
	nRet = app_manager_request_terminate_bg_app(pAppContext);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_manager_request_terminate_bg_app", AppManagerGetError(nRet), app_control_destroy(hAppControl));	

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_control_destroy", AppManagerGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: Test app_manager_set_app_context_event_cb and app_manager_unset_app_context_event_cb
/**
* @testcase 			ITc_app_manager_set_unset_app_context_event_cb_p
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			Test app_manager_set_app_context_event_cb and app_manager_unset_app_context_event_cb
* @scenario				Call app_manager_set_app_context_event_cb and app_manager_unset_app_context_event_cb
* @apicovered			app_manager_set_app_context_event_cb, app_manager_unset_app_context_event_cb
* @passcase				If API returns APP_MANAGER_ERROR_NONE
* @failcase				If API fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_set_unset_app_context_event_cb_p(void)
{
	START_TEST;

	int nRet = APP_MANAGER_ERROR_NONE, nTimeoutId = 0;
	app_control_h hAppControl = NULL;

	nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));
	CHECK_HANDLE(hAppControl, "app_control_create");

	nRet = app_control_set_app_id(hAppControl , TEST_APPMANAGERTESTFILE_APPID);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_manager_set_app_context_event_cb(AppManagerAppContextChangeCallback, NULL);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_manager_set_app_context_event_cb", AppManagerGetError(nRet), app_control_destroy(hAppControl));

	g_bAppManagerCallback = false;

	nRet = app_control_add_extra_data(hAppControl, "Term_SECONDARYAPP", "Term_Value");
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_control_add_extra_data", AppControlGetError(nRet));
	sleep(1);

	nRet = app_control_send_launch_request(hAppControl, NULL, NULL);
	sleep(1);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_control_send_launch_request", AppControlGetError(nRet), app_manager_unset_app_context_event_cb();app_control_destroy(hAppControl));
	RUN_POLLING_LOOP;

	if ( g_bAppManagerCallback == false )
	{
		FPRINTF("[Line : %d][%s] app_control_send_launch_request failed, error returned = Callback Not Invoked\\n", __LINE__, API_NAMESPACE);
		app_control_send_terminate_request(hAppControl);
		app_manager_unset_app_context_event_cb();
		app_control_destroy(hAppControl);
		return 1;
	}

	nRet = app_control_send_terminate_request(hAppControl);
	sleep(1);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_control_send_terminate_request", AppControlGetError(nRet), app_manager_unset_app_context_event_cb();app_control_destroy(hAppControl));
	app_manager_unset_app_context_event_cb();

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To retrieve contexts of all running applications.
/**
* @testcase 			ITc_app_manager_foreach_app_context_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To retrieve contexts of all running applications.
* @scenario				Register callback to get information\n
* 						Check if callback is invoked
* @apicovered			app_manager_foreach_app_context
* @passcase				If callback is invoked after app_manager_foreach_app_context is called
* @failcase				If callback is not invoked after app_manager_foreach_app_context is called
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_foreach_app_context_p(void)
{
	START_TEST;

	int nDelay = 0;
	g_bAppManagerCallback = false;

	// Target API
	int nRet = app_manager_foreach_app_context(AppManagerAppContextCallback, NULL);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_foreach_app_context", AppManagerGetError(nRet));
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
		FPRINTF("[Line : %d][%s] app_manager_foreach_app_context error returned = callback function not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: To retrieve all installed applications information
/**
* @testcase 			ITc_app_manager_foreach_app_info_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To retrieve all installed applications information
* @scenario				Register callback to get information\n
* 						Check if callback is invoked\n
* @apicovered			app_manager_foreach_app_info
* @passcase				If callback is invoked after app_manager_foreach_app_info is called
* @failcase				If callback is not invoked after app_manager_foreach_app_info is called
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_foreach_app_info_p(void)
{
	START_TEST;

	int nDelay = 0;
	g_bAppManagerCallback = false;

	// Target API
	int nRet = app_manager_foreach_app_info(AppInfoMetaDataFilterForeachCallback, NULL);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_foreach_app_info", AppManagerGetError(nRet));
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
		FPRINTF("[Line : %d][%s] app_manager_foreach_app_info error returned = callback function not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: To get the application context for the given ID of the application
/**
* @testcase 			ITc_app_manager_get_app_context_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To get the application context for the given ID of the application
* @scenario				Get the application context\n
* 						Destroy the application context
* @apicovered			app_manager_get_app_context, app_context_destroy
* @passcase				If app_manager_get_app_context, app_context_destroy returns success and returned handle is not NULL
* @failcase				If app_manager_get_app_context or app_context_destroy returns failure or returned handle is NULL
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_get_app_context_p(void)
{
	START_TEST;

	app_context_h pstAppContext = NULL;

	// Target API
	int nRet = app_manager_get_app_context((const char *)TEST_TESTAPPLICATION_APPID, &pstAppContext);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_context", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppContext, "app_manager_get_app_context");

	nRet = app_context_destroy(pstAppContext);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_context_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: To get the ID of the application for the given process ID
/**
* @testcase 			ITc_app_manager_get_app_id_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To get the ID of the application for the given process ID
* @scenario				Get the application context for the given ID of the application\n
* 						Get the process ID with the given application context\n
* 						Get the ID of the application for the given process ID\n
* 						Destroy the application context
* @apicovered			app_manager_get_app_id, app_manager_get_app_context, app_context_get_pid, app_context_destroy
* @passcase				If API returns success and returned handle is not NULL
* @failcase				If either API returns failure or returned handle is NULL or any other supporting API fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_get_app_id_p(void)
{
	START_TEST;

	int nPid = 0;
	app_context_h pstAppContext = NULL;
	char *pszAppID = NULL;

	int nRet = app_manager_get_app_context((const char *)TEST_TESTAPPLICATION_APPID, &pstAppContext);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_context", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppContext, "app_manager_get_app_context");

	nRet = app_context_get_pid(pstAppContext, &nPid);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_context_get_pid", AppManagerGetError(nRet), app_context_destroy(pstAppContext));

	if (nPid < 0)
	{
		FPRINTF("[Line : %d][%s] app_context_get_pid failed, error returned = PID returned is Negative\\n", __LINE__, API_NAMESPACE);
		app_context_destroy(pstAppContext);
		return 1;
	}

	nRet = app_manager_get_app_id(nPid, &pszAppID);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_id", AppManagerGetError(nRet), app_context_destroy(pstAppContext));

	if ( pszAppID == NULL )
	{
		FPRINTF("[Line : %d][%s] app_manager_get_app_id error returned = AppID returned is NULL\\n", __LINE__, API_NAMESPACE);
		app_context_destroy(pstAppContext);
		return 1;
	}
	else if ( strcmp(pszAppID, (const char *)TEST_TESTAPPLICATION_APPID) != 0 )
	{
		FPRINTF("[Line : %d][%s] app_manager_get_app_id error returned = AppID returned [ %s ] is not correct\\n", __LINE__, API_NAMESPACE, pszAppID);
		app_context_destroy(pstAppContext);
		FREE_MEMORY(pszAppID);
		return 1;
	}

	FREE_MEMORY(pszAppID);	
	nRet = app_context_destroy(pstAppContext);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_context_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: To get the application information for the given application ID
/**
* @testcase 			ITc_app_manager_get_app_info_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To get the application information for the given application ID
* @scenario				Get the application information\n
*						Destroy the application information
* @apicovered			app_manager_get_app_info, app_info_destroy
* @passcase				If app_manager_get_app_info, app_info_destroy returns success and returned handle is not NULL
* @failcase				If app_manager_get_app_info or app_info_destroy returns failure or returned handle is NULL
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_get_app_info_p(void)
{
	START_TEST;

	app_info_h pstAppInfo = NULL;

	int nRet = app_manager_get_app_info((const char *)TEST_TESTAPPLICATION_APPID, &pstAppInfo);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_info", AppManagerGetError(nRet));
	CHECK_HANDLE(pstAppInfo, "app_manager_get_app_info");

	nRet = app_info_destroy(pstAppInfo);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_info_destroy", AppManagerGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: To check whether the application with the given package name is running
/**
* @testcase 			ITc_app_manager_is_running_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To check whether the application with the given package name is running
* @scenario				Check if the application opened in startup is running
* @apicovered			app_manager_is_running
* @passcase				If API returns success and returned value is true
* @failcase				If either API returns failure or returned value is false
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_is_running_p(void)
{
	START_TEST;

	bool bIsRunning = false;

	// Target API
	int nRet = app_manager_is_running((const char *)TEST_TESTAPPLICATION_APPID, &bIsRunning);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_is_running", AppManagerGetError(nRet));
	if ( bIsRunning != true )
	{
		FPRINTF("[Line : %d][%s] app_manager_is_running error returned = App is not running\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: To resume an application after opening it
/**
* @testcase 			ITc_app_manager_resume_app_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To resume an application after opening it
* @scenario				Open an application\n
* 						Resume the application\n
* 						Get the opened application context\n
* 						Terminate the open application
* @apicovered			app_control_create, app_control_set_app_id, app_control_send_launch_request, app_manager_get_app_context, app_manager_resume_app \n
*						app_context_destroy, app_control_destroy, app_control_send_terminate_request
* @passcase				If app_control_send_launch_request and app_control_send_terminate_request returns success
* @failcase				If either app_control_send_launch_request, app_manager_resume_app or app_control_send_launch_request returns false or any supporting API fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_resume_app_p(void)
{
	START_TEST;

	app_context_h pstOpenAppContext = NULL;
	bool bIsRunning = false;
	app_control_h app_control_handler = NULL;

	int nRet = app_control_create(&app_control_handler);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));
	CHECK_HANDLE(app_control_handler, "app_control_create");

	nRet = app_control_set_app_id(app_control_handler , TEST_APPMANAGERTESTFILE_APPID);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(app_control_handler));

	sleep(1);
	nRet = app_control_send_launch_request(app_control_handler , NULL , NULL);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_send_launch_request", AppControlGetError(nRet), app_control_destroy(app_control_handler));

	sleep(1);
	nRet = app_manager_get_app_context(TEST_APPMANAGERTESTFILE_APPID, &pstOpenAppContext);
	if ( nRet != APP_MANAGER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_manager_get_app_context error returned = %s\\n", __LINE__, API_NAMESPACE, AppManagerGetError(nRet));
		app_control_send_terminate_request(app_control_handler);
		app_control_destroy(app_control_handler);
		return 1;
	}
	if ( pstOpenAppContext == NULL )
	{
		FPRINTF("[Line : %d][%s] app_manager_get_app_context error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE);
		app_control_send_terminate_request(app_control_handler);
		app_control_destroy(app_control_handler);
		return 1;
	}

	nRet = app_manager_resume_app(pstOpenAppContext);	
	if ( nRet != APP_MANAGER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_manager_resume_app error returned = %s\\n", __LINE__, API_NAMESPACE, AppManagerGetError(nRet));
		app_context_destroy(pstOpenAppContext);
		app_control_send_terminate_request(app_control_handler);
		app_control_destroy(app_control_handler);
		return 1;
	}
	else
	{
		nRet = app_manager_is_running(TEST_APPMANAGERTESTFILE_APPID, &bIsRunning);
		if ( nRet != APP_MANAGER_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] app_manager_is_running error returned = %s\\n", __LINE__, API_NAMESPACE, AppManagerGetError(nRet));
			app_context_destroy(pstOpenAppContext);
			app_control_send_terminate_request(app_control_handler);
			app_control_destroy(app_control_handler);
			return 1;
		}
		if ( !bIsRunning )
		{
			FPRINTF("[Line : %d][%s] app_manager_is_running error returned = App is not running\\n", __LINE__, API_NAMESPACE);
			app_context_destroy(pstOpenAppContext);
			app_control_send_terminate_request(app_control_handler);
			app_control_destroy(app_control_handler);
			return 1;
		}
	}

	nRet = app_context_destroy(pstOpenAppContext);
	if ( nRet != APP_MANAGER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_context_destroy error returned = %s\\n", __LINE__, API_NAMESPACE, AppManagerGetError(nRet));
		app_control_send_terminate_request(app_control_handler);
		app_control_destroy(app_control_handler);
		return 1;
	}

	nRet = app_control_send_terminate_request(app_control_handler);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_send_terminate_request", AppControlGetError(nRet), app_control_destroy(app_control_handler));

	nRet = app_control_destroy(app_control_handler);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To get the application shared resource path for the given application ID
/**
* @testcase 			ITc_app_manager_get_shared_resource_path_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To get the shared resource path for corresponding application information for the given application ID
* @scenario				Get the application information\n
*						Destroy the application information
* @apicovered			app_manager_get_shared_resource_path
* @passcase				If app_manager_get_shared_resource_path returns success
* @failcase				If app_manager_get_shared_resource_path fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_get_shared_resource_path_p(void)
{
	START_TEST;

	char *pszSharePath = NULL;

	int nRet = app_manager_get_shared_resource_path((const char *)TEST_TESTAPPLICATION_APPID, &pszSharePath);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_shared_resource_path", AppManagerGetError(nRet));
	CHECK_VALUE_STRING(pszSharePath, "app_manager_get_shared_resource_path");	
	FREE_MEMORY(pszSharePath);	
	return 0;
}

//& type: auto
//& purpose: To get the application shared trusted path for the given application ID
/**
* @testcase 			ITc_app_manager_get_shared_trusted_path_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To get the shared resource path for corresponding application information for the given application ID
* @scenario				Get the application information\n
*						Destroy the application information
* @apicovered			app_manager_get_shared_trusted_path
* @passcase				If app_manager_get_shared_trusted_path returns success
* @failcase				If app_manager_get_shared_trusted_path fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_get_shared_trusted_path_p(void)
{
	START_TEST;

	char *pszSharePath = NULL;

	// Target API
	int nRet = app_manager_get_shared_trusted_path((const char *)TEST_TESTAPPLICATION_APPID, &pszSharePath);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_shared_trusted_path", AppManagerGetError(nRet));
	CHECK_VALUE_STRING(pszSharePath, "app_manager_get_shared_trusted_path");	
	FREE_MEMORY(pszSharePath);	
	return 0;
}

//& type: auto
//& purpose: To get the application shared trusted path for the given application ID
/**
* @testcase 			ITc_app_manager_get_shared_data_path_p
* @deprecated			Deprecated API since 3.0
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To get the shared resource path for corresponding application information for the given application ID
* @scenario				Get the application information\n
*						Destroy the application information
* @apicovered			app_manager_get_shared_data_path
* @passcase				If app_manager_get_shared_data_path returns success
* @failcase				If app_manager_get_shared_data_path fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_get_shared_data_path_p(void)
{
	START_TEST;

	char *pszSharePath = NULL;

	// Target API
	int nRet = app_manager_get_shared_data_path((const char *)TEST_TESTAPPLICATION_APPID, &pszSharePath);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_shared_data_path", AppManagerGetError(nRet));
	CHECK_VALUE_STRING(pszSharePath, "app_manager_get_shared_data_path");	
	FREE_MEMORY(pszSharePath);	
	return 0;
}

//& type: auto
//& purpose: To get the application shared trusted path for the given application ID
/**
* @testcase 			ITc_app_manager_get_external_shared_data_path_p
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			To get the external shared data path for corresponding application information for the given application ID
* @scenario				Get the application information\n
*						Destroy the application information
* @apicovered			app_manager_get_external_shared_data_path
* @passcase				If app_manager_get_external_shared_data_path returns success
* @failcase				If app_manager_get_external_shared_data_path fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_get_external_shared_data_path_p(void)
{
	START_TEST;

	char *pszSharePath = NULL;

	int nRet = app_manager_get_external_shared_data_path((const char *)TEST_TESTAPPLICATION_APPID, &pszSharePath);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_external_shared_data_path", AppManagerGetError(nRet));	
	CHECK_VALUE_STRING(pszSharePath, "app_manager_get_external_shared_data_path");	
	FREE_MEMORY(pszSharePath);	
	return 0;
}

//& type: auto
//& purpose: To create and destroy the app manager event handle
/**
* @testcase 			ITc_app_manager_event_create_destroy_p
* @author				SRID(shilpa.j)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Create the app manager event handle
* @scenario				Create the app manager event handle
*						Destroy the event handle
* @apicovered			app_manager_event_create,app_manager_event_destroy
* @passcase				If app_manager_event_create  and app_manager_event_destroy returns success
* @failcase				If app_manager_event_create or app_manager_event_destroy fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_event_create_destroy_p(void)
{
	START_TEST;

	app_manager_event_h hEventHandle = NULL;

	int nRet = app_manager_event_create(&hEventHandle);	
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_event_create", AppManagerGetError(nRet));	
	CHECK_HANDLE(hEventHandle, "app_manager_event_create");
	
	nRet = app_manager_event_destroy(hEventHandle);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_event_destroy", AppManagerGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose: Sets the event to handle to listen
/**
* @testcase 			ITc_app_manager_event_set_status_p
* @author				SRID(shilpa.j)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Sets the event to handle to listen
* @scenario				Create the app manager event handle
						Sets the event to handle to listen
*						Destroy the event handle
* @apicovered			app_manager_event_create,app_manager_event_set_status
* @passcase				If app_manager_event_set_status returns success
* @failcase				If app_manager_event_set_status fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_event_set_status_p(void)
{
	START_TEST;

	app_manager_event_h hEventHandle = NULL;	
	int nEnumStartCount;
	
	int nStatusOption[] = {
			APP_MANAGER_EVENT_STATUS_TYPE_ALL ,
			APP_MANAGER_EVENT_STATUS_TYPE_ENABLE,
			APP_MANAGER_EVENT_STATUS_TYPE_DISABLE,
		};
		int nStatusOptionCount = sizeof(nStatusOption) / sizeof(nStatusOption[0]);

	int nRet = app_manager_event_create(&hEventHandle);	
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_event_create", AppManagerGetError(nRet));	
	CHECK_HANDLE(hEventHandle, "app_manager_event_create");
	
	for(nEnumStartCount = 0 ; nEnumStartCount < nStatusOptionCount ; nEnumStartCount++ )
	{	
		FPRINTF("Status = [%s]  \\n" ,AppManagerGetStaus(nStatusOption[nEnumStartCount]));
		//Target API
		nRet = app_manager_event_set_status(hEventHandle,nStatusOption[nEnumStartCount]);				
		PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_manager_event_set_status", AppManagerGetError(nRet), app_manager_event_destroy(hEventHandle));
	}

	
	nRet = app_manager_event_destroy(hEventHandle);
	PRINT_RESULT_NORETURN(APP_MANAGER_ERROR_NONE, nRet, "app_manager_event_destroy", AppManagerGetError(nRet));	
	
	return 0;
}


//& type: auto
//& purpose: Sets the event to handle to listen
/**
* @testcase 			ITc_app_manager_set_unset_event_cb_p
* @author				SRID(shilpa.j)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Sets the event to handle to listen
* @scenario				Create the app manager event handle
						Sets the event to handle to listen
*						Destroy the event handle
* @apicovered			app_manager_event_create,app_manager_event_set_status,app_manager_unset_event_cb
* @passcase				If app_manager_set_event_cb or app_manager_unset_event_cb returns success
* @failcase				If app_manager_unset_event_cb or app_manager_set_event_cb fails
* @precondition			app manager instance should be created
* @postcondition		app should be closed and app manager instance should be destroyed
*/
int ITc_app_manager_set_unset_event_cb_p(void)
{
	START_TEST;
	int nTimeoutId = 0;
	app_manager_event_h hEventHandle = NULL;
	g_bAppManagerCallback = false;

	int nRet = app_manager_event_create(&hEventHandle);	
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_event_create", AppManagerGetError(nRet));	
	CHECK_HANDLE(hEventHandle, "app_manager_event_create");
	//Target API
	nRet = app_manager_set_event_cb(hEventHandle,AppManagerEventCallback,NULL);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_manager_set_event_cb", AppManagerGetError(nRet), app_manager_event_destroy(hEventHandle));
	

	//Callback hit is not checked as there is no way or such APIs to check invocation of callback registered  - discussed with developer
	
	/*RUN_POLLING_LOOP;
	if ( g_bAppManagerCallback == false )
	{
		FPRINTF("[Line : %d][%s] app_manager_set_event_cb failed, error returned = Callback Not Invoked\\n", __LINE__, API_NAMESPACE);
		app_manager_event_destroy(hEventHandle);
		return 1;
	}*/
	//Target API
	nRet = app_manager_unset_event_cb(hEventHandle);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_manager_unset_event_cb", AppManagerGetError(nRet), app_manager_event_destroy(hEventHandle));
	
	nRet = app_manager_event_destroy(hEventHandle);
	PRINT_RESULT_NORETURN(APP_MANAGER_ERROR_NONE, nRet, "app_manager_event_destroy", AppManagerGetError(nRet));	
	
	return 0;
}

/**
  @testcase			ITc_app_info_is_support_ambient_p
* @author			SRID(mohit.m)
* @reviewer			SRID(shobhit.v)
* @type			auto
* @since_tizen			5.5
* @description		`	checks whether the application supports ambient mode.
* @scenario			Create the app info handle and get the application information in this handle \N
*				checks whether handle supports ambient mode \n
*				Destroy the handle and check for Pass/Fail
* @apicovered			app_manager_get_app_info, app_info_is_support_ambient,app_info_destroy
* @passcase			app_info_is_support_ambient returns 0
* @failcase			app_info_is_support_ambient returns 1
* @precondition			app info handle should be created
* @postcondition		app info handle should be destroyed
*/
int ITc_app_info_is_support_ambient_p(void)
{
	START_TEST;

	app_info_h hAppInfo = NULL;
	bool bIsSupported = false;
	int nRet = APP_MANAGER_ERROR_NONE;

	nRet = app_manager_get_app_info((const char *)TEST_TESTAPPLICATION_APPID, &hAppInfo);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_info", AppManagerGetError(nRet));
	CHECK_HANDLE(hAppInfo, "app_manager_get_app_info");

	//Target API
	nRet = app_info_is_support_ambient(hAppInfo, &bIsSupported);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_is_support_ambient", AppManagerGetError(nRet),app_info_destroy(hAppInfo));

	nRet = app_info_destroy(hAppInfo);
	PRINT_RESULT_NORETURN(APP_MANAGER_ERROR_NONE, nRet, "app_info_destroy", AppManagerGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets the list of resource controls for a particular application.
/**
  @testcase			ITc_app_info_foreach_res_control_p
* @author			SRID(nibha.sharma)
* @reviewer			SRID(shobhit.v)
* @type			auto
* @since_tizen			6.5
* @description		`	Gets the list of resource controls for a particular application.
* @scenario			Gets the list of resource controls for a particular application.
* @apicovered			app_info_foreach_res_control
* @passcase			app_info_foreach_res_control returns 0
* @failcase			app_info_foreach_res_control returns 1
* @precondition			launch resource control applciation
* @postcondition		NA
*/
int ITc_app_info_foreach_res_control_p(void)
{
	START_TEST;

	app_info_h pstAppInfo = NULL;
	app_control_h hAppControlHandle = NULL;
	g_bResCallBackIsHit = false;
	bool bIsRunning = false;
	int nRet = APP_MANAGER_ERROR_NONE;

	nRet = app_manager_is_running(TEST_HELLOWORLD_APPID, &bIsRunning);
	PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_manager_is_running", AppManagerGetError(nRet));
	if (bIsRunning != true) {
		nRet = app_control_create(&hAppControlHandle);
		PRINT_RESULT(APP_MANAGER_ERROR_NONE, nRet, "app_control_create", AppManagerGetError(nRet));
		CHECK_HANDLE(hAppControlHandle, "app_control_create");

		nRet = app_control_set_app_id(hAppControlHandle, TEST_HELLOWORLD_APPID);
		PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_control_set_app_id", AppManagerGetError(nRet),app_control_destroy(hAppControlHandle));

		nRet = app_control_send_launch_request(hAppControlHandle, NULL, NULL);
		PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_control_send_launch_request", AppManagerGetError(nRet),app_control_destroy(hAppControlHandle));
	}
	nRet = app_manager_get_app_info(TEST_HELLOWORLD_APPID, &pstAppInfo);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_manager_get_app_info", AppManagerGetError(nRet),app_control_destroy(hAppControlHandle));
	CHECK_HANDLE_CLEANUP(pstAppInfo, "app_manager_get_app_info",app_control_destroy(hAppControlHandle));

	nRet = app_info_foreach_res_control(pstAppInfo, ResourceControlCB, NULL);
	PRINT_RESULT_CLEANUP(APP_MANAGER_ERROR_NONE, nRet, "app_info_foreach_res_control", AppManagerGetError(nRet),app_info_destroy(pstAppInfo);app_control_destroy(hAppControlHandle));
	PRINT_RESULT_CLEANUP(true, g_bResCallBackIsHit, "app_info_foreach_res_control", "CallBack Not Invoked",app_info_destroy(pstAppInfo);app_control_destroy(hAppControlHandle));

	nRet = app_info_destroy(pstAppInfo);
	PRINT_RESULT_NORETURN(APP_MANAGER_ERROR_NONE, nRet, "app_info_destroy", AppManagerGetError(nRet));

	nRet = app_control_send_terminate_request(g_app_control_handler);
	PRINT_RESULT_NORETURN(APP_MANAGER_ERROR_NONE, nRet, "app_control_send_terminate_request", AppManagerGetError(nRet));

	nRet = app_control_destroy(hAppControlHandle);
	PRINT_RESULT_NORETURN(APP_MANAGER_ERROR_NONE, nRet, "app_control_destroy", AppManagerGetError(nRet));

	return 0;
}
/** @} */
/** @} */
