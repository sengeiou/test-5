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

iotcon_response_h g_hResponse = NULL;
static bool g_bRequestRespHandlerCB = false;
static GMainLoop *g_loop;
static iotcon_resource_h g_hLightResourceResp;
static iotcon_remote_resource_h g_hRemoteResourceResp;
static bool g_found;
static int g_timeout_count;

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
	g_main_loop_quit(g_loop);
	g_main_loop_unref(g_loop);
	g_loop = NULL;
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
	g_idle_add(gmain_loop_quit_idle, NULL);
}

/**
* @function 		RequestRespHandlerCB
* @description	 	Called when create iotcon resource to get request handle
* @parameter		iotcon_resource_h : The resource handle, iotcon_request_h : The request handle
*					user_data : The user data passed from function
* @return 			NA
*/
static void RequestRespHandlerCB(iotcon_resource_h resource, iotcon_request_h request,
		void *user_data)
{
	FPRINTF("RequestRespHandlerCB called \n");
	g_bRequestRespHandlerCB = true;

	int nRet = iotcon_response_create(request, &g_hResponse);
	if( nRet != IOTCON_ERROR_NONE)
	{
		FPRINTF("[Line: %d][%s] iotcon_response_create fail\\n", __LINE__, API_NAMESPACE);
		g_bResCallback = false;
	}
	if(g_hResponse == NULL)
	{
		FPRINTF("[Line: %d][%s] g_hResponse handle is NULL\\n", __LINE__, API_NAMESPACE);
		g_bResCallback = false;
	}
	QuitGmainLoopIdle(false);

	return;
}

/**
* @function 		CreateResource
* @description	 	Called to create and add resource and interface.
* @parameter		NA
* @return 			intiger : 0 if sussess
*/
static int CreateResource()
{
	int nRet;
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
			RequestRespHandlerCB,
			NULL,
			&g_hLightResourceResp);
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
	FPRINTF("Inside Response GetRemoteResourceCB callback... \n");
	g_bRequestRespHandlerCB = true;
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
	int nRet;
	iotcon_query_h hQuery;
	g_bRequestRespHandlerCB = true;

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
		nRet = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY, hQuery, FoundResourceCB, NULL);
		if (IOTCON_ERROR_NONE != nRet)
		{
			FPRINTF("[Line : %d][%s] iotcon_find_resource fail in startup error returned : %s\\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
			iotcon_query_destroy(hQuery);
			QuitGmainLoopIdle(false);
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

	nRet = iotcon_remote_resource_clone(resource, &g_hRemoteResourceResp);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_remote_resource_clone() Fail(%d)", nRet);
		QuitGmainLoopIdle(false);
		return false;
	}

	nRet = iotcon_remote_resource_get(g_hRemoteResourceResp, NULL, GetRemoteResourceCB, NULL);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_remote_resource_clone() Fail(%d)", nRet);
		QuitGmainLoopIdle(false);
		return false;
	}
	return false;
}

