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
#include "ITs-widget_viewer_evas-common.h"

/** @addtogroup itc-widget_viewer_evas
*  @ingroup itc
*  @{
*/

/**
 * @function 		WidgetServiceGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet: error code returned
 * @return 			error string
 */
char* WidgetViewerGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch(nRet)
	{
		case WIDGET_ERROR_INVALID_PARAMETER:		szErrorVal = "WIDGET_ERROR_INVALID_PARAMETER";			break;
		case WIDGET_ERROR_OUT_OF_MEMORY:			szErrorVal = "WIDGET_ERROR_OUT_OF_MEMORY";				break;
		case WIDGET_ERROR_RESOURCE_BUSY:			szErrorVal = "WIDGET_ERROR_RESOURCE_BUSY";				break;
		case WIDGET_ERROR_PERMISSION_DENIED:		szErrorVal = "WIDGET_ERROR_PERMISSION_DENIED";			break;
		case WIDGET_ERROR_CANCELED:					szErrorVal = "WIDGET_ERROR_CANCELED";					break;
		case WIDGET_ERROR_IO_ERROR:					szErrorVal = "WIDGET_ERROR_IO_ERROR";					break;
		case WIDGET_ERROR_TIMED_OUT:				szErrorVal = "WIDGET_ERROR_TIMED_OUT";					break;
		case WIDGET_ERROR_NOT_SUPPORTED:			szErrorVal = "WIDGET_ERROR_NOT_SUPPORTED";				break;
		case WIDGET_ERROR_FILE_NO_SPACE_ON_DEVICE:	szErrorVal = "WIDGET_ERROR_FILE_NO_SPACE_ON_DEVICE";	break;
		case WIDGET_ERROR_FAULT:					szErrorVal = "WIDGET_ERROR_FAULT";						break;
		case WIDGET_ERROR_ALREADY_EXIST:			szErrorVal = "WIDGET_ERROR_ALREADY_EXIST";				break;
		case WIDGET_ERROR_ALREADY_STARTED:			szErrorVal = "WIDGET_ERROR_ALREADY_STARTED";			break;
		case WIDGET_ERROR_NOT_EXIST:				szErrorVal = "WIDGET_ERROR_NOT_EXIST";					break;
		case WIDGET_ERROR_DISABLED:					szErrorVal = "WIDGET_ERROR_DISABLED";					break;
		case WIDGET_ERROR_MAX_EXCEEDED: 			szErrorVal = "WIDGET_ERROR_MAX_EXCEEDED";					break;
		default:									szErrorVal = "Unknown Error";							break;
	}
	return szErrorVal;
}

/**
 * @function 		WidgetServiceTimeout
 * @description	 	Called if some callback is not invoked for a particular timeout
 * @parameter		gpointer data
 * @return 			gboolean
 */
Eina_Bool WidgetViewerTimeout(void *data)
{
	FPRINTF("[Line: %d][%s] Callback Timeout\\n", __LINE__, API_NAMESPACE);
	elm_exit();
	return ECORE_CALLBACK_DONE;
}

/**
 * @function 		WidgetViewerGetWidgetId
 * @description	 	widget_viewer_evas_get_widget_id api is called in this function.
 * @parameter		Evas_Object *widget
 * @return 			NA
 */
void WidgetViewerGetWidgetId(Evas_Object *widget)
{
	FPRINTF("[Line: %d][%s] WidgetViewerGetWidgetId is invoked\\n", __LINE__, API_NAMESPACE);
	g_pWidgetID = widget_viewer_evas_get_widget_id(widget);
}

/**
 * @function 		WidgetViewerFeedMouseUpEvent
 * @description	 	widget_viewer_evas_feed_mouse_up_event api is called in this function.
 * @parameter		Evas_Object *widget
 * @return 			NA
 */
void WidgetViewerFeedMouseUpEvent(Evas_Object *widget)
{
	FPRINTF("[Line: %d][%s] WidgetViewerFeedMouseUpEvent is invoked\\n", __LINE__, API_NAMESPACE);
	Evas *e;

	e = evas_object_evas_get(widget);
	evas_event_feed_mouse_down(e, 1, EVAS_BUTTON_NONE, 0, NULL);

	g_nRet = widget_viewer_evas_feed_mouse_up_event(widget);
}

