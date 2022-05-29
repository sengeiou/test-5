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

void *g_UserData = NULL;
static char *g_PlaylistName = "test_playlist";
static gboolean g_ResultPlaylistCb = false;
static char *g_McServerName = NULL;
static mc_server_state_e g_McServerState = MC_SERVER_STATE_NONE;

static char *g_McTestMetadata[] = {
        "media_title",
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

mc_playback_action_e g_ePlaybackActionArr[] = { MC_PLAYBACK_ACTION_PLAY,
						MC_PLAYBACK_ACTION_PAUSE,
						MC_PLAYBACK_ACTION_STOP,
						MC_PLAYBACK_ACTION_NEXT,
						MC_PLAYBACK_ACTION_PREV,
						MC_PLAYBACK_ACTION_FAST_FORWARD,
						MC_PLAYBACK_ACTION_REWIND,
						MC_PLAYBACK_ACTION_TOGGLE_PLAY_PAUSE};

mc_ability_support_e g_eAbilitySupportArray[] = {MC_ABILITY_SUPPORTED_YES,
						MC_ABILITY_SUPPORTED_NO};

mc_display_mode_e g_server_eDisplayModeArray[] =
{
	MC_DISPLAY_MODE_LETTER_BOX,	/**< Letter box */
	MC_DISPLAY_MODE_ORIGIN_SIZE,	/**< Origin size */
	MC_DISPLAY_MODE_FULL_SCREEN,	/**< Full-screen */
	MC_DISPLAY_MODE_CROPPED_FULL	/**< Cropped full-screen */
};

//& set: MediaController

/** @addtogroup itc-media-controller-server
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_media_controller_server_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_controller_server_startup(void)
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
 * @function 		ITs_media_controller_server_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_controller_server_cleanup(void)
{
	if(g_hMcClient != NULL)
		mc_client_destroy(g_hMcClient);
	if(g_hMcServer != NULL)
		mc_server_destroy(g_hMcServer);
	if(g_hMcSearch != NULL)
		mc_search_destroy(g_hMcSearch);

	return;
}

/*
 * @function 		ServerPositionCommandReceivedCallBack
 * @description	 	Callback Function
 * @parameter		const char* client_name, const char *request_id, unsigned long long position, void *user_data
 * @return 			NA
 */
void ServerPositionCommandReceivedCallBack(const char* client_name, const char *request_id, unsigned long long position, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ServerPositionCommandReceivedCallBack");
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
}

/*
 * @function 		ServerShufleModeCommandReceivedCallBack
 * @description	 	Callback Function
 * @parameter		const char* client_name, const char *request_id, mc_shuffle_mode_e shuffle_mode, void *user_data
 * @return 			NA
 */
void ServerShufleModeCommandReceivedCallBack(const char* client_name, const char *request_id, mc_shuffle_mode_e shuffle_mode, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ServerShufleModeCommandReceivedCallBack");
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
}

/*
 * @function 		ServerRepeateModeCommandReceivedCallBack
 * @description	 	Callback Function
 * @parameter		const char* client_name, const char *request_id, mc_repeat_mode_e repeat_mode, void *user_data
 * @return 			NA
 */
void ServerRepeateModeCommandReceivedCallBack(const char* client_name, const char *request_id, mc_repeat_mode_e repeat_mode, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ServerRepeateModeCommandReceivedCallBack");
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
}

/*
 * @function 		ServerPlaylistCommandReceivedCallback
 * @description	 	Callback Function
 * @parameter		const char* client_name, const char *request_id, const char *playlist_name, const char *index, mc_playback_action_e action, unsigned long long position, void *user_data
 * @return 			NA
 */
void ServerPlaylistCommandReceivedCallback(const char* client_name, const char *request_id, const char *playlist_name, const char *index, mc_playback_action_e action, unsigned long long position, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ServerPlaylistCommandReceivedCallback");
#endif

	strncpy(g_szClientName, client_name, strlen(client_name)+1);
	g_CallBackHit = true;
	QuitGmainLoop();
}

/*
 * @function 		ServerCustomCommandReceivedCallback
 * @description	 	Callback Function
 * @parameter		const char client_name, const char *request_id, const char *command, bundle *data, void *user_data
 * @return 			NA
 */
void ServerCustomCommandReceivedCallback(const char client_name, const char *request_id, const char *command, bundle *data, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ServerCustomCommandReceivedCallback");
#endif
	g_CallBackHit = true;
	QuitGmainLoop();
}

/*
 * @function 		ServerForeachPlaylistCommandReceivedCallback
 * @description	 	Callback Function
 * @parameter		const char *app_id, mc_playlist_cb callback, void *user_data
 * @return 			NA
 */
void ServerForeachPlaylistCommandReceivedCallback(const char *app_id, mc_playlist_cb callback, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ServerForeachPlaylistCommandReceivedCallback");
#endif
	g_CallBackHit = true;
	QuitGmainLoop();
}

/*
 * @function 			ServerMcRegisterPlaylist
 * @description	 	ServerMcRegisterPlaylist creates and add items into playlist.
 * @parameter		mc_playlist_h *playlist
 * @return 			correct error code
 */
int ServerMcRegisterPlaylist(mc_playlist_h *hPlaylistReg)
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
			nRet = mc_server_add_item_to_playlist(g_hMcServer, hPlaylist, "1", StringIndex, g_PlaylistArray[StringIndex]);
			PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_add_item_to_playlist", MediaControllerGetError(nRet),mc_playlist_destroy(hPlaylist));
		}

		nRet = mc_server_update_playlist_done(g_hMcServer, hPlaylist);
		PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_playlist_done", MediaControllerGetError(nRet),mc_playlist_destroy(hPlaylist));

		*hPlaylistReg = hPlaylist;

		return MEDIA_CONTROLLER_ERROR_NONE;
}

/*
 * @function 			ServerPlaylistItemCallback
 * @description	 	ServerPlaylistItemCallback  is invoked when playlist item is updated
 * @parameter		const char *index, mc_metadata_h meta, void *user_data
 * @return 		true/false on success and failure
 */
bool ServerPlaylistItemCallback(const char *pIndex, mc_metadata_h hMetaData, void *pUserData)
{
	FPRINTF("%d:%s invoked\n", __LINE__, __FUNCTION__);

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	char *pszValue = NULL;
	char *pszIndex = "1";
	char *pszTitle = "title_1";

	if (pIndex != NULL) {
		if(strncmp(pIndex, pszIndex,strlen(pszIndex))) {
			FPRINTF("[%d:%s] wrong playlist index [%s]\n", __LINE__, __FUNCTION__, pIndex);
			QuitGmainLoop();
			return false;
		}

		nRet = mc_metadata_get(hMetaData, MC_META_MEDIA_TITLE, &pszValue);
		if (nRet != MEDIA_CONTROLLER_ERROR_NONE){
			FPRINTF("[%d:%s] fail mc_metadata_get [%d]\n", __LINE__, __FUNCTION__, nRet);
			FREE_MEMORY(pszValue);
			QuitGmainLoop();
			return false;
		}

		if (pszValue != NULL) {
			if(strncmp(pszValue, pszTitle,strlen(pszTitle) ) == 0) {
				FREE_MEMORY(pszValue);
				g_ResultPlaylistCb = true;
				QuitGmainLoop();
				return true;
			}
			else{
				FPRINTF("[%d:%s] incorrect title  pszValue [%s]\n", __LINE__, __FUNCTION__, pszValue);
				FREE_MEMORY(pszValue);
			}
		}
		else{
			FPRINTF("[%d:%s] pszValue returned is null\n", __LINE__, __FUNCTION__);
		}

	}
	else {
		FPRINTF("[%d:%s] pIndex is null\n", __LINE__, __FUNCTION__);
	}

	QuitGmainLoop();
	return false;
}

/*
 * @function		ServerAttributeUpdatedCallBack
 * @description		ServerAttributeUpdatedCallBack is invoked when subtitles or 360 mode is enabled
 * @parameter		const char *pszServerName, bool bIsEnabled, void *pszData
 * @return		N/A
 */
void ServerAttributeUpdatedCallBack(const char *pszServerName, bool bIsEnabled, void *pszData)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ServerPlaylistCommandReceivedCallback");
#endif
	g_CallBackHit = true;

	if (!bIsEnabled) {
		FPRINTF("[%d:%s] wrong attribute status [%d] [%d]\\n", __LINE__, __FUNCTION__, bIsEnabled, false);
	}

	QuitGmainLoop();
}

/*
 * @function		ServerDisplayModeUpdatedCallBack
 * @description		ServerDisplayModeUpdatedCallBack is invoked when display mode is updated
 * @parameter		const char *pszServerName, mc_display_mode_e eDisplayMode, void *pszData
 * @return		N/A
 */
void ServerDisplayModeUpdatedCallBack(const char *pszServerName, mc_display_mode_e eDisplayMode, void *pszData)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ServerPlaylistCommandReceivedCallback");
#endif
	g_CallBackHit = true;

	if (eDisplayMode != g_server_eDisplayModeArray[g_nModeIdx])
	{
		FPRINTF("[%d:%s] wrong display mode [%d] expected display mode is[%d]\\n", __LINE__, __FUNCTION__, eDisplayMode, g_server_eDisplayModeArray[g_nModeIdx]);
	}
	QuitGmainLoop();
}

/*
 * @function		ServerDisplayRotationUpdatedCallBack
 * @description		ServerDisplayRotationUpdatedCallBack is invoked when display mode is updated
 * @parameter		const char *pszServerName, mc_display_rotation_e eDisplayRotation, void *pszData
 * @return		N/A
 */
void ServerDisplayRotationUpdatedCallBack(const char *pszServerName, mc_display_rotation_e eDisplayRotation, void *pszData)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] ServerDisplayRotationUpdatedCallBack Callback Invoked\\n", __LINE__, API_NAMESPACE);
#endif

	g_CallBackHit = true;
	if (eDisplayRotation != MC_DISPLAY_ROTATION_270)
	{
		FPRINTF("[%d:%s] wrong display rotation [%d] expected display rotation is [%d]\\n", __LINE__, __FUNCTION__, eDisplayRotation, MC_DISPLAY_ROTATION_270);
	}
	QuitGmainLoop();
}

/**
 * @function 		DisplayModeCmdReceivedCallBack
 * @description	 	Callback Function
 * @parameter		const char *pszClientName, const char *pszReqID, mc_display_mode_e eDisplayMode, void *pszData
 * @return 		NA
 */
void DisplayModeCmdReceivedCallBack(const char *pszClientName, const char *pszReqID, mc_display_mode_e eDisplayMode, void *pszData)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DisplayModeCmdReceivedCallBack Callback Invoked\\n", __LINE__, API_NAMESPACE);
#endif

	g_CallBackHit = true;

	if (eDisplayMode != g_server_eDisplayModeArray[g_nModeIdx]){
		FPRINTF("[%d:%s] wrong display mode [%d] expected display mode is [%d]\\n", __LINE__, __FUNCTION__, eDisplayMode, g_server_eDisplayModeArray[g_nModeIdx]);
	}
	QuitGmainLoop();
}

