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

//& set: Wifi-direct-registration-negative
static bool g_wd_supported_registration_n = true;


/**
 * @function		utc_wifi_direct_registration_negative_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_registration_negative_startup(void)
{
    system_info_get_platform_bool("tizen.org/feature/network.wifi.direct", &g_wd_supported_registration_n);
	wifi_direct_deinitialize();
}

/**
 * @function		utc_wifi_direct_registration_negative_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_registration_negative_cleanup(void)
{
	wifi_direct_deinitialize();
}

/**
 * @testcase		utc_wifi_direct_initialize_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_initialize should fail on invoking it twice.
 * @scenario  		Verify wifi_direct_initialize by invoking it twice.
 */
int utc_wifi_direct_initialize_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_n == false) {
        ret = wifi_direct_initialize();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_initialize();

    ret = wifi_direct_initialize();
    assert_eq(ret, WIFI_DIRECT_ERROR_ALREADY_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_deinitialize_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_deinitialize should fail if it is not initialized.
 * @scenario  		Verify wifi_direct_deinitialize.
 */
int utc_wifi_direct_deinitialize_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_n == false) {
        ret = wifi_direct_deinitialize();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_deinitialize();

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_device_state_changed_cb_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_set_device_state_changed_cb should fail with invalid parameters.
 * @scenario  		Verify wifi_direct_set_device_state_changed_cb by passing NULL parameters.
 */
int utc_wifi_direct_set_device_state_changed_cb_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_n == false) {
        ret = wifi_direct_set_device_state_changed_cb(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_device_state_changed_cb(NULL, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_unset_device_state_changed_cb_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_unset_device_state_changed_cb should not unregisters the callback called when the state of device is changed.
 * @scenario  		Verify wifi_direct_unset_device_state_changed_cb.
 */
int utc_wifi_direct_unset_device_state_changed_cb_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_n == false) {
        ret = wifi_direct_unset_device_state_changed_cb();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_unset_device_state_changed_cb();

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_discovery_state_changed_cb_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_set_discovery_state_changed_cb should not register the callback called when the state of discovery is changed.
 * @scenario  		Verify wifi_direct_set_discovery_state_changed_cb by invoking it with NULL parameters.
 */
int utc_wifi_direct_set_discovery_state_changed_cb_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_n == false) {
        ret = wifi_direct_set_discovery_state_changed_cb(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_discovery_state_changed_cb(NULL, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_unset_discovery_state_changed_cb_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_unset_discovery_state_changed_cb should not unregister the callback called when the state of discovery is changed.
 * @scenario  		Verify wifi_direct_unset_discovery_state_changed_cb.
 */
int utc_wifi_direct_unset_discovery_state_changed_cb_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_n == false) {
        ret = wifi_direct_unset_discovery_state_changed_cb();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_unset_discovery_state_changed_cb();

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_connection_state_changed_cb_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_set_connection_state_changed_cb should fail with invalid parameters.
 * @scenario  		Verify wifi_direct_set_connection_state_changed_cb by invoking it with NULL parameters.
 */
int utc_wifi_direct_set_connection_state_changed_cb_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_n == false) {
        ret = wifi_direct_set_connection_state_changed_cb(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_connection_state_changed_cb(NULL, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_unset_connection_state_changed_cb_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_unset_connection_state_changed_cb should not unregister the callback called when the state of connection is changed.
 * @scenario  		Verify wifi_direct_unset_connection_state_changed_cb.
 */
int utc_wifi_direct_unset_connection_state_changed_cb_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_n == false) {
        ret = wifi_direct_unset_connection_state_changed_cb();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_unset_connection_state_changed_cb();

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_peer_info_connection_state_changed_cb_n
 * @since_tizen		5.0
 * @type		Negative
 * @description		wifi_direct_set_peer_info_connection_state_changed_cb should fail with invalid parameters.
 * @scenario  		Verify wifi_direct_set_peer_info_connection_state_changed_cb by invoking it with NULL parameters.
 */
int utc_wifi_direct_set_peer_info_connection_state_changed_cb_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_n == false) {
        ret = wifi_direct_set_peer_info_connection_state_changed_cb(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_peer_info_connection_state_changed_cb(NULL, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_unset_peer_info_connection_state_changed_cb_n
 * @since_tizen		5.0
 * @type		Negative
 * @description		wifi_direct_unset_peer_info_connection_state_changed_cb should not unregister the callback called when the peer info state of connection is changed.
 * @scenario  		Verify wifi_direct_unset_peer_info_connection_state_changed_cb.
 */
int utc_wifi_direct_unset_peer_info_connection_state_changed_cb_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_n == false) {
        ret = wifi_direct_unset_peer_info_connection_state_changed_cb();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_unset_peer_info_connection_state_changed_cb();

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_service_state_changed_cb_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_set_service_state_changed_cb should fail with invalid parameters.
 * @scenario  		Verify wifi_direct_set_service_state_changed_cb by invoking it with NULL parameters.
 */
int utc_wifi_direct_set_service_state_changed_cb_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool supported;
    if(g_wd_supported_registration_n == false) {
        ret = wifi_direct_set_service_state_changed_cb(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.service_discovery",&supported);
    if(!supported) {
        ret = wifi_direct_set_service_state_changed_cb(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_service_state_changed_cb(NULL, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_unset_service_state_changed_cb_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_unset_service_state_changed_cb should not unregister the callback called when the state of the service discovery is changed.
 * @scenario  		Verify wifi_direct_unset_service_state_changed_cb.
 */
int utc_wifi_direct_unset_service_state_changed_cb_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool supported;
    if(g_wd_supported_registration_n == false) {
        ret = wifi_direct_unset_service_state_changed_cb();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.service_discovery",&supported);
    if(!supported) {
        ret = wifi_direct_unset_service_state_changed_cb();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_unset_service_state_changed_cb();

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_client_ip_address_assigned_cb_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_set_client_ip_address_assigned_cb should fail with invalid parameters.
 * @scenario  		Verify wifi_direct_set_client_ip_address_assigned_cb by invoking it with NULL parameters.
 */
int utc_wifi_direct_set_client_ip_address_assigned_cb_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_n == false) {
        ret = wifi_direct_set_client_ip_address_assigned_cb(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_client_ip_address_assigned_cb(NULL, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_unset_client_ip_address_assigned_cb_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_unset_client_ip_address_assigned_cb should not unregisters the callback called when the IP address of the client is assigned if your                         device is the group owner.
 * @scenario  		Verify wifi_direct_unset_client_ip_address_assigned_cb.
 */
int utc_wifi_direct_unset_client_ip_address_assigned_cb_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool supported;
    if(g_wd_supported_registration_n == false) {
        ret = wifi_direct_unset_client_ip_address_assigned_cb();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.service_discovery",&supported);
    if(!supported) {
        ret = wifi_direct_unset_service_state_changed_cb();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_unset_client_ip_address_assigned_cb();

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_peer_found_cb_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_set_peer_found_cb should not registers the callback called when the peer is found.
 * @scenario  		Verify wifi_direct_set_peer_found_cb.
 */
int utc_wifi_direct_set_peer_found_cb_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_n == false) {
        ret = wifi_direct_set_peer_found_cb(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_peer_found_cb(NULL, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_unset_peer_found_cb_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_unset_peer_found_cb should not unregisters the callback called when the peer is found.
 * @scenario  		Verify wifi_direct_unset_peer_found_cb.
 */
int utc_wifi_direct_unset_peer_found_cb_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_n == false) {
        ret = wifi_direct_unset_peer_found_cb();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_unset_peer_found_cb();

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_state_changed_cb_n
 * @since_tizen		3.0
 * @type		Negative
 * @description		wifi_direct_set_state_changed_cb should not registers the callback called when the state is changed.
 * @scenario  		Verify wifi_direct_set_state_changed_cb.
 */
int utc_wifi_direct_set_state_changed_cb_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_n == false) {
        ret = wifi_direct_set_state_changed_cb(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_state_changed_cb(NULL, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_unset_state_changed_cb_n
 * @since_tizen		3.0
 * @type		Negative
 * @description		wifi_direct_unset_state_changed_cb should not deregisters the callback called when the state is changed.
 * @scenario  		Verify wifi_direct_unset_state_changed_cb.
 */
int utc_wifi_direct_unset_state_changed_cb_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_n == false) {
        ret = wifi_direct_unset_state_changed_cb();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_unset_state_changed_cb();

    assert_eq(ret, WIFI_DIRECT_ERROR_OPERATION_FAILED);

    return 0;
}
