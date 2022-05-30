//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
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
#include "ITs-media-controller-common.h"

static char *g_TestAppname = "org.tizen.media-controller-native-itc";
static char *g_PlaylistName = "test_playlist";
static char *g_McServerName = NULL;
static mc_server_state_e g_McServerState = MC_SERVER_STATE_NONE;
static char *g_McPlaylistName = "test_playlist";

//& set: MediaController

/** @addtogroup itc-media-controller-client
*  @ingroup itc
*  @{
*/

/****************************************************Enum Definition Start****************************************************/

mc_subscription_type_e g_eMcSubscriptionType[] = {MC_SUBSCRIPTION_TYPE_SERVER_STATE,
							MC_SUBSCRIPTION_TYPE_PLAYBACK,
							MC_SUBSCRIPTION_TYPE_METADATA,
							MC_SUBSCRIPTION_TYPE_SHUFFLE_MODE,
							MC_SUBSCRIPTION_TYPE_REPEAT_MODE,
							MC_SUBSCRIPTION_TYPE_PLAYLIST};

mc_playback_action_e g_ePlaybackActionArray[] = { MC_PLAYBACK_ACTION_PLAY,
							MC_PLAYBACK_ACTION_PAUSE,
							MC_PLAYBACK_ACTION_STOP,
							MC_PLAYBACK_ACTION_NEXT,
							MC_PLAYBACK_ACTION_PREV,
							MC_PLAYBACK_ACTION_FAST_FORWARD,
							MC_PLAYBACK_ACTION_REWIND,
							MC_PLAYBACK_ACTION_TOGGLE_PLAY_PAUSE};

mc_content_type_e g_eContentTypeArray[] = {MC_CONTENT_TYPE_IMAGE,
						MC_CONTENT_TYPE_VIDEO,
						MC_CONTENT_TYPE_MUSIC,
						MC_CONTENT_TYPE_OTHER};

mc_search_category_e g_eSearchCategoryArray[] = {MC_SEARCH_TITLE,
							MC_SEARCH_ARTIST,
							MC_SEARCH_ALBUM,
							MC_SEARCH_GENRE,
							MC_SEARCH_TPO};

mc_ability_e g_eAbilitySupportAllArray[] = {MC_ABILITY_SHUFFLE,    /**< Shuffle */
						  MC_ABILITY_REPEAT,    /**< Repeat */
						  MC_ABILITY_PLAYBACK_POSITION, /**< Playback Position */
						  MC_ABILITY_PLAYLIST,   /**< Playlist */
						  MC_ABILITY_CLIENT_CUSTOM,  /**< Custom command from a client */
						  MC_ABILITY_SEARCH,    /**< Search */ };

mc_display_mode_e g_controller_eDisplayModeArray[] =
{
	MC_DISPLAY_MODE_LETTER_BOX,	/**< Letter box */
	MC_DISPLAY_MODE_ORIGIN_SIZE,	/**< Origin size */
	MC_DISPLAY_MODE_FULL_SCREEN,	/**< Full-screen */
	MC_DISPLAY_MODE_CROPPED_FULL	/**< Cropped full-screen */
};

mc_display_rotation_e g_controller_eDisplayRotationArray[] =
{
	MC_DISPLAY_ROTATION_NONE,		/**< Display is not rotated */
	MC_DISPLAY_ROTATION_90,		/**< Display is rotated 90 degrees */
	MC_DISPLAY_ROTATION_180,	/**< Display is rotated 180 degrees */
	MC_DISPLAY_ROTATION_270		/**< Display is rotated 270 degrees */
};

/*****************************************************Enum Definition End*****************************************************/
static char* g_PlaylistArray[]={
	"title_1",
	"artist_1",
	"album_1",
	"author_1",
	"genre_1",
	"duration_1",
	"date_1",
	"copyright_1",
	"destription_1",
	"track_num_1",
	"picture_1"
};

static char* g_TestKeywords[]={
	"test_title",
	"test_artist",
	"test_album",
	"test_genre",
	"test_tpo",
};

/****************************************************Callback Start****************************************************/

/**
 * @function 		ServerPlayBackActionCallBack
 * @description	 	Callback Function
 * @parameter		const char* client_name, const char *request_id, mc_playback_action_e action, void *user_data
 * @return 			NA
 */
void ServerPlayBackActionCallBack(const char* client_name, const char *request_id, mc_playback_action_e action, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ServerPlayBackActionCallBack");
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
}

/**
 * @function 		ClientServerStateUpdatedCallBack
 * @description	 	Callback Function
 * @parameter		const char *server_name, mc_server_state_e state, void *user_data
 * @return 			NA
 */
void ClientServerStateUpdatedCallBack(const char *server_name, mc_server_state_e state, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ClientServerStateUpdatedCallBack");
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
}

/**
 * @function 		ClientPlayBackUpdatedCallBack
 * @description	 	Callback Function
 * @parameter		const char *server_name, mc_playback_h playback, void *user_data
 * @return 			NA
 */
void ClientPlayBackUpdatedCallBack(const char *server_name, mc_playback_h playback, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ClientPlayBackUpdatedCallBack");
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
 * @function 		ClientMetadataUpdatedCallBack
 * @description	 	Callback Function
 * @parameter		const char *server_name, mc_metadata_h metadata, void *user_data
 * @return 			NA
 */
void ClientMetadataUpdatedCallBack(const char *server_name, mc_metadata_h metadata, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ClientMetadataUpdatedCallBack");
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
}

/**
 * @function 		ClientShuffleModeUpdatedCallBack
 * @description	 	Callback Function
 * @parameter		const char *server_name, mc_shuffle_mode_e mode, void *user_data
 * @return 			NA
 */
void ClientShuffleModeUpdatedCallBack(const char *server_name, mc_shuffle_mode_e mode, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ClientShuffleModeUpdatedCallBack");
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
}

/**
 * @function 		ClientRepeatModeUpdatedCallBack
 * @description	 	Callback Function
 * @parameter		const char *server_name, mc_repeat_mode_e mode, void *user_data
 * @return 			NA
 */
void ClientRepeatModeUpdatedCallBack(const char *server_name, mc_repeat_mode_e mode, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ClientRepeatModeUpdatedCallBack");
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
}

/**
 * @function 		ClientForeachServerCallBack
 * @description	 	Callback Function
 * @parameter		const char *server_name, void *user_data
 * @return 			true/false
 */
bool ClientForeachServerCallBack(const char *server_name, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ClientForeachServerCallBack");
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
}

/**
 * @function 		ForeachServerSubscribedCallBack
 * @description	 	Callback Function
 * @parameter		const char *server_name, void *user_data
 * @return 			true/false
 */
bool ForeachServerSubscribedCallBack(const char *server_name, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ForeachServerSubscribedCallBack");
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
}

/**
 * @function 		ClientCustomComandReplyCallBack
 * @description	 	Callback Function
 * @parameter		const char *server_name, const char *request_id, int result_code, bundle *data, void *user_data
 * @return 			NA
 */
void ClientCustomComandReplyCallBack(const char *server_name, const char *request_id, int result_code, bundle *data, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ClientCustomComandReplyCallBack");
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
}

/**
 * @function 				ClientMcPlaylistUpdatedCallBack
 * @description 			Callback Function
 * @parameter 			const char *server_name, mc_playback_h playback, int result_code, void *user_data
 * @return				NA
 */
void ClientMcPlaylistUpdatedCallBack(const char *pszServerName, mc_playlist_update_mode_e mode, const char *pszPlaylistName, mc_playlist_h hPlaylist, void *pUserData)
{
	FPRINTF("%d:%s  invoked\n", __LINE__, __FUNCTION__);

	if(strncmp(pszServerName, g_TestAppname,strlen(g_TestAppname))) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\n", __LINE__, __FUNCTION__, pszServerName, g_TestAppname);
		QuitGmainLoop();
		return;
	}

	if(strncmp(pszPlaylistName, g_McPlaylistName, strlen(g_PlaylistName))) {
		FPRINTF("[%d:%s] wrong playlist name [%s][%s]\n", __LINE__, __FUNCTION__, pszPlaylistName, g_PlaylistName);
		QuitGmainLoop();
		return;
	}

	if ((mode != MC_PLAYLIST_UPDATED) && (mode != MC_PLAYLIST_REMOVED)) {
		FPRINTF("[%d:%s] wrong mode [%d]\n", __LINE__, __FUNCTION__, mode);
	}

	g_CallBackHit = true;
	QuitGmainLoop();

	return;
}

/**
 * @function            ClientMcRegisterPlaylist
 * @description         Register function ,create and update playlist
 * @parameter           mc_playlist_h *playlist
 * @return                      MEDIA_CONTROLLER_ERROR_NONE=0 for success and 1 for failure
 */
int ClientMcRegisterPlaylist(mc_playlist_h *hPlaylistReg)
{
	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h hPlaylist = NULL;

	nRet = mc_server_create_playlist(g_hMcServer, g_PlaylistName, &hPlaylist);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_create_playlist", MediaControllerGetError(nRet));
	CHECK_HANDLE(hPlaylist, "mc_server_create_playlist");

	int sSize = sizeof(g_PlaylistArray)/sizeof(g_PlaylistArray[0]);
	int StringIndex = 0;
	for(StringIndex = 0; StringIndex < sSize; StringIndex++)
	{
		FPRINTF("[%d:%s] Adding item to playlist index=%d, [%s]\n", __LINE__, __FUNCTION__, StringIndex, g_PlaylistArray[StringIndex]);
		nRet = mc_server_add_item_to_playlist(g_hMcServer, hPlaylist, "1", MC_META_MEDIA_TITLE, g_PlaylistArray[StringIndex]);
		PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_add_item_to_playlist", MediaControllerGetError(nRet),mc_playlist_destroy(hPlaylist));
	}

	nRet = mc_server_update_playlist_done(g_hMcServer, hPlaylist);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_playlist_done", MediaControllerGetError(nRet),mc_playlist_destroy(hPlaylist));
	*hPlaylistReg = hPlaylist;

	return MEDIA_CONTROLLER_ERROR_NONE;
}

/**
 * @function 		ClientPlaybackAbilityUpdatedCallBack
 * @description	 	Callback Function
 * @parameter		const char *server_name, mc_playback_ability_h ability, void *user_data
 * @return 			NA
 */
void ClientPlaybackAbilityUpdatedCallBack(const char *server_name, mc_playback_ability_h ability, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ClientPlaybackAbilityUpdatedCallBack");
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
}

/**
 * @function 		McSearchConditionCallBack
 * @description	 	Callback Function
 * @parameter		mc_content_type_e content_type, mc_search_category_e category, const char *search_keyword, bundle *data, void *user_data
 * @return 			NA
 */
bool McSearchConditionCallBack(mc_content_type_e content_type, mc_search_category_e category, const char *search_keyword, bundle *data, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "McSearchConditionCallBack");
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
	return false;
}

/**
 * @function 		McServerSearchCmdReceivedCallBack
 * @description	 	Callback Function
 * @parameter		const char *client_name, const char *request_id, mc_search_h search, void *user_data
 * @return 			NA
 */
void McServerSearchCmdReceivedCallBack(const char *client_name, const char *request_id, mc_search_h search, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "McServerSearchCmdReceivedCallBack");
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
}

/*
 * @function 		ServerCustomCmdReceivedCallback
 * @description	 	Callback Function
 * @parameter		const char client_name, const char *request_id, const char *command, bundle *data, void *user_data
 * @return 			NA
 */
void ServerCustomCmdReceivedCallback(const char * client_name, const char *request_id, const char *command, bundle *data, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ServerCustomCmdReceivedCallback");
#endif
	if(client_name)
	{
		strncpy(g_szClientName, client_name, strlen(client_name)+1);
	}
	g_CallBackHit = true;
	QuitGmainLoop();
}

/**
 * @function 		ClientAbilitySupportUpdatedCallBack
 * @description	 	Callback Function
 * @parameter		const char *server_name, mc_ability_e ability, mc_playback_ability_h ability, void *user_data
 * @return 			NA
 */
void ClientAbilitySupportUpdatedCallBack(const char *server_name, mc_ability_e ability, mc_ability_support_e support, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ClientAbilitySupportUpdatedCallBack");
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
 * @function 		ClientAbilitySupportedItemsUpdatedCallBack
 * @description	 	Callback Function
 * @parameter		const char *pszServerName, unsigned int nSupportedItems, void *pszData
 * @return 		NA
 */
void ClientAbilitySupportedItemsUpdatedCallBack(const char *pszServerName, unsigned int nSupportedItems, void *pszData)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] ClientAbilitySupportedItemsUpdatedCallBack Callback Invoked\\n", __LINE__, API_NAMESPACE);
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
}

/**
 * @function 		ClientBoolAttributeUpdatedCallBack
 * @description	 	Callback Function
 * @parameter		const char *pszServerName, bool bIsEnabled, void *pszData
 * @return 		NA
 */
void ClientBoolAttributeUpdatedCallBack(const char *pszServerName, bool bIsEnabled, void *pszData)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] ClientBoolAttributeUpdatedCallBack Callback Invoked\\n", __LINE__, API_NAMESPACE);
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
}

/**
 * @function 		ClientDisplayModeUpdatedCallBack
 * @description	 	Callback Function
 * @parameter		const char *pszServerName, mc_display_mode_e eDisplayMode, void *pszData
 * @return 		NA
 */
