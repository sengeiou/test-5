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
#include "utc-connection-common.h"

//& set: ConnectionProfile

static void test_profile_state_changed_cb(connection_profile_state_e state, void* user_data)
{
	char *profile_name;
	connection_profile_h profile = user_data;

	QUIT_GMAIN_LOOP;

	if (profile == NULL)
		return;

	int ret = connection_profile_get_name(profile, &profile_name);
	PRINT_RETURN("connection_profile_get_name", ret);
	if (ret != CONNECTION_ERROR_NONE) {
		FREE_RESOURCE(profile_name);
		return;
	}

	FREE_RESOURCE(profile_name);
}

/**
 * @function		utc_connection_profile_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_connection_profile_startup(void)
{
	wifi_supported = connection_check_feature_supported(FEATURE_WIFI);
	telephony_supported = connection_check_feature_supported(FEATURE_TELEPHONY);
	bt_tethering_supported = connection_check_feature_supported(FEATURE_BT_TETHERING);
	ethernet_supported = connection_check_feature_supported(FEATURE_ETHERNET);

	if (telephony_supported == false && wifi_supported == false
			&& bt_tethering_supported == false && ethernet_supported == false) {
		all_features_not_supported = true;
		FPRINTF("[%s:%d] all feature is not supported\\n", __FILE__, __LINE__);
		return ;
	}

	int ret = connection_create(&connection);
	PRINT_RETURN("connection_create", ret);

	if (ret != CONNECTION_ERROR_NONE)
		return;

	if (telephony_supported) {
		if (!profile_cellular) {
			ret = connection_profile_create(CONNECTION_PROFILE_TYPE_CELLULAR, "Net", &profile_cellular);
			PRINT_RETURN("connection_profile_create", ret);
		}
	}

	if (wifi_supported) {
		if (!profile_wifi) {
			ret = connection_profile_create(CONNECTION_PROFILE_TYPE_WIFI, NULL, &profile_wifi);
			PRINT_RETURN("connection_profile_create", ret);
		}
	}
}

/**
 * @function		utc_connection_profile_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_connection_profile_cleanup(void)
{
	int ret;

	if (profile_cellular) {
		ret = connection_profile_destroy(profile_cellular);
		PRINT_RETURN("connection_profile_destroy", ret);
		if (ret == CONNECTION_ERROR_NONE)
			profile_cellular = NULL;
	}

	if (profile_wifi) {
		ret = connection_profile_destroy(profile_wifi);
		PRINT_RETURN("connection_profile_destroy", ret);
		if (ret == CONNECTION_ERROR_NONE)
			profile_wifi = NULL;
	}

	if (profile_temp) {
		ret = connection_profile_destroy(profile_temp);
		PRINT_RETURN("connection_profile_destroy", ret);
		if (ret == CONNECTION_ERROR_NONE)
			profile_temp = NULL;
	}

	if (connection) {
		ret = connection_destroy(connection);
		PRINT_RETURN("connection_destroy", ret);
		if (ret == CONNECTION_ERROR_NONE)
			connection = NULL;
	}
}

/* Common profile operations. */

/**
 * @testcase		utc_connection_profile_create_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Creates a profile handle.
 * @scenario  		Invoking connection_profile_create with valid parameter.
 */
