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
#include "ITs-iotcon-common.h"

//& set: Iotcon

/** @addtogroup itc-iotcon
*  @ingroup itc
*  @{
*/

static iotcon_remote_resource_h g_hClient = NULL;
static iotcon_resource_types_h g_hTypes = NULL;
static iotcon_resource_interfaces_h g_hInterface = NULL;
static iotcon_remote_resource_h g_hResourceHandle = NULL;
static iotcon_remote_resource_h g_hcacheHandle = NULL;
static int g_nRetcb;
static iotcon_resource_h g_light_resource;
static int g_brightness = 1;
static int g_timeout_count;
static bool g_found;

#define ENCAP_LIGHT_RESOURCE_TYPE "core.light"
#define ENCAP_LIGHT_RESOURCE_URI "/a/light"

/**
 * @function           gmain_loop_quit_idle
 * @description                Called if some callback is not invoked for a particular timeout
 * @parameter          gpointer data
 * @return                     gboolean
 */
static gboolean gmain_loop_quit_idle(gpointer p)
{
	if (g_pMainLoop)
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
	return G_SOURCE_REMOVE;
}

/**
* @function			Iotcon_update_lite_resource
* @description		create , add and update state
* @parameter[IN]	void
* @return			void
*/
static void Iotcon_update_lite_resource(void)
{
	iotcon_attributes_h state = NULL;

	int ret = iotcon_attributes_create(&state);
	if (IOTCON_ERROR_NONE != ret)
	{
		FPRINTF("[Line : %d][%s] iotcon_attributes_create fail\\n", __LINE__, API_NAMESPACE);
		return;
	}
	ret = iotcon_attributes_add_int(state, "int", ++g_brightness);
	if (IOTCON_ERROR_NONE != ret)
	{
		FPRINTF("[Line : %d][%s] iotcon_attributes_add_int fail\\n", __LINE__, API_NAMESPACE);
		iotcon_attributes_destroy(state);
		return;
	}
	ret = iotcon_lite_resource_update_attributes(g_hLiteLightResource, state);
	if (IOTCON_ERROR_NONE != ret)
	{
		FPRINTF("[Line : %d][%s] iotcon_lite_resource_update_attributes fail\\n", __LINE__, API_NAMESPACE);
		iotcon_attributes_destroy(state);
		return;
	}
	iotcon_attributes_destroy(state);
	return;
}

/**
* @function			IotconRemoteResourceRequestHandlerCB
* @description		Resourse and request handler
* @parameter[IN]	iotcon_resource_h resource
* @parameter[IN]	iotcon_request_h request
* @parameter[IN]	user_data
* @return			void
*/
static void IotconRemoteResourceRequestHandlerCB(iotcon_resource_h resource,iotcon_request_h request, void *user_data)
{
	return;
}
/**
* @function			IotconRepresentationChangedCB
* @description		Specifies the type of function passed to iotcon_query_foreach()
* @parameter[IN]	iotcon_remote_resource_h resource
* @parameter[IN]	iotcon_representation_h representation
* @parameter[IN]	user_data The user data to pass to the function
* @return			true to continue with the next iteration of the loop.
*/
static void IotconRepresentationChangedCB(iotcon_remote_resource_h resource, iotcon_representation_h representation, void *user_data)
{
	FPRINTF("[Line : %d][%s] IotconRepresentationChangedCB\\n", __LINE__, API_NAMESPACE);
	iotcon_representation_h repr = NULL;

	g_nRetcb = true;

	if((resource == NULL) || (representation == NULL))
	{
		FPRINTF("[Line : %d][%s] IotconRepresentationChangedCB input resource and representation is NULL failed !!!\\n", __LINE__, API_NAMESPACE);
	}

	g_nCheckAPICb = iotcon_remote_resource_get_cached_representation(resource, &repr);
	if (IOTCON_ERROR_NONE != g_nCheckAPICb)
	{
		FPRINTF("[Line : %d][%s] iotcon_remote_resource_get_cached_representation failed, error returned : %s\\n", __LINE__, API_NAMESPACE , IotConGetError(g_nCheckAPICb));
		g_idle_add(gmain_loop_quit_idle, NULL);
		return;
	}

	g_idle_add(gmain_loop_quit_idle, NULL);
	return;
}
/**
* @function			IotconMonitoringChangedCB
* @description		Specifies the type of function passed to iotcon_query_foreach()
* @parameter[IN]	iotcon_remote_resource_h resource
* @parameter[IN]	iotcon_representation_h representation
* @parameter[IN]	user_data The user data to pass to the function
* @return			true to continue with the next iteration of the loop.
*/
static void IotconMonitoringChangedCB(iotcon_remote_resource_h resource, iotcon_remote_resource_state_e state, void *user_data)
{
	FPRINTF("[Line : %d][%s] IotconMonitoringChangedCB\\n", __LINE__, API_NAMESPACE);

	g_nRetcb = true;
	if(resource == NULL)
	{
		FPRINTF("[Line : %d][%s] IotconMonitoringChangedCB input resourse is NULL failed !!!\\n", __LINE__, API_NAMESPACE);
	}

	g_idle_add(gmain_loop_quit_idle, NULL);

	return;
}
/**
* @function			IotconCachingChangedCB
* @description		Specifies the type of function passed to iotcon_query_foreach()
* @parameter[IN]	iotcon_remote_resource_h resource
* @parameter[IN]	iotcon_representation_h representation
* @parameter[IN]	user_data The user data to pass to the function
* @return			true to continue with the next iteration of the loop.
*/
static void IotconCachingChangedCB(iotcon_remote_resource_h resource, iotcon_representation_h representation, void *user_data)
{
	FPRINTF("[Line : %d][%s] IotconCachingChangedCB\\n", __LINE__, API_NAMESPACE);

	if((resource == NULL)||(representation == NULL))
	{
		FPRINTF("[Line : %d][%s] IotconCachingChangedCB input resource and representation is NULL failed !!!\\n", __LINE__, API_NAMESPACE);
	}

	g_nRetcb = true;

	g_idle_add(gmain_loop_quit_idle, NULL);
	return;
}