/**
 * @function 		WidgetViewerTcFreeze
 * @description	 	widget_viewer_evas_freeze_visibility api is called in this function.
 * @parameter		Evas_Object *widget
 * @return 			NA
 */
void WidgetViewerTcFreeze(Evas_Object *widget)
{
	FPRINTF("[Line: %d][%s] WidgetViewerTcFreeze is invoked\\n", __LINE__, API_NAMESPACE);
	g_nRet = widget_viewer_evas_freeze_visibility(widget, WIDGET_VISIBILITY_STATUS_SHOW_FIXED);
}

/**
 * @function 		WidgetViewerGetTitleString
 * @description	 	widget_viewer_evas_get_title_string api is called in this function.
 * @parameter		Evas_Object *widget
 * @return 			NA
 */
void WidgetViewerGetTitleString(Evas_Object *widget)
{
	FPRINTF("[Line: %d][%s] WidgetViewerGetTitleString is invoked\\n", __LINE__, API_NAMESPACE);
	g_pTitleString = widget_viewer_evas_get_title_string(widget);
}

/**
 * @function 		WidgetViewerPause
 * @description	 	widget_viewer_evas_pause_widget api is called in this function.
 * @parameter		Evas_Object *widget
 * @return 			NA
 */
void WidgetViewerPause(Evas_Object *widget)
{
	FPRINTF("[Line: %d][%s] WidgetViewerPause is invoked\\n", __LINE__, API_NAMESPACE);
	g_nRet = widget_viewer_evas_pause_widget(widget);
}

/**
 * @function 		WidgetViewerResume
 * @description	 	widget_viewer_evas_resume_widget api is called in this function.
 * @parameter		Evas_Object *widget
 * @return 			NA
 */
void WidgetViewerResume(Evas_Object *widget)
{
	FPRINTF("[Line: %d][%s] WidgetViewerResume is invoked\\n", __LINE__, API_NAMESPACE);
	g_nRet = widget_viewer_evas_resume_widget(widget);
}

/**
 * @function 		WidgetViewerThaw
 * @description	 	widget_viewer_evas_thaw_visibility api is called in this function.
 * @parameter		Evas_Object *widget
 * @return 			NA
 */
void WidgetViewerThaw(Evas_Object *widget)
{
	FPRINTF("[Line: %d][%s] WidgetViewerThaw is invoked\\n", __LINE__, API_NAMESPACE);
	g_nRet = widget_viewer_evas_thaw_visibility(widget);
}

/**
 * @function 		WidgetViewerGetContent
 * @description	 	widget_viewer_evas_get_content_info api is called in this function.
 * @parameter		Evas_Object *widget
 * @return 			NA
 */
void WidgetViewerGetContent(Evas_Object *widget)
{
	FPRINTF("[Line: %d][%s] WidgetViewerGetContent is invoked\\n", __LINE__, API_NAMESPACE);
	g_pContentString = widget_viewer_evas_get_content_info(widget);
}

/**
 * @function 		WidgetViewerActivate
 * @description	 	widget_viewer_evas_activate_faulted_widget api is called in this function.
 * @parameter		Evas_Object *widget
 * @return 			NA
 */
void WidgetViewerActivate(Evas_Object *widget)
{
	FPRINTF("[Line: %d][%s] WidgetViewerActivate is invoked\\n", __LINE__, API_NAMESPACE);
	widget_viewer_evas_activate_faulted_widget(widget);
	g_nRet = 0;	/* No returns */
}

/**
 * @function 		WidgetViewerAsyncRetCallback
 * @description	 	This function is called from Widget_Create_CB callback. Validates the parameters values.
 * @parameter		test_case_cb cb, widget_evas_event_info *info
 * @return 			1 (true) or 0 (false)
 */
int WidgetViewerAsyncRetCallback(test_case_cb cb, struct widget_evas_event_info *info)
{
	if ( (info == NULL) || (info->error != WIDGET_ERROR_NONE) || (info->widget_app_id == NULL) || (info->event != WIDGET_EVENT_CREATED) )
	{
		FPRINTF("[Line: %d][%s] WidgetViewerAsyncRetCallback failed \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

/** @} */
