//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-http-common.h"

//& set: Http

/** @addtogroup itc-http
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_http_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_http_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	g_bFeatureUnsupported = false;
   
	int nRet = 0;
	if (!g_bHttpInit) {
		nRet = http_init();
		g_bHttpInit = true;
	}

#ifdef WEARABLE
	if ( !TCTCheckSystemInfoFeatureSupported(HTTP_FEATURE, API_NAMESPACE) )
	{
		
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] http_init API call returned mismatch %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, HttpGetError(nRet));
			g_bHttpInit = false;
		}
		else
		{
			FPRINTF("[Line : %d][%s] http_init API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, HttpGetError(nRet));
			g_bFeatureUnsupported = true;
		}
		return;
	}
#endif	
	
	if ( nRet != HTTP_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] http_init failed API return %s error \\n", __LINE__, API_NAMESPACE, HttpGetError(nRet));
		g_bHttpInit = false;
		return;
	}
	
	return;
}


/**
 * @function 		ITs_http_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_http_cleanup(void)
{
	int nRet = 0;

	if (g_bHttpInit) {
		nRet = http_deinit();
		if (nRet != HTTP_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] http_deinit failed API return %s error \\n", __LINE__, API_NAMESPACE, HttpGetError(nRet));
		}

		g_bHttpInit = false;
	}

	return;
}

/** @addtogroup itc-http-testcases
*  @brief 		Integration testcases for module http
*  @ingroup 	itc-http
*  @{
*/


//& purpose: Initializes/Deinitializes the Http module.
//& type: auto 
/**
* @testcase   			ITc_http_init_deinit_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Initializes/Deinitializes the Http module
* @scenario				call http_init, http_deinit
* @apicovered			http_init , http_deinit 					
* @passcase				When http_init and http_deinit is successful.
* @failcase				If API http_init and http_deinit fails.
* @precondition			http_init() should be successfully called
* @postcondition		NA
*/
int ITc_http_init_deinit_p(void)
{
	START_TEST;

	http_deinit();
	
	//Target API
	int nRet = http_init();	
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_init", HttpGetError(nRet));
		
	//Target API
	nRet = http_deinit();	
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_deinit", HttpGetError(nRet));
	
	g_bHttpInit = false;

	return 0;
}

//& purpose: Creates/Destroys the Http session handle.
//& type: auto 
/**
* @testcase   			ITc_http_session_create_destroy_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Creates/Destroys the Http session handle.
* @scenario				call http_session_create, http_session_destroy
* @apicovered			http_session_create , http_session_destroy 					
* @passcase				When http_session_create and http_session_destroy is successful.
* @failcase				If API http_session_create and http_session_destroy fails.
* @precondition			http_init() should be successfully called
* @postcondition		NA
*/
int ITc_http_session_create_destroy_p(void)
{
	START_TEST;

	http_session_h hHttpSession = NULL;
	
	//Target API
	int nRet = http_session_create(HTTP_SESSION_MODE_NORMAL, &hHttpSession);	
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_session_create", HttpGetError(nRet));
	CHECK_HANDLE(hHttpSession,"http_session_create");
	
	//Target API
	nRet = http_session_destroy(hHttpSession);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_session_destroy", HttpGetError(nRet));
	
	return 0;
}

//& purpose: Sets/Gets the value to redirect the HTTP request automatically
//& type: auto 
/**
* @testcase   			ITc_http_session_set_get_auto_redirection_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Sets/Gets the value to redirect the HTTP request automatically
* @scenario				call http_session_create, http_session_set_auto_redirection, http_session_get_auto_redirection, http_session_destroy
* @apicovered			http_session_create , http_session_set_auto_redirection, http_session_get_auto_redirection, http_session_destroy 					
* @passcase				When http_session_create, http_session_set_auto_redirection, http_session_get_auto_redirection, http_session_destroy is successful.
* @failcase				If API http_session_set_auto_redirection and http_session_get_auto_redirection fails
* @precondition			http_init() should be successfully called
* @postcondition		NA
*/
int ITc_http_session_set_get_auto_redirection_p(void)
{
	START_TEST;

	http_session_h hHttpSession = NULL;
	bool bAutoRedirect = true; 
	bool bIsAutoRedirect = false; 
	
	int nRet = http_session_create(HTTP_SESSION_MODE_NORMAL, &hHttpSession);	
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_session_create", HttpGetError(nRet));
	CHECK_HANDLE(hHttpSession,"http_session_create");
	
	//Target API
	nRet = http_session_set_auto_redirection(hHttpSession, bAutoRedirect);	
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_session_set_auto_redirection", HttpGetError(nRet),http_session_destroy(hHttpSession));
	
	//Target API
	nRet = http_session_get_auto_redirection(hHttpSession, &bIsAutoRedirect);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_session_get_auto_redirection", HttpGetError(nRet),http_session_destroy(hHttpSession));
	
	if( bAutoRedirect != bIsAutoRedirect )
	{
		FPRINTF("[Line : %d][%s] bIsAutoRedirect comparision fails! \\n", __LINE__, API_NAMESPACE);
		http_session_destroy(hHttpSession);
		return 1;
	}
	
	nRet = http_session_destroy(hHttpSession);
	PRINT_RESULT_NORETURN(HTTP_ERROR_NONE, nRet, "http_session_destroy", HttpGetError(nRet));
	
	return 0;
}

