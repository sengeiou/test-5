/**
 * Copyright (c) 2019 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "assert.h"
#include <mv_inference.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <image_util.h>
#include <system_info.h>
#include <storage.h>
#include "tct_common.h"

#define FILE_PATH_SIZE 1024
#define API_NAMESPACE "[MediaVision]"

static bool isVisionSupported = false;
static int gStartupError;

static mv_inference_h gInferenceHandle = NULL;
static mv_engine_config_h gEngineConfigHandle = NULL;
static mv_source_h gSourceHandle = NULL;
const char *gInferenceExampleDir = NULL;
static mv_point_s** gPldResultLandmarks = NULL;
static float** gPldResultScore = NULL;
static mv_pose_h gPoseHandle = NULL;

static bool gIsForeachSupportedCallBackInvoked = false;
static bool gIsImageClassifyCallBackInvoked = false;
static bool gIsObjectDetectCallBackInvoked = false;
static bool gIsFaceDetectCallBackInvoked = false;
static bool gIsFacialLandmarkDetectCallBackInvoked = false;
static bool gIsPoseLandmarkDetectCallBackInvoked = false;
static bool gIsGetPoseLandmark = false;

static int gPldResultErr;
static int gPldResultNumberOfPoses;
static int gPldResultNumberOfLandmarks;
static int gPldResultLabel;
static float gPoseCompareScore;

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

static int set_image_classification_engine_config(mv_engine_config_h engineCfg)
{
    int ret = MEDIA_VISION_ERROR_NONE;

    char modelFilename[1024];
    char modelMetaFilename[1024];
    char labelFilename[1024];
    char *inputNodeName = "input_2";
    char *outputNodeName[1] = {"dense_3/Softmax"};
    snprintf(modelFilename, 1024, "%s/models/%s", gInferenceExampleDir, IC_MODEL_FILENAME);
    snprintf(modelMetaFilename, 1024, "%s/models/%s", gInferenceExampleDir, IC_MODEL_META_FILENAME);
    snprintf(labelFilename, 1024, "%s/models/%s", gInferenceExampleDir, IC_LABEL_FILENAME);

    ret = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_WEIGHT_FILE_PATH,
                        modelFilename);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_META_FILE_PATH,
                        modelMetaFilename);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_DATA_TYPE,
                        MV_INFERENCE_DATA_FLOAT32);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_USER_FILE_PATH,
                        labelFilename);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_double_attribute(engineCfg,
                        MV_INFERENCE_MODEL_MEAN_VALUE,
                        127.0);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_double_attribute(engineCfg,
                        MV_INFERENCE_MODEL_STD_VALUE,
                        127.0);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_double_attribute(engineCfg,
                        MV_INFERENCE_CONFIDENCE_THRESHOLD,
                        0.5);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_BACKEND_TYPE,
                        MV_INFERENCE_BACKEND_TFLITE);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_TARGET_DEVICE_TYPE,
                        MV_INFERENCE_TARGET_DEVICE_CPU);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_TENSOR_WIDTH,
                        224);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_TENSOR_HEIGHT,
                        224);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_TENSOR_CHANNELS,
                        3);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_INPUT_NODE_NAME,
                        inputNodeName);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_array_string_attribute(engineCfg,
                        MV_INFERENCE_OUTPUT_NODE_NAMES,
                        outputNodeName,
                        1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    return ret;
}

static int set_object_detection_engine_config(mv_engine_config_h engineCfg)
{
    int ret = MEDIA_VISION_ERROR_NONE;

    char modelFilename[1024];
    char modelMetaFilename[1024];
    char labelFilename[1024];
    char *inputNodeName = "normalized_input_image_tensor";
    char *outputNodeName[4] = {"TFLite_Detection_PostProcess",
                            "TFLite_Detection_PostProcess:1",
                            "TFLite_Detection_PostProcess:2",
                            "TFLite_Detection_PostProcess:3"};

    snprintf(modelFilename, 1024, "%s/models/%s", gInferenceExampleDir, OD_MODEL_FILENAME);
    snprintf(modelMetaFilename, 1024, "%s/models/%s", gInferenceExampleDir, OD_MODEL_META_FILENAME);
    snprintf(labelFilename, 1024, "%s/models/%s", gInferenceExampleDir, OD_LABEL_FILENAME);

    ret = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_WEIGHT_FILE_PATH,
                        modelFilename);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_META_FILE_PATH,
                        modelMetaFilename);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_DATA_TYPE,
                        MV_INFERENCE_DATA_FLOAT32);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_USER_FILE_PATH,
                        labelFilename);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_double_attribute(engineCfg,
                        MV_INFERENCE_MODEL_MEAN_VALUE,
                        127.5);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_double_attribute(engineCfg,
                        MV_INFERENCE_MODEL_STD_VALUE,
                        127.5);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_double_attribute(engineCfg,
                        MV_INFERENCE_CONFIDENCE_THRESHOLD,
                        0.3);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_BACKEND_TYPE,
                        MV_INFERENCE_BACKEND_TFLITE);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_TARGET_DEVICE_TYPE,
                        MV_INFERENCE_TARGET_DEVICE_CPU);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_TENSOR_WIDTH,
                        300);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_TENSOR_HEIGHT,
                        300);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_TENSOR_CHANNELS,
                        3);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_INPUT_NODE_NAME,
                        inputNodeName);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_array_string_attribute(engineCfg,
                        MV_INFERENCE_OUTPUT_NODE_NAMES,
                        outputNodeName,
                        4);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    return ret;
}

static int set_face_detection_engine_config(mv_engine_config_h engineCfg)
{
    int ret = MEDIA_VISION_ERROR_NONE;

    char modelFilename[1024];
    char modelMetaFilename[1024];
    char *inputNodeName = "normalized_input_image_tensor";
    char *outputNodeName[4] = {"TFLite_Detection_PostProcess",
                                "TFLite_Detection_PostProcess:1",
                                "TFLite_Detection_PostProcess:2",
                                "TFLite_Detection_PostProcess:3"};
    snprintf(modelFilename, 1024, "%s/models/%s", gInferenceExampleDir, FD_MODEL_FILENAME);
    snprintf(modelMetaFilename, 1024, "%s/models/%s", gInferenceExampleDir, FD_MODEL_META_FILENAME);

    ret = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_WEIGHT_FILE_PATH,
                        modelFilename);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_META_FILE_PATH,
                        modelMetaFilename);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_DATA_TYPE,
                        MV_INFERENCE_DATA_FLOAT32);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_double_attribute(engineCfg,
                        MV_INFERENCE_MODEL_MEAN_VALUE,
                        127.5);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_double_attribute(engineCfg,
                        MV_INFERENCE_MODEL_STD_VALUE,
                        127.5);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_double_attribute(engineCfg,
                        MV_INFERENCE_CONFIDENCE_THRESHOLD,
                        0.3);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_BACKEND_TYPE,
                        MV_INFERENCE_BACKEND_TFLITE);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_TARGET_DEVICE_TYPE,
                        MV_INFERENCE_TARGET_DEVICE_CPU);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_TENSOR_WIDTH,
                        300);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_TENSOR_HEIGHT,
                        300);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_TENSOR_CHANNELS,
                        3);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_INPUT_NODE_NAME,
                        inputNodeName);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_array_string_attribute(engineCfg,
                        MV_INFERENCE_OUTPUT_NODE_NAMES,
                        outputNodeName,
                        4);
    return ret;
}

static int set_facial_landmark_detection_engine_config(mv_engine_config_h engineCfg)
{
    int ret = MEDIA_VISION_ERROR_NONE;

    char modelFilename[1024];
    char modelMetaFilename[1024];
    char *inputNodeName = "Placeholder";
    char *outputNodeName[1] = {"fanet8ss_inference/fully_connected_1/Sigmoid"};
    snprintf(modelFilename, 1024, "%s/models/%s", gInferenceExampleDir, FLD_MODEL_FILENAME);
    snprintf(modelMetaFilename, 1024, "%s/models/%s", gInferenceExampleDir, FLD_MODEL_META_FILENAME);

    ret = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_WEIGHT_FILE_PATH,
                        modelFilename);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_META_FILE_PATH,
                        modelMetaFilename);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_DATA_TYPE,
                        MV_INFERENCE_DATA_FLOAT32);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_double_attribute(engineCfg,
                        MV_INFERENCE_MODEL_MEAN_VALUE,
                        0.0);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_double_attribute(engineCfg,
                        MV_INFERENCE_MODEL_STD_VALUE,
                        1.0);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_BACKEND_TYPE,
                        MV_INFERENCE_BACKEND_TFLITE);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_TARGET_DEVICE_TYPE,
                        MV_INFERENCE_TARGET_DEVICE_CPU);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_TENSOR_WIDTH,
                        128);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_TENSOR_HEIGHT,
                        128);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_TENSOR_CHANNELS,
                        3);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_INPUT_NODE_NAME,
                        inputNodeName);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_array_string_attribute(engineCfg,
                        MV_INFERENCE_OUTPUT_NODE_NAMES,
                        outputNodeName,
                        1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    return ret;
}

static int set_pose_landmark_detection_engine_config(mv_engine_config_h engineCfg)
{
    int ret = MEDIA_VISION_ERROR_NONE;

    char modelFilename[FILE_PATH_SIZE];
    char modelMetaFilename[FILE_PATH_SIZE];
    char poseMappingFilename[FILE_PATH_SIZE];
    char *inputNodeName = "image";
    char *outputNodeName[1] = { "Convolutional_Pose_Machine/stage_5_out" };
    snprintf(modelFilename, FILE_PATH_SIZE, "%s/models/%s",
                            gInferenceExampleDir, PLD_MODEL_FILENAME);
    snprintf(modelMetaFilename, FILE_PATH_SIZE, "%s/models/%s",
                            gInferenceExampleDir, PLD_MODEL_META_FILENAME);
    snprintf(poseMappingFilename, FILE_PATH_SIZE, "%s/models/%s",
                            gInferenceExampleDir, PLD_POSE_MAPPING_FILENAME);

    ret = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_WEIGHT_FILE_PATH,
                        modelFilename);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_META_FILE_PATH,
                        modelMetaFilename);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);


    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_DATA_TYPE,
                        MV_INFERENCE_DATA_FLOAT32);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_MODEL_USER_FILE_PATH,
                        poseMappingFilename);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_double_attribute(engineCfg,
                        MV_INFERENCE_MODEL_MEAN_VALUE,
                        0.0);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_double_attribute(engineCfg,
                        MV_INFERENCE_MODEL_STD_VALUE,
                        1.0);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_BACKEND_TYPE,
                        MV_INFERENCE_BACKEND_TFLITE);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_TARGET_DEVICE_TYPE,
                        MV_INFERENCE_TARGET_DEVICE_CPU);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_TENSOR_WIDTH,
                        192);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_TENSOR_HEIGHT,
                        192);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_int_attribute(engineCfg,
                        MV_INFERENCE_INPUT_TENSOR_CHANNELS,
                        3);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_string_attribute(engineCfg,
                        MV_INFERENCE_INPUT_NODE_NAME,
                        inputNodeName);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_engine_config_set_array_string_attribute(engineCfg,
                        MV_INFERENCE_OUTPUT_NODE_NAMES,
                        outputNodeName,
                        1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    return ret;
}

static int load_image_to_media_source(
        const char *file_path,
        mv_source_h source)
{
    if (NULL == file_path || NULL == source)
    {
        printf("File path or source is NULL\n");
        return MEDIA_VISION_ERROR_INVALID_PARAMETER;
    }

    unsigned long width = 0;
    unsigned long height = 0;
    unsigned long long buffer_size = 0;
    unsigned char *data_buffer = NULL;
    int ret1 = IMAGE_UTIL_ERROR_NONE;
    int ret2 = MEDIA_VISION_ERROR_NONE;
    image_util_decode_h _decoder = NULL;

    ret1 = image_util_decode_create(&_decoder);
    if (ret1 != IMAGE_UTIL_ERROR_NONE) goto _LOAD_IMAGE_FAIL;
    ret1 = image_util_decode_set_input_path(_decoder, file_path);
    if (ret1 != IMAGE_UTIL_ERROR_NONE) goto _LOAD_IMAGE_FAIL;
    ret1 = image_util_decode_set_colorspace(_decoder, IMAGE_UTIL_COLORSPACE_RGB888);
    if (ret1 != IMAGE_UTIL_ERROR_NONE) goto _LOAD_IMAGE_FAIL;
    ret1 = image_util_decode_set_output_buffer(_decoder, &data_buffer);
    if (ret1 != IMAGE_UTIL_ERROR_NONE) goto _LOAD_IMAGE_FAIL;
    ret1 = image_util_decode_run(_decoder, &width, &height, &buffer_size);
    if (ret1 != IMAGE_UTIL_ERROR_NONE) goto _LOAD_IMAGE_FAIL;

    // Only grayscale and RGB jpegs in test set:
    mv_colorspace_e source_colorspace = MEDIA_VISION_COLORSPACE_RGB888;

    ret2 = mv_source_clear(source);
    if (ret2 != MEDIA_VISION_ERROR_NONE) goto _LOAD_IMAGE_FAIL;

    ret2 = mv_source_fill_by_buffer(
                    source, data_buffer, (unsigned int)buffer_size,
                    (unsigned int)width, (unsigned int)height,
                    source_colorspace);

_LOAD_IMAGE_FAIL:
    image_util_decode_destroy(_decoder);
    if(data_buffer)
        free(data_buffer);

    assert_eq(IMAGE_UTIL_ERROR_NONE, ret1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret2);

    return MEDIA_VISION_ERROR_NONE;
}

/**
 * @function	utc_capi_media_vision_inference_startup
 * @description	Inference module UTC startup code
 * @parameter	NA
 * @return		NA
 */
