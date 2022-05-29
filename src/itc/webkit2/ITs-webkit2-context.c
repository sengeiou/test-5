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
#include <storage.h>

/** @addtogroup itc-webkit2
*  @ingroup itc
*  @{
*/

struct Ewk_Test_View {
    Evas_Object* window;
    Evas* evas;
    Evas_Object* background;
    Evas_Object* webview;
    Evas_Smart*  evas_smart_class;
};
static struct Ewk_Test_View test_view;
char* EWK_CONTEXT_FAVICON_HTML_FILE = NULL;
char* EWK_CONTEXT_FAVICON_HTML_FILENAME = "ewk_context/favicon.html";
char* EWK_CONTEXT_FAVICON_BMP_FILE = NULL;
char* EWK_CONTEXT_FAVICON_BMP_FILENAME = "ewk_context/favicon.bmp";
#define FILE_PREFIX "file://"
#define UNUSED __attribute__((unused))
#define itc_webkit2_main_loop_quit ecore_main_loop_quit
#define itc_webkit2_main_loop_begin ecore_main_loop_begin
static bool g_bWebkit_EFL_LoadSuccess = false;
static bool g_bWebkit_EFL_IconReceived = false;



static Eina_Bool mainLoopQuit(void* data)
{
	FPRINTF("[Line : %d][%s] TimeOut Occurs\\n", __LINE__, API_NAMESPACE);
	Webkit_EFL_main_loop_quit();
	return EINA_FALSE;
}
static void itc_webkit2_ewk_test_res_end(void)
{
    free(EWK_CONTEXT_FAVICON_HTML_FILE);
    free(EWK_CONTEXT_FAVICON_BMP_FILE);
}

static void itc_webkit2_ewk_test_end()
{
    FPRINTF("[Line : %d][%s] Inside itc_webkit2_ewk_test_end \\n", __LINE__, API_NAMESPACE);
	/* 1. Freeing resources */
    if (test_view.webview)
        evas_object_del(test_view.webview);

    if (test_view.window)
        evas_object_del(test_view.window);

    /* 2. Closing whole EWK */
    ewk_shutdown();
    elm_shutdown();
    itc_webkit2_ewk_test_res_end();
}
static Eina_Bool loadURL(const char* url)
{
    return ewk_view_url_set(test_view.webview, url);
}

bool ewk_storage_device_supported_cb(int storage_id, storage_type_e type, storage_state_e state, const char *path, void *user_data)
{
    if (type != STORAGE_TYPE_INTERNAL)
        return true;

    // FIX Path in ewk_storage_device_supported_cb return /home/owner/content
    // instead of directory where package install sample files.
    if(strcmp(path, app_get_data_path()))
        path = app_get_data_path();


    EWK_CONTEXT_FAVICON_HTML_FILE = (char*)malloc(strlen(path) + strlen(EWK_CONTEXT_FAVICON_HTML_FILENAME) + strlen(FILE_PREFIX) + 6);
    CHECK_HANDLE(EWK_CONTEXT_FAVICON_HTML_FILE,"malloc:failure:ewk_storage_device_supported_cb");
    snprintf(EWK_CONTEXT_FAVICON_HTML_FILE, (strlen(path) + strlen(EWK_CONTEXT_FAVICON_HTML_FILENAME) + strlen(FILE_PREFIX) + 6),
        "%s%s/res/%s", FILE_PREFIX, path, EWK_CONTEXT_FAVICON_HTML_FILENAME);

    EWK_CONTEXT_FAVICON_BMP_FILE = (char*)malloc(strlen(path) + strlen(EWK_CONTEXT_FAVICON_BMP_FILENAME) + strlen(FILE_PREFIX) + 6);
    CHECK_HANDLE_CLEANUP(EWK_CONTEXT_FAVICON_BMP_FILE,"malloc:failure:ewk_storage_device_supported_cb",free(EWK_CONTEXT_FAVICON_HTML_FILE));
    snprintf(EWK_CONTEXT_FAVICON_BMP_FILE, (strlen(path) + strlen(EWK_CONTEXT_FAVICON_BMP_FILENAME) + strlen(FILE_PREFIX) + 6),
        "%s/res/%s", path, EWK_CONTEXT_FAVICON_BMP_FILENAME);

    return false;
}

