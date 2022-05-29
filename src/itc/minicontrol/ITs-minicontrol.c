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

#include "ITs-minicontrol-common.h"
/** @addtogroup itc-minicontrol
*  @ingroup minicontrol
*  @{
*/

static GMainLoop *g_pMainLoop = NULL;
static int g_itc_minicontrol_viewer_add_p_result = 0;
static bool g_bMinicontrolCallbackHit;
bool g_bMinicontrolNotSupported = false;
/**
 * @function 		ITs_minicontrol_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_minicontrol_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT start-up: ITs_Minicontrol_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bMinicontrolNotSupported = false;

#if defined(MOBILE) || defined(WEARABLE)   //Starts MOBILE/WEARABLE
	if ( !TCTCheckSystemInfoFeatureSupported(MINICONTROL_FEATURE, API_NAMESPACE) )
	{
			g_bMinicontrolNotSupported = true;
	}
#endif   //End mobile/wearable
	return;
}

/**
 * @function 		ITs_minicontrol_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_minicontrol_cleanup(void)
{
#if DEBUG
        FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Minicontrol_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		minicontrol_viewer_event_callback
* @description	 	callback function for minicontrol set event
* @parameter		event : minicontrol_event_e event, minicontrol_name : minicontrol_name, bundle: bundle, user_data: user_data sent to callback
* @return 			NA
*/
void minicontrol_viewer_event_callback(minicontrol_event_e event, const char *minicontrol_name, bundle *event_arg, void *data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] minicontrol_viewer_event_callback \\n", __LINE__, API_NAMESPACE);
#endif
	
	g_bMinicontrolCallbackHit = true;
	
	Evas_Object *parent_window = NULL;
	Evas_Object *viewer = NULL;
	parent_window = elm_win_add(NULL, "parent_window", ELM_WIN_BASIC);

	evas_object_resize(parent_window, 480, 800);

	viewer = minicontrol_viewer_add(parent_window, minicontrol_name);
	g_itc_minicontrol_viewer_add_p_result = (viewer != NULL) ? 1 : 0;

	evas_object_hide(parent_window);
	evas_object_hide(viewer);

	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		minicontrol_window_callback
* @description	 	callback function for minicontrol create window
* @parameter		event_type: minicontrol_viewer_event_e, bundle: bundle
* @return 			NA
*/
void minicontrol_window_callback(minicontrol_viewer_event_e event_type, bundle *event_arg)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] minicontrol_window_callback callback \\n", __LINE__, API_NAMESPACE);
#endif
	g_bMinicontrolCallbackHit = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		create_minicontrol_window_thread
* @description	 	callback function for minicontrol window
* @parameter		user_data: user_data sent to callback
* @return 			NA
*/
static int create_minicontrol_window_thread(void *data)
{
	Evas_Object *minicontrol_window = NULL;

	usleep(1000000);
	/* Wait a sec for viewer*/
	minicontrol_window = minicontrol_create_window(MINICONTROL_NAME, MINICONTROL_TARGET_VIEWER_QUICK_PANEL, minicontrol_window_callback);
	CHECK_HANDLE(minicontrol_window, "minicontrol_create_window");

	elm_win_alpha_set(minicontrol_window, EINA_TRUE);
	evas_object_resize(minicontrol_window, 480, 800);
	evas_object_show(minicontrol_window);

	return 0;
}

/************************** callback block end**********************************************/

/** @addtogroup itc-minicontrol-testcases
*  @brief 		Integration testcases for module minicontrol
*  @ingroup 	itc-minicontrol
*  @{
*/