/**
 * @function 		DisplayRotationCmdReceivedCallBack
 * @description	 	Callback Function
 * @parameter		const char *pszClientName, const char *pszReqID, mc_display_mode_e eDisplayMode, void *pszData
 * @return 		NA
 */
void DisplayRotationCmdReceivedCallBack(const char *pszClientName, const char *pszReqID, mc_display_rotation_e eDisplayRotation, void *pszData)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DisplayRotationCmdReceivedCallBack Callback Invoked\\n", __LINE__, API_NAMESPACE);
#endif

	g_CallBackHit = true;

	if (eDisplayRotation != MC_DISPLAY_ROTATION_270) {
		FPRINTF("[%d:%s] wrong display rotation [%d] expected display rotation is [%d]\\n", __LINE__, __FUNCTION__, eDisplayRotation, MC_DISPLAY_ROTATION_270);
	}
	QuitGmainLoop();
}

/**
 * @function 		ServerAbilitySupportedItemsUpdatedCallBack
 * @description	 	Callback Function
 * @parameter		const char *pszServerName, unsigned int nSupportedItems, void *pszData
 * @return 		NA
 */
void ServerAbilitySupportedItemsUpdatedCallBack(const char *pszServerName, unsigned int nSupportedItems, void *pszData)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] ServerAbilitySupportedItemsUpdatedCallBack Callback Invoked\\n", __LINE__, API_NAMESPACE);
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
}

/** @addtogroup itc-media-controller-testcases
*  @brief 		Integration testcases for module media-controller
*  @ingroup 	itc-media-controller
*  @{
*/

