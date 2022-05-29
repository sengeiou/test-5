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
#include "ITs-rpc-port-common.h"

/** @addtogroup itc-rpc-port
*  @ingroup itc
*  @{
*/
#include <service_app.h>
#include <app_manager.h>

static rpc_port_proxy_h g_hproxyhandle;
static rpc_port_h g_hreceivedport;
static rpc_port_parcel_h g_hParcel;

static const char g_szParcelServiceAppID[] = "org.example.stubsample";
static const char g_szParcelPortName[] = "Message";
const char g_szCreateTest[] = "create_from_port";
const char g_szSendTest[] = "send";
const char g_szSetGetSeqNumTest[] = "set_get_seq_num";
const char g_szSetGetTagTest[] = "set_get_tag";
static const char g_szPorttest[] = "porttest";
static const char g_szPort_Name[] = "Message";

bool g_callbackOnMsgReceived;
/**
* @function 		RpcParcelTo
* @description	 	function for parcel handle.
* @parameter		NA
* @return 			NA
*/
void RpcParcelTo(rpc_port_parcel_h h, void *data)
{
	return;
}
/**
* @function 		RpcParcelFrom
* @description	 	ffunction for parcel handle.
* @parameter		NA
* @return 			NA
*/
void RpcParcelFrom(rpc_port_parcel_h h, void *data)
{
	return;
}
/**
* @function 		RpcMessage_Onconnected_cb
* @description	 	Callback function for rpc_port_proxy_add_connected_event_cb.
* @parameter		const char *endpoint, const char *port_name, rpc_port_h port, void *data
* @return 			NA
*/
void RpcMessage_Onconnected_cb(const char *endpoint, const char *port_name, rpc_port_h port, void *data)
{
	int nRet;
	FPRINTF("[Line : %d][%s] Inside Callback RpcMessage_Onconnected_cb \\n", __LINE__, API_NAMESPACE);

	if (strncmp(endpoint, g_szParcelServiceAppID,strlen(endpoint)))
	{
		normal_exit(1);
		return;
	}

	g_bCallbackCalled = true;
	if(port)
	{
		FPRINTF("[Line : %d][%s] Port Added \\n", __LINE__, API_NAMESPACE);
		g_hreceivedport = port;
	}
	if (data == g_szCreateTest)
	{
		FPRINTF("[Line : %d][%s] g_szCreateTest \\n", __LINE__, API_NAMESPACE);
		rpc_port_parcel_h hParcel = NULL;

		nRet = rpc_port_parcel_create(&hParcel);
		if (nRet != RPC_PORT_ERROR_NONE) {
			FPRINTF("[Line : %d][%s] rpc_port_parcel_create error  \\n", __LINE__, API_NAMESPACE);
			return;
		}
		if (hParcel == NULL) {
			FPRINTF("[Line : %d][%s] hParcel is NULL  \\n", __LINE__, API_NAMESPACE);
			normal_exit(1);
			return;
		}
		rpc_port_parcel_write_int32(hParcel, Message_METHOD_Send);
		rpc_port_parcel_write_string(hParcel, "receive");

		rpc_port_parcel_send(hParcel, port);
		rpc_port_parcel_destroy(hParcel);
		return;
	}
	else if (data == g_szSendTest)
	{
		FPRINTF("[Line : %d][%s] g_szSendTest \\n", __LINE__, API_NAMESPACE);
		rpc_port_parcel_header_h hRpcPortParcel;
		nRet = rpc_port_parcel_create(&g_hParcel);
		if (nRet != RPC_PORT_ERROR_NONE) {
			FPRINTF("[Line : %d][%s] rpc_port_parcel_create error  \\n", __LINE__, API_NAMESPACE);
			normal_exit(1);
			return;
		}
		if (g_hParcel == NULL) {
			FPRINTF("[Line : %d][%s] g_hParcel is NULL  \\n", __LINE__, API_NAMESPACE);
			normal_exit(1);
			return;
		}
		nRet = rpc_port_parcel_get_header(g_hParcel, &hRpcPortParcel);
		if (nRet != RPC_PORT_ERROR_NONE) {
			FPRINTF("[Line : %d][%s] rpc_port_parcel_get_header error  \\n", __LINE__, API_NAMESPACE);
			rpc_port_parcel_destroy(g_hParcel);
			normal_exit(1);
			return;
		}
		if (hRpcPortParcel == NULL) {
			FPRINTF("[Line : %d][%s] hRpcPortParcel is NULL  \\n", __LINE__, API_NAMESPACE);
			rpc_port_parcel_destroy(g_hParcel);
			normal_exit(1);
			return;
		}
		nRet = rpc_port_parcel_header_set_tag(hRpcPortParcel, "1.5.0");
		if (nRet != RPC_PORT_ERROR_NONE) {
			FPRINTF("[Line : %d][%s] rpc_port_parcel_header_set_tag error  \\n", __LINE__, API_NAMESPACE);
			rpc_port_parcel_destroy(g_hParcel);
			normal_exit(1);
			return;
		}
		nRet = rpc_port_parcel_header_set_seq_num(hRpcPortParcel, 100);
		if (nRet != RPC_PORT_ERROR_NONE) {
			FPRINTF("[Line : %d][%s] rpc_port_parcel_header_set_seq_num error  \\n", __LINE__, API_NAMESPACE);
			rpc_port_parcel_destroy(g_hParcel);
			normal_exit(1);
			return;
		}
		rpc_port_parcel_write_int32(g_hParcel, Message_METHOD_Send);

		rpc_port_parcel_write_string(g_hParcel, "receive");

		rpc_port_parcel_send(g_hParcel, port);
	}
	FPRINTF("[Line : %d][%s] Leaving Callback RpcMessage_Onconnected_cb \\n", __LINE__, API_NAMESPACE);
	return;
}

