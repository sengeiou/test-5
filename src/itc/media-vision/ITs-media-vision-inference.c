//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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

static mv_inference_h gInferenceHandle = NULL;
static mv_engine_config_h gEngineConfigHandle = NULL;
static mv_source_h gSourceHandle = NULL;
const char *gInferenceExampleDir = NULL;
int  g_nRetVal;
bool g_bResultNumber;
bool g_bIsGetPoseLandmark;
int g_nNumberOfLandmarks;
int g_nNumberOfPoses;
float g_PoseCompareScore;
int g_nLabel;

#define IC_MODEL_FILENAME "ic_tflite_model.tflite"
#define IC_MODEL_META_FILENAME "ic_tflite_model_meta.json"
#define IC_LABEL_FILENAME "ic_label.txt"

#define OD_MODEL_FILENAME "od_tflite_model.tflite"
#define OD_MODEL_META_FILENAME "od_tflite_model_meta.json"
#define OD_LABEL_FILENAME "od_label.txt"

#define FD_MODEL_FILENAME "fd_tflite_model1.tflite"
#define FD_MODEL_META_FILENAME "fd_tflite_model1_meta.json"

#define FLD_MODEL_FILENAME "fld_tflite_model1.tflite"
#define FLD_MODEL_META_FILENAME "fld_tflite_model1_meta.json"

#define PLD_MODEL_FILENAME "pld_tflite_model.tflite"
#define PLD_MODEL_META_FILENAME "pld_tflite_model_meta.json"
#define PLD_POSE_MAPPING_FILENAME "pld_pose_mapping.txt"
#define PLD_MOCAP_FILEAME "pld_mocap.bvh"
#define PLD_MOCAP_MAPPING_FILENAME "pld_mocap_mapping.txt"

//& set: MediaVision

/** @addtogroup itc-media-vision
*  @ingroup itc
*  @{
*/

/**
 * @function 		LoadImageToMediaSOurce
 * @description	 	Helper Function for load image to media source
 * @parameter		const char *file_path, mv_source_h source
 * @return 		On success 0 and non zero value on failure
 */
static int LoadImageToMediaSOurce(
        const char *file_path,
        mv_source_h source)
{
    if (NULL == file_path || NULL == source)
    {

	FPRINTF("File path or source is NULL\n");
        return MEDIA_VISION_ERROR_INVALID_PARAMETER;
    }

    unsigned long width = 0;
    unsigned long height = 0;
    unsigned long long buffer_size = 0;
    unsigned char *data_buffer = NULL;
    int nRet = IMAGE_UTIL_ERROR_NONE;
    int nRetMedia = MEDIA_VISION_ERROR_NONE;
    image_util_decode_h _decoder = NULL;

    nRet = image_util_decode_create(&_decoder);
    if(nRet != IMAGE_UTIL_ERROR_NONE)
    {
	FPRINTF("image_util_decode_create is failed \n");
	return 1;
    }

    nRet = image_util_decode_set_input_path(_decoder, file_path);
    if(nRet != IMAGE_UTIL_ERROR_NONE)
    {
	FPRINTF("image_util_decode_set_input_path is failed \n");
	image_util_decode_destroy(_decoder);
	return 1;
    }
    nRet = image_util_decode_set_colorspace(_decoder, IMAGE_UTIL_COLORSPACE_RGB888);
    if(nRet != IMAGE_UTIL_ERROR_NONE)
    {
	FPRINTF("image_util_decode_set_colorspace is failed \n");
	image_util_decode_destroy(_decoder);
	return 1;
    }
    nRet = image_util_decode_set_output_buffer(_decoder, &data_buffer);
    if(nRet != IMAGE_UTIL_ERROR_NONE)
    {
	FPRINTF("image_util_decode_set_output_buffer is failed \n");
	image_util_decode_destroy(_decoder);
	return 1;
    }
    nRet = image_util_decode_run(_decoder, &width, &height, &buffer_size);
    if(nRet != IMAGE_UTIL_ERROR_NONE)
    {
	FPRINTF("image_util_decode_run is failed \n");
	image_util_decode_destroy(_decoder);
	return 1;
    }
    // Only grayscale and RGB jpegs in test set:
    mv_colorspace_e source_colorspace = MEDIA_VISION_COLORSPACE_RGB888;

    nRetMedia = mv_source_clear(source);
    if(nRet != MEDIA_VISION_ERROR_NONE)
    {
	FPRINTF("mv_source_clear is failed \n");
	image_util_decode_destroy(_decoder);
	return 1;
    }
    nRetMedia = mv_source_fill_by_buffer(
                    source, data_buffer, (unsigned int)buffer_size,
                    (unsigned int)width, (unsigned int)height,
                    source_colorspace);
    if(nRet != MEDIA_VISION_ERROR_NONE)
    {
	FPRINTF("mv_source_fill_by_buffer is failed \n");
	image_util_decode_destroy(_decoder);
	return 1;
    }

    image_util_decode_destroy(_decoder);
    return MEDIA_VISION_ERROR_NONE;
}

/**
 * @function 		SetFacialLandmarkDetectionEngineConfigParameter
 * @description	 	Helper Function for setting face detection settings
 * @parameter		v_engine_config_h engineCfg
 * @return 		On success 0 and non zero value on failure
 */
static int SetFacialLandmarkDetectionEngineConfigParameter(mv_engine_config_h engineCfg)
{
    int nRet = MEDIA_VISION_ERROR_NONE;

    char modelFilename[1024];
    char modelMetaFilename[1024];
    snprintf(modelFilename, 1024, "%s/models/%s", gInferenceExampleDir, FLD_MODEL_FILENAME);
    snprintf(modelMetaFilename, 1024, "%s/models/%s", gInferenceExampleDir, FLD_MODEL_META_FILENAME);

    nRet = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_WEIGHT_FILE_PATH,
                        modelFilename);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_string_attribute", MediaVisionGetError(nRet));
    nRet = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_META_FILE_PATH,
                        modelMetaFilename);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_string_attribute", MediaVisionGetError(nRet));

    nRet = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_BACKEND_TYPE,
                        MV_INFERENCE_BACKEND_TFLITE);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_int_attribute", MediaVisionGetError(nRet));
    nRet = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_TARGET_DEVICE_TYPE,
                        MV_INFERENCE_TARGET_DEVICE_CPU);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_int_attribute", MediaVisionGetError(nRet));

    return nRet;
}

/**
 * @function 		SetFaceDetectionEngineConfigParameter
 * @description	 	Helper Function for setting face detection settings
 * @parameter		v_engine_config_h engineCfg
 * @return 		On success 0 and non zero value on failure
 */
