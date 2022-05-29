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

http_session_h g_hHttpSession = NULL;
http_transaction_h g_hHttpTransaction;
bool b_HttpTransactionHeaderCB = false;
bool b_HttpTransactionBodyCB = false;
bool b_HttpTransactionWriteCB = false;
bool b_HttpTransactionCompletedCB = false;
bool b_HttpTransactionProgressCB = false;
bool b_HttpTransactionProgressPauseResumeCB = false;
bool g_bIsValid = true;
bool g_Pause = false;
bool g_Resume = false;
//& set: Http

/** @addtogroup itc-http
*  @ingroup itc
*  @{
*/


/**
* @function 		HttpTransactionHeaderCB
* @description	 	Called when the http header is received
* @parameter		http_transaction_h, char *header, size_t header_len, void *user_data
* @return 			NA
*/
static void HttpTransactionHeaderCB(http_transaction_h http_transaction, char *header, size_t header_len, void *user_data)
{

	FPRINTF("[Line : %d][%s] HttpTransactionHeaderCB callback called\\n", __LINE__, API_NAMESPACE);

	b_HttpTransactionHeaderCB = true;
	
	g_bCallbackHit = true;

	return;
}

/**
* @function 		HttpTransactionBodyCB
* @description	 	Called when the http response is received
* @parameter		http_transaction_h, char *body, size_t header_len, void *user_data
* @return 			NA
*/
static void HttpTransactionBodyCB(http_transaction_h http_transaction, char *body, size_t size, size_t count, void *user_data)
{

	FPRINTF("[Line : %d][%s] HttpTransactionBodyCB callback called\\n", __LINE__, API_NAMESPACE);

	b_HttpTransactionBodyCB = true;
	
	g_bCallbackHit = true;

	return;
}

/**
* @function 		HttpTransactionWriteCB
* @description	 	Called when the http ready to write event is received
* @parameter		http_transaction_h, int recommended_chunk_size, void *user_data
* @return 			NA
*/
static void HttpTransactionWriteCB(http_transaction_h http_transaction, int recommended_chunk_size, void *user_data)
{

	FPRINTF("[Line : %d][%s] HttpTransactionWriteCB callback called\\n", __LINE__, API_NAMESPACE);

	b_HttpTransactionWriteCB = true;
	g_bCallbackHit = true;

	return;
}

/**
* @function 		HttpTransactionCompletedCB
* @description	 	Called when the http transaction is completed
* @parameter		http_transaction_h, void *user_data
* @return 			NA
*/
static void HttpTransactionCompletedCB(http_transaction_h transaction, void *user_data)
{
#if DEBUG	
	FPRINTF("[Line : %d][%s] HttpTransactionCompletedCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	b_HttpTransactionCompletedCB = true;	
	g_bCallbackHit = true;

	if ( g_pHttpMainLoop )
	{
		g_main_loop_quit(g_pHttpMainLoop);
		g_pHttpMainLoop = NULL;
	}

	return;
}

static void HttpTransactionAbortedCB(http_transaction_h transaction, int reason, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] HttpTransactionAbortedCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;

	if ( g_pHttpMainLoop )
	{
		g_main_loop_quit(g_pHttpMainLoop);
		g_pHttpMainLoop = NULL;
	}

	return;
}

/**
* @function 		HttpTransactionCompletedGetStatusTextVersionRealmCB
* @description	 	Called when the http transaction is completed
* @parameter		http_transaction_h, void *user_data
* @return 			NA
*/
static void HttpTransactionCompletedGetStatusTextVersionRealmCB(http_transaction_h transaction, void *user_data)
{
	int nRet;

	FPRINTF("[Line : %d][%s] HttpTransactionCompletedGetStatusTextVersionRealmCB callback called\\n", __LINE__, API_NAMESPACE);
	b_HttpTransactionCompletedCB = true;	
	g_bCallbackHit = true;
	http_version_e r_version = -1;
	http_status_code_e r_status = -1;	
	char *r_status_text = NULL;
	char *r_realm = NULL;
	g_bIsValid = true;	
	
	
	//Target API
	nRet = http_transaction_response_get_status_code(transaction, &r_status);
	if(nRet != HTTP_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] http_transaction_response_get_status_code failed : [%s]\\n", __LINE__, API_NAMESPACE,HttpGetError(nRet));
		g_bIsValid = false;
		if (g_pHttpMainLoop) {
			g_main_loop_quit(g_pHttpMainLoop);
			g_pHttpMainLoop = NULL;
		}
		return;
	}
	if( r_status < HTTP_STATUS_UNDEFINED || r_status > HTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED )
	{
		FPRINTF("[Line : %d][%s] status code is not set\\n", __LINE__, API_NAMESPACE);
		g_bIsValid = false;
		return;
	}
	FPRINTF("[Line : %d][%s] status code[%d]\\n", __LINE__, API_NAMESPACE, r_status);

	
	//Target API
	nRet = http_transaction_response_get_status_text(transaction, &r_status_text);
	if(nRet != HTTP_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] http_transaction_response_get_status_text failed : [%s]\\n", __LINE__, API_NAMESPACE,HttpGetError(nRet));
		g_bIsValid = false;
		if (g_pHttpMainLoop) {
			g_main_loop_quit(g_pHttpMainLoop);
			g_pHttpMainLoop = NULL;
		}
		return;
	}
	if( r_status_text == NULL)
	{
		FPRINTF("[Line : %d][%s] r_status_text is not set\\n", __LINE__, API_NAMESPACE);
		g_bIsValid = false;
		return;
	}
	FPRINTF("[Line : %d][%s] status text[%s]\\n", __LINE__, API_NAMESPACE, r_status_text);

	
	//Target API
	nRet = http_transaction_response_get_version(transaction, &r_version);
	if(nRet != HTTP_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] http_transaction_response_get_version failed : [%s]\\n", __LINE__, API_NAMESPACE,HttpGetError(nRet));
		if (r_status_text) {
			g_free(r_status_text);
			r_status_text = NULL;
		}
		g_bIsValid = false;
		if (g_pHttpMainLoop) {
			g_main_loop_quit(g_pHttpMainLoop);
			g_pHttpMainLoop = NULL;
		}
		return;
	}
	if( r_version < HTTP_VERSION_1_0 || r_version > HTTP_VERSION_1_1 )
	{
		FPRINTF("[Line : %d][%s]http_transaction_response_get_version returned invalid value(%d)\\n", __LINE__, API_NAMESPACE, r_version);
		g_bIsValid = false;
		return;
	}	
	FPRINTF("[Line : %d][%s] version[%d]\\n", __LINE__, API_NAMESPACE, r_version);

	
	//Target API
	if (r_status == HTTP_STATUS_UNAUTHORIZED) {
		nRet = http_transaction_get_realm(transaction, &r_realm);
		if(nRet != HTTP_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] http_transaction_get_realm failed : [%s]\\n", __LINE__, API_NAMESPACE,HttpGetError(nRet));
			if (r_status_text) {
				g_free(r_status_text);
				r_status_text = NULL;
			}
			g_bIsValid = false;
			if (g_pHttpMainLoop) {
				g_main_loop_quit(g_pHttpMainLoop);
				g_pHttpMainLoop = NULL;
			}
			return;
		}
		if( r_realm == NULL)
		{
			FPRINTF("[Line : %d][%s] r_realm is not set\\n", __LINE__, API_NAMESPACE);
			g_bIsValid = false;
			return;
		}
		FPRINTF("[Line : %d][%s] realm[%s]\\n", __LINE__, API_NAMESPACE, r_realm);
	}
	
	
	if (r_realm) {
			g_free(r_realm);
			r_realm = NULL;
		}
	if (r_status_text) {
		g_free(r_status_text);
		r_status_text = NULL;
	}
	
	if ( g_pHttpMainLoop )
	{
		g_main_loop_quit(g_pHttpMainLoop);
		g_pHttpMainLoop = NULL;
	}
	
	return;
}