void ClientDisplayModeUpdatedCallBack(const char *pszServerName, mc_display_mode_e eDisplayMode, void *pszData)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] ClientDisplayModeUpdatedCallBack Callback Invoked\\n", __LINE__, API_NAMESPACE);
#endif

	g_CallBackHit = true;

	if(strncmp(pszServerName, g_TestAppname, strlen(g_TestAppname))) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\n", __LINE__, __FUNCTION__, pszServerName, g_TestAppname);
		QuitGmainLoop();
		return;
	}

	if (eDisplayMode != g_controller_eDisplayModeArray[g_nModeIdx])
	{
		FPRINTF("[%d:%s] wrong display mode [%d] expected display mode is[%d]\\n", __LINE__, __FUNCTION__, eDisplayMode, g_controller_eDisplayModeArray[g_nModeIdx]);
	}

	QuitGmainLoop();
}

/**
 * @function 		ClientDisplayRotationUpdatedCallBack
 * @description	 	Callback Function
 * @parameter		const char *pszServerName, mc_display_rotation_e eDisplayRotation, void *pszData
 * @return 		NA
 */
void ClientDisplayRotationUpdatedCallBack(const char *pszServerName, mc_display_rotation_e eDisplayRotation, void *pszData)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] ClientDisplayRotationUpdatedCallBack Callback Invoked\\n", __LINE__, API_NAMESPACE);
#endif

	g_CallBackHit = true;

	if(strncmp(pszServerName, g_TestAppname, strlen(g_TestAppname))) {
		FPRINTF("[%d:%s] wrong server name [%s][%s]\n", __LINE__, __FUNCTION__, pszServerName, g_TestAppname);
		QuitGmainLoop();
		return;
	}

	if (eDisplayRotation != g_controller_eDisplayRotationArray[g_nRotationIdx])
	{
		FPRINTF("[%d:%s] wrong display rotation [%d] expected display rotation is [%d]\\n", __LINE__, __FUNCTION__, eDisplayRotation, g_controller_eDisplayRotationArray[g_nRotationIdx]);
	}
	QuitGmainLoop();
}

/**
 * @function 		ServerDisplayModeCmdReceivedCallBack
 * @description	 	Callback Function
 * @parameter		const char *pszClientName, const char *pszReqID, mc_display_mode_e eDisplayMode, void *pszData
 * @return 		NA
 */
void ServerDisplayModeCmdReceivedCallBack(const char *pszClientName, const char *pszReqID, mc_display_mode_e eDisplayMode, void *pszData)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] ServerDisplayModeCmdReceivedCallBack Callback Invoked\\n", __LINE__, API_NAMESPACE);
#endif

	g_CallBackHit = true;

	if (eDisplayMode != g_controller_eDisplayModeArray[g_nModeIdx]){
		FPRINTF("[%d:%s] wrong display mode [%d] expected display mode is [%d]\\n", __LINE__, __FUNCTION__, eDisplayMode, g_controller_eDisplayModeArray[g_nModeIdx]);
	}
	QuitGmainLoop();
}

/**
 * @function 		ServerDisplayRotationCmdReceivedCallBack
 * @description	 	Callback Function
 * @parameter		const char *pszClientName, const char *pszReqID, mc_display_mode_e eDisplayMode, void *pszData
 * @return 		NA
 */
void ServerDisplayRotationCmdReceivedCallBack(const char *pszClientName, const char *pszReqID, mc_display_rotation_e eDisplayRotation, void *pszData)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] ServerDisplayRotationCmdReceivedCallBack Callback Invoked\\n", __LINE__, API_NAMESPACE);
#endif

	g_CallBackHit = true;

	if (eDisplayRotation != MC_DISPLAY_ROTATION_270) {
		FPRINTF("[%d:%s] wrong display rotation [%d] expected display rotation is [%d]\\n", __LINE__, __FUNCTION__, eDisplayRotation, MC_DISPLAY_ROTATION_270);
	}
	QuitGmainLoop();
}

/*****************************************************Callback End*****************************************************/

/**
 * @function 		ITs_media_controller_client_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_controller_client_startup(void)
{
	int nRet = -1;
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	nRet = mc_server_create(&g_hMcServer);
	PRINT_RESULTNONE(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_create", MediaControllerGetError(nRet));
	CHECK_HANDLE_NONE(g_hMcServer, "mc_server_create");

	nRet = mc_client_create(&g_hMcClient);
	PRINT_RESULTNONE(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_create", MediaControllerGetError(nRet));
	CHECK_HANDLE_NONE(g_hMcClient, "mc_client_create");

	nRet = mc_search_create(&g_hMcSearch);
	PRINT_RESULTNONE(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_search_create", MediaControllerGetError(nRet));
	CHECK_HANDLE_NONE(g_hMcSearch, "mc_search_create");

	g_bMediaControllerCreation = true;

	return;
}

/**
 * @function 		ITs_media_controller_client_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_controller_client_cleanup(void)
{
	if(g_hMcClient != NULL)
		mc_client_destroy(g_hMcClient);
	if(g_hMcServer != NULL)
		mc_server_destroy(g_hMcServer);
	if(g_hMcSearch != NULL)
		mc_search_destroy(g_hMcSearch);

	return;
}

/** @addtogroup itc-media-controller-client-testcases
*  @brief 		Integration testcases for module media-controller-client
*  @ingroup 	itc-media-controller-client
*  @{
*/

