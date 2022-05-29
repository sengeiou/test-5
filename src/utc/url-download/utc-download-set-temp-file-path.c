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
#include "utc-download-common.h"
#include <download.h>
#include <string.h>
#include <glib.h>
#include <glib-object.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dlog.h>

#define CONFIG_VALUE_LEN_MAX      1024    //maximum length of value

//& set: utc-download-set-temp-file-path

static GMainLoop* gloop = NULL;
static guint gTimeoutId = -1;

static bool is_error = false;
static int id = -1;

static gboolean download_timeout_callback(gpointer data)
{
	dlog_print(DLOG_ERROR, "NativeTCT", "Timeout has been reached. [%d] will be canceled.", id);
	download_cancel(id);
	g_main_loop_quit(gloop);
	return false;
}

static void state_cb(int download_id, download_state_e state, void *user_data)
{
    int retcode = 0;
    download_error_e err = DOWNLOAD_ERROR_NONE;
    if (state >= DOWNLOAD_STATE_DOWNLOADING) {
        if (state == DOWNLOAD_STATE_FAILED) {
            retcode = download_get_error(download_id, &err);
            if (retcode != DOWNLOAD_ERROR_NONE) {
                is_error = true;
            }
        }
        g_main_loop_quit(gloop);
    }
}

/**
 * @function		utc_download_set_temp_path_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_download_set_temp_path_startup(void)
{
	int retcode = 0;
	gloop = g_main_loop_new(NULL, 0);
	gTimeoutId = g_timeout_add(DOWNLOAD_TIMEOUT, download_timeout_callback, gloop);

	g_bIsDownloadFeatureSupported = download_check_feature(DOWNLOAD_SUPPORTED_FEATURE_DOWNLOAD);

	retcode = download_create(&id);
	if (retcode != DOWNLOAD_ERROR_NONE)
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
}

/**
 * @function		utc_download_set_temp_path_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_download_set_temp_path_cleanup(void)
{
	int retcode = download_destroy(id);
	if (retcode != DOWNLOAD_ERROR_NONE)
		fprintf(stderr, "Cleanup error at %s:%d\n", __FILE__, __LINE__);

    g_source_remove(gTimeoutId);
    g_main_loop_unref(gloop);
    gloop = NULL;
	id = -1;
}

/**
 * @testcase		utc_download_set_temp_file_path_p1
 * @since_tizen		2.3
 * @description		Positive test case of download_set_temp_file_path()
 */
int utc_download_set_temp_file_path_p1(void)
{
    int retcode = 0;
    int set_result = 0;

	char *pszFilePath = NULL;
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

	dlog_print(DLOG_ERROR, "NativeTCT", "[%s][%d] utc_download_set_temp_file_path_p1", __FILE__, __LINE__);

	if ( true == GetValueForTCTSetting("DEVICE_PHYSICAL_STORAGE_30", pszValue, API_NAMESPACE ))

	{
		FPRINTF("[%s][%d] 'DEVICE_PHYSICAL_STORAGE_30' Values Received = %s\\n", __FILE__, __LINE__, pszValue);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s][%d] 'DEVICE_PHYSICAL_STORAGE_30' Values Received = %s", __FILE__, __LINE__, pszValue);
		int path_size = strlen(pszValue) + strlen("/Downloads") + 1;
		pszFilePath = (char*)calloc(path_size, sizeof(char));
		if( NULL == pszFilePath )
		{
			FPRINTF("[%s][%d] 'Memory allocation to pszFilePath failed\\n", __FILE__, __LINE__);
			//dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] GetValueForTCTSetting returned error", __FILE__, __LINE__);
			return 1;
		}
		snprintf(pszFilePath, path_size, "%s/Downloads", pszValue);
	}
	else
	{
		FPRINTF("[%s][%d] GetValueForTCTSetting returned error for 'DEVICE_PHYSICAL_STORAGE_30'\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s][%d] GetValueForTCTSetting returned error for 'DEVICE_PHYSICAL_STORAGE_30'", __FILE__, __LINE__);
		return 1;
	}

	if (!g_bIsDownloadFeatureSupported) {
		retcode = download_set_temp_file_path(id, pszFilePath);
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	} else {
		retcode = download_set_url(id, TEST_URL);
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);

		is_error = false;
		retcode = download_set_state_changed_cb(id, (download_state_changed_cb) state_cb, NULL);
		if (!g_bIsDownloadFeatureSupported)
			assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
		else
			assert_eq(retcode, DOWNLOAD_ERROR_NONE);

		retcode = download_start(id);
		if (retcode == DOWNLOAD_ERROR_NONE)
			g_main_loop_run(gloop);
		assert_eq(is_error, false);

		retcode = download_cancel(id);
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);

		retcode = download_set_temp_file_path(id, pszFilePath);
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);

		retcode = download_start(id);
		if (retcode == DOWNLOAD_ERROR_NONE)
			g_main_loop_run(gloop);
		assert_eq(is_error, false);

		download_destroy(id);
	}
    return 0;
}

/**
 * @testcase		utc_download_set_temp_file_path_n1
 * @since_tizen		2.3
 * @description		Negative test case of download_set_temp_file_path() - Invalid parameter(ID)
 */
int utc_download_set_temp_file_path_n1(void)
{
    int retcode = 0;

    retcode = download_set_temp_file_path(-1, "temp_file");
	if (!g_bIsDownloadFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
		assert_eq(retcode, DOWNLOAD_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_download_set_temp_file_path_n2
 * @since_tizen		2.3
 * @description		Negative test case of download_set_temp_file_path() - Invalid parameter(NULL pointer)
 */
int utc_download_set_temp_file_path_n2(void)
{
    int retcode = 0;

    retcode = download_set_temp_file_path(id, NULL);
	if (!g_bIsDownloadFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
		assert_eq(retcode, DOWNLOAD_ERROR_INVALID_PARAMETER);

    return 0;
}