/**
* @function 		HttpTransactionProgressCB
* @description	 	 Called to notify when the content body of the response message is being downloaded or uploaded
* @parameter		http_transaction_h http_transaction, double download_total, double download_now, double upload_total, double upload_now, void *user_data
* @return 			NA
*/
static void HttpTransactionProgressCB(http_transaction_h http_transaction, double download_total, double download_now, double upload_total, double upload_now, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] HttpTransactionProgressCB callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if (download_total > 0) {
		b_HttpTransactionProgressCB = true;
		g_bCallbackHit = true;
	}

	return;
}

/**
* @function 		HttpTransactionProgressCB
* @description	 	 Called to notify when the content body of the response message is being downloaded or uploaded
* @parameter		http_transaction_h http_transaction, double download_total, double download_now, double upload_total, double upload_now, void *user_data
* @return 			NA
*/
static void HttpTransactionProgressPauseResumeCB(http_transaction_h http_transaction, double download_total, double download_now, double upload_total, double upload_now, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] HttpTransactionProgressPauseResumeCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	double pDownloadRate = download_now / download_total * 100;
	int nRet;
	b_HttpTransactionProgressPauseResumeCB = true;
	g_bIsValid = true;	
	
	if (g_Pause == true && g_Resume == false) {
		//Target API
		nRet =  http_transaction_resume(http_transaction) ;
		if(nRet != HTTP_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] http_transaction_resume failed : [%s]\\n", __LINE__, API_NAMESPACE,HttpGetError(nRet));
			g_bIsValid = false;
			return;
		}
		g_Resume = true;
	}

	if (g_Pause == false) {
		//Target API
		nRet =  http_transaction_pause(http_transaction, HTTP_PAUSE_ALL);
		if(nRet != HTTP_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] http_transaction_pause failed : [%s]\\n", __LINE__, API_NAMESPACE,HttpGetError(nRet));
			g_bIsValid = false;
			return;
		}
		g_Pause = true;
	}

	return;
}
/**
 * @function 		ITs_http_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_http_transaction_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	int nRet;
	g_bFeatureUnsupported = false;

	if(!g_bHttpInit) {
		nRet = http_init();
		g_bHttpInit = true;

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
	}
	
	if (!g_hHttpSession) {
		nRet = http_session_create(HTTP_SESSION_MODE_NORMAL, &g_hHttpSession);
		if( nRet != HTTP_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] http_session_create failed API return %s error \\n", __LINE__, API_NAMESPACE, HttpGetError(nRet));
			g_bHttpInit = false;
			return;
		}
	}
	
	nRet = http_session_open_transaction(g_hHttpSession, HTTP_METHOD_GET, &g_hHttpTransaction);
	if( nRet != HTTP_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] http_session_create failed API return %s error \\n", __LINE__, API_NAMESPACE, HttpGetError(nRet));
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
 * @function 		ITs_http_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_http_transaction_cleanup(void)
{
	int nRet = 0;
	if(g_hHttpTransaction != NULL)
	{
		nRet = http_transaction_destroy(g_hHttpTransaction);
		if (nRet != HTTP_ERROR_NONE)	
		{	
			FPRINTF("[Line : %d][%s] http_transaction_destroy failed API return %s error \\n", __LINE__, API_NAMESPACE, HttpGetError(nRet));
		}
		g_hHttpTransaction = NULL;
	}
	
	return;
}

/** @addtogroup itc-http-testcases
*  @brief 		Integration testcases for module http
*  @ingroup 	itc-http
*  @{
*/

