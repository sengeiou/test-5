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
#include "ITs-screen-mirroring-common.h"

#define PACKAGE "screen_mirroring_sink_test"

/** @addtogroup itc-screen-mirroring
*  @ingroup itc
*  @{
*/

scmirroring_sink_h g_hScMirroringSink = NULL;

static Evas_Object* g_evas;
static Evas_Object* _create_win(const char *name);
static void create_win();
static void _win_del(void *data, Evas_Object *obj, void *event);
static void create_render_rect_and_bg(Evas_Object *win);

static void create_win()
{
	Evas_Object *win = NULL;
	/* create window */
	win = _create_win(PACKAGE);
	g_evas = win;
	create_render_rect_and_bg(g_evas);

	elm_win_activate(win);
	evas_object_show(win);
}

void create_render_rect_and_bg(Evas_Object *win)
{
	if (!win) {
		g_print("no win");
		return;
	}
	Evas_Object *bg, *rect;

	bg = elm_bg_add(win);
	elm_win_resize_object_add(win, bg);
	evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(bg);

	rect = evas_object_rectangle_add(evas_object_evas_get(win));
	if (!rect) {
		g_print("no rect");
		return;
	}
	evas_object_color_set(rect, 0, 0, 0, 0);
	evas_object_render_op_set(rect, EVAS_RENDER_COPY);

	elm_win_resize_object_add(win, rect);
	evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(rect);
	evas_object_show(win);
}

static Evas_Object* _create_win(const char *name)
{
	Evas_Object *eo = NULL;
	int w = 0;
	int h = 0;

	eo = elm_win_add(NULL, name, ELM_WIN_BASIC);
	if (eo) {
		elm_win_title_set(eo, name);
		elm_win_borderless_set(eo, EINA_TRUE);
		evas_object_smart_callback_add(eo, "delete,request", _win_del, NULL);
		elm_win_autodel_set(eo, EINA_TRUE);
		elm_win_screen_size_get(eo, NULL, NULL, &w, &h);
		elm_win_alpha_set(eo, EINA_TRUE);
	}
	return eo;
}

static void _win_del(void *data, Evas_Object *obj, void *event)
{
	elm_exit();
}
/**
* @function 		scmirroring_state_sink_callback
* @description	 	Callback function to indicate sink state
* @parameter		scmirroring_error_e error_code, scmirroring_state_e state, void *user_data
* @return 			NA
*/
void scmirroring_state_sink_callback(scmirroring_error_e error_code, scmirroring_sink_state_e state, void *user_data)
{
	FPRINTF("Received Callback error code=[%d]", error_code);

	if ( state == SCMIRRORING_SINK_STATE_NONE )
	{
		FPRINTF(" state[%d] SCMIRRORING_SINK_STATE_NONE", state);
	}
	else if (state == SCMIRRORING_SINK_STATE_NULL )
	{
		FPRINTF(" state[%d] SCMIRRORING_SINK_STATE_NULL", state);
	}
	else if ( state == SCMIRRORING_SINK_STATE_PREPARED )
	{
		FPRINTF(" state[%d] SCMIRRORING_SINK_STATE_PREPARED", state);
	}
	else if ( state == SCMIRRORING_SINK_STATE_CONNECTED )
	{
		FPRINTF(" state[%d] SCMIRRORING_SINK_STATE_CONNECTED", state);
	}
	else if ( state == SCMIRRORING_SINK_STATE_PLAYING )
	{
		FPRINTF(" state[%d] SCMIRRORING_SINK_STATE_PLAYING", state);
	}
	else if ( state == SCMIRRORING_SINK_STATE_PAUSED )
	{
		FPRINTF(" state[%d] SCMIRRORING_SINK_STATE_PAUSED", state);
	}
	else if ( state == SCMIRRORING_SINK_STATE_DISCONNECTED )
	{
		FPRINTF(" state[%d] SCMIRRORING_SINK_STATE_DISCONNECTED", state);
	}
	else if ( state == SCMIRRORING_SINK_STATE_MAX )
	{
		FPRINTF(" state[%d] SCMIRRORING_SINK_STATE_MAX", state);
	}
	else
	{
		FPRINTF(" state[%d] Invalid State", state);
	}

	return;
}