/**
 * @testcase 				ITs_mc_client_create_destroy_p
 * @author            		SRID(bipin.k)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test mc_client_create and mc_client_destroy
 * @scenario				Call mc_client_create, mc_client_destroy
 * @apicovered				mc_client_create, mc_client_destroy
 * @passcase				If mc_client_create and mc_client_destroy returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_client_create and mc_client_destroy
int ITs_mc_client_create_destroy_p(void)
{
	START_TEST;

	int nRet = -1;

	nRet = mc_client_destroy(g_hMcClient);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_destroy", MediaControllerGetError(nRet));

	nRet = mc_client_create(&g_hMcClient);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_create", MediaControllerGetError(nRet));
	CHECK_HANDLE(g_hMcClient, "mc_client_create");

	nRet = mc_client_destroy(g_hMcClient);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_destroy", MediaControllerGetError(nRet));

	nRet = mc_client_create(&g_hMcClient);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_create", MediaControllerGetError(nRet));
	CHECK_HANDLE(g_hMcClient, "mc_client_create");

	return 0;
}

/**
 * @testcase 				ITs_mc_client_set_unset_server_update_cb_p
 * @author            		SRID(bipin.k)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			4.0
 * @description				To test mc_client_set_server_updated_cb and mc_client_unset_server_updated_cb
 * @scenario				Call mc_client_set_server_updated_cb, mc_client_unset_server_updated_cb
 * @apicovered				mc_client_set_server_updated_cb, mc_client_unset_server_updated_cb
 * @passcase				If mc_client_set_server_updated_cb and mc_client_unset_server_updated_cb returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test server state updated callback and check its functionality
int ITs_mc_client_set_unset_server_updated_cb_p(void)
{
    START_TEST;

	int nRet = -1;

	g_CallBackHit = false;
	nRet = mc_client_set_server_updated_cb(g_hMcClient, ClientServerStateUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_server_updated_cb", MediaControllerGetError(nRet));

	nRet = mc_server_destroy(g_hMcServer);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_destroy", MediaControllerGetError(nRet), mc_client_unset_server_updated_cb(g_hMcClient));

	nRet = mc_server_create(&g_hMcServer);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_create", MediaControllerGetError(nRet), mc_client_unset_server_updated_cb(g_hMcClient));
	CHECK_HANDLE_CLEANUP(g_hMcServer, "mc_server_create", mc_client_unset_server_updated_cb(g_hMcClient));

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "mc_client_set_server_updated_cb", "CallBack Not Invoked", mc_client_unset_server_updated_cb(g_hMcClient));

	nRet = mc_client_unset_server_updated_cb(g_hMcClient);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_server_updated_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITs_mc_client_set_unset_playback_update_cb_p
 * @author            		SRID(bipin.k)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			4.0
 * @description				To test mc_client_set_playback_updated_cb and mc_client_unset_playback_updated_cb
 * @scenario				Call mc_client_set_playback_updated_cb, mc_client_unset_playback_updated_cb
 * @apicovered				mc_client_set_playback_updated_cb, mc_client_unset_playback_updated_cb
 * @passcase				If mc_client_set_playback_updated_cb and mc_client_unset_playback_updated_cb returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_client_set_playback_updated_cb and mc_client_unset_playback_updated_cb
int ITs_mc_client_set_unset_playback_updated_cb_p(void)
{
    START_TEST;

	int nRet = -1;

	g_CallBackHit = false;
	nRet = mc_client_set_playback_updated_cb(g_hMcClient, ClientPlayBackUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_playback_updated_cb", MediaControllerGetError(nRet));

	nRet = SetServerPlayBackInfo();
	PRINT_RESULT_CLEANUP(0, nRet, "SetServerPlayBackInfo", "Return Value Not Correct", mc_client_unset_playback_updated_cb(g_hMcClient));

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "mc_client_set_playback_updated_cb", "CallBack Not Invoked", mc_client_unset_playback_updated_cb(g_hMcClient));

	nRet = mc_client_unset_playback_updated_cb(g_hMcClient);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_playback_updated_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITs_mc_client_set_unset_metadata_update_cb_p
 * @author            		SRID(bipin.k)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			4.0
 * @description				To test mc_client_set_metadata_updated_cb and mc_client_unset_metadata_updated_cb
 * @scenario				Call mc_client_set_metadata_updated_cb, mc_client_unset_metadata_updated_cb
 * @apicovered				mc_client_set_metadata_updated_cb, mc_client_unset_metadata_updated_cb
 * @passcase				If mc_client_set_metadata_updated_cb and mc_client_unset_metadata_updated_cb returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_client_set_metadata_updated_cb and mc_client_unset_metadata_updated_cb
int ITs_mc_client_set_unset_metadata_updated_cb_p(void)
{
    START_TEST;

	int nRet = -1;

	g_CallBackHit = false;
	nRet = mc_client_set_metadata_updated_cb(g_hMcClient, ClientMetadataUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_metadata_updated_cb", MediaControllerGetError(nRet));

	nRet = SetServerMetaData();
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "SetServerMetaData", "Return Value Not Correct", mc_client_unset_metadata_updated_cb(g_hMcClient));

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "mc_client_set_metadata_updated_cb", "CallBack Not Invoked", mc_client_unset_metadata_updated_cb(g_hMcClient));

	nRet = mc_client_unset_metadata_updated_cb(g_hMcClient);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_metadata_updated_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITs_mc_client_set_unset_shuffle_mode_update_cb_p
 * @author            		SRID(bipin.k)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			4.0
 * @description				To test mc_client_set_shuffle_mode_updated_cb and mc_client_unset_shuffle_mode_updated_cb
 * @scenario				Call mc_client_set_shuffle_mode_updated_cb, mc_client_unset_shuffle_mode_updated_cb
 * @apicovered				mc_client_set_shuffle_mode_updated_cb, mc_client_unset_shuffle_mode_updated_cb
 * @passcase				If mc_client_set_shuffle_mode_updated_cb and mc_client_unset_shuffle_mode_updated_cb returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_client_set_shuffle_mode_updated_cb and mc_client_unset_shuffle_mode_updated_cb
int ITs_mc_client_set_unset_shuffle_mode_updated_cb_p(void)
{
    START_TEST;

	int nRet = -1;

	g_CallBackHit = false;
	nRet = mc_client_set_shuffle_mode_updated_cb(g_hMcClient, ClientShuffleModeUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_shuffle_mode_updated_cb", MediaControllerGetError(nRet));

	nRet = UpdateServerModes();
	PRINT_RESULT_CLEANUP(0, nRet, "UpdateServerModes", "Return Value Not Correct", mc_client_unset_shuffle_mode_updated_cb(g_hMcClient));

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "mc_client_set_shuffle_mode_updated_cb", "CallBack Not Invoked", mc_client_unset_shuffle_mode_updated_cb(g_hMcClient));

	nRet = mc_client_unset_shuffle_mode_updated_cb(g_hMcClient);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_shuffle_mode_updated_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITs_mc_client_set_unset_repeat_mode_update_cb_p
 * @author            		SRID(bipin.k)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			4.0
 * @description				To test mc_client_set_repeat_mode_updated_cb and mc_client_unset_repeat_mode_updated_cb
 * @scenario				Call mc_client_set_repeat_mode_updated_cb, mc_client_unset_repeat_mode_updated_cb
 * @apicovered				mc_client_set_repeat_mode_updated_cb, mc_client_unset_repeat_mode_updated_cb
 * @passcase				If mc_client_set_repeat_mode_updated_cb and mc_client_unset_repeat_mode_updated_cb returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_client_set_repeat_mode_updated_cb and mc_client_unset_repeat_mode_updated_cb
int ITs_mc_client_set_unset_repeat_mode_updated_cb_p(void)
{
    START_TEST;

	int nRet = -1;

	g_CallBackHit = false;
	nRet = mc_client_set_repeat_mode_updated_cb(g_hMcClient, ClientRepeatModeUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_repeat_mode_updated_cb", MediaControllerGetError(nRet));

	nRet = UpdateServerModes();
	PRINT_RESULT_CLEANUP(0, nRet, "UpdateServerModes", "Return Value Not Correct", mc_client_unset_repeat_mode_updated_cb(g_hMcClient));

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "mc_client_set_repeat_mode_updated_cb", "CallBack Not Invoked", mc_client_unset_repeat_mode_updated_cb(g_hMcClient));

	nRet = mc_client_unset_repeat_mode_updated_cb(g_hMcClient);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_repeat_mode_updated_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mc_client_get_latest_server_info_p
 * @author            		SRID(bipin.k)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test mc_client_get_latest_server_info
 * @scenario				Call mc_client_get_latest_server_info
 * @apicovered				mc_client_get_latest_server_info
 * @passcase				If mc_client_get_latest_server_info returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_client_get_latest_server_info
int ITc_mc_client_get_latest_server_info_p(void)
{
    START_TEST;

	int nRet = -1;
	char *pszServerName = NULL;
	mc_server_state_e eServerState = 0;

	nRet = mc_client_get_latest_server_info(g_hMcClient, &pszServerName, &eServerState);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet));
	CHECK_HANDLE(pszServerName, "mc_client_get_latest_server_info");
	if(eServerState < MC_SERVER_STATE_NONE || eServerState > MC_SERVER_STATE_DEACTIVATE)
	{
		FPRINTF("[Line : %d][%s] %s Enum returned is out of range =%d \\n", __LINE__, API_NAMESPACE, "eServerState",eServerState);
		FREE_MEMORY(pszServerName);
		return 1;
	}
	FREE_MEMORY(pszServerName);

    return 0;
}

/**
 * @testcase 				ITc_mc_client_get_destroy_server_playback_info_p
 * @author            		SRID(bipin.k)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test mc_client_get_server_playback_info and mc_client_destroy_playback
 * @scenario				Call mc_client_get_server_playback_info, mc_client_destroy_playback
 * @apicovered				mc_client_get_server_playback_info, mc_client_destroy_playback
 * @passcase				If mc_client_get_server_playback_info and mc_client_destroy_playback returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_client_get_server_playback_info and mc_client_destroy_playback
int ITc_mc_client_get_destroy_server_playback_info_p(void)
{
    START_TEST;

	int nRet = -1;
	mc_playback_h hPlayBack = NULL;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(0, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = mc_client_get_server_playback_info(g_hMcClient, g_szServerName, &hPlayBack);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_playback_info", MediaControllerGetError(nRet));
	CHECK_HANDLE(hPlayBack, "mc_client_get_server_playback_info");

	nRet = mc_client_destroy_playback(hPlayBack);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_destroy_playback", MediaControllerGetError(nRet));

    return 0;
}

/**
 * @testcase 				ITc_mc_client_get_destroy_server_metadata_p
 * @author            		SRID(bipin.k)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			4.0
 * @description				To test mc_client_get_server_metadata and mc_metadata_destroy
 * @scenario				Call mc_client_get_server_metadata, mc_metadata_destroy
 * @apicovered				mc_client_get_server_metadata, mc_metadata_destroy
 * @passcase				If mc_client_get_server_metadata and mc_metadata_destroy returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_client_get_server_metadata and mc_metadata_destroy
int ITc_mc_client_get_destroy_server_metadata_p(void)
{
    START_TEST;

	int nRet = -1;
	mc_metadata_h hMetaData = NULL;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(0, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = mc_client_get_server_metadata(g_hMcClient, g_szServerName, &hMetaData);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_metadata", MediaControllerGetError(nRet));
	CHECK_HANDLE(hMetaData, "mc_client_get_server_metadata");
	nRet = mc_metadata_destroy(hMetaData);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_metadata_destroy", MediaControllerGetError(nRet));
    return 0;
}

/**
 * @testcase 				ITc_mc_client_get_server_shuffle_mode_p
 * @author            		SRID(bipin.k)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test mc_client_get_server_shuffle_mode
 * @scenario				Call mc_client_get_server_shuffle_mode
 * @apicovered				mc_client_get_server_shuffle_mode
 * @passcase				If mc_client_get_server_shuffle_mode returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_client_get_server_shuffle_mode
int ITc_mc_client_get_server_shuffle_mode_p(void)
{
    START_TEST;

	int nRet = -1;
	mc_shuffle_mode_e eShuffleMode = MC_SHUFFLE_MODE_OFF;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(0, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = mc_client_get_server_shuffle_mode(g_hMcClient, g_szServerName, &eShuffleMode);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_shuffle_mode", MediaControllerGetError(nRet));
	PRINT_RESULT(MC_SHUFFLE_MODE_ON, eShuffleMode, "mc_client_get_server_shuffle_mode", "Shuffle Value Mismatch");

    return 0;
}

/**
 * @testcase 				ITc_mc_client_get_server_repeat_mode_p
 * @author            		SRID(bipin.k)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test mc_client_get_server_repeat_mode
 * @scenario				Call mc_client_get_server_repeat_mode
 * @apicovered				mc_client_get_server_repeat_mode
 * @passcase				If mc_client_get_server_repeat_mode returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_client_get_server_repeat_mode
int ITc_mc_client_get_server_repeat_mode_p(void)
{
    START_TEST;

	int nRet = -1;
	mc_repeat_mode_e eRepeatMode = MC_REPEAT_MODE_OFF;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(0, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = mc_client_get_server_repeat_mode(g_hMcClient, g_szServerName, &eRepeatMode);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_repeat_mode", MediaControllerGetError(nRet));
	PRINT_RESULT(MC_REPEAT_MODE_ON, eRepeatMode, "mc_client_get_server_repeat_mode", "Repeat Value Mismatch");

    return 0;
}

/**
 * @testcase 				ITc_mc_client_get_playback_state_p
 * @author            		SRID(bipin.k)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test mc_client_get_playback_state
 * @scenario				Call mc_client_get_playback_state
 * @apicovered				mc_client_get_playback_state
 * @passcase				If mc_client_get_playback_state returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_client_get_playback_state
int ITc_mc_client_get_playback_state_p(void)
{
    START_TEST;

	int nRet = -1;
	mc_playback_h hPlayBack = NULL;
	mc_playback_states_e eState = MC_PLAYBACK_STATE_STOPPED;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(0, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = mc_client_get_server_playback_info(g_hMcClient, g_szServerName, &hPlayBack);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_playback_info", MediaControllerGetError(nRet));
	CHECK_HANDLE(hPlayBack, "mc_client_get_server_playback_info");

	nRet = mc_client_get_playback_state(hPlayBack, &eState);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_playback_state", MediaControllerGetError(nRet), mc_client_destroy_playback(hPlayBack));
	PRINT_RESULT_CLEANUP(MC_PLAYBACK_STATE_PLAYING, eState, "mc_client_get_playback_state", "PlayBack State Mismatch", mc_client_destroy_playback(hPlayBack));

	nRet = mc_client_destroy_playback(hPlayBack);
	PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_destroy_playback", MediaControllerGetError(nRet));

    return 0;
}

/**
 * @testcase 				ITc_mc_client_get_playback_position_p
 * @author            		SRID(bipin.k)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test mc_client_get_playback_position
 * @scenario				Call mc_client_get_playback_position
 * @apicovered				mc_client_get_playback_position
 * @passcase				If mc_client_get_playback_position returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_client_get_playback_position
int ITc_mc_client_get_playback_position_p(void)
{
    START_TEST;

	int nRet = -1;
	mc_playback_h hPlayBack = NULL;
	unsigned long long ullPosition = 0;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = mc_client_get_server_playback_info(g_hMcClient, g_szServerName, &hPlayBack);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_playback_info", MediaControllerGetError(nRet));
	CHECK_HANDLE(hPlayBack, "mc_client_get_server_playback_info");

	nRet = mc_client_get_playback_position(hPlayBack, &ullPosition);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_playback_position", MediaControllerGetError(nRet), mc_client_destroy_playback(hPlayBack));
	PRINT_RESULT_CLEANUP(PLAYBACKPOSITION, (int)ullPosition, "mc_client_get_playback_position", "PlayBack Position Mismatch", mc_client_destroy_playback(hPlayBack));

	nRet = mc_client_destroy_playback(hPlayBack);
	PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_destroy_playback", MediaControllerGetError(nRet));

    return 0;
}

/**
 * @testcase 				ITs_mc_client_foreach_server_p
 * @author            		SRID(bipin.k)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test mc_client_foreach_server
 * @scenario				Call mc_client_foreach_server
 * @apicovered				mc_client_foreach_server
 * @passcase				If mc_client_foreach_server returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_client_foreach_server
int ITs_mc_client_foreach_server_p(void)
{
    START_TEST;
	int nRet = -1;

	g_CallBackHit = false;
	nRet = mc_client_foreach_server(g_hMcClient, ClientForeachServerCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_foreach_server", MediaControllerGetError(nRet));

	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "mc_client_foreach_server", "CallBack Not Invoked");

	return 0;
}

/**
 * @testcase 				ITs_mc_client_send_playback_action_cmd_p
 * @author            		SRID(priya.kohli)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			4.0
 * @description				To test mc_server_set_playback_action_cmd_received_cb and mc_client_send_playback_action_cmd and mc_server_unset_playback_action_cmd_received_cb
 * @scenario				Call mc_server_set_playback_action_cmd_received_cb, mc_client_send_playback_action_cmd and mc_server_unset_playback_action_cmd_received_cb
 * @apicovered				mc_server_set_playback_action_cmd_received_cb, mc_client_send_playback_action_cmd and mc_server_unset_playback_action_cmd_received_cb
 * @passcase				If mc_server_set_playback_action_cmd_received_cb, mc_client_send_playback_action_cmd and mc_server_unset_playback_action_cmd_received_cb returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_server_set_playback_action_cmd_received_cb and mc_client_send_playback_action_cmd and mc_server_unset_playback_action_cmd_received_cb
int ITs_mc_client_send_playback_action_cmd_p(void)
{
    START_TEST;

	int nRet = -1;
	mc_playback_action_e ePlaybackAction;
	int nSize = sizeof(g_ePlaybackActionArray)/sizeof(g_ePlaybackActionArray[0]);
	bundle *bundle_data = NULL;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct", mc_server_unset_playback_action_cmd_received_cb(g_hMcServer));

	for ( int nCounter = 0; nCounter < nSize; nCounter++ )
	{
		g_CallBackHit = false;
		ePlaybackAction = g_ePlaybackActionArray[nCounter];

		nRet = mc_server_set_playback_action_cmd_received_cb(g_hMcServer, ServerPlayBackActionCallBack, bundle_data);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_playback_action_cmd_received_cb", MediaControllerGetError(nRet));

		nRet = mc_client_send_playback_action_cmd(g_hMcClient, g_szServerName, ePlaybackAction, &g_request_id);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_playback_action_cmd", MediaControllerGetError(nRet));

		IterateGmainLoop();
		PRINT_RESULT_CLEANUP(true, g_CallBackHit, "ServerPlayBackActionCallBack", "CallBack Not Invoked", mc_server_unset_playback_action_cmd_received_cb(g_hMcServer));

		nRet = mc_server_unset_playback_action_cmd_received_cb(g_hMcServer);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_unset_playback_action_cmd_received_cb", MediaControllerGetError(nRet));
	}

	return 0;
}

/**
 * @testcase 				ITc_mc_client_subscribe_unsubscribe_p
 * @author            		SRID(bipin.k)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test mc_client_subscribe, mc_client_unsubscribe
 * @scenario				Call mc_client_subscribe and mc_client_unsubscribe
 * @apicovered				mc_client_subscribe, mc_client_unsubscribe
 * @passcase				If mc_client_subscribe and mc_client_unsubscribe returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_client_subscribe and mc_client_unsubscribe
int ITc_mc_client_subscribe_unsubscribe_p(void)
{
    START_TEST;
	int nRet = -1;
	int nEnumCounter = 0;
	int nEnumSize = sizeof(g_eMcSubscriptionType) / sizeof(g_eMcSubscriptionType[0]);

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(0, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	for (nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++)
	{
		nRet = SetUpdateCallBacks(g_eMcSubscriptionType[nEnumCounter]);
		PRINT_RESULT(0, nRet, "SetUpdateCallBacks", "Return Value Not Correct");

		if(g_eMcSubscriptionType[nEnumCounter] == MC_SUBSCRIPTION_TYPE_PLAYLIST)
		{
			nRet = mc_client_set_playlist_updated_cb(g_hMcClient, ClientMcPlaylistUpdatedCallBack, NULL);
			PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_playlist_updated_cb", MediaControllerGetError(nRet));
		}

		nRet = mc_client_subscribe(g_hMcClient, g_eMcSubscriptionType[nEnumCounter], g_szServerName);
		PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_subscribe", MediaControllerGetError(nRet), UnSetUpdateCallBacks(g_eMcSubscriptionType[nEnumCounter]));

		nRet = mc_client_unsubscribe(g_hMcClient, g_eMcSubscriptionType[nEnumCounter], g_szServerName);
		PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unsubscribe", MediaControllerGetError(nRet), UnSetUpdateCallBacks(g_eMcSubscriptionType[nEnumCounter]));

		nRet = UnSetUpdateCallBacks(g_eMcSubscriptionType[nEnumCounter]);
		PRINT_RESULT(0, nRet, "UnSetUpdateCallBacks", "Return Value Not Correct");

		if(g_eMcSubscriptionType[nEnumCounter] == MC_SUBSCRIPTION_TYPE_PLAYLIST)
		{
			nRet = mc_client_unset_playlist_updated_cb(g_hMcClient);
			PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_playlist_updated_cb", MediaControllerGetError(nRet));
		}
	}
	return 0;
}

/**
 * @testcase 				ITc_mc_client_foreach_server_subscribed_p
 * @author            		SRID(bipin.k)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To mc_client_foreach_server_subscribed
 * @scenario				Call mc_client_foreach_server_subscribed
 * @apicovered				mc_client_foreach_server_subscribed
 * @passcase				If mc_client_foreach_server_subscribed returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_client_foreach_server_subscribed
int ITc_mc_client_foreach_server_subscribed_p(void)
{
    START_TEST;
	int nRet = -1;
	int nEnumCounter = 0;
	int nEnumSize = sizeof(g_eMcSubscriptionType) / sizeof(g_eMcSubscriptionType[0]);

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(0, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	for (nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		nRet = SetUpdateCallBacks(g_eMcSubscriptionType[nEnumCounter]);
		PRINT_RESULT(0, nRet, "SetUpdateCallBacks", "Return Value Not Correct");

		if(g_eMcSubscriptionType[nEnumCounter] == MC_SUBSCRIPTION_TYPE_PLAYLIST)
		{
		nRet = mc_client_set_playlist_updated_cb(g_hMcClient, ClientMcPlaylistUpdatedCallBack, NULL);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_playlist_updated_cb", MediaControllerGetError(nRet));
		}

		nRet = mc_client_subscribe(g_hMcClient, g_eMcSubscriptionType[nEnumCounter], g_szServerName);
		PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_subscribe", MediaControllerGetError(nRet), UnSetUpdateCallBacks(g_eMcSubscriptionType[nEnumCounter]));

		g_CallBackHit = false;
		nRet = mc_client_foreach_server_subscribed(g_hMcClient, g_eMcSubscriptionType[nEnumCounter], ForeachServerSubscribedCallBack, NULL);
		PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_foreach_server_subscribed", MediaControllerGetError(nRet), mc_client_unsubscribe(g_hMcClient, g_eMcSubscriptionType[nEnumCounter], g_szServerName); UnSetUpdateCallBacks(g_eMcSubscriptionType[nEnumCounter]));
		IterateGmainLoop();
		PRINT_RESULT_CLEANUP(true, g_CallBackHit, "mc_client_foreach_server_subscribed", "CallBack Not Invoked", mc_client_unsubscribe(g_hMcClient, g_eMcSubscriptionType[nEnumCounter], g_szServerName); UnSetUpdateCallBacks(g_eMcSubscriptionType[nEnumCounter]));

		nRet = mc_client_unsubscribe(g_hMcClient, g_eMcSubscriptionType[nEnumCounter], g_szServerName);
		PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unsubscribe", MediaControllerGetError(nRet), UnSetUpdateCallBacks(g_eMcSubscriptionType[nEnumCounter]));

		nRet = UnSetUpdateCallBacks(g_eMcSubscriptionType[nEnumCounter]);
		PRINT_RESULT(0, nRet, "UnSetUpdateCallBacks", "Return Value Not Correct");

		if(g_eMcSubscriptionType[nEnumCounter] == MC_SUBSCRIPTION_TYPE_PLAYLIST)
		{
			nRet = mc_client_unset_playlist_updated_cb(g_hMcClient);
			PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_playlist_updated_cb", MediaControllerGetError(nRet));
		}
	}

    return 0;
}

/**
 * @testcase 				ITc_mc_client_send_playback_position_cmd_p
 * @author            		SRID(priya.kohli)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			4.0
 * @description				To test mc_client_get_playback_position
 * @scenario				Call mc_client_get_playback_position
 * @apicovered				mc_client_send_playback_position_cmd
 * @passcase				If mc_client_send_playback_position_cmd returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			Create a media controller client handle by calling mc_client_create().
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_client_send_playback_position_cmd
int ITc_mc_client_send_playback_position_cmd_p(void)
{
	START_TEST;

	int nRet = -1;
	unsigned long long ullSetPosition = 15;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = mc_client_send_playback_position_cmd(g_hMcClient, g_szServerName, ullSetPosition, &g_request_id);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_playback_position_cmd", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mc_client_send_shuffle_mode_cmd_p
 * @author            		SRID(priya.kohli)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			4.0
 * @description				To test mc_client_get_playback_position
 * @scenario				Call mc_client_get_playback_position
 * @apicovered				mc_client_get_playback_position,mc_client_send_shuffle_mode_cmd
 * @passcase				If mc_client_send_shuffle_mode_cmd returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			Create a media controller client handle by calling mc_client_create().
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_client_send_shuffle_mode_cmd
int ITc_mc_client_send_shuffle_mode_cmd_p(void)
{
	START_TEST;

	int nRet = -1;
	mc_shuffle_mode_e eShuffleModeArray[] = { MC_SHUFFLE_MODE_ON,
											MC_SHUFFLE_MODE_OFF};
	mc_shuffle_mode_e eShuffleMode;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	int nSize = sizeof(eShuffleModeArray)/sizeof(eShuffleModeArray[0]);

	for(int nCounter = 0; nCounter < nSize; nCounter++)
	{
		eShuffleMode = eShuffleModeArray[nCounter];
		nRet = mc_client_send_shuffle_mode_cmd(g_hMcClient, g_szServerName, eShuffleMode, &g_request_id);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_shuffle_mode_cmd", MediaControllerGetError(nRet));
	}

	return 0;
}

/**
 * @testcase 				ITc_mc_client_send_repeat_mode_cmd_p
 * @author            		SRID(priya.kohli)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			4.0
 * @description				To test mc_client_get_playback_position
 * @scenario				Call mc_client_get_playback_position
 * @apicovered				mc_client_get_playback_position,mc_client_send_repeat_mode_cmd
 * @passcase				If mc_client_send_repeat_mode_cmd returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			Create a media controller client handle by calling mc_client_create().
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_client_send_repeat_mode_cmd
int ITc_mc_client_send_repeat_mode_cmd_p(void)
{
	START_TEST;

	int nRet = -1;
	mc_repeat_mode_e eRepeatModeArray[] = { MC_REPEAT_MODE_ON,
											MC_REPEAT_MODE_OFF,
											MC_REPEAT_MODE_ONE_MEDIA};
	mc_repeat_mode_e eRepeatMode;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	int nSize = sizeof(eRepeatModeArray)/sizeof(eRepeatModeArray[0]);

	for(int nCounter = 0; nCounter < nSize; nCounter++)
	{
		eRepeatMode = eRepeatModeArray[nCounter];
		nRet = mc_client_send_repeat_mode_cmd(g_hMcClient, g_szServerName, eRepeatMode, &g_request_id);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_repeat_mode_cmd", MediaControllerGetError(nRet));
	}

	return 0;
}

/**
 * @testcase 				ITc_mc_client_send_playlist_cmd_p
 * @author            		SRID(priya.kohli)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			4.0
 * @description				To test mc_client_send_playlist_cmd
 * @scenario				Call mc_client_send_playlist_cmd
 * @apicovered				mc_client_send_playlist_cmd
 * @passcase				If mc_client_send_playlist_cmd returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			Create a media controller client handle by calling mc_client_create().
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_client_send_playlist_cmd
int ITc_mc_client_send_playlist_cmd_p(void)
{
	START_TEST;

	int nRet = -1;
	const char *pszIndex="3";
	unsigned long long ullPosition = 0;
	mc_playback_action_e ePlaybackAction;
	int nSize = sizeof(g_ePlaybackActionArray)/sizeof(g_ePlaybackActionArray[0]);

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	for ( int nCounter = 0; nCounter < nSize; nCounter++ )
	{
		ePlaybackAction = g_ePlaybackActionArray[nCounter];

		nRet = mc_client_send_playlist_cmd(g_hMcClient, g_szServerName, g_szPlaylistName, pszIndex, ePlaybackAction, ullPosition, &g_request_id);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_playlist_cmd", MediaControllerGetError(nRet));
	}

	return 0;
}

/**
 * @testcase 				ITc_mc_client_send_custom_cmd_p
 * @author            		SRID(priya.kohli)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			4.0
 * @description				Sends the custom command to server.
 * @scenario				Call mc_client_send_custom_cmd
 * @apicovered				mc_client_send_custom_cmd
 * @passcase				If mc_client_send_custom_cmd returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: Sends the custom command to server.
int ITc_mc_client_send_custom_cmd_p(void)
{
	START_TEST;

	int nRet = -1;
	bundle *bundle_data = NULL;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = mc_client_send_custom_cmd(g_hMcClient, g_szServerName, TESTCOMMAND, bundle_data, &g_request_id);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_custom_cmd", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mc_client_set_unset_cmd_reply_received_cb_p
 * @author            		SRID(priya.kohli)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			4.0
 * @description				Sets the callback for receiving the result of the command from the media controller server.
 * @scenario				The media controller client which calls this function will receives the result of the command from all media controller servers.
 * @apicovered				mc_client_set_cmd_reply_received_cb, mc_client_send_custom_cmd, mc_client_unset_cmd_reply_received_cb, mc_server_set_custom_cmd_received_cb, mc_server_send_cmd_reply, mc_server_unset_custom_cmd_received_cb
 * @passcase				If mc_client_set_cmd_reply_received_cb, mc_client_send_custom_cmd, mc_client_unset_cmd_reply_received_cb returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To set the callback for receiving the result of the command from the media controller server.
int ITc_mc_client_set_unset_cmd_reply_received_cb_p(void)
{
	START_TEST;

	int nRet = -1;
	bundle *bundle_data = NULL;
	void *user_data = NULL;
	void *usr_data = NULL;
	int nCode = MC_RESULT_CODE_SUCCESS;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = mc_client_set_cmd_reply_received_cb(g_hMcClient, ClientCustomComandReplyCallBack, user_data);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "ClientCustomComandReplyCallBack", MediaControllerGetError(nRet));

	nRet = mc_server_set_custom_cmd_received_cb(g_hMcServer, ServerCustomCmdReceivedCallback, usr_data);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "ServerCustomCmdReceivedCallback", MediaControllerGetError(nRet), mc_client_unset_cmd_reply_received_cb(g_hMcClient));

	g_CallBackHit = false;
	nRet = mc_client_send_custom_cmd(g_hMcClient, g_szServerName, TESTCOMMAND, bundle_data, &g_request_id);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_custom_cmd", MediaControllerGetError(nRet), mc_client_unset_cmd_reply_received_cb(g_hMcClient); mc_server_unset_custom_cmd_received_cb(g_hMcServer));

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "ServerCustomCmdReceivedCallback", "CallBack Not Invoked", mc_client_unset_cmd_reply_received_cb(g_hMcClient); mc_server_unset_custom_cmd_received_cb(g_hMcServer));

	g_CallBackHit = false;
	nRet = mc_server_send_cmd_reply(g_hMcServer, g_szClientName, g_request_id, nCode, bundle_data);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_send_cmd_reply", MediaControllerGetError(nRet), bundle_free(bundle_data); mc_client_unset_cmd_reply_received_cb(g_hMcClient); mc_server_unset_custom_cmd_received_cb(g_hMcServer));
	bundle_free(bundle_data);

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "ClientCustomComandReplyCallBack", "CallBack Not Invoked", mc_client_unset_cmd_reply_received_cb(g_hMcClient); mc_server_unset_custom_cmd_received_cb(g_hMcServer));

	nRet = mc_client_unset_cmd_reply_received_cb(g_hMcClient);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_cmd_reply_received_cb", MediaControllerGetError(nRet), mc_server_unset_custom_cmd_received_cb(g_hMcServer));

	nRet = mc_server_unset_custom_cmd_received_cb(g_hMcServer);
	PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_unset_custom_cmd_received_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mc_client_set_unset_cb_send_event_reply
 * @author            			SRID(samuel.peter)
 * @reviewer         			SRID(manoj.g2)
 * @type 				auto
 * @since_tizen 			4.0
 * @description				Sets and unsets the event callback for media controller client, and then checks if the callback is hit by sending event reply.
 * @scenario				Sets callback with mc_client_set_custom_event_received_cb, checks with mc_client_send_event_reply and then unsets with mc_client_unset_custom_event_received_cb.
 * @apicovered				mc_client_set_custom_event_received_cb, mc_server_set_event_reply_received_cb, mc_client_unset_custom_event_received_cb, mc_client_send_event_reply, mc_server_foreach_client, mc_server_send_custom_event, mc_server_unset_event_reply_received_cb.
 * @passcase				If mc_client_set_custom_event_received_cb, mc_client_send_event_reply and mc_client_unset_custom_event_received_cb return MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To check the event callbacks by setting and then sending an event reply.
int ITc_mc_client_set_unset_cb_send_event_reply_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	int nSize = 0;
	bool bReplyResult = false;
	bool bReplyName = false;
	bool bReplyRequest = false;
	char *pszEvent = "test";
	char *pszRequestID = NULL;
	char *pszClientName = NULL;
        mc_result_code_e eResultCodeArray[] = {
        MC_RESULT_CODE_SUCCESS,
        MC_RESULT_CODE_ALREADY_DONE,
        MC_RESULT_CODE_ABORTED,
        MC_RESULT_CODE_TIMEOUT,
        MC_RESULT_CODE_NETWORK_FAILED,
        MC_RESULT_CODE_NO_ACCOUNT,
        MC_RESULT_CODE_UNKNOWN,
};

        int nCount = 0;
        int nCountEnum = sizeof(eResultCodeArray)/sizeof(eResultCodeArray[0]);


	nRet = mc_client_set_custom_event_received_cb(g_hMcClient, EventReceivedCallback, NULL);
	PRINT_RESULT(nRet, MEDIA_CONTROLLER_ERROR_NONE, "mc_client_set_custom_event_received_cb", MediaControllerGetError(nRet));

	nRet = mc_server_set_event_reply_received_cb(g_hMcServer, EventReceivedCallback, NULL);
	PRINT_RESULT_CLEANUP(nRet, MEDIA_CONTROLLER_ERROR_NONE, "mc_server_set_event_reply_received_cb", MediaControllerGetError(nRet), mc_client_unset_custom_event_received_cb(g_hMcClient));

 	nRet = mc_server_foreach_client(g_hMcServer, McActivatedClientCb, &pszClientName);
	PRINT_RESULT_CLEANUP(nRet, MEDIA_CONTROLLER_ERROR_NONE, "mc_server_foreach_client", MediaControllerGetError(nRet), mc_client_unset_custom_event_received_cb(g_hMcClient); mc_server_unset_event_reply_received_cb(g_hMcServer));
	CHECK_HANDLE_CLEANUP(pszClientName, "mc_server_foreach_client", mc_client_unset_custom_event_received_cb(g_hMcClient); mc_server_unset_event_reply_received_cb(g_hMcServer));
        for(nCount = 0; nCount < nCountEnum; nCount++)
        {
                g_CallBackHit = false;
                pszRequestID = NULL;
                nRet = mc_server_send_custom_event(g_hMcServer, pszClientName, pszEvent, NULL, &pszRequestID);
                PRINT_RESULT_CLEANUP(nRet, MEDIA_CONTROLLER_ERROR_NONE, "mc_server_send_custom_event", MediaControllerGetError(nRet), FREE_MEMORY(pszClientName); mc_client_unset_custom_event_received_cb(g_hMcClient); mc_server_unset_event_reply_received_cb(g_hMcServer));
                CHECK_HANDLE_CLEANUP(pszRequestID, "mc_server_send_custom_event", FREE_MEMORY(pszClientName); mc_client_unset_custom_event_received_cb(g_hMcClient));

                IterateGmainLoop();
                PRINT_RESULT_CLEANUP(g_CallBackHit, true, "EventReceivedCallback", MediaControllerGetError(nRet), FREE_MEMORY(pszRequestID); FREE_MEMORY(pszClientName); mc_client_unset_custom_event_received_cb(g_hMcClient); mc_server_unset_event_reply_received_cb(g_hMcServer));

                g_CallBackHit = false;
                nRet = mc_client_send_event_reply(g_hMcClient, pszClientName, pszRequestID, eResultCodeArray[nCount], NULL);
                PRINT_RESULT_CLEANUP(nRet, MEDIA_CONTROLLER_ERROR_NONE, "mc_client_send_event_reply", MediaControllerGetError(nRet), FREE_MEMORY(pszRequestID); FREE_MEMORY(pszClientName); mc_client_unset_custom_event_received_cb(g_hMcClient); mc_server_unset_event_reply_received_cb(g_hMcServer));

                IterateGmainLoop();
                PRINT_RESULT_CLEANUP(g_CallBackHit, true, "EventReceivedCallback", "false", FREE_MEMORY(pszRequestID); FREE_MEMORY(pszClientName); mc_client_unset_custom_event_received_cb(g_hMcClient); mc_server_unset_event_reply_received_cb(g_hMcServer));
        }
        nRet = mc_client_unset_custom_event_received_cb(g_hMcClient);
        PRINT_RESULT_CLEANUP(nRet, MEDIA_CONTROLLER_ERROR_NONE, "mc_client_unset_event_reply_received_cb", MediaControllerGetError(nRet), FREE_MEMORY(pszRequestID); FREE_MEMORY(pszClientName); mc_server_unset_event_reply_received_cb(g_hMcServer));

        nRet = mc_server_unset_event_reply_received_cb(g_hMcServer);
        PRINT_RESULT_NORETURN(nRet, MEDIA_CONTROLLER_ERROR_NONE, "mc_server_unset_event_reply_received_cb", MediaControllerGetError(nRet));

        FREE_MEMORY(pszRequestID);
	FREE_MEMORY(pszClientName);
	return 0;
}

/**
 * @testcase 				ITc_mc_client_set_unset_playlist_updated_cb_p
 * @author            		SRID(bipin.k)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			4.0
 * @description				Positive test case to check wether callback is set and unset
 * @scenario				The media controller client which calls this function will receives the callback for playlist upgradation.
 * @apicovered				mc_client_set_playlist_updated_cb, mc_client_unset_playlist_updated_cb
 * @passcase				If Target API is successful and callback invoked
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
 //& type: auto
//& purpose: To check  wether set and unset of callback is correct or not
int ITc_mc_client_set_unset_playlist_updated_cb_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h hPlaylist = NULL;

	g_CallBackHit = false;

	nRet = mc_client_set_playlist_updated_cb(g_hMcClient, ClientMcPlaylistUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_playlist_updated_cb", MediaControllerGetError(nRet));

	nRet = ClientMcRegisterPlaylist(&hPlaylist);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "ClientMcRegisterPlaylist", MediaControllerGetError(nRet),mc_client_unset_playlist_updated_cb(g_hMcClient));
	CHECK_HANDLE_CLEANUP(hPlaylist, "ClientMcRegisterPlaylist",mc_client_unset_playlist_updated_cb(g_hMcClient));

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(g_CallBackHit, true, "mc_client_set_playlist_updated_cb", "Callback not hit Correctly", mc_client_unset_playlist_updated_cb(g_hMcClient));


	nRet = mc_client_unset_playlist_updated_cb(g_hMcClient);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_playlist_updated_cb", MediaControllerGetError(nRet));

	return 0;
}

 /**
 * @testcase 					ITc_mc_playlist_get_name_p
 * @author					SRID(bipin.k)
 * @reviewer					SRID(manoj.g2)
 * @type 						auto
 * @since_tizen 				4.0
 * @description				Positive test case of ITc_mc_playlist_get_name_p
 * @scenario					The ITc_mc_playlist_get_name_p returns correct playlist name.
 * @apicovered				mc_server_create_playlist, mc_playlist_get_name
 * @passcase					If the playlist name  returned is correct.
 * @failcase					If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
 //& type: auto
//& purpose: To get playlist name
int ITc_mc_playlist_get_name_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h hPlaylist = NULL;
	char *pszPlaylistName = NULL;
	bool bCheckVal = false;

	nRet = mc_server_create_playlist(g_hMcServer, g_PlaylistName, &hPlaylist);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_create_playlist", MediaControllerGetError(nRet));
	CHECK_HANDLE(hPlaylist, "mc_server_create_playlist");

	nRet = mc_playlist_get_name(hPlaylist, &pszPlaylistName);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_get_name", MediaControllerGetError(nRet),mc_playlist_destroy(hPlaylist));

	if (pszPlaylistName != NULL) {
		if (strncmp(g_PlaylistName, pszPlaylistName,strlen(g_PlaylistName)) == 0)
			bCheckVal = true;

		FREE_MEMORY(pszPlaylistName);
	}
	else{
		FPRINTF("[Line : %d][%s] %s pszPlaylistName is NULL\\n", __LINE__, API_NAMESPACE,"mc_playlist_get_name");
		mc_playlist_destroy(hPlaylist);
		return 1;
	}

	if (bCheckVal != true)
	{
		FPRINTF("[Line : %d][%s] %s index returned did not match\\n", __LINE__, API_NAMESPACE, "mc_playlist_get_name");
		mc_playlist_destroy(hPlaylist);
		return 1;
	}

	nRet = mc_playlist_destroy(hPlaylist);
	PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_destroy", MediaControllerGetError(nRet));

	return 0;
}

 /**
 * @testcase 				ITc_mc_client_set_unset_playback_ability_updated_cb_p
 * @author					SRID(priya.kohli)
 * @reviewer				SRID(awadhesh1.s)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				Sets and unsets the callback for monitoring the playback ability of the media controller server.
 * @scenario				Sets and unsets the callback for monitoring the playback ability of the media controller server.
 *							The media controller client which calls this function will receive notifications from all media controller servers.
 * @apicovered				mc_client_set_playback_ability_updated_cb, mc_server_update_playback_ability, mc_client_unset_playback_ability_updated_cb
 * @passcase				If Target API is successful and callback is invoked
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
 //& type: auto
//& purpose: To set and unset the callback for monitoring the playback ability of the media controller server.
int ITc_mc_client_set_unset_playback_ability_updated_cb_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	g_CallBackHit = false;

	nRet = mc_client_set_playback_ability_updated_cb(g_hMcClient, ClientPlaybackAbilityUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_playback_ability_updated_cb", MediaControllerGetError(nRet));

	nRet = mc_server_update_playback_ability(g_hMcServer);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_playback_ability", MediaControllerGetError(nRet), mc_client_unset_playback_ability_updated_cb(g_hMcClient));
	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "mc_client_set_playback_ability_updated_cb", "CallBack Not Invoked", mc_client_unset_playback_ability_updated_cb(g_hMcClient));

	nRet = mc_client_unset_playback_ability_updated_cb(g_hMcClient);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_playback_ability_updated_cb", MediaControllerGetError(nRet));

	return 0;
}

 /**
 * @testcase 					ITc_mc_client_set_get_playlist_item_info_p
 * @author					SRID(kanchan.m)
 * @reviewer					SRID(awadhesh1.s)
 * @type 						auto
 * @since_tizen 				5.0
 * @description				Sets and Gets the playlist name and index of the media in playlist.
 * @scenario					Sets and Gets the playlist name and index of the media in playlist.
 * @apicovered				mc_server_set_playlist_item_info, mc_client_get_playlist_item_info
 * @passcase					If the playlist name and index of the media returned is correct.
 * @failcase					If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
 //& type: auto
//& purpose: To set and get the playlist name and index of the media in playlist.
int ITc_mc_client_set_get_playlist_item_info_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_h hPlayBack = NULL;
	char * pszGetIndex = 0;
	char * pszSetItemIndex = "3";
	char * pszGetPlaylistName = NULL;
	char * pszServerName = NULL;
	mc_server_state_e eServerState;

	nRet = mc_server_set_playlist_item_info(g_hMcServer, g_PlaylistName, pszSetItemIndex);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_playlist_item_info", MediaControllerGetError(nRet));

	nRet = mc_server_update_playback_info(g_hMcServer);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_playback_info", MediaControllerGetError(nRet));

	nRet = mc_client_get_latest_server_info(g_hMcClient, &pszServerName, &eServerState);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet));
	CHECK_HANDLE(pszServerName,"mc_client_get_latest_server_info");

	if((eServerState < MC_SERVER_STATE_NONE) || (eServerState > MC_SERVER_STATE_DEACTIVATE))
	{
		FPRINTF("[Line : %d][%s] %s Enum returned is out of range =%d \\n", __LINE__, API_NAMESPACE, "eServerState ",eServerState);
		FREE_MEMORY(pszServerName);
		return 1;
	}

	nRet = mc_client_get_server_playback_info(g_hMcClient, pszServerName, &hPlayBack);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_playback_info", MediaControllerGetError(nRet), FREE_MEMORY(pszServerName));
	CHECK_HANDLE_CLEANUP(hPlayBack, "mc_client_get_server_playback_info", FREE_MEMORY(pszServerName));

	nRet = mc_client_get_playlist_item_info(hPlayBack, &pszGetPlaylistName, &pszGetIndex);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_playlist_item_info", MediaControllerGetError(nRet),mc_client_destroy_playback(hPlayBack);FREE_MEMORY(pszServerName));
	CHECK_HANDLE_CLEANUP(pszGetPlaylistName, "mc_client_get_playlist_item_info",mc_client_destroy_playback(hPlayBack);FREE_MEMORY(pszServerName));
	CHECK_HANDLE_CLEANUP(pszGetIndex, "mc_client_get_playlist_item_info",mc_client_destroy_playback(hPlayBack);FREE_MEMORY(pszServerName);FREE_MEMORY(pszGetPlaylistName));

	if (strncmp(pszGetIndex, pszSetItemIndex, strlen(pszSetItemIndex))!= 0)
	{
		FPRINTF("[Line : %d][%s] %s index returned did not match =%s \\n", __LINE__, API_NAMESPACE, "mc_client_get_playlist_item_info",pszGetIndex);
		nRet = mc_client_destroy_playback(hPlayBack);
		PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_destroy_playback", MediaControllerGetError(nRet));
		FREE_MEMORY(pszGetIndex);
		FREE_MEMORY(pszGetPlaylistName);
		FREE_MEMORY(pszServerName);
		return 1;
	}

	if (strncmp(pszGetPlaylistName, g_PlaylistName, strlen(g_PlaylistName))!= 0)
	{
		FPRINTF("[Line : %d][%s] %s index returned did not match =%s \\n", __LINE__, API_NAMESPACE, "mc_client_get_playlist_item_info",pszGetPlaylistName);
		nRet = mc_client_destroy_playback(hPlayBack);
		PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_destroy_playback", MediaControllerGetError(nRet));
		FREE_MEMORY(pszGetIndex);
		FREE_MEMORY(pszGetPlaylistName);
		FREE_MEMORY(pszServerName);

		return 1;
	}

	nRet = mc_client_destroy_playback(hPlayBack);
	PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_destroy_playback", MediaControllerGetError(nRet));

	FREE_MEMORY(pszGetIndex);
	FREE_MEMORY(pszGetPlaylistName);
	FREE_MEMORY(pszServerName);

    return 0;
}

 /**
 * @testcase 					ITc_mc_client_set_get_age_rating_p
 * @author					SRID(kanchan.m)
 * @reviewer					SRID(priya.kohli)
 * @type 					auto
 * @since_tizen 				5.0
 * @description					Sets and Gets age rating of the content to update the latest playback info.
 * @scenario					Sets and Gets age rating of the content to update the latest playback info.
 * @apicovered					mc_server_set_content_age_rating, mc_client_get_age_rating
 * @passcase					If the age rating of the content is correct.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				NA
 * @postcondition				NA
 * */
 //& type: auto