/**
 * @testcase 				ITc_mc_server_create_destroy_p
 * @author            		SRID(abhishek1.g)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test mc_server_create and mc_server_destroy
 * @scenario				Call mc_server_create, mc_server_destroy
 * @apicovered				mc_server_create, mc_server_destroy
 * @passcase				If mc_server_create and mc_server_destroy returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_server_create and mc_server_destroy
int ITc_mc_server_create_destroy_p(void)
{
    START_TEST;

	int nRet = -1;

	nRet = mc_server_destroy(g_hMcServer);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_destroy", MediaControllerGetError(nRet));

	nRet = mc_server_create(&g_hMcServer);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_create", MediaControllerGetError(nRet));
	CHECK_HANDLE(g_hMcServer, "mc_server_create");

	nRet = mc_server_destroy(g_hMcServer);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_destroy", MediaControllerGetError(nRet));

	nRet = mc_server_create(&g_hMcServer);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_create", MediaControllerGetError(nRet));
	CHECK_HANDLE(g_hMcServer, "mc_server_create");

    return 0;
}

/**
 * @testcase 				ITc_mc_server_set_playback_state_p
 * @author            		SRID(abhishek1.g)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test mc_server_set_playback_state
 * @scenario				Call mc_server_set_playback_state
 * @apicovered				mc_server_set_playback_state
 * @passcase				If mc_server_set_playback_state returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_server_set_playback_state
int ITc_mc_server_set_playback_state_p(void)
{
	START_TEST;

	int nRet = -1;

	nRet = mc_server_set_playback_state(g_hMcServer, MC_PLAYBACK_STATE_PLAYING);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_playback_state", MediaControllerGetError(nRet));

    return 0;
}

/**
 * @testcase 				ITc_mc_server_set_playback_position_p
 * @author            		SRID(abhishek1.g)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test mc_server_set_playback_position
 * @scenario				Call mc_server_set_playback_position
 * @apicovered				mc_server_set_playback_position
 * @passcase				If mc_server_set_playback_position returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_server_set_playback_position
int ITc_mc_server_set_playback_position_p(void)
{
	START_TEST;

	int nRet = -1;

	nRet = mc_server_set_playback_position(g_hMcServer, PLAYBACKPOSITION);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_playback_position", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mc_server_set_metadata_p
 * @author            		SRID(abhishek1.g)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test mc_server_set_metadata
 * @scenario				Call mc_server_set_metadata
 * @apicovered				mc_server_set_metadata
 * @passcase				If mc_server_set_metadata returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_server_set_metadata
int ITc_mc_server_set_metadata_p(void)
{
	START_TEST;

	int nRet = -1;

	nRet = mc_server_set_metadata(g_hMcServer, MC_META_MEDIA_TITLE, "media_title");
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_metadata", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mc_server_update_playback_info_p
 * @author            		SRID(abhishek1.g)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test mc_server_update_playback_info
 * @scenario				Call mc_server_update_playback_info
 * @apicovered				mc_server_update_playback_info
 * @passcase				If mc_server_update_playback_info returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_server_update_playback_info
int ITc_mc_server_update_playback_info_p(void)
{
	START_TEST;

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
 * @testcase 				ITc_mc_server_update_metadata_p
 * @author            		SRID(abhishek1.g)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test mc_server_update_metadata
 * @scenario				Call mc_server_update_metadata
 * @apicovered				mc_server_update_metadata
 * @passcase				If mc_server_update_metadata returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_server_update_metadata
int ITc_mc_server_update_metadata_p(void)
{
	START_TEST;

	int nRet = -1;

	nRet = mc_server_set_metadata(g_hMcServer, MC_META_MEDIA_PICTURE, "media_picture_path");
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_metadata", MediaControllerGetError(nRet));

	nRet = mc_server_update_metadata(g_hMcServer);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_metadata", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mc_server_update_shuffle_mode_p
 * @author            		SRID(abhishek1.g)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test mc_server_update_shuffle_mode
 * @scenario				Call mc_server_update_shuffle_mode
 * @apicovered				mc_server_update_shuffle_mode
 * @passcase				If mc_server_update_shuffle_mode returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_server_update_shuffle_mode
int ITc_mc_server_update_shuffle_mode_p(void)
{
	START_TEST;

	int nRet = -1;

	nRet = mc_server_update_shuffle_mode(g_hMcServer, MC_SHUFFLE_MODE_ON);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_shuffle_mode", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mc_server_update_repeat_mode_p
 * @author            		SRID(abhishek1.g)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test mc_server_update_repeat_mode
 * @scenario				Call mc_server_update_repeat_mode
 * @apicovered				mc_server_update_repeat_mode
 * @passcase				If mc_server_update_repeat_mode returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_server_update_repeat_mode
int ITc_mc_server_update_repeat_mode_p(void)
{
	START_TEST;

	int nRet = -1;

	nRet = mc_server_update_repeat_mode(g_hMcServer, MC_REPEAT_MODE_ON);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_repeat_mode", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mc_server_set_unset_repeat_mode_cmd_received_cb_p
 * @author            		SRID(priya.kohli)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			4.0
 * @description				Sets and unsets the callback for receiving repeat mode command from client.
 * @scenario				Call mc_server_set_repeat_mode_cmd_received_cb, mc_server_unset_repeat_mode_cmd_received_cb
 * @apicovered				mc_server_set_repeat_mode_cmd_received_cb,mc_server_unset_repeat_mode_cmd_received_cb
 * @passcase				If mc_server_set_repeat_mode_cmd_received_cb, mc_server_unset_repeat_mode_cmd_received_cb returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			Create a media controller server handle by calling mc_server_create().
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To set and unset the callback for receiving repeat mode command from client.
int ITc_mc_server_set_unset_repeat_mode_cmd_received_cb_p(void)
{
	START_TEST;

	int nRet = -1;
	g_CallBackHit = false;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = mc_server_set_repeat_mode_cmd_received_cb(g_hMcServer, ServerRepeateModeCommandReceivedCallBack, g_UserData);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_repeat_mode_cmd_received_cb", MediaControllerGetError(nRet));

	nRet = mc_client_send_repeat_mode_cmd(g_hMcClient, g_szServerName, MC_REPEAT_MODE_ON, &g_request_id);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_repeat_mode_cmd", MediaControllerGetError(nRet),mc_server_unset_repeat_mode_cmd_received_cb(g_hMcServer));

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "ServerRepeateModeCommandReceivedCallBack", "CallBack Not Invoked", mc_server_unset_playback_position_cmd_received_cb(g_hMcServer));

	nRet = mc_server_unset_repeat_mode_cmd_received_cb(g_hMcServer);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_unset_repeat_mode_cmd_received_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mc_server_set_unset_shufle_mode_cmd_received_cb_p
 * @author            		SRID(priya.kohli)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			4.0
 * @description				Sets and unsets the callback for receiving shuffle mode command from client.
 * @scenario				Call mc_server_set_shuffle_mode_cmd_received_cb, mc_server_unset_shuffle_mode_cmd_received_cb
 * @apicovered				mc_server_set_shuffle_mode_cmd_received_cb,mc_server_unset_shuffle_mode_cmd_received_cb
 * @passcase				If mc_server_set_shuffle_mode_cmd_received_cb, mc_server_unset_shuffle_mode_cmd_received_cb returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			Create a media controller server handle by calling mc_server_create().
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To set and unset the callback for receiving shuffle mode command from client.
int ITc_mc_server_set_unset_shufle_mode_cmd_received_cb_p(void)
{
	START_TEST;

	int nRet = -1;
	g_CallBackHit = false;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = mc_server_set_shuffle_mode_cmd_received_cb(g_hMcServer, ServerShufleModeCommandReceivedCallBack, g_UserData);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_shuffle_mode_cmd_received_cb", MediaControllerGetError(nRet));

	nRet = mc_client_send_shuffle_mode_cmd(g_hMcClient, g_szServerName, MC_SHUFFLE_MODE_ON, &g_request_id);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_shuffle_mode_cmd", MediaControllerGetError(nRet),mc_server_unset_shuffle_mode_cmd_received_cb(g_hMcServer));

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "ServerShufleModeCommandReceivedCallBack", "CallBack Not Invoked", mc_server_unset_shuffle_mode_cmd_received_cb(g_hMcServer));

	nRet = mc_server_unset_shuffle_mode_cmd_received_cb(g_hMcServer);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_unset_shuffle_mode_cmd_received_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mc_server_set_unset_playback_position_cmd_received_cb_p
 * @author            		SRID(priya.kohli)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			4.0
 * @description				Sets and unsets the callback for receiving playback position command from client.
 * @scenario				Call mc_server_set_playback_position_cmd_received_cb
 * @apicovered				mc_server_set_playback_position_cmd_received_cb, mc_server_set_playback_position, mc_server_unset_playback_position_cmd_received_cb
 * @passcase				If mc_server_set_playback_position_cmd_received_cb , mc_server_unset_playback_position_cmd_received_cbreturns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			Create a media controller server handle by calling mc_server_create().
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To set and unset the callback for receiving playback position command from client.
int ITc_mc_server_set_unset_playback_position_cmd_received_cb_p(void)
{
	START_TEST;

	int nRet = -1;
	g_CallBackHit = false;
	unsigned long long ullSetPosition = 15;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = mc_server_set_playback_position_cmd_received_cb(g_hMcServer, ServerPositionCommandReceivedCallBack, g_UserData);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_playback_position_cmd_received_cb", MediaControllerGetError(nRet));

	nRet = mc_client_send_playback_position_cmd(g_hMcClient, g_szServerName, ullSetPosition, &g_request_id);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_playback_position_cmd", MediaControllerGetError(nRet), mc_server_unset_playback_position_cmd_received_cb(g_hMcServer));

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "ServerPositionCommandReceivedCallBack", "CallBack Not Invoked", mc_server_unset_playback_position_cmd_received_cb(g_hMcServer));

	nRet = mc_server_unset_playback_position_cmd_received_cb(g_hMcServer);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_unset_playback_position_cmd_received_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mc_server_set_unset_playlist_cmd_received_cb_p
 * @author            		SRID(priya.kohli)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			4.0
 * @description				Sets and unsets the callback for receiving playlist command from client.
 * @scenario				Call mc_server_set_playlist_cmd_received_cb,mc_server_unset_playlist_cmd_received_cb
 * @apicovered				mc_server_set_playlist_cmd_received_cb,mc_server_unset_playlist_cmd_received_cb
 * @passcase				If mc_server_set_playlist_cmd_received_cb,mc_server_unset_playlist_cmd_received_cb returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To set and unset the callback for receiving playlist command from client.
int ITc_mc_server_set_unset_playlist_cmd_received_cb_p(void)
{
	START_TEST;

	int nRet = -1;
	g_CallBackHit = false;
	const char *pszIndex="3";
	unsigned long long ullPosition = 0;

	nRet = mc_server_set_playlist_cmd_received_cb(g_hMcServer, ServerPlaylistCommandReceivedCallback,g_UserData);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_playlist_cmd_received_cb", MediaControllerGetError(nRet));

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = mc_client_send_playlist_cmd(g_hMcClient, g_szServerName, g_szPlaylistName, pszIndex, MC_PLAYBACK_ACTION_PLAY, ullPosition, &g_request_id);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_playlist_cmd", MediaControllerGetError(nRet),mc_server_unset_playlist_cmd_received_cb(g_hMcServer));

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "ServerPlaylistCommandReceivedCallback", "CallBack Not Invoked", mc_server_unset_playlist_cmd_received_cb(g_hMcServer));

	nRet = mc_server_unset_playlist_cmd_received_cb(g_hMcServer);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_unset_playlist_cmd_received_cb", MediaControllerGetError(nRet));

    return 0;
}

/**
 * @testcase 				ITc_mc_server_set_unset_custom_cmd_received_cb
 * @author            		SRID(priya.kohli)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			4.0
 * @description				Sets and Unsets the callback for receiving custom command from client.
 * @scenario				Call mc_server_set_custom_cmd_received_cb, mc_server_unset_custom_cmd_received_cb
 * @apicovered				mc_server_set_custom_cmd_received_cb, mc_client_send_custom_cmd, mc_server_unset_custom_cmd_received_cb
 * @passcase				If mc_server_set_custom_cmd_received_cb, mc_client_send_custom_cmd, mc_server_unset_custom_cmd_received_cb returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To set and unset the callback for receiving custom command from client.
int ITc_mc_server_set_unset_custom_cmd_received_cb_p(void)
{
	START_TEST;

	int nRet = -1;
	g_CallBackHit = false;
	bundle *bundle_data = NULL;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = mc_server_set_custom_cmd_received_cb(g_hMcServer, ServerCustomCommandReceivedCallback, g_UserData);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_custom_cmd_received_cb", MediaControllerGetError(nRet));

	nRet = mc_client_send_custom_cmd(g_hMcClient, g_szServerName, TESTCOMMAND, bundle_data, &g_request_id);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_custom_cmd", MediaControllerGetError(nRet), mc_server_unset_custom_cmd_received_cb(g_hMcServer));

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "ServerCustomCommandReceivedCallback", "CallBack Not Invoked", mc_server_unset_custom_cmd_received_cb(g_hMcServer));

	nRet = mc_server_unset_custom_cmd_received_cb(g_hMcServer);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_unset_custom_cmd_received_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mc_server_foreach_client_p
 * @author            			SRID(samuel.peter)
 * @reviewer         			SRID(manoj.g2)
 * @type 				auto
 * @since_tizen 			4.0
 * @description				Enables callback for each client
 * @scenario				Call mc_server_foreach_client
 * @apicovered				mc_server_foreach_client
 * @passcase				If mc_server_foreach_client returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To enable the callback for each client.
int ITc_mc_server_foreach_client_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	g_CallBackHit = false;

	nRet = mc_server_foreach_client(g_hMcServer, McActivatedClientCb, NULL);
	PRINT_RESULT(nRet, MEDIA_CONTROLLER_ERROR_NONE, "mc_server_foreach_client", MediaControllerGetError(nRet));

	PRINT_RESULT(g_CallBackHit, true, "mc_server_foreach_client", "false");

	return 0;
}

/**
 * @testcase 				ITc_mc_server_set_unset_cb_send_custom_event
 * @author            			SRID(samuel.peter)
 * @reviewer         			SRID(manoj.g2)
 * @type 				auto
 * @since_tizen 			4.0
 * @description				Sets and unsets the callback for custom events, and checks whether the callback is hit by sending an event.
 * @scenario				Call mc_server_set_event_reply_received_cb, mc_server_send_custom_event and then mc_server_unset_event_reply_received_cb
 * @apicovered				mc_server_set_event_reply_received_cb, mc_server_foreach_client, mc_server_send_custom_event, mc_server_unset_event_reply_received_cb
 * @passcase				If mc_server_set_event_reply_received_cb, mc_server_foreach_client, mc_server_send_custom_event, mc_server_unset_event_reply_received_cb returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To set and unset the callback for receiving custom command from media controller server.
int ITc_mc_server_set_unset_cb_send_custom_event_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	char *pszEvent = "test";
	char *pClientName = NULL;
	g_CallBackHit = false;

	nRet = mc_server_set_event_reply_received_cb(g_hMcServer, EventReceivedCallback, NULL);
	PRINT_RESULT(nRet, MEDIA_CONTROLLER_ERROR_NONE, "mc_server_set_event_reply_received_cb", MediaControllerGetError(nRet));

	nRet = mc_server_foreach_client(g_hMcServer, McActivatedClientCb, &pClientName);
	PRINT_RESULT_CLEANUP(nRet, MEDIA_CONTROLLER_ERROR_NONE, "mc_server_foreach_client", MediaControllerGetError(nRet), mc_server_unset_event_reply_received_cb(g_hMcServer));
	CHECK_HANDLE_CLEANUP(pClientName, "mc_server_foreach_client", mc_server_unset_event_reply_received_cb(g_hMcServer));

	nRet = mc_server_send_custom_event(g_hMcServer, pClientName, pszEvent, NULL, NULL);
	PRINT_RESULT_CLEANUP(nRet, MEDIA_CONTROLLER_ERROR_NONE, "mc_server_send_custom_event", MediaControllerGetError(nRet), FREE_MEMORY(pClientName); mc_server_unset_event_reply_received_cb(g_hMcServer));
	IterateGmainLoop();

	PRINT_RESULT_CLEANUP(g_CallBackHit, true, "mc_server_send_custom_event", "false", FREE_MEMORY(pClientName); mc_server_unset_event_reply_received_cb(g_hMcServer));

	nRet = mc_server_unset_event_reply_received_cb(g_hMcServer);
	PRINT_RESULT_CLEANUP(nRet, MEDIA_CONTROLLER_ERROR_NONE, "mc_server_unset_event_reply_received_cb", MediaControllerGetError(nRet), FREE_MEMORY(pClientName));

	FREE_MEMORY(pClientName);

	return 0;
}
 /**
 * @testcase 					ITc_mc_server_create_destroy_playlist_p
 * @author					SRID(bipin.k)
 * @reviewer					SRID(manoj.g2)
 * @type 						auto
 * @since_tizen 				4.0
 * @description				mc_server_create_playlist  creates a new playlist and then it is destroyed
 * @scenario					Call mc_server_create_playlist and mc_playlist_destroy
 * @apicovered				mc_server_create_playlist,mc_playlist_destroy
 * @passcase					If mc_server_create_playlist,mc_playlist_destroy  returns success error code
 * @failcase					If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose:  To destroy created playlist

int ITc_mc_server_create_destroy_playlist_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h hPlaylist = NULL;

	nRet = mc_server_create_playlist(g_hMcServer, g_PlaylistName, &hPlaylist);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_create_playlist", MediaControllerGetError(nRet));
	CHECK_HANDLE(hPlaylist, "mc_server_create_playlist");

	nRet = mc_playlist_destroy(hPlaylist);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_destroy", MediaControllerGetError(nRet));

	return 0;
}

 /**
 * @testcase 					ITc_mc_server_create_update_add_delete_playlist_p
 * @author					SRID(bipin.k)
 * @reviewer					SRID(manoj.g2)
 * @type 						auto
 * @since_tizen 				4.0
 * @description				ITc_mc_server_create_update_add_delete_playlist_p to create ,update ,add  and delete  item to playlist.
 * @scenario					Call ServerMcRegisterPlaylist
 * @apicovered				mc_server_create_playlist,mc_server_create_playlist,mc_server_delete_playlist,mc_playlist_destroy
 * @passcase					If create ,delete ,update and add is items into playlist is successful.
 * @failcase					If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To create ,update ,add  and  delete item to playlist.

int ITc_mc_server_create_update_add_delete_playlist_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h hPlaylist = NULL;

	nRet = ServerMcRegisterPlaylist(&hPlaylist);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "ServerMcRegisterPlaylist", MediaControllerGetError(nRet));
	CHECK_HANDLE(hPlaylist, "ServerMcRegisterPlaylist");

	nRet = mc_server_delete_playlist(g_hMcServer, hPlaylist);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_delete_playlist", MediaControllerGetError(nRet),mc_playlist_destroy(hPlaylist));

	nRet = mc_playlist_destroy(hPlaylist);
	PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_destroy", MediaControllerGetError(nRet));

	return 0;
}

 /**
 * @testcase 					ITc_mc_playlist_foreach_item_p
 * @author					SRID(bipin.k)
 * @reviewer					SRID(manoj.g2)
 * @type 						auto
 * @since_tizen 				4.0
 * @description				Positive test case of mc_playlist_foreach_item
 * @scenario					Callback invoked for each playlist item
 * @apicovered				mc_playlist_foreach_item,ServerMcRegisterPlaylist,mc_playlist_destroy.
 * @passcase					If ServerMcRegisterPlaylist,mc_playlist_foreach_item is successful.
 * @failcase					If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To see wether playlist item callback is being invoked or not.
int ITc_mc_playlist_foreach_item_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h hPlaylist = NULL;
	g_ResultPlaylistCb = false;

	nRet = ServerMcRegisterPlaylist(&hPlaylist);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "ServerMcRegisterPlaylist", MediaControllerGetError(nRet));
	CHECK_HANDLE(hPlaylist, "ServerMcRegisterPlaylist");

	nRet = mc_playlist_foreach_item(hPlaylist, ServerPlaylistItemCallback, NULL);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_foreach_item", MediaControllerGetError(nRet),mc_playlist_destroy(hPlaylist));

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_ResultPlaylistCb, "ServerPlaylistItemCallback", "CallBack Not Invoked", mc_playlist_destroy(hPlaylist);mc_server_unset_playback_position_cmd_received_cb(g_hMcServer));

	nRet = mc_playlist_destroy(hPlaylist);
	PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_destroy", MediaControllerGetError(nRet));

	return 0;
}

  /**
 * @testcase 					ITc_mc_playlist_clone_and_destroy_p
 * @author					SRID(bipin.k)
 * @reviewer					SRID(manoj.g2)
 * @type 						auto
 * @since_tizen 				4.0
 * @description				Positive test case for cloning and destroying playlist.
 * @scenario					Call ServerMcRegisterPlaylist
 * @apicovered				ServerMcRegisterPlaylist,mc_playlist_clone,mc_playlist_destroy.
 * @passcase					If mc_playlist_clone and mc_playlist_destroy is successful.
 * @failcase					If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To clone and destroy playlist data

int ITc_mc_playlist_clone_and_destroy_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h hPlaylist = NULL;
	mc_playlist_h hPlaylistDst = NULL;

	nRet = ServerMcRegisterPlaylist(&hPlaylist);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "ServerMcRegisterPlaylist", MediaControllerGetError(nRet));
	CHECK_HANDLE(hPlaylist, "mc_client_get_latest_server_info");

	nRet = mc_playlist_clone(hPlaylist, &hPlaylistDst);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_clone", MediaControllerGetError(nRet),mc_playlist_destroy(hPlaylist);mc_playlist_destroy(hPlaylist););
	CHECK_HANDLE(hPlaylistDst, "mc_playlist_clone");

	nRet = mc_playlist_destroy(hPlaylist);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_destroy", MediaControllerGetError(nRet), mc_playlist_destroy(hPlaylistDst));

	nRet = mc_playlist_destroy(hPlaylistDst);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_destroy", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 					ITc_mc_metadata_clone_p
 * @author					SRID(bipin.k)
 * @reviewer					SRID(manoj.g2)
 * @type 						auto
 * @since_tizen 				4.0
 * @description				Positive test case of metadata clone.
 * @scenario					Call mc_metadata_clone
 * @apicovered				mc_client_get_latest_server_info,mc_client_get_server_metadata,mc_metadata_clone,mc_metadata_destroy
 * @passcase					If mc_metadata_clone and mc_metadata_destroy is successful.
 * @failcase					If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
 //& type: auto
//& purpose: To clone and destroy metadata
int ITc_mc_metadata_clone_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_metadata_h hMetadata = NULL;
	mc_metadata_h hMetadataDst = NULL;

	nRet = mc_client_get_latest_server_info(g_hMcClient, &g_McServerName, &g_McServerState);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet));
	CHECK_HANDLE(g_McServerName, "mc_client_get_latest_server_info");
	if((g_McServerState < MC_SERVER_STATE_NONE) || (g_McServerState > MC_SERVER_STATE_DEACTIVATE))
	{
		FPRINTF("[Line : %d][%s] %s Enum returned is out of range =%d \\n", __LINE__, API_NAMESPACE, "g_McServerState ",g_McServerState);
		FREE_MEMORY(g_McServerName);
		return 1;
	}

	nRet = mc_client_get_server_metadata(g_hMcClient, g_McServerName, &hMetadata);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_metadata", MediaControllerGetError(nRet),FREE_MEMORY(g_McServerName));
	CHECK_HANDLE_CLEANUP(hMetadata, "mc_client_get_server_metadata", FREE_MEMORY(g_McServerName));

	nRet = mc_metadata_clone(hMetadata, &hMetadataDst);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_metadata_clone", MediaControllerGetError(nRet),FREE_MEMORY(g_McServerName);mc_metadata_destroy(hMetadata));
	CHECK_HANDLE_CLEANUP(hMetadataDst, "mc_metadata_clone", FREE_MEMORY(g_McServerName));

	nRet = mc_metadata_destroy(hMetadata);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_metadata_destroy", MediaControllerGetError(nRet),mc_metadata_destroy(hMetadataDst);FREE_MEMORY(g_McServerName));

	nRet = mc_metadata_destroy(hMetadataDst);
	PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_metadata_destroy", MediaControllerGetError(nRet));

	FREE_MEMORY(g_McServerName);

	return 0;
}
  /**
 * @testcase 					ITc_mc_metadata_destroy_p
 * @author					SRID(bipin.k)
 * @reviewer					SRID(manoj.g2)
 * @type 						auto
 * @since_tizen 				4.0
 * @description				Positive test case to get server metadata and then destroy it.
 * @scenario					Call  mc_client_get_server_metadata and mc_metadata_destroy
 * @apicovered				mc_client_get_latest_server_info,mc_client_get_server_metadata,mc_metadata_destroy
 * @passcase					If mc_metadata_destroy is successful.
 * @failcase					If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
 //& type: auto
//& purpose: To destroy  server metadata
int ITc_mc_metadata_destroy_p(void)
{
	START_TEST;
	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_metadata_h hMetadata = NULL;

	nRet = mc_client_get_latest_server_info(g_hMcClient, &g_McServerName, &g_McServerState);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet));
	CHECK_HANDLE(g_McServerName, "mc_client_get_latest_server_info");
	if((g_McServerState < MC_SERVER_STATE_NONE) || (g_McServerState > MC_SERVER_STATE_DEACTIVATE))
	{
		FPRINTF("[Line : %d][%s] %s Enum returned is out of range =%d \\n", __LINE__, API_NAMESPACE, "g_McServerState ",g_McServerState);
		FREE_MEMORY(g_McServerName);
		return 1;
	}

	nRet = mc_client_get_server_metadata(g_hMcClient, g_McServerName, &hMetadata);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_metadata", MediaControllerGetError(nRet),FREE_MEMORY(g_McServerName));
	CHECK_HANDLE_CLEANUP(hMetadata, "mc_client_get_server_metadata",FREE_MEMORY(g_McServerName));

	nRet = mc_metadata_destroy(hMetadata);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_metadata_destroy", MediaControllerGetError(nRet),FREE_MEMORY(g_McServerName));

	FREE_MEMORY(g_McServerName);

	return 0;
}

  /**
 * @testcase 					ITc_mc_metadata_get_p
 * @author					SRID(bipin.k)
 * @reviewer					SRID(manoj.g2)
 * @type 						auto
 * @since_tizen 				4.0
 * @description				Positive test case of mc_metadata_get and then destroy it.
 * @scenario					Call ITc_mc_metadata_get_p, mc_metadata_destroy
 * @apicovered				mc_client_get_latest_server_info,mc_client_get_server_metadata,mc_metadata_get
 * @passcase					If mc_metadata_get and mc_metadata_destroy is successful.
 * @failcase					If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
 //& type: auto
//& purpose: To get and destroy metadata
int ITc_mc_metadata_get_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_metadata_h hMetadata = NULL;
	char *pValue = NULL;
	bool bCheckVal = false;

	nRet = mc_client_get_latest_server_info(g_hMcClient, &g_McServerName, &g_McServerState);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet));
	CHECK_HANDLE(g_McServerName, "mc_client_get_latest_server_info");
	if((g_McServerState < MC_SERVER_STATE_NONE) || (g_McServerState > MC_SERVER_STATE_DEACTIVATE))
	{
		FPRINTF("[Line : %d][%s] %s Enum returned is out of range =%d \\n", __LINE__, API_NAMESPACE, "g_McServerState ",g_McServerState);
		FREE_MEMORY(g_McServerName);
		return 1;
	}

	nRet = mc_client_get_server_metadata(g_hMcClient, g_McServerName, &hMetadata);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_metadata", MediaControllerGetError(nRet),FREE_MEMORY(g_McServerName));
	CHECK_HANDLE_CLEANUP(hMetadata, "mc_client_get_server_metadata",FREE_MEMORY(g_McServerName));

	nRet = mc_metadata_get(hMetadata, MC_META_MEDIA_TITLE, &pValue);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_metadata_get", MediaControllerGetError(nRet),mc_metadata_destroy(hMetadata);FREE_MEMORY(g_McServerName));
	CHECK_HANDLE_CLEANUP(pValue, "mc_metadata_get", mc_metadata_destroy(hMetadata);FREE_MEMORY(g_McServerName));

	if (strncmp(pValue, g_McTestMetadata[0],strlen( g_McTestMetadata[0])) == 0){
		bCheckVal = true;
	}
	FREE_MEMORY(pValue);

	if(bCheckVal != true){
		FPRINTF("[Line : %d][%s] %s Metadata is not Correct\\n", __LINE__, API_NAMESPACE, "mc_metadata_get");
		FREE_MEMORY(g_McServerName);
		mc_metadata_destroy(hMetadata);
		return 1;
	}

	FREE_MEMORY(g_McServerName);
	nRet = mc_metadata_destroy(hMetadata);
	PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_destroy_metadata", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mc_server_send_cmd_reply_p
 * @author            		SRID(priya.kohli)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				To test mc_server_send_cmd_reply
 * @scenario				Call mc_server_send_cmd_reply
 * @apicovered				mc_server_send_cmd_reply, mc_server_unset_custom_cmd_received_cb
 * @passcase				If mc_server_send_cmd_reply returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_server_send_cmd_reply
int ITc_mc_server_send_cmd_reply_p(void)
{
	START_TEST;

	int nRet = -1;
	g_CallBackHit = false;
	const char *pszIndex="3";
	unsigned long long ullPosition = 0;
	int nCode = 0;
        mc_result_code_e eResultCodeArray[] = {
        MC_RESULT_CODE_SUCCESS,
        MC_RESULT_CODE_ALREADY_DONE,
        MC_RESULT_CODE_ABORTED,
        MC_RESULT_CODE_TIMEOUT,
        MC_RESULT_CODE_NETWORK_FAILED,
        MC_RESULT_CODE_NO_ACCOUNT,
        MC_RESULT_CODE_UNKNOWN,
};

        int nCountEnum = sizeof(eResultCodeArray)/sizeof(eResultCodeArray[0]);
        int nCount = 0;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = mc_server_set_playlist_cmd_received_cb(g_hMcServer, ServerPlaylistCommandReceivedCallback,g_UserData);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_playlist_cmd_received_cb", MediaControllerGetError(nRet));

        for(nCount = 0; nCount < nCountEnum; nCount++)
        {

	        nRet = mc_client_send_playlist_cmd(g_hMcClient, g_szServerName, g_szPlaylistName, pszIndex, MC_PLAYBACK_ACTION_PLAY, ullPosition, &g_request_id);
	        PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_playlist_cmd", MediaControllerGetError(nRet),mc_server_unset_playlist_cmd_received_cb(g_hMcServer));

	        IterateGmainLoop();
	        PRINT_RESULT_CLEANUP(true, g_CallBackHit, "ServerPlaylistCommandReceivedCallback", "CallBack Not Invoked", mc_server_unset_playlist_cmd_received_cb(g_hMcServer));

	        bundle *pBundle = bundle_create();
	        CHECK_HANDLE_CLEANUP(pBundle, "bundle_create", mc_server_unset_playlist_cmd_received_cb(g_hMcServer));

	        nRet = bundle_add_str(pBundle, "key1", "value1");
	        PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "bundle_add_str", MediaControllerGetError(nRet), bundle_free(pBundle));

                nRet = mc_server_send_cmd_reply(g_hMcServer, g_szClientName, g_request_id, eResultCodeArray[nCount], pBundle);
                PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_send_cmd_reply", MediaControllerGetError(nRet), bundle_free(pBundle); mc_server_unset_playlist_cmd_received_cb(g_hMcServer));
	bundle_free(pBundle);

        }
	nRet = mc_server_unset_playlist_cmd_received_cb(g_hMcServer);
	PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_unset_playlist_cmd_received_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mc_server_add_item_to_playlist_p
 * @author            		SRID(priya.kohli)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				To test mc_server_add_item_to_playlist
 * @scenario				Call mc_server_add_item_to_playlist
 * @apicovered				mc_server_create_playlist, mc_server_add_item_to_playlist, mc_playlist_destroy
 * @passcase				If mc_server_add_item_to_playlist returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_server_add_item_to_playlist
int ITc_mc_server_add_item_to_playlist_p(void)
{
    START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h hPlaylist = NULL;
	const char *pszIndex = "1";

	nRet = mc_server_create_playlist(g_hMcServer, g_PlaylistName, &hPlaylist);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_create_playlist", MediaControllerGetError(nRet));
	CHECK_HANDLE(hPlaylist, "mc_server_create_playlist");

	int sSize = sizeof(g_PlaylistArray)/sizeof(g_PlaylistArray[0]);
	int StringIndex = 0;
	for(StringIndex = 0; StringIndex < sSize; StringIndex++)
	{
		FPRINTF("[%d:%s] Adding item to playlist index=%d, [%s]\n", __LINE__, __FUNCTION__, StringIndex, g_PlaylistArray[StringIndex]);
		nRet = mc_server_add_item_to_playlist(g_hMcServer, hPlaylist, pszIndex, StringIndex, g_PlaylistArray[StringIndex]);
		PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_add_item_to_playlist", MediaControllerGetError(nRet),mc_playlist_destroy(hPlaylist));
	}

	nRet = mc_playlist_destroy(hPlaylist);
	PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_destroy", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mc_server_update_playlist_done_p
 * @author            		SRID(priya.kohli)
 * @reviewer         		SRID(manoj.g2)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				To test mc_server_update_playlist_done
 * @scenario				Call mc_server_update_playlist_done
 * @apicovered				mc_server_create_playlist, mc_server_add_item_to_playlist, mc_server_update_playlist_done, mc_playlist_destroy
 * @passcase				If mc_server_update_playlist_done returns MEDIA_CONTROLLER_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mc_server_update_playlist_done
int ITc_mc_server_update_playlist_done_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h hPlaylist = NULL;
	const char *pszIndex = "1";

	nRet = mc_server_create_playlist(g_hMcServer, g_PlaylistName, &hPlaylist);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_create_playlist", MediaControllerGetError(nRet));
	CHECK_HANDLE(hPlaylist, "mc_server_create_playlist");

	int sSize = sizeof(g_PlaylistArray)/sizeof(g_PlaylistArray[0]);
	int StringIndex = 0;
	for(StringIndex = 0; StringIndex < sSize; StringIndex++)
	{
		FPRINTF("[%d:%s] Adding item to playlist index=%d, [%s]\n", __LINE__, __FUNCTION__, StringIndex, g_PlaylistArray[StringIndex]);
		nRet = mc_server_add_item_to_playlist(g_hMcServer, hPlaylist, pszIndex, StringIndex, g_PlaylistArray[StringIndex]);
		PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_add_item_to_playlist", MediaControllerGetError(nRet),mc_playlist_destroy(hPlaylist));
	}

	nRet = mc_server_update_playlist_done(g_hMcServer, hPlaylist);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_playlist_done", MediaControllerGetError(nRet),mc_playlist_destroy(hPlaylist));

	nRet = mc_playlist_destroy(hPlaylist);
	PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_destroy", MediaControllerGetError(nRet));

	return 0;
}

 /**
 * @testcase 				ITc_mc_server_set_get_playback_content_type_p
 * @author					SRID(priya.kohli)
 * @reviewer				SRID(awadhesh1.s)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				Sets and gets the playback content type to update the latest playback info.
 * @scenario				Sets and gets the playback content type to update the latest playback info.
 * @apicovered				mc_server_set_playback_content_type, mc_server_update_playback_info, mc_client_get_playback_content_type
 * @passcase				If Target API is successful
 * @failcase				If Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
 //& type: auto
//& purpose: To set and get the playback content type to update the latest playback info.
int ITc_mc_server_set_get_playback_content_type_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_content_type_e eContentTypeArray[] = {MC_CONTENT_TYPE_IMAGE,
						MC_CONTENT_TYPE_VIDEO,
						MC_CONTENT_TYPE_MUSIC,
						MC_CONTENT_TYPE_OTHER};
	mc_content_type_e eGetContentType;
	mc_playback_h hPlaybackInfo;
	char * pszServerName = NULL;
	mc_server_state_e eServerState;

	int nSize = sizeof(eContentTypeArray)/sizeof(eContentTypeArray[0]);

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	for(int nCounter = 0; nCounter < nSize; nCounter++)
	{
		nRet = mc_server_set_playback_content_type(g_hMcServer, eContentTypeArray[nCounter]);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_playback_content_type", MediaControllerGetError(nRet));

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

		nRet = mc_client_get_server_playback_info(g_hMcClient, pszServerName, &hPlaybackInfo);
		PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_playback_info", MediaControllerGetError(nRet), FREE_MEMORY(pszServerName));
		CHECK_HANDLE_CLEANUP(hPlaybackInfo, "mc_client_get_server_playback_info", FREE_MEMORY(pszServerName));

		nRet = mc_client_get_playback_content_type(hPlaybackInfo, &eGetContentType);
		PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_playback_content_type", MediaControllerGetError(nRet), FREE_MEMORY(pszServerName); mc_client_destroy_playback(hPlaybackInfo));

		if (eContentTypeArray[nCounter] != eGetContentType)
		{
			FPRINTF("[Line : %d][%s] %s Content type returned did not match \\n", __LINE__, API_NAMESPACE, "mc_client_get_playback_content_type");
			mc_client_destroy_playback(hPlaybackInfo);
			FREE_MEMORY(pszServerName);
			return 1;
		}

		nRet = mc_client_destroy_playback(hPlaybackInfo);
		PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_destroy_playback", MediaControllerGetError(nRet));
		hPlaybackInfo = NULL;
	}
	return 0;
}

 /**
 * @testcase 				ITc_mc_server_set_get_icon_p
 * @author					SRID(priya.kohli)
 * @reviewer				SRID(awadhesh1.s)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				Sets and gets the icon URI of media controller server.
 * @scenario				Sets and gets the icon URI of media controller server.
 * @apicovered				mc_server_set_icon, mc_client_get_server_icon
 * @passcase				If Target API is successful
 * @failcase				If Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
 //& type: auto
//& purpose: To set and get the icon URI of media controller server.
int ITc_mc_server_set_get_icon_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	char *pszUri = "test.jpg";
	char *pszGetUri = NULL;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = mc_server_set_icon(g_hMcServer, pszUri);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_icon", MediaControllerGetError(nRet), FREE_MEMORY(pszUri));

	nRet = mc_client_get_server_icon(g_hMcClient, g_szServerName, &pszGetUri);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_icon", MediaControllerGetError(nRet));
	CHECK_HANDLE(pszGetUri, "mc_client_get_server_icon");

	if (strncmp(pszUri, pszGetUri,strlen(pszUri))!= 0)
	{
		FPRINTF("[Line : %d][%s] %s Icon returned did not match = %s \\n", __LINE__, API_NAMESPACE, "mc_client_get_server_icon",pszGetUri);
		FREE_MEMORY(pszGetUri);
		return 1;
	}

	FREE_MEMORY(pszGetUri);

	return 0;
}

 /**
 * @testcase 				ITc_mc_server_set_get_update_playback_ability_p
 * @author					SRID(priya.kohli)
 * @reviewer				SRID(awadhesh1.s)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				Sets and gets the playback ability's support of the media controller.
 * @scenario				Sets and gets the playback ability's support of the media controller.
 * @apicovered				mc_server_set_playback_ability, mc_server_update_playback_ability, mc_client_get_server_playback_ability, mc_playback_ability_destroy
 * @passcase				If Target API is successful
 * @failcase				If Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
 //& type: auto
//& purpose: To set and get the playback ability's support of the media controller.
int ITc_mc_server_set_get_update_playback_ability_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_ability_h hAbility = NULL;

	int nPlaybackSize = sizeof(g_ePlaybackActionArr)/sizeof(g_ePlaybackActionArr[0]);
	int nAbilitySize = sizeof(g_eAbilitySupportArray)/sizeof(g_eAbilitySupportArray[0]);

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	for ( int nPlaybackCounter = 0; nPlaybackCounter < nPlaybackSize; nPlaybackCounter++ )
	{
		for ( int nAbilityCounter = 0; nAbilityCounter < nAbilitySize; nAbilityCounter++ )
		{
			nRet = mc_server_set_playback_ability(g_hMcServer, g_ePlaybackActionArr[nPlaybackCounter], g_eAbilitySupportArray[nAbilityCounter]);
			PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_playback_ability", MediaControllerGetError(nRet));

			nRet = mc_server_update_playback_ability(g_hMcServer);
			PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_playback_ability", MediaControllerGetError(nRet));

			nRet = mc_client_get_server_playback_ability(g_hMcClient, g_szServerName, &hAbility);
			PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_playback_ability", MediaControllerGetError(nRet));
			CHECK_HANDLE(hAbility, "mc_client_get_server_playback_ability");

			nRet = mc_playback_ability_destroy(hAbility);
			PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playback_ability_destroy", MediaControllerGetError(nRet));
			hAbility = NULL;
		}
	}

	return 0;
}

 /**
 * @testcase 				ITc_mc_playback_ability_clone_destroy_p
 * @author					SRID(priya.kohli)
 * @reviewer				SRID(awadhesh1.s)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				Clones and destroys a playback ability handle.
 * @scenario				Clones and destroys a playback ability handle.
 * @apicovered				mc_client_get_server_playback_ability, mc_playback_ability_clone, mc_playback_ability_destroy
 * @passcase				If Target API is successful
 * @failcase				If Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
 //& type: auto
//& purpose: To clone and destroy a playback ability handle.
int ITc_mc_playback_ability_clone_destroy_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_ability_h hAbility = NULL;
	mc_playback_ability_h hAbilityDst = NULL;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(0, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = mc_client_get_server_playback_ability(g_hMcClient, g_szServerName, &hAbility);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_playback_ability", MediaControllerGetError(nRet));
	CHECK_HANDLE(hAbility, "mc_client_get_server_playback_ability");

	nRet = mc_playback_ability_clone(hAbility, &hAbilityDst);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playback_ability_clone", MediaControllerGetError(nRet),mc_playback_ability_destroy(hAbility));
	CHECK_HANDLE_CLEANUP(hAbilityDst, "mc_playback_ability_clone",mc_playback_ability_destroy(hAbility));

	nRet = mc_playback_ability_destroy(hAbility);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playback_ability_destroy", MediaControllerGetError(nRet),mc_playback_ability_destroy(hAbilityDst));

	nRet = mc_playback_ability_destroy(hAbilityDst);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playback_ability_destroy", MediaControllerGetError(nRet));

	return 0;
}

 /**
 * @testcase 				ITc_mc_playback_action_is_supported_p
 * @author					SRID(priya.kohli)
 * @reviewer				SRID(awadhesh1.s)
 * @type 					auto
 * @since_tizen 			5.0
 * @description				Gets the support value of the playback ability.
 * @scenario				Gets the support value of the playback ability.
 * @apicovered				mc_client_get_server_playback_ability, mc_playback_action_is_supported, mc_playback_ability_destroy
 * @passcase				If Target API is successful
 * @failcase				If Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
 //& type: auto
//& purpose: To get the support value of the playback ability.
int ITc_mc_playback_action_is_supported_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playback_ability_h hAbility = NULL;
	mc_ability_support_e eAbilitySupport = MC_ABILITY_SUPPORTED_UNDECIDED;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(0, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	int nSize = sizeof(g_ePlaybackActionArr)/sizeof(g_ePlaybackActionArr[0]);

	for ( int nCounter = 0; nCounter < nSize; nCounter++ )
	{
		nRet = mc_client_get_server_playback_ability(g_hMcClient, g_szServerName, &hAbility);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_server_playback_ability", MediaControllerGetError(nRet));
		CHECK_HANDLE(hAbility, "mc_client_get_server_playback_ability");

		nRet = mc_playback_action_is_supported(hAbility, g_ePlaybackActionArr[nCounter], &eAbilitySupport);
		PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playback_action_is_supported", MediaControllerGetError(nRet),mc_playback_ability_destroy(hAbility));

		if((eAbilitySupport < MC_ABILITY_SUPPORTED_YES) || (eAbilitySupport > MC_ABILITY_SUPPORTED_UNDECIDED))
		{
			FPRINTF("[Line : %d][%s] Enum returned is out of range =%d \\n", __LINE__, API_NAMESPACE);
			nRet = mc_playback_ability_destroy(hAbility);
			PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_destroy_playback_ability", MediaControllerGetError(nRet));
			return 1;
		}

		nRet = mc_playback_ability_destroy(hAbility);
		PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_destroy_playback_ability", MediaControllerGetError(nRet));
	}

	return 0;
}

 /**
 * @testcase 				ITc_mc_server_set_unset_search_cmd_received_cb_p
 * @author				SRID(kanchan.m)
 * @reviewer				SRID(priya.kohli)
 * @type 				auto
 * @since_tizen 			5.0
 * @description				Sets and unsets the callback for receiving search command from client.
 * @scenario				Sets and unsets the callback for receiving search command from client.
 * @apicovered				mc_server_set_search_cmd_received_cb, mc_server_unset_search_cmd_received_cb
 * @passcase				If Target API is successful and callback is invoked
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
 //& type: auto
//& purpose: To set and unset the callback for receiving search command from client..
int ITc_mc_server_set_unset_search_cmd_received_cb_p(void)
{
	START_TEST;

	int nRet = -1;
	char * pszRequestID = 0;
	g_CallBackHit = false;
	mc_content_type_e eContentType = MC_CONTENT_TYPE_IMAGE;
	mc_search_category_e eSearchCategory = MC_SEARCH_TITLE;
	char* TestKeywords = "test_title";
	char * pszServerName = NULL;
	mc_server_state_e eServerState;

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

	nRet = mc_search_set_condition(g_hMcSearch, eContentType, eSearchCategory, TestKeywords, NULL);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_search_set_condition", MediaControllerGetError(nRet), FREE_MEMORY(pszServerName));

	nRet = mc_client_send_search_cmd(g_hMcClient, pszServerName, g_hMcSearch, &pszRequestID);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_search_cmd", MediaControllerGetError(nRet), FREE_MEMORY(pszServerName));
	CHECK_HANDLE(pszRequestID,"mc_client_send_search_cmd");

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "mc_server_set_search_cmd_received_cb", "CallBack Not Invoked", mc_server_unset_search_cmd_received_cb(g_hMcServer); FREE_MEMORY(pszServerName); FREE_MEMORY(pszRequestID));

	nRet = mc_server_unset_search_cmd_received_cb(g_hMcServer);
	PRINT_RESULT_CLEANUP(nRet, MEDIA_CONTROLLER_ERROR_NONE, "mc_server_unset_search_cmd_received_cb", MediaControllerGetError(nRet),FREE_MEMORY(pszServerName); FREE_MEMORY(pszRequestID));
	FREE_MEMORY(pszServerName);
	FREE_MEMORY(pszRequestID);

	return 0;
}

 /**
 * @testcase 				ITc_mc_metadata_encode_decode_season_p
 * @author					SRID(priya.kohli)
 * @reviewer				SRID(j.abhishek)
 * @type 					auto
 * @since_tizen 			5.5
 * @description				Encodes and decodes the season data for use in metadata.
 * @scenario				Encodes and decodes the season data for use in metadata.
 * @apicovered				mc_metadata_encode_season, mc_metadata_decode_season
 * @passcase				If Target API is successful
 * @failcase				If Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
 //& type: auto
//& purpose: To encodes and decodes the season data for use in metadata.
int ITc_mc_metadata_encode_decode_season_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	char * pszSeasonMeta = NULL;
	char * pszStrVal = NULL;
	int nGetSeasonNum = 0;
	const char *pszSeasonTitle = "media_season";
	int nSeasonNum = 15;

	nRet = mc_metadata_encode_season(nSeasonNum, pszSeasonTitle, &pszSeasonMeta);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_metadata_encode_season", MediaControllerGetError(nRet));
	CHECK_HANDLE(pszSeasonMeta, "mc_metadata_encode_season");

	nRet = mc_metadata_decode_season(pszSeasonMeta, &nGetSeasonNum, &pszStrVal);
	FREE_MEMORY(pszSeasonMeta);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_metadata_decode_season", MediaControllerGetError(nRet));
	CHECK_HANDLE(pszStrVal, "mc_metadata_decode_season");
	if(nGetSeasonNum != nSeasonNum) {
		FPRINTF("[%d:%s] wrong nGetSeasonNum value [%d]\n", __LINE__, __FUNCTION__, nGetSeasonNum);
		FREE_MEMORY(pszStrVal);
		return 1;
	}

	if(strncmp(pszSeasonTitle, pszStrVal,strlen(pszStrVal))) {
		FPRINTF("[%d:%s] wrong pszStrVal value [%s]\n", __LINE__, __FUNCTION__, pszStrVal);
		FREE_MEMORY(pszStrVal);
		return 1;
	}

	FREE_MEMORY(pszStrVal);

	return 0;
}

 /**
 * @testcase 				ITc_mc_metadata_encode_decode_episode_p
 * @author					SRID(priya.kohli)
 * @reviewer				SRID(j.abhishek)
 * @type 					auto
 * @since_tizen 			5.5
 * @description				Encodes and decodes the episode data for use in metadata.
 * @scenario				Encodes and decodes the episode data for use in metadata.
 * @apicovered				mc_metadata_encode_episode, mc_metadata_decode_episode
 * @passcase				If Target API is successful
 * @failcase				If Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
 //& type: auto
//& purpose: To encodes and decodes the episode data for use in metadata.
int ITc_mc_metadata_encode_decode_episode_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	char * pszEpisodeMeta = NULL;
	char * pszStrVal = NULL;
	int nGetEpisodeNum = 0;
	const char *pszEpisodeTitle = "media_episode";
	int nEpisodeNum = 15;

	nRet = mc_metadata_encode_episode(nEpisodeNum, pszEpisodeTitle, &pszEpisodeMeta);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_metadata_encode_episode", MediaControllerGetError(nRet));
	CHECK_HANDLE(pszEpisodeMeta, "mc_metadata_encode_episode");

	nRet = mc_metadata_decode_episode(pszEpisodeMeta, &nGetEpisodeNum, &pszStrVal);
	FREE_MEMORY(pszEpisodeMeta);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_metadata_decode_episode", MediaControllerGetError(nRet));
	CHECK_HANDLE(pszStrVal, "mc_metadata_decode_episode");
	if(nGetEpisodeNum != nEpisodeNum) {
		FPRINTF("[%d:%s] wrong nGetEpisodeNum value [%d]\n", __LINE__, __FUNCTION__, nGetEpisodeNum);
		FREE_MEMORY(pszStrVal);
		return 1;
	}

	if(strncmp(pszEpisodeTitle, pszStrVal,strlen(pszStrVal))) {
		FPRINTF("[%d:%s] wrong pszStrVal value [%s]\n", __LINE__, __FUNCTION__, pszStrVal);
		FREE_MEMORY(pszStrVal);
		return 1;
	}

	FREE_MEMORY(pszStrVal);

	return 0;
}

 /**
 * @testcase 				ITc_mc_metadata_encode_decode_resolution_p
 * @author					SRID(priya.kohli)
 * @reviewer				SRID(j.abhishek)
 * @type 					auto
 * @since_tizen 			5.5
 * @description				Encodes and decodes the resolution data for use in metadata.
 * @scenario				Encodes and decodes the resolution data for use in metadata.
 * @apicovered				mc_metadata_encode_resolution, mc_metadata_decode_resolution
 * @passcase				If Target API is successful
 * @failcase				If Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
 //& type: auto
//& purpose: To encodes and decodes the resolution data for use in metadata.
int ITc_mc_metadata_encode_decode_resolution_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	char * pszResolutionMeta = NULL;
	unsigned int nWidth = 0;
	unsigned int nHeight = 0;

	nRet = mc_metadata_encode_resolution(META_W, META_H, &pszResolutionMeta);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_metadata_encode_resolution", MediaControllerGetError(nRet));
	CHECK_HANDLE(pszResolutionMeta, "mc_metadata_encode_resolution");

	nRet = mc_metadata_decode_resolution(pszResolutionMeta, &nWidth, &nHeight);
	FREE_MEMORY(pszResolutionMeta);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_metadata_decode_resolution", MediaControllerGetError(nRet));

	if(nWidth != META_W) {
		FPRINTF("[%d:%s] wrong nWidth value [%u]\n", __LINE__, __FUNCTION__, nWidth);
		return 1;
	}

	if(nHeight != META_H) {
		FPRINTF("[%d:%s] wrong nHeight value [%u]\n", __LINE__, __FUNCTION__, nHeight);
		return 1;
	}

	return 0;
}


/**
 * @testcase 					ITc_mc_playlist_get_item_count_p
 * @author						SRID(priya.kohli)
 * @reviewer					SRID(bipin.k)
 * @type 						auto
 * @since_tizen 				5.5
 * @description					Gets the number of the media item in a playlist.
 * @scenario					To get the number of the media item in a playlist.
 * @apicovered					mc_playlist_get_item_count, mc_playlist_destroy
 * @passcase					If Target API is successful
 * @failcase					If Target API Fails
 * @precondition				NA
 * @postcondition				Playlist should be released using mc_playlist_destroy().
 * */
 //& type: auto
