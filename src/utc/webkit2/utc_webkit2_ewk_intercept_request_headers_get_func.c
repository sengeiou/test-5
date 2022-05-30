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
static const char intercept_url[] = "http://request.intercept.ewk.api.test/";

// results:
static const Eina_Hash* headers;
static char* accept_header;
static char* user_agent_header;

static Eina_Bool emergency_exit_func(void* user_data) {
  Ecore_Timer** timer = (Ecore_Timer**)user_data;
  *timer = NULL;
  utc_webkit2_main_loop_quit();
  return ECORE_CALLBACK_CANCEL;
}

static void intercept_request_callback(Evas_Object* o, Ewk_Intercept_Request* intercept_request, void* user_data) {
  headers = ewk_intercept_request_headers_get(null_intercept_request ? NULL : intercept_request);
  if (headers) {
    accept_header = (char*)eina_hash_find(headers, "Accept");
    if (accept_header) {
      accept_header = strdup(accept_header);
    }
    user_agent_header = (char*)eina_hash_find(headers, "User-Agent");
    if (user_agent_header) {
      user_agent_header = strdup(user_agent_header);
    }
  }
}

/**
 * @function		utc_webkit2_ewk_intercept_request_headers_get_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_intercept_request_headers_get_func_startup(void)
{
  emergency_exit_timer = NULL;
  headers = NULL;
  accept_header = NULL;
  user_agent_header = NULL;
  null_intercept_request = EINA_FALSE;

  utc_webkit2_ewk_test_init();

  ewk_context_intercept_request_callback_set(ewk_view_context_get(test_view.webview), intercept_request_callback, NULL);
}

/**
 * @function		utc_webkit2_ewk_intercept_request_headers_get_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_intercept_request_headers_get_func_cleanup(void)
{
  free(accept_header);
  free(user_agent_header);

  if (emergency_exit_timer) {
    ecore_timer_del(emergency_exit_timer);
    emergency_exit_timer = NULL;
  }

  utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_intercept_request_headers_get_p
 * @since_tizen		3.0
 * @description		Set callback for intercepting requests
 * @scenario		Create Webkit View\n
 *                  Set intercept request callback\n
 *                  Get intercepted request's headers\n
 *                  Check if right headers were returned
 */
int utc_webkit2_ewk_intercept_request_headers_get_p(void)
{
  emergency_exit_timer = ecore_timer_add(5, emergency_exit_func, &emergency_exit_timer);
  ewk_view_url_set(test_view.webview, intercept_url);
  utc_webkit2_main_loop_begin();
  assert(headers);
  assert(accept_header);
  assert(strstr(accept_header, "text/html") != NULL);
  assert(user_agent_header);
  assert(strcmp(user_agent_header, ewk_view_user_agent_get(test_view.webview)) == 0);

  return 0;
}

/**
 * @testcase		utc_webkit2_ewk_intercept_request_headers_get_n
 * @since_tizen		3.0
 * @description		Set callback for intercepting requests
 * @scenario		Check operation for entering incorrect parameter
 */
int utc_webkit2_ewk_intercept_request_headers_get_n(void)
{
  null_intercept_request = EINA_TRUE;
  emergency_exit_timer = ecore_timer_add(5, emergency_exit_func, &emergency_exit_timer);
  ewk_view_url_set(test_view.webview, intercept_url);
  utc_webkit2_main_loop_begin();
  assert(!headers);

  return 0;
}

