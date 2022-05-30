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
static cion_peer_info_h g_hPeer;
bool bIsServerDiscovered = false;

/**
* @function 		ConnectionRequestCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ConnectionRequestCB(const char *service_name,const cion_peer_info_h peer_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback ConnectionRequestCB called\\n", __LINE__, API_NAMESPACE);
	int nRetVal = -1;
	cion_server_h hServer = (cion_server_h)user_data;

	nRetVal = cion_server_accept(hServer, peer_info);
	if (nRetVal != CION_ERROR_NONE)
		FPRINTF("[Line : %d][%s] Failed to accept client\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ServerDiscoveredCB
* @description	 	Callback function
* @parameter		const char *service_name,const cion_peer_info_h peer_info, void *user_data
* @return 			NA
*/
static void ServerDiscoveredCB(const char *service_name,const cion_peer_info_h peer_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback ServerDiscoveredCB called\\n", __LINE__, API_NAMESPACE);
	int nRetVal = -1;
	nRetVal = cion_peer_info_clone(peer_info, &g_hPeer);
	if (nRetVal != CION_ERROR_NONE)
		FPRINTF("[Line : %d][%s] Failed cion_peer_info_clone\\n", __LINE__, API_NAMESPACE);
	bIsServerDiscovered = true;

	if (g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
 * @function 		ITs_cion_peer_info_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_cion_peer_info_startup(void)
{
	g_bCionPayloadCreation = false;
	g_hClient = NULL;
	g_hServer = NULL;
	g_hPeer = NULL;
	bIsServerDiscovered = false;
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	int nRetVal = -1;
	nRetVal = cion_server_create(&g_hServer, "ITs_cion_peer_info_startup","ITs_cion_peer_info_startup", NULL);
	if (nRetVal != CION_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] cion_server_create Failed\\n", __LINE__, API_NAMESPACE);
		return;
	}
	if (g_hServer == NULL)
	{
		FPRINTF("[Line : %d][%s] g_hServer is NULL\\n", __LINE__, API_NAMESPACE);
		return;
	}

	nRetVal = cion_client_create(&g_hClient, "ITs_cion_peer_info_startup",NULL);
	if (nRetVal != CION_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] cion_client_create Failed\\n", __LINE__, API_NAMESPACE);
		return;
	}
	if (g_hClient == NULL)
	{
		FPRINTF("[Line : %d][%s] g_hClient is NULL\\n", __LINE__, API_NAMESPACE);
		return;
	}

	nRetVal = cion_server_listen(g_hServer, ConnectionRequestCB,NULL);
	if (nRetVal != CION_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] cion_server_listen Failed\\n", __LINE__, API_NAMESPACE);
		return;
	}

	nRetVal = cion_client_try_discovery(g_hClient, ServerDiscoveredCB, NULL);
	RUN_POLLING_LOOP;
	sleep(2);
	if (nRetVal != CION_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] cion_client_try_discovery Failed\\n", __LINE__, API_NAMESPACE);
		return;
	}
	g_bCionPayloadCreation = true;
	return;
}


