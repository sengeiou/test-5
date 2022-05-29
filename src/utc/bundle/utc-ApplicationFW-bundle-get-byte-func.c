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

//& set: BundleGetByteFunc

/**
 * @testcase		utc_ApplicationFW_bundle_get_byte_p
 * @since_tizen		2.3
 * @description		Gets the byte value with 'b' key
 */
int utc_ApplicationFW_bundle_get_byte_p(void)
{
    int r;
    unsigned char data[4] = {0, 1, 2, 3};
    unsigned char* output = NULL;
    size_t size = 0;

    bundle *b = bundle_create();
    assert_neq(b, NULL);

    r = bundle_add_byte(b, "b", (void*)data, 4);
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_get_byte(b, "b", (void*)&output, &size);
    assert_eq(r, BUNDLE_ERROR_NONE);
    assert_eq(size, 4);
    int i;
    for(i = 0; i < 4; i++) {
        assert_eq(data[i], output[i]);
    }

    bundle_free(b);
    return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_get_byte_n
 * @since_tizen		2.3
 * @description		Gets the byte value with invalid parameters
 */
int utc_ApplicationFW_bundle_get_byte_n(void)
{
    int r;
    r = bundle_get_byte(NULL, NULL, NULL, NULL);
    assert_eq(r, BUNDLE_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_get_byte_n2
 * @since_tizen		2.3
 * @description		Gets the byte value with invalid key and value
 */
int utc_ApplicationFW_bundle_get_byte_n2(void)
{
    int r;
    bundle *b = bundle_create();
    assert_neq(b, NULL);

    r = bundle_get_byte(b, NULL, NULL, NULL);
    assert_eq(r, BUNDLE_ERROR_INVALID_PARAMETER);

    bundle_free(b);
    return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_get_byte_n3
 * @since_tizen		2.3
 * @description		Gets the byte value with not available key
 */
int utc_ApplicationFW_bundle_get_byte_n3(void)
{
    int r;
    unsigned char* output = NULL;
    size_t size = 0;
    bundle *b = bundle_create();
    assert_neq(b, NULL);

    r = bundle_get_byte(b, "somekey", (void*)&output, &size);
    assert_eq(r, BUNDLE_ERROR_KEY_NOT_AVAILABLE);

    bundle_free(b);
    return 0;
}
