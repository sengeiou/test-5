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
#include <app_control.h>

//& set: utc-download-set-notification-app-control

#define APPCONTROL_KEY "key"
#define APPCONTROL_DATA "ongoing"

static app_control_h h = NULL;
static int id = -1;

void utc_download_set_notification_app_control_startup(void)
{
	int retcode = 0;

	g_bIsDownloadFeatureSupported = download_check_feature(DOWNLOAD_SUPPORTED_FEATURE_DOWNLOAD);

	retcode = app_control_create(&h);
	if (retcode != APP_CONTROL_ERROR_NONE)
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);

	retcode = app_control_add_extra_data(h, APPCONTROL_KEY, APPCONTROL_DATA);
	if (retcode != APP_CONTROL_ERROR_NONE)
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);

    retcode = download_create(&id);
	if (retcode != DOWNLOAD_ERROR_NONE)
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
}

void utc_download_set_notification_app_control_cleanup(void)
{
	int retcode = download_destroy(id);
	if (retcode != DOWNLOAD_ERROR_NONE)
		fprintf(stderr, "Cleanup error at %s:%d\n", __FILE__, __LINE__);

	retcode = app_control_destroy(h);
	if (retcode != APP_CONTROL_ERROR_NONE)
		fprintf(stderr, "Cleanup error at %s:%d\n", __FILE__, __LINE__);

	h = NULL;
	id = -1;
}

/**
 * @testcase		utc_download_set_notification_app_control_p1
 * @since_tizen		2.3
 * @description		Positive test case of download_set_notification_app_control()
 */
int utc_download_set_notification_app_control_p1(void)
{
    int retcode = 0;
	char *output = NULL;
    app_control_h h_db = NULL;

	if (!g_bIsDownloadFeatureSupported) {
		retcode = download_set_notification_app_control(id,
				DOWNLOAD_NOTIFICATION_APP_CONTROL_TYPE_ONGOING, h);
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	} else {
		retcode = download_set_notification_app_control(id,
				DOWNLOAD_NOTIFICATION_APP_CONTROL_TYPE_ONGOING, h);
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);

		retcode = download_get_notification_app_control(id,
				DOWNLOAD_NOTIFICATION_APP_CONTROL_TYPE_ONGOING, &h_db);
		assert_eq(retcode, DOWNLOAD_ERROR_NONE);
		assert(h_db);
		retcode = app_control_get_extra_data(h_db, APPCONTROL_KEY, &output);
		assert_eq(retcode, APP_CONTROL_ERROR_NONE);
		assert(output);
		assert_eq(strcmp(APPCONTROL_DATA, output), 0);
	}

    return 0;
}

/**
 * @testcase		utc_download_set_notification_app_control_n1
 * @since_tizen		2.3
 * @description		Negative test case of download_set_notification_app_control() - Invalid parameter(ID)
 */
int utc_download_set_notification_app_control_n1(void)
{
    int retcode = 0;

    retcode = download_set_notification_app_control(-1,
            DOWNLOAD_NOTIFICATION_APP_CONTROL_TYPE_ONGOING, h);
	if (!g_bIsDownloadFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
		assert_eq(retcode, DOWNLOAD_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_download_set_notification_app_control_n2
 * @since_tizen		2.3
 * @description		Negative test case of download_set_notification_app_control() - Invalid parameter(NULL pointer)
 */
int utc_download_set_notification_app_control_n2(void)
{
    int retcode = 0;

    retcode = download_set_notification_app_control(id,
            DOWNLOAD_NOTIFICATION_APP_CONTROL_TYPE_ONGOING, NULL);
	if (!g_bIsDownloadFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
		assert_eq(retcode, DOWNLOAD_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_download_set_notification_app_control_n3
 * @since_tizen		2.3
 * @description		Negative test case of download_set_notification_app_control() - Invalid parameter(state value)
 */
int utc_download_set_notification_app_control_n3(void)
{
    int retcode = 0;

    retcode = download_set_notification_app_control(id, 4, h);
	if (!g_bIsDownloadFeatureSupported)
		assert_eq(retcode, DOWNLOAD_ERROR_NOT_SUPPORTED);
	else
		assert_eq(retcode, DOWNLOAD_ERROR_INVALID_PARAMETER);

    return 0;
}
