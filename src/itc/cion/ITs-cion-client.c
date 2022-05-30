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
#include "ITs-cion-common.h"

//& set: Cion

/** @addtogroup itc-cion
*  @ingroup itc
*  @{
*/
bool g_bCallbackCalledDiscover;
bool g_bCallbackCalledResult;

struct cbdata {
	cion_client_h client;
	bool connected;
};
static GMainLoop *main_loop;
static guint source_id;
static gboolean __timeout_cb(gpointer data)
{
	g_main_loop_quit(main_loop);
	return FALSE;
}

static void RunPollingLoop(void) {
	main_loop = g_main_loop_new(NULL, FALSE);
	source_id = g_timeout_add(60000, __timeout_cb, NULL);\
	g_main_loop_run(main_loop);\
	g_source_remove(source_id);
	main_loop = NULL;
}

static void StopPollingLoop(void) {
	sleep(1);
	g_source_remove(source_id);
	g_main_loop_quit(main_loop);
}

struct send_data {
	cion_client_h client;
	unsigned char *return_data;
	unsigned int return_data_size;
	int ret;
};

static gpointer SendDataThread(gpointer data)
{
	FPRINTF("[Line : %d][%s] SendDataThread called\\n", __LINE__, API_NAMESPACE);
	unsigned char str[] ="data_test";
	struct send_data *send_data = (struct send_data *)data;

	send_data->ret = cion_client_send_data(send_data->client, str, strlen((const char*)str),5000, &send_data->return_data, &send_data->return_data_size);
	StopPollingLoop();

	return NULL;
}

/**
* @function 		ServerDataReceivedCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, const unsigned char *data,unsigned int data_size, unsigned char **return_data,unsigned int *return_data_size, void *user_data
* @return 			NA
*/
void ServerDataReceivedCB(const char *service_name,const cion_peer_info_h peer_info, const unsigned char *data,unsigned int data_size, unsigned char **return_data,unsigned int *return_data_size, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback ServerDataReceivedCB called\\n", __LINE__, API_NAMESPACE);
	char pszStr[] ="data_result";
	*return_data = (unsigned char *)strdup(pszStr);
	*return_data_size = strlen(pszStr);
}

