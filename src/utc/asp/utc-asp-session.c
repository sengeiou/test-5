//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <asp.h>
#include <system_info.h>

#include "assert.h"
static bool g_asp_supported = false;
static asp_session_h local_session = NULL;

//& set: Asp-Session

/**
 * @function		utc_asp_session_startup
 * @since_tizen		4.0
 * @description		Created the Session Handle before each session related CAPI's
 * @parameter		NA
 * @return			NA
 */
void utc_asp_session_startup(void)
{
	/* TODO check mac_addr and adv_id */
	char *mac_addr = "00:11:22:33:44:55";
	int adv_id = 0x01;
	system_info_get_platform_bool("http://tizen.org/feature/network.asp", &g_asp_supported);
	asp_initialize();
	asp_session_create(mac_addr, adv_id, &local_session);
}

/**
 * @function		utc_asp_session_cleanup
 * @since_tizen		4.0
 * @description		Destroy the session Handle before each session related CAPI's
 * @parameter		NA
 * @return			NA
 */
void utc_asp_session_cleanup(void)
{
	asp_session_destroy(local_session);
	asp_deinitialize();
}


/**
 * @testcase		utc_asp_session_get_mac_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Gets the session mac for an Application Service Platform session.
 * @scenario		First create the session handle & then get the  session mac address.
 					In clean-up function, destroy the session handle.
 *
 */