//& purpose: Gets the number of active transactions in the current session
//& type: auto 
/**
* @testcase   			ITc_http_session_get_active_transaction_count_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Gets the number of active transactions in the current session
* @scenario				call http_session_create, http_session_get_active_transaction_count, http_session_destroy
* @apicovered			http_session_create , http_session_get_active_transaction_count, http_session_destroy 					
* @passcase				When http_session_create, http_session_get_active_transaction_count, http_session_destroy is successful.
* @failcase				If API http_session_get_active_transaction_count fails
* @precondition			http_init() should be successfully called
* @postcondition		NA
*/
int ITc_http_session_get_active_transaction_count_p(void)
{
	START_TEST;

	http_session_h hHttpSession = NULL;
	int nActiveTransactionCount = -1;
		
	int nRet = http_session_create(HTTP_SESSION_MODE_NORMAL, &hHttpSession);	
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_session_create", HttpGetError(nRet));
	CHECK_HANDLE(hHttpSession,"http_session_create");
	
	//Target API
	nRet = http_session_get_active_transaction_count(hHttpSession, &nActiveTransactionCount);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_session_get_active_transaction_count", HttpGetError(nRet),http_session_destroy(hHttpSession));
	
	if( nActiveTransactionCount == -1 )
	{
		FPRINTF("[Line : %d][%s] nActiveTransactionCount not set!! \\n", __LINE__, API_NAMESPACE);
		http_session_destroy(hHttpSession);
		return 1;
	}
	
	nRet = http_session_destroy(hHttpSession);
	PRINT_RESULT_NORETURN(HTTP_ERROR_NONE, nRet, "http_session_destroy", HttpGetError(nRet));
	
	return 0;
}

//& purpose: Gets the maximum number of transactions for the current session
//& type: auto 
/**
* @testcase   			ITc_http_session_get_max_transaction_count_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Gets the maximum number of transactions for the current session
* @scenario				call http_session_create, http_session_get_max_transaction_count, http_session_destroy
* @apicovered			http_session_create , http_session_get_max_transaction_count, http_session_destroy 					
* @passcase				When http_session_create, http_session_get_max_transaction_count, http_session_destroy is successful.
* @failcase				If API http_session_get_max_transaction_count fails
* @precondition			http_init() should be successfully called
* @postcondition		NA
*/
int ITc_http_session_get_max_transaction_count_p(void)
{
	START_TEST;

	http_session_h hHttpSession = NULL;
	int nGetMaxTransactionCount = -1;
		
	int nRet = http_session_create(HTTP_SESSION_MODE_NORMAL, &hHttpSession);	
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_session_create", HttpGetError(nRet));
	CHECK_HANDLE(hHttpSession,"http_session_create");
	
	//Target API
	nRet = http_session_get_max_transaction_count(hHttpSession, &nGetMaxTransactionCount);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_session_get_max_transaction_count", HttpGetError(nRet),http_session_destroy(hHttpSession));
	
	if( nGetMaxTransactionCount == -1 )
	{
		FPRINTF("[Line : %d][%s] nGetMaxTransactionCount not set!! \\n", __LINE__, API_NAMESPACE);
		http_session_destroy(hHttpSession);
		return 1;
	}
	
	nRet = http_session_destroy(hHttpSession);
	PRINT_RESULT_NORETURN(HTTP_ERROR_NONE, nRet, "http_session_destroy", HttpGetError(nRet));
	
	return 0;
}


