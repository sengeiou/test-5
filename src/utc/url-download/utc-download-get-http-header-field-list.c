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

//& set: utc-download-get-http-header-field-list

static int id = -1;

/**
 * @testcase		utc_download_get_http_header_field_list_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_download_get_http_header_field_list_startup(void)
{
	int retcode = 0;

	g_bIsDownloadFeatureSupported = download_check_feature(DOWNLOAD_SUPPORTED_FEATURE_DOWNLOAD);
	retcode = download_create(&id);
	if (retcode != DOWNLOAD_ERROR_NONE)
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);

	retcode = download_add_http_header_field(id, "field1", "value1");
	if (retcode != DOWNLOAD_ERROR_NONE)
			fprintf(stderr, "Cleanup error at %s:%d\n", __FILE__, __LINE__);

	retcode = download_add_http_header_field(id, "field2", "value2");
	if (retcode != DOWNLOAD_ERROR_NONE)
			fprintf(stderr, "Cleanup error at %s:%d\n", __FILE__, __LINE__);


}

/**
 * @testcase		utc_download_get_http_header_field_list_cleanup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_download_get_http_header_field_list_cleanup(void)
{
	int retcode = download_destroy(id);
	if (retcode != DOWNLOAD_ERROR_NONE)
		fprintf(stderr, "Cleanup error at %s:%d\n", __FILE__, __LINE__);

	id = -1;
}

/**
 * @testcase		utc_download_get_http_header_field_list_p1
 * @since_tizen		2.3
 * @description		Positive test case of download_get_http_header_field_list()
 */
int utc_download_get_http_header_field_list_p1(void)
{
    int retcode = 0;
    char **fields = NULL;
    int length = 0;
    int i;

    retcode = download_get_http_header_field_list(id, &fields, &length);
	if (!g_bIsDownloadFeatureSupported) {
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);
		assert_gt(length, 0);
		assert(fields);

		for (i=0; i < length; i++)
			free(fields[i]);
		free(fields);
	}

    return 0;
}

/**
 * @testcase		utc_download_get_http_header_field_list_n1
 * @since_tizen		2.3
 * @description		Negative test case of download_get_http_header_field_list() - Invalid parameter(NULL pointer)
 */
int utc_download_get_http_header_field_list_n1(void)
{
    int retcode = 0;
    int length = 0;

    retcode = download_get_http_header_field_list(id, NULL, &length);
	if (!g_bIsDownloadFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
	    assert_eq(retcode, DOWNLOAD_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_download_get_http_header_field_list_n2
 * @since_tizen		2.3
 * @description		Negative test case of download_get_http_header_field_list() - Invalid parameter(NULL pointer)
 */
int utc_download_get_http_header_field_list_n2(void)
{
    int retcode = 0;
    char **fields = NULL;

    retcode = download_get_http_header_field_list(id, &fields, NULL);
	if (!g_bIsDownloadFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
		assert_eq(retcode, DOWNLOAD_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_download_get_http_header_field_list_n3
 * @since_tizen		2.3
 * @description		Negative test case of download_get_http_header_field_list() - Invalid parameter(ID)
 */
int utc_download_get_http_header_field_list_n3(void)
{
    int retcode = 0;
    char **fields = NULL;
    int length = 0;

    retcode = download_get_http_header_field_list(-1, &fields, &length);
	if (!g_bIsDownloadFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
	    assert_eq(retcode, DOWNLOAD_ERROR_INVALID_PARAMETER);

    return 0;
}
