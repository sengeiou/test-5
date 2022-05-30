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
#include <bundle.h>
#include <string.h>

//& set: BundleGetStrArrayFunc

static bundle *b = NULL;

/**
 * @function		utc_ApplicationFW_bundle_get_str_array_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_ApplicationFW_bundle_get_str_array_startup(void)
{
    b = bundle_create();
}

/**
 * @function		utc_ApplicationFW_bundle_get_str_array_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_ApplicationFW_bundle_get_str_array_cleanup(void)
{
    bundle_free(b);
    b = NULL;
}

/**
 * @testcase		utc_ApplicationFW_bundle_get_str_array_p
 * @since_tizen		2.3
 * @description		Gets a string array from 'key' key
 */
int utc_ApplicationFW_bundle_get_str_array_p(void)
{
    int r = 0;

    int array_len = 0;
    const char *str_array[] = { "aaa", "bbb", "ccc" };
    const char **out_str_array = NULL;

    assert_neq(b, NULL);

    r = bundle_add_str_array(b, "key", str_array, 3);
    assert_eq(r, BUNDLE_ERROR_NONE);

    out_str_array = bundle_get_str_array(b, "key", &array_len);
    assert(out_str_array);
    assert_eq(array_len, 3);

    assert_eq(get_last_result(), BUNDLE_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_get_str_array_n
 * @since_tizen		2.3
 * @description		Gets a string array from invalid parameters
 */
int utc_ApplicationFW_bundle_get_str_array_n(void)
{
    const char **str_array = bundle_get_str_array(NULL,NULL, 0);
    assert_eq(str_array, NULL);

    assert_eq(get_last_result(),BUNDLE_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_get_str_array_n2
 * @since_tizen		2.3
 * @description		Gets a string array from invalid key
 */
int utc_ApplicationFW_bundle_get_str_array_n2(void)
{
    assert_neq(b, NULL);

    const char **str_array = bundle_get_str_array(b, NULL, 0);
    assert_eq(str_array, NULL);

    assert_eq(get_last_result(),BUNDLE_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_get_str_array_n3
 * @since_tizen		2.3
 * @description		Gets a string array from not available key
 */
int utc_ApplicationFW_bundle_get_str_array_n3(void)
{
    int len = 0;

    assert_neq(b, NULL);

    const char **str_array = bundle_get_str_array(b, "somekey", &len);
    assert_eq(str_array, NULL);
    assert_eq(len, 0);

    assert_eq(get_last_result(),BUNDLE_ERROR_KEY_NOT_AVAILABLE);
    return 0;
}