//& purpose: To set and get age rating of the content to update the latest playback info.
int ITc_mc_client_set_get_age_rating_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_content_age_rating_e eContentAgeRatingArray[] = {MC_CONTENT_RATING_ALL,
								MC_CONTENT_RATING_1_PLUS,
								MC_CONTENT_RATING_2_PLUS,
								MC_CONTENT_RATING_3_PLUS,
								MC_CONTENT_RATING_4_PLUS,
								MC_CONTENT_RATING_5_PLUS,
								MC_CONTENT_RATING_6_PLUS,
								MC_CONTENT_RATING_7_PLUS,
								MC_CONTENT_RATING_8_PLUS,
								MC_CONTENT_RATING_9_PLUS,
								MC_CONTENT_RATING_10_PLUS,
								MC_CONTENT_RATING_11_PLUS,
								MC_CONTENT_RATING_12_PLUS,
								MC_CONTENT_RATING_13_PLUS,
								MC_CONTENT_RATING_14_PLUS,
								MC_CONTENT_RATING_15_PLUS,
								MC_CONTENT_RATING_16_PLUS,
								MC_CONTENT_RATING_17_PLUS,
								MC_CONTENT_RATING_18_PLUS,
								MC_CONTENT_RATING_19_PLUS};
									mc_content_age_rating_e eGetContentAgeRating;
	mc_playback_h hPlayBack = NULL;
	char * pszServerName = NULL;
	mc_server_state_e eServerState = -1;

	int nSize = sizeof(eContentAgeRatingArray)/sizeof(eContentAgeRatingArray[0]);

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	for(int nCounter = 0; nCounter < nSize; nCounter++)
	{
		nRet = mc_server_set_content_age_rating(g_hMcServer, eContentAgeRatingArray[nCounter]);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_content_age_rating", MediaControllerGetError(nRet));

		nRet = mc_server_update_playback_info(g_hMcServer);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_playback_info", MediaControllerGetError(nRet));

		nRet = mc_client_get_latest_server_info(g_hMcClient, &pszServerName, &eServerState);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet));
		CHECK_HANDLE(pszServerName,"mc_client_get_latest_server_info");

		if((eServerState < MC_SERVER_STATE_NONE) || (eServerState > MC_SERVER_STATE_DEACTIVATE))
		{
			FPRINTF("[Line : %d][%s] %s Enum returned is out of range =%d \\n", __LINE__, API_NAMESPACE, "eServerState ",eServerState);
			FREE_MEMORY(pszServerName);
			return 1;
		}

		nRet = mc_client_get_server_playback_info(g_hMcClient, pszServerName, &hPlayBack);
		PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_playback_info", MediaControllerGetError(nRet), FREE_MEMORY(pszServerName));
		CHECK_HANDLE_CLEANUP(hPlayBack, "mc_client_get_server_playback_info", FREE_MEMORY(pszServerName));

		nRet = mc_client_get_age_rating(hPlayBack, &eGetContentAgeRating);
		PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_age_rating", MediaControllerGetError(nRet), FREE_MEMORY(pszServerName); mc_client_destroy_playback(hPlayBack));

		if (eContentAgeRatingArray[nCounter] != eGetContentAgeRating)
		{
			FPRINTF("[Line : %d][%s] %s Content type returned did not match \\n", __LINE__, API_NAMESPACE, "mc_client_get_age_rating");
			FREE_MEMORY(pszServerName)
			mc_client_destroy_playback(hPlayBack);
			return 1;
		}
	}
	FREE_MEMORY(pszServerName);
	mc_client_destroy_playback(hPlayBack);
	return 0;
}

 /**
 * @testcase 					ITc_mc_client_send_search_cmd_p
 * @author					SRID(kanchan.m)
 * @reviewer					SRID(priya.kohli)
 * @type 					auto
 * @since_tizen 				5.0
 * @description					Sends the search command to server.
 * @scenario					Sends the search command to server.
 * @apicovered				mc_server_set_search_cmd_received_cb, mc_client_get_latest_server_info, mc_search_set_condition, mc_client_send_search_cmd
 * @passcase					If mc_client_send_search_cmd returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				NA
 * @postcondition				NA
 * */
 //& type: auto
