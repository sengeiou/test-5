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
//#include <app.h>
#include <app_manager.h>
#include <service_app.h>

static rpc_port_proxy_h g_hproxyhandle;

const char g_szService_App_Id[] = "org.example.stubsample";
const char g_szInvalid_Cert_Service_App_Id[] = "org.example.invalidcertstub";
const char g_szInvalid_Privilege_Service_App_Id[] = "org.example.invalidprivilegestub";

const char g_szDisconnecttest[] = "disconnecttest";
const char g_szReceivetest[] = "receivetest";
const char g_szPorttest[] = "porttest";
const char g_szPort_Name[] = "Message";
static char g_szProxygetporttest[] = "proxygetporttest";
const char g_szSharingArraytest[] = "sharingarraytest";
const char g_szSetSharingtest[] = "setsharingtest";
const char g_szUnsetSharingttest[] = "unsetsharingtest";

static int nRet;


/**
* @function 		Rpc_Message_On_Connected_cb
* @description	 	Callback function for rpc_port_proxy_add_connected_event_cb.
* @parameter		const char *endpoint, const char *port_name, rpc_port_h port, void *data
* @return 			NA
*/
static void Rpc_Message_On_Connected_cb(const char *endpoint, const char *port_name, rpc_port_h port, void *data)
{
	FPRINTF("[Line : %d][%s] Inside Callback Rpc_Message_On_Connected_cb \\n", __LINE__, API_NAMESPACE);

	g_bCallbackCalled = true;
	char *pszWrite = NULL;

	if (data == g_szDisconnecttest) {
		FPRINTF("[Line : %d][%s] connected to test disconnect %s\\n", __LINE__, API_NAMESPACE,endpoint);
		pszWrite = "disconnect";

	} else if (data == g_szReceivetest) {
		FPRINTF("[Line : %d][%s] connected to test receive data %s\\n", __LINE__, API_NAMESPACE,endpoint);
		pszWrite = "receive";

	} else if (data == g_szPorttest) {
		FPRINTF("[Line : %d][%s] connected to test read and write data %s\\n", __LINE__, API_NAMESPACE,endpoint);
		pszWrite = "write";
	}
	if ((data == g_szDisconnecttest) || (data == g_szPorttest) || (data == g_szReceivetest))
	{
		rpc_port_parcel_h hParcel;
		g_hReceivedPort = port;
		rpc_port_parcel_create(&hParcel);
		rpc_port_parcel_write_int32(hParcel, Message_METHOD_Send);
		rpc_port_parcel_write_string(hParcel,pszWrite);

		rpc_port_parcel_send(hParcel, port);
		rpc_port_parcel_destroy(hParcel);
		normal_exit(0);
		FPRINTF("[Line : %d][%s] Leaving Callback Rpc_Message_On_Connected_cb \\n", __LINE__, API_NAMESPACE);
		return;
	}
	if (data == g_szProxygetporttest)
	{
		rpc_port_h callback_port;
		int ret;
		ret = rpc_port_proxy_get_port(g_hproxyhandle, RPC_PORT_PORT_CALLBACK, &callback_port);
		if (ret != RPC_PORT_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] rpc_port_proxy_get_port fail %s\\n", __LINE__, API_NAMESPACE,endpoint);
			normal_exit(1);
			return;
		}
		else
		{
			normal_exit(0);
			return;
		}
	}
	if (data == g_szSharingArraytest)
	{
		char pszFile1[PATH_LEN];
		char pszFile2[PATH_LEN];
		const char *pszFiles[3] = { NULL, };
		int nCount = 2;

		GetFilePath("file_name1.txt", pszFile1, sizeof(pszFile1));
		GetFilePath("file_name2.txt", pszFile2, sizeof(pszFile2));
		CreateFile(pszFile1, "test1");
		CreateFile(pszFile2, "test2");

		pszFiles[0] = pszFile1;
		pszFiles[1] = pszFile2;
		nRet = rpc_port_set_private_sharing_array(port, pszFiles, nCount);
		rpc_port_unset_private_sharing(port);
	}
	if (data == g_szSetSharingtest)
	{
		char pszFile[PATH_LEN];
		GetFilePath("file_name.txt", pszFile, sizeof(pszFile));
		CreateFile(pszFile, "test");
		nRet = rpc_port_set_private_sharing(port, pszFile);
		rpc_port_unset_private_sharing(port);
	}
	if (data == g_szUnsetSharingttest)
	{
		nRet = rpc_port_unset_private_sharing(port);
	}

	if (strncmp(endpoint, g_szService_App_Id,strlen(endpoint))) {
		FPRINTF("[Line : %d][%s] Mismatch App Id  \\n", __LINE__, API_NAMESPACE);
		normal_exit(1);
		return;
	}
	normal_exit(0);
	FPRINTF("[Line : %d][%s] Leaving Callback Rpc_Message_On_Connected_cb \\n", __LINE__, API_NAMESPACE);
	return;
}