//& purpose: to add minicontrol named as "minicontrol_name" to a given parent evas object return it
//& type : auto
/**
* @testcase 			ITc_minicontrol_viewer_add_p
* @type 				auto
* @author				SRID(shekhar1.s)
* @reviewer				SRID(gupta.sanjay)
* @since_tizen			2.4
* @description			Adds minicontrol named as "minicontrol_name" to a given parent evas object and returns it.
* @scenario				sets the callback for the viewer event\n
*						creates window\n
*						checks the viewer callback\n
*						adds the viewer\n
*						unsets the callback
* @apicovered			minicontrol_viewer_set_event_cb, minicontrol_viewer_unset_event_cb, minicontrol_viewer_add
* @passcase				When minicontrol_viewer_add return success
* @failcase				When minicontrol_viewer_add return failure
* @precondition			none
* @postcondition		none
*/
int ITc_minicontrol_viewer_add_p(void)
{
	START_TEST;
	
	pthread_t thread_id;
	int g_timeout_id = 0;
	minicontrol_error_e nRet;
	g_itc_minicontrol_viewer_add_p_result = 0;

	nRet = minicontrol_viewer_set_event_cb(minicontrol_viewer_event_callback, "user_data");
#if defined(MOBILE) || defined(WEARABLE)   //Starts MOBILE/WEARABLE
	if (g_bMinicontrolNotSupported)
	{
		if(nRet != MINICONTROL_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line: %d][%s] Feature is mismatch \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line: %d][%s] Feature is Not Supported \\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
#endif   //End mobile/wearable
	PRINT_RESULT(MINICONTROL_ERROR_NONE, nRet, "minicontrol_viewer_set_event_cb", MinicontrolGetError(nRet));

	create_minicontrol_window_thread(NULL);
	RUN_POLLING_LOOP;
	PRINT_RESULT(1, g_itc_minicontrol_viewer_add_p_result, "minicontrol_viewer_add", MinicontrolGetError(nRet));
	nRet = minicontrol_viewer_unset_event_cb();
	PRINT_RESULT(MINICONTROL_ERROR_NONE, nRet, "minicontrol_viewer_unset_event_cb", MinicontrolGetError(nRet));
	
	return 0;
}

//& purpose: to send an event to the provider.
//& type : auto
/**
* @testcase 			ITc_minicontrol_viewer_send_event_p
* @type 				auto
* @author				SRID(shekhar1.s)
* @reviewer				SRID(gupta.sanjay)
* @since_tizen			2.4
* @description			Sends an event to the provider.
* @scenario				send the event to the provider.
* @apicovered			minicontrol_viewer_send_event
* @passcase				When minicontrol_viewer_send_event return success
* @failcase				When minicontrol_viewer_send_event return failure
* @precondition			none
* @postcondition		none
*/
int ITc_minicontrol_viewer_send_event_p(void)
{
	START_TEST;

	bundle *event_arg = NULL;
	minicontrol_viewer_event_e event_viewer[] = { MINICONTROL_VIEWER_EVENT_REPORT_ANGLE, MINICONTROL_VIEWER_EVENT_SHOW, MINICONTROL_VIEWER_EVENT_HIDE };
	
	int nEnumEventSize = sizeof(event_viewer) / sizeof(event_viewer[0]);
	int nEnumEventCounter = 0;
	for ( nEnumEventCounter = 0; nEnumEventCounter < nEnumEventSize; nEnumEventCounter++ )
	{
		minicontrol_error_e nRet = minicontrol_viewer_send_event(TARGET_APP_ID, event_viewer[nEnumEventCounter], event_arg);
#if defined(MOBILE) || defined(WEARABLE)   //Starts MOBILE/WEARABLE
		if (g_bMinicontrolNotSupported)
		{
			if(nRet != MINICONTROL_ERROR_NOT_SUPPORTED)
			{
				FPRINTF("[Line: %d][%s] Feature is mismatch \\n", __LINE__, API_NAMESPACE);
				return 1;
			}
			else
			{
				FPRINTF("[Line: %d][%s] Feature is Not Supported \\n", __LINE__, API_NAMESPACE);
				return 0;
			}
		}
#endif   //End mobile/wearable
		PRINT_RESULT(MINICONTROL_ERROR_NONE, nRet, "minicontrol_viewer_send_event", MinicontrolGetError(nRet));
	}
	return 0;
}

