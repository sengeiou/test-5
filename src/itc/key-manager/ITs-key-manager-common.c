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
#include "ITs-key-manager-common.h"

//Add helper function definitions here

/** @addtogroup itc-key-manager
*  @ingroup itc
*  @{
*/

/**
 * @function 		KeyManagerGetDataPath
 * @description	 	Returnes the application data path
 * @parameter		pAppDataPath: application data path
 * @return 			true if succeed else false
 */
bool KeyManagerGetDataPath(char* pAppDataPath)
{
	if ( NULL == pAppDataPath )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	memset(pAppDataPath, 0, PATH_LEN);

	char* pPath = NULL;
	pPath = app_get_data_path();
	if ( NULL == pPath )
	{
		FPRINTF("[Line : %d][%s] Unable to get application data path; app_get_data_path returned null value \\n", __LINE__, API_NAMESPACE);
		return false;
	}

	strncpy(pAppDataPath, pPath, PATH_LEN-1);

	FPRINTF("[Line : %d][%s] application data path returned = %s\\n", __LINE__, API_NAMESPACE, pAppDataPath);

	return true;
}

/**
 * @function 		KeyManagerAppendToAppDataPath
 * @description	 	Appends the input string to application data path
 * @parameter		pInputPath: path to append to data path; pFinalPath: final resultant path
 * @return 			true if succeed else false
 */
bool KeyManagerAppendToAppDataPath(char* pInputPath, char* pFinalPath)
{
	if ( (NULL == pInputPath) || (NULL == pFinalPath) )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	char pAppDataPath[PATH_LEN] = {0,};
	if ( false == KeyManagerGetDataPath(pAppDataPath) )
	{
		return false;
	}

	memset(pFinalPath, 0, PATH_LEN);
	strncpy(pFinalPath, pAppDataPath, PATH_LEN-1);
	strncat(pFinalPath, pInputPath, strlen(pInputPath)+1);

	FPRINTF("[Line : %d][%s] result path returned = %s\\n", __LINE__, API_NAMESPACE, pFinalPath);

	return true;
}

/**
 * @function 		KeyMngrGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
char* KeyMngrGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case CKMC_ERROR_NONE:						szErrorVal = "CKMC_ERROR_NONE";							break;
	case CKMC_ERROR_INVALID_PARAMETER:			szErrorVal = "CKMC_ERROR_INVALID_PARAMETER";			break;
	case CKMC_ERROR_OUT_OF_MEMORY:				szErrorVal = "CKMC_ERROR_OUT_OF_MEMORY";				break;
	case CKMC_ERROR_PERMISSION_DENIED:			szErrorVal = "CKMC_ERROR_PERMISSION_DENIED";			break;
	case CKMC_ERROR_SOCKET:						szErrorVal = "CKMC_ERROR_SOCKET";						break;
	case CKMC_ERROR_BAD_REQUEST:				szErrorVal = "CKMC_ERROR_BAD_REQUEST";					break;
	case CKMC_ERROR_BAD_RESPONSE:				szErrorVal = "CKMC_ERROR_BAD_RESPONSE";					break;
	case CKMC_ERROR_SEND_FAILED:				szErrorVal = "CKMC_ERROR_SEND_FAILED";					break;
	case CKMC_ERROR_RECV_FAILED:				szErrorVal = "CKMC_ERROR_RECV_FAILED";					break;
	case CKMC_ERROR_AUTHENTICATION_FAILED:		szErrorVal = "CKMC_ERROR_AUTHENTICATION_FAILED";		break;
	case CKMC_ERROR_BUFFER_TOO_SMALL:			szErrorVal = "CKMC_ERROR_BUFFER_TOO_SMALL";				break;
	case CKMC_ERROR_SERVER_ERROR:				szErrorVal = "CKMC_ERROR_SERVER_ERROR";					break;
	case CKMC_ERROR_DB_LOCKED:					szErrorVal = "CKMC_ERROR_DB_LOCKED";					break;
	case CKMC_ERROR_DB_ERROR:					szErrorVal = "CKMC_ERROR_DB_ERROR";						break;
	case CKMC_ERROR_DB_ALIAS_EXISTS:			szErrorVal = "CKMC_ERROR_DB_ALIAS_EXISTS";				break;
	case CKMC_ERROR_DB_ALIAS_UNKNOWN:			szErrorVal = "CKMC_ERROR_DB_ALIAS_UNKNOWN";				break;
	case CKMC_ERROR_VERIFICATION_FAILED:		szErrorVal = "CKMC_ERROR_VERIFICATION_FAILED";			break;
	case CKMC_ERROR_INVALID_FORMAT:				szErrorVal = "CKMC_ERROR_INVALID_FORMAT";				break;
	case CKMC_ERROR_FILE_ACCESS_DENIED:			szErrorVal = "CKMC_ERROR_FILE_ACCESS_DENIED";			break;
	case CKMC_ERROR_UNKNOWN:					szErrorVal = "CKMC_ERROR_UNKNOWN";						break;
	default:									szErrorVal = "Unknown Error";							break;
	}

	return szErrorVal;
}

/**
 * @function 		LoadPkcs12
 * @description	 	Creates a new ckmc_key_s(private key), ckmc_cert_s(certificate), and ckmc_cert_list_s(CA certificates) handle from a given PKCS#12 file and returns them.
 * @parameter		ckmc_pkcs12_s **pkcs12_bundle, int *nRetVal
 * @return 			NA
 *
 */
