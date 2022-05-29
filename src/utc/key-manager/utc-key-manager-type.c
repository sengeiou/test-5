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
#include "tct_common.h"
#include "res-util.h"

#include <ckmc/ckmc-manager.h>
#include <ckmc/ckmc-type.h>
#include <ckmc/ckmc-error.h>

#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <fts.h>
#include <storage.h>

static const char *RSA_PUBKEY =
    "-----BEGIN PUBLIC KEY-----\n"
    "IIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA2b1bXDa+S8/MGWnMkru4\n"
    "T4tUddtZNi0NVjQn9RFH1NMa220GsRhRO56F77FlSVFKfSfVZKIiWg6C+DVCkcLf\n"
    "zXJ/Z0pvwOQYBAqVMFjV6efQGN0JzJ1Unu7pPRiZl7RKGEI+cyzzrcDyrLLrQ2W7\n"
    "0ZySkNEOv6Frx9JgC5NExuYY4lk2fQQa38JXiZkfyzif2em0px7mXbyf5LjccsKq\n"
    "v1e+XLtMsL0ZefRcqsP++NzQAI8fKX7WBT+qK0HJDLiHrKOTWYzx6CwJ66LD/vvf\n"
    "j55xtsKDLVDbsotvf8/m6VLMab+vqKk11TP4tq6yo0mwyTADvgl1zowQEO9I1W6o\n"
    "zQIDAQAB\n"
    "-----END PUBLIC KEY-----";

static const char* RSA_PUB_KEY_PEM2 =
    "-----BEGIN PUBLIC KEY-----\n"
    "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA2b1bXDa+S8/MGWnMkru4\n"
    "T4tUddtZNi0NVjQn9RFH1NMa220GsRhRO56F77FlSVFKfSfVZKIiWg6C+DVCkcLf\n"
    "zXJ/Z0pvwOQYBAqVMFjV6efQGN0JzJ1Unu7pPRiZl7RKGEI+cyzzrcDyrLLrQ2W7\n"
    "0ZySkNEOv6Frx9JgC5NExuYY4lk2fQQa38JXiZkfyzif2em0px7mXbyf5LjccsKq\n"
    "v1e+XLtMsL0ZefRcqsP++NzQAI8fKX7WBT+qK0HJDLiHrKOTWYzx6CwJ66LD/vvf\n"
    "j55xtsKDLVDbsotvf8/m6VLMab+vqKk11TP4tq6yo0mwyTADvgl1zowQEO9I1W6o\n"
    "zQIDAQAB\n"
    "-----END PUBLIC KEY-----";

static const char *RSA_PRIKEY =
    "-----BEGIN RSA PRIVATE KEY-----\n"
    "Proc-Type: 4,ENCRYPTED\n"
    "DEK-Info: DES-EDE3-CBC,6C6507B11671DABC\n"
    "\n"
    "YiKNviNqc/V/i241CKtAVsNckesE0kcaka3VrY7ApXR+Va93YoEwVQ8gB9cE/eHH\n"
    "S0j3ZS1PAVFM/qo4ZnPdMzaSLvTQw0GAL90wWgF3XQ+feMnWyBObEoQdGXE828TB\n"
    "SLz4UOIQ55Dx6JSWTfEhwAlPs2cEWD14xvuxPzAEzBIYmWmBBsCN94YgFeRTzjH0\n"
    "TImoYVMN60GgOfZWw6rXq9RaV5dY0Y6F1piypCLGD35VaXAutdHIDvwUGECPm7SN\n"
    "w05jRro53E1vb4mYlZEY/bs4q7XEOI5+ZKT76Xn0oEJNX1KRL1h2q8fgUkm5j40M\n"
    "uQj71aLR9KyIoQARwGLeRy09tLVjH3fj66CCMqaPcxcIRIyWi5yYBB0s53ipm6A9\n"
    "CYuyc7MS2C0pOdWKsDvYsHR/36KUiIdPuhF4AbaTqqO0eWeuP7Na7dGK56Fl+ooi\n"
    "cUpJr7cIqMl2vL25B0jW7d4TB3zwCEkVVD1fBPeNoZWo30z4bILcBqjjPkQfHZ2e\n"
    "xNraG3qI4FHjoPT8JEE8p+PgwaMoINlICyIMKiCdvwz9yEnsHPy7FkmatpS+jFoS\n"
    "mg8R9vMwgK/HGEm0dmb/7/a0XsG2jCDm6cOmJdZJFQ8JW7hFs3eOHpNlQYDChG2D\n"
    "A1ExslqBtbpicywTZhzFdYU/hxeCr4UqcY27Zmhr4JlBPMyvadWKeOqCamWepjbT\n"
    "T/MhWJbmWgZbI5s5sbpu7cOYubQcUIEsTaQXGx/KEzGo1HLn9tzSeQfP/nqjAD/L\n"
    "T5t1Mb8o4LuV/fGIT33Q3i2FospJMqp2JINNzG18I6Fjo08PTvJ3row40Rb76+lJ\n"
    "wN1IBthgBgsgsOdB6XNc56sV+uq2TACsNNWw+JnFRCkCQgfF/KUrvN+WireWq88B\n"
    "9UPG+Hbans5A6K+y1a+bzfdYnKws7x8wNRyPxb7Vb2t9ZTl5PBorPLVGsjgf9N5X\n"
    "tCdBlfJsUdXot+EOxrIczV5zx0JIB1Y9hrDG07RYkzPuJKxkW7skqeLo8oWGVpaQ\n"
    "LGWvuebky1R75hcSuL3e4QHfjBHPdQ31fScB884tqkbhBAWr2nT9bYEmyT170bno\n"
    "8QkyOSb99xZBX55sLDHs9p61sTJr2C9Lz/KaWQs+3hTkpwSjSRyjEMH2n491qiQX\n"
    "G+kvLEnvtR8sl9zinorj/RfsxyPntAxudfY3qaYUu2QkLvVdfTVUVbxS/Fg8f7B3\n"
    "hEjCtpKgFjPxQuHE3didNOr5xM7mkmLN/QA7yHVgdpE64T5mFgC3JcVRpcR7zBPH\n"
    "3OeXHgjrhDfN8UIX/cq6gNgD8w7O0rhHa3mEXI1xP14ykPcJ7wlRuLm9P3fwx5A2\n"
    "jQrVKJKw1Nzummmspn4VOpJY3LkH4Sxo4e7Soo1l1cxJpzmERwgMF+vGz1L70+DG\n"
    "M0hVrz1PxlOsBBFgcdS4TB91DIs/RcFDqrJ4gOPNKCgBP+rgTXXLFcxUwJfE3lKg\n"
    "Kmpwdne6FuQYX3eyRVAmPgOHbJuRQCh/V4fYo51UxCcEKeKy6UgOPEJlXksWGbH5\n"
    "VFmlytYW6dFKJvjltSmK6L2r+TlyEQoXwTqe4bkfhB2LniDEq28hKQ==\n"
    "-----END RSA PRIVATE KEY-----";

static const char *RSA_PRIKEY_PASS = "1234";


