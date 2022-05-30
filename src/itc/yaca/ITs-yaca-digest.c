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
#include "ITs-yaca-common.h"

//& set: Yaca

/** @addtogroup itc-yaca
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_yaca_digest_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_yaca_digest_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	
	int nRet = yaca_initialize();
	if( nRet != YACA_ERROR_NONE )
	{
		g_bYacaInit = false; 
	}
	else
	{
		g_bYacaInit = true;
	}
	return;
}


/**
 * @function 		ITs_yaca_digest_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_yaca_digest_cleanup(void)
{
	yaca_cleanup();
	
	return;
}

/** @addtogroup itc-yaca-testcases
*  @brief 		Integration testcases for module yaca
*  @ingroup 	itc-yaca
*  @{
*/


//& type: auto
//& purpose: Initializes the digest context
/**
* @testcase 			ITc_yaca_digest_initialize_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Initializes the digest context
* @scenario				Initializes the digest context
* @apicovered			yaca_digest_initialize
* @passcase				If yaca_digest_initialize returns success
* @failcase				If yaca_digest_initialize fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_digest_initialize_p(void)
{
	START_TEST;	
	
	yaca_context_h hContext;
	
	//Target API
	int nRet = yaca_digest_initialize(&hContext, YACA_DIGEST_SHA256);	
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_digest_initialize", YacaGetError(nRet));
		
	yaca_context_destroy(hContext);
	
	return 0;
}

//& type: auto
//& purpose: Initializes the digest context
/**
* @testcase 			ITc_yaca_digest_update_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Initializes the digest context
* @scenario				Initializes the digest context
* @apicovered			yaca_digest_initialize, yaca_digest_update
* @passcase				If yaca_digest_initialize, yaca_digest_update returns success
* @failcase				If yaca_digest_initialize, yaca_digest_update fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_digest_update_p(void)
{
	START_TEST;	
	
	yaca_context_h hContext;
	
	//Target API
	int nRet = yaca_digest_initialize(&hContext, YACA_DIGEST_SHA256);	
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_digest_initialize", YacaGetError(nRet));
		
	nRet = yaca_digest_update(hContext, lorem1024, 1024);
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_digest_update", YacaGetError(nRet));
	
	yaca_context_destroy(hContext);
	
	return 0;
}

//& type: auto
//& purpose: Calculates the final digest
/**
* @testcase 			ITc_yaca_digest_finalize_p
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			Calculates the final digest
* @scenario				Calculates the final digest
* @apicovered			yaca_digest_initialize, yaca_digest_finalize
* @passcase				If yaca_digest_initialize, yaca_digest_finalize returns success
* @failcase				If yaca_digest_initialize, yaca_digest_finalize fails
* @precondition			NA
* @postcondition		Initializes the library
*/
int ITc_yaca_digest_finalize_p(void)
{
	START_TEST;	
	
	yaca_context_h hContext;
	size_t digest_len;
	char *digest = NULL;
		
	//Target API
	int nRet = yaca_digest_initialize(&hContext, YACA_DIGEST_SHA256);	
	PRINT_RESULT(YACA_ERROR_NONE, nRet, "yaca_digest_initialize", YacaGetError(nRet));
		
	nRet = yaca_digest_update(hContext, lorem1024, 1024);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_digest_update", YacaGetError(nRet), yaca_context_destroy(hContext));
	
	nRet = yaca_context_get_output_length(hContext, 0, &digest_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_context_get_output_length", YacaGetError(nRet), yaca_context_destroy(hContext));
	
	nRet = yaca_malloc(digest_len, (void**) &digest);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_malloc", YacaGetError(nRet), yaca_context_destroy(hContext));
	
	nRet = yaca_digest_finalize(hContext, digest, &digest_len);
	PRINT_RESULT_CLEANUP(YACA_ERROR_NONE, nRet, "yaca_digest_finalize", YacaGetError(nRet), yaca_context_destroy(hContext));
	
	yaca_context_destroy(hContext);
	
	return 0;
}
/** @} */
/** @} */