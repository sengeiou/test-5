//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-widget_viewer_evas-common.h"

//& set: Widget_viewer_evas

/** @addtogroup itc-widget_viewer_evas
*  @ingroup itc
*  @{
*/

Evas_Object *g_win = NULL;

bool g_bWidgetCreation = false;
bool g_bWidgetViewerCBFlag = false;
bool g_bSkipExecutionWithPass = false;
bool g_bSkipExecutionWithFail = false;
bool g_bWidgetViewerEvasReadFeatureStatusDone = false;
bool g_bWidgetFeatureSupported = false;
int g_nInstanceId;

/**
 * @brief Callback funtion
 */
static void widget_create_cb(void *data, Evas_Object *obj, void *event_info)
{
	FPRINTF("[Line: %d][%s] widget_create_cb called. \\n", __LINE__, API_NAMESPACE);
	struct widget_evas_event_info *info = event_info;
	test_case_cb cb = data;
	int nRet;

	nRet = WidgetViewerAsyncRetCallback(cb, info);
	if ( !nRet && cb )
	{
		int w;
		int h;
		cb(obj);

		nRet = widget_service_get_size(WIDGET_SIZE_TYPE_4x4, &w, &h);
		if ( nRet == WIDGET_ERROR_NONE )
		{
			evas_object_resize(obj, w, h);
			evas_object_color_set(obj, 255, 255, 255, 255); /* Just for the line-coverage */
			evas_object_hide(obj);
			evas_object_show(obj);
		}
	}

	elm_exit();
}

static int WidgetViewerGetInstanceID(Evas_Object *widget)
{
	FPRINTF("[Line: %d][%s] WidgetViewerGetInstanceID called. \\n", __LINE__, API_NAMESPACE);
        const char *instance_id;

        instance_id = widget_viewer_evas_get_widget_instance_id(widget);
	if( (int) instance_id == 0 )
	{
		FPRINTF("[Line: %d][%s] g_nInstanceId is: %d \\n", __LINE__, API_NAMESPACE,g_nInstanceId);
        	g_nInstanceId = 1;
	}
	else
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_get_widget_instance_id is successfull \\n", __LINE__, API_NAMESPACE);
		FPRINTF("[Line: %d][%s] g_nInstanceId is: %d \\n", __LINE__, API_NAMESPACE,g_nInstanceId);
		g_nInstanceId = 0;
	}

        return 0;
}


/**
 * @function 		ITs_widget_viewer_evas_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_widget_viewer_evas_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	TCT_CheckInstalledApp(1, TEST_SAMPLE_APPID);
	if ( false == g_bWidgetViewerEvasReadFeatureStatusDone )
	{
		g_bWidgetFeatureSupported = TCTCheckSystemInfoFeatureSupported(WIDGET_VIEWER_EVAS_FEATURE, API_NAMESPACE);
		g_bWidgetViewerEvasReadFeatureStatusDone = true;
	}

	elm_init(0, NULL);
	elm_config_accel_preference_set("opengl");
	g_win = elm_win_add(NULL, "ITC WIN", ELM_WIN_BASIC);

	int nRet = widget_viewer_evas_init(g_win);
	if ( !g_bWidgetFeatureSupported )
	{
		if ( nRet == WIDGET_ERROR_NOT_SUPPORTED )
		{
			g_bSkipExecutionWithPass = true;
			return;
		}

		g_bSkipExecutionWithFail = true;
		return;
	}

	if ( nRet != WIDGET_ERROR_NONE )
	{
		g_bWidgetCreation = false;
	}
	else
	{
		g_bWidgetCreation = true;
		FPRINTF("[Line: %d][%s] widget_viewer_evas_init success\\n", __LINE__, API_NAMESPACE);
	}
	return;
}

/**
 * @function 		ITs_widget_viewer_evas_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_widget_viewer_evas_cleanup(void)
{
	if ( g_win )
	{
		evas_object_del(g_win);
	}
	elm_shutdown();

	if ( g_bWidgetCreation == true )
	{
		int nRet;
		nRet = widget_viewer_evas_fini();
		if ( nRet == WIDGET_ERROR_NONE )
		{
			g_bWidgetCreation = false;
			FPRINTF("[Line: %d][%s] widget_viewer_evas_fini success\\n", __LINE__, API_NAMESPACE);
		}
	}
	return;
}

/** @addtogroup itc-widget_viewer_evas-testcases
*  @brief 		Integration testcases for module widget_viewer_evas
*  @ingroup 	itc-widget_viewer_evas
*  @{
*/

