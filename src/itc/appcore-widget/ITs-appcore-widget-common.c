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

//Add helper function definitions here

/**
 * @function 		AppcoreWidgetGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
char* AppcoreWidgetGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
		case WIDGET_ERROR_NONE:
			szErrorVal = "WIDGET_ERROR_NONE";
			break;
		case WIDGET_ERROR_INVALID_PARAMETER:
			szErrorVal = "WIDGET_ERROR_INVALID_PARAMETER";
			break;
		case WIDGET_ERROR_FAULT:
			szErrorVal = "WIDGET_ERROR_FAULT";
			break;
		case WIDGET_ERROR_NOT_SUPPORTED:
			szErrorVal = "WIDGET_ERROR_NOT_SUPPORTED";
			break;
		case WIDGET_ERROR_CANCELED:
			szErrorVal = "WIDGET_ERROR_CANCELED";
			break;
		case WIDGET_ERROR_OUT_OF_MEMORY:
			szErrorVal = "WIDGET_ERROR_OUT_OF_MEMORY";
			break;
		default:
			szErrorVal = "Unknown Error";
			break;
	}

	return szErrorVal;
}

/**
* @function 		BundleGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* BundleGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case BUNDLE_ERROR_NONE:
		szErrorVal = "BUNDLE_ERROR_NONE";
		break;
	case BUNDLE_ERROR_OUT_OF_MEMORY:
		szErrorVal = "BUNDLE_ERROR_OUT_OF_MEMORY";
		break;
	case BUNDLE_ERROR_INVALID_PARAMETER:
		szErrorVal = "BUNDLE_ERROR_INVALID_PARAMETER";
		break;
	case BUNDLE_ERROR_KEY_NOT_AVAILABLE:
		szErrorVal = "BUNDLE_ERROR_KEY_NOT_AVAILABLE";
		break;
	case BUNDLE_ERROR_KEY_EXISTS:
		szErrorVal = "BUNDLE_ERROR_KEY_EXISTS";
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
* @parameter[IN]	user_data The user data passed from g_timeout_add
* @return			0
*/
gboolean handler(gpointer user_data)
{
	widget_app_exit();
	return FALSE;
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
* @function			widget_instance_create_callback
* @description		Called when the widget instance starts
* @parameter[IN]	context The context of widget instance
* @parameter[IN]	content The data set for the previous status
* @parameter[IN]	w The pixel value for widget width
* @parameter[IN]	h The pixel value for widget height
* @parameter[IN]	user_data The user data passed from widget_app_class_create function
* @return			WIDGET_ERROR_NONE on success, otherwise an error code on failure
*/
int widget_instance_create_callback(widget_context_h context, bundle *content, int w, int h, void *user_data)
{
	widget_app_exit();
	
	if ((user_data == NULL) || (strcmp(user_data, TESTSTRING) != 0) )
	{
		FPRINTF("[Line : %d][appcore_widget_ITC] Invalid data passed to callback\\n", __LINE__);
		return -1;
	}
	
	return WIDGET_ERROR_NONE;
}

/**
* @function			widget_instance_destroy_callback
* @description		Called before the widget instance is destroyed
* @parameter[IN]	context The context of widget instance
* @parameter[IN]	reason The reason for destruction
* @parameter[IN/OUT] content The data set to save
* @parameter[IN]	user_data The user data passed from widget_app_class_create function
* @return			WIDGET_ERROR_NONE on success, otherwise an error code on failure
*/
int widget_instance_destroy_callback(widget_context_h context, widget_app_destroy_type_e reason, bundle *content, void *user_data)
{
	return 0;
}

/**
* @function			widget_instance_pause_callback
* @description		Called when the widget is invisible
* @parameter[IN]	context The context of widget instance
* @parameter[IN]	user_data The user data passed from widget_app_class_create function
* @return			WIDGET_ERROR_NONE on success, otherwise an error code on failure
*/
int widget_instance_pause_callback(widget_context_h context, void *user_data)
{
	return 0;
}

/**
* @function			widget_instance_resume_callback
* @description		Called when the widget is visible
* @parameter[IN]	context The context of widget instance
* @parameter[IN]	user_data The user data passed from widget_app_class_create function
* @return			WIDGET_ERROR_NONE on success, otherwise an error code on failure
*/
int widget_instance_resume_callback(widget_context_h context, void *user_data)
{
	return 0;
}

/**
* @function			widget_instance_update_callback
* @description		Called when the event for updating widget is received
* @parameter[IN]	context The context of widget instance
* @parameter[IN]	content The data set for updating this widget. It will be provided by requester
*						Requester can use widget_service_trigger_update()
* @parameter[IN]	force Although the widget is paused, if it is TRUE, the widget can be updated
* @parameter[IN]	user_data The user data passed from widget_app_class_create function
* @return			WIDGET_ERROR_NONE on success, otherwise an error code on failure
*/
int widget_instance_update_callback(widget_context_h context, bundle *content, int force, void *user_data)
{
	return 0;
}

/**
* @function			widget_instance_resize_callback
* @description		Called before the widget size is changed
* @parameter[IN]	context The context of widget instance
* @parameter[IN]	w The pixel value for widget width
* @parameter[IN]	h The pixel value for widget height
* @parameter[IN]	user_data The user data passed from widget_app_class_create function
* @return			WIDGET_ERROR_NONE on success, otherwise an error code on failure
*/
int widget_instance_resize_callback(widget_context_h context, int w, int h, void *user_data)
{
	return 0;
}

/**
* @function			widget_app_create_callback
* @description		Called when the application starts
* @parameter[IN]	user_data The user data passed from the callback registration function
* @return			The object of widget class
*/
widget_class_h widget_app_create_callback(void *user_data)
{
		widget_instance_lifecycle_callback_s ops = {
		.create = widget_instance_create_callback,
		.destroy = widget_instance_destroy_callback,
		.pause = widget_instance_pause_callback,
		.resume = widget_instance_resume_callback,
		.update = widget_instance_update_callback,
		.resize = widget_instance_resize_callback,
	};

	return widget_app_class_create(ops, user_data);
}

/**
* @function			widget_app_terminate_callback
* @description		Called when the application's main loop exits
* @parameter[IN]	user_data The user data passed from the callback registration function
* @return			NA
*/
void widget_app_terminate_callback(void *user_data)
{
}

/**
* @function			widget_context_callback
* @description		Called for each widget context
* @parameter[IN]	context The context for widget instance
* @parameter[IN]	data The data for caller
* @return			true to continue with the next iteration of the loop, otherwise false to break out of the loop
*/
bool widget_context_callback(widget_context_h context, void *data)
{
	g_hWidgetContexts[g_nContextCount++] = context;
	if ( g_nContextCount >= MAX_CONTEXT_COUNT )
	{
		return false;
	}
	return true;
}

/** @} */ //end of itc-appcore-widget