void utc_capi_media_vision_inference_startup1(void)
{
    printf("capi-media-vision mv_inference tests STARTUP is launched\n");

    bool isInferenceSupported = true;
    system_info_get_platform_bool("http://tizen.org/feature/vision.inference", &isInferenceSupported);

    if (isInferenceSupported)
        isVisionSupported = true;
    else
        isVisionSupported = false;

    printf("capi-media-vision mv_inference tests STARTUP is completed\n");
}

/**
 * @function	utc_capi_media_vision_inference_cleanup
 * @description	Inference module UTC cleanup code
 * @parameter	NA
 * @return		NA
 */
void utc_capi_media_vision_inference_cleanup1(void)
{
    printf("capi-media-vision mv_image tests CLEANUP is launched\n");
    printf("capi-media-vision mv_image tests CLEANUP is completed\n");
}


/**
 * @function	utc_capi_media_vision_inference_startup
 * @description	Inference module UTC startup code
 * @parameter	NA
 * @return		NA
 */
void utc_capi_media_vision_inference_startup2(void)
{
    printf("capi-media-vision mv_inference tests STARTUP is launched\n");

    bool isInferenceSupported = true;
    system_info_get_platform_bool("http://tizen.org/feature/vision.inference", &isInferenceSupported);

    if (isInferenceSupported)
        isVisionSupported = true;
    else
        isVisionSupported = false;


    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    if (true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE)) {
        PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received %s\\n", __LINE__, API_NAMESPACE, pszValue);

        gInferenceExampleDir=(char*)calloc(strlen(pszValue)+strlen("/res/res/inference")+1, sizeof(char));
        snprintf(gInferenceExampleDir, strlen(pszValue)+strlen("/res/res/inference")+1, "%s/res/res/inference", pszValue);

    } else {
        PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
    }

    gStartupError = mv_inference_create(&gInferenceHandle);
    if (MEDIA_VISION_ERROR_NONE != gStartupError) {
        gInferenceHandle = NULL;
        printf("mv_inference_h create is failed\n");
        return;
    }

    gStartupError = mv_create_engine_config(&gEngineConfigHandle);
    if (MEDIA_VISION_ERROR_NONE != gStartupError) {
        gEngineConfigHandle = NULL;
        printf("mv_engine_config_h create is failed\n");
        return;
    }

    gStartupError = mv_create_source(&gSourceHandle);
    if (MEDIA_VISION_ERROR_NONE != gStartupError) {
        gSourceHandle = NULL;
        printf("mv_source_h create is failed\n");
        return;
    }

    printf("capi-media-vision mv_inference tests STARTUP is completed\n");
}