//& purpose: widget viewer evas get widget id
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_get_widget_id_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			widget viewer get widget id
* @scenario				get widget id
* @apicovered			widget_viewer_evas_get_widget_id
* @passcase				When widget_viewer_evas_get_widget_id is successful
* @failcase				If target API widget_viewer_evas_get_widget_id fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_get_widget_id_p(void)
{
	START_TEST;

	Evas_Object *widget;
	int w, h;
	int nTimeoutId = 0;

	widget = widget_viewer_evas_add_widget(g_win, TEST_SAMPLE_APPID, NULL, 0.0f);
	if ( widget == NULL )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_add_widget failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_pWidgetID = NULL;
	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, widget_create_cb, WidgetViewerGetWidgetId);

	int ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	if ( ret != WIDGET_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_size failed\\n", __LINE__, API_NAMESPACE);
	}

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT_CB, WidgetViewerTimeout, NULL);
	elm_run();

	if ( g_pWidgetID == NULL )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_get_widget_id failed. \\n", __LINE__, API_NAMESPACE);
		widget_viewer_evas_set_permanent_delete(widget, 1);
		evas_object_del(widget);
		return 1;
	}
	else
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_get_widget_id passed, id is: %s\\n", __LINE__, API_NAMESPACE, g_pWidgetID);
	}

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);
	return 0;
}

//& purpose: widget viewer evas get period
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_get_period_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This function get period
* @scenario				get period
* @apicovered			widget_viewer_evas_get_period
* @passcase				When widget_viewer_evas_get_period is successful
* @failcase				If target API widget_viewer_evas_get_period fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_get_period_p(void)
{
	START_TEST;
	double period = 0.0;

	period = widget_viewer_evas_get_period(g_win);
	FPRINTF("[Line: %d][%s] widget_viewer_evas_get_period = [%f]\\n", __LINE__, API_NAMESPACE, period);
	return 0;
}

//& purpose: widget viewer evas is visibility frozen
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_is_visibility_frozen_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			widget viewer evas is visibility frozen
* @scenario				is visibility frozen
* @apicovered			widget_viewer_evas_is_visibility_frozen
* @passcase				When widget_viewer_evas_is_visibility_frozen is successful
* @failcase				If target API widget_viewer_evas_is_visibility_frozen fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_is_visibility_frozen_p(void)
{
	START_TEST;
	bool bIsVisibilityFrozen = false;

	bIsVisibilityFrozen = widget_viewer_evas_is_visibility_frozen(g_win);

	FPRINTF("[Line: %d][%s] widget_viewer_evas_is_visibility_frozen = [%d]\\n", __LINE__, API_NAMESPACE, bIsVisibilityFrozen);

	return 0;
}


//& purpose: widget viewer evas is widget
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_is_widget_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			widget viewer evas is widget
* @scenario				is widget
* @apicovered			widget_viewer_evas_is_widget
* @passcase				When widget_viewer_evas_is_widget is successful
* @failcase				If target API widget_viewer_evas_is_widget fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_is_widget_p(void)
{
	START_TEST;
	bool bIswidget = false;

	bIswidget = widget_viewer_evas_is_widget(g_win);

	FPRINTF("[Line: %d][%s] widget_viewer_evas_is_widget = [%d]\\n", __LINE__, API_NAMESPACE, bIswidget);

	return 0;
}

