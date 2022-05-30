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
#include "ITs-mtp-common.h"

//& set: Mtp

/** @addtogroup itc-mtp
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_mtp_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_mtp_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_MTP_p\\n", __LINE__, API_NAMESPACE);
#endif

	IS_FEATURE_SUPPORTED(MTP_FEATURE, g_bMTPIsSupported, API_NAMESPACE);
	
	int nRetVal = mtp_initialize();
	if ( false == g_bMTPIsSupported )
	{
		if ( nRetVal != TIZEN_ERROR_NOT_SUPPORTED )
		{
			g_bMTPMismatch = true;
		}
		else
		{
			g_bMTPNotSupported = true;
		}
		return;
	}

	if ( nRetVal != MTP_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] MTP initialization failed, error returned = %s\\n", __LINE__, API_NAMESPACE, MTPGetError(nRetVal));
		g_bMTPInit = false;
	}
	else
	{
		FPRINTF("[Line : %d][%s] MTP initialized successfully\\n", __LINE__, API_NAMESPACE);
		g_bMTPInit = true;
	}
	return;
}


/**
 * @function 		ITs_mtp_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_mtp_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_MTP_p\\n", __LINE__, API_NAMESPACE);
#endif
	if ( g_bMTPInit )
	{
		int nRetVal = mtp_deinitialize();
		if ( nRetVal != MTP_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] MTP de-initialization failed, error returned = %s\\n", __LINE__, API_NAMESPACE, MTPGetError(nRetVal));
		}
		else
		{
			FPRINTF("[Line : %d][%s] MTP de-initialized successfully\\n", __LINE__, API_NAMESPACE);
		}
	}
	return;
}

//& purpose: Initialize and Deinitialize the MTP API
//& type: auto
/**
* @testcase 			ITc_mtp_initialize_deinitialize_p
* @since_tizen			3.0
* @type 				auto
* @description			Initialize and Deinitialize the MTP API
* @scenario				Initialize MTP API\n
*						Deinitialize MTP API
* @apicovered			mtp_initialize and mtp_deinitialize
* @passcase				When mtp_initialize and mtp_deinitialize is successful
* @failcase				If target API mtp_initialize or mtp_deinitialize fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mtp_initialize_deinitialize_p(void)
{
	START_TEST;

	int nRetVal = mtp_deinitialize();
	PRINT_RESULT(MTP_ERROR_NONE, nRetVal, "mtp_deinitialize", MTPGetError(nRetVal));

	nRetVal = mtp_initialize();
	PRINT_RESULT(MTP_ERROR_NONE, nRetVal, "mtp_initialize", MTPGetError(nRetVal));

	nRetVal = mtp_deinitialize();
	PRINT_RESULT(MTP_ERROR_NONE, nRetVal, "mtp_deinitialize", MTPGetError(nRetVal));

	nRetVal = mtp_initialize();
	PRINT_RESULT(MTP_ERROR_NONE, nRetVal, "mtp_initialize", MTPGetError(nRetVal));
	return 0;
}

/** @} */
/** @} */