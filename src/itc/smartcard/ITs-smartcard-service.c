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
#include "ITs-smartcard-common.h"

//& set: Smartcard

/**
 * @function 		ITs_smartcard_service_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_smartcard_service_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Smartcard_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bIsUICCSupported = TCTCheckSystemInfoFeatureSupported(SE_UICC_FEATURE, API_NAMESPACE);
	g_bIsESESupported = TCTCheckSystemInfoFeatureSupported(SE_ESE_FEATURE, API_NAMESPACE);
	g_bIsSmartcardSupported = g_bIsUICCSupported || g_bIsESESupported;

	g_bIsFeatureMismatched = false;
	g_bIsServiceInitialized = false;
	
	int nRet = smartcard_initialize();
	if ( !g_bIsSmartcardSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] smartcard_initialize failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, SmartcardGetError(nRet), nRet);
			g_bIsFeatureMismatched = true;
			return;
		}
		
		FPRINTF("[Line : %d][%s] smartcard_initialize is unsupported\\n", __LINE__, API_NAMESPACE);
		g_bIsFeatureMismatched = false;
	}
	else if ( nRet != SMARTCARD_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] smartcard_initialize failed, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, SmartcardGetError(nRet), nRet);
		g_bIsServiceInitialized = false;
	}
	else
	{
		g_bIsServiceInitialized = true;
	}
	
	return;
}

/**
 * @function 		ITs_smartcard_service_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_smartcard_service_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Smartcard_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet = smartcard_deinitialize();
	if ( !g_bIsSmartcardSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] smartcard_deinitialize failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, SmartcardGetError(nRet), nRet);
			return;
		}
		
		FPRINTF("[Line : %d][%s] smartcard_deinitialize is unsupported\\n", __LINE__, API_NAMESPACE);
	}
	if ( nRet != SMARTCARD_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] smartcard_deinitialize failed, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, SmartcardGetError(nRet), nRet);
	}
	return;
}

//& purpose Gets the list of available Secure Element readers
//& type: auto
/**
* @testcase 		ITc_smartcard_get_readers_p
* @since_tizen		2.3.1
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		Gets the list of available Secure Element readers
* @scenario			Initialize smartcard service\n
*					Get the list of available Secure Element readers\n
*					De-initialize smartcard service
* @apicovered		smartcard_get_readers
* @passcase			If smartcard_get_readers and all supporting APIs are successful
* @failcase			If smartcard_get_readers or any supporting API is failed
* @precondition		NA
* @postcondition	NA
*/
int ITc_smartcard_get_readers_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	int* pnReaders = NULL;
	int nLength = 0;
	
	// Target API
	int nRet = smartcard_get_readers(&pnReaders, &nLength);
	PRINT_RESULT(SMARTCARD_ERROR_NONE, nRet, "smartcard_get_readers", SmartcardGetError(nRet));
	
	FPRINTF("[Line : %d][%s] smartcard_get_readers returned %d readers\\n", __LINE__, API_NAMESPACE, nLength);
	
	FREE_MEMORY(pnReaders);
	
	return 0;
}
