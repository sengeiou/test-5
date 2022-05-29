//
// Copyright (c) 2014 - 2021 Samsung Electronics Co., Ltd.
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

#include <ckmc/ckmc-manager.h>
#include <ckmc/ckmc-type.h>
#include <ckmc/ckmc-error.h>

#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


FILE *g_fpLog;

#define _PRINT_LOG(...) {\
    g_fpLog = fopen("/tmp/utclog", "a");\
    fprintf(g_fpLog, __VA_ARGS__);\
    fclose(g_fpLog);\
}

#define PRINT_ERROR(fmt, args...) {\
    _PRINT_LOG("[E/%d] "fmt"\\n", __LINE__, ##args); \
}

#define PRINT_INFO(fmt, args...) {\
    _PRINT_LOG("[I/%d] "fmt"\\n", __LINE__, ##args); \
}


//& set: key-manager-crypto

static const char* CRY_RSA_PRI_KEY =
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

static const char* CRY_CERT =
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
static const char* CERT_CHAIN1 =
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
static const char* CERT_CHAIN2 =
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

/*
 * Not Before: Jul 21 23:00:00 2020 GMT
 * Not After : Oct  8 07:00:00 2024 GMT
 * Subject: C = US, O = Microsoft Corporation, CN = Microsoft RSA TLS CA 01
 */
static const char* OCSP_CERT_IM =
    "-----BEGIN CERTIFICATE-----\n"
    "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\n"
    "-----END CERTIFICATE-----\n";

/*
 * Not Before: Dec 22 01:34:07 2021 GMT
 * Not After : Jun 22 01:34:07 2022 GMT
 * Subject: CN = www.bing.com
 * Issuer: C = US, O = Microsoft Corporation, CN = Microsoft RSA TLS CA 01
 */
