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

#include "ITs-media-content-common.h"



static bool MediaItemCb(media_info_h hMedia, void *user_data)
{
#if DEBUG
        FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "MediaItemCb");
#endif
        FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "MediaItemCb");
        int nRet;

        nRet = media_info_get_media_id(hMedia, &pszMediaId);
        if ((nRet != MEDIA_CONTENT_ERROR_NONE) || (pszMediaId == NULL)) {
                FPRINTF("[Line : %d][%s] %s Callback error\\n", __LINE__, API_NAMESPACE, "MediaItemCb");
                FPRINTF("[Line : %d][%s] %s media_info_get_media_id failed \\n", __LINE__, API_NAMESPACE, "MediaItemCb");
                return false;
        }

        nRet = media_info_get_book(hMedia, &g_hBook);
        if ((nRet != MEDIA_CONTENT_ERROR_NONE) || (g_hBook == NULL)) {
                FPRINTF("[Line : %d][%s] %s Callback error\\n", __LINE__, API_NAMESPACE, "MediaItemCb");
                FPRINTF("[Line : %d][%s] %s media_info_get_book failed \\n", __LINE__, API_NAMESPACE, "MediaItemCb");
                return false;
        }

        return true;
}

/**
 * @function            ITs_media_content_info_startup
 * @description         Called before each test
 * @parameter           NA
 * @return                      NA
 */
