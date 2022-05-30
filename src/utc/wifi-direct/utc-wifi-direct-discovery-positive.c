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
#include <glib.h>
#include <system_info.h>

//& set: Wifi-direct-discovery-positive

static GMainLoop* loop = NULL;
static bool activated_callback = false;
static bool g_wd_supported_discovery_p = true;

/**
 * @function		utc_wifi_direct_discovery_positive_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_discovery_positive_startup(void)
{
    system_info_get_platform_bool("tizen.org/feature/network.wifi.direct", &g_wd_supported_discovery_p);
    wifi_direct_initialize();
}


/**
 * @function		utc_wifi_direct_discovery_positive_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_discovery_positive_cleanup(void)
{
    wifi_direct_deactivate();

    wifi_direct_deinitialize();
}

static gboolean activate_timeout(gpointer data)
{
    activated_callback = false;
    g_main_loop_quit(loop);
    g_main_loop_unref(loop);
    loop = NULL;
    return FALSE;
}

static void wifi_activated_callback(wifi_direct_error_e error_code,
        wifi_direct_device_state_e device_state,
        void *user_data)
{
    if (WIFI_DIRECT_ERROR_NONE == error_code && WIFI_DIRECT_DEVICE_STATE_ACTIVATED == device_state) {
        activated_callback= true;
        g_main_loop_quit(loop);
        g_main_loop_unref(loop);
    }
}

static int wait_for_activate_callback(void)
{
	wifi_direct_state_e state;
	int timeout_testcase = 0;
	int ret;

	ret = wifi_direct_set_device_state_changed_cb(wifi_activated_callback, NULL);
	if (WIFI_DIRECT_ERROR_NONE == ret)
	{
		ret = wifi_direct_get_state(&state);
		if(ret == WIFI_DIRECT_ERROR_NONE && state < WIFI_DIRECT_STATE_ACTIVATING)
		{
			ret = wifi_direct_activate();

			if (WIFI_DIRECT_ERROR_NONE == ret)
			{
				loop = g_main_loop_new(NULL, FALSE);
				timeout_testcase = g_timeout_add(20000, activate_timeout, loop);
				g_main_loop_run(loop);
				g_source_remove(timeout_testcase);
				wifi_direct_unset_device_state_changed_cb();

				if (!activated_callback)
				{
					ret = -1;
				}
			}
		}
	}
	return ret;
}

bool _discovered_peers_impl_cb(wifi_direct_discovered_peer_info_s* peer, void* user_data)
{
    return true;
}

/**
 * @testcase		utc_wifi_direct_start_discovery_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Starts discovery to find all P2P capable devices, asynchronous.
 * @scenario  		Discover P2P devices.
 */
int utc_wifi_direct_start_discovery_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_discovery_p == false) {
        ret = wifi_direct_start_discovery(0, 0);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    bool supported;

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.service_discovery",&supported);
    if(!supported) return 0;

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_start_discovery(0, 0);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_cancel_discovery_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Cancels discovery process, asynchronous.
 * @scenario  		Verify wifi_direct_cancel_discovery.
 */
int utc_wifi_direct_cancel_discovery_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_discovery_p == false) {
        ret = wifi_direct_cancel_discovery();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    bool supported;

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.service_discovery",&supported);
    if(!supported) return 0;

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_cancel_discovery();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_foreach_discovered_peers_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Gets the information of discovered peers.
 * @scenario  		Verify wifi_direct_foreach_discovered_peers.
 */
int utc_wifi_direct_foreach_discovered_peers_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_discovery_p == false) {
        ret = wifi_direct_foreach_discovered_peers(_discovered_peers_impl_cb, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_foreach_discovered_peers(_discovered_peers_impl_cb, NULL);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_local_wps_type_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Gets the WPS (Wi-Fi Protected Setup) type.
 * @scenario  		Invoke wifi_direct_get_local_wps_type.
 */
int utc_wifi_direct_get_local_wps_type_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    wifi_direct_wps_type_e type = 0;
    if(g_wd_supported_discovery_p == false) {
        ret = wifi_direct_get_local_wps_type(&type);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_local_wps_type(&type);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_req_wps_type_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Sets the requested WPS (Wi-Fi Protected Setup) type.
 * @scenario  		Invoke wifi_direct_set_req_wps_type with valid wps_type.
 */
int utc_wifi_direct_set_req_wps_type_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    wifi_direct_wps_type_e type = WIFI_DIRECT_WPS_TYPE_PBC;
    if(g_wd_supported_discovery_p == false) {
        ret = wifi_direct_set_req_wps_type(type);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_req_wps_type(type);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_req_wps_type_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Gets the requested WPS (Wi-Fi Protected Setup) type.
 * @scenario  		Invoke wifi_direct_get_req_wps_type.
 */
int utc_wifi_direct_get_req_wps_type_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    wifi_direct_wps_type_e type = WIFI_DIRECT_WPS_TYPE_PBC;
    if(g_wd_supported_discovery_p == false) {
        ret = wifi_direct_get_req_wps_type(&type);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_req_wps_type(&type);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_is_discoverable_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Checks whether this device is discoverable or not by P2P discovery.
 * @scenario  		Invoke wifi_direct_is_discoverable.
 */
int utc_wifi_direct_is_discoverable_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool discoverable = false;
    if(g_wd_supported_discovery_p == false) {
        ret = wifi_direct_is_discoverable(&discoverable);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_is_discoverable(&discoverable);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_is_listening_only_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Checks whether the local device is listening only.
 * @scenario  		Invoke wifi_direct_is_listening_only.
 */
int utc_wifi_direct_is_listening_only_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool listen_only = false;
    if(g_wd_supported_discovery_p == false) {
        ret = wifi_direct_is_listening_only(&listen_only);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_is_listening_only(&listen_only);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_start_discovery_specific_channel_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Starts discovery to find all P2P capable devices with specified channel, asynchronous.
 * @scenario  		Invoke wifi_direct_start_discovery_specific_channel with valid parameters.
 */
int utc_wifi_direct_start_discovery_specific_channel_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool listen_only = false;
    int timeout = 10;
    wifi_direct_discovery_channel_e channel = WIFI_DIRECT_DISCOVERY_CHANNEL1;
    if(g_wd_supported_discovery_p == false) {
        ret = wifi_direct_start_discovery_specific_channel(listen_only, timeout, channel);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_start_discovery_specific_channel(listen_only, timeout, channel);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_start_discovery_specific_freq_p
 * @since_tizen		4.0
 * @type		positive
 * @description		Starts discovery to find all P2P capable devices using specified frequency, asynchronous.
 * @scenario  		Invoke wifi_direct_start_discovery_specific_freq with valid parameters.
 */
int utc_wifi_direct_start_discovery_specific_freq_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool listen_only = false;
    int timeout = 10;
    int frequency = 2412;

    if(g_wd_supported_discovery_p == false) {
        ret = wifi_direct_start_discovery_specific_freq(listen_only, timeout,
							frequency);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_start_discovery_specific_freq(listen_only, timeout,
						    frequency);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}
