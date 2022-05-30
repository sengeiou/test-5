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
#include "ITs-capi-message-port-common.h"

/** @addtogroup itc-message-port
* @ingroup		itc
* @{
*/

//& set: MessagePort
static bundle* pstBundleHandle = NULL;
app_control_h g_app_control_handler = NULL;
bool g_bMessagePort = false;

#ifdef TV	//Starts TV
gboolean timeout_func(gpointer data)
{
	g_main_loop_quit((GMainLoop *)data);
	return false;
}
#endif  //TV	//End TV

/**
* @function 		ITs_message_port_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_message_port_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Message_Port_p\\n", __LINE__, API_NAMESPACE);
#endif

	TCT_CheckInstalledApp(1, TEST_MESSAGEPORT_APPID);
	if(LaunchAppToSendMsg(g_szRemoteAppId))
	{
		g_bMessagePort = true;
	}
	pstBundleHandle = bundle_create();
	return;
}

/**
* @function 		ITs_message_port_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_message_port_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Message_Port_p\\n", __LINE__, API_NAMESPACE);
#endif
	
	if(g_bMessagePort)
	{
		TerminateSendToApp();
	}
	bundle_free(pstBundleHandle);
	return;
}

/**
* @function 		__message_port_cb
* @description	 	callback function for message port
* @parameter		int local_nPortId, const char *remote_app_id, const char *remote_port, bool trusted_remote_port, bundle *message, void *user_data
* @return 			NA
*/ 
static void __message_port_cb(int local_nPortId, const char *remote_app_id, const char *remote_port, bool trusted_remote_port, bundle *message, void *user_data)
{
	FPRINTF("[Line : %d][%s] Reached message port callback\\n", __LINE__, API_NAMESPACE);
	return;
}

/** @addtogroup	itc-message-port-testcases
* @brief 		Integration testcases for module message-port
* @ingroup		itc-message-port
* @{
*/

