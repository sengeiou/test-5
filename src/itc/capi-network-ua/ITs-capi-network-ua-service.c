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
 * @function 		ITs_capi_network_ua_service_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_capi_network_ua_service_startup(void)
{
	g_bUaInit = false;
	g_bIsUaFeatureSupported = false;
	g_bFeatureByPass = false;
	g_hService = NULL;

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
	nRet = ua_service_create(g_hServiceStr, &g_hService);
	if ( nRet != UA_ERROR_NONE )
	{
		FPRINTF("[%s:%d] ua_service_create fail , error returned = (%d)\\n", __FILE__, __LINE__,nRet);
		g_bUaInit = false;
		return;
	}
	if(g_hService == NULL)
	{
		g_bUaInit = false;
		return;
	}
	g_bUaInit = true;
}


/**
 * @function 		ITs_capi_network_ua_service_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_capi_network_ua_service_cleanup(void)
{
	int nRet = UA_ERROR_NONE;

	if (g_bIsUaFeatureSupported && g_bUaInit)
	{
		if(g_hService)
		{
			nRet = ua_service_destroy(g_hService);
			if ( nRet != UA_ERROR_NONE )
			{
				FPRINTF("[%s:%d] ua_service_destroy failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
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
/**
 * @function 		CapiNetworkUaForeachServiceCallBack
 * @description	 	Callback Function
 * @parameter		ua_service_h service_handle, void *user_data
 * @return 			bool
 */
static bool CapiNetworkUaForeachServiceCallBack( ua_service_h service_handle, void *user_data )
{
	g_bCallBackHit = true;
	return true;
}
/**
 * @function 		CapiNetworkUaServiceForeachAddedUserCallBack
 * @description	 	Callback Function
 * @parameter		ua_service_h service_handle, ua_user_h user_handle, void *user_data
 * @return 			bool
 */
static bool CapiNetworkUaServiceForeachAddedUserCallBack( ua_service_h service_handle, ua_user_h user_handle, void *user_data)
{
	return true;
}
//& purpose: Creates and Destroys the service handle
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_service_create_destroy_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates and Destroys the service handle.
* @scenario				Creates and Destroys the service handle.
* @apicovered			ua_service_create,ua_service_destroy
* @passcase				If ua_service_create,ua_service_destroy is successfull
* @failcase 			If ua_service_create,ua_service_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_service_create_destroy_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;

	//Target API
	nRet = ua_service_destroy(g_hService);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_service_destroy", UaGetError(nRet));

	//Target API
	nRet = ua_service_create(g_hServiceStr, &g_hService);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_service_create", UaGetError(nRet));
	CHECK_HANDLE(g_hService, "ua_service_create");

	return 0;
}


//& purpose: Adds and Removes the service handle
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_service_add_remove_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Adds and Removes the service handle.
* @scenario				Adds and Removes the service handle.
* @apicovered			ua_service_add,ua_service_remove
* @passcase				If ua_service_add,ua_service_remove is successfull
* @failcase 			If ua_service_add,ua_service_remove fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_service_add_remove_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;

	//Target API
	nRet = ua_service_add(g_hService);
	if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_ALREADY_REGISTERED)
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_service_add", UaGetError(nRet), nRet);
		return 1;
	}
	else
		FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, "ua_service_add");
	//Target API
	nRet = ua_service_remove(g_hService);
	if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_NOT_REGISTERED)
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_service_remove", UaGetError(nRet), nRet);
		return 1;
	}
	else
		FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, "ua_service_remove");

	return 0;
}
//& purpose: Retrieves handles of all added services.
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_foreach_service_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Retrieves handles of all added services.
* @scenario				Retrieves handles of all added services.
* @apicovered			ua_foreach_service
* @passcase				If ua_foreach_service is successfull
* @failcase 			If ua_foreach_service fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_foreach_service_p(void)
{
	START_TEST;

	g_bCallBackHit = false;

	//Target API
	int nRet = ua_foreach_service(CapiNetworkUaForeachServiceCallBack, NULL);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_foreach_service", UaGetError(nRet));
	PRINT_RESULT(true, g_bCallBackHit, "ua_foreach_service", "CallBack Not Invoked");

	return 0;
}
//& purpose: Gets default service handle
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_get_default_service_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets default service handle.
* @scenario				Gets default service handle.
* @apicovered			ua_get_default_service
* @passcase				If ua_get_default_service is successfull
* @failcase 			If ua_get_default_service fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_get_default_service_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	ua_service_h hService = NULL;
	//Target API
	nRet = ua_get_default_service(&hService);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_get_default_service", UaGetError(nRet));
	CHECK_HANDLE(hService, "ua_get_default_service");

	return 0;
}

