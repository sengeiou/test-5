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

/****************************************************Callback Start****************************************************/

/**
 * @function 		Nsd_Ssdp_Found_cb_p
 * @description	 	Called when a service has become available or unavailable
 * @parameter		ssdp_service_state_e state,ssdp_service_h ssdp_remote_service, void *user_data
 * @return 			NA
 */
void Nsd_Ssdp_Found_cb_p(ssdp_service_state_e state,ssdp_service_h ssdp_remote_service, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked: Nsd_Ssdp_Found_cb_p\\n", __LINE__, API_NAMESPACE);
}

/**
 * @function 		Nsd_registered_cb_p
 * @description	 	Called when the registration of SSDP service is finished
 * @parameter		ssdp_error_e result,ssdp_service_h ssdp_local_service, void *user_data
 * @return 			NA
 */
void Nsd_registered_cb_p(ssdp_error_e result,ssdp_service_h ssdp_local_service, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked: Nsd_registered_cb_p\\n", __LINE__, API_NAMESPACE);
}

/*****************************************************Callback End*****************************************************/

/**
 * @function 		ITs_nsd_ssdp_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_nsd_ssdp_startup(void)
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

	//Feature check for feature network.service_discovery.ssdp
	IS_FEATURE_SUPPORTED(FEATURE_SSDP, g_bFeatureSupported, API_NAMESPACE);

	//Initialize the SSDP
	int nRet = ssdp_initialize();
	if ( !g_bFeatureSupported )
	{
		if ( nRet == TIZEN_ERROR_NOT_SUPPORTED )
		{
			g_bFeatureNotSupported = true;
			return;
		}
		FPRINTF("[Line : %d][%s] ssdp_initialize failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s\\n", __LINE__, API_NAMESPACE, NsdSsdpGetError(nRet));
		g_bFeatureMismatched = true;
		return;
	}
	if ( nRet == SSDP_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] ssdp_initialize successfully in startup\\n", __LINE__, API_NAMESPACE);;
		g_bNsdInitialize = true;
	}
	else
	{
		FPRINTF("[Line : %d][%s] ssdp_initialize failed in startup\\n", __LINE__, API_NAMESPACE);
		g_bNsdInitialize = false;
	}
	return;
}


/**
 * @function 		ITs_nsd_ssdp_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_nsd_ssdp_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_NSD_p\\n", __LINE__, API_NAMESPACE);
#endif
	if ( g_bNsdInitialize )
	{
		//De-Initialize the SSDP
		int nRet = ssdp_deinitialize();
		if ( nRet != SSDP_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] ssdp_deinitialize failed on cleanup, error returned = %s\\n", __LINE__, API_NAMESPACE, NsdSsdpGetError(nRet));
		}
	}
	return;
}

//& purpose: To Initializes and Deinitializes SSDP
//& type : auto
/**
* @testcase 			ITc_ssdp_initialize_deinitialize_p
* @type 				auto
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @since_tizen			3.0
* @description			Initializes and Deinitializes SSDP
* @scenario				De-Initialize the SSDP initialized in startup\n
* 						Initialize the SSDP\n
* 						De-Initialize the SSDP\n
* 						Initialize the SSDP to be de-initialize in cleanup
* @apicovered			ssdp_initialize, ssdp_deinitialize
* @passcase				When ssdp_initialize and dp_deinitialize return success
* @failcase				When ssdp_initialize or ssdp_deinitialize return failure
* @precondition			none
* @postcondition		none
*/
int ITc_ssdp_initialize_deinitialize_p(void)
{
	START_TEST;
	
	//De-Initialize the SSDP initialized in startup
	int nRet = ssdp_deinitialize();
	PRINT_RESULT(SSDP_ERROR_NONE, nRet, "ssdp_deinitialize", NsdSsdpGetError(nRet));
	
	//Target API
	nRet = ssdp_initialize();
	PRINT_RESULT(SSDP_ERROR_NONE, nRet, "ssdp_initialize", NsdSsdpGetError(nRet));
	
	//Target API
	nRet = ssdp_deinitialize();
	PRINT_RESULT(SSDP_ERROR_NONE, nRet, "ssdp_deinitialize", NsdSsdpGetError(nRet));
	
	//Initialize the SSDP to be de-initialize in cleanup
	nRet = ssdp_initialize();
	PRINT_RESULT_NORETURN(SSDP_ERROR_NONE, nRet, "ssdp_initialize", NsdSsdpGetError(nRet));
		
    return 0;
}

