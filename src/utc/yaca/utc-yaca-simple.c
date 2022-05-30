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
#include <yaca_simple.h>
#include <yaca_crypto.h>
#include <yaca_key.h>
#include <yaca_encrypt.h>

#include "lorem.h"

//& set: Yaca

/**
 * @function        utc_yaca_simple_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_yaca_simple_startup(void)
{
	yaca_initialize();
}

/**
 * @function        utc_yaca_simple_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_yaca_simple_cleanup(void)
{
	yaca_cleanup();
}

/**
 * @testcase        utc_yaca_simple_calculate_digest_p
 * @since_tizen     3.0
 * @description     Calculates a digest of a buffer.
 * @scenario        Calculates a digest of a buffer with valid parameters.
 */
int utc_yaca_simple_calculate_digest_p(void)
{
	int ret = YACA_ERROR_NONE;
	char *digest = NULL;
	size_t digest_len;

	ret = yaca_simple_calculate_digest(YACA_DIGEST_SHA256, lorem1024, 1024, &digest, &digest_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_free(digest);

	return 0;
}

/**
 * @testcase        utc_yaca_simple_calculate_digest_n
 * @since_tizen     3.0
 * @description     Calculates a digest of a buffer.
 * @scenario        Calculates a digest of a buffer with invalid parameters.
 */
int utc_yaca_simple_calculate_digest_n(void)
{
	int ret = YACA_ERROR_NONE;
	char *digest = NULL;
	size_t digest_len;

	ret = yaca_simple_calculate_digest((yaca_digest_algorithm_e)-1, lorem1024, 1024, &digest, &digest_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_calculate_digest(YACA_DIGEST_SHA256, NULL, 1024, &digest, &digest_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_calculate_digest(YACA_DIGEST_SHA256, lorem1024, 0, &digest, &digest_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_calculate_digest(YACA_DIGEST_SHA256, lorem1024, 1024, NULL, &digest_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_calculate_digest(YACA_DIGEST_SHA256, lorem1024, 1024, &digest, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_free(digest);

	return 0;
}

/**
 * @testcase        utc_yaca_simple_encrypt_p
 * @since_tizen     3.0
 * @description     Encrypts data using a symmetric cipher.
 * @scenario        Encrypts data using a symmetric cipher with valid parameters.
 */
int utc_yaca_simple_encrypt_p(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_ECB;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;

	char *enc = NULL;
	size_t enc_len = 0;
	size_t iv_bit_len = 0;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_derive_pbkdf2("foo bar", "123456789", 10, 1000,
			YACA_DIGEST_SHA256, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_encrypt_get_iv_bit_length(algo, bcm, key_bit_len, &iv_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	if (iv_bit_len > 0) {
		ret = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv);
		assert_eq(ret, YACA_ERROR_NONE);
	}

	ret = yaca_simple_encrypt(algo, bcm, key, iv, lorem4096, LOREM4096_SIZE, &enc, &enc_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_free(enc);
	yaca_key_destroy(iv);
	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_simple_encrypt_n
 * @since_tizen     3.0
 * @description     Encrypts data using a symmetric cipher.
 * @scenario        Encrypts data using a symmetric cipher with invalid parameters.
 */
int utc_yaca_simple_encrypt_n(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_ECB;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;

	char *enc = NULL;
	size_t enc_len = 0;
	size_t iv_bit_len = 0;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_derive_pbkdf2("foo bar", "123456789", 10, 1000,
			YACA_DIGEST_SHA256, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_encrypt_get_iv_bit_length(algo, bcm, key_bit_len, &iv_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	if (iv_bit_len > 0) {
		ret = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv);
		assert_eq(ret, YACA_ERROR_NONE);
	}

	ret = yaca_simple_encrypt((yaca_encrypt_algorithm_e)-1, bcm, key, iv, lorem4096,
								LOREM4096_SIZE, &enc, &enc_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_encrypt(algo, (yaca_block_cipher_mode_e)-1, key, iv, lorem4096,
								LOREM4096_SIZE, &enc, &enc_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_encrypt(algo, bcm, NULL, iv, lorem4096, LOREM4096_SIZE, &enc, &enc_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_encrypt(algo, bcm, key, iv, NULL, LOREM4096_SIZE, &enc, &enc_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_encrypt(algo, bcm, key, iv, lorem4096, 0, &enc, &enc_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_encrypt(algo, bcm, key, iv, lorem4096, LOREM4096_SIZE, NULL, &enc_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_key_destroy(iv);
	yaca_key_destroy(key);

	return 0;
}

int encrypt_simple(const yaca_encrypt_algorithm_e algo,
					const yaca_block_cipher_mode_e bcm,
					const size_t key_bit_len)
{
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;

	char *enc = NULL;
	char *dec = NULL;
	size_t enc_len;
	size_t dec_len;
	size_t iv_bit_len;

	int ret = YACA_ERROR_NONE;

	/* Key generation */
	if ((ret = yaca_key_derive_pbkdf2("foo bar", "123456789", 10, 1000,
								YACA_DIGEST_SHA256, key_bit_len, &key)) != YACA_ERROR_NONE)
		return ret;

	if ((ret = yaca_encrypt_get_iv_bit_length(algo, bcm, key_bit_len, &iv_bit_len)) != YACA_ERROR_NONE)
		goto exit;

	if (iv_bit_len > 0 && (ret = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv)) != YACA_ERROR_NONE)
		goto exit;

	if ((ret = yaca_simple_encrypt(algo, bcm, key, iv, lorem4096, LOREM4096_SIZE, &enc, &enc_len)) != YACA_ERROR_NONE)
		goto exit;

	if ((ret = yaca_simple_decrypt(algo, bcm, key, iv, enc, enc_len, &dec, &dec_len)) != YACA_ERROR_NONE)
		goto exit;

	assert_eq(LOREM4096_SIZE, dec_len);
	int i;
	for (i = 0; i < LOREM4096_SIZE; i++)
		assert_eq(lorem4096[i], dec[i]);

exit:
	yaca_free(enc);
	yaca_free(dec);
	yaca_key_destroy(iv);
	yaca_key_destroy(key);

	return ret;
}

/**
 * @testcase        utc_yaca_simple_decrypt_p
 * @since_tizen     3.0
 * @description     Decrypts data using a symmetric cipher.
 * @scenario        Decrypts data using a symmetric cipher with valid parameters.
 */
int utc_yaca_simple_decrypt_p(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_ECB;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	int ret = YACA_ERROR_NONE;

	ret = encrypt_simple(algo, bcm, key_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	algo = YACA_ENCRYPT_CAST5;
	bcm = YACA_BCM_CFB;
	key_bit_len = YACA_KEY_LENGTH_UNSAFE_40BIT;

	ret = encrypt_simple(algo, bcm, key_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	algo = YACA_ENCRYPT_UNSAFE_RC2;
	bcm = YACA_BCM_CBC;
	key_bit_len = YACA_KEY_LENGTH_UNSAFE_8BIT;

	ret = encrypt_simple(algo, bcm, key_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	algo = YACA_ENCRYPT_UNSAFE_RC4;
	bcm = YACA_BCM_NONE;
	key_bit_len = YACA_KEY_LENGTH_2048BIT;

	ret = encrypt_simple(algo, bcm, key_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_yaca_simple_decrypt_n
 * @since_tizen     3.0
 * @description     Decrypts data using a symmetric cipher.
 * @scenario        Decrypts data using a symmetric cipher with invalid parameters.
 */
int utc_yaca_simple_decrypt_n(void)
{
	yaca_encrypt_algorithm_e algo = YACA_ENCRYPT_AES;
	yaca_block_cipher_mode_e bcm = YACA_BCM_ECB;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_h iv = YACA_KEY_NULL;

	char *enc = NULL;
	size_t enc_len = 0;
	char *dec = NULL;
	size_t dec_len = 0;
	size_t iv_bit_len = 0;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_derive_pbkdf2("foo bar", "123456789", 10, 1000,
			YACA_DIGEST_SHA256, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_encrypt_get_iv_bit_length(algo, bcm, key_bit_len, &iv_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);

	if (iv_bit_len > 0) {
		ret = yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv);
		assert_eq(ret, YACA_ERROR_NONE);
	}

	ret = yaca_simple_encrypt(algo, bcm, key, iv, lorem4096, LOREM4096_SIZE, &enc, &enc_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_simple_decrypt((yaca_encrypt_algorithm_e)-1, bcm, key, iv, enc, enc_len, &dec, &dec_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_decrypt(algo, (yaca_block_cipher_mode_e)-1, key, iv, enc, enc_len, &dec, &dec_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_decrypt(algo, bcm, NULL, iv, enc, enc_len, &dec, &dec_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_decrypt(algo, bcm, key, iv, NULL, enc_len, &dec, &dec_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_decrypt(algo, bcm, key, iv, enc, 0, &dec, &dec_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_decrypt(algo, bcm, key, iv, enc, enc_len, NULL, &dec_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_decrypt(algo, bcm, key, iv, enc, enc_len, &dec, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_free(enc);
	yaca_free(dec);
	yaca_key_destroy(iv);
	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_simple_calculate_signature_p
 * @since_tizen     3.0
 * @description     Creates a signature using asymmetric private key.
 * @scenario        Creates a signature using asymmetric private key with valid parameters.
 */
int utc_yaca_simple_calculate_signature_p(void)
{
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	char *signature = NULL;
	size_t signature_len;

	yaca_key_h prv = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_simple_calculate_signature(YACA_DIGEST_SHA512, prv, lorem4096, LOREM4096_SIZE,
				  &signature, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_free(signature);
	yaca_key_destroy(prv);

	return 0;
}

/**
 * @testcase        utc_yaca_simple_calculate_signature_n
 * @since_tizen     3.0
 * @description     Creates a signature using asymmetric private key.
 * @scenario        Creates a signature using asymmetric private key with invalid parameters.
 */
int utc_yaca_simple_calculate_signature_n(void)
{
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	char *signature = NULL;
	size_t signature_len;

	yaca_key_h prv = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_simple_calculate_signature((yaca_digest_algorithm_e)-1, prv, lorem4096, LOREM4096_SIZE,
				  &signature, &signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_calculate_signature(YACA_DIGEST_SHA512, NULL, lorem4096, LOREM4096_SIZE,
				  &signature, &signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_calculate_signature(YACA_DIGEST_SHA512, prv, NULL, LOREM4096_SIZE,
				  &signature, &signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_calculate_signature(YACA_DIGEST_SHA512, prv, lorem4096, 0,
				  &signature, &signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_calculate_signature(YACA_DIGEST_SHA512, prv, lorem4096, LOREM4096_SIZE,
				  NULL, &signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_calculate_signature(YACA_DIGEST_SHA512, prv, lorem4096, LOREM4096_SIZE,
				  &signature, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_free(signature);
	yaca_key_destroy(prv);

	return 0;
}

/**
 * @testcase        utc_yaca_simple_verify_signature_p
 * @since_tizen     3.0
 * @description     Verifies a signature using asymmetric public key.
 * @scenario        Verifies a signature using asymmetric public key with valid parameters.
 */
int utc_yaca_simple_verify_signature_p(void)
{
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	char *signature = NULL;
	size_t signature_len;

	yaca_key_h prv = YACA_KEY_NULL;
	yaca_key_h pub = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(prv, &pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_simple_calculate_signature(YACA_DIGEST_SHA512, prv, lorem4096, LOREM4096_SIZE,
				  &signature, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_simple_verify_signature(YACA_DIGEST_SHA512, pub, lorem4096, LOREM4096_SIZE,
					signature, signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_free(signature);
	yaca_key_destroy(prv);
	yaca_key_destroy(pub);

	return 0;
}

/**
 * @testcase        utc_yaca_simple_verify_signature_n
 * @since_tizen     3.0
 * @description     Verifies a signature using asymmetric public key.
 * @scenario        Verifies a signature using asymmetric public key with invalid parameters.
 */
int utc_yaca_simple_verify_signature_n(void)
{
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	char *signature = NULL;
	size_t signature_len;

	yaca_key_h prv = YACA_KEY_NULL;
	yaca_key_h pub = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(prv, &pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_simple_calculate_signature(YACA_DIGEST_SHA512, prv, lorem4096, LOREM4096_SIZE,
				  &signature, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_simple_verify_signature((yaca_digest_algorithm_e)-1, pub, lorem4096, LOREM4096_SIZE,
					signature, signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_verify_signature(YACA_DIGEST_SHA512, NULL, lorem4096, LOREM4096_SIZE,
					signature, signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_verify_signature(YACA_DIGEST_SHA512, pub, NULL, LOREM4096_SIZE,
					signature, signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_verify_signature(YACA_DIGEST_SHA512, pub, lorem4096, 0,
					signature, signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_verify_signature(YACA_DIGEST_SHA512, pub, lorem4096, LOREM4096_SIZE,
					NULL, signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_verify_signature(YACA_DIGEST_SHA512, pub, lorem4096, LOREM4096_SIZE,
					signature, 0);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_free(signature);
	yaca_key_destroy(prv);
	yaca_key_destroy(pub);

	return 0;
}

/**
 * @testcase        utc_yaca_simple_calculate_hmac_p
 * @since_tizen     3.0
 * @description     Calculates a HMAC of given message using symmetric key.
 * @scenario        Calculates a HMAC of given message using symmetric key with valid parameters.
 */
int utc_yaca_simple_calculate_hmac_p(void)
{
	char *signature = NULL;
	size_t signature_len;

	yaca_key_h key = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_SYMMETRIC, YACA_KEY_LENGTH_256BIT, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_simple_calculate_hmac(YACA_DIGEST_SHA512, key, lorem4096, LOREM4096_SIZE,
				  &signature, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_free(signature);
	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_simple_calculate_hmac_n
 * @since_tizen     3.0
 * @description     Calculates a HMAC of given message using symmetric key.
 * @scenario        Calculates a HMAC of given message using symmetric key with invalid parameters.
 */
int utc_yaca_simple_calculate_hmac_n(void)
{
		char *signature = NULL;
	size_t signature_len;

	yaca_key_h key = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_SYMMETRIC, YACA_KEY_LENGTH_256BIT, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_simple_calculate_hmac((yaca_digest_algorithm_e)-1, key, lorem4096, LOREM4096_SIZE,
				  &signature, &signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_calculate_hmac(YACA_DIGEST_SHA512, NULL, lorem4096, LOREM4096_SIZE,
				  &signature, &signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_calculate_hmac(YACA_DIGEST_SHA512, key, NULL, LOREM4096_SIZE,
				  &signature, &signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_calculate_hmac(YACA_DIGEST_SHA512, key, lorem4096, 0,
				  &signature, &signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_calculate_hmac(YACA_DIGEST_SHA512, key, lorem4096, LOREM4096_SIZE,
				  NULL, &signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_calculate_hmac(YACA_DIGEST_SHA512, key, lorem4096, LOREM4096_SIZE,
				  &signature, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_free(signature);
	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_simple_calculate_cmac_p
 * @since_tizen     3.0
 * @description     Calculates a CMAC of given message using symmetric key.
 * @scenario        Calculates a CMAC of given message using symmetric key with valid parameters.
 */
int utc_yaca_simple_calculate_cmac_p(void)
{
	char *signature = NULL;
	size_t signature_len;

	yaca_key_h key = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_SYMMETRIC, YACA_KEY_LENGTH_256BIT, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_simple_calculate_cmac(YACA_ENCRYPT_AES, key, lorem4096, LOREM4096_SIZE,
				  &signature, &signature_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_free(signature);
	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_simple_calculate_cmac_n
 * @since_tizen     3.0
 * @description     Calculates a CMAC of given message using symmetric key.
 * @scenario        Calculates a CMAC of given message using symmetric key with invalid parameters.
 */
int utc_yaca_simple_calculate_cmac_n(void)
{
	char *signature = NULL;
	size_t signature_len;

	yaca_key_h key = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_SYMMETRIC, YACA_KEY_LENGTH_256BIT, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_simple_calculate_cmac((yaca_encrypt_algorithm_e)-1, key, lorem4096, LOREM4096_SIZE,
				  &signature, &signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_calculate_cmac(YACA_ENCRYPT_AES, NULL, lorem4096, LOREM4096_SIZE,
				  &signature, &signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_calculate_cmac(YACA_ENCRYPT_AES, key, NULL, LOREM4096_SIZE,
				  &signature, &signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_calculate_cmac(YACA_ENCRYPT_AES, key, lorem4096, 0,
				  &signature, &signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_calculate_cmac(YACA_ENCRYPT_AES, key, lorem4096, LOREM4096_SIZE,
				  NULL, &signature_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_simple_calculate_cmac(YACA_ENCRYPT_AES, key, lorem4096, LOREM4096_SIZE,
				  &signature, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_free(signature);
	yaca_key_destroy(key);

	return 0;
}


