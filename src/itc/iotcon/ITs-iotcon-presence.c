/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <glib.h>
#include <system_info.h>
#include <iotcon.h>

#include "ITs-iotcon-common.h"

enum {
	PRESENCE_ADD_PRESENCE_CB_P,
	PRESENCE_REMOVE_PRESENCE_CB_P,
	PRESENCE_GET_HOST_ADDR_P,
	PRESENCE_GET_CONN_TYPE_P,
	PRESENCE_GET_RSRC_TYPE_P,
	PRESENCE_RESPONSE_GET_RESULT_P,
	PRESENCE_RESPONSE_GET_TRIGGER_P,
	PRESENCE_RESPONSE_GET_HOST_ADDR_P,
	PRESENCE_RESPONSE_GET_CONN_TYPE_P,
	PRESENCE_RESPONSE_GET_RSRC_TYPE_P,
};

#define PRESENCE_LIGHT_RESOURCE_TYPE "core.light"
#define PRESENCE_LIGHT_RESOURCE_URI "/a/light"

static bool g_found;
static int g_timeout_count;
static bool g_result;
static GMainLoop *g_loop;

/* ### server side ### */
static iotcon_resource_h g_light_resource;
static iotcon_presence_h g_presence;

static gboolean presence_main_loop_quit_idle(gpointer p)
{

	g_main_loop_quit(g_loop);
	g_main_loop_unref(g_loop);
	g_loop = NULL;
	return G_SOURCE_REMOVE;
}

static void presence_main_loop_quit(bool result)
{
	g_result = result;
	g_idle_add(presence_main_loop_quit_idle, NULL);
}


static void presence_request_handler(iotcon_resource_h resource,
		iotcon_request_h request, void *user_data)
{

}

static void presence_destroy_resource()
{
	if (g_light_resource) {
		iotcon_resource_destroy(g_light_resource);
		g_light_resource = NULL;
	}
}