//& purpose: Sends the search command to server.
int ITc_mc_client_send_search_cmd_p(void)
{
	START_TEST;

	int nRet = -1;
	char * pszRequestID = 0;
	mc_content_type_e eContentType = MC_CONTENT_TYPE_IMAGE;
	mc_search_category_e eSearchCategory = MC_SEARCH_TITLE;
	char* pszTestKeywords = "test_title";
	g_CallBackHit = false;
	char * pszServerName = NULL;
	mc_server_state_e eServerState = -1;

	nRet = mc_server_set_search_cmd_received_cb(g_hMcServer, McServerSearchCmdReceivedCallBack, NULL);
	PRINT_RESULT(nRet, MEDIA_CONTROLLER_ERROR_NONE, "mc_server_set_search_cmd_received_cb", MediaControllerGetError(nRet));

	nRet = mc_client_get_latest_server_info(g_hMcClient, &pszServerName, &eServerState);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet));
	CHECK_HANDLE(pszServerName,"mc_client_get_latest_server_info");

	if((eServerState < MC_SERVER_STATE_NONE) || (eServerState > MC_SERVER_STATE_DEACTIVATE))
	{
		FPRINTF("[Line : %d][%s] %s Enum returned is out of range =%d \\n", __LINE__, API_NAMESPACE, "eServerState ",eServerState);
		FREE_MEMORY(pszServerName);
		return 1;
	}

	nRet = mc_search_set_condition(g_hMcSearch, eContentType, eSearchCategory, pszTestKeywords, NULL);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_search_set_condition", MediaControllerGetError(nRet), FREE_MEMORY(pszServerName));

	nRet = mc_client_send_search_cmd(g_hMcClient, pszServerName, g_hMcSearch, &pszRequestID);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_search_cmd", MediaControllerGetError(nRet), FREE_MEMORY(pszServerName));
	CHECK_HANDLE_CLEANUP(pszRequestID,"mc_client_send_search_cmd", FREE_MEMORY(pszServerName));

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "mc_client_send_search_cmd", "CallBack Not Invoked", FREE_MEMORY(pszServerName); FREE_MEMORY(pszRequestID));
	FREE_MEMORY(pszRequestID);
	FREE_MEMORY(pszServerName);

	return 0;
}

 /**
 * @testcase 					ITc_mc_search_create_clone_destroy_p
 * @author					SRID(kanchan.m)
 * @reviewer					SRID(priya.kohli)
 * @type 					auto
 * @since_tizen 				5.0
 * @description					To test mc_search_create, mc_search_clone, mc_search_destroy.
 * @scenario					To test mc_search_create, mc_search_clone, mc_search_destroy.
 * @apicovered					mc_search_create, mc_search_clone, mc_search_destroy
 * @passcase					If mc_client_create, mc_client_destroy and mc_search_destroy returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				NA
 * @postcondition				NA
 * */
 //& type: auto
