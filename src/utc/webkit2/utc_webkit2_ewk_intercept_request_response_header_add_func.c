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

#define LENGTH_HEADER_BUFFER_SIZE 20

static Ecore_Timer* emergency_exit_timer;

static const char intercept_url[] = "http://request.intercept.ewk.api.test/";
static const char intercept_url_ajax[] = "http://request.intercept.ewk.api.test/ajax/";
static const char base_title[] = "intercept request";
static const char body_ajax_test_format[] =
    "document.title = '%s: ' + this.getResponseHeader('%s')"
    " + ', %s: ' + this.getResponseHeader('%s');";
static const char body_format[] =
    "<html><head><title>%s</title></head>"
    "<body><script>"
    "function ajax_listener() {%s}"
    "window.onload = function() {"
    "  setTimeout("
    "    function() {"
    "      var ajax = new XMLHttpRequest();"
    "      ajax.onload = ajax_listener;"
    "      ajax.open('GET','%s', true);"
    "      ajax.send();"
    "    }, 1000);"
    "  }"
    "</script>"
    "</body></html>";
static const char body_ajax_done[] = "dummy ajax payload";
static char* body_ajax_test_done;
static char* body_done;
static const char test_header_field_1[] = "TEST_FIELD_1";
static const char test_header_value_1[] = "TEST_VALUE_1";
static const char test_header_field_2[] = "TEST_FIELD_2";
static const char test_header_value_2[] = "TEST_VALUE_2";
static const char expected_title_format[] = "%s: %s, %s: %s";
static char* expected_title_done;

// results:
static Eina_Bool timeout;
static Eina_Bool header_add_1_result;
static Eina_Bool header_add_2_result;
static Eina_Bool load_success;
static int first_title_equal_base_title;

static Eina_Bool emergency_exit_func(void* user_data) {
  timeout = EINA_TRUE;
  Ecore_Timer** timer = (Ecore_Timer**)user_data;
  *timer = NULL;
  utc_webkit2_main_loop_quit();
  return ECORE_CALLBACK_CANCEL;
}

static void load_finished(void* data, Evas_Object* webview, void* event_info) {
  first_title_equal_base_title = strcmp(ewk_view_title_get(test_view.webview), base_title) == 0;
  load_success = EINA_TRUE;
}

static void load_error(void* data, Evas_Object* webview, void* event_info) {
  load_success = EINA_FALSE;
  utc_webkit2_main_loop_quit();
}

static void title_changed(void* data, Evas_Object* webview, void* event_info) {
  const char* title = ewk_view_title_get(test_view.webview);
  if (load_success && strcmp(title, base_title) != 0) {
    utc_webkit2_main_loop_quit();
  }
}

// AJAX request is used, because it is only way to check response headers in JS+HTML
static void intercept_request_callback(Evas_Object* o, Ewk_Intercept_Request* intercept_request, void* user_data) {
  const char* url = ewk_intercept_request_url_get(intercept_request);
  const char* body;
  if (strcmp(url, intercept_url) == 0) {
    body = body_done;
  } else if (strcmp(url, intercept_url_ajax) == 0) {
    body = body_ajax_done;
  } else {
    ewk_intercept_request_ignore(intercept_request);
    return;
  }
  int body_length = strlen(body);
  char length_header[LENGTH_HEADER_BUFFER_SIZE];
  snprintf((char*)length_header, LENGTH_HEADER_BUFFER_SIZE - 1, "%d", body_length);
  ewk_intercept_request_response_status_set(intercept_request, 200, NULL);
  ewk_intercept_request_response_header_add(intercept_request, "Content-Type", "text/html; charset=UTF-8");
  ewk_intercept_request_response_header_add(intercept_request, "Content-Length", (char*)length_header);
  ewk_intercept_request_response_header_add(intercept_request, "Access-Control-Allow-Origin", "*");
  header_add_1_result = ewk_intercept_request_response_header_add(intercept_request, test_header_field_1, test_header_value_1);
  header_add_2_result = ewk_intercept_request_response_header_add(intercept_request, test_header_field_2, test_header_value_2);
  ewk_intercept_request_response_body_set(intercept_request, body, body_length);
}

static void intercept_request_callback_neg_1(Evas_Object* o, Ewk_Intercept_Request* intercept_request, void* user_data) {
  header_add_1_result = ewk_intercept_request_response_header_add(NULL, test_header_field_1, test_header_value_1);
}

static void intercept_request_callback_neg_2(Evas_Object* o, Ewk_Intercept_Request* intercept_request, void* user_data) {
  header_add_1_result = ewk_intercept_request_response_header_add(intercept_request, NULL, test_header_value_1);
}

static void intercept_request_callback_neg_3(Evas_Object* o, Ewk_Intercept_Request* intercept_request, void* user_data) {
  header_add_1_result = ewk_intercept_request_response_header_add(intercept_request, test_header_field_1, NULL);
}

