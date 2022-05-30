//
// Copyright (c) 2016 Samsung Electronics Co., Ltd.
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
#include "utc_webkit2_ewk.h"

#ifndef NULL
#define NULL    0x0
#endif

static Ecore_Timer* emergency_exit_timer;
static Eina_Bool null_intercept_request;
static const char expected_title[] = "Testing Sample Page";

// results:
static Eina_Bool timeout;
static Eina_Bool load_success;
static Eina_Bool callback_called;
static Eina_Bool ignore_intercept_request_result;

static Eina_Bool emergency_exit_func(void* user_data) {
  timeout = EINA_TRUE;
  Ecore_Timer** timer = (Ecore_Timer**)user_data;
  *timer = NULL;
  utc_webkit2_main_loop_quit();
  return ECORE_CALLBACK_CANCEL;
}

static void load_finished(void* data, Evas_Object* webview, void* event_info) {
  load_success = EINA_TRUE;
  utc_webkit2_main_loop_quit();
}

static void intercept_request_callback(Evas_Object* o, Ewk_Intercept_Request* intercept_request, void* user_data) {
  callback_called = EINA_TRUE;
  ignore_intercept_request_result = ewk_intercept_request_ignore(null_intercept_request ? NULL : intercept_request);
}

/**
 * @function		utc_webkit2_ewk_intercept_request_ignore_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_intercept_request_ignore_func_startup(void)
{
  emergency_exit_timer = NULL;
  timeout = EINA_FALSE;
  load_success = EINA_FALSE;
  callback_called = EINA_FALSE;
  null_intercept_request = EINA_FALSE;
  ignore_intercept_request_result = EINA_FALSE;

  utc_webkit2_ewk_test_init();

  ewk_context_intercept_request_callback_set(ewk_view_context_get(test_view.webview), intercept_request_callback, NULL);
  evas_object_smart_callback_add(test_view.webview, "load,finished", load_finished, NULL);
}

/**
 * @function		utc_webkit2_ewk_intercept_request_ignore_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_intercept_request_ignore_func_cleanup(void)
{
  if (emergency_exit_timer) {
    ecore_timer_del(emergency_exit_timer);
    emergency_exit_timer = NULL;
  }

  evas_object_smart_callback_del(test_view.webview, "load,finished", load_finished);

  utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_intercept_request_ignore_p
 * @since_tizen		3.0
 * @description		Set callback for intercepting requests
 * @scenario		Create Webkit View\n
 *                  Set intercept request callback\n
 *                  Ignore request\n
 *                  Check if request was handled normally
 */
int utc_webkit2_ewk_intercept_request_ignore_p(void)
{
  emergency_exit_timer = ecore_timer_add(5, emergency_exit_func, &emergency_exit_timer);
  ewk_view_url_set(test_view.webview, COMMON_SAMPLE_HTML_FILE);
  utc_webkit2_main_loop_begin();
  assert(!timeout);
  assert(load_success);
  assert(callback_called);
  assert(ignore_intercept_request_result);
  assert(strcmp(ewk_view_title_get(test_view.webview), expected_title) == 0);

  return 0;
}

/**
 * @testcase		utc_webkit2_ewk_intercept_request_ignore_n
 * @since_tizen		3.0
 * @description		Set callback for intercepting requests
 * @scenario		Check operation for entering incorrect parameter
 */
int utc_webkit2_ewk_intercept_request_ignore_n(void)
{
  emergency_exit_timer = ecore_timer_add(5, emergency_exit_func, &emergency_exit_timer);
  null_intercept_request = EINA_TRUE;
  ewk_view_url_set(test_view.webview, COMMON_SAMPLE_HTML_FILE);
  utc_webkit2_main_loop_begin();
  assert(timeout);
  assert(!load_success);
  assert(callback_called);
  assert(!ignore_intercept_request_result);

  return 0;
}

