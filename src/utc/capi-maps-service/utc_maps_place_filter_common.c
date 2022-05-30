/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string.h>
#include "assert.h"
#include <maps_error.h>
#include <maps_place_filter.h>
#include <maps_service.h>
#include "utc_maps_utils.h"

static int ret = 0;
static maps_place_filter_h __pFilter = NULL;
static bool is_maps_supported = false;

/**
 * @function		utc_maps_place_filter_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_place_filter_startup(void)
{
	is_maps_supported = _is_maps_feature_supported();

	ret = 0;
	__pFilter = NULL;
	maps_place_filter_create(&__pFilter);
}

/**
 * @function		utc_maps_place_filter_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_place_filter_cleanup(void)
{
	maps_place_filter_destroy(__pFilter);
}

/**
 * @testcase		utc_maps_place_filter_create_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_filter_create()
 */
int utc_maps_place_filter_create_p(void)
{
	maps_place_filter_h filter = NULL;

	ret = maps_place_filter_create(&filter);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert(filter);

	ret = maps_place_filter_destroy(filter);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_filter_create_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_filter_create()
 */
int utc_maps_place_filter_create_n(void)
{
	ret = maps_place_filter_create(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_filter_destroy_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_filter_destroy()
 */
int utc_maps_place_filter_destroy_p(void)
{
	/* tested in utc_maps_place_filter_create_p */
	return 0;
}

/**
 * @testcase		utc_maps_place_filter_destroy_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_filter_destroy()
 */
int utc_maps_place_filter_destroy_n(void)
{
	ret = maps_place_filter_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_filter_clone_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_filter_clone()
 */
int utc_maps_place_filter_clone_p(void)
{
	maps_place_filter_h clone_place_filter = NULL;

	ret = maps_place_filter_clone(__pFilter, &clone_place_filter);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert(clone_place_filter);
		
	ret = maps_place_filter_destroy(clone_place_filter);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_filter_clone_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_filter_clone()
 */
int utc_maps_place_filter_clone_n(void)
{
	maps_place_filter_h clone_place_filter = NULL;

	ret = maps_place_filter_clone(NULL, &clone_place_filter);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_clone(__pFilter, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_filter_get_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_filter_get()
 */
int utc_maps_place_filter_get_p(void)
{
	char *test = NULL;

	ret = maps_place_filter_set(__pFilter, "key", "value");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_get(__pFilter, "key", &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert_eq(strcmp(test, "value"), 0);

		free(test);
	}
	return 0;
}

/**
 * @testcase		utc_maps_place_filter_get_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_filter_get()
 */
int utc_maps_place_filter_get_n(void)
{
	char *test = NULL;

	ret = maps_place_filter_set(__pFilter, "key", "value");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_get(NULL, "key", &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_get(__pFilter, NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_get(__pFilter, "key", NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_filter_get_keyword_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_filter_get_keyword()
 */
int utc_maps_place_filter_get_keyword_p(void)
{
	char *test = NULL;

	ret = maps_place_filter_set_keyword(__pFilter, "keyword");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_get_keyword(__pFilter, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert(test);
		assert_eq(strcmp(test, "keyword"), 0);

		free(test);
	}
	return 0;
}

/**
 * @testcase		utc_maps_place_filter_get_keyword_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_filter_get_keyword()
 */
int utc_maps_place_filter_get_keyword_n(void)
{
	char *test = NULL;

	ret = maps_place_filter_set_keyword(__pFilter, "keyword");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_get_keyword(NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
	assert(!test);

	ret = maps_place_filter_get_keyword(__pFilter, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_filter_get_category_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_filter_get_category()
 */
int utc_maps_place_filter_get_category_p(void)
{
	maps_place_category_h category = NULL;
	maps_place_category_h test = NULL;

	ret = maps_place_category_create(&category);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_set_category(__pFilter, category);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_get_category(__pFilter, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_category_destroy(category);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_category_destroy(test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_filter_get_category_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_filter_get_category()
 */
int utc_maps_place_filter_get_category_n(void)
{
	maps_place_category_h test = NULL;

	ret = maps_place_filter_get_category(NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_get_category(__pFilter, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

static bool __utc_maps_place_filter_properties_cb(int index, int total, char *key, void *value, void *user_data)
{
	free(key);
	free(value);
	return true;
}

/**
 * @testcase		utc_maps_place_filter_foreach_property_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_filter_foreach_property()
 */
int utc_maps_place_filter_foreach_property_p(void)
{
	ret = maps_place_filter_set(__pFilter, "key", "value");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_foreach_property(__pFilter, __utc_maps_place_filter_properties_cb, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_filter_foreach_property_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_filter_foreach_property()
 */
int utc_maps_place_filter_foreach_property_n(void)
{
	ret = maps_place_filter_set(__pFilter, "key", "value");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_foreach_property(NULL, __utc_maps_place_filter_properties_cb, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_foreach_property(__pFilter, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_filter_get_place_name_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_filter_get_place_name()
 */
int utc_maps_place_filter_get_place_name_p(void)
{
	char *test = NULL;

	ret = maps_place_filter_set_place_name(__pFilter, "place_name");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_get_place_name(__pFilter, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert_eq(strcmp(test, "place_name"), 0);

		free(test);
	}
	return 0;
}

/**
 * @testcase		utc_maps_place_filter_get_place_name_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_filter_get_place_name()
 */
int utc_maps_place_filter_get_place_name_n(void)
{
	char *test = NULL;

	ret = maps_place_filter_get_place_name(NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_get_place_name(__pFilter, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_filter_set_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_filter_set()
 */
int utc_maps_place_filter_set_p(void)
{
	/* tested in utc_maps_place_filter_get_p */
	return 0;
}

/**
 * @testcase		utc_maps_place_filter_set_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_filter_set()
 */
int utc_maps_place_filter_set_n(void)
{
	ret = maps_place_filter_set(NULL, "key", "value");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_set(__pFilter, NULL, "value");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_set(__pFilter, "key", NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_set(NULL, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_filter_set_category_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_filter_set_category()
 */
int utc_maps_place_filter_set_category_p(void)
{
	/* tested in utc_maps_place_filter_get_category_p */
	return 0;
}

/**
 * @testcase		utc_maps_place_filter_set_category_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_filter_set_category()
 */
int utc_maps_place_filter_set_category_n(void)
{
	maps_place_category_h category = NULL;

	ret = maps_place_filter_set_category(NULL, category);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_set_category(__pFilter, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_filter_set_keyword_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_filter_set_keyword()
 */
int utc_maps_place_filter_set_keyword_p(void)
{
	/* tested in utc_maps_place_filter_get_keyword_p */
	return 0;
}

/**
 * @testcase		utc_maps_place_filter_set_keyword_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_filter_set_keyword()
 */
int utc_maps_place_filter_set_keyword_n(void)
{
	ret = maps_place_filter_set_keyword(NULL, "keyword");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_set_keyword(__pFilter, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_filter_set_place_name_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_filter_set_place_name()
 */
int utc_maps_place_filter_set_place_name_p(void)
{
	/* tested in utc_maps_place_filter_get_place_name_p */
	return 0;
}

/**
 * @testcase		utc_maps_place_filter_set_place_name_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_filter_set_place_name()
 */
int utc_maps_place_filter_set_place_name_n(void)
{
	ret = maps_place_filter_set_place_name(NULL,"place_name");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_set_place_name(__pFilter, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_filter_set_place_address_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_filter_set_place_address()
 */
int utc_maps_place_filter_set_place_address_p(void)
{
	/* tested in utc_maps_place_filter_get_place_address_p */
	return 0;
}

/**
 * @testcase		utc_maps_place_filter_set_place_address_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_filter_set_place_address()
 */
int utc_maps_place_filter_set_place_address_n(void)
{
	ret = maps_place_filter_set_place_address(NULL,"restaurant");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_set_place_address(__pFilter, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_filter_get_place_address_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_filter_get_place_address()
 */
int utc_maps_place_filter_get_place_address_p(void)
{
	char *test = NULL;

	ret = maps_place_filter_set_place_address(__pFilter, "restaurant");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_get_place_address(__pFilter, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert_eq(strcmp(test, "restaurant"), 0);

		free(test);
	}
	return 0;
}

/**
 * @testcase		utc_maps_place_filter_get_place_address_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_filter_get_place_address()
 */
int utc_maps_place_filter_get_place_address_n(void)
{
	char *test = NULL;

	ret = maps_place_filter_get_place_address(NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_filter_get_place_address(__pFilter, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

