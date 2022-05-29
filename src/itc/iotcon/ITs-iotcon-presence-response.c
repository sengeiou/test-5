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
#include "assert.h"
#include <glib.h>
#include <system_info.h>
#include <iotcon.h>
#include "ITs-iotcon-common.h"
#define PRESENCE_INTERVAL 10
//& set: Iotcon

static int g_timeout_count;
//static bool g_feature;
static bool g_found;
static bool g_bResult;
static GMainLoop *g_loop;
static iotcon_resource_h g_light_resource;
static iotcon_presence_h g_presence;
static bool g_bCallbackHit = false;
static int g_nRet;


enum {
	PRESENCE_RESPONSE_GET_CONNECTIVITY_TYPE,
	PRESENCE_RESPONSE_GET_HOST_ADDRESS,
	PRESENCE_RESPONSE_GET_RESOURCE_TYPE,
	PRESENCE_RESPONSE_GET_RESULT,
	PRESENCE_RESPONSE_GET_TRIGGER,
	ADD_REMOVE_PRESENCE_CB,
};



/**
 * @function 		PresenceResponsePresenceCB
 * @description	 	callback function
 * @parameter		iotcon_presence_h presence,iotcon_error_e err, iotcon_presence_response_h response, void *user_data
 * @return 			void
 */
static void RequestHandlerCB(iotcon_resource_h resource, iotcon_request_h request,void *user_data)
{

}

/**
 * @function 		CreateResource
 * @description	 	function
 * @parameter		int tc_index
 * @return 			int
 */
