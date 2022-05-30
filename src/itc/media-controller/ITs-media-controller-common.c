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
#include "ITs-media-controller-common.h"

/** @addtogroup itc-media-controller
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		MediaControllerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* MediaControllerGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch(nRet)
	{
		case MEDIA_CONTROLLER_ERROR_NONE:						szErrorVal = "MEDIA_CONTROLLER_ERROR_NONE";						break;
		case MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER:			szErrorVal = "MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER";		break;
		case MEDIA_CONTROLLER_ERROR_OUT_OF_MEMORY:				szErrorVal = "MEDIA_CONTROLLER_ERROR_OUT_OF_MEMORY";			break;
		case MEDIA_CONTROLLER_ERROR_INVALID_OPERATION:			szErrorVal = "MEDIA_CONTROLLER_ERROR_INVALID_OPERATION";		break;
		case MEDIA_CONTROLLER_ERROR_FILE_NO_SPACE_ON_DEVICE:	szErrorVal = "MEDIA_CONTROLLER_ERROR_FILE_NO_SPACE_ON_DEVICE";	break;
		case MEDIA_CONTROLLER_ERROR_PERMISSION_DENIED:			szErrorVal = "MEDIA_CONTROLLER_ERROR_PERMISSION_DENIED";		break;
		case MEDIA_CONTROLLER_ERROR_ABILITY_LIMITED_BY_SERVER_APP:			szErrorVal = "MEDIA_CONTROLLER_ERROR_ABILITY_LIMITED_BY_SERVER_APP";		break;
		default: 												szErrorVal = "MEDIA_CONTROLLER_ERROR_UNKNOWN";
	break;
	}
	return szErrorVal;
}

/**
 * @function 		TimeoutFunction
 * @description	 	Called if some callback is not invoked for a particular timeout
 * @parameter		gpointer data
 * @return 			gboolean
 */
gboolean TimeoutFunction(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
	}
	return false;
}

/**
* @function 		IterateGmainLoop
* @description	 	Called to wait
* @parameter		NA
* @return 			NA
*/
void IterateGmainLoop(void)
{
	if(g_CallBackHit != true)
	{
		g_pMainLoop = g_main_loop_new(NULL, false);
		g_nTimeoutId = g_timeout_add(TIMEOUT_CB, TimeoutFunction, g_pMainLoop);
		g_main_loop_run(g_pMainLoop);
		g_source_remove(g_nTimeoutId);
		g_nTimeoutId = 0;
		g_pMainLoop = NULL;
	}
}

