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
#include "ITs-appcore-watch-common.h"

//Add helper function definitions here

/**
 * @function 		AppcoreWatchGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
char* AppcoreWatchGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch (nRet)
	{
		case APP_ERROR_NONE:
			szErrorVal = "APP_ERROR_NONE";
			break;
		case APP_ERROR_INVALID_PARAMETER:
			szErrorVal = "APP_ERROR_INVALID_PARAMETER";
			break;
		case APP_ERROR_INVALID_CONTEXT:
			szErrorVal = "APP_ERROR_INVALID_CONTEXT";
			break;
		case APP_ERROR_ALREADY_RUNNING:
			szErrorVal = "APP_ERROR_ALREADY_RUNNING";
			break;
		case APP_ERROR_OUT_OF_MEMORY:
			szErrorVal = "APP_ERROR_OUT_OF_MEMORY";
			break;
		case APP_ERROR_NOT_SUPPORTED:
			szErrorVal = "APP_ERROR_NOT_SUPPORTED";
			break;
		default:
			szErrorVal = "Unknown Error";
			break;
	}

	return szErrorVal;
}

/**
* @function			handler
* @description		Called when the exit signal is sent
* @parameter[IN]	signal
* @return			NA
*/
void handler(int sig)
{
	watch_app_exit();
}

/**
* @function			event_callback
* @description		Called when a system event is occurred
* @parameter[IN]	event The system event message
* @parameter[IN]	data The user data passed to the callback functions
* @return			NA
*/
void event_callback(void *event, void *data)
{
}

/**
* @function			watch_app_create_callback
* @description		Called when the application starts
* @parameter[IN]	width The width of the window of idle screen that will show the watch UI
* @parameter[IN]	height The height of the window of idle screen that will show the watch UI
* @parameter[IN]	user_data The user data passed from the callback registration function
* @return			true on success, otherwise false
*/
bool watch_app_create_callback(int width, int height, void *user_data)
{
	if (g_pAppcoreWatchMainLoop)
	{
		g_main_loop_quit(g_pAppcoreWatchMainLoop);
		g_main_loop_unref(g_pAppcoreWatchMainLoop);
		g_pAppcoreWatchMainLoop = NULL;
	}
	return true;
}

/**
* @function			watch_app_terminate_callback
* @description		Called when the application's main loop exits
* @parameter[IN]	user_data The user data passed from the callback registration function
* @return			true on success, otherwise false
*/
void watch_app_terminate_callback(void *user_data)
{
}

/**
* @function			watch_app_control_callback
* @description		Called when another application sends a launch request to the application
* @parameter[IN]	app_control The handle to the app_control
* @parameter[IN]	user_data The user data passed from the callback registration function
* @return			true on success, otherwise false
*/
void watch_app_control_callback(app_control_h app_control, void *user_data)
{
}

/**
* @function			watch_app_pause_callback
* @description		Called when the application is completely obscured by another application and becomes invisible
* @parameter[IN]	user_data The user data passed from the callback registration function
* @return			true on success, otherwise false
*/
void watch_app_pause_callback(void *user_data)
{
}

/**
* @function			watch_app_resume_callback
* @description		Called when the application becomes visible
* @parameter[IN]	user_data The user data passed from the callback registration function
* @return			true on success, otherwise false
*/
void watch_app_resume_callback(void *user_data)
{
}

/**
* @function			watch_app_time_tick_callback
* @description		Called at each second. This callback is not called while the app is paused or the device is in ambient mode
* @parameter[IN]	watch_time The watch time handle. watch_time will not be available after returning this callback. It will be freed by the framework.
* @parameter[IN]	user_data The user data to be passed to the callback functions
* @return			true on success, otherwise false
*/
void watch_app_time_tick_callback(watch_time_h watch_time, void *user_data)
{
}

/**
* @function			watch_app_ambient_tick_callback
* @description		Called at each minute when the device in the ambient mode
* @parameter[IN]	watch_time The watch time handle. watch_time will not be available after returning this callback. It will be freed by the framework.
* @parameter[IN]	user_data The user data to be passed to the callback functions
* @return			true on success, otherwise false
*/
void watch_app_ambient_tick_callback(watch_time_h watch_time, void *user_data)
{
}

/**
* @function			watch_app_ambient_changed_callback
* @description		Called when the device enters or exits the ambient mode
* @parameter[IN]	ambient_mode If true the device enters the ambient mode, otherwise false
* @parameter[IN]	user_data The user data to be passed to the callback functions
* @return			true on success, otherwise false
*/
void watch_app_ambient_changed_callback(bool ambient_mode, void *user_data)
{
}

/**
 * @function 		AppcoreWatchTimeout
 * @description	 	Called if some callback is not invoked for a particular AppcoreWatchTimeout
 * @parameter		gpointer data
 * @return 			gboolean
 */ 
gboolean AppcoreWatchTimeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
		g_main_loop_unref(pMainLoop);
		pMainLoop = NULL;
	}
	FPRINTF("[Line : %d][appcore_watch_ITC] Callback AppcoreWatchTimeout\\n", __LINE__);
	return false;
}
