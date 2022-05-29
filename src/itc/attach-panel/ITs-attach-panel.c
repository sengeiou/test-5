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
#include "ITs-attach-panel-common.h"

/** @addtogroup itc-attach_panel
*  @ingroup itc
*  @{
*/

//& set: attach_panel

/**
* @function 		ITs_attach-panel_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 		NA
*/
void ITs_attach_panel_startup(void)
{
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0 )
	{
		int nRet = remove(ERR_LOG);
		PRINT_RESULT_NORETURN(0, nRet, "ITs_attach_panel_startup -remove", "Remove failed for ERR_LOG");
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_attach-panel_startup\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function 		ITs_attach-panel_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 		NA
*/
void ITs_attach_panel_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_attach-panel_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
}


/** @addtogroup itc-attach-panel-testcases
*  @brief 		Integration testcases for module attach-panel
*  @ingroup 	itc-attach-panel
*  @{
*/

//& purpose: To test Show and Hide attach panel without animation
//& type: auto
/**
* @testcase 			ITc_attach_panel_show_hide_without_animation_p
* @since_tizen			4.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			To test Show and Hide attach panel without animation
* @scenario				attach_panel_show_without_animation,attach_panel_hide_without_animation
* @apicovered			attach_panel_show_without_animation,attach_panel_hide_without_animation
* @passcase				When target API is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_attach_panel_show_hide_without_animation_p(void)
{
	START_TEST;

	attach_panel_h hAttachPanel = NULL;
	Evas_Object *win = NULL;
	Evas_Object *conformant = NULL;

	win = elm_win_add(NULL, "Attach Panel Sample", ELM_WIN_BASIC);
	CHECK_HANDLE(win, "elm_win_add");
	evas_object_show(win);		// return type of evas_object_show api is void so no return type check

	conformant = elm_conformant_add(win);
	CHECK_HANDLE(conformant, "elm_conformant_add");

	evas_object_size_hint_weight_set(conformant,  EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);		// return type of evas_object_size_hint_weight_set api is void so no return type check
	elm_win_resize_object_add(win, conformant);		// return type of elm_win_resize_object_add api is void so no return type check
	evas_object_show(conformant);		// return type of evas_object_show api is void so no return type check
	
	bool bAttachFeatureSupported = TCTCheckSystemInfoFeatureSupported(FEATURE_ATTACHPANEL, API_NAMESPACE);
	

	int nRet = attach_panel_create(conformant, &hAttachPanel);
	if ( false == bAttachFeatureSupported)
	{
		if(nRet == TIZEN_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] attach_panel_create API call returned  %s error for unsupported attachpanel feature\\n", __LINE__, API_NAMESPACE, AttachPanelGetError(nRet));
			return 0;
		}
		else
		{
			FPRINTF("[Line : %d][%s] attach_panel_create API call returned  %s error for unsupported attachpanel feature\\n", __LINE__, API_NAMESPACE, AttachPanelGetError(nRet));
			return 1;
		}
	}
	else
	{
		PRINT_RESULT_CLEANUP(ATTACH_PANEL_ERROR_NONE, nRet, "attach_panel_create", AttachPanelGetError(nRet),evas_object_del(conformant);conformant = NULL;evas_object_del(win);win = NULL);
	}

	nRet = attach_panel_add_content_category(hAttachPanel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	PRINT_RESULT_CLEANUP(ATTACH_PANEL_ERROR_NONE, nRet, "attach_panel_add_content_category", AttachPanelGetError(nRet),attach_panel_destroy(hAttachPanel);evas_object_del(conformant);conformant = NULL;evas_object_del(win);win = NULL);
	
	nRet = attach_panel_show_without_animation(hAttachPanel);
	PRINT_RESULT_CLEANUP(ATTACH_PANEL_ERROR_NONE, nRet, "attach_panel_show_without_animation", AttachPanelGetError(nRet),attach_panel_destroy(hAttachPanel);evas_object_del(conformant);conformant = NULL;evas_object_del(win);win = NULL);

	nRet = attach_panel_remove_content_category(hAttachPanel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	PRINT_RESULT_CLEANUP(ATTACH_PANEL_ERROR_NONE, nRet, "attach_panel_remove_content_category", AttachPanelGetError(nRet),attach_panel_destroy(hAttachPanel);evas_object_del(conformant);conformant = NULL;evas_object_del(win);win = NULL);

	nRet = attach_panel_destroy(hAttachPanel);
	PRINT_RESULT_CLEANUP(ATTACH_PANEL_ERROR_NONE, nRet, "attach_panel_destroy", AttachPanelGetError(nRet),evas_object_del(conformant);conformant = NULL;evas_object_del(win);win = NULL);

	evas_object_del(conformant);	// return type of evas_object_del api is void so no return type check
	conformant = NULL;

	evas_object_del(win);	// return type of evas_object_del api is void so no return type check
	win = NULL;

	return 0;
}
/** @} */
/** @} */
