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

//& set: BundleKeyval

static int _correct_array_type = 0;
static int _keyval_type_array = 0;

static void _foreach_cb_1(const char *key, const int type, const bundle_keyval_t *kv, void *data)
{
    int r = 0;

    r = bundle_keyval_get_type( (bundle_keyval_t *) kv);
    if(r == BUNDLE_TYPE_STR_ARRAY) {
        _correct_array_type = 1;
    }
}

static void _foreach_cb_2(const char *key, const int type, const bundle_keyval_t *kv, void *data)
{
    _keyval_type_array = bundle_keyval_type_is_array((bundle_keyval_t *)kv);
}

/**
 * @testcase		utc_ApplicationFW_bundle_keyval_get_type_p
 * @since_tizen		2.3
 * @description		Gets the type of key-value pair
 */
int utc_ApplicationFW_bundle_keyval_get_type_p(void)
{
    int r = 0;
    const char *str_array[] = { "aaa", "bbb", "ccc" };

    bundle *b = bundle_create();
    assert(b);

    r = bundle_add_str_array(b, "key", str_array, 3);
    assert_eq(r, BUNDLE_ERROR_NONE);

    bundle_foreach(b, _foreach_cb_1, NULL);
    assert(_correct_array_type);

    bundle_free(b);
    return 0;
}


/**
 * @testcase		utc_ApplicationFW_bundle_keyval_get_type_n
 * @since_tizen		2.3
 * @description		Gets the type of key-value pair with invalid parameter
 */
int utc_ApplicationFW_bundle_keyval_get_type_n(void)
{
    int r = 0;

    r = bundle_keyval_get_type(NULL);
    assert_eq(r, -1);

    return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_keyval_type_is_array_p
 * @since_tizen		2.3
 * @description		Gets the type of key-value pair and check wheter the type is array
 */
int utc_ApplicationFW_bundle_keyval_type_is_array_p(void)
{
    int r = 0;
    const char *str_array[] = { "aaa", "bbb", "ccc" };

    bundle *b = bundle_create();
    assert(b);

    r = bundle_add_str_array(b, "key", str_array, 3);
    assert_eq(r, BUNDLE_ERROR_NONE);

    bundle_foreach(b, _foreach_cb_2, NULL);
    assert(_keyval_type_array);

    bundle_free(b);
    return 0;
}


/**
 * @testcase		utc_ApplicationFW_bundle_keyval_type_is_array_n
 * @since_tizen		2.3
 * @description		Determines whether the type of a key-value pair is array with invalid parameter
 */
int utc_ApplicationFW_bundle_keyval_type_is_array_n(void)
{
    int r = 0;

    r = bundle_keyval_type_is_array(NULL);
    assert_neq(r, 0);

    return 0;
}
