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

//& set: BundleKeyvalGetBasicVal
static int ret_error;
static bool basic_val_notempty;
static bool basic_size_notempty;

static void sample_cb(const char *key, const int type, const bundle_keyval_t *kv, void *user_data)
{

	void *basic_val = NULL;
	size_t basic_size = 0;

	ret_error = bundle_keyval_get_basic_val( (bundle_keyval_t *) kv, &basic_val, &basic_size);

	if(basic_val!=NULL)basic_val_notempty=true;
	if(basic_size>0)basic_size_notempty=true;

	return;
 }

/**
 * @testcase		utc_bundle_keyval_get_basic_val_p
 * @since_tizen		2.3
 * @description		Gets the value and size of the value from a key-value pair of basic type
 */
int utc_bundle_keyval_get_basic_val_p(void)
{
	int ret;
	bundle *b = bundle_create(); // Create new bundle object

	ret = bundle_add_str(b, "k1", "v1");
	assert_eq(ret, BUNDLE_ERROR_NONE);

	ret_error=0;
	basic_val_notempty=false;
	basic_size_notempty=false;
	bundle_foreach(b, sample_cb, NULL);    // iterate sample_cb for each key/val
	
	bundle_del(b, "k1"); // Fix memory leak
	bundle_free(b); // Fix memory leak

	assert_eq(ret_error, BUNDLE_ERROR_NONE);
	assert_eq(basic_val_notempty,true);
	assert_eq(basic_size_notempty,true);
	return 0;
}


/**
 * @testcase		utc_bundle_keyval_get_basic_val_n
 * @since_tizen		2.3
 * @description		Gets the value and size of the value from a key-value pair of basic type with invalid parameters
 */
int utc_bundle_keyval_get_basic_val_n(void)
{
	int ret = 0;

	ret = bundle_keyval_get_basic_val(NULL, NULL, NULL);
	assert_eq(ret, BUNDLE_ERROR_INVALID_PARAMETER);

	return 0;
}
