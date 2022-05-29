#include "CTs-platform-permission-common.h"
#include "assert.h"
#include "tct_common.h"
#include "media_content.h"
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <glib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <app.h>
#include <storage.h>

#define TIMEOUT_CB					30000
#define ERR_LOG 					"/tmp/tclog"

#define PATH_LEN					1024

#define GMAINTIMEOUT				30000 		//30 seconds
#define HIDDENFOLDERPATH			"/NewName/.hide/testing"
#define TESTFOLDERPATH				"/test"
#define DEFAULTFOLDERPATH			"/Videos"
#define DUMMY						"/Dummy"
#define TESTITEMPATH				"/test1.jpg"
#define INSERTPATH					"/test.jpg"
#define INSERTPATHALBUM				"/test3.jpg"
#define INSERTPATHINFO				"/test2.jpg"
#define INSERTPATHVIDEO				"/Camera/20140709-115007.mp4"
#define INSERTPATHAUDIO				"/TestRingtone.mp3"


#define PATHLEN						1024
#define TESTIMAGE					"TestImage.jpg"
#define TESTSTRING					"Test"
#define TESTAUDIO					"TestAudio.mp3"
#define TAGNAME						"TestTag"
#define TAGNAMENEW					"TestTagNew"
#define FOLDERNAME					"TestFolder"
#define FOLDERNAMENEW				"TestFolderNew"
#define FOLDERNAMEIMG				"Images"
#define FOLDERFILE					"TestFolder/TestImage.jpg"
#define TESTVIDEO					"TestVideo.mp4"
#define PLAYLISTNAME				"TESTPLAYLIST"
#define PLAYLISTNAMENEW				"TESTPLAYLISTNEW"
#define THUMBNAILIMAGE				"ThumbNailImage.jpg"
#define TESTPLAYLIST				"TestPlaylist.m3u"
#define FILTERCONDITION				"MEDIA_TYPE=1"
#define TESTRATING					"TestRating"
#define TESTAUTHOR					"author:TestAuthor"
#define TESTCATEGORY				"TestCategory"
#define TESTCONTENT					"content:TestContent"
#define TESTDESCRIPTION				"TestDescription"
#define TESTDISPLAYNAME				"TestDisplayName"
#define TESTKEYWORD					"TestKeyword"
#define TESTLOCATIONTAG				"TestLocationTag"
#define TESTPROVIDER				"TestProvider"
#define TESTWEATHER					"weather set : ok"


#define FREE_MEMORY(buffer) {\
	if ( buffer != NULL )\
{\
	free(buffer);\
	buffer = NULL;\
}\
}

media_playlist_h g_stHandlePlaylist = NULL;
media_info_h g_stHandleInfo = NULL;
media_info_h g_stImage = NULL;
media_info_h g_stVideo = NULL;
media_info_h g_stAudio = NULL;
audio_meta_h g_pstAudioMetaHandle = NULL;
video_meta_h g_pstVideoMetaHandle = NULL;
image_meta_h g_pstImageMetaHandle = NULL;
media_tag_h g_stHandleMediaTag = NULL;

bool g_bMediaCreation = false;
bool g_bMediaContentCBFlag = false;
int g_nPlaylistId = 0;
char* g_pMediaId = NULL;
char* g_pMediaImageId = NULL;
char* g_pMediaVideoId = NULL;
char* g_pMediaAudioId = NULL;

GMainLoop *g_loop;
int g_nStorageId = 0;
bool g_bStorageFound = false;

char g_strStorageInternalLocation[PATH_LEN];
char g_strSystemRingtones[PATH_LEN];
char g_strSystemImages[PATH_LEN];
char g_strSystemSound[PATH_LEN];
char g_strSystemSoundFolder[PATH_LEN];
char g_strSystemVideos[PATH_LEN];
char g_strSystemCamera[PATH_LEN];
char g_strSystemCam[PATH_LEN];
char g_strHiddenFolderPath[PATH_LEN];
char g_strTestItemPath[PATH_LEN];
char g_strInsertPath[PATH_LEN];
char g_strInsertPathAlbum[PATH_LEN];
char g_strInsertPathInfo[PATH_LEN];
char g_strSystemDownloads[PATH_LEN];
char g_strSystemOthers[PATH_LEN];
char g_strDummyPath[PATH_LEN];


