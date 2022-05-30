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

iotcon_request_h g_hRequest = NULL;
static bool g_bRequestHandlerCB = false;
static bool g_bResult;
static iotcon_resource_h g_hLightResource;
static iotcon_remote_resource_h g_hRemoteResource;
static int g_timeout_count;
static bool g_found;

enum {
	REQUEST_GET_QUERY,
	REQUEST_GET_HOST_ADDRESS,
	REQUEST_GET_CONNECTIVITY_TYPE,
	REQUEST_GET_REPRESENTATION,
	REQUEST_GET_REQUEST_TYPE,
	REQUEST_GET_OPTIONS,
	REQUEST_GET_OBSERVE_TYPE,
	REQUEST_GET_OBSERVE_ID,
};

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
    if ( Handle == NULL )\
    {\
        FPRINTF("[Line: %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
        FreeResource;\
        return 1;\
    }\
}

/**
 * @function 		gmain_loop_quit_idle
 * @description	 	Called if some callback is not invoked for a particular timeout
 * @parameter		gpointer data
 * @return 			gboolean
 */
static gboolean gmain_loop_quit_idle(gpointer p)
{

	g_main_loop_quit(g_pMainLoop);
	g_main_loop_unref(g_pMainLoop);
	g_pMainLoop = NULL;
	return G_SOURCE_REMOVE;
}

/**
* @function 		QuitGmainLoopIdle
* @description	 	Called to quit
* @parameter		NA
* @return 			NA
*/
static void QuitGmainLoopIdle(bool result)
{
	g_bResult = result;
	g_idle_add(gmain_loop_quit_idle, NULL);
}

