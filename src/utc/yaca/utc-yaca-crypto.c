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

#include <yaca_crypto.h>
#include <yaca_error.h>
#include <yaca_key.h>
#include <yaca_sign.h>
#include <yaca_encrypt.h>
#include "lorem.h"

//& set: Yaca

#define TEST_MEM_SIZE 512

/**
 * @function        utc_yaca_crypto_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_yaca_crypto_startup(void)
{
	yaca_initialize();
}

/**
 * @function        utc_yaca_crypto_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_yaca_crypto_cleanup(void)
{
	yaca_cleanup();
}

/**
 * @testcase        utc_yaca_initialize_p
 * @since_tizen     3.0
 * @description     Initializes the library.
 * @scenario        Initializes the library.
 */
int utc_yaca_initialize_p(void)
{
	yaca_cleanup();

	int ret = yaca_initialize();
	assert_eq(ret, YACA_ERROR_NONE);
	return 0;
}

/**
 * @testcase        utc_yaca_cleanup_p
 * @since_tizen     3.0
 * @description     Cleans up the library.
 * @scenario        Cleans up the library.
 */
int utc_yaca_cleanup_p(void)
{
	yaca_cleanup();
	return 0;
}

/**
 * @testcase        utc_yaca_malloc_p
 * @since_tizen     3.0
 * @description     Allocates the memory.
 * @scenario        Allocates the memory with valid paramters.
 */
int utc_yaca_malloc_p(void)
{
	void *memory;
	size_t size = 1024;

	int ret = yaca_malloc(size, &memory);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_free(memory);
	return 0;
}

/**
 * @testcase        utc_yaca_malloc_n
 * @since_tizen     3.0
 * @description     Allocates the memory.
 * @scenario        Allocates the memory with invalid paramters.
 */
