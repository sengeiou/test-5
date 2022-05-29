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
const char *image_object_serizalization_path = "image_object.txt";
/**
 * @function 		MvRecognizedCB
 * @description	 	Callback Function
 * @parameter		mv_source_h source,mv_engine_config_h engine_cfg,const mv_image_object_h *image_objects, mv_quadrangle_s **locations, unsigned int number_of_objects, void *user_data
 * @return 			NA
 */
static void MvRecognizedCB( mv_source_h source,mv_engine_config_h engine_cfg,const mv_image_object_h *image_objects, mv_quadrangle_s **locations, unsigned int number_of_objects, void *user_data)
{
#if DEBUG
    FPRINTF("[Line : %d][%s]Callback Invoked\\n", __LINE__, API_NAMESPACE, "MvRecognizedCB");
#endif
    if (NULL == user_data)
    {
        FPRINTF("[Line : %d][%s] USer data is null\\n", __LINE__, API_NAMESPACE);
        return;
    }
}
/**
 * @function 		MvTrackedCB
 * @description	 	Callback Function
 * @parameter		mv_source_h source, mv_image_tracking_model_h tracking_model, mv_engine_config_h engine_cfg,mv_quadrangle_s     *location,void *user_data
 * @return 			NA
 */
void MvTrackedCB( mv_source_h source, mv_image_tracking_model_h tracking_model, mv_engine_config_h engine_cfg,mv_quadrangle_s *location,void *user_data)
{
#if DEBUG
    FPRINTF("[Line : %d][%s]Callback Invoked\\n", __LINE__, API_NAMESPACE, "MvTrackedCB");
#endif
    if (NULL == user_data)
    {
        FPRINTF("[Line : %d][%s] User Data not correct in callback\\n", __LINE__, API_NAMESPACE);
        return;
    }
}

