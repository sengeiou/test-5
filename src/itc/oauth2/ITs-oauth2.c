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
#include "ITs-oauth2-common.h"

//& set: Oauth2

/** @addtogroup itc-oauth2
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_oauth2_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_oauth2_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	FPRINTF("[Line : %d][%s] Start-up: Oauth2\\n", __LINE__, API_NAMESPACE);
	
	return;
}

/**
 * @function 		ITs_oauth2_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_oauth2_cleanup(void)
{
	FPRINTF("[Line : %d][%s] Clean-up: Oauth2\\n", __LINE__, API_NAMESPACE);
	return;
}

/** @addtogroup itc-oauth2-testcases
*  @brief 		Integration testcases for module oauth2
*  @ingroup 	itc-oauth2
*  @{
*/

/**
* @testcase 			ITc_oauth2_manager_create_destroy_p
* @since_tizen 			2.4
* @owner				SRID(nibha.sharma)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Creates & destroy manager
* @scenario				Create handle oauth2_manager_h\n
*					 	Destroy handle oauth2_manager_h
* @apicovered			oauth2_manager_create, oauth2_manager_destroy
* @passcase				When oauth2_manager_create & oauth2_manager_destroy are successful and return valid data.
* @failcase				If target API fails or return invalid value.
* @precondition			None
* @postcondition		None
*/
//& purpose: Creates & destroy g_hManager
//& type: auto
int ITc_oauth2_manager_create_destroy_p(void)
{
	START_TEST_NO_CHECK;
	
	oauth2_manager_h hManager = NULL;
	
	int nRet = oauth2_manager_create(&hManager);
    PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_manager_create", Oauth2InfoGetError(nRet));
	CHECK_HANDLE(hManager, "oauth2_manager_create");
	
	nRet = oauth2_manager_destroy(hManager);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_manager_destroy", Oauth2InfoGetError(nRet));
	
	return 0;
} 

/**
* @testcase 			ITc_oauth2_request_create_destroy_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Creates & destroy request
* @scenario				Create handler oauth2_request_h\n
*					 	Destroy handle oauth2_request_h
* @apicovered			oauth2_request_create, oauth2_request_destroy
* @passcase				When oauth2_request_create & oauth2_request_destroy is successful and return valid data.
* @failcase				If target API fails or return invalid value.
* @precondition			None
* @postcondition		None
*/
//& purpose: Creates & destroy g_hRequest
//& type: auto
int ITc_oauth2_request_create_destroy_p(void)
{
 	START_TEST_NO_CHECK;
	
	oauth2_request_h hRequest = NULL;
	
	int nRet = oauth2_request_create(&hRequest);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_create", Oauth2InfoGetError(nRet));
	CHECK_HANDLE(hRequest, "oauth2_manager_create");
	
	nRet = oauth2_request_destroy(hRequest);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_destroy", Oauth2InfoGetError(nRet));
	
	return 0;
} 

/** @} */
/** @} */