/**
 * @function 		ITs_screen_mirroring_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_screen_mirroring_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Screen_Mirroring_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bIsFeatureSupported = true;
	g_bIsFeatureSupportMismatch = false;

	IS_FEATURE_SUPPORTED(SCREEN_MIRRORING_WIFI_DIRECT_FEATURE, g_bIsFeatureSupported, API_NAMESPACE);
	
	int nRet = scmirroring_sink_create(&g_hScMirroringSink);
	
	if ( nRet != SCMIRRORING_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "scmirroring_sink_create", ScreenMirroringInfoGetError(nRet), nRet);
		return;
	}
	
	if ( g_hScMirroringSink == NULL )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, "scmirroring_sink_create");
		return;
	}
	
	return;
}

/**
 * @function 		ITs_screen_mirroring_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_screen_mirroring_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Screen_Mirroring_p\\n", __LINE__, API_NAMESPACE);
#endif
	int nRet = 0;
		
	if ( g_hScMirroringSink != NULL )
	{
		nRet = scmirroring_sink_destroy(g_hScMirroringSink);
		if ( nRet != SCMIRRORING_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "scmirroring_sink_destroy", ScreenMirroringInfoGetError(nRet), nRet);
			return;
		}
	}
	return;
}

//& purpose: set sink IP and Port
//& type: auto
/**
* @testcase 				ITc_scmirroring_sink_set_ip_and_port_p
* @since_tizen 				2.4
* @owner					SRID(nibha.sharma)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				set sink IP and Port
* @scenario					scmirroring_sink_create\n
*							scmirroring_sink_set_ip_and_port
* @apicovered				scmirroring_sink_set_ip_and_port
* @passcase					When scmirroring_sink_set_ip_and_port is successful and return valid data.
* @failcase					If target API fails or return invalid value.
* @precondition				None
* @postcondition			None
*/
int ITc_scmirroring_sink_set_ip_and_port_p(void)
{
	START_TEST;

	const char * ip = "192.168.49.1";
	const char* port = "2022";

	int nRet = scmirroring_sink_set_ip_and_port(g_hScMirroringSink,ip,port);
	PRINT_RESULT(SCMIRRORING_ERROR_NONE, nRet, "scmirroring_sink_set_ip_and_port", ScreenMirroringInfoGetError(nRet));

	return 0;
}

//& purpose: set display for sink
//& type: auto
/**
* @testcase 				ITc_scmirroring_sink_set_display_p
* @since_tizen 				2.4
* @owner					SRID(nibha.sharma)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				set display for sink
* @scenario					scmirroring_sink_create\n
*							scmirroring_sink_set_display
* @apicovered				scmirroring_sink_create, scmirroring_sink_destroy, scmirroring_sink_set_display
* @passcase					When scmirroring_sink_set_display is successful and return valid data.
* @failcase					If target API fails or return invalid value.
* @precondition				None
* @postcondition			None
*/
int ITc_scmirroring_sink_set_display_p(void)
{
	START_TEST;

	scmirroring_sink_h hSkMirroring = NULL;
	scmirroring_display_type_e setDisp[] = {SCMIRRORING_DISPLAY_TYPE_OVERLAY, SCMIRRORING_DISPLAY_TYPE_EVAS, SCMIRRORING_DISPLAY_TYPE_MAX};
	int nRet = 0, enum_size = sizeof(setDisp) / sizeof(setDisp), enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		nRet = scmirroring_sink_create(&hSkMirroring);
		PRINT_RESULT(SCMIRRORING_ERROR_NONE, nRet, "scmirroring_sink_create", ScreenMirroringInfoGetError(nRet));
		CHECK_HANDLE(hSkMirroring, "scmirroring_sink_create");
		create_win();
		evas_object_show(g_evas);

		nRet = scmirroring_sink_set_display(hSkMirroring, setDisp[enum_counter], (void *)g_evas);
		PRINT_RESULT_CLEANUP(SCMIRRORING_ERROR_NONE, nRet, "scmirroring_sink_set_display", ScreenMirroringInfoGetError(nRet), scmirroring_sink_destroy(hSkMirroring));

		nRet = scmirroring_sink_destroy(hSkMirroring);
		PRINT_RESULT_NORETURN(SCMIRRORING_ERROR_NONE, nRet, "scmirroring_sink_destroy", ScreenMirroringInfoGetError(nRet));
	}

	return 0;
}