//Add global variables here
bool g_bMediaContentStartup;
bool g_CallBackHit;
int g_nTimeoutId;
GMainLoop *g_pMainLoop;
int g_nInternalStorageId;
char g_szInternalStoragePath[PATHLEN];
char g_szImagePath[PATHLEN];
char g_szImageFolder[PATHLEN];
char g_szAudioPath[PATHLEN];
char g_szFolderFilePath[PATHLEN];
char g_szMediaId[PATHLEN];

media_folder_h g_hFolder;

char g_szVideoFolder[PATHLEN];
char g_szVideoPath[PATHLEN];
char g_szAudioFolder[PATHLEN];
media_playlist_h g_hPlaylist;
int g_nPlaylistId;

char g_szPlayListPath[PATHLEN];
filter_h g_hFilter;
char g_szStorageId[PATHLEN];
media_info_h g_hAudioInfo;
media_info_h g_hVideoInfo;
media_info_h g_hImageInfo;
char g_szAudioId[PATHLEN];
char g_szVideoId[PATHLEN];
char g_szImageId[PATHLEN];

media_face_h g_hFace;

#define PRINT_RESULTFALSE_CLEANUP(eCompare, eRetVal, API, Error, FreeResource) {\
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
		return false;\
	}\
}
/**
 * @function 		MediaGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
char* MediaGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch(nRet)
	{		
		case MEDIA_CONTENT_ERROR_NONE : 				szErrorVal = "MEDIA_CONTENT_ERROR_NONE" ; break;
		case MEDIA_CONTENT_ERROR_DB_FAILED : 			szErrorVal = "MEDIA_CONTENT_ERROR_DB_FAILED" ; break;
		case MEDIA_CONTENT_ERROR_INVALID_PARAMETER : 	szErrorVal = "MEDIA_CONTENT_ERROR_INVALID_PARAMETER" ; break;
		case MEDIA_CONTENT_ERROR_OUT_OF_MEMORY : 		szErrorVal = "MEDIA_CONTENT_ERROR_OUT_OF_MEMORY" ; break;
		case MEDIA_CONTENT_ERROR_INVALID_OPERATION :	szErrorVal = "MEDIA_CONTENT_ERROR_INVALID_OPERATION" ; break;
		case MEDIA_CONTENT_ERROR_DB_BUSY : 				szErrorVal = "MEDIA_CONTENT_ERROR_DB_BUSY" ; break;
		case MEDIA_CONTENT_ERROR_NETWORK : 				szErrorVal = "MEDIA_CONTENT_ERROR_NETWORK" ; break;
		case MEDIA_CONTENT_FILE_NO_SPACE_ON_DEVICE:		szErrorVal = "MEDIA_CONTENT_FILE_NO_SPACE_ON_DEVICE" ; break;
		case MEDIA_CONTENT_ERROR_UNSUPPORTED_CONTENT:	szErrorVal = "MEDIA_CONTENT_ERROR_UNSUPPORTED_CONTENT" ; break;
		case MEDIA_CONTENT_ERROR_NOT_SUPPORTED:			szErrorVal = "MEDIA_CONTENT_ERROR_NOT_SUPPORTED" ; break;
		case MEDIA_CONTENT_ERROR_PERMISSION_DENIED:		szErrorVal = "MEDIA_CONTENT_ERROR_PERMISSION_DENIED" ; break;
		default : 										szErrorVal = "MEDIA_CONTENT_ERROR_UNKNOWN" ; break;
	}
	return szErrorVal;
}
/**
* @function 		IterateGmainLoop
* @description	 	Called to wait
* @parameter		NA
* @return 			NA
*/
void IterateGmainLoop(void)
{
	if(g_CallBackHit == false)
	{
		g_pMainLoop = g_main_loop_new(NULL, false);
		g_nTimeoutId = g_timeout_add(TIMEOUT_CB, TimeoutFunction, NULL);
		g_main_loop_run(g_pMainLoop);

		g_source_remove(g_nTimeoutId);
		g_nTimeoutId = 0;

		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}
/**
* @function 		StorageGetErrorMedia
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* StorageGetErrorMedia(storage_error_e nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case STORAGE_ERROR_NONE:				szErrorVal = "STORAGE_ERROR_NONE";					break;
		case STORAGE_ERROR_INVALID_PARAMETER:	szErrorVal = "STORAGE_ERROR_INVALID_PARAMETER";		break;
		case STORAGE_ERROR_OUT_OF_MEMORY:		szErrorVal = "STORAGE_ERROR_OUT_OF_MEMORY";			break;
		case STORAGE_ERROR_NOT_SUPPORTED:		szErrorVal = "STORAGE_ERROR_NOT_SUPPORTED";			break;
		case STORAGE_ERROR_OPERATION_FAILED:	szErrorVal = "STORAGE_ERROR_OPERATION_FAILED";		break;
		default:								szErrorVal = "Unknown Error";						break;
	}
	return szErrorVal;
}

/**
* @function 		QuitGmainLoopMedia
* @description	 	Called to quit
* @parameter		NA
* @return 			NA
*/
void QuitGmainLoopMedia(void)
{
	if(g_pMainLoop)
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

/**
 * @function 		StorageForeachCallBack
 * @description	 	Callback Function
 * @parameter		int storage_id, storage_type_e type, storage_state_e state, const char* path, void* user_data
 * @return 			NA
 */
static bool StorageForeachCallBack(int storage_id, storage_type_e type, storage_state_e state, const char* path, void* user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "StorageForeachCallBack");
#endif

	if ( type == STORAGE_TYPE_INTERNAL )
	{
		g_nInternalStorageId = storage_id;
		memset(g_szInternalStoragePath, 0, PATHLEN);
		strncpy(g_szInternalStoragePath, path, PATHLEN -1 );
		g_CallBackHit = true;
		QuitGmainLoopMedia();
		return false;
	}

	return true;
}

/**
 * @function 		FolderScanCompletedCb
 * @description	 	Callback Function
 * @parameter		media_content_error_e error, void* user_data
 * @return 			NA
 */
static void FolderScanCompletedCb(media_content_error_e error, void* user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "FolderScanCompletedCb");
#endif

	g_CallBackHit = true;
	QuitGmainLoopMedia();
	return;
}