/**
* @function 		RequestHandlerCB
* @description	 	Called when create iotcon resource to get request handle
* @parameter		iotcon_resource_h : The resource handle, iotcon_request_h : The request handle
*					user_data : The user data passed from function
* @return 			NA
*/
static void RequestHandlerCB(iotcon_resource_h resource, iotcon_request_h request,
		void *user_data)
{
    FPRINTF("Inside RequestHandlerCB callback... \n");
	int nRet;
	int tc_index = GPOINTER_TO_INT(user_data);
	iotcon_query_h hQuery = NULL;
	char *pcHostAddress = NULL;
    iotcon_connectivity_type_e eType = -1;
	iotcon_representation_h hRep = NULL;
	iotcon_request_type_e eRequestType = -1;
	iotcon_options_h hOptions = NULL;
	iotcon_options_h hGetOptions = NULL;
	iotcon_response_h hResponse;
	iotcon_observe_type_e eObserveType = -1;
	int nObserveId = -1;
	g_bRequestHandlerCB = true;

	if(request == NULL)
	{
		FPRINTF("Handle iotcon_request_h is null in RequestHandlerCB callback... \n");
		return;
	}
	switch (tc_index)
	{
		case REQUEST_GET_QUERY:
			nRet = iotcon_request_get_query(request, &hQuery);
			if (IOTCON_ERROR_NONE != nRet) {
				FPRINTF("[Line : %d][%s] iotcon_request_get_query fail error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				QuitGmainLoopIdle(false);
			}
			if(hQuery == NULL)
			{
				FPRINTF("[Line : %d][%s] hQuery handle NULL : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				QuitGmainLoopIdle(false);
			}
			QuitGmainLoopIdle(true);
			return;
		case REQUEST_GET_HOST_ADDRESS:
			nRet = iotcon_request_get_host_address(request, &pcHostAddress);
			if (IOTCON_ERROR_NONE != nRet)
			{
				FPRINTF("[Line : %d][%s] iotcon_request_get_host_address fail error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				QuitGmainLoopIdle(false);
			}
			if(pcHostAddress == NULL)
			{
				FPRINTF("[Line : %d][%s] pcHostAddress handle NULL : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				QuitGmainLoopIdle(false);
			}
			QuitGmainLoopIdle(true);
			return;
		case REQUEST_GET_CONNECTIVITY_TYPE:
			nRet = iotcon_request_get_connectivity_type(request, &eType);
			if (IOTCON_ERROR_NONE != nRet)
			{
				FPRINTF("[Line : %d][%s] iotcon_request_get_connectivity_type fail error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				QuitGmainLoopIdle(false);
			}
			if(eType == -1)
			{
				FPRINTF("enum not initialized [iotcon_connectivity_type_e] failed \n");
				QuitGmainLoopIdle(false);
			}
			QuitGmainLoopIdle(true);
			return;
		case REQUEST_GET_REPRESENTATION:
			nRet = iotcon_request_get_representation(request, &hRep);
			if (IOTCON_ERROR_NONE != nRet)
			{
				FPRINTF("[Line : %d][%s] iotcon_request_get_representation fail error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				QuitGmainLoopIdle(false);
			}
			if(hRep == NULL)
			{
				FPRINTF("[Line : %d][%s] hRep handle NULL : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				QuitGmainLoopIdle(false);
			}
		    QuitGmainLoopIdle(true);
			return;
		case REQUEST_GET_REQUEST_TYPE:
			nRet = iotcon_request_get_request_type(request, &eRequestType);
			if (IOTCON_ERROR_NONE != nRet)
			{
				FPRINTF("[Line : %d][%s] iotcon_request_get_request_type fail error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				QuitGmainLoopIdle(false);
			}
			if(eRequestType == -1)
			{
				FPRINTF("[Line : %d][%s] enum not set : \\n", __LINE__, API_NAMESPACE );
				QuitGmainLoopIdle(false);
			}
			QuitGmainLoopIdle(true);
			return;
		case REQUEST_GET_OPTIONS:
			nRet = iotcon_response_create(request, &hResponse);
			if (IOTCON_ERROR_NONE != nRet)
			{
				FPRINTF("[Line : %d][%s] iotcon_response_create fail error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				QuitGmainLoopIdle(false);
			}
			if(hResponse == NULL)
			{
				FPRINTF("[Line : %d][%s] hResponse handle NULL : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				QuitGmainLoopIdle(false);
			}
			nRet = iotcon_options_create(&hOptions);
			if (IOTCON_ERROR_NONE != nRet)
			{
				FPRINTF("[Line : %d][%s] iotcon_options_create fail error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				iotcon_response_destroy(hResponse);
				QuitGmainLoopIdle(false);
			}
			if(hOptions == NULL)
			{
				FPRINTF("[Line : %d][%s] hOptions handle NULL : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				iotcon_response_destroy(hResponse);
				QuitGmainLoopIdle(false);
			}
			nRet = iotcon_request_get_options(request, &hGetOptions);
			if (IOTCON_ERROR_NONE != nRet)
			{
				FPRINTF("[Line : %d][%s] iotcon_request_get_options fail error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				iotcon_options_destroy(hOptions);
				iotcon_response_destroy(hResponse);
				QuitGmainLoopIdle(false);
			}
			if(hGetOptions == NULL)
			{
				FPRINTF("[Line : %d][%s] hGetOptions handle NULL : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				iotcon_response_destroy(hResponse);
				QuitGmainLoopIdle(false);
			}
			iotcon_options_destroy(hOptions);
			iotcon_response_destroy(hResponse);
			QuitGmainLoopIdle(true);
			return;
		case REQUEST_GET_OBSERVE_TYPE:
			nRet = iotcon_request_get_observe_type(request, &eObserveType);
			if (IOTCON_ERROR_NONE != nRet)
			{
				FPRINTF("[Line : %d][%s] iotcon_request_get_observe_type fail error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				QuitGmainLoopIdle(false);
			}
			if(eObserveType == -1)
			{
				FPRINTF("[Line : %d][%s] value not set : \\n", __LINE__, API_NAMESPACE );
				QuitGmainLoopIdle(false);
			}
            QuitGmainLoopIdle(true);
			return;
		case REQUEST_GET_OBSERVE_ID:
			nRet = iotcon_request_get_observe_id(request, &nObserveId);
			if (IOTCON_ERROR_NONE != nRet)
			{
				FPRINTF("[Line : %d][%s] iotcon_request_get_observe_id fail error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				QuitGmainLoopIdle(false);
			}
			if(nObserveId == -1)
			{
				FPRINTF("[Line : %d][%s] value not set : \\n", __LINE__, API_NAMESPACE );
				QuitGmainLoopIdle(false);
			}
			QuitGmainLoopIdle(true);
			return;
		default:
			FPRINTF("[Line : %d][%s] Invalid tc_index(%d) ", __LINE__, API_NAMESPACE,tc_index);
			QuitGmainLoopIdle(false);
			return;
	}
}

/**
* @function 		CreateResource
* @description	 	Called to create and add resource and interface.
* @parameter		NA
* @return 			intiger : 0 if sussess
*/
static int CreateResource(int tc_index)
{
    FPRINTF("Inside CreateResource... \n");
	int nRet;
	//int nIotconTimeoutId = 0;
	iotcon_resource_types_h hLightTypes;
	iotcon_resource_interfaces_h hLightiFaces;

	nRet = iotcon_resource_types_create(&hLightTypes);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_create", IotConGetError(nRet));

	nRet = iotcon_resource_types_add(hLightTypes, LIGHT_RESOURCE_TYPE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_add", IotConGetError(nRet),iotcon_resource_types_destroy(hLightTypes));

	nRet = iotcon_resource_interfaces_create(&hLightiFaces);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_create", IotConGetError(nRet),iotcon_resource_types_destroy(hLightTypes));

	nRet = iotcon_resource_interfaces_add(hLightiFaces, IOTCON_INTERFACE_DEFAULT);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_add", IotConGetError(nRet),iotcon_resource_interfaces_destroy(hLightiFaces);iotcon_resource_types_destroy(hLightTypes));

	nRet = iotcon_resource_interfaces_add(hLightiFaces, IOTCON_INTERFACE_BATCH);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_add", IotConGetError(nRet),iotcon_resource_interfaces_destroy(hLightiFaces);iotcon_resource_types_destroy(hLightTypes));
	nRet = iotcon_resource_create(LIGHT_RESOURCE_URI,
			hLightTypes,
			hLightiFaces,
			(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),
			RequestHandlerCB,
			GINT_TO_POINTER(tc_index),
			&g_hLightResource);
	//RUN_POLLING_LOOP;
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_create", IotConGetError(nRet),iotcon_resource_interfaces_destroy(hLightiFaces);iotcon_resource_types_destroy(hLightTypes));

	iotcon_resource_interfaces_destroy(hLightiFaces);
	iotcon_resource_types_destroy(hLightTypes);

	return 0;
}

/**
* @function 		GetRemoteResourceCB
* @description	 	Called to get remote resource
* @parameter		iotcon_remote_resource_h : The remote resource handle, iotcon_request_h : The request handle
*					iotcon_error_e : iotcon error	user_data : The user data passed from function
* @return 			NA
*/
static void GetRemoteResourceCB(iotcon_remote_resource_h resource,	iotcon_error_e err,
		iotcon_request_type_e request_type, iotcon_response_h response, void *user_data)
{
    FPRINTF("Inside GetRemoteResourceCB callback... \n");
	g_bRequestHandlerCB = true;
	QuitGmainLoopIdle(true);

	return;
}

/**
* @function 		FoundResourceCB
* @description	 	get remote resource clone
* @parameter		iotcon_remote_resource_h : The remote resource handle, iotcon_error_e : iotcon error
*					user_data : The user data passed from function
* @return 			NA
*/
static bool FoundResourceCB(iotcon_remote_resource_h resource,
		iotcon_error_e err, void *user_data)
{
	FPRINTF("Inside FoundResourceCB callback... \n");
	//int nIotconTimeoutId = 0;
	int nRet;
	g_bRequestHandlerCB = true;
    iotcon_query_h hquery;
	iotcon_query_h query;
	iotcon_options_h hoptions;

	if (IOTCON_ERROR_TIMEOUT == err && g_timeout_count < TIMEOUT_COUNT_MAX)
	{
		g_timeout_count++;
		nRet = iotcon_query_create(&query);
		if (IOTCON_ERROR_NONE != nRet)
		{
			FPRINTF("[Line : %d][%s] iotcon_query_create fail error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
			return false;
		}
		nRet = iotcon_query_set_resource_type(query, LIGHT_RESOURCE_TYPE);
		if (IOTCON_ERROR_NONE != nRet) 
		{
			FPRINTF("[Line : %d][%s] iotcon_query_set_resource_type fail error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
			iotcon_query_destroy(query);
			return false;
		}
		nRet = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY,
				query, FoundResourceCB, NULL);
		if (IOTCON_ERROR_NONE != nRet)
		{
			FPRINTF("[Line : %d][%s] iotcon_find_resource fail in startup error returned : %s\\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
			iotcon_query_destroy(query);
			QuitGmainLoopIdle(false);
			return false;
		}
		nRet = iotcon_query_destroy(query);
		if (IOTCON_ERROR_NONE != nRet)
		{
			FPRINTF("[Line : %d][%s] iotcon_query_destroy fail error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
			return false;
		}
		return false;
	}
	else if (IOTCON_ERROR_NONE != err)
	{
		QuitGmainLoopIdle(false);
		return false;
	}

	if (g_found)
		return false;

	g_found = true;

	char *host_address, *uri;
	iotcon_remote_resource_get_host_address(resource, &host_address);
	iotcon_remote_resource_get_uri_path(resource, &uri);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] host_address[%s], uri[%s]", __FUNCTION__, __LINE__, host_address, uri);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] expected host_address[%s], found host_address[%s]", __FUNCTION__, __LINE__, g_ipv4_address, host_address);
	if (strstr(host_address, g_ipv4_address) == NULL) { // targeted resource, BUT wrong device, so skip this resource and try again
		g_found = false;
		return true;
	}

	nRet = iotcon_remote_resource_clone(resource, &g_hRemoteResource);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_remote_resource_clone() Fail(%d)", nRet);
		QuitGmainLoopIdle(false);
		return false;
	}
	nRet = iotcon_query_create(&hquery);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_query_create() Fail(%d)", nRet);
		QuitGmainLoopIdle(false);
		return false;
	}
	nRet = iotcon_query_add(hquery, "key", "value");
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_query_add() Fail(%d)", nRet);
		iotcon_query_destroy(hquery);
		QuitGmainLoopIdle(false);
		return false;
	}
    /* Add options */
	nRet = iotcon_options_create(&hoptions);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_options_create() Fail(%d)", nRet);
		iotcon_query_destroy(hquery);
		QuitGmainLoopIdle(false);
		return false;
	}

	nRet = iotcon_options_add(hoptions, 2048, "data");
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_options_add() Fail(%d)", nRet);
		iotcon_query_destroy(hquery);
		iotcon_options_destroy(hoptions);
		QuitGmainLoopIdle(false);
		return false;
	}
	nRet = iotcon_remote_resource_set_options(g_hRemoteResource, hoptions);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_remote_resource_set_options() Fail(%d)", nRet);
		iotcon_query_destroy(hquery);
		iotcon_options_destroy(hoptions);
		QuitGmainLoopIdle(false);
		return false;
	}
	iotcon_options_destroy(hoptions);
	nRet = iotcon_remote_resource_get(g_hRemoteResource, hquery, GetRemoteResourceCB, NULL);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_remote_resource_clone() Fail(%d)", nRet);
		iotcon_query_destroy(hquery);
		QuitGmainLoopIdle(false);
		return false;
	}
	//RUN_POLLING_LOOP;
	iotcon_query_destroy(hquery);
	return false;
}

/**
* @function 		CreateAndFindResource
* @description	 	Function to create and find resource
* @parameter		NA
* @return 			intiger : 0 if sussess
*/
static int CreateAndFindResource(int tc_index)
{
	FPRINTF("[Line : %d][%s] Inside : CreateAndFindResource !!!\\n", __LINE__, API_NAMESPACE);
	int nRet;
	iotcon_query_h hQuery;
	g_pMainLoop = g_main_loop_new(NULL, FALSE);
	g_bRequestHandlerCB = false;

	nRet = CreateResource(tc_index);
	if (nRet == 1) {
		FPRINTF("[Line : %d][%s] CreateResource() \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	nRet = iotcon_query_create(&hQuery);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_create", IotConGetError(nRet));
		
	nRet = iotcon_query_set_resource_type(hQuery, LIGHT_RESOURCE_TYPE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_query_set_resource_type", IotConGetError(nRet),iotcon_query_destroy(hQuery));

	nRet = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY,
			hQuery, FoundResourceCB, NULL);
	if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("iotcon_find_resource() Fail(%d)", nRet);
		iotcon_query_destroy(hQuery);
		return 1;
	}
	nRet = iotcon_query_destroy(hQuery);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_query_destroy", IotConGetError(nRet));

	if(g_pMainLoop)
	{
		g_main_loop_run(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}

	if(g_bRequestHandlerCB != true)
	{
		FPRINTF("[Line : %d][%s] CreateAndFindResource failed... \\n", __LINE__, API_NAMESPACE);
		return 1;
	}else
		return 0;
}

/**
 * @function 		ITs_iotcon_request_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_request_startup(void)
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
 * @function 		ITs_iotcon_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_request_cleanup(void)
{
	icitc_free_client_ipv4_address();

	if (g_hRemoteResource) {
		iotcon_remote_resource_destroy(g_hRemoteResource);
		g_hRemoteResource = NULL;
	}
	if (g_hLightResource) {
		iotcon_resource_destroy(g_hLightResource);
		g_hLightResource = NULL;
	}
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


//& type: auto
//& purpose:  scenario to get query resource in iotcon iotcon.
/**
* @testcase   			ITc_iotcon_request_get_query_p
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get query resource in iotcon iotcon.
* @scenario				get query \n
* @apicovered			iotcon_request_get_query
* @passcase				If iotcon_request_get_query passes.
* @failcase				If iotcon_request_get_query fails.
* @precondition			get query
* @postcondition		NA
*/
int ITc_iotcon_request_get_query_p(void)
{
	START_TEST;

	int nRet = CreateAndFindResource(REQUEST_GET_QUERY);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateAndFindResource", IotConGetError(nRet));

	return 0;
}
//& type: auto
//& purpose:  scenario to get host address in iotcon request.
/**
* @testcase   			ITc_iotcon_request_get_host_address_p
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get host address in iotcon request.
* @scenario				get host address \n
* @apicovered			iotcon_request_get_host_address
* @passcase				If iotcon_request_get_host_address passes.
* @failcase				If iotcon_request_get_host_address fails.
* @precondition			create device
* @postcondition		NA
*/
int ITc_iotcon_request_get_host_address_p(void)
{
	START_TEST;
	int nRet = CreateAndFindResource(REQUEST_GET_HOST_ADDRESS);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateAndFindResource", IotConGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  scenario to get connectivity type in iotcon request.
/**
* @testcase   			ITc_iotcon_request_get_connectivity_type_p
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get connectivity type in iotcon request.
* @scenario				connectivity type \n
* @apicovered			iotcon_request_get_connectivity_type
* @passcase				If iotcon_request_get_connectivity_type passes.
* @failcase				If iotcon_request_get_connectivity_type fails.
* @precondition			create device
* @postcondition		NA
*/
int ITc_iotcon_request_get_connectivity_type_p(void)
{
	START_TEST;
	int nRet = CreateAndFindResource(REQUEST_GET_CONNECTIVITY_TYPE);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateAndFindResource", IotConGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  scenario to get representation in iotcon iotcon.
/**
* @testcase   			ITc_iotcon_request_get_representation_p
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get representation in iotcon iotcon.
* @scenario				get representation \n
* @apicovered			iotcon_request_get_representation
* @passcase				If iotcon_request_get_representation passes.
* @failcase				If iotcon_request_get_representation fails.
* @precondition			create device
* @postcondition		NA
*/
int ITc_iotcon_request_get_representation_p(void)
{
	START_TEST;
	int nRet = CreateAndFindResource(REQUEST_GET_REPRESENTATION);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateAndFindResource", IotConGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  scenario to get request type in iotcon iotcon.
/**
* @testcase   			ITc_iotcon_request_get_request_type_p
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get request type in iotcon iotcon.
* @scenario				get request type \n
* @apicovered			iotcon_request_get_request_type
* @passcase				If iotcon_request_get_request_type passes.
* @failcase				If iotcon_request_get_request_type fails.
* @precondition			get request type
* @postcondition		NA
*/
int ITc_iotcon_request_get_request_type_p(void)
{
	START_TEST;
	int nRet = CreateAndFindResource(REQUEST_GET_REQUEST_TYPE);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateAndFindResource", IotConGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  scenario to get option in iotcon request.
/**
* @testcase   			ITc_iotcon_request_get_options_p
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get option in iotcon request.
* @scenario				get option \n
* @apicovered			iotcon_request_get_options
* @passcase				If iotcon_request_get_options passes.
* @failcase				If iotcon_request_get_options fails.
* @precondition			get option
* @postcondition		NA
*/
int ITc_iotcon_request_get_options_p(void)
{
	START_TEST;
	int nRet = CreateAndFindResource(REQUEST_GET_OPTIONS);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateAndFindResource", IotConGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  scenario to get observe type in iotcon request.
/**
* @testcase   			ITc_iotcon_request_get_observe_type_p
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get observe type in iotcon request.
* @scenario				get observe type \n
* @apicovered			iotcon_request_get_observe_type
* @passcase				If iotcon_request_get_observe_type passes.
* @failcase				If iotcon_request_get_observe_type fails.
* @precondition			get observe type
* @postcondition		NA
*/
int ITc_iotcon_request_get_observe_type_p(void)
{
	START_TEST;
	int nRet = CreateAndFindResource(REQUEST_GET_OBSERVE_TYPE);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateAndFindResource", IotConGetError(nRet));

	return 0;
}
//& type: auto
//& purpose:  scenario to get observe id in iotcon request.
/**
* @testcase   			ITc_iotcon_request_get_observe_id_p
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get observe id in iotcon request.
* @scenario				get observe id \n
* @apicovered			iotcon_request_get_observe_id
* @passcase				If iotcon_request_get_observe_id passes.
* @failcase				If iotcon_request_get_observe_id fails.
* @precondition			get observe id
* @postcondition		NA
*/
int ITc_iotcon_request_get_observe_id_p(void)
{
	START_TEST;
	int nRet = CreateAndFindResource(REQUEST_GET_OBSERVE_ID);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateAndFindResource", IotConGetError(nRet));

	return 0;
}

/** @} */
/** @} */
