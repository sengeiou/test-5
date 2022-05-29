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
#include "ITs-tzsh-quickpanel-common.h"

tzsh_quickpanel_type_e eQuickPanelTypeArray[] = {TZSH_QUICKPANEL_TYPE_UNKNOWN,
								TZSH_QUICKPANEL_TYPE_SYSTEM_DEFAULT,
								TZSH_QUICKPANEL_TYPE_CONTEXT_MENU,
								TZSH_QUICKPANEL_TYPE_APPS_MENU};
/**
 * @function 		ITs_tzsh_quickpanel_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_tzsh_quickpanel_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	elm_init(0, NULL);
	return;
}

/**
 * @function 		ITs_tzsh_quickpanel_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_tzsh_quickpanel_cleanup(void)
{
	elm_shutdown();
	return;
}

/** @addtogroup itc-tzsh-quickpanel-testcases
*  @brief 		Integration testcases for module tzsh-quickpanel
*  @ingroup 	itc-tzsh-quickpanel
*  @{
*/

//& purpose: Creates a instance of tzsh object
//& type : auto
/**
* @testcase 			ITc_tzsh_quickpanel_tzsh_create_destroy_p
* @since_tizen 			3.0
* @author				SRID(shilpa.j)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Creates a instance of tzsh object
* @scenario				create handle\n
* @apicovered			tzsh_create, tzsh_destroy
* @passcase				When API return TZSH_ERROR_NONE
* @failcase				When API not return TZSH_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_tzsh_quickpanel_tzsh_create_destroy_p(void)
{
	tzsh_h htzsh = NULL;
	int nRet = 0;

	START_TEST;
	htzsh = tzsh_create(TZSH_TOOLKIT_TYPE_UNKNOWN);
	CHECK_HANDLE(htzsh, "tzsh_create");

	nRet = tzsh_destroy(htzsh);
	PRINT_RESULT(TZSH_ERROR_NONE, nRet, "tzsh_destroy", TzshQuickpanelGetError(nRet));

	return 0;
}

//& purpose: Creates a quick panel object for a specific type which handles quick-panel services
//& type : auto
/**
* @testcase 			ITc_tzsh_quickpanel_panel_create_destroy_p
* @since_tizen 			3.0
* @author				SRID(shilpa.j)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Creates a quick panel object for a specific type which handles quick-panel services
* @scenario				create an elm window\n
						create tzsh handle\n
						create quick-panel handle\n
* @apicovered			tzsh_create, tzsh_destroy,tzsh_quickpanel_create_with_type,tzsh_quickpanel_destroy
* @passcase				When API return TZSH_ERROR_NONE
* @failcase				When API not return TZSH_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_tzsh_quickpanel_panel_create_destroy_p(void)
{
	Evas_Object *eWin = NULL;
	tzsh_h htzsh = NULL;
	tzsh_quickpanel_h hpanel = NULL;
	tzsh_window tzWin = 0;
	int nRet = 0;
	START_TEST;
	eWin = CreateWindow("quickpanel client");
	CHECK_HANDLE(eWin, "CreateWindow failed");

	evas_object_show(eWin);
	int nSize = sizeof(eQuickPanelTypeArray)/sizeof(eQuickPanelTypeArray[0]);

	tzWin = elm_win_window_id_get(eWin);
	if(tzWin <=0)
	{
		FPRINTF("\\n[Line : %d][%s]elm_win_window_id_get error returned negative  value for elm_win_window_id_get",__LINE__, API_NAMESPACE);
		return 1;
	}

	htzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
	CHECK_HANDLE(htzsh, "tzsh_create");

	for(int nCounter = 1; nCounter < nSize; nCounter++)
	{
		//Target API
		hpanel = tzsh_quickpanel_create_with_type(htzsh, tzWin, eQuickPanelTypeArray[nCounter]);
		CHECK_HANDLE_CLEANUP(hpanel, "tzsh_quickpanel_create_with_type",tzsh_destroy(htzsh));

		//Target API
		nRet = tzsh_quickpanel_destroy(hpanel);
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_destroy", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh));
	}

	nRet = tzsh_destroy(htzsh);
	PRINT_RESULT_NORETURN(TZSH_ERROR_NONE, nRet, "tzsh_destroy", TzshQuickpanelGetError(nRet));

	return 0;
}

//& purpose: Shows the quickpanel service window
//& type : auto
/**
* @testcase 			ITc_tzsh_quickpanel_panel_show_hide_p
* @since_tizen 			3.0
* @author				SRID(shilpa.j)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Shows the quickpanel service window
* @scenario				create an elm window
						create tzsh handle
						create quick-panel handle
						Shows the quickpanel service window
* @apicovered			tzsh_quickpanel_show,tzsh_quickpanel_hide,tzsh_create, tzsh_destroy,tzsh_quickpanel_create_with_type,tzsh_quickpanel_destroy
* @passcase				When API return TZSH_ERROR_NONE
* @failcase				When API not return TZSH_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_tzsh_quickpanel_panel_show_hide_p(void)
{
	Evas_Object *eWin = NULL;
	tzsh_h htzsh = NULL;
	tzsh_quickpanel_h hpanel = NULL;
	tzsh_window tzWin = 0;

	START_TEST;
	eWin = CreateWindow("quickpanel client");
	CHECK_HANDLE(eWin, "CreateWindow failed");

	evas_object_show(eWin);

	tzWin = elm_win_window_id_get(eWin);
	if(tzWin <=0)
	{
		FPRINTF("\\n[Line : %d][%s]elm_win_window_id_get error returned negative  value for elm_win_window_id_get",__LINE__, API_NAMESPACE);
		return 1;
	}

	htzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
	CHECK_HANDLE(htzsh, "tzsh_create");

	hpanel = tzsh_quickpanel_create_with_type(htzsh, tzWin, TZSH_QUICKPANEL_TYPE_SYSTEM_DEFAULT);
	CHECK_HANDLE_CLEANUP(hpanel, "tzsh_quickpanel_create_with_type",tzsh_destroy(htzsh));

	//Target API
	int nRet = tzsh_quickpanel_show(hpanel);
	if (nRet != TZSH_ERROR_NO_SERVICE)
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_show", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh);tzsh_quickpanel_destroy(hpanel));
	}
	else
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NO_SERVICE, nRet, "tzsh_quickpanel_show", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh);tzsh_quickpanel_destroy(hpanel));
	}

	//Target API
	 nRet = tzsh_quickpanel_hide(hpanel);
	if (nRet != TZSH_ERROR_NO_SERVICE)
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_hide", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh);tzsh_quickpanel_destroy(hpanel));
	}
	else
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NO_SERVICE, nRet, "tzsh_quickpanel_hide", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh);tzsh_quickpanel_destroy(hpanel));
	}

	usleep(2000000);

	nRet = tzsh_quickpanel_destroy(hpanel);
	PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_destroy", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh));

	nRet = tzsh_destroy(htzsh);
	PRINT_RESULT_NORETURN(TZSH_ERROR_NONE, nRet, "tzsh_destroy", TzshQuickpanelGetError(nRet));

    return 0;
}

//& purpose: Gets the visible state of the quickpanel
//& type : auto
/**
* @testcase 			ITc_tzsh_quickpanel_visible_get_p
* @since_tizen 			3.0
* @author				SRID(shilpa.j)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Gets the visible state of the quickpanel
* @scenario				create an elm window\n
						create tzsh handle\n
						create quick-panel handle\n
						Get the visible state of the quickpanel
* @apicovered			tzsh_quickpanel_visible_get,tzsh_create, tzsh_destroy,tzsh_quickpanel_create_with_type,tzsh_quickpanel_destroy
* @passcase				When API return TZSH_ERROR_NONE
* @failcase				When API not return TZSH_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_tzsh_quickpanel_visible_get_p(void)
{
	Evas_Object *eWin = NULL;
	tzsh_h htzsh = NULL;
	tzsh_quickpanel_h hpanel = NULL;
	tzsh_window tzWin = 0;
	tzsh_quickpanel_state_visible_e tzsh_state = -1;

	START_TEST;
	eWin = CreateWindow("quickpanel client");
	CHECK_HANDLE(eWin, "CreateWindow failed");

	evas_object_show(eWin);

	tzWin = elm_win_window_id_get(eWin);
	if(tzWin <=0)
	{
		FPRINTF("\\n[Line : %d][%s]elm_win_window_id_get error returned negative  value for elm_win_window_id_get",__LINE__, API_NAMESPACE);
		return 1;
	}

	htzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
	CHECK_HANDLE(htzsh, "tzsh_create");

	hpanel = tzsh_quickpanel_create_with_type(htzsh, tzWin, TZSH_QUICKPANEL_TYPE_SYSTEM_DEFAULT);
	CHECK_HANDLE_CLEANUP(hpanel, "tzsh_quickpanel_create_with_type",tzsh_destroy(htzsh));

	int nRet = tzsh_quickpanel_show(hpanel);
	if (nRet != TZSH_ERROR_NO_SERVICE)
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_show", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh);tzsh_quickpanel_destroy(hpanel));
	}
	else
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NO_SERVICE, nRet, "tzsh_quickpanel_show", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh);tzsh_quickpanel_destroy(hpanel));
	}

	usleep(2000000);
	//Target API
	nRet = tzsh_quickpanel_visible_get(hpanel,&tzsh_state);
	if (nRet != TZSH_ERROR_NO_SERVICE)
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_visible_get", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh);tzsh_quickpanel_destroy(hpanel));
		if(tzsh_state != TZSH_QUICKPANEL_STATE_VISIBLE_SHOWN)
		{
			FPRINTF("\\n[Line : %d][%s]tzsh_quickpanel_visible_get error returned wrong value for state",__LINE__, API_NAMESPACE);
			tzsh_quickpanel_destroy(hpanel);
			tzsh_destroy(htzsh);
			return 1;
		}
	}
	else
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NO_SERVICE, nRet, "tzsh_quickpanel_visible_get", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh);tzsh_quickpanel_destroy(hpanel));
	}

	nRet = tzsh_quickpanel_destroy(hpanel);
	PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_destroy", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh));

	nRet = tzsh_destroy(htzsh);
	PRINT_RESULT_NORETURN(TZSH_ERROR_NONE, nRet, "tzsh_destroy", TzshQuickpanelGetError(nRet));

    return 0;
}

//& purpose: Gets the orientation of the quickpanel
//& type : auto
/**
* @testcase 			ITc_tzsh_quickpanel_orientation_get_p
* @since_tizen 			3.0
* @author				SRID(shilpa.j)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Gets the orientation of the quickpanel
* @scenario				create an elm window\n
						create tzsh handle\n
						create quick-panel handle\n
						Get the visible state of the quickpanel
* @apicovered			tzsh_quickpanel_orientation_get,tzsh_create, tzsh_destroy,tzsh_quickpanel_create_with_type,tzsh_quickpanel_destroy
* @passcase				When API return TZSH_ERROR_NONE
* @failcase				When API not return TZSH_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_tzsh_quickpanel_orientation_get_p(void)
{
	Evas_Object *eWin = NULL;
	tzsh_h htzsh = NULL;
	tzsh_quickpanel_h hpanel = NULL;
	tzsh_window tzWin = 0;
	tzsh_quickpanel_state_orientation_e tzsh_state = -1;

	START_TEST;
	eWin = CreateWindow("quickpanel client");
	CHECK_HANDLE(eWin, "CreateWindow failed");

	evas_object_show(eWin);

	tzWin = elm_win_window_id_get(eWin);
	if(tzWin <=0)
	{
		FPRINTF("\\n[Line : %d][%s]elm_win_window_id_get error returned negative  value for elm_win_window_id_get",__LINE__, API_NAMESPACE);
		return 1;
	}

	htzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
	CHECK_HANDLE(htzsh, "tzsh_create");

	hpanel = tzsh_quickpanel_create_with_type(htzsh, tzWin, TZSH_QUICKPANEL_TYPE_SYSTEM_DEFAULT);
	CHECK_HANDLE_CLEANUP(hpanel, "tzsh_quickpanel_create_with_type",tzsh_destroy(htzsh));

	//Target API
	int nRet = tzsh_quickpanel_orientation_get(hpanel,&tzsh_state);
	if (nRet != TZSH_ERROR_NO_SERVICE)
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_orientation_get", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh);tzsh_quickpanel_destroy(hpanel));
		if(tzsh_state != TZSH_QUICKPANEL_STATE_ORIENTATION_0)
		{
			FPRINTF("\\n[Line : %d][%s]tzsh_quickpanel_orientation_get error returned wrong value for state",__LINE__, API_NAMESPACE);
			tzsh_quickpanel_destroy(hpanel);
			tzsh_destroy(htzsh);
			return 1;
		}
	}
	else
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NO_SERVICE, nRet, "tzsh_quickpanel_orientation_get", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh);tzsh_quickpanel_destroy(hpanel));
	}

	nRet = tzsh_quickpanel_destroy(hpanel);
	PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_destroy", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh));

	nRet = tzsh_destroy(htzsh);
	PRINT_RESULT_NORETURN(TZSH_ERROR_NONE, nRet, "tzsh_destroy", TzshQuickpanelGetError(nRet));

	return 0;
}

static void tzsh_quickpanel_VisibleCallback(int type, tzsh_quickpanel_event_info_h ev_info, void *data)
{
	tzsh_quickpanel_state_visible_e eState;
	FPRINTF("[Line : %d][%s] Inside callback \"tzsh_quickpanel_VisibleCallback\"\\n", __LINE__, API_NAMESPACE);

	if (type != TZSH_QUICKPANEL_EVENT_VISIBLE)
		 return;

	int nRet = tzsh_quickpanel_event_visible_get(ev_info, &eState);
	if(nRet != TZSH_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] Inside callback \"tzsh_quickpanel_event_visible_get failed\"\\n", __LINE__, API_NAMESPACE);
	}
}

//& purpose: Adds the  event handler
//& type : auto
/**
* @testcase 			ITc_tzsh_quickpanel_event_handler_Visible_add_delete_get_p
* @since_tizen 			3.0
* @author				SRID(shilpa.j)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Adds the event handler
* @scenario				create an elm window\n
						create tzsh handle\n
						create quick-panel handle\n
						Adds the event handler
* @apicovered			tzsh_quickpanel_event_handler_add,tzsh_quickpanel_event_visible_get,tzsh_quickpanel_event_handler_del,tzsh_create, tzsh_destroy,tzsh_quickpanel_create_with_type,tzsh_quickpanel_destroy
* @passcase				When API return TZSH_ERROR_NONE
* @failcase				When API not return TZSH_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_tzsh_quickpanel_event_handler_Visible_add_delete_get_p(void)
{
	Evas_Object *eWin = NULL;
	tzsh_h htzsh = NULL;
	tzsh_quickpanel_h hpanel = NULL;
	tzsh_window tzWin = 0;
	tzsh_quickpanel_event_handler_h hEventHandler;

	START_TEST;

	eWin = CreateWindow("quickpanel client");
	CHECK_HANDLE(eWin, "CreateWindow failed");

	evas_object_show(eWin);

	tzWin = elm_win_window_id_get(eWin);
	if(tzWin <=0)
	{
		FPRINTF("\\n[Line : %d][%s]elm_win_window_id_get error returned negative  value for elm_win_window_id_get",__LINE__, API_NAMESPACE);
		return 1;
	}

	htzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
	CHECK_HANDLE(htzsh, "tzsh_create");

	hpanel = tzsh_quickpanel_create_with_type(htzsh, tzWin, TZSH_QUICKPANEL_TYPE_SYSTEM_DEFAULT);
	CHECK_HANDLE_CLEANUP(hpanel, "tzsh_quickpanel_create_with_type",tzsh_destroy(htzsh));

	int  nRet = tzsh_quickpanel_show(hpanel);
	if (nRet != TZSH_ERROR_NO_SERVICE)
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_show", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh);tzsh_quickpanel_destroy(hpanel));
	}
	else
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NO_SERVICE, nRet, "tzsh_quickpanel_show", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh);tzsh_quickpanel_destroy(hpanel));
	}

	//Target API
	hEventHandler = tzsh_quickpanel_event_handler_add(hpanel, TZSH_QUICKPANEL_EVENT_VISIBLE, tzsh_quickpanel_VisibleCallback, NULL);

	CHECK_HANDLE_CLEANUP(hEventHandler, "tzsh_quickpanel_event_handler_add",tzsh_quickpanel_destroy(hpanel);tzsh_destroy(htzsh));

	nRet = tzsh_quickpanel_event_handler_del(hpanel, hEventHandler);
	PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_event_handler_del", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh);tzsh_quickpanel_destroy(hpanel));

	nRet = tzsh_quickpanel_destroy(hpanel);
	PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_destroy", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh));

	nRet = tzsh_destroy(htzsh);
	PRINT_RESULT_NORETURN(TZSH_ERROR_NONE, nRet, "tzsh_destroy", TzshQuickpanelGetError(nRet));

	return 0;
}

static void tzsh_quickpanel_OrientationCallback(int type, tzsh_quickpanel_event_info_h ev_info, void *data)
{
	tzsh_quickpanel_state_orientation_e eState;
	FPRINTF("[Line : %d][%s] Inside callback \"tzsh_quickpanel_VisibleCallback\"\\n", __LINE__, API_NAMESPACE);

	if (type != TZSH_QUICKPANEL_EVENT_ORIENTATION)
		return;
	int nRet = tzsh_quickpanel_event_orientation_get(ev_info, &eState);

	if(nRet != TZSH_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] Inside callback \"tzsh_quickpanel_event_orientation_get failed\"\\n", __LINE__, API_NAMESPACE);
	}
}

//& purpose: Adds the  event handler
//& type : auto
/**
* @testcase 			ITc_tzsh_quickpanel_event_handler_Orientation_add_delete_get_p
* @since_tizen 			3.0
* @author				SRID(shilpa.j)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Adds the event handler
* @scenario				create an elm window\n
						create tzsh handle\n
						create quick-panel handle\n
						Adds the event handler
* @apicovered			tzsh_quickpanel_event_handler_add,tzsh_quickpanel_event_visible_get,tzsh_quickpanel_event_handler_del,tzsh_create, tzsh_destroy,tzsh_quickpanel_create_with_type,tzsh_quickpanel_destroy
* @passcase				When API return TZSH_ERROR_NONE
* @failcase				When API not return TZSH_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_tzsh_quickpanel_event_handler_orientation_add_delete_get_p(void)
{
	Evas_Object *eWin = NULL;
	tzsh_h htzsh = NULL;
	tzsh_quickpanel_h hpanel = NULL;
	tzsh_window tzWin = 0;
	tzsh_quickpanel_event_handler_h hEventHandler;

	START_TEST;

	eWin = CreateWindow("quickpanel client");
	CHECK_HANDLE(eWin, "CreateWindow failed");

	evas_object_show(eWin);

	tzWin = elm_win_window_id_get(eWin);
	if(tzWin <=0)
	{
		FPRINTF("\\n[Line : %d][%s]elm_win_window_id_get error returned negative  value for elm_win_window_id_get",__LINE__, API_NAMESPACE);
		return 1;
	}

	htzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
	CHECK_HANDLE(htzsh, "tzsh_create");

	hpanel = tzsh_quickpanel_create_with_type(htzsh, tzWin, TZSH_QUICKPANEL_TYPE_SYSTEM_DEFAULT);
	CHECK_HANDLE_CLEANUP(hpanel, "tzsh_quickpanel_create_with_type",tzsh_destroy(htzsh));

	//Target API
	hEventHandler = tzsh_quickpanel_event_handler_add(hpanel, TZSH_QUICKPANEL_EVENT_ORIENTATION, tzsh_quickpanel_OrientationCallback, NULL);
	CHECK_HANDLE_CLEANUP(hEventHandler, "tzsh_quickpanel_event_handler_add",tzsh_quickpanel_destroy(hpanel);tzsh_destroy(htzsh));

	int nRet = tzsh_quickpanel_event_handler_del(hpanel, hEventHandler);
	PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_event_handler_del", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh);tzsh_quickpanel_destroy(hpanel));

	nRet = tzsh_quickpanel_destroy(hpanel);
	PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_destroy", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh));

	nRet = tzsh_destroy(htzsh);
	PRINT_RESULT_NORETURN(TZSH_ERROR_NONE, nRet, "tzsh_destroy", TzshQuickpanelGetError(nRet));

	return 0;
}

//& purpose: Gets the type of the quickpanel
//& type : auto
/**
* @testcase 			ITc_tzsh_quickpanel_type_get_p
* @since_tizen 			5.5
* @author				SRID(kanchan.m)
* @reviewer				SRID(priya.kohli)
* @type 				auto
* @description			Gets the type of the quickpanel
* @scenario				create an elm window\n
						create tzsh handle\n
						create quick-panel handle\n
						Get the type of the quickpanel
* @apicovered			tzsh_quickpanel_type_get,tzsh_create, tzsh_destroy,tzsh_quickpanel_create_with_type,tzsh_quickpanel_destroy
* @passcase				When API return TZSH_ERROR_NONE
* @failcase				When API not return TZSH_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_tzsh_quickpanel_type_get_p(void)
{
	Evas_Object *eWin = NULL;
	tzsh_h htzsh = NULL;
	tzsh_quickpanel_h hpanel = NULL;
	tzsh_window tzWin = 0;
	tzsh_quickpanel_type_e tzsh_type = -1;
	int nRet = 0;
	START_TEST;
	eWin = CreateWindow("quickpanel client");
	CHECK_HANDLE(eWin, "CreateWindow failed");

	evas_object_show(eWin);
	int nSize = sizeof(eQuickPanelTypeArray)/sizeof(eQuickPanelTypeArray[0]);

	tzWin = elm_win_window_id_get(eWin);
	if(tzWin <=0)
	{
		FPRINTF("\\n[Line : %d][%s]elm_win_window_id_get error returned negative value for elm_win_window_id_get",__LINE__, API_NAMESPACE);
		return 1;
	}

	htzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
	CHECK_HANDLE(htzsh, "tzsh_create");

	for(int nCounter = 1; nCounter < nSize; nCounter++)
	{
		hpanel = tzsh_quickpanel_create_with_type(htzsh, tzWin, eQuickPanelTypeArray[nCounter]);
		CHECK_HANDLE_CLEANUP(hpanel, "tzsh_quickpanel_create_with_type", tzsh_destroy(htzsh));

		//Target API
		nRet = tzsh_quickpanel_type_get(hpanel, &tzsh_type);
		if (nRet != TZSH_ERROR_NO_SERVICE)
		{
			PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_type_get", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh);tzsh_quickpanel_destroy(hpanel));
			if(tzsh_type != eQuickPanelTypeArray[nCounter])
			{
				FPRINTF("\\n[Line : %d][%s]tzsh_quickpanel_type_get error returned wrong value for type",__LINE__, API_NAMESPACE);
				tzsh_quickpanel_destroy(hpanel);
				tzsh_destroy(htzsh);
				return 1;
			}
		}
		else
		{
			PRINT_RESULT_CLEANUP(TZSH_ERROR_NO_SERVICE, nRet, "tzsh_quickpanel_type_get", TzshQuickpanelGetError(nRet),tzsh_destroy(htzsh);tzsh_quickpanel_destroy(hpanel));
		}

	nRet = tzsh_quickpanel_destroy(hpanel);
	PRINT_RESULT_NORETURN(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_destroy", TzshQuickpanelGetError(nRet));
	}

	nRet = tzsh_destroy(htzsh);
	PRINT_RESULT_NORETURN(TZSH_ERROR_NONE, nRet, "tzsh_destroy", TzshQuickpanelGetError(nRet));

    return 0;
}

//& purpose: Sets and  Gets the window's scrollable state of the quickpanel service window.
//& type : auto
/**
* @testcase		ITc_tzsh_quickpanel_scrollable_state_set_get_p
* @since_tizen		5.5
* @author		SRID(j.abhishek)
* @reviewer		SRID(shobhit.v)
* @type		auto
* @description		Sets and Gets the window's scrollable state of the quickpanel service window.
* @scenario		create an elm window\n
			create tzsh handle\n
			create quick-panel handle\n
			Sets the scrollable state of the quickpanel service window and get back
* @apicovered		tzsh_quickpanel_scrollable_state_set, tzsh_quickpanel_scrollable_state_get,\n
			tzsh_create, tzsh_destroy, tzsh_quickpanel_create, tzsh_quickpanel_destroy
* @passcase		When API return TZSH_ERROR_NONE and get state is same as set state
* @failcase		When API not return TZSH_ERROR_NONE
* @precondition	None
* @postcondition	None
*/
int ITc_tzsh_quickpanel_scrollable_state_set_get_p(void)
{
	START_TEST;

	Evas_Object *eWin = NULL;
	tzsh_h htzsh = NULL;
	tzsh_quickpanel_h hQuickPanel = NULL;
	tzsh_window tzWin = 0;
	int nRet = -1;
	tzsh_quickpanel_state_scrollable_e eQPScrollableState;

	eWin = CreateWindow("quickpanel client");
	CHECK_HANDLE(eWin, "CreateWindow failed");

	evas_object_show(eWin);
	tzWin = elm_win_window_id_get(eWin);

	htzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
	CHECK_HANDLE(htzsh, "tzsh_create");

	hQuickPanel = tzsh_quickpanel_create(htzsh, tzWin);
	CHECK_HANDLE_CLEANUP(hQuickPanel, "tzsh_quickpanel_create", tzsh_destroy(htzsh));

	//Target API
	nRet = tzsh_quickpanel_scrollable_state_set(hQuickPanel, TZSH_QUICKPANEL_STATE_SCROLLABLE_SET);
	if (nRet != TZSH_ERROR_NO_SERVICE)
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_scrollable_state_set", TzshQuickpanelGetError(nRet), tzsh_destroy(htzsh); tzsh_quickpanel_destroy(hQuickPanel));
	}
	else
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NO_SERVICE, nRet, "tzsh_quickpanel_scrollable_state_set", TzshQuickpanelGetError(nRet), tzsh_destroy(htzsh); tzsh_quickpanel_destroy(hQuickPanel));
	}
	//Target API
	nRet = tzsh_quickpanel_scrollable_state_get(hQuickPanel, &eQPScrollableState);
	if (nRet != TZSH_ERROR_NO_SERVICE)
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_scrollable_state_get", TzshQuickpanelGetError(nRet), tzsh_destroy(htzsh); tzsh_quickpanel_destroy(hQuickPanel));
		PRINT_RESULT_CLEANUP(TZSH_QUICKPANEL_STATE_SCROLLABLE_SET, eQPScrollableState, "tzsh_quickpanel_scrollable_state_get", TzshQuickpanelGetError(nRet), tzsh_destroy(htzsh); tzsh_quickpanel_destroy(hQuickPanel));
	}
	else
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NO_SERVICE, nRet, "tzsh_quickpanel_scrollable_state_get", TzshQuickpanelGetError(nRet), tzsh_destroy(htzsh); tzsh_quickpanel_destroy(hQuickPanel));
	}

	//Target API
	nRet = tzsh_quickpanel_scrollable_state_set(hQuickPanel, TZSH_QUICKPANEL_STATE_SCROLLABLE_UNSET);
	if (nRet != TZSH_ERROR_NO_SERVICE)
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_scrollable_state_set", TzshQuickpanelGetError(nRet), tzsh_destroy(htzsh); tzsh_quickpanel_destroy(hQuickPanel));
	}
	else
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NO_SERVICE, nRet, "tzsh_quickpanel_scrollable_state_set", TzshQuickpanelGetError(nRet), tzsh_destroy(htzsh); tzsh_quickpanel_destroy(hQuickPanel));
	}
	//Target API
	nRet = tzsh_quickpanel_scrollable_state_get(hQuickPanel, &eQPScrollableState);
	if (nRet != TZSH_ERROR_NO_SERVICE)
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_scrollable_state_get", TzshQuickpanelGetError(nRet), tzsh_destroy(htzsh); tzsh_quickpanel_destroy(hQuickPanel));
		PRINT_RESULT_CLEANUP(TZSH_QUICKPANEL_STATE_SCROLLABLE_UNSET, eQPScrollableState, "tzsh_quickpanel_scrollable_state_get", TzshQuickpanelGetError(nRet), tzsh_destroy(htzsh); tzsh_quickpanel_destroy(hQuickPanel));
	}
	else
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NO_SERVICE, nRet, "tzsh_quickpanel_scrollable_state_get", TzshQuickpanelGetError(nRet), tzsh_destroy(htzsh); tzsh_quickpanel_destroy(hQuickPanel));
	}

	//Target API
	nRet = tzsh_quickpanel_scrollable_state_set(hQuickPanel, TZSH_QUICKPANEL_STATE_SCROLLABLE_RETAIN);
	if (nRet != TZSH_ERROR_NO_SERVICE)
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_scrollable_state_set", TzshQuickpanelGetError(nRet), tzsh_destroy(htzsh); tzsh_quickpanel_destroy(hQuickPanel));
	}
	else
	{
		PRINT_RESULT_CLEANUP(TZSH_ERROR_NO_SERVICE, nRet, "tzsh_quickpanel_scrollable_state_set", TzshQuickpanelGetError(nRet), tzsh_destroy(htzsh); tzsh_quickpanel_destroy(hQuickPanel));
	}

	//cleanup resource
	nRet = tzsh_quickpanel_destroy(hQuickPanel);
	PRINT_RESULT_NORETURN(TZSH_ERROR_NONE, nRet, "tzsh_quickpanel_destroy", TzshQuickpanelGetError(nRet));

	nRet = tzsh_destroy(htzsh);
	PRINT_RESULT_NORETURN(TZSH_ERROR_NONE, nRet, "tzsh_destroy", TzshQuickpanelGetError(nRet));

	return 0;
}

/** @} */
/** @} */
