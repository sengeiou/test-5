//
// Copyright (c) 2014 - 2019 Samsung Electronics Co., Ltd.
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
#include "res-util.h"

#include <ckmc/ckmc-manager.h>
#include <ckmc/ckmc-type.h>
#include <ckmc/ckmc-error.h>

#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

//& set: key-manager-storage2
static const char* RSA_PUB_KEY_PEM = "-----BEGIN PUBLIC KEY-----\n"
    "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA2b1bXDa+S8/MGWnMkru4\n"
    "T4tUddtZNi0NVjQn9RFH1NMa220GsRhRO56F77FlSVFKfSfVZKIiWg6C+DVCkcLf\n"
    "zXJ/Z0pvwOQYBAqVMFjV6efQGN0JzJ1Unu7pPRiZl7RKGEI+cyzzrcDyrLLrQ2W7\n"
    "0ZySkNEOv6Frx9JgC5NExuYY4lk2fQQa38JXiZkfyzif2em0px7mXbyf5LjccsKq\n"
    "v1e+XLtMsL0ZefRcqsP++NzQAI8fKX7WBT+qK0HJDLiHrKOTWYzx6CwJ66LD/vvf\n"
    "j55xtsKDLVDbsotvf8/m6VLMab+vqKk11TP4tq6yo0mwyTADvgl1zowQEO9I1W6o\n"
    "zQIDAQAB\n"
    "-----END PUBLIC KEY-----";

static const char* CERT_PEM = "-----BEGIN CERTIFICATE-----\n"
    "MIIEgDCCA2igAwIBAgIIcjtBYJGQtOAwDQYJKoZIhvcNAQEFBQAwSTELMAkGA1UE\n"
    "BhMCVVMxEzARBgNVBAoTCkdvb2dsZSBJbmMxJTAjBgNVBAMTHEdvb2dsZSBJbnRl\n"
    "cm5ldCBBdXRob3JpdHkgRzIwHhcNMTQwNTIyMTEyOTQyWhcNMTQwODIwMDAwMDAw\n"
    "WjBtMQswCQYDVQQGEwJVUzETMBEGA1UECAwKQ2FsaWZvcm5pYTEWMBQGA1UEBwwN\n"
    "TW91bnRhaW4gVmlldzETMBEGA1UECgwKR29vZ2xlIEluYzEcMBoGA1UEAwwTYWNj\n"
    "b3VudHMuZ29vZ2xlLmNvbTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB\n"
    "ALtlLWVWPN3q3bSEQl1Z97gPdgl5vbgJOZSAr0ZY0tJCuFLBbUKetJWryyE+5KpG\n"
    "gMMpLS4v8/bvXaZc6mAs+RfAqGM24C3vQg5hPnj4dflnhL0WiOCZBurm1tV4oexk\n"
    "HLXs3jr/jpnb738AQpj8zZ9a4VEBuHJRZALnWZ/XhqU+dvYomAoRQNuL5OhkT7uu\n"
    "d0NKJL9JjYLyQglGgE2sVsWv2kj7EO/P9Q6NEKt9BGmhMsFvtfeKUaymynaxpR1g\n"
    "wEPlqYvB38goh1dIOgVLT0OVyLImeg5Mdwar/8c1U0OYhLOc6PJapOZAfUkE+3+w\n"
    "xYt8AChLN1b5szOwInrCVpECAwEAAaOCAUYwggFCMB0GA1UdJQQWMBQGCCsGAQUF\n"
    "BwMBBggrBgEFBQcDAjAeBgNVHREEFzAVghNhY2NvdW50cy5nb29nbGUuY29tMGgG\n"
    "CCsGAQUFBwEBBFwwWjArBggrBgEFBQcwAoYfaHR0cDovL3BraS5nb29nbGUuY29t\n"
    "L0dJQUcyLmNydDArBggrBgEFBQcwAYYfaHR0cDovL2NsaWVudHMxLmdvb2dsZS5j\n"
    "b20vb2NzcDAdBgNVHQ4EFgQU0/UtToEtNIfwDwHuYGuVKcj0xK8wDAYDVR0TAQH/\n"
    "BAIwADAfBgNVHSMEGDAWgBRK3QYWG7z2aLV29YG2u2IaulqBLzAXBgNVHSAEEDAO\n"
    "MAwGCisGAQQB1nkCBQEwMAYDVR0fBCkwJzAloCOgIYYfaHR0cDovL3BraS5nb29n\n"
    "bGUuY29tL0dJQUcyLmNybDANBgkqhkiG9w0BAQUFAAOCAQEAcGNI/X9f0g+7ij0o\n"
    "ehLpk6vxSMQGrmOZ4+PG/MC9SLClCkt7zJkfU7erZnyVXyxCpwlljq+Wk9YTPUOq\n"
    "xD/V2ikQVSAANoxGJFO9UoL5jzWusPhKKv8CcM7fuiERz8K+CfBcqfxbgI5rH0g5\n"
    "dYclmLC81cJ/08i+9Nltvxv69Y3hGfEICT6K+EdSxwnQzOhpMZmvxZsIj+d6CVNa\n"
    "9ICYgUthsNQVWzrIs5wknpjjZ9liDMwJX0vu8A0rce4X/Lna5hh2bW9igz2iP5WM\n"
    "9fuwdbTw4y3jfPQgszU4YZxWxhMzccxe058Qx1tLndAknBQEBesQjXytVQpuM1SV\n"
    "rHva8A==\n"
    "-----END CERTIFICATE-----\n";

/**
 * @function		utc_key_manager_store_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_key_manager_store_startup(void)
{

//    setuid(APPUSER_ID);
}

/**
 * @function		utc_key_manager_store_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_key_manager_store_cleanup(void)
{
}

/**
 * @testcase        utc_ckmc_save_key_p
 * @since_tizen     2.3
 * @description     Store a key
 * @scenario        Store a key with a key alias, a key object and store policy 
 */
