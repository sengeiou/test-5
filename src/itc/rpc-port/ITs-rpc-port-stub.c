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

#include <app_manager.h>
#include <service_app.h>

static rpc_port_stub_h g_hstubhandle;

const char g_szProxyAppID[] = "org.example.proxyrpcport";
static char g_szDisconnecttest[] = "disconnecttest";
static const char g_szReceivetest[] = "receivetest";
const char g_szPort_Name_Stubtest[] = "Message2";
static char g_szStubgetporttest[] = "stubgetporttest";
static char g_szStubgetdisconnectport[] = "disconnectporttest";

/**
* @function 		Rpc_Message_On_Connected_stub_cb
* @description	 	Callback function for rpc_port_stub_add_connected_event_cb.
* @parameter		const char *sender, const char *instance, void *data
* @return 			NA
*/
static void Rpc_Message_On_Connected_stub_cb(const char *sender, const char *instance, void *data)
{
	FPRINTF("[Line : %d][%s] Inside Callback Rpc_Message_On_Connected_stub_cb \\n", __LINE__, API_NAMESPACE);
	g_bCallbackCalled = true;

	if (data == g_szStubgetporttest) 
	{
		FPRINTF("[Line : %d][%s] rpc_port_stub_get_port called \\n", __LINE__, API_NAMESPACE);
		rpc_port_h hPort = NULL;
		int nRetVal = rpc_port_stub_get_port(g_hstubhandle, RPC_PORT_PORT_CALLBACK,instance,&hPort);
		if (nRetVal != RPC_PORT_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] rpc_port_stub_get_port error  \\n", __LINE__, API_NAMESPACE);
			normal_exit(1);
			return;
		}
		else
		{
			normal_exit(0);
			return;
		}
	}
	else if (data == g_szStubgetdisconnectport)
	{
		FPRINTF("[Line : %d][%s] rpc_port_stub_get_port called \\n", __LINE__, API_NAMESPACE);
		rpc_port_h hPort = NULL;
		int nRetVal = rpc_port_stub_get_port(g_hstubhandle, RPC_PORT_PORT_CALLBACK,instance,&hPort);
		if (nRetVal != RPC_PORT_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] rpc_port_stub_get_port error  \\n", __LINE__, API_NAMESPACE);
			normal_exit(1);
			return;
		}
		nRetVal = rpc_port_disconnect(hPort);
		if (nRetVal != RPC_PORT_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] rpc_port_disconnect error  \\n", __LINE__, API_NAMESPACE);
			normal_exit(1);
			return;
		}
		else
		{
			normal_exit(0);
			return;
		}
	}
	if (strncmp(sender, g_szProxyAppID,strlen(sender)))
	{
		FPRINTF("[Line : %d][%s] Mismatch for Proxy App Id error  \\n", __LINE__, API_NAMESPACE);
		normal_exit(1);
	}
	FPRINTF("[Line : %d][%s] Leaving Callback Rpc_Message_On_Connected_stub_cb \\n", __LINE__, API_NAMESPACE);
	return;
}

/**
* @function 		Rpc_Message_On_Connected_stub_single_cb
* @description	 	Callback function for rpc_port_stub_add_connected_event_cb.
* @parameter		const char *sender, const char *instance, void *data
* @return 			NA
*/
static void Rpc_Message_On_Connected_stub_single_cb(const char *sender, const char *instance, void *data)
{
	FPRINTF("[Line : %d][%s] Inside Callback Rpc_Message_On_Connected_stub_single_cb \\n", __LINE__, API_NAMESPACE);
	g_bCallbackCalled = true;

	if (strncmp(sender, g_szProxyAppID,strlen(sender)))
	{
		FPRINTF("[Line : %d][%s] Mismatch for Proxy App Id error  \\n", __LINE__, API_NAMESPACE);
		g_main_loop_quit(g_pMainLoop);
		normal_exit(1);
	}
	if (data == g_szStubgetporttest)
	{
		FPRINTF("[Line : %d][%s] rpc_port_stub_get_port called \\n", __LINE__, API_NAMESPACE);
		rpc_port_h hPort = NULL;
		int nRetVal = rpc_port_stub_get_port(g_hstubhandle, RPC_PORT_PORT_CALLBACK,instance,&hPort);
		if (nRetVal != RPC_PORT_ERROR_NONE) 
		{
			FPRINTF("[Line : %d][%s] rpc_port_stub_get_port error  \\n", __LINE__, API_NAMESPACE);
			g_main_loop_quit(g_pMainLoop);
			normal_exit(1);
			return;
		}
		else
		{
			normal_exit(0);
			return;
		}
	}
	g_main_loop_quit(g_pMainLoop);
	FPRINTF("[Line : %d][%s] Leaving Callback Rpc_Message_On_Connected_stub_single_cb \\n", __LINE__, API_NAMESPACE);
	return;
}

