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

//& set: BundleGetStrFunc

/**
 * @testcase		utc_ApplicationFW_bundle_get_str_p
 * @since_tizen		2.3
 * @description		Gets the string value with 'key' key
 */
int utc_ApplicationFW_bundle_get_str_p(void)
{
    int r;
    char* output = NULL;
    bundle *b = bundle_create();
    assert_neq(b, NULL);

    r = bundle_add_str(b, "key", "123");
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_get_str(b, "key", &output);
    assert_eq(r, BUNDLE_ERROR_NONE);
    assert_neq(output, NULL);
    assert(!strcmp(output, "123"));

    bundle_free(b);
    return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_get_str_n
 * @since_tizen		2.3
 * @description		Gets the string value with invalid parameters
 */
int utc_ApplicationFW_bundle_get_str_n(void)
{
    int r;
    r = bundle_get_str(NULL, NULL, NULL);
    assert_eq(r, BUNDLE_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_get_str_n2
 * @since_tizen		2.3
 * @description		Gets the string value with invalid key
 */
int utc_ApplicationFW_bundle_get_str_n2(void)
{
    int r;
    bundle *b = bundle_create();
    assert_neq(b, NULL);

    r = bundle_get_str(b, NULL, NULL);
    assert_eq(r, BUNDLE_ERROR_INVALID_PARAMETER);

    bundle_free(b);
    return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_get_str_n3
 * @since_tizen		2.3
 * @description		Gets the string value with not available key
 */
int utc_ApplicationFW_bundle_get_str_n3(void)
{
    int r;
    char* output = NULL;
    bundle *b = bundle_create();
    assert_neq(b, NULL);

    r = bundle_get_str(b, "somekey", &output);
    assert_eq(r, BUNDLE_ERROR_KEY_NOT_AVAILABLE);

    bundle_free(b);
    return 0;
}