/**
* @function 		IotconRemoteResourceOptionsCB
* @description	 	Callback Function
* @parameter		iotcon_remote_resource_h resource, iotcon_error_e result,void *user_data
* @return 			bool
*/
 static bool IotconRemoteResourceOptionsCB(iotcon_remote_resource_h resource, iotcon_error_e result,void *user_data)
{
	FPRINTF("[Line : %d][%s] IotconRemoteResourceOptionsCB\\n", __LINE__, API_NAMESPACE);
	int nRet;
	iotcon_query_h hQuery;
	g_bCheckCb = true;

	if (IOTCON_ERROR_TIMEOUT == result && g_timeout_count < TIMEOUT_COUNT_MAX)
	{
		g_timeout_count++;
		nRet = iotcon_query_create(&hQuery);
		PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_create", IotConGetError(nRet));

		nRet = iotcon_query_set_resource_type(hQuery, LIGHT_RESOURCE_TYPE);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_query_set_resource_type", IotConGetError(nRet),iotcon_query_destroy(hQuery));

		nRet = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY, hQuery, IotconRemoteResourceOptionsCB, NULL);
		if (IOTCON_ERROR_NONE != nRet)
		{
			FPRINTF("[Line : %d][%s] iotcon_find_resource fail in startup error returned : %s\\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
			iotcon_query_destroy(hQuery);
			g_idle_add(gmain_loop_quit_idle, NULL);
		}
		nRet = iotcon_query_destroy(hQuery);
		PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_query_destroy", IotConGetError(nRet));
		return false;
	}
	else if (IOTCON_ERROR_NONE != result)
	{
		g_idle_add(gmain_loop_quit_idle, NULL);
		return false;
	}

	if (g_found)
		return false;

	g_found = true;


	if(resource == NULL)
	{
		FPRINTF("[Line : %d][%s] Iotcon_presence_found_resource_cb input resource is NULL failed !!!\\n", __LINE__, API_NAMESPACE);
	}

	char *host_address, *uri;
	iotcon_remote_resource_get_host_address(resource, &host_address);
	iotcon_remote_resource_get_uri_path(resource, &uri);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] host_address[%s], uri[%s]", __FUNCTION__, __LINE__, host_address, uri);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] expected host_address[%s], found host_address[%s]", __FUNCTION__, __LINE__, g_ipv4_address, host_address);

	if (strstr(host_address, g_ipv4_address) == NULL) { // targeted resource, BUT wrong device, so skip this resource and try again
		g_found = false;
		return true;
	}

	nRet = iotcon_remote_resource_clone(resource, &g_hResourceHandle);
	if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] iotcon_remote_resource_clone fail error returned : %s\\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
		g_idle_add(gmain_loop_quit_idle, NULL);
		return false;
	}

	g_idle_add(gmain_loop_quit_idle, NULL);
	return false;
}

/**
* @function 		IotconCreateRemoteResource
* @description	 	Create Remote Resource
* @parameter		NA
* @return 			NA
*/
int IotconCreateRemoteResource()
{
	int nRet = iotcon_resource_types_create(&g_hTypes);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_create", IotConGetError(nRet));
	CHECK_HANDLE(g_hTypes,"iotcon_resource_types_create");

	nRet = iotcon_resource_types_add(g_hTypes,LIGHT_RESOURCE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_add", IotConGetError(nRet), iotcon_resource_types_destroy(g_hTypes));

	nRet = iotcon_resource_interfaces_create(&g_hInterface);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_create", IotConGetError(nRet), iotcon_resource_types_destroy(g_hTypes));
	CHECK_HANDLE(g_hInterface,"iotcon_resource_interfaces_create");

	nRet = iotcon_resource_interfaces_add(g_hInterface, IOTCON_INTERFACE_DEFAULT);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_add", IotConGetError(nRet), iotcon_resource_interfaces_destroy(g_hInterface);iotcon_resource_types_destroy(g_hTypes));

	nRet = iotcon_remote_resource_create(REMOTE_IP, IOTCON_CONNECTIVITY_IP, REMOTE_RESOURCE_LIGHT,IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE, g_hTypes, g_hInterface, &g_hClient);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_create", IotConGetError(nRet),  iotcon_resource_interfaces_destroy(g_hInterface);iotcon_resource_types_destroy(g_hTypes));
    CHECK_HANDLE(g_hClient,"iotcon_remote_resource_create");

    iotcon_resource_types_destroy(g_hTypes);
	iotcon_resource_interfaces_destroy(g_hInterface);
	return 0;
}

/**
* @function 		IotconDestroyRemoteResource
* @description	 	Destroy Remote Resource
* @parameter		NA
* @return 			NA
*/
void IotconDestroyRemoteResource()
{
	if (g_hClient)
	{
		iotcon_remote_resource_destroy(g_hClient);
		g_hClient = NULL;
	}
}

/**
* @function 		IotconCreateResource
* @description	 	Create Resource
* @parameter		NA
* @return 			int
*/
int IotconCreateResource()
{
	int nRet = iotcon_resource_types_create(&g_hTypes);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_create", IotConGetError(nRet));
	CHECK_HANDLE(g_hTypes,"iotcon_resource_types_create");

	nRet = iotcon_resource_types_add(g_hTypes,LIGHT_RESOURCE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_add", IotConGetError(nRet), iotcon_resource_types_destroy(g_hTypes));

	nRet = iotcon_resource_interfaces_create(&g_hInterface);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_create", IotConGetError(nRet), iotcon_resource_types_destroy(g_hTypes));
	CHECK_HANDLE(g_hInterface,"iotcon_resource_interfaces_create");

	nRet = iotcon_resource_interfaces_add(g_hInterface, IOTCON_INTERFACE_DEFAULT);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_add", IotConGetError(nRet), iotcon_resource_interfaces_destroy(g_hInterface);iotcon_resource_types_destroy(g_hTypes));

	nRet = iotcon_resource_create(REMOTE_RESOURCE_LIGHT,g_hTypes,g_hInterface,(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),IotconRemoteResourceRequestHandlerCB,NULL,&g_light_resource);
    PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_create", IotConGetError(nRet),  iotcon_resource_interfaces_destroy(g_hInterface);iotcon_resource_types_destroy(g_hTypes));
    CHECK_HANDLE(g_light_resource,"iotcon_resource_create");

    iotcon_resource_types_destroy(g_hTypes);
	iotcon_resource_interfaces_destroy(g_hInterface);
	return 0;
}

/**
* @function 		IotconDestroyResource
* @description	 	Destroy Resource
* @parameter		NA
* @return 			NA
*/
void IotconDestroyResource()
{
	if (g_light_resource)
	{
		iotcon_resource_destroy(g_light_resource);
		g_light_resource = NULL;
	}
}

/**
* @function			IotconGetChangedCB
* @description		callback
* @parameter[IN]	iotcon_remote_resource_h resource
* @parameter[IN]	iotcon_error_e err
* @parameter[IN]	iotcon_request_type_e request_type
* @parameter[IN]	iotcon_response_h response
* @parameter[IN]	user_data The user data to pass to the function
* @return			true to continue with the next iteration of the loop.
*/
static void IotconGetChangedCB(iotcon_remote_resource_h resource, iotcon_error_e err,iotcon_request_type_e request_type, iotcon_response_h response, void *user_data)
{
	if((resource == NULL)||(response == NULL))
	{
		FPRINTF("[Line : %d][%s] IotconGetChangedCB input resource and response is NULL failed !!!\\n", __LINE__, API_NAMESPACE);
	}
	g_nGetCb = true;

	g_idle_add(gmain_loop_quit_idle, NULL);

	return;
}
/**
* @function			IotconPutChangedCB
* @description		callback
* @parameter[IN]	iotcon_remote_resource_h resource
* @parameter[IN]	iotcon_error_e err
* @parameter[IN]	iotcon_request_type_e request_type
* @parameter[IN]	iotcon_response_h response
* @parameter[IN]	user_data The user data to pass to the function
* @return			true to continue with the next iteration of the loop.
*/
static void IotconPutChangedCB(iotcon_remote_resource_h resource, iotcon_error_e err,iotcon_request_type_e request_type, iotcon_response_h response, void *user_data)
{
	if((resource == NULL)||(response == NULL))
	{
		FPRINTF("[Line : %d][%s] IotconPutChangedCB input resource and response is NULL failed !!!\\n", __LINE__, API_NAMESPACE);
	}
	g_nPutCb = true;

	g_idle_add(gmain_loop_quit_idle, NULL);

	return;
}
/**
* @function			IotconPostChangedCB
* @description		callback
* @parameter[IN]	iotcon_remote_resource_h resource
* @parameter[IN]	iotcon_error_e err
* @parameter[IN]	iotcon_request_type_e request_type
* @parameter[IN]	iotcon_response_h response
* @parameter[IN]	user_data The user data to pass to the function
* @return			true to continue with the next iteration of the loop.
*/
static void IotconPostChangedCB(iotcon_remote_resource_h resource, iotcon_error_e err,iotcon_request_type_e request_type, iotcon_response_h response, void *user_data)
{
	if((resource == NULL)||(response == NULL))
	{
		FPRINTF("[Line : %d][%s] IotconPostChangedCB input resource and response is NULL failed !!!\\n", __LINE__, API_NAMESPACE);
	}
	g_nPostCb = true;

	g_idle_add(gmain_loop_quit_idle, NULL);

	return;
}
/**
* @function			IotconDeleteChangedCB
* @description		callback
* @parameter[IN]	iotcon_remote_resource_h resource
* @parameter[IN]	iotcon_error_e err
* @parameter[IN]	iotcon_request_type_e request_type
* @parameter[IN]	iotcon_response_h response
* @parameter[IN]	user_data The user data to pass to the function
* @return			true to continue with the next iteration of the loop.
*/
static void IotconDeleteChangedCB(iotcon_remote_resource_h resource, iotcon_error_e err,iotcon_request_type_e request_type, iotcon_response_h response, void *user_data)
{
	if((resource == NULL)||(response == NULL))
	{
		FPRINTF("[Line : %d][%s] IotconDeleteChangedCB input resource and response is NULL failed !!!\\n", __LINE__, API_NAMESPACE);
	}
	g_nDeleteCb = true;

	g_idle_add(gmain_loop_quit_idle, NULL);

	return;
}

/**
* @function			IotconObserveChangedCB
* @description		Specifies the type of function passed to iotcon_remote_resource_observe_deregister()
* @parameter[IN]	iotcon_remote_resource_h resource
* @parameter[IN]	iotcon_error_e err
* @parameter[IN]	int sequence_number
* @parameter[IN]	iotcon_response_h response
* @parameter[IN]	user_data The user data to pass to the function
* @return			true to continue with the next iteration of the loop.
*/
static void IotconObserveChangedCB(iotcon_remote_resource_h resource, iotcon_error_e err,int sequence_number, iotcon_response_h response, void *user_data)
{
	if((resource == NULL)||(response == NULL))
	{
		FPRINTF("[Line : %d][%s] IotconObserveChangedCB input resource and response is NULL failed !!!\\n", __LINE__, API_NAMESPACE);
	}

	g_nRetcb = true;

	g_idle_add(gmain_loop_quit_idle, NULL);

	return;
}

/**
* @function			IotconFindResourceCB
* @description		callback function
* @parameter[IN]	iotcon_remote_resource_h resource
* @parameter[IN]	iotcon_error_e err
* @parameter[IN]	user_data The user data to pass to the function
* @return			bool
*/
static bool IotconFindResourceCB(iotcon_remote_resource_h resource, iotcon_error_e err, void *user_data)
{
	FPRINTF("[Line : %d][%s] IotconFindResourceCB\\n", __LINE__, API_NAMESPACE);
	char *host_address, *uri;
	g_bCheckCb = true;
	g_nCheckAPICb = err;

	if (IOTCON_ERROR_TIMEOUT == err && g_timeout_count < TIMEOUT_COUNT_MAX)
	{
		g_idle_add(gmain_loop_quit_idle, NULL);
		g_timeout_count++;
		return false;
	}
	else if (IOTCON_ERROR_NONE != err)
	{
		g_idle_add(gmain_loop_quit_idle, NULL);
		return false;
	}

	if (g_found) {
		g_idle_add(gmain_loop_quit_idle, NULL);
		return false;
	}

	if (resource == NULL) {
		FPRINTF("[Line : %d][%s] IotconFindResourceCB input resource is NULL failed !!!\\n", __LINE__, API_NAMESPACE);
		g_idle_add(gmain_loop_quit_idle, NULL);
		return false;
	}

	g_found = true;

	iotcon_remote_resource_get_host_address(resource, &host_address);
	iotcon_remote_resource_get_uri_path(resource, &uri);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] host_address[%s], uri[%s]", __FUNCTION__, __LINE__, host_address, uri);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] expected host_address[%s], found host_address[%s]", __FUNCTION__, __LINE__, g_ipv4_address, host_address);

	if (strstr(host_address, g_ipv4_address) == NULL) { // targeted resource, BUT wrong device, so skip this resource and try again
		g_found = false;
		return true;
	}

	g_nCheckAPICb = iotcon_remote_resource_clone(resource, &g_hcacheHandle);
	if (IOTCON_ERROR_NONE != g_nCheckAPICb)
	{
		FPRINTF("[Line : %d][%s] iotcon_remote_resource_clone fail error returned : %s\\n", __LINE__, API_NAMESPACE, IotConGetError(g_nCheckAPICb));
	}

	g_idle_add(gmain_loop_quit_idle, NULL);

	return false;
}

