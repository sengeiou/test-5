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
 * @function 		ITs_yaca_rsa_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_yaca_rsa_startup(void)
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
 * @function 		ITs_yaca_rsa_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_yaca_rsa_cleanup(void)
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
//& purpose: Encrypts/decrypt data using a RSA public key.
/**
* @testcase 			ITc_yaca_rsa_public_encrypt_private_decrypt_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Encrypts/decrypt data using a RSA public key
* @scenario				Encrypts/decrypt data using a RSA public key
* @apicovered			yaca_rsa_public_encrypt,yaca_rsa_private_decrypt
* @passcase				If yaca_rsa_public_encrypt,yaca_rsa_private_decrypt returns success
* @failcase				If yaca_rsa_public_encrypt,yaca_rsa_private_decrypt fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_rsa_public_encrypt_private_decrypt_p(void)
{
	START_TEST;
	
	yaca_key_h hPrvKey = YACA_KEY_NULL;
	yaca_key_h hPubKey = YACA_KEY_NULL;
	char *pCipherText = NULL;
	size_t nCipherTextLen;
	char *plaintext = NULL;
	size_t plaintext_len;
	const size_t nKeyBitLen = YACA_KEY_LENGTH_1024BIT;
	const size_t nInputLen = nKeyBitLen / 8 - 12;
	int nRet;
		
	nRet = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, nKeyBitLen, &hPrvKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	CHECK_HANDLE(hPrvKey, "yaca_key_generate");
	
	nRet = yaca_key_extract_public(hPrvKey, &hPubKey);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_extract_public", YacaGetError(nRet),yaca_key_destroy(hPrvKey));
	CHECK_HANDLE(hPubKey, "yaca_key_extract_public");	
	
	//Target API
	nRet = yaca_rsa_public_encrypt(YACA_PADDING_PKCS1, hPubKey, lorem1024, nInputLen, &pCipherText, &nCipherTextLen);	
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_rsa_public_encrypt", YacaGetError(nRet), yaca_key_destroy(hPrvKey);yaca_key_destroy(hPubKey));
	if(pCipherText == NULL)
	{
		FPRINTF("[Line : %d][%s] pCipherText value is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	//Target API
	nRet = yaca_rsa_private_decrypt(YACA_PADDING_PKCS1, hPrvKey, pCipherText, nCipherTextLen, &plaintext, &plaintext_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_rsa_private_decrypt", YacaGetError(nRet), yaca_key_destroy(hPrvKey);yaca_key_destroy(hPubKey));
		
	yaca_free(plaintext);		
	yaca_free(pCipherText);
	yaca_key_destroy(hPrvKey);
	yaca_key_destroy(hPubKey);
	
	return 0;
}
	
//& type: auto
//& purpose: Encrypts/decrypt data using a RSA public key.
/**
* @testcase 			ITc_yaca_rsa_private_encrypt_public_decrypt_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Encrypts/decrypt data using a RSA public key
* @scenario				Encrypts/decrypt data using a RSA public key
* @apicovered			yaca_key_generate,yaca_rsa_private_encrypt, yaca_rsa_public_decrypt
* @passcase				If yaca_key_generate  and yaca_rsa_private_encrypt, yaca_rsa_public_decrypt returns success
* @failcase				If yaca_key_generate or yaca_rsa_private_encrypt, yaca_rsa_public_decrypt fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_rsa_private_encrypt_public_decrypt_p(void)
{
	START_TEST;
	
	yaca_key_h hPrvKey = YACA_KEY_NULL;
	yaca_key_h hPubKey = YACA_KEY_NULL;
	char *pCipherText = NULL;
	size_t nCipherTextLen;
	char *plaintext = NULL;
	size_t plaintext_len;
	const size_t nKeyBitLen = YACA_KEY_LENGTH_1024BIT;
	const size_t nInputLen = nKeyBitLen / 8 - 12;	
	int nRet;
		
	nRet = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, nKeyBitLen, &hPrvKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	CHECK_HANDLE(hPrvKey, "yaca_key_generate");	
			
	nRet = yaca_key_extract_public(hPrvKey, &hPubKey);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_extract_public", YacaGetError(nRet),yaca_key_destroy(hPrvKey));
	CHECK_HANDLE(hPubKey, "yaca_key_extract_public");	
		
	//Target API
	nRet = yaca_rsa_private_encrypt(YACA_PADDING_PKCS1, hPrvKey, lorem1024, nInputLen, &pCipherText, &nCipherTextLen);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_rsa_public_encrypt", YacaGetError(nRet), yaca_key_destroy(hPrvKey);yaca_key_destroy(hPubKey));
	if(pCipherText == NULL)
	{
		FPRINTF("[Line : %d][%s] pCipherText value is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	//Target API
	nRet = yaca_rsa_public_decrypt(YACA_PADDING_PKCS1, hPubKey, pCipherText, nCipherTextLen, &plaintext, &plaintext_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_rsa_public_decrypt", YacaGetError(nRet), yaca_key_destroy(hPrvKey);yaca_key_destroy(hPubKey));
		
	yaca_free(plaintext);		
	yaca_free(pCipherText);
	yaca_key_destroy(hPrvKey);
	yaca_key_destroy(hPubKey);
	
	return 0;
}
	


/** @} */
/** @} */
