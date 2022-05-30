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
#include "ITs-efl-util-common.h"
#include <efl_util.h>

//& set: EflUtil

/** @addtogroup itc-efl-util
 *  @ingroup itc
 *  @{
 */
 
static void WinDel(void *data, Evas_Object *obj, void *event)
{
    elm_exit();
}
efl_util_gesture_type_e const Values[] = {EFL_UTIL_GESTURE_TYPE_NONE,EFL_UTIL_GESTURE_TYPE_EDGE_SWIPE,EFL_UTIL_GESTURE_TYPE_EDGE_DRAG,
					  EFL_UTIL_GESTURE_TYPE_TAP,EFL_UTIL_GESTURE_TYPE_PALM_COVER,EFL_UTIL_GESTURE_TYPE_PAN,EFL_UTIL_GESTURE_TYPE_PINCH,
						EFL_UTIL_GESTURE_TYPE_PALM_SWIPE};
efl_util_gesture_edge_e const Edge_Values[] = {EFL_UTIL_GESTURE_EDGE_NONE,EFL_UTIL_GESTURE_EDGE_TOP,EFL_UTIL_GESTURE_EDGE_RIGHT,EFL_UTIL_GESTURE_EDGE_BOTTOM,
					 	EFL_UTIL_GESTURE_EDGE_LEFT};

#define MAX_EDGE_VAL 4
#define MAX_VAL      7

static Evas_Object* CreateNormalWin(const char *name)
{
	Evas_Object *eo = NULL;

	eo = elm_win_add(NULL, name, ELM_WIN_BASIC);
	if (eo)
	{
		elm_win_title_set(eo, name);
		elm_win_borderless_set(eo, EINA_TRUE);
		evas_object_smart_callback_add(eo, "delete,request",
				WinDel, NULL);
		elm_win_indicator_mode_set(eo, ELM_WIN_INDICATOR_SHOW);
	}

	return eo;
}



/**
* @function 		ITs_efl_util_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_efl_util_startup(void)
{
	struct stat buf;   
	if ( stat(ERR_LOG, &buf) == 0 )
	{
		remove(ERR_LOG);
	}
	elm_init(0, NULL);
	g_bEflUtilCreation = true;
}

/**
* @function 		ITs_efl_util_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_efl_util_cleanup(void)
{
	elm_shutdown();
}


/** @addtogroup itc-efl-util-testcases
 *  @brief 		Integration testcases for module efl-util
 *  @ingroup 	itc-efl-util
 *  @{
 */
 