/**
* @function 		Rpc_Message_On_DisConnected_stub_cb
* @description	 	Callback function for rpc_port_stub_add_disconnected_event_cb.
* @parameter		const char *sender, const char *instance, void *data
* @return 			NA
*/
void Rpc_Message_On_DisConnected_stub_cb(const char *sender, const char *instance, void *data)
{
	FPRINTF("[Line : %d][%s] Inside Callback Rpc_Message_On_DisConnected_stub_cb \\n", __LINE__, API_NAMESPACE);

	g_bcallBackDisConnect = true;

	if (strncmp(sender, g_szProxyAppID,strlen(sender))) {
		FPRINTF("[Line : %d][%s] Mismatch for Proxy App Iderror  \\n", __LINE__, API_NAMESPACE);
		g_main_loop_quit(g_pMainLoop);
		normal_exit(1);
		return;
	}
	FPRINTF("[Line : %d][%s] Leaving Rpc_Message_On_DisConnected_stub_cb \\n", __LINE__, API_NAMESPACE);
	if (g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
	normal_exit(0);
	return;
}
/**
* @function 		Rpc_Message_On_Received_stub_cb
* @description	 	Callback function for rpc_port_stub_add_received_event_cb.
* @parameter		const char *sender, const char *instance, rpc_port_h port, void *data
* @return 			NA
*/
int Rpc_Message_On_Received_stub_cb(const char *sender, const char *instance, rpc_port_h port, void *data)
{
	FPRINTF("[Line : %d][%s] Inside Callback Rpc_Message_On_Received_stub_cb \\n", __LINE__, API_NAMESPACE);

	g_callbackMsgreceived = true;

	if (strncmp(sender, g_szProxyAppID,strlen(sender))) {
		normal_exit(1);
		return 0;
	}

	rpc_port_parcel_h parcel_received = NULL;
	int nMsgRec = -1;
	int nRep = 0;
	char *pszMsg = NULL;

	if (data == g_szDisconnecttest)
	{
		nRep = -1;
	}

	int nRet = rpc_port_parcel_create_from_port(&parcel_received, port);
	if(nRet != RPC_PORT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] rpc_port_parcel_create_from_port error \\n", __LINE__, API_NAMESPACE);
		normal_exit(1);
		return 0;
	}
	rpc_port_parcel_read_int32(parcel_received, &nMsgRec);
	rpc_port_parcel_read_string(parcel_received, &pszMsg);
	if (nMsgRec != Message_METHOD_Send)
	{
		FPRINTF("[Line : %d][%s] Error in SEND \\n", __LINE__, API_NAMESPACE);
		rpc_port_parcel_destroy(parcel_received);
		normal_exit(1);
		FREE_MEMORY(pszMsg);
		return 0;
	}
	rpc_port_parcel_destroy(parcel_received);

	rpc_port_parcel_h hParcel;
	rpc_port_parcel_create(&hParcel);
	rpc_port_parcel_write_int32(hParcel, Message_METHOD_Result);
	rpc_port_parcel_write_int32(hParcel, nRep);
	rpc_port_parcel_send(hParcel, port);
	rpc_port_parcel_destroy(hParcel);

	if (data == g_szDisconnecttest) {
		return 0;
	}

	FREE_MEMORY(pszMsg);
	normal_exit(0);
	FPRINTF("[Line : %d][%s] Leaving Rpc_Message_On_Received_stub_cb \\n", __LINE__, API_NAMESPACE);
	return 0;
}

