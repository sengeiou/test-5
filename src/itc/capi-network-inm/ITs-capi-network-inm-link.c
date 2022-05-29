//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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
#include "ITs-capi-network-inm-common.h"

/** @addtogroup itc-capi-network-inm
*  @ingroup itc
*  @{
*/

//& set: Inm

/**
* @function 		ITs_inm_link_startup
* @description	 	Called before each test
* @parameter		NA
* @return 		NA
*/
void ITs_inm_link_startup(void)
{
	g_bFeatureInm = TCTCheckSystemInfoFeatureSupported(FEATURE_INM, API_NAMESPACE);

	g_hInmHandle = NULL;
	g_hLinkHandle = NULL;
	g_hAddressHandle = NULL;
	g_hRouteHandle = NULL;
	g_bInmCreation = false;
	g_bIsFeatureMismatched = false;
	g_bFeatureNotSupported = false;

	int nRet = inm_initialize(&g_hInmHandle);
	if(!g_bFeatureInm)
	{
		if(nRet != INM_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] inm_initialize failed due to feature mismatch.\\n", __LINE__, API_NAMESPACE);
			g_bIsFeatureMismatched = true;
			return;
		}
		else
		{
			g_bFeatureNotSupported = true;
			return;
		}
	}
	else
	{
		if(nRet != INM_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] inm_initialize failed. Error returned = %s\\n", __LINE__, API_NAMESPACE, InmGetError(nRet));
			return;
		}
	}
	if(g_hInmHandle == NULL)
	{
		FPRINTF("[Line : %d][%s] inm_initialize failed. Handle returned = %s, nRet = %s\\n", __LINE__, API_NAMESPACE, g_hInmHandle, InmGetError(nRet));
		return;
	}

	nRet = InmGetCurrentLink(&g_hLinkHandle);
	if(nRet != INM_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] InmGetCurrentLink failed. Error returned = %s\\n", __LINE__, API_NAMESPACE, InmGetError(nRet));
		return;
	}
	if(g_hLinkHandle == NULL)
	{
		FPRINTF("[Line : %d][%s] inmGetCurrentLink failed. Handle returned = %s, nRet = %s\\n", __LINE__, API_NAMESPACE, g_hLinkHandle, InmGetError(nRet));
		return;
	}
	g_bInmCreation = true;

	return;
}

/**
* @function 		ITs_inm_link_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 		NA
*/
void ITs_inm_link_cleanup(void)
{
	if(g_hLinkHandle != NULL)
	{
		int nRet = inm_link_destroy(g_hLinkHandle);
		if(nRet != INM_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] inm_link_destroy failed. Error returned = %s\\n", __LINE__, API_NAMESPACE, InmGetError(nRet));
		}
		g_hLinkHandle = NULL;
	}
	if(g_hInmHandle != NULL)
	{
		int nRet = inm_deinitialize(g_hInmHandle);
		if(nRet != INM_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] inm_deinitialize failed. Error returned = %s\\n", __LINE__, API_NAMESPACE, InmGetError(nRet));
		}
		g_hInmHandle = NULL;
	}
}

/****************************************************Callback Start****************************************************/

/**
 * @function 		InmLinkCb
 * @description	 	Callback Function
 * @parameter		inm_link_h link, void *user_data
 * @return 			NA
 */
static bool InmLinkCb(inm_link_h link, void *user_data)
{
	FPRINTF("Inside InmLinkCb callback");
	g_nCallbackRet = true;
	return false;
}

/**
 * @function 		InmLinkAddressCb
 * @description	 	Callback Function
 * @parameter		inm_link_address_h address, void *user_data
 * @return 			NA
 */