/**
* @function 		CreateAndFindResource
* @description	 	Function to create and find resource
* @parameter		NA
* @return 			intiger : 0 if sussess
*/
static int CreateAndFindResource()
{
	int nRet;
	iotcon_query_h hQuery;
	g_loop = g_main_loop_new(NULL, FALSE);

	nRet = CreateResource();
	if (0 != nRet) {
		FPRINTF("[Line : %d][%s]  CreateResource() Fail", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(g_bResCallback == false)
	{
		FPRINTF("[Line : %d][%s]  RequestRespHandlerCB() Fail", __LINE__, API_NAMESPACE);
		return 1;
	}
	nRet = iotcon_query_create(&hQuery);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_create", IotConGetError(nRet));
		
	nRet = iotcon_query_set_resource_type(hQuery, LIGHT_RESOURCE_TYPE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_query_set_resource_type", IotConGetError(nRet),iotcon_query_destroy(hQuery));

	nRet = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY,
			hQuery, FoundResourceCB, NULL);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_find_resource", IotConGetError(nRet),iotcon_query_destroy(hQuery));

	nRet = iotcon_query_destroy(hQuery);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_query_destroy", IotConGetError(nRet));

	if(g_loop)
	{
		g_main_loop_run(g_loop);
		g_main_loop_unref(g_loop);
		g_loop = NULL;
	}

	if(g_bRequestRespHandlerCB != true)
	{
		FPRINTF("[Line : %d][%s] CreateAndFindResource failed \\n", __LINE__, API_NAMESPACE);
		return 1;
	}else
		return 0;
}

/**
* @function 		CreateResourceInterfaces
* @description	 	Function to create and add iotcon interfaces
* @parameter		iotcon_resource_interfaces_h : iotcon interface handle
* @return 			intiger : 0 if sussess
*/
int CreateResourceInterfaces(iotcon_resource_interfaces_h *ifaces_h)
{
	int nRet;
	iotcon_resource_interfaces_h hIfaces;

	nRet = iotcon_resource_interfaces_create(&hIfaces);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_create", IotConGetError(nRet));


	nRet = iotcon_resource_interfaces_add(hIfaces, IOTCON_INTERFACE_DEFAULT);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_add", IotConGetError(nRet));

	nRet = iotcon_resource_interfaces_add(hIfaces, IOTCON_INTERFACE_BATCH);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_add", IotConGetError(nRet));

	*ifaces_h = hIfaces;

	return 0;
}

/**
* @function 		CreateResourceTypes
* @description	 	Function to create resource type
* @parameter		iotcon_resource_types_h : iotcon resource type handle,  const char * : resource type
* @return 			intiger : 0 if sussess
*/
int CreateResourceTypes(const char *type, iotcon_resource_types_h *types_h)
{
	int nRet;
	iotcon_resource_types_h hTypes;

	nRet = iotcon_resource_types_create(&hTypes);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_create", IotConGetError(nRet));

	nRet = iotcon_resource_types_add(hTypes, type);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_add", IotConGetError(nRet));

	*types_h = hTypes;

	return 0;
}


/**
* @function 		CreateAttributes
* @description	 	Function to create iotcon attributes
* @parameter		iotcon_attributes_h : iotcon attributes handle
* @return 			intiger : 0 if sussess
*/
int CreateAttributes(iotcon_attributes_h *attributes_h)
{
	int nRet;
	iotcon_attributes_h hAttributes, hValAttributes;
	unsigned char byte_str[3] = {70, 71, 72};
	iotcon_list_h list1, list2, list3, list4, list5, list6, list7;

	nRet = iotcon_attributes_create(&hAttributes);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_create", IotConGetError(nRet));

	nRet = iotcon_attributes_add_int(hAttributes, "int", 1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_int", IotConGetError(nRet),iotcon_attributes_destroy(hAttributes));

	nRet = iotcon_attributes_add_bool(hAttributes, "bool", true);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_bool", IotConGetError(nRet),iotcon_attributes_destroy(hAttributes));

	nRet = iotcon_attributes_add_double(hAttributes, "double", 1.1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_double", IotConGetError(nRet),iotcon_attributes_destroy(hAttributes));

	nRet = iotcon_attributes_add_null(hAttributes, "null");
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_null", IotConGetError(nRet),iotcon_attributes_destroy(hAttributes));

	nRet = iotcon_attributes_add_str(hAttributes, "str", "string");
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_str", IotConGetError(nRet),iotcon_attributes_destroy(hAttributes));

	nRet = iotcon_attributes_add_byte_str(hAttributes, "bytestr", byte_str, 3);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_byte_str", IotConGetError(nRet),iotcon_attributes_destroy(hAttributes));

	/* attributes */
	nRet = iotcon_attributes_create(&hValAttributes);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_create", IotConGetError(nRet),iotcon_attributes_destroy(hAttributes));

	nRet = iotcon_attributes_add_int(hValAttributes, "hValAttributes", 10);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_int", IotConGetError(nRet),iotcon_attributes_destroy(hValAttributes);iotcon_attributes_destroy(hAttributes));

	nRet = iotcon_attributes_add_attributes(hAttributes, "attributes", hValAttributes);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_attributes", IotConGetError(nRet),iotcon_attributes_destroy(hValAttributes);iotcon_attributes_destroy(hAttributes));

	/* attributes list */
	nRet = iotcon_list_create(IOTCON_TYPE_ATTRIBUTES, &list6);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet),iotcon_attributes_destroy(hValAttributes);iotcon_attributes_destroy(hAttributes));

	nRet = iotcon_list_add_attributes(list6, hValAttributes, -1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_attributes", IotConGetError(nRet),iotcon_list_destroy(list6);iotcon_attributes_destroy(hValAttributes);iotcon_attributes_destroy(hAttributes));
	iotcon_attributes_destroy(hValAttributes);

	nRet = iotcon_attributes_add_list(hAttributes, "state_list", list6);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_list", IotConGetError(nRet),iotcon_list_destroy(list6);iotcon_attributes_destroy(hAttributes));
	iotcon_list_destroy(list6);

	/* int list */
	nRet = iotcon_list_create(IOTCON_TYPE_INT, &list1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet),iotcon_attributes_destroy(hAttributes));

	nRet = iotcon_list_add_int(list1, 1, -1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_int", IotConGetError(nRet),iotcon_list_destroy(list1);iotcon_attributes_destroy(hAttributes));

	nRet = iotcon_attributes_add_list(hAttributes, "int_list", list1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_list", IotConGetError(nRet),iotcon_list_destroy(list1);iotcon_attributes_destroy(hAttributes));
	iotcon_list_destroy(list1);

	/* boolean list */
	nRet = iotcon_list_create(IOTCON_TYPE_BOOL, &list2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet),iotcon_attributes_destroy(hAttributes));

	nRet = iotcon_list_add_bool(list2, true, -1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_bool", IotConGetError(nRet),iotcon_list_destroy(list2);iotcon_attributes_destroy(hAttributes));

	nRet = iotcon_attributes_add_list(hAttributes, "bool_list", list2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_list", IotConGetError(nRet),iotcon_list_destroy(list2);iotcon_attributes_destroy(hAttributes));
	iotcon_list_destroy(list2);

	/* string list */
	nRet = iotcon_list_create(IOTCON_TYPE_STR, &list3);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet),iotcon_attributes_destroy(hAttributes));

	nRet = iotcon_list_add_str(list3, "string", -1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_str", IotConGetError(nRet),iotcon_list_destroy(list3);iotcon_attributes_destroy(hAttributes));

	nRet = iotcon_attributes_add_list(hAttributes, "str_list", list3);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_list", IotConGetError(nRet),iotcon_list_destroy(list3);iotcon_attributes_destroy(hAttributes));
	iotcon_list_destroy(list3);

	/* byte string list */
	nRet = iotcon_list_create(IOTCON_TYPE_BYTE_STR, &list4);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet),iotcon_attributes_destroy(hAttributes));

	nRet = iotcon_list_add_byte_str(list4, byte_str, 3, -1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_byte_str", IotConGetError(nRet),iotcon_list_destroy(list4);iotcon_attributes_destroy(hAttributes));

	nRet = iotcon_attributes_add_list(hAttributes, "byte_str_list", list4);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_list", IotConGetError(nRet),iotcon_list_destroy(list4);iotcon_attributes_destroy(hAttributes));

	/* list list */
	nRet = iotcon_list_create(IOTCON_TYPE_LIST, &list5);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet),iotcon_list_destroy(list4);iotcon_attributes_destroy(hAttributes));

	nRet = iotcon_list_add_list(list5, list4, -1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_list", IotConGetError(nRet),iotcon_list_destroy(list5);iotcon_list_destroy(list4);iotcon_attributes_destroy(hAttributes));
	iotcon_list_destroy(list4);

	nRet = iotcon_attributes_add_list(hAttributes, "list_list", list5);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_list", IotConGetError(nRet),iotcon_list_destroy(list5);iotcon_attributes_destroy(hAttributes));
	iotcon_list_destroy(list5);

	/* double list */
	nRet = iotcon_list_create(IOTCON_TYPE_DOUBLE, &list7);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet),iotcon_attributes_destroy(hAttributes));

	nRet = iotcon_list_add_double(list7, 1.1, -1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_double", IotConGetError(nRet),iotcon_list_destroy(list7);iotcon_attributes_destroy(hAttributes));

	nRet =iotcon_attributes_add_list(hAttributes, "double_list", list7);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_list", IotConGetError(nRet),iotcon_list_destroy(list7);iotcon_attributes_destroy(hAttributes));
	iotcon_list_destroy(list7);

	*attributes_h = hAttributes;

	return 0;
}

/**
* @function 		CreateRepresentation
* @description	 	Function to create iotcon representation
* @parameter		iotcon_representation_h : iotcon representation handle
* @return 			intiger : 0 if sussess
*/
int CreateRepresentation(iotcon_representation_h *representation)
{
	int nRet;
	char *uri_path = "/uri_path";
	iotcon_attributes_h hAttributes;
	iotcon_representation_h hRep;
	iotcon_resource_types_h hTypes;
	iotcon_resource_interfaces_h hIfaces;

	nRet = iotcon_representation_create(&hRep);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_representation_create() Fail(%d)", nRet);
		return nRet;
	}

	/* uri path */
	nRet = iotcon_representation_set_uri_path(hRep, uri_path);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_representation_set_uri_path() Fail(%d)", nRet);
		iotcon_representation_destroy(hRep);
		return nRet;
	}

	/* resource types */
	nRet = CreateResourceTypes(LIGHT_RESOURCE_TYPE, &hTypes);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("CreateResourceTypes() Fail(%d)", nRet);
		iotcon_representation_destroy(hRep);
		return nRet;
	}

	nRet = iotcon_representation_set_resource_types(hRep, hTypes);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_representation_set_resource_types() Fail(%d)", nRet);
		iotcon_resource_types_destroy(hTypes);
		iotcon_representation_destroy(hRep);
		return nRet;
	}

	iotcon_resource_types_destroy(hTypes);

	/* resource interfaces */
	nRet = CreateResourceInterfaces(&hIfaces);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("CreateResourceInterfaces() Fail(%d)", nRet);
		iotcon_representation_destroy(hRep);
		return nRet;
	}

	nRet = iotcon_representation_set_resource_interfaces(hRep, hIfaces);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_representation_set_resource_interfaces() Fail(%d)", nRet);
		iotcon_resource_interfaces_destroy(hIfaces);
		iotcon_representation_destroy(hRep);
		return nRet;
	}

	iotcon_resource_interfaces_destroy(hIfaces);

	/* attributes */
	nRet = CreateAttributes(&hAttributes);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("CreateAttributes() Fail(%d)", nRet);
		iotcon_representation_destroy(hRep);
		return nRet;
	}

	nRet = iotcon_representation_set_attributes(hRep, hAttributes);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_representation_set_attributes() Fail(%d)", nRet);
		iotcon_attributes_destroy(hAttributes);
		iotcon_representation_destroy(hRep);
		return nRet;
	}

	iotcon_attributes_destroy(hAttributes);
	*representation = hRep;

	return 0;
}

