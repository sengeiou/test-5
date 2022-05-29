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

//& set: Wifi-direct-device-negative
static bool g_wd_supported_device_n = true;


/**
 * @function		utc_wifi_direct_device_negative_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_device_negative_startup(void)
{
    system_info_get_platform_bool("tizen.org/feature/network.wifi.direct", &g_wd_supported_device_n);
    wifi_direct_initialize();
}

/**
 * @function		utc_wifi_direct_device_negative_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_device_negative_cleanup(void)
{
    wifi_direct_deinitialize();
}

/**
 * @testcase		utc_wifi_direct_set_session_timer_n
 * @since_tizen		3.0
 * @type		negative
 * @description		wifi_direct_set_session_timer should fail on invalid parameters.
 * @scenario  		Verify wifi_direct_set_session_timer by passing negative value parameter.
 */
int utc_wifi_direct_set_session_timer_n(void)
{
	int ret = WIFI_DIRECT_ERROR_NONE;
	if(g_wd_supported_device_n == false) {
		ret = wifi_direct_set_session_timer(120);
		assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_direct_set_session_timer(-120);

	assert_eq(ret,  WIFI_DIRECT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_wifi_direct_get_session_timer_n
 * @since_tizen		3.0
 * @type		negative
 * @description		wifi_direct_set_session_timer should fail on invalid parameters.
 * @scenario  		Verify wifi_direct_set_session_timer by passing negative value parameter.
 */
int utc_wifi_direct_get_session_timer_n(void)
{
	int ret = WIFI_DIRECT_ERROR_NONE;

	if(g_wd_supported_device_n == false) {
		ret = wifi_direct_get_session_timer(NULL);
		assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_direct_get_session_timer(NULL);

	assert_eq(ret,  WIFI_DIRECT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_wifi_direct_get_ssid_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_get_ssid should fail on invalid parameters.
 * @scenario		Verify wifi_direct_get_ssid by passing NULL as a parameter.
 */
int utc_wifi_direct_get_ssid_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_get_ssid(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_ssid(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_mac_address_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_get_mac_address should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_get_mac_address by passing invalid MAC address as a parameter.
 */
int utc_wifi_direct_get_mac_address_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_get_mac_address(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_mac_address(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_state_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_get_state should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_get_state by passing NULL as a parameter.
 */
int utc_wifi_direct_get_state_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_get_state(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_state(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_activate_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_activate should fail when wifi_direct is not initialized.
 * @scenario  		Verify wifi_direct_activate after deinitializing Wi-Fi Direct.
 */
int utc_wifi_direct_activate_n(void)
{
    int ret = wifi_direct_deinitialize();
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_activate();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_activate();

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_deactivate_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_deactivate should fail when wifi_direct is not initialized.
 * @scenario  		Verify wifi_direct_deactivate after deinitizing Wi-Fi Direct.
	
 */
int utc_wifi_direct_deactivate_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_deactivate();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_deinitialize();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_deactivate();

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_device_name_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_get_device_name should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_get_device_name by passing NULL as a device_name.
 */
int utc_wifi_direct_get_device_name_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_get_device_name(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_device_name(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_primary_device_type_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_get_primary_device_type should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_get_primary_device_type by passing NULL as a device_type.
 */
int utc_wifi_direct_get_primary_device_type_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_get_primary_device_type(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_primary_device_type(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_secondary_device_type_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_get_secondary_device_type should fail on invalid parameter.
 * @scenario  		Verify wifi_direct_get_secondary_device_type by passing NULL as a device_type.
 */
int utc_wifi_direct_get_secondary_device_type_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_get_secondary_device_type(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_secondary_device_type(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_init_miracast_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_init_miracast should fail when Wi-Fi Direct is not initialized.
 * @scenario  		Verify wifi_direct_init_miracast after Wi-Fi Direct is deinitialized.
 */
int utc_wifi_direct_init_miracast_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_init_miracast(0);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    bool supported;
    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.display",&supported);
    if(!supported) {
        ret = wifi_direct_init_miracast(0);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_deinitialize();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_init_miracast(0);

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_init_display_n
 * @since_tizen		2.4
 * @type		Negative
 * @description		wifi_direct_init_display should fail when Wi-Fi Direct is not initialized.
 * @scenario  		Verify wifi_direct_init_display after Wi-Fi Direct is deinitialized.
 */
int utc_wifi_direct_init_display_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_init_display();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    bool supported;
    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.display",&supported);
    if(!supported) {
        ret = wifi_direct_init_display();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_deinitialize();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_init_display();

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_deinit_display_n
 * @since_tizen		2.4
 * @type		Negative
 * @description		wifi_direct_deinit_display should fail when Wi-Fi Direct is not initialized.
 * @scenario  		Verify wifi_direct_deinit_display after Wi-Fi Direct is deinitialized.
 */
int utc_wifi_direct_deinit_display_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_deinit_display();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    bool supported;
    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.display",&supported);
    if(!supported) {
        ret = wifi_direct_deinit_display();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_deinitialize();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_deinit_display();

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_display_n
 * @since_tizen		2.4
 * @type		Negative
 * @description		wifi_direct_set_display should fail when Wi-Fi Direct is not initialized.
 * @scenario  		Verify wifi_direct_set_display after Wi-Fi Direct is deinitialized.
 */
int utc_wifi_direct_set_display_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_set_display(0, 0, 0);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    bool supported;
    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.display",&supported);
    if(!supported) {
        ret = wifi_direct_set_display(0, 0, 0);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_deinitialize();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_set_display(0, 0, 0);

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_display_availability_n
 * @since_tizen		2.4
 * @type		Negative
 * @description		wifi_direct_set_display_availability should fail when Wi-Fi Direct is not initialized.
 * @scenario  		Verify wifi_direct_set_display_availability after Wi-Fi Direct is deinitialized.
 */
int utc_wifi_direct_set_display_availability_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_set_display_availability(0);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    bool supported;
    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.display",&supported);
    if(!supported) {
        ret = wifi_direct_set_display_availability(0);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_deinitialize();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_set_display_availability(0);

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_display_n
 * @since_tizen		5.0
 * @type		Negative
 * @description		wifi_direct_get_display should fail when Wi-Fi Direct is not initialized.
 * @scenario  		Verify wifi_direct_get_display after Wi-Fi Direct is deinitialized.
 */
int utc_wifi_direct_get_display_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    wifi_direct_display_type_e type;
    int port;
    int hdcp;
    bool supported;

    if(g_wd_supported_device_n == false) {
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

    ret = wifi_direct_deinitialize();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_get_display(&type, &port, &hdcp);

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_display_availability_n
 * @since_tizen		5.0
 * @type		Negative
 * @description		wifi_direct_get_display_availability should fail when Wi-Fi Direct is not initialized.
 * @scenario  		Verify wifi_direct_get_display_availability after Wi-Fi Direct is deinitialized.
 */
int utc_wifi_direct_get_display_availability_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool availability;
    bool supported;

    if(g_wd_supported_device_n == false) {
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

    ret = wifi_direct_deinitialize();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_get_display_availability(&availability);

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_is_autoconnection_mode_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_is_autoconnection_mode should fail with invalid parameter.
 * @scenario  		Verify wifi_direct_is_autoconnection_mode by passing NULL as a mode.
 */
int utc_wifi_direct_is_autoconnection_mode_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_is_autoconnection_mode(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_is_autoconnection_mode(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_autoconnection_mode_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_set_autoconnection_mode should fail when Wi-Fi Direct is not initialized.
 * @scenario  		Verify wifi_direct_set_autoconnection_mode after Wi-Fi Direct is deinitialized.
 */
int utc_wifi_direct_set_autoconnection_mode_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_set_autoconnection_mode(false);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_deinitialize();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_set_autoconnection_mode(false);
    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_autoconnection_peer_n
 * @since_tizen		2.4
 * @type		Negative
 * @description		wifi_direct_set_autoconnection_peer should fail with invalid parameter.
 * @scenario  		Verify wifi_direct_set_autoconnection_peer by passing NULL as a MAC address.
 */
int utc_wifi_direct_set_autoconnection_peer_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_set_autoconnection_peer(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_autoconnection_peer(NULL);
    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_device_name_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_set_device_name should fail with invalid parameter.
 * @scenario  		Verify wifi_direct_set_device_name by passing NULL as a device name.
 */
int utc_wifi_direct_set_device_name_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_set_device_name(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_device_name(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_foreach_supported_wps_types_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_foreach_supported_wps_types should fail with invalid parameter.
 * @scenario  		Verify wifi_direct_foreach_supported_wps_types by passing NULL as a callback and user data.
 */
int utc_wifi_direct_foreach_supported_wps_types_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_foreach_supported_wps_types(NULL, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_foreach_supported_wps_types(NULL, NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_supported_wps_mode_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		wifi_direct_get_supported_wps_mode should fail with invalid parameter.
 * @scenario  		Verify wifi_direct_get_supported_wps_mode by passing NULL as a wps_mode.
 */
int utc_wifi_direct_get_supported_wps_mode_n(void)
{
	int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
	ret = wifi_direct_get_supported_wps_mode(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

	ret = wifi_direct_get_supported_wps_mode(NULL);

	assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_wifi_direct_add_vsie_n
 * @since_tizen		4.0
 * @type		Negative
 * @description		wifi_direct_add_vsie should fail with invalid parameter.
 * @scenario  		Verify wifi_direct_add_vsie by passing NULL as vsie_str.
 */
int utc_wifi_direct_add_vsie_n(void)
{
	int ret = WIFI_DIRECT_ERROR_NONE;
	wifi_direct_vsie_frames_e frame_id =
		WIFI_DIRECT_VSIE_FRAME_P2P_PROBE_REQ;

	if(g_wd_supported_device_n == false) {
		ret = wifi_direct_add_vsie(frame_id, NULL);
		assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_direct_add_vsie(frame_id, NULL);
	assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_wifi_direct_get_vsie_n
 * @since_tizen		4.0
 * @type		Negative
 * @description		wifi_direct_get_vsie should fail with invalid parameter.
 * @scenario  		Verify wifi_direct_get_vsie by passing NULL as vsie_str.
 */
int utc_wifi_direct_get_vsie_n(void)
{
	int ret = WIFI_DIRECT_ERROR_NONE;
	wifi_direct_vsie_frames_e frame_id =
		WIFI_DIRECT_VSIE_FRAME_P2P_PROBE_REQ;

	if(g_wd_supported_device_n == false) {
		ret = wifi_direct_get_vsie(frame_id, NULL);
		assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_direct_get_vsie(frame_id, NULL);
	assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_wifi_direct_remove_vsie_n
 * @since_tizen		4.0
 * @type		Negative
 * @description		wifi_direct_remove_vsie should fail with invalid parameter.
 * @scenario  		Verify wifi_direct_remove_vsie by passing NULL as vsie_str.
 */
int utc_wifi_direct_remove_vsie_n(void)
{
	int ret = WIFI_DIRECT_ERROR_NONE;
	wifi_direct_vsie_frames_e frame_id =
		WIFI_DIRECT_VSIE_FRAME_P2P_PROBE_REQ;

	if(g_wd_supported_device_n == false) {
		ret = wifi_direct_remove_vsie(frame_id, NULL);
		assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wifi_direct_remove_vsie(frame_id, NULL);
	assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_wifi_direct_set_wps_config_method_n
 * @since_tizen		5.0
 * @type		Negative
 * @description		wifi_direct_set_wps_config_method should fail with invalid parameter.
 * @scenario  		Verify wifi_direct_set_wps_config_method by passing invalid wps config method.
 */
int utc_wifi_direct_set_wps_config_method_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_set_wps_config_method(-1);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_wps_config_method(-1);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_wps_config_method_n
 * @since_tizen		5.0
 * @type		Negative
 * @description		wifi_direct_get_wps_config_method should fail with invalid parameter.
 * @scenario  		Verify wifi_direct_get_wps_config_method by passing NULL parameter.
 */
int utc_wifi_direct_get_wps_config_method_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_device_n == false) {
        ret = wifi_direct_get_wps_config_method(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_wps_config_method(NULL);

    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}