/**
* @function 		QuitGmainLoop
* @description	 	Called to quit
* @parameter		NA
* @return 			NA
*/
void QuitGmainLoop(void)
{
	if(g_pMainLoop != NULL)
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		McActivatedClientCb
* @description	 	Called when client callback is activated
* @parameter		pszClientName: client name
*			userData: user data
* @return 		success status
*/
bool McActivatedClientCb(const char *pszClientName, void *userData)
{
	char **pszGetName = (char **)userData;
	int nSize = strlen(pszClientName);

	if(strncmp(pszClientName, g_mcTestAppName, nSize) == 0)
	{
		if (pszGetName != NULL)
			*pszGetName = g_strdup(pszClientName);
		FPRINTF("[LINE: %d][ %s ] Callback was hit and client name matches test app name", __LINE__, __FUNCTION__);
		g_CallBackHit = TRUE;
		return FALSE;
	}

	FPRINTF("[LINE: %d][ %s ] Callback was hit but client name did not match test app name", __LINE__, __FUNCTION__);
	return TRUE;
}

/**
* @function 		EventReceivedCallback
* @description	 	Called when client callback is activated
* @parameter		pszObjectName: object name
			pszRequestId: request id
			nResultCode: result code
			bData: extra data
*			userData: user data
* @return 		NA
*/
void EventReceivedCallback(const char *pszObjectName, const char *pszRequestId, int nResultCode, bundle *bData, void *userData)
{
	g_CallBackHit = TRUE;
	QuitGmainLoop();
	return;
}

/**
* @function 		SetServerPlayBackInfo
* @description	 	Set playback info
* @parameter		NA
* @return 			NA
*/
bool SetServerPlayBackInfo(void)
{
	int nRet = -1;

	nRet = mc_server_set_playback_state(g_hMcServer, MC_PLAYBACK_STATE_PLAYING);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_playback_state", MediaControllerGetError(nRet));

	nRet = mc_server_set_playback_position(g_hMcServer, PLAYBACKPOSITION);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_playback_position", MediaControllerGetError(nRet));

	nRet = mc_server_update_playback_info(g_hMcServer);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_playback_info", MediaControllerGetError(nRet));

	return 0;
}

/**
* @function 		SetServerMetaData
* @description	 	Set metadata
* @parameter		NA
* @return 			NA
*/
bool SetServerMetaData(void)
{
	int nRet = -1;
	char *pszEncodedMeta = NULL;
	mc_meta_e eMcMetaType[] = {	MC_META_MEDIA_TITLE,
								MC_META_MEDIA_ARTIST,
								MC_META_MEDIA_ALBUM,
								MC_META_MEDIA_AUTHOR,
								MC_META_MEDIA_GENRE,
								MC_META_MEDIA_DURATION,
								MC_META_MEDIA_DATE,
								MC_META_MEDIA_COPYRIGHT,
								MC_META_MEDIA_DESCRIPTION,
								MC_META_MEDIA_TRACK_NUM,
								MC_META_MEDIA_PICTURE
	};

	static char *eMcTestMetadata[] = {"media_title",
								"media_artist",
								"media_album",
								"media_author",
								"media_genre",
								"200",
								"media_date",
								"media_copyright",
								"media_description",
								"media_track_num 3/10",
								"media_picture_path",
	};

	int nEnumCounter = 0;
	int nEnumSize = sizeof(eMcMetaType) / sizeof(eMcMetaType[0]);
	int nSeasonNum = 15;
	int nEpisodeNum = 15;
	mc_meta_e eSeasonAtribute = 11;
	mc_meta_e eEpisodeAtribute = 12;
	char * pszSeasonTitle = "media_season";
	char * pszEpisodeTitle = "media_episode";

	for (nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		nRet = mc_server_set_metadata(g_hMcServer, eMcMetaType[nEnumCounter], eMcTestMetadata[nEnumCounter]);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_metadata", MediaControllerGetError(nRet));
	}

	nRet = mc_metadata_encode_season(nSeasonNum, pszSeasonTitle, &pszEncodedMeta);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_metadata_encode_season", MediaControllerGetError(nRet));
	CHECK_HANDLE(pszEncodedMeta, "mc_metadata_encode_season");
	nRet = mc_server_set_metadata(g_hMcServer, eSeasonAtribute, pszEncodedMeta);
	FREE_MEMORY(pszEncodedMeta);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_metadata", MediaControllerGetError(nRet));

	nRet = mc_metadata_encode_episode(nEpisodeNum, pszEpisodeTitle, &pszEncodedMeta);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_metadata_encode_episode", MediaControllerGetError(nRet));
	CHECK_HANDLE(pszEncodedMeta, "mc_metadata_encode_episode");
	nRet = mc_server_set_metadata(g_hMcServer, eEpisodeAtribute, pszEncodedMeta);
	FREE_MEMORY(pszEncodedMeta);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_metadata", MediaControllerGetError(nRet));

	nRet = mc_metadata_encode_resolution(META_W, META_H, &pszEncodedMeta);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_metadata_encode_resolution", MediaControllerGetError(nRet));
	CHECK_HANDLE(pszEncodedMeta, "mc_metadata_encode_resolution");
	nRet = mc_server_set_metadata(g_hMcServer, MC_META_MEDIA_RESOLUTION, pszEncodedMeta);
	FREE_MEMORY(pszEncodedMeta);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_metadata", MediaControllerGetError(nRet));

	nRet = mc_server_update_metadata(g_hMcServer);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_metadata", MediaControllerGetError(nRet));

	return 0;
}

/**
* @function 		UpdateServerModes
* @description	 	Update Mode
* @parameter		NA
* @return 			NA
*/
bool UpdateServerModes(void)
{
	int nRet = -1;

	nRet = mc_server_update_repeat_mode(g_hMcServer, MC_REPEAT_MODE_ON);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_repeat_mode", MediaControllerGetError(nRet));

	nRet = mc_server_update_shuffle_mode(g_hMcServer, MC_SHUFFLE_MODE_ON);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_shuffle_mode", MediaControllerGetError(nRet));

	return 0;
}

/**
* @function 		CreateCompleteServer
* @description	 	Create a Server
* @parameter		NA
* @return 			NA
*/
bool CreateCompleteServer(void)
{
	int nRet = -1;

	nRet = SetServerPlayBackInfo();
	PRINT_RESULT(0, nRet, "SetServerPlayBackInfo", "Return Value Not Correct");

	nRet = SetServerMetaData();
	PRINT_RESULT(0, nRet, "SetServerMetaData", "Return Value Not Correct");

	nRet = UpdateServerModes();
	PRINT_RESULT(0, nRet, "UpdateServerModes", "Return Value Not Correct");

	return 0;
}

/**
* @function 		GetCompleteServerInfo
* @description	 	Get Server Info
* @parameter		NA
* @return 			NA
*/
bool GetCompleteServerInfo(void)
{
	int nRet = -1;

	nRet = CreateCompleteServer();
	PRINT_RESULT(0, nRet, "CreateCompleteServer", "Return Value Not Correct");

	char *pszServerName = NULL;
	mc_server_state_e eServerState = 0;
	nRet = mc_client_get_latest_server_info(g_hMcClient, &pszServerName, &eServerState);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet));
	CHECK_HANDLE(pszServerName, "mc_client_get_latest_server_info");
	if((eServerState < MC_SERVER_STATE_NONE) || (eServerState > MC_SERVER_STATE_DEACTIVATE))
	{
		FPRINTF("[Line : %d][%s] %s Enum returned is out of range =%d \\n", __LINE__, API_NAMESPACE, "eServerState",eServerState);
		FREE_MEMORY(pszServerName);
		return 1;
	}
	strncpy(g_szServerName, pszServerName, PATHLEN);
	FREE_MEMORY(pszServerName);

	FPRINTF("[Line : %d][%s] Server Name is = %s\\n", __LINE__, API_NAMESPACE, g_szServerName);
	return 0;
}