//& purpose: To Create and Destroy a SSDP local service handle
//& type : auto
/**
* @testcase 			ITc_ssdp_create_destroy_local_service_p
* @type 				auto
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @since_tizen			3.0
* @description			Creates and Destroys a SSDP local service handle
* @scenario				initialize ssdp\n
*						create ssdp local service handle\n
*						destroy ssdp local service handle
*						deinitialize ssdp
* @apicovered			ssdp_create_local_service, ssdp_destroy_local_service
* @passcase				When ssdp_create_local_service and ssdp_destroy_local_service return success
* @failcase				When ssdp_create_local_service or ssdp_destroy_local_service return failure
* @precondition			ssdp should be initialized
* @postcondition		ssdp should be de-initialized
*/
int ITc_ssdp_create_destroy_local_service_p(void)
{
	START_TEST;
	
	char *pszTarget = "upnp:rootdevice";
	ssdp_service_h hLocalService = 0;
	
	//Target API
	int nRet = ssdp_create_local_service(pszTarget,&hLocalService);
	PRINT_RESULT(SSDP_ERROR_NONE, nRet, "ssdp_create_local_service", NsdSsdpGetError(nRet));
	CHECK_HANDLE_INT(hLocalService, "ssdp_create_local_service");
	
	//Target API
	nRet = ssdp_destroy_local_service(hLocalService);
	PRINT_RESULT(SSDP_ERROR_NONE, nRet, "ssdp_destroy_local_service", NsdSsdpGetError(nRet));
			
    return 0;
}

//& purpose: To Set and Get the USN (Unique Service Name) of SSDP local service
//& type : auto
/**
* @testcase 			ITc_ssdp_service_set_get_usn_p
* @type 				auto
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @since_tizen			3.0
* @description			Sets and Gets the USN (Unique Service Name) of SSDP local service
* @scenario				initialize ssdp\n
*						create ssdp local service handle\n
*						ssdp_service_set_usn and ssdp_service_get_usn\n
*						compare set and get values\n
*						destroy ssdp local service handle\n
*						deinitialize ssdp
* @apicovered			ssdp_service_set_usn, ssdp_service_get_usn
* @passcase				When ssdp_service_set_usn and ssdp_service_get_usn return success
* @failcase				When ssdp_service_set_usn or ssdp_service_get_usn return failure
* @precondition			ssdp should be initialized
* @postcondition		ssdp should be de-initialized
*/
int ITc_ssdp_service_set_get_usn_p(void)
{
	START_TEST;
	
	ssdp_service_h hLocalService = 0;
	char *pszTarget ="upnp:rootdevice";
	char pszSetUsn[] =  "uuid:1234abce-12ab";
	char *pszGetUsn = NULL;
	
	//Create ssdp local service handle
	int nRet = ssdp_create_local_service(pszTarget,&hLocalService);
	PRINT_RESULT(SSDP_ERROR_NONE, nRet, "ssdp_create_local_service", NsdSsdpGetError(nRet));
	CHECK_HANDLE_INT(hLocalService, "ssdp_create_local_service");
	
	//Target API
	nRet = ssdp_service_set_usn(hLocalService,pszSetUsn);
	PRINT_RESULT_CLEANUP(SSDP_ERROR_NONE, nRet, "ssdp_service_set_usn", NsdSsdpGetError(nRet),ssdp_destroy_local_service(hLocalService));
	
	//Target API
	nRet = ssdp_service_get_usn(hLocalService,&pszGetUsn);
	PRINT_RESULT_CLEANUP(SSDP_ERROR_NONE, nRet, "ssdp_service_get_usn", NsdSsdpGetError(nRet),ssdp_destroy_local_service(hLocalService));
	
	//Compare Set and Get Value
	if (strcmp(pszSetUsn, pszGetUsn) != 0 )
	{
		FPRINTF("[Line : %d][%s] ssdp_service_get_usn return value %s mismatched with set value %s\\n", __LINE__, API_NAMESPACE, pszSetUsn, pszGetUsn);
		ssdp_destroy_local_service(hLocalService);
		return 1;
	}
	
	FREE_MEMORY(pszGetUsn);
	//Destroy ssdp local service handle
	nRet = ssdp_destroy_local_service(hLocalService);
	PRINT_RESULT_NORETURN(SSDP_ERROR_NONE, nRet, "ssdp_destroy_local_service", NsdSsdpGetError(nRet));
			
    return 0;
}