static int SetFaceDetectionEngineConfigParameter(mv_engine_config_h engineCfg)
{
    int nRet = MEDIA_VISION_ERROR_NONE;

    char modelFilename[1024];
    char modelMetaFilename[1024];
    snprintf(modelFilename, 1024, "%s/models/%s", gInferenceExampleDir, FD_MODEL_FILENAME);
    snprintf(modelMetaFilename, 1024, "%s/models/%s", gInferenceExampleDir, FD_MODEL_META_FILENAME);

    nRet = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_WEIGHT_FILE_PATH,
                        modelFilename);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_string_attribute", MediaVisionGetError(nRet));
    nRet = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_META_FILE_PATH,
                        modelMetaFilename);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_string_attribute", MediaVisionGetError(nRet));

    nRet = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_BACKEND_TYPE,
                        MV_INFERENCE_BACKEND_TFLITE);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_int_attribute", MediaVisionGetError(nRet));
    nRet = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_TARGET_DEVICE_TYPE,
                        MV_INFERENCE_TARGET_DEVICE_CPU);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_int_attribute", MediaVisionGetError(nRet));

    return nRet;
}

/**
 * @function 		SetObjectDetectionEngineConfigParameter
 * @description	 	Helper Function for setting Object detection settings
 * @parameter		v_engine_config_h engineCfg
 * @return 		On success 0 and non zero value on failure
 */
static int SetObjectDetectionEngineConfigParameter(mv_engine_config_h engineCfg)
{
    int nRet = MEDIA_VISION_ERROR_NONE;

    char modelFilename[1024];
    char modelMetaFilename[1024];
    char labelFilename[1024];
    snprintf(modelFilename, 1024, "%s/models/%s", gInferenceExampleDir, OD_MODEL_FILENAME);
    snprintf(modelMetaFilename, 1024, "%s/models/%s", gInferenceExampleDir, OD_MODEL_META_FILENAME);
    snprintf(labelFilename, 1024, "%s/models/%s", gInferenceExampleDir, OD_LABEL_FILENAME);

    nRet = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_WEIGHT_FILE_PATH,
                        modelFilename);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_string_attribute", MediaVisionGetError(nRet));
    nRet = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_META_FILE_PATH,
                        modelMetaFilename);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_string_attribute", MediaVisionGetError(nRet));
    nRet = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_USER_FILE_PATH,
                        labelFilename);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_string_attribute", MediaVisionGetError(nRet));

    nRet = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_BACKEND_TYPE,
                        MV_INFERENCE_BACKEND_TFLITE);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_int_attribute", MediaVisionGetError(nRet));
    nRet = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_TARGET_DEVICE_TYPE,
                        MV_INFERENCE_TARGET_DEVICE_CPU);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_int_attribute", MediaVisionGetError(nRet));

    return nRet;
}

/**
 * @function 		SetImageClassificationEngineConfigParameter
 * @description	 	Helper Function for setting image classification
 * @parameter		v_engine_config_h engineCfg
 * @return 		On success 0 and non zero value on failure
 */
static int SetImageClassificationEngineConfigParameter(mv_engine_config_h engineCfg)
{
    int nRet = -1;

    char modelFilename[1024];
    char modelMetaFilename[1024];
    char labelFilename[1024];
    snprintf(modelFilename, 1024, "%s/models/%s", gInferenceExampleDir, IC_MODEL_FILENAME);
    snprintf(modelMetaFilename, 1024, "%s/models/%s", gInferenceExampleDir, IC_MODEL_META_FILENAME);
    snprintf(labelFilename, 1024, "%s/models/%s", gInferenceExampleDir, IC_LABEL_FILENAME);

    nRet = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_WEIGHT_FILE_PATH,
                        modelFilename);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_string_attribute", MediaVisionGetError(nRet));
    nRet = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_META_FILE_PATH,
                        modelMetaFilename);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_string_attribute", MediaVisionGetError(nRet));
    nRet = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_USER_FILE_PATH,
                        labelFilename);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_string_attribute", MediaVisionGetError(nRet));

    nRet = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_BACKEND_TYPE,
                        MV_INFERENCE_BACKEND_TFLITE);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_int_attribute", MediaVisionGetError(nRet));
    nRet = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_TARGET_DEVICE_TYPE,
                        MV_INFERENCE_TARGET_DEVICE_CPU);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_int_attribute", MediaVisionGetError(nRet));

    return nRet;
}

/**
 * @function 		SetPoseLandmarkDetectionEngineConfig
 * @description	 	Helper Function for pose landmark detection engine config
 * @parameter		v_engine_config_h engineCfg
 * @return 		On success 0 and non zero value on failure
 */
static int SetPoseLandmarkDetectionEngineConfig(mv_engine_config_h engineCfg)
{
	int nRet = -1;

	char modelFilename[PATHLEN];
    char modelMetaFilename[PATHLEN];
	char poseMappingFilename[PATHLEN];
	snprintf(modelFilename, PATHLEN, "%s/models/%s",
                            gInferenceExampleDir, PLD_MODEL_FILENAME);
    snprintf(modelMetaFilename, PATHLEN, "%s/models/%s",
                            gInferenceExampleDir, PLD_MODEL_META_FILENAME);
	snprintf(poseMappingFilename, PATHLEN, "%s/models/%s",
                            gInferenceExampleDir, PLD_POSE_MAPPING_FILENAME);

	nRet = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_WEIGHT_FILE_PATH,
                        modelFilename);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_string_attribute", MediaVisionGetError(nRet));

	nRet = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_META_FILE_PATH,
                        modelMetaFilename);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_string_attribute", MediaVisionGetError(nRet));

	nRet = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_USER_FILE_PATH,
                        poseMappingFilename);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_string_attribute", MediaVisionGetError(nRet));

	nRet = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_BACKEND_TYPE,
                        MV_INFERENCE_BACKEND_TFLITE);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_int_attribute", MediaVisionGetError(nRet));

	nRet = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_TARGET_DEVICE_TYPE,
                        MV_INFERENCE_TARGET_DEVICE_CPU);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_int_attribute", MediaVisionGetError(nRet));

	return nRet;
}

/**
 * @function 		ImageClassifiyCB
 * @description	 	Callback Function
 * @parameter		mv_source_h source, int number_of_classes,const int *indices, const char **names, const float *confidences, void *user_data
 * @return 			NA
 */
static void ImageClassifiyCB(mv_source_h source,
                        int number_of_classes,
                        const int *indices,
                        const char **names,
                        const float *confidences,
                        void *user_data)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] Inside ImageClassifiyCB callback \\n", __LINE__, API_NAMESPACE);
#endif

    g_CallBackHit = true;
}

/**
 * @function 		ObjectDetectionCB
 * @description	 	Callback Function
 * @parameter		mv_source_h source, int number_of_object,const , int *indices, const char **names, const float *confidences, const mv_rectangle_s *locations, void *user_data
 * @return 			NA
 */