/**
* @function    SetUpdateCallBacks
* @description     Register Update Callbacks
* @parameter   mc_subscription_type_e eSubscriptionType
* @return  NA
*/
bool SetUpdateCallBacks(mc_subscription_type_e eSubscriptionType)
{
       int nRet = -1;
       switch(eSubscriptionType)
       {
              case MC_SUBSCRIPTION_TYPE_SERVER_STATE:
                     nRet = mc_client_set_server_updated_cb(g_hMcClient, ClientServerStateUpdatedCallBack, NULL);
                     PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_server_updated_cb", MediaControllerGetError(nRet));
                     break;
              case MC_SUBSCRIPTION_TYPE_PLAYBACK:
                     nRet = mc_client_set_playback_updated_cb(g_hMcClient, ClientPlayBackUpdatedCallBack, NULL);
                     PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_playback_updated_cb", MediaControllerGetError(nRet));
                     break;
              case MC_SUBSCRIPTION_TYPE_METADATA:
                     nRet = mc_client_set_metadata_updated_cb(g_hMcClient, ClientMetadataUpdatedCallBack, NULL);
                     PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_metadata_updated_cb", MediaControllerGetError(nRet));
                     break;
              case MC_SUBSCRIPTION_TYPE_SHUFFLE_MODE:
                     nRet = mc_client_set_shuffle_mode_updated_cb(g_hMcClient, ClientShuffleModeUpdatedCallBack, NULL);
                     PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_shuffle_mode_updated_cb", MediaControllerGetError(nRet));
                     break;
              case MC_SUBSCRIPTION_TYPE_REPEAT_MODE:
                     nRet = mc_client_set_repeat_mode_updated_cb(g_hMcClient, ClientRepeatModeUpdatedCallBack, NULL);
                     PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_repeat_mode_updated_cb", MediaControllerGetError(nRet));
                     break;
       }
       return 0;
}

/**
* @function               UnSetUpdateCallBacks
* @description               UnRegister Update Callbacks
* @parameter              mc_subscription_type_e eSubscriptionType
* @return                      NA
*/
bool UnSetUpdateCallBacks(mc_subscription_type_e eSubscriptionType)
{
       int nRet = -1;
       switch(eSubscriptionType)
       {
              case MC_SUBSCRIPTION_TYPE_SERVER_STATE:
                     nRet = mc_client_unset_server_updated_cb(g_hMcClient);
                     PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_server_updated_cb", MediaControllerGetError(nRet));
                     break;
              case MC_SUBSCRIPTION_TYPE_PLAYBACK:
                     nRet = mc_client_unset_playback_updated_cb(g_hMcClient);
                     PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_playback_updated_cb", MediaControllerGetError(nRet));
                     break;
              case MC_SUBSCRIPTION_TYPE_METADATA:
                     nRet = mc_client_unset_metadata_updated_cb(g_hMcClient);
                     PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_metadata_updated_cb", MediaControllerGetError(nRet));
                     break;
              case MC_SUBSCRIPTION_TYPE_SHUFFLE_MODE:
                     nRet = mc_client_unset_shuffle_mode_updated_cb(g_hMcClient);
                     PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_shuffle_mode_updated_cb", MediaControllerGetError(nRet));
                     break;
              case MC_SUBSCRIPTION_TYPE_REPEAT_MODE:
                     nRet = mc_client_unset_repeat_mode_updated_cb(g_hMcClient);
                     PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_repeat_mode_updated_cb", MediaControllerGetError(nRet));
                     break;
       }
       return 0;
}

