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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <system_info.h>
#include "assert.h"
#include "runtime_info.h"


//& set: RuntimeInfo


static void runtime_info_changed(runtime_info_key_e key, void *user_data)
{
}

static int is_resourced_activated(void)
{
	return access("/run/resourced", F_OK) == 0 ? 1 : 0;
}

static int compare_retcode_with_feature_support(int retcode, const char *feature)
{
	bool supported = false;

	system_info_get_platform_bool(feature, &supported);

	if (supported)
		return (retcode == RUNTIME_INFO_ERROR_NONE) ? 0 : 1;
	else
		return (retcode == RUNTIME_INFO_ERROR_NOT_SUPPORTED) ? 0 : 1;
}

static double get_platform_version(void)
{
	double version = 5.0;
	char *version_str;

	if (system_info_get_platform_string("tizen.org/feature/platform.version", &version_str) == SYSTEM_INFO_ERROR_NONE)
		version = atof(version_str);

	return version;
}

/**
 * @testcase		utc_runtime_info_get_value_double_n
 * @since_tizen		2.3
 * @description		Get double type key negative test (for NULL key)
 */
int utc_runtime_info_get_value_double_n(void)
{
    double value;
    int retcode;

    retcode = runtime_info_get_value_double((runtime_info_key_e)NULL, &value);

    assert_neq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_runtime_info_get_value_double_p
 * @since_tizen		2.3
 * @description		Get double type key positive test
 */
int utc_runtime_info_get_value_double_p(void)
{
//TODO: current runtime_info does not have double type value.
    return 0;
}

/**
 * @testcase		utc_runtime_info_get_value_string_p
 * @since_tizen		2.3
 * @description		Get string type key positive test
 */
int utc_runtime_info_get_value_string_p(void)
{
//TODO: current runtime_info does not have string type value.
    return 0;
}

/**
 * @testcase		utc_runtime_info_get_value_bool_p
 * @since_tizen		2.3
 * @description		Get bool type key positive test
 */
int utc_runtime_info_get_value_bool_p(void)
{
    bool value;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUDIO_JACK_CONNECTED;

    retcode = runtime_info_get_value_bool(key, &value);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_runtime_info_get_value_bool_n
 * @since_tizen		2.3
 * @description		Get bool type key negative test (invalid parameter)
 */
int utc_runtime_info_get_value_bool_n(void)
{
    int retcode;

    retcode = runtime_info_get_value_bool((runtime_info_key_e)NULL, NULL);

    assert_neq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}




/**
 * @testcase		utc_runtime_info_AUDIO_JACK_CONNECTED_n1
 * @since_tizen		2.3
 * @description		Audio Jack status negative test (key type mismatch)
 */
int utc_runtime_info_AUDIO_JACK_CONNECTED_n1(void)
{
    char *value = NULL;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUDIO_JACK_CONNECTED;

    retcode = runtime_info_get_value_string(key, &value);

    free(value);
    value = NULL;

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_AUDIO_JACK_CONNECTED_n2
 * @since_tizen		2.3
 * @description		Audio Jack status negative test (retrieval test; invalid parameter)
 */
int utc_runtime_info_AUDIO_JACK_CONNECTED_n2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUDIO_JACK_CONNECTED;

    retcode = runtime_info_get_value_bool(key, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_AUDIO_JACK_CONNECTED_n3
 * @since_tizen		2.3
 * @description		Audio Jack status negative test (set change callback; invalid parameter)
 */
int utc_runtime_info_AUDIO_JACK_CONNECTED_n3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUDIO_JACK_CONNECTED;

    retcode = runtime_info_set_changed_cb(key, NULL, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_AUDIO_JACK_CONNECTED_p1
 * @since_tizen		2.3
 * @description		Audio Jack status positive test (value retrieval)
 */
int utc_runtime_info_AUDIO_JACK_CONNECTED_p1(void)
{
    bool value;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUDIO_JACK_CONNECTED;

    retcode = runtime_info_get_value_bool(key, &value);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}


/**
 * @testcase		utc_runtime_info_AUDIO_JACK_CONNECTED_p2
 * @since_tizen		2.3
 * @description		Audio Jack status positive test (set change callback)
 */
int utc_runtime_info_AUDIO_JACK_CONNECTED_p2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUDIO_JACK_CONNECTED;

    retcode = runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);

    runtime_info_unset_changed_cb(key);

    return 0;
}


/**
 * @testcase		utc_runtime_info_AUDIO_JACK_CONNECTED_p3
 * @since_tizen		2.3
 * @description		Audio Jack status positive test (unset change callback)
 */
int utc_runtime_info_AUDIO_JACK_CONNECTED_p3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUDIO_JACK_CONNECTED;

    runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    retcode = runtime_info_unset_changed_cb(key);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}


/**
 * @testcase		utc_runtime_info_BATTERY_IS_CHARGING_n1
 * @since_tizen		2.3
 * @description		Battery status negative test (key type mismatch)
 */
int utc_runtime_info_BATTERY_IS_CHARGING_n1(void)
{
    char *value = NULL;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_BATTERY_IS_CHARGING;

    retcode = runtime_info_get_value_string(key, &value);

    free(value);
    value = NULL;

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_BATTERY_IS_CHARGING_n2
 * @since_tizen		2.3
 * @description		Battery status negative test (value retrieval; invalid parameter)
 */
int utc_runtime_info_BATTERY_IS_CHARGING_n2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_BATTERY_IS_CHARGING;

    retcode = runtime_info_get_value_bool(key, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_BATTERY_IS_CHARGING_n3
 * @since_tizen		2.3
 * @description		Battery status negative test (set change callback; invalid parameters)
 */
int utc_runtime_info_BATTERY_IS_CHARGING_n3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_BATTERY_IS_CHARGING;

    retcode = runtime_info_set_changed_cb(key, NULL, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_BATTERY_IS_CHARGING_p1
 * @since_tizen		2.3
 * @description		Battery status positive test (value retrieval)
 */
int utc_runtime_info_BATTERY_IS_CHARGING_p1(void)
{
    bool value;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_BATTERY_IS_CHARGING;

    retcode = runtime_info_get_value_bool(key, &value);

    if (get_platform_version() == 4.0) {
        assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
        return 0;
    }

	return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/battery");
}


/**
 * @testcase		utc_runtime_info_BATTERY_IS_CHARGING_p2
 * @since_tizen		2.3
 * @description		Battery status positive test (set change callback)
 */
int utc_runtime_info_BATTERY_IS_CHARGING_p2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_BATTERY_IS_CHARGING;

    retcode = runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

	if (retcode == RUNTIME_INFO_ERROR_NONE)
	    runtime_info_unset_changed_cb(key);

    if (get_platform_version() == 4.0) {
        assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
        return 0;
    }

	return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/battery");
}


/**
 * @testcase		utc_runtime_info_BATTERY_IS_CHARGING_p3
 * @since_tizen		2.3
 * @description		Battery status positive test (unset change callback)
 */
int utc_runtime_info_BATTERY_IS_CHARGING_p3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_BATTERY_IS_CHARGING;

    runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    retcode = runtime_info_unset_changed_cb(key);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}


/**
 * @testcase		utc_runtime_info_BLUETOOTH_ENABLED_n1
 * @since_tizen		2.3
 * @description		Bluetooth status negative test (key type mismatch)
 */
int utc_runtime_info_BLUETOOTH_ENABLED_n1(void)
{
    char *value = NULL;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_BLUETOOTH_ENABLED;

    retcode = runtime_info_get_value_string(key, &value);

    free(value);
    value = NULL;

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_BLUETOOTH_ENABLED_n2
 * @since_tizen		2.3
 * @description		Bluetooth status negative test (value retrieval; invalid parameters)
 */
int utc_runtime_info_BLUETOOTH_ENABLED_n2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_BLUETOOTH_ENABLED;

    retcode = runtime_info_get_value_bool(key, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_BLUETOOTH_ENABLED_n3
 * @since_tizen		2.3
 * @description		Bluetooth status negative test (set change callback; invalid parameters)
 */
int utc_runtime_info_BLUETOOTH_ENABLED_n3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_BLUETOOTH_ENABLED;

    retcode = runtime_info_set_changed_cb(key, NULL, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_BLUETOOTH_ENABLED_p1
 * @since_tizen		2.3
 * @description		Bluetooth status positive test (value retrieval)
 */
int utc_runtime_info_BLUETOOTH_ENABLED_p1(void)
{
    bool value;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_BLUETOOTH_ENABLED;

    retcode = runtime_info_get_value_bool(key, &value);

    if (get_platform_version() == 4.0) {
        assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
        return 0;
    }

	return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/network.bluetooth");
}


/**
 * @testcase		utc_runtime_info_BLUETOOTH_ENABLED_p2
 * @since_tizen		2.3
 * @description		Bluetooth status positive test (set change callback)
 */
int utc_runtime_info_BLUETOOTH_ENABLED_p2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_BLUETOOTH_ENABLED;

    retcode = runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

	if (retcode == RUNTIME_INFO_ERROR_NONE)
 	   runtime_info_unset_changed_cb(key);

    if (get_platform_version() == 4.0) {
        assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
        return 0;
    }

	return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/network.bluetooth");
}


/**
 * @testcase		utc_runtime_info_BLUETOOTH_ENABLED_p3
 * @since_tizen		2.3
 * @description		Bluetooth status positive test (unset change callback)
 */
int utc_runtime_info_BLUETOOTH_ENABLED_p3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_BLUETOOTH_ENABLED;

    runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    retcode = runtime_info_unset_changed_cb(key);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}


/**
 * @testcase		utc_runtime_info_BLUETOOTH_TETHERING_ENABLED_n1
 * @since_tizen		2.3
 * @description		Bluetooth tethering status negative test (key type mismatch)
 */
int utc_runtime_info_BLUETOOTH_TETHERING_ENABLED_n1(void)
{
    char *value = NULL;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_BLUETOOTH_TETHERING_ENABLED;

    retcode = runtime_info_get_value_string(key, &value);

    free(value);
    value = NULL;

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_BLUETOOTH_TETHERING_ENABLED_n2
 * @since_tizen		2.3
 * @description		Bluetooth tethering status negative test (value retrieval; invalid parameter)
 */
int utc_runtime_info_BLUETOOTH_TETHERING_ENABLED_n2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_BLUETOOTH_TETHERING_ENABLED;

    retcode = runtime_info_get_value_bool(key, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_BLUETOOTH_TETHERING_ENABLED_n3
 * @since_tizen		2.3
 * @description		Bluetooth tethering status negative test (set change callback; invalid parameters)
 */
int utc_runtime_info_BLUETOOTH_TETHERING_ENABLED_n3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_BLUETOOTH_TETHERING_ENABLED;

    retcode = runtime_info_set_changed_cb(key, NULL, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_BLUETOOTH_TETHERING_ENABLED_p1
 * @since_tizen		2.3
 * @description		Bluetooth tethering status positive test (value retrieval)
 */
int utc_runtime_info_BLUETOOTH_TETHERING_ENABLED_p1(void)
{
    bool value;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_BLUETOOTH_TETHERING_ENABLED;

    retcode = runtime_info_get_value_bool(key, &value);

	return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/network.tethering.bluetooth");
}


/**
 * @testcase		utc_runtime_info_BLUETOOTH_TETHERING_ENABLED_p2
 * @since_tizen		2.3
 * @description		Bluetooth tethering status positive test (set change callback)
 */
int utc_runtime_info_BLUETOOTH_TETHERING_ENABLED_p2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_BLUETOOTH_TETHERING_ENABLED;

	retcode = runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

	if (retcode == RUNTIME_INFO_ERROR_NONE)
		runtime_info_unset_changed_cb(key);

	return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/network.tethering.bluetooth");
}


/**
 * @testcase		utc_runtime_info_BLUETOOTH_TETHERING_ENABLED_p3
 * @since_tizen		2.3
 * @description		Bluetooth tethering status positive test (unset change callback)
 */
int utc_runtime_info_BLUETOOTH_TETHERING_ENABLED_p3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_BLUETOOTH_TETHERING_ENABLED;

    runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    retcode = runtime_info_unset_changed_cb(key);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}


/**
 * @testcase		utc_runtime_info_DATA_ROAMING_ENABLED_n1
 * @since_tizen		2.3
 * @description		Data Roaming Status negative test (key type mismatch)
 */
int utc_runtime_info_DATA_ROAMING_ENABLED_n1(void)
{
    char *value = NULL;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_DATA_ROAMING_ENABLED;

    retcode = runtime_info_get_value_string(key, &value);

    free(value);
    value = NULL;

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_DATA_ROAMING_ENABLED_n2
 * @since_tizen		2.3
 * @description		Data Roaming status negative test (value retrieval; invalid parameters)
 */
int utc_runtime_info_DATA_ROAMING_ENABLED_n2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_DATA_ROAMING_ENABLED;

    retcode = runtime_info_get_value_bool(key, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_DATA_ROAMING_ENABLED_n3
 * @since_tizen		2.3
 * @description		Data Roaming status negative test (set change callback; invalid parameters)
 */
int utc_runtime_info_DATA_ROAMING_ENABLED_n3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_DATA_ROAMING_ENABLED;

    retcode = runtime_info_set_changed_cb(key, NULL, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_DATA_ROAMING_ENABLED_p1
 * @since_tizen		2.3
 * @description		Data Roaming status positive test (value retrieval)
 */
int utc_runtime_info_DATA_ROAMING_ENABLED_p1(void)
{
    bool value;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_DATA_ROAMING_ENABLED;

    retcode = runtime_info_get_value_bool(key, &value);

    return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/network.telephony");
}


/**
 * @testcase		utc_runtime_info_DATA_ROAMING_ENABLED_p2
 * @since_tizen		2.3
 * @description		Data Roaming status positive test (set change callback)
 */
int utc_runtime_info_DATA_ROAMING_ENABLED_p2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_DATA_ROAMING_ENABLED;

    retcode = runtime_info_set_changed_cb(key, runtime_info_changed, NULL);
    if (retcode == RUNTIME_INFO_ERROR_NONE)
        runtime_info_unset_changed_cb(key);

    return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/network.telephony");
}


/**
 * @testcase		utc_runtime_info_DATA_ROAMING_ENABLED_p3
 * @since_tizen		2.3
 * @description		Data Roaming status positive test (unset change callback)
 */
int utc_runtime_info_DATA_ROAMING_ENABLED_p3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_DATA_ROAMING_ENABLED;

    runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    retcode = runtime_info_unset_changed_cb(key);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}


/**
 * @testcase		utc_runtime_info_GPS_STATUS_n1
 * @since_tizen		2.3
 * @description		GPS status negative test (key type mismatch)
 */
int utc_runtime_info_GPS_STATUS_n1(void)
{
    char *value = NULL;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_GPS_STATUS;

    retcode = runtime_info_get_value_string(key, &value);

    free(value);
    value = NULL;

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_GPS_STATUS_n2
 * @since_tizen		2.3
 * @description		GPS status negative test (value retrieval; invalid parameters)
 */
int utc_runtime_info_GPS_STATUS_n2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_GPS_STATUS;

    retcode = runtime_info_get_value_int(key, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_GPS_STATUS_n3
 * @since_tizen		2.3
 * @description		GPS status negative test (set change callback; invalid parameters)
 */
int utc_runtime_info_GPS_STATUS_n3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_GPS_STATUS;

    retcode = runtime_info_set_changed_cb(key, NULL, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_GPS_STATUS_p1
 * @since_tizen		2.3
 * @description		GPS status positive test (value retrieval)
 */
int utc_runtime_info_GPS_STATUS_p1(void)
{
    int value;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_GPS_STATUS;

    retcode = runtime_info_get_value_int(key, &value);

    if (get_platform_version() == 4.0) {
        assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
        return 0;
    }

	return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/location.gps");
}


/**
 * @testcase		utc_runtime_info_GPS_STATUS_p2
 * @since_tizen		2.3
 * @description		GPS status positive test (set change callback)
 */
int utc_runtime_info_GPS_STATUS_p2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_GPS_STATUS;

    retcode = runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

	if (retcode == RUNTIME_INFO_ERROR_NONE)
	    runtime_info_unset_changed_cb(key);

    if (get_platform_version() == 4.0) {
        assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
        return 0;
    }

	return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/location.gps");
}


/**
 * @testcase		utc_runtime_info_GPS_STATUS_p3
 * @since_tizen		2.3
 * @description		GPS status positive test (unset change callback)
 */
int utc_runtime_info_GPS_STATUS_p3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_GPS_STATUS;

    runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    retcode = runtime_info_unset_changed_cb(key);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}


/**
 * @testcase		utc_runtime_info_get_value_string_n
 * @since_tizen		2.3
 * @description		Get string type key negative test (invalid parameters)
 */
int utc_runtime_info_get_value_string_n(void)
{
    char *value = NULL;
    int retcode;

    retcode = runtime_info_get_value_string((runtime_info_key_e)NULL, &value);
    assert_neq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}


/**
 * @testcase		utc_runtime_info_PACKET_DATA_ENABLED_n1
 * @since_tizen		2.3
 * @description		Packet data (3G) status negative test (key type mismatch)
 */
int utc_runtime_info_PACKET_DATA_ENABLED_n1(void)
{
    char *value = NULL;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_PACKET_DATA_ENABLED;

    retcode = runtime_info_get_value_string(key, &value);

    free(value);
    value = NULL;

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_PACKET_DATA_ENABLED_n2
 * @since_tizen		2.3
 * @description		Packet data (3G) status negative test (value retrieval; invalid parameters)
 */
int utc_runtime_info_PACKET_DATA_ENABLED_n2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_PACKET_DATA_ENABLED;

    retcode = runtime_info_get_value_bool(key, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_PACKET_DATA_ENABLED_n3
 * @since_tizen		2.3
 * @description		Packet data (3G) status negative test (set change callback; invalid parameters)
 */
int utc_runtime_info_PACKET_DATA_ENABLED_n3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_PACKET_DATA_ENABLED;

    retcode = runtime_info_set_changed_cb(key, NULL, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_PACKET_DATA_ENABLED_p1
 * @since_tizen		2.3
 * @description		Packet data (3G) positive test (value retrieval)
 */
int utc_runtime_info_PACKET_DATA_ENABLED_p1(void)
{
    bool value;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_PACKET_DATA_ENABLED;

    retcode = runtime_info_get_value_bool(key, &value);

    return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/network.telephony");
}


/**
 * @testcase		utc_runtime_info_PACKET_DATA_ENABLED_p2
 * @since_tizen		2.3
 * @description		Packet data (3G) positive test (set change callback)
 */
int utc_runtime_info_PACKET_DATA_ENABLED_p2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_PACKET_DATA_ENABLED;

    retcode = runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    if (retcode == RUNTIME_INFO_ERROR_NONE)
        runtime_info_unset_changed_cb(key);

    return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/network.telephony");
}


/**
 * @testcase		utc_runtime_info_PACKET_DATA_ENABLED_p3
 * @since_tizen		2.3
 * @description		Packet data (3G) positive test (unset change callback)
 */
int utc_runtime_info_PACKET_DATA_ENABLED_p3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_PACKET_DATA_ENABLED;

    runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    retcode = runtime_info_unset_changed_cb(key);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}




/**
 * @testcase		utc_runtime_info_AUTO_ROTATION_ENABLED_n1
 * @since_tizen		2.3
 * @description		Auto rotation feature negative test (key type mismatch)
 */
int utc_runtime_info_AUTO_ROTATION_ENABLED_n1(void)
{
    char *value = NULL;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUTO_ROTATION_ENABLED;

    retcode = runtime_info_get_value_string(key, &value);

    free(value);
    value = NULL;

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_AUTO_ROTATION_ENABLED_n2
 * @since_tizen		2.3
 * @description		Auto rotation feature negative test (value retrieval; invalid parameters)
 */
int utc_runtime_info_AUTO_ROTATION_ENABLED_n2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUTO_ROTATION_ENABLED;

    retcode = runtime_info_get_value_bool(key, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_AUTO_ROTATION_ENABLED_n3
 * @since_tizen		2.3
 * @description		Auto rotation feature negative test (set change callback; invalid parameters)
 */
int utc_runtime_info_AUTO_ROTATION_ENABLED_n3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUTO_ROTATION_ENABLED;

    retcode = runtime_info_set_changed_cb(key, NULL, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_AUTO_ROTATION_ENABLED_p1
 * @since_tizen		2.3
 * @description		Auto rotation feature positive test (value retrieval)
 */
int utc_runtime_info_AUTO_ROTATION_ENABLED_p1(void)
{
    bool value;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUTO_ROTATION_ENABLED;

    retcode = runtime_info_get_value_bool(key, &value);

    if (get_platform_version() == 4.0) {
        assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
        return 0;
    }

	return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/screen.auto_rotation");
}


/**
 * @testcase		utc_runtime_info_AUTO_ROTATION_ENABLED_p2
 * @since_tizen		2.3
 * @description		Auto rotation feature positive test (set change callback)
 */
int utc_runtime_info_AUTO_ROTATION_ENABLED_p2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUTO_ROTATION_ENABLED;

    retcode = runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

	if (retcode == RUNTIME_INFO_ERROR_NONE)
	    runtime_info_unset_changed_cb(key);

    if (get_platform_version() == 4.0) {
        assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
        return 0;
    }

	return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/screen.auto_rotation");
}


/**
 * @testcase		utc_runtime_info_AUTO_ROTATION_ENABLED_p3
 * @since_tizen		2.3
 * @description		Auto rotation feature positive test (unset change callback)
 */
int utc_runtime_info_AUTO_ROTATION_ENABLED_p3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUTO_ROTATION_ENABLED;

    runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    retcode = runtime_info_unset_changed_cb(key);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}




/**
 * @testcase		utc_runtime_info_USB_TETHERING_ENABLED_n1
 * @since_tizen		2.3
 * @description		USB tethering status negative test (key type mismatch)
 */
int utc_runtime_info_USB_TETHERING_ENABLED_n1(void)
{
    char *value = NULL;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_USB_TETHERING_ENABLED;

    retcode = runtime_info_get_value_string(key, &value);

    free(value);
    value = NULL;

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_USB_TETHERING_ENABLED_n2
 * @since_tizen		2.3
 * @description		USB tethering status negative test (value retrieval; invalid parameters)
 */
int utc_runtime_info_USB_TETHERING_ENABLED_n2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_USB_TETHERING_ENABLED;

    retcode = runtime_info_get_value_bool(key, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_USB_TETHERING_ENABLED_n3
 * @since_tizen		2.3
 * @description		USB tethering status negative test (set change callback; invalid parameters)
 */
int utc_runtime_info_USB_TETHERING_ENABLED_n3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_USB_TETHERING_ENABLED;

    retcode = runtime_info_set_changed_cb(key, NULL, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_USB_TETHERING_ENABLED_p1
 * @since_tizen		2.3
 * @description		USB tethering status positive test (value retrieval)
 */
int utc_runtime_info_USB_TETHERING_ENABLED_p1(void)
{
    bool value;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_USB_TETHERING_ENABLED;

    retcode = runtime_info_get_value_bool(key, &value);

	return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/network.tethering.usb");
}


/**
 * @testcase		utc_runtime_info_USB_TETHERING_ENABLED_p2
 * @since_tizen		2.3
 * @description		USB tethering status positive test (set change callback)
 */
int utc_runtime_info_USB_TETHERING_ENABLED_p2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_USB_TETHERING_ENABLED;

	retcode = runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

	if (retcode == RUNTIME_INFO_ERROR_NONE)
		runtime_info_unset_changed_cb(key);

	return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/network.tethering.usb");
}


/**
 * @testcase		utc_runtime_info_USB_TETHERING_ENABLED_p3
 * @since_tizen		2.3
 * @description		USB tethering status positive test (unset change callback)
 */
int utc_runtime_info_USB_TETHERING_ENABLED_p3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_USB_TETHERING_ENABLED;

    runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    retcode = runtime_info_unset_changed_cb(key);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}


/**
 * @testcase		utc_runtime_info_VIBRATION_ENABLED_n1
 * @since_tizen		2.3
 * @description		Vibration status negative test (key type mismatch)
 */
int utc_runtime_info_VIBRATION_ENABLED_n1(void)
{
    char *value = NULL;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_VIBRATION_ENABLED;

    retcode = runtime_info_get_value_string(key, &value);

    free(value);
    value = NULL;

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_VIBRATION_ENABLED_n2
 * @since_tizen		2.3
 * @description		Vibration status negative test (value retrieval; invalid parameters)
 */
int utc_runtime_info_VIBRATION_ENABLED_n2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_VIBRATION_ENABLED;

    retcode = runtime_info_get_value_bool(key, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_VIBRATION_ENABLED_n3
 * @since_tizen		2.3
 * @description		Vibration status negative test (set change callback; invalid parameters)
 */
int utc_runtime_info_VIBRATION_ENABLED_n3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_VIBRATION_ENABLED;

    retcode = runtime_info_set_changed_cb(key, NULL, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_VIBRATION_ENABLED_p1
 * @since_tizen		2.3
 * @description		Vibration status positive test (value retrieval)
 */
int utc_runtime_info_VIBRATION_ENABLED_p1(void)
{
    bool value;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_VIBRATION_ENABLED;

    retcode = runtime_info_get_value_bool(key, &value);

    return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/feedback.vibration");
}


/**
 * @testcase		utc_runtime_info_VIBRATION_ENABLED_p2
 * @since_tizen		2.3
 * @description		Vibration status positive test (set change callback)
 */
int utc_runtime_info_VIBRATION_ENABLED_p2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_VIBRATION_ENABLED;

    retcode = runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    if (retcode == RUNTIME_INFO_ERROR_NONE)
        runtime_info_unset_changed_cb(key);

    return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/feedback.vibration");
}


/**
 * @testcase		utc_runtime_info_VIBRATION_ENABLED_p3
 * @since_tizen		2.3
 * @description		Vibration status positive test (unset change callback)
 */
int utc_runtime_info_VIBRATION_ENABLED_p3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_VIBRATION_ENABLED;

    runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    retcode = runtime_info_unset_changed_cb(key);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}


/**
 * @testcase		utc_runtime_info_WIFI_HOTSPOT_ENABLED_n1
 * @since_tizen		2.3
 * @description		Wifi hotspot status negative test (key type mismatch)
 */
int utc_runtime_info_WIFI_HOTSPOT_ENABLED_n1(void)
{
    char *value = NULL;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_WIFI_HOTSPOT_ENABLED;

    retcode = runtime_info_get_value_string(key, &value);

    free(value);
    value = NULL;

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_WIFI_HOTSPOT_ENABLED_n2
 * @since_tizen		2.3
 * @description		Wifi hotspot status negative test (value retrieval; invalid parameters)
 */
int utc_runtime_info_WIFI_HOTSPOT_ENABLED_n2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_WIFI_HOTSPOT_ENABLED;

    retcode = runtime_info_get_value_bool(key, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_WIFI_HOTSPOT_ENABLED_n3
 * @since_tizen		2.3
 * @description		Wifi hotspot negative test (set change callback; invalid parameters)
 */
int utc_runtime_info_WIFI_HOTSPOT_ENABLED_n3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_WIFI_HOTSPOT_ENABLED;

    retcode = runtime_info_set_changed_cb(key, NULL, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_WIFI_HOTSPOT_ENABLED_p1
 * @since_tizen		2.3
 * @description		Wifi hotspot positive test (value retrieval)
 */
int utc_runtime_info_WIFI_HOTSPOT_ENABLED_p1(void)
{
    bool value;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_WIFI_HOTSPOT_ENABLED;

    retcode = runtime_info_get_value_bool(key, &value);

	return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/network.tethering.wifi");
}


/**
 * @testcase		utc_runtime_info_WIFI_HOTSPOT_ENABLED_p2
 * @since_tizen		2.3
 * @description		Wifi hotspot positive test (set change callback)
 */
int utc_runtime_info_WIFI_HOTSPOT_ENABLED_p2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_WIFI_HOTSPOT_ENABLED;

	retcode = runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

	if (retcode == RUNTIME_INFO_ERROR_NONE)
		runtime_info_unset_changed_cb(key);

	return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/network.tethering.wifi");
}


/**
 * @testcase		utc_runtime_info_WIFI_HOTSPOT_ENABLED_p3
 * @since_tizen		2.3
 * @description		Wifi hotspot positive test (unset change callback)
 */
int utc_runtime_info_WIFI_HOTSPOT_ENABLED_p3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_WIFI_HOTSPOT_ENABLED;

    runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    retcode = runtime_info_unset_changed_cb(key);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}




/**
 * @testcase		utc_runtime_info_TV_OUT_CONNECTED_n1
 * @since_tizen		2.3
 * @description		TV connection status negative test (key type mismatch)
 */
int utc_runtime_info_TV_OUT_CONNECTED_n1(void)
{
    char *value = NULL;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_TV_OUT_CONNECTED;

    retcode = runtime_info_get_value_string(key, &value);

    free(value);
    value = NULL;

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_TV_OUT_CONNECTED_n2
 * @since_tizen		2.3
 * @description		TV connection status negative test (value retrieval; invalid parameters)
 */
int utc_runtime_info_TV_OUT_CONNECTED_n2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_TV_OUT_CONNECTED;

    retcode = runtime_info_get_value_bool(key, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_TV_OUT_CONNECTED_n3
 * @since_tizen		2.3
 * @description		TV connection status negative test (set change callback; invalid parameters)
 */
int utc_runtime_info_TV_OUT_CONNECTED_n3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_TV_OUT_CONNECTED;

    retcode = runtime_info_set_changed_cb(key, NULL, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_TV_OUT_CONNECTED_p1
 * @since_tizen		2.3
 * @description		TV connection status positive test (value retrieval)
 */
int utc_runtime_info_TV_OUT_CONNECTED_p1(void)
{
    bool value;
    int retcode;
    bool support = false;

    runtime_info_key_e key = RUNTIME_INFO_KEY_TV_OUT_CONNECTED;

    retcode = runtime_info_get_value_bool(key, &value);

    system_info_get_platform_bool("http://tizen.org/feature/screen.output.hdmi", &support);
    if (!support)
        system_info_get_platform_bool("http://tizen.org/feature/screen.output.rca", &support);

    if (support)
        assert_eq(retcode, SYSTEM_INFO_ERROR_NONE);
    else
        assert_eq(retcode, RUNTIME_INFO_ERROR_NOT_SUPPORTED);

    return 0;
}


/**
 * @testcase		utc_runtime_info_TV_OUT_CONNECTED_p2
 * @since_tizen		2.3
 * @description		TV connection status positive test (set change callback)
 */
int utc_runtime_info_TV_OUT_CONNECTED_p2(void)
{
    int retcode;
    bool support = false;
    runtime_info_key_e key = RUNTIME_INFO_KEY_TV_OUT_CONNECTED;

    retcode = runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    system_info_get_platform_bool("http://tizen.org/feature/screen.output.hdmi", &support);
    if (!support)
        system_info_get_platform_bool("http://tizen.org/feature/screen.output.rca", &support);

    if (support)
        assert_eq(retcode, SYSTEM_INFO_ERROR_NONE);
    else
        assert_eq(retcode, RUNTIME_INFO_ERROR_NOT_SUPPORTED);

    runtime_info_unset_changed_cb(key);

    return 0;
}


/**
 * @testcase		utc_runtime_info_TV_OUT_CONNECTED_p3
 * @since_tizen		2.3
 * @description		TV connection status positive test (unset change callback)
 */
int utc_runtime_info_TV_OUT_CONNECTED_p3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_TV_OUT_CONNECTED;

    runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    retcode = runtime_info_unset_changed_cb(key);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}


/**
 * @testcase		utc_runtime_info_AUDIO_JACK_STATUS_n1
 * @since_tizen		2.3
 * @description		Audio jack status negative test (key type mismatch)
 */
int utc_runtime_info_AUDIO_JACK_STATUS_n1(void)
{
    char *value = NULL;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUDIO_JACK_STATUS;

    retcode = runtime_info_get_value_string(key, &value);

    free(value);
    value = NULL;

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_AUDIO_JACK_STATUS_n2
 * @since_tizen		2.3
 * @description		Audio jack status negative test (value retrieval; invalid parameters)
 */
int utc_runtime_info_AUDIO_JACK_STATUS_n2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUDIO_JACK_STATUS;

    retcode = runtime_info_get_value_int(key, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_AUDIO_JACK_STATUS_n3
 * @since_tizen		2.3
 * @description		Audio jack status negative test (set change callback; invalid parameters)
 */
int utc_runtime_info_AUDIO_JACK_STATUS_n3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUDIO_JACK_STATUS;

    retcode = runtime_info_set_changed_cb(key, NULL, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_AUDIO_JACK_STATUS_p1
 * @since_tizen		2.3
 * @description		Audio jack status positive test (value retrieval)
 */
int utc_runtime_info_AUDIO_JACK_STATUS_p1(void)
{
    int value;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUDIO_JACK_STATUS;


    retcode = runtime_info_get_value_int(key, &value);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}


/**
 * @testcase		utc_runtime_info_AUDIO_JACK_STATUS_p2
 * @since_tizen		2.3
 * @description		Audio jack status positive test (set change callback)
 */
int utc_runtime_info_AUDIO_JACK_STATUS_p2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUDIO_JACK_STATUS;

    retcode = runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);

    runtime_info_unset_changed_cb(key);

    return 0;
}


/**
 * @testcase		utc_runtime_info_AUDIO_JACK_STATUS_p3
 * @since_tizen		2.3
 * @description		Audio jack status positive test (unset change callback)
 */
int utc_runtime_info_AUDIO_JACK_STATUS_p3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUDIO_JACK_STATUS;

    runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    retcode = runtime_info_unset_changed_cb(key);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}




/**
 * @testcase		utc_runtime_info_USB_CONNECTED_n1
 * @since_tizen		2.3
 * @description		USB connection status negative test (key type mismatch)
 */
int utc_runtime_info_USB_CONNECTED_n1(void)
{
    char *value = NULL;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_USB_CONNECTED;

    retcode = runtime_info_get_value_string(key, &value);

    free(value);
    value = NULL;

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_USB_CONNECTED_n2
 * @since_tizen		2.3
 * @description		USB connection status negative test (value retrieval; invalid parameters)
 */
int utc_runtime_info_USB_CONNECTED_n2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_USB_CONNECTED;

    retcode = runtime_info_get_value_bool(key, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_USB_CONNECTED_n3
 * @since_tizen		2.3
 * @description		USB connection status negative test (set change callback; invalid parameters)
 */
int utc_runtime_info_USB_CONNECTED_n3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_USB_CONNECTED;

    retcode = runtime_info_set_changed_cb(key, NULL, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_USB_CONNECTED_p1
 * @since_tizen		2.3
 * @description		USB connection status positive test (value retrieval)
 */
int utc_runtime_info_USB_CONNECTED_p1(void)
{
    bool value;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_USB_CONNECTED;

    retcode = runtime_info_get_value_bool(key, &value);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}


/**
 * @testcase		utc_runtime_info_USB_CONNECTED_p2
 * @since_tizen		2.3
 * @description		USB connection status positive test (set change callback)
 */
int utc_runtime_info_USB_CONNECTED_p2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_USB_CONNECTED;

    retcode = runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);

    runtime_info_unset_changed_cb(key);

    return 0;
}


/**
 * @testcase		utc_runtime_info_USB_CONNECTED_p3
 * @since_tizen		2.3
 * @description		USB connection status positive test (unset change callback)
 */
int utc_runtime_info_USB_CONNECTED_p3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_USB_CONNECTED;

    runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    retcode = runtime_info_unset_changed_cb(key);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}


/**
 * @testcase		utc_runtime_info_CHARGER_CONNECTED_n1
 * @since_tizen		2.3
 * @description		Charger connection status negative test (key type mismatch)
 */
int utc_runtime_info_CHARGER_CONNECTED_n1(void)
{
    char *value = NULL;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_CHARGER_CONNECTED;

    retcode = runtime_info_get_value_string(key, &value);

    free(value);
    value = NULL;

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_CHARGER_CONNECTED_n2
 * @since_tizen		2.3
 * @description		Charger connection status negative test (value retrieval; invalid parameters)
 */
int utc_runtime_info_CHARGER_CONNECTED_n2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_CHARGER_CONNECTED;

    retcode = runtime_info_get_value_bool(key, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_CHARGER_CONNECTED_n3
 * @since_tizen		2.3
 * @description		Charger connection status negative test (set change callback; invalid parameters)
 */
int utc_runtime_info_CHARGER_CONNECTED_n3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_CHARGER_CONNECTED;

    retcode = runtime_info_set_changed_cb(key, NULL, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
    return 0;
}


/**
 * @testcase		utc_runtime_info_CHARGER_CONNECTED_p1
 * @since_tizen		2.3
 * @description		Charger connection status positive test (value retrieval)
 */
int utc_runtime_info_CHARGER_CONNECTED_p1(void)
{
    bool value;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_CHARGER_CONNECTED;

    retcode = runtime_info_get_value_bool(key, &value);

    if (get_platform_version() == 4.0) {
        assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
        return 0;
    }

	return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/battery");
}


/**
 * @testcase		utc_runtime_info_CHARGER_CONNECTED_p2
 * @since_tizen		2.3
 * @description		Charger connection status positive test (set change callback)
 */
int utc_runtime_info_CHARGER_CONNECTED_p2(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_CHARGER_CONNECTED;

    retcode = runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

	if (retcode == RUNTIME_INFO_ERROR_NONE)
	    runtime_info_unset_changed_cb(key);

    if (get_platform_version() == 4.0) {
        assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
        return 0;
    }

	return compare_retcode_with_feature_support(retcode, "http://tizen.org/feature/battery");
}


/**
 * @testcase		utc_runtime_info_CHARGER_CONNECTED_p3
 * @since_tizen		2.3
 * @description		Charger connection status positive test (unset change callback)
 */
int utc_runtime_info_CHARGER_CONNECTED_p3(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_CHARGER_CONNECTED;

    runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    retcode = runtime_info_unset_changed_cb(key);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_runtime_info_get_value_int_p
 * @since_tizen		2.3
 * @description		Get int type key positive test
 */
int utc_runtime_info_get_value_int_p(void)
{
    int value;
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUDIO_JACK_STATUS;

    retcode = runtime_info_get_value_int(key, &value);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}


/**
 * @testcase		utc_runtime_info_set_changed_cb_p
 * @since_tizen		2.3
 * @description		Set change callback positive test
 */
int utc_runtime_info_set_changed_cb_p(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUDIO_JACK_CONNECTED;

    retcode = runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);

    runtime_info_unset_changed_cb(key);

    return 0;
}


/**
 * @testcase		utc_runtime_info_unset_changed_cb_p
 * @since_tizen		2.3
 * @description		Unset change callback positive test
 */
int utc_runtime_info_unset_changed_cb_p(void)
{
    int retcode;
    runtime_info_key_e key = RUNTIME_INFO_KEY_AUDIO_JACK_CONNECTED;

    runtime_info_set_changed_cb(key, runtime_info_changed, NULL);

    retcode = runtime_info_unset_changed_cb(key);

    assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}




/**
 * @testcase		utc_runtime_info_get_value_int_n
 * @since_tizen		2.3
 * @description		Get int type key negative test (invalid parameters)
 */
int utc_runtime_info_get_value_int_n(void)
{
    int value;
    int retcode;

    retcode = runtime_info_get_value_int((runtime_info_key_e)NULL, &value);

    assert_neq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}
/**
 * @testcase		utc_runtime_info_set_changed_cb_n
 * @since_tizen		2.3
 * @description		Set change callback negative test (invalid parameters)
 */
int utc_runtime_info_set_changed_cb_n(void)
{
    int retcode;

    retcode = runtime_info_set_changed_cb((runtime_info_key_e)NULL, NULL, NULL);

    assert_neq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}



/**
 * @testcase		utc_runtime_info_unset_changed_cb_n
 * @since_tizen		2.3
 * @description		Unset change callback negative test (invalid parameters)
 */
int utc_runtime_info_unset_changed_cb_n(void)
{
    int retcode;

    retcode = runtime_info_unset_changed_cb(-1);

    assert_neq(retcode, RUNTIME_INFO_ERROR_NONE);
    return 0;
}


/* Memory usage TC */
/**
 * @testcase		utc_runtime_info_get_system_memory_info_p
 * @since_tizen		2.3
 * @description		System memory info retrieval positive test
 */
int utc_runtime_info_get_system_memory_info_p(void)
{
	int retcode;
	runtime_memory_info_s info;

	retcode = runtime_info_get_system_memory_info(&info);

	assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_system_memory_info_n
 * @since_tizen		2.3
 * @description		System memory info retrieval negative test (invalid parameters)
 */
int utc_runtime_info_get_system_memory_info_n(void)
{
	int retcode;

	retcode = runtime_info_get_system_memory_info(NULL);

	assert_neq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_process_memory_info_p
 * @since_tizen		2.3
 * @description		Process memory info retrieval positive test
 */
int utc_runtime_info_get_process_memory_info_p(void)
{
	int retcode;
	process_memory_info_s *info;
	int pids[1];

	pids[0] = getpid();
	retcode = runtime_info_get_process_memory_info(pids, 1, &info);

	if (!is_resourced_activated())
		assert_eq(retcode, RUNTIME_INFO_ERROR_REMOTE_IO);
	else
		assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_process_memory_info_n_1
 * @since_tizen		2.3
 * @description		Process memory info retrieval negative test (invalid parameters)
 */
int utc_runtime_info_get_process_memory_info_n_1(void)
{
	int retcode;
	process_memory_info_s *info;

	retcode = runtime_info_get_process_memory_info(NULL, 1, &info);

	assert_neq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_process_memory_info_n_2
 * @since_tizen		2.3
 * @description		Process memory info retrieval negative test (invalid parameters)
 */
int utc_runtime_info_get_process_memory_info_n_2(void)
{
	int retcode;
	process_memory_info_s *info;
	int pids[1];

	pids[0] = getpid();
	retcode = runtime_info_get_process_memory_info(pids, -1, &info);

	assert_neq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_process_memory_info_n_3
 * @since_tizen		2.3
 * @description		Process memory info retrieval negative test (invalid parameters)
 */
int utc_runtime_info_get_process_memory_info_n_3(void)
{
	int retcode;
	int pids[1];

	pids[0] = getpid();
	retcode = runtime_info_get_process_memory_info(pids, 1, NULL);

	assert_neq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/* Cpu usage TC */
/**
 * @testcase		utc_runtime_info_get_cpu_usage_p
 * @since_tizen		2.3
 * @description		System CPU usage info retrieval positive test
 */
int utc_runtime_info_get_cpu_usage_p(void)
{
	int retcode;
	runtime_cpu_usage_s usage;

	retcode = runtime_info_get_cpu_usage(&usage);

	assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_cpu_usage_n
 * @since_tizen		2.3
 * @description		System CPU usage info retrieval negative test (invalid parameters)
 */
int utc_runtime_info_get_cpu_usage_n(void)
{
	int retcode;

	retcode = runtime_info_get_cpu_usage(NULL);

	assert_neq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_process_cpu_usage_p
 * @since_tizen		2.3
 * @description		Process CPU usage info retrieval positive test
 */
int utc_runtime_info_get_process_cpu_usage_p(void)
{
	int retcode;
	process_cpu_usage_s *usage;
	int pids[1];

	pids[0] = getpid();
	retcode = runtime_info_get_process_cpu_usage(pids, 1, &usage);

	if (!is_resourced_activated())
		assert_eq(retcode, RUNTIME_INFO_ERROR_REMOTE_IO);
	else
		assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_process_cpu_usage_n_1
 * @since_tizen		2.3
 * @description		Process CPU usage info retrieval negative test (invalid parameters)
 */
int utc_runtime_info_get_process_cpu_usage_n_1(void)
{
	int retcode;
	process_cpu_usage_s *usage;

	retcode = runtime_info_get_process_cpu_usage(NULL, 1, &usage);

	assert_neq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_process_cpu_usage_n_2
 * @since_tizen		2.3
 * @description		Process CPU usage info retrieval negative test (invalid parameters)
 */
int utc_runtime_info_get_process_cpu_usage_n_2(void)
{
	int retcode;
	process_cpu_usage_s *usage;
	int pids[1];

	pids[0] = getpid();
	retcode = runtime_info_get_process_cpu_usage(pids, -1, &usage);

	assert_neq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_process_cpu_usage_n_3
 * @since_tizen		2.3
 * @description		Process CPU usage info retrieval negative test (invalid parameters)
 */
int utc_runtime_info_get_process_cpu_usage_n_3(void)
{
	int retcode;
	int pids[1];

	pids[0] = getpid();
	retcode = runtime_info_get_process_cpu_usage(pids, 1, NULL);

	assert_neq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_processor_count_p
 * @since_tizen		3.0
 * @description		Get processor count positive test
 */
int utc_runtime_info_get_processor_count_p(void)
{
	int retcode;
	int num_processor;

	retcode = runtime_info_get_processor_count(&num_processor);

	assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_processor_count_n
 * @since_tizen		3.0
 * @description		Get processor count negative test (invalid parameter)
 */
int utc_runtime_info_get_processor_count_n(void)
{
	int retcode;
	int *num_processor = NULL;

	retcode = runtime_info_get_processor_count(num_processor);

	assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_processor_current_frequency_p
 * @since_tizen		3.0
 * @description		Get processor current frequency positive test
 */
int utc_runtime_info_get_processor_current_frequency_p(void)
{
	int retcode;
	int core_number = 0;
	int core_frequency;

	retcode = runtime_info_get_processor_current_frequency(core_number, &core_frequency);

	assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_processor_current_frequency_n_1
 * @since_tizen		3.0
 * @description		Get processor current frequency negative test (invalid parameter)
 */
int utc_runtime_info_get_processor_current_frequency_n_1(void)
{
	int retcode;
	int core_number = -1;
	int core_frequency;

	retcode = runtime_info_get_processor_current_frequency(core_number, &core_frequency);

	assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_processor_current_frequency_n_2
 * @since_tizen		3.0
 * @description		Get processor current frequency negative test (invalid parameter)
 */
int utc_runtime_info_get_processor_current_frequency_n_2(void)
{
	int retcode;
	int core_number = 0;
	int *core_frequency = NULL;

	retcode = runtime_info_get_processor_current_frequency(core_number, core_frequency);

	assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_processor_max_frequency_p
 * @since_tizen		3.0
 * @description		Get processor max frequency positive test
 */
int utc_runtime_info_get_processor_max_frequency_p(void)
{
	int retcode;
	int core_number = 0;
	int core_frequency;

	retcode = runtime_info_get_processor_max_frequency(core_number, &core_frequency);

	assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_processor_max_frequency_n_1
 * @since_tizen		3.0
 * @description		Get processor max frequency negative test (invalid parameter)
 */
int utc_runtime_info_get_processor_max_frequency_n_1(void)
{
	int retcode;
	int core_number = -1;
	int core_frequency;

	retcode = runtime_info_get_processor_max_frequency(core_number, &core_frequency);

	assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_processor_max_frequency_n_2
 * @since_tizen		3.0
 * @description		Get processor max frequency negative test (invalid parameter)
 */
int utc_runtime_info_get_processor_max_frequency_n_2(void)
{
	int retcode;
	int core_number = 0;
	int *core_frequency = NULL;

	retcode = runtime_info_get_processor_max_frequency(core_number, core_frequency);

	assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_physical_memory_size_p
 * @since_tizen		4.0
 * @description		Get physical memory size positive test
 */
int utc_runtime_info_get_physical_memory_size_p(void)
{
	int retcode;
	int size;

	retcode = runtime_info_get_physical_memory_size(&size);

	assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_physical_memory_size_n
 * @since_tizen		4.0
 * @description		Get physical memory size negative test (invalid parameter)
 */
int utc_runtime_info_get_physical_memory_size_n(void)
{
	int retcode;
	int *size = NULL;

	retcode = runtime_info_get_physical_memory_size(size);

	assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase        utc_runtime_info_app_usage_destroy_p
 * @since_tizen     4.0
 * @description     Destroy app usage handle positive test
 */
int utc_runtime_info_app_usage_destroy_p(void)
{
	int retcode;
	app_usage_h handle;

	retcode = runtime_info_get_all_apps_memory_usage(&handle);
	if (retcode == RUNTIME_INFO_ERROR_REMOTE_IO)
		return is_resourced_activated() ? 1 : 0;
	else if (retcode != RUNTIME_INFO_ERROR_NONE)
		return 1;

	retcode = runtime_info_app_usage_destroy(handle);

	assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase        utc_runtime_info_app_usage_destroy_n
 * @since_tizen     4.0
 * @description     Destroy app usage handle negative test (invalid parameter)
 */
int utc_runtime_info_app_usage_destroy_n(void)
{
	int retcode;

	retcode = runtime_info_app_usage_destroy(NULL);

	assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase        utc_runtime_info_app_usage_get_count_p
 * @since_tizen     4.0
 * @description     Get the app count positive test
 */
int utc_runtime_info_app_usage_get_count_p(void)
{
	int retcode;
	app_usage_h handle;
	int count;

	retcode = runtime_info_get_all_apps_memory_usage(&handle);
	if (retcode == RUNTIME_INFO_ERROR_REMOTE_IO)
		return is_resourced_activated() ? 1 : 0;
	else if (retcode != RUNTIME_INFO_ERROR_NONE)
		return 1;

	retcode = runtime_info_app_usage_get_count(handle, &count);

	assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase        utc_runtime_info_app_usage_get_count_n_1
 * @since_tizen     4.0
 * @description     Get the app count negative test (invalid input parameter)
 */
int utc_runtime_info_app_usage_get_count_n_1(void)
{
	int retcode;
	int count;

	retcode = runtime_info_app_usage_get_count(NULL, &count);

	assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase        utc_runtime_info_app_usage_get_count_n_2
 * @since_tizen     4.0
 * @description     Get the app count negative test (invalid output parameter)
 */
int utc_runtime_info_app_usage_get_count_n_2(void)
{
	int retcode;
	app_usage_h handle;

	retcode = runtime_info_get_all_apps_cpu_rate(&handle);
	if (retcode == RUNTIME_INFO_ERROR_REMOTE_IO)
		return is_resourced_activated() ? 1 : 0;
	else if (retcode != RUNTIME_INFO_ERROR_NONE)
		return 1;

	retcode = runtime_info_app_usage_get_count(handle, NULL);

	assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase        utc_runtime_info_app_usage_get_appid_p
 * @since_tizen     4.0
 * @description     Get the app appid positive test
 */
int utc_runtime_info_app_usage_get_appid_p(void)
{
	int retcode;
	app_usage_h handle;
	char *appid;

	retcode = runtime_info_get_all_apps_cpu_rate(&handle);
	if (retcode == RUNTIME_INFO_ERROR_REMOTE_IO)
		return is_resourced_activated() ? 1 : 0;
	else if (retcode != RUNTIME_INFO_ERROR_NONE)
		return 1;

	retcode = runtime_info_app_usage_get_appid(handle, 0, &appid);

	assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase        utc_runtime_info_app_usage_get_appid_n_1
 * @since_tizen     4.0
 * @description     Get the app appid negative test (invalid input parameter)
 */
int utc_runtime_info_app_usage_get_appid_n_1(void)
{
	int retcode;
	char *appid;

	retcode = runtime_info_app_usage_get_appid(NULL, -1, &appid);

	assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase        utc_runtime_info_app_usage_get_appid_n_2
 * @since_tizen     4.0
 * @description     Get the app appid negative test (invalid output parameter)
 */
int utc_runtime_info_app_usage_get_appid_n_2(void)
{
	int retcode;
	app_usage_h handle;

	retcode = runtime_info_get_all_apps_cpu_rate(&handle);
	if (retcode == RUNTIME_INFO_ERROR_REMOTE_IO)
		return is_resourced_activated() ? 1 : 0;
	else if (retcode != RUNTIME_INFO_ERROR_NONE)
		return 1;

	retcode = runtime_info_app_usage_get_appid(handle, 0, NULL);

	assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase        utc_runtime_info_app_usage_get_usage_p
 * @since_tizen     4.0
 * @description     Get the app usage positive test
 */
int utc_runtime_info_app_usage_get_usage_p(void)
{
	int retcode;
	app_usage_h handle;
	unsigned int usage;

	retcode = runtime_info_get_all_apps_memory_usage(&handle);
	if (retcode == RUNTIME_INFO_ERROR_REMOTE_IO)
		return is_resourced_activated() ? 1 : 0;
	else if (retcode != RUNTIME_INFO_ERROR_NONE)
		return 1;

	retcode = runtime_info_app_usage_get_usage(handle, 0, &usage);

	assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase        utc_runtime_info_app_usage_get_usage_n_1
 * @since_tizen     4.0
 * @description     Get the app usage negative test (invalid input parameter)
 */
int utc_runtime_info_app_usage_get_usage_n_1(void)
{
	int retcode;
	unsigned int usage;

	retcode = runtime_info_app_usage_get_usage(NULL, -1, &usage);

	assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase        utc_runtime_info_app_usage_get_usage_n_2
 * @since_tizen     4.0
 * @description     Get the app usage negative test (invalid output parameter)
 */
int utc_runtime_info_app_usage_get_usage_n_2(void)
{
	int retcode;
	app_usage_h handle;

	retcode = runtime_info_get_all_apps_memory_usage(&handle);
	if (retcode == RUNTIME_INFO_ERROR_REMOTE_IO)
		return is_resourced_activated() ? 1 : 0;
	else if (retcode != RUNTIME_INFO_ERROR_NONE)
		return 1;

	retcode = runtime_info_app_usage_get_usage(handle, 0, NULL);

	assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_all_apps_memory_usage_p
 * @since_tizen		4.0
 * @description		Get all apps' memory usage positive test
 */
int utc_runtime_info_get_all_apps_memory_usage_p(void)
{
	int retcode;
	app_usage_h handle;

	retcode = runtime_info_get_all_apps_memory_usage(&handle);

	if (!is_resourced_activated())
		assert_eq(retcode, RUNTIME_INFO_ERROR_REMOTE_IO);
	else
		assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_all_apps_memory_usage_n
 * @since_tizen		4.0
 * @description		Get all apps' memory usage negative test (invalid parameter)
 */
int utc_runtime_info_get_all_apps_memory_usage_n(void)
{
	int retcode;

	retcode = runtime_info_get_all_apps_memory_usage(NULL);

	assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_all_apps_cpu_rate_p
 * @since_tizen		4.0
 * @description		Get all apps' CPU rate positive test
 */
int utc_runtime_info_get_all_apps_cpu_rate_p(void)
{
	int retcode;
	app_usage_h handle;

	retcode = runtime_info_get_all_apps_cpu_rate(&handle);

	if (!is_resourced_activated())
		assert_eq(retcode, RUNTIME_INFO_ERROR_REMOTE_IO);
	else
		assert_eq(retcode, RUNTIME_INFO_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_runtime_info_get_all_apps_cpu_rate_n
 * @since_tizen		4.0
 * @description		Get all apps' CPU rate negative test (invalid parameter)
 */
int utc_runtime_info_get_all_apps_cpu_rate_n(void)
{
	int retcode;

	retcode = runtime_info_get_all_apps_cpu_rate(NULL);

	assert_eq(retcode, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
	return 0;
}
