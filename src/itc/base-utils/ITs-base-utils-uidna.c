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
* @function 		ITs_base_utils_uidna_startup
* @description	 	Called before each test
* @parameter		NA
* @return 	        NA
*/
void ITs_base_utils_uidna_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT start-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif
        int nRet = i18n_uidna_create(I18N_UIDNA_DEFAULT, &h_uidna);
	if (nRet != I18N_ERROR_NONE)
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("\\n[Line : %d][%s] i18n_uidna_create failed with error code %s\\n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRet));
	}
	else if(h_uidna == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] h_uidna is null\\n", __LINE__, API_NAMESPACE);
		g_bBaseUtilsInitFlag = false;
	}
	else
	{
		g_bBaseUtilsInitFlag = true;
	}
	return;
}
/**
* @function 		ITs_base_utils_uidna_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 	        NA
*/
void ITs_base_utils_uidna_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

        int nRet = -1;
        if(h_uidna != NULL)
        {
               nRet = i18n_uidna_destroy(h_uidna);
               if(nRet != I18N_ERROR_NONE)
               {
                       FPRINTF("\\n[Line : %d][%s] i18n_uidna_destroy failed with error code %s\\n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRet)); 
               }
               h_uidna = NULL;
        }
        g_bBaseUtilsInitFlag = false;
	return;
}
/*
 * @testcase		ITc_i18n_uidna_label_to_ascii_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_uidna_label_to_ascii
 * @apicovered		18n_uidna_create, i18n_uidna_label_to_ascii, i18n_uidna_destroy, i18n_uidna_info_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_uidna_label_to_ascii
 * @failcase		I18N_ERROR_NONE not returned by i18n_uidna_label_to_ascii
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uidna_label_to_ascii_p(void)
{
        START_TEST;

        int nRet = -1;
        i18n_uchar dest[I18N_UCHAR_CAPACITY];
	i18n_uidna_info_h h_info = NULL;
	int32_t length = -1;
        int32_t expected_length = 4;
        static const i18n_uchar fA_sharps16[] = { 0x66, 0x41, 0xdf, 0 };

        //Target API
        nRet = i18n_uidna_label_to_ascii(h_uidna, fA_sharps16, -1, dest, I18N_UCHAR_CAPACITY, &h_info, &length);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_uidna_label_to_ascii", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_info, "i18n_uidna_label_to_ascii");
        PRINT_RESULT_CLEANUP(length, expected_length, "i18n_uidna_label_to_ascii", "obtained length and expected length are not same", i18n_uidna_info_destroy(h_info));

        nRet = i18n_uidna_info_destroy(h_info);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uidna_info_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_uidna_label_to_unicode_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_uidna_label_to_unicode
 * @apicovered		18n_uidna_create, i18n_uidna_label_to_unicode, i18n_uidna_destroy, i18n_uidna_info_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_uidna_label_to_unicode
 * @failcase		I18N_ERROR_NONE not returned by i18n_uidna_label_to_unicode
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uidna_label_to_unicode_p(void)
{
        START_TEST;

        int nRet = -1;
        i18n_uchar dest[I18N_UCHAR_CAPACITY];
	i18n_uidna_info_h h_info = NULL;
	int32_t length = -1;
        int32_t expected_length = 4;
        static const i18n_uchar fA_sharps16[] = { 0x66, 0x41, 0xdf, 0 };

        //Target API
        nRet = i18n_uidna_label_to_unicode(h_uidna, fA_sharps16, i18n_ustring_get_length(fA_sharps16), dest, I18N_UCHAR_CAPACITY, &h_info, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_uidna_label_to_unicode", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_info, "i18n_uidna_label_to_unicode");
        PRINT_RESULT_CLEANUP(length, expected_length, "i18n_uidna_label_to_ascii", "obtained length and expected length are not same", i18n_uidna_info_destroy(h_info));

        nRet = i18n_uidna_info_destroy(h_info);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uidna_info_destroy", BaseUtilsGetError(nRet));

        return 0;

}
/*
 * @testcase		ITc_i18n_uidna_name_to_ascii_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_uidna_name_to_ascii
 * @apicovered		18n_uidna_create, i18n_uidna_name_to_ascii, i18n_uidna_destroy, i18n_uidna_info_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_uidna_name_to_ascii
 * @failcase		I18N_ERROR_NONE not returned by i18n_uidna_name_to_ascii
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uidna_name_to_ascii_p(void)
{
        START_TEST;

        int nRet = -1;
        i18n_uchar dest[I18N_UCHAR_CAPACITY];
	i18n_uidna_info_h h_info = NULL;
	int32_t length = -1;
        int32_t expected_length = 4;
        static const i18n_uchar fA_sharps16[] = { 0x66, 0x41, 0xdf, 0 };

        //Target API
        nRet = i18n_uidna_name_to_ascii(h_uidna, fA_sharps16, i18n_ustring_get_length(fA_sharps16), dest, I18N_UCHAR_CAPACITY, &h_info, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_uidna_name_to_ascii", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_info, "i18n_uidna_name_to_ascii");
        PRINT_RESULT_CLEANUP(length, expected_length, "i18n_uidna_name_to_ascii", "obtained length and expected length are not same", i18n_uidna_info_destroy(h_info));

        nRet = i18n_uidna_info_destroy(h_info);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uidna_info_destroy", BaseUtilsGetError(nRet));

        return 0;

}
/*
 * @testcase		ITc_i18n_uidna_name_to_unicode_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_uidna_name_to_unicode
 * @apicovered		18n_uidna_create, i18n_uidna_name_to_unicode, i18n_uidna_destroy, i18n_uidna_info_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_uidna_name_to_unicode
 * @failcase		I18N_ERROR_NONE not returned by i18n_uidna_name_to_unicode
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uidna_name_to_unicode_p(void)
{
        START_TEST;

        int nRet = -1;
        i18n_uchar dest[I18N_UCHAR_CAPACITY];
	i18n_uidna_info_h h_info = NULL;
	int32_t length = -1;
        int32_t expected_length = 4;
        static const i18n_uchar fA_sharps16[] = { 0x66, 0x41, 0xdf, 0 };

        //Target API
        nRet = i18n_uidna_name_to_unicode(h_uidna, fA_sharps16, -1, dest, I18N_UCHAR_CAPACITY, &h_info, &length);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_uidna_name_to_unicode", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_info, "i18n_uidna_name_to_unicode");
        PRINT_RESULT_CLEANUP(length, expected_length, "i18n_uidna_name_to_unicode", "obtained length and expected length are not same", i18n_uidna_info_destroy(h_info));

        nRet = i18n_uidna_info_destroy(h_info);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uidna_info_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_uidna_label_to_ascii_UTF8_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_uidna_label_to_ascii_UTF8
 * @apicovered		18n_uidna_create, i18n_uidna_label_to_ascii_UTF8, i18n_uidna_destroy, i18n_uidna_info_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_uidna_label_to_ascii_UTF8
 * @failcase		I18N_ERROR_NONE not returned by i18n_uidna_label_to_ascii_UTF8
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uidna_label_to_ascii_UTF8_p(void)
{
        START_TEST;

        int nRet = -1;
        char dest[I18N_UCHAR_CAPACITY];
	i18n_uidna_info_h h_info = NULL;
	int32_t length = -1;
        int32_t expected_length = 4;
        static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };

        //Target API
        nRet = i18n_uidna_label_to_ascii_UTF8(h_uidna, fA_sharps8, -1, dest, I18N_UCHAR_CAPACITY, &h_info, &length);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_uidna_label_to_ascii_UTF8", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_info, "i18n_uidna_label_to_ascii_UTF8");
        PRINT_RESULT_CLEANUP(length, expected_length, "i18n_uidna_label_to_ascii_UTF8", "obtained length and expected length are not same", i18n_uidna_info_destroy(h_info));

        nRet = i18n_uidna_info_destroy(h_info);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uidna_info_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_uidna_label_to_unicode_UTF8_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_uidna_label_to_unicode_UTF8
 * @apicovered		i18n_uidna_create, i18n_uidna_label_to_unicode_UTF8, i18n_uidna_destroy, i18n_uidna_info_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_uidna_label_to_unicode_UTF8
 * @failcase		I18N_ERROR_NONE not returned by i18n_uidna_label_to_unicode_UTF8
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uidna_label_to_unicode_UTF8_p(void)
{
        START_TEST;

        int nRet = -1;
        char dest[I18N_UCHAR_CAPACITY];
	i18n_uidna_info_h h_info = NULL;
	int32_t length = -1;
        int32_t expected_length = 4;
        static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };

        //Target API
        nRet = i18n_uidna_label_to_unicode_UTF8(h_uidna, fA_sharps8, (int32_t)strlen(fA_sharps8), dest, I18N_UCHAR_CAPACITY, &h_info, &length);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_uidna_label_to_unicode_UTF8", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_info, "i18n_uidna_label_to_unicode_UTF8");
        PRINT_RESULT_CLEANUP(length, expected_length, "i18n_uidna_label_to_unicode_UTF8", "obtained length and expected length are not same", i18n_uidna_info_destroy(h_info));

        nRet = i18n_uidna_info_destroy(h_info);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uidna_info_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_uidna_name_to_ascii_UTF8_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_uidna_name_to_ascii_UTF8
 * @apicovered		i18n_uidna_create, i18n_uidna_name_to_ascii_UTF8, i18n_uidna_destroy, i18n_uidna_info_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_uidna_name_to_ascii_UTF8
 * @failcase		I18N_ERROR_NONE not returned by i18n_uidna_name_to_ascii_UTF8
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uidna_name_to_ascii_UTF8_p(void)
{
        START_TEST;

        int nRet = -1;
        char dest[I18N_UCHAR_CAPACITY];
	i18n_uidna_info_h h_info = NULL;
	int32_t length = -1;
        int32_t expected_length = 4;
        static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };

        //Target API
        nRet = i18n_uidna_name_to_ascii_UTF8(h_uidna, fA_sharps8, (int32_t)strlen(fA_sharps8), dest, I18N_UCHAR_CAPACITY, &h_info, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_uidna_name_to_ascii_UTF8", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_info, "i18n_uidna_name_to_ascii_UTF8");
        PRINT_RESULT_CLEANUP(length, expected_length, "i18n_uidna_name_to_ascii_UTF8", "obtained length and expected length are not same", i18n_uidna_info_destroy(h_info));
        nRet = i18n_uidna_info_destroy(h_info);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uidna_info_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_uidna_name_to_unicode_UTF8_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_uidna_name_to_unicode_UTF8
 * @apicovered		i18n_uidna_create, i18n_uidna_name_to_unicode_UTF8, i18n_uidna_destroy, i18n_uidna_info_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_uidna_name_to_unicode_UTF8
 * @failcase		I18N_ERROR_NONE not returned by i18n_uidna_name_to_unicode_UTF8
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uidna_name_to_unicode_UTF8_p(void)
{
        START_TEST;

        int nRet = -1;
        char dest[I18N_UCHAR_CAPACITY];
	i18n_uidna_info_h h_info = NULL;
	int32_t length = -1;
        int32_t expected_length = 4;
        static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };

        //Target API
        nRet = i18n_uidna_name_to_unicode_UTF8(h_uidna, fA_sharps8, -1, dest, I18N_UCHAR_CAPACITY, &h_info, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_uidna_name_to_unicode_UTF8", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_info, "i18n_uidna_name_to_unicode_UTF8");
        PRINT_RESULT_CLEANUP(length, expected_length, "i18n_uidna_name_to_unicode_UTF8", "obtained length and expected length are not same", i18n_uidna_info_destroy(h_info));

        nRet = i18n_uidna_info_destroy(h_info);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uidna_info_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_uidna_info_get_is_trans_different_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_uidna_info_get_is_trans_different
 * @apicovered		i18n_uidna_create, i18n_uidna_name_to_unicode_UTF8, i18n_uidna_destroy, i18n_uidna_info_destroy, i18n_uidna_info_get_is_trans_different
 * @passcase		I18N_ERROR_NONE returned by i18n_uidna_info_get_is_trans_different
 * @failcase		I18N_ERROR_NONE not returned by i18n_uidna_info_get_is_trans_different
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uidna_info_get_is_trans_different_p(void)
{
        START_TEST;

        int nRet = -1;
        char dest[I18N_UCHAR_CAPACITY];
	i18n_uidna_info_h h_info = NULL;
	int32_t length = -1;
        int32_t expected_length = 4;
        i18n_ubool is_trans_different = false;
        static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };

        nRet = i18n_uidna_name_to_unicode_UTF8(h_uidna, fA_sharps8, -1, dest, I18N_UCHAR_CAPACITY, &h_info, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_uidna_name_to_unicode_UTF8", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_info, "i18n_uidna_name_to_unicode_UTF8");
        PRINT_RESULT_CLEANUP(length, expected_length, "i18n_uidna_name_to_unicode_UTF8", "obtained length and expected length are not same", i18n_uidna_info_destroy(h_info));

        //Target API
        nRet = i18n_uidna_info_get_is_trans_different(h_info, &is_trans_different);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_uidna_info_get_is_trans_different", BaseUtilsGetError(nRet), i18n_uidna_info_destroy(h_info));
        PRINT_RESULT_CLEANUP(true, is_trans_different, "i18n_uidna_info_get_is_trans_different", "obtained result is not correct", i18n_uidna_info_destroy(h_info));

        nRet = i18n_uidna_info_destroy(h_info);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uidna_info_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_uidna_info_get_errors_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_uidna_info_get_errors
 * @apicovered		i18n_uidna_create, i18n_uidna_name_to_unicode_UTF8, i18n_uidna_info_get_errors, i18n_uidna_destroy, i18n_uidna_info_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_uidna_info_get_errors
 * @failcase		I18N_ERROR_NONE not returned by i18n_uidna_info_get_errors
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uidna_info_get_errors_p(void)
{
        START_TEST;

        int nRet = -1;
        char dest[I18N_UCHAR_CAPACITY];
	i18n_uidna_info_h h_info = NULL;
	int32_t length = -1;
        int32_t expected_length = 4;
        uint32_t errors;
        static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };

        nRet = i18n_uidna_name_to_unicode_UTF8(h_uidna, fA_sharps8, -1, dest, I18N_UCHAR_CAPACITY, &h_info, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_uidna_name_to_unicode_UTF8", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_info, "i18n_uidna_name_to_unicode_UTF8");
        PRINT_RESULT_CLEANUP(length, expected_length, "i18n_uidna_name_to_unicode_UTF8", "obtained length and expected length are not same", i18n_uidna_info_destroy(h_info));

        //Target API
        nRet = i18n_uidna_info_get_errors(h_info, &errors);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_uidna_name_to_unicode_UTF8", BaseUtilsGetError(nRet), i18n_uidna_info_destroy(h_info));

        nRet = i18n_uidna_info_destroy(h_info);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uidna_info_destroy", BaseUtilsGetError(nRet));

        return 0;
}
/*
 * @testcase		ITc_i18n_uidna_info_destroy_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_uidna_info_destroy
 * @apicovered		i18n_uidna_create, i18n_uidna_name_to_unicode_UTF8, i18n_uidna_info_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_uidna_info_destroy
 * @failcase		I18N_ERROR_NONE not returned by i18n_uidna_info_destroy
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_uidna_info_destroy_p(void)
{
        START_TEST;

        int nRet = -1;
        char dest[I18N_UCHAR_CAPACITY];
	i18n_uidna_info_h h_info = NULL;
	int32_t length = -1;
        static const char fA_sharps8[] = { 0x66, 0x41, (char)0xc3, (char)0x9f, 0 };

        nRet = i18n_uidna_name_to_unicode_UTF8(h_uidna, fA_sharps8, -1, dest, I18N_UCHAR_CAPACITY, &h_info, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_uidna_name_to_unicode_UTF8", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_info, "i18n_uidna_name_to_unicode_UTF8");

        //Target API
        nRet = i18n_uidna_info_destroy(h_info);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_uidna_info_destroy", BaseUtilsGetError(nRet));

        return 0;
}
