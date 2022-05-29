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

//& set: BundleEncodeFunc

/**
 * @testcase		utc_ApplicationFW_bundle_encode_p
 * @since_tizen		2.3
 * @description		Encode a bundle
 */
int utc_ApplicationFW_bundle_encode_p(void)
{
    int r = 0;
    int len = 0;

    bundle_raw *raw = NULL;
    bundle *b = bundle_create();
    assert_neq(b, NULL);

    r = bundle_add_str(b, "a", "123");
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_encode(b, &raw, &len);
    assert_eq(r, BUNDLE_ERROR_NONE);
    assert_neq(raw, NULL);
    assert(len > 0);

    bundle_free(b);
    free(raw);
    return 0;
}


/**
 * @testcase		utc_ApplicationFW_bundle_encode_n
 * @since_tizen		2.3
 * @description		Encode a bundle with invalid handle and bundle_raw
 */
int utc_ApplicationFW_bundle_encode_n(void)
{
    int r = 0;

    r = bundle_encode(NULL, NULL, NULL);
    assert_eq(r, BUNDLE_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_encode_n2
 * @since_tizen		2.3
 * @description		Encode a bundle with invalid bundle_raw
 */
int utc_ApplicationFW_bundle_encode_n2(void)
{
    int r = 0;

    bundle *b = bundle_create();
    assert_neq(b, NULL);

    r = bundle_add_str(b, "a", "123");
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_encode(b, NULL, NULL);
    assert_eq(r, BUNDLE_ERROR_INVALID_PARAMETER);

    bundle_free(b);
    return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_encode_n3
 * @since_tizen		2.3
 * @description		Encode a bundle with invalid length of bundle_raw
 * @description		
 */
int utc_ApplicationFW_bundle_encode_n3(void)
{
    int r = 0;

    bundle *b = bundle_create();
    bundle_raw *raw = NULL;
    assert_neq(b, NULL);

    r = bundle_add_str(b, "a", "123");
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_encode(b, &raw, NULL);
    assert_eq(r, BUNDLE_ERROR_INVALID_PARAMETER);

    bundle_free(b);
    return 0;
}
