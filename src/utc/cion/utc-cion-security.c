//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
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
#include "assert_common.h"

#include <cion.h>
#include <dlog.h>
#include <glib.h>

#define LOG_TAG "NativeTCT"

//& set: Cion

void utc_cion_security_startup(void)
{
}

void utc_cion_security_cleanup(void)
{
}

/**
 * @testcase		utc_cion_security_create_p
 * @since_tizen		6.5
 * @description		Creates a cion security.
 */
int utc_cion_security_create_p(void)
{
	int ret;
	cion_security_h security;

	ret = cion_security_create(&security);
	assert_eq(ret, CION_ERROR_NONE);

	cion_security_destroy(security);

	return 0;
}

/**
 * @testcase		utc_cion_security_create_n
 * @since_tizen		6.5
 * @description		Creates a cion security for negative case.
 */
int utc_cion_security_create_n(void)
{
	int ret;

	ret = cion_security_create(NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_security_destory_p
 * @since_tizen		6.5
 * @description		Destroys a cion security.
 */
int utc_cion_security_destory_p(void)
{
	int ret;
	cion_security_h security;

	ret = cion_security_create(&security);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_security_destroy(security);
	assert_eq(ret, CION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_cion_security_destory_n
 * @since_tizen		6.5
 * @description		Destroys a cion security for negative case.
 */
int utc_cion_security_destory_n(void)
{
	int ret;

	ret = cion_security_destroy(NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_security_set_ca_path_p
 * @since_tizen		6.5
 * @description		Sets CA path.
 */
int utc_cion_security_set_ca_path_p(void)
{
	int ret;
	cion_security_h security;

	ret = cion_security_create(&security);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_security_set_ca_path(security, "path");
	assert_eq(ret, CION_ERROR_NONE);

	cion_security_destroy(security);

	return 0;
}

/**
 * @testcase		utc_cion_security_set_ca_path_n
 * @since_tizen		6.5
 * @description		Sets CA path for negative case.
 */
int utc_cion_security_set_ca_path_n(void)
{
	int ret;
	cion_security_h security = (cion_security_h)1;

	ret = cion_security_set_ca_path(NULL, "path");
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_security_set_ca_path(security, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_security_set_cert_path_p
 * @since_tizen		6.5
 * @description		Sets certificate path.
 */
int utc_cion_security_set_cert_path_p(void)
{
	int ret;
	cion_security_h security;

	ret = cion_security_create(&security);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_security_set_cert_path(security, "path");
	assert_eq(ret, CION_ERROR_NONE);

	cion_security_destroy(security);

	return 0;
}

/**
 * @testcase		utc_cion_security_set_cert_path_n
 * @since_tizen		6.5
 * @description		Sets certificate path for negative case.
 */
int utc_cion_security_set_cert_path_n(void)
{
	int ret;
	cion_security_h security = (cion_security_h)1;

	ret = cion_security_set_cert_path(NULL, "path");
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_security_set_cert_path(security, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_security_set_private_key_path_p
 * @since_tizen		6.5
 * @description		Sets private key path.
 */
int utc_cion_security_set_private_key_path_p(void)
{
	int ret;
	cion_security_h security;

	ret = cion_security_create(&security);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_security_set_private_key_path(security, "path");
	assert_eq(ret, CION_ERROR_NONE);

	cion_security_destroy(security);

	return 0;
}

/**
 * @testcase		utc_cion_security_set_private_key_path_n
 * @since_tizen		6.5
 * @description		Sets private key path for negative case.
 */
int utc_cion_security_set_private_key_path_n(void)
{
	int ret;
	cion_security_h security = (cion_security_h)1;

	ret = cion_security_set_private_key_path(NULL, "path");
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_security_set_private_key_path(security, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_security_get_ca_path_p
 * @since_tizen		6.5
 * @description		Gets CA path.
 */
int utc_cion_security_get_ca_path_p(void)
{
	int ret;
	cion_security_h security;
	char *path;

	ret = cion_security_create(&security);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_security_set_ca_path(security, "path");
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_security_get_ca_path(security, &path);
	assert_eq(ret, CION_ERROR_NONE);

	free(path);
	cion_security_destroy(security);

	return 0;
}

/**
 * @testcase		utc_cion_security_get_ca_path_n
 * @since_tizen		6.5
 * @description		Gets CA path for negative case.
 */
int utc_cion_security_get_ca_path_n(void)
{
	int ret;
	cion_security_h security = (cion_security_h)1;
	char *path;

	ret = cion_security_get_ca_path(NULL, &path);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_security_get_ca_path(security, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_security_get_cert_path_p
 * @since_tizen		6.5
 * @description		Gets certificate path.
 */
int utc_cion_security_get_cert_path_p(void)
{
	int ret;
	cion_security_h security;
	char *path;

	ret = cion_security_create(&security);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_security_set_cert_path(security, "path");
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_security_get_cert_path(security, &path);
	assert_eq(ret, CION_ERROR_NONE);

	free(path);
	cion_security_destroy(security);

	return 0;
}

/**
 * @testcase		utc_cion_security_get_cert_path_n
 * @since_tizen		6.5
 * @description		Gets certificate path for negative case.
 */
int utc_cion_security_get_cert_path_n(void)
{
	int ret;
	cion_security_h security = (cion_security_h)1;
	char *path;

	ret = cion_security_get_cert_path(NULL, &path);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_security_get_cert_path(security, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_security_get_private_key_path_p
 * @since_tizen		6.5
 * @description		Gets private key path.
 */
int utc_cion_security_get_private_key_path_p(void)
{
	int ret;
	cion_security_h security;
	char *path;

	ret = cion_security_create(&security);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_security_set_private_key_path(security, "path");
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_security_get_private_key_path(security, &path);
	assert_eq(ret, CION_ERROR_NONE);

	free(path);
	cion_security_destroy(security);

	return 0;
}

/**
 * @testcase		utc_cion_security_get_private_key_path_n
 * @since_tizen		6.5
 * @description		Gets private key path for negative case.
 */
int utc_cion_security_get_private_key_path_n(void)
{
	int ret;
	cion_security_h security = (cion_security_h)1;
	char *path;

	ret = cion_security_get_private_key_path(NULL, &path);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_security_get_private_key_path(security, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}