//& purpose: To Set and Get the URL (Uniform Resource Locator) for description of SSDP local service
//& type : auto
/**
* @testcase 			ITc_ssdp_service_set_get_url_p
* @type 				auto
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @since_tizen			3.0
* @description			Sets and Gets the URL (Uniform Resource Locator) for description of SSDP local service
* @scenario				initialize ssdp\n
*						create ssdp local service handle\n
*						ssdp_service_set_url and ssdp_service_get_url\n
*						compare set and get values\n
*						destroy ssdp local service handle\n
*						deinitialize ssdp
* @apicovered			ssdp_service_set_url, ssdp_service_get_url
* @passcase				When ssdp_service_set_url and ssdp_service_get_url return success
* @failcase				When ssdp_service_set_url or ssdp_service_get_url return failure
* @precondition			ssdp should be initialized
* @postcondition		ssdp should be de-initialized
*/
int ITc_ssdp_service_set_get_url_p(void)
{
	START_TEST;
	
	ssdp_service_h hLocalService = 0;
	char *pszTarget = "upnp:rootdevice";
	char pszSetUrl[]  = "localhost";
	char *pszGetUrl = NULL;
	
	//Create ssdp local service handle
	int nRet = ssdp_create_local_service(pszTarget,&hLocalService);
	PRINT_RESULT(SSDP_ERROR_NONE, nRet, "ssdp_create_local_service", NsdSsdpGetError(nRet));
	CHECK_HANDLE_INT(hLocalService, "ssdp_create_local_service");
	
	//Target API
	nRet = ssdp_service_set_url(hLocalService,pszSetUrl);
	PRINT_RESULT_CLEANUP(SSDP_ERROR_NONE, nRet, "ssdp_service_set_url", NsdSsdpGetError(nRet),ssdp_destroy_local_service(hLocalService));
	
	//Target API
	nRet = ssdp_service_get_url(hLocalService,&pszGetUrl);
	PRINT_RESULT_CLEANUP(SSDP_ERROR_NONE, nRet, "ssdp_service_get_url", NsdSsdpGetError(nRet),ssdp_destroy_local_service(hLocalService));
	
	//Compare Set and Get Value
	if (strcmp(pszSetUrl, pszGetUrl) != 0 )
	{
		FPRINTF("[Line : %d][%s] ssdp_service_get_url return value %s mismatched with set value %s\\n", __LINE__, API_NAMESPACE, pszSetUrl, pszGetUrl);
		ssdp_destroy_local_service(hLocalService);
		return 1;
	}
	
	FREE_MEMORY(pszGetUrl);
	//Destroy ssdp local service handle
	nRet = ssdp_destroy_local_service(hLocalService);
	PRINT_RESULT_NORETURN(SSDP_ERROR_NONE, nRet, "ssdp_destroy_local_service", NsdSsdpGetError(nRet));
			
    return 0;
}


