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
#include <yaca_key.h>
#include <yaca_crypto.h>
#include <yaca_types.h>


//& set: Yaca

/**
 * @function        utc_yaca_key_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_yaca_key_startup(void)
{
	yaca_initialize();
}

/**
 * @function        utc_yaca_key_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_yaca_key_cleanup(void)
{
	yaca_cleanup();
}

/**
 * @testcase        utc_yaca_key_get_type_p
 * @since_tizen     3.0
 * @description     Gets key's type.
 * @scenario        Gets key's type with valid parameters.
 */
int utc_yaca_key_get_type_p(void)
{
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;
	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_key_type_e ret_key_type;
	ret = yaca_key_get_type(key, &ret_key_type);
	assert_eq(ret, YACA_ERROR_NONE);
	assert_eq(key_type, ret_key_type);

	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_key_get_type_n
 * @since_tizen     3.0
 * @description     Gets key's type.
 * @scenario        Gets key's type with invalid parameters.
 */
int utc_yaca_key_get_type_n(void)
{
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;
	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_key_type_e ret_key_type;
	ret = yaca_key_get_type(NULL, &ret_key_type);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_get_type(key, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_key_get_bit_length_p
 * @since_tizen     3.0
 * @description     Gets key's length.
 * @scenario        Gets key's length with valid parameters.
 */
int utc_yaca_key_get_bit_length_p(void)
{
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;
	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	size_t ret_key_bit_len;
	ret = yaca_key_get_bit_length(key, &ret_key_bit_len);
	assert_eq(ret, YACA_ERROR_NONE);
	assert_eq(key_bit_len, ret_key_bit_len);

	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_key_get_bit_length_n
 * @since_tizen     3.0
 * @description     Gets key's length.
 * @scenario        Gets key's length with invalid parameters.
 */
int utc_yaca_key_get_bit_length_n(void)
{
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;
	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	size_t ret_key_bit_len;
	ret = yaca_key_get_bit_length(NULL, &ret_key_bit_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_get_bit_length(key, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_key_import_p
 * @since_tizen     3.0
 * @description     Imports a key.
 * @scenario        Imports a key with symmetric key type.
 */
int utc_yaca_key_import_p(void)
{
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;
	int ret = YACA_ERROR_NONE;

	yaca_key_h b64_imported = YACA_KEY_NULL;
	yaca_key_h raw_imported = YACA_KEY_NULL;

	char *raw = NULL;
	size_t raw_len;
	char *b64 = NULL;
	size_t b64_len;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_export(key, YACA_KEY_FORMAT_DEFAULT, YACA_KEY_FILE_FORMAT_BASE64, NULL, &b64, &b64_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_import(YACA_KEY_TYPE_SYMMETRIC, NULL, b64, b64_len, &b64_imported);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_export(key, YACA_KEY_FORMAT_DEFAULT, YACA_KEY_FILE_FORMAT_RAW, NULL, &raw, &raw_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_import(YACA_KEY_TYPE_SYMMETRIC, NULL, raw, raw_len, &raw_imported);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_key_destroy(key);
	yaca_key_destroy(b64_imported);
	yaca_key_destroy(raw_imported);
	yaca_free(raw);
	yaca_free(b64);

	return 0;
}

/**
 * @testcase        utc_yaca_key_import_p2
 * @since_tizen     3.0
 * @description     Imports a key.
 * @scenario        Imports a key with DES key type.
 */
int utc_yaca_key_import_p2(void)
{
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_type_e key_type = YACA_KEY_TYPE_DES;
	size_t key_bit_len = YACA_KEY_LENGTH_192BIT;
	int ret = YACA_ERROR_NONE;

	yaca_key_h b64_imported = YACA_KEY_NULL;
	yaca_key_h raw_imported = YACA_KEY_NULL;

	char *raw = NULL;
	size_t raw_len;
	char *b64 = NULL;
	size_t b64_len;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_export(key, YACA_KEY_FORMAT_DEFAULT, YACA_KEY_FILE_FORMAT_BASE64, NULL, &b64, &b64_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_import(YACA_KEY_TYPE_SYMMETRIC, NULL, b64, b64_len, &b64_imported);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_export(key, YACA_KEY_FORMAT_DEFAULT, YACA_KEY_FILE_FORMAT_RAW, NULL, &raw, &raw_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_import(YACA_KEY_TYPE_SYMMETRIC, NULL, raw, raw_len, &raw_imported);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_key_destroy(key);
	yaca_key_destroy(b64_imported);
	yaca_key_destroy(raw_imported);
	yaca_free(raw);
	yaca_free(b64);

	return 0;
}

int export_import_asymmetric_keys(yaca_key_type_e pri_key_type, yaca_key_type_e pub_key_type, size_t key_bit_len)
{
	yaca_key_h pri_key = YACA_KEY_NULL;
	yaca_key_h pub_key = YACA_KEY_NULL;
	char * password = "test_password";
	int ret = YACA_ERROR_NONE;

	yaca_key_h pem_imported = YACA_KEY_NULL;
	yaca_key_h der_imported = YACA_KEY_NULL;
	yaca_key_h pkcs8_imported = YACA_KEY_NULL;

	char *der = NULL;
	size_t der_len;
	char *pem = NULL;
	size_t pem_len;
	char *pkcs8 = NULL;
	size_t pkcs8_len;

	ret = yaca_key_generate(pri_key_type, key_bit_len, &pri_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(pri_key, &pub_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_export(pri_key, YACA_KEY_FORMAT_DEFAULT, YACA_KEY_FILE_FORMAT_DER, NULL, &der, &der_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_import(pri_key_type, NULL, der, der_len, &der_imported);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_export(pub_key, YACA_KEY_FORMAT_DEFAULT, YACA_KEY_FILE_FORMAT_PEM, NULL, &pem, &pem_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_import(pub_key_type, NULL, pem, pem_len, &pem_imported);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_export(pri_key, YACA_KEY_FORMAT_PKCS8, YACA_KEY_FILE_FORMAT_DER, password, &pkcs8, &pkcs8_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_import(pri_key_type, password, pkcs8, pkcs8_len, &pkcs8_imported);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_key_destroy(pri_key);
	yaca_key_destroy(pub_key);
	yaca_key_destroy(pem_imported);
	yaca_key_destroy(der_imported);
	yaca_key_destroy(pkcs8_imported);
	yaca_free(der);
	yaca_free(pem);
	yaca_free(pkcs8);

	return 0;
}


/**
 * @testcase        utc_yaca_key_import_p3
 * @since_tizen     3.0
 * @description     Imports a key.
 * @scenario        Imports a key with RSA key type.
 */
int utc_yaca_key_import_p3(void)
{
	return export_import_asymmetric_keys(YACA_KEY_TYPE_RSA_PRIV, YACA_KEY_TYPE_RSA_PUB, YACA_KEY_LENGTH_1024BIT);
}

/*
 * @testcase        utc_yaca_key_import_p4
 * @since_tizen     3.0
 * @description     Imports a key.
 * @scenario        Imports a key with DSA key type.
 */
int utc_yaca_key_import_p4(void)
{
	return export_import_asymmetric_keys(YACA_KEY_TYPE_DSA_PRIV, YACA_KEY_TYPE_DSA_PUB, YACA_KEY_LENGTH_1024BIT);
}

/*
 * @testcase        utc_yaca_key_import_p5
 * @since_tizen     3.0
 * @description     Imports a key.
 * @scenario        Imports a key with ECDSA key type.
 */
int utc_yaca_key_import_p5(void)
{
	return export_import_asymmetric_keys(YACA_KEY_TYPE_EC_PRIV, YACA_KEY_TYPE_EC_PUB, YACA_KEY_LENGTH_EC_SECP384R1);
}

/*
 * @testcase        utc_yaca_key_import_p6
 * @since_tizen     3.0
 * @description     Imports a key.
 * @scenario        Imports a key with Diffie-Helmann key type.
 */
int utc_yaca_key_import_p6(void)
{
	return export_import_asymmetric_keys(YACA_KEY_TYPE_DH_PRIV, YACA_KEY_TYPE_DH_PUB, YACA_KEY_LENGTH_DH_RFC_2048_224);
}

int export_import_asymmetric_params(yaca_key_type_e param_key_type, size_t key_bit_len)
{
	yaca_key_h param_key = YACA_KEY_NULL;
	int ret = YACA_ERROR_NONE;

	yaca_key_h pem_imported = YACA_KEY_NULL;
	yaca_key_h der_imported = YACA_KEY_NULL;

	char *der = NULL;
	size_t der_len;
	char *pem = NULL;
	size_t pem_len;

	ret = yaca_key_generate(param_key_type, key_bit_len, &param_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_export(param_key, YACA_KEY_FORMAT_DEFAULT, YACA_KEY_FILE_FORMAT_DER, NULL, &der, &der_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_import(param_key_type, NULL, der, der_len, &der_imported);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_export(param_key, YACA_KEY_FORMAT_DEFAULT, YACA_KEY_FILE_FORMAT_PEM, NULL, &pem, &pem_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_import(param_key_type, NULL, pem, pem_len, &pem_imported);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_key_destroy(param_key);
	yaca_key_destroy(pem_imported);
	yaca_key_destroy(der_imported);
	yaca_free(der);
	yaca_free(pem);

	return 0;
}

/*
 * @testcase        utc_yaca_key_import_p7
 * @since_tizen     3.0
 * @description     Imports parameters.
 * @scenario        Imports parameters for DSA algorithm.
 */
int utc_yaca_key_import_p7(void)
{
	return export_import_asymmetric_params(YACA_KEY_TYPE_DSA_PARAMS, YACA_KEY_LENGTH_512BIT);
}

/*
 * @testcase        utc_yaca_key_import_p8
 * @since_tizen     3.0
 * @description     Imports parameters.
 * @scenario        Imports parameters for DSA algorithm.
 */
int utc_yaca_key_import_p8(void)
{
	return export_import_asymmetric_params(YACA_KEY_TYPE_DH_PARAMS, YACA_KEY_LENGTH_DH_RFC_2048_256);
}

/*
 * @testcase        utc_yaca_key_import_p9
 * @since_tizen     3.0
 * @description     Imports parameters.
 * @scenario        Imports parameters for ECDSA algorithm.
 */
int utc_yaca_key_import_p9(void)
{
	return export_import_asymmetric_params(YACA_KEY_TYPE_EC_PARAMS, YACA_KEY_LENGTH_EC_PRIME256V1);
}





/**
 * @testcase        utc_yaca_key_import_n
 * @since_tizen     3.0
 * @description     Imports a key.
 * @scenario        Imports a key with invalid parameters.
 */
int utc_yaca_key_import_n(void)
{
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;
	int ret = YACA_ERROR_NONE;

	yaca_key_h b64_imported = YACA_KEY_NULL;

	char *b64 = NULL;
	size_t b64_len;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_export(key, YACA_KEY_FORMAT_DEFAULT, YACA_KEY_FILE_FORMAT_BASE64, NULL, &b64, &b64_len);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_import((yaca_key_type_e) -1, NULL, b64, b64_len, &b64_imported);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_import(YACA_KEY_TYPE_SYMMETRIC, NULL, NULL, b64_len, &b64_imported);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_import(YACA_KEY_TYPE_SYMMETRIC, NULL, b64, 0, &b64_imported);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_import(YACA_KEY_TYPE_SYMMETRIC, NULL, b64, b64_len, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_key_destroy(key);
	yaca_key_destroy(b64_imported);
	yaca_free(b64);

	return 0;
}

/**
 * @testcase        utc_yaca_key_export_p
 * @since_tizen     3.0
 * @description     Exports a key.
 * @scenario        Exports a key with valid parameters.
 */
int utc_yaca_key_export_p(void)
{
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;
	int ret = YACA_ERROR_NONE;

	char *b64 = NULL;
	size_t b64_len;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_export(key, YACA_KEY_FORMAT_DEFAULT, YACA_KEY_FILE_FORMAT_BASE64, NULL, &b64, &b64_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_key_destroy(key);
	yaca_free(b64);

	return 0;
}

/**
 * @testcase        utc_yaca_key_export_n
 * @since_tizen     3.0
 * @description     Exports a key.
 * @scenario        Exports a key with invalid parameters.
 */
int utc_yaca_key_export_n(void)
{
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;
	int ret = YACA_ERROR_NONE;

	char *b64 = NULL;
	size_t b64_len;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_export(NULL, YACA_KEY_FORMAT_DEFAULT, YACA_KEY_FILE_FORMAT_BASE64, NULL, &b64, &b64_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_export(key, (yaca_key_format_e) -1, YACA_KEY_FILE_FORMAT_BASE64, NULL, &b64, &b64_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_export(key, YACA_KEY_FORMAT_DEFAULT, (yaca_key_file_format_e) -1, NULL, &b64, &b64_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_export(key, YACA_KEY_FORMAT_DEFAULT, YACA_KEY_FILE_FORMAT_BASE64, NULL, NULL, &b64_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_export(key, YACA_KEY_FORMAT_DEFAULT, YACA_KEY_FILE_FORMAT_BASE64, NULL, &b64, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_key_generate_p
 * @since_tizen     3.0
 * @description     Generates a secure key.
 * @scenario        Generates a secure key with valid parameters.
 */
int utc_yaca_key_generate_p(void)
{
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;
	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(key_type, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_key_generate_n
 * @since_tizen     3.0
 * @description     Generates a secure key.
 * @scenario        Generates a secure key with invalid parameters.
 */
int utc_yaca_key_generate_n(void)
{
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_type_e key_type = YACA_KEY_TYPE_SYMMETRIC;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;
	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate((yaca_key_type_e) -1, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_generate(key_type, 0, &key);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_generate(key_type, key_bit_len, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_yaca_key_generate_from_parameters_p
 * @since_tizen     3.0
 * @description     Generates a secure key from parameters.
 * @scenario        Generates a secure key from parameters with valid parameters.
 */
int utc_yaca_key_generate_from_parameters_p(void)
{
	int ret = YACA_ERROR_NONE;
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_h key_params = YACA_KEY_NULL;

	ret = yaca_key_generate(YACA_KEY_TYPE_DSA_PARAMS, YACA_KEY_LENGTH_512BIT, &key_params);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_generate_from_parameters(key_params, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_key_destroy(key);
	yaca_key_destroy(key_params);

	return 0;
}

/**
 * @testcase        utc_yaca_key_generate_from_parameters_n
 * @since_tizen     3.0
 * @description     Generates a secure key from parameters.
 * @scenario        Generates a secure key from parameters with invalid parameters.
 */
int utc_yaca_key_generate_from_parameters_n(void)
{
	int ret = YACA_ERROR_NONE;
	yaca_key_h key = YACA_KEY_NULL;
	yaca_key_h key_params = YACA_KEY_NULL;

	ret = yaca_key_generate(YACA_KEY_TYPE_DSA_PARAMS, YACA_KEY_LENGTH_512BIT, &key_params);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_generate_from_parameters(NULL, &key);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_generate_from_parameters(key_params, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_key_destroy(key_params);

	return 0;
}

/**
 * @testcase        utc_yaca_key_extract_public_p
 * @since_tizen     3.0
 * @description     Extracts public key from a private one.
 * @scenario        Extracts public key from a private one with valid parameters.
 */
int utc_yaca_key_extract_public_p(void)
{
	yaca_key_h rsa_priv = YACA_KEY_NULL;
	yaca_key_h rsa_pub = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_RSA_PRIV, YACA_KEY_LENGTH_1024BIT, &rsa_priv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(rsa_priv, &rsa_pub);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_key_destroy(rsa_pub);
	yaca_key_destroy(rsa_priv);

	return 0;
}

/**
 * @testcase        utc_yaca_key_extract_public_n
 * @since_tizen     3.0
 * @description     Extracts public key from a private one.
 * @scenario        Extracts public key from a private one with invalid parameters.
 */
int utc_yaca_key_extract_public_n(void)
{
	yaca_key_h dsa_priv = YACA_KEY_NULL;
	yaca_key_h dsa_pub = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_DSA_PRIV, YACA_KEY_LENGTH_1024BIT, &dsa_priv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(NULL, &dsa_pub);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_extract_public(dsa_priv, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_key_destroy(dsa_pub);
	yaca_key_destroy(dsa_priv);

	return 0;
}

/**
 * @testcase        utc_yaca_key_extract_parameters_p
 * @since_tizen     3.0
 * @description     Extracts parameters from a key.
 * @scenario        Extracts parameters from a key with valid parameters.
 */
int utc_yaca_key_extract_parameters_p(void)
{
	yaca_key_h priv = YACA_KEY_NULL;
	yaca_key_h pub = YACA_KEY_NULL;
	yaca_key_h params = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_EC_PRIV, YACA_KEY_LENGTH_EC_PRIME256V1, &priv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(priv, &pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_parameters(pub, &params);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_key_destroy(pub);
	yaca_key_destroy(priv);
	yaca_key_destroy(params);

	return 0;
}

/**
 * @testcase        utc_yaca_key_extract_parameters_n
 * @since_tizen     3.0
 * @description     Extracts parameters from a key.
 * @scenario        Extracts parameters from a key with invalid parameters.
 */
int utc_yaca_key_extract_parameters_n(void)
{
	yaca_key_h priv = YACA_KEY_NULL;
	yaca_key_h pub = YACA_KEY_NULL;
	yaca_key_h params = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_EC_PRIV, YACA_KEY_LENGTH_EC_PRIME256V1, &priv);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(priv, &pub);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_parameters(NULL, &params);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_extract_parameters(pub, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_key_destroy(pub);
	yaca_key_destroy(priv);
	yaca_key_destroy(params);

	return 0;
}


/**
 * @testcase        utc_yaca_key_destroy_p
 * @since_tizen     3.0
 * @description     Release the key created by the library.
 * @scenario        Release the key created by the library with valid parameters.
 */
int utc_yaca_key_destroy_p(void)
{
	yaca_key_h dsa_priv = YACA_KEY_NULL;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_DSA_PRIV, YACA_KEY_LENGTH_1024BIT, &dsa_priv);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_key_destroy(dsa_priv);

	return 0;
}

/**
 * @testcase        utc_yaca_key_derive_pbkdf2_p
 * @since_tizen     3.0
 * @description     Derives a key from user password.
 * @scenario        Derives a key from user password with valid parameters.
 */
int utc_yaca_key_derive_pbkdf2_p(void)
{
	yaca_key_h key = YACA_KEY_NULL;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_derive_pbkdf2("foo bar", "123456789", 10, 1000,
								YACA_DIGEST_SHA256, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_key_destroy(key);

	return 0;
}

/**
 * @testcase        utc_yaca_key_derive_pbkdf2_n
 * @since_tizen     3.0
 * @description     Derives a key from user password.
 * @scenario        Derives a key from user password with invalid parameters.
 */
int utc_yaca_key_derive_pbkdf2_n(void)
{
	yaca_key_h key = YACA_KEY_NULL;
	size_t key_bit_len = YACA_KEY_LENGTH_256BIT;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_derive_pbkdf2(NULL, "123456789", 10, 1000,
								YACA_DIGEST_SHA256, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_derive_pbkdf2("foo bar", NULL, 10, 1000,
								YACA_DIGEST_SHA256, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_derive_pbkdf2("foo bar", "123456789", 0, 1000,
								YACA_DIGEST_SHA256, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_derive_pbkdf2("foo bar", "123456789", 10, 0,
								YACA_DIGEST_SHA256, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_derive_pbkdf2("foo bar", "123456789", 10, 1000,
								(yaca_digest_algorithm_e) -1, key_bit_len, &key);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_derive_pbkdf2("foo bar", "123456789", 10, 1000,
								YACA_DIGEST_SHA256, 0, &key);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_derive_pbkdf2("foo bar", "123456789", 10, 1000,
								YACA_DIGEST_SHA256, key_bit_len, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_yaca_key_derive_dh_p
 * @since_tizen     3.0
 * @description     Derives a key from Diffie-Hellman keys.
 * @scenario        Derives a key from Diffie-Hellman keys with valid parameters.
 */
int utc_yaca_key_derive_dh_p(void)
{
	yaca_key_h dh_peer_pri_key = YACA_KEY_NULL;
	yaca_key_h dh_peer_pub_key = YACA_KEY_NULL;
	yaca_key_h dh_pri_key = YACA_KEY_NULL;
	yaca_key_h params = YACA_KEY_NULL;
	char *secret = NULL;
	size_t secret_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_DH_PRIV, YACA_KEY_LENGTH_DH_RFC_2048_256, &dh_peer_pri_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(dh_peer_pri_key, &dh_peer_pub_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_parameters(dh_peer_pub_key, &params);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_generate_from_parameters(params, &dh_pri_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_derive_dh(dh_pri_key, dh_peer_pub_key, &secret, &secret_len);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_key_destroy(dh_peer_pri_key);
	yaca_key_destroy(dh_peer_pub_key);
	yaca_key_destroy(dh_pri_key);
	yaca_key_destroy(params);
	yaca_free(secret);

	return 0;
}

/**
 * @testcase        utc_yaca_key_derive_dh_n
 * @since_tizen     3.0
 * @description     Derives a key from Diffie-Hellman keys.
 * @scenario        Derives a key from Diffie-Hellman keys with invalid parameters.
 */
int utc_yaca_key_derive_dh_n(void)
{
	yaca_key_h dh_peer_pri_key = YACA_KEY_NULL;
	yaca_key_h dh_peer_pub_key = YACA_KEY_NULL;
	yaca_key_h dh_pri_key = YACA_KEY_NULL;
	yaca_key_h params = YACA_KEY_NULL;
	char *secret = NULL;
	size_t secret_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_DH_PRIV, YACA_KEY_LENGTH_DH_RFC_2048_256, &dh_peer_pri_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(dh_peer_pri_key, &dh_peer_pub_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_parameters(dh_peer_pub_key, &params);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_generate_from_parameters(params, &dh_pri_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_derive_dh(NULL, dh_peer_pub_key, &secret, &secret_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_derive_dh(dh_pri_key, NULL, &secret, &secret_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_derive_dh(dh_pri_key, dh_peer_pub_key, NULL, &secret_len);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_derive_dh(dh_pri_key, dh_peer_pub_key, &secret, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_key_destroy(dh_peer_pri_key);
	yaca_key_destroy(dh_peer_pub_key);
	yaca_key_destroy(dh_pri_key);
	yaca_key_destroy(params);
	yaca_free(secret);

	return 0;
}


/**
 * @testcase        utc_yaca_key_derive_kdf_p
 * @since_tizen     3.0
 * @description     Derives a key from a secret.
 * @scenario        Derives a key from a secret with valid parameters.
 */
int utc_yaca_key_derive_kdf_p(void)
{
	yaca_key_h dh_peer_pri_key = YACA_KEY_NULL;
	yaca_key_h dh_peer_pub_key = YACA_KEY_NULL;
	yaca_key_h dh_pri_key = YACA_KEY_NULL;
	yaca_key_h params = YACA_KEY_NULL;
	char *secret = NULL;
	size_t secret_len;
	char *temp_material = NULL;
	size_t temp_material_len;
	size_t key_material_len;
	size_t iv_material_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_DH_PRIV, YACA_KEY_LENGTH_DH_RFC_2048_256, &dh_peer_pri_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(dh_peer_pri_key, &dh_peer_pub_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_parameters(dh_peer_pub_key, &params);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_generate_from_parameters(params, &dh_pri_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_derive_dh(dh_pri_key, dh_peer_pub_key, &secret, &secret_len);
	assert_eq(ret, YACA_ERROR_NONE);

	key_material_len = YACA_KEY_LENGTH_192BIT / 8;
	iv_material_len = YACA_KEY_LENGTH_IV_128BIT / 8;
	temp_material_len = key_material_len + iv_material_len;
	ret = yaca_key_derive_kdf(YACA_KDF_X962, YACA_DIGEST_SHA512, secret, secret_len,
								NULL, 0, temp_material_len, &temp_material);
	assert_eq(ret, YACA_ERROR_NONE);

	yaca_key_destroy(dh_peer_pri_key);
	yaca_key_destroy(dh_peer_pub_key);
	yaca_key_destroy(dh_pri_key);
	yaca_key_destroy(params);
	yaca_free(secret);
	yaca_free(temp_material);

	return 0;
}

/**
 * @testcase        utc_yaca_key_derive_kdf_n
 * @since_tizen     3.0
 * @description     Derives a key from a secret.
 * @scenario        Derives a key from a secret with invalid parameters.
 */
int utc_yaca_key_derive_kdf_n(void)
{
	yaca_key_h dh_peer_pri_key = YACA_KEY_NULL;
	yaca_key_h dh_peer_pub_key = YACA_KEY_NULL;
	yaca_key_h dh_pri_key = YACA_KEY_NULL;
	yaca_key_h params = YACA_KEY_NULL;
	char *secret = NULL;
	size_t secret_len;
	char *temp_material = NULL;
	size_t temp_material_len;
	size_t key_material_len;
	size_t iv_material_len;

	int ret = YACA_ERROR_NONE;

	ret = yaca_key_generate(YACA_KEY_TYPE_DH_PRIV, YACA_KEY_LENGTH_DH_RFC_2048_256, &dh_peer_pri_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_public(dh_peer_pri_key, &dh_peer_pub_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_extract_parameters(dh_peer_pub_key, &params);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_generate_from_parameters(params, &dh_pri_key);
	assert_eq(ret, YACA_ERROR_NONE);

	ret = yaca_key_derive_dh(dh_pri_key, dh_peer_pub_key, &secret, &secret_len);
	assert_eq(ret, YACA_ERROR_NONE);

	key_material_len = YACA_KEY_LENGTH_192BIT / 8;
	iv_material_len = YACA_KEY_LENGTH_IV_128BIT / 8;
	temp_material_len = key_material_len + iv_material_len;

	ret = yaca_key_derive_kdf((yaca_kdf_e) -1, YACA_DIGEST_SHA512, secret, secret_len,
								NULL, 0, temp_material_len, &temp_material);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_derive_kdf(YACA_KDF_X962, (yaca_digest_algorithm_e) -1, secret, secret_len,
								NULL, 0, temp_material_len, &temp_material);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_derive_kdf(YACA_KDF_X962, YACA_DIGEST_SHA512, NULL, secret_len,
								NULL, 0, temp_material_len, &temp_material);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_derive_kdf(YACA_KDF_X962, YACA_DIGEST_SHA512, secret, 0,
								NULL, 0, temp_material_len, &temp_material);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_derive_kdf(YACA_KDF_X962, YACA_DIGEST_SHA512, secret, secret_len,
								NULL, 0, 0, &temp_material);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	ret = yaca_key_derive_kdf(YACA_KDF_X962, YACA_DIGEST_SHA512, secret, secret_len,
								NULL, 0, temp_material_len, NULL);
	assert_eq(ret, YACA_ERROR_INVALID_PARAMETER);

	yaca_key_destroy(dh_peer_pri_key);
	yaca_key_destroy(dh_peer_pub_key);
	yaca_key_destroy(dh_pri_key);
	yaca_key_destroy(params);
	yaca_free(secret);
	yaca_free(temp_material);

	return 0;
}

