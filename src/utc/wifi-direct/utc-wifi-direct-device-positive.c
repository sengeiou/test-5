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

//& set: Wifi-direct-device-positive

static GMainLoop* loop = NULL;
static bool activated_callback = false;
static bool g_wd_supported_device_p = true;

/**
 * @function		utc_wifi_direct_device_positive_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_device_positive_startup(void)
{
    system_info_get_platform_bool("tizen.org/feature/network.wifi.direct", &g_wd_supported_device_p);
    wifi_direct_initialize();
}

/**
 * @function		utc_wifi_direct_device_positive_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_device_positive_cleanup(void)
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
        wifi_direct_device_state_e device_state, void *user_data)
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

static bool foreach_supported_wps_impl_cb(wifi_direct_wps_type_e type, void* user_data)
{
    return true;
}

/**
 * @testcase		utc_wifi_direct_set_session_timer_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Sets session timer of a local device.
 * @scenario  		Verify wifi_direct_set_session_timer.
 */
int utc_wifi_direct_set_session_timer_p(void)
{
	int ret = WIFI_DIRECT_ERROR_NONE;
	if(g_wd_supported_device_p == false) {
		ret = wifi_direct_set_session_timer(120);
		assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_direct_set_session_timer(120);

	assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_direct_get_session_timer_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Gets session timer of a local device.
 * @scenario  		Verify wifi_direct_get_session_timer.
 */
int utc_wifi_direct_get_session_timer_p(void)
{
	int ret = WIFI_DIRECT_ERROR_NONE;
	int seconds = 0;

	if(g_wd_supported_device_p == false) {
		ret = wifi_direct_get_session_timer(&seconds);
		assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_direct_get_session_timer(&seconds);

	assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_direct_activate_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Activates the Wi-Fi Direct service, asynchronous.
 * @scenario  		Deactivate and Activate Wi-Fi Direct service.
 */
int utc_wifi_direct_activate_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_activate();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    wifi_direct_deactivate();

    ret = wifi_direct_activate();

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_ssid_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Gets SSID(Service Set Identifier) of a local device.
 * @scenario  		Verify wifi_direct_get_ssid.
 */
int utc_wifi_direct_get_ssid_p(void)
{
    char* ssid = NULL;
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_get_ssid(&ssid);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_ssid(&ssid);
    free(ssid);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_mac_address_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Gets MAC address of a local device.
 * @scenario  		Verify wifi_direct_get_mac_address.
 */
int utc_wifi_direct_get_mac_address_p(void)
{
    char* mac_address = NULL;
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_get_mac_address(&mac_address);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_get_mac_address(&mac_address);
    free(mac_address);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_state_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Gets the state of Wi-Fi Direct service.
 * @scenario  		Verify wifi_direct_get_state.
 */
int utc_wifi_direct_get_state_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    wifi_direct_state_e status = WIFI_DIRECT_STATE_DEACTIVATED;
    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_get_state(&status);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_state(&status);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_deactivate_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Deactivates the Wi-Fi Direct service, asynchronous.
 * @scenario  		Verify wifi_direct_deactivate.
 */
int utc_wifi_direct_deactivate_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_deactivate();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_deactivate();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_device_name_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Gets the name of a local device.
 * @scenario  		Verify wifi_direct_get_device_name.
 */
int utc_wifi_direct_get_device_name_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    char *dev_name = NULL;
    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_get_device_name(&dev_name);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_device_name(&dev_name);
    free(dev_name);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_primary_device_type_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Gets the primary device type of a local device.
 * @scenario  		Verify wifi_direct_get_primary_device_type.
 */
int utc_wifi_direct_get_primary_device_type_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    wifi_direct_primary_device_type_e type = 0;
    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_get_primary_device_type(&type);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_primary_device_type(&type);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_secondary_device_type_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Gets the secondary device type of a local device.
 * @scenario  		Verify wifi_direct_get_secondary_device_type.
 */
int utc_wifi_direct_get_secondary_device_type_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    wifi_direct_secondary_device_type_e type = 0;
    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_get_secondary_device_type(&type);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_secondary_device_type(&type);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_init_miracast_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Initializes or deintializes the WiFi-Direct Display (MIRACAST) service.
 * @scenario  		Verify wifi_direct_init_miracast.
 */
int utc_wifi_direct_init_miracast_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool enable = false;
    bool supported;
    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_init_miracast(enable);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.display",&supported);
    if(!supported) {
        ret = wifi_direct_init_miracast(enable);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_init_miracast(enable);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_init_display_p
 * @since_tizen		2.4
 * @type		positive
 * @description		Enables  Wi-Fi Display (WFD) functionality and  initialize the various variables required for WFD.
 * @scenario  		Verify wifi_direct_init_display.
 */
int utc_wifi_direct_init_display_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool supported;
    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_init_display();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.display",&supported);
    if(!supported) {
        ret = wifi_direct_init_display();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_init_display();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_deinit_display_p
 * @since_tizen		2.4
 * @type		positive
 * @description		This API shall disable Wi-Fi Display functionality & disable the support of WFD Information Element (IE).
 * @scenario  		Initialize display and deinitialize display.
 */
int utc_wifi_direct_deinit_display_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool supported;
    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_deinit_display();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.display",&supported);
    if(!supported) {
        ret = wifi_direct_deinit_display();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_init_display();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_deinit_display();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_display_p
 * @since_tizen		2.4
 * @type		positive
 * @description		Sets the Wi-Fi Display parameters for the WFD IE of local device.
 * @scenario  		Verify wifi_direct_set_display by passing valid type, port, HDCP parameters.
 */
int utc_wifi_direct_set_display_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool supported;
    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_set_display(0, 0, 0);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.display",&supported);
    if(!supported) {
        ret = wifi_direct_set_display(0, 0, 0);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_init_display();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_set_display(WIFI_DIRECT_DISPLAY_TYPE_DUAL, 7236, true);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_display_availability_p
 * @since_tizen		2.4
 * @type		positive
 * @description		Sets the Wi-Fi Display Session Availability.
 * @scenario  		Verify wifi_direct_set_display_availability by passing valid parameter.
 */
int utc_wifi_direct_set_display_availability_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool supported;
    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_set_display_availability(true);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.display",&supported);
    if(!supported) {
        ret = wifi_direct_set_display_availability(true);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_init_display();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_set_display_availability(true);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_display_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Gets the Wi-Fi Display parameters for the WFD IE of local device.
 * @scenario  		Verify wifi_direct_get_display by passing valid type, port, HDCP parameters.
 */
int utc_wifi_direct_get_display_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    wifi_direct_display_type_e type;
    int port;
    int hdcp;
    bool supported;

    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_get_display(&type, &port, &hdcp);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.display",&supported);
    if(!supported) {
        ret = wifi_direct_get_display(&type, &port, &hdcp);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_init_display();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_get_display(&type, &port, &hdcp);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_display_availability_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Gets the Wi-Fi Display Session Availability.
 * @scenario  		Verify wifi_direct_get_display_availability by passing valid parameter.
 */
int utc_wifi_direct_get_display_availability_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool availability;
    bool supported;

    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_get_display_availability(&availability);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.display",&supported);
    if(!supported) {
        ret = wifi_direct_get_display_availability(&availability);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_init_display();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_get_display_availability(&availability);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_is_autoconnection_mode_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Get the Autoconnection mode status.
 * @scenario  		Verify wifi_direct_is_autoconnection_mode.
 */
int utc_wifi_direct_is_autoconnection_mode_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool mode = false;
    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_is_autoconnection_mode(&mode);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_is_autoconnection_mode(&mode);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_autoconnection_mode_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Sets the Autoconnection mode.
 * @scenario  		Verify wifi_direct_set_autoconnection_mode by passing valid mode.
 */
int utc_wifi_direct_set_autoconnection_mode_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool mode = true;
    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_set_autoconnection_mode(mode);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_set_autoconnection_mode(mode);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_autoconnection_peer_p
 * @since_tizen		2.4
 * @type		positive
 * @description		Allows a device to connect automatically.
 * @scenario  		Verify wifi_direct_set_autoconnection_peer by passing valid MAC address.
 */
int utc_wifi_direct_set_autoconnection_peer_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_set_autoconnection_peer("AA:BB:CC:DD:EE:FF");
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_device_name_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Sets the friendly name of a local device.
 * @scenario  		Verify wifi_direct_set_device_name by passing valid dev name.
 */
int utc_wifi_direct_set_device_name_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    char *device_name = "Samsung";
    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_set_device_name(device_name);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_device_name(device_name);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_foreach_supported_wps_types_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Gets the supported WPS (Wi-Fi Protected Setup) types.
 * @scenario  		Verify wifi_direct_foreach_supported_wps_types by passing callback and user data parameters.
 */
int utc_wifi_direct_foreach_supported_wps_types_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_p == false) {
        ret = wifi_direct_foreach_supported_wps_types(foreach_supported_wps_impl_cb, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_foreach_supported_wps_types(foreach_supported_wps_impl_cb, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_supported_wps_mode_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Gets the all supported WPS (Wi-Fi Protected Setup) types at local device.
 * @scenario  		Verify wifi_direct_get_supported_wps_mode by passing valid wps_mode.
 */
int utc_wifi_direct_get_supported_wps_mode_p(void)
{
	int ret = WIFI_DIRECT_ERROR_NONE;
	int supported_wps_mode = 0;
    if(g_wd_supported_device_p == false) {
    	ret = wifi_direct_get_supported_wps_mode(&supported_wps_mode);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

	ret = wifi_direct_get_supported_wps_mode(&supported_wps_mode);

	assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_direct_add_vsie_p
 * @since_tizen		4.0
 * @type		positive
 * @description		Adds the Wi-Fi Vendor Specific Information Element (VSIE) to specific frame type.
 * @scenario  		Verify wifi_direct_add_vsie by passing valid parameters.
 */
int utc_wifi_direct_add_vsie_p(void)
{
	int ret = WIFI_DIRECT_ERROR_NONE;
	int supported_wps_mode = 0;
	const char *vsie_str = "dd0f0000f00f0002060102055b54565d20";
	wifi_direct_vsie_frames_e frame_id =
		WIFI_DIRECT_VSIE_FRAME_P2P_PROBE_REQ;

	if(g_wd_supported_device_p == false) {
		ret = wifi_direct_add_vsie(frame_id, vsie_str);
		assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wait_for_activate_callback();
	assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

	ret = wifi_direct_add_vsie(frame_id, vsie_str);
	assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

	/* remove vsie before exiting TC */
	wifi_direct_remove_vsie(frame_id, vsie_str);

	return 0;
}

/**
 * @testcase		utc_wifi_direct_get_vsie_p
 * @since_tizen		4.0
 * @type		positive
 * @description		Gets the Wi-Fi Vendor Specific Information Element (VSIE) of specific frame type.
 * @scenario  		Verify wifi_direct_get_vsie by passing valid parameters.
 */
int utc_wifi_direct_get_vsie_p(void)
{
	int ret = WIFI_DIRECT_ERROR_NONE;
	int supported_wps_mode = 0;
	const char *set_vsie_str = "dd0f0000f00f0002060102055b54565d20";
	char *get_vsie_str = NULL;
	wifi_direct_vsie_frames_e frame_id =
		WIFI_DIRECT_VSIE_FRAME_P2P_PROBE_REQ;

	if(g_wd_supported_device_p == false) {
		ret = wifi_direct_get_vsie(frame_id, &get_vsie_str);
		assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wait_for_activate_callback();
	assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

	ret = wifi_direct_add_vsie(frame_id, set_vsie_str);
	assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

	ret = wifi_direct_get_vsie(frame_id, &get_vsie_str);
	assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

	/* remove vsie before exiting TC */
	wifi_direct_remove_vsie(frame_id, set_vsie_str);

	return 0;
}

/**
 * @testcase		utc_wifi_direct_remove_vsie_p
 * @since_tizen		4.0
 * @type		positive
 * @description		Removes the Wi-Fi Vendor Specific Information Element (VSIE) from specific frame type.
 * @scenario  		Verify wifi_direct_remove_vsie by passing valid parameters.
 */
int utc_wifi_direct_remove_vsie_p(void)
{
	int ret = WIFI_DIRECT_ERROR_NONE;
	int supported_wps_mode = 0;
	const char *vsie_str = "dd0f0000f00f0002060102055b54565d20";
	wifi_direct_vsie_frames_e frame_id =
		WIFI_DIRECT_VSIE_FRAME_P2P_PROBE_REQ;

	if(g_wd_supported_device_p == false) {
		ret = wifi_direct_remove_vsie(frame_id, vsie_str);
		assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wait_for_activate_callback();
	assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

	ret = wifi_direct_add_vsie(frame_id, vsie_str);
	assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

	ret = wifi_direct_remove_vsie(frame_id, vsie_str);
	assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_direct_set_wps_config_method_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Sets the wps config method.
 * @scenario  		Verify wifi_direct_set_wps_config_method by passing valid config method.
 */
int utc_wifi_direct_set_wps_config_method_p(void)
{
	int ret = WIFI_DIRECT_ERROR_NONE;
	if(g_wd_supported_device_p == false) {
		ret = wifi_direct_set_wps_config_method(WIFI_DIRECT_CONFIG_METHOD_DEFAULT);
		assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wait_for_activate_callback();
	assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

	ret = wifi_direct_set_wps_config_method(WIFI_DIRECT_CONFIG_METHOD_DEFAULT);
	assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_direct_get_wps_config_method_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Gets the wps config method.
 * @scenario  		Verify wifi_direct_get_wps_config_method by passing valid config method.
 */
int utc_wifi_direct_get_wps_config_method_p(void)
{
	int ret = WIFI_DIRECT_ERROR_NONE;
	int wps_config_method = 0;
	if(g_wd_supported_device_p == false) {
		ret = wifi_direct_get_wps_config_method(&wps_config_method);
		assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_direct_get_wps_config_method(&wps_config_method);

	assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

	return 0;
}