/**
* @function 		RpcMessage_Onconnected_cb2
* @description	 	Callback function for rpc_port_proxy_add_connected_event_cb.
* @parameter		const char *endpoint, const char *port_name, rpc_port_h port, void *data
* @return 			NA
*/
void RpcMessage_Onconnected_cb2(const char *endpoint, const char *port_name, rpc_port_h port, void *data)
{
	int nRet;
	FPRINTF("[Line : %d][%s] Inside Callback RpcMessage_Onconnected_cb2 \\n", __LINE__, API_NAMESPACE);

	if (strncmp(endpoint, g_szParcelServiceAppID,strlen(endpoint)))
	{
		normal_exit(1);
		return;
	}

	g_bCallbackCalled = true;
	if(port)
	{
		FPRINTF("[Line : %d][%s] rpc_port_h handle is not NULL \\n", __LINE__, API_NAMESPACE);
		g_hreceivedport = port;
	}
	if (data == g_szCreateTest)
	{
		rpc_port_parcel_h hParcel = NULL;

		nRet = rpc_port_parcel_create(&hParcel);
		if (nRet != RPC_PORT_ERROR_NONE) {
			FPRINTF("[Line : %d][%s] rpc_port_parcel_create error  \\n", __LINE__, API_NAMESPACE);
			return;
		}
		rpc_port_parcel_write_int32(hParcel, Message_METHOD_Send);
		rpc_port_parcel_write_string(hParcel, "receive");

		rpc_port_parcel_send(hParcel, port);
		rpc_port_parcel_destroy(hParcel);
	}
	else if (data == g_szSendTest)
	{
		rpc_port_parcel_h hRpcPortParcel;
		nRet = rpc_port_parcel_create(&hRpcPortParcel);
		if (nRet != RPC_PORT_ERROR_NONE) {
			FPRINTF("[Line : %d][%s] rpc_port_parcel_create error  \\n", __LINE__, API_NAMESPACE);
			normal_exit(1);
			return;
		}

		nRet = rpc_port_parcel_write_string(hRpcPortParcel, "test");
		if (nRet != RPC_PORT_ERROR_NONE)
			rpc_port_parcel_destroy(hRpcPortParcel);

		nRet = rpc_port_parcel_send(hRpcPortParcel, port);
		if (nRet != RPC_PORT_ERROR_NONE) {
			FPRINTF("[Line : %d][%s] rpc_port_parcel_send error  \\n", __LINE__, API_NAMESPACE);
			rpc_port_parcel_destroy(hRpcPortParcel);
			normal_exit(1);
			return;
		}

		nRet = rpc_port_parcel_destroy(hRpcPortParcel);
		if (nRet != RPC_PORT_ERROR_NONE) {
			FPRINTF("[Line : %d][%s] rpc_port_parcel_destroy error  \\n", __LINE__, API_NAMESPACE);
			normal_exit(1);
			return;
		}
	}
	FPRINTF("[Line : %d][%s] Leaving Callback RpcMessage_Onconnected_cb2 \\n", __LINE__, API_NAMESPACE);
	return;
}
/**
* @function 		RpcMessage_Onreceived_cb
* @description	 	Callback function for rpc_port_proxy_add_received_event_cb.
* @parameter		const char *endpoint, const char *port_name,void *data
* @return 			NA
*/
void RpcMessage_Onreceived_cb(const char *endpoint, const char *port_name, void *data)
{
	FPRINTF("[Line : %d][%s] Inside Callback RpcMessage_Onreceived_cb \\n", __LINE__, API_NAMESPACE);
	if (strncmp(endpoint, g_szParcelServiceAppID,strlen(endpoint))) {
		return;
	}

	rpc_port_parcel_h hParcelReceive = NULL;
	rpc_port_h hreceivedport= NULL;

	rpc_port_parcel_header_h hReceivedHeader;

	rpc_port_parcel_h hPortParcel = NULL;
	rpc_port_parcel_header_h hPortParcelHeader = NULL;

	int nRet = rpc_port_proxy_get_port(g_hproxyhandle, RPC_PORT_PORT_CALLBACK, &hreceivedport);
	if ( nRet != RPC_PORT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] rpc_port_proxy_get_port error  \\n", __LINE__, API_NAMESPACE);
		g_main_loop_quit(g_pMainLoop);
		normal_exit(1);
		return;
	}
	if (data == g_szSetGetTagTest) {
		FPRINTF("[Line : %d][%s] g_szSetGetTagTest \\n", __LINE__, API_NAMESPACE);
		char *hTag;
		char *hReceivedTag;
		nRet = rpc_port_parcel_create_from_port(&hParcelReceive, hreceivedport);
		if ( nRet != RPC_PORT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] rpc_port_parcel_create_from_port error  \\n", __LINE__, API_NAMESPACE);
			if(hParcelReceive)
			{
				rpc_port_parcel_destroy(hParcelReceive);
			}
			g_main_loop_quit(g_pMainLoop);
			normal_exit(1);
			return;
		}
		if (hParcelReceive == NULL) {
			FPRINTF("[Line : %d][%s] hParcelReceive is NULL  \\n", __LINE__, API_NAMESPACE);
			normal_exit(1);
			return;
		}

		nRet = rpc_port_parcel_get_header(g_hParcel, &hPortParcelHeader);
		if ( nRet != RPC_PORT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] rpc_port_parcel_get_header error  \\n", __LINE__, API_NAMESPACE);
			if(hParcelReceive)
			{
				rpc_port_parcel_destroy(hParcelReceive);
			}
			g_main_loop_quit(g_pMainLoop);
			normal_exit(1);
			return;
		}
		if (hPortParcelHeader == NULL) {
			FPRINTF("[Line : %d][%s] hPortParcelHeader is NULL  \\n", __LINE__, API_NAMESPACE);
			rpc_port_parcel_destroy(hParcelReceive);
			normal_exit(1);
			return;
		}

		nRet = rpc_port_parcel_header_get_tag(hPortParcelHeader, &hTag);
		if ( nRet != RPC_PORT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] rpc_port_parcel_header_get_tag error  \\n", __LINE__, API_NAMESPACE);
			if(hParcelReceive)
			{
				rpc_port_parcel_destroy(hParcelReceive);
			}
			g_main_loop_quit(g_pMainLoop);
			normal_exit(1);
			return;
		}
		if (hTag == NULL) {
			FPRINTF("[Line : %d][%s] hTag is NULL  \\n", __LINE__, API_NAMESPACE);
			rpc_port_parcel_destroy(hParcelReceive);
			normal_exit(1);
			return;
		}

		nRet = rpc_port_parcel_get_header(hParcelReceive, &hReceivedHeader);
		if ( nRet != RPC_PORT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] rpc_port_parcel_get_header error  \\n", __LINE__, API_NAMESPACE);
			if(hParcelReceive)
			{
				rpc_port_parcel_destroy(hParcelReceive);
			}
			g_main_loop_quit(g_pMainLoop);
			normal_exit(1);
			return;
		}
		if (hReceivedHeader == NULL) {
			FPRINTF("[Line : %d][%s] hReceivedHeader is NULL  \\n", __LINE__, API_NAMESPACE);
			rpc_port_parcel_destroy(hParcelReceive);
			normal_exit(1);
			return;
		}

		nRet = rpc_port_parcel_header_get_tag(hPortParcelHeader, &hReceivedTag);
		if ( nRet != RPC_PORT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] rpc_port_parcel_header_get_tag error  \\n", __LINE__, API_NAMESPACE);
			if(hParcelReceive)
			{
				rpc_port_parcel_destroy(hParcelReceive);
			}
			g_main_loop_quit(g_pMainLoop);
			normal_exit(1);
			return;
		}
		if (hReceivedTag == NULL) {
			FPRINTF("[Line : %d][%s] hReceivedTag is NULL  \\n", __LINE__, API_NAMESPACE);
			rpc_port_parcel_destroy(hParcelReceive);
			normal_exit(1);
			return;
		}

		if (strcmp(hReceivedTag, hTag) != 0)
		{
			FPRINTF("[Line : %d][%s] rpc_port_parcel_destroy error %s %s \\n", __LINE__, API_NAMESPACE,hReceivedTag,hTag);
			rpc_port_parcel_destroy(hParcelReceive);
			g_main_loop_quit(g_pMainLoop);
			normal_exit(1);
			return;
		}
		nRet = rpc_port_parcel_destroy(hParcelReceive);
		if (nRet != RPC_PORT_ERROR_NONE) {
			FPRINTF("[Line : %d][%s] rpc_port_parcel_destroy error  \\n", __LINE__, API_NAMESPACE);
			g_main_loop_quit(g_pMainLoop);
			normal_exit(1);
			return;
		}
		if (g_pMainLoop )
		{
			g_main_loop_quit(g_pMainLoop);
		}
		g_callbackOnMsgReceived = true;
		normal_exit(0);
		return;
	}
	else if (data == g_szSetGetSeqNumTest)
	{
		FPRINTF("[Line : %d][%s] g_szSetGetSeqNumTest \\n", __LINE__, API_NAMESPACE);
		int seq_num;
		int received_seq_num;
		nRet = rpc_port_parcel_create_from_port(&hParcelReceive, hreceivedport);
		if ( nRet != RPC_PORT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] rpc_port_parcel_create_from_port error  \\n", __LINE__, API_NAMESPACE);
			if(hParcelReceive)
			{
				rpc_port_parcel_destroy(hParcelReceive);
			}
			g_main_loop_quit(g_pMainLoop);
			normal_exit(1);
			return;
		}

		nRet = rpc_port_parcel_get_header(g_hParcel, &hPortParcelHeader);
		if ( nRet != RPC_PORT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] rpc_port_parcel_get_header error  \\n", __LINE__, API_NAMESPACE);
			if(hParcelReceive)
			{
				rpc_port_parcel_destroy(hParcelReceive);
			}
			g_main_loop_quit(g_pMainLoop);
			normal_exit(1);
			return;
		}
		if (hPortParcelHeader == NULL) {
			FPRINTF("[Line : %d][%s] hPortParcelHeader is NULL  \\n", __LINE__, API_NAMESPACE);
			rpc_port_parcel_destroy(hParcelReceive);
			normal_exit(1);
			return;
		}

		nRet = rpc_port_parcel_header_get_seq_num(hPortParcelHeader, &seq_num);
		if ( nRet != RPC_PORT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] rpc_port_parcel_header_get_seq_num error  \\n", __LINE__, API_NAMESPACE);
			if(hParcelReceive)
			{
				rpc_port_parcel_destroy(hParcelReceive);
			}
			g_main_loop_quit(g_pMainLoop);
			normal_exit(1);
			return;
		}

		nRet = rpc_port_parcel_get_header(hParcelReceive, &hReceivedHeader);
		if ( nRet != RPC_PORT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] rpc_port_parcel_get_header error  \\n", __LINE__, API_NAMESPACE);
			if(hParcelReceive)
			{
				rpc_port_parcel_destroy(hParcelReceive);
			}
			g_main_loop_quit(g_pMainLoop);
			normal_exit(1);
			return;
		}
		if (hReceivedHeader == NULL) {
			FPRINTF("[Line : %d][%s] hReceivedHeader is NULL  \\n", __LINE__, API_NAMESPACE);
			rpc_port_parcel_destroy(hParcelReceive);
			normal_exit(1);
			return;
		}

		nRet = rpc_port_parcel_header_get_seq_num(hReceivedHeader, &received_seq_num);
		if ( nRet != RPC_PORT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] rpc_port_parcel_header_get_seq_num error  \\n", __LINE__, API_NAMESPACE);
			if(hParcelReceive)
			{
				rpc_port_parcel_destroy(hParcelReceive);
			}
			g_main_loop_quit(g_pMainLoop);
			normal_exit(1);
			return;
		}

		if (seq_num != received_seq_num)
		{
			FPRINTF("[Line : %d][%s] mismatch error %d %d \\n", __LINE__, API_NAMESPACE,seq_num,received_seq_num);
			normal_exit(1);
			return;
		}

		nRet = rpc_port_parcel_destroy(hParcelReceive);
		if (nRet != RPC_PORT_ERROR_NONE) {
			FPRINTF("[Line : %d][%s] rpc_port_parcel_destroy error  \\n", __LINE__, API_NAMESPACE);
			rpc_port_parcel_destroy(hParcelReceive);
			g_main_loop_quit(g_pMainLoop);
			normal_exit(1);
			return;
		}
		g_main_loop_quit(g_pMainLoop);
		g_callbackOnMsgReceived = true;
		normal_exit(0);
		return;
	}

	nRet = rpc_port_parcel_create_from_port(&hParcelReceive, hreceivedport);
	if ( nRet != RPC_PORT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] rpc_port_parcel_create_from_port error  \\n", __LINE__, API_NAMESPACE);
		if(hParcelReceive)
		{
			rpc_port_parcel_destroy(hParcelReceive);
		}
		g_main_loop_quit(g_pMainLoop);
		normal_exit(1);
		return;
	}
	nRet = rpc_port_parcel_destroy(hParcelReceive);
	if (nRet != RPC_PORT_ERROR_NONE) {
		FPRINTF("[Line : %d][%s] rpc_port_parcel_destroy error  \\n", __LINE__, API_NAMESPACE);
		g_main_loop_quit(g_pMainLoop);
		normal_exit(1);
		return;
	}
	if (g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
	FPRINTF("[Line : %d][%s] Leaving Callback RpcMessage_Onreceived_cb \\n", __LINE__, API_NAMESPACE);
	g_callbackOnMsgReceived = true;
	normal_exit(0);
}

