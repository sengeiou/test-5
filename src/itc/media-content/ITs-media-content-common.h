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
#ifndef _ITS_MEDIA_CONTENT_COMMON_H_
#define _ITS_MEDIA_CONTENT_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include "media_content.h"
#include <glib.h>
#include <app.h>
#include <storage.h>
#include <string.h>
#include <system_info.h>

/** @addtogroup itc-media-content
*  @ingroup itc
*  @{
*/

//Add helper function defines here
#define API_NAMESPACE				"MEDIA_CONTENT_ITC"
#define TIMEOUT_CB					15000
#define PATHLEN						1024
#define TESTIMAGE					"TestImage.jpg"
#define TESTTEXT					"TestText.txt"
#define TESTBOOK					"itc_test.pdf"
#define TESTSTRING					"Test"
#define REMOVEIMAGE					"Remove.jpg"
#define TESTAUDIO					"TestAudio.mp3"
#define ALBUMNAME					"Test1"
#define TAGNAME						"TestTag"
#define TAGNAMENEW					"TestTagNew"
#define FOLDERNAME					"TestFolder"
#define FOLDERNAMENEW				"TestFolderNew"
#define FOLDERNAMEIMG				"Images"
#define FOLDERFILE					"TestFolder/TestImage.jpg"
#define BOOKMARKIMAGE				"BookMarkImage.jpg"
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
#define BURSTIMAGE1					"BurstImage1.jpg"
#define BURSTIMAGE2					"BurstImage2.jpg"
#define BURSTIMAGE3					"BurstImage3.jpg"
#define BURSTIMAGE4					"BurstImage4.jpg"
#define BURSTARRAYLENGTH			4
#define TESTTITLE					"TESTTITLE"
#define TESTARTIST					"ABC"
#define TESTGENRE					"COMEDY"
#define DATE						"21OCT"
#define FACE_DETECTION	"http://tizen.org/feature/vision.face_recognition"
#define SCAN_FEATURE  	"http://tizen.org/feature/content.scanning.others"

#define START_TEST {\
	FPRINTF("Starting test : %s\\n",__FUNCTION__);\
	if ( !g_bMediaContentStartup )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of Media-Content failed so leaving test\\n",__LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

bool g_bIsScanFeatureSupported;
bool g_bIsScanFeatureNotSupported;
bool g_bScanFeatureMismatch;
static char* pszMediaId;
static book_meta_h g_hBook;
static book_meta_h g_hBookDst;

#define START_TEST_PLAYLIST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bScanFeatureMismatch )\
	{\
		FPRINTF("[Line : %d][%s] Feature support as returned and error code as returned by media_content_scan_file() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
	else if ( g_bIsScanFeatureNotSupported )\
	{\
		FPRINTF("[Line : %d][%s] Content scanning others feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
	if ( !g_bMediaContentStartup )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of Media-Content failed so leaving test\\n",__LINE__, API_NAMESPACE);\
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

#define CHECK_COUNT_CLEANUP(Value, API, FreeResource) {\
	if ( Value < 0 )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Value returned is incorrect\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

#define CHECK_COUNT(Value, API) {\
	if ( Value < 0 )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Value returned is incorrect\\n", __LINE__, API_NAMESPACE, API);\
		return 1;\
	}\
}

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

#define PRINT_RESULTFALSE(eCompare, eRetVal, API, Error) {\
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
		return false;\
	}\
}

//Add global variables here
bool g_bMediaContentStartup;
bool g_CallBackHit;
int g_nTimeoutId;
GMainLoop *g_pMainLoop;
int g_nInternalStorageId;
char g_szInternalStoragePath[PATHLEN];
char g_szImagePath[PATHLEN];
char g_szTextPath[PATHLEN];
char g_szBookPath[PATHLEN];
char g_szImageFolder[PATHLEN];
char g_szTextFolder[PATHLEN];
char g_szAudioPath[PATHLEN];
char g_szFolderFilePath[PATHLEN];
media_album_h g_hAlbum;
media_tag_h g_hTag;
char g_szMediaId[PATHLEN];
int g_nTagId;
media_folder_h g_hFolder;
media_bookmark_h g_hBookmark;
int g_nBookmarkId;
char *g_pszFaceId;
char g_szVideoFolder[PATHLEN];
char g_szVideoPath[PATHLEN];
char g_szAudioFolder[PATHLEN];
media_playlist_h g_hPlaylist;
int g_nPlaylistId;
int g_nPlaylistMemberId;
char g_szPlayListPath[PATHLEN];
filter_h g_hFilter;
char g_szStorageId[PATHLEN];
media_info_h g_hAudioInfo;
media_info_h g_hTextInfo;
media_info_h g_hBookInfo;
media_info_h g_hVideoInfo;
media_info_h g_hImageInfo;
media_face_h g_hFace;
char g_szAudioId[PATHLEN];
char g_szVideoId[PATHLEN];
char g_szImageId[PATHLEN];
char g_szBurstImagePath[BURSTARRAYLENGTH][PATHLEN];
char *g_pszBurstImagePointer[BURSTARRAYLENGTH];
char g_szFinalPath[PATHLEN];
audio_meta_h g_hAudioMeta;
video_meta_h g_hVideoMeta;
image_meta_h g_hImageMeta;

char g_szExternalImagePath[PATHLEN];
char g_szExternalStoragePath[PATHLEN];
int g_nExternalStorageId;

//Add helper function declarations here
char* MediaContentGetError(int nRet);
char* StorageGetError(storage_error_e nRet);
gboolean TimeoutFunction(gpointer data);
void IterateGmainLoop(void);
void QuitGmainLoop(void);
bool GetInternalStorageIdandPath(void);
void AppendPaths(char *FirstPath, char *SecondPath, char *FinalPath);
bool GetFolderPath(int WhichFolder, char *FinalPath);
void AppendSlash(char *FirstPath, char *FinalPath);
bool DeleteAllMedia(void);
bool GetExternalStorageIdandPath(void);
void RemoveFileInfo(const char *data);
void CopyFileInfo(const char *data);

/** @} */
#endif  //_ITS_MEDIA_CONTENT_COMMON_H_