//& purpose: Registers and submit callback called when receive header
//& type: auto 
/**
* @testcase   			ITc_http_transaction_register_callbacks_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Registers and submit callback called when receive header
* @scenario				call http_transaction_set_received_header_cb
* @apicovered			http_transaction_set_received_header_cb  					
* @passcase				When http_transaction_set_received_header_cb is successful.
* @failcase				If API http_transaction_set_received_header_cb fails.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_transaction_register_callbacks_p(void)
{
	START_TEST;
	int nTimeoutId = 0;
	g_bCallbackHit = false;
	http_method_e method;
	const char uri[100] = "http://www.google.com";	
	http_transaction_h transaction = NULL;
	b_HttpTransactionHeaderCB = false;
	b_HttpTransactionBodyCB = false;
	b_HttpTransactionWriteCB = false;
	b_HttpTransactionCompletedCB = false;
	b_HttpTransactionProgressCB = false;

	int nRet =  http_session_open_transaction(g_hHttpSession, HTTP_METHOD_GET, &transaction);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_session_open_transaction", HttpGetError(nRet));	
	CHECK_HANDLE(transaction,"http_session_open_transaction");
	
	nRet =  http_transaction_request_get_method(transaction, &method);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_request_get_method", HttpGetError(nRet),http_transaction_destroy(transaction));	
	
	nRet = http_transaction_request_set_uri(transaction, uri);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_request_set_uri", HttpGetError(nRet),http_transaction_destroy(transaction));	
			
	//Target API
	nRet = http_transaction_set_received_header_cb(transaction, HttpTransactionHeaderCB, NULL);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_set_received_header_cb", HttpGetError(nRet),http_transaction_destroy(transaction));	
	
	//Target API
	nRet = http_transaction_set_received_body_cb(transaction, HttpTransactionBodyCB, NULL);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_set_received_body_cb", HttpGetError(nRet),http_transaction_destroy(transaction));	
	
	//Target API
	nRet = http_transaction_set_completed_cb(transaction, HttpTransactionCompletedCB, NULL);	
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_set_completed_cb", HttpGetError(nRet),http_transaction_destroy(transaction));

	nRet = http_transaction_set_aborted_cb(transaction, HttpTransactionAbortedCB, NULL);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_set_aborted_cb", HttpGetError(nRet),http_transaction_destroy(transaction));
	
	//Target API
	nRet =  http_transaction_submit(transaction);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_submit", HttpGetError(nRet),http_transaction_destroy(transaction));	
		
	RUN_POLLING_LOOP;
	
	if (transaction) {
		http_transaction_destroy(transaction);		
		transaction = NULL;
	}
	if ( b_HttpTransactionHeaderCB == false )
	{
		FPRINTF("[Line : %d][%s] b_HttpTransactionHeaderCB failed\\n", __LINE__, API_NAMESPACE);		
		return 1;
	}	
	if ( b_HttpTransactionBodyCB == false )
	{
		FPRINTF("[Line : %d][%s] b_HttpTransactionBodyCB failed\\n", __LINE__, API_NAMESPACE);		
		return 1;
	}		
	if ( b_HttpTransactionCompletedCB == false )
	{
		FPRINTF("[Line : %d][%s] b_HttpTransactionCompletedCB failed\\n", __LINE__, API_NAMESPACE);		
		return 1;
	}	
			
	return 0;
}

//& purpose:Registers callback called when write data
//& type: auto 
/**
* @testcase   			ITc_http_transaction_set_uploaded_cb_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Registers callback called when write data
* @scenario				call http_transaction_set_uploaded_cb
* @apicovered			http_transaction_set_uploaded_cb  					
* @passcase				When http_transaction_set_uploaded_cb is successful.
* @failcase				If API http_transaction_set_uploaded_cb fails.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_transaction_set_uploaded_cb_p(void)
{
    START_TEST;
	int nRet; 
    int nTimeoutId = 0;
	http_transaction_h transaction;
	const char* post_msg = "name=tizen&project=capi-network-curl";
	b_HttpTransactionWriteCB = false;
	g_bCallbackHit = false;

	if (g_hHttpTransaction) {
		http_transaction_destroy(g_hHttpTransaction);
		g_hHttpTransaction = NULL;
	}

	nRet = http_session_open_transaction(g_hHttpSession, HTTP_METHOD_POST, &transaction);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_session_open_transaction", HttpGetError(nRet));	
	CHECK_HANDLE(transaction,"http_session_open_transaction");
	
	nRet = http_transaction_request_set_uri(transaction, "https://ptsv2.com/t/tizen/post");
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_request_set_uri", HttpGetError(nRet),http_transaction_destroy(transaction));	
	
	nRet = http_transaction_set_ready_to_write(transaction, TRUE);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_set_ready_to_write", HttpGetError(nRet),http_transaction_destroy(transaction));	
	
	nRet = http_transaction_request_write_body(transaction, post_msg);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_request_write_body", HttpGetError(nRet),http_transaction_destroy(transaction));	

	nRet = http_transaction_header_add_field(transaction, "Transfer-Encoding", "chunked");
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_header_add_field", HttpGetError(nRet),http_transaction_destroy(transaction));	

	nRet = http_transaction_header_add_field(transaction, "Expect", "");
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_header_add_field", HttpGetError(nRet),http_transaction_destroy(transaction));	
		
	//Target API
	nRet =  http_transaction_set_uploaded_cb(transaction, HttpTransactionWriteCB, NULL);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_set_uploaded_cb", HttpGetError(nRet),http_transaction_destroy(transaction));

	nRet = http_transaction_set_aborted_cb(transaction, HttpTransactionAbortedCB, NULL);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_set_aborted_cb", HttpGetError(nRet),http_transaction_destroy(transaction));

	nRet = http_transaction_set_completed_cb(transaction, HttpTransactionCompletedCB, NULL);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_set_completed_cb", HttpGetError(nRet),http_transaction_destroy(transaction));
		
	nRet =  http_transaction_submit(transaction);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_submit", HttpGetError(nRet),http_transaction_destroy(transaction));
		
    RUN_POLLING_LOOP;

    if ( g_bCallbackHit == false )
    {
        FPRINTF("[Line : %d][%s] HttpTransactionWriteCB failed\\n", __LINE__, API_NAMESPACE);        
        return 1;
    }    

	http_transaction_destroy(transaction);
	transaction = NULL;
	
    return 0;
}

//& purpose: Registers callback that is called when data is uploaded/downloaded
//& type: auto 
/**
* @testcase   			ITc_http_transaction_set_progress_cb_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Registers callback that is called when data is uploaded/downloaded
* @scenario				call http_transaction_set_progress_cb
* @apicovered			http_transaction_set_progress_cb  					
* @passcase				When http_transaction_set_progress_cb is successful.
* @failcase				If API http_transaction_set_progress_cb fails.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_transaction_set_progress_cb_p(void)
{
	START_TEST;
	int nTimeoutId = 0;
	g_bCallbackHit = false;
	const char uri[100] = "http://www.tizen.org";		
	
	int nRet = http_transaction_request_set_uri(g_hHttpTransaction, uri);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_request_set_uri", HttpGetError(nRet));
	
	//Target API
	nRet =  http_transaction_set_progress_cb(g_hHttpTransaction, HttpTransactionProgressCB, NULL);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_set_progress_cb", HttpGetError(nRet));

	nRet = http_transaction_set_aborted_cb(g_hHttpTransaction, HttpTransactionAbortedCB, NULL);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_set_aborted_cb", HttpGetError(nRet));

	nRet = http_transaction_set_completed_cb(g_hHttpTransaction, HttpTransactionCompletedCB, NULL);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_set_aborted_cb", HttpGetError(nRet));
	
	nRet =  http_transaction_submit(g_hHttpTransaction);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_submit", HttpGetError(nRet));

	RUN_POLLING_LOOP;
	
	if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] HttpTransactionProgressCB failed\\n", __LINE__, API_NAMESPACE);		
		return 1;
	}	
		
	return 0;
}

//& purpose: Sets/Gets the timeout in seconds that is the timeout for waiting the transaction
//& type: auto 
/**
* @testcase   			ITc_http_transaction_set_get_timeout_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Sets/Gets the timeout in seconds that is the timeout for waiting the transaction
* @scenario				call http_transaction_set_timeout, http_transaction_get_timeout
* @apicovered			http_transaction_set_timeout, http_transaction_get_timeout  					
* @passcase				When http_transaction_set_timeout, http_transaction_get_timeout is successful.
* @failcase				If API http_transaction_set_timeout, http_transaction_get_timeout fails.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_transaction_set_get_timeout_p(void)
{
	START_TEST;

	int nTimeout = 10;	
	int nGetTimout = -1;
	
	//Target API
	int nRet =  http_transaction_set_timeout(g_hHttpTransaction, nTimeout);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_set_timeout", HttpGetError(nRet));
	
	//Target API
	nRet =  http_transaction_get_timeout(g_hHttpTransaction, &nGetTimout);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_get_timeout", HttpGetError(nRet));
	
	if( nTimeout != nGetTimout)
	{
		FPRINTF("[Line : %d][%s] nGetTimout value not set!! \\n", __LINE__, API_NAMESPACE);		
		return 1;
	}
	
	return 0;
}

//& purpose: Sets ready to write event for a transaction
//& type: auto 
/**
* @testcase   			ITc_http_transaction_set_ready_to_write_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Sets ready to write event for a transaction
* @scenario				call http_transaction_set_ready_to_write
* @apicovered			http_transaction_set_ready_to_write  					
* @passcase				When http_transaction_set_ready_to_write is successful.
* @failcase				If API http_transaction_set_ready_to_write fails.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_transaction_set_ready_to_write_p(void)
{
	START_TEST;

	bool bReadyToWrite = true;
	
	//Target API
	int nRet =  http_transaction_set_ready_to_write(g_hHttpTransaction, bReadyToWrite);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_set_ready_to_write", HttpGetError(nRet));
			
	return 0;
}

//& purpose: Sets/Gets the interface name
//& type: auto 
/**
* @testcase   			ITc_http_transaction_set_get_interface_name_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Sets/Gets the interface name
* @scenario				call http_transaction_set_interface_name , http_transaction_get_interface_name
* @apicovered			http_transaction_set_interface_name, http_transaction_get_interface_name 					
* @passcase				When http_transaction_set_interface_name, http_transaction_get_interface_name is successful.
* @failcase				If API http_transaction_set_interface_name, http_transaction_get_interface_name fails.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_transaction_set_get_interface_name_p(void)
{
	START_TEST;

	const char pInterfaceName[10] = "wlan0";
	char *pGetInterfaceName;	
	
	//Target API
	int nRet =  http_transaction_set_interface_name(g_hHttpTransaction, pInterfaceName);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_set_interface_name", HttpGetError(nRet));
	
	//Target API
	nRet =  http_transaction_get_interface_name(g_hHttpTransaction, &pGetInterfaceName);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_get_interface_name", HttpGetError(nRet));
	
	if ( strcmp( pGetInterfaceName, pInterfaceName ) != 0 )
	{
		FPRINTF("[Line : %d][%s] pGetInterfaceName in http_transaction_get_interface_name is not same, as set\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pGetInterfaceName);
		return 1;
	}
	FREE_MEMORY(pGetInterfaceName);
	
	return 0;
}

//& purpose: Sets/Gets the flag to verify a server certificate
//& type: auto 
/**
* @testcase   			ITc_http_transaction_set_get_server_certificate_verification_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Sets/Gets the flag to verify a server certificate
* @scenario				call http_transaction_set_server_certificate_verification, http_transaction_get_server_certificate_verification
* @apicovered			http_transaction_set_server_certificate_verification, http_transaction_get_server_certificate_verification  					
* @passcase				When http_transaction_set_server_certificate_verification, http_transaction_get_server_certificate_verification is successful.
* @failcase				If API http_transaction_set_server_certificate_verification, http_transaction_get_server_certificate_verification fails.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_transaction_set_get_server_certificate_verification_p(void)
{
	START_TEST;

	bool bVerify = true;
	bool bGetVerify = false;
	
	//Target API
	int nRet =  http_transaction_set_server_certificate_verification(g_hHttpTransaction, bVerify);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_set_server_certificate_verification", HttpGetError(nRet));
	
	//Target API
	nRet =  http_transaction_get_server_certificate_verification(g_hHttpTransaction, &bGetVerify);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_get_server_certificate_verification", HttpGetError(nRet));
	
	if ( bGetVerify != bVerify )
	{
		FPRINTF("[Line : %d][%s] bGetVerify in http_transaction_get_server_certificate_verification is not same, as set\\n", __LINE__, API_NAMESPACE);		
		return 1;
	}
	
	return 0;
}

//& purpose: Pauses/resume the transaction
//& type: auto 
/**
* @testcase   			ITc_http_transaction_pause_resume_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Pauses/resume the transaction
* @scenario				call http_transaction_pause, http_transaction_resume
* @apicovered			http_transaction_pause, http_transaction_resume  					
* @passcase				When http_transaction_pause, http_transaction_resume is successful.
* @failcase				If API http_transaction_pause, http_transaction_resume fails.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_transaction_pause_resume_p(void)
{
	
	START_TEST;
	int nTimeoutId = 0;
	int nRet;
	http_transaction_h transaction;
	char pValue[10];
	b_HttpTransactionProgressCB = true;
	g_bCallbackHit = false;

	if (g_hHttpTransaction) {
		http_transaction_destroy(g_hHttpTransaction);
		g_hHttpTransaction = NULL;
	}

	nRet = http_session_open_transaction(g_hHttpSession, HTTP_METHOD_GET, &transaction);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_session_open_transaction", HttpGetError(nRet));	
	CHECK_HANDLE(transaction,"http_session_open_transaction");
	
	nRet = http_transaction_set_timeout(transaction, 5);
	nRet = http_transaction_request_set_uri(transaction, "http://www.tizen.org");
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_request_set_uri", HttpGetError(nRet),http_transaction_destroy(transaction));	
	
	//Target API
	nRet =  http_transaction_set_progress_cb(transaction, HttpTransactionProgressPauseResumeCB, NULL);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_set_progress_cb", HttpGetError(nRet),http_transaction_destroy(transaction));

	nRet = http_transaction_set_aborted_cb(transaction, HttpTransactionAbortedCB, NULL);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_set_aborted_cb", HttpGetError(nRet),http_transaction_destroy(transaction));

	nRet = http_transaction_set_completed_cb(transaction, HttpTransactionCompletedCB, NULL);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_set_completed_cb", HttpGetError(nRet),http_transaction_destroy(transaction));
		
	nRet =  http_transaction_submit(transaction);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_submit", HttpGetError(nRet),http_transaction_destroy(transaction));	

	RUN_POLLING_LOOP;

	if ( b_HttpTransactionProgressCB == false )
	{
		FPRINTF("[Line : %d][%s] b_HttpTransactionWriteCB failed\\n", __LINE__, API_NAMESPACE);	
		http_transaction_destroy(transaction);
		return 1;
	}	
	if(!g_bIsValid)
	{
		FPRINTF("[Line : %d][%s] API failed in HttpTransactionProgressPauseResumeCB \\n", __LINE__, API_NAMESPACE);		
		http_transaction_destroy(transaction);
		return 1;
	}
	
	nRet =  http_transaction_destroy(transaction);
    PRINT_RESULT_NORETURN(HTTP_ERROR_NONE, nRet, "http_transaction_destroy", HttpGetError(nRet));	
	
	return 0;
}
//& purpose:  Gets the Http Header Field value from custom header
//& type: auto 
/**
* @testcase   			ITc_http_transaction_header_add_remove_field_p
* @since_tizen			3.0
* @author             	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			 Gets the Http Header Field value from custom header
* @scenario				call http_transaction_header_add_field and http_transaction_header_remove_field
* @apicovered			http_transaction_header_add_field .http_transaction_header_remove_field					
* @passcase				When http_transaction_header_add_field and http_transaction_header_remove_field is successful.
* @failcase				If API http_transaction_header_add_field or http_transaction_header_remove_field fails.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_transaction_header_add_remove_field_p(void)
{
	START_TEST;

	  const char szfield[20] = "Content-Length";		
	  const char szvalue[10] = "10";	
	
	//Target API
	int nRet =  http_transaction_header_add_field(g_hHttpTransaction,szfield,szvalue);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_header_add_field", HttpGetError(nRet));
	
	//Target API
	nRet =  http_transaction_header_remove_field(g_hHttpTransaction, szfield);	
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_header_remove_field", HttpGetError(nRet));
	
	return 0;
}

//& purpose:  Gets & Sets an HTTP method of the request header.
//& type: auto 
/**
* @testcase   			ITc_http_transaction_request_set_get_method_p
* @since_tizen			3.0
* @author             	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Sets and gets  HTTP method of the request header.
* @scenario				call http_transaction_request_set_method and http_transaction_request_get_method
* @apicovered			http_transaction_request_set_method ,http_transaction_request_get_method					
* @passcase				When http_transaction_request_set_method and http_transaction_request_get_method is successful.
* @failcase				If API http_transaction_request_set_method or http_transaction_request_get_method fails.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_transaction_request_set_get_method_p(void)
{
	START_TEST;

	  http_method_e method;	
	  
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
	
	for ( nEnumCounter=0;nEnumCounter<nEnumSize;nEnumCounter++)
	{
		//Target API
		int nRet =  http_transaction_request_set_method(g_hHttpTransaction,eHttpMethodType[nEnumCounter]);
		PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_request_set_method", HttpGetError(nRet));
		
		//Target API
		nRet =  http_transaction_request_get_method(g_hHttpTransaction, &method);	
		PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_request_get_method", HttpGetError(nRet));
		if(method != eHttpMethodType[nEnumCounter])
		{
			FPRINTF("[Line : %d][%s]http_transaction_request_get_method method [%d] mismatch value\\n", __LINE__, API_NAMESPACE,nEnumCounter);
			return 1;
		}
	}
			
	return 0;
}
//& purpose:  Gets & Sets HTTP version of the request header.
//& type: auto 
/**
* @testcase   			ITc_http_transaction_request_set_get_version_p
* @since_tizen			3.0
* @author             	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Sets and gets HTTP version of the request header.
* @scenario				call http_transaction_request_set_version and http_transaction_request_get_version
* @apicovered			http_transaction_request_set_version ,http_transaction_request_get_version					
* @passcase				When http_transaction_request_set_version and http_transaction_request_get_version is successful.
* @failcase				If API http_transaction_request_set_version or http_transaction_request_get_version fails.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_transaction_request_set_get_version_p(void)
{
	START_TEST;

	  http_version_e version = HTTP_VERSION_1_1;
      http_version_e versionNew; 	  
	
	//Target API
	int nRet =  http_transaction_request_set_version(g_hHttpTransaction,version);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_request_set_version", HttpGetError(nRet));
	
	//Target API
	nRet =  http_transaction_request_get_version(g_hHttpTransaction, &versionNew);	
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_request_get_version", HttpGetError(nRet));
	if(versionNew != HTTP_VERSION_1_1)
	{
		FPRINTF("[Line : %d][%s]http_transaction_request_get_version version mismatch value\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
			
	return 0;
}

//& purpose:  Gets & Sets a URI of the request header.
//& type: auto 
/**
* @testcase   			ITc_http_transaction_request_set_get_uri_p
* @since_tizen			3.0
* @author             	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Sets and gets URI of the request header
* @scenario				call http_transaction_request_set_uri and http_transaction_request_get_uri
* @apicovered			http_transaction_request_set_uri ,http_transaction_request_get_uri					
* @passcase				When http_transaction_request_set_uri and http_transaction_request_get_uri is successful.
* @failcase				If API http_transaction_request_set_uri or http_transaction_request_get_uri fails.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_transaction_request_set_get_uri_p(void)
{
	START_TEST;

	  const char szhostUri[100] = "http://www.tizen.org";		
      char *szhostNewuri=NULL;	  
	
	//Target API
	int nRet =  http_transaction_request_set_uri(g_hHttpTransaction,szhostUri);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_request_set_uri", HttpGetError(nRet));
	
	//Target API
	nRet =  http_transaction_request_get_uri(g_hHttpTransaction, &szhostNewuri);	
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_request_get_uri", HttpGetError(nRet));
	if( strcmp(szhostNewuri, (const char *)szhostUri) != 0 )
	{
		FPRINTF("[Line : %d][%s] http_transaction_request_get_uri error returned = uri returned [ %s ] is not correct\\n", __LINE__, API_NAMESPACE, szhostNewuri);
		FREE_MEMORY(szhostNewuri);
		return 1;
	}
	FREE_MEMORY(szhostNewuri);		
	return 0;
}

//& purpose:  Gets & Sets the Accept-Encoding header field of HttpRequest.
//& type: auto 
/**
* @testcase   			ITc_http_transaction_request_set_get_accept_encoding_p
* @since_tizen			3.0
* @author             	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Sets and gets the Accept-Encoding header field of HttpRequest
* @scenario				call http_transaction_request_set_accept_encoding and http_transaction_request_get_accept_encoding
* @apicovered			http_transaction_request_set_accept_encoding ,http_transaction_request_get_accept_encoding					
* @passcase				When http_transaction_request_set_accept_encoding and http_transaction_request_get_accept_encoding is successful.
* @failcase				If API http_transaction_request_set_accept_encoding or http_transaction_request_get_accept_encoding fails.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_transaction_request_set_get_accept_encoding_p(void)
{
	START_TEST;

	  const char szencoding[100] = "gzip, deflate";			
      char *szNewEcncoding=NULL;	  
	
	//Target API
	int nRet =  http_transaction_request_set_accept_encoding(g_hHttpTransaction,szencoding);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_request_set_accept_encoding", HttpGetError(nRet));
	
	//Target API
	nRet =  http_transaction_request_get_accept_encoding(g_hHttpTransaction, &szNewEcncoding);	
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_request_get_accept_encoding", HttpGetError(nRet));
	if( strcmp(szNewEcncoding, (const char *)szencoding) != 0 )
	{
		FPRINTF("[Line : %d][%s] http_transaction_request_get_accept_encoding error returned = uri returned [ %s ] is not correct\\n", __LINE__, API_NAMESPACE, szNewEcncoding);
		FREE_MEMORY(szNewEcncoding);
		return 1;
	}
	FREE_MEMORY(szNewEcncoding);
	
	return 0;
}


//& purpose:  Gets & Sets a cookie in the HTTP request.
//& type: auto 
/**
* @testcase   			ITc_http_transaction_request_set_get_cookie_p
* @since_tizen			3.0
* @author             	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Sets and gets a cookie in the HTTP request
* @scenario				call http_transaction_request_set_cookie and http_transaction_request_get_cookie
* @apicovered			http_transaction_request_set_cookie ,http_transaction_request_get_cookie					
* @passcase				When http_transaction_request_set_cookie and http_transaction_request_get_cookie is successful.
* @failcase				If API http_transaction_request_set_cookie or http_transaction_request_get_cookie fails.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_transaction_request_set_get_cookie_p(void)
{
	START_TEST;

	  const char szcookie[100] = "tool=tizen; fun=yes;";		
      char *szNewCookie=NULL;	  
	
	//Target API
	int nRet =  http_transaction_request_set_cookie(g_hHttpTransaction,szcookie);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_request_set_cookie", HttpGetError(nRet));
	
	//Target API
	nRet =  http_transaction_request_get_cookie(g_hHttpTransaction, &szNewCookie);	
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_request_get_cookie", HttpGetError(nRet));
	if( strcmp(szNewCookie, (const char *)szcookie) != 0 )
	{
		FPRINTF("[Line : %d][%s] http_transaction_request_get_accept_encoding error returned = uri returned [ %s ] is not correct\\n", __LINE__, API_NAMESPACE, szNewCookie);
		FREE_MEMORY(szNewCookie);
		return 1;
	}
			
	FREE_MEMORY(szNewCookie);
	
	return 0;
}

//& purpose:   Writes the request message body.
//& type: auto 
/**
* @testcase   			ITc_http_transaction_request_write_body_p
* @since_tizen			3.0
* @author             	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			 Writes the request message body
* @scenario				call http_transaction_request_write_body 
* @apicovered			http_transaction_request_write_body 					
* @passcase				When http_transaction_request_write_body .
* @failcase				If API http_transaction_request_write_body fails.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_transaction_request_write_body_p(void)
{
	START_TEST;

	const char szbody[100] = "data";				
     	
	//Target API
	int nRet =  http_transaction_request_write_body(g_hHttpTransaction,szbody);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_request_write_body", HttpGetError(nRet));
					
	return 0;
}

//& purpose:  Opens HTTP transaction with authentication information.
//& type: auto 
/**
* @testcase   			ITc_http_trasaction_open_authentication_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Opens HTTP transaction with authentication information.
* @scenario				call http_transaction_open_authentication 
* @apicovered			http_transaction_open_authentication 					
* @passcase				When http_transaction_open_authentication .
* @failcase				If API http_transaction_open_authentication fails.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_trasaction_open_authentication_p(void)
{
	START_TEST;

	http_transaction_h h_HttpAuthTransaction;  	  
	
	//Target API
	int nRet =  http_transaction_open_authentication(g_hHttpTransaction, &h_HttpAuthTransaction);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_open_authentication", HttpGetError(nRet));
	CHECK_HANDLE( h_HttpAuthTransaction, "http_transaction_open_authentication");	
	
	return 0;
}

//& purpose: Sets/Gets an HTTP credentials
//& type: auto 
/**
* @testcase   			ITc_http_transaction_set_get_credentials_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Invoking http_transaction_set_credentials  with valid parameter.
* @scenario				call http_transaction_set_credentials http_transaction_get_credentials
* @apicovered			http_transaction_set_credentials and http_transaction_get_credentials					
* @passcase				When http_transaction_set_credentials and http_transaction_get_credentials.
* @failcase				If API http_transaction_set_credentials or http_transaction_get_credentials fails.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_transaction_set_get_credentials_p(void)
{
	START_TEST;

	const char pUserName[10] = "tizen";
	const char pPassword[10] = "q1w2e3r4";
	char *pGetUserName;
	char *pGetPassword;
	
	//Target API
	int nRet =  http_transaction_set_credentials(g_hHttpTransaction, pUserName, pPassword);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_set_credentials", HttpGetError(nRet));

	//Target API
	nRet =  http_transaction_get_credentials(g_hHttpTransaction, &pGetUserName, &pGetPassword);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_get_credentials", HttpGetError(nRet));
	
	if ( strcmp( pUserName, pGetUserName ) != 0 )
	{
		FPRINTF("[Line : %d][%s] pGetUserName in http_transaction_get_credentials is not same, as set\\n", __LINE__, API_NAMESPACE);	\
		FREE_MEMORY(pGetUserName);
		FREE_MEMORY(pGetPassword);		
		return 1;
	}
	if ( strcmp( pPassword, pGetPassword ) != 0 )
	{
		FPRINTF("[Line : %d][%s] pGetPassword in http_transaction_get_credentials is not same, as set\\n", __LINE__, API_NAMESPACE);		
		FREE_MEMORY(pGetUserName);
		FREE_MEMORY(pGetPassword);
		return 1;
	}
	FREE_MEMORY(pGetUserName);
	FREE_MEMORY(pGetPassword);
	
	return 0;
}

//& purpose: Sets/Gets an HTTP authentication scheme.
//& type: auto 
/**
* @testcase   			ITc_http_transaction_set_get_http_auth_scheme_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Sets/Gets an HTTP authentication scheme.
* @scenario				call http_transaction_set_http_auth_scheme http_transaction_get_http_auth_scheme
* @apicovered			http_transaction_set_http_auth_scheme and http_transaction_get_http_auth_scheme					
* @passcase				When http_transaction_set_http_auth_scheme and http_transaction_get_http_auth_scheme.
* @failcase				If API http_transaction_set_http_auth_scheme or http_transaction_get_http_auth_scheme fails.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_transaction_set_get_http_auth_scheme_p(void)
{
	START_TEST;	
	http_auth_scheme_e eGetAuthScheme;
	
	http_auth_scheme_e eAuthScheme[] = {
		HTTP_AUTH_NONE,             /**< No authentication type */
		HTTP_AUTH_PROXY_BASIC,      /**< The authentication type is Proxy Basic Authentication */
		HTTP_AUTH_PROXY_MD5,        /**< The authentication type is Proxy Digest Authentication */
		HTTP_AUTH_WWW_BASIC,        /**< The authentication Type is HTTP Basic Authentication */
		HTTP_AUTH_WWW_MD5,          /**< The authentication type is HTTP Digest Authentication */
		HTTP_AUTH_PROXY_NTLM,       /**< The authentication type is Proxy NTLM Authentication */
		HTTP_AUTH_WWW_NTLM,         /**< The authentication type is NTLM Authentication */
		HTTP_AUTH_WWW_NEGOTIATE     /**< The authentication type is Negotiate Authentication */
	};

	int nEnumSize = sizeof(eAuthScheme) / sizeof(eAuthScheme[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter=0;nEnumCounter<nEnumSize;nEnumCounter++)
	{
		//Target API
		int nRet = http_transaction_set_http_auth_scheme(g_hHttpTransaction, eAuthScheme[nEnumCounter]);
		PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_set_http_auth_scheme", HttpGetError(nRet));

		//Target API
		nRet =  http_transaction_get_http_auth_scheme(g_hHttpTransaction, &eGetAuthScheme);
		PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_get_http_auth_scheme", HttpGetError(nRet));
		
		if ( eAuthScheme[nEnumCounter] != eGetAuthScheme )
		{
			FPRINTF("[Line : %d][%s] eGetAuthScheme in http_transaction_get_http_auth_scheme is not same, as set\\n", __LINE__, API_NAMESPACE);		
			return 1;
		}
	}
		
	return 0;
}

