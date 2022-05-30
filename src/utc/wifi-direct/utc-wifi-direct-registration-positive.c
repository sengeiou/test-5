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

//& set: Wifi-direct-registration-positive
static bool g_wd_supported_registration_p = true;

/**
 * @function		utc_wifi_direct_registration_positive_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_registration_positive_startup(void)
{
    system_info_get_platform_bool("tizen.org/feature/network.wifi.direct", &g_wd_supported_registration_p);
    wifi_direct_initialize();
}

/**
 * @function		utc_wifi_direct_registration_positive_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_registration_positive_cleanup(void)
{
    wifi_direct_deinitialize();
}

static void _device_state_changed_cb(int error_code, wifi_direct_device_state_e device_state, void *user_data)
{
    return;
}

static void _discovery_state_changed_cb(int error_code, wifi_direct_discovery_state_e discovery_state, void *user_data)
{
    return;
}


static void _connection_state_changed_cb(int error_code, wifi_direct_connection_state_e connection_state, const char* mac_address, void *user_data)
{
    return;
}

static void _peer_info_connection_state_changed_cb(int error_code, wifi_direct_connection_state_e connection_state, wifi_direct_connection_state_cb_data_s data_s, void *user_data)
{
    return;
}

static void _cb_ip_assigned(const char* mac_address, const char* ip_address, const char* interface_address, void *user_data)
{
}

static void _cb_peer_found(int error_code, wifi_direct_discovery_state_e discovery_state, const char *mac_address, void *user_data)
{
	return;
}

static void _service_state_changed_cb(int error_code,
    wifi_direct_service_discovery_state_e discovery_state,
    wifi_direct_service_type_e service_type,
    void *response_data, const char * mac_address, void *user_data)
{
}

static void _cb_state_chanaged(wifi_direct_state_e state, void *user_data)
{
	return;
}

/**
 * @testcase		utc_wifi_direct_initialize_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Initializes Wi-Fi Direct service.
 * @scenario  		Verify wifi_direct_initialize.
 */