static const char *TEST_ROOT_CA =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIDnzCCAoegAwIBAgIJAMH/ADkC5YSTMA0GCSqGSIb3DQEBBQUAMGYxCzAJBgNV\n"
    "BAYTAkFVMRMwEQYDVQQIDApTb21lLVN0YXRlMQ0wCwYDVQQKDARBQ01FMRAwDgYD\n"
    "VQQLDAdUZXN0aW5nMSEwHwYDVQQDDBhUZXN0IHJvb3QgY2EgY2VydGlmaWNhdGUw\n"
    "HhcNMTQxMjMwMTcyMTUyWhcNMjQxMjI3MTcyMTUyWjBmMQswCQYDVQQGEwJBVTET\n"
    "MBEGA1UECAwKU29tZS1TdGF0ZTENMAsGA1UECgwEQUNNRTEQMA4GA1UECwwHVGVz\n"
    "dGluZzEhMB8GA1UEAwwYVGVzdCByb290IGNhIGNlcnRpZmljYXRlMIIBIjANBgkq\n"
    "hkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA0EJRdUtd2th0vTVF7QxvDKzyFCF3w9vC\n"
    "9IDE/Yr12w+a9jd0s7/eG96qTHIYffS3B7x2MB+d4n+SR3W0qmYh7xk8qfEgH3da\n"
    "eDoV59IZ9r543KM+g8jm6KffYGX1bIJVVY5OhBRbO9nY6byYpd5kbCIUB6dCf7/W\n"
    "rQl1aIdLGFIegAzPGFPXDcU6F192686x54bxt/itMX4agHJ9ZC/rrTBIZghVsjJo\n"
    "5/AH5WZpasv8sfrGiiohAxtieoYoJkv5MOYP4/2lPlOY+Cgw1Yoz+HHv31AllgFs\n"
    "BquBb/kJVmCCNsAOcnvQzTZUsW/TXz9G2nwRdqI1nSy2JvVjZGsqGQIDAQABo1Aw\n"
    "TjAdBgNVHQ4EFgQUt6pkzFt1PZlfYRL/HGnufF4frdwwHwYDVR0jBBgwFoAUt6pk\n"
    "zFt1PZlfYRL/HGnufF4frdwwDAYDVR0TBAUwAwEB/zANBgkqhkiG9w0BAQUFAAOC\n"
    "AQEAld7Qwq0cdzDQ51w1RVLwTR8Oy25PB3rzwEHcSGJmdqlMi3xOdaz80S1R1BBX\n"
    "ldvGBG5Tn0vT7xSuhmSgI2/HnBpy9ocHVOmhtNB4473NieEpfTYrnGXrFxu46Wus\n"
    "9m/ZnugcQ2G6C54A/NFtvgLmaC8uH8M7gKdS6uYUwJFQEofkjmd4UpOYSqmcRXhS\n"
    "Jzd5FYFWkJhKJYp3nlENSOD8CUFFVGekm05nFN2gRVc/qaqQkEX77+XYvhodLRsV\n"
    "qMn7nf7taidDKLO2T4bhujztnTYOhhaXKgPy7AtZ28N2wvX96VyAPB/vrchGmyBK\n"
    "kOg11TpPdNDkhb1J4ZCh2gupDg==\n"
    "-----END CERTIFICATE-----";

static const char *TEST_IM_CA =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIDljCCAn6gAwIBAgICEAAwDQYJKoZIhvcNAQEFBQAwZjELMAkGA1UEBhMCQVUx\n"
    "EzARBgNVBAgMClNvbWUtU3RhdGUxDTALBgNVBAoMBEFDTUUxEDAOBgNVBAsMB1Rl\n"
    "c3RpbmcxITAfBgNVBAMMGFRlc3Qgcm9vdCBjYSBjZXJ0aWZpY2F0ZTAeFw0xNTAx\n"
    "MTYxNjQ1MzRaFw0zNTAxMTExNjQ1MzRaMGQxCzAJBgNVBAYTAkFVMRMwEQYDVQQI\n"
    "DApTb21lLVN0YXRlMQ0wCwYDVQQKDARBQ01FMRAwDgYDVQQLDAdUZXN0aW5nMR8w\n"
    "HQYDVQQDDBZUZXN0IElNIENBIGNlcnRpZmljYXRlMIIBIjANBgkqhkiG9w0BAQEF\n"
    "AAOCAQ8AMIIBCgKCAQEAzmBF78qClgoKfnLAncMXZwZ14TW+5kags1+QCYeg3c7j\n"
    "L9+RvDxIaX2tKf1sukJcwQfYqUlQkwt+58LMOb2ORtkpj8Or6WCWCZ0BzneT8ug7\n"
    "nxJT4m9+bohMF0JoKjjB2H4KNMHamLIwUxRKt6nyfk81kVhJOi2vzzxd+UCPi6Pc\n"
    "UAbJNH48eNgOIg55nyFovVzYj8GIo/9GvHJj83PPa/KlJZ+Z1qZASZZ/VYorplVT\n"
    "thsHXKfejhFy5YJ9t7n/vyAQsyBsagZsvX19xnH41fbYXHKf8UbXG23rNaZlchs6\n"
    "XJVLQdzOpj3WTj/lCocVHqLaZISLhNQ3aI7kUBUdiwIDAQABo1AwTjAdBgNVHQ4E\n"
    "FgQUoCYNaCBP4jl/3SYQuK8Ka+6i3QEwHwYDVR0jBBgwFoAUt6pkzFt1PZlfYRL/\n"
    "HGnufF4frdwwDAYDVR0TBAUwAwEB/zANBgkqhkiG9w0BAQUFAAOCAQEAjRzWiD97\n"
    "Htv4Kxpm3P+C+xP9AEteCJfO+7p8MWgtWEJOknJyt55zeKS2JwZIq57KcbqD8U7v\n"
    "vAUx1ymtUhlFPFd7J1mJ3pou+3aFYmGShYhGHpbrmUwjp7HVP588jrW1NoZVHdMc\n"
    "4OgJWFrViXeu9+maIcekjMB/+9Y0dUgQuK5ZuT5H/Jwet7Th/o9uufTUZjBzRvrB\n"
    "pbXgQpqgME2av4Q/6LuldPCTHLtWXgFUU2R+yCGmuGilvhFJnKoQryAbYnIQNWE8\n"
    "SLoHQ9s1i7Zyb7HU6UAaqMOz15LBkyAqtNyJcO2p7Q/p5YK0xfD4xisI5qXucqVm\n"
    "F2obL5qJSTN/RQ==\n"
    "-----END CERTIFICATE-----";

static const char *TEST_LEAF_CERT =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIDOzCCAiMCAQEwDQYJKoZIhvcNAQEFBQAwZDELMAkGA1UEBhMCQVUxEzARBgNV\n"
    "BAgMClNvbWUtU3RhdGUxDTALBgNVBAoMBEFDTUUxEDAOBgNVBAsMB1Rlc3Rpbmcx\n"
    "HzAdBgNVBAMMFlRlc3QgSU0gQ0EgY2VydGlmaWNhdGUwHhcNMTUwMTE2MTY0ODE0\n"
    "WhcNMzUwMTExMTY0ODE0WjBjMQswCQYDVQQGEwJBVTETMBEGA1UECAwKU29tZS1T\n"
    "dGF0ZTENMAsGA1UECgwEQUNNRTEQMA4GA1UECwwHVGVzdGluZzEeMBwGA1UEAwwV\n"
    "VGVzdCBsZWFmIGNlcnRpZmljYXRlMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIB\n"
    "CgKCAQEAzTdDIa2tDmRxFnIgiG+mBz8GoSVODs0ImNQGbqj+pLhBOFRH8fsah4Jl\n"
    "z5YF9KwhMVLknnHGFLE/Nb7Ac35kEzhMQMpTRxohW83oxw3eZ8zN/FBoKqg4qHRq\n"
    "QR8kS10YXTgrBR0ex/Vp+OUKEw6h7yL2r4Tpvrn9/qHwsxtLxqWbDIVf1O9b1Lfc\n"
    "bllYMdmV5E62yN5tcwrDP8gvHjFnVeLzrG8wTpc9FR90/0Jkfp5jAJcArOBLrT0E\n"
    "4VRqs+4HuwT8jAwFAmNnc7IYX5qSjtSWkmmHe73K/lzB+OiI0JEc/3eWUTWqwTSk\n"
    "4tNCiQGBKJ39LXPTBBJdzmxVH7CUDQIDAQABMA0GCSqGSIb3DQEBBQUAA4IBAQAp\n"
    "UdDOGu3hNiG+Vn10aQ6B1ZmOj3t+45gUV3sC+y8hB8EK1g4P5Ke9bVDts0T5eOnj\n"
    "CSc+6VoND5O4adI0IFFRFljHNVnvjeosHfUZNnowsmA2ptQBtC1g5ZKRvKXlkC5/\n"
    "i5BGgRqPFA7y9WB9Y05MrJHf3E+Oz/RBsLeeNiNN+rF5X1vYExvGHpo0M0zS0ze9\n"
    "HtC0aOy8ocsTrQkf3ceHTAXx2i8ftoSSD4klojtWFpWMrNQa52F7wB9nU6FfKRuF\n"
    "Zj/T1JkYXKkEwZU6nAR2jdZp3EP9xj3o15V/tyFcXHx6l8NTxn4cJb+Xe4VquQJz\n"
    "6ON7PVe0ABN/AlwVQiFE\n"
    "-----END CERTIFICATE-----";


static char *file1 = "ckm_test_cert";
static char *file2 = "ckm_test_cert_2";
static char *path1 = NULL;
static char *path2 = NULL;


static bool __storage_device_supported_cb(int storage_id, storage_type_e type, storage_state_e state, const char *path, void *user_data)
{
    if(type == STORAGE_TYPE_INTERNAL)
    {
    size_t length = strlen(path) + strlen(file1) + 2;
        path1 = (char*)malloc(length);
        memset(path1, 0x00, length);
        snprintf(path1, length, "%s/%s", path, file1);
    length = strlen(path) + strlen(file2) + 2;
        path2 = (char*)malloc(length);
        memset(path2, 0x00, length);
        snprintf(path2, length, "%s/%s", path, file2);
        return false;
    }
    return true;
}