//& purpose: widget viewer evas is faulted
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_is_faulted_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			widget viewer evas is faulted
* @scenario				is faulted
* @apicovered			widget_viewer_evas_is_faulted
* @passcase				When widget_viewer_evas_is_faulted is successful
* @failcase				If target API widget_viewer_evas_is_faulted fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_is_faulted_p(void)
{
	START_TEST;
	bool bIsFaulted = false;

	bIsFaulted = widget_viewer_evas_is_faulted(g_win);

	FPRINTF("[Line: %d][%s] widget_viewer_evas_is_faulted = [%d]\\n", __LINE__, API_NAMESPACE, bIsFaulted);
	return 0;
}


//& purpose: widget viewer evas notify resumed status of viewer
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_notify_resumed_status_of_viewer_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			widget viewer evas notify resumed status of viewer
* @scenario				notify resumed status of viewer
* @apicovered			widget_viewer_evas_notify_resumed_status_of_viewer
* @passcase				When widget_viewer_evas_notify_resumed_status_of_viewer is successful
* @failcase				If target API widget_viewer_evas_notify_resumed_status_of_viewer fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_notify_resumed_status_of_viewer_p(void)
{
	START_TEST;
	int nRet;

	nRet = widget_viewer_evas_notify_resumed_status_of_viewer();
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_viewer_evas_notify_resumed_status_of_viewer", WidgetViewerGetError(nRet));

	FPRINTF("[Line: %d][%s] widget_viewer_evas_notify_resumed_status_of_viewer \\n", __LINE__, API_NAMESPACE);
	return 0;
}

//& purpose: widget viewer evas notify paused status of viewer
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_notify_paused_status_of_viewer_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			widget viewer evas notify paused status of viewer
* @scenario				notify paused status of viewer
* @apicovered			widget_viewer_evas_notify_paused_status_of_viewer
* @passcase				When widget_viewer_evas_notify_paused_status_of_viewer is successful
* @failcase				If target API widget_viewer_evas_notify_paused_status_of_viewer fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_notify_paused_status_of_viewer_p(void)
{
	START_TEST;
	int nRet;

	nRet = widget_viewer_evas_notify_paused_status_of_viewer();
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_viewer_evas_notify_paused_status_of_viewer", WidgetViewerGetError(nRet));

	FPRINTF("[Line: %d][%s] widget_viewer_evas_notify_paused_status_of_viewer \\n", __LINE__, API_NAMESPACE);

	return 0;
}

//& purpose: widget viewer evas pause widget
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_pause_widget_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			widget viewer evas pause widget
* @scenario				pause widget
* @apicovered			widget_viewer_evas_pause_widget
* @passcase				When widget_viewer_evas_pause_widget is successful
* @failcase				If target API widget_viewer_evas_pause_widget fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_pause_widget_p(void)
{
	START_TEST;
	Evas_Object *widget;
	int w, h;
	int nTimeoutId = 0;

	widget = widget_viewer_evas_add_widget(g_win, TEST_SAMPLE_APPID, NULL, 0.0f);
	if ( widget == NULL )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_add_widget failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_nRet = -1;
	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, widget_create_cb, WidgetViewerPause);

	int ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	if ( ret != WIDGET_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_size failed\\n", __LINE__, API_NAMESPACE);
	}

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT_CB, WidgetViewerTimeout, NULL);
	elm_run();

	if ( g_nRet != 0 )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_pause_widget failed. \\n", __LINE__, API_NAMESPACE);
		widget_viewer_evas_set_permanent_delete(widget, 1);
		evas_object_del(widget);
		return 1;
	}
	else
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_pause_widget passed\\n", __LINE__, API_NAMESPACE);
	}

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);
	return 0;
}


