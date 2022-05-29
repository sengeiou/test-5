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

//& set: Wifi-direct-connection-positive

static GMainLoop* loop = NULL;
static bool activated_callback = false;
static bool g_wd_supported_connection_p = true;

/**
 * @function		utc_wifi_direct_connection_positive_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_connection_positive_startup(void)
{
    system_info_get_platform_bool("tizen.org/feature/network.wifi.direct", &g_wd_supported_connection_p);
    wifi_direct_initialize();
}


/**
 * @function		utc_wifi_direct_connection_positive_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_connection_positive_cleanup(void)
{
    wifi_direct_deactivate();

    wifi_direct_deinitialize();
}

static gboolean testcase_timeout(gpointer data)
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
        activated_callback = true;
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
				timeout_testcase = g_timeout_add(20000, testcase_timeout, loop);
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

bool _connected_peers_impl_cb(wifi_direct_connected_peer_info_s* peer, void* user_data)
{
    return true;
}

/**
 * @testcase		utc_wifi_direct_connect_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Connects to a specified peer, asynchronous.
 * @scenario  		Invoking wifi_direct_connect with proper MAC address should connect to peer.
 */
int utc_wifi_direct_connect_p(void)
{
    char *mac_address = "94:63:D1:02:AB:52";
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_connection_p == false) {
        ret = wifi_direct_connect(mac_address);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_connect(mac_address);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_wps_pin_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Sets or updates the WPS (Wi-Fi Protected Setup) PIN number user expects.
 * @scenario  		Verify wifi_direct_set_wps_pin by passing valid PIN.
 */
int utc_wifi_direct_set_wps_pin_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    char *pin = "12345678";
    if(g_wd_supported_connection_p == false) {
        ret = wifi_direct_set_wps_pin(pin);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_wps_pin(pin);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}
