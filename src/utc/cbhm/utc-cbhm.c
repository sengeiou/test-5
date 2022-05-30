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
#include "assert.h"
#include <cbhm.h>
#include <dlog.h>
#include <Elementary.h>

Evas_Object *main_win = NULL;

Eina_Bool _timer_cb(void *data)
{
   cbhm_h cbhm_handle = data;
   cbhm_close_service(cbhm_handle);
   ecore_main_loop_quit();
   return EINA_FALSE;
}

static int
_selection_data_cb(cbhm_h cbhm_handle, const char *buf, size_t len, void *user_data)
{
    return CBHM_ERROR_NONE;
}

static int
_selection_clicked_cb(cbhm_h cbhm_handle, void *user_data)
{
   return CBHM_ERROR_NONE;
}

static void
_item_changed_cb(cbhm_h cbhm_handle, int item_count, void *user_data)
{
   return;
}

static void
_monitor_cb(cbhm_h cbhm_handle, bool active_state, void *user_data)
{
   return;
}

void utc_cbhm_startup(void)
{
   elm_init(0, NULL);
   main_win = elm_win_add(NULL, "main", ELM_WIN_BASIC);
   evas_object_resize(main_win, 320, 480);
   elm_object_focus_set(main_win, EINA_TRUE);
}

void utc_cbhm_cleanup(void)
{
   if (main_win != NULL) {
        evas_object_del(main_win);
        main_win = NULL;
   }
   elm_shutdown();
}

/**
 * @testcase	utc_cbhm_open_service_p
 * @since_tizen	3.0
 * @description	Initialize the clipboard handle
 * @scenario	Open clipboard handle
 */
