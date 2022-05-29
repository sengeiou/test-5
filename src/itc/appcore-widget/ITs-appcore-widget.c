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
#include <glib.h>
#include "ITs-appcore-widget-common.h"

/** @addtogroup itc-appcore-widget
*  @ingroup itc
*  @{
*/

bool g_bAppcoreWidgetFeatureSupported = false;

//& set: AppcoreWidget

/**
 * @function 		ITs_appcore_widget_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_appcore_widget_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Appcore_Widget_p\\n", __LINE__, API_NAMESPACE);
#endif
	g_timeout_add(4000, handler, NULL);

	IS_FEATURE_SUPPORTED(APPCORE_WIDGET_FEATURE, g_bAppcoreWidgetFeatureSupported, API_NAMESPACE);

	return;
}

/**
 * @function 		ITs_appcore_widget_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_appcore_widget_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Appcore_Widget_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup itc-appcore-widget-testcases
*  @brief 		Integration testcases for module appcore-widget
*  @ingroup 	itc-appcore-widget
*  @{
*/

int _instance_create_callback(widget_context_h context, bundle *content, int w, int h, void *user_data)
{
	// Target API
	int nRet = widget_app_exit();

	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_app_exit", AppcoreWidgetGetError(nRet));

	if ((user_data == NULL) || (strcmp(user_data, TESTSTRING) != 0) )
	{
		FPRINTF("[Line : %d][appcore_widget_ITC] Invalid data passed to callback\\n", __LINE__);
		return -1;
	}

	return WIDGET_ERROR_NONE;
}


int _instance_destroy_callback(widget_context_h context, widget_app_destroy_type_e reason, bundle *content, void *user_data)
{
	return 0;
}

int _instance_pause_callback(widget_context_h context, void *user_data)
{
	return 0;
}

int _instance_resume_callback(widget_context_h context, void *user_data)
{
	return 0;
}


int _instance_update_callback(widget_context_h context, bundle *content, int force, void *user_data)
{
	return 0;
}


int _instance_resize_callback(widget_context_h context, int w, int h, void *user_data)
{
	return 0;
}


widget_class_h _app_create_callback(void *user_data)
{
		widget_instance_lifecycle_callback_s ops = {
		.create = _instance_create_callback,
		.destroy = _instance_destroy_callback,
		.pause = _instance_pause_callback,
		.resume = _instance_resume_callback,
		.update = _instance_update_callback,
		.resize = _instance_resize_callback,
	};

	return widget_app_class_create(ops, user_data);
}

