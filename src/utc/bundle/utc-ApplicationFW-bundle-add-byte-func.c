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

//& set: BundleAddByteFunc

static bundle *b = NULL;

/**
 * @function		utc_ApplicationFW_bundle_add_byte_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_ApplicationFW_bundle_add_byte_startup(void)
{
    b = bundle_create();
}

/**
 * @function		utc_ApplicationFW_bundle_add_byte_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_ApplicationFW_bundle_add_byte_cleanup(void)
{
    bundle_free(b);
    b = NULL;
}

/**
 * @testcase		utc_ApplicationFW_bundle_add_byte_p
 * @since_tizen		2.3
 * @description		Add a byte type key-value pair and get the type
 */
int utc_ApplicationFW_bundle_add_byte_p(void)
{
    int r = 0;
    unsigned char data[4] = {0, 1, 2, 3};

    assert_neq(b, NULL);

    r = bundle_add_byte(b, "b", data, 4);
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_get_type(b, "b");
    assert_eq(r, BUNDLE_TYPE_BYTE);

    return 0;
}


/**
 * @testcase		utc_ApplicationFW_bundle_add_byte_n
 * @since_tizen		2.3
 * @description		Add a byte type key-value and add the same pair
 */
int utc_ApplicationFW_bundle_add_byte_n(void)
{
    int r = 0;
    unsigned char data[4] = {0, 1, 2, 3};

    assert_neq(b, NULL);

    r = bundle_add_byte(b, "b", data, 4);
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_add_byte(b, "b", data, 4);
    assert_eq(r, BUNDLE_ERROR_KEY_EXISTS);

    return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_add_byte_n2
 * @since_tizen		2.3
 * @description		Add a byte type key-value with invalid key
 */
int utc_ApplicationFW_bundle_add_byte_n2(void)
{
    int r = 0;
    unsigned char data[4] = {0, 1, 2, 3};

    r = bundle_add_byte(b, NULL, data, 4);
    assert_eq(r, BUNDLE_ERROR_INVALID_PARAMETER);

    return 0;
}