//& purpose: To get the number of the media item in a playlist.
int ITc_mc_playlist_get_item_count_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h hPlaylist = NULL;
	int nCount = 0;
	int nItemCount = 1;

	nRet = ServerMcRegisterPlaylist(&hPlaylist);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "ServerMcRegisterPlaylist", MediaControllerGetError(nRet));
	CHECK_HANDLE(hPlaylist, "ServerMcRegisterPlaylist");

	nRet = mc_playlist_get_item_count(hPlaylist, &nCount);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_get_item_count", MediaControllerGetError(nRet), mc_playlist_destroy(hPlaylist));
	PRINT_RESULT_CLEANUP(nItemCount, nCount, "mc_playlist_get_item_count", "nCount != 1", mc_playlist_destroy(hPlaylist));

	nRet = mc_playlist_destroy(hPlaylist);
	PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_destroy", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 					ITc_mc_playlist_get_playlist_count_p
 * @author						SRID(priya.kohli)
 * @reviewer					SRID(bipin.k)
 * @type 						auto
 * @since_tizen 				5.5
 * @description					Gets the number of playlists for the given app_id.
 * @scenario					The media controller server can have several playlists. You can get playlist count only for the activated media controller server.
 * @apicovered					mc_playlist_get_playlist_count, mc_playlist_destroy
 * @passcase					If Target API is successful
 * @failcase					If Target API Fails
 * @precondition				NA
 * @postcondition				Playlist should be released using mc_playlist_destroy().
 * */
 //& type: auto
