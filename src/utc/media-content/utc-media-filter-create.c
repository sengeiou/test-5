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

//& set: MediaFilterCreate

static filter_h g_filter = NULL;

/**
 * @function		utc_media_filter_create_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_filter_create_cleanup(void)
{
	if (g_filter) {
		media_filter_destroy(g_filter);
		g_filter = NULL;
	}
}

/**
 * @testcase		utc_media_filter_create_n
 * @since_tizen		2.3
 * @description		Negative test case of media_filter_create()
 */
int utc_media_filter_create_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_create(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_create_p
 * @since_tizen		2.3
 * @description		Positive test case of media_filter_create()
 */
int utc_media_filter_create_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_create(&g_filter);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}
