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
#include "ITs-yaca-common.h"

//& set: Yaca

/** @addtogroup itc-yaca
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_yaca_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_yaca_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	
	int nRet = yaca_initialize();
	if( nRet != YACA_ERROR_NONE )
	{
		g_bYacaInit = false; 
	}
	else
	{
		g_bYacaInit = true;
	}
	return;
}


/**
 * @function 		ITs_yaca_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_yaca_cleanup(void)
{
	yaca_cleanup();
	
	return;
}

/** @addtogroup itc-yaca-testcases
*  @brief 		Integration testcases for module yaca
*  @ingroup 	itc-yaca
*  @{
*/


//& type: auto
//& purpose: Initializes/Cleans up the library
/**
* @testcase 			ITc_yaca_initialize_cleanup_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Initializes/Cleans up the library
* @scenario				Initializes/Cleans up the library
* @apicovered			yaca_initialize,yaca_cleanup
* @passcase				If yaca_initialize  and yaca_cleanup returns success
* @failcase				If yaca_initialize or yaca_cleanup fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_initialize_cleanup_p(void)
{

	START_TEST;
	
	//Target API
	yaca_cleanup();
		
	//Target API
	int nRet = yaca_initialize();	
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_initialize", YacaGetError(nRet));
		
	return 0;
}

//& type: auto
//& purpose: Allocates the memory.
/**
* @testcase 			ITc_yaca_malloc_free_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Allocates the memory.
* @scenario				Allocates the memory.
* @apicovered			yaca_malloc,yaca_free
* @passcase				If yaca_malloc  and yaca_free returns success
* @failcase				If yaca_malloc or yaca_free fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_malloc_free_p(void)
{

	START_TEST;
	
	void *pMemory;
	size_t nSize = 1024;

	//Target API
	int nRet = yaca_malloc(nSize, &pMemory);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_malloc", YacaGetError(nRet));

	//Target API
	yaca_free(pMemory);
	
	return 0;
}

//& type: auto
//& purpose: Allocates the zeroed memory.
/**
* @testcase 			ITc_yaca_zalloc_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Allocates the zeroed memory.
* @scenario				Allocates the zeroed memory.
* @apicovered			yaca_zalloc,yaca_free
* @passcase				If yaca_zalloc  and yaca_free returns success
* @failcase				If yaca_zalloc or yaca_free fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_zalloc_p(void)
{

	START_TEST;
	
	void *pMemory = NULL;
	size_t nSize = 1024;

	//Target API
	int nRet = yaca_zalloc(nSize, &pMemory);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_zalloc", YacaGetError(nRet));

	yaca_free(pMemory);
	
	return 0;
}

//& type: auto
//& purpose:  Re-allocates the memory.
/**
* @testcase 			ITc_yaca_realloc_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Re-allocates the memory.
* @scenario				Re-allocates the memory.
* @apicovered			yaca_malloc, yaca_realloc yaca_free
* @passcase				If yaca_malloc,  yaca_realloc and yaca_free returns success
* @failcase				If yaca_malloc, yaca_realloc or yaca_free fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_realloc_p(void)
{

	START_TEST;
	
	void *pMemory;
	size_t nSize = 1024;

	int nRet = yaca_malloc(nSize, &pMemory);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_malloc", YacaGetError(nRet));
	
	//Target API
	nRet = yaca_realloc(nSize*2, &pMemory);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_realloc", YacaGetError(nRet));
	
	yaca_free(pMemory);
	
	return 0;
}

//& type: auto
//& purpose: Safely compares two buffers.
/**
* @testcase 			ITc_yaca_memcmp_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Safely compares two buffers.
* @scenario				Safely compares two buffers.
* @apicovered			yaca_memcmp
* @passcase				If yaca_memcmp returns success
* @failcase				If yaca_memcmp fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_memcmp_p(void)
{

	START_TEST;
	
	unsigned char first[TEST_MEM_SIZE] = {1, };
	unsigned char second[TEST_MEM_SIZE] = {1, };

	//Target API
	int nRet = yaca_memcmp(first, second, TEST_MEM_SIZE);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_memcmp", YacaGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: Generates random data.
/**
* @testcase 			ITc_yaca_randomize_bytes_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Generates random data.
* @scenario				Generates random data.
* @apicovered			yaca_randomize_bytes
* @passcase				If yaca_randomize_bytes returns success
* @failcase				If yaca_randomize_bytes fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_randomize_bytes_p(void)
{

	START_TEST;
	
	char pData[32] = {0, };

	//Target API
	int nRet = yaca_randomize_bytes(pData, 32);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_randomize_bytes", YacaGetError(nRet));
	
	return 0;
}
#if 0
//& type: auto
//& purpose: Gets the output length for a given context.
/**
* @testcase 			ITc_yaca_context_get_nOutputLength_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Gets the output length for a given context.
* @scenario				Gets the output length for a given context.
* @apicovered			yaca_key_generate, yaca_context_get_nOutputLength
* @passcase				If yaca_key_generate, yaca_context_get_nOutputLength returns success
* @failcase				If yaca_key_generate, yaca_context_get_nOutputLength fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_context_get_nOutputLength_p(void)
{

	START_TEST;

	size_t nOutputLen = 0;
	yaca_key_h prv = YACA_KEY_NULL;
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;
	yaca_context_h hContext = YACA_CONTEXT_NULL;
	
	int nRet = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	CHECK_HANDLE(prv, "yaca_key_generate");
	
	nRet = yaca_sign_initialize(&hContext, YACA_DIGEST_SHA512, prv);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_sign_initialize", YacaGetError(nRet),yaca_key_destroy(prv));

	//Target API	
	nRet = yaca_context_get_nOutputLength(hContext, 0, &nOutputLen);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_get_nOutputLength", YacaGetError(nRet),yaca_key_destroy(prv));
	
	yaca_key_destroy(prv);
	
	return 0;
}
#endif
//& type: auto
//& purpose: Sets the non-standard context properties.
/**
* @testcase 			ITc_yaca_context_set_get_property_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Sets the non-standard context properties.
* @scenario				Sets the non-standard context properties.
* @apicovered			yaca_context_set_property ,yaca_context_destroy
* @passcase				If yaca_context_set_property, yaca_context_destroy returns success
* @failcase				If yaca_context_set_property, yaca_context_destroy fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_context_set_get_property_p(void)
{

	START_TEST;
	
	yaca_encrypt_algorithm_e eEncryptAlgorithm = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e eBlockCipherMode = YACA_BCM_GCM;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t hKeyBitLen = YACA_KEY_LENGTH_256BIT;
	size_t iv_bit_len = YACA_KEY_LENGTH_IV_128BIT;

	yaca_context_h hContext = YACA_CONTEXT_NULL;
	yaca_key_h hKey = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;

	char *enc = NULL;
	char *dec = NULL;
	char *aad = NULL;
	char *tag = NULL;
	size_t aad_len = 16;
	size_t tag_len = 16;
	size_t output_len;

	int nRet = YACA_ERROR_NONE;

	// Key generation
	nRet = yaca_key_generate(key_type, hKeyBitLen, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	CHECK_HANDLE(hKey, "yaca_key_generate");	

	// IV generation
	nRet = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet), yaca_key_destroy(hKey));
	CHECK_HANDLE(iv, "yaca_key_generate");
	
	nRet = yaca_zalloc(aad_len, (void**)&aad);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_zalloc", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_key_destroy(iv));

	nRet = yaca_randomize_bytes(aad, aad_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_randomize_bytes", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(aad);yaca_key_destroy(iv));
	
	nRet = yaca_zalloc(tag_len, (void**)&tag);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_zalloc", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(aad);yaca_key_destroy(iv));

	// Encryption
	nRet = yaca_encrypt_initialize(&hContext, eEncryptAlgorithm, eBlockCipherMode, hKey, iv);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_encrypt_initialize", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(aad);yaca_free(tag);yaca_key_destroy(iv));

	nRet = yaca_context_set_property(hContext, YACA_PROPERTY_GCM_AAD, aad, aad_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_set_property", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(tag);yaca_free(aad);yaca_context_destroy(hContext);yaca_key_destroy(iv));

	nRet = yaca_context_get_output_length(hContext, LOREM4096_SIZE, &output_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_get_output_length", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(tag);yaca_free(aad);yaca_context_destroy(hContext);yaca_key_destroy(iv));
	
	yaca_free(enc);
	yaca_free(dec);
	yaca_free(tag);
	yaca_free(aad);
	yaca_context_destroy(hContext);
	yaca_key_destroy(iv);
	yaca_key_destroy(hKey);
	
	return 0;
}

/** @} */
/** @} */
