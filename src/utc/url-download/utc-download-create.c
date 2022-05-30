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

//& set: utc-download-create


/**
 * @testcase		utc_download_create_startup
 * @description		Called before each test
 */
void utc_download_create_startup(void)
{
	g_bIsDownloadFeatureSupported = download_check_feature(DOWNLOAD_SUPPORTED_FEATURE_DOWNLOAD);
}

/**
 * @testcase		utc_download_create_p1
 * @since_tizen		2.3
 * @description		Positive test case of download_create()
 */
int utc_download_create_p1(void)
{
    int retcode = 0;
    int id = 0;

    retcode = download_create(&id);
	if (!g_bIsDownloadFeatureSupported) {
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	} else {
	    assert_eq(retcode, DOWNLOAD_ERROR_NONE);
	    download_destroy(id);
	}

    return 0;
}

/**
 * @testcase		utc_download_create_n1
 * @since_tizen		2.3
 * @description		Negative test case of download_create() - Invalid parameter(ID)
 */
int utc_download_create_n1(void)
{
    int retcode = 0;

    retcode = download_create(NULL);
	if (!g_bIsDownloadFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
	    assert_neq(retcode, DOWNLOAD_ERROR_NONE);

    return 0;
}
