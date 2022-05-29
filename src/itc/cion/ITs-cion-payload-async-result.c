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
static cion_server_h g_hServer;
static cion_client_h g_hClient;
bool connected = false;
bool g_asyncResult;

/**
* @function 		ConnectionRequestCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ConnectionRequestCB(const char *service_name,const cion_peer_info_h peer_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside ConnectionRequestCB\\n", __LINE__, API_NAMESPACE);
	int nRetVal = -1;
	nRetVal = cion_server_accept(g_hServer, peer_info);
	if (nRetVal != CION_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] cion_server_accept Failed\\n", __LINE__, API_NAMESPACE);
		return;
	}
}

/**
* @function 		ServerDiscoveredCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ServerDiscoveredCB(const char *service_name,const cion_peer_info_h peer_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside ServerDiscoveredCB\\n", __LINE__, API_NAMESPACE);
	int nRetVal = -1;
	nRetVal = cion_client_connect(g_hClient, peer_info);
	if (nRetVal != CION_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] cion_client_connect Failed\\n", __LINE__, API_NAMESPACE);
		return;
	}
}

/**
* @function 		ConnectionResultCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info,const cion_connection_result_h result, void *user_data
* @return 			NA
*/
static void ConnectionResultCB(const char *service_name,const cion_peer_info_h peer_info,const cion_connection_result_h result, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside ConnectionResultCB\\n", __LINE__, API_NAMESPACE);
	cion_connection_status_e eStatus;
	int nRetVal = -1;
	nRetVal = cion_connection_result_get_status(result, &eStatus);
	if (nRetVal != CION_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] cion_connection_result_get_status Failed\\n", __LINE__, API_NAMESPACE);
		return;
	}
	if (eStatus == CION_CONNECTION_STATUS_OK)
	{
		FPRINTF("[Line : %d][%s] Connection established\\n", __LINE__, API_NAMESPACE);
		connected = true;
	}
	if (g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		PayloadAsyncResultCB
* @description	 	Callback function
* @parameter		const cion_payload_async_result_h result,void *user_data
* @return 			NA
*/
void PayloadAsyncResultCB(const cion_payload_async_result_h result,void *user_data)
{
	g_asyncResult = true;
	FPRINTF("[Line : %d][%s] Inside PayloadAsyncResultCB\\n", __LINE__, API_NAMESPACE);
	int nRetVal = -1;
	cion_payload_async_result_h *hClone =(cion_payload_async_result_h *)user_data;

	nRetVal = cion_payload_async_result_clone(result, hClone);
	if (nRetVal != CION_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] Failed to clone payload async result\\n", __LINE__, API_NAMESPACE);
		return;
	}
	if (g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}
/**
 * @function 		ITs_cion_payload_async_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_cion_payload_async_startup(void)
{
	g_bCionPayloadCreation = false;
	g_hClient = NULL;
	g_hServer = NULL;
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	int nRetVal = -1;
	if (connected)
		return;

	nRetVal = cion_server_create(&g_hServer,"ITs_cion_payload_async_startup","ITs_cion_payload_async_startup", NULL);
	if (nRetVal != CION_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] cion_server_create Failed\\n", __LINE__, API_NAMESPACE);
		return;
	}

	nRetVal = cion_client_create(&g_hClient,"ITs_cion_payload_async_startup", NULL);
	if (nRetVal != CION_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] cion_client_create Failed\\n", __LINE__, API_NAMESPACE);
		return;
	}

	nRetVal = cion_server_listen(g_hServer, ConnectionRequestCB,g_hServer);
	if (nRetVal != CION_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] cion_server_listen Failed\\n", __LINE__, API_NAMESPACE);
		return;
	}

	nRetVal = cion_client_add_connection_result_cb(g_hClient,ConnectionResultCB, NULL);
	if (nRetVal != CION_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] cion_client_add_connection_result_cb Failed\\n", __LINE__, API_NAMESPACE);
		return;
	}

	nRetVal = cion_client_try_discovery(g_hClient, ServerDiscoveredCB, NULL);
	if (nRetVal != CION_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] cion_client_try_discovery Failed\\n", __LINE__, API_NAMESPACE);
		return;
	}
	RUN_POLLING_LOOP1;
	sleep(2);
	g_bCionPayloadCreation = true;
	return;
}


/**
 * @function 		ITs_cion_payload_async_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_cion_payload_async_cleanup(void)
{
	int nRetVal = -1;
	connected = false;
	if(g_hClient)
	{
		nRetVal = cion_client_destroy(g_hClient);
		if (nRetVal != CION_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] cion_client_destroy Failed\\n", __LINE__, API_NAMESPACE);
			return;
		}
		g_hClient = NULL;
	}
	if(g_hServer)
	{
		nRetVal = cion_server_destroy(g_hServer);
		if (nRetVal != CION_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] cion_server_destroy Failed\\n", __LINE__, API_NAMESPACE);
			return;
		}
		g_hServer = NULL;
	}
	return;
}

/** @addtogroup itc-cion-testcases
*  @brief 		Integration testcases for module cion
*  @ingroup 	itc-cion
*  @{
*/

//& purpose:  Creates a clone of payload async result.
//& type: auto
/**
* @testcase 			ITc_cion_payload_async_result_clone_destroy_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates a clone of payload async result.
* @scenario				Creates a clone of payload async result.
* @apicovered			cion_payload_async_result_clone,cion_payload_async_result_destroy
* @passcase				If cion_payload_async_result_clone,cion_payload_async_result_destroy is successfull
* @failcase 			If cion_payload_async_result_clone,cion_payload_async_result_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_payload_async_result_clone_destroy_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	cion_payload_h hPayload;
	g_asyncResult = false;
	cion_payload_async_result_h hResult = NULL;
	unsigned char data[] = "ITc_cion_payload_async_result_clone_destroy_p";

	if (!connected)
	{
		FPRINTF("[Line : %d][%s] cion_server_accept Failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = cion_payload_create(&hPayload, CION_PAYLOAD_TYPE_DATA);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_payload_create", CionGetError(nRetVal));

	nRetVal = cion_payload_set_data(hPayload, data, sizeof(data));
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_payload_set_data", CionGetError(nRetVal),cion_payload_destroy(hPayload));

	nRetVal = cion_client_send_payload_async(g_hClient, hPayload,PayloadAsyncResultCB, &hResult);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_send_payload_async", CionGetError(nRetVal),cion_payload_destroy(hPayload));

	RUN_POLLING_LOOP1;
	if(g_asyncResult == false)
	{
		FPRINTF("[Line : %d][%s] PayloadAsyncResultCB callback not hit\\n", __LINE__, API_NAMESPACE);
		cion_payload_destroy(hPayload);
		return 1;
	}
	CHECK_HANDLE(hResult,"cion_client_send_payload_async");

	nRetVal = cion_payload_destroy(hPayload);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_payload_destroy", CionGetError(nRetVal),cion_payload_async_result_destroy(hResult));

	nRetVal = cion_payload_async_result_destroy(hResult);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_payload_async_result_destroy", CionGetError(nRetVal));
	g_asyncResult = false;

	return 0;
}

//& purpose:  Gets the peer information from async result.
//& type: auto
/**
* @testcase 			ITc_cion_payload_async_result_clone_destroy_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the peer information from async result.
* @scenario				Gets the peer information from async result.
* @apicovered			cion_payload_async_result_get_peer_info
* @passcase				If cion_payload_async_result_get_peer_info is successfull
* @failcase 			If cion_payload_async_result_get_peer_info fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_payload_async_result_get_peer_info_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	cion_payload_h hPayload;
	g_asyncResult = false;
	cion_payload_async_result_h hResult = NULL;
	unsigned char data[] = "ITc_cion_payload_async_result_get_peer_info_p";
	cion_peer_info_h hPeer = NULL;

	if (!connected)
	{
		FPRINTF("[Line : %d][%s] cion_server_accept Failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = cion_payload_create(&hPayload, CION_PAYLOAD_TYPE_DATA);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_payload_create", CionGetError(nRetVal));

	nRetVal = cion_payload_set_data(hPayload, data, sizeof(data));
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_payload_set_data", CionGetError(nRetVal),cion_peer_info_destroy(hPeer));

	nRetVal = cion_client_send_payload_async(g_hClient, hPayload,PayloadAsyncResultCB, &hResult);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_client_send_payload_async", CionGetError(nRetVal),cion_peer_info_destroy(hPeer));

	RUN_POLLING_LOOP1;
	if(g_asyncResult == false)
	{
		FPRINTF("[Line : %d][%s] PayloadAsyncResultCB callback not hit\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	CHECK_HANDLE(hResult,"cion_payload_async_result_get_peer_info");

	nRetVal = cion_payload_async_result_get_peer_info(hResult, &hPeer);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_payload_async_result_get_peer_info", CionGetError(nRetVal),cion_peer_info_destroy(hPeer));
	CHECK_HANDLE(hPeer,"cion_payload_async_result_get_peer_info");

	nRetVal = cion_peer_info_destroy(hPeer);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_peer_info_destroy", CionGetError(nRetVal));

	nRetVal = cion_payload_destroy(hPayload);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_payload_destroy", CionGetError(nRetVal));

	nRetVal = cion_payload_async_result_destroy(hResult);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_payload_async_result_destroy", CionGetError(nRetVal));
	g_asyncResult = false;

	return 0;
}

//& purpose:   Gets the payload ID.
//& type: auto
/**
* @testcase 			ITc_cion_payload_async_result_get_payload_id_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the payload ID.
* @scenario				Gets the payload ID.
* @apicovered			cion_payload_async_result_get_payload_id
* @passcase				If cion_payload_async_result_get_payload_id is successfull
* @failcase 			If cion_payload_async_result_get_payload_id fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_payload_async_result_get_payload_id_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	cion_payload_h hPayload;
	g_asyncResult = false;
	cion_payload_async_result_h hResult = NULL;
	unsigned char data[] = "ITc_cion_payload_async_result_get_payload_id_p";
	char *payload_id = NULL;

	if (!connected)
	{
		FPRINTF("[Line : %d][%s] cion_server_accept Failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = cion_payload_create(&hPayload, CION_PAYLOAD_TYPE_DATA);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_peer_info_destroy", CionGetError(nRetVal));

	nRetVal = cion_payload_set_data(hPayload, data, sizeof(data));
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_peer_info_destroy", CionGetError(nRetVal),cion_payload_destroy(hPayload));

	nRetVal = cion_client_send_payload_async(g_hClient, hPayload,PayloadAsyncResultCB, &hResult);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_peer_info_destroy", CionGetError(nRetVal),cion_payload_destroy(hPayload));

	RUN_POLLING_LOOP1;
	if(g_asyncResult == false)
	{
		FPRINTF("[Line : %d][%s] PayloadAsyncResultCB callback not hit\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	CHECK_HANDLE(hResult,"cion_client_send_payload_async");

	nRetVal = cion_payload_async_result_get_payload_id(hResult, &payload_id);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_payload_async_result_get_payload_id", CionGetError(nRetVal),cion_payload_destroy(hPayload));
	CHECK_HANDLE(payload_id,"cion_payload_async_result_get_payload_id");

	FREE_MEMORY(payload_id);
	nRetVal = cion_payload_destroy(hPayload);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_peer_info_destroy", CionGetError(nRetVal));

	nRetVal = cion_payload_async_result_destroy(hResult);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_peer_info_destroy", CionGetError(nRetVal));
	g_asyncResult = false;
	return 0;
}

/** @} */
/** @} */