/**
 * @function		utc_key_manager_type_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_key_manager_type_startup(void)
{
    if(storage_foreach_device_supported(__storage_device_supported_cb, NULL) != STORAGE_ERROR_NONE)
    {
        fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
    }
}

/**
 * @function		utc_key_manager_type_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_key_manager_type_cleanup(void)
{
    if(path1) free(path1);
    if(path2) free(path2);
}

/**
 * @testcase        utc_ckmc_alias_new_p
 * @since_tizen     3.0
 * @description     Creates a new full alias which is a concatenation of owner id and alias.
 * @scenario        Creates a new full alias with system owner id.
 */
int utc_ckmc_alias_new_p(void)
{
    char *full_alias = NULL;
    const char *alias = "ckmc_alias_new_p_alias";

    int ret = ckmc_alias_new(ckmc_owner_id_system, alias, &full_alias);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_neq(full_alias, NULL);

    free(full_alias);

    return 0;
}

/**
 * @testcase        utc_ckmc_alias_new_n
 * @since_tizen     3.0
 * @description     Creates a new full alias which is a concatenation of owner id and alias.
 * @scenario        Creates a new full alias with invalid parameter.
 */
int utc_ckmc_alias_new_n(void)
{
    const char *alias = "ckmc_alias_new_n_alias";

    int ret = ckmc_alias_new(ckmc_owner_id_system, alias, NULL);

    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_ckmc_alias_new_n2
 * @since_tizen     3.0
 * @description     Creates a new full alias which is a concatenation of owner id and alias.
 * @scenario        Creates a new full alias with invalid parameter.
 */
int utc_ckmc_alias_new_n2(void)
{
    char *full_alias = NULL;

    int ret = ckmc_alias_new(ckmc_owner_id_system, NULL, &full_alias);

    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_ckmc_alias_new_n3
 * @since_tizen     3.0
 * @description     Creates a new full alias which is a concatenation of owner id and alias.
 * @scenario        Creates a new full alias with invalid parameter.
 */
int utc_ckmc_alias_new_n3(void)
{
    char *full_alias = NULL;
    const char *alias = "ckmc_alias_new_n_alias";

    int ret = ckmc_alias_new(NULL, alias, &full_alias);

    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase        utc_ckmc_key_new_p
 * @since_tizen     2.3
 * @description     Create a new key object of a public key.
 * @scenario        Create a new key object from a public key binary.
 */
int utc_ckmc_key_new_p(void)
{
    ckmc_key_s *key;

    int ret = ckmc_key_new(
            (unsigned char *)RSA_PUBKEY,
            strlen(RSA_PUBKEY),
            CKMC_KEY_RSA_PUBLIC,
            NULL,
            &key);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(key->key_size, strlen(RSA_PUBKEY));
    assert_eq(key->key_type, CKMC_KEY_RSA_PUBLIC);
    assert_eq(key->password, NULL);

    ret = memcmp(
            key->raw_key,
            RSA_PUBKEY,
            strlen(RSA_PUBKEY));
    assert_eq(ret, 0);

    ckmc_key_free(key);
    return 0;
}

/**
 * @testcase        utc_ckmc_key_new_p2
 * @since_tizen     2.3
 * @description     Create a new key object of a private key.
 * @scenario        Create a new key object from a public key binary.
 */
int utc_ckmc_key_new_p2(void)
{
    ckmc_key_s *key;

    int ret = ckmc_key_new(
            (unsigned char *)RSA_PRIKEY,
            strlen(RSA_PRIKEY),
            CKMC_KEY_RSA_PRIVATE,
            (char *)RSA_PRIKEY_PASS,
            &key);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(key->key_size, strlen(RSA_PRIKEY));
    assert_eq(key->key_type, CKMC_KEY_RSA_PRIVATE);

    ret = memcmp(
            key->raw_key,
            RSA_PRIKEY,
            strlen(RSA_PRIKEY));
    assert_eq(ret, 0);

    ret = memcmp(
            key->password,
            RSA_PRIKEY_PASS,
            strlen(RSA_PRIKEY_PASS));
    assert_eq(ret, 0);

    ckmc_key_free(key);
    return 0;
}

/**
 * @testcase        utc_ckmc_key_new_n
 * @since_tizen     2.3
 * @description     Check an error in creating a key.
 * @scenario        Create a new key object from a wrong key binary.
 */
int utc_ckmc_key_new_n(void)
{
    int ret = ckmc_key_new(
            NULL,
            0,
            CKMC_KEY_NONE,
            NULL,
            NULL);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_ckmc_key_free_p
 * @since_tizen     2.3
 * @description     Free a key object.
 * @scenario        Create a key object and free it.
 */
int utc_ckmc_key_free_p(void)
{
    ckmc_key_s *key;

    int ret = ckmc_key_new(
            (unsigned char *)RSA_PUBKEY,
            strlen(RSA_PUBKEY),
            CKMC_KEY_RSA_PUBLIC,
            NULL,
            &key);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(key->key_size, strlen(RSA_PUBKEY));
    assert_eq(key->password, NULL);

    ret = memcmp(
            key->raw_key,
            RSA_PUBKEY,
            strlen(RSA_PUBKEY));
    assert_eq(ret, 0);

    // returns void
    ckmc_key_free(key);
    return 0;
}

/**
 * @testcase        utc_ckmc_key_free_n
 * @since_tizen     2.3
 * @description     Free a NULL key object.
 * @scenario        Free a key object with a NULL parameter.
 */
int utc_ckmc_key_free_n(void)
{
    // returns void
    ckmc_key_free(NULL);
    return 0;
}

/**
 * @testcase        utc_ckmc_buffer_new_p
 * @since_tizen     2.3
 * @description     Create a new buffer object.
 * @scenario        Create a new buffer object from a binary.
 */
int utc_ckmc_buffer_new_p(void)
{
    ckmc_raw_buffer_s *buff;
    int ret = ckmc_buffer_new(
            (unsigned char *)RSA_PUBKEY,
            strlen(RSA_PUBKEY),
            &buff);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(buff->size, strlen(RSA_PUBKEY));

    ret = memcmp(
            buff->data,
            RSA_PUBKEY,
            strlen(RSA_PUBKEY));
    assert_eq(ret, 0);

    ckmc_buffer_free(buff);
    return 0;
}

/**
 * @testcase        utc_ckmc_buffer_new_n
 * @since_tizen     2.3
 * @description     Check an error in creating a buff.
 * @scenario        Create a new buffer object from NULL.
 */
int utc_ckmc_buffer_new_n(void)
{
    int ret = ckmc_buffer_new(
            NULL,
            0,
            NULL);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_ckmc_buffer_free_p
 * @since_tizen     2.3
 * @description     Check an error in freeing a buff object.
 * @scenario        Create a new buffer object from NULL.
 */
int utc_ckmc_buffer_free_p(void)
{
    ckmc_raw_buffer_s *buff;
    int ret = ckmc_buffer_new(
            (unsigned char *)RSA_PUBKEY,
            strlen(RSA_PUBKEY),
            &buff);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(buff->size, strlen(RSA_PUBKEY));

    ret = memcmp(
            buff->data,
            RSA_PUBKEY,
            strlen(RSA_PUBKEY));
    assert_eq(ret, 0);

    // returns void
    ckmc_buffer_free(buff);
    return 0;
}

/**
 * @testcase        utc_ckmc_buffer_free_n
 * @since_tizen     2.3
 * @description     Free a NULL buffer object.
 * @scenario        Free a buffer object with a NULL parameter.
 */
int utc_ckmc_buffer_free_n(void)
{
    // returns void
    ckmc_buffer_free(NULL);
    return 0;
}

/**
 * @testcase        utc_ckmc_cert_new_p
 * @since_tizen     2.3
 * @description     Create a new certificate object.
 * @scenario        Create a new certificate object from a certificate binary.
 */
int utc_ckmc_cert_new_p(void)
{
    ckmc_cert_s *cert;
    int ret = ckmc_cert_new(
            (unsigned char *)TEST_LEAF_CERT,
            strlen(TEST_LEAF_CERT),
            CKMC_FORM_PEM,
            &cert);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert->cert_size, strlen(TEST_LEAF_CERT));
    assert_eq(cert->data_format, CKMC_FORM_PEM);

    ret = memcmp(
            cert->raw_cert,
            TEST_LEAF_CERT,
            strlen(TEST_LEAF_CERT));
    assert_eq(ret, 0);

    ckmc_cert_free(cert);
    return 0;
}

/**
 * @testcase        utc_ckmc_cert_new_n
 * @since_tizen     2.3
 * @description     Check an error in creating a cert object.
 * @scenario        Create a new certificate object from a wrong certificate binary.
 */
int utc_ckmc_cert_new_n(void)
{
    int ret = ckmc_cert_new(
            NULL,
            0,
            CKMC_FORM_PEM,
            NULL);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_ckmc_cert_free_p
 * @since_tizen     2.3
 * @description     Free a certifcate object.
 * @scenario        Create a certifcate object and free it.
 */
int utc_ckmc_cert_free_p(void)
{
    ckmc_cert_s *cert;
    int ret = ckmc_cert_new(
            (unsigned char *)TEST_LEAF_CERT,
            strlen(TEST_LEAF_CERT),
            CKMC_FORM_PEM,
            &cert);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert->cert_size, strlen(TEST_LEAF_CERT));
    assert_eq(cert->data_format, CKMC_FORM_PEM);

    ret = memcmp(
            cert->raw_cert,
            TEST_LEAF_CERT,
            strlen(TEST_LEAF_CERT));
    assert_eq(ret, 0);

    // returns void
    ckmc_cert_free(cert);
    return 0;
}

/**
 * @testcase        utc_ckmc_cert_free_n
 * @since_tizen     2.3
 * @description     Free a NULL certificate object.
 * @scenario        Free a certificate object with a NULL parameter.
 */
int utc_ckmc_cert_free_n(void)
{
    ckmc_cert_free(NULL);
    return 0;
}

/**
 * @testcase        utc_ckmc_pkcs12_new_p
 * @since_tizen     2.4
 * @description     Create a new pkcs12 object.
 * @scenario        Create a key, certificates and create a new pkcs12 object from them.
 */
int utc_ckmc_pkcs12_new_p(void)
{
    ckmc_key_s *prikey;
    ckmc_cert_s *cert;

    ckmc_cert_list_s *ca_cert_list;
    ckmc_cert_s *cert1;
    ckmc_cert_s *cert2;
    ckmc_cert_list_s *cert_list_previous;
    ckmc_cert_list_s *cert_list_last;

    ckmc_pkcs12_s *pkcs12;

    // new private key
    int ret = ckmc_key_new(
            (unsigned char *)RSA_PRIKEY,
            strlen(RSA_PRIKEY),
            CKMC_KEY_RSA_PRIVATE,
            (char *)RSA_PRIKEY_PASS,
            &prikey);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(prikey->key_size, strlen(RSA_PRIKEY));
    assert_eq(prikey->key_type, CKMC_KEY_RSA_PRIVATE);

    ret = memcmp(
            prikey->raw_key,
            RSA_PRIKEY,
            strlen(RSA_PRIKEY));
    assert_eq(ret, 0);

    ret = memcmp(
            prikey->password,
            RSA_PRIKEY_PASS,
            strlen(RSA_PRIKEY_PASS));
    assert_eq(ret, 0);

    // new cert
    ret = ckmc_cert_new(
            (unsigned char *)TEST_LEAF_CERT,
            strlen(TEST_LEAF_CERT),
            CKMC_FORM_PEM,
            &cert);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert->cert_size, strlen(TEST_LEAF_CERT));
    assert_eq(cert->data_format, CKMC_FORM_PEM);

    ret = memcmp(
            cert->raw_cert,
            TEST_LEAF_CERT,
            strlen(TEST_LEAF_CERT));
    assert_eq(ret, 0);


    // new ca_cert_list

    // new cert1 for ca_cert_list
    ret = ckmc_cert_new(
            (unsigned char *)TEST_IM_CA,
            strlen(TEST_IM_CA),
            CKMC_FORM_PEM,
            &cert1);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert1->cert_size, strlen(TEST_IM_CA));
    assert_eq(cert1->data_format, CKMC_FORM_PEM);

    ret = memcmp(
            cert1->raw_cert,
            TEST_IM_CA,
            strlen(TEST_IM_CA));
    assert_eq(ret, 0);

    // new cert_list for ca_cert_list
    ret = ckmc_cert_list_new(cert1, &ca_cert_list);
    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(ca_cert_list->next, NULL);
    assert_eq(ca_cert_list->cert, cert1);

    cert_list_previous = ca_cert_list;

    // new cert2 for ca_cert_list
    ret = ckmc_cert_new(
            (unsigned char *)TEST_ROOT_CA,
            strlen(TEST_ROOT_CA),
            CKMC_FORM_PEM,
            &cert2);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert2->cert_size, strlen(TEST_ROOT_CA));
    assert_eq(cert2->data_format, CKMC_FORM_PEM);

    ret = memcmp(
            cert2->raw_cert,
            TEST_ROOT_CA,
            strlen(TEST_ROOT_CA));
    assert_eq(ret, 0);

    // add cert to cert_list for ca_cert_list
    ret = ckmc_cert_list_add(
            cert_list_previous,
            cert2,
            &cert_list_last);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert_list_previous->next, cert_list_last);
    assert_eq(cert_list_previous->cert, cert1);
    assert_eq(cert_list_last->next, NULL);
    assert_eq(cert_list_last->cert, cert2);


    // new pkcs12
    ret = ckmc_pkcs12_new(
            prikey,
            cert,
            ca_cert_list,
            &pkcs12);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(pkcs12->priv_key, prikey);
    assert_eq(pkcs12->cert, cert);
    assert_eq(pkcs12->ca_chain, ca_cert_list);

    ckmc_pkcs12_free(pkcs12);
    return 0;
}

