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

//& set: wifi-direct-service-discovery-negative
static bool g_wd_supported_sd_n = true;


/**
 * @function		utc_wifi_direct_service_negative_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_service_negative_startup(void)
{
    system_info_get_platform_bool("tizen.org/feature/network.wifi.direct", &g_wd_supported_sd_n);
    wifi_direct_initialize();
}

/**
 * @function		utc_wifi_direct_service_negative_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_service_negative_cleanup(void)
{
     wifi_direct_deinitialize();
}

/**
 * @testcase		utc_wifi_direct_register_service_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Should not register for a UPNP service using WiFi Direct Service Discovery.
 * @scenario  		Verify wifi_direct_register_service by passing invalid information.
 */
int utc_wifi_direct_register_service_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    char *info1 = NULL;
    char *info2 = "uuid:6859dede-8574-59ab-9332-123456789012::upnp:rootdevice";
    int service_id = 0;
    if(g_wd_supported_sd_n == false) {
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

    ret = wifi_direct_register_service(WIFI_DIRECT_SERVICE_TYPE_UPNP, info1, info2, &service_id);
    assert_eq(ret, WIFI_DIRECT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_deregister_service_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Should not deregister for a SERVICE.
 * @scenario  		Verify wifi_direct_deregister_service by passing invalid service id.
	
 */
int utc_wifi_direct_deregister_service_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_sd_n == false) {
        ret = wifi_direct_deregister_service(10);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    bool supported;

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.service_discovery",&supported);
    if(!supported) {
        ret = wifi_direct_deregister_service(10);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_deregister_service(10);

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_PERMITTED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_start_service_discovery_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		WiFi Direct Service Discovery should not be started.
 * @scenario  		Verify wifi_direct_start_service_discovery by passing invalid service id.
	
 */
int utc_wifi_direct_start_service_discovery_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    const char *mac_addr = "f2:27:65:75:18:bf";
    if(g_wd_supported_sd_n == false) {
        ret = wifi_direct_start_service_discovery(mac_addr, 10);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    bool supported;

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.service_discovery",&supported);
    if(!supported) {
        ret = wifi_direct_start_service_discovery(mac_addr, 10);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_start_service_discovery(mac_addr, 10);

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_PERMITTED);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_cancel_service_discovery_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Service should not be cancelled.
 * @scenario  		Verify wifi_direct_cancel_service_discovery by passing invalid service id.
	
 */
int utc_wifi_direct_cancel_service_discovery_n(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    const char *mac_addr = "f2:27:65:75:18:bf";
    if(g_wd_supported_sd_n == false) {
        ret = wifi_direct_cancel_service_discovery(mac_addr, 10);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    bool supported;

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.service_discovery",&supported);
    if(!supported) {
        ret = wifi_direct_cancel_service_discovery(mac_addr, 10);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_cancel_service_discovery(mac_addr, 10);

    assert_eq(ret, WIFI_DIRECT_ERROR_NOT_PERMITTED);

    return 0;
}
