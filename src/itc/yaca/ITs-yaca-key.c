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
 * @function 		ITs_yaca_key_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_yaca_key_startup(void)
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
 * @function 		ITs_yaca_key_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_yaca_key_cleanup(void)
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
//& purpose: Generates/Destroy yaca key.
/**
* @testcase 			ITc_yaca_key_generate_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Generates/Destroy yaca key.
* @scenario				Generates/Destroy yaca key.
* @apicovered			yaca_key_generate
* @passcase				If yaca_key_generate returns success
* @failcase				If yaca_key_generate fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_key_generate_p(void)
{
	START_TEST;

	yaca_key_h prv = YACA_KEY_NULL;
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	//Target API
	int nRet = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	
	yaca_key_destroy(prv);
	
	return 0;
}

//& type: auto
//& purpose: Gets key's type
/**
* @testcase 			ITc_yaca_key_get_type_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Gets key's type
* @scenario				Gets key's type
* @apicovered			yaca_key_generate, yaca_key_get_type
* @passcase				If yaca_key_generate, yaca_key_get_type returns success
* @failcase				If yaca_key_generate, yaca_key_get_type fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_key_get_type_p(void)
{
	START_TEST;

	yaca_key_h hKey = YACA_KEY_NULL;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t nKeyBitLen = YACA_KEY_LENGTH_256BIT;
	yaca_key_type_e eRetKeyType;
	int nRet = YACA_ERROR_NONE;

	nRet = yaca_key_generate(key_type, nKeyBitLen, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	CHECK_HANDLE(hKey, "yaca_key_generate");
	
	//Target API
	nRet = yaca_key_get_type(hKey, &eRetKeyType);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_get_type", YacaGetError(nRet));
		
	yaca_key_destroy(hKey);
		
	return 0;
}

//& type: auto
//& purpose: Gets key's length
/**
* @testcase 			ITc_yaca_key_get_bit_length_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Gets key's length
* @scenario				Gets key's length
* @apicovered			yaca_key_generate, yaca_key_get_bit_length
* @passcase				If yaca_key_generate, yaca_key_get_bit_length returns success
* @failcase				If yaca_key_generate, yaca_key_get_bit_length fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_key_get_bit_length_p(void)
{
	START_TEST;

	yaca_key_h hKey = YACA_KEY_NULL;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t nKeyBitLen = YACA_KEY_LENGTH_256BIT;
	size_t nRetKeyBitLen;
	int nRet = YACA_ERROR_NONE;

	nRet = yaca_key_generate(key_type, nKeyBitLen, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	CHECK_HANDLE(hKey, "yaca_key_generate");
	
	//Target API
	nRet = yaca_key_get_bit_length(hKey, &nRetKeyBitLen);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_get_bit_length", YacaGetError(nRet));
		
	yaca_key_destroy(hKey);
		
	return 0;
}


//& type: auto
//& purpose: Imports/export key to arbitrary format
/**
* @testcase 			ITc_yaca_key_export_import_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Imports/export a key to arbitrary format
* @scenario				Imports/export a key to arbitrary format
* @apicovered			yaca_key_generate, yaca_key_export, yaca_key_import
* @passcase				If yaca_key_generate, yaca_key_export, yaca_key_import returns success
* @failcase				If yaca_key_generate, yaca_key_export, yaca_key_import fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_key_export_import_p(void)
{
	START_TEST;

	yaca_key_h hKey = YACA_KEY_NULL;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t nKeyBitLen = YACA_KEY_LENGTH_256BIT;
	int nRet = YACA_ERROR_NONE;
	char *pFileFormatExport = NULL;
	size_t encodedLen;
	yaca_key_h hImportedKey = YACA_KEY_NULL;	
	
	nRet = yaca_key_generate(key_type, nKeyBitLen, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	CHECK_HANDLE(hKey, "yaca_key_generate");

	//Target API
	nRet = yaca_key_export(hKey, YACA_KEY_FORMAT_DEFAULT, YACA_KEY_FILE_FORMAT_RAW, NULL, &pFileFormatExport, &encodedLen);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_export", YacaGetError(nRet), yaca_key_destroy(hKey));
	
	//Target API
	nRet = yaca_key_import(key_type, NULL, pFileFormatExport, encodedLen, &hImportedKey);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_import", YacaGetError(nRet), yaca_free(pFileFormatExport);yaca_key_destroy(hKey));		
	CHECK_HANDLE_CLEANUP(hImportedKey, "yaca_key_import", yaca_key_destroy(hKey));
	
	yaca_free(pFileFormatExport);	
	yaca_key_destroy(hImportedKey);	
	yaca_key_destroy(hKey);
	
	return 0;
}

//& type: auto
//& purpose: Generates a secure key from parameters.
/**
* @testcase 			ITc_yaca_key_generate_from_parameters_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Generates a secure key from parameters.
* @scenario				Generates a secure key from parameters.
* @apicovered			yaca_key_generate, yaca_key_generate_from_parameters
* @passcase				If yaca_key_generate, yaca_key_generate_from_parameters returns success
* @failcase				If yaca_key_generate, yaca_key_generate_from_parameters fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_key_generate_from_parameters_p(void)
{
	START_TEST;

	yaca_key_h hKey = YACA_KEY_NULL;
	yaca_key_h keyParam = YACA_KEY_NULL;
	int nRet = YACA_ERROR_NONE;

	nRet = yaca_key_generate(YACA_KEY_TYPE_DSA_PARAMS, YACA_KEY_LENGTH_512BIT, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	CHECK_HANDLE(hKey, "yaca_key_generate");
	
	//Target API
	nRet = yaca_key_generate_from_parameters(hKey, &keyParam);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_generate_from_parameters", YacaGetError(nRet), yaca_key_destroy(hKey));
	CHECK_HANDLE(keyParam, "yaca_key_generate_from_parameters");	
	
	yaca_key_destroy(keyParam);	
	yaca_key_destroy(hKey);
	
	return 0;
}

//& type: auto
//& purpose: Extracts parameters from a key
/**
* @testcase 			ITc_yaca_key_extract_parameters_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Extracts parameters from a key
* @scenario				Extracts parameters from a key
* @apicovered			yaca_key_generate, yaca_key_extract_parameters
* @passcase				If yaca_key_generate, yaca_key_extract_parameters returns success
* @failcase				If yaca_key_generate, yaca_key_extract_parameters fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_key_extract_parameters_p(void)
{
	START_TEST;

	yaca_key_h hKey = YACA_KEY_NULL;
	yaca_key_h hPub = YACA_KEY_NULL;
	yaca_key_h hParams = YACA_KEY_NULL;
	int nRet = YACA_ERROR_NONE;

	nRet = yaca_key_generate(YACA_KEY_TYPE_EC_PRIV, YACA_KEY_LENGTH_EC_PRIME256V1, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	CHECK_HANDLE(hKey, "yaca_key_generate");
	
	nRet = yaca_key_extract_public(hKey, &hPub);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_extract_public", YacaGetError(nRet),yaca_key_destroy(hKey));
	CHECK_HANDLE(hPub, "yaca_key_extract_public");
	
	//Target API
	nRet = yaca_key_extract_parameters(hPub, &hParams);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_extract_parameters", YacaGetError(nRet), yaca_key_destroy(hPub);yaca_key_destroy(hKey));
	CHECK_HANDLE(hParams, "yaca_key_extract_parameters");	
	
	yaca_key_destroy(hParams);	
	yaca_key_destroy(hPub);
	yaca_key_destroy(hKey);
	
	return 0;
}

//& type: auto
//& purpose: Derives a key from Diffie-Hellman keys
/**
* @testcase 			ITc_yaca_key_derive_dh_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Derives a key from Diffie-Hellman keys
* @scenario				Derives a key from Diffie-Hellman keys
* @apicovered			yaca_key_generate, yaca_key_extract_parameters, yaca_key_derive_dh
* @passcase				If yaca_key_generate, yaca_key_extract_parameters, yaca_key_derive_dh returns success
* @failcase				If yaca_key_generate, yaca_key_extract_parameters, yaca_key_derive_dh fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_key_derive_dh_p(void)
{
	START_TEST;

	yaca_key_h hDhPeerPriKey = YACA_KEY_NULL;
	yaca_key_h hDhPriKey = YACA_KEY_NULL;
	yaca_key_h hPub = YACA_KEY_NULL;
	yaca_key_h hParams = YACA_KEY_NULL;
	char *secret = NULL;
	size_t secret_len;
	int nRet = YACA_ERROR_NONE;

	nRet = yaca_key_generate(YACA_KEY_TYPE_DH_PRIV, YACA_KEY_LENGTH_DH_RFC_2048_256, &hDhPeerPriKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	CHECK_HANDLE(hDhPeerPriKey, "yaca_key_generate");
	
	nRet = yaca_key_extract_public(hDhPeerPriKey, &hPub);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_extract_public", YacaGetError(nRet),yaca_key_destroy(hDhPeerPriKey));
	CHECK_HANDLE(hPub, "yaca_key_extract_public");
		
	nRet = yaca_key_extract_parameters(hPub, &hParams);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_extract_parameters", YacaGetError(nRet), yaca_key_destroy(hPub);yaca_key_destroy(hDhPeerPriKey));
	CHECK_HANDLE(hParams, "yaca_key_extract_parameters");	
	
	nRet = yaca_key_generate_from_parameters(hParams, &hDhPriKey);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_generate_from_parameters", YacaGetError(nRet), yaca_key_destroy(hPub);yaca_key_destroy(hDhPeerPriKey));
	CHECK_HANDLE(hDhPriKey, "yaca_key_generate_from_parameters");	
	
	//Target API
	nRet = yaca_key_derive_dh(hDhPriKey, hPub, &secret, &secret_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_derive_dh", YacaGetError(nRet), yaca_key_destroy(hPub);yaca_key_destroy(hParams);yaca_key_destroy(hDhPeerPriKey));
	CHECK_HANDLE(hParams, "yaca_key_derive_dh");	
	
	yaca_free(secret);
	yaca_key_destroy(hDhPriKey);
	yaca_key_destroy(hParams);	
	yaca_key_destroy(hPub);
	yaca_key_destroy(hDhPeerPriKey);
	
	return 0;
}

//& type: auto
//& purpose: Derives a key from a secret
/**
* @testcase 			ITc_yaca_key_derive_kdf_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Derives a key from a secret
* @scenario				Derives a key from a secret
* @apicovered			yaca_key_generate, yaca_key_extract_parameters, yaca_key_derive_dh, yaca_key_derive_kdf
* @passcase				If yaca_key_generate, yaca_key_extract_parameters, yaca_key_derive_dh, yaca_key_derive_kdf returns success
* @failcase				If yaca_key_generate, yaca_key_extract_parameters, yaca_key_derive_dh, yaca_key_derive_kdf fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_key_derive_kdf_p(void)
{
	START_TEST;

	yaca_key_h hDhPeerPriKey = YACA_KEY_NULL;
	yaca_key_h hDhPriKey = YACA_KEY_NULL;
	yaca_key_h hPub = YACA_KEY_NULL;
	yaca_key_h hParams = YACA_KEY_NULL;
	char *secret = NULL;
	size_t secret_len;
	char *pTempMaterial = NULL;
	size_t nTempMaterialLen;
	size_t nKeyMaterialLen;
	size_t nIvMaterialLen;
	int nRet = YACA_ERROR_NONE;

	nRet = yaca_key_generate(YACA_KEY_TYPE_DH_PRIV, YACA_KEY_LENGTH_DH_RFC_2048_256, &hDhPeerPriKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	CHECK_HANDLE(hDhPeerPriKey, "yaca_key_generate");
	
	nRet = yaca_key_extract_public(hDhPeerPriKey, &hPub);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_extract_public", YacaGetError(nRet),yaca_key_destroy(hDhPeerPriKey));
	CHECK_HANDLE(hPub, "yaca_key_extract_public");
		
	nRet = yaca_key_extract_parameters(hPub, &hParams);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_extract_parameters", YacaGetError(nRet), yaca_key_destroy(hPub);yaca_key_destroy(hDhPeerPriKey));
	CHECK_HANDLE(hParams, "yaca_key_extract_parameters");	
	
	nRet = yaca_key_generate_from_parameters(hParams, &hDhPriKey);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_generate_from_parameters", YacaGetError(nRet), yaca_key_destroy(hPub);yaca_key_destroy(hDhPeerPriKey));
	CHECK_HANDLE(hDhPriKey, "yaca_key_generate_from_parameters");	
		
	nRet = yaca_key_derive_dh(hDhPriKey, hPub, &secret, &secret_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_derive_dh", YacaGetError(nRet), yaca_key_destroy(hPub);yaca_key_destroy(hParams);yaca_key_destroy(hDhPeerPriKey));
	CHECK_HANDLE(hParams, "yaca_key_derive_dh");	
	if(secret == NULL)
	{
		FPRINTF("[Line : %d][%s] secret value is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	nKeyMaterialLen = YACA_KEY_LENGTH_192BIT / 8;
	nIvMaterialLen = YACA_KEY_LENGTH_IV_128BIT / 8;
	nTempMaterialLen = nKeyMaterialLen + nIvMaterialLen;
	
	//Target API
	nRet = yaca_key_derive_kdf(YACA_KDF_X962, YACA_DIGEST_SHA512, secret, secret_len, NULL, 0, nTempMaterialLen, &pTempMaterial);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_derive_kdf", YacaGetError(nRet), yaca_key_destroy(hPub);yaca_key_destroy(hParams);yaca_key_destroy(hDhPeerPriKey));
	CHECK_HANDLE(hParams, "yaca_key_derive_kdf");	
	
	yaca_free(pTempMaterial);	
	yaca_free(secret);
	yaca_key_destroy(hDhPriKey);
	yaca_key_destroy(hParams);	
	yaca_key_destroy(hPub);
	yaca_key_destroy(hDhPeerPriKey);
	
	return 0;
}
//& type: auto
//& purpose: Extracts public key from a private one.
/**
* @testcase 			ITc_yaca_key_extract_public_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Extracts public key from a private one.
* @scenario				Extracts public key from a private one.
* @apicovered			yaca_key_generate, yaca_key_extract_public
* @passcase				If yaca_key_generate, yaca_key_extract_public returns success
* @failcase				If yaca_key_generate, yaca_key_extract_public fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_key_extract_public_p(void)
{
	START_TEST;

	yaca_key_h hKey = YACA_KEY_NULL;
	yaca_key_h pubKeyExtract = YACA_KEY_NULL;
	int nRet = YACA_ERROR_NONE;

	nRet = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, YACA_KEY_LENGTH_1024BIT, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_generate", YacaGetError(nRet));
	CHECK_HANDLE(hKey, "yaca_key_generate");
	
	//Target API
	nRet = yaca_key_extract_public(hKey, &pubKeyExtract);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_key_extract_public", YacaGetError(nRet), yaca_key_destroy(hKey));
	CHECK_HANDLE(pubKeyExtract, "yaca_key_extract_public");	
		
	yaca_key_destroy(pubKeyExtract);	
	yaca_key_destroy(hKey);
	
	return 0;
}

//& type: auto
//& purpose: Derives a key from user password
/**
* @testcase 			ITc_yaca_key_derive_pbkdf2_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Derives a key from user password
* @scenario				Derives a key from user password
* @apicovered			yaca_key_generate, yaca_key_derive_pbkdf2
* @passcase				If yaca_key_generate, yaca_key_derive_pbkdf2 returns success
* @failcase				If yaca_key_generate, yaca_key_derive_pbkdf2 fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_key_derive_pbkdf2_p(void)
{
	START_TEST;
	
	yaca_key_h hKey = YACA_KEY_NULL;
	size_t nKeyBitLen = YACA_KEY_LENGTH_256BIT;
	int nRet = YACA_ERROR_NONE;

	//Target API
	nRet = yaca_key_derive_pbkdf2("foo bar", "123456789", 10, 1000,	YACA_DIGEST_SHA256, nKeyBitLen, &hKey);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_key_derive_pbkdf2", YacaGetError(nRet));
	CHECK_HANDLE(hKey, "yaca_key_derive_pbkdf2");
	
	return 0;
}

/** @} */
/** @} */