/**
* @function 		ITs_rpc_port_parcel_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_rpc_port_parcel_startup(void)
{
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0 )
	{
		int ret = remove(ERR_LOG);
		if(ret == -1)
		{
			FPRINTF("[Line: %d][%s] unlinking file name error =%s \\n", __LINE__, API_NAMESPACE,ERR_LOG);
			return;
		}
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_rpc-port_p\\n", __LINE__, API_NAMESPACE);
#endif
	g_hParcel = NULL;
	int nRet = rpc_port_proxy_create(&g_hproxyhandle);
	if ( nRet != RPC_PORT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to Create proxy handle, error returned = %s\\n", __LINE__, API_NAMESPACE, RpcPortGetError(nRet));
		g_bRpcPortCreation = false;
	}
	g_bRpcPortCreation = true;
}

/**
* @function 		ITs_rpc_port_parcel_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_rpc_port_parcel_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: rpc-port\\n", __LINE__, API_NAMESPACE);
#endif
	if (g_hproxyhandle)
	{
		rpc_port_proxy_destroy(g_hproxyhandle);
	}
	if (g_hParcel)
	{
		rpc_port_parcel_destroy(g_hParcel);
	}
}

/**
* @testcase 			ITc_rpc_port_parcel_create_destroy_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Creates and destroys the rpc port parcel handle
* @scenario				Creates and destroys the rpc port parcel handle
* @apicovered			rpc_port_parcel_create,rpc_port_parcel_destroy
* @passcase				When rpc_port_proxy_create,rpc_port_parcel_destroy is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_parcel_create_destroy_p(void)
{
	START_TEST;
	rpc_port_parcel_h hPortParcel = NULL;

	// Target API
	int nRetVal = rpc_port_parcel_create(&hPortParcel);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_create", RpcPortGetError(nRetVal));
	CHECK_HANDLE(hPortParcel, "rpc_port_parcel_create");

	// Target API
	nRetVal = rpc_port_parcel_destroy(hPortParcel);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_destroy", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_parcel_create_from_port_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Creates the rpc port parcel handle from rpc port handle
* @scenario				Creates the rpc port parcel handle from rpc port handle
* @apicovered			rpc_port_parcel_create_from_port,rpc_port_proxy_add_connected_event_cb,rpc_port_proxy_add_received_event_cb,rpc_port_proxy_connect
* @passcase				When rpc_port_parcel_create_from_port is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_parcel_create_from_port_p(void)
{
	START_TEST;

	rpc_port_parcel_h hPortParcel = NULL;
	g_bCallbackCalled = false;
	g_callbackOnMsgReceived = false;
	int nTimeoutId = -1;

	int nRetVal = rpc_port_proxy_add_connected_event_cb(g_hproxyhandle,RpcMessage_Onconnected_cb, g_szCreateTest);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_connected_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_proxy_add_received_event_cb(g_hproxyhandle,RpcMessage_Onreceived_cb, NULL);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_received_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_proxy_connect(g_hproxyhandle,g_szParcelServiceAppID,g_szParcelPortName);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_connect", RpcPortGetError(nRetVal));

	RUN_POLLING_LOOP;
	if(g_bCallbackCalled != true)
	{
		FPRINTF("[Line : %d][%s] Callback RpcMessage_Onconnected_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_proxy_add_connected_event_cb");
		return 1;
	}
	if(g_callbackOnMsgReceived != true)
	{

		FPRINTF("[Line : %d][%s] Callback RpcMessage_Onreceived_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_proxy_add_received_event_cb");
		return 1;
	}

	return 0;
}


/**
* @testcase 			ITc_rpc_port_parcel_send_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Sends the rpc port parcel data to rpc port handle
* @scenario				Sends the rpc port parcel data to rpc port handle
* @apicovered			rpc_port_parcel_send,rpc_port_proxy_add_connected_event_cb
* @passcase				When rpc_port_parcel_send is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_parcel_send_p(void)
{
	START_TEST;

	rpc_port_proxy_h hPortProxy = NULL;
	g_bCallbackCalled = false;
	int nTimeoutId = -1;

	int nRetVal = rpc_port_proxy_add_connected_event_cb(g_hproxyhandle,RpcMessage_Onconnected_cb2, g_szSendTest);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_connected_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_proxy_connect(g_hproxyhandle,g_szParcelServiceAppID,g_szParcelPortName);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_connect", RpcPortGetError(nRetVal));
	RUN_POLLING_LOOP;
	if(g_bCallbackCalled != true)
	{

		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_Connected_cb2 not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_proxy_add_connected_event_cb");
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_rpc_port_parcel_write_read_byte_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Writes and reads byte data to the rpc port parcel handle
* @scenario				Writes and reads byte data to the rpc port parcel handle
* @apicovered			rpc_port_parcel_write_byte,rpc_port_parcel_read_byte,rpc_port_parcel_create,rpc_port_parcel_destroy
* @passcase				When rpc_port_parcel_write_byte,rpc_port_parcel_read_byte is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_parcel_write_read_byte_p(void)
{
	START_TEST;
	rpc_port_parcel_h hPortParcel = NULL;
	char chData;

	int nRetVal = rpc_port_parcel_create(&hPortParcel);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_create", RpcPortGetError(nRetVal));
	CHECK_HANDLE(hPortParcel, "rpc_port_parcel_create");
	// Target API
	nRetVal = rpc_port_parcel_write_byte(hPortParcel,'a');
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_write_byte", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	// Target API
	nRetVal = rpc_port_parcel_read_byte(hPortParcel,&chData);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_write_byte", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	if(chData != 'a')
	{
		FPRINTF("[Line : %d][%s] Value of byte from rpc_port_parcel_read_byte is wrong \\n", __LINE__, API_NAMESPACE);
		rpc_port_parcel_destroy(hPortParcel);
		return 1;
	}

	nRetVal = rpc_port_parcel_destroy(hPortParcel);
	PRINT_RESULT_NORETURN(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_destroy", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_parcel_write_read_int16_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Writes and reads int16 data to the rpc port parcel handle
* @scenario				Writes and reads int16 data to the rpc port parcel handle
* @apicovered			rpc_port_parcel_write_int16,rpc_port_parcel_read_int16,rpc_port_parcel_create,rpc_port_parcel_destroy
* @passcase				When rpc_port_parcel_write_int16,rpc_port_parcel_read_int16 is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_parcel_write_read_int16_p(void)
{
	START_TEST;
	rpc_port_parcel_h hPortParcel = NULL;
	short nOutData,nInData=16;

	int nRetVal = rpc_port_parcel_create(&hPortParcel);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_create", RpcPortGetError(nRetVal));
	CHECK_HANDLE(hPortParcel, "rpc_port_parcel_create");
	// Target API
	nRetVal = rpc_port_parcel_write_int16(hPortParcel,nInData);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_write_int16", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	// Target API
	nRetVal = rpc_port_parcel_read_int16(hPortParcel,&nOutData);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_read_int16", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));

	if(nOutData != nInData)
	{
		FPRINTF("[Line : %d][%s] Value of int16 from rpc_port_parcel_read_int16 is wrong \\n", __LINE__, API_NAMESPACE);
		rpc_port_parcel_destroy(hPortParcel);
		return 1;
	}

	nRetVal = rpc_port_parcel_destroy(hPortParcel);
	PRINT_RESULT_NORETURN(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_destroy", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_parcel_write_read_int32_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Writes and reads int32 data to the rpc port parcel handle
* @scenario				Writes and reads int32 data to the rpc port parcel handle
* @apicovered			rpc_port_parcel_write_int32,rpc_port_parcel_read_int32,rpc_port_parcel_create,rpc_port_parcel_destroy
* @passcase				When rpc_port_parcel_write_int32 ,rpc_port_parcel_read_int32is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_parcel_write_read_int32_p(void)
{
	START_TEST;
	rpc_port_parcel_h hPortParcel = NULL;
	int nOutData,nInData=32;

	int nRetVal = rpc_port_parcel_create(&hPortParcel);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_create", RpcPortGetError(nRetVal));
	CHECK_HANDLE(hPortParcel, "rpc_port_parcel_create");
	// Target API
	nRetVal = rpc_port_parcel_write_int32(hPortParcel,nInData);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_write_int32", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	// Target API
	nRetVal = rpc_port_parcel_read_int32(hPortParcel,&nOutData);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_read_int32", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	if(nOutData != nInData)
	{
		FPRINTF("[Line : %d][%s] Value of int32 from rpc_port_parcel_read_int32 is wrong \\n", __LINE__, API_NAMESPACE);
		rpc_port_parcel_destroy(hPortParcel);
		return 1;
	}

	nRetVal = rpc_port_parcel_destroy(hPortParcel);
	PRINT_RESULT_NORETURN(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_destroy", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_parcel_write_read_int64_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Writes and reads int64 data to the rpc port parcel handle
* @scenario				Writes and reads int64 data to the rpc port parcel handle
* @apicovered			rpc_port_parcel_write_int64,rpc_port_parcel_read_int64,rpc_port_parcel_create,rpc_port_parcel_destroy
* @passcase				When rpc_port_parcel_read_int64,rpc_port_parcel_write_int64 is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_parcel_write_read_int64_p(void)
{
	START_TEST;
	rpc_port_parcel_h hPortParcel = NULL;
	long long lOutData,lInData=64;

	int nRetVal = rpc_port_parcel_create(&hPortParcel);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_create", RpcPortGetError(nRetVal));
	CHECK_HANDLE(hPortParcel, "rpc_port_parcel_create");
	// Target API
	nRetVal = rpc_port_parcel_write_int64(hPortParcel,lInData);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_write_int64", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	// Target API
	nRetVal = rpc_port_parcel_read_int64(hPortParcel,&lOutData);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_read_int64", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	if(lOutData != lInData)
	{
		FPRINTF("[Line : %d][%s] Value of int64 from rpc_port_parcel_read_int64 is wrong \\n", __LINE__, API_NAMESPACE);
		rpc_port_parcel_destroy(hPortParcel);
		return 1;
	}

	nRetVal = rpc_port_parcel_destroy(hPortParcel);
	PRINT_RESULT_NORETURN(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_destroy", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_parcel_write_read_float_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Writes and reads float data to the rpc port parcel handle.
* @scenario				Writes and reads float data to the rpc port parcel handle.
* @apicovered			rpc_port_parcel_write_float,rpc_port_parcel_read_float,rpc_port_parcel_create,rpc_port_parcel_destroy
* @passcase				When rpc_port_parcel_write_float ,rpc_port_parcel_read_float is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_parcel_write_read_float_p(void)
{
	START_TEST;
	rpc_port_parcel_h hPortParcel = NULL;
	float flOutData,flInData=3.49f;

	int nRetVal = rpc_port_parcel_create(&hPortParcel);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_create", RpcPortGetError(nRetVal));
	CHECK_HANDLE(hPortParcel, "rpc_port_parcel_create");
	// Target API
	nRetVal = rpc_port_parcel_write_float(hPortParcel,flInData);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_write_float", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	// Target API
	nRetVal = rpc_port_parcel_read_float(hPortParcel,&flOutData);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_read_float", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	if(flInData != flOutData)
	{
		FPRINTF("[Line : %d][%s] Value from rpc_port_parcel_read_float is wrong \\n", __LINE__, API_NAMESPACE);
		rpc_port_parcel_destroy(hPortParcel);
		return 1;
	}

	nRetVal = rpc_port_parcel_destroy(hPortParcel);
	PRINT_RESULT_NORETURN(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_destroy", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_parcel_write_read_double_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Writes and reads double data to the rpc port parcel handle
* @scenario				Writesand reads  double data to the rpc port parcel handle
* @apicovered			rpc_port_parcel_write_double,rpc_port_parcel_read_double,rpc_port_parcel_create,rpc_port_parcel_destroy
* @passcase				When rpc_port_parcel_write_double,rpc_port_parcel_read_double is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_parcel_write_read_double_p(void)
{
	START_TEST;
	rpc_port_parcel_h hPortParcel = NULL;
	double dOutData,dInData=298645678;

	int nRetVal = rpc_port_parcel_create(&hPortParcel);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_create", RpcPortGetError(nRetVal));
	CHECK_HANDLE(hPortParcel, "rpc_port_parcel_create");
	// Target API
	nRetVal = rpc_port_parcel_write_double(hPortParcel,dInData);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_write_double", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	// Target API
	nRetVal = rpc_port_parcel_read_double(hPortParcel,&dOutData);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_read_double", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	if(dInData != dOutData)
	{
		FPRINTF("[Line : %d][%s] Value from rpc_port_parcel_read_double is wrong \\n", __LINE__, API_NAMESPACE);
		rpc_port_parcel_destroy(hPortParcel);
		return 1;
	}

	nRetVal = rpc_port_parcel_destroy(hPortParcel);
	PRINT_RESULT_NORETURN(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_destroy", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_parcel_write_read_string_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Writes and reads string data to the rpc port parcel handle.
* @scenario				Writes and reads string data to the rpc port parcel handle.
* @apicovered			rpc_port_parcel_write_string,rpc_port_parcel_read_string,rpc_port_parcel_create,rpc_port_parcel_destroy
* @passcase				When rpc_port_parcel_write_string,rpc_port_parcel_read_string is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_parcel_write_read_string_p(void)
{
	START_TEST;
	rpc_port_parcel_h hPortParcel = NULL;
	char *pszOutdata = NULL;
	const char *pszIndata = "test";

	int nRetVal = rpc_port_parcel_create(&hPortParcel);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_create", RpcPortGetError(nRetVal));
	CHECK_HANDLE(hPortParcel, "rpc_port_parcel_create");
	// Target API
	nRetVal = rpc_port_parcel_write_string(hPortParcel,pszIndata);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_write_string", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	// Target API
	nRetVal = rpc_port_parcel_read_string(hPortParcel,&pszOutdata);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_read_string", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	CHECK_HANDLE_CLEANUP(pszOutdata,"rpc_port_parcel_read_string",rpc_port_parcel_destroy(hPortParcel));

	if(strncmp(pszIndata,pszOutdata,strlen(pszIndata)) != 0)
	{
		FPRINTF("[Line : %d][%s] Value from rpc_port_parcel_read_string is wrong \\n", __LINE__, API_NAMESPACE);
		rpc_port_parcel_destroy(hPortParcel);
		FREE_MEMORY(pszOutdata);
		return 1;
	}
	FREE_MEMORY(pszOutdata);

	nRetVal = rpc_port_parcel_destroy(hPortParcel);
	PRINT_RESULT_NORETURN(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_destroy", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_parcel_write_read_bool_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Writes and reads  bool data to the rpc port parcel handle
* @scenario				Writes and reads bool data to the rpc port parcel handle
* @apicovered			rpc_port_parcel_write_bool,rpc_port_parcel_read_bool,rpc_port_parcel_create,rpc_port_parcel_destroy
* @passcase				When rpc_port_parcel_write_bool,rpc_port_parcel_read_bool is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_parcel_write_read_bool_p(void)
{
	START_TEST;
	rpc_port_parcel_h hPortParcel = NULL;
	bool bOutData,bInData = true;
	int nRetVal = rpc_port_parcel_create(&hPortParcel);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_create", RpcPortGetError(nRetVal));
	CHECK_HANDLE(hPortParcel, "rpc_port_parcel_create");
	// Target API
	nRetVal = rpc_port_parcel_write_bool(hPortParcel,bInData);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_write_bool", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	// Target API
	nRetVal = rpc_port_parcel_read_bool(hPortParcel,&bOutData);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_read_bool", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	if(bOutData != bInData)
	{
		FPRINTF("[Line : %d][%s] Value from rpc_port_parcel_read_bool is wrong \\n", __LINE__, API_NAMESPACE);
		rpc_port_parcel_destroy(hPortParcel);
		return 1;
	}

	nRetVal = rpc_port_parcel_destroy(hPortParcel);
	PRINT_RESULT_NORETURN(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_destroy", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_parcel_write_read_bundle_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Writes and reads bundle data to the rpc port parcel handle
* @scenario				Writes and reads bundle data to the rpc port parcel handle
* @apicovered			rpc_port_parcel_write_bundle,rpc_port_parcel_read_bundle,rpc_port_parcel_create,rpc_port_parcel_destroy
* @passcase				When rpc_port_parcel_write_bundle,rpc_port_parcel_read_bundle is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_parcel_write_read_bundle_p(void)
{
	START_TEST;
	rpc_port_parcel_h hPortParcel = NULL;

	int nRetVal = rpc_port_parcel_create(&hPortParcel);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_create", RpcPortGetError(nRetVal));
	CHECK_HANDLE(hPortParcel, "rpc_port_parcel_create");
	bundle *pInBundle = bundle_create();
	bundle *pOutBundle = NULL;
	if (pInBundle == NULL)
	{
		FPRINTF("[Line : %d][%s] Precondition of  rpc_port_parcel_write_bundle fails as  bundle_create returns NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	// Target API
	nRetVal = rpc_port_parcel_write_bundle(hPortParcel,pInBundle);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_write_bundle", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	// Target API
	nRetVal = rpc_port_parcel_read_bundle(hPortParcel,&pOutBundle);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_read_bundle", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	CHECK_HANDLE_CLEANUP(pOutBundle,"rpc_port_parcel_read_bundle",bundle_free(pInBundle);rpc_port_parcel_destroy(hPortParcel));

	bundle_free(pInBundle);
	bundle_free(pOutBundle);

	nRetVal = rpc_port_parcel_destroy(hPortParcel);
	PRINT_RESULT_NORETURN(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_destroy", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_parcel_write_read_array_count_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Writes and reads  array count data to the rpc port parcel handle
* @scenario				Writes and reads array count data to the rpc port parcel handle
* @apicovered			rpc_port_parcel_write_array_count,rpc_port_parcel_read_array_count,rpc_port_parcel_create,rpc_port_parcel_destroy
* @passcase				When rpc_port_parcel_write_array_count ,rpc_port_parcel_read_array_count is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_parcel_write_read_array_count_p(void)
{
	START_TEST;
	rpc_port_parcel_h hPortParcel = NULL;
	int nOutData,nInData=15;

	int nRetVal = rpc_port_parcel_create(&hPortParcel);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_create", RpcPortGetError(nRetVal));
	CHECK_HANDLE(hPortParcel, "rpc_port_parcel_create");
	// Target API
	nRetVal = rpc_port_parcel_write_array_count(hPortParcel,nInData);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_write_array_count", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	// Target API
	nRetVal = rpc_port_parcel_read_array_count(hPortParcel,&nOutData);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_read_array_count", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	if(nOutData != nInData)
	{
		FPRINTF("[Line : %d][%s] Value of int32 from rpc_port_parcel_read_array_count is wrong \\n", __LINE__, API_NAMESPACE);
		rpc_port_parcel_destroy(hPortParcel);
		return 1;
	}

	nRetVal = rpc_port_parcel_destroy(hPortParcel);
	PRINT_RESULT_NORETURN(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_destroy", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_parcel_write_read_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Writes and reads data to the rpc port parcel handle using parcelable
* @scenario				Writes and reads data to the rpc port parcel handle using parcelable
* @apicovered			rpc_port_parcel_write,rpc_port_parcel_create,rpc_port_parcel_destroy,rpc_port_parcel_read
* @passcase				When rpc_port_parcel_write,rpc_port_parcel_read is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_parcel_write_read_p(void)
{
	START_TEST;
	rpc_port_parcel_h hPortParcel = NULL;

	int nRetVal = rpc_port_parcel_create(&hPortParcel);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_create", RpcPortGetError(nRetVal));
	CHECK_HANDLE(hPortParcel, "rpc_port_parcel_create");

	rpc_port_parcelable_t parcelable = {
		.to = RpcParcelTo,
		.from = RpcParcelFrom
	};
	// Target API
	nRetVal = rpc_port_parcel_write(hPortParcel,&parcelable,NULL);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_write", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));

	// Target API
	nRetVal = rpc_port_parcel_read(hPortParcel,&parcelable,NULL);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_read", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));

	nRetVal = rpc_port_parcel_destroy(hPortParcel);
	PRINT_RESULT_NORETURN(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_destroy", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_parcel_burst_write_read_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Writes and reads burst data to the rpc port parcel handle using parcelable
* @scenario				Writes and reads burst data to the rpc port parcel handle using parcelable
* @apicovered			rpc_port_parcel_burst_write,rpc_port_parcel_create,rpc_port_parcel_destroy,rpc_port_parcel_burst_read
* @passcase				When rpc_port_parcel_burst_write,rpc_port_parcel_burst_read is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_parcel_burst_write_read_p(void)
{
	START_TEST;
	rpc_port_parcel_h hPortParcel = NULL;
	 unsigned char buf[] = { 0, 1, 'a', 'b', 3 };
	 unsigned char buf2[] = { 0, };

	int nRetVal = rpc_port_parcel_create(&hPortParcel);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_create", RpcPortGetError(nRetVal));
	CHECK_HANDLE(hPortParcel, "rpc_port_parcel_create");

	// Target API
	nRetVal = rpc_port_parcel_burst_write(hPortParcel,buf, sizeof(buf));
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_burst_write", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));

	// Target API
	nRetVal = rpc_port_parcel_burst_read(hPortParcel,(unsigned char *)&buf2,sizeof(buf));
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_burst_read", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));

	nRetVal = rpc_port_parcel_destroy(hPortParcel);
	PRINT_RESULT_NORETURN(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_destroy", RpcPortGetError(nRetVal));

	return 0;
}
/**
* @testcase 			ITc_rpc_port_parcel_get_header_p
* @since_tizen			6.5
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Gets the header handle from the rpc port parcel handle
* @scenario				Gets the header handle from the rpc port parcel handle
* @apicovered			rpc_port_parcel_get_header
* @passcase				When rpc_port_parcel_get_header is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_rpc_port_parcel_get_header_p(void)
{
	START_TEST;
	rpc_port_parcel_h hPortParcel = NULL;
	rpc_port_parcel_header_h hPortParcelHeader = NULL;

	int nRetVal = rpc_port_parcel_create(&hPortParcel);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_create", RpcPortGetError(nRetVal));
	CHECK_HANDLE(hPortParcel, "rpc_port_parcel_create");

	// Target API
	nRetVal = rpc_port_parcel_get_header(hPortParcel, &hPortParcelHeader);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_get_header", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));

	nRetVal = rpc_port_parcel_destroy(hPortParcel);
	PRINT_RESULT_NORETURN(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_destroy", RpcPortGetError(nRetVal));

	return 0;
}
/**
* @testcase 			ITc_rpc_port_parcel_header_set_get_seq_num_p
* @since_tizen			6.5
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets and gets the sequence number
* @scenario				Sets and gets the sequence number
* @apicovered			rpc_port_parcel_get_header
* @passcase				When rpc_port_parcel_get_header is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_rpc_port_parcel_header_set_get_seq_num_p(void)
{
	START_TEST;

	g_bCallbackCalled = false;
	g_callbackOnMsgReceived = false;
	int nTimeoutId = -1;

	int nRetVal = rpc_port_proxy_add_connected_event_cb(g_hproxyhandle,RpcMessage_Onconnected_cb, g_szSendTest);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_connected_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_proxy_add_received_event_cb(g_hproxyhandle,RpcMessage_Onreceived_cb, g_szSetGetSeqNumTest);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_received_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_proxy_connect(g_hproxyhandle,g_szParcelServiceAppID, g_szPort_Name);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_connect_sync", RpcPortGetError(nRetVal));

	RUN_POLLING_LOOP;
	if(g_bCallbackCalled != true)
	{
		FPRINTF("[Line : %d][%s] Callback RpcMessage_Onconnected_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_proxy_add_connected_event_cb");
		return 1;
	}
	if(g_callbackOnMsgReceived != true)
	{

		FPRINTF("[Line : %d][%s] Callback RpcMessage_Onreceived_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_proxy_add_received_event_cb");
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_rpc_port_parcel_header_get_timestamp_p
* @since_tizen			6.5
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Gets the timestamp from the header handle of the rpc port parcel.
* @scenario				Gets the timestamp from the header handle of the rpc port parcel.
* @apicovered			rpc_port_parcel_get_header
* @passcase				When rpc_port_parcel_get_header is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_rpc_port_parcel_header_get_timestamp_p(void)
{
	START_TEST;

	rpc_port_parcel_h hPortParcel = NULL;
	rpc_port_parcel_header_h hPortParcelHeader = NULL;
	struct timespec getTimeStamp = { 0, };

	int nRetVal = rpc_port_parcel_create(&hPortParcel);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_create", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_parcel_get_header(hPortParcel, &hPortParcelHeader);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_get_header", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));

	nRetVal = rpc_port_parcel_header_get_timestamp(hPortParcelHeader, &getTimeStamp);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_header_get_timestamp", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));

	nRetVal = rpc_port_parcel_destroy(hPortParcel);
	PRINT_RESULT_NORETURN(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_destroy", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_parcel_header_set_get_tag_p
* @since_tizen			6.5
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets and gets the tag.
* @scenario				Sets and gets the tag.
* @apicovered			rpc_port_parcel_header_set_tag,rpc_port_parcel_header_get_tag
* @passcase				When rpc_port_parcel_header_set_tag and rpc_port_parcel_header_get_tag is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_rpc_port_parcel_header_set_get_tag_p(void)
{
	START_TEST;

	g_bCallbackCalled = false;
	g_callbackOnMsgReceived = false;
	int nTimeoutId = -1;

	int nRetVal = rpc_port_proxy_add_connected_event_cb(g_hproxyhandle,RpcMessage_Onconnected_cb, g_szSendTest);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_connected_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_proxy_add_received_event_cb(g_hproxyhandle,RpcMessage_Onreceived_cb, g_szSetGetTagTest);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_received_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_proxy_connect(g_hproxyhandle,g_szParcelServiceAppID, g_szPort_Name);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_connect", RpcPortGetError(nRetVal));

	RUN_POLLING_LOOP;
	if(g_bCallbackCalled != true)
	{
		FPRINTF("[Line : %d][%s] Callback RpcMessage_Onconnected_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_proxy_add_connected_event_cb");
		return 1;
	}
	if(g_callbackOnMsgReceived != true)
	{

		FPRINTF("[Line : %d][%s] Callback RpcMessage_Onreceived_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_proxy_add_received_event_cb");
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_rpc_port_parcel_get_raw_p
* @since_tizen			6.5
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Gets the raw data of the rpc port parcel handle.
* @scenario				Gets the raw data of the rpc port parcel handle.
* @apicovered			rpc_port_parcel_get_raw
* @passcase				When rpc_port_parcel_get_raw is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_rpc_port_parcel_get_raw_p(void)
{
	START_TEST;
	rpc_port_parcel_h hPortParcel = NULL;
	rpc_port_parcel_h hPortParcelFromRaw = NULL;
	unsigned int nSize = 0;
	char *pszStr = NULL, *pszWriteString = "test";
	void *pszRaw = NULL;

	int nRetVal = rpc_port_parcel_create(&hPortParcel);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_create", RpcPortGetError(nRetVal));
	CHECK_HANDLE(hPortParcel, "rpc_port_parcel_create");

	nRetVal = rpc_port_parcel_write_string(hPortParcel, pszWriteString);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_write_string", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));

	nRetVal = rpc_port_parcel_get_raw(hPortParcel, &pszRaw, &nSize);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_get_raw", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	CHECK_HANDLE_CLEANUP(pszRaw, "rpc_port_parcel_get_raw",rpc_port_parcel_destroy(hPortParcel));
	if( nSize == 0)
	{
		FPRINTF("[Line : %d][%s] nSize is 0\\n", __LINE__, API_NAMESPACE);
		rpc_port_parcel_destroy(hPortParcel);
		return 1;
	}

	nRetVal = rpc_port_parcel_destroy(hPortParcel);
	PRINT_RESULT_NORETURN(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_destroy", RpcPortGetError(nRetVal));

	return nRetVal;
}

/**
* @testcase 			ITc_rpc_port_parcel_create_from_raw_p
* @since_tizen			6.5
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Creates the rpc port parcel handle with given the raw data.
* @scenario				Creates the rpc port parcel handle with given the raw data.
* @apicovered			rpc_port_parcel_create_from_raw
* @passcase				When rpc_port_parcel_create_from_raw is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_rpc_port_parcel_create_from_raw_p(void)
{
	START_TEST;
	rpc_port_parcel_h hPortParcel = NULL;
	rpc_port_parcel_h hPortParcelFromRaw = NULL;
	unsigned int nSize = 0, *pszWriteString = "test_create_from_raw";
	char *pszStr = NULL;
	void *pszRaw = NULL;

	int nRetVal = rpc_port_parcel_create(&hPortParcel);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_create", RpcPortGetError(nRetVal));
	CHECK_HANDLE(hPortParcel, "rpc_port_parcel_create");

	nRetVal = rpc_port_parcel_write_string(hPortParcel, pszWriteString);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_write_string", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));

	nRetVal = rpc_port_parcel_get_raw(hPortParcel, &pszRaw, &nSize);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_get_raw", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcel));
	CHECK_HANDLE_CLEANUP(pszRaw, "rpc_port_parcel_get_raw",rpc_port_parcel_destroy(hPortParcel));
	if( nSize == 0)
	{
		FPRINTF("[Line : %d][%s] nSize is 0\\n", __LINE__, API_NAMESPACE);
		rpc_port_parcel_destroy(hPortParcel);
		return 1;
	}

	nRetVal = rpc_port_parcel_create_from_raw(&hPortParcelFromRaw, pszRaw, nSize);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_create_from_raw", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcelFromRaw);rpc_port_parcel_destroy(hPortParcel));
	CHECK_HANDLE_CLEANUP(hPortParcelFromRaw, "rpc_port_parcel_create_from_raw",rpc_port_parcel_destroy(hPortParcel));

	nRetVal = rpc_port_parcel_read_string(hPortParcelFromRaw, &pszStr);
	PRINT_RESULT_CLEANUP(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_read_string", RpcPortGetError(nRetVal),rpc_port_parcel_destroy(hPortParcelFromRaw);rpc_port_parcel_destroy(hPortParcel));
	CHECK_HANDLE_CLEANUP(pszStr, "rpc_port_parcel_read_string",rpc_port_parcel_destroy(hPortParcelFromRaw);rpc_port_parcel_destroy(hPortParcel));

	if (strcmp(pszStr, pszWriteString) != 0)
	{
		FPRINTF("[Line : %d][%s] string mismatch\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszStr);
		rpc_port_parcel_destroy(hPortParcelFromRaw);
		rpc_port_parcel_destroy(hPortParcel);
		return 1;
	}

	FREE_MEMORY(pszStr);
	nRetVal = rpc_port_parcel_destroy(hPortParcelFromRaw);
	PRINT_RESULT_NORETURN(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_destroy", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_parcel_destroy(hPortParcel);
	PRINT_RESULT_NORETURN(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_parcel_destroy", RpcPortGetError(nRetVal));

	return nRetVal;
}
/** @} */
/** @} */