//& purpose: Runs the main loop of the application until widget_app_exit() is called
//& type: auto
/**
* @testcase 				ITc_appcore_widget_widget_app_main_exit_p
* @since_tizen				2.3.1
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Runs the main loop of the application until widget_app_exit() is called
* @scenario					Run the main loop of the application.\n
*							Exit the main loop of the application
* @apicovered				widget_app_main, widget_app_exit
* @passcase					When widget_app_main and widget_app_exit is successful
* @failcase					If target API widget_app_main or widget_app_exit or any supporting API fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_appcore_widget_widget_app_main_exit_p(void)
{
	START_TEST;

	widget_app_lifecycle_callback_s callback = {0,};
	int argc = 1;
	char **argv;
	argv = malloc(1 * sizeof(char *));
	if ( NULL == argv )
	{
		FPRINTF("[Line : %d][%s] Memory Allocation Failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	argv[0] = "widget_app";

	callback.create = _app_create_callback;
	callback.terminate = widget_app_terminate_callback;

	// Target API
	int nRet = widget_app_main(argc, argv, &callback, NULL);
	FREE_MEMORY(argv);
	CHECK_SUPPORT(WIDGET_ERROR_NOT_SUPPORTED, nRet, "widget_app_main", AppcoreWidgetGetError(nRet));

	return 0;
}

//& purpose: Adds and removes the system event handler
//& type: auto
/**
* @testcase 				ITc_appcore_widget_widget_app_add_remove_event_handler_p
* @since_tizen				2.3.1
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Adds and removes the system event handler
* @scenario					Add the system event handler.\n
*							Remove the registered event handler
* @apicovered				widget_app_add_event_handler, widget_app_remove_event_handler
* @passcase					When widget_app_add_event_handler and widget_app_remove_event_handler is successful
* @failcase					If target API widget_app_add_event_handler or widget_app_remove_event_handler or any supporting API fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_appcore_widget_widget_app_add_remove_event_handler_p(void)
{
	START_TEST;
	
	app_event_handler_h handler;

	// Target API
	int nRet = widget_app_add_event_handler(&handler, APP_EVENT_LOW_MEMORY, (app_event_cb) event_callback, NULL);
	CHECK_SUPPORT(WIDGET_ERROR_NOT_SUPPORTED, nRet, "widget_app_add_event_handler", AppcoreWidgetGetError(nRet));
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_app_add_event_handler", AppcoreWidgetGetError(nRet));

	// Target API
	nRet = widget_app_remove_event_handler(handler);
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_app_remove_event_handler", AppcoreWidgetGetError(nRet));
	
	return 0;
}

//& purpose: Makes a class for widget instances
//& type: auto
/**
* @testcase 				ITc_appcore_widget_widget_app_class_create_p
* @since_tizen				2.3.1
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Makes a class for widget instances
* @scenario					Make a class for widget instances
* @apicovered				widget_app_class_create
* @passcase					When widget_app_class_create is successful
* @failcase					If target API widget_app_class_create or any supporting API fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_appcore_widget_widget_app_class_create_p(void)
{
	START_TEST;
	
	widget_instance_lifecycle_callback_s ops = {
		.create = widget_instance_create_callback,
		.destroy = widget_instance_destroy_callback,
		.pause = widget_instance_pause_callback,
		.resume = widget_instance_resume_callback,
		.update = widget_instance_update_callback,
		.resize = widget_instance_resize_callback,
	};

	void *user_data = TESTSTRING;

	// Target API
	widget_class_h ch = widget_app_class_create(ops, user_data);
	
	int nRet = get_last_result();
	CHECK_SUPPORT(WIDGET_ERROR_NOT_SUPPORTED, nRet, "widget_app_class_create", AppcoreWidgetGetError(nRet));
	
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_app_add_event_handler", AppcoreWidgetGetError(nRet));
	CHECK_HANDLE(ch, "widget_app_class_create");
	
	return 0;
}

//& purpose: Retrieves all widget contexts in this application
//& type: auto
/**
* @testcase 				ITc_appcore_widget_widget_app_foreach_context_p
* @since_tizen				2.3.1
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Retrieves all widget contexts in this application
* @scenario					Retrieve all widget contexts in this application
* @apicovered				widget_app_foreach_context
* @passcase					When widget_app_foreach_context is successful
* @failcase					If target API widget_app_foreach_context or any supporting API fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_appcore_widget_widget_app_foreach_context_p(void)
{
	START_TEST;
	
	g_nContextCount = 0;
	
	// Target API
	int nRet = widget_app_foreach_context(widget_context_callback, NULL);
	CHECK_SUPPORT(WIDGET_ERROR_NOT_SUPPORTED, nRet, "widget_app_foreach_context", AppcoreWidgetGetError(nRet));
	
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_app_foreach_context", AppcoreWidgetGetError(nRet));
	// widget instance cannot be created in TC so g_nContextCount is always zero.

	return 0;
}

//& purpose: Adds an additional widget class for multi-class of widget instantiation
//& type: auto
/**
* @testcase 				ITc_appcore_widget_widget_app_class_add_p
* @since_tizen				3.0
* @author					SRID(nibha.sharma)
* @reviewer					SRID(parshant.v)
* @type 					auto
* @description				Adds an additional widget class for multi-class of widget instantiation
* @scenario					Adds an additional widget class for multi-class of widget instantiation
* @apicovered				widget_app_class_add
* @passcase					When widget_app_class_add is successful
* @failcase					If target API widget_app_class_add or any supporting API fails
* @precondition				widget_app_class_create
* @postcondition			NA
*/
int ITc_appcore_widget_widget_app_class_add_p(void)
{
	START_TEST;
	
	widget_instance_lifecycle_callback_s ops = {
		.create = widget_instance_create_callback,
		.destroy = widget_instance_destroy_callback,
		.pause = widget_instance_pause_callback,
		.resume = widget_instance_resume_callback,
		.update = widget_instance_update_callback,
		.resize = widget_instance_resize_callback,
	};

	void *user_data = TESTSTRING;
	const char *class_id = CLASSID;

	widget_class_h hWidgetClassHandle = widget_app_class_create(ops, user_data);
	int nRet = get_last_result();
	CHECK_SUPPORT(WIDGET_ERROR_NOT_SUPPORTED, nRet, "widget_app_class_create", AppcoreWidgetGetError(nRet));
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_app_class_create", AppcoreWidgetGetError(nRet));
	CHECK_HANDLE(hWidgetClassHandle, "widget_app_class_create");
	
	// Target API
	widget_class_h hMultiClassHandle = widget_app_class_add(hWidgetClassHandle,class_id,ops,user_data);
	nRet = get_last_result();
	CHECK_SUPPORT(WIDGET_ERROR_NOT_SUPPORTED, nRet, "widget_app_class_add", AppcoreWidgetGetError(nRet));
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_app_class_add", AppcoreWidgetGetError(nRet));
	CHECK_HANDLE(hMultiClassHandle, "widget_app_class_add");
	
	return 0;
}


/** @} */ //end of itc-appcore-widget-testcases
/** @} */ //end of itc-appcore-widget