//& purpose: widget viewer evas resume widget
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_resume_widget_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			widget viewer evas resume widget
* @scenario				resume widget
* @apicovered			widget_viewer_evas_resume_widget
* @passcase				When widget_viewer_evas_resume_widget is successful
* @failcase				If target API widget_viewer_evas_resume_widget fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_resume_widget_p(void)
{
	START_TEST;
	Evas_Object *widget;
	int w, h;
	int nTimeoutId = 0;

	widget = widget_viewer_evas_add_widget(g_win, TEST_SAMPLE_APPID, NULL, 0.0f);
	if ( widget == NULL )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_add_widget failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_nRet = -1;
	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, widget_create_cb, WidgetViewerResume);

	int ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	if ( ret != WIDGET_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_size failed\\n", __LINE__, API_NAMESPACE);
	}

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT_CB, WidgetViewerTimeout, NULL);
	elm_run();

	if ( (g_nRet != WIDGET_ERROR_ALREADY_EXIST) && (g_nRet != WIDGET_ERROR_NONE) )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_resume_widget failed. \\n", __LINE__, API_NAMESPACE);
		widget_viewer_evas_set_permanent_delete(widget, 1);
		evas_object_del(widget);
		return 1;
	}
	else
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_resume_widget passed.\\n", __LINE__, API_NAMESPACE);
	}

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);
	return 0;
}

//& purpose: widget viewer evas feed mouse up event
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_feed_mouse_up_event_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			widget viewer evas feed mouse up event
* @scenario				feed mouse up event
* @apicovered			widget_viewer_evas_feed_mouse_up_event
* @passcase				When widget_viewer_evas_feed_mouse_up_event is successful
* @failcase				If target API widget_viewer_evas_feed_mouse_up_event fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_feed_mouse_up_event_p(void)
{
	START_TEST;
	Evas_Object *widget;
	int w, h;
	int nTimeoutId = 0;

	widget = widget_viewer_evas_add_widget(g_win, TEST_SAMPLE_APPID, NULL, 0.0f);
	if ( widget == NULL )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_add_widget failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_nRet = -1;
	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, widget_create_cb, WidgetViewerFeedMouseUpEvent);

	int ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	if ( ret != WIDGET_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_size failed\\n", __LINE__, API_NAMESPACE);
	}

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT_CB, WidgetViewerTimeout, NULL);
	elm_run();

	if ( g_nRet != 0 )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_feed_mouse_up_event failed. \\n", __LINE__, API_NAMESPACE);
		widget_viewer_evas_set_permanent_delete(widget, 1);
		evas_object_del(widget);
		return 1;
	}
	else
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_feed_mouse_up_event passed\\n", __LINE__, API_NAMESPACE );
	}

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);
	return 0;
}


//& purpose: widget viewer evas thaw visibility
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_thaw_visibility_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			widget viewer evas thaw visibility
* @scenario				thaw visibility
* @apicovered			widget_viewer_evas_thaw_visibility
* @passcase				When widget_viewer_evas_thaw_visibility is successful
* @failcase				If target API widget_viewer_evas_thaw_visibility fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_thaw_visibility_p(void)
{
	START_TEST;
	Evas_Object *widget;
	int w, h;
	int nTimeoutId = 0;

	widget = widget_viewer_evas_add_widget(g_win, TEST_SAMPLE_APPID, NULL, 0.0f);
	if ( widget == NULL )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_add_widget failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_nRet = -1;
	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, widget_create_cb, WidgetViewerThaw);

	int ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	if ( ret != WIDGET_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_size failed\\n", __LINE__, API_NAMESPACE);
	}

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT_CB, WidgetViewerTimeout, NULL);
	elm_run();

	if ( g_nRet != 0 )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_thaw_visibility failed. \\n", __LINE__, API_NAMESPACE);
		widget_viewer_evas_set_permanent_delete(widget, 1);
		evas_object_del(widget);
		return 1;
	}
	else
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_thaw_visibility passed.\\n", __LINE__, API_NAMESPACE);
	}

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);
	return 0;
}

