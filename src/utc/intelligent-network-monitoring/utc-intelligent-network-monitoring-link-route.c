/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
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

#include "utc-intelligent-network-monitoring-common.h"

/**
 * @function        utc_inm_link_route_startup
 * @since_tizen     5.5
 * @description     Initializes inm link route.Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_inm_link_route_startup(void)
{
	g_bFeatureInm = inm_check_feature_supported(FEATURE_INM);
	g_hLink = NULL;

	int ret = inm_initialize(&g_hInm);
	PRINT_RETURN("inm_initialize", ret);
	if (ret != INM_ERROR_NONE) {
		if (ret != INM_ERROR_NOT_SUPPORTED || !g_bFeatureInm) {
			FPRINTF("[%s:%d] Fail to initialize\\n", __FILE__, __LINE__);
			dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Fail to initialize", __FILE__, __LINE__);
		}
		return;
	}

	ret = inm_get_current_link(&g_hLink);
	if (ret != INM_ERROR_NONE || !g_hLink) {
		FPRINTF("[%s:%d] Fail to get current link\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Fail to get current link", __FILE__, __LINE__);
		return;
	}

	ret = inm_save_any_route(g_hLink);
	if (ret != INM_ERROR_NONE || !g_hRoute) {
		FPRINTF("[%s:%d] Fail to get current link route\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Fail to get current route", __FILE__, __LINE__);
		return;
	}
}

/**
 * @function        utc_inm_link_route_cleanup
 * @since_tizen     5.5
 * @description     Deinitializes inm.Called after each test.
 * @parameter       NA
 * @return          NA
 */
void utc_inm_link_route_cleanup(void)
{
	int ret;

	ret = inm_link_route_destroy(g_hRoute);
	PRINT_RETURN("inm_link_route_destroy", ret);
	g_hRoute = NULL;

	ret = inm_link_destroy(g_hLink);
	PRINT_RETURN("inm_link_destroy", ret);
	g_hLink = NULL;

	ret = inm_deinitialize(g_hInm);
	PRINT_RETURN("inm_deinitialize", ret);
	g_hInm = NULL;
}

/*****************************************
 * CAPI_NETWORK_INM_LINK_MODULE
 *****************************************/

/**
 * @testcase        utc_inm_link_route_destroy_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Destroys the route handle.
 * @scenario        Invoking inm_link_route_destroy with valid parameter.
 */