/**
* @function 		GetInternalStorageIdandPath
* @description	 	Called to get internal storage id and path
* @parameter		NA
* @return 			NA
*/
bool GetInternalStorageIdandPath(void)
{
	g_CallBackHit = false;
	int nRet = storage_foreach_device_supported(StorageForeachCallBack, NULL);
	PRINT_RESULT(STORAGE_ERROR_NONE, nRet, "storage_foreach_device_supported", StorageGetErrorMedia(nRet));

	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "storage_foreach_device_supported", "CallBack Not Invoked");

	return 0;
}

/**
* @function 		MediaInfoCB
* @description	 	Called for every available media info
* @parameter		media : The handle to media info, user_data value : The user data passed from the foreach function
* @return 			boolean value
*/
bool MediaInfoCB(media_info_h media, void* user_data)
{
	g_bMediaContentCBFlag = true;
	media_content_type_e type = 0;
	char* name = NULL;
	media_info_get_media_type(media, &type);
	media_info_get_display_name(media, &name);
	if ( g_stImage == NULL && type == MEDIA_CONTENT_TYPE_IMAGE )
	{
		FPRINTF("[Line: %d][%s] MEDIA_CONTENT_TYPE_IMAGE\\n", __LINE__, API_NAMESPACE);
		FPRINTF("[Line: %d][%s] media name: %s\\n", __LINE__, API_NAMESPACE, name);
		media_info_clone(&g_stImage, media);
		media_info_clone(&g_stHandleInfo, media);
		media_info_get_media_id(media, &g_pMediaImageId);
		media_info_get_media_id(media, &g_pMediaId);
		media_info_get_image(media, &g_pstImageMetaHandle);
	}

	if ( g_stVideo == NULL && type == MEDIA_CONTENT_TYPE_VIDEO )
	{
		FPRINTF("[Line: %d][%s] MEDIA_CONTENT_TYPE_VIDEO\\n", __LINE__, API_NAMESPACE);
		FPRINTF("[Line: %d][%s] media name: %s\\n", __LINE__, API_NAMESPACE, name);
		media_info_clone(&g_stVideo, media);
		media_info_get_media_id(media, &g_pMediaVideoId);
		media_info_get_media_id(media, &g_pMediaId);
		media_info_get_video(media, &g_pstVideoMetaHandle);
	}
	if ( g_stAudio == NULL && type == MEDIA_CONTENT_TYPE_MUSIC )
	{
		FPRINTF("[Line: %d][%s] MEDIA_CONTENT_TYPE_MUSIC\\n", __LINE__, API_NAMESPACE);
		FPRINTF("[Line: %d][%s] media name: %s\\n", __LINE__, API_NAMESPACE, name);
		media_info_clone(&g_stAudio, media);
		media_info_clone(&g_stHandleInfo, media);
		media_info_get_media_id(media, &g_pMediaAudioId);
		media_info_get_media_id(media, &g_pMediaId);
		media_info_get_audio(media, &g_pstAudioMetaHandle);
	}
	if ( g_stAudio == NULL && type == MEDIA_CONTENT_TYPE_SOUND )
	{
		FPRINTF("[Line: %d][%s] MEDIA_CONTENT_TYPE_SOUND\\n", __LINE__, API_NAMESPACE);
		FPRINTF("[Line: %d][%s] media name: %s\\n", __LINE__, API_NAMESPACE, name);
		media_info_clone(&g_stAudio, media);
		media_info_clone(&g_stHandleInfo, media);
		media_info_get_media_id(media, &g_pMediaAudioId);
		media_info_get_audio(media, &g_pstAudioMetaHandle);
		media_info_get_media_id(media, &g_pMediaId);
	}
	if ( g_stHandleInfo == NULL && type == MEDIA_CONTENT_TYPE_OTHERS )
	{
		FPRINTF("[Line: %d][%s] MEDIA_CONTENT_TYPE_OTHERS\\n", __LINE__, API_NAMESPACE);
		FPRINTF("[Line: %d][%s] media name: %s\\n", __LINE__, API_NAMESPACE, name);
		media_info_clone(&g_stHandleInfo, media);
		media_info_get_media_id(media, &g_pMediaId);
	}
	
	if ( g_loop != NULL )
	{
		g_main_loop_quit(g_loop);
		g_loop = NULL;
	}
	return true;
}