//& purpose: Updates the properties for the added service
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_service_update_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Updates the properties for the added service.
* @scenario				Updates the properties for the added service.
* @apicovered			ua_service_update
* @passcase				If ua_service_update is successfull
* @failcase 			If ua_service_update fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_service_update_p(void)
{
	START_TEST;

	ua_service_h hService = NULL;
	int nRet = ua_get_default_service(&hService);
	if (nRet != UA_ERROR_NONE)
	{
		nRet = ua_service_create(g_hServiceStr, &hService);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_service_create", UaGetError(nRet));
		CHECK_HANDLE(hService, "ua_service_create");

		nRet = ua_service_add(hService);
		if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_ALREADY_REGISTERED)
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_service_add", UaGetError(nRet), nRet);
			ua_service_destroy(hService);
			return 1;
		}
		//Target API
		nRet = ua_service_update(hService);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_service_update", UaGetError(nRet), ua_service_remove(hService); ua_service_destroy(hService));

		nRet = ua_service_remove(hService);
		if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_NOT_REGISTERED)
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_service_remove", UaGetError(nRet), nRet);
			ua_service_destroy(hService);
			return 1;
		}
		nRet = ua_service_destroy(hService);
		PRINT_RESULT_NORETURN(UA_ERROR_NONE, nRet, "ua_service_destroy", UaGetError(nRet));
	}
	else
	{
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_get_default_service", UaGetError(nRet));
		CHECK_HANDLE(hService, "ua_get_default_service");
		//Target API
		nRet = ua_service_update(hService);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_service_update", UaGetError(nRet));
	}
	return 0;
}
//& purpose: Gets name info for service handle
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_service_get_name_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets name info for service handle
* @scenario				Gets name info for service handle
* @apicovered			ua_service_get_name
* @passcase				If ua_service_get_name is successfull
* @failcase 			If ua_service_get_name fails
* @precondition			NA
* @postcondition		You must release name
*/
int ITc_capi_network_ua_service_get_name_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	char *pszServiceName = NULL;

	//Target API
	nRet = ua_service_get_name(g_hService, &pszServiceName);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_service_get_name", UaGetError(nRet));
	if(strcmp(g_hServiceStr,pszServiceName) != 0)
	{
		FPRINTF("[Line : %d][%s] ua_service_get_name, error = service name is not same. service name = %s output service name = %s \\n", __LINE__, API_NAMESPACE, g_hServiceStr, pszServiceName);
		FREE_MEMORY(pszServiceName);
		return 1;
	}
	FREE_MEMORY(pszServiceName);
	return 0;
}
//& purpose: Sets and Gets detection threshold for service handle
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_service_set_get_detection_threshold_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets detection threshold for service handle
* @scenario				Sets and Gets detection threshold for service handle
* @apicovered			ua_service_set_detection_threshold, ua_service_get_detection_threshold
* @passcase				If ua_service_set_detection_threshold, ua_service_get_detection_threshold is successfull
* @failcase 			If ua_service_set_detection_threshold, ua_service_get_detection_threshold fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_service_set_get_detection_threshold_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	ua_service_h hService = NULL;
	unsigned int nSetPresenceThresh = 0;
	unsigned int nSetAbsenceThresh = 0;
	unsigned int nGetPresenceThresh = 0;
	unsigned int nGetAbsenceThresh = 0;

	//Target API
	nRet = ua_service_set_detection_threshold(g_hService, nSetPresenceThresh, nSetAbsenceThresh);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_service_set_detection_threshold", UaGetError(nRet));
	//Target API
	nRet = ua_service_get_detection_threshold(g_hService, &nGetPresenceThresh, &nGetAbsenceThresh);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_service_get_detection_threshold", UaGetError(nRet));
	if( (nSetPresenceThresh != nGetPresenceThresh) || (nSetAbsenceThresh != nGetAbsenceThresh) )
	{
		FPRINTF("\\n [Line : %d][%s] ua_service_detection_threshold set and get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Gets service handle by service name for added service
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_get_service_by_name_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets service handle by service name for added service.
* @scenario				Gets service handle by service name for added service..
* @apicovered			ua_get_service_by_name
* @passcase				If ua_get_service_by_name is successfull
* @failcase 			If ua_get_service_by_name fails
* @precondition			NA
* @postcondition		service handle should be destroyed by using ua_service_destroy()
*/
int ITc_capi_network_ua_get_service_by_name_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;

	//Target API
	nRet = ua_get_service_by_name(g_hServiceStr, &g_hService);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_get_service_by_name", UaGetError(nRet));
	CHECK_HANDLE(g_hService, "ua_get_service_by_name");

	return 0;
}
//& purpose: Adds and Removes a user for a specific service.
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_service_add_remove_user_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Adds and Removes a user for a specific service.
* @scenario				Adds and Removes a user for a specific service.
* @apicovered			ua_service_add_user, ua_service_remove_user
* @passcase				If ua_service_add_user, ua_service_remove_user is successfull
* @failcase 			If ua_service_add_user, ua_service_remove_user fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_service_add_remove_user_p(void)
{
	START_TEST;

	ua_service_h hService = NULL;
	ua_user_h hUser = NULL;
	char pszAccountStr[] = {"default@default.com"};
	int nRet = ua_get_default_service(&hService);

	if (nRet != UA_ERROR_NONE)
	{
		nRet = ua_service_create(g_hServiceStr, &hService);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_service_create", UaGetError(nRet));
		CHECK_HANDLE(hService, "ua_service_create");

		nRet = ua_service_add(hService);
		if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_ALREADY_REGISTERED)
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_service_add", UaGetError(nRet), nRet);
			ua_service_destroy(hService);
			return 1;
		}
		nRet = ua_user_create(pszAccountStr, &hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_user_create", UaGetError(nRet), ua_service_remove(hService); ua_service_destroy(hService));
		CHECK_HANDLE_CLEANUP(hUser, "ua_user_create", ua_service_remove(hService); ua_service_destroy(hService));

		nRet = ua_user_add(hUser);
		if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_ALREADY_REGISTERED)
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_user_add", UaGetError(nRet), nRet);
			ua_user_destroy(hUser);
			ua_service_remove(hService);
			ua_service_destroy(hService);
			return 1;
		}
		//Target API
		nRet = ua_service_add_user(hService, hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_service_add_user", UaGetError(nRet), ua_user_remove(hUser); ua_user_destroy(hUser); ua_service_remove(hService); ua_service_destroy(hService));
		//Target API
		nRet = ua_service_remove_user(hService, hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_service_remove_user", UaGetError(nRet), ua_user_remove(hUser); ua_user_destroy(hUser); ua_service_remove(hService); ua_service_destroy(hService));

		nRet = ua_user_remove(hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_user_remove", UaGetError(nRet), ua_user_destroy(hUser); ua_service_remove(hService); ua_service_destroy(hService));

		nRet = ua_user_destroy(hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_user_destroy", UaGetError(nRet), ua_service_remove(hService); ua_service_destroy(hService));

		nRet = ua_service_remove(hService);
		if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_NOT_REGISTERED)
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_service_remove", UaGetError(nRet), nRet);
			ua_service_destroy(hService);
			return 1;
		}
		nRet = ua_service_destroy(hService);
		PRINT_RESULT_NORETURN(UA_ERROR_NONE, nRet, "ua_service_destroy", UaGetError(nRet));
	}
	else
	{
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_get_default_service", UaGetError(nRet));
		CHECK_HANDLE(hService, "ua_get_default_service");

		nRet = ua_user_create(pszAccountStr, &hUser);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_user_create", UaGetError(nRet));
		CHECK_HANDLE(hUser, "ua_user_create");

		nRet = ua_user_add(hUser);
		if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_ALREADY_REGISTERED)
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_user_add", UaGetError(nRet), nRet);
			ua_user_destroy(hUser);
			return 1;
		}
		//Target API
		nRet = ua_service_add_user(hService, hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_service_add_user", UaGetError(nRet), ua_user_remove(hUser); ua_user_destroy(hUser));
		//Target API
		nRet = ua_service_remove_user(hService, hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_service_remove_user", UaGetError(nRet), ua_user_remove(hUser); ua_user_destroy(hUser));

		nRet = ua_user_remove(hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_user_remove", UaGetError(nRet), ua_user_destroy(hUser));

		nRet = ua_user_destroy(hUser);
		PRINT_RESULT_NORETURN(UA_ERROR_NONE, nRet, "ua_user_destroy", UaGetError(nRet));
	}
	return 0;
}
//& purpose: Triggers callback for every user of a specific service.
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_service_foreach_users_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Triggers callback for every user of a specific service.
* @scenario				Triggers callback for every user of a specific service.
* @apicovered			ua_service_foreach_users
* @passcase				If ua_service_foreach_users is successfull
* @failcase 			If ua_service_foreach_users fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_service_foreach_users_p(void)
{
	START_TEST;

	ua_service_h hService = NULL;
	ua_user_h hUser = NULL;
	char pszAccountStr[] = {"default@default.com"};

	int nRet = ua_get_default_service(&hService);
	if (nRet != UA_ERROR_NONE)
	{
		nRet = ua_service_create(g_hServiceStr, &hService);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_service_create", UaGetError(nRet));
		CHECK_HANDLE(hService, "ua_service_create");

		nRet = ua_service_add(hService);
		if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_ALREADY_REGISTERED)
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_service_add", UaGetError(nRet), nRet);
			ua_service_destroy(hService);
			return 1;
		}
		nRet = ua_user_create(pszAccountStr, &hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_user_create", UaGetError(nRet), ua_service_remove(hService); ua_service_destroy(hService));
		CHECK_HANDLE_CLEANUP(hUser, "ua_user_create", ua_service_remove(hService); ua_service_destroy(hService));

		nRet = ua_user_add(hUser);
		if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_ALREADY_REGISTERED)
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_user_add", UaGetError(nRet), nRet);
			ua_user_destroy(hUser);
			ua_service_remove(hService);
			ua_service_destroy(hService);
			return 1;
		}
		nRet = ua_service_add_user(hService, hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_service_add_user", UaGetError(nRet), ua_user_remove(hUser); ua_user_destroy(hUser); ua_service_remove(hService); ua_service_destroy(hService));

		//Target API
		nRet = ua_service_foreach_users(hService, CapiNetworkUaServiceForeachAddedUserCallBack, NULL);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_service_foreach_users", UaGetError(nRet), ua_service_remove_user(hService, hUser); ua_user_remove(hUser); ua_user_destroy(hUser); ua_service_remove(hService); ua_service_destroy(hService));

		nRet = ua_service_remove_user(hService, hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_service_remove_user", UaGetError(nRet), ua_user_remove(hUser); ua_user_destroy(hUser); ua_service_remove(hService); ua_service_destroy(hService));

		nRet = ua_user_remove(hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_user_remove", UaGetError(nRet), ua_user_destroy(hUser); ua_service_remove(hService); ua_service_destroy(hService));

		nRet = ua_user_destroy(hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_user_destroy", UaGetError(nRet), ua_service_remove(hService); ua_service_destroy(hService));

		nRet = ua_service_remove(hService);
		if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_NOT_REGISTERED)
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_service_remove", UaGetError(nRet), nRet);
			ua_service_destroy(hService);
			return 1;
		}
		nRet = ua_service_destroy(hService);
		PRINT_RESULT_NORETURN(UA_ERROR_NONE, nRet, "ua_service_destroy", UaGetError(nRet));
	}
	else
	{
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_get_default_service", UaGetError(nRet));
		CHECK_HANDLE(hService, "ua_get_default_service");

		nRet = ua_user_create(pszAccountStr, &hUser);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_user_create", UaGetError(nRet));
		CHECK_HANDLE(hUser, "ua_user_create");

		nRet = ua_user_add(hUser);
		if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_ALREADY_REGISTERED)
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_user_add", UaGetError(nRet), nRet);
			ua_user_destroy(hUser);
			return 1;
		}
		nRet = ua_service_add_user(hService, hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_service_add_user", UaGetError(nRet), ua_user_remove(hUser); ua_user_destroy(hUser));

		//Target API
		nRet = ua_service_foreach_users(hService, CapiNetworkUaServiceForeachAddedUserCallBack, NULL);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_service_foreach_users", UaGetError(nRet), ua_service_remove_user(hService, hUser); ua_user_remove(hUser); ua_user_destroy(hUser));

		nRet = ua_service_remove_user(hService, hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_service_remove_user", UaGetError(nRet), ua_user_remove(hUser); ua_user_destroy(hUser));

		nRet = ua_user_remove(hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_user_remove", UaGetError(nRet), ua_user_destroy(hUser));

		nRet = ua_user_destroy(hUser);
		PRINT_RESULT_NORETURN(UA_ERROR_NONE, nRet, "ua_user_destroy", UaGetError(nRet));
	}
	return 0;
}
//& purpose: Sets name info for service handle.
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_service_get_user_by_account_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets name info for service handle.
* @scenario				Sets name info for service handle.
* @apicovered			ua_service_get_user_by_account
* @passcase				If ua_service_get_user_by_account is successfull
* @failcase 			If ua_service_get_user_by_account fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_service_get_user_by_account_p(void)
{
	START_TEST;

	ua_service_h hService = NULL;
	ua_user_h hUser = NULL;
	char pszAccountStr[] = {"default@default.com"};
	int nRet = ua_get_default_service(&hService);

	if (nRet != UA_ERROR_NONE)
	{
		nRet = ua_service_create(g_hServiceStr, &hService);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_service_create", UaGetError(nRet));
		CHECK_HANDLE(hService, "ua_service_create");

		nRet = ua_service_add(hService);
		if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_ALREADY_REGISTERED)
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_service_add", UaGetError(nRet), nRet);
			ua_service_destroy(hService);
			return 1;
		}
		nRet = ua_user_create(pszAccountStr, &hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_user_create", UaGetError(nRet), ua_service_remove(hService); ua_service_destroy(hService));
		CHECK_HANDLE_CLEANUP(hUser, "ua_user_create", ua_service_remove(hService); ua_service_destroy(hService));

		nRet = ua_user_add(hUser);
		if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_ALREADY_REGISTERED)
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_user_add", UaGetError(nRet), nRet);
			ua_user_destroy(hUser);
			ua_service_remove(hService);
			ua_service_destroy(hService);
			return 1;
		}
		nRet = ua_service_add_user(hService, hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_service_add_user", UaGetError(nRet), ua_user_remove(hUser); ua_user_destroy(hUser); ua_service_remove(hService); ua_service_destroy(hService));
		//Target API
		nRet = ua_service_get_user_by_account(hService, pszAccountStr, &hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_service_get_user_by_account", UaGetError(nRet), ua_service_remove_user(hService, hUser); ua_user_remove(hUser); ua_user_destroy(hUser); ua_service_remove(hService); ua_service_destroy(hService));
		CHECK_HANDLE_CLEANUP(hUser, "ua_service_get_user_by_account", ua_service_remove_user(hService, hUser); ua_user_remove(hUser); ua_user_destroy(hUser); ua_service_remove(hService); ua_service_destroy(hService));

		nRet = ua_service_remove_user(hService, hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_service_remove_user", UaGetError(nRet), ua_user_remove(hUser); ua_user_destroy(hUser); ua_service_remove(hService); ua_service_destroy(hService));

		nRet = ua_user_remove(hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_user_remove", UaGetError(nRet), ua_user_destroy(hUser); ua_service_remove(hService); ua_service_destroy(hService));

		nRet = ua_user_destroy(hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_user_remove", UaGetError(nRet), ua_service_remove(hService); ua_service_destroy(hService));

		nRet = ua_service_remove(hService);
		if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_NOT_REGISTERED)
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_service_remove", UaGetError(nRet), nRet);
			ua_service_destroy(hService);
			return 1;
		}
		nRet = ua_service_destroy(hService);
		PRINT_RESULT_NORETURN(UA_ERROR_NONE, nRet, "ua_service_destroy", UaGetError(nRet));
	}
	else
	{
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_get_default_service", UaGetError(nRet));
		CHECK_HANDLE(hService, "ua_get_default_service");

		nRet = ua_user_create(pszAccountStr, &hUser);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_user_create", UaGetError(nRet));
		CHECK_HANDLE(hUser, "ua_user_create");

		nRet = ua_user_add(hUser);
		if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_ALREADY_REGISTERED)
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_user_add", UaGetError(nRet), nRet);
			ua_user_destroy(hUser);
			return 1;
		}
		nRet = ua_service_add_user(hService, hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_service_add_user", UaGetError(nRet), ua_user_remove(hUser); ua_user_destroy(hUser));
		//Target API
		nRet = ua_service_get_user_by_account(hService, pszAccountStr, &hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_service_get_user_by_account", UaGetError(nRet), ua_service_remove_user(hService, hUser); ua_user_remove(hUser); ua_user_destroy(hUser));
		CHECK_HANDLE_CLEANUP(hUser, "ua_service_get_user_by_account", ua_service_remove_user(hService, hUser); ua_user_remove(hUser); ua_user_destroy(hUser));

		nRet = ua_service_remove_user(hService, hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_service_remove_user", UaGetError(nRet), ua_user_remove(hUser); ua_user_destroy(hUser));

		nRet = ua_user_remove(hUser);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_user_remove", UaGetError(nRet), ua_user_destroy(hUser));

		nRet = ua_user_destroy(hUser);
		PRINT_RESULT_NORETURN(UA_ERROR_NONE, nRet, "ua_user_destroy", UaGetError(nRet));
	}
	return 0;
}