//& purpose: To get the number of playlists for the given app_id.
int ITc_mc_playlist_get_playlist_count_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h hPlaylist = NULL;
	int nCount = 0;
	int nPlaylistCount = 1;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = ServerMcRegisterPlaylist(&hPlaylist);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "ServerMcRegisterPlaylist", MediaControllerGetError(nRet));
	CHECK_HANDLE(hPlaylist, "ServerMcRegisterPlaylist");

	nRet = mc_playlist_get_playlist_count(g_szServerName, &nCount);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_get_playlist_count", MediaControllerGetError(nRet), mc_playlist_destroy(hPlaylist));
	PRINT_RESULT_CLEANUP(nPlaylistCount, nCount, "mc_playlist_get_playlist_count", "nCount != 1", mc_playlist_destroy(hPlaylist));

	nRet = mc_playlist_destroy(hPlaylist);
	PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_destroy", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 					ITc_mc_playlist_get_playlist_p
 * @author						SRID(priya.kohli)
 * @reviewer					SRID(bipin.k)
 * @type 						auto
 * @since_tizen 				5.5
 * @description					Gets the playlist handle.
 * @scenario					This function creates a new playlist handle for the given app_id and playlist_name.
 *								You can get the playlist only for the activated media controller server.
 *								If app_id is not an ID of an activated media controller server, or if playlist_name is invalid,
 *								this function will return #MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER.
 * @apicovered					mc_playlist_get_playlist, mc_playlist_destroy
 * @passcase					If Target API is successful
 * @failcase					If Target API Fails
 * @precondition				NA
 * @postcondition				Playlist should be released using mc_playlist_destroy().
 * */
 //& type: auto
