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
#include <yaca_seal.h>
#include <yaca_crypto.h>
#include <yaca_key.h>

#include "lorem.h"

#include <dlog.h>

//& set: Yaca

/**
 * @function        utc_yaca_seal_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_yaca_seal_startup(void)
{
	yaca_initialize();
}

/**
 * @function        utc_yaca_seal_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_yaca_seal_cleanup(void)
{
	yaca_cleanup();
}

/**
 * @testcase        utc_yaca_seal_initialize_p
 * @since_tizen     3.0
 * @description     Initializes an asymmetric encryption context.
 * @scenario        Initializes an asymmetric encryption context with valid parameters.
 */
int utc_yaca_seal_initialize_p(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_CBC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key_pub = YACA_KEY_NULL;
	yaca_key_h key_priv = YACA_KEY_NULL;
	yaca_key_h sym_key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, YACA_KEY_LENGTH_2048BIT, &key_priv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(key_priv, &key_pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_seal_initialize(&ctx, key_pub, algo, bcm, key_bit_len, &sym_key, &iv);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	yaca_key_destroy(sym_key);
	yaca_key_destroy(iv);
	yaca_key_destroy(key_pub);
	yaca_key_destroy(key_priv);

	return 0;
}

/**
 * @testcase        utc_yaca_seal_initialize_n
 * @since_tizen     3.0
 * @description     Initializes an asymmetric encryption context.
 * @scenario        Initializes an asymmetric encryption context with invalid parameters.
 */
int utc_yaca_seal_initialize_n(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_CBC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key_pub = YACA_KEY_NULL;
	yaca_key_h key_priv = YACA_KEY_NULL;
	yaca_key_h sym_key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, YACA_KEY_LENGTH_2048BIT, &key_priv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(key_priv, &key_pub);
	assert_eq(ret, YACA_ERROR_NONE);

	// checked
	ret = yaca_seal_initialize(NULL, key_pub, algo, bcm, key_bit_len, &sym_key, &iv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	// checked
	ret = yaca_seal_initialize(&ctx, NULL, algo, bcm, key_bit_len, &sym_key, &iv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_seal_initialize(&ctx, key_pub, (yaca_encrypt_algorithm_e)-1, bcm, key_bit_len, &sym_key, &iv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_seal_initialize(&ctx, key_pub, algo, (yaca_block_cipher_mode_e)-1, key_bit_len, &sym_key, &iv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_seal_initialize(&ctx, key_pub, algo, bcm, 0, &sym_key, &iv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	//ret = yaca_seal_initialize(&ctx, key_pub, algo, bcm, key_bit_len, NULL, &iv);
	//assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	//ret = yaca_seal_initialize(&ctx, key_pub, algo, bcm, key_bit_len, &sym_key, NULL);
	//assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_context_destroy(ctx);
	yaca_key_destroy(sym_key);
	yaca_key_destroy(iv);
	yaca_key_destroy(key_pub);
	yaca_key_destroy(key_priv);

	return 0;
}

/**
 * @testcase        utc_yaca_seal_update_p
 * @since_tizen     3.0
 * @description     Encrypts piece of the data.
 * @scenario        Encrypts piece of the data with valid parameters.
 */
int utc_yaca_seal_update_p(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_CBC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key_pub = YACA_KEY_NULL;
	yaca_key_h key_priv = YACA_KEY_NULL;
	yaca_key_h sym_key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;

	char *enc = NULL;
	size_t enc_len;

	size_t block_len;
	size_t output_len;
	size_t written_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, YACA_KEY_LENGTH_2048BIT, &key_priv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(key_priv, &key_pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_seal_initialize(&ctx, key_pub, algo, bcm, key_bit_len, &sym_key, &iv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	enc_len = output_len + block_len;
	ret = yaca_malloc(enc_len, (void**)&enc);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = enc_len;
	ret = yaca_seal_update(ctx, lorem4096, LOREM4096_SIZE, enc, &written_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_free(enc);
	yaca_context_destroy(ctx);
	yaca_key_destroy(sym_key);
	yaca_key_destroy(iv);
	yaca_key_destroy(key_pub);
	yaca_key_destroy(key_priv);

	return 0;
}

/**
 * @testcase        utc_yaca_seal_update_n
 * @since_tizen     3.0
 * @description     Encrypts piece of the data.
 * @scenario        Encrypts piece of the data with invalid parameters.
 */
int utc_yaca_seal_update_n(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_CBC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key_pub = YACA_KEY_NULL;
	yaca_key_h key_priv = YACA_KEY_NULL;
	yaca_key_h sym_key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;

	char *enc = NULL;
	size_t enc_len;

	size_t block_len;
	size_t output_len;
	size_t written_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, YACA_KEY_LENGTH_2048BIT, &key_priv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(key_priv, &key_pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_seal_initialize(&ctx, key_pub, algo, bcm, key_bit_len, &sym_key, &iv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	enc_len = output_len + block_len;
	ret = yaca_malloc(enc_len, (void**)&enc);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = enc_len;
	ret = yaca_seal_update(NULL, lorem4096, LOREM4096_SIZE, enc, &written_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_seal_update(ctx, NULL, LOREM4096_SIZE, enc, &written_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_seal_update(ctx, lorem4096, 0, enc, &written_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_seal_update(ctx, lorem4096, LOREM4096_SIZE, NULL, &written_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_seal_update(ctx, lorem4096, LOREM4096_SIZE, enc, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_free(enc);
	yaca_context_destroy(ctx);
	yaca_key_destroy(sym_key);
	yaca_key_destroy(iv);
	yaca_key_destroy(key_pub);
	yaca_key_destroy(key_priv);

	return 0;
}

/**
 * @testcase        utc_yaca_seal_finalize_p
 * @since_tizen     3.0
 * @description     Encrypts the final piece of the data.
 * @scenario        Encrypts the final piece of the data with valid parameters.
 */
int utc_yaca_seal_finalize_p(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_CBC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
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

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, YACA_KEY_LENGTH_2048BIT, &key_priv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(key_priv, &key_pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_seal_initialize(&ctx, key_pub, algo, bcm, key_bit_len, &sym_key, &iv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	enc_len = output_len + block_len;
	ret = yaca_malloc(enc_len, (void**)&enc);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = enc_len;
	ret = yaca_seal_update(ctx, lorem4096, LOREM4096_SIZE, enc, &written_len);
	assert_eq(ret, YACA_ERROR_NONE);

	rem = enc_len - written_len;
	ret = yaca_seal_finalize(ctx, enc + written_len, &rem);
	assert_eq(ret, YACA_ERROR_NONE);

	enc_len = written_len + rem;

	yaca_free(enc);
	yaca_context_destroy(ctx);
	yaca_key_destroy(sym_key);
	yaca_key_destroy(iv);
	yaca_key_destroy(key_pub);
	yaca_key_destroy(key_priv);

	return 0;
}

/**
 * @testcase        utc_yaca_seal_finalize_n
 * @since_tizen     3.0
 * @description     Encrypts the final piece of the data.
 * @scenario        Encrypts the final piece of the data with invalid parameters.
 */
int utc_yaca_seal_finalize_n(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_CBC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
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

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, YACA_KEY_LENGTH_2048BIT, &key_priv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(key_priv, &key_pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_seal_initialize(&ctx, key_pub, algo, bcm, key_bit_len, &sym_key, &iv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	enc_len = output_len + block_len;
	ret = yaca_malloc(enc_len, (void**)&enc);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = enc_len;
	ret = yaca_seal_update(ctx, lorem4096, LOREM4096_SIZE, enc, &written_len);
	assert_eq(ret, YACA_ERROR_NONE);

	rem = enc_len - written_len;
	ret = yaca_seal_finalize(NULL, enc + written_len, &rem);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_seal_finalize(ctx, NULL, &rem);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_seal_finalize(ctx, enc + written_len, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_free(enc);
	yaca_context_destroy(ctx);
	yaca_key_destroy(sym_key);
	yaca_key_destroy(iv);
	yaca_key_destroy(key_pub);
	yaca_key_destroy(key_priv);

	return 0;
}

/**
 * @testcase        utc_yaca_open_initialize_p
 * @since_tizen     3.0
 * @description     Initializes an asymmetric decryption context.
 * @scenario        Initializes an asymmetric decryption context with valid parameters.
 */
int utc_yaca_open_initialize_p(void)
{
	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key_priv = YACA_KEY_NULL;
	yaca_key_h key_pub = YACA_KEY_NULL;
	yaca_key_h sym_key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;

	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_CBC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, YACA_KEY_LENGTH_2048BIT, &key_priv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(key_priv, &key_pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_seal_initialize(&ctx, key_pub, algo, bcm, key_bit_len, &sym_key, &iv);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	ctx = YACA_CONTEXT_NULL;

	ret = yaca_open_initialize(&ctx, key_priv, algo, bcm, key_bit_len, sym_key, iv);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	yaca_key_destroy(sym_key);
	yaca_key_destroy(iv);
	yaca_key_destroy(key_pub);
	yaca_key_destroy(key_priv);

	return 0;
}

/**
 * @testcase        utc_yaca_open_initialize_n
 * @since_tizen     3.0
 * @description     Initializes an asymmetric decryption context.
 * @scenario        Initializes an asymmetric decryption context with invalid parameters.
 */
int utc_yaca_open_initialize_n(void)
{
	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key_priv = YACA_KEY_NULL;
	yaca_key_h key_pub = YACA_KEY_NULL;
	yaca_key_h sym_key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;

	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_CBC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, YACA_KEY_LENGTH_1024BIT, &key_priv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(key_priv, &key_pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_seal_initialize(&ctx, key_pub, algo, bcm, key_bit_len, &sym_key, &iv);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	ctx = YACA_CONTEXT_NULL;

	ret = yaca_open_initialize(NULL, key_priv, algo, bcm, key_bit_len, sym_key, iv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_open_initialize(&ctx, NULL, algo, bcm, key_bit_len, sym_key, iv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_open_initialize(&ctx, key_priv, (yaca_encrypt_algorithm_e)-1, bcm, key_bit_len, sym_key, iv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_open_initialize(&ctx, key_priv, algo, (yaca_block_cipher_mode_e) -1, key_bit_len, sym_key, iv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_open_initialize(&ctx, key_priv, algo, bcm, 0, sym_key, iv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_open_initialize(&ctx, key_priv, algo, bcm, key_bit_len, NULL, iv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_open_initialize(&ctx, key_priv, algo, bcm, key_bit_len, sym_key, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_context_destroy(ctx);
	yaca_key_destroy(sym_key);
	yaca_key_destroy(iv);
	yaca_key_destroy(key_pub);
	yaca_key_destroy(key_priv);

	return 0;
}

/**
 * @testcase        utc_yaca_open_update_p
 * @since_tizen     3.0
 * @description     Decrypts piece of the data.
 * @scenario        Decrypts piece of the data with valid parameters.
 */
int utc_yaca_open_update_p(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_CBC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key_pub = YACA_KEY_NULL;
	yaca_key_h key_priv = YACA_KEY_NULL;
	yaca_key_h sym_key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;

	char *enc = NULL;
	size_t enc_len;
	char *dec = NULL;
	size_t dec_len;

	size_t block_len;
	size_t output_len;
	size_t written_len;
	size_t rem;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, YACA_KEY_LENGTH_2048BIT, &key_priv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(key_priv, &key_pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_seal_initialize(&ctx, key_pub, algo, bcm, key_bit_len, &sym_key, &iv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	enc_len = output_len + block_len;
	ret = yaca_malloc(enc_len, (void**)&enc);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = enc_len;
	ret = yaca_seal_update(ctx, lorem4096, LOREM4096_SIZE, enc, &written_len);
	assert_eq(ret, YACA_ERROR_NONE);

	rem = enc_len - written_len;
	ret = yaca_seal_finalize(ctx, enc + written_len, &rem);
	assert_eq(ret, YACA_ERROR_NONE);

	enc_len = written_len + rem;
	yaca_context_destroy(ctx);
	ctx = YACA_CONTEXT_NULL;

	ret = yaca_open_initialize(&ctx, key_priv, algo, bcm, key_bit_len, sym_key, iv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	dec_len = output_len + block_len;
	ret = yaca_malloc(dec_len, (void**)&dec);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = dec_len;
	ret = yaca_open_update(ctx, enc, enc_len, dec, &written_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_free(enc);
	yaca_free(dec);
	yaca_context_destroy(ctx);
	yaca_key_destroy(sym_key);
	yaca_key_destroy(iv);
	yaca_key_destroy(key_pub);
	yaca_key_destroy(key_priv);

	return 0;
}

/**
 * @testcase        utc_yaca_open_update_n
 * @since_tizen     3.0
 * @description     Decrypts piece of the data.
 * @scenario        Decrypts piece of the data with invalid parameters.
 */
int utc_yaca_open_update_n(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_CBC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key_pub = YACA_KEY_NULL;
	yaca_key_h key_priv = YACA_KEY_NULL;
	yaca_key_h sym_key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;

	char *enc = NULL;
	size_t enc_len;
	char *dec = NULL;
	size_t dec_len;

	size_t block_len;
	size_t output_len;
	size_t written_len;
	size_t rem;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, YACA_KEY_LENGTH_2048BIT, &key_priv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(key_priv, &key_pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_seal_initialize(&ctx, key_pub, algo, bcm, key_bit_len, &sym_key, &iv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	enc_len = output_len + block_len;
	ret = yaca_malloc(enc_len, (void**)&enc);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = enc_len;
	ret = yaca_seal_update(ctx, lorem4096, LOREM4096_SIZE, enc, &written_len);
	assert_eq(ret, YACA_ERROR_NONE);

	rem = enc_len - written_len;
	ret = yaca_seal_finalize(ctx, enc + written_len, &rem);
	assert_eq(ret, YACA_ERROR_NONE);

	enc_len = written_len + rem;
	yaca_context_destroy(ctx);
	ctx = YACA_CONTEXT_NULL;

	ret = yaca_open_initialize(&ctx, key_priv, algo, bcm, key_bit_len, sym_key, iv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	dec_len = output_len + block_len;
	ret = yaca_malloc(dec_len, (void**)&dec);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = dec_len;
	ret = yaca_open_update(NULL, enc, enc_len, dec, &written_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_open_update(ctx, NULL, enc_len, dec, &written_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_open_update(ctx, enc, 0, dec, &written_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_open_update(ctx, enc, enc_len, NULL, &written_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_open_update(ctx, enc, enc_len, dec, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_free(enc);
	yaca_free(dec);
	yaca_context_destroy(ctx);
	yaca_key_destroy(sym_key);
	yaca_key_destroy(iv);
	yaca_key_destroy(key_pub);
	yaca_key_destroy(key_priv);

	return 0;
}

/**
 * @testcase        utc_yaca_open_finalize_p
 * @since_tizen     3.0
 * @description     Decrypts the final piece of the data.
 * @scenario        Decrypts the final piece of the data with valid parameters.
 */
int utc_yaca_open_finalize_p(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_3DES_3TDEA;
	yaca_block_cipher_mode_e bcm = YACA_BCM_CFB;
	size_t key_bit_len = YACA_KEY_LENGTH_192BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key_pub = YACA_KEY_NULL;
	yaca_key_h key_priv = YACA_KEY_NULL;
	yaca_key_h sym_key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;

	char *enc = NULL;
	size_t enc_len;
	char *dec = NULL;
	size_t dec_len;

	size_t block_len;
	size_t output_len;
	size_t written_len;
	size_t rem;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, YACA_KEY_LENGTH_2048BIT, &key_priv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(key_priv, &key_pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_seal_initialize(&ctx, key_pub, algo, bcm, key_bit_len, &sym_key, &iv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	enc_len = output_len + block_len;
	ret = yaca_malloc(enc_len, (void**)&enc);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = enc_len;
	ret = yaca_seal_update(ctx, lorem4096, LOREM4096_SIZE, enc, &written_len);
	assert_eq(ret, YACA_ERROR_NONE);

	rem = enc_len - written_len;
	ret = yaca_seal_finalize(ctx, enc + written_len, &rem);
	assert_eq(ret, YACA_ERROR_NONE);

	enc_len = written_len + rem;

	yaca_context_destroy(ctx);
	ctx = YACA_CONTEXT_NULL;

	ret = yaca_open_initialize(&ctx, key_priv, algo, bcm, key_bit_len, sym_key, iv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	dec_len = output_len + block_len;
	ret = yaca_malloc(dec_len, (void**)&dec);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = 0;
	ret = yaca_open_update(ctx, enc, enc_len, dec, &written_len);
	assert_eq(ret, YACA_ERROR_NONE);

	rem = 0;
	ret = yaca_open_finalize(ctx, dec + written_len, &rem);
	assert_eq(ret, YACA_ERROR_NONE);

	dec_len = written_len + rem;
	assert_eq(LOREM4096_SIZE, dec_len);

	int i;
	for (i = 0; i < LOREM4096_SIZE; i++)
		assert_eq(lorem4096[i], dec[i]);

	yaca_free(enc);
	yaca_free(dec);
	yaca_context_destroy(ctx);
	yaca_key_destroy(sym_key);
	yaca_key_destroy(iv);
	yaca_key_destroy(key_pub);
	yaca_key_destroy(key_priv);

	return 0;
}

/**
 * @testcase        utc_yaca_open_finalize_n
 * @since_tizen     3.0
 * @description     Decrypts the final piece of the data.
 * @scenario        Decrypts the final piece of the data with invalid parameters.
 */
int utc_yaca_open_finalize_n(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_3DES_3TDEA;
	yaca_block_cipher_mode_e bcm = YACA_BCM_CFB;
	size_t key_bit_len = YACA_KEY_LENGTH_192BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key_pub = YACA_KEY_NULL;
	yaca_key_h key_priv = YACA_KEY_NULL;
	yaca_key_h sym_key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;

	char *enc = NULL;
	size_t enc_len;
	char *dec = NULL;
	size_t dec_len;

	size_t block_len;
	size_t output_len;
	size_t written_len;
	size_t rem;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, YACA_KEY_LENGTH_2048BIT, &key_priv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(key_priv, &key_pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_seal_initialize(&ctx, key_pub, algo, bcm, key_bit_len, &sym_key, &iv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	enc_len = output_len + block_len;
	ret = yaca_malloc(enc_len, (void**)&enc);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = enc_len;
	ret = yaca_seal_update(ctx, lorem4096, LOREM4096_SIZE, enc, &written_len);
	assert_eq(ret, YACA_ERROR_NONE);

	rem = enc_len - written_len;
	ret = yaca_seal_finalize(ctx, enc + written_len, &rem);
	assert_eq(ret, YACA_ERROR_NONE);

	enc_len = written_len + rem;

	yaca_context_destroy(ctx);
	ctx = YACA_CONTEXT_NULL;

	ret = yaca_open_initialize(&ctx, key_priv, algo, bcm, key_bit_len, sym_key, iv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	dec_len = output_len + block_len;
	ret = yaca_malloc(dec_len, (void**)&dec);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = dec_len;
	ret = yaca_open_update(ctx, enc, enc_len, dec, &written_len);
	assert_eq(ret, YACA_ERROR_NONE);

	rem = dec_len - written_len;
	ret = yaca_open_finalize(NULL, dec + written_len, &rem);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_open_finalize(ctx, NULL, &rem);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_open_finalize(ctx, dec + written_len, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_free(enc);
	yaca_free(dec);
	yaca_context_destroy(ctx);
	yaca_key_destroy(sym_key);
	yaca_key_destroy(iv);
	yaca_key_destroy(key_pub);
	yaca_key_destroy(key_priv);

	return 0;
}


