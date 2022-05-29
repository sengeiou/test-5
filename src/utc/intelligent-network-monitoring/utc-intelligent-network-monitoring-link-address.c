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
 * @function        utc_inm_link_address_startup
 * @since_tizen     5.5
 * @description     Initializes inm link address.Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_inm_link_address_startup(void)
{
	g_bFeatureInm = inm_check_feature_supported(FEATURE_INM);
	g_hLink = NULL;
	g_hAddress = NULL;

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

	ret = inm_save_any_address(g_hLink);
	if (ret != INM_ERROR_NONE || !g_hAddress) {
		FPRINTF("[%s:%d] Fail to get current link address\\n", __FILE__, __LINE__);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Fail to get current address", __FILE__, __LINE__);
		return;
	}
}

/**
 * @function        utc_inm_link_address_cleanup
 * @since_tizen     5.5
 * @description     Deinitializes inm link address.Called after each test.
 * @parameter       NA
 * @return          NA
 */
void utc_inm_link_address_cleanup(void)
{
	int ret;

	ret = inm_link_address_destroy(g_hAddress);
	PRINT_RETURN("inm_link_address_destroy", ret);
	g_hAddress = NULL;

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
 * @testcase        utc_inm_link_address_destroy_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Destroys the address handle.
 * @scenario        Invoking inm_link_address_destroy with valid parameter.
 */
int utc_inm_link_address_destroy_p(void)
{
	inm_link_address_h address_clone = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_address_destroy(address_clone);
		CHECK_RETURN("inm_link_address_destroy", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_address_clone(&address_clone, g_hAddress);
	CHECK_RETURN("inm_link_address_clone", ret, INM_ERROR_NONE);

	ret = inm_link_address_destroy(address_clone);
	CHECK_RETURN("inm_link_address_destroy", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_link_address_destroy_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     inm_link_address_destroy should fail with invalid parameter.
 * @scenario        Verify inm_link_destroy by passing invalid parameter.
 */
int utc_inm_link_address_destroy_n(void)
{
	int ret = inm_link_address_destroy(NULL);

	if (!g_bFeatureInm)
		CHECK_RETURN("inm_link_address_destroy", ret, INM_ERROR_NOT_SUPPORTED);
	else
		CHECK_RETURN("inm_link_address_destroy", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_link_address_clone_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Clones a link address handle.
 * @scenario        Verify inm_link_address_clone with valid parameter and destroy it.
 */
int utc_inm_link_address_clone_p(void)
{
	inm_link_address_h address_clone = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_address_clone(&address_clone, g_hAddress);
		CHECK_RETURN("inm_link_clone", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_address_clone(&address_clone, g_hAddress);
	CHECK_RETURN("inm_link_clone", ret, INM_ERROR_NONE);

	ret = inm_link_address_destroy(address_clone);
	PRINT_RETURN("inm_link_address_destroy", ret);

	return 0;
}

/**
 * @testcase        utc_inm_link_address_clone_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Should not Clones a link address handle.
 * @scenario        Verify inm_link_clone by passing invalid parameters.
 */
int utc_inm_link_address_clone_n(void)
{
	inm_link_address_h address_clone = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_address_clone(&address_clone, g_hAddress);
		CHECK_RETURN("inm_link_clone", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_address_clone(NULL, NULL);
	CHECK_RETURN("inm_link_clone", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_address_clone(&address_clone, NULL);
	CHECK_RETURN("inm_link_clone", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_address_clone(NULL, g_hAddress);
	CHECK_RETURN("inm_link_clone", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_link_address_get_family_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Get the address family.
 * @scenario        Invoking inm_link_address_get_family with valid parameter.
 */
int utc_inm_link_address_get_family_p(void)
{
	inm_address_family_e family;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_address_get_family(g_hAddress, &family);
		CHECK_RETURN("inm_link_address_get_family", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_address_get_family(g_hAddress, &family);
	CHECK_RETURN("inm_link_address_get_family", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_link_address_get_family_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Should not return address family.
 * @scenario        Verify inm_link_address_get_family by passing invalid parameter.
 */
int utc_inm_link_address_get_family_n(void)
{
	inm_address_family_e family;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_address_get_family(g_hAddress, &family);
		CHECK_RETURN("inm_link_address_get_family", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_address_get_family(NULL, NULL);
	CHECK_RETURN("inm_link_address_get_family", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_address_get_family(NULL, &family);
	CHECK_RETURN("inm_link_address_get_family", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_address_get_family(g_hAddress, NULL);
	CHECK_RETURN("inm_link_address_get_family", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_link_address_get_prefix_length_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Get the address prefix length.
 * @scenario        Invoking inm_link_address_get_prefix_length with valid parameter.
 */
int utc_inm_link_address_get_prefix_length_p(void)
{
	int prefix_length;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_address_get_prefix_length(g_hAddress, &prefix_length);
		CHECK_RETURN("inm_link_address_get_prefix_length", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_address_get_prefix_length(g_hAddress, &prefix_length);
	CHECK_RETURN("inm_link_address_get_prefix_length", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_link_address_get_prefix_length_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Should not return address prefix length.
 * @scenario        Verify inm_link_address_get_prefix_length by passing invalid parameter.
 */
int utc_inm_link_address_get_prefix_length_n(void)
{
	int prefix_length;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_address_get_prefix_length(g_hAddress, &prefix_length);
		CHECK_RETURN("inm_link_address_get_prefix_length", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_address_get_prefix_length(NULL, NULL);
	CHECK_RETURN("inm_link_address_get_prefix_length", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_address_get_prefix_length(NULL, &prefix_length);
	CHECK_RETURN("inm_link_address_get_prefix_length", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_address_get_prefix_length(g_hAddress, NULL);
	CHECK_RETURN("inm_link_address_get_prefix_length", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_link_address_get_scope_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Get the address scope.
 * @scenario        Invoking inm_link_address_get_scope with valid parameter.
 */
int utc_inm_link_address_get_scope_p(void)
{
	inm_link_scope_e scope;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_address_get_scope(g_hAddress, &scope);
		CHECK_RETURN("inm_link_address_get_scope", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_address_get_scope(g_hAddress, &scope);
	CHECK_RETURN("inm_link_address_get_scope", ret, INM_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_inm_link_address_get_scope_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Should not return address scope.
 * @scenario        Verify inm_link_address_get_scope by passing invalid parameter.
 */
int utc_inm_link_address_get_scope_n(void)
{
	inm_link_scope_e scope;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_address_get_scope(g_hAddress, &scope);
		CHECK_RETURN("inm_link_address_get_family", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_address_get_scope(NULL, NULL);
	CHECK_RETURN("inm_link_address_get_family", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_address_get_scope(NULL, &scope);
	CHECK_RETURN("inm_link_address_get_family", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_address_get_scope(g_hAddress, NULL);
	CHECK_RETURN("inm_link_address_get_family", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_inm_link_address_get_string_p
 * @since_tizen     5.5
 * @type            Positive
 * @description     Get the address string.
 * @scenario        Invoking inm_link_address_get_string with valid parameter.
 */
int utc_inm_link_address_get_string_p(void)
{
	char *p_addr_str = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_address_get_string(g_hAddress, &p_addr_str);
		CHECK_RETURN("inm_link_address_get_string", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_address_get_string(g_hAddress, &p_addr_str);
	if (!p_addr_str)
		CHECK_RETURN("inm_link_address_get_string", ret, INM_ERROR_DATA_NOT_FOUND);
	else
		CHECK_RETURN("inm_link_address_get_string", ret, INM_ERROR_NONE);
	FREE_MEMORY_TC(p_addr_str);

	return 0;
}

/**
 * @testcase        utc_inm_link_address_get_string_n
 * @since_tizen     5.5
 * @type            Negative
 * @description     Should not return address string.
 * @scenario        Verify inm_link_address_get_string by passing invalid parameter.
 */
int utc_inm_link_address_get_string_n(void)
{
	char *p_addr_str = NULL;
	int ret = INM_ERROR_NONE;

	if (!g_bFeatureInm) {
		ret = inm_link_address_get_string(g_hAddress, &p_addr_str);
		CHECK_RETURN("inm_link_address_get_string", ret, INM_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = inm_link_address_get_string(NULL, NULL);
	CHECK_RETURN("inm_link_address_get_string", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_address_get_string(NULL, &p_addr_str);
	CHECK_RETURN("inm_link_address_get_string", ret, INM_ERROR_INVALID_PARAMETER);
	ret = inm_link_address_get_string(g_hAddress, NULL);
	CHECK_RETURN("inm_link_address_get_string", ret, INM_ERROR_INVALID_PARAMETER);

	return 0;
}