//& purpose: To get the playlist handle.
int ITc_mc_playlist_get_playlist_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h hPlaylist = NULL;
	mc_playlist_h hGetPlaylist = NULL;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = ServerMcRegisterPlaylist(&hPlaylist);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "ServerMcRegisterPlaylist", MediaControllerGetError(nRet));
	CHECK_HANDLE(hPlaylist, "ServerMcRegisterPlaylist");

	nRet = mc_playlist_get_playlist(g_szServerName, g_PlaylistName, &hGetPlaylist);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_get_playlist", MediaControllerGetError(nRet), mc_playlist_destroy(hPlaylist));
	CHECK_HANDLE(hGetPlaylist, "mc_playlist_get_playlist");

	nRet = mc_playlist_destroy(hPlaylist);
	PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_destroy", MediaControllerGetError(nRet));

	nRet = mc_playlist_destroy(hGetPlaylist);
	PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_destroy", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 					ITc_mc_playlist_foreach_playlist_p
 * @author						SRID(priya.kohli)
 * @reviewer					SRID(bipin.k)
 * @type 						auto
 * @since_tizen 				5.5
 * @description					Iterates through playlists of the media controller server.
 * @scenario					This function iterates through all playlists of the given app_id.
 *								The media controller server can have several playlists.
 *								You can get playlists only for the activated media controller server.
 *								If app_id is not an ID of an activated media controller server,
 *								this function will return #MEDIA_CONTROLLER_ERROR_INVALID_PARAMETER.
 *								The callback function will be invoked for every retrieved playlist.
 *								If there are no playlists, the callback will not be invoked.
 * @apicovered					mc_playlist_foreach_playlist, mc_playlist_destroy
 * @passcase					If Target API is successful
 * @failcase					If Target API Fails
 * @precondition				NA
 * @postcondition				Playlist should be released using mc_playlist_destroy().
 * */
 //& type: auto
