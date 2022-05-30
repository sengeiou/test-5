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
//& set: BundleDupFunc

/**
 * @testcase		utc_ApplicationFW_bundle_dup_p
 * @since_tizen		2.3
 * @description		Duplicates a bundle object and compare it with original object
 */
int utc_ApplicationFW_bundle_dup_p(void)
{
	bundle *b = NULL;
	bundle *b_dup = NULL;
	int ret = 0;
	char *val = NULL;

	b = bundle_create();
	assert_neq(b, NULL);

	ret = bundle_add_str(b, "aa", "bb");
	assert_eq(ret, BUNDLE_ERROR_NONE);

	b_dup = bundle_dup(b);
	assert_neq(b_dup, NULL);

	ret = bundle_get_str(b_dup, "aa", &val);
	assert_eq(ret, BUNDLE_ERROR_NONE);

	assert(!strcmp(val, "bb"));

	bundle_free(b);
	bundle_free(b_dup);

	return 0;
}


/**
 * @testcase		utc_ApplicationFW_bundle_dup_n
 * @since_tizen		2.3
 * @description		Duplicates a bundle with invalid object
 */
int utc_ApplicationFW_bundle_dup_n(void)
{
	bundle *b = NULL;

	b = bundle_dup(NULL);
	assert_eq(b, NULL);

	bundle_free(b);
	return 0;
}
