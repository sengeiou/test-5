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
#include <maps_preference.h>
#include "utc_maps_utils.h"

static int ret = 0;
static maps_preference_h preference = NULL;
static int iterations = 0;
static bool is_maps_supported = false;

/* typedef bool (*maps_preference_properties_cb)(int index, int total, char *key, char *value, void* user_data); */
static bool __utc_maps_preference_properties_cb(int index, int total, char *key, char *value, void* user_data)
{
	assert(key);
	assert(value);
	assert(index >= 0);
	assert(total > 0);
	assert(index < total);
	iterations++;
	free(key);
	free(value);
	return true;
}


/**
 * @function		utc_maps_preference_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_preference_startup(void)
{
	is_maps_supported = _is_maps_feature_supported();

	maps_preference_create(&preference);
	iterations = 0;
}

/**
 * @function		utc_maps_preference_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_preference_cleanup(void)
{
	maps_preference_destroy(preference);
}

/**
 * @testcase		utc_maps_preference_create_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_create()
 */
int utc_maps_preference_create_p(void)
{
	maps_preference_h test_preference = NULL;

	ret = maps_preference_create(&test_preference);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert(test_preference);

	ret = maps_preference_destroy(test_preference);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_create_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_create()
 */
int utc_maps_preference_create_n(void)
{
	ret = maps_preference_create(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_destroy_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_destroy()
 */
int utc_maps_preference_destroy_p(void)
{
	/* Tested in utc_maps_preference_create_p */
	return 0;
}

/**
 * @testcase		utc_maps_preference_destroy_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_destroy()
 */
int utc_maps_preference_destroy_n(void)
{
	ret = maps_preference_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_clone_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_clone()
 */
int utc_maps_preference_clone_p(void)
{
	maps_preference_h cloned = NULL;

	ret = maps_preference_clone(preference, &cloned);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert(cloned);

	ret = maps_preference_destroy(cloned);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_clone_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_clone()
 */
int utc_maps_preference_clone_n(void)
{
	maps_preference_h cloned = NULL;

	ret = maps_preference_clone(NULL, &cloned);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_clone(preference, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_clone(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_get_distance_unit_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_get_distance_unit()
 */
int utc_maps_preference_get_distance_unit_p(void)
{
	maps_distance_unit_e unit = MAPS_DISTANCE_UNIT_KM;

	ret = maps_preference_set_distance_unit(preference, MAPS_DISTANCE_UNIT_M);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_distance_unit(preference, &unit);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert_eq(unit, MAPS_DISTANCE_UNIT_M);
	return 0;
}

/**
 * @testcase		utc_maps_preference_get_distance_unit_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_get_distance_unit()
 */
int utc_maps_preference_get_distance_unit_n(void)
{
	maps_distance_unit_e unit = MAPS_DISTANCE_UNIT_KM;

	ret = maps_preference_get_distance_unit(NULL, &unit);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_distance_unit(preference, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_distance_unit(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_get_language_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_get_language()
 */
int utc_maps_preference_get_language_p(void)
{
	char *language = NULL;

	ret = maps_preference_set_language(preference, "EN-US");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_language(preference, &language);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert(language);
		assert_eq(strcmp(language, "EN-US"), 0);

		free(language);
	}
	return 0;
}

/**
 * @testcase		utc_maps_preference_get_language_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_get_language()
 */
int utc_maps_preference_get_language_n(void)
{
	char *language = NULL;

	ret = maps_preference_get_language(NULL, &language);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_language(preference, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_language(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_get_max_results_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_get_max_results()
 */
int utc_maps_preference_get_max_results_p(void)
{
	int max_results = 0;

	ret = maps_preference_set_max_results(preference, 4);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_max_results(preference, &max_results);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert_eq(max_results, 4);
	return 0;
}

/**
 * @testcase		utc_maps_preference_get_max_results_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_get_max_results()
 */
int utc_maps_preference_get_max_results_n(void)
{
	int max_results = 0;

	ret = maps_preference_get_max_results(NULL, &max_results);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_max_results(preference, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_max_results(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_get_country_code_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_get_country_code()
 */
int utc_maps_preference_get_country_code_p(void)
{
	char *country_code = NULL;

	ret = maps_preference_set_country_code(preference, "RUS");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_country_code(preference, &country_code);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert(country_code);
		assert_eq(strcmp(country_code, "RUS"), 0);

		free(country_code);
	}
	return 0;
}

/**
 * @testcase		utc_maps_preference_get_country_code_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_get_country_code()
 */
int utc_maps_preference_get_country_code_n(void)
{
	char *country_code = NULL;

	ret = maps_preference_get_country_code(NULL, &country_code);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_country_code(preference, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_country_code(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_get_route_optimization_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_get_route_optimization()
 */
int utc_maps_preference_get_route_optimization_p(void)
{
	maps_route_optimization_e optimization = MAPS_ROUTE_TYPE_SHORTEST;

	ret = maps_preference_set_route_optimization(preference, MAPS_ROUTE_TYPE_FASTEST);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_route_optimization(preference, &optimization);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert_eq(optimization, MAPS_ROUTE_TYPE_FASTEST);
	return 0;
}

/**
 * @testcase		utc_maps_preference_get_route_optimization_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_get_route_optimization()
 */
int utc_maps_preference_get_route_optimization_n(void)
{
	maps_route_optimization_e optimization = MAPS_ROUTE_TYPE_SHORTEST;

	ret = maps_preference_get_route_optimization(NULL, &optimization);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_route_optimization(preference, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_route_optimization(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_get_route_transport_mode_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_get_route_transport_mode()
 */
int utc_maps_preference_get_route_transport_mode_p(void)
{
	maps_route_transport_mode_e transport_mode = MAPS_ROUTE_TRANSPORT_MODE_TRUCK;

	ret = maps_preference_set_route_transport_mode(preference, MAPS_ROUTE_TRANSPORT_MODE_CAR);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_route_transport_mode(preference, &transport_mode);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert_eq(transport_mode, MAPS_ROUTE_TRANSPORT_MODE_CAR);
	return 0;
}

/**
 * @testcase		utc_maps_preference_get_route_transport_mode_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_get_route_transport_mode()
 */
int utc_maps_preference_get_route_transport_mode_n(void)
{
	maps_route_transport_mode_e transport_mode = MAPS_ROUTE_TRANSPORT_MODE_TRUCK;

	ret = maps_preference_get_route_transport_mode(NULL, &transport_mode);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_route_transport_mode(preference, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_route_transport_mode(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_get_route_feature_weight_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_get_route_feature_weight()
 */
int utc_maps_preference_get_route_feature_weight_p(void)
{
	maps_route_feature_weight_e feature_weight = MAPS_ROUTE_FEATURE_WEIGHT_NORMAL;

	ret = maps_preference_set_route_feature_weight(preference, MAPS_ROUTE_FEATURE_WEIGHT_AVOID);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_route_feature_weight(preference, &feature_weight);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert_eq(feature_weight, MAPS_ROUTE_FEATURE_WEIGHT_AVOID);
	return 0;
}

/**
 * @testcase		utc_maps_preference_get_route_feature_weight_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_get_route_feature_weight()
 */
int utc_maps_preference_get_route_feature_weight_n(void)
{
	maps_route_feature_weight_e feature_weight = MAPS_ROUTE_FEATURE_WEIGHT_NORMAL;

	ret = maps_preference_get_route_feature_weight(NULL, &feature_weight);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_route_feature_weight(preference, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_route_feature_weight(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_get_route_feature_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_get_route_feature()
 */
int utc_maps_preference_get_route_feature_p(void)
{
	maps_route_feature_e feature = MAPS_ROUTE_FEATURE_NO;

	ret = maps_preference_set_route_feature(preference, MAPS_ROUTE_FEATURE_TOLL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_route_feature(preference, &feature);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert_eq(feature, MAPS_ROUTE_FEATURE_TOLL);
	return 0;
}

/**
 * @testcase		utc_maps_preference_get_route_feature_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_get_route_feature()
 */
int utc_maps_preference_get_route_feature_n(void)
{
	maps_route_feature_e feature = MAPS_ROUTE_FEATURE_NO;

	ret = maps_preference_get_route_feature(NULL, &feature);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_route_feature(preference, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_route_feature(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_get_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_get()
 */
int utc_maps_preference_get_p(void)
{
	char *value = NULL;

	ret = maps_preference_set_property(preference, "key", "value");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get(preference, "key", &value);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert(value);
		assert_eq(strcmp(value, "value"), 0);

		free(value);
	}
	return 0;
}

/**
 * @testcase		utc_maps_preference_get_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_get()
 */
int utc_maps_preference_get_n(void)
{
	char *value = NULL;

	ret = maps_preference_get(NULL, "key", &value);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get(preference, NULL, &value);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get(preference, "key", NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get(NULL, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_foreach_property_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_foreach_property()
 */
int utc_maps_preference_foreach_property_p(void)
{
	ret = maps_preference_set_property(preference, "key", "value");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_foreach_property(preference, __utc_maps_preference_properties_cb, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert_eq(iterations, 1);
	return 0;
 }

/**
 * @testcase		utc_maps_preference_foreach_property_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_foreach_property()
 */
int utc_maps_preference_foreach_property_n(void)
{
	ret = maps_preference_foreach_property(NULL, __utc_maps_preference_properties_cb, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_foreach_property(preference, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_foreach_property(NULL, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_set_distance_unit_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_set_distance_unit()
 */
int utc_maps_preference_set_distance_unit_p(void)
{
	/* Tested in utc_maps_preference_set_distance_unit_p */
	return 0;
}

/**
 * @testcase		utc_maps_preference_set_distance_unit_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_set_distance_unit()
 */
int utc_maps_preference_set_distance_unit_n(void)
{
	ret = maps_preference_set_distance_unit(NULL, MAPS_DISTANCE_UNIT_M);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_set_distance_unit(preference, 100);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_set_distance_unit(preference, -1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_set_language_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_set_language()
 */
int utc_maps_preference_set_language_p(void)
{
	/* Tested in utc_maps_preference_get_language_p */
	return 0;
}

/**
 * @testcase		utc_maps_preference_set_language_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_set_language()
 */
int utc_maps_preference_set_language_n(void)
{
	ret = maps_preference_set_language(NULL, "EN-US");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_set_language(preference, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_set_language(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_set_max_results_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_set_max_results()
 */
int utc_maps_preference_set_max_results_p(void)
{
	/* Tested in utc_maps_preference_get_max_results_p */
	return 0;
}

/**
 * @testcase		utc_maps_preference_set_max_results_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_set_max_results()
 */
int utc_maps_preference_set_max_results_n(void)
{
	ret = maps_preference_set_max_results(NULL, 4);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_set_max_results(preference, 0);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_set_max_results(NULL, 0);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_set_country_code_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_set_country_code()
 */
int utc_maps_preference_set_country_code_p(void)
{
	/* Tested in utc_maps_preference_get_country_code_p */
	return 0;
}

/**
 * @testcase		utc_maps_preference_set_country_code_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_set_country_code()
 */
int utc_maps_preference_set_country_code_n(void)
{
	ret = maps_preference_set_country_code(NULL, "RUS");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_set_country_code(preference, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_set_country_code(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_set_route_optimization_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_set_route_optimization()
 */
int utc_maps_preference_set_route_optimization_p(void)
{
	/* Tested in utc_maps_preference_get_route_optimization_p */
	return 0;
}

/**
 * @testcase		utc_maps_preference_set_route_optimization_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_set_route_optimization()
 */
int utc_maps_preference_set_route_optimization_n(void)
{
	ret = maps_preference_set_route_optimization(NULL, MAPS_ROUTE_TYPE_FASTEST);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_set_route_transport_mode_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_set_route_transport_mode()
 */
int utc_maps_preference_set_route_transport_mode_p(void)
{
	/* Tested in utc_maps_preference_get_route_transport_mode_p */
	return 0;
}

/**
 * @testcase		utc_maps_preference_set_route_transport_mode_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_set_route_transport_mode()
 */
int utc_maps_preference_set_route_transport_mode_n(void)
{
	ret = maps_preference_set_route_transport_mode(NULL, MAPS_ROUTE_TRANSPORT_MODE_CAR);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_set_route_transport_mode(preference, 100);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_set_route_transport_mode(preference, -1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_set_route_feature_weight_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_set_route_feature_weight()
 */
int utc_maps_preference_set_route_feature_weight_p(void)
{
	/* Tested in utc_maps_preference_get_route_feature_weight_p */
	return 0;
}

/**
 * @testcase		utc_maps_preference_set_route_feature_weight_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_set_route_feature_weight()
 */
int utc_maps_preference_set_route_feature_weight_n(void)
{
	ret = maps_preference_set_route_feature_weight(NULL, MAPS_ROUTE_FEATURE_WEIGHT_AVOID);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_set_route_feature_weight(preference, 5);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_set_route_feature_weight(preference, -1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_set_route_feature_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_set_route_feature()
 */
int utc_maps_preference_set_route_feature_p(void)
{
	/* Tested in utc_maps_preference_get_route_feature_p */
	return 0;
}

/**
 * @testcase		utc_maps_preference_set_route_feature_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_set_route_feature()
 */
int utc_maps_preference_set_route_feature_n(void)
{
	ret = maps_preference_set_route_feature(NULL, MAPS_ROUTE_FEATURE_TOLL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_set_route_feature(preference, 11);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_set_route_feature(preference, -1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_set_property_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_set_property()
 */
int utc_maps_preference_set_property_p(void)
{
	/* Tested in utc_maps_preference_get_p */
	return 0;
}

/**
 * @testcase		utc_maps_preference_set_property_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_set_property()
 */
int utc_maps_preference_set_property_n(void)
{
	ret = maps_preference_set_property(NULL, "key", "value");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_set_property(preference, NULL, "value");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_set_property(preference, "key", NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_set_property(NULL, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_set_route_alternatives_enabled_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_set_route_alternatives_enabled()
 */
int utc_maps_preference_set_route_alternatives_enabled_p(void)
{
	/* Tested in utc_maps_preference_get_route_alternatives_enabled_p */
	return 0;
}

/**
 * @testcase		utc_maps_preference_set_route_alternatives_enabled_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_set_route_alternatives_enabled()
 */
int utc_maps_preference_set_route_alternatives_enabled_n(void)
{
	ret = maps_preference_set_route_alternatives_enabled(NULL, true);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_preference_get_route_alternatives_enabled_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_preference_get_route_alternatives_enabled()
 */
int utc_maps_preference_get_route_alternatives_enabled_p(void)
{
	bool enable = false;

	ret = maps_preference_set_route_alternatives_enabled(preference, true);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_get_route_alternatives_enabled(preference, &enable);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert(enable);
	return 0;
}

/**
 * @testcase		utc_maps_preference_get_route_alternatives_enabled_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_preference_get_route_alternatives_enabled()
 */
int utc_maps_preference_get_route_alternatives_enabled_n(void)
{
	ret = maps_preference_get_route_alternatives_enabled(NULL, (bool*)true);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