//& purpose: widget viewer evas get title string
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_get_title_string_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			widget viewer evas get title string
* @scenario				get title string
* @apicovered			widget_viewer_evas_get_title_string
* @passcase				When widget_viewer_evas_get_title_string is successful
* @failcase				If target API widget_viewer_evas_get_title_string fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_get_title_string_p(void)
{
	START_TEST;

	Evas_Object *widget;
	int w, h;
	int nTimeoutId = 0;

	widget = widget_viewer_evas_add_widget(g_win, TEST_SAMPLE_APPID, NULL, 0.0f);
	if ( widget == NULL )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_add_widget failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_pTitleString = NULL;
	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, widget_create_cb, WidgetViewerGetTitleString);

	int ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	if ( ret != WIDGET_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_size failed\\n", __LINE__, API_NAMESPACE);
	}

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT_CB, WidgetViewerTimeout, NULL);
	elm_run();

	if ( g_pTitleString == NULL )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_get_title_string failed. \\n", __LINE__, API_NAMESPACE);
		widget_viewer_evas_set_permanent_delete(widget, 1);
		evas_object_del(widget);
		return 1;
	}
	else
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_get_title_string passed, Title is: %s\\n", __LINE__, API_NAMESPACE, g_pTitleString);
	}

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);
	return 0;
}


//& purpose: widget viewer evas freeze visibility
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_freeze_visibility_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			widget viewer evas freeze visibility
* @scenario				freeze visibility
* @apicovered			widget_viewer_evas_freeze_visibility
* @passcase				When widget_viewer_evas_freeze_visibility is successful
* @failcase				If target API widget_viewer_evas_freeze_visibility fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_freeze_visibility_p(void)
{
	START_TEST;
	Evas_Object *widget;
	int w, h;
	int nTimeoutId = 0;

	widget = widget_viewer_evas_add_widget(g_win, TEST_SAMPLE_APPID, NULL, 0.0f);
	if ( widget == NULL )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_add_widget failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_nRet = -1;
	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, widget_create_cb, WidgetViewerTcFreeze);

	int ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	if ( ret != WIDGET_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_size failed\\n", __LINE__, API_NAMESPACE);
	}

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT_CB, WidgetViewerTimeout, NULL);
	elm_run();

	if ( g_nRet != 0 )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_freeze_visibility failed. \\n", __LINE__, API_NAMESPACE);
		widget_viewer_evas_set_permanent_delete(widget, 1);
		evas_object_del(widget);
		return 1;
	}
	else
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_freeze_visibility passed\\n", __LINE__, API_NAMESPACE);
	}

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);
	return 0;
}

//& purpose: widget viewer evas set option
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_set_option_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			widget viewer evas set option
* @scenario				set option
* @apicovered			widget_viewer_evas_set_option
* @passcase				When widget_viewer_evas_set_option is successful
* @failcase				If target API widget_viewer_evas_set_option fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_set_option_p(void)
{
	START_TEST;
	int nRet;
	widget_evas_conf_e eWidgetEvasConf = WIDGET_VIEWER_EVAS_EASY_MODE;
	int value = 1; /**< Easy mode on/off. 1: on, 0: off */

	nRet = widget_viewer_evas_set_option(eWidgetEvasConf, value);
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_viewer_evas_set_option", WidgetViewerGetError(nRet));

	return 0;
}

//& purpose: Notifies the orientation of the viewer to all providers
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_notify_orientation_of_viewer_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Notifies the orientation of the viewer to all providers
* @scenario				orientation of viewer
* @apicovered			widget_viewer_evas_notify_orientation_of_viewer
* @passcase				When widget_viewer_evas_notify_orientation_of_viewer is successful
* @failcase				If target API widget_viewer_evas_notify_orientation_of_viewer fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_notify_orientation_of_viewer_p(void)
{
	START_TEST;
	int nRet;
	int nOrientation = 0;

	nRet = widget_viewer_evas_notify_orientation_of_viewer(nOrientation);
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_viewer_evas_notify_orientation_of_viewer", WidgetViewerGetError(nRet));

	return 0;
}