//& purpose: Register and unregister a callback for events originated by minicontrol provider.
//& type : auto
/**
* @testcase 			ITc_minicontrol_viewer_set_unset_event_cb_p
* @type 				auto
* @author				SRID(shekhar1.s)
* @reviewer				SRID(gupta.sanjay)
* @since_tizen			2.4
* @description			Registers and unregister a callback for events originated by minicontrol provider.
* @scenario				sets the callback for the viewer event\n
*						creates window\n
*						checks the viewer callback\n
*						adds the viewer\n
*						unsets the callback
* @apicovered			minicontrol_viewer_set_event_cb, minicontrol_create_window, minicontrol_viewer_unset_event_cb
* @passcase				When minicontrol_viewer_set_event_cb, minicontrol_create_window, minicontrol_viewer_unset_event_cb return success
* @failcase				When minicontrol_viewer_set_event_cb, minicontrol_create_window, minicontrol_viewer_unset_event_cb return failure
* @precondition			none
* @postcondition		none
*/
int ITc_minicontrol_viewer_set_unset_event_cb_p(void)
{
	START_TEST;
	
	int g_timeout_id = 0;
	Evas_Object *minicontrol_window = NULL;
	g_bMinicontrolCallbackHit = false;
	
	minicontrol_error_e nRet = minicontrol_viewer_set_event_cb(minicontrol_viewer_event_callback, NULL);
#if defined(MOBILE) || defined(WEARABLE)   //Starts MOBILE/WEARABLE
	if (g_bMinicontrolNotSupported)
	{
		if(nRet != MINICONTROL_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line: %d][%s] Feature is mismatch \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line: %d][%s] Feature is Not Supported \\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
#endif   //End mobile/wearable
	PRINT_RESULT(MINICONTROL_ERROR_NONE, nRet, "minicontrol_viewer_set_event_cb", MinicontrolGetError(nRet));
	
	minicontrol_window = minicontrol_create_window(MINICONTROL_NAME, MINICONTROL_TARGET_VIEWER_QUICK_PANEL, minicontrol_window_callback);
	if ( minicontrol_window == NULL )
	{
		nRet = get_last_result();
		FPRINTF("[Line : %d][%s] minicontrol_viewer_add failed viewer is NULL error %s\\n", __LINE__, API_NAMESPACE, MinicontrolGetError(nRet));
		minicontrol_viewer_unset_event_cb();
		return 1;	
	}
	
	elm_win_alpha_set(minicontrol_window, EINA_TRUE);
	evas_object_resize(minicontrol_window, 480, 800);
	evas_object_show(minicontrol_window);
	
	RUN_POLLING_LOOP;
	
	if ( g_bMinicontrolCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] minicontrol_viewer_set_event_cb callback not hit \\n", __LINE__, API_NAMESPACE);
		minicontrol_viewer_unset_event_cb();
		return 1;	
	}

	nRet = minicontrol_viewer_unset_event_cb();
	PRINT_RESULT(MINICONTROL_ERROR_NONE, nRet, "minicontrol_viewer_unset_event_cb", MinicontrolGetError(nRet));
	
	return 0;
}

