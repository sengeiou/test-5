/* Copyright (c) 2014 Samsung Electronics Co., Ltd.

   Licensed under the Apache License, Version 2.0 (the License);
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include "assert.h"
#include "utc_webkit2_ewk.h"

static Eina_Bool loadURL(const char* url)
{
    return ewk_view_url_set(test_view.webview, url);
}

static int iconReceived(void* data, Evas_Object* webview, void* event_info)
{
    static const int PIXEL_SIZE = 4;
    static int w = 0 , h = 0;
    Ewk_Context* context = ewk_view_context_get(test_view.webview);
    assert(context);

    Evas_Object* favicon = ewk_context_icon_database_icon_object_add(context, EWK_CONTEXT_FAVICON_HTML_FILE, test_view.evas);
    assert(favicon);
    evas_object_image_size_get(favicon, &w, &h);

    Evas_Object* img = evas_object_image_filled_add(test_view.evas);
    assert(img);
    evas_object_image_file_set(img, EWK_CONTEXT_FAVICON_BMP_FILE , NULL);
    assert_eq(0, memcmp(evas_object_image_data_get(favicon, EINA_FALSE),
                        evas_object_image_data_get(img, EINA_FALSE),
                        w * h * PIXEL_SIZE));
    utc_webkit2_main_loop_quit();
}

/**
 * @function		utc_webkit2_ewk_context_icon_database_icon_object_add_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_context_icon_database_icon_object_add_func_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "icon,received", iconReceived, NULL);
}

/**
 * @function		utc_webkit2_ewk_context_icon_database_icon_object_add_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_context_icon_database_icon_object_add_func_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "icon,received", iconReceived);
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_context_icon_database_icon_object_add_p
 * @since_tizen		2.4
 * @description		To get image representing the given URL
 * @scenario		ewk_view_context_get\n
 *			ewk_context_icon_database_icon_object_add
 */
int utc_webkit2_ewk_context_icon_database_icon_object_add_p(void)
{
    assert(loadURL(EWK_CONTEXT_FAVICON_HTML_FILE));
    utc_webkit2_main_loop_begin();
    return 0;
}

/**
 * @testcase		utc_webkit2_ewk_context_icon_database_icon_object_add_n
 * @since_tizen		2.4
 * @description		To get image representing the given URL
 * @scenario		Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_context_icon_database_icon_object_add_n(void)
{
    Evas_Object* favicon = ewk_context_icon_database_icon_object_add(ewk_view_context_get(test_view.webview), NULL, test_view.evas);
    assert_eq(favicon, NULL);
    return 0;
}