//& purpose: set sink resolution
//& type: auto
/**
* @testcase 				ITc_scmirroring_sink_set_resolution_p
* @since_tizen 				2.4
* @owner					SRID(nibha.sharma)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				set sink resolution
* @scenario					scmirroring_sink_create\n
*							scmirroring_sink_set_resolution
* @apicovered				scmirroring_sink_create, scmirroring_sink_destroy, scmirroring_sink_set_resolution
* @passcase					When scmirroring_sink_set_resolution is successful and return valid data.
* @failcase					If target API fails or return invalid value.
* @precondition				None
* @postcondition			None
*/
int ITc_scmirroring_sink_set_resolution_p(void)
{
	START_TEST;

	scmirroring_sink_h hSkMirroring = NULL;
	scmirroring_resolution_e setResol[] = {SCMIRRORING_RESOLUTION_1920x1080_P30, SCMIRRORING_RESOLUTION_1280x720_P30, SCMIRRORING_RESOLUTION_960x540_P30, SCMIRRORING_RESOLUTION_864x480_P30, SCMIRRORING_RESOLUTION_720x480_P60, SCMIRRORING_RESOLUTION_640x480_P60, SCMIRRORING_RESOLUTION_640x360_P30};
	int nRet = 0, enum_size = sizeof(setResol) / sizeof(setResol[0]), enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		nRet = scmirroring_sink_create(&hSkMirroring);
		PRINT_RESULT(SCMIRRORING_ERROR_NONE, nRet, "scmirroring_sink_create", ScreenMirroringInfoGetError(nRet));
		CHECK_HANDLE(hSkMirroring, "scmirroring_sink_create");

		nRet = scmirroring_sink_set_resolution(hSkMirroring,setResol[enum_counter]);
		PRINT_RESULT_CLEANUP(SCMIRRORING_ERROR_NONE, nRet, "scmirroring_sink_set_resolution", ScreenMirroringInfoGetError(nRet), scmirroring_sink_destroy(hSkMirroring));

		nRet = scmirroring_sink_destroy(hSkMirroring);
		PRINT_RESULT_NORETURN(SCMIRRORING_ERROR_NONE, nRet, "scmirroring_sink_destroy", ScreenMirroringInfoGetError(nRet));
	}
	return 0;
}

//& purpose: sink state set & unset callback
//& type: auto
/**
* @testcase 				ITc_scmirroring_sink_set_unset_state_changed_cb_p
* @since_tizen 				2.4
* @owner					SRID(nibha.sharma)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				sink state set & unset callback
* @scenario					scmirroring_sink_create\n
*							scmirroring_sink_set_state_changed_cb\n
*							scmirroring_sink_unset_state_changed_cb
* @apicovered				scmirroring_sink_set_state_changed_cb, scmirroring_sink_unset_state_changed_cb
* @passcase					When scmirroring_sink_set_state_changed_cb & scmirroring_sink_unset_state_changed_cb is successful and return valid data.
* @failcase					If target API fails or return invalid value.
* @precondition				None
* @postcondition			None
*/
int ITc_scmirroring_sink_set_unset_state_changed_cb_p(void)
{
	START_TEST;

	int nRet = scmirroring_sink_set_state_changed_cb(g_hScMirroringSink, scmirroring_state_sink_callback, NULL);
	PRINT_RESULT(SCMIRRORING_ERROR_NONE, nRet, "scmirroring_sink_set_state_changed_cb", ScreenMirroringInfoGetError(nRet));

	nRet = scmirroring_sink_unset_state_changed_cb(g_hScMirroringSink);
	PRINT_RESULT(SCMIRRORING_ERROR_NONE, nRet, "scmirroring_sink_unset_state_changed_cb", ScreenMirroringInfoGetError(nRet));

	return 0;
}

