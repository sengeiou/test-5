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

#define LIGHT_RESOURCE_TYPE "core.light"
#define LIGHT_RESOURCE_TYPE2 "core.light2"
#define LIGHT_RESOURCE_TYPE3 "core.light3"
#define LIGHT_RESOURCE_URI "/a/light"
#define LED_RESOURCE_TYPE "core.led"
#define LED_RESOURCE_URI "/a/led"

enum {
	RESOURCE_BIND_CHILD_RESOURCE,
	RESOURCE_BIND_INTERFACE,
	RESOURCE_BIND_TYPE,
	RESOURCE_CREATE,
	RESOURCE_DESTROY,
	RESOURCE_GET_INTERFACES,
	RESOURCE_GET_NTH_CHILD,
	RESOURCE_GET_NUMBER_OF_CHILDREN,
	RESOURCE_GET_PROPERTIES,
	RESOURCE_GET_TYPES,
	RESOURCE_GET_URI_PATH,
	RESOURCE_NOTIFY,
	RESOURCE_SET_REQUEST_HANDLER,
	RESOURCE_UNBIND_CHILD_RESOURCE,
};

bool g_check = false;
static bool g_bRequestHandlerCB = false;
static bool g_bResult;
static iotcon_resource_h g_hLightResource;
static iotcon_remote_resource_h g_hRemoteResource;

/**
* @function 		CreateState
* @description	 	Called to create iotcon state handle
* @parameter		iotcon_attributes_h : The state handle
* @return 			int
*/
static int CreateState(iotcon_attributes_h *state_h)
{
	int nRet;
	iotcon_attributes_h state, val_attributes;
	unsigned char byte_str[3] = {70, 71, 72};
	iotcon_list_h list1, list2, list3, list4, list5, list6, list7;

	nRet = iotcon_attributes_create(&state);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_attributes_create() Fail(%d)", nRet);
		return nRet;
	}

	nRet = iotcon_attributes_add_int(state, "int", 1);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_attributes_add_int() Fail(%d)", nRet);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	nRet = iotcon_attributes_add_bool(state, "bool", true);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_attributes_add_bool() Fail(%d)", nRet);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	nRet = iotcon_attributes_add_double(state, "double", 1.1);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_attributes_add_double() Fail(%d)", nRet);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	nRet = iotcon_attributes_add_null(state, "null");
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_attributes_add_null() Fail(%d)", nRet);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	nRet = iotcon_attributes_add_str(state, "str", "string");
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_attributes_add_str() Fail(%d)", nRet);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	nRet = iotcon_attributes_add_byte_str(state, "bytestr", byte_str, 3);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_attributes_add_byte_str() Fail(%d)", nRet);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	/* state */
	nRet = iotcon_attributes_create(&val_attributes);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_attributes_create() Fail(%d)", nRet);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	nRet = iotcon_attributes_add_int(val_attributes, "val_attributes", 10);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_attributes_add_int() Fail(%d)", nRet);
		iotcon_attributes_destroy(val_attributes);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	nRet = iotcon_attributes_add_attributes(state, "state", val_attributes);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_attributes_add_attributes() Fail(%d)", nRet);
		iotcon_attributes_destroy(val_attributes);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	/* state list */
	nRet = iotcon_list_create(IOTCON_TYPE_ATTRIBUTES, &list6);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_list_create() Fail(%d)", nRet);
		iotcon_attributes_destroy(val_attributes);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	nRet = iotcon_list_add_attributes(list6, val_attributes, -1);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_list_add_attributes() Fail(%d)", nRet);
		iotcon_list_destroy(list6);
		iotcon_attributes_destroy(val_attributes);
		iotcon_attributes_destroy(state);
		return nRet;
	}
	iotcon_attributes_destroy(val_attributes);

	nRet = iotcon_attributes_add_list(state, "state_list", list6);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_attributes_add_list() Fail(%d)", nRet);
		iotcon_list_destroy(list6);
		iotcon_attributes_destroy(state);
		return nRet;
	}
	iotcon_list_destroy(list6);

	/* int list */
	nRet = iotcon_list_create(IOTCON_TYPE_INT, &list1);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_list_create() Fail(%d)", nRet);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	nRet = iotcon_list_add_int(list1, 1, -1);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_list_add_int() Fail(%d)", nRet);
		iotcon_list_destroy(list1);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	nRet = iotcon_attributes_add_list(state, "int_list", list1);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_attributes_add_list() Fail(%d)", nRet);
		iotcon_list_destroy(list1);
		iotcon_attributes_destroy(state);
		return nRet;
	}
	iotcon_list_destroy(list1);

	/* boolean list */
	nRet = iotcon_list_create(IOTCON_TYPE_BOOL, &list2);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_list_create() Fail(%d)", nRet);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	nRet = iotcon_list_add_bool(list2, true, -1);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_list_add_bool() Fail(%d)", nRet);
		iotcon_list_destroy(list2);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	nRet = iotcon_attributes_add_list(state, "bool_list", list2);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_attributes_add_list() Fail(%d)", nRet);
		iotcon_list_destroy(list2);
		iotcon_attributes_destroy(state);
		return nRet;
	}
	iotcon_list_destroy(list2);

	/* string list */
	nRet = iotcon_list_create(IOTCON_TYPE_STR, &list3);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_list_create() Fail(%d)", nRet);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	nRet = iotcon_list_add_str(list3, "string", -1);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_list_add_str() Fail(%d)", nRet);
		iotcon_list_destroy(list3);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	nRet = iotcon_attributes_add_list(state, "str_list", list3);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_attributes_add_list() Fail(%d)", nRet);
		iotcon_list_destroy(list3);
		iotcon_attributes_destroy(state);
		return nRet;
	}
	iotcon_list_destroy(list3);

	/* byte string list */
	nRet = iotcon_list_create(IOTCON_TYPE_BYTE_STR, &list4);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_list_create() Fail(%d)", nRet);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	nRet = iotcon_list_add_byte_str(list4, byte_str, 3, -1);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_list_add_byte_str() Fail(%d)", nRet);
		iotcon_list_destroy(list4);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	nRet = iotcon_attributes_add_list(state, "byte_str_list", list4);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_attributes_add_list() Fail(%d)", nRet);
		iotcon_list_destroy(list4);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	/* list list */
	nRet = iotcon_list_create(IOTCON_TYPE_LIST, &list5);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_list_create() Fail(%d)", nRet);
		iotcon_list_destroy(list4);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	nRet = iotcon_list_add_list(list5, list4, -1);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_list_add_list() Fail(%d)", nRet);
		iotcon_list_destroy(list5);
		iotcon_list_destroy(list4);
		iotcon_attributes_destroy(state);
		return nRet;
	}
	iotcon_list_destroy(list4);

	nRet = iotcon_attributes_add_list(state, "list_list", list5);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_attributes_add_list() Fail(%d)", nRet);
		iotcon_list_destroy(list5);
		iotcon_attributes_destroy(state);
		return nRet;
	}
	iotcon_list_destroy(list5);

	/* double list */
	nRet = iotcon_list_create(IOTCON_TYPE_DOUBLE, &list7);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_list_create() Fail(%d)", nRet);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	nRet = iotcon_list_add_double(list7, 1.1, -1);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_list_add_double() Fail(%d)", nRet);
		iotcon_list_destroy(list7);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	nRet =iotcon_attributes_add_list(state, "double_list", list7);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_attributes_add_list() Fail(%d)", nRet);
		iotcon_list_destroy(list7);
		iotcon_attributes_destroy(state);
		return nRet;
	}

	iotcon_list_destroy(list7);

	*state_h = state;

	return 0;
}

