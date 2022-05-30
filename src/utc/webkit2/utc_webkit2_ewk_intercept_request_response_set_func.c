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
static const char body_format[] = "<html><head><title>%s</title></head>"
                                  "<body>Hello, Request Intercept!</body></html>";
static const char headers_format[] = "200 OK\r\n"
                                     "Content-Type: text/html; charset=UTF-8\r\n"
                                     "Content-Length: %zu\r\n"
                                     "\r\n";
static const char title_expected[] = "RESPONSE SET SUCCESS";
static char* body_done;
static char* headers_done;
static Eina_Bool null_intercept_request;
static Eina_Bool null_body;
static Eina_Bool null_headers;
static size_t data_to_write;

// results:
static Eina_Bool timeout = EINA_FALSE;
static Eina_Bool load_success = EINA_FALSE;
static Eina_Bool response_set_result = EINA_FALSE;

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
  const char* url = ewk_intercept_request_url_get(intercept_request);
  if (strcmp(url, intercept_url) == 0) {
    response_set_result = ewk_intercept_request_response_set(
        null_intercept_request ? NULL: intercept_request,
        null_headers ? NULL : headers_done,
        null_body ? NULL : body_done,
        data_to_write);
  } else {
    ewk_intercept_request_ignore(intercept_request);
  }
}

/**
 * @function		utc_webkit2_ewk_intercept_request_response_set_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_intercept_request_response_set_func_startup(void)
{
  emergency_exit_timer = NULL;
  null_intercept_request = EINA_FALSE;
  null_headers = EINA_FALSE;
  null_body = EINA_FALSE;
  timeout = EINA_FALSE;
  load_success = EINA_FALSE;
  response_set_result = EINA_FALSE;

  int size = snprintf(NULL, 0, body_format, title_expected);
  body_done = (char*)malloc((size + 1) * sizeof(char));
  if (body_done) {
    snprintf(body_done, size + 1, body_format, title_expected);
    data_to_write = strlen(body_done);
  } else {
    data_to_write = 0;
  }

  size = snprintf(NULL, 0, headers_format, data_to_write);
  headers_done = (char*)malloc((size + 1) * sizeof(char));
  if (headers_done)
    snprintf(headers_done, size + 1, headers_format, data_to_write);

  utc_webkit2_ewk_test_init();

  ewk_context_intercept_request_callback_set(ewk_view_context_get(test_view.webview), intercept_request_callback, NULL);
  evas_object_smart_callback_add(test_view.webview, "load,finished", load_finished, NULL);
}

/**
 * @function		utc_webkit2_ewk_intercept_request_response_set_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_intercept_request_response_set_func_cleanup(void)
{
  free(body_done);
  free(headers_done);

  if (emergency_exit_timer) {
    ecore_timer_del(emergency_exit_timer);
    emergency_exit_timer = NULL;
  }

  evas_object_smart_callback_del(test_view.webview, "load,finished", load_finished);

  utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_intercept_request_response_set_p
 * @since_tizen		3.0
 * @description		Write response to intercepted request
 * @scenario		Create Webkit View\n
 *                  Intercept request\n
 *                  Write custom response\n
 *                  Validate custom response
 */
int utc_webkit2_ewk_intercept_request_response_set_p(void)
{
  emergency_exit_timer = ecore_timer_add(5, emergency_exit_func, &emergency_exit_timer);
  ewk_view_url_set(test_view.webview, intercept_url);
  utc_webkit2_main_loop_begin();
  assert(!timeout);
  assert(load_success);
  assert(response_set_result);
  assert(strcmp(ewk_view_title_get(test_view.webview), title_expected) == 0);

  return 0;
}

/**
 * @testcase		utc_webkit2_ewk_intercept_request_response_set_n
 * @since_tizen		3.0
 * @description		Write response to intercepted request
 * @scenario		Check operation for entering incorrect parameter
 */
int utc_webkit2_ewk_intercept_request_response_set_n(void)
{
  emergency_exit_timer = ecore_timer_add(5, emergency_exit_func, &emergency_exit_timer);
  null_intercept_request = EINA_TRUE;
  ewk_view_url_set(test_view.webview, intercept_url);
  utc_webkit2_main_loop_begin();
  assert(timeout);
  assert(!response_set_result);

  return 0;
}

/**
 * @testcase		utc_webkit2_ewk_intercept_request_response_set_n1
 * @since_tizen		3.0
 * @description		Write response to intercepted request
 * @scenario		Check operation for entering incorrect parameter
 */
int utc_webkit2_ewk_intercept_request_response_set_n1(void)
{
  emergency_exit_timer = ecore_timer_add(5, emergency_exit_func, &emergency_exit_timer);
  null_headers = EINA_TRUE;
  ewk_view_url_set(test_view.webview, intercept_url);
  utc_webkit2_main_loop_begin();
  assert(timeout);
  assert(!response_set_result);

  return 0;
}

/**
 * @testcase		utc_webkit2_ewk_intercept_request_response_set_n2
 * @since_tizen		3.0
 * @description		Write response to intercepted request
 * @scenario		Check operation for entering incorrect parameter
 */
int utc_webkit2_ewk_intercept_request_response_set_n2(void)
{
  emergency_exit_timer = ecore_timer_add(5, emergency_exit_func, &emergency_exit_timer);
  null_body = EINA_TRUE;
  ewk_view_url_set(test_view.webview, intercept_url);
  utc_webkit2_main_loop_begin();
  assert(timeout);
  assert(!response_set_result);

  return 0;
}