static const char* OCSP_CERT =
    "-----BEGIN CERTIFICATE-----\n"
    "MIINWjCCC0KgAwIBAgITEgAfcvcKCqFVliq5ywAAAB9y9zANBgkqhkiG9w0BAQsF\n"
    "ADBPMQswCQYDVQQGEwJVUzEeMBwGA1UEChMVTWljcm9zb2Z0IENvcnBvcmF0aW9u\n"
    "MSAwHgYDVQQDExdNaWNyb3NvZnQgUlNBIFRMUyBDQSAwMTAeFw0yMTEyMjIwMTM0\n"
    "MDdaFw0yMjA2MjIwMTM0MDdaMBcxFTATBgNVBAMTDHd3dy5iaW5nLmNvbTCCASIw\n"
    "DQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAJYbrxy4NFq3iQ0ZXASXsYp02tLG\n"
    "hKK54sWr4QFxIkYJZQX9/xBdwQMfYSdH793Zdft/6tn0kRk9W0aDLUE/5Iw1perB\n"
    "YBFPflSfLp1JGj5Btrr6D+5VSBBSAx9Mq/taAUTlmLVnTJHamJt+yRbiiLn6+wIf\n"
    "6P8hw2/Bae7bX5COiwL5RWyoMJz0LxKTWFLax4fx3wuFRKinBVNJyhommtJDXlG6\n"
    "4UhXkwgbf4mdfI1bQGuzurOJZ8Mv17MIQilT+gBnF2b7Kx5H+LxJF3gXbJjAfoPF\n"
    "98NUtRCqQYzAIA3JrHKxThi2ALDmloejGTXuD9rllv8DaETPrch0M9zU0s0CAwEA\n"
    "AaOCCWUwgglhMIIBfgYKKwYBBAHWeQIEAgSCAW4EggFqAWgAdgApeb7wnjk5IfBW\n"
    "c59jpXflvld9nGAK+PlNXSZcJV3HhAAAAX3fz2fZAAAEAwBHMEUCIQCCUdOep2CF\n"
    "1UKCVaMAp0XKoeyXLCY+dLx9naojXnc7gQIgFdLQMXazPR1jezRCdTCQPK8gfWTQ\n"
    "gpxy0+jLuPrAvEoAdwBVgdTCFpA2AUrqC5tXPFPwwOQ4eHAlCBcvo6odBxPTDAAA\n"
    "AX3fz2jrAAAEAwBIMEYCIQDEOCKOre6gyuDKiUgSgReIGIY0SYicpmTkfWvvRyJW\n"
    "ygIhAL2tnClNihUTXxdkFp6PGdglKRyarYVObk18jNl9sbZtAHUAUaOw9f0BeZxW\n"
    "bbg3eI8MpHrMGyfL956IQpoN/tSLBeUAAAF9389o8gAABAMARjBEAiB3xhpmaVCS\n"
    "OqL/M40nsRW1qiTjpgJlHrfaBumUVpsjkgIgIWTbLmuAVkC4hzsF5y9T7ntMAI39\n"
    "GYRstybaGUvcQeMwJwYJKwYBBAGCNxUKBBowGDAKBggrBgEFBQcDATAKBggrBgEF\n"
    "BQcDAjA+BgkrBgEEAYI3FQcEMTAvBicrBgEEAYI3FQiH2oZ1g+7ZAYLJhRuBtZ5h\n"
    "hfTrYIFdhYaOQYfCmFACAWQCAScwgYcGCCsGAQUFBwEBBHsweTBTBggrBgEFBQcw\n"
    "AoZHaHR0cDovL3d3dy5taWNyb3NvZnQuY29tL3BraS9tc2NvcnAvTWljcm9zb2Z0\n"
    "JTIwUlNBJTIwVExTJTIwQ0ElMjAwMS5jcnQwIgYIKwYBBQUHMAGGFmh0dHA6Ly9v\n"
    "Y3NwLm1zb2NzcC5jb20wHQYDVR0OBBYEFJ75gKW07KZZzv6xGyHoaaoBVHztMA4G\n"
    "A1UdDwEB/wQEAwIEsDCCBW0GA1UdEQSCBWQwggVgggx3d3cuYmluZy5jb22CEGRp\n"
    "Y3QuYmluZy5jb20uY26CEyoucGxhdGZvcm0uYmluZy5jb22CCiouYmluZy5jb22C\n"
    "CGJpbmcuY29tghZpZW9ubGluZS5taWNyb3NvZnQuY29tghMqLndpbmRvd3NzZWFy\n"
    "Y2guY29tghljbi5pZW9ubGluZS5taWNyb3NvZnQuY29tghEqLm9yaWdpbi5iaW5n\n"
    "LmNvbYINKi5tbS5iaW5nLm5ldIIOKi5hcGkuYmluZy5jb22CGGVjbi5kZXYudmly\n"
    "dHVhbGVhcnRoLm5ldIINKi5jbi5iaW5nLm5ldIINKi5jbi5iaW5nLmNvbYIQc3Ns\n"
    "LWFwaS5iaW5nLmNvbYIQc3NsLWFwaS5iaW5nLm5ldIIOKi5hcGkuYmluZy5uZXSC\n"
    "DiouYmluZ2FwaXMuY29tgg9iaW5nc2FuZGJveC5jb22CFmZlZWRiYWNrLm1pY3Jv\n"
    "c29mdC5jb22CG2luc2VydG1lZGlhLmJpbmcub2ZmaWNlLm5ldIIOci5iYXQuYmlu\n"
    "Zy5jb22CECouci5iYXQuYmluZy5jb22CEiouZGljdC5iaW5nLmNvbS5jboIPKi5k\n"
    "aWN0LmJpbmcuY29tgg4qLnNzbC5iaW5nLmNvbYIQKi5hcHBleC5iaW5nLmNvbYIW\n"
    "Ki5wbGF0Zm9ybS5jbi5iaW5nLmNvbYINd3AubS5iaW5nLmNvbYIMKi5tLmJpbmcu\n"
    "Y29tgg9nbG9iYWwuYmluZy5jb22CEXdpbmRvd3NzZWFyY2guY29tgg5zZWFyY2gu\n"
    "bXNuLmNvbYIRKi5iaW5nc2FuZGJveC5jb22CGSouYXBpLnRpbGVzLmRpdHUubGl2\n"
    "ZS5jb22CDyouZGl0dS5saXZlLmNvbYIYKi50MC50aWxlcy5kaXR1LmxpdmUuY29t\n"
    "ghgqLnQxLnRpbGVzLmRpdHUubGl2ZS5jb22CGCoudDIudGlsZXMuZGl0dS5saXZl\n"
    "LmNvbYIYKi50My50aWxlcy5kaXR1LmxpdmUuY29tghUqLnRpbGVzLmRpdHUubGl2\n"
    "ZS5jb22CCzNkLmxpdmUuY29tghNhcGkuc2VhcmNoLmxpdmUuY29tghRiZXRhLnNl\n"
    "YXJjaC5saXZlLmNvbYIVY253ZWIuc2VhcmNoLmxpdmUuY29tggxkZXYubGl2ZS5j\n"
    "b22CDWRpdHUubGl2ZS5jb22CEWZhcmVjYXN0LmxpdmUuY29tgg5pbWFnZS5saXZl\n"
    "LmNvbYIPaW1hZ2VzLmxpdmUuY29tghFsb2NhbC5saXZlLmNvbS5hdYIUbG9jYWxz\n"
    "ZWFyY2gubGl2ZS5jb22CFGxzNGQuc2VhcmNoLmxpdmUuY29tgg1tYWlsLmxpdmUu\n"
    "Y29tghFtYXBpbmRpYS5saXZlLmNvbYIObG9jYWwubGl2ZS5jb22CDW1hcHMubGl2\n"
    "ZS5jb22CEG1hcHMubGl2ZS5jb20uYXWCD21pbmRpYS5saXZlLmNvbYINbmV3cy5s\n"
    "aXZlLmNvbYIcb3JpZ2luLmNud2ViLnNlYXJjaC5saXZlLmNvbYIWcHJldmlldy5s\n"
    "b2NhbC5saXZlLmNvbYIPc2VhcmNoLmxpdmUuY29tghJ0ZXN0Lm1hcHMubGl2ZS5j\n"
    "b22CDnZpZGVvLmxpdmUuY29tgg92aWRlb3MubGl2ZS5jb22CFXZpcnR1YWxlYXJ0\n"
    "aC5saXZlLmNvbYIMd2FwLmxpdmUuY29tghJ3ZWJtYXN0ZXIubGl2ZS5jb22CE3dl\n"
    "Ym1hc3RlcnMubGl2ZS5jb22CFXd3dy5sb2NhbC5saXZlLmNvbS5hdYIUd3d3Lm1h\n"
    "cHMubGl2ZS5jb20uYXUwgbAGA1UdHwSBqDCBpTCBoqCBn6CBnIZNaHR0cDovL21z\n"
    "Y3JsLm1pY3Jvc29mdC5jb20vcGtpL21zY29ycC9jcmwvTWljcm9zb2Z0JTIwUlNB\n"
    "JTIwVExTJTIwQ0ElMjAwMS5jcmyGS2h0dHA6Ly9jcmwubWljcm9zb2Z0LmNvbS9w\n"
    "a2kvbXNjb3JwL2NybC9NaWNyb3NvZnQlMjBSU0ElMjBUTFMlMjBDQSUyMDAxLmNy\n"
    "bDBXBgNVHSAEUDBOMEIGCSsGAQQBgjcqATA1MDMGCCsGAQUFBwIBFidodHRwOi8v\n"
    "d3d3Lm1pY3Jvc29mdC5jb20vcGtpL21zY29ycC9jcHMwCAYGZ4EMAQIBMB8GA1Ud\n"
    "IwQYMBaAFLV2DDARzseSQk1Mx1wsyKkM6AtkMB0GA1UdJQQWMBQGCCsGAQUFBwMB\n"
    "BggrBgEFBQcDAjANBgkqhkiG9w0BAQsFAAOCAgEANf9lCvl9aj7qHuAPleyuDr0M\n"
    "9D2LMjeim+ooL7QnVxw5cusBIfctG0qBX2PEe+++ViUigGg0v6QKasJ7XQ3hs6kf\n"
    "TAHMTXgiXq/NpWeWieEWVdrgSoihPmZbcmvD6wCXgR4kAGReU6yKPpi66dSSU5yl\n"
    "c2gC+6+ooy46LPSe3nopA2HvZ3A2uvXY3TmXKX9K2CxpsHUoBSLersdI+gcSUZhs\n"
    "qnzpW07AuoMuquzC2nUmb8HFNKqkqQ4tgluHtU506j/sgnnQzTUt55nTk1JhwCiB\n"
    "ltfrMSGz+GhrLgO8r/DiMF8mPo+y0zsoYU9H1doUMmddyoI05Z+IjhzwI0iRqYlT\n"
    "syef//6tnVqO/Oarn/e5ZK8k8UWOGs52c2pAJMjIP6dplfsrwc7jb3TbiM26qGpv\n"
    "pf6nrLg3lqhLpzuPIzfX+Ped3hsWAqm/3k/An3kU+Bh3Y8e6oExgLeXbWp1vm24N\n"
    "gFhWuODPPSC1mEMvUR6ZUycgwU7XShqGeYtKzX7dt9EH+OhAXq//1EbPZ/x41o5u\n"
    "AiJBXLjYvx6tNfQsG9IAA5YjWVuju/xLXsJWgTVCk7hgu12QFR+9L59o5okwxFu5\n"
    "D2KgZb2BPZFGcJ5s3B0QZWKEqDB5yPDmo1RmBDbxdrJvOiwUKY7JVR8tqll5unz8\n"
    "pwWa/hYZWHYfUK0kFkM=\n"
    "-----END CERTIFICATE-----\n";

