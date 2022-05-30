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

struct cbdata {
	cion_server_h server;
	cion_peer_info_h peer;
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

/**
* @function 		ClientServerDiscoveredCB2
* @description	 	Callback function
* @parameter		const char *service_name,	const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ClientServerDiscoveredCB2(const char *service_name,	const cion_peer_info_h peer_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside ClientServerDiscoveredCB2\\n", __LINE__, API_NAMESPACE);
	int ret;
	cion_peer_info_h *peer = (cion_peer_info_h *)user_data;

	ret = cion_peer_info_clone(peer_info, peer);
	if (ret != CION_ERROR_NONE)
		FPRINTF("[Line : %d][%s] failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);
	StopPollingLoop();
}

/**
* @function 		ClientServerDiscoveredCB3
* @description	 	Callback function
* @parameter		const char *service_name,	const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ClientServerDiscoveredCB3(const char *service_name,const cion_peer_info_h peer_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside ClientServerDiscoveredCB3\\n", __LINE__, API_NAMESPACE);
	int ret;
	cion_peer_info_h *peer = (cion_peer_info_h *)user_data;

	ret = cion_peer_info_clone(peer_info, peer);
	if (ret != CION_ERROR_NONE)
		FPRINTF("[Line : %d][%s] failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);
	StopPollingLoop();
}

/**
* @function 		ServerConnectionRequestCB4
* @description	 	Callback function
* @parameter		const char *service_name,	const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ServerConnectionRequestCB4(const char *service_name,const cion_peer_info_h peer_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside ServerConnectionRequestCB4\\n", __LINE__, API_NAMESPACE);
	int ret;
	cion_peer_info_h *peer = (cion_peer_info_h *)user_data;

	ret = cion_peer_info_clone(peer_info, peer);
	if (ret != CION_ERROR_NONE)
		FPRINTF("[Line : %d][%s] failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);

	StopPollingLoop();
}

/**
* @function 		ServerConnectionRequestCB3
* @description	 	Callback function
* @parameter		const char *service_name,	const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ServerConnectionRequestCB3(const char *service_name,const cion_peer_info_h peer_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside ServerConnectionRequestCB3\\n", __LINE__, API_NAMESPACE);
	int ret;
	cion_peer_info_h *peer = (cion_peer_info_h *)user_data;

	ret = cion_peer_info_clone(peer_info, peer);
	if (ret != CION_ERROR_NONE)
		FPRINTF("[Line : %d][%s] failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);

	StopPollingLoop();
}

/**
* @function 		ServerConnectionResultCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info,	const cion_connection_result_h result, void *user_data
* @return 			NA
*/
static void ServerConnectionResultCB(const char *service_name,const cion_peer_info_h peer_info,	const cion_connection_result_h result, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside ServerConnectionResultCB\\n", __LINE__, API_NAMESPACE);
	int ret;
	cion_connection_status_e status;

	ret = cion_connection_result_get_status(result, &status);
	if (ret != CION_ERROR_NONE) {
		FPRINTF("[Line : %d][%s] failed cion_connection_result_get_status\\n", __LINE__, API_NAMESPACE);
		return;
	}
	StopPollingLoop();
}

/**
* @function 		ServerConnectionRequestCB2
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ServerConnectionRequestCB2(const char *service_name,const cion_peer_info_h peer_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside ServerConnectionRequestCB2\\n", __LINE__, API_NAMESPACE);
	int ret;
	struct cbdata *data = (struct cbdata *)user_data;

	ret = cion_peer_info_clone(peer_info, &(data->peer));
	if (ret != CION_ERROR_NONE)
		FPRINTF("[Line : %d][%s] failed to clone peer info\\n", __LINE__, API_NAMESPACE);
	ret = cion_server_accept(data->server, peer_info);
	if (ret != CION_ERROR_NONE)
		FPRINTF("[Line : %d][%s] failed to accept client\\n", __LINE__, API_NAMESPACE);

}

/**
* @function 		ClientServerDiscoveredCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ClientServerDiscoveredCB(const char *service_name,const cion_peer_info_h peer_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside ClientServerDiscoveredCB\\n", __LINE__, API_NAMESPACE);
	int ret;
	cion_client_h client = (cion_client_h)user_data;

	if (peer_info == NULL)
		FPRINTF("[Line : %d][%s] peerinfo is null\\n", __LINE__, API_NAMESPACE);

	ret = cion_client_connect(client, peer_info);
	if (ret != CION_ERROR_NONE)
		FPRINTF("[Line : %d][%s] failed to connect to server\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ServerPayloadAsyncResultCB
* @description	 	Callback function
* @parameter		const cion_payload_async_result_h result, void *user_data
* @return 			NA
*/
static void ServerPayloadAsyncResultCB(	const cion_payload_async_result_h result, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside ServerPayloadAsyncResultCB\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ServerConnectedPeerInfoCB
* @description	 	Callback function
* @parameter		const cion_peer_info_h peer_info,	void *user_data
* @return 			NA
*/
static bool ServerConnectedPeerInfoCB(const cion_peer_info_h peer_info,	void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside ServerConnectedPeerInfoCB\\n", __LINE__, API_NAMESPACE);
	return true;
}

/**
* @function 		ServerPayloadReceivedCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, const cion_payload_h payload,cion_payload_transfer_status_e status,void *user_data
* @return 			NA
*/
static void ServerPayloadReceivedCB(const char *service_name,const cion_peer_info_h peer_info, const cion_payload_h payload,cion_payload_transfer_status_e status,void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside ServerPayloadReceivedCB\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ServerConnectionRequestCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ServerConnectionRequestCB(const char *service_name,const cion_peer_info_h peer_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside ServerConnectionRequestCB\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ServerDataReceivedCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, const unsigned char *data,unsigned int data_size, unsigned char **return_data,unsigned int *return_data_size, void *user_data
* @return 			NA
*/
static void ServerDataReceivedCB(const char *service_name,const cion_peer_info_h peer_info, const unsigned char *data,unsigned int data_size, unsigned char **return_data,unsigned int *return_data_size, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside ServerDataReceivedCB\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ServerDisconnectedCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ServerDisconnectedCB(const char *service_name,const cion_peer_info_h peer_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside ServerDisconnectedCB\\n", __LINE__, API_NAMESPACE);
}
/**
 * @function 		ITs_cion_server_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_cion_server_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	return;
}


/**
 * @function 		ITs_cion_server_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_cion_server_cleanup(void)
{
	return;
}

/** @addtogroup itc-cion-testcases
*  @brief 		Integration testcases for module cion
*  @ingroup 	itc-cion
*  @{
*/

//& purpose: Creates and Destroy the Cion server handle.
//& type: auto
/**
* @testcase 			ITc_cion_server_create_destroy_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates and Destroy the Cion server handle.
* @scenario				Creates and Destroy the Cion server handle.
* @apicovered			cion_server_create,cion_server_destroy
* @passcase				If cion_server_create,cion_server_destroy is successfull
* @failcase 			If cion_server_create,cion_server_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_server_create_destroy_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_server_h hServer;

	nRetVal = cion_server_create(&hServer, "ITc_cion_server_create_destroy_p","ITc_cion_server_create_destroy_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose: Starts and Stops listening to connection requests from clients.
//& type: auto
/**
* @testcase 			ITc_cion_server_listen_top_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Starts and Stops listening to connection requests from clients.
* @scenario				Starts and Stops listening to connection requests from clients.
* @apicovered			cion_server_listen,cion_server_stop
* @passcase				If cion_server_listen,cion_server_stop is successfull
* @failcase 			If cion_server_listen,cion_server_stop fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_server_listen_stop_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_server_h hServer;

	nRetVal = cion_server_create(&hServer, "ITc_cion_server_listen_stop_p","ITc_cion_server_listen_stop_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_server_listen(hServer, ServerConnectionRequestCB, NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_listen", CionGetError(nRetVal));

	nRetVal = cion_server_stop(hServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_stop", CionGetError(nRetVal));

	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose: Disconnects from a client.
//& type: auto
/**
* @testcase 			ITc_cion_server_disconnect_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Disconnects from a client.
* @scenario				Disconnects from a client.
* @apicovered			cion_server_disconnect
* @passcase				If cion_server_disconnect is successfull
* @failcase 			If cion_server_disconnect fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_server_disconnect_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_server_h hServer;
	cion_client_h hClient;
	struct cbdata data;

	nRetVal = cion_server_create(&hServer, "ITc_cion_server_disconnect_p","ITc_cion_server_disconnect_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_server_add_connection_result_cb(hServer, ServerConnectionResultCB, NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_add_connection_result_cb", CionGetError(nRetVal));

	nRetVal = cion_client_create(&hClient, "ITc_cion_server_disconnect_p",NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_create", CionGetError(nRetVal));
	CHECK_HANDLE(hClient,"cion_client_create");

	data.server = hServer;
	data.peer = NULL;

	nRetVal = cion_server_listen(hServer, ServerConnectionRequestCB2,&data);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_listen", CionGetError(nRetVal));

	nRetVal = cion_client_try_discovery(hClient, ClientServerDiscoveredCB,hClient);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_try_discovery", CionGetError(nRetVal));

	RunPollingLoop();

	// nRetVal = cion_server_stop(hServer);
	// PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_stop", CionGetError(nRetVal));

	nRetVal = cion_server_disconnect(hServer, data.peer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_disconnect", CionGetError(nRetVal));

	nRetVal = cion_peer_info_destroy(data.peer);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_peer_info_destroy", CionGetError(nRetVal));

	nRetVal = cion_client_destroy(hClient);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_client_destroy", CionGetError(nRetVal));

	// nRetVal = cion_server_remove_connection_result_cb(hServer,ServerConnectionResultCB);
	// PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_server_remove_connection_result_cb", CionGetError(nRetVal));

	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose:  Sends payload asynchronously
//& type: auto
/**
* @testcase 			ITc_cion_server_send_payload_async_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sends payload asynchronously
* @scenario				Sends payload asynchronously
* @apicovered			cion_server_send_payload_async
* @passcase				If cion_server_send_payload_async is successfull
* @failcase 			If cion_server_send_payload_async fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_server_send_payload_async_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_server_h hServer;
	cion_client_h hClient;
	cion_payload_h hPayload;
	struct cbdata data;
	unsigned char payload_data[] = "ITc_cion_server_send_payload_async_p";

	nRetVal = cion_server_create(&hServer, "ITc_cion_server_send_payload_async_p","ITc_cion_server_send_payload_async_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_server_add_connection_result_cb(hServer, ServerConnectionResultCB, NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_add_connection_result_cb", CionGetError(nRetVal));

	nRetVal = cion_client_create(&hClient,"ITc_cion_server_send_payload_async_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_create", CionGetError(nRetVal));

	data.server = hServer;
	data.peer = NULL;

	nRetVal = cion_server_listen(hServer, ServerConnectionRequestCB2,&data);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_listen", CionGetError(nRetVal));

	nRetVal = cion_client_try_discovery(hClient, ClientServerDiscoveredCB,hClient);
	RunPollingLoop();
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_try_discovery", CionGetError(nRetVal));

	nRetVal = cion_payload_create(&hPayload, CION_PAYLOAD_TYPE_DATA);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_payload_create", CionGetError(nRetVal));

	nRetVal = cion_payload_set_data(hPayload, payload_data,sizeof(payload_data));
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_payload_set_data", CionGetError(nRetVal));

	nRetVal = cion_server_send_payload_async(hServer, data.peer, hPayload, NULL,NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_send_payload_async", CionGetError(nRetVal));

	nRetVal = cion_payload_destroy(hPayload);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_payload_destroy", CionGetError(nRetVal));

	nRetVal = cion_client_destroy(hClient);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_destroy", CionGetError(nRetVal));

	nRetVal = cion_server_remove_connection_result_cb(hServer,ServerConnectionResultCB);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_remove_connection_result_cb", CionGetError(nRetVal));

	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose:  Adds and  Removes callback function for connection result.
//& type: auto
/**
* @testcase 			ITc_cion_server_add_remove_connection_result_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Adds and  Removes callback function for connection result.
* @scenario				Adds and  Removes callback function for connection result.
* @apicovered			cion_server_add_connection_result_cb,cion_server_remove_connection_result_cb
* @passcase				If cion_server_add_connection_result_cb,cion_server_remove_connection_result_cb is successfull
* @failcase 			If cion_server_add_connection_result_cb,cion_server_remove_connection_result_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_server_add_remove_connection_result_cb_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_server_h hServer;

	nRetVal = cion_server_create(&hServer, "ITc_cion_server_add_remove_connection_result_cb_p","ITc_cion_server_add_remove_connection_result_cb_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_server_add_connection_result_cb(hServer,ServerConnectionResultCB, NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_add_connection_result_cb", CionGetError(nRetVal));

	nRetVal = cion_server_remove_connection_result_cb(hServer,ServerConnectionResultCB);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_remove_connection_result_cb", CionGetError(nRetVal));

	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose:  Adds and  Removes callback function to receive payload.
//& type: auto
/**
* @testcase 			ITc_cion_server_add_remove_payload_received_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Adds and  Removes callback function to receive payload.
* @scenario				Adds and  Removes callback function to receive payload.
* @apicovered			cion_server_add_payload_received_cb,cion_server_remove_payload_received_cb
* @passcase				If cion_server_add_payload_received_cb,cion_server_remove_payload_received_cb is successfull
* @failcase 			If cion_server_add_payload_received_cb,cion_server_remove_payload_received_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_server_add_remove_payload_received_cb_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_server_h hServer;

	nRetVal = cion_server_create(&hServer, "ITc_cion_server_add_remove_payload_received_cb_p","ITc_cion_server_add_remove_payload_received_cb_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_server_add_payload_received_cb(hServer,ServerPayloadReceivedCB, NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_add_payload_received_cb", CionGetError(nRetVal));

	nRetVal = cion_server_remove_payload_received_cb(hServer,ServerPayloadReceivedCB);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_remove_payload_received_cb", CionGetError(nRetVal));

	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose:   Sets and Unsets callback function to receive data.
//& type: auto
/**
* @testcase 			ITc_cion_server_set_unset_data_received_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Unsets callback function to receive data.
* @scenario				Sets and Unsets callback function to receive data.
* @apicovered			cion_server_set_data_received_cb,cion_server_unset_data_received_cb
* @passcase				If cion_server_set_data_received_cb,cion_server_unset_data_received_cb is successfull
* @failcase 			If cion_server_set_data_received_cb,cion_server_unset_data_received_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_server_set_unset_data_received_cb_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_server_h hServer;

	nRetVal = cion_server_create(&hServer, "ITc_cion_server_set_unset_data_received_cb_p","ITc_cion_server_set_unset_data_received_cb_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_server_set_data_received_cb(hServer,ServerDataReceivedCB, NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_set_data_received_cb", CionGetError(nRetVal));

	nRetVal = cion_server_unset_data_received_cb(hServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_unset_data_received_cb", CionGetError(nRetVal));

	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose:   Adds and Removes callback function for disconnect state.
//& type: auto
/**
* @testcase 			ITc_cion_server_add_remove_disconnected_cb_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Unsets callback function to receive data.
* @scenario				Sets and Unsets callback function to receive data.
* @apicovered			cion_server_add_disconnected_cb,cion_server_remove_disconnected_cb
* @passcase				If cion_server_add_disconnected_cb,cion_server_remove_disconnected_cb is successfull
* @failcase 			If cion_server_add_disconnected_cb,cion_server_remove_disconnected_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_server_add_remove_disconnected_cb_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_server_h hServer;

	nRetVal = cion_server_create(&hServer, "ITc_cion_server_add_remove_disconnected_cb_p","ITc_cion_server_add_remove_disconnected_cb_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_server_add_disconnected_cb(hServer,ServerDisconnectedCB, NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_add_disconnected_cb", CionGetError(nRetVal));

	nRetVal = cion_server_remove_disconnected_cb(hServer,ServerDisconnectedCB);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_remove_disconnected_cb", CionGetError(nRetVal));

	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose:    Accepts the connection request from a peer.
//& type: auto
/**
* @testcase 			ITc_cion_server_accept_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Accepts the connection request from a peer.
* @scenario				Accepts the connection request from a peer.
* @apicovered			cion_server_accept
* @passcase				If cion_server_accept is successfull
* @failcase 			If cion_server_accept fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_server_accept_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_server_h hServer;
	cion_client_h hClient;
	cion_peer_info_h hPeerClient = NULL;
	cion_peer_info_h hPeerServer = NULL;

	nRetVal = cion_server_create(&hServer, "ITc_cion_server_accept_p","ITc_cion_server_accept_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_client_create(&hClient, "ITc_cion_server_accept_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_create", CionGetError(nRetVal));

	nRetVal = cion_server_listen(hServer, ServerConnectionRequestCB3,&hPeerClient);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_listen", CionGetError(nRetVal));

	nRetVal = cion_client_try_discovery(hClient, ClientServerDiscoveredCB2,&hPeerServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_try_discovery", CionGetError(nRetVal));

	RunPollingLoop();
	sleep(2);
	CHECK_HANDLE(hPeerServer,"cion_client_try_discovery");

	nRetVal = cion_client_connect(hClient, hPeerServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_connect", CionGetError(nRetVal));

	RunPollingLoop();

	nRetVal = cion_server_accept(hServer, hPeerClient);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_accept", CionGetError(nRetVal));

	nRetVal = cion_peer_info_destroy(hPeerServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_peer_info_destroy", CionGetError(nRetVal));

	nRetVal =  cion_peer_info_destroy(hPeerClient);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_peer_info_destroy", CionGetError(nRetVal));

	nRetVal = cion_client_destroy(hClient);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_destroy", CionGetError(nRetVal));

	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose:   Sets the server display name.
//& type: auto
/**
* @testcase 			ITc_cion_server_set_display_name_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets the server display name.
* @scenario				Sets the server display name.
* @apicovered			cion_server_set_display_name
* @passcase				If cion_server_set_display_name is successfull
* @failcase 			If cion_server_set_display_name fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_server_set_display_name_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_server_h hServer;

	nRetVal = cion_server_create(&hServer, "ITc_cion_server_set_display_name_p","ITc_cion_server_set_display_name_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_server_set_display_name(hServer, "display_name");
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));

	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose:   Sets on-demand launch state.
//& type: auto
/**
* @testcase 			ITc_cion_server_set_on_demand_launch_enabled_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets on-demand launch state.
* @scenario				Sets on-demand launch state.
* @apicovered			cion_server_set_on_demand_launch_enabled
* @passcase				If cion_server_set_on_demand_launch_enabled is successfull
* @failcase 			If cion_server_set_on_demand_launch_enabled fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_server_set_on_demand_launch_enabled_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_server_h hServer;

	nRetVal = cion_server_create(&hServer, "ITc_cion_server_set_on_demand_launch_enabled_p","ITc_cion_server_set_on_demand_launch_enabled_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_server_set_on_demand_launch_enabled(hServer, true);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_set_on_demand_launch_enabled", CionGetError(nRetVal));

	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose: Gets connected peers information.
//& type: auto
/**
* @testcase 			ITc_cion_server_foreach_connected_peer_info_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets connected peers information.
* @scenario				Gets connected peers information.
* @apicovered			cion_server_foreach_connected_peer_info
* @passcase				If cion_server_foreach_connected_peer_info is successfull
* @failcase 			If cion_server_foreach_connected_peer_info fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_server_foreach_connected_peer_info_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_server_h hServer;

	nRetVal = cion_server_create(&hServer, "ITc_cion_server_foreach_connected_peer_info_p","ITc_cion_server_foreach_connected_peer_info_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_server_foreach_connected_peer_info(hServer,ServerConnectedPeerInfoCB, NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_set_on_demand_launch_enable", CionGetError(nRetVal));

	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose:    Rejects the connection request from a peer.
//& type: auto
/**
* @testcase 			ITc_cion_server_reject_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Rejects the connection request from a peer.
* @scenario				Rejects the connection request from a peer.
* @apicovered			cion_server_reject
* @passcase				If cion_server_reject is successfull
* @failcase 			If cion_server_reject fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_server_reject_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_server_h hServer;
	cion_client_h hClient;
	cion_peer_info_h hPeerClient = NULL;
	cion_peer_info_h hPeerServer = NULL;

	nRetVal = cion_server_create(&hServer, "ITc_cion_server_reject_p","ITc_cion_server_reject_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_client_create(&hClient, "ITc_cion_server_reject_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_create", CionGetError(nRetVal));

	nRetVal = cion_server_listen(hServer, ServerConnectionRequestCB4,&hPeerClient);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_listen", CionGetError(nRetVal));

	nRetVal = cion_client_try_discovery(hClient, ClientServerDiscoveredCB3,&hPeerServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_try_discovery", CionGetError(nRetVal));

	RunPollingLoop();
	sleep(2);
	CHECK_HANDLE(hPeerServer,"cion_client_try_discovery");

	nRetVal = cion_client_connect(hClient, hPeerServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_connect", CionGetError(nRetVal));

	RunPollingLoop();

	nRetVal = cion_server_reject(hServer, hPeerClient, NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_reject", CionGetError(nRetVal));

	nRetVal = cion_peer_info_destroy(hPeerServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_peer_info_destroy", CionGetError(nRetVal));

	nRetVal =  cion_peer_info_destroy(hPeerClient);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_peer_info_destroy", CionGetError(nRetVal));

	nRetVal = cion_client_destroy(hClient);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_client_destroy", CionGetError(nRetVal));

	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	return 0;
}
/** @} */
/** @} */
