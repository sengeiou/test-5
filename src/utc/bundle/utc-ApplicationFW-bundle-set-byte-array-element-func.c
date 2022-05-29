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

void utc_ApplicationFW_bundle_set_byte_array_element_startup(void)
{
	b = bundle_create();
	bundle_add_byte_array(b, "byte_array", 3);
}

void utc_ApplicationFW_bundle_set_byte_array_element_cleanup(void)
{
	bundle_free(b);
}

/**
 * @testcase            utc_ApplicationFW_bundle_set_byte_array_element_p
 * @since_tizen         5.5
 * @description         Sets an element of an array of byte sequences.
 * @scenario            Calls bundle_set_byte_array_element() and then checks the result.
 */
int utc_ApplicationFW_bundle_set_byte_array_element_p(void)
{
	int ret;

	assert_neq(b, NULL);

	ret = bundle_set_byte_array_element(b, "byte_array", 0, "aaa\0", 4);
	assert_eq(ret, BUNDLE_ERROR_NONE);

	ret = bundle_set_byte_array_element(b, "byte_array", 1, "bbb\0", 4);
	assert_eq(ret, BUNDLE_ERROR_NONE);

	ret = bundle_set_byte_array_element(b, "byte_array", 2, "ccc\0", 4);
	assert_eq(ret, BUNDLE_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_ApplicationFW_bundle_set_byte_array_element_n
 * @since_tizen         5.5
 * @description         Sets an element of an array of byte sequences.
 * @scenario            Calls bundle_set_byte_array_element() and then checks the result.
 */
int utc_ApplicationFW_bundle_set_byte_array_element_n(void)
{
	int ret;

	assert_neq(b, NULL);

	ret = bundle_set_byte_array_element(NULL, NULL, -1, NULL, 0);
	assert_eq(ret, BUNDLE_ERROR_INVALID_PARAMETER);

	return 0;
}
