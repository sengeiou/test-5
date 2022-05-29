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

//& set: BundleAddStrFunc

static bundle *b = NULL;

/**
 * @function		utc_ApplicationFW_bundle_add_str_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_ApplicationFW_bundle_add_str_startup(void)
{
    b = bundle_create();
}

/**
 * @function		utc_ApplicationFW_bundle_add_str_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_ApplicationFW_bundle_add_str_cleanup(void)
{
    bundle_free(b);
    b = NULL;
}

/**
 * @testcase		utc_ApplicationFW_bundle_add_str_p
 * @since_tizen		2.3
 * @description		Add a string type key-value pair and get the type
 */
int utc_ApplicationFW_bundle_add_str_p(void)
{
    int r = 0;
    char *key = "a";
    char *val = "123";

    assert_neq(b, NULL);

    r = bundle_add_str(b, key, val);
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_get_type(b, key);
    assert_eq(r, BUNDLE_TYPE_STR);

    return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_add_str_n
 * @since_tizen		2.3
 * @description		Add a string type key-value pair and add the same pair
 */
int utc_ApplicationFW_bundle_add_str_n(void)
{
    int r = 0;
    char *key = "key";
    char *val1 = "aaa";
    char *val2 = "bbb";

    r = bundle_add_str(b, key, val1);
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_add_str(b, key, val2);
    assert_eq(r, BUNDLE_ERROR_KEY_EXISTS);

    return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_add_str_n2
 * @since_tizen		2.3
 * @description		Add a string type key-value with invalid key
 */
int utc_ApplicationFW_bundle_add_str_n2(void)
{
    int r = 0;
    char *val = "aaa";

    r = bundle_add_str(b, NULL, val);
    assert_eq(r, BUNDLE_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_add_str_n3
 * @since_tizen		2.3
 * @description		Add a string type key-value with invalid value
 */
int utc_ApplicationFW_bundle_add_str_n3(void)
{
    int r = 0;
    char *key = "key";

    r = bundle_add_str(b, key, NULL);
    assert_eq(r, BUNDLE_ERROR_INVALID_PARAMETER);

    return 0;
}
