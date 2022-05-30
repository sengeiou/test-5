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
#include <glib.h>
#include <maps_error.h>
#include <maps_place.h>
#include <maps_service.h>
#include <unistd.h>
#include "utc_maps_utils.h"

static int ret = 0;
static maps_place_h __pPlace = NULL;
static bool category_available = false;
static bool service_enabled_place = false;
static bool attribute_available = false;
static bool contact_available = false;
static bool editorial_available = false;
static bool image_available = false;
static bool review_available = false;
static bool is_maps_supported = false;

/**
 * @function		utc_maps_place_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_place_startup(void)
{
	is_maps_supported = _is_maps_feature_supported();

	ret = 0;
	category_available = false;
	service_enabled_place = false;
	attribute_available = false;
	contact_available = false;
	editorial_available = false;
	image_available = false;
	review_available = false;
}

/**
 * @function		utc_maps_place_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_place_cleanup(void)
{
}

/**
 * @testcase		utc_maps_place_destroy_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_destroy()
 */
int utc_maps_place_destroy_n(void)
{
	ret = maps_place_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_clone_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_clone()
 */
int utc_maps_place_clone_n(void)
{
	maps_place_h clone = NULL;

	ret = maps_place_clone(NULL, &clone);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_clone(__pPlace, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_get_id_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_get_id()
 */
int utc_maps_place_get_id_n(void)
{
	char *id;

	ret = maps_place_get_id(NULL, &id);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_get_id(__pPlace, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_get_name_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_get_name()
 */
int utc_maps_place_get_name_n(void)
{
	char *name;

	ret = maps_place_get_name(NULL, &name);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_get_name(__pPlace, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_get_uri_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_get_uri()
 */
int utc_maps_place_get_uri_n(void)
{
	char *uri;

	ret = maps_place_get_uri(NULL, &uri);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_get_uri(__pPlace, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_get_location_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_get_location()
 */
int utc_maps_place_get_location_n(void)
{
	maps_coordinates_h coords = NULL;

	ret = maps_place_get_location(NULL, &coords);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_get_location(__pPlace, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_get_distance_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_get_distance()
 */
int utc_maps_place_get_distance_n(void)
{
	int test = 0;

	ret = maps_place_get_distance(NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_get_distance(__pPlace, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_get_address_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_get_address()
 */
int utc_maps_place_get_address_n(void)
{
	maps_address_h address = NULL;

	ret = maps_address_create(&address);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_get_address(NULL, &address);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_get_address(__pPlace, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_destroy(address);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_get_rating_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_get_rating()
 */
int utc_maps_place_get_rating_n(void)
{
	maps_place_rating_h rating = NULL;

	ret = maps_place_get_rating(NULL, &rating);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_get_rating(__pPlace, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

static bool __utc_maps_place_category_cb(int index, int total, maps_place_category_h category, void *user_data)
{
	category_available = true;
	service_enabled_place = true;

	maps_place_category_destroy(category);
	return true;
}

/**
 * @testcase		utc_maps_place_foreach_category_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_foreach_category()
 */
int utc_maps_place_foreach_category_n(void)
{
	void *user_data = NULL;

	ret = maps_place_foreach_category(NULL, __utc_maps_place_category_cb, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_foreach_category(__pPlace, NULL, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

static bool __utc_maps_place_attribute_cb(int index, int total, maps_place_attribute_h attribute, void *user_data)
{
	attribute_available = true;
	service_enabled_place = true;

	maps_place_attribute_destroy(attribute);
	return true;
}

/**
 * @testcase		utc_maps_place_foreach_attribute_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_foreach_attribute()
 */
int utc_maps_place_foreach_attribute_n(void)
{
	void *user_data = NULL;

	ret = maps_place_foreach_attribute(NULL, __utc_maps_place_attribute_cb, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_foreach_attribute(__pPlace, NULL, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

static bool __utc_maps_place_contact_cb(int index, int total, maps_place_contact_h contact, void *user_data)
{
	contact_available = true;
	service_enabled_place = true;

	maps_place_contact_destroy(contact);
	return true;
}

/**
 * @testcase		utc_maps_place_foreach_contact_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_foreach_contact()
 */
int utc_maps_place_foreach_contact_n(void)
{
	void *user_data = NULL;

	ret = maps_place_foreach_contact(NULL, __utc_maps_place_contact_cb, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_foreach_contact(__pPlace, NULL, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

static bool __utc_maps_place_editorial_cb(int index, int total, maps_place_editorial_h editorial, void *user_data)
{
	editorial_available = true;
	service_enabled_place = true;

	maps_place_editorial_destroy(editorial);
	return true;
}

/**
 * @testcase		utc_maps_place_foreach_editorial_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_foreach_editorial()
 */
int utc_maps_place_foreach_editorial_n(void)
{
	void *user_data = NULL;

	ret = maps_place_foreach_editorial(NULL, __utc_maps_place_editorial_cb, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_foreach_editorial(__pPlace, NULL, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

static bool __utc_maps_place_image_cb(int index, int total, maps_place_image_h image, void *user_data)
{
	image_available = true;
	service_enabled_place = true;

	maps_place_image_destroy(image);
	return true;
}

/**
 * @testcase		utc_maps_place_foreach_image_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_foreach_image()
 */
int utc_maps_place_foreach_image_n(void)
{
	void *user_data = NULL;

	ret = maps_place_foreach_image(NULL, __utc_maps_place_image_cb, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_foreach_image(__pPlace, NULL, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

static bool __utc_maps_place_review_cb(int index, int total, maps_place_review_h review, void *user_data)
{
	review_available = true;
	service_enabled_place = true;

	maps_place_review_destroy(review);
	return true;
}

/**
 * @testcase		utc_maps_place_foreach_review_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_foreach_review()
 */
int utc_maps_place_foreach_review_n(void)
{
	void *user_data = NULL;

	ret = maps_place_foreach_review(NULL, __utc_maps_place_review_cb, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_foreach_review(__pPlace, NULL, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_get_supplier_link_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_get_supplier_link()
 */
int utc_maps_place_get_supplier_link_n(void)
{
	maps_place_link_object_h supplier = NULL;

	ret = maps_place_get_supplier_link(NULL, &supplier);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_get_supplier_link(__pPlace, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_place_get_related_link_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_get_related_link()
 */
int utc_maps_place_get_related_link_n(void)
{
	maps_place_link_object_h related = NULL;

	ret = maps_place_get_related_link(NULL, &related);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_get_related_link(__pPlace, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

static bool __maps_place_properties_cb(int index, int total, char* key, void* value, void* user_data)
{
	free(key);
	free(value);
	return true;
}

/**
 * @testcase		utc_maps_place_foreach_property_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_foreach_property()
 */
int utc_maps_place_foreach_property_n(void)
{
	ret = maps_place_foreach_property(NULL, __maps_place_properties_cb, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_place_foreach_property(__pPlace, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}
/**
 * @testcase		utc_maps_place_list_destroy_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_place_list_destroy()
 */
int utc_maps_place_list_destroy_n(void)
{
	ret = maps_place_list_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}