void ITs_media_content_book_startup(void)
{
        struct stat stBuff;
        if ( stat(ERR_LOG, &stBuff) == 0 )
        {
                remove(ERR_LOG);
        }
        g_bMediaContentStartup = false;
        g_hFilter = NULL;
        pszMediaId = NULL;
        g_hBookDst = NULL;
        g_hBook = NULL;
	g_hBookInfo = NULL;
        int nRet;
        nRet = media_content_connect();
        if(nRet != MEDIA_CONTENT_ERROR_NONE){
                FPRINTF("[Line : %d][%s] media_content_connect api in startup failed\\n", __LINE__, API_NAMESPACE);
                return;
        }

	nRet = GetInternalStorageIdandPath();
	PRINT_RESULTNONE_CLEANUP(0, nRet, "GetInternalStorageId", "Return Value Not Correct", media_content_disconnect());

	AppendPaths(g_szInternalStoragePath, TESTBOOK, g_szBookPath);
	nRet = media_info_insert_to_db(g_szBookPath, &g_hBookInfo);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_insert_to_db", MediaContentGetError(nRet), media_content_disconnect());

        char *pszCondition = "MEDIA_TYPE=5 AND MEDIA_STORAGE_TYPE=0";
        nRet = media_filter_create(&g_hFilter);
        PRINT_RESULTNONE(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_create", MediaContentGetError(nRet));
        if(g_hFilter == NULL){
                FPRINTF("[Line : %d][%s] Filter Handle is Null\\n", __LINE__, API_NAMESPACE);
                return;
        }
        nRet = media_filter_set_condition(g_hFilter, pszCondition, MEDIA_CONTENT_COLLATE_DEFAULT);
        PRINT_RESULTNONE(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_set_condition", MediaContentGetError(nRet));

        nRet = media_filter_set_order(g_hFilter, MEDIA_CONTENT_ORDER_ASC, MEDIA_TITLE, MEDIA_CONTENT_COLLATE_DEFAULT);
        PRINT_RESULTNONE(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_set_order", MediaContentGetError(nRet));

        nRet = media_info_foreach_media_from_db(g_hFilter, MediaItemCb, NULL);
        if(nRet != MEDIA_CONTENT_ERROR_NONE){
                FPRINTF("[Line : %d][%s] media_info_foreach_media_from_db api in startup failed\\n", __LINE__, API_NAMESPACE);
                return;
        }
        g_bMediaContentStartup = true;
}

/**
 * @function            ITs_media_content_book_cleanup
 * @description         Called before each test
 * @parameter           NA
 * @return                      NA
 */
void ITs_media_content_book_cleanup(void)
{
        if (pszMediaId != NULL) {
                FREE_MEMORY(pszMediaId);
                pszMediaId = NULL;
        }

        if (g_hBook != NULL) {
                book_meta_destroy(g_hBook);
                g_hBook = NULL;
        }

        if (g_hBookDst!= NULL) {
                book_meta_destroy(g_hBookDst);
                g_hBookDst = NULL;
        }

        if (g_hFilter) {
                media_filter_destroy(g_hFilter);
                g_hFilter = NULL;
        }
	if(g_hBookInfo)
	{
		media_info_destroy(g_hBookInfo);
		g_hBookInfo = NULL;
	}
        media_content_disconnect();
}

/**
 * @testcase            ITc_media_book_meta_clone_destroy_p
 * @since_tizen         6.5
 * @author              SRID(mohit.m)
 * @reviewer            SRID(shobhit.v)
 * @type                auto
 * @scenario            calls the api based on code
 * @apitarget           book_meta_clone, book_meta_destroy
 * @apicovered          book_meta_clone, book_meta_destroy
 * @passcase            MEDIA_CONTENT_ERROR_NONE returned by book_meta_clone, book_meta_destroy
 * @failcase            MEDIA_CONTENT_ERROR_NONE not returned by book_meta_clone, book_meta_destroy
 * @precondition        NA
 * @postcondition       NA
 */
int ITc_media_book_meta_clone_destroy_p(void)
{
        START_TEST;

        int nRet;
        nRet = book_meta_clone(&g_hBookDst, g_hBook);
        PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "book_meta_clone", MediaContentGetError(nRet));
        CHECK_HANDLE(g_hBookDst, "book_meta_clone");

        //Target API
        nRet = book_meta_destroy(g_hBookDst);
        PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "book_meta_destroy", MediaContentGetError(nRet));
        g_hBookDst = NULL;
        return 0;
}

/**
 * @testcase            ITc_media_book_meta_get_media_id_p
 * @since_tizen         6.5
 * @author              SRID(mohit.m)
 * @reviewer            SRID(shobhit.v)
 * @type                auto
 * @scenario            calls the api based on code
 * @apitarget           book_meta_get_media_id
 * @apicovered          book_meta_get_media_id
 * @passcase            MEDIA_CONTENT_ERROR_NONE returned by book_meta_get_media_id
 * @failcase            MEDIA_CONTENT_ERROR_NONE not returned by book_meta_get_media_id
 * @precondition        NA
 * @postcondition       NA
 */
int ITc_media_book_meta_get_media_id_p(void)
{
        START_TEST;

        int nRet;
        char *pszMediaId = NULL;

        //Target API
        nRet = book_meta_get_media_id(g_hBook, &pszMediaId);
        PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "book_meta_get_media_id", MediaContentGetError(nRet));

        CHECK_HANDLE(pszMediaId, "book_meta_get_media_id");
        FREE_MEMORY(pszMediaId);

        return 0;
}

/**
 * @testcase            ITc_book_meta_get_subject_p
 * @since_tizen         6.5
 * @author              SRID(mohit.m)
 * @reviewer            SRID(shobhit.v)
 * @type                auto
 * @scenario            calls the api based on code
 * @apitarget           book_meta_get_subject
 * @apicovered          book_meta_get_subject
 * @passcase            MEDIA_CONTENT_ERROR_NONE returned by book_meta_get_subject
 * @failcase            MEDIA_CONTENT_ERROR_NONE not returned by book_meta_get_subject
 * @precondition        NA
 * @postcondition       NA
 */
int ITc_book_meta_get_subject_p(void)
{
        START_TEST;

        int nRet;
        char *pszSubjectId = NULL;

        //Target API
        nRet = book_meta_get_subject(g_hBook, &pszSubjectId);
        PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "book_meta_get_subject", MediaContentGetError(nRet));

        CHECK_HANDLE(pszSubjectId, "book_meta_get_subject");
        FREE_MEMORY(pszSubjectId);

        return 0;
}

/**
 * @testcase            ITc_book_meta_get_author_p
 * @since_tizen         6.5
 * @author              SRID(mohit.m)
 * @reviewer            SRID(shobhit.v)
 * @type                auto
 * @scenario            calls the api based on code
 * @apitarget           book_meta_get_author
 * @apicovered          book_meta_get_author
 * @passcase            MEDIA_CONTENT_ERROR_NONE returned by book_meta_get_author
 * @failcase            MEDIA_CONTENT_ERROR_NONE not returned by book_meta_get_author
 * @precondition        NA
 * @postcondition       NA
 */