//& purpose: API to test efl_util_set_notification_window_level and efl_util_get_notification_window_level
//& type: auto
/**
* @testcase   			ITc_efl_util_efl_util_set_get_notification_window_level_p
* @since_tizen 			2.3
* @author             	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and Gets Notification Level
* @scenario				Set Notification Level \n
* 						Get Notification Level and Verify
* @apicovered			efl_util_set_notification_window_level, efl_util_get_notification_window_level
* @passcase				When efl_util_set_notification_window_level and efl_util_get_notification_window_level are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_efl_util_efl_util_set_get_notification_window_level_p(void)
{
	START_TEST;
	
	Evas_Object *pstWindow = NULL;
	if ( EflUtilCreateNotificationWindow(&pstWindow) == false )
	{
		return 1;
	}
	
	efl_util_notification_level_e eLevel = EFL_UTIL_NOTIFICATION_LEVEL_DEFAULT;

	// Target API
	int nRetVal = efl_util_set_notification_window_level(pstWindow, EFL_UTIL_NOTIFICATION_LEVEL_MEDIUM);

	PRINT_RESULT(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_set_notification_window_level", EflUtilGetError(nRetVal));

	// Target API
	nRetVal = efl_util_get_notification_window_level(pstWindow, &eLevel);
	PRINT_RESULT(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_get_notification_window_level", EflUtilGetError(nRetVal));
	if ( eLevel != EFL_UTIL_NOTIFICATION_LEVEL_MEDIUM )
	{
		FPRINTF("[Line : %d][%s] efl_util_set_notification_window_level failed due to level mismatch. Expected Level : EFL_UTIL_NOTIFICATION_LEVEL_MEDIUM, Obtained Level : %d\\n", __LINE__, API_NAMESPACE , eLevel);
		return 1;
	}
	return 0;
}


//& purpose: API to test efl_util_set_window_opaque_state
//& type: auto
/**
* @testcase				ITc_efl_util_set_window_opaque_state_p
* @since_tizen 			2.4
* @author				SRID(a.ankush)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets the alpha window's visual state to opaque state\n
* @scenario				Set the alpha window's visual state to opaque state\n
*						Unset the alpha window's visual state\n
* @apicovered			efl_util_set_window_opaque_state
* @passcase				When efl_util_set_window_opaque_state is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_efl_util_set_window_opaque_state_p(void)
{
	START_TEST;

	Evas_Object *pstWindow = NULL;
	if ( EflUtilCreateNotificationWindow(&pstWindow) == false )
	{
		return 1;
	}
	int set_unset_opaque[] = {1,0};
	int nSize = sizeof(set_unset_opaque)/sizeof(set_unset_opaque[0]);
	int nIndex = 0;

	for(nIndex = 0; nIndex < nSize; nIndex++)
	{	
		FPRINTF("[Line : %d][%s] Executing for opaque value = %d \\n", __LINE__, API_NAMESPACE, set_unset_opaque[nIndex]);
		int nRetVal = efl_util_set_window_opaque_state(pstWindow, set_unset_opaque[nIndex]);
		PRINT_RESULT(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_set_window_opaque_state", EflUtilGetError(nRetVal));
	}
	return 0;
}

//& purpose: Sets the window's screen mode
//& type: auto
/**
* @testcase				ITc_efl_util_set_get_window_screen_mode_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			This API is useful when the application need to keep the display turned on\n
* @scenario				Set the window's screen mode\n
*						Get the window's screen mode\n
* @apicovered			efl_util_set_window_screen_mode, efl_util_get_window_screen_mode
* @passcase				When efl_util_set_window_screen_mode and efl_util_get_window_screen_mode are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_efl_util_set_get_window_screen_mode_p(void)
{
	START_TEST;
	efl_util_screen_mode_e eScreenMode[] = { 
										 EFL_UTIL_SCREEN_MODE_DEFAULT,
										 EFL_UTIL_SCREEN_MODE_ALWAYS_ON
										};
	efl_util_screen_mode_e eGetMode;

	Evas_Object *pstWindow = NULL;
	if ( EflUtilCreateNotificationWindow(&pstWindow) == false )
	{
		return 1;
	}

	int nIndex = 0;
	int nSize = sizeof(eScreenMode)/sizeof(eScreenMode[0]);
	
	for(nIndex = 0; nIndex < nSize ; nIndex++)
	{
		FPRINTF("[Line : %d][%s] Executing for Set Mode = %s \\n", __LINE__, API_NAMESPACE, GetScreenMode(eScreenMode[nIndex]));
		//Target API
		int nRetVal = efl_util_set_window_screen_mode(pstWindow, eScreenMode[nIndex]);
		PRINT_RESULT(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_set_window_screen_mode", EflUtilGetError(nRetVal));

		//Target API
		nRetVal = efl_util_get_window_screen_mode(pstWindow, &eGetMode);
		PRINT_RESULT(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_get_window_screen_mode", EflUtilGetError(nRetVal));

		if ( eGetMode != eScreenMode[nIndex] )
		{
			FPRINTF("[Line : %d][%s] efl_util set get screen mode failes since set and get mode are not same, Set mode = %d, Get Mode = %d\\n", __LINE__, API_NAMESPACE, eScreenMode[nIndex], eGetMode);
			return 1;
		}
	}

	return 0;
}

//& purpose: Sets the window's brightness
//& type: auto
/**
* @testcase				ITc_efl_util_set_get_window_brightness_p
* @since_tizen 			3.0
* @author				SRID(shilpa.j)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			This API sets the brightness of window
* @scenario				Set the window's brightness
*						Get the window's brightness
* @apicovered			efl_util_set_window_brightness, efl_util_get_window_brightness
* @passcase				When efl_util_set_window_brightness and efl_util_get_window_brightness are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_efl_util_set_get_window_brightness_p(void)
{
	START_TEST;
	
	Evas_Object *pstWindow = NULL;
	if ( EflUtilCreateNotificationWindow(&pstWindow) == false )
	{
		return 1;
	}

	int nBrigtness = 50;
	int nResultBrigtness =-1;

	//Target API
	int nRetVal = efl_util_set_window_brightness(pstWindow,nBrigtness);
	PRINT_RESULT(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_set_window_brightness", EflUtilGetError(nRetVal));

	//Target API
	nRetVal = efl_util_get_window_brightness(pstWindow, &nResultBrigtness);
	PRINT_RESULT(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_get_window_brightness", EflUtilGetError(nRetVal));

	if ( nBrigtness != nResultBrigtness )
	{
		FPRINTF("[Line : %d][%s] efl_util set get brightness  fails since set and get brightness are not same, Set Brightness = %d, Get Brightness = %d\\n", __LINE__, API_NAMESPACE, nBrigtness, nResultBrigtness);
		return 1;
	}
	

	return 0;
}

//& purpose: Initializes system and check if global gestures are supported
//& type: auto
/**
* @testcase				ITc_efl_util_gesture_initialize_deinitialize_p
* @since_tizen 			4.0
* @author				SRID(bipin.k)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			To verify wether efl util gesture initialize and deinitialize api is working
*						properly.
* @scenario				Initialize gesture API and Deinitialize gesture API.
* @apicovered			efl_util_gesture_initialize, efl_util_gesture_deinitialize
* @passcase				When efl_util_gesture_initialize and efl_util_gesture_deinitialize are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_efl_util_gesture_initialize_deinitialize_p(void)
{
	START_TEST;
	int nRetVal = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;

	h_gesture = efl_util_gesture_initialize();
	CHECK_HANDLE(h_gesture,"efl_util_gesture_initialize");

	nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_initialize", EflUtilGetError(nRetVal),efl_util_gesture_deinitialize(h_gesture));

	nRetVal = efl_util_gesture_deinitialize(h_gesture);
	PRINT_RESULT(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_deinitialize", EflUtilGetError(nRetVal));

	return 0;
}


//& purpose: To verify  efl_util_gesture_edge_swipe_new with one fingure
// Generates a edge swipe gesture's grab info handle.
//& type: auto
/**
* @testcase				ITc_efl_util_gesture_edge_swipe_new_p
* @since_tizen 			4.0
* @author				SRID(bipin.k)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			To verify whether efl_util_gesture_edge_swipe_new API is
*						working properly in the case a user requests the new edge swipe
*						with one  fingers and differrent top edges.
* @scenario				Initialize gesture API and then create gesture grab info handle with
*						one fingure.
* @apicovered			efl_util_gesture_edge_swipe_new
* @passcase				When efl_util_gesture_edge_swipe_new is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_efl_util_gesture_edge_swipe_new_p(void)
{
	START_TEST;

	int nRetVal = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_data d_edge_swipe = NULL;

	for(int i=1;i<=MAX_EDGE_VAL;i++)
	{
		efl_util_gesture_h h_gesture = NULL;

		h_gesture = efl_util_gesture_initialize();
		CHECK_HANDLE(h_gesture,"efl_util_gesture_initialize");

		nRetVal = get_last_result();
		PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_initialize", EflUtilGetError(nRetVal),efl_util_gesture_deinitialize(h_gesture));

		int type=(efl_util_gesture_edge_e)Edge_Values[i];
		d_edge_swipe = efl_util_gesture_edge_swipe_new(h_gesture, 1, type);
		CHECK_HANDLE_CLEANUP(d_edge_swipe,"efl_util_gesture_edge_swipe_new",efl_util_gesture_deinitialize(h_gesture));
		nRetVal = get_last_result();
		PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_edge_swipe_new", EflUtilGetError(nRetVal),efl_util_gesture_deinitialize(h_gesture));

		nRetVal = efl_util_gesture_deinitialize(h_gesture);
		PRINT_RESULT(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_deinitialize", EflUtilGetError(nRetVal));
	}

		return 0;
}


//& purpose: To verify  efl_util_gesture_edge_swipe_new with two fingers.
// Generates a edge swipe gesture's grab info handle.
//& type: auto
/**
* @testcase				ITc_efl_util_gesture_edge_swipe_new_two_fingers_p
* @since_tizen 			4.0
* @author				SRID(bipin.k)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description  		To verify whether efl_util_gesture_edge_swipe_new API is
*						working properly in the case a user requests the new edge swipe
*						with two fingers and top edge
* @scenario				Initialize gesture API and generate a gestures grab info handle with
*						two fingers.
* @apicovered			efl_util_gesture_edge_swipe_new
* @passcase				When efl_util_gesture_edge_swipe_new is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_efl_util_gesture_edge_swipe_new_two_fingers_p(void)
{
	START_TEST;

	int nRetVal = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_edge_swipe = NULL;

	h_gesture = efl_util_gesture_initialize();
	CHECK_HANDLE(h_gesture,"efl_util_gesture_initialize");

	nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_initialize", EflUtilGetError(nRetVal),efl_util_gesture_deinitialize(h_gesture));

	d_edge_swipe = efl_util_gesture_edge_swipe_new(h_gesture, 2, EFL_UTIL_GESTURE_EDGE_TOP);
	CHECK_HANDLE_CLEANUP(d_edge_swipe,"efl_util_gesture_edge_swipe_new",efl_util_gesture_deinitialize(h_gesture));
	nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_edge_swipe_new", EflUtilGetError(nRetVal),efl_util_gesture_deinitialize(h_gesture));

	nRetVal = efl_util_gesture_deinitialize(h_gesture);
	PRINT_RESULT(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_deinitialize", EflUtilGetError(nRetVal));

	return 0;
}

//& purpose: To verify efl_util_gesture_edge_swipe_size_set,efl_util_gesture_edge_swipe_free,
//Sets a specific size of edge for edge swipe gesture.
//& type: auto
/**
* @testcase				ITc_efl_util_gesture_edge_swipe_size_set_and_free_p
* @since_tizen 			4.0
* @author				SRID(bipin.k)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description  		To verify whether efl_util_gesture_edge_swipe_size_set API is
*						working properly in the case a user requests the set edge swipe size
*						with partial edge size 0 to 359.
* @scenario				Initialize gesture API efl_util_gesture_initialize,efl_util_gesture_edge_swipe_new and
*						try to set a specific size of edge for edge swipe gesture.
* @apicovered			efl_util_gesture_edge_swipe_size_set,efl_util_gesture_edge_swipe_free.
* @passcase				When efl_util_gesture_edge_swipe_size_set,efl_util_gesture_edge_swipe_free is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_efl_util_gesture_edge_swipe_size_set_and_free_p(void)
{
	START_TEST;

	int nRetVal = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_edge_swipe = NULL;

	h_gesture = efl_util_gesture_initialize();
	CHECK_HANDLE(h_gesture, "efl_util_gesture_initialize");

	nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_initialize", EflUtilGetError(nRetVal),efl_util_gesture_deinitialize(h_gesture));

	d_edge_swipe = efl_util_gesture_edge_swipe_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_TOP);
	CHECK_HANDLE_CLEANUP(d_edge_swipe,"efl_util_gesture_edge_swipe_new",efl_util_gesture_deinitialize(h_gesture));

	nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_edge_swipe_new", EflUtilGetError(nRetVal),efl_util_gesture_deinitialize(h_gesture));

	nRetVal = efl_util_gesture_edge_swipe_size_set(d_edge_swipe, EFL_UTIL_GESTURE_EDGE_SIZE_PARTIAL,0,359);
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_edge_swipe_size_set", EflUtilGetError(nRetVal),efl_util_gesture_edge_swipe_free(h_gesture, d_edge_swipe);efl_util_gesture_deinitialize(h_gesture));

	nRetVal = efl_util_gesture_edge_swipe_free(h_gesture, d_edge_swipe);
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_edge_swipe_free", EflUtilGetError(nRetVal),efl_util_gesture_deinitialize(h_gesture));

	nRetVal = efl_util_gesture_deinitialize(h_gesture);
	PRINT_RESULT(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_deinitialize", EflUtilGetError(nRetVal));

	return 0;
}

//& purpose: To verify efl_util_gesture_edge_drag_new,efl_util_gesture_edge_drag_free.
//& type: auto
/**
* @testcase				ITc_efl_util_gesture_edge_drag_new_and_free_p
* @since_tizen 			4.0
* @author				SRID(bipin.k)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description  		To verify whether efl_util_gesture_edge_drag_new,efl_util_gesture_edge_drag_free
*						API is working properly in the case a user requests the new edge drag
*						with one finger and top edge.
* @scenario				Initialize gesture API efl_util_gesture_initialize and then generate a edge drag
*						gesture's grab info handle and then free the handle.
* @apicovered			efl_util_gesture_edge_drag_new,efl_util_gesture_edge_drag_free
* @passcase				When efl_util_gesture_edge_drag_new,efl_util_gesture_edge_drag_free is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_efl_util_gesture_edge_drag_new_and_free_p(void)
{
	START_TEST;

	int nRetVal = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_edge_drag = NULL;

	h_gesture = efl_util_gesture_initialize();
	CHECK_HANDLE(h_gesture,"efl_util_gesture_initialize");

	nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_initialize", EflUtilGetError(nRetVal),efl_util_gesture_deinitialize(h_gesture));

	d_edge_drag = efl_util_gesture_edge_drag_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_TOP);
	CHECK_HANDLE_CLEANUP(d_edge_drag,"efl_util_gesture_edge_drag_new",efl_util_gesture_deinitialize(h_gesture));

	nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_edge_drag_new", EflUtilGetError(nRetVal),efl_util_gesture_deinitialize(h_gesture));

	nRetVal = efl_util_gesture_edge_drag_free(h_gesture, d_edge_drag);
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_edge_drag_free", EflUtilGetError(nRetVal),efl_util_gesture_deinitialize(h_gesture));

	nRetVal = efl_util_gesture_deinitialize(h_gesture);
	PRINT_RESULT(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_deinitialize", EflUtilGetError(nRetVal));

	return 0;
}


//& purpose: To verify efl_util_gesture_edge_drag_size_set for setting  specific
//size of edge for edge drag gesture.
//& type: auto
/**
* @testcase				ITc_efl_util_gesture_edge_drag_size_set_p
* @since_tizen 			4.0
* @author				SRID(bipin.k)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description 			To verify whether efl_util_gesture_edge_drag_size_set API is
*						working properly in the case a user requests the set edge drag size
*						with partial edge size.
* @scenario				Initialize gesture API efl_util_gesture_initialize,efl_util_gesture_edge_drag_new and setting
*						specific size of edge for edge drag gesture.
* @apicovered			efl_util_gesture_edge_drag_size_set
* @passcase				When efl_util_gesture_edge_drag_size_set is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_efl_util_gesture_edge_drag_size_set_p(void)
{
	START_TEST;

	int nRetVal = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_edge_drag = NULL;

	h_gesture = efl_util_gesture_initialize();
	CHECK_HANDLE(h_gesture,"efl_util_gesture_initialize");

	nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_initialize", EflUtilGetError(nRetVal),efl_util_gesture_deinitialize(h_gesture));

	d_edge_drag = efl_util_gesture_edge_drag_new(h_gesture, 1, EFL_UTIL_GESTURE_EDGE_TOP);
	CHECK_HANDLE_CLEANUP(d_edge_drag,"efl_util_gesture_edge_drag_new",efl_util_gesture_deinitialize(h_gesture));

	nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_edge_drag_new", EflUtilGetError(nRetVal),efl_util_gesture_deinitialize(h_gesture));

	nRetVal = efl_util_gesture_edge_drag_size_set(d_edge_drag, EFL_UTIL_GESTURE_EDGE_SIZE_PARTIAL,0,359);
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_edge_drag_size_set", EflUtilGetError(nRetVal),efl_util_gesture_edge_drag_free(h_gesture, d_edge_drag);efl_util_gesture_deinitialize(h_gesture));

	nRetVal = efl_util_gesture_edge_drag_free(h_gesture, d_edge_drag);
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_edge_drag_free", EflUtilGetError(nRetVal),efl_util_gesture_deinitialize(h_gesture));

	nRetVal = efl_util_gesture_deinitialize(h_gesture);
	PRINT_RESULT(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_deinitialize", EflUtilGetError(nRetVal));

	return 0;
}

//& purpose: To verify efl_util_gesture_tap_new,efl_util_gesture_tap_free
//& type: auto
/**
* @testcase				ITc_efl_util_gesture_tap_new_and_free_p
* @since_tizen 			4.0
* @author				SRID(bipin.k)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description 			To verify whether efl_util_gesture_tap_new API is
*						working properly in the case a user requests the new tap
*						with two fingers and double taps.
* @scenario				Initialize gesture API efl_util_gesture_initialize and  generate a tap
*						gesture's grab info handle and then free the handle.
* @apicovered			efl_util_gesture_tap_new,efl_util_gesture_tap_free.
* @passcase				When efl_util_gesture_tap_new,efl_util_gesture_tap_free is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_efl_util_gesture_tap_new_and_free_p(void)
{
	START_TEST;

	int nRetVal = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_tap = NULL;

	h_gesture = efl_util_gesture_initialize();
	CHECK_HANDLE(h_gesture,"efl_util_gesture_initialize");

	nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_initialize", EflUtilGetError(nRetVal),efl_util_gesture_deinitialize(h_gesture));

	d_tap = efl_util_gesture_tap_new(h_gesture, 2, 2);
	CHECK_HANDLE_CLEANUP(d_tap,"efl_util_gesture_tap_new",efl_util_gesture_deinitialize(h_gesture));

	nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_tap_new", EflUtilGetError(nRetVal),efl_util_gesture_deinitialize(h_gesture));

	nRetVal = efl_util_gesture_tap_free(h_gesture, d_tap);
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_tap_free", EflUtilGetError(nRetVal),efl_util_gesture_deinitialize(h_gesture));

	nRetVal = efl_util_gesture_deinitialize(h_gesture);
	PRINT_RESULT(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_deinitialize", EflUtilGetError(nRetVal));

	return 0;
}

 //& purpose: To verify efl_util_gesture_palm_cover_new,efl_util_gesture_palm_cover_free
//& type: auto
/**
* @testcase				ITc_efl_util_gesture_palm_cover_new_and_free_p
* @since_tizen 			4.0
* @author				SRID(bipin.k)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description 			To verify whether efl_util_gesture_palm_cover_new API is
*						working properly in the case a user requests the new palm cover
*						with valid efl_util_gesture_h.
* @scenario				Initialize gesture API efl_util_gesture_initialize and generates a
*						palm cover gesture's grab info handle and then free it.
* @apicovered			efl_util_gesture_palm_cover_new,efl_util_gesture_palm_cover_free
* @passcase				When efl_util_gesture_palm_cover_new,efl_util_gesture_palm_cover_free is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_efl_util_gesture_palm_cover_new_and_free_p(void)
{
	START_TEST;

	int nRetVal = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_palm_cover = NULL;

	h_gesture = efl_util_gesture_initialize();
	CHECK_HANDLE(h_gesture,"efl_util_gesture_initialize");

	nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_initialize", EflUtilGetError(nRetVal),efl_util_gesture_deinitialize(h_gesture));

	d_palm_cover = efl_util_gesture_palm_cover_new(h_gesture);
	CHECK_HANDLE_CLEANUP(d_palm_cover,"efl_util_gesture_palm_cover_new",efl_util_gesture_deinitialize(h_gesture));

	nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_palm_cover_new", EflUtilGetError(nRetVal),efl_util_gesture_palm_cover_free(h_gesture, d_palm_cover);efl_util_gesture_deinitialize(h_gesture));

	nRetVal = efl_util_gesture_palm_cover_free(h_gesture, d_palm_cover);
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_palm_cover_free", EflUtilGetError(nRetVal),efl_util_gesture_deinitialize(h_gesture));

	nRetVal = efl_util_gesture_deinitialize(h_gesture);
	PRINT_RESULT(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_deinitialize", EflUtilGetError(nRetVal));

	return 0;
}


//& purpose: To verify efl_util_gesture_select,efl_util_gesture_deselect.
//Selects a global gesture on given window.
//& type: auto
 /**
* @testcase				ITc_efl_util_gesture_select_deselect_p
* @since_tizen 			4.0
* @author				SRID(bipin.k)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description 			To verify whether ITc_efl_util_gesture_select_deselect_p API is
*						working properly in the case a user requests the gesture select
*						with a palm cover gesture.
* @scenario				Initialize gesture API efl_util_gesture_initialize,efl_util_gesture_palm_cover_new and
*						select a global gesture on given window.
* @apicovered			efl_util_gesture_select,efl_util_gesture_deselect.
* @passcase				When efl_util_gesture_select,efl_util_gesture_deselect is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_efl_util_gesture_select_deselect_p(void)
{
	START_TEST;

	int nRetVal = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	efl_util_gesture_data d_palm_cover = NULL;
	Evas_Object *window = NULL;

	window = CreateNormalWin("Gesture Window");
	CHECK_HANDLE(window,"CreateNormalWin");

	h_gesture = efl_util_gesture_initialize();
	CHECK_HANDLE_CLEANUP(h_gesture,"efl_util_gesture_initialize",evas_object_del(window));

	nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_initialize", EflUtilGetError(nRetVal),evas_object_del(window);efl_util_gesture_deinitialize(h_gesture));

	d_palm_cover = efl_util_gesture_palm_cover_new(h_gesture);
	CHECK_HANDLE_CLEANUP(d_palm_cover,"efl_util_gesture_palm_cover_new",evas_object_del(window);efl_util_gesture_deinitialize(h_gesture));

	nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_palm_cover_new", EflUtilGetError(nRetVal),efl_util_gesture_palm_cover_free(h_gesture,d_palm_cover);evas_object_del(window);efl_util_gesture_deinitialize(h_gesture));

	nRetVal = efl_util_gesture_select(h_gesture, window, d_palm_cover);
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_select", EflUtilGetError(nRetVal),efl_util_gesture_palm_cover_free(h_gesture,d_palm_cover);evas_object_del(window);efl_util_gesture_deinitialize(h_gesture););

	nRetVal = efl_util_gesture_deselect(h_gesture, window, d_palm_cover);
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_deselect", EflUtilGetError(nRetVal),efl_util_gesture_palm_cover_free(h_gesture,d_palm_cover);evas_object_del(window);efl_util_gesture_deinitialize(h_gesture));

	nRetVal = efl_util_gesture_palm_cover_free(h_gesture,d_palm_cover);
	PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_palm_cover_free", EflUtilGetError(nRetVal),evas_object_del(window);efl_util_gesture_deinitialize(h_gesture));

	evas_object_del(window);

	nRetVal = efl_util_gesture_deinitialize(h_gesture);
	PRINT_RESULT(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_deinitialize", EflUtilGetError(nRetVal));

	return 0;
}

//& purpose: To verify efl_util_gesture_activate_set_on_window
//& type: auto
/**
* @testcase				ITc_efl_util_gesture_activate_set_on_window_p
* @since_tizen 			4.0
* @author				SRID(bipin.k)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description 			To verify whether efl_util_gesture_activate_set_on_window API is
*						working properly in the case a user requests the activate
*						with tap gesture.
* @scenario				Initialize gesture API efl_util_gesture_initialize and activating  or deactivating
*						a global gesture on a given window.
* @apicovered			efl_util_gesture_activate_set_on_window.
* @passcase				When efl_util_gesture_activate_set_on_window is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_efl_util_gesture_activate_set_on_window_p(void)
{
	START_TEST;

	int nRetVal = EFL_UTIL_ERROR_NONE;
	efl_util_gesture_h h_gesture = NULL;
	Evas_Object *window = NULL;
	unsigned int type;
	for(int i=1;i<=MAX_VAL;i++)
	{
		window = CreateNormalWin("Gesture Window");
		CHECK_HANDLE(window,"CreateNormalWin");

		h_gesture = efl_util_gesture_initialize();
		CHECK_HANDLE_CLEANUP(h_gesture,"efl_util_gesture_initialize",evas_object_del(window));

		nRetVal = get_last_result();
		PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_initialize", EflUtilGetError(nRetVal), evas_object_del(window);efl_util_gesture_deinitialize(h_gesture));

		type = Values[i];
		nRetVal = efl_util_gesture_activate_set_on_window(h_gesture, window, type, EINA_TRUE);
		PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_activate_set_on_window", EflUtilGetError(nRetVal), evas_object_del(window);efl_util_gesture_deinitialize(h_gesture));

		nRetVal = efl_util_gesture_activate_set_on_window(h_gesture, window, type, EINA_FALSE);
		PRINT_RESULT_CLEANUP(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_activate_set_on_window", EflUtilGetError(nRetVal), evas_object_del(window);efl_util_gesture_deinitialize(h_gesture));

		evas_object_del(window);

		nRetVal = efl_util_gesture_deinitialize(h_gesture);
		PRINT_RESULT(EFL_UTIL_ERROR_NONE, nRetVal, "efl_util_gesture_deinitialize", EflUtilGetError(nRetVal));
	}

	return 0;
}

/** @} */
/** @} */