static void ObjectDetectionCB(mv_source_h source,
                        int number_of_object,
                        const int *indices,
                        const char **names,
                        const float *confidences,
                        const mv_rectangle_s *locations,
                        void *user_data)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] Inside ObjectDetectionCB callback \\n", __LINE__, API_NAMESPACE);
#endif
    g_CallBackHit = true;
}

/**
 * @function 		FaceDetectionCB
 * @description	 	Callback Function
 * @parameter		mv_source_h source, int number_of_faces,  const float *confidences,const mv_rectangle_s *locations, void *user_data
 * @return 		NA
 */
static void FaceDetectionCB (mv_source_h source,
                        int number_of_faces,
                        const float *confidences,
                        const mv_rectangle_s *locations,
                        void *user_data)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] Inside FaceDetectionCB callback \\n", __LINE__, API_NAMESPACE);
#endif
    g_CallBackHit = true;
}

/**
 * @function 		FaceLandmarkDetectionCB
 * @description	 	Callback Function
 * @parameter		mv_source_h source, int number_of_landmark, const mv_rectangle_s *locations, void *user_data
 * @return 		NA
 */
static void FaceLandmarkDetectionCB (mv_source_h source,
                        int number_of_landmark,
                        const mv_rectangle_s *locations,
                        void *user_data)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] Inside FaceLandmarkDetectionCB callback \\n", __LINE__, API_NAMESPACE);
#endif
    g_CallBackHit = true;
}

/**
 * @function 		SupportedInferenceCB
 * @description	 	Callback Function
 * @parameter		const char *engine, bool supported, void *user_data
 * @return 		NA
 */
static bool SupportedInferenceCB(
                        const char *engine,
                        bool supported,
                        void *user_data)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] Inside SupportedInferenceCB callback \\n", __LINE__, API_NAMESPACE);
#endif
    g_CallBackHit = true;
}

/**
 * @function 		PoseLandmarkDetectedCB
 * @description	 	Callback Function
 * @parameter		mv_source_h source, mv_inference_pose_result_h locations, void *user_data
 * @return			NA
 */
static void PoseLandmarkDetectedCB(mv_source_h source, mv_inference_pose_result_h locations, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Inside PoseLandmarkDetectedCB callback \\n", __LINE__, API_NAMESPACE);
#endif
	g_CallBackHit = true;
}

/**
 * @function 		GetPoseLandmarkDetectedResultCB
 * @description	 	Callback Function
 * @parameter		mv_source_h source, mv_inference_pose_result_h result, void *user_data
 * @return			NA
 */
static void GetPoseLandmarkDetectedResultCB(mv_source_h source, mv_inference_pose_result_h result, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Inside GetPoseLandmarkDetectedResultCB callback \\n", __LINE__, API_NAMESPACE);
#endif
	g_CallBackHit = true;
	 g_nRetVal = mv_inference_pose_get_number_of_poses(result, &g_nNumberOfPoses);
}

/**
 * @function 		GetNumberOfLandmarksCB
 * @description	 	Callback Function
 * @parameter		mv_source_h source, mv_inference_pose_result_h result, void *user_data
 * @return			NA
 */
static void GetNumberOfLandmarksCB(mv_source_h source, mv_inference_pose_result_h result, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Inside GetNumberOfLandmarksCB callback \\n", __LINE__, API_NAMESPACE);
#endif
	g_CallBackHit = true;

	 g_nRetVal = mv_inference_pose_get_number_of_landmarks(result, &g_nNumberOfLandmarks);
}

/**
 * @function 		GetLandmarkCB
 * @description	 	Callback Function
 * @parameter		mv_source_h source, mv_inference_pose_result_h result, void *user_data
 * @return			NA
 */
static void GetLandmarkCB(mv_source_h source, mv_inference_pose_result_h result, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Inside GetLandmarkCB callback \\n", __LINE__, API_NAMESPACE);
#endif
	g_CallBackHit = true;
	int nResultNumberOfPoses = -1;
	int nResultNumberOfLandmarks =  -1;
	static mv_point_s** resultLandmarks = NULL;
	static float** resultScore = NULL;

	 g_nRetVal = mv_inference_pose_get_number_of_poses(result, &nResultNumberOfPoses);
	if ( g_nRetVal != MEDIA_VISION_ERROR_NONE || nResultNumberOfPoses <= 0)
		return;

	 g_nRetVal = mv_inference_pose_get_number_of_landmarks(result, &nResultNumberOfLandmarks);
	if ( g_nRetVal != MEDIA_VISION_ERROR_NONE ||nResultNumberOfLandmarks < 0)
		return;

	resultLandmarks = (mv_point_s **)malloc(nResultNumberOfPoses * sizeof(mv_point_s *));
	resultScore = (float **)malloc(nResultNumberOfPoses * sizeof(float *));
	for (int nPose = 0; nPose < nResultNumberOfPoses; ++nPose)
	{
		resultLandmarks[nPose] = (mv_point_s *)malloc(nResultNumberOfLandmarks * sizeof(mv_point_s));
		resultScore[nPose] = (float *)malloc(nResultNumberOfLandmarks * sizeof(float));
		for (int part = 0; part < nResultNumberOfLandmarks; ++part) {
			 g_nRetVal = mv_inference_pose_get_landmark(result, nPose, part,
													&(resultLandmarks[nPose][part]),
													&(resultScore[nPose][part]));
			if ( g_nRetVal != MEDIA_VISION_ERROR_NONE)
				break;
		}
	}

	g_bIsGetPoseLandmark = true;

	if (resultLandmarks){
		for (int pose = 0; pose < nResultNumberOfPoses; ++pose)
			free(resultLandmarks[pose]);
		free(resultLandmarks);
		resultLandmarks = NULL;
	}

	if (resultScore){
		for (int pose = 0; pose < nResultNumberOfPoses; ++pose)
			free(resultScore[pose]);
		free(resultScore);
		resultScore = NULL;
	}
}

/**
 * @function 		GetPoseCB
 * @description	 	Callback Function
 * @parameter		mv_source_h source, mv_inference_pose_result_h result, void *user_data
 * @return			NA
 */
static void GetPoseCB(mv_source_h source, mv_inference_pose_result_h result, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Inside GetPoseCB callback \\n", __LINE__, API_NAMESPACE);
#endif
	g_CallBackHit = true;
	g_nRetVal = mv_inference_pose_get_number_of_poses(result, &g_nNumberOfPoses);
	if (g_nRetVal != MEDIA_VISION_ERROR_NONE)
		return;

	if (g_nNumberOfPoses <= 0)
		return;

	g_nRetVal = mv_inference_pose_get_label(result, 0, &g_nLabel);
}

/**
 * @function 		PoseCompareCB
 * @description	 	Callback Function
 * @parameter		mv_source_h source, mv_inference_pose_result_h result, void *user_data
 * @return			NA
 */
