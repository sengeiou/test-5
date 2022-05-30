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
#include "ITs-appcore-agent-common.h"

/** @addtogroup itc-appcore-agent
*  @ingroup itc
*  @{
*/
//& set: AppcoreAgent

static int main_loop_flag = 0;

static bool service_app_exit_cb(void * user_data)
{
	service_app_exit();

	return false;
}

/**
* @function 		ServiceAppCreate
* @description	 	callback for service app create
* @parameter		user_data : user data send to callback
* @return 			true
*/
static bool ServiceAppCreate(void *user_data)
{
	main_loop_flag = 1;

	g_idle_add(service_app_exit_cb, NULL);

	return true;
}

/**
* @function 		ServiceAppTerminate
* @description	 	callback for service app terminate
* @parameter		user_data: user data send to callback
* @return 			NA
*/
static void ServiceAppTerminate(void *user_data)
{
	main_loop_flag = 0;
}

/**
* @function 		AppEventHandlerCb
* @description	 	callback for app event handle
* @parameter		event_info: event info, user_data: user data send to callback
* @return 			NA
*/
static void AppEventHandlerCb(app_event_info_h event_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside Callback AppEventHandlerCb\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ITs_appcore_agent_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_appcore_agent_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Appcore_Agent_p\\n", __LINE__, API_NAMESPACE);
#endif

	return;
}


/** @function 		ITs_appcore_agent_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_appcore_agent_cleanup(void)
{
	alarm(0);

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Appcore_Agent_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup itc-appcore-agent-testcases
*  @brief 		Integration testcases for module appcore-agent
*  @ingroup 	itc-appcore-agent
*  @{
*/


//& purpose: To check the main entry point of Tizen service application and exit the application
//& type : auto
/**
* @testcase 				ITc_appcore_agent_service_app_main_exit_p
* @since_tizen				2.3
* @author            		SRID(a.pandia1)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				To check the main entry point of Tizen service application and exit the application
* @scenario					Call API service_app_main to get into main entry point of Tizen service application\n
*							Call API service_app_exit to exit from Tizen service application\n
* @apicovered				service_app_main
* @passcase					When API returns APP_ERROR_NONE
* @failcase					When API does not return APP_ERROR_NONE
* @precondition				None
* @postcondition			None
*/
int ITc_appcore_agent_service_app_main_exit_p(void)
{
	START_TEST;

	int nRetVal = 0;
	service_app_lifecycle_callback_s cbHandle = {0};
	main_loop_flag = 1;

	cbHandle.create = ServiceAppCreate;
	cbHandle.terminate = ServiceAppTerminate;

	nRetVal = service_app_main(g_argc, g_argv, &cbHandle, NULL);
	PRINT_RESULT(APP_ERROR_NONE, nRetVal, "service_app_main", AppcoreAgentGetError(nRetVal));
	
	g_result = 0;
	return 0;
}

//& purpose: To check set/unset system event handler callback function 
//& type : auto
/**
* @testcase 				ITc_appcore_agent_service_app_add_remove_event_handler_p
* @since_tizen				2.3
* @author            		SRID(a.pandia1)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				To check set/unset system event handler callback function
* @scenario					Call API service_app_add_event_handler to add event handler callback function\n
*							Call API service_app_remove_event_handler to add event handler callback function 
* @apicovered				service_app_add_event_handler, service_app_remove_event_handler
* @passcase					When API returns APP_ERROR_NONE
* @failcase					When API does not return APP_ERROR_NONE
* @precondition				None
* @postcondition			None
*/
int ITc_appcore_agent_service_app_add_remove_event_handler_p(void)
{
	START_TEST;

	// Initializing testing variable
	int nRetVal = 0 ,  nEnumLoopCount = 0;

	app_event_handler_h hEvent;
	app_event_type_e eAppEventType = APP_EVENT_LOW_MEMORY;

	int arrAppEventType[] = {
		APP_EVENT_LOW_MEMORY,
		APP_EVENT_LOW_BATTERY};
		// APP_EVENT_LANGUAGE_CHANGED,						/* suggested by developer to be used by UI applications only */
		// APP_EVENT_DEVICE_ORIENTATION_CHANGED,
		// APP_EVENT_REGION_FORMAT_CHANGED};

		int nAppEventTypeIteration = sizeof(arrAppEventType) /sizeof(arrAppEventType[0]) ;

		for ( nEnumLoopCount = 0; nEnumLoopCount < nAppEventTypeIteration; nEnumLoopCount++ )
		{
			eAppEventType = arrAppEventType[nEnumLoopCount];
			nRetVal = service_app_add_event_handler(&hEvent, eAppEventType, AppEventHandlerCb, NULL);
			PRINT_RESULT(APP_ERROR_NONE, nRetVal, "service_app_add_event_handler", AppcoreAgentGetError(nRetVal));

			if ( hEvent == NULL )
			{
				FPRINTF("[Line : %d][%s] service_app_add_event_handler failed, event handler is not filled \\n", __LINE__, API_NAMESPACE);
				return 1;
			}
			
			nRetVal = service_app_remove_event_handler(hEvent);
			PRINT_RESULT(APP_ERROR_NONE, nRetVal, "service_app_remove_event_handler", AppcoreAgentGetError(nRetVal));
		}

		normal_exit(0);
		return 0;
}
/** @} */ //end of itc-appcore-agent-testcases
/** @} */ //end of itc-appcore-agent
