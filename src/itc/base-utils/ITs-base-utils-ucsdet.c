//
// Copyright (c) 2020 Samsung Electronics Co., Ltd.
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

#include "ITs-base-utils-common.h"

/** @addtogroup itc-base-utils
*  @ingroup itc
*  @{
*/
/**
* @function 		ITs_base_utils_ucsdet_startup
* @description	 	Called before each test
* @parameter		NA
* @return 	        NA
*/
void ITs_base_utils_ucsdet_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT start-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif
        int nRet = i18n_ucsdet_create(&g_hUcsd);
	if (nRet != I18N_ERROR_NONE)
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("\\n[Line : %d][%s] i18n_ucsdet_create failed with error code %s\\n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRet));
	}
	else if(g_hUcsd == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] g_hUcsd is null\\n", __LINE__, API_NAMESPACE);
		g_bBaseUtilsInitFlag = false;
	}
	else
	{
		g_bBaseUtilsInitFlag = true;
	}
	return;
}
/**
* @function 		ITs_base_utils_ucsdet_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 	        NA
*/
void ITs_base_utils_ucsdet_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

        int nRet = -1;
        if(g_hUcsd != NULL)
        {
               nRet = i18n_ucsdet_destroy(g_hUcsd);
               if(nRet != I18N_ERROR_NONE)
               {
                       FPRINTF("\\n[Line : %d][%s] i18n_ucsdet_destroy failed with error code %s\\n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRet));
               }
               g_hUcsd = NULL;
        }
        g_bBaseUtilsInitFlag = false;
	return;
}
/*
 * @testcase		ITc_i18n_ucsdet_create_destroy_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucsdet_create, i18n_ucsdet_destroy
 * @apicovered          i18n_ucsdet_create, i18n_ucsdet_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_ucsdet_create, i18n_ucsdet_destroy
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucsdet_create, i18n_ucsdet_destroy
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucsdet_create_destroy_p(void)
{
        START_TEST;

        int nRet = -1;
        nRet = i18n_ucsdet_destroy(g_hUcsd);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucsdet_destroy", BaseUtilsGetError(nRet));
        g_hUcsd = NULL;

        //Target API
        nRet = i18n_ucsdet_create(&g_hUcsd);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucsdet_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_hUcsd, "i18n_ucsdet_create");

        //Target API
        nRet = i18n_ucsdet_destroy(g_hUcsd);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucsdet_destroy", BaseUtilsGetError(nRet));
        g_hUcsd = NULL;

        nRet = i18n_ucsdet_create(&g_hUcsd);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucsdet_create", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucsdet_set_text_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucsdet_set_text
 * @apicovered		i18n_ustring_unescape, i18n_ucsdet_set_text
 * @passcase		I18N_ERROR_NONE returned by i18n_ucsdet_set_text
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucsdet_set_text
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucsdet_set_text_p(void)
{
        START_TEST;

        int nRet = -1;
        static const char szSrc[] = "This is a string with some non-ascii characters that will "
		"be converted to UTF-8, then showed through the detection process.  "
		"\\u0391\\u0392\\u0393\\u0394\\u0395"
		"Sure would be nice if our source could contain Unicode directly!";
        int32_t byte_length = 0, string_length = 0;
        int32_t dest_capacity = sizeof(szSrc);
	i18n_uchar szDest[dest_capacity];
        const char *pszCode = "UTF-8";
	char *pszBytes = NULL;

        string_length = i18n_ustring_unescape(szSrc, szDest, dest_capacity);
        pszBytes = UcsdetGetBytes(szDest, string_length, pszCode, &byte_length);
        CHECK_HANDLE(pszBytes, "UcsdetGetBytes");

        //Target API
        nRet = i18n_ucsdet_set_text(g_hUcsd, pszBytes, byte_length);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_set_text", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));

        FREE_MEMORY(pszBytes);
        return 0;
}
/*
 * @testcase		ITc_i18n_ucsdet_set_declared_encoding_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucsdet_set_declared_encoding
 * @apicovered		i18n_ucsdet_set_declared_encoding
 * @passcase		I18N_ERROR_NONE returned by i18n_ucsdet_set_declared_encoding
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucsdet_set_declared_encoding
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucsdet_set_declared_encoding_p(void)
{
        START_TEST;

        int nRet = -1;
        const char* pszEncoding = "ISO-2022-JP";

        //Target API
        nRet = i18n_ucsdet_set_declared_encoding(g_hUcsd, pszEncoding, -1);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucsdet_set_declared_encoding", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucsdet_detect_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_uidna_label_to_ascii
 * @apicovered		i18n_ustring_unescape, i18n_ucsdet_detect
 * @passcase		I18N_ERROR_NONE returned by i18n_ucsdet_detect
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucsdet_detect
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucsdet_detect_p(void)
{
        START_TEST;

        int nRet = -1;
        static const char szSrc[] = "This is a string with some non-ascii characters that will "
		"be converted to UTF-8, then showed through the detection process.  "
		"\\u0391\\u0392\\u0393\\u0394\\u0395"
		"Sure would be nice if our source could contain Unicode directly!";

        int32_t byte_length = 0, string_length = 0;
        int32_t dest_capacity = sizeof(szSrc);
	i18n_uchar szDest[dest_capacity];
	char *pszBytes = NULL;
        const char *pszCode = "UTF-8";
        i18n_ucharset_match_h h_ucsm = NULL;

        string_length = i18n_ustring_unescape(szSrc, szDest, dest_capacity);
        pszBytes = UcsdetGetBytes(szDest, string_length, pszCode, &byte_length);
        CHECK_HANDLE(pszBytes, "UcsdetGetBytes");

        nRet = i18n_ucsdet_set_text(g_hUcsd, pszBytes, byte_length);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_set_text", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));

        //Target API
        nRet = i18n_ucsdet_detect(g_hUcsd, &h_ucsm);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_detect", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));
        CHECK_HANDLE_CLEANUP(h_ucsm, "i18n_ucsdet_detect", FREE_MEMORY(pszBytes));

        FREE_MEMORY(pszBytes);
        return 0;
}
/*
 * @testcase		ITc_i18n_ucsdet_detect_all_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucsdet_detect_all
 * @apicovered		i18n_ucsdet_get_language, i18n_ustring_unescape, i18n_ucsdet_enable_input_filter, i18n_ucsdet_set_text
 * @passcase		I18N_ERROR_NONE returned by i18n_ucsdet_detect_all
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucsdet_detect_all
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucsdet_detect_all_p(void)
{
        START_TEST;

        int nRet = -1;
        static const char szSrc[] = "<a> <lot> <of> <English> <inside> <the> <markup> Un tr\\u00E8s petit peu de Fran\\u00E7ais. <to> <confuse> <the> <detector>";
	int32_t string_length = 0;
        int32_t dest_capacity = sizeof(szSrc);
	i18n_uchar szDest[dest_capacity];
	int32_t byte_length = 0;
	char *pszBytes = NULL;
        const char *pszCode = "UTF-8";
        i18n_ubool bResult = false;
        i18n_ucharset_match_h *h_ucsms;
	int32_t matches_found = -1;

        string_length = i18n_ustring_unescape(szSrc, szDest, dest_capacity);
	pszBytes = UcsdetGetBytes(szDest, string_length, pszCode, &byte_length);
        CHECK_HANDLE(pszBytes, "UcsdetGetBytes");

        nRet = i18n_ucsdet_enable_input_filter(g_hUcsd, true, &bResult);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_enable_input_filter", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));

        nRet = i18n_ucsdet_is_input_filter_enabled(g_hUcsd, &bResult);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_is_input_filter_enabled", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));
        PRINT_RESULT_CLEANUP(true, bResult, "i18n_ucsdet_is_input_filter_enabled", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));

        nRet = i18n_ucsdet_set_text(g_hUcsd, pszBytes, byte_length);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_set_text", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));

        //Target API
        nRet = i18n_ucsdet_detect_all(g_hUcsd, &matches_found, &h_ucsms);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_detect_all", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));
        if(matches_found < 0)
        {
                FPRINTF("\\n[Line : %d][%s] i18n_ucsdet_detect_all failed ,matches_found is not correct \n", __LINE__, API_NAMESPACE);
                FREE_MEMORY(pszBytes);
                return 1;
        }

        FREE_MEMORY(pszBytes);
        return 0;
}
/*
 * @testcase		ITc_i18n_ucsdet_get_name_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucsdet_get_name
 * @apicovered		i18n_ucsdet_get_language, i18n_ustring_unescape, i18n_ucsdet_enable_input_filter, i18n_ucsdet_set_text
 * @passcase		I18N_ERROR_NONE returned by i18n_ucsdet_get_name
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucsdet_get_name
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucsdet_get_name_p(void)
{
        START_TEST;

        static const char szSrc[] = "<a> <lot> <of> <English> <inside> <the> <markup> Un tr\\u00E8s petit peu de Fran\\u00E7ais. <to> <confuse> <the> <detector>";
        int32_t string_length = 0;
        int32_t dest_capacity = sizeof(szSrc);
	i18n_uchar szDest[dest_capacity];
	int32_t byte_length = 0;
	char *pszBytes = NULL;
        i18n_ubool bResult = false;
        i18n_ucharset_match_h *h_ucsms;
        const char *pszName = NULL;
        const char *pszExpectedName = "ISO-8859-1";
	int32_t matches_found = -1;
        i18n_ucharset_match_h h_ucsm = NULL;
        int i = 0;
        int nRet = -1;

        string_length = i18n_ustring_unescape(szSrc, szDest, dest_capacity);
        pszBytes = UcsdetGetBytes(szDest, string_length, pszExpectedName, &byte_length);
        CHECK_HANDLE(pszBytes, "UcsdetGetBytes");

        nRet = i18n_ucsdet_enable_input_filter(g_hUcsd, true, &bResult);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_enable_input_filter", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));

        nRet = i18n_ucsdet_is_input_filter_enabled(g_hUcsd, &bResult);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_is_input_filter_enabled", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));
        PRINT_RESULT_CLEANUP(true, bResult, "i18n_ucsdet_is_input_filter_enabled", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));

        nRet = i18n_ucsdet_set_text(g_hUcsd, pszBytes, byte_length);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_set_text", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));

        nRet = i18n_ucsdet_detect_all(g_hUcsd, &matches_found, &h_ucsms);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_detect_all", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));
        if(matches_found < 0)
        {
                FPRINTF("\\n[Line : %d][%s] i18n_ucsdet_detect_all failed ,matches_found is not correct \n", __LINE__, API_NAMESPACE);
                FREE_MEMORY(pszBytes);
                return 1;
        }

        for(i = 0; i < matches_found; ++i)
        {
		h_ucsm = NULL;
                pszName = NULL;
		nRet = i18n_ucsdet_detect(g_hUcsd, &h_ucsm);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_detect", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));
                CHECK_HANDLE_CLEANUP(h_ucsm, "i18n_ucsdet_detect", FREE_MEMORY(pszBytes));

                //Target API
		nRet = i18n_ucsdet_get_name(h_ucsm, &pszName);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_get_name", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));
		CHECK_HANDLE_CLEANUP(pszName, "i18n_ucsdet_get_name", FREE_MEMORY(pszBytes));
                if(strncmp(pszExpectedName, pszName, strlen(pszExpectedName)) != 0)
                {
                        FPRINTF("[Line : %d][%s] i18n_ucsdet_get_name mismatch. pszExpectedName = %s, pszName= %s\\n", __LINE__, API_NAMESPACE, pszExpectedName, pszName);
                        FREE_MEMORY(pszBytes);
                        return 1;
                }
	}
        FREE_MEMORY(pszBytes);
        return 0;
}
/*
 * @testcase		ITc_i18n_ucsdet_get_confidence_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucsdet_get_confidence
 * @apicovered		i18n_ucsdet_get_language, i18n_ustring_unescape, i18n_ucsdet_enable_input_filter, i18n_ucsdet_set_text
 * @passcase		I18N_ERROR_NONE returned by i18n_ucsdet_get_confidence
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucsdet_get_confidence
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucsdet_get_confidence_p(void)
{
        START_TEST;

        int nRet = -1;
        static const char szSrc[] = "<a> <lot> <of> <English> <inside> <the> <markup> Un tr\\u00E8s petit peu de Fran\\u00E7ais. <to> <confuse> <the> <detector>";
        int32_t string_length = 0;
        int32_t dest_capacity = sizeof(szSrc);
	i18n_uchar szDest[dest_capacity];
	int32_t byte_length = 0;
	char *pszBytes = NULL;
        i18n_ubool bResult = false;
        i18n_ucharset_match_h *h_ucsms;
        i18n_ucharset_match_h h_ucsm = NULL;
	int32_t matches_found = -1;
        int32_t ConfidenceNumber = -1;
        int32_t ExpectedConfidenceNumber = 56;
        const char *pszNameCode = "ISO-8859-1";
        int i = 0;

        string_length = i18n_ustring_unescape(szSrc, szDest, dest_capacity);
        pszBytes = UcsdetGetBytes(szDest, string_length, pszNameCode, &byte_length);
        CHECK_HANDLE(pszBytes, "UcsdetGetBytes");

        nRet = i18n_ucsdet_enable_input_filter(g_hUcsd, true, &bResult);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_enable_input_filter", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));

        nRet = i18n_ucsdet_is_input_filter_enabled(g_hUcsd, &bResult);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_is_input_filter_enabled", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));
        PRINT_RESULT_CLEANUP(true, bResult, "i18n_ucsdet_is_input_filter_enabled", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));

        nRet = i18n_ucsdet_set_text(g_hUcsd, pszBytes, byte_length);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_set_text", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));

        nRet = i18n_ucsdet_detect_all(g_hUcsd, &matches_found, &h_ucsms);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_detect_all", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));
        if(matches_found < 0)
        {
                FPRINTF("\\n[Line : %d][%s] i18n_ucsdet_detect_all failed ,matches_found is not correct \n", __LINE__, API_NAMESPACE);
                FREE_MEMORY(pszBytes);
                return 1;
        }

        for(i = 0; i < matches_found; ++i)
        {
		h_ucsm = NULL;
                ConfidenceNumber = -1;
		nRet = i18n_ucsdet_detect(g_hUcsd, &h_ucsm);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_detect", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));
                CHECK_HANDLE_CLEANUP(h_ucsm, "i18n_ucsdet_detect", FREE_MEMORY(pszBytes));

                //Target API
                nRet = i18n_ucsdet_get_confidence(h_ucsm, &ConfidenceNumber);
                PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_get_confidence", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));
                PRINT_RESULT_CLEANUP(ExpectedConfidenceNumber, ConfidenceNumber, "i18n_ucsdet_get_confidence", "obtained and expected number are not same", FREE_MEMORY(pszBytes));
	}
        FREE_MEMORY(pszBytes);
        return 0;
}
/*
 * @testcase		ITc_i18n_ucsdet_get_language_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucsdet_get_language
 * @apicovered		i18n_ucsdet_get_language, i18n_ustring_unescape, i18n_ucsdet_enable_input_filter, i18n_ucsdet_set_text
 * @passcase		I18N_ERROR_NONE returned by i18n_ucsdet_get_language
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucsdet_get_language
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucsdet_get_language_p(void)
{
        START_TEST;

        int nRet = -1;
        static const char szSrc[] = "<a> <lot> <of> <English> <inside> <the> <markup> Un tr\\u00E8s petit peu de Fran\\u00E7ais. <to> <confuse> <the> <detector>";
        int32_t string_length = 0;
        int32_t dest_capacity = sizeof(szSrc);
	i18n_uchar szDest[dest_capacity];
	int32_t byte_length = 0;
	char *pszBytes = NULL;
        i18n_ubool bResult = false;
        i18n_ucharset_match_h *h_ucsms;
        i18n_ucharset_match_h h_ucsm = NULL;
        const char *pszLanguage = NULL;
        const char *pszExpectedLanguage = "fr";
	int32_t matches_found = -1;
        const char *pszNameCode = "ISO-8859-1";
        int i = 0;

        string_length = i18n_ustring_unescape(szSrc, szDest, dest_capacity);
        pszBytes = UcsdetGetBytes(szDest, string_length, pszNameCode, &byte_length);
        CHECK_HANDLE(pszBytes, "UcsdetGetBytes");

        nRet = i18n_ucsdet_enable_input_filter(g_hUcsd, true, &bResult);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_enable_input_filter", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));

        nRet = i18n_ucsdet_is_input_filter_enabled(g_hUcsd, &bResult);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_is_input_filter_enabled", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));
        PRINT_RESULT_CLEANUP(true, bResult, "i18n_ucsdet_is_input_filter_enabled", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));

        nRet = i18n_ucsdet_set_text(g_hUcsd, pszBytes, byte_length);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_set_text", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));

        nRet = i18n_ucsdet_detect_all(g_hUcsd, &matches_found, &h_ucsms);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_detect_all", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes))
        if(matches_found < 0)
        {
                FPRINTF("\\n[Line : %d][%s] i18n_ucsdet_detect_all failed ,matches_found is not correct \n", __LINE__, API_NAMESPACE);
                FREE_MEMORY(pszBytes);
                return 1;
        }

        for(i = 0; i < matches_found; ++i)
        {
		h_ucsm = NULL;
                pszLanguage = NULL;
		nRet = i18n_ucsdet_detect(g_hUcsd, &h_ucsm);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_detect", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));
                CHECK_HANDLE_CLEANUP(h_ucsm, "i18n_ucsdet_detect", FREE_MEMORY(pszBytes));

                //Target API
                nRet = i18n_ucsdet_get_language(h_ucsm, &pszLanguage);
                PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_get_language", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));
                CHECK_HANDLE_CLEANUP(pszLanguage, "i18n_ucsdet_get_language", FREE_MEMORY(pszBytes));
                if(strncmp(pszExpectedLanguage, pszLanguage, strlen(pszExpectedLanguage)) != 0)
                {
                        FPRINTF("[Line : %d][%s] i18n_ucsdet_get_language mismatch. pszExpectedLanguage = %s, pszLanguage= %s\\n", __LINE__, API_NAMESPACE, pszExpectedLanguage, pszLanguage);
                        FREE_MEMORY(pszBytes);
                        return 1;
                }

	}
        FREE_MEMORY(pszBytes);
        return 0;
}
/*
 * @testcase		ITc_i18n_ucsdet_get_uchars_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucsdet_get_uchars
 * @apicovered		i18n_ustring_unescape, i18n_ucsdet_set_text. i18n_ucsdet_detect
 * @passcase		I18N_ERROR_NONE returned by i18n_ucsdet_get_uchars
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucsdet_get_uchars
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucsdet_get_uchars_p(void)
{
        START_TEST;

        int nRet = -1;
        static const char szSrc[] = "This is a string with some non-ascii characters that will "
		"be converted to UTF-8, then showed through the detection process.  "
		"\\u0391\\u0392\\u0393\\u0394\\u0395"
		"Sure would be nice if our source could contain Unicode directly!";

        int32_t byte_length = 0, string_length = 0, ObtainedLength = -1;
        int32_t dest_capacity = sizeof(szSrc);
	i18n_uchar szDest[dest_capacity];
	char *pszBytes = NULL;
        i18n_ucharset_match_h h_ucsm = NULL;
        i18n_uchar detected[dest_capacity];

        string_length = i18n_ustring_unescape(szSrc, szDest, dest_capacity);
        pszBytes = UcsdetGetBytes(szDest, string_length, "UTF-8", &byte_length);
        CHECK_HANDLE(pszBytes, "UcsdetGetBytes");

        nRet = i18n_ucsdet_set_text(g_hUcsd, pszBytes, byte_length);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_set_text", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));

        nRet = i18n_ucsdet_detect(g_hUcsd, &h_ucsm);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_detect", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));
        CHECK_HANDLE_CLEANUP(h_ucsm, "i18n_ucsdet_detect", FREE_MEMORY(pszBytes));

        //Target API
        nRet = i18n_ucsdet_get_uchars(h_ucsm, detected, string_length, &ObtainedLength);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_get_uchars", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));
        if(ObtainedLength < 0)
        {
                FPRINTF("\\n[Line : %d][%s] i18n_ucsdet_get_uchars failed ,ObtainedLength is not correct \n", __LINE__, API_NAMESPACE);
                FREE_MEMORY(pszBytes);
                return 1;
        }


        FREE_MEMORY(pszBytes);
        return 0;
}
/*
 * @testcase		ITc_i18n_ucsdet_get_all_detectable_charsets_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucsdet_get_all_detectable_charsets
 * @apicovered          i18n_ucsdet_get_all_detectable_charsets
 * @passcase		I18N_ERROR_NONE returned by i18n_ucsdet_get_all_detectable_charsets
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucsdet_get_all_detectable_charsets
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucsdet_get_all_detectable_charsets_p(void)
{
        START_TEST;

        int nRet = -1;
        i18n_uenumeration_h h_iterator = NULL;

        //Target API
	nRet = i18n_ucsdet_get_all_detectable_charsets(g_hUcsd, &h_iterator);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucsdet_get_all_detectable_charsets", BaseUtilsGetError(nRet));
	CHECK_HANDLE(h_iterator, "i18n_ucsdet_get_all_detectable_charsets");

        return 0;
}
/*
 * @testcase		ITc_i18n_ucsdet_is_input_filter_enabled
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucsdet_is_input_filter_enabled
 * @apicovered          i18n_ucsdet_enable_input_filter, i18n_ucsdet_is_input_filter_enabled, i18n_ustring_unescape
 * @passcase		I18N_ERROR_NONE returned by i18n_ucsdet_is_input_filter_enabled
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucsdet_is_input_filter_enabled
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucsdet_is_input_filter_enabled(void)
{
        START_TEST;

        int nRet = -1;
        static const char szSrc[] = "<a> <lot> <of> <English> <inside> <the> <markup> Un tr\\u00E8s petit peu de Fran\\u00E7ais. <to> <confuse> <the> <detector>";
	int32_t string_length = 0;
        int32_t dest_capacity = sizeof(szSrc);
	i18n_uchar szDest[dest_capacity];
	int32_t byte_length = 0;
	char *pszBytes = NULL;
        i18n_ubool bResult = false;

        string_length = i18n_ustring_unescape(szSrc, szDest, dest_capacity);
	pszBytes = UcsdetGetBytes(szDest, string_length, "UTF-8", &byte_length);
        CHECK_HANDLE(pszBytes, "UcsdetGetBytes");

        nRet = i18n_ucsdet_enable_input_filter(g_hUcsd, true, &bResult);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_enable_input_filter", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));

        //Target API
        nRet = i18n_ucsdet_is_input_filter_enabled(g_hUcsd, &bResult);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucsdet_is_input_filter_enabled", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));
        PRINT_RESULT_CLEANUP(true, bResult, "i18n_ucsdet_is_input_filter_enabled", BaseUtilsGetError(nRet), FREE_MEMORY(pszBytes));

        FREE_MEMORY(pszBytes);
        return 0;
}
/*
 * @testcase		ITc_i18n_ucsdet_enable_input_filter_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucsdet_enable_input_filter
 * @apicovered		i18n_ucsdet_enable_input_filter
 * @passcase		I18N_ERROR_NONE returned by i18n_ucsdet_enable_input_filter
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucsdet_enable_input_filter
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucsdet_enable_input_filter_p(void)
{
        START_TEST;

        int nRet = -1;
        i18n_ubool bResult = false;
	nRet = i18n_ucsdet_enable_input_filter(g_hUcsd, true, &bResult);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucsdet_enable_input_filter", BaseUtilsGetError(nRet));
        return 0;
}
