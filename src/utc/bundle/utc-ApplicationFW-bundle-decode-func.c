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
#include <stdlib.h>

//& set: BundleDecodeFunc

/**
 * @testcase		utc_ApplicationFW_bundle_decode_p1
 * @since_tizen		2.3
 * @description		Deserializes bundle_raw as a string type encoded bundle
 */
int utc_ApplicationFW_bundle_decode_p1(void)
{
    int r = 0;
    int len;
    bundle_raw *raw = NULL;
    char *val = NULL;

    bundle *b = bundle_create();
    assert(b);
    r = bundle_add_str(b, "a", "123");
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_encode(b, &raw, &len);
    assert_eq(r, BUNDLE_ERROR_NONE);
    assert_neq(raw, NULL);

    bundle *b_dec = bundle_decode(raw, len);
    assert(b_dec);

    bundle_get_str(b_dec, "a", &val);
    assert(!strcmp("123", val));

    bundle_free(b);
    bundle_free(b_dec);
    free(raw);
    return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_decode_p2
 * @since_tizen		2.3
 * @description		Deserializes bundle_raw as a strings array type encoded bundle
 */
int utc_ApplicationFW_bundle_decode_p2(void)
{
    int r = 0;
    int len;
    int array_len = 3;
    int array_len_dec = 0;
    bundle_raw *raw = NULL;
    const char *str_array[] = { "aaa", "bbb", "ccc" };
    const char **out_str_array = NULL;

    bundle *b = bundle_create();
    assert(b);

    r = bundle_add_str_array(b, "key", str_array, array_len);
    assert_eq(r, BUNDLE_ERROR_NONE);

    r = bundle_encode(b, &raw, &len);
    assert_eq(r, BUNDLE_ERROR_NONE);
    assert_neq(raw, NULL);

    bundle *b_dec = bundle_decode(raw, len);
    assert(b_dec);

    out_str_array = bundle_get_str_array(b_dec, "key", &array_len_dec);
    assert(out_str_array);
    assert_eq(array_len_dec, 3);
    assert(0 == strcmp("aaa", out_str_array[0]));

    bundle_free(b);
    bundle_free(b_dec);
    free(raw);

    return 0;
}


/**
 * @testcase		utc_ApplicationFW_bundle_decode_n
 * @since_tizen		2.3
 * @description		Deserializes bundle_raw with invalid bundle_raw
 */
int utc_ApplicationFW_bundle_decode_n(void)
{
    bundle* result = bundle_decode(NULL, 1);
    assert(!result);
    bundle_free(result);

    return 0;
}
