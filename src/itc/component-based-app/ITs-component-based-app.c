//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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

#include "ITs-component-based-app-common.h"

/** @addtogroup itc-component-based-app
*  @ingroup itc
*  @{
*/

/****************************************************Callback Start****************************************************/
/**
* @function 		FrameComponentCreateCB
* @description	 	Callback Function
* @parameters		component_h hComponent, void *pszData
* @return 		N/A
*/
static Evas_Object* FrameComponentCreateCB(component_h hComponent, void *pszData)
{
	FPRINTF("[Line : %d][%s] FrameComponentCreateCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
	return NULL;
}

/**
* @function 		FrameComponentStartCB
* @description	 	Callback Function
* @parameters		component_h hComponent, app_control_h hAppControl, bool bIsRestarted, void *pszData
* @return 		N/A
*/
static void FrameComponentStartCB(component_h hComponent, app_control_h hAppControl, bool bIsRestarted, void *pszData)
{
	FPRINTF("[Line : %d][%s] FrameComponentStartCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		FrameComponentResumeCB
* @description	 	Callback Function
* @parameters		component_h hComponent, void *pszData
* @return 		N/A
*/
static void FrameComponentResumeCB(component_h hComponent, void *pszData)
{
	FPRINTF("[Line : %d][%s] FrameComponentResumeCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		FrameComponentPauseCB
* @description	 	Callback Function
* @parameters		component_h hComponent, void *pszData
* @return 		N/A
*/
static void FrameComponentPauseCB(component_h hComponent, void *pszData)
{
	FPRINTF("[Line : %d][%s] FrameComponentPauseCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		FrameComponentStopCB
* @description	 	Callback Function
* @parameters		component_h hComponent, void *pszData
* @return 		N/A
*/
static void FrameComponentStopCB(component_h hComponent, void *pszData)
{
	FPRINTF("[Line : %d][%s] FrameComponentStopCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		FrameComponentDestroyCB
* @description	 	Callback Function
* @parameters		component_h hComponent, void *pszData
* @return 		N/A
*/
static void FrameComponentDestroyCB(component_h hComponent, void *pszData)
{
	FPRINTF("[Line : %d][%s] FrameComponentDestroyCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		FrameComponentRestoreContentCB
* @description	 	Callback Function
* @parameters		component_h hComponent, bundle *bundleContent, void *pszData
* @return 		N/A
*/
static void FrameComponentRestoreContentCB(component_h hComponent, bundle *bundleContent, void *pszData)
{
	FPRINTF("[Line : %d][%s] FrameComponentRestoreContentCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		FrameComponentSaveContentCB
* @description	 	Callback Function
* @parameters		component_h hComponent, bundle *bundleContent, void *pszData
* @return 		N/A
*/
static void FrameComponentSaveContentCB(component_h hComponent, bundle *bundleContent, void *pszData)
{
	FPRINTF("[Line : %d][%s] FrameComponentSaveContentCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		FrameComponentActionCB
* @description	 	Callback Function
* @parameters		component_h hComponent, const char *pszAction, app_control_h hAppControl, void *pszData
* @return 		N/A
*/
static void FrameComponentActionCB(component_h hComponent, const char *pszAction, app_control_h hAppControl, void *pszData)
{
	FPRINTF("[Line : %d][%s] FrameComponentActionCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		FrameComponentDeviceOrientationChangedCB
* @description	 	Callback Function
* @parameters		component_h hComponent, component_device_orientation_e eOrientation, void *pszData
* @return 		N/A
*/
static void FrameComponentDeviceOrientationChangedCB(component_h hComponent, component_device_orientation_e eOrientation, void *pszData)
{
	FPRINTF("[Line : %d][%s] FrameComponentDeviceOrientationChangedCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		FrameComponentLanguageChangedCB
* @description	 	Callback Function
* @parameters		component_h hComponent, const char *pszLanguage, void *pszData
* @return 		N/A
*/
static void FrameComponentLanguageChangedCB(component_h hComponent, const char *pszLanguage, void *pszData)
{
	FPRINTF("[Line : %d][%s] FrameComponentLanguageChangedCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		FrameComponentRegionFormatChangedCB
* @description	 	Callback Function
* @parameters		component_h hComponent, const char *pszRegion, void *pszData
* @return 		N/A
*/
static void FrameComponentRegionFormatChangedCB(component_h hComponent, const char *pszRegion, void *pszData)
{
	FPRINTF("[Line : %d][%s] FrameComponentRegionFormatChangedCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		FrameComponentLowBatteryCB
* @description	 	Callback Function
* @parameters		component_h hComponent, component_low_battery_status_e eLowBattStatus, void *pszData
* @return 		N/A
*/
static void FrameComponentLowBatteryCB(component_h hComponent, component_low_battery_status_e eLowBattStatus, void *pszData)
{
	FPRINTF("[Line : %d][%s] FrameComponentLowBatteryCBCallback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		FrameComponentLowMemoryCB
* @description	 	Callback Function
* @parameters		component_h hComponent, component_low_memory_status_e eLowMemtatus, void *pszData
* @return 		N/A
*/
static void FrameComponentLowMemoryCB(component_h hComponent, component_low_memory_status_e eLowMemtatus, void *pszData)
{
	FPRINTF("[Line : %d][%s] FrameComponentLowMemoryCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		FrameComponentSuspendedStateChangedCB
* @description	 	Callback Function
* @parameters		component_h hComponent, component_suspended_state_e eSuspendedState, void *pszData
* @return 		N/A
*/
static void FrameComponentSuspendedStateChangedCB(component_h hComponent, component_suspended_state_e eSuspendedState, void *pszData)
{
	FPRINTF("[Line : %d][%s] FrameComponentSuspendedStateChangedCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ServiceComponentCreateCB
* @description	 	Callback Function
* @parameters		component_h hComponent, void *pszData
* @return 		N/A
*/
static bool ServiceComponentCreateCB(component_h hComponent, void *pszData)
{
	FPRINTF("[Line : %d][%s] ServiceComponentCreateCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
	return false;
}

/**
* @function 		ServiceComponentStartCommandCB
* @description	 	Callback Function
* @parameters		component_h hComponent, app_control_h hAppControl, bool restarted, void *pszData
* @return 		N/A
*/
static void ServiceComponentStartCommandCB(component_h hComponent, app_control_h hAppControl, bool restarted, void *pszData)
{
	FPRINTF("[Line : %d][%s] ServiceComponentStartCommandCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ServiceComponentDestroyCB
* @description	 	Callback Function
* @parameters		component_h hComponent, void *pszData
* @return 		N/A
*/
static void ServiceComponentDestroyCB(component_h hComponent, void *pszData)
{
	FPRINTF("[Line : %d][%s] ServiceComponentDestroyCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ServiceComponentSaveContentCB
* @description	 	Callback Function
* @parameters		component_h hComponent, bundle *bundleContent, void *pszData
* @return 		N/A
*/
static void  ServiceComponentSaveContentCB(component_h hComponent, bundle *bundleContent, void *pszData)
{
	FPRINTF("[Line : %d][%s] ServiceComponentSaveContentCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ServiceComponentActionCB
* @description	 	Callback Function
* @parameters		component_h hComponent, const char *pszAction, app_control_h hAppControl, void *pszData
* @return 		N/A
*/
static void ServiceComponentActionCB(component_h hComponent, const char *pszAction, app_control_h hAppControl, void *pszData)
{
	FPRINTF("[Line : %d][%s] ServiceComponentActionCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ServiceComponentDeviceOrientationChangedCB
* @description	 	Callback Function
* @parameters		component_h hComponent, component_device_orientation_e eOrientation, void *pszData
* @return 		N/A
*/
static void ServiceComponentDeviceOrientationChangedCB(component_h hComponent, component_device_orientation_e eOrientation, void *pszData)
{
	FPRINTF("[Line : %d][%s] ServiceComponentDeviceOrientationChangedCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ServiceComponentLanguageChangedCB
* @description	 	Callback Function
* @parameters		component_h hComponent, const char *pszLanguage, void *pszData
* @return 		N/A
*/
static void ServiceComponentLanguageChangedCB(component_h hComponent, const char *pszLanguage, void *pszData)
{
	FPRINTF("[Line : %d][%s] ServiceComponentLanguageChangedCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ServiceComponentRegionFormatChangedCB
* @description	 	Callback Function
* @parameters		component_h hComponent, const char *pszRegion, void *pszData
* @return 		N/A
*/
static void ServiceComponentRegionFormatChangedCB(component_h hComponent, const char *pszRegion, void *pszData)
{
	FPRINTF("[Line : %d][%s] ServiceComponentRegionFormatChangedCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ServiceComponentLowBatteryCB
* @description	 	Callback Function
* @parameters		component_h hComponent, component_low_battery_status_e eLowBattStatus, void *pszData
* @return 		N/A
*/
static void ServiceComponentLowBatteryCB(component_h hComponent, component_low_battery_status_e eLowBattStatus, void *pszData)
{
	FPRINTF("[Line : %d][%s] ServiceComponentLowBatteryCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ServiceComponentLowMemoryCB
* @description	 	Callback Function
* @parameters		component_h hComponent, component_low_memory_status_e eLowMemtatus, void *pszData
* @return 		N/A
*/
static void ServiceComponentLowMemoryCB(component_h hComponent, component_low_memory_status_e eLowMemtatus, void *pszData)
{
	FPRINTF("[Line : %d][%s] ServiceComponentLowMemoryCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ServiceComponentSuspendedStateChangedCB
* @description	 	Callback Function
* @parameters		component_h hComponent, component_suspended_state_e eSuspendedState, void *pszData
* @return 		N/A
*/
static void ServiceComponentSuspendedStateChangedCB(component_h hComponent, component_suspended_state_e eSuspendedState, void *pszData)
{
	FPRINTF("[Line : %d][%s] ServiceComponentSuspendedStateChangedCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
}
/*****************************************************Callback End*****************************************************/

/**
* @function		ITs_componenet_based_app_startup
* @description		Called before each test, checks pre-installed apps
* @parameter		NA
* @return		NA
*/
void ITs_componenet_based_app_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_componenet_based_app_startup\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(2, TEST_COMPONENTBASED_APPID, TEST_HELLOWORLD_APPID);
}

/**
* @function		ITs_componenet_based_app_cleanup
* @description		Called after each test
* @parameter		NA
* @return		NA
*/
void ITs_componenet_based_app_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_componenet_based_app_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
}


/** @addtogroup		itc-component-based-app-testcases
*  @brief		Integration testcases for module itc-component-based-app
*  @ingroup		itc-component-based-app
*  @{
*/

/**
* @testcase				ITc_component_based_app_main_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Runs the main loop of the application until component_based_app_exit() is called.
* @scenario				Launch component based app using helper synchronous function AppControlSend()
*					with extra data and check for result and check for Pass/Fail.
* @apicovered				component_based_app_main
* @passcase				If API return result is APP_CONTROL_RESULT_SUCCEEDED
* @failcase				If API fails
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_component_based_app_main_p(void)
{
	START_TEST;

	int nRet = APP_CONTROL_RESULT_FAILED;

	nRet = AppControlSend(TEST_COMPONENTBASED_APPID, TEST_SERVICE_COMP_ID, "ITc_component_based_app_main");
	PRINT_RESULT(APP_CONTROL_RESULT_SUCCEEDED, nRet, "component_based_app_main", AppControlGetResult(nRet));

	return 0;
}

/**
* @testcase				ITc_component_based_app_exit_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Exits the main loop of the application.
* @scenario				Launch component based app using helper asynchronous function AppControlSendAsync()
*					with extra data and check for result and check for Pass/Fail.
* @apicovered				component_based_app_exit
* @passcase				If API returns APP_CONTROL_ERROR_NONE
* @failcase				If API fails
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_component_based_app_exit_p(void)
{
	START_TEST;

	int nRet = APP_CONTROL_RESULT_SUCCEEDED;
	bool bIsRunning = true;

	nRet =  AppControlSendAsync(TEST_COMPONENTBASED_APPID, TEST_SERVICE_COMP_ID, "ITc_component_based_app_exit");
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "component_based_app_exit", AppControlGetError(nRet));
	sleep(1);

	nRet = component_manager_is_running(TEST_SERVICE_COMP_ID, &bIsRunning);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_manager_is_running", CompManagerAppGetError(nRet));
	PRINT_RESULT(false, bIsRunning, "component_manager_is_running", "App suppose to be closed");

	return 0;
}

/**
* @testcase				ITc_component_based_app_add_frame_component_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Adds a new frame component to comp_class.
* @scenario				Register frame_component_lifecycle_callback_s callbacks
*					asynchronously and check whether app is exited or not
*					call API, check handle and check for error and check for Pass/Fail.
* @apicovered				component_based_app_add_frame_component
* @passcase				If API returns APP_ERROR_NONE
* @failcase				If API fails
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_component_based_app_add_frame_component_p(void)
{
	START_TEST;

	int nRet = APP_ERROR_NONE;
	component_class_h hCompClass = NULL;

	frame_component_lifecycle_callback_s FrameCompCB = {
		.create = FrameComponentCreateCB,
		.start = FrameComponentStartCB,
		.resume = FrameComponentResumeCB,
		.pause = FrameComponentPauseCB,
		.stop = FrameComponentStopCB,
		.destroy = FrameComponentDestroyCB,
		.restore_content = FrameComponentRestoreContentCB,
		.save_content = FrameComponentSaveContentCB,
		.action = FrameComponentActionCB,
		.device_orientation_changed = FrameComponentDeviceOrientationChangedCB,
		.language_changed = FrameComponentLanguageChangedCB,
		.region_format_changed = FrameComponentRegionFormatChangedCB,
		.low_battery = FrameComponentLowBatteryCB,
		.low_memory = FrameComponentLowMemoryCB,
		.suspended_state_changed = FrameComponentSuspendedStateChangedCB
	};

	hCompClass = component_based_app_add_frame_component(hCompClass, TEST_FRAME_COMP_ID, &FrameCompCB, NULL);
	nRet = get_last_result();
	PRINT_RESULT(APP_ERROR_NONE, nRet, "component_based_app_add_frame_component", AppGetError(nRet));
	CHECK_HANDLE(hCompClass, "component_based_app_add_frame_component");

	return 0;
}

/**
* @testcase				ITc_component_based_app_add_service_component_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Adds a service component to comp_class.
* @scenario				Register service_component_lifecycle_callback_s callbacks
*					asynchronously and check whether app is exited or not
*					call API, check handle and check for error and check for Pass/Fail.
* @apicovered				component_based_app_add_service_component
* @passcase				If API returns APP_ERROR_NONE
* @failcase				If API fails
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_component_based_app_add_service_component_p(void)
{
	START_TEST;

	int nRet = APP_ERROR_NONE;
	component_class_h hCompClass = NULL;

	service_component_lifecycle_callback_s ServiceCompCB = {
		.create = ServiceComponentCreateCB,
		.start_command = ServiceComponentStartCommandCB,
		.destroy = ServiceComponentDestroyCB,
		.save_content = ServiceComponentSaveContentCB,
		.action = ServiceComponentActionCB,
		.device_orientation_changed = ServiceComponentDeviceOrientationChangedCB,
		.language_changed = ServiceComponentLanguageChangedCB,
		.region_format_changed = ServiceComponentRegionFormatChangedCB,
		.low_battery = ServiceComponentLowBatteryCB,
		.low_memory = ServiceComponentLowMemoryCB,
		.suspended_state_changed = ServiceComponentSuspendedStateChangedCB
	};

	hCompClass = component_based_app_add_service_component(hCompClass, TEST_SERVICE_COMP_ID, &ServiceCompCB, NULL);
	nRet = get_last_result();
	PRINT_RESULT(APP_ERROR_NONE, nRet, "component_based_app_add_service_component", AppGetError(nRet));
	CHECK_HANDLE(hCompClass, "component_based_app_add_service_component");

	return 0;
}

/**
* @testcase				ITc_component_get_id_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Gets the ID of the component.
* @scenario				Launch component based app using helper synchronous function AppControlSend()
*					with extra data and check for result and check for Pass/Fail.
* @apicovered				component_get_id
* @passcase				If API return result is APP_CONTROL_RESULT_SUCCEEDED
* @failcase				If API fails
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_component_get_id_p(void)
{
	START_TEST;

	int nRet = APP_CONTROL_RESULT_FAILED;

	nRet =  AppControlSend(TEST_COMPONENTBASED_APPID, TEST_SERVICE_COMP_ID, "ITc_component_get_id");
	PRINT_RESULT(APP_CONTROL_RESULT_SUCCEEDED, nRet, "component_get_id", AppControlGetResult(nRet));

	return 0;
}

/**
* @testcase				ITc_component_get_instance_id_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Gets the instance ID of the component.
* @scenario				Launch component based app using helper synchronous function AppControlSend()
*					with extra data and check for result and check for Pass/Fail.
* @apicovered				component_get_instance_id
* @passcase				If API return result is APP_CONTROL_RESULT_SUCCEEDED
* @failcase				If API fails
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_component_get_instance_id_p(void)
{
	START_TEST;

	int nRet = APP_CONTROL_RESULT_FAILED;

	nRet =  AppControlSend(TEST_COMPONENTBASED_APPID, TEST_SERVICE_COMP_ID, "ITc_component_get_instance_id");
	PRINT_RESULT(APP_CONTROL_RESULT_SUCCEEDED, nRet, "component_get_instance_id", AppControlGetResult(nRet));

	return 0;
}

/**
* @testcase				ITc_component_register_action_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Registers the app_control action.
* @scenario				Launch component based app using helper synchronous function AppControlSend()
*					with extra data and check for result and check for Pass/Fail.
* @apicovered				component_register_action
* @passcase				If API return result is APP_CONTROL_RESULT_SUCCEEDED
* @failcase				If API fails
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_component_register_action_p(void)
{
	START_TEST;

	int nRet = APP_CONTROL_RESULT_FAILED;

	nRet =  AppControlSend(TEST_COMPONENTBASED_APPID, TEST_SERVICE_COMP_ID, "ITc_component_register_action");
	PRINT_RESULT(APP_CONTROL_RESULT_SUCCEEDED, nRet, "component_register_action", AppControlGetResult(nRet));

	return 0;
}

/**
* @testcase				ITc_component_deregister_action_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Deregisters the registered app_control action.
* @scenario				Launch component based app using helper synchronous function AppControlSend()
*					with extra data and check for result and check for Pass/Fail.
* @apicovered				component_deregister_action
* @passcase				If API return result is APP_CONTROL_RESULT_SUCCEEDED
* @failcase				If API fails
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_component_deregister_action_p(void)
{
	START_TEST;

	int nRet = APP_CONTROL_RESULT_FAILED;

	nRet =  AppControlSend(TEST_COMPONENTBASED_APPID, TEST_SERVICE_COMP_ID, "ITc_component_deregister_action");
	PRINT_RESULT(APP_CONTROL_RESULT_SUCCEEDED, nRet, "component_deregister_action", AppControlGetResult(nRet));

	return 0;
}

/**
* @testcase				ITc_component_send_launch_request_sync_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Sends the launch request synchronously.
* @scenario				Launch component based app using helper synchronous function AppControlSend()
*					with extra data and check for result and check for Pass/Fail.
* @apicovered				component_send_launch_request_sync
* @passcase				If API return result is APP_CONTROL_RESULT_SUCCEEDED
* @failcase				If API fails
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_component_send_launch_request_sync_p(void)
{
	START_TEST;

	int nRet = APP_CONTROL_RESULT_FAILED;

	nRet = AppControlSend(TEST_COMPONENTBASED_APPID, TEST_SERVICE_COMP_ID, "ITc_component_launch_req_sync");
	PRINT_RESULT(APP_CONTROL_RESULT_SUCCEEDED, nRet, "component_send_launch_request_sync", AppControlGetResult(nRet));

	return 0;
}

/**
* @testcase				ITc_component_send_launch_request_async_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Sends the launch request synchronously.
* @scenario				Launch component based app using helper synchronous function AppControlSend()
*					with extra data and check for result and check for Pass/Fail.
* @apicovered				component_send_launch_request_async
* @passcase				If API return result is APP_CONTROL_RESULT_SUCCEEDED
* @failcase				If API fails
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_component_send_launch_request_async_p(void)
{
	START_TEST;

	int nRet = APP_CONTROL_RESULT_FAILED;

	nRet = AppControlSend(TEST_COMPONENTBASED_APPID, TEST_SERVICE_COMP_ID, "ITc_component_launch_req_async");
	PRINT_RESULT(APP_CONTROL_RESULT_SUCCEEDED, nRet, "component_send_launch_request_async", AppControlGetResult(nRet));

	return 0;
}

/**
* @testcase				ITc_frame_component_get_display_status_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Gets the display status.
* @scenario				Check display feature, Launch component based app using helper
*					asynchronous function AppControlSendAsyn() with extra data
*					and check for result and check for Pass/Fail.
* @apicovered				frame_component_get_display_status
* @passcase				If API returns APP_CONTROL_ERROR_NONE
* @failcase				If API fails
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_frame_component_get_display_status_p(void)
{
	START_TEST;

	int nRet = APP_CONTROL_ERROR_NONE;
	bool bScreenFeature = false;

	/* For IOT headless */
	bScreenFeature = TCTCheckSystemInfoFeatureSupported(TIZEN_FEATURE_SCREEN, API_NAMESPACE);
	if (!bScreenFeature)
	{
		FPRINTF("[Line : %d][%s] %s Feature not spported .\\n", __LINE__, API_NAMESPACE, TIZEN_FEATURE_SCREEN);
		return 0;
	}

	nRet = AppControlSendAsync(TEST_COMPONENTBASED_APPID, TEST_FRAME_COMP_ID, "ITc_frame_component_get_display_status");
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "frame_component_get_display_status", AppControlGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_frame_component_get_window_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Gets an Evas object for the frame component.
* @scenario				Check display feature, Launch component based app using helper
*					synchronous function AppControlSend() with extra data
*					and check for result and check for Pass/Fail.
* @apicovered				frame_component_get_window
* @passcase				If API return result is APP_CONTROL_RESULT_SUCCEEDED
* @failcase				If API fails
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_frame_component_get_window_p(void)
{
	START_TEST;

	int nRet = APP_CONTROL_ERROR_NONE;
	bool bScreenFeature = false;

	/* For IOT headless */
	bScreenFeature = TCTCheckSystemInfoFeatureSupported(TIZEN_FEATURE_SCREEN, API_NAMESPACE);
	if (!bScreenFeature)
	{
		FPRINTF("[Line : %d][%s] %s Feature not spported .\\n", __LINE__, API_NAMESPACE, TIZEN_FEATURE_SCREEN);
		return 0;
	}

	nRet =  AppControlSend(TEST_COMPONENTBASED_APPID, TEST_SERVICE_COMP_ID, "ITc_frame_component_get_window");
	PRINT_RESULT(APP_CONTROL_RESULT_SUCCEEDED, nRet, "frame_component_get_window", AppControlGetResult(nRet));

	return 0;
}

/**
* @testcase				ITc_component_finish_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type				auto
* @description				Finishes the component instance.
* @scenario				Launch component based app using helper synchronous function AppControlSend()
*					with extra data and check for result and check for Pass/Fail.
* @apicovered				component_finish
* @passcase				If API return result is APP_CONTROL_RESULT_SUCCEEDED
* @failcase				If API fails
* @precondition			N/A
* @postcondition			N/A
* */
int ITc_component_finish_p(void)
{
	START_TEST;

	int nRet = APP_CONTROL_RESULT_FAILED;

	nRet =  AppControlSend(TEST_COMPONENTBASED_APPID, TEST_SERVICE_COMP_ID, "ITc_component_finish");
	PRINT_RESULT(APP_CONTROL_RESULT_SUCCEEDED, nRet, "component_finish", AppControlGetResult(nRet));

	return 0;
}

/** @} */
/** @} */