/**
 * @testcase        utc_ckmc_pkcs12_new_n
 * @since_tizen     2.4
 * @description     Check an error in creating a pkcs12.
 * @scenario        Create a new pkcs12 object from NULL.
 */
int utc_ckmc_pkcs12_new_n(void)
{
    int ret = ckmc_pkcs12_new(
            NULL,
            NULL,
            NULL,
            NULL);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_ckmc_pkcs12_free_p
 * @since_tizen     2.4
 * @description     Check an error in freeing a pkcs12 object
 * @scenario        Create a new pkcs12 object from NULL.
 */
int utc_ckmc_pkcs12_free_p(void)
{
    ckmc_key_s *prikey;
    ckmc_cert_s *cert;

    ckmc_cert_list_s *ca_cert_list;
    ckmc_cert_s *cert1;
    ckmc_cert_s *cert2;
    ckmc_cert_list_s *cert_list_previous;
    ckmc_cert_list_s *cert_list_last;

    ckmc_pkcs12_s *pkcs12;

    // new private key
    int ret = ckmc_key_new(
            (unsigned char *)RSA_PRIKEY,
            strlen(RSA_PRIKEY),
            CKMC_KEY_RSA_PRIVATE,
            (char *)RSA_PRIKEY_PASS,
            &prikey);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(prikey->key_size, strlen(RSA_PRIKEY));
    assert_eq(prikey->key_type, CKMC_KEY_RSA_PRIVATE);

    ret = memcmp(
            prikey->raw_key,
            RSA_PRIKEY,
            strlen(RSA_PRIKEY));
    assert_eq(ret, 0);

    ret = memcmp(
            prikey->password,
            RSA_PRIKEY_PASS,
            strlen(RSA_PRIKEY_PASS));
    assert_eq(ret, 0);

    // new cert
    ret = ckmc_cert_new(
            (unsigned char *)TEST_LEAF_CERT,
            strlen(TEST_LEAF_CERT),
            CKMC_FORM_PEM,
            &cert);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert->cert_size, strlen(TEST_LEAF_CERT));
    assert_eq(cert->data_format, CKMC_FORM_PEM);

    ret = memcmp(
            cert->raw_cert,
            TEST_LEAF_CERT,
            strlen(TEST_LEAF_CERT));
    assert_eq(ret, 0);


    // new ca_cert_list

    // new cert1 for ca_cert_list
    ret = ckmc_cert_new(
            (unsigned char *)TEST_IM_CA,
            strlen(TEST_IM_CA),
            CKMC_FORM_PEM,
            &cert1);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert1->cert_size, strlen(TEST_IM_CA));
    assert_eq(cert1->data_format, CKMC_FORM_PEM);

    ret = memcmp(
            cert1->raw_cert,
            TEST_IM_CA,
            strlen(TEST_IM_CA));
    assert_eq(ret, 0);

    // new cert_list for ca_cert_list
    ret = ckmc_cert_list_new(cert1, &ca_cert_list);
    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(ca_cert_list->next, NULL);
    assert_eq(ca_cert_list->cert, cert1);

    cert_list_previous = ca_cert_list;

    // new cert2 for ca_cert_list
    ret = ckmc_cert_new(
            (unsigned char *)TEST_ROOT_CA,
            strlen(TEST_ROOT_CA),
            CKMC_FORM_PEM,
            &cert2);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert2->cert_size, strlen(TEST_ROOT_CA));
    assert_eq(cert2->data_format, CKMC_FORM_PEM);

    ret = memcmp(
            cert2->raw_cert,
            TEST_ROOT_CA,
            strlen(TEST_ROOT_CA));
    assert_eq(ret, 0);

    // add cert to cert_list for ca_cert_list
    ret = ckmc_cert_list_add(
            cert_list_previous,
            cert2,
            &cert_list_last);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert_list_previous->next, cert_list_last);
    assert_eq(cert_list_previous->cert, cert1);
    assert_eq(cert_list_last->next, NULL);
    assert_eq(cert_list_last->cert, cert2);

    // new pkcs12
    ret = ckmc_pkcs12_new(
            prikey,
            cert,
            ca_cert_list,
            &pkcs12);
    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(pkcs12->priv_key, prikey);
    assert_eq(pkcs12->cert, cert);
    assert_eq(pkcs12->ca_chain, ca_cert_list);

    // returns void
    ckmc_pkcs12_free(pkcs12);
    return 0;
}

