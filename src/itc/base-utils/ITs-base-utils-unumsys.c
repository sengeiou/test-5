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
* @function 		ITs_base_utils_unumsys_startup
* @description	 	Called before each test
* @parameter		NA
* @return 	        NA
*/
void ITs_base_utils_unumsys_startup(void)
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
* @function 		ITs_base_utils_unumsys_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 	        NA
*/
void ITs_base_utils_unumsys_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

/*
 * @testcase		ITc_i18n_unumsys_create_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unumsys_create
 * @apicovered		i18n_unumsys_create
 * @passcase		I18N_ERROR_NONE returned by i18n_unumsys_create
 * @failcase		I18N_ERROR_NONE not returned by i18n_unumsys_create
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unumsys_create_p(void)
{
        START_TEST_PRINT;
        const char* pszLocale = "en@numbers=roman";
        i18n_unumsys_h unumsys = NULL;
        int nRet = -1;

        //Target API
        nRet = i18n_unumsys_create(pszLocale, &unumsys);
        CHECK_HANDLE(unumsys, "i18n_unumsys_create");
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_unumsys_create", BaseUtilsGetError(nRet), i18n_unumsys_destroy(unumsys));
        i18n_unumsys_destroy(unumsys);
        return 0;
}
/*
 * @testcase		ITc_i18n_unumsys_create_by_name_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unumsys_create_by_name
 * @apicovered		i18n_unumsys_create_by_name
 * @passcase		I18N_ERROR_NONE returned by i18n_unumsys_create_by_name
 * @failcase		I18N_ERROR_NONE not returned by i18n_unumsys_create_by_name
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unumsys_create_by_name_p(void)
{
        START_TEST_PRINT;
        const char* pszName = "arabext";
        i18n_unumsys_h unumsys = NULL;
        int nRet = -1;

        //Target API
        nRet = i18n_unumsys_create_by_name(pszName, &unumsys);
        CHECK_HANDLE(unumsys, "i18n_unumsys_create_by_name");
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_unumsys_create_by_name", BaseUtilsGetError(nRet), i18n_unumsys_destroy(unumsys));
        i18n_unumsys_destroy(unumsys);
        return 0;
}
/*
 * @testcase		ITc_i18n_unumsys_get_available_names_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unumsys_get_available_names
 * @apicovered		i18n_unumsys_get_available_names
 * @passcase		I18N_ERROR_NONE returned by i18n_unumsys_get_available_names
 * @failcase		I18N_ERROR_NONE not returned by i18n_unumsys_get_available_names
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unumsys_get_available_names_p(void)
{
        START_TEST_PRINT;
        int nRet = -1;
        i18n_uenumeration_h uenum = NULL;

        //Target API
        nRet = i18n_unumsys_get_available_names(&uenum);
        CHECK_HANDLE(uenum, "i18n_unumsys_get_available_names");
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_unumsys_get_available_names", BaseUtilsGetError(nRet), i18n_uenumeration_destroy(uenum));
        i18n_uenumeration_destroy(uenum);
        return 0;
}
/*
 * @testcase		ITc_i18n_unumsys_get_name_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unumsys_get_name
 * @apicovered		i18n_unumsys_get_name, i18n_unumsys_create
 * @passcase		I18N_ERROR_NONE returned by i18n_unumsys_get_name
 * @failcase		I18N_ERROR_NONE not returned by i18n_unumsys_get_name
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unumsys_get_name_p(void)
{
        START_TEST_PRINT;
        const char* pszName = "en";
        i18n_unumsys_h unumsys = NULL;
        int nRet = -1;
        const char* pszNumsys = NULL;

        nRet = i18n_unumsys_create(pszName, &unumsys);
        CHECK_HANDLE(unumsys, "i18n_unumsys_create");
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_unumsys_create", BaseUtilsGetError(nRet), i18n_unumsys_destroy(unumsys));
        //Target API
        nRet = i18n_unumsys_get_name(unumsys, &pszNumsys);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_unumsys_get_name", BaseUtilsGetError(nRet), i18n_unumsys_destroy(unumsys));
        CHECK_HANDLE(pszNumsys, "i18n_unumsys_get_name");
        if(strncmp(pszNumsys, "latn", strlen("latn")) != 0)
        {
             FPRINTF("[Line : %d][%s] error returned = returned string is not correct\\n", __LINE__, API_NAMESPACE);
             i18n_unumsys_destroy(unumsys);
             return 1;
        }
        i18n_unumsys_destroy(unumsys);
        return 0;
}
/*
 * @testcase		ITc_i18n_unumsys_is_algorithmic_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unumsys_is_algorithmic
 * @apicovered		i18n_unumsys_is_algorithmic, i18n_unumsys_create
 * @passcase		I18N_ERROR_NONE returned by i18n_unumsys_is_algorithmic
 * @failcase		I18N_ERROR_NONE not returned by i18n_unumsys_is_algorithmic
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unumsys_is_algorithmic_p(void)
{
        START_TEST_PRINT;
        int nRet = -1;
        const char* pszLocale = "en";
        const char* pszLocaleNew = "en@numbers=roman";
        i18n_ubool result = true;
        i18n_unumsys_h unumsys = NULL;
        i18n_unumsys_h unumsysnew = NULL;

        nRet = i18n_unumsys_create(pszLocale, &unumsys);
        CHECK_HANDLE(unumsys, "i18n_unumsys_create");
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_unumsys_create", BaseUtilsGetError(nRet), i18n_unumsys_destroy(unumsys));
        //Target API
        nRet = i18n_unumsys_is_algorithmic(unumsys, &result);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_unumsys_is_algorithmic", BaseUtilsGetError(nRet), i18n_unumsys_destroy(unumsys));
	PRINT_RESULT_CLEANUP(false, result, "i18n_unumsys_is_algorithmic", "obtained result is incorrect", i18n_unumsys_destroy(unumsys));

        nRet = i18n_unumsys_create(pszLocaleNew, &unumsysnew);
        CHECK_HANDLE(unumsysnew, "i18n_unumsys_create");
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_unumsys_create", BaseUtilsGetError(nRet), i18n_unumsys_destroy(unumsysnew));
        //Target API
        nRet = i18n_unumsys_is_algorithmic(unumsysnew, &result);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_unumsys_is_algorithmic", BaseUtilsGetError(nRet), i18n_unumsys_destroy(unumsysnew));
	PRINT_RESULT_CLEANUP(true, result, "i18n_unumsys_is_algorithmic", "obtained result is incorrect", i18n_unumsys_destroy(unumsysnew));

        i18n_unumsys_destroy(unumsys);
        i18n_unumsys_destroy(unumsysnew);
        return 0;
}
/*
 * @testcase		ITc_i18n_unumsys_get_radix_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unumsys_get_radix
 * @apicovered		i18n_unumsys_get_radix, i18n_unumsys_create
 * @passcase		I18N_ERROR_NONE returned by i18n_unumsys_get_radix
 * @failcase		I18N_ERROR_NONE not returned by i18n_unumsys_get_radix
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unumsys_get_radix_p(void)
{
        START_TEST_PRINT;
        const char* pszLocale = "en";
        i18n_unumsys_h unumsys = NULL;
        int nRet = -1;
        int32_t result = -1;
        int32_t expected_result = 10;


        nRet = i18n_unumsys_create(pszLocale, &unumsys);
        CHECK_HANDLE(unumsys, "i18n_unumsys_create");
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_unumsys_create", BaseUtilsGetError(nRet), i18n_unumsys_destroy(unumsys));
        //Target API
	nRet = i18n_unumsys_get_radix(unumsys, &result);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_unumsys_get_radix", BaseUtilsGetError(nRet), i18n_unumsys_destroy(unumsys));
        PRINT_RESULT_CLEANUP(result, expected_result, "i18n_unumsys_get_radix", "obtained result is not correct", i18n_unumsys_destroy(unumsys));
        i18n_unumsys_destroy(unumsys);

        return 0;
}
/*
 * @testcase		ITc_i18n_unumsys_get_description_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unumsys_get_description
 * @apicovered		i18n_unumsys_get_description, i18n_unumsys_create
 * @passcase		I18N_ERROR_NONE returned by i18n_unumsys_get_description
 * @failcase		I18N_ERROR_NONE not returned by i18n_unumsys_get_description
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unumsys_get_description_p(void)
{
        START_TEST_PRINT;
        const char* pszLocale = "en";
        i18n_unumsys_h unumsys = NULL;
        int nRet = -1;
        static const i18n_uchar latn_desc[] = {0x0030,0x0031,0x0032,0x0033,0x0034,0x0035,0x0036,0x0037,0x0038,0x0039,0};
        int32_t ulen = -1;
	i18n_uchar result[I18N_UCHAR_CAPACITY];

        nRet = i18n_unumsys_create(pszLocale, &unumsys);
        CHECK_HANDLE(unumsys, "i18n_unumsys_create");
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_unumsys_create", BaseUtilsGetError(nRet), i18n_unumsys_destroy(unumsys));
        //Target API
        nRet = i18n_unumsys_get_description(unumsys, result, I18N_UCHAR_CAPACITY, &ulen);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_unumsys_get_description", BaseUtilsGetError(nRet), i18n_unumsys_destroy(unumsys));
	PRINT_RESULT_CLEANUP(i18n_ustring_compare(result, latn_desc), 0, "i18n_unumsys_get_description", "obtained values are not correct", i18n_unumsys_destroy(unumsys));
        i18n_unumsys_destroy(unumsys);

        return 0;
}