//& purpose: Registers and unregisters local port. 
//& type: auto 
/**
* @testcase 			ITc_message_port_register_unregister_local_port_p
* @since_tizen			2.3
* @author            	SRID(tewari.r)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Registers and unregisters local port
* @scenario				Register local port\n
* 						Unregister local port
* @apicovered			message_port_register_local_port, message_port_unregister_local_port						
* @passcase				When message_port_register_local_port and  message_port_unregister_local_port are successful.
* @failcase				If target API message_port_register_local_port or message_port_unregister_local_port fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_message_port_register_unregister_local_port_p(void)
{
	START_TEST;

	int nPortId = message_port_register_local_port(g_szLocalPort, __message_port_cb, NULL);
	if ( nPortId < 0 )
	{
		FPRINTF("[Line : %d][%s] message_port_register_local_port failed, error returned = %d (%s)\\n", __LINE__, API_NAMESPACE, nPortId, MessagePortGetError(nPortId));
		return 1;
	}

	int nRet = message_port_unregister_local_port(nPortId);
	PRINT_RESULT(MESSAGE_PORT_ERROR_NONE, nRet, "message_port_unregister_local_port", MessagePortGetError(nRet));

	return 0;
}

//& purpose: Registers and unregisters trusted local port. 
//& type: auto 
/**
* @testcase 			ITc_message_port_register_unregister_trusted_local_port_p
* @since_tizen			2.3
* @author            	SRID(tewari.r)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Registers and unregisters trusted local port
* @scenario				Register trusted local port\n
* 						Unregister trusted local port
* @apicovered			message_port_register_trusted_local_port, message_port_unregister_trusted_local_port						
* @passcase				When message_port_register_trusted_local_port and  message_port_unregister_trusted_local_port are successful.
* @failcase				If target api message_port_register_trusted_local_port or message_port_unregister_trusted_local_port fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_message_port_register_unregister_trusted_local_port_p(void)
{
	START_TEST;

	int nPortId = message_port_register_trusted_local_port(g_szLocalPort, __message_port_cb, NULL);
	if ( nPortId < 0 )
	{
		FPRINTF("[Line : %d][%s] message_port_register_trusted_local_port failed, error returned = %d (%s)\\n", __LINE__, API_NAMESPACE, nPortId, MessagePortGetError(nPortId));
		return 1;
	}

	int nRet = message_port_unregister_trusted_local_port(nPortId);
	PRINT_RESULT(MESSAGE_PORT_ERROR_NONE, nRet, "message_port_unregister_trusted_local_port", MessagePortGetError(nRet));

	return 0;
}

//& purpose: Checks remote port. 
//& type: auto 
/**
* @testcase 			ITc_message_port_check_remote_port_p
* @since_tizen			2.3
* @author            	SRID(tewari.r)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Checks remote port
* @scenario				Check remote port
* @apicovered			message_port_check_remote_port						
* @passcase				When message_port_check_remote_port is successful.
* @failcase				If target api message_port_check_remote_port fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_message_port_check_remote_port_p(void)
{
	START_TEST_REMOTE;

	bool bExist = false;
	int nRet = message_port_check_remote_port(g_szRemoteAppId, g_szRemotePort, &bExist);
	PRINT_RESULT(MESSAGE_PORT_ERROR_NONE, nRet, "message_port_check_remote_port", MessagePortGetError(nRet));
	if (!bExist)
	{
		FPRINTF("[Line: %d][%s] message_port_check_remote_port failed, returned bExist :: false\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Checks trusted remote port. 
//& type: auto 
/**
* @testcase 			ITc_message_port_check_trusted_remote_port_p
* @since_tizen			2.3
* @author            	SRID(tewari.r)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Checks trusted remote port
* @scenario				Check trusted remote port
* @apicovered			message_port_check_trusted_remote_port						
* @passcase				When message_port_check_trusted_remote_port is successful.
* @failcase				If target api message_port_check_trusted_remote_port fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_message_port_check_trusted_remote_port_p(void)
{
	START_TEST_REMOTE;

	bool bExist = false;
	
	int nRet = message_port_check_trusted_remote_port(g_szRemoteAppId, g_szRemotePort, &bExist);
	PRINT_RESULT(MESSAGE_PORT_ERROR_NONE, nRet, "message_port_check_trusted_remote_port", MessagePortGetError(nRet));

	return 0;
}

//& purpose: Send message. 
//& type: auto 
/**
* @testcase 			ITc_message_port_send_message_p
* @since_tizen			2.3
* @author            	SRID(tewari.r)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Registers local port, check remote port and send message
* @scenario				Register local port\n
*						Check remote port\n
*						Send message\n
* 						Unregister local port
* @apicovered			message_port_register_local_port, message_port_check_remote_port, message_port_send_message, message_port_unregister_local_port						
* @passcase				When message_port_register_local_port, message_port_check_remote_port and message_port_send_message are successful.
* @failcase				If api message_port_register_local_port, message_port_check_remote_port and message_port_send_message fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_message_port_send_message_p(void)
{
	START_TEST_REMOTE;
	bool bExist = false;
	int nPortId = message_port_register_local_port(g_szLocalPort, __message_port_cb, NULL);
	if ( nPortId < 0 )
	{
		FPRINTF("[Line : %d][%s] message_port_register_local_port failed, error returned = %d(%s)\\n", __LINE__, API_NAMESPACE, nPortId,MessagePortGetError(nPortId));
		return 1;
	}
	sleep(2);
	int nRet = message_port_check_remote_port(g_szRemoteAppId, g_szRemotePort, &bExist);
	PRINT_RESULT_CLEANUP(MESSAGE_PORT_ERROR_NONE, nRet, "message_port_check_remote_port", MessagePortGetError(nRet), message_port_unregister_local_port(nPortId));
	if (!bExist)
	{
		FPRINTF("[Line: %d][%s] message_port_check_remote_port failed, returned bExist :: false\\n", __LINE__, API_NAMESPACE);
		message_port_unregister_local_port(nPortId);
		return 1;
	}
	nRet = message_port_send_message(g_szRemoteAppId, g_szRemotePort, pstBundleHandle);
	PRINT_RESULT_CLEANUP(MESSAGE_PORT_ERROR_NONE, nRet, "message_port_send_message", MessagePortGetError(nRet), message_port_unregister_local_port(nPortId));

	nRet = message_port_unregister_local_port(nPortId);
	PRINT_RESULT(MESSAGE_PORT_ERROR_NONE, nRet, "message_port_unregister_local_port", MessagePortGetError(nRet));
	
	return 0;
}

//& purpose: Send message. 
//& type: auto 
/**
* @testcase 			ITc_message_port_send_message_with_local_port_p
* @since_tizen			2.3
* @author            	SRID(tewari.r)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Registers local port, check remote port and send message\n
* @scenario				Register local port\n
*						Check remote port\n
*						Send message\n
* 						Unregister local port.
* @apicovered			message_port_register_local_port, message_port_check_remote_port, message_port_send_message, message_port_unregister_local_port						
* @passcase				When message_port_register_local_port, message_port_check_remote_port and message_port_send_message are successful.
* @failcase				If api message_port_register_local_port, message_port_check_remote_port and message_port_send_message fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_message_port_send_message_with_local_port_p(void)
{
	START_TEST_REMOTE;
	bool bExist = false;
		
	int nPortId = message_port_register_local_port(g_szLocalPort, __message_port_cb, NULL);
	if ( nPortId < 0 )
	{
		FPRINTF("[Line : %d][%s] message_port_register_local_port failed, error returned = %d(%s)\\n", __LINE__, API_NAMESPACE, nPortId,MessagePortGetError(nPortId));
		return 1;
	}
	sleep(2);
	
	int nRet = message_port_check_remote_port(g_szRemoteAppId, g_szRemotePort, &bExist);
	PRINT_RESULT_CLEANUP(MESSAGE_PORT_ERROR_NONE, nRet, "message_port_check_remote_port", MessagePortGetError(nRet), message_port_unregister_local_port(nPortId));
	if (!bExist)
	{
		FPRINTF("[Line: %d][%s] message_port_check_remote_port failed, returned bExist :: false\\n", __LINE__, API_NAMESPACE);
		message_port_unregister_local_port(nPortId);
		return 1;
	}
	nRet = message_port_send_message_with_local_port(g_szRemoteAppId, g_szRemotePort, pstBundleHandle, nPortId);
	PRINT_RESULT_CLEANUP(MESSAGE_PORT_ERROR_NONE, nRet, "message_port_send_message_with_local_port", MessagePortGetError(nRet), message_port_unregister_local_port(nPortId));

	nRet = message_port_unregister_local_port(nPortId);
	PRINT_RESULT(MESSAGE_PORT_ERROR_NONE, nRet, "message_port_unregister_local_port", MessagePortGetError(nRet));
	
	return 0;
}

//& purpose: Add a callback to watch that remote port is registered.
//& type: auto 
/**
* @testcase 		ITc_message_port_add_registered_cb_p
* @since_tizen		4.0
* @author            	SRID(j.abhishek)
* @reviewer         	SRID(nibha.sharma)
* @type 		auto
* @description		Add a callback to watch that remote port is registered.
* @scenario		Call message_port_add_registered_cb api
* @apicovered		message_port_add_registered_cb
* @passcase		When message_port_add_registered_cb is successful.
* @failcase		If api message_port_add_registered_cb fails.
* @precondition		NA
* @postcondition	NA
*/
int ITc_message_port_add_registered_cb_p(void)
{
	START_TEST_REMOTE;

	int nRet = MESSAGE_PORT_ERROR_NONE;
	int watcher_id = 0;

	nRet = message_port_add_registered_cb(g_szRemoteAppId, g_szRemotePort, 1, __message_port_cb, NULL, &watcher_id);
	if (!watcher_id)
	{
		FPRINTF("[Line: %d][%s] message_port_add_registered_cb failed, returned watcher_id :: 0\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	PRINT_RESULT(MESSAGE_PORT_ERROR_NONE, nRet, "message_port_add_registered_cb", MessagePortGetError(nRet));
	
	return 0;
}


//& purpose: Add a callback to watch that remote port is unregistered.
//& type: auto 
/**
* @testcase 		ITc_message_port_add_unregistered_cb_p
* @since_tizen		4.0
* @author            	SRID(j.abhishek)
* @reviewer         	SRID(nibha.sharma)
* @type 		auto
* @description		Add a callback to watch that remote port is unregistered.
* @scenario		Call message_port_add_unregistered_cb api
* @apicovered		message_port_add_unregistered_cb
* @passcase		When message_port_add_unregistered_cb is successful.
* @failcase		If api message_port_add_unregistered_cb fails.
* @precondition		NA
* @postcondition	NA
*/
int ITc_message_port_add_unregistered_cb_p(void)
{
	START_TEST_REMOTE;

	int nRet = MESSAGE_PORT_ERROR_NONE;
	int watcher_id = 0;

	nRet = message_port_add_unregistered_cb(g_szTerminatedRemoteAppId, g_szRemotePort, 1, __message_port_cb, NULL, &watcher_id);
	if (!watcher_id)
	{
		FPRINTF("[Line: %d][%s] message_port_add_registered_cb failed, returned watcher_id :: 0\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	PRINT_RESULT(MESSAGE_PORT_ERROR_NONE, nRet, "message_port_add_unregistered_cb", MessagePortGetError(nRet));
	
	return 0;
}

//& purpose: Remove a callback to watch that remote port is registered.
//& type: auto 
/**
* @testcase 		ITc_message_port_remove_registration_event_cb_p
* @since_tizen		4.0
* @author            	SRID(j.abhishek)
* @reviewer         	SRID(nibha.sharma)
* @type 		auto
* @description		Remove a callback to watch that remote port is registered.
* @scenario		Call message_port_remove_registration_event_cb api
* @apicovered		message_port_remove_registration_event_cb
* @passcase		When message_port_remove_registration_event_cb is successful.
* @failcase		If api message_port_remove_registration_event_cb fails.
* @precondition		Add a callback to watch that remote port is registered.
* @postcondition	NA
*/
int ITc_message_port_remove_registration_event_cb_p(void)
{
	START_TEST_REMOTE;

	int nRet = MESSAGE_PORT_ERROR_NONE;
	int watcher_id = 0;

	nRet = message_port_add_registered_cb(g_szRemoteAppId, g_szRemotePort, 1, __message_port_cb, NULL, &watcher_id);
	if (!watcher_id)
	{
		FPRINTF("[Line: %d][%s] message_port_add_registered_cb failed, returned watcher_id :: 0\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	PRINT_RESULT(MESSAGE_PORT_ERROR_NONE, nRet, "message_port_add_registered_cb", MessagePortGetError(nRet));

	nRet = message_port_remove_registration_event_cb(watcher_id);
	PRINT_RESULT(MESSAGE_PORT_ERROR_NONE, nRet, "message_port_remove_registration_event_cb", MessagePortGetError(nRet));

	return 0;
}


/** @} */ //end of itc-message-port
/** @} */ //end of itc-message-port-testcases
