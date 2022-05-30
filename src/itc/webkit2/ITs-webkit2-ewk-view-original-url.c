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

static bool isLoadSucceed = false;
/**
* @function 		Webkit_EFL_LoadError
* @description	 	Callback function to get webkit load error info
* @parameter		data : user data,webview : evas object, event_info : event information
* @return 			NA
*/
static void Webkit_EFL_LoadError(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_LoadError occurs\\n", __LINE__, API_NAMESPACE);
	isLoadSucceed = false;
	Webkit_EFL_main_loop_quit();
}

/**
* @function 		Webkit_EFL_LoadFinished
* @description	 	Callback function to get webkit load finish info
* @parameter		data : user data, eObject : evas object, dataFinished : event information
* @return 			NA
*/
static void Webkit_EFL_LoadFinished(void* data, Evas_Object* eObject, void* dataFinished)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_LoadFinished Success\\n", __LINE__, API_NAMESPACE);
	isLoadSucceed = true;
	Webkit_EFL_main_loop_quit();
}

/**
* @function 		ITs_webkit-ewk-view-original_url_startup
* @description	 	Called before each test
* @parameter		NA
* @return 		NA
*/

void ITs_webkit_ewk_view_original_url_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		int ret = remove(ERR_LOG);
		if(ret == -1)
		{
			FPRINTF("[Line: %d][%s] unlinking file name error =%s \\n", __LINE__, API_NAMESPACE,ERR_LOG);
			return;
		}
	}
#if DEBUG
	FPRINTF("[Line: %d][%s]  ITs_webkit_ewk_view_original_url_startup: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

/**
* @function 		ITs_webkit-ewk-view-original_url_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 		NA
*/
void ITs_webkit_ewk_view_original_url_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] ITs_webkit_ewk_view_original_url_cleanup: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
#if defined(MOBILE) || defined(WEARABLE) || defined(TIZENIOT)|| defined(TV)	//Starts MOBILE or WEARABLE or TIZENIOT
//& type: auto
//& purpose: Get the Original URL string of the view object
/**
* @testcase 			ITc_webkit_ewk_view_original_url_p
* @since_tizen			4.0
* @author			SRID(sp.pradhan)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description	 		To get ewk original url
* @scenario			Create Webkit View\n
*				Get Original URL
*				Validate the get values\n
*				Destroy Webkit View
* @apicovered			ewk_view_original_url_get
* @passcase			when ewk_view_original_url_get is successful and return valid URL
* @failcase			If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_webkit_ewk_view_original_url_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_EWK_VIEW_ORIGINAL_URL, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		FPRINTF("[Line : %d][%s] create webkit view failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	isLoadSucceed = false;
	if (EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	Webkit_EFL_main_loop_begin();
	if (isLoadSucceed == false)
	{
		FPRINTF("[Line : %d][%s] Unable to load URL to Web View\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	const char* originalUrl = NULL;
	originalUrl = ewk_view_original_url_get(objWebkit_EFL_view.webview);
	if ( originalUrl == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_view_original_url_get API call returned NULL value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	if ( 0 != strcmp(pPath, originalUrl) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_original_url_get returned wrong value; expected = %s, returned = %s\\n", __LINE__, API_NAMESPACE, pPath, originalUrl);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}


#endif  //End MOBILE or WEARABLE or TIZENIOT
/** @} */
/** @} */
