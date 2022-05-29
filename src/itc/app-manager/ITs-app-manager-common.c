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
* @function 		AppManagerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* AppManagerGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case APP_MANAGER_ERROR_NONE:					szErrorVal = "APP_MANAGER_ERROR_NONE";						break;
	case APP_MANAGER_ERROR_INVALID_PARAMETER:		szErrorVal = "APP_MANAGER_ERROR_INVALID_PARAMETE";			break;
	case APP_MANAGER_ERROR_OUT_OF_MEMORY:			szErrorVal = "APP_MANAGER_ERROR_OUT_OF_MEMORY";				break;
	case APP_MANAGER_ERROR_IO_ERROR:				szErrorVal = "APP_MANAGER_ERROR_IO_ERROR";					break;
	case APP_MANAGER_ERROR_NO_SUCH_APP:				szErrorVal = "APP_MANAGER_ERROR_NO_SUCH_APP";				break;
	case APP_MANAGER_ERROR_DB_FAILED:				szErrorVal = "APP_MANAGER_ERROR_DB_FAILED";					break;
	case APP_MANAGER_ERROR_INVALID_PACKAGE:			szErrorVal = "APP_MANAGER_ERROR_INVALID_PACKAGE";			break;
	case APP_MANAGER_ERROR_APP_NO_RUNNING:			szErrorVal = "APP_MANAGER_ERROR_APP_NO_RUNNING";			break;
	case APP_MANAGER_ERROR_REQUEST_FAILED:			szErrorVal = "APP_MANAGER_ERROR_REQUEST_FAILED";			break;
	case APP_MANAGER_ERROR_PERMISSION_DENIED:		szErrorVal = "APP_MANAGER_ERROR_PERMISSION_DENIED";			break;
	default:										szErrorVal = "Unknown Error";								break;
	}

	return szErrorVal;
}

/**
* @function 		AppControlGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* AppControlGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case APP_CONTROL_ERROR_NONE:					szErrorVal = "APP_CONTROL_ERROR_NONE";						break;
	case APP_CONTROL_ERROR_INVALID_PARAMETER:		szErrorVal = "APP_CONTROL_ERROR_INVALID_PARAMETER";			break;
	case APP_CONTROL_ERROR_OUT_OF_MEMORY:			szErrorVal = "APP_CONTROL_ERROR_OUT_OF_MEMORY";				break;
	case APP_CONTROL_ERROR_APP_NOT_FOUND:			szErrorVal = "APP_CONTROL_ERROR_APP_NOT_FOUND";				break;
	case APP_CONTROL_ERROR_KEY_NOT_FOUND:			szErrorVal = "APP_CONTROL_ERROR_KEY_NOT_FOUND";				break;
	case APP_CONTROL_ERROR_KEY_REJECTED:			szErrorVal = "APP_CONTROL_ERROR_KEY_REJECTED";				break;
	case APP_CONTROL_ERROR_INVALID_DATA_TYPE:		szErrorVal = "APP_CONTROL_ERROR_INVALID_DATA_TYPE";			break;
	case APP_CONTROL_ERROR_LAUNCH_REJECTED:			szErrorVal = "APP_CONTROL_ERROR_LAUNCH_REJECTED";			break;
	case APP_CONTROL_ERROR_PERMISSION_DENIED:		szErrorVal = "APP_CONTROL_ERROR_PERMISSION_DENIED";			break;
	case APP_CONTROL_ERROR_LAUNCH_FAILED:			szErrorVal = "APP_CONTROL_ERROR_LAUNCH_FAILED";				break;
	case APP_CONTROL_ERROR_TIMED_OUT:				szErrorVal = "APP_CONTROL_ERROR_TIMED_OUT";					break;
	default:										szErrorVal = "Unknown Error";								break;
	}

	return szErrorVal;
}

/**
* @function 		AppManagerGetStaus
* @description	 	Maps enums to string values
* @parameter		nStatus : enum returned
* @return 			enum string
*/
char* AppManagerGetStaus(int nStatus)
{
	char *szStatusVal = NULL;
	switch ( nStatus )
	{
	case APP_MANAGER_EVENT_STATUS_TYPE_ALL:			szStatusVal = "APP_MANAGER_EVENT_STATUS_TYPE_ALL";			break;
	case APP_MANAGER_EVENT_STATUS_TYPE_ENABLE:		szStatusVal = "APP_MANAGER_EVENT_STATUS_TYPE_ENABLE";		break;
	case APP_MANAGER_EVENT_STATUS_TYPE_DISABLE:		szStatusVal = "APP_MANAGER_EVENT_STATUS_TYPE_DISABLE";		break;
	
	}
	return szStatusVal;
}

