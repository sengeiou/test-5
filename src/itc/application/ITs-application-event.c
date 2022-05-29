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

bool g_bEventAddHandler = false;
bool g_bCallBackHit_applicationEvent = false;
bool g_bUserDataMismatch_applicationEvent = false;

char *g_pUserDataKey_applicationEvent = "user_data_key1";
void *g_pUserData_applicationEvent = "user_data_1";


/**
* @function 		ITs_application_event_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_application_event_startup(void)
{
	g_bCallBackHit_applicationEvent = false;
	g_bUserDataMismatch_applicationEvent = false;

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
* @function 		ITs_application_event_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_application_event_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Application_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		event_check_trusted_app_event_cb
* @description	 	Handle events of trusted receiver-applications with same key.
* @parameter		event_name, event_data, user_data
* @return 		NA
*/
static void event_check_trusted_app_event_cb(const char *event_name, bundle *event_data, void *user_data)
{
	g_bCallBackHit_applicationEvent = true;
	FPRINTF("[Line : %d][%s] event_check_trusted_app_event_cb invoked \\n", __LINE__, API_NAMESPACE);

	if(strcmp((char *)user_data,(char *)g_pUserData_applicationEvent) != 0)
	{
		g_bUserDataMismatch_applicationEvent = true;
	}

	if (g_pApplicationMainLoop)
	{
		g_main_loop_quit(g_pApplicationMainLoop);
		g_pApplicationMainLoop = NULL;
	}

	return;
}

/**
* @function 		application_event_cb
* @description	 	callback function for event add handler
* @parameter		event_name : interested event name, event_data : data of interested event, user_data : user data set by event_add_event_handler()
* @return 			NA
*/
void application_event_cb(const char *event_name, bundle *event_data, void *user_data)
{
	g_bCallBackHit_applicationEvent = true;
	if(strcmp((char *)user_data,(char *)g_pUserData_applicationEvent) != 0)
	{
		g_bUserDataMismatch_applicationEvent = true;
	}


	g_bEventAddHandler = true;
	FPRINTF("[Line : %d][%s] application_event_cb invoked \\n", __LINE__, API_NAMESPACE);
	if (g_pApplicationMainLoop)
	{
		g_main_loop_quit(g_pApplicationMainLoop);
		g_pApplicationMainLoop = NULL;
	}

	return;
}