/**
* @function 		ServerConnectionRequestCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ServerConnectionRequestCB(const char *service_name,const cion_peer_info_h peer_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback ServerConnectionRequestCB called\\n", __LINE__, API_NAMESPACE);
	int nRetVal = -1;
	cion_server_h hServer = (cion_server_h)user_data;

	nRetVal = cion_server_accept(hServer, peer_info);
	if (nRetVal != CION_ERROR_NONE)
		FPRINTF("[Line : %d][%s] Failed to accept client\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ClientServerDiscoveredCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ClientServerDiscoveredCB(const char *service_name,const cion_peer_info_h peer_info, void *user_data)
{
	sleep(2);
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] Callback ClientServerDiscoveredCB called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ClientServerDiscoveredCB2
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ClientServerDiscoveredCB2(const char *service_name,const cion_peer_info_h peer_info, void *user_data)
{
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] Callback ClientServerDiscoveredCB2 called\\n", __LINE__, API_NAMESPACE);
	int nRetVal = -1;
	cion_peer_info_h *pszPeer = (cion_peer_info_h *)user_data;

	FPRINTF("[Line : %d][%s] server discovered\\n", __LINE__, API_NAMESPACE);
	nRetVal = cion_peer_info_clone(peer_info, pszPeer);
	if (nRetVal != CION_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] Failed cion_client_connect\\n", __LINE__, API_NAMESPACE);
	}

	StopPollingLoop();
}

/**
* @function 		ClientServerDiscoveredCB3
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ClientServerDiscoveredCB3(const char *service_name,const cion_peer_info_h peer_info, void *user_data)
{
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] Callback ClientServerDiscoveredCB3 called\\n", __LINE__, API_NAMESPACE);
	int nRetVal = -1;
	struct cbdata *cbdata = (struct cbdata *)user_data;

	FPRINTF("[Line : %d][%s] server discovered\\n", __LINE__, API_NAMESPACE);
	nRetVal =  cion_client_connect(cbdata->client, peer_info);
	if (nRetVal != CION_ERROR_NONE)
		FPRINTF("[Line : %d][%s] Failed cion_client_connect\\n", __LINE__, API_NAMESPACE);

	StopPollingLoop();
}

/**
* @function 		ClientServerDiscoveredCB4
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ClientServerDiscoveredCB4(const char *service_name,const cion_peer_info_h peer_info, void *user_data)
{
	g_bCallbackCalledDiscover = true;
	FPRINTF("[Line : %d][%s] Callback ClientServerDiscoveredCB4 called\\n", __LINE__, API_NAMESPACE);
	int nRetVal = -1;
	struct cbdata *cbdata = (struct cbdata *)user_data;

	FPRINTF("[Line : %d][%s] server discovered\\n", __LINE__, API_NAMESPACE);
	nRetVal =  cion_client_connect(cbdata->client, peer_info);
	if (nRetVal != CION_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] Failed cion_client_connect\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		cbdata->connected = true;
	}
	StopPollingLoop();
}

/**
* @function 		ClientDisconnectedCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ClientDisconnectedCB(const char *service_name,const cion_peer_info_h peer_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback ClientDisconnectedCB called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ClientPayloadReceivedCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, const cion_payload_h payload,cion_payload_transfer_status_e status,void *user_data
* @return 			NA
*/
static void ClientPayloadReceivedCB(const char *service_name,const cion_peer_info_h peer_info, const cion_payload_h payload,cion_payload_transfer_status_e status,void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback ClientPayloadReceivedCB called\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ClientConnectionResultCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info,const cion_connection_result_h result, void *user_data
* @return 			NA
*/
static void ClientConnectionResultCB(const char *service_name,const cion_peer_info_h peer_info,const cion_connection_result_h result, void *user_data)
{
	cion_connection_status_e status;
	int nRetVal;

	nRetVal = cion_connection_result_get_status(result, &status);

	FPRINTF("[Line : %d][%s] Callback ClientConnectionResultCB called[%d][%d]\\n", __LINE__, API_NAMESPACE, nRetVal, status);
	sleep(2);

	if (status == CION_CONNECTION_STATUS_OK)
		g_bCallbackCalledResult = true;

	StopPollingLoop();
}

/**
* @function 		ClientConnectionResultCBAddRemove
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info,const cion_connection_result_h result, void *user_data
* @return 			NA
*/
static void ClientConnectionResultCBAddRemove(const char *service_name,const cion_peer_info_h peer_info,const cion_connection_result_h result, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback ClientConnectionResultCBAddRemove called\\n", __LINE__, API_NAMESPACE);
}

/**
 * @function 		ITs_cion_client_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_cion_client_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	return;
}


/**
 * @function 		ITs_cion_client_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_cion_client_cleanup(void)
{
	return;
}

/** @addtogroup itc-cion-testcases
*  @brief 		Integration testcases for module cion
*  @ingroup 	itc-cion
*  @{
*/

//& purpose:  Creates and Destroy a Cion client handle
//& type: auto
/**
* @testcase 			ITc_cion_client_create_destroy_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates and Destroy a Cion client handle
* @scenario				Creates and Destroy a Cion client handle
* @apicovered			cion_client_create,cion_client_destroy
* @passcase				If cion_client_create,cion_client_destroy is successfull
* @failcase 			If cion_client_create,cion_client_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_client_create_destroy_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_client_h hClient = NULL;

	nRetVal = cion_client_create(&hClient, "ITc_cion_client_create_destroy_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_create", CionGetError(nRetVal));
	CHECK_HANDLE(hClient,"cion_client_create");

	nRetVal = cion_client_destroy(hClient);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose: Tries and Stop to discover a Cion server.
//& type: auto
/**
* @testcase 			ITc_cion_client_try_stop_discovery_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Tries and Stop to discover a Cion server.
* @scenario				Tries and Stop to discover a Cion server.
* @apicovered			cion_client_try_discovery,cion_client_stop_discovery
* @passcase				If cion_client_try_discovery,cion_client_stop_discovery is successfull
* @failcase 			If cion_client_try_discovery,cion_client_stop_discovery fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_client_try_stop_discovery_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_client_h hClient = NULL;
	cion_server_h hServer = NULL;
	g_bCallbackCalled = false;
	int nTimeoutId = -1;
	struct send_data cbdata = { 0 };

	nRetVal = cion_server_create(&hServer, "ITc_cion_client_try_stop_discovery_p","ITc_cion_client_try_stop_discovery_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_client_create(&hClient, "ITc_cion_client_try_stop_discovery_p",NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_create", CionGetError(nRetVal));
	CHECK_HANDLE(hClient,"cion_client_create");

	nRetVal = cion_server_set_data_received_cb(hServer, ServerDataReceivedCB, NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_set_data_received_cb", CionGetError(nRetVal));

	nRetVal = cion_server_listen(hServer, ServerConnectionRequestCB,hServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_listen", CionGetError(nRetVal));

	nRetVal = cion_client_add_connection_result_cb(hClient,ClientConnectionResultCB, NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_add_connection_result_cb", CionGetError(nRetVal));

	cbdata.client = hClient;
	nRetVal = cion_client_try_discovery(hClient, ClientServerDiscoveredCB4,&cbdata);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_try_discovery", CionGetError(nRetVal));

	RunPollingLoop();
	if(g_bCallbackCalledDiscover != true)
	{
		FPRINTF("[Line : %d][%s] Callback ClientServerDiscoveredCB4 not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_try_discovery", CionGetError(nRetVal));

	nRetVal = cion_client_stop_discovery(hClient);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_stop_discovery", CionGetError(nRetVal));

	nRetVal = cion_client_destroy(hClient);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_client_destroy", CionGetError(nRetVal));

	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose: Tries to connect and disconnnect to the Cion server.
//& type: auto
/**
* @testcase 			ITc_cion_client_connect_disconnect_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Tries to connect and disconnnect to the Cion server.
* @scenario				Tries to connect and disconnnect to the Cion server.
* @apicovered			cion_client_connect,cion_client_disconnect
* @passcase				If cion_client_connect,cion_client_disconnect is successfull
* @failcase 			If cion_client_connect,cion_client_disconnect fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_client_connect_disconnect_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_client_h hClient = NULL;
	cion_server_h hServer = NULL;
	cion_peer_info_h hPeer = NULL;
	g_bCallbackCalled = false;
	int nTimeoutId = -1;

	nRetVal = cion_server_create(&hServer, "ITc_cion_client_connect_disconnect_p","ITc_cion_client_connect_disconnect_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_client_create(&hClient, "ITc_cion_client_connect_disconnect_p",NULL);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_create", CionGetError(nRetVal),cion_server_destroy(hServer));
	CHECK_HANDLE(hClient,"cion_client_create");

	nRetVal = cion_server_listen(hServer, ServerConnectionRequestCB,hServer);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_server_listen", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	nRetVal = cion_client_try_discovery(hClient, ClientServerDiscoveredCB2,&hPeer);
	RunPollingLoop();
	if(g_bCallbackCalled != true)
	{
		FPRINTF("[Line : %d][%s] Callback ClientServerDiscoveredCB2 not invoked\\n", __LINE__, API_NAMESPACE);
		cion_server_destroy(hServer);
		cion_client_destroy(hClient);
		return 1;
	}
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_try_discovery", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));
	CHECK_HANDLE(hPeer,"cion_client_try_discovery");

	nRetVal = cion_client_connect(hClient, hPeer);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_connect", CionGetError(nRetVal),cion_peer_info_destroy(hPeer);cion_client_stop_discovery(hClient);cion_client_destroy(hClient);cion_server_destroy(hServer));

	nRetVal = cion_client_disconnect(hClient);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_disconnect", CionGetError(nRetVal),cion_peer_info_destroy(hPeer);cion_client_stop_discovery(hClient);cion_client_destroy(hClient);cion_server_destroy(hServer));

	nRetVal = cion_peer_info_destroy(hPeer);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_peer_info_destroy", CionGetError(nRetVal));
	hPeer = NULL;

	nRetVal = cion_client_stop_discovery(hClient);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_client_stop_discovery", CionGetError(nRetVal));

	nRetVal = cion_client_destroy(hClient);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_client_destroy", CionGetError(nRetVal));

	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose:  Sends the data.
//& type: auto
/**
* @testcase 			ITc_cion_client_send_data_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sends the data.
* @scenario				Sends the data.
* @apicovered			cion_client_send_data
* @passcase				If cion_client_send_data is successfull
* @failcase 			If cion_client_send_data fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_client_send_data_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_client_h hClient;
	cion_server_h hServer;
	g_bCallbackCalled = false;
	g_bCallbackCalledDiscover = false;
	g_bCallbackCalledResult = false;
	int nTimeoutId = -1;

	GThread *thread;
	struct send_data cbdata = { 0 };
	struct send_data send_data = { 0 };

	nRetVal = cion_server_create(&hServer,"ITc_cion_client_send_data_p","ITc_cion_client_send_data_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_client_create(&hClient,"ITc_cion_client_send_data_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_create", CionGetError(nRetVal));
	CHECK_HANDLE(hClient,"cion_client_create");

	nRetVal = cion_server_set_data_received_cb(hServer, ServerDataReceivedCB, NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_set_data_received_cb", CionGetError(nRetVal));

	nRetVal = cion_server_listen(hServer, ServerConnectionRequestCB,hServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_listen", CionGetError(nRetVal));

	nRetVal = cion_client_add_connection_result_cb(hClient, ClientConnectionResultCB, NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_add_connection_result_cb", CionGetError(nRetVal));

	cbdata.client = hClient;
	nRetVal = cion_client_try_discovery(hClient, ClientServerDiscoveredCB4,&cbdata);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_try_discovery", CionGetError(nRetVal));

	RunPollingLoop();
	if(g_bCallbackCalledDiscover != true)
	{
		FPRINTF("[Line : %d][%s] Callback ClientServerDiscoveredCB4 not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	RunPollingLoop();
	if(g_bCallbackCalledResult != true)
	{
		FPRINTF("[Line : %d][%s] Callback ClientConnectionResultCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	send_data.client = hClient;
	thread = g_thread_new("send_data", SendDataThread, &send_data);

	RunPollingLoop();
	PRINT_RESULT(CION_ERROR_NONE, send_data.ret, "cion_client_send_data", CionGetError(send_data.ret));
	if(strncmp((const char *)send_data.return_data, "data_result",send_data.return_data_size) != 0)
	{
		FPRINTF("[Line : %d][%s] data is not correct\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	FREE_MEMORY(send_data.return_data);
	g_thread_unref(thread);

	nRetVal = cion_client_destroy(hClient);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_client_destroy", CionGetError(nRetVal));

	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose: Sends the payload asynchronously.
//& type: auto
/**
* @testcase 			ITc_cion_client_send_payload_async_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sends the payload asynchronously.
* @scenario				Sends the payload asynchronously.
* @apicovered			cion_client_send_payload_async
* @passcase				If cion_client_send_payload_async is successfull
* @failcase 			If cion_client_send_payload_async fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_client_send_payload_async_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_client_h hClient;
	cion_server_h hServer;
	cion_payload_h hPayload;
	unsigned char pszData[] = "ITc_cion_client_send_payload_async_p";
	struct cbdata cbdata;
	g_bCallbackCalled = false;
	g_bCallbackCalledResult = false;
	int nTimeoutId = -1;

	nRetVal = cion_server_create(&hServer,"ITc_cion_client_send_payload_async_p","ITc_cion_client_send_payload_async_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_client_create(&hClient,"ITc_cion_client_send_payload_async_p", NULL);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_create", CionGetError(nRetVal),cion_server_destroy(hServer));
	CHECK_HANDLE(hClient,"cion_client_create");

	nRetVal = cion_server_listen(hServer, ServerConnectionRequestCB,hServer);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_server_listen", CionGetError(nRetVal),cion_server_destroy(hServer);cion_client_destroy(hClient));

	cbdata.client = hClient;
	cbdata.connected = false;

	nRetVal = cion_client_try_discovery(hClient, ClientServerDiscoveredCB3,&cbdata);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_try_discovery", CionGetError(nRetVal),cion_server_destroy(hServer);cion_client_destroy(hClient));

	nRetVal = cion_client_add_connection_result_cb(hClient,ClientConnectionResultCB, NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_add_connection_result_cb", CionGetError(nRetVal));

	RunPollingLoop();
	if(g_bCallbackCalled != true)
	{
		FPRINTF("[Line : %d][%s] Callback ClientServerDiscoveredCB2 not invoked\\n", __LINE__, API_NAMESPACE);
		cion_server_destroy(hServer);
		cion_client_destroy(hClient);
		return 1;
	}

	RunPollingLoop();
	if(g_bCallbackCalledResult != true)
	{
		FPRINTF("[Line : %d][%s] Callback ClientConnectionResultCB not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = cion_payload_create(&hPayload, CION_PAYLOAD_TYPE_DATA);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_payload_create", CionGetError(nRetVal),cion_server_destroy(hServer);cion_client_destroy(hClient));
	CHECK_HANDLE(hPayload,"cion_payload_create");

	nRetVal = cion_payload_set_data(hPayload, pszData, sizeof(pszData));
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_payload_set_data", CionGetError(nRetVal),cion_server_destroy(hServer);cion_client_destroy(hClient));

	nRetVal = cion_client_send_payload_async(hClient, hPayload, NULL, NULL);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_send_payload_async", CionGetError(nRetVal),cion_server_destroy(hServer);cion_client_destroy(hClient));

	nRetVal = cion_client_destroy(hClient);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_client_destroy", CionGetError(nRetVal));

	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose: Adds and remove callback function for connection result.
//& type: auto
/**
* @testcase 			ITc_cion_client_add_remove_connection_result_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Adds and remove callback function for connection result.
* @scenario				Adds and remove callback function for connection result.
* @apicovered			cion_client_add_connection_result_cb,cion_client_remove_connection_result_cb
* @passcase				If cion_client_add_connection_result_cb,cion_client_remove_connection_result_cb is successfull
* @failcase 			If cion_client_add_connection_result_cb,cion_client_remove_connection_result_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_client_add_remove_connection_result_cb_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_client_h hClient;

	nRetVal = cion_client_create(&hClient,"ITc_cion_client_add_remove_connection_result_cb_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hClient,"cion_server_create");

	nRetVal = cion_client_add_connection_result_cb(hClient,ClientConnectionResultCBAddRemove, NULL);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_add_connection_result_cb", CionGetError(nRetVal),cion_client_destroy(hClient));

	nRetVal = cion_client_remove_connection_result_cb(hClient,ClientConnectionResultCBAddRemove);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_client_remove_connection_result_cb", CionGetError(nRetVal));

	nRetVal = cion_client_destroy(hClient);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_client_destroy", CionGetError(nRetVal));

	return 0;
}
//& purpose:  Add and Removes callback function to receive payload.
//& type: auto
/**
* @testcase 			ITc_cion_client_add_remove_payload_received_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Add and Removes callback function to receive payload.
* @scenario				Add and Removes callback function to receive payload.
* @apicovered			cion_client_add_payload_received_cb,cion_client_remove_payload_received_cb
* @passcase				If cion_client_add_payload_received_cb,cion_client_remove_payload_received_cb is successfull
* @failcase 			If cion_client_add_payload_received_cb,cion_client_remove_payload_received_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_client_add_remove_payload_received_cb_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_client_h hClient;

	nRetVal = cion_client_create(&hClient,"ITc_cion_client_add_remove_payload_received_cb_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hClient,"cion_server_create");

	nRetVal = cion_client_add_payload_received_cb(hClient,ClientPayloadReceivedCB, NULL);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_add_payload_received_cb", CionGetError(nRetVal),cion_client_destroy(hClient));

	nRetVal = cion_client_remove_payload_received_cb(hClient,ClientPayloadReceivedCB);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_client_remove_payload_received_cb", CionGetError(nRetVal));

	nRetVal = cion_client_destroy(hClient);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_client_destroy", CionGetError(nRetVal));

	return 0;
}
//& purpose: Adds and remove callback function for disconnection state.
//& type: auto
/**
* @testcase 			ITc_cion_client_add_remove_disconnected_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Adds and remove callback function for disconnection state.
* @scenario				Adds and remove callback function for disconnection state.
* @apicovered			cion_client_add_disconnected_cb,cion_client_remove_disconnected_cb
* @passcase				If cion_client_add_disconnected_cb,cion_client_remove_disconnected_cb is successfull
* @failcase 			If cion_client_add_disconnected_cb,cion_client_remove_disconnected_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_client_add_remove_disconnected_cb_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_client_h hClient;

	nRetVal = cion_client_create(&hClient,"ITc_cion_client_add_remove_disconnected_cb_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hClient,"cion_server_create");

	nRetVal = cion_client_add_disconnected_cb(hClient,ClientDisconnectedCB, NULL);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_add_disconnected_cb", CionGetError(nRetVal),cion_client_destroy(hClient));

	nRetVal = cion_client_remove_disconnected_cb(hClient,ClientDisconnectedCB);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_client_remove_disconnected_cb", CionGetError(nRetVal));

	nRetVal = cion_client_destroy(hClient);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_client_destroy", CionGetError(nRetVal));

	return 0;
}
/** @} */
/** @} */
