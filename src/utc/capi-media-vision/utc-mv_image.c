/**
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
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
#include <mv_image.h>

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

static mv_image_tracking_model_h g_tracking_model = NULL;

const char *target_image_source_path = NULL;
const char *scene_image_source_path = NULL;
const char *tracking_squence_path = NULL;
const int tracking_squence_size = 22;
const char *tracking_frame_type = ".jpg";
const char *pInternalDataPath = NULL;

static bool check_image_model_files(
        const char *file_name_src,
        const char *file_name_dst)
{
    FILE *fp1, *fp2;
    int ch1, ch2;
    bool ret;

    fp1 = fopen(file_name_src, "r");
    fp2 = fopen(file_name_dst, "r");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Fail to open source %s or destination %s\n",
                         file_name_src, file_name_dst);
        if (fp1) {
            fclose(fp1);
        }

        if (fp2) {
            fclose(fp2);
        }
        return false;
    }

    ch1 = getc(fp1);
    ch2 = getc(fp2);

    while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2))
    {
        ch1 = getc(fp1);
        ch2 = getc(fp2);
    }

    if (ch1 == ch2)
    {
        printf("Model files are identical\n");
        fclose(fp1);
        fclose(fp2);
        ret = true;
    }
    else
    {
        printf("Model files are Not identical\n");
        fclose(fp1);
        fclose(fp2);
        ret = false;
    }

    return ret;
}

static int load_source(
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

    ret2 = mv_source_fill_by_buffer(source, data_buffer, (unsigned int)buffer_size,
                                   (unsigned int)width, (unsigned int)height, source_colorspace);

_LOAD_IMAGE_FAIL:
    image_util_decode_destroy(_decoder);
    if(data_buffer)
        free(data_buffer);

    assert_eq(IMAGE_UTIL_ERROR_NONE, ret1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret2);

    return MEDIA_VISION_ERROR_NONE;
}

static int load_tracking_frame(
        int frame_number,
        mv_source_h source)
{
    char frame_path[100] = {0};
    snprintf(frame_path, 100, "%s%i%s",
            tracking_squence_path,
            frame_number,
            tracking_frame_type);
    return load_source(frame_path, source);
}

/**
 * @function	utc_capi_media_vision_image_startup
 * @description	Image module UTC startup code
 * @parameter	NA
 * @return		NA
 */
void utc_capi_media_vision_image_startup(void)
{
    printf("capi-media-vision mv_image tests STARTUP is launched\n");

    bool isImageRecognitionSupported = false;
    system_info_get_platform_bool("http://tizen.org/feature/vision.image_recognition", &isImageRecognitionSupported);

    if (isImageRecognitionSupported)
        isVisionSupported = true;
    else
        isVisionSupported = false;
    
    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    if (true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE)) {
        PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received %s\\n", __LINE__, API_NAMESPACE, pszValue);
        target_image_source_path=(char*)calloc(strlen(pszValue)+strlen("/res/res/image/target.jpg")+1, sizeof(char));
        snprintf(target_image_source_path, strlen(pszValue)+strlen("/res/res/image/target.jpg")+1, "%s/res/res/image/target.jpg", pszValue);

        scene_image_source_path=(char*)calloc(strlen(pszValue)+strlen("/res/res/image/scene.jpg")+1, sizeof(char));
        snprintf(scene_image_source_path, strlen(pszValue)+strlen("/res/res/image/scene.jpg")+1, "%s/res/res/image/scene.jpg", pszValue);

        tracking_squence_path=(char*)calloc(strlen(pszValue)+strlen("/res/res/image/tracking/frame")+1, sizeof(char));
        snprintf(tracking_squence_path, strlen(pszValue)+strlen("/res/res/image/tracking/frame")+1, "%s/res/res/image/tracking/frame", pszValue);

        pInternalDataPath=(char*)calloc(strlen(pszValue)+strlen("/data")+1,sizeof(char));
        snprintf(pInternalDataPath, strlen(pszValue)+strlen("/data")+1, "%s/data", pszValue);
    } else {
        PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
    }

    gStartupError = mv_image_tracking_model_create(&g_tracking_model);
    if (MEDIA_VISION_ERROR_NONE != gStartupError) {
        g_tracking_model = NULL;
        printf("mv_image_tracking_model_h create is failed\n");
        return;
    }

    printf("capi-media-vision mv_image tests STARTUP is completed\n");
}