/**
 * @testcase        utc_ckmc_pkcs12_free_n
 * @since_tizen     2.4
 * @description     Free a NULL pkcs12 object.
 * @scenario        Free a pkcs12 object with a NULL parameter.
 */
int utc_ckmc_pkcs12_free_n(void)
{
    // returns void
    ckmc_pkcs12_free(NULL);
    return 0;
}

/**
 * @testcase        utc_ckmc_alias_list_new_p
 * @since_tizen     2.3
 * @description     Create a new alias list object.
 * @scenario        Create a new alias list object with an alias.
 */
int utc_ckmc_alias_list_new_p(void)
{
    const char *ALIAS = "alias";
    ckmc_alias_list_s *alias_list;

    int ret = ckmc_alias_list_new((char *)ALIAS, &alias_list);

    assert_eq(ret, CKMC_ERROR_NONE);
    ret = memcmp(
            alias_list->alias,
            ALIAS,
            strlen(ALIAS));
    assert_eq(ret, 0);

    ckmc_alias_list_free(alias_list);
    return 0;
}

/**
 * @testcase        utc_ckmc_alias_list_new_n
 * @since_tizen     2.3
 * @description     Check an error in creating an alias list object.
 * @scenario        Create a new alias list object from NULL.
 */
int utc_ckmc_alias_list_new_n(void)
{
    int ret = ckmc_alias_list_new(NULL, NULL);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_ckmc_alias_list_add_p
 * @since_tizen     2.3
 * @description     add a new alias to an alias list object.
 * @scenario        Create a new alias list object and add a new alias to it.
 */
int utc_ckmc_alias_list_add_p(void)
{
    const char *ALIAS1 = "alias1";
    const char *ALIAS2 = "alias2";

    ckmc_alias_list_s *alias_list;
    ckmc_alias_list_s *alias_list_previous;
    ckmc_alias_list_s *alias_list_last;

    // new alias_list
    int ret = ckmc_alias_list_new((char *)ALIAS1, &alias_list);

    assert_eq(ret, CKMC_ERROR_NONE);
    ret = memcmp(
            alias_list->alias,
            ALIAS1,
            strlen(ALIAS1));
    assert_eq(ret, 0);

    alias_list_previous = alias_list;

    // add alias_list
    ret = ckmc_alias_list_add(
            alias_list_previous,
            (char *)ALIAS2,
            &alias_list_last);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(alias_list_previous->next, alias_list_last);
    assert_eq(alias_list_last->next, NULL);

    ret = memcmp(
            alias_list_last->alias,
            ALIAS2,
            strlen(ALIAS2));
    assert_eq(ret, 0);

    ckmc_alias_list_free(alias_list);
    return 0;
}

/**
 * @testcase        utc_ckmc_alias_list_add_n
 * @since_tizen     2.3
 * @description     Check an error in adding an alias.
 * @scenario        Add a NULL alias to a NULL alias list.
 */
int utc_ckmc_alias_list_add_n(void)
{
    int ret = ckmc_alias_list_add(NULL, NULL, NULL);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_ckmc_alias_list_free_p
 * @since_tizen     2.3
 * @description     Free only an alias list object itself.
 * @scenario        Create an alias list object and free it.
 */
int utc_ckmc_alias_list_free_p(void)
{
    const char *ALIAS = "alias";
    ckmc_alias_list_s *alias_list;

    int ret = ckmc_alias_list_new((char *)ALIAS, &alias_list);

    assert_eq(ret, CKMC_ERROR_NONE);
    ret = memcmp(
            alias_list->alias,
            ALIAS,
            strlen(ALIAS));
    assert_eq(ret, 0);

    // returns void
    ckmc_alias_list_free(alias_list);
    return 0;
}

/**
 * @testcase        utc_ckmc_alias_list_free_n
 * @since_tizen     2.3
 * @description     Free a NULL alias list object.
 * @scenario        Free an alias list object with a NULL parameter.
 */
int utc_ckmc_alias_list_free_n(void)
{
    // returns void
    ckmc_alias_list_free(NULL);
    return 0;
}

/**
 * @testcase        utc_ckmc_alias_list_all_free_p
 * @since_tizen     2.3
 * @description     Free an alias list object and its aliases in it. .
 * @scenario        Create an alias list object, add an alias to it and free it.
 */
int utc_ckmc_alias_list_all_free_p(void)
{
    ckmc_alias_list_s *alias_list;
    const char *alias_str = "alias";
    char *ALIAS = (char *)malloc(strlen(alias_str) + 1);
    if (ALIAS == NULL)
        return 1;
    int ret;

    strncpy(ALIAS, alias_str, strlen(alias_str) + 1);

    ret = ckmc_alias_list_new(ALIAS, &alias_list);

    if (ret != CKMC_ERROR_NONE) {
        free(ALIAS);
    }

    assert_eq(ret, CKMC_ERROR_NONE);

    ret = memcmp(
            alias_list->alias,
            ALIAS,
            strlen(ALIAS));

    ckmc_alias_list_all_free(alias_list);

    assert_eq(ret, 0);

    return 0;
}

/**
 * @testcase        utc_ckmc_alias_list_all_free_n
 * @since_tizen     2.3
 * @description     Free a NULL alias list object.
 * @scenario        Free an alias list object with a NULL parameter.
 */
int utc_ckmc_alias_list_all_free_n(void)
{
    // returns void
    ckmc_alias_list_all_free(NULL);
    return 0;
}

/**
 * @testcase        utc_ckmc_cert_list_new_p
 * @since_tizen     2.3
 * @description     Create a new certificate list object.
 * @scenario        Create a new certificate list object with an certificate object.
 */
int utc_ckmc_cert_list_new_p(void)
{
    ckmc_cert_s *cert;
    ckmc_cert_list_s *cert_list;

    // new cert
    int ret = ckmc_cert_new(
            (unsigned char *)TEST_LEAF_CERT,
            strlen(TEST_LEAF_CERT),
            CKMC_FORM_PEM,
            &cert);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert->cert_size, strlen(TEST_LEAF_CERT));
    assert_eq(cert->data_format, CKMC_FORM_PEM);

    ret = memcmp(
            cert->raw_cert,
            TEST_LEAF_CERT,
            strlen(TEST_LEAF_CERT));
    assert_eq(ret, 0);

    // new cert_list
    ret = ckmc_cert_list_new(cert, &cert_list);
    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert_list->next, NULL);
    assert_eq(cert_list->cert, cert);

    ckmc_cert_list_all_free(cert_list);
    return 0;
}

/**
 * @testcase        utc_ckmc_cert_list_new_n
 * @since_tizen     2.3
 * @description     Check an error in creating an certificate list object.
 * @scenario        Create a new certificate list object from NULL.
 */
