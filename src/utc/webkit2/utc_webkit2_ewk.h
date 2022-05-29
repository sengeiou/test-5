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
#ifndef UTC_WEBKIT2_EWK_H
#define UTC_WEBKIT2_EWK_H

/* Common headers */
#include <Ecore_Evas.h>
#include <Ecore.h>
#include <Edje.h>
#include <Eina.h>
#include <Elementary.h>
#include <glib-object.h>
#include <glib.h>
#include <storage.h>
#include <app.h>

#include "EWebKit.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Definitions and macros */
#define UNUSED __attribute__((unused))

#define DEFAULT_WIDTH_OF_WINDOW 480
#define DEFAULT_HEIGHT_OF_WINDOW 800

#ifndef NULL
#define NULL    0x0
#endif

/* A short 'smart data' getter */
#define EWK_VIEW_SD_GET(o, ptr) \
    Ewk_View_Smart_Data *ptr = (Ewk_View_Smart_Data *)evas_object_smart_data_get(o)

/* A structure that collects shared object variables */
struct Ewk_Test_View {
    Evas_Object* window;
    Evas* evas;
    Evas_Object* background;
    Evas_Object* webview;
    Evas_Smart*  evas_smart_class;
};

struct _Ewk_Notification_Test {
    const char* body;
    const char* iconURL;
    const char* replaceID;
    const char* title;
    uint64_t notificationID;
};

typedef struct _Ewk_Notification_Test Ewk_Notification_Test;

#ifndef NOT_USE_INIT_END

/* A shared object (of type of the above structure). The object is initialized by startup()
   and used in testing functions */
static struct Ewk_Test_View test_view;

#define FILE_PREFIX "file://"
static char* COMMON_SAMPLE_HTML_FILE = NULL;
static const char* COMMON_SAMPLE_HTML_FILENAME = "common/sample.html";
static char* COMMON_SAMPLE1_HTML_FILE = NULL;
static const char* COMMON_SAMPLE1_HTML_FILENAME = "common/sample_1.html";
static char* COMMON_SAMPLE2_HTML_FILE = NULL;
static const char* COMMON_SAMPLE2_HTML_FILENAME = "common/sample_2.html";
static char* COMMON_SAMPLE3_HTML_FILE = NULL;
static const char* COMMON_SAMPLE3_HTML_FILENAME = "common/sample_js_geolocation.html";
static char* COMMON_SAMPLE4_HTML_FILE = NULL;
static const char* COMMON_SAMPLE4_HTML_FILENAME = "common/sample_notification.html";
static char* EWK_VIEW_BACK_FORWARD_HTML_FILE = NULL;
static const char* EWK_VIEW_BACK_FORWARD_HTML_FILENAME = "ewk_view/back_forward.html";
static char* EWK_VIEW_SAMPLE_HTML_FILE = NULL;
static const char* EWK_VIEW_SAMPLE_HTML_FILENAME = "ewk_view/sample.html";
static char* EWK_VIEW_SCROLL_HTML_FILE = NULL;
static const char* EWK_VIEW_SCROLL_HTML_FILENAME = "ewk_view/scroll.html";
static char* EWK_VIEW_TEXT_FIND_HTML_FILE = NULL;
static const char* EWK_VIEW_TEXT_FIND_HTML_FILENAME = "ewk_view/text_find.html";
static char* EWK_VIEW_TEXT_SELECTION_HTML_FILE = NULL;
static const char* EWK_VIEW_TEXT_SELECTION_HTML_FILENAME = "ewk_view/text_selection.html";
static char* EWK_VIEW_ADD_JS_INTERFACE_SAMPLE_HTML_FILE = NULL;
static const char* EWK_VIEW_ADD_JS_INTERFACE_SAMPLE_HTML_FILENAME = "ewk_view/add_js_interface_sample.html";
static char* EWK_VIEW_ORIGINAL_URL_GET_HTML_FILE = NULL;
static const char* EWK_VIEW_ORIGINAL_URL_GET_HTML_FILENAME = "ewk_view/original_url_get.html";
static char* EWK_CONTEXT_FAVICON_HTML_FILE = NULL;
static const char* EWK_CONTEXT_FAVICON_HTML_FILENAME = "ewk_context/favicon.html";
static char* EWK_CONTEXT_FAVICON_BMP_FILE = NULL;
static const char* EWK_CONTEXT_FAVICON_BMP_FILENAME = "ewk_context/favicon.bmp";