/**
 * @function	utc_capi_media_vision_inference_cleanup
 * @description	Inference module UTC cleanup code
 * @parameter	NA
 * @return		NA
 */
void utc_capi_media_vision_inference_cleanup2(void)
{
    printf("capi-media-vision mv_image tests CLEANUP is launched\n");

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

    if (gPldResultLandmarks){
        for (int pose = 0; pose < gPldResultNumberOfPoses; ++pose)
            free(gPldResultLandmarks[pose]);
        free(gPldResultLandmarks);
        gPldResultLandmarks = NULL;
    }

    if (gPldResultScore){
        for (int pose = 0; pose < gPldResultNumberOfPoses; ++pose)
            free(gPldResultScore[pose]);
        free(gPldResultScore);
        gPldResultScore = NULL;
    }

    if (gPoseHandle) {
        mv_pose_destroy(gPoseHandle);
        gPoseHandle = NULL;
    }

    printf("capi-media-vision mv_image tests CLEANUP is completed\n");
}

/**
 * @brief Positive test case of mv_inference_create_p()
 * @testcase        utc_mediavision_mv_inference_create_p
 * @since_tizen     5.5
 * @description     Create inference handle
 */
int utc_mediavision_mv_inference_create_p(void)
{
    printf("Inside mv_inference_create_p\n");

    mv_inference_h inferenceHandle = NULL;
    int ret = mv_inference_create(&inferenceHandle);
    if (!isVisionSupported) {
        assert_eq(ret, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_destroy(inferenceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_inference_create_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_inference_create()
 * @testcase        utc_mediavision_mv_inference_create_n
 * @since_tizen     5.5
 * @description     Create inference handle,
 *                  but fail because input parameter is NULL
 */
int utc_mediavision_mv_inference_create_n(void)
{
    printf("Inside mv_inference_create_n\n");

    int ret = mv_inference_create(NULL);
    if (!isVisionSupported) {
        assert_eq(ret, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_inference_create_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_inference_destroy_p()
 * @testcase        utc_mediavision_mv_inference_destroy_p
 * @since_tizen     5.5
 * @description     Destroy inference handle
 */
int utc_mediavision_mv_inference_destroy_p(void)
{
    printf("Inside mv_inference_destroy_p\n");

    mv_inference_h inferenceHandle = NULL;
    int ret = mv_inference_create(&inferenceHandle);
    if (!isVisionSupported) {
        assert_eq(ret, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_destroy(inferenceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_inference_destroy_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_inference_destroy_n()
 * @testcase        utc_mediavision_mv_inference_destroy_n
 * @since_tizen     5.5
 * @description     Destroy inference handle,
 *                  but fail because input parameter is NULL
 */
int utc_mediavision_mv_inference_destroy_n(void)
{
    printf("Inside mv_inference_destroy_n\n");

    int ret = mv_inference_destroy(NULL);
    if (!isVisionSupported) {
        assert_eq(ret, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_inference_destroy_n\n");

    return 0;
}

static bool _supported_inference_engine_cb(
                        const char *engine,
                        bool supported,
                        void *user_data)
{
    gIsForeachSupportedCallBackInvoked = true;
    return true;
}
/**
 * @brief Positive test case of mv_inference_foreach_supported_engine_p()
 * @testcase        utc_mediavision_mv_inference_foreach_supported_engine_p
 * @since_tizen     5.5
 * @description     Check supported engine
 */
int utc_mediavision_mv_inference_foreach_supported_engine()
{
    printf("Inside mv_inference_foreach_supported_engine_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    int ret = mv_inference_foreach_supported_engine(gInferenceHandle,
                        _supported_inference_engine_cb,
                        NULL);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(true, gIsForeachSupportedCallBackInvoked);

    printf("Before return mv_inference_foreach_supported_engine_p\n");

    return 0;
}

/**
 * @brief Positive test case of mv_inference_configure_p()
 * @testcase        utc_mediavision_mv_inference_configure_p
 * @since_tizen     5.5
 * @description     Configure inference handle
 */
int utc_mediavision_mv_inference_configure_p(void)
{
    printf("Inside mv_inference_configure_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    int ret = MEDIA_VISION_ERROR_NONE;

    // create handle
    assert_eq(set_image_classification_engine_config(gEngineConfigHandle), MEDIA_VISION_ERROR_NONE);

    ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_inference_configure_p\n");
    return 0;
}


/**
 * @brief Negative test case of mv_inference_configure_n1()
 * @testcase        utc_mediavision_mv_inference_configure_n
 * @since_tizen     5.5
 * @description     Configure inference handle,
 *                  but fail because input parameters are invalid
 */
int utc_mediavision_mv_inference_configure_n1(void)
{
    printf("Inside mv_inference_configure_n1\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    int ret = mv_inference_configure(gInferenceHandle, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_inference_configure(NULL, gEngineConfigHandle);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_inference_configure(NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_inference_configure_n1\n");
    return 0;
}

/**
 * @brief Negative test case of mv_inference_configure_n2()
 * @testcase        utc_mediavision_mv_inference_configure_n
 * @since_tizen     5.5
 * @description     Configure inference handle,
 *                  but fail because the invalid value is set
 */
int utc_mediavision_mv_inference_configure_n2(void)
{
    printf("Inside mv_inference_configure_n2\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    int ret = mv_engine_config_set_int_attribute(gEngineConfigHandle,
                        MV_INFERENCE_BACKEND_TYPE,
                        MV_INFERENCE_BACKEND_MAX);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_inference_configure_n2\n");
    return 0;
}


/**
 * @brief Positive test case of mv_inference_prepare_p()
 * @testcase        utc_mediavision_mv_inference_prepare_p
 * @since_tizen     5.5
 * @description     Prepare inference handle
 */
int utc_mediavision_mv_inference_prepare_p(void)
{
    printf("Inside mv_inference_prepare_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(set_image_classification_engine_config(gEngineConfigHandle), MEDIA_VISION_ERROR_NONE);

    int ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_prepare(gInferenceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_inference_configure_p\n");
    return 0;
}

/**
 * @brief Negative test case of mv_inference_prepare_n1()
 * @testcase        utc_mediavision_mv_inference_prepare_n
 * @since_tizen     5.5
 * @description     Prepare inference handle,
 *                  but fail because input handle is NULL
 */
int utc_mediavision_mv_inference_prepare_n1(void)
{
    printf("Inside mv_inference_prepare_n1\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    int ret = mv_inference_prepare(NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_inference_prepare_n1\n");
    return 0;
}

static void _classified_cb (mv_source_h source,
                        int number_of_classes,
                        const int *indices,
                        const char **names,
                        const float *confidences,
                        void *user_data)
{
    gIsImageClassifyCallBackInvoked = true;
}
/**
 * @brief Positive test case of mv_inference_image_classify()
 * @testcase        utc_mediavision_mv_inference_image_classify_p
 * @since_tizen     5.5
 * @description     Classify an image
 */
int utc_mediavision_mv_inference_image_classify_p(void)
{
    printf("Inside mv_inference_image_classify_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    char imageFilename[1024];

    assert_eq(set_image_classification_engine_config(gEngineConfigHandle), MEDIA_VISION_ERROR_NONE);

    int ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_prepare(gInferenceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    snprintf(imageFilename, 1024, "%s/images/%s", gInferenceExampleDir, "banana.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_image_classify(gSourceHandle,
                                    gInferenceHandle,
                                    NULL,
                                    _classified_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(true, gIsImageClassifyCallBackInvoked);

    printf("Before return mv_inference_image_classify_p\n");
    return 0;
}

/**
 * @brief Negative test case of mv_inference_image_classify()
 * @testcase        utc_mediavision_mv_inference_image_classify_n1
 * @since_tizen     5.5
 * @description     Classify an image,
 *                  but fail because input parameter is NULL
 */
int utc_mediavision_mv_inference_image_classify_n1(void)
{
    printf("Inside mv_inference_image_classify_n1\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    char imageFilename[1024];

    assert_eq(set_image_classification_engine_config(gEngineConfigHandle), MEDIA_VISION_ERROR_NONE);

    int ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_prepare(gInferenceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    snprintf(imageFilename, 1024, "%s/images/%s", gInferenceExampleDir, "banana.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    // source is NULL
    ret = mv_inference_image_classify(NULL,
                                    gInferenceHandle,
                                    NULL,
                                    _classified_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    // inference handle is NULL
    ret = mv_inference_image_classify(gSourceHandle,
                                    NULL,
                                    NULL,
                                    _classified_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    // callback is NULL
    ret = mv_inference_image_classify(gSourceHandle,
                                    gInferenceHandle,
                                    NULL,
                                    NULL,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_inference_image_classify_n1\n");
    return 0;
}

/**
 * @brief Negative test case of mv_inference_image_classify()
 * @testcase        utc_mediavision_mv_inference_image_classify_n2
 * @since_tizen     5.5
 * @description     Classify an image,
 *                  but fail because mv_inference_prepare() isn't called before
 */
int utc_mediavision_mv_inference_image_classify_n2(void)
{
    printf("Inside mv_inference_image_classify_n2\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    char imageFilename[1024];

    assert_eq(set_image_classification_engine_config(gEngineConfigHandle), MEDIA_VISION_ERROR_NONE);

    int ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    snprintf(imageFilename, 1024, "%s/images/%s", gInferenceExampleDir, "banana.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    // skip the mv_inference_prepare()
    ret = mv_inference_image_classify(gSourceHandle,
                                    gInferenceHandle,
                                    NULL,
                                    _classified_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_OPERATION, ret);

    printf("Before return mv_inference_image_classify_n2\n");
    return 0;
}

static void _od_detected_cb (mv_source_h source,
                        int number_of_object,
                        const int *indices,
                        const char **names,
                        const float *confidences,
                        const mv_rectangle_s *locations,
                        void *user_data)
{
    gIsObjectDetectCallBackInvoked = true;
}
/**
 * @brief Positive test case of mv_inference_object_detect()
 * @testcase        utc_mediavision_mv_inference_object_detect_p
 * @since_tizen     5.5
 * @description     Detect objects in an image
 */
int utc_mediavision_mv_inference_object_detect_p(void)
{
    printf("Inside mv_inference_object_detect_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    char imageFilename[1024];

    assert_eq(set_object_detection_engine_config(gEngineConfigHandle), MEDIA_VISION_ERROR_NONE);

    int ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_prepare(gInferenceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    snprintf(imageFilename, 1024, "%s/images/%s", gInferenceExampleDir, "dog2.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_object_detect(gSourceHandle,
                                    gInferenceHandle,
                                    _od_detected_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(true, gIsObjectDetectCallBackInvoked);

    printf("Before return mv_inference_object_detect_p\n");
    return 0;
}

/**
 * @brief Negative test case of mv_inference_object_detect()
 * @testcase        utc_mediavision_mv_inference_object_detect_n1
 * @since_tizen     5.5
 * @description     Detect objects in an image,
 *                  but fail because input parameter is NULL
 */
int utc_mediavision_mv_inference_object_detect_n1(void)
{
    printf("Inside mv_inference_object_detect_n1\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    char imageFilename[1024];

    assert_eq(set_object_detection_engine_config(gEngineConfigHandle), MEDIA_VISION_ERROR_NONE);

    int ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_prepare(gInferenceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    snprintf(imageFilename, 1024, "%s/images/%s", gInferenceExampleDir, "dog2.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    // source is NULL
    ret = mv_inference_object_detect(NULL,
                                    gInferenceHandle,
                                    _od_detected_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    // inference handle is NULL
    ret = mv_inference_object_detect(gSourceHandle,
                                    NULL,
                                    _od_detected_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    // callback is NULL
    ret = mv_inference_object_detect(gSourceHandle,
                                    gInferenceHandle,
                                    NULL,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_inference_image_classify_n1\n");
    return 0;
}

/**
 * @brief Positive test case of mv_inference_object_detect()
 * @testcase        utc_mediavision_mv_inference_object_detect_n2
 * @since_tizen     5.5
 * @description     Detect objects in an image,
 *                  but fail because mv_inference_prepare() isn't called before
 */
int utc_mediavision_mv_inference_object_detect_n2(void)
{
    printf("Inside mv_inference_object_detect_n2\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    char imageFilename[1024];

    assert_eq(set_object_detection_engine_config(gEngineConfigHandle), MEDIA_VISION_ERROR_NONE);

    int ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    snprintf(imageFilename, 1024, "%s/images/%s", gInferenceExampleDir, "dog2.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_object_detect(gSourceHandle,
                                    gInferenceHandle,
                                    _od_detected_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_OPERATION, ret);

    printf("Before return mv_inference_object_detect_n2\n");
    return 0;
}

static void _fd_detected_cb (mv_source_h source,
                        int number_of_faces,
                        const float *confidences,
                        const mv_rectangle_s *locations,
                        void *user_data)
{
    gIsFaceDetectCallBackInvoked = true;
}
/**
 * @brief Positive test case of mv_inference_face_detect()
 * @testcase        utc_mediavision_mv_inference_face_detect_p
 * @since_tizen     5.5
 * @description     Detect faces in an image
 */
int utc_mediavision_mv_inference_face_detect_p(void)
{
    printf("Inside mv_inference_face_detect_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    char imageFilename[1024];

    assert_eq(set_face_detection_engine_config(gEngineConfigHandle), MEDIA_VISION_ERROR_NONE);

    int ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_prepare(gInferenceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    snprintf(imageFilename, 1024, "%s/images/%s", gInferenceExampleDir, "faceDetection.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_face_detect(gSourceHandle,
                                    gInferenceHandle,
                                    _fd_detected_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(true, gIsFaceDetectCallBackInvoked);

    printf("Before return mv_inference_face_detect_p\n");
    return 0;
}

/**
 * @brief Negative test case of mv_inference_face_detect()
 * @testcase        utc_mediavision_mv_inference_face_detect_n1
 * @since_tizen     5.5
 * @description     Detect faces in an image,
 *                  but fail because input parameter is NULL
 */
int utc_mediavision_mv_inference_face_detect_n1(void)
{
    printf("Inside mv_inference_face_detect_n1\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    char imageFilename[1024];

    assert_eq(set_face_detection_engine_config(gEngineConfigHandle), MEDIA_VISION_ERROR_NONE);

    int ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_prepare(gInferenceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    snprintf(imageFilename, 1024, "%s/images/%s", gInferenceExampleDir, "faceDetection.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    // source is NULL
    ret = mv_inference_face_detect(NULL,
                                    gInferenceHandle,
                                    _fd_detected_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    // inference handle is NULL
    ret = mv_inference_face_detect(gSourceHandle,
                                    NULL,
                                    _fd_detected_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    // callback is NULL
    ret = mv_inference_face_detect(gSourceHandle,
                                    gInferenceHandle,
                                    NULL,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_inference_object_detect_n1\n");
    return 0;
}

/**
 * @brief Positive test case of mv_inference_face_detect()
 * @testcase        utc_mediavision_mv_inference_face_detect_n2
 * @since_tizen     5.5
 * @description     Detect objects in an image,
 *                  but fail because mv_inference_prepare() isn't called before
 */
int utc_mediavision_mv_inference_face_detect_n2(void)
{
    printf("Inside mv_inference_face_detect_n2\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    char imageFilename[1024];

    assert_eq(set_face_detection_engine_config(gEngineConfigHandle), MEDIA_VISION_ERROR_NONE);

    int ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    snprintf(imageFilename, 1024, "%s/images/%s", gInferenceExampleDir, "faceDetection.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_face_detect(gSourceHandle,
                                    gInferenceHandle,
                                    _fd_detected_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_OPERATION, ret);

    printf("Before return mv_inference_face_detect_n2\n");
    return 0;
}

static void _fld_detected_cb (mv_source_h source,
                        int number_of_landmark,
                        const mv_rectangle_s *locations,
                        void *user_data)
{
    gIsFacialLandmarkDetectCallBackInvoked = true;
}
/**
 * @brief Positive test case of mv_inference_facial_landmark_detect()
 * @testcase        utc_mediavision_mv_inference_facial_landmark_detect_p
 * @since_tizen     5.5
 * @description     Detect landmark on a face which is detected
 */
int utc_mediavision_mv_inference_facial_landmark_detect_p(void)
{
    printf("Inside mv_inference_facial_landmark_detect_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    char imageFilename[1024];

    assert_eq(set_facial_landmark_detection_engine_config(gEngineConfigHandle), MEDIA_VISION_ERROR_NONE);

    int ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_prepare(gInferenceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    snprintf(imageFilename, 1024, "%s/images/%s", gInferenceExampleDir, "faceLandmark.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_facial_landmark_detect(gSourceHandle,
                                    gInferenceHandle,
                                    NULL,
                                    _fld_detected_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(true, gIsFacialLandmarkDetectCallBackInvoked);

    printf("Before return mv_inference_facial_landmark_detect_p\n");
    return 0;
}

/**
 * @brief Negative test case of mv_inference_facial_landmark_detect()
 * @testcase        utc_mediavision_mv_inference_facial_landmark_detect_n1
 * @since_tizen     5.5
 * @description     Detect landmark on a face which is detected,
 *                  but fail because input parameter is NULL
 */
int utc_mediavision_mv_inference_facial_landmark_detect_n1(void)
{
    printf("Inside mv_inference_facial_landmark_detect_n1\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    char imageFilename[1024];

    assert_eq(set_facial_landmark_detection_engine_config(gEngineConfigHandle), MEDIA_VISION_ERROR_NONE);

    int ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_prepare(gInferenceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    snprintf(imageFilename, 1024, "%s/images/%s", gInferenceExampleDir, "faceLandmark.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    // source is NULL
    ret = mv_inference_facial_landmark_detect(NULL,
                                    gInferenceHandle,
                                    NULL,
                                    _fld_detected_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    // inference handle is NULL
    ret = mv_inference_facial_landmark_detect(gSourceHandle,
                                    NULL,
                                    NULL,
                                    _fld_detected_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    // callback is NULL
    ret = mv_inference_facial_landmark_detect(gSourceHandle,
                                    gInferenceHandle,
                                    NULL,
                                    NULL,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_inference_facial_landmark_detect_n1\n");
    return 0;
}

/**
 * @brief Positive test case of mv_inference_facial_landmark_detect()
 * @testcase        utc_mediavision_mv_inference_facial_landmark_detect_n2
 * @since_tizen     5.5
 * @description     Detect landmark on a face which is detected,
 *                  but fail because mv_inference_prepare() isn't called before
 */
int utc_mediavision_mv_inference_facial_landmark_detect_n2(void)
{
    printf("Inside mv_inference_facial_landmark_detect_n2\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    char imageFilename[1024];

    assert_eq(set_facial_landmark_detection_engine_config(gEngineConfigHandle), MEDIA_VISION_ERROR_NONE);

    int ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    snprintf(imageFilename, 1024, "%s/images/%s", gInferenceExampleDir, "faceLandmark.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_facial_landmark_detect(gSourceHandle,
                                    gInferenceHandle,
                                    NULL,
                                    _fld_detected_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_OPERATION, ret);

    printf("Before return mv_inference_facial_landmark_detect_n2\n");
    return 0;
}

static void _pld_detected_cb(mv_source_h source,
                        mv_inference_pose_result_h locations,
                        void *user_data)
{
    gIsPoseLandmarkDetectCallBackInvoked = true;
}

/**
 * @brief Positive test case of mv_inference_pose_landmark_detect()
 * @testcase        utc_mediavision_mv_inference_pose_landmark_detect_p
 * @since_tizen     6.0
 * @description     Detect pose landmark on a human body
 */
int utc_mediavision_mv_inference_pose_landmark_detect_p(void)
{
    printf("Inside mv_inference_pose_landmark_detect_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    char imageFilename[FILE_PATH_SIZE];
    assert_eq(set_pose_landmark_detection_engine_config(gEngineConfigHandle), MEDIA_VISION_ERROR_NONE);

    int ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_prepare(gInferenceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    snprintf(imageFilename, FILE_PATH_SIZE, "%s/images/%s", gInferenceExampleDir, "poseLandmark.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_pose_landmark_detect(gSourceHandle,
                                    gInferenceHandle,
                                    NULL,
                                    _pld_detected_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(true, gIsPoseLandmarkDetectCallBackInvoked);

    printf("Before return mv_inference_pose_landmark_detect_p\n");
    return 0;
}

/**
 * @brief Negative test case of mv_inference_pose_landmark_detect()
 * @testcase        utc_mediavision_mv_inference_pose_landmark_detect_n1
 * @since_tizen     6.0
 * @description     Detect pose landmark on a human body,
 *                  but fail because an input parameter is NULL
 */
int utc_mediavision_mv_inference_pose_landmark_detect_n1(void)
{
    printf("Inside mv_inference_pose_landmark_detect_n1\n");
    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    char imageFilename[FILE_PATH_SIZE];
    assert_eq(set_pose_landmark_detection_engine_config(gEngineConfigHandle), MEDIA_VISION_ERROR_NONE);

    int ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_prepare(gInferenceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    snprintf(imageFilename, FILE_PATH_SIZE, "%s/images/%s", gInferenceExampleDir, "poseLandmark.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    // source is NULL
    ret = mv_inference_pose_landmark_detect(NULL,
                                    gInferenceHandle,
                                    NULL,
                                    _pld_detected_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    // inference handle is NULL
    ret = mv_inference_pose_landmark_detect(gSourceHandle,
                                    NULL,
                                    NULL,
                                    _pld_detected_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    // callback is NULL
     ret = mv_inference_pose_landmark_detect(gSourceHandle,
                                    gInferenceHandle,
                                    NULL,
                                    NULL,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_inference_pose_landmark_detect_n1\n");
    return 0;
}

/**
 * @brief Negative test case of mv_inference_pose_landmark_detect()
 * @testcase        utc_mediavision_mv_inference_pose_landmark_detect_n2
 * @since_tizen     6.0
 * @description     Detect pose landmark on a human body,
 *                  but fail because mv_inference_prepare() isn't called
 */
int utc_mediavision_mv_inference_pose_landmark_detect_n2(void)
{
    printf("Inside mv_inference_pose_landmark_detect_n2\n");
    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    char imageFilename[FILE_PATH_SIZE];
    assert_eq(set_pose_landmark_detection_engine_config(gEngineConfigHandle), MEDIA_VISION_ERROR_NONE);

    int ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    snprintf(imageFilename, FILE_PATH_SIZE, "%s/images/%s", gInferenceExampleDir, "poseLandmark.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_inference_pose_landmark_detect(gSourceHandle,
                                    gInferenceHandle,
                                    NULL,
                                    _pld_detected_cb,
                                    NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_OPERATION, ret);

    printf("Before return mv_inference_pose_landmark_detect_n2\n");
    return 0;
}

static void get_pose_landmark_detection_result_cb1(mv_source_h source,
                                    mv_inference_pose_result_h result,
                                    void *user_data)
{
    printf("Inside get_pose_landmark_detection_result_cb1\n");
    gIsPoseLandmarkDetectCallBackInvoked = true;

    gPldResultErr = mv_inference_pose_get_number_of_poses(result, &gPldResultNumberOfPoses);
    printf("Before retrun get_pose_landmark_detection_result_cb1\n");
}

/**
 * @function	utc_mediavision_mv_inference_pose_landmark_detect_cb1_startup
 * @description	Inference module UTC startup code for mv_inference_pose_get_number_of_poses()
 * @parameter	NA
 * @return		NA
 */
void utc_capi_media_vision_inference_pose_landmark_detect_cb1_startup(void)
{
    printf("Inside utc_mediavision_mv_inference_pose_landmark_detect_cb1_startup\n");
    utc_capi_media_vision_inference_startup2();

    if (gStartupError != MEDIA_VISION_ERROR_NONE)
        return;

    char imageFilename[FILE_PATH_SIZE];
    int ret = set_pose_landmark_detection_engine_config(gEngineConfigHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("set_pose_landmark_detection_engine_config is failed\n");
        return;
    }

    ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("mv_inference_configure is failed\n");
        return;
    }

    ret = mv_inference_prepare(gInferenceHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("mv_inference_prepare is failed\n");
        return;
    }

    snprintf(imageFilename, FILE_PATH_SIZE, "%s/images/%s", gInferenceExampleDir, "poseLandmark.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("load_image_to_media_source is failed\n");
        return;
    }

    ret = mv_inference_pose_landmark_detect(gSourceHandle,
                                    gInferenceHandle,
                                    NULL,
                                    get_pose_landmark_detection_result_cb1,
                                    NULL);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("mv_inference_pose_landmark_detect is failed\n");
        return;
    }

    printf("Before return utc_mediavision_mv_inference_pose_landmark_detect_cb1_startup\n");
}

/**
 * @brief Positive test case of mv_inference_get_number_of_poses()
 * @testcase        utc_mediavision_mv_inference_get_number_of_poses_p
 * @since_tizen     6.0
 * @description     Get the number of poses from a detected result
 */
int utc_mediavision_mv_inference_get_number_of_poses_p(void)
{
    printf("Inside mv_inference_get_number_of_poses_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(true, gIsPoseLandmarkDetectCallBackInvoked);
    assert_eq(MEDIA_VISION_ERROR_NONE, gPldResultErr);
    assert_gt(gPldResultNumberOfPoses, 0);

    printf("Before return mv_inference_get_number_of_poses_p\n");
    return 0;
}

/**
 * @brief Negative test case of mv_inference_get_number_of_poses()
 * @testcase        utc_mediavision_mv_inference_get_number_of_poses_n
 * @since_tizen     6.0
 * @description     Get the number of poses from a detected result,
 *                  but fail because handle is NULL
 */
int utc_mediavision_mv_inference_get_number_of_poses_n(void)
{
    printf("Inside mv_inference_get_number_of_poses_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    // handle is NULL
    int ret = mv_inference_pose_get_number_of_poses(NULL, &gPldResultNumberOfPoses);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_inference_get_number_of_poses_n\n");
    return 0;
}

static void get_pose_landmark_detection_result_cb2(mv_source_h source,
                                    mv_inference_pose_result_h result,
                                    void *user_data)
{
    printf("Inside get_pose_landmark_detection_result_cb2\n");
    gIsPoseLandmarkDetectCallBackInvoked = true;

    gPldResultErr = mv_inference_pose_get_number_of_landmarks(result, &gPldResultNumberOfLandmarks);
    printf("Before retrun get_pose_landmark_detection_result_cb2\n");
}

/**
 * @function	utc_mediavision_mv_inference_pose_landmark_detect_cb2_startup
 * @description	Inference module UTC startup code for mv_inference_pose_get_number_of_landmarks()
 * @parameter	NA
 * @return		NA
 */
void utc_capi_media_vision_inference_pose_landmark_detect_cb2_startup(void)
{
    printf("Inside utc_mediavision_mv_inference_pose_landmark_detect_cb2_startup\n");
    utc_capi_media_vision_inference_startup2();

    if (gStartupError != MEDIA_VISION_ERROR_NONE)
        return;

    char imageFilename[FILE_PATH_SIZE];
    int ret = set_pose_landmark_detection_engine_config(gEngineConfigHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("set_pose_landmark_detection_engine_config is failed\n");
        return;
    }

    ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("mv_inference_configure is failed\n");
        return;
    }

    ret = mv_inference_prepare(gInferenceHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("mv_inference_prepare is failed\n");
        return;
    }

    snprintf(imageFilename, FILE_PATH_SIZE, "%s/images/%s", gInferenceExampleDir, "poseLandmark.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("load_image_to_media_source is failed\n");
        return;
    }

    ret = mv_inference_pose_landmark_detect(gSourceHandle,
                                    gInferenceHandle,
                                    NULL,
                                    get_pose_landmark_detection_result_cb2,
                                    NULL);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("mv_inference_pose_landmark_detect is failed\n");
        return;
    }

    printf("Before return utc_mediavision_mv_inference_pose_landmark_detect_cb2_startup\n");
}

/**
 * @brief Positive test case of mv_inference_get_number_of_landmarks()
 * @testcase        utc_mediavision_mv_inference_get_number_of_landmarks_p
 * @since_tizen     6.0
 * @description     Get the number of landmarks from a detected result
 */
int utc_mediavision_mv_inference_get_number_of_landmarks_p(void)
{
    printf("Inside mv_inference_get_number_of_landmarks_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(true, gIsPoseLandmarkDetectCallBackInvoked);
    assert_eq(MEDIA_VISION_ERROR_NONE, gPldResultErr);
    assert_gt(gPldResultNumberOfLandmarks, 0);

    printf("Before return mv_inference_get_number_of_landmarks_p\n");
    return 0;
}

/**
 * @brief Negative test case of mv_inference_get_number_of_landmarks()
 * @testcase        utc_mediavision_mv_inference_get_number_of_landmarks_n
 * @since_tizen     6.0
 * @description     Get the number of landmarks from a detected result,
 *                  but fail because handle is NULL
 */
int utc_mediavision_mv_inference_get_number_of_landmarks_n(void)
{
    printf("Inside mv_inference_get_number_of_landmarks_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    // handle is NULL
    int ret = mv_inference_pose_get_number_of_landmarks(NULL, &gPldResultNumberOfLandmarks);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_inference_get_number_of_landmarks_n\n");
    return 0;
}

static void get_pose_landmark_detection_result_cb3(mv_source_h source,
                                    mv_inference_pose_result_h result,
                                    void *user_data)
{
    printf("Inside get_pose_landmark_detection_result_cb3\n");
    gIsPoseLandmarkDetectCallBackInvoked = true;

    // get the number of poses
    gPldResultErr = mv_inference_pose_get_number_of_poses(result, &gPldResultNumberOfPoses);
    if (gPldResultErr != MEDIA_VISION_ERROR_NONE)
        return;

    // get the number of landmarks
    gPldResultErr = mv_inference_pose_get_number_of_landmarks(result, &gPldResultNumberOfLandmarks);
    if (gPldResultErr != MEDIA_VISION_ERROR_NONE)
        return;

    // allocate memory with the number of poses
    gPldResultLandmarks = (mv_point_s **)malloc(gPldResultNumberOfPoses * sizeof(mv_point_s *));
    gPldResultScore = (float **)malloc(gPldResultNumberOfPoses * sizeof(float *));
    for (int pose = 0; pose < gPldResultNumberOfPoses; ++pose) {
        // allocate memory with the number of landmarks
        gPldResultLandmarks[pose] = (mv_point_s *)malloc(gPldResultNumberOfLandmarks * sizeof(mv_point_s));
        gPldResultScore[pose] = (float *)malloc(gPldResultNumberOfLandmarks * sizeof(float));
        for (int part = 0; part < gPldResultNumberOfLandmarks; ++part) {
            gPldResultErr = mv_inference_pose_get_landmark(result, pose, part,
                                                            &(gPldResultLandmarks[pose][part]),
                                                            &(gPldResultScore[pose][part]));
            if (gPldResultErr != MEDIA_VISION_ERROR_NONE)
                return;
        }
    }

    gIsGetPoseLandmark = true;
    printf("Before retrun get_pose_landmark_detection_result_cb3\n");
}

/**
 * @function	utc_mediavision_mv_inference_pose_landmark_detect_cb3_startup
 * @description	Inference module UTC startup code for mv_inference_pose_get_landmark()
 * @parameter	NA
 * @return		NA
 */
void utc_capi_media_vision_inference_pose_landmark_detect_cb3_startup(void)
{
    printf("Inside utc_mediavision_mv_inference_pose_landmark_detect_cb3_startup\n");
    utc_capi_media_vision_inference_startup2();

    if (gStartupError != MEDIA_VISION_ERROR_NONE)
        return;

    char imageFilename[FILE_PATH_SIZE];
    int ret =  set_pose_landmark_detection_engine_config(gEngineConfigHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("set_pose_landmark_detection_engine_config is failed\n");
        return;
    }

    ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("mv_inference_configure is failed\n");
        return;
    }

    ret = mv_inference_prepare(gInferenceHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("mv_inference_prepare is failed\n");
        return;
    }

    snprintf(imageFilename, FILE_PATH_SIZE, "%s/images/%s", gInferenceExampleDir, "poseLandmark.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("load_image_to_media_source is failed\n");
        return;
    }

    ret = mv_inference_pose_landmark_detect(gSourceHandle,
                                    gInferenceHandle,
                                    NULL,
                                    get_pose_landmark_detection_result_cb3,
                                    NULL);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("mv_inference_pose_landmark_detect is failed\n");
        return;
    }

    printf("Before return utc_mediavision_mv_inference_pose_landmark_detect_cb3_startup\n");
}

/**
 * @brief Positive test case of mv_inference_get_landmark()
 * @testcase        utc_mediavision_mv_inference_get_landmark_p
 * @since_tizen     6.0
 * @description     Get landmarks from a detected result
 */
int utc_mediavision_mv_inference_get_landmark_p(void)
{
    printf("Inside mv_inference_get_landmark_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(true, gIsPoseLandmarkDetectCallBackInvoked);
    assert_eq(MEDIA_VISION_ERROR_NONE, gPldResultErr);
    assert_gt(gPldResultNumberOfPoses, 0);
    assert_gt(gPldResultNumberOfLandmarks, 0);
    assert_eq(true, gIsGetPoseLandmark);

    printf("Before return mv_inference_get_landmark_p\n");
    return 0;
}

/**
 * @brief Negative test case of mv_inference_get_landmark()
 * @testcase        utc_mediavision_mv_inference_get_landmark_n
 * @since_tizen     6.0
 * @description     Get landmarks from a detected result,
 *                  but fail because handle is NULL
 */
int utc_mediavision_mv_inference_get_landmark_n(void)
{
    printf("Inside mv_inference_get_landmark_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    // handle is NULL
    mv_point_s landmark;
    float score;
    int ret = mv_inference_pose_get_landmark(NULL, 0, 0, &landmark, &score);

    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_inference_get_landmark_n\n");
    return 0;
}

static void get_pose_landmark_detection_result_cb5(mv_source_h source,
                                    mv_inference_pose_result_h result,
                                    void *user_data)
{
    printf("Inside get_pose_landmark_detection_result_cb5\n");
    gIsPoseLandmarkDetectCallBackInvoked = true;

    gPldResultErr = mv_inference_pose_get_number_of_poses(result, &gPldResultNumberOfPoses);
    if (gPldResultErr != MEDIA_VISION_ERROR_NONE)
        return;

    if (gPldResultNumberOfPoses <= 0)
        return;

    gPldResultErr = mv_inference_pose_get_label(result, 0, &gPldResultLabel);
    printf("Before retrun get_pose_landmark_detection_result_cb5\n");
}

/**
 * @function	utc_mediavision_mv_inference_pose_landmark_detect_cb5_startup
 * @description	Inference module UTC startup code for mv_inference_pose_get_label()
 * @parameter	NA
 * @return		NA
 */
void utc_capi_media_vision_inference_pose_landmark_detect_cb5_startup(void)
{
    printf("Inside utc_mediavision_mv_inference_pose_landmark_detect_cb5_startup\n");
    utc_capi_media_vision_inference_startup2();

    if (gStartupError != MEDIA_VISION_ERROR_NONE)
        return;

    char imageFilename[FILE_PATH_SIZE];
    int ret = set_pose_landmark_detection_engine_config(gEngineConfigHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("set_pose_landmark_detection_engine_config is failed\n");
        return;
    }

    ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("mv_inference_configure is failed\n");
        return;
    }

    ret = mv_inference_prepare(gInferenceHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("mv_inference_prepare is failed\n");
        return;
    }

    snprintf(imageFilename, FILE_PATH_SIZE, "%s/images/%s", gInferenceExampleDir, "poseLandmark.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("load_image_to_media_source is failed\n");
        return;
    }

    ret = mv_inference_pose_landmark_detect(gSourceHandle,
                                    gInferenceHandle,
                                    NULL,
                                    get_pose_landmark_detection_result_cb5,
                                    NULL);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("mv_inference_pose_landmark_detect is failed\n");
        return;
    }

    printf("Before return utc_mediavision_mv_inference_pose_landmark_detect_cb5_startup\n");
}

/**
 * @brief Positive test case of mv_inference_get_label()
 * @testcase        utc_mediavision_mv_inference_pose_get_label_p
 * @since_tizen     6.0
 * @description     Get the label from a detected result
 */
int utc_mediavision_mv_inference_get_label_p(void)
{
    printf("Inside mv_inference_pose_get_label_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(true, gIsPoseLandmarkDetectCallBackInvoked);
    assert_eq(MEDIA_VISION_ERROR_NONE, gPldResultErr);
    assert_gt(gPldResultNumberOfPoses, 0);
    assert_leq(gPldResultLabel, 0);

    printf("Before return mv_inference_pose_get_label_p\n");
    return 0;
}

/**
 * @brief Positive test case of mv_inference_get_label()
 * @testcase        utc_mediavision_mv_inference_pose_get_label_n
 * @since_tizen     6.0
 * @description     Get the label from a detected result,
 *                  but fail because handle is NULL
 */
int utc_mediavision_mv_inference_get_label_n(void)
{
    printf("Inside mv_inference_pose_get_label_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    // handle is NULL
    int ret = mv_inference_pose_get_label(NULL, 0, &gPldResultLabel);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_inference_pose_get_label_nn");
    return 0;
}

/**
 * @brief Positive test case of mv_pose_create_p()
 * @testcase        utc_mediavision_mv_pose_create_p
 * @since_tizen     6.0
 * @description     Create pose handle
 */
int utc_mediavision_mv_pose_create_p(void)
{
    printf("Inside mv_pose_create_p\n");

    mv_pose_h poseHandle = NULL;
    int ret = mv_pose_create(&poseHandle);
    if (!isVisionSupported) {
        assert_eq(ret, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_pose_destroy(poseHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_pose_create_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_pose_create()
 * @testcase        utc_mediavision_mv_pose_create_n
 * @since_tizen     6.0
 * @description     Create pose handle,
 *                  but fail because input parameter is NULL
 */
int utc_mediavision_mv_pose_create_n(void)
{
    printf("Inside mv_pose_create_n\n");

    int ret = mv_pose_create(NULL);
    if (!isVisionSupported) {
        assert_eq(ret, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_pose_create_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_pose_destroy_p()
 * @testcase        utc_mediavision_mv_pose_destroy_p
 * @since_tizen     6.0
 * @description     Destroy pose handle
 */
int utc_mediavision_mv_pose_destroy_p(void)
{
    printf("Inside mv_pose_destroy_p\n");

    mv_pose_h poseHandle = NULL;
    int ret = mv_pose_create(&poseHandle);
    if (!isVisionSupported) {
        assert_eq(ret, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_pose_destroy(poseHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_pose_destroy_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_pose_destroy_n()
 * @testcase        utc_mediavision_mv_pose_destroy_n
 * @since_tizen     6.0
 * @description     Destroy pose handle,
 *                  but fail because input parameter is NULL
 */
int utc_mediavision_mv_pose_destroy_n(void)
{
    printf("Inside mv_pose_destroy_n\n");

    int ret = mv_pose_destroy(NULL);
    if (!isVisionSupported) {
        assert_eq(ret, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_pose_destroy_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_pose_set_from_file()
 * @testcase        utc_mediavision_mv_pose_set_from_file_p
 * @since_tizen     6.0
 * @description     Set pose mocap file and its mapping file
 */
int utc_mediavision_mv_pose_set_from_file_p(void)
{
    printf("Inside mv_pose_set_from_file_p\n");

    mv_pose_h poseHandle = NULL;
    int ret = mv_pose_create(&poseHandle);
    if (!isVisionSupported) {
        assert_eq(ret, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    char poseMocapFilename[FILE_PATH_SIZE];
    char poseMocapMappingFilename[FILE_PATH_SIZE];
    snprintf(poseMocapFilename, FILE_PATH_SIZE, "%s/models/%s", gInferenceExampleDir, "pld_mocap.bvh");
    snprintf(poseMocapMappingFilename, FILE_PATH_SIZE, "%s/models/%s", gInferenceExampleDir, "pld_mocap_mapping.txt");

    ret = mv_pose_set_from_file(poseHandle, poseMocapFilename, poseMocapMappingFilename);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_pose_destroy(poseHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_pose_set_from_file_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_pose_set_from_file()
 * @testcase        utc_mediavision_mv_pose_set_from_file_n1
 * @since_tizen     6.0
 * @description     Set pose mocap file and its mapping file,
 *                  but fail because file paths are NULL
 */
int utc_mediavision_mv_pose_set_from_file_n1(void)
{
    printf("Inside mv_pose_set_from_file_n1\n");

    mv_pose_h poseHandle = NULL;
    int ret = mv_pose_create(&poseHandle);
    if (!isVisionSupported) {
        assert_eq(ret, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    char poseMocapFilename[FILE_PATH_SIZE];
    char poseMocapMappingFilename[FILE_PATH_SIZE];
    snprintf(poseMocapFilename, FILE_PATH_SIZE, "%s/models/%s", gInferenceExampleDir, "pld_mocap.bvh");
    snprintf(poseMocapMappingFilename, FILE_PATH_SIZE, "%s/models/%s", gInferenceExampleDir, "pld_mocap_mapping.txt");

    // hand is NULL
    ret = mv_pose_set_from_file(NULL, poseMocapFilename, poseMocapMappingFilename);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    // motion capture file path is NULL
    ret = mv_pose_set_from_file(poseHandle, NULL, poseMocapMappingFilename);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    // motion mapping file path is NULL
    ret = mv_pose_set_from_file(poseHandle, poseMocapFilename, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_pose_destroy(poseHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_pose_set_from_file_n1\n");

    return 0;
}

/**
 * @brief Negative test case of mv_pose_set_from_file()
 * @testcase        utc_mediavision_mv_pose_set_from_file_n2
 * @since_tizen     6.0
 * @description     Set pose mocap file and its mapping file,
 *                  but fail because file paths are fake (invalid)
 */
int utc_mediavision_mv_pose_set_from_file_n2(void)
{
    printf("Inside mv_pose_set_from_file_n2\n");

    mv_pose_h poseHandle = NULL;
    int ret = mv_pose_create(&poseHandle);
    if (!isVisionSupported) {
        assert_eq(ret, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    char poseMocapFilename[FILE_PATH_SIZE];
    char poseMocapMappingFilename[FILE_PATH_SIZE];
    snprintf(poseMocapFilename, FILE_PATH_SIZE, "%s/models/%s", gInferenceExampleDir, "pld_mocap.bvh");
    snprintf(poseMocapMappingFilename, FILE_PATH_SIZE, "%s/models/%s", gInferenceExampleDir, "pld_mocap_mapping.txt");

    // fakefile doesn't exist
    char fakeFilename[FILE_PATH_SIZE];
    snprintf(fakeFilename, FILE_PATH_SIZE, "%s/models/%s", gInferenceExampleDir, "fakefile");

    // motion capture file path is invalid
    ret = mv_pose_set_from_file(poseHandle, fakeFilename, poseMocapMappingFilename);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PATH, ret);

    // motion mapping file path is invalid
    ret = mv_pose_set_from_file(poseHandle, poseMocapFilename, fakeFilename);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PATH, ret);

    ret = mv_pose_destroy(poseHandle);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_pose_set_from_file_n2\n");

    return 0;
}

static void get_pose_landmark_detection_result_cb4(mv_source_h source,
                                    mv_inference_pose_result_h result,
                                    void *user_data)
{
    printf("Inside get_pose_landmark_detection_result_cb4\n");
    gIsPoseLandmarkDetectCallBackInvoked = true;

    mv_pose_h *pose = (mv_pose_h *)user_data;
    int part = MV_INFERENCE_HUMAN_BODY_PART_LEG_RIGHT | MV_INFERENCE_HUMAN_BODY_PART_LEG_LEFT;
    gPldResultErr = mv_pose_compare(*pose, result, part, &gPoseCompareScore);
    if (gPldResultErr != MEDIA_VISION_ERROR_NONE)
        return;

    printf("Before retrun get_pose_landmark_detection_result_cb4\n");
}

/**
 * @function	utc_mediavision_mv_inference_pose_landmark_detect_cb4_startup
 * @description	Inference module UTC startup code for mv_pose_compare()
 * @parameter	NA
 * @return		NA
 */
void utc_capi_media_vision_inference_pose_landmark_detect_cb4_startup(void)
{
    printf("Inside utc_mediavision_mv_inference_pose_landmark_detect_cb4_startup\n");
    utc_capi_media_vision_inference_startup2();

    if (gStartupError != MEDIA_VISION_ERROR_NONE)
        return;

    char imageFilename[FILE_PATH_SIZE];
    int ret = set_pose_landmark_detection_engine_config(gEngineConfigHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("set_pose_landmark_detection_engine_config is failed\n");
        return;
    }

    ret = mv_inference_configure(gInferenceHandle, gEngineConfigHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("mv_inference_configure is failed\n");
        return;
    }

    ret = mv_inference_prepare(gInferenceHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("mv_inference_prepare is failed\n");
        return;
    }

    snprintf(imageFilename, FILE_PATH_SIZE, "%s/images/%s", gInferenceExampleDir, "poseLandmark.jpg");
    ret = load_image_to_media_source(imageFilename, gSourceHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("load_image_to_media_source is failed\n");
        return;
    }

    ret = mv_pose_create(&gPoseHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("mv_pose_create is failed\n");
        return;
    }

    char poseMocapFilename[FILE_PATH_SIZE];
    char poseMocapMappingFilename[FILE_PATH_SIZE];
    snprintf(poseMocapFilename, FILE_PATH_SIZE, "%s/models/%s", gInferenceExampleDir, "pld_mocap.bvh");
    snprintf(poseMocapMappingFilename, FILE_PATH_SIZE, "%s/models/%s", gInferenceExampleDir, "pld_mocap_mapping.txt");

    ret = mv_pose_set_from_file(gPoseHandle, poseMocapFilename, poseMocapMappingFilename);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("mv_pose_set_from_file is failed\n");
        return;
    }

    ret = mv_inference_pose_landmark_detect(gSourceHandle,
                                    gInferenceHandle,
                                    NULL,
                                    get_pose_landmark_detection_result_cb4,
                                    &gPoseHandle);
    if (ret != MEDIA_VISION_ERROR_NONE) {
        printf("mv_inference_pose_landmark_detect is failed\n");
        return;
    }

    printf("Before return utc_mediavision_mv_inference_pose_landmark_detect_cb4_startup\n");
}

/**
 * @brief Positive test case of mv_pose_compare()
 * @testcase        utc_mediavision_mv_pose_compare_p
 * @since_tizen     6.0
 * @description     Compare a result which is detected by mv_inference_pose_landmark_detect()
 *                  with a pose which is set by mv_pose_set_from_file()
 */
int utc_mediavision_mv_pose_compare_p(void)
{
    printf("Inside mv_inference_get_landmark_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(true, gIsPoseLandmarkDetectCallBackInvoked);
    assert_eq(MEDIA_VISION_ERROR_NONE, gPldResultErr);
    assert_gt(gPoseCompareScore, 0.5);

    printf("Before return mv_inference_get_landmark_p\n");
    return 0;
}

/**
 * @brief Negative test case of mv_pose_compare()
 * @testcase        utc_mediavision_mv_pose_compare_n
 * @since_tizen     6.0
 * @description     Compare a result which is detected by mv_inference_pose_landmark_detect()
 *                  with a pose which is set by mv_pose_set_from_file(),
 *                  but fail because hanlde is NULL
 */
int utc_mediavision_mv_pose_compare_n(void)
{
    printf("Inside mv_pose_compare_n\n");

    mv_pose_h poseHandle = NULL;
    int ret = mv_pose_create(&poseHandle);
    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    char poseMocapFilename[FILE_PATH_SIZE];
    char poseMocapMappingFilename[FILE_PATH_SIZE];
    snprintf(poseMocapFilename, FILE_PATH_SIZE, "%s/models/%s", gInferenceExampleDir, "pld_mocap.bvh");
    snprintf(poseMocapMappingFilename, FILE_PATH_SIZE, "%s/models/%s", gInferenceExampleDir, "pld_mocap_mapping.txt");

    ret = mv_pose_set_from_file(poseHandle, poseMocapFilename, poseMocapMappingFilename);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    int part = MV_INFERENCE_HUMAN_BODY_PART_LEG_RIGHT | MV_INFERENCE_HUMAN_BODY_PART_LEG_LEFT;
    // handle is NULL
    ret = mv_pose_compare(poseHandle, NULL, part, &gPoseCompareScore);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_pose_compare_n\n");
    return 0;
}