int utc_connection_profile_create_p(void)
{
	int ret;

	if (profile_cellular) {
		ret = connection_profile_destroy(profile_cellular);
		PRINT_RETURN("connection_profile_destroy", ret);
		profile_cellular = NULL;
	}

	if (telephony_supported) {
		ret = connection_profile_create(CONNECTION_PROFILE_TYPE_CELLULAR, "Net", &profile_cellular);
		CHECK_RETURN("connection_profile_create", ret, CONNECTION_ERROR_NONE);
	} else {
		ret = connection_profile_create(CONNECTION_PROFILE_TYPE_CELLULAR, "Net", &profile_cellular);
		CHECK_RETURN("connection_profile_create", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_create_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		should not creates a profile handle.
 * @scenario  		Verify connection_profile_create by passing invalid parameter.
 */
int utc_connection_profile_create_n(void)
{
	int ret;
	connection_profile_h profile_temp = NULL;

	if (telephony_supported == false && wifi_supported == false) {
		ret = connection_profile_create(CONNECTION_PROFILE_TYPE_CELLULAR, "Net", NULL);
		CHECK_RETURN("connection_profile_create", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (telephony_supported) {
		ret = connection_profile_create(-1, "Net", &profile_temp);
		CHECK_RETURN("connection_profile_create", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_create(CONNECTION_PROFILE_TYPE_CELLULAR, NULL, &profile_temp);
		CHECK_RETURN("connection_profile_create", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_create(CONNECTION_PROFILE_TYPE_CELLULAR, "Net", NULL);
		CHECK_RETURN("connection_profile_create", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		ret = connection_profile_create(CONNECTION_PROFILE_TYPE_CELLULAR, "Net", NULL);
		CHECK_RETURN("connection_profile_create", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_clone_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Clones a profile handle.
 * @scenario  		Verify connection_profile_clone with valid parameter and destroy it.
 */
int utc_connection_profile_clone_p(void)
{
	connection_profile_h profile_temp = NULL;
	int ret = 0;
	connection_profile_h profile_to_be_cloned = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_clone(&profile_temp, profile_to_be_cloned);
		CHECK_RETURN("connection_profile_clone", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	test_get_any_profile(&profile_to_be_cloned);
	if (profile_to_be_cloned != NULL) {
		ret = connection_profile_clone(&profile_temp, profile_to_be_cloned);
		CHECK_RETURN("connection_profile_clone", ret, CONNECTION_ERROR_NONE);

		ret = connection_profile_destroy(profile_to_be_cloned);
		PRINT_RETURN("connection_profile_destroy", ret);
		ret = connection_profile_destroy(profile_temp);
		PRINT_RETURN("connection_profile_destroy", ret);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_clone_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		should not Clones a profile handle.
 * @scenario  		Verify connection_profile_clone by passing invalid parameters.
 */
int utc_connection_profile_clone_n(void)
{
	int ret;
	connection_profile_h profile_temp = NULL;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_clone(NULL, profile_inval);
		CHECK_RETURN("connection_profile_clone", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_clone(NULL, profile_inval);
	CHECK_RETURN("connection_profile_clone", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_clone(NULL, profile_cellular);
	CHECK_RETURN("connection_profile_clone", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_clone(&profile_temp, profile_inval);
	CHECK_RETURN("connection_profile_clone", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_name_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the profile name.
 * @scenario  		Get the profile name by invoking connection_profile_get_name with a valid parameter.
 */
int utc_connection_profile_get_name_p(void)
{
	int ret;
	char *name = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_get_name(profile_temp, &name);
		FREE_RESOURCE(name);
		CHECK_RETURN("connection_profile_get_name", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	test_get_any_profile(&profile_temp);
	assert(profile_temp);

	ret = connection_profile_get_name(profile_temp, &name);
	FREE_RESOURCE(name);
	CHECK_RETURN("connection_profile_get_name", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_name_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		should not return profile handle.
 * @scenario  		Verify connection_profile_get_name by passing invalid profile handle.
 */
int utc_connection_profile_get_name_n(void)
{
	int ret;
	char *name = NULL;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_get_name(profile_inval, NULL);
		FREE_RESOURCE(name);
		CHECK_RETURN("connection_profile_get_name", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_get_name(profile_inval, NULL);
	CHECK_RETURN("connection_profile_get_name", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_name(profile_inval, &name);
	FREE_RESOURCE(name);
	CHECK_RETURN("connection_profile_get_name", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_name(profile_cellular, NULL);
	CHECK_RETURN("connection_profile_get_name", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_id_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the profile ID.
 * @scenario  		Invoking connection_profile_get_id with valid profile handle.
 */
int utc_connection_profile_get_id_p(void)
{
	char *id = NULL;
	connection_profile_h profile_h = NULL;
	int ret = test_get_any_profile(&profile_h);

	if (all_features_not_supported) {
		ret = connection_profile_get_id(profile_temp, &id);
		FREE_RESOURCE(id);
		CHECK_RETURN("connection_profile_get_id", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	profile_temp = profile_h;
	assert(profile_temp);

	ret = connection_profile_get_id(profile_temp, &id);
	FREE_RESOURCE(id);
	CHECK_RETURN("connection_profile_get_id", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_id_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		should not return profile ID.
 * @scenario  		Verify connection_profile_get_id by passing invalid parameter..
 */
int utc_connection_profile_get_id_n(void)
{
	int ret;
    char *id = NULL;
    connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_get_id(profile_inval, NULL);
	    CHECK_RETURN("connection_profile_get_id", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = connection_profile_get_id(profile_inval, NULL);
    CHECK_RETURN("connection_profile_get_id", ret, CONNECTION_ERROR_INVALID_PARAMETER);
    ret = connection_profile_get_id(profile_inval, &id);
    CHECK_RETURN("connection_profile_get_id", ret, CONNECTION_ERROR_INVALID_PARAMETER);
    ret = connection_profile_get_id(profile_cellular, NULL);
    CHECK_RETURN("connection_profile_get_id", ret, CONNECTION_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase		utc_connection_profile_get_type_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the network type.
 * @scenario  		connection_profile_get_type should return profile type.
 */
int utc_connection_profile_get_type_p(void)
{
	connection_profile_type_e type;
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_get_type(profile_temp, &type);
		CHECK_RETURN("connection_profile_get_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_get_type(profile_temp, &type);
	CHECK_RETURN("connection_profile_get_type", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_type_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		should not get the network type.
 * @scenario  		Verify connection_profile_get_type by passing invalid parameter.
 */
int utc_connection_profile_get_type_n(void)
{
	int ret;
	connection_profile_type_e type;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_get_type(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_get_type(profile_inval, NULL);
	CHECK_RETURN("connection_profile_get_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_type(profile_inval, &type);
	CHECK_RETURN("connection_profile_get_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_type(profile_cellular, NULL);
	CHECK_RETURN("connection_profile_get_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_network_interface_name_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the name of the network interface, e.g. eth0 and pdp0.
 * @scenario  		Invoking connection_profile_get_network_interface_name with valid parameter.
 */
int utc_connection_profile_get_network_interface_name_p(void)
{
	char *name = NULL;
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_get_network_interface_name(profile_temp, &name);
		FREE_RESOURCE(name);
		CHECK_RETURN("connection_profile_get_network_interface_name", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_get_network_interface_name(profile_temp, &name);
	FREE_RESOURCE(name);
	CHECK_RETURN("connection_profile_get_network_interface_name", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_network_interface_name_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		should not get the name of the network interface.
 * @scenario  		Verify connection_profile_get_network_interface_name by passing invalid parameter.
 */
int utc_connection_profile_get_network_interface_name_n(void)
{
	int ret;
	char *name = NULL;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_get_network_interface_name(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_network_interface_name", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_get_network_interface_name(profile_inval, NULL);
	CHECK_RETURN("connection_profile_get_network_interface_name", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_network_interface_name(profile_inval, &name);
	CHECK_RETURN("connection_profile_get_network_interface_name", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_network_interface_name(profile_cellular, NULL);
	CHECK_RETURN("connection_profile_get_network_interface_name", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_state_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the network type and the state of the profile.
 * @scenario  		Verify connection_profile_get_state with valid parameter.
 */
int utc_connection_profile_get_state_p(void)
{
	connection_profile_state_e state;
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_get_state(profile_temp, &state);
		CHECK_RETURN("connection_profile_get_state", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_get_state(profile_temp, &state);
	CHECK_RETURN("connection_profile_get_state", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_state_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		should not get the state of the profile.
 * @scenario  		Verify connection_profile_get_state by passing invalid parameter.
 */
int utc_connection_profile_get_state_n(void)
{
	int ret;
	connection_profile_state_e state;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_get_state(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_state", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_get_state(profile_inval, NULL);
	CHECK_RETURN("connection_profile_get_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_state(profile_inval, &state);
	CHECK_RETURN("connection_profile_get_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_state(profile_cellular, NULL);
	CHECK_RETURN("connection_profile_get_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_ip_config_type_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the IP config type.Should return the type of the IP config.
 * @scenario  		Invoking connection_profile_get_ip_config_type with valid parameter.
 */
int utc_connection_profile_get_ip_config_type_p(void)
{
	connection_ip_config_type_e type;
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_get_ip_config_type(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, &type);
		CHECK_RETURN("connection_profile_get_ip_config_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_get_ip_config_type(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, &type);
	CHECK_RETURN("connection_profile_get_ip_config_type", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_ip_config_type_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		should not return the type of the IP config.
 * @scenario  		Verify connection_profile_get_ip_config_type by passing invalid parameter..
 */
int utc_connection_profile_get_ip_config_type_n(void)
{
	int ret;
	connection_ip_config_type_e type;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_get_ip_config_type(profile_inval, -1, NULL);
		CHECK_RETURN("connection_profile_get_ip_config_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_get_ip_config_type(profile_inval, -1, NULL);
	CHECK_RETURN("connection_profile_get_ip_config_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_ip_config_type(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, &type);
	CHECK_RETURN("connection_profile_get_ip_config_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_ip_config_type(profile_cellular, -1, &type);
	CHECK_RETURN("connection_profile_get_ip_config_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_ip_config_type(profile_cellular, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_profile_get_ip_config_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_ip_config_type(profile_inval, -1, &type);
	CHECK_RETURN("connection_profile_get_ip_config_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_ip_config_type(profile_cellular, -1, NULL);
	CHECK_RETURN("connection_profile_get_ip_config_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_ip_address_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the IP address.Shoudl return IP Address.
 * @scenario  		Invoking connection_profile_get_ip_address with valid parameter.
 */
int utc_connection_profile_get_ip_address_p(void)
{
	char *ip_addr = NULL;
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_get_ip_address(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_addr);
		FREE_RESOURCE(ip_addr);
		CHECK_RETURN("connection_profile_get_ip_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_get_ip_address(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_RESOURCE(ip_addr);
	CHECK_RETURN("connection_profile_get_ip_address", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_ip_address_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		should not return IP Address.
 * @scenario  		Verify connection_profile_get_ip_address by passing invalid parameter.
 */
int utc_connection_profile_get_ip_address_n(void)
{
	int ret;
	char *ip_addr = NULL;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_get_ip_address(profile_inval, -1, NULL);
		CHECK_RETURN("connection_profile_get_ip_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_get_ip_address(profile_inval, -1, NULL);
	CHECK_RETURN("connection_profile_get_ip_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_ip_address(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_addr);
	CHECK_RETURN("connection_profile_get_ip_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_ip_address(profile_cellular, -1, &ip_addr);
	CHECK_RETURN("connection_profile_get_ip_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_ip_address(profile_cellular, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_profile_get_ip_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_ip_address(profile_inval, -1, &ip_addr);
	CHECK_RETURN("connection_profile_get_ip_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_ip_address(profile_cellular, -1, NULL);
	CHECK_RETURN("connection_profile_get_ip_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_subnet_mask_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the Subnet Mask.
 * @scenario  		Invoking connection_profile_get_subnet_mask with valid parameter.
 */
int utc_connection_profile_get_subnet_mask_p(void)
{
	char *ip_addr = NULL;
	int ret = test_get_any_profile(&profile_temp);

	if(all_features_not_supported){
		ret = connection_profile_get_subnet_mask(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_addr);
		FREE_RESOURCE(ip_addr);
		CHECK_RETURN("connection_profile_get_subnet_mask", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_get_subnet_mask(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_RESOURCE(ip_addr);
	CHECK_RETURN("connection_profile_get_subnet_mask", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_subnet_mask_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		should not return any subnet mask.
 * @scenario  		Verify connection_profile_get_subnet_mask by passing invalid parameter.
 */
int utc_connection_profile_get_subnet_mask_n(void)
{
	int ret;
	char *ip_addr = NULL;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_get_subnet_mask(profile_inval, -1, NULL);
		CHECK_RETURN("connection_profile_get_subnet_mask", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_get_subnet_mask(profile_inval, -1, NULL);
	CHECK_RETURN("connection_profile_get_subnet_mask", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_subnet_mask(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_addr);
	CHECK_RETURN("connection_profile_get_subnet_mask", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_subnet_mask(profile_cellular, -1, &ip_addr);
	CHECK_RETURN("connection_profile_get_subnet_mask", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_subnet_mask(profile_cellular, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_profile_get_subnet_mask", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_subnet_mask(profile_inval, -1, &ip_addr);
	CHECK_RETURN("connection_profile_get_subnet_mask", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_subnet_mask(profile_cellular, -1, NULL);
	CHECK_RETURN("connection_profile_get_subnet_mask", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_gateway_address_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the Gateway address.
 * @scenario  		Invoking connection_profile_get_gateway_address with valid parameter.
 */
int utc_connection_profile_get_gateway_address_p(void)
{
	char *ip_addr = NULL;
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_get_gateway_address(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_addr);
		FREE_RESOURCE(ip_addr);
		CHECK_RETURN("connection_profile_get_gateway_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_get_gateway_address(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_RESOURCE(ip_addr);
	CHECK_RETURN("connection_profile_get_gateway_address", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_gateway_address_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_get_gateway_address should fail with invalid parameter.
 * @scenario  		Verify connection_profile_get_gateway_address by passing invalid parameter.
 */
int utc_connection_profile_get_gateway_address_n(void)
{
	int ret;
	char *ip_addr = NULL;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_get_gateway_address(profile_inval, -1, NULL);
		CHECK_RETURN("connection_profile_get_gateway_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_get_gateway_address(profile_inval, -1, NULL);
	CHECK_RETURN("connection_profile_get_gateway_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_gateway_address(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_addr);
	CHECK_RETURN("connection_profile_get_gateway_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_gateway_address(profile_cellular, -1, &ip_addr);
	CHECK_RETURN("connection_profile_get_gateway_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_gateway_address(profile_cellular, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_profile_get_gateway_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_gateway_address(profile_inval, -1, &ip_addr);
	CHECK_RETURN("connection_profile_get_gateway_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_gateway_address(profile_cellular, -1, NULL);
	CHECK_RETURN("connection_profile_get_gateway_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_connection_profile_get_dhcp_server_address_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     Gets the DHCP server address.
 * @scenario        Invoking connection_profile_get_dhcp_server_address with valid parameter.
 */
int utc_connection_profile_get_dhcp_server_address_p(void)
{
	char *ip_addr = NULL;
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_get_dhcp_server_address(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_addr);
		FREE_RESOURCE(ip_addr);
		CHECK_RETURN("connection_profile_get_dhcp_server_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_get_dhcp_server_address(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_RESOURCE(ip_addr);
	CHECK_RETURN("connection_profile_get_dhcp_server_address", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_connection_profile_get_gateway_address_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     connection_profile_get_dhcp_server_address should fail with invalid parameter.
 * @scenario        Verify connection_profile_get_dhcp_server_address by passing invalid parameter.
 */
int utc_connection_profile_get_dhcp_server_address_n(void)
{
	int ret;
	char *ip_addr = NULL;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_get_dhcp_server_address(profile_inval, -1, NULL);
		CHECK_RETURN("connection_profile_get_dhcp_server_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_get_dhcp_server_address(profile_inval, -1, NULL);
	CHECK_RETURN("connection_profile_get_dhcp_server_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_dhcp_server_address(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_addr);
	CHECK_RETURN("connection_profile_get_dhcp_server_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_dhcp_server_address(profile_cellular, -1, &ip_addr);
	CHECK_RETURN("connection_profile_get_dhcp_server_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_dhcp_server_address(profile_cellular, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_profile_get_dhcp_server_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_dhcp_server_address(profile_inval, -1, &ip_addr);
	CHECK_RETURN("connection_profile_get_dhcp_server_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_dhcp_server_address(profile_cellular, -1, NULL);
	CHECK_RETURN("connection_profile_get_dhcp_server_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_connection_profile_get_dhcp_lease_duration_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     Gets the DHCP lease duration.
 * @scenario        Invoking connection_profile_get_dhcp_lease_duration with valid parameter.
 */
int utc_connection_profile_get_dhcp_lease_duration_p(void)
{
	int dhcp_lease_duration = 0;
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_get_dhcp_lease_duration(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, &dhcp_lease_duration);
		CHECK_RETURN("connection_profile_get_dhcp_lease_duration", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_get_dhcp_lease_duration(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, &dhcp_lease_duration);
	CHECK_RETURN("connection_profile_get_dhcp_lease_duration", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_connection_profile_get_dhcp_lease_duration_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     connection_profile_get_dhcp_lease_duration should fail with invalid parameter.
 * @scenario        Verify connection_profile_get_dhcp_lease_duration by passing invalid parameter.
 */
int utc_connection_profile_get_dhcp_lease_duration_n(void)
{
	int ret;
	int dhcp_lease_duration = 0;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_get_dhcp_lease_duration(profile_inval, -1, NULL);
		CHECK_RETURN("connection_profile_get_dhcp_lease_duration", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		ret = connection_profile_get_dhcp_lease_duration(profile_wifi, CONNECTION_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED, &dhcp_lease_duration);
		CHECK_RETURN("connection_profile_get_dhcp_lease_duration", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_get_dhcp_server_address(profile_inval, -1, NULL);
	CHECK_RETURN("connection_profile_get_dhcp_lease_duration", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_dhcp_server_address(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, &dhcp_lease_duration);
	CHECK_RETURN("connection_profile_get_dhcp_lease_duration", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_dhcp_server_address(profile_cellular, -1, &dhcp_lease_duration);
	CHECK_RETURN("connection_profile_get_dhcp_lease_duration", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_dhcp_server_address(profile_cellular, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_profile_get_dhcp_lease_duration", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_dhcp_server_address(profile_inval, -1, &dhcp_lease_duration);
	CHECK_RETURN("connection_profile_get_dhcp_lease_duration", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_dhcp_server_address(profile_cellular, -1, NULL);
	CHECK_RETURN("connection_profile_get_dhcp_lease_duration", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_dns_address_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the DNS address.
 * @scenario  		Invoking connection_profile_get_dns_address with valid parameter.
 */
int utc_connection_profile_get_dns_address_p(void)
{
	char *ip_addr = NULL;
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_get_dns_address(profile_temp, 1, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_addr);
		FREE_RESOURCE(ip_addr);
		CHECK_RETURN("connection_profile_get_dns_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_get_dns_address(profile_temp, 1, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_RESOURCE(ip_addr);
	CHECK_RETURN("connection_profile_get_dns_address", ret, CONNECTION_ERROR_NONE);
	ret = connection_profile_get_dns_address(profile_temp, 2, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_RESOURCE(ip_addr);
	CHECK_RETURN("connection_profile_get_dns_address", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_dns_address_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_get_dns_address should fail with invalid parameter.
 * @scenario  		Verify connection_profile_get_dns_address by passing invalid parameter.
 */
int utc_connection_profile_get_dns_address_n(void)
{
	int ret;
	char *ip_addr = NULL;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_get_dns_address(profile_inval, 1, -1, NULL);
		CHECK_RETURN("connection_profile_get_dns_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_get_dns_address(profile_inval, 1, -1, NULL);
	CHECK_RETURN("connection_profile_get_dns_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_dns_address(profile_inval, 1, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_RESOURCE(ip_addr);
	CHECK_RETURN("connection_profile_get_dns_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_dns_address(profile_cellular, 1, -1, &ip_addr);
	FREE_RESOURCE(ip_addr);
	CHECK_RETURN("connection_profile_get_dns_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_dns_address(profile_cellular, 1, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_profile_get_dns_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_dns_address(profile_inval, 1, -1, &ip_addr);
	FREE_RESOURCE(ip_addr);
	CHECK_RETURN("connection_profile_get_dns_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_dns_address(profile_cellular, 1, -1, NULL);
	CHECK_RETURN("connection_profile_get_dns_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_dns_address(profile_cellular, 99, CONNECTION_ADDRESS_FAMILY_IPV6, &ip_addr);
	FREE_RESOURCE(ip_addr);
	CHECK_RETURN("connection_profile_get_dns_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_proxy_type_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Sets the Proxy type.
 * @scenario  		Invoking connection_profile_set_proxy_type with valid parameter.
 */
int utc_connection_profile_get_proxy_type_p(void)
{
	connection_proxy_type_e type;
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_get_proxy_type(profile_temp, &type);
		CHECK_RETURN("connection_profile_get_proxy_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_set_proxy_type(profile_temp, CONNECTION_PROXY_TYPE_MANUAL);
	CHECK_RETURN("connection_profile_get_proxy_type", ret, CONNECTION_ERROR_NONE);
	ret = connection_profile_get_proxy_type(profile_temp, &type);
	CHECK_RETURN("connection_profile_get_proxy_type", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_proxy_type_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_get_proxy_type should fail with invalid parameter.
 * @scenario  		Verify connection_profile_get_proxy_type by passing invalid parameter.
 */
int utc_connection_profile_get_proxy_type_n(void)
{
	int ret;
	connection_proxy_type_e type;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_get_proxy_type(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_proxy_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_get_proxy_type(profile_inval, NULL);
	CHECK_RETURN("connection_profile_get_proxy_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_proxy_type(profile_inval, &type);
	CHECK_RETURN("connection_profile_get_proxy_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_proxy_type(profile_cellular, NULL);
	CHECK_RETURN("connection_profile_get_proxy_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_proxy_address_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the Proxy address.
 * @scenario  		Invoking connection_profile_get_proxy_address with valid parameter.
 */
int utc_connection_profile_get_proxy_address_p(void)
{
	char *ip_addr = NULL;
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_get_proxy_address(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_addr);
		FREE_RESOURCE(ip_addr);
		CHECK_RETURN("connection_profile_get_proxy_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_get_proxy_address(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_addr);
	FREE_RESOURCE(ip_addr);
	CHECK_RETURN("connection_profile_get_proxy_address", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_proxy_address_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_get_proxy_address should fail with invalid parameter.
 * @scenario  		Verify connection_profile_get_proxy_address by passing invalid parameter.
 */
int utc_connection_profile_get_proxy_address_n(void)
{
	int ret;
	char *ip_addr = NULL;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_get_proxy_address(profile_inval, -1, NULL);
		CHECK_RETURN("connection_profile_get_proxy_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_get_proxy_address(profile_inval, -1, NULL);
	CHECK_RETURN("connection_profile_get_proxy_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_proxy_address(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, &ip_addr);
	CHECK_RETURN("connection_profile_get_proxy_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_proxy_address(profile_cellular, -1, &ip_addr);
	CHECK_RETURN("connection_profile_get_proxy_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_proxy_address(profile_cellular, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_profile_get_proxy_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_proxy_address(profile_inval, -1, &ip_addr);
	CHECK_RETURN("connection_profile_get_proxy_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_proxy_address(profile_cellular, -1, NULL);
	CHECK_RETURN("connection_profile_get_proxy_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_ip_config_type_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Sets the IP config type.
 * @scenario  		Invoking connection_profile_set_ip_config_type with valid parameter.
 */
int utc_connection_profile_set_ip_config_type_p(void)
{
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_set_ip_config_type(profile_temp,
				CONNECTION_ADDRESS_FAMILY_IPV4, CONNECTION_IP_CONFIG_TYPE_STATIC);
		CHECK_RETURN("connection_profile_set_ip_config_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_set_ip_config_type(profile_temp,
			CONNECTION_ADDRESS_FAMILY_IPV4, CONNECTION_IP_CONFIG_TYPE_STATIC);
	CHECK_RETURN("connection_profile_set_ip_config_type", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_ip_config_type_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_set_ip_config_type should fail with invalid parameter.
 * @scenario  		Verify connection_profile_set_ip_config_type by passing invalid parameter.
 */
int utc_connection_profile_set_ip_config_type_n(void)
{
	int ret;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_set_ip_config_type(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, -1);
		CHECK_RETURN("connection_profile_set_ip_config_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_set_ip_config_type(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, -1);
	CHECK_RETURN("connection_profile_set_ip_config_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_set_ip_config_type(profile_inval,
			CONNECTION_ADDRESS_FAMILY_IPV4, CONNECTION_IP_CONFIG_TYPE_STATIC);
	CHECK_RETURN("connection_profile_set_ip_config_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_set_ip_config_type(profile_cellular, CONNECTION_ADDRESS_FAMILY_IPV4, -1);
	CHECK_RETURN("connection_profile_set_ip_config_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_ip_address_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Sets the IP address.
 * @scenario  		Invoking connection_profile_set_ip_address with valid parameter.
 */
int utc_connection_profile_set_ip_address_p(void)
{
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_set_ip_address(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, "192.168.11.1");
		CHECK_RETURN("connection_profile_set_ip_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_set_ip_address(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, "192.168.11.1");
	CHECK_RETURN("connection_profile_set_ip_address", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_ip_address_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_set_ip_address should fail with invalid parameter.
 * @scenario  		Verify connection_profile_set_ip_address by passing invalid parameter.
 */
int utc_connection_profile_set_ip_address_n(void)
{
	int ret;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_set_ip_address(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
		CHECK_RETURN("connection_profile_set_ip_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_set_ip_address(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_profile_set_ip_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_set_ip_address(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, "192.168.11.1");
	CHECK_RETURN("connection_profile_set_ip_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_subnet_mask_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Sets the Subnet Mask.
 * @scenario  		Invoking connection_profile_set_subnet_mask with valid parameter.
 */
int utc_connection_profile_set_subnet_mask_p(void)
{
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_set_subnet_mask(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, "255.255.255.0");
		CHECK_RETURN("connection_profile_set_subnet_mask", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_set_subnet_mask(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, "255.255.255.0");
	CHECK_RETURN("connection_profile_set_subnet_mask", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_subnet_mask_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_set_subnet_mask should fail with invalid parameter.
 * @scenario  		Verify connection_profile_set_subnet_mask by passing invalid parameter.
 */
int utc_connection_profile_set_subnet_mask_n(void)
{
	int ret;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_set_subnet_mask(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
		CHECK_RETURN("connection_profile_set_subnet_mask", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_set_subnet_mask(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_profile_set_subnet_mask", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_set_subnet_mask(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, "255.255.255.0");
	CHECK_RETURN("connection_profile_set_subnet_mask", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_gateway_address_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Sets the Gateway address.
 * @scenario  		Invoking connection_profile_set_gateway_address with valid parameter.
 */
int utc_connection_profile_set_gateway_address_p(void)
{
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_set_gateway_address(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, "192.168.11.1");
		CHECK_RETURN("connection_profile_set_gateway_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_set_gateway_address(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, "192.168.11.1");
	CHECK_RETURN("connection_profile_set_gateway_address", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_gateway_address_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_set_gateway_address should fail with invalid parameter.
 * @scenario  		Verify connection_profile_set_gateway_address by passing invalid parameter.
 */
int utc_connection_profile_set_gateway_address_n(void)
{
	int ret;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_set_gateway_address(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
		CHECK_RETURN("connection_profile_set_gateway_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_set_gateway_address(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_profile_set_gateway_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_set_gateway_address(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, "192.168.11.1");
	CHECK_RETURN("connection_profile_set_gateway_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_dns_address_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Sets the DNS address.
 * @scenario  		Invoking connection_profile_set_dns_address with valid parameter.
 */
int utc_connection_profile_set_dns_address_p(void)
{
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_set_dns_address(profile_temp, 1, CONNECTION_ADDRESS_FAMILY_IPV4, "192.168.11.1");
		CHECK_RETURN("connection_profile_set_dns_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_set_dns_address(profile_temp, 1, CONNECTION_ADDRESS_FAMILY_IPV4, "192.168.11.1");
	CHECK_RETURN("connection_profile_set_dns_address", ret, CONNECTION_ERROR_NONE);
	ret = connection_profile_set_dns_address(profile_temp, 2, CONNECTION_ADDRESS_FAMILY_IPV4, "192.168.11.2");
	CHECK_RETURN("connection_profile_set_dns_address", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_dns_address_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_set_dns_address should fail with invalid parameter.
 * @scenario  		Verify connection_profile_set_dns_address by passing invalid parameter.
 */
int utc_connection_profile_set_dns_address_n(void)
{
	int ret;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_set_dns_address(profile_inval, 1, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
		CHECK_RETURN("connection_profile_set_dns_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_set_dns_address(profile_inval, 1, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_profile_set_dns_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_set_dns_address(profile_inval, 1, CONNECTION_ADDRESS_FAMILY_IPV4, "192.168.11.1");
	CHECK_RETURN("connection_profile_set_dns_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_set_dns_address(profile_cellular, 99, CONNECTION_ADDRESS_FAMILY_IPV4, "192.168.11.1");
	CHECK_RETURN("connection_profile_set_dns_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_proxy_type_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Sets the Proxy type.
 * @scenario  		Invoking connection_profile_set_proxy_type with valid parameter.
 */
int utc_connection_profile_set_proxy_type_p(void)
{
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_set_proxy_type(profile_temp, CONNECTION_PROXY_TYPE_MANUAL);
		CHECK_RETURN("connection_profile_set_proxy_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_set_proxy_type(profile_temp, CONNECTION_PROXY_TYPE_MANUAL);
	CHECK_RETURN("connection_profile_set_proxy_type", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_proxy_type_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_set_proxy_type should fail with invalid parameter.
 * @scenario  		Verify connection_profile_set_proxy_type by passing invalid parameter.
 */
int utc_connection_profile_set_proxy_type_n(void)
{
	int ret;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_set_proxy_type(profile_inval, -1);
		CHECK_RETURN("connection_profile_set_proxy_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_set_proxy_type(profile_inval, -1);
	CHECK_RETURN("connection_profile_set_proxy_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_set_proxy_type(profile_inval, CONNECTION_PROXY_TYPE_MANUAL);
	CHECK_RETURN("connection_profile_set_proxy_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_set_proxy_type(profile_cellular, -1);
	CHECK_RETURN("connection_profile_set_proxy_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_proxy_address_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Sets the Proxy address.
 * @scenario  		Invoking connection_profile_set_proxy_address with valid parameter.
 */
int utc_connection_profile_set_proxy_address_p(void)
{
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_set_proxy_address(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, "192.168.11.1:8080");
		CHECK_RETURN("connection_profile_set_proxy_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_set_proxy_address(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, "192.168.11.1:8080");
	CHECK_RETURN("connection_profile_set_proxy_address", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_proxy_address_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_set_proxy_address should fail with invalid parameter.
 * @scenario  		Verify connection_profile_set_proxy_address by passing invalid parameter.
 */
int utc_connection_profile_set_proxy_address_n(void)
{
	int ret;
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		ret = connection_profile_set_proxy_address(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
		CHECK_RETURN("connection_profile_set_proxy_address", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = connection_profile_set_proxy_address(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_profile_set_proxy_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_set_proxy_address(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, "192.168.11.1:8080");
	CHECK_RETURN("connection_profile_set_proxy_address", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_state_changed_cb_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Registers the callback that is called when the state of profile is changed.
 * @scenario  		Invoking connection_profile_set_state_changed_cb with valid parameter.
 */
int utc_connection_profile_set_state_changed_cb_p(void)
{
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_set_state_changed_cb(profile_temp, test_profile_state_changed_cb, NULL);
		CHECK_RETURN("connection_profile_set_state_changed_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_set_state_changed_cb(profile_temp, test_profile_state_changed_cb, NULL);
	RUN_GMAIN_LOOP;
	CHECK_RETURN("connection_profile_set_state_changed_cb", ret, CONNECTION_ERROR_NONE);

	ret = connection_profile_unset_state_changed_cb(profile_temp);
	PRINT_RETURN("connection_profile_unset_state_changed_cb", ret);

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_state_changed_cb_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_set_state_changed_cb should fail with invalid parameter.
 * @scenario  		Verify connection_profile_set_state_changed_cb by passing callback and user_data as NULL.
 */
int utc_connection_profile_set_state_changed_cb_n(void)
{
	connection_profile_h profile_inval = NULL;
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_set_state_changed_cb(profile_inval, NULL, NULL);
		CHECK_RETURN("connection_profile_set_state_changed_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_set_state_changed_cb(profile_inval, NULL, NULL);
	CHECK_RETURN("connection_profile_set_state_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_set_state_changed_cb(profile_inval, test_profile_state_changed_cb, NULL);
	CHECK_RETURN("connection_profile_set_state_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_set_state_changed_cb(profile_temp, NULL, NULL);
	CHECK_RETURN("connection_profile_set_state_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_unset_state_changed_cb_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Unregisters the callback that is called when the state of profile is changed.
 * @scenario  		Invoking connection_profile_unset_state_changed_cb with valid parameter.
 */
int utc_connection_profile_unset_state_changed_cb_p(void)
{
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_unset_state_changed_cb(profile_temp);
		CHECK_RETURN("connection_profile_unset_state_changed_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_set_state_changed_cb(profile_temp, test_profile_state_changed_cb, NULL);
	RUN_GMAIN_LOOP;
	PRINT_RETURN("connection_profile_set_state_changed_cb", ret);

	ret = connection_profile_unset_state_changed_cb(profile_temp);
	CHECK_RETURN("connection_profile_unset_state_changed_cb", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_unset_state_changed_cb_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_unset_state_changed_cb should fail with invalid parameter.
 * @scenario  		Verify connection_profile_unset_state_changed_cb by passing invalid profile handle.
 */
int utc_connection_profile_unset_state_changed_cb_n(void)
{
	connection_profile_h profile_inval = NULL;

	int ret = connection_profile_unset_state_changed_cb(profile_inval);

	if (all_features_not_supported) {
		CHECK_RETURN("connection_profile_unset_state_changed_cb", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_profile_unset_state_changed_cb", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	}

	return 0;
}


/* Cellular profile operations. */

/**
 * @testcase		utc_connection_profile_set_cellular_service_type_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Sets the service type.
 * @scenario  		Invoking connection_profile_set_cellular_service_type with valid parameter.
 */
int utc_connection_profile_set_cellular_service_type_p(void)
{
	if(telephony_supported) {
		int ret = connection_profile_set_cellular_service_type(profile_cellular, CONNECTION_CELLULAR_SERVICE_TYPE_INTERNET);
		CHECK_RETURN("connection_profile_set_cellular_service_type", ret, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_profile_set_cellular_service_type(profile_cellular, CONNECTION_CELLULAR_SERVICE_TYPE_INTERNET);
		CHECK_RETURN("connection_profile_set_cellular_service_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_cellular_service_type_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_set_cellular_service_type should fail with invalid parameter.
 * @scenario  		Verify connection_profile_set_cellular_service_type by passing invalid parameter.
 */
int utc_connection_profile_set_cellular_service_type_n(void)
{
	connection_profile_h profile_inval = NULL;

	if (telephony_supported) {
		int ret = connection_profile_set_cellular_service_type(profile_inval, -1);
		CHECK_RETURN("connection_profile_set_cellular_service_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_set_cellular_service_type(profile_inval, CONNECTION_CELLULAR_SERVICE_TYPE_INTERNET);
		CHECK_RETURN("connection_profile_set_cellular_service_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_set_cellular_service_type(profile_cellular, -1);
		CHECK_RETURN("connection_profile_set_cellular_service_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_set_cellular_service_type(profile_wifi, CONNECTION_CELLULAR_SERVICE_TYPE_INTERNET);
		CHECK_RETURN("connection_profile_set_cellular_service_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_set_cellular_service_type(profile_inval, -1);
		CHECK_RETURN("connection_profile_set_cellular_service_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_cellular_apn_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Sets the APN (Access Point Name).
 * @scenario  		Invoking connection_profile_set_cellular_apn with valid parameter.
 */
int utc_connection_profile_set_cellular_apn_p(void)
{
	if (telephony_supported) {
		int ret = connection_profile_set_cellular_apn(profile_cellular, "tizen.org");
		CHECK_RETURN("connection_profile_set_cellular_apn", ret, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_profile_set_cellular_apn(profile_cellular, "tizen.org");
		CHECK_RETURN("connection_profile_set_cellular_apn", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_cellular_apn_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_set_cellular_apn should fail with invalid parameter.
 * @scenario  		Verify connection_profile_set_cellular_apn by passing invalid parameter.
 */
int utc_connection_profile_set_cellular_apn_n(void)
{
	connection_profile_h profile_inval = NULL;

	if (telephony_supported) {
		int ret = connection_profile_set_cellular_apn(profile_inval, NULL);
		CHECK_RETURN("connection_profile_set_cellular_apn", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_set_cellular_apn(profile_inval, "tizen.org");
		CHECK_RETURN("connection_profile_set_cellular_apn", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_set_cellular_apn(profile_cellular, NULL);
		CHECK_RETURN("connection_profile_set_cellular_apn", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_set_cellular_apn(profile_wifi, "tizen.org");
		CHECK_RETURN("connection_profile_set_cellular_apn", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_set_cellular_apn(profile_inval, NULL);
		CHECK_RETURN("connection_profile_set_cellular_apn", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_connection_profile_set_cellular_auth_info_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Sets the Authentication information.
 * @scenario  		Invoking connection_profile_set_cellular_auth_info with valid parameter.
 */
int utc_connection_profile_set_cellular_auth_info_p(void)
{
	if (telephony_supported) {
		int ret = connection_profile_set_cellular_auth_info(profile_cellular,
				CONNECTION_CELLULAR_AUTH_TYPE_PAP, "tizen", "flower");
		CHECK_RETURN("connection_profile_set_cellular_auth_info", ret, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_profile_set_cellular_auth_info(profile_cellular,
				CONNECTION_CELLULAR_AUTH_TYPE_PAP, "tizen", "flower");
		CHECK_RETURN("connection_profile_set_cellular_auth_info", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_cellular_auth_info_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_set_cellular_auth_info should fail with invalid parameter.
 * @scenario  		Verify connection_profile_set_cellular_auth_info by passing invalid AUTHENTICATION TYPE/parameter.
 */
int utc_connection_profile_set_cellular_auth_info_n(void)
{
	connection_profile_h profile_inval = NULL;

	if (telephony_supported) {
		int ret = connection_profile_set_cellular_auth_info(profile_inval, -1, NULL, NULL);
		CHECK_RETURN("connection_profile_set_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_set_cellular_auth_info(profile_inval,
				CONNECTION_CELLULAR_AUTH_TYPE_PAP, "tizen", "flower");
		CHECK_RETURN("connection_profile_set_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_set_cellular_auth_info(profile_cellular, -1, "tizen", "flower");
		CHECK_RETURN("connection_profile_set_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_set_cellular_auth_info(profile_cellular,
				CONNECTION_CELLULAR_AUTH_TYPE_PAP, NULL, "flower");
		CHECK_RETURN("connection_profile_set_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_set_cellular_auth_info(profile_cellular,
				CONNECTION_CELLULAR_AUTH_TYPE_PAP, "tizen", NULL);
		CHECK_RETURN("connection_profile_set_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_set_cellular_auth_info(profile_inval,
				CONNECTION_CELLULAR_AUTH_TYPE_PAP, NULL, "flower");
		CHECK_RETURN("connection_profile_set_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_set_cellular_auth_info(profile_cellular,
				CONNECTION_CELLULAR_AUTH_TYPE_PAP, NULL, NULL);
		CHECK_RETURN("connection_profile_set_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_set_cellular_auth_info(profile_wifi,
				CONNECTION_CELLULAR_AUTH_TYPE_PAP, "tizen", "flower");
		CHECK_RETURN("connection_profile_set_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_set_cellular_auth_info(profile_inval, -1, NULL, NULL);
		CHECK_RETURN("connection_profile_set_cellular_auth_info", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_cellular_home_url_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		connection_profile_set_cellular_home_url.
 * @scenario  		Invoking connection_profile_set_cellular_home_url with valid parameter.
 */
int utc_connection_profile_set_cellular_home_url_p(void)
{
	if(telephony_supported) {
		int ret = connection_profile_set_cellular_home_url(profile_cellular, "www.tizen.org");
		CHECK_RETURN("connection_profile_set_cellular_home_url", ret, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_profile_set_cellular_home_url(profile_cellular, "www.tizen.org");
		CHECK_RETURN("connection_profile_set_cellular_home_url", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_cellular_home_url_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_set_cellular_home_url should fail with invalid parameter.
 * @scenario  		Verify connection_profile_set_cellular_home_url by passing invalid profile handle.
 */
int utc_connection_profile_set_cellular_home_url_n(void)
{
	connection_profile_h profile_inval = NULL;

	if (telephony_supported) {
		int ret = connection_profile_set_cellular_home_url(profile_inval, NULL);
		CHECK_RETURN("connection_profile_set_cellular_home_url", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_set_cellular_home_url(profile_inval, "www.tizen.org");
		CHECK_RETURN("connection_profile_set_cellular_home_url", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_set_cellular_home_url(profile_cellular, NULL);
		CHECK_RETURN("connection_profile_set_cellular_home_url", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_set_cellular_home_url(profile_wifi, "www.tizen.org");
		CHECK_RETURN("connection_profile_set_cellular_home_url", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_set_cellular_home_url(profile_inval, NULL);
		CHECK_RETURN("connection_profile_set_cellular_home_url", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

#if (defined(MOBILE) || defined(WEARABLE)  || defined(TIZENIOT) || defined(TV)) //Starts MOBILE or WEARABLE or TIZENIOT or TV
/**
 * @testcase		utc_connection_profile_set_cellular_pdn_type_p
 * @since_tizen 	3.0
 * @type		Positive
 * @description		Sets the pdn type.
 * @scenario  		Invoking connection_profile_set_cellular_pdn_type with valid parameter.
 */
int utc_connection_profile_set_cellular_pdn_type_p(void)
{
	int ret = connection_profile_set_cellular_pdn_type(profile_cellular, CONNECTION_CELLULAR_PDN_TYPE_IPV4);

	if (telephony_supported) {
		CHECK_RETURN("connection_profile_set_cellular_pdn_type", ret, CONNECTION_ERROR_NONE);
	} else {
		CHECK_RETURN("connection_profile_set_cellular_pdn_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_cellular_pdn_type_n
 * @since_tizen 	3.0
 * @type		Negative
 * @description		connection_profile_set_cellular_pdn_type should fail with invalid parameter.
 * @scenario  		Verify connection_profile_set_cellular_pdn_type by passing invalid profile handle.
 */
int utc_connection_profile_set_cellular_pdn_type_n(void)
{
	connection_profile_h profile_inval = NULL;
	connection_cellular_pdn_type_e type = CONNECTION_CELLULAR_PDN_TYPE_IPV4;

	if (telephony_supported) {
		int ret = connection_profile_set_cellular_pdn_type(profile_inval, type);
		CHECK_RETURN("connection_profile_set_cellular_pdn_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_set_cellular_pdn_type(profile_wifi, type);
		CHECK_RETURN("connection_profile_set_cellular_pdn_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_set_cellular_pdn_type(profile_inval, type);
		CHECK_RETURN("connection_profile_set_cellular_pdn_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_cellular_roam_pdn_type_p
 * @since_tizen 	3.0
 * @type		Positive
 * @description		Sets the roam pdn type.
 * @scenario  		Invoking connection_profile_set_cellular_roam_pdn_type with valid parameter.
 */
int utc_connection_profile_set_cellular_roam_pdn_type_p(void)
{
	int ret = connection_profile_set_cellular_roam_pdn_type(profile_cellular, CONNECTION_CELLULAR_PDN_TYPE_IPV4);

	if (telephony_supported) {
		CHECK_RETURN("connection_profile_set_cellular_roam_pdn_type", ret, CONNECTION_ERROR_NONE);
	} else {
		CHECK_RETURN("connection_profile_set_cellular_roam_pdn_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_cellular_roam_pdn_type_n
 * @since_tizen 	3.0
 * @type		Negative
 * @description		connection_profile_set_cellular_roam_pdn_type should fail with invalid parameter.
 * @scenario  		Verify connection_profile_set_cellular_roam_pdn_type by passing invalid profile handle.
 */
int utc_connection_profile_set_cellular_roam_pdn_type_n(void)
{
	connection_profile_h profile_inval = NULL;
	connection_cellular_pdn_type_e type = CONNECTION_CELLULAR_PDN_TYPE_IPV4;

	if (telephony_supported) {
		int ret = connection_profile_set_cellular_roam_pdn_type(profile_inval, type);
		CHECK_RETURN("connection_profile_set_cellular_roam_pdn_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_set_cellular_roam_pdn_type(profile_wifi, type);
		CHECK_RETURN("connection_profile_set_cellular_roam_pdn_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_set_cellular_roam_pdn_type(profile_inval, type);
		CHECK_RETURN("connection_profile_set_cellular_roam_pdn_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}
#endif  // End MOBILE or WEARABLE or TIZENIOT

/**
 * @testcase		utc_connection_profile_get_cellular_service_type_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Sets the home URL.
 * @scenario  		Invoking connection_profile_get_cellular_service_type with valid parameter.
 */
int utc_connection_profile_get_cellular_service_type_p(void)
{
	connection_cellular_service_type_e type;

	if (telephony_supported) {
		connection_profile_set_cellular_service_type(profile_cellular, CONNECTION_CELLULAR_SERVICE_TYPE_INTERNET);

		int ret = connection_profile_get_cellular_service_type(profile_cellular, &type);
		CHECK_RETURN("connection_profile_get_cellular_service_type", ret, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_profile_get_cellular_service_type(profile_cellular, &type);
		CHECK_RETURN("connection_profile_get_cellular_service_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_cellular_service_type_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_get_cellular_service_type should fail with invalid parameter.
 * @scenario  		Verify connection_profile_get_cellular_service_type by passing invalid profile handle and home URL.
 */
int utc_connection_profile_get_cellular_service_type_n(void)
{
	connection_profile_h profile_inval = NULL;
	connection_cellular_service_type_e type;

	if (telephony_supported) {
		int ret = connection_profile_get_cellular_service_type(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_cellular_service_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_service_type(profile_inval, &type);
		CHECK_RETURN("connection_profile_get_cellular_service_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_service_type(profile_cellular, NULL);
		CHECK_RETURN("connection_profile_get_cellular_service_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_service_type(profile_wifi, &type);
		CHECK_RETURN("connection_profile_get_cellular_service_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_get_cellular_service_type(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_cellular_service_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_cellular_apn_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the APN (access point name).
 * @scenario  		Invoking connection_profile_get_cellular_apn with valid parameter.
 */
int utc_connection_profile_get_cellular_apn_p(void)
{
	char *apn = NULL;

	int ret = connection_profile_get_cellular_apn(profile_cellular, &apn);
	FREE_RESOURCE(apn);

	if(telephony_supported) {
		CHECK_RETURN("connection_profile_get_cellular_apn", ret, CONNECTION_ERROR_NONE);
	} else {
		CHECK_RETURN("connection_profile_get_cellular_apn", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_cellular_apn_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_get_cellular_apn should fail with invalid parameter.
 * @scenario  		Verify connection_profile_get_cellular_apn by passing invalid parameter.
 */
int utc_connection_profile_get_cellular_apn_n(void)
{
	connection_profile_h profile_inval = NULL;
	char *apn = NULL;

	if (telephony_supported) {
		int ret = connection_profile_get_cellular_apn(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_cellular_apn", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_apn(profile_inval, &apn);
		CHECK_RETURN("connection_profile_get_cellular_apn", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_apn(profile_cellular, NULL);
		CHECK_RETURN("connection_profile_get_cellular_apn", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_apn(profile_wifi, NULL);
		CHECK_RETURN("connection_profile_get_cellular_apn", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_get_cellular_apn(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_cellular_apn", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_cellular_auth_info_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the authentication information.
 * @scenario  		Invoking connection_profile_get_cellular_auth_info with valid parameter.
 */
int utc_connection_profile_get_cellular_auth_info_p(void)
{
	connection_cellular_auth_type_e type;
	char *name = NULL;
	char *pwd = NULL;

	int ret = connection_profile_get_cellular_auth_info(profile_cellular, &type, &name, &pwd);
	FREE_RESOURCE(name); FREE_RESOURCE(pwd);

	if (telephony_supported) {
		CHECK_RETURN("connection_profile_get_cellular_auth_info", ret, CONNECTION_ERROR_NONE);
	} else {
		CHECK_RETURN("connection_profile_get_cellular_auth_info", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_cellular_auth_info_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_get_cellular_auth_info should fail with invalid parameter.
 * @scenario  		Verify connection_profile_get_cellular_auth_info by passing invalid parameter.
 */
int utc_connection_profile_get_cellular_auth_info_n(void)
{
	connection_profile_h profile_inval = NULL;
	connection_cellular_auth_type_e type;
	char *name = NULL;
	char *pwd = NULL;

	if (telephony_supported) {
		int ret = connection_profile_get_cellular_auth_info(profile_inval, NULL, NULL, NULL);
		CHECK_RETURN("connection_profile_get_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_auth_info(profile_inval, &type, &name, &pwd);
		CHECK_RETURN("connection_profile_get_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_auth_info(profile_cellular, NULL, &name, &pwd);
		CHECK_RETURN("connection_profile_get_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_auth_info(profile_cellular, &type, NULL, &pwd);
		CHECK_RETURN("connection_profile_get_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_auth_info(profile_cellular, &type, &name, NULL);
		CHECK_RETURN("connection_profile_get_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_auth_info(profile_inval, NULL, &name, &pwd);
		CHECK_RETURN("connection_profile_get_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_auth_info(profile_inval, &type, NULL, &pwd);
		CHECK_RETURN("connection_profile_get_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_auth_info(profile_inval, &type, &name, NULL);
		CHECK_RETURN("connection_profile_get_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_auth_info(profile_cellular, NULL, NULL, &pwd);
		CHECK_RETURN("connection_profile_get_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_auth_info(profile_cellular, NULL, &name, NULL);
		CHECK_RETURN("connection_profile_get_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_auth_info(profile_cellular, &type, NULL, NULL);
		CHECK_RETURN("connection_profile_get_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_auth_info(profile_inval, NULL, NULL, &pwd);
		CHECK_RETURN("connection_profile_get_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_auth_info(profile_cellular, NULL, NULL, NULL);
		CHECK_RETURN("connection_profile_get_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_auth_info(profile_wifi, &type, &name, &pwd);
		CHECK_RETURN("connection_profile_get_cellular_auth_info", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_get_cellular_auth_info(profile_inval, NULL, NULL, NULL);
		CHECK_RETURN("connection_profile_get_cellular_auth_info", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_cellular_home_url_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the home URL.
 * @scenario  		Invoking connection_profile_get_cellular_home_url with valid parameter.
 */
int utc_connection_profile_get_cellular_home_url_p(void)
{
	char *home_url = NULL;

	int ret = connection_profile_get_cellular_home_url(profile_cellular, &home_url);
	FREE_RESOURCE(home_url);

	if (telephony_supported) {
		CHECK_RETURN("connection_profile_get_cellular_home_url", ret, CONNECTION_ERROR_NONE);
	} else {
		CHECK_RETURN("connection_profile_get_cellular_home_url", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_cellular_home_url_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_get_cellular_home_url should fail with invalid parameter.
 * @scenario  		Verify connection_profile_get_cellular_home_url by passing invalid profile handle.
 */
int utc_connection_profile_get_cellular_home_url_n(void)
{
	connection_profile_h profile_inval = NULL;
	char *home_url = NULL;

	if (telephony_supported) {
		int ret = connection_profile_get_cellular_home_url(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_cellular_home_url", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_home_url(profile_inval, &home_url);
		CHECK_RETURN("connection_profile_get_cellular_home_url", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_home_url(profile_cellular, NULL);
		CHECK_RETURN("connection_profile_get_cellular_home_url", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_home_url(profile_wifi, &home_url);
		CHECK_RETURN("connection_profile_get_cellular_home_url", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_get_cellular_home_url(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_cellular_home_url", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

#if (defined(MOBILE) || defined(WEARABLE)  || defined(TIZENIOT) || defined(TV)) //Starts MOBILE or WEARABLE or TIZENIOT or TV
/**
 * @testcase		utc_connection_profile_get_cellular_pdn_type_p
 * @since_tizen 	3.0
 * @type		Positive
 * @description		Gets the pdn type.
 * @scenario  		Invoking connection_profile_get_cellular_pdn_type with valid parameter.
 */
int utc_connection_profile_get_cellular_pdn_type_p(void)
{
	connection_cellular_pdn_type_e type;

	if (telephony_supported) {
		int ret = connection_profile_set_cellular_pdn_type(profile_cellular, CONNECTION_CELLULAR_PDN_TYPE_IPV4);
		CHECK_RETURN("connection_profile_set_cellular_pdn_type", ret, CONNECTION_ERROR_NONE);

		ret = connection_profile_get_cellular_pdn_type(profile_cellular, &type);
		CHECK_RETURN("connection_profile_set_cellular_pdn_type", ret, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_profile_get_cellular_pdn_type(profile_cellular, &type);
		CHECK_RETURN("connection_profile_set_cellular_pdn_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_cellular_pdn_type_n
 * @since_tizen 	3.0
 * @type		Negative
 * @description		connection_profile_get_cellular_pdn_type should fail with invalid parameter.
 * @scenario  		Verify connection_profile_get_cellular_pdn_type by passing invalid profile handle.
 */
int utc_connection_profile_get_cellular_pdn_type_n(void)
{
	connection_profile_h profile_inval = NULL;
	connection_cellular_pdn_type_e type;

	if (telephony_supported) {
		int ret = connection_profile_get_cellular_pdn_type(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_cellular_pdn_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_pdn_type(profile_cellular, NULL);
		CHECK_RETURN("connection_profile_get_cellular_pdn_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_pdn_type(profile_wifi, &type);
		CHECK_RETURN("connection_profile_get_cellular_pdn_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_get_cellular_pdn_type(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_cellular_pdn_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_cellular_roam_pdn_type_p
 * @since_tizen 	3.0
 * @type		Positive
 * @description		Gets the roam pdn type.
 * @scenario  		Invoking connection_profile_get_cellular_roam_pdn_type with valid parameter.
 */
int utc_connection_profile_get_cellular_roam_pdn_type_p(void)
{
	connection_cellular_pdn_type_e type;

	if(telephony_supported) {
		int ret = connection_profile_set_cellular_roam_pdn_type(profile_cellular, CONNECTION_CELLULAR_PDN_TYPE_IPV4);
		CHECK_RETURN("connection_profile_set_cellular_roam_pdn_type", ret, CONNECTION_ERROR_NONE);

		ret = connection_profile_get_cellular_roam_pdn_type(profile_cellular, &type);
		CHECK_RETURN("connection_profile_set_cellular_roam_pdn_type", ret, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_profile_get_cellular_roam_pdn_type(profile_cellular, &type);
		CHECK_RETURN("connection_profile_set_cellular_roam_pdn_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_cellular_roam_pdn_type_n
 * @since_tizen 	3.0
 * @type		Negative
 * @description		connection_profile_get_cellular_roam_pdn_type should fail with invalid parameter.
 * @scenario  		Verify connection_profile_get_cellular_roam_pdn_type by passing invalid profile handle.
 */
int utc_connection_profile_get_cellular_roam_pdn_type_n(void)
{
	connection_profile_h profile_inval = NULL;
	connection_cellular_pdn_type_e type;

	if (telephony_supported) {
		int ret = connection_profile_get_cellular_roam_pdn_type(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_cellular_roam_pdn_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_roam_pdn_type(profile_cellular, NULL);
		CHECK_RETURN("connection_profile_get_cellular_roam_pdn_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_cellular_roam_pdn_type(profile_wifi, &type);
		CHECK_RETURN("connection_profile_get_cellular_roam_pdn_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_get_cellular_roam_pdn_type(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_cellular_roam_pdn_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}
#endif  // End MOBILE or WEARABLE or TIZENIOT or TV

/**
 * @testcase		utc_connection_profile_is_cellular_roaming_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Checks wheter the connection is in roaming state.
 * @scenario  		Invoking connection_profile_is_cellular_roaming with valid parameter.
 */
int utc_connection_profile_is_cellular_roaming_p(void)
{
	bool roaming;

	if (telephony_supported) {
		int ret = connection_profile_is_cellular_roaming(profile_cellular, &roaming);
		CHECK_RETURN("connection_profile_is_cellular_roaming", ret, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_profile_is_cellular_roaming(profile_cellular, &roaming);
		CHECK_RETURN("connection_profile_is_cellular_roaming", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_is_cellular_roaming_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_is_cellular_roaming should fail with invalid parameter.
 * @scenario  		Verify connection_profile_is_cellular_roaming by passing invalid parameter.
 */
int utc_connection_profile_is_cellular_roaming_n(void)
{
	connection_profile_h profile_inval = NULL;
	bool roaming;

	if (telephony_supported) {
		int ret = connection_profile_is_cellular_roaming(profile_inval, NULL);
		CHECK_RETURN("connection_profile_is_cellular_roaming", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_is_cellular_roaming(profile_inval, &roaming);
		CHECK_RETURN("connection_profile_is_cellular_roaming", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_is_cellular_roaming(profile_cellular, NULL);
		CHECK_RETURN("connection_profile_is_cellular_roaming", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_is_cellular_roaming(profile_wifi, &roaming);
		CHECK_RETURN("connection_profile_is_cellular_roaming", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_is_cellular_roaming(profile_inval, NULL);
		CHECK_RETURN("connection_profile_is_cellular_roaming", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_is_cellular_hidden_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Checks whether the profile is hidden.
 * @scenario  		Invoking connection_profile_is_cellular_hidden with valid parameter.
 */
int utc_connection_profile_is_cellular_hidden_p(void)
{
	bool is_hidden;

	if (telephony_supported) {
		int ret = connection_profile_is_cellular_hidden(profile_cellular, &is_hidden);
		CHECK_RETURN("connection_profile_is_cellular_hidden", ret, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_profile_is_cellular_hidden(profile_cellular, &is_hidden);
		CHECK_RETURN("connection_profile_is_cellular_hidden", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;

}

/**
 * @testcase		utc_connection_profile_is_cellular_hidden_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_is_cellular_hidden should fail with invalid parameter.
 * @scenario  		Verify connection_profile_is_cellular_hidden by passing invalid parameter.
 */
int utc_connection_profile_is_cellular_hidden_n(void)
{
	connection_profile_h profile_inval = NULL;
	bool is_hidden;

	if (telephony_supported) {
		int ret = connection_profile_is_cellular_hidden(profile_inval, NULL);
		CHECK_RETURN("connection_profile_is_cellular_hidden", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_is_cellular_hidden(profile_inval, &is_hidden);
		CHECK_RETURN("connection_profile_is_cellular_hidden", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_is_cellular_hidden(profile_cellular, NULL);
		CHECK_RETURN("connection_profile_is_cellular_hidden", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_is_cellular_hidden(profile_wifi, &is_hidden);
		CHECK_RETURN("connection_profile_is_cellular_hidden", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_is_cellular_hidden(profile_inval, NULL);
		CHECK_RETURN("connection_profile_is_cellular_hidden", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_is_cellular_editable_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Checks whether the profile is editable.
 * @scenario  		Invoking connection_profile_is_cellular_editable with valid parameter.
 */
int utc_connection_profile_is_cellular_editable_p(void)
{
	bool is_editable;

	if (telephony_supported) {
		int ret = connection_profile_is_cellular_editable(profile_cellular, &is_editable);
		CHECK_RETURN("connection_profile_is_cellular_editable", ret, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_profile_is_cellular_editable(profile_cellular, &is_editable);
		CHECK_RETURN("connection_profile_is_cellular_editable", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_is_cellular_editable_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_is_cellular_editable should fail with invalid parameter.
 * @scenario  		Verify connection_profile_is_cellular_editable by passing invalid parameter.
 */
int utc_connection_profile_is_cellular_editable_n(void)
{
	connection_profile_h profile_inval = NULL;
	bool is_editable;

	if (telephony_supported) {
		int ret = connection_profile_is_cellular_editable(profile_inval, NULL);
		CHECK_RETURN("connection_profile_is_cellular_editable", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_is_cellular_editable(profile_inval, &is_editable);
		CHECK_RETURN("connection_profile_is_cellular_editable", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_is_cellular_editable(profile_cellular, NULL);
		CHECK_RETURN("connection_profile_is_cellular_editable", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_is_cellular_editable(profile_wifi, &is_editable);
		CHECK_RETURN("connection_profile_is_cellular_editable", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_is_cellular_editable(profile_inval, NULL);
		CHECK_RETURN("connection_profile_is_cellular_editable", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_is_cellular_default_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Checks whether the profile is default.is_default  @c true if the profile is default,
			otherwise @c false if the profile is not default
 * @scenario  		Invoking connection_profile_is_cellular_default with valid parameter.
 */
int utc_connection_profile_is_cellular_default_p(void)
{
	bool is_default;

	if (telephony_supported) {
		int ret = connection_profile_is_cellular_default(profile_cellular, &is_default);
		CHECK_RETURN("connection_profile_is_cellular_default", ret, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_profile_is_cellular_default(profile_cellular, &is_default);
		CHECK_RETURN("connection_profile_is_cellular_default", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_is_cellular_default_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_is_cellular_default should fail with invalid parameter.
 * @scenario  		Verify connection_profile_is_cellular_default by passing invalid parameter.
 */
int utc_connection_profile_is_cellular_default_n(void)
{
	bool is_editable;

	if (telephony_supported) {
		int ret = connection_profile_is_cellular_default(NULL, &is_editable);
		CHECK_RETURN("connection_profile_is_cellular_default", ret, CONNECTION_ERROR_INVALID_PARAMETER);

		ret = connection_profile_is_cellular_default(profile_cellular, NULL);
		CHECK_RETURN("connection_profile_is_cellular_default", ret, CONNECTION_ERROR_INVALID_PARAMETER);

		ret = connection_profile_is_cellular_default(profile_wifi, &is_editable);
		CHECK_RETURN("connection_profile_is_cellular_default", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_is_cellular_default(NULL, &is_editable);
		CHECK_RETURN("connection_profile_is_cellular_default", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_refresh_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Refreshes the profile information.
 * @scenario  		Invoking connection_profile_refresh with valid parameter.
 */
int utc_connection_profile_refresh_p(void)
{
	int ret = test_get_any_profile(&profile_temp);

	if (all_features_not_supported) {
		ret = connection_profile_refresh(profile_temp);
		CHECK_RETURN("connection_profile_refresh", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);
	ret = connection_profile_refresh(profile_temp);
	CHECK_RETURN("connection_profile_refresh", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_refresh_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_refresh should fail with invalid parameter.
 * @scenario  		Verify connection_profile_refresh by passing invalid profile handle.
 */
int utc_connection_profile_refresh_n(void)
{
	connection_profile_h profile_inval = NULL;

	int ret = connection_profile_refresh(profile_inval);

	if (all_features_not_supported) {
		CHECK_RETURN("connection_profile_refresh", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_profile_refresh", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/* Wi-Fi profile operations. */

/**
 * @testcase		utc_connection_profile_get_wifi_essid_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the ESSID (Extended Service Set Identifier).
 * @scenario  		Invoking connection_profile_get_wifi_essid with valid parameter.
 */
int utc_connection_profile_get_wifi_essid_p(void)
{
	char *essid = NULL;

	int ret = connection_profile_get_wifi_essid(profile_wifi, &essid);
	FREE_RESOURCE(essid);

	if (wifi_supported) {
		CHECK_RETURN("connection_profile_get_wifi_essid", ret, CONNECTION_ERROR_NONE);
	} else {
		CHECK_RETURN("connection_profile_get_wifi_essid", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_wifi_essid_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_get_wifi_essid should fail with invalid parameter.
 * @scenario  		Verify connection_profile_get_wifi_essid by passing invalid parameter.
 */
int utc_connection_profile_get_wifi_essid_n(void)
{
	connection_profile_h profile_inval = NULL;
	char *essid = NULL;

	if (wifi_supported) {
		int ret = connection_profile_get_wifi_essid(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_wifi_essid", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_essid(profile_inval, &essid);
		CHECK_RETURN("connection_profile_get_wifi_essid", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_essid(profile_wifi, NULL);
		CHECK_RETURN("connection_profile_get_wifi_essid", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_essid(profile_cellular, &essid);
		CHECK_RETURN("connection_profile_get_wifi_essid", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_get_wifi_essid(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_wifi_essid", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_wifi_bssid_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the BSSID (Basic Service Set Identifier).
 * @scenario  		Invoking connection_profile_get_wifi_bssid with valid parameter.
 */
int utc_connection_profile_get_wifi_bssid_p(void)
{
	char *bssid = NULL;

	int ret = connection_profile_get_wifi_bssid(profile_wifi, &bssid);
	FREE_RESOURCE(bssid);

	if (wifi_supported) {
		CHECK_RETURN("connection_profile_get_wifi_bssid", ret, CONNECTION_ERROR_NONE);
	} else {
		CHECK_RETURN("connection_profile_get_wifi_bssid", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_wifi_bssid_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_get_wifi_bssid should fail with invalid parameter.
 * @scenario  		Verify connection_profile_get_wifi_bssid by passing invalid parameter.
 */
int utc_connection_profile_get_wifi_bssid_n(void)
{
	connection_profile_h profile_inval = NULL;
	char *bssid = NULL;

	if (wifi_supported) {
		int ret = connection_profile_get_wifi_bssid(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_wifi_bssid", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_bssid(profile_inval, &bssid);
		CHECK_RETURN("connection_profile_get_wifi_bssid", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_bssid(profile_wifi, NULL);
		CHECK_RETURN("connection_profile_get_wifi_bssid", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_bssid(profile_cellular, &bssid);
		CHECK_RETURN("connection_profile_get_wifi_bssid", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_get_wifi_bssid(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_wifi_bssid", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_wifi_rssi_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the RSSI.
 * @scenario  		Invoking connection_profile_get_wifi_rssi with valid parameter.
 */
int utc_connection_profile_get_wifi_rssi_p(void)
{
	int rssi;

	if (wifi_supported) {
		int ret = connection_profile_get_wifi_rssi(profile_wifi, &rssi);
		CHECK_RETURN("connection_profile_get_wifi_rssi", ret, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_profile_get_wifi_rssi(profile_wifi, &rssi);
		CHECK_RETURN("connection_profile_get_wifi_rssi", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_wifi_rssi_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_get_wifi_rssi should fail with invalid parameter.
 * @scenario  		Verify connection_profile_get_wifi_rssi by passing invalid parameter.
 */
int utc_connection_profile_get_wifi_rssi_n(void)
{
	connection_profile_h profile_inval = NULL;
	int rssi;

	if (wifi_supported) {
		int ret = connection_profile_get_wifi_rssi(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_wifi_rssi", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_rssi(profile_inval, &rssi);
		CHECK_RETURN("connection_profile_get_wifi_rssi", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_rssi(profile_wifi, NULL);
		CHECK_RETURN("connection_profile_get_wifi_rssi", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_rssi(profile_cellular, &rssi);
		CHECK_RETURN("connection_profile_get_wifi_rssi", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_get_wifi_rssi(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_wifi_rssi", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_wifi_frequency_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the frequency (MHz).
 * @scenario  		Invoking connection_profile_get_wifi_frequency with valid parameter.
 */
int utc_connection_profile_get_wifi_frequency_p(void)
{
	int frequency;

	if (wifi_supported) {
		int ret = connection_profile_get_wifi_frequency(profile_wifi, &frequency);
		CHECK_RETURN("connection_profile_get_wifi_frequency", ret, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_profile_get_wifi_frequency(profile_wifi, &frequency);
		CHECK_RETURN("connection_profile_get_wifi_frequency", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_wifi_frequency_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_get_wifi_frequency should fail with invalid parameter.
 * @scenario  		Verify connection_profile_get_wifi_frequency by passing invalid parameter.
 */
int utc_connection_profile_get_wifi_frequency_n(void)
{
	connection_profile_h profile_inval = NULL;
	int frequency;

	if (wifi_supported) {
		int ret = connection_profile_get_wifi_frequency(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_wifi_frequency", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_frequency(profile_inval, &frequency);
		CHECK_RETURN("connection_profile_get_wifi_frequency", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_frequency(profile_wifi, NULL);
		CHECK_RETURN("connection_profile_get_wifi_frequency", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_frequency(profile_cellular, &frequency);
		CHECK_RETURN("connection_profile_get_wifi_frequency", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_get_wifi_frequency(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_wifi_frequency", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_wifi_max_speed_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the max speed (Mbps).
 * @scenario  		Invoking connection_profile_get_wifi_max_speed with valid parameter.
 */
int utc_connection_profile_get_wifi_max_speed_p(void)
{
	int max_speed;

	if (wifi_supported) {
		int ret = connection_profile_get_wifi_max_speed(profile_wifi, &max_speed);
		CHECK_RETURN("connection_profile_get_wifi_max_speed", ret, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_profile_get_wifi_max_speed(profile_wifi, &max_speed);
		CHECK_RETURN("connection_profile_get_wifi_max_speed", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_wifi_max_speed_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_get_wifi_max_speed should fail with invalid parameter.
 * @scenario  		Verify connection_profile_get_wifi_max_speed by passing invalid parameter.
 */
int utc_connection_profile_get_wifi_max_speed_n(void)
{
	connection_profile_h profile_inval = NULL;
	int max_speed;

	if (wifi_supported) {
		int ret = connection_profile_get_wifi_max_speed(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_wifi_max_speed", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_max_speed(profile_inval, &max_speed);
		CHECK_RETURN("connection_profile_get_wifi_max_speed", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_max_speed(profile_wifi, NULL);
		CHECK_RETURN("connection_profile_get_wifi_max_speed", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_max_speed(profile_cellular, &max_speed);
		CHECK_RETURN("connection_profile_get_wifi_max_speed", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_get_wifi_max_speed(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_wifi_max_speed", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_wifi_security_type_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the security mode of Wi-Fi.
 * @scenario  		Invoking connection_profile_get_wifi_security_type with valid parameter.
 */
int utc_connection_profile_get_wifi_security_type_p(void)
{
	connection_wifi_security_type_e sec_type;

	if (wifi_supported) {
		int ret = connection_profile_get_wifi_security_type(profile_wifi, &sec_type);
		CHECK_RETURN("connection_profile_get_wifi_security_type", ret, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_profile_get_wifi_security_type(profile_wifi, &sec_type);
		CHECK_RETURN("connection_profile_get_wifi_security_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_wifi_security_type_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_get_wifi_security_type should fail with invalid parameter.
 * @scenario  		Verify connection_profile_get_wifi_security_type by passing invalid parameter.
 */
int utc_connection_profile_get_wifi_security_type_n(void)
{
	connection_profile_h profile_inval = NULL;
	connection_wifi_security_type_e sec_type;

	if (wifi_supported) {
		int ret = connection_profile_get_wifi_security_type(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_wifi_security_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_security_type(profile_inval, &sec_type);
		CHECK_RETURN("connection_profile_get_wifi_security_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_security_type(profile_wifi, NULL);
		CHECK_RETURN("connection_profile_get_wifi_security_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_security_type(profile_cellular, &sec_type);
		CHECK_RETURN("connection_profile_get_wifi_security_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_get_wifi_security_type(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_wifi_security_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_wifi_encryption_type_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Gets the security mode of Wi-Fi.
 * @scenario  		Invoking connection_profile_get_wifi_encryption_type with valid parameter.
 */
int utc_connection_profile_get_wifi_encryption_type_p(void)
{
	connection_wifi_encryption_type_e enc_type;

	if (wifi_supported) {
		int ret = connection_profile_get_wifi_encryption_type(profile_wifi, &enc_type);
		CHECK_RETURN("connection_profile_get_wifi_encryption_type", ret, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_profile_get_wifi_encryption_type(profile_wifi, &enc_type);
		CHECK_RETURN("connection_profile_get_wifi_encryption_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_wifi_encryption_type_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_get_wifi_encryption_type should fail with invalid parameter.
 * @scenario  		Verify connection_profile_get_wifi_encryption_type by passing invalid parameter.
 */
int utc_connection_profile_get_wifi_encryption_type_n(void)
{
	connection_profile_h profile_inval = NULL;
	connection_wifi_encryption_type_e enc_type;

	if (wifi_supported) {
		int ret = connection_profile_get_wifi_encryption_type(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_wifi_encryption_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_encryption_type(profile_inval, &enc_type);
		CHECK_RETURN("connection_profile_get_wifi_encryption_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_encryption_type(profile_wifi, NULL);
		CHECK_RETURN("connection_profile_get_wifi_encryption_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_get_wifi_encryption_type(profile_cellular, &enc_type);
		CHECK_RETURN("connection_profile_get_wifi_encryption_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_get_wifi_encryption_type(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_wifi_encryption_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_is_wifi_passphrase_required_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Checks whether passphrase is required.
 * @scenario  		Invoking connection_profile_is_wifi_passphrase_required with valid parameter.
 */
int utc_connection_profile_is_wifi_passphrase_required_p(void)
{
	bool flag;

	if (wifi_supported) {
		int ret = connection_profile_is_wifi_passphrase_required(profile_wifi, &flag);
		CHECK_RETURN("connection_profile_is_wifi_passphrase_required", ret, CONNECTION_ERROR_NONE);
	} else {
		int ret = connection_profile_is_wifi_passphrase_required(profile_wifi, &flag);
		CHECK_RETURN("connection_profile_is_wifi_passphrase_required", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_is_wifi_passphrase_required_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_is_wifi_passphrase_required should fail with invalid parameter.
 * @scenario  		Verify connection_profile_is_wifi_passphrase_required by passing invalid parameter.
 */
int utc_connection_profile_is_wifi_passphrase_required_n(void)
{
	connection_profile_h profile_inval = NULL;
	bool flag;

	if (wifi_supported) {
		int ret = connection_profile_is_wifi_passphrase_required(profile_inval, NULL);
		CHECK_RETURN("connection_profile_is_wifi_passphrase_required", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_is_wifi_passphrase_required(profile_inval, &flag);
		CHECK_RETURN("connection_profile_is_wifi_passphrase_required", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_is_wifi_passphrase_required(profile_wifi, NULL);
		CHECK_RETURN("connection_profile_is_wifi_passphrase_required", ret, CONNECTION_ERROR_INVALID_PARAMETER);
		ret = connection_profile_is_wifi_passphrase_required(profile_cellular, &flag);
		CHECK_RETURN("connection_profile_is_wifi_passphrase_required", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	} else {
		int ret = connection_profile_is_wifi_passphrase_required(profile_inval, NULL);
		CHECK_RETURN("connection_profile_is_wifi_passphrase_required", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_wifi_passphrase_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Sets the passphrase of the Wi-Fi WPA.
 * @scenario  		Invoking connection_profile_set_wifi_passphrase with valid parameter.
 */
int utc_connection_profile_set_wifi_passphrase_p(void)
{
    if(wifi_supported) {
        int ret = connection_profile_set_wifi_passphrase(profile_wifi, "keystring");
        CHECK_RETURN("connection_profile_set_wifi_passphrase", ret, CONNECTION_ERROR_NONE);
    } else {
        int ret = connection_profile_set_wifi_passphrase(profile_wifi, "keystring");
        CHECK_RETURN("connection_profile_set_wifi_passphrase", ret, CONNECTION_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_connection_profile_set_wifi_passphrase_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_set_wifi_passphrase should fail with invalid parameter.
 * @scenario  		Verify connection_profile_set_wifi_passphrase by passing invalid parameter.
 */
int utc_connection_profile_set_wifi_passphrase_n(void)
{
    connection_profile_h profile_inval = NULL;

    if(wifi_supported) {
        int ret = connection_profile_set_wifi_passphrase(profile_inval, NULL);
        CHECK_RETURN("connection_profile_set_wifi_passphrase", ret, CONNECTION_ERROR_INVALID_PARAMETER);
        ret = connection_profile_set_wifi_passphrase(profile_inval, "keystring");
        CHECK_RETURN("connection_profile_set_wifi_passphrase", ret, CONNECTION_ERROR_INVALID_PARAMETER);
        ret = connection_profile_set_wifi_passphrase(profile_wifi, NULL);
        CHECK_RETURN("connection_profile_set_wifi_passphrase", ret, CONNECTION_ERROR_INVALID_PARAMETER);
        ret = connection_profile_set_wifi_passphrase(profile_cellular, "keystring");
        CHECK_RETURN("connection_profile_set_wifi_passphrase", ret, CONNECTION_ERROR_INVALID_PARAMETER);
    } else {
        int ret = connection_profile_set_wifi_passphrase(profile_inval, NULL);
        CHECK_RETURN("connection_profile_set_wifi_passphrase", ret, CONNECTION_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_connection_profile_is_wifi_wps_supported_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Checks whether the WPS (Wi-Fi Protected Setup) is supported.
 * @scenario  		Invoking connection_profile_is_wifi_wps_supported with valid parameter.
 */
int utc_connection_profile_is_wifi_wps_supported_p(void)
{
    bool flag;

    if(wifi_supported) {
        int ret = connection_profile_is_wifi_wps_supported(profile_wifi, &flag);
        CHECK_RETURN("connection_profile_set_wifi_passphrase", ret, CONNECTION_ERROR_NONE);
    } else {
        int ret = connection_profile_is_wifi_wps_supported(profile_wifi, &flag);
        CHECK_RETURN("connection_profile_set_wifi_passphrase", ret, CONNECTION_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_connection_profile_is_wifi_wps_supported_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_is_wifi_wps_supported should fail with invalid parameter.
 * @scenario  		Verify connection_profile_is_wifi_wps_supported by passing invalid parameter.
 */
int utc_connection_profile_is_wifi_wps_supported_n(void)
{
    connection_profile_h profile_inval = NULL;
    bool flag;

    if(wifi_supported) {
        int ret = connection_profile_is_wifi_wps_supported(profile_inval, NULL);
        CHECK_RETURN("connection_profile_set_wifi_passphrase", ret, CONNECTION_ERROR_INVALID_PARAMETER);
        ret = connection_profile_is_wifi_wps_supported(profile_inval, &flag);
        CHECK_RETURN("connection_profile_set_wifi_passphrase", ret, CONNECTION_ERROR_INVALID_PARAMETER);
        ret = connection_profile_is_wifi_wps_supported(profile_wifi, NULL);
        CHECK_RETURN("connection_profile_set_wifi_passphrase", ret, CONNECTION_ERROR_INVALID_PARAMETER);
        ret = connection_profile_is_wifi_wps_supported(profile_cellular, &flag);
        CHECK_RETURN("connection_profile_set_wifi_passphrase", ret, CONNECTION_ERROR_INVALID_PARAMETER);
    } else {
        int ret = connection_profile_is_wifi_wps_supported(profile_inval, NULL);
        CHECK_RETURN("connection_profile_set_wifi_passphrase", ret, CONNECTION_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase        utc_connection_profile_get_ipv6_state_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     Gets IPv6 state
 * @scenario        Invoking connection_profile_get_ipv6_state with valid parameter.
 */
int utc_connection_profile_get_ipv6_state_p(void)
{
	connection_profile_state_e state;
	int ret = test_get_any_profile(&profile_temp);

	if(all_features_not_supported) {
		ret = connection_profile_get_ipv6_state(profile_temp, &state);
		CHECK_RETURN("connection_profile_get_ipv6_state", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);

	ret = connection_profile_get_ipv6_state(profile_temp, &state);
	CHECK_RETURN("connection_profile_get_ipv6_state", ret, CONNECTION_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_connection_profile_get_ipv6_state_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     connection_profile_get_ipv6_state should be failed with invalid parameter.
 * @scenario        Verify connection_profile_get_ipv6_state by passing invalid parameter.
 */
int utc_connection_profile_get_ipv6_state_n(void)
{
	connection_profile_h profile_inval = NULL;
	connection_profile_state_e state;

	if(all_features_not_supported) {
		int ret = connection_profile_get_ipv6_state(profile_inval, NULL);
		CHECK_RETURN("connection_profile_get_ipv6_state", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int ret = connection_profile_get_ipv6_state(profile_inval, NULL);
	CHECK_RETURN("connection_profile_get_ipv6_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_ipv6_state(profile_inval, &state);
	CHECK_RETURN("connection_profile_get_ipv6_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_ipv6_state(profile_wifi, NULL);
	CHECK_RETURN("connection_profile_get_ipv6_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_connection_profile_get_prefix_length_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     Gets prefix length
 * @scenario        Invoking connection_profile_get_ipv6_state with valid parameter.
 */
int utc_connection_profile_get_prefix_length_p(void)
{
	int length;

	if (all_features_not_supported) {
		int ret = connection_profile_get_prefix_length(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, &length);
		CHECK_RETURN("connection_profile_get_prefix_length", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		ret = connection_profile_get_prefix_length(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV6, &length);
		CHECK_RETURN("connection_profile_get_prefix_length", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	int ret = connection_get_current_profile(connection, &profile_temp);
	CHECK_RETURN("connection_profile_get_prefix_length", ret, CONNECTION_ERROR_NONE);
	ret = connection_profile_get_prefix_length(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, &length);
	CHECK_RETURN("connection_profile_get_prefix_length", ret, CONNECTION_ERROR_NONE);
	ret = connection_profile_get_prefix_length(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV6, &length);
	CHECK_RETURN("connection_profile_get_prefix_length", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_connection_profile_get_prefix_length_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     connection_profile_get_prefix_length should be failed with invalid parameter.
 * @scenario        Verify prefix_length by passing invalid parameter.
 */
int utc_connection_profile_get_prefix_length_n(void)
{
	connection_profile_h profile_inval = NULL;
	int length;

	if (all_features_not_supported) {
		int ret = connection_profile_get_prefix_length(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, &length);
		CHECK_RETURN("connection_profile_get_prefix_length", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		ret = connection_profile_get_prefix_length(profile_wifi, CONNECTION_ADDRESS_FAMILY_IPV6, NULL);
		CHECK_RETURN("connection_profile_get_prefix_length", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	int ret = connection_profile_get_prefix_length(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_profile_get_prefix_length", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_prefix_length(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, &length);
	CHECK_RETURN("connection_profile_get_prefix_length", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_prefix_length(profile_wifi, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_profile_get_prefix_length", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_connection_profile_set_prefix_length_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     Sets prefix length
 * @scenario        Invoking connection_profile_set_ipv6_state with valid parameter.
 */
int utc_connection_profile_set_prefix_length_p(void)
{
	int length = 32;

	if (all_features_not_supported) {
		int ret = connection_profile_set_prefix_length(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, length);
		CHECK_RETURN("connection_profile_set_prefix_length", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	int ret = connection_get_current_profile(connection, &profile_temp);
	CHECK_RETURN("connection_profile_set_prefix_length", ret, CONNECTION_ERROR_NONE);
	ret = connection_profile_set_prefix_length(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, length);
	CHECK_RETURN("connection_profile_set_prefix_length", ret, CONNECTION_ERROR_NONE);
	ret = connection_profile_set_prefix_length(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV6, length);
	CHECK_RETURN("connection_profile_set_prefix_length", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_connection_profile_set_prefix_length_n
 * @since_tizen     4.0
 * @type            Negative
 * @description	    connection_profile_set_prefix_length should be failed with invalid parameter.
 * @scenario        Verify prefix_length by passing invalid parameter.
 */
int utc_connection_profile_set_prefix_length_n(void)
{
	connection_profile_h profile_inval = NULL;
	int length = 32;

	if (all_features_not_supported) {
		int ret = connection_profile_set_prefix_length(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, length);
		CHECK_RETURN("connection_profile_set_prefix_length", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	int ret = connection_profile_set_prefix_length(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, length);
	CHECK_RETURN("connection_profile_set_prefix_length", ret, CONNECTION_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_connection_profile_get_dns_config_type_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     Gets DNS configuration type
 * @scenario        Invoking connection_profile_get_dns_config_typ with valid parameter.
 */
int utc_connection_profile_get_dns_config_type_p(void)
{
	connection_dns_config_type_e config_type;
	int ret = connection_get_current_profile(connection, &profile_temp);
	PRINT_RETURN("connection_get_current_profile", ret);

	if (all_features_not_supported) {
		ret = connection_profile_get_dns_config_type(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, &config_type);
		CHECK_RETURN("connection_profile_get_dns_config_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(profile_temp);

	ret = connection_profile_get_dns_config_type(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, &config_type);
	CHECK_RETURN("connection_profile_get_dns_config_type", ret, CONNECTION_ERROR_NONE);
	ret = connection_profile_get_dns_config_type(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV6, &config_type);
	CHECK_RETURN("connection_profile_get_dns_config_type", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_connection_profile_get_dns_config_type_n
 * @since_tizen     4.0
 * @type            Negative
 * @description     connection_profile_get_dns_config_typ should be failed with invalid parameter.
 * @scenario        Verify connection_profile_get_dns_config_typ by passing invalid parameter.
 */
int utc_connection_profile_get_dns_config_type_n(void)
{
	connection_profile_h profile_inval = NULL;
	connection_dns_config_type_e config_type;

	if(all_features_not_supported) {
		int ret = connection_profile_get_dns_config_type(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
		CHECK_RETURN("connection_profile_get_dns_config_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int ret = connection_profile_get_dns_config_type(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, NULL);
	CHECK_RETURN("connection_profile_get_dns_config_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_dns_config_type(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV6, &config_type);
	CHECK_RETURN("connection_profile_get_dns_config_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_get_dns_config_type(profile_wifi, CONNECTION_ADDRESS_FAMILY_IPV6, NULL);
	CHECK_RETURN("connection_profile_get_dns_config_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_connection_profile_set_dns_config_type_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     Sets DNS configuration type
 * @scenario        Invoking connection_profile_set_dns_config_typ with valid parameter.
 */
int utc_connection_profile_set_dns_config_type_p(void)
{
	if (all_features_not_supported) {
		int ret = connection_profile_set_dns_config_type(profile_wifi, CONNECTION_ADDRESS_FAMILY_IPV6, CONNECTION_DNS_CONFIG_TYPE_DYNAMIC);
		CHECK_RETURN("connection_profile_set_dns_config_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	int ret = connection_get_current_profile(connection, &profile_temp);
	CHECK_RETURN("connection_profile_set_dns_config_type", ret, CONNECTION_ERROR_NONE);
	ret = connection_profile_set_dns_config_type(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, CONNECTION_DNS_CONFIG_TYPE_STATIC);
	CHECK_RETURN("connection_profile_set_dns_config_type", ret, CONNECTION_ERROR_NONE);
	ret = connection_profile_set_dns_config_type(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV4, CONNECTION_DNS_CONFIG_TYPE_DYNAMIC);
	CHECK_RETURN("connection_profile_set_dns_config_type", ret, CONNECTION_ERROR_NONE);
	ret = connection_profile_set_dns_config_type(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV6, CONNECTION_DNS_CONFIG_TYPE_STATIC);
	CHECK_RETURN("connection_profile_set_dns_config_type", ret, CONNECTION_ERROR_NONE);
	ret = connection_profile_set_dns_config_type(profile_temp, CONNECTION_ADDRESS_FAMILY_IPV6, CONNECTION_DNS_CONFIG_TYPE_DYNAMIC);
	CHECK_RETURN("connection_profile_set_dns_config_type", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_set_dns_config_type_n
 * @since_tizen 	4.0
 * @type			Negative
 * @description		connection_profile_set_dns_config_typ should be failed with invalid parameter.
 * @scenario  		Verify connection_profile_get_dns_config_typ by passing invalid parameter.
 */
int utc_connection_profile_set_dns_config_type_n(void)
{
	connection_profile_h profile_inval = NULL;

	if (all_features_not_supported) {
		int ret = connection_profile_set_dns_config_type(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, CONNECTION_DNS_CONFIG_TYPE_DYNAMIC);
		CHECK_RETURN("connection_profile_set_dns_config_type", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	int ret = connection_profile_set_dns_config_type(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, CONNECTION_DNS_CONFIG_TYPE_STATIC);
	CHECK_RETURN("connection_profile_set_dns_config_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_set_dns_config_type(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV6, CONNECTION_DNS_CONFIG_TYPE_STATIC);
	CHECK_RETURN("connection_profile_set_dns_config_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	ret = connection_profile_set_dns_config_type(profile_inval, CONNECTION_ADDRESS_FAMILY_IPV4, CONNECTION_DNS_CONFIG_TYPE_DYNAMIC);
	CHECK_RETURN("connection_profile_set_dns_config_type", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_internet_state_p
 * @since_tizen 	5.5
 * @type		Positive
 * @description		Gets internet state.
 * @scenario  		Verify connection_profile_get_internet_state by passing valid parameter.
 */
int utc_connection_profile_get_internet_state_p(void)
{
	connection_internet_state_e internet_state;

	if (all_features_not_supported) {
		int ret = connection_profile_get_internet_state(profile_wifi, &internet_state);
		CHECK_RETURN("connection_profile_get_internet_state", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	connection_profile_h profile_h = NULL;
	int ret = test_get_any_profile(&profile_h);
	ret = connection_profile_get_internet_state(profile_h, &internet_state);
	CHECK_RETURN("connection_profile_get_internet_state", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_internet_state_n1
 * @since_tizen 	5.5
 * @type		Negative
 * @description		connection_profile_get_internet_state should be failed with invalid parameter.
 * @scenario  		Verify connection_profile_get_internet_state by passing profile as NULL.
 */
int utc_connection_profile_get_internet_state_n1(void)
{
	connection_internet_state_e internet_state;

	if (all_features_not_supported) {
		int ret = connection_profile_get_internet_state(NULL, &internet_state);
		CHECK_RETURN("connection_profile_get_internet_state", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	int ret = connection_profile_get_internet_state(NULL, &internet_state);
	CHECK_RETURN("connection_profile_get_internet_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_get_internet_state_n2
 * @since_tizen 	5.5
 * @type		Negative
 * @description		connection_profile_get_internet_state should be failed with invalid parameter.
 * @scenario  		Verify connection_profile_get_internet_state by passing invalid parameter.
 */
int utc_connection_profile_get_internet_state_n2(void)
{
	if (all_features_not_supported) {
		int ret = connection_profile_get_internet_state(profile_temp, NULL);
		CHECK_RETURN("connection_profile_get_internet_state", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	}

	connection_profile_h profile_h = NULL;
	int ret = test_get_any_profile(&profile_h);
	ret = connection_profile_get_internet_state(profile_h, NULL);
	CHECK_RETURN("connection_profile_get_internet_state", ret, CONNECTION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_connection_profile_destroy_p
 * @since_tizen 	2.3
 * @type		Positive
 * @description		Destroys a profile handle.
 * @scenario  		Invoking connection_profile_destroy with valid parameter.
 */
int utc_connection_profile_destroy_p(void)
{
	int ret = CONNECTION_ERROR_INVALID_PARAMETER;

	if (all_features_not_supported) {
		ret = connection_profile_destroy(profile_temp);
		CHECK_RETURN("connection_profile_destroy", ret, CONNECTION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	test_get_any_profile(&profile_temp);
	assert(profile_temp);
	ret = connection_profile_destroy(profile_temp);
	CHECK_RETURN("connection_profile_destroy", ret, CONNECTION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_connection_profile_destroy_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		connection_profile_destroy should fail with invalid parameter.
 * @scenario  		Verify connection_profile_destroy by passing invalid parameter.
 */
int utc_connection_profile_destroy_n(void)
{
	int ret = connection_profile_destroy(NULL);

	if (all_features_not_supported) {
		CHECK_RETURN("connection_profile_destroy", ret, CONNECTION_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("connection_profile_destroy", ret, CONNECTION_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