//& purpose: Create & destroy g_hScMirroringSink
//& type: auto
/**
* @testcase 				ITc_scmirroring_sink_create_destroy_p
* @since_tizen 				2.4
* @owner					SRID(nibha.sharma)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Create & destroy g_hScMirroringSink
* @scenario					scmirroring_sink_create\n
*							scmirroring_sink_destroy
* @apicovered				scmirroring_sink_create,scmirroring_sink_destroy
* @passcase					When scmirroring_sink_create & scmirroring_sink_destroy is successful and return valid data.
* @failcase					If target API fails or return invalid value.
* @precondition				None
* @postcondition			None
*/
int ITc_scmirroring_sink_create_destroy_p(void)
{
	START_TEST;
	scmirroring_sink_h hSkMirroring = NULL;

	int nRet = scmirroring_sink_create(&hSkMirroring);
	PRINT_RESULT(SCMIRRORING_ERROR_NONE, nRet, "scmirroring_sink_create", ScreenMirroringInfoGetError(nRet));
	CHECK_HANDLE(hSkMirroring, "scmirroring_sink_create");

	nRet = scmirroring_sink_destroy(hSkMirroring);
	PRINT_RESULT(SCMIRRORING_ERROR_NONE, nRet, "scmirroring_sink_destroy", ScreenMirroringInfoGetError(nRet));
	return 0;
}

//& purpose: Gets the current state of screen mirroring sink
//& type: auto
/**
* @testcase 				ITc_scmirroring_sink_get_current_state_p
* @since_tizen 				5.0
* @owner					SRID(nibha.sharma)
* @reviewer					SRID(a.pandia1)
* @type 					auto
* @description				Gets the current state of screen mirroring sink
* @scenario					scmirroring_sink_create\n
*							scmirroring_sink_get_current_state\n
*							scmirroring_sink_destroy
* @apicovered				scmirroring_sink_create,scmirroring_sink_get_current_state,scmirroring_sink_destroy
* @passcase					When scmirroring_sink_create,scmirroring_sink_get_current_state & scmirroring_sink_destroy is successful and return valid data.
* @failcase					If target API fails or return invalid value.
* @precondition				None
* @postcondition			None
*/
int ITc_scmirroring_sink_get_current_state_p(void)
{
	START_TEST;
	scmirroring_sink_h hSkMirroring = NULL;
	scmirroring_sink_state_e eGetState;
	char * szStateValue= NULL;

	int nRet = scmirroring_sink_create(&hSkMirroring);
	PRINT_RESULT(SCMIRRORING_ERROR_NONE, nRet, "scmirroring_sink_create", ScreenMirroringInfoGetError(nRet));
	CHECK_HANDLE(hSkMirroring,"scmirroring_sink_create");

	nRet = scmirroring_sink_get_current_state(hSkMirroring, &eGetState);
	PRINT_RESULT(SCMIRRORING_ERROR_NONE, nRet, "scmirroring_sink_get_current_state", ScreenMirroringInfoGetError(nRet));
	szStateValue = ScreenMirroringSinkState(eGetState);

	if(szStateValue == NULL)
	{
		FPRINTF("scmirroring_sink_get_current_state api is Fail.Value of eGetState is NULL");
		scmirroring_sink_destroy(hSkMirroring);
		return 1;
	}

	nRet = scmirroring_sink_destroy(hSkMirroring);
	PRINT_RESULT_NORETURN(SCMIRRORING_ERROR_NONE, nRet, "scmirroring_sink_destroy", ScreenMirroringInfoGetError(nRet));

	return 0;
}

/** @} */
/** @} */