/**
* @function 		Rpc_Message_On_Received_stub_end_cb
* @description	 	Callback function for rpc_port_stub_add_received_event_cb.
* @parameter		const char *sender, const char *instance, rpc_port_h port, void *data
* @return 			NA
*/
int Rpc_Message_On_Received_stub_end_cb(const char *sender, const char *instance, rpc_port_h port, void *data)
{
	FPRINTF("[Line : %d][%s] Inside Callback Rpc_Message_On_Received_stub_end_cb \\n", __LINE__, API_NAMESPACE);

	g_callbackMsgreceived = true;

	if (strncmp(sender, g_szProxyAppID,strlen(sender))) {
		normal_exit(1);
		return 0;
	}

	rpc_port_parcel_h parcel_received = NULL;
	int nMsgRec = -1;
	int nRep = 0;
	char *pszMsg = NULL;

	if (data == g_szDisconnecttest)
	{
		nRep = -1;
	}

	int nRet = rpc_port_parcel_create_from_port(&parcel_received, port);
	if(nRet != RPC_PORT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] rpc_port_parcel_create_from_port error \\n", __LINE__, API_NAMESPACE);
		g_main_loop_quit(g_pMainLoop);
		normal_exit(1);
		return 0;
	}
	nRet = rpc_port_parcel_read_int32(parcel_received, &nMsgRec);
	if(nRet != RPC_PORT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] rpc_port_parcel_read_int32 error \\n", __LINE__, API_NAMESPACE);
		g_main_loop_quit(g_pMainLoop);
		normal_exit(1);
		return 0;
	}
	nRet = rpc_port_parcel_read_string(parcel_received, &pszMsg);
	if(nRet != RPC_PORT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] rpc_port_parcel_read_string error \\n", __LINE__, API_NAMESPACE);
		g_main_loop_quit(g_pMainLoop);
		normal_exit(1);
		return 0;
	}
	if (nMsgRec != Message_METHOD_Send)
	{
		FPRINTF("[Line : %d][%s] Error in SEND \\n", __LINE__, API_NAMESPACE);
		rpc_port_parcel_destroy(parcel_received);
		g_main_loop_quit(g_pMainLoop);
		normal_exit(1);
		FREE_MEMORY(pszMsg);
		return 0;
	}

	rpc_port_parcel_destroy(parcel_received);

	rpc_port_parcel_h hParcel;
	rpc_port_parcel_create(&hParcel);
	rpc_port_parcel_write_int32(hParcel, Message_METHOD_Result);
	rpc_port_parcel_write_int32(hParcel, nRep);
	rpc_port_parcel_send(hParcel, port);
	rpc_port_parcel_destroy(hParcel);

	if (data == g_szDisconnecttest) {
		return 0;
	}

	FREE_MEMORY(pszMsg);
	if (g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
	normal_exit(0);
	FPRINTF("[Line : %d][%s] Leaving Rpc_Message_On_Received_stub_end_cb \\n", __LINE__, API_NAMESPACE);
	return 0;
}
/**
* @function 		RunProxyApp
* @description	 	function for launching proxy app.
* @parameter		NA
* @return 			NA
*/
void RunProxyApp()
 {
	bool bIsRunning = false;
	int nCounter = 30;
	app_control_h hAppCtrl;
	int nRet = app_control_create(&hAppCtrl);
	if (nRet != APP_CONTROL_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] app_control_create error \\n", __LINE__, API_NAMESPACE);
		service_app_exit();
		return;
	}

	nRet = app_control_set_app_id(hAppCtrl, g_szProxyAppID);
	if (nRet != APP_CONTROL_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] app_control_set_app_id error  \\n", __LINE__, API_NAMESPACE);
		service_app_exit();
		return;
	}

	do
	{
		nRet = app_control_send_launch_request(hAppCtrl, NULL, NULL);
		if (nRet != APP_CONTROL_ERROR_NONE)
		{
			sleep(1);
		}
		app_manager_is_running(g_szProxyAppID, &bIsRunning);
	} while (--nCounter > 0 && !bIsRunning);
	sleep(1);
}
/*
* @function 		ITs_rpc_port_stub_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_rpc_port_stub_startup(void)
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
	g_bRpcPortCreation = true;
	int nRet = rpc_port_stub_create(&g_hstubhandle, g_szPort_Name_Stubtest);
	if ( nRet != RPC_PORT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to Create rpc_port_stub handle, error returned = %s\\n", __LINE__, API_NAMESPACE, RpcPortGetError(nRet));
		g_bRpcPortCreation = false;
	}
	if(g_hstubhandle == NULL)
	{
		FPRINTF("[Line : %d][%s] Unable to Create proxy handle, error returned = %s\\n", __LINE__, API_NAMESPACE, RpcPortGetError(nRet));
		g_bRpcPortCreation = false;
	}
}
/**
* @function 		ITs_rpc_port_stub_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_rpc_port_stub_cleanup(void)
{
	#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: rpc-port\\n", __LINE__, API_NAMESPACE);
#endif
	if (g_hstubhandle)
	{
		rpc_port_stub_destroy(g_hstubhandle);
	}

}

/**
* @testcase 			ITc_rpc_port_stub_get_port_p
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
int ITc_rpc_port_stub_get_port_p(void)
{
	START_TEST;

	g_bCallbackCalled = false;
	g_callbackMsgreceived = false;
	int nTimeoutId = -1;

	int nRetVal = rpc_port_stub_add_connected_event_cb(g_hstubhandle,Rpc_Message_On_Connected_stub_single_cb, g_szStubgetporttest);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_stub_add_connected_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_stub_add_received_event_cb(g_hstubhandle,Rpc_Message_On_Received_stub_end_cb, NULL);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_stub_add_received_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_stub_listen(g_hstubhandle);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_stub_listen", RpcPortGetError(nRetVal));

	RunProxyApp();
	RUN_POLLING_LOOP;

	if(g_bCallbackCalled != true)
	{
		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_Connected_stub_single_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_stub_add_connected_event_cb");
		return 1;
	}
	if(g_callbackMsgreceived != true)
	{
		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_Received_stub_end_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_stub_add_received_event_cb");
		return 1;
	}
	FPRINTF("[Line : %d][%s] Leaving testcase %s\\n", __LINE__, API_NAMESPACE, "ITc_rpc_port_stub_get_port_p");
	return 0;
}

/**
* @testcase 			ITc_rpc_port_stub_create_destroy_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Creates and destroys the rpc port stub handle
* @scenario				Creates and destroys the rpc port stub handle
* @apicovered			rpc_port_stub_create,rpc_port_stub_destroy
* @passcase				When rpc_port_stub_create,rpc_port_stub_destroy is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_stub_create_destroy_p(void)
{
	START_TEST;
	rpc_port_stub_h hPortStub = NULL;

	// Target API
	int nRetVal = rpc_port_stub_create(&hPortStub,"port");
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_stub_create", RpcPortGetError(nRetVal));
	CHECK_HANDLE(hPortStub, "rpc_port_stub_create");

	// Target API
	nRetVal = rpc_port_stub_destroy(hPortStub);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_stub_destroy", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_stub_listen_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Listens the rpc port
* @scenario				Listens the rpc port
* @apicovered			rpc_port_stub_listen
* @passcase				When rpc_port_stub_listen is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_stub_listen_p(void)
{
	START_TEST;
	// Target API
	int nRetVal = rpc_port_stub_listen(g_hstubhandle);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_stub_listen", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_stub_add_privilege_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Adds privilege to rpc port
* @scenario				Adds privilege to rpc port
* @apicovered			rpc_port_stub_add_privilege
* @passcase				When rpc_port_stub_add_privilege is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_rpc_port_stub_add_privilege_p(void)
{
	START_TEST;
	const char* pszPrivilege = "http://tizen.org/alarm.set";
	// Target API
	int nRetVal = rpc_port_stub_add_privilege(g_hstubhandle,pszPrivilege);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_stub_add_privilege", RpcPortGetError(nRetVal));

	return 0;
}
/**
* @testcase 			ITc_rpc_port_stub_set_trusted_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Sets trusted to rpc port
* @scenario				Sets trusted to rpc port
* @apicovered			rpc_port_stub_set_trusted
* @passcase				When rpc_port_stub_set_trusted is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_stub_set_trusted_p(void)
{
	START_TEST;
	bool bVal = true;

	// Target API
	int nRetVal = rpc_port_stub_set_trusted(g_hstubhandle,bVal);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_stub_set_trusted", RpcPortGetError(nRetVal));

	return 0;
}

/**
* @testcase 			ITc_rpc_port_stub_add_connected_received_event_cb_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Adds a stub connected callback
* @scenario				Check whether the result is RPC_PORT_ERROR_NONE or NOT
*                       and check if connected callback is called.
* @apicovered			rpc_port_stub_add_connected_event_cb,rpc_port_stub_add_received_event_cb,rpc_port_stub_listen
* @passcase				When rpc_port_stub_add_connected_event_cb is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_stub_add_connected_received_event_cb_p(void)
{
	START_TEST;

	rpc_port_proxy_h hPortProxy = NULL;
	g_bCallbackCalled = false;
	g_callbackMsgreceived = false;
	int nTimeoutId = -1;

	// Target API
	int nRetVal = rpc_port_stub_add_connected_event_cb(g_hstubhandle,Rpc_Message_On_Connected_stub_cb, NULL);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_stub_add_connected_event_cb", RpcPortGetError(nRetVal));

	// Target API
	nRetVal = rpc_port_stub_add_received_event_cb(g_hstubhandle,Rpc_Message_On_Received_stub_end_cb, NULL);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_stub_add_received_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_stub_listen(g_hstubhandle);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_stub_listen", RpcPortGetError(nRetVal));

	RunProxyApp();
	RUN_POLLING_LOOP;

	if(g_bCallbackCalled != true)
	{
		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_Connected_stub_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_stub_add_connected_event_cb");
		return 1;
	}

	if(g_callbackMsgreceived != true)
	{

		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_Received_stub_end_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_stub_add_received_event_cb");
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_rpc_port_stub_add_disconnected_event_cb_p
* @since_tizen			4.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Adds a stub disconnected callback
* @scenario				Check whether the result is RPC_PORT_ERROR_NONE or NOT
*                       and check if disconnected callback is called.
* @apicovered			rpc_port_stub_add_disconnected_event_cb,rpc_port_stub_add_connected_event_cb,rpc_port_stub_add_received_event_cb,rpc_port_stub_listen
* @passcase				When rpc_port_stub_add_disconnected_event_cb is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/

int ITc_rpc_port_stub_add_disconnected_event_cb_p(void)
{
	START_TEST;
	rpc_port_proxy_h hPortProxy = NULL;
	g_bCallbackCalled = false;
	g_callbackMsgreceived = false;
	g_bcallBackDisConnect = false;
	int nTimeoutId = -1;

	int nRetVal = rpc_port_stub_add_connected_event_cb(g_hstubhandle,Rpc_Message_On_Connected_stub_cb, g_szDisconnecttest);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_stub_add_connected_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_stub_add_received_event_cb(g_hstubhandle,Rpc_Message_On_Received_stub_cb, g_szDisconnecttest);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_stub_add_received_event_cb", RpcPortGetError(nRetVal));

	// Target API
	nRetVal = rpc_port_stub_add_disconnected_event_cb(g_hstubhandle,Rpc_Message_On_DisConnected_stub_cb, NULL);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_stub_add_disconnected_event_cb", RpcPortGetError(nRetVal));


	nRetVal = rpc_port_stub_listen(g_hstubhandle);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_stub_listen", RpcPortGetError(nRetVal));

	RunProxyApp();
	RUN_POLLING_LOOP;

	if(g_bCallbackCalled != true)
	{
		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_Connected_stub_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_stub_add_connected_event_cb");
		return 1;
	}

	if(g_callbackMsgreceived != true)
	{
		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_Received_stub_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_stub_add_received_event_cb");
		return 1;
	}

	if(g_bcallBackDisConnect != true)
	{
		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_DisConnected_stub_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_stub_add_disconnected_event_cb");
		return 1;
	}
	return 0;
}

/**
* @testcase 			ITc_rpc_port_disconnect_p
* @since_tizen			6.5
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Disconnects the port.
* @scenario				Disconnects the port.
* @apicovered			rpc_port_disconnect
* @passcase				When rpc_port_disconnect is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_rpc_port_disconnect_p(void)
{
	START_TEST;

	rpc_port_proxy_h hPortProxy = NULL;
	g_bCallbackCalled = false;
	g_callbackMsgreceived = false;
	g_bcallBackDisConnect = false;
	int nTimeoutId = -1;

	int nRetVal = rpc_port_stub_add_connected_event_cb(g_hstubhandle,Rpc_Message_On_Connected_stub_cb, g_szStubgetdisconnectport);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_stub_add_connected_event_cb", RpcPortGetError(nRetVal));

	nRetVal = rpc_port_stub_add_received_event_cb(g_hstubhandle,Rpc_Message_On_Received_stub_cb, NULL);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_stub_add_received_event_cb", RpcPortGetError(nRetVal));

	// Target API
	nRetVal = rpc_port_stub_add_disconnected_event_cb(g_hstubhandle,Rpc_Message_On_DisConnected_stub_cb, NULL);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_stub_add_disconnected_event_cb", RpcPortGetError(nRetVal));


	nRetVal = rpc_port_stub_listen(g_hstubhandle);
	PRINT_RESULT(RPC_PORT_ERROR_NONE, nRetVal, "rpc_port_stub_listen", RpcPortGetError(nRetVal));

	RunProxyApp();
	RUN_POLLING_LOOP;

	if(g_bCallbackCalled != true)
	{
		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_Connected_stub_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_stub_add_connected_event_cb");
		return 1;
	}

	if(g_callbackMsgreceived != true)
	{
		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_Received_stub_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_stub_add_received_event_cb");
		return 1;
	}

	if(g_bcallBackDisConnect != true)
	{
		FPRINTF("[Line : %d][%s] Callback Rpc_Message_On_DisConnected_stub_cb not invoked for %s\\n", __LINE__, API_NAMESPACE, "rpc_port_stub_add_disconnected_event_cb");
		return 1;
	}
	return 0;
}
/** @} */
/** @} */