/**
 * @function		utc_webkit2_ewk_intercept_request_response_header_add_func_startup
 * @description		Called before positive test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_intercept_request_response_header_add_func_startup(void)
{
  header_add_1_result = EINA_FALSE;
  header_add_2_result = EINA_FALSE;
  load_success = EINA_FALSE;
  first_title_equal_base_title = 0;

  int size;
  size = snprintf(NULL, 0, body_ajax_test_format, test_header_field_1, test_header_field_1, test_header_field_2, test_header_field_2);
  body_ajax_test_done = (char*)malloc((size + 1) * sizeof(char));
  if (body_ajax_test_done) {
    snprintf(body_ajax_test_done, size+1, body_ajax_test_format, test_header_field_1, test_header_field_1, test_header_field_2, test_header_field_2);

    size = snprintf(NULL, 0, body_format, base_title, body_ajax_test_done, intercept_url_ajax);
    body_done = (char*)malloc((size + 1) * sizeof(char));
    if (body_done)
      snprintf(body_done, size+1, body_format, base_title, body_ajax_test_done, intercept_url_ajax);
  }

  size = snprintf(NULL, 0, expected_title_format, test_header_field_1, test_header_value_1, test_header_field_2, test_header_value_2);
  expected_title_done = (char*)malloc((size + 1) * sizeof(char));
  if (expected_title_done)
    snprintf(expected_title_done, size+1, expected_title_format, test_header_field_1, test_header_value_1, test_header_field_2, test_header_value_2);

  utc_webkit2_ewk_test_init();

  ewk_context_intercept_request_callback_set(ewk_view_context_get(test_view.webview), intercept_request_callback, NULL);
  evas_object_smart_callback_add(test_view.webview, "title,changed", title_changed, NULL);
  evas_object_smart_callback_add(test_view.webview, "load,finished", load_finished, NULL);
  evas_object_smart_callback_add(test_view.webview, "load,error", load_error, NULL);
}

/**
 * @function		utc_webkit2_ewk_intercept_request_response_header_add_func_cleanup
 * @description		Called after positive test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_intercept_request_response_header_add_func_cleanup(void)
{
  free(body_done);
  free(body_ajax_test_done);
  free(expected_title_done);

  evas_object_smart_callback_del(test_view.webview, "title,changed", title_changed);
  evas_object_smart_callback_del(test_view.webview, "load,finished", load_finished);
  evas_object_smart_callback_del(test_view.webview, "load,error", load_error);

  utc_webkit2_ewk_test_end();
}

/**
 * @function		utc_webkit2_ewk_intercept_request_response_header_add_func_neg_startup
 * @description		Called before negative test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_intercept_request_response_header_add_func_neg_startup(void)
{
  header_add_1_result = EINA_TRUE;
  emergency_exit_timer = NULL;
  timeout = EINA_FALSE;

  utc_webkit2_ewk_test_init();
}

/**
 * @function		utc_webkit2_ewk_intercept_request_response_header_add_func_neg_cleanup
 * @description		Called after positive test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_intercept_request_response_header_add_func_neg_cleanup(void)
{
  if (emergency_exit_timer) {
    ecore_timer_del(emergency_exit_timer);
    emergency_exit_timer = NULL;
  }

  utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_intercept_request_response_header_add_p
 * @since_tizen		3.0
 * @description		Adds headers for intercepted request response
 * @scenario		 Create Webkit View\n
 *                  Intercept request\n
 *                  Write response with additional headers\n
 *                  Validate response headers
 */
int utc_webkit2_ewk_intercept_request_response_header_add_p(void)
{
  ewk_view_url_set(test_view.webview, intercept_url);
  utc_webkit2_main_loop_begin();

  assert(load_success);
  assert(header_add_1_result);
  assert(header_add_2_result);
  assert(first_title_equal_base_title);
  assert(strcmp(expected_title_done, ewk_view_title_get(test_view.webview)) == 0);

  return 0;
}

/**
 * @testcase		utc_webkit2_ewk_intercept_request_response_header_add_n
 * @since_tizen		3.0
 * @description		Adds headers for intercepted request response
 * @scenario		 Check operation for entering incorrect parameter
 */
int utc_webkit2_ewk_intercept_request_response_header_add_n(void)
{
  emergency_exit_timer = ecore_timer_add(5, emergency_exit_func, &emergency_exit_timer);
  ewk_context_intercept_request_callback_set(ewk_view_context_get(test_view.webview), intercept_request_callback_neg_1, NULL);
  ewk_view_url_set(test_view.webview, intercept_url);
  utc_webkit2_main_loop_begin();
  assert(timeout);
  assert(!header_add_1_result);

  return 0;
}

/**
 * @testcase		utc_webkit2_ewk_intercept_request_response_header_add_n1
 * @since_tizen		3.0
 * @description		Adds headers for intercepted request response
 * @scenario		 Check operation for entering incorrect parameter
 */
int utc_webkit2_ewk_intercept_request_response_header_add_n1(void)
{
  emergency_exit_timer = ecore_timer_add(5, emergency_exit_func, &emergency_exit_timer);
  ewk_context_intercept_request_callback_set(ewk_view_context_get(test_view.webview), intercept_request_callback_neg_2, NULL);
  ewk_view_url_set(test_view.webview, intercept_url);
  utc_webkit2_main_loop_begin();
  assert(timeout);
  assert(!header_add_1_result);

  return 0;
}

/**
 * @testcase		utc_webkit2_ewk_intercept_request_response_header_add_n2
 * @since_tizen		3.0
 * @description		Adds headers for intercepted request response
 * @scenario		 Check operation for entering incorrect parameter
 */
int utc_webkit2_ewk_intercept_request_response_header_add_n2(void)
{
  emergency_exit_timer = ecore_timer_add(5, emergency_exit_func, &emergency_exit_timer);
  ewk_context_intercept_request_callback_set(ewk_view_context_get(test_view.webview), intercept_request_callback_neg_3, NULL);
  ewk_view_url_set(test_view.webview, intercept_url);
  utc_webkit2_main_loop_begin();
  assert(timeout);
  assert(!header_add_1_result);

  return 0;
}
