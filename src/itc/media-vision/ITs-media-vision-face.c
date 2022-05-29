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
#include "ITs-media-vision-common.h"

//& set: MediaVision

/** @addtogroup itc-media-vision
*  @ingroup itc
*  @{
*/

static mv_face_tracking_model_h hTrackingModel = NULL;
static bool lost_flag = false;
static char *track_seq_path = "NULL";
static char *track_prep_frame_path = "NULL";
static char* pInternalStoragePath=NULL;

static bool storage_device_cb(int storage_id, storage_type_e type, storage_state_e state, const char* path, void* user_data) 
{
	if (type == STORAGE_TYPE_INTERNAL) {
		pInternalStoragePath = (char*)calloc(strlen(path)+1, sizeof(char));
		if (pInternalStoragePath == NULL)
		{
			FPRINTF("[Line : %d][%s] Memory allocation of pInternalStoragePath failed\\n", __LINE__, API_NAMESPACE);
			return false;
		}
		snprintf(pInternalStoragePath, strlen(path)+1, "%s", path);

		track_seq_path=(char*)calloc(strlen(path)+strlen("/res/track/sequence")+1, sizeof(char));
		if (track_seq_path == NULL)
		{
			FPRINTF("[Line : %d][%s] Memory allocation of track_seq_path failed\\n", __LINE__, API_NAMESPACE);
			return false;
		}
		snprintf(track_seq_path, strlen(path)+strlen("/res/track/sequence")+1, "%s/res/track/sequence", path);

		track_prep_frame_path=(char*)calloc(strlen(path)+strlen("/res/track/sequence/01.jpg")+1, sizeof(char));
		if (track_prep_frame_path == NULL)
		{
			FPRINTF("[Line : %d][%s] Memory allocation of track_prep_frame_path failed\\n", __LINE__, API_NAMESPACE);
			return false;
		}
		snprintf(track_prep_frame_path, strlen(path)+strlen("/res/track/sequence/01.jpg")+1, "%s/res/track/sequence/01.jpg", path);

		return false;
	}
	return true;
}


/****************************************************Callback Start****************************************************/
/**
 * @function 		MvFaceDetectedCB
 * @description	 	Callback Function
 * @parameter		mv_source_h source, mv_engine_config_h engine_cfg, mv_rectangle_s *faces_locations, int number_of_faces, void *user_data
 * @return 			NA
 */
static void MvFaceDetectedCB(mv_source_h source, mv_engine_config_h engine_cfg, mv_rectangle_s *faces_locations, int number_of_faces, void *user_data)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] Callback Invoked\\n", __LINE__, API_NAMESPACE, "MvFaceDetectedCB");
#endif

    if (user_data == NULL)
    {
        FPRINTF("[Line : %d][%s] User Data not correct in callback\\n", __LINE__, API_NAMESPACE);
        QuitGmainLoop();
        return;
    }

    g_CallBackHit = true;
    QuitGmainLoop();
    return;

}

/**
 * @function 		MvFaceRecognizedCB
 * @description	 	Callback Function
 * @parameter		mv_source_h source, mv_face_recognition_model_h recognition_model, mv_engine_config_h engine_cfg, mv_rectangle_s *face_location,const int *face_label, double confidence, void *user_data
 * @return 			NA
 */
static void MvFaceRecognizedCB(mv_source_h source, mv_face_recognition_model_h recognition_model, mv_engine_config_h engine_cfg, mv_rectangle_s *face_location, const int *face_label, double confidence, void *user_data)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] Callback Invoked\\n", __LINE__, API_NAMESPACE, "MvFaceDetectedCB");
#endif
    if (user_data != NULL)
    {
        bool *is_called = (bool*)user_data;
        *is_called = true;
    }
    if (face_location)
    {
        FPRINTF("[Line : %d][%s] Face has been recognized as face [%i] with confidence %.2f\\n", __LINE__, API_NAMESPACE, *face_label, confidence);
    }
    else
    {
        FPRINTF("[Line : %d][%s] Face wasn't recognized\\n", __LINE__, API_NAMESPACE);
    }
}

/**
 * @function 		MvTrackCB
 * @description	 	Callback Function
 * @parameter		mv_source_h source, mv_face_tracking_model_h tracking_model, mv_engine_config_h engine_cfg, mv_quadrangle_s *location, double confidence, void *user_data
 * @return 			NA
 */
static void MvTrackCB( mv_source_h source, mv_face_tracking_model_h tracking_model, mv_engine_config_h engine_cfg, mv_quadrangle_s *location, double confidence, void *user_data)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] Callback Invoked\\n", __LINE__, API_NAMESPACE, "MvTrackCB");
#endif
    if (NULL != user_data)
    {
		FPRINTF("[Line : %d][%s] Track on %s\\n", __LINE__, API_NAMESPACE, (char *)user_data);
    }
    else
    {
        return;
    }

    if (NULL != location)
    {
		FPRINTF("[Line : %d][%s] Face tracked to the location bounded by "
               "(%i, %i)-(%i, %i)-(%i, %i)-(%i, %i); confidence: %f\\n", __LINE__, API_NAMESPACE, location->points[0].x, location->points[0].y,
               location->points[1].x, location->points[1].y,
               location->points[2].x, location->points[2].y,
               location->points[3].x, location->points[3].y,
               confidence);
    }
    else if (!lost_flag)
    {
		FPRINTF("[Line : %d][%s] Tracker has lost the face\\n", __LINE__, API_NAMESPACE);
        lost_flag = true;
    }
}

/**
 * @function 		MvEyeConditionCB
 * @description	 	Callback Function
 * @parameter		mv_source_h source, mv_engine_config_h engine_cfg, mv_rectangle_s face_location, mv_face_eye_condition_e eye_condition, void *user_data
 * @return 			NA
 */