/**
* @function		AppManagerGetAppComponent
* @description		Maps enums to string values
* @parameter		app_info_app_component_type_e : enum returned
* @return		enum string
*/
char* AppManagerGetAppComponent(app_info_app_component_type_e nStatus)
{
	char *szStatusVal = "Unknown Value";
	switch ( nStatus )
	{
	case APP_INFO_APP_COMPONENT_TYPE_UI_APP:		szStatusVal = "APP_INFO_APP_COMPONENT_TYPE_UI_APP";		break;
	case APP_INFO_APP_COMPONENT_TYPE_SERVICE_APP:		szStatusVal = "APP_INFO_APP_COMPONENT_TYPE_SERVICE_APP";		break;
	case APP_INFO_APP_COMPONENT_TYPE_WIDGET_APP:		szStatusVal = "APP_INFO_APP_COMPONENT_TYPE_WIDGET_APP";		break;
	case APP_INFO_APP_COMPONENT_TYPE_WATCH_APP:		szStatusVal = "APP_INFO_APP_COMPONENT_TYPE_WATCH_APP";		break;
	case APP_INFO_APP_COMPONENT_TYPE_COMPONENT_BASED_APP:		szStatusVal = "APP_INFO_APP_COMPONENT_TYPE_COMPONENT_BASED_APP";		break;
	}
	return szStatusVal;
} 

/**
* @function 		AppManagerCallbackTimeout
* @description	 	callback function to terminate g_main loop
* @parameter		data : user data sent to callback
* @return 			NA
*/
gboolean AppManagerCallbackTimeout(gpointer data)
{
	GMainLoop* pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
		g_main_loop_unref(pMainLoop);
		pMainLoop = NULL;
	}
	return false;
}

/**
* @function 		AppManagerAppContextChangeCallback
* @description	 	callback function for capturing context event change callbacks
* @parameter		app_context_h app_context, app_context_event_e event, void *user_data
* @return 			NA
*/
void AppManagerAppContextChangeCallback(app_context_h app_context, app_context_event_e event, void *user_data)
{
#if DEGUG
	FPRINTF("[Line : %d][%s] Callback AppManagerAppContextChangeCallback is called\\n", __LINE__, API_NAMESPACE);
#endif

	g_bAppManagerCallback = true;

	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		AppManagerCreateEventLoop
* @description	 	Create Event Loop to support callbacks
* @parameter		pArg : handle to g_main loop
* @return 			NA
*/
void* AppManagerCreateEventLoop(void* pArg)
{
	g_pMainLoop = g_main_loop_new(NULL, FALSE);

	int nTimeoutId = g_timeout_add(GMAINTIMEOUT, AppManagerCallbackTimeout, g_pMainLoop);
	g_main_loop_run(g_pMainLoop);//blocking call
	g_source_remove(nTimeoutId);
	return NULL;
}

/**
* @function 		AppManagerAppContextEventCallback
* @description	 	callback function for capturing context event callbacks
* @parameter		app_context : app context handle ,event : event captured ,user_data : user data sent to callback
* @return 			NA
*/
void AppManagerAppContextEventCallback(app_context_h app_context, app_context_event_e event, void *user_data)
{
#if DEGUG
	FPRINTF("[Line : %d][%s] Callback AppManagerAppContextEventCallback is called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bAppManagerCallback = true;
	if (g_pMainLoop)
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		AppInfoMetaDataFilterForeachCallback
* @description	 	callback function for capturing application filter metadata event callbacks
* @parameter		app_info : application info handle ,user_data : user data sent to callback
* @return 			NA
*/
bool AppInfoMetaDataFilterForeachCallback (app_info_h app_info, void *user_data)
{
#if DEGUG
	FPRINTF("[Line : %d][%s] Callback AppInfoMetaDataFilterForeachCallback is called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bAppManagerCallback = true;
	return g_bAppManagerCallback;
}

/**
* @function 		AppInfoMetaDataCallback
* @description	 	callback function for capturing application metadata event callbacks
* @parameter		metadata_key : metadata key, metadata_value : metadata value associated with key ,user_data : user data sent to callback
* @return 			NA
*/
bool AppInfoMetaDataCallback(const char *metadata_key, const char *metadata_value, void *user_data)
{
#if DEGUG
	FPRINTF("[Line : %d][%s] Callback AppInfoMetaDataCallback is called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bAppManagerCallback = true;
	return g_bAppManagerCallback;
}

/**
* @function 		AppManagerAppContextCallback
* @description	 	callback function to get the application context once for each running application
* @parameter		app_context : app context handle ,user_data : user data sent to callback
* @return 			NA
*/
bool AppManagerAppContextCallback(app_context_h app_context, void *user_data)
{
#if DEGUG
	FPRINTF("[Line : %d][%s] Callback AppManagerAppContextCallback is called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bAppManagerCallback = true;
	return g_bAppManagerCallback;
}
/**
* @function			app_manager_event_callback
* @description		Callback function for app_manager_set_event_cb 
* @parameter	const char * :type, const char *: app_id,app_manager_event_type_e :event_type,app_manager_event_state_e :event_state,
					app_manager_event_h :handle, void *user_data

* @return			NA
*/
bool AppManagerEventCallback(const char *type, const char *app_id,app_manager_event_type_e event_type,app_manager_event_state_e event_state,
		app_manager_event_h handle, void *user_data)
{
	#if DEGUG
	FPRINTF("[Line : %d][%s] Callback AppManagerEventCallback is called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bAppManagerCallback = true;
	return g_bAppManagerCallback;
	
}

/** @} */