/**
* @function 		Rpc_Message_On_Connected_cb
* @description	 	Callback function for rpc_port_proxy_add_connected_event_cb.
* @parameter		const char *endpoint, const char *port_name, rpc_port_h port, void *data
* @return 			NA
*/
static void Rpc_Message_On_Connected_cb2(const char *endpoint, const char *port_name, rpc_port_h port, void *data)
{
	FPRINTF("[Line : %d][%s] Inside Callback Rpc_Message_On_Connected_cb2 \\n", __LINE__, API_NAMESPACE);

	g_bCallbackCalled = true;
	char *pszWrite = NULL;
	if (data == g_szDisconnecttest) {
		FPRINTF("[Line : %d][%s] connected to test disconnect %s\\n", __LINE__, API_NAMESPACE,endpoint);
		pszWrite = "disconnect";

	} else if (data == g_szReceivetest) {
		FPRINTF("[Line : %d][%s] connected to test receive data %s\\n", __LINE__, API_NAMESPACE,endpoint);
		pszWrite = "receive";

	} else if (data == g_szPorttest) {
		FPRINTF("[Line : %d][%s] connected to test read and write data %s\\n", __LINE__, API_NAMESPACE,endpoint);
		pszWrite = "write";
	}
	if ((data == g_szDisconnecttest) || (data == g_szPorttest) || (data == g_szReceivetest))
	{
		rpc_port_parcel_h hParcel;
		g_hReceivedPort = port;
		rpc_port_parcel_create(&hParcel);
		rpc_port_parcel_write_int32(hParcel, Message_METHOD_Send);
		rpc_port_parcel_write_string(hParcel,pszWrite);

		rpc_port_parcel_send(hParcel, port);
		rpc_port_parcel_destroy(hParcel);
		g_main_loop_quit(g_pMainLoop);
		return;
	}
	if (data == g_szProxygetporttest) {
		rpc_port_h callback_port;
		int ret;

		ret = rpc_port_proxy_get_port(g_hproxyhandle, RPC_PORT_PORT_CALLBACK, &callback_port);
		if (ret != RPC_PORT_ERROR_NONE) {
			FPRINTF("[Line : %d][%s] connected to test read and write data %s\\n", __LINE__, API_NAMESPACE,endpoint);
			normal_exit(1);
			return;
		} else {
			g_main_loop_quit(g_pMainLoop);
			normal_exit(0);
			return;
		}
	}

	if (strncmp(endpoint, g_szService_App_Id,strlen(endpoint))) {
		FPRINTF("[Line : %d][%s] Mismatch App Id  \\n", __LINE__, API_NAMESPACE);
		normal_exit(1);
		return;
	}
	if (g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
	normal_exit(0);
	FPRINTF("[Line : %d][%s] Leaving Callback Rpc_Message_On_Connected_cb2 \\n", __LINE__, API_NAMESPACE);
	return;
}

/**
* @function 		Rpc_Message_On_Disconnected_cb
* @description	 	Callback function for rpc_port_proxy_add_disconnected_event_cb.
* @parameter		const char *endpoint, const char *port_name, rpc_port_h port, void *data
* @return 			NA
*/
void Rpc_Message_On_Disconnected_cb(const char *endpoint, const char *port_name, void *data)
{
	FPRINTF("[Line : %d][%s] Inside Callback Rpc_Message_On_Disconnected_cb \\n", __LINE__, API_NAMESPACE);
	g_bcallBackDisConnect = true;

	if (strncmp(endpoint, g_szService_App_Id,strlen(endpoint))) {
		FPRINTF("[Line : %d][%s] Mismatch Service App Id error  \\n", __LINE__, API_NAMESPACE);
		g_main_loop_quit(g_pMainLoop);
		normal_exit(1);
		return;
	}

	if (g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
	FPRINTF("[Line : %d][%s] Leaving Callback Rpc_Message_On_Disconnected_cb \\n", __LINE__, API_NAMESPACE);
	normal_exit(0);
	return;
}

/**
* @function 		Rpc_Message_On_Rejected_cb
* @description	 	Callback function for rpc_port_proxy_add_rejected_event_cb.
* @parameter		const char *endpoint, const char *port_name,void *data
* @return 			NA
*/
void Rpc_Message_On_Rejected_cb(const char *endpoint, const char *port_name, void *data)
{
	FPRINTF("[Line : %d][%s] Inside Callback Rpc_Message_On_Rejected_cb \\n", __LINE__, API_NAMESPACE);
	g_bCallbackCalled = true;

	if (strncmp(endpoint, g_szInvalid_Cert_Service_App_Id,strlen(endpoint))) {
		FPRINTF("[Line : %d][%s] Mismatch for Cert App Id error  \\n", __LINE__, API_NAMESPACE);
		g_main_loop_quit(g_pMainLoop);
		normal_exit(1);
		return;
	}

	if (g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
	FPRINTF("[Line : %d][%s] Leaving Callback Rpc_Message_On_Rejected_cb \\n", __LINE__, API_NAMESPACE);
	normal_exit(0);
}

/**
* @function 		Rpc_Message_On_Received_cb
* @description	 	Callback function for rpc_port_proxy_add_received_event_cb.
* @parameter		const char *endpoint, const char *port_name,void *data
* @return 			NA
*/

static void Rpc_Message_On_Received_cb(const char *endpoint, const char *port_name, void *data)
{
	FPRINTF("[Line : %d][%s] Inside Callback Rpc_Message_On_Received_cb \\n", __LINE__, API_NAMESPACE);

	g_callbackMsgreceived = true;

	if (strncmp(endpoint, g_szService_App_Id , strlen(endpoint))) {
		FPRINTF("[Line : %d][%s] Mismatch for Service  App Id error  \\n", __LINE__, API_NAMESPACE);
		g_main_loop_quit(g_pMainLoop);
		normal_exit(1);
		return;
	}
	rpc_port_parcel_h parcel_received = NULL;
	rpc_port_h hreceivedport= NULL;
	int nRet = -1;
	int nRetRead;


	nRetRead = rpc_port_proxy_get_port(g_hproxyhandle, RPC_PORT_PORT_CALLBACK, &hreceivedport);
	if ( nRetRead != RPC_PORT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] rpc_port_proxy_get_port error  \\n", __LINE__, API_NAMESPACE);
		g_main_loop_quit(g_pMainLoop);
		normal_exit(1);
		return;
	}

	nRetRead = rpc_port_parcel_create_from_port(&parcel_received, hreceivedport);
	if(nRetRead != RPC_PORT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] rpc_port_parcel_create_from_port error \\n", __LINE__, API_NAMESPACE);
		g_main_loop_quit(g_pMainLoop);
		normal_exit(1);
		return;
	}
	rpc_port_parcel_read_int32(parcel_received, &nRet);
	if (nRet != 0) {
		FPRINTF("[Line : %d][%s] Invalid protocol \\n", __LINE__, API_NAMESPACE);
		rpc_port_parcel_destroy(parcel_received);
		return;
	}
	rpc_port_parcel_destroy(parcel_received);

	if (data == g_szPorttest)
	{
		FPRINTF("[Line : %d][%s] Port read error \\n", __LINE__, API_NAMESPACE);
		g_main_loop_quit(g_pMainLoop);
		normal_exit(1);
		return;
	}
	if (g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
	FPRINTF("[Line : %d][%s] Leaving Callback Rpc_Message_On_Received_cb \\n", __LINE__, API_NAMESPACE);
	normal_exit(0);
}

/**
* @function 		ITs_rpc_port_proxy_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_rpc_port_proxy_startup(void)
{
	g_hproxyhandle = NULL;
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
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_rpc-port\\n", __LINE__, API_NAMESPACE);
#endif
	g_bRpcPortCreation = true;
	int nRet = rpc_port_proxy_create(&g_hproxyhandle);
	if ( nRet != RPC_PORT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to Create proxy handle, error returned = %s\\n", __LINE__, API_NAMESPACE, RpcPortGetError(nRet));
		g_bRpcPortCreation = false;
	}
	if(g_hproxyhandle == NULL)
	{
		FPRINTF("[Line : %d][%s] Unable to Create proxy handle, error returned = %s\\n", __LINE__, API_NAMESPACE, RpcPortGetError(nRet));
		g_bRpcPortCreation = false;
	}

}

/**
* @function 		ITs_rpc_port_proxy_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_rpc_port_proxy_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: rpc-port\\n", __LINE__, API_NAMESPACE);
#endif
	if(g_bRpcPortCreation)
	{
		if (g_hproxyhandle)
		{
			rpc_port_proxy_destroy(g_hproxyhandle);
		}
	}
}

/**
* @testcase 			ITc_rpc_port_proxy_get_port_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Gets a port from proxy handle
* @scenario				Gets a port from proxy handle
* @apicovered			rpc_port_proxy_get_port
* @passcase				When rpc_port_proxy_get_port is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_rpc_port_proxy_get_port_p(void)
{
	START_TEST;

	rpc_port_h *hPort = NULL;
	g_bCallbackCalled = false;
	int nTimeoutId = -1;
	rpc_port_port_type_e ePortType[]= {
										RPC_PORT_PORT_MAIN, /**< Main channel */
										RPC_PORT_PORT_CALLBACK, /**< The channel for callbacks */
										};
	int ePortTypeSize = sizeof(ePortType)/sizeof(ePortType[0]);
	int nCount = 0;

	int nRetVal = rpc_port_proxy_add_connected_event_cb(g_hproxyhandle,Rpc_Message_On_Connected_cb2, g_szProxygetporttest);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_connected_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_proxy_connect(g_hproxyhandle,g_szService_App_Id, g_szPort_Name);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_connect", RpcPortGetError(nRetVal));
	RUN_POLLING_LOOP;
	if(g_bCallbackCalled != true)
	{

		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_Connected_cb2 not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_proxy_add_connected_event_cb");
		return 1;
	}

	// Target API
	for(nCount = 0;nCount < ePortTypeSize; nCount++)
	{
		hPort = NULL;
		nRetVal = rpc_port_proxy_get_port(g_hproxyhandle, ePortType[nCount],&hPort);
		PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_get_port", RpcPortGetError(nRetVal));
		CHECK_HANDLE(hPort, "rpc_port_proxy_get_port");
	}

	return 0;
}

 /**
* @testcase 			ITc_rpc_port_read_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Reads data from an RPC port
* @scenario				Reads data from an RPC port
* @apicovered			rpc_port_read
* @passcase				When rpc_port_read is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_rpc_port_read_p(void)
{
	START_TEST;
	int nRetVal = rpc_port_proxy_add_connected_event_cb(g_hproxyhandle,Rpc_Message_On_Connected_cb, g_szReceivetest);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_connected_event_cb", RpcPortGetError(nRetVal));

	// Target API
	g_bCallbackCalled = false;
	nRetVal = rpc_port_proxy_add_received_event_cb(g_hproxyhandle,Rpc_Message_On_Received_cb, g_szReceivetest);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_received_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_proxy_connect(g_hproxyhandle,g_szService_App_Id, g_szPort_Name);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_connect", RpcPortGetError(nRetVal));

	RUN_POLLING_LOOP;
	if(g_bCallbackCalled != true)
	{

		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_Connected_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_proxy_add_connected_event_cb");
		return 1;
	}
	if(g_callbackMsgreceived != true)
	{

		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_Received_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_proxy_add_received_event_cb");
		return 1;
	}
	return 0;
}

 /**
* @testcase 			ITc_rpc_port_write_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Writes data to an RPC port
* @scenario				Writes data to an RPC port
* @apicovered			rpc_port_write
* @passcase				When rpc_port_write is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_rpc_port_write_p(void)
{
	START_TEST;
	rpc_port_h *hPort = NULL;
	g_bCallbackCalled = false;
	rpc_port_parcel_h parcel_received = NULL;
	char data[] = "read";
	char buf[256];

	int nTimeoutId = -1;
	int nRetVal = rpc_port_proxy_add_connected_event_cb(g_hproxyhandle,Rpc_Message_On_Connected_cb2, NULL);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_connected_event_cb", RpcPortGetError(nRetVal));

	// Target API
	nRetVal = rpc_port_proxy_connect(g_hproxyhandle,g_szService_App_Id, g_szPort_Name);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_connect", RpcPortGetError(nRetVal));
	RUN_POLLING_LOOP;
	if(g_bCallbackCalled != true)
	{

		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_Connected_cb2 not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_proxy_add_connected_event_cb");
		return 1;
	}
	nRetVal = rpc_port_proxy_get_port(g_hproxyhandle, RPC_PORT_PORT_CALLBACK,&hPort);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_get_port", RpcPortGetError(nRetVal));
	CHECK_HANDLE(hPort, "rpc_port_proxy_get_port");

	nRetVal = rpc_port_write(hPort, buf, sizeof(data));
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_write", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_proxy_create_destroy_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Creates and destroys the rpc port proxy handle
* @scenario				Creates and destroys the rpc port proxy handle
* @apicovered			rpc_port_proxy_create,rpc_port_proxy_destroy
* @passcase				When rpc_port_proxy_create,rpc_port_proxy_destroy is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_proxy_create_destroy_p(void)
{
	START_TEST;
	rpc_port_proxy_h hPortProxy = NULL;

	// Target API
	int nRetVal = rpc_port_proxy_create(&hPortProxy);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_create", RpcPortGetError(nRetVal));
	CHECK_HANDLE(hPortProxy, "rpc_port_proxy_create");

	// Target API
	nRetVal = rpc_port_proxy_destroy(hPortProxy);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_destroy", RpcPortGetError(nRetVal));

	return 0;
}


/**
* @testcase 			ITc_rpc_port_proxy_connect_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Connects to rpc port
* @scenario				Check whether the result is RPC_PORT_ERROR_NONE or NOT
*                       and check if connected callback is called.
* @apicovered			rpc_port_proxy_add_connected_event_cb,rpc_port_proxy_connect
* @passcase				When rpc_port_proxy_connect is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_rpc_port_proxy_connect_p(void)
{
	START_TEST;

	g_bCallbackCalled = false;
	int nTimeoutId = -1;

	int nRetVal = rpc_port_proxy_add_connected_event_cb(g_hproxyhandle,Rpc_Message_On_Connected_cb2, NULL);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_connected_event_cb", RpcPortGetError(nRetVal));

	// Target API
	nRetVal = rpc_port_proxy_connect(g_hproxyhandle,g_szService_App_Id, g_szPort_Name);
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
* @testcase 			ITc_rpc_port_proxy_add_connected_disconnected_event_cb_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Adds connected event callback to handle and ads disconnected event callback to handle
* @scenario				Check whether the result is RPC_PORT_ERROR_NONE or NOT
*                       and check if connected and disconnected callback is called.
* @apicovered			rpc_port_proxy_add_connected_event_cb,rpc_port_proxy_add_disconnected_event_cb,rpc_port_proxy_connect
* @passcase				When rpc_port_proxy_add_connected_event_cb,rpc_port_proxy_add_disconnected_event_cb is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_proxy_add_connected_disconnected_event_cb_p(void)
{
	START_TEST;

	int nTimeoutId = -1;
	g_bCallbackCalled = false;

	// Target API
	int nRetVal = rpc_port_proxy_add_connected_event_cb(g_hproxyhandle,Rpc_Message_On_Connected_cb, g_szDisconnecttest);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_connected_event_cb", RpcPortGetError(nRetVal));

	g_bcallBackDisConnect = false;
	// Target API
	nRetVal = rpc_port_proxy_add_disconnected_event_cb(g_hproxyhandle, Rpc_Message_On_Disconnected_cb, NULL);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_connected_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_proxy_connect(g_hproxyhandle,g_szService_App_Id, g_szPort_Name);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_connect", RpcPortGetError(nRetVal));

	RUN_POLLING_LOOP;

	if( g_bCallbackCalled != true )
	{
		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_Connected_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_proxy_add_connected_event_cb");
		return 1;
	}
	if( g_bcallBackDisConnect != true)
	{

		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_Disconnected_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_proxy_add_connected_event_cb");
		return 1;
	}
	return 0;
}

/**
* @testcase 			ITc_rpc_port_proxy_add_rejected_event_cb_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Adds rejected event callback to handle
* @scenario				Check whether the result is RPC_PORT_ERROR_NONE or NOT
*                       and check if rejected callback is called.
* @apicovered			rpc_port_proxy_add_rejected_event_cb,rpc_port_proxy_connect
* @passcase				When rpc_port_proxy_add_rejected_event_cb is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_proxy_add_rejected_event_cb_p(void)
{
	START_TEST;

	g_bCallbackCalled = false;
	int nTimeoutId = -1;

	// Target API
	int nRetVal = rpc_port_proxy_add_connected_event_cb(g_hproxyhandle,Rpc_Message_On_Connected_cb, NULL);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_connected_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_proxy_add_rejected_event_cb(g_hproxyhandle,Rpc_Message_On_Rejected_cb, NULL);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_rejected_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_proxy_connect(g_hproxyhandle,g_szInvalid_Cert_Service_App_Id, g_szPort_Name);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_connect", RpcPortGetError(nRetVal));
	RUN_POLLING_LOOP;
	if(g_bCallbackCalled != true)
	{

		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_Rejected_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_proxy_add_rejected_event_cb");
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_rpc_port_proxy_add_received_event_cb_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Connects to rpc port
* @scenario				Check whether the result is RPC_PORT_ERROR_NONE or NOT
*                       and check if received callback is called.
* @apicovered			rpc_port_proxy_add_received_event_cb,rpc_port_proxy_connect
* @passcase				When rpc_port_proxy_add_received_event_cb is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_proxy_add_received_event_cb_p(void)
{
	START_TEST;

	rpc_port_proxy_h hPortProxy = NULL;
	g_bCallbackCalled = false;
	g_callbackMsgreceived = false;
	int nTimeoutId = -1;

	int nRetVal = rpc_port_proxy_add_connected_event_cb(g_hproxyhandle,Rpc_Message_On_Connected_cb, g_szReceivetest);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_connected_event_cb", RpcPortGetError(nRetVal));

	// Target API
	nRetVal = rpc_port_proxy_add_received_event_cb(g_hproxyhandle,Rpc_Message_On_Received_cb, g_szReceivetest);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_received_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_proxy_connect(g_hproxyhandle,g_szService_App_Id, g_szPort_Name);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_connect", RpcPortGetError(nRetVal));

	RUN_POLLING_LOOP;
	if(g_bCallbackCalled != true)
	{

		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_Connected_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_proxy_add_connected_event_cb");
		return 1;
	}
	if(g_callbackMsgreceived != true)
	{

		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_Received_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_proxy_add_received_event_cb");
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_rpc_port_proxy_connect_sync_p
* @since_tizen			6.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Connects to rpc port synchronously.
* @scenario				Check whether the result is RPC_PORT_ERROR_NONE or NOT
*                       and check if connected callback is called.
* @apicovered			rpc_port_proxy_connect_sync
* @passcase				When rpc_port_proxy_connect_sync is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_rpc_port_proxy_connect_sync_p(void)
{
	START_TEST;

	int nRetVal = -1;
	g_bCallbackCalled = false;

	nRetVal = rpc_port_proxy_add_connected_event_cb(g_hproxyhandle,Rpc_Message_On_Connected_cb, NULL);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_connected_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_proxy_connect_sync(g_hproxyhandle,g_szService_App_Id, g_szPort_Name);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_connect_sync", RpcPortGetError(nRetVal));
	PRINT_RESULT(true, g_bCallbackCalled, "rpc_port_proxy_connect_sync", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_set_private_sharing_array_p
* @since_tizen			6.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Shares files for the stub application.
* @scenario				Check whether the result is RPC_PORT_ERROR_NONE or NOT
*                       Sets the paths of private sharing files.
* @apicovered			rpc_port_set_private_sharing_array
* @passcase				When rpc_port_set_private_sharing_array is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_rpc_port_set_private_sharing_array_p(void)
{
	START_TEST;

	int nRetVal = -1;
	nRet = -1;
	g_bCallbackCalled = false;

	nRetVal = rpc_port_proxy_add_connected_event_cb(g_hproxyhandle,Rpc_Message_On_Connected_cb, g_szSharingArraytest);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_connected_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_proxy_connect_sync(g_hproxyhandle,g_szService_App_Id, g_szPort_Name);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_connect_sync", RpcPortGetError(nRetVal));
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRet, "rpc_port_set_private_sharing_array", RpcPortGetError(nRetVal));
	PRINT_RESULT(true, g_bCallbackCalled, "rpc_port_set_private_sharing_array", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_set_private_sharing_p
* @since_tizen			6.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Shares a file for the stub application.
* @scenario				Check whether the result is RPC_PORT_ERROR_NONE or NOT
*                       Sets the path of the private sharing file.
* @apicovered			rpc_port_set_private_sharing
* @passcase				When rpc_port_set_private_sharing is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_rpc_port_set_private_sharing_p(void)
{
	START_TEST;

	int nRetVal = -1;
	nRet = -1;
	g_bCallbackCalled = false;


	nRetVal = rpc_port_proxy_add_connected_event_cb(g_hproxyhandle,Rpc_Message_On_Connected_cb, g_szSetSharingtest);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_connected_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_proxy_connect_sync(g_hproxyhandle,g_szService_App_Id, g_szPort_Name);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_connect_sync", RpcPortGetError(nRetVal));
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRet, "rpc_port_set_private_sharing", RpcPortGetError(nRetVal));
	PRINT_RESULT(true, g_bCallbackCalled, "rpc_port_set_private_sharing", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_unset_private_sharing_p
* @since_tizen			6.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Unshares the file.
* @scenario				Check whether the result is RPC_PORT_ERROR_NONE or NOT
*                       Unsets the private sharing.
* @apicovered			rpc_port_unset_private_sharing
* @passcase				When rpc_port_unset_private_sharing is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_rpc_port_unset_private_sharing_p(void)
{
	START_TEST;

	int nRetVal = -1;
	nRet = -1;
	g_bCallbackCalled = false;

	nRetVal = rpc_port_proxy_add_connected_event_cb(g_hproxyhandle,Rpc_Message_On_Connected_cb, g_szUnsetSharingttest);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_add_connected_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_proxy_connect_sync(g_hproxyhandle,g_szService_App_Id, g_szPort_Name);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_proxy_connect_sync", RpcPortGetError(nRetVal));
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRet, "rpc_port_unset_private_sharing", RpcPortGetError(nRetVal));
	PRINT_RESULT(true, g_bCallbackCalled, "rpc_port_unset_private_sharing", RpcPortGetError(nRetVal));

	return 0;
}

/** @} */
/** @} */
