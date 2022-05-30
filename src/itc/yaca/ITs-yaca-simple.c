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
 * @function 		ITs_yaca_simple_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_yaca_simple_startup(void)
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
 * @function 		ITs_yaca_simple_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_yaca_simple_cleanup(void)
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
//& purpose: Calculates a digest of a buffer
/**
* @testcase 			ITc_yaca_simple_calculate_digest_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Calculates a digest of a buffer
* @scenario				Calculates a digest of a buffer
* @apicovered			yaca_simple_calculate_digest
* @passcase				If yaca_simple_calculate_digest returns success
* @failcase				If yaca_simple_calculate_digest fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_simple_calculate_digest_p(void)
{
	START_TEST;
	
	char *digest = NULL;
	size_t digest_len;
	
	//Target API
	int nRet = yaca_simple_calculate_digest(YACA_DIGEST_SHA256, lorem1024, 1024, &digest, &digest_len);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_simple_calculate_digest", YacaGetError(nRet));
	
	yaca_free(digest);
		
	return 0;
}

//& type: auto
//& purpose: Encrypts data using a symmetric cipher
/**
* @testcase 			ITc_yaca_simple_encrypt_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Encrypts data using a symmetric cipher
* @scenario				Encrypts data using a symmetric cipher
* @apicovered			yaca_simple_encrypt, yaca_key_generate
* @passcase				If yaca_simple_encrypt returns success
* @failcase				If yaca_simple_encrypt fails
* @precondition			NA
* @postcondition		Initializes the library 180030009009
*/
int ITc_yaca_simple_encrypt_p(void)
{
	START_TEST;
	
	yaca_encrypt_algorithm_e eAlgorithm = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e eBlockCipherMode = YACA_BCM_ECB;
	size_t hKeyBitLen = YACA_KEY_LENGTH_256BIT;

	yaca_key_h hKey = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;

	char *enc = NULL;
	size_t enc_len = 0;
	size_t iv_bit_len = 0;
	
	//Target API
	int nRet = yaca_key_derive_pbkdf2("foo bar", "123456789", 10, 1000,	YACA_DIGEST_SHA256, hKeyBitLen, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_derive_pbkdf2", YacaGetError(nRet));
	CHECK_HANDLE(hKey, "yaca_key_derive_pbkdf2");
	
	nRet = yaca_encrypt_get_iv_bit_length(eAlgorithm, eBlockCipherMode, hKeyBitLen, &iv_bit_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_encrypt_get_iv_bit_length", YacaGetError(nRet),yaca_key_destroy(hKey));
	
	if (iv_bit_len > 0) {
		nRet = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv);
		PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet),yaca_key_destroy(hKey));
	}
	
	nRet = yaca_simple_encrypt(eAlgorithm, eBlockCipherMode, hKey, iv, lorem4096, LOREM4096_SIZE, &enc, &enc_len);	
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_simple_encrypt", YacaGetError(nRet),yaca_free(enc);yaca_key_destroy(iv);yaca_key_destroy(hKey));
	
	yaca_free(enc);
	yaca_key_destroy(iv);
	yaca_key_destroy(hKey);
		
	return 0;
}

//& type: auto
//& purpose: Decrypts data using a symmetric cipher
/**
* @testcase 			ITc_yaca_simple_decrypt_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Decrypts data using a symmetric cipher
* @scenario				Decrypts data using a symmetric cipher
* @apicovered			yaca_simple_encrypt, yaca_simple_decrypt yaca_key_generate
* @passcase				If yaca_simple_encrypt, yaca_simple_decrypt returns success
* @failcase				If yaca_simple_encrypt, yaca_simple_decrypt fails
* @precondition			NA
* @postcondition		Initializes the library 180030009009
*/
int ITc_yaca_simple_decrypt_p(void)
{
	START_TEST;
	
	yaca_encrypt_algorithm_e eAlgorithm = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e eBlockCipherMode = YACA_BCM_ECB;
	size_t hKeyBitLen = YACA_KEY_LENGTH_256BIT;

	yaca_key_h hKey = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;

	char *enc = NULL;
	size_t enc_len = 0;
	size_t iv_bit_len = 0;
	char *dec = NULL;
	size_t dec_len;
	
	//Target API
	int nRet = yaca_key_derive_pbkdf2("foo bar", "123456789", 10, 1000,	YACA_DIGEST_SHA256, hKeyBitLen, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_derive_pbkdf2", YacaGetError(nRet));
	CHECK_HANDLE(hKey, "yaca_key_derive_pbkdf2");
	
	nRet = yaca_encrypt_get_iv_bit_length(eAlgorithm, eBlockCipherMode, hKeyBitLen, &iv_bit_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_encrypt_get_iv_bit_length", YacaGetError(nRet),yaca_key_destroy(hKey));
	
	if (iv_bit_len > 0) {
		nRet = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv);
		PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet),yaca_key_destroy(hKey));
	}
	
	nRet = yaca_simple_encrypt(eAlgorithm, eBlockCipherMode, hKey, iv, lorem4096, LOREM4096_SIZE, &enc, &enc_len);	
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_simple_encrypt", YacaGetError(nRet),yaca_free(enc);yaca_key_destroy(iv);yaca_key_destroy(hKey));
	
	nRet = yaca_simple_decrypt(eAlgorithm, eBlockCipherMode, hKey, iv, enc, enc_len, &dec, &dec_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_simple_decrypt", YacaGetError(nRet),yaca_free(enc);yaca_key_destroy(iv);yaca_key_destroy(hKey));
	
	yaca_free(enc);
	yaca_free(dec);
	yaca_key_destroy(iv);
	yaca_key_destroy(hKey);
		
	return 0;
}

