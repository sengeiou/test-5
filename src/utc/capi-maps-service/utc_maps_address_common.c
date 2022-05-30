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
#include <maps_address.h>
#include <maps_service.h>
#include "utc_maps_utils.h"

static int ret = 0;
static maps_address_h address = NULL;
static maps_address_list_h __pAddressList = NULL;
static bool __isCalled = false;
static bool is_maps_supported = false;


/**
 * @function		utc_maps_address_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_address_startup(void)
{
	is_maps_supported = _is_maps_feature_supported();

	maps_address_create(&address);
	maps_address_list_create(&__pAddressList);
}

/**
 * @function		utc_maps_address_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_address_cleanup(void)
{
	maps_address_destroy(address);
	maps_address_list_destroy(__pAddressList);
}

/**
 * @testcase		utc_maps_address_create_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_create()
 */
int utc_maps_address_create_p(void)
{
	maps_address_h test_address = NULL;

	ret = maps_address_create(&test_address);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert(test_address);

	ret = maps_address_destroy(test_address);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_create_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_create()
 */
int utc_maps_address_create_n(void)
{
	ret = maps_address_create(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_destroy_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_destroy()
 */
int utc_maps_address_destroy_p(void)
{
	/* tested in utc_maps_address_create_p */
	return 0;
}

/**
 * @testcase		utc_maps_address_destroy_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_destroy()
 */
int utc_maps_address_destroy_n(void)
{
	ret = maps_address_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_clone_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_clone()
 */
int utc_maps_address_clone_p(void)
{
	maps_address_h clone_address = NULL;
	char *buff = NULL;

	if (is_maps_supported) {
		maps_address_set_building_number(address, "building_number");
		maps_address_set_street(address, "street");
		maps_address_set_district(address, "district");
		maps_address_set_city(address, "city");
		maps_address_set_state(address, "state");
		maps_address_set_country_code(address, "country_code");
		maps_address_set_postal_code(address, "postal_code");
		maps_address_set_freetext(address, "freetext");
		maps_address_set_country(address, "country");
		maps_address_set_county(address, "county");

		ret = maps_address_clone(address, &clone_address);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(clone_address);

		ret = maps_address_get_building_number(clone_address, &buff);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(buff);
		assert(!strcmp(buff, "building_number"));
		if (buff) free(buff);

		ret = maps_address_get_street(clone_address, &buff);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(buff);
		assert(!strcmp(buff, "street"));
		if (buff) free(buff);

		ret = maps_address_get_district(clone_address, &buff);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(buff);
		assert(!strcmp(buff, "district"));
		if (buff) free(buff);

		ret = maps_address_get_city(clone_address, &buff);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(buff);
		assert(!strcmp(buff, "city"));
		if (buff) free(buff);

		ret = maps_address_get_state(clone_address, &buff);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(buff);
		assert(!strcmp(buff, "state"));
		if (buff) free(buff);

		ret = maps_address_get_country_code(clone_address, &buff);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(buff);
		assert(!strcmp(buff, "country_code"));
		if (buff) free(buff);

		ret = maps_address_get_postal_code(clone_address, &buff);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(buff);
		assert(!strcmp(buff, "postal_code"));
		if (buff) free(buff);

		ret = maps_address_get_country(clone_address, &buff);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(buff);
		assert(!strcmp(buff, "country"));
		if (buff) free(buff);

		ret = maps_address_get_county(clone_address, &buff);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(buff);
		assert(!strcmp(buff, "county"));
		if (buff) free(buff);

		ret = maps_address_destroy(clone_address);
		assert_eq(ret, MAPS_ERROR_NONE);
	} else {
		ret = maps_address_clone(address, &clone_address);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_maps_address_clone_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_clone()
 */
int utc_maps_address_clone_n(void)
{
	maps_address_h clone_address = NULL;

	ret = maps_address_clone(NULL, &clone_address);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
	assert(!clone_address);

	ret = maps_address_clone(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_set_building_number_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_set_building_number()
 */
int utc_maps_address_set_building_number_p(void)
{
	/* tested in utc_maps_address_get_building_number_p */
	return 0;
}

/**
 * @testcase		utc_maps_address_set_building_number_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_set_building_number()
 */
int utc_maps_address_set_building_number_n(void)
{
	ret = maps_address_set_building_number(NULL, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_set_building_number(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_set_street_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_set_street()
 */
int utc_maps_address_set_street_p(void)
{
	/* tested in utc_maps_address_get_street_p */
	return 0;
}

/**
 * @testcase		utc_maps_address_set_street_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_set_street()
 */
int utc_maps_address_set_street_n(void)
{
	ret = maps_address_set_street(NULL, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_set_street(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_set_district_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_set_district()
 */
int utc_maps_address_set_district_p(void)
{
	/* tested in utc_maps_address_get_district_p */
	return 0;
}

/**
 * @testcase		utc_maps_address_set_district_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_set_district()
 */
int utc_maps_address_set_district_n(void)
{
	ret = maps_address_set_district(NULL, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_set_district(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_set_city_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_set_city()
 */
int utc_maps_address_set_city_p(void)
{
	/* tested in utc_maps_address_get_city_p */
	return 0;
}

/**
 * @testcase		utc_maps_address_set_city_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_set_city()
 */
int utc_maps_address_set_city_n(void)
{
	ret = maps_address_set_city(NULL, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_set_city(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_set_state_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_set_state()
 */
int utc_maps_address_set_state_p(void)
{
	/* tested in utc_maps_address_get_state_p */
	return 0;
}

/**
 * @testcase		utc_maps_address_set_state_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_set_state()
 */
int utc_maps_address_set_state_n(void)
{
	ret = maps_address_set_state(NULL, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_set_state(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_set_country_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_set_country()
 */
int utc_maps_address_set_country_p(void)
{
	/* tested in utc_maps_address_get_country_p */
	return 0;
}

/**
 * @testcase		utc_maps_address_set_country_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_set_country()
 */
int utc_maps_address_set_country_n(void)
{
	ret = maps_address_set_country(NULL, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_set_country(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_set_country_code_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_set_country_code()
 */
int utc_maps_address_set_country_code_p(void)
{
	/* tested in utc_maps_address_get_country_code_p */
	return 0;
}

/**
 * @testcase		utc_maps_address_set_country_code_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_set_country_code()
 */
int utc_maps_address_set_country_code_n(void)
{
	ret = maps_address_set_country_code(NULL, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_set_country_code(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_set_county_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_set_county()
 */
int utc_maps_address_set_county_p(void)
{
	/* tested in utc_maps_address_get_county_p */
	return 0;
}

/**
 * @testcase		utc_maps_address_set_county_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_set_county()
 */
int utc_maps_address_set_county_n(void)
{
	ret = maps_address_set_county(NULL, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_set_county(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_set_postal_code_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_set_postal_code()
 */
int utc_maps_address_set_postal_code_p(void)
{
	/* tested in utc_maps_address_get_postal_code_p */
	return 0;
}

/**
 * @testcase		utc_maps_address_set_postal_code_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_set_postal_code()
 */
int utc_maps_address_set_postal_code_n(void)
{
	ret = maps_address_set_postal_code(NULL, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_set_postal_code(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_set_freetext_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_set_freetext()
 */
int utc_maps_address_set_freetext_p(void)
{
	/* tested in utc_maps_address_get_freetext_p */
	return 0;
}

/**
 * @testcase		utc_maps_address_set_freetext_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_set_freetext()
 */
int utc_maps_address_set_freetext_n(void)
{
	ret = maps_address_set_freetext(NULL, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_set_freetext(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_get_building_number_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_get_building_number()
 */
int utc_maps_address_get_building_number_p(void)
{
	char *building_number = NULL;

	ret = maps_address_set_building_number(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_building_number(address, &building_number);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert(building_number);
		assert_eq(strcmp(building_number, "test"), 0);

		free(building_number);
	}
	return 0;
}

/**
 * @testcase		utc_maps_address_get_building_number_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_get_building_number()
 */
int utc_maps_address_get_building_number_n(void)
{
	char *building_number = NULL;

	ret = maps_address_set_building_number(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_building_number(NULL, &building_number);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
	assert(!building_number);

	ret = maps_address_get_building_number(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_get_street_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_get_street()
 */
int utc_maps_address_get_street_p(void)
{
	char *street = NULL;

	ret = maps_address_set_street(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_street(address, &street);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert(street);
		assert_eq(strcmp(street, "test"), 0);

		free(street);
	}
	return 0;
}

/**
 * @testcase		utc_maps_address_get_street_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_get_street()
 */
int utc_maps_address_get_street_n(void)
{
	char *street = NULL;
	
	ret = maps_address_set_street(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_street(NULL, &street);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
	assert(!street);

	ret = maps_address_get_street(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_get_district_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_get_district()
 */
int utc_maps_address_get_district_p(void)
{
	char *district = NULL;

	ret = maps_address_set_district(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_district(address, &district);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert(district);
		assert_eq(strcmp(district, "test"), 0);

		free(district);
	}
	return 0;
}

/**
 * @testcase		utc_maps_address_get_district_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_get_district()
 */
int utc_maps_address_get_district_n(void)
{
	char *district = NULL;

	ret = maps_address_set_district(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_district(NULL, &district);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
	assert(!district);

	ret = maps_address_get_district(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_get_city_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_get_city()
 */
int utc_maps_address_get_city_p(void)
{
	char *city = NULL;

	ret = maps_address_set_city(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_city(address, &city);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert(city);
		assert_eq(strcmp(city, "test"), 0);

		free(city);
	}
	return 0;
}

/**
 * @testcase		utc_maps_address_get_city_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_get_city()
 */
int utc_maps_address_get_city_n(void)
{
	char *city = NULL;

	ret = maps_address_set_city(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_city(NULL, &city);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
	assert(!city);

	ret = maps_address_get_city(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_get_state_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_get_state()
 */
int utc_maps_address_get_state_p(void)
{
	char *state = NULL;

	ret = maps_address_set_state(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_state(address, &state);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert(state);
		assert_eq(strcmp(state, "test"), 0);

		free(state);
	}
	return 0;
}

/**
 * @testcase		utc_maps_address_get_state_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_get_state()
 */
int utc_maps_address_get_state_n(void)
{
	char *state = NULL;

	ret = maps_address_set_state(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_state(NULL, &state);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
	assert(!state);

	ret = maps_address_get_state(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_get_country_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_get_country()
 */
int utc_maps_address_get_country_p(void)
{
	char *country = NULL;

	ret = maps_address_set_country(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_country(address, &country);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert(country);
		assert_eq(strcmp(country, "test"), 0);

		free(country);
	}
	return 0;
}

/**
 * @testcase		utc_maps_address_get_country_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_get_country()
 */
int utc_maps_address_get_country_n(void)
{
	char *country = NULL;

	ret = maps_address_set_country(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_country(NULL, &country);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
	assert(!country);

	ret = maps_address_get_country(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_get_country_code_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_get_country_code()
 */
int utc_maps_address_get_country_code_p(void)
{
	char *country_code = NULL;

	ret = maps_address_set_country_code(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_country_code(address, &country_code);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert(country_code);
		assert_eq(strcmp(country_code, "test"), 0);

		free(country_code);
	}
	return 0;
}

/**
 * @testcase		utc_maps_address_get_country_code_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_get_country_code()
 */
int utc_maps_address_get_country_code_n(void)
{
	char *country_code = NULL;

	ret = maps_address_set_country_code(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_country_code(NULL, &country_code);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
	assert(!country_code);

	ret = maps_address_get_country_code(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_get_county_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_get_county()
 */
int utc_maps_address_get_county_p(void)
{
	char *county = NULL;

	ret = maps_address_set_county(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_county(address, &county);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert(county);
		assert_eq(strcmp(county, "test"), 0);

		free(county);
	}
	return 0;
}

/**
 * @testcase		utc_maps_address_get_county_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_get_county()
 */
int utc_maps_address_get_county_n(void)
{
	char *county = NULL;

	ret = maps_address_set_county(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_county(NULL, &county);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
	assert(!county);

	ret = maps_address_get_county(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_get_postal_code_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_get_postal_code()
 */
int utc_maps_address_get_postal_code_p(void)
{
	char *postal_code = NULL;

	ret = maps_address_set_postal_code(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_postal_code(address, &postal_code);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert(postal_code);
		assert_eq(strcmp(postal_code, "test"), 0);

		free(postal_code);
	}
	return 0;
}

/**
 * @testcase		utc_maps_address_get_postal_code_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_get_postal_code()
 */
int utc_maps_address_get_postal_code_n(void)
{
	char *postal_code = NULL;

	ret = maps_address_set_postal_code(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_postal_code(NULL, &postal_code);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
	assert(!postal_code);

	ret = maps_address_get_postal_code(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_get_freetext_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_get_freetext()
 */
int utc_maps_address_get_freetext_p(void)
{
	char *freetext = NULL;

	ret = maps_address_set_freetext(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_freetext(address, &freetext);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert(freetext);
		assert_eq(strcmp(freetext, "test"), 0);

		free(freetext);
	}
	return 0;
}

/**
 * @testcase		utc_maps_address_get_freetext_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_get_freetext()
 */
int utc_maps_address_get_freetext_n(void)
{
	char *freetext = NULL;

	ret = maps_address_set_freetext(address, "test");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_get_freetext(NULL, &freetext);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
	assert(!freetext);

	ret = maps_address_get_freetext(address, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}


/**
 * @testcase		utc_maps_address_list_create_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_list_create()
 */
int utc_maps_address_list_create_p(void)
{
	maps_address_list_h addr_list = NULL;

	ret = maps_address_list_create(&addr_list);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert(addr_list);
	ret = maps_address_list_destroy(addr_list);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_list_create_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_list_create()
 */
int utc_maps_address_list_create_n(void)
{
	ret = maps_address_list_create(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_list_destroy_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_list_destroy()
 */
int utc_maps_address_list_destroy_p(void)
{
	/* tested in utc_maps_address_list_create_p */
	return 0;
}

/**
 * @testcase		utc_maps_address_list_destroy_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_list_destroy()
 */
int utc_maps_address_list_destroy_n(void)
{
	ret = maps_address_list_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_list_append_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_list_append()
 */
int utc_maps_address_list_append_p(void)
{
	ret = maps_address_list_append(__pAddressList, address);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_list_remove(__pAddressList, address);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_list_append_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_list_append()
 */
int utc_maps_address_list_append_n(void)
{
	ret = maps_address_list_append(NULL, address);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_list_append(__pAddressList, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_list_remove_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_list_remove()
 */
int utc_maps_address_list_remove_p(void)
{
	/* tested in utc_maps_address_list_append_p */
	return 0;
}

/**
 * @testcase		utc_maps_address_list_remove_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_list_remove()
 */
int utc_maps_address_list_remove_n(void)
{
	ret = maps_address_list_remove(NULL, address);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_list_remove(__pAddressList, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_list_get_length_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_list_get_length()
 */
int utc_maps_address_list_get_length_p(void)
{
	int len = 0;

	ret = maps_address_list_get_length(__pAddressList, &len);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_list_get_length_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_list_get_length()
 */
int utc_maps_address_list_get_length_n(void)
{
	int len = 0;

	ret = maps_address_list_get_length(NULL, &len);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_list_get_length(__pAddressList, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

static bool __maps_address_list_cb(int index, maps_address_h addr, void *user_data)
{
	__isCalled = true;
	assert(addr);

	return true;
}

/**
 * @testcase		utc_maps_address_list_foreach_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_address_list_foreach()
 */
int utc_maps_address_list_foreach_p(void)
{
	ret = maps_address_list_append(__pAddressList, address);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_list_foreach(__pAddressList, __maps_address_list_cb, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert_eq(__isCalled, true);

	ret = maps_address_list_remove(__pAddressList, address);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_address_list_foreach_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_address_list_foreach()
 */
int utc_maps_address_list_foreach_n(void)
{
	ret = maps_address_list_foreach(NULL, __maps_address_list_cb, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_list_foreach(__pAddressList, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