int utc_cbhm_open_service_p(void)
{

   cbhm_h cbhm_handle;
   int ret = cbhm_open_service(&cbhm_handle);
   assert_eq(ret, CBHM_ERROR_NONE);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_open_service_n
 * @since_tizen	3.0
 * @description	Initialize the clipboard handle
 * @scenario	Try to open clipboard handle with null pointer
 */
int utc_cbhm_open_service_n(void)
{
   int ret = cbhm_open_service(NULL);
   assert_eq(ret, CBHM_ERROR_INVALID_PARAMETER);

   return 0;
}

/**
 * @testcase	utc_cbhm_close_service_p
 * @since_tizen	3.0
 * @description	deinitialize the clipboard handle
 * @scenario	Close the clipboard handle
 */
int utc_cbhm_close_service_p(void)
{

   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   int ret = cbhm_close_service(cbhm_handle);
   assert_eq(ret, CBHM_ERROR_NONE);

   return 0;
}

/**
 * @testcase	utc_cbhm_close_service_n
 * @since_tizen	3.0
 * @description	deinitialize the clipboard handle
 * @scenario	Try to close the clipboard handle with null pointer
 */
int utc_cbhm_close_service_n(void)
{
   int ret = cbhm_close_service(NULL);
   assert_eq(ret, CBHM_ERROR_INVALID_PARAMETER);

   return 0;
}

/**
 * @testcase	utc_cbhm_show_p
 * @since_tizen	3.0
 * @description	Shows clipboard
 * @scenario	Shows clipboard normally
 */
int utc_cbhm_show_p(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   cbhm_selection_type_set(cbhm_handle, CBHM_SEL_TYPE_TEXT);
   int ret = cbhm_show(cbhm_handle);
   assert_eq(ret, CBHM_ERROR_NONE);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_show_n
 * @since_tizen	3.0
 * @description	Shows clipboard
 * @scenario	Try to show clipboard with null pointer
 */
int utc_cbhm_show_n(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   cbhm_selection_type_set(cbhm_handle, CBHM_SEL_TYPE_TEXT);
   int ret = cbhm_show(NULL);
   assert_eq(ret, CBHM_ERROR_INVALID_PARAMETER);

   cbhm_close_service(cbhm_handle);

    return 0;
}

/**
 * @testcase	utc_cbhm_hide_p
 * @since_tizen	3.0
 * @description	Hides clipboard
 * @scenario	Hides clipboard normally
 */
int utc_cbhm_hide_p(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   int ret = cbhm_hide(cbhm_handle);
   assert_eq(ret, CBHM_ERROR_NONE);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_hide_n
 * @since_tizen	3.0
 * @description	Hides clipboard
 * @scenario	Try to hide clipboard with null pointer
 */
int utc_cbhm_hide_n(void)
{
   int ret = cbhm_hide(NULL);
   assert_eq(ret, CBHM_ERROR_INVALID_PARAMETER);

   return 0;
}

/**
 * @testcase	utc_cbhm_selection_set_p1
 * @since_tizen	3.0
 * @description	Copy data to clipboard
 * @scenario	Copy some text to clipboard normally as CBHM_SEL_TYPE_TEXT
 */
int utc_cbhm_selection_set_p1(void)
{
   cbhm_h cbhm_handle;
   char *test_str;

   cbhm_open_service(&cbhm_handle);

   test_str = strdup("clipboard utc test1");

   int ret = cbhm_selection_set(cbhm_handle, CBHM_SEL_TYPE_TEXT, test_str, strlen(test_str));
   free(test_str);

   ecore_timer_add(0.5, _timer_cb, cbhm_handle);
   ecore_main_loop_begin();

   assert_eq(ret, CBHM_ERROR_NONE);

   return 0;
}

/**
 * @testcase	utc_cbhm_selection_set_p2
 * @since_tizen	3.0
 * @description	Copy data to clipboard
 * @scenario	Copy some text to clipboard normally as CBHM_SEL_TYPE_MARKUP
 */
int utc_cbhm_selection_set_p2(void)
{
   cbhm_h cbhm_handle;
   char *test_str;

   cbhm_open_service(&cbhm_handle);

   test_str = strdup("clipboard utc test2");

   int ret = cbhm_selection_set(cbhm_handle, CBHM_SEL_TYPE_MARKUP, test_str, strlen(test_str));
   free(test_str);

   ecore_timer_add(0.5, _timer_cb, cbhm_handle);
   ecore_main_loop_begin();

   assert_eq(ret, CBHM_ERROR_NONE);

   return 0;
}

/**
 * @testcase	utc_cbhm_selection_set_p3
 * @since_tizen	3.0
 * @description	Copy data to clipboard
 * @scenario	Copy some text to clipboard normally as Combined Item
 */
int utc_cbhm_selection_set_p3(void)
{
   cbhm_h cbhm_handle;
   char *test_str;

   cbhm_open_service(&cbhm_handle);

   test_str = strdup("<item absize=240x180 href=file:///usr/share/elementary/images/icon_07.png>clipboard utc test3");

   int ret = cbhm_selection_set(cbhm_handle, CBHM_SEL_TYPE_MARKUP, test_str, strlen(test_str));
   free(test_str);

   ecore_timer_add(0.5, _timer_cb, cbhm_handle);
   ecore_main_loop_begin();

   assert_eq(ret, CBHM_ERROR_NONE);

   return 0;
}

/**
 * @testcase	utc_cbhm_selection_set_p4
 * @since_tizen	3.0
 * @description	Copy data to clipboard
 * @scenario	Copy some text to clipboard normally as CBHM_SEL_TYPE_IMAGE
 */
int utc_cbhm_selection_set_p4(void)
{
   cbhm_h cbhm_handle;
   char *test_str;

   cbhm_open_service(&cbhm_handle);

   test_str = strdup("file:///usr/share/elementary/images/icon_07.png");

   int ret = cbhm_selection_set(cbhm_handle, CBHM_SEL_TYPE_IMAGE, test_str, strlen(test_str));
   free(test_str);

   ecore_timer_add(0.5, _timer_cb, cbhm_handle);
   ecore_main_loop_begin();

   assert_eq(ret, CBHM_ERROR_NONE);

   return 0;
}

/**
 * @testcase	utc_cbhm_selection_set_p5
 * @since_tizen	3.0
 * @description	Copy data to clipboard
 * @scenario	Copy some text to clipboard normally as CBHM_SEL_TYPE_HTML(text)
 */
int utc_cbhm_selection_set_p5(void)
{
   cbhm_h cbhm_handle;
   char *test_str;

   cbhm_open_service(&cbhm_handle);

   test_str = strdup("<p>clipboard utc test5</p>");

   int ret = cbhm_selection_set(cbhm_handle, CBHM_SEL_TYPE_HTML, test_str, strlen(test_str));
   free(test_str);

   ecore_timer_add(0.5, _timer_cb, cbhm_handle);
   ecore_main_loop_begin();

   assert_eq(ret, CBHM_ERROR_NONE);

   return 0;
}

/**
 * @testcase	utc_cbhm_selection_set_p6
 * @since_tizen	3.0
 * @description	Copy data to clipboard
 * @scenario	Copy some text to clipboard normally as CBHM_SEL_TYPE_HTML(image and text)
 */
int utc_cbhm_selection_set_p6(void)
{
   cbhm_h cbhm_handle;
   char *test_str;

   cbhm_open_service(&cbhm_handle);

   test_str = strdup("<img src=\"/usr/share/elementary/images/icon_07.png\"> <p>clipboard utc test5</p>");

   int ret = cbhm_selection_set(cbhm_handle, CBHM_SEL_TYPE_HTML, test_str, strlen(test_str));
   free(test_str);

   ecore_timer_add(0.5, _timer_cb, cbhm_handle);
   ecore_main_loop_begin();

   assert_eq(ret, CBHM_ERROR_NONE);

   return 0;
}

/**
 * @testcase	utc_cbhm_selection_set_n
 * @since_tizen	3.0
 * @description	Copy data to clipboard
 * @scenario	Try to copy data to clipboard with null pointer
 */
int utc_cbhm_selection_set_n(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   int ret = cbhm_selection_set(NULL, CBHM_SEL_TYPE_TEXT, NULL, 0);
   assert_eq(ret, CBHM_ERROR_INVALID_PARAMETER);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_selection_get_p
 * @since_tizen	3.0
 * @description	Gets data from clipboard
 * @scenario	Gets data as CBHM_SEL_TYP_TEXT from clipboard
 */
int utc_cbhm_selection_get_p(void)
{
   cbhm_h cbhm_handle;
   char *test_str = strdup("clipboard utc test3");

   cbhm_open_service(&cbhm_handle);

   cbhm_selection_type_set(cbhm_handle, CBHM_SEL_TYPE_TEXT);
   cbhm_selection_set(cbhm_handle, CBHM_SEL_TYPE_TEXT, test_str, strlen(test_str));
   sleep(2);

   int ret = cbhm_selection_get(cbhm_handle, CBHM_SEL_TYPE_TEXT, _selection_data_cb, NULL);
   free(test_str);
   assert_eq(ret, CBHM_ERROR_NONE);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_selection_get_n
 * @since_tizen	3.0
 * @description	Gets data from clipboard
 * @scenario	Try to get data from clipboard with null pointer
 */
int utc_cbhm_selection_get_n(void)
{
   cbhm_h cbhm_handle;
   char *test_str = strdup("clipboard utc test4");

   cbhm_open_service(&cbhm_handle);

   cbhm_selection_type_set(cbhm_handle, CBHM_SEL_TYPE_TEXT);
   cbhm_selection_set(cbhm_handle, CBHM_SEL_TYPE_TEXT, test_str, strlen(test_str));
   free(test_str);
   sleep(2);

   int ret = cbhm_selection_get(NULL, CBHM_SEL_TYPE_TEXT, NULL, NULL);
   assert_eq(ret, CBHM_ERROR_INVALID_PARAMETER);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_item_count_get_p
 * @since_tizen	3.0
 * @description	Gets item count of clipboard items
 * @scenario	Gets clipboard item count normally
 */
int utc_cbhm_item_count_get_p(void)
{
   cbhm_h cbhm_handle;
   char *test_str = strdup("clipboard utc test5");

   cbhm_open_service(&cbhm_handle);

   cbhm_selection_set(cbhm_handle, CBHM_SEL_TYPE_TEXT, test_str, strlen(test_str));
   int ret = cbhm_item_count_get(cbhm_handle);
   free(test_str);
   assert(ret != CBHM_ERROR_INVALID_PARAMETER && ret > -1);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_item_count_get_n
 * @since_tizen	3.0
 * @description	Gets item count of clipboard items
 * @scenario	Try to get clipboard item count with null pointer
 */
int utc_cbhm_item_count_get_n(void)
{
   int ret = cbhm_item_count_get(NULL);
   assert_eq(ret, CBHM_ERROR_INVALID_PARAMETER);

   return 0;
}

/**
 * @testcase	utc_cbhm_selection_type_set_p
 * @since_tizen	3.0
 * @description	Sets selection type
 * @scenario	Sets selection type as CBHM_SEL_TYPE_TEXT
 */
int utc_cbhm_selection_type_set_p(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   int ret = cbhm_selection_type_set(cbhm_handle, CBHM_SEL_TYPE_TEXT);
   assert_eq(ret, CBHM_ERROR_NONE);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_selection_type_set_n
 * @since_tizen	3.0
 * @description	Sets selection type
 * @scenario	Try to set selection type with null pointer
 */
int utc_cbhm_selection_type_set_n(void)
{
   int ret = cbhm_selection_type_set(NULL, CBHM_SEL_TYPE_TEXT);
   assert_eq(ret, CBHM_ERROR_INVALID_PARAMETER);

   return 0;
}

/**
 * @testcase	utc_cbhm_selection_type_get_p
 * @since_tizen	3.0
 * @description	Gets selection type
 * @scenario	Gets selection type from clipboard handle
 */
int utc_cbhm_selection_type_get_p(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   cbhm_sel_type_e type = CBHM_SEL_TYPE_NONE;
   int ret = cbhm_selection_type_get(cbhm_handle, &type);
   assert_eq(ret, CBHM_ERROR_NONE);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_selection_type_get_n
 * @since_tizen	3.0
 * @description	Gets selection type
 * @scenario	Try to get selection type with null pointer
 */
int utc_cbhm_selection_type_get_n(void)
{
   cbhm_sel_type_e type = CBHM_SEL_TYPE_NONE;
   int ret = cbhm_selection_type_get(NULL, &type);
   assert_eq(ret, CBHM_ERROR_INVALID_PARAMETER);

   return 0;
}

/**
 * @testcase	utc_cbhm_item_selected_callback_add_p
 * @since_tizen	3.0
 * @description	Adds clipboard item selected callback
 * @scenario	Adds clipboard item selected callback normally
 */
int utc_cbhm_item_selected_callback_add_p(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   int ret = cbhm_item_selected_callback_add(cbhm_handle, _selection_clicked_cb, NULL);
   assert_eq(ret, CBHM_ERROR_NONE);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_item_selected_callback_add_n
 * @since_tizen	3.0
 * @description	Adds clipboard item selected callback
 * @scenario	Try to add clipboard item selected callback with null pointer
 */
int utc_cbhm_item_selected_callback_add_n(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   int ret = cbhm_item_selected_callback_add(NULL, NULL, NULL);
   assert_eq(ret, CBHM_ERROR_INVALID_PARAMETER);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_item_selected_callback_add_p
 * @since_tizen	4.0
 * @description	Removes clipboard item selected callback
 * @scenario	Removes clipboard item selected callback normally
 */
int utc_cbhm_item_selected_callback_remove_p(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   int ret = cbhm_item_selected_callback_add(cbhm_handle, _selection_clicked_cb, NULL);
   assert_eq(ret, CBHM_ERROR_NONE);

   ret = cbhm_item_selected_callback_remove(cbhm_handle, _selection_clicked_cb, NULL);
   assert_eq(ret, CBHM_ERROR_NONE);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_item_selected_callback_add_n
 * @since_tizen	4.0
 * @description	Removes clipboard item selected callback
 * @scenario	Try to remove clipboard item selected callback with null pointer
 */
int utc_cbhm_item_selected_callback_remove_n(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   int ret = cbhm_item_selected_callback_remove(NULL, NULL, NULL);
   assert_eq(ret, CBHM_ERROR_INVALID_PARAMETER);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_item_selected_callback_add_p
 * @since_tizen	4.0
 * @description	Adds clipboard item selected callback
 * @scenario	Adds clipboard item selected callback normally
 */
int utc_cbhm_item_changed_callback_add_p(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   int ret = cbhm_item_selected_callback_add(cbhm_handle, _item_changed_cb, NULL);
   assert_eq(ret, CBHM_ERROR_NONE);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_item_selected_callback_add_n
 * @since_tizen	3.0
 * @description	Adds clipboard item selected callback
 * @scenario	Try to add clipboard item selected callback with null pointer
 */
int utc_cbhm_item_changed_callback_add_n(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   int ret = cbhm_item_selected_callback_add(NULL, NULL, NULL);
   assert_eq(ret, CBHM_ERROR_INVALID_PARAMETER);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_item_changed_callback_remove_p
 * @since_tizen	4.0
 * @description	Removes clipboard item changed callback
 * @scenario	Removes clipboard item changed callback normally
 */
int utc_cbhm_item_changed_callback_remove_p(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   int ret = cbhm_item_changed_callback_add(cbhm_handle, _item_changed_cb, NULL);
   assert_eq(ret, CBHM_ERROR_NONE);

   ret = cbhm_item_changed_callback_remove(cbhm_handle, _item_changed_cb, NULL);
   assert_eq(ret, CBHM_ERROR_NONE);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_item_changed_callback_remove_n
 * @since_tizen	4.0
 * @description	Removes clipboard item changed callback
 * @scenario	Try to remove clipboard item changed callback with null pointer
 */
int utc_cbhm_item_changed_callback_remove_n(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   int ret = cbhm_item_changed_callback_remove(NULL, NULL, NULL);
   assert_eq(ret, CBHM_ERROR_INVALID_PARAMETER);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_state_get_p
 * @since_tizen	4.0
 * @description	Gets state of clipboard
 * @scenario	Gets current state of clipboard normaly
 */
int utc_cbhm_state_get_p(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   cbhm_state_type_e state;
   int ret = cbhm_state_get(cbhm_handle, &state);
   assert_eq(state, CBHM_STATE_HIDE);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_state_get_n
 * @since_tizen	4.0
 * @description	Gets state of clipboard
 * @scenario	Try to get state of clipboard with null pointer
 */
int utc_cbhm_state_get_n(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   cbhm_state_type_e state;
   int ret = cbhm_state_get(cbhm_handle, NULL);
   assert_eq(ret, CBHM_ERROR_INVALID_PARAMETER);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_latest_item_type_get_p
 * @since_tizen	4.0
 * @description	Gets latest item type of clipboard
 * @scenario	Gets latest item type of clipboard normaly
 */
int utc_cbhm_latest_item_type_get_p(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   cbhm_sel_type_e type;
   int ret = cbhm_latest_item_type_get(cbhm_handle, &type);
   assert_eq(ret, CBHM_ERROR_NONE);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_latest_item_type_get_n
 * @since_tizen	4.0
 * @description	Gets latest item type of clipboard
 * @scenario	Try to get latest item type with null pointer
 */
int utc_cbhm_latest_item_type_get_n(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   int ret = cbhm_latest_item_type_get(NULL, NULL);
   assert_eq(ret, CBHM_ERROR_INVALID_PARAMETER);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_monitor_callback_add_p
 * @since_tizen	4.0
 * @description	Adds clipboard monitor callback
 * @scenario	Adds clipboard monitor callback normally
 */
int utc_cbhm_monitor_callback_add_p(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   int ret = cbhm_monitor_callback_add(cbhm_handle, _monitor_cb, NULL);
   assert_eq(ret, CBHM_ERROR_NONE);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_monitor_callback_add_n
 * @since_tizen	4.0
 * @description	Adds clipboard monitor callback
 * @scenario	Try to add clipboard monitor callback with null pointer
 */
int utc_cbhm_monitor_callback_add_n(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   int ret = cbhm_monitor_callback_add(NULL, NULL, NULL);
   assert_eq(ret, CBHM_ERROR_INVALID_PARAMETER);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_monitor_callback_remove_p
 * @since_tizen	4.0
 * @description	Removes clipboard monitor callback
 * @scenario	Removes clipboard monitor callback normally
 */
int utc_cbhm_monitor_callback_remove_p(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   int ret = cbhm_monitor_callback_add(cbhm_handle, _monitor_cb, NULL);
   assert_eq(ret, CBHM_ERROR_NONE);

   ret = cbhm_monitor_callback_remove(cbhm_handle, _monitor_cb, NULL);
   assert_eq(ret, CBHM_ERROR_NONE);

   cbhm_close_service(cbhm_handle);

   return 0;
}

/**
 * @testcase	utc_cbhm_monitor_callback_remove_n
 * @since_tizen	4.0
 * @description	Removes clipboard monitor callback
 * @scenario	Try to remove clipboard monitor callback with null pointer
 */
int utc_cbhm_monitor_callback_remove_n(void)
{
   cbhm_h cbhm_handle;
   cbhm_open_service(&cbhm_handle);

   int ret = cbhm_monitor_callback_remove(NULL, NULL, NULL);
   assert_eq(ret, CBHM_ERROR_INVALID_PARAMETER);

   cbhm_close_service(cbhm_handle);

   return 0;
}
