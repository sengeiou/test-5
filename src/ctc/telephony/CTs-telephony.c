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
#include "CTs-telephony-common.h"

/** @addtogroup ctc-telephony
* @ingroup		ctc
* @{
*/

//& set: Telephony

/**
* @function 		CTs_telephony_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_telephony_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Telephony_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function 		CTs_telephony_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_telephony_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Telephony_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup	ctc-telephony-testcases
* @brief 		Integration testcases for module telephony
* @ingroup		ctc-telephony
* @{
*/

//& purpose: A purpose of sending SMS in device if it supports.
//&type: auto
/**
* @testcase			CTc_telephony_IsSupportedSMS_MMS_p
* @since_tizen		2.3
* @author			SRID(saurabh.s9)
* @reviewer         SRID(gupta.sanjay)
* @type 			auto
* @scenario			Gets a boolean value of the platform feature\n
* 					Gets a boolean value of the platform feature for SMS sending
* @apicovered		system_info_get_platform_bool
* @passcase			Covered api should return zero success value
* @failcase			Covered api returns negative error value 
* @precondition		NA
* @postcondition	NA
*/
int CTc_telephony_IsSupportedSMS_p(void)
{
	START_TEST;

	bool bIsTelephonySupported;
	IS_FEATURE_SUPPORTED(TELEPHONY_FEATURE, bIsTelephonySupported, API_NAMESPACE)
	if ( !bIsTelephonySupported )
	{
		FPRINTF("[Line : %d][%s] Telephony is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	
	FPRINTF("[Line : %d][%s] Telephony feature is supported\\n", __LINE__, API_NAMESPACE);
	
	bool bIsSmsSupported;
	IS_FEATURE_SUPPORTED(SMS_FEATURE, bIsSmsSupported, API_NAMESPACE)
	
	messages_service_h hMessageService = NULL;
	if ( !bIsSmsSupported )
	{
		FPRINTF("[Line : %d][%s] Telephony is supported but SMS (messaging) is not supported\\n", __LINE__, API_NAMESPACE);
		
		int nRet = messages_open_service(&hMessageService);
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] messages_open_service return %s for unsupported SMS feature\\n",__LINE__, API_NAMESPACE, MessagesGetError(nRet));
			return 1;
		}
		
		FPRINTF("[Line : %d][%s] messages_open_service returned TIZEN_ERROR_NOT_SUPPORTED for unsupported SMS feature\\n",__LINE__, API_NAMESPACE);
		return 0;
	}
	
	FPRINTF("[Line : %d][%s] SMS feature is supported\\n", __LINE__, API_NAMESPACE);
	
	int nRet = messages_open_service(&hMessageService);
	if ( nRet != MESSAGES_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] messages_open_service returned %s for supported SMS feature\\n",__LINE__, API_NAMESPACE, MessagesGetError(nRet));
		return 1;
	}
	
	if(hMessageService == NULL)
	{
		FPRINTF("[Line : %d][%s] messages_open_service failed. hMessageService is NULL\\n",__LINE__, API_NAMESPACE);
		return 1;
	}
	
	FPRINTF("[Line : %d][%s] messages_open_service API didn't return any error for supported telephony feature\\n",__LINE__, API_NAMESPACE);

	nRet = messages_close_service(hMessageService);
	if ( nRet != MESSAGES_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] messages_close_service returned %s for supported SMS feature\\n",__LINE__, API_NAMESPACE, MessagesGetError(nRet));
		return 1;
	}
	
	FPRINTF("[Line : %d][%s] messages_close_service API didn't return any error for supported telephony feature\\n",__LINE__, API_NAMESPACE);
	return 0;
}

/** @} */ //end of ctc-telephony
/** @} */ //end of ctc-telephony-testcases