//& purpose: To iterate through playlists of the media controller server.
int ITc_mc_playlist_foreach_playlist_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	mc_playlist_h hPlaylist = NULL;
	g_CallBackHit = false;

	nRet = GetCompleteServerInfo();
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "GetCompleteServerInfo", "Return Value Not Correct");

	nRet = ServerMcRegisterPlaylist(&hPlaylist);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "ServerMcRegisterPlaylist", MediaControllerGetError(nRet));
	CHECK_HANDLE(hPlaylist, "ServerMcRegisterPlaylist");

	nRet = mc_playlist_foreach_playlist(g_szServerName, ServerForeachPlaylistCommandReceivedCallback, g_UserData);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_foreach_playlist", MediaControllerGetError(nRet), mc_playlist_destroy(hPlaylist));

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "ServerForeachPlaylistCommandReceivedCallback", "CallBack Not Invoked", mc_playlist_destroy(hPlaylist));

	nRet = mc_playlist_destroy(hPlaylist);
	PRINT_RESULT_NORETURN(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_playlist_destroy", MediaControllerGetError(nRet));
	return 0;
}

/**
 * @testcase					ITc_mc_server_update_subtitles_enabled_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type					auto
 * @since_tizen					5.5
 * @description					Updates the modified subtitles display status.
 * @apicovered					mc_server_update_subtitles_enabled
 * @passcase					If Target API is successful
 * @failcase					If Target API Fails
 * @precondition				mc_client_create, mc_server_create
 * @postcondition				mc_client_destroy, mc_server_destroy
 * */
 //& type: auto
//& purpose: Updates the modified subtitles display status.
int ITc_mc_server_update_subtitles_enabled_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	g_CallBackHit = false;

	nRet = mc_client_set_subtitles_updated_cb(g_hMcClient, ServerAttributeUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_subtitles_updated_cb", MediaControllerGetError(nRet));

	nRet = mc_server_update_subtitles_enabled(g_hMcServer, true);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_subtitles_enabled", MediaControllerGetError(nRet));

	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "ServerAttributeUpdatedCallBack", "CallBack Not Invoked");

	return 0;
}

/**
 * @testcase					ITc_mc_server_update_360_mode_enabled_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type					auto
 * @since_tizen					5.5
 * @description					Updates the modified 360 mode display status.
 * @apicovered					mc_server_update_360_mode_enabled
 * @passcase					If Target API is successful
 * @failcase					If Target API Fails
 * @precondition				mc_client_create, mc_server_create
 * @postcondition				mc_client_destroy, mc_server_destroy
 * */
 //& type: auto
//& purpose: Updates the modified 360 mode display status.
int ITc_mc_server_update_360_mode_enabled_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	g_CallBackHit = false;

	nRet = mc_client_set_360_mode_updated_cb(g_hMcClient, ServerAttributeUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_360_mode_updated_cb", MediaControllerGetError(nRet));

	nRet = mc_server_update_360_mode_enabled(g_hMcServer, true);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_360_mode_enabled", MediaControllerGetError(nRet));

	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "ServerAttributeUpdatedCallBack", "CallBack Not Invoked");

	return 0;
}

/**
 * @testcase					ITc_mc_server_update_display_mode_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type					auto
 * @since_tizen					5.5
 * @description					Updates the modified display mode.
 * @apicovered					mc_server_update_display_mode
 * @passcase					If Target API is successful
 * @failcase					If Target API Fails
 * @precondition				mc_client_create, mc_server_create
 * @postcondition				mc_client_destroy, mc_server_destroy
 * */
 //& type: auto
//& purpose: Updates the modified display mode.
int ITc_mc_server_update_display_mode_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	g_CallBackHit = false;

	nRet = mc_client_set_display_mode_updated_cb(g_hMcClient, ServerDisplayModeUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_display_mode_updated_cb", MediaControllerGetError(nRet));

	int nModeSize = sizeof(g_server_eDisplayModeArray)/sizeof(g_server_eDisplayModeArray[0]);

	for(g_nModeIdx = 0; g_nModeIdx < nModeSize; g_nModeIdx++)
	{
		g_CallBackHit = false;
		nRet = mc_server_update_display_mode(g_hMcServer, g_server_eDisplayModeArray[g_nModeIdx]);
		PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_display_mode", MediaControllerGetError(nRet));

		IterateGmainLoop();
		PRINT_RESULT(true, g_CallBackHit, "ServerDisplayModeUpdatedCallBack", "CallBack Not Invoked");
	}

	return 0;
}

/**
 * @testcase					ITc_mc_server_update_display_rotation_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type					auto
 * @since_tizen					5.5
 * @description					Updates the modified display rotation.
 * @apicovered					mc_server_update_display_rotation
 * @passcase					If Target API is successful
 * @failcase					If Target API Fails
 * @precondition				mc_client_create, mc_server_create
 * @postcondition				mc_client_destroy, mc_server_destroy
 * */
 //& type: auto
//& purpose: Updates the modified display rotation.
int ITc_mc_server_update_display_rotation_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	g_CallBackHit = false;

	nRet = mc_client_set_display_rotation_updated_cb(g_hMcClient, ServerDisplayRotationUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_display_rotation_updated_cb", MediaControllerGetError(nRet));

	nRet = mc_server_update_display_rotation(g_hMcServer, MC_DISPLAY_ROTATION_270);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_update_display_rotation", MediaControllerGetError(nRet));

	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "ServerDisplayRotationUpdatedCallBack", "CallBack Not Invoked");

	return 0;
}

/**
 * @testcase					ITc_mc_server_set_unset_subtitles_cmd_received_cb_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type					auto
 * @since_tizen					5.5
 * @description					Set and Unsets the callback for receiving subtitles command from client.
 * @apicovered					mc_server_set_subtitles_cmd_received_cb, mc_server_unset_subtitles_cmd_received_cb
 * @passcase					If Target API is successful
 * @failcase					If Target API Fails
 * @precondition				mc_client_create, mc_server_create
 * @postcondition				mc_client_destroy, mc_server_destroy
 * */
 //& type: auto
