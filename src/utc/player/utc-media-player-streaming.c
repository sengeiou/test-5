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
#include <glib.h>
#include <Elementary.h>
#include <storage.h>
#include <system_info.h>
#include <media/player.h>
#include <curl/curl.h>
#include "tct_common.h"
#include "net_connection.h"
#include <dlog.h>

#define API_NAMESPACE    "[PLAYER]"

//& set: MediaPlayerStreaming

#define CONFIG_LINE_LEN_MAX     2048   //maximum key-value line length
#define CONFIG_VALUE_LEN_MAX    1024   //maximum length of value
#define COOKIE_EXAMPLE "cookie example"

static player_h player = NULL;
static connection_h connection = NULL;
static bool wifi_supported = false;
static bool telepony_supported = false;
static bool ethernet_supported = false;

static bool _is_broken = false;
static bool _is_pass = false;
static bool _is_network_supportable = false;
static char g_media_path[CONFIG_VALUE_LEN_MAX] = {0,};
static char g_media_adaptive_path[CONFIG_VALUE_LEN_MAX] = {0,};

bool get_value_from_config(char* key, char* value)
{
        if ( NULL == key )
        {
            return false;
        }
        FILE* pfilePtr = fopen(CONFIGFILE_PATH, "r");
        if ( NULL == pfilePtr )
        {
            return false;
        }

        char* pszKey = NULL;
        char* pszValue = NULL;
        char* pszDelim = "=\n";
        char szConfigLine[CONFIG_LINE_LEN_MAX] = {0,};

        while ( !feof(pfilePtr) )
        {
                if ( fgets(szConfigLine, CONFIG_LINE_LEN_MAX, pfilePtr) != NULL )
                {
                        pszKey = strtok(szConfigLine, pszDelim);
                        pszValue = strtok(NULL, pszDelim);
                        if ( pszKey != NULL ) {
	                        if ( 0 == strcmp(pszKey, key) )
	                        {
	                                break;
	                        }
                        }
                        pszKey = NULL;
                        pszValue = NULL;
                }
        }

        fclose(pfilePtr);
        if ( NULL == pszValue )
        {
                return false;
        }

        if ( strlen(pszValue) >= CONFIG_VALUE_LEN_MAX )
        {
                return false;
        }

        memset(value, 0, CONFIG_VALUE_LEN_MAX);
        strncpy(value, pszValue, strlen(pszValue));
        return true;
}

bool check_online_status(char *media_path)
{
	bool ret = true;
	CURL *curl = NULL;
	CURLcode res = CURLE_OK;

	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, media_path);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT_MS, 10000L);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 10000L);
		curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
		curl_easy_setopt(curl, CURLOPT_IPRESOLVE, 1L);

		res = curl_easy_perform(curl);
		if(res != CURLE_OK) {
			PRINT_UTC_LOG("[Line : %d][%s] curl_easy_perform() failed: %s\n", __LINE__, API_NAMESPACE, curl_easy_strerror(res));
			ret = false;
		}

		curl_easy_cleanup(curl);
	}

	return ret;

}