//& type: auto
//& purpose: Creates a signature using asymmetric private key.
/**
* @testcase 			ITc_yaca_simple_calculate_signature_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Creates a signature using asymmetric private key.
* @scenario				Creates a signature using asymmetric private key.
* @apicovered			yaca_simple_calculate_signature
* @passcase				If yaca_simple_calculate_signature returns success
* @failcase				If yaca_simple_calculate_signature fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_simple_calculate_signature_p(void)
{
	START_TEST;
	
	char *pSignature = NULL;
	size_t signature_len;
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;
	yaca_key_h prv = YACA_KEY_NULL;
	
	int nRet = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	
	//Target API
	nRet = yaca_simple_calculate_signature(YACA_DIGEST_SHA512, prv, lorem4096, LOREM4096_SIZE, &pSignature, &signature_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_simple_calculate_signature", YacaGetError(nRet),yaca_key_destroy(prv));
	
	yaca_free(pSignature);
	yaca_key_destroy(prv);
		
	return 0;
}

//& type: auto
//& purpose: Verifies a signature using asymmetric public key
/**
* @testcase 			ITc_yaca_simple_verify_signature_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Verifies a signature using asymmetric public key
* @scenario				Verifies a signature using asymmetric public key
* @apicovered			yaca_simple_calculate_signature, yaca_simple_verify_signature
* @passcase				If yaca_simple_calculate_signature, yaca_simple_verify_signature returns success
* @failcase				If yaca_simple_calculate_signature, yaca_simple_verify_signature fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_simple_verify_signature_p(void)
{
	START_TEST;
	
	char *pSignature = NULL;
	size_t signature_len;
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;
	yaca_key_h prv = YACA_KEY_NULL;
	yaca_key_h pub = YACA_KEY_NULL;

	int nRet = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	
	nRet = yaca_key_extract_public(prv, &pub);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_extract_public", YacaGetError(nRet),yaca_key_destroy(prv));
	
	nRet = yaca_simple_calculate_signature(YACA_DIGEST_SHA512, prv, lorem4096, LOREM4096_SIZE, &pSignature, &signature_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_simple_calculate_signature", YacaGetError(nRet),yaca_key_destroy(prv));
	
	//Target API	
	nRet = yaca_simple_verify_signature(YACA_DIGEST_SHA512, pub, lorem4096, LOREM4096_SIZE,	pSignature, signature_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_simple_verify_signature", YacaGetError(nRet), yaca_free(pSignature); yaca_key_destroy(prv));
	
	yaca_free(pSignature);
	yaca_key_destroy(pub);
	yaca_key_destroy(prv);
		
	return 0;
}

//& type: auto
//& purpose: Calculates a HMAC of given message using symmetric key
/**
* @testcase 			ITc_yaca_simple_calculate_hmac_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Calculates a HMAC of given message using symmetric key
* @scenario				Calculates a HMAC of given message using symmetric key
* @apicovered			yaca_simple_calculate_hmac
* @passcase				If yaca_simple_calculate_hmac returns success
* @failcase				If yaca_simple_calculate_hmac fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_simple_calculate_hmac_p(void)
{
	START_TEST;
	
	char *pSignature = NULL;
	size_t signature_len;
	yaca_key_h hKey = YACA_KEY_NULL;
	
	int nRet = yaca_key_generate(YACA_KEY_TYPE_SYMMETRIC, YACA_KEY_LENGTH_256BIT, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	
	//Target API
	nRet = yaca_simple_calculate_hmac(YACA_DIGEST_SHA512, hKey, lorem4096, LOREM4096_SIZE, &pSignature, &signature_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_simple_calculate_hmac", YacaGetError(nRet),yaca_key_destroy(hKey));
	
	yaca_free(pSignature);
	yaca_key_destroy(hKey);
		
	return 0;
}

//& type: auto
//& purpose: Calculates a CMAC of given message using symmetric key
/**
* @testcase 			ITc_yaca_simple_calculate_cmac_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Calculates a CMAC of given message using symmetric key
* @scenario				Calculates a CMAC of given message using symmetric key
* @apicovered			yaca_simple_calculate_cmac
* @passcase				If yaca_simple_calculate_cmac returns success
* @failcase				If yaca_simple_calculate_cmac fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_simple_calculate_cmac_p(void)
{
	START_TEST;
	
	char *pSignature = NULL;
	size_t signature_len;
	yaca_key_h hKey = YACA_KEY_NULL;
	
	int nRet = yaca_key_generate(YACA_KEY_TYPE_SYMMETRIC, YACA_KEY_LENGTH_256BIT, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	
	//Target API
	nRet = yaca_simple_calculate_cmac(YACA_ENCRYPT_AES, hKey, lorem4096, LOREM4096_SIZE, &pSignature, &signature_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_simple_calculate_cmac", YacaGetError(nRet),yaca_key_destroy(hKey));
	
	yaca_free(pSignature);
	yaca_key_destroy(hKey);
			
	return 0;
}

/** @} */
/** @} */