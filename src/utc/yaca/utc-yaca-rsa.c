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
#include <yaca_rsa.h>
#include <yaca_crypto.h>
#include <yaca_key.h>

#include "lorem.h"

#include <dlog.h>

//& set: Yaca

/**
 * @function        utc_yaca_rsa_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_yaca_rsa_startup(void)
{
	yaca_initialize();
}

/**
 * @function        utc_yaca_rsa_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_yaca_rsa_cleanup(void)
{
	yaca_cleanup();
}

/**
 * @testcase        utc_yaca_rsa_public_encrypt_p
 * @since_tizen     3.0
 * @description     Encrypts data using a RSA public key.
 * @scenario        Encrypts data using a RSA public key with valid parameters.
 */
int utc_yaca_rsa_public_encrypt_p(void)
{
	yaca_key_h prv_key = YACA_KEY_NULL;
	yaca_key_h pub_key = YACA_KEY_NULL;
	char *ciphertext = NULL;
	size_t ciphertext_len;
	const size_t key_bit_len = YACA_KEY_LENGTH_1024BIT;
	const size_t input_len = key_bit_len / 8 - 12;
	int ret;

	/* Key generation */
	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, key_bit_len, &prv_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(prv_key, &pub_key);
	assert_eq(ret, YACA_ERROR_NONE);

	/* encrypt with PKCS1 padding */
	ret = yaca_rsa_public_encrypt(YACA_PADDING_PKCS1, pub_key,
								  lorem1024, input_len,
								  &ciphertext, &ciphertext_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_free(ciphertext);
	yaca_key_destroy(prv_key);
	yaca_key_destroy(pub_key);

	return 0;
}

/**
 * @testcase        utc_yaca_rsa_public_encrypt_n
 * @since_tizen     3.0
 * @description     Encrypts data using a RSA public key.
 * @scenario        Encrypts data using a RSA public key with invalid parameters.
 */
int utc_yaca_rsa_public_encrypt_n(void)
{
	yaca_key_h prv_key = YACA_KEY_NULL;
	yaca_key_h pub_key = YACA_KEY_NULL;
	char *ciphertext = NULL;
	size_t ciphertext_len;
	const size_t key_bit_len = YACA_KEY_LENGTH_1024BIT;
	const size_t input_len = key_bit_len / 8 - 12;
	int ret;

	/* Key generation */
	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, key_bit_len, &prv_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(prv_key, &pub_key);
	assert_eq(ret, YACA_ERROR_NONE);

	/* encrypt with PKCS1 padding */
	ret = yaca_rsa_public_encrypt((yaca_padding_e) -1, pub_key, lorem1024, input_len,
								  &ciphertext, &ciphertext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_public_encrypt(YACA_PADDING_PKCS1, NULL, lorem1024, input_len,
								  &ciphertext, &ciphertext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_public_encrypt(YACA_PADDING_PKCS1, pub_key, NULL, input_len,
								  &ciphertext, &ciphertext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_public_encrypt(YACA_PADDING_PKCS1, pub_key, lorem1024, 0,
								  &ciphertext, &ciphertext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_public_encrypt(YACA_PADDING_PKCS1, pub_key, lorem1024, input_len,
								  NULL, &ciphertext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_public_encrypt(YACA_PADDING_PKCS1, pub_key, lorem1024, input_len,
								  &ciphertext, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_free(ciphertext);
	yaca_key_destroy(prv_key);
	yaca_key_destroy(pub_key);

	return 0;
}

/**
 * @testcase        utc_yaca_rsa_private_decrypt_p
 * @since_tizen     3.0
 * @description     Decrypts data using a RSA private key.
 * @scenario        Decrypts data using a RSA private key with valid parameters.
 */
int utc_yaca_rsa_private_decrypt_p(void)
{
	yaca_key_h prv_key = YACA_KEY_NULL;
	yaca_key_h pub_key = YACA_KEY_NULL;
	char *ciphertext = NULL;
	size_t ciphertext_len;
	char *plaintext = NULL;
	size_t plaintext_len;
	const size_t key_bit_len = YACA_KEY_LENGTH_1024BIT;
	const size_t input_len = key_bit_len / 8 - 12;
	int ret;

	/* Key generation */
	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, key_bit_len, &prv_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(prv_key, &pub_key);
	assert_eq(ret, YACA_ERROR_NONE);

	/* encrypt with PKCS1 padding */
	ret = yaca_rsa_public_encrypt(YACA_PADDING_PKCS1, pub_key,
								  lorem1024, input_len,
								  &ciphertext, &ciphertext_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_rsa_private_decrypt(YACA_PADDING_PKCS1, prv_key,
								   ciphertext, ciphertext_len,
								   &plaintext, &plaintext_len);
	assert_eq(ret, YACA_ERROR_NONE);

	// compare
	assert_eq(input_len, plaintext_len);
	int idx;
	for (idx = 0; idx < input_len; idx++) {
		assert_eq(lorem1024[idx], plaintext[idx]);
	}

	yaca_free(ciphertext);
	yaca_free(plaintext);
	yaca_key_destroy(prv_key);
	yaca_key_destroy(pub_key);

	return 0;
}

/**
 * @testcase        utc_yaca_rsa_private_decrypt_n
 * @since_tizen     3.0
 * @description     Decrypts data using a RSA private key.
 * @scenario        Decrypts data using a RSA private key with invalid parameters.
 */
int utc_yaca_rsa_private_decrypt_n(void)
{
	yaca_key_h prv_key = YACA_KEY_NULL;
	yaca_key_h pub_key = YACA_KEY_NULL;
	char *ciphertext = NULL;
	size_t ciphertext_len;
	char *plaintext = NULL;
	size_t plaintext_len;
	const size_t key_bit_len = YACA_KEY_LENGTH_1024BIT;
	const size_t input_len = key_bit_len / 8 - 12;
	int ret;

	/* Key generation */
	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, key_bit_len, &prv_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(prv_key, &pub_key);
	assert_eq(ret, YACA_ERROR_NONE);

	/* encrypt with PKCS1 padding */
	ret = yaca_rsa_public_encrypt(YACA_PADDING_PKCS1, pub_key,
								  lorem1024, input_len,
								  &ciphertext, &ciphertext_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_rsa_private_decrypt((yaca_padding_e) -1, prv_key, ciphertext, ciphertext_len,
								   &plaintext, &plaintext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_private_decrypt(YACA_PADDING_PKCS1, NULL, ciphertext, ciphertext_len,
								   &plaintext, &plaintext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_private_decrypt(YACA_PADDING_PKCS1, prv_key, NULL, ciphertext_len,
								   &plaintext, &plaintext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_private_decrypt(YACA_PADDING_PKCS1, prv_key, ciphertext, 0,
								   &plaintext, &plaintext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_private_decrypt(YACA_PADDING_PKCS1, prv_key, ciphertext, ciphertext_len,
								   NULL, &plaintext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_private_decrypt(YACA_PADDING_PKCS1, prv_key, ciphertext, ciphertext_len,
								   &plaintext, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_free(ciphertext);
	yaca_free(plaintext);
	yaca_key_destroy(prv_key);
	yaca_key_destroy(pub_key);

	return 0;
}

/**
 * @testcase        utc_yaca_rsa_private_encrypt_p
 * @since_tizen     3.0
 * @description     Encrypts data using a RSA private key.
 * @scenario        Encrypts data using a RSA private key with valid parameters.
 */
int utc_yaca_rsa_private_encrypt_p(void)
{
	yaca_key_h prv_key = YACA_KEY_NULL;
	char *ciphertext = NULL;
	size_t ciphertext_len;
	const size_t key_bit_len = YACA_KEY_LENGTH_1024BIT;
	const size_t input_len = key_bit_len / 8 - 12;
	int ret;

	/* Key generation */
	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, key_bit_len, &prv_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_rsa_private_encrypt(YACA_PADDING_PKCS1, prv_key,
								   lorem1024, input_len,
								   &ciphertext, &ciphertext_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_free(ciphertext);
	yaca_key_destroy(prv_key);

	return 0;
}

/**
 * @testcase        utc_yaca_rsa_private_encrypt_n
 * @since_tizen     3.0
 * @description     Encrypts data using a RSA private key.
 * @scenario        Encrypts data using a RSA private key with invalid parameters.
 */
int utc_yaca_rsa_private_encrypt_n(void)
{
	yaca_key_h prv_key = YACA_KEY_NULL;
	char *ciphertext = NULL;
	size_t ciphertext_len;
	const size_t key_bit_len = YACA_KEY_LENGTH_1024BIT;
	const size_t input_len = key_bit_len / 8 - 12;
	int ret;

	/* Key generation */
	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, key_bit_len, &prv_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_rsa_private_encrypt((yaca_padding_e) -1, prv_key, lorem1024, input_len,
								   &ciphertext, &ciphertext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_private_encrypt(YACA_PADDING_PKCS1, NULL, lorem1024, input_len,
								   &ciphertext, &ciphertext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_private_encrypt(YACA_PADDING_PKCS1, prv_key, NULL, input_len,
								   &ciphertext, &ciphertext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_private_encrypt(YACA_PADDING_PKCS1, prv_key, lorem1024, 0,
								   &ciphertext, &ciphertext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_private_encrypt(YACA_PADDING_PKCS1, prv_key, lorem1024, input_len,
								   NULL, &ciphertext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_private_encrypt(YACA_PADDING_PKCS1, prv_key, lorem1024, input_len,
								   &ciphertext, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_free(ciphertext);
	yaca_key_destroy(prv_key);

	return 0;
}

/**
 * @testcase        utc_yaca_rsa_public_decrypt_p
 * @since_tizen     3.0
 * @description     Encrypts data using a RSA public key.
 * @scenario        Encrypts data using a RSA public key with valid parameters.
 */
int utc_yaca_rsa_public_decrypt_p(void)
{
	yaca_key_h prv_key = YACA_KEY_NULL;
	yaca_key_h pub_key = YACA_KEY_NULL;
	char *ciphertext = NULL;
	size_t ciphertext_len;
	char *plaintext = NULL;
	size_t plaintext_len;
	const size_t key_bit_len = YACA_KEY_LENGTH_1024BIT;
	const size_t input_len = key_bit_len / 8 - 12;
	int ret;

	/* Key generation */
	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, key_bit_len, &prv_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(prv_key, &pub_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_rsa_private_encrypt(YACA_PADDING_PKCS1, prv_key,
								   lorem1024, input_len,
								   &ciphertext, &ciphertext_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_rsa_public_decrypt(YACA_PADDING_PKCS1, pub_key,
								  ciphertext, ciphertext_len,
								  &plaintext, &plaintext_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_free(ciphertext);
	yaca_free(plaintext);
	yaca_key_destroy(prv_key);
	yaca_key_destroy(pub_key);

	return 0;
}

/**
 * @testcase        utc_yaca_rsa_public_decrypt_n
 * @since_tizen     3.0
 * @description     Encrypts data using a RSA public key.
 * @scenario        Encrypts data using a RSA public key with invalid parameters.
 */
int utc_yaca_rsa_public_decrypt_n(void)
{
	yaca_key_h prv_key = YACA_KEY_NULL;
	yaca_key_h pub_key = YACA_KEY_NULL;
	char *ciphertext = NULL;
	size_t ciphertext_len;
	char *plaintext = NULL;
	size_t plaintext_len;
	const size_t key_bit_len = YACA_KEY_LENGTH_1024BIT;
	const size_t input_len = key_bit_len / 8 - 12;
	int ret;

	/* Key generation */
	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, key_bit_len, &prv_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(prv_key, &pub_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_rsa_private_encrypt(YACA_PADDING_PKCS1, prv_key,
								   lorem1024, input_len,
								   &ciphertext, &ciphertext_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_rsa_public_decrypt((yaca_padding_e) -1, pub_key, ciphertext, ciphertext_len,
								  &plaintext, &plaintext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_public_decrypt(YACA_PADDING_PKCS1, NULL, ciphertext, ciphertext_len,
								  &plaintext, &plaintext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_public_decrypt(YACA_PADDING_PKCS1, pub_key, NULL, ciphertext_len,
								  &plaintext, &plaintext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_public_decrypt(YACA_PADDING_PKCS1, pub_key, ciphertext, 0,
								  &plaintext, &plaintext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_public_decrypt(YACA_PADDING_PKCS1, pub_key, ciphertext, ciphertext_len,
								  NULL, &plaintext_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_rsa_public_decrypt(YACA_PADDING_PKCS1, pub_key, ciphertext, ciphertext_len,
								  &plaintext, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_free(ciphertext);
	yaca_free(plaintext);
	yaca_key_destroy(prv_key);
	yaca_key_destroy(pub_key);

	return 0;
}