static bool InmLinkAddressCb(inm_link_address_h address, void *user_data)
{
	FPRINTF("Inside InmLinkAddressCb callback");
	g_nCallbackRet = true;
	if(address)
	{
		int nRet = inm_link_address_clone(&g_hAddressHandle, address);
		if(nRet != INM_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] inm_link_address_clone failed. Error returned = %s\\n", __LINE__, API_NAMESPACE, InmGetError(nRet));
			return false;
		}
		if(g_hAddressHandle == NULL)
		{
			FPRINTF("[Line : %d][%s] inm_link_address_clone failed. g_hAddressHandle is NULL\\n", __LINE__, API_NAMESPACE);
			return false;
		}
	}
	g_nCallbackFail = true;
	return false;
}

/**
 * @function 		InmLinkRouteCb
 * @description	 	Callback Function
 * @parameter		inm_link_route_h route, void *user_data
 * @return 			NA
 */
static bool  InmLinkRouteCb(inm_link_route_h route, void *user_data)
{
	FPRINTF("Inside InmLinkRouteCb callback");
	g_nCallbackRet = true;
	if (route)
	{
		int nRet = inm_link_route_clone(&g_hRouteHandle, route);
		if(nRet != INM_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] inm_link_route_clone failed. Error returned = %s\\n", __LINE__, API_NAMESPACE, InmGetError(nRet));
			return false;
		}
		if(g_hRouteHandle == NULL)
		{
			FPRINTF("[Line : %d][%s] inm_link_route_clone failed. g_hRouteHandle is NULL\\n", __LINE__, API_NAMESPACE);
			return false;
		}
	}
	g_nCallbackFail = true;
	return false;
}
/*****************************************************Callback End*****************************************************/

/** @addtogroup itc-inm-testcases
*  @brief 		Integration testcases for module capi-network-inm
*  @ingroup 	itc-inm
*  @{
*/