//& purpose: To Get the target of SSDP service.
//& type : auto
/**
* @testcase 			ITc_ssdp_service_get_target_p
* @type 				auto
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @since_tizen			3.0
* @description			Gets the target of SSDP service.
* @scenario				initialize ssdp\n
*						create ssdp local service handle\n
*						ssdp_service_get_target\n
*						check get value\n
*						destroy ssdp local service handle\n
*						deinitialize ssdp
* @apicovered			ssdp_service_get_target
* @passcase				When ssdp_service_get_target return success
* @failcase				When ssdp_service_get_target return failure
* @precondition			ssdp should be initialized
* @postcondition		ssdp should be de-initialized
*/
int ITc_ssdp_service_get_target_p(void)
{
	START_TEST;
	
	ssdp_service_h hLocalService = 0;
	char *pszTarget = "upnp:rootdevice";
	char *pszGetTarget = NULL;
	
	//Create ssdp local service handle
	int nRet = ssdp_create_local_service(pszTarget,&hLocalService);
	PRINT_RESULT(SSDP_ERROR_NONE, nRet, "ssdp_create_local_service", NsdSsdpGetError(nRet));
	CHECK_HANDLE_INT(hLocalService, "ssdp_create_local_service");
	
	//Target API
	nRet = ssdp_service_get_target(hLocalService,&pszGetTarget);
	PRINT_RESULT_CLEANUP(SSDP_ERROR_NONE, nRet, "ssdp_service_get_target", NsdSsdpGetError(nRet),ssdp_destroy_local_service(hLocalService));
	
	FPRINTF("[Line : %d][%s] pszGetTarget is %s\\n", __LINE__, API_NAMESPACE,pszGetTarget);
	
	//Check Get Value
	if(pszGetTarget == NULL)
	{
		FPRINTF("[Line : %d][%s] pszGetTarget is null\\n", __LINE__, API_NAMESPACE);
		ssdp_destroy_local_service(hLocalService);
		return 1;
	}
	
	FREE_MEMORY(pszGetTarget);
	//Destroy ssdp local service handle
	nRet = ssdp_destroy_local_service(hLocalService);
	PRINT_RESULT_NORETURN(SSDP_ERROR_NONE, nRet, "ssdp_destroy_local_service", NsdSsdpGetError(nRet));
			
    return 0;
}

//& purpose: To Register and Deregister the SSDP local service for publishing.
//& type : auto
/**
* @testcase 			ITc_ssdp_register_deregister_local_service_p
* @type 				auto
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @since_tizen			3.0
* @description			Registers and Deregisters the SSDP local service for publishing
* @scenario				initialize ssdp\n
*						create ssdp local service handle\n
*						ssdp_register_local_service,ssdp_deregister_local_service\n
*						destroy ssdp local service handle
*						deinitialize ssdp
* @apicovered			ssdp_register_local_service and ssdp_deregister_local_service
* @passcase				When ssdp_register_local_service and ssdp_deregister_local_service return success
* @failcase				When ssdp_register_local_service or ssdp_deregister_local_service return failure
* @precondition			ssdp should be initialized
* @postcondition		ssdp should be de-initialized
*/
int ITc_ssdp_register_deregister_local_service_p(void)
{
	START_TEST;
	
	ssdp_service_h hLocalService = 0;
	char *pszTarget =  "upnp:rootdevice";
	char *pszSetUrl =  "192.168.0.1";
	char *pszSetUsn =  "uuid:1234abce";
	
	//Create ssdp local service handle
	int nRet = ssdp_create_local_service(pszTarget,&hLocalService);
	PRINT_RESULT(SSDP_ERROR_NONE, nRet, "ssdp_create_local_service", NsdSsdpGetError(nRet));
	CHECK_HANDLE_INT(hLocalService, "ssdp_create_local_service");
	
	//Set the usn for description of SSDP local service
	nRet = ssdp_service_set_usn(hLocalService,pszSetUsn);
	PRINT_RESULT_CLEANUP(SSDP_ERROR_NONE, nRet, "ssdp_service_set_usn", NsdSsdpGetError(nRet),ssdp_destroy_local_service(hLocalService));
	
	
	//Set the url for description of SSDP local service
	nRet = ssdp_service_set_url(hLocalService,pszSetUrl);
	PRINT_RESULT_CLEANUP(SSDP_ERROR_NONE, nRet, "ssdp_service_set_url", NsdSsdpGetError(nRet),ssdp_destroy_local_service(hLocalService));
	
	//Target API : As discussed with developer callback is not used currently so we are not checking for callback hit
	nRet = ssdp_register_local_service(hLocalService, Nsd_registered_cb_p, NULL);
	PRINT_RESULT_CLEANUP(SSDP_ERROR_NONE, nRet, "ssdp_register_local_service", NsdSsdpGetError(nRet),ssdp_destroy_local_service(hLocalService));
		
	//Target API
	nRet = ssdp_deregister_local_service(hLocalService);
	PRINT_RESULT_NORETURN(SSDP_ERROR_NONE, nRet, "ssdp_deregister_local_service", NsdSsdpGetError(nRet));
	
	//Destroy ssdp local service handle
	nRet = ssdp_destroy_local_service(hLocalService);
	PRINT_RESULT_NORETURN(SSDP_ERROR_NONE, nRet, "ssdp_destroy_local_service", NsdSsdpGetError(nRet));
			
    return 0;
}