static void MvEyeConditionCB( mv_source_h source, mv_engine_config_h engine_cfg, mv_rectangle_s face_location, mv_face_eye_condition_e eye_condition, void *user_data)
{
#if DEBUG
    FPRINTF("[Line : %d][%s]Callback Invoked\\n", __LINE__, API_NAMESPACE, "MvEyeConditionCB");
#endif
    mv_face_eye_condition_e *expected = (mv_face_eye_condition_e*) user_data;

    if (*expected != MV_FACE_EYES_NOT_FOUND || *expected != MV_FACE_EYES_OPEN)
    {
        FPRINTF("[Line : %d][%s] Wrong value of variable expected\\n", __LINE__, API_NAMESPACE);
        return;
    }
}

/**
 * @function 		MvFaceExpressionCB
 * @description	 	Callback Function
 * @parameter		mv_source_h source, mv_engine_config_h engine_cfg, mv_rectangle_s face_location, mv_face_facial_expression_e facial_expression, void *user_data
 * @return 			NA
 */
static void MvFaceExpressionCB( mv_source_h source, mv_engine_config_h engine_cfg, mv_rectangle_s face_location, mv_face_facial_expression_e facial_expression, void *user_data)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] Callback Invoked\\n", __LINE__, API_NAMESPACE, "MvFaceExpressionCB");
#endif
    mv_face_facial_expression_e *expected = (mv_face_facial_expression_e*) user_data;
    if (*expected != MV_FACE_NEUTRAL)
    {
        FPRINTF("[Line : %d][%s] Wrong value of variable expected\\n", __LINE__, API_NAMESPACE);
        return;
    }
}
/*****************************************************Callback End*****************************************************/

static int strCompare(const void *p1, const void *p2)
{
    return strcmp((char * const) p1, (char * const) p2);
}

void MediaVisionCreateModel()
{
    int nRet = mv_face_recognition_model_create(&g_hRecognitionModel);
    if (false == g_bIsFaceRecognitionFeatureSupported)
    {
		if(nRet != MEDIA_VISION_ERROR_NOT_SUPPORTED)
		{
			FPRINTF( "\\n [Line : %d] [%s] mv_face_recognition_model_create failed, expected return = MEDIA_VISION_ERROR_NOT_SUPPORTED, value returned = %s ", __LINE__, API_NAMESPACE , MediaVisionGetError(nRet));
			g_bMismatch = true;
			return;
		}
		return;
    }
    else
    {
		FPRINTF( "\\n [Line : %d] [%s] mv_face_recognition_model_create, value returned = %s ", __LINE__, API_NAMESPACE , MediaVisionGetError(nRet));
        CHECK_HANDLE_NONE(g_hRecognitionModel, "mv_face_recognition_model_create");
    }

    g_bMediavisionFaceRecognitionModelCreation = true;
}


/**
 * @function 		ITs_media_vision_face_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_vision_face_startup(void)
{
    struct stat stBuff;
    if ( stat(ERR_LOG, &stBuff) == 0 )
    {
        remove(ERR_LOG);
    }

	g_bMediavisionFaceRecognitionModelCreation = false;
	g_bMismatch = false;
	g_bIsFaceRecognitionFeatureSupported = TCTCheckSystemInfoFeatureSupported(FACERECOGFEATURE, API_NAMESPACE);
	g_bIsBarcodeGenerationFeatureSupported = TCTCheckSystemInfoFeatureSupported(BARCODEGENFEATURE, API_NAMESPACE);
	g_bIsBarcodeDetectionFeatureSupported = TCTCheckSystemInfoFeatureSupported(BARCODEDETFEATURE, API_NAMESPACE);

	storage_foreach_device_supported(storage_device_cb,NULL);

    return;
}


/**
 * @function 		ITs_media_vision_face_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_vision_face_cleanup(void)
{
	if(g_hRecognitionModel != NULL){
		mv_face_recognition_model_destroy(g_hRecognitionModel);
		g_hRecognitionModel = NULL;
	}

	if (pInternalStoragePath) {
		free(pInternalStoragePath);
		pInternalStoragePath = NULL;
	}

	if (track_seq_path) {
		free(track_seq_path);
		track_seq_path = NULL;
	}

	if (track_prep_frame_path) {
		free(track_prep_frame_path);
		track_prep_frame_path = NULL;
	}

    return;
}

/** @addtogroup itc-media-vision-testcases
*  @brief 		Integration testcases for module media-vision
*  @ingroup 	itc-media-vision
*  @{
*/