void LoadPkcs12(ckmc_pkcs12_s **pkcs12_bundle, int *nRetVal)
{
	char pszFilePath[PATH_LEN] = {0,};
	if ( false == KeyManagerAppendToAppDataPath(PATHPFX, pszFilePath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return;
	}
	*nRetVal = ckmc_pkcs12_load(pszFilePath, PASSPHRASEPFX, pkcs12_bundle);
}

/**
 * @function 		SaveKey
 * @description	 	Stores a key inside key manager based on the provided policy.
 * @parameter		char* alias, int *nRetVal
 * @return 		NA
 *
 */
void SaveKey(char* alias, int *nRetVal)
{
	ckmc_key_s test_key;
	char* key_password = NULL;
	ckmc_policy_s test_policy;
	char* policy_password = NULL;

	test_key.raw_key = (unsigned char *)RSA_PUB_KEY_PEM;
	test_key.key_size = strlen(RSA_PUB_KEY_PEM);
	test_key.key_type = CKMC_KEY_RSA_PUBLIC;
	test_key.password = key_password;

	test_policy.password = policy_password;
	test_policy.extractable = true;

	*nRetVal = ckmc_save_key(alias, test_key, test_policy);
}

/**
 * @function 		RemoveAlias
 * @description	 	Removes an alias inside key manager based on the provided policy.
 * @parameter		char* alias
 * @return 		NA
 *
 */
void RemoveAlias(char* alias)
{
	ckmc_remove_alias(alias);
}

/**
 * @function 		SaveCertificate
 * @description	 	Stores a certificate inside key manager based on the provided policy.
 * @parameter		char* alias, int *nRetVal
 * @return 		NA
 *
 */
void SaveCertificate(char* alias, int *nRetVal)
{
	ckmc_cert_s cert;
	ckmc_policy_s test_policy;

	char* policy_password = NULL;

	test_policy.password = policy_password;
	test_policy.extractable = true;

	cert.raw_cert = (unsigned char *)CERT_PEM;
	cert.cert_size = strlen(CERT_PEM);
	cert.data_format = CKMC_FORM_PEM;

	 *nRetVal = ckmc_save_cert(alias, cert, test_policy);
}

/**
 * @function 		SaveData
 * @description	 	Stores a data inside key manager based on the provided policy.
 * @parameter		char* alias, int *nRetVal
 * @return 		NA
 *
 */
void SaveData(const char* alias, int *nRetVal)
{
	char* pszPassword = NULL;
	char* pData = "My bin data";

	ckmc_raw_buffer_s DataBuffer;
	ckmc_policy_s policy;

	DataBuffer.data = (unsigned char *) pData;
	DataBuffer.size = strlen(pData);

	policy.password = pszPassword;
	policy.extractable = true;

	*nRetVal = ckmc_save_data(alias, DataBuffer, policy);
}

char* RSA_PUB_KEY_PEM = "-----BEGIN PUBLIC KEY-----\n"
	"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA2b1bXDa+S8/MGWnMkru4\n"
	"T4tUddtZNi0NVjQn9RFH1NMa220GsRhRO56F77FlSVFKfSfVZKIiWg6C+DVCkcLf\n"
	"zXJ/Z0pvwOQYBAqVMFjV6efQGN0JzJ1Unu7pPRiZl7RKGEI+cyzzrcDyrLLrQ2W7\n"
	"0ZySkNEOv6Frx9JgC5NExuYY4lk2fQQa38JXiZkfyzif2em0px7mXbyf5LjccsKq\n"
	"v1e+XLtMsL0ZefRcqsP++NzQAI8fKX7WBT+qK0HJDLiHrKOTWYzx6CwJ66LD/vvf\n"
	"j55xtsKDLVDbsotvf8/m6VLMab+vqKk11TP4tq6yo0mwyTADvgl1zowQEO9I1W6o\n"
	"zQIDAQAB\n"
	"-----END PUBLIC KEY-----";

char* CERT_PEM = "-----BEGIN CERTIFICATE-----\n"
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

char* CRY_RSA_PRI_KEY =
	"-----BEGIN RSA PRIVATE KEY-----\n"
	"MIICXQIBAAKBgQDCKb9BkTdOjCTXKPi/H5FSGuyrgzORBtR3nCTg7SRnL47zNGEj\n"
	"l2wkgsY9ZO3UJHm0gy5KMjWeCuUVkSD3G46J9obg1bYJivCQBJKxfieA8sWOtNq1\n"
	"M8emHGK8o3sjaRklrngmk2xSCs5vFJVlCluzAYUmrPDm64C3+n4yW4pBCQIDAQAB\n"
	"AoGAd1IWgiHO3kuLvFome7XXpaB8P27SutZ6rcLcewnhLDRy4g0XgTrmL43abBJh\n"
	"gdSkooVXZity/dvuKpHUs2dQ8W8zYiFFsHfu9qqLmLP6SuBPyUCvlUDH5BGfjjxI\n"
	"5qGWIowj/qGHKpbQ7uB+Oe2BHwbHao0zFZIkfKqY0mX9U00CQQDwF/4zQcGS1RX/\n"
	"229gowTsvSGVmm8cy1jGst6xkueEuOEZ/AVPO1fjavz+nTziUk4E5lZHAj18L6Hl\n"
	"iO29LRujAkEAzwbEWVhfTJewCZIFf3sY3ifXhGZhVKDHVzPBNyoft8Z+09DMHTJb\n"
	"EYg85MIbR73aUyIWsEci/CPk6LPRNv47YwJAHtQF2NEFqPPhakPjzjXAaSFz0YDN\n"
	"6ZWWpZTMEWL6hUkz5iE9EUpeY54WNB8+dRT6XZix1VZNTMfU8uMdG6BSHwJBAKYM\n"
	"gm47AGz5eVujwD8op6CACk+KomRzdI+P1lh9s+T+E3mnDiAY5IxiXp0Ix0K6lyN4\n"
	"wwPuerQLwi2XFKZsMYsCQQDOiSQFP9PfXh9kFzN6e89LxOdnqC/r9i5GDB3ea8eL\n"
	"SCRprpzqOXZvOP1HBAEjsJ6k4f8Dqj1fm+y8ZcgAZUPr\n"
	"-----END RSA PRIVATE KEY-----\n";

char* CRY_CERT =
	"-----BEGIN CERTIFICATE-----\n"
	"MIICijCCAfOgAwIBAgIJAMvaNHQ1ozT8MA0GCSqGSIb3DQEBBQUAMF4xCzAJBgNV\n"
	"BAYTAlBMMQ0wCwYDVQQIDARMb2R6MQ0wCwYDVQQHDARMb2R6MRAwDgYDVQQKDAdT\n"
	"YW1zdW5nMREwDwYDVQQLDAhTZWN1cml0eTEMMAoGA1UEAwwDQ0tNMB4XDTE0MDcw\n"
	"MjEyNDE0N1oXDTE3MDcwMTEyNDE0N1owXjELMAkGA1UEBhMCUEwxDTALBgNVBAgM\n"
	"BExvZHoxDTALBgNVBAcMBExvZHoxEDAOBgNVBAoMB1NhbXN1bmcxETAPBgNVBAsM\n"
	"CFNlY3VyaXR5MQwwCgYDVQQDDANDS00wgZ8wDQYJKoZIhvcNAQEBBQADgY0AMIGJ\n"
	"AoGBAMIpv0GRN06MJNco+L8fkVIa7KuDM5EG1HecJODtJGcvjvM0YSOXbCSCxj1k\n"
	"7dQkebSDLkoyNZ4K5RWRIPcbjon2huDVtgmK8JAEkrF+J4DyxY602rUzx6YcYryj\n"
	"eyNpGSWueCaTbFIKzm8UlWUKW7MBhSas8ObrgLf6fjJbikEJAgMBAAGjUDBOMB0G\n"
	"A1UdDgQWBBQuW9DuITahZJ6saVZZI0aBlis5vzAfBgNVHSMEGDAWgBQuW9DuITah\n"
	"ZJ6saVZZI0aBlis5vzAMBgNVHRMEBTADAQH/MA0GCSqGSIb3DQEBBQUAA4GBAB2X\n"
	"GNtJopBJR3dCpzDONknr/c6qcsPVa3nH4c7qzy6F+4bgqa5IObnoF8zUrvD2sMAO\n"
	"km3C/N+Qzt8Rb7ORM6U4tlPp1kZ5t6PKjghhNaiYwVm9A/Zm+wyAmRIkQiYDr4MX\n"
	"e+bRAkPmJeEWpaav1lvvBnFzGSGJrnSSeWUegGyn\n"
	"-----END CERTIFICATE-----\n";

// Test certificate signed with test intermediate ca
char* CERT_CHAIN1 =
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
	"-----END CERTIFICATE-----\n";

// Test root ca is installed in /etc/ssl/certs
// Test intermediate ca signed with test root ca
char* CERT_CHAIN2 =
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
	"-----END CERTIFICATE-----\n";

char *RSA_PRIKEY =
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

char *RSA_PRIKEY_PASS = "1234";

char *TEST_ROOT_CA =
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

char *TEST_IM_CA =
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

char *TEST_LEAF_CERT =
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

char *RSA_PUBKEY =
	"-----BEGIN PUBLIC KEY-----\n"
	"IIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA2b1bXDa+S8/MGWnMkru4\n"
	"T4tUddtZNi0NVjQn9RFH1NMa220GsRhRO56F77FlSVFKfSfVZKIiWg6C+DVCkcLf\n"
	"zXJ/Z0pvwOQYBAqVMFjV6efQGN0JzJ1Unu7pPRiZl7RKGEI+cyzzrcDyrLLrQ2W7\n"
	"0ZySkNEOv6Frx9JgC5NExuYY4lk2fQQa38JXiZkfyzif2em0px7mXbyf5LjccsKq\n"
	"v1e+XLtMsL0ZefRcqsP++NzQAI8fKX7WBT+qK0HJDLiHrKOTWYzx6CwJ66LD/vvf\n"
	"j55xtsKDLVDbsotvf8/m6VLMab+vqKk11TP4tq6yo0mwyTADvgl1zowQEO9I1W6o\n"
	"zQIDAQAB\n"
	"-----END PUBLIC KEY-----";

/** @} */