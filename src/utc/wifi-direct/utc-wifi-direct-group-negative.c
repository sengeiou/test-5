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
#include "assert.h"
#include <wifi-direct.h>
#include <stdlib.h>
#include <system_info.h>

//& set: Wifi-direct-group-negative
static bool g_wd_supported_group_n = true;


/**
 * @function		utc_wifi_direct_group_negative_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_group_negative_startup(void)
{
    system_info_get_platform_bool("tizen.org/feature/network.wifi.direct", &g_wd_supported_group_n);
    wifi_direct_initialize();
}

/**
 * @function		utc_wifi_direct_group_negative_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_group_negative_cleanup(void)
{
    wifi_direct_deinitialize();
}

/**
 * @testcase		utc_wifi_direct_set_auto_group_removal_n
 * @since_tizen		3.0
 * @type		Negative
 * @description		wifi_direct_set_auto_group_removal should fail on invalid invocation.
 * @scenario  		Invoke wifi_direct_set_auto_group_removal when it is not permitted.
 */
int utc_wifi_direct_set_auto_group_removal_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_set_auto_group_removal(false);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_auto_group_removal(false);

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_PERMITTED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_create_group_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_create_group should fail on invalid invocation.
 * @scenario  		Invoke wifi_direct_create_group when it is not permitted.
 */
int utc_wifi_direct_create_group_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_create_group();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_create_group();

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_PERMITTED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_destroy_group_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_destroy_group should fail on invalid invocation.
 * @scenario  		Invoke wifi_direct_destroy_group when it is not permitted.
 */
int utc_wifi_direct_destroy_group_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_destroy_group();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_destroy_group();

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_PERMITTED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_is_group_owner_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_is_group_owner should fail with NULL parameter.
 * @scenario  		Verify wifi_direct_is_group_owner by passing NULL as a parameter.
 */