/**
* @function 		CreateResourceTypes
* @description	 	Called to create iotcon resource types handle
* @parameter		iotcon_resource_types_h : The resource types handle
* @return 			int
*/
static int CreateResourceTypes(const char *type, iotcon_resource_types_h *types_h)
{
	int nRet;
	iotcon_resource_types_h types;

	nRet = iotcon_resource_types_create(&types);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_resource_types_create() Fail(%d)", nRet);
		return nRet;
	}

	nRet = iotcon_resource_types_add(types, type);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_resource_types_add() Fail(%d)", nRet);
		iotcon_resource_types_destroy(types);
		return nRet;
	}

	*types_h = types;
	return 0;
}

/**
* @function 		CreateResourceInterfaces
* @description	 	Called to create iotcon interfaces handle
* @parameter		iotcon_resource_interfaces_h : The interfaces handle
* @return 			int
*/
static int CreateResourceInterfaces(iotcon_resource_interfaces_h *ifaces_h)
{
	int nRet;
	iotcon_resource_interfaces_h ifaces;

	nRet = iotcon_resource_interfaces_create(&ifaces);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_resource_interfaces_create() Fail(%d)", nRet);
		return nRet;
	}

	nRet = iotcon_resource_interfaces_add(ifaces, IOTCON_INTERFACE_DEFAULT);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_resource_interfaces_add() Fail(%d)", nRet);
		iotcon_resource_interfaces_destroy(ifaces);
		return nRet;
	}

	nRet = iotcon_resource_interfaces_add(ifaces, IOTCON_INTERFACE_BATCH);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_resource_interfaces_add() Fail(%d)", nRet);
		iotcon_resource_interfaces_destroy(ifaces);
		return nRet;
	}

	*ifaces_h = ifaces;

	return 0;
}

/**
* @function 		CreateRepresentation
* @description	 	Called to create iotcon representation handle
* @parameter		iotcon_representation_h : The representation handle
* @return 			int
*/
static int CreateRepresentation(iotcon_representation_h *representation)
{
	int nRet;
	char *uri_path = "/uri_path";
	iotcon_attributes_h state;
	iotcon_representation_h repr;
	iotcon_resource_types_h types;
	iotcon_resource_interfaces_h ifaces;

	nRet = iotcon_representation_create(&repr);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_representation_create() Fail(%d)", nRet);
		return nRet;
	}

	/* uri path */
	nRet = iotcon_representation_set_uri_path(repr, uri_path);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_representation_set_uri_path() Fail(%d)", nRet);
		iotcon_representation_destroy(repr);
		return nRet;
	}

	/* resource types */
	nRet = CreateResourceTypes(LIGHT_RESOURCE_TYPE, &types);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("CreateResourceTypes() Fail(%d)", nRet);
		iotcon_representation_destroy(repr);
		return nRet;
	}

	nRet = iotcon_representation_set_resource_types(repr, types);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_representation_set_resource_types() Fail(%d)", nRet);
		iotcon_resource_types_destroy(types);
		iotcon_representation_destroy(repr);
		return nRet;
	}

	iotcon_resource_types_destroy(types);

	/* resource interfaces */
	nRet = CreateResourceInterfaces(&ifaces);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("CreateResourceInterfaces() Fail(%d)", nRet);
		iotcon_representation_destroy(repr);
		return nRet;
	}

	nRet = iotcon_representation_set_resource_interfaces(repr, ifaces);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_representation_set_resource_interfaces() Fail(%d)", nRet);
		iotcon_resource_interfaces_destroy(ifaces);
		iotcon_representation_destroy(repr);
		return nRet;
	}

	iotcon_resource_interfaces_destroy(ifaces);

	/* state */
	nRet = CreateState(&state);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("CreateState() Fail(%d)", nRet);
		iotcon_representation_destroy(repr);
		return nRet;
	}

	nRet = iotcon_representation_set_attributes(repr, state);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_representation_set_attributes() Fail(%d)", nRet);
		iotcon_attributes_destroy(state);
		iotcon_representation_destroy(repr);
		return nRet;
	}

	iotcon_attributes_destroy(state);
	*representation = repr;

	return 0;
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
* @function 		FindRequestHandlerCB
* @description	 	Called when create iotcon resource to get response handle
* @parameter		iotcon_resource_h : The resource handle, iotcon_request_h : The request handle
*					user_data : The user data passed from function
* @return 			NA
*/
static void FindRequestHandlerCB(iotcon_resource_h resource,
		iotcon_request_h request, void *user_data)
{
	FPRINTF("Inside FindRequestHandlerCB callback... \n");

	int nRet;
	iotcon_representation_h repr;
	g_bRequestHandlerCB = true;
	iotcon_response_h response;
	nRet = CreateRepresentation(&repr);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("CreateRepresentation() Fail(%d)", nRet);
		QuitGmainLoopIdle(false);
		return;
	}

	nRet = iotcon_response_create(request, &response);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_response_create() Fail(%d)", nRet);
		QuitGmainLoopIdle(false);
		return;
	}

	nRet = iotcon_response_set_representation(response, repr);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_response_set_representation() Fail(%d)", nRet);
		iotcon_response_destroy(response);
		QuitGmainLoopIdle(false);
		return;
	}

	nRet = iotcon_response_set_result(response, IOTCON_RESPONSE_OK);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_response_set_result() Fail(%d)", nRet);
		iotcon_response_destroy(response);
		QuitGmainLoopIdle(false);
		return;
	}

	iotcon_representation_destroy(repr);

	nRet = iotcon_response_send(response);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_response_send() Fail(%d)", nRet);
		iotcon_response_destroy(response);
		QuitGmainLoopIdle(false);
		return;
	}

	iotcon_response_destroy(response);
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
	iotcon_representation_h hRep = NULL;
	iotcon_response_h hResponse;
	g_bRequestHandlerCB = true;

     nRet = CreateRepresentation(&hRep);
     if (IOTCON_ERROR_NONE != nRet) {
            FPRINTF("CreateRepresentation() Fail(%d)", nRet);
            QuitGmainLoopIdle(false);
           return;
     }

     nRet = iotcon_response_create(request, &hResponse);
     if (IOTCON_ERROR_NONE != nRet) {
            FPRINTF("iotcon_response_create() Fail(%d)", nRet);
            QuitGmainLoopIdle(false);
            return;
     }

     nRet = iotcon_response_set_representation(hResponse, hRep);
     if (IOTCON_ERROR_NONE != nRet) {
            FPRINTF("iotcon_response_set_representation() Fail(%d)", nRet);
            iotcon_response_destroy(hResponse);
            QuitGmainLoopIdle(false);
            return;
     }

     nRet = iotcon_response_set_result(hResponse, IOTCON_RESPONSE_OK);
     if (IOTCON_ERROR_NONE != nRet) {
            FPRINTF("iotcon_response_set_result() Fail(%d)", nRet);
            iotcon_response_destroy(hResponse);
            QuitGmainLoopIdle(false);
            return;
     }

    iotcon_representation_destroy(hRep);

     nRet = iotcon_response_send(hResponse);
     if (IOTCON_ERROR_NONE != nRet) {
            FPRINTF("iotcon_response_send() Fail(%d)", nRet);
            iotcon_response_destroy(hResponse);
            QuitGmainLoopIdle(false);
            return;
     }

     iotcon_response_destroy(hResponse);
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

	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_create", IotConGetError(nRet),iotcon_resource_interfaces_destroy(hLightiFaces);iotcon_resource_types_destroy(hLightTypes));

	iotcon_resource_interfaces_destroy(hLightiFaces);
	iotcon_resource_types_destroy(hLightTypes);

	return 0;
}

