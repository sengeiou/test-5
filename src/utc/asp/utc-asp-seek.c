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
static asp_seek_service_h local_seek;

//& set: Asp-Seek


/**
 * @function		utc_asp_seek_startup
 * @since_tizen		4.0
 * @description		Created the Session Handle before each seek related CAPI's
 * @parameter		NA
 * @return			NA
 */
void utc_asp_seek_startup(void)
{
	char *service_type = "Display";
	system_info_get_platform_bool("http://tizen.org/feature/network.asp", &g_asp_supported);
	asp_initialize();
	asp_seek_create(service_type, &local_seek);

}

/**
 * @function		utc_asp_seek_cleanup
 * @since_tizen		4.0
 * @description		Destroy the seek Handle before each seek related CAPI's
 * @parameter		NA
 * @return			NA
 */
void utc_asp_seek_cleanup(void)
{
	asp_seek_destroy(local_seek);
	asp_deinitialize();
}

/**
 * @testcase		utc_asp_seek_add_info_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the information for a service to be sought.
 * @scenario		First create the seek handle & then add the key information
 					In clean-up function, destroy the seek handle.
 *
 */
int utc_asp_seek_add_info_p(void)
{
	int ret = ASP_ERROR_NONE;
	char *key = "hdcp=2,mode=dual";

	if(g_asp_supported == false) {
		ret = asp_seek_add_info(local_seek, key);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_add_info(local_seek, key);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/*
 * @testcase		utc_asp_seek_add_info_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_seek_add_info() by passing the Null Handle.
 * @scenario		Pass the Null handle while sets the key information and
 *					ensure ASP_ERROR_INVALID_PARAMETER error is reported
 */
int utc_asp_seek_add_info_n1(void)
{
   	int ret = ASP_ERROR_NONE;
	char *key = "<hdcp,mode>";
	if(g_asp_supported == false) {
		ret = asp_seek_add_info(NULL, key);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_add_info(NULL, key);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/*
 * @testcase		utc_asp_seek_add_info_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_seek_add_info() by passing the invalid Handle.
 * @scenario		Pass the invalid handle while sets the key information and
 *					ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported
 */
int utc_asp_seek_add_info_n2(void)
{
	int ret = ASP_ERROR_NONE;
	char *key = "<hdcp,mode>";
	if(g_asp_supported == false) {
		ret = asp_seek_add_info(local_seek + 1, key);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_add_info(local_seek + 1, key);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_seek_remove_info_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Remove the Seek Information key
 * @scenario		First create the seek handle & then remove the key information
 					In clean-up function, destroy the seek handle.
 *
 */
int utc_asp_seek_remove_info_p(void)
{
	int ret = ASP_ERROR_NONE;
	char *key = "<hdcp,mode>";

	if(g_asp_supported == false) {
		ret = asp_seek_remove_info(local_seek, key);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_remove_info(local_seek, key);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/*
 * @testcase		utc_asp_seek_remove_info_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_seek_remove_info() by passing the Null Handle.
 * @scenario		Pass the Null handle while remove the key information and
 *					ensure ASP_ERROR_INVALID_PARAMETER error is reported
 */
int utc_asp_seek_remove_info_n1(void)
{
	int ret = ASP_ERROR_NONE;
	char *key = "hdcp=2,mode=dual";
	if(g_asp_supported == false) {
		ret = asp_seek_remove_info(NULL, key);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_remove_info(NULL, key);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/*
 * @testcase		utc_asp_seek_remove_info_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_seek_remove_info() by passing the invalid Handle.
 * @scenario		Pass the invalid handle while remove the key information and
 *					ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported
 */
int utc_asp_seek_remove_info_n2(void)
{
	int ret = ASP_ERROR_NONE;
	char *key = "hdcp=2,mode=dual";
	if(g_asp_supported == false) {
		ret = asp_seek_remove_info(local_seek + 1, key);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_remove_info(local_seek + 1, key);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_seek_set_discovery_tech_p1
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the discovery mechanism for a service to be sought.
 * @scenario		First create the seek handle & then Set the P2P discovery mechanism.
 					In clean-up function, destroy the seek handle.
 *
 */
int utc_asp_seek_set_discovery_tech_p1(void)
{
	int ret = ASP_ERROR_NONE;
	int tech = ASP_DISCOVERY_TECH_P2P;
	if(g_asp_supported == false) {
		ret = asp_seek_set_discovery_tech(local_seek, tech);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_set_discovery_tech(local_seek, tech);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}


/**
 * @testcase		utc_asp_seek_set_discovery_tech_p2
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the discovery mechanism for a service to be advertised
 * @scenario		First create the seek handle & then Set the INFRA discovery mechanism.
 					In clean-up function, destroy the seek handle.
 *
 */
int utc_asp_seek_set_discovery_tech_p2(void)
{
	int ret = ASP_ERROR_NONE;
	int tech = ASP_DISCOVERY_TECH_INFRA;
	if(g_asp_supported == false) {
		ret = asp_seek_set_discovery_tech(local_seek, tech);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_set_discovery_tech(local_seek, tech);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_seek_set_discovery_tech_p3
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the discovery mechanism for a service to be advertised
 * @scenario		First create the seek handle & then Set the BLE discovery mechanism.
 					In clean-up function, destroy the seek handle.
 *
 */
int utc_asp_seek_set_discovery_tech_p3(void)
{
	int ret = ASP_ERROR_NONE;
	int tech = ASP_DISCOVERY_TECH_BLE;
	if(g_asp_supported == false) {
		ret = asp_seek_set_discovery_tech(local_seek, tech);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
	return 0;
}

ret = asp_seek_set_discovery_tech(local_seek, tech);
assert_eq(ret, ASP_ERROR_NONE);
return 0;
}

/**
 * @testcase		utc_asp_set_advertising_tech_p4
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the discovery mechanism for a service to be advertised
 * @scenario		First create the seek handle & then Set the NFC discovery mechanism.
 					In clean-up function, destroy the seek handle.
 *
 */
int utc_asp_seek_set_discovery_tech_p4(void)
{
	int ret = ASP_ERROR_NONE;
	int tech = ASP_DISCOVERY_TECH_NFC;
	if(g_asp_supported == false) {
		ret = asp_seek_set_discovery_tech(local_seek, tech);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_set_discovery_tech(local_seek, tech);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_seek_set_discovery_tech_p5
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the discovery mechanism for a service to be advertised
 * @scenario		First create the seek handle & then Set the NAN discovery mechanism.
 					In clean-up function, destroy the seek handle.
 *
 */
int utc_asp_seek_set_discovery_tech_p5(void)
{
	int ret = ASP_ERROR_NONE;
	int tech = ASP_DISCOVERY_TECH_NAN;
	if(g_asp_supported == false) {
		ret = asp_seek_set_discovery_tech(local_seek, tech);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_set_discovery_tech(local_seek, tech);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}


/**
 * @testcase		utc_asp_seek_set_discovery_tech_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_seek_set_discovery_tech() by passing the Null Handle.
 * @scenario		Pass the Null handle while sets the discovery mechanism and
 *					ensure ASP_ERROR_INVALID_PARAMETER error is reported
 */
int utc_asp_seek_set_discovery_tech_n1(void)
{
	int ret = ASP_ERROR_NONE;
	int tech = ASP_DISCOVERY_TECH_P2P;
	if(g_asp_supported == false) {
		ret = asp_seek_set_discovery_tech(NULL, tech);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_set_discovery_tech(NULL, tech);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_seek_set_discovery_tech_n2
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify asp_seek_set_discovery_tech() by passing the Invalid value of Technology.
 * @scenario		Pass the invalid value of discovery_tech while sets the discovery mechanism and ensure no unexpected behaviour.
 *					Also ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 					In clean-up function, destroy the advertised handle
 */
int utc_asp_seek_set_discovery_tech_n2(void)
{
	int ret = ASP_ERROR_NONE;
	int tech = 0;
	if(g_asp_supported == false) {
		ret = asp_seek_set_discovery_tech(local_seek, tech);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_set_discovery_tech(local_seek, tech);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_seek_set_discovery_tech_n3
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_seek_set_discovery_tech() with invalid handle
 * @scenario		Call the asp_seek_set_discovery_tech()function with invalid handle
 *					and ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported.
 */
int utc_asp_seek_set_discovery_tech_n3(void)
{
	int ret = ASP_ERROR_NONE;
	int tech = ASP_DISCOVERY_TECH_P2P;

	if(g_asp_supported == false) {
		ret = asp_seek_set_discovery_tech(local_seek + 1, tech);
	assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
	return 0;
	}

	ret = asp_seek_set_discovery_tech(local_seek + 1, tech);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_seek_set_preferred_connection_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the preferred connection for a service to be seek
 * @scenario		First create the seek handle & then Set the Preferred connection.
 					In clean-up function, destroy the seek handle.
 *
 */
int utc_asp_seek_set_preferred_connection_p(void)
{
	int ret = ASP_ERROR_NONE;
	int preferred_connection = 1;
	if(g_asp_supported == false) {
		ret = asp_seek_set_preferred_connection(local_seek, preferred_connection);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_set_preferred_connection(local_seek, preferred_connection);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_seek_set_preferred_connection_n1
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify asp_seek_set_preferred_connection() by passing the Null Handle.
 * @scenario		Pass the Null handle while sets the preferred connection and
 *					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_seek_set_preferred_connection_n1(void)
{
	int ret = ASP_ERROR_NONE;
	int preferred_connection = 1;
	if(g_asp_supported == false) {
		ret = asp_seek_set_preferred_connection(NULL, preferred_connection);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_set_preferred_connection(NULL, preferred_connection);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_seek_set_preferred_connection_n2
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Verify asp_seek_set_preferred_connection() with invalid handle
 * @scenario		Call the asp_seek_set_preferred_connection()function with invalid handle
 *					and ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported.
 */
int utc_asp_seek_set_preferred_connection_n2(void)
{
	int ret = ASP_ERROR_NONE;
	int preferred_connection = 1;
	if(g_asp_supported == false) {
		ret = asp_seek_set_preferred_connection(local_seek + 1, preferred_connection);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_set_preferred_connection(local_seek + 1, preferred_connection);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_seek_start_n1
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Seek service with NULL seek_service
 * @scenario		Seek service with NULL seek_service and
 * ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_seek_start_n1(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_seek_start(NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_start(NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_seek_start_n2
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Seek service with invalid seek_service
 * @scenario		Seek service with invalid seek_service and
 * ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported.
 */
int utc_asp_seek_start_n2(void)
{
	int ret = ASP_ERROR_NONE;

	if (g_asp_supported == false) {
		ret = asp_seek_start(local_seek + 1);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_start(local_seek + 1);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_seek_stop_n1
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Stop seeking service with NULL seek_service
 * @scenario		Stop seeking service with NULL seek_service and
 * ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_seek_stop_n1(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_seek_stop(NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_stop(NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_seek_stop_n2
 * @since_tizen 	3.0
 * @type			Negative
 * @description 	Stop seeking with invalid seek_service
 * @scenario		Stop seeking with invalid seek_service and
 * ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported.
 */
int utc_asp_seek_stop_n2(void)
{
	int ret = ASP_ERROR_NONE;

	if (g_asp_supported == false) {
		ret = asp_seek_stop(local_seek + 1);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_seek_stop(local_seek + 1);
	assert_eq(ret, ASP_ERROR_OPERATION_FAILED);
	return 0;
}
