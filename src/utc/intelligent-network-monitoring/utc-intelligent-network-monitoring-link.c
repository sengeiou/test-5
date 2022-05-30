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
 * @function        utc_inm_link_startup
 * @since_tizen     5.5
 * @description     Initializes inm link.Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_inm_link_startup(void)
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
}

/**
 * @function        utc_inm_link_cleanup
 * @since_tizen     5.5
 * @description     Deinitializes inm link.Called after each test.
 * @parameter       NA
 * @return          NA
 */
void utc_inm_link_cleanup(void)
{
	int ret;

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
 * @testcase        utc_inm_link_destroy_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Destroys the link handle.
 * @scenario        Invoking inm_link_destroy with valid parameter.
 */
int utc_inm_link_destroy_p(void)
{
	inm_link_h link_clone = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_destroy(link_clone);
		CHECK_RETURN("inm_link_destroy", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (g_hLink != NULL) {
		ret = inm_link_clone(&link_clone, g_hLink);
		CHECK_RETURN("inm_link_clone", ret, INM_ERROR_NONE);
	}

	ret = inm_link_destroy(link_clone);
	CHECK_RETURN("inm_link_destroy", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_link_destroy_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     inm_link_destroy should fail with invalid parameter.
 * @scenario        Verify inm_link_destroy by passing invalid parameter.
 */
int utc_inm_link_destroy_n(void)
{
	int ret = inm_link_destroy(NULL);

	if (!g_bFeatureInm)
		CHECK_RETURN("inm_link_destroy", ret, INM_ERROR_NOT_SUPPORTED);
	else
		CHECK_RETURN("inm_link_destroy", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_link_clone_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Clones a link handle.
 * @scenario        Verify inm_link_clone with valid parameter and destroy it.
 */
int utc_inm_link_clone_p(void)
{
	inm_link_h link_cloned = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_clone(&link_cloned, g_hLink);
		CHECK_RETURN("inm_link_clone", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_clone(&link_cloned, g_hLink);
	CHECK_RETURN("inm_link_clone", ret, INM_ERROR_NONE);

	ret = inm_link_destroy(link_cloned);
	PRINT_RETURN("inm_link_destroy", ret);

	return 0;
}

/**
 * @testcase        utc_inm_link_clone_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Should not Clones a profile handle.
 * @scenario        Verify inm_link_clone by passing invalid parameters.
 */
int utc_inm_link_clone_n(void)
{
	inm_link_h link_cloned = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_clone(&link_cloned, g_hLink);
		CHECK_RETURN("inm_link_clone", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_clone(NULL, NULL);
	CHECK_RETURN("inm_link_clone", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_clone(NULL, g_hLink);
	CHECK_RETURN("inm_link_clone", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_clone(&link_cloned, NULL);
	CHECK_RETURN("inm_link_clone", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_link_get_interface_name_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Gets the link interface name.
 * @scenario        Invoking inm_link_get_interface_name with valid link handle.
 */
int utc_inm_link_get_interface_name_p(void)
{
	char *name = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_get_interface_name(g_hLink, &name);
		CHECK_RETURN("inm_link_get_interface_name", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_get_interface_name(g_hLink, &name);
	FREE_MEMORY_TC(name);
	CHECK_RETURN("inm_link_get_interface_name", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_link_get_interface_name_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Should not return link name.
 * @scenario        Verify inm_link_get_interface_name by passing invalid parameter.
 */
int utc_inm_link_get_interface_name_n(void)
{
	char *name = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_get_interface_name(g_hLink, &name);
		CHECK_RETURN("inm_link_get_interface_name", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_get_interface_name(NULL, NULL);
	CHECK_RETURN("inm_link_get_interface_name", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_get_interface_name(NULL, &name);
	CHECK_RETURN("inm_link_get_interface_name", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_get_interface_name(g_hLink, NULL);
	CHECK_RETURN("inm_link_get_interface_name", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_link_get_flags_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Gets the link flags.
 * @scenario        Invoking inm_link_get_flags with valid link handle.
 */
int utc_inm_link_get_flags_p(void)
{
	int flags;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_get_flags(g_hLink, &flags);
		CHECK_RETURN("inm_link_get_flags", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_get_flags(g_hLink, &flags);
	CHECK_RETURN("inm_link_get_flags", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_link_get_flags_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Should not return link flags.
 * @scenario        Verify inm_link_get_flags by passing invalid parameter.
 */
int utc_inm_link_get_flags_n(void)
{
	int flags;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_get_flags(g_hLink, &flags);
		CHECK_RETURN("inm_link_get_flags", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_get_flags(NULL, NULL);
	CHECK_RETURN("inm_link_get_flags", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_get_flags(NULL, &flags);
	CHECK_RETURN("inm_link_get_flags", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_get_flags(g_hLink, NULL);
	CHECK_RETURN("inm_link_get_flags", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_link_get_operation_state_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Gets the link operation state.
 * @scenario        Invoking inm_link_get_operation_state with valid link handle.
 */
int utc_inm_link_get_operation_state_p(void)
{
	inm_link_oper_state_e operation_state;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_get_operation_state(g_hLink, &operation_state);
		CHECK_RETURN("inm_link_get_operation_state", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_get_operation_state(g_hLink, &operation_state);
	CHECK_RETURN("inm_link_get_operation_state", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_link_get_operation_state_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Should not return link operation state.
 * @scenario        Verify inm_link_get_operation_state by passing invalid parameter.
 */
int utc_inm_link_get_operation_state_n(void)
{
	inm_link_oper_state_e operation_state;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_get_operation_state(g_hLink, &operation_state);
		CHECK_RETURN("inm_link_get_operation_state", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}
	ret = inm_link_get_operation_state(NULL, NULL);
	CHECK_RETURN("inm_link_get_operation_state", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_get_operation_state(NULL, &operation_state);
	CHECK_RETURN("inm_link_get_operation_state", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_get_operation_state(g_hLink, NULL);
	CHECK_RETURN("inm_link_get_operation_state", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_link_get_received_bytes_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Gets the link received bytes.
 * @scenario        Invoking inm_link_get_received_bytes with valid link handle.
 */
int utc_inm_link_get_received_bytes_p(void)
{
	unsigned long long bytes;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_get_received_bytes(g_hLink, &bytes);
		CHECK_RETURN("inm_link_get_received_bytes", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_get_received_bytes(g_hLink, &bytes);
	CHECK_RETURN("inm_link_get_received_bytes", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_link_get_received_bytes_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Should not return link received bytes.
 * @scenario        Verify inm_link_get_received_bytes by passing invalid parameter.
 */
int utc_inm_link_get_received_bytes_n(void)
{
	unsigned long long bytes;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_get_received_bytes(g_hLink, &bytes);
		CHECK_RETURN("inm_link_get_received_bytes", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_get_received_bytes(NULL, NULL);
	CHECK_RETURN("inm_link_get_received_bytes", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_get_received_bytes(NULL, &bytes);
	CHECK_RETURN("inm_link_get_received_bytes", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_get_received_bytes(g_hLink, NULL);
	CHECK_RETURN("inm_link_get_received_bytes", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_link_get_sent_bytes_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Gets the link sent bytes.
 * @scenario        Invoking inm_link_get_sent_bytes with valid link handle.
 */
int utc_inm_link_get_sent_bytes_p(void)
{
	unsigned long long bytes;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_get_sent_bytes(g_hLink, &bytes);
		CHECK_RETURN("inm_link_get_sent_bytes", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_get_sent_bytes(g_hLink, &bytes);
	CHECK_RETURN("inm_link_get_sent_bytes", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_link_get_sent_bytes_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Should not return link sent bytes.
 * @scenario        Verify inm_link_get_sent_bytes by passing invalid parameter.
 */
int utc_inm_link_get_sent_bytes_n(void)
{
	unsigned long long bytes;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_get_sent_bytes(g_hLink, &bytes);
		CHECK_RETURN("inm_link_get_sent_bytes", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_get_sent_bytes(NULL, NULL);
	CHECK_RETURN("inm_link_get_sent_bytes", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_get_sent_bytes(NULL, &bytes);
	CHECK_RETURN("inm_link_get_sent_bytes", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_get_sent_bytes(g_hLink, NULL);
	CHECK_RETURN("inm_link_get_sent_bytes", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_link_foreach_address_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Gets the link address information.
 * @scenario        Get all the network interface address information. Ensure no error.
 */
int utc_inm_link_foreach_address_p(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_foreach_address(g_hLink, inm_foreach_address_callback, NULL);
		CHECK_RETURN("inm_link_foreach_address", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_foreach_address(g_hLink, inm_foreach_address_callback, NULL);
	CHECK_RETURN("inm_link_foreach_address", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_link_foreach_address_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Verify inm_link_foreach_address by passing invalid parameters
 * @scenario        Pass invalid parameters and ensure network interface information are not returned.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_link_foreach_address_n(void)
{
    int ret = INM_ERROR_NONE;

	ret = inm_link_foreach_address(NULL, NULL, NULL);

	if (!g_bFeatureInm)
		CHECK_RETURN("inm_link_foreach_address", ret, INM_ERROR_NOT_SUPPORTED);
	else
		CHECK_RETURN("inm_link_foreach_address", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_link_foreach_route_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Gets the link route information.
 * @scenario        Get all the network interface route information. Ensure no error.
 */
int utc_inm_link_foreach_route_p(void)
{
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_foreach_route(g_hLink, inm_foreach_route_callback, NULL);
		CHECK_RETURN("inm_link_foreach_route", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_foreach_route(g_hLink, inm_foreach_route_callback, NULL);
	CHECK_RETURN("inm_link_foreach_route", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_link_foreach_route_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Verify inm_link_foreach_route by passing invalid parameters
 * @scenario        Pass invalid parameters and ensure network interface information are not returned.
 *                  Ensure return value should be INM_ERROR_INVALID_PARAMETER.
 */
int utc_inm_link_foreach_route_n(void)
{
    int ret = INM_ERROR_NONE;

	ret = inm_link_foreach_route(NULL, NULL, NULL);

	if (!g_bFeatureInm)
		CHECK_RETURN("inm_link_foreach_route", ret, INM_ERROR_NOT_SUPPORTED);
	else
		CHECK_RETURN("inm_link_foreach_route", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}