/**
* @function 		ResourceNotifyIdle
* @description	 	Called when Resource idle is notified
* @parameter		gpointer data
* @return 			gboolean
*/
static gboolean ResourceNotifyIdle(gpointer p)
{
	int nRet;
	iotcon_representation_h repr;
	CreateRepresentation(&repr);
	nRet = iotcon_resource_notify(g_hLightResource, repr, NULL, IOTCON_QOS_HIGH);
	if (IOTCON_ERROR_NONE != nRet) {
		FPRINTF("iotcon_resource_notify() Fail(%d)", nRet);
		iotcon_representation_destroy(repr);
		QuitGmainLoopIdle(false);
		return G_SOURCE_REMOVE;
	}
	iotcon_representation_destroy(repr);
	return G_SOURCE_REMOVE;
}

/**
* @function 		ResourceObserveCB
* @description	 	Called when resource observe is registered
* @parameter		iotcon_remote_resource_h : The remote resource handle, iotcon_error_e : The iotcon error,
*					sequence number ,iotcon_response_h: Iotcon Reponse user_data : The user data passed from function
* @return 			NA
*/
static void ResourceObserveCB(iotcon_remote_resource_h resource,
		iotcon_error_e err, int sequence_number, iotcon_response_h response, void *user_data)
{
	static int notify_count = 0;
	int tc_index = (int)user_data;

	switch (tc_index) {
	case RESOURCE_CREATE:
	case RESOURCE_SET_REQUEST_HANDLER:
		QuitGmainLoopIdle(true);
		return;
	case RESOURCE_NOTIFY:
		if (0 == notify_count++) {
			FPRINTF("RESOURCE_NOTIFY");
			g_idle_add(ResourceNotifyIdle, NULL);
			return;
		}
		QuitGmainLoopIdle(true);
		return;
	default:
		FPRINTF("Invalid tc_index(%d)", tc_index);
		QuitGmainLoopIdle(false);
		return;
	}
}

