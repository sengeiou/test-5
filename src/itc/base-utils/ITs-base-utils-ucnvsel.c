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
* @function 		ITs_base_utils_ucnvsel_startup
* @description	 	Called before each test
* @parameter		NA
* @return 	        NA
*/
void ITs_base_utils_ucnvsel_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT start-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif
        int nRet = -1;
	g_hUcnvExcludedSet = NULL;
	nRet = i18n_uset_create_empty(&g_hUcnvExcludedSet);
	if(nRet != I18N_ERROR_NONE)
        {
                g_bBaseUtilsInitFlag = false;
                FPRINTF("\\n[Line : %d][%s] i18n_uset_create_empty failed with error code %s\\n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRet));
        }
        else if(g_hUcnvExcludedSet == NULL)
        {
                g_bBaseUtilsInitFlag = false;
                FPRINTF("\\n[Line : %d][%s] g_hUcnvExcludedSet is null\\n", __LINE__, API_NAMESPACE);
        }
        else
        {
                g_bBaseUtilsInitFlag = true;
        }

	return;
}
/**
* @function 		ITs_base_utils_ucnvsel_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 	        NA
*/
void ITs_base_utils_ucnvsel_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

        int nRet = -1;
        if(g_hUcnvExcludedSet != NULL)
        {
               nRet = i18n_uset_destroy(g_hUcnvExcludedSet);
               if(nRet != I18N_ERROR_NONE)
               {
                      FPRINTF("\\n[Line : %d][%s] i18n_uset_destroy failed with error code %s\\n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRet));
               }
               g_hUcnvExcludedSet = NULL;
        }
        g_bBaseUtilsInitFlag = false;
	return;
}
/*
 * @testcase		ITc_i18n_ucnvsel_create_destroy_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnvsel_create, i18n_ucnvsel_destroy
 * @apicovered          i18n_ucnvsel_create, i18n_ucnvsel_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnvsel_create, i18n_ucnvsel_destroy
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnvsel_create, i18n_ucnvsel_destroy
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnvsel_create_destroy_p(void)
{
        START_TEST;

        int nRet = -1;
        int32_t num_encodings = 0;
        g_UconvSel = NULL;
        const char **pszEncodings = (const char **)malloc(sizeof(char *));

        //Target API
        nRet = i18n_ucnvsel_create(pszEncodings, num_encodings, g_hUcnvExcludedSet, I18N_UCNV_ROUNDTRIP_SET, &g_UconvSel);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_create", BaseUtilsGetError(nRet), FREE_MEMORY(pszEncodings));
        CHECK_HANDLE_CLEANUP(g_UconvSel, "i18n_ucnvsel_create", FREE_MEMORY(pszEncodings));

        //Target API
        nRet = i18n_ucnvsel_destroy(g_UconvSel);
        PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_destroy", BaseUtilsGetError(nRet), FREE_MEMORY(pszEncodings));

        FREE_MEMORY(pszEncodings);
        return 0;
}
/*
 * @testcase		ITc_i18n_ucnvsel_create_from_serialized_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnvsel_create_from_serialized
 * @apicovered          i18n_ucsdet_create, i18n_ucnvsel_serialize, i18n_ucnvsel_create_from_serialized, i18n_ucsdet_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnvsel_create_from_serialized
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnvsel_create_from_serialized
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnvsel_create_from_serialized_p(void)
{
        START_TEST;
        int nRet = -1;
        const char **pszEncodings = NULL;
        int32_t num_encodings = 0;
        int32_t serial_length = -1;
        int32_t serial_length_create = -1;
        char *pszStrBuffer = NULL;
        g_UconvSel = NULL;

        nRet = i18n_ucnvsel_create(pszEncodings, num_encodings, g_hUcnvExcludedSet, I18N_UCNV_ROUNDTRIP_AND_FALLBACK_SET, &g_UconvSel);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_UconvSel, "i18n_ucnvsel_create");

        nRet = i18n_ucnvsel_serialize(g_UconvSel, pszStrBuffer, 0, &serial_length);
	PRINT_RESULT_CLEANUP(I18N_ERROR_BUFFER_OVERFLOW, nRet, "i18n_ucnvsel_serialize", BaseUtilsGetError(nRet), i18n_ucnvsel_destroy(g_UconvSel));
        if(serial_length < 0)
        {
                FPRINTF("\\n[Line : %d][%s] i18n_ucnvsel_serialize failed ,serial_length is not correct \n", __LINE__, API_NAMESPACE);
                nRet = i18n_ucnvsel_destroy(g_UconvSel);
                PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_destroy", BaseUtilsGetError(nRet));
                return 1;
        }

        pszStrBuffer = (char *)malloc(serial_length);
	nRet = i18n_ucnvsel_serialize(g_UconvSel, pszStrBuffer, serial_length, &serial_length_create);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_serialize", BaseUtilsGetError(nRet), i18n_ucnvsel_destroy(g_UconvSel); FREE_MEMORY(pszStrBuffer));
        if(serial_length_create < 0)
        {
                FPRINTF("\\n[Line : %d][%s] i18n_ucnvsel_serialize failed ,serial_length_create is not correct \n", __LINE__, API_NAMESPACE);
                nRet = i18n_ucnvsel_destroy(g_UconvSel);
                PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_destroy", BaseUtilsGetError(nRet));
                FREE_MEMORY(pszStrBuffer);
                return 1;
        }

        nRet = i18n_ucnvsel_destroy(g_UconvSel);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_destroy", BaseUtilsGetError(nRet));
        g_UconvSel = NULL;

        nRet = i18n_ucnvsel_create_from_serialized(pszStrBuffer, serial_length, &g_UconvSel);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_create_from_serialized", BaseUtilsGetError(nRet), FREE_MEMORY(pszStrBuffer));
        CHECK_HANDLE_CLEANUP(g_UconvSel, "i18n_ucnvsel_create_from_serialized", FREE_MEMORY(pszStrBuffer));

        nRet = i18n_ucnvsel_destroy(g_UconvSel);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_destroy", BaseUtilsGetError(nRet));

        FREE_MEMORY(pszStrBuffer);

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnvsel_serialize_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnvsel_serialize
 * @apicovered          i18n_ucnvsel_create, i18n_ucnvsel_serialize, i18n_ucnvsel_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnvsel_serialize
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnvsel_serialize
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnvsel_serialize_p(void)
{
        START_TEST;
        int nRet = -1;
        const char **pszEncodings = NULL;
        int32_t num_encodings = 0;
        int32_t serial_length = -1;
        int32_t serial_length_create = -1;
        char *pszStrBuffer = NULL;
        void *pszBuffer = NULL;
        g_UconvSel = NULL;

        nRet = i18n_ucnvsel_create(pszEncodings, num_encodings, g_hUcnvExcludedSet, I18N_UCNV_ROUNDTRIP_SET, &g_UconvSel);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_UconvSel, "i18n_ucnvsel_create");

        //Target API
        nRet = i18n_ucnvsel_serialize(g_UconvSel, pszStrBuffer, 0, &serial_length);
	PRINT_RESULT_CLEANUP(I18N_ERROR_BUFFER_OVERFLOW, nRet, "i18n_ucnvsel_serialize", BaseUtilsGetError(nRet), i18n_ucnvsel_destroy(g_UconvSel));
        if(serial_length < 0)
        {
                FPRINTF("\\n[Line : %d][%s] i18n_ucnvsel_serialize failed ,serial_length is not correct \n", __LINE__, API_NAMESPACE);
                nRet = i18n_ucnvsel_destroy(g_UconvSel);
                PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_destroy", BaseUtilsGetError(nRet));
                return 1;
        }

        pszStrBuffer = (char *)malloc(sizeof(char) * serial_length);

        //Target API
	nRet = i18n_ucnvsel_serialize(g_UconvSel, pszStrBuffer, serial_length, &serial_length_create);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_serialize", BaseUtilsGetError(nRet), i18n_ucnvsel_destroy(g_UconvSel); FREE_MEMORY(pszStrBuffer));
        if(serial_length_create < 0)
        {
                FPRINTF("\\n[Line : %d][%s] i18n_ucnvsel_serialize failed ,serial_length_create is not correct \n", __LINE__, API_NAMESPACE);
                nRet = i18n_ucnvsel_destroy(g_UconvSel);
                PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_destroy", BaseUtilsGetError(nRet));
                FREE_MEMORY(pszStrBuffer);
                return 1;
        }

        nRet = i18n_ucnvsel_destroy(g_UconvSel);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_destroy", BaseUtilsGetError(nRet));
        g_UconvSel = NULL;

        FREE_MEMORY(pszStrBuffer);
        return 0;
}
/*
 * @testcase		ITc_i18n_ucnvsel_select_for_string_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnvsel_select_for_string
 * @apicovered          i18n_ucnvsel_create, i18n_ucnvsel_select_for_string, i18n_ucnvsel_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnvsel_select_for_string
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnvsel_select_for_string
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnvsel_select_for_string_p(void)
{
        START_TEST;
        int nRet = -1;
        i18n_uenumeration_h hEnumeration = NULL;
	const char *pszString = "Hello World!";
	const i18n_uchar szUcharStr[I18N_UCHAR_CAPACITY] = {0,};
        void *pszBuffer = NULL;
	int32_t len = -1;
        int32_t string_length = 5;
        int32_t num_encodings = 0;
	i18n_error_code_e status;
        g_UconvSel = NULL;

        i18n_ustring_from_UTF8((i18n_uchar *)szUcharStr, I18N_UCHAR_CAPACITY, &len, pszString, string_length, &status);
	PRINT_RESULT(I18N_ERROR_NONE, status, "i18n_ustring_from_UTF8", "returned value is not correct");
        if(len < 0)
        {
                FPRINTF("\\n[Line : %d][%s] i18n_ustring_from_UTF8 failed ,len is not correct \n", __LINE__, API_NAMESPACE);
                return 1;
        }

        nRet = i18n_ucnvsel_create(pszBuffer, num_encodings, g_hUcnvExcludedSet, I18N_UCNV_ROUNDTRIP_AND_FALLBACK_SET, &g_UconvSel);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_UconvSel, "i18n_ucnvsel_create");

        //Target API
        nRet = i18n_ucnvsel_select_for_string(g_UconvSel, szUcharStr, len, &hEnumeration);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_select_for_string", BaseUtilsGetError(nRet), i18n_ucnvsel_destroy(g_UconvSel));
        CHECK_HANDLE_CLEANUP(hEnumeration, "i18n_ucnvsel_select_for_string", i18n_ucnvsel_destroy(g_UconvSel));

        nRet = i18n_ucnvsel_destroy(g_UconvSel);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_destroy", BaseUtilsGetError(nRet));
        g_UconvSel = NULL;

        return 0;
}
/*
 * @testcase		ITc_i18n_ucnvsel_select_for_utf8_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ucnvsel_select_for_utf8
 * @apicovered          i18n_ucnvsel_create, i18n_ucnvsel_select_for_utf8, i18n_ucnvsel_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_ucnvsel_select_for_utf8
 * @failcase		I18N_ERROR_NONE not returned by i18n_ucnvsel_select_for_utf8
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ucnvsel_select_for_utf8_p(void)
{
        START_TEST;
        int nRet = -1;
        i18n_uenumeration_h hEnumeration = NULL;
	const char *pszString = "Hello world!";
        void *pszBuffer = NULL;
        int32_t string_length = 5;
        int32_t num_encodings = 0;
        g_UconvSel = NULL;

        nRet = i18n_ucnvsel_create(pszBuffer, num_encodings, g_hUcnvExcludedSet, I18N_UCNV_ROUNDTRIP_AND_FALLBACK_SET, &g_UconvSel);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_create", BaseUtilsGetError(nRet));
        CHECK_HANDLE(g_UconvSel, "i18n_ucnvsel_create");

        //Target API
	nRet = i18n_ucnvsel_select_for_utf8(g_UconvSel, pszString, string_length, &hEnumeration);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_select_for_utf8", BaseUtilsGetError(nRet), i18n_ucnvsel_destroy(g_UconvSel));
        CHECK_HANDLE_CLEANUP(g_UconvSel, "i18n_ucnvsel_select_for_utf8", i18n_ucnvsel_destroy(g_UconvSel));

        nRet = i18n_ucnvsel_destroy(g_UconvSel);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnvsel_destroy", BaseUtilsGetError(nRet));
        g_UconvSel = NULL;

        return 0;
}
