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
#include <glib.h>
#include <glib-object.h>

//& set: utc-download-start

static GMainLoop* gloop = NULL;
static guint gTimeoutId = -1;

static int is_download_success = true;
static int is_download_failed = 0;
static int id = -1;
static bool is_error = false;

static gboolean download_timeout_callback(gpointer data)
{
	dlog_print(DLOG_ERROR, "NativeTCT", "Timeout has been reached. [%d] will be canceled.", id);
	download_cancel(id);
	g_main_loop_quit(gloop);
	return false;
}

static void state_n_cb(int download_id, download_state_e state, void *user_data)
{
    int retcode = 0;
    download_error_e err = DOWNLOAD_ERROR_NONE;
    if (state == DOWNLOAD_STATE_FAILED || state == DOWNLOAD_STATE_CANCELED) {
        is_download_failed = true;
        retcode = download_get_error(download_id, &err);
        if (retcode != DOWNLOAD_ERROR_NONE) {
            is_error = false;
        }
        g_main_loop_quit(gloop);
    } else {
        is_download_failed = false;
        g_main_loop_quit(gloop);
    }
}

static void state_p_cb (int download_id, download_state_e state, void *user_data)
{
    int retcode = 0;
    download_error_e err = DOWNLOAD_ERROR_NONE;
    if (state == DOWNLOAD_STATE_COMPLETED || state == DOWNLOAD_STATE_DOWNLOADING) {
        is_download_success = true;
        g_main_loop_quit(gloop);
    } else if (state == DOWNLOAD_STATE_CANCELED) {
		is_download_success = false;
		g_main_loop_quit(gloop);
	} else
        is_download_success = false;

    retcode = download_get_error(download_id, &err);
    if (retcode != DOWNLOAD_ERROR_NONE) {
        g_main_loop_quit(gloop);
        return;
    }

    if (err == DOWNLOAD_ERROR_INVALID_URL)
        fprintf(stderr,"invaild url err");
    else
        fprintf(stderr, "another error[%d]", err);
}

/**
 * @function		utc_download_start_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_download_start_startup(void)
{
	gloop = g_main_loop_new(NULL, 0);
	gTimeoutId = g_timeout_add(DOWNLOAD_TIMEOUT, download_timeout_callback, gloop);
    is_download_success = true;
    is_download_failed = false;

	g_bIsDownloadFeatureSupported = download_check_feature(DOWNLOAD_SUPPORTED_FEATURE_DOWNLOAD);
}

/**
 * @function		utc_download_start_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_download_start_cleanup(void)
{
    is_download_failed = false;
    is_download_success = false;
    g_source_remove(gTimeoutId);
    g_main_loop_quit(gloop);
    g_main_loop_unref(gloop);
    gloop = NULL;
}

/**
 * @testcase		utc_download_start_p1
 * @since_tizen		2.3
 * @description		Positive test case of download_start()
 */
int utc_download_start_p1(void)
{
    int retcode = 0;

	if (!g_bIsDownloadFeatureSupported) {
		retcode = download_start(id);
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	} else {
		retcode = download_create(&id);
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);

		retcode = download_set_url(id, TEST_URL);
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);

		is_error = false;
		retcode = download_set_state_changed_cb(id, (download_state_changed_cb) state_p_cb, NULL);
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);
		assert_eq(is_error, false);

		retcode = download_start(id);
		if (retcode == DOWNLOAD_ERROR_NONE)
			g_main_loop_run(gloop);
		else
			is_download_success = false;

		retcode = download_unset_state_changed_cb(id);
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);

		download_destroy(id);
		assert_eq(is_download_success, true);
	}

    return 0;

  /*fprintf(stderr,"BLOCK (same to TETware result)");
    return 1;*/
}

/**
 * @testcase		utc_download_start_n1
 * @since_tizen		2.3
 * @description		Negative test case of download_start()
 */
int utc_download_start_n1(void)
{
    int retcode = 0;

	if (!g_bIsDownloadFeatureSupported) {
		retcode = download_start(id);
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	} else {
		retcode = download_create(&id);
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);

		retcode = download_set_url(id, "abc.com");
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);

		is_error = false;
		retcode = download_set_state_changed_cb(id, (download_state_changed_cb) state_n_cb, NULL);
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);
		assert_eq(is_error, false);

		retcode = download_start(id);
		if (retcode == DOWNLOAD_ERROR_NONE)
			g_main_loop_run(gloop);
		retcode = download_unset_state_changed_cb(id);
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);
		download_destroy(id);
		assert_eq(is_download_failed, true);
	}

    return 0;

    /*fprintf(stderr,"BLOCK (same to TETware result)");
    return 1;*/
}