static bool ewk_storage_device_supported_cb(int storage_id, storage_type_e type, storage_state_e state, const char *path, void *user_data)
{
    if (type != STORAGE_TYPE_INTERNAL)
        return true;

    // FIX Path in ewk_storage_device_supported_cb return /home/owner/content
    // instead of directory where package install sample files.
    if(strcmp(path, app_get_data_path()))
        path = app_get_data_path();

    COMMON_SAMPLE_HTML_FILE = (char*)malloc(strlen(path) + strlen(COMMON_SAMPLE_HTML_FILENAME) + strlen(FILE_PREFIX) + 6);
    if(COMMON_SAMPLE_HTML_FILE) {
        snprintf(COMMON_SAMPLE_HTML_FILE, (strlen(path) + strlen(COMMON_SAMPLE_HTML_FILENAME) + strlen(FILE_PREFIX) + 6),
            "%s%s/res/%s", FILE_PREFIX, path, COMMON_SAMPLE_HTML_FILENAME);
    }

    COMMON_SAMPLE1_HTML_FILE = (char*)malloc(strlen(path) + strlen(COMMON_SAMPLE1_HTML_FILENAME) + strlen(FILE_PREFIX) + 6);
    if(COMMON_SAMPLE1_HTML_FILE) {
        snprintf(COMMON_SAMPLE1_HTML_FILE, (strlen(path) + strlen(COMMON_SAMPLE1_HTML_FILENAME) + strlen(FILE_PREFIX) + 6),
            "%s%s/res/%s", FILE_PREFIX, path, COMMON_SAMPLE1_HTML_FILENAME);
    }

    COMMON_SAMPLE2_HTML_FILE = (char*)malloc(strlen(path) + strlen(COMMON_SAMPLE2_HTML_FILENAME) + strlen(FILE_PREFIX) + 6);
    if(COMMON_SAMPLE2_HTML_FILE) {
        snprintf(COMMON_SAMPLE2_HTML_FILE, (strlen(path) + strlen(COMMON_SAMPLE2_HTML_FILENAME) + strlen(FILE_PREFIX) + 6),
            "%s%s/res/%s", FILE_PREFIX, path, COMMON_SAMPLE2_HTML_FILENAME);
    }

    COMMON_SAMPLE3_HTML_FILE = (char*)malloc(strlen(path) + strlen(COMMON_SAMPLE3_HTML_FILENAME) + strlen(FILE_PREFIX) + 6);
    if(COMMON_SAMPLE3_HTML_FILE) {
        snprintf(COMMON_SAMPLE3_HTML_FILE, (strlen(path) + strlen(COMMON_SAMPLE3_HTML_FILENAME) + strlen(FILE_PREFIX) + 6),
            "%s%s/res/%s", FILE_PREFIX, path, COMMON_SAMPLE3_HTML_FILENAME);
    }

    COMMON_SAMPLE4_HTML_FILE = (char*)malloc(strlen(path) + strlen(COMMON_SAMPLE4_HTML_FILENAME) + strlen(FILE_PREFIX) + 6);
    if(COMMON_SAMPLE4_HTML_FILE) {
        snprintf(COMMON_SAMPLE4_HTML_FILE, (strlen(path) + strlen(COMMON_SAMPLE4_HTML_FILENAME) + strlen(FILE_PREFIX) + 6),
            "%s%s/res/%s", FILE_PREFIX, path, COMMON_SAMPLE4_HTML_FILENAME);
    }

    EWK_VIEW_BACK_FORWARD_HTML_FILE = (char*)malloc(strlen(path) + strlen(EWK_VIEW_BACK_FORWARD_HTML_FILENAME) + strlen(FILE_PREFIX) + 6);
    if(EWK_VIEW_BACK_FORWARD_HTML_FILE) {
        snprintf(EWK_VIEW_BACK_FORWARD_HTML_FILE, (strlen(path) + strlen(EWK_VIEW_BACK_FORWARD_HTML_FILENAME) + strlen(FILE_PREFIX) + 6),
            "%s%s/res/%s", FILE_PREFIX, path, EWK_VIEW_BACK_FORWARD_HTML_FILENAME);
    }

    EWK_VIEW_SAMPLE_HTML_FILE = (char*)malloc(strlen(path) + strlen(EWK_VIEW_SAMPLE_HTML_FILENAME) + strlen(FILE_PREFIX) + 6);
    if(EWK_VIEW_SAMPLE_HTML_FILE) {
        snprintf(EWK_VIEW_SAMPLE_HTML_FILE, (strlen(path) + strlen(EWK_VIEW_SAMPLE_HTML_FILENAME) + strlen(FILE_PREFIX) + 6),
            "%s%s/res/%s", FILE_PREFIX, path, EWK_VIEW_SAMPLE_HTML_FILENAME);
    }

    EWK_VIEW_SCROLL_HTML_FILE = (char*)malloc(strlen(path) + strlen(EWK_VIEW_SCROLL_HTML_FILENAME) + strlen(FILE_PREFIX) + 6);
    if(EWK_VIEW_SCROLL_HTML_FILE) {
        snprintf(EWK_VIEW_SCROLL_HTML_FILE, (strlen(path) + strlen(EWK_VIEW_SCROLL_HTML_FILENAME) + strlen(FILE_PREFIX) + 6),
            "%s%s/res/%s", FILE_PREFIX, path, EWK_VIEW_SCROLL_HTML_FILENAME);
    }

    EWK_VIEW_TEXT_FIND_HTML_FILE = (char*)malloc(strlen(path) + strlen(EWK_VIEW_TEXT_FIND_HTML_FILENAME) + strlen(FILE_PREFIX) + 6);
    if(EWK_VIEW_TEXT_FIND_HTML_FILE) {
        snprintf(EWK_VIEW_TEXT_FIND_HTML_FILE, (strlen(path) + strlen(EWK_VIEW_TEXT_FIND_HTML_FILENAME) + strlen(FILE_PREFIX) + 6),
            "%s%s/res/%s", FILE_PREFIX, path, EWK_VIEW_TEXT_FIND_HTML_FILENAME);
    }

    EWK_VIEW_TEXT_SELECTION_HTML_FILE = (char*)malloc(strlen(path) + strlen(EWK_VIEW_TEXT_SELECTION_HTML_FILENAME) + strlen(FILE_PREFIX) + 6);
    if(EWK_VIEW_TEXT_SELECTION_HTML_FILE) {
        snprintf(EWK_VIEW_TEXT_SELECTION_HTML_FILE, (strlen(path) + strlen(EWK_VIEW_TEXT_SELECTION_HTML_FILENAME) + strlen(FILE_PREFIX) + 6),
            "%s%s/res/%s", FILE_PREFIX, path, EWK_VIEW_TEXT_SELECTION_HTML_FILENAME);
    }

    EWK_VIEW_ADD_JS_INTERFACE_SAMPLE_HTML_FILE = (char*)malloc(strlen(path) + strlen(EWK_VIEW_ADD_JS_INTERFACE_SAMPLE_HTML_FILENAME) + strlen(FILE_PREFIX) + 6);
    if(EWK_VIEW_ADD_JS_INTERFACE_SAMPLE_HTML_FILE) {
        snprintf(EWK_VIEW_ADD_JS_INTERFACE_SAMPLE_HTML_FILE, (strlen(path) + strlen(EWK_VIEW_ADD_JS_INTERFACE_SAMPLE_HTML_FILENAME) + strlen(FILE_PREFIX) + 6),
            "%s%s/res/%s", FILE_PREFIX, path, EWK_VIEW_ADD_JS_INTERFACE_SAMPLE_HTML_FILENAME);
    }

    EWK_VIEW_ORIGINAL_URL_GET_HTML_FILE  = (char*)malloc(strlen(path) + strlen(EWK_VIEW_ORIGINAL_URL_GET_HTML_FILENAME) + strlen(FILE_PREFIX) + 6);
    if(EWK_VIEW_ORIGINAL_URL_GET_HTML_FILE) {
        snprintf(EWK_VIEW_ORIGINAL_URL_GET_HTML_FILE, (strlen(path) + strlen(EWK_VIEW_ORIGINAL_URL_GET_HTML_FILENAME) + strlen(FILE_PREFIX) + 6),
            "%s%s/res/%s", FILE_PREFIX, path, EWK_VIEW_ORIGINAL_URL_GET_HTML_FILENAME);
    }

    EWK_CONTEXT_FAVICON_HTML_FILE = (char*)malloc(strlen(path) + strlen(EWK_CONTEXT_FAVICON_HTML_FILENAME) + strlen(FILE_PREFIX) + 6);
    if(EWK_CONTEXT_FAVICON_HTML_FILE) {
        snprintf(EWK_CONTEXT_FAVICON_HTML_FILE, (strlen(path) + strlen(EWK_CONTEXT_FAVICON_HTML_FILENAME) + strlen(FILE_PREFIX) + 6),
            "%s%s/res/%s", FILE_PREFIX, path, EWK_CONTEXT_FAVICON_HTML_FILENAME);
    }

    EWK_CONTEXT_FAVICON_BMP_FILE = (char*)malloc(strlen(path) + strlen(EWK_CONTEXT_FAVICON_BMP_FILENAME) + strlen(FILE_PREFIX) + 6);
    if(EWK_CONTEXT_FAVICON_BMP_FILE) {
        snprintf(EWK_CONTEXT_FAVICON_BMP_FILE, (strlen(path) + strlen(EWK_CONTEXT_FAVICON_BMP_FILENAME) + strlen(FILE_PREFIX) + 6),
            "%s/res/%s", path, EWK_CONTEXT_FAVICON_BMP_FILENAME);
    }

    return false;
}