/**
* @function 		MediaContentInsertBatchCB
* @description	 	Called when media items are inserted completely.
* @parameter		media : The handle to media info, user_data value : The user data passed from the foreach function
* @return 			NA
*/
void MediaContentInsertBatchCB(media_content_error_e error, void* user_data)
{
	FPRINTF("[Line: %d][%s] MediaContentInsertBatchCB media item inserted completely\\n", __LINE__, API_NAMESPACE);
	g_bMediaContentCBFlag = true;
		
	g_CallBackHit = true;
	QuitGmainLoopMedia();
	return;
}

/**
* @function 		GetFolderPath
* @description	 	Get Specific Folder Path
* @parameter		NA
* @return 			NA
*/
bool GetFolderPath(int WhichFolder, char *FinalPath)
{
	char* pszTempPath = NULL;
	int nRet = storage_get_directory(g_nInternalStorageId, WhichFolder, &pszTempPath);
	PRINT_RESULT(STORAGE_ERROR_NONE, nRet, "storage_get_directory", StorageGetErrorMedia(nRet));
	CHECK_HANDLE(pszTempPath, "storage_get_directory");

	memset(FinalPath, 0, PATHLEN);
	strncpy(FinalPath, pszTempPath, strlen(pszTempPath)-1);
	FREE_MEMORY(pszTempPath);

	FPRINTF("[Line : %d][%s] Folder Path is : %s\\n", __LINE__, API_NAMESPACE, FinalPath);
	return 0;
}


/**
* @function 		AppendPaths
* @description	 	Join 2 paths
* @parameter		NA
* @return 			NA
*/
void AppendPaths(char *FirstPath, char *SecondPath, char *FinalPath)
{
	memset(FinalPath, 0, PATHLEN);
	strncpy(FinalPath, FirstPath, strlen(FirstPath)+1);
	strncat(FinalPath, "/", strlen("/")+1);
	strncat(FinalPath, SecondPath, strlen(SecondPath)+1);

	FPRINTF("[Line : %d][%s] Appended Path is : %s\\n", __LINE__, API_NAMESPACE, FinalPath);
}

