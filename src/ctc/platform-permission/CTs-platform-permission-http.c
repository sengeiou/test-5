#include "CTs-platform-permission-common.h"
#include <http.h>
#define  HTTP_FEATURE "http://tizen.org/feature/network.internet"
http_session_h g_hHttpSession;
http_transaction_h g_hHttpTransaction;
bool g_bHttpInit =false;
/**
* @function         HttpGetError
* @description      Maps error enumerators to string values
* @parameter        nRet : error code returned
* @return           error string
*/
char* HttpGetError(int nRet)
{
    char *szErrorVal = "Unknown Error";

    switch ( nRet )
    {
        case HTTP_ERROR_NONE:                    szErrorVal = "HTTP_ERROR_NONE";                        break;
        case HTTP_ERROR_OUT_OF_MEMORY:            szErrorVal = "HTTP_ERROR_OUT_OF_MEMORY";            break;
        case HTTP_ERROR_PERMISSION_DENIED:        szErrorVal = "HTTP_ERROR_PERMISSION_DENIED";        break;
        case HTTP_ERROR_INVALID_PARAMETER:        szErrorVal = "HTTP_ERROR_INVALID_PARAMETER";        break;
        case HTTP_ERROR_INVALID_OPERATION:        szErrorVal = "HTTP_ERROR_INVALID_OPERATION";        break;
        case HTTP_ERROR_OPERATION_FAILED:        szErrorVal = "HTTP_ERROR_OPERATION_FAILED";            break;
        case HTTP_ERROR_COULDNT_RESOLVE_HOST:    szErrorVal = "HTTP_ERROR_COULDNT_RESOLVE_HOST";        break;
        case HTTP_ERROR_COULDNT_CONNECT:        szErrorVal = "HTTP_ERROR_COULDNT_CONNECT";            break;
        case HTTP_ERROR_OPERATION_TIMEDOUT:        szErrorVal = "HTTP_ERROR_OPERATION_TIMEDOUT";        break;
        case HTTP_ERROR_SSL_CONNECT_ERROR:        szErrorVal = "HTTP_ERROR_SSL_CONNECT_ERROR";        break;
        case HTTP_ERROR_NOT_SUPPORTED:            szErrorVal = "HTTP_ERROR_NOT_SUPPORTED";            break;
    }
    return szErrorVal;
}

/**
* @function		CTs_platform_permission_http_startup
* @description		Called before each test
* @parameter		NA
* @return			NA
*/
void CTs_platform_permission_http_startup(void)
{
    struct stat stBuff;
    if ( stat(ERR_LOG, &stBuff) == 0 )
    {
	if (remove(ERR_LOG))
	{
		FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
	}
    }
    g_bHttpInit = true;

    int nRet = http_init();
    if ( nRet != HTTP_ERROR_NONE )
    {
        FPRINTF("[Line : %d][%s] http_init failed API return %s error \\n", __LINE__, API_NAMESPACE, HttpGetError(nRet));
        g_bHttpInit = false;
        return;
    }

    nRet = http_session_create(HTTP_SESSION_MODE_NORMAL, &g_hHttpSession);
    if( nRet != HTTP_ERROR_NONE )
    {
        FPRINTF("[Line : %d][%s] http_session_create failed API return %s error \\n", __LINE__, API_NAMESPACE, HttpGetError(nRet));
        g_bHttpInit = false;
        return;
    }
    if(NULL == g_hHttpSession )
    {
       FPRINTF("[Line : %d][%s] g_hHttpSession handle is NULL error \\n", __LINE__, API_NAMESPACE);
       g_bHttpInit = false;
       return;
    
    }
    nRet = http_session_open_transaction(g_hHttpSession, HTTP_METHOD_GET, &g_hHttpTransaction);
    if( nRet != HTTP_ERROR_NONE )
    {
        FPRINTF("[Line : %d][%s] http_session_open_transaction failed API return %s error \\n", __LINE__, API_NAMESPACE, HttpGetError(nRet));
        g_bHttpInit = false;
        return;
    }
    if(g_hHttpTransaction == NULL)
    {
        FPRINTF("[Line : %d][%s] g_hHttpTransaction handle is null \\n", __LINE__, API_NAMESPACE);
        g_bHttpInit = false;
        return;
    }
    return;
}


/**
* @function		CTs_platform_permission_http_cleanup
* @description		Called before each test
* @parameter		NA
* @return			NA
*/
void CTs_platform_permission_http_cleanup(void)
{
    int nRet = 0;
    if( g_hHttpTransaction != NULL)
    {
        nRet = http_transaction_destroy(g_hHttpTransaction);
		if (nRet != HTTP_ERROR_NONE)
        {
            FPRINTF("[Line : %d][%s] http_transaction_destroy failed API return %s error \\n", __LINE__, API_NAMESPACE, HttpGetError(nRet));
        }
        nRet = http_session_destroy(g_hHttpSession);
        if (nRet != HTTP_ERROR_NONE)
        {
            FPRINTF("[Line : %d][%s] http_session_destroy failed API return %s error \\n", __LINE__, API_NAMESPACE, HttpGetError(nRet));
        }
    }
    nRet = http_deinit();
    if (nRet != HTTP_ERROR_NONE)
    {
        FPRINTF("[Line : %d][%s] http_deinit failed API return %s error \\n", __LINE__, API_NAMESPACE, HttpGetError(nRet));
    }

    return;
}
//& purpose: to check privilege http://tizen.org/privilege/internet
//& type: auto
/**
* @testcase               CTc_Http_PrivilegeInternet_http_transaction_submit
* @since_tizen            3.0
* @author                 SRID(manoj.g2)
* @reviewer               SRID(a.pandia1)
* @type                    auto
* @description            Submits the Http request
* @scenario                call http_transaction_submit
* @apicovered              http_transaction_submit
* @passcase                If all privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase                If all privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition            http_session_open_transaction() should be successfully called
* @postcondition        NA
*/

int CTc_Http_PrivilegeInternet_http_transaction_submit(void)
{
    START_TEST;
    int nRet = 1;
    const char uri[100] = "http://www.tizen.org";
    #ifdef WEARABLE
    bool bIsHttpFeatureSupported =false;
    IS_FEATURE_SUPPORTED(HTTP_FEATURE, bIsHttpFeatureSupported, API_NAMESPACE);
	 if ( false == bIsHttpFeatureSupported )
		{
			FPRINTF("[Line : %d][%s] Feature is not supported\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	 #endif
	 if( false ==  g_bHttpInit)
	 {
	      FPRINTF("[Line : %d][%s] Http initialization failed \\n", __LINE__, API_NAMESPACE);
			return 1;
	 }
    nRet = http_transaction_request_set_uri(g_hHttpTransaction, uri);
    PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_request_set_uri", HttpGetError(nRet));

    //Target API
    nRet = http_transaction_submit(g_hHttpTransaction);
    PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "http_transaction_submit", HttpGetError(nRet));

    return 0;
}