static int presence_create_resource()
{
	iotcon_resource_types_h light_types;
	iotcon_resource_interfaces_h light_ifaces;

	int nRet = iotcon_resource_types_create(&light_types);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_create", IotConGetError(nRet));

	nRet = iotcon_resource_types_add(light_types, PRESENCE_LIGHT_RESOURCE_TYPE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_add", IotConGetError(nRet),iotcon_resource_types_destroy(light_types));

	nRet = iotcon_resource_interfaces_create(&light_ifaces);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_create", IotConGetError(nRet),iotcon_resource_types_destroy(light_types));

	nRet = iotcon_resource_interfaces_add(light_ifaces, IOTCON_INTERFACE_DEFAULT);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_add", IotConGetError(nRet),iotcon_resource_interfaces_destroy(light_ifaces);iotcon_resource_types_destroy(light_types));

	nRet = iotcon_resource_interfaces_add(light_ifaces, IOTCON_INTERFACE_BATCH);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_add", IotConGetError(nRet),iotcon_resource_interfaces_destroy(light_ifaces);iotcon_resource_types_destroy(light_types));

	nRet = iotcon_resource_create(PRESENCE_LIGHT_RESOURCE_URI, light_types,	light_ifaces,(IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),presence_request_handler,NULL,&g_light_resource);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_create", IotConGetError(nRet),iotcon_resource_interfaces_destroy(light_ifaces);iotcon_resource_types_destroy(light_types));

	iotcon_resource_interfaces_destroy(light_ifaces);
	iotcon_resource_types_destroy(light_types);

	return 0;
}

static void presence_handler(iotcon_presence_h presence, iotcon_error_e err,
		iotcon_presence_response_h response, void *user_data)
{

}
/**
* @function 		presence_found_resource
* @description	 	get remote resource clone
* @parameter		iotcon_remote_resource_h : The remote resource handle, iotcon_error_e : iotcon error
*					user_data : The user data passed from function
* @return 			bool
*/
static bool presence_found_resource(iotcon_remote_resource_h resource,
		iotcon_error_e err, void *user_data)
{
	int nRet;
	iotcon_connectivity_type_e conn_type;
	char *host_address = NULL;
	char *presence_host_address;
	char *presence_resource_type;
	iotcon_connectivity_type_e presence_conn_type;
	int tc_index = GPOINTER_TO_INT(user_data);
	iotcon_query_h hQuery;	

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
		nRet = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY, hQuery, presence_found_resource, GINT_TO_POINTER(tc_index));
		if (IOTCON_ERROR_NONE != nRet)
		{
			FPRINTF("[Line : %d][%s] iotcon_find_resource fail in startup error returned : %s\\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
			iotcon_query_destroy(hQuery);
			presence_main_loop_quit(false);
			return false;
			
		}
		nRet = iotcon_query_destroy(hQuery);
		if (IOTCON_ERROR_NONE != nRet)
		{
			FPRINTF("[Line : %d][%s] iotcon_query_destroy fail error returned : %s\\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
			return false;
			
		}
		return false;
	}
	else if (IOTCON_ERROR_NONE != err)
	{
		presence_main_loop_quit(false);
		return false;
	}

	if (g_found)
		return false;

	g_found = true;

	if(resource == NULL)
	{
		FPRINTF("[Line : %d][%s] iotcon_remote_resource_h is null in presence_found_resource callback. \\n", __LINE__, API_NAMESPACE);
		return false;
	}

	nRet = iotcon_remote_resource_get_host_address(resource, &host_address);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("[Line : %d][%s] Handle iotcon_remote_resource_get_host_address failed: %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		presence_main_loop_quit(false);
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

	nRet = iotcon_remote_resource_get_connectivity_type(resource, &conn_type);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("[Line : %d][%s] iotcon_remote_resource_get_connectivity_type failed: %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		presence_main_loop_quit(false);
		return false;
	}

	switch (tc_index)
	{
		case PRESENCE_ADD_PRESENCE_CB_P:
		case PRESENCE_REMOVE_PRESENCE_CB_P:
			nRet = iotcon_add_presence_cb(host_address, conn_type,PRESENCE_LIGHT_RESOURCE_TYPE,presence_handler, NULL, &g_presence);
			if (IOTCON_ERROR_NONE != nRet)
			{
				FPRINTF("[Line : %d][%s] iotcon_add_presence_cb failed: %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				presence_main_loop_quit(false);
				return false;
			}
			nRet = iotcon_remove_presence_cb(g_presence);
			if (IOTCON_ERROR_NONE != nRet) {
				FPRINTF("[Line : %d][%s] iotcon_remove_presence_cb failed: %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				presence_main_loop_quit(false);
				return false;
			}
			presence_main_loop_quit(true);
			return true;
		case PRESENCE_GET_HOST_ADDR_P:
			nRet = iotcon_add_presence_cb(host_address, conn_type,PRESENCE_LIGHT_RESOURCE_TYPE,presence_handler, NULL, &g_presence);
			if (IOTCON_ERROR_NONE != nRet)
			{
				FPRINTF("[Line : %d][%s] iotcon_add_presence_cb failed: %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				presence_main_loop_quit(false);
				return false;
			}
			nRet = iotcon_presence_get_host_address(g_presence, &presence_host_address);
			if (IOTCON_ERROR_NONE != nRet)
			{
				FPRINTF("[Line : %d][%s] iotcon_presence_get_host_address failed: %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				iotcon_remove_presence_cb(g_presence);
				presence_main_loop_quit(false);
				return false;
			}
			iotcon_remove_presence_cb(g_presence);
			presence_main_loop_quit(true);
			return true;
		case PRESENCE_GET_CONN_TYPE_P:
			nRet = iotcon_add_presence_cb(host_address, conn_type,PRESENCE_LIGHT_RESOURCE_TYPE,presence_handler, NULL, &g_presence);
			if (IOTCON_ERROR_NONE != nRet)
			{
				FPRINTF("[Line : %d][%s] iotcon_add_presence_cb failed: %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				presence_main_loop_quit(false);
				return false;
			}
			nRet = iotcon_presence_get_connectivity_type(g_presence, &presence_conn_type);
			if (IOTCON_ERROR_NONE != nRet)
			{
				FPRINTF("[Line : %d][%s] iotcon_presence_get_connectivity_type failed: %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				iotcon_remove_presence_cb(g_presence);
				presence_main_loop_quit(false);
				return false;
			}
			iotcon_remove_presence_cb(g_presence);
			presence_main_loop_quit(true);
			return true;
		case PRESENCE_GET_RSRC_TYPE_P:
			nRet = iotcon_add_presence_cb(host_address, conn_type,PRESENCE_LIGHT_RESOURCE_TYPE,presence_handler, NULL, &g_presence);
			if (IOTCON_ERROR_NONE != nRet)
			{
				FPRINTF("[Line : %d][%s] iotcon_add_presence_cb failed: %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				presence_main_loop_quit(false);
				return false;
			}
			nRet = iotcon_presence_get_resource_type(g_presence, &presence_resource_type);
			if (IOTCON_ERROR_NONE != nRet)
			{
				FPRINTF("[Line : %d][%s] iotcon_presence_get_resource_type failed: %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
				iotcon_remove_presence_cb(g_presence);
				presence_main_loop_quit(false);
				return false;
			}
			iotcon_remove_presence_cb(g_presence);
			presence_main_loop_quit(true);
			return true;
		default:
		    FPRINTF("[Line : %d][%s] invalid index %d\\n", __LINE__, API_NAMESPACE,tc_index);
			return false;
	}
	return false;
}
static int CreateAndFindResource(int tc_index)
{
	iotcon_query_h hQuery;	
	g_loop = g_main_loop_new(NULL, FALSE);

	int nRet = presence_create_resource();
	if (nRet == 1)
	{
		FPRINTF("[Line : %d][%s] Handle iotcon_remote_resource_h is null in presence_found_resource callback. : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		return 1;
	}
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
	nRet = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY, hQuery, presence_found_resource, GINT_TO_POINTER(tc_index));
	if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] Handle iotcon_remote_resource_h is null in presence_found_resource callback. : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		iotcon_query_destroy(hQuery);
		return 1;
	}

	if(g_loop)
	{
		g_main_loop_run(g_loop);
		g_main_loop_unref(g_loop);
		g_loop = NULL;
	}

	iotcon_query_destroy(hQuery);
	presence_destroy_resource();

		
	if (true == g_result)
		return 0;
	return 1;
}
/* ##################################################### */

/**
 * @function 		ITs_iotcon_presence_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_presence_startup(void)
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
 * @function 		ITs_iotcon_presence_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_presence_cleanup(void)
{
	icitc_free_client_ipv4_address();

	if (g_bIotconConnect)
	{
		iotcon_deinitialize();
	}
}


//& type: auto
//& purpose:  scenario to get the host address on basis of response handle
/**
* @testcase   			ITc_iotcon_presence_get_host_address_p
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
int ITc_iotcon_presence_get_host_address_p(void)
{
	START_TEST;
	int nRet = CreateAndFindResource(PRESENCE_GET_HOST_ADDR_P);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateAndFindResource", IotConGetError(nRet));

	return 0;
}


//& type: auto
//& purpose:  scenario to get the type of connection on basis of response handle
 /**
* @testcase   			ITc_iotcon_presence_get_connectivity_type_p
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
int ITc_iotcon_presence_get_connectivity_type_p(void)
{
	START_TEST;
	int nRet = CreateAndFindResource(PRESENCE_GET_CONN_TYPE_P);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateAndFindResource", IotConGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  scenario to get the type of resource on basis of response handle
/**
* @testcase   			ITc_iotcon_presence_get_resource_type_p
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
int ITc_iotcon_presence_get_resource_type_p(void)
{
	START_TEST;

	int nRet = CreateAndFindResource(PRESENCE_GET_RSRC_TYPE_P);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateAndFindResource", IotConGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  To start the presence
/**
* @testcase   			ITc_iotcon_presence_start_stop_presence_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Start and Stop the presence with defined time
* @scenario				call iotcon_start_presence,iotcon_stop_presence
* @apicovered			iotcon_start_presence,iotcon_stop_presence
* @passcase				When iotcon_start_presence and iotcon_stop_presence is successful.
* @failcase				If target iotcon_start_presence,iotcon_stop_presence API fails.
* @precondition			iotcon should be connected
* @postcondition		iotcon should be disconnected
*/
int ITc_iotcon_presence_start_stop_presence_p(void)
{
	START_TEST;
	iotcon_stop_presence();

	int nRet = iotcon_start_presence(10);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_start_presence", IotConGetError(nRet));

	nRet = iotcon_stop_presence();
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_stop_presence", IotConGetError(nRet));

	return 0;
}


//& type: auto
//& purpose:  scenario to add and remove new presence handle
/**
* @testcase   			ITc_iotcon_presence_add_remove_presence_cb_p
* @since_tizen			3.0
* @author             	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			add and remove new presence handle
* @scenario				call iotcon_add_presence_cb
* @apicovered			iotcon_add_presence_cb,iotcon_remove_presence_cb
* @passcase				When iotcon_add_presence_cb and iotcon_remove_presence_cb is successful.
* @failcase				If target API iotcon_add_presence_cb or iotcon_remove_presence_cb or any precondition API fails.
* @precondition			iotcon should be connected
* @postcondition		iotcon should be disconnected
*/
int ITc_iotcon_presence_add_remove_presence_cb_p(void)
{
	START_TEST;
	int nRet = CreateAndFindResource(PRESENCE_ADD_PRESENCE_CB_P);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateAndFindResource", IotConGetError(nRet));

	return 0;
}


/** @} */
/** @} */
