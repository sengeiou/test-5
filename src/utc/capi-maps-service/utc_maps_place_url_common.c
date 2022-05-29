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
#include <maps_place_url.h>
#include <maps_service.h>
#include "utc_maps_utils.h"

static int ret = 0;
static maps_place_url_h __pUrl = NULL;
static bool is_maps_supported = false;

/**
 * @function		utc_maps_place_url_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_place_url_startup(void)
{
	is_maps_supported = _is_maps_feature_supported();
}

/**
 * @function		utc_maps_place_url_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_place_url_cleanup(void)
{
}

/**
 * @testcase		utc_maps_place_url_destroy_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_url_destroy()
 */
int utc_maps_place_url_destroy_n(void)
{
	ret = maps_place_url_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_url_clone_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_url_clone()
 */
int utc_maps_place_url_clone_n(void)
{
	maps_place_url_h clone_place_url = NULL;

	ret = maps_place_url_clone(NULL, &clone_place_url);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_url_clone(__pUrl, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_url_get_path_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_url_get_path()
 */
int utc_maps_place_url_get_path_n(void)
{
	char *path = NULL;

	ret = maps_place_url_get_path(NULL, &path);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_url_get_path(__pUrl, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_url_get_description_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_url_get_description()
 */
int utc_maps_place_url_get_description_n(void)
{
	char *description = NULL;

	ret = maps_place_url_get_description(NULL, &description);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_url_get_description(__pUrl, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}
