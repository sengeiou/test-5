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
#include <ewk_cookie_manager.h>

/**
 * @function            utc_webkit2_ewk_cookie_manager_persistent_storage_set_func_startup
 * @description         Called before each test
 * @parameter           NA
 * @return                      NA
 */
int utc_webkit2_ewk_cookie_manager_persistent_storage_set_func_startup(void)
{
  utc_webkit2_ewk_test_init();
}

/**
 * @function            utc_webkit2_ewk_cookie_manager_persistent_storage_set_p
 * @description         Positive test with sqlite based storage
 * @parameter           NA
 * @return                      NA
 */
int utc_webkit2_ewk_cookie_manager_persistent_storage_set_p(void)
{
  char *path = "/tmp/mycookiestoragedir";
  Ewk_Cookie_Manager* cookieManager = ewk_context_cookie_manager_get(
    ewk_view_context_get(test_view.webview));

  ewk_cookie_manager_persistent_storage_set(cookieManager, path,
    EWK_COOKIE_PERSISTENT_STORAGE_SQLITE);
  return 0;
}

/**
 * @function            utc_webkit2_ewk_cookie_manager_persistent_storage_set_p1
 * @description         Positive test with text file based storage
 * @parameter           NA
 * @return                      NA
 */
int utc_webkit2_ewk_cookie_manager_persistent_storage_set_p1(void)
{
  char *path = "/tmp/mycookiestoragedir";
  Ewk_Cookie_Manager* cookieManager = ewk_context_cookie_manager_get(
    ewk_view_context_get(test_view.webview));

  ewk_cookie_manager_persistent_storage_set(cookieManager, path,
    EWK_COOKIE_PERSISTENT_STORAGE_TEXT);

  return 0;
}

/**
 * @function            utc_webkit2_ewk_cookie_manager_persistent_storage_set_n
 * @description         Negative test with setting NULL as a persistent path
 * @parameter           NA
 * @return                      NA
 */
int utc_webkit2_ewk_cookie_manager_persistent_storage_set_n(void)
{
  char *path = NULL;
  Ewk_Cookie_Manager* cookieManager = ewk_context_cookie_manager_get(
    ewk_view_context_get(test_view.webview));

  ewk_cookie_manager_persistent_storage_set(cookieManager, path,
    EWK_COOKIE_PERSISTENT_STORAGE_SQLITE);

  return 0;
}


/**
 * @function            utc_webkit2_ewk_cookie_manager_persistent_storage_set_func_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return                      NA
 */
void utc_webkit2_ewk_cookie_manager_persistent_storage_set_func_cleanup(void)
{
   utc_webkit2_ewk_test_end();
}
