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

//& set: BundleGetTypeFunc

/**
 * @testcase		utc_ApplicationFW_bundle_get_type_p
 * @since_tizen		2.3
 * @description		Gets the type of value with various keys
 */
int utc_ApplicationFW_bundle_get_type_p(void)
{
	int r;
	unsigned char data[4] = {0, 1, 2, 3};
	char *sa[] = {"aaa", "bbb", "ccc"};
	bundle *b = bundle_create();
	assert_neq(b, NULL);

	r = bundle_add_str(b, "a", "123");
	assert_eq(r, BUNDLE_ERROR_NONE);

	r = bundle_get_type(b, "a");
	assert_eq(r, BUNDLE_TYPE_STR);

	r = bundle_add_byte(b, "b", (const void *)data, 4);
	assert_eq(r, BUNDLE_ERROR_NONE);

	r = bundle_get_type(b, "b");
	assert_eq(r, BUNDLE_TYPE_BYTE);

	r = bundle_add_str_array(b, "c", (const char **)sa, 3);
	assert_eq(r, BUNDLE_ERROR_NONE);

	r = bundle_get_type(b, "c");
	assert_eq(r, BUNDLE_TYPE_STR_ARRAY);

	bundle_free(b);
	return 0;
}

/**
 * @testcase		utc_ApplicationFW_bundle_get_type_n
 * @since_tizen		2.3
 * @description		Gets the type of value with invalid parameters
 */
int utc_ApplicationFW_bundle_get_type_n(void)
{
	int r;
	r = bundle_get_type(NULL, NULL);
	assert_lt(r, 0);

	return 0;
}
