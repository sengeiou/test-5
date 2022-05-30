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

asp_advert_service_h local_advert = NULL;

//& set: Asp-Advert

/**
 * @function		utc_asp_advertise_startup
 * @since_tizen		4.0
 * @description		Created the advertise Handle before each advertise related CAPI's
 * @parameter		NA
 * @return			NA
 */
void utc_asp_advert_startup(void)
{

	/* TODO: check instance name */
	char *instance_name = "SinkDisplay";
	system_info_get_platform_bool("http://tizen.org/feature/network.asp", &g_asp_supported);

	asp_initialize();

	asp_advert_create(instance_name, &local_advert);

}

/**
 * @function		utc_asp_advert_cleanup
 * @since_tizen		4.0
 * @description		Destroy the Advertise Handle before each session related CAPI's
 * @parameter		NA
 * @return			NA
 */
void utc_asp_advert_cleanup(void)
{

	asp_advert_destroy(local_advert);
	local_advert = NULL;
	asp_deinitialize();
}

/**
 * @testcase		utc_asp_advert_set_service_type_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	 Sets the Service type for a service to be advertised..
 * @scenario		First create the advertised handle & then Set the service type.
 					In clean-up function, destroy the advertised handle.
 *
 */
int utc_asp_advert_set_service_type_p(void)
{
   	int ret = ASP_ERROR_NONE;
	char *service_type = "Display";
	if (g_asp_supported == false) {
		ret = asp_advert_set_service_type(local_advert, service_type);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_service_type(local_advert, service_type);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_service_type_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_set_service_type() by passing the Null Handle.
 * @scenario		Pass the Null handle while sets the service type and
 *					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_advert_set_service_type_n1(void)
{
   	int ret = ASP_ERROR_NONE;
	char *service_type = "Display";
	if (g_asp_supported == false) {
		ret = asp_advert_set_service_type(NULL, service_type);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_service_type(NULL, service_type);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_service_type_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_service_type() by passing the Null pointer to service type.
 * @scenario		Pass the Null pointer  while sets the service type and
 *					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_advert_set_service_type_n2(void)
{
   	int ret = ASP_ERROR_NONE;
	char *service_type = NULL;
	if (g_asp_supported == false) {
		ret = asp_advert_set_service_type(local_advert, service_type);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_service_type(local_advert, service_type);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_service_type_n3
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_set_service_type() by passing the Invalid Handle.
 * @scenario		Pass the Invalid handle while sets the service type and
 *					ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported.
 */
int utc_asp_advert_set_service_type_n3(void)
{
   	int ret = ASP_ERROR_NONE;
	char *service_type = "Display";
	if (g_asp_supported == false) {
		ret = asp_advert_set_service_type(local_advert + 1, service_type);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_service_type(local_advert + 1, service_type);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_auto_accept_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the auto_accept for a service to be advertised.
 * @scenario		First create the advertised handle & then set the auto accept value.
 					In clean-up function, destroy the advertised handle.
 *
 */
int utc_asp_advert_set_auto_accept_p(void)
{
	int ret = ASP_ERROR_NONE;
	int auto_accept = 1	;
	if(g_asp_supported == false) {
		ret = asp_advert_set_auto_accept(local_advert, auto_accept);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_auto_accept(local_advert, auto_accept);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_auto_accept_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_auto_accept() by passing the Null Handle.
 * @scenario		Pass the Null handle while sets the auto accept value and ensure no unexpected behavior.
 *					Also ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_advert_set_auto_accept_n1(void)
{
   	int ret = ASP_ERROR_NONE;
	int auto_accept = 1	;
	if(g_asp_supported == false) {
		ret = asp_advert_set_auto_accept(NULL, auto_accept);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_auto_accept(NULL, auto_accept);
    assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_asp_advert_set_auto_accept_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_auto_accept() by passing the Invalid Handle.
 * @scenario		Pass the Invalid handle while sets the auto accept value and ensure no unexpected behavior.
 *					Also ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported.
 */
int utc_asp_advert_set_auto_accept_n2(void)
{
	int ret = ASP_ERROR_NONE;
	int auto_accept = 1	;
	if(g_asp_supported == false) {
		ret = asp_advert_set_auto_accept(local_advert + 1, auto_accept);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_auto_accept(local_advert + 1, auto_accept);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}


/**
 * @testcase		utc_asp_advert_add_info_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the information for a service to be advertised.
 * @scenario		First create the advertise handle & then add the key & value information
 					In clean-up function, destroy the advertise handle.
 *
 */
int utc_asp_advert_add_info_p(void)
{
   	int ret = ASP_ERROR_NONE;
	char *key = "<hdcp,mode>";
	char *value = "<2,dual>";
	if(g_asp_supported == false) {
		ret = asp_advert_add_info(local_advert, key, value);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_add_info(local_advert, key, value);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/*
 * @testcase		utc_asp_advert_add_info_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_add_info() by passing the Null Handle.
 * @scenario		Pass the Null handle while sets the key, value information and
 *					ensure ASP_ERROR_INVALID_PARAMETER error is reported
 */
int utc_asp_advert_add_info_n1(void)
{
   	int ret = ASP_ERROR_NONE;
	char *key = "<hdcp,mode>";
	char *value = "<2,dual>";
	if(g_asp_supported == false) {
		ret = asp_advert_add_info(NULL, key, value);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_add_info(NULL, key, value);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/*
 * @testcase		utc_asp_advert_add_info_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_add_info() by passing the invalid Handle.
 * @scenario		Pass the Null handle while sets the key, value information and
 *					ensure ASP_ERROR_INVALID_PARAMETER error is reported
 */
int utc_asp_advert_add_info_n2(void)
{
   	int ret = ASP_ERROR_NONE;
	char *key = "<hdcp,mode>";
	char *value = "<2,dual>";
	if(g_asp_supported == false) {
		ret = asp_advert_add_info(local_advert + 1, key, value);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_add_info(local_advert + 1, key, value);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_advert_get_info_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Gets the Service Advertise information.
 * @scenario		First create the advertise handle & then add the key & value information
 					In clean-up function, destroy the advertise handle.
 *
 */
int utc_asp_advert_get_info_p(void)
{
	int ret = ASP_ERROR_NONE;
	char *key = "<hdcp,mode>";
	char *value = NULL;
	int length;

	if (g_asp_supported == false) {
		ret = asp_advert_get_info(local_advert, key, &length, &value);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_add_info(local_advert, key, "<2,dual>");
	assert_eq(ret, ASP_ERROR_NONE);

	ret = asp_advert_get_info(local_advert, key, &length, &value);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/*
 * @testcase		utc_asp_advert_get_info_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_add_info() by passing the Null Handle.
 * @scenario		Pass the Null handle while get the information and
 *					ensure ASP_ERROR_INVALID_PARAMETER error is reported
 */
int utc_asp_advert_get_info_n1(void)
{
	int ret = ASP_ERROR_NONE;
	char *key = "<hdcp,mode>";
	char *value = NULL;
	int length;

	if (g_asp_supported == false) {
		ret = asp_advert_get_info(NULL, key, &length, &value);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_get_info(NULL, key, &length, &value);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/*
 * @testcase		utc_asp_advert_get_info_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_add_info() by passing the invalid Handle.
 * @scenario		Pass the invalid handle while get the information and
 *					ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported
 */
int utc_asp_advert_get_info_n2(void)
{
	int ret = ASP_ERROR_NONE;
	char *key = "<hdcp,mode>";
	char *value = NULL;
	int length;

	if (g_asp_supported == false) {
		ret = asp_advert_get_info(local_advert + 1, key, &length, &value);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_get_info(local_advert + 1, key, &length, &value);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_advert_remove_info_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Remove the advertise Information key
 * @scenario		First create the advertise handle & then remove the key information
 					In clean-up function, destroy the advertise handle.
 *
 */
int utc_asp_advert_remove_info_p(void)
{
	int ret = ASP_ERROR_NONE;
	char *key = "<hdcp,mode>";

	if(g_asp_supported == false) {
		ret = asp_advert_remove_info(local_advert, key);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_add_info(local_advert, key, "<2,dual>");
	assert_eq(ret, ASP_ERROR_NONE);

	ret = asp_advert_remove_info(local_advert, key);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/*
 * @testcase		utc_asp_advert_remove_info_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_remove_info() by passing the Null Handle.
 * @scenario		Pass the Null handle while remove the key information and
 *					ensure ASP_ERROR_INVALID_PARAMETER error is reported
 */
int utc_asp_advert_remove_info_n1(void)
{
	int ret = ASP_ERROR_NONE;
	char *key = "<hdcp,mode>";
	if(g_asp_supported == false) {
		ret = asp_advert_remove_info(NULL, key);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_remove_info(NULL, key);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/*
 * @testcase		utc_asp_advert_remove_info_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_remove_info() by passing the invalid Handle.
 * @scenario		Pass the invalid handle while remove the key information and
 *					ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported
 */
int utc_asp_advert_remove_info_n2(void)
{
	int ret = ASP_ERROR_NONE;
	char *key = "<hdcp,mode>";
	if(g_asp_supported == false) {
		ret = asp_advert_remove_info(local_advert + 1, key);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_remove_info(local_advert + 1, key);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_status_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the advertise status
 * @scenario		First create the advertise handle & then sets the advertise status
 					In clean-up function, destroy the advertise handle.
 *
 */
int utc_asp_advert_set_status_p(void)
{
	unsigned char status = 1;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_set_status(local_advert, status);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_status(local_advert, status);
	assert_eq(ret, ASP_ERROR_NONE);

	return 0;
}

/*
 * @testcase		utc_asp_advert_set_status_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_status() by passing the Null Handle.
 * @scenario		Pass the Null handle while remove the key information and
 *					ensure ASP_ERROR_INVALID_PARAMETER error is reported
 */
int utc_asp_advert_set_status_n1(void)
{
	unsigned char status = 1;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_set_status(NULL, status);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_status(NULL, status);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/*
 * @testcase		utc_asp_advert_set_status_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_status() by passing the invalid Handle.
 * @scenario		Pass the invalid handle while remove the key information and
 *					ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported
 */
int utc_asp_advert_set_status_n2(void)
{
	unsigned char status = 1;
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_set_status(local_advert + 1, status);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_status(local_advert + 1, status);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_discovery_tech_p1
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the discovery mechanism for a service to be advertised
 * @scenario		First create the advertised handle & then Set the P2P discovery mechanism.
 					In clean-up function, destroy the advertised handle.
 *
 */
int utc_asp_advert_set_discovery_tech_p1(void)
{
	int ret = ASP_ERROR_NONE;
	int tech = ASP_DISCOVERY_TECH_P2P;
	if(g_asp_supported == false) {
		ret = asp_advert_set_discovery_tech(local_advert, tech);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_discovery_tech(local_advert, tech);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}


/**
 * @testcase		utc_asp_advert_set_discovery_tech_p2
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the discovery mechanism for a service to be advertised
 * @scenario		First create the advertised handle & then Set the INFRA discovery mechanism.
 					In clean-up function, destroy the advertised handle.
 *
 */
int utc_asp_advert_set_discovery_tech_p2(void)
{
  int ret = ASP_ERROR_NONE;
	int tech = ASP_DISCOVERY_TECH_INFRA;
	if(g_asp_supported == false) {
		ret = asp_advert_set_discovery_tech(local_advert, tech);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_discovery_tech(local_advert, tech);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_discovery_tech_p3
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the discovery mechanism for a service to be advertised
 * @scenario		First create the advertised handle & then Set the BLE discovery mechanism.
 					In clean-up function, destroy the advertised handle.
 *
 */
int utc_asp_advert_set_discovery_tech_p3(void)
{
	int ret = ASP_ERROR_NONE;
	int tech = ASP_DISCOVERY_TECH_BLE;
	if(g_asp_supported == false) {
		ret = asp_advert_set_discovery_tech(local_advert, tech);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_discovery_tech(local_advert, tech);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_discovery_tech_p4
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the discovery mechanism for a service to be advertised
 * @scenario		First create the advertised handle & then Set the NFC discovery mechanism.
 					In clean-up function, destroy the advertised handle.
 *
 */
int utc_asp_advert_set_discovery_tech_p4(void)
{
	int ret = ASP_ERROR_NONE;
	int tech = ASP_DISCOVERY_TECH_NFC;
	if(g_asp_supported == false) {
		ret = asp_advert_set_discovery_tech(local_advert, tech);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_discovery_tech(local_advert, tech);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_discovery_tech_p5
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the discovery mechanism for a service to be advertised
 * @scenario		First create the advertised handle & then Set the NAN discovery mechanism.
 					In clean-up function, destroy the advertised handle.
 *
 */
int utc_asp_advert_set_discovery_tech_p5(void)
{
	int ret = ASP_ERROR_NONE;
	int tech = ASP_DISCOVERY_TECH_NAN;
	if(g_asp_supported == false) {
		ret = asp_advert_set_discovery_tech(local_advert, tech);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_discovery_tech(local_advert, tech);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}


/**
 * @testcase		utc_asp_advert_set_discovery_tech_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_discovery_tech() by passing the Null Handle.
 * @scenario		Pass the Null handle while sets the discovery mechanism and ensure no unexpected behaviour.
 *					Also ensure ASP_ERROR_INVALID_PARAMETER error is reported
 */
int utc_asp_advert_set_discovery_tech_n1(void)
{
	int ret = ASP_ERROR_NONE;
	int tech = ASP_DISCOVERY_TECH_P2P;
	if(g_asp_supported == false) {
		ret = asp_advert_set_discovery_tech(NULL, tech);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_discovery_tech(NULL, tech);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_discovery_tech_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_discovery_tech() by passing the Invalid value of Technology.
 * @scenario		Pass the invalid value of discovery_tech while sets the discovery mechanism and ensure no unexpected behaviour.
 *					Also ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 					In clean-up function, destroy the advertised handle
 */
int utc_asp_advert_set_discovery_tech_n2(void)
{
	int ret = ASP_ERROR_NONE;
	int tech = 0;
	if(g_asp_supported == false) {
		ret = asp_advert_set_discovery_tech(local_advert, tech);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_discovery_tech(local_advert, tech);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_discovery_tech_n3
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_discovery_tech() by passing the Invalid handle.
 * @scenario		Pass the invalid value of discovery_tech while sets the discovery mechanism and ensure no unexpected behavior.
 *					Also ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported.
 					In clean-up function, destroy the advertised handle
 */
int utc_asp_advert_set_discovery_tech_n3(void)
{
	int ret = ASP_ERROR_NONE;
	int tech = ASP_DISCOVERY_TECH_INFRA;
	if(g_asp_supported == false) {
		ret = asp_advert_set_discovery_tech(local_advert + 1, tech);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_discovery_tech(local_advert + 1, tech);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_preferred_connection_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the preferred connection for a service to be advertised
 * @scenario		First create the advertised handle & then Set the Preferred connection.
 					In clean-up function, destroy the advertised handle.
 *
 */
int utc_asp_advert_set_preferred_connection_p(void)
{
	int ret = ASP_ERROR_NONE;
	int preferred_connection = 1;
	if(g_asp_supported == false) {
		ret = asp_advert_set_preferred_connection(local_advert, preferred_connection);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_preferred_connection(local_advert, preferred_connection);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_preferred_connection_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_set_advertising_preferred_connection() by passing the Null Handle.
 * @scenario		Pass the Null handle while sets the preferred connection and ensure no unexpected behavior.
 *					Also ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_advert_set_preferred_connection_n1(void)
{
	int ret = ASP_ERROR_NONE;
	int preferred_connection = 1;
	if(g_asp_supported == false) {
		ret = asp_advert_set_preferred_connection(NULL, preferred_connection);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_preferred_connection(NULL, preferred_connection);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_preferred_connection_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_set_advertising_preferred_connection() by passing the invalid Handle.
 * @scenario		Pass the invalid handle while sets the preferred connection and ensure no unexpected behavior.
 *					Also ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_advert_set_preferred_connection_n2(void)
{
	int ret = ASP_ERROR_NONE;
	int preferred_connection = 1;
	if(g_asp_supported == false) {
		ret = asp_advert_set_preferred_connection(local_advert + 1, preferred_connection);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_preferred_connection(local_advert + 1, preferred_connection);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_p2p_role_scheme_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the Wi-Fi P2P role for a service to be advertised.
 * @scenario		First create the advertised handle & then Set the P2P role.
 					In clean-up function, destroy the advertised handle.
 *
 */
int utc_asp_advert_set_p2p_role_scheme_p(void)
{
	int ret = ASP_ERROR_NONE;
	unsigned char role = 0;
	if(g_asp_supported == false) {
		ret = asp_advert_set_p2p_role_scheme(local_advert, role);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_p2p_role_scheme(local_advert, role);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_p2p_role_scheme_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_p2p_role_scheme() by passing the Null Handle.
 * @scenario		Pass the Null handle while sets the P2P role and ensure no unexpected behaviour.
 *					Also ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_advert_set_p2p_role_scheme_n1(void)
{
	int ret = ASP_ERROR_NONE;
	unsigned char role = 0;
	if(g_asp_supported == false) {
		ret = asp_advert_set_p2p_role_scheme(NULL, role);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_p2p_role_scheme(NULL, role);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_p2p_role_scheme_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_p2p_role_scheme() by passing the invalid Handle.
 * @scenario		Pass the invalid handle while sets the P2P role and ensure no unexpected behaviour.
 *					Also ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_advert_set_p2p_role_scheme_n2(void)
{
	int ret = ASP_ERROR_NONE;
	unsigned char role = 0;
	if(g_asp_supported == false) {
		ret = asp_advert_set_p2p_role_scheme(local_advert + 1, role);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_p2p_role_scheme(local_advert + 1, role);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}


/**
 * @testcase		utc_asp_advert_get_p2p_role_scheme_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Gets the Wi-Fi P2P role for a service to be advertised.
 * @scenario		First create the advertised handle & then Get the P2P role.
 					In clean-up function, destroy the advertised handle.
 *
 */
int utc_asp_advert_get_p2p_role_scheme_p(void)
{
	int ret = ASP_ERROR_NONE;
	asp_advert_p2p_role_scheme_e role = 0;
	if(g_asp_supported == false) {
		ret = asp_advert_get_p2p_role_scheme(local_advert, &role);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_get_p2p_role_scheme(local_advert, &role);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_advert_get_p2p_role_scheme_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_get_p2p_role_scheme() by passing the Null Handle.
 * @scenario		Pass the Null handle while sets the P2P role and ensure no unexpected behaviour.
 *					Also ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_advert_get_p2p_role_scheme_n1(void)
{
	int ret = ASP_ERROR_NONE;
	asp_advert_p2p_role_scheme_e role = 0;
	if(g_asp_supported == false) {
		ret = asp_advert_get_p2p_role_scheme(NULL, &role);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_get_p2p_role_scheme(NULL, &role);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_get_p2p_role_scheme_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_get_p2p_role_scheme() by passing the invalid Handle.
 * @scenario		Pass the invalid handle while sets the P2P role and ensure no unexpected behaviour.
 *					Also ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_advert_get_p2p_role_scheme_n2(void)
{
	int ret = ASP_ERROR_NONE;
	asp_advert_p2p_role_scheme_e role = 0;
	if(g_asp_supported == false) {
		ret = asp_advert_get_p2p_role_scheme(local_advert + 1, &role);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_get_p2p_role_scheme(local_advert + 1, &role);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_p2p_config_method_p1
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the p2p configuration method for a service to be advertised.
 * @scenario		First create the advertised handle & then Set the P2P Config method to NONE
 					In clean-up function, destroy the advertised handle.
 *
 */
int utc_asp_advert_set_p2p_config_method_p1(void)
{
	int ret = ASP_ERROR_NONE;
	unsigned int config_method = ASP_WPS_TYPE_NONE;
	if(g_asp_supported == false) {
		ret = asp_advert_set_p2p_config_method(local_advert, config_method);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_p2p_config_method(local_advert, config_method);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_p2p_config_method_p2
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the p2p configuration method for a service to be advertised.
 * @scenario		First create the advertised handle & then Set the P2P Config method to Default
 					In clean-up function, destroy the advertised handle.
 *
 */
int utc_asp_advert_set_p2p_config_method_p2(void)
{
	int ret = ASP_ERROR_NONE;
	unsigned int config_method = ASP_WPS_TYPE_DEFAULT;
	if(g_asp_supported == false) {
		ret = asp_advert_set_p2p_config_method(local_advert, config_method);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_p2p_config_method(local_advert, config_method);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_p2p_config_method_p3
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the p2p configuration method for a service to be advertised.
 * @scenario		First create the advertised handle & then Set the P2P Config method to
 					both display and keypad.In clean-up function, destroy the advertised handle.
 *
 */
int utc_asp_advert_set_p2p_config_method_p3(void)
{
	int ret = ASP_ERROR_NONE;
	unsigned int config_method = ASP_WPS_TYPE_PIN_BOTH;
	if(g_asp_supported == false) {
		ret = asp_advert_set_p2p_config_method(local_advert, config_method);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_p2p_config_method(local_advert, config_method);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_p2p_config_method_p4
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the p2p configuration method for a service to be advertised.
 * @scenario		First create the advertised handle & then Set the P2P Config method to display.
 					In clean-up function, destroy the advertised handle.
 *
 */
int utc_asp_advert_set_p2p_config_method_p4(void)
{
	int ret = ASP_ERROR_NONE;
	unsigned int config_method = ASP_WPS_TYPE_PIN_DISPLAY;
	if(g_asp_supported == false) {
		ret = asp_advert_set_p2p_config_method(local_advert, config_method);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_p2p_config_method(local_advert, config_method);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_p2p_config_method_p5
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the p2p configuration method for a service to be advertised.
 * @scenario		First create the advertised handle & then Set the P2P Config method to keypad.
 					In clean-up function, destroy the advertised handle.
 *
 */
int utc_asp_advert_set_p2p_config_method_p5(void)
{
	int ret = ASP_ERROR_NONE;
	unsigned int config_method = ASP_WPS_TYPE_PIN_KEYPAD;
	if(g_asp_supported == false) {
		ret = asp_advert_set_p2p_config_method(local_advert, config_method);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_p2p_config_method(local_advert, config_method);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_p2p_config_method_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_p2p_config_method() by passing the Null Handle.
 * @scenario		Pass the Null handle while sets the P2P Config method and ensure no unexpected behaviour.
 *					Also ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_advert_set_p2p_config_method_n1(void)
{
   	int ret = ASP_ERROR_NONE;
	unsigned int config_method = ASP_WPS_TYPE_NONE;
	if(g_asp_supported == false) {
		ret = asp_advert_set_p2p_config_method(NULL, config_method);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_p2p_config_method(NULL, config_method);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_p2p_config_method_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_p2p_config_method() by passing the invalid value of config method.
 * @scenario		Pass the invalid value of config method & Sets the P2P Config method.
 *					Ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 					In clean-up function, destroy the advertised handle.
 */
int utc_asp_advert_set_p2p_config_method_n2(void)
{
   	int ret = ASP_ERROR_NONE;
	unsigned int config_method = 10;
	if(g_asp_supported == false) {
		ret = asp_advert_set_p2p_config_method(local_advert, config_method);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_p2p_config_method(local_advert, config_method);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_p2p_config_method_n3
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_p2p_config_method() by passing the invalid handle.
 * @scenario		Pass the invalid handle & Sets the P2P Config method.
 *					Ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported.
 					In clean-up function, destroy the advertised handle.
 */
int utc_asp_advert_set_p2p_config_method_n3(void)
{
	int ret = ASP_ERROR_NONE;
	unsigned int config_method = ASP_WPS_TYPE_NONE;
	if(g_asp_supported == false) {
		ret = asp_advert_set_p2p_config_method(local_advert + 1, config_method);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_p2p_config_method(local_advert + 1, config_method);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}


/**
 * @testcase		utc_asp_advert_get_p2p_config_method_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Gets the p2p configuration method for a service to be advertised.
 * @scenario		First create the advertised handle & then Get the P2P Config method.
 					In clean-up function, destroy the advertised handle.
 *
 */
int utc_asp_advert_get_p2p_config_method_p(void)
{
	int ret = ASP_ERROR_NONE;
	unsigned int config_method = ASP_WPS_TYPE_PIN_KEYPAD;
	if(g_asp_supported == false) {
		ret = asp_advert_get_p2p_config_method(local_advert, &config_method);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_get_p2p_config_method(local_advert, &config_method);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_advert_get_p2p_config_method_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_get_p2p_config_method() by passing the Null Handle.
 * @scenario		Pass the Null handle while gets the P2P Config method and ensure no unexpected behaviour.
 *					Also ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_advert_get_p2p_config_method_n1(void)
{
   	int ret = ASP_ERROR_NONE;
	unsigned int config_method = ASP_WPS_TYPE_NONE;
	if(g_asp_supported == false) {
		ret = asp_advert_get_p2p_config_method(NULL, &config_method);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_get_p2p_config_method(NULL, &config_method);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_get_p2p_config_method_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_get_p2p_config_method() by passing the invalid value of config method.
 * @scenario		Pass the invalid value of config method & Gets the P2P Config method.
 *					Ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 					In clean-up function, destroy the advertised handle.
 */
int utc_asp_advert_get_p2p_config_method_n2(void)
{
	int ret = ASP_ERROR_NONE;

	if(g_asp_supported == false) {
		ret = asp_advert_get_p2p_config_method(local_advert, NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_get_p2p_config_method(local_advert, NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_get_p2p_config_method_n3
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_get_p2p_config_method() by passing the invalid handle.
 * @scenario		Pass the invalid handle & Gets the P2P Config method.
 *					Ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported.
 					In clean-up function, destroy the advertised handle.
 */
int utc_asp_advert_get_p2p_config_method_n3(void)
{
	int ret = ASP_ERROR_NONE;
	unsigned int config_method = ASP_WPS_TYPE_NONE;
	if(g_asp_supported == false) {
		ret = asp_advert_get_p2p_config_method(local_advert + 1, &config_method);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_get_p2p_config_method(local_advert + 1, &config_method);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_p2p_response_p
 * @since_tizen 	4.0
 * @type			Positive
 * @description 	Sets the service response for an advertised service.
 * @scenario		First create the advertised handle & then Set the service response.
 					In clean-up function, destroy the advertised handle.
 *
 */
int utc_asp_advert_set_p2p_response_p(void)
{
	int ret = ASP_ERROR_NONE;
	char *service_rsp = "displayservice";
	int length = strlen(service_rsp);

	if(g_asp_supported == false) {
		ret = asp_advert_set_p2p_response(local_advert, service_rsp, length);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_p2p_response(local_advert, service_rsp, length);
	assert_eq(ret, ASP_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_p2p_response_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_set_advertising_preferred_connection() by passing the Null Handle.
 * @scenario		Pass the Null handle while sets the service response and
 *					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_advert_set_p2p_response_n1(void)
{
	int ret = ASP_ERROR_NONE;
	char *service_rsp = "displayservice";
	int length = strlen(service_rsp);
	if(g_asp_supported == false) {
		ret = asp_advert_set_p2p_response(NULL, service_rsp, length);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_p2p_response(NULL, service_rsp, length);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_p2p_response_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_p2p_response() by passing the Null value of service response.
 * @scenario		Pass the NULL value inside service response while sets the service response and
 *					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_advert_set_p2p_response_n2(void)
{
   	int ret = ASP_ERROR_NONE;
	char *service_rsp = NULL;
	int length = 10;
	if(g_asp_supported == false) {
		ret = asp_advert_set_p2p_response(local_advert, service_rsp, length);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_p2p_response(local_advert, service_rsp, length);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_p2p_response_n3
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_p2p_response() by passing the invalid length.
 * @scenario		Pass the invalid value while sets the service response and
 *					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_advert_set_p2p_response_n3(void)
{
	int ret = ASP_ERROR_NONE;
	char *service_rsp = "displayservice";
	int length = 1000;
	if(g_asp_supported == false) {
		ret = asp_advert_set_p2p_response(local_advert, service_rsp, length);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_p2p_response(local_advert, service_rsp, length);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_set_p2p_response_n4
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Verify asp_advert_set_p2p_response() by passing the invalid handle.
 * @scenario		Pass the invalid handle while sets the service response and
 *					ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported.
 */
int utc_asp_advert_set_p2p_response_n4(void)
{
   	int ret = ASP_ERROR_NONE;
	char *service_rsp = "displayservice";
	int length = 10;
	if(g_asp_supported == false) {
		ret = asp_advert_set_p2p_response(local_advert + 1, service_rsp, length);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_set_p2p_response(local_advert + 1, service_rsp, length);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_advert_start_advertising_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Advertise service with NULL adv_service
 * @scenario		Advertise service with NULL adv_service and
 *					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_advert_start_advertising_n1(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_advert_start_advertising(NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_start_advertising(NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_start_advertising_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Advertise service with invalid adv_service
 * @scenario		Advertise service with invalid adv service and
 *					ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported.
 */
int utc_asp_advert_start_advertising_n2(void)
{
	int ret = ASP_ERROR_NONE;

	if (g_asp_supported == false) {
		ret = asp_advert_start_advertising(local_advert + 1);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_start_advertising(local_advert + 1);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_advert_stop_advertising_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Cancel advertise service with NULL adv_service
 * @scenario		Cancel advertise service with NULL adv_service and
 *					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_advert_stop_advertising_n1(void)
{
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_advert_stop_advertising(NULL);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_stop_advertising(NULL);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_stop_advertising_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Cancel advertise service with invalid adv_service
 * @scenario		Cancel advertise service with invalid adv service and
 *					ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported.
 */
int utc_asp_advert_stop_advertising_n2(void)
{
	int ret = ASP_ERROR_NONE;

	if (g_asp_supported == false) {
		ret = asp_advert_stop_advertising(local_advert + 1);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_stop_advertising(local_advert + 1);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_asp_advert_change_service_status_n1
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Change service status with NULL adv_service
 * @scenario		Change service status with NULL adv_service and
 *					ensure ASP_ERROR_INVALID_PARAMETER error is reported.
 */
int utc_asp_advert_change_service_status_n1(void)
{
	unsigned char status = 0;
	int ret = ASP_ERROR_NONE;
	if (g_asp_supported == false) {
		ret = asp_advert_change_service_status(NULL, status);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_change_service_status(NULL, status);
	assert_eq(ret, ASP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_asp_advert_change_service_status_n2
 * @since_tizen 	4.0
 * @type			Negative
 * @description 	Change service status with invalid adv_service
 * @scenario		Change service status with invalid adv service and
 *					ensure ASP_ERROR_SERVICE_NOT_FOUND error is reported.
 */
int utc_asp_advert_change_service_status_n2(void)
{
	unsigned char status = 0;
	int ret = ASP_ERROR_NONE;

	if (g_asp_supported == false) {
		ret = asp_advert_change_service_status(local_advert + 1, status);
		assert_eq(ret, ASP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = asp_advert_change_service_status(local_advert + 1, status);
	assert_eq(ret, ASP_ERROR_SERVICE_NOT_FOUND);
	return 0;
}