/**
 * @function 		ITs_cion_peer_info_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_cion_peer_info_cleanup(void)
{
	int nRetVal = -1;
	bIsServerDiscovered = false;
	if(g_hPeer)
	{
		nRetVal = cion_peer_info_destroy(g_hPeer);
		if (nRetVal != CION_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] cion_peer_info_destroy Failed\\n", __LINE__, API_NAMESPACE);
			return;
		}
		g_hPeer = NULL;
	}
	if(g_hClient)
	{
		nRetVal = cion_client_stop_discovery(g_hClient);
		if (nRetVal != CION_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] cion_client_destroy Failed\\n", __LINE__, API_NAMESPACE);
			return;
		}
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

//& purpose: Creates and Destroy a clone of peer info handle.
//& type: auto
/**
* @testcase 			ITc_cion_peer_info_clone_destroy_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates and Destroy a clone of peer info handle.
* @scenario				Creates and Destroy a clone of peer info handle.
* @apicovered			cion_peer_info_clone,cion_peer_info_destroy
* @passcase				If cion_peer_info_clone,cion_peer_info_destroy is successfull
* @failcase 			If cion_peer_info_clone,cion_peer_info_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_peer_info_clone_destroy_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	cion_peer_info_h hClone;

	if (bIsServerDiscovered == false)
	{
		FPRINTF("[Line : %d][%s] precondition failed. server not discovered\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = cion_peer_info_clone(g_hPeer, &hClone);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_peer_info_clone", CionGetError(nRetVal));

	nRetVal = cion_peer_info_destroy(hClone);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_peer_info_destroy", CionGetError(nRetVal));
	hClone = NULL;

	return 0;
}

//& purpose: Gets the device ID.
//& type: auto
/**
* @testcase 			ITc_cion_peer_info_get_device_id_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the device ID.
* @scenario				Gets the device ID.
* @apicovered			cion_peer_info_get_device_id
* @passcase				If cion_peer_info_get_device_id is successfull
* @failcase 			If cion_peer_info_get_device_id fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_peer_info_get_device_id_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	char *device_id = NULL;

	if (bIsServerDiscovered == false)
	{
		FPRINTF("[Line : %d][%s] precondition failed. server not discovered\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = cion_peer_info_get_device_id(g_hPeer, &device_id);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_peer_info_get_device_id", CionGetError(nRetVal));
	if (device_id == NULL)
	{
		FPRINTF("[Line : %d][%s] device_id is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	FREE_MEMORY(device_id);

	return 0;
}

//& purpose:  Gets the device name.
//& type: auto
/**
* @testcase 			ITc_cion_peer_info_get_device_name_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the device name.
* @scenario				Gets the device name.
* @apicovered			cion_peer_info_get_device_name
* @passcase				If cion_peer_info_get_device_name is successfull
* @failcase 			If cion_peer_info_get_device_name fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_peer_info_get_device_name_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	char *device_name = NULL;

	if (bIsServerDiscovered == false)
	{
		FPRINTF("[Line : %d][%s] precondition failed. server not discovered\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = cion_peer_info_get_device_name(g_hPeer, &device_name);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_peer_info_get_device_id", CionGetError(nRetVal));
	if (device_name == NULL)
	{
		FPRINTF("[Line : %d][%s] device_name is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	FREE_MEMORY(device_name);

	return 0;
}

//& purpose:  Gets the device's platform.
//& type: auto
/**
* @testcase 			ITc_cion_peer_info_get_device_platform_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the device's platform.
* @scenario				Gets the device's platform.
* @apicovered			cion_peer_info_get_device_platform
* @passcase				If cion_peer_info_get_device_platform is successfull
* @failcase 			If cion_peer_info_get_device_platform fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_peer_info_get_device_platform_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	char *device_platform = NULL;

	if (bIsServerDiscovered == false)
	{
		FPRINTF("[Line : %d][%s] precondition failed. server not discovered\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = cion_peer_info_get_device_platform(g_hPeer, &device_platform);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_peer_info_get_device_platform", CionGetError(nRetVal));
	if (device_platform == NULL)
	{
		FPRINTF("[Line : %d][%s] device_platform is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	FREE_MEMORY(device_platform);

	return 0;
}

//& purpose:  Gets the device's platform version.
//& type: auto
/**
* @testcase 			ITc_cion_peer_info_get_device_platform_version_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the device's platform version.
* @scenario				Gets the device's platform version.
* @apicovered			cion_peer_info_get_device_platform_version
* @passcase				If cion_peer_info_get_device_platform_version is successfull
* @failcase 			If cion_peer_info_get_device_platform_version fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_peer_info_get_device_platform_version_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	char *device_platform_version = NULL;

	if (bIsServerDiscovered == false)
	{
		FPRINTF("[Line : %d][%s] precondition failed. server not discovered\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = cion_peer_info_get_device_platform_version(g_hPeer,&device_platform_version);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_peer_info_get_device_platform_version", CionGetError(nRetVal));
	if (device_platform_version == NULL)
	{
		FPRINTF("[Line : %d][%s] device_platform_version is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}


	FREE_MEMORY(device_platform_version);

	return 0;
}

//& purpose:  Gets the device's type.
//& type: auto
/**
* @testcase 			ITc_cion_peer_info_get_device_type_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the device's type.
* @scenario				Gets the device's type.
* @apicovered			cion_peer_info_get_device_type
* @passcase				If cion_peer_info_get_device_type is successfull
* @failcase 			If cion_peer_info_get_device_type fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_peer_info_get_device_type_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	char *device_type = NULL;

	if (bIsServerDiscovered == false)
	{
		FPRINTF("[Line : %d][%s] precondition failed. server not discovered\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = cion_peer_info_get_device_type(g_hPeer, &device_type);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_peer_info_get_device_type", CionGetError(nRetVal));
	if (device_type == NULL)
	{
		FPRINTF("[Line : %d][%s] device_type is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	FREE_MEMORY(device_type);

	return 0;
}

//& purpose:  Gets application ID of peer.
//& type: auto
/**
* @testcase 			ITc_cion_peer_info_get_app_id_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets application ID of peer.
* @scenario				Gets application ID of peer.
* @apicovered			cion_peer_info_get_app_id
* @passcase				If cion_peer_info_get_app_id is successfull
* @failcase 			If cion_peer_info_get_app_id fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_peer_info_get_app_id_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	char *app_id = NULL;

	if (bIsServerDiscovered == false)
	{
		FPRINTF("[Line : %d][%s] precondition failed. server not discovered\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = cion_peer_info_get_app_id(g_hPeer, &app_id);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_peer_info_get_app_id", CionGetError(nRetVal));
	if (app_id == NULL)
	{
		FPRINTF("[Line : %d][%s] app_id is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	FREE_MEMORY(app_id);

	return 0;
}

//& purpose:   Gets application version of peer.
//& type: auto
/**
* @testcase 			ITc_cion_peer_info_get_app_version_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets application version of peer.
* @scenario				Gets application version of peer.
* @apicovered			cion_peer_info_get_app_version
* @passcase				If cion_peer_info_get_app_version is successfull
* @failcase 			If cion_peer_info_get_app_version fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_peer_info_get_app_version_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	char *app_version = NULL;

	if (bIsServerDiscovered == false)
	{
		FPRINTF("[Line : %d][%s] precondition failed. server not discovered\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = cion_peer_info_get_app_version(g_hPeer, &app_version);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_peer_info_get_app_id", CionGetError(nRetVal));
	if (app_version == NULL)
	{
		FPRINTF("[Line : %d][%s] app_version is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	FREE_MEMORY(app_version);

	return 0;
}

//& purpose:   Gets UUID of peer.
//& type: auto
/**
* @testcase 			ITc_cion_peer_info_get_uuid_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets UUID of peer.
* @scenario				Gets UUID of peer.
* @apicovered			cion_peer_info_get_uuid
* @passcase				If cion_peer_info_get_uuid is successfull
* @failcase 			If cion_peer_info_get_uuid fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_peer_info_get_uuid_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	char *uuid = NULL;

	if (bIsServerDiscovered == false)
	{
		FPRINTF("[Line : %d][%s] precondition failed. server not discovered\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = cion_peer_info_get_uuid(g_hPeer, &uuid);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_peer_info_get_uuid", CionGetError(nRetVal));
	if (uuid == NULL)
	{
		FPRINTF("[Line : %d][%s] uuid is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	FREE_MEMORY(uuid);

	return 0;
}

//& purpose:    Gets display name of peer.
//& type: auto
/**
* @testcase 			ITc_cion_peer_info_get_display_name_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets display name of peer.
* @scenario				Gets display name of peer.
* @apicovered			cion_peer_info_get_display_name
* @passcase				If cion_peer_info_get_display_name is successfull
* @failcase 			If cion_peer_info_get_display_name fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_peer_info_get_display_name_p(void)
{
	START_TEST_PAYLOAD;
	int nRetVal = -1;
	char *display_name = NULL;

	if (bIsServerDiscovered == false)
	{
		FPRINTF("[Line : %d][%s] precondition failed. server not discovered\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = cion_peer_info_get_display_name(g_hPeer, &display_name);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_peer_info_get_display_name", CionGetError(nRetVal));
	if (display_name == NULL)
	{
		FPRINTF("[Line : %d][%s] display_name is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	FREE_MEMORY(display_name);

	return 0;
}

/** @} */
/** @} */