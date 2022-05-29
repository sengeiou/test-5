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
#include <stdio.h>
#include "assert.h"
#include "utc_webkit2_ewk.h"

/**
 * @function		utc_webkit2_ewk_init_func_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_init_func_startup(void)
{
    elm_init(0, NULL);
}

/**
 * @function		utc_webkit2_ewk_init_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_webkit2_ewk_init_func_cleanup(void)
{
    elm_shutdown();
}


/**
 * @testcase		utc_webkit2_ewk_init_p
 * @since_tizen		2.3
 * @description		Initialise webkit instance
 * @scenario		Initialise/Increases reference count of webkit instance
 */
int utc_webkit2_ewk_init_p(void)
{
    assert_neq(ewk_init(), 0);
    return 0;
}


/**
 * @testcase		utc_webkit2_ewk_init_n
 * @since_tizen		2.3
 * @description		Initialise webkit instance
 * @scenario		Check operation entered incorrect parameter
 */
int utc_webkit2_ewk_init_n(void)
{
    ewk_init();
    int ewk_count = ewk_shutdown();
    assert_eq(ewk_init(), ewk_count + 1);
    return 0;
}
