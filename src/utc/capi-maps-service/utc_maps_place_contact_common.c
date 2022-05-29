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
#include <maps_place_contact.h>
#include <maps_service.h>
#include "utc_maps_utils.h"

static int ret = 0;
static maps_place_contact_h __pContact = NULL;
static bool is_maps_supported = false;

/**
 * @function		utc_maps_place_contact_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_place_contact_startup(void)
{
	is_maps_supported = _is_maps_feature_supported();
}

/**
 * @function		utc_maps_place_contact_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_place_contact_cleanup(void)
{
}

/**
 * @testcase		utc_maps_place_contact_destroy_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_contact_destroy()
 */
int utc_maps_place_contact_destroy_n(void)
{
	ret = maps_place_contact_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_contact_clone_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_contact_clone()
 */
int utc_maps_place_contact_clone_n(void)
{
	maps_place_contact_h clone_place_contact = NULL;

	ret = maps_place_contact_clone(NULL, &clone_place_contact);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_contact_clone(__pContact, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_contact_get_label_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_contact_get_label()
 */
int utc_maps_place_contact_get_label_n(void)
{
	char *label = NULL;

	ret = maps_place_contact_get_label(NULL, &label);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_contact_get_label(__pContact, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_contact_get_type_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_contact_get_type()
 */
int utc_maps_place_contact_get_type_n(void)
{
	char *type = NULL;

	ret = maps_place_contact_get_type(NULL, &type);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_contact_get_type(__pContact, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_contact_get_value_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_contact_get_value()
 */
int utc_maps_place_contact_get_value_n(void)
{
	char *value = NULL;

	ret = maps_place_contact_get_value(NULL, &value);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_contact_get_value(__pContact, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}