/**
 * @function 		ITs_iotcon_remote_resource_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_remote_resource_startup(void)
{
	struct stat stBuff;
	char *svr_db_path;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	g_bIotconConnect = true;
	g_bFeatureUnsupported = false;

	icitc_get_client_ipv4_address();

	ic_get_svr_db_path(&svr_db_path);
   int nRet = iotcon_initialize(svr_db_path);
	free(svr_db_path);

	if ( !TCTCheckSystemInfoFeatureSupported(IOTCON_FEATURE, API_NAMESPACE) )
	{

		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] iotcon_initialize API call returned mismatch %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
			g_bIotconConnect = false;
		}
		else
		{
			FPRINTF("[Line : %d][%s] iotcon_initialize API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
			g_bFeatureUnsupported = true;
		}
		return;
	}

	if ( nRet != IOTCON_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] iotcon_initialize failed API return %s error \\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
		g_bIotconConnect = false;
		return;
	}

	return;
}


/**
 * @function 		ITs_iotcon_remote_resource_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_remote_resource_cleanup(void)
{
	icitc_free_client_ipv4_address();

	if( g_bIotconConnect )
	{
		iotcon_deinitialize();
	}
	return;
}

/** @addtogroup itc-iotcon-testcases
*  @brief 		Integration testcases for module iotcon
*  @ingroup 	itc-iotcon
*  @{
*/

