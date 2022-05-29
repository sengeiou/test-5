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
 * @function 		ITs_yaca_encrypt_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_yaca_encrypt_startup(void)
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
 * @function 		ITs_yaca_encrypt_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_yaca_encrypt_cleanup(void)
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
//& purpose: Returns the recommended/default length of the IV for a given encryption configuration.
/**
* @testcase 			ITc_yaca_encrypt_get_iv_bit_length_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Returns the recommended/default length of the IV for a given encryption configuration.
* @scenario				Returns the recommended/default length of the IV for a given encryption configuration.
* @apicovered			yaca_key_generate, yaca_key_derive_pbkdf2, yaca_encrypt_get_iv_bit_length
* @passcase				If yaca_key_generate, yaca_key_derive_pbkdf2, yaca_encrypt_get_iv_bit_length returns success
* @failcase				If yaca_key_generate, yaca_key_derive_pbkdf2, yaca_encrypt_get_iv_bit_length fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_encrypt_get_iv_bit_length_p(void)
{
	START_TEST;
	
	yaca_key_h hKey = YACA_KEY_NULL;
	size_t nKeyBitLen = YACA_KEY_LENGTH_256BIT;
	yaca_encrypt_algorithm_e eEncryptAlgorithm = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e eBlockCipherMode = YACA_BCM_ECB;
	size_t nIvBitLen;
	int nRet = YACA_ERROR_NONE;
	
	nRet = yaca_key_derive_pbkdf2("foo bar", "123456789", 10, 1000, YACA_DIGEST_SHA256, nKeyBitLen, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_derive_pbkdf2", YacaGetError(nRet));
	CHECK_HANDLE(hKey, "yaca_key_derive_pbkdf2");
	
	//Target API	
	nRet = yaca_encrypt_get_iv_bit_length(eEncryptAlgorithm, eBlockCipherMode, nKeyBitLen, &nIvBitLen);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_encrypt_get_iv_bit_length", YacaGetError(nRet));
		
	return 0;
}


//& type: auto
//& purpose: Initializes the encrypt context
/**
* @testcase 			ITc_yaca_encrypt_initialize_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Initializes the encrypt context
* @scenario				Initializes the encrypt context
* @apicovered			yaca_key_generate, yaca_key_derive_pbkdf2, yaca_encrypt_initialize
* @passcase				If yaca_key_generate, yaca_key_derive_pbkdf2, yaca_encrypt_initialize returns success
* @failcase				If yaca_key_generate, yaca_key_derive_pbkdf2, yaca_encrypt_initialize fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_encrypt_initialize_p(void)
{
	START_TEST;
	
	yaca_key_h hKey = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;
	yaca_context_h hContext = YACA_CONTEXT_NULL;
	size_t nKeyBitLen = YACA_KEY_LENGTH_256BIT;
	yaca_encrypt_algorithm_e eEncryptAlgorithm = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e eBlockCipherMode = YACA_BCM_ECB;
	size_t nIvBitLen;
	int nRet = YACA_ERROR_NONE;
	
	nRet = yaca_key_derive_pbkdf2("foo bar", "123456789", 10, 1000, YACA_DIGEST_SHA256, nKeyBitLen, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_derive_pbkdf2", YacaGetError(nRet));
	CHECK_HANDLE(hKey, "yaca_key_derive_pbkdf2");
	
	nRet = yaca_encrypt_get_iv_bit_length(eEncryptAlgorithm, eBlockCipherMode, nKeyBitLen, &nIvBitLen);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_encrypt_get_iv_bit_length", YacaGetError(nRet), yaca_key_destroy(hKey));
	
	if (nIvBitLen > 0) {
		nRet = yaca_key_generate(YACA_KEY_TYPE_IV, nIvBitLen, &iv);
		PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet), yaca_key_destroy(hKey));
	}
	
	//Target API
	nRet = yaca_encrypt_initialize(&hContext, eEncryptAlgorithm, eBlockCipherMode, hKey, iv);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_encrypt_initialize", YacaGetError(nRet),yaca_key_destroy(iv);yaca_key_destroy(hKey));
	
	yaca_context_destroy(hContext);
	yaca_key_destroy(iv);
	yaca_key_destroy(hKey);
		
	return 0;
}

//& type: auto
//& purpose: Initializes the encrypt context
/**
* @testcase 			ITc_yaca_decrypt_initialize_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Initializes the encrypt context
* @scenario				Initializes the encrypt context
* @apicovered			yaca_key_generate, yaca_key_derive_pbkdf2, yaca_decrypt_initialize
* @passcase				If yaca_key_generate, yaca_key_derive_pbkdf2, yaca_decrypt_initialize returns success
* @failcase				If yaca_key_generate, yaca_key_derive_pbkdf2, yaca_decrypt_initialize fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_decrypt_initialize_p(void)
{
	START_TEST;
	
	yaca_key_h hKey = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;
	yaca_context_h hContext = YACA_CONTEXT_NULL;
	size_t nKeyBitLen = YACA_KEY_LENGTH_256BIT;
	yaca_encrypt_algorithm_e eEncryptAlgorithm = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e eBlockCipherMode = YACA_BCM_ECB;
	size_t nIvBitLen;
	int nRet = YACA_ERROR_NONE;
	
	nRet = yaca_key_derive_pbkdf2("foo bar", "123456789", 10, 1000, YACA_DIGEST_SHA256, nKeyBitLen, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_derive_pbkdf2", YacaGetError(nRet));
	CHECK_HANDLE(hKey, "yaca_key_derive_pbkdf2");
	
	nRet = yaca_encrypt_get_iv_bit_length(eEncryptAlgorithm, eBlockCipherMode, nKeyBitLen, &nIvBitLen);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_encrypt_get_iv_bit_length", YacaGetError(nRet), yaca_key_destroy(hKey));
	
	if (nIvBitLen > 0) {
		nRet = yaca_key_generate(YACA_KEY_TYPE_IV, nIvBitLen, &iv);
		PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet), yaca_key_destroy(hKey));
	}
	
	//Target API
	nRet = yaca_decrypt_initialize(&hContext, eEncryptAlgorithm, eBlockCipherMode, hKey, iv);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_decrypt_initialize", YacaGetError(nRet),yaca_key_destroy(iv);yaca_key_destroy(hKey));
	
	yaca_context_destroy(hContext);
	yaca_key_destroy(iv);
	yaca_key_destroy(hKey);
		
	return 0;
}

//& type: auto
//& purpose: Encrypts chunk of the data
/**
* @testcase 			ITc_yaca_encrypt_update_finalize_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Encrypts chunk of the data
* @scenario				Encrypts chunk of the data
* @apicovered			yaca_key_generate, yaca_encrypt_update, yaca_encrypt_finalize, yaca_encrypt_initialize
* @passcase				If yaca_key_generate, yaca_encrypt_update, yaca_encrypt_finalize, yaca_encrypt_initialize returns success
* @failcase				If yaca_key_generate, yaca_encrypt_update, yaca_encrypt_finalize, yaca_encrypt_initialize fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_encrypt_update_finalize_p(void)
{
	START_TEST;
	
	yaca_encrypt_algorithm_e eEncryptAlgorithm = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e eBlockCipherMode = YACA_BCM_ECB;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t nKeyBitLen = YACA_KEY_LENGTH_256BIT;

	yaca_context_h hContext = YACA_CONTEXT_NULL;
	yaca_key_h hKey = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;
	size_t nIvBitLen;

	char *enc = NULL;
	size_t enc_len;

	size_t block_len;
	size_t output_len;
	size_t written_len;
	size_t rem;
	int nRet = YACA_ERROR_NONE;
	
	nRet = yaca_key_generate(key_type, nKeyBitLen, &hKey);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet), yaca_key_destroy(hKey));
	CHECK_HANDLE(hKey, "yaca_key_generate");
		
	nRet = yaca_encrypt_get_iv_bit_length(eEncryptAlgorithm, eBlockCipherMode, nKeyBitLen, &nIvBitLen);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_encrypt_get_iv_bit_length", YacaGetError(nRet), yaca_key_destroy(hKey));
	
	if (nIvBitLen > 0) {
		nRet = yaca_key_generate(YACA_KEY_TYPE_IV, nIvBitLen, &iv);
		PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet), yaca_key_destroy(hKey));
	}

	nRet = yaca_encrypt_initialize(&hContext, eEncryptAlgorithm, eBlockCipherMode, hKey, iv);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_encrypt_initialize", YacaGetError(nRet),yaca_key_destroy(hKey);yaca_key_destroy(iv));
	
	
	// For the update
	nRet = yaca_context_get_output_length(hContext, LOREM4096_SIZE, &output_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_get_output_length", YacaGetError(nRet), yaca_context_destroy(hContext);yaca_key_destroy(iv);yaca_key_destroy(hKey));

	// For the finalize
	nRet = yaca_context_get_output_length(hContext, 0, &block_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_get_output_length", YacaGetError(nRet), yaca_context_destroy(hContext);yaca_key_destroy(iv);yaca_key_destroy(hKey));

	enc_len = output_len + block_len;
	nRet = yaca_malloc(enc_len, (void**)&enc);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_malloc", YacaGetError(nRet), yaca_context_destroy(hContext);yaca_key_destroy(iv);yaca_key_destroy(hKey));

	written_len = enc_len;
	//Target API
	nRet = yaca_encrypt_update(hContext, lorem4096, LOREM4096_SIZE, enc, &written_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_encrypt_update", YacaGetError(nRet), yaca_context_destroy(hContext);yaca_key_destroy(iv);yaca_key_destroy(hKey);yaca_free(enc));
		
	rem = enc_len - written_len;
	//Target API
	nRet = yaca_encrypt_finalize(hContext, enc + written_len, &rem);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_encrypt_finalize", YacaGetError(nRet), yaca_context_destroy(hContext);yaca_key_destroy(iv);yaca_key_destroy(hKey);yaca_free(enc));
		
	yaca_free(enc);
	yaca_context_destroy(hContext);
	yaca_key_destroy(iv);
	yaca_key_destroy(hKey);
		
	return 0;
}


//& type: auto
//& purpose: Encrypts chunk of the data
/**
* @testcase 			ITc_yaca_decrypt_update_finalize_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Encrypts chunk of the data
* @scenario				Encrypts chunk of the data
* @apicovered			yaca_key_generate, yaca_decrypt_update, yaca_decrypt_finalize, yaca_encrypt_initialize
* @passcase				If yaca_key_generate, yaca_decrypt_update, yaca_decrypt_finalize, yaca_encrypt_initialize returns success
* @failcase				If yaca_key_generate, yaca_decrypt_update, yaca_decrypt_finalize, yaca_encrypt_initialize fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_decrypt_update_finalize_p(void)
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
	size_t enc_len;
	size_t dec_len;

	char *aad = NULL;
	char *tag = NULL;
	size_t aad_len = 16;
	size_t tag_len = 16;

	size_t block_len;
	size_t output_len;
	size_t written_len;
	size_t rem;

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

	// Encryption
	nRet = yaca_encrypt_initialize(&hContext, eEncryptAlgorithm, eBlockCipherMode, hKey, iv);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_encrypt_initialize", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(aad);yaca_key_destroy(iv));

	nRet = yaca_context_set_property(hContext, YACA_PROPERTY_GCM_AAD, aad, aad_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_set_property", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(aad);yaca_context_destroy(hContext);yaca_key_destroy(iv));

	nRet = yaca_context_get_output_length(hContext, LOREM4096_SIZE, &output_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_get_output_length", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(aad);yaca_context_destroy(hContext);yaca_key_destroy(iv));

	nRet = yaca_context_get_output_length(hContext, 0, &block_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_get_output_length", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(aad);yaca_context_destroy(hContext);yaca_key_destroy(iv));

	enc_len = output_len + block_len;
	nRet = yaca_malloc(enc_len, (void**)&enc);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_malloc", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(aad);yaca_context_destroy(hContext);yaca_key_destroy(iv));

	written_len = enc_len;
	nRet = yaca_encrypt_update(hContext, lorem4096, LOREM4096_SIZE, enc, &written_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_encrypt_update", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(aad);yaca_free(enc);yaca_context_destroy(hContext);yaca_key_destroy(iv));

	rem = enc_len - written_len;
	nRet = yaca_encrypt_finalize(hContext, enc + written_len, &rem);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_encrypt_finalize", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(aad);yaca_free(enc);yaca_context_destroy(hContext);yaca_key_destroy(iv));

	enc_len = rem + written_len;

	// Set the tag length and get the tag after final encryption
	nRet = yaca_context_set_property(hContext, YACA_PROPERTY_GCM_TAG_LEN, (void*)&tag_len, sizeof(tag_len));
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_set_property", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(aad);yaca_free(enc);yaca_context_destroy(hContext);yaca_key_destroy(iv));

	nRet = yaca_context_get_property(hContext, YACA_PROPERTY_GCM_TAG, (void**)&tag, &tag_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_get_property", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(aad);yaca_free(enc);yaca_context_destroy(hContext);yaca_key_destroy(iv));

	yaca_context_destroy(hContext);
	hContext = YACA_CONTEXT_NULL;

	// Decryption
	nRet = yaca_decrypt_initialize(&hContext, eEncryptAlgorithm, eBlockCipherMode, hKey, iv);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_decrypt_initialize", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(tag);yaca_free(aad);yaca_free(enc);yaca_context_destroy(hContext);yaca_key_destroy(iv));

	nRet = yaca_context_set_property(hContext, YACA_PROPERTY_GCM_AAD, aad, aad_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_set_property", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(tag);yaca_free(aad);yaca_free(enc);yaca_context_destroy(hContext);yaca_key_destroy(iv));

	nRet = yaca_context_get_output_length(hContext, LOREM4096_SIZE, &output_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_get_output_length", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(tag);yaca_free(aad);yaca_free(enc);yaca_context_destroy(hContext);yaca_key_destroy(iv));

	nRet = yaca_context_get_output_length(hContext, 0, &block_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_get_output_length", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(tag);yaca_free(aad);yaca_free(enc);yaca_context_destroy(hContext);yaca_key_destroy(iv));

	dec_len = output_len + block_len;
	nRet = yaca_malloc(dec_len, (void**)&dec);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_malloc", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(tag);yaca_free(aad);yaca_free(enc);yaca_context_destroy(hContext);yaca_key_destroy(iv));

//Target API
	written_len = dec_len;
	nRet = yaca_decrypt_update(hContext, enc, enc_len, dec, &written_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_decrypt_update", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(tag);yaca_free(aad);yaca_free(dec);yaca_free(enc);yaca_context_destroy(hContext);yaca_key_destroy(iv));

	rem = dec_len - written_len;

	// Set expected tag value before final decryption
	nRet = yaca_context_set_property(hContext, YACA_PROPERTY_GCM_TAG, tag, tag_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_set_property", YacaGetError(nRet), yaca_key_destroy(hKey);yaca_free(tag);yaca_free(aad);yaca_free(dec);yaca_free(enc);yaca_context_destroy(hContext);yaca_key_destroy(iv));

//Target API
	nRet = yaca_decrypt_finalize(hContext, dec + written_len, &rem);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_decrypt_finalize", YacaGetError(nRet), yaca_context_destroy(hContext);yaca_key_destroy(iv);yaca_free(tag);yaca_free(aad);yaca_free(enc);yaca_free(dec);yaca_key_destroy(hKey));

	dec_len = rem + written_len;

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
