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
#include <yaca_digest.h>
#include <yaca_crypto.h>

#include "lorem.h"

//& set: Yaca

/**
 * @function        utc_yaca_digest_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_yaca_digest_startup(void)
{
	yaca_initialize();
}

/**
 * @function        utc_yaca_digest_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_yaca_digest_cleanup(void)
{
	yaca_cleanup();
}

/**
 * @testcase        utc_yaca_digest_initialize_p
 * @since_tizen     3.0
 * @description     Initializes the digest context.
 * @scenario        Initializes the digest context.
 */
int utc_yaca_digest_initialize_p(void)
{
	yaca_context_h ctx;

	int ret = yaca_digest_initialize(&ctx, YACA_DIGEST_SHA256);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	return 0;
}

/**
 * @testcase        utc_yaca_digest_initialize_n
 * @since_tizen     3.0
 * @description     Initializes the digest context.
 * @scenario        Initializes the digest context with invalid parameters.
 */
int utc_yaca_digest_initialize_n(void)
{
	yaca_context_h ctx;

	int ret = yaca_digest_initialize(NULL, YACA_DIGEST_SHA256);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_digest_initialize(&ctx, (yaca_digest_algorithm_e) -1);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_yaca_digest_update_p
 * @since_tizen     3.0
 * @description     Feeds the data into the message digest algorithm.
 * @scenario        Feeds the data into the message digest algorithm with valid parameters.
 */
int utc_yaca_digest_update_p(void)
{
	yaca_context_h ctx;

	int ret = yaca_digest_initialize(&ctx, YACA_DIGEST_SHA256);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_digest_update(ctx, lorem1024, 1024);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	return 0;
}

/**
 * @testcase        utc_yaca_digest_update_n
 * @since_tizen     3.0
 * @description     Feeds the data into the message digest algorithm.
 * @scenario        Feeds the data into the message digest algorithm with invalid parameters.
 */
int utc_yaca_digest_update_n(void)
{
	yaca_context_h ctx;

	int ret = yaca_digest_initialize(&ctx, YACA_DIGEST_SHA256);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_digest_update(NULL, lorem1024, 1024);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_digest_update(ctx, NULL, 1024);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_digest_update(ctx, lorem1024, 0);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_context_destroy(ctx);
	return 0;
}

/**
 * @testcase        utc_yaca_digest_finalize_p
 * @since_tizen     3.0
 * @description     Calculates the final digest.
 * @scenario        Calculates the final digest with SHA256.
 */
int utc_yaca_digest_finalize_p(void)
{
	yaca_context_h ctx;
	size_t digest_len;
	char *digest = NULL;

	int ret = yaca_digest_initialize(&ctx, YACA_DIGEST_SHA256);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_digest_update(ctx, lorem1024, 1024);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &digest_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_malloc(digest_len, (void**) &digest);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_digest_finalize(ctx, digest, &digest_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	return 0;
}

/**
 * @testcase        utc_yaca_digest_finalize_p2
 * @since_tizen     3.0
 * @description     Calculates the final digest.
 * @scenario        Calculates the final digest with MD5.
 */
int utc_yaca_digest_finalize_p2(void)
{
	yaca_context_h ctx;
	size_t digest_len;
	char *digest = NULL;

	int ret = yaca_digest_initialize(&ctx, YACA_DIGEST_MD5);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_digest_update(ctx, lorem1024, 1024);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &digest_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_malloc(digest_len, (void**) &digest);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_digest_finalize(ctx, digest, &digest_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	return 0;
}

/**
 * @testcase        utc_yaca_digest_finalize_p3
 * @since_tizen     3.0
 * @description     Calculates the final digest.
 * @scenario        Calculates the final digest with SHA1.
 */
int utc_yaca_digest_finalize_p3(void)
{
	yaca_context_h ctx;
	size_t digest_len;
	char *digest = NULL;

	int ret = yaca_digest_initialize(&ctx, YACA_DIGEST_SHA1);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_digest_update(ctx, lorem1024, 1024);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &digest_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_malloc(digest_len, (void**) &digest);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_digest_finalize(ctx, digest, &digest_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	return 0;
}

/**
 * @testcase        utc_yaca_digest_finalize_p4
 * @since_tizen     3.0
 * @description     Calculates the final digest.
 * @scenario        Calculates the final digest with SHA224.
 */
int utc_yaca_digest_finalize_p4(void)
{
	yaca_context_h ctx;
	size_t digest_len;
	char *digest = NULL;

	int ret = yaca_digest_initialize(&ctx, YACA_DIGEST_SHA224);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_digest_update(ctx, lorem1024, 1024);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &digest_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_malloc(digest_len, (void**) &digest);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_digest_finalize(ctx, digest, &digest_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	return 0;
}

/**
 * @testcase        utc_yaca_digest_finalize_p5
 * @since_tizen     3.0
 * @description     Calculates the final digest.
 * @scenario        Calculates the final digest with SHA384.
 */
int utc_yaca_digest_finalize_p5(void)
{
	yaca_context_h ctx;
	size_t digest_len;
	char *digest = NULL;

	int ret = yaca_digest_initialize(&ctx, YACA_DIGEST_SHA384);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_digest_update(ctx, lorem1024, 1024);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &digest_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_malloc(digest_len, (void**) &digest);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_digest_finalize(ctx, digest, &digest_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	return 0;
}

/**
 * @testcase        utc_yaca_digest_finalize_p6
 * @since_tizen     3.0
 * @description     Calculates the final digest.
 * @scenario        Calculates the final digest with SHA512.
 */
int utc_yaca_digest_finalize_p6(void)
{
	yaca_context_h ctx;
	size_t digest_len;
	char *digest = NULL;

	int ret = yaca_digest_initialize(&ctx, YACA_DIGEST_SHA512);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_digest_update(ctx, lorem1024, 1024);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &digest_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_malloc(digest_len, (void**) &digest);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_digest_finalize(ctx, digest, &digest_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_context_destroy(ctx);
	return 0;
}






/**
 * @testcase        utc_yaca_digest_finalize_n
 * @since_tizen     3.0
 * @description     Calculates the final digest.
 * @scenario        Calculates the final digest with invalid parameters.
 */
int utc_yaca_digest_finalize_n(void)
{
	yaca_context_h ctx;
	size_t digest_len;
	char *digest = NULL;

	int ret = yaca_digest_initialize(&ctx, YACA_DIGEST_SHA256);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_digest_update(ctx, lorem1024, 1024);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_context_get_output_length(ctx, 0, &digest_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_malloc(digest_len, (void**) &digest);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_digest_finalize(NULL, digest, &digest_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_digest_finalize(ctx, NULL, &digest_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_digest_finalize(ctx, digest, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_context_destroy(ctx);
	return 0;
}