//& purpose: To test mc_search_create, mc_search_clone, mc_search_destroy.
int ITc_mc_search_create_clone_destroy_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_search_h hMCSearch = NULL;
	mc_search_h hMCSearchDst = NULL;

	nRet = mc_search_create(&hMCSearch);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_search_create", MediaControllerGetError(nRet));
	CHECK_HANDLE(hMCSearch, "mc_search_create");

	nRet = mc_search_clone(hMCSearch, &hMCSearchDst);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_search_clone", MediaControllerGetError(nRet),mc_search_destroy(hMCSearch));
	CHECK_HANDLE_CLEANUP(hMCSearchDst, "mc_search_clone", mc_search_destroy(hMCSearch));

	nRet = mc_search_destroy(hMCSearch);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_search_destroy", MediaControllerGetError(nRet), mc_search_destroy(hMCSearchDst));

	nRet = mc_search_destroy(hMCSearchDst);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_search_destroy", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 					ITc_mc_search_set_condition_p
 * @author					SRID(kanchan.m)
 * @reviewer					SRID(priya.kohli)
 * @type 					auto
 * @since_tizen 				5.0
 * @description					Sets the information to search.
 * @scenario					Sets the information to search.
 * @apicovered					mc_search_set_condition
 * @passcase					If mc_search_set_condition returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				NA
 * @postcondition				NA
 * */
 //& type: auto
//& purpose: Sets the information to search.
int ITc_mc_search_set_condition_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;

	int nContentTypeSize = sizeof(g_eContentTypeArray)/sizeof(g_eContentTypeArray[0]);
	int nSearchCategorySize = sizeof(g_eSearchCategoryArray)/sizeof(g_eSearchCategoryArray[0]);

	for ( int nContentTypeCounter = 0; nContentTypeCounter < nContentTypeSize; nContentTypeCounter++ )
	{
		for ( int nSearchCategoryCounter = 0; nSearchCategoryCounter < nSearchCategorySize; nSearchCategoryCounter++ )
		{
			nRet = mc_search_set_condition(g_hMcSearch, g_eContentTypeArray[nContentTypeCounter], g_eSearchCategoryArray[nSearchCategoryCounter], g_TestKeywords[nSearchCategoryCounter], NULL);
			PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_search_set_condition", MediaControllerGetError(nRet));
		}
	}
	return 0;
}

/**
 * @testcase 					ITc_mc_search_foreach_condition_p
 * @author					SRID(kanchan.m)
 * @reviewer					SRID(priya.kohli)
 * @type 					auto
 * @since_tizen 				5.0
 * @description					This function gets all search conditions set.
 * @scenario					This function gets all search conditions set.
 * @apicovered					mc_search_foreach_condition
 * @passcase					If mc_search_foreach_condition returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				NA
 * @postcondition				NA
 * */
 //& type: auto
//& purpose: This function gets all search conditions set.
int ITc_mc_search_foreach_condition_p(void)
{
	START_TEST;

	g_CallBackHit = false;
	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_content_type_e eContentType = MC_CONTENT_TYPE_IMAGE;
	mc_search_category_e eSearchCategory = MC_SEARCH_TITLE;
	char* pszTestKeywords = "test_title";

	nRet = mc_search_set_condition(g_hMcSearch, eContentType, eSearchCategory, pszTestKeywords, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_search_set_condition", MediaControllerGetError(nRet));

	nRet = mc_search_foreach_condition(g_hMcSearch, McSearchConditionCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_search_foreach_condition", MediaControllerGetError(nRet));

	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "mc_search_foreach_condition", "CallBack Not Invoked");

	return 0;
}

/**
 * @testcase 					ITc_mc_search_get_condition_count_p
 * @author					SRID(karanam.s)
 * @reviewer					SRID(priya.kohli)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Gets the number of conditions to search.
 * @scenario					Call mc_server_create, mc_search_set_condition, mc_search_get_condition_count and mc_server_destroy
 * @apicovered					mc_search_get_condition_count
 * @passcase					If mc_search_get_condition_count returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_server_create
 * @postcondition				mc_server_destroy
 * */
 //& type: auto
//& purpose: This function gets the number of conditions to search.
int ITc_mc_search_get_condition_count_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	int nSetCount = 0;
	int nGetCount = -1;

	int nContentTypeSize = sizeof(g_eContentTypeArray)/sizeof(g_eContentTypeArray[0]);
	int nSearchCategorySize = sizeof(g_eSearchCategoryArray)/sizeof(g_eSearchCategoryArray[0]);

	for ( int nContentTypeCounter = 0; nContentTypeCounter < nContentTypeSize; nContentTypeCounter++ )
	{
		for ( int nSearchCategoryCounter = 0; nSearchCategoryCounter < nSearchCategorySize; nSearchCategoryCounter++ )
		{
			nRet = mc_search_set_condition(g_hMcSearch, g_eContentTypeArray[nContentTypeCounter], g_eSearchCategoryArray[nSearchCategoryCounter], g_TestKeywords[nSearchCategoryCounter], NULL);
			PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_search_set_condition", MediaControllerGetError(nRet));
			nSetCount+=1;
		}
	}

	nRet = mc_search_get_condition_count(g_hMcSearch, &nGetCount);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_search_get_condition_count", MediaControllerGetError(nRet));
	if(nGetCount != nSetCount)
	{
		FPRINTF("[Line : %d][%s] SetCount %d did not match with GetCount %d\\n", __LINE__, API_NAMESPACE, nSetCount, nGetCount);
		return 1;
	}

	return 0;
}

/**
 * @testcase 					ITc_mc_client_set_unset_ability_support_updated_cb_p
 * @author					SRID(manoj.g2)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Set and Unset callback for ability support.
 * @scenario					Call mc_client_set_ability_support_updated_cb,mc_client_unset_ability_support_updated_cb, mc_server_set_ability_support
 * @apicovered					mc_client_set_ability_support_updated_cb,mc_client_unsetset_ability_support_updated_cb, mc_server_set_ability_support
 * @passcase					If mc_client_set_ability_support_updated_cb,mc_client_unsetset_ability_support_updated_cb, mc_server_set_ability_support returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_server_create
 * @postcondition				mc_server_destroy
 * */
 //& type: auto