/**
 * @testcase 				ITc_mv_face_recognition_model_create_destroy_p
 * @author            		SRID(avinash.a)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				To test mv_face_recognition_model_create and mv_face_recognition_model_destroy
 * @scenario				Call mv_face_recognition_model_create, mv_face_recognition_model_destroy
 * @apicovered				mv_face_recognition_model_create, mv_face_recognition_model_destroy
 * @passcase				If mv_face_recognition_model_create and mv_face_recognition_model_destroy returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mv_face_recognition_model_create and mv_face_recognition_model_destroy
int ITc_mv_face_recognition_model_create_destroy_p(void)
{
    MediaVisionCreateModel();
	START_TEST_FACE;
	
    int nRet = -1;

    nRet = mv_face_recognition_model_destroy(g_hRecognitionModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_recognition_model_destroy", MediaVisionGetError(nRet));

    nRet = mv_face_recognition_model_create(&g_hRecognitionModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_recognition_model_create", MediaVisionGetError(nRet));
    CHECK_HANDLE(g_hRecognitionModel, "mv_face_recognition_model_create");

    nRet = mv_face_recognition_model_destroy(g_hRecognitionModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_recognition_model_destroy", MediaVisionGetError(nRet));

    nRet = mv_face_recognition_model_create(&g_hRecognitionModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_recognition_model_create", MediaVisionGetError(nRet));
    CHECK_HANDLE(g_hRecognitionModel, "mv_face_recognition_model_create");

    return 0;
}

/**
 * @testcase 				ITc_mv_face_recognition_model_clone_p
 * @author            		SRID(avinash.a)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				To test mv_face_recognition_model_clone
 * @scenario				Call mv_face_recognition_model_clone
 * @apicovered				mv_face_recognition_model_clone
 * @passcase				If mv_face_recognition_model_clone returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			mv_face_recognition_model_create
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mv_face_recognition_model_clone
int ITc_mv_face_recognition_model_clone_p(void)
{
    MediaVisionCreateModel();
	START_TEST_FACE;
	
    int nRet = -1;
    mv_face_recognition_model_h hCloned;
    
    nRet = mv_face_recognition_model_clone(g_hRecognitionModel, &hCloned);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_recognition_model_clone", MediaVisionGetError(nRet));
    CHECK_HANDLE(hCloned, "mv_face_recognition_model_clone");

    return 0;
}

/**
 * @testcase                            ITc_mv_face_detect_p
 * @author                      SRID(nibha.sharma)
 * @reviewer                    SRID(gupta.sanjay)
 * @type                                        auto
 * @since_tizen                         3.0
 * @description                         To test _mv_face_detect
 * @scenario                            Call mv_source_fill_by_buffer and _mv_face_detect
 * @apicovered                          mv_face_detect,mv_source_fill_by_buffer
 * @passcase                            If _mv_face_detect returns MEDIA_VISION_ERROR_NONE
 * @failcase                            If Precondition API or Target API Fails
 * @precondition                        NA
 * @postcondition                       NA
 * */