//& purpose: Create a window for minicontrol.
//& type : auto
/**
* @testcase 			ITc_minicontrol_create_window_p
* @type 				auto
* @author				SRID(shekhar1.s)
* @reviewer				SRID(gupta.sanjay)
* @since_tizen			2.4
* @description			Create a window for minicontrol.
* @scenario				create window\n
*						check the callback
* @apicovered			minicontrol_create_window
* @passcase				When minicontrol_create_window return success
* @failcase				When minicontrol_create_window return failure
* @precondition			none
* @postcondition		none
*/
int ITc_minicontrol_create_window_p(void)
{
	START_TEST;
	
	int g_timeout_id = 0;
	Evas_Object *minicontrol_window = NULL;	
	minicontrol_target_viewer_e event_viewer[] = { MINICONTROL_TARGET_VIEWER_QUICK_PANEL };
	int nEnumEventSize = sizeof(event_viewer) / sizeof(event_viewer[0]);
	int nEnumEventCounter = 0;
	
	for ( nEnumEventCounter = 0; nEnumEventCounter < nEnumEventSize; nEnumEventCounter++ )
	{
		minicontrol_window = minicontrol_create_window(MINICONTROL_NAME, event_viewer[nEnumEventCounter], minicontrol_window_callback);
		minicontrol_error_e nRet = get_last_result();
#if defined(MOBILE) || defined(WEARABLE)   //Starts MOBILE/WEARABLE
		if (g_bMinicontrolNotSupported)
		{
			if(nRet != MINICONTROL_ERROR_NOT_SUPPORTED)
			{
				FPRINTF("[Line: %d][%s] Feature is mismatch \\n", __LINE__, API_NAMESPACE);
				return 1;
			}
			else
			{
				FPRINTF("[Line: %d][%s] Feature is Not Supported \\n", __LINE__, API_NAMESPACE);
				return 0;
			}
		}
#endif   //End mobile/wearable

		elm_win_alpha_set(minicontrol_window, EINA_TRUE);
		evas_object_resize(minicontrol_window, 480, 800);
		evas_object_show(minicontrol_window);
	
		RUN_POLLING_LOOP;
		if ( minicontrol_window == NULL )
		{
			FPRINTF("[Line : %d][%s] minicontrol_create_window failed minicontrol_window is NULL for enum %s error %s\\n", __LINE__, API_NAMESPACE, MinicontrolGetTargetViewer(event_viewer[nEnumEventCounter]), MinicontrolGetError(nRet));
			return 1;	
		}

	}
	evas_object_hide(minicontrol_window);
	return 0;
}

//& purpose: Send an event to the viewer.
//& type : auto
/**
* @testcase 			ITc_minicontrol_send_event_p
* @type 				auto
* @author				SRID(shekhar1.s)
* @reviewer				SRID(gupta.sanjay)
* @since_tizen			2.4
* @description			Send an event to the viewer.
* @scenario				create window\n
*						send event
* @apicovered			minicontrol_create_window, minicontrol_send_event
* @passcase				When minicontrol_create_window, minicontrol_send_event return success
* @failcase				When minicontrol_create_window, minicontrol_send_event return failure
* @precondition			none
* @postcondition		none
*/
int ITc_minicontrol_send_event_p(void)
{
	START_TEST;
	
	Evas_Object *minicontrol_window = NULL;

	minicontrol_window = minicontrol_create_window(MINICONTROL_NAME, MINICONTROL_TARGET_VIEWER_QUICK_PANEL, minicontrol_window_callback);
	minicontrol_error_e nRet = get_last_result();
#if defined(MOBILE) || defined(WEARABLE)   //Starts MOBILE/WEARABLE
	if (g_bMinicontrolNotSupported)
	{
		if(nRet != MINICONTROL_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line: %d][%s] Feature is mismatch \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line: %d][%s] Feature is Not Supported \\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
#endif   //End mobile/wearable
	if ( minicontrol_window == NULL)
	{
		FPRINTF("[Line : %d][%s] minicontrol_create_window failed with error %s\\n", __LINE__, API_NAMESPACE, MinicontrolGetError(nRet));
		return 1;	
	}
	minicontrol_provider_event_e event_viewer[] = { MINICONTROL_PROVIDER_EVENT_REQUEST_HIDE, MINICONTROL_PROVIDER_EVENT_REQUEST_ANGLE };
	
	int nEnumEventSize = sizeof(event_viewer) / sizeof(event_viewer[0]);
	int nEnumEventCounter = 0;
	for ( nEnumEventCounter = 0; nEnumEventCounter < nEnumEventSize; nEnumEventCounter++ )
	{
		minicontrol_error_e nRet = minicontrol_send_event(minicontrol_window, event_viewer[nEnumEventCounter], NULL);
		PRINT_RESULT(MINICONTROL_ERROR_NONE, nRet, "minicontrol_send_event", MinicontrolGetError(nRet));
	}
	evas_object_hide(minicontrol_window);
	return 0;
}

/** @}*/
/** @}*/