void itc_webkit2_ewk_test_res_init()
{
    FPRINTF("[Line : %d][%s] Inside itc_webkit2_ewk_test_res_init \\n", __LINE__, API_NAMESPACE);
    if(storage_foreach_device_supported(ewk_storage_device_supported_cb, NULL) != STORAGE_ERROR_NONE) {
        FPRINTF("Startup error at %s:%d\n", __FILE__, __LINE__);
    }
    if(EWK_CONTEXT_FAVICON_HTML_FILE == NULL ||
       EWK_CONTEXT_FAVICON_BMP_FILE == NULL ) {
        FPRINTF("Startup error at %s:%d\n", __FILE__, __LINE__);
    }
}
/**
 * Initiates objects used in the test.
 *
 * This function should be _always_ called before the actual test starts.
 * @see utc_webkit2_ewk_test_end()
 */
static void itc_webkit2_ewk_test_init()
{
    elm_init(0, NULL);
    ewk_init();
    elm_config_accel_preference_set("opengl");

    test_view.window = elm_win_add(NULL, "TC Launcher", ELM_WIN_BASIC);
    elm_win_title_set(test_view.window, "TC Launcher");
    test_view.evas = evas_object_evas_get(test_view.window);
    test_view.background = evas_object_rectangle_add(test_view.evas);

    evas_object_name_set(test_view.background, "view");
    evas_object_color_set(test_view.background, 255, 0, 255, 255);
    evas_object_move(test_view.background, 0, 0);
    evas_object_resize(test_view.background, DEFAULT_WIDTH_OF_WINDOW, DEFAULT_HEIGHT_OF_WINDOW);
    evas_object_layer_set(test_view.background, EVAS_LAYER_MIN);
    //evas_object_show(test_view.background);

    /* 3. Initialization of webview */
    test_view.webview = ewk_view_add(test_view.evas);
    evas_object_move(test_view.webview, 10, 10);
    evas_object_resize(test_view.webview, DEFAULT_WIDTH_OF_WINDOW-20, DEFAULT_HEIGHT_OF_WINDOW-20);

    //evas_object_show(test_view.webview);
    //evas_object_show(test_view.window);
    itc_webkit2_ewk_test_res_init();
}
#if defined(MOBILE) || defined(TIZENIOT) || defined(TV)
static void iconReceived_Local(void* data, Evas_Object* webview, void* event_info)
{
    static const int PIXEL_SIZE = 4;
    static int w = 0 , h = 0;
    Ewk_Context* context = ewk_view_context_get(test_view.webview);


    Evas_Object* favicon = ewk_context_icon_database_icon_object_add(context, EWK_CONTEXT_FAVICON_HTML_FILE, test_view.evas);

    evas_object_image_size_get(favicon, &w, &h);

    Evas_Object* img = evas_object_image_filled_add(test_view.evas);

    evas_object_image_file_set(img, EWK_CONTEXT_FAVICON_BMP_FILE , NULL);

    itc_webkit2_main_loop_quit();
}
#endif

/**
* @function 		Webkit_EFL_LoadError
* @description	 	Callback function to get webkit load error info
* @parameter		data : user data,webview : evas object, event_info : event information
* @return 			NA
*/
static void Webkit_EFL_LoadError(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_LoadError occurs\\n", __LINE__, API_NAMESPACE);
	g_bWebkit_EFL_LoadSuccess = false;
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
	g_bWebkit_EFL_LoadSuccess = true;
	Webkit_EFL_main_loop_quit();
}

/**
* @function			iconReceived
* @description		Webkit_EFL_main_loop_quit called
* @parameter		void* data, Evas_Object* webview, void* event_info
* @return			none
*/
void iconReceived(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Icon Received Callback Invoked\\n", __LINE__, API_NAMESPACE);
	g_bWebkit_EFL_IconReceived = true;
	Webkit_EFL_main_loop_quit();
}

/**
* @function 		ITs_webkit_efl_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_webkit_efl_context_startup(void)
{
struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT start-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif

	return;
}


/**
* @function 		ITs_webkit_efl_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_webkit_efl_context_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

#ifdef TV	//Starts TV
/** @addtogroup itc-webkit2-testcases
*  @brief 		Integration testcases for module webkit2
*  @ingroup 	itc-webkit2
*  @{
*/