//& purpose: Creates a new query handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_remote_resource_create_destroy_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Create/destroy a remote resource handle.
* @scenario				call iotcon_initialize() ,create types , add types then create remote resource;
* @apicovered			iotcon_remote_resource_create , iotcon_remote_resource_destroy ,iotcon_resource_types_add ,iotcon_resource_types_create.
* @passcase				When iotcon_remote_resource_create and iotcon_remote_resource_destroy is successful.
* @failcase				If API iotcon_remote_resource_create and iotcon_remote_resource_destroy fails.
* @precondition			iotcon_initialize() should be successfully called
* @postcondition		NA
*/
int ITc_iotcon_remote_resource_create_destroy_p(void)
{
	START_TEST;

	iotcon_remote_resource_h hClient = NULL;
	iotcon_resource_types_h hTypes = NULL;
	iotcon_resource_interfaces_h hInterface = NULL;

	int nRet = iotcon_resource_types_create(&hTypes);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_create", IotConGetError(nRet));
	CHECK_HANDLE(hTypes,"iotcon_resource_types_create");

	nRet = iotcon_resource_types_add(hTypes, LIGHT_RESOURCE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_add", IotConGetError(nRet), iotcon_resource_types_destroy(hTypes));

	nRet = iotcon_resource_interfaces_create(&hInterface);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_create", IotConGetError(nRet), iotcon_resource_types_destroy(hTypes));
	CHECK_HANDLE(hInterface,"iotcon_resource_interfaces_create");

	nRet = iotcon_resource_interfaces_add(hInterface, IOTCON_INTERFACE_DEFAULT);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_create", IotConGetError(nRet),
						 iotcon_resource_interfaces_destroy(hInterface);iotcon_resource_types_destroy(hTypes));

	nRet = iotcon_remote_resource_create(REMOTE_IP, IOTCON_CONNECTIVITY_IP, REMOTE_RESOURCE_LIGHT,IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE
										, hTypes, hInterface, &hClient);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_create", IotConGetError(nRet),
						 iotcon_resource_interfaces_destroy(hInterface);iotcon_resource_types_destroy(hTypes));
	CHECK_HANDLE(hClient,"iotcon_remote_resource_create");

	nRet = iotcon_remote_resource_destroy(hClient);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_destroy", IotConGetError(nRet),
						 iotcon_resource_interfaces_destroy(hInterface);iotcon_resource_types_destroy(hTypes));

	iotcon_resource_interfaces_destroy(hInterface);
	iotcon_resource_types_destroy(hTypes);

	return 0;
}


