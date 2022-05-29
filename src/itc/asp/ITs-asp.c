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
#include "ITs-asp-common.h"

//& set: Asp

/** @addtogroup itc-asp
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_asp_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_asp_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		int nRet = remove(ERR_LOG);
		PRINT_RESULT_NORETURN(0, nRet, "ITs_asp_startup -remove", "Remove failed for ERR_LOG");
	}
	
	g_bFeatureMismatch = false;
	g_bFeatureNotSupported = false;
	g_bAspInit = true;
	
	bool bAspFeatureSupported = TCTCheckSystemInfoFeatureSupported(ASP_FEATURE, API_NAMESPACE);
	
	int nRet = asp_initialize();
	
	if ( false == bAspFeatureSupported) 
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] asp_initialize API call returned mismatch %s error for unsupported network.asp feature\\n", __LINE__, API_NAMESPACE, AspOutputGetError(nRet));
			g_bFeatureMismatch = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] asp_initialize API call correctly returned %s error for unsupported network.asp feature\\n", __LINE__, API_NAMESPACE, AspOutputGetError(nRet));
			g_bFeatureNotSupported = true;
		}
		return;
	}

	if ( nRet != ASP_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] asp_initialize API failed in Precondition, returned error %s \\n", __LINE__, API_NAMESPACE, AspOutputGetError(nRet));
		g_bAspInit = false;
	}

	return;
}


/**
 * @function 		ITs_asp_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_asp_cleanup(void)
{
	if (g_bAspInit)
	{
		int nRet = asp_deinitialize();
		if ( nRet != ASP_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] asp_deinitialize API failed in Postcondition, returned error %s \\n", __LINE__, API_NAMESPACE, AspOutputGetError(nRet));
		}
	}
	return;
}

/** @addtogroup itc-asp-testcases
*  @brief 		Integration testcases for module asp
*  @ingroup 	itc-asp
*  @{
*/

//& purpose: To check Initialization and deinitialization of Application Service Platform
//& type : auto
/**
* @testcase 			ITc_asp_initialize_deinitialize_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			To check Initialization and deinitialization of Application Service Platform
* @scenario				Call API to initialization and deinitialization Application Service Platform
* @apicovered			asp_initialize, asp_deinitialize
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_asp_initialize_deinitialize_p(void)
{
    START_TEST;
	
	int nRet = asp_deinitialize();
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_deinitialize in Precondition", AspOutputGetError(nRet));
	
	nRet = asp_initialize();
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_initialize", AspOutputGetError(nRet));
	
	nRet = asp_deinitialize();
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_deinitialize", AspOutputGetError(nRet));
	
	nRet = asp_initialize();
	PRINT_RESULT_NORETURN(ASP_ERROR_NONE, nRet, "asp_initialize in Postcondition", AspOutputGetError(nRet));
	
	return 0;
}

//& purpose: Creates and destroyes the description of a service to be advertised
//& type : auto
/**
* @testcase 			ITc_asp_advert_create_destroy_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Creates and destroyes the description of a service to be advertised
* @scenario				Creates and destroyes the description of a service to be advertised
* @apicovered			asp_advert_create, asp_advert_destroy
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize
* @postcondition		Call API asp_deinitialize
*/
int ITc_asp_advert_create_destroy_p(void)
{
    START_TEST;
	
	char *pszServiceName = "TestAdvertSvc";
	asp_advert_service_h hAdvertSvc = NULL;
	
	int nRet = asp_advert_create(pszServiceName, &hAdvertSvc);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_create", AspOutputGetError(nRet));
	CHECK_HANDLE(hAdvertSvc, "asp_advert_create");
	
	nRet = asp_advert_destroy(hAdvertSvc);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_destroy", AspOutputGetError(nRet));
	
	return 0;
}

//& purpose: Creates and destroyes the description of a seek operation
//& type : auto
/**
* @testcase 			ITc_asp_seek_create_destroy_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Creates and destroyes the description of a seek operation
* @scenario				Creates and destroyes the description of a seek operation
* @apicovered			asp_seek_create, asp_seek_destroy
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize
* @postcondition		Call API asp_deinitialize
*/
int ITc_asp_seek_create_destroy_p(void)
{
    START_TEST;
	
	char *pszSvcType = "Display";
	asp_seek_service_h hSeekSvc = NULL;
	
	int nRet = asp_seek_create(pszSvcType, &hSeekSvc);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_seek_create", AspOutputGetError(nRet));
	CHECK_HANDLE(hSeekSvc, "asp_seek_create");
	
	nRet = asp_seek_destroy(hSeekSvc);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_seek_destroy", AspOutputGetError(nRet));
	
	return 0;
}

//& purpose: Creates and destroys a local Application Service Platform (ASP) session
//& type : auto
/**
* @testcase 			ITc_asp_session_create_destroy_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Creates and destroyes the description of a seek operation
* @scenario				Creates and destroyes the description of a seek operation
* @apicovered			asp_session_create, asp_session_destroy
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize
* @postcondition		Call API asp_deinitialize
*/
int ITc_asp_session_create_destroy_p(void)
{
    START_TEST;
	
	asp_session_h hAspSession = NULL;
	char *pszSessionMac = "00:11:22:33:44:55";
	int nAdvId = 0x01;
	
	int nRet = asp_session_create(pszSessionMac, nAdvId, &hAspSession);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_create", AspOutputGetError(nRet));
	CHECK_HANDLE(hAspSession, "asp_session_create");
	
	nRet = asp_session_destroy(hAspSession);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_destroy", AspOutputGetError(nRet));
	
	return 0;
}

/** @} */
/** @} */