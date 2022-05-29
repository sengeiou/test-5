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
#include "ITs-webkit2-common.h"

/** @addtogroup itc-webkit2
*  @ingroup itc
*  @{
*/



/**
* @function 		Webkit_EFLGetDataPath
* @description	 	Returns the application data path
* @parameter		pAppDataPath: application data path
* @return 			true if succeed else false
*/
bool Webkit_EFLGetDataPath(char* pAppDataPath)
{
	if ( NULL == pAppDataPath )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	memset(pAppDataPath, 0, PATH_LEN);

	char* pPath = NULL;
	pPath = app_get_data_path();
	if ( NULL == pPath )
	{
		FPRINTF("[Line : %d][%s] Unable to get application data path; app_get_data_path returned null value\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	strncpy(pAppDataPath, pPath, PATH_LEN-1);
	FPRINTF("[Line : %d][%s] application data path returned = %s\\n", __LINE__, API_NAMESPACE, pAppDataPath);
	return true;
}

/**
* @function 		Webkit_EFLAppendToAppDataPath
* @description	 	Appends the input string to application data path
* @parameter		pInputPath: path to append to data path; pFinalPath: final resultant path
* @return 			true if succeed else false
*/
bool Webkit_EFLAppendToAppDataPath(char* pInputPath, char* pFinalPath)
{
	if ( NULL == pInputPath || NULL == pFinalPath )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	char pAppDataPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLGetDataPath(pAppDataPath) )
	{
		return false;
	}

	memset(pFinalPath, 0, PATH_LEN);
	strncpy(pFinalPath, pAppDataPath, PATH_LEN-1);
	strncat(pFinalPath, pInputPath, strlen(pInputPath)+1);

	return true;
}

/**
* @function 		Webkit_EFLAppendToDataPathWithFileFormat
* @description	 	Appends the input string to application data path with file extension in the prefix 
* @parameter		pInputPath: path to append to data path; pFinalPath: final resultant path
* @return 			true if succeed else false
*/
bool Webkit_EFLAppendToDataPathWithFileFormat(char* pInputPath, char* pFinalPath)
{
	if ( NULL == pInputPath || NULL == pFinalPath )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	char pFileAppDataPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToAppDataPath(pInputPath, pFileAppDataPath) )
	{
		return false;
	}

	memset(pFinalPath, 0, PATH_LEN);
	strncpy(pFinalPath, "file://", PATH_LEN-1); //file prefix appended
	strncat(pFinalPath, pFileAppDataPath, strlen(pFileAppDataPath)+1);

	FPRINTF("[Line : %d][%s] result path returned = %s\\n", __LINE__, API_NAMESPACE, pFinalPath);

	return true;
}

