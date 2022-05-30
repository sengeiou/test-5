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

//& set: utc-download-set-network-type

static int id = -1;

/** @function        utc_download_set_network_type_startup
 *  @description     Called before each test
 *  @parameter       NA
 *  @return          NA
 */
void utc_download_set_network_type_startup(void)
{
	int retcode = 0;

	g_bIsDownloadFeatureSupported = download_check_feature(DOWNLOAD_SUPPORTED_FEATURE_DOWNLOAD);
	g_bIsTelephonyFeatureSupported = download_check_feature(DOWNLOAD_SUPPORTED_FEATURE_TELEPHONY);

	retcode = download_create(&id);
	if (retcode != DOWNLOAD_ERROR_NONE)
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
}

/** @function        utc_download_set_network_type_cleanup
 *  @description     Called before each test
 *  @parameter       NA
 *  @return          NA
 */
void utc_download_set_network_type_cleanup(void)
{
	int retcode = download_destroy(id);
	if (retcode != DOWNLOAD_ERROR_NONE)
		fprintf(stderr, "Cleanup error at %s:%d\n", __FILE__, __LINE__);

	id = -1;
}


/**
 * @testcase		utc_download_set_network_type_p1
 * @since_tizen		2.3
 * @description		Positive test case of download_set_network_type()
 */
int utc_download_set_network_type_p1(void)
{
    int retcode = 0;

	download_network_type_e input = DOWNLOAD_NETWORK_DATA_NETWORK;
    download_network_type_e output;

	retcode = download_set_network_type(id, input);
	if (!g_bIsDownloadFeatureSupported || !g_bIsTelephonyFeatureSupported) {
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	} else{
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);
		retcode = download_get_network_type(id, &output);
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);
		assert_eq(output, input);
	}
    return 0;
}


/**
 * @testcase		utc_download_set_network_type_n1
 * @since_tizen		2.3
 * @description		Negative test case of download_set_network_type() - Invalid parameter(ID)
 */
int utc_download_set_network_type_n1(void)
{
    int retcode = 0;

    retcode = download_set_network_type(-1, DOWNLOAD_NETWORK_DATA_NETWORK);
	if (!g_bIsDownloadFeatureSupported || !g_bIsTelephonyFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
		assert_eq(retcode, DOWNLOAD_ERROR_INVALID_PARAMETER);

    return 0;
}
/**
 * @testcase		utc_download_set_network_type_n2
 * @since_tizen		2.3
 * @description		Negative test case of download_set_network_type() - Invalid parameter
 */
int utc_download_set_network_type_n2(void)
{
    int retcode = 0;

    retcode = download_set_network_type(id, 10);
	if (!g_bIsDownloadFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
		assert_eq(retcode, DOWNLOAD_ERROR_INVALID_PARAMETER);

    return 0;
}
