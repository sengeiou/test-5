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

//& set: Wifi-direct-group-positive

static GMainLoop* loop = NULL;
static bool activated_callback = false;
static bool connection_callback = false;
static bool g_wd_supported_group_p = true;

/**
 * @function		utc_wifi_direct_group_positive_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_group_positive_startup(void)
{
    system_info_get_platform_bool("tizen.org/feature/network.wifi.direct", &g_wd_supported_group_p);
    wifi_direct_initialize();
}


/**
 * @function		utc_wifi_direct_group_positive_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_wifi_direct_group_positive_cleanup(void)
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


static gboolean connection_timeout(gpointer data)
{
	connection_callback = false;
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

static void wifi_connection_callback(wifi_direct_error_e error_code,
		wifi_direct_connection_state_e connection_state,
		const char *mac_address,
		void *user_data)
{
	int ret = WIFI_DIRECT_ERROR_NONE;
	wifi_direct_state_e state;

    if (WIFI_DIRECT_ERROR_NONE == error_code && WIFI_DIRECT_GROUP_CREATED == connection_state) {
		connection_callback= true;
		g_main_loop_quit(loop);
		g_main_loop_unref(loop);
		ret = wifi_direct_get_state(&state);
		if(ret == WIFI_DIRECT_ERROR_NONE && state == WIFI_DIRECT_STATE_CONNECTED) {
			connection_callback = true;
		}

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


static int wait_for_connection_callback(void)
{
	wifi_direct_state_e state;
	int timeout_testcase = 0;
	int ret;

	ret = wifi_direct_set_connection_state_changed_cb(wifi_connection_callback, NULL);
	if (WIFI_DIRECT_ERROR_NONE == ret)
	{
		ret = wifi_direct_get_state(&state);
		if(ret == WIFI_DIRECT_ERROR_NONE && state >= WIFI_DIRECT_STATE_ACTIVATED)
		{
			ret = wifi_direct_create_group();

			if (WIFI_DIRECT_ERROR_NONE == ret)
			{
				loop = g_main_loop_new(NULL, FALSE);
				timeout_testcase = g_timeout_add(20000, connection_timeout, loop);
				g_main_loop_run(loop);
				g_source_remove(timeout_testcase);
				wifi_direct_unset_connection_state_changed_cb();

				if (!connection_callback)
				{
					ret = -1;
				}
			}
		}
	}
	return ret;
}

static bool _wifi_direct_persistent_group_cb(const char* mac_address, const char* ssid, void* user_data)
{
    return true;
}

/**
 * @testcase		utc_wifi_direct_set_auto_group_removal_p
 * @since_tizen		3.0
 * @type		positive
 * @description		Sets auto group removal flags on P2P daemon.
 * @scenario  		wifi_direct_set_auto_group_removal should sets flag on P2P daemon.
 */