//& type: auto
//& purpose: To test mv_face_detect
int ITc_mv_face_detect_p(void)
{
    START_TEST;
	
	if( !(g_bIsFaceRecognitionFeatureSupported && (g_bIsBarcodeGenerationFeatureSupported || g_bIsBarcodeDetectionFeatureSupported)) )
	{
		FPRINTF("[Line : %d][%s] Bar code, face and barcode feature is not supported and api also returned not supported so leaving test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
    int nRet = -1 , number_of_faces_on_image = -1;

    nRet = mv_create_source(&g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));
    CHECK_HANDLE(g_hMvSource, "mv_create_source");

    g_pBufferData = calloc(1, BUFFERSIZE);
    CHECK_HANDLE(g_pBufferData, "calloc");

    nRet = mv_source_fill_by_buffer(g_hMvSource, (unsigned char *)g_pBufferData, BUFFERSIZE, 20, 30, MEDIA_VISION_COLORSPACE_RGB888);
    PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_source_fill_by_buffer", MediaVisionGetError(nRet), FREE_MEMORY(g_pBufferData));

    nRet = mv_face_detect(g_hMvSource, NULL, MvFaceDetectedCB, &number_of_faces_on_image);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_detect", MediaVisionGetError(nRet));

    FREE_MEMORY(g_pBufferData)

    nRet = mv_destroy_source(g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_source", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase                            ITc_mv_face_recognition_model_save_load_p
 * @author                      SRID(nibha.sharma)
 * @reviewer                    SRID(gupta.sanjay)
 * @type                                        auto
 * @since_tizen                         3.0
 * @description                         To test mv_face_recognition_model_save and mv_face_recognition_model_load
 * @scenario                            Call mv_face_recognition_model_add, mv_face_recognition_model_load, mv_face_recognition_model_learn and mv_face_recognition_model_save
 * @apicovered                          mv_face_recognition_model_add, mv_face_recognition_model_load, mv_face_recognition_model_learn and mv_face_recognition_model_save
 * @passcase                            If mv_face_recognition_model_save and mv_face_recognition_model_load returns MEDIA_VISION_ERROR_NONE
 * @failcase                            If Precondition API or Target API Fails
 * @precondition                        mv_face_recognition_model_create
 * @postcondition                       NA
 * */
//& type: auto
//& purpose: To test mv_face_recognition_model_save and mv_face_recognition_model_load
int ITc_mv_face_recognition_model_save_load_p(void)
{
	MediaVisionCreateModel();
    START_TEST_FACE;
    
	if( !(g_bIsBarcodeGenerationFeatureSupported || g_bIsBarcodeDetectionFeatureSupported) )
	{
		FPRINTF("[Line : %d][%s] Bar code feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
    int nRet = -1;

    nRet = mv_create_source(&g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));
    CHECK_HANDLE(g_hMvSource, "mv_create_source");

    g_pBufferData = calloc(1, BUFFERSIZE);
    CHECK_HANDLE(g_pBufferData, "calloc");

    nRet = mv_source_fill_by_buffer(g_hMvSource, (unsigned char *)g_pBufferData, BUFFERSIZE, 20, 30, MEDIA_VISION_COLORSPACE_RGB888);
    PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_source_fill_by_buffer", MediaVisionGetError(nRet), FREE_MEMORY(g_pBufferData));

    nRet = mv_face_recognition_model_add(g_hMvSource, g_hRecognitionModel, NULL, 1);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_recognition_model_add", MediaVisionGetError(nRet));

    nRet = mv_face_recognition_model_learn(NULL, g_hRecognitionModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_recognition_model_learn", MediaVisionGetError(nRet));

    FREE_MEMORY(g_pBufferData);

    nRet = mv_destroy_source(g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_source", MediaVisionGetError(nRet));

	char pszFilePath[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath(PATHPFXTREC, pszFilePath) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_face_recognition_model_save(pszFilePath, g_hRecognitionModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_recognition_model_save", MediaVisionGetError(nRet));

    nRet = mv_face_recognition_model_load(pszFilePath, &g_hRecognitionModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_recognition_model_load", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase                            ITc_mv_face_recognition_model_add_p
 * @author                      SRID(nibha.sharma)
 * @reviewer                    SRID(gupta.sanjay)
 * @type                                        auto
 * @since_tizen                         3.0
 * @description                         To test mv_face_recognition_model_add
 * @scenario                            Call mv_face_recognition_model_add
 * @apicovered                          mv_face_recognition_model_add
 * @passcase                            If mv_face_recognition_model_add returns MEDIA_VISION_ERROR_NONE
 * @failcase                            If Precondition API or Target API Fails
 * @precondition                        mv_face_recognition_model_create
 * @postcondition                       NA
 * */
//& type: auto
//& purpose: To test mv_face_recognition_model_add
int ITc_mv_face_recognition_model_add_p(void)
{
    MediaVisionCreateModel();
    START_TEST_FACE;

    if( !(g_bIsBarcodeGenerationFeatureSupported || g_bIsBarcodeDetectionFeatureSupported) )
    {
        FPRINTF("[Line : %d][%s] Bar code is not supported \\n", __LINE__, API_NAMESPACE);
        return 0;
    }
    int nRet = -1;

    mv_rectangle_s location;
    unsigned int width = 0;
    unsigned int height = 0;
    location.point.x = 0;
    location.point.y = 0;

    char pszFilePath[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath(PATHPFXNEUT, pszFilePath) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_create_source(&g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));
    CHECK_HANDLE(g_hMvSource, "mv_create_source");

    nRet = image_load(pszFilePath, g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "image_load", MediaVisionGetError(nRet));

    nRet = mv_source_get_width(g_hMvSource,&width);
    location.width = (int)width;
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_source_get_width", MediaVisionGetError(nRet));


    nRet = mv_source_get_height( g_hMvSource,&height);
    location.height = (int)height;
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_source_get_height", MediaVisionGetError(nRet));

    nRet = mv_face_recognition_model_add(g_hMvSource, g_hRecognitionModel, &location, 1);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_recognition_model_add", MediaVisionGetError(nRet));

    FREE_MEMORY(g_pBufferData);

    nRet = mv_destroy_source(g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_source", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase                            ITc_mv_face_recognition_model_reset_p
 * @author                      SRID(nibha.sharma)
 * @reviewer                    SRID(gupta.sanjay)
 * @type                                        auto
 * @since_tizen                         3.0
 * @description                         To test mv_face_recognition_model_reset
 * @scenario                            Call mv_face_recognition_model_add and mv_face_recognition_model_reset
 * @apicovered                          mv_face_recognition_model_reset, mv_face_recognition_model_add
 * @passcase                            If mv_face_recognition_model_reset returns MEDIA_VISION_ERROR_NONE
 * @failcase                            If Precondition API or Target API Fails
 * @precondition                        mv_face_recognition_model_create
 * @postcondition                       NA
 * */
//& type: auto
//& purpose: To test mv_face_recognition_model_reset
int ITc_mv_face_recognition_model_reset_p(void)
{
    MediaVisionCreateModel();
	START_TEST_FACE;
    
	if( !(g_bIsBarcodeGenerationFeatureSupported || g_bIsBarcodeDetectionFeatureSupported) )
	{
		FPRINTF("[Line : %d][%s] Bar code, face feature is not supported and api also returned not supported so leaving test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
    int nRet = -1, reset_label = 1;

    char pszFilePath[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath(PATHPFX01, pszFilePath) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_create_source(&g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));
    CHECK_HANDLE(g_hMvSource, "mv_create_source");

    nRet = image_load(pszFilePath,g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "image_load", MediaVisionGetError(nRet));

    nRet = mv_face_recognition_model_add(g_hMvSource, g_hRecognitionModel, NULL, 1);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_recognition_model_add", MediaVisionGetError(nRet));

    nRet = mv_face_recognition_model_reset(g_hRecognitionModel, &reset_label);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_recognition_model_reset", MediaVisionGetError(nRet));

    return 0;


}

/**
 * @testcase                            ITc_mv_face_recognition_model_learn_p
 * @author                      SRID(nibha.sharma)
 * @reviewer                    SRID(gupta.sanjay)
 * @type                                        auto
 * @since_tizen                         3.0
 * @description                         To test mv_face_recognition_model_learn
 * @scenario                            Call mv_face_recognition_model_learn
 * @apicovered                          mv_face_recognition_model_learn
 * @passcase                            If mv_face_recognition_model_learn returns MEDIA_VISION_ERROR_NONE
 * @failcase                            If Precondition API or Target API Fails
 * @precondition                        NA
 * @postcondition                       NA
 * */
//& type: auto
//& purpose: To test mv_face_recognition_model_learn
int ITc_mv_face_recognition_model_learn_p(void)
{
    MediaVisionCreateModel();
	START_TEST_FACE;
	
	if( !(g_bIsBarcodeGenerationFeatureSupported || g_bIsBarcodeDetectionFeatureSupported) )
	{
		FPRINTF("[Line : %d][%s] Bar code feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
    int nRet = -1;

    nRet = mv_create_source(&g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));
    CHECK_HANDLE(g_hMvSource, "mv_create_source");

    g_pBufferData = calloc(1, BUFFERSIZE);
    CHECK_HANDLE(g_pBufferData, "calloc");

    nRet = mv_source_fill_by_buffer(g_hMvSource, (unsigned char *)g_pBufferData, BUFFERSIZE, 20, 30, MEDIA_VISION_COLORSPACE_RGB888);
    PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_source_fill_by_buffer", MediaVisionGetError(nRet), FREE_MEMORY(g_pBufferData));

    nRet = mv_face_recognition_model_add(g_hMvSource, g_hRecognitionModel, NULL, 1);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_recognition_model_add", MediaVisionGetError(nRet));
	
	nRet = mv_create_engine_config(&g_hMvEngineConfig);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_engine_config", MediaVisionGetError(nRet));
    CHECK_HANDLE(g_hMvEngineConfig, "mv_create_engine_config");

    nRet = mv_face_recognition_model_learn(g_hMvEngineConfig, g_hRecognitionModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_recognition_model_learn", MediaVisionGetError(nRet));

    FREE_MEMORY(g_pBufferData);
	
	if(g_hMvEngineConfig != NULL)
	{
		nRet = mv_destroy_engine_config(g_hMvEngineConfig);
		g_hMvEngineConfig = NULL;
		PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_engine_config", MediaVisionGetError(nRet));
	}

    nRet = mv_destroy_source(g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_source", MediaVisionGetError(nRet));

    return 0;


}

/**
 * @testcase                            ITc_mv_face_recognition_model_query_labels_p
 * @author                      SRID(nibha.sharma)
 * @reviewer                    SRID(gupta.sanjay)
 * @type                                        auto
 * @since_tizen                         3.0
 * @description                         To test mv_face_recognition_model_query_labels
 * @scenario                            Call mv_face_recognition_model_query_labels
 * @apicovered                          mv_face_recognition_model_query_labels
 * @passcase                            If mv_face_recognition_model_query_labels returns MEDIA_VISION_ERROR_NONE
 * @failcase                            If Precondition API or Target API Fails
 * @precondition                        NA
 * @postcondition                       NA
 * */
//& type: auto
//& purpose: To test mv_face_recognition_model_query_labels
int ITc_mv_face_recognition_model_query_labels_p(void)
{
    MediaVisionCreateModel();
    START_TEST_FACE;

	if( !(g_bIsBarcodeGenerationFeatureSupported || g_bIsBarcodeDetectionFeatureSupported) )
	{
		FPRINTF("[Line : %d][%s] Bar code feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
    int nRet = -1;
    int *nlabels = NULL;
    unsigned int labels_n = 0;

    char pszFilePath[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath(PATHPFX09, pszFilePath) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_create_source(&g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));
    CHECK_HANDLE(g_hMvSource, "mv_create_source");

    nRet = image_load(pszFilePath,g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "image_load", MediaVisionGetError(nRet));

    nRet = mv_face_recognition_model_add(g_hMvSource, g_hRecognitionModel, NULL, 1);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_recognition_model_add", MediaVisionGetError(nRet));

    nRet = mv_face_recognition_model_query_labels(g_hRecognitionModel, &nlabels, &labels_n);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_recognition_model_query_labels", MediaVisionGetError(nRet));
    if (0 != labels_n)
    {
        FPRINTF("[Line : %d][%s] mv_face_recognition_model_query_labels failed\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    return 0;
}

/**
 * @testcase                            ITc_mv_face_tracking_model_create_destroy_p
 * @author                      SRID(nibha.sharma)
 * @reviewer                    SRID(gupta.sanjay)
 * @type                                        auto
 * @since_tizen                         3.0
 * @description                         To test mv_face_tracking_model_create and mv_face_tracking_model_destroy
 * @scenario                            Call mv_face_tracking_model_create and mv_face_tracking_model_destroy
 * @apicovered                          mv_face_tracking_model_create and mv_face_tracking_model_destroy
 * @passcase                            If mv_face_tracking_model_create and mv_face_tracking_model_destroy returns MEDIA_VISION_ERROR_NONE
 * @failcase                            If Precondition API or Target API Fails
 * @precondition                        NA
 * @postcondition                       NA
 * */
//& type: auto
//& purpose: To test mv_face_tracking_model_create and mv_face_tracking_model_destroy
int ITc_mv_face_tracking_model_create_destroy_p(void)
{
    START_TEST;
    
	if( g_bIsFaceRecognitionFeatureSupported == false )
	{
		FPRINTF("[Line : %d][%s] Face recognition feature is not supported and api also returned not supported so leaving test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
    int nRet = -1;
    mv_face_tracking_model_h hTestTrackingModel = NULL;

    nRet = mv_face_tracking_model_create(&hTestTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_tracking_model_create", MediaVisionGetError(nRet));
    CHECK_HANDLE(hTestTrackingModel, "mv_face_tracking_model_h");

    nRet = mv_face_tracking_model_destroy(hTestTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_tracking_model_destroy", MediaVisionGetError(nRet));
    hTestTrackingModel = NULL;

    return 0;
}

/**
 * @testcase                            ITc_mv_face_tracking_model_prepare_p
 * @author                      SRID(nibha.sharma)
 * @reviewer                    SRID(gupta.sanjay)
 * @type                                        auto
 * @since_tizen                         3.0
 * @description                         To test mv_face_tracking_model_prepare
 * @scenario                            Call mv_face_tracking_model_create, mv_face_tracking_model_prepare
 * @apicovered                          mv_face_tracking_model_create, mv_face_tracking_model_prepare
 * @passcase                            If mv_face_tracking_model_prepare returns MEDIA_VISION_ERROR_NONE
 * @failcase                            If Precondition API or Target API Fails
 * @precondition                        NA
 * @postcondition                       NA
 * */
//& type: auto
//& purpose: To test mv_face_tracking_model_prepare
int ITc_mv_face_tracking_model_prepare_p(void)
{
    START_TEST;
	
    if( !(g_bIsFaceRecognitionFeatureSupported && (g_bIsBarcodeGenerationFeatureSupported || g_bIsBarcodeDetectionFeatureSupported)) )
	{
		FPRINTF("[Line : %d][%s] face and barcode feature is not supported and api also returned not supported so leaving test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
    int nRet = mv_create_source(&g_hMvSource);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));
    CHECK_HANDLE(g_hMvSource, "mv_create_source");

    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/track/sequence/01.jpg")+1, "%s/res/track/sequence/01.jpg", pInternalStoragePath);
    nRet = image_load(pszValue, g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "image_load", MediaVisionGetError(nRet));
	
    nRet = mv_face_tracking_model_create(&hTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_tracking_model_create", MediaVisionGetError(nRet));

    mv_quadrangle_s roi;
    roi.points[0].x = 440;
    roi.points[0].y = 130;
    roi.points[1].x = 530;
    roi.points[1].y = 130;
    roi.points[2].x = 530;
    roi.points[2].y = 240;
    roi.points[3].x = 440;
    roi.points[3].y = 240;
	
	nRet = mv_create_engine_config(&g_hMvEngineConfig);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_engine_config", MediaVisionGetError(nRet));
    CHECK_HANDLE(g_hMvEngineConfig, "mv_create_engine_config");

    nRet = mv_face_tracking_model_prepare(hTrackingModel, g_hMvEngineConfig, g_hMvSource, &roi);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_tracking_model_prepare", MediaVisionGetError(nRet));
	
	if(g_hMvEngineConfig != NULL)
	{
		nRet = mv_destroy_engine_config(g_hMvEngineConfig);
		g_hMvEngineConfig = NULL;
		PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_engine_config", MediaVisionGetError(nRet));
	}
	
	nRet = mv_face_tracking_model_destroy(hTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_tracking_model_destroy", MediaVisionGetError(nRet));

    nRet = mv_destroy_source(g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_source", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase                            ITc_mv_face_tracking_model_clone_p
 * @author                      SRID(nibha.sharma)
 * @reviewer                    SRID(gupta.sanjay)
 * @type                                        auto
 * @since_tizen                         3.0
 * @description                         To test mv_face_tracking_model_clone
 * @scenario                            Call mv_face_tracking_model_clone
 * @apicovered                          mv_face_tracking_model_clone
 * @passcase                            If mv_face_tracking_model_clone returns MEDIA_VISION_ERROR_NONE
 * @failcase                            If Precondition API or Target API Fails
 * @precondition                        NA
 * @postcondition                       NA
 * */
//& type: auto
//& purpose: To test mv_face_tracking_model_clone
int ITc_mv_face_tracking_model_clone_p(void)
{
    START_TEST;
    
	if( g_bIsFaceRecognitionFeatureSupported == false )
	{
		FPRINTF("[Line : %d][%s] Face recognition feature is not supported and api also returned not supported so leaving test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
    int nRet = -1;
    mv_face_tracking_model_h hTestTrackingModel = NULL;
    mv_face_tracking_model_h hDestModel = NULL;

    nRet = mv_face_tracking_model_create(&hTestTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_tracking_model_create", MediaVisionGetError(nRet));
    CHECK_HANDLE(hTestTrackingModel, "mv_face_tracking_model_h");

    nRet = mv_face_tracking_model_clone(hTestTrackingModel, &hDestModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_tracking_model_clone", MediaVisionGetError(nRet));

    char pszFilePath_s[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath("test_src_model", pszFilePath_s) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_face_tracking_model_save(pszFilePath_s, hTestTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_tracking_model_save", MediaVisionGetError(nRet));

    char pszFilePath_d[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath("test_dst_model", pszFilePath_d) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_face_tracking_model_save(pszFilePath_d, hDestModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_tracking_model_save", MediaVisionGetError(nRet));

    bool bCompareModels = checkModelFile(pszFilePath_s, pszFilePath_d);
    if (!bCompareModels)
    {
        FPRINTF("[Line : %d][%s] models are not same\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_face_tracking_model_destroy(hTestTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_tracking_model_destroy", MediaVisionGetError(nRet));

    nRet = mv_face_tracking_model_destroy(hDestModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_tracking_model_destroy", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase                            ITc_mv_face_tracking_model_save_p
 * @author                      SRID(nibha.sharma)
 * @reviewer                    SRID(gupta.sanjay)
 * @type                                        auto
 * @since_tizen                         3.0
 * @description                         To test mv_face_tracking_model_save
 * @scenario                            Call mv_face_tracking_model_create and mv_face_tracking_model_save
 * @apicovered                          mv_face_tracking_model_create and mv_face_tracking_model_save
 * @passcase                            If mv_face_tracking_model_create and mv_face_tracking_model_save returns MEDIA_VISION_ERROR_NONE
 * @failcase                            If Precondition API or Target API Fails
 * @precondition                        NA
 * @postcondition                       NA
 * */
//& type: auto
//& purpose: To test mv_face_tracking_model_save
int ITc_mv_face_tracking_model_save_p(void)
{
    START_TEST;
    
	if( !(g_bIsFaceRecognitionFeatureSupported && (g_bIsBarcodeGenerationFeatureSupported || g_bIsBarcodeDetectionFeatureSupported)) )
	{
		FPRINTF("[Line : %d][%s] Bar code, face and barcode feature is not supported and api also returned not supported so leaving test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
    int nRet = -1;

    char pszFilePath[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath(PATHPFX01, pszFilePath) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_create_source(&g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));
    CHECK_HANDLE(g_hMvSource, "mv_create_source");

    nRet = mv_face_tracking_model_create(&hTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_tracking_model_create", MediaVisionGetError(nRet));

    nRet = mv_face_tracking_model_save("/tmp/test_trk_model", hTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_tracking_model_save", MediaVisionGetError(nRet));

    nRet = mv_face_tracking_model_destroy(hTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_tracking_model_destroy", MediaVisionGetError(nRet));

    nRet = mv_destroy_source(g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_source", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase                            ITc_mv_face_tracking_model_load_p
 * @author                      SRID(nibha.sharma)
 * @reviewer                    SRID(gupta.sanjay)
 * @type                                        auto
 * @since_tizen                         3.0
 * @description                         To test mv_face_tracking_model_load
 * @scenario                            Call mv_face_tracking_model_load
 * @apicovered                          mv_face_tracking_model_load
 * @passcase                            If mv_face_tracking_model_load returns MEDIA_VISION_ERROR_NONE
 * @failcase                            If Precondition API or Target API Fails
 * @precondition                        NA
 * @postcondition                       NA
 * */
//& type: auto
//& purpose: To test mv_face_tracking_model_load
int ITc_mv_face_tracking_model_load_p(void)
{
    START_TEST;
    
	if( g_bIsFaceRecognitionFeatureSupported == false )
	{
		FPRINTF("[Line : %d][%s] Face recognition feature is not supported and api also returned not supported so leaving test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
    int nRet = -1;

    char pszFilePath[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath("test_trk_model", pszFilePath) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_face_tracking_model_load( pszFilePath, &g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_tracking_model_load", MediaVisionGetError(nRet));

    nRet = mv_face_tracking_model_destroy(g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_tracking_model_destroy", MediaVisionGetError(nRet));
    g_hMvSource = NULL;

    return 0;
}

/**
 * @testcase                            ITc_mv_face_recognize_p
 * @author                      SRID(nibha.sharma)
 * @reviewer                    SRID(gupta.sanjay)
 * @type                                        auto
 * @since_tizen                         3.0
 * @description                         To test mv_face_recognize
 * @scenario                            Call mv_face_recognize
 * @apicovered                          mv_face_recognize
 * @passcase                            If mv_face_recognize returns MEDIA_VISION_ERROR_NONE
 * @failcase                            If Precondition API or Target API Fails
 * @precondition                        NA
 * @postcondition                       NA
 * */
//& type: auto
//& purpose: To test mv_face_recognize
int ITc_mv_face_recognize_p(void)
{
    START_TEST;
    
	if( !(g_bIsFaceRecognitionFeatureSupported && (g_bIsBarcodeGenerationFeatureSupported || g_bIsBarcodeDetectionFeatureSupported)) )
	{
		FPRINTF("[Line : %d][%s] Bar code, face and barcode feature is not supported and api also returned not supported so leaving test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
    int nRet = -1;
    mv_face_recognition_model_h recognition_model = NULL;
    bool is_called = false;
    mv_source_h source = NULL;

    char pszFilePath[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath(PATHPFXTREC, pszFilePath) )
    {
         FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
         return 1;
    }

    nRet = mv_face_recognition_model_load( pszFilePath, &recognition_model);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_recognition_model_load", MediaVisionGetError(nRet));

    nRet = mv_create_source(&source);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));

    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/P1/09.jpg")+1, "%s/P1/09.jpg", pInternalStoragePath);
    nRet = image_load( pszValue, source);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "image_load", MediaVisionGetError(nRet));

    nRet = mv_face_recognize(source, recognition_model, NULL, NULL, MvFaceRecognizedCB, &is_called);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_recognize", MediaVisionGetError(nRet));
    if (false == is_called)
    {
        FPRINTF("[Line : %d][%s] unable to recognize face\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_destroy_source(source);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_source", MediaVisionGetError(nRet));

    nRet = mv_face_recognition_model_destroy(recognition_model);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_recognition_model_destroy", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase                            ITc_mv_face_track_p
 * @author                      SRID(nibha.sharma)
 * @reviewer                    SRID(gupta.sanjay)
 * @type                                        auto
 * @since_tizen                         3.0
 * @description                         To test mv_face_track
 * @scenario                            Call mv_face_tracking_model_create,mv_face_tracking_model_prepare and mv_face_track
 * @apicovered                          mv_face_tracking_model_create,mv_face_tracking_model_prepare and mv_face_track
 * @passcase                            If mv_face_track returns MEDIA_VISION_ERROR_NONE
 * @failcase                            If Precondition API or Target API Fails
 * @precondition                        NA
 * @postcondition                       NA
 * */
//& type: auto
//& purpose: To test mv_face_track
int ITc_mv_face_track_p(void)
{
	START_TEST;
    
	if( !(g_bIsFaceRecognitionFeatureSupported && (g_bIsBarcodeGenerationFeatureSupported || g_bIsBarcodeDetectionFeatureSupported)) )
	{
		FPRINTF("[Line : %d][%s] Bar code, face and barcode feature is not supported and api also returned not supported so leaving test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet = -1, frames_counter = 0, idx = 1;;
	
	nRet = mv_face_tracking_model_create(&hTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_tracking_model_create", MediaVisionGetError(nRet));
	
	nRet = mv_create_source(&g_hMvSource);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));
    CHECK_HANDLE(g_hMvSource, "mv_create_source");

    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/track/sequence/01.jpg")+1, "%s/res/track/sequence/01.jpg", pInternalStoragePath);
    nRet = image_load(pszValue, g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "image_load", MediaVisionGetError(nRet));

    mv_quadrangle_s roi;
    roi.points[0].x = 440;
    roi.points[0].y = 130;
    roi.points[1].x = 530;
    roi.points[1].y = 130;
    roi.points[2].x = 530;
    roi.points[2].y = 240;
    roi.points[3].x = 440;
    roi.points[3].y = 240;

    nRet = mv_face_tracking_model_prepare(hTrackingModel, NULL, g_hMvSource, &roi);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_tracking_model_prepare", MediaVisionGetError(nRet));

    char (*frames)[1024] = (char **) malloc(0);
    struct dirent *ent;
    DIR *dir = opendir(track_seq_path);
    if (NULL != dir)
    {
        while (NULL != (ent = readdir (dir)))
        {
            if ('.' == ent->d_name[0] ||
                0   != strcmp(".jpg", ent->d_name + strlen(ent->d_name) - 4))
            {
                continue;
            }

            frames = (char **) realloc(frames, ++frames_counter * 1024);

            snprintf(frames[frames_counter - 1], strlen(track_seq_path)+strlen("/")+strlen(ent->d_name)+1, "%s/%s", track_seq_path, ent->d_name);
        }
        closedir(dir);
    }

    if (1 >= frames_counter)
    {
        FPRINTF("[Line : %d][%s]  Value is not lower than %d \\n", __LINE__, API_NAMESPACE,frames_counter);
		free(frames);
        return 1;
    }

    FPRINTF("[Line : %d][%s] frames_counter %i\\n", __LINE__, API_NAMESPACE, frames_counter);
    qsort(&frames[0], frames_counter, 1024, strCompare);

    for (; idx < frames_counter; ++idx)
    {
        nRet = image_load(frames[idx], g_hMvSource);
        PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "image_load", MediaVisionGetError(nRet),free(frames));

        nRet = mv_face_track(g_hMvSource, hTrackingModel, NULL, MvTrackCB, true, frames[idx]);
        PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_track", MediaVisionGetError(nRet),free(frames));
    }

    free(frames);
    frames = NULL;

    nRet = mv_face_tracking_model_destroy(hTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_tracking_model_destroy", MediaVisionGetError(nRet));

    nRet = mv_destroy_source(g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_source", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase                            ITc_mv_face_eye_condition_recognize_p
 * @author                      SRID(nibha.sharma)
 * @reviewer                    SRID(gupta.sanjay)
 * @type                                        auto
 * @since_tizen                         3.0
 * @description                         To test mv_face_eye_condition_recognize
 * @scenario                            Call mv_face_eye_condition_recognize
 * @apicovered                          mv_face_eye_condition_recognize
 * @passcase                            If mv_face_eye_condition_recognize returns MEDIA_VISION_ERROR_NONE
 * @failcase                            If Precondition API or Target API Fails
 * @precondition                        mv_face_recognition_model_create
 * @postcondition                       NA
 * */
//& type: auto
//& purpose: To test mv_face_eye_condition_recognize
int ITc_mv_face_eye_condition_recognize_p(void)
{
    START_TEST;
	
	if( !(g_bIsFaceRecognitionFeatureSupported && (g_bIsBarcodeGenerationFeatureSupported || g_bIsBarcodeDetectionFeatureSupported)) )
	{
		FPRINTF("[Line : %d][%s] Bar code, face and barcode feature is not supported and api also returned not supported so leaving test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
    mv_rectangle_s location;
    mv_face_eye_condition_e eye_condition;
    int nRet = -1;
    location.point.x = 177;
    location.point.y = 87;
    location.width = 157;
    location.height = 157;

    eye_condition = MV_FACE_EYES_OPEN;

    char pszFilePath[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath(PATHPFX01, pszFilePath) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_create_source(&g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));

    nRet = image_load(pszFilePath, g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "image_load", MediaVisionGetError(nRet));

    nRet = mv_face_eye_condition_recognize( g_hMvSource, NULL, location, MvEyeConditionCB,&eye_condition);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_eye_condition_recognize", MediaVisionGetError(nRet));

    nRet = mv_destroy_source(g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_source", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase                            ITc_mv_face_facial_expression_recognize_p
 * @author                      SRID(nibha.sharma)
 * @reviewer                    SRID(gupta.sanjay)
 * @type                                        auto
 * @since_tizen                         3.0
 * @description                         To test mv_face_facial_expression_recognize
 * @scenario                            Call mv_face_facial_expression_recognize
 * @apicovered                          mv_face_facial_expression_recognize
 * @passcase                            If mv_face_facial_expression_recognize returns MEDIA_VISION_ERROR_NONE
 * @failcase                            If Precondition API or Target API Fails
 * @precondition                        NA
 * @postcondition                       NA
 * */
//& type: auto
//& purpose: To test mv_face_facial_expression_recognize
int ITc_mv_face_facial_expression_recognize_p(void)
{
    START_TEST;
    
	if( !(g_bIsFaceRecognitionFeatureSupported && (g_bIsBarcodeGenerationFeatureSupported || g_bIsBarcodeDetectionFeatureSupported)) )
	{
		FPRINTF("[Line : %d][%s] Bar code, face and barcode feature is not supported and api also returned not supported so leaving test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

    unsigned int width = 0;
    unsigned int height = 0;
    mv_rectangle_s location;
    location.point.x = 0;
    location.point.y = 0;
    mv_face_facial_expression_e face_expression = MV_FACE_NEUTRAL;
    int nRet = -1;

    char pszFilePath[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath(PATHPFXNEUT, pszFilePath) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_create_source(&g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));

    nRet = image_load(pszFilePath, g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "image_load", MediaVisionGetError(nRet));

    nRet = mv_source_get_width(g_hMvSource, &width);
    location.width = (int)width;
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_source_get_width", MediaVisionGetError(nRet));

    nRet = mv_source_get_height( g_hMvSource, &height);
    location.height = (int)height;
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_source_get_height", MediaVisionGetError(nRet));

    nRet = mv_face_facial_expression_recognize( g_hMvSource, NULL, location, MvFaceExpressionCB, &face_expression);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_face_facial_expression_recognize", MediaVisionGetError(nRet));

    nRet = mv_destroy_source(g_hMvSource);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_source", MediaVisionGetError(nRet));

    return 0;
}
/** @} */
/** @} */