//& purpose: Creates a new query handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_remote_resource_clone_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Creates clone of existing resource .
* @scenario				Call iotcon_remote_resource_clone
* @apicovered			iotcon_remote_resource_clone .iotcon_remote_resource_destroy
* @passcase				When iotcon_remote_resource_clone is successful.
* @failcase				If target API iotcon_remote_resource_clone fails.
* @precondition			iotcon_initialize() should be successfully called
* @postcondition		NA
*/
int ITc_iotcon_remote_resource_clone_p(void)
{
	START_TEST;

	iotcon_remote_resource_h hClient = NULL;
	iotcon_resource_types_h hTypes = NULL;
	iotcon_resource_interfaces_h hInterface = NULL;
	iotcon_remote_resource_h hClonedClient = NULL;

	int nRet = iotcon_resource_types_create(&hTypes);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_create", IotConGetError(nRet));
	CHECK_HANDLE(hTypes,"iotcon_resource_types_create");

	nRet = iotcon_resource_types_add(hTypes, LIGHT_RESOURCE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_add", IotConGetError(nRet), iotcon_resource_types_destroy(hTypes));

	nRet = iotcon_resource_interfaces_create(&hInterface);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_create", IotConGetError(nRet), iotcon_resource_types_destroy(hTypes));
	CHECK_HANDLE(hInterface,"iotcon_resource_interfaces_create");

	nRet = iotcon_resource_interfaces_add(hInterface, IOTCON_INTERFACE_DEFAULT);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_create", IotConGetError(nRet),
						 iotcon_resource_interfaces_destroy(hInterface);iotcon_resource_types_destroy(hTypes));

	nRet = iotcon_remote_resource_create(REMOTE_IP, IOTCON_CONNECTIVITY_IP, REMOTE_RESOURCE_LIGHT,IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE
										, hTypes, hInterface, &hClient);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_create", IotConGetError(nRet),
						 iotcon_resource_interfaces_destroy(hInterface);iotcon_resource_types_destroy(hTypes));
	CHECK_HANDLE(hClient,"iotcon_remote_resource_create");

	nRet = iotcon_remote_resource_clone(hClient, &hClonedClient);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_clone", IotConGetError(nRet),
						 iotcon_resource_interfaces_destroy(hInterface);iotcon_resource_types_destroy(hTypes);iotcon_remote_resource_destroy(hClient));
	CHECK_HANDLE(hClonedClient,"iotcon_remote_resource_clone");

	iotcon_resource_interfaces_destroy(hInterface);
	iotcon_remote_resource_destroy(hClient);
	iotcon_remote_resource_destroy(hClonedClient);
	iotcon_resource_types_destroy(hTypes);

	return 0;
}
//& purpose: Creates a new query handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_remote_resource_observe_register_deregister_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Register/Deregister remote resource.
* @scenario				call iotcon_remote_resource_clone and iotcon_remote_resource_get to invoke callback function
* @apicovered			iotcon_remote_resource_clone , iotcon_remote_resource_get ,	iotcon_remote_resource_destroy,iotcon_remote_resource_observe_register, iotcon_remote_resource_observe_deregister
* @passcase				When iotcon_query_create is successful.
* @failcase				If target API fails.
* @precondition			iotcon_initialize() should be successfully called
* @postcondition		NA
*/
int ITc_iotcon_remote_resource_observe_register_deregister_p(void)
{
	START_TEST;

	int nIotconTimeoutId = 0;
	iotcon_query_h hQuery;
	int nRet = IotconCreateLiteResource();
    if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] IotconCreateLiteResource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		return 1;
	}
	g_bCheckCb = false;
	g_nRetcb = false;
	g_found = false;
	g_nCheckAPICb = 0;
	g_timeout_count = 0;

	while (g_timeout_count < TIMEOUT_COUNT_MAX && g_found == false) {
		nRet = iotcon_query_create(&hQuery);
		PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_create", IotConGetError(nRet));

		nRet = iotcon_query_set_resource_type(hQuery, LIGHT_RESOURCE_TYPE);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_query_set_resource_type", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_query_destroy(hQuery));

		nRet = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY, hQuery, IotconFindResourceCB, NULL);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_find_resource", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_query_destroy(hQuery));

		RUN_POLLING_LOOP;

		nRet = iotcon_query_destroy(hQuery);
		PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_query_destroy", IotConGetError(nRet));

		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, g_nCheckAPICb, "API call inside callback failed", IotConGetError(g_nCheckAPICb),IotconDestroyLiteResource());
	}

	if (g_hcacheHandle == NULL) {
		FPRINTF("[Line : %d][%s] Find resource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		IotconDestroyLiteResource();
		return 1;
	}

	if (g_found == false) {
		FPRINTF("[Line : %d][%s] Find resource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		iotcon_remote_resource_destroy(g_hcacheHandle);
		g_hcacheHandle = NULL;
		IotconDestroyLiteResource();
		return 1;
	}

	nRet = iotcon_remote_resource_observe_register(g_hcacheHandle, IOTCON_OBSERVE_IGNORE_OUT_OF_ORDER, NULL, IotconObserveChangedCB, NULL);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_observe_register", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_remote_resource_destroy(g_hcacheHandle));

	RUN_POLLING_LOOP;

	nRet = iotcon_remote_resource_observe_deregister(g_hcacheHandle);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_observe_deregister", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_remote_resource_destroy(g_hcacheHandle));

	nRet = iotcon_remote_resource_destroy(g_hcacheHandle);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_destroy", IotConGetError(nRet));

	if((g_bCheckCb == false) || (g_nRetcb == false))
	{
		FPRINTF("[Line : %d][%s] IotconObserveChangedCB callback not invoked: \\n", __LINE__, API_NAMESPACE );
		IotconDestroyLiteResource();
		return 1;
	}

	IotconDestroyLiteResource();

	return 0;
}
//& purpose: Creates a new query handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_remote_resource_get_put_post_delete_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get put post delete remote resource.
* @scenario				call iotcon_remote_resource_clone
* @apicovered			iotcon_remote_resource_clone , iotcon_remote_resource_get ,iotcon_representation_create	,iotcon_remote_resource_put,iotcon_remote_resource_post,iotcon_remote_resource_delete
* @passcase				When iotcon_remote_resource_clone , iotcon_remote_resource_get ,iotcon_representation_create	,iotcon_remote_resource_put,iotcon_remote_resource_post,iotcon_remote_resource_delete is successful.
* @failcase				If target API fails.
* @precondition			iotcon_initialize() should be successfully called
* @postcondition		NA
*/
int ITc_iotcon_remote_resource_get_put_post_delete_p(void)
{
	START_TEST;

	int nIotconTimeoutId = 0;
	iotcon_query_h hQuery;
	iotcon_representation_h hRepr = NULL;
	int nRet = IotconCreateLiteResource();
    if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] IotconCreateLiteResource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		return 1;
	}
	g_bCheckCb = false;
	g_nGetCb = false;
	g_nPutCb = false;
	g_nPostCb = false;
	g_nDeleteCb = false;
	g_nCheckAPICb = 0;
	g_found = false;
	g_timeout_count = 0;

	while (g_timeout_count < TIMEOUT_COUNT_MAX && g_found == false) {
		nRet = iotcon_query_create(&hQuery);
		PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_create", IotConGetError(nRet));

		nRet = iotcon_query_set_resource_type(hQuery, LIGHT_RESOURCE_TYPE);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_query_set_resource_type", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_query_destroy(hQuery));

		nRet = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY, hQuery, IotconFindResourceCB, NULL);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_find_resource", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_query_destroy(hQuery));

		RUN_POLLING_LOOP;

		nRet = iotcon_query_destroy(hQuery);
		PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_query_destroy", IotConGetError(nRet));

		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, g_nCheckAPICb, "API call inside callback failed", IotConGetError(g_nCheckAPICb),IotconDestroyLiteResource());
	}

	if (g_hcacheHandle == NULL) {
		FPRINTF("[Line : %d][%s] Find resource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		IotconDestroyLiteResource();
		return 1;
	}

	if (g_found == false) {
		FPRINTF("[Line : %d][%s] Find resource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		iotcon_remote_resource_destroy(g_hcacheHandle);
		g_hcacheHandle = NULL;
		IotconDestroyLiteResource();
		return 1;
	}

	nRet = iotcon_query_create(&hQuery);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_create", IotConGetError(nRet));

	nRet = iotcon_query_add(hQuery, "key", "value");
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_query_add", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_remote_resource_destroy(g_hcacheHandle);iotcon_query_destroy(hQuery));

	//Get
	nRet =  iotcon_remote_resource_get(g_hcacheHandle, hQuery, IotconGetChangedCB, NULL);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_get", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_remote_resource_destroy(g_hcacheHandle);iotcon_query_destroy(hQuery));

	RUN_POLLING_LOOP;

	iotcon_query_destroy(hQuery);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_query_destroy", IotConGetError(nRet));

	//Put
	nRet = iotcon_representation_create(&hRepr);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_representation_create", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_remote_resource_destroy(g_hcacheHandle));
	CHECK_HANDLE(hRepr,"iotcon_representation_create");

	nRet = iotcon_remote_resource_put(g_hcacheHandle, hRepr, NULL, IotconPutChangedCB, NULL);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_put", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_remote_resource_destroy(g_hcacheHandle);iotcon_representation_destroy(hRepr));

	RUN_POLLING_LOOP;

	//post
	nRet = iotcon_remote_resource_post(g_hcacheHandle, hRepr, NULL, IotconPostChangedCB, NULL);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_post", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_remote_resource_destroy(g_hcacheHandle);iotcon_representation_destroy(hRepr));

	RUN_POLLING_LOOP;

	nRet = iotcon_representation_destroy(hRepr);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_representation_destroy", IotConGetError(nRet));

	//delete
	nRet = iotcon_remote_resource_delete(g_hcacheHandle, IotconDeleteChangedCB, NULL);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_post", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_remote_resource_destroy(g_hcacheHandle));

	RUN_POLLING_LOOP;

	nRet = iotcon_remote_resource_destroy(g_hcacheHandle);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_destroy", IotConGetError(nRet));

	if((g_bCheckCb == false) || (g_nGetCb == false) || (g_nPutCb == false) || (g_nPostCb == false) || (g_nDeleteCb == false))
	{
		FPRINTF("[Line : %d][%s] ITc_iotcon_remote_resource_get_put_post_delete_p callback not invoked: \\n", __LINE__, API_NAMESPACE );
		IotconDestroyLiteResource();
		return 1;
	}

	IotconDestroyLiteResource();

	return 0;
}
//& purpose: Creates a new query handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_remote_resource_start_stop_caching_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Creates a new query handle.
* @scenario				call iotcon_query_create
* @apicovered			iotcon_remote_resource_clone, iotcon_remote_resource_start_caching, iotcon_remote_resource_stop_caching	,iotcon_remote_resource_destroy
* @passcase				When iotcon_remote_resource_clone, iotcon_remote_resource_start_caching, iotcon_remote_resource_stop_caching are successful.
* @failcase				If target API iotcon_query_create or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/

int ITc_iotcon_remote_resource_start_stop_caching_p(void)
{
	START_TEST;
	int nIotconTimeoutId = 0;
	iotcon_query_h hQuery;

	int nRet = IotconCreateLiteResource();
    if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] IotconCreateLiteResource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		return 1;
	}
	g_bCheckCb = false;
	g_nRetcb = false;
	g_nCheckAPICb = 0;
	g_found = false;
	g_timeout_count = 0;

	while (g_timeout_count < TIMEOUT_COUNT_MAX && g_found == false) {
		nRet = iotcon_query_create(&hQuery);
		PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_create", IotConGetError(nRet));

		nRet = iotcon_query_set_resource_type(hQuery, LIGHT_RESOURCE_TYPE);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_query_set_resource_type", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_query_destroy(hQuery));

		nRet = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY, hQuery, IotconFindResourceCB, NULL);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_find_resource", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_query_destroy(hQuery));

		RUN_POLLING_LOOP;

		nRet = iotcon_query_destroy(hQuery);
		PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_query_destroy", IotConGetError(nRet));

		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, g_nCheckAPICb, "API call inside callback failed", IotConGetError(g_nCheckAPICb),IotconDestroyLiteResource());
	}

	if (g_hcacheHandle == NULL) {
		FPRINTF("[Line : %d][%s] Find resource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		IotconDestroyLiteResource();
		return 1;
	}

	if (g_found == false) {
		FPRINTF("[Line : %d][%s] Find resource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		iotcon_remote_resource_destroy(g_hcacheHandle);
		g_hcacheHandle = NULL;
		IotconDestroyLiteResource();
		return 1;
	}

	nRet = iotcon_remote_resource_start_caching(g_hcacheHandle, IotconCachingChangedCB, NULL);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_start_caching", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_remote_resource_destroy(g_hcacheHandle));

	Iotcon_update_lite_resource();

	RUN_POLLING_LOOP;

	nRet = iotcon_remote_resource_stop_caching(g_hcacheHandle);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_stop_caching", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_remote_resource_destroy(g_hcacheHandle));

	nRet = iotcon_remote_resource_destroy(g_hcacheHandle);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_destroy", IotConGetError(nRet));

	if((g_bCheckCb == false) || (g_nRetcb == false))
	{
		FPRINTF("[Line : %d][%s] IotconCachingChangedCB callback not invoked: \\n", __LINE__, API_NAMESPACE );
		iotcon_query_destroy(hQuery);
		IotconDestroyLiteResource();
		return 1;
	}

	IotconDestroyLiteResource();
	return 0;
}
//& purpose: Creates a new query handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_remote_resource_start_stop_monitoring_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Creates a new query handle.
* @scenario				call iotcon_query_create
* @apicovered			iotcon_remote_resource_clone, iotcon_remote_resource_start_monitoring ,iotcon_remote_resource_stop_monitoring,iotcon_remote_resource_destroy
* @passcase				When iotcon_remote_resource_clone, iotcon_remote_resource_start_monitoring ,iotcon_remote_resource_stop_monitoring are successful.
* @failcase				If target API iotcon_query_create or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_remote_resource_start_stop_monitoring_p(void)
{
	START_TEST;

	int nIotconTimeoutId = 0;
	iotcon_query_h hQuery;
	int nRet = IotconCreateResource();
    if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] IotconCreateRemoteResource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		return 1;
	}
	g_bCheckCb = false;
	g_nRetcb = false;
	g_nCheckAPICb = 0;
	g_found = false;
	g_timeout_count = 0;

	while (g_timeout_count < TIMEOUT_COUNT_MAX && g_found == false) {
		nRet = iotcon_query_create(&hQuery);
		PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_create", IotConGetError(nRet));

		nRet = iotcon_query_set_resource_type(hQuery, LIGHT_RESOURCE_TYPE);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_query_set_resource_type", IotConGetError(nRet),IotconDestroyResource();iotcon_query_destroy(hQuery));

		nRet = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY, hQuery, IotconFindResourceCB, NULL);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_find_resource", IotConGetError(nRet),IotconDestroyResource();iotcon_query_destroy(hQuery));

		RUN_POLLING_LOOP;

		nRet = iotcon_query_destroy(hQuery);
		PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_query_destroy", IotConGetError(nRet));

		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, g_nCheckAPICb, "API call inside callback failed", IotConGetError(g_nCheckAPICb),IotconDestroyResource());
	}

	if (g_hcacheHandle == NULL) {
		FPRINTF("[Line : %d][%s] Find resource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		IotconDestroyResource();
		return 1;
	}

	if (g_found == false) {
		FPRINTF("[Line : %d][%s] Find resource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		iotcon_remote_resource_destroy(g_hcacheHandle);
		g_hcacheHandle = NULL;
		IotconDestroyResource();
		return 1;
	}

	nRet = iotcon_remote_resource_start_monitoring(g_hcacheHandle, IotconMonitoringChangedCB,NULL);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_start_monitoring", IotConGetError(nRet),IotconDestroyResource();iotcon_remote_resource_destroy(g_hcacheHandle));

	IotconDestroyResource();

	RUN_POLLING_LOOP;

	nRet = iotcon_remote_resource_stop_monitoring(g_hcacheHandle);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_start_monitoring", IotConGetError(nRet),iotcon_remote_resource_destroy(g_hcacheHandle));

	nRet = iotcon_remote_resource_destroy(g_hcacheHandle);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_destroy", IotConGetError(nRet));

	if((g_bCheckCb == false) || (g_nRetcb == false))
	{
		FPRINTF("[Line : %d][%s] IotconMonitoringChangedCB callback not invoked: \\n", __LINE__, API_NAMESPACE );
		return 1;
	}

	return 0;
}

//& purpose: Creates a new query handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_remote_resource_get_connectivity_type_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Creates a new query handle.
* @scenario				call iotcon_remote_resource_get_connectivity_type
* @apicovered			iotcon_remote_resource_get_connectivity_type
* @passcase				When iotcon_remote_resource_get_connectivity_type is successful.
* @failcase				If target API iotcon_query_create or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/

int ITc_iotcon_remote_resource_get_connectivity_type_p(void)
{
	START_TEST;

	iotcon_connectivity_type_e connectivity_type;
	int nRet = IotconCreateRemoteResource();
    if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] IotconCreateRemoteResource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		return 1;
	}

	nRet = iotcon_remote_resource_get_connectivity_type(g_hClient, &connectivity_type);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_get_connectivity_type", IotConGetError(nRet), IotconDestroyRemoteResource());

    IotconDestroyRemoteResource();
	return 0;
}