int utc_yaca_malloc_n(void)
{
	void *memory;
	size_t size = 1024;

	int ret = yaca_malloc(0, &memory);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_malloc(size, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_yaca_zalloc_p
 * @since_tizen     3.0
 * @description     Allocates the zeroed memory.
 * @scenario        Allocates the zeroed memory with valid paramters.
 */
int utc_yaca_zalloc_p(void)
{
	void *memory = NULL;
	size_t size = 1024;

	int ret = yaca_zalloc(size, &memory);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_free(memory);
	return 0;
}

/**
 * @testcase        utc_yaca_zalloc_n
 * @since_tizen     3.0
 * @description     Allocates the zeroed memory.
 * @scenario        Allocates the zeroed memory with invalid paramters.
 */
int utc_yaca_zalloc_n(void)
{
	void *memory;
	size_t size = 1024;

	int ret = yaca_zalloc(0, &memory);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_zalloc(size, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_yaca_realloc_p
 * @since_tizen     3.0
 * @description     Re-allocates the memory.
 * @scenario        Re-allocates the memory with valid paramters.
 */
int utc_yaca_realloc_p(void)
{
	void *memory;
	size_t size = 1024;

	int ret = yaca_malloc(size, &memory);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_realloc(size*2, &memory);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_free(memory);
	return 0;
}

/**
 * @testcase        utc_yaca_realloc_n
 * @since_tizen     3.0
 * @description     Re-allocates the memory.
 * @scenario        Re-allocates the memory with invalid paramters.
 */
int utc_yaca_realloc_n(void)
{
	void *memory;
	size_t size = 1024;

	int ret = yaca_realloc(0, &memory);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_realloc(size, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_yaca_free_p
 * @since_tizen     3.0
 * @description     Frees the memory.
 * @scenario        Frees the memory.
 */
int utc_yaca_free_p(void)
{
	void *memory;
	size_t size = 1024;

	int ret = yaca_malloc(size, &memory);
	assert_eq(ret, YACA_ERROR_NONE);
	yaca_free(memory);

	yaca_free(NULL);

	return 0;
}

/**
 * @testcase        utc_yaca_memcmp_p
 * @since_tizen     3.0
 * @description     Safely compares two buffers.
 * @scenario        Safely compares two buffers with valid parameters.
 */
int utc_yaca_memcmp_p(void)
{
	unsigned char first[TEST_MEM_SIZE] = {1, };
	unsigned char second[TEST_MEM_SIZE] = {1, };

	int ret = yaca_memcmp(first, second, TEST_MEM_SIZE);
	assert_eq(ret, YACA_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_yaca_memcmp_n
 * @since_tizen     3.0
 * @description     Safely compares two buffers.
 * @scenario        Safely compares two buffers with different values.
 */
int utc_yaca_memcmp_n(void)
{
	unsigned char first[TEST_MEM_SIZE] = {1, };
	unsigned char second[TEST_MEM_SIZE] = {2, };

	int ret = yaca_memcmp(first, second, TEST_MEM_SIZE);
	assert_eq(ret, YACA_ERROR_DATA_MISMATCH);

	return 0;
}

/**
 * @testcase        utc_yaca_randomize_bytes_p
 * @since_tizen     3.0
 * @description     Generates random data.
 * @scenario        Generates random data with valid parameters.
 */
int utc_yaca_randomize_bytes_p(void)
{
	char data[32] = {0, };

	int ret = yaca_randomize_bytes(data, 32);
	assert_eq(ret, YACA_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_yaca_randomize_bytes_n
 * @since_tizen     3.0
 * @description     Generates random data.
 * @scenario        Generates random data with invalid parameters.
 */
int utc_yaca_randomize_bytes_n(void)
{
	char data[32] = {0, };

	int ret = yaca_randomize_bytes(NULL, 32);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_randomize_bytes(data, 0);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_yaca_context_set_property_p
 * @since_tizen     3.0
 * @description     Sets the non-standard context properties.
 * @scenario        Sets the non-standard context properties with valid parameters.
 */
int utc_yaca_context_set_property_p(void)
{
	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h prv = YACA_KEY_NULL;
	yaca_padding_e padding = YACA_PADDING_PKCS1_PSS;
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	int ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize(&ctx, YACA_DIGEST_SHA512, prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_set_property(ctx, YACA_PROPERTY_PADDING, (void*)(&padding), sizeof(padding));
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_key_destroy(prv);
	yaca_context_destroy(ctx);

	return 0;
}

/**
 * @testcase        utc_yaca_context_set_property_n
 * @since_tizen     3.0
 * @description     Sets the non-standard context properties.
 * @scenario        Sets the non-standard context properties with invalid parameters.
 */
int utc_yaca_context_set_property_n(void)
{
	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h prv = YACA_KEY_NULL;
	yaca_padding_e padding = YACA_PADDING_PKCS1_PSS;
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	int ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize(&ctx, YACA_DIGEST_SHA512, prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_set_property(NULL, YACA_PROPERTY_PADDING, (void*)(&padding), sizeof(padding));
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_context_set_property(ctx, (yaca_property_e) -1, (void*)(&padding), sizeof(padding));
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_context_set_property(ctx, YACA_PROPERTY_PADDING, (void*)NULL, sizeof(padding));
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_context_set_property(ctx, YACA_PROPERTY_PADDING, (void*)(&padding), 0);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_key_destroy(prv);
	yaca_context_destroy(ctx);

	return 0;
}


/**
 * @testcase        utc_yaca_context_get_property_p
 * @since_tizen     3.0
 * @description     Gets the non-standard context properties.
 * @scenario        Gets the non-standard context properties with valid parameters.
 */
int utc_yaca_context_get_property_p(void)
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
	size_t enc_len;

	char *aad = NULL;
	char *tag = NULL;
	size_t aad_len = 16;
	size_t tag_len = 16;

	size_t block_len;
	size_t output_len;
	size_t written_len;

	/* Key generation */
	assert_eq(yaca_key_generate(key_type, key_bit_len, &key), YACA_ERROR_NONE);

	/* IV generation */
	assert_eq(yaca_key_generate(YACA_KEY_TYPE_IV, iv_bit_len, &iv), YACA_ERROR_NONE);

	assert_eq(yaca_zalloc(aad_len, (void**)&aad), YACA_ERROR_NONE);

	assert_eq(yaca_randomize_bytes(aad, aad_len), YACA_ERROR_NONE);

	/* Encryption */
	{
		assert_eq(yaca_encrypt_initialize(&ctx, algo, bcm, key, iv), YACA_ERROR_NONE);

		/* Provide any AAD data */
		assert_eq(yaca_context_set_property(ctx, YACA_PROPERTY_GCM_AAD, aad, aad_len), YACA_ERROR_NONE);

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

		/* Set the tag length and get the tag after final encryption */
		assert_eq(yaca_context_set_property(ctx, YACA_PROPERTY_GCM_TAG_LEN,
			                          (void*)&tag_len, sizeof(tag_len)), YACA_ERROR_NONE);

		assert_eq(yaca_context_get_property(ctx, YACA_PROPERTY_GCM_TAG, (void**)&tag, &tag_len), YACA_ERROR_NONE);

		yaca_context_destroy(ctx);
		ctx = YACA_CONTEXT_NULL;
	}

	yaca_free(enc);
	yaca_free(tag);
	yaca_free(aad);
	yaca_context_destroy(ctx);
	yaca_key_destroy(iv);
	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_context_get_property_n
 * @since_tizen     3.0
 * @description     Gets the non-standard context properties.
 * @scenario        Gets the non-standard context properties with invalid parameters.
 */
int utc_yaca_context_get_property_n(void)
{
	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h prv = YACA_KEY_NULL;
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	yaca_padding_e *returned_padding = NULL;
	size_t returned_size = 0;

	int ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize(&ctx, YACA_DIGEST_SHA512, prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_property(NULL, YACA_PROPERTY_PADDING, (void**)&returned_padding, &returned_size);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_context_get_property(ctx, (yaca_padding_e) -1, (void**)&returned_padding, &returned_size);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_context_get_property(ctx, YACA_PROPERTY_PADDING, (void**)NULL, &returned_size);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_key_destroy(prv);
	yaca_context_destroy(ctx);

	return 0;
}

/**
 * @testcase        utc_yaca_context_destroy_p
 * @since_tizen     3.0
 * @description     Destroys context.
 * @scenario        Destroys context.
 */
int utc_yaca_context_destroy_p(void)
{
	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h prv = YACA_KEY_NULL;
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	int ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize(&ctx, YACA_DIGEST_SHA512, prv);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);

	yaca_context_destroy((yaca_context_h) NULL);

	yaca_key_destroy(prv);
	return 0;
}

/**
 * @testcase        utc_yaca_context_get_output_length_p
 * @since_tizen     3.0
 * @description     Gets the output length for a given context.
 * @scenario        Gets the output length for a given context.
 */
int utc_yaca_context_get_output_length_p(void)
{
	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h prv = YACA_KEY_NULL;
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	int ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize(&ctx, YACA_DIGEST_SHA512, prv);
	assert_eq(ret, YACA_ERROR_NONE);

	size_t output_len = 0;
	ret = yaca_context_get_output_length(ctx, 0, &output_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	yaca_key_destroy(prv);
	return 0;
}

/**
 * @testcase        utc_yaca_context_get_output_length_n
 * @since_tizen     3.0
 * @description     Gets the output length for a given context.
 * @scenario        Gets the output length for a given context with invalid parameters.
 */
int utc_yaca_context_get_output_length_n(void)
{
	yaca_context_h ctx = YACA_CONTEXT_NULL;
	yaca_key_h prv = YACA_KEY_NULL;
	yaca_key_type_e type = YACA_KEY_TYPE_RSA_PRIV;

	int ret = yaca_key_generate(type, YACA_KEY_LENGTH_1024BIT, &prv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_sign_initialize(&ctx, YACA_DIGEST_SHA512, prv);
	assert_eq(ret, YACA_ERROR_NONE);

	size_t output_len = 0;
	ret = yaca_context_get_output_length(NULL, 512, &output_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_context_get_output_length(ctx, 512, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_context_destroy(ctx);
	yaca_key_destroy(prv);
	return 0;
}