//& purpose: This function Set and Unset callback for ability support.
int ITc_mc_client_set_unset_ability_support_updated_cb_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	g_CallBackHit = false;

	int nAbilityTypeSize = sizeof(g_eAbilitySupportAllArray)/sizeof(g_eAbilitySupportAllArray[0]);

	nRet = mc_client_set_ability_support_updated_cb(g_hMcClient, ClientAbilitySupportUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_ability_support_updated_cb", MediaControllerGetError(nRet));

	for ( int nAbilityTypeCounter = 0; nAbilityTypeCounter < nAbilityTypeSize; nAbilityTypeCounter++ )
	{
		g_CallBackHit = false;
		nRet = mc_server_set_ability_support(g_hMcServer,  g_eAbilitySupportAllArray[nAbilityTypeCounter], MC_ABILITY_SUPPORTED_YES);
		PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_ability_support", MediaControllerGetError(nRet), mc_client_unset_ability_support_updated_cb(g_hMcClient));
		IterateGmainLoop();
		PRINT_RESULT_CLEANUP(true, g_CallBackHit, "mc_server_set_ability_support", "CallBack Not Invoked", mc_client_unset_ability_support_updated_cb(g_hMcClient));
	}

	nRet = mc_client_unset_ability_support_updated_cb(g_hMcClient);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_ability_support_updated_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 					ITc_mc_client_get_server_ability_support_p
 * @author					SRID(manoj.g2)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Gets the support value of the ability support of the updated media controller server.
 * @scenario					Call mmc_client_get_server_ability_support
 * @apicovered					mc_client_get_server_ability_support
 * @passcase					If mc_client_get_server_ability_support returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_server_create
 * @postcondition				mc_server_destroy
 * */
 //& type: auto
//& purpose: Gets the support value of the ability support of the updated media controller server.
int ITc_mc_client_get_server_ability_support_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_ability_support_e eAbilitySupport = -1;;
	int nAbilityTypeSize = sizeof(g_eAbilitySupportAllArray)/sizeof(g_eAbilitySupportAllArray[0]);

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(0, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	for ( int nAbilityTypeCounter = 0; nAbilityTypeCounter < nAbilityTypeSize; nAbilityTypeCounter++ )
	{
		nRet = mc_client_get_server_ability_support(g_hMcClient, g_szServerName, g_eAbilitySupportAllArray[nAbilityTypeCounter], &eAbilitySupport);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_ability_support", MediaControllerGetError(nRet));

		if((eAbilitySupport < MC_ABILITY_SUPPORTED_YES) || (eAbilitySupport > MC_ABILITY_SUPPORTED_UNDECIDED))
		{
			FPRINTF("[Line : %d][%s] Enum returned is out of range\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}


	return 0;
}

/**
 * @testcase 					ITc_mc_client_set_unset_display_mode_ability_updated_cb_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Sets and unset the callback for monitoring the display mode ability of the media controller server.
 * @scenario					Call mc_client_set_display_mode_ability_updated_cb and mc_client_unset_display_mode_ability_updated_cb
 * @apicovered					mc_client_set_display_mode_ability_updated_cb, mc_client_unset_display_mode_ability_updated_cb
 * @passcase					If mc_client_set_display_mode_ability_updated_cb, mc_client_unset_display_mode_ability_updated_cb returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_server_create
 * @postcondition				mc_server_destroy
 * */
 //& type: auto
//& purpose: Sets and unset the callback for monitoring the display mode ability of the media controller server.
int ITc_mc_client_set_unset_display_mode_ability_updated_cb_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	unsigned int uDisplayMode = MC_DISPLAY_MODE_LETTER_BOX | MC_DISPLAY_MODE_ORIGIN_SIZE | MC_DISPLAY_MODE_FULL_SCREEN | MC_DISPLAY_MODE_CROPPED_FULL;
	g_CallBackHit = false;

	nRet = mc_client_set_display_mode_ability_updated_cb(g_hMcClient, ClientAbilitySupportedItemsUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_display_mode_ability_updated_cb", MediaControllerGetError(nRet));

	nRet = mc_server_set_display_mode_ability(g_hMcServer, uDisplayMode, MC_ABILITY_SUPPORTED_YES);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_display_mode_ability", MediaControllerGetError(nRet), mc_client_unset_display_mode_ability_updated_cb(g_hMcClient));

	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "mc_client_set_display_mode_ability_updated_cb", "CallBack Not Invoked");

	nRet = mc_client_unset_display_mode_ability_updated_cb(g_hMcClient);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_display_mode_ability_updated_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 					ITc_mc_client_set_unset_display_rotation_ability_updated_cb_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Sets and unsets the callback for monitoring the display rotation ability of the media controller server.
 * @scenario					Call mc_client_set_display_rotation_ability_updated_cb and mc_client_unset_display_rotation_ability_updated_cb
 * @apicovered					mc_client_set_display_rotation_ability_updated_cb, mc_client_unset_display_rotation_ability_updated_cb
 * @passcase					If mc_client_set_display_rotation_ability_updated_cb, mc_client_unset_display_rotation_ability_updated_cb returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_server_create
 * @postcondition				mc_server_destroy
 * */
 //& type: auto
//& purpose: Sets and unsets the callback for monitoring the display rotation ability of the media controller server.
int ITc_mc_client_set_unset_display_rotation_ability_updated_cb_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	unsigned int uDisplayRotation = MC_DISPLAY_ROTATION_NONE | MC_DISPLAY_ROTATION_90 | MC_DISPLAY_ROTATION_180 | MC_DISPLAY_ROTATION_270;
	g_CallBackHit = false;

	nRet = mc_client_set_display_rotation_ability_updated_cb(g_hMcClient, ClientAbilitySupportedItemsUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_display_rotation_ability_updated_cb", MediaControllerGetError(nRet));

	nRet = mc_server_set_display_rotation_ability(g_hMcServer, uDisplayRotation, MC_ABILITY_SUPPORTED_YES);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_display_rotation_ability", MediaControllerGetError(nRet), mc_client_unset_display_rotation_ability_updated_cb(g_hMcClient));

	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "mc_client_set_display_rotation_ability_updated_cb", "CallBack Not Invoked");

	nRet = mc_client_unset_display_rotation_ability_updated_cb(g_hMcClient);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_display_rotation_ability_updated_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 					ITc_mc_client_set_unset_subtitles_updated_cb_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Sets and unsets the callback for monitoring the media controller server's subtitles display.
 * @scenario					Call mc_client_set_subtitles_updated_cb and mc_client_unset_subtitles_updated_cb
 * @apicovered					mc_client_set_subtitles_updated_cb, mc_client_unset_subtitles_updated_cb
 * @passcase					If mc_client_set_subtitles_updated_cb, mc_client_unset_subtitles_updated_cb returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_server_create
 * @postcondition				mc_server_destroy
 * */
 //& type: auto
//& purpose: Sets and unsets the callback for monitoring the media controller server's subtitles display.
int ITc_mc_client_set_unset_subtitles_updated_cb_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	g_CallBackHit = false;

	nRet = mc_client_set_subtitles_updated_cb(g_hMcClient, ClientBoolAttributeUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_subtitles_updated_cb", MediaControllerGetError(nRet));

	nRet = mc_server_update_subtitles_enabled(g_hMcServer, true);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_subtitles_enabled", MediaControllerGetError(nRet), mc_client_unset_subtitles_updated_cb(g_hMcClient));

	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "mc_client_set_subtitles_updated_cb", "CallBack Not Invoked");

	nRet = mc_client_unset_subtitles_updated_cb(g_hMcClient);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_subtitles_updated_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 					ITc_mc_client_set_unset_360_mode_updated_cb_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Sets and unsets the callback for monitoring the media controller server's 360 mode display.
 * @scenario					Call mc_client_set_360_mode_updated_cb and mc_client_unset_360_mode_updated_cb
 * @apicovered					mc_client_set_360_mode_updated_cb, mc_client_unset_360_mode_updated_cb
 * @passcase					If mc_client_set_360_mode_updated_cb, mc_client_unset_360_mode_updated_cb returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_server_create
 * @postcondition				mc_server_destroy
 * */
 //& type: auto
//& purpose: Sets and unsets the callback for monitoring the media controller server's 360 mode display.
int ITc_mc_client_set_unset_360_mode_updated_cb_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	g_CallBackHit = false;

	nRet = mc_client_set_360_mode_updated_cb(g_hMcClient, ClientBoolAttributeUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_360_mode_updated_cb", MediaControllerGetError(nRet));

	nRet = mc_server_update_360_mode_enabled(g_hMcServer, true);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_360_mode_enabled", MediaControllerGetError(nRet), mc_client_unset_360_mode_updated_cb(g_hMcClient));

	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "mc_client_set_360_mode_updated_cb", "CallBack Not Invoked");

	nRet = mc_client_unset_360_mode_updated_cb(g_hMcClient);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_360_mode_updated_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 					ITc_mc_client_set_unset_display_mode_updated_cb_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Sets and unsets the callback for monitoring the media controller server's display mode.
 * @scenario					Call mc_client_set_display_mode_updated_cb and mc_client_unset_display_mode_updated_cb
 * @apicovered					mc_client_set_display_mode_updated_cb, mc_client_unset_display_mode_updated_cb
 * @passcase					If mc_client_set_display_mode_updated_cb, mc_client_unset_display_mode_updated_cb returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_server_create
 * @postcondition				mc_server_destroy
 * */
 //& type: auto
//& purpose: Sets and unsets the callback for monitoring the media controller server's display mode.
int ITc_mc_client_set_unset_display_mode_updated_cb_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;

	nRet = mc_client_set_display_mode_updated_cb(g_hMcClient, ClientDisplayModeUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_display_mode_updated_cb", MediaControllerGetError(nRet));

	int nModeSize = sizeof(g_controller_eDisplayModeArray)/sizeof(g_controller_eDisplayModeArray[0]);

	for(g_nModeIdx = 0; g_nModeIdx < nModeSize; g_nModeIdx++)
	{
		g_CallBackHit = false;
		nRet = mc_server_update_display_mode(g_hMcServer, g_controller_eDisplayModeArray[g_nModeIdx]);
		PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_display_mode", MediaControllerGetError(nRet), mc_client_unset_display_mode_updated_cb(g_hMcClient));

		IterateGmainLoop();
		PRINT_RESULT_CLEANUP(true, g_CallBackHit, "mc_client_set_display_mode_updated_cb", "CallBack Not Invoked", mc_client_unset_display_mode_updated_cb(g_hMcClient));
	}

	nRet = mc_client_unset_display_mode_updated_cb(g_hMcClient);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_display_mode_updated_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 					ITc_mc_client_set_unset_display_rotation_updated_cb_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Sets and unsets the callback for monitoring the media controller server's display rotation.
 * @scenario					Call mc_client_set_display_rotation_updated_cb and mc_client_unset_display_rotation_updated_cb
 * @apicovered					mc_client_set_display_rotation_updated_cb, mc_client_unset_display_rotation_updated_cb
 * @passcase					If mc_client_set_display_rotation_updated_cb, mc_client_unset_display_rotation_updated_cb returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_server_create
 * @postcondition				mc_server_destroy
 * */
 //& type: auto
//& purpose: Sets and unsets the callback for monitoring the media controller server's display rotation.
int ITc_mc_client_set_unset_display_rotation_updated_cb_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;

	nRet = mc_client_set_display_rotation_updated_cb(g_hMcClient, ClientDisplayRotationUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_display_rotation_updated_cb", MediaControllerGetError(nRet));

	int nRotationSize = sizeof(g_controller_eDisplayRotationArray)/sizeof(g_controller_eDisplayRotationArray[0]);

	for(g_nRotationIdx = 0; g_nRotationIdx < nRotationSize; g_nRotationIdx++)
	{
		g_CallBackHit = false;
		nRet = mc_server_update_display_rotation(g_hMcServer, g_controller_eDisplayRotationArray[g_nRotationIdx]);
		PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_display_rotation", MediaControllerGetError(nRet), mc_client_unset_display_rotation_updated_cb(g_hMcClient));

		IterateGmainLoop();
		PRINT_RESULT_CLEANUP(true, g_CallBackHit, "mc_client_set_display_rotation_updated_cb", "CallBack Not Invoked", mc_client_unset_display_rotation_updated_cb(g_hMcClient));
	}

	nRet = mc_client_unset_display_rotation_updated_cb(g_hMcClient);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_unset_display_rotation_updated_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 					ITc_mc_client_get_server_subtitles_enabled_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Gets the latest subtitles display status.
 * @scenario					Call mc_client_get_server_subtitles_enabled
 * @apicovered					mc_client_get_server_subtitles_enabled
 * @passcase					If mc_client_get_server_subtitles_enabled returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_server_create
 * @postcondition				mc_server_destroy
 * */
 //& type: auto
//& purpose: Gets the latest subtitles display status.
int ITc_mc_client_get_server_subtitles_enabled_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	bool bIsEnabled = false;

	nRet = mc_server_update_subtitles_enabled(g_hMcServer, true);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_subtitles_enabled", MediaControllerGetError(nRet));

	nRet = mc_client_get_latest_server_info(g_hMcClient, &g_McServerName, &g_McServerState);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet));

	nRet = mc_client_get_server_subtitles_enabled(g_hMcClient, g_McServerName, &bIsEnabled);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_subtitles_enabled", MediaControllerGetError(nRet));

	PRINT_RESULT(true, bIsEnabled, "mc_client_get_server_subtitles_enabled", "mc_client_get_server_subtitles_enabled return value is different");
	return 0;
}

/**
 * @testcase 					ITc_mc_client_get_server_360_mode_enabled_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Gets the latest subtitles display status.
 * @scenario					Call mc_client_get_server_subtitles_enabled
 * @apicovered					mc_client_get_server_subtitles_enabled
 * @passcase					If mc_client_get_server_subtitles_enabled returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_server_create
 * @postcondition				mc_server_destroy
 * */
 //& type: auto
//& purpose: Gets the latest subtitles display status.
int ITc_mc_client_get_server_360_mode_enabled_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	bool bIsEnabled = false;

	nRet = mc_server_update_360_mode_enabled(g_hMcServer, true);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_360_mode_enabled", MediaControllerGetError(nRet));

	nRet = mc_client_get_latest_server_info(g_hMcClient, &g_McServerName, &g_McServerState);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet));

	nRet = mc_client_get_server_360_mode_enabled(g_hMcClient, g_McServerName, &bIsEnabled);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_360_mode_enabled", MediaControllerGetError(nRet));

	PRINT_RESULT(true, bIsEnabled, "mc_client_get_server_360_mode_enabled", "mc_client_get_server_360_mode_enabled return value is different");
	return 0;
}

