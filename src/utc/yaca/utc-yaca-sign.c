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
#include "assert.h"

#include <yaca_error.h>
#include <yaca_sign.h>
#include <yaca_crypto.h>
#include <yaca_key.h>

#include "lorem.h"

#include <dlog.h>

//& set: Yaca

/**
 * @function        utc_yaca_sign_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_yaca_sign_startup(void)
{
	yaca_initialize();
}

/**
 * @function        utc_yaca_sign_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_yaca_sign_cleanup(void)
{
	yaca_cleanup();
}

/**
 * @testcase        utc_yaca_sign_initialize_p
 * @since_tizen     3.0
 * @description     Initializes a signature context.
 * @scenario        Initializes a signature context with valid parameters.
 */
int utc_yaca_sign_initialize_p(void)
{
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h prv = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize(&ctx, YACA_DIGEST_SHA512, prv);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	yaca_key_destroy(prv);

	return 0;
}

/**
 * @testcase        utc_yaca_sign_initialize_n
 * @since_tizen     3.0
 * @description     Initializes a signature context.
 * @scenario        Initializes a signature context with invalid parameters.
 */
int utc_yaca_sign_initialize_n(void)
{
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h prv = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize(NULL, YACA_DIGEST_SHA512, prv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_sign_initialize(&ctx, (yaca_digest_algorithm_e) -1, prv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_sign_initialize(&ctx, YACA_DIGEST_SHA512, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_context_destroy(ctx);
	yaca_key_destroy(prv);

	return 0;
}

/**
 * @testcase        utc_yaca_sign_initialize_hmac_p
 * @since_tizen     3.0
 * @description     Initializes a signature context for HMAC.
 * @scenario        Initializes a signature context for HMAC with valid parameters.
 */
int utc_yaca_sign_initialize_hmac_p(void)
{
	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_SYMMETRIC, YACA_KEY_LENGTH_256BIT, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize_hmac(&ctx, YACA_DIGEST_SHA512, key);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_sign_initialize_hmac_n
 * @since_tizen     3.0
 * @description     Initializes a signature context for HMAC.
 * @scenario        Initializes a signature context for HMAC with invalid parameters.
 */
int utc_yaca_sign_initialize_hmac_n(void)
{
	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_SYMMETRIC, YACA_KEY_LENGTH_256BIT, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize_hmac(NULL, YACA_DIGEST_SHA512, key);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_sign_initialize_hmac(&ctx, (yaca_digest_algorithm_e) -1, key);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_sign_initialize_hmac(&ctx, YACA_DIGEST_SHA512, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_context_destroy(ctx);
	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_sign_initialize_cmac_p
 * @since_tizen     3.0
 * @description     Initializes a signature context for CMAC.
 * @scenario        Initializes a signature context for CMAC with valid parameters.
 */
int utc_yaca_sign_initialize_cmac_p(void)
{
	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_SYMMETRIC, YACA_KEY_LENGTH_256BIT, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize_cmac(&ctx, YACA_ENCRYPT_AES, key);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_sign_initialize_cmac_n
 * @since_tizen     3.0
 * @description     Initializes a signature context for CMAC.
 * @scenario        Initializes a signature context for CMAC with invalid parameters.
 */
int utc_yaca_sign_initialize_cmac_n(void)
{
	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_SYMMETRIC, YACA_KEY_LENGTH_256BIT, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize_cmac(NULL, YACA_ENCRYPT_AES, key);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_sign_initialize_cmac(&ctx, (yaca_encrypt_algorithm_e) -1, key);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_sign_initialize_cmac(&ctx, YACA_ENCRYPT_AES, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_context_destroy(ctx);
	yaca_key_destroy(key);

	return 0;
}


/**
 * @testcase        utc_yaca_sign_update_p
 * @since_tizen     3.0
 * @description     Feeds the data into the digital signature or MAC algorithm.
 * @scenario        Feeds the data into the digital signature or MAC algorithm with valid parameters.
 */
int utc_yaca_sign_update_p(void)
{
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h prv = YACA_KEY_NULL;
	yaca_padding_e padding = YACA_PADDING_PKCS1_PSS;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize(&ctx, YACA_DIGEST_SHA512, prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_set_property(ctx, YACA_PROPERTY_PADDING, (char*)(&padding), sizeof(padding));
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_update(ctx, lorem4096, LOREM4096_SIZE);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	yaca_key_destroy(prv);

	return 0;
}

/**
 * @testcase        utc_yaca_sign_update_n
 * @since_tizen     3.0
 * @description     Feeds the data into the digital signature or MAC algorithm.
 * @scenario        Feeds the data into the digital signature or MAC algorithm with invalid parameters.
 */
int utc_yaca_sign_update_n(void)
{
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h prv = YACA_KEY_NULL;
	yaca_padding_e padding = YACA_PADDING_PKCS1_PSS;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize(&ctx, YACA_DIGEST_SHA512, prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_set_property(ctx, YACA_PROPERTY_PADDING, (char*)(&padding), sizeof(padding));
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_update(NULL, lorem4096, LOREM4096_SIZE);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_sign_update(ctx, NULL, LOREM4096_SIZE);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_sign_update(ctx, lorem4096, 0);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_context_destroy(ctx);
	yaca_key_destroy(prv);

	return 0;
}

/**
 * @testcase        utc_yaca_sign_finalize_p
 * @since_tizen     3.0
 * @description     Calculates the final signature or MAC.
 * @scenario        Calculates the final signature or MAC with valid parameters.
 */
int utc_yaca_sign_finalize_p(void)
{
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h prv = YACA_KEY_NULL;
	yaca_padding_e padding = YACA_PADDING_PKCS1_PSS;

	char *signature = NULL;
	size_t signature_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize(&ctx, YACA_DIGEST_SHA512, prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_set_property(ctx, YACA_PROPERTY_PADDING, (char*)(&padding), sizeof(padding));
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_update(ctx, lorem4096, LOREM4096_SIZE);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_malloc(signature_len, (void**)&signature);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_finalize(ctx, signature, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	yaca_key_destroy(prv);

	return 0;
}

/**
 * @testcase        utc_yaca_sign_finalize_n
 * @since_tizen     3.0
 * @description     Calculates the final signature or MAC.
 * @scenario        Calculates the final signature or MAC with invalid parameters.
 */
int utc_yaca_sign_finalize_n(void)
{
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h prv = YACA_KEY_NULL;
	yaca_padding_e padding = YACA_PADDING_PKCS1_PSS;

	char *signature = NULL;
	size_t signature_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize(&ctx, YACA_DIGEST_SHA512, prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_set_property(ctx, YACA_PROPERTY_PADDING, (char*)(&padding), sizeof(padding));
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_update(ctx, lorem4096, LOREM4096_SIZE);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_malloc(signature_len, (void**)&signature);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_finalize(NULL, signature, &signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_sign_finalize(ctx, NULL, &signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_sign_finalize(ctx, signature, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_context_destroy(ctx);
	yaca_key_destroy(prv);

	return 0;
}

/**
 * @testcase        utc_yaca_verify_initialize_p
 * @since_tizen     3.0
 * @description     Initializes a signature verification context for asymmetric signatures.
 * @scenario        Initializes a signature verification context for asymmetric signatures
 *                  with valid parameters.
 */
int utc_yaca_verify_initialize_p(void)
{
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h prv = YACA_KEY_NULL;
	yaca_key_h pub = YACA_KEY_NULL;
	yaca_padding_e padding = YACA_PADDING_PKCS1_PSS;

	char *signature = NULL;
	size_t signature_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize(&ctx, YACA_DIGEST_SHA512, prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_set_property(ctx, YACA_PROPERTY_PADDING, (char*)(&padding), sizeof(padding));
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_update(ctx, lorem4096, LOREM4096_SIZE);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_malloc(signature_len, (void**)&signature);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_finalize(ctx, signature, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	ctx = YACA_CONTEXT_NULL;

	ret = yaca_key_extract_public(prv, &pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_verify_initialize(&ctx, YACA_DIGEST_SHA512, pub);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	yaca_key_destroy(prv);
	yaca_key_destroy(pub);

	return 0;
}

/**
 * @testcase        utc_yaca_verify_initialize_n
 * @since_tizen     3.0
 * @description     Initializes a signature verification context for asymmetric signatures.
 * @scenario        Initializes a signature verification context for asymmetric signatures
 *                  with invalid parameters.
 */
int utc_yaca_verify_initialize_n(void)
{
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h prv = YACA_KEY_NULL;
	yaca_key_h pub = YACA_KEY_NULL;
	yaca_padding_e padding = YACA_PADDING_PKCS1_PSS;

	char *signature = NULL;
	size_t signature_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize(&ctx, YACA_DIGEST_SHA512, prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_set_property(ctx, YACA_PROPERTY_PADDING, (char*)(&padding), sizeof(padding));
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_update(ctx, lorem4096, LOREM4096_SIZE);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_malloc(signature_len, (void**)&signature);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_finalize(ctx, signature, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	ctx = YACA_CONTEXT_NULL;

	ret = yaca_key_extract_public(prv, &pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_verify_initialize(NULL, YACA_DIGEST_SHA512, pub);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_verify_initialize(&ctx, (yaca_digest_algorithm_e) -1, pub);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_verify_initialize(&ctx, YACA_DIGEST_SHA512, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_context_destroy(ctx);
	yaca_key_destroy(prv);
	yaca_key_destroy(pub);

	return 0;
}

/**
 * @testcase        utc_yaca_verify_update_p
 * @since_tizen     3.0
 * @description     Feeds the data into the digital signature verification algorithm.
 * @scenario        Feeds the data into the digital signature verification algorithm with valid parameters.
 */
int utc_yaca_verify_update_p(void)
{
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h prv = YACA_KEY_NULL;
	yaca_key_h pub = YACA_KEY_NULL;
	yaca_padding_e padding = YACA_PADDING_PKCS1_PSS;

	char *signature = NULL;
	size_t signature_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize(&ctx, YACA_DIGEST_SHA512, prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_set_property(ctx, YACA_PROPERTY_PADDING, (char*)(&padding), sizeof(padding));
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_update(ctx, lorem4096, LOREM4096_SIZE);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_malloc(signature_len, (void**)&signature);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_finalize(ctx, signature, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	ctx = YACA_CONTEXT_NULL;

	ret = yaca_key_extract_public(prv, &pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_verify_initialize(&ctx, YACA_DIGEST_SHA512, pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_set_property(ctx, YACA_PROPERTY_PADDING, (char*)(&padding), sizeof(padding));
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_verify_update(ctx, lorem4096, LOREM4096_SIZE);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	yaca_key_destroy(prv);
	yaca_key_destroy(pub);

	return 0;
}

/**
 * @testcase        utc_yaca_verify_update_n
 * @since_tizen     3.0
 * @description     Feeds the data into the digital signature verification algorithm.
 * @scenario        Feeds the data into the digital signature verification algorithm with invalid parameters.
 */
int utc_yaca_verify_update_n(void)
{
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h prv = YACA_KEY_NULL;
	yaca_key_h pub = YACA_KEY_NULL;
	yaca_padding_e padding = YACA_PADDING_PKCS1_PSS;

	char *signature = NULL;
	size_t signature_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize(&ctx, YACA_DIGEST_SHA512, prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_set_property(ctx, YACA_PROPERTY_PADDING, (char*)(&padding), sizeof(padding));
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_update(ctx, lorem4096, LOREM4096_SIZE);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_malloc(signature_len, (void**)&signature);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_finalize(ctx, signature, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	ctx = YACA_CONTEXT_NULL;

	ret = yaca_key_extract_public(prv, &pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_verify_initialize(&ctx, YACA_DIGEST_SHA512, pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_set_property(ctx, YACA_PROPERTY_PADDING, (char*)(&padding), sizeof(padding));
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_verify_update(NULL, lorem4096, LOREM4096_SIZE);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_verify_update(ctx, NULL, LOREM4096_SIZE);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_verify_update(ctx, lorem4096, 0);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_context_destroy(ctx);
	yaca_key_destroy(prv);
	yaca_key_destroy(pub);

	return 0;
}

/**
 * @testcase        utc_yaca_verify_finalize_p
 * @since_tizen     3.0
 * @description     Performs the verification.
 * @scenario        Performs the verification with valid parameters.
 */
int utc_yaca_verify_finalize_p(void)
{
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h prv = YACA_KEY_NULL;
	yaca_key_h pub = YACA_KEY_NULL;
	yaca_padding_e padding = YACA_PADDING_PKCS1_PSS;

	char *signature = NULL;
	size_t signature_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize(&ctx, YACA_DIGEST_SHA512, prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_set_property(ctx, YACA_PROPERTY_PADDING, (char*)(&padding), sizeof(padding));
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_update(ctx, lorem4096, LOREM4096_SIZE);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_malloc(signature_len, (void**)&signature);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_finalize(ctx, signature, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	ctx = YACA_CONTEXT_NULL;

	ret = yaca_key_extract_public(prv, &pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_verify_initialize(&ctx, YACA_DIGEST_SHA512, pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_set_property(ctx, YACA_PROPERTY_PADDING, (char*)(&padding), sizeof(padding));
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_verify_update(ctx, lorem4096, LOREM4096_SIZE);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_verify_finalize(ctx, signature, signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	yaca_key_destroy(prv);
	yaca_key_destroy(pub);

	return 0;
}

/**
 * @testcase        utc_yaca_verify_finalize_n
 * @since_tizen     3.0
 * @description     Performs the verification.
 * @scenario        Performs the verification with invalid parameters.
 */
int utc_yaca_verify_finalize_n(void)
{
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h prv = YACA_KEY_NULL;
	yaca_key_h pub = YACA_KEY_NULL;
	yaca_padding_e padding = YACA_PADDING_PKCS1_PSS;

	char *signature = NULL;
	size_t signature_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize(&ctx, YACA_DIGEST_SHA512, prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_set_property(ctx, YACA_PROPERTY_PADDING, (char*)(&padding), sizeof(padding));
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_update(ctx, lorem4096, LOREM4096_SIZE);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_malloc(signature_len, (void**)&signature);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_finalize(ctx, signature, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	ctx = YACA_CONTEXT_NULL;

	ret = yaca_key_extract_public(prv, &pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_verify_initialize(&ctx, YACA_DIGEST_SHA512, pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_set_property(ctx, YACA_PROPERTY_PADDING, (char*)(&padding), sizeof(padding));
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_verify_update(ctx, lorem4096, LOREM4096_SIZE);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_verify_finalize(NULL, signature, signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_verify_finalize(ctx, NULL, signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_verify_finalize(ctx, signature, 0);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_context_destroy(ctx);
	yaca_key_destroy(prv);
	yaca_key_destroy(pub);

	return 0;
}