//& type: auto
//& purpose: Initialise webkit instance
/**
* @testcase 			ITc_ewk_context_ewk_init_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Initialise webkit instance
* @scenario				Initialise/Increases reference count of webkit instance\n
*						Destroy/Decreases reference count of webkit instance
* @apicovered			ewk_init, ewk_shutdown
* @passcase				When ewk_init returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_context_ewk_init_p(void)
{
	START_TEST;

	//Target API
	int nRetValInit = ewk_init();
	if ( nRetValInit <= 0 )
	{
		FPRINTF("[Line : %d][%s] ewk_init failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRetValShutDown = ewk_shutdown();
	if ( nRetValShutDown != (nRetValInit-1) )	// reference count should decrease by 1
	{
		FPRINTF("[Line : %d][%s] ewk_shutdown failed, webkit instance reference count = %d on initialisation and %d on shutdown\\n", __LINE__, API_NAMESPACE, nRetValInit, nRetValShutDown);
		return 1;
	}
	return 0;
}
//& type: auto
//& purpose: Shutdown webkit instance.
/**
* @testcase 			ITc_ewk_context_ewk_shutdown_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Shutdown webkit instance
* @scenario				Initialise/Increases reference count of webkit instance\n
*						Destroy/Decreases reference count of webkit instance
* @apicovered			ewk_init, ewk_shutdown
* @passcase				When ewk_shutdown returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_context_ewk_shutdown_p(void)
{
	START_TEST;
	int nRetValInit = ewk_init();
	if ( nRetValInit <= 0 )
	{
		FPRINTF("[Line : %d][%s] ewk_init failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	//Target API
	int nRetValShutDown = ewk_shutdown();
	if ( nRetValShutDown != (nRetValInit-1) )	// reference count should decrease by 1
	{
		FPRINTF("[Line : %d][%s] ewk_shutdown failed, webkit instance reference count = %d on initialisation and %d on shutdown\\n", __LINE__, API_NAMESPACE, nRetValInit, nRetValShutDown);
		return 1;
	}
	return 0;
}
#endif  	//End TV
//& type: auto
//& purpose: Request to set cache model
/**
* @testcase 			ITc_ewk_context_cache_model_set_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Request to set cache model
* @scenario				Create Webkit View\n
*						Call ewk_context_cache_model_set to set\n
*						Call ewk_context_cache_model_get to get the value\n
*						Validate the get value\n\n
*						Destroy webkit view
* @apicovered			ewk_context_cache_model_set, ewk_context_cache_model_get
* @passcase				When ewk_context_cache_model_set able to set the value properly
* @failcase				If target API fails or set value not fetched during get operation
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_context_cache_model_set_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Cache_Model eValueSet = EWK_CACHE_MODEL_DOCUMENT_VIEWER;
	Eina_Bool bResult = EINA_FALSE;

	//Target API
	bResult = ewk_context_cache_model_set(ewk_view_context_get(objWebkit_EFL_view.webview), eValueSet);
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_context_cache_model_set returned error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Ewk_Cache_Model eValueGet = ewk_context_cache_model_get(ewk_view_context_get(objWebkit_EFL_view.webview));
	if ( eValueSet != eValueGet )
	{
		FPRINTF("[Line : %d][%s] ewk_context_cache_model_get returned incorrect value; Expected Value = %d, Returned Value = %d\\n", __LINE__, API_NAMESPACE, eValueSet, eValueGet);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Request to get cache model
/**
* @testcase 			ITc_ewk_context_cache_model_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Request to get cache model
* @scenario				Create Webkit View\n
*						Call ewk_context_cache_model_set to set\n
*						Call ewk_context_cache_model_get to get the value\n
*						Validate the get value\n
*						Destroy webkit view
* @apicovered			ewk_context_cache_model_set, ewk_context_cache_model_get
* @passcase				When ewk_context_cache_model_get able to get the value properly
* @failcase				If target API fails or set value not fetched during get operation
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_context_cache_model_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Cache_Model eValueSet = EWK_CACHE_MODEL_DOCUMENT_VIEWER;
	Eina_Bool bResult = EINA_FALSE;
	bResult = ewk_context_cache_model_set(ewk_view_context_get(objWebkit_EFL_view.webview), eValueSet);
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_context_cache_model_set returned error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Ewk_Cache_Model eValueGet = EWK_CACHE_MODEL_DOCUMENT_BROWSER;
	//Target API
	eValueGet = ewk_context_cache_model_get(ewk_view_context_get(objWebkit_EFL_view.webview));
	if ( eValueSet != eValueGet )
	{
		FPRINTF("[Line : %d][%s] ewk_context_cache_model_get returned incorrect value; Expected Value = %d, Returned Value = %d\\n", __LINE__, API_NAMESPACE, eValueSet, eValueGet);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Gets the cookie manager instance for this context
/**
* @testcase 			ITc_ewk_context_cookie_manager_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets the cookie manager instance for this context
* @scenario				Create Webkit View\n
*						Call ewk_context_cookie_manager_get to get the value\n
*						Validate the get value\n
*						Destroy webkit view
* @apicovered			ewk_context_cookie_manager_get
* @passcase				When ewk_context_cookie_manager_get able to get the value properly
* @failcase				If target API fetches invalid value during get operation
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_context_cookie_manager_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Cookie_Manager* eValueGet = NULL;
	//Target API
	eValueGet = ewk_context_cookie_manager_get(ewk_view_context_get(objWebkit_EFL_view.webview));
	if ( eValueGet == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_context_cookie_manager_get returned NULL value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Clears HTTP caches in the local storage
/**
* @testcase 			ITc_ewk_context_resource_cache_clear_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Clears HTTP caches in the local storage
* @scenario				Create Webkit View\n
*						Call ewk_context_resource_cache_clear\n
*						Destroy webkit view
* @apicovered			ewk_context_resource_cache_clear
* @passcase				When ewk_context_resource_cache_clear behaves properly
* @failcase				If target API didn't behave properly
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_context_resource_cache_clear_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	//Target API
	ewk_context_resource_cache_clear(ewk_view_context_get(objWebkit_EFL_view.webview));
	Webkit_EFLDestroyWebKitView();
	return 0;
}


#if defined(MOBILE) || defined(TIZENIOT) || defined(TV)		//Starts MOBILE or  TIZENIOT
//& purpose: To get image representing the given URL
//& type: auto
/**
* @testcase 			ITc_ewk_context_icon_database_icon_object_add_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			To get image representing the given URL
* @scenario				ewk_view_context_get\n
*						evas_object_evas_get\n
*						ewk_context_icon_database_icon_object_add
* @apicovered			ewk_view_context_get, ewk_context_icon_database_icon_object_add
* @passcase				When ewk_context_icon_database_icon_object_add is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_context_icon_database_icon_object_add_p(void)
{
	START_TEST;
	FPRINTF("[Line : %d][%s] Inside TC\\n", __LINE__, API_NAMESPACE);

	itc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "icon,received", iconReceived_Local, NULL);

	if(!loadURL(EWK_CONTEXT_FAVICON_HTML_FILE))
	{
		FPRINTF("[Line : %d][%s] Not loadURL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	evas_object_smart_callback_del(test_view.webview, "icon,received", iconReceived_Local);
	FPRINTF("[Line : %d][%s] After evas_object_smart_callback_del \\n", __LINE__, API_NAMESPACE);
    itc_webkit2_ewk_test_end();
	FPRINTF("[Line : %d][%s] After utc_webkit2_ewk_test_end \\n", __LINE__, API_NAMESPACE);

	/*
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "icon,received", iconReceived, NULL);
	Ewk_Context* context = ewk_view_context_get(objWebkit_EFL_view.webview);
	if ( !context )
	{
		FPRINTF("[Line : %d][%s] Unable to create context\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	const char* url = "http://www.google.co.kr/";

	// Initialize database.
	g_bWebkit_EFL_IconReceived = false;
	ewk_context_icon_database_icon_object_add(context, url, objWebkit_EFL_view.evas);
	Eina_Bool result = ewk_view_url_set(objWebkit_EFL_view.webview, (url));
	if ( !result )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set failed\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if ( g_bWebkit_EFL_LoadSuccess == false )
	{
		FPRINTF("[Line : %d][%s] Unable to load URL to Web View\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Ecore_Timer* timer = ecore_timer_add(5.0f, mainLoopQuit, NULL);
	Webkit_EFL_main_loop_begin();
	ecore_timer_del(timer);
	if ( g_bWebkit_EFL_IconReceived == false )
	{
		FPRINTF("[Line : %d][%s] Unable to invoke Icon Received Callback\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Evas_Object* favicon = ewk_context_icon_database_icon_object_add(context, url, objWebkit_EFL_view.evas);
	if ( favicon == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to to add icon object\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "icon,received", iconReceived);

	Webkit_EFLDestroyWebKitView();
*/
	return 0;

}