//& type: auto
//& purpose: add and remove the registered event handler
/**
* @testcase 			ITc_app_event_add_remove_event_handler_p
* @since_tizen			2.4
* @author				SRID(ajay.kr1)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Adds the event handler for receiving event-data of interested events and removes the registered event handler
* @scenario				Add event handler\n
*						Remove event handler
* @apicovered			event_add_event_handler, event_remove_event_handler
* @passcase				When event_add_event_handler and event_remove_event_handler are successful.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_app_event_add_remove_event_handler_p(void)
{
	START_TEST;

	int nTimeoutId = 0;
	int nRet = EVENT_ERROR_NONE;
	event_handler_h event_handler;
	bundle* pEventData = bundle_create();
	CHECK_HANDLE(pEventData, "bundle_create");

	nRet = bundle_add_str(pEventData, "user_data_key1", "user_data_1");
	PRINT_RESULT_CLEANUP(BUNDLE_ERROR_NONE, nRet, "bundle_add_str", BundleGetError(nRet), bundle_free(pEventData));

	g_bEventAddHandler = false;
 	// Target API
	nRet = event_add_event_handler("event.native.application-itc.user_event", application_event_cb, g_pUserData_applicationEvent, &event_handler);
	PRINT_RESULT_CLEANUP(EVENT_ERROR_NONE, nRet, "event_add_event_handler", EventGetError(nRet), bundle_free(pEventData));
	if(NULL == event_handler)
	{
		FPRINTF("[Line : %d][%s] event_add_event_handler returned NULL event handle\\n", __LINE__, API_NAMESPACE);
		event_remove_event_handler(event_handler);
		bundle_free(pEventData);
		return 1;	
	}

	nRet = event_publish_app_event("event.native.application-itc.user_event", pEventData);
	PRINT_RESULT_CLEANUP(EVENT_ERROR_NONE, nRet, "event_publish_app_event", EventGetError(nRet), event_remove_event_handler(event_handler);bundle_free(pEventData));

	RUN_POLLING_LOOP;

	if (!g_bEventAddHandler)
	{
		FPRINTF("[Line : %d][%s] application_event_cb callback not executed\\n", __LINE__, API_NAMESPACE);
		event_remove_event_handler(event_handler);
		bundle_free(pEventData);
		return 1;
	}

	if(g_bCallBackHit_applicationEvent && g_bUserDataMismatch_applicationEvent)
	{
		FPRINTF("[Line : %d][%s] User data in callback is not same which is passed through caller function.\\n", __LINE__, API_NAMESPACE);
		event_remove_event_handler(event_handler);
		bundle_free(pEventData);
		return 1;
	}

	//Target API
	nRet = event_remove_event_handler(event_handler);
	PRINT_RESULT_CLEANUP(EVENT_ERROR_NONE, nRet, "event_remove_event_handler", EventGetError(nRet), bundle_free(pEventData));

	nRet = bundle_free(pEventData);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRet, "bundle_free", BundleGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Sends the User-Event to receiver applications
/**
* @testcase 			ITc_application_event_publish_app_event_p
* @since_tizen			2.4
* @author				SRID(ajay.kr1)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Sends the User-Event to receiver applications.
* @scenario				Sends the user-event
* @apicovered			event_publish_app_event
* @passcase				When event_publish_app_event is successful.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_application_event_publish_app_event_p(void)
{
 	START_TEST;

	bundle* pEventData = bundle_create();
	CHECK_HANDLE(pEventData, "bundle_create");

	int nRet = bundle_add_str(pEventData, "user_data_key1", "user_data_1");
	PRINT_RESULT_CLEANUP(BUNDLE_ERROR_NONE, nRet, "bundle_add_str", BundleGetError(nRet), bundle_free(pEventData));

	nRet = event_publish_app_event("event.native.application-itc.user_event", pEventData);
 	PRINT_RESULT_CLEANUP(EVENT_ERROR_NONE, nRet, "event_publish_app_event", EventGetError(nRet), bundle_free(pEventData));

	nRet = bundle_free(pEventData);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRet, "bundle_free", BundleGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Sends the User-Event to trusted receiver-applications.
/**
* @testcase 			ITc_application_event_publish_trusted_app_event_p
* @since_tizen			2.4
* @author				SRID(ajay.kr1)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Sends the User-Event to trusted receiver-applications.
* @scenario				Sends the user-event
* @apicovered			event_publish_trusted_app_event
* @passcase				When event_publish_trusted_app_event is successful.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_application_event_publish_trusted_app_event_p(void)
{
 	START_TEST;

	int nTimeoutId = 0;
	event_handler_h event_handler;

	
	int nRet = event_add_event_handler("event.native.application-itc.user_event", event_check_trusted_app_event_cb, g_pUserData_applicationEvent, &event_handler);

	PRINT_RESULT(BUNDLE_ERROR_NONE, nRet, "event_add_event_handler", BundleGetError(nRet));

	bundle* pEventData = bundle_create();
	CHECK_HANDLE(pEventData, "bundle_create");

	nRet = bundle_add_str(pEventData, g_pUserDataKey_applicationEvent, g_pUserData_applicationEvent);
	PRINT_RESULT_CLEANUP(BUNDLE_ERROR_NONE, nRet, "bundle_add_str", BundleGetError(nRet), bundle_free(pEventData));

	nRet = event_publish_trusted_app_event("event.native.application-itc.user_event", pEventData);
 	PRINT_RESULT_CLEANUP(EVENT_ERROR_NONE, nRet, "event_publish_trusted_app_event", EventGetError(nRet), bundle_free(pEventData));
	
	RUN_POLLING_LOOP;

	if(g_bCallBackHit_applicationEvent == false)
	{
		FPRINTF("[Line : %d][%s] event_check_trusted_app_event_cb callback is not invoked.\\n", __LINE__, API_NAMESPACE);
		event_remove_event_handler(event_handler);
		bundle_free(pEventData);
		return 1;
	}

	if(g_bCallBackHit_applicationEvent && g_bUserDataMismatch_applicationEvent)
	{
		FPRINTF("[Line : %d][%s] User data in callback is not same which is passed through caller function.\\n", __LINE__, API_NAMESPACE);
		event_remove_event_handler(event_handler);
		bundle_free(pEventData);
		return 1;
	}

	nRet = bundle_free(pEventData);
	event_remove_event_handler(event_handler);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRet, "bundle_free", BundleGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Sends the User-Event to trusted receiver-applications.
/**
* @testcase 			ITc_application_event_keep_last_event_data_p
* @since_tizen			3.0
* @author				SRID(shekhar1.s)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Keeps last user-event data for receiver applications.
* @scenario				Keeps last user-event data.
* @apicovered			event_keep_last_event_data
* @passcase				When event_keep_last_event_data is successful.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_application_event_keep_last_event_data_p(void)
{
 	START_TEST;

	int nTimeoutId = 0;
	event_handler_h event_handler;

	int nRet = event_keep_last_event_data("event.native.application-itc.user_event");
	PRINT_RESULT(EVENT_ERROR_NONE, nRet, "event_keep_last_event_data", EventGetError(nRet));
	
	bundle* pEventData = bundle_create();
	CHECK_HANDLE(pEventData, "bundle_create");

	nRet = bundle_add_str(pEventData, "user_data_key1", "user_data_1");
	PRINT_RESULT_CLEANUP(BUNDLE_ERROR_NONE, nRet, "bundle_add_str", BundleGetError(nRet), bundle_free(pEventData));

	nRet = event_publish_app_event("event.native.application-itc.user_event", pEventData);
 	PRINT_RESULT_CLEANUP(EVENT_ERROR_NONE, nRet, "event_publish_app_event", EventGetError(nRet), bundle_free(pEventData));
	
	nRet = event_add_event_handler("event.native.application-itc.user_event", application_event_cb, g_pUserData_applicationEvent, &event_handler);
	PRINT_RESULT_CLEANUP(EVENT_ERROR_NONE, nRet, "event_add_event_handler", EventGetError(nRet), bundle_free(pEventData));
	if(NULL == event_handler)
	{
		FPRINTF("[Line : %d][%s] event_add_event_handler returned NULL event handle\\n", __LINE__, API_NAMESPACE);
		event_remove_event_handler(event_handler);
		bundle_free(pEventData);
		return 1;	
	}

	RUN_POLLING_LOOP;

	if (!g_bEventAddHandler)
	{
		FPRINTF("[Line : %d][%s] application_event_cb callback not executed\\n", __LINE__, API_NAMESPACE);
		event_remove_event_handler(event_handler);
		bundle_free(pEventData);
		return 1;
	}

	nRet = bundle_free(pEventData);
	PRINT_RESULT_NORETURN(BUNDLE_ERROR_NONE, nRet, "bundle_free", BundleGetError(nRet));

	

	return 0;
}
/** @} */
/** @} */