/**
* @function 		CTs_platform_permission_mediacontent_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_mediacontent_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}
	
	
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_mediacontent_startup\\n", __LINE__, API_NAMESPACE);
#endif

	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
	int nRet = media_content_connect();
	if ( nRet == MEDIA_CONTENT_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] media_content_connect passed\\n", __LINE__, API_NAMESPACE);
		g_bMediaCreation = true;
	}
	else
	{
		FPRINTF("[Line: %d][%s] media_content_connect failed, error returned = %s\\n", __LINE__, API_NAMESPACE, MediaGetError(nRet));
		g_bMediaCreation = false;
	}
	
	
}

/**
* @function 		CTs_platform_permission_mediacontent_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_mediacontent_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_mediacontent_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
		
	if ( g_bMediaCreation )
	{
		int nRet = media_content_disconnect();
		if ( nRet == MEDIA_CONTENT_ERROR_NONE )
		{
			FPRINTF("[Line: %d][%s] media_content_disconnect passed\\n", __LINE__, API_NAMESPACE);
		}
		else
		{
			FPRINTF("[Line: %d][%s] media_content_disconnect failed, error returned = %s\\n", __LINE__, API_NAMESPACE, MediaGetError(nRet));
		}
	}
	else
	{
		FPRINTF("[Line: %d][%s] media_content_connect failed\\n", __LINE__, API_NAMESPACE);
	}
}

//& purpose: Checking tizen.org/privilege/mediastorage privilege
//& type: auto
/**
* @testcase			CTc_MediaContent_PrivilegeMediaStorage_scan_folder
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Connects to the media content service\n
* 					Requests to scan a media folder\n
* 					Disconnects from the media content service
* @apicovered		media_content_connect, 	media_content_scan_folder, media_content_disconnect
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		NA
* @postcondition	NA
*/
int CTc_MediaContent_PrivilegeMediaStorage_scan_folder(void)
{
	START_TEST;

	int nRet = GetInternalStorageIdandPath();
	PRINT_RESULT(0, nRet, "GetInternalStorageId", "Return Value Not Correct");

	nRet = GetFolderPath(STORAGE_DIRECTORY_IMAGES, g_szImageFolder);
	PRINT_RESULT(0, nRet, "GetFolderPath", "Return Value Not Correct");

	g_CallBackHit = false;
	nRet = media_content_scan_folder(g_szImageFolder, false, FolderScanCompletedCb, TESTSTRING);
	
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "media_content_scan_folder", MediaGetError(nRet));
	
	
	return 0;
}

//& purpose: Checking tizen.org/privilege/ContentWrite privilege
//& type: auto
/**
* @testcase			CTc_MediaContent_PrivilegeContentWrite_media_info_insert_to_db
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			insert to DB 
* @apicovered		media_info_insert_to_db
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		Insert an external storage micro SD/ SD Card
* @postcondition	NA
*/
int CTc_MediaContent_PrivilegeContentWrite_media_info_insert_to_db(void)
{
	START_TEST;
	
	int nRet = GetInternalStorageIdandPath();
	PRINT_RESULT_CLEANUP(0, nRet, "GetInternalStorageId", "Return Value Not Correct", media_content_disconnect());

	nRet = GetFolderPath(STORAGE_DIRECTORY_MUSIC, g_szAudioFolder);
	PRINT_RESULT(0, nRet, "GetFolderPath", MediaGetError(nRet));
	AppendPaths(g_szAudioFolder, TESTAUDIO, g_szAudioPath);
	
	nRet = media_info_insert_to_db(g_szAudioPath, &g_hAudioInfo);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "media_info_insert_to_db", MediaGetError(nRet),media_info_destroy(g_hAudioInfo),MEDIA_CONTENT_ERROR_NONE);
			
	return 0;
}