int utc_wifi_direct_is_group_owner_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_is_group_owner(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_is_group_owner(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_is_autonomous_group_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_is_autonomous_group should fail with NULL parameter.
 * @scenario  		Verify wifi_direct_is_autonomous_group by passing NULL as a parameter.
 */
int utc_wifi_direct_is_autonomous_group_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_is_autonomous_group(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_is_autonomous_group(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_group_owner_intent_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_get_group_owner_intent should fail with NULL parameter.
 * @scenario  		Verify wifi_direct_get_group_owner_intent by passing NULL as a parameter.
 */
int utc_wifi_direct_get_group_owner_intent_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_get_group_owner_intent(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_group_owner_intent(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_group_owner_intent_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_set_group_owner_intent should fail by passing invalid value as a parameter.
 * @scenario  		Invoke wifi_direct_set_group_owner_intent with invalid parameter.
 */
int utc_wifi_direct_set_group_owner_intent_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_set_group_owner_intent(20);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_group_owner_intent(20);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_max_clients_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_get_max_clients should fail with NULL parameter.
 * @scenario  		Verify wifi_direct_get_max_clients by passing NULL as a parameter.
 */
int utc_wifi_direct_get_max_clients_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_get_max_clients(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_max_clients(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_max_clients_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_set_max_clients should fail with invalid parameter.
 * @scenario  		Invoke wifi_direct_set_max_clients with invalid parameter.
 */
int utc_wifi_direct_set_max_clients_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_set_max_clients(0);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_max_clients(0);

    assert_eq(ret, WIFI_DIRECT_ERROR_OPERATION_FAILED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_passphrase_n
 * @since_tizen		2.4
 * @type		Negative
 * @description		wifi_direct_set_passphrase should fail with NULL parameter.
 * @scenario  		Verify wifi_direct_set_passphrase by passing NULL as a parameter.
 */
int utc_wifi_direct_set_passphrase_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_set_passphrase(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_passphrase(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_passphrase_n
 * @since_tizen		2.4
 * @type		Negative
 * @description		wifi_direct_get_passphrase should fail with NULL parameter.
 * @scenario  		Verify wifi_direct_get_passphrase by passing NULL as a parameter.
 */
int utc_wifi_direct_get_passphrase_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_set_passphrase(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_passphrase(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_persistent_group_enabled_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_set_persistent_group_enabled should fail with NULL parameter.
 * @scenario  		Verify wifi_direct_set_persistent_group_enabled by passing NULL as a parameter.
 */
int utc_wifi_direct_set_persistent_group_enabled_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_set_persistent_group_enabled(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    wifi_direct_deinitialize();

    ret = wifi_direct_set_persistent_group_enabled(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_foreach_persistent_groups_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_foreach_persistent_groups should fail with NULL parameter.
 * @scenario  		Verify wifi_direct_foreach_persistent_groups by passing NULL as a parameter.
 */
int utc_wifi_direct_foreach_persistent_groups_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_foreach_persistent_groups(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_foreach_persistent_groups(NULL, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_is_persistent_group_enabled_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_is_persistent_group_enabled should fail with NULL parameter.
 * @scenario  		Verify wifi_direct_is_persistent_group_enabled by passing NULL as a parameter.
 */
int utc_wifi_direct_is_persistent_group_enabled_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_is_persistent_group_enabled(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_is_persistent_group_enabled(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_subnet_mask_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_get_subnet_mask should fail with NULL parameter.
 * @scenario  		Verify wifi_direct_get_subnet_mask by passing NULL as a parameter.
 */
int utc_wifi_direct_get_subnet_mask_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_get_subnet_mask(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_subnet_mask(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_operating_channel_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_get_operating_channel should fail with NULL parameter.
 * @scenario  		Verify wifi_direct_get_operating_channel by passing NULL as a parameter.
 */
int utc_wifi_direct_get_operating_channel_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_get_operating_channel(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_operating_channel(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_ip_address_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_get_ip_address should fail with NULL parameter.
 * @scenario  		Verify wifi_direct_get_ip_address by passing NULL as a parameter.
 */
int utc_wifi_direct_get_ip_address_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_get_ip_address(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_ip_address(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_gateway_address_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_get_gateway_address should fail with NULL parameter.
 * @scenario  		Verify wifi_direct_get_gateway_address by passing NULL as a parameter.
 */
int utc_wifi_direct_get_gateway_address_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_get_gateway_address(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_gateway_address(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_network_interface_name_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_get_network_interface_name should fail with NULL parameter.
 * @scenario  		Verify wifi_direct_get_network_interface_name by passing NULL as a parameter.
 */
int utc_wifi_direct_get_network_interface_name_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_get_network_interface_name(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_network_interface_name(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_remove_persistent_group_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_remove_persistent_group should fail with NULL parameter.
 * @scenario  		Verify wifi_direct_remove_persistent_group by passing NULL as a parameter.
 */
int utc_wifi_direct_remove_persistent_group_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_remove_persistent_group(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_remove_persistent_group(NULL, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_create_group_with_ssid_n
 * @since_tizen		5.0
 * @type		Negative
 * @description		wifi_direct_create_group_with_ssid should fail on invalid invocation.
 * @scenario  		Invoke wifi_direct_create_group_with_ssid when it is not permitted.
 */
int utc_wifi_direct_create_group_with_ssid_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_create_group_with_ssid(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_create_group_with_ssid(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_remove_persistent_device_n
 * @since_tizen		5.0
 * @type		Negative
 * @description		wifi_direct_remove_persistent_device should fail with NULL parameter.
 * @scenario  		Verify wifi_direct_remove_persistent_device by passing NULL as a parameter.
 */
int utc_wifi_direct_remove_persistent_device_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_remove_persistent_device(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_remove_persistent_device(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_remove_all_persistent_devices_n
 * @since_tizen		5.0
 * @type		Negative
 * @description		wifi_direct_remove_all_persistent_devices should fail on invalid invocation.
 * @scenario  		Invoke wifi_direct_remove_all_persistent_devices when it is not permitted.
 */
int utc_wifi_direct_remove_all_persistent_devices_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_remove_all_persistent_devices();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_remove_all_persistent_devices();

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_PERMITTED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_go_intent_per_type_n
 * @since_tizen		5.0
 * @type		Negative
 * @description		wifi_direct_set_go_intent_per_type should fail by passing invalid value as a parameter.
 * @scenario  		Invoke wifi_direct_set_go_intent_per_type with invalid parameter.
 */
int utc_wifi_direct_set_go_intent_per_type_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_set_go_intent_per_type(1, 20);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_go_intent_per_type(1, 20);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_go_intent_per_type_n
 * @since_tizen		5.0
 * @type		Negative
 * @description		wifi_direct_get_go_intent_per_type should fail with NULL parameter.
 * @scenario  		Verify wifi_direct_get_go_intent_per_type by passing NULL as a parameter.
 */
int utc_wifi_direct_get_go_intent_per_type_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_n == false) {
        ret = wifi_direct_get_go_intent_per_type(1, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_go_intent_per_type(1, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}