//& purpose: widget viewer evas cancel click event
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_cancel_click_event_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			widget viewer evas cancel click event
* @scenario				cancel click event
* @apicovered			widget_viewer_evas_cancel_click_event
* @passcase				When widget_viewer_evas_cancel_click_event is successful
* @failcase				If target API widget_viewer_evas_cancel_click_event fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_cancel_click_event_p(void)
{
	START_TEST;

	widget_viewer_evas_cancel_click_event(g_win);
	return 0;
}


//& purpose: Before delete a widget, set the deletion mode
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_set_permanent_delete_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Before delete a widget, set the deletion mode
* @scenario				set the deletion mode
* @apicovered			widget_viewer_evas_set_permanent_delete
* @passcase				When widget_viewer_evas_set_permanent_delete is successful
* @failcase				If target API widget_viewer_evas_set_permanent_delete fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_set_permanent_delete_p(void)
{
	START_TEST;
	/*second param: flag Pass 1 if you delete this widget instance permanently,
	or pass 0 if you want to keep it and it will be re-created soon.*/

	widget_viewer_evas_set_permanent_delete(g_win, 1);
	return 0;
}

//& purpose: widget viewer evas disable preview
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_disable_preview_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			widget viewer evas disable preview
* @scenario				disable preview
* @apicovered			widget_viewer_evas_disable_preview
* @passcase				When widget_viewer_evas_disable_preview is successful
* @failcase				If target API widget_viewer_evas_disable_preview fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_disable_preview_p(void)
{
	START_TEST;

	widget_viewer_evas_disable_preview(g_win);
	return 0;
}

//& purpose: widget viewer evas overlay text
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_disable_overlay_text_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			widget viewer evas overlay text
* @scenario				overlay text
* @apicovered			widget_viewer_evas_disable_overlay_text
* @passcase				When widget_viewer_evas_disable_overlay_text is successful
* @failcase				If target API widget_viewer_evas_disable_overlay_text fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_disable_overlay_text_p(void)
{
	START_TEST;

	Evas_Object *widget;
	int w, h;

	widget = widget_viewer_evas_add_widget(g_win, TEST_SAMPLE_APPID, NULL, 0.0f);
	if ( widget == NULL )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_add_widget failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	if ( ret != WIDGET_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_size failed\\n", __LINE__, API_NAMESPACE);
	}

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	widget_viewer_evas_disable_overlay_text(widget);

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	return 0;
}

//& purpose: widget viewer evas disable loading
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_disable_loading_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			widget viewer evas disable loading
* @scenario				disable loading
* @apicovered			widget_viewer_evas_disable_loading
* @passcase				When widget_viewer_evas_disable_loading is successful
* @failcase				If target API widget_viewer_evas_disable_loading fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_disable_loading_p(void)
{
	START_TEST;

	Evas_Object *widget;
	int w, h;

	widget = widget_viewer_evas_add_widget(g_win, TEST_SAMPLE_APPID, NULL, 0.0f);
	if ( widget == NULL )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_add_widget failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	if ( ret != WIDGET_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_size failed\\n", __LINE__, API_NAMESPACE);
	}

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	widget_viewer_evas_disable_loading(widget);

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	return 0;
}

//& purpose: widget viewer evas add widget
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_add_widget_p
* @since_tizen			2.3.1
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This function add widget
* @scenario				add widget
* @apicovered			widget_viewer_evas_add_widget
* @passcase				When widget_viewer_evas_add_widget is successful
* @failcase				If target API widget_viewer_evas_add_widget fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_add_widget_p(void)
{
	START_TEST;

	Evas_Object *widget;
	int w, h;

	widget = widget_viewer_evas_add_widget(g_win, TEST_SAMPLE_APPID, NULL, 0.0f);
	if ( widget == NULL )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_add_widget failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	if ( ret != WIDGET_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_size failed\\n", __LINE__, API_NAMESPACE);
	}

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);
	return 0;
}


