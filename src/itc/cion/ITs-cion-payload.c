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
static cion_payload_h g_hPayload;
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

struct cbdata {
	cion_client_h client;
	bool connected;
};

/**
* @function 		ServerConnectionRequestCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ServerConnectionRequestCB(const char *service_name,const cion_peer_info_h peer_info, void *user_data)
{
	int ret;
	cion_server_h server = (cion_server_h)user_data;
	ret = cion_server_accept(server, peer_info);
	if (ret != CION_ERROR_NONE)
		FPRINTF("[Line : %d][%s] failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ClientServerDiscoveredCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ClientServerDiscoveredCB(const char *service_name,const cion_peer_info_h peer_info, void *user_data)
{
	int ret;
	cion_client_h client = (cion_client_h)user_data;

	ret = cion_client_connect(client, peer_info);
	if (ret != CION_ERROR_NONE)
		FPRINTF("[Line : %d][%s] failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ConnectionResultCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info,const cion_connection_result_h result, void *user_data
* @return 			NA
*/
static void ConnectionResultCB(const char *service_name,const cion_peer_info_h peer_info,const cion_connection_result_h result, void *user_data)
{
	int ret;
	cion_connection_status_e status = CION_CONNECTION_STATUS_ERROR;
	bool *connected = (bool *)user_data;

	ret = cion_connection_result_get_status(result, &status);
	if (ret != CION_ERROR_NONE)
		FPRINTF("[Line : %d][%s] failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);

	if (status == CION_CONNECTION_STATUS_OK) {
		FPRINTF("[Line : %d][%s] failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);
		*connected = true;
	} else {
		FPRINTF("[Line : %d][%s] failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);
		*connected = false;
	}

	StopPollingLoop();
}

/**
* @function 		ServerPayloadReceivedCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, const cion_payload_h payload,cion_payload_transfer_status_e status, void *user_data
* @return 			NA
*/
static void ServerPayloadReceivedCB(const char *service_name,const cion_peer_info_h peer_info, const cion_payload_h payload,cion_payload_transfer_status_e status, void *user_data)
{
	char *data_path;
	char save_as[PATH_MAX];
	int *result = (int *)user_data;

	if (status == CION_PAYLOAD_TRANSFER_STATUS_FAILURE) {
		FPRINTF("[Line : %d][%s] failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);
		return;
	}

	if (status == CION_PAYLOAD_TRANSFER_STATUS_IN_PROGRESS) {
		FPRINTF("[Line : %d][%s] failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);
		return;
	}

	data_path = app_get_data_path();
	snprintf(save_as, sizeof(save_as), "%s/download.png", data_path);
	free(data_path);

	*result = cion_payload_save_as_file(payload, save_as);

	StopPollingLoop();
}

/**
* @function 		ServerPayloadReceivedCB2
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, const cion_payload_h payload,cion_payload_transfer_status_e status, void *user_data
* @return 			NA
*/
static void ServerPayloadReceivedCB2(const char *service_name,
		const cion_peer_info_h peer_info, const cion_payload_h payload,
		cion_payload_transfer_status_e status, void *user_data)
{
	int *result = (int *)user_data;
	char *file_name;

	if (status == CION_PAYLOAD_TRANSFER_STATUS_FAILURE) {
		FPRINTF("[Line : %d][%s] failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);
		return;
	}

	if (status == CION_PAYLOAD_TRANSFER_STATUS_IN_PROGRESS) {
		FPRINTF("[Line : %d][%s] failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);
		return;
	}

	*result = cion_payload_get_received_file_name(payload, &file_name);
	FPRINTF("[Line : %d][%s] failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);
	free(file_name);
	StopPollingLoop();
}

/**
* @function 		ServerPayloadReceivedCB3
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, const cion_payload_h payload,cion_payload_transfer_status_e status, void *user_data
* @return 			NA
*/
static void ServerPayloadReceivedCB3(const char *service_name,
		const cion_peer_info_h peer_info, const cion_payload_h payload,
		cion_payload_transfer_status_e status, void *user_data)
{
	int *result = (int *)user_data;
	uint64_t bytes;

	if (status == CION_PAYLOAD_TRANSFER_STATUS_FAILURE) {
		FPRINTF("[Line : %d][%s] failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);
		return;
	}

	if (status == CION_PAYLOAD_TRANSFER_STATUS_IN_PROGRESS) {
		FPRINTF("[Line : %d][%s] failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);
		return;
	}

	*result = cion_payload_get_received_bytes(payload, &bytes);
	StopPollingLoop();
}

/**
* @function 		ServerPayloadReceivedCB4
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, const cion_payload_h payload,cion_payload_transfer_status_e status, void *user_data
* @return 			NA
*/
static void ServerPayloadReceivedCB4(const char *service_name,
		const cion_peer_info_h peer_info, const cion_payload_h payload,
		cion_payload_transfer_status_e status, void *user_data)
{
	int *result = (int *)user_data;
	uint64_t bytes;

	if (status == CION_PAYLOAD_TRANSFER_STATUS_FAILURE) {
		FPRINTF("[Line : %d][%s] failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);
		return;
	}

	if (status == CION_PAYLOAD_TRANSFER_STATUS_IN_PROGRESS) {
		FPRINTF("[Line : %d][%s] failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);
		return;
	}

	*result = cion_payload_get_total_bytes(payload, &bytes);
	FPRINTF("[Line : %d][%s] failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);
	StopPollingLoop();
}
/**
 * @function 		ITs_cion_payload_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_cion_payload_startup(void)
{
	g_bCionPayloadCreation = false;
	g_hPayload = NULL;
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	int nRetVal = -1;
	nRetVal = cion_payload_create(&g_hPayload, CION_PAYLOAD_TYPE_DATA);
	if (nRetVal != CION_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] Failed to create payload handle\\n", __LINE__, API_NAMESPACE);
		return;
	}
	g_bCionPayloadCreation = true;
	return;
}


/**
 * @function 		ITs_cion_payload_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_cion_payload_cleanup(void)
{
	if(g_hPayload)
	{
		cion_payload_destroy(g_hPayload);
		g_hPayload = NULL;
	}
	return;
}

/** @addtogroup itc-cion-testcases
*  @brief 		Integration testcases for module cion
*  @ingroup 	itc-cion
*  @{
*/

//& purpose: Creates and destroy a payload handle.
//& type: auto
/**
* @testcase 			ITc_cion_payload_create_destroy_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates and destroy a payload handle.
* @scenario				Creates and destroy a payload handle.
* @apicovered			cion_payload_create,cion_payload_destroy
* @passcase				If cion_payload_create,cion_payload_destroy is successfull
* @failcase 			If cion_payload_create,cion_payload_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_payload_create_destroy_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;

	nRetVal = cion_payload_destroy(g_hPayload);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_payload_destroy", CionGetError(nRetVal));

	nRetVal = cion_payload_create(&g_hPayload, CION_PAYLOAD_TYPE_DATA);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_payload_create", CionGetError(nRetVal));
	CHECK_HANDLE(g_hPayload,"cion_payload_create");

	nRetVal = cion_payload_destroy(g_hPayload);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_payload_destroy", CionGetError(nRetVal));

	nRetVal = cion_payload_create(&g_hPayload, CION_PAYLOAD_TYPE_DATA);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_payload_create", CionGetError(nRetVal));
	CHECK_HANDLE(g_hPayload,"cion_payload_create");

	return 0;
}

//& purpose: Gets the type of payload.
//& type: auto
/**
* @testcase 			ITc_cion_payload_get_type_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the type of payload.
* @scenario				Gets the type of payload.
* @apicovered			cion_payload_get_type
* @passcase				If cion_payload_get_type is successfull
* @failcase 			If cion_payload_get_type fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_payload_get_type_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	cion_payload_type_e eType;

	nRetVal = cion_payload_get_type(g_hPayload, &eType);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_payload_get_type", CionGetError(nRetVal));

	return 0;
}

//& purpose: Sets and Gets the data to payload.
//& type: auto
/**
* @testcase 			ITc_cion_payload_set_get_data_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets the data to payload.
* @scenario				Sets and Gets the data to payload.
* @apicovered			cion_payload_set_data,cion_payload_get_data
* @passcase				If cion_payload_set_data,cion_payload_get_data is successfull
* @failcase 			If cion_payload_set_data,cion_payload_get_data fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_payload_set_get_data_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	unsigned char pszData[] = "ITc_cion_payload_get_data_p";
	unsigned char *pszGetData = NULL;
	unsigned int nDataSize = 0;

	nRetVal = cion_payload_set_data(g_hPayload, pszData, sizeof(pszData));
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_payload_set_data", CionGetError(nRetVal));

	nRetVal = cion_payload_get_data(g_hPayload, &pszGetData, &nDataSize);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_payload_get_data", CionGetError(nRetVal));
	CHECK_HANDLE(pszGetData,"cion_payload_get_data");
	if(nDataSize != sizeof(pszData))
	{
		FPRINTF("[Line : %d][%s] Value Mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose:  Sets the file path to send payload.
//& type: auto
/**
* @testcase 			ITc_cion_payload_set_file_path_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets the file path to send payload.
* @scenario				Sets the file path to send payload.
* @apicovered			cion_payload_set_file_path
* @passcase				If cion_payload_set_file_path is successfull
* @failcase 			Ifcion_payload_set_file_path fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_payload_set_file_path_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	cion_payload_h hFilePayload;
	char *pszResPath;
	char pszPath[PATH_MAX];

	pszResPath = app_get_shared_resource_path();
	snprintf(pszPath, sizeof(pszPath), "%s/cion-native-itc.png", pszResPath);
	FREE_MEMORY(pszResPath);

	nRetVal = cion_payload_create(&hFilePayload, CION_PAYLOAD_TYPE_FILE);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_payload_create", CionGetError(nRetVal));

	nRetVal = cion_payload_set_file_path(hFilePayload, pszPath);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_payload_set_file_path", CionGetError(nRetVal));

	return 0;
}

//& purpose: Gets the ID of payload.
//& type: auto
/**
* @testcase 			ITc_cion_payload_get_payload_id_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the ID of payload.
* @scenario				Gets the ID of payload.
* @apicovered			cion_payload_get_payload_id
* @passcase				If cion_payload_get_payload_id is successfull
* @failcase 			If cion_payload_get_payload_id fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_payload_get_payload_id_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	char *pszPayloadID = NULL;

	nRetVal = cion_payload_get_payload_id(g_hPayload, &pszPayloadID);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_payload_get_payload_id", CionGetError(nRetVal));

	FREE_MEMORY(pszPayloadID);

	return 0;
}

//& purpose: Saves the payload as a file.
//& type: auto
/**
* @testcase 			ITc_cion_payload_save_as_file_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Saves the payload as a file.
* @scenario				Saves the payload as a file.
* @apicovered			cion_payload_save_as_file
* @passcase				If cion_payload_save_as_file is successfull
* @failcase 			If cion_payload_save_as_file fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_payload_save_as_file_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	cion_client_h hClient;
	cion_server_h hServer;
	bool connected = false;
	cion_payload_h payload;
	char icon_path[PATH_MAX];
	char *shared_res_path;
	int result = CION_ERROR_OPERATION_FAILED;

	nRetVal = cion_server_create(&hServer, "ITc_cion_payload_save_as_file_p","ITc_cion_payload_save_as_file_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_client_create(&hClient, "ITc_cion_payload_save_as_file_p", NULL);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_create", CionGetError(nRetVal),cion_server_destroy(hServer));


	nRetVal = cion_client_add_connection_result_cb(hClient,ConnectionResultCB, &connected);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_add_connection_result_cb", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	nRetVal = cion_server_listen(hServer, ServerConnectionRequestCB, hServer);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_server_listen", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	nRetVal = cion_client_try_discovery(hClient, ClientServerDiscoveredCB, hClient);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_try_discovery", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	RunPollingLoop();

	nRetVal = cion_server_add_payload_received_cb(hServer,ServerPayloadReceivedCB, &result);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_server_add_payload_received_cb", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	shared_res_path = app_get_shared_resource_path();
	snprintf(icon_path, sizeof(icon_path), "%s/cion-native-itc.png",
	shared_res_path);
	free(shared_res_path);

	nRetVal = cion_payload_create(&payload, CION_PAYLOAD_TYPE_FILE);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_payload_create", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	nRetVal = cion_payload_set_file_path(payload, icon_path);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_payload_set_file_path", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	nRetVal = cion_client_send_payload_async(hClient, payload, NULL, NULL);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_send_payload_async", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	RunPollingLoop();

	nRetVal = cion_client_destroy(hClient);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_client_destroy", CionGetError(nRetVal));
	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	PRINT_RESULT_NORETURN(CION_ERROR_NONE, result, "cion_client_send_payload_async", CionGetError(nRetVal));

	return 0;
}

//& purpose: Gets the name of received file from the payload.
//& type: auto
/**
* @testcase 			ITc_cion_payload_get_received_file_name_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the name of received file from the payload.
* @scenario				Gets the name of received file from the payload.
* @apicovered			cion_payload_get_received_file_name
* @passcase				If cion_payload_get_received_file_name is successfull
* @failcase 			If cion_payload_get_received_file_name fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_payload_get_received_file_name_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	cion_client_h hClient;
	cion_server_h hServer;
	bool connected = false;
	cion_payload_h payload;
	char icon_path[PATH_MAX];
	char *shared_res_path;
	int result = CION_ERROR_OPERATION_FAILED;

	nRetVal = cion_server_create(&hServer, "ITc_cion_payload_get_received_file_name_p","ITc_cion_payload_get_received_file_name_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_client_create(&hClient, "ITc_cion_payload_get_received_file_name_p", NULL);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_create", CionGetError(nRetVal),cion_server_destroy(hServer));


	nRetVal = cion_client_add_connection_result_cb(hClient,ConnectionResultCB, &connected);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_add_connection_result_cb", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	nRetVal = cion_server_listen(hServer, ServerConnectionRequestCB, hServer);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_server_listen", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	nRetVal = cion_client_try_discovery(hClient, ClientServerDiscoveredCB, hClient);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_try_discovery", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	RunPollingLoop();

	nRetVal = cion_server_add_payload_received_cb(hServer,ServerPayloadReceivedCB2, &result);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_server_add_payload_received_cb", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	shared_res_path = app_get_shared_resource_path();
	snprintf(icon_path, sizeof(icon_path), "%s/cion-native-itc.png",shared_res_path);
	free(shared_res_path);

	nRetVal = cion_payload_create(&payload, CION_PAYLOAD_TYPE_FILE);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_payload_create", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	nRetVal = cion_payload_set_file_path(payload, icon_path);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_payload_set_file_path", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	nRetVal = cion_client_send_payload_async(hClient, payload, NULL, NULL);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_send_payload_async", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	RunPollingLoop();

	nRetVal = cion_client_destroy(hClient);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_client_destroy", CionGetError(nRetVal));
	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	PRINT_RESULT_NORETURN(CION_ERROR_NONE, result, "cion_client_try_discovery", CionGetError(nRetVal));

	return 0;
}

//& purpose: Gets the size of currently received file from the payload.
//& type: auto
/**
* @testcase 			ITc_cion_payload_get_received_bytes_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the size of currently received file from the payload.
* @scenario				Gets the size of currently received file from the payload.
* @apicovered			cion_payload_get_received_bytes
* @passcase				If cion_payload_get_received_bytes is successfull
* @failcase 			If cion_payload_get_received_bytes fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_payload_get_received_bytes_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	cion_client_h hClient;
	cion_server_h hServer;
	bool connected = false;
	cion_payload_h payload;
	char icon_path[PATH_MAX];
	char *shared_res_path;
	int result = CION_ERROR_OPERATION_FAILED;

	nRetVal = cion_server_create(&hServer, "ITc_cion_payload_get_received_bytes_p","ITc_cion_payload_get_received_bytes_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_client_create(&hClient, "ITc_cion_payload_get_received_bytes_p", NULL);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_create", CionGetError(nRetVal),cion_server_destroy(hServer));


	nRetVal = cion_client_add_connection_result_cb(hClient,ConnectionResultCB, &connected);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_add_connection_result_cb", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	nRetVal = cion_server_listen(hServer, ServerConnectionRequestCB, hServer);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_server_listen", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	nRetVal = cion_client_try_discovery(hClient, ClientServerDiscoveredCB, hClient);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_try_discovery", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	RunPollingLoop();

	nRetVal = cion_server_add_payload_received_cb(hServer,ServerPayloadReceivedCB3, &result);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_server_add_payload_received_cb", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	shared_res_path = app_get_shared_resource_path();
	snprintf(icon_path, sizeof(icon_path), "%s/cion-native-itc.png",shared_res_path);
	free(shared_res_path);

	nRetVal = cion_payload_create(&payload, CION_PAYLOAD_TYPE_FILE);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_payload_create", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	nRetVal = cion_payload_set_file_path(payload, icon_path);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_payload_set_file_path", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	nRetVal = cion_client_send_payload_async(hClient, payload, NULL, NULL);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_send_payload_async", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	RunPollingLoop();

	nRetVal = cion_client_destroy(hClient);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_client_destroy", CionGetError(nRetVal));
	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	PRINT_RESULT_NORETURN(CION_ERROR_NONE, result, "cion_client_send_payload_async", CionGetError(nRetVal));

	return 0;
}

//& purpose: Gets the total size of file from the payload
//& type: auto
/**
* @testcase 			ITc_cion_payload_get_total_bytes_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the total size of file from the payload
* @scenario				Gets the total size of file from the payload
* @apicovered			cion_payload_get_total_bytes
* @passcase				If cion_payload_get_total_bytes is successfull
* @failcase 			If cion_payload_get_total_bytes fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_payload_get_total_bytes_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	cion_client_h hClient;
	cion_server_h hServer;
	bool connected = false;
	cion_payload_h payload;
	char icon_path[PATH_MAX];
	char *shared_res_path;
	int result = CION_ERROR_OPERATION_FAILED;

	nRetVal = cion_server_create(&hServer, "ITc_cion_payload_get_total_bytes_p","ITc_cion_payload_get_total_bytes_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_server_create", CionGetError(nRetVal));
	CHECK_HANDLE(hServer,"cion_server_create");

	nRetVal = cion_client_create(&hClient, "ITc_cion_payload_get_total_bytes_p", NULL);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_create", CionGetError(nRetVal),cion_server_destroy(hServer));


	nRetVal = cion_client_add_connection_result_cb(hClient,ConnectionResultCB, &connected);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_add_connection_result_cb", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	nRetVal = cion_server_listen(hServer, ServerConnectionRequestCB, hServer);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_server_listen", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	nRetVal = cion_client_try_discovery(hClient, ClientServerDiscoveredCB, hClient);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_try_discovery", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	RunPollingLoop();

	nRetVal = cion_server_add_payload_received_cb(hServer,ServerPayloadReceivedCB4, &result);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_server_add_payload_received_cb", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	shared_res_path = app_get_shared_resource_path();
	snprintf(icon_path, sizeof(icon_path), "%s/cion-native-itc.png",shared_res_path);
	free(shared_res_path);

	nRetVal = cion_payload_create(&payload, CION_PAYLOAD_TYPE_FILE);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_payload_create", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	nRetVal = cion_payload_set_file_path(payload, icon_path);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_payload_set_file_path", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	nRetVal = cion_client_send_payload_async(hClient, payload, NULL, NULL);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_send_payload_async", CionGetError(nRetVal),cion_client_destroy(hClient);cion_server_destroy(hServer));

	RunPollingLoop();

	nRetVal = cion_client_destroy(hClient);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_client_destroy", CionGetError(nRetVal));
	nRetVal = cion_server_destroy(hServer);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_server_destroy", CionGetError(nRetVal));

	PRINT_RESULT_NORETURN(CION_ERROR_NONE, result, "cion_client_try_discovery", CionGetError(nRetVal));

	return 0;
}


/** @} */
/** @} */
