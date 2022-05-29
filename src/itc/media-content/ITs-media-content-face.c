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
#include "ITs-media-content-common.h"

//& set: MediaContent

/**
 * @function 		MediaFaceDetectionCompletedCB
 * @description	 	Callback Function
 * @parameter		media_content_error_e error, int face_count, void* user_data
 * @return 			NA
 */
static void MediaFaceDetectionCompletedCB(media_content_error_e error, const int face_count, void *user_data)
{

	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "MediaFaceDetectionCompletedCB");


	g_CallBackHit = true;
	QuitGmainLoop();
	return;
}

static bool MediaFaceForeachCB(media_face_h face, void *user_data)
{
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "MediaFaceForeachCB");
	char *face_id = NULL;

	if (face)
	{
		media_face_get_face_id(face, &face_id);
	}

	if (face_id)
	{
		free(face_id);
		face_id = NULL;
	}

	g_CallBackHit = true;
	QuitGmainLoop();
	return true;
}

/**
 * @function 		ITs_media_content_face_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_face_startup(void)
{
struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	char *pszMediaId = NULL;
	g_bMediaContentStartup = false;
	g_bIsScanFeatureSupported = false;
	g_bIsScanFeatureNotSupported = false;
	g_bScanFeatureMismatch= false;

	g_bIsScanFeatureSupported = TCTCheckSystemInfoFeatureSupported(SCAN_FEATURE, API_NAMESPACE);

	int nRet = media_content_connect();
	PRINT_RESULTNONE(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_connect", MediaContentGetError(nRet));

	nRet = GetInternalStorageIdandPath();
	PRINT_RESULTNONE_CLEANUP(0, nRet, "GetInternalStorageId", "Return Value Not Correct", media_content_disconnect());

	nRet = GetFolderPath(STORAGE_DIRECTORY_IMAGES, g_szImageFolder);
	PRINT_RESULTNONE_CLEANUP(0, nRet, "GetFolderPath", "Return Value Not Correct", media_content_disconnect());
	CopyFileInfo("image");

	AppendPaths(g_szInternalStoragePath, TESTTEXT, g_szTextPath);
	nRet = media_info_insert_to_db(g_szTextPath, &g_hTextInfo);
	if ( !g_bIsScanFeatureSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			g_bScanFeatureMismatch = true;
		}
		else
		{
			g_bIsScanFeatureNotSupported = true;
		}
		media_content_disconnect();
		return;
	}
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_insert_to_db", MediaContentGetError(nRet), media_content_disconnect());

	AppendPaths(g_szImageFolder, TESTIMAGE, g_szImagePath);
	nRet = media_info_insert_to_db(g_szImagePath, &g_hImageInfo);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_insert_to_db", MediaContentGetError(nRet), media_content_disconnect());
	nRet = media_info_get_media_id(g_hImageInfo, &pszMediaId);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_media_id", MediaContentGetError(nRet), media_content_disconnect());
	memset(g_szImageId, 0, PATHLEN);
	strncpy(g_szImageId, pszMediaId, PATHLEN-1);
	FREE_MEMORY(pszMediaId);
	
	nRet = media_face_create(g_szImageId,&g_hFace);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_create", MediaContentGetError(nRet), media_content_disconnect());
	
	if(g_hFace == NULL)
	{
		FPRINTF("[Line : %d][%s]g_hFace is null:\\n", __LINE__, API_NAMESPACE);
		return;
	}
	g_bMediaContentStartup = true;
	return;
}

/**
 * @function 		ITs_media_content_face_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_face_cleanup(void)
{
	if(g_hTextInfo)
	{
		media_info_destroy(g_hTextInfo);
	}
	if(g_hImageInfo)
	{
		media_face_delete_from_db(g_szImageId);
		media_info_destroy(g_hImageInfo);
	}
	if(g_bMediaContentStartup && g_bIsScanFeatureSupported)
	{
		media_face_destroy(g_hFace);
		media_content_disconnect();
	}
	return;
}

/** @addtogroup itc-media-content-testcases
*  @brief 		Integration testcases for module media-content
*  @ingroup 	itc-media-content
*  @{
*/