void utc_key_manager_crypto_startup(void)
{
//    setuid(APPUSER_ID);
}

void utc_key_manager_crypto_cleanup(void)
{
}


/**
 * @testcase        utc_ckmc_create_key_pair_rsa_p
 * @since_tizen     2.3
 * @description     Create a private key and its public key with RSA algorithm.
 * @scenario        Create a private key and its public key with their aliases and store policies.
 */
int utc_ckmc_create_key_pair_rsa_p(void)
{
    int temp;

    size_t size = 1024;
    const char *private_key_alias = "PRV_KEY1";
    const char *public_key_alias = "PUB_KEY1";
    ckmc_policy_s policy_private_key;
    ckmc_policy_s policy_public_key;

    policy_private_key.password = NULL;
    policy_private_key.extractable = true;

    policy_public_key.password = NULL;
    policy_public_key.extractable = true;

    temp = ckmc_create_key_pair_rsa(size, private_key_alias, public_key_alias, policy_private_key, policy_public_key);
    assert_eq(temp,CKMC_ERROR_NONE);
    temp = ckmc_remove_key (private_key_alias);
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_remove_key (public_key_alias);
    assert_eq(temp, CKMC_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_ckmc_create_key_pair_rsa_n
 * @since_tizen     2.3
 * @description     Check an error in creating a RSA key pair.
 * @scenario        Create a new key pair from NULL parameters.
 */
int utc_ckmc_create_key_pair_rsa_n(void)
{
    int temp;

    size_t size = 2048;
    const char *private_key_alias = NULL;
    const char *public_key_alias = NULL;
    ckmc_policy_s policy_private_key;
    ckmc_policy_s policy_public_key;

    policy_private_key.password = NULL;
    policy_private_key.extractable = true;

    policy_public_key.password = NULL;
    policy_public_key.extractable = true;

    temp = ckmc_create_key_pair_rsa(size, private_key_alias, public_key_alias, policy_private_key, policy_public_key);
    assert_eq(temp,CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_ckmc_create_key_pair_ecdsa_p
 * @since_tizen     2.3
 * @description     Create a private key and its public key with ECDSA algorithm.
 * @scenario        Create a private key and its public key with their aliases and store policies.
 */
int utc_ckmc_create_key_pair_ecdsa_p(void)
{
    int temp;

    ckmc_ec_type_e ectype = CKMC_EC_PRIME192V1;
    const char *private_key_alias = "ecdsa-test-1";
    const char *public_key_alias = "ecdsa-test-2";
    ckmc_policy_s policy_private_key;
    ckmc_policy_s policy_public_key;

    char *key_password = "privatepassword";

    policy_private_key.password = key_password;
    policy_private_key.extractable = false;

    policy_public_key.password = NULL;
    policy_public_key.extractable = true;

    temp = ckmc_create_key_pair_ecdsa(ectype, private_key_alias, public_key_alias, policy_private_key, policy_public_key);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_remove_key (private_key_alias);
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_remove_key (public_key_alias);
    assert_eq(temp, CKMC_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_ckmc_create_key_pair_ecdsa_n
 * @since_tizen     2.3
 * @description     Check an error in creating a ECDSA key pair.
 * @scenario        Create a new key pair from NULL parameters.
 */
int utc_ckmc_create_key_pair_ecdsa_n(void)
{
    int temp;

    ckmc_ec_type_e ectype = CKMC_EC_PRIME192V1;
    const char *private_key_alias = NULL;
    const char *public_key_alias = NULL;
    ckmc_policy_s policy_private_key;
    ckmc_policy_s policy_public_key;

    char *key_password = "privatepassword";

    policy_private_key.password = key_password;
    policy_private_key.extractable = false;

    policy_public_key.password = NULL;
    policy_public_key.extractable = true;

    temp = ckmc_create_key_pair_ecdsa(ectype, private_key_alias, public_key_alias, policy_private_key, policy_public_key);
    assert_eq(temp,CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_ckmc_create_key_pair_dsa_p
 * @since_tizen     2.3
 * @description     Create a private key and its public key with DSA algorithm.
 * @scenario        Create a private key and its public key with their aliases and store policies.
 */
int utc_ckmc_create_key_pair_dsa_p(void)
{
    int temp;
    size_t size = 1024;
    const char *private_key_alias = "dsa-test-1-priv";
    const char *public_key_alias = "dsa-test-1-pub";
    ckmc_policy_s policy_private_key;
    ckmc_policy_s policy_public_key;

    policy_private_key.password = NULL;
    policy_private_key.extractable = false;

    policy_public_key.password = NULL;
    policy_public_key.extractable = true;

    temp = ckmc_create_key_pair_dsa(size, private_key_alias, public_key_alias, policy_private_key, policy_public_key);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_remove_key (private_key_alias);
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_remove_key (public_key_alias);
    assert_eq(temp, CKMC_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_ckmc_create_key_pair_dsa_n
 * @since_tizen     2.3
 * @description     Check an error in creating a DSA key pair.
 * @scenario        Create a new key pair from NULL parameters.
 */
int utc_ckmc_create_key_pair_dsa_n(void)
{
    int temp;
    size_t size = 1024;
    const char *private_key_alias = NULL;
    const char *public_key_alias = NULL;
    ckmc_policy_s policy_private_key;
    ckmc_policy_s policy_public_key;

    policy_private_key.password = NULL;
    policy_private_key.extractable = false;

    policy_public_key.password = NULL;
    policy_public_key.extractable = true;

    temp = ckmc_create_key_pair_dsa(size, private_key_alias, public_key_alias, policy_private_key, policy_public_key);
    assert_eq(temp, CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_ckmc_create_signature_p
 * @since_tizen     2.3
 * @description     Create a signature value from a message
 * @scenario        Store a private key and create a signature value from a message with a private key alias.
 */
int utc_ckmc_create_signature_p(void)
{
    int temp;

    char* message = "message test";

    ckmc_raw_buffer_s msg_buff;
    msg_buff.data = (unsigned char*) message;
    msg_buff.size = strlen(message);

    const char *pri_alias = "create_signature_p_pri_alias";
    const char *pub_alias = "create_signature_p_pub_alias";
    char *key_passwd = NULL;
    char *pri_passwd = NULL;
    char *pub_passwd = NULL;

    ckmc_cert_s cert;
    cert.raw_cert = (unsigned char *) CRY_CERT;
    cert.cert_size = strlen(CRY_CERT);
    cert.data_format = CKMC_FORM_PEM;

    ckmc_policy_s certpolicy;
    certpolicy.password = pub_passwd;
    certpolicy.extractable = true;

    ckmc_key_s prikey;
    prikey.raw_key = (unsigned char *) CRY_RSA_PRI_KEY;
    prikey.key_size = strlen(CRY_RSA_PRI_KEY);
    prikey.key_type = CKMC_KEY_NONE;
    prikey.password = key_passwd;

    ckmc_policy_s pripolicy;
    pripolicy.password = pri_passwd;
    pripolicy.extractable = false;

    temp = ckmc_save_cert(pub_alias, cert, certpolicy);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_save_key(pri_alias, prikey, pripolicy);
    assert_eq(temp,CKMC_ERROR_NONE);

    ckmc_hash_algo_e hash_algo = CKMC_HASH_SHA256;
    ckmc_rsa_padding_algo_e pad_algo = CKMC_PKCS1_PADDING;
    ckmc_raw_buffer_s *signature;

    temp = ckmc_create_signature(
                    pri_alias,
                    pri_passwd,
                    msg_buff,
                    hash_algo,
                    pad_algo,
                    &signature);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_remove_cert(pub_alias);
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_remove_key(pri_alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_create_signature_n
 * @since_tizen     2.3
 * @description     Create a signature value from a message with NULL alias
 * @scenario        Store a private key and create a signature value from a message with a NULL alias.
 */
int utc_ckmc_create_signature_n(void)
{
    int temp;

    char* message = "message test";

    ckmc_raw_buffer_s msg_buff;
    msg_buff.data = (unsigned char*) message;
    msg_buff.size = strlen(message);

    const char *pri_alias = "crete_signature_n_prv3";
    const char *pub_alias = "crete_signature_n_pub3";
    const char *pri_alias_wrong = NULL;
    const char *pub_alias_wrong = NULL;
    char *key_passwd = NULL;
    char *pri_passwd = NULL;
    char *pub_passwd = NULL;

    ckmc_cert_s cert;
    cert.raw_cert = (unsigned char *) CRY_CERT;
    cert.cert_size = strlen(CRY_CERT);
    cert.data_format = CKMC_FORM_PEM;

    ckmc_policy_s certpolicy;
    certpolicy.password = pub_passwd;
    certpolicy.extractable = true;

    ckmc_key_s prikey;
    prikey.raw_key = (unsigned char *) CRY_RSA_PRI_KEY;
    prikey.key_size = strlen(CRY_RSA_PRI_KEY);
    prikey.key_type = CKMC_KEY_NONE;
    prikey.password = key_passwd;

    ckmc_policy_s pripolicy;
    pripolicy.password = pri_passwd;
    pripolicy.extractable = false;

    temp = ckmc_save_cert(pub_alias, cert, certpolicy);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_save_key(pri_alias, prikey, pripolicy);
    assert_eq(temp,CKMC_ERROR_NONE);

    ckmc_hash_algo_e hash_algo = CKMC_HASH_SHA256;
    ckmc_rsa_padding_algo_e pad_algo = CKMC_PKCS1_PADDING;
    ckmc_raw_buffer_s *signature;

    temp = ckmc_create_signature(
                    pri_alias_wrong,
                    pub_alias_wrong,
                    msg_buff,
                    hash_algo,
                    pad_algo,
                    &signature);
    assert_eq(temp,CKMC_ERROR_INVALID_PARAMETER);

    temp = ckmc_remove_cert(pub_alias);
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_remove_key(pri_alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_verify_signature_p
 * @since_tizen     2.3
 * @description     Verify a signature value from a message
 * @scenario        Store a private key and a public key.
                    Create a signature value from a message with a private alias.
                    Verify the signature value with the public key alias.
 */
int utc_ckmc_verify_signature_p(void)
{
    int temp;

    char* message = "message test";

    ckmc_raw_buffer_s msg_buff;
    msg_buff.data = (unsigned char*) message;
    msg_buff.size = strlen(message);

    const char *pri_alias = "verify_signature_p_prv3";
    const char *pub_alias = "verify_signature_p_pub3";
    char *key_passwd = NULL;
    char *pri_passwd = NULL;
    char *pub_passwd = NULL;

    ckmc_hash_algo_e hash_algo = CKMC_HASH_SHA256;
    ckmc_rsa_padding_algo_e pad_algo = CKMC_PKCS1_PADDING;
    ckmc_raw_buffer_s *signature;

    ckmc_cert_s cert;
    cert.raw_cert = (unsigned char *) CRY_CERT;
    cert.cert_size = strlen(CRY_CERT);
    cert.data_format = CKMC_FORM_PEM;

    ckmc_policy_s certpolicy;
    certpolicy.password = pub_passwd;
    certpolicy.extractable = true;

    ckmc_key_s prikey;
    prikey.raw_key = (unsigned char *) CRY_RSA_PRI_KEY;
    prikey.key_size = strlen(CRY_RSA_PRI_KEY);
    prikey.key_type = CKMC_KEY_NONE;
    prikey.password = key_passwd;

    ckmc_policy_s pripolicy;
    pripolicy.password = pri_passwd;
    pripolicy.extractable = false;

    temp = ckmc_save_cert(pub_alias, cert, certpolicy);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_save_key(pri_alias, prikey, pripolicy);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_create_signature(
                    pri_alias,
                    pri_passwd,
                    msg_buff,
                    hash_algo,
                    pad_algo,
                    &signature);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_verify_signature(
                    pub_alias,
                    pub_passwd,
                    msg_buff,
                    *signature,
                    hash_algo,
                    pad_algo);

    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_remove_cert(pub_alias);
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_remove_key(pri_alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_verify_signature_n
 * @since_tizen     2.3
 * @description     Create a signature value from a message with NULL alias
 * @scenario        Store a private key and a public key.
                    Create a signature value from a message with a private alias.
                    Verify the signature value with the NULL alias.
 */
int utc_ckmc_verify_signature_n(void)
{
    int temp;

    char* message = "message test";

    ckmc_raw_buffer_s msg_buff;
    msg_buff.data = (unsigned char*) message;
    msg_buff.size = strlen(message);

    const char *pri_alias = "verify_signature_n_pri3";
    const char *pub_alias = "verify_signature_n_pub3";
    const char *pri_alias_wrong = NULL;
    const char *pub_alias_wrong = NULL;
    char *key_passwd = NULL;
    char *pri_passwd = NULL;
    char *pub_passwd = NULL;

    ckmc_hash_algo_e hash_algo = CKMC_HASH_SHA256;
    ckmc_rsa_padding_algo_e pad_algo = CKMC_PKCS1_PADDING;
    ckmc_raw_buffer_s *signature;

    ckmc_cert_s cert;
    cert.raw_cert = (unsigned char *) CRY_CERT;
    cert.cert_size = strlen(CRY_CERT);
    cert.data_format = CKMC_FORM_PEM;

    ckmc_policy_s certpolicy;
    certpolicy.password = pub_passwd;
    certpolicy.extractable = true;

    ckmc_key_s prikey;
    prikey.raw_key = (unsigned char *) CRY_RSA_PRI_KEY;
    prikey.key_size = strlen(CRY_RSA_PRI_KEY);
    prikey.key_type = CKMC_KEY_NONE;
    prikey.password = key_passwd;

    ckmc_policy_s pripolicy;
    pripolicy.password = pri_passwd;
    pripolicy.extractable = false;

    temp = ckmc_save_cert(pub_alias, cert, certpolicy);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_save_key(pri_alias, prikey, pripolicy);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_create_signature(
                    pri_alias,
                    pri_passwd,
                    msg_buff,
                    hash_algo,
                    pad_algo,
                    &signature);
    assert_eq(temp,CKMC_ERROR_NONE);

    temp = ckmc_verify_signature(
                    pri_alias_wrong,
                    pub_alias_wrong,
                    msg_buff,
                    *signature,
                    hash_algo,
                    pad_algo);
    assert_eq(temp,CKMC_ERROR_INVALID_PARAMETER);

    temp = ckmc_remove_cert(pub_alias);
    assert_eq(temp, CKMC_ERROR_NONE);
    temp = ckmc_remove_key(pri_alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_cert_chain_p
 * @since_tizen     2.3
 * @description     verify a certificate and get a certificate chain.
 * @scenario        Set a leaf certificate and untrunsted certificates.
                    Call ckmc_get_cert_chain to get a certificate chain.
 */
int utc_ckmc_get_cert_chain_p(void)
{
    int temp;
    int chain_len = 3;

    ckmc_cert_s c_cert;
    ckmc_cert_s c_cert1;
    ckmc_cert_list_s untrustedcerts;

    c_cert.raw_cert = (unsigned char *) CERT_CHAIN1;
    c_cert.cert_size = strlen(CERT_CHAIN1);
    c_cert.data_format = CKMC_FORM_PEM;

    c_cert1.raw_cert = (unsigned char *) CERT_CHAIN2;
    c_cert1.cert_size = strlen(CERT_CHAIN2);
    c_cert1.data_format = CKMC_FORM_PEM;

    untrustedcerts.cert = &c_cert1;
    untrustedcerts.next = NULL;

    ckmc_cert_list_s *cert_chain_list;

    temp = ckmc_get_cert_chain(&c_cert, &untrustedcerts, &cert_chain_list);
    assert_eq(temp, CKMC_ERROR_NONE);

    int cnt = 0;
    ckmc_cert_list_s *current = cert_chain_list;

    while (current) {
        current = current->next;
        cnt++;
    }
    ckmc_cert_list_all_free(cert_chain_list);

    assert_eq(cnt, chain_len);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_cert_chain_n
 * @since_tizen     2.3
 * @description     Check an error in getting a ceritifcate chain.
 * @scenario        Set only a leaf certificate.
                    Call ckmc_get_cert_chain to get a certificate chain.
 */
int utc_ckmc_get_cert_chain_n(void)
{
    int temp;
    ckmc_cert_s c_cert;

    ckmc_cert_list_s *cert_chain_list = NULL;
    ckmc_cert_list_s *untrustedcerts = NULL;

    c_cert.raw_cert = (unsigned char *) CERT_CHAIN1;
    c_cert.cert_size = strlen(CERT_CHAIN1);
    c_cert.data_format = CKMC_FORM_PEM;

    temp = ckmc_get_cert_chain(&c_cert, untrustedcerts, &cert_chain_list);
    assert_eq(temp,CKMC_ERROR_VERIFICATION_FAILED);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_cert_chain_with_alias_p
 * @since_tizen     2.3
 * @description     verify a certificate and get a certificate chain.
 * @scenario        Store a leaf ceritifcate and untrunsted certificates
                    Call ckmc_get_cert_chain with their aliases to get a certificate chain.
 */
int utc_ckmc_get_cert_chain_with_alias_p(void)
{
    int temp;
    int chain_len = 3;
    ckmc_cert_s c_cert, c_cert1;
    ckmc_policy_s cert_policy;
    char* policy_password = NULL;
    char* save_cert_alias = "cert_untrusted";

    c_cert.raw_cert = (unsigned char *) CERT_CHAIN1;
    c_cert.cert_size = strlen(CERT_CHAIN1);
    c_cert.data_format = CKMC_FORM_PEM;


    cert_policy.password = policy_password;
    cert_policy.extractable = true;

    c_cert1.raw_cert = (unsigned char *) CERT_CHAIN2;
    c_cert1.cert_size = strlen(CERT_CHAIN2);
    c_cert1.data_format = CKMC_FORM_PEM;

    temp = ckmc_save_cert(save_cert_alias, c_cert1, cert_policy);
    assert_eq(temp, CKMC_ERROR_NONE);

    ckmc_alias_list_s *cert_alias_list;
    temp = ckmc_get_cert_alias_list(&cert_alias_list);
    assert_eq(temp, CKMC_ERROR_NONE);
    assert_neq(cert_alias_list, NULL);

    ckmc_cert_list_s *cert_chain_list;
    temp = ckmc_get_cert_chain_with_alias(&c_cert, cert_alias_list, &cert_chain_list);
    assert_eq(temp, CKMC_ERROR_NONE);

    int cnt = 0;
    ckmc_cert_list_s *current = cert_chain_list;

    while (current) {
        current = current->next;
        cnt++;
    }
    ckmc_cert_list_all_free(cert_chain_list);

    assert_eq(cnt, chain_len);

    temp = ckmc_remove_cert(save_cert_alias);
    assert_eq(temp, CKMC_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_ckmc_get_cert_chain_with_alias_n
 * @since_tizen     2.3
 * @description     Check an error in getting a ceritifcate chain.
 * @scenario        Set only a leaf certificate.
                    Call ckmc_get_cert_chain to get a certificate chain with a NULL alise list .
 */
int utc_ckmc_get_cert_chain_with_alias_n(void)
{
    int temp;
    ckmc_cert_s c_cert;

    c_cert.raw_cert = (unsigned char *) CERT_CHAIN1;
    c_cert.cert_size = strlen(CERT_CHAIN1);
    c_cert.data_format = CKMC_FORM_PEM;

    ckmc_cert_list_s *cert_chain_list = NULL;
    ckmc_alias_list_s *cert_alias_list = NULL;

    temp = ckmc_get_cert_chain_with_alias(&c_cert, cert_alias_list, &cert_chain_list);
    assert_eq(temp,CKMC_ERROR_VERIFICATION_FAILED);

    return 0;
}


/**
 * @testcase        utc_ckmc_get_cert_chain_with_trustedcert_p
 * @since_tizen     2.4
 * @description     verify a certificate and get a certificate chain
 * @scenario        Set a leaf certificate, untrunsted certificates, and trusted certificates.
                    Call ckmc_get_cert_chain to get a valid certificate chain.
 */
int utc_ckmc_get_cert_chain_with_trustedcert_p(void)
{
    int temp;
    int chain_len = 3;

    ckmc_cert_s c_cert;
    ckmc_cert_s c_cert1;
    ckmc_cert_list_s untrustedcerts;
    ckmc_cert_list_s trustedcerts;

    c_cert.raw_cert = (unsigned char *) CERT_CHAIN1;
    c_cert.cert_size = strlen(CERT_CHAIN1);
    c_cert.data_format = CKMC_FORM_PEM;

    c_cert1.raw_cert = (unsigned char *) CERT_CHAIN2;
    c_cert1.cert_size = strlen(CERT_CHAIN2);
    c_cert1.data_format = CKMC_FORM_PEM;

    untrustedcerts.cert = &c_cert1;
    untrustedcerts.next = NULL;

    trustedcerts.cert = NULL;
    trustedcerts.next = NULL;

    ckmc_cert_list_s *cert_chain_list;

    temp = ckmc_get_cert_chain_with_trustedcert(
            &c_cert,
            &trustedcerts,
            &untrustedcerts,
            true,
            &cert_chain_list);
    assert_eq(temp,CKMC_ERROR_NONE);

    int cnt = 0;
    ckmc_cert_list_s *current = cert_chain_list;
    while (current) {
        current = current->next;
        cnt++;
    }
    ckmc_cert_list_all_free(cert_chain_list);

    assert_eq(cnt,chain_len);

    return 0;
}


/**
 * @testcase        utc_ckmc_get_cert_chain_with_trustedcert_n
 * @since_tizen     2.4
 * @description     Check an error in getting a ceritifcate chain.
 * @scenario        Set only a leaf certificate.
                    Call ckmc_get_cert_chain to get a certificate chain.
 */
int utc_ckmc_get_cert_chain_with_trustedcert_n(void)
{
    int temp;
    ckmc_cert_s c_cert;

    ckmc_cert_list_s *untrustedcerts = NULL;
    ckmc_cert_list_s *trustedcerts = NULL;
    ckmc_cert_list_s *cert_chain_list = NULL;

    c_cert.raw_cert = (unsigned char *) CERT_CHAIN1;
    c_cert.cert_size = strlen(CERT_CHAIN1);
    c_cert.data_format = CKMC_FORM_PEM;

    temp = ckmc_get_cert_chain_with_trustedcert(
            &c_cert,
            trustedcerts,
            untrustedcerts,
            true,
            &cert_chain_list);
    assert_eq(temp,CKMC_ERROR_VERIFICATION_FAILED);

    return 0;
}

/**
 * @testcase        utc_ckmc_ocsp_check_p
 * @since_tizen     2.4
 * @description     get a certificate status with OCSP(Online Certificate Status Protocol)
 * @scenario        Get a certificate chain and get certificate status of this chain.
 */
int utc_ckmc_ocsp_check_p(void)
{
    int temp;

    ckmc_cert_s c_cert;
    c_cert.raw_cert = (unsigned char *) OCSP_CERT;
    c_cert.cert_size = strlen(OCSP_CERT);
    c_cert.data_format = CKMC_FORM_PEM;

    ckmc_cert_s c_cert_im;
    c_cert_im.raw_cert = (unsigned char *) OCSP_CERT_IM;
    c_cert_im.cert_size = strlen(OCSP_CERT_IM);
    c_cert_im.data_format = CKMC_FORM_PEM;

    ckmc_cert_list_s untrustedcerts;
    untrustedcerts.cert = &c_cert_im;
    untrustedcerts.next = NULL;

    ckmc_cert_list_s *cert_chain_list;
    temp = ckmc_get_cert_chain(&c_cert, &untrustedcerts, &cert_chain_list);
    assert_eq(temp, CKMC_ERROR_NONE);
    assert_neq(cert_chain_list, NULL);

    ckmc_ocsp_status_e ocsp_status;
    temp = ckmc_ocsp_check(cert_chain_list, &ocsp_status);

    assert_eq(temp, CKMC_ERROR_NONE);
    assert_neq(temp, CKMC_OCSP_ERROR_INVALID_RESPONSE);

    return 0;
}


/**
 * @testcase        utc_ckmc_ocsp_check_n
 * @since_tizen     2.4
 * @description     check a certificate status with OCSP with a NULL chain
 * @scenario        ckmc_ocsp_check with a NULL chain
 */
int utc_ckmc_ocsp_check_n(void)
{
    int temp = ckmc_ocsp_check(NULL, NULL);
    assert_neq(temp, CKMC_ERROR_NONE);

    return 0;
}


/**
 * @testcase        utc_ckmc_create_key_aes_p
 * @since_tizen     3.0
 * @description     Create a key for AES algorithm.
 * @scenario        Create a key for AES algorithm.
 */
int utc_ckmc_create_key_aes_p(void)
{
    int temp;

    size_t size = 256;
    const char *aes_key_alias = "aes_p_key";
    ckmc_policy_s aes_key_policy;

    aes_key_policy.password = NULL;
    aes_key_policy.extractable = true;

    ckmc_remove_alias(aes_key_alias);

    temp = ckmc_create_key_aes(size, aes_key_alias, aes_key_policy);
    assert_eq(temp, CKMC_ERROR_NONE);

    temp = ckmc_remove_alias(aes_key_alias);
    assert_eq(temp, CKMC_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_ckmc_create_key_aes_n
 * @since_tizen     3.0
 * @description     Check an error in creating a AES key.
 * @scenario        Create a new AES key from invalid parameters.
 */
int utc_ckmc_create_key_aes_n(void)
{
    int ret;

    size_t size = 256;
    const char *aes_key_alias = "aes_n_key";
    ckmc_policy_s aes_key_policy;

    aes_key_policy.password = NULL;
    aes_key_policy.extractable = true;

    ret = ckmc_create_key_aes(size, NULL, aes_key_policy);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);

    ret = ckmc_create_key_aes(999, aes_key_alias, aes_key_policy);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_ckmc_encrypt_data_p
 * @since_tizen     3.0
 * @description     Encrypt data with AES algorithm.
 * @scenario        Create AES key and encrypt data with it.
 */
int utc_ckmc_encrypt_data_p(void)
{
    int ret;

    size_t size = 256;
    const char *aes_key_alias = "encrypt_data_p_key";
    ckmc_policy_s aes_key_policy;

    ckmc_param_list_h params = NULL;
    ckmc_raw_buffer_s plaintext;
    ckmc_raw_buffer_s iv_buffer;

    ckmc_raw_buffer_s *encrypted = NULL;

    unsigned char data[512] = {0, };
    unsigned char iv[16] = {0, };

    aes_key_policy.password = NULL;
    aes_key_policy.extractable = true;
    plaintext.data = data;
    plaintext.size = sizeof(data);
    iv_buffer.data = iv;
    iv_buffer.size = sizeof(iv);

    ckmc_remove_alias(aes_key_alias);

    ret = ckmc_create_key_aes(size, aes_key_alias, aes_key_policy);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_generate_new_params(CKMC_ALGO_AES_CBC, &params);
    assert_eq(ret, CKMC_ERROR_NONE);
    ret = ckmc_param_list_set_buffer(params, CKMC_PARAM_ED_IV, &iv_buffer);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_encrypt_data(params, aes_key_alias, NULL, plaintext, &encrypted);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_remove_alias(aes_key_alias);
    assert_eq(ret, CKMC_ERROR_NONE);

    ckmc_param_list_free(params);
    ckmc_buffer_free(encrypted);

    return 0;
}

/**
 * @testcase        utc_ckmc_encrypt_data_n
 * @since_tizen     3.0
 * @description     Check an error in encrypting data.
 * @scenario        Encrypt data with invalid parameters.
 */
int utc_ckmc_encrypt_data_n(void)
{
    int ret;

    const char *aes_key_alias = "encrypt_data_n_key_alias";
    ckmc_param_list_h params = NULL;
    ckmc_raw_buffer_s plaintext;

    ckmc_raw_buffer_s *encrypted = NULL;

    ret = ckmc_encrypt_data(NULL, aes_key_alias, NULL, plaintext, &encrypted);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);

    ret = ckmc_encrypt_data(params, NULL,  NULL, plaintext, &encrypted);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);

    ret = ckmc_encrypt_data(params, aes_key_alias, NULL, plaintext, NULL);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_ckmc_decrypt_data_p
 * @since_tizen     3.0
 * @description     Decrypt data with AES CTR algorithm.
 * @scenario        Create AES key and encrypt data with it.
                    Decrypt data.
 */
int utc_ckmc_decrypt_data_p(void)
{
    int ret;

    size_t size = 256;
    const char *aes_key_alias = "decrypt_data_p_key";
    ckmc_policy_s aes_key_policy;

    ckmc_param_list_h params = NULL;
    ckmc_raw_buffer_s plaintext;
    ckmc_raw_buffer_s iv_buffer;

    ckmc_raw_buffer_s *encrypted = NULL;
    ckmc_raw_buffer_s *decrypted = NULL;

    unsigned char data[86] = {0, };
    unsigned char iv[16] = {0, };

    aes_key_policy.password = NULL;
    aes_key_policy.extractable = true;
    plaintext.data = data;
    plaintext.size = sizeof(data);
    iv_buffer.data = iv;
    iv_buffer.size = sizeof(iv);

    ckmc_remove_alias(aes_key_alias);

    ret = ckmc_create_key_aes(size, aes_key_alias, aes_key_policy);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_generate_new_params(CKMC_ALGO_AES_CTR, &params);
    assert_eq(ret, CKMC_ERROR_NONE);
    ret = ckmc_param_list_set_buffer(params, CKMC_PARAM_ED_IV, &iv_buffer);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_encrypt_data(params, aes_key_alias, NULL, plaintext, &encrypted);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_decrypt_data(params, aes_key_alias, NULL, *encrypted, &decrypted);
    assert_eq(ret, CKMC_ERROR_NONE);

    assert_eq(memcmp(plaintext.data, decrypted->data, plaintext.size), 0);

    ret = ckmc_remove_alias(aes_key_alias);
    assert_eq(ret, CKMC_ERROR_NONE);

    ckmc_param_list_free(params);
    ckmc_buffer_free(encrypted);
    ckmc_buffer_free(decrypted);

    return 0;
}

/**
 * @testcase        utc_ckmc_decrypt_data_p_2
 * @since_tizen     3.0
 * @description     Decrypt data with AES CBC algorithm.
 * @scenario        Create AES key and encrypt data with it.
                    Decrypt data.
 */
int utc_ckmc_decrypt_data_p_2(void)
{
    int ret;

    size_t size = 256;
    const char *aes_key_alias = "decrypt_data_p_2_key";
    ckmc_policy_s aes_key_policy;

    ckmc_param_list_h params = NULL;
    ckmc_raw_buffer_s plaintext;
    ckmc_raw_buffer_s iv_buffer;

    ckmc_raw_buffer_s *encrypted = NULL;
    ckmc_raw_buffer_s *decrypted = NULL;

    unsigned char data[86] = {0, };
    unsigned char iv[16] = {0, };

    aes_key_policy.password = NULL;
    aes_key_policy.extractable = true;
    plaintext.data = data;
    plaintext.size = sizeof(data);
    iv_buffer.data = iv;
    iv_buffer.size = sizeof(iv);

    ckmc_remove_alias(aes_key_alias);

    ret = ckmc_create_key_aes(size, aes_key_alias, aes_key_policy);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_generate_new_params(CKMC_ALGO_AES_CBC, &params);
    assert_eq(ret, CKMC_ERROR_NONE);
    ret = ckmc_param_list_set_buffer(params, CKMC_PARAM_ED_IV, &iv_buffer);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_encrypt_data(params, aes_key_alias, NULL, plaintext, &encrypted);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_decrypt_data(params, aes_key_alias, NULL, *encrypted, &decrypted);
    assert_eq(ret, CKMC_ERROR_NONE);

    assert_eq(memcmp(plaintext.data, decrypted->data, plaintext.size), 0);

    ret = ckmc_remove_alias(aes_key_alias);
    assert_eq(ret, CKMC_ERROR_NONE);

    ckmc_param_list_free(params);
    ckmc_buffer_free(encrypted);
    ckmc_buffer_free(decrypted);

    return 0;
}

/**
 * @testcase        utc_ckmc_decrypt_data_p_3
 * @since_tizen     3.0
 * @description     Decrypt data with AES GCM algorithm.
 * @scenario        Create AES key and encrypt data with it.
                    Decrypt data.
 */
int utc_ckmc_decrypt_data_p_3(void)
{
    int ret;

    size_t size = 256;
    const char *aes_key_alias = "decrypt_data_p_3_key";
    ckmc_policy_s aes_key_policy;

    ckmc_param_list_h params = NULL;
    ckmc_raw_buffer_s plaintext;
    ckmc_raw_buffer_s iv_buffer;
    ckmc_raw_buffer_s aad_buffer;

    ckmc_raw_buffer_s* encrypted = NULL;
    ckmc_raw_buffer_s* decrypted = NULL;

    unsigned char data[86] = {0, };
    unsigned char iv[16] = {0, };
    unsigned char aad[32] = {1, };

    aes_key_policy.password = NULL;
    aes_key_policy.extractable = true;
    plaintext.data = data;
    plaintext.size = sizeof(data);
    iv_buffer.data = iv;
    iv_buffer.size = sizeof(iv);
    aad_buffer.data = aad;
    aad_buffer.size = sizeof(aad);

    ckmc_remove_alias(aes_key_alias);

    ret = ckmc_create_key_aes(size, aes_key_alias, aes_key_policy);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_generate_new_params(CKMC_ALGO_AES_GCM, &params);
    assert_eq(ret, CKMC_ERROR_NONE);
    ret = ckmc_param_list_set_integer(params, CKMC_PARAM_ED_TAG_LEN, 128);
    assert_eq(ret, CKMC_ERROR_NONE);
    ret = ckmc_param_list_set_buffer(params, CKMC_PARAM_ED_IV, &iv_buffer);
    assert_eq(ret, CKMC_ERROR_NONE);
    ret = ckmc_param_list_set_buffer(params, CKMC_PARAM_ED_AAD, &aad_buffer);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_encrypt_data(params, aes_key_alias, NULL, plaintext, &encrypted);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_decrypt_data(params, aes_key_alias, NULL, *encrypted, &decrypted);
    assert_eq(ret, CKMC_ERROR_NONE);

    assert_eq(memcmp(plaintext.data, decrypted->data, plaintext.size), 0);

    ret = ckmc_remove_alias(aes_key_alias);
    assert_eq(ret, CKMC_ERROR_NONE);

    ckmc_param_list_free(params);
    ckmc_buffer_free(encrypted);
    ckmc_buffer_free(decrypted);

    return 0;
}


/**
 * @testcase        utc_ckmc_decrypt_data_p_4
 * @since_tizen     3.0
 * @description     Decrypt data with AES CFB algorithm.
 * @scenario        Create AES key and encrypt data with it.
                    Decrypt data.
 */
int utc_ckmc_decrypt_data_p_4(void)
{
    int ret;

    size_t size = 256;
    const char *aes_key_alias = "decrypt_data_p_4_key";
    ckmc_policy_s aes_key_policy;

    ckmc_param_list_h params = NULL;
    ckmc_raw_buffer_s plaintext;
    ckmc_raw_buffer_s iv_buffer;

    ckmc_raw_buffer_s *encrypted = NULL;
    ckmc_raw_buffer_s *decrypted = NULL;

    unsigned char data[86] = {0, };
    unsigned char iv[16] = {0, };

    aes_key_policy.password = NULL;
    aes_key_policy.extractable = true;
    plaintext.data = data;
    plaintext.size = sizeof(data);
    iv_buffer.data = iv;
    iv_buffer.size = sizeof(iv);

    ckmc_remove_alias(aes_key_alias);

    ret = ckmc_create_key_aes(size, aes_key_alias, aes_key_policy);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_generate_new_params(CKMC_ALGO_AES_CFB, &params);
    assert_eq(ret, CKMC_ERROR_NONE);
    ret = ckmc_param_list_set_buffer(params, CKMC_PARAM_ED_IV, &iv_buffer);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_encrypt_data(params, aes_key_alias, NULL, plaintext, &encrypted);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_decrypt_data(params, aes_key_alias, NULL, *encrypted, &decrypted);
    assert_eq(ret, CKMC_ERROR_NONE);

    assert_eq(memcmp(plaintext.data, decrypted->data, plaintext.size), 0);

    ret = ckmc_remove_alias(aes_key_alias);
    assert_eq(ret, CKMC_ERROR_NONE);

    ckmc_param_list_free(params);
    ckmc_buffer_free(encrypted);
    ckmc_buffer_free(decrypted);

    return 0;
}

/**
 * @testcase        utc_ckmc_decrypt_data_p_5
 * @since_tizen     3.0
 * @description     Decrypt data with RSA algorithm.
 * @scenario        Create a RSA key pair and encrypt data with its public key.
                    Decrypt data with its private key.
 */
int utc_ckmc_decrypt_data_p_5(void)
{
    int ret;

    size_t size = 1024;
    const char *private_key_alias = "decrypt_data_p_5_prikey";
    const char *public_key_alias = "decrypt_data_p_5_pubkey";
    ckmc_policy_s policy_private_key;
    ckmc_policy_s policy_public_key;

    ckmc_param_list_h params = NULL;
    ckmc_raw_buffer_s plaintext;

    ckmc_raw_buffer_s *encrypted = NULL;
    ckmc_raw_buffer_s *decrypted = NULL;

    unsigned char data[86] = {0, };

    policy_private_key.password = NULL;
    policy_private_key.extractable = true;
    policy_public_key.password = NULL;
    policy_public_key.extractable = true;
    plaintext.data = data;
    plaintext.size = sizeof(data);

    ckmc_remove_alias(private_key_alias);
    ckmc_remove_alias(public_key_alias);

    ret = ckmc_create_key_pair_rsa(size, private_key_alias, public_key_alias, policy_private_key, policy_public_key);
    assert_eq(ret,CKMC_ERROR_NONE);

    ret = ckmc_generate_new_params(CKMC_ALGO_RSA_OAEP, &params);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_encrypt_data(params, public_key_alias, NULL, plaintext, &encrypted);
    assert_eq(ret, CKMC_ERROR_NONE);

    ret = ckmc_decrypt_data(params, private_key_alias, NULL, *encrypted, &decrypted);
    assert_eq(ret, CKMC_ERROR_NONE);

    assert_eq(memcmp(plaintext.data, decrypted->data, plaintext.size), 0);

    ret = ckmc_remove_key (private_key_alias);
    assert_eq(ret, CKMC_ERROR_NONE);
    ret = ckmc_remove_key (public_key_alias);
    assert_eq(ret, CKMC_ERROR_NONE);

    ckmc_param_list_free(params);
    ckmc_buffer_free(encrypted);
    ckmc_buffer_free(decrypted);

    return 0;
}

/**
 * @testcase        utc_ckmc_decrypt_data_n
 * @since_tizen     3.0
 * @description     Decrypt data with invalid paramters.
 * @scenario        Decrypt data with invalid paramters.
 */
int utc_ckmc_decrypt_data_n(void)
{
    int ret;

    const char *aes_key_alias = "decrypt_data_n_key";

    ckmc_param_list_h params = NULL;
    ckmc_raw_buffer_s encrypted;

    ckmc_raw_buffer_s *decrypted = NULL;

    ret = ckmc_decrypt_data(NULL, aes_key_alias, NULL, encrypted, &decrypted);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);

    ret = ckmc_decrypt_data(params, NULL,  NULL, encrypted, &decrypted);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);

    ret = ckmc_decrypt_data(params, aes_key_alias, NULL, encrypted, NULL);
    assert_eq(ret, CKMC_ERROR_INVALID_PARAMETER);

    return 0;
}