/**
* @testcase				ITc_inm_foreach_link_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Gets handles of the link.
* @scenario				Gets handles of the link.
* @apicovered			inm_foreach_link
* @passcase				inm_foreach_link return(s) 0
* @failcase				inm_foreach_link return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_foreach_link_p(void)
{
	START_TEST;

	g_nCallbackRet = false;

	int nRet = inm_foreach_link(g_hInmHandle, InmLinkCb, NULL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_foreach_link", InmGetError(nRet));
	if (g_nCallbackRet == false)
	{
		FPRINTF("Failed: InmLinkCb Callback not getting hit");
		return 1;
	}

	return 0;
}

/**
* @testcase				ITc_inm_connection_get_link_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Gets the link handle for this connection.
* @scenario				Gets the link handle for this connection.
* @apicovered			inm_connection_get_link
* @passcase				inm_connection_get_link return(s) 0
* @failcase				inm_connection_get_link return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_connection_get_link_p(void)
{
	START_TEST;

	inm_connection_h hConnectionHandle = NULL;
	inm_link_h hLinkHandle = NULL;

	int nRet = inm_get_current_connection(g_hInmHandle, &hConnectionHandle);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_get_current_connection", InmGetError(nRet));
	CHECK_HANDLE(hConnectionHandle, "inm_get_current_connection");

	nRet = inm_connection_get_link(hConnectionHandle, &hLinkHandle);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_link", InmGetError(nRet),inm_connection_destroy(&hConnectionHandle));
	CHECK_HANDLE_CLEANUP(hLinkHandle, "inm_connection_get_link",inm_connection_destroy(&hConnectionHandle));
	FREE_MEMORY(hLinkHandle);

	nRet = inm_connection_destroy(&hConnectionHandle);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_inm_link_destroy_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Destroys a link handle.
* @scenario				Destroys a link handle.
* @apicovered			inm_link_destroy
* @passcase				inm_link_destroy return(s) 0
* @failcase				inm_link_destroy return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_destroy_p(void)
{
	START_TEST;

	inm_link_h hLinkHandle = NULL;

	int nRet = InmGetCurrentLink(&hLinkHandle);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inmGetCurrentLink", InmGetError(nRet));
	CHECK_HANDLE(hLinkHandle, "inmGetCurrentLink");

	nRet = inm_link_destroy(hLinkHandle);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_inm_link_clone_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Clones a link handle.
* @scenario				Clones a link handle.
* @apicovered			inm_link_clone
* @passcase				inm_link_clone return(s) 0
* @failcase				inm_link_clone return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_clone_p(void)
{
	START_TEST;

	inm_link_h hCloned = NULL;

	int nRet = inm_link_clone(&hCloned, g_hLinkHandle);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_clone", InmGetError(nRet));
	CHECK_HANDLE(hCloned, "inm_link_clone");

	nRet = inm_link_destroy(hCloned);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_link_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_inm_link_get_interface_name_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Gets the link interface name.
* @scenario				Gets the link interface name.
* @apicovered			inm_link_get_interface_name
* @passcase				inm_link_get_interface_name return(s) 0
* @failcase				inm_link_get_interface_name return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_get_interface_name_p(void)
{
	START_TEST;

	char *pszInterfaceName = NULL;

	int nRet = inm_link_get_interface_name(g_hLinkHandle, &pszInterfaceName);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_get_interface_name", InmGetError(nRet));
	CHECK_HANDLE(pszInterfaceName, "inm_link_get_interface_name");
	FREE_MEMORY(pszInterfaceName);

	return 0;
}

/**
* @testcase				ITc_inm_link_get_flags_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Gets the link flags.
* @scenario				Gets the link flags.
* @apicovered			inm_link_get_flags
* @passcase				inm_link_get_flags return(s) 0
* @failcase				inm_link_get_flags return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_get_flags_p(void)
{
	START_TEST;

	int nFlags = -1;

	int nRet = inm_link_get_flags(g_hLinkHandle, &nFlags);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_get_flags", InmGetError(nRet));
	if( nFlags < 0 )
	{
		FPRINTF("[Line : %d][%s] %s failed. nFlags = %d\\n", __LINE__, API_NAMESPACE, "inm_link_get_flags", nFlags);
		return 1;
	}

	return 0;
}

/**
* @testcase				ITc_inm_link_get_operation_state_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Gets the link operation status.
* @scenario				Gets the link operation status.
* @apicovered			inm_link_get_operation_state
* @passcase				inm_link_get_operation_state return(s) 0
* @failcase				inm_link_get_operation_state return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_get_operation_state_p(void)
{
	START_TEST;

	inm_link_oper_state_e eOperationState = -1;

	int nRet = inm_link_get_operation_state(g_hLinkHandle, &eOperationState);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_get_operation_state", InmGetError(nRet));
	if( eOperationState < INM_LINK_OPER_UNKNOWN || eOperationState > INM_LINK_OPER_UP )
	{
		FPRINTF("[Line : %d][%s] %s failed. eOperationState = %d\\n", __LINE__, API_NAMESPACE, "inm_link_get_operation_state", eOperationState);
		return 1;
	}

	return 0;
}

/**
* @testcase				ITc_inm_link_get_received_bytes_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Gets the bytes received by the link.
* @scenario				Gets the bytes received by the link.
* @apicovered			inm_link_get_received_bytes
* @passcase				inm_link_get_received_bytes return(s) 0
* @failcase				inm_link_get_received_bytes return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_get_received_bytes_p(void)
{
	START_TEST;

	unsigned long long llBytes = 0;

	//As per developer,if interface has no recv/sent byte, llBytes should be zero so llBytes value is not checked
	int nRet = inm_link_get_received_bytes(g_hLinkHandle, &llBytes);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_get_received_bytes", InmGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_inm_link_get_sent_bytes_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Gets the bytes sent by the link.
* @scenario				Gets the bytes sent by the link.
* @apicovered			inm_link_get_sent_bytes
* @passcase				inm_link_get_sent_bytes return(s) 0
* @failcase				inm_link_get_sent_bytes return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_get_sent_bytes_p(void)
{
	START_TEST;

	unsigned long long llBytes = 0;

	//As per developer,if interface has no recv/sent byte, llBytes should be zero so llBytes value is not checked
	int nRet = inm_link_get_sent_bytes(g_hLinkHandle, &llBytes);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_get_sent_bytes", InmGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_inm_link_foreach_address_destroy_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Gets all addresses of the link and destroy address link handle.
* @scenario				Gets all addresses of the link and destroy address link handle.
* @apicovered			inm_link_foreach_address and inm_link_address_destroy
* @passcase				inm_link_foreach_address and inm_link_address_destroy return(s) 0
* @failcase				inm_link_foreach_address and inm_link_address_destroy return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_foreach_address_destroy_p(void)
{
	START_TEST;

	g_nCallbackRet = false;
	g_nCallbackFail = false;

	int nRet =  inm_link_foreach_address(g_hLinkHandle, InmLinkAddressCb,NULL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_foreach_address", InmGetError(nRet));
	if (g_nCallbackRet == false)
	{
		FPRINTF("Failed. InmLinkAddressCb Callback not getting hit");
		return 1;
	}
	if (g_nCallbackFail == false)
	{
		return 1;
	}

	nRet = inm_link_address_destroy(g_hAddressHandle);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_address_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_inm_link_address_clone_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Clones a link address handle.
* @scenario				Clones a link address handle.
* @apicovered			inm_link_address_clone
* @passcase				inm_link_address_clone return(s) 0
* @failcase				inm_link_address_clone return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_address_clone_p(void)
{
	START_TEST;

	inm_link_address_h hAddCloned = NULL;
	g_nCallbackRet = false;
	g_nCallbackFail = false;

	int nRet =  inm_link_foreach_address(g_hLinkHandle, InmLinkAddressCb,NULL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_foreach_address", InmGetError(nRet));
	if (g_nCallbackRet == false)
	{
		FPRINTF("Failed. InmLinkAddressCb Callback not getting hit");
		return 1;
	}
	if (g_nCallbackFail == false)
	{
		return 1;
	}

	nRet = inm_link_address_clone(&hAddCloned, g_hAddressHandle);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_link_address_clone", InmGetError(nRet),inm_link_address_destroy(g_hAddressHandle));
	CHECK_HANDLE_CLEANUP(hAddCloned, "inm_link_address_clone",inm_link_address_destroy(g_hAddressHandle));

	nRet = inm_link_address_destroy(hAddCloned);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_link_address_destroy", InmGetError(nRet),inm_link_address_destroy(g_hAddressHandle));

	nRet = inm_link_address_destroy(g_hAddressHandle);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_link_address_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_inm_link_address_get_family_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Gets the address family.
* @scenario				Gets the address family.
* @apicovered			inm_link_address_get_family
* @passcase				inm_link_address_get_family return(s) 0
* @failcase				inm_link_address_get_family return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_address_get_family_p(void)
{
	START_TEST;

	inm_address_family_e eFamily = -1;
	inm_link_address_h hAddCloned = NULL;
	g_nCallbackRet = false;
	g_nCallbackFail = false;

	int nRet =  inm_link_foreach_address(g_hLinkHandle, InmLinkAddressCb,NULL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_foreach_address", InmGetError(nRet));
	if (g_nCallbackRet == false)
	{
		FPRINTF("Failed. InmLinkAddressCb Callback not getting hit");
		return 1;
	}
	if (g_nCallbackFail == false)
	{
		return 1;
	}

	nRet = inm_link_address_clone(&hAddCloned, g_hAddressHandle);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_link_address_clone", InmGetError(nRet),inm_link_address_destroy(g_hAddressHandle));
	CHECK_HANDLE_CLEANUP(hAddCloned, "inm_link_address_clone",inm_link_address_destroy(g_hAddressHandle));

	nRet = inm_link_address_get_family(hAddCloned, &eFamily);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_link_address_get_family", InmGetError(nRet),inm_link_address_destroy(hAddCloned);inm_link_address_destroy(g_hAddressHandle));
	if( eFamily < INM_ADDRESS_FAMILY_IPV4 || eFamily > INM_ADDRESS_FAMILY_IPV6 )
	{
		FPRINTF("[Line : %d][%s] %s failed. eFamily = %d\\n", __LINE__, API_NAMESPACE, "inm_link_address_get_family", eFamily);
		nRet = inm_link_address_destroy(hAddCloned);
		PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_link_address_destroy", InmGetError(nRet),inm_link_address_destroy(g_hAddressHandle));
		nRet = inm_link_address_destroy(g_hAddressHandle);
		PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_address_destroy", InmGetError(nRet));
		return 1;
	}

	nRet = inm_link_address_destroy(hAddCloned);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_link_address_destroy", InmGetError(nRet),inm_link_address_destroy(g_hAddressHandle));

	nRet = inm_link_address_destroy(g_hAddressHandle);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_link_address_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_inm_link_address_get_prefix_length_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Gets the address prefix length.
* @scenario				Gets the address prefix length.
* @apicovered			inm_link_address_get_prefix_length
* @passcase				inm_link_address_get_prefix_length return(s) 0
* @failcase				inm_link_address_get_prefix_length return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_address_get_prefix_length_p(void)
{
	START_TEST;

	int nPrefixLength = -1;
	g_nCallbackRet = false;
	g_nCallbackFail = false;

	int nRet =  inm_link_foreach_address(g_hLinkHandle, InmLinkAddressCb,NULL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_foreach_address", InmGetError(nRet));
	if (g_nCallbackRet == false)
	{
		FPRINTF("Failed. InmLinkAddressCb Callback not getting hit");
		return 1;
	}
	if (g_nCallbackFail == false)
	{
		return 1;
	}

	nRet = inm_link_address_get_prefix_length(g_hAddressHandle, &nPrefixLength);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_link_address_get_prefix_length", InmGetError(nRet),inm_link_address_destroy(g_hAddressHandle));
	if( nPrefixLength < 0 )
	{
		FPRINTF("[Line : %d][%s] %s failed. nPrefixLength = %d\\n", __LINE__, API_NAMESPACE, "inm_link_address_get_prefix_length", nPrefixLength);
		nRet = inm_link_address_destroy(g_hAddressHandle);
		PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_address_destroy", InmGetError(nRet));
		return 1;
	}

	nRet = inm_link_address_destroy(g_hAddressHandle);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_link_address_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_inm_link_address_get_scope_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Gets the address scope.
* @scenario				Gets the address scope.
* @apicovered			inm_link_address_get_scope
* @passcase				inm_link_address_get_scope return(s) 0
* @failcase				inm_link_address_get_scope return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_address_get_scope_p(void)
{
	START_TEST;

	inm_link_scope_e eScope = -1;
	g_nCallbackRet = false;
	g_nCallbackFail = false;

	int nRet =  inm_link_foreach_address(g_hLinkHandle, InmLinkAddressCb,NULL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_foreach_address", InmGetError(nRet));
	if (g_nCallbackRet == false)
	{
		FPRINTF("Failed. InmLinkAddressCb Callback not getting hit");
		return 1;
	}
	if (g_nCallbackFail == false)
	{
		return 1;
	}

	nRet = inm_link_address_get_scope(g_hAddressHandle, &eScope);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_link_address_get_scope", InmGetError(nRet),inm_link_address_destroy(g_hAddressHandle));
	if( eScope < INM_LINK_SCOPE_NOWHERE || eScope > INM_LINK_SCOPE_UNIVERSE )
	{
		FPRINTF("[Line : %d][%s] %s failed. eScope = %d\\n", __LINE__, API_NAMESPACE, "inm_link_address_get_scope", eScope);
		nRet = inm_link_address_destroy(g_hAddressHandle);
		PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_address_destroy", InmGetError(nRet));
		return 1;
	}

	nRet = inm_link_address_destroy(g_hAddressHandle);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_link_address_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_inm_link_address_get_string_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Gets the address string.
* @scenario				Gets the address string.
* @apicovered			inm_link_address_get_string
* @passcase				inm_link_address_get_string return(s) 0
* @failcase				inm_link_address_get_string return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_address_get_string_p(void)
{
	START_TEST;

	char *pszAddressString = NULL;
	g_nCallbackRet = false;
	g_nCallbackFail = false;

	int nRet =  inm_link_foreach_address(g_hLinkHandle, InmLinkAddressCb,NULL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_foreach_address", InmGetError(nRet));
	if (g_nCallbackRet == false)
	{
		FPRINTF("Failed. InmLinkAddressCb Callback not getting hit");
		return 1;
	}
	if (g_nCallbackFail == false)
	{
		return 1;
	}

	nRet = inm_link_address_get_string(g_hAddressHandle, &pszAddressString);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_link_address_get_string", InmGetError(nRet),inm_link_address_destroy(g_hAddressHandle));
	CHECK_HANDLE_CLEANUP(pszAddressString, "inm_link_address_get_string",inm_link_address_destroy(g_hAddressHandle));
	FREE_MEMORY(pszAddressString);

	nRet = inm_link_address_destroy(g_hAddressHandle);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_link_address_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_inm_link_foreach_route_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Gets all route tables of the link.
* @scenario				Gets all route tables of the link.
* @apicovered			inm_link_foreach_route
* @passcase				inm_link_foreach_route return(s) 0
* @failcase				inm_link_foreach_route return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_foreach_route_p(void)
{
	START_TEST;

	g_nCallbackRet = false;
	g_nCallbackFail = false;

	int nRet = inm_link_foreach_route(g_hLinkHandle, InmLinkRouteCb,NULL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_foreach_route", InmGetError(nRet));
	if (g_nCallbackRet == false)
	{
		FPRINTF("Failed. InmLinkRouteCb Callback not getting hit");
		return 1;
	}
	if (g_nCallbackFail == false)
	{
		return 1;
	}

	nRet = inm_link_route_destroy(g_hRouteHandle);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_link_route_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_inm_link_route_destroy_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Destroys a link route handle.
* @scenario				Destroys a link route handle.
* @apicovered			inm_link_route_destroy
* @passcase				inm_link_route_destroy return(s) 0
* @failcase				inm_link_route_destroy return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_route_destroy_p(void)
{
	START_TEST;

	g_nCallbackRet = false;
	g_nCallbackFail = false;

	int nRet = inm_link_foreach_route(g_hLinkHandle, InmLinkRouteCb,NULL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_foreach_route", InmGetError(nRet));
	if (g_nCallbackRet == false)
	{
		FPRINTF("Failed. InmLinkRouteCb Callback not getting hit");
		return 1;
	}
	if (g_nCallbackFail == false)
	{
		return 1;
	}

	nRet = inm_link_route_destroy(g_hRouteHandle);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_route_destroy", InmGetError(nRet));


	return 0;
}

/**
* @testcase				ITc_inm_link_route_clone_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Clones a link route handle.
* @scenario				Clones a link route handle.
* @apicovered			inm_link_route_clone
* @passcase				inm_link_route_clone return(s) 0
* @failcase				inm_link_route_clone return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_route_clone_p(void)
{
	START_TEST;

	inm_link_route_h hCloned = NULL;
	g_nCallbackRet = false;
	g_nCallbackFail = false;

	int nRet = inm_link_foreach_route(g_hLinkHandle, InmLinkRouteCb,NULL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_foreach_route", InmGetError(nRet));
	if (g_nCallbackRet == false)
	{
		FPRINTF("Failed. InmLinkRouteCb Callback not getting hit");
		return 1;
	}
	if (g_nCallbackFail == false)
	{
		return 1;
	}

	nRet = inm_link_route_clone(&hCloned, g_hRouteHandle);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_link_route_clone", InmGetError(nRet),inm_link_route_destroy(g_hRouteHandle));
	CHECK_HANDLE_CLEANUP(hCloned, "inm_link_route_clone",inm_link_route_destroy(g_hRouteHandle));

	nRet = inm_link_route_destroy(hCloned);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_link_route_destroy", InmGetError(nRet),inm_link_route_destroy(g_hRouteHandle));

	nRet = inm_link_route_destroy(g_hRouteHandle);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_link_route_destroy", InmGetError(nRet));
	return 0;
}

/**
* @testcase				ITc_inm_link_route_get_destination_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Gets the route destination.
* @scenario				Gets the route destination.
* @apicovered			inm_link_route_get_destination
* @passcase				inm_link_route_get_destination return(s) 0
* @failcase				inm_link_route_get_destination return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_route_get_destination_p(void)
{
	START_TEST;

	char *pszDestination = NULL;
	g_nCallbackRet = false;
	g_nCallbackFail = false;

	int nRet = inm_link_foreach_route(g_hLinkHandle, InmLinkRouteCb,NULL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_foreach_route", InmGetError(nRet));
	if (g_nCallbackRet == false)
	{
		FPRINTF("Failed. InmLinkRouteCb Callback not getting hit");
		return 1;
	}
	if (g_nCallbackFail == false)
	{
		return 1;
	}

	nRet = inm_link_route_get_destination(g_hRouteHandle, &pszDestination);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_link_route_get_destination", InmGetError(nRet),inm_link_route_destroy(g_hRouteHandle));
	CHECK_HANDLE_CLEANUP(pszDestination, "inm_link_route_get_destination",inm_link_route_destroy(g_hRouteHandle));
	FREE_MEMORY(pszDestination);

	nRet = inm_link_route_destroy(g_hRouteHandle);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_link_route_destroy", InmGetError(nRet));


	return 0;
}

/**
* @testcase				ITc_inm_link_route_get_gateway_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Gets the route gateway.
* @scenario				Gets the route gateway.
* @apicovered			inm_link_route_get_gateway
* @passcase				inm_link_route_get_gateway return(s) 0
* @failcase				inm_link_route_get_gateway return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_route_get_gateway_p(void)
{
	START_TEST;

	char *pszGateway = NULL;
	g_nCallbackRet = false;
	g_nCallbackFail = false;

	int nRet = inm_link_foreach_route(g_hLinkHandle, InmLinkRouteCb,NULL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_foreach_route", InmGetError(nRet));
	if (g_nCallbackRet == false)
	{
		FPRINTF("Failed. InmLinkRouteCb Callback not getting hit");
		return 1;
	}
	if (g_nCallbackFail == false)
	{
		return 1;
	}

	nRet = inm_link_route_get_gateway(g_hRouteHandle, &pszGateway);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_link_route_get_gateway", InmGetError(nRet),inm_link_route_destroy(g_hRouteHandle));
	CHECK_HANDLE_CLEANUP(pszGateway, "inm_link_route_get_gateway",inm_link_route_destroy(g_hRouteHandle));
	FREE_MEMORY(pszGateway);

	nRet = inm_link_route_destroy(g_hRouteHandle);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_link_route_destroy", InmGetError(nRet));


	return 0;
}

/**
* @testcase				ITc_inm_link_route_get_interface_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Gets the route interface.
* @scenario				Gets the route interface.
* @apicovered			inm_link_route_get_interface
* @passcase				inm_link_route_get_interface return(s) 0
* @failcase				inm_link_route_get_interface return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_route_get_interface_p(void)
{
	START_TEST;

	char *pszInterface = NULL;
	g_nCallbackRet = false;
	g_nCallbackFail = false;

	int nRet = inm_link_foreach_route(g_hLinkHandle, InmLinkRouteCb,NULL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_foreach_route", InmGetError(nRet));
	if (g_nCallbackRet == false)
	{
		FPRINTF("Failed. InmLinkRouteCb Callback not getting hit");
		return 1;
	}
	if (g_nCallbackFail == false)
	{
		return 1;
	}

	nRet = inm_link_route_get_interface(g_hRouteHandle, &pszInterface);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_link_route_get_interface", InmGetError(nRet),inm_link_route_destroy(g_hRouteHandle));
	CHECK_HANDLE_CLEANUP(pszInterface, "inm_link_route_get_interface",inm_link_route_destroy(g_hRouteHandle));
	FREE_MEMORY(pszInterface);

	nRet = inm_link_route_destroy(g_hRouteHandle);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_link_route_destroy", InmGetError(nRet));


	return 0;
}

/**
* @testcase				ITc_inm_link_route_is_default_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manog.g2)
* @type					auto
* @description			Checks whether the route is default or not.
* @scenario				Checks whether the route is default or not.
* @apicovered			inm_link_route_is_default
* @passcase				inm_link_route_is_default return(s) 0
* @failcase				inm_link_route_is_default return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_route_is_default_p(void)
{
	START_TEST;

	bool bIsDefault = false;
	g_nCallbackRet = false;
	g_nCallbackFail = false;

	int nRet = inm_link_foreach_route(g_hLinkHandle, InmLinkRouteCb,NULL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_foreach_route", InmGetError(nRet));
	if (g_nCallbackRet == false)
	{
		FPRINTF("Failed. InmLinkRouteCb Callback not getting hit");
		return 1;
	}
	if (g_nCallbackFail == false)
	{
		return 1;
	}

	nRet = inm_link_route_is_default(g_hRouteHandle, &bIsDefault);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_link_route_is_default", InmGetError(nRet),inm_link_route_destroy(g_hRouteHandle));

	nRet = inm_link_route_destroy(g_hRouteHandle);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_link_route_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_inm_link_route_get_type_p
* @since_tizen			5.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description			Gets the route type.
* @scenario				Gets the route type.
* @apicovered			inm_link_route_get_type
* @passcase				inm_link_route_get_type return(s) 0
* @failcase				inm_link_route_get_type return(s) 1
* @precondition			N/A
* @postcondition		N/A
* */
int ITc_inm_link_route_get_type_p(void)
{
	START_TEST;

	inm_link_route_type_e eType = -1;
	g_nCallbackRet = false;
	g_nCallbackFail = false;

	int nRet = inm_link_foreach_route(g_hLinkHandle, InmLinkRouteCb,NULL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_foreach_route", InmGetError(nRet));
	if (g_nCallbackRet == false)
	{
		FPRINTF("Failed. InmLinkRouteCb Callback not getting hit");
		return 1;
	}
	if (g_nCallbackFail == false)
	{
		return 1;
	}

	nRet = inm_link_route_get_type(g_hRouteHandle, &eType);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_link_route_get_type", InmGetError(nRet),inm_link_route_destroy(g_hRouteHandle));
	if( eType < INM_LINK_ROUTE_TYPE_UNSPEC || eType > INM_LINK_ROUTE_TYPE_XRESOLVE )
	{
		FPRINTF("[Line : %d][%s] %s failed. eType = %d\\n", __LINE__, API_NAMESPACE, "inm_link_route_get_type", eType);
		nRet = inm_link_route_destroy(g_hRouteHandle);
		PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_link_route_destroy", InmGetError(nRet));
		return 1;
	}

	nRet = inm_link_route_destroy(g_hRouteHandle);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_link_route_destroy", InmGetError(nRet));

	return 0;
}

/** @} */
/** @} */