static void utc_webkit2_ewk_test_res_init()
{
    if(storage_foreach_device_supported(ewk_storage_device_supported_cb, NULL) != STORAGE_ERROR_NONE) {
        fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
    }
    if(COMMON_SAMPLE_HTML_FILE == NULL || COMMON_SAMPLE1_HTML_FILE == NULL ||
       COMMON_SAMPLE2_HTML_FILE == NULL || COMMON_SAMPLE3_HTML_FILE == NULL ||
       COMMON_SAMPLE4_HTML_FILE == NULL || EWK_VIEW_BACK_FORWARD_HTML_FILE == NULL ||
       EWK_VIEW_SAMPLE_HTML_FILE == NULL || EWK_VIEW_SCROLL_HTML_FILE == NULL ||
       EWK_VIEW_TEXT_FIND_HTML_FILE == NULL || EWK_VIEW_TEXT_SELECTION_HTML_FILE == NULL ||
       EWK_VIEW_ADD_JS_INTERFACE_SAMPLE_HTML_FILE == NULL || EWK_VIEW_ORIGINAL_URL_GET_HTML_FILE == NULL ||
       EWK_CONTEXT_FAVICON_HTML_FILE == NULL || EWK_CONTEXT_FAVICON_BMP_FILE == NULL ) {
        fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
    }
}

