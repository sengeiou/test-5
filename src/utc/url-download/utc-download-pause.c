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
#include <unistd.h>

//& set: utc-download-pause

static GMainLoop* gloop = NULL;
static guint gTimeoutId = -1;

static int id = -1;
static int is_pause_success = false;
static int is_started = false;
static bool is_error = false;
static bool is_changed = false;

static gboolean download_timeout_callback(gpointer data)
{
	dlog_print(DLOG_ERROR, "NativeTCT", "Timeout has been reached. [%d] will be canceled.", id);
	download_cancel(id);
	g_main_loop_quit(gloop);
	return false;
}

static void state_cb(int download_id, download_state_e state, void *user_data)
{
	is_changed = true;

	if (state == DOWNLOAD_STATE_COMPLETED) {
		g_main_loop_quit(gloop);
	} else if (state == DOWNLOAD_STATE_PAUSED) {
		is_pause_success = true;
		g_main_loop_quit(gloop);
	} else if (is_started == false && state == DOWNLOAD_STATE_DOWNLOADING) {
		is_started = true;
		g_main_loop_quit(gloop);
	} else if (state >= DOWNLOAD_STATE_FAILED) {
		is_error = true;
		g_main_loop_quit(gloop);
	}
}

/**
 * @function		utc_download_pause_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_download_pause_startup(void)
{
    gloop = g_main_loop_new(NULL, 0);
    gTimeoutId = g_timeout_add(DOWNLOAD_TIMEOUT, download_timeout_callback, gloop);

	g_bIsDownloadFeatureSupported = download_check_feature(DOWNLOAD_SUPPORTED_FEATURE_DOWNLOAD);
	is_pause_success = false;
}

/**
 * @function		utc_download_pause_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_download_pause_cleanup(void)
{
	is_pause_success = true;
	g_source_remove(gTimeoutId);
    g_main_loop_unref(gloop);
    gloop = NULL;
}

/**
 * @testcase		utc_download_pause_p1
 * @since_tizen		2.3
 * @description		Positive test case of download_pause()
 *
 */
int utc_download_pause_p1(void)
{
    int retcode = 0;

	if (!g_bIsDownloadFeatureSupported) {
		retcode = download_pause(id);
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	} else {
		retcode = download_create(&id);
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);

		retcode = download_set_url(id, TEST_URL);
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);

		is_error = false;
		retcode = download_set_state_changed_cb(id, (download_state_changed_cb)state_cb, NULL);
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);

		retcode = download_start(id);
		if (retcode == DOWNLOAD_ERROR_NONE)
			g_main_loop_run(gloop);
		else
			is_started = false;

		assert_eq(is_started, true);
		assert_eq(is_error, false);

		is_changed = false;

		if (is_started) {
			retcode = download_pause(id);
			if (retcode == DOWNLOAD_ERROR_NONE) {
				if (!is_changed && !is_pause_success)
					g_main_loop_run(gloop);
			} else {
				is_pause_success = false;
			}
		}

		assert_eq(is_error, false);
		download_unset_state_changed_cb(id);
		download_destroy(id);

		assert_eq(is_pause_success, true);
	}
	return 0;
}

/**
 * @testcase		utc_download_pause_n1
 * @since_tizen		2.3
 * @description		Negative test case of download_pause() - Invalid parameter(ID)
 */
int utc_download_pause_n1(void)
{
    int retcode = 0;

    retcode = download_pause(-1);
	if (!g_bIsDownloadFeatureSupported)
			assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
		assert_neq(retcode, DOWNLOAD_ERROR_NONE);

    return 0;
}
