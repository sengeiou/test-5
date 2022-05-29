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
#include <maps_place_link_object.h>
#include <maps_service.h>
#include "utc_maps_utils.h"

static int ret = 0;
static maps_place_link_object_h __pLinkObject = NULL;
static bool is_maps_supported = false;

/**
 * @function		utc_maps_place_link_object_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_place_link_object_startup(void)
{
	is_maps_supported = _is_maps_feature_supported();
}

/**
 * @function		utc_maps_place_link_object_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_place_link_object_cleanup(void)
{
}

/**
 * @testcase		utc_maps_place_link_object_destroy_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_link_object_destroy()
 */
int utc_maps_place_link_object_destroy_n(void)
{
	ret = maps_place_link_object_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
	return 0;
}

/**
 * @testcase		utc_maps_place_link_object_clone_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_link_object_clone()
 */
int utc_maps_place_link_object_clone_n(void)
{
	maps_place_link_object_h clone_place_link_object = NULL;

	ret = maps_place_link_object_clone(NULL, &clone_place_link_object);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_link_object_clone(__pLinkObject, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_link_object_get_id_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_link_object_get_id()
 */
int utc_maps_place_link_object_get_id_n(void)
{
	char *id = NULL;

	ret = maps_place_link_object_get_id(NULL, &id);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_link_object_get_id(__pLinkObject, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_link_object_get_name_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_link_object_get_name()
 */
int utc_maps_place_link_object_get_name_n(void)
{
	char *name = NULL;

	ret = maps_place_link_object_get_name(NULL, &name);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_link_object_get_name(__pLinkObject, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_link_object_get_type_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_link_object_get_type()
 */
int utc_maps_place_link_object_get_type_n(void)
{
	char *type = NULL;

	ret = maps_place_link_object_get_type(NULL, &type);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_link_object_get_type(__pLinkObject, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_link_object_get_string_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_link_object_get_string()
 */
int utc_maps_place_link_object_get_string_n(void)
{
	char *string = NULL;

	ret = maps_place_link_object_get_string(NULL, &string);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_link_object_get_string(__pLinkObject, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}
