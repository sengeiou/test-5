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

//& set: utc-download-get-url

#define INPUT_URL "www.tizen.org"

static int id = -1;

void utc_download_get_url_startup(void)
{
	int retcode = 0;

	g_bIsDownloadFeatureSupported = download_check_feature(DOWNLOAD_SUPPORTED_FEATURE_DOWNLOAD);

    retcode = download_create(&id);
	if (retcode != DOWNLOAD_ERROR_NONE)
			fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);

    retcode = download_set_url(id, INPUT_URL);
	if (retcode != DOWNLOAD_ERROR_NONE)
			fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
}

void utc_download_get_url_cleanup(void)
{
	int retcode = download_destroy(id);
	if (retcode != DOWNLOAD_ERROR_NONE)
			fprintf(stderr, "Cleanup error at %s:%d\n", __FILE__, __LINE__);

	id = -1;
}

/**
 * @testcase		utc_download_get_url_p1
 * @since_tizen		2.3
 * @description		Positive test case of download_get_url()
 */
int utc_download_get_url_p1(void)
{
    int retcode = 0;
    char *output = NULL;

    retcode = download_get_url(id, &output);
	if (!g_bIsDownloadFeatureSupported) {
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);
		assert(output);
		assert(!strcmp(INPUT_URL, output));
		free(output);
	}

    return 0;
}

/**
 * @testcase		utc_download_get_url_n1
 * @since_tizen		2.3
 * @description		Negative test case of download_get_url() - Invalid parameter(ID)
 */
int utc_download_get_url_n1(void)
{
    int retcode = 0;
    char *output = NULL;

    retcode = download_get_url(-1, &output);
	if (!g_bIsDownloadFeatureSupported)
			assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
	    assert_eq(retcode, DOWNLOAD_ERROR_INVALID_PARAMETER);
    
	return 0;
}

/**
 * @testcase		utc_download_get_url_n2
 * @since_tizen		2.3
 * @description		Negative test case of download_get_url() - Invalid parameter(NULL pointer)
 */
int utc_download_get_url_n2(void)
{
    int retcode = 0;

    retcode = download_get_url(id, NULL);
	if (!g_bIsDownloadFeatureSupported)
			assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
	    assert_eq(retcode, DOWNLOAD_ERROR_INVALID_PARAMETER);

    return 0;
}