/**
* @testcase 			ITc_media_face_create_destroy_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_face_create and media_face_destroy
* @scenario				Call media_face_create and media_face_destroy
* @apicovered			media_face_create and media_face_destroy
* @passcase				When media_face_create and media_face_destroy is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_face_create and media_face_destroy
//& type: auto
int ITc_media_face_create_destroy_p(void)
{
	START_TEST_PLAYLIST;
	
	int nRet = media_face_destroy(g_hFace);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_destroy", MediaContentGetError(nRet));

	nRet = media_face_create(g_szImageId,&g_hFace);		
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_create", MediaContentGetError(nRet));
	CHECK_HANDLE(g_hFace, "media_face_create");	
			
	return 0;
}

/**
* @testcase 			ITc_media_face_clone_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_face_clone
* @scenario				Call media_face_clone
* @apicovered			media_face_clone
* @passcase				When media_face_clone is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_face_clone
//& type: auto
int ITc_media_face_clone_p(void)
{
	START_TEST_PLAYLIST;

	media_face_h hFaceHandle = NULL;
	
	int nRet = media_face_clone(&hFaceHandle, g_hFace);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_clone", MediaContentGetError(nRet));
	CHECK_HANDLE(hFaceHandle, "media_face_clone");
	
	return 0;
}

/**
* @testcase 			ITc_media_face_get_face_id_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_face_get_face_id
* @scenario				Call media_face_get_face_id
* @apicovered			media_face_get_face_id
* @passcase				When media_face_get_face_id is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_face_get_face_id
//& type: auto
int ITc_media_face_get_face_id_p(void)
{
	START_TEST_PLAYLIST;

	char *pszFaceId = NULL;

	int nRet = media_face_get_face_id(g_hFace, &pszFaceId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_get_face_id", MediaContentGetError(nRet));
	
	return 0;
}

/**
* @testcase 			ITc_media_face_get_media_id_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_face_get_media_id
* @scenario				Call media_face_get_media_id
* @apicovered			media_face_get_media_id
* @passcase				When media_face_get_media_id is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_face_get_media_id
//& type: auto
int ITc_media_face_get_media_id_p(void)
{
	START_TEST_PLAYLIST;
	
	char *pszMediaId = NULL;
	
	int nRet = media_face_get_media_id(g_hFace, &pszMediaId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_get_media_id", MediaContentGetError(nRet));
	FREE_MEMORY(pszMediaId);
	
	return 0;
}

/**
* @testcase 			ITc_media_face_set_get_face_rect_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_face_set_face_rect and media_face_get_face_rect
* @scenario				Call media_face_set_face_rect and media_face_get_face_rect
* @apicovered			media_face_set_face_rect and media_face_get_face_rect
* @passcase				When media_face_set_face_rect and media_face_get_face_rect is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_face_set_face_rect and media_face_get_face_rect
//& type: auto
int ITc_media_face_set_get_face_rect_p(void)
{
	START_TEST_PLAYLIST;
	
	unsigned int rectx = 0,recty = 0,rectw = 0,recth = 0;
	
	int nRet = media_face_set_face_rect(g_hFace, 1,2,1,3);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_set_face_rect", MediaContentGetError(nRet));
	
	nRet = media_face_get_face_rect(g_hFace, &rectx, &recty, &rectw, &recth);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_get_face_rect", MediaContentGetError(nRet));

	return 0;
}       

/**
* @testcase 			ITc_media_face_set_get_orientation_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_face_set_orientation and media_face_get_orientation
* @scenario				Call media_face_set_orientation and media_face_get_orientation
* @apicovered			media_face_set_orientation and media_face_get_orientation
* @passcase				When media_face_set_orientation and media_face_get_orientation is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_face_set_orientation and media_face_get_orientation
//& type: auto
int ITc_media_face_set_get_orientation_p(void)
{
	START_TEST_PLAYLIST;

	media_content_orientation_e SetOrient = 3;
	media_content_orientation_e GetOrient = 0;
		
	int nRet = media_face_set_orientation(g_hFace,SetOrient);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_set_orientation", MediaContentGetError(nRet));
	
	nRet = media_face_get_orientation(g_hFace, &GetOrient);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_get_orientation", MediaContentGetError(nRet));
	PRINT_RESULT(SetOrient, GetOrient, "media_face_get_orientation","Orientation Mismatch");
	
	return 0;
}  
           
/**
* @testcase 			ITc_media_face_set_get_tag_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_face_set_tag and media_face_get_tag
* @scenario				Call media_face_set_tag and media_face_get_tag
* @apicovered			media_face_set_tag and media_face_get_tag
* @passcase				When media_face_set_tag and media_face_get_tag is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_face_set_tag and media_face_get_tag
//& type: auto
int ITc_media_face_set_get_tag_p(void)
{
	START_TEST_PLAYLIST;
	
	char *pszTag = NULL;
	
	int nRet = media_face_set_tag(g_hFace,TESTLOCATIONTAG);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_set_tag", MediaContentGetError(nRet));
	
	nRet = media_face_get_tag(g_hFace, &pszTag);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_get_tag", MediaContentGetError(nRet));
	CHECK_HANDLE(pszTag, "media_face_get_tag");
	PRINT_RESULT(0, strcmp(TESTLOCATIONTAG, pszTag), "media_face_get_tag","Keyword Mismatch");
	FREE_MEMORY(pszTag);

	return 0;
}  
                
/**
* @testcase 			ITc_media_face_insert_to_and_delete_from_db_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_face_delete_from_db and media_face_insert_to_db
* @scenario				Call media_face_delete_from_db and media_face_insert_to_db
* @apicovered			media_face_delete_from_db and media_face_insert_to_db
* @passcase				When media_face_delete_from_db and media_face_insert_to_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_face_delete_from_db and media_face_insert_to_db
//& type: auto
int ITc_media_face_insert_to_and_delete_from_db_p(void)
{
	START_TEST_PLAYLIST;
	
	char *face_id = NULL;

	int nRet = media_face_set_face_rect(g_hFace, 10, 12, 50, 100);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_set_face_rect", MediaContentGetError(nRet));
	
	nRet = media_face_set_orientation(g_hFace, 5);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_set_orientation", MediaContentGetError(nRet));
	
	nRet = media_face_set_tag(g_hFace, TESTLOCATIONTAG);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_set_tag", MediaContentGetError(nRet));
		
	nRet = media_face_insert_to_db(g_hFace);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_insert_to_db", MediaContentGetError(nRet));

	nRet = media_face_get_face_id(g_hFace, &face_id);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_get_face_id", MediaContentGetError(nRet));

	nRet = media_face_delete_from_db(face_id);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_delete_from_db", MediaContentGetError(nRet));
	
	return 0;
}

/**
* @testcase 			ITc_media_face_update_to_db_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_face_update_to_db
* @scenario				Call media_face_update_to_db
* @apicovered			media_face_update_to_db
* @passcase				When media_face_update_to_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_face_update_to_db
//& type: auto
int ITc_media_face_update_to_db_p(void)
{
	START_TEST_PLAYLIST;
	
	int nRet = media_face_set_face_rect(g_hFace, 20, 22, 70, 70);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_set_face_rect", MediaContentGetError(nRet));
	
	nRet = media_face_set_orientation(g_hFace, 3);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_set_orientation", MediaContentGetError(nRet));
	
	nRet = media_face_set_tag(g_hFace, NULL);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_set_tag", MediaContentGetError(nRet));
	
	nRet = media_face_insert_to_db(g_hFace);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_insert_to_db", MediaContentGetError(nRet));
	
	nRet = media_face_update_to_db(g_hFace);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_update_to_db", MediaContentGetError(nRet));
	
	return 0;
}

//& purpose: Test media start/cancel face detection
//& type: auto
/**
* @testcase 			ITc_media_info_start_cancel_face_detection_p
* @since_tizen			3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Test media start/cancel face detection
* @scenario				Call media_info_start_face_detection and media_info_cancel_face_detection
* @apicovered			media_info_start_face_detection and media_info_cancel_face_detection
* @passcase				When media_info_start_face_detection and media_info_cancel_face_detectionis successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_media_info_start_cancel_face_detection_p(void)
{
	START_TEST_PLAYLIST;
	
	g_CallBackHit = false;
	
	CHECK_HANDLE(g_hImageInfo, "media_info_insert_to_db");
	
	bool bIsFaceDetectionFeatureSupported = true;
	bIsFaceDetectionFeatureSupported = TCTCheckSystemInfoFeatureSupported(FACE_DETECTION, API_NAMESPACE);		
	
	int nRet =  media_info_start_face_detection( g_hImageInfo, MediaFaceDetectionCompletedCB , NULL);
    if ( !bIsFaceDetectionFeatureSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] media_info_start_face_detection returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE,  MediaContentGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] media_info_start_face_detection correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE,  MediaContentGetError(nRet));
			return 0;
		}	
	}
	
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_start_face_detection", MediaContentGetError(nRet));

	//If callback is invoked for "media_info_start_face_detection" then media_info_cancel_face_detection api will fail. So call "media_info_start_face_detection" one more time.
	media_info_start_face_detection( g_hImageInfo, MediaFaceDetectionCompletedCB , NULL);

	// for media_info_cancel_face_detection to work no need to check for callback hit as per the header file info
	nRet = media_info_cancel_face_detection(g_hImageInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_cancel_face_detection", MediaContentGetError(nRet));
		
	return 0;
}

//& purpose: Get face count from db
//& type: auto
/**
* @testcase 			ITc_media_face_get_face_count_from_db_p
* @since_tizen			4.0
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Get face count from db
* @scenario				Call media_filter_create and media_face_get_face_count_from_db
* @apicovered			media_filter_create and media_face_get_face_count_from_db
* @passcase				When media_filter_create and media_face_get_face_count_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			media_filter_create
* @postcondition		NA
*/
int ITc_media_face_get_face_count_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nRet = -1;
	int face_cnt = -1;
	filter_h hFilter = NULL;

	nRet = media_filter_create(&hFilter);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_create", MediaContentGetError(nRet));
	CHECK_HANDLE(hFilter, "media_filter_create");

	//Target API
	nRet = media_face_get_face_count_from_db(hFilter, &face_cnt);
	PRINT_RESULT_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_get_face_count_from_db", MediaContentGetError(nRet), media_filter_destroy(hFilter));
	CHECK_COUNT_CLEANUP(face_cnt, "media_face_get_face_count_from_db",media_filter_destroy(hFilter));

	media_filter_destroy(hFilter);

	return 0;
}

//& purpose: Get face foreach from db
//& type: auto
/**
* @testcase 			ITc_media_face_foreach_face_from_db_p
* @since_tizen			4.0
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Get face foreach from db
* @scenario				Call media_filter_create and media_face_foreach_face_from_db
* @apicovered			media_filter_create and mmedia_face_foreach_face_from_db
* @passcase				When media_filter_create and media_face_foreach_face_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			media_filter_create
* @postcondition		NA
*/
int ITc_media_face_foreach_face_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nRet = -1;
	g_CallBackHit = false;
	filter_h hFilter = NULL;

	nRet = media_filter_create(&hFilter);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_create", MediaContentGetError(nRet));
	CHECK_HANDLE(hFilter, "media_filter_create");

	//Target API
	nRet = media_face_foreach_face_from_db(hFilter, MediaFaceForeachCB, NULL);
	PRINT_RESULT_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_foreach_face_from_db", MediaContentGetError(nRet), media_filter_destroy(hFilter));
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "media_face_foreach_face_from_db", "CallBack Not Invoked", media_filter_destroy(hFilter));

	media_filter_destroy(hFilter);

	return 0;
}
/** @} */
/** @} */
