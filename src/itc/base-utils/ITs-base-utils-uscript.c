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
* @function 		ITs_base_utils_uscript_startup
* @description	 	Called before each test
* @parameter		NA
* @return 	        NA
*/
void ITs_base_utils_uscript_startup(void)
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
* @function 		ITs_base_utils_uscript_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 	        NA
*/
void ITs_base_utils_uscript_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

/*
 * @testcase		ITc_i18n_uscript_get_codes_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		gets codes related to parameter language
 * @apitarget		i18n_uscript_get_codes
 * @apicovered		i18n_uscript_get_codes
 * @passcase		I18N_ERROR_NONE returned by i18n_uscript_get_codes
 * @failcase		I18N_ERROR_NONE not returned by i18n_uscript_get_codes
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uscript_get_codes_p(void)
{
        START_TEST_PRINT;
        i18n_uscript_code_e KOREAN[2] = { I18N_USCRIPT_HANGUL, I18N_USCRIPT_HAN };
        i18n_uscript_code_e scripts[2];
        int32_t len = -1;
        const char* pszLanguage = "ko";
        int32_t capacity = 2;
        int nCount = 2;
        int nRet = -1;

        //Target API
        nRet = i18n_uscript_get_codes(pszLanguage, scripts, capacity, &len);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_uscript_get_codes", BaseUtilsGetError(nRet));
        if(len == -1)
        {
                FPRINTF("[Line : %d][%s] invalid length returned\\n", __LINE__, API_NAMESPACE);
                return 1;
        }

        int i;
        for(i = 0; i < nCount; i++)
        {
                PRINT_RESULT(KOREAN[i], scripts[i], "i18n_uscript_get_codes", "values obtained from api are not correct");
        }
        return 0;
}

/*
 * @testcase		ITc_i18n_uscript_get_name_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		gets uscript name as per parameter
 * @apitarget		i18n_uscript_get_name
 * @apicovered		i18n_uscript_get_name
 * @passcase		returned name matches the expected name
 * @failcase		returned name does not match the expected name
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uscript_get_name_p(void)
{
        START_TEST_PRINT;
        const char* pszName = NULL;

        //Target API
        pszName = i18n_uscript_get_name(I18N_USCRIPT_HANGUL);
        CHECK_HANDLE(pszName, "i18n_uscript_get_name");

        if(strncmp(pszName, "Hangul", strlen("Hangul")) != 0)
        {
                FPRINTF("[Line : %d][%s] returned string is nor correct\\n", __LINE__, API_NAMESPACE);
                return 1;
        }
        return 0;
}
/*
 * @testcase		ITc_i18n_uscript_get_short_name_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		gets uscript name as per parameter
 * @apitarget		i18n_uscript_get_short_name
 * @apicovered		i18n_uscript_get_short_name
 * @passcase		returned name matches the expected name
 * @failcase		returned name does not match the expected name
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uscript_get_short_name_p(void)
{
        START_TEST_PRINT;

        const char* pszName = NULL;

        //Target API
        pszName = i18n_uscript_get_short_name(I18N_USCRIPT_HANGUL);
        CHECK_HANDLE(pszName, "i18n_uscript_get_short_name");

        if(strncmp(pszName, "Hang", strlen("Hang")) != 0)
        {
                FPRINTF("[Line : %d][%s] returned string is not correct\\n", __LINE__, API_NAMESPACE);
                return 1;
        }
        return 0;
}
/*
 * @testcase		ITc_i18n_uscript_get_script_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		gets script according to the codepoints
 * @apitarget		i18n_uscript_get_script
 * @apicovered		i18n_uscript_get_script
 * @passcase		returned uscriptcode matches the expected uscriptcode
 * @failcase	        returned uscriptcode does not match the expected uscriptcode
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uscript_get_script_p(void)
{
        START_TEST_PRINT;
        i18n_uscript_code_e script_code = I18N_USCRIPT_INVALID_CODE;
        int nRet;

        uint32_t codepoints[] = {
		0x0000FFBE, /* I18N_USCRIPT_HANGUL*/
		0x0000FFCF, /* I18N_USCRIPT_HANGUL*/
		0x0000FFD7, /* I18N_USCRIPT_HANGUL*/
		0x0000FFDC, /* I18N_USCRIPT_HANGUL*/
		0x00010330, /* I18N_USCRIPT_GOTHIC*/
	};

	i18n_uscript_code_e expected[] = {
		I18N_USCRIPT_HANGUL,
		I18N_USCRIPT_HANGUL,
		I18N_USCRIPT_HANGUL,
		I18N_USCRIPT_HANGUL,
		I18N_USCRIPT_GOTHIC,
	};
        int nCounter;
        int nCountLimit = sizeof(expected)/sizeof(expected[0]);
        for(nCounter = 0; nCounter < nCountLimit; nCounter++)
        {
                //Target API
                nRet = i18n_uscript_get_script(codepoints[nCounter], &script_code);
                PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_uscript_get_script", BaseUtilsGetError(nRet));
                PRINT_RESULT(expected[nCounter], script_code, "i18n_uscript_get_script", "value obtained from api is wrong");
        }
        return 0;
}
/*
 * @testcase		ITc_i18n_uscript_has_script_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		checks whether uscript has script
 * @apitarget		i18n_uscript_has_script
 * @apicovered		i18n_uscript_has_script
 * @passcase		i18n_uscript_has_script is successful
 * @failcase            i18n_uscript_has_script is not successful
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uscript_has_script_p(void)
{
        START_TEST_PRINT;
        i18n_ubool bHasScript = false;
        bHasScript = i18n_uscript_has_script(0x063f, I18N_USCRIPT_ARABIC);
        PRINT_RESULT(true, bHasScript, "i18n_uscript_has_script", "uscript does not have script");
        return 0;
}
/*
 * @testcase		ITc_i18n_uscript_get_script_extensions_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls api based on codepoint
 * @apitarget		i18n_uscript_get_script_extensions
 * @apicovered		i18n_uscript_get_script_extensions
 * @passcase		I18N_ERROR_NONE returned by i18n_uscript_get_script_extensions
 * @failcase		I18N_ERROR_NONE not returned by i18n_uscript_get_script_extensions
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uscript_get_script_extensions_p(void)
{
        START_TEST_PRINT;
        i18n_uscript_code_e scripts[20];
	int32_t len = -1;
        int32_t capacity = 20;
        int nRet = -1;

	nRet = i18n_uscript_get_script_extensions(0x0640, scripts, capacity, &len);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_uscript_get_script_extensions", BaseUtilsGetError(nRet));
        if(len == -1)
        {
                FPRINTF("[Line : %d][%s] returned length is invalid\\n", __LINE__, API_NAMESPACE);
                return 1;
        }

	return 0;
}
/*
 * @testcase		ITc_i18n_uscript_get_sample_string_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_uscript_get_sample_string
 * @apicovered		i18n_uscript_get_sample_string
 * @passcase		I18N_ERROR_NONE returned by i18n_uscript_get_sample_string
 * @failcase		I18N_ERROR_NONE not returned by i18n_uscript_get_sample_string
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uscript_get_sample_string_p(void)
{
        START_TEST_PRINT;
        i18n_uchar sample[8];
	int32_t len = -1;
        int32_t capacity = 8;
        int nRet;
        nRet = i18n_uscript_get_sample_string(I18N_USCRIPT_LATIN, sample, capacity, &len);
        PRINT_RESULT(I18N_ERROR_NONE, nRet,  "i18n_uscript_get_sample_string", BaseUtilsGetError(nRet));
        if(len == -1)
        {
                FPRINTF("[Line : %d][%s] returned length is invalid\\n", __LINE__, API_NAMESPACE);
                return 1;
        }
        return 0;
}
/*
 * @testcase		ITc_i18n_uscript_get_usage_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		checks the usage of the given uscript
 * @apitarget		i18n_uscript_get_usage
 * @apicovered		i18n_uscript_get_usage
 * @passcase		i18n_uscript_get_usage is successful
 * @failcase		i18n_uscript_get_usage is not successful
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uscript_get_usage_p(void)
{
        START_TEST_PRINT;
        i18n_uscript_usage_e usage = i18n_uscript_get_usage(I18N_USCRIPT_KOREAN);
	PRINT_RESULT(usage, I18N_USCRIPT_USAGE_RECOMMENDED, "i18n_uscript_get_usage", "script usage is not recommended");
        return 0;
}
/*
 * @testcase		ITc_i18n_uscript_is_right_to_left_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		checks whether uscript is right to left or not
 * @apitarget		i18n_uscript_is_right_to_left
 * @apicovered		i18n_uscript_is_right_to_left
 * @passcase		i18n_uscript_is_right_to_left is successful
 * @failcase		i18n_uscript_is_right_to_left is not successful
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uscript_is_right_to_left_p(void)
{
        START_TEST_PRINT;
        i18n_ubool bIsRightToLeft = i18n_uscript_is_right_to_left(I18N_USCRIPT_KOREAN);
	PRINT_RESULT(bIsRightToLeft, false, "i18n_uscript_is_right_to_left", "answer is not correct");

	bIsRightToLeft = i18n_uscript_is_right_to_left(I18N_USCRIPT_ARABIC);
	PRINT_RESULT(bIsRightToLeft, true, "i18n_uscript_is_right_to_left", "answer is not correct");

	return 0;
}
/*
 * @testcase		ITc_i18n_uscript_breaks_between_letters_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		checks whether uscript is cased or not
 * @apitarget		i18n_uscript_breaks_between_letters
 * @apicovered		i18n_uscript_breaks_between_letters
 * @passcase		i18n_uscript_breaks_between_letters is successful
 * @failcase		i18n_uscript_breaks_between_letters is not successful
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uscript_breaks_between_letters_p(void)
{
        START_TEST_PRINT;
        i18n_ubool b = i18n_uscript_breaks_between_letters(I18N_USCRIPT_KOREAN);
	PRINT_RESULT(b, false,"ITc_i18n_uscript_breaks_between_letters", "answer is not correct");

	b = i18n_uscript_breaks_between_letters(I18N_USCRIPT_THAI);
	PRINT_RESULT(b, true,"ITc_i18n_uscript_breaks_between_letters", "answer is not correct");
        return 0;
}
/*
 * @testcase		ITc_i18n_uscript_is_cased_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		checks whether uscript is cased or not
 * @apitarget		i18n_uscript_is_cased
 * @apicovered		i18n_uscript_is_cased
 * @passcase		i18n_uscript_is_cased is called successfully
 * @failcase	        i18n_uscript_is_cased is not called successfully
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uscript_is_cased_p(void)
{
        START_TEST_PRINT;
        i18n_ubool b = i18n_uscript_is_cased(I18N_USCRIPT_KOREAN);
	PRINT_RESULT(b, false,"ITc_i18n_uscript_breaks_between_letters", "answer is not correct");

	b = i18n_uscript_is_cased(I18N_USCRIPT_LATIN);
	PRINT_RESULT(b, true,"ITc_i18n_uscript_breaks_between_letters", "answer is not correct");

	return 0;
}