//& purpose: Creates a new query handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_remote_resource_get_uri_path_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Creates a new query handle.
* @scenario				call iotcon_remote_resource_get_uri_path
* @apicovered			iotcon_remote_resource_get_uri_path
* @passcase				When iotcon_remote_resource_get_uri_path is successful.
* @failcase				If target API iotcon_query_create or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_remote_resource_get_uri_path_p(void)
{
	START_TEST;

	char *uri = NULL;

	int nRet = IotconCreateRemoteResource();
    if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] IotconCreateRemoteResource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		return 1;
	}
	nRet = iotcon_remote_resource_get_uri_path(g_hClient, &uri);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_get_uri_path", IotConGetError(nRet), IotconDestroyRemoteResource());
	CHECK_HANDLE(uri,"iotcon_remote_resource_get_uri_path");

	if (0 != strcmp(REMOTE_RESOURCE_LIGHT, uri))
	{
		FPRINTF("[Line : %d][%s] iotcon_remote_resource_get_uri_path failed uri path does not match \"%s\" \\n", __LINE__, API_NAMESPACE, REMOTE_RESOURCE_LED);
		IotconDestroyRemoteResource();
		return 1;
	}
    IotconDestroyRemoteResource();
	return 0;
}

//& purpose: Creates a new query handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_remote_resource_get_host_address_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Creates a new query handle.
* @scenario				call iotcon_remote_resource_get_host_address
* @apicovered			iotcon_remote_resource_get_host_address
* @passcase				When iotcon_remote_resource_get_host_address is successful.
* @failcase				If target API iotcon_remote_resource_get_host_address or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_remote_resource_get_host_address_p(void)
{
	START_TEST;

	char *host = NULL;

	int nRet = IotconCreateRemoteResource();
    if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] IotconCreateRemoteResource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		return 1;
	}
	nRet = iotcon_remote_resource_get_host_address(g_hClient, &host);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_get_host_address", IotConGetError(nRet), IotconDestroyRemoteResource());
	CHECK_HANDLE(host,"iotcon_remote_resource_get_host_address");

	if (0 != strcmp(REMOTE_IP, host))
	{
		FPRINTF("[Line : %d][%s] iotcon_remote_resource_get_host_address failed host address does not match. Remote Address: \"%s\" and Get received: %s\\n", __LINE__, API_NAMESPACE, REMOTE_IP, host);
		IotconDestroyRemoteResource();
		return 1;
	}
    IotconDestroyRemoteResource();
	return 0;
}

