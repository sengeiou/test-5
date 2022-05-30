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
#include <system_info.h>

//& set: utc-download-get-network-type

static download_network_type_e input = DOWNLOAD_NETWORK_DATA_NETWORK;
static int id = -1;

void utc_download_get_network_type_startup(void)
{
	g_bIsDownloadFeatureSupported = download_check_feature(DOWNLOAD_SUPPORTED_FEATURE_DOWNLOAD);
	g_bIsTelephonyFeatureSupported = download_check_feature(DOWNLOAD_SUPPORTED_FEATURE_TELEPHONY);

	download_create(&id);
	download_set_network_type(id, input);
}

void utc_download_get_network_type_cleanup(void)
{
	download_destroy(id);
}
/**
 * @testcase		utc_download_get_network_type_p1
 * @since_tizen		2.3
 * @description		Positive test case of download_get_network_type()
 */
int utc_download_get_network_type_p1(void)
{
    int retcode = 0;
    download_network_type_e output;

	retcode = download_get_network_type(id, &output);
    if (!g_bIsDownloadFeatureSupported) {
        assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
    } else{
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);
		if (g_bIsTelephonyFeatureSupported)
			assert_eq(output, input);
    }
    return 0;
}

/**
 * @testcase		utc_download_get_network_type_n1
 * @since_tizen		2.3
 * @description		Negative test case of download_get_network_type() - Invalid parameter(ID)
 */
int utc_download_get_network_type_n1(void)
{
    int retcode = 0;
    download_network_type_e type;

    retcode = download_get_network_type(-1, &type);
    if (!g_bIsDownloadFeatureSupported)
        assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
    else
	    assert_eq(retcode, DOWNLOAD_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_download_get_network_type_n2
 * @since_tizen		2.3
 * @description		Negative test case of download_get_network_type() - Invalid parameter(NULL pointer)
 */
int utc_download_get_network_type_n2(void)
{
    int retcode = 0;

    retcode = download_get_network_type(id, NULL);
    if (!g_bIsDownloadFeatureSupported)
        assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
    else
	    assert_eq(retcode, DOWNLOAD_ERROR_INVALID_PARAMETER);

    return 0;
}
