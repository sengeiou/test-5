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
 * @function 		ITs_yaca_seal_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_yaca_seal_startup(void)
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
 * @function 		ITs_yaca_seal_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_yaca_seal_cleanup(void)
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
//& purpose: Initializes/update an asymmetric encryption context
/**
* @testcase 			ITc_yaca_seal_initialize_update_finalize_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Initializes/update an asymmetric encryption context
* @scenario				Initializes/update an asymmetric encryption context
* @apicovered			yaca_seal_initialize, yaca_seal_update, yaca_seal_finalize, yaca_key_generate
* @passcase				If yaca_seal_initialize, yaca_seal_update, yaca_seal_finalize and yaca_key_generate returns success
* @failcase				If yaca_seal_initialize yaca_seal_update, yaca_seal_finalize or yaca_key_generate fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_seal_initialize_update_finalize_p(void)
{

	START_TEST;
	
	yaca_encrypt_algorithm_e eAlgorithm = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e eBlockCipherMode = YACA_BCM_CBC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h hContext = YACA_CONTEXT_NULL;
	yaca_key_h key_pub = YACA_KEY_NULL;
	yaca_key_h key_priv = YACA_KEY_NULL;
	yaca_key_h sym_key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;
	
	char *enc = NULL;
	size_t enc_len;

	size_t block_len;
	size_t output_len;
	size_t written_len;
	size_t rem;
	
	int nRet = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, YACA_KEY_LENGTH_2048BIT, &key_priv);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	CHECK_HANDLE(key_priv, "yaca_key_generate");
	
	nRet = yaca_key_extract_public(key_priv, &key_pub);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet),yaca_key_destroy(key_priv));
	CHECK_HANDLE(key_pub, "yaca_key_extract_public");
		
//Target API
	nRet = yaca_seal_initialize(&hContext, key_pub, eAlgorithm, eBlockCipherMode, key_bit_len, &sym_key, &iv);	
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_seal_initialize", YacaGetError(nRet),yaca_key_destroy(key_priv);yaca_key_destroy(key_pub));
	CHECK_HANDLE(hContext, "yaca_seal_initialize");
	
	nRet = yaca_context_get_output_length(hContext, LOREM4096_SIZE, &output_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_get_output_length", YacaGetError(nRet),yaca_key_destroy(key_priv);yaca_key_destroy(key_pub);yaca_key_destroy(iv);yaca_key_destroy(sym_key);yaca_context_destroy(hContext));
	
	nRet = yaca_context_get_output_length(hContext, 0, &block_len);	
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_get_output_length", YacaGetError(nRet),yaca_key_destroy(key_priv);yaca_key_destroy(key_pub);yaca_key_destroy(iv);yaca_key_destroy(sym_key);yaca_context_destroy(hContext));
	
	enc_len = output_len + block_len;
	nRet = yaca_malloc(enc_len, (void**)&enc);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "malloc:failure:ITc_yaca_seal_initialize_update_finalize_p", YacaGetError(nRet),yaca_key_destroy(key_priv);yaca_key_destroy(key_pub);yaca_key_destroy(iv);yaca_key_destroy(sym_key);yaca_context_destroy(hContext));
	
	written_len = enc_len;
//Target API
	nRet = yaca_seal_update(hContext, lorem4096, LOREM4096_SIZE, enc, &written_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_seal_update", YacaGetError(nRet),yaca_key_destroy(key_priv);yaca_key_destroy(key_pub);yaca_key_destroy(iv);yaca_key_destroy(sym_key);yaca_context_destroy(hContext));
	
//Target API
	rem = enc_len - written_len;
	nRet = yaca_seal_finalize(hContext, enc + written_len, &rem);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_seal_finalize", YacaGetError(nRet),yaca_key_destroy(key_priv);yaca_key_destroy(key_pub);yaca_key_destroy(iv);yaca_key_destroy(sym_key);yaca_context_destroy(hContext);yaca_free(enc));
	
	yaca_free(enc);
	yaca_context_destroy(hContext);
	yaca_key_destroy(sym_key);
	yaca_key_destroy(iv);
	yaca_key_destroy(key_pub);
	yaca_key_destroy(key_priv);
	
	return 0;
}


//& type: auto
//& purpose: Initializes an asymmetric decryption context
/**
* @testcase 			ITc_yaca_open_initialize_update_finalize_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Initializes an asymmetric decryption context
*						Decrypts piece of the data
* @scenario				Initializes an asymmetric decryption context
* @apicovered			yaca_seal_initialize, yaca_open_initialize, yaca_open_update, yaca_open_finalize, yaca_seal_update, yaca_seal_finalize, yaca_key_generate
* @passcase				If yaca_seal_initialize, yaca_open_initialize, yaca_open_update, yaca_open_finalize, yaca_seal_update, yaca_seal_finalize and yaca_key_generate returns success
* @failcase				If yaca_seal_initialize, yaca_open_initialize, yaca_open_update, yaca_open_finalize, yaca_seal_update, yaca_seal_finalize or yaca_key_generate fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_open_initialize_update_finalize_p(void)
{
	START_TEST;
	
	yaca_context_h hContext = YACA_CONTEXT_NULL;
	yaca_key_h key_priv = YACA_KEY_NULL;
	yaca_key_h key_pub = YACA_KEY_NULL;
	yaca_key_h sym_key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;

	yaca_encrypt_algorithm_e eAlgorithm = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e eBlockCipherMode = YACA_BCM_CBC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;
	
	char *enc = NULL;
	size_t enc_len;
	char *dec = NULL;
	size_t dec_len;

	size_t block_len;
	size_t output_len;
	size_t written_len;
	size_t rem;
	
	int nRet = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, YACA_KEY_LENGTH_2048BIT, &key_priv);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	CHECK_HANDLE(key_priv, "yaca_key_generate");
	
	nRet = yaca_key_extract_public(key_priv, &key_pub);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet),yaca_key_destroy(key_priv));
	CHECK_HANDLE(key_pub, "yaca_key_extract_public");
	
	nRet = yaca_seal_initialize(&hContext, key_pub, eAlgorithm, eBlockCipherMode, key_bit_len, &sym_key, &iv);	
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_seal_initialize", YacaGetError(nRet),yaca_key_destroy(key_priv);yaca_key_destroy(key_pub));
	CHECK_HANDLE(hContext, "yaca_seal_initialize");
	
	nRet = yaca_context_get_output_length(hContext, LOREM4096_SIZE, &output_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_seal_initialize", YacaGetError(nRet),yaca_key_destroy(key_priv);yaca_key_destroy(key_pub));

	nRet = yaca_context_get_output_length(hContext, 0, &block_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_seal_initialize", YacaGetError(nRet),yaca_key_destroy(key_priv);yaca_key_destroy(key_pub));

	enc_len = output_len + block_len;
	nRet = yaca_malloc(enc_len, (void**)&enc);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_seal_initialize", YacaGetError(nRet),yaca_key_destroy(key_priv);yaca_key_destroy(key_pub));

	written_len = enc_len;
	nRet = yaca_seal_update(hContext, lorem4096, LOREM4096_SIZE, enc, &written_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_seal_initialize", YacaGetError(nRet),yaca_key_destroy(key_priv);yaca_key_destroy(key_pub));

	rem = enc_len - written_len;
	nRet = yaca_seal_finalize(hContext, enc + written_len, &rem);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_seal_initialize", YacaGetError(nRet),yaca_key_destroy(key_priv);yaca_key_destroy(key_pub));

	enc_len = written_len + rem;
	
	yaca_context_destroy(hContext);
	
	//Target API
	nRet = yaca_open_initialize(&hContext, key_priv, eAlgorithm, eBlockCipherMode, key_bit_len, sym_key, iv);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_open_initialize", YacaGetError(nRet),yaca_key_destroy(key_priv);yaca_key_destroy(key_pub));
	
	nRet = yaca_context_get_output_length(hContext, LOREM4096_SIZE, &output_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_get_output_length", YacaGetError(nRet),yaca_key_destroy(key_priv);yaca_key_destroy(key_pub);yaca_key_destroy(iv);yaca_key_destroy(sym_key);yaca_context_destroy(hContext));
	
	nRet = yaca_context_get_output_length(hContext, 0, &block_len);	
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_get_output_length", YacaGetError(nRet),yaca_key_destroy(key_priv);yaca_key_destroy(key_pub);yaca_key_destroy(iv);yaca_key_destroy(sym_key);yaca_context_destroy(hContext));
	
	dec_len = output_len + block_len;
	nRet = yaca_malloc(dec_len, (void**)&dec);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_malloc", YacaGetError(nRet),yaca_key_destroy(key_priv);yaca_key_destroy(key_pub);yaca_key_destroy(iv);yaca_key_destroy(sym_key);yaca_context_destroy(hContext));
	
	written_len = dec_len;

	//Target API
	nRet = yaca_open_update(hContext, enc, enc_len, dec, &written_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_seal_finalize", YacaGetError(nRet),yaca_key_destroy(key_priv);yaca_key_destroy(key_pub);yaca_key_destroy(iv);yaca_key_destroy(sym_key);yaca_context_destroy(hContext);yaca_free(enc);yaca_free(dec));
	
	rem = 0;
	nRet = yaca_open_finalize(hContext, dec + written_len, &rem);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_seal_finalize", YacaGetError(nRet),yaca_key_destroy(key_priv);yaca_key_destroy(key_pub);yaca_key_destroy(iv);yaca_key_destroy(sym_key);yaca_context_destroy(hContext);yaca_free(enc);yaca_free(dec));
	
	yaca_free(enc);
	yaca_free(dec);
	yaca_context_destroy(hContext);
	yaca_key_destroy(sym_key);
	yaca_key_destroy(iv);
	yaca_key_destroy(key_pub);
	yaca_key_destroy(key_priv);
		
	return 0;
}
/** @} */
/** @} */