/**
* @function			Webkit_EFLCreateWebKitView
* @description		Creates WebKit View
* @parameter		none
* @return			true if success else false
*/
bool Webkit_EFLCreateWebKitView()
{
	elm_init(0, NULL);
	ewk_init();

	elm_config_accel_preference_set(PREFERRED_ENGINE);

	objWebkit_EFL_view.window = elm_win_add(NULL, VIEW_WINDOW_NAME, ELM_WIN_BASIC);
	if ( NULL == objWebkit_EFL_view.window )
	{
		FPRINTF("[Line : %d][%s] elm_win_add returns NULL value\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	elm_win_title_set(objWebkit_EFL_view.window, VIEW_WINDOW_NAME);
	objWebkit_EFL_view.evas = evas_object_evas_get(objWebkit_EFL_view.window);
	if ( NULL == objWebkit_EFL_view.evas )
	{
		FPRINTF("[Line : %d][%s] evas_object_evas_get returns NULL value\\n", __LINE__, API_NAMESPACE);
		evas_object_del(objWebkit_EFL_view.window);
		return false;
	}

	objWebkit_EFL_view.background = evas_object_rectangle_add(objWebkit_EFL_view.evas);
	if ( NULL == objWebkit_EFL_view.background )
	{
		FPRINTF("[Line : %d][%s] evas_object_rectangle_add returns NULL value\\n", __LINE__, API_NAMESPACE);
		evas_object_del(objWebkit_EFL_view.window);
		return false;
	}

	evas_object_name_set(objWebkit_EFL_view.background, VIEW_BKG_NAME);
	evas_object_color_set(objWebkit_EFL_view.background, 255, 0, 255, 255);
	evas_object_move(objWebkit_EFL_view.background, 0, 0);
	evas_object_resize(objWebkit_EFL_view.background, DEFAULT_WIDTH_OF_WINDOW, DEFAULT_HEIGHT_OF_WINDOW);
	evas_object_layer_set(objWebkit_EFL_view.background, EVAS_LAYER_MIN);

	objWebkit_EFL_view.webview = ewk_view_add(objWebkit_EFL_view.evas);
	if ( NULL == objWebkit_EFL_view.webview )
	{
		FPRINTF("[Line : %d][%s] ewk_view_add returns NULL value\\n", __LINE__, API_NAMESPACE);
		evas_object_del(objWebkit_EFL_view.window);
		return false;
	}

	evas_object_move(objWebkit_EFL_view.webview, WEBVIEW_MOVE, WEBVIEW_MOVE);
	evas_object_resize(objWebkit_EFL_view.webview, DEFAULT_WIDTH_OF_WINDOW-WEBVIEW_RANGE, DEFAULT_HEIGHT_OF_WINDOW-WEBVIEW_RANGE);

	FPRINTF("[Line : %d][%s] WebkitView created successfully\\n", __LINE__, API_NAMESPACE);

	return true;
}

/**
* @function			Webkit_EFLDestroyWebKitView
* @description		Destroys WebKit View
* @parameter		none
* @return			none
*/
void Webkit_EFLDestroyWebKitView()
{
	if ( objWebkit_EFL_view.webview )
	{
		evas_object_del(objWebkit_EFL_view.webview);
	}

	if ( objWebkit_EFL_view.window )
	{
		evas_object_del(objWebkit_EFL_view.window);
	}
	ewk_shutdown();
	elm_shutdown();
}


/**
* @function			Webkit_EFL_main_loop_begin
* @description		Ecore Main Loop starts
* @parameter[OUT]	none
* @return			NA
*/
void Webkit_EFL_main_loop_begin()
{
	ecore_main_loop_begin();
}

/**
* @function			Webkit_EFL_main_loop_quit
* @description		Ecore Main Loop quits
* @parameter[OUT]	none
* @return			NA
*/
void Webkit_EFL_main_loop_quit()
{
	ecore_main_loop_quit();
}

#if defined(MOBILE) ||  defined(TIZENIOT) || defined(TV)	//Starts MOBILE or TIZENIOT

Ewk_Autofill_Profile* GetEwkAFillProf()
{
	Ewk_Autofill_Profile* profile = ewk_autofill_profile_new();
	if ( NULL == profile )
	{
		return profile;
	}
	
	char id[10];
	snprintf(id, sizeof(id)-1, "%d",TEST_AUTOFILL_PROFILE_ID);
	ewk_autofill_profile_data_set(profile, EWK_PROFILE_ID, id);
	ewk_autofill_profile_data_set(profile, EWK_PROFILE_NAME, TEST_AUTOFILL_PROFILE_NAME);
	ewk_autofill_profile_data_set(profile, EWK_PROFILE_COMPANY, TEST_AUTOFILL_PROFILE_COMPANY);
	ewk_autofill_profile_data_set(profile, EWK_PROFILE_ADDRESS1, TEST_AUTOFILL_PROFILE_ADDRESS1);
	ewk_autofill_profile_data_set(profile, EWK_PROFILE_ADDRESS2, TEST_AUTOFILL_PROFILE_ADDRESS2);
	ewk_autofill_profile_data_set(profile, EWK_PROFILE_CITY_TOWN, TEST_AUTOFILL_PROFILE_CITY_TOWN);
	ewk_autofill_profile_data_set(profile, EWK_PROFILE_STATE_PROVINCE_REGION, TEST_AUTOFILL_PROFILE_STATE_PROVINCE_REGION);
	ewk_autofill_profile_data_set(profile, EWK_PROFILE_ZIPCODE, TEST_AUTOFILL_PROFILE_ZIPCODE);
	ewk_autofill_profile_data_set(profile, EWK_PROFILE_COUNTRY, TEST_AUTOFILL_PROFILE_COUNTRY);
	ewk_autofill_profile_data_set(profile, EWK_PROFILE_PHONE, TEST_AUTOFILL_PROFILE_PHONE);
	ewk_autofill_profile_data_set(profile, EWK_PROFILE_EMAIL, TEST_AUTOFILL_PROFILE_EMAIL);
	return profile;
}
#endif  	//End MOBILE

Eina_Bool timeout_cb_event_loop_wait(void *data)
{
	ecore_main_loop_quit();
	return ECORE_CALLBACK_CANCEL;
}

bool EventLoopWait(double time)
{
	if ( !main_loop_running )
	{
		main_loop_running = true;
		timeout = ecore_timer_add(time, timeout_cb_event_loop_wait, NULL);

		ecore_main_loop_begin();

		if ( timeout )
		{
			ecore_timer_del(timeout);
			timeout = NULL;
		}

		main_loop_running = false;
		return true;
	}

	return false;
}

/** @} */
