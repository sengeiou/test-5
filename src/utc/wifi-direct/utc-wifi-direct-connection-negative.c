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

//& set: Wifi-direct-connection-negative
static bool g_wd_supported_connection_n = true;


/**
 * @function		utc_wifi_direct_connection_negative_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_connection_negative_startup(void)
{
    system_info_get_platform_bool("tizen.org/feature/network.wifi.direct", &g_wd_supported_connection_n);

    wifi_direct_initialize();
}

/**
 * @function		utc_wifi_direct_connection_negative_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_connection_negative_cleanup(void)
{
    wifi_direct_deinitialize();
}

/**
 * @testcase		utc_wifi_direct_connect_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_connect should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_connect by passing invalid MAC address as a parameter.
*/
int utc_wifi_direct_connect_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_connection_n == false) {
        ret = wifi_direct_connect(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_connect(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_wps_pin_n
 * @since_tizen 	2.3
 * @type		Negative
 * @description		Verify wifi_direct_set_wps_pin by passing invalid PIN as a parameter.
 * @scenario  		Do not Establish WPS (Wi-Fi Protected Setup) connection.
*/
int utc_wifi_direct_set_wps_pin_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_connection_n == false) {
        ret = wifi_direct_set_wps_pin(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_wps_pin(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_foreach_connected_peers_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Verify wifi_direct_foreach_connected_peers by passing NULL as a parameter.
 * @scenario  		Should not display information about peers.
 */
int utc_wifi_direct_foreach_connected_peers_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_connection_n == false) {
        ret = wifi_direct_foreach_connected_peers(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_foreach_connected_peers(NULL, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_wps_pin_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_get_wps_pin should not return any WPS PIN.
 * @scenario  		Invoke wifi_direct_get_wps_pin when it is not permitted.
 */
int utc_wifi_direct_get_wps_pin_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_connection_n == false) {
        ret = wifi_direct_get_wps_pin(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_wps_pin(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_disconnect_all_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_disconnect_all should fail.
 * @scenario  		Invoke wifi_direct_disconnect_all when it is not permitted.
 */
int utc_wifi_direct_disconnect_all_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_connection_n == false) {
        ret = wifi_direct_disconnect_all();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_disconnect_all();

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_PERMITTED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_disconnect_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_disconnect should fail with invalid parameter.
 * @scenario  		Invoke wifi_direct_disconnect with NULL parameter.
 */
int utc_wifi_direct_disconnect_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_connection_n == false) {
        ret = wifi_direct_disconnect(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_disconnect(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_cancel_connection_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_cancel_connection should fail when it is a invalid parameter.	
 * @scenario  		Verify wifi_direct_cancel_connection by passing NULL as a parameter.
 */
int utc_wifi_direct_cancel_connection_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_connection_n == false) {
        ret = wifi_direct_cancel_connection(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_cancel_connection(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_activate_pushbutton_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Should not set the WPS config PBC (Push Button Configuration) as preferred method for connection.
 * @scenario  		Invoke wifi_direct_activate_pushbutton when it is not permitted.
 */
int utc_wifi_direct_activate_pushbutton_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_connection_n == false) {
        ret = wifi_direct_activate_pushbutton();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_activate_pushbutton();

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_PERMITTED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_connecting_peer_info_n
 * @since_tizen		4.0
 * @type		Negative
 * @description		wifi_direct_get_connecting_peer_info should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_get_connecting_peer_info by passing NULL as a parameter.
*/
int utc_wifi_direct_get_connecting_peer_info_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_connection_n == false) {
        ret = wifi_direct_get_connecting_peer_info(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_connecting_peer_info(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}