//& purpose: Set and Unsets the callback for receiving subtitles command from client.
int ITc_mc_server_set_unset_subtitles_cmd_received_cb_p(void)
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
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet), mc_server_unset_subtitles_cmd_received_cb(g_hMcServer));

	nRet = mc_client_send_subtitles_cmd(g_hMcClient, g_McServerName, true, &pszReqID);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_subtitles_cmd", MediaControllerGetError(nRet), mc_server_unset_subtitles_cmd_received_cb(g_hMcServer));
	CHECK_HANDLE_CLEANUP(pszReqID, "mc_client_send_subtitles_cmd", mc_server_unset_subtitles_cmd_received_cb(g_hMcServer));
	FREE_MEMORY(pszReqID);

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "ServerEnableCmdReceivedCallBack", "CallBack Not Invoked", mc_server_unset_subtitles_cmd_received_cb(g_hMcServer));

	nRet = mc_server_unset_subtitles_cmd_received_cb(g_hMcServer);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_unset_subtitles_cmd_received_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase					ITc_mc_server_set_unset_360_mode_cmd_received_cb_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type					auto
 * @since_tizen					5.5
 * @description					Set and Unsets the callback for receiving 360 mode command from client.
 * @apicovered					mc_server_set_360_mode_cmd_received_cb, mc_server_unset_360_mode_cmd_received_cb
 * @passcase					If Target API is successful
 * @failcase					If Target API Fails
 * @precondition				mc_client_create, mc_server_create
 * @postcondition				mc_client_destroy, mc_server_destroy
 * */
 //& type: auto
//& purpose: Set and Unsets the callback for receiving 360 mode command from client.
int ITc_mc_server_set_unset_360_mode_cmd_received_cb_p(void)
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
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet), mc_server_unset_360_mode_cmd_received_cb(g_hMcServer));

	nRet = mc_client_send_360_mode_cmd(g_hMcClient, g_McServerName, true, &pszReqID);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_360_mode_cmd", MediaControllerGetError(nRet), mc_server_unset_360_mode_cmd_received_cb(g_hMcServer));
	CHECK_HANDLE_CLEANUP(pszReqID, "mc_client_send_360_mode_cmd", mc_server_unset_subtitles_cmd_received_cb(g_hMcServer));
	FREE_MEMORY(pszReqID);

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "mc_client_send_360_mode_cmd", "CallBack Not Invoked", mc_server_unset_360_mode_cmd_received_cb(g_hMcServer));

	nRet = mc_server_unset_360_mode_cmd_received_cb(g_hMcServer);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_unset_subtitles_cmd_received_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 					ITc_mc_server_set_unset_display_mode_cmd_received_cb_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Set and Unsets the callback for receiving display mode command from client.
 * @scenario					Call mc_server_set_display_mode_cmd_received_cb, mc_server_unset_display_mode_cmd_received_cb
 * @apicovered					mc_server_set_display_mode_cmd_received_cb, mc_server_unset_display_mode_cmd_received_cb
 * @passcase					If mc_server_set_display_mode_cmd_received_cb, mc_server_unset_display_mode_cmd_received_cb returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_client_create, mc_server_create
 * @postcondition				mc_client_destroy, mc_server_destroy
 * */
 //& type: auto
//& purpose: Set and Unsets the callback for receiving display mode command from client.
int ITc_mc_server_set_unset_display_mode_cmd_received_cb_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	unsigned int uSetDisplayAbility = MC_DISPLAY_MODE_LETTER_BOX | MC_DISPLAY_MODE_ORIGIN_SIZE | MC_DISPLAY_MODE_FULL_SCREEN | MC_DISPLAY_MODE_CROPPED_FULL;
	char *pszReqID = NULL;
	g_CallBackHit = false;

	nRet = mc_server_set_display_mode_ability(g_hMcServer, uSetDisplayAbility, MC_ABILITY_SUPPORTED_YES);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_display_mode_ability", MediaControllerGetError(nRet));

	nRet = mc_server_set_display_mode_cmd_received_cb(g_hMcServer, DisplayModeCmdReceivedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_display_mode_cmd_received_cb", MediaControllerGetError(nRet));

	nRet = mc_client_get_latest_server_info(g_hMcClient, &g_McServerName, &g_McServerState);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet), mc_server_unset_display_mode_cmd_received_cb(g_hMcServer));

	int nModeSize = sizeof(g_server_eDisplayModeArray)/sizeof(g_server_eDisplayModeArray[0]);

	for(g_nModeIdx = 0; g_nModeIdx < nModeSize; g_nModeIdx++)
	{
		g_CallBackHit = false;
		nRet = mc_client_send_display_mode_cmd(g_hMcClient, g_McServerName, g_server_eDisplayModeArray[g_nModeIdx], &pszReqID);
		PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_display_mode_cmd", MediaControllerGetError(nRet), mc_server_unset_display_mode_cmd_received_cb(g_hMcServer));
		CHECK_HANDLE_CLEANUP(pszReqID, "mc_client_send_display_mode_cmd", mc_server_unset_subtitles_cmd_received_cb(g_hMcServer));
		FREE_MEMORY(pszReqID);

		IterateGmainLoop();
		PRINT_RESULT_CLEANUP(true, g_CallBackHit, "DisplayModeCmdReceivedCallBack", "CallBack Not Invoked", mc_server_unset_display_mode_cmd_received_cb(g_hMcServer));
	}
	nRet = mc_server_unset_display_mode_cmd_received_cb(g_hMcServer);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_unset_display_mode_cmd_received_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 					ITc_mc_server_set_unset_display_rotation_cmd_received_cb_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Set and Unsets the callback for receiving display rotation command from client.
 * @scenario					Call mc_server_set_display_rotation_cmd_received_cb, mc_server_unset_display_rotation_cmd_received_cb
 * @apicovered					mc_server_set_display_rotation_cmd_received_cb, mc_server_unset_display_rotation_cmd_received_cb
 * @passcase					If mc_server_set_display_rotation_cmd_received_cb, mc_server_unset_display_rotation_cmd_received_cb returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_client_create, mc_server_create
 * @postcondition				mc_client_destroy, mc_server_destroy
 * */
 //& type: auto
//& purpose: Set and Unsets the callback for receiving display rotation command from client.
int ITc_mc_server_set_unset_display_rotation_cmd_received_cb_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	unsigned int uSetSupportedRotations = MC_DISPLAY_ROTATION_NONE | MC_DISPLAY_ROTATION_90 | MC_DISPLAY_ROTATION_180 | MC_DISPLAY_ROTATION_270;
	char *pszReqID = NULL;
	g_CallBackHit = false;
	mc_display_rotation_e eSetDisplayRotation = MC_DISPLAY_ROTATION_270; // MC_DISPLAY_ROTATION_NONE, MC_DISPLAY_ROTATION_90 and MC_DISPLAY_ROTATION_180 are not supported

	nRet = mc_server_set_display_rotation_ability(g_hMcServer, uSetSupportedRotations, MC_ABILITY_SUPPORTED_YES);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_display_rotation_ability", MediaControllerGetError(nRet));

	nRet = mc_server_set_display_rotation_cmd_received_cb(g_hMcServer, DisplayRotationCmdReceivedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_display_rotation_cmd_received_cb", MediaControllerGetError(nRet));

	nRet = mc_client_get_latest_server_info(g_hMcClient, &g_McServerName, &g_McServerState);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_get_latest_server_info", MediaControllerGetError(nRet), mc_server_unset_display_rotation_cmd_received_cb(g_hMcServer));

	nRet = mc_client_send_display_rotation_cmd(g_hMcClient, g_McServerName, eSetDisplayRotation, &pszReqID);
	PRINT_RESULT_CLEANUP(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_send_display_rotation_cmd", MediaControllerGetError(nRet), mc_server_unset_display_rotation_cmd_received_cb(g_hMcServer));
	CHECK_HANDLE_CLEANUP(pszReqID, "mc_client_send_display_rotation_cmd", mc_server_unset_subtitles_cmd_received_cb(g_hMcServer));
	FREE_MEMORY(pszReqID);

	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "DisplayRotationCmdReceivedCallBack", "CallBack Not Invoked", mc_server_unset_display_rotation_cmd_received_cb(g_hMcServer));

	nRet = mc_server_unset_display_rotation_cmd_received_cb(g_hMcServer);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_unset_display_rotation_cmd_received_cb", MediaControllerGetError(nRet));

	return 0;
}

/**
 * @testcase 					ITc_mc_server_set_display_mode_ability_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Sets the display mode ability of the media controller.
 * @scenario					Call mc_server_set_display_mode_ability
 * @apicovered					mc_server_set_display_mode_ability
 * @passcase					If mc_server_set_display_mode_ability returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_client_create, mc_server_create
 * @postcondition				mc_client_destroy, mc_server_destroy
 * */
 //& type: auto
//& purpose: Sets the display mode ability of the media controller.
int ITc_mc_server_set_display_mode_ability_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	unsigned int uDisplayMode = MC_DISPLAY_MODE_LETTER_BOX | MC_DISPLAY_MODE_ORIGIN_SIZE | MC_DISPLAY_MODE_FULL_SCREEN | MC_DISPLAY_MODE_CROPPED_FULL;
	g_CallBackHit = false;

	nRet = mc_client_set_display_mode_ability_updated_cb(g_hMcClient, ServerAbilitySupportedItemsUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_display_mode_ability_updated_cb", MediaControllerGetError(nRet));

	nRet = mc_server_set_display_mode_ability(g_hMcServer, uDisplayMode, MC_ABILITY_SUPPORTED_YES);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_display_mode_ability", MediaControllerGetError(nRet));

	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "ServerAbilitySupportedItemsUpdatedCallBack", "CallBack Not Invoked");
	return 0;
}

/**
 * @testcase 					ITc_mc_server_set_display_rotation_ability_p
 * @author					SRID(j.abhishek)
 * @reviewer					SRID(shobhit.v)
 * @type 					auto
 * @since_tizen 				5.5
 * @description					Sets the display rotation ability of the media controller.
 * @scenario					Call mc_server_set_display_rotation_ability
 * @apicovered					mc_server_set_display_rotation_ability
 * @passcase					If mc_server_set_display_rotation_ability returns MEDIA_CONTROLLER_ERROR_NONE.
 * @failcase					If Precondition API or Target API Fails
 * @precondition				mc_client_create, mc_server_create
 * @postcondition				mc_client_destroy, mc_server_destroy
 * */
 //& type: auto
//& purpose: Sets the display rotation ability of the media controller.
int ITc_mc_server_set_display_rotation_ability_p(void)
{
	START_TEST;

	int nRet = MEDIA_CONTROLLER_ERROR_NONE;
	unsigned int uDisplayRotation = MC_DISPLAY_ROTATION_NONE | MC_DISPLAY_ROTATION_90 | MC_DISPLAY_ROTATION_180 | MC_DISPLAY_ROTATION_270;
	g_CallBackHit = false;

	nRet = mc_client_set_display_rotation_ability_updated_cb(g_hMcClient, ServerAbilitySupportedItemsUpdatedCallBack, NULL);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_client_set_display_rotation_ability_updated_cb", MediaControllerGetError(nRet));

	nRet = mc_server_set_display_rotation_ability(g_hMcServer, uDisplayRotation, MC_ABILITY_SUPPORTED_YES);
	PRINT_RESULT(MEDIA_CONTROLLER_ERROR_NONE, nRet, "mc_server_set_display_rotation_ability", MediaControllerGetError(nRet));

	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "ServerAbilitySupportedItemsUpdatedCallBack", "CallBack Not Invoked");

	return 0;
}

/** @} */
/** @} */
