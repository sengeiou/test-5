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
#include <unistd.h>
#include <glib.h>
#include <maps_error.h>
#include <maps_place_category.h>
#include <maps_service.h>
#include "utc_maps_utils.h"


static int ret = 0;
static maps_place_category_h __pCategory = NULL;
static bool is_maps_supported = false;

/**
 * @function		utc_maps_place_category_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_place_category_startup(void)
{
	is_maps_supported = _is_maps_feature_supported();

	ret = 0;
	__pCategory = NULL;
	maps_place_category_create(&__pCategory);
}

/**
 * @function		utc_maps_place_category_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_place_category_cleanup(void)
{
	maps_place_category_destroy(__pCategory);
}

/**
 * @testcase		utc_maps_place_category_create_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_category_create()
 */
int utc_maps_place_category_create_p(void)
{
	maps_place_category_h category = NULL;

	ret = maps_place_category_create(&category);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert(category);

	ret = maps_place_category_destroy(category);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_category_create_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_category_create()
 */
int utc_maps_place_category_create_n(void)
{
	ret = maps_place_category_create(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_category_destroy_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_category_destroy()
 */
int utc_maps_place_category_destroy_p(void)
{
	/* tested in utc_maps_place_category_create_p */
	return 0;
}

/**
 * @testcase		utc_maps_place_category_destroy_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_category_destroy()
 */
int utc_maps_place_category_destroy_n(void)
{
	ret = maps_place_category_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
	return 0;
}

/**
 * @testcase		utc_maps_place_category_clone_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_category_clone()
 */
int utc_maps_place_category_clone_p(void)
{
	maps_place_category_h clone_place_category = NULL;

	if (is_maps_supported) {
		maps_place_category_set_id(__pCategory, "test");
		ret = maps_place_category_set_name(__pCategory, "test");
		ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
		maps_place_category_set_url(__pCategory, "test");

		ret = maps_place_category_clone(__pCategory, &clone_place_category);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(clone_place_category);

		ret = maps_place_category_destroy(clone_place_category);
		assert_eq(ret, MAPS_ERROR_NONE);
	} else {
		ret = maps_place_category_clone(__pCategory, &clone_place_category);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_maps_place_category_clone_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_category_clone()
 */
int utc_maps_place_category_clone_n(void)
{
	maps_place_category_h clone_place_category = NULL;

	ret = maps_place_category_clone(NULL, &clone_place_category);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_category_clone(__pCategory, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_category_set_id_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_category_set_id()
 */
int utc_maps_place_category_set_id_p(void)
{
	/* tested in utc_maps_place_category_get_id_p */
	return 0;
}

/**
 * @testcase		utc_maps_place_category_set_id_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_category_set_id()
 */
int utc_maps_place_category_set_id_n(void)
{
	ret = maps_place_category_set_id(NULL, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_category_set_id(__pCategory, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_category_set_id(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_category_get_id_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_category_get_id()
 */
int utc_maps_place_category_get_id_p(void)
{
	char *id = NULL;

	ret = maps_place_category_set_id(__pCategory, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_category_get_id(__pCategory, &id);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert_eq(strcmp(id, "test"), 0);

		free(id);
	}
	return 0;
}

/**
 * @testcase		utc_maps_place_category_get_id_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_category_get_id()
 */
int utc_maps_place_category_get_id_n(void)
{
	char *id = NULL;

	ret = maps_place_category_get_id(NULL, &id);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_category_get_id(__pCategory, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_category_set_name_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_category_set_name()
 */
int utc_maps_place_category_set_name_p(void)
{
	/* tested in utc_maps_place_category_get_name_p */
	return 0;
}

/**
 * @testcase		utc_maps_place_category_set_name_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_category_set_name()
 */
int utc_maps_place_category_set_name_n(void)
{
	ret = maps_place_category_set_name(NULL, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_category_set_name(__pCategory, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_category_set_name(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_category_get_name_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_category_get_name()
 */
int utc_maps_place_category_get_name_p(void)
{
	char *name = NULL;

	ret = maps_place_category_set_name(__pCategory, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_category_get_name(__pCategory, &name);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert_eq(strcmp(name, "test"), 0);

		free(name);
	}
	return 0;
}

/**
 * @testcase		utc_maps_place_category_get_name_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_category_get_name()
 */
int utc_maps_place_category_get_name_n(void)
{
	char *name = NULL;

	ret = maps_place_category_get_name(NULL, &name);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_category_get_name(__pCategory, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_category_set_url_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_category_set_url()
 */
int utc_maps_place_category_set_url_p(void)
{
	/* tested in utc_maps_place_category_get_url_p */
	return 0;
}

/**
 * @testcase		utc_maps_place_category_set_url_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_category_set_url()
 */
int utc_maps_place_category_set_url_n(void)
{
	ret = maps_place_category_set_url(NULL, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_category_set_url(__pCategory, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_category_set_url(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_category_get_url_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_place_category_get_url()
 */
int utc_maps_place_category_get_url_p(void)
{
	char *url = NULL;

	ret = maps_place_category_set_url(__pCategory, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_category_get_url(__pCategory, &url);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert_eq(strcmp(url, "test"), 0);
		
		free(url);
	}
	return 0;
}

/**
 * @testcase		utc_maps_place_category_get_url_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_category_get_url()
 */
int utc_maps_place_category_get_url_n(void)
{
	char *url = NULL;

	ret = maps_place_category_get_url(NULL, &url);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_category_get_url(__pCategory, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}