/**
 * @function 		ServerEnableCmdReceivedCallBack
 * @description	 	Callback Function
 * @parameter		const char *pszClientName, const char *pszReqID, bool bIsEnabled, void *pszData
 * @return 		NA
 */
void ServerEnableCmdReceivedCallBack(const char *pszClientName, const char *pszReqID, bool bIsEnabled, void *pszData)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] ServerEnableCmdReceivedCallBack Callback Invoked\\n", __LINE__, API_NAMESPACE);
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
	return;
}
/**
* @function		ClientGetDisplayModeAbility
* @description		Check, if supported mode is same as set.
* @parameter		bitwise ORed mc_display_mode_e SupportedModes
* @return		0/1 mode matched or not
*/
int ClientGetDisplayModeAbility(unsigned int SupportedModes)
{
	int nRet = 0;
	if (!(SupportedModes & MC_DISPLAY_MODE_LETTER_BOX)) {
		FPRINTF("[%d:%s] wrong supported mode [%d] expected is [%d]\\n", __LINE__, __FUNCTION__, SupportedModes, MC_DISPLAY_MODE_LETTER_BOX);
		nRet = 1;
	}

	if (!(SupportedModes & MC_DISPLAY_MODE_ORIGIN_SIZE)) {
		FPRINTF("[%d:%s] wrong supported mode [%d] expected is [%d]\\n", __LINE__, __FUNCTION__, SupportedModes, MC_DISPLAY_MODE_ORIGIN_SIZE);
		nRet = 1;
	}

	if (!(SupportedModes & MC_DISPLAY_MODE_FULL_SCREEN)) {
		FPRINTF("[%d:%s] wrong supported mode [%d] expected is [%d]\\n", __LINE__, __FUNCTION__, SupportedModes, MC_DISPLAY_MODE_FULL_SCREEN);
		nRet = 1;
	}

	if (!(SupportedModes & MC_DISPLAY_MODE_CROPPED_FULL)) {
		FPRINTF("[%d:%s] wrong supported mode [%d] expected is [%d]\\n", __LINE__, __FUNCTION__, SupportedModes, MC_DISPLAY_MODE_CROPPED_FULL);
		nRet = 1;
	}
	return nRet;

}

/**
* @function		ClientGetDisplayRotationAbility
* @description		Check, if supported rotation is same as set.
* @parameter		bitwise ORed mc_display_rotation_e SupportedRotations
* @return		0/1 mode matched or not
*/
int ClientGetDisplayRotationAbility(unsigned int SupportedRotations)
{
	int nRet = 0;
	if (!(SupportedRotations & MC_DISPLAY_ROTATION_NONE)) {
		FPRINTF("[%d:%s] wrong supported rotation [%d] expected is [%d]\\n", __LINE__, __FUNCTION__, SupportedRotations, MC_DISPLAY_ROTATION_NONE);
		nRet = 1;
	}

	if (!(SupportedRotations & MC_DISPLAY_ROTATION_90)) {
		FPRINTF("[%d:%s] wrong supported rotation [%d] expected is [%d]\\n", __LINE__, __FUNCTION__, SupportedRotations, MC_DISPLAY_ROTATION_90);
		nRet = 1;
	}

	if (!(SupportedRotations & MC_DISPLAY_ROTATION_180)) {
		FPRINTF("[%d:%s] wrong supported rotation [%d] expected is [%d]\\n", __LINE__, __FUNCTION__, SupportedRotations, MC_DISPLAY_ROTATION_180);
		nRet = 1;
	}

	if (!(SupportedRotations & MC_DISPLAY_ROTATION_270)) {
		FPRINTF("[%d:%s] wrong supported rotation [%d] expected is [%d]\\n", __LINE__, __FUNCTION__, SupportedRotations, MC_DISPLAY_ROTATION_270);
		nRet = 1;
	}
	return nRet;
}

/** @} */
