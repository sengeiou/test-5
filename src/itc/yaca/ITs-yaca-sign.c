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
 * @function 		ITs_yaca_sign_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_yaca_sign_startup(void)
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
 * @function 		ITs_yaca_sign_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_yaca_sign_cleanup(void)
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
//& purpose: Initializes a signature context.
/**
* @testcase 			ITc_yaca_sign_initialize_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Initializes up signature context.
* @scenario				Initializes up signature context.
* @apicovered			yaca_sign_initialize,yaca_context_destroy,yaca_key_generate
* @passcase				If yaca_sign_initialize yaca_context_destroy,  and yaca_key_generate returns success
* @failcase				If yaca_sign_initialize yaca_context_destroy, or yaca_key_generate fails
* @precondition			Yaca initialize
* @postcondition		NA
*/
int ITc_yaca_sign_initialize_p(void)
{
	START_TEST;
	
	yaca_key_type_e eType = YACA_KEY_TYPE_RSA_PRIV;
	yaca_context_h hContext = YACA_CONTEXT_NULL;
	yaca_key_h hKey = YACA_KEY_NULL;
	
	int nRet = yaca_key_generate(eType, YACA_KEY_LENGTH_1024BIT, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	
	//Target API
	nRet = yaca_sign_initialize(&hContext, YACA_DIGEST_SHA512, hKey);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_sign_initialize", YacaGetError(nRet),yaca_key_destroy(hKey));
		
	yaca_context_destroy(hContext);	
	yaca_key_destroy(hKey);
	
	return 0;
}

//& type: auto
//& purpose: Initializes a signature context for HMAC
/**
* @testcase 			ITc_yaca_sign_initialize_hmac_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Initializes a signature context for HMAC
* @scenario				Initializes a signature context for HMAC
* @apicovered			yaca_sign_initialize_hmac,yaca_context_destroy,yaca_key_generate
* @passcase				If yaca_sign_initialize_hmac yaca_context_destroy,  and yaca_key_generate returns success
* @failcase				If yaca_sign_initialize_hmac yaca_context_destroy, or yaca_key_generate fails
* @precondition			Yaca initialize
* @postcondition		NA
*/
int ITc_yaca_sign_initialize_hmac_p(void)
{
	START_TEST;

	yaca_context_h hContext = YACA_CONTEXT_NULL;
	yaca_key_h hKey = YACA_KEY_NULL;
	
	int nRet = yaca_key_generate(YACA_KEY_TYPE_SYMMETRIC, YACA_KEY_LENGTH_256BIT, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	
	//Target API
	nRet = yaca_sign_initialize_hmac(&hContext, YACA_DIGEST_SHA512, hKey);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_sign_initialize_hmac", YacaGetError(nRet),yaca_key_destroy(hKey));
		
	yaca_context_destroy(hContext);
	yaca_key_destroy(hKey);
	
	return 0;
}

//& type: auto
//& purpose: Initializes a signature context for CMAC
/**
* @testcase 			ITc_yaca_sign_initialize_cmac_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Initializes a signature context for CMAC
* @scenario				Initializes a signature context for CMAC
* @apicovered			yaca_sign_initialize_cmac,yaca_context_destroy,yaca_key_generate
* @passcase				If yaca_sign_initialize_cmac yaca_context_destroy,  and yaca_key_generate returns success
* @failcase				If yaca_sign_initialize_cmac yaca_context_destroy, or yaca_key_generate fails
* @precondition			Yaca initialize
* @postcondition		NA
*/
int ITc_yaca_sign_initialize_cmac_p(void)
{
	START_TEST;

	yaca_context_h hContext = YACA_CONTEXT_NULL;
	yaca_key_h hKey = YACA_KEY_NULL;
	
	int nRet = yaca_key_generate(YACA_KEY_TYPE_SYMMETRIC, YACA_KEY_LENGTH_256BIT, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	
	//Target API
	nRet = yaca_sign_initialize_cmac(&hContext, YACA_ENCRYPT_AES, hKey);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_sign_initialize_cmac", YacaGetError(nRet),yaca_key_destroy(hKey));
		
	yaca_context_destroy(hContext);
	yaca_key_destroy(hKey);
	
	return 0;
}

//& type: auto
//& purpose: Feeds the data into the digital signature or MAC algorithm.
/**
* @testcase 			ITc_yaca_sign_update_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Feeds the data into the digital signature or MAC algorithm.
* @scenario				Feeds the data into the digital signature or MAC algorithm.
* @apicovered			yaca_sign_update,yaca_sign_finalize, yaca_context_destroy,yaca_key_generate
* @passcase				If yaca_sign_update, yaca_sign_finalize, yaca_context_destroy,  and yaca_key_generate returns success
* @failcase				If yaca_sign_update, yaca_sign_finalize, yaca_context_destroy, or yaca_key_generate fails
* @precondition			Yaca initialize
* @postcondition		NA
*/
int ITc_yaca_sign_update_p(void)
{
	START_TEST;

	yaca_context_h hContext = YACA_CONTEXT_NULL;
	yaca_key_h hKey = YACA_KEY_NULL;
	yaca_padding_e padding = YACA_PADDING_PKCS1_PSS;
	char *signature = NULL;
	size_t signature_len;
	
	int nRet = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, YACA_KEY_LENGTH_1024BIT, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
		
	nRet = yaca_sign_initialize(&hContext, YACA_DIGEST_SHA512, hKey);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_sign_initialize", YacaGetError(nRet),yaca_key_destroy(hKey));
		
	nRet = yaca_context_set_property(hContext, YACA_PROPERTY_PADDING, (char*)(&padding), sizeof(padding));
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_set_property", YacaGetError(nRet),yaca_context_destroy(hContext);yaca_key_destroy(hKey));
	
	//Target API
	nRet = yaca_sign_update(hContext, lorem4096, LOREM4096_SIZE);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_sign_update", YacaGetError(nRet),yaca_context_destroy(hContext);yaca_key_destroy(hKey));
		
	nRet = yaca_context_get_output_length(hContext, 0, &signature_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_get_output_length", YacaGetError(nRet),yaca_context_destroy(hContext);yaca_key_destroy(hKey));

	nRet = yaca_malloc(signature_len, (void**)&signature);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_malloc", YacaGetError(nRet),yaca_context_destroy(hContext);yaca_key_destroy(hKey));

	//Target API
	nRet = yaca_sign_finalize(hContext, signature, &signature_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_sign_finalize", YacaGetError(nRet),yaca_context_destroy(hContext);yaca_key_destroy(hKey);yaca_free(signature));
	
	yaca_free(signature);
	yaca_context_destroy(hContext);
	yaca_key_destroy(hKey);
	
	return 0;
}


//& type: auto
//& purpose: Initializes a signature verification context for asymmetric signatures
/**
* @testcase 			ITc_yaca_verify_initialize_update_finalize_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Initializes a signature verification context for asymmetric signatures
* @scenario				Initializes a signature verification context for asymmetric signatures
* @apicovered			yaca_verify_initialize, yaca_sign_update, yaca_verify_finalize, yaca_sign_finalize, yaca_context_destroy,yaca_key_generate
* @passcase				If yaca_verify_initialize, yaca_sign_update, yaca_verify_finalize, yaca_sign_finalize, yaca_context_destroy,  and yaca_key_generate returns success
* @failcase				If yaca_verify_initialize, yaca_sign_update, yaca_verify_finalize, yaca_sign_finalize, yaca_context_destroy, or yaca_key_generate fails
* @precondition			Yaca initialize
* @postcondition		NA
*/
int ITc_yaca_verify_initialize_update_finalize_p(void)
{
	START_TEST;

	yaca_context_h hContext = YACA_CONTEXT_NULL;
	yaca_key_h hKey = YACA_KEY_NULL;
	yaca_key_h pub = YACA_KEY_NULL;
	yaca_padding_e padding = YACA_PADDING_PKCS1_PSS;
	char *signature = NULL;
	size_t signature_len;
	
	int nRet = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, YACA_KEY_LENGTH_1024BIT, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
		
	nRet = yaca_sign_initialize(&hContext, YACA_DIGEST_SHA512, hKey);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_sign_initialize", YacaGetError(nRet),yaca_key_destroy(hKey));
		
	nRet = yaca_context_set_property(hContext, YACA_PROPERTY_PADDING, (char*)(&padding), sizeof(padding));
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_set_property", YacaGetError(nRet),yaca_context_destroy(hContext);yaca_key_destroy(hKey));
	
	nRet = yaca_sign_update(hContext, lorem4096, LOREM4096_SIZE);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_sign_update", YacaGetError(nRet),yaca_context_destroy(hContext);yaca_key_destroy(hKey));
		
	nRet = yaca_context_get_output_length(hContext, 0, &signature_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_get_output_length", YacaGetError(nRet),yaca_context_destroy(hContext);yaca_key_destroy(hKey));

	nRet = yaca_malloc(signature_len, (void**)&signature);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_malloc", YacaGetError(nRet),yaca_context_destroy(hContext);yaca_key_destroy(hKey));
	
	nRet = yaca_sign_finalize(hContext, signature, &signature_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_sign_finalize", YacaGetError(nRet),yaca_context_destroy(hContext);yaca_key_destroy(hKey);yaca_free(signature));
	
	yaca_context_destroy(hContext);
	
	nRet = 	yaca_key_extract_public(hKey, &pub);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_extract_public", YacaGetError(nRet),yaca_context_destroy(hContext);yaca_key_destroy(hKey);yaca_free(signature));

	//Target API	
	nRet = 	yaca_verify_initialize(&hContext, YACA_DIGEST_SHA512, pub);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_verify_initialize", YacaGetError(nRet),yaca_context_destroy(hContext);yaca_key_destroy(hKey);yaca_free(signature));
	
	nRet = 	yaca_context_set_property(hContext, YACA_PROPERTY_PADDING, (char*)(&padding), sizeof(padding));
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_set_property", YacaGetError(nRet),yaca_context_destroy(hContext);yaca_key_destroy(hKey);yaca_free(signature));

	//Target API	
	nRet = 	yaca_verify_update(hContext, lorem4096, LOREM4096_SIZE);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_verify_update", YacaGetError(nRet),yaca_context_destroy(hContext);yaca_key_destroy(hKey);yaca_free(signature));
	
	//Target API	
	nRet = 	yaca_verify_finalize(hContext, signature, signature_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_verify_update", YacaGetError(nRet),yaca_context_destroy(hContext);yaca_key_destroy(hKey);yaca_free(signature));
	
	yaca_free(signature);
	yaca_context_destroy(hContext);
	yaca_key_destroy(hKey);
	
	return 0;
}
/** @} */
/** @} */