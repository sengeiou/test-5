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
#include <media_content.h>
#include <tct_common.h>

//& set: MediaFilterDestroy

static filter_h g_filter = NULL;

static media_content_error_e startup_ret = MEDIA_CONTENT_ERROR_NONE;

/**
 * @function		utc_media_filter_destroy_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_filter_destroy_startup(void)
{
	media_content_error_e ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_create(&g_filter);

	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_filter_create failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}
}

/**
 * @function		utc_media_filter_destroy_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_filter_destroy_cleanup(void)
{
	if (g_filter) {
		media_filter_destroy(g_filter);
		g_filter = NULL;
	}
}

/**
 * @testcase		utc_media_filter_destroy_n
 * @since_tizen		2.3
 * @description		Negative test case of media_filter_destroy()
 */
int utc_media_filter_destroy_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_destroy(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_destroy_p
 * @since_tizen		2.3
 * @description		Positive test case of media_filter_destroy()
 */
int utc_media_filter_destroy_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_destroy(g_filter);
	g_filter = NULL;
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}
