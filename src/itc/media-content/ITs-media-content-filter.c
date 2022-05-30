//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-media-content-common.h"

//& set: MediaContent

/** @addtogroup itc-media-content
*  @ingroup itc
*  @{
*/

/****************************************************Enums Start****************************************************/

media_content_collation_e g_eCollationTypeInput[] = {
														MEDIA_CONTENT_COLLATE_DEFAULT,
														MEDIA_CONTENT_COLLATE_NOCASE,
														MEDIA_CONTENT_COLLATE_RTRIM,
														MEDIA_CONTENT_COLLATE_LOCALIZED
													};

media_content_order_e g_eContentOrder[] = {
											MEDIA_CONTENT_ORDER_ASC,
											MEDIA_CONTENT_ORDER_DESC
										};

/*****************************************************Enums End*****************************************************/



/**
 * @function 		ITs_media_content_filter_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_filter_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	g_bMediaContentStartup = false;
	int nRet = media_content_connect();
	PRINT_RESULTNONE(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_connect", MediaContentGetError(nRet));

	nRet = media_filter_create(&g_hFilter);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_create", MediaContentGetError(nRet), media_content_disconnect());

	g_bMediaContentStartup = true;
	return;
}

/**
 * @function 		ITs_media_content_filter_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_filter_cleanup(void)
{
	if(g_bMediaContentStartup)
	{
		media_filter_destroy(g_hFilter);
		media_content_disconnect();
	}
	return;
}

/** @addtogroup itc-media-content-testcases
*  @brief 		Integration testcases for module media-content
*  @ingroup 	itc-media-content
*  @{
*/

/**
* @testcase 			ITc_media_filter_create_destroy_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_filter_create and media_filter_destroy
* @scenario				Call media_filter_create and media_filter_destroy
* @apicovered			media_filter_create, media_filter_destroy
* @passcase				When media_filter_create and media_filter_destroy is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_filter_create and media_filter_destroy
//& type: auto
int ITc_media_filter_create_destroy_p(void)
{
	START_TEST;

	filter_h hFilter = NULL;
	int nRet = media_filter_create(&hFilter);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_create", MediaContentGetError(nRet));
	CHECK_HANDLE(hFilter, "media_filter_create");

	nRet = media_filter_destroy(hFilter);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_destroy", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_filter_set_get_condition_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_filter_set_condition and media_filter_get_condition
* @scenario				Call media_filter_set_condition and media_filter_get_condition
* @apicovered			media_filter_set_condition, media_filter_get_condition
* @passcase				When media_filter_set_condition and media_filter_get_condition is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_filter_set_condition and media_filter_get_condition
//& type: auto
int ITc_media_filter_set_get_condition_p(void)
{
	START_TEST;
	int nRet = 0;
	char* pszCondition = NULL;
	int nEnumCounter = 0;
	media_content_collation_e eCollateType = -1;
	int nEnumSize = sizeof(g_eCollationTypeInput) / sizeof(g_eCollationTypeInput[0]);

	for ( nEnumCounter= 0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		nRet = media_filter_set_condition(g_hFilter, FILTERCONDITION, g_eCollationTypeInput[nEnumCounter]);
		PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_set_condition", MediaContentGetError(nRet));

		nRet = media_filter_get_condition(g_hFilter, &pszCondition, &eCollateType);
		PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_get_condition", MediaContentGetError(nRet));
		CHECK_HANDLE(pszCondition, "media_filter_get_condition");
		PRINT_RESULT_CLEANUP(0, strcmp(pszCondition, FILTERCONDITION), "media_filter_get_condition", "Condition Mismatch", FREE_MEMORY(pszCondition));
		PRINT_RESULT_CLEANUP(g_eCollationTypeInput[nEnumCounter], eCollateType, "media_filter_get_condition", "Collation type Mismatch", FREE_MEMORY(pszCondition));

		FREE_MEMORY(pszCondition);
	}

	return 0;
}

/**
* @testcase 			ITc_media_filter_set_get_order_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_filter_set_order and media_filter_get_order
* @scenario				Call media_filter_set_order and media_filter_get_order
* @apicovered			media_filter_set_order, media_filter_get_order
* @passcase				When media_filter_set_order and media_filter_get_order is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_filter_set_order and media_filter_get_order
//& type: auto
int ITc_media_filter_set_get_order_p(void)
{
	START_TEST;
	int nRet = 0;
	char* pszOrder = NULL;
	int nEnumCounter = 0;
	media_content_collation_e eCollateType = -1;
	int nEnumSize = sizeof(g_eCollationTypeInput) / sizeof(g_eCollationTypeInput[0]);

	int nEnumCounterOuter = 0;
	media_content_order_e eOrderType = -1;
	int nEnumSizeOuter = sizeof(g_eContentOrder) / sizeof(g_eContentOrder[0]);

	for(nEnumCounterOuter = 0; nEnumCounterOuter < nEnumSizeOuter; nEnumCounterOuter++)
	{
		for ( nEnumCounter= 0; nEnumCounter < nEnumSize; nEnumCounter++)
		{
			nRet = media_filter_set_order(g_hFilter, g_eContentOrder[nEnumCounterOuter], MEDIA_TITLE, g_eCollationTypeInput[nEnumCounter]);
			PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_set_order", MediaContentGetError(nRet));

			nRet = media_filter_get_order(g_hFilter, &eOrderType, &pszOrder, &eCollateType);
			PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_get_order", MediaContentGetError(nRet));
			CHECK_HANDLE(pszOrder, "media_filter_get_order");
			PRINT_RESULT_CLEANUP(0, strcmp(pszOrder, MEDIA_TITLE), "media_filter_get_order", "Condition Mismatch", FREE_MEMORY(pszOrder));
			PRINT_RESULT_CLEANUP(g_eCollationTypeInput[nEnumCounter], eCollateType, "media_filter_get_order", "Collation type Mismatch", FREE_MEMORY(pszOrder));
			PRINT_RESULT_CLEANUP(g_eContentOrder[nEnumCounterOuter], eOrderType, "media_filter_get_order", "Order Mismatch", FREE_MEMORY(pszOrder));

			FREE_MEMORY(pszOrder);
		}
	}

	return 0;
}

/**
* @testcase 			ITc_media_filter_set_get_offset_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_filter_set_offset and media_filter_get_offset
* @scenario				Call media_filter_set_offset and media_filter_get_offset
* @apicovered			media_filter_set_offset, media_filter_get_offset
* @passcase				When media_filter_set_offset and media_filter_get_offset is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_filter_set_offset and media_filter_get_offset
//& type: auto
int ITc_media_filter_set_get_offset_p(void)
{
	START_TEST;
	int nRet = 0;
	int nOffset = -1;
	int nCount = -1;

	nRet = media_filter_set_offset(g_hFilter, 1, 1);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_set_offset", MediaContentGetError(nRet));

	nRet = media_filter_get_offset(g_hFilter, &nOffset, &nCount);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_get_offset", MediaContentGetError(nRet));
	PRINT_RESULT(1, nOffset, "media_filter_get_offset", "Offset Mismatch");
	PRINT_RESULT(1, nCount, "media_filter_get_offset", "Count Mismatch");

	return 0;
}


/** @} */
/** @} */