static int CreateResource(int tc_index)
{
	int nRet;
	iotcon_resource_types_h light_types;
	iotcon_resource_interfaces_h light_ifaces;

	nRet = iotcon_resource_types_create(&light_types);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_create", IotConGetError(nRet));
	CHECK_HANDLE(light_types,"iotcon_resource_types_create");

	nRet = iotcon_resource_types_add(light_types, LIGHT_RESOURCE_TYPE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_add", IotConGetError(nRet),iotcon_resource_types_destroy(light_types));

	nRet = iotcon_resource_interfaces_create(&light_ifaces);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_create", IotConGetError(nRet),iotcon_resource_types_destroy(light_types));
	CHECK_HANDLE_CLEANUP(light_ifaces,"iotcon_resource_interfaces_create",iotcon_resource_types_destroy(light_types));

	nRet = iotcon_resource_interfaces_add(light_ifaces, IOTCON_INTERFACE_DEFAULT);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_add", IotConGetError(nRet),iotcon_resource_interfaces_destroy(light_ifaces);iotcon_resource_types_destroy(light_types));

	nRet = iotcon_resource_create(LIGHT_RESOURCE_URI,light_types,light_ifaces,(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),RequestHandlerCB,	(void *)tc_index,&g_light_resource);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_create", IotConGetError(nRet),iotcon_resource_interfaces_destroy(light_ifaces);iotcon_resource_types_destroy(light_types));

	iotcon_resource_interfaces_destroy(light_ifaces);
	iotcon_resource_types_destroy(light_types);

	return 0;
}

/**
 * @function 		DestroyResource
 * @description	 	function
 * @parameter		void
 * @return 			void
 */
static void DestroyResource()
{
	if (g_light_resource)
	{
		iotcon_resource_destroy(g_light_resource);
		g_light_resource = NULL;
	}

}

/**
 * @function 		presence_response_main_loop_quit_idle
 * @description	 	function
 * @parameter		gpointer p
 * @return 			gboolean
 */
static gboolean presence_response_main_loop_quit_idle(gpointer p)
{
	g_main_loop_quit(g_loop);
	g_main_loop_unref(g_loop);
	g_loop = NULL;
	return G_SOURCE_REMOVE;
}

/**
 * @function 		presence_response_main_loop_quit
 * @description	 	function
 * @parameter		bool result
 * @return 			void
 */
static void presence_response_main_loop_quit(bool result)
{
	g_bResult = result;
	g_idle_add(presence_response_main_loop_quit_idle, NULL);
}


/**
 * @function 		PresenceResponsePresenceCB
 * @description	 	callback function
 * @parameter		iotcon_presence_h presence,iotcon_error_e err, iotcon_presence_response_h response, void *user_data
 * @return 			void
 */
static void PresenceResponsePresenceCB(iotcon_presence_h presence,iotcon_error_e err, iotcon_presence_response_h response, void *user_data)
{
	int nRet;
	int tc_index = GPOINTER_TO_INT(user_data);
	iotcon_connectivity_type_e conn_type;
	char *host_address;
	char *resource_type;
	iotcon_presence_result_e result;
	iotcon_presence_trigger_e trigger;

	g_bCallbackHit = true;

	if(response == NULL)
	{
		return;
	}

	if (IOTCON_ERROR_NONE != err)
		return;

	switch (tc_index) {
	case PRESENCE_RESPONSE_GET_CONNECTIVITY_TYPE:
		nRet = iotcon_presence_response_get_connectivity_type(response, &conn_type);
		if (IOTCON_ERROR_NONE != nRet) {
			FPRINTF("[Line : %d][%s] iotcon_presence_response_get_connectivity_type fail in startup error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
			presence_response_main_loop_quit(false);
		}
		presence_response_main_loop_quit(true);
		return;
	case PRESENCE_RESPONSE_GET_HOST_ADDRESS:
		nRet = iotcon_presence_response_get_host_address(response, &host_address);
		if (IOTCON_ERROR_NONE != nRet) {
			FPRINTF("[Line : %d][%s] iotcon_presence_response_get_host_address fail in startup error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
			presence_response_main_loop_quit(false);
		}
		presence_response_main_loop_quit(true);
		return;
	case PRESENCE_RESPONSE_GET_RESOURCE_TYPE:
		nRet = iotcon_presence_response_get_resource_type(response, &resource_type);
		if (IOTCON_ERROR_NONE != nRet) {
			FPRINTF("[Line : %d][%s] iotcon_presence_response_get_resource_type fail in startup error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
			presence_response_main_loop_quit(false);
		}
		presence_response_main_loop_quit(true);
		return;
	case PRESENCE_RESPONSE_GET_RESULT:
		nRet = iotcon_presence_response_get_result(response, &result);
		if (IOTCON_ERROR_NONE != nRet) {
			FPRINTF("[Line : %d][%s] iotcon_presence_response_get_result fail in startup error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
			presence_response_main_loop_quit(false);
		}
		presence_response_main_loop_quit(true);
		return;
	case PRESENCE_RESPONSE_GET_TRIGGER:
		nRet = iotcon_presence_response_get_trigger(response, &trigger);
		if (IOTCON_ERROR_NONE != nRet) {
			FPRINTF("[Line : %d][%s] iotcon_presence_response_get_trigger fail in startup error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
			presence_response_main_loop_quit(false);
		}
		presence_response_main_loop_quit(true);
		return;
	case ADD_REMOVE_PRESENCE_CB:
		FPRINTF("[Line : %d][%s]  PresenceResponsePresenceCB callback hit", __LINE__, API_NAMESPACE);
		presence_response_main_loop_quit(true);
		return;
	default:
		FPRINTF("[Line : %d][%s] Invalid tc_index(%d) ", __LINE__, API_NAMESPACE,tc_index);
		presence_response_main_loop_quit(false);
		return;
	}
}

/**
 * @function 		PresenceResponseResourceUpdate
 * @description	 	helper function
 * @parameter		gpointer p
 * @return 			gboolean
 */
static gboolean PresenceResponseResourceUpdate(gpointer p)
{
	iotcon_resource_bind_interface(g_light_resource, IOTCON_INTERFACE_BATCH);
	return G_SOURCE_REMOVE;
}

/**
 * @function 		FoundResourceCB
 * @description	 	callback function
 * @parameter		iotcon_remote_resource_h resource, iotcon_error_e err,void *user_data
 * @return 			void
 */
static bool FoundResourceCB(iotcon_remote_resource_h resource, iotcon_error_e err,void *user_data)
{
	int nRet;
	char *host_address;
	iotcon_query_h hQuery;
	iotcon_connectivity_type_e conn_type;

	if (IOTCON_ERROR_TIMEOUT == err && g_timeout_count < TIMEOUT_COUNT_MAX)
	{
		g_timeout_count++;
		nRet = iotcon_query_create(&hQuery);
		if (IOTCON_ERROR_NONE != nRet)
		{
			FPRINTF("[Line : %d][%s] iotcon_query_create fail error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
			return false;
		}
		nRet = iotcon_query_set_resource_type(hQuery, LIGHT_RESOURCE_TYPE);
		if (IOTCON_ERROR_NONE != nRet) 
		{
			FPRINTF("[Line : %d][%s] iotcon_query_set_resource_type fail error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
			iotcon_query_destroy(hQuery);
			return false;
		}
		nRet = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY, hQuery, FoundResourceCB, user_data);
		if (IOTCON_ERROR_NONE != nRet)
		{
			FPRINTF("[Line : %d][%s] iotcon_find_resource fail in startup error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
			iotcon_query_destroy(hQuery);
			presence_response_main_loop_quit(false);
			return false;
		}
		nRet = iotcon_query_destroy(hQuery);
		if (IOTCON_ERROR_NONE != nRet)
		{
			FPRINTF("[Line : %d][%s] iotcon_query_destroy fail error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
			return false;
		}
		return false;
	}
	else if (IOTCON_ERROR_NONE != err)
	{
		presence_response_main_loop_quit(false);
		return false;
	}

	if (g_found)
		return false;

	nRet = iotcon_remote_resource_get_host_address(resource, &host_address);
	if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] iotcon_remote_resource_get_host_address fail in startup error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		presence_response_main_loop_quit(false);
		return false;
	}

	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] expected host_address[%s], found host_address[%s]", __FUNCTION__, __LINE__, g_ipv4_address, host_address);

	if (strstr(host_address, g_ipv4_address) == NULL) { // targeted resource, BUT wrong device, so skip this resource and try again
		g_found = false;
		return true;
	}

	char *uri;
	iotcon_remote_resource_get_uri_path(resource, &uri);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] host_address[%s], uri[%s]", __FUNCTION__, __LINE__, host_address, uri);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] expected uri[%s], found uri[%s]", __FUNCTION__, __LINE__, LIGHT_RESOURCE_URI, uri);

	if (strncmp(uri, LIGHT_RESOURCE_URI, strlen(LIGHT_RESOURCE_URI)) != 0)
	{
		g_found = false;
		return true;
	}

	nRet = iotcon_remote_resource_get_connectivity_type(resource, &conn_type);
	if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] iotcon_remote_resource_get_connectivity_type fail in startup error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		presence_response_main_loop_quit(false);
		return false;
	}

	g_nRet = iotcon_add_presence_cb(host_address, conn_type, LIGHT_RESOURCE_TYPE,PresenceResponsePresenceCB, user_data, &g_presence);
	if (IOTCON_ERROR_NONE != g_nRet)
	{
		FPRINTF("[Line : %d][%s] iotcon_add_presence_cb fail in startup error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(g_nRet));
		presence_response_main_loop_quit(false);
		return false;
	}

	g_idle_add(PresenceResponseResourceUpdate, NULL);
	g_found = true;

	return false;
}

/**
 * @function 		CreateAndFindResource
 * @description	 	helper function
 * @parameter		int tc_index
 * @return 			int
 */
static int CreateAndFindResource(int tc_index)
{
	int nRet;
	iotcon_query_h hQuery;
	g_loop = g_main_loop_new(NULL, FALSE);

	nRet = CreateResource(tc_index);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateResource", IotConGetError(nRet));

	nRet = iotcon_query_create(&hQuery);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_query_create", IotConGetError(nRet), DestroyResource());
		
	nRet = iotcon_query_set_resource_type(hQuery, LIGHT_RESOURCE_TYPE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_query_set_resource_type", IotConGetError(nRet), iotcon_query_destroy(hQuery);DestroyResource());
	
	nRet = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY, hQuery, FoundResourceCB, GINT_TO_POINTER(tc_index));
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_find_resource", IotConGetError(nRet), DestroyResource();iotcon_query_destroy(hQuery));

	nRet = iotcon_query_destroy(hQuery);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_query_destroy", IotConGetError(nRet));
	
	if(g_loop)
	{
		g_main_loop_run(g_loop);
		g_main_loop_unref(g_loop);
		g_loop = NULL;
	}

	DestroyResource();

	if (true == g_bResult)
		return 0;
	else
		return 1;
}

/**
 * @function      ITs_iotcon_presence_response_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */

 void ITs_iotcon_presence_response_startup(void)
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

	if (true == g_bIotconConnect)
	{
		nRet = iotcon_start_presence(PRESENCE_INTERVAL);
		if (IOTCON_ERROR_NONE != nRet)
		{
			FPRINTF("[Line : %d][%s] iotcon_start_presence fail in startup : \\n", __LINE__, API_NAMESPACE);
			g_bIotconConnect = false;
			iotcon_deinitialize();
			return;
		}
	}

	return;
}


/**
 * @function      ITs_iotcon_presence_response_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void ITs_iotcon_presence_response_cleanup(void)
{
	icitc_free_client_ipv4_address();

	if(g_presence != NULL)
	{
		iotcon_remove_presence_cb(g_presence);
	    g_presence = NULL;
	}

	/*
	if (true == g_bIotconConnect)
	{
		//iotcon_stop_presence();
		//iotcon_deinitialize();
	}
	*/

}



//& type: auto
//& purpose:  scenario to get the result on basis of response handle
/**
* @testcase   			ITc_iotcon_presence_response_get_result_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get the result on basis of response handle
* @scenario				call iotcon_presence_response_get_result
* @apicovered			iotcon_presence_response_get_result
* @passcase				When iotcon_presence_response_get_result is successful.
* @failcase				If target iotcon_presence_response_get_result or any precondition API fails.
* @precondition			iotcon should be connected
* @postcondition		iotcon should be disconnected
*/
int ITc_iotcon_presence_response_get_result_p(void)
{
	START_TEST;
	int nRet = CreateAndFindResource(PRESENCE_RESPONSE_GET_RESULT);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateAndFindResource", IotConGetError(nRet));
	return 0;
}

//& type: auto
//& purpose:  scenario to get the trigger value on basis of response handle
/**
* @testcase   			ITc_iotcon_presence_response_get_trigger_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get the trigger value on basis of response handle
* @scenario				call iotcon_presence_response_get_trigger
* @apicovered			iotcon_presence_response_get_trigger
* @passcase				When iotcon_presence_response_get_trigger is successful.
* @failcase				If target iotcon_presence_response_get_trigger or any precondition API fails.
* @precondition			iotcon should be connected
* @postcondition		iotcon should be disconnected
*/
int ITc_iotcon_presence_response_get_trigger_p(void)
{
	START_TEST;
	int nRet = CreateAndFindResource(PRESENCE_RESPONSE_GET_TRIGGER);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateAndFindResource", IotConGetError(nRet));
	return 0;
}

//& type: auto
//& purpose:  scenario to get the type of connection on basis of response handle
 /**
* @testcase   			ITc_iotcon_presence_response_get_connectivity_type_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get the type of connection on basis of response handle
* @scenario				call iotcon_presence_response_get_connectivity_type
* @apicovered			iotcon_presence_response_get_connectivity_type
* @passcase				When iotcon_presence_response_get_connectivity_type is successful.
* @failcase				If target iotcon_presence_response_get_connectivity_type or any precondition API fails.
* @precondition			iotcon should be connected
* @postcondition		iotcon should be disconnected
*/
int ITc_iotcon_presence_response_get_connectivity_type_p(void)
{
	START_TEST;
	int nRet = CreateAndFindResource(PRESENCE_RESPONSE_GET_CONNECTIVITY_TYPE);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateAndFindResource", IotConGetError(nRet));
	return 0;
}

//& type: auto
//& purpose:  scenario to get the type of resource on basis of response handle
/**
* @testcase   			ITc_iotcon_presence_response_get_resource_type_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get the type of resource on basis of response handle
* @scenario				call iotcon_presence_response_get_resource_type
* @apicovered			iotcon_presence_response_get_resource_type
* @passcase				When iotcon_presence_response_get_resource_type is successful.
* @failcase				If target iotcon_presence_response_get_resource_type or any precondition API fails.
* @precondition			iotcon should be connected
* @postcondition		iotcon should be disconnected
*/
int ITc_iotcon_presence_response_get_resource_type_p(void)
{
	START_TEST;
	int nRet = CreateAndFindResource(PRESENCE_RESPONSE_GET_RESOURCE_TYPE);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateAndFindResource", IotConGetError(nRet));
	return 0;
}


//& type: auto
//& purpose:  scenario to get the host address on basis of response handle
/**
* @testcase   			ITc_iotcon_presence_response_get_host_address_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get the host address on basis of response handle
* @scenario				call iotcon_add_presence_cb
* @apicovered			iotcon_presence_response_get_host_address
* @passcase				When iotcon_presence_response_get_host_address is successful.
* @failcase				If target iotcon_presence_response_get_host_address or any precondition API fails.
* @precondition			iotcon should be connected
* @postcondition		iotcon should be disconnected
*/
int ITc_iotcon_presence_response_get_host_address_p(void)
{
	START_TEST;
	int nRet = CreateAndFindResource(PRESENCE_RESPONSE_GET_HOST_ADDRESS);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateAndFindResource", IotConGetError(nRet));
	return 0;
}

/** @} */
/** @} */