//& purpose: Checking tizen.org/privilege/ContentWrite privilege
//& type: auto
/**
* @testcase			CTc_MediaContent_PrivilegeContentWrite_media_info_insert_batch_to_db
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Open connection to content service\n
*					Inserts media files into the media database, asynchronously\n
*					Deletes media files from the media database\n
*					Destroy the media info handle\n
*					Close connection to content service
* @apicovered		media_info_insert_batch_to_db, media_info_delete_batch_from_db,
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		Insert an external storage micro SD/ SD Card
* @postcondition	NA
*/
int CTc_MediaContent_PrivilegeContentWrite_media_info_insert_batch_to_db(void)
{
	START_TEST;
	filter_h stFilter = NULL;
	
	int nRet = GetInternalStorageIdandPath();
	PRINT_RESULT(0, nRet, "GetInternalStorageIdandPath", MediaGetError(nRet));

	nRet = GetFolderPath(STORAGE_DIRECTORY_MUSIC, g_szAudioFolder);
	PRINT_RESULT(0, nRet, "GetFolderPath", MediaGetError(nRet));
	AppendPaths(g_szAudioFolder, TESTAUDIO, g_szAudioPath);
		
	nRet = GetFolderPath(STORAGE_DIRECTORY_IMAGES, g_szImageFolder);
	PRINT_RESULT(0, nRet, "GetFolderPath", MediaGetError(nRet));
	AppendPaths(g_szImageFolder, TESTIMAGE, g_szImagePath);
	
	nRet = GetFolderPath(STORAGE_DIRECTORY_VIDEOS, g_szVideoFolder);
	PRINT_RESULT(0, nRet, "GetFolderPath", MediaGetError(nRet));
	AppendPaths(g_szVideoFolder, TESTVIDEO, g_szVideoPath);
	
	const char *pszInsertPathList[3] = {
		g_szAudioPath,
		g_szImagePath,
		g_szVideoPath 
	};
	
	nRet = media_info_foreach_media_from_db(NULL, MediaInfoCB,NULL);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_foreach_media_from_db", MediaGetError(nRet));
	
	nRet = media_filter_create(&stFilter);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_create", MediaGetError(nRet));
	
	nRet = media_filter_set_condition(stFilter, "MEDIA_TYPE=0 OR MEDIA_TYPE=1 OR MEDIA_TYPE=3", MEDIA_CONTENT_COLLATE_NOCASE);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_set_condition", MediaGetError(nRet));
		
	nRet = media_info_insert_batch_to_db(pszInsertPathList, sizeof(pszInsertPathList) / sizeof(*pszInsertPathList), MediaContentInsertBatchCB, NULL);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "media_info_insert_batch_to_db", MediaGetError(nRet),media_filter_destroy(stFilter),MEDIA_CONTENT_ERROR_NONE);
				
	return 0;
}

//& purpose: Checking tizen.org/privilege/ContentWrite privilege
//& type: auto
/**
* @testcase			CTc_MediaContent_PrivilegeContentWrite_media_playlist_insert_to_db
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			insert media playlist to db
* @apicovered		media_playlist_insert_to_db
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		Insert an external storage micro SD/ SD Card
* @postcondition	NA
*/
int CTc_MediaContent_PrivilegeContentWrite_media_playlist_insert_to_db(void)
{
	START_TEST;
	g_bMediaContentStartup = false;
	
	int nRet = GetInternalStorageIdandPath();
	PRINT_RESULT(0, nRet, "GetInternalStorageIdandPath", MediaGetError(nRet));

	nRet = GetFolderPath(STORAGE_DIRECTORY_MUSIC, g_szAudioFolder);
	PRINT_RESULT(0, nRet, "GetFolderPath", MediaGetError(nRet));
	AppendPaths(g_szAudioFolder, TESTAUDIO, g_szAudioPath);

	nRet = media_playlist_insert_to_db(PLAYLISTNAME, &g_hPlaylist);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "media_playlist_insert_to_db", MediaGetError(nRet));
	
	return 0;
}

//& purpose: Checking tizen.org/privilege/ContentWrite privilege
//& type: auto
/**
* @testcase			CTc_MediaContent_PrivilegeContentWrite_media_tag_insert_to_db
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			insert media tag to db
* @apicovered		media_tag_insert_to_db
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		Insert an external storage micro SD/ SD Card
* @postcondition	NA
*/
int CTc_MediaContent_PrivilegeContentWrite_media_tag_insert_to_db(void)
{
	START_TEST;
	media_tag_h stHandleMediaTag = NULL;
	
	g_bMediaContentStartup = false;
	
	int nRet = GetInternalStorageIdandPath();
	PRINT_RESULT(0, nRet, "GetInternalStorageIdandPath", MediaGetError(nRet));

	nRet = GetFolderPath(STORAGE_DIRECTORY_IMAGES, g_szImageFolder);
	PRINT_RESULT(0, nRet, "GetFolderPath", MediaGetError(nRet));
	AppendPaths(g_szImageFolder, TESTIMAGE, g_szImagePath);

	nRet = media_tag_insert_to_db(TAGNAME, &stHandleMediaTag);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "media_tag_insert_to_db", MediaGetError(nRet));
	
	return 0;
}