/**
 * Initiates objects used in the test.
 *
 * This function should be _always_ called before the actual test starts.
 * @see utc_webkit2_ewk_test_end()
 */
static UNUSED void utc_webkit2_ewk_test_init()
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
    utc_webkit2_ewk_test_res_init();
}

static void utc_webkit2_ewk_test_res_end(void)
{
    free(COMMON_SAMPLE_HTML_FILE);
    free(COMMON_SAMPLE1_HTML_FILE);
    free(COMMON_SAMPLE2_HTML_FILE);
    free(COMMON_SAMPLE3_HTML_FILE);
    free(COMMON_SAMPLE4_HTML_FILE);
    free(EWK_VIEW_BACK_FORWARD_HTML_FILE);
    free(EWK_VIEW_SAMPLE_HTML_FILE);
    free(EWK_VIEW_SCROLL_HTML_FILE);
    free(EWK_VIEW_TEXT_FIND_HTML_FILE);
    free(EWK_VIEW_TEXT_SELECTION_HTML_FILE);
    free(EWK_VIEW_ADD_JS_INTERFACE_SAMPLE_HTML_FILE);
    free(EWK_VIEW_ORIGINAL_URL_GET_HTML_FILE);
    free(EWK_CONTEXT_FAVICON_HTML_FILE);
    free(EWK_CONTEXT_FAVICON_BMP_FILE);
}

/**
 * Frees resources used during the test.
 * This function should be _always_ called after the test is completed.
 * @see utc_webkit2_ewk_test_init()
 */
static UNUSED void utc_webkit2_ewk_test_end()
{
    /* 1. Freeing resources */
    if (test_view.webview)
        evas_object_del(test_view.webview);

    if (test_view.window)
        evas_object_del(test_view.window);

    /* 2. Closing whole EWK */
    ewk_shutdown();
    elm_shutdown();
    utc_webkit2_ewk_test_res_end();
}

static Ecore_Timer* timeout_;
static bool isMainLoopRunning;

static UNUSED Eina_Bool timeout_cb_event_loop_wait(void* data)
{
    ecore_main_loop_quit();
    return ECORE_CALLBACK_CANCEL;
}

static UNUSED bool eventLoopWait(double time)
{
    if (!isMainLoopRunning) {
        isMainLoopRunning = true;
        timeout_ = ecore_timer_add(time, timeout_cb_event_loop_wait, NULL);
        ecore_main_loop_begin();
        if (timeout_) {
            ecore_timer_del(timeout_);
            timeout_ = NULL;
        }
        isMainLoopRunning = false;
        return true;
    }
    return false;
}
#endif

/**
 * Begins main application loop.
 */

#define utc_webkit2_main_loop_begin ecore_main_loop_begin

/**
 * Ends main application loop.
 */

#define utc_webkit2_main_loop_quit ecore_main_loop_quit

#ifdef __cplusplus
}
#endif

#endif
