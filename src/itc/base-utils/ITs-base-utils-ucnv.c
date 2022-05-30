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
* @function 		ITs_base_utils_ucnv_startup
* @description	 	Called before each test
* @parameter		NA
* @return 	        NA
*/
void ITs_base_utils_ucnv_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT start-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
/**
* @function 		ITs_base_utils_ucnv_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 	        NA
*/
void ITs_base_utils_ucnv_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	return;
}
/*
 * @testcase		ITc_i18n_ucnv_get_max_bytes_for_string_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_get_max_bytes_for_string
 * @apicovered          i18n_ucnv_get_max_bytes_for_string
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_get_max_bytes_for_string
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_get_max_bytes_for_string
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_get_max_bytes_for_string_p(void)
{
        START_TEST_PRINT;

        int result = -1;
        int ExpectedResult = 22;
        int nRet = -1;

        //Target API
        result = i18n_ucnv_get_max_bytes_for_string(1, 2);
	PRINT_RESULT(ExpectedResult, result, "i18n_ucnv_get_max_bytes_for_string", "result and ExpectedResult are not same");

	nRet = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "get_last_result", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_compare_names_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_compare_names
 * @apicovered          i18n_ucnv_compare_names
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_compare_names
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_compare_names
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_compare_names_p(void)
{
        START_TEST_PRINT;

        static const char *szSrc1[] = { "UTF-8", "utf_8", "u*T@f08", "Utf 8" };
        static const char *szSrc2[] = { "utf", "utfa", "utfb", "utfc"};
        static const char *szSrc3[] = { "utfc", "utfb", "utfa", "utf"};
        int count = 3;
        int i;
        int nRet = -1;

        for(i = 0; i < count; i++)
        {
                //Target API
                nRet = i18n_ucnv_compare_names(szSrc1[i], szSrc1[i + 1]);
                PRINT_RESULT(nRet, 0 , "i18n_ucnv_compare_names", "expected and obtained result are not same");

                //Target API
                nRet = i18n_ucnv_compare_names(szSrc2[i], szSrc2[i + 1]);
                if(nRet >= 0)
                {
                        FPRINTF("\\n[Line : %d][%s] i18n_ucnv_compare_names failed ,return value is not correct \n", __LINE__, API_NAMESPACE);
                        return 1;
                }

                //Target API
                nRet = i18n_ucnv_compare_names(szSrc3[i], szSrc3[i + 1]);
                if(nRet <= 0)
                {
                        FPRINTF("\\n[Line : %d][%s] i18n_ucnv_compare_names failed ,return value is not correct \n", __LINE__, API_NAMESPACE);
                        return 1;
                }
        }

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_create_destroy_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_create, i18n_ucnv_destroy
 * @apicovered          i18n_ucnv_create, i18n_ucnv_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_create, i18n_ucnv_destroy
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_create, i18n_ucnv_destroy
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_create_destroy_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = "ibm-949";

        //Target API
        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));
        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_create_unicode_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_create_unicode
 * @apicovered          i18n_ucnv_create_unicode
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_create_unicode
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_create_unicode
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_create_unicode_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_uchar szConv[] = {0x0069, 0x0062, 0x006d, 0x002d, 0x0039, 0x0034, 0x0033, 0x0000};

        i18n_ucnv_h hCnv = NULL;

        //Target API
        nRet = i18n_ucnv_create_unicode(szConv, &hCnv);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create_unicode", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create_unicode");

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));
        hCnv = NULL;

        //Target API
        nRet = i18n_ucnv_create_unicode(NULL, &hCnv);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create_unicode", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create_unicode");

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));
        hCnv = NULL;

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_create_ccsid_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_create_ccsid
 * @apicovered          i18n_ucnv_create_ccsid
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_create_ccsid
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_create_ccsid
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_create_ccsid_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        int szCodePointSize = -1;
        int i;
        int32_t szCodePoints[]={ 37, 850, 943, 949, 950, 1047, 1252, 1392, 33722 };
        i18n_ucnv_h hCnv = NULL;

        szCodePointSize = sizeof(szCodePoints)/sizeof(szCodePoints[0]);

        for(i = 0; i < szCodePointSize; i++)
        {
                //Target API
                nRet = i18n_ucnv_create_ccsid(szCodePoints[i], I18N_UCNV_IBM, &hCnv);
                PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create_ccsid", BaseUtilsGetError(nRet));
                CHECK_HANDLE(hCnv, "i18n_ucnv_create_ccsid");

                nRet = i18n_ucnv_destroy(hCnv);
                PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));
                hCnv = NULL;
        }

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_safe_clone_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_safe_clone
 * @apicovered          i18n_ucnv_safe_clone
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_safe_clone
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_safe_clone
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_safe_clone_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv1 = NULL;
        i18n_ucnv_h hCnv2 = NULL;
        const char *pszConv = "iso-8859-3";

        nRet = i18n_ucnv_create(pszConv, &hCnv1);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv1, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_safe_clone(hCnv1, &hCnv2);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_safe_clone", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv1));
        CHECK_HANDLE_CLEANUP(hCnv2, "i18n_ucnv_safe_clone", i18n_ucnv_destroy(hCnv1));

        nRet = i18n_ucnv_destroy(hCnv2);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        nRet = i18n_ucnv_destroy(hCnv1);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_set_get_subst_chars_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_set_subst_chars, i18n_ucnv_get_subst_chars
 * @apicovered          i18n_ucnv_create, i18n_ucnv_set_subst_chars, i18n_ucnv_get_subst_chars, i18n_ucnv_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_set_subst_chars, i18n_ucnv_get_subst_chars
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_set_subst_chars, i18n_ucnv_get_subst_chars
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_set_get_subst_chars_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        char new_subchars[] = {0x7F};
	char get_subchars[10];
	int8_t len = sizeof(new_subchars);
        i18n_ucnv_h hCnv = NULL;

	nRet = i18n_ucnv_create(NULL, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
	nRet = i18n_ucnv_set_subst_chars(hCnv, new_subchars, len);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_set_subst_chars", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        //Target API
	nRet = i18n_ucnv_get_subst_chars(hCnv, get_subchars, &len);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_subst_chars", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));
        PRINT_RESULT_CLEANUP(1, len, "i18n_ucnv_get_subst_chars", "expected and obtained length are not same", i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_set_subst_string_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_set_subst_string
 * @apicovered          i18n_ucnv_set_subst_string
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_set_subst_string
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_set_subst_string
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_set_subst_string_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = "ISO-8859-1";
        char DestBuffer[16];
	int8_t length;
	static const i18n_uchar szSrc[] = { 0x61, 0x62, 0x63, 0x64, 0x65 };
        int32_t szSrcSize = (int32_t)(sizeof(szSrc)/sizeof(szSrc[0]));

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_set_subst_string(hCnv, szSrc, szSrcSize);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_set_subst_string", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        length = sizeof(DestBuffer);
        nRet = i18n_ucnv_get_subst_chars(hCnv, DestBuffer, &length);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_subst_chars", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_get_invalid_chars_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_get_invalid_chars
 * @apicovered          i18n_ucnv_get_invalid_chars
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_get_invalid_chars
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_get_invalid_chars
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_get_invalid_chars_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = NULL;
        char szInvalidChars[10];
        int8_t InvalidLength = (int32_t)(sizeof(szInvalidChars)/sizeof(szInvalidChars[0]));

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_get_invalid_chars(hCnv, szInvalidChars, &InvalidLength);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_invalid_chars", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));
        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_get_invalid_uchars_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_get_invalid_uchars
 * @apicovered          i18n_ucnv_get_invalid_uchars
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_get_invalid_uchars
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_get_invalid_uchars
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_get_invalid_uchars_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = NULL;
        i18n_uchar szInvalidChars[10];
        int8_t InvalidLength = (int32_t)(sizeof(szInvalidChars)/sizeof(szInvalidChars[0]));

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_get_invalid_uchars(hCnv, szInvalidChars, &InvalidLength);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_invalid_uchars", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));
        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_reset_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_reset
 * @apicovered          i18n_ucnv_reset
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_reset
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_reset
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_reset_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = NULL;

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_reset(hCnv);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_reset", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_reset_to_unicode_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_reset_to_unicode
 * @apicovered          i18n_ucnv_reset_to_unicode
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_reset_to_unicode
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_reset_to_unicode
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_reset_to_unicode_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = NULL;

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_reset_to_unicode(hCnv);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_reset_to_unicode", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_reset_from_unicode_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_reset_from_unicode
 * @apicovered          i18n_ucnv_reset_from_unicode
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_reset_from_unicode
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_reset_from_unicode
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_reset_from_unicode_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = NULL;

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_reset_from_unicode(hCnv);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_reset_from_unicode", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_get_max_char_size_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_get_max_char_size
 * @apicovered          i18n_ucnv_get_max_char_size
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_get_max_char_size
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_get_max_char_size
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_get_max_char_size_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = "UTF-16";
        int8_t size = -1;

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_get_max_char_size(hCnv, &size);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_max_char_size", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));
        PRINT_RESULT_CLEANUP(size, 2, "i18n_ucnv_get_max_char_size", "obtained and expected size are not same", i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_get_min_char_size_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_get_min_char_size
 * @apicovered          i18n_ucnv_get_min_char_size
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_get_min_char_size
 * @failcase		I18N_ERROR_NONE not returned i18n_ucnv_get_min_char_size
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_get_min_char_size_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = "ibm-949_P110-1999";
        int8_t size = -1;

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_get_min_char_size(hCnv, &size);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_min_char_size", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));
        PRINT_RESULT_CLEANUP(size, 1, "i18n_ucnv_get_min_char_size", "obtained and expected size are not same", i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_get_display_name_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_get_display_name
 * @apicovered          i18n_ucnv_get_display_name
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_get_display_name
 * @failcase		I18N_ERROR_NONE not returned i18n_ucnv_get_display_name
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_get_display_name_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = "ibm-949";
        i18n_uchar *pszDisplayName = NULL;
	int32_t DisplayCapacity = 0;
	int32_t DisplayNameLen = -1;
        const char *pszDisplayLocale = "ko_KR";

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        nRet = i18n_ucnv_get_display_name(hCnv, pszDisplayLocale, pszDisplayName, DisplayCapacity, &DisplayNameLen);
        if(I18N_ERROR_BUFFER_OVERFLOW == nRet) {
		pszDisplayName = (i18n_uchar *)malloc((I18N_UCHAR_CAPACITY) * sizeof(i18n_uchar));
		nRet = i18n_ucnv_get_display_name(hCnv, pszDisplayLocale, pszDisplayName, I18N_UCHAR_CAPACITY, &DisplayNameLen);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_display_name", BaseUtilsGetError(nRet), FREE_MEMORY(pszDisplayName); i18n_ucnv_destroy(hCnv));
                if(DisplayNameLen < 0)
                {
                        FPRINTF("\\n[Line : %d][%s] i18n_ucnv_get_display_name failed ,DisplayNameLen is not correct \n", __LINE__, API_NAMESPACE);
                        FREE_MEMORY(pszDisplayName);
                        i18n_ucnv_destroy(hCnv);
                        return 1;
                }
		FREE_MEMORY(pszDisplayName);
		pszDisplayName = NULL;
	}

        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_display_name", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));
        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_get_name_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_get_name
 * @apicovered          i18n_ucnv_get_name
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_get_name
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_get_name
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_get_name_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        static const char *const pszNames[] = {
		"Unicode",					"UTF-16",
		"UnicodeBigUnmarked",		"UTF-16BE",
		"UnicodeBig",				"UTF-16BE,version=1",
		"UnicodeLittleUnmarked",	"UTF-16LE",
		"UnicodeLittle",			"UTF-16LE,version=1",
		"x-UTF-16LE-BOM",			"UTF-16LE,version=1"
	};
        int nCount = 12;
        int i = 0;
        const char *pszEncodedNames = NULL;

        for(i = 0; i < nCount; i += 2)
        {
                pszEncodedNames = NULL;
                hCnv = NULL;
                nRet = i18n_ucnv_create(pszNames[i], &hCnv);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
                CHECK_HANDLE(hCnv, "i18n_ucnv_create");

                //Target API
                nRet = i18n_ucnv_get_name(hCnv, &pszEncodedNames);
                PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_name", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));
                CHECK_HANDLE_CLEANUP(pszEncodedNames, "i18n_ucnv_get_name", i18n_ucnv_destroy(hCnv));

                if(strncmp(pszNames[i + 1], pszEncodedNames, strlen(pszNames[i + 1])) != 0)
                {
                        FPRINTF("[Line : %d][%s] i18n_ucnv_get_name mismatch. pszExpected = %s, pszEncodedNames = %s\\n", __LINE__, API_NAMESPACE, pszNames[i + 1], pszEncodedNames);
                        i18n_ucnv_destroy(hCnv);
                        return 1;
                }
                nRet = i18n_ucnv_destroy(hCnv);
                PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));
        }

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_get_ccsid_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_get_ccsid
 * @apicovered          i18n_ucnv_get_ccsid
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_get_ccsid
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_get_ccsid
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_get_ccsid_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        int32_t SrcCcsid[] = { 37, 850, 943, 949, 950, 1047, 1252, 1392, 33722 };
        int nCount = sizeof(SrcCcsid)/sizeof(SrcCcsid[0]);
        int i;
        int32_t ObtainedCcsid = 0;
        i18n_ucnv_h hCnv = NULL;


        for(i = 0; i < nCount; i++)
        {
                ObtainedCcsid = 0;
                hCnv = NULL;

                nRet = i18n_ucnv_create_ccsid(SrcCcsid[i], I18N_UCNV_IBM, &hCnv);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create_ccsid", BaseUtilsGetError(nRet));
                CHECK_HANDLE(hCnv, "i18n_ucnv_create_ccsid");

                //Target API
                nRet = i18n_ucnv_get_ccsid(hCnv, &ObtainedCcsid);
                PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_ccsid", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));
                PRINT_RESULT_CLEANUP(SrcCcsid[i], ObtainedCcsid, "i18n_ucnv_get_ccsid", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

                nRet = i18n_ucnv_destroy(hCnv);
                PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        }

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_get_platform_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget	        i18n_ucnv_get_platform
 * @apicovered          i18n_ucnv_get_platform
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_get_platform
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_get_platform
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_get_platform_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = "utf-8";
        i18n_ucnv_platform_e platform;

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
	nRet = i18n_ucnv_get_platform(hCnv, &platform);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_platform", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));
	PRINT_RESULT_CLEANUP(platform, I18N_UCNV_IBM, "i18n_ucnv_get_platform", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_get_type_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_get_type
 * @apicovered          i18n_ucnv_get_type
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_get_type
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_get_type
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_get_type_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = "utf-8";
        i18n_ucnv_type_e type;

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
	nRet = i18n_ucnv_get_type(hCnv, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_type", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));
	PRINT_RESULT_CLEANUP(type, I18N_UCNV_UTF8, "i18n_ucnv_get_type", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_get_starters_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_get_starters
 * @apicovered          i18n_ucnv_get_starters
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_get_starters
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_get_starters
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_get_starters_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = "ksc";
        i18n_ubool starters[I18N_UCHAR_CAPACITY];

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
	nRet = i18n_ucnv_get_starters(hCnv, starters);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_starters", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_get_unicode_set_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_get_unicode_set
 * @apicovered          i18n_ucnv_get_unicode_set
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_get_unicode_set
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_get_unicode_set
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_get_unicode_set_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_uset_h hSet = NULL;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = "ksc";

	nRet = i18n_uset_create(1, 0, &hSet);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_uset_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hSet, "i18n_uset_create");

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_get_unicode_set(hCnv, hSet, I18N_UCNV_ROUNDTRIP_SET);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_unicode_set", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_from_unicode_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_from_unicode
 * @apicovered          i18n_ucnv_from_unicode
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_from_unicode
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_from_unicode
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_from_unicode_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        const char *pszConv = "UTF-8";
        i18n_ucnv_h hCnv = NULL;
        char szBuffer[2] = {1, 1};
	i18n_uchar szUcharBuffer[2] = {2, 2};
	char *pszChars = szBuffer;
	i18n_uchar *pszUchars = (i18n_uchar *)szUcharBuffer;
	i18n_uchar *pszUcharsBad = (i18n_uchar *)(szUcharBuffer + 1);

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_from_unicode(hCnv, &pszChars, pszChars, (const i18n_uchar **)&pszUchars, pszUchars, NULL, true);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_from_unicode", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_to_unicode_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_to_unicode
 * @apicovered          i18n_ucnv_to_unicode
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_to_unicode
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_to_unicode
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_to_unicode_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        const char *pszConv = "UTF-8";
        i18n_ucnv_h hCnv = NULL;
        char szBuffer[2] = {1, 1};
	i18n_uchar szUcharBuffer[2] = {2, 2};
	char *pszChars = szBuffer;
	i18n_uchar *pszUchars = (i18n_uchar *)szUcharBuffer;
	i18n_uchar *pszUcharsBad = (i18n_uchar *)(szUcharBuffer + 1);

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_to_unicode(hCnv, &pszUchars, pszUchars, (const i18n_uchar **)&pszChars, pszChars, NULL, true);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_to_unicode", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_from_uchars_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_from_uchars
 * @apicovered          i18n_ucnv_from_uchars
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_from_uchars
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_from_uchars
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_from_uchars_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = "UTF-16";
        static const i18n_uchar szSrc[1] = {0xd900};
	char szBuffer[I18N_UCHAR_CAPACITY];
	int32_t ObtainedLength = -1;
        int32_t ExpectedLength = 4;

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_from_uchars(hCnv, szBuffer, I18N_UCHAR_CAPACITY, szSrc, 1, &ObtainedLength);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_from_uchars", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));
        PRINT_RESULT_CLEANUP(ExpectedLength, ObtainedLength, "i18n_ucnv_from_uchars", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_to_uchars_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_to_uchars
 * @apicovered          i18n_ucnv_to_uchars
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_to_uchars
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_to_uchars
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_to_uchars_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = "ibm-943";
        static const char szTarget[] = {
		0x5c, 0x75, 0x73, 0x72,
		0x5c, 0x6c, 0x6f, 0x63, 0x61, 0x6c,
		0x5c, 0x73, 0x68, 0x61, 0x72, 0x65,
		0x5c, 0x64, 0x61, 0x74, 0x61,
		0x5c, 0x69, 0x63, 0x75, 0x74, 0x65, 0x73, 0x74, 0x2e, 0x74, 0x78, 0x74,
		0
	};

	i18n_uchar szResult[I18N_UCHAR_CAPACITY];
	int32_t ObtainedLength = -1;

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_to_uchars(hCnv, szResult, I18N_UCHAR_CAPACITY, szTarget, (int32_t)strlen(szTarget), &ObtainedLength);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_to_uchars", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));
        if(ObtainedLength < 0)
        {
                FPRINTF("\\n[Line : %d][%s] i18n_ucnv_to_uchars failed ,ObtainedLength is not correct \n", __LINE__, API_NAMESPACE);
                i18n_ucnv_destroy(hCnv);
                return 1;
        }

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));
        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_get_next_uchar_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget	        i18n_ucnv_get_next_uchar
 * @apicovered          i18n_ucnv_get_next_uchar
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_get_next_uchar
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_get_next_uchar
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_get_next_uchar_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = "ibm-1363";
        const char szSrcData[] = { (char)0xa2, (char)0xae, (char)0xa2 };
	const char *pszSrc = szSrcData;
	const char *pszSrcLimit = szSrcData + sizeof(szSrcData);
	i18n_uchar32 result1, result2, result3;

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_get_next_uchar(hCnv, &pszSrc, pszSrcLimit, &result1);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_next_uchar", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));
	PRINT_RESULT_CLEANUP(0xa1, result1, "i18n_ucnv_get_next_uchar", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        //Target API
        nRet = i18n_ucnv_get_next_uchar(hCnv, &pszSrc, pszSrcLimit, &result2);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_next_uchar", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));
	PRINT_RESULT_CLEANUP(0x1a, result2, "i18n_ucnv_get_next_uchar", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));
        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_convert_ex_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_convert_ex
 * @apicovered          i18n_ucnv_convert_ex
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_convert_ex
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_convert_ex
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_convert_ex_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv1 = NULL;
        i18n_ucnv_h hCnv2 = NULL;
        const char *pszConv1 = "UTF-8";
        const char *pszConv2 = "Shift-JIS";
        char szTargetBuffer[I18N_UCHAR_CAPACITY];
        char szSrcBuffer[I18N_UCHAR_CAPACITY];
	char *pszTarget = szTargetBuffer;
	const char *pszSrc = szSrcBuffer;

        nRet = i18n_ucnv_create(pszConv1, &hCnv1);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv1, "i18n_ucnv_create");

        nRet = i18n_ucnv_create(pszConv2, &hCnv2);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv2));
        CHECK_HANDLE_CLEANUP(hCnv2, "i18n_ucnv_create", i18n_ucnv_destroy(hCnv2));

        //Target API
        nRet = i18n_ucnv_convert_ex(hCnv2, hCnv1, &pszTarget, szTargetBuffer + sizeof(szTargetBuffer), &pszSrc, NULL, NULL, NULL, NULL, NULL, true, true);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_convert_ex", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv2); i18n_ucnv_destroy(hCnv1));

        nRet = i18n_ucnv_destroy(hCnv2);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        nRet = i18n_ucnv_destroy(hCnv1);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));
        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_convert_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_convert
 * @apicovered          i18n_ucnv_convert
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_convert
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_convert
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_convert_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        int32_t target_limit = 0, source_limit = 0, target_capacity = 0;
        const uint8_t szSrc[]={ 0x00, 0x04, 0x05, 0x06, 0xa2, 0xb4, 0x00};
	const uint8_t szExpectedTarget[]={ 0x00, 0x37, 0x2d, 0x2e, 0x0e, 0x49, 0x62, 0x0f, 0x00};
	char *pszTarget = NULL;
        source_limit = sizeof(szSrc)/sizeof(szSrc[0]);
        int i = 0;

        nRet = i18n_ucnv_convert("ibm-1364", "ibm-1363", NULL, target_limit, (const char*)szSrc, source_limit, &target_capacity);
        if(nRet == I18N_ERROR_BUFFER_OVERFLOW) {
		target_limit = target_capacity + 1;
		pszTarget = (char *)malloc(sizeof(char) *target_limit);
		nRet = i18n_ucnv_convert("ibm-1364", "ibm-1363", pszTarget, target_limit, (const char*)szSrc, source_limit, &target_capacity);
	}

        if(pszTarget != NULL)
        {
                PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_convert", BaseUtilsGetError(nRet), FREE_MEMORY(pszTarget));
                for(i = 0; i < target_capacity; ++i)
                        PRINT_RESULT_CLEANUP(pszTarget[i], szExpectedTarget[i], "i18n_ucnv_convert", "obtained and expected values are not correct", FREE_MEMORY(pszTarget));
                FREE_MEMORY(pszTarget);
        }
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_convert", BaseUtilsGetError(nRet));
        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_from_algorithmic_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_from_algorithmic
 * @apicovered          i18n_ucnv_from_algorithmic
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_from_algorithmic
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_from_algorithmic
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_from_algorithmic_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        static const uint8_t
		utf8[]={
			/* 4e00 		  30a1				ff61			  0410 */
			0xe4, 0xb8, 0x80, 0xe3, 0x82, 0xa1, 0xef, 0xbd, 0xa1, 0xd0, 0x90
		},
		shiftJIS[]={
			0x88, 0xea, 0x83, 0x40, 0xa1, 0x84, 0x40
		};

	int32_t length = -1;
	char szTarget[I18N_UCHAR_CAPACITY];
        const char *pszConv = "shift-JIS";

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_from_algorithmic(hCnv, I18N_UCNV_UTF8, szTarget, sizeof(shiftJIS), (const char *)utf8, sizeof(utf8), &length);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_from_algorithmic", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));
        PRINT_RESULT_CLEANUP(length, sizeof(shiftJIS), "i18n_ucnv_from_algorithmic", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));
        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_to_algorithmic_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_to_algorithmic
 * @apicovered          i18n_ucnv_to_algorithmic
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_to_algorithmic
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_to_algorithmic
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_to_algorithmic_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        static const uint8_t
		utf8[]={
			/* 4e00 		  30a1				ff61			  0410 */
			0xe4, 0xb8, 0x80, 0xe3, 0x82, 0xa1, 0xef, 0xbd, 0xa1, 0xd0, 0x90
		},
		shiftJIS[]={
			0x88, 0xea, 0x83, 0x40, 0xa1, 0x84, 0x40
		};

	int32_t length;
	char szTarget[I18N_UCHAR_CAPACITY];
        char szShiftJIS[I18N_UCHAR_CAPACITY];
        const char *pszConv = "shift-JIS";

        memcpy(szShiftJIS, shiftJIS, sizeof(shiftJIS));
	szShiftJIS[sizeof(shiftJIS)] = 0;
        memset(szTarget, 0x55, sizeof(szTarget));

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_to_algorithmic(I18N_UCNV_UTF8, hCnv, szTarget, sizeof(szTarget), szShiftJIS, -1, &length);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_to_algorithmic", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));
        PRINT_RESULT_CLEANUP(length, sizeof(utf8), "i18n_ucnv_to_algorithmic", "obtained and expected length are different", i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_flush_cache_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_flush_cache
 * @apicovered          i18n_ucnv_flush_cache
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_flush_cache
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_flush_cache
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_flush_cache_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hConverters[4];
        const char *pszConv1 = "ibm-1047";
        const char *pszConv2 = "ibm-954";
        i18n_ucnv_flush_cache();

        nRet = i18n_ucnv_create(pszConv1, &hConverters[0]);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hConverters[0], "i18n_ucnv_create");

        nRet = i18n_ucnv_create(pszConv1, &hConverters[1]);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hConverters[0]));
        CHECK_HANDLE_CLEANUP(hConverters[1], "i18n_ucnv_create", i18n_ucnv_destroy(hConverters[0]));

        nRet = i18n_ucnv_create(pszConv1, &hConverters[2]);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hConverters[0]); i18n_ucnv_destroy(hConverters[1]));
        CHECK_HANDLE_CLEANUP(hConverters[2], "i18n_ucnv_create", i18n_ucnv_destroy(hConverters[0]); i18n_ucnv_destroy(hConverters[1]));

        nRet = i18n_ucnv_create(pszConv2, &hConverters[3]);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hConverters[0]); i18n_ucnv_destroy(hConverters[1]));
        CHECK_HANDLE_CLEANUP(hConverters[3], "i18n_ucnv_create", i18n_ucnv_destroy(hConverters[0]); i18n_ucnv_destroy(hConverters[1]); i18n_ucnv_destroy(hConverters[2]));

        nRet = i18n_ucnv_flush_cache();
        PRINT_RESULT_CLEANUP(nRet, 0, "i18n_ucnv_flush_cache", "value obtained is not correct", i18n_ucnv_destroy(hConverters[0]); i18n_ucnv_destroy(hConverters[1]); i18n_ucnv_destroy(hConverters[2]); i18n_ucnv_destroy(hConverters[3]));

        nRet = i18n_ucnv_destroy(hConverters[0]);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        nRet = i18n_ucnv_destroy(hConverters[1]);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        nRet = i18n_ucnv_flush_cache();
        PRINT_RESULT_CLEANUP(nRet, 0, "i18n_ucnv_flush_cache", "value obtained is not correct", i18n_ucnv_destroy(hConverters[2]); i18n_ucnv_destroy(hConverters[3]));

        nRet = i18n_ucnv_destroy(hConverters[2]);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        nRet = i18n_ucnv_destroy(hConverters[3]);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_count_available_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_count_available
 * @apicovered          i18n_ucnv_count_available, i18n_ucnv_get_available_name
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_count_available, i18n_ucnv_get_available_name
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_count_available, i18n_ucnv_get_available_name
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_count_available_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        int count = 0;
        int i = 0;
        const char *pszName = NULL;

        //Target API
        count = i18n_ucnv_count_available();
        if(count < 0)
        {
                FPRINTF("\\n[Line : %d][%s] i18n_ucnv_count_available failed ,return number is not correct \n", __LINE__, API_NAMESPACE);
                return 1;
        }
        for(i = 0; i < count; i++)
        {
                nRet = i18n_ucnv_get_available_name(i, &pszName);
                PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_available_name", BaseUtilsGetError(nRet));
                CHECK_HANDLE(pszName, "i18n_ucnv_get_available_name");
        }
        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_get_available_name_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_get_available_name
 * @apicovered          i18n_ucnv_get_available_name
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_get_available_name
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_get_available_name
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_get_available_name_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        const char *pszName = NULL;

        //Target API
        nRet = i18n_ucnv_get_available_name(1, &pszName);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_available_name", BaseUtilsGetError(nRet));
        CHECK_HANDLE(pszName, "i18n_ucnv_get_available_name");

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_create_all_names_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_create_all_names
 * @apicovered          i18n_ucnv_create_all_names
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_create_all_names
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_create_all_names
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_create_all_names_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_uenumeration_h hEnumeration = NULL;

        //Target API
        nRet = i18n_ucnv_create_all_names(&hEnumeration);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create_all_names", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hEnumeration, "i18n_ucnv_create_all_names");

        nRet = i18n_uenumeration_destroy(hEnumeration);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uenumeration_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_count_aliases_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget	        i18n_ucnv_count_aliases
 * @apicovered          i18n_ucnv_count_aliases
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_count_aliases
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_count_aliases
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_count_aliases_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        const char *pszAlias = "utf-8";
        uint16_t number = -1;

        //Target API
        nRet = i18n_ucnv_count_aliases(pszAlias, &number);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_count_aliases", BaseUtilsGetError(nRet));
        if(number < 0)
        {
                FPRINTF("\\n[Line : %d][%s] i18n_ucnv_count_aliases failed ,return number is not correct \n", __LINE__, API_NAMESPACE);
                return 1;
        }

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_get_aliases_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_get_aliases
 * @apicovered          i18n_ucnv_get_aliases
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_get_aliases
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_get_aliases
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_get_aliases_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszAlias = "utf-8";
	uint16_t number = -1;
	const char **pszAliases;
	pszAliases = (const char **)malloc(number * sizeof(const char *));

	nRet = i18n_ucnv_count_aliases(pszAlias, &number);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_count_aliases", BaseUtilsGetError(nRet), FREE_MEMORY(pszAliases));
	if(number < 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ucnv_count_aliases failed ,return number is not correct \n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszAliases);
		return 1;
	}

	//Target API
	nRet = i18n_ucnv_get_aliases(pszAlias, pszAliases);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_aliases", BaseUtilsGetError(nRet), FREE_MEMORY(pszAliases));

	FREE_MEMORY(pszAliases);

	return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_get_alias_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_get_alias
 * @apicovered          i18n_ucnv_get_alias
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_get_alias
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_get_alias
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_get_alias_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        const char *pszAlias = "utf-8";
        uint16_t number = -1;
        const char **pszAliases;

        const char *pszCheckAlias = NULL;
        uint16_t i = 0;

        nRet = i18n_ucnv_count_aliases(pszAlias, &number);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_count_aliases", BaseUtilsGetError(nRet));
        if(number < 0)
        {
                FPRINTF("\\n[Line : %d][%s] i18n_ucnv_count_aliases failed ,return number is not correct \n", __LINE__, API_NAMESPACE);
                return 1;
        }

        pszAliases = (const char **)malloc(number * sizeof(const char *));

        nRet = i18n_ucnv_get_aliases(pszAlias, pszAliases);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_aliases", BaseUtilsGetError(nRet), FREE_MEMORY(pszAliases));

	for(i = 0; i < number; ++i)
        {
                pszCheckAlias = NULL;

                //Target API
		nRet = i18n_ucnv_get_alias(pszAlias, i, &pszCheckAlias);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_alias", BaseUtilsGetError(nRet), FREE_MEMORY(pszAliases));
                CHECK_HANDLE_CLEANUP(pszCheckAlias, "i18n_ucnv_get_alias", FREE_MEMORY(pszAliases));
                if(strncmp(pszAliases[i], pszCheckAlias, strlen(pszAliases[i])) != 0)
                {
                        FPRINTF("[Line : %d][%s] i18n_ucnv_get_alias mismatch. pszAliases[i] = %s, pszCheckAlias = %s\\n", __LINE__, API_NAMESPACE, pszAliases[i], pszCheckAlias);
                        FREE_MEMORY(pszAliases);
                        return 1;
                }
	}
        FREE_MEMORY(pszAliases);
        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_create_standard_names_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_create_standard_names
 * @apicovered          i18n_ucnv_create_standard_names
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_create_standard_names
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_create_standard_names
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_create_standard_names_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        const char *pszConv = "ASCII";
        const char *pszStandard = "IANA";
        i18n_uenumeration_h hEnumeration = NULL;

        //Target API
        nRet = i18n_ucnv_create_standard_names(pszConv, pszStandard, &hEnumeration);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create_standard_names", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_count_standards_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_count_standards
 * @apicovered          i18n_ucnv_count_standards
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_count_standards
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_count_standards
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_count_standards_p(void)
{
        START_TEST_PRINT;

        uint16_t count = -1;

        //Target API
        count = i18n_ucnv_count_standards();

        if(count < 0)
        {
                FPRINTF("\\n[Line : %d][%s] i18n_ucnv_count_standards failed ,return value is not correct \n", __LINE__, API_NAMESPACE);
                return 1;
        }

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_get_standard_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_get_standard
 * @apicovered          i18n_ucnv_get_standard
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_get_standard
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_get_standard
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_get_standard_p(void)
{
        START_TEST_PRINT;

        uint16_t count = -1;
        int i = 0;
        const char *pszStandard = NULL;
        int nRet = -1;
        count = i18n_ucnv_count_standards();

        if(count < 0)
        {
                FPRINTF("\\n[Line : %d][%s] i18n_ucnv_count_standards failed ,return value is not correct \n", __LINE__, API_NAMESPACE);
                return 1;
        }
        for(i = 0; i < count -1; ++i)
        {
		pszStandard = NULL;
                //Target API
		nRet = i18n_ucnv_get_standard(i, &pszStandard);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_standard", BaseUtilsGetError(nRet));
                CHECK_HANDLE(pszStandard, "i18n_ucnv_get_standard");
	}
        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_get_standard_name_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_get_standard_names
 * @apicovered          i18n_ucnv_get_standard_names
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_get_standard_names
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_get_standard_names
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_get_standard_name_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        const char *pszConv = "ASCII";
        const char *pszStandard = "IANA";
        const char *pszTag = NULL;
        const char *pszExpected = "ANSI_X3.4-1968";

        //Target API
        nRet = i18n_ucnv_get_standard_name(pszConv, pszStandard, &pszTag);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_standard_name", BaseUtilsGetError(nRet));
        CHECK_HANDLE(pszTag, "i18n_ucnv_get_standard_name");

        if(strncmp(pszExpected, pszTag, strlen(pszExpected)) != 0)
        {
                FPRINTF("[Line : %d][%s] i18n_ucnv_get_standard_name mismatch. pszExpected = %s, pszTag = %s\\n", __LINE__, API_NAMESPACE, pszExpected, pszTag);
                return 1;
        }
        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_get_canonical_name_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_get_canonical_name
 * @apicovered          i18n_ucnv_get_canonical_name
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_get_canonical_name
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_get_canonical_name
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_get_canonical_name_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        const char *pszConv = "UTF-8";
        const char *pszStandard = "IANA";
        const char *pszTag = NULL;
        const char *pszExpected = "UTF-8";

        //Target API
        nRet = i18n_ucnv_get_canonical_name(pszConv, pszStandard, &pszTag);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_get_canonical_name", BaseUtilsGetError(nRet));
        CHECK_HANDLE(pszTag, "i18n_ucnv_get_canonical_name");

        if(strncmp(pszExpected, pszTag, strlen(pszExpected)) != 0)
        {
                FPRINTF("[Line : %d][%s] i18n_ucnv_get_standard_names mismatch. pszExpected = %s, pszTag = %s\\n", __LINE__, API_NAMESPACE, pszExpected, pszTag);
                return 1;
        }
        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_set_get_default_name_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_set_default_name, i18n_ucnv_get_default_name
 * @apicovered          i18n_ucnv_set_default_name, i18n_ucnv_get_default_name
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_set_default_name, i18n_ucnv_get_default_name
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_set_default_name, i18n_ucnv_get_default_name
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_set_get_default_name_p(void)
{
        START_TEST_PRINT;

        const char *pszName = "UTF-8";
        const char *pszGetName = NULL;
        //Target API
        i18n_ucnv_set_default_name(pszName);

        //Target API
	pszGetName = i18n_ucnv_get_default_name();
	if(strncmp(pszName, pszGetName, strlen(pszName)) != 0)
        {
                FPRINTF("[Line : %d][%s] i18n_ucnv_get_default_name mismatch. pszName = %s, pszExpectedName = %s\\n", __LINE__, API_NAMESPACE, pszName, pszGetName);
                return 1;
        }
        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_fix_file_separator_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_fix_file_separator
 * @apicovered          i18n_ucnv_create, i18n_ucnv_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_fix_file_separator
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_fix_file_separator
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_fix_file_separator_p(void)
{
        START_TEST_PRINT;

        static const char szTarget[] = {
		0x5c, 0x75, 0x73, 0x72,
		0x5c, 0x6c, 0x6f, 0x63, 0x61, 0x6c,
		0x5c, 0x73, 0x68, 0x61, 0x72, 0x65,
		0x5c, 0x64, 0x61, 0x74, 0x61,
		0x5c, 0x69, 0x63, 0x75, 0x74, 0x65, 0x73, 0x74, 0x2e, 0x74, 0x78, 0x74,
		0
	};
        i18n_uchar szResult[I18N_UCHAR_CAPACITY];
        i18n_uchar szAsciiResult[I18N_UCHAR_CAPACITY];
	int32_t len = -1;
        int32_t ascii_len = -1;
        const char *pszConv1 = "ibm-943";
        const char *pszConv2 = "LATIN-1";
        i18n_ucnv_h hCnv1 = NULL;
        i18n_ucnv_h hCnv2 = NULL;
        int nRet = -1;

        nRet = i18n_ucnv_create(pszConv1, &hCnv1);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv1, "i18n_ucnv_create");

        nRet = i18n_ucnv_create(pszConv2, &hCnv2);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv2));
        CHECK_HANDLE_CLEANUP(hCnv2, "i18n_ucnv_create", i18n_ucnv_destroy(hCnv1));

        nRet = i18n_ucnv_to_uchars(hCnv1, szResult, I18N_UCHAR_CAPACITY, szTarget, (int32_t)strlen(szTarget), &len);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_to_uchars", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv2); i18n_ucnv_destroy(hCnv1));

        nRet = i18n_ucnv_to_uchars(hCnv2, szAsciiResult, I18N_UCHAR_CAPACITY, szTarget, (int32_t)strlen(szTarget), &ascii_len);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_to_uchars", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv2); i18n_ucnv_destroy(hCnv1));

        //Target API
        nRet = i18n_ucnv_fix_file_separator(hCnv1, szResult, len);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_fix_file_separator", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv2); i18n_ucnv_destroy(hCnv1));
        PRINT_RESULT_CLEANUP(i18n_ustring_compare(szResult, szAsciiResult), 0, "i18n_ucnv_fix_file_separator", "values are not equal", i18n_ucnv_destroy(hCnv2); i18n_ucnv_destroy(hCnv1));

        nRet = i18n_ucnv_destroy(hCnv2);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        nRet = i18n_ucnv_destroy(hCnv1);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_is_ambiguous_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_create, i18n_ucnv_is_ambiguous
 * @apicovered          i18n_ucnv_create, i18n_ucnv_is_ambiguous
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_create, i18n_ucnv_is_ambiguous
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_create, i18n_ucnv_is_ambiguous
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_is_ambiguous_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = "UTF-8";
        i18n_ubool bAmbiguous = false;

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_is_ambiguous(hCnv, &bAmbiguous);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_is_ambiguous", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_set_fallback_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_set_fallback
 * @apicovered          i18n_ucnv_create, i18n_ucnv_set_fallback
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_create, i18n_ucnv_set_fallback
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_create, i18n_ucnv_set_fallback
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_set_fallback_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = "ibm-1371";
        i18n_ubool bResult = false;

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        //Target API
        nRet = i18n_ucnv_set_fallback(hCnv, true);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_set_fallback", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_uses_fallback(hCnv, &bResult);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_uses_fallback", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));
        PRINT_RESULT_CLEANUP(true, bResult, "i18n_ucnv_uses_fallback", "value is not correct", i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_uses_fallback_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_uses_fallback
 * @apicovered          i18n_ucnv_create, i18n_ucnv_uses_fallback
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_create, i18n_ucnv_uses_fallback
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_create, i18n_ucnv_uses_fallback
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_uses_fallback_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = "ibm-1371";
        i18n_ubool bResult = false;

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        nRet = i18n_ucnv_set_fallback(hCnv, true);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_set_fallback", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

        //Target API
        nRet = i18n_ucnv_uses_fallback(hCnv, &bResult);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_uses_fallback", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));
        PRINT_RESULT_CLEANUP(true, bResult, "i18n_ucnv_uses_fallback", "value is not correct", i18n_ucnv_destroy(hCnv));

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_detect_unicode_signature_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_detect_unicode_signature_p
 * @apicovered          ITc_i18n_ucnv_detect_unicode_signature_p
 * @passcase		I18N_ERROR_NONE returned by ITc_i18n_ucnv_detect_unicode_signature_p
 * @failcase		I18N_ERROR_NONE not returned by ITc_i18n_ucnv_detect_unicode_signature_p
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_detect_unicode_signature_p(void)
{
        START_TEST_PRINT;

        static const char* pszData[] = {
		"\xFE\xFF\x00\x00", 	/* UTF-16BE */
		"\xFF\xFE\x00\x00", 	/* UTF-16LE */
		"\xEF\xBB\xBF\x00", 	/* UTF-8	*/
		"\x0E\xFE\xFF\x00", 	/* SCSU 	*/

		"\xFE\xFF", 			/* UTF-16BE */
		"\xFF\xFE", 			/* UTF-16LE */
		"\xEF\xBB\xBF", 		/* UTF-8	*/
		"\x0E\xFE\xFF", 		/* SCSU 	*/

		"\xFE\xFF\x41\x42", 	/* UTF-16BE */
		"\xFF\xFE\x41\x41", 	/* UTF-16LE */
		"\xEF\xBB\xBF\x41", 	/* UTF-8	*/
		"\x0E\xFE\xFF\x41", 	/* SCSU 	*/

		"\x2B\x2F\x76\x38\x2D", /* UTF-7	*/
		"\x2B\x2F\x76\x38\x41", /* UTF-7	*/
		"\x2B\x2F\x76\x39\x41", /* UTF-7	*/
		"\x2B\x2F\x76\x2B\x41", /* UTF-7	*/
		"\x2B\x2F\x76\x2F\x41",  /* UTF-7	 */

		"\xDD\x73\x66\x73"		/* UTF-EBCDIC */
	};

	static const char* pszExpected[] = {
		"UTF-16BE",
		"UTF-16LE",
		"UTF-8",
		"SCSU",

		"UTF-16BE",
		"UTF-16LE",
		"UTF-8",
		"SCSU",

		"UTF-16BE",
		"UTF-16LE",
		"UTF-8",
		"SCSU",

		"UTF-7",
		"UTF-7",
		"UTF-7",
		"UTF-7",
		"UTF-7",

		"UTF-EBCDIC"
	};

	static const int32_t expected_len[] =
        {
		2, 2, 3, 3,
		2, 2, 3, 3,
		2, 2, 3, 3,
		5, 4, 4, 4, 4,
		4
	};
        int nRet = -1;
	const char *pszSrc = NULL;
        const char *pszName = NULL;
	int32_t signature_length = -1;
        int nCount = sizeof(pszData)/sizeof(pszData[0]);
        int i = 0;

        for(i = 0; i < nCount; ++i)
        {
		pszSrc = pszData[i];
                pszName = NULL;

                //Target API
		nRet = i18n_ucnv_detect_unicode_signature(pszSrc, -1, &signature_length, &pszName);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_detect_unicode_signature", BaseUtilsGetError(nRet));
                CHECK_HANDLE(pszName, "i18n_ucnv_detect_unicode_signature");
		PRINT_RESULT(signature_length, expected_len[i], "i18n_ucnv_detect_unicode_signature", "obtained and expected length are not same");
                if(strncmp(pszName, pszExpected[i], strlen(pszName)) != 0)
                {
                        FPRINTF("[Line : %d][%s] i18n_ucnv_get_name mismatch. pszExpected = %s, pszName = %s\\n", __LINE__, API_NAMESPACE, pszExpected[i], pszName);
                        return 1;
                }
	}

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_from_ucount_pending_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget	        i18n_ucnv_from_ucount_pending
 * @apicovered          i18n_ucnv_from_ucount_pending
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_from_ucount_pending
 * @failcase		I18N_ERROR_NONE not returned i18n_ucnv_from_ucount_pending
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_from_ucount_pending_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        static const struct {
		i18n_uchar input[6];
		int32_t len;
		int32_t exp;
	}from_unicode_tests[] = {
		{{ 0xdbc4},1,1},
		{{ 0xdbc4, 0xde34, 0xd84d},3,1},
	};

        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = "UTF-8";
        char *pszTarget = NULL;
        char *pszTargetLimit = NULL;
        const i18n_uchar *pszSource = NULL;
        const i18n_uchar *pszSourceLimit = NULL;

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        int nCount = 2;
        int i = 0;
        int32_t len = 0;

        for(i = 0; i < nCount; i++)
        {
                char sztgt[10];
		pszTarget = sztgt;
		pszTargetLimit = pszTarget + 10;
		pszSource = from_unicode_tests[i].input;
		pszSourceLimit = pszSource + from_unicode_tests[i].len;
		len = 0;


		nRet = i18n_ucnv_from_unicode(hCnv, &pszTarget, pszTargetLimit, &pszSource, pszSourceLimit, NULL, false);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_from_unicode", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

                //Target API
		nRet = i18n_ucnv_from_ucount_pending(hCnv, &len);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_from_ucount_pending", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));
		PRINT_RESULT_CLEANUP(len, from_unicode_tests[i].exp, "i18n_ucnv_from_ucount_pending", "obtained and expected length are not equal", i18n_ucnv_destroy(hCnv));
        }

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_to_ucount_pending_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_to_ucount_pending
 * @apicovered          i18n_ucnv_to_ucount_pending
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_to_ucount_pending
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_to_ucount_pending
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_to_ucount_pending_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        static const struct {
		char input[6];
		int32_t len;
		int32_t exp;
	}to_unicode_tests[] = {
		{{0x05, 0x01, 0x02},3,3},
		{{0x01, 0x02},2,2},
		{{0x07,  0x00, 0x01, 0x02},4,4},
	};

        i18n_ucnv_h hCnv = NULL;
        const char *pszConv = "UTF-8";
        char *pszTarget = NULL;
        char *pszTargetLimit = NULL;
        const i18n_uchar *pszSource = NULL;
        const i18n_uchar *pszSourceLimit = NULL;

        nRet = i18n_ucnv_create(pszConv, &hCnv);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(hCnv, "i18n_ucnv_create");

        int nCount = 3;
        int i = 0;
        int32_t len = 0;

        for(i = 0; i < nCount; i++)
        {
                i18n_uchar sztgt[10];
		pszTarget = sztgt;
		pszTargetLimit = pszTarget + 10;
		pszSource = to_unicode_tests[i].input;
		pszSourceLimit = pszSource + to_unicode_tests[i].len;
		len = 0;

		nRet = i18n_ucnv_from_unicode(hCnv, &pszTarget, pszTargetLimit, &pszSource, pszSourceLimit, NULL, false);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_from_unicode", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));

                //Target API
		nRet = i18n_ucnv_to_ucount_pending(hCnv, &len);
                PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_from_ucount_pending", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));
       }

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnv_is_fixed_width_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnv_is_fixed_width
 * @apicovered          i18n_ucnv_create, i18n_ucnv_is_fixed_width
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnv_create, i18n_ucnv_is_fixed_width
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnv_create, i18n_ucnv_is_fixed_width
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnv_is_fixed_width_p(void)
{
        START_TEST_PRINT;

        int nRet = -1;
        const char *szFixedWidth[] = {
		"US-ASCII",
		"UTF32",
		"ibm-5478_P100-1995"
	};

	const char *szNotFixedWidth[] = {
		"GB18030",
		"UTF8",
		"windows-949-2000",
		"UTF16"
	};
        i18n_ubool bResult = false;
        i18n_ucnv_h hCnv = NULL;
        int nCount1 = 3;
        int nCount2 = 4;
        int i = 0;

	for(i = 0; i < nCount1; ++i)
        {
                hCnv = NULL;
                bResult = false;
		nRet = i18n_ucnv_create(szFixedWidth[i], &hCnv);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
                CHECK_HANDLE(hCnv, "i18n_ucnv_create");

                //Target API
		nRet = i18n_ucnv_is_fixed_width(hCnv, &bResult);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_is_fixed_width", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));
	        PRINT_RESULT_CLEANUP(true, bResult, "i18n_ucnv_is_fixed_width", "result is not correct", i18n_ucnv_destroy(hCnv));
	}

	for(i = 0; i < nCount2; ++i)
        {
                hCnv = NULL;
                bResult = true;
		nRet = i18n_ucnv_create(szNotFixedWidth[i], &hCnv);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnv_create", BaseUtilsGetError(nRet));
                CHECK_HANDLE(hCnv, "i18n_ucnv_create");

                //Target API
		nRet = i18n_ucnv_is_fixed_width(hCnv, &bResult);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnv_is_fixed_width", BaseUtilsGetError(nRet), i18n_ucnv_destroy(hCnv));
	        PRINT_RESULT_CLEANUP(false, bResult, "i18n_ucnv_is_fixed_width", "result is not correct", i18n_ucnv_destroy(hCnv));
	}

        nRet = i18n_ucnv_destroy(hCnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));
	return 0;
}