//& purpose: Gets an HTTP status code,text,version and realm
//& type: auto 
/**
* @testcase   			ITc_http_transaction_get_status_code_text_version_realm_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Gets an HTTP status code,text,version and realm
* @scenario				call http_transaction_get_realm 
* @apicovered			http_transaction_get_realm, http_transaction_response_get_status_code, http_transaction_response_get_status_text, http_transaction_response_get_version				
* @passcase				When http_transaction_get_realm, http_transaction_response_get_status_code, http_transaction_response_get_status_text, http_transaction_response_get_version success.
* @failcase				If API http_transaction_get_realm, http_transaction_response_get_status_code, http_transaction_response_get_status_text, http_transaction_response_get_version fails.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_transaction_get_status_code_text_version_realm_p(void)
{
	START_TEST;

	const char uri[100] = "http://test.webdav.org/auth-basic/";	
	int nTimeoutId = 0;
	b_HttpTransactionCompletedCB = false;
	g_bCallbackHit = false;

	int nRet = http_transaction_request_set_uri(g_hHttpTransaction, uri);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_request_set_uri", HttpGetError(nRet));	
	
	//Target API
	nRet = http_transaction_set_completed_cb(g_hHttpTransaction, HttpTransactionCompletedGetStatusTextVersionRealmCB, NULL);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_set_completed_cb", HttpGetError(nRet));

	nRet = http_transaction_set_aborted_cb(g_hHttpTransaction, HttpTransactionAbortedCB, NULL);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_set_aborted_cb", HttpGetError(nRet));
	
	//Target API
	nRet =  http_transaction_submit(g_hHttpTransaction);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_submit", HttpGetError(nRet));	
	
	RUN_POLLING_LOOP;
	
	if(!g_bIsValid)
	{
		FPRINTF("[Line : %d][%s] API failed in HttpTransactionCompletedGetStatusTextVersionRealmCB \\n", __LINE__, API_NAMESPACE);		
		return 1;
	}
	
	return 0;
}

//& purpose: Sets the file path for uploading a file.
//& type: auto 
/**
* @testcase   			ITc_http_transaction_request_set_upload_file_cancel_p
* @since_tizen			3.0
* @author             	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets the file path for uploading a file
* @scenario				Sets the file path for uploading a file
* @apicovered			http_transaction_request_set_upload_file and http_transaction_cancel
* @passcase				When http_transaction_request_set_upload_file and http_transaction_cancel success.
* @failcase				If API http_transaction_request_set_upload_file or http_transaction_cancel fail.
* @precondition			http_session_open_transaction() should be successfully called
* @postcondition		NA
*/
int ITc_http_transaction_request_set_upload_file_cancel_p(void)
{
	START_TEST;
	
	char *pszFilePath = NULL;
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
	{
		FPRINTF("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
		int path_size = strlen(pszValue)+strlen("/res/test.txt")+1;
		pszFilePath=(char*)calloc(path_size, sizeof(char));
		if( NULL == pszFilePath )
		{
			FPRINTF("[Line : %d][%s] 'Memory allocation to pszFilePath failed\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		snprintf(pszFilePath, path_size, "%s/res/test.txt", pszValue);
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	//Target API
	int nRet = http_transaction_request_set_upload_file(g_hHttpTransaction, pszFilePath);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_request_set_upload_file", HttpGetError(nRet),FREE_MEMORY(pszFilePath));
	
	nRet = http_transaction_cancel(g_hHttpTransaction);
	PRINT_RESULT_CLEANUP(HTTP_ERROR_NONE, nRet, "http_transaction_cancel", HttpGetError(nRet),FREE_MEMORY(pszFilePath));
	
	FREE_MEMORY(pszFilePath);
	return 0;
}

//& purpose:	Sets and Gets the flag to allow TCP Fast Open.
//& type: auto
/**
* @testcase			ITc_http_transaction_set_get_tcp_fastopen_p
* @since_tizen			5.0
* @author			SRID(j.abhishek)
* @reviewer			SRID(nibha.sharma)
* @type			auto
* @description			Sets and Gets the flag to allow TCP Fast Open.
* @scenario			call http_transaction_set_tcp_fastopen and http_transaction_get_tcp_fastopen
* @apicovered			http_transaction_set_tcp_fastopen and http_transaction_get_tcp_fastopen
* @passcase			When http_transaction_set_tcp_fastopen and http_transaction_get_tcp_fastopen.
* @failcase			If API http_transaction_set_tcp_fastopen or http_transaction_get_tcp_fastopen fails.
* @precondition			http_transaction_set_tcp_fastopen() and http_transaction_get_tcp_fastopen() should be successfully called
* @postcondition			NA
*/
int ITc_http_transaction_set_get_tcp_fastopen_p(void)
{
	START_TEST;
	int nRet = -1;
	bool IsEnabled = true;

	//Target API
	nRet = http_transaction_set_tcp_fastopen(g_hHttpTransaction, IsEnabled);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_set_tcp_fastopen", HttpGetError(nRet));
	IsEnabled = false;

	//Target API
	nRet = http_transaction_get_tcp_fastopen(g_hHttpTransaction, &IsEnabled);
	PRINT_RESULT(HTTP_ERROR_NONE, nRet, "http_transaction_get_tcp_fastopen", HttpGetError(nRet));

	if(!IsEnabled)
	{
		FPRINTF("[Line : %d][%s] Fast Open flag is disabled returned from API http_transaction_get_tcp_fastopen \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

/** @} */
/** @} */
