//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	 http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-application-common.h"

/** @addtogroup itc-application
*  @ingroup itc
*  @{
*/
//& set: Application

bool g_bCallBackHit = false;
bool g_bUserDataMismatch = false;

void *g_pUserData = "user_data_1";


/**
* @function 		ITs_application_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_application_startup(void)
{
	g_bCallBackHit = false;
	g_bUserDataMismatch = false;

	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Application_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(2, TEST_HELLOWORLD_APPID, TEST_TESTAPPLICATION_APPID);
	return;
}

/**
* @function 		ITs_application_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_application_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Application_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		ui_app_event_callback
* @description	 	callback function for capturing app event callbacks
* @parameter		event_info : event captured, user_data : user data sent to callback
* @return 			NA
*/
void ui_app_event_callback(app_event_info_h event_info, void* user_data)
{
	g_bCallBackHit = true;
	if(strcmp((char *)user_data,(char *)g_pUserData) != 0)
	{
		g_bUserDataMismatch = true;
	}

	FPRINTF("[Line : %d][%s] app_event_callback triggered\\n", __LINE__, API_NAMESPACE);
	return;
}

/** @addtogroup itc-application-testcases
*  @brief 		Integration testcases for module application
*  @ingroup 	itc-application
*  @{
*/

//& type: auto
//& purpose: Creates and Destroys AppControl.
/**
* @testcase 			ITc_application_ui_app_add_remove_event_handler_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Adds and Removes event handler
* @scenario				Add event handler and check its status
*						Removes event handler
* @apicovered			ui_app_add_event_handler, ui_app_remove_event_handler
* @passcase				When ui_app_add_event_handler and ui_app_remove_event_handler are successful.
* @failcase				If target API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_application_ui_app_add_remove_event_handler_p(void)
{
	START_TEST;
	app_event_handler_h event_handler;

	//Target API
	int nRet = ui_app_add_event_handler(&event_handler, APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_event_callback, NULL);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "ui_app_add_event_handler", AppGetError(nRet));

	// Give some sleep between create and destroy
	usleep(2000);

	//Target API
	nRet = ui_app_remove_event_handler(event_handler);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "ui_app_remove_event_handler", AppGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: gets device orientation
/**
* @testcase 			ITc_application_app_get_device_orientation_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call target API and validate the values.
* @scenario				Call target API\n
*						Validate the value
* @apicovered			app_get_device_orientation
* @passcase				When app_get_device_orientation is successful and returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_get_device_orientation_p(void)
{
	START_TEST;

	//Target API
	app_device_orientation_e orientation = app_get_device_orientation();
	if ( (orientation != APP_DEVICE_ORIENTATION_0) && (orientation != APP_DEVICE_ORIENTATION_90) && (orientation != APP_DEVICE_ORIENTATION_180) && (orientation != APP_DEVICE_ORIENTATION_270) )
	{
		FPRINTF("[Line : %d][%s] app_get_device_orientation returned wrong value = %d\\n", __LINE__, API_NAMESPACE, orientation);
		return 1;
	}

	FPRINTF("[Line : %d][%s] app_get_device_orientation returned value = %d\\n", __LINE__, API_NAMESPACE, orientation);
	return 0;
}

//& type: auto
//& purpose: gets absolute path to application tep resource directory
/**
* @testcase 			ITc_application_app_get_tep_resource_path_p
* @since_tizen			2.4
* @author				SRID(abhishek1.g)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call target API and validate the values.
* @scenario				Call target API\n
*						Validate the value
* @apicovered			app_get_tep_resource_path
* @passcase				When app_get_tep_resource_path is successful and returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_get_tep_resource_path_p(void)
{
	START_TEST;

	//Target API
	char* pPath = app_get_tep_resource_path();
	CHECK_VALUE_STRING(pPath, "app_get_tep_resource_path");
	
	return 0;
}

//& type: auto
//& purpose: Test app_control_enable_app_started_result_event
/**
* @testcase 			ITc_app_control_enable_app_started_result_event_p
* @since_tizen			2.4
* @author				SRID(abhishek1.g)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Test app_control_enable_app_started_result_event
* @scenario				Call Test app_control_enable_app_started_result_event
* @apicovered			app_control_create, app_control_destroy, app_control_set_mime, app_control_enable_app_started_result_event
* @passcase				When app_control_enable_app_started_result_event is successful and return correct value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
int ITc_app_control_enable_app_started_result_event_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	const char *pszMime = "image/jpeg";
	nRet = app_control_set_mime(hAppControl, pszMime);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_mime", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_enable_app_started_result_event(hAppControl);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_enable_app_started_result_event", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

/** @} */
/** @} */
