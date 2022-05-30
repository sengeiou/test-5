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

//& set: utc-download-unset-progress-cb

static int id = -1;
static bool bIsUnset = false;

static void on_url_download_progess(int id, unsigned long long received, void *user_data)
{

}

void utc_download_unset_progress_cb_startup(void)
{
	int retcode = 0;

	bIsUnset = false;
	g_bIsDownloadFeatureSupported = download_check_feature(DOWNLOAD_SUPPORTED_FEATURE_DOWNLOAD);
	retcode = download_create(&id);
	if (retcode != DOWNLOAD_ERROR_NONE)
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);

	retcode = download_set_progress_cb(id, on_url_download_progess, NULL);
	if (retcode != DOWNLOAD_ERROR_NONE)
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
}

void utc_download_unset_progress_cb_cleanup(void)
{
	int retcode = 0;

	if (!bIsUnset) {
		retcode = download_unset_progress_cb(id);
		if (retcode != DOWNLOAD_ERROR_NONE)
			fprintf(stderr, "Cleanup error at %s:%d\n", __FILE__, __LINE__);
	}

	retcode = download_destroy(id);
	if (retcode != DOWNLOAD_ERROR_NONE)
		fprintf(stderr, "Cleanup error at %s:%d\n", __FILE__, __LINE__);

	id = -1;
}

/**
 * @testcase		utc_download_unset_progress_cb_p1
 * @since_tizen		2.3
 * @description		Positive test case of download_unset_progress_cb()
 */
int utc_download_unset_progress_cb_p1(void)
{
    int retcode = 0;

    retcode = download_unset_progress_cb(id);
	if (!g_bIsDownloadFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);

	bIsUnset = true;

    return 0;
}

/**
 * @testcase		utc_download_unset_progress_cb_n1
 * @since_tizen		2.3
 * @description		Negative test case of download_unset_progress_cb() - Invalid parameter(ID)
 */
int utc_download_unset_progress_cb_n1(void)
{
    int retcode = 0;

    retcode = download_unset_progress_cb(-1);
	if (!g_bIsDownloadFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
    	assert_eq(retcode, DOWNLOAD_ERROR_ID_NOT_FOUND);

    return 0;
}