int ITc_book_meta_get_author_p(void)
{
        START_TEST;

        int nRet;
        char *pszAuthor = NULL;

        //Target API
        nRet = book_meta_get_author(g_hBook, &pszAuthor);
        PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "book_meta_get_author", MediaContentGetError(nRet));

        CHECK_HANDLE(pszAuthor, "book_meta_get_author");
        FREE_MEMORY(pszAuthor);

        return 0;
}

/**
 * @testcase            ITc_book_meta_get_date_p
 * @since_tizen         6.5
 * @author              SRID(mohit.m)
 * @reviewer            SRID(shobhit.v)
 * @type                auto
 * @scenario            calls the api based on code
 * @apitarget           book_meta_get_date
 * @apicovered          book_meta_get_date
 * @passcase            MEDIA_CONTENT_ERROR_NONE returned by book_meta_get_date
 * @failcase            MEDIA_CONTENT_ERROR_NONE not returned by book_meta_get_date
 * @precondition        NA
 * @postcondition       NA
 */
int ITc_book_meta_get_date_p(void)
{
        START_TEST;

        int nRet;
        char *pszDate = NULL;

        //Target API
        nRet = book_meta_get_date(g_hBook, &pszDate);
        PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "book_meta_get_date", MediaContentGetError(nRet));

        CHECK_HANDLE(pszDate, "book_meta_get_date");
        FREE_MEMORY(pszDate);

        return 0;
}

/**
 * @testcase            ITc_book_meta_get_publisher_p
 * @since_tizen         6.5
 * @author              SRID(mohit.m)
 * @reviewer            SRID(shobhit.v)
 * @type                auto
 * @scenario            calls the api based on code
 * @apitarget           book_meta_get_publisher
 * @apicovered          book_meta_get_publisher
 * @passcase            MEDIA_CONTENT_ERROR_NONE returned by book_meta_get_publisher
 * @failcase            MEDIA_CONTENT_ERROR_NONE not returned by book_meta_get_publisher
 * @precondition        NA
 * @postcondition       NA
 */
int ITc_book_meta_get_publisher_p(void)
{
        START_TEST;

        int nRet;
        char *pszPublisher = NULL;

        //Target API
        nRet = book_meta_get_publisher(g_hBook, &pszPublisher);
        PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "book_meta_get_publisher", MediaContentGetError(nRet));

        CHECK_HANDLE(pszPublisher, "book_meta_get_publisher");
        FREE_MEMORY(pszPublisher);

        return 0;
}

/**
 * @testcase            ITc_media_book_meta_get_path_with_keyword_p
 * @since_tizen         6.5
 * @author              SRID(nibha.sharma)
 * @reviewer            SRID(shobhit.v)
 * @type                auto
 * @scenario            Gets a list of paths to ebooks which contain a given keyword.
 * @apitarget           book_meta_get_path_with_keyword
 * @apicovered          book_meta_get_path_with_keyword
 * @passcase            MEDIA_CONTENT_ERROR_NONE returned by book_meta_get_path_with_keyword
 * @failcase            MEDIA_CONTENT_ERROR_NONE not returned by book_meta_get_path_with_keyword
 * @precondition        NA
 * @postcondition       NA
 */
int ITc_media_book_meta_get_path_with_keyword_p(void)
{
	START_TEST;
	int nRet = MEDIA_CONTENT_ERROR_NONE;
	char **pszPathList = NULL;
	unsigned int nPathListLength = 0;
	const char *pszKeyword = "test";

	nRet = book_meta_get_path_with_keyword(pszKeyword, &pszPathList, &nPathListLength);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "book_meta_get_path_with_keyword", MediaContentGetError(nRet));

	while (pszPathList && nPathListLength > 0)
	{
		FREE_MEMORY(pszPathList[--nPathListLength]);
	}

	FREE_MEMORY(pszPathList);

	return 0;
}