int utc_inm_link_route_destroy_p(void)
{
	inm_link_route_h route_clone = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_route_destroy(route_clone);
		CHECK_RETURN("inm_link_route_destroy", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_route_clone(&route_clone, g_hRoute);
	CHECK_RETURN("inm_link_route_clone", ret, INM_ERROR_NONE);

	ret = inm_link_route_destroy(route_clone);
	CHECK_RETURN("inm_link_route_destroy", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_link_route_destroy_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     inm_link_route_destroy should fail with invalid parameter.
 * @scenario        Verify inm_link_destroy by passing invalid parameter.
 */
int utc_inm_link_route_destroy_n(void)
{
	int ret = inm_link_route_destroy(NULL);
	if (!g_bFeatureInm)
		CHECK_RETURN("inm_link_route_destroy", ret, INM_ERROR_NOT_SUPPORTED);
	else
		CHECK_RETURN("inm_link_route_destroy", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_link_route_clone_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Clones a link route handle.
 * @scenario        Verify inm_link_route_clone with valid parameter and destroy it.
 */
int utc_inm_link_route_clone_p(void)
{
	inm_link_route_h route_clone = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_route_clone(&route_clone, g_hRoute);
		CHECK_RETURN("inm_link_clone", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_route_clone(&route_clone, g_hRoute);
	CHECK_RETURN("inm_link_route_clone", ret, INM_ERROR_NONE);

	ret = inm_link_route_destroy(route_clone);
	PRINT_RETURN("inm_link_route_destroy", ret);

	return 0;
}

/**
 * @testcase        utc_inm_link_route_clone_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Should not Clones a link route handle.
 * @scenario        Verify inm_link_clone by passing invalid parameters.
 */
int utc_inm_link_route_clone_n(void)
{
	inm_link_route_h route_clone = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_route_clone(&route_clone, g_hRoute);
		CHECK_RETURN("inm_link_route_clone", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_route_clone(NULL, NULL);
	CHECK_RETURN("inm_link_route_clone", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_route_clone(&route_clone, NULL);
	CHECK_RETURN("inm_link_route_clone", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_route_clone(NULL, g_hRoute);
	CHECK_RETURN("inm_link_route_clone", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_link_route_get_destination_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Get the route destination.
 * @scenario        Invoking inm_link_route_get_destination with valid parameter.
 */
int utc_inm_link_route_get_destination_p(void)
{
	char *destination = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_route_get_destination(g_hRoute, &destination);
		CHECK_RETURN("inm_link_route_get_destination", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_route_get_destination(g_hRoute, &destination);
	if (!destination)
		CHECK_RETURN("inm_link_route_get_destination", ret, INM_ERROR_DATA_NOT_FOUND);
	else
		CHECK_RETURN("inm_link_route_get_destination", ret, INM_ERROR_NONE);
	FREE_MEMORY_TC(destination);

	return 0;
}


/**
 * @testcase        utc_inm_link_route_get_destination_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Should not return route destination.
 * @scenario        Verify inm_link_route_get_destination by passing invalid parameter.
 */
int utc_inm_link_route_get_destination_n(void)
{
	char *destination = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_route_get_destination(g_hRoute, &destination);
		CHECK_RETURN("inm_link_route_get_destination", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_route_get_destination(NULL, NULL);
	CHECK_RETURN("inm_link_route_get_destination", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_route_get_destination(NULL, &destination);
	CHECK_RETURN("inm_link_route_get_destination", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_route_get_destination(g_hRoute, NULL);
	CHECK_RETURN("inm_link_route_get_destination", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_link_route_get_gateway_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Get the route gateway.
 * @scenario        Invoking inm_link_route_get_gateway with valid parameter.
 */
int utc_inm_link_route_get_gateway_p(void)
{
	char *gateway = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_route_get_gateway(g_hRoute, &gateway);
		CHECK_RETURN("inm_link_route_get_gateway", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_route_get_gateway(g_hRoute, &gateway);
	if (!gateway)
		CHECK_RETURN("inm_link_route_get_gateway", ret, INM_ERROR_DATA_NOT_FOUND);
	else
		CHECK_RETURN("inm_link_route_get_gateway", ret, INM_ERROR_NONE);
	FREE_MEMORY_TC(gateway);

	return 0;
}

/**
 * @testcase        utc_inm_link_route_get_gateway_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Should not return route gateway.
 * @scenario        Verify inm_link_route_get_gateway by passing invalid parameter.
 */
int utc_inm_link_route_get_gateway_n(void)
{
	char *gateway = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_route_get_gateway(g_hRoute, &gateway);
		CHECK_RETURN("inm_link_route_get_gateway", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_route_get_gateway(NULL, NULL);
	CHECK_RETURN("inm_link_route_get_gateway", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_route_get_gateway(NULL, &gateway);
	CHECK_RETURN("inm_link_route_get_gateway", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_route_get_gateway(g_hRoute, NULL);
	CHECK_RETURN("inm_link_route_get_gateway", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_link_route_get_interface_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Get the route interface.
 * @scenario        Invoking inm_link_route_get_interface with valid parameter.
 */
int utc_inm_link_route_get_interface_p(void)
{
	char *interface = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_route_get_interface(g_hRoute, &interface);
		CHECK_RETURN("inm_link_route_get_interface", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_route_get_interface(g_hRoute, &interface);
	if (!interface)
		CHECK_RETURN("inm_link_route_get_interface", ret, INM_ERROR_DATA_NOT_FOUND);
	else
		CHECK_RETURN("inm_link_route_get_interface", ret, INM_ERROR_NONE);
	FREE_MEMORY_TC(interface);

	return 0;
}

/**
 * @testcase        utc_inm_link_route_get_interface_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Should not return route interface.
 * @scenario        Verify inm_link_route_get_interface by passing invalid parameter.
 */
int utc_inm_link_route_get_interface_n(void)
{
	char *interface = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_route_get_interface(g_hRoute, &interface);
		CHECK_RETURN("inm_link_route_get_interface", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_route_get_interface(NULL, NULL);
	CHECK_RETURN("inm_link_route_get_interface", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_route_get_interface(NULL, &interface);
	CHECK_RETURN("inm_link_route_get_interface", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_route_get_interface(g_hRoute, NULL);
	CHECK_RETURN("inm_link_route_get_interface", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_link_route_is_default_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Check if route is default route.
 * @scenario        Invoking inm_link_route_is_default with valid parameter.
 */
int utc_inm_link_route_is_default_p(void)
{
	bool is_default;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_route_is_default(g_hRoute, &is_default);
		CHECK_RETURN("inm_link_route_get_interface", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_route_is_default(g_hRoute, &is_default);
	CHECK_RETURN("inm_link_route_get_gateway", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_link_route_is_default_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Should not return route is default.
 * @scenario        Verify inm_link_route_is_default by passing invalid parameter.
 */
int utc_inm_link_route_is_default_n(void)
{
	bool is_default;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_route_is_default(g_hRoute, &is_default);
		CHECK_RETURN("inm_link_route_is_default", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_route_is_default(NULL, NULL);
	CHECK_RETURN("inm_link_route_is_default", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_route_is_default(NULL, &is_default);
	CHECK_RETURN("inm_link_route_is_default", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_route_is_default(g_hRoute, NULL);
	CHECK_RETURN("inm_link_route_is_default", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_link_route_get_type_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Gets the route type.
 * @scenario        Invoking inm_link_route_get_type with valid parameter.
 */
int utc_inm_link_route_get_type_p(void)
{
	inm_link_route_type_e type;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_route_get_type(g_hRoute, &type);
		CHECK_RETURN("inm_link_route_get_type", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_route_get_type(g_hRoute, &type);
	CHECK_RETURN("inm_link_route_get_type", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_link_route_get_type_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Should not return route type.
 * @scenario        Verify inm_link_route_get_type by passing invalid parameter.
 */
int utc_inm_link_route_get_type_n(void)
{
	inm_link_route_type_e type;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_route_get_type(g_hRoute, &type);
		CHECK_RETURN("inm_link_route_get_type", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_route_get_type(NULL, NULL);
	CHECK_RETURN("inm_link_route_get_type", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_route_get_type(NULL, &type);
	CHECK_RETURN("inm_link_route_get_type", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_route_get_type(g_hRoute, NULL);
	CHECK_RETURN("inm_link_route_get_type", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