//& purpose: Request for deleting all web application caches.
//& type: auto
/**
* @testcase 			ITc_ewk_context_application_cache_delete_all_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Request for deleting all web application caches.
* @scenario				ewk_view_context_get\n
*						ewk_context_application_cache_delete_all
* @apicovered			ewk_view_context_get, ewk_context_application_cache_delete_all
* @passcase				When ewk_context_application_cache_delete_all is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_context_application_cache_delete_all_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}
        evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
        evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);

        const char* url = "http://www.google.co.kr/";

        Eina_Bool result = ewk_view_url_set(objWebkit_EFL_view.webview, (url));
        if ( !result )
        {
                FPRINTF("[Line : %d][%s] ewk_view_url_set failed\\n", __LINE__, API_NAMESPACE);
                Webkit_EFLDestroyWebKitView();
                return 1;
        }

        Webkit_EFL_main_loop_begin();
        if ( g_bWebkit_EFL_LoadSuccess == false )
        {
                FPRINTF("[Line : %d][%s] Unable to load URL to Web View\\n", __LINE__, API_NAMESPACE);
                Webkit_EFLDestroyWebKitView();
                return 1;
        }
	Eina_Bool cacheStatus;
	Ewk_Context* ewkContext = ewk_view_context_get(objWebkit_EFL_view.webview);
	if ( ewkContext == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_context_new failed\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	cacheStatus = ewk_context_application_cache_delete_all(ewkContext);
	if ( cacheStatus == EINA_FALSE )
	{
		FPRINTF("[Line : %d][%s] ewk_context_application_cache_delete_all failed\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
        evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
        evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);

	Webkit_EFLDestroyWebKitView();
	return 0;
}
#endif  //End MOBILE or TIZENIOT

//& purpose: To get and set background music status
//& type: auto
/**
* @testcase 			ITc_ewk_context_background_music_get_set_p
* @since_tizen			4.0
* @owner				SRID(manoj.g2)
* @reviewer				SRID(shobhit.verma)
* @type					auto
* @description			To get and set background music status
* @scenario				ewk_context_background_music_set\n
*						ewk_context_background_music_get
* @apicovered			ewk_context_background_music_set, ewk_context_background_music_get
* @passcase				When ewk_context_background_music_set, ewk_context_background_music_get is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_context_background_music_get_set_p(void)
{
	START_TEST;
	Eina_Bool result;

	itc_webkit2_ewk_test_init();
	result = ewk_context_background_music_set(ewk_view_context_get(test_view.webview), EINA_TRUE);

	if ( result == EINA_FALSE )
	{
		FPRINTF("[Line : %d][%s] ewk_context_background_music_set failed\\n", __LINE__, API_NAMESPACE);
		itc_webkit2_ewk_test_end();
		return 1;
	}

	result = ewk_context_background_music_get(ewk_view_context_get(test_view.webview));
	if ( result == EINA_FALSE )
	{
		FPRINTF("[Line : %d][%s] ewk_context_background_music_get failed\\n", __LINE__, API_NAMESPACE);
		itc_webkit2_ewk_test_end();
		return 1;
	}

	itc_webkit2_ewk_test_end();

	return 0;
}

//& purpose: To get and set block multimedia on call status
//& type: auto
/**
* @testcase 			ITc_ewk_context_block_multimedia_on_call_get_set_p
* @since_tizen			4.0
* @owner				SRID(manoj.g2)
* @reviewer				SRID(shobhit.verma)
* @type					auto
* @description			To get and set block multimedia on call status
* @scenario				ewk_context_block_multimedia_on_call_set\n
*						ewk_context_block_multimedia_on_call_get
* @apicovered			ewk_context_block_multimedia_on_call_set, ewk_context_block_multimedia_on_call_get
* @passcase				When ewk_context_block_multimedia_on_call_set, ewk_context_block_multimedia_on_call_get is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_context_block_multimedia_on_call_get_set_p(void)
{
	START_TEST;
	Eina_Bool result;

	itc_webkit2_ewk_test_init();
	result = ewk_context_block_multimedia_on_call_set(ewk_view_context_get(test_view.webview), EINA_TRUE);

	if ( result == EINA_FALSE )
	{
		FPRINTF("[Line : %d][%s] ewk_context_block_multimedia_on_call_set failed\\n", __LINE__, API_NAMESPACE);
		itc_webkit2_ewk_test_end();
		return 1;
	}

	result = ewk_context_block_multimedia_on_call_get(ewk_view_context_get(test_view.webview));
	if ( result == EINA_FALSE )
	{
		FPRINTF("[Line : %d][%s] ewk_context_block_multimedia_on_call_get failed\\n", __LINE__, API_NAMESPACE);
		itc_webkit2_ewk_test_end();
		return 1;
	}

	itc_webkit2_ewk_test_end();

	return 0;
}

//& purpose: To get and set enable state of rotation lock
//& type: auto
/**
* @testcase 			ITc_ewk_context_rotation_lock_get_set_p
* @since_tizen			4.0
* @owner				SRID(manoj.g2)
* @reviewer				SRID(shobhit.verma)
* @type					auto
* @description			To get and set enable state of rotation lock
* @scenario				ewk_context_rotation_lock_set\n
*						ewk_context_rotation_lock_get
* @apicovered			ewk_context_rotation_lock_set, ewk_context_rotation_lock_get
* @passcase				When ewk_context_rotation_lock_set, ewk_context_rotation_lock_get is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_context_rotation_lock_get_set_p(void)
{
	START_TEST;
	Eina_Bool result;

	itc_webkit2_ewk_test_init();
	result = ewk_context_rotation_lock_set(ewk_view_context_get(test_view.webview), EINA_TRUE);

	if ( result == EINA_FALSE )
	{
		FPRINTF("[Line : %d][%s] ewk_context_rotation_lock_set failed\\n", __LINE__, API_NAMESPACE);
		itc_webkit2_ewk_test_end();
		return 1;
	}

	result = ewk_context_rotation_lock_get(ewk_view_context_get(test_view.webview));
	if ( result == EINA_FALSE )
	{
		FPRINTF("[Line : %d][%s] ewk_context_rotation_lock_get failed\\n", __LINE__, API_NAMESPACE);
		itc_webkit2_ewk_test_end();
		return 1;
	}

	itc_webkit2_ewk_test_end();

	return 0;
}

//& purpose: To get and set enable state of sound overlap
//& type: auto
/**
* @testcase 			ITc_ewk_context_sound_overlap_get_set_p
* @since_tizen			4.0
* @owner				SRID(manoj.g2)
* @reviewer				SRID(shobhit.verma)
* @type					auto
* @description			To get and set enable state of sound overlap
* @scenario				ewk_context_sound_overlap_set\n
*						ewk_context_sound_overlap_get
* @apicovered			ewk_context_sound_overlap_set, ewk_context_sound_overlap_get
* @passcase				When ewk_context_sound_overlap_set, ewk_context_sound_overlap_get is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_context_sound_overlap_get_set_p(void)
{
	START_TEST;
	Eina_Bool result;

	itc_webkit2_ewk_test_init();
	result = ewk_context_sound_overlap_set(ewk_view_context_get(test_view.webview), EINA_TRUE);

	if ( result == EINA_FALSE )
	{
		FPRINTF("[Line : %d][%s] ewk_context_sound_overlap_set failed\\n", __LINE__, API_NAMESPACE);
		itc_webkit2_ewk_test_end();
		return 1;
	}

	result = ewk_context_sound_overlap_get(ewk_view_context_get(test_view.webview));
	if ( result == EINA_FALSE )
	{
		FPRINTF("[Line : %d][%s] ewk_context_sound_overlap_get failed\\n", __LINE__, API_NAMESPACE);
		itc_webkit2_ewk_test_end();
		return 1;
	}

	itc_webkit2_ewk_test_end();

	return 0;
}

/** @} */
/** @} */
