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

//& set: wifi-direct-service-discovery-positive

static GMainLoop* loop = NULL;
static bool activated_callback = false;
static bool service_callback = false;
static bool g_wd_supported_sd_p = true;

/**
 * @function		utc_wifi_direct_service_positive_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_service_positive_startup(void)
{
    system_info_get_platform_bool("tizen.org/feature/network.wifi.direct", &g_wd_supported_sd_p);
    wifi_direct_initialize();

}

/**
 * @function		utc_wifi_direct_service_positive_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_service_positive_cleanup(void)
{
    wifi_direct_deactivate();

    wifi_direct_deinitialize();
}

static gboolean activate_timeout(gpointer data)
{
    activated_callback= false;
    g_main_loop_quit(loop);
    g_main_loop_unref(loop);
    loop = NULL;
    return FALSE;
}

static gboolean service_timeout(gpointer data)
{
	service_callback = false;
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

static void wifi_service_callback(int error_code,
		wifi_direct_service_discovery_state_e service_state,
		wifi_direct_service_type_e service_type, void *response_data,
		const char *mac_address, void *user_data)
{
	int ret = WIFI_DIRECT_ERROR_NONE;

    if (WIFI_DIRECT_ERROR_NONE == error_code && WIFI_DIRECT_SERVICE_DISCOVERY_STARTED == service_state) {
    	g_main_loop_quit(loop);
    	g_main_loop_unref(loop);
    	service_callback= true;
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


static int wait_for_service_callback(void)
{
	wifi_direct_state_e state;
	int timeout_testcase = 0;
	int ret;
    if(g_wd_supported_sd_p == false) {
        ret = wifi_direct_set_service_state_changed_cb(wifi_service_callback, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    bool supported;
    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.service_discovery",&supported);
    if(!supported) {
        ret = wifi_direct_set_service_state_changed_cb(wifi_service_callback, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

	ret = wifi_direct_set_service_state_changed_cb(wifi_service_callback, NULL);
	if (WIFI_DIRECT_ERROR_NONE == ret)
	{
		ret = wifi_direct_get_state(&state);
		if(ret == WIFI_DIRECT_ERROR_NONE && state >= WIFI_DIRECT_STATE_ACTIVATED)
		{
			ret = wifi_direct_start_service_discovery(NULL, WIFI_DIRECT_SERVICE_TYPE_BONJOUR);

			if (WIFI_DIRECT_ERROR_NONE == ret)
			{
				loop = g_main_loop_new(NULL, FALSE);
				timeout_testcase = g_timeout_add(20000, service_timeout, loop);
				g_main_loop_run(loop);
				g_source_remove(timeout_testcase);
				wifi_direct_unset_service_state_changed_cb();

				if (!service_callback)
				{
					ret = -1;
				}
			}
		}
	}
	return ret;
}

/**
 * @testcase		utc_wifi_direct_register_service_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Registers for a service using WiFi Direct Service Discovery.
 * @scenario  		Register UPNP Service with valid information.
 */
int utc_wifi_direct_register_service_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    char *info1 = "10";
    char *info2 = "uuid:6859dede-8574-59ab-9332-123456789012::upnp:rootdevice";
    int service_id = 0;
    if(g_wd_supported_sd_p == false) {
        ret = wifi_direct_register_service(WIFI_DIRECT_SERVICE_TYPE_UPNP, info1, info2, &service_id);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    bool supported;

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.service_discovery",&supported);
    if(!supported) {
        ret = wifi_direct_register_service(WIFI_DIRECT_SERVICE_TYPE_UPNP, info1, info2, &service_id);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_register_service(WIFI_DIRECT_SERVICE_TYPE_UPNP, info1, info2, &service_id);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_deregister_service_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Deregisters for a service used for WiFi Direct Service Discovery..
 * @scenario  		Register UPNP Service and deregister using its service ID.
 */
int utc_wifi_direct_deregister_service_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    char *info1 = "10";
    char *info2 = "uuid:6859dede-8574-59ab-9332-123456789012::upnp:rootdevice";
    int service_id = 0;
    if(g_wd_supported_sd_p == false) {
        ret = wifi_direct_deregister_service(service_id);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    bool supported;

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.service_discovery",&supported);
    if(!supported) {
        ret = wifi_direct_deregister_service(service_id);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_register_service(WIFI_DIRECT_SERVICE_TYPE_UPNP, info1, info2, &service_id);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_deregister_service(service_id);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_start_service_discovery_p
 * @since_tizen		2.3
 * @type		positive
 * @description		WiFi Direct Service Discovery will be started.
 * @scenario  		Discover the UPNP Service.
 */
int utc_wifi_direct_start_service_discovery_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_sd_p == false) {
        ret = wifi_direct_start_service_discovery(NULL, WIFI_DIRECT_SERVICE_TYPE_UPNP);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    bool supported;

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.service_discovery",&supported);
    if(!supported) {
        ret = wifi_direct_start_service_discovery(NULL, WIFI_DIRECT_SERVICE_TYPE_UPNP);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_start_service_discovery(NULL, WIFI_DIRECT_SERVICE_TYPE_UPNP);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    wifi_direct_cancel_service_discovery(NULL, WIFI_DIRECT_SERVICE_TYPE_UPNP);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_cancel_service_discovery_p
 * @since_tizen		2.3
 * @type		positive
 * @description		A service started for WiFi Direct Service Discovery will be stopped.
 * @scenario  		Discover the BONJOUR Service.
 */
int utc_wifi_direct_cancel_service_discovery_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_sd_p == false) {
        ret = wifi_direct_cancel_service_discovery(NULL, WIFI_DIRECT_SERVICE_TYPE_BONJOUR);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    bool supported;

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.service_discovery",&supported);
    if(!supported) {
        ret = wifi_direct_cancel_service_discovery(NULL, WIFI_DIRECT_SERVICE_TYPE_BONJOUR);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wait_for_service_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_cancel_service_discovery(NULL, WIFI_DIRECT_SERVICE_TYPE_BONJOUR);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}
