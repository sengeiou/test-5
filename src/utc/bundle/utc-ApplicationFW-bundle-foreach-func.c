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
#include <stdbool.h>
//& set: BundleForeachFunc

static int cb_counter;
static char *keys[2] = {"aa", "bb"};
static char *vals[2] = {"123", "456"};
static bool valid_key = true;
static bool valid_type = true;
static bool valid_kv = true;
static bool valid_val = true;

static void _foreach_cb(const char *key, const int type, const bundle_keyval_t *kv, void *data)
{
	void *basic_val = NULL;
	size_t basic_size = 0;

	if (key && keys[cb_counter] && !strcmp(key, keys[cb_counter]))
		valid_key = false;
	if (type != BUNDLE_TYPE_STR)
		valid_type = false;
	if (kv == NULL) {
		valid_kv = false;
	} else {
		bundle_keyval_get_basic_val((bundle_keyval_t *)kv, &basic_val, &basic_size);
		if (basic_val && vals[cb_counter] && strcmp(basic_val, vals[cb_counter]))
			valid_val = false;
	}

	cb_counter++;
}


/**
 * @testcase		utc_ApplicationFW_bundle_foreach_p
 * @since_tizen		2.3
 * @description		Iterates a callback function
 */
int utc_ApplicationFW_bundle_foreach_p(void)
{
	int r = 0;

	cb_counter = 0;
	bundle *b = bundle_create();
	assert_neq(b, NULL);

	r = bundle_add_str(b, "a", "123");
	assert_eq(r, BUNDLE_ERROR_NONE);
	r = bundle_add_str(b, "b", "456");
	assert_eq(r, BUNDLE_ERROR_NONE);

	bundle_foreach(b, _foreach_cb, NULL);
	assert_eq(cb_counter, 2);

	assert(valid_key);
	assert(valid_type);
	assert(valid_kv);
	assert(valid_val);

	bundle_free(b);
	return 0;
}


/**
 * @testcase		utc_ApplicationFW_bundle_foreach_n
 * @since_tizen		2.3
 * @description		Iterates a callback function with invalid parameters
 */
int utc_ApplicationFW_bundle_foreach_n(void)
{
	bundle_foreach(NULL, NULL, NULL);

	/* Function does not return any value so test PASS if there's no
	 * segmentation fault for NULL pointers */
	return 0;
}