int utc_ckmc_cert_list_new_n(void)
{
    int ret = ckmc_cert_list_new(NULL, NULL);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_ckmc_cert_list_add_p
 * @since_tizen     2.3
 * @description     add a new certificate to an certificate list object.
 * @scenario        Create a new certificate list object and add a new certificate to it.
 */
int utc_ckmc_cert_list_add_p(void)
{
    ckmc_cert_s *cert1;
    ckmc_cert_s *cert2;
    ckmc_cert_list_s *cert_list_previous;
    ckmc_cert_list_s *cert_list_last;

    // new cert1
    int ret = ckmc_cert_new(
            (unsigned char *)TEST_LEAF_CERT,
            strlen(TEST_LEAF_CERT),
            CKMC_FORM_PEM,
            &cert1);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert1->cert_size, strlen(TEST_LEAF_CERT));
    assert_eq(cert1->data_format, CKMC_FORM_PEM);

    ret = memcmp(
            cert1->raw_cert,
            TEST_LEAF_CERT,
            strlen(TEST_LEAF_CERT));
    assert_eq(ret, 0);

    // new cert_list
    ret = ckmc_cert_list_new(cert1, &cert_list_previous);
    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert_list_previous->next, NULL);
    assert_eq(cert_list_previous->cert, cert1);

    // new cert2
    ret = ckmc_cert_new(
            (unsigned char *)TEST_IM_CA,
            strlen(TEST_IM_CA),
            CKMC_FORM_PEM,
            &cert2);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert2->cert_size, strlen(TEST_IM_CA));
    assert_eq(cert2->data_format, CKMC_FORM_PEM);

    ret = memcmp(
            cert2->raw_cert,
            TEST_IM_CA,
            strlen(TEST_IM_CA));
    assert_eq(ret, 0);

    // add cert to cert_list
    ret = ckmc_cert_list_add(
            cert_list_previous,
            cert2,
            &cert_list_last);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert_list_previous->next, cert_list_last);
    assert_eq(cert_list_previous->cert, cert1);
    assert_eq(cert_list_last->next, NULL);
    assert_eq(cert_list_last->cert, cert2);

    ckmc_cert_list_all_free(cert_list_previous);
    return 0;
}

/**
 * @testcase        utc_ckmc_cert_list_add_n
 * @since_tizen     2.3
 * @description     Check an error in adding an alias.
 * @scenario        Add a NULL certificate to a NULL certificate list.
 */
int utc_ckmc_cert_list_add_n(void)
{
    int ret = ckmc_cert_list_add(
            NULL,
            NULL,
            NULL);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_ckmc_cert_list_free_p
 * @since_tizen     2.3
 * @description     Free only an certificate list object itself.
 * @scenario        Create an certificate list object and free it.
 */
int utc_ckmc_cert_list_free_p(void)
{
    ckmc_cert_s *cert;
    ckmc_cert_list_s *cert_list;

    // new cert
    int ret = ckmc_cert_new(
            (unsigned char *)TEST_LEAF_CERT,
            strlen(TEST_LEAF_CERT),
            CKMC_FORM_PEM,
            &cert);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert->cert_size, strlen(TEST_LEAF_CERT));
    assert_eq(cert->data_format, CKMC_FORM_PEM);

    ret = memcmp(
            cert->raw_cert,
            TEST_LEAF_CERT,
            strlen(TEST_LEAF_CERT));
    assert_eq(ret, 0);

    // new cert_list
    ret = ckmc_cert_list_new(cert, &cert_list);
    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert_list->next, NULL);
    assert_eq(cert_list->cert, cert);

    // returns void
    ckmc_cert_list_free(cert_list);
    ckmc_cert_free(cert);
    return 0;
}

/**
 * @testcase        utc_ckmc_cert_list_free_n
 * @since_tizen     2.3
 * @description     Free a NULL certificate list object.
 * @scenario        Free an certificate list object with a NULL parameter.
 */
int utc_ckmc_cert_list_free_n(void)
{
    // returns void
    ckmc_cert_list_free(NULL);
    return 0;
}

/**
 * @testcase        utc_ckmc_cert_list_all_free_p
 * @since_tizen     2.3
 * @description     Free an certificate list object and its certificates in it. .
 * @scenario        Create an certificate list object, add a certificate to it and free it.
 */
int utc_ckmc_cert_list_all_free_p(void)
{
    ckmc_cert_s *cert;
    ckmc_cert_list_s *cert_list;

    // new cert
    int ret = ckmc_cert_new(
            (unsigned char *)TEST_LEAF_CERT,
            strlen(TEST_LEAF_CERT),
            CKMC_FORM_PEM,
            &cert);

    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert->cert_size, strlen(TEST_LEAF_CERT));
    assert_eq(cert->data_format, CKMC_FORM_PEM);

    ret = memcmp(
            cert->raw_cert,
            TEST_LEAF_CERT,
            strlen(TEST_LEAF_CERT));
    assert_eq(ret, 0);

    // new cert_list
    ret = ckmc_cert_list_new(cert, &cert_list);
    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(cert_list->next, NULL);
    assert_eq(cert_list->cert, cert);

    // returns void
    ckmc_cert_list_all_free(cert_list);
    return 0;
}

/**
 * @testcase        utc_ckmc_cert_list_all_free_n
 * @since_tizen     2.3
 * @description     Free a NULL certificate list object.
 * @scenario        Free a certificate list object with a NULL parameter.
 */
int utc_ckmc_cert_list_all_free_n(void)
{
    // returns void
    ckmc_cert_list_all_free(NULL);
    return 0;
}


/**
 * @testcase        utc_ckmc_load_cert_from_file_p
 * @since_tizen     2.3
 * @description     Create a certificate object from a certificate file.
 * @scenario        Create a certificate object with a certificate file path
 */
int utc_ckmc_load_cert_from_file_p(void)
{
    int ret;

    ckmc_cert_s *pcert;

    char cert_path[PATH_LEN] = {0, };
    append_to_app_data_path("cert_for_loadtest.pem", cert_path, sizeof(cert_path));

    ret = ckmc_load_cert_from_file(cert_path, &pcert);
    assert_eq(ret,CKMC_ERROR_NONE);

    ckmc_cert_free(pcert);
    remove(path1);
    return 0;
}

/**
 * @testcase        utc_ckmc_load_cert_from_file_n
 * @since_tizen     2.3
 * @description     Create a certificate object from a wrong certificate file.
 * @scenario        Create a certificate object with a corrupted certificate file path
 */
int utc_ckmc_load_cert_from_file_n(void)
{
    int ret;

    ckmc_cert_s *pcert;

    char cert_path[PATH_LEN] = {0, };
    append_to_app_data_path(
        "invalid_cert_for_loadtest.pem", cert_path, sizeof(cert_path));

    ret = ckmc_load_cert_from_file(cert_path, &pcert);
    assert_eq(ret,CKMC_ERROR_INVALID_FORMAT);

    remove(path2);

    return 0;
}

/**
 * @testcase        utc_ckmc_load_from_pkcs12_file_p
 * @since_tizen     2.3
 * @description     Create a key object, a certificate object, and an certificate list from a pkcs12 file.
 * @scenario        Load a key, a certificate, a certificate list from a file.
                    Save them and remove them to test their validity.
 */
int utc_ckmc_load_from_pkcs12_file_p(void)
{
    const char *password = "password";

    int temp;

    ckmc_key_s *private_key = NULL;
    ckmc_cert_s *cert = NULL;
    ckmc_cert_list_s *ca_cert_list = NULL;

    char p12_path[PATH_LEN] = {0, };
    append_to_app_data_path("p12_for_loadtest.p12", p12_path, sizeof(p12_path));
    temp = ckmc_load_from_pkcs12_file(
        p12_path, password, &private_key, &cert, &ca_cert_list);
    assert_eq(temp,CKMC_ERROR_NONE);

    assert_neq(private_key, NULL);
    assert_neq(cert, NULL);
    assert_neq(ca_cert_list, NULL);

    ckmc_policy_s policy;
    policy.password = NULL;
    policy.extractable = 1;

    const char *pkey_alias = "pkey_alias_p";
    temp = ckmc_save_key(pkey_alias, *private_key, policy);
    assert_eq(temp,CKMC_ERROR_NONE);

    const char *cert_alias = "cert_alias_p";
    temp = ckmc_save_cert(cert_alias, *cert, policy);
    assert_eq(temp,CKMC_ERROR_NONE);

    ckmc_cert_list_s *tmpList = ca_cert_list;
    const char *ca_cert_alias_0 = "ca_cert_alias_0_p";
    temp = ckmc_save_cert(ca_cert_alias_0, *(tmpList->cert), policy);
    assert_eq(temp,CKMC_ERROR_NONE);

    tmpList = tmpList->next;
    const char *ca_cert_alias_1 = "ca_cert_alias_1_p";
    temp = ckmc_save_cert(ca_cert_alias_1, *(tmpList->cert), policy);
    assert_eq(temp,CKMC_ERROR_NONE);

    ckmc_remove_key(pkey_alias);
    ckmc_remove_cert(cert_alias);
    ckmc_remove_cert(ca_cert_alias_0);
    ckmc_remove_cert(ca_cert_alias_1);

    ckmc_key_free(private_key);
    ckmc_cert_free(cert);
    ckmc_cert_list_all_free(ca_cert_list);

    remove(path1);
    remove(path2);

    return 0;
}