/**
* @function 		FoundResourceCB
* @description	 	get remote resource clone
* @parameter		iotcon_remote_resource_h : The remote resource handle, iotcon_error_e : iotcon error
*					user_data : The user data passed from function
* @return 			bool
*/
static bool FoundResourceCB(iotcon_remote_resource_h resource,iotcon_error_e err, void *user_data)
{
	FPRINTF("Inside FoundResourceCB callback... \n");

	int nRet;
	int tc_index = (int)user_data;
	int nIotconTimeoutId = 0;
	iotcon_query_h hquery;

	if (IOTCON_ERROR_TIMEOUT == err && nIotconTimeoutId < TIMEOUT_COUNT_MAX) {
		nIotconTimeoutId++;
		nRet = iotcon_query_create(&hquery);
		if (IOTCON_ERROR_NONE != nRet)
		{
			FPRINTF("[Line : %d][%s] iotcon_query_create fail error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
			return false;
		}
		nRet = iotcon_query_set_resource_type(hquery, LIGHT_RESOURCE_TYPE);
		if (IOTCON_ERROR_NONE != nRet) 
		{
			FPRINTF("[Line : %d][%s] iotcon_query_set_resource_type fail error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
			iotcon_query_destroy(hquery);
			return false;
		}
		nRet = iotcon_find_resource(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP | IOTCON_CONNECTIVITY_PREFER_UDP | IOTCON_CONNECTIVITY_IPV4_ONLY,
				hquery, FoundResourceCB, user_data);
		if (IOTCON_ERROR_NONE != nRet) {
			FPRINTF("iotcon_find_resource() Fail(%d)", nRet);
			iotcon_query_destroy(hquery);
			QuitGmainLoopIdle(false);
			
		}
		nRet = iotcon_query_destroy(hquery);
		if (IOTCON_ERROR_NONE != nRet)
		{
			FPRINTF("[Line : %d][%s] iotcon_query_destroy fail error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
			
		}
		return false;
	} else if (IOTCON_ERROR_NONE != err) {
		QuitGmainLoopIdle(false);
		return false;
	}

	char *host_address, *uri;
	iotcon_remote_resource_get_host_address(resource, &host_address);
	iotcon_remote_resource_get_uri_path(resource, &uri);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] host_address[%s], uri[%s]", __FUNCTION__, __LINE__, host_address, uri);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] expected host_address[%s], found host_address[%s]", __FUNCTION__, __LINE__, g_ipv4_address, host_address);
	if (strstr(host_address, g_ipv4_address) == NULL) { // targeted resource, BUT wrong device, so skip this resource and try again
		return true;
	}

	switch (tc_index) {
	case RESOURCE_SET_REQUEST_HANDLER:
		nRet = iotcon_resource_set_request_handler(g_hLightResource,
				FindRequestHandlerCB, (void *)tc_index);
		if (IOTCON_ERROR_NONE != nRet) {
			FPRINTF("iotcon_resource_set_request_handler() Fail(%d)", nRet);
			QuitGmainLoopIdle(false);
			return false;
		}

		nRet = iotcon_remote_resource_clone(resource, &g_hRemoteResource);
		if (IOTCON_ERROR_NONE != nRet) {
			FPRINTF("iotcon_remote_resource_clone() Fail(%d)", nRet);
			QuitGmainLoopIdle(false);
			return false;
		}

		nRet = iotcon_remote_resource_observe_register(g_hRemoteResource,
				IOTCON_OBSERVE_ACCEPT_OUT_OF_ORDER, NULL, ResourceObserveCB, (void *)tc_index);
		if (IOTCON_ERROR_NONE != nRet) {
			FPRINTF("iotcon_remote_resource_observe_register() Fail(%d)", nRet);
			QuitGmainLoopIdle(false);
			return false;
		}
		break;
	case RESOURCE_CREATE:
	case RESOURCE_NOTIFY:
		nRet = iotcon_remote_resource_clone(resource, &g_hRemoteResource);
		if (IOTCON_ERROR_NONE != nRet) {
			FPRINTF("iotcon_remote_resource_clone() Fail(%d)", nRet);
			QuitGmainLoopIdle(false);
			return false;
		}

		nRet = iotcon_remote_resource_observe_register(g_hRemoteResource,
				IOTCON_OBSERVE_ACCEPT_OUT_OF_ORDER, NULL, ResourceObserveCB, (void *)tc_index);
		if (IOTCON_ERROR_NONE != nRet) {
			FPRINTF("iotcon_remote_resource_observe_register() Fail(%d)", nRet);
			QuitGmainLoopIdle(false);
			return false;
		}
		break;
	default:
		FPRINTF("Invalid tc_index(%d)", tc_index);
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
			hQuery, FoundResourceCB, (void *)tc_index);
	if (IOTCON_ERROR_NONE != nRet) {
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

//& set: Iotcon

/** @addtogroup itc-iotcon
*  @ingroup itc
*  @{
*/
static iotcon_resource_h g_hLightResource = NULL;
static iotcon_resource_h g_hLedResource = NULL;
iotcon_resource_h g_hResource = NULL;
iotcon_request_h g_hReq = NULL;

/**
* @function 		IotconResourceTypesForeachCB
* @description	 	Callback Function
* @parameter		const char *type, void *user_data
* @return 			NA
*/
bool IotconResourceTypesForeachCB(const char *type, void *user_data)
{
	g_bCheckCb = true;
	if (user_data)
		++ (*((int *)user_data));
	return IOTCON_FUNC_CONTINUE;
}

/**
* @function 		IotconRequestHandlerCB
* @description	 	Callback Function
* @parameter		iotcon_resource_h resource, iotcon_request_h request, void *user_data
* @return 			NA
*/
void IotconRequestHandlerCB(iotcon_resource_h resource, iotcon_request_h request, void *user_data)
 {
	g_bCheckCb = true;
	FPRINTF("[Line : %d][%s] Inside IotconRequestHandlerCB callback... \\n", __LINE__, API_NAMESPACE);

	if( resource == NULL)
	{
		FPRINTF("[Line : %d][%s] IotconRequestHandlerCB callback, resource is NULL\\n", __LINE__, API_NAMESPACE);
	}else{
		g_hResource = resource;
	}
	if( request == NULL )
	{
		FPRINTF("[Line : %d][%s] IotconRequestHandlerCB callback, request is NULL\\n", __LINE__, API_NAMESPACE);
	}else{
		g_hReq = request;
	}

    if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
		return;
	}

	return;
 }

/**
* @function 		IotconSetRequestHandlerCB
* @description	 	Callback Function
* @parameter		iotcon_resource_h resource,iotcon_request_h request, void *user_data
* @return 			NA
*/
void IotconSetRequestHandlerCB(iotcon_resource_h resource,iotcon_request_h request, void *user_data)
{
	g_bCheckCb = true;

	if (user_data)
		++ (*((int *)user_data));

	if(resource == NULL || request == NULL )
	{
		FPRINTF("[Line : %d][%s] IotconSetRequestHandlerCB callback, resource or request is NULL\\n", __LINE__, API_NAMESPACE);
	}
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
		return;
	}
	return;

}
/**
* @function 		IotconDestroyRes
* @description	 	destroy resource
* @parameter		NA
* @return 			NA
*/
void IotconDestroyRes(void)
{
	if (g_hLightResource)
	{
		iotcon_resource_destroy(g_hLightResource);
		g_hLightResource = NULL;
		return;
	}
	if (g_hLedResource)
	{
		iotcon_resource_destroy(g_hLedResource);
		g_hLedResource = NULL;
		return;
	}
	return;
}

/**
 * @function 		IotconCreateResourceLight
 * @description	 	Creates lite resource iotcon
 * @parameter		NA
 * @return 			NA
 */
static int IotconCreateResourceLight(void)
{
	iotcon_resource_types_h light_types = NULL;
	iotcon_resource_interfaces_h light_ifaces;
	int nIotconTimeoutId = 0;

	int nRet = iotcon_resource_types_create(&light_types);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_create", IotConGetError(nRet));
	if(light_types==NULL)
	{
		FPRINTF("[Line : %d][%s] iotcon_resource_types_create fail light_type is NULL error returned : \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = iotcon_resource_types_add(light_types, "core.light");
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_add", IotConGetError(nRet),iotcon_resource_types_destroy(light_types));

	nRet = iotcon_resource_interfaces_create(&light_ifaces);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_create", IotConGetError(nRet),iotcon_resource_types_destroy(light_types));

	nRet = iotcon_resource_interfaces_add(light_ifaces, IOTCON_INTERFACE_DEFAULT);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_add", IotConGetError(nRet),iotcon_resource_types_destroy(light_types);iotcon_resource_interfaces_destroy(light_ifaces));

	nRet = iotcon_resource_interfaces_add(light_ifaces, IOTCON_INTERFACE_BATCH);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_add", IotConGetError(nRet),iotcon_resource_types_destroy(light_types);iotcon_resource_interfaces_destroy(light_ifaces));

	g_bCheckCb = false;

	nRet = iotcon_resource_create(REMOTE_RESOURCE_LIGHT,light_types,light_ifaces,
				  (IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),IotconSetRequestHandlerCB,NULL,&g_hLightResource);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_create", IotConGetError(nRet),iotcon_resource_types_destroy(light_types);iotcon_resource_interfaces_destroy(light_ifaces));

	RUN_POLLING_LOOP;

	if(g_hLightResource==NULL)
	{
		FPRINTF("[Line : %d][%s] iotcon_resource_create fail g_hLightResource is NULL error returned : \\n", __LINE__, API_NAMESPACE);

		iotcon_resource_types_destroy(light_types);
		iotcon_resource_interfaces_destroy(light_ifaces);
		return 1;
	}

	iotcon_resource_interfaces_destroy(light_ifaces);
	iotcon_resource_types_destroy(light_types);

	return 0;
}

/**
 * @function 		IotconCreateResourceLED
 * @description	 	Creates lite resource iotcon
 * @parameter		NA
 * @return 			NA
 */
static int IotconCreateResourceLED(void)
{
	iotcon_resource_types_h light_types = NULL;
	iotcon_resource_interfaces_h light_ifaces;
	int nIotconTimeoutId = 0;

	int nRet = iotcon_resource_types_create(&light_types);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_create", IotConGetError(nRet));
	if(light_types==NULL)
	{
		FPRINTF("[Line : %d][%s] iotcon_resource_types_create fail light_type is NULL error returned : \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = iotcon_resource_types_add(light_types, "core.light");
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_add", IotConGetError(nRet),iotcon_resource_types_destroy(light_types));

	nRet = iotcon_resource_interfaces_create(&light_ifaces);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_create", IotConGetError(nRet),iotcon_resource_types_destroy(light_types));

	nRet = iotcon_resource_interfaces_add(light_ifaces, IOTCON_INTERFACE_DEFAULT);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_add", IotConGetError(nRet),iotcon_resource_types_destroy(light_types);iotcon_resource_interfaces_destroy(light_ifaces));

	nRet = iotcon_resource_interfaces_add(light_ifaces, IOTCON_INTERFACE_BATCH);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_add", IotConGetError(nRet),iotcon_resource_types_destroy(light_types);iotcon_resource_interfaces_destroy(light_ifaces));

	g_bCheckCb = false;


	nRet = iotcon_resource_create(REMOTE_RESOURCE_LED,light_types,light_ifaces,
				  (IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),IotconRequestHandlerCB,NULL,&g_hLedResource);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_create", IotConGetError(nRet),iotcon_resource_types_destroy(light_types);iotcon_resource_interfaces_destroy(light_ifaces));

	RUN_POLLING_LOOP;

	if(g_hLedResource==NULL)
	{
		FPRINTF("[Line : %d][%s] iotcon_lite_resource_create fail g_hLedResource is NULL error returned : \\n", __LINE__, API_NAMESPACE);

		iotcon_resource_types_destroy(light_types);
		iotcon_resource_interfaces_destroy(light_ifaces);
		return 1;
	}

	iotcon_resource_interfaces_destroy(light_ifaces);
	iotcon_resource_types_destroy(light_types);

	return 0;
}

/**
* @function 		IotconCreateLightResource
* @description	 	create light resource
* @parameter		NA
* @return 			NA
*/
static int IotconCreateLightResource(void)
{
	g_bCheckCb = false;
    int nIotconTimeoutId = 0;

	iotcon_resource_types_h hLightTypes = NULL;

	IotconDestroyRes();

	int nRet = iotcon_resource_types_create(&hLightTypes);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_create", IotConGetError(nRet));
	CHECK_HANDLE(hLightTypes,"iotcon_resource_types_create");

	nRet = iotcon_resource_types_add(hLightTypes, LIGHT_RESOURCE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_add", IotConGetError(nRet),iotcon_resource_types_destroy(hLightTypes));
    g_nCheckAPICb = 0;

	iotcon_resource_interfaces_h ifaces;

	nRet = iotcon_resource_interfaces_create(&ifaces);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_create", IotConGetError(nRet),iotcon_resource_types_destroy(hLightTypes));

	nRet = iotcon_resource_interfaces_add(ifaces, IOTCON_INTERFACE_BATCH);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_add", IotConGetError(nRet),iotcon_resource_types_destroy(hLightTypes);iotcon_resource_interfaces_destroy(ifaces));

	nRet = iotcon_resource_create(REMOTE_RESOURCE_LIGHT,hLightTypes,ifaces,
		  (IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE),IotconRequestHandlerCB,NULL,&g_hLightResource);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_create", IotConGetError(nRet),iotcon_resource_types_remove(hLightTypes, LIGHT_RESOURCE);iotcon_resource_types_destroy(hLightTypes);iotcon_resource_interfaces_destroy(ifaces));
	CHECK_HANDLE(g_hLightResource,"iotcon_resource_create");

	RUN_POLLING_LOOP;

	iotcon_resource_types_destroy(hLightTypes);
	iotcon_resource_interfaces_destroy(ifaces);

	return 0;
}

/**
* @function 		IotconCreateLedResource
* @description	 	create led resource
* @parameter		NA
* @return 			NA
*/
bool IotconCreateLedResource(void)
{
	int nIotconTimeoutId = 0;
	g_bCheckCb = false;
	iotcon_resource_types_h hLedTypes = NULL;
	IotconDestroyRes();

	int nRet = iotcon_resource_types_create(&hLedTypes);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_create", IotConGetError(nRet));
	CHECK_HANDLE(hLedTypes,"iotcon_resource_types_create");

	nRet = iotcon_resource_types_add(hLedTypes, REMOTE_RESOURCE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_add", IotConGetError(nRet),iotcon_resource_types_destroy(hLedTypes));
	g_nCheckAPICb = 0;

	iotcon_resource_interfaces_h ifaces;

	nRet = iotcon_resource_interfaces_create(&ifaces);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_create", IotConGetError(nRet),iotcon_resource_types_destroy(hLedTypes));

	nRet = iotcon_resource_interfaces_add(ifaces, IOTCON_INTERFACE_BATCH);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_add", IotConGetError(nRet),iotcon_resource_types_destroy(hLedTypes);iotcon_resource_interfaces_destroy(ifaces));

	nRet = iotcon_resource_create(REMOTE_RESOURCE_LED,hLedTypes,ifaces,(IOTCON_RESOURCE_DISCOVERABLE |IOTCON_RESOURCE_OBSERVABLE), IotconRequestHandlerCB, NULL, &g_hLedResource);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_create", IotConGetError(nRet),iotcon_resource_types_remove(hLedTypes, REMOTE_RESOURCE); iotcon_resource_types_destroy(hLedTypes);iotcon_resource_interfaces_destroy(ifaces));
	CHECK_HANDLE(g_hLedResource,"iotcon_resource_create");

	RUN_POLLING_LOOP;

	iotcon_resource_types_destroy(hLedTypes);
	iotcon_resource_interfaces_destroy(ifaces);

	return 0;
}

/**
 * @function 		ITs_iotcon_resource_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_resource_startup(void)
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
 * @function 		ITs_iotcon_resource_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_resource_cleanup(void)
{
	#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_iotcon_resource_cleanup\\n", __LINE__, API_NAMESPACE);
#endif

	icitc_free_client_ipv4_address();

	if (g_bIotconConnect)
	{
		iotcon_deinitialize();
		return;
	}
	return;

}

/** @addtogroup itc-iotcon-testcases
*  @brief 		Integration testcases for module iotcon
*  @ingroup 	itc-iotcon
*  @{
*/

//& type: auto
//& purpose:  scenario to create & destroy resource
/**
* @testcase 			ITc_iotcon_resource_create_destroy_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to create & destroy resource
* @scenario				create resource \n
* 						destroy resource\n
* @apicovered			iotcon_resource_create, iotcon_resource_destroy
* @passcase				if iotcon_resource_create and iotcon_resource_destroy passes
* @failcase				if iotcon_resource_create or iotcon_resource_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_resource_create_destroy_p(void)
{
	START_TEST;
	int nRet = IotconCreateLightResource();
	if ( nRet != IOTCON_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] IotconCreateLightResource error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if (g_hLightResource)
	{
		nRet = iotcon_resource_destroy(g_hLightResource);
		PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_destroy", IotConGetError(nRet));
		g_hLightResource = NULL;

	}
	if (g_hLedResource)
	{
		nRet = iotcon_resource_destroy(g_hLedResource);
		PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_destroy", IotConGetError(nRet));
		g_hLedResource = NULL;
	}

    return 0;
}

//& type: auto
//& purpose:  scenario to bind an interface to resource
/**
* @testcase 			ITc_iotcon_resource_bind_interface_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to bind an interface to resource
* @scenario				create resource \n
*						bind resource interface \n
* 						destroy resource\n
* @apicovered			iotcon_resource_bind_interface
* @passcase				if iotcon_resource_bind_interface passes
* @failcase				if iotcon_resource_bind_interface fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_resource_bind_interface_p(void)
{
	START_TEST;
	int nRet = IotconCreateLightResource();
	if ( nRet != IOTCON_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] IotconCreateLightResource error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	nRet = iotcon_resource_bind_interface(g_hLightResource, IOTCON_INTERFACE_DEFAULT);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_bind_interface", IotConGetError(nRet),IotconDestroyRes());
	IotconDestroyRes();

    return 0;
}

//& type: auto
//& purpose:  scenario to bind an type to resource
/**
* @testcase 			ITc_iotcon_resource_bind_type_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to bind an type to resource
* @scenario				create resource \n
*						bind resource type \n
* 						destroy resource\n
* @apicovered			iotcon_resource_bind_type
* @passcase				if iotcon_resource_bind_type passes
* @failcase				if iotcon_resource_bind_type fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_resource_bind_type_p(void)
{
	START_TEST;
	int nRet = IotconCreateLightResource();
	if ( nRet != IOTCON_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] IotconCreateLightResource error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	nRet = iotcon_resource_bind_type(g_hLightResource, LIGHT_RESOURCE2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_bind_type", IotConGetError(nRet),IotconDestroyRes());
	IotconDestroyRes();

    return 0;
}

//& type: auto
//& purpose:  scenario to set request handler of resource
/**
* @testcase 			ITc_iotcon_resource_set_request_handler_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to set request handler of resource
* @scenario				create resource \n
*						set request handler \n
* 						destroy resource\n
* @apicovered			iotcon_resource_set_request_handler
* @passcase				if iotcon_resource_set_request_handler passes
* @failcase				if iotcon_resource_set_request_handler fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_resource_set_request_handler_p(void)
{
	START_TEST;
	int nRet = CreateAndFindResource(RESOURCE_SET_REQUEST_HANDLER);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateAndFindResource", IotConGetError(nRet));
	return 0;
}


//& type: auto
//& purpose:  scenario to binds and unbinds a child resource into the parent resource
/**
* @testcase 			ITc_iotcon_resource_bind_unbind_child_resource_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to binds  and unbinds a child resource into the parent resource
* @scenario				create resource \n
*						binds  and unbinds a child resource into the parent resource \n
* 						destroy resource\n
* @apicovered			iotcon_resource_bind_child_resource , iotcon_resource_unbind_child_resource
* @passcase				if iotcon_resource_bind_child_resource & iotcon_resource_unbind_child_resource passes
* @failcase				if iotcon_resource_bind_child_resource & iotcon_resource_unbind_child_resource fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_resource_bind_unbind_child_resource_p(void)
{
	START_TEST;
	int nRet = IotconCreateResourceLight();
	if ( nRet != IOTCON_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] IotconCreateLightResource error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false != IotconCreateResourceLED() )
	{
		FPRINTF("[Line : %d][%s] IotconCreateLedResource error\\n", __LINE__, API_NAMESPACE);
		IotconDestroyRes();
		return 1;
	}
	nRet = iotcon_resource_bind_child_resource(g_hLightResource, g_hLedResource);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_bind_child_resource", IotConGetError(nRet),IotconDestroyRes());

	nRet = iotcon_resource_unbind_child_resource(g_hLightResource, g_hLedResource);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_unbind_child_resource", IotConGetError(nRet),IotconDestroyRes());

	IotconDestroyRes();

    return 0;
}

//& type: auto
//& purpose:  scenario to get number of childrens of resource
/**
* @testcase 			ITc_iotcon_resource_get_child_count_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get number of childrens of resource
* @scenario				create resource \n
*						get number of childrens of resource \n
* 						destroy resource\n
* @apicovered			ITc_iotcon_resource_get_child_count_p
* @passcase				if ITc_iotcon_resource_get_child_count_p passes
* @failcase				if ITc_iotcon_resource_get_child_count_p fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_resource_get_child_count_p(void)
{
	START_TEST;
	unsigned int nNumber = 0;
	int nRet = IotconCreateResourceLight();
	if ( nRet != IOTCON_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] IotconCreateLightResource error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( false != IotconCreateResourceLED() )
	{
		FPRINTF("[Line : %d][%s] IotconCreateLedResource error\\n", __LINE__, API_NAMESPACE);
		IotconDestroyRes();
		return 1;
	}
	nRet = iotcon_resource_bind_child_resource(g_hLightResource, g_hLedResource);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_bind_child_resource", IotConGetError(nRet),IotconDestroyRes());

	nRet = iotcon_resource_get_child_count(g_hLightResource, &nNumber);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_get_child_count", IotConGetError(nRet),IotconDestroyRes());

	if ( nNumber != 1 )
	{
		FPRINTF("[Line : %d][%s] no of children not matching nAddNumber != nNumber\\n", __LINE__, API_NAMESPACE);
		IotconDestroyRes();
		return 1;
	}
	nRet = iotcon_resource_unbind_child_resource(g_hLightResource, g_hLedResource);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_unbind_child_resource", IotConGetError(nRet),IotconDestroyRes());
	IotconDestroyRes();
    return 0;
}

//& type: auto
//& purpose:  scenario to get nth child of resource
/**
* @testcase 			ITc_iotcon_resource_get_nth_child_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get nth child of resource
* @scenario				create resource \n
*						get nth child of resource \n
* 						destroy resource\n
* @apicovered			iotcon_resource_get_nth_child
* @passcase				if iotcon_resource_get_nth_child passes
* @failcase				if iotcon_resource_get_nth_child fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_resource_get_nth_child_p(void)
{
	START_TEST;
	int nRet = IotconCreateResourceLight();
	if ( nRet != IOTCON_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] IotconCreateLightResource error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( false != IotconCreateResourceLED() )
	{
		FPRINTF("[Line : %d][%s] IotconCreateLedResource error\\n", __LINE__, API_NAMESPACE);
		IotconDestroyRes();
		return 1;
	}
	nRet = iotcon_resource_bind_child_resource(g_hLightResource, g_hLedResource);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_bind_child_resource", IotConGetError(nRet),IotconDestroyRes());

	nRet = iotcon_resource_get_nth_child(g_hLightResource, 0, &g_hLedResource);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_get_nth_child", IotConGetError(nRet),IotconDestroyRes());
	CHECK_HANDLE(g_hLedResource,"iotcon_resource_get_nth_child");

	nRet = iotcon_resource_unbind_child_resource(g_hLightResource, g_hLedResource);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_unbind_child_resource", IotConGetError(nRet),IotconDestroyRes());
	IotconDestroyRes();
    return 0;
}

//& type: auto
//& purpose:  scenario to get uri path of resource
/**
* @testcase 			ITc_iotcon_resource_get_uri_path_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get uri path of resource
* @scenario				create resource \n
*						get uri path of resource \n
* 						destroy resource\n
* @apicovered			iotcon_resource_get_uri_path
* @passcase				if iotcon_resource_get_uri_path passes
* @failcase				if iotcon_resource_get_uri_path fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_resource_get_uri_path_p(void)
{
	START_TEST;
	char *uri = NULL;
	int nRet = IotconCreateLightResource();
	if ( nRet != IOTCON_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] IotconCreateLightResource error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	nRet = iotcon_resource_get_uri_path(g_hLightResource, &uri);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_get_uri_path", IotConGetError(nRet),IotconDestroyRes());
	if (strcmp(REMOTE_RESOURCE_LIGHT, uri) != 0)
	{
	    IotconDestroyRes();
		//free(uri);
		return 1;
	}
	IotconDestroyRes();
	//free(uri);
    return 0;
}

//& type: auto
//& purpose:  scenario to get types of resource
/**
* @testcase 			ITc_iotcon_resource_get_types_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get types of resource
* @scenario				create resource \n
*						get types of resource \n
* 						destroy resource\n
* @apicovered			iotcon_resource_get_types
* @passcase				if iotcon_resource_get_types passes
* @failcase				if iotcon_resource_get_types fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_resource_get_types_p(void)
{
	START_TEST;
	iotcon_resource_types_h hTypes = NULL;
    int nRet = IotconCreateLightResource();
	if ( nRet != IOTCON_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] IotconCreateLightResource error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	nRet = iotcon_resource_get_types(g_hLightResource, &hTypes);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_get_types", IotConGetError(nRet),IotconDestroyRes());
	CHECK_HANDLE(hTypes,"iotcon_resource_get_types");

	IotconDestroyRes();
    return 0;
}

//& type: auto
//& purpose:  scenario to get interfaces of resource
/**
* @testcase 			ITc_iotcon_resource_get_interfaces_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get interfaces of resource
* @scenario				create resource \n
*						get interfaces of resource \n
* 						destroy resource\n
* @apicovered			iotcon_resource_get_interfaces
* @passcase				if iotcon_resource_get_interfaces passes
* @failcase				if iotcon_resource_get_interfaces fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_resource_get_interfaces_p(void)
{
	START_TEST;

	iotcon_resource_interfaces_h hIface = NULL;

	int nRet = IotconCreateResourceLight();
	if ( nRet != IOTCON_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] IotconCreateLightResource error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}


	nRet = iotcon_resource_get_interfaces(g_hLightResource, &hIface);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_get_interfaces", IotConGetError(nRet),IotconDestroyRes());

	if(hIface == NULL)
	{
		IotconDestroyRes();
		return 1;
	}
	IotconDestroyRes();
    return 0;
}

//& type: auto
//& purpose:  scenario to get properties of resource
/**
* @testcase 			ITc_iotcon_resource_get_policies_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get properties of resource
* @scenario				create resource \n
*						iotcon_resource_get_policies \n
* 						destroy resource\n
* @apicovered			iotcon_resource_get_policies
* @passcase				if iotcon_resource_get_policies passes
* @failcase				if iotcon_resource_get_policies fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_resource_get_policies_p(void)
{
	START_TEST;
	uint8_t nProperties = 0;
    int nRet = IotconCreateLightResource();
	if ( nRet != IOTCON_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] IotconCreateLightResource error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	nRet = iotcon_resource_get_policies(g_hLightResource, &nProperties);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_get_policies", IotConGetError(nRet),IotconDestroyRes());
	if ((IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE) != nProperties)
	{
		IotconDestroyRes();
		return 1;
	}
	IotconDestroyRes();
    return 0;
}

//& type: auto
//& purpose:  scenario to create and destroy resource types
/**
* @testcase 			ITc_iotcon_resource_types_create_destroy_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to create and destroy resource types
* @scenario				create resource type \n
* 						destroy resource type\n
* @apicovered			iotcon_resource_types_create , iotcon_resource_types_destroy
* @passcase				if iotcon_resource_types_create & iotcon_resource_types_destroy passes
* @failcase				if iotcon_resource_types_create & iotcon_resource_types_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_resource_types_create_destroy_p(void)
{
	START_TEST;

	iotcon_resource_types_h hTypes = NULL;

	int nRet = iotcon_resource_types_create(&hTypes);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_create", IotConGetError(nRet));
	CHECK_HANDLE(hTypes,"iotcon_resource_types_create");

	iotcon_resource_types_destroy(hTypes);

	return 0;
}

//& type: auto
//& purpose:  scenario to add and remove resource types
/**
* @testcase 			ITc_iotcon_resource_types_add_remove_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to add and remove resource types
* @scenario				create resource \n
*						add and remove resource types \n
* 						destroy resource\n
* @apicovered			iotcon_resource_types_add , iotcon_resource_types_remove
* @passcase				if iotcon_resource_types_add & iotcon_resource_types_remove passes
* @failcase				if iotcon_resource_types_add & iotcon_resource_types_remove fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_resource_types_add_remove_p(void)
{
	START_TEST;

	iotcon_resource_types_h hTypes = NULL;

	int nRet = iotcon_resource_types_create(&hTypes);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_create", IotConGetError(nRet));
	CHECK_HANDLE(hTypes,"iotcon_resource_types_create");

	nRet = iotcon_resource_types_add(hTypes, REMOTE_RESOURCE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_add", IotConGetError(nRet),iotcon_resource_types_destroy(hTypes));

	nRet = iotcon_resource_types_remove(hTypes, REMOTE_RESOURCE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_remove", IotConGetError(nRet),iotcon_resource_types_destroy(hTypes));

	iotcon_resource_types_destroy(hTypes);

	return 0;
}

//& type: auto
//& purpose:  scenario to gets all of the resource types of the list by invoking the callback function.
/**
* @testcase 			ITc_iotcon_resource_types_foreach_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to gets all of the resource types of the list by invoking the callback function.
* @scenario				create resource \n
*						gets all of the resource types of the list \n
* 						destroy resource\n
* @apicovered			iotcon_resource_types_foreach
* @passcase				if iotcon_resource_types_foreach passes
* @failcase				if iotcon_resource_types_foreach fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_resource_types_foreach_p(void)
{
	START_TEST;
	iotcon_resource_types_h hTypes = NULL;
	int nCount =0;
	g_bCheckCb = false;

	int nRet = iotcon_resource_types_create(&hTypes);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_create", IotConGetError(nRet));
	CHECK_HANDLE(hTypes,"iotcon_resource_types_create");

	nRet = iotcon_resource_types_add(hTypes, REMOTE_RESOURCE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_add", IotConGetError(nRet),iotcon_resource_types_destroy(hTypes));

	nRet = iotcon_resource_types_add(hTypes, LIGHT_RESOURCE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_add", IotConGetError(nRet),iotcon_resource_types_destroy(hTypes));

	nRet = iotcon_resource_types_foreach(hTypes, IotconResourceTypesForeachCB, &nCount);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_foreach", IotConGetError(nRet),iotcon_resource_types_destroy(hTypes));


	if(g_bCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] callback not invoked : \\n", __LINE__, API_NAMESPACE );
		nRet = iotcon_resource_types_remove(hTypes, REMOTE_RESOURCE);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_remove", IotConGetError(nRet),iotcon_resource_types_destroy(hTypes));
		nRet = iotcon_resource_types_remove(hTypes, LIGHT_RESOURCE);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_remove", IotConGetError(nRet),iotcon_resource_types_destroy(hTypes));
		iotcon_resource_types_destroy(hTypes);
		return 1;
	}
	if (nCount != VAL3)
	{
		FPRINTF("[Line : %d][%s] value mismatch \\n", __LINE__, API_NAMESPACE );
		nRet = iotcon_resource_types_remove(hTypes, REMOTE_RESOURCE);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_remove", IotConGetError(nRet),iotcon_resource_types_destroy(hTypes));
		nRet = iotcon_resource_types_remove(hTypes, LIGHT_RESOURCE);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_remove", IotConGetError(nRet),iotcon_resource_types_destroy(hTypes));
		iotcon_resource_types_destroy(hTypes);
		return 1;
	}
	nRet = iotcon_resource_types_remove(hTypes, REMOTE_RESOURCE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_remove", IotConGetError(nRet),iotcon_resource_types_destroy(hTypes));
	nRet = iotcon_resource_types_remove(hTypes, LIGHT_RESOURCE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_remove", IotConGetError(nRet),iotcon_resource_types_destroy(hTypes));
	iotcon_resource_types_destroy(hTypes);
	return 0;
}

//& type: auto
//& purpose:  scenario to binds and unbinds a child resource into the parent resource
/**
* @testcase 			ITc_iotcon_resource_types_clone_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to binds  and unbinds a child resource into the parent resource
* @scenario				create resource \n
*						binds  and unbinds a child resource into the parent resource \n
* 						destroy resource\n
* @apicovered			iotcon_resource_types_clone // missing API
* @passcase				if iotcon_resource_types_clone passes
* @failcase				if iotcon_resource_types_clone fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_resource_types_clone_p(void)
{
	START_TEST;

	iotcon_resource_types_h hTypes1, hTypes2;

	int nRet = iotcon_resource_types_create(&hTypes1);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_create", IotConGetError(nRet));
	CHECK_HANDLE(hTypes1,"iotcon_resource_types_create");

	nRet = iotcon_resource_types_add(hTypes1, REMOTE_RESOURCE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_foreach", IotConGetError(nRet),iotcon_resource_types_destroy(hTypes1));

	nRet = iotcon_resource_types_clone(hTypes1, &hTypes2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_foreach", IotConGetError(nRet),iotcon_resource_types_remove(hTypes1, REMOTE_RESOURCE);iotcon_resource_types_destroy(hTypes1));
	CHECK_HANDLE(hTypes2,"iotcon_resource_types_clone");

	nRet = iotcon_resource_types_remove(hTypes1, REMOTE_RESOURCE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_remove", IotConGetError(nRet),iotcon_resource_types_destroy(hTypes1);iotcon_resource_types_destroy(hTypes2));
	iotcon_resource_types_destroy(hTypes2);
	iotcon_resource_types_destroy(hTypes1);

	return 0;
}

//& type: auto
//& purpose:  scenario to notifies specific clients that resource's attributes have changed.
/**
* @testcase 			ITc_iotcon_resource_find_notify_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to notifies specific clients that resource's attributes have changed
* @scenario				create resource and resource types \n
*						iotcon_resource_notify \n
* 						destroy resource
* @apicovered			iotcon_resource_notify, iotcon_find_resource
* @passcase				if iotcon_resource_notify passes
* @failcase				if iotcon_resource_notify fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_resource_notify_p(void)
{
	START_TEST;

	int nRet = CreateAndFindResource(RESOURCE_NOTIFY);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "CreateAndFindResource", IotConGetError(nRet));

	return 0;
}

/** @} */
/** @} */