bool check_connection_statistics(connection_h connection, long long *size)
{
	long long rv = 0;
	int err = CONNECTION_ERROR_NONE;
	connection_type_e type = CONNECTION_TYPE_DISCONNECTED;

	if (wifi_supported) {
		type = CONNECTION_TYPE_WIFI;
	} else if (telepony_supported) {
		type = CONNECTION_TYPE_CELLULAR;
	} else {
		PRINT_UTC_LOG("[Line : %d][%s] network is not supportable.\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	err = connection_get_statistics(connection, type, CONNECTION_STATISTICS_TYPE_TOTAL_RECEIVED_DATA, &rv);

	if (err != CONNECTION_ERROR_NONE) {
		PRINT_UTC_LOG("[Line : %d][%s] Failed to check connection statistics.\\n", __LINE__, API_NAMESPACE);
		return false;
	} else {
		PRINT_UTC_LOG("[Line : %d][%s] WiFi last recv data size [%lld]\\n", __LINE__, API_NAMESPACE, rv);
	}

	*size = rv;
	return true;
}

static int _player_prepare_with_connection_check(gchar *media_path)
{
	int ret = PLAYER_ERROR_NONE;
	long long before = 0, after = 0;

	if (!check_online_status(media_path)) {
		PRINT_UTC_LOG("[Line : %d][%s][Reference] network is disconnected\\n", __LINE__, API_NAMESPACE);
	}

	if (connection && !check_connection_statistics(connection, &before)) {
		PRINT_UTC_LOG("[Line : %d][%s] Failed to get connection statistics\\n", __LINE__, API_NAMESPACE);
	}

	ret = player_prepare(player);

	if (connection) {
		if (!check_connection_statistics(connection, &after)) {
			PRINT_UTC_LOG("[Line : %d][%s] Failed to get connection statistics\\n", __LINE__, API_NAMESPACE);
		} else {
			PRINT_UTC_LOG("[Line : %d][%s][Reference] total received data [%lld]\\n", __LINE__, API_NAMESPACE, (after-before));
		}
	}

	if (ret != PLAYER_ERROR_NONE) {
		PRINT_UTC_LOG("[Line : %d][%s] Failed to player_prepare 0x%X\\n", __LINE__, API_NAMESPACE, ret);
	}

	return ret;
}

bool check_network_supportable(void)
{
#define _FEATURE_NAME_WIFI      "http://tizen.org/feature/network.wifi"
#define _FEATURE_NAME_TELEPHONY "http://tizen.org/feature/network.telephony"
#define _FEATURE_NAME_ETHERNET  "http://tizen.org/feature/network.ethernet"

	system_info_get_platform_bool(_FEATURE_NAME_WIFI, &wifi_supported);
	system_info_get_platform_bool(_FEATURE_NAME_TELEPHONY, &telepony_supported);
	system_info_get_platform_bool(_FEATURE_NAME_ETHERNET, &ethernet_supported);

	if (wifi_supported || telepony_supported || ethernet_supported)
		return true;

	PRINT_UTC_LOG("[Line : %d][%s] network is not supportable.\\n", __LINE__, API_NAMESPACE);
	return false;
}

/**
 * @function		utc_media_player_streaming_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_player_streaming_startup(void)
{
    _is_broken = false;
    _is_pass = false;

    _is_network_supportable = check_network_supportable();

    if (true != get_value_from_config("PLAYER_HTTP_STREAMING_URL", g_media_path)) {
        PRINT_UTC_LOG("[Line : %d][%s] Failed to get value from config\\n", __LINE__, API_NAMESPACE);
        _is_broken = true;
    }

    if (true != get_value_from_config("PLAYER_ADAPTIVE_STREAMING_URL", g_media_adaptive_path)) {
        PRINT_UTC_LOG("[Line : %d][%s] Failed to get value from config\\n", __LINE__, API_NAMESPACE);
        _is_broken = true;
    }

    int ret = player_create(&player);
    if (PLAYER_ERROR_NONE != ret) {
        _is_broken = true;
        return;
    }

    if (connection_create(&connection) != CONNECTION_ERROR_NONE) {
        PRINT_UTC_LOG("[Line : %d][%s] Failed to create connection handle\\n", __LINE__, API_NAMESPACE);
    } else {
		PRINT_UTC_LOG("[Line : %d][%s] Success to create connection handle %p\\n", __LINE__, API_NAMESPACE, connection);
    }
}

/**
 * @function		utc_media_player_streaming_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_player_streaming_cleanup(void)
{
    if (connection && connection_destroy(connection) != CONNECTION_ERROR_NONE) {
        PRINT_UTC_LOG("[Line : %d][%s] Failed to destroy connection handle\\n", __LINE__, API_NAMESPACE);
    }

    player_destroy(player);
}

/**
 * @testcase		utc_media_player_get_streaming_download_progress_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get streaming download progress
 */
int utc_media_player_get_streaming_download_progress_p(void)
{
	assert(!_is_broken);

	int ret = PLAYER_ERROR_NONE;
	int start;
	int current;

	ret = player_set_streaming_cookie(player, COOKIE_EXAMPLE, sizeof(COOKIE_EXAMPLE));
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_set_uri(player, g_media_path);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = _player_prepare_with_connection_check(g_media_path);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_start(player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_get_streaming_download_progress(player, &start, &current);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_stop(player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_unprepare(player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	if (start < 0 || start > 100 || current < 0 || current > 100) {
		assert(false);
	}

	return 0;
}

/**
 * @testcase		utc_media_player_get_streaming_download_progress_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get streaming download progress
 */
int utc_media_player_get_streaming_download_progress_n(void)
{
	int ret = PLAYER_ERROR_NONE;
	int start;
	int current;

	ret = player_set_streaming_cookie(player, COOKIE_EXAMPLE, sizeof(COOKIE_EXAMPLE));
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_set_uri(player, g_media_path);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = _player_prepare_with_connection_check(g_media_path);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_start(player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_get_streaming_download_progress(NULL, &start, &current);
	assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

	ret = player_stop(player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_unprepare(player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_player_get_streaming_download_progress_n2
 * @since_tizen		2.3.1
 * @description		Negative test case to get streaming download progress
 */
int utc_media_player_get_streaming_download_progress_n2(void)
{
	int ret = PLAYER_ERROR_NONE;
    int start;
    int current;

    ret = player_set_streaming_cookie(player, COOKIE_EXAMPLE, sizeof(COOKIE_EXAMPLE));
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_set_uri(player, g_media_path);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_get_streaming_download_progress(player, &start, &current);
    assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

    return 0;
}

/**
 * @testcase		utc_media_player_set_streaming_cookie_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set streaming cookie
 */
int utc_media_player_set_streaming_cookie_p(void)
{
    assert(!_is_broken);

    int ret = player_set_streaming_cookie(player, COOKIE_EXAMPLE, sizeof(COOKIE_EXAMPLE));
    assert_eq(ret, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_set_streaming_cookie_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set streaming cookie
 */
int utc_media_player_set_streaming_cookie_n(void)
{
    assert(!_is_broken);

    int ret = player_set_streaming_cookie(NULL, COOKIE_EXAMPLE, sizeof(COOKIE_EXAMPLE));
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

void _player_adaptive_variant_cb(int bandwidth, int width, int height, void *user_data)
{
    _is_pass = TRUE;
}


/**
 * @testcase        utc_media_player_foreach_adaptive_variant_p
 * @since_tizen     4.0
 * @description     Positive test case to retrieve adaptive variant info
 */
int utc_media_player_foreach_adaptive_variant_p(void)
{
	assert(!_is_broken);
	int ret = PLAYER_ERROR_NONE;

	ret = player_set_uri(player, g_media_adaptive_path);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = _player_prepare_with_connection_check(g_media_adaptive_path);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_foreach_adaptive_variant(player, (player_adaptive_variant_cb)_player_adaptive_variant_cb, player);
	assert_eq(ret, PLAYER_ERROR_NONE);
	assert(_is_pass);

	return 0;
}

/**
 * @testcase        utc_media_player_foreach_adaptive_variant_n
 * @since_tizen     4.0
 * @description     Negative test case to retrieve adaptive variant info
 */
int utc_media_player_foreach_adaptive_variant_n(void)
{
	assert(!_is_broken);
	int ret = PLAYER_ERROR_NONE;

	ret = player_set_uri(player, g_media_adaptive_path);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = _player_prepare_with_connection_check(g_media_adaptive_path);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_foreach_adaptive_variant(player, NULL, player);
	assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_media_player_set_max_adaptive_variant_limit_p
 * @since_tizen     4.0
 * @description     Positive test case to set max adaptive variant
 */
int utc_media_player_set_get_max_adaptive_variant_limit_p(void)
{
	assert(!_is_broken);

	int ret = PLAYER_ERROR_NONE;
	int bandwidth = 500000, width = 1920, height = 1080;
	int get_bandwidth = 0, get_width = 0, get_height = 0;

	ret = player_set_uri(player, g_media_adaptive_path);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = _player_prepare_with_connection_check(g_media_adaptive_path);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_set_max_adaptive_variant_limit(player, bandwidth, width, height);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_get_max_adaptive_variant_limit(player, &get_bandwidth, &get_width, &get_height);
	assert_eq(ret, PLAYER_ERROR_NONE);
	assert_eq(bandwidth, get_bandwidth);
	assert_eq(width, get_width);
	assert_eq(height, get_height);

	return 0;
}

/**
 * @testcase        utc_media_player_set_max_adaptive_variant_limit_n
 * @since_tizen     4.0
 * @description     Negative test case to set max adaptive variant
 */
int utc_media_player_set_max_adaptive_variant_limit_n(void)
{
    assert(!_is_broken);
    int bandwidth = 0, width = 0, height = 0;

    int ret = player_set_max_adaptive_variant_limit(NULL, bandwidth, width, height);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_media_player_get_max_adaptive_variant_limit_n
 * @since_tizen     4.0
 * @description     Negative test case to get max adaptive variant
 */
int utc_media_player_get_max_adaptive_variant_limit_n(void)
{
    assert(!_is_broken);

    int bandwidth = 0, width = 0, height = 0;

    int ret = player_get_max_adaptive_variant_limit(NULL, &bandwidth, &width, &height);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_media_player_set_get_streaming_buffering_time_p
 * @since_tizen     4.0
 * @description     Positive test case to set/get streaming buffering time
 */
int utc_media_player_set_get_streaming_buffering_time_p(void)
{
	assert(!_is_broken);
	int ret = PLAYER_ERROR_NONE;
	int btime = 50000, rbtime = 100000;
	int get_btime = 0, get_rbtime = 0;

	ret = player_set_uri(player, g_media_path);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_set_streaming_buffering_time(player, btime, rbtime);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = _player_prepare_with_connection_check(g_media_path);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_get_streaming_buffering_time(player, &get_btime, &get_rbtime);
	assert_eq(ret, PLAYER_ERROR_NONE);
	assert_eq(btime, get_btime);
	assert_eq(rbtime, get_rbtime);

	return 0;
}

/**
 * @testcase        utc_media_player_set_streaming_buffering_time_n
 * @since_tizen     4.0
 * @description     Negative test case to set streaming buffering time
 */
int utc_media_player_set_streaming_buffering_time_n(void)
{
    assert(!_is_broken);
    int btime = 0, rbtime = 0;

    int ret = player_set_streaming_buffering_time(NULL, btime, rbtime);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_media_player_get_streaming_buffering_time_n
 * @since_tizen     4.0
 * @description     Negative test case to get streaming buffering time
 */
int utc_media_player_get_streaming_buffering_time_n(void)
{
    assert(!_is_broken);

    int get_btime = 0, get_rbtime = 0;

    int ret = player_get_streaming_buffering_time(NULL, &get_btime, &get_rbtime);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

