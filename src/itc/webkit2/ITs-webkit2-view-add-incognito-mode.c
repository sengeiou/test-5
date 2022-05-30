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

#include "ITs-webkit2-common.h"

/** @addtogroup itc-webkit2
*  @ingroup itc
*  @{
*/

/**
* @function 		ITs_webkit_view_add_incognito_mode_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_webkit_view_add_incognito_mode_startup(void)
{
	
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT start-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif

	elm_init(0, NULL);
    ewk_init();
    elm_config_accel_preference_set("opengl");

	return;
}


/**
* @function 		ITs_webkit_view_add_incognito_mode_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_webkit_view_add_incognito_mode_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif
	ewk_shutdown();
    elm_shutdown();
	return;
}

//& type: auto
//& purpose: Test to creates a new EFL web view object in incognito mode
/**
* @testcase 			ITc_webkit_ewk_view_add_in_incognito_mode_p
* @since_tizen			2.3
* @author				SRID(a.pandia1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description	 		Creates a new EFL web view object in incognito mode
* @scenario				Creates a new EFL web view object in incognito mode
* @apicovered			ewk_view_add_in_incognito_mode
* @passcase				If ewk_view_add_in_incognito_mode returns proper Evas_Object 
* @failcase				If target API ewk_view_add_in_incognito_mode doesn't return proper Evas_Object 
* @precondition			NA
* @postcondition		NA
*/
int ITc_webkit_ewk_view_add_in_incognito_mode_p(void)
{
	START_TEST;
	
	Evas_Object* EvasWin = elm_win_add(NULL, "TC Launcher", ELM_WIN_BASIC);
    elm_win_title_set(EvasWin, "TC Launcher");
    Evas* evas = evas_object_evas_get(EvasWin);

    /* Initialization of webview */
    Evas_Object* EvasWebView = ewk_view_add_in_incognito_mode(evas);
	CHECK_HANDLE_CLEANUP(EvasWebView,"ewk_view_add_in_incognito_mode", evas_object_del(EvasWebView);evas_object_del(EvasWin));
	
    evas_object_del(EvasWebView);
    evas_object_del(EvasWin);
    
	return 0;
}

/** @} */
/** @} */