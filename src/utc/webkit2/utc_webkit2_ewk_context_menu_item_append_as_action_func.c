/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * */

#include "assert.h"
#include "utc_webkit2_ewk.h"

enum {
  CUSTOM_CONTEXT_MENU_ITEM_BASE_TAG = EWK_CONTEXT_MENU_ITEM_BASE_APPLICATION_TAG,
  CUSTOM_CONTEXT_MENU_ITEM_TEST_TAG
};

/**
 * @function		utc_webkit2_ewk_context_menu_item_append_as_action_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_context_menu_item_append_as_action_func_startup(void)
{
	utc_webkit2_ewk_test_init();
}

/**
 * @function		utc_webkit2_ewk_context_menu_item_append_as_action_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_context_menu_item_append_as_action_func_cleanup(void)
{
	utc_webkit2_ewk_test_end();
}

/**
 * @testcase		utc_webkit2_ewk_context_menu_item_append_as_action_n
 * @since_tizen		2.3
 * @description		Appends context menu item based on action
 * @scenario		Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_context_menu_item_append_as_action_n(void)
{
	Eina_Bool result = ewk_context_menu_item_append_as_action(NULL, CUSTOM_CONTEXT_MENU_ITEM_TEST_TAG, "test", EINA_TRUE);
	assert_eq(result, EINA_FALSE);
	return 0;
}