int utc_wifi_direct_initialize_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_p == false) {
        ret = wifi_direct_initialize();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_deinitialize();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_initialize();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_device_state_changed_cb_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Registers the callback called when the state of device is changed.
 * @scenario  		Verify wifi_direct_set_device_state_changed_cb.
 */
int utc_wifi_direct_set_device_state_changed_cb_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_p == false) {
        ret = wifi_direct_set_device_state_changed_cb(_device_state_changed_cb, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_device_state_changed_cb(_device_state_changed_cb, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_unset_device_state_changed_cb_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Unregisters the callback called when the state of device is changed.
 * @scenario  		Verify wifi_direct_unset_device_state_changed_cb.
 */
int utc_wifi_direct_unset_device_state_changed_cb_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_p == false) {
        ret = wifi_direct_unset_device_state_changed_cb();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_unset_device_state_changed_cb();

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_discovery_state_changed_cb_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Registers the callback called when the state of discovery is changed.
 * @scenario  		Register the discovery state changed callback.
 */
int utc_wifi_direct_set_discovery_state_changed_cb_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_p == false) {
        ret = wifi_direct_set_discovery_state_changed_cb(_discovery_state_changed_cb, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_discovery_state_changed_cb(_discovery_state_changed_cb, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_unset_discovery_state_changed_cb_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Unregisters the callback called when the state of discovery is changed.
 * @scenario  		Unregister the discovery state changed callback.
 */
int utc_wifi_direct_unset_discovery_state_changed_cb_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_p == false) {
        ret = wifi_direct_unset_discovery_state_changed_cb();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_unset_discovery_state_changed_cb();

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_connection_state_changed_cb_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Registers the callback called when the state of connection is changed.
 * @scenario  		Register the connection state changed callback.
 */
int utc_wifi_direct_set_connection_state_changed_cb_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_p == false) {
        ret = wifi_direct_set_connection_state_changed_cb(_connection_state_changed_cb, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_connection_state_changed_cb(_connection_state_changed_cb, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_unset_connection_state_changed_cb_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Unregisters the callback called when the state of connection is changed.
 * @scenario  		Unregister the connection state changed callback.
 */
int utc_wifi_direct_unset_connection_state_changed_cb_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_p == false) {
        ret = wifi_direct_unset_connection_state_changed_cb();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_unset_connection_state_changed_cb();

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_peer_info_connection_state_changed_cb_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Registers the callback called when the peer info connecion state is changed.
 * @scenario  		Register the peer info connection state changed callback.
 */
int utc_wifi_direct_set_peer_info_connection_state_changed_cb_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_p == false) {
        ret = wifi_direct_set_peer_info_connection_state_changed_cb(_peer_info_connection_state_changed_cb, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_peer_info_connection_state_changed_cb(_peer_info_connection_state_changed_cb, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_unset_peer_info_connection_state_changed_cb_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Unregisters the callback called when the peer info conection state is changed.
 * @scenario  		Unregister the peer info connection state changed callback.
 */
int utc_wifi_direct_unset_peer_info_connection_state_changed_cb_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_p == false) {
        ret = wifi_direct_unset_peer_info_connection_state_changed_cb();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_unset_peer_info_connection_state_changed_cb();

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_deinitialize_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Deinitializes Wi-Fi Direct service.
 * @scenario  		Deinitialize Wi-Fi Direct service.
 */
int utc_wifi_direct_deinitialize_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_p == false) {
        ret = wifi_direct_deinitialize();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_deinitialize();

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_service_state_changed_cb_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Registers the callback called when the state of the service discovery is changed.
 * @scenario  		Register callback on service discovery state change.
 */
int utc_wifi_direct_set_service_state_changed_cb_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_p == false) {
        ret = wifi_direct_set_service_state_changed_cb(_service_state_changed_cb, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    bool supported;

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.service_discovery",&supported);
    if(!supported) {
        ret = wifi_direct_set_service_state_changed_cb(_service_state_changed_cb, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_service_state_changed_cb(_service_state_changed_cb, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_unset_service_state_changed_cb_p
 * @since_tizen		2.3
 * @type		positive
 * @description	 	Unregisters the callback called when the state of the service discovery is changed.
 * @scenario  		Unregister callback on service discovery state change.
 */
int utc_wifi_direct_unset_service_state_changed_cb_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_p == false) {
        ret = wifi_direct_unset_service_state_changed_cb();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    bool supported;

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.service_discovery",&supported);
    if(!supported) {
        ret = wifi_direct_unset_service_state_changed_cb();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_unset_service_state_changed_cb();

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_client_ip_address_assigned_cb_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Registers the callback called when the IP address of the client is assigned if your device is the group owner.
 * @scenario  		Verify wifi_direct_set_client_ip_address_assigned_cb when client IP address is assigned.
 */
int utc_wifi_direct_set_client_ip_address_assigned_cb_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_p == false) {
        ret = wifi_direct_set_client_ip_address_assigned_cb(_cb_ip_assigned, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_client_ip_address_assigned_cb(_cb_ip_assigned, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_unset_client_ip_address_assigned_cb_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Unregisters the callback called when the IP address of the client is assigned if your device is the group owner.
 * @scenario  		Verify wifi_direct_unset_client_ip_address_assigned_cb when client IP address is assigned.
 */
int utc_wifi_direct_unset_client_ip_address_assigned_cb_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_p == false) {
        ret = wifi_direct_unset_client_ip_address_assigned_cb();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_unset_client_ip_address_assigned_cb();

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_peer_found_cb_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Registers the callback called when the peer is found.
 * @scenario  		Verify wifi_direct_set_peer_found_cb.
 */
int utc_wifi_direct_set_peer_found_cb_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_p == false) {
        ret = wifi_direct_set_peer_found_cb(_cb_peer_found, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_peer_found_cb(_cb_peer_found, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_unset_peer_found_cb_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Unregisters the callback called when the peer is found.
 * @scenario  		Verify wifi_direct_unset_peer_found_cb.
 */
int utc_wifi_direct_unset_peer_found_cb_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_registration_p == false) {
        ret = wifi_direct_unset_peer_found_cb();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_unset_peer_found_cb();

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}


/**
 * @testcase		utc_wifi_direct_set_state_changed_cb_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Registers the callback called called when the state is changed.
 * @scenario  		Verify wifi_direct_set_state_changed_cb.
 */
int utc_wifi_direct_set_state_changed_cb_p(void)
{
	int ret = WIFI_DIRECT_ERROR_NONE;
	if(g_wd_supported_registration_p == false) {
        ret = wifi_direct_set_state_changed_cb(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }
	ret = wifi_direct_set_state_changed_cb(_cb_state_chanaged, NULL);
	assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

	wifi_direct_unset_state_changed_cb();
	return 0;
}


/**
 * @testcase		utc_wifi_direct_unset_state_changed_cb_p
 * @since_tizen		3.0
 * @type		Negative
 * @description		wifi_direct_set_state_changed_cb should deregisters the callback called when the state is changed.
 * @scenario  		Verify wifi_direct_unset_state_changed_cb.
 */
int utc_wifi_direct_unset_state_changed_cb_p(void)
{
	int ret = WIFI_DIRECT_ERROR_NONE;
	if(g_wd_supported_registration_p == false) {
		ret = wifi_direct_unset_state_changed_cb();
		assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
		return 0;
	}
	ret = wifi_direct_set_state_changed_cb(_cb_state_chanaged, NULL);
	assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

	ret = wifi_direct_unset_state_changed_cb();
	assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

	return 0;
}