/**
 * @function 		ITs_iotcon_response_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_response_startup(void)
{
	struct stat stBuff;
	char *svr_db_path;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	g_bIotconConnect = true;
	g_bFeatureUnsupported = false;
	g_bResCallback = true;

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
		nRet = CreateAndFindResource();
		if (1 == nRet)
		{
			FPRINTF("[Line : %d][%s] CreateAndFindResource fail in startup : \\n", __LINE__, API_NAMESPACE);
			g_bIotconConnect = false;
			iotcon_deinitialize();
			return;
		}
	}

	return;
}


/**
 * @function 		ITs_iotcon_response_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_response_cleanup(void)
{
	icitc_free_client_ipv4_address();

	if (g_hRemoteResourceResp) {
		iotcon_remote_resource_destroy(g_hRemoteResourceResp);
		g_hRemoteResourceResp = NULL;
	}
	if (g_hLightResourceResp) {
		iotcon_resource_destroy(g_hLightResourceResp);
		g_hLightResourceResp = NULL;
	}
	if( g_bIotconConnect )
	{
		iotcon_deinitialize();
	}

	return;
}

// purpose: Creates a new hResponse handle and destroy it.
//& type: auto
/**
* @testcase   			ITc_iotcon_response_create_destroy_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Creates a new hResponse handle and destroy it.
* @scenario				call iotcon_response_create and iotcon_response_destroy
* @apicovered			iotcon_response_create,iotcon_response_destroy
* @passcase				When iotcon_response_create and iotcon_response_destroy is successful.
* @failcase				If target API iotcon_response_create or iotcon_response_destroy fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_response_create_destroy_p(void)
{
	START_TEST;
	CALLBACK_TEST;
	g_bRequestRespHandlerCB = false;

	int nRet = iotcon_response_destroy(g_hResponse);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_response_destroy", IotConGetError(nRet));
	
    return 0;
}

// purpose: Set and Get the options for response handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_response_set_get_options_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get  and set the options for hResponse handle.
* @scenario				call iotcon_response_get_options,iotcon_response_set_options
* @apicovered			iotcon_response_get_options	 & iotcon_response_set_options
* @passcase				When iotcon_response_get_options & iotcon_response_set_options is successful.
* @failcase				If target API iotcon_response_get_options  or iotcon_response_set_options API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_response_set_get_options_p(void)
{
	START_TEST;
	CALLBACK_TEST;
	int nRet = 0;
	g_bRequestRespHandlerCB = false;

	iotcon_options_h hOptions;
	iotcon_options_h hGetOptions;

	nRet = iotcon_options_create(&hOptions);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_options_create", IotConGetError(nRet),iotcon_response_destroy(g_hResponse));
	CHECK_HANDLE_CLEANUP(hOptions,"iotcon_options_create",iotcon_options_destroy(hOptions);iotcon_response_destroy(g_hResponse));

	nRet = iotcon_response_set_options(g_hResponse, hOptions);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_response_set_options", IotConGetError(nRet),iotcon_options_destroy(hOptions);iotcon_response_destroy(g_hResponse));

	nRet = iotcon_response_get_options(g_hResponse, &hGetOptions);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_response_get_options", IotConGetError(nRet),iotcon_options_destroy(hOptions);iotcon_response_destroy(g_hResponse));
	CHECK_HANDLE_CLEANUP(hGetOptions,"iotcon_response_get_options",iotcon_options_destroy(hOptions);iotcon_response_destroy(g_hResponse));

	if(hOptions != hGetOptions)
	{
		FPRINTF("[Line : %d][%s] Values of set get not matched!!!\\n", __LINE__, API_NAMESPACE);
		iotcon_options_destroy(hOptions);
		iotcon_response_destroy(g_hResponse);
        return 1;
	}

	iotcon_options_destroy(hOptions);
	iotcon_response_destroy(g_hResponse);

	return 0;
}


// purpose: Set and Get the representation for handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_response_set_get_representation_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Create the representation ,set it and get the representation for hResponse handle.
* @scenario				call iotcon_response_get_representation & iotcon_response_set_representation
* @apicovered			iotcon_representation_create,iotcon_response_get_representation	 iotcon_representation_destroy and iotcon_response_set_representation
* @passcase				When iotcon_response_get_representation & iotcon_response_set_representation is successful.
* @failcase				If target API iotcon_response_get_representation,iotcon_response_set_representation ,iotcon_representation_destroy
						or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_response_set_get_representation_p(void)
{
	START_TEST;
	CALLBACK_TEST;
	iotcon_representation_h hRep = NULL;
	iotcon_representation_h hRepresentation = NULL;
	g_bRequestRespHandlerCB = false;

	int nRet = iotcon_representation_create(&hRep);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_representation_create", IotConGetError(nRet),iotcon_response_destroy(g_hResponse));
	CHECK_HANDLE_CLEANUP(hRep,"iotcon_representation_create",iotcon_response_destroy(g_hResponse));

	nRet = iotcon_response_set_representation(g_hResponse, hRep);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_response_set_representation", IotConGetError(nRet),iotcon_representation_destroy(hRep);iotcon_response_destroy(g_hResponse););

	nRet = iotcon_response_get_representation(g_hResponse, &hRepresentation);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_response_get_representation", IotConGetError(nRet),iotcon_representation_destroy(hRep);iotcon_response_destroy(g_hResponse));
	CHECK_HANDLE(hRepresentation,"iotcon_response_get_representation");

	iotcon_representation_destroy(hRepresentation);
	iotcon_representation_destroy(hRep);
	iotcon_response_destroy(g_hResponse);

    return 0;
}

// purpose: Get and set the result for handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_response_set_get_result_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Set the result for response handle and check it with the Get Result.
* @scenario				call iotcon_response_get_result and iotcon_response_set_result
* @apicovered			iotcon_response_get_result	,iotcon_response_set_result
* @passcase				When iotcon_response_get_result & iotcon_response_set_result is successful.
* @failcase				If target API iotcon_response_get_result ,iotcon_response_set_result or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_response_set_get_result_p(void)
{
	START_TEST;
	CALLBACK_TEST;
	g_bRequestRespHandlerCB = false;
	iotcon_response_result_e eResponseResult;
	int i;
	int nRet;

	for (i = IOTCON_RESPONSE_OK; i <= IOTCON_RESPONSE_FORBIDDEN; i++) {

		nRet = iotcon_response_set_result(g_hResponse, i);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_response_set_result", IotConGetError(nRet),iotcon_response_destroy(g_hResponse));

		nRet = iotcon_response_get_result(g_hResponse, &eResponseResult);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_response_get_result", IotConGetError(nRet),iotcon_response_destroy(g_hResponse));
		if(eResponseResult != i)
		{
			FPRINTF("[Line : %d][%s] Values of set get not matched in !!!\\n", __LINE__, API_NAMESPACE);
			iotcon_response_destroy(g_hResponse);
			return 1;
		}
	}

	iotcon_response_destroy(g_hResponse);

	return 0;
}
// purpose: Send response to the client.
//& type: auto
/**
* @testcase   			ITc_iotcon_response_send_p
* @since_tizen			3.0
* @author             	SRID(gaurav.m2)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Send response to the client.
* @scenario				call iotcon_response_send
* @apicovered			iotcon_response_send
* @passcase				When iotcon_response_send is successful.
* @failcase				If target API iotcon_response_send or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_response_send_p(void)
{
	START_TEST;
	CALLBACK_TEST;
	g_bRequestRespHandlerCB = false;
	iotcon_options_h hOptions = NULL;
	iotcon_representation_h hRep = NULL;

	int nRet = iotcon_options_create(&hOptions);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_options_create", IotConGetError(nRet),iotcon_response_destroy(g_hResponse));
	CHECK_HANDLE_CLEANUP(hOptions,"iotcon_options_create",iotcon_response_destroy(g_hResponse));

	nRet = iotcon_options_add(hOptions, 2048, "1");
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_options_add", IotConGetError(nRet),iotcon_options_destroy(hOptions);iotcon_response_destroy(g_hResponse));

	nRet = iotcon_response_set_result(g_hResponse, IOTCON_RESPONSE_OK);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_response_set_result", IotConGetError(nRet),iotcon_options_destroy(hOptions);iotcon_response_destroy(g_hResponse));

	nRet = iotcon_response_set_options(g_hResponse, hOptions);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_response_set_options", IotConGetError(nRet),iotcon_options_destroy(hOptions);iotcon_response_destroy(g_hResponse));

	nRet = CreateRepresentation(&hRep);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "CreateRepresentation", IotConGetError(nRet),iotcon_options_destroy(hOptions);iotcon_response_destroy(g_hResponse));
	CHECK_HANDLE_CLEANUP(hRep,"CreateRepresentation",iotcon_options_destroy(hOptions);iotcon_response_destroy(g_hResponse));

	nRet = iotcon_representation_create(&hRep);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_representation_create", IotConGetError(nRet),iotcon_options_destroy(hOptions);iotcon_response_destroy(g_hResponse));
	CHECK_HANDLE_CLEANUP(hRep,"iotcon_representation_create",iotcon_options_destroy(hOptions);iotcon_representation_destroy(hRep);iotcon_response_destroy(g_hResponse));

	nRet = iotcon_response_set_representation(g_hResponse, hRep);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_response_set_representation", IotConGetError(nRet),iotcon_representation_destroy(hRep);iotcon_options_destroy(hOptions);iotcon_response_destroy(g_hResponse));

	//target api
	nRet = iotcon_response_send(g_hResponse);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_response_send", IotConGetError(nRet),iotcon_representation_destroy(hRep);iotcon_options_destroy(hOptions);iotcon_response_destroy(g_hResponse));

	iotcon_representation_destroy(hRep);
	iotcon_options_destroy(hOptions);
	iotcon_response_destroy(g_hResponse);

    return 0;
}
