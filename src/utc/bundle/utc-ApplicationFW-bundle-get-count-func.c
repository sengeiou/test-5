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

//& set: BundleGetCountFunc

/**
 * @testcase		utc_ApplicationFW_bundle_get_count_p
 * @since_tizen		2.3
 * @description		Gets the number of bundle items
 */
int utc_ApplicationFW_bundle_get_count_p(void)
{
    int r;
    bundle *b = bundle_create();
    assert_neq(b, NULL);

    r = bundle_add_str(b, "a", "123");
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_get_count(b);
    assert_eq(r, 1);

    r = bundle_add_str(b, "b", "456");
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_get_count(b);
    assert_eq(r, 2);

    r = bundle_del(b, "b");
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_get_count(b);
    assert_eq(r, 1);

    bundle_free(b);
    return 0;
}


/**
 * @testcase		utc_ApplicationFW_bundle_get_count_n
 * @since_tizen		2.3
 * @description		Gets the number of bundle items with NULL
 */
int utc_ApplicationFW_bundle_get_count_n(void)
{
    int r;
    r = bundle_get_count(NULL);
    assert_eq(r, BUNDLE_ERROR_NONE);
    return 0;
}