//& purpose: To Start and Stop browsing the SSDP remote service.
//& type : auto
/**
* @testcase 			ITc_ssdp_start_stop_browsing_service_p
* @type 				auto
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @since_tizen			3.0
* @description			Starts and Stop browsing the SSDP remote service
* @scenario				initialize ssdp\n
*						create ssdp local service handle\n
*						ssdp_start_browsing_service,ssdp_stop_browsing_service\n
*						destroy ssdp local service handle
*						deinitialize ssdp
* @apicovered			ssdp_start_browsing_service and ssdp_stop_browsing_service
* @passcase				When ssdp_start_browsing_service and ssdp_stop_browsing_service return success
* @failcase				When ssdp_start_browsing_service or ssdp_stop_browsing_service return failure
* @precondition			ssdp should be initialized
* @postcondition		ssdp should be de-initialized
*/
int ITc_ssdp_start_stop_browsing_service_p(void)
{
	START_TEST;
	
	ssdp_browser_h hSsdpBrowser = 0;
	char *pszTarget = "upnp:rootdevice";
	ssdp_service_h hLocalService = 0;
	char *pszSetUrl =  "http://192.168.0.110/";
	char *pszSetUsn =  "uuid:1234abce";

	//Create ssdp local service handle
	int nRet = ssdp_create_local_service(pszTarget,&hLocalService);
	PRINT_RESULT(SSDP_ERROR_NONE, nRet, "ssdp_create_local_service", NsdSsdpGetError(nRet));
	CHECK_HANDLE_INT(hLocalService, "ssdp_create_local_service");
	
	//Set the usn for description of SSDP local service
	nRet = ssdp_service_set_usn(hLocalService,pszSetUsn);
	PRINT_RESULT_CLEANUP(SSDP_ERROR_NONE, nRet, "ssdp_service_set_usn", NsdSsdpGetError(nRet),ssdp_destroy_local_service(hLocalService));
	
	
	//Set the url for description of SSDP local service
	nRet = ssdp_service_set_url(hLocalService,pszSetUrl);
	PRINT_RESULT_CLEANUP(SSDP_ERROR_NONE, nRet, "ssdp_service_set_url", NsdSsdpGetError(nRet),ssdp_destroy_local_service(hLocalService));
	
	//Target API : As discussed with developer callback is not used currently so we are not checking for callback hit
	nRet = ssdp_register_local_service(hLocalService, Nsd_registered_cb_p, NULL);
	PRINT_RESULT_CLEANUP(SSDP_ERROR_NONE, nRet, "ssdp_register_local_service", NsdSsdpGetError(nRet),ssdp_destroy_local_service(hLocalService));
		
	//Target API : As discussed with developer callback is not used currently so we are not checking for callback hit
	nRet = ssdp_start_browsing_service(pszTarget,&hSsdpBrowser,Nsd_Ssdp_Found_cb_p, NULL);
	PRINT_RESULT_CLEANUP(SSDP_ERROR_NONE, nRet, "ssdp_start_browsing_service", NsdSsdpGetError(nRet),ssdp_destroy_local_service(hLocalService));
		
	//Target API
	nRet = ssdp_stop_browsing_service(hSsdpBrowser);
	PRINT_RESULT_CLEANUP(SSDP_ERROR_NONE, nRet, "ssdp_stop_browsing_service", NsdSsdpGetError(nRet),ssdp_deregister_local_service(hLocalService); ssdp_destroy_local_service(hLocalService));
	
	//Target API
	nRet = ssdp_deregister_local_service(hLocalService);
	PRINT_RESULT_NORETURN(SSDP_ERROR_NONE, nRet, "ssdp_deregister_local_service", NsdSsdpGetError(nRet));
	
	//Destroy ssdp local service handle
	nRet = ssdp_destroy_local_service(hLocalService);
	PRINT_RESULT_NORETURN(SSDP_ERROR_NONE, nRet, "ssdp_destroy_local_service", NsdSsdpGetError(nRet));
					
    return 0;
}

/** @} */
/** @} */