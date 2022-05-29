/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <bundle.h>

#include "assert.h"

static bundle *b = NULL;

void utc_ApplicationFW_bundle_add_byte_array_startup(void)
{
	b = bundle_create();
}

void utc_ApplicationFW_bundle_add_byte_array_cleanup(void)
{
	bundle_free(b);
}

/**
 * @testcase            utc_ApplicationFW_bundle_add_byte_array_p
 * @since_tizen         5.5
 * @description         Adds an 'array of byte sequences' type key-value pair into a bundle.
 * @scenario            Calls bundle_add_byte_array() and then checks the result.
 */
int utc_ApplicationFW_bundle_add_byte_array_p(void)
{
	int ret;

	assert_neq(b, NULL);

	ret = bundle_add_byte_array(b, "byte_array", 4);
	assert_eq(ret, BUNDLE_ERROR_NONE);

	ret = bundle_get_type(b, "byte_array");
	assert_eq(ret, BUNDLE_TYPE_BYTE_ARRAY);

	return 0;
}


/**
 * @testcase            utc_ApplicationFW_bundle_add_byte_array_n1
 * @since_tizen         5.5
 * @description         Adds an 'array of byte sequences' type key-value pair into a bundle.
 * @scenario            Calls bundle_add_byte_array() twice.
 *                      And then checks the result.
 *                      The result value should be BUNDLE_ERROR_KEY_EXISTS.
 */
int utc_ApplicationFW_bundle_add_byte_array_n1(void)
{
	int ret;

	assert_neq(b, NULL);

	ret = bundle_add_byte_array(b, "byte_array", 4);
	assert_eq(ret, BUNDLE_ERROR_NONE);

	ret = bundle_add_byte_array(b, "byte_array", 4);
	assert_eq(ret, BUNDLE_ERROR_KEY_EXISTS);

	return 0;
}

/**
 * @testcase            utc_ApplicationFW_bundle_add_byte_array_n2
 * @since_tizen         5.5
 * @description         Adds an 'array of byte sequences' type key-value pair into a bundle.
 * @scenario            Calls bundle_add_byte_array() with invalid parameter.
 *                      The result value should be BUNDLE_ERROR_INVALID_PARAMETER.
 */
int utc_ApplicationFW_bundle_add_byte_array_n2(void)
{
	int ret;

	ret = bundle_add_byte(NULL, NULL, NULL, 0);
	assert_eq(ret, BUNDLE_ERROR_INVALID_PARAMETER);

	return 0;
}
