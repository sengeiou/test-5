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
#ifndef _ITS_WEBKIT_EFL_COMMON_H_
#define _ITS_WEBKIT_EFL_COMMON_H_

#include "tct_common.h"
#include <Ecore_Evas.h>
#include <Ecore.h>
#include <Evas.h>
#include <Edje.h>
#include <Eina.h>
#include <Elementary.h>
#include <glib-object.h>
#include <glib.h>
#include <app.h>

#include "EWebKit.h"

/** @addtogroup itc-webkit2
*  @ingroup itc
*  @{
*/

#define WAIT_CALLBACK				5
#define MICROSECONDS_PER_SECOND		1000000
#define LOG							100
#define VIEW_WINDOW_NAME			"WEBKIT-EFL-WINDOW"
#define VIEW_BKG_NAME				"view"
#define PREFERRED_ENGINE			"opengl"
#define DEFAULT_WIDTH_OF_WINDOW		480
#define DEFAULT_HEIGHT_OF_WINDOW	800
#define WEBVIEW_MOVE				10
#define WEBVIEW_RANGE				20
#define INITIALIZE_FAIL				1
#define SAMPLE_HTML_FILE			"webkit2_files/res/common/sample.html"
#define SAMPLE_HTML_FILE1			"webkit2_files/res/common/sample_1.html"
#define SAMPLE_HTML_FILE2			"webkit2_files/res/common/sample_2.html"
#define CONTEXT_MENU_PATH			"webkit2_files/res/ewk_context_menu/index.html"
#define SAMPLE_HTML_FILE_TITLE		"Testing Sample Page"
#define SAMPLE_EWK_HTML_FILE		"webkit2_files/res/ewk_view/text_selection.html"
#define INVALID_FILE_PATH			"webkit2_files/res/common/InvalidFile.html"
#define COOKIE_STORAGE_PATH			"/tmp/mycookiestoragedir"
#define POLICY_DECISION_URL			"http://www.google.com"
#define RESPONSE_STATUS_CODE_SUCCESS 200
#define SET_DEFAULT_ENCODING		"utf-8"
#define SET_DEFAULT_FONT_SIZE		10
#define SET_USER_AGENT				"Mozilla/5.0 (Unknown; Linux armv7l **TEST*TEST**) AppleWebKit/534.16+ (KHTML, like Gecko) Version/5.0 Safari/534.16+"
#define TEST_JS_SCRIPT				"document.getElementById('getParaContent').innerHTML"
#define TIMEOUT_VALUE				7.0f
#define SCALE_FACTOR_VALUE			2.0
#define X_CENTRE					5
#define Y_CENTRE					5
#define SET_CONTENT					"This is test content page"
#define SAMPLE_SCROLL_FILE		"webkit2_files/res/ewk_view/scroll.html"
#define SAMPLE_HTML_FILE_VIEW		"webkit2_files/res/ewk_view/sample.html"
#define SAMPLE_FILE_VIEW_TEXT_FIND	"webkit2_files/res/ewk_view/text_find.html"
#define SAMPLE_EWK_VIEW_ORIGINAL_URL	"webkit2_files/res/ewk_view/original_url_get.html"
#define SCROLL_BY_X					14
#define SCROLL_BY_Y					28
#define PATH_LEN					1024
#define LAUNCH_URL					"http://www.chromium.org"
#define API_NAMESPACE				"WEBKIT2_ITC"
#define PORIENT						90
#define URL 						"http://www.webkit.org"
/*
static char* EWK_CONTEXT_FAVICON_HTML_FILE = NULL;
static const char* EWK_CONTEXT_FAVICON_HTML_FILENAME = "ewk_context/favicon.html";
static char* EWK_CONTEXT_FAVICON_BMP_FILE = NULL;
static const char* EWK_CONTEXT_FAVICON_BMP_FILENAME = "ewk_context/favicon.bmp";
*/
static const unsigned		TEST_AUTOFILL_PROFILE_ID					= 12345;
static const char* const	TEST_AUTOFILL_PROFILE_NAME					= "Mr. Smith";
static const char* const	TEST_AUTOFILL_PROFILE_NAME_2				= "Mrs. Smith";
static const char* const	TEST_AUTOFILL_PROFILE_COMPANY				= "SomeCompany";
static const char* const	TEST_AUTOFILL_PROFILE_ADDRESS1				= "Existing Street 15";
static const char* const	TEST_AUTOFILL_PROFILE_ADDRESS2				= "NonExisting Street -15";
static const char* const	TEST_AUTOFILL_PROFILE_CITY_TOWN				= "Capitol";
static const char* const	TEST_AUTOFILL_PROFILE_STATE_PROVINCE_REGION	= "Beautiful Province";
static const char* const	TEST_AUTOFILL_PROFILE_ZIPCODE				= "12-345";
static const char* const	TEST_AUTOFILL_PROFILE_COUNTRY				= "Neverland";
static const char* const	TEST_AUTOFILL_PROFILE_PHONE					= "123456789";
static const char* const	TEST_AUTOFILL_PROFILE_EMAIL					= "someEmail@someServer.com";

//Add helper function declarations here

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s \\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

struct WebKit_EFL_ewk_View{
	Evas_Object* window;
	Evas* evas;
	Evas_Object* background;
	Evas_Object* webview;
	Evas_Smart* evas_smart_class;
};

struct WebKit_EFL_ewk_View objWebkit_EFL_view;

Ecore_Timer *timeout;
bool main_loop_running;
bool EventLoopWait(double time);

#if defined(MOBILE) ||  defined(TIZENIOT) || defined(TV)//Starts MOBILE or  TIZENIOT
Ewk_Autofill_Profile* GetEwkAFillProf();

#endif  //End MOBILE or TIZENIOT
bool Webkit_EFLCreateWebKitView();
void Webkit_EFLDestroyWebKitView();


void Webkit_EFL_main_loop_begin();
void Webkit_EFL_main_loop_quit();

bool Webkit_EFLGetDataPath(char* pPath); // this function outputs tha application data path
bool Webkit_EFLAppendToAppDataPath(char* pInputPath, char* pFinalPath); // this function appends the input string to app data path and outputs the final resultant path
bool Webkit_EFLAppendToDataPathWithFileFormat(char* pInputPath, char* pFinalPath); // this function appends the input string to app data path with file extension in the prefix and outputs the final resultant path

/** @} */
#endif  //_ITS_WEBKIT_EFL_COMMON_H_
