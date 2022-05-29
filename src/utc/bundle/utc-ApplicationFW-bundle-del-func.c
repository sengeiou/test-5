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
//& set: BundleDelFunc

static bundle *b = NULL;

/**
 * @function		utc_ApplicationFW_bundle_del_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_ApplicationFW_bundle_del_startup(void)
{
    b = bundle_create();
}

/**
 * @function		utc_ApplicationFW_bundle_del_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_ApplicationFW_bundle_del_cleanup(void)
{
    bundle_free(b);
}

/**
 * @testcase		utc_ApplicationFW_bundle_del_p
 * @since_tizen		2.3
 * @description		Deletes a key-value object and get the object
 */
int utc_ApplicationFW_bundle_del_p(void)
{
    int r = 0;
    assert_neq(b, NULL);
    char *val = NULL;

    r = bundle_add_str(b, "a", "123");
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_del(b, "a");
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_get_str(b, "a", &val);
    assert_eq(r, BUNDLE_ERROR_KEY_NOT_AVAILABLE);

    return 0;
}


/**
 * @testcase		utc_ApplicationFW_bundle_del_n
 * @since_tizen		2.3
 * @description		Deletes a key-value object and try to delete the object again
 */
int utc_ApplicationFW_bundle_del_n(void)
{
    int r = 0;
    assert_neq(b, NULL);

    r = bundle_add_str(b, "a", "123");
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_del(b, "a");
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_del(b, "a");
    assert_eq(r, BUNDLE_ERROR_KEY_NOT_AVAILABLE);

    return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_del_n2
 * @since_tizen		2.3
 * @description		Deletes a key-value object with invalid object
 */
int utc_ApplicationFW_bundle_del_n2(void)
{
    int r = 0;
    assert_neq(b, NULL);

    r = bundle_del(b, NULL);
    assert_eq(r, BUNDLE_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_del_n3
 * @since_tizen		2.3
 * @description		Deletes a key-value object with invalid handle
 */
int utc_ApplicationFW_bundle_del_n3(void)
{
    int r = 0;
    assert_neq(b, NULL);

    r = bundle_del(NULL, "a");
    assert_eq(r, BUNDLE_ERROR_INVALID_PARAMETER);

    return 0;
}