//& purpose: Activate a widget in faulted state
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_activate_faulted_widget_p
* @since_tizen			2.3.1
* @author            	SRID(shobhit.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Activate a widget in faulted state
* @scenario				get content string of widget
* @apicovered			widget_viewer_evas_add_widget, evas_object_smart_callback_add, widget_service_get_size and widget_viewer_evas_activate_faulted_widget
* @passcase				if target api widget_viewer_evas_activate_faulted_widget does not crash
* @failcase				if target api widget_viewer_evas_activate_faulted_widget crashed
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_activate_faulted_widget_p(void)
{
	START_TEST;

	Evas_Object *widget;
	int w, h;
	int nTimeoutId = 0;

	widget = widget_viewer_evas_add_widget(g_win, TEST_SAMPLE_APPID, NULL, 0.0f);
	if ( widget == NULL )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_add_widget failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_nRet = -1;
	g_pContentString = NULL;
	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, widget_create_cb, WidgetViewerActivate);

	int ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	if ( ret != WIDGET_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_size failed\\n", __LINE__, API_NAMESPACE);
	}

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT_CB, WidgetViewerTimeout, NULL);
	elm_run();

	if ( g_nRet != 0 )
	{
		FPRINTF("[Line: %d][%s] Callback not Invoked: widget_viewer_evas_activate_faulted_widget API call is not called. \\n", __LINE__, API_NAMESPACE);
		widget_viewer_evas_set_permanent_delete(widget, 1);
		evas_object_del(widget);
		return 1;
	}
	else
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_activate_faulted_widget passed.\\n", __LINE__, API_NAMESPACE);
	}

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);
	return 0;
}


//& purpose: Gets content string of widget
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_get_content_info_p
* @since_tizen			2.3.1
* @author            	SRID(shobhit.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets content string of widget
* @scenario				get content string of widget
* @apicovered			widget_viewer_evas_add_widget, evas_object_smart_callback_add, widget_service_get_size and widget_viewer_evas_get_content_info
* @passcase				When widget_viewer_evas_get_content_info is successful
* @failcase				If target API widget_viewer_evas_get_content_info fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_get_content_info_p(void)
{
	START_TEST;

	Evas_Object *widget;
	int w, h;
	int nTimeoutId = 0;
	bundle *b;
	int len;
	char *content_info = NULL;

	b = bundle_create();
	if (b == NULL) {
		FPRINTF("[Line: %d][%s] bundle_create failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if (bundle_add_str(b, "CONTENT_INFO_TEST", "value") != BUNDLE_ERROR_NONE) {
		FPRINTF("[Line: %d][%s] bundle_add_str failed\\n", __LINE__, API_NAMESPACE);
		bundle_free(b);
		return 1;
	}

	if (bundle_encode(b, (bundle_raw **)&content_info, &len) != BUNDLE_ERROR_NONE) {
		FPRINTF("[Line: %d][%s] bundle_add_str failed\\n", __LINE__, API_NAMESPACE);
		bundle_free(b);
		return 1;
	}

	widget = widget_viewer_evas_add_widget(g_win, TEST_SAMPLE_APPID, content_info, 0.0f);
	if ( widget == NULL )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_add_widget failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_pContentString = NULL;
	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, widget_create_cb, WidgetViewerGetContent);

	int ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	if ( ret != WIDGET_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_size failed\\n", __LINE__, API_NAMESPACE);
	}

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT_CB, WidgetViewerTimeout, NULL);
	elm_run();

	if ( g_pContentString == NULL || strcmp(g_pContentString, content_info) != 0 )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_get_content_info failed. \\n", __LINE__, API_NAMESPACE);
		widget_viewer_evas_set_permanent_delete(widget, 1);
		evas_object_del(widget);
		return 1;
	}
	else
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_get_content_info passed, content is: %s\\n", __LINE__, API_NAMESPACE, g_pContentString);
	}

	bundle_free(b);
	free(content_info);
	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);
	return 0;
}

