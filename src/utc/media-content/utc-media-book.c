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

//& set: MediaBook

static book_meta_h g_book;
static book_meta_h g_book_dst;
static filter_h g_filter;
static char *g_media_id = NULL;

static media_content_error_e startup_ret = MEDIA_CONTENT_ERROR_NONE;

static bool media_item_cb(media_info_h media, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_get_media_id(media, &g_media_id);
	if ((ret != MEDIA_CONTENT_ERROR_NONE) || (g_media_id == NULL)) {
		fprintf(stderr, "CB error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "media_info_get_media_id failed (code: %d)\n", ret);
		return false;
	}

	ret = media_info_get_book(media, &g_book);
	if ((ret != MEDIA_CONTENT_ERROR_NONE) || (g_book == NULL)) {
		fprintf(stderr, "CB error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "media_info_get_book failed (code: %d)\n", ret);
		return false;
	}

	return true;
}

/**
 * @function		utc_media_book_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_book_startup(void)
{
	/* start of TC */
	g_filter = NULL;
	g_book = NULL;

	media_content_error_e ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_content_connect();
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_content_connect failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	const char *condition = "MEDIA_TYPE=5 AND MEDIA_STORAGE_TYPE=0";	//Book

	media_filter_create(&g_filter);
	media_filter_set_condition(g_filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT);
	media_filter_set_order(g_filter, MEDIA_CONTENT_ORDER_ASC, MEDIA_TITLE, MEDIA_CONTENT_COLLATE_DEFAULT);
	if (g_filter == NULL) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "filter is NULL");
		startup_ret = ret;
		return;
	}

	ret = media_info_foreach_media_from_db(g_filter, media_item_cb, NULL);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_info_foreach_media_from_db failed (code: %d)\n", ret);
		startup_ret = ret;
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
	/* end of TC */
	if (g_media_id != NULL) {
		free(g_media_id);
		g_media_id = NULL;
	}

	if (g_book != NULL) {
		book_meta_destroy(g_book);
		g_book = NULL;
	}

	if (g_book_dst != NULL) {
		book_meta_destroy(g_book_dst);
		g_book_dst = NULL;
	}

	if (g_filter) {
		media_filter_destroy(g_filter);
		g_filter = NULL;
	}

	media_content_disconnect();
}

/**
 * @testcase		utc_media_book_meta_destroy_n
 * @since_tizen		6.5
 * @description		Negative test case of book_meta_destroy()
 */
int utc_media_book_meta_destroy_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = book_meta_destroy(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_destroy_p
 * @since_tizen		6.5
 * @description		Positive test case of book_meta_destroy()
 */
int utc_media_book_meta_destroy_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = book_meta_clone(&g_book_dst, g_book);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = book_meta_destroy(g_book_dst);
	g_book_dst = NULL;
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_clone_n
 * @since_tizen		6.5
 * @description		Negative test case of book_meta_clone()
 */
int utc_media_book_meta_clone_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = book_meta_clone(&g_book_dst, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_clone_p
 * @since_tizen		6.5
 * @description		Positive test case of book_meta_clone()
 */
int utc_media_book_meta_clone_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = book_meta_clone(&g_book_dst, g_book);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_media_id_n
 * @since_tizen		6.5
 * @description		Negative test case of book_meta_get_media_id()
 */
int utc_media_book_meta_get_media_id_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *media_id = NULL;

	ret = book_meta_get_media_id(NULL, &media_id);

	if (media_id)
		free(media_id);

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_media_id_p
 * @since_tizen		6.5
 * @description		Positive test case of book_meta_get_media_id()
 */
int utc_media_book_meta_get_media_id_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *media_id = NULL;

	ret = book_meta_get_media_id(g_book, &media_id);

	if (media_id)
		free(media_id);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_subject_n
 * @since_tizen		6.5
 * @description		Negative test case of book_meta_get_subject()
 */
int utc_media_book_meta_get_subject_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *subject = NULL;

	ret = book_meta_get_subject(NULL, &subject);

	if (subject)
		free(subject);

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_subject_p
 * @since_tizen		6.5
 * @description		Positive test case of book_meta_get_subject()
 */
int utc_media_book_meta_get_subject_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *subject = NULL;

	ret = book_meta_get_subject(g_book, &subject);

	if (subject)
		free(subject);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_author_n
 * @since_tizen		6.5
 * @description		Negative test case of book_meta_get_author()
 */
int utc_media_book_meta_get_author_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *author = NULL;

	ret = book_meta_get_author(NULL, &author);

	if (author)
		free(author);

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_author_p
 * @since_tizen		6.5
 * @description		Positive test case of book_meta_get_author()
 */
int utc_media_book_meta_get_author_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *author = NULL;

	ret = book_meta_get_author(g_book, &author);

	if (author)
		free(author);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_date_n
 * @since_tizen		6.5
 * @description		Negative test case of book_meta_get_date()
 */
int utc_media_book_meta_get_date_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *date = NULL;

	ret = book_meta_get_date(NULL, &date);

	if (date)
		free(date);

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_date_p
 * @since_tizen		6.5
 * @description		Positive test case of book_meta_get_date()
 */
int utc_media_book_meta_get_date_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *date = NULL;

	ret = book_meta_get_date(g_book, &date);

	if (date)
		free(date);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_publisher_n
 * @since_tizen		6.5
 * @description		Negative test case of book_meta_get_publisher()
 */
int utc_media_book_meta_get_publisher_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *publisher = NULL;

	ret = book_meta_get_publisher(NULL, &publisher);

	if (publisher)
		free(publisher);

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_publisher_p
 * @since_tizen		6.5
 * @description		Positive test case of book_meta_get_publisher()
 */
int utc_media_book_meta_get_publisher_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *publisher = NULL;

	ret = book_meta_get_publisher(g_book, &publisher);

	if (publisher)
		free(publisher);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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
	const char *keyword = "test";

	assert_eq(book_meta_get_path_with_keyword(NULL, &path_list, &len), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(book_meta_get_path_with_keyword(keyword, NULL, &len), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(book_meta_get_path_with_keyword(keyword, &path_list, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_book_meta_get_path_with_keyword_p
 * @since_tizen		6.5
 * @description		Positive test case of book_meta_get_path_with_keyword()
 */
int utc_media_book_meta_get_path_with_keyword_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char **path_list = NULL;
	unsigned int len = 0;
	const char *keyword = "test";

	ret = book_meta_get_path_with_keyword(keyword, &path_list, &len);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	while (path_list && len > 0)
		free(path_list[--len]);

	free(path_list);

	return 0;
}