/**
 * @testcase        utc_ckmc_load_from_pkcs12_file_n
 * @since_tizen     2.3
 * @description     Load from a wrong pkcs12 file.
 * @scenario        Load with a corrupted pkcs12 file path
 */
int utc_ckmc_load_from_pkcs12_file_n(void)
{
    const char *password = "password";

    int temp;

    ckmc_key_s *private_key = NULL;
    ckmc_cert_s *cert = NULL;
    ckmc_cert_list_s *ca_cert_list = NULL;

    char p12_path[PATH_LEN] = {0, };
    append_to_app_data_path("invalid_p12_for_loadtest.p12", p12_path, sizeof(p12_path));
    temp = ckmc_load_from_pkcs12_file(
        p12_path, password, &private_key, &cert, &ca_cert_list);
    assert_eq(temp,CKMC_ERROR_INVALID_FORMAT);

    return 0;
}

/**
 * @testcase        utc_ckmc_pkcs12_load_p
 * @since_tizen     2.4
 * @description     Create a pkcs12 object from a pkcs12 file.
 * @scenario        Create a pkcs12 object with a pkcs12 file path
 */
int utc_ckmc_pkcs12_load_p(void)
{
    const char *password = "password";

    int temp;

    ckmc_pkcs12_s *ppkcs12 = NULL;

    char p12_path[PATH_LEN] = {0, };
    append_to_app_data_path("p12_for_loadtest.p12", p12_path, sizeof(p12_path));
    temp = ckmc_pkcs12_load(p12_path, password, &ppkcs12);
    assert_eq(temp,CKMC_ERROR_NONE);

    ckmc_pkcs12_free(ppkcs12);

    return 0;
}

/**
 * @testcase        utc_ckmc_pkcs12_load_n
 * @since_tizen     2.4
 * @description     Create a pkcs12 object from a wrong pkcs12 file.
 * @scenario        Create a pkcs12 object with a corrupted pkcs12 file path
 */
int utc_ckmc_pkcs12_load_n(void)
{
    const char *password = "password";

    int temp;

    ckmc_pkcs12_s *ppkcs12 = NULL;

    char p12_path[PATH_LEN] = {0, };
    append_to_app_data_path(
        "invalid_p12_for_loadtest.p12", p12_path, sizeof(p12_path));
    temp = ckmc_pkcs12_load(p12_path, password, &ppkcs12);
    assert_eq(temp,CKMC_ERROR_INVALID_FORMAT);

    return 0;
}

/**
 * @testcase        utc_ckmc_param_list_new_p
 * @since_tizen     3.0
 * @description     Create a new param list with a NULL param in it.
 * @scenario        Create a new param list.
 */
int utc_ckmc_param_list_new_p(void)
{
    int ret;

    ckmc_param_list_h params = NULL;

    ret = ckmc_param_list_new(&params);
    assert_eq(ret, CKMC_ERROR_NONE);

    ckmc_param_list_free(params);

    return 0;
}

/**
 * @testcase        utc_ckmc_param_list_new_n
 * @since_tizen     3.0
 * @description     Check an error in creating a new param list.
 * @scenario        Create a new param list from a NULL parameter.
 */
int utc_ckmc_param_list_new_n(void)
{
    int ret = ckmc_param_list_new(NULL);

    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_ckmc_param_list_set_integer_p
 * @since_tizen     3.0
 * @description     Add a parameter with integer type to a param list.
 * @scenario        Create a param list and add a parameter to it with a name and an integer.
 */
int utc_ckmc_param_list_set_integer_p(void)
{
    int ret;

    ckmc_param_list_h params = NULL;

    ret = ckmc_param_list_new(&params);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_param_list_set_integer(params, CKMC_PARAM_ED_CTR_LEN, 128);
    assert_eq(ret, CKMC_ERROR_NONE);

    ckmc_param_list_free(params);

    return 0;
}

/**
 * @testcase        utc_ckmc_param_list_set_integer_n
 * @since_tizen     3.0
 * @description     Check an error in adding a parameter to param list.
 * @scenario        Create a param list and add a parameter to it with a invalid value.
 */
int utc_ckmc_param_list_set_integer_n(void)
{
    int ret;

    ckmc_param_list_h params = NULL;

    ret = ckmc_param_list_new(&params);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_param_list_set_integer(params, (ckmc_param_name_e)0, 128);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);

    ckmc_param_list_free(params);

    return 0;
}

/**
 * @testcase        utc_ckmc_param_list_set_buffer_p
 * @since_tizen     3.0
 * @description     Add a parameter with buffer type to a param list.
 * @scenario        Create a param list and add a parameter to it with a name and a buffer.
 */
int utc_ckmc_param_list_set_buffer_p(void)
{
    int ret;

    ckmc_param_list_h params = NULL;
    ckmc_raw_buffer_s buffer;

    unsigned char iv[32] = {0, };

    buffer.data = iv;
    buffer.size = sizeof(iv);

    ret = ckmc_param_list_new(&params);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_param_list_set_buffer(params, CKMC_PARAM_ED_IV, &buffer);
    assert_eq(ret, CKMC_ERROR_NONE);

    ckmc_param_list_free(params);

    return 0;
}

/**
 * @testcase        utc_ckmc_param_list_set_buffer_p
 * @since_tizen     3.0
 * @description     Check an error in adding a parameter to param list.
 * @scenario        Add a wrong parameter to a param list.
 */
int utc_ckmc_param_list_set_buffer_n(void)
{
    int ret;

    ckmc_param_list_h params = NULL;
    ckmc_raw_buffer_s buffer;

    buffer.data = NULL;
    buffer.size = 0;

    ret = ckmc_param_list_new(&params);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_param_list_set_buffer(params, CKMC_PARAM_ED_IV, &buffer);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);

    ckmc_param_list_free(params);

    return 0;
}

/**
 * @testcase        utc_ckmc_param_list_get_integer_p
 * @since_tizen     3.0
 * @description     Get a parameter with integer type from a param list.
 * @scenario        Create a param list and add a parameter to it with a name and an integer.
                    Get a parameter from it.
 */
int utc_ckmc_param_list_get_integer_p(void)
{
    int ret;

    ckmc_param_list_h params = NULL;
    ckmc_param_name_e name = CKMC_PARAM_ED_CTR_LEN;
    uint64_t origvalue = 128;
    uint64_t value = 0;

    ret = ckmc_param_list_new(&params);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_param_list_set_integer(params, name, origvalue);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_param_list_get_integer(params, name, &value);
    assert_eq(ret, CKMC_ERROR_NONE);
    assert_eq(origvalue, value);

    ckmc_param_list_free(params);

    return 0;
}

/**
 * @testcase        utc_ckmc_param_list_get_integer_n
 * @since_tizen     3.0
 * @description     Check an error in getting a parameter to param list.
 * @scenario        Create a param list and get a parameter with a invalid name.
 */
int utc_ckmc_param_list_get_integer_n(void)
{
    int ret;

    ckmc_param_list_h params = NULL;
    ckmc_param_name_e origname = CKMC_PARAM_ED_CTR_LEN;
    ckmc_param_name_e name = CKMC_PARAM_ED_TAG_LEN;
    uint64_t origvalue = 128;
    uint64_t value = 0;

    ret = ckmc_param_list_new(&params);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_param_list_set_integer(params, origname, origvalue);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_param_list_get_integer(params, name, &value);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);

    ckmc_param_list_free(params);

    return 0;
}

/**
 * @testcase        utc_ckmc_param_list_get_buffer_p
 * @since_tizen     3.0
 * @description     Get a parameter with integer type from a param list.
 * @scenario        Create a param list and add a parameter to it with a name and a buffer.
                    Get a parameter from it.
 */
int utc_ckmc_param_list_get_buffer_p(void)
{
    int ret;

    ckmc_param_list_h params = NULL;
    ckmc_param_name_e name = CKMC_PARAM_ED_IV;
    ckmc_raw_buffer_s origbuffer;
    ckmc_raw_buffer_s *buffer = NULL;

    unsigned char iv[32] = {0, };

    origbuffer.data = iv;
    origbuffer.size = sizeof(iv);

    ret = ckmc_param_list_new(&params);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_param_list_set_buffer(params, name, &origbuffer);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_param_list_get_buffer(params, name, &buffer);
    assert_eq(ret, CKMC_ERROR_NONE);

    assert_eq(origbuffer.size, buffer->size);
    assert_eq(memcmp(origbuffer.data, buffer->data, sizeof(iv)), 0);

    ckmc_buffer_free(buffer);
    ckmc_param_list_free(params);

    return 0;
}