//& purpose: Gets widget objects instance id
//& type: auto
/**
* @testcase 			ITc_widget_viewer_evas_get_widget_instance_id_p
* @since_tizen			4.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Gets widget objects instance id
* @scenario				Gets widget objects instance id
* @apicovered			widget_viewer_evas_add_widget, evas_object_smart_callback_add, widget_service_get_size and widget_viewer_evas_get_widget_instance_id
* @passcase				When widget_viewer_evas_get_widget_instance_id is successful
* @failcase				If target API widget_viewer_evas_get_widget_instance_id fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_viewer_evas_get_widget_instance_id_p(void)
{
	START_TEST;

	Evas_Object *widget;
	int w, h;
	int nTimeoutId = 0;

	widget = widget_viewer_evas_add_widget(g_win, TEST_SAMPLE_APPID, NULL, 0.0f);
	if ( widget == NULL )
	{
		FPRINTF("[Line: %d][%s] widget_viewer_evas_add_widget failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_pContentString = NULL;
	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, widget_create_cb, WidgetViewerGetInstanceID);

	int ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	if ( ret != WIDGET_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_size failed\\n", __LINE__, API_NAMESPACE);
	}

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT_CB, WidgetViewerTimeout, NULL);
	elm_run();

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);
	
	return g_nInstanceId;
}

////& purpose: widget viewer evas get content string
////& type: auto
///**
//* @testcase 			ITc_widget_viewer_evas_get_content_string_p
//* @since_tizen			2.3.1
//* @author            	SRID(gaurav.m2)
//* @reviewer         	SRID(gupta.sanjay)
//* @type 				auto
//* @description			This function get content string
//* @scenario				get content string
//* @apicovered			widget_viewer_evas_get_content_string
//* @passcase				When widget_viewer_evas_get_content_string is successful
//* @failcase				If target API widget_viewer_evas_get_content_string fails or any precondition API fails
//* @precondition			NA
//* @postcondition		NA
//*/
//int ITc_widget_viewer_evas_get_content_string_p(void)
//{
//	START_TEST;
//	const char *pContentString=NULL;
//
//	pContentString = widget_viewer_evas_get_content_string(g_win);
//	if(pContentString == NULL)
//	{
//		FPRINTF("[Line: %d][%s] widget_viewer_evas_get_content_string failed\\n", __LINE__, API_NAMESPACE);
//		return 1;
//	}else{
//		FPRINTF("[Line: %d][%s] widget_viewer_evas_get_content_string id = [%s]\\n", __LINE__, API_NAMESPACE,pContentString);
//	}
//
//	return 0;
//}
//
////& purpose: widget viewer evas activate
////& type: auto
///**
//* @testcase 			ITc_widget_viewer_evas_activate_p
//* @since_tizen			2.3.1
//* @author            	SRID(gaurav.m2)
//* @reviewer         	SRID(gupta.sanjay)
//* @type 				auto
//* @description			widget viewer evas activate
//* @scenario				viewer evas activate
//* @apicovered			widget_viewer_evas_activate
//* @passcase				When widget_viewer_evas_activate is successful
//* @failcase				If target API widget_viewer_evas_activate fails or any precondition API fails
//* @precondition			NA
//* @postcondition		NA
//*/
//int ITc_widget_viewer_evas_activate_p(void)
//{
//	START_TEST;
//
//	widget_viewer_evas_activate(g_win);
//
//	return 0;
//}

/** @} */
/** @} */
