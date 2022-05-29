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
 * @function 		ITs_smartcard_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_smartcard_startup(void)
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

	return;
}

/**
 * @function 		ITs_smartcard_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_smartcard_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Smartcard_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& purpose Initializes and deinitializes smartcard service
//& type: auto
/**
* @testcase 		ITc_smartcard_initialize_deinitialize_p
* @since_tizen		2.3.1
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		Initializes and deinitializes smartcard service
* @scenario			Initialize smartcard service\n
*					De-initialize smartcard service
* @apicovered		smartcard_initialize, smartcard_deinitialize
* @passcase			If initialization and deinitialization of service is successful
* @failcase			If failed to initialize or deinitialize the service
* @precondition		NA
* @postcondition	NA
*/
int ITc_smartcard_initialize_deinitialize_p(void)
{
	START_TEST;

	// Target API
	int nRet = smartcard_initialize();
	if ( !g_bIsSmartcardSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] smartcard_initialize failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, SmartcardGetError(nRet), nRet);
			return 1;
		}
		
		FPRINTF("[Line : %d][%s] smartcard_initialize is unsupported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	PRINT_RESULT(SMARTCARD_ERROR_NONE, nRet, "smartcard_initialize", SmartcardGetError(nRet));
	
	// Target API
	nRet = smartcard_deinitialize();
	if ( !g_bIsSmartcardSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] smartcard_deinitialize failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, SmartcardGetError(nRet), nRet);
			return 1;
		}
		
		FPRINTF("[Line : %d][%s] smartcard_deinitialize is unsupported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	
	PRINT_RESULT(SMARTCARD_ERROR_NONE, nRet, "smartcard_deinitialize", SmartcardGetError(nRet));
	return 0;
}