//& purpose: Opens/destroys Http transaction from the Http Session
//& type: auto 
/**
* @testcase   			ITc_http_session_open_destroy_transaction_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Opens/destroys Http transaction from the Http Session
* @scenario				call http_session_create, http_session_open_transaction, http_transaction_destroy http_session_destroy
* @apicovered			http_session_create , http_session_open_transaction,http_transaction_destroy,  http_session_destroy 					
* @passcase				When http_session_create, http_session_open_transaction,http_transaction_destroy, http_session_destroy is successful.
* @failcase				If API http_session_open_transaction and http_transaction_destroyfails
* @precondition			http_init() should be successfully called
* @postcondition		NA
*/
int ITc_http_session_open_destroy_transaction_p(void)
{
	START_TEST;

	http_session_h hHttpSession = NULL;
	http_transaction_h hHttpTransaction;
	http_method_e eHttpMethodType[] = {
		HTTP_METHOD_GET,
		HTTP_METHOD_OPTIONS,
		HTTP_METHOD_HEAD,
		HTTP_METHOD_DELETE,
		HTTP_METHOD_TRACE,
		HTTP_METHOD_POST,
		HTTP_METHOD_PUT,
		HTTP_METHOD_CONNECT
	};

	int nEnumSize = sizeof(eHttpMethodType) / sizeof(eHttpMethodType[0]);
	int nEnumCounter = 0;

	int nRet = http_session_create(HTTP_SESSION_MODE_NORMAL, &hHttpSession);	
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_session_create", HttpGetError(nRet));
	CHECK_HANDLE(hHttpSession,"http_session_create");
		
	for ( nEnumCounter=0;nEnumCounter<nEnumSize;nEnumCounter++)
	{
		//Target API
		nRet = http_session_open_transaction(hHttpSession, eHttpMethodType[nEnumCounter], &hHttpTransaction);
		PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_session_open_transaction", HttpGetError(nRet),http_session_destroy(hHttpSession));
		CHECK_HANDLE_CLEANUP(hHttpTransaction,"http_session_open_transaction",http_session_destroy(hHttpSession));
		
		//Target API
		nRet = http_transaction_destroy(hHttpTransaction);
		PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_destroy", HttpGetError(nRet),http_session_destroy(hHttpSession));
	}
		
	nRet = http_session_destroy(hHttpSession);
	PRINT_RESULT_NORETURN(HTTP_ERROR_NONE, nRet, "http_session_destroy", HttpGetError(nRet));
	
	return 0;
}



//& purpose: All http_transactions should be set to NULL after using it
//& type: auto 
/**
* @testcase   			ITc_http_session_destroy_all_transactions_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			All http_transactions should be set to NULL after using it
* @scenario				call http_session_create, http_session_destroy_all_transactions, http_session_destroy
* @apicovered			http_session_create , http_session_destroy_all_transactions, http_session_destroy 					
* @passcase				When http_session_create, http_session_destroy_all_transactions, http_session_destroy is successful.
* @failcase				If API http_session_destroy_all_transactions fails
* @precondition			http_init() should be successfully called
* @postcondition		NA
*/
int ITc_http_session_destroy_all_transactions_p(void)
{
	START_TEST;

	http_session_h hHttpSession = NULL;
	http_transaction_h hHttpTransaction;
	http_method_e eHttpMethodType[] = {
		HTTP_METHOD_GET,
		HTTP_METHOD_OPTIONS,
		HTTP_METHOD_HEAD,
		HTTP_METHOD_DELETE,
		HTTP_METHOD_TRACE,
		HTTP_METHOD_POST,
		HTTP_METHOD_PUT,
		HTTP_METHOD_CONNECT
	};

	int nEnumSize = sizeof(eHttpMethodType) / sizeof(eHttpMethodType[0]);
	int nEnumCounter = 0;

	int nRet = http_session_create(HTTP_SESSION_MODE_NORMAL, &hHttpSession);	
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_session_create", HttpGetError(nRet));
	CHECK_HANDLE(hHttpSession,"http_session_create");
		
	for ( nEnumCounter=0;nEnumCounter<nEnumSize;nEnumCounter++)
	{	
		nRet = http_session_open_transaction(hHttpSession, eHttpMethodType[nEnumCounter], &hHttpTransaction);
		PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_session_open_transaction", HttpGetError(nRet),http_session_destroy(hHttpSession));
		CHECK_HANDLE_CLEANUP(hHttpTransaction,"http_session_open_transaction",http_session_destroy(hHttpSession));	
	}
	
	//Target API
	nRet = http_session_destroy_all_transactions(hHttpSession);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_session_destroy_all_transactions", HttpGetError(nRet),http_session_destroy(hHttpSession));
	
	nRet = http_session_destroy(hHttpSession);
	PRINT_RESULT_NORETURN(HTTP_ERROR_NONE, nRet, "http_session_destroy", HttpGetError(nRet));
	
	return 0;
}


/** @} */
/** @} */