int utc_wifi_direct_set_auto_group_removal_p(void)
{
	int ret = WIFI_DIRECT_ERROR_NONE;
	if(g_wd_supported_group_p == false) {
		ret = wifi_direct_set_auto_group_removal(true);
		assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = wait_for_activate_callback();
	assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

	ret = wifi_direct_set_auto_group_removal(true);
	assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_wifi_direct_create_group_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Creates a Wi-Fi Direct Group, asynchronous.
 * @scenario  		wifi_direct_create_group should create Wi-Fi Direct group.
 */
int utc_wifi_direct_create_group_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_p == false) {
        ret = wifi_direct_create_group();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wait_for_connection_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_destroy_group_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Destorys the Wi-Fi Direct Group, asynchronous.
 * @scenario  		wifi_direct_destroy_group should destroy group.
 */
int utc_wifi_direct_destroy_group_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_p == false) {
        ret = wifi_direct_destroy_group();
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wait_for_connection_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_destroy_group();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_is_group_owner_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Checks whether this device is the group owner or not
 * @scenario  		Verify wifi_direct_is_group_owner.
 */
int utc_wifi_direct_is_group_owner_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool owner;
    if(g_wd_supported_group_p == false) {
        ret = wifi_direct_is_group_owner(&owner);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_is_group_owner(&owner);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_is_autonomous_group_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Checks whether the current group is the autonomous group or not.
 * @scenario  		Verify wifi_direct_is_autonomous_group.
 */
int utc_wifi_direct_is_autonomous_group_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool autonomous_group;
    if(g_wd_supported_group_p == false) {
        ret = wifi_direct_is_autonomous_group(&autonomous_group);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wait_for_connection_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_is_autonomous_group(&autonomous_group);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_group_owner_intent_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Gets the intent of the group owner.
 * @scenario  		Know the intent of the group owner. Should return the intent of the group owner.
 */
int utc_wifi_direct_get_group_owner_intent_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    int go_intent = 0;
    if(g_wd_supported_group_p == false) {
        ret = wifi_direct_get_group_owner_intent(&go_intent);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_group_owner_intent(&go_intent);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_group_owner_intent_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Sets the intent of the group owner.
 * @scenario  		Verify wifi_direct_set_group_owner_intent by passing proper go_intent value.
 */
int utc_wifi_direct_set_group_owner_intent_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    int go_intent = 7;
    if(g_wd_supported_group_p == false) {
        ret = wifi_direct_set_group_owner_intent(go_intent);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_group_owner_intent(go_intent);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_max_clients_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Gets the max number of clients.
 * @scenario  		Know Wi-Fi Direct get max clients.
 */
int utc_wifi_direct_get_max_clients_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    int max = 0;
    if(g_wd_supported_group_p == false) {
        ret = wifi_direct_get_max_clients(&max);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_max_clients(&max);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_max_clients_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Sets the max number of clients.
 * @scenario  		Verify wifi_direct_set_max_clients by passing the max number of clients.
 */
int utc_wifi_direct_set_max_clients_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    int max = 8;
    if(g_wd_supported_group_p == false) {
        ret = wifi_direct_set_max_clients(max);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_max_clients(max);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_passphrase_p
 * @since_tizen		2.4
 * @type		positive
 * @description		Sets or updates Wi-Fi Protected Access (WPA) password. When creating Wi-Fi Direct Group, this password will be used.
 * @scenario  		Verify wifi_direct_set_passphrase by passing passphrase(new wpa password to set).
 */
int utc_wifi_direct_set_passphrase_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_p == false) {
        ret = wifi_direct_set_passphrase(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_passphrase("ABCDEFGH");
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_passphrase_p
 * @since_tizen		2.4
 * @type		positive
 * @description		Gets the Wi-Fi Protected Access (WPA) password when creating Wi-Fi Direct Group.
 * @scenario  		Verify wifi_direct_get_passphrase. Should return passphrase  Pointer to store WPA password.
 */
int utc_wifi_direct_get_passphrase_p(void)
{
	  char* passphrase = NULL;
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_p == false) {
        ret = wifi_direct_get_passphrase(NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wait_for_connection_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_get_passphrase(&passphrase);
    if(passphrase)
		free(passphrase);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_persistent_group_enabled_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Enables the persistent group.If @a enabled is true, then P2P persistent group will be used while creating a group and establishing a connection.
 * @scenario  		Verify wifi_direct_set_persistent_group_enabled.
 */
int utc_wifi_direct_set_persistent_group_enabled_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool enabled = true;
    if(g_wd_supported_group_p == false) {
        ret = wifi_direct_set_persistent_group_enabled(enabled);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    //it's not documented that this method requires wifi_activate
    ret = wifi_direct_set_persistent_group_enabled(enabled);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_foreach_persistent_groups_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Gets the persistent groups.
 * @scenario  		Verify wifi_direct_foreach_persistent_groups.
 */
int utc_wifi_direct_foreach_persistent_groups_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_p == false) {
        ret = wifi_direct_foreach_persistent_groups(_wifi_direct_persistent_group_cb, NULL);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    //it's not documented that this method requires wifi_activate
    ret = wifi_direct_foreach_persistent_groups(_wifi_direct_persistent_group_cb, NULL);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_is_persistent_group_enabled_p
 * @since_tizen		2.3
 * @type		positive
 * @description		Checks whether the persistent group is enabled or disabled. Should return the status of the persistent group.
 * @scenario  		Verify wifi_direct_is_persistent_group_enabled.
 */
int utc_wifi_direct_is_persistent_group_enabled_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    bool enabled = false;
    if(g_wd_supported_group_p == false) {
        ret = wifi_direct_is_persistent_group_enabled(&enabled);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wait_for_connection_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wifi_direct_is_persistent_group_enabled(&enabled);

    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_create_group_with_ssid_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Creates a Wi-Fi Direct Group with given SSID, asynchronous.
 * @scenario  		wifi_direct_create_group_with_ssid should create Wi-Fi Direct group with provided SSID.
 */
int utc_wifi_direct_create_group_with_ssid_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    if(g_wd_supported_group_p == false) {
        ret = wifi_direct_create_group_with_ssid("Tizen");
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wait_for_activate_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    ret = wait_for_connection_callback();
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_set_go_intent_per_type_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Sets the intent of the group owner by device type.
 * @scenario  		Verify wifi_direct_set_go_intent_per_type by passing proper go_intent and device type value.
 */
int utc_wifi_direct_set_go_intent_per_type_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    int go_intent = 7;
	int type = 1;
    if(g_wd_supported_group_p == false) {
        ret = wifi_direct_set_go_intent_per_type(type, go_intent);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_set_go_intent_per_type(type, go_intent);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wifi_direct_get_go_intent_per_type_p
 * @since_tizen		5.0
 * @type		positive
 * @description		Gets the intent of the group owner by device type.
 * @scenario  		Verify wifi_direct_get_go_intent_per_type by passing proper go_intent and device type value.
 */
int utc_wifi_direct_get_go_intent_per_type_p(void)
{
    int ret = WIFI_DIRECT_ERROR_NONE;
    int go_intent;
	int type = 1;
    if(g_wd_supported_group_p == false) {
        ret = wifi_direct_get_go_intent_per_type(type, &go_intent);
        assert_eq(ret, WIFI_DIRECT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = wifi_direct_get_go_intent_per_type(type, &go_intent);
    assert_eq(ret, WIFI_DIRECT_ERROR_NONE);

    return 0;
}
