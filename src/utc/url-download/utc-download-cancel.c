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

//& set: utc-download-cancel

static GMainLoop* gloop = NULL;
static guint gTimeoutId = -1;

static int id = -1;
static int is_started = false;
static bool is_error = false;
static bool is_canceled = false;

static gboolean download_timeout_callback(gpointer data)
{
	download_cancel(id);
	return false;
}

static void state_cb(int download_id, download_state_e state, void *user_data)
{
    if (state == DOWNLOAD_STATE_COMPLETED) {
        g_main_loop_quit(gloop);
    } else if (state == DOWNLOAD_STATE_DOWNLOADING) {
        is_started = true;
        g_main_loop_quit(gloop);
    } else if (state == DOWNLOAD_STATE_FAILED) {
        is_error = true;
        g_main_loop_quit(gloop);
    } else if (state == DOWNLOAD_STATE_CANCELED) {
		is_canceled = true;
		g_main_loop_quit(gloop);
	}
}

/**
 * @function		utc_download_cancel_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_download_cancel_startup(void)
{
	gloop = g_main_loop_new(NULL, 0);
	gTimeoutId = g_timeout_add(DOWNLOAD_TIMEOUT, download_timeout_callback, gloop);

	g_bIsDownloadFeatureSupported = download_check_feature(DOWNLOAD_SUPPORTED_FEATURE_DOWNLOAD);
}

/**
 * @function		utc_download_cancel_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_download_cancel_cleanup(void)
{
	g_source_remove(gTimeoutId);
    g_main_loop_unref(gloop);
    gloop = NULL;
}

/**
 * @testcase		utc_download_cancel_p1
 * @since_tizen		2.3
 * @description		Positive test case of download_cancel()
 */
int utc_download_cancel_p1(void)
{
    int retcode = 0;
	download_state_e state;

	if (g_bIsDownloadFeatureSupported) {
		retcode = download_create(&id);
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);

		retcode = download_set_url(id, TEST_URL);
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);

		is_error = false;
		retcode = download_set_state_changed_cb(id, (download_state_changed_cb) state_cb, NULL);
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);

		retcode = download_start(id);
		if (retcode == DOWNLOAD_ERROR_NONE){
			g_main_loop_run(gloop);
		} else {
			is_started = false;
		}
		assert_eq(is_error, false);

		if (is_started && !is_canceled) {
			retcode = download_cancel(id);
			assert_eq(retcode, DOWNLOAD_ERROR_NONE);
		} else {
			assert_eq((is_started | is_canceled), true);
		}
		download_unset_state_changed_cb(id);
		sleep(1);
		download_get_state(id, &state);
		download_destroy(id);

		assert_eq(state, DOWNLOAD_STATE_CANCELED);
	} else {
		retcode = download_cancel(-1);
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	}
    return 0;
}

/**
 * @testcase		utc_download_cancel_n1
 * @since_tizen		2.3
 * @description		Negative test case of () - Invalid parameter(ID)
 */
int utc_download_cancel_n1(void)
{
    int retcode = 0;

    retcode = download_cancel(-1);
	if (!g_bIsDownloadFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
    	assert_neq(retcode, DOWNLOAD_ERROR_NONE);

    return 0;
}
