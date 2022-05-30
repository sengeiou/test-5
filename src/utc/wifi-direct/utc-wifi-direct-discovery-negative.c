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

//& set: Wifi-direct-discovery-negative
static bool g_wd_supported_discovery_n = true;


/**
 * @function		utc_wifi_direct_discovery_negative_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_discovery_negative_startup(void)
{
    system_info_get_platform_bool("tizen.org/feature/network.wifi.direct", &g_wd_supported_discovery_n);
    wifi_direct_initialize();
}


/**
 * @function		utc_wifi_direct_discovery_negative_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_discovery_negative_cleanup(void)
{
    wifi_direct_deinitialize();
}

/**
 * @testcase		utc_wifi_direct_start_discovery_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_start_discovery should fail.
 * @scenario  		Invoke wifi_direct_start_discovery with invalid parameters.
 */
int utc_wifi_direct_start_discovery_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_discovery_n == false) {
        ret = wifi_direct_start_discovery(false, 0);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_start_discovery(false, 0);

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_PERMITTED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_cancel_discovery_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_cancel_discovery should fail.
 * @scenario  		Invoke wifi_direct_cancel_discovery when it is not permitted.

 */
int utc_wifi_direct_cancel_discovery_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_discovery_n == false) {
        ret = wifi_direct_cancel_discovery();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_cancel_discovery();

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_PERMITTED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_peer_info_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_get_peer_info should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_get_peer_info by passing NULL as a MAC address and peer_info parameter.
 */
int utc_wifi_direct_get_peer_info_n(void)
{
	int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_discovery_n == false) {
    	ret = wifi_direct_get_peer_info(NULL,NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

	ret = wifi_direct_get_peer_info(NULL,NULL);

	assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_wifi_direct_foreach_discovered_peers_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_foreach_discovered_peers should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_foreach_discovered_peers by passing invalid callback and user_data.
 */
int utc_wifi_direct_foreach_discovered_peers_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_discovery_n == false) {
        ret = wifi_direct_foreach_discovered_peers(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_foreach_discovered_peers(NULL, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_local_wps_type_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_get_local_wps_type should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_get_local_wps_type by passing NULL as a wps (Wi-Fi Protected Setup) type.
 */
int utc_wifi_direct_get_local_wps_type_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_discovery_n == false) {
        ret = wifi_direct_get_local_wps_type(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_local_wps_type(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_req_wps_type_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_set_req_wps_type should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_set_req_wps_type by passing WIFI_DIRECT_WPS_TYPE_NONE as a parameter.
 */
int utc_wifi_direct_set_req_wps_type_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_discovery_n == false) {
        ret = wifi_direct_set_req_wps_type(WIFI_DIRECT_WPS_TYPE_NONE);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_req_wps_type(WIFI_DIRECT_WPS_TYPE_NONE);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_req_wps_type_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_get_req_wps_type should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_get_req_wps_type by passing NULL as a parameter.
 */
int utc_wifi_direct_get_req_wps_type_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_discovery_n == false) {
        ret = wifi_direct_get_req_wps_type(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_req_wps_type(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_is_discoverable_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_is_discoverable should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_is_discoverable by passing NULL as a discoverable.
 */
int utc_wifi_direct_is_discoverable_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_discovery_n == false) {
        ret = wifi_direct_is_discoverable(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_is_discoverable(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_is_listening_only_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_is_listening_only should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_is_listening_only by passing NULL as a listen_only parameter.
 */
int utc_wifi_direct_is_listening_only_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_discovery_n == false) {
        ret = wifi_direct_is_listening_only(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_is_listening_only(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_start_discovery_specific_channel_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_start_discovery_specific_channel should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_start_discovery_specific_channel by passing invalid parameters.
 */
int utc_wifi_direct_start_discovery_specific_channel_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_discovery_n == false) {
        ret = wifi_direct_start_discovery_specific_channel(false, -2, 25);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_start_discovery_specific_channel(false, -2, 25);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_start_discovery_specific_freq_n
 * @since_tizen		4.0
 * @type		Negative
 * @description		wifi_direct_start_discovery_specific_freq should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_start_discovery_specific_freq by passing invalid parameters.
 */
int utc_wifi_direct_start_discovery_specific_freq_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_discovery_n == false) {
        ret = wifi_direct_start_discovery_specific_freq(false, -2, 2412);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_start_discovery_specific_freq(false, -2, 2412);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_peer_display_availability_n
 * @since_tizen		2.4
 * @type		Negative
 * @description		wifi_direct_get_peer_display_availability should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_get_peer_display_availability by passing NULL as a mac_addr and availability parameters.
 */
int utc_wifi_direct_get_peer_display_availability_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;

    bool supported;
    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.display",&supported);
    if(!supported) {
        ret = wifi_direct_get_peer_display_availability(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_peer_display_availability(NULL, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_peer_display_type_n
 * @since_tizen		2.4
 * @type		Negative
 * @description		wifi_direct_get_peer_display_type should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_get_peer_display_type by passing NULL as a mac_addr and type parameters.
 */
int utc_wifi_direct_get_peer_display_type_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;

    bool supported;
    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.display",&supported);
    if(!supported) {
        ret = wifi_direct_get_peer_display_type(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }
    ret = wifi_direct_get_peer_display_type(NULL, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_peer_display_hdcp_n
 * @since_tizen		2.4
 * @type		Negative
 * @description		wifi_direct_get_peer_display_hdcp should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_get_peer_display_hdcp by passing NULL as a mac_addr and HDCP parameters.
 */
int utc_wifi_direct_get_peer_display_hdcp_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;

    bool supported;
    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.display",&supported);
    if(!supported) {
        ret = wifi_direct_get_peer_display_hdcp(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }
    ret = wifi_direct_get_peer_display_hdcp(NULL, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_peer_display_port_n
 * @since_tizen		2.4
 * @type		Negative
 * @description		wifi_direct_get_peer_display_port should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_get_peer_display_port by passing NULL as a MAC address and port.
 */
int utc_wifi_direct_get_peer_display_port_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;

    bool supported;
    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.display",&supported);
    if(!supported) {
        ret = wifi_direct_get_peer_display_port(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }
    ret = wifi_direct_get_peer_display_port(NULL, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_peer_display_throughput_n
 * @since_tizen		2.4
 * @type		Negative
 * @description		wifi_direct_get_peer_display_availability should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_get_peer_display_availability by passing NULL for mac_addr and availability parameter.
 */
int utc_wifi_direct_get_peer_display_throughput_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;

    bool supported;
    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.display",&supported);
    if(!supported) {
        ret = wifi_direct_get_peer_display_throughput(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }
    ret = wifi_direct_get_peer_display_throughput(NULL, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_wifi_direct_get_peer_rssi_n
 * @since_tizen         3.0
 * @type                Negative
 * @description         wifi_direct_get_peer_rssi should fail on invalid parameter.
 * @scenario            Verify wifi_direct_get_peer_rssi by passing NULL for mac_addr and rssi parameter.
 */
int utc_wifi_direct_get_peer_rssi_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;

    bool supported;
    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct",&supported);
    if(!supported) {
        ret = wifi_direct_get_peer_rssi(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }
    ret = wifi_direct_get_peer_rssi(NULL, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_wifi_direct_get_peer_vsie_n_1
 * @since_tizen         5.0
 * @type                Negative
 * @description         wifi_direct_get_peer_vsie should fail on invalid parameter.
 * @scenario            Verify wifi_direct_get_peer_vsie by passing NULL for mac_address parameter.
 */
int utc_wifi_direct_get_peer_vsie_n_1(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    char *vsie = NULL;

    bool supported;
    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct",&supported);
    if(!supported) {
        ret = wifi_direct_get_peer_vsie(NULL, &vsie);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }
    ret = wifi_direct_get_peer_vsie(NULL, &vsie);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase            utc_wifi_direct_get_peer_vsie_n_2
 * @since_tizen         5.0
 * @type                Negative
 * @description         wifi_direct_get_peer_vsie should fail on invalid parameter.
 * @scenario            Verify wifi_direct_get_peer_vsie by passing NULL for vsie parameter.
 */
int utc_wifi_direct_get_peer_vsie_n_2(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    char mac_address[] = "11:11:11:11:11:11";

    bool supported;
    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct",&supported);
    if(!supported) {
        ret = wifi_direct_get_peer_vsie(mac_address, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }
    ret = wifi_direct_get_peer_vsie(mac_address, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}