/**
 * @function	utc_capi_media_vision_image_cleanup
 * @description	Image module UTC cleanup code
 * @parameter	NA
 * @return		NA
 */
void utc_capi_media_vision_image_cleanup(void)
{
    	printf("capi-media-vision mv_image tests CLEANUP is launched\n");

	if (g_tracking_model) {
		mv_image_tracking_model_destroy(g_tracking_model);
		g_tracking_model = NULL;
	}

	if (target_image_source_path) {
		free(target_image_source_path);
		target_image_source_path = NULL;
	}

	if (scene_image_source_path) {
		free(scene_image_source_path);
		scene_image_source_path = NULL;
	}

	if (tracking_squence_path) {
		free(tracking_squence_path);
		tracking_squence_path = NULL;
	}

	if (pInternalDataPath) {
		free(pInternalDataPath);
		pInternalDataPath = NULL;
	}

    	printf("capi-media-vision mv_image tests CLEANUP is completed\n");
}

/**
 * @brief Positive test case of mv_image_tracking_model_create()
 * @testcase        utc_mediavision_mv_image_tracking_model_create_p
 * @since_tizen     3.0
 * @description     Create image tracking model handle
 */
int utc_mediavision_mv_image_tracking_model_create_p(void)
{
    printf("Inside mv_image_tracking_model_create_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_image_tracking_model_h tracking_model;
    int ret = mv_image_tracking_model_create(&tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_tracking_model_destroy(tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_image_tracking_model_create_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_tracking_model_create()
 * @testcase        utc_mediavision_mv_image_tracking_model_create_n
 * @since_tizen     3.0
 * @description     Create image tracking model handle,
 *                  but fail because input pamameter is NULL
 */
int utc_mediavision_mv_image_tracking_model_create_n(void)
{
    printf("Inside mv_image_tracking_model_create_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_image_tracking_model_create(NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_image_tracking_model_create_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_image_tracking_model_destroy()
 * @testcase        utc_mediavision_mv_image_tracking_model_destroy_p
 * @since_tizen     3.0
 * @description     Destroy image tracking model handle
 */
int utc_mediavision_mv_image_tracking_model_destroy_p(void)
{
    printf("Inside mv_image_tracking_model_destroy_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_image_tracking_model_h tracking_model;
    int ret = mv_image_tracking_model_create(&tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_tracking_model_destroy(tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_image_tracking_model_destroy_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_tracking_model_destroy()
 * @testcase        utc_mediavision_mv_image_tracking_model_destroy_n
 * @since_tizen     3.0
 * @description     Destroy image tracking model handle,
 *                  but fail because input parameter is NULL
 */
int utc_mediavision_mv_image_tracking_model_destroy_n(void)
{
    printf("Inside mv_image_tracking_model_destroy_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_image_tracking_model_destroy(NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_image_tracking_model_destroy_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_image_tracking_model_clone()
 * @testcase        utc_mediavision_mv_image_tracking_model_clone_p
 * @since_tizen     3.0
 * @description     Clone image tracking model
 */
int utc_mediavision_mv_image_tracking_model_clone_p(void)
{
    printf("Inside mv_image_tracking_model_clone_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_image_tracking_model_h tracking_model_src = NULL;
    int ret = mv_image_tracking_model_create(&tracking_model_src);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_image_tracking_model_h tracking_model_dst = NULL;

    ret = mv_image_tracking_model_clone(tracking_model_src, &tracking_model_dst);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    // Check whether source_model and dest_model equal or not
    char path_to_save_src[FILE_PATH_SIZE] = "";
    snprintf(path_to_save_src, FILE_PATH_SIZE, "%s/test_img_s", pInternalDataPath);
    ret = mv_image_tracking_model_save(path_to_save_src, tracking_model_src);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    char path_to_save_dst[FILE_PATH_SIZE] = "";
    snprintf(path_to_save_dst, FILE_PATH_SIZE, "%s/test_img_d", pInternalDataPath);
    ret = mv_image_tracking_model_save(path_to_save_dst, tracking_model_dst);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    bool compare_models = check_image_model_files(path_to_save_src, path_to_save_dst);
    assert_eq(true, compare_models);

    ret = mv_image_tracking_model_destroy(tracking_model_src);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_tracking_model_destroy(tracking_model_dst);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_image_tracking_model_clone_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_tracking_model_clone()
 * @testcase        utc_mediavision_mv_image_tracking_model_clone_n
 * @since_tizen     3.0
 * @description     Clone image tracking model
 *                  but fail input parameters are NULL
 */
int utc_mediavision_mv_image_tracking_model_clone_n(void)
{
    printf("Inside mv_image_tracking_model_clone_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_image_tracking_model_clone(NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_image_tracking_model_clone_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_image_tracking_model_save()
 * @testcase        utc_mediavision_mv_image_tracking_model_save_p
 * @since_tizen     3.0
 * @description     Save image tracking model
 */
int utc_mediavision_mv_image_tracking_model_save_p(void)
{
    printf("Inside mv_image_tracking_model_save_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_image_tracking_model_h tracking_model;
    int ret = mv_image_tracking_model_create(&tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    char path_to_save[FILE_PATH_SIZE] = "";
    snprintf(path_to_save, FILE_PATH_SIZE, "%s/tracking_model_s", pInternalDataPath);
    ret = mv_image_tracking_model_save(path_to_save, tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_tracking_model_destroy(tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_image_tracking_model_destroy_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_tracking_model_save()
 * @testcase        utc_mediavision_mv_image_tracking_model_save_n1
 * @since_tizen     3.0
 * @description     Save image tracking model,
 *                  but fail because parameters are NULL
 */
int utc_mediavision_mv_image_tracking_model_save_n1(void)
{
    printf("Inside mv_image_tracking_model_save_n1\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_image_tracking_model_save(NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_image_tracking_model_save_n1\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_tracking_model_save()
 * @testcase        utc_mediavision_mv_image_tracking_model_save_n2
 * @since_tizen     3.0
 * @description     Save image tracking model,
 *                  but fail because file_name is NULL
 */
int utc_mediavision_mv_image_tracking_model_save_n2(void)
{
    printf("Inside mv_image_tracking_model_save_n2\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_image_tracking_model_h tracking_model;
    int ret = mv_image_tracking_model_create(&tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_tracking_model_save(NULL, tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, mv_image_tracking_model_destroy(tracking_model));
    assert_eq(MEDIA_VISION_ERROR_INVALID_PATH, ret);

    printf("Before return mv_image_tracking_model_save_n2\n");

    return 0;
}

/**
 * @brief Positive test case of mv_image_tracking_model_load()
 * @testcase        utc_mediavision_mv_image_tracking_model_load_p
 * @since_tizen     3.0
 * @description     Load image tracking model
 */
int utc_mediavision_mv_image_tracking_model_load_p(void)
{
    printf("Inside mv_image_tracking_model_load_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_image_tracking_model_h source_model = NULL;
    int ret = mv_image_tracking_model_create(&source_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    char path_to_save[FILE_PATH_SIZE] = "";
    snprintf(path_to_save, FILE_PATH_SIZE, "%s/tracking_model_l", pInternalDataPath);
    ret = mv_image_tracking_model_save(path_to_save, source_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_tracking_model_destroy(source_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    source_model = NULL;

    ret = mv_image_tracking_model_load(path_to_save, &source_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_tracking_model_destroy(source_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_image_tracking_model_load_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_tracking_model_load()
 * @testcase        utc_mediavision_mv_image_tracking_model_load_n1
 * @since_tizen     3.0
 * @description     Load image tracking model,
 *                  but fail because input parameters are NULL
 */
int utc_mediavision_mv_image_tracking_model_load_n1(void)
{
    printf("Inside mv_image_tracking_model_load_n1\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_image_tracking_model_load(NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_image_tracking_model_load_n1\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_tracking_model_load()
 * @testcase        utc_mediavision_mv_image_tracking_model_load_n2
 * @since_tizen     3.0
 * @description     Load image tracking model,
 *                  but fail because file_name is NULL
 */
int utc_mediavision_mv_image_tracking_model_load_n2(void)
{
    printf("Inside mv_image_tracking_model_load_n2\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_image_tracking_model_h source_model = NULL;
    const int ret = mv_image_tracking_model_load(NULL, &source_model);

    assert_eq(MEDIA_VISION_ERROR_INVALID_PATH, ret);

    printf("Before return mv_image_tracking_model_load_n2\n");

    return 0;
}

void recognized_cb(
        mv_source_h source,
        mv_engine_config_h engine_cfg,
        const mv_image_object_h *image_objects,
        mv_quadrangle_s **locations,
        unsigned int number_of_objects,
        void *user_data)
{
    if (NULL != user_data)
    {
        bool *is_called = (bool *)user_data;
        *is_called = true;
    }

    int object_num = 0;
    for (; object_num < number_of_objects; ++object_num)
    {
        if (NULL == locations[object_num])
        {
            printf("Image #%i is not recognized.\n", object_num);
        }
        else
        {
            printf("Image #%i is recognized. {(%i, %i); (%i, %i); (%i, %i); (%i, %i)}\n",
                    object_num,
                    locations[object_num]->points[0].x, locations[object_num]->points[0].y,
                    locations[object_num]->points[1].x, locations[object_num]->points[1].y,
                    locations[object_num]->points[2].x, locations[object_num]->points[2].y,
                    locations[object_num]->points[3].x, locations[object_num]->points[3].y);
        }
    }
}

/**
 * @brief Positive test case of mv_image_recognize()
 * @testcase        utc_mediavision_mv_image_recognize_p
 * @since_tizen     3.0
 * @description     Recognize image
 */
int utc_mediavision_mv_image_recognize_p(void)
{
    printf("Inside mv_image_recognize_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h target_image;
    int ret = mv_create_source(&target_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = load_source(target_image_source_path, target_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_image_object_h target;
    ret = mv_image_object_create(&target);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_object_fill(target, NULL, target_image, NULL);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_source_h scene_image;
    ret = mv_create_source(&scene_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = load_source(scene_image_source_path, scene_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    bool is_called = false;
    ret = mv_image_recognize(scene_image, &target, 1, NULL, recognized_cb, &is_called);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(true, is_called);

    ret = mv_destroy_source(scene_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_object_destroy(target);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_destroy_source(target_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_image_recognize_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_recognize()
 * @testcase        utc_mediavision_mv_image_recognize_n
 * @since_tizen     3.0
 * @description     Recognize image,
 *                  but fail because input parameters are NULL
 */
int utc_mediavision_mv_image_recognize_n(void)
{
    printf("Inside mv_image_recognize_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_image_recognize(NULL, NULL, 0, NULL, NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_image_recognize_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_image_object_create()
 * @testcase        utc_mediavision_mv_image_object_create_p
 * @since_tizen     3.0
 * @description     Create image object handle
 */
int utc_mediavision_mv_image_object_create_p(void)
{
    printf("Inside mv_image_object_create_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_image_object_h image_object;
    int ret = mv_image_object_create(&image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_object_destroy(image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_image_object_create_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_object_create()
 * @testcase        utc_mediavision_mv_image_object_create_n
 * @since_tizen     3.0
 * @description     Create image object handle,
 *                  but fail because input parameter is NULL
 */
int utc_mediavision_mv_image_object_create_n(void)
{
    printf("Inside mv_image_object_create_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_image_object_create(NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_image_object_create_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_image_object_destroy()
 * @testcase        utc_mediavision_mv_image_object_destroy_p
 * @since_tizen     3.0
 * @description     Destroy image object handle
 */
int utc_mediavision_mv_image_object_destroy_p(void)
{
    printf("Inside mv_image_object_destroy_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_image_object_h image_object;
    int ret = mv_image_object_create(&image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_object_destroy(image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_image_object_destroy_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_object_destroy()
 * @testcase        utc_mediavision_mv_image_object_destroy_n
 * @since_tizen     3.0
 * @description     Destroy image object handle,
 *                  but fail because input parameter is NULL
 */
int utc_mediavision_mv_image_object_destroy_n(void)
{
    printf("Inside mv_image_object_destroy_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_image_object_destroy(NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_image_object_destroy_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_image_object_fill()
 * @testcase        utc_mediavision_mv_image_object_fill_p
 * @since_tizen     3.0
 * @description     Fill image object
 */
int utc_mediavision_mv_image_object_fill_p(void)
{
    printf("Inside mv_image_object_fill_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h target_image;
    int ret = mv_create_source(&target_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = load_source(target_image_source_path, target_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_image_object_h target;
    ret = mv_image_object_create(&target);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_object_fill(target, NULL, target_image, NULL);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_object_destroy(target);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_destroy_source(target_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_image_object_fill_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_object_fill()
 * @testcase        utc_mediavision_mv_image_object_fill_n
 * @since_tizen     3.0
 * @description     Fill image object
 *                  but fail because input parameters are NULL
 */
int utc_mediavision_mv_image_object_fill_n(void)
{
    printf("Inside mv_image_object_fill_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_image_object_fill(NULL, NULL, NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_image_object_fill_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_image_object_save()
 * @testcase        utc_mediavision_mv_image_object_save_p
 * @since_tizen     3.0
 * @description     Save image object
 */
int utc_mediavision_mv_image_object_save_p(void)
{
    printf("Inside mv_image_object_save_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_image_object_h image_object;
    int ret = mv_image_object_create(&image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    char path_to_save[FILE_PATH_SIZE] = "";
    snprintf(path_to_save, FILE_PATH_SIZE, "%s/image_object", pInternalDataPath);

    ret = mv_image_object_save(path_to_save, image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_object_destroy(image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_image_object_save_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_object_save()
 * @testcase        utc_mediavision_mv_image_object_save_n1
 * @since_tizen     3.0
 * @description     Save image object,
 *                  input parameters are NULL
 */
int utc_mediavision_mv_image_object_save_n1(void)
{
    printf("Inside mv_image_object_save_n1\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_image_object_save(NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_image_object_save_n1\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_object_save()
 * @testcase        utc_mediavision_mv_image_object_save_n2
 * @since_tizen     3.0
 * @description     Save image object,
 *                  fine_name is NULL
 */
int utc_mediavision_mv_image_object_save_n2(void)
{
    printf("Inside mv_image_object_save_n2\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_image_object_h image_object;
    int ret = mv_image_object_create(&image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_object_save(NULL, image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, mv_image_object_destroy(image_object));
    assert_eq(MEDIA_VISION_ERROR_INVALID_PATH, ret);

    printf("Before return mv_image_object_save_n2\n");

    return 0;
}

/**
 * @brief Positive test case of mv_image_object_load()
 * @testcase        utc_mediavision_mv_image_object_load_p
 * @since_tizen     3.0
 * @description     Load image object
 */
int utc_mediavision_mv_image_object_load_p(void)
{
    printf("Inside mv_image_object_load_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_image_object_h image_object;
    int ret = mv_image_object_create(&image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    char path_to_save[FILE_PATH_SIZE] = "";
    snprintf(path_to_save, FILE_PATH_SIZE, "%s/image_object", pInternalDataPath);

    ret = mv_image_object_save(path_to_save, image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_object_destroy(image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    image_object = NULL;

    ret = mv_image_object_load(path_to_save, &image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_object_destroy(image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_image_object_load_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_object_load()
 * @testcase        utc_mediavision_mv_image_object_load_n1
 * @since_tizen     3.0
 * @description     Load image object,
 *                  but fail input parameters are NULL
 */
int utc_mediavision_mv_image_object_load_n1(void)
{
    printf("Inside mv_image_object_load_n1\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_image_object_load(NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_image_object_load_n1\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_object_load()
 * @testcase        utc_mediavision_mv_image_object_load_n2
 * @since_tizen     3.0
 * @description     Load image object,
 *                  but fail because file_name is NULL
 */
int utc_mediavision_mv_image_object_load_n2(void)
{
    printf("Inside mv_image_object_load_n2\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_image_object_h image_object = NULL;
    const int ret = mv_image_object_load(NULL, &image_object);

    assert_eq(MEDIA_VISION_ERROR_INVALID_PATH, ret);

    printf("Before return mv_image_object_load_n2\n");

    return 0;
}

/**
 * @brief Positive test case of mv_image_object_get_recognition_rate()
 * @testcase        utc_mediavision_mv_image_object_get_recognition_rate_p
 * @since_tizen     3.0
 * @description     Get recognition rate
 */
int utc_mediavision_mv_image_object_get_recognition_rate_p(void)
{
    printf("Inside mv_image_object_get_recognition_rate_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_image_object_h image_object;
    int ret = mv_image_object_create(&image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    double recognition_rate = 0.;
    ret = mv_image_object_get_recognition_rate(image_object, &recognition_rate);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(0, recognition_rate);

    ret = mv_image_object_destroy(image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_image_object_get_recognition_rate_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_object_get_recognition_rate()
 * @testcase        utc_mediavision_mv_image_object_get_recognition_rate_n
 * @since_tizen     3.0
 * @description     Get recognition rate,
 *                  but fail because input parameters are NULL
 */
int utc_mediavision_mv_image_object_get_recognition_rate_n(void)
{
    printf("Inside mv_image_object_get_recognition_rate_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_image_object_get_recognition_rate(NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_image_object_get_recognition_rate_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_image_object_get_label()
 * @testcase        utc_mediavision_mv_image_object_get_label_p
 * @since_tizen     3.0
 * @description     Get label of image object
 */
int utc_mediavision_mv_image_object_get_label_p(void)
{
    printf("Inside mv_image_object_get_label_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_image_object_h image_object;
    int ret = mv_image_object_create(&image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    const int test_label = 24;
    ret = mv_image_object_set_label(image_object, test_label);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    int label = 0;
    ret = mv_image_object_get_label(image_object, &label);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(test_label, label);

    ret = mv_image_object_destroy(image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_image_object_get_label_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_object_get_label()
 * @testcase        utc_mediavision_mv_image_object_get_label_n
 * @since_tizen     3.0
 * @description     Get label of image object,
 *                  but fail because input parameters are NULL
 */
int utc_mediavision_mv_image_object_get_label_n(void)
{
    printf("Inside mv_image_object_get_label_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_image_object_get_label(NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_image_object_get_label_n\n");

    return 0;
}


/**
 * @brief Positive test case of mv_image_object_set_label()
 * @testcase        utc_mediavision_mv_image_object_set_label_p
 * @since_tizen     3.0
 * @description     Set label to image object
 */
int utc_mediavision_mv_image_object_set_label_p(void)
{
    printf("Inside mv_image_object_set_label_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_image_object_h image_object;
    int ret = mv_image_object_create(&image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    const int test_label = 24;
    ret = mv_image_object_set_label(image_object, test_label);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_object_destroy(image_object);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_image_object_set_label_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_object_set_label()
 * @testcase        utc_mediavision_mv_image_object_set_label_n
 * @since_tizen     3.0
 * @description     Set label to image object,
 *                  but fail because input parameters are NULL
 */
int utc_mediavision_mv_image_object_set_label_n(void)
{
    printf("Inside mv_image_object_set_label_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_image_object_set_label(NULL, 0);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_image_object_set_label_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_image_object_clone()
 * @testcase        utc_mediavision_mv_image_object_clone_p
 * @since_tizen     3.0
 * @description     Clone image object
 */
int utc_mediavision_mv_image_object_clone_p(void)
{
    printf("Inside mv_image_object_clone_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_image_object_h image_object1 = NULL;
    int ret = mv_image_object_create(&image_object1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_image_object_h image_object2 = NULL;

    ret = mv_image_object_clone(image_object1, &image_object2);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    // Check whether objects equal or not
    char path_to_save_src[FILE_PATH_SIZE] = "";
    snprintf(path_to_save_src, FILE_PATH_SIZE, "%s/test_src_object", pInternalDataPath);
    ret = mv_image_object_save(path_to_save_src, image_object1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    char path_to_save_dst[FILE_PATH_SIZE] = "";
    snprintf(path_to_save_dst, FILE_PATH_SIZE, "%s/test_dst_object", pInternalDataPath);
    ret = mv_image_object_save(path_to_save_dst, image_object2);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    bool compare_models = check_image_model_files(path_to_save_src, path_to_save_dst);
    assert_eq(true, compare_models);

    ret = mv_image_object_destroy(image_object1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_object_destroy(image_object2);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_image_object_clone_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_object_clone()
 * @testcase        utc_mediavision_mv_image_object_clone_n
 * @since_tizen     3.0
 * @description     Clone image object,
 *                  but fail because input parameters are NULL
 */
int utc_mediavision_mv_image_object_clone_n(void)
{
    printf("Inside mv_image_object_clone_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_image_object_clone(NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_image_object_clone_n\n");

    return 0;
}

void tracked_cb(
        mv_source_h source,
        mv_image_tracking_model_h tracking_model,
        mv_engine_config_h engine_cfg,
        mv_quadrangle_s *location,
        void *user_data)
{
    if (NULL == user_data)
    {
        return;
    }

    bool *is_called = (bool *)user_data;
    *is_called = true;

    if (NULL == location)
    {
        printf("object is missing.");
        usleep(1000000);
    }
    else
    {
        printf("object is found. {(%i, %i); (%i, %i); (%i, %i); (%i, %i)}",
                location->points[0].x, location->points[0].y,
                location->points[1].x, location->points[1].y,
                location->points[2].x, location->points[2].y,
                location->points[3].x, location->points[3].y);
    }
    printf("\n");
}

/**
 * @brief Positive test case of mv_image_track()
 * @testcase        utc_mediavision_mv_image_track_p
 * @since_tizen     3.0
 * @description     Track image
 */
int utc_mediavision_mv_image_track_p(void)
{
    printf("Inside mv_image_track_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h target_image;
    int ret = mv_create_source(&target_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = load_source(target_image_source_path, target_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_image_object_h target;
    ret = mv_image_object_create(&target);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_object_fill(target, NULL, target_image, NULL);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_image_tracking_model_h target_tracking_model;
    ret = mv_image_tracking_model_create(&target_tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_tracking_model_set_target(target, target_tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_source_h frame_image;
    ret = mv_create_source(&frame_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    int frame_num = 0;
    for (frame_num = 1; frame_num <= tracking_squence_size; ++frame_num)
    {
        ret = load_tracking_frame(frame_num, frame_image);
        assert_eq(MEDIA_VISION_ERROR_NONE, ret);

        bool is_called = false;
        ret = mv_image_track(
                      frame_image,
                      target_tracking_model,
                      NULL,
                      tracked_cb,
                      &is_called);
        assert_eq(MEDIA_VISION_ERROR_NONE, ret);
        assert_eq(true, is_called);
    }

    ret = mv_destroy_source(frame_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_tracking_model_destroy(target_tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_object_destroy(target);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_destroy_source(target_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_image_track_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_track()
 * @testcase        utc_mediavision_mv_image_track_n
 * @since_tizen     3.0
 * @description     Track image,
 *                  but fail bacause input parameters are NULL
 */
int utc_mediavision_mv_image_track_n(void)
{
    printf("Inside mv_image_track_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_image_track(NULL, NULL, NULL, NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_image_track_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_image_tracking_model_refresh()
 * @testcase        utc_mediavision_mv_image_tracking_model_refresh_p
 * @since_tizen     3.0
 * @description     Refresh image tracking model
 */
int utc_mediavision_mv_image_tracking_model_refresh_p(void)
{
    printf("Inside mv_image_tracking_model_refresh_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h target_image;
    int ret = mv_create_source(&target_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = load_source(target_image_source_path, target_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_image_object_h target;
    ret = mv_image_object_create(&target);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_object_fill(target, NULL, target_image, NULL);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_image_tracking_model_h tracking_model;
    ret = mv_image_tracking_model_create(&tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_tracking_model_set_target(target, tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_tracking_model_refresh(tracking_model, NULL);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_tracking_model_destroy(tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_object_destroy(target);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_destroy_source(target_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_image_tracking_model_refresh_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_tracking_model_refresh()
 * @testcase        utc_mediavision_mv_image_tracking_model_refresh_n
 * @since_tizen     3.0
 * @description     Refresh image tracking model,
 *                  but fail because input parameters are NULL
 */
int utc_mediavision_mv_image_tracking_model_refresh_n(void)
{
    printf("Inside mv_image_tracking_model_refresh_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_image_tracking_model_refresh(NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_image_tracking_model_refreshn\n");

    return 0;
}

/**
 * @brief Positive test case of mv_image_tracking_model_set_target()
 * @testcase        utc_mediavision_mv_image_tracking_model_set_target_p
 * @since_tizen     3.0
 * @description     Set target to image tracking model
 */
int utc_mediavision_mv_image_tracking_model_set_target_p(void)
{
    printf("Inside mv_image_tracking_model_set_target_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h target_image;
    int ret = mv_create_source(&target_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = load_source(target_image_source_path, target_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_image_object_h target;
    ret = mv_image_object_create(&target);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_object_fill(target, NULL, target_image, NULL);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_image_tracking_model_h target_tracking_model;
    ret = mv_image_tracking_model_create(&target_tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_tracking_model_set_target(target, target_tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_tracking_model_destroy(target_tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_image_object_destroy(target);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_destroy_source(target_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_image_tracking_model_set_target_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_image_tracking_model_set_target()
 * @testcase        utc_mediavision_mv_image_tracking_model_set_target_n
 * @since_tizen     3.0
 * @description     Set target to image tracking model,
 *                  but fail because input parameters are NULL
 */
int utc_mediavision_mv_image_tracking_model_set_target_n(void)
{
    printf("Inside mv_image_tracking_model_set_target_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_image_tracking_model_set_target(NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_image_tracking_model_set_target_n\n");

    return 0;
}