int utc_ckmc_save_key_p(void)
{
    int temp;
    ckmc_key_s test_key;
    char* key_password = NULL;
    ckmc_policy_s test_policy;
    char* policy_password = NULL;
    char* alias = "save_key_p";

    test_key.raw_key =  (unsigned char *)RSA_PUB_KEY_PEM;
    test_key.key_size = strlen(RSA_PUB_KEY_PEM);
    test_key.key_type = CKMC_KEY_RSA_PUBLIC;
    test_key.password = key_password;

    test_policy.password = policy_password;
    test_policy.extractable = true;

    temp = ckmc_save_key(alias, test_key, test_policy);
    assert_eq(temp,CKMC_ERROR_NONE);

    ckmc_remove_alias(alias);

    return 0;
}

/**
 * @testcase        utc_ckmc_save_key_n
 * @since_tizen     2.3
 * @description     Check an error in storing a key.
 * @scenario        Try to store a corrupted key.
                    Try to store a key with a NULL alias .
 */
int utc_ckmc_save_key_n(void)
{
    int temp;
    ckmc_key_s test_key, correct_test_key;
    char* key_password = NULL;
    ckmc_policy_s test_policy;
    char* policy_password = NULL;
    char* alias = "save_key_n";
    char* keyPem = "-----BEGIN PUBLICnzQIDAQAB\n-----END PUBLIC KEY-----";
    char* null_alias = NULL;

    test_key.raw_key =  (unsigned char *)keyPem;
    test_key.key_size = strlen(keyPem);
    test_key.key_type = CKMC_KEY_RSA_PUBLIC;
    test_key.password = key_password;

    correct_test_key.raw_key =  (unsigned char *)RSA_PUB_KEY_PEM;
    correct_test_key.key_size = strlen(RSA_PUB_KEY_PEM);
    correct_test_key.key_type = CKMC_KEY_RSA_PUBLIC;
    correct_test_key.password = key_password;

    test_policy.password = policy_password;
    test_policy.extractable = true;

    // check CKMC_ERROR_INVALID_FORMAT
    temp = ckmc_save_key(alias, test_key, test_policy);
    assert_eq(temp, CKMC_ERROR_INVALID_FORMAT);

    // check CKMC_ERROR_INVALID_PARAMETER
    temp = ckmc_save_key(null_alias, correct_test_key, test_policy);
    assert_eq(temp, CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_ckmc_remove_key_p
 * @since_tizen     2.3
 * @description     Remove a key
 * @scenario        Store a key and remove it with its alias. 
 */
int utc_ckmc_remove_key_p(void)
{
    int temp;
    ckmc_key_s test_key;
    char* key_password = NULL;
    ckmc_policy_s test_policy;
    char* policy_password = NULL;
    char* alias = "remove_key_p";

    test_key.raw_key =  (unsigned char *)RSA_PUB_KEY_PEM;
    test_key.key_size = strlen(RSA_PUB_KEY_PEM);
    test_key.key_type = CKMC_KEY_RSA_PUBLIC;
    test_key.password = key_password;

    test_policy.password = policy_password;
    test_policy.extractable = true;

    temp = ckmc_save_key(alias, test_key, test_policy);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_remove_key(alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_remove_key_n
 * @since_tizen     2.3
 * @description     Check an error in removing a key.
 * @scenario        Store a key.
                    Try to remove a key with a wrong alias.
                    Try to remove a key with a NULL alias.
 */
int utc_ckmc_remove_key_n(void)
{
    int temp;
    ckmc_key_s test_key;
    char* key_password = NULL;
    ckmc_policy_s test_policy;
    char* policy_password = NULL;
    char* alias = "remove_key_n";
    char* wrong_alias = "wrong";
    char* null_alias = NULL;

    test_key.raw_key =  (unsigned char *)RSA_PUB_KEY_PEM;
    test_key.key_size = strlen(RSA_PUB_KEY_PEM);
    test_key.key_type = CKMC_KEY_RSA_PUBLIC;
    test_key.password = key_password;

    test_policy.password = policy_password;
    test_policy.extractable = true;

    temp = ckmc_save_key(alias, test_key, test_policy);
    assert_eq(temp,CKMC_ERROR_NONE);

    // check CKMC_ERROR_DB_ALIAS_UNKNOWN
    temp = ckmc_remove_key(wrong_alias);
    assert_eq(temp, CKMC_ERROR_DB_ALIAS_UNKNOWN);

    // check CKMC_ERROR_INVALID_PARAMETER
    temp = ckmc_remove_key(null_alias);
    assert_eq(temp, CKMC_ERROR_INVALID_PARAMETER);

    temp = ckmc_remove_key(alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_key_p
 * @since_tizen     2.3
 * @description     Get a key from DB
 * @scenario        Store a key and get it with its alias. 
 */
int utc_ckmc_get_key_p(void)
{
    int temp;
    ckmc_key_s test_key, *test_key2;
    char* key_password = NULL;
    ckmc_policy_s test_policy, test_policy2;
    char* policy_password = NULL;
    char* alias = "get_key_p";
    char* alias2 = "get_key_p_2";

    test_key.raw_key =  (unsigned char *)RSA_PUB_KEY_PEM;
    test_key.key_size = strlen(RSA_PUB_KEY_PEM);
    test_key.key_type = CKMC_KEY_RSA_PUBLIC;
    test_key.password = key_password;

    test_policy.password = policy_password;
    test_policy.extractable = true;

    test_policy2.password = policy_password;
    test_policy2.extractable = false;

    temp = ckmc_save_key(alias, test_key, test_policy);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_save_key(alias2, test_key, test_policy2);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_get_key(alias, key_password, &test_key2);
    assert_eq(temp, CKMC_ERROR_NONE);

    ckmc_key_free(test_key2);

    temp = ckmc_remove_alias(alias);
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_remove_alias(alias2);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_key_n
 * @since_tizen     2.3
 * @description     Check an error in getting a key.
 * @scenario        Try to remove a key with a NULL alias.
                    Try to remove a key with a wrong alias.
 */
int utc_ckmc_get_key_n(void)
{
    int temp;
    ckmc_key_s *test_key;
    char* policy_password = NULL;
    char* wrong_alias = NULL;
    char* nonKey = "get_key_n2";

    // check CKMC_ERROR_INVALID_PARAMETER
    temp = ckmc_get_key(wrong_alias, policy_password, &test_key);
    assert_eq(temp, CKMC_ERROR_INVALID_PARAMETER);

    // check CKMC_ERROR_DB_ALIAS_UNKNOWN
    temp = ckmc_get_key(nonKey, policy_password, &test_key);
    assert_eq(temp, CKMC_ERROR_DB_ALIAS_UNKNOWN);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_key_n2
 * @since_tizen     2.3
 * @description     Check an error in removing a key.
 * @scenario        Store a key with extractable = false option.
                    Try to get a key with its alias.
 */
int utc_ckmc_get_key_n2(void)
{
    int temp;
    ckmc_key_s test_key, *test_key2;
    char* key_password = NULL;
    ckmc_policy_s test_policy;
    char* policy_password = NULL;
    char* alias = "get_key_n2";

    test_key.raw_key =  (unsigned char *)RSA_PUB_KEY_PEM;
    test_key.key_size = strlen(RSA_PUB_KEY_PEM);
    test_key.key_type = CKMC_KEY_RSA_PUBLIC;
    test_key.password = key_password;

    test_policy.password = policy_password;
    test_policy.extractable = false;

    temp = ckmc_save_key(alias, test_key, test_policy);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_get_key(alias, key_password, &test_key2);
    assert_eq(temp, CKMC_ERROR_NOT_EXPORTABLE);

    temp = ckmc_remove_alias(alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_key_alias_list_p
 * @since_tizen     2.3
 * @description     Get a alias list of keys from DB
 * @scenario        Get a alias list of keys with a 0 sized list.
                    Stores several keys.
                    Get a alias list of keys with aliases of stored keys
 */
int utc_ckmc_get_key_alias_list_p(void)
{
    int temp;

    ckmc_key_s test_key;
    char* key_password = NULL;

    ckmc_policy_s test_policy1, test_policy2;
    char* policy_password = NULL;
    ckmc_alias_list_s *aliasList = NULL;
    ckmc_alias_list_s *aliasNext = NULL;
    int cnt1 = 0;
    int cnt2 = 0;

    temp = ckmc_get_key_alias_list(&aliasList);
    if (temp == CKMC_ERROR_NONE) {
        // key-manager has key
        aliasNext = aliasList;
        while (aliasNext) {
            aliasNext = aliasNext->next;
            cnt1++;
        }
        ckmc_alias_list_all_free(aliasList);
    }
    else if (temp == CKMC_ERROR_DB_ALIAS_UNKNOWN) {
        // key-manager has no key
        cnt1 = 0;
    }
    else {
        // error.
        assert_eq(1, 0);
    }

    test_key.raw_key =  (unsigned char *)RSA_PUB_KEY_PEM;
    test_key.key_size = strlen(RSA_PUB_KEY_PEM);
    test_key.key_type = CKMC_KEY_RSA_PUBLIC;
    test_key.password = key_password;

    test_policy1.password = policy_password;
    test_policy1.extractable = true;

    test_policy2.password = policy_password;
    test_policy2.extractable = false;

    temp = ckmc_save_key("get_key_alias_list_p_1", test_key, test_policy1);
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_save_key("get_key_alias_list_p_2", test_key, test_policy2);
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_save_key("get_key_alias_list_p_3", test_key, test_policy2);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_get_key_alias_list(&aliasList);
    assert_eq(temp, CKMC_ERROR_NONE);

    aliasNext = aliasList;
    while (aliasNext) {
        aliasNext = aliasNext->next;
        cnt2++;
    }
    ckmc_alias_list_all_free(aliasList);

    assert_eq((cnt2 - cnt1), 3);

    temp = ckmc_remove_alias("get_key_alias_list_p_1");
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_remove_alias("get_key_alias_list_p_2");
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_remove_alias("get_key_alias_list_p_3");
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_key_alias_list_n
 * @since_tizen     2.3
 * @description     Check an error in get a key alias list.
 * @scenario        Try to get a key with a NULL parameter.
 */
int utc_ckmc_get_key_alias_list_n(void)
{
    int temp;

    // check CKMC_ERROR_INVALID_PARAMETER
    temp = ckmc_get_key_alias_list(NULL);
    assert_eq(temp,CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_ckmc_save_cert_p
 * @since_tizen     2.3
 * @type            auto
 * @description     Store a certificate
 * @scenario        Store a certificate with its alias, a certificate object and store policy
 * @apicovered      ckmc_save_cert
 * @passcase        When ckmc_save_cert is successful
 * @failcase        If target API fails.
 * @precondition    None
 * @postcondition   None
 */
int utc_ckmc_save_cert_p(void)
{
    int temp;

    ckmc_cert_s cert;
    ckmc_policy_s test_policy;

    char* alias = "save_cert_p";
    char* policy_password = NULL;

    test_policy.password = policy_password;
    test_policy.extractable = true;

    cert.raw_cert =  (unsigned char *)CERT_PEM;
    cert.cert_size = strlen(CERT_PEM);
    cert.data_format = CKMC_FORM_PEM;

    temp = ckmc_save_cert(alias, cert, test_policy);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_remove_alias(alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_save_cert_n
 * @since_tizen     2.3
 * @description     Check an error in storing a certificate.
 * @scenario        Try to store a key with a NULL alias .
 */
int utc_ckmc_save_cert_n(void)
{
    int temp;

    ckmc_cert_s cert;
    ckmc_policy_s test_policy;

    char* alias = NULL;
    char* policy_password = NULL;
    test_policy.password = policy_password;
    test_policy.extractable = true;

    cert.raw_cert =  (unsigned char *)CERT_PEM;
    cert.cert_size = strlen(CERT_PEM);
    cert.data_format = CKMC_FORM_PEM;

    // check CKMC_ERROR_INVALID_PARAMETER
    temp = ckmc_save_cert(alias, cert, test_policy);
    assert_eq(temp,CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_ckmc_remove_cert_p
 * @since_tizen     2.3
 * @description     Remove a certificate
 * @scenario        Store a certificate and remove it with its alias.
 */
int utc_ckmc_remove_cert_p(void)
{
    int temp;

    ckmc_cert_s cert;
    ckmc_policy_s test_policy;

    char* alias = "remove_cert_p";
    char* policy_password = NULL;

    test_policy.password = policy_password;
    test_policy.extractable = true;

    cert.raw_cert =  (unsigned char *)CERT_PEM;
    cert.cert_size = strlen(CERT_PEM);
    cert.data_format = CKMC_FORM_PEM;

    temp = ckmc_save_cert(alias, cert, test_policy);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_remove_cert(alias);
    assert_eq(temp,CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_remove_cert_n
 * @since_tizen     2.3
 * @description     Check an error in removing a certificate.
 * @scenario        Try to remove a certificate with a wrong alias.
                    Try to remove a certificate with a NULL alias.
 */
int utc_ckmc_remove_cert_n(void)
{
    int temp;
    char* wrong_alias = NULL;
    char* unKnown_alias = "remove_cert_n";

    // check CKMC_ERROR_INVALID_PARAMETER
    temp = ckmc_remove_cert(wrong_alias);
    assert_eq(temp,CKMC_ERROR_INVALID_PARAMETER);

    // check CKMC_ERROR_DB_ALIAS_UNKNOWN
    temp = ckmc_remove_cert(unKnown_alias);
    assert_eq(temp,CKMC_ERROR_DB_ALIAS_UNKNOWN);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_cert_p
 * @since_tizen     2.3
 * @description     Get a certificate from DB
 * @scenario        Store a certificate and get it with its alias.
 */
int utc_ckmc_get_cert_p(void)
{
    int temp;

    ckmc_cert_s cert;
    ckmc_cert_s *cert2;
    ckmc_policy_s test_policy;

    char* alias = "get_cert_p";
    char* policy_password = NULL;

    test_policy.password = policy_password;
    test_policy.extractable = true;

    cert.raw_cert =  (unsigned char *)CERT_PEM;
    cert.cert_size = strlen(CERT_PEM);
    cert.data_format = CKMC_FORM_PEM;

    temp = ckmc_save_cert(alias, cert, test_policy);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_get_cert(alias,policy_password,&cert2);
    assert_eq(temp,CKMC_ERROR_NONE);

    ckmc_cert_free(cert2);

    temp = ckmc_remove_alias(alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_cert_n
 * @since_tizen     2.3
 * @description     Check an error in getting a certificate.
 * @scenario        Try to remove a certificate with a NULL alias.
 */
int utc_ckmc_get_cert_n(void)
{
    int temp;
    char* password = NULL;
    char* wrong_alias = NULL;
    ckmc_cert_s *cert;

    temp = ckmc_get_cert(wrong_alias, password, &cert);
    assert_eq(temp,CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_cert_n2
 * @since_tizen     2.3
 * @description     Check an error in getting a certificate.
 * @scenario        Try to remove a certificate with a wrong alias.
 */
int utc_ckmc_get_cert_n2(void)
{
    int temp;
    char* password = NULL;
    char* alias = "get_cert_n2";
    ckmc_cert_s *cert;

    temp = ckmc_get_cert(alias, password, &cert);
    assert_eq(temp,CKMC_ERROR_DB_ALIAS_UNKNOWN);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_cert_n3
 * @since_tizen     2.3
 * @description     Check an error in removing a certificate.
 * @scenario        Store a certificate with extractable = false option.
                    Try to get a certificate with its alias.
 */
int utc_ckmc_get_cert_n3(void)
{
    int temp;

    ckmc_cert_s cert;
    ckmc_cert_s *cert2;
    ckmc_policy_s test_policy;

    char* alias = "get_cert_n3";
    char* policy_password = NULL;

    test_policy.password = policy_password;
    test_policy.extractable = false;

    cert.raw_cert =  (unsigned char *)CERT_PEM;
    cert.cert_size = strlen(CERT_PEM);
    cert.data_format = CKMC_FORM_PEM;

    temp = ckmc_save_cert(alias, cert, test_policy);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_get_cert(alias,policy_password,&cert2);
    assert_eq(temp,CKMC_ERROR_NOT_EXPORTABLE);

    temp = ckmc_remove_alias(alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_cert_alias_list_p
 * @since_tizen     2.3
 * @description     Get a alias list of certificates from DB
 * @scenario        Get a alias list of certificates with a 0 sized list.
                    Stores several certificates.
                    Get a alias list of keys with aliases of stored keys
 */
int utc_ckmc_get_cert_alias_list_p(void)
{
    int temp;

    ckmc_cert_s cert;
    ckmc_policy_s test_policy;

    char* policy_password = NULL;
    int cnt1 = 0;
    int cnt2 = 0;
    ckmc_alias_list_s *aliasList = NULL;
    ckmc_alias_list_s *aliasNext = NULL;

    temp = ckmc_get_cert_alias_list(&aliasList);
    if (temp ==  CKMC_ERROR_NONE) {
        // key-manager has cert
        aliasNext = aliasList;
        while (aliasNext) {
            aliasNext = aliasNext->next;
            cnt1++;
        }
        ckmc_alias_list_all_free(aliasList);
    }
    else if (temp == CKMC_ERROR_DB_ALIAS_UNKNOWN) {
        // key-manager has no cert
        cnt1 = 0;
    }
    else {
        // error.
        assert_eq(1, 0);
    }

    test_policy.password = policy_password;
    test_policy.extractable = true;

    cert.raw_cert =  (unsigned char *)CERT_PEM;
    cert.cert_size = strlen(CERT_PEM);
    cert.data_format = CKMC_FORM_PEM;

    temp = ckmc_save_cert("get_cert_alias_list_p_1", cert, test_policy);
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_save_cert("get_cert_alias_list_p_2", cert, test_policy);
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_save_cert("get_cert_alias_list_p_3", cert, test_policy);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_get_cert_alias_list(&aliasList);
    assert_eq(temp, CKMC_ERROR_NONE);

    aliasNext = aliasList;
    while (aliasNext) {
        aliasNext = aliasNext->next;
        cnt2++;
    }
    ckmc_alias_list_all_free(aliasList);

    assert_eq((cnt2 - cnt1), 3);

    temp = ckmc_remove_alias("get_cert_alias_list_p_1");
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_remove_alias("get_cert_alias_list_p_2");
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_remove_alias("get_cert_alias_list_p_3");
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_cert_alias_list_n
 * @since_tizen     2.3
 * @description     Check an error in get a certificate alias list.
 * @scenario        Try to get a certificate with a NULL parameter.
 */
int utc_ckmc_get_cert_alias_list_n(void)
{
    int temp;

    temp = ckmc_get_cert_alias_list(NULL);
    assert_eq(temp,CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_ckmc_save_data_p
 * @since_tizen     2.3
 * @description     Store a data
 * @scenario        Store a data with its alias, a data object and store policy
 */
int utc_ckmc_save_data_p(void)
{
    int temp;
    char* policy_password = NULL;
    char* bin_data = "My bin data";
    char* alias = "save_data_p";
    ckmc_raw_buffer_s test_data;
    ckmc_policy_s test_policy;

    test_data.data = (unsigned char *) bin_data;
    test_data.size = strlen(bin_data);

    test_policy.password = policy_password;
    test_policy.extractable = true;

    temp = ckmc_save_data(alias, test_data, test_policy);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_remove_alias(alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_save_data_n
 * @since_tizen     2.3
 * @description     Check an error in storing a data.
 * @scenario        Try to store a data with a NULL alias .
 */
int utc_ckmc_save_data_n(void)
{
    int temp;
    char* policy_password = NULL;
    char* bin_data = "My bin data";
    char* alias = NULL;
    ckmc_raw_buffer_s test_data;
    ckmc_policy_s test_policy;

    test_data.data = (unsigned char *) bin_data;
    test_data.size = strlen(bin_data);

    test_policy.password = policy_password;
    test_policy.extractable = true;

    temp = ckmc_save_data(alias, test_data, test_policy);
    assert_eq(temp,CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase        utc_ckmc_remove_data_p
 * @since_tizen     2.3
 * @description     Remove a data
 * @scenario        Store a data and remove it with its alias.
 */
int utc_ckmc_remove_data_p(void)
{
    int temp;
    char* policy_password = NULL;
    char* bin_data = "My bin data";
    char* alias = "remove_data_p";
    ckmc_raw_buffer_s test_data;
    ckmc_policy_s test_policy;

    test_data.data = (unsigned char *) bin_data;
    test_data.size = strlen(bin_data);

    test_policy.password = policy_password;
    test_policy.extractable = true;

    temp = ckmc_save_data(alias, test_data, test_policy);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_remove_data(alias);
    assert_eq(temp,CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_remove_data_n
 * @since_tizen     2.3
 * @description     Check an error in removing a data.
 * @scenario        Try to remove a data with a NULL alias.
 */
int utc_ckmc_remove_data_n(void)
{
    int temp = ckmc_remove_data(NULL);
    assert_eq(temp, CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_ckmc_remove_data_n2
 * @since_tizen     2.3
 * @description     Check an error in removing a data.
 * @scenario        Try to remove a data with a wrong alias.
 */
int utc_ckmc_remove_data_n2(void)
{
    int temp;
    char* alias = "remove_dadta_n2";

    temp = ckmc_remove_data(alias);
    assert_eq(temp,CKMC_ERROR_DB_ALIAS_UNKNOWN);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_data_p
 * @since_tizen     2.3
 * @description     Get a data from DB
 * @scenario        Store a data and get it with its alias.
 */
int utc_ckmc_get_data_p(void)
{
    int temp;
    char* policy_password = NULL;
    char* bin_data = "My bin data";
    char* alias = "get_data_p";
    ckmc_raw_buffer_s test_data;
    ckmc_raw_buffer_s *recv_data;
    ckmc_policy_s test_policy;

    test_data.data = (unsigned char *) bin_data;
    test_data.size = strlen(bin_data);

    test_policy.password = policy_password;
    test_policy.extractable = true;

    temp = ckmc_save_data(alias, test_data, test_policy);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_get_data(alias, policy_password, &recv_data);
    assert_eq(temp,CKMC_ERROR_NONE);

    ckmc_buffer_free(recv_data);

    temp = ckmc_remove_alias(alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_data_n
 * @since_tizen     2.3
 * @description     Check an error in getting a data.
 * @scenario        Try to get a data with a NULL alias.
 */
int utc_ckmc_get_data_n(void)
{
    int temp;
    char* policy_password = NULL;
    char* alias = NULL;
    ckmc_raw_buffer_s *recv_data;

    temp = ckmc_get_data(alias, policy_password, &recv_data);
    assert_eq(temp,CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_data_n2
 * @since_tizen     2.3
 * @description     Check an error in getting a data.
 * @scenario        Try to get a data with a wrong alias.
 */
int utc_ckmc_get_data_n2(void)
{
    int temp;
    char* policy_password = NULL;
    char* alias = "get_data_n2";

    ckmc_raw_buffer_s *recv_data;

    temp = ckmc_get_data(alias, policy_password, &recv_data);
    assert_eq(temp,CKMC_ERROR_DB_ALIAS_UNKNOWN);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_data_alias_list_p
 * @since_tizen     2.3
 * @description     Get a alias list of data from DB
 * @scenario        Get a alias list of data with a 0 sized list.
                    Stores several data.
                    Get a alias list of data with aliases of stored data
 */
int utc_ckmc_get_data_alias_list_p(void)
{
    int temp;

    ckmc_raw_buffer_s test_data;
    ckmc_policy_s test_policy;
    char* bin_data = "My bin data";

    char* policy_password = NULL;
    int cnt1 = 0;
    int cnt2 = 0;
    ckmc_alias_list_s *aliasList = NULL;
    ckmc_alias_list_s *aliasNext = NULL;

    temp = ckmc_get_data_alias_list(&aliasList);
    if (temp == CKMC_ERROR_NONE) {
        // key-manager has data
        aliasNext = aliasList;
        while (aliasNext) {
            aliasNext = aliasNext->next;
            cnt1++;
        }
        ckmc_alias_list_all_free(aliasList);
    }
    else if (temp == CKMC_ERROR_DB_ALIAS_UNKNOWN) {
        // key-manager has no data
        cnt1 = 0;
    }
    else {
        // error.
        assert_eq(1, 0);
    }

    test_data.data = (unsigned char *) bin_data;
    test_data.size = strlen(bin_data);

    test_policy.password = policy_password;
    test_policy.extractable = true;

    temp = ckmc_save_data("get_data_alias_list_p_1", test_data, test_policy);
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_save_data("get_data_alias_list_p_2", test_data, test_policy);
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_save_data("get_data_alias_list_p_3", test_data, test_policy);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_get_data_alias_list(&aliasList);
    assert_eq(temp, CKMC_ERROR_NONE);

    aliasNext = aliasList;
    while (aliasNext) {
        aliasNext = aliasNext->next;
        cnt2++;
    }
    ckmc_alias_list_all_free(aliasList);

    assert_eq((cnt2 - cnt1), 3);

    temp = ckmc_remove_alias("get_data_alias_list_p_1");
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_remove_alias("get_data_alias_list_p_2");
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_remove_alias("get_data_alias_list_p_3");
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_data_alias_list_n
 * @since_tizen     2.3
 * @description     Check an error in get a data alias list.
 * @scenario        Try to get a data with a NULL parameter.
 */
int utc_ckmc_get_data_alias_list_n(void)
{
    int temp = ckmc_get_data_alias_list(NULL);
    assert_eq(temp, CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase        utc_ckmc_save_pkcs12_p
 * @since_tizen     2.4
 * @description     Store a pkcs12 data from a key and certifcates
 * @scenario        Load a key and certificates from a pkcs12 file.
                    Store a pkcs12 data with its alias
 */
int utc_ckmc_save_pkcs12_p(void)
{
    int temp;
    ckmc_pkcs12_s *ppkcs12 = NULL;
    char *alias_PKCS_exportable = "save_pkcs12_p";
    ckmc_policy_s key_policy;
    ckmc_policy_s cert_policy;

    key_policy.password = NULL;
    key_policy.extractable = true;
    cert_policy.password = NULL;
    cert_policy.extractable = true;

    char p12_path[PATH_LEN] = {0, };
    append_to_app_data_path("pkcs.p12", p12_path, sizeof(p12_path));
    temp = ckmc_pkcs12_load(p12_path, NULL, &ppkcs12);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_save_pkcs12(
            alias_PKCS_exportable,
            ppkcs12,
            key_policy,
            cert_policy);
    assert_eq(temp, CKMC_ERROR_NONE);

    ckmc_pkcs12_free(ppkcs12);

    temp = ckmc_remove_alias(alias_PKCS_exportable);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}


/**
 * @testcase        utc_ckmc_save_pkcs12_n
 * @since_tizen     2.4
 * @description     Check an error in storing a pkcs12 data.
 * @scenario        Try to store a pkcs12 data with a NULL alias .
 */
int utc_ckmc_save_pkcs12_n(void)
{
    int temp;
    ckmc_pkcs12_s *ppkcs12 = NULL;
    char *alias_PKCS_exportable = NULL;
    ckmc_policy_s key_policy;
    ckmc_policy_s cert_policy;

    key_policy.password = NULL;
    key_policy.extractable = true;
    cert_policy.password = NULL;
    cert_policy.extractable = true;

    char p12_path[PATH_LEN] = {0, };
    append_to_app_data_path("pkcs.p12", p12_path, sizeof(p12_path));
    temp = ckmc_pkcs12_load(p12_path, NULL, &ppkcs12);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_save_pkcs12(
            alias_PKCS_exportable,
            ppkcs12,
            key_policy,
            cert_policy);
    assert_eq(temp, CKMC_ERROR_INVALID_PARAMETER);

    ckmc_pkcs12_free(ppkcs12);

    return 0;
}


/**
 * @testcase        utc_ckmc_get_pkcs12_p
 * @since_tizen     2.4
 * @description     Get a pkcs12 data from DB
 * @scenario        Load a key and certifcates from a file and store them as a pkcs12
                    Get it with its alias.
 */
int utc_ckmc_get_pkcs12_p(void)
{
    int temp;
    ckmc_pkcs12_s *ppkcs12 = NULL;
    char *alias_PKCS_exportable = "get_pkcs12_p";
    ckmc_policy_s key_policy;
    ckmc_policy_s cert_policy;

    key_policy.password = NULL;
    key_policy.extractable = true;
    cert_policy.password = NULL;
    cert_policy.extractable = true;

    char p12_path[PATH_LEN] = {0, };
    append_to_app_data_path("pkcs.p12", p12_path, sizeof(p12_path));
    temp = ckmc_pkcs12_load(p12_path, NULL, &ppkcs12);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_save_pkcs12(
            alias_PKCS_exportable,
            ppkcs12,
            key_policy,
            cert_policy);
    assert_eq(temp, CKMC_ERROR_NONE);

    ckmc_pkcs12_free(ppkcs12);

    temp = ckmc_get_pkcs12(
            alias_PKCS_exportable,
            key_policy.password,
            cert_policy.password,
            &ppkcs12);
    assert_eq(temp, CKMC_ERROR_NONE);

    ckmc_pkcs12_free(ppkcs12);

    temp = ckmc_remove_alias(alias_PKCS_exportable);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}


/**
 * @testcase        utc_ckmc_get_pkcs12_n
 * @since_tizen     2.4
 * @description     Check an error in getting a pkcs12 data.
 * @scenario        Try to remove a pkcs12 data with NULL parameters.
 */
int utc_ckmc_get_pkcs12_n(void)
{
    int temp;
    ckmc_pkcs12_s *ppkcs12 = NULL;

    temp = ckmc_get_pkcs12(NULL, NULL, NULL, &ppkcs12);
    assert_eq(temp, CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_ckmc_remove_alias_p
 * @since_tizen     2.4
 * @description     Remove a key, a certificat or data with its alias.
 * @scenario        Store a data and remove it with its alias.
 */
int utc_ckmc_remove_alias_p(void)
{
   int temp;
   char* policy_password = NULL;
   char* bin_data = "My bin data";
   char* alias = "utc_ckmc_remove_alias_p";
   ckmc_raw_buffer_s test_data;
   ckmc_policy_s test_policy;

   test_data.data = (unsigned char *) bin_data;
   test_data.size = strlen(bin_data);
   test_policy.password = policy_password;
   test_policy.extractable = true;

   temp = ckmc_save_data(alias, test_data, test_policy);
   assert_eq(temp,CKMC_ERROR_NONE);

   temp = ckmc_remove_alias(alias);
   assert_eq(temp,CKMC_ERROR_NONE);

   return 0;
}

/**
 * @testcase        utc_ckmc_remove_alias_n
 * @since_tizen     2.4
 * @description     Check an error in removing a key, a certificat or data with its alias.
 * @scenario        Try to remove a data with a NULL alias.
 */
int utc_ckmc_remove_alias_n(void)
{
   int temp = ckmc_remove_alias(NULL);
   assert_eq(temp, CKMC_ERROR_INVALID_PARAMETER);

   return 0;
}

/**
 * @testcase        utc_ckmc_set_permission_p
 * @since_tizen     2.4
 * @description     Set access permission of a key, certificate, or data.
 * @scenario        Store a data and set its access permission.
 */
int utc_ckmc_set_permission_p(void)
{
    int temp;
    char* policy_password = NULL;
    char* bin_data = "My bin data";
    char* alias = "save_data";
    ckmc_raw_buffer_s test_data;
    ckmc_policy_s test_policy;
    const char * accessor = "test-label2";

    test_data.data = (unsigned char *) bin_data;
    test_data.size = strlen(bin_data);

    test_policy.password = policy_password;
    test_policy.extractable = true;

    temp = ckmc_save_data(alias, test_data, test_policy);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_set_permission(alias, accessor, CKMC_PERMISSION_READ);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_remove_alias(alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}


/**
 * @testcase        utc_ckmc_set_permission_n
 * @since_tizen     2.4
 * @description     Check an error in setting permission
 * @scenario        Try to set permission with a NULL alias.
 */
int utc_ckmc_set_permission_n(void)
{
    int temp;
    char* alias = NULL;
    const char* accessor = "test-label2";

    temp = ckmc_set_permission(alias, accessor, CKMC_PERMISSION_READ);
    assert_neq(temp,CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_allow_access_p
 * @since_tizen     2.3
 * @description     Allow access for READ on a key, certificate, or data.
 * @scenario        Store a data and allow access on it.
 */
int utc_ckmc_allow_access_p(void)
{
    int temp;
    const char *alias = "allow_access_p";
    const char *accessor = "allow_access_p_to";
    ckmc_access_right_e granted = CKMC_AR_READ;

    // for saving data to share
    char *policy_password = NULL;
    char *bin_data = "My bin data";
    ckmc_raw_buffer_s test_data;
    ckmc_policy_s test_policy;

    test_data.data = (unsigned char *) bin_data;
    test_data.size = strlen(bin_data);
    test_policy.password = policy_password;
    test_policy.extractable = true;

    temp = ckmc_save_data(alias, test_data, test_policy);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_allow_access(alias, accessor, granted);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_remove_alias(alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_allow_access_p2
 * @since_tizen     2.3
 * @description     Allow access of READ_REMOVE on a key, certificate, or data.
 * @scenario        Store a data and allow access on it.
 */
int utc_ckmc_allow_access_p2(void)
{
    int temp;
    const char *alias = "allow_access_p2";
    const char *accessor = "allow_access_p2_to";
    ckmc_access_right_e granted = CKMC_AR_READ_REMOVE;

    // for saving data to share
    char *policy_password = NULL;
    char *bin_data = "My bin data";
    ckmc_raw_buffer_s test_data;
    ckmc_policy_s test_policy;

    test_data.data = (unsigned char *) bin_data;
    test_data.size = strlen(bin_data);
    test_policy.password = policy_password;
    test_policy.extractable = true;

    temp = ckmc_save_data(alias, test_data, test_policy);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_allow_access(alias, accessor, granted);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_remove_alias(alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_allow_access_n
 * @since_tizen     2.3
 * @description     Check an error in allowing access
 * @scenario        Try to allow access with  NULL aliases.
 */
int utc_ckmc_allow_access_n(void)
{
    int temp;

    temp = ckmc_allow_access(NULL, NULL, CKMC_AR_READ);
    assert_eq(temp, CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_ckmc_allow_access_n2
 * @since_tizen     2.3
 * @description     Check an error in allowing access
 * @scenario        Try to allow access with  a wroing alias.
 */
int utc_ckmc_allow_access_n2(void)
{
    int temp;
    const char *alias = "allow_access_n2";
    const char *wrong_alias = "qwerasdfzxcv";
    const char *accessor = "allow_access_n2_to";
    ckmc_access_right_e granted = CKMC_AR_READ;

    // for saving data to share
    char *policy_password = NULL;
    char *bin_data = "My bin data";
    ckmc_raw_buffer_s test_data;
    ckmc_policy_s test_policy;

    test_data.data = (unsigned char *) bin_data;
    test_data.size = strlen(bin_data);
    test_policy.password = policy_password;
    test_policy.extractable = true;

    temp = ckmc_save_data(alias, test_data, test_policy);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_allow_access(wrong_alias, accessor, granted);
    assert_eq(temp, CKMC_ERROR_DB_ALIAS_UNKNOWN);

    temp = ckmc_remove_alias(alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_deny_access_p
 * @since_tizen     2.3
 * @description     Deny access on a key, certificate, or data.
 * @scenario        Store a data and allow access on it.
                    Deny access of READ on it.
 */
int utc_ckmc_deny_access_p(void)
{
    int temp;
    const char *alias = "deny_access_p";
    const char *accessor = "deny_access_p_to";
    ckmc_access_right_e granted = CKMC_AR_READ;

    // for saving data to share
    char *policy_password = NULL;
    char *bin_data = "My bin data";
    ckmc_raw_buffer_s test_data;
    ckmc_policy_s test_policy;

    test_data.data = (unsigned char *) bin_data;
    test_data.size = strlen(bin_data);
    test_policy.password = policy_password;
    test_policy.extractable = true;

    temp = ckmc_save_data(alias, test_data, test_policy);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_allow_access(alias, accessor, granted);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_deny_access(alias, accessor);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_remove_alias(alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_deny_access_p2
 * @since_tizen     2.3
 * @description     Deny access on a key, certificate, or data.
 * @scenario        Store a data and allow access of READ_REMOVE on it.
                    Deny access on it.
 */
int utc_ckmc_deny_access_p2(void)
{
    int temp;
    const char *alias = "deny_access_p2";
    const char *accessor = "deny_access_p2_to";
    ckmc_access_right_e granted = CKMC_AR_READ_REMOVE;

    // for saving data to share
    char *policy_password = NULL;
    char *bin_data = "My bin data";
    ckmc_raw_buffer_s test_data;
    ckmc_policy_s test_policy;

    test_data.data = (unsigned char *) bin_data;
    test_data.size = strlen(bin_data);
    test_policy.password = policy_password;
    test_policy.extractable = true;

    temp = ckmc_save_data(alias, test_data, test_policy);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_allow_access(alias, accessor, granted);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_deny_access(alias, accessor);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_remove_alias(alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_deny_access_p3
 * @since_tizen     3.0
 * @description     Check if we can remove access which was not granted
 * @scenario        Store a data
                    Try to deny access on it without allowing access.
 */
int utc_ckmc_deny_access_p3(void)
{
    int temp;
    const char *alias = "deny_access_p3";
    const char *accessor = "deny_access_p3_to";

    // for saving data to share
    char *policy_password = NULL;
    char *bin_data = "My bin data";
    ckmc_raw_buffer_s test_data;
    ckmc_policy_s test_policy;

    test_data.data = (unsigned char *) bin_data;
    test_data.size = strlen(bin_data);
    test_policy.password = policy_password;
    test_policy.extractable = true;

    temp = ckmc_save_data(alias, test_data, test_policy);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_deny_access(alias, accessor);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_remove_alias(alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}


/**
 * @testcase        utc_ckmc_allow_deny_n
 * @since_tizen     2.3
 * @description     Check an error in denying access
 * @scenario        Try to deny access with a NULL alias.
 */
int utc_ckmc_allow_deny_n(void)
{
    int temp;

    temp = ckmc_deny_access(NULL, NULL);
    assert_eq(temp, CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_ckmc_allow_deny_n2
 * @since_tizen     2.3
 * @description     Check an error in denying access
 * @scenario        Store a data and allow access on it
                    Try to deny access with a wrong alias.
 */
int utc_ckmc_allow_deny_n2(void)
{
    int temp;
    const char *alias = "deny_access_n2";
    const char *wrong_alias = "qwerpoiuasdf";
    const char *accessor = "deny_access_n2_to";
    ckmc_access_right_e granted = CKMC_AR_READ;

    // for saving data to share
    char *policy_password = NULL;
    char *bin_data = "My bin data";
    ckmc_raw_buffer_s test_data;
    ckmc_policy_s test_policy;

    test_data.data = (unsigned char *) bin_data;
    test_data.size = strlen(bin_data);
    test_policy.password = policy_password;
    test_policy.extractable = true;

    temp = ckmc_save_data(alias, test_data, test_policy);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_allow_access(alias, accessor, granted);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_deny_access(wrong_alias, accessor);
    assert_eq(temp, CKMC_ERROR_DB_ALIAS_UNKNOWN);

    temp = ckmc_remove_alias(alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
* @testcase         utc_ckmc_get_key_alias_info_list_p
* @since            5.5
* @scenario         Gets all available key aliases (should return none)
*/
int utc_ckmc_get_key_alias_info_list_p(void)
{
    ckmc_alias_info_list_s* ppalias_list = NULL;

    int retCode = ckmc_get_key_alias_info_list(&ppalias_list);
    ckmc_alias_info_list_all_free(ppalias_list);
    assert_eq(retCode, CKMC_ERROR_DB_ALIAS_UNKNOWN);
    return 0;
}

/**
* @testcase         utc_ckmc_get_key_alias_info_list_p
* @since            5.5
* @scenario         Gets all available key aliases
*/
int utc_ckmc_get_key_alias_info_list_n(void)
{
    int retCode = ckmc_get_key_alias_info_list(NULL);
    assert_eq(retCode, CKMC_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
* @testcase         utc_ckmc_get_cert_alias_info_list_p
* @since            5.5
* @scenario         Gets all available certificate aliases (should return none)
*/
int utc_ckmc_get_cert_alias_info_list_p(void)
{
    ckmc_alias_info_list_s* ppalias_list = NULL;

    int retCode = ckmc_get_cert_alias_info_list(&ppalias_list);
    ckmc_alias_info_list_all_free(ppalias_list);
    assert_eq(retCode, CKMC_ERROR_DB_ALIAS_UNKNOWN);
    return 0;
}

/**
* @testcase         utc_ckmc_get_cert_alias_info_list_p
* @since            5.5
* @scenario         Gets all available certificate aliases
*/
int utc_ckmc_get_cert_alias_info_list_n(void)
{
    int retCode = ckmc_get_cert_alias_info_list(NULL);
    assert_eq(retCode, CKMC_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
* @testcase         utc_ckmc_get_data_alias_info_list_p1
* @since            5.5
* @scenario         Gets all available data aliases (should return none)
*/
int utc_ckmc_get_data_alias_info_list_p1(void)
{
    ckmc_alias_info_list_s* ppalias_list = NULL;

    int retCode = ckmc_get_data_alias_info_list(&ppalias_list);
    ckmc_alias_info_list_all_free(ppalias_list);
    assert_eq(retCode, CKMC_ERROR_DB_ALIAS_UNKNOWN);
    return 0;
}

/**
* @testcase         utc_ckmc_get_data_alias_info_list_p2
* @since            5.5
* @scenario         Gets all available data aliases (should return 1)
*/
int utc_ckmc_get_data_alias_info_list_p2(void)
{
    ckmc_alias_info_list_s* ppalias_list = NULL;

    int retCode;
    char* policy_password = NULL;
    char* bin_data = "My bin data";
    char* alias = "save_data_p";
    ckmc_raw_buffer_s test_data;
    ckmc_policy_s test_policy;

    test_data.data = (unsigned char *) bin_data;
    test_data.size = strlen(bin_data);

    test_policy.password = policy_password;
    test_policy.extractable = true;

    retCode = ckmc_save_data(alias, test_data, test_policy);
    assert_eq(retCode, CKMC_ERROR_NONE);

    retCode = ckmc_get_data_alias_info_list(&ppalias_list);
    assert_eq(retCode, CKMC_ERROR_NONE);
    assert_eq(ppalias_list->next, NULL);

    ckmc_alias_info_list_all_free(ppalias_list);

    retCode = ckmc_remove_alias(alias);
    assert_eq(retCode, CKMC_ERROR_NONE);
    return 0;
}

/**
* @testcase         utc_ckmc_get_data_alias_info_list_p
* @since            5.5
* @scenario         Gets all available data aliases
*/
int utc_ckmc_get_data_alias_info_list_n(void)
{
    int retCode = ckmc_get_data_alias_info_list(NULL);
    assert_eq(retCode, CKMC_ERROR_INVALID_PARAMETER);
    return 0;
}