/**
 * @testcase 					ITc_mc_client_get_server_display_mode_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Gets the latest display mode.
 * @scenario					Call mc_client_get_server_display_mode
 * @apicovered					mc_client_get_server_display_mode
 * @passcase					If mc_client_get_server_display_mode returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_server_create
 * @postcondition				mc_server_destroy
 * */
 //& type: auto
//& purpose: Gets the latest display mode.
int ITc_mc_client_get_server_display_mode_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_display_mode_e eGetMode = 0;

	int nModeSize = sizeof(g_controller_eDisplayModeArray)/sizeof(g_controller_eDisplayModeArray[0]);
	int nModeIdx;

	for(nModeIdx = 0; nModeIdx < nModeSize; nModeIdx++)
	{
		nRet = mc_server_update_display_mode(g_hMcServer, g_controller_eDisplayModeArray[nModeIdx]);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_display_mode", MediaControllerGetError(nRet));

		nRet = mc_client_get_latest_server_info(g_hMcClient, &g_McServerName, &g_McServerState);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet));

		nRet = mc_client_get_server_display_mode(g_hMcClient, g_McServerName, &eGetMode);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_display_mode", MediaControllerGetError(nRet));

		PRINT_RESULT(g_controller_eDisplayModeArray[nModeIdx], eGetMode, "mc_client_get_server_display_mode", "display mode return value is different than updated");
	}
	return 0;
}

/**
 * @testcase 					ITc_mc_client_get_server_display_rotation_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Gets the latest display rotation.
 * @scenario					Call mc_client_get_server_display_rotation
 * @apicovered					mc_client_get_server_display_rotation
 * @passcase					If mc_client_get_server_display_rotation returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_server_create
 * @postcondition				mc_server_destroy
 * */
 //& type: auto
//& purpose: Gets the latest display rotation.
int ITc_mc_client_get_server_display_rotation_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_display_rotation_e eGetRotation = 0;

	int nRotationSize = sizeof(g_controller_eDisplayRotationArray)/sizeof(g_controller_eDisplayRotationArray[0]);
	int nRotationIdx;

	for(nRotationIdx = 0; nRotationIdx < nRotationSize; nRotationIdx++)
	{
		nRet = mc_server_update_display_rotation(g_hMcServer, g_controller_eDisplayRotationArray[nRotationIdx]);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_display_rotation", MediaControllerGetError(nRet));

		nRet = mc_client_get_latest_server_info(g_hMcClient, &g_McServerName, &g_McServerState);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet));

		nRet = mc_client_get_server_display_rotation(g_hMcClient, g_McServerName, &eGetRotation);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_display_rotation", MediaControllerGetError(nRet));

		PRINT_RESULT(g_controller_eDisplayRotationArray[nRotationIdx], eGetRotation, "mc_client_get_server_display_rotation", "Updated and get display rotation is not matching");
	}
	return 0;
}

/**
 * @testcase 					ITc_mc_client_get_server_display_mode_ability_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Gets the supported display mode of the updated media controller server.
 * @scenario					Call mc_client_get_server_display_mode_ability
 * @apicovered					mc_client_get_server_display_mode_ability
 * @passcase					If mc_client_get_server_display_mode_ability returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_server_create
 * @postcondition				mc_server_destroy
 * */
 //& type: auto
//& purpose: Gets the supported display mode of the updated media controller server.
int ITc_mc_client_get_server_display_mode_ability_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	unsigned int uSetDisplayAbility = MC_DISPLAY_MODE_LETTER_BOX | MC_DISPLAY_MODE_ORIGIN_SIZE | MC_DISPLAY_MODE_FULL_SCREEN | MC_DISPLAY_MODE_CROPPED_FULL;
	unsigned int uGetDisplayAbility = 0;

	nRet = mc_server_set_display_mode_ability(g_hMcServer, uSetDisplayAbility, MC_ABILITY_SUPPORTED_YES);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_display_mode_ability", MediaControllerGetError(nRet));

	nRet = mc_client_get_latest_server_info(g_hMcClient, &g_McServerName, &g_McServerState);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet));

	nRet = mc_client_get_server_display_mode_ability(g_hMcClient, g_McServerName, &uGetDisplayAbility);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_display_mode_ability", MediaControllerGetError(nRet));

	if(ClientGetDisplayModeAbility(uGetDisplayAbility))
	{
		return 1;
	}

	return 0;
}

/**
 * @testcase 					ITc_mc_client_get_server_display_rotation_ability_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Gets the supported display rotation of the updated media controller server.
 * @scenario					Call mc_client_get_server_display_rotation_ability
 * @apicovered					mc_client_get_server_display_rotation_ability
 * @passcase					If mc_client_get_server_display_rotation_ability returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_server_create
 * @postcondition				mc_server_destroy
 * */
 //& type: auto
//& purpose: Gets the supported display rotation of the updated media controller server.
int ITc_mc_client_get_server_display_rotation_ability_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	unsigned int uSetSupportedRotations = MC_DISPLAY_ROTATION_NONE | MC_DISPLAY_ROTATION_90 | MC_DISPLAY_ROTATION_180 | MC_DISPLAY_ROTATION_270;
	unsigned int uGetSupportedRotations = 0;

	nRet = mc_server_set_display_rotation_ability(g_hMcServer, uSetSupportedRotations, MC_ABILITY_SUPPORTED_YES);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_display_rotation_ability", MediaControllerGetError(nRet));

	nRet = mc_client_get_latest_server_info(g_hMcClient, &g_McServerName, &g_McServerState);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet));

	nRet = mc_client_get_server_display_rotation_ability(g_hMcClient, g_McServerName, &uGetSupportedRotations);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_display_rotation_ability", MediaControllerGetError(nRet));

	if(ClientGetDisplayRotationAbility(uGetSupportedRotations))
	{
		return 1;
	}

	return 0;
}

/**
 * @testcase 					ITc_mc_client_send_subtitles_cmd_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Sends the subtitles command to server.
 * @scenario					Call mc_client_send_subtitles_cmd
 * @apicovered					mc_client_send_subtitles_cmd
 * @passcase					If mc_client_send_subtitles_cmd returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_server_create
 * @postcondition				mc_server_destroy
 * */
 //& type: auto
//& purpose: Sends the subtitles command to server.
int ITc_mc_client_send_subtitles_cmd_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_ability_e eAbilitySupport = MC_ABILITY_SUBTITLES;
	char *pszReqID = NULL;
	g_CallBackHit = false;

	nRet = mc_server_set_ability_support(g_hMcServer, eAbilitySupport, MC_ABILITY_SUPPORTED_YES);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_ability_support", MediaControllerGetError(nRet));

	nRet = mc_server_set_subtitles_cmd_received_cb(g_hMcServer, ServerEnableCmdReceivedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_subtitles_cmd_received_cb", MediaControllerGetError(nRet));

	nRet = mc_client_get_latest_server_info(g_hMcClient, &g_McServerName, &g_McServerState);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet));

	nRet = mc_client_send_subtitles_cmd(g_hMcClient, g_McServerName, true, &pszReqID);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_subtitles_cmd", MediaControllerGetError(nRet));
	CHECK_HANDLE(pszReqID, "mc_client_send_subtitles_cmd");

	FREE_MEMORY(pszReqID);

	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "mc_client_send_subtitles_cmd", "CallBack Not Invoked");

	return 0;
}

/**
 * @testcase 					ITc_mc_client_send_360_mode_cmd_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Sends the 360 mode command to server.
 * @scenario					Call mc_client_send_360_mode_cmd
 * @apicovered					mc_client_send_360_mode_cmd
 * @passcase					If mc_client_send_360_mode_cmd returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_server_create
 * @postcondition				mc_server_destroy
 * */
 //& type: auto
//& purpose: Sends the 360 mode command to server.
int ITc_mc_client_send_360_mode_cmd_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_ability_e eAbilitySupport = MC_ABILITY_360_MODE;
	char *pszReqID = NULL;
	g_CallBackHit = false;

	nRet = mc_server_set_ability_support(g_hMcServer, eAbilitySupport, MC_ABILITY_SUPPORTED_YES);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_ability_support", MediaControllerGetError(nRet));

	nRet = mc_server_set_360_mode_cmd_received_cb(g_hMcServer, ServerEnableCmdReceivedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_360_mode_cmd_received_cb", MediaControllerGetError(nRet));

	nRet = mc_client_get_latest_server_info(g_hMcClient, &g_McServerName, &g_McServerState);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet));

	nRet = mc_client_send_360_mode_cmd(g_hMcClient, g_McServerName, true, &pszReqID);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_360_mode_cmd", MediaControllerGetError(nRet));
	FREE_MEMORY(pszReqID);

	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "mc_client_send_360_mode_cmd", "CallBack Not Invoked");

	return 0;
}

/**
 * @testcase 					ITc_mc_client_send_display_mode_cmd_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Sends the display mode command to server.
 * @scenario					Call mc_client_send_display_mode_cmd
 * @apicovered					mc_client_send_display_mode_cmd
 * @passcase					If mc_client_send_display_mode_cmd returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_server_create
 * @postcondition				mc_server_destroy
 * */
 //& type: auto
//& purpose: Sends the display mode command to server.
int ITc_mc_client_send_display_mode_cmd_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	unsigned int unSetDisplayAbility = MC_DISPLAY_MODE_LETTER_BOX | MC_DISPLAY_MODE_ORIGIN_SIZE | MC_DISPLAY_MODE_FULL_SCREEN | MC_DISPLAY_MODE_CROPPED_FULL;
	char *pszReqID = NULL;
	g_CallBackHit = false;

	nRet = mc_server_set_display_mode_ability(g_hMcServer, unSetDisplayAbility, MC_ABILITY_SUPPORTED_YES);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_display_mode_ability", MediaControllerGetError(nRet));

	nRet = mc_server_set_display_mode_cmd_received_cb(g_hMcServer, ServerDisplayModeCmdReceivedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_display_mode_cmd_received_cb", MediaControllerGetError(nRet));

	nRet = mc_client_get_latest_server_info(g_hMcClient, &g_McServerName, &g_McServerState);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet));

	int nModeSize = sizeof(g_controller_eDisplayModeArray)/sizeof(g_controller_eDisplayModeArray[0]);

	for(g_nModeIdx = 0; g_nModeIdx < nModeSize; g_nModeIdx++)
	{
		g_CallBackHit = false;
		nRet = mc_client_send_display_mode_cmd(g_hMcClient, g_McServerName, g_controller_eDisplayModeArray[g_nModeIdx], &pszReqID);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_display_mode_cmd", MediaControllerGetError(nRet));

		CHECK_HANDLE(pszReqID, "mc_client_send_display_mode_cmd");
		FREE_MEMORY(pszReqID);

		IterateGmainLoop();
		PRINT_RESULT(true, g_CallBackHit, "mc_client_send_display_mode_cmd", "CallBack Not Invoked");
	}
	return 0;
}

/**
 * @testcase 					ITc_mc_client_send_display_rotation_cmd_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Sends the display rotation command to server.
 * @scenario					Call mc_client_send_display_rotation_cmd
 * @apicovered					mc_client_send_display_rotation_cmd
 * @passcase					If mc_client_send_display_rotation_cmd returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_server_create
 * @postcondition				mc_server_destroy
 * */
 //& type: auto
//& purpose: Sends the display rotation command to server.
int ITc_mc_client_send_display_rotation_cmd_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	unsigned int uSetSupportedRotations = MC_DISPLAY_ROTATION_NONE | MC_DISPLAY_ROTATION_90 | MC_DISPLAY_ROTATION_180 | MC_DISPLAY_ROTATION_270;
	char *pszReqID = NULL;
	g_CallBackHit = false;
	mc_display_rotation_e eSetDisplayRotation = MC_DISPLAY_ROTATION_270; // MC_DISPLAY_ROTATION_NONE, MC_DISPLAY_ROTATION_90 and MC_DISPLAY_ROTATION_180 are not supported

	nRet = mc_server_set_display_rotation_ability(g_hMcServer, uSetSupportedRotations, MC_ABILITY_SUPPORTED_YES);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_display_rotation_ability", MediaControllerGetError(nRet));

	nRet = mc_server_set_display_rotation_cmd_received_cb(g_hMcServer, ServerDisplayRotationCmdReceivedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_display_rotation_cmd_received_cb", MediaControllerGetError(nRet));

	nRet = mc_client_get_latest_server_info(g_hMcClient, &g_McServerName, &g_McServerState);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet));

	nRet = mc_client_send_display_rotation_cmd(g_hMcClient, g_McServerName, eSetDisplayRotation, &pszReqID);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_display_rotation_cmd", MediaControllerGetError(nRet));
	FREE_MEMORY(pszReqID);

	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "mc_client_send_display_rotation_cmd", "CallBack Not Invoked");

	return 0;
}
/** @} */
/** @} */
