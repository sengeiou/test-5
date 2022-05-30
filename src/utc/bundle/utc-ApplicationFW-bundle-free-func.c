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

//& set: BundleFreeFunc

/**
 * @testcase		utc_ApplicationFW_bundle_free_p
 * @since_tizen		2.3
 * @description		Frees the bundle object
 */
int utc_ApplicationFW_bundle_free_p(void)
{
    int r;

    bundle *b = NULL;
    b = bundle_create();
    assert_neq(b, NULL);

    r = bundle_free(b);
    assert_eq(r, BUNDLE_ERROR_NONE);

    return 0;
}


/**
 * @testcase		utc_ApplicationFW_bundle_free_n
 * @since_tizen		2.3
 * @description		Frees the invalid bundle object
 */
int utc_ApplicationFW_bundle_free_n(void)
{
    int r = 0;

    r = bundle_free(NULL);
    assert_eq(r, BUNDLE_ERROR_INVALID_PARAMETER);
    return 0;
}
