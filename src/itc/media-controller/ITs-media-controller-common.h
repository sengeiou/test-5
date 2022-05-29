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
#ifndef _ITS_MEDIA_CONTROLLER_COMMON_H_
#define _ITS_MEDIA_CONTROLLER_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <media_controller_client.h>
#include <media_controller_server.h>
#include <media_controller_type.h>
#include <media_controller_metadata.h>
#include "ITs-media-controller-common.h"
#include <glib.h>
#include <Ecore.h>
#include <string.h>

/** @addtogroup itc-media-controller
*  @ingroup itc
*  @{
*/
//Add test package related defines here
#define API_NAMESPACE			"MEDIA_CONTROLLER_ITC"
#define PLAYBACKPOSITION		1000
#define PATHLEN					1024
#define TESTCOMMAND				"Test"
#define TIMEOUT_CB				15000
#define META_W					320
#define META_H					240

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bMediaControllerCreation )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of media-controller failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

#define CHECK_HANDLE_NONE(Handle, API) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		return;\
	}\
}

#define PRINT_RESULTNONE_CLEANUP(eCompare, eRetVal, API, Error, FreeResource) {\
	if ( eRetVal == eCompare )\
	{\
		if ( DEBUG )\
		{\
			FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
		}\
	}\
	else \
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, Error, eRetVal);\
		FreeResource;\
		return;\
	}\
}

#define PRINT_RESULTNONE(eCompare, eRetVal, API, Error) {\
	if ( eRetVal == eCompare )\
	{\
		if ( DEBUG )\
		{\
			FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
		}\
	}\
	else \
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, Error, eRetVal);\
		return;\
	}\
}

//Add test package related global variables here
bool g_CallBackHit;
bool g_bMediaControllerCreation;
mc_server_h g_hMcServer;
mc_client_h g_hMcClient;
mc_search_h g_hMcSearch;
char g_szServerName[PATHLEN];
char g_szClientName[PATHLEN];
int g_nTimeoutId;
GMainLoop *g_pMainLoop;
const static char *g_szPlaylistName = "test_playlist";
static char *g_request_id = NULL;
static char *g_mcTestAppName = "org.tizen.media-controller-native-itc";
int g_nModeIdx;
int g_nRotationIdx;

//Add callback function declarations here
void ServerPlayBackActionCallBack(const char* client_name, const char *request_id, mc_playback_action_e action, void *user_data);
void ServerRepeateModeCommandReceivedCallBack(const char* client_name, const char *request_id, mc_repeat_mode_e repeat_mode, void *user_data);
void ServerShufleModeCommandReceivedCallBack(const char* client_name, const char *request_id, mc_shuffle_mode_e shuffle_mode, void *user_data);
void ServerPositionCommandReceivedCallBack(const char* client_name, const char *request_id, unsigned long long position, void *user_data);
void ServerPlaylistCommandReceivedCallback(const char* client_name, const char *request_id, const char *playlist_name, const char *index, mc_playback_action_e action, unsigned long long position, void *user_data);
void ServerCustomCommandReceivedCallback(const char client_name, const char *request_id, const char *command, bundle *data, void *user_data);
void ClientServerStateUpdatedCallBack(const char *server_name, mc_server_state_e state, void *user_data);
void ClientPlayBackUpdatedCallBack(const char *server_name, mc_playback_h playback, void *user_data);
void ClientMetadataUpdatedCallBack(const char *server_name, mc_metadata_h metadata, void *user_data);
void ClientShuffleModeUpdatedCallBack(const char *server_name, mc_shuffle_mode_e mode, void *user_data);
void ClientRepeatModeUpdatedCallBack(const char *server_name, mc_repeat_mode_e mode, void *user_data);
void ClientCustomComandReplyCallBack(const char *server_name, const char *request_id, int result_code, bundle *data, void *user_data);
void EventReceivedCallback(const char *object_name, const char *request_id, int result_code, bundle *data, void *user_data);
bool McActivatedClientCb(const char *client_name, void *user_data);
void ClientMcPlaylistUpdatedCallBack(const char *server_name, mc_playlist_update_mode_e mode, const char *playlist_name, mc_playlist_h playlist, void *user_data);
int  ClientMcRegisterPlaylist(mc_playlist_h *playlist);
int  ServerMcRegisterPlaylist(mc_playlist_h *playlist);
bool ServerPlaylistItemCallback(const char *index, mc_metadata_h meta, void *user_data);
void ClientPlaybackAbilityUpdatedCallBack(const char *server_name, mc_playback_ability_h ability, void *user_data);
void ClientShuffleAbilityUpdatedCallBack(const char *server_name, mc_ability_support_e support, void *user_data);
void ClientRepeatAbilityUpdatedCallBack(const char *server_name, mc_ability_support_e support, void *user_data);
bool McSearchConditionCallBack(mc_content_type_e content_type, mc_search_category_e category, const char *search_keyword, bundle *data, void *user_data);
void McServerSearchCmdReceivedCallBack(const char *client_name, const char *request_id, mc_search_h search, void *user_data);
void ServerEnableCmdReceivedCallBack(const char *pszClientName, const char *pszReqID, bool bIsEnabled, void *pszData);

//Add helper function declarations here
char* MediaControllerGetError(int nRet);
gboolean TimeoutFunction(gpointer data);
void IterateGmainLoop(void);
void QuitGmainLoop(void);
bool SetServerPlayBackInfo(void);
bool SetServerMetaData(void);
bool UpdateServerModes(void);
bool CreateCompleteServer(void);
bool GetCompleteServerInfo(void);
bool SetUpdateCallBacks(mc_subscription_type_e eSubscriptionType);
bool UnSetUpdateCallBacks(mc_subscription_type_e eSubscriptionType);
int ClientGetDisplayModeAbility(unsigned int SupportedModes);
int ClientGetDisplayRotationAbility(unsigned int SupportedRotations);

/** @} */
#endif  //_ITS_MEDIA_CONTROLLER_COMMON_H_
