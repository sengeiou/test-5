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

//& set: BundleKeyvalGetArrayVal

static int type_is_array_ret;
static int get_array_val_err;
static bool val_not_empty;
static bool len_not_empty;
static bool size_not_empty;
static bool kv_not_empty;

static void sample_cb(const char *key, const int type, const bundle_keyval_t *kv, void *user_data) {

	void **array_val = NULL;
	unsigned int array_len = 0;
	size_t *array_elem_size = NULL;

	if(kv != NULL) kv_not_empty = true;

	type_is_array_ret = bundle_keyval_type_is_array((bundle_keyval_t *)kv);
	get_array_val_err = bundle_keyval_get_array_val((bundle_keyval_t *)kv, &array_val, &array_len, &array_elem_size);

	if(array_val != NULL) val_not_empty = true;
	if(array_len > 0) len_not_empty = true;
	if(array_elem_size != NULL) size_not_empty = true;

	return;
 }

/**
 * @testcase		utc_bundle_keyval_get_array_val_p
 * @since_tizen		2.3
 * @description		Gets the value array, length of the array, and size of each array item
 */
int utc_bundle_keyval_get_array_val_p(void)
{
	int ret;
	bundle *b = bundle_create(); // Create new bundle object
	const char *s_arr[] = {"abc", "bcd", "cde"};

	ret = bundle_add_str_array(b, "k3", s_arr, 3); // add a key-val pair
	assert_eq(ret, BUNDLE_ERROR_NONE);

	type_is_array_ret = 0;
	get_array_val_err = 0;
	val_not_empty = false;
	len_not_empty = false;
	size_not_empty = false;
	kv_not_empty = false;

	bundle_foreach(b, sample_cb, NULL);    // iterate sample_cb for each key/val

	assert_eq(type_is_array_ret, 1);
	assert_eq(get_array_val_err, BUNDLE_ERROR_NONE);
	assert(kv_not_empty);
	assert(val_not_empty);
	assert(len_not_empty);
	assert(size_not_empty);

	bundle_del(b, "k3"); // Fix memory leak
	bundle_free(b);  // Fix memory leak

	return 0;
 }


/**
 * @testcase		utc_bundle_keyval_get_array_val_n
 * @since_tizen		2.3
 * @description		Gets the arrays with invalid parameters
 */
int utc_bundle_keyval_get_array_val_n(void)
{
	int ret = 0;

	ret = bundle_keyval_get_array_val(NULL, NULL, NULL, NULL);
	assert_eq(ret, BUNDLE_ERROR_INVALID_PARAMETER);

	return 0;
}