/**
 * @function 		ITs_media_vision_image_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_vision_image_startup(void)
{
    struct stat stBuff;
    if ( stat(ERR_LOG, &stBuff) == 0 )
    {
        remove(ERR_LOG);
    }
   
	g_bIsImageRecognitionFeatureSupported = TCTCheckSystemInfoFeatureSupported(IMAGERECOGFEATURE, API_NAMESPACE);
	g_bIsBarcodeGenerationFeatureSupported = TCTCheckSystemInfoFeatureSupported(BARCODEGENFEATURE, API_NAMESPACE);
	g_bIsBarcodeDetectionFeatureSupported = TCTCheckSystemInfoFeatureSupported(BARCODEDETFEATURE, API_NAMESPACE);

    return;
}


/**
 * @function 		ITs_media_vision_image_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_vision_image_cleanup(void)
{
    return;
}

/**
 * @testcase 				ITc_mv_image_object_create_destroy_p
 * @author            		SRID(nibha.sharma)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				To test mv_image_object_create and mv_image_object_destroy
 * @scenario				Call mv_image_object_create, mv_image_object_destroy
 * @apicovered				mv_image_object_create, mv_image_object_destroy
 * @passcase				If mv_image_object_create and mv_image_object_destroy returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mv_image_object_create and mv_image_object_destroy
int ITc_mv_image_object_create_destroy_p(void)
{
    START_TEST_IMAGE;

    int nRet = -1;
    mv_image_object_h hImageObject;

    nRet = mv_image_object_create(&hImageObject);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_create", MediaVisionGetError(nRet));
    CHECK_HANDLE(hImageObject, "mv_image_object_create");

    nRet = mv_image_object_destroy(hImageObject);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_destroy", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase 				ITc_mv_image_object_fill_p
 * @author            		SRID(nibha.sharma)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				To test mv_image_object_fill
 * @scenario				Call mv_source_fill_by_buffer, mv_image_object_create and mv_image_object_fill
 * @apicovered				mv_source_fill_by_buffer, mv_image_object_create and mv_image_object_fill
 * @passcase				If mv_image_object_fill returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mv_image_object_fill
int ITc_mv_image_object_fill_p(void)
{
    START_TEST_IMAGE;
    
	if( !(g_bIsBarcodeGenerationFeatureSupported || g_bIsBarcodeDetectionFeatureSupported) )
	{
		FPRINTF("[Line : %d][%s] Bar code feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
    int nRet = -1;
    mv_source_h hTargetImage;
    mv_image_object_h htarget;

    nRet = mv_create_source(&hTargetImage);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));

    g_pBufferData = calloc(1, BUFFERSIZE);
    CHECK_HANDLE(g_pBufferData, "calloc");

    nRet = mv_source_fill_by_buffer(hTargetImage, (unsigned char *)g_pBufferData, BUFFERSIZE, 20, 30, MEDIA_VISION_COLORSPACE_RGB888);
    PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_source_fill_by_buffer", MediaVisionGetError(nRet), FREE_MEMORY(g_pBufferData));

    nRet = mv_image_object_create(&htarget);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_create", MediaVisionGetError(nRet));
	
	nRet = mv_create_engine_config(&g_hMvEngineConfig);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_engine_config", MediaVisionGetError(nRet));
    CHECK_HANDLE(g_hMvEngineConfig, "mv_create_engine_config");

    nRet = mv_image_object_fill(htarget, g_hMvEngineConfig, hTargetImage, NULL);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_fill", MediaVisionGetError(nRet));

    FREE_MEMORY(g_pBufferData);
	
	if(g_hMvEngineConfig != NULL)
	{
		nRet = mv_destroy_engine_config(g_hMvEngineConfig);
		g_hMvEngineConfig = NULL;
		PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_engine_config", MediaVisionGetError(nRet));
	}

    nRet = mv_image_object_destroy(htarget);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_destroy", MediaVisionGetError(nRet));

    nRet = mv_destroy_source(hTargetImage);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_source", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase 				ITc_mv_image_object_get_recognition_rate_p
 * @author            		SRID(nibha.sharma)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				To test mv_image_object_get_recognition_rate
 * @scenario				Call mv_image_object_create, mv_image_object_get_recognition_rate
 * @apicovered				mv_image_object_create, mv_image_object_get_recognition_rate
 * @passcase				If mv_image_object_get_recognition_rate returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mv_image_object_get_recognition_rate
int ITc_mv_image_object_get_recognition_rate_p(void)
{
    START_TEST_IMAGE;

    int nRet = -1;
    mv_image_object_h hImageObject;
    double recognition_rate = 0;

    nRet = mv_image_object_create(&hImageObject);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_create", MediaVisionGetError(nRet));

    nRet = mv_image_object_get_recognition_rate(hImageObject, &recognition_rate);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_get_recognition_rate", MediaVisionGetError(nRet));
    if (0 != recognition_rate)
    {
        FPRINTF("[Line : %d][%s] recognition_rate not valid!!!\\n", __LINE__, API_NAMESPACE);
        return 1;
    }
    nRet = mv_image_object_destroy(hImageObject);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_destroy", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase 				ITc_mv_image_object_set_get_label_p
 * @author            		SRID(nibha.sharma)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				To test mv_image_object_set_label and mv_image_object_get_label
 * @scenario				Call mv_image_object_set_label and mv_image_object_get_label
 * @apicovered				mv_image_object_set_label and mv_image_object_get_label
 * @passcase				If mv_image_object_set_label and mv_image_object_get_label returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mv_image_object_set_label and mv_image_object_get_label
int ITc_mv_image_object_set_get_label_p(void)
{
    START_TEST_IMAGE;

    int nRet = -1;
    mv_image_object_h hImageObject;
    const int test_label = 24;
    int label = 0;

    nRet = mv_image_object_create(&hImageObject);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_create", MediaVisionGetError(nRet));

    nRet = mv_image_object_set_label(hImageObject, test_label);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_set_label", MediaVisionGetError(nRet));

    nRet = mv_image_object_get_label(hImageObject, &label);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_get_label", MediaVisionGetError(nRet));
    if (test_label != label)
    {
        FPRINTF("[Line : %d][%s] Values of set get not matched!!!\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_image_object_destroy(hImageObject);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_destroy", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase 				ITc_mv_image_object_clone_p
 * @author            		SRID(nibha.sharma)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				To test mv_image_object_clone
 * @scenario				Call mv_image_object_create, mv_image_object_clone
 * @apicovered				mv_image_object_create, mv_image_object_clone
 * @passcase				If mv_image_object_clone returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mv_image_object_clone
int ITc_mv_image_object_clone_p(void)
{
    START_TEST_IMAGE;

    int nRet = -1;
    mv_image_object_h hImageObject1 = NULL, hImageObject2 = NULL;

    nRet = mv_image_object_create(&hImageObject1);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_create", MediaVisionGetError(nRet));

    nRet = mv_image_object_create(&hImageObject2);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_create", MediaVisionGetError(nRet));

    nRet = mv_image_object_clone(hImageObject1, &hImageObject2);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_clone", MediaVisionGetError(nRet));

    char pszFilePath_s[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath("test_src_model", pszFilePath_s) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_image_object_save(pszFilePath_s, hImageObject1);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_save", MediaVisionGetError(nRet));

    char pszFilePath_d[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath("test_src_model", pszFilePath_d) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_image_object_save(pszFilePath_d, hImageObject2);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_save", MediaVisionGetError(nRet));

    bool compare_models = checkModelFile(pszFilePath_s, pszFilePath_d);
    if (!compare_models)
    {
        FPRINTF("[Line : %d][%s] model not matches\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_image_object_destroy(hImageObject1);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_destroy", MediaVisionGetError(nRet));

    nRet = mv_image_object_destroy(hImageObject2);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_destroy", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase 				ITc_mv_image_object_save_load_p
 * @author            		SRID(nibha.sharma)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				To test mv_image_object_save and mv_image_object_load
 * @scenario				Call mv_image_object_save and mv_image_object_load
 * @apicovered				mv_image_object_save and mv_image_object_load
 * @passcase				If mv_image_object_save and mv_image_object_load returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mv_image_object_save and mv_image_object_load
int ITc_mv_image_object_save_load_p(void)
{
    START_TEST_IMAGE;

    int nRet = -1;
    mv_image_object_h hImageObject;

    nRet = mv_image_object_create(&hImageObject);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_create", MediaVisionGetError(nRet));

    char pszFilePath[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath(image_object_serizalization_path, pszFilePath) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_image_object_save(pszFilePath, hImageObject);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_save", MediaVisionGetError(nRet));

    nRet = mv_image_object_destroy(hImageObject);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_destroy", MediaVisionGetError(nRet));

    hImageObject = NULL;
    nRet = mv_image_object_load(pszFilePath, &hImageObject);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_load", MediaVisionGetError(nRet));

    nRet = mv_image_object_destroy(hImageObject);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_destroy", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase 				ITc_mv_image_tracking_model_create_p
 * @author            		SRID(nibha.sharma)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				To test mv_image_tracking_model_create
 * @scenario				Call mv_image_tracking_model_create
 * @apicovered				mv_image_tracking_model_create
 * @passcase				If mv_image_tracking_model_create returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mv_image_tracking_model_create
int ITc_mv_image_tracking_model_create_p(void)
{
    START_TEST_IMAGE;

    int nRet = -1;
    mv_image_tracking_model_h tracking_model;

    nRet = mv_image_tracking_model_create(&tracking_model);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_create", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase 				ITc_mv_image_tracking_model_set_target_p
 * @author            		SRID(nibha.sharma)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				To test mv_image_tracking_model_set_target
 * @scenario				Call mv_source_fill_by_buffer, mv_image_tracking_model_set_target
 * @apicovered				mv_source_fill_by_buffer, mv_image_tracking_model_set_target
 * @passcase				If mv_image_tracking_model_set_target returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mv_image_tracking_model_set_target
int ITc_mv_image_tracking_model_set_target_p(void)
{
    START_TEST_IMAGE;
    
	if( !(g_bIsBarcodeGenerationFeatureSupported || g_bIsBarcodeDetectionFeatureSupported) )
	{
		FPRINTF("[Line : %d][%s] Bar code feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
    int nRet = -1;
    mv_source_h hTargetImage;
    mv_image_tracking_model_h hTargetTrackingModel;
    mv_image_object_h hTarget;

    nRet = mv_create_source(&hTargetImage);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));

	char pszFilePath[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath(PATHPFXTAR, pszFilePath) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_image_object_create(&hTarget);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_create", MediaVisionGetError(nRet));

    nRet = image_load(pszFilePath, hTargetImage);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "image_load", MediaVisionGetError(nRet));

    nRet = mv_image_object_fill(hTarget, NULL, hTargetImage, NULL);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_fill", MediaVisionGetError(nRet));

    nRet = mv_image_tracking_model_create(&hTargetTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_create", MediaVisionGetError(nRet));

    nRet = mv_image_tracking_model_set_target(hTarget, hTargetTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_set_target", MediaVisionGetError(nRet));

    nRet = mv_image_tracking_model_destroy(hTargetTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_destroy", MediaVisionGetError(nRet));
	
	nRet = mv_destroy_source(hTargetImage);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_source", MediaVisionGetError(nRet));

    nRet = mv_image_object_destroy(hTarget);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_destroy", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase 				ITc_mv_image_tracking_model_destroy_p
 * @author            		SRID(nibha.sharma)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				To test mv_image_tracking_model_destroy
 * @scenario				Call mv_image_tracking_model_create and mv_image_tracking_model_destroy
 * @apicovered				mv_image_tracking_model_create and mv_image_tracking_model_destroy
 * @passcase				If mv_image_tracking_model_destroy returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mv_image_tracking_model_destroy
int ITc_mv_image_tracking_model_destroy_p(void)
{
    START_TEST_IMAGE;

    int nRet = -1;
    mv_image_tracking_model_h hTrackingModel;

    nRet = mv_image_tracking_model_create(&hTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_create", MediaVisionGetError(nRet));

    nRet = mv_image_tracking_model_destroy(hTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_destroy", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase 				ITc_mv_image_tracking_model_refresh_p
 * @author            		SRID(nibha.sharma)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				To test mv_image_tracking_model_refresh
 * @scenario				Call mv_image_tracking_model_set_target, mv_image_tracking_model_refresh
 * @apicovered				mv_image_tracking_model_set_target, mv_image_tracking_model_refresh
 * @passcase				If mv_image_tracking_model_refresh returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mv_image_tracking_model_refresh
int ITc_mv_image_tracking_model_refresh_p(void)
{
    START_TEST_IMAGE;
    
	if( !(g_bIsBarcodeGenerationFeatureSupported || g_bIsBarcodeDetectionFeatureSupported) )
	{
		FPRINTF("[Line : %d][%s] Bar code feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
    int nRet = -1;
    mv_source_h hTargetImage;
    mv_image_tracking_model_h hTrackingModel;
    mv_image_object_h hTarget;

    char pszFilePath[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath(PATHPFXTAR, pszFilePath) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_create_source(&hTargetImage);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));

	nRet = image_load(pszFilePath, hTargetImage);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "image_load", MediaVisionGetError(nRet));

    nRet = mv_image_object_create(&hTarget);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_create", MediaVisionGetError(nRet));
	
	nRet = mv_create_engine_config(&g_hMvEngineConfig);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_engine_config", MediaVisionGetError(nRet));
    CHECK_HANDLE(g_hMvEngineConfig, "mv_create_engine_config");

    nRet = mv_image_object_fill(hTarget, g_hMvEngineConfig, hTargetImage, NULL);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_fill", MediaVisionGetError(nRet));

    nRet = mv_image_tracking_model_create(&hTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_create", MediaVisionGetError(nRet));

    nRet = mv_image_tracking_model_set_target(hTarget, hTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_set_target", MediaVisionGetError(nRet));

    nRet = mv_image_tracking_model_refresh(hTrackingModel, NULL);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_refresh", MediaVisionGetError(nRet));

    nRet = mv_image_tracking_model_destroy(hTrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_destroy", MediaVisionGetError(nRet));
	
	if(g_hMvEngineConfig != NULL)
	{
		nRet = mv_destroy_engine_config(g_hMvEngineConfig);
		g_hMvEngineConfig = NULL;
		PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_engine_config", MediaVisionGetError(nRet));
	}

    nRet = mv_image_object_destroy(hTarget);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_destroy", MediaVisionGetError(nRet));

    nRet = mv_destroy_source(hTargetImage);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_source", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase 				ITc_mv_image_tracking_model_clone_p
 * @author            		SRID(nibha.sharma)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				To test mv_image_tracking_model_clone
 * @scenario				Call mv_image_tracking_model_create, mv_image_tracking_model_clone and mv_image_tracking_model_save
 * @apicovered				mv_image_tracking_model_create, mv_image_tracking_model_clone and mv_image_tracking_model_save
 * @passcase				If mv_image_tracking_model_clone and mv_image_tracking_model_save returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mv_image_tracking_model_clone 
int ITc_mv_image_tracking_model_clone_p(void)
{
    START_TEST_IMAGE;

    int nRet = -1;
    mv_image_tracking_model_h hTrackingModelSrc = NULL;
    mv_image_tracking_model_h hTrackingModelDst = NULL;

    nRet = mv_image_tracking_model_create(&hTrackingModelSrc);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_create", MediaVisionGetError(nRet));

    nRet = mv_image_tracking_model_clone(hTrackingModelSrc, &hTrackingModelDst);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_clone", MediaVisionGetError(nRet));

    char pszFilePath_s[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath("test_img_s", pszFilePath_s) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_image_tracking_model_save(pszFilePath_s, hTrackingModelSrc);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_save", MediaVisionGetError(nRet));

    char pszFilePath_d[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath("test_img_d", pszFilePath_d) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_image_tracking_model_save(pszFilePath_d, hTrackingModelDst);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_save", MediaVisionGetError(nRet));

    bool compare_models = checkModelFile(pszFilePath_s, pszFilePath_d);
    if (TRUE != compare_models)
    {
        FPRINTF("[Line : %d][%s] model not matches\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_image_tracking_model_destroy(hTrackingModelSrc);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_destroy", MediaVisionGetError(nRet));

    nRet = mv_image_tracking_model_destroy(hTrackingModelDst);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_destroy", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase 				ITc_mv_image_tracking_model_save_load_p
 * @author            		SRID(nibha.sharma)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				To test mv_image_tracking_model_load and mv_image_tracking_model_save
 * @scenario				Call mv_image_tracking_model_create, mv_image_tracking_model_save,mv_image_tracking_model_load
 * @apicovered				mv_image_tracking_model_create, mv_image_tracking_model_save,mv_image_tracking_model_load
 * @passcase				If mv_image_tracking_model_load and mv_image_tracking_model_save returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mv_image_tracking_model_load and mv_image_tracking_model_save
int ITc_mv_image_tracking_model_save_load_p(void)
{
    START_TEST_IMAGE;

    int nRet = -1;
    mv_image_tracking_model_h hSourceModel = NULL;

    nRet = mv_image_tracking_model_create(&hSourceModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_create", MediaVisionGetError(nRet));

    char pszFilePath[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath("tracking_model.txt", pszFilePath) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_image_tracking_model_save(pszFilePath, hSourceModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_save", MediaVisionGetError(nRet));

    nRet = mv_image_tracking_model_destroy(hSourceModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_destroy", MediaVisionGetError(nRet));

    nRet = mv_image_tracking_model_load(pszFilePath, &hSourceModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_load", MediaVisionGetError(nRet));

    nRet = mv_image_tracking_model_destroy(hSourceModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_destroy", MediaVisionGetError(nRet));

    return 0;
}

/**
 * @testcase 				ITc_mv_image_recognize_p
 * @author            		SRID(nibha.sharma)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				To test mv_image_recognize
 * @scenario				Call mv_image_object_create, mv_image_recognize
 * @apicovered				mv_image_object_create, mv_image_recognize
 * @passcase				If mv_image_recognize returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			mv_image_object_create
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mv_image_recognize
int ITc_mv_image_recognize_p(void)
{
    START_TEST_IMAGE;
    
	if( !(g_bIsBarcodeGenerationFeatureSupported || g_bIsBarcodeDetectionFeatureSupported) )
	{
		FPRINTF("[Line : %d][%s] Bar code feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
    int nRet = -1;
    mv_source_h hTargetImage;
    mv_image_object_h target;
    mv_source_h scene_image;


    char pszFilePath[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath(PATHPFXTAR, pszFilePath) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    char pszFilePathImage[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath(PATHPFXSCENE, pszFilePathImage) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_create_source(&hTargetImage);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));
    CHECK_HANDLE(hTargetImage, "mv_create_source");

    nRet = image_load(pszFilePath, hTargetImage);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "image_load", MediaVisionGetError(nRet));

    nRet = mv_image_object_create(&target);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_create", MediaVisionGetError(nRet));
	
	nRet = mv_create_engine_config(&g_hMvEngineConfig);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_engine_config", MediaVisionGetError(nRet));
    CHECK_HANDLE(g_hMvEngineConfig, "mv_create_engine_config");

    nRet = mv_image_object_fill(target, g_hMvEngineConfig, hTargetImage, NULL);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_fill", MediaVisionGetError(nRet));

    nRet = mv_create_source(&scene_image);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));

    nRet = image_load(pszFilePathImage, scene_image);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "image_load", MediaVisionGetError(nRet));
	
    nRet = mv_image_recognize(scene_image, &target, 1, g_hMvEngineConfig, MvRecognizedCB, "scene_image");
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_recognize", MediaVisionGetError(nRet));

    nRet = mv_destroy_source(scene_image);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_source", MediaVisionGetError(nRet));
	
	if(g_hMvEngineConfig != NULL)
	{
		nRet = mv_destroy_engine_config(g_hMvEngineConfig);
		g_hMvEngineConfig = NULL;
		PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_engine_config", MediaVisionGetError(nRet));
	}

    nRet = mv_image_object_destroy(target);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_destroy", MediaVisionGetError(nRet));

    nRet = mv_destroy_source(hTargetImage);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_source", MediaVisionGetError(nRet));

    return 0;
}


/**
 * @testcase 				ITc_mv_image_track_p
 * @author            		SRID(nibha.sharma)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				To test mv_image_track
 * @scenario				Call mv_source_fill_by_buffer, mv_image_object_create,mv_image_tracking_model_create,mv_image_tracking_model_set_target,mv_image_track
 * @apicovered				mv_source_fill_by_buffer, mv_image_object_create,mv_image_tracking_model_create,mv_image_tracking_model_set_target,mv_image_track
 * @passcase				If mv_image_track returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			mv_source_fill_by_buffer
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mv_image_track
int ITc_mv_image_track_p(void)
{
     START_TEST_IMAGE;
    
	if( !(g_bIsBarcodeGenerationFeatureSupported || g_bIsBarcodeDetectionFeatureSupported) )
	{
		FPRINTF("[Line : %d][%s] Bar code feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	};

    int nRet = -1;

    mv_source_h hTargetImage;
    mv_image_object_h hTarget;
    mv_source_h hFrameImage;
    mv_image_tracking_model_h hImageTtrackingModel;
    int frame_num = 0;

    nRet = mv_create_source(&hTargetImage);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));

	char pszFilePath[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath(PATHPFXTAR, pszFilePath) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    char pszFilePathImage[PATHLEN] = {0,};
    if ( false == MediaVisionAppendToAppDataPath(PATHPFXSCENE, pszFilePathImage) )
    {
        FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    nRet = mv_image_object_create(&hTarget);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_create", MediaVisionGetError(nRet));

    nRet = image_load(pszFilePath, hTargetImage);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "image_load", MediaVisionGetError(nRet));	

	nRet = mv_create_engine_config(&g_hMvEngineConfig);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_engine_config", MediaVisionGetError(nRet));
    CHECK_HANDLE(g_hMvEngineConfig, "mv_create_engine_config");

    nRet = mv_image_object_fill(hTarget, g_hMvEngineConfig, hTargetImage, NULL);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_fill", MediaVisionGetError(nRet));

    nRet = mv_image_tracking_model_create(&hImageTtrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_create", MediaVisionGetError(nRet));

    nRet = mv_image_tracking_model_set_target(hTarget, hImageTtrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_set_target", MediaVisionGetError(nRet));

    nRet = mv_create_source(&hFrameImage);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));

	nRet = image_load(pszFilePathImage, hFrameImage);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "image_load", MediaVisionGetError(nRet));
   
    nRet = mv_image_track( hFrameImage, hImageTtrackingModel, g_hMvEngineConfig, MvTrackedCB, &frame_num);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_track", MediaVisionGetError(nRet));

    nRet = mv_destroy_source(hFrameImage);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_source", MediaVisionGetError(nRet));

    nRet = mv_image_tracking_model_destroy(hImageTtrackingModel);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_tracking_model_destroy", MediaVisionGetError(nRet));

    nRet = mv_image_object_destroy(hTarget);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_image_object_destroy", MediaVisionGetError(nRet));

    nRet = mv_destroy_source(hTargetImage);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_source", MediaVisionGetError(nRet));

    return 0;
}
/** @} */
/** @} */
