//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
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
//& set: BaseUtilsUnormalization

/**
* @function 		ITs_base_utils_unormalization_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_base_utils_unormalization_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bBaseUtilsInitFlag = true;
	return;
}

/**
* @function 		ITs_base_utils_unormalization_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_unormalization_cleanup(void)
{
	g_bBaseUtilsInitFlag = false;

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& type: auto
//& purpose: Gets a Unormalizer instance and Writes the normalized form of the source string to the destination string.
/**
* @testcase				ITc_i18n_unormalization_get_instance_normalize_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets a Unormalizer instance
* 						Writes the normalized form of the source string to the destination string(replacing its contents). The source and destination strings must be different buffers.. 	
* @apitarget			i18n_unormalization_get_instance, i18n_unormalization_normalize
* @apicovered			i18n_unormalization_get_instance, i18n_unormalization_normalize, i18n_ustring_copy_ua_n, i18n_ustring_get_length
* @passcase				When i18n_unormalization_get_instance, i18n_unormalization_normalize are successful
* @failcase				If target i18n_unormalization_get_instance or i18n_unormalization_normalize fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unormalization_get_instance_normalize_p(void)
{	
	START_TEST;

	i18n_uchar uSourceStr[I18N_UCHAR_CAPACITY] = { 0, };
	int nSourceLength = -1;
	i18n_uchar *pRet = i18n_ustring_copy_ua_n(uSourceStr, (char *)SOURCE_STRING, strlen(SOURCE_STRING));
	nSourceLength = i18n_ustring_get_length(uSourceStr);
	if ( pRet == NULL || nSourceLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n Failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_unormalization_mode_e eUnormalizationMode[] = {	I18N_UNORMALIZATION_COMPOSE, 
		I18N_UNORMALIZATION_DECOMPOSE,
		I18N_UNORMALIZATION_FCD,
		I18N_UNORMALIZATION_COMPOSE_CONTIGUOUS};
	int nEnumSize = sizeof(eUnormalizationMode) / sizeof(eUnormalizationMode[0]);
	int nEnumCounter = 0;
	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		i18n_unormalizer_h uNormalizer = NULL;
		FPRINTF("[Line : %d][%s] Executing i18n_unormalization_get_instance with Unormalization-Mode(%s) and NAME =%s\\n", __LINE__, API_NAMESPACE, UnormalizationModeValue(eUnormalizationMode[nEnumCounter]), UNORMALIZATION_NFC_NAME);
		int nRetVal = i18n_unormalization_get_instance(NULL, UNORMALIZATION_NFC_NAME, eUnormalizationMode[nEnumCounter], &uNormalizer);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_unormalization_get_instance", BaseUtilsGetError(nRetVal));
		CHECK_HANDLE(uNormalizer, "i18n_unormalization_get_instance");

		i18n_uchar uDestinationStr[I18N_UCHAR_CAPACITY] = { 0, };
		int nDestinationLength = -1;
		nRetVal = i18n_unormalization_normalize(uNormalizer, uSourceStr, nSourceLength, uDestinationStr, I18N_UCHAR_CAPACITY, &nDestinationLength);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_unormalization_normalize", BaseUtilsGetError(nRetVal));
		CHECK_RETURN_VAL(nDestinationLength, "i18n_unormalization_normalize");
	}
	return 0;
}
/*
 * @testcase		ITc_i18n_unormalization_get_nfc_instance_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unormalization_get_nfc_instance
 * @apicovered		i18n_unormalization_get_nfc_instance
 * @passcase		I18N_ERROR_NONE returned by i18n_unormalization_get_nfc_instance
 * @failcase		I18N_ERROR_NONE not returned by i18n_unormalization_get_nfc_instance
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unormalization_get_nfc_instance_p(void)
{
        START_TEST_PRINT;
        int nRet = -1;
        i18n_unormalizer_h h_normalizer = NULL;

        //Target API
        nRet = i18n_unormalization_get_nfc_instance(&h_normalizer);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_nfc_instance", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_normalizer, "i18n_unormalization_get_nfc_instance");
        return 0;
}
/*
 * @testcase		ITc_i18n_unormalization_get_nfd_instance_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unormalization_get_nfd_instance
 * @apicovered		i18n_unormalization_get_nfd_instance
 * @passcase		I18N_ERROR_NONE returned by i18n_unormalization_get_nfd_instance
 * @failcase		I18N_ERROR_NONE not returned by i18n_unormalization_get_nfd_instance
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unormalization_get_nfd_instance_p(void)
{
        START_TEST_PRINT;
        int nRet = -1;
        i18n_unormalizer_h h_normalizer = NULL;

        //Target API
        nRet = i18n_unormalization_get_nfd_instance(&h_normalizer);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_nfd_instance", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_normalizer, "i18n_unormalization_get_nfd_instance");
        return 0;
}
/*
 * @testcase		ITc_i18n_unormalization_get_nfkc_instance_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unormalization_get_nfkc_instance
 * @apicovered		i18n_unormalization_get_nfkc_instance
 * @passcase		I18N_ERROR_NONE returned by i18n_unormalization_get_nfkc_instance
 * @failcase		I18N_ERROR_NONE not returned by i18n_unormalization_get_nfkc_instance
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unormalization_get_nfkc_instance_p(void)
{
        START_TEST_PRINT;
        i18n_unormalizer_h h_normalizer = NULL;
        int nRet = -1;

        //Target API
	nRet = i18n_unormalization_get_nfkc_instance(&h_normalizer);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_nfkc_instance", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_normalizer, "i18n_unormalization_get_nfkc_instance");
	return 0;
}
/*
 * @testcase		ITc_i18n_unormalization_get_nfkc_casefold_instance_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unormalization_get_nfkc_casefold_instance
 * @apicovered		i18n_unormalization_get_nfkc_casefold_instance
 * @passcase		I18N_ERROR_NONE returned by i18n_unormalization_get_nfkc_casefold_instance
 * @failcase		I18N_ERROR_NONE not returned by i18n_unormalization_get_nfkc_casefold_instance
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unormalization_get_nfkc_casefold_instance_p(void)
{
        START_TEST_PRINT;
        i18n_unormalizer_h h_normalizer = NULL;
        int nRet = -1;

        //Target API
	nRet = i18n_unormalization_get_nfkc_casefold_instance(&h_normalizer);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_nfkc_casefold_instance", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_normalizer, "i18n_unormalization_get_nfkc_casefold_instance");
	return 0;
}
/*
 * @testcase		ITc_i18n_unormalization_get_nfkd_instance_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unormalization_get_nfkd_instance
 * @apicovered		i18n_unormalization_get_nfkd_instance
 * @passcase		I18N_ERROR_NONE returned by i18n_unormalization_get_nfkd_instance
 * @failcase		I18N_ERROR_NONE not returned by i18n_unormalization_get_nfkd_instance
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unormalization_get_nfkd_instance_p(void)
{
        START_TEST_PRINT;
        i18n_unormalizer_h h_normalizer = NULL;
        int nRet = -1;

        //Target API
	nRet = i18n_unormalization_get_nfkd_instance(&h_normalizer);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_nfkd_instance", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_normalizer, "i18n_unormalization_get_nfkd_instance");
	return 0;
}
/*
 * @testcase		ITc_i18n_unormalization_create_filtered_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unormalization_create_filtered
 * @apicovered		i18n_unormalization_create_filtered, i18n_unormalization_get_nfc_instance
 * @passcase		I18N_ERROR_NONE returned by i18n_unormalization_create_filtered
 * @failcase		I18N_ERROR_NONE not returned by i18n_unormalization_create_filtered
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unormalization_create_filtered_p(void)
{
        START_TEST_PRINT;
        i18n_unormalizer_h h_nfc = NULL;
        i18n_unormalizer_h h_normalizer = NULL;
        i18n_uset_h filter_set;
        int nRet = -1;
	nRet = i18n_unormalization_get_nfc_instance(&h_nfc);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_nfc_instance", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_nfc, "i18n_unormalization_get_nfc_instance");

        //Target API
	nRet = i18n_unormalization_create_filtered(h_nfc, &filter_set, &h_normalizer);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_create_filtered", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_normalizer, "i18n_unormalization_create_filtered");
	return 0;
}
/*
 * @testcase		ITc_i18n_unormalization_destroy_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unormalization_destroy
 * @apicovered		i18n_unormalization_destroy, i18n_unormalization_get_nfc_instance
 * @passcase		I18N_ERROR_NONE returned by i18n_unormalization_destroy
 * @failcase		I18N_ERROR_NONE not returned by i18n_unormalization_destroy
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unormalization_destroy_p(void)
{
        START_TEST_PRINT;
        i18n_unormalizer_h h_nfc = NULL;
        i18n_unormalizer_h h_normalizer = NULL;
        i18n_uset_h filter_set;
        int nRet = -1;
	nRet = i18n_unormalization_get_nfc_instance(&h_nfc);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_nfc_instance", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_nfc, "i18n_unormalization_get_nfc_instance");

	nRet = i18n_unormalization_create_filtered(h_nfc, &filter_set, &h_normalizer);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_create_filtered", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_normalizer, "i18n_unormalization_create_filtered");

        //Target API
        nRet = i18n_unormalization_destroy(h_normalizer);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_unormalization_normalize_second_and_append_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unormalization_normalize_second_and_append
 * @apicovered		i18n_unormalization_normalize_second_and_append, i18n_unormalization_get_nfc_instance
 * @passcase		I18N_ERROR_NONE returned by i18n_unormalization_normalize_second_and_append
 * @failcase		I18N_ERROR_NONE not returned by i18n_unormalization_normalize_second_and_append
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unormalization_normalize_second_and_append_p(void)
{
        START_TEST_PRINT;
        i18n_unormalizer_h h_normalizer = NULL;
        int nRet = -1;

	nRet = i18n_unormalization_get_nfc_instance(&h_normalizer);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_nfc_instance", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_normalizer, "i18n_unormalization_get_nfc_instance");

        i18n_uchar a[20] = { 0x61, 0x62, 0x63, 0x41, 0x327, 0 };
	i18n_uchar b[]={ 0x30A, 0x64, 0x65, 0x66, 0 };
        i18n_uchar expected[]={ 0x61, 0x62, 0x63, 0xC5, 0x327, 0x64, 0x65, 0x66 };

        int32_t length = -1;
        int32_t len_of_array = (int32_t)(sizeof(a)/sizeof(a[0]));
        int32_t len_of_expected = (int32_t)(sizeof(expected)/sizeof(expected[0]));

        //Target API
	nRet = i18n_unormalization_normalize_second_and_append(h_normalizer, a, -1, len_of_array, b, -1, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_normalize_second_and_append", BaseUtilsGetError(nRet));
	PRINT_RESULT(length, len_of_expected, "i18n_unormalization_normalize_second_and_append", "obtained length is incorrect");

        int i;
        for(i = 0; i < length; i++)
        {
                PRINT_RESULT(a[i], expected[i], "i18n_unormalization_normalize_second_and_append", "values obtained are not correct");
        }
        return 0;

}
/*
 * @testcase		ITc_i18n_unormalization_append_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unormalization_append
 * @apicovered		i18n_unormalization_append
 * @passcase		I18N_ERROR_NONE returned by i18n_unormalization_append
 * @failcase		I18N_ERROR_NONE not returned by i18n_unormalization_append
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unormalization_append_p(void)
{
        START_TEST_PRINT;
        i18n_unormalizer_h h_normalizer = NULL;
        int nRet = -1;

	nRet = i18n_unormalization_get_nfc_instance(&h_normalizer);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_nfc_instance", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_normalizer, "i18n_unormalization_get_nfc_instance");

        i18n_uchar a[20] = { 0x61, 0x62, 0x63, 0x41, 0x327, 0 };
        i18n_uchar b[]={ 0x30A, 0x64, 0x65, 0x66, 0 };
        i18n_uchar expected[]={ 0x61, 0x62, 0x63, 0xC5, 0x327, 0x64, 0x65, 0x66 };

        int32_t length = -1;
        int32_t len_of_array = (int32_t)(sizeof(a)/sizeof(a[0]));
        int32_t len_of_expected = (int32_t)(sizeof(expected)/sizeof(expected[0]));

        //Target API
	nRet = i18n_unormalization_append(h_normalizer, a, -1, len_of_array, b, -1, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_append", BaseUtilsGetError(nRet));
	PRINT_RESULT(length, len_of_expected, "i18n_unormalization_append", "obtained length is incorrect");

        int i;
        for(i = 0; i < length; i++)
        {
                PRINT_RESULT(a[i], expected[i], "i18n_unormalization_append", "values obtained are not correct");
        }
        return 0;
}
/*
 * @testcase		ITc_i18n_unormalization_get_decomposition_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unormalization_get_decomposition
 * @apicovered		i18n_unormalization_get_decomposition
 * @passcase		I18N_ERROR_NONE returned by i18n_unormalization_get_decomposition
 * @failcase		I18N_ERROR_NONE not returned by i18n_unormalization_get_decomposition
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unormalization_get_decomposition_p(void)
{
        START_TEST_PRINT;
        i18n_unormalizer_h h_normalizer = NULL;
        int nRet = -1;

	nRet = i18n_unormalization_get_instance(NULL, "nfc", I18N_UNORMALIZATION_COMPOSE_CONTIGUOUS, &h_normalizer);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_instance", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_normalizer, "i18n_unormalization_get_nfc_instance");

        i18n_uchar decomp[I18N_UCHAR_CAPACITY];
	int32_t length = -1;
        int32_t expected_length;
        int i;
        //Target API
	nRet = i18n_unormalization_get_decomposition(h_normalizer, 0x20, decomp, I18N_UCHAR_CAPACITY, &length);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_decomposition", BaseUtilsGetError(nRet));

        length = -1;
        nRet = i18n_unormalization_get_decomposition(h_normalizer, 0xe4, decomp, I18N_UCHAR_CAPACITY, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_decomposition", BaseUtilsGetError(nRet));
        if(length < 0)
        {
                FPRINTF("[Line : %d][%s] error returned = length returned is not valid\\n", __LINE__, API_NAMESPACE);
                return 1;
        }
        i18n_uchar expected[] = {0x61, 0x308, 0};
        expected_length = 2;

        PRINT_RESULT(length, expected_length, "i18n_unormalization_get_decomposition", "returned length is not correct");
        for(i = 0; i <= length; i++)
        {
                PRINT_RESULT(decomp[i], expected[i], "i18n_unormalization_get_decomposition", "obtained values are not correct");
        }


        length = -1;
        nRet = i18n_unormalization_get_decomposition(h_normalizer, 0xac01, decomp, I18N_UCHAR_CAPACITY, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_decomposition", BaseUtilsGetError(nRet));
        if(length < 0)
        {
                FPRINTF("[Line : %d][%s] error returned = length returned is invalid\\n", __LINE__, API_NAMESPACE);
                return 1;
        }
        i18n_uchar expected_new[] = {0x1100, 0x1161, 0x11a8, 0};
        expected_length = 3;

        PRINT_RESULT(length, expected_length, "i18n_unormalization_get_decomposition", "returned length is not correct");
        for(i = 0; i <= length; i++)
        {
                PRINT_RESULT(decomp[i], expected_new[i], "i18n_unormalization_get_decomposition", "obtained values are not correct");
        }

        return 0;
}
/*
 * @testcase		ITc_i18n_unormalization_get_raw_decomposition_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unormalization_get_raw_decomposition
 * @apicovered		i18n_unormalization_get_raw_decomposition, i18n_unormalization_get_nfkc_instance
 * @passcase		I18N_ERROR_NONE returned by i18n_unormalization_get_raw_decomposition
 * @failcase		I18N_ERROR_NONE not returned by i18n_unormalization_get_raw_decomposition
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unormalization_get_raw_decomposition_p(void)
{
        START_TEST_PRINT;
        i18n_unormalizer_h h_normalizer = NULL;
        int nRet = -1;

	nRet = i18n_unormalization_get_nfkc_instance(&h_normalizer);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_nfkc_instance", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_normalizer, "i18n_unormalization_get_nfkc_instance");

        i18n_uchar decomp[I18N_UCHAR_CAPACITY];
	int32_t length = -1;
        int32_t expected_length;
        int i;
        //Target API
	nRet = i18n_unormalization_get_raw_decomposition(h_normalizer, 0x20, decomp, I18N_UCHAR_CAPACITY, &length);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_raw_decomposition", BaseUtilsGetError(nRet));

        length = -1;
        nRet = i18n_unormalization_get_raw_decomposition(h_normalizer, 0xe4, decomp, I18N_UCHAR_CAPACITY, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_raw_decomposition", BaseUtilsGetError(nRet));
        if(length < 0)
        {
                FPRINTF("[Line : %d][%s] error returned = length returned is invalid\\n", __LINE__, API_NAMESPACE);
                return 1;
        }
        i18n_uchar expected[] = {0x61, 0x308, 0};
        expected_length = 2;

        PRINT_RESULT(length, expected_length, "i18n_unormalization_get_raw_decomposition", "returned length is not correct");
        for(i = 0; i <= length; i++)
        {
                PRINT_RESULT(decomp[i], expected[i], "i18n_unormalization_get_raw_decomposition", "obtained values are not correct");
        }

        length = -1;
        nRet = i18n_unormalization_get_raw_decomposition(h_normalizer, 0x1e08, decomp, I18N_UCHAR_CAPACITY, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_raw_decomposition", BaseUtilsGetError(nRet));
        if(length < 0)
        {
                FPRINTF("[Line : %d][%s] error returned = length returned is invalid\\n", __LINE__, API_NAMESPACE);
                return 1;
        }
        i18n_uchar expected_2[] = {0xc7, 0x301, 0};
        expected_length = 2;

        PRINT_RESULT(length, expected_length, "i18n_unormalization_get_raw_decomposition", "returned length is not correct");
        for(i = 0; i <= length; i++)
        {
                PRINT_RESULT(decomp[i], expected_2[i], "i18n_unormalization_get_raw_decomposition", "obtained values are not correct");
        }

        length = -1;
        nRet = i18n_unormalization_get_raw_decomposition(h_normalizer, 0x212b, decomp, I18N_UCHAR_CAPACITY, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_raw_decomposition", BaseUtilsGetError(nRet));
        if(length < 0)
        {
                FPRINTF("[Line : %d][%s] error returned = length returned is invalid\\n", __LINE__, API_NAMESPACE);
                return 1;
        }
        i18n_uchar expected_3[] = {0xc5, 0};
        expected_length = 1;

        PRINT_RESULT(length, expected_length, "i18n_unormalization_get_raw_decomposition", "returned length is not correct");
        for(i = 0; i <= length; i++)
        {
                PRINT_RESULT(decomp[i], expected_3[i], "i18n_unormalization_get_raw_decomposition", "obtained values are not correct");
        }

        length = -1;
        nRet = i18n_unormalization_get_raw_decomposition(h_normalizer, 0xac00, decomp, I18N_UCHAR_CAPACITY, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_raw_decomposition", BaseUtilsGetError(nRet));
        if(length < 0)
        {
                FPRINTF("[Line : %d][%s] error returned = length returned is invalid\\n", __LINE__, API_NAMESPACE);
                return 1;
        }
        i18n_uchar expected_4[] = {0x1100, 0x1161, 0};
        expected_length = 2;

        PRINT_RESULT(length, expected_length, "i18n_unormalization_get_raw_decomposition", "returned length is not correct");
        for(i = 0; i <= length; i++)
        {
                PRINT_RESULT(decomp[i], expected_4[i], "i18n_unormalization_get_raw_decomposition", "obtained values are not correct");
        }

        length = -1;
        nRet = i18n_unormalization_get_raw_decomposition(h_normalizer, 0xac01, decomp, I18N_UCHAR_CAPACITY, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_raw_decomposition", BaseUtilsGetError(nRet));
        if(length < 0)
        {
                FPRINTF("[Line : %d][%s] error returned = length returned is invalid\\n", __LINE__, API_NAMESPACE);
                return 1;
        }
        i18n_uchar expected_5[] = {0xac00, 0x11a8, 0};
        expected_length = 2;

        PRINT_RESULT(length, expected_length, "i18n_unormalization_get_raw_decomposition", "returned length is not correct");
        for(i = 0; i <= length; i++)
        {
                PRINT_RESULT(decomp[i], expected_5[i], "i18n_unormalization_get_raw_decomposition", "obtained values are not correct");
        }

        return 0;
}
/*
 * @testcase		ITc_i18n_unormalization_compose_pair_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unormalization_compose_pair
 * @apicovered		i18n_unormalization_compose_pair
 * @passcase		I18N_ERROR_NONE returned by i18n_unormalization_compose_pair
 * @failcase		I18N_ERROR_NONE not returned by i18n_unormalization_compose_pair
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unormalization_compose_pair_p(void)
{
        START_TEST_PRINT;
        i18n_unormalizer_h h_normalizer = NULL;
        int nRet = -1;

	nRet = i18n_unormalization_get_nfc_instance(&h_normalizer);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_nfc_instance", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_normalizer, "i18n_unormalization_get_nfc_instance");

        i18n_uchar a = 0x1100;
	i18n_uchar b = 0x1161;
	i18n_uchar composite = 0xac00;
        i18n_uchar32 result;

        //Target API
	nRet = i18n_unormalization_compose_pair(h_normalizer, a, b, &result);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_compose_pair", BaseUtilsGetError(nRet));
	PRINT_RESULT(result, composite, "i18n_unormalization_compose_pair", "obtained value is incorrect");
        return 0;
}
/*
 * @testcase		ITc_i18n_unormalization_is_normalized_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unormalization_is_normalized
 * @apicovered		i18n_unormalization_is_normalized, i18n_unormalization_get_nfc_instance
 * @passcase		I18N_ERROR_NONE returned by i18n_unormalization_is_normalized
 * @failcase		I18N_ERROR_NONE not returned by i18n_unormalization_is_normalized
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unormalization_is_normalized_p(void)
{
        START_TEST_PRINT;
        i18n_unormalizer_h h_normalizer = NULL;
        int nRet = -1;

	nRet = i18n_unormalization_get_nfc_instance(&h_normalizer);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_nfc_instance", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_normalizer, "i18n_unormalization_get_nfc_instance");

        i18n_uchar src[3] = {0xAC00, 0xAC01, 0};
        i18n_ubool result = false;

        //Target API
	nRet = i18n_unormalization_is_normalized(h_normalizer, src, 1, &result);
        PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_is_normalized", BaseUtilsGetError(nRet));
	PRINT_RESULT(true, result, "i18n_unormalization_is_normalized", "obtained value is not correct");

        return 0;
}
/*
 * @testcase		ITc_i18n_unormalization_quick_check_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unormalization_quick_check
 * @apicovered		i18n_unormalization_quick_check, i18n_unormalization_get_nfd_instance
 * @passcase		I18N_ERROR_NONE returned by i18n_unormalization_quick_check
 * @failcase		I18N_ERROR_NONE not returned by i18n_unormalization_quick_check
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unormalization_quick_check_p(void)
{
        START_TEST_PRINT;
        i18n_unormalizer_h h_normalizer = NULL;
        int nRet = -1;
        int nCount = 10;

	nRet = i18n_unormalization_get_nfd_instance(&h_normalizer);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_nfd_instance", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_normalizer, "i18n_unormalization_get_nfd_instance");

        i18n_uchar CPnfd[] = {0x00C6, 0x017F, 0x0F74, 0x1000, 0x1E9A,0x2261, 0x3075, 0x4000, 0x5000, 0xF000};
        i18n_unormalization_check_result_e result;
	int i;
        for(i = 0; i < nCount; i++)
        {
                //Target API
                nRet = i18n_unormalization_quick_check(h_normalizer, &(CPnfd[i]), 1, &result);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_quick_check", BaseUtilsGetError(nRet));
		PRINT_RESULT(result, I18N_UNORMALIZATION_YES, "i18n_unormalization_quick_check", "obtained value is not correct");
        }
        return 0;

}
/*
 * @testcase		ITc_i18n_unormalization_span_quick_check_yes_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unormalization_span_quick_check_yes
 * @apicovered		i18n_unormalization_span_quick_check_yes
 * @passcase		I18N_ERROR_NONE returned by i18n_unormalization_span_quick_check_yes
 * @failcase		I18N_ERROR_NONE not returned by i18n_unormalization_span_quick_check_yes
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unormalization_span_quick_check_yes_p(void)
{
        START_TEST_PRINT;
        i18n_unormalizer_h h_normalizer = NULL;
        int nRet = -1;

	nRet = i18n_unormalization_get_nfd_instance(&h_normalizer);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_nfd_instance", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_normalizer, "i18n_unormalization_get_nfd_instance");

        i18n_uchar CPnfd[] = {0x00C6, 0x017F, 0x0F74, 0x1000, 0x1E9A, 0x2261, 0x3075, 0x4000, 0x5000, 0xF000};
        int32_t result;
        int i;
        for(i = 0; i < 10; i++)
        {
                //Target API
                nRet = i18n_unormalization_span_quick_check_yes(h_normalizer, &(CPnfd[i]), 1, &result);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_span_quick_check_yes", BaseUtilsGetError(nRet));
		PRINT_RESULT(result, 1, "i18n_unormalization_span_quick_check_yes", "obtained result is not correct");
        }
        return 0;
}
/*
 * @testcase		ITc_i18n_unormalizer_has_boundary_before_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unormalizer_has_boundary_before
 * @apicovered		i18n_unormalization_get_nfd_instance, i18n_unormalizer_has_boundary_before
 * @passcase		I18N_ERROR_NONE returned by i18n_unormalizer_has_boundary_before
 * @failcase		I18N_ERROR_NONE not returned by i18n_unormalizer_has_boundary_before
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unormalizer_has_boundary_before_p(void)
{
        START_TEST_PRINT;
        i18n_unormalizer_h h_normalizer = NULL;
        int nRet = -1;

	nRet = i18n_unormalization_get_nfd_instance(&h_normalizer);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_nfd_instance", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_normalizer, "i18n_unormalization_get_nfd_instance");

        i18n_ubool result = false;

        //Target API
	nRet = i18n_unormalizer_has_boundary_before(h_normalizer, 0xad, &result);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalizer_has_boundary_before", BaseUtilsGetError(nRet));
	PRINT_RESULT(true, result, "i18n_unormalizer_has_boundary_before", "obtained result is not correct");

	return 0;
}
/*
 * @testcase		ITc_i18n_unormalizer_has_boundary_after_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unormalizer_has_boundary_after
 * @apicovered		i18n_unormalizer_has_boundary_after, i18n_unormalization_get_nfd_instance
 * @passcase		I18N_ERROR_NONE returned by i18n_unormalizer_has_boundary_after
 * @failcase		I18N_ERROR_NONE not returned by i18n_unormalizer_has_boundary_after
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unormalizer_has_boundary_after_p(void)
{
        START_TEST_PRINT;
        i18n_unormalizer_h h_normalizer = NULL;
        int nRet = -1;

	nRet = i18n_unormalization_get_nfd_instance(&h_normalizer);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_nfd_instance", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_normalizer, "i18n_unormalization_get_nfd_instance");

        i18n_ubool result = false;

        //Target API
	nRet = i18n_unormalizer_has_boundary_after(h_normalizer, 0xad, &result);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalizer_has_boundary_after", BaseUtilsGetError(nRet));
	PRINT_RESULT(true, result, "i18n_unormalizer_has_boundary_after", "obtained result is not correct");

	return 0;
}
/*
 * @testcase		ITc_i18n_unormalization_is_inert_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_unormalizer_is_inert
 * @apicovered		i18n_unormalizer_is_inert, i18n_unormalization_get_nfd_instance
 * @passcase		I18N_ERROR_NONE returned by i18n_unormalizer_is_inert, i18n_unormalization_get_nfd_instance
 * @failcase		I18N_ERROR_NONE not returned by i18n_unormalizer_is_inert
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_unormalization_is_inert_p(void)
{
        START_TEST_PRINT;
        i18n_unormalizer_h h_normalizer = NULL;
        int nRet = -1;

	nRet = i18n_unormalization_get_nfd_instance(&h_normalizer);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalization_get_nfd_instance", BaseUtilsGetError(nRet));
        CHECK_HANDLE(h_normalizer, "i18n_unormalization_get_nfd_instance");

        i18n_ubool result = false;

        //Target API
	nRet = i18n_unormalization_is_inert(h_normalizer, 0xad, &result);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unormalizer_is_inert", BaseUtilsGetError(nRet));
	PRINT_RESULT(true, result, "i18n_unormalizer_is_inert", "obtained result is not correct");

	return 0;
}

