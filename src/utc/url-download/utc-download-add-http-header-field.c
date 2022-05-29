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

//& set: utc-download-add-http-header-field

static int id = -1;

/**
 * @function		utc_download_add_http_header_field_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_download_add_http_header_field_startup(void)
{
	int retcode = 0;

	g_bIsDownloadFeatureSupported = download_check_feature(DOWNLOAD_SUPPORTED_FEATURE_DOWNLOAD);
	retcode = download_create(&id);
	if (retcode != DOWNLOAD_ERROR_NONE)
			fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
}

/**
 * @function		utc_download_add_http_header_field_cleanup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_download_add_http_header_field_cleanup(void)
{
	int retcode = download_destroy(id);
	if (retcode != DOWNLOAD_ERROR_NONE)
			fprintf(stderr, "Cleanup error at %s:%d\n", __FILE__, __LINE__);
}

/**
 * @testcase		utc_download_add_http_header_field_p1
 * @since_tizen		2.3
 * @description		Positive test case of download_add_http_header_field()
 */
int utc_download_add_http_header_field_p1(void)
{
    int retcode = 0;

    retcode = download_add_http_header_field(id, "field", "value");
	if (!g_bIsDownloadFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_download_add_http_header_field_n1
 * @since_tizen		2.3
 * @description		Negative test case of download_add_http_header_field() - Invalid parameter(ID)
 */
int utc_download_add_http_header_field_n1(void)
{
    int retcode = 0;

    retcode = download_add_http_header_field(-1, "field", "value");
	if (!g_bIsDownloadFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
    	assert_eq(retcode, DOWNLOAD_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_download_add_http_header_field_n2
 * @since_tizen		2.3
 * @description		Negative test case of download_add_http_header_field() - NULL field
 */
int utc_download_add_http_header_field_n2(void)
{
    int retcode = 0;

    retcode = download_add_http_header_field(id, NULL, "value");
	if (!g_bIsDownloadFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
    	assert_eq(retcode, DOWNLOAD_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_download_add_http_header_field_n3
 * @since_tizen		2.3
 * @description		Negative test case of download_add_http_header_field() - NULL value
 */
int utc_download_add_http_header_field_n3(void)
{
    int retcode = 0;

    retcode = download_add_http_header_field(id, "field", NULL);
	if (!g_bIsDownloadFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
    	assert_eq(retcode, DOWNLOAD_ERROR_INVALID_PARAMETER);

    return 0;
}