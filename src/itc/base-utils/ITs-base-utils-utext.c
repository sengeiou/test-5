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
* @function 		ITs_base_utils_utext_startup
* @description	 	Called before each test
* @parameter		NA
* @return               NA
*/
void ITs_base_utils_utext_startup(void)
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
* @function 		ITs_base_utils_utext_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 		NA
*/
void ITs_base_utils_utext_cleanup(void)
{
#if DEBUG
        FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

        return;
}

/**
* @testcase				ITc_i18n_utext_create_for_UTF8_p
* @since_tizen 			        6.0
* @author            	                mohit.m
* @reviewer                             shobhit.v
* @type 				auto
* @scenario				Creates the handle for UTF8 type string
* @apitarget			        i18n_utext_create_for_UTF8
* @apicovered			        i18n_utext_create_for_UTF8, i18n_utext_next32
* @passcase				When i18n_utext_create_for_UTF8, i18n_utext_next32 is successful
* @failcase				If target i18n_utext_create_for_UTF8, i18n_utext_next32 API fails or any precondition and postcondition API fails.
* @precondition			        NA
* @postcondition		        NA
*/
int ITc_i18n_utext_create_for_UTF8_p(void)
{
        START_TEST_PRINT;
        i18n_utext_h g_utext = NULL;
        const char *pszCreateString = NULL;
        i18n_utext_h g_utb = NULL;
        int nRet;

        //Target API
        nRet = i18n_utext_create_for_UTF8(g_utext, pszCreateString, 0, &g_utb);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_UTF8", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_utb, "i18n_utext_create_for_UTF8");
        return 0;
}
/**
* @testcase				ITc_i18n_utext_create_for_uchars_p
* @since_tizen 			        6.0
* @author            	                mohit.m
* @reviewer                             shobhit.v
* @type 				auto
* @scenario				Creates the handle for uchars type string
* @apitarget			        i18n_utext_create_for_uchars
* @apicovered			        i18n_utext_create_for_uchars, i18n_utext_destroy
* @passcase				When i18n_utext_create_for_uchars, i18n_utext_destroy is successful
* @failcase				If target i18n_utext_create_for_uchars, i18n_utext_destroy API fails or any precondition and postcondition API fails.
* @precondition			        NA
* @postcondition		        NA
*/
int ITc_i18n_utext_create_for_uchars_p(void)
{
        START_TEST_PRINT;
        i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0};
        i18n_utext_h g_utext = NULL;
        i18n_utext_h g_utb = NULL;
        int nRet;

        //Target API
        nRet = i18n_utext_create_for_uchars(g_utext, uString, -1, &g_utb);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_uchars", BaseUtilsGetError(nRet));

        CHECK_HANDLE(g_utb, "i18n_utext_create_for_uchars");
        i18n_utext_destroy(g_utb);
        return 0;
}
/**
* @testcase				ITc_i18n_utext_clone_p
* @since_tizen 			        6.0
* @author            	                mohit.m
* @reviewer                             shobhit.v
* @type 				auto
* @scenario				Creates the handle for uchars type string
* @apitarget			        i18n_utext_clone
* @apicovered			        i18n_utext_create_for_uchars, i18n_utext_clone, i18n_utext_destroy
* @passcase				When i18n_utext_create_for_uchars, i18n_utext_clone is successful
* @failcase				If target i18n_utext_create_for_uchars, i18n_utext_clone API fails or any precondition and postcondition API fails.
* @precondition			        NA
* @postcondition		        NA
*/
int ITc_i18n_utext_clone_p(void)
{
        START_TEST_PRINT;
        i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0};
        i18n_utext_h g_uta = NULL;
        i18n_utext_h g_utb = NULL;
        i18n_utext_h g_utext_dest = NULL;
        i18n_utext_h g_utext = NULL;
        int nRet;

        nRet = i18n_utext_create_for_uchars(g_utext, uString, -1, &g_utb);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_uchars", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_utb, "i18n_utext_create_for_uchars");
        //Target API
        nRet = i18n_utext_clone(g_utext_dest, g_utb, false, false, &g_uta);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_clone", BaseUtilsGetError(nRet));

        CHECK_HANDLE(g_uta, "i18n_utext_clone");
        if(g_uta == g_utb)
        {
	        i18n_utext_destroy(g_uta);
                i18n_utext_destroy(g_utb);
                return 1;
        }
        i18n_utext_destroy(g_uta);
        i18n_utext_destroy(g_utb);
        return 0;
}
/**
* @testcase				ITc_i18n_utext_equals_p
* @since_tizen 			        6.0
* @author            	                mohit.m
* @reviewer                             shobhit.v
* @type 				auto
* @scenario				checks the equality of two handles
* @apitarget			        i18n_utext_equals
* @apicovered			        i18n_utext_create_for_uchars, i18n_utext_equals
* @passcase				When i18n_utext_create_for_uchars, i18n_utext_equals is successful
* @failcase				If target i18n_utext_create_for_uchars, i18n_utext_equals API fails or any precondition and postcondition API fails.
* @precondition			        NA
* @postcondition	                NA
*/
int ITc_i18n_utext_equals_p(void)
{
        START_TEST_PRINT;
        i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0};
        i18n_utext_h g_utext_one = NULL;
        i18n_utext_h g_utb_one = NULL;
        i18n_utext_h g_utext_two = NULL;
        i18n_utext_h g_utb_two = NULL;
        int nRet;

        nRet = i18n_utext_create_for_uchars(g_utext_one, uString, -1, &g_utb_one);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_uchars", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_utb_one, "i18n_utext_create_for_uchars");

        nRet = i18n_utext_create_for_uchars(g_utext_two, uString, -1, &g_utb_two);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_uchars", BaseUtilsGetError(nRet), i18n_utext_destroy(g_utb_one));
        CHECK_HANDLE(g_utb_two, "i18n_utext_create_for_uchars");

        //Target API
        i18n_ubool result = i18n_utext_equals(g_utb_one, g_utb_two);
        PRINT_RESULT_CLEANUP(true, result, "i18n_utext_equals", "values are not same", i18n_utext_destroy(g_utb_one); i18n_utext_destroy(g_utb_two));

        i18n_utext_destroy(g_utb_one);
        i18n_utext_destroy(g_utb_two);
        return 0;
}
/**
* @testcase				ITc_i18n_utext_native_length_p
* @since_tizen 			        6.0
* @author            	                mohit.m
* @reviewer                             shobhit.v
* @type 				auto
* @scenario				checks the length of utext string
* @apitarget			        i18n_utext_native_length
* @apicovered			        i18n_utext_create_for_uchars, i18n_utext_clone, i18n_utext_destroy
* @passcase				When i18n_utext_create_for_uchars, i18n_utext_clone, i18n_utext_native_length is successful
* @failcase				If target i18n_utext_create_for_uchars, i18n_utext_clone, utext_native_length API fails or any precondition and postcondition API fails.
* @precondition			        NA
* @postcondition		        NA
*/
int ITc_i18n_utext_native_length_p(void)
{
        START_TEST_PRINT;
        i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0};
        int64_t len;
        i18n_utext_h g_uta = NULL;
        i18n_utext_h g_utb = NULL;
        i18n_utext_h g_utext_dest = NULL;
        i18n_utext_h g_utext = NULL;
        int nRet;

        nRet = i18n_utext_create_for_uchars(g_utext, uString, -1, &g_utb);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_uchars", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_utb, "i18n_utext_create_for_uchars");

        nRet = i18n_utext_clone(g_utext_dest, g_utb, false, false, &g_uta);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_utext_clone", BaseUtilsGetError(nRet), i18n_utext_destroy(g_utb));

        //Target API
        len = i18n_utext_native_length(g_utb);
        PRINT_RESULT_CLEANUP(len, i18n_ustring_get_length(uString), "i18n_utext_native_length", "lengths are different", i18n_utext_destroy(g_utb); i18n_utext_destroy(g_uta));

        i18n_utext_destroy(g_utb);
        i18n_utext_destroy(g_uta);
        return 0;
}
/**
* @testcase				ITc_i18n_utext_is_length_expensive_p
* @since_tizen 			        6.0
* @author            	                mohit.m
* @reviewer                             shobhit.v
* @type 				auto
* @scenario				checks the length of utext string
* @apitarget			        i18n_utext_is_length_expensive
* @apicovered			        i18n_utext_create_for_uchars, i18n_utext_destroy, i18n_utext_is_length_expensive
* @passcase				When i18n_utext_create_for_uchars, i18n_utext_is_length_expensive is successful
* @failcase				If target i18n_utext_create_for_uchars, i18n_utext_is_length_expensive API fails or any precondition and postcondition API fails.
* @precondition		         	NA
* @postcondition	         	NA
*/
int ITc_i18n_utext_is_length_expensive_p(void)
{
        START_TEST_PRINT;
        i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0};
        int64_t len;
        i18n_utext_h g_utb = NULL;
        i18n_utext_h g_utext = NULL;
        int nRet;
        i18n_ubool b;

        nRet = i18n_utext_create_for_uchars(g_utext, uString, -1, &g_utb);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_uchars", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_utb, "i18n_utext_create_for_uchars");
        //Target API
        b = i18n_utext_is_length_expensive(g_utb);
        PRINT_RESULT_CLEANUP(b, true, "i18n_utext_is_length_expensive", "it is not expensive", i18n_utext_destroy(g_utb));
        i18n_utext_destroy(g_utb);
        return 0;
}
/**
* @testcase				ITc_i18n_utext_char32_at_p
* @since_tizen 			        6.0
* @author            	                mohit.m
* @reviewer                             shobhit.v
* @type 				auto
* @scenario				checks the character at a specific position
* @apitarget			        i18n_utext_char32_at
* @apicovered			        i18n_utext_create_for_uchars, i18n_utext_char32_at
* @passcase				When i18n_utext_create_for_uchars, i18n_utext_char32_at is successful
* @failcase				If target i18n_utext_create_for_uchars, i18n_utext_char32_at API fails or any precondition and postcondition API fails.
* @precondition			        NA
* @postcondition		        NA
*/
int ITc_i18n_utext_char32_at_p(void)
{
        START_TEST_PRINT;
        i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0};
        i18n_utext_h g_utb = NULL;
        i18n_utext_h g_utext = NULL;
        i18n_uchar32 c;
        int nRet;

        nRet = i18n_utext_create_for_uchars(g_utext, uString, -1, &g_utb);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_uchars", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_utb, "i18n_utext_create_for_uchars");

        int i;

        for(i = 0; i < 2; i++)
        {
                //Target API
                c = i18n_utext_char32_at(g_utb, i);
                PRINT_RESULT_CLEANUP(uString[i], c, "i18n_utext_char32_at", "characters are not same", i18n_utext_destroy(g_utb));
        }
        i18n_utext_destroy(g_utb);
        return 0;
}
/**
* @testcase				ITc_i18n_utext_current32_p
* @since_tizen 			        6.0
* @author            	                mohit.m
* @reviewer                             shobhit.v
* @type 				auto
* @scenario				checks the character at a specific position
* @apitarget			        i18n_utext_current32
* @apicovered			        i18n_utext_create_for_uchars, i18n_utext_current32
* @passcase				When i18n_utext_create_for_uchars, i18n_utext_current32 is successful
* @failcase				If target i18n_utext_create_for_uchars, i18n_utext_current32 API fails or any precondition and postcondition API fails.
* @precondition			        NA
* @postcondition	         	NA
*/
int ITc_i18n_utext_current32_p(void)
{
        START_TEST_PRINT;
        i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0};
        i18n_utext_h g_utb = NULL;
        i18n_utext_h g_utext = NULL;
        i18n_uchar32 c;
        int nRet;

        nRet = i18n_utext_create_for_uchars(g_utext, uString, -1, &g_utb);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_uchars", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_utb, "i18n_utext_create_for_uchars");

        //Target API
	c = i18n_utext_current32(g_utb);
        PRINT_RESULT_CLEANUP(uString[0], c, "i18n_utext_current32", "characters are not same", i18n_utext_destroy(g_utb));
        i18n_utext_destroy(g_utb);

        return 0;
}
/**
* @testcase				ITc_i18n_utext_next32_p
* @since_tizen 			        6.0
* @author            	                mohit.m
* @reviewer                             shobhit.v
* @type 				auto
* @scenario				checks the character at a specific positions
* @apitarget			        i18n_utext_next32
* @apicovered			        i18n_utext_create_for_uchars, i18n_utext_next32
* @passcase				When i18n_utext_create_for_uchars, i18n_utext_next32 is successful
* @failcase				If target i18n_utext_create_for_uchars, i18n_utext_next32 API fails or any precondition and postcondition API fails.
* @precondition			        NA
* @postcondition		        NA
*/
int ITc_i18n_utext_next32_p(void)
{
        START_TEST_PRINT;
        i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0};
        i18n_utext_h g_utb = NULL;
        i18n_utext_h g_utext = NULL;
        i18n_uchar32 c;
        int nRet;

        nRet = i18n_utext_create_for_uchars(g_utext, uString, -1, &g_utb);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_uchars", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_utb, "i18n_utext_create_for_uchars");

        //Target API
        c = i18n_utext_next32(g_utb);
        PRINT_RESULT_CLEANUP(uString[0], c, "i18n_utext_next32", "characters are not same", i18n_utext_destroy(g_utb));

        c = i18n_utext_current32(g_utb);
        PRINT_RESULT_CLEANUP(uString[1], c, "i18n_utext_current32", "characters are not same", i18n_utext_destroy(g_utb));
        i18n_utext_destroy(g_utb);
        return 0;
}
/**
* @testcase				ITc_i18n_utext_previous32_p
* @since_tizen 			        6.0
* @author            	                mohit.m
* @reviewer                             shobhit.v
* @type 				auto
* @scenario				checks the character at a specific positions
* @apitarget			        i18n_utext_previous32
* @apicovered			        i18n_utext_create_for_uchars, i18n_utext_previous32
* @passcase				When i18n_utext_create_for_uchars, i18n_utext_previous32 is successful
* @failcase				If target i18n_utext_create_for_uchars, i18n_utext_previous32 API fails or any precondition and postcondition API fails.
* @precondition			        NA
* @postcondition		        NA
*/
int ITc_i18n_utext_previous32_p(void)
{
        START_TEST_PRINT;
        i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0};
        i18n_utext_h g_utb = NULL;
        i18n_utext_h g_utext = NULL;
        i18n_uchar32 c;
        int nRet;
        int64_t initial_index = 0;

        nRet = i18n_utext_create_for_uchars(g_utext, uString, -1, &g_utb);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_uchars", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_utb, "i18n_utext_create_for_uchars");

        i18n_utext_set_native_index(g_utb, initial_index);
        //Target API
        c = i18n_utext_previous32(g_utb);
        PRINT_RESULT_CLEANUP(I18N_SENTINEL, c, "i18n_utext_next32", "characters are not same", i18n_utext_destroy(g_utb));

        c = i18n_utext_current32(g_utb);
        PRINT_RESULT_CLEANUP(uString[initial_index], c, "i18n_utext_current32", "characters are not same", i18n_utext_destroy(g_utb));
        i18n_utext_destroy(g_utb);
        return 0;
}
/**
* @testcase				ITc_i18n_utext_next32_from_p
* @since_tizen 			        6.0
* @author            	                mohit.m
* @reviewer                             shobhit.v
* @type 				auto
* @scenario				checks the character at a specific positions
* @apitarget			        i18n_utext_next32_from
* @apicovered			        i18n_utext_create_for_uchars, i18n_utext_next32_from
* @passcase				When i18n_utext_create_for_uchars, i18n_utext_next32_from is successful
* @failcase				If target i18n_utext_create_for_uchars, i18n_utext_next32_from API fails or any precondition and postcondition API fails.
* @precondition			        NA
* @postcondition		        NA
*/
int ITc_i18n_utext_next32_from_p(void)
{
        START_TEST_PRINT;
        i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0};
        i18n_utext_h g_utb = NULL;
        i18n_utext_h g_utext = NULL;
        i18n_uchar32 c;
        int nRet;
        int64_t index = 1;

        nRet = i18n_utext_create_for_uchars(g_utext, uString, -1, &g_utb);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_uchars", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_utb, "i18n_utext_create_for_uchars");

        //Target API
        c = i18n_utext_next32_from(g_utb, index);
        PRINT_RESULT_CLEANUP(uString[index], c, "i18n_utext_next32_from", "characters are not same", i18n_utext_destroy(g_utb));
        i18n_utext_destroy(g_utb);
        return 0;
}
/**
* @testcase				ITc_i18n_utext_previous32_from_p
* @since_tizen 			        6.0
* @author            	                mohit.m
* @reviewer                             shobhit.v
* @type 				auto
* @scenario				checks the character at a specific positions
* @apitarget			        i18n_utext_previous32_from
* @apicovered			        i18n_utext_create_for_uchars, i18n_utext_previous32_from
* @passcase				When i18n_utext_create_for_uchars, i18n_utext_previous32_from is successful
* @failcase				If target i18n_utext_create_for_uchars, i18n_utext_previous32_from API fails or any precondition and postcondition API fails.
* @precondition			        NA
* @postcondition		        NA
*/
int ITc_i18n_utext_previous32_from_p(void)
{
        START_TEST_PRINT;
        i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0};
        i18n_utext_h g_utb = NULL;
        i18n_utext_h g_utext = NULL;
        i18n_uchar32 c;
        int nRet;
        int64_t index = 2;

        nRet = i18n_utext_create_for_uchars(g_utext, uString, -1, &g_utb);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_uchars", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_utb, "i18n_utext_create_for_uchars");

        //Target API
        c = i18n_utext_previous32_from(g_utb, index);
        PRINT_RESULT_CLEANUP(uString[index - 1], c, "i18n_utext_previous32_from", "characters are not same", i18n_utext_destroy(g_utb));
        i18n_utext_destroy(g_utb);
        return 0;
}
/**
* @testcase				ITc_i18n_utext_set_get_native_index_p
* @since_tizen 			        6.0
* @author            	                mohit.m
* @reviewer                             shobhit.v
* @type 				auto
* @scenario				checks the character at a specific positions
* @apitarget			        i18n_utext_set_native_index, i18n_utext_get_native_index
* @apicovered			        i18n_utext_create_for_uchars, i18n_utext_set_native_index, i18n_utext_get_native_index
* @passcase				When i18n_utext_create_for_uchars, i18n_utext_set_native_index, i18n_utext_get_native_index is successful
* @failcase				If target i18n_utext_create_for_uchars, i18n_utext_get_native_index, i18n_utext_set_native_index API fails or any precondition and postcondition API fails.
* @precondition			        NA
* @postcondition	        	NA
*/
int ITc_i18n_utext_set_get_native_index_p(void)
{
        START_TEST_PRINT;
        i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0};
        i18n_utext_h g_utb = NULL;
        i18n_utext_h g_utext = NULL;
        int64_t i;
        int nRet;
        int64_t index_first = 1;
        int64_t index_second = 2;

        nRet = i18n_utext_create_for_uchars(g_utext, uString, -1, &g_utb);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_uchars", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_utb, "i18n_utext_create_for_uchars");

        //Target API
        i18n_utext_set_native_index(g_utb, index_second);
        i = i18n_utext_get_native_index(g_utb);
        PRINT_RESULT_CLEANUP(i, index_second, "i18n_utext_get_native_index", "characters are not same", i18n_utext_destroy(g_utb));
        i18n_utext_set_native_index(g_utb, index_first);
        i = i18n_utext_get_native_index(g_utb);
        PRINT_RESULT_CLEANUP(i, index_first, "i18n_utext_get_native_index", "characters are not same", i18n_utext_destroy(g_utb));

        i18n_utext_destroy(g_utb);
        return 0;
}
/**
* @testcase				ITc_i18n_utext_move_index32_p
* @since_tizen 			        6.0
* @author            	                mohit.m
* @reviewer                             shobhit.v
* @type 				auto
* @scenario				checks the character at a specific positions
* @apitarget			        i18n_utext_move_index32
* @apicovered			        i18n_utext_create_for_uchars, i18n_utext_move_index32
* @passcase				When i18n_utext_create_for_uchars, i18n_utext_move_index32 is successful
* @failcase				If target i18n_utext_create_for_uchars, i18n_utext_move_index32 API fails or any precondition and postcondition API fails.
* @precondition			        NA
* @postcondition		        NA
*/
int ITc_i18n_utext_move_index32_p(void)
{
        START_TEST_PRINT;
        i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0};
        i18n_utext_h g_utb = NULL;
        i18n_utext_h g_utext = NULL;
        i18n_ubool b;
        int nRet;
        int64_t initial_index = 0;
        int32_t move_index = 1;
        int32_t move_index_latest = 2;
        int64_t set_index = 1;

        nRet = i18n_utext_create_for_uchars(g_utext, uString, -1, &g_utb);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_uchars", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_utb, "i18n_utext_create_for_uchars");

        i18n_utext_set_native_index(g_utb, initial_index);

        //Target API
        b = i18n_utext_move_index32(g_utb, move_index);
        PRINT_RESULT_CLEANUP(true, b, "i18n_utext_move_index32", "api returned false", i18n_utext_destroy(g_utb));

        i18n_utext_set_native_index(g_utb, set_index);
        b = i18n_utext_move_index32(g_utb, move_index_latest);
        PRINT_RESULT_CLEANUP(true, b, "i18n_utext_move_index32", "api returned false", i18n_utext_destroy(g_utb));

        i18n_utext_destroy(g_utb);
        return 0;
}
/**
* @testcase				ITc_i18n_utext_get_previous_native_index_p
* @since_tizen 			        6.0
* @author            	                mohit.m
* @reviewer                             shobhit.v
* @type 				auto
* @scenario				checks the previous native index
* @apitarget			        i18n_utext_get_previous_native_index
* @apicovered			        i18n_utext_create_for_uchars, i18n_utext_get_previous_native_index
* @passcase				When i18n_utext_create_for_uchars, i18n_utext_get_previous_native_index is successful
* @failcase				If target i18n_utext_create_for_uchars, i18n_utext_get_previous_native_index API fails or any precondition and postcondition API fails.
* @precondition			        NA
* @postcondition		        NA
*/
int ITc_i18n_utext_get_previous_native_index_p(void)
{
        START_TEST_PRINT;
        i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0};
        i18n_utext_h g_utb = NULL;
        i18n_utext_h g_utext = NULL;
        int64_t i;
        int64_t initial_index = 1;
        int nRet;

        nRet = i18n_utext_create_for_uchars(g_utext, uString, -1, &g_utb);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_uchars", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_utb, "i18n_utext_create_for_uchars");

        i18n_utext_set_native_index(g_utb, initial_index);

        //Target API
        i = i18n_utext_get_previous_native_index(g_utb);
        PRINT_RESULT_CLEANUP(i, initial_index - 1, "i18n_utext_get_previous_native_index", "characters are not same", i18n_utext_destroy(g_utb));
        i18n_utext_destroy(g_utb);
        return 0;
}
/**
* @testcase				ITc_i18n_utext_extract_p
* @since_tizen 			        6.0
* @author            	                mohit.m
* @reviewer                             shobhit.v
* @type 				auto
* @scenario				checks the previous native index
* @apitarget			        i18n_utext_extract
* @apicovered			        i18n_utext_create_for_uchars, i18n_utext_extract
* @passcase				When i18n_utext_create_for_uchars, i18n_utext_extract is successful
* @failcase				If target i18n_utext_create_for_uchars, i18n_utext_extract API fails or any precondition and postcondition API fails.
* @precondition			        NA
* @postcondition		        NA
*/
int ITc_i18n_utext_extract_p(void)
{
        START_TEST_PRINT;
        i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0};
        i18n_utext_h g_utb = NULL;
        i18n_utext_h g_utext = NULL;
        int32_t len;
        int64_t native_start = 0;
        int64_t native_limit = 100;
        int32_t dest_capacity = 100;
        int nRet;
        i18n_uchar buf[100];

        nRet = i18n_utext_create_for_uchars(g_utext, uString, -1, &g_utb);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_uchars", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_utb, "i18n_utext_create_for_uchars");

        memset(buf, 0, sizeof(buf));

        //Target API
        nRet = i18n_utext_extract(g_utb, native_start, native_limit, buf, dest_capacity, &len);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_utext_extract", BaseUtilsGetError(nRet), i18n_utext_destroy(g_utb));
        PRINT_RESULT_CLEANUP(len, i18n_ustring_get_length(uString), "i18n_utext_extract", "lengths are not equal", i18n_utext_destroy(g_utb));
        i18n_utext_destroy(g_utb);
        return 0;
}
/**
* @testcase				ITc_i18n_utext_is_writable_p
* @since_tizen 			        6.0
* @author                       	mohit.m
* @reviewer                             shobhit.v
* @type 				auto
* @scenario				checks if the text is replaceable or copiable
* @apitarget			        i18n_utext_is_writable
* @apicovered			        i18n_utext_create_for_uchars, i18n_utext_is_writable
* @passcase				When i18n_utext_create_for_uchars, i18n_utext_is_writable is successful
* @failcase				If target i18n_utext_create_for_uchars, i18n_utext_is_writable API fails or any precondition and postcondition API fails.
* @precondition			        NA
* @postcondition		        NA
*/
int ITc_i18n_utext_is_writable_p(void)
{
        START_TEST_PRINT;
        i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0};
        i18n_utext_h g_utb = NULL;
        i18n_utext_h g_utext = NULL;
        i18n_ubool b;
        int nRet;

        nRet = i18n_utext_create_for_uchars(g_utext, uString, -1, &g_utb);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_uchars", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_utb, "i18n_utext_create_for_uchars");
        //Target API
        //true case is not possible to check
        b = i18n_utext_is_writable(g_utb);
        PRINT_RESULT_CLEANUP(false, b, "i18n_utext_is_writable", "it is not expensive", i18n_utext_destroy(g_utb));
        i18n_utext_destroy(g_utb);
        return 0;
}
/**
* @testcase				ITc_i18n_utext_has_meta_data_p
* @since_tizen 			        6.0
* @author            	                mohit.m
* @reviewer                             shobhit.v
* @type 				auto
* @scenario				checks if the text is replaceable or copiable
* @apitarget			        i18n_utext_has_meta_data
* @apicovered			        i18n_utext_create_for_uchars, i18n_utext_has_meta_data
* @passcase				When i18n_utext_create_for_uchars, i18n_utext_has_meta_data is successful
* @failcase				If target i18n_utext_create_for_uchars, i18n_utext_has_meta_data API fails or any precondition and postcondition API fails.
* @precondition			        NA
* @postcondition	        	NA
*/
int ITc_i18n_utext_has_meta_data_p(void)
{
        START_TEST_PRINT;
        i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0};
        i18n_utext_h g_utb = NULL;
        i18n_utext_h g_utext = NULL;
        i18n_ubool b;
        int nRet;

        nRet = i18n_utext_create_for_uchars(g_utext, uString, -1, &g_utb);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_uchars", BaseUtilsGetError(nRet));

        //Target API
        //true case is not possible to check
        b = i18n_utext_has_meta_data(g_utb);
        PRINT_RESULT_CLEANUP(false, b, "i18n_utext_has_meta_data", "it has meta-data", i18n_utext_destroy(g_utb));
        i18n_utext_destroy(g_utb);
        return 0;
}
/**
* @testcase				ITc_i18n_utext_freeze_p
* @since_tizen 			        6.0
* @author            	                mohit.m
* @reviewer                             shobhit.v
* @type 				auto
* @scenario	                        freezes the utext string
* @apitarget			        i18n_utext_has_meta_data
* @apicovered			        i18n_utext_create_for_uchars, i18n_utext_freeze
* @passcase				When i18n_utext_create_for_uchars, i18n_utext_freeze is successful
* @failcase				If target i18n_utext_create_for_uchars, i18n_utext_freeze API fails or any precondition and postcondition API fails.
* @precondition			        NA
* @postcondition		        NA
*/
int ITc_i18n_utext_freeze_p(void)
{
        START_TEST_PRINT;
        i18n_uchar uString[]  = {0x41, 0x42, 0x43, 0};
        i18n_utext_h g_utb = NULL;
        i18n_utext_h g_utext = NULL;
        i18n_ubool b;
        int nRet;

        nRet = i18n_utext_create_for_uchars(g_utext, uString, -1, &g_utb);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_utext_create_for_uchars", BaseUtilsGetError(nRet));
        //Target API
        i18n_utext_freeze(g_utb);

        b = i18n_utext_is_writable(g_utb);
        PRINT_RESULT_CLEANUP(false, b, "i18n_utext_is_writable", "returned value is true after freezing", i18n_utext_destroy(g_utb));
        i18n_utext_destroy(g_utb);
        return 0;
}
