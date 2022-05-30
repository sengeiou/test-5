//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
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
#include <limits.h>
#include <storage.h>

#define TEST_KEYWORD "test"

//& set: MediaBook

static book_meta_h g_book;
static char *g_val_str = NULL;
static int startup_ret = MEDIA_CONTENT_ERROR_NONE;

/**
 * @function		utc_media_book_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_book_startup(void)
{
	char *root_path = NULL;
	char epub_path[PATH_MAX + 1] = { 0, };
	char pdf_path[PATH_MAX + 1] = { 0, };
	media_info_h media = NULL;

	if (storage_get_root_directory(0, &root_path) == STORAGE_ERROR_NONE) {
		snprintf(epub_path, PATH_MAX, "%s/res/utc_test.epub", root_path);
		snprintf(pdf_path, PATH_MAX, "%s/res/utc_test.pdf", root_path);
		FREE_MEMORY(root_path);
	}

	startup_ret = media_content_connect();
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_content_connect failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_info_get_media_from_db_by_path(epub_path, &media);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		startup_ret = media_info_insert_to_db(epub_path, &media);
		if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
			FPRINTF("[Line : %d] media_info_insert_to_db failed.\\n", __LINE__);
			return;
		}

		startup_ret = media_content_scan_file(pdf_path);
		if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
			FPRINTF("[Line : %d] media_content_scan_file failed.\\n", __LINE__);
			return;
		}
	}

	startup_ret = media_info_get_book(media, &g_book);
	media_info_destroy(media);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_info_get_book failed.\\n", __LINE__);
		return;
	}
}

/**
 * @function		utc_media_book_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_book_cleanup(void)
{
	media_content_disconnect();

	if (g_book) {
		book_meta_destroy(g_book);
		g_book = NULL;
	}

	FREE_MEMORY(g_val_str);
}

/**
 * @testcase		utc_media_book_meta_destroy_n
 * @since_tizen		6.5
 * @description		Negative test case of book_meta_destroy()
 */
int utc_media_book_meta_destroy_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(book_meta_destroy(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_destroy_p
 * @since_tizen		6.5
 * @description		Positive test case of book_meta_destroy()
 */
int utc_media_book_meta_destroy_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(book_meta_destroy(g_book), MEDIA_CONTENT_ERROR_NONE);
	g_book = NULL;

	return 0;
}

/**
 * @testcase		utc_media_book_meta_clone_n
 * @since_tizen		6.5
 * @description		Negative test case of book_meta_clone()
 */
int utc_media_book_meta_clone_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);
	book_meta_h book = NULL;

	assert_eq(book_meta_clone(&book, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(book_meta_clone(NULL, g_book), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_clone_p
 * @since_tizen		6.5
 * @description		Positive test case of book_meta_clone()
 */
int utc_media_book_meta_clone_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);
	book_meta_h book = NULL;

	assert_eq(book_meta_clone(&book, g_book), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(book_meta_destroy(book), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_media_id_n
 * @since_tizen		6.5
 * @description		Negative test case of book_meta_get_media_id()
 */
int utc_media_book_meta_get_media_id_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(book_meta_get_media_id(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(book_meta_get_media_id(g_book, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_media_id_p
 * @since_tizen		6.5
 * @description		Positive test case of book_meta_get_media_id()
 */
int utc_media_book_meta_get_media_id_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(book_meta_get_media_id(g_book, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_subject_n
 * @since_tizen		6.5
 * @description		Negative test case of book_meta_get_subject()
 */
int utc_media_book_meta_get_subject_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(book_meta_get_subject(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(book_meta_get_subject(g_book, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_subject_p
 * @since_tizen		6.5
 * @description		Positive test case of book_meta_get_subject()
 */
int utc_media_book_meta_get_subject_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(book_meta_get_subject(g_book, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_author_n
 * @since_tizen		6.5
 * @description		Negative test case of book_meta_get_author()
 */
int utc_media_book_meta_get_author_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(book_meta_get_author(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(book_meta_get_author(g_book, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_author_p
 * @since_tizen		6.5
 * @description		Positive test case of book_meta_get_author()
 */
int utc_media_book_meta_get_author_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(book_meta_get_author(g_book, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_date_n
 * @since_tizen		6.5
 * @description		Negative test case of book_meta_get_date()
 */
int utc_media_book_meta_get_date_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(book_meta_get_date(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(book_meta_get_date(g_book, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_date_p
 * @since_tizen		6.5
 * @description		Positive test case of book_meta_get_date()
 */
int utc_media_book_meta_get_date_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(book_meta_get_date(g_book, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_publisher_n
 * @since_tizen		6.5
 * @description		Negative test case of book_meta_get_publisher()
 */
int utc_media_book_meta_get_publisher_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(book_meta_get_publisher(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(book_meta_get_publisher(g_book, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_publisher_p
 * @since_tizen		6.5
 * @description		Positive test case of book_meta_get_publisher()
 */
int utc_media_book_meta_get_publisher_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(book_meta_get_publisher(g_book, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_path_with_keyword_n
 * @since_tizen		6.5
 * @description		Negative test case of book_meta_get_path_with_keyword()
 */
int utc_media_book_meta_get_path_with_keyword_n(void)
{
	char **path_list = NULL;
	unsigned int len = 0;

	assert_eq(book_meta_get_path_with_keyword(NULL, &path_list, &len), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(book_meta_get_path_with_keyword(TEST_KEYWORD, NULL, &len), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(book_meta_get_path_with_keyword(TEST_KEYWORD, &path_list, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_path_with_keyword_p
 * @since_tizen		6.5
 * @description		Positive test case of book_meta_get_path_with_keyword()
 */
int utc_media_book_meta_get_path_with_keyword_p(void)
{
	char **path_list = NULL;
	unsigned int len = 0;

	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(book_meta_get_path_with_keyword(TEST_KEYWORD, &path_list, &len), MEDIA_CONTENT_ERROR_NONE);

	while (path_list && len > 0)
		free(path_list[--len]);

	free(path_list);

	return 0;
}