//& purpose: Creates a new query handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_remote_resource_get_device_id_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Creates a new query handle.
* @scenario				call iotcon_remote_resource_get_device_id
* @apicovered			iotcon_remote_resource_get_device_id
* @passcase				When iotcon_remote_resource_get_device_id is successful.
* @failcase				If target API iotcon_remote_resource_get_device_id or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_remote_resource_get_device_id_p(void)
{
	START_TEST;

    int nIotconTimeoutId = 0;
	char *sid;
	iotcon_query_h hQuery;
	g_bCheckCb = false;

    int nRet = IotconCreateLiteResource();
    if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] IotconCreateLiteResource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		return 1;
	}
	nRet = iotcon_query_create(&hQuery);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_create", IotConGetError(nRet));
		
	nRet = iotcon_query_set_resource_type(hQuery, LIGHT_RESOURCE_TYPE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_query_set_resource_type", IotConGetError(nRet),iotcon_query_destroy(hQuery));
	
	nRet = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY, hQuery, IotconRemoteResourceOptionsCB, NULL);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_find_resource", IotConGetError(nRet), IotconDestroyLiteResource();iotcon_query_destroy(hQuery););
	RUN_POLLING_LOOP;

	if(g_bCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] IotconRemoteResourceOptionsCB callback not invoked: \\n", __LINE__, API_NAMESPACE );
		iotcon_query_destroy(hQuery);
		IotconDestroyLiteResource();
		return 1;
	}

	nRet = iotcon_remote_resource_get_device_id(g_hResourceHandle, &sid);
	if(IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] iotcon_remote_resource_get_device_id failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		iotcon_query_destroy(hQuery);
		iotcon_remote_resource_destroy(g_hResourceHandle);
		IotconDestroyLiteResource();
		return 1;
	}
	CHECK_HANDLE(sid,"iotcon_remote_resource_get_device_id");
	
	iotcon_query_destroy(hQuery);
	iotcon_remote_resource_destroy(g_hResourceHandle);
	IotconDestroyLiteResource();
	return 0;
}


//& purpose: Creates a new query handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_remote_resource_get_types_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Creates a new query handle.
* @scenario				call iotcon_remote_resource_get_types
* @apicovered			iotcon_remote_resource_get_types
* @passcase				When iotcon_remote_resource_get_types is successful.
* @failcase				If target API iotcon_remote_resource_get_types or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_remote_resource_get_types_p(void)
{
	START_TEST;

	iotcon_resource_types_h hTypes = NULL;

	int nRet = IotconCreateRemoteResource();
    if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] IotconCreateRemoteResource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		return 1;
	}
	nRet = iotcon_remote_resource_get_types(g_hClient, &hTypes);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_get_host_address", IotConGetError(nRet), IotconDestroyRemoteResource());
	CHECK_HANDLE(hTypes, "iotcon_remote_resource_get_types");

	IotconDestroyRemoteResource();
	return 0;
}

//& purpose: Creates a new query handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_remote_resource_get_interfaces_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Creates a new query handle.
* @scenario				call iotcon_remote_resource_get_interfaces
* @apicovered			iotcon_remote_resource_get_interfaces
* @passcase				When iotcon_remote_resource_get_interfaces is successful.
* @failcase				If target API iotcon_remote_resource_get_interfaces or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_remote_resource_get_interfaces_p(void)
{
	START_TEST;

	iotcon_resource_interfaces_h ifaces;

	int nRet = IotconCreateRemoteResource();
    if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] IotconCreateRemoteResource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		return 1;
	}
	nRet = iotcon_remote_resource_get_interfaces(g_hClient, &ifaces);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_get_interfaces", IotConGetError(nRet), IotconDestroyRemoteResource());
    CHECK_HANDLE(ifaces, "iotcon_remote_resource_get_interfaces");

    IotconDestroyRemoteResource();
	return 0;
}

//& purpose: Creates a new query handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_remote_resource_get_properties_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Creates a new query handle.
* @scenario				call iotcon_remote_resource_get_properties
* @apicovered			iotcon_remote_resource_get_properties
* @passcase				When iotcon_remote_resource_get_properties is successful.
* @failcase				If target API iotcon_remote_resource_get_properties or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_remote_resource_get_policies_p(void)
{
	START_TEST;

	uint8_t properties;

	int nRet = IotconCreateRemoteResource();
    if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] IotconCreateRemoteResource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		return 1;
	}
	nRet = iotcon_remote_resource_get_policies(g_hClient, &properties);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_get_policies", IotConGetError(nRet), IotconDestroyRemoteResource());

	if (false == (IOTCON_RESOURCE_OBSERVABLE & properties))
	{
		FPRINTF("[Line : %d][%s] iotcon_remote_resource_get_policies failed\\n", __LINE__, API_NAMESPACE);
		IotconDestroyRemoteResource();
		return 1;
	}
    IotconDestroyRemoteResource();
	return 0;
}

//& purpose: Creates a new query handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_remote_resource_set_get_options_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Creates a new query handle.
* @scenario				call iotcon_remote_resource_set_options , iotcon_remote_resource_get_options
* @apicovered			iotcon_remote_resource_set_options,iotcon_options_create,	iotcon_options_add,		iotcon_remote_resource_set_options	,iotcon_remote_resource_get_options
* @passcase				When iotcon_remote_resource_set_options,iotcon_options_create,	iotcon_options_add,		iotcon_remote_resource_set_options	,iotcon_remote_resource_get_options are successful.
* @failcase				If target API  or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_remote_resource_set_get_options_p(void)
{
	START_TEST;

	int nIotconTimeoutId = 0;
	iotcon_query_h hQuery;
	iotcon_options_h hSetOptions = NULL;
	iotcon_options_h hGetOptions;

	int nRet = IotconCreateLiteResource();
    if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] IotconCreateLiteResource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		return 1;
	}
	g_bCheckCb = false;

	nRet = iotcon_query_create(&hQuery);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_create", IotConGetError(nRet));
		
	nRet = iotcon_query_set_resource_type(hQuery, LIGHT_RESOURCE_TYPE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_query_set_resource_type", IotConGetError(nRet),iotcon_query_destroy(hQuery));
	
	nRet = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY, hQuery,IotconRemoteResourceOptionsCB, NULL);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_find_resource", IotConGetError(nRet), IotconDestroyLiteResource(); iotcon_query_destroy(hQuery));
	RUN_POLLING_LOOP;

	if(g_bCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] IotconRemoteResourceOptionsCB callback not invoked: \\n", __LINE__, API_NAMESPACE );
		iotcon_query_destroy(hQuery);
		IotconDestroyLiteResource();
		return 1;
	}
	/* options may be NULL */
	nRet = iotcon_remote_resource_set_options(g_hResourceHandle, NULL);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_set_options", IotConGetError(nRet), iotcon_remote_resource_destroy(g_hResourceHandle);IotconDestroyLiteResource();iotcon_query_destroy(hQuery));

	nRet = iotcon_options_create(&hSetOptions);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_options_create", IotConGetError(nRet), iotcon_remote_resource_destroy(g_hResourceHandle);IotconDestroyLiteResource();	iotcon_query_destroy(hQuery));
	CHECK_HANDLE(hSetOptions,"iotcon_options_create");

	nRet = iotcon_options_add(hSetOptions, 2500, "options_value");
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_options_add", IotConGetError(nRet), iotcon_options_destroy(hSetOptions);iotcon_remote_resource_destroy(g_hResourceHandle);IotconDestroyLiteResource();iotcon_query_destroy(hQuery));

	nRet = iotcon_remote_resource_set_options(g_hResourceHandle, hSetOptions);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_set_options", IotConGetError(nRet), iotcon_options_destroy(hSetOptions);iotcon_remote_resource_destroy(g_hResourceHandle);IotconDestroyLiteResource();iotcon_query_destroy(hQuery));

	nRet = iotcon_remote_resource_get_options(g_hResourceHandle, &hGetOptions);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_get_options", IotConGetError(nRet), iotcon_options_destroy(hSetOptions);iotcon_remote_resource_destroy(g_hResourceHandle);IotconDestroyLiteResource();iotcon_query_destroy(hQuery));
	CHECK_HANDLE(hGetOptions,"iotcon_remote_resource_get_options");

	iotcon_query_destroy(hQuery);
	iotcon_remote_resource_destroy(g_hResourceHandle);
	IotconDestroyLiteResource();
	iotcon_options_destroy(hSetOptions);

	return 0;
}