/**
 * @testcase        utc_ckmc_param_list_get_buffer_n
 * @since_tizen     3.0
 * @description     Check an error in getting a parameter from a param list.
 * @scenario        Create a param list and get a parameter with a invalid name.
 */
int utc_ckmc_param_list_get_buffer_n(void)
{
    int ret;

    ckmc_param_list_h params = NULL;
    ckmc_param_name_e origname = CKMC_PARAM_ED_IV;
    ckmc_param_name_e name = CKMC_PARAM_ED_AAD;
    ckmc_raw_buffer_s origbuffer;
    ckmc_raw_buffer_s *buffer = NULL;

    unsigned char iv[32] = {0, };

    origbuffer.data = iv;
    origbuffer.size = sizeof(iv);

    ret = ckmc_param_list_new(&params);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_param_list_set_buffer(params, origname, &origbuffer);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_param_list_get_buffer(params, name, &buffer);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);

    ckmc_param_list_free(params);

    return 0;
}

/**
 * @testcase        utc_ckmc_param_list_free_p
 * @since_tizen     3.0
 * @description     Free a param list object.
 * @scenario        Create a param list object and free it.
 */
int utc_ckmc_param_list_free_p(void)
{
    int ret;

    ckmc_param_list_h params = NULL;

    ret = ckmc_param_list_new(&params);
    assert_eq(ret, CKMC_ERROR_NONE);

    ckmc_param_list_free(params);

    return 0;
}

/**
 * @testcase        utc_ckmc_param_list_free_n
 * @since_tizen     3.0
 * @description     Free a NULL param list object.
 * @scenario        Free a param list object with a NULL parameter.
 */
int utc_ckmc_param_list_free_n(void)
{
    // returns void
    ckmc_param_list_free(NULL);

    return 0;
}

/**
 * @testcase        utc_ckmc_generate_new_params_p
 * @since_tizen     3.0
 * @description     Generates algorithm parameters for a given algorithm type and adds them to the list.
 * @scenario        Create a param list.
                    Generates algorithm parameters for a given algorithm type.
 */
int utc_ckmc_generate_new_params_p(void)
{
    int ret;

    ckmc_param_list_h params = NULL;

    ret = ckmc_generate_new_params(CKMC_ALGO_AES_CTR, &params);
    assert_eq(ret, CKMC_ERROR_NONE);
    ckmc_param_list_free(params);
    params = NULL;

    ret = ckmc_generate_new_params(CKMC_ALGO_AES_CBC, &params);
    assert_eq(ret, CKMC_ERROR_NONE);
    ckmc_param_list_free(params);
    params = NULL;

    ret = ckmc_generate_new_params(CKMC_ALGO_AES_GCM, &params);
    assert_eq(ret, CKMC_ERROR_NONE);
    ckmc_param_list_free(params);
    params = NULL;

    ret = ckmc_generate_new_params(CKMC_ALGO_AES_CFB, &params);
    assert_eq(ret, CKMC_ERROR_NONE);
    ckmc_param_list_free(params);
    params = NULL;

    ret = ckmc_generate_new_params(CKMC_ALGO_RSA_OAEP, &params);
    assert_eq(ret, CKMC_ERROR_NONE);
    ckmc_param_list_free(params);
    params = NULL;

    return 0;
}

/**
 * @testcase        utc_ckmc_generate_new_params_n
 * @since_tizen     3.0
 * @description     Check an error in creating a parameter.
 * @scenario        Create a param list and get a parameter with a invalid paramter.
 */
int utc_ckmc_generate_new_params_n(void)
{
    int ret = ckmc_generate_new_params(CKMC_ALGO_AES_CTR, NULL);

    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_ckmc_alias_info_get_alias_p
 * @since_tizen     5.5
 * @description     Check if alias is accessible from struct
 * @scenario        Save key to db and check if alias is accessible
 */
int utc_ckmc_alias_info_get_alias_p(void)
{
    ckmc_alias_info_list_s *ppalias_list, *tmp;
    ckmc_key_s test_key;
    ckmc_policy_s test_policy;
    int ret;
    char* key_password = NULL;
    char* policy_password = NULL;
    char* current_alias;
    const char* alias = "utc_ckmc_alias_info_get_alias_p_test_alias";
    bool foundAlias = false;

    test_key.raw_key =  (unsigned char *)RSA_PUB_KEY_PEM2;
    test_key.key_size = strlen(RSA_PUB_KEY_PEM2);
    test_key.key_type = CKMC_KEY_RSA_PUBLIC;
    test_key.password = key_password;

    test_policy.password = policy_password;
    test_policy.extractable = true;

    ret = ckmc_save_key(alias, test_key, test_policy);
    assert_eq(ret, CKMC_ERROR_NONE);
    ret = ckmc_get_key_alias_info_list(&ppalias_list);
    assert_eq(ret, CKMC_ERROR_NONE);

    tmp = ppalias_list;

    while (tmp) {
        ret = ckmc_alias_info_get_alias(tmp->info, &current_alias);
        assert_eq(ret, CKMC_ERROR_NONE);
        if (strstr(current_alias, alias)) {
            foundAlias = true;
            break;
        }
        tmp = tmp->next;
    }
    ckmc_alias_info_list_all_free(ppalias_list);
    ckmc_remove_key(alias);
    assert_eq(foundAlias, true);
    return 0;
}

/**
 * @testcase        utc_ckmc_alias_info_get_alias_n
 * @since_tizen     5.5
 * @description     Check an error when getting a parameter from empty struct
 * @scenario        Create a empty struct and try to get empty paramerer
 */
int utc_ckmc_alias_info_get_alias_n(void)
{
    char* alias;
    int retCode = ckmc_alias_info_get_alias(NULL, &alias);
    assert_eq(retCode, CKMC_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_ckmc_alias_info_is_password_protected_p
 * @since_tizen     5.5
 * @description     Check password protection status for key
 * @scenario        Save key to db and check alias password protection status
 */
int utc_ckmc_alias_info_is_password_protected_p(void)
{
ckmc_alias_info_list_s *ppalias_list, *tmp;
    ckmc_key_s test_key;
    ckmc_policy_s test_policy;
    int ret;
    char* current_alias;
    const char* alias = "utc_ckmc_alias_info_get_alias_p_test_alias";
    bool foundAlias = false;

    test_key.raw_key =  (unsigned char *)RSA_PUB_KEY_PEM2;
    test_key.key_size = strlen(RSA_PUB_KEY_PEM2);
    test_key.key_type = CKMC_KEY_RSA_PUBLIC;
    test_key.password = NULL;

    test_policy.password = NULL;
    test_policy.extractable = true;

    ret = ckmc_save_key(alias, test_key, test_policy);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_get_key_alias_info_list(&ppalias_list);
    assert_eq(ret, CKMC_ERROR_NONE);

    tmp = ppalias_list;

    while (tmp) {
        ret = ckmc_alias_info_get_alias(tmp->info, &current_alias);
        assert_eq(ret, CKMC_ERROR_NONE);
        if (strstr(current_alias, alias)) {
            foundAlias = true;
            bool is_password_protected;
            ret = ckmc_alias_info_is_password_protected(tmp->info, &is_password_protected);
            assert_eq(ret, CKMC_ERROR_NONE);
            assert_eq(is_password_protected, false);
            break;
        }
        tmp = tmp->next;
    }
    ckmc_alias_info_list_all_free(ppalias_list);
    ckmc_remove_key(alias);
    assert_eq(foundAlias, true);
    return 0;
}

/**
 * @testcase        utc_ckmc_alias_info_is_password_protected_n
 * @since_tizen     5.5
 * @description     Check an error when getting a parameter from empty struct
 * @scenario        Create a empty struct and try to get empty parameter
 */
int utc_ckmc_alias_info_is_password_protected_n(void)
{
    bool password_status;
    int retCode = ckmc_alias_info_is_password_protected(NULL, &password_status);
    assert_eq(retCode, CKMC_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_ckmc_alias_info_list_all_free_p
 * @since_tizen     5.5
 * @description     Check if function for freeing resources work
 * @scenario        Create struct and use deleter function
 */
int utc_ckmc_alias_info_list_all_free_p(void)
{
    ckmc_alias_info_list_s* list = (ckmc_alias_info_list_s*)
        malloc(sizeof(ckmc_alias_info_list_s));
    list->info = NULL;
    list->next = NULL;
    ckmc_alias_info_list_all_free(list);
    return 0;
}
