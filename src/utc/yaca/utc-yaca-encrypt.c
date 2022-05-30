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
#include <yaca_encrypt.h>
#include <yaca_crypto.h>
#include <yaca_key.h>
#include <yaca_simple.h>

#include "lorem.h"

//& set: Yaca

/**
 * @function        utc_yaca_encrypt_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_yaca_encrypt_startup(void)
{
	yaca_initialize();
}

/**
 * @function        utc_yaca_encrypt_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_yaca_encrypt_cleanup(void)
{
	yaca_cleanup();
}

/**
 * @testcase        utc_yaca_encrypt_get_iv_bit_length_p
 * @since_tizen     3.0
 * @description     Returns the recommended/default length of the IV for a given encryption configuration.
 * @scenario        Returns the recommended/default length of the IV for a given encryption configuration
 *                  with valid parameters.
 */
int utc_yaca_encrypt_get_iv_bit_length_p(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_ECB;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;
	yaca_key_h key = YACA_KEY_NULL;
	size_t iv_bit_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_derive_pbkdf2("foo bar", "123456789", 10, 1000, YACA_DIGEST_SHA256, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_encrypt_get_iv_bit_length(algo, bcm, key_bit_len, &iv_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_encrypt_get_iv_bit_length_n
 * @since_tizen     3.0
 * @description     Returns the recommended/default length of the IV for a given encryption configuration.
 * @scenario        Returns the recommended/default length of the IV for a given encryption configuration
 *                  with invalid parameters.
 */
int utc_yaca_encrypt_get_iv_bit_length_n(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_ECB;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;
	yaca_key_h key = YACA_KEY_NULL;
	size_t iv_bit_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_derive_pbkdf2("foo bar", "123456789", 10, 1000, YACA_DIGEST_SHA256, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_encrypt_get_iv_bit_length((yaca_encrypt_algorithm_e) -1, bcm, key_bit_len, &iv_bit_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_encrypt_get_iv_bit_length(algo, (yaca_block_cipher_mode_e) -1, key_bit_len, &iv_bit_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_encrypt_get_iv_bit_length(algo, bcm, 0, &iv_bit_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_encrypt_get_iv_bit_length(algo, bcm, key_bit_len, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_encrypt_initialize_p
 * @since_tizen     3.0
 * @description     Initializes the encrypt context.
 * @scenario        Initializes the encrypt context.
 */
int utc_yaca_encrypt_initialize_p(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_ECB;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;
	size_t iv_bit_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_encrypt_get_iv_bit_length(algo, bcm, key_bit_len, &iv_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	if (iv_bit_len > 0) {
		ret = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv);
		assert_eq(ret, YACA_ERROR_NONE);
	}

	ret = yaca_encrypt_initialize(&ctx, algo, bcm, key, iv);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	yaca_key_destroy(iv);
	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_encrypt_initialize_n
 * @since_tizen     3.0
 * @description     Initializes the encrypt context.
 * @scenario        Initializes the encrypt context with invalid parameters.
 */
int utc_yaca_encrypt_initialize_n(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_ECB;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;
	size_t iv_bit_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_encrypt_get_iv_bit_length(algo, bcm, key_bit_len, &iv_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	if (iv_bit_len > 0) {
		ret = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv);
		assert_eq(ret, YACA_ERROR_NONE);
	}

	ret = yaca_encrypt_initialize(NULL, algo, bcm, key, iv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_encrypt_initialize(&ctx, (yaca_encrypt_algorithm_e) -1, bcm, key, iv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_encrypt_initialize(&ctx, algo, (yaca_block_cipher_mode_e) -1, key, iv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_encrypt_initialize(&ctx, algo, bcm, NULL, iv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_context_destroy(ctx);
	yaca_key_destroy(iv);
	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_encrypt_update_p
 * @since_tizen     3.0
 * @description     Encrypts chunk of the data.
 * @scenario        Encrypts chunk of the data with valid parameters.
 */
int utc_yaca_encrypt_update_p(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_ECB;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;
	size_t iv_bit_len;

	char *enc = NULL;
	size_t enc_len;

	size_t block_len;
	size_t output_len;
	size_t written_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_encrypt_get_iv_bit_length(algo, bcm, key_bit_len, &iv_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	if (iv_bit_len > 0) {
		ret = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv);
		assert_eq(ret, YACA_ERROR_NONE);
	}

	ret = yaca_encrypt_initialize(&ctx, algo, bcm, key, iv);
	assert_eq(ret, YACA_ERROR_NONE);

	// For the update
	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	// For the finalize
	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	enc_len = output_len + block_len;
	ret = yaca_malloc(enc_len, (void**)&enc);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = enc_len;
	ret = yaca_encrypt_update(ctx, lorem4096, LOREM4096_SIZE, enc, &written_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	yaca_free(enc);
	yaca_key_destroy(iv);
	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_encrypt_update_n
 * @since_tizen     3.0
 * @description     Encrypts chunk of the data.
 * @scenario        Encrypts chunk of the data with invalid parameters.
 */
int utc_yaca_encrypt_update_n(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_ECB;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;
	size_t iv_bit_len;

	char *enc = NULL;
	size_t enc_len;

	size_t block_len;
	size_t output_len;
	size_t written_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_encrypt_get_iv_bit_length(algo, bcm, key_bit_len, &iv_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	if (iv_bit_len > 0) {
		ret = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv);
		assert_eq(ret, YACA_ERROR_NONE);
	}

	ret = yaca_encrypt_initialize(&ctx, algo, bcm, key, iv);
	assert_eq(ret, YACA_ERROR_NONE);

	// For the update
	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	// For the finalize
	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	enc_len = output_len + block_len;
	ret = yaca_malloc(enc_len, (void**)&enc);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = enc_len;
	ret = yaca_encrypt_update(NULL, lorem4096, LOREM4096_SIZE, enc, &written_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_encrypt_update(ctx, NULL, LOREM4096_SIZE, enc, &written_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_encrypt_update(ctx, lorem4096, 0, enc, &written_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_encrypt_update(ctx, lorem4096, LOREM4096_SIZE, NULL, &written_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_encrypt_update(ctx, lorem4096, LOREM4096_SIZE, enc, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_context_destroy(ctx);
	yaca_free(enc);
	yaca_key_destroy(iv);
	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_encrypt_finalize_p
 * @since_tizen     3.0
 * @description     Encrypts the final chunk of the data.
 * @scenario        Encrypts the final chunk of the data with valid parameters.
 */
int utc_yaca_encrypt_finalize_p(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_ECB;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;
	size_t iv_bit_len;

	char *enc = NULL;
	size_t enc_len;

	size_t block_len;
	size_t output_len;
	size_t written_len;
	size_t rem;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_encrypt_get_iv_bit_length(algo, bcm, key_bit_len, &iv_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	if (iv_bit_len > 0) {
		ret = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv);
		assert_eq(ret, YACA_ERROR_NONE);
	}

	ret = yaca_encrypt_initialize(&ctx, algo, bcm, key, iv);
	assert_eq(ret, YACA_ERROR_NONE);

	// For the update
	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	// For the finalize
	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	enc_len = output_len + block_len;
	ret = yaca_malloc(enc_len, (void**)&enc);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = enc_len;
	ret = yaca_encrypt_update(ctx, lorem4096, LOREM4096_SIZE, enc, &written_len);
	assert_eq(ret, YACA_ERROR_NONE);

	rem = enc_len - written_len;
	ret = yaca_encrypt_finalize(ctx, enc + written_len, &rem);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	yaca_free(enc);
	yaca_key_destroy(iv);
	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_encrypt_finalize_n
 * @since_tizen     3.0
 * @description     Encrypts the final chunk of the data.
 * @scenario        Encrypts the final chunk of the data with invalid parameters.
 */
int utc_yaca_encrypt_finalize_n(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_ECB;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;
	size_t iv_bit_len;

	char *enc = NULL;
	size_t enc_len;

	size_t block_len;
	size_t output_len;
	size_t written_len;
	size_t rem;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_encrypt_get_iv_bit_length(algo, bcm, key_bit_len, &iv_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	if (iv_bit_len > 0) {
		ret = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv);
		assert_eq(ret, YACA_ERROR_NONE);
	}

	ret = yaca_encrypt_initialize(&ctx, algo, bcm, key, iv);
	assert_eq(ret, YACA_ERROR_NONE);

	// For the update
	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	// For the finalize
	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	enc_len = output_len + block_len;
	ret = yaca_malloc(enc_len, (void**)&enc);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = enc_len;
	ret = yaca_encrypt_update(ctx, lorem4096, LOREM4096_SIZE, enc, &written_len);
	assert_eq(ret, YACA_ERROR_NONE);

	rem = enc_len - written_len;
	ret = yaca_encrypt_finalize(NULL, enc + written_len, &rem);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_encrypt_finalize(ctx, NULL, &rem);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_encrypt_finalize(ctx, enc + written_len, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_context_destroy(ctx);
	yaca_free(enc);
	yaca_key_destroy(iv);
	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_decrypt_initialize_p
 * @since_tizen     3.0
 * @description     Initializes the decrypt context.
 * @scenario        Initializes the decrypt context.
 */
int utc_yaca_decrypt_initialize_p(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_ECB;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;
	size_t iv_bit_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_encrypt_get_iv_bit_length(algo, bcm, key_bit_len, &iv_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	if (iv_bit_len > 0) {
		ret = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv);
		assert_eq(ret, YACA_ERROR_NONE);
	}

	ret = yaca_decrypt_initialize(&ctx, algo, bcm, key, iv);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	yaca_key_destroy(iv);
	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_decrypt_initialize_n
 * @since_tizen     3.0
 * @description     Initializes the decrypt context.
 * @scenario        Initializes the decrypt context with invalid parameters.
 */
int utc_yaca_decrypt_initialize_n(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_ECB;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;
	size_t iv_bit_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_encrypt_get_iv_bit_length(algo, bcm, key_bit_len, &iv_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	if (iv_bit_len > 0) {
		ret = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv);
		assert_eq(ret, YACA_ERROR_NONE);
	}

	ret = yaca_decrypt_initialize(NULL, algo, bcm, key, iv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_decrypt_initialize(&ctx, (yaca_encrypt_algorithm_e) -1, bcm, key, iv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_decrypt_initialize(&ctx, algo, (yaca_block_cipher_mode_e) -1, key, iv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_decrypt_initialize(&ctx, algo, bcm, NULL, iv);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_context_destroy(ctx);
	yaca_key_destroy(iv);
	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_decrypt_update_p
 * @since_tizen     3.0
 * @description     Encrypts chunk of the data.
 * @scenario        Encrypts chunk of the data with valid parameters.
 */
int utc_yaca_decrypt_update_p(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_ECB;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;
	size_t iv_bit_len;

	char enc[256] = {0, };
	size_t enc_len = sizeof(enc);
	char *dec = NULL;
	size_t dec_len;

	size_t block_len;
	size_t output_len;
	size_t written_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_encrypt_get_iv_bit_length(algo, bcm, key_bit_len, &iv_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	if (iv_bit_len > 0) {
		ret = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv);
		assert_eq(ret, YACA_ERROR_NONE);
	}

	ret = yaca_decrypt_initialize(&ctx, algo, bcm, key, iv);
	assert_eq(ret, YACA_ERROR_NONE);

	// For the update
	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	// For the finalize
	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	dec_len = output_len + block_len;
	ret = yaca_malloc(dec_len, (void**)&dec);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = dec_len;
	ret = yaca_decrypt_update(ctx, enc, enc_len, dec, &written_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	yaca_free(dec);
	yaca_key_destroy(iv);
	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_decrypt_update_n
 * @since_tizen     3.0
 * @description     Encrypts chunk of the data.
 * @scenario        Encrypts chunk of the data with invalid parameters.
 */
int utc_yaca_decrypt_update_n(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_ECB;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;
	size_t iv_bit_len;

	char enc[256] = {0, };
	size_t enc_len = sizeof(enc);
	char *dec = NULL;
	size_t dec_len;

	size_t block_len;
	size_t output_len;
	size_t written_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_encrypt_get_iv_bit_length(algo, bcm, key_bit_len, &iv_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	if (iv_bit_len > 0) {
		ret = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv);
		assert_eq(ret, YACA_ERROR_NONE);
	}

	ret = yaca_decrypt_initialize(&ctx, algo, bcm, key, iv);
	assert_eq(ret, YACA_ERROR_NONE);

	// For the update
	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	// For the finalize
	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	dec_len = output_len + block_len;
	ret = yaca_malloc(dec_len, (void**)&dec);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = dec_len;
	ret = yaca_decrypt_update(NULL, enc, enc_len, dec, &written_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_decrypt_update(ctx, NULL, enc_len, dec, &written_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_decrypt_update(ctx, enc, 0, dec, &written_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_decrypt_update(ctx, enc, enc_len, NULL, &written_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_decrypt_update(ctx, enc, enc_len, dec, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_context_destroy(ctx);
	yaca_free(dec);
	yaca_key_destroy(iv);
	yaca_key_destroy(key);

	return 0;
}

int encrypt_advanced(const yaca_encrypt_algorithm_e algo,
						const yaca_block_cipher_mode_e bcm,
						const yaca_key_type_e key_type,
						const size_t key_bit_len)
{
	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;
	size_t iv_bit_len;

	char *enc = NULL;
	char *dec = NULL;
	size_t enc_len;
	size_t dec_len;

	size_t block_len;
	size_t output_len;
	size_t written_len;

	/* Key generation */
	assert_eq(yaca_key_generate(key_type, key_bit_len, &key), YACA_ERROR_NONE);

	assert_eq(yaca_encrypt_get_iv_bit_length(algo, bcm, key_bit_len, &iv_bit_len), YACA_ERROR_NONE);

	assert_eq(iv_bit_len > 0 && yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv), YACA_ERROR_NONE);

	/* Encryption */
	{
		assert_eq(yaca_encrypt_initialize(&ctx, algo, bcm, key, iv), YACA_ERROR_NONE);

		/* For the update */
		assert_eq(yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len), YACA_ERROR_NONE);

		/* For the finalize */
		assert_eq(yaca_context_get_output_length(ctx, 0, &block_len), YACA_ERROR_NONE);

		/* Calculate max output: size of update + final chunks */
		enc_len = output_len + block_len;
		assert_eq(yaca_malloc(enc_len, (void**)&enc), YACA_ERROR_NONE);

		assert_eq(yaca_encrypt_update(ctx, lorem4096, LOREM4096_SIZE, enc, &written_len), YACA_ERROR_NONE);

		enc_len = written_len;

		assert_eq(yaca_encrypt_finalize(ctx, enc + written_len, &written_len), YACA_ERROR_NONE);

		enc_len += written_len;

		yaca_context_destroy(ctx);
		ctx = YACA_CONTEXT_NULL;
	}

	/* Decryption */
	{
		assert_eq(yaca_decrypt_initialize(&ctx, algo, bcm, key, iv), YACA_ERROR_NONE);

		/* For the update */
		assert_eq(yaca_context_get_output_length(ctx, enc_len, &output_len), YACA_ERROR_NONE);

		/* For the finalize */
		assert_eq(yaca_context_get_output_length(ctx, 0, &block_len), YACA_ERROR_NONE);

		/* Calculate max output: size of update + final chunks */
		dec_len = output_len + block_len;
		assert_eq(yaca_malloc(dec_len, (void**)&dec), YACA_ERROR_NONE);

		assert_eq(yaca_decrypt_update(ctx, enc, enc_len, dec, &written_len), YACA_ERROR_NONE);

		dec_len = written_len;

		assert_eq(yaca_decrypt_finalize(ctx, dec + written_len, &written_len), YACA_ERROR_NONE);

		dec_len += written_len;
	}

	yaca_free(dec);
	yaca_free(enc);
	yaca_context_destroy(ctx);
	yaca_key_destroy(iv);
	yaca_key_destroy(key);

	return 0;
}


/*
 * @testcase        utc_yaca_decrypt_finalize_p
 * @since_tizen     3.0
 * @description     Encrypts the final chunk of the data.
 * @scenario        Encrypts the final chunk of the data with valid parameters.
 */
int utc_yaca_decrypt_finalize_p(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_ECB;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	assert_eq(encrypt_advanced(algo, bcm, key_type, key_bit_len), 0);

	algo = YACA_ENCRYPT_3DES_3TDEA;
	bcm = YACA_BCM_OFB;
	key_type = YACA_KEY_TYPE_DES;
	key_bit_len = YACA_KEY_LENGTH_192BIT;

	assert_eq(encrypt_advanced(algo, bcm, key_type, key_bit_len), 0);

	algo = YACA_ENCRYPT_CAST5;
	bcm = YACA_BCM_CFB;
	key_type = YACA_KEY_TYPE_SYMMETRIC;
	key_bit_len = YACA_KEY_LENGTH_UNSAFE_40BIT;

	assert_eq(encrypt_advanced(algo, bcm, key_type, key_bit_len), 0);

	algo = YACA_ENCRYPT_UNSAFE_RC2;
	bcm = YACA_BCM_CBC;
	key_type = YACA_KEY_TYPE_SYMMETRIC;
	key_bit_len = YACA_KEY_LENGTH_UNSAFE_8BIT;

	assert_eq(encrypt_advanced(algo, bcm, key_type, key_bit_len), 0);

	algo = YACA_ENCRYPT_UNSAFE_RC4;
	bcm = YACA_BCM_NONE;
	key_type = YACA_KEY_TYPE_SYMMETRIC;
	key_bit_len = YACA_KEY_LENGTH_2048BIT;

	assert_eq(encrypt_advanced(algo, bcm, key_type, key_bit_len), 0);

	return 0;
}

/*
 * @testcase        utc_yaca_decrypt_finalize_p2
 * @since_tizen     3.0
 * @description     Encrypts the final chunk of the data.
 * @scenario        Encrypts the final chunk of the data with AES GCM.
 */
int utc_yaca_decrypt_finalize_p2(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_GCM;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;
	size_t iv_bit_len = YACA_KEY_LENGTH_IV_128BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key = YACA_KEY_NULL;
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

	int ret = YACA_ERROR_NONE;

	// Key generation
	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	// IV generation
	ret = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_zalloc(aad_len, (void**)&aad);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_randomize_bytes(aad, aad_len);
	assert_eq(ret, YACA_ERROR_NONE);

	// Encryption
	ret = yaca_encrypt_initialize(&ctx, algo, bcm, key, iv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_set_property(ctx, YACA_PROPERTY_GCM_AAD, aad, aad_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	enc_len = output_len + block_len;
	ret = yaca_malloc(enc_len, (void**)&enc);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = enc_len;
	ret = yaca_encrypt_update(ctx, lorem4096, LOREM4096_SIZE, enc, &written_len);
	assert_eq(ret, YACA_ERROR_NONE);

	rem = enc_len - written_len;
	ret = yaca_encrypt_finalize(ctx, enc + written_len, &rem);
	assert_eq(ret, YACA_ERROR_NONE);

	enc_len = rem + written_len;

	// Set the tag length and get the tag after final encryption
	ret = yaca_context_set_property(ctx, YACA_PROPERTY_GCM_TAG_LEN, (void*)&tag_len, sizeof(tag_len));
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_property(ctx, YACA_PROPERTY_GCM_TAG, (void**)&tag, &tag_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	ctx = YACA_CONTEXT_NULL;

	// Decryption
	ret = yaca_decrypt_initialize(&ctx, algo, bcm, key, iv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_set_property(ctx, YACA_PROPERTY_GCM_AAD, aad, aad_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	dec_len = output_len + block_len;
	ret = yaca_malloc(dec_len, (void**)&dec);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = dec_len;
	ret = yaca_decrypt_update(ctx, enc, enc_len, dec, &written_len);
	assert_eq(ret, YACA_ERROR_NONE);

	rem = dec_len - written_len;

	// Set expected tag value before final decryption
	ret = yaca_context_set_property(ctx, YACA_PROPERTY_GCM_TAG, tag, tag_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_decrypt_finalize(ctx, dec + written_len, &rem);
	assert_eq(ret, YACA_ERROR_NONE);

	dec_len = rem + written_len;

	yaca_free(enc);
	yaca_free(dec);
	yaca_free(tag);
	yaca_free(aad);
	yaca_context_destroy(ctx);
	yaca_key_destroy(iv);
	yaca_key_destroy(key);

	return 0;
}

/*
 * @testcase        utc_yaca_decrypt_finalize_p3
 * @since_tizen     3.0
 * @description     Encrypts the final chunk of the data with AES CCM.
 * @scenario        Encrypts the final chunk of the data with AES CCM.
 */
int utc_yaca_decrypt_finalize_p3(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_CCM;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;
	size_t iv_bit_len = YACA_KEY_LENGTH_IV_64BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;

	char *enc = NULL;
	char *dec = NULL;
	size_t enc_len;
	size_t dec_len;

	char *aad = NULL;
	char *tag = NULL;
	size_t aad_len = 16;
	size_t tag_len = 14;

	size_t block_len;
	size_t output_len;
	size_t written_len;
	size_t len;

	/* Key generation */
	assert_eq(yaca_key_generate(key_type, key_bit_len, &key), YACA_ERROR_NONE);

	/* IV generation */
	assert_eq(yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv), YACA_ERROR_NONE);

	assert_eq(yaca_zalloc(aad_len, (void**)&aad), YACA_ERROR_NONE);

	assert_eq(yaca_randomize_bytes(aad, aad_len), YACA_ERROR_NONE);

	/* Encryption */
	{
		assert_eq(yaca_encrypt_initialize(&ctx, algo, bcm, key, iv), YACA_ERROR_NONE);

		/* Set tag length (optionally) */
		assert_eq(yaca_context_set_property(ctx, YACA_PROPERTY_CCM_TAG_LEN,
									  (void*)&tag_len, sizeof(tag_len)), YACA_ERROR_NONE);

		/* The total plain text length must be passed (only needed if AAD is passed) */
		assert_eq(yaca_encrypt_update(ctx, NULL, LOREM4096_SIZE , NULL, &len), YACA_ERROR_NONE);

		assert_eq(yaca_context_set_property(ctx, YACA_PROPERTY_CCM_AAD, aad, aad_len), YACA_ERROR_NONE);

		/* For the update */
		assert_eq(yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len), YACA_ERROR_NONE);

		/* For the finalize */
		assert_eq(yaca_context_get_output_length(ctx, 0, &block_len), YACA_ERROR_NONE);

		/* Calculate max output: size of update + final chunks */
		enc_len = output_len + block_len;
		assert_eq(yaca_malloc(enc_len, (void**)&enc), YACA_ERROR_NONE);

		assert_eq(yaca_encrypt_update(ctx, lorem4096, LOREM4096_SIZE, enc, &written_len), YACA_ERROR_NONE);

		enc_len = written_len;

		assert_eq(yaca_encrypt_finalize(ctx, enc + written_len, &written_len), YACA_ERROR_NONE);

		enc_len += written_len;

		/* Get the tag after final encryption */
		assert_eq(yaca_context_get_property(ctx, YACA_PROPERTY_CCM_TAG, (void**)&tag, &tag_len), YACA_ERROR_NONE);

		yaca_context_destroy(ctx);
		ctx = YACA_CONTEXT_NULL;
	}

	/* Decryption */
	{
		assert_eq(yaca_decrypt_initialize(&ctx, algo, bcm, key, iv), YACA_ERROR_NONE);

		/* Set expected tag value */
		assert_eq(yaca_context_set_property(ctx, YACA_PROPERTY_CCM_TAG, tag, tag_len), YACA_ERROR_NONE);

		/* The total encrypted text length must be passed (only needed if AAD is passed) */
		assert_eq(yaca_decrypt_update(ctx, NULL, enc_len , NULL, &len), YACA_ERROR_NONE);

		assert_eq(yaca_context_set_property(ctx, YACA_PROPERTY_CCM_AAD, aad, aad_len), YACA_ERROR_NONE);

		/* For the update */
		assert_eq(yaca_context_get_output_length(ctx, enc_len, &output_len), YACA_ERROR_NONE);

		/* For the finalize */
		assert_eq(yaca_context_get_output_length(ctx, 0, &block_len), YACA_ERROR_NONE);

		/* Calculate max output: size of update + final chunks */
		dec_len = output_len + block_len;
		assert_eq(yaca_malloc(dec_len, (void**)&dec), YACA_ERROR_NONE);

		/* The tag verify is performed when you call the final yaca_decrypt_update(),
		 * there is no call to yaca_decrypt_finalize() */
		assert_eq(yaca_decrypt_update(ctx, enc, enc_len, dec, &written_len), YACA_ERROR_NONE);

		dec_len = written_len;
	}

	yaca_free(enc);
	yaca_free(dec);
	yaca_free(tag);
	yaca_free(aad);
	yaca_context_destroy(ctx);
	yaca_key_destroy(iv);
	yaca_key_destroy(key);

	return 0;
}

/*
 * @testcase        utc_yaca_decrypt_finalize_p4
 * @since_tizen     3.0
 * @description     Wrap and Unwrap a key with a AES key.
 * @scenario        Wrap and Unwrap a key.
 */
int utc_yaca_decrypt_finalize_p4(void)
{
	int ret;
	yaca_key_h sym_key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;
	yaca_key_h aes_key = YACA_KEY_NULL;

	size_t iv_bit_len;
	char *key_data = NULL;
	size_t key_data_len;
	char *wrapped_key = NULL;
	size_t wrapped_key_len;

	ret = yaca_key_generate(YACA_KEY_TYPE_SYMMETRIC, YACA_KEY_LENGTH_256BIT, &aes_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_generate(YACA_KEY_TYPE_SYMMETRIC, YACA_KEY_LENGTH_192BIT, &sym_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_encrypt_get_iv_bit_length(YACA_ENCRYPT_AES,
										 YACA_BCM_WRAP,
										 YACA_KEY_LENGTH_192BIT,
										 &iv_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	if (iv_bit_len > 0) {
		ret = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv);
		assert_eq(ret, YACA_ERROR_NONE);
	}

	/* Key wrapping */
	{
		ret = yaca_key_export(aes_key, YACA_KEY_FORMAT_DEFAULT, YACA_KEY_FILE_FORMAT_RAW, NULL,
							  &key_data, &key_data_len);
		assert_eq(ret, YACA_ERROR_NONE);

		ret = yaca_simple_encrypt(YACA_ENCRYPT_AES, YACA_BCM_WRAP, sym_key, iv,
								  key_data, key_data_len,
								  &wrapped_key, &wrapped_key_len);
		assert_eq(ret, YACA_ERROR_NONE);

	}

	yaca_free(key_data);
	key_data = NULL;
	yaca_key_destroy(aes_key);
	aes_key = YACA_KEY_NULL;

	/* Key unwrapping */
	{
		ret = yaca_simple_decrypt(YACA_ENCRYPT_AES, YACA_BCM_WRAP, sym_key, iv,
								  wrapped_key, wrapped_key_len,
								  &key_data, &key_data_len);
		assert_eq(ret, YACA_ERROR_NONE);

		ret = yaca_key_import(YACA_KEY_TYPE_SYMMETRIC, NULL, key_data, key_data_len, &aes_key);
		assert_eq(ret, YACA_ERROR_NONE);
	}

	yaca_key_destroy(aes_key);
	yaca_key_destroy(sym_key);
	yaca_key_destroy(iv);
	yaca_free(key_data);
	yaca_free(wrapped_key);

	return 0;
}

/**
 * @testcase        utc_yaca_decrypt_finalize_n
 * @since_tizen     3.0
 * @description     Encrypts the final chunk of the data.
 * @scenario        Encrypts the final chunk of the data with invalid parameters.
 */
int utc_yaca_decrypt_finalize_n(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_ECB;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;
	size_t iv_bit_len;

	char enc[256] = {0, };
	size_t enc_len = sizeof(enc);
	char *dec = NULL;
	size_t dec_len;

	size_t block_len;
	size_t output_len;
	size_t written_len;
	size_t rem;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_encrypt_get_iv_bit_length(algo, bcm, key_bit_len, &iv_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	if (iv_bit_len > 0) {
		ret = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv);
		assert_eq(ret, YACA_ERROR_NONE);
	}

	ret = yaca_decrypt_initialize(&ctx, algo, bcm, key, iv);
	assert_eq(ret, YACA_ERROR_NONE);

	// For the update
	ret = yaca_context_get_output_length(ctx, LOREM4096_SIZE, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	// For the finalize
	ret = yaca_context_get_output_length(ctx, 0, &block_len);
	assert_eq(ret, YACA_ERROR_NONE);

	dec_len = output_len + block_len;
	ret = yaca_malloc(dec_len, (void**)&dec);
	assert_eq(ret, YACA_ERROR_NONE);

	written_len = dec_len;
	ret = yaca_decrypt_update(ctx, enc, enc_len, dec, &written_len);
	assert_eq(ret, YACA_ERROR_NONE);

	rem = dec_len - written_len;
	ret = yaca_decrypt_finalize(NULL, dec + written_len, &rem);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_decrypt_finalize(ctx, NULL, &rem);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_decrypt_finalize(ctx, dec + written_len, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_context_destroy(ctx);
	yaca_key_destroy(iv);
	yaca_key_destroy(key);

	return 0;
}