//& purpose: Creates a new query handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_remote_resource_get_cached_representation_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Creates a new query handle.
* @scenario				call iotcon_query_create
* @apicovered			iotcon_remote_resource_clone,iotcon_remote_resource_start_caching,	iotcon_state_create,iotcon_state_add_int,iotcon_lite_resource_update_state,iotcon_remote_resource_get_cached_representation
* @passcase				When iotcon_remote_resource_clone,iotcon_remote_resource_start_caching,	iotcon_state_create,iotcon_state_add_int,iotcon_lite_resource_update_state,iotcon_remote_resource_get_cached_representation	are successful.
* @failcase				If target API or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_remote_resource_get_cached_representation_p(void)
{
	START_TEST;
	int nIotconTimeoutId = 0;
	iotcon_query_h hQuery;
	int nRet = IotconCreateLiteResource();
    if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] IotconCreateLiteResource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		return 1;
	}
	g_bCheckCb = false;
	g_nRetcb = false;
	g_nCheckAPICb = 0;
	g_found = false;
	g_timeout_count = 0;

	while (g_timeout_count < TIMEOUT_COUNT_MAX && g_found == false) {
		nRet = iotcon_query_create(&hQuery);
		PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_create", IotConGetError(nRet));

		nRet = iotcon_query_set_resource_type(hQuery, LIGHT_RESOURCE_TYPE);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_query_set_resource_type", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_query_destroy(hQuery));

		nRet = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY, hQuery, IotconFindResourceCB, NULL);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_find_resource", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_query_destroy(hQuery));

		RUN_POLLING_LOOP;

		nRet = iotcon_query_destroy(hQuery);
		PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_query_destroy", IotConGetError(nRet));

		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, g_nCheckAPICb, "API call inside callback failed", IotConGetError(g_nCheckAPICb),IotconDestroyLiteResource());
	}

	if (g_hcacheHandle == NULL) {
		FPRINTF("[Line : %d][%s] Find resource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		IotconDestroyLiteResource();
		return 1;
	}

	if (g_found == false) {
		FPRINTF("[Line : %d][%s] Find resource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		iotcon_remote_resource_destroy(g_hcacheHandle);
		g_hcacheHandle = NULL;
		IotconDestroyLiteResource();
		return 1;
	}

	nRet = iotcon_remote_resource_start_caching(g_hcacheHandle, IotconRepresentationChangedCB, NULL);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_start_caching", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_remote_resource_destroy(g_hcacheHandle));

	Iotcon_update_lite_resource();
	RUN_POLLING_LOOP;

	nRet = iotcon_remote_resource_stop_caching(g_hcacheHandle);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_stop_caching", IotConGetError(nRet),IotconDestroyLiteResource();iotcon_remote_resource_destroy(g_hcacheHandle));

	nRet = iotcon_remote_resource_destroy(g_hcacheHandle);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_destroy", IotConGetError(nRet));

	if((g_bCheckCb == false) || (g_nRetcb == false))
	{
		FPRINTF("[Line : %d][%s] IotconRepresentationChangedCB callback not invoked: \\n", __LINE__, API_NAMESPACE );
		IotconDestroyLiteResource();
		return 1;
	}

	IotconDestroyLiteResource();

	return 0;
}

//& purpose: Creates a new query handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_remote_resource_set_get_checking_interval_p
* @since_tizen			3.0
* @author             	SRID(manu.tiwari)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Sets and Gets the time interval of monitoring & caching API of remote resource.
* @scenario				call iotcon_remote_resource_get_time_interval, iotcon_remote_resource_set_time_interval
* @apicovered			iotcon_remote_resource_get_time_interval,iotcon_remote_resource_set_time_interval
* @passcase				When iotcon_remote_resource_get_time_interval,iotcon_remote_resource_set_time_interval are successful.
* @failcase				If target API or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_remote_resource_set_get_checking_interval_p(void)
{
	START_TEST;

	int SetTimeInterval = 250;
	int GetTimeInterval = 0;
	int nRet = IotconCreateRemoteResource();
    if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] IotconCreateRemoteResource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		return 1;
	}
	
	nRet = iotcon_remote_resource_set_checking_interval(g_hClient, SetTimeInterval);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_set_checking_interval", IotConGetError(nRet));

	nRet = iotcon_remote_resource_get_checking_interval(g_hClient, &GetTimeInterval);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_get_checking_interval", IotConGetError(nRet));

	if (SetTimeInterval != GetTimeInterval)
	{
		FPRINTF("[Line : %d][%s] iotcon_remote_resource_set_checking_interval and iotcon_remote_resource_get_checking_interval does not match\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}
//& purpose: CrGets the device name.
//& type: auto
/**
* @testcase   			ITc_remote_resource_get_device_name_p
* @since_tizen			3.0
* @author             	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			 Gets the device name API of remote resource.
* @scenario				call iotcon_remote_resource_get_device_name
* @apicovered			iotcon_remote_resource_get_device_name,iotcon_remote_resource_destroy
* @passcase				When iotcon_remote_resource_get_device_name is successful.
* @failcase				If target API or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_remote_resource_get_device_name_p(void)
{
	START_TEST;

	char *pszDeviceName =NULL;
	int nIotconTimeoutId = 0;
	iotcon_query_h hQuery;

	g_bCheckCb = false;

    int nRet = IotconCreateLiteResource();
    if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] IotconCreateLiteResource failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		return 1;
	}
	nRet = iotcon_query_create(&hQuery);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_create", IotConGetError(nRet));
	nRet = iotcon_query_set_resource_type(hQuery, LIGHT_RESOURCE_TYPE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_query_set_resource_type", IotConGetError(nRet),iotcon_query_destroy(hQuery));
	
	nRet = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY, hQuery,IotconRemoteResourceOptionsCB, NULL);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_find_resource", IotConGetError(nRet), IotconDestroyLiteResource();iotcon_query_destroy(hQuery));
	RUN_POLLING_LOOP;

	if(g_bCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] IotconRemoteResourceOptionsCB callback not invoked: \\n", __LINE__, API_NAMESPACE );
		iotcon_query_destroy(hQuery);
		IotconDestroyLiteResource();
		return 1;
	}


	nRet = iotcon_remote_resource_get_device_name(g_hResourceHandle, &pszDeviceName);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_get_device_name", IotConGetError(nRet), IotconDestroyLiteResource();iotcon_remote_resource_destroy(g_hResourceHandle);iotcon_query_destroy(hQuery));
	if(pszDeviceName == NULL)
	{
		FPRINTF("[Line : %d][%s] iotcon_remote_resource_get_device_name failed : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		iotcon_query_destroy(hQuery);
		iotcon_remote_resource_destroy(g_hResourceHandle);
		IotconDestroyLiteResource();
		return 1;

	}
	iotcon_query_destroy(hQuery);
	iotcon_remote_resource_destroy(g_hResourceHandle);
	IotconDestroyLiteResource();


	return 0;
}




/** @} */
/** @} */