static void PoseCompareCB(mv_source_h source, mv_inference_pose_result_h result, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Inside PoseCompareCB callback \\n", __LINE__, API_NAMESPACE);
#endif
	g_CallBackHit = true;

	mv_pose_h *hPose = (mv_pose_h *)user_data;
	int nPart = MV_INFERENCE_HUMAN_BODY_PART_LEG_RIGHT | MV_INFERENCE_HUMAN_BODY_PART_LEG_LEFT;
	 g_nRetVal = mv_pose_compare(hPose, result, nPart, &g_PoseCompareScore);
}

/**
 * @function 		ITs_media_vision_inference_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */

void ITs_media_vision_inference_startup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] Inside ITs_media_vision_inference_startup \\n", __LINE__, API_NAMESPACE);
#endif
    struct stat stBuff;
    int nRet = -1;
    if ( stat(ERR_LOG, &stBuff) == 0 )
    {
        remove(ERR_LOG);
    }
    g_bMediavisionInferenceModelCreation = false;
    g_bMismatch = false;
    g_bIsVisionInferenceFeatureSupported = TCTCheckSystemInfoFeatureSupported(VISIONINFERENCEFEATURE, API_NAMESPACE);
    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    if (true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE)) {
	FPRINTF("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received %s\\n", __LINE__, API_NAMESPACE, pszValue);

        gInferenceExampleDir=(char*)calloc(strlen(pszValue)+strlen("/res/res/inference")+1, sizeof(char));
        snprintf(gInferenceExampleDir, strlen(pszValue)+strlen("/res/res/inference")+1, "%s/res/res/inference", pszValue);

    } else {
	FPRINTF("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
    }

    nRet = mv_inference_create(&gInferenceHandle);
    if(!g_bIsVisionInferenceFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] mv_inference_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)\\n", __FILE__, __LINE__,nRet);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] mv_inference_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)", __FILE__, __LINE__, nRet);
			g_bMismatch = true;
			return;
		}

		FPRINTF("[%s:%d] mv_inference_create is unsupported\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] mv_inference_create is unsupported", __FILE__, __LINE__);
		g_bMismatch = false;
	}
	else if ( nRet != MEDIA_VISION_ERROR_NONE )
	{
		FPRINTF("[%s:%d] mv_inference_create failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] mv_inference_create failed, error returned = (%d)", __FILE__, __LINE__,  nRet);
		g_bMediavisionInferenceModelCreation = false;
	}
	else
	{
		g_bMediavisionInferenceModelCreation = true;
	}

    nRet = mv_create_engine_config(&gEngineConfigHandle);
    if (MEDIA_VISION_ERROR_NONE != nRet) {
        gEngineConfigHandle = NULL;
	FPRINTF("[%s:%d] mv_create_engine_config failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
	g_bMediavisionInferenceModelCreation = false;
        return;
    }

    nRet = mv_create_source(&gSourceHandle);
    if (MEDIA_VISION_ERROR_NONE != nRet) {
        gSourceHandle = NULL;
        FPRINTF("[%s:%d] mv_create_source failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
	g_bMediavisionInferenceModelCreation = false;
        return;
    }
}


/**
 * @function 		ITs_media_vision_inference_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_vision_inference_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] Inside ITs_media_vision_inference_cleanup \\n", __LINE__, API_NAMESPACE);
#endif
    if (gInferenceHandle) {
        mv_inference_destroy(gInferenceHandle);
        gInferenceHandle = NULL;
    }

    if (gEngineConfigHandle) {
        mv_destroy_engine_config(gEngineConfigHandle);
        gEngineConfigHandle = NULL;
    }

    if (gSourceHandle) {
        mv_destroy_source(gSourceHandle);
        gSourceHandle = NULL;
    }

    if (gInferenceExampleDir) {
        free(gInferenceExampleDir);
        gInferenceExampleDir = NULL;
    }

    return;
}

/**
 * @testcase 				ITc_mediavision_mv_engine_set_get_array_string_attribute_p
 * @author            			SRID(manoj.g2)
 * @reviewer         			SRID(shobhit.v)
 * @type 				auto
 * @since_tizen 			5.5
 * @description				Set and Get mv engine array string attribute
 * @scenario				Set and Get mv engine array string attribute
 * @apicovered				mv_engine_config_set_array_string_attribute, mv_engine_config_get_array_string_attribute
 * @passcase				If mv_engine_config_set_array_string_attribute, mv_engine_config_get_array_string_attribute and Precondition APi's returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: Set and Get mv engine array string attribute
int ITc_mediavision_mv_engine_set_get_array_string_attribute_p(void)
{
    START_TEST_INFERENCE;
    int nRet = -1;
    char modelFilename[1024];
    char *inputNodeName = "INPUT_TENSOR_NAME";
    char *outputNodeName[1] = {"OUTPUT_TENSOR_NAME"};
    char *getOutPutName = NULL;
    snprintf(modelFilename, 1024, "%s/models/%s", gInferenceExampleDir, FLD_MODEL_FILENAME);
    const int expectedSize = 2;
    const char *expectedParameterValue[2] = {"output/node1", "output/node2"};
    int actualSize = 0;
    char **actualParameterValue = NULL;
    mv_engine_config_h hEngineHandler = NULL;
    int resultFlag = 0;

    nRet = mv_create_engine_config(&hEngineHandler);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_engine_config", MediaVisionGetError(nRet));
    CHECK_HANDLE(hEngineHandler, "mv_create_engine_config");

    nRet = mv_engine_config_set_array_string_attribute(hEngineHandler, "MV_INFERENCE_OUTPUT_NODE_NAMES", expectedParameterValue,2);
    PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_set_array_string_attribute", MediaVisionGetError(nRet), mv_destroy_engine_config(hEngineHandler));

    nRet = mv_engine_config_get_array_string_attribute(hEngineHandler, "MV_INFERENCE_OUTPUT_NODE_NAMES", &actualParameterValue, &actualSize);
    PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_engine_config_get_array_string_attribute", MediaVisionGetError(nRet), mv_destroy_engine_config(hEngineHandler));

    PRINT_RESULT(expectedSize, actualSize, "expected and actual size is not same", MediaVisionGetError(nRet));
    for (int i = 0; i < expectedSize; ++i) {
	if(strcmp(expectedParameterValue[i], actualParameterValue[i]) != 0)
	{
		FPRINTF("[%s:%d] Expected and actual parameter value is not same\\n", __FILE__, __LINE__);
		resultFlag = 1;
	}
    }

    nRet = mv_destroy_engine_config(hEngineHandler);
    PRINT_RESULT_NORETURN(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_engine_config", MediaVisionGetError(nRet));

    for (int i = 0; i < actualSize; ++i) {
        free(actualParameterValue[i]);
    }
    free(actualParameterValue);
    if(resultFlag)
	return 1;
    else
	return 0;
}


/**
 * @testcase 				ITc_mediavision_mv_inference_create_destroy_p
 * @author            			SRID(manoj.g2)
 * @reviewer         			SRID(shobhit.v)
 * @type 				auto
 * @since_tizen 			5.5
 * @description				To check for inference create and destroy handle
 * @scenario				To check for inference create and destroy handle
 * @apicovered				mv_inference_create, mv_inference_destroy
 * @passcase				If mv_inference_create, mv_inference_destroy returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To check for inference create and destroy handle
int ITc_mediavision_mv_inference_create_destroy_p(void)
{
    START_TEST_INFERENCE;
    int nRet = -1;
    mv_inference_h hInferenceHandle = NULL;

    nRet = mv_inference_create(&hInferenceHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_create", MediaVisionGetError(nRet));
    CHECK_HANDLE(hInferenceHandle, "mv_inference_create");

    nRet = mv_inference_destroy(hInferenceHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_destroy", MediaVisionGetError(nRet));
    return 0;
}

/**
 * @testcase 				ITc_mediavision_mv_inference_configure_p
 * @author            			SRID(manoj.g2)
 * @reviewer         			SRID(shobhit.v)
 * @type 				auto
 * @since_tizen 			5.5
 * @description				To configure inference handle
 * @scenario				To configure inference handle
 * @apicovered				mv_inference_configure
 * @passcase				If mv_inference_configure and Precondition API's returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To configure inference handle
int ITc_mediavision_mv_inference_configure_p(void)
{
    START_TEST_INFERENCE;
    int nRet = -1;

    nRet = SetImageClassificationEngineConfigParameter(gEngineConfigHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "SetImageClassificationEngineConfigParameter", MediaVisionGetError(nRet));

    nRet = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_configure", MediaVisionGetError(nRet));
    return 0;
}

/**
 * @testcase 				ITc_mediavision_mv_inference_prepare_p
 * @author            			SRID(manoj.g2)
 * @reviewer         			SRID(shobhit.v)
 * @type 				auto
 * @since_tizen 			5.5
 * @description				To prepare inference handle
 * @scenario				To prepare inference handle
 * @apicovered				mv_inference_prepare
 * @passcase				If mv_inference_prepare and Precondition API's returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To prepare inference handle
int ITc_mediavision_mv_inference_prepare_p(void)
{
    START_TEST_INFERENCE;
    int nRet = -1;

    nRet = SetImageClassificationEngineConfigParameter(gEngineConfigHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "SetImageClassificationEngineConfigParameter", MediaVisionGetError(nRet));

    nRet = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_configure", MediaVisionGetError(nRet));

    nRet = mv_inference_prepare(gInferenceHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_prepare", MediaVisionGetError(nRet));
    return 0;
}

/**
 * @testcase 				ITc_mediavision_mv_inference_foreach_supported_engine_p
 * @author            			SRID(manoj.g2)
 * @reviewer         			SRID(shobhit.v)
 * @type 				auto
 * @since_tizen 			5.5
 * @description				To foreach supported inference engine
 * @scenario				To foreach supported inference engine
 * @apicovered				mv_inference_foreach_supported_engine
 * @passcase				If mv_inference_foreach_supported_engine and Precondition API's returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To foreach supported inference engine
int ITc_mediavision_mv_inference_foreach_supported_engine_p(void)
{
    START_TEST_INFERENCE;
    int nRet = -1;

    nRet = mv_inference_foreach_supported_engine(gInferenceHandle, SupportedInferenceCB, NULL);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_foreach_supported_engine", MediaVisionGetError(nRet));
    PRINT_RESULT(g_CallBackHit, true, "callback not hit", MediaVisionGetError(nRet));
    return 0;
}

/**
 * @testcase 				ITc_mediavision_mv_inference_image_classify_p
 * @author            			SRID(manoj.g2)
 * @reviewer         			SRID(shobhit.v)
 * @type 				auto
 * @since_tizen 			5.5
 * @description				To classify image inference handle
 * @scenario				To classify image inference handle
 * @apicovered				mv_inference_image_classify
 * @passcase				If mv_inference_image_classify and Precondition API's returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To classify image inference handle
int ITc_mediavision_mv_inference_image_classify_p(void)
{
    START_TEST_INFERENCE;
    int nRet = -1;
    char pszImageFileName[1024];

    nRet = SetImageClassificationEngineConfigParameter(gEngineConfigHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "SetImageClassificationEngineConfigParameter", MediaVisionGetError(nRet));

    nRet = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_configure", MediaVisionGetError(nRet));

    nRet = mv_inference_prepare(gInferenceHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_prepare", MediaVisionGetError(nRet));

    snprintf(pszImageFileName, 1024, "%s/images/%s", gInferenceExampleDir, "banana.jpg");
    nRet = LoadImageToMediaSOurce(pszImageFileName, gSourceHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "LoadImageToMediaSOurce", MediaVisionGetError(nRet));

    g_CallBackHit = false;
    nRet = mv_inference_image_classify(gSourceHandle,
                                    gInferenceHandle,
                                    NULL,
                                    ImageClassifiyCB,
                                    NULL);
   PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_image_classify", MediaVisionGetError(nRet));
   PRINT_RESULT(g_CallBackHit, true, "callback not hit", MediaVisionGetError(nRet));
   return 0;
}

/**
 * @testcase 				ITc_mediavision_mv_inference_object_detect_p
 * @author            			SRID(manoj.g2)
 * @reviewer         			SRID(shobhit.v)
 * @type 				auto
 * @since_tizen 			5.5
 * @description				To Check for inference object detect
 * @scenario				To Check for inference object detect
 * @apicovered				mv_inference_object_detect
 * @passcase				If mv_inference_object_detect and Precondition API's returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To Check for inference object detect
int ITc_mediavision_mv_inference_object_detect_p(void)
{
    START_TEST_INFERENCE;
    int nRet = -1;
    char pszImageFileName[1024];

    nRet = SetObjectDetectionEngineConfigParameter(gEngineConfigHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "SetObjectDetectionEngineConfigParameter", MediaVisionGetError(nRet));

    nRet = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_configure", MediaVisionGetError(nRet));

    nRet = mv_inference_prepare(gInferenceHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_prepare", MediaVisionGetError(nRet));

    snprintf(pszImageFileName, 1024, "%s/images/%s", gInferenceExampleDir, "dog2.jpg");
    nRet = LoadImageToMediaSOurce(pszImageFileName, gSourceHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "LoadImageToMediaSOurce", MediaVisionGetError(nRet));

    g_CallBackHit = false;
    nRet = mv_inference_object_detect(gSourceHandle,
                                    gInferenceHandle,
                                    ObjectDetectionCB,
                                    NULL);

   PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_object_detect", MediaVisionGetError(nRet));
   PRINT_RESULT(g_CallBackHit, true, "callback not hit", MediaVisionGetError(nRet));
   return 0;
}


/**
 * @testcase 				ITc_mediavision_mv_inference_face_detect_p
 * @author            			SRID(manoj.g2)
 * @reviewer         			SRID(shobhit.v)
 * @type 				auto
 * @since_tizen 			5.5
 * @description				To Check for inference face detect
 * @scenario				To Check for inference face detect
 * @apicovered				mv_inference_face_detect
 * @passcase				If mv_inference_face_detect and Precondition API's returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To Check for inference face detect
int ITc_mediavision_mv_inference_face_detect_p(void)
{
    START_TEST_INFERENCE;
    int nRet = -1;
    char pszImageFileName[1024];

    nRet = SetFaceDetectionEngineConfigParameter(gEngineConfigHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "SetFaceDetectionEngineConfigParameter", MediaVisionGetError(nRet));

    nRet = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_configure", MediaVisionGetError(nRet));

    nRet = mv_inference_prepare(gInferenceHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_prepare", MediaVisionGetError(nRet));

    snprintf(pszImageFileName, 1024, "%s/images/%s", gInferenceExampleDir, "faceDetection.jpg");
    nRet = LoadImageToMediaSOurce(pszImageFileName, gSourceHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "LoadImageToMediaSOurce", MediaVisionGetError(nRet));

    g_CallBackHit = false;
    nRet = mv_inference_face_detect(gSourceHandle,
                                    gInferenceHandle,
                                    FaceDetectionCB,
                                    NULL);

   PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_face_detect", MediaVisionGetError(nRet));
   PRINT_RESULT(g_CallBackHit, true, "callback not hit", MediaVisionGetError(nRet));
   return 0;
}

/**
 * @testcase 				ITc_mediavision_mv_inference_facial_landmark_detect_p
 * @author            			SRID(manoj.g2)
 * @reviewer         			SRID(shobhit.v)
 * @type 				auto
 * @since_tizen 			5.5
 * @description				To Check for inference facial landmark detection
 * @scenario				To Check for inference facial landmark detection
 * @apicovered				mv_inference_facial_landmark_detect
 * @passcase				If mv_inference_facial_landmark_detect and Precondition API's returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To Check for inference facial landmark detection
int ITc_mediavision_mv_inference_facial_landmark_detect_p(void)
{
    START_TEST_INFERENCE;
    int nRet = -1;
    char pszImageFileName[1024];

    nRet = SetFacialLandmarkDetectionEngineConfigParameter(gEngineConfigHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "SetFacialLandmarkDetectionEngineConfigParameter", MediaVisionGetError(nRet));

    nRet = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_configure", MediaVisionGetError(nRet));

    nRet = mv_inference_prepare(gInferenceHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_prepare", MediaVisionGetError(nRet));

    snprintf(pszImageFileName, 1024, "%s/images/%s", gInferenceExampleDir, "faceLandmark.jpg");
    nRet = LoadImageToMediaSOurce(pszImageFileName, gSourceHandle);
    PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "LoadImageToMediaSOurce", MediaVisionGetError(nRet));

    g_CallBackHit = false;
    nRet = mv_inference_facial_landmark_detect(gSourceHandle,
                                    gInferenceHandle, NULL,
                                    FaceLandmarkDetectionCB,
                                    NULL);

   PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_facial_landmark_detect", MediaVisionGetError(nRet));
   PRINT_RESULT(g_CallBackHit, true, "callback not hit", MediaVisionGetError(nRet));
   return 0;
}

/**
 * @testcase 				ITc_mediavision_mv_inference_pose_landmark_detect_p
 * @author					SRID(priya.kohli)
 * @reviewer				SRID(shobhit.v)
 * @type					auto
 * @since_tizen 			6.0
 * @description				Performs pose landmarks detection.
 * @scenario				This function is used to launch pose landmark detection.
 *							Each time when mv_inference_pose_landmark_detect() is called
 *							detected_cb will receive a list of pose landmark's locations
 *							in the media source
 * @apicovered				mv_inference_pose_landmark_detect
 * @passcase				If mv_inference_pose_landmark_detect and Precondition API's returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To perform pose landmarks detection.
int ITc_mediavision_mv_inference_pose_landmark_detect_p(void)
{
	START_TEST_INFERENCE;
	int nRet = -1;
	char pszImageFileName[PATHLEN];

	nRet = SetPoseLandmarkDetectionEngineConfig(gEngineConfigHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "SetPoseLandmarkDetectionEngineConfig", MediaVisionGetError(nRet));

	nRet = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_configure", MediaVisionGetError(nRet));

	nRet = mv_inference_prepare(gInferenceHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_prepare", MediaVisionGetError(nRet));

	snprintf(pszImageFileName, PATHLEN, "%s/images/%s", gInferenceExampleDir, "poseLandmark.jpg");
	nRet = LoadImageToMediaSOurce(pszImageFileName, gSourceHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "LoadImageToMediaSOurce", MediaVisionGetError(nRet));

	g_CallBackHit = false;
	nRet = mv_inference_pose_landmark_detect(gSourceHandle, gInferenceHandle, NULL, PoseLandmarkDetectedCB, NULL);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_pose_landmark_detect", MediaVisionGetError(nRet));
	PRINT_RESULT(true, g_CallBackHit, "mv_inference_pose_landmark_detect", MediaVisionGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mediavision_mv_inference_get_number_of_poses_p
 * @author					SRID(priya.kohli)
 * @reviewer				SRID(shobhit.v)
 * @type					auto
 * @since_tizen 			6.0
 * @description				Gets the number of poses.
 * @scenario				Gets the number of poses.
 * @apicovered				mv_inference_pose_get_number_of_poses
 * @passcase				If mv_inference_pose_get_number_of_poses and Precondition API's returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To get the number of poses.
int ITc_mediavision_mv_inference_get_number_of_poses_p(void)
{
	START_TEST_INFERENCE;
	int nRet = -1;
	 g_nRetVal = -1;
	g_bResultNumber = -1;
	char pszImageFileName[PATHLEN];

	nRet = SetPoseLandmarkDetectionEngineConfig(gEngineConfigHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "SetPoseLandmarkDetectionEngineConfig", MediaVisionGetError(nRet));

	nRet = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_configure", MediaVisionGetError(nRet));

	nRet = mv_inference_prepare(gInferenceHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_prepare", MediaVisionGetError(nRet));

	snprintf(pszImageFileName, PATHLEN, "%s/images/%s", gInferenceExampleDir, "poseLandmark.jpg");
	nRet = LoadImageToMediaSOurce(pszImageFileName, gSourceHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "LoadImageToMediaSOurce", MediaVisionGetError(nRet));

	g_CallBackHit = false;
	nRet = mv_inference_pose_landmark_detect(gSourceHandle, gInferenceHandle, NULL, GetPoseLandmarkDetectedResultCB, NULL);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_pose_landmark_detect", MediaVisionGetError(nRet));
	PRINT_RESULT(true, g_CallBackHit, "mv_inference_pose_landmark_detect", MediaVisionGetError(nRet));
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE,  g_nRetVal, "mv_inference_pose_get_number_of_poses", MediaVisionGetError(nRet));

	if(g_nNumberOfPoses <= 0)
	{
		FPRINTF("[Line : %d][%s] Invalid value of  g_nNumberOfPoses, g_nNumberOfPoses = %d \\n", __LINE__, API_NAMESPACE, g_nNumberOfPoses);
		return 1;
	}

	return 0;
}

/**
 * @testcase 				ITc_mediavision_mv_inference_get_number_of_landmarks_p
 * @author					SRID(priya.kohli)
 * @reviewer				SRID(shobhit.v)
 * @type					auto
 * @since_tizen 			6.0
 * @description				Gets the number of landmarks per a pose.
 * @scenario				Gets the number of landmarks per a pose.
 * @apicovered				mv_inference_pose_get_number_of_landmarks
 * @passcase				If mv_inference_pose_get_number_of_landmarks and Precondition API's returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To get the number of landmarks per a pose.
int ITc_mediavision_mv_inference_get_number_of_landmarks_p(void)
{
	START_TEST_INFERENCE;
	int nRet = -1;
	 g_nRetVal = -1;
	g_bResultNumber = -1;
	char pszImageFileName[PATHLEN];

	nRet = SetPoseLandmarkDetectionEngineConfig(gEngineConfigHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "SetPoseLandmarkDetectionEngineConfig", MediaVisionGetError(nRet));

	nRet = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_configure", MediaVisionGetError(nRet));

	nRet = mv_inference_prepare(gInferenceHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_prepare", MediaVisionGetError(nRet));

	snprintf(pszImageFileName, PATHLEN, "%s/images/%s", gInferenceExampleDir, "poseLandmark.jpg");
	nRet = LoadImageToMediaSOurce(pszImageFileName, gSourceHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "LoadImageToMediaSOurce", MediaVisionGetError(nRet));

	g_CallBackHit = false;
	nRet = mv_inference_pose_landmark_detect(gSourceHandle, gInferenceHandle, NULL, GetNumberOfLandmarksCB, NULL);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_pose_landmark_detect", MediaVisionGetError(nRet));
	PRINT_RESULT(true, g_CallBackHit, "mv_inference_pose_landmark_detect", MediaVisionGetError(nRet));
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE,  g_nRetVal, "mv_inference_pose_get_number_of_landmarks", MediaVisionGetError(nRet));

	if(g_nNumberOfLandmarks <= 0)
	{
		FPRINTF("[Line : %d][%s] Invalid value of  g_nNumberOfLandmarks, g_nNumberOfLandmarks = %d \\n", __LINE__, API_NAMESPACE, g_nNumberOfLandmarks);
		return 1;
	}

	return 0;
}

/**
 * @testcase 				ITc_mediavision_mv_inference_get_landmark_p
 * @author					SRID(priya.kohli)
 * @reviewer				SRID(shobhit.v)
 * @type					auto
 * @since_tizen 			6.0
 * @description				Gets landmark location of a part of a pose.
 * @scenario				Gets landmark location of a part of a pose.
 * @apicovered				mv_inference_pose_get_landmark
 * @passcase				If mv_inference_pose_get_landmark and Precondition API's returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To get landmark location of a part of a pose.
int ITc_mediavision_mv_inference_get_landmark_p(void)
{
	START_TEST_INFERENCE;
	int nRet = -1;
	g_bResultNumber = -1;
	char pszImageFileName[PATHLEN];

	nRet = SetPoseLandmarkDetectionEngineConfig(gEngineConfigHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "SetPoseLandmarkDetectionEngineConfig", MediaVisionGetError(nRet));

	nRet = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_configure", MediaVisionGetError(nRet));

	nRet = mv_inference_prepare(gInferenceHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_prepare", MediaVisionGetError(nRet));

	snprintf(pszImageFileName, PATHLEN, "%s/images/%s", gInferenceExampleDir, "poseLandmark.jpg");
	nRet = LoadImageToMediaSOurce(pszImageFileName, gSourceHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "LoadImageToMediaSOurce", MediaVisionGetError(nRet));

	g_CallBackHit = false;
	g_bIsGetPoseLandmark = false;

	nRet = mv_inference_pose_landmark_detect(gSourceHandle, gInferenceHandle, NULL, GetLandmarkCB, NULL);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_pose_landmark_detect", MediaVisionGetError(nRet));
	PRINT_RESULT(true, g_CallBackHit, "mv_inference_pose_landmark_detect", MediaVisionGetError(nRet));
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE,  g_nRetVal, "mv_inference_pose_landmark_detect", MediaVisionGetError(nRet));
	PRINT_RESULT(true, g_bIsGetPoseLandmark, "mv_inference_pose_get_landmark", MediaVisionGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mediavision_mv_inference_pose_get_label_p
 * @author					SRID(priya.kohli)
 * @reviewer				SRID(shobhit.v)
 * @type					auto
 * @since_tizen 			6.0
 * @description				Gets a label of a pose
 * @scenario				Gets a label of a pose
 * @apicovered				mv_inference_pose_get_label
 * @passcase				If mv_inference_pose_get_label and Precondition API's returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To get label of a pose.
int ITc_mediavision_mv_inference_pose_get_label_p(void)
{
	START_TEST_INFERENCE;
	int nRet = -1;
	char pszImageFileName[PATHLEN];

	nRet = SetPoseLandmarkDetectionEngineConfig(gEngineConfigHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "SetPoseLandmarkDetectionEngineConfig", MediaVisionGetError(nRet));

	nRet = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_configure", MediaVisionGetError(nRet));

	nRet = mv_inference_prepare(gInferenceHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_prepare", MediaVisionGetError(nRet));

	snprintf(pszImageFileName, PATHLEN, "%s/images/%s", gInferenceExampleDir, "poseLandmark.jpg");
	nRet = LoadImageToMediaSOurce(pszImageFileName, gSourceHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "LoadImageToMediaSOurce", MediaVisionGetError(nRet));

	g_CallBackHit = false;

	nRet = mv_inference_pose_landmark_detect(gSourceHandle, gInferenceHandle, NULL, GetPoseCB, NULL);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_pose_landmark_detect", MediaVisionGetError(nRet));
	PRINT_RESULT(true, g_CallBackHit, "mv_inference_pose_landmark_detect", MediaVisionGetError(nRet));
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE,  g_nRetVal, "mv_inference_pose_landmark_detect", MediaVisionGetError(nRet));
	if(g_nNumberOfPoses <= 0)
	{
		FPRINTF("[Line : %d][%s] Invalid value of  g_nNumberOfPoses, g_nNumberOfPoses = %d \\n", __LINE__, API_NAMESPACE, g_nNumberOfPoses);
		return 1;
	}
	if(g_nLabel > 0)
	{
		FPRINTF("[Line : %d][%s] Invalid value of  g_nLabel, g_nLabel = %d \\n", __LINE__, API_NAMESPACE, g_nLabel);
		return 1;
	}

	return 0;
}

/**
 * @testcase 				ITc_mediavision_mv_pose_create_destroy_p
 * @author					SRID(priya.kohli)
 * @reviewer				SRID(shobhit.v)
 * @type					auto
 * @since_tizen 			6.0
 * @description				Creates and destroys pose handle.
 * @scenario				Creates pose handle.
 *							Destroys pose handle and releases all its resources.
 * @apicovered				mv_pose_create, mv_pose_destroy
 * @passcase				If mv_pose_create, mv_pose_destroy and Precondition API's returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To create and destroy pose handle.
int ITc_mediavision_mv_pose_create_destroy_p(void)
{
	START_TEST_INFERENCE;
	int nRet = -1;
	mv_pose_h hPoseHandle = NULL;

	nRet = mv_pose_create(&hPoseHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_pose_create", MediaVisionGetError(nRet));

	nRet = mv_pose_destroy(hPoseHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_pose_destroy", MediaVisionGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mediavision_mv_pose_set_from_file_p
 * @author					SRID(priya.kohli)
 * @reviewer				SRID(shobhit.v)
 * @type					auto
 * @since_tizen 			6.0
 * @description				Sets a motion capture file and its pose mapping file to the pose.
 * @scenario				This function is used to set a motion capture file and
 *							its pose mapping file
 * @apicovered				mv_pose_set_from_file
 * @passcase				If mv_pose_set_from_file and Precondition API's returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To set a motion capture file and its pose mapping file to the pose.
int ITc_mediavision_mv_pose_set_from_file_p(void)
{
	START_TEST_INFERENCE;
	int nRet = -1;
	mv_pose_h hPoseHandle = NULL;

	nRet = mv_pose_create(&hPoseHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_pose_create", MediaVisionGetError(nRet));

	char pszPoseMocapFilename[PATHLEN];
	char pszPoseMocapMappingFilename[PATHLEN];
	snprintf(pszPoseMocapFilename, PATHLEN, "%s/models/%s", gInferenceExampleDir, "pld_mocap.bvh");
	snprintf(pszPoseMocapMappingFilename, PATHLEN, "%s/models/%s", gInferenceExampleDir, "pld_mocap_mapping.txt");

	nRet = mv_pose_set_from_file(hPoseHandle, pszPoseMocapFilename, pszPoseMocapMappingFilename);
	PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_pose_set_from_file", MediaVisionGetError(nRet), mv_pose_destroy(hPoseHandle));

	nRet = mv_pose_destroy(hPoseHandle);
	PRINT_RESULT_NORETURN(MEDIA_VISION_ERROR_NONE, nRet, "mv_pose_destroy", MediaVisionGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_mediavision_mv_pose_compare_p
 * @author					SRID(priya.kohli)
 * @reviewer				SRID(shobhit.v)
 * @type					auto
 * @since_tizen 			6.0
 * @description				Compares an action pose with the pose which is set by mv_pose_set_from_file().
 * @scenario				This function is used to compare action pose with the pose
 *							which is set by mv_pose_set_from_file().
 *							Parts to be compared can be selected by #mv_inference_human_body_part_e.
 *							Their similarity will be given by the score between 0 ~ 1.
 * @apicovered				mv_pose_compare
 * @passcase				If mv_pose_compare and Precondition API's returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To compare an action pose with the pose which is set by mv_pose_set_from_file().
int ITc_mediavision_mv_pose_compare_p(void)
{
	START_TEST_INFERENCE;
	int nRet = -1;
	 g_nRetVal = -1;
	g_bResultNumber = -1;
	char pszImageFileName[PATHLEN];

	nRet = SetPoseLandmarkDetectionEngineConfig(gEngineConfigHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "SetPoseLandmarkDetectionEngineConfig", MediaVisionGetError(nRet));

	nRet = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_configure", MediaVisionGetError(nRet));

	nRet = mv_inference_prepare(gInferenceHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_prepare", MediaVisionGetError(nRet));

	snprintf(pszImageFileName, PATHLEN, "%s/images/%s", gInferenceExampleDir, "poseLandmark.jpg");
	nRet = LoadImageToMediaSOurce(pszImageFileName, gSourceHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "LoadImageToMediaSOurce", MediaVisionGetError(nRet));

	mv_pose_h hPoseHandle = NULL;
	nRet = mv_pose_create(&hPoseHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_pose_create", MediaVisionGetError(nRet));

	char pszPoseMocapFilename[PATHLEN];
	char pszPoseMocapMappingFilename[PATHLEN];
	snprintf(pszPoseMocapFilename, PATHLEN, "%s/models/%s", gInferenceExampleDir, "pld_mocap.bvh");
	snprintf(pszPoseMocapMappingFilename, PATHLEN, "%s/models/%s", gInferenceExampleDir, "pld_mocap_mapping.txt");

	nRet = mv_pose_set_from_file(hPoseHandle, pszPoseMocapFilename, pszPoseMocapMappingFilename);
	PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_pose_set_from_file", MediaVisionGetError(nRet), mv_pose_destroy(hPoseHandle));

	g_CallBackHit = false;
	nRet = mv_inference_pose_landmark_detect(gSourceHandle, gInferenceHandle, NULL, PoseCompareCB, hPoseHandle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_inference_pose_landmark_detect", MediaVisionGetError(nRet));
	PRINT_RESULT(true, g_CallBackHit, "mv_inference_pose_landmark_detect", MediaVisionGetError(nRet));
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE,  g_nRetVal, "mv_pose_compare", MediaVisionGetError(nRet));
	assert_gt(g_PoseCompareScore, 0.5);
	
	if(g_PoseCompareScore <= 0.5)
	{
		FPRINTF("[Line : %d][%s] Invalid value of  g_PoseCompareScore, g_PoseCompareScore = %f \\n", __LINE__, API_NAMESPACE, g_PoseCompareScore);
		return 1;
	}

	nRet = mv_pose_destroy(hPoseHandle);
	PRINT_RESULT_NORETURN(MEDIA_VISION_ERROR_NONE, nRet, "mv_pose_destroy", MediaVisionGetError(nRet));

	return 0;
}
