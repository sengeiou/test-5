//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
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
#include "ITs-capi-network-ua-common.h"

//& set: CapiNetwork-ua

/** @addtogroup itc-capi-network-ua
*  @ingroup itc
*  @{
*/
/**
 * @function 		ITs_capi_network_ua_user_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_capi_network_ua_user_startup(void)
{
	g_bUaInit = false;
	g_hUser = NULL;
	g_bIsUaFeatureSupported = false;
	g_bFeatureByPass = false;
	char pszAccountStr[] = {"default@default.com"};

	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	int nRet = UA_ERROR_NONE;

	g_bIsUaFeatureSupported = TCTCheckSystemInfoFeatureSupported(UA_FEATURE, API_NAMESPACE);

	nRet = ua_initialize();
	if(!g_bIsUaFeatureSupported)
	{
		if ( nRet != UA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] ua_initialize failed to return UA_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)\\n", __FILE__, __LINE__,nRet);
			return;
		}

		FPRINTF("[%s:%d] feature and ua_initialize is unsupported\\n", __FILE__, __LINE__);
		g_bFeatureByPass = true;
		return;
	}
	else if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_ALREADY_DONE)
	{
		FPRINTF("[%s:%d] ua_initialize failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		g_bUaInit = false;
		return;
	}
	nRet = ua_user_create(pszAccountStr, &g_hUser);
	if ( nRet != UA_ERROR_NONE )
	{
		FPRINTF("[%s:%d] ua_user_create failed ,error returned = (%d)\\n", __FILE__, __LINE__,nRet);
		g_bUaInit = false;
		return;
	}
	if(g_hUser == NULL)
	{
		FPRINTF("[%s:%d] g_hUser is NULL\\n", __FILE__, __LINE__);
		g_bUaInit = false;
		return;
	}
	g_bUaInit = true;
}

/**
 * @function 		ITs_capi_network_ua_user_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_capi_network_ua_user_cleanup(void)
{
	int nRet = UA_ERROR_NONE;

	if (g_bIsUaFeatureSupported && g_bUaInit)
	{
		if(g_hUser)
		{
			nRet = ua_user_destroy(g_hUser);
			if ( nRet != UA_ERROR_NONE )
			{
				FPRINTF("[%s:%d] ua_user_destroy fail, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
			}
		}
		nRet = ua_deinitialize();
		if ( nRet != UA_ERROR_NONE )
		{
			FPRINTF("[%s:%d] ua_deinitialize failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		}
	}
	return;
}

//& purpose: Creates and Destroys the user handle.
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_user_create_destroy_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates and Destroys the user handle.
* @scenario				Creates and Destroys the user handle.
* @apicovered			ua_user_create,ua_user_destroy
* @passcase				If ua_user_create,ua_user_destroy is successfull
* @failcase 			If ua_user_create,ua_user_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_user_create_destroy_p(void)
{
	START_TEST;

	char pszAccountStr[] = {"default@default.com"};

	//Target API
	int nRet = ua_user_destroy(g_hUser);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_user_destroy", UaGetError(nRet));

	//Target API
	nRet = ua_user_create(pszAccountStr, &g_hUser);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_user_create", UaGetError(nRet));
	CHECK_HANDLE(g_hUser, "ua_user_create");

	return 0;
}

//& purpose: Adds, Removes the user handle.
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_user_add_remove_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Adds, Removes the user handle.
* @scenario				Adds, Removes the user handle.
* @apicovered			ua_user_add,ua_user_remove
* @passcase				If ua_user_add,ua_user_remove is successfull
* @failcase 			If ua_user_add,ua_user_remove fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_user_add_remove_p(void)
{
	START_TEST;

	//Target API
	int nRet = ua_user_add(g_hUser);
	if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_ALREADY_REGISTERED)
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_user_add", UaGetError(nRet), nRet);
		return 1;
	}
	//Target API
	nRet = ua_user_remove(g_hUser);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_user_remove", UaGetError(nRet));

	return 0;
}

//& purpose: Gets account info for user handle
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_user_get_account_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets account info for user handle.
* @scenario				Gets account info for user handle.
* @apicovered			ua_user_get_account
* @passcase				If ua_user_get_account is successfull
* @failcase 			If ua_user_get_account fails
* @precondition			NA
* @postcondition		must release account
*/
int ITc_capi_network_ua_user_get_account_p(void)
{
	START_TEST;

	char *pszAccount = NULL;

	//Target API
	int nRet = ua_user_get_account(g_hUser, &pszAccount);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_user_get_account", UaGetError(nRet));
	CHECK_HANDLE(pszAccount, "ua_user_get_account");
	FREE_MEMORY(pszAccount);

	return 0;
}