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
#include "ITs-nsd-common.h"

//& set: Nsd

/** @addtogroup itc-nsd
*  @ingroup itc
*  @{
*/
bool g_bIPVal;
/****************************************************Callback Start****************************************************/

/**
 * @function 		Dnssd_found_cb_p
 * @description	 	Called when the registration of DNSSD service is finished
 * @parameter		dnssd_service_state_e service_state,dnssd_service_h remote_service, void *user_data
 * @return 			NA
 */
static void Dnssd_found_cb_p(dnssd_service_state_e service_state,dnssd_service_h remote_service, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked: Dnssd_found_cb_p\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;
	char * pszIPV4Address = NULL;
	char * pszIPV6Address = NULL;
	
	//Target API
	int nRet = dnssd_service_get_ip(remote_service, &pszIPV4Address,&pszIPV6Address);
	if(nRet != DNSSD_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] dnssd_service_get_ip fails\n", __LINE__, API_NAMESPACE);
		g_bIPVal = false;
		if ( g_pMainLoop )
		{
			g_main_loop_quit(g_pMainLoop);
			g_main_loop_unref(g_pMainLoop);
			g_pMainLoop = NULL;
		}
	}
		
	//Check Get Value
	if((pszIPV4Address == NULL)||(pszIPV6Address == NULL))
	{
		FPRINTF("[Line : %d][%s] ip address is null\\n", __LINE__, API_NAMESPACE);
		g_bIPVal = false;
		if ( g_pMainLoop )
		{
			g_main_loop_quit(g_pMainLoop);
			g_main_loop_unref(g_pMainLoop);
			g_pMainLoop = NULL;
		}
	}
	
	FREE_MEMORY(pszIPV4Address);
	FREE_MEMORY(pszIPV6Address);
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
 * @function 		Dnssd_registered_reply_cb_p
 * @description	 	Called when a DNSSD service is found
 * @parameter		dnssd_error_e result,dnssd_service_h local_service, void *user_data
 * @return 			NA
 */
static void Dnssd_registered_reply_cb_p(dnssd_error_e result,dnssd_service_h local_service, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked: Dnssd_registered_reply_cb_p\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/*****************************************************Callback End*****************************************************/

/**
 * @function 		ITs_nsd_dnssd_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_nsd_dnssd_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_NSD_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bFeatureNotSupported = false;
	g_bFeatureMismatched = false;
	g_bNsdInitialize = false;
	g_bFeatureSupported = false;

	//Feature check for feature network.service_discovery.dnssd
	IS_FEATURE_SUPPORTED(FEATURE_DNSSD, g_bFeatureSupported, API_NAMESPACE);

	//Initialize the DNSSD
	int nRet = dnssd_initialize();
	if ( !g_bFeatureSupported )
	{
		if ( nRet == TIZEN_ERROR_NOT_SUPPORTED )
		{
			g_bFeatureNotSupported = true;
			return;
		}
		FPRINTF("[Line : %d][%s] dnssd_initialize failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s\\n", __LINE__, API_NAMESPACE, NsdDnsSdGetError(nRet));
		g_bFeatureMismatched = true;
		return;
	}
	if ( nRet == DNSSD_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] dnssd_initialize successfully\\n", __LINE__, API_NAMESPACE);;
		g_bNsdInitialize = true;
	}
	else
	{
		FPRINTF("[Line : %d][%s] dnssd_initialize failed\\n", __LINE__, API_NAMESPACE);
		g_bNsdInitialize = false;
	}
	return;
}


/**
 * @function 		ITs_nsd_dnssd_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_nsd_dnssd_cleanup(void)
{
	#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_NSD_p\\n", __LINE__, API_NAMESPACE);
#endif
	if ( g_bNsdInitialize )
	{
		//De-Initialize the DNSSD
		int nRet = dnssd_deinitialize();
		if ( nRet != DNSSD_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] dnssd_deinitialize failed on cleanup, error returned = %s\\n", __LINE__, API_NAMESPACE, NsdDnsSdGetError(nRet));
		}
	}
	return;
}

//& purpose: To Initialize and Deinitialize DNSSD
//& type : auto
/**
* @testcase 			ITc_dnssd_initialize_deinitialize_p
* @type 				auto
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @since_tizen			3.0
* @description			Initializes and Deinitializes DNSSD
* @scenario				De-Initialize the DNSSD initialized in startup\n
* 						Initialize the DNSSD\n
* 						De-Initialize the DNSSD\n
* 						Initialize the DNSSD to be de-initialize in cleanup
* @apicovered			dnssd_initialize, dnssd_deinitialize
* @passcase				When dnssd_initialize and dnssd_deinitialize return success
* @failcase				When dnssd_initialize or dnssd_deinitialize return failure
* @precondition			none
* @postcondition		none
*/
int ITc_dnssd_initialize_deinitialize_p(void)
{
	START_TEST;
	
	//De-Initialize the DNSSD initialized in startup
	int nRet = dnssd_deinitialize();
	PRINT_RESULT(DNSSD_ERROR_NONE, nRet, "dnssd_deinitialize", NsdDnsSdGetError(nRet));
	
	//Target API
	nRet = dnssd_initialize();
	PRINT_RESULT(DNSSD_ERROR_NONE, nRet, "dnssd_initialize", NsdDnsSdGetError(nRet));
	
	//Target API
	nRet = dnssd_deinitialize();
	PRINT_RESULT(DNSSD_ERROR_NONE, nRet, "dnssd_deinitialize", NsdDnsSdGetError(nRet));
	
	//Initialize the DNSSD to be de-initialize in cleanup
	nRet = dnssd_initialize();
	PRINT_RESULT_NORETURN(DNSSD_ERROR_NONE, nRet, "dnssd_initialize", NsdDnsSdGetError(nRet));
		
    return 0;
}

//& purpose: To Create and Destroy a DNSSD local service handle
//& type : auto
/**
* @testcase 			ITc_dnssd_create_destroy_local_service_p
* @type 				auto
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @since_tizen			3.0
* @description			Creates and Destroys a DNSSD local service handle
* @scenario				initialize dnssd\n
*						create dnssd local service handle\n
*						destroy dnssd local service handle\n
*						deinitialize dnssd
* @apicovered			dnssd_create_local_service, dnssd_destroy_local_service
* @passcase				When dnssd_create_local_service and dnssd_destroy_local_service return success
* @failcase				When dnssd_create_local_service or dnssd_destroy_local_service return failure
* @precondition			none
* @postcondition		none
*/
int ITc_dnssd_create_destroy_local_service_p(void)
{
	START_TEST;
	
	char *pszServiceType ="_upnp._tcp";
	dnssd_service_h hLocalService = 0;
	
	//Target API
	int nRet = dnssd_create_local_service(pszServiceType,&hLocalService);
	PRINT_RESULT(DNSSD_ERROR_NONE, nRet, "dnssd_create_local_service", NsdDnsSdGetError(nRet));
	CHECK_HANDLE_INT(hLocalService, "dnssd_create_local_service");
	
	//Target API
	nRet = dnssd_destroy_local_service(hLocalService);
	PRINT_RESULT(DNSSD_ERROR_NONE, nRet, "dnssd_destroy_local_service", NsdDnsSdGetError(nRet));
			
    return 0;
}

//& purpose: To Set and Get the name of DNSSD local/remote service.
//& type : auto
/**
* @testcase 			ITc_dnssd_service_set_get_name_p
* @type 				auto
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @since_tizen			3.0
* @description			Sets and Gets the name of DNSSD local/remote service.
* @scenario				initialize dnssd\n
*						create dnssd local service handle\n
*						dnssd_service_set_name and dnssd_service_get_name\n
*						compare set and get values\n
*						destroy dnssd local service handle\n
*						deinitialize dnssd
* @apicovered			dnssd_service_set_name, dnssd_service_get_name
* @passcase				When dnssd_service_set_name and dnssd_service_get_name return success
* @failcase				When dnssd_service_set_name or dnssd_service_get_name return failure
* @precondition			none
* @postcondition		none
*/
int ITc_dnssd_service_set_get_name_p(void)
{
	START_TEST;
	
	char *pszServiceType = "_upnp._tcp";
	char pszSetServiceName[] = "ssh";
	char *pszGetServiceName = NULL;
	dnssd_service_h hLocalService = 0;
	
	//Create DNSSD local service handle
	int nRet = dnssd_create_local_service(pszServiceType,&hLocalService);
	PRINT_RESULT(DNSSD_ERROR_NONE, nRet, "dnssd_create_local_service", NsdDnsSdGetError(nRet));
	CHECK_HANDLE_INT(hLocalService, "dnssd_create_local_service");
	
	//Target API
	nRet = dnssd_service_set_name(hLocalService,pszSetServiceName);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_service_set_name", NsdDnsSdGetError(nRet),dnssd_destroy_local_service(hLocalService));
	
	//Target API
	nRet = dnssd_service_get_name(hLocalService,&pszGetServiceName);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_service_get_name", NsdDnsSdGetError(nRet),dnssd_destroy_local_service(hLocalService));
	
	//Compare Set and Get Value
	if (strcmp(pszSetServiceName, pszGetServiceName) != 0 )
	{
		FPRINTF("[Line : %d][%s] dnssd_service_get_name return value %s mismatched with set value %s\\n", __LINE__, API_NAMESPACE, pszSetServiceName, pszGetServiceName);
		dnssd_destroy_local_service(hLocalService);
		return 1;
	}
	
	FREE_MEMORY(pszGetServiceName);
	
	//Destroy DNSSD local service handle
	nRet = dnssd_destroy_local_service(hLocalService);
	PRINT_RESULT_NORETURN(DNSSD_ERROR_NONE, nRet, "dnssd_destroy_local_service", NsdDnsSdGetError(nRet));
			
    return 0;
}

//& purpose: To Set and Get the port of DNSSD local/remote service.
//& type : auto
/**
* @testcase 			ITc_dnssd_service_set_get_port_p
* @type 				auto
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @since_tizen			3.0
* @description			Sets and Gets the port of DNSSD local/remote service.
* @scenario				initialize dnssd\n
*						create dnssd local service handle\n
*						dnssd_service_set_port and dnssd_service_get_port\n
*						compare set and get values\n
*						destroy dnssd local service handle\n
*						deinitialize dnssd
* @apicovered			dnssd_service_set_port, dnssd_service_get_port
* @passcase				When dnssd_service_set_port and dnssd_service_get_port return success
* @failcase				When dnssd_service_set_port or dnssd_service_get_port return failure
* @precondition			none
* @postcondition		none
*/
int ITc_dnssd_service_set_get_port_p(void)
{
	START_TEST;
	
	char *pszServiceType = "_upnp._tcp";
	int nSetPort = 0;
	int nGetPort = -1;
	dnssd_service_h hLocalService = 0;
	
	//Create DNSSD local service handle
	int nRet = dnssd_create_local_service(pszServiceType,&hLocalService);
	PRINT_RESULT(DNSSD_ERROR_NONE, nRet, "dnssd_create_local_service", NsdDnsSdGetError(nRet));
	CHECK_HANDLE_INT(hLocalService, "dnssd_create_local_service");
	
	//Target API
	nRet = dnssd_service_set_port(hLocalService,nSetPort);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_service_set_port", NsdDnsSdGetError(nRet),dnssd_destroy_local_service(hLocalService));
	
	//Target API
	nRet = dnssd_service_get_port(hLocalService,&nGetPort);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_service_get_port", NsdDnsSdGetError(nRet),dnssd_destroy_local_service(hLocalService));
	
	//Compare Set and Get Value
	if(nSetPort!=nGetPort)
	{
		FPRINTF("[Line : %d][%s] dnssd_service_get_port return value %d mismatched with set value %d\\n", __LINE__, API_NAMESPACE, nSetPort, nGetPort);
		dnssd_destroy_local_service(hLocalService);
		return 1;
	}
	
	//Destroy DNSSD local service handle
	nRet = dnssd_destroy_local_service(hLocalService);
	PRINT_RESULT_NORETURN(DNSSD_ERROR_NONE, nRet, "dnssd_destroy_local_service", NsdDnsSdGetError(nRet));
			
    return 0;
}

//& purpose: To Get the type of DNSSD local/remote service.
//& type : auto
/**
* @testcase 			ITc_dnssd_service_get_type_p
* @type 				auto
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @since_tizen			3.0
* @description			Gets the type of DNSSD local/remote service.
* @scenario				initialize dnssd\n
*						create dnssd local service handle\n
*						dnssd_service_get_type\n
*						check get value\n
*						destroy dnssd local service handle\n
*						deinitialize dnssd
* @apicovered			dnssd_service_get_type
* @passcase				When dnssd_service_get_type return success
* @failcase				When dnssd_service_get_type return failure
* @precondition			none
* @postcondition		none
*/
int ITc_dnssd_service_get_type_p(void)
{
	START_TEST;
	
	char *pszServiceType = "_upnp._tcp";
	char *pszGetServiceType = NULL;
	dnssd_service_h hLocalService = 0;
	
	//Create DNSSD local service handle
	int nRet = dnssd_create_local_service(pszServiceType,&hLocalService);
	PRINT_RESULT(DNSSD_ERROR_NONE, nRet, "dnssd_create_local_service", NsdDnsSdGetError(nRet));
	CHECK_HANDLE_INT(hLocalService, "dnssd_create_local_service");
	
	//Target API
	nRet = dnssd_service_get_type(hLocalService, &pszGetServiceType);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_service_get_type", NsdDnsSdGetError(nRet),dnssd_destroy_local_service(hLocalService));
	
	//Check Get Value
	if(pszGetServiceType == NULL)
	{
		FPRINTF("[Line : %d][%s] pszGetServiceType is null\\n", __LINE__, API_NAMESPACE);
		dnssd_destroy_local_service(hLocalService);
		return 1;
	}
	
	FREE_MEMORY(pszGetServiceType);

	//Destroy DNSSD local service handle
	nRet = dnssd_destroy_local_service(hLocalService);
	PRINT_RESULT_NORETURN(DNSSD_ERROR_NONE, nRet, "dnssd_destroy_local_service", NsdDnsSdGetError(nRet));
			
    return 0;
}

//& purpose: Registers and Deregisters the DNSSD local service for publishing.
//& type : auto
/**
* @testcase 			ITc_dnssd_register_deregister_local_service_p
* @type 				auto
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @since_tizen			3.0
* @description			Registers and Deregisters the DNSSD local service for publishing.
* @scenario				initialize dnssd\n
*						create dnssd local service handle\n
*						dnssd_register_local_service and dnssd_deregister_local_service\n
*						destroy dnssd local service handle\n
*						deinitialize dnssd
* @apicovered			dnssd_register_local_service, dnssd_deregister_local_service
* @passcase				When dnssd_register_local_service and dnssd_deregister_local_service return success
* @failcase				When dnssd_register_local_service or dnssd_deregister_local_service return failure
* @precondition			none
* @postcondition		none
*/
int ITc_dnssd_register_deregister_local_service_p(void)
{
	START_TEST;
	
	char *pszServiceType = "_upnp._tcp";
	int nSetPort = 0;
	dnssd_service_h hLocalService = 0;
	char *pszSetServiceName = "ssh";
	int nTimeoutId = 0;
	g_bCallbackResult = false;
	
	//Create DNSSD local service handle
	int nRet = dnssd_create_local_service(pszServiceType,&hLocalService);
	PRINT_RESULT(DNSSD_ERROR_NONE, nRet, "dnssd_create_local_service", NsdDnsSdGetError(nRet));
	CHECK_HANDLE_INT(hLocalService, "dnssd_create_local_service");
	
	//Set the name of DNSSD local/remote service.
	nRet = dnssd_service_set_name(hLocalService,pszSetServiceName);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_service_set_name", NsdDnsSdGetError(nRet), dnssd_destroy_local_service(hLocalService));
	
	//Set the port of DNSSD local/remote service.
	nRet = dnssd_service_set_port(hLocalService,nSetPort);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_service_set_port", NsdDnsSdGetError(nRet), dnssd_destroy_local_service(hLocalService));
	
	//Target API
	nRet = dnssd_register_local_service(hLocalService, Dnssd_registered_reply_cb_p, NULL);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_register_local_service", NsdDnsSdGetError(nRet), dnssd_destroy_local_service(hLocalService));
	
	//Waiting for callback hit
	RUN_POLLING_LOOP;
	
	if(!g_bCallbackResult)
	{
		FPRINTF("[Line : %d][%s] Callback not hit\\n", __LINE__, API_NAMESPACE);
		dnssd_deregister_local_service(hLocalService);
		dnssd_destroy_local_service(hLocalService);
		return 1;
	}

	//Target API
	nRet = dnssd_deregister_local_service(hLocalService);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_deregister_local_service", NsdDnsSdGetError(nRet), dnssd_destroy_local_service(hLocalService));
	
	//Destroy DNSSD local service handle
	nRet = dnssd_destroy_local_service(hLocalService);
	PRINT_RESULT_NORETURN(DNSSD_ERROR_NONE, nRet, "dnssd_destroy_local_service", NsdDnsSdGetError(nRet));
			
    return 0;
}

//& purpose: Adds and Removes the TXT record.
//& type : auto
/**
* @testcase 			ITc_dnssd_service_add_remove_txt_record_p
* @type 				auto
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @since_tizen			3.0
* @description			Adds and Removes the TXT record.
* @scenario				initialize dnssd\n
*						create dnssd local service handle\n
*						dnssd_service_add_txt_record and dnssd_service_remove_txt_record\n
*						destroy dnssd local service handle\n
*						deinitialize dnssd
* @apicovered			dnssd_service_add_txt_record, dnssd_service_remove_txt_record
* @passcase				When dnssd_service_add_txt_record and dnssd_service_remove_txt_record return success
* @failcase				When dnssd_service_add_txt_record or dnssd_service_remove_txt_record return failure
* @precondition			none
* @postcondition		none
*/
int ITc_dnssd_service_add_remove_txt_record_p(void)
{
	START_TEST;
	
	char *pszServiceType = "_upnp._tcp";
	int nSetPort = 0;
	unsigned short nLength = 0;
	dnssd_service_h hLocalService = 0;
	char *pszSetServiceName = "ssh";
	char *pszKey = "papersizeA4";
	int nTimeoutId = 0;
	g_bCallbackResult = false;
	
	//Create DNSSD local service handle
	int nRet = dnssd_create_local_service(pszServiceType,&hLocalService);
	PRINT_RESULT(DNSSD_ERROR_NONE, nRet, "dnssd_create_local_service", NsdDnsSdGetError(nRet));
	CHECK_HANDLE_INT(hLocalService, "dnssd_create_local_service");
	
	//Set the name of DNSSD local/remote service.
	nRet = dnssd_service_set_name(hLocalService,pszSetServiceName);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_service_set_name", NsdDnsSdGetError(nRet),dnssd_destroy_local_service(hLocalService));
	
	//Set the port of DNSSD local/remote service.
	nRet = dnssd_service_set_port(hLocalService,nSetPort);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_service_set_port", NsdDnsSdGetError(nRet),dnssd_destroy_local_service(hLocalService));
	
	//Registers the DNSSD local service for publishing.
	nRet = dnssd_register_local_service(hLocalService, Dnssd_registered_reply_cb_p, NULL);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_register_local_service", NsdDnsSdGetError(nRet),dnssd_destroy_local_service(hLocalService));
	
	//Waiting for callback hit
	RUN_POLLING_LOOP;
	
	if(!g_bCallbackResult)
	{
		FPRINTF("[Line : %d][%s] Callback not hit\\n", __LINE__, API_NAMESPACE);
		dnssd_deregister_local_service(hLocalService);
		dnssd_destroy_local_service(hLocalService);
		return 1;
	}
		
	//Target API
	nRet = dnssd_service_add_txt_record(hLocalService,pszKey, nLength, NULL);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_service_add_txt_record", NsdDnsSdGetError(nRet),dnssd_deregister_local_service(hLocalService);dnssd_destroy_local_service(hLocalService));
		
	//Target API
	nRet = dnssd_service_remove_txt_record(hLocalService,pszKey);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_service_remove_txt_record", NsdDnsSdGetError(nRet),dnssd_deregister_local_service(hLocalService);dnssd_destroy_local_service(hLocalService));
	
	//Deregisters the DNSSD local service for publishing
	nRet = dnssd_deregister_local_service(hLocalService);
	PRINT_RESULT_NORETURN(DNSSD_ERROR_NONE, nRet, "dnssd_deregister_local_service", NsdDnsSdGetError(nRet));

	//Destroy DNSSD local service handle
	nRet = dnssd_destroy_local_service(hLocalService);
	PRINT_RESULT_NORETURN(DNSSD_ERROR_NONE, nRet, "dnssd_destroy_local_service", NsdDnsSdGetError(nRet));
			
    return 0;
}

//& purpose: Sets/updates and Unsets the DNS resource record.
//& type : auto
/**
* @testcase 			ITc_dnssd_service_set_unset_record_p
* @type 				auto
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @since_tizen			3.0
* @description			Sets/updates and Unsets the DNS resource record
* @scenario				initialize dnssd\n
*						create dnssd local service handle\n
*						dnssd_service_set_record and dnssd_service_unset_record\n
*						destroy dnssd local service handle\n
*						deinitialize dnssd
* @apicovered			dnssd_service_set_record, dnssd_service_unset_record
* @passcase				When dnssd_service_set_record and dnssd_service_unset_record return success
* @failcase				When dnssd_service_set_record or dnssd_service_unset_record return failure
* @precondition			none
* @postcondition		none
*/
int ITc_dnssd_service_set_unset_record_p(void)
{
	START_TEST;
	
	char *pszServiceType = "_upnp._tcp";
	int nSetPort = 12345;
	dnssd_service_h hLocalService = 0;
	char *pszSetServiceName = "ssh";
	int nTimeoutId = 0;
	g_bCallbackResult = false;
	unsigned short unGetServiceType = 16;
	char szBuff[32] = {0,};
	char *pszValue = "http://www.tizen.org";
	
	g_strlcpy(szBuff + 1, pszValue, sizeof(szBuff));
	szBuff[0] = strlen(pszValue);
	
	//Create DNSSD local service handle
	int nRet = dnssd_create_local_service(pszServiceType,&hLocalService);
	PRINT_RESULT(DNSSD_ERROR_NONE, nRet, "dnssd_create_local_service", NsdDnsSdGetError(nRet));
	CHECK_HANDLE_INT(hLocalService, "dnssd_create_local_service");
	
	//Set the name of DNSSD local/remote service.
	nRet = dnssd_service_set_name(hLocalService,pszSetServiceName);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_service_set_name", NsdDnsSdGetError(nRet),dnssd_destroy_local_service(hLocalService));
	
	//Set the port of DNSSD local/remote service.
	nRet = dnssd_service_set_port(hLocalService,nSetPort);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_service_set_port", NsdDnsSdGetError(nRet),dnssd_destroy_local_service(hLocalService));
	
	//Registers the DNSSD local service for publishing.
	nRet = dnssd_register_local_service(hLocalService, Dnssd_registered_reply_cb_p, NULL);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_register_local_service", NsdDnsSdGetError(nRet),dnssd_destroy_local_service(hLocalService));
	
	//Waiting for callback hit
	RUN_POLLING_LOOP;
	
	if(!g_bCallbackResult)
	{
		FPRINTF("[Line : %d][%s] Callback not hit\\n", __LINE__, API_NAMESPACE);
		dnssd_deregister_local_service(hLocalService);
		dnssd_destroy_local_service(hLocalService);
		return 1;
	}
	
	//Target API
	nRet = dnssd_service_set_record(hLocalService,unGetServiceType, szBuff[0] + 1, (void *)szBuff);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_service_set_record", NsdDnsSdGetError(nRet),dnssd_deregister_local_service(hLocalService);dnssd_destroy_local_service(hLocalService));
	
	//Target API
	nRet = dnssd_service_unset_record(hLocalService,unGetServiceType);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_service_unset_record", NsdDnsSdGetError(nRet),dnssd_deregister_local_service(hLocalService);dnssd_destroy_local_service(hLocalService));
	
	//Deregisters the DNSSD local service for publishing.
	nRet = dnssd_deregister_local_service(hLocalService);
	PRINT_RESULT_NORETURN(DNSSD_ERROR_NONE, nRet, "dnssd_deregister_local_service", NsdDnsSdGetError(nRet));
	
	//Destroy DNSSD local service handle
	nRet = dnssd_destroy_local_service(hLocalService);
	PRINT_RESULT_NORETURN(DNSSD_ERROR_NONE, nRet, "dnssd_destroy_local_service", NsdDnsSdGetError(nRet));
			
    return 0;
}

//& purpose:Gets the TXT record.
//& type : auto
/**
* @testcase 			ITc_dnssd_service_get_all_txt_record_p
* @type 				auto
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @since_tizen			3.0
* @description			Gets the TXT record.
* @scenario				initialize dnssd\n
*						create dnssd local service handle\n
*						dnssd_service_get_all_txt_record\n
*						destroy dnssd local service handle\n
*						deinitialize dnssd
* @apicovered			dnssd_service_get_all_txt_record
* @passcase				When dnssd_service_get_all_txt_record return success
* @failcase				When dnssd_service_get_all_txt_record return failure
* @precondition			none
* @postcondition		none
*/
int ITc_dnssd_service_get_all_txt_record_p(void)
{
	START_TEST;
	
	char *pszServiceType = "_upnp._tcp";
	int nSetPort = 0;
	dnssd_service_h hLocalService = 0;
	char *pszSetServiceName = "ssh";
	int nTimeoutId = 0;
	g_bCallbackResult = false;
	char *pszKey = "papersizeA4";
	unsigned short length = 0;
	void *pszData = NULL;
	
	//Create DNSSD local service handle
	int nRet = dnssd_create_local_service(pszServiceType,&hLocalService);
	PRINT_RESULT(DNSSD_ERROR_NONE, nRet, "dnssd_create_local_service", NsdDnsSdGetError(nRet));
	CHECK_HANDLE_INT(hLocalService, "dnssd_create_local_service");
	
	//Set the name of DNSSD local/remote service.
	nRet = dnssd_service_set_name(hLocalService,pszSetServiceName);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_service_set_name", NsdDnsSdGetError(nRet), dnssd_deregister_local_service(hLocalService);dnssd_destroy_local_service(hLocalService));
	
	//Set the port of DNSSD local/remote service.
	nRet = dnssd_service_set_port(hLocalService,nSetPort);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_service_set_port", NsdDnsSdGetError(nRet), dnssd_deregister_local_service(hLocalService);dnssd_destroy_local_service(hLocalService));
	
	//Deregisters the DNSSD local service for publishing.
	nRet = dnssd_register_local_service(hLocalService, Dnssd_registered_reply_cb_p, NULL);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_register_local_service", NsdDnsSdGetError(nRet),dnssd_deregister_local_service(hLocalService); dnssd_destroy_local_service(hLocalService));
	
	//Waiting for callback hit
	RUN_POLLING_LOOP;
	
	if(!g_bCallbackResult)
	{
		FPRINTF("[Line : %d][%s] Callback not hit\\n", __LINE__, API_NAMESPACE);
		dnssd_deregister_local_service(hLocalService);
		dnssd_destroy_local_service(hLocalService);
		return 1;
	}
	
	//Adds the TXT record.
	nRet = dnssd_service_add_txt_record(hLocalService,pszKey, length, NULL);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_service_add_txt_record", NsdDnsSdGetError(nRet), dnssd_deregister_local_service(hLocalService);dnssd_destroy_local_service(hLocalService));
	
	//Target API
	nRet = dnssd_service_get_all_txt_record(hLocalService, &length, &pszData);
	PRINT_RESULT_CLEANUP(DNSSD_ERROR_NONE, nRet, "dnssd_service_get_all_txt_record", NsdDnsSdGetError(nRet),dnssd_deregister_local_service(hLocalService); dnssd_destroy_local_service(hLocalService));
	
	FREE_MEMORY(pszData);
	
	//Deregisters the DNSSD local service for publishing.
	nRet = dnssd_deregister_local_service(hLocalService);
	PRINT_RESULT_NORETURN(DNSSD_ERROR_NONE, nRet, "dnssd_deregister_local_service", NsdDnsSdGetError(nRet));
	
	//Destroy DNSSD local service handle
	nRet = dnssd_destroy_local_service(hLocalService);
	PRINT_RESULT_NORETURN(DNSSD_ERROR_NONE, nRet, "dnssd_destroy_local_service", NsdDnsSdGetError(nRet));
			
    return 0;
}

/** @} */
/** @} */