int utc_asp_session_get_mac_p(void)
{
	int ret = ASP_ERROR_NONE;
	char *sesion_mac = NULL;
	if(g_asp_supported == false) {
		ret = asp_session_get_mac(local_session, &sesion_mac);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_mac(local_session, &sesion_mac);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_mac_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_mac() by passing the Null Handle.
 * @scenario		Pass the Null handle in asp_session_get_mac()and ensure no unexpected behaviour.
 *					Also ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_session_get_mac_n1(void)
{
	int ret = ASP_ERROR_NONE;
	char *sesion_mac = NULL;

	if(g_asp_supported == false) {
		ret = asp_session_get_mac(NULL, &sesion_mac);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_mac(NULL, &sesion_mac);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_mac_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_mac() by passing the Null pointer in place of session_mac address
 * @scenario		Pass the Null pointer in asp_session_get_mac()and ensure no unexpected behavior.
 *					Also ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 					In clean-up function, destroy the session handle.
 */
int utc_asp_session_get_mac_n2(void)
{
   	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_get_mac(local_session, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_mac(local_session, NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_mac_n3
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_mac() with invalid handle
 * @scenario		Call the asp_session_get_mac()function with invalid handle
 *					and ensure ASP_ERROR_SESSION_NOT_FOUND error is reported.
 */
int utc_asp_session_get_mac_n3(void)
{
	int ret = ASP_ERROR_NONE;
	char *sesion_mac = NULL;

	if(g_asp_supported == false) {
		ret = asp_session_get_mac(local_session + 1, &sesion_mac);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_mac(local_session + 1, &sesion_mac);
	assert_eq(ret, ASP_ERROR_SESSION_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_id_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Gets the session ID for an Application Service Platform session.
 * @scenario		First create the session handle & then get the  session id.
 					In clean-up function, destroy the session handle.
 *
 */
int utc_asp_session_get_id_p(void)
{
	int ret = ASP_ERROR_NONE;
	unsigned int sesion_id;
	if(g_asp_supported == false) {
		ret = asp_session_get_id(local_session, &sesion_id);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_id(local_session, &sesion_id);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_id_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_id() by passing the Null Handle.
 * @scenario		Pass the Null handle in asp_session_get_id()and
 					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_session_get_id_n1(void)
{
	int ret = ASP_ERROR_NONE;
	unsigned int sesion_id;

	if(g_asp_supported == false) {
		ret = asp_session_get_id(NULL, &sesion_id);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_id(NULL, &sesion_id);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_id_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_id() by passing the Null pointer in place of session_id
 * @scenario		Pass the Null pointer in asp_session_get_id()and
 *					Ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 					In clean-up function, destroy the session handle.
 */
int utc_asp_session_get_id_n2(void)
{
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_get_id(local_session, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_id(local_session, NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_id_n3
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_id() with invalid handle
 * @scenario		Call the asp_session_get_id()function with invalid handle
 *					and ensure ASP_ERROR_SESSION_NOT_FOUND error is reported.
 */
int utc_asp_session_get_id_n3(void)
{
	int ret = ASP_ERROR_NONE;
	unsigned int sesion_id;

	if(g_asp_supported == false) {
		ret = asp_session_get_id(local_session + 1, &sesion_id);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_id(local_session + 1, &sesion_id);
	assert_eq(ret, ASP_ERROR_SESSION_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_info_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the information for an Application Service Platform session.
 * @scenario		First create the session handle & then set the service information
 					In clean-up function, destroy the session handle.
 *
 */
int utc_asp_session_set_info_p(void)
{
	int ret = ASP_ERROR_NONE;
	char *service_info = "HDCP Enable";

	if(g_asp_supported == false) {
		ret = asp_session_set_info(local_session, service_info);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_info(local_session, service_info);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_info_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_set_info() by passing the Null session Handle.
 * @scenario		Pass the Null handle in asp_session_set_info()and
 					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_session_set_info_n1(void)
{
	int ret = ASP_ERROR_NONE;
	char *service_info = "HDCP Enable";

	if(g_asp_supported == false) {
		ret = asp_session_set_info(NULL,service_info);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_info(NULL,service_info);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_info_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_set_info() by passing the Null pointer in place of service_info
 * @scenario		Pass the Null pointer in asp_session_set_info()and
 *					Ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 					In clean-up function, destroy the session handle.
 */
int utc_asp_session_set_info_n2(void)
{
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_set_info(local_session, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_info(local_session, NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_info_n3
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_set_info() with invalid handle
 * @scenario		Call the asp_session_set_info()function with invalid handle
 *					and ensure ASP_ERROR_SESSION_NOT_FOUND error is reported.
 */
int utc_asp_session_set_info_n3(void)
{
	int ret = ASP_ERROR_NONE;
	char *service_info = "HDCP Enable";

	if(g_asp_supported == false) {
		ret = asp_session_set_info(local_session + 1, service_info);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_info(local_session + 1, service_info);
	assert_eq(ret, ASP_ERROR_SESSION_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_info_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Gets the information for an Application Service Platform session.
 * @scenario		First create the session handle & then get the service information
 					In clean-up function, destroy the session handle.
 *
 */
int utc_asp_session_get_info_p(void)
{
	int ret = ASP_ERROR_NONE;
	char *service_info = NULL;

	if(g_asp_supported == false) {
		ret = asp_session_get_info(local_session, &service_info);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_info(local_session, &service_info);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_info_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_info() by passing the Null session Handle.
 * @scenario		Pass the Null handle in asp_session_get_info()and
 					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_session_get_info_n1(void)
{
	int ret = ASP_ERROR_NONE;
	char *service_info = NULL;

	if(g_asp_supported == false) {
		ret = asp_session_get_info(NULL, &service_info);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_info(NULL, &service_info);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_info_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_info() by passing the Null pointer in place of service_info
 * @scenario		Pass the Null pointer in asp_session_get_info()and
 *					Ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 					In clean-up function, destroy the session handle.
 */
int utc_asp_session_get_info_n2(void)
{
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_get_info(local_session, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_info(local_session, NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_info_n3
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_info() with invalid handle
 * @scenario		Call the asp_session_get_info()function with invalid handle
 *					and ensure ASP_ERROR_SESSION_NOT_FOUND error is reported.
 */
int utc_asp_session_get_info_n3(void)
{
	int ret = ASP_ERROR_NONE;
	char *service_info = NULL;

	if(g_asp_supported == false) {
		ret = asp_session_get_info(local_session + 1, &service_info);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}


	ret = asp_session_get_info(local_session + 1, &service_info);
	assert_eq(ret, ASP_ERROR_SESSION_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_p2p_role_scheme_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the Wi-Fi Direct group role in session.
 * @scenario		First create the session handle & then set the network role
 					In clean-up function, destroy the session handle.
 *
 */
int utc_asp_session_set_p2p_role_scheme_p(void)
{
	int ret = ASP_ERROR_NONE;
	int network_role = 1;

	if(g_asp_supported == false) {
		ret = asp_session_set_p2p_role_scheme(local_session, network_role);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_p2p_role_scheme(local_session, network_role);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_p2p_role_scheme_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_set_p2p_role_scheme() by passing the Null session Handle.
 * @scenario		Pass the Null handle in asp_session_set_p2p_role_scheme()and
 					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_session_set_p2p_role_scheme_n1(void)
{
	int ret = ASP_ERROR_NONE;
	int network_role = 1;

	if(g_asp_supported == false) {
		ret = asp_session_set_p2p_role_scheme(NULL, network_role);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_p2p_role_scheme(NULL, network_role);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_p2p_role_scheme_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_set_p2p_role_scheme() by passing the zero in network_role.
 * @scenario		Pass the invalid value  in asp_session_set_p2p_role_scheme()and
 					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_session_set_p2p_role_scheme_n2(void)
{
	int ret = ASP_ERROR_NONE;
	int network_role = 0;

	if(g_asp_supported == false) {
		ret = asp_session_set_p2p_role_scheme(local_session, network_role);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_p2p_role_scheme(local_session, network_role);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_p2p_role_scheme_n3
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_set_p2p_role_scheme() with invalid handle
 * @scenario		Call the asp_session_set_p2p_role_scheme()function with invalid handle
 *					and ensure ASP_ERROR_SESSION_NOT_FOUND error is reported.
 */
int utc_asp_session_set_p2p_role_scheme_n3(void)
{
	int ret = ASP_ERROR_NONE;
	int network_role = 1;

	if(g_asp_supported == false) {
		ret = asp_session_set_p2p_role_scheme(local_session + 1, network_role);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_p2p_role_scheme(local_session + 1, network_role);
	assert_eq(ret, ASP_ERROR_SESSION_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_p2p_role_scheme_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Gets the Wi-Fi Direct group role in session.
 * @scenario		First create the session handle & then gets the network role
 					In clean-up function, destroy the session handle.
 *
 */
int utc_asp_session_get_p2p_role_scheme_p(void)
{
	int ret = ASP_ERROR_NONE;
	asp_advert_p2p_role_scheme_e network_role;

	if(g_asp_supported == false) {
		ret = asp_session_get_p2p_role_scheme(local_session, &network_role);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_p2p_role_scheme(local_session, &network_role);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_p2p_role_scheme_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_p2p_role_scheme() by passing the Null session Handle.
 * @scenario		Pass the Null handle in asp_session_get_p2p_role_scheme()and
 					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_session_get_p2p_role_scheme_n1(void)
{
	int ret = ASP_ERROR_NONE;
	asp_advert_p2p_role_scheme_e network_role;

	if(g_asp_supported == false) {
		ret = asp_session_get_p2p_role_scheme(NULL,&network_role);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_p2p_role_scheme(NULL,&network_role);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_p2p_role_scheme_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_p2p_role_scheme() by passing the NULL in network_role.
 * @scenario		Pass the invalid value  in asp_session_get_p2p_role_scheme()and
 					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_session_get_p2p_role_scheme_n2(void)
{
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_get_p2p_role_scheme(local_session, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_p2p_role_scheme(local_session, NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_p2p_role_scheme_n3
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_p2p_role_scheme() with invalid handle
 * @scenario		Call the asp_session_get_p2p_role_scheme()function with invalid handle
 *					and ensure ASP_ERROR_SESSION_NOT_FOUND error is reported.
 */
int utc_asp_session_get_p2p_role_scheme_n3(void)
{
	int ret = ASP_ERROR_NONE;
	asp_advert_p2p_role_scheme_e network_role;

	if(g_asp_supported == false) {
		ret = asp_session_get_p2p_role_scheme(local_session + 1, &network_role);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_p2p_role_scheme(local_session + 1, &network_role);
	assert_eq(ret, ASP_ERROR_SESSION_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_p2p_config_method_p1
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the Wi-Fi Direct group role in session.
 * @scenario		First create the session handle & then set the config value to ASP_WPS_TYPE_PIN_DISPLAY
 					In clean-up function, destroy the session handle.
 *
 */
int utc_asp_session_set_p2p_config_method_p1(void)
{
	int ret = ASP_ERROR_NONE;
	asp_wps_type_e network_config = ASP_WPS_TYPE_PIN_DISPLAY;

	if(g_asp_supported == false) {
		ret = asp_session_set_p2p_config_method(local_session, network_config);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_p2p_config_method(local_session, network_config);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_p2p_config_method_p2
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the Wi-Fi Direct group role in session.
 * @scenario		First create the session handle & then set the config value to ASP_WPS_TYPE_DEFAULT
 					In clean-up function, destroy the session handle.
 *
 */
int utc_asp_session_set_p2p_config_method_p2(void)
{
	int ret = ASP_ERROR_NONE;
	asp_wps_type_e network_config = ASP_WPS_TYPE_DEFAULT;

	if(g_asp_supported == false) {
		ret = asp_session_set_p2p_config_method(local_session, network_config);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_p2p_config_method(local_session, network_config);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_p2p_config_method_p3
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the Wi-Fi Direct group role in session.
 * @scenario		First create the session handle & then set the config value to ASP_WPS_TYPE_PIN_BOTH
 					In clean-up function, destroy the session handle.
 *
 */
int utc_asp_session_set_p2p_config_method_p3(void)
{
	int ret = ASP_ERROR_NONE;
	asp_wps_type_e network_config = ASP_WPS_TYPE_PIN_BOTH;

	if(g_asp_supported == false) {
		ret = asp_session_set_p2p_config_method(local_session, network_config);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_p2p_config_method(local_session, network_config);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_p2p_config_method_p4
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the Wi-Fi Direct group role in session.
 * @scenario		First create the session handle & then set the config value to ASP_WPS_TYPE_PIN_KEYPAD
 					In clean-up function, destroy the session handle.
 *
 */
int utc_asp_session_set_p2p_config_method_p4(void)
{
	int ret = ASP_ERROR_NONE;
	asp_wps_type_e network_config = ASP_WPS_TYPE_PIN_KEYPAD;

	if(g_asp_supported == false) {
		ret = asp_session_set_p2p_config_method(local_session, network_config);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_p2p_config_method(local_session, network_config);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}


/**
 * @testcase		utc_asp_session_set_p2p_config_method_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_set_p2p_config_method() by passing the Null session Handle.
 * @scenario		Pass the Null handle in asp_session_set_p2p_config_method()and
 					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_session_set_p2p_config_method_n1(void)
{
	int ret = ASP_ERROR_NONE;
	asp_wps_type_e network_config = ASP_WPS_TYPE_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_set_p2p_config_method(NULL, network_config);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_p2p_config_method(NULL, network_config);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_p2p_config_method_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_set_p2p_config_method() by passing the -1 in config .
 * @scenario		Pass the invalid value in asp_session_set_p2p_config_method()and
 					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_session_set_p2p_config_method_n2(void)
{
	int ret = ASP_ERROR_NONE;
	asp_wps_type_e network_config = -1;

	if(g_asp_supported == false) {
		ret = asp_session_set_p2p_config_method(local_session, network_config);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_p2p_config_method(local_session, network_config);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_p2p_config_method_n3
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify utc_asp_session_set_p2p_config_method_n3() with invalid handle
 * @scenario		Call the utc_asp_session_set_p2p_config_method_n3()function with invalid handle
 *					and ensure ASP_ERROR_SESSION_NOT_FOUND error is reported.
 */
int utc_asp_session_set_p2p_config_method_n3(void)
{
	int ret = ASP_ERROR_NONE;
	asp_wps_type_e network_config = ASP_WPS_TYPE_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_set_p2p_config_method(local_session + 1, network_config);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_p2p_config_method(local_session + 1, network_config);
	assert_eq(ret, ASP_ERROR_SESSION_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_p2p_config_method_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Gets the Preferred WSC Configuration method.
 * @scenario		First create the session handle & then gets the network role
 					In clean-up function, destroy the session handle.
 *
 */
int utc_asp_session_get_p2p_config_method_p(void)
{
	int ret = ASP_ERROR_NONE;
	asp_wps_type_e network_config;

	if(g_asp_supported == false) {
		ret = asp_session_get_p2p_config_method(local_session, &network_config);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_p2p_config_method(local_session, &network_config);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_p2p_config_method_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_p2p_config_method() by passing the Null session Handle.
 * @scenario		Pass the Null handle in asp_session_get_p2p_config_method()and
 					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_session_get_p2p_config_method_n1(void)
{
	int ret = ASP_ERROR_NONE;
	asp_wps_type_e network_config;

	if(g_asp_supported == false) {
		ret = asp_session_get_p2p_config_method(NULL,&network_config);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_p2p_config_method(NULL,&network_config);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_p2p_config_method_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_p2p_config_method() by passing the NULL in network_role.
 * @scenario		Pass the invalid value  in asp_session_get_p2p_config_method()and
 					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_session_get_p2p_config_method_n2(void)
{
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_get_p2p_config_method(local_session, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_p2p_config_method(local_session, NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_p2p_config_method_n3
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_p2p_config_method() with invalid handle
 * @scenario		Call the asp_session_get_p2p_config_method()function with invalid handle
 *					and ensure ASP_ERROR_SESSION_NOT_FOUND error is reported.
 */
int utc_asp_session_get_p2p_config_method_n3(void)
{
	int ret = ASP_ERROR_NONE;
	asp_wps_type_e network_config;

	if(g_asp_supported == false) {
		ret = asp_session_get_p2p_config_method(local_session + 1, &network_config);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_p2p_config_method(local_session + 1, &network_config);
	assert_eq(ret, ASP_ERROR_SESSION_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_close_status_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Gets the close status.
 * @scenario		First create the session handle & then gets the close status
 					In clean-up function, destroy the session handle.
 *
 */
int utc_asp_session_get_close_status_p(void)
{
	int ret = ASP_ERROR_NONE;
	int close_status;

	if(g_asp_supported == false) {
		ret = asp_session_get_close_status(local_session, &close_status);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_close_status(local_session, &close_status);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_close_status_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_close_status() by passing the Null session Handle.
 * @scenario		Pass the Null handle in asp_session_get_close_status()and
 					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_session_get_close_status_n1(void)
{
	int ret = ASP_ERROR_NONE;
	int close_status;

	if(g_asp_supported == false) {
		ret = asp_session_get_close_status(NULL, &close_status);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_close_status(NULL, &close_status);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_close_status_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_close_status() by passing the NULL in close status.
 * @scenario		Pass the invalid value  in asp_session_get_close_status()and
 					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_session_get_close_status_n2(void)
{
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_session_get_close_status(local_session, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_close_status(local_session, NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_close_status_n3
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_session_get_close_status() with invalid handle
 * @scenario		Call the asp_session_get_close_status()function with invalid handle
 *					and ensure ASP_ERROR_SESSION_NOT_FOUND error is reported.
 */
int utc_asp_session_get_close_status_n3(void)
{
	int ret = ASP_ERROR_NONE;
	int close_status;

	if(g_asp_supported == false) {
		ret = asp_session_get_close_status(local_session + 1, &close_status);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_close_status(local_session + 1, &close_status);
	assert_eq(ret, ASP_ERROR_SESSION_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_session_connect_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Connect session with NULL session
 * @scenario		Connect session with NULL session and ensure proper error is returned.
 */
int utc_asp_session_connect_n1(void)
{
	int ret = ASP_ERROR_NONE;

	if (g_asp_supported == false) {
		ret = asp_session_connect(NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_connect(NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_connect_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Connect session with invalid session
 * @scenario		Connect session with invalid session and ensure proper error is returned.
 */
int utc_asp_session_connect_n2(void)
{
	int ret = ASP_ERROR_NONE;

	if (g_asp_supported == false) {
		ret = asp_session_connect(local_session + 1);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_connect(local_session + 1);
	assert_eq(ret, ASP_ERROR_SESSION_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_session_confirm_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Confirm session with NULL session
 * @scenario		Confirm session with NULL session and ensure proper error is returned.
 */
int utc_asp_session_confirm_n1(void)
{
	int ret = ASP_ERROR_NONE;
	char *pin = "12345678";

	if (g_asp_supported == false) {
		ret = asp_session_confirm(NULL, 1, pin);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_confirm(NULL, 1, pin);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_confirm_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Confirm session with invalid session
 * @scenario		Confirm session with invalid session and ensure proper error is returned.
 */
int utc_asp_session_confirm_n2(void)
{
	int ret = ASP_ERROR_NONE;
	char *pin = "12345678";

	if (g_asp_supported == false) {
		ret = asp_session_confirm(local_session + 1, 1, pin);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_confirm(local_session + 1, 1, pin);
	assert_eq(ret, ASP_ERROR_SESSION_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_handle_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Get session ready with NULL session_mac
 * @scenario		Get session ready with NULL session_mac and ensure proper error is returned.
 */
int utc_asp_session_get_handle_n1(void)
{
	int ret = ASP_ERROR_NONE;
	int id = 0x01;

	if (g_asp_supported == false) {
		ret = asp_session_get_handle(NULL, id, &local_session);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_handle(NULL, id, &local_session);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_get_handle_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Get session ready with invalid session
 * @scenario		Get session ready with invalid session and ensure proper error is returned.
 */
int utc_asp_session_get_handle_n2(void)
{
	int ret = ASP_ERROR_NONE;
	char *session_mac = "00:11:22:00:11:22";
	int id = 0x01;

	if (g_asp_supported == false) {
		ret = asp_session_get_handle(session_mac, id, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_get_handle(session_mac, id, NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_state_ready_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Set session ready with NULL session
 * @scenario		Set session ready with NULL session and ensure proper error is returned.
 */
int utc_asp_session_set_state_ready_n1(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_set_state_ready(NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_state_ready(NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_set_state_ready_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Set session ready with invalid session
 * @scenario		Set session ready with invalid session and ensure proper error is returned.
 */
int utc_asp_session_set_state_ready_n2(void)
{
	int ret = ASP_ERROR_NONE;

	if (g_asp_supported == false) {
		ret = asp_session_set_state_ready(local_session + 1);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_set_state_ready(local_session + 1);
	assert_eq(ret, ASP_ERROR_SESSION_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_session_close_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Close session with NULL session
 * @scenario		Close session with NULL session and ensure proper error is returned.
 */
int utc_asp_session_close_n1(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_close(NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_close(NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_close_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Close session with invalid session
 * @scenario		Close session with invalid session and ensure proper error is returned.
 */
int utc_asp_session_close_n2(void)
{
	int ret = ASP_ERROR_NONE;

	if (g_asp_supported == false) {
		ret = asp_session_close(local_session + 1);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_close(local_session + 1);
	assert_eq(ret, ASP_ERROR_SESSION_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_session_bind_port_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Bound port with NULL session
 * @scenario		Bound port with NULL session and ensure proper error is returned.
 */
int utc_asp_session_bind_port_n1(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_bind_port(NULL, "192.168.0.1", 12345, 80);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_bind_port(NULL, "192.168.0.1", 12345, 80);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_bind_port_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Bound port with NULL ip address
 * @scenario		Bound port with NULL ip address and ensure proper error is returned.
 */
int utc_asp_session_bind_port_n2(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_bind_port(local_session, NULL, 12345, 80);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_bind_port(local_session, NULL, 12345, 80);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_bind_port_n3
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Bound port with invalid handle
 * @scenario		Bound port with invalid handle and ensure proper error is returned.
 */
int utc_asp_session_bind_port_n3(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_bind_port(local_session + 1, "192.168.0.1", 12345, 80);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_bind_port(local_session + 1, "192.168.0.1", 12345, 80);
	assert_eq(ret, ASP_ERROR_SESSION_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_session_release_port_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Release port with NULL session
 * @scenario		Release port with NULL session and ensure proper error is returned.
 */
int utc_asp_session_release_port_n1(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_release_port(NULL, "192.168.0.1", 12345, 80);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_release_port(NULL, "192.168.0.1", 12345, 80);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_release_port_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Release port with NULL ip address
 * @scenario		Release port with NULL ip address and ensure proper error is returned.
 */
int utc_asp_session_release_port_n2(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_release_port(local_session, NULL, 12345, 80);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_release_port(local_session, NULL, 12345, 80);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_session_release_port_n3
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Release port with invalid handle
 * @scenario		Release port with invalid handle and ensure proper error is returned.
 */
int utc_asp_session_release_port_n3(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_session_release_port(local_session + 1, "192.168.0.1", 12345, 80);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_session_release_port(local_session + 1, "192.168.0.1", 12345, 80);
	assert_eq(ret, ASP_ERROR_SESSION_NOT_FOUND);
	return 0;
}
