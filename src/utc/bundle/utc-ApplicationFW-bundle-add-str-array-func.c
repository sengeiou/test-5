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

//& set: BundleAddStrArrayFunc

static bundle *b = NULL;

/**
 * @function		utc_ApplicationFW_bundle_add_str_array_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_ApplicationFW_bundle_add_str_array_startup(void)
{
    b = bundle_create();
}

/**
 * @function		utc_ApplicationFW_bundle_add_str_array_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_ApplicationFW_bundle_add_str_array_cleanup(void)
{
    bundle_free(b);
    b = NULL;
}

/**
 * @testcase		utc_ApplicationFW_bundle_add_str_array_p
 * @since_tizen		2.3
 * @description		Add a strings array type and get the type
 */
int utc_ApplicationFW_bundle_add_str_array_p(void)
{
    int r = 0;
    int array_len = 3;
    assert_neq(b, NULL);
    const char *str_array[] = { "aaa", "bbb", "ccc" };

    r = bundle_add_str_array(b, "key", str_array, array_len);
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_get_type(b, "key");
    assert_eq(r, BUNDLE_TYPE_STR_ARRAY);

    return 0;
}

// key already exists
/**
 * @testcase		utc_ApplicationFW_bundle_add_str_array_n
 * @since_tizen		2.3
 * @description		Add a strings array type key-value pair and add the same pair
 */
int utc_ApplicationFW_bundle_add_str_array_n(void)
{
    int r = 0;
    int array_len = 3;
    const char *str_array[] = { "aaa", "bbb", "ccc" };
    assert_neq(b, NULL);

    r = bundle_add_str_array(b, "key", str_array, array_len);
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_add_str_array(b, "key", str_array, array_len);
    assert_eq(r, BUNDLE_ERROR_KEY_EXISTS);

    return 0;
}

// NULL key pointer
/**
 * @testcase		utc_ApplicationFW_bundle_add_str_array_n2
 * @since_tizen		2.3
 * @description		Add a strings array type key-value with invalid key-value pair
 */
int utc_ApplicationFW_bundle_add_str_array_n2(void)
{
    int r = 0;
    assert_neq(b, NULL);

    r = bundle_add_str_array(b, NULL, NULL, 0);
    assert_eq(r, BUNDLE_ERROR_INVALID_PARAMETER);

    return 0;
}

// all pointers NULL
/**
 * @testcase		utc_ApplicationFW_bundle_add_str_array_n3
 * @since_tizen		2.3
 * @description		Add a strings array type key-value with invalid handle and key-value pair
 */
int utc_ApplicationFW_bundle_add_str_array_n3(void)
{
    int r = 0;
    assert_neq(b, NULL);

    r = bundle_add_str_array(NULL, NULL, NULL, 0);
    assert_eq(r, BUNDLE_ERROR_INVALID_PARAMETER);

    return 0;
}
