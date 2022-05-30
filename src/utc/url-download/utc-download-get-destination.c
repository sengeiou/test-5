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

//& set: utc-download-get-destination
#define CONFIG_VALUE_LEN_MAX      1024

static char *input = NULL;
static int id = -1;

/* @function        utc_download_get_destination_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_download_get_destination_startup(void)
{
	int retcode = 0;
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

	if (true == GetValueForTCTSetting("DEVICE_PHYSICAL_STORAGE_30", pszValue, API_NAMESPACE)) {
		FPRINTF("[%s][%d] 'DEVICE_PHYSICAL_STORAGE_30' Values Received = %s\\n",
				__FILE__, __LINE__, pszValue);
		int path_size = strlen(pszValue) + strlen("/Downloads") + 1;
		input = (char*)calloc(path_size, sizeof(char));
		if(NULL == input) {
			FPRINTF("[%s][%d] 'Memory allocation to input failed\\n", __FILE__, __LINE__);
			return 1;
		}
		snprintf(input, path_size, "%s/Downloads", pszValue);
	} else {
		FPRINTF("[%s][%d] GetValueForTCTSetting returned error for 'DEVICE_PHYSICAL_STORAGE_30'\\n",
				__FILE__, __LINE__);
		return 1;
	}

    if(input == NULL) {
        fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
    }

	g_bIsDownloadFeatureSupported = download_check_feature(DOWNLOAD_SUPPORTED_FEATURE_DOWNLOAD);
	retcode = download_create(&id);
	if (retcode != DOWNLOAD_ERROR_NONE)
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);

	retcode = download_set_destination(id, input);
	if (retcode != DOWNLOAD_ERROR_NONE)
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
}

/* @function        utc_download_get_destination_cleanpu
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_download_get_destination_cleanup(void)
{
	int retcode = download_destroy(id);
	if (retcode != DOWNLOAD_ERROR_NONE)
		fprintf(stderr, "Cleanup error at %s:%d\n", __FILE__, __LINE__);

	if (input)
		free(input);

	id = -1;
}

/**
 * @testcase		utc_download_get_destination_p1
 * @since_tizen		2.3
 * @description		Positive test case of download_get_destination()
 */
int utc_download_get_destination_p1(void)
{
    int retcode = 0;
    char *output = NULL;

	retcode = download_get_destination(id, &output);
	if (!g_bIsDownloadFeatureSupported) {
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);
		if(input != NULL) {
			assert(!strcmp(input, output));
		}
	}

    return 0;
}

/**
 * @testcase		utc_download_get_destination_n1
 * @since_tizen		2.3
 * @description		Negative test case of download_get_destination() - Invalid parameter(ID)
 */
int utc_download_get_destination_n1(void)
{
    int retcode = 0;
    char *output = NULL;

    retcode = download_get_destination(-1, &output);
	if (!g_bIsDownloadFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
	    assert_eq(retcode, DOWNLOAD_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_download_get_destination_n2
 * @since_tizen		2.3
 * @description		Negative test case of download_get_destination() - Invalid parameter(NULL pointer)
 */
int utc_download_get_destination_n2(void)
{
    int retcode = 0;

    retcode = download_get_destination(id, NULL);
	if (!g_bIsDownloadFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
	    assert_eq(retcode, DOWNLOAD_ERROR_INVALID_PARAMETER);

    return 0;
}
