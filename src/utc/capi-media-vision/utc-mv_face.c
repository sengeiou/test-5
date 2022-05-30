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
#include <mv_face.h>

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <image_util.h>
#include <system_info.h>
#include <storage.h>
#include "tct_common.h"

#define FILE_PATH_SIZE 1024
#define API_NAMESPACE "[MediaVision]"

static bool isVisionSupported = false;
static int gStartupError;

static unsigned int p1_face_examples_n = 5;
const char *p1_face_examples_dir = NULL;

static unsigned int p2_face_examples_n = 5;
const char *p2_face_examples_dir = NULL;

static const char *track_seq_path = NULL;
static char *track_prep_frame_path = NULL;

static const char* path_to_trk_model = NULL;
static const char* path_to_rec_model = NULL;

static bool is_eye_condition_cb_called = false;
static bool is_facial_expression_cb_called = false;
static bool is_face_detected_cb_called = false;

static char* pInternalStoragePath = NULL;
static char* pInternalDataPath = NULL;

static bool check_model_files(
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

    ret2 = mv_source_fill_by_buffer(source, data_buffer, (unsigned long long)buffer_size,
                                   (unsigned int)width, (unsigned int)height, source_colorspace);

_LOAD_IMAGE_FAIL:
    image_util_decode_destroy(_decoder);
    if(data_buffer)
        free(data_buffer);

    assert_eq(IMAGE_UTIL_ERROR_NONE, ret1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret2);
    return MEDIA_VISION_ERROR_NONE;
}

static int init_examples_by_dir(
        const char *dir,
        unsigned int ex_n,
        mv_source_h **out_examples)
{
    int err = MEDIA_VISION_ERROR_NONE;

    *out_examples = (mv_source_h*)malloc(ex_n * sizeof(mv_source_h));
    if(*out_examples == NULL) {
        printf("Error occured in memory allocation to *out_examples\n");
        return MEDIA_VISION_ERROR_OUT_OF_MEMORY;
    }

    char image_path[FILE_PATH_SIZE] = "";

    unsigned int img_ind = 0;
    for (img_ind = 0; img_ind < ex_n; ++img_ind)
    {
        snprintf(image_path, FILE_PATH_SIZE, "%s/%02u.jpg", dir, img_ind);
        err = mv_create_source(&((*out_examples)[img_ind]));
        if (MEDIA_VISION_ERROR_NONE != err)
        {
            printf("Can't create source to load image [%s].\n", image_path);
            return err;
        }
        err = load_image_to_media_source(image_path, (*out_examples)[img_ind]);
        if (MEDIA_VISION_ERROR_NONE != err)
        {
            printf("Can't load image [%s] to the source.\n", image_path);
            return err;
        }
    }

    return err;
}
static int free_examples_set(mv_source_h *out_examples, unsigned int ex_n)
{
    int err = out_examples ? MEDIA_VISION_ERROR_NONE : MEDIA_VISION_ERROR_NO_DATA;

    if (MEDIA_VISION_ERROR_NONE != err)
    {
        printf("Can't free examples set, array pointer is NULL.\n");
        return err;
    }

    unsigned int img_ind = 0;
    for (img_ind = 0; img_ind < ex_n; ++img_ind)
    {
        err = mv_destroy_source(out_examples[img_ind]);
        if (MEDIA_VISION_ERROR_NONE != err)
        {
            printf("Failed to destroy example %u from examples set.\n", img_ind);
            return err;
        }
    }

    free(out_examples);

    return err;
}
/**
 * @function	utc_capi_media_vision_face_startup
 * @description	Face module UTC startup code
 * @parameter	NA
 * @return		NA
 */
void utc_capi_media_vision_face_startup(void)
{
    printf("capi-media-vision mv_face tests STARTUP is launched\n");

    bool isFaceRecognitionSupported = false;

    system_info_get_platform_bool("http://tizen.org/feature/vision.face_recognition", &isFaceRecognitionSupported);

    if (isFaceRecognitionSupported)
        isVisionSupported = true;
    else
        isVisionSupported = false;

    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    if (true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE)) {
        PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received %s\\n", __LINE__, API_NAMESPACE, pszValue);

        pInternalStoragePath = (char*)calloc(strlen(pszValue)+5, sizeof(char));
        snprintf(pInternalStoragePath, strlen(pszValue)+5, "%s/res", pszValue);

        pInternalDataPath = (char*)calloc(strlen(pszValue)+strlen("/data")+1, sizeof(char));
        snprintf(pInternalDataPath, strlen(pszValue)+strlen("/data")+1, "%s/data", pszValue);

        p1_face_examples_dir=(char*)calloc(strlen(pszValue)+strlen("/res/res/rec/P1")+1, sizeof(char));
        snprintf(p1_face_examples_dir, strlen(pszValue)+strlen("/res/res/rec/P1")+1, "%s/res/res/rec/P1", pszValue);

        p2_face_examples_dir=(char*)calloc(strlen(pszValue)+strlen("/res/res/rec/P2")+1, sizeof(char));
        snprintf(p2_face_examples_dir, strlen(pszValue)+strlen("/res/res/rec/P2")+1, "%s/res/res/rec/P2", pszValue);

        track_seq_path=(char*)calloc(strlen(pszValue)+strlen("/res/res/track/sequence")+1, sizeof(char));
        snprintf(track_seq_path, strlen(pszValue)+strlen("/res/res/track/sequence")+1, "%s/res/res/track/sequence", pszValue);

        track_prep_frame_path=(char*)calloc(strlen(pszValue)+strlen("/res/res/track/sequence/1.jpg")+1, sizeof(char));
        snprintf(track_prep_frame_path, strlen(pszValue)+strlen("/res/res/track/sequence/1.jpg")+1, "%s/res/res/track/sequence/1.jpg", pszValue);

        path_to_trk_model=(char*)calloc(strlen(pszValue)+strlen("/res/res/model/test_trk_model")+1, sizeof(char));
        snprintf(path_to_trk_model, strlen(pszValue)+strlen("/res/res/model/test_trk_model")+1, "%s/res/res/model/test_trk_model", pszValue);

        path_to_rec_model=(char*)calloc(strlen(pszValue)+strlen("/res/res/model/test_rec_model")+1, sizeof(char));
        snprintf(path_to_rec_model, strlen(pszValue)+strlen("/res/res/model/test_rec_model")+1, "%s/res/res/model/test_rec_model", pszValue);
    } else {
        PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
    }
    printf("capi-media-vision mv_face tests STARTUP is completed\n");
}

/**
 * @function	utc_capi_media_vision_face_cleanup
 * @description	Face module UTC cleanup code
 * @parameter	NA
 * @return		NA
 */
void utc_capi_media_vision_face_cleanup(void)
{
    	printf("capi-media-vision mv_face tests CLEANUP is launched\n");
	if (pInternalStoragePath) {
		free(pInternalStoragePath);
		pInternalStoragePath = NULL;
	}

	if (pInternalDataPath) {
		free(pInternalDataPath);
		pInternalDataPath = NULL;
	}

	if (p1_face_examples_dir) {
		free(p1_face_examples_dir);
		p1_face_examples_dir = NULL;
	}

	if (p2_face_examples_dir) {
		free(p2_face_examples_dir);
		p2_face_examples_dir = NULL;
	}

	if (track_seq_path) {
		free(track_seq_path);
		track_seq_path = NULL;
	}

	if (track_prep_frame_path) {
		free(track_prep_frame_path);
		track_prep_frame_path = NULL;
	}

	if (path_to_trk_model) {
		free(path_to_trk_model);
		path_to_trk_model = NULL;
	}

	if (path_to_rec_model) {
		free(path_to_rec_model);
		path_to_rec_model = NULL;
	}	

    	printf("capi-media-vision mv_face tests CLEANUP is completed\n");
}

static bool lost_flag = false;

void track_cb(
        mv_source_h source,
        mv_face_tracking_model_h tracking_model,
        mv_engine_config_h engine_cfg,
        mv_quadrangle_s *location,
        double confidence,
        void *user_data)
{
    if (NULL != user_data)
    {
        bool *is_called = (bool*)user_data;
        *is_called = true;
    }
    else
    {
        return;
    }

    if (NULL != location)
    {
        printf("Face tracked to the location bounded by "
               "(%i, %i)-(%i, %i)-(%i, %i)-(%i, %i); confidence: %f\n",
               location->points[0].x, location->points[0].y,
               location->points[1].x, location->points[1].y,
               location->points[2].x, location->points[2].y,
               location->points[3].x, location->points[3].y,
               confidence);
    }
    else if (!lost_flag)
    {
        printf("Tracker has lost the face\n");
        lost_flag = true;
    }
}

/**
 * @brief Positive test case of mv_face_tracking_model_create()
 * @testcase        utc_mediavision_mv_face_tracking_model_create_p
 * @since_tizen     3.0
 * @description     Create face tracking model handle
 */
int utc_mediavision_mv_face_tracking_model_create_p(void)
{
    printf("Inside mv_face_tracking_model_create_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_face_tracking_model_h test_tracking_model = NULL;
    int ret = mv_face_tracking_model_create(&test_tracking_model);
    assert_neq(NULL, test_tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_tracking_model_destroy(test_tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_tracking_model_create_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_tracking_model_create()
 * @testcase        utc_mediavision_mv_face_tracking_model_create_n
 * @since_tizen     3.0
 * @description     Create face tracking model handle,
 *                  but fail because input handle is NULL
 */
int utc_mediavision_mv_face_tracking_model_create_n(void)
{
    printf("Inside mv_face_tracking_model_create_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_face_tracking_model_create(NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_face_tracking_model_create_n\n");

    return 0;
}


/**
 * @brief Positive test case of mv_face_tracking_model_destroy()
 * @testcase        utc_mediavision_mv_face_tracking_model_destroy_p
 * @since_tizen     3.0
 * @description     Destroy face tracking model handle
 */
int utc_mediavision_mv_face_tracking_model_destroy_p(void)
{
    printf("Inside mv_face_tracking_model_destroy_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_face_tracking_model_h tracking_model = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE, mv_face_tracking_model_create(&tracking_model));
    const int ret = mv_face_tracking_model_destroy(tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    tracking_model = NULL;

    printf("Before return mv_face_tracking_model_destroy_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_tracking_model_destroy()
 * @testcase        utc_mediavision_mv_face_tracking_model_destroy_n
 * @since_tizen     3.0
 * @description     Destroy face tracking model handle,
 *                  but fail because input handle is NULL
 */
int utc_mediavision_mv_face_tracking_model_destroy_n(void)
{
    printf("Inside mv_face_tracking_model_destroy_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_face_tracking_model_destroy(NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_face_tracking_model_destroy_n\n");

    return 0;
}


/**
 * @brief Positive test case of mv_face_tracking_model_prepare()
 * @testcase        utc_mediavision_mv_face_tracking_model_prepare_p
 * @since_tizen     3.0
 * @description     Prepare face tracking model
 */
int utc_mediavision_mv_face_tracking_model_prepare_p(void)
{
    printf("Inside mv_face_tracking_model_prepare_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h source = NULL;
    int ret = mv_create_source(&source);
    assert_neq(NULL, source);

    ret = load_image_to_media_source(track_prep_frame_path, source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_face_tracking_model_h tracking_model = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE, mv_face_tracking_model_create(&tracking_model));

    mv_quadrangle_s roi;
    roi.points[0].x = 440;
    roi.points[0].y = 130;
    roi.points[1].x = 530;
    roi.points[1].y = 130;
    roi.points[2].x = 530;
    roi.points[2].y = 240;
    roi.points[3].x = 440;
    roi.points[3].y = 240;

    ret = mv_face_tracking_model_prepare(tracking_model, NULL, source, &roi);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(MEDIA_VISION_ERROR_NONE, mv_face_tracking_model_destroy(tracking_model));

    ret = mv_destroy_source(source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_tracking_model_prepare_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_tracking_model_prepare()
 * @testcase        utc_mediavision_mv_face_tracking_model_prepare_n
 * @since_tizen     3.0
 * @description     Prepare face tracking model,
 *                  but fail because input parameters are invalid
 */
int utc_mediavision_mv_face_tracking_model_prepare_n(void)
{
    printf("Inside mv_face_tracking_model_prepare_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h source = NULL;
    int ret = mv_create_source(&source);
    assert_neq(NULL, source);

    mv_quadrangle_s roi;
    roi.points[0].x = 440;
    roi.points[0].y = 130;
    roi.points[1].x = 530;
    roi.points[1].y = 130;
    roi.points[2].x = 530;
    roi.points[2].y = 240;
    roi.points[3].x = 440;
    roi.points[3].y = 240;

    mv_face_tracking_model_h tracking_model = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE, mv_face_tracking_model_create(&tracking_model));

    ret = mv_face_tracking_model_prepare(tracking_model, NULL, source, &roi);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = load_image_to_media_source(track_prep_frame_path, source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_tracking_model_prepare(NULL, NULL, source, &roi);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_face_tracking_model_prepare(tracking_model, NULL, NULL, &roi);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    roi.points[0].x = -1; // negative roi coordinate

    ret = mv_face_tracking_model_prepare(tracking_model, NULL, source, &roi);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_source_get_width(source, &(roi.points[0].x));
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    roi.points[0].x += 1; // out of image roi coordinate

    ret = mv_face_tracking_model_prepare(tracking_model, NULL, source, &roi);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);
    assert_eq(MEDIA_VISION_ERROR_NONE, mv_face_tracking_model_destroy(tracking_model));

    ret = mv_destroy_source(source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_tracking_model_prepare_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_face_tracking_model_clone()
 * @testcase        utc_mediavision_mv_face_tracking_model_clone_p
 * @since_tizen     3.0
 * @description     Clone face tracking model
 */
int utc_mediavision_mv_face_tracking_model_clone_p(void)
{
    printf("Inside mv_face_tracking_model_clone_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_face_tracking_model_h source_model = NULL;
    int ret = mv_face_tracking_model_create(&source_model);
    assert_neq(NULL, source_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_face_tracking_model_h dest_model = NULL;

    ret = mv_face_tracking_model_clone(source_model, &dest_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    // Check whether source_model and dest_model equal or not
    char path_to_save_src[FILE_PATH_SIZE] = "";
    snprintf(path_to_save_src, FILE_PATH_SIZE, "%s/test_src_model", pInternalDataPath);
    ret = mv_face_tracking_model_save(path_to_save_src, source_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    char path_to_save_dst[FILE_PATH_SIZE] = "";
    snprintf(path_to_save_dst, FILE_PATH_SIZE, "%s/test_dst_model", pInternalDataPath);
    ret = mv_face_tracking_model_save(path_to_save_dst, dest_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    bool compare_models = check_model_files(path_to_save_src, path_to_save_dst);
    assert_eq(true, compare_models);

    ret = mv_face_tracking_model_destroy(source_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_tracking_model_destroy(dest_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_tracking_model_clone_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_tracking_model_clone()
 * @testcase        utc_mediavision_mv_face_tracking_model_clone_n
 * @since_tizen     3.0
 * @description     Clone face tracking model,
 *                  but fail because of input parameters are NULL
 */
int utc_mediavision_mv_face_tracking_model_clone_n(void)
{
    printf("Inside mv_face_tracking_model_clone_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_face_tracking_model_h tracking_model = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE, mv_face_tracking_model_create(&tracking_model));

    int ret = mv_face_tracking_model_clone(tracking_model, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_face_tracking_model_clone(NULL, tracking_model);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);
    assert_eq(MEDIA_VISION_ERROR_NONE, mv_face_tracking_model_destroy(tracking_model));

    printf("Before return mv_face_tracking_model_clone_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_face_tracking_model_save()
 * @testcase        utc_mediavision_mv_face_tracking_model_save_p
 * @since_tizen     3.0
 * @description     Save face tracking model
 */
int utc_mediavision_mv_face_tracking_model_save_p(void)
{
    printf("Inside mv_face_tracking_model_save_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    char modelDataPath [FILE_PATH_SIZE];
    snprintf(modelDataPath, strlen(pInternalDataPath) + strlen("/test_trk_model")+1, "%s/test_trk_model", pInternalDataPath);

    mv_face_tracking_model_h tracking_model = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE, mv_face_tracking_model_create(&tracking_model));

    int ret = mv_face_tracking_model_save(modelDataPath, tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_source_h source = NULL;
    ret = mv_create_source(&source);
    assert_neq(NULL, source);

    ret = load_image_to_media_source(track_prep_frame_path, source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_quadrangle_s roi;
    roi.points[0].x = 440;
    roi.points[0].y = 130;
    roi.points[1].x = 530;
    roi.points[1].y = 130;
    roi.points[2].x = 530;
    roi.points[2].y = 240;
    roi.points[3].x = 440;
    roi.points[3].y = 240;

    ret = mv_face_tracking_model_prepare(tracking_model, NULL, source, &roi);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_tracking_model_save(modelDataPath, tracking_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(MEDIA_VISION_ERROR_NONE, mv_face_tracking_model_destroy(tracking_model));

    ret = mv_destroy_source(source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_tracking_model_save_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_tracking_model_save()
 * @testcase        utc_mediavision_mv_face_tracking_model_save_n
 * @since_tizen     3.0
 * @description     Save face tracking model,
 *                  but fail because input parameter is NULL or
 *                  the path is invalid
 */
int utc_mediavision_mv_face_tracking_model_save_n(void)
{
    printf("Inside mv_face_tracking_model_save_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }
    mv_face_tracking_model_h tracking_model = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE, mv_face_tracking_model_create(&tracking_model));

    int ret = mv_face_tracking_model_save(path_to_trk_model, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_face_tracking_model_save(NULL, tracking_model);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PATH, ret);

    // unexisted file path:
    ret = mv_face_tracking_model_save(
              "/fake/path/test_trk_model",
              tracking_model);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PATH, ret);
    assert_eq(MEDIA_VISION_ERROR_NONE, mv_face_tracking_model_destroy(tracking_model));

    printf("Before return mv_face_tracking_model_save_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_face_tracking_model_load()
 * @testcase        utc_mediavision_mv_face_tracking_model_load_p
 * @since_tizen     3.0
 * @description     Load face tracking model,
 */
int utc_mediavision_mv_face_tracking_model_load_p(void)
{
    printf("Inside mv_face_tracking_model_load_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_face_tracking_model_h source_model = NULL;
    int ret = mv_face_tracking_model_load(path_to_trk_model, &source_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_tracking_model_destroy(source_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    source_model = NULL;

    printf("Before return mv_face_tracking_model_load_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_tracking_model_load()
 * @testcase        utc_mediavision_mv_face_tracking_model_load_n
 * @since_tizen     3.0
 * @description     Load face tracking model,
 *                  but fail because input parameter is NULL
 *                  or the path is invalid
 */
int utc_mediavision_mv_face_tracking_model_load_n(void)
{
    printf("Inside mv_face_tracking_model_load_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    int ret = mv_face_tracking_model_load(path_to_trk_model, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    mv_face_tracking_model_h source_model = NULL;
    ret = mv_face_tracking_model_load(NULL, &source_model);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PATH, ret);

    // unexisted file path:
    ret = mv_face_tracking_model_load(
              "/fake/path/test_trk_model",
              &source_model);

    if (source_model) {
        int ret2 = mv_face_tracking_model_destroy(source_model);
        assert_eq(MEDIA_VISION_ERROR_NONE, ret2);
    }

    assert_eq(MEDIA_VISION_ERROR_INVALID_PATH, ret);

    printf("Before return mv_face_tracking_model_load_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_face_track()
 * @testcase        utc_mediavision_mv_face_track_p
 * @since_tizen     3.0
 * @description     Track face and invoke callback providing tracking results
 */
int utc_mediavision_mv_face_track_p(void)
{
    printf("Inside mv_face_track_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h source = NULL;
    int ret = mv_create_source(&source);
    assert_neq(NULL, source);

    ret = load_image_to_media_source(track_prep_frame_path, source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_face_tracking_model_h tracking_model = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE, mv_face_tracking_model_create(&tracking_model));

    mv_quadrangle_s roi;
    roi.points[0].x = 440;
    roi.points[0].y = 130;
    roi.points[1].x = 530;
    roi.points[1].y = 130;
    roi.points[2].x = 530;
    roi.points[2].y = 240;
    roi.points[3].x = 440;
    roi.points[3].y = 240;

    assert_eq(MEDIA_VISION_ERROR_NONE, mv_face_tracking_model_prepare(tracking_model, NULL, source, &roi));

    assert_eq(MEDIA_VISION_ERROR_NONE, mv_source_clear(source));

    int retTmp = MEDIA_VISION_ERROR_NONE;
    int frames_counter = 1;
    char frame[FILE_PATH_SIZE];
    bool is_called = false;
    for (; frames_counter <= 20; ++frames_counter)
    {
        memset(frame, 0, FILE_PATH_SIZE);
        snprintf(frame, FILE_PATH_SIZE, "%s/%d.jpg", track_seq_path, frames_counter);

        if (frames_counter < 2)
            continue;

        printf("Frame Path: %s\n",  frame);
        ret = load_image_to_media_source(frame, source);
        if (ret != MEDIA_VISION_ERROR_NONE) {
            printf("Error occured in load_image_to_media_source()\n");
            break;
        }

        is_called = false;
        ret = mv_face_track(
                  source, tracking_model, NULL, track_cb, true, &is_called);
        if (ret != MEDIA_VISION_ERROR_NONE || is_called == false) {
            printf("Error occured in mv_face_track()\n");
            break;
        }
    }

    assert_eq(MEDIA_VISION_ERROR_NONE, mv_destroy_source(source));
    assert_eq(MEDIA_VISION_ERROR_NONE, mv_face_tracking_model_destroy(tracking_model));
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(true, is_called);

    printf("Before return mv_face_track_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_track()
 * @testcase        utc_mediavision_mv_face_track_n
 * @since_tizen     3.0
 * @description     Track face and invoke callback providing tracking results,
 *                  but fail because input parameters are NULL or
 *                  callback is NULL
 */
int utc_mediavision_mv_face_track_n(void)
{
    printf("Inside mv_face_track_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h source = NULL;
    int ret = mv_create_source(&source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_neq(NULL, source);

    mv_face_tracking_model_h tracking_model = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE, mv_face_tracking_model_create(&tracking_model));

    ret = mv_face_track(source, tracking_model, NULL, track_cb, true, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = load_image_to_media_source(track_prep_frame_path, source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_track(NULL, tracking_model, NULL, track_cb, true, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_face_track(source, NULL, NULL, track_cb, true, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_face_track(source, tracking_model, NULL, NULL, true, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);
    assert_eq(MEDIA_VISION_ERROR_NONE, mv_face_tracking_model_destroy(tracking_model));

    ret = mv_destroy_source(source);
    source = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_track_n\n");

    return 0;
}

void face_recognized_cb(
        mv_source_h source,
        mv_face_recognition_model_h recognition_model,
        mv_engine_config_h engine_cfg,
        mv_rectangle_s *face_location,
        const int *face_label,
        double confidence,
        void *user_data)
{
    if (NULL != user_data)
    {
        bool *is_called = (bool*)user_data;
        *is_called = true;
    }

    if (face_location)
    {
        printf("Face has been recognized as face [%i] with confidence %.2f\n", *face_label, confidence);
    }
    else
    {
        printf("Face wasn't recognized\n");
    }
}

/**
 * @brief Positive test case of mv_face_recognize()
 * @testcase        utc_mediavision_mv_face_recognize_p
 * @since_tizen     3.0
 * @description     Recognize face and invoke callback providing recognition results
 */
int utc_mediavision_mv_face_recognize_p(void)
{
    printf("Inside mv_face_recognize_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_face_recognition_model_h recognition_model = NULL;

    int ret = mv_face_recognition_model_load(
                  path_to_rec_model,
                  &recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_source_h source = NULL;
    ret = mv_create_source(&source);
    assert_neq(NULL, source);

    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/rec/P1/09.jpg")+1, "%s/res/rec/P1/09.jpg", pInternalStoragePath);
    ret = load_image_to_media_source(pszValue, source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    bool is_called = false;
    ret = mv_face_recognize(source, recognition_model, NULL, NULL, face_recognized_cb, &is_called);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(true, is_called);

    ret = mv_destroy_source(source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_recognition_model_destroy(recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_recognize_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_recognize()
 * @testcase        utc_mediavision_mv_face_recognize_n
 * @since_tizen     3.0
 * @description     Recognize face and invoke callback providing recognition results,
 *                  but fail because input parameters are invalid
 */
int utc_mediavision_mv_face_recognize_n(void)
{
    printf("Inside mv_face_recognize_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_face_recognition_model_h recognition_model = NULL;

    int ret = mv_face_recognition_model_load(
                  path_to_rec_model,
                  &recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_source_h source = NULL;
    ret = mv_create_source(&source);
    assert_neq(NULL, source);

    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/rec/P1/09.jpg")+1, "%s/res/rec/P1/09.jpg", pInternalStoragePath);
    ret = load_image_to_media_source(pszValue,source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    // empty source:
    ret = mv_face_recognize(
                  NULL,
                  recognition_model,
                  NULL,
                  NULL,
                  face_recognized_cb,
                  NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    // empty model:
    ret = mv_face_recognize(
                  source,
                  NULL,
                  NULL,
                  NULL,
                  face_recognized_cb,
                  NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    // empty callback:
    ret = mv_face_recognize(
                  source,
                  recognition_model,
                  NULL,
                  NULL,
                  NULL,
                  NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    // incorrect rois:
    mv_rectangle_s bad_roi1;
    bad_roi1.point.x = -5;
    bad_roi1.point.y = -5;
    bad_roi1.width = 100;
    bad_roi1.height = 100;

    mv_rectangle_s bad_roi2;
    bad_roi2.point.x = 0;
    bad_roi2.point.y = 0;
    bad_roi2.width = 0;
    bad_roi2.height = 0;
    assert_eq(MEDIA_VISION_ERROR_NONE,
            mv_source_get_width(source, &(bad_roi2.width)));
    assert_eq(MEDIA_VISION_ERROR_NONE,
            mv_source_get_height(source, &(bad_roi2.height)));

    bad_roi2.width += 1;
    bad_roi2.height += 1;

    ret = mv_face_recognize(
                  source,
                  recognition_model,
                  NULL,
                  &bad_roi1,
                  face_recognized_cb,
                  NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_face_recognize(
                  source,
                  recognition_model,
                  NULL,
                  &bad_roi2,
                  face_recognized_cb,
                  NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    // everything is empty:
    ret = mv_face_recognize(NULL, NULL, NULL, NULL, NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_destroy_source(source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_recognition_model_destroy(recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_recognize_n\n");

    return 0;
}

void eye_condition_cb(
        mv_source_h source,
        mv_engine_config_h engine_cfg,
        mv_rectangle_s face_location,
        mv_face_eye_condition_e eye_condition,
        void *user_data)
{
    mv_face_eye_condition_e *expected = (mv_face_eye_condition_e*) user_data;

    is_eye_condition_cb_called = true;

    switch (eye_condition)
    {
        case MV_FACE_EYES_NOT_FOUND:
            printf("Eyes not found -> ");
            *expected == eye_condition ? printf("Passed\n") : printf("Failed\n");
            break;
        case MV_FACE_EYES_OPEN:
            printf("Eyes are open -> ");
            *expected == eye_condition ? printf("Passed\n") : printf("Failed\n");
            break;
        case MV_FACE_EYES_CLOSED:
            printf("Eyes are closed -> ");
            *expected == eye_condition ? printf("Passed\n") : printf("Failed\n");
            break;
    }
}

/**
 * @brief Positive test case of mv_face_eye_condition_recognize()
 * @testcase        utc_mediavision_mv_face_eye_condition_recognize_p
 * @since_tizen     3.0
 * @description     Recognize eye condition and invoke callback providing results
 */
int utc_mediavision_mv_face_eye_condition_recognize_p(void)
{
    printf("Inside mv_face_eye_condition_recognition_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_rectangle_s location;
    mv_face_eye_condition_e eye_condition;

    mv_source_h source1 = NULL;
    int ret = mv_create_source(&source1);
    assert_neq(NULL, source1);

    mv_source_h source2 = NULL;
    ret = mv_create_source(&source2);
    assert_neq(NULL, source2);

    mv_source_h source3 = NULL;
    ret = mv_create_source(&source3);
    assert_neq(NULL, source3);

    mv_source_h source4 = NULL;
    ret = mv_create_source(&source4);
    assert_neq(NULL, source4);

    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/eye/01.jpg")+1, "%s/res/eye/01.jpg", pInternalStoragePath);
    ret = load_image_to_media_source(pszValue, source1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    memset(pszValue, 0, CONFIG_VALUE_LEN_MAX);
    snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/eye/02.jpg")+1, "%s/res/eye/02.jpg", pInternalStoragePath);
    ret = load_image_to_media_source(pszValue, source2);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    memset(pszValue, 0, CONFIG_VALUE_LEN_MAX);
    snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/eye/03.jpg")+1, "%s/res/eye/03.jpg", pInternalStoragePath);
    ret = load_image_to_media_source(pszValue, source3);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    memset(pszValue, 0, CONFIG_VALUE_LEN_MAX);
    snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/eye/04.jpg")+1, "%s/res/eye/04.jpg", pInternalStoragePath);
    ret = load_image_to_media_source(pszValue, source4);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    // open
    location.point.x = 177;
    location.point.y = 87;
    location.width = 157;
    location.height = 157;

    eye_condition = MV_FACE_EYES_OPEN;
    is_eye_condition_cb_called = false;

    ret = mv_face_eye_condition_recognize(
                source1,
                NULL,
                location,
                eye_condition_cb,
                &eye_condition);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(true, is_eye_condition_cb_called);

    // closed (left eye)
    location.point.x = 201;
    location.point.y = 72;
    location.width = 176;
    location.height = 176;

    eye_condition = MV_FACE_EYES_CLOSED;
    is_eye_condition_cb_called = false;

    ret = mv_face_eye_condition_recognize(
                source2,
                NULL,
                location,
                eye_condition_cb,
                &eye_condition);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(true, is_eye_condition_cb_called);

    // closed (right eye)
    location.point.x = 204;
    location.point.y = 117;
    location.width = 154;
    location.height = 154;

    eye_condition = MV_FACE_EYES_CLOSED;
    is_eye_condition_cb_called = false;

    ret = mv_face_eye_condition_recognize(
                source3,
                NULL,
                location,
                eye_condition_cb,
                &eye_condition);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(true, is_eye_condition_cb_called);

    // closed (both eyes)
    location.point.x = 196;
    location.point.y = 96;
    location.width = 171;
    location.height = 171;

    eye_condition = MV_FACE_EYES_CLOSED;
    is_eye_condition_cb_called = false;

    ret = mv_face_eye_condition_recognize(
                source4,
                NULL,
                location,
                eye_condition_cb,
                &eye_condition);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(true, is_eye_condition_cb_called);

    ret = mv_destroy_source(source1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_destroy_source(source2);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_destroy_source(source3);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_destroy_source(source4);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_eye_condition_recognize_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_eye_condition_recognize()
 * @testcase        utc_mediavision_mv_face_eye_condition_recognize_n
 * @since_tizen     3.0
 * @description     Recognize eye condition and invoke callback providing results,
 *                  But fail because input parameters are NULL
 */
int utc_mediavision_mv_face_eye_condition_recognize_n(void)
{
    printf("Inside mv_face_eye_condition_recognize_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_rectangle_s location;
    location.point.x = 0;
    location.point.y = 0;
    location.width = 0;
    location.height = 0;

    int ret = mv_face_eye_condition_recognize(NULL, NULL, location, NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    mv_source_h source = NULL;
    ret = mv_create_source(&source);
    assert_neq(NULL, source);

    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/eye/01.jpg")+1, "%s/res/eye/01.jpg", pInternalStoragePath);
    ret = load_image_to_media_source(pszValue, source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_eye_condition_recognize(
                source,
                NULL,
                location,
                eye_condition_cb,
                NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_destroy_source(source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_eye_condition_recognize_n\n");

    return 0;
}

void face_expression_cb(
        mv_source_h source,
        mv_engine_config_h engine_cfg,
        mv_rectangle_s face_location,
        mv_face_facial_expression_e facial_expression,
        void *user_data)
{
    mv_face_facial_expression_e *expected = (mv_face_facial_expression_e*) user_data;
    is_facial_expression_cb_called = true;

    switch (facial_expression)
    {
        case MV_FACE_UNKNOWN:
            printf("Facial expression not recognized -> ");
            break;
        case MV_FACE_NEUTRAL:
            printf("Facial expression is recognized as neutral -> ");
            break;
        case MV_FACE_SMILE:
            printf("Facial expression is recognized as smiling -> ");
            break;
    }

    *expected == facial_expression ? printf("Passed\n") : printf("Failed\n");
}

/**
 * @brief Positive test case of mv_face_facial_expression_recognize()
 * @testcase        utc_mediavision_mv_face_facial_expression_recognize_p
 * @since_tizen     3.0
 * @description     Recognize facial expression and invoke callback providing results
 */
int utc_mediavision_mv_face_facial_expression_recognize_p(void)
{
    printf("Inside mv_face_facial_expression_recognize_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_rectangle_s location;
    location.point.x = 0;
    location.point.y = 0;
    mv_face_facial_expression_e face_expression;

    mv_source_h source1 = NULL;
    int ret = mv_create_source(&source1);
    assert_neq(NULL, source1);

    mv_source_h source2 = NULL;
    ret = mv_create_source(&source2);
    assert_neq(NULL, source2);

    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/expr/neutral.jpg")+1, "%s/res/expr/neutral.jpg", pInternalStoragePath);
    ret = load_image_to_media_source(pszValue, source1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    memset(pszValue, 0, CONFIG_VALUE_LEN_MAX);
    snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/expr/smile.jpg")+1, "%s/res/expr/smile.jpg", pInternalStoragePath);
    ret = load_image_to_media_source(pszValue, source2);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    face_expression = MV_FACE_NEUTRAL;
	is_facial_expression_cb_called = false;

    ret = mv_source_get_width(
                source1,
                &(location.width));
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_source_get_height(
                source1,
                &(location.height));
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_facial_expression_recognize(
                source1,
                NULL,
                location,
                face_expression_cb,
                &face_expression);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(true, is_facial_expression_cb_called);

    face_expression = MV_FACE_SMILE;
    is_facial_expression_cb_called = false;

    ret = mv_source_get_width(
                source2,
                &(location.width));
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_source_get_height(
                source2,
                &(location.height));
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_facial_expression_recognize(
                source2,
                NULL,
                location,
                face_expression_cb,
                &face_expression);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(true, is_facial_expression_cb_called);

    face_expression = MV_FACE_UNKNOWN;
    is_facial_expression_cb_called = false;

    location.width = 1;
    location.height = 1;

    ret = mv_face_facial_expression_recognize(
                source1,
                NULL,
                location,
                face_expression_cb,
                &face_expression);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(true, is_facial_expression_cb_called);

    ret = mv_destroy_source(source1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_destroy_source(source2);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_facila_expression_recognize_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_facial_expression_recognize()
 * @testcase        utc_mediavision_mv_face_facial_expression_recognize_n
 * @since_tizen     3.0
 * @description     Recognize facial expression and invoke callback providing results,
 *                  but fail because input parameters are NULL
 */
int utc_mediavision_mv_face_facial_expression_recognize_n(void)
{
    printf("Inside mv_face_facial_expression_recognize_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_rectangle_s location;
    location.point.x = -1;
    location.point.y = -1;
    location.width = 0;
    location.height = 0;

    int ret = mv_face_facial_expression_recognize(NULL, NULL, location, NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    mv_source_h source = NULL;
    ret = mv_create_source(&source);
    assert_neq(NULL, source);

    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/expr/neutral.jpg")+1, "%s/res/expr/neutral.jpg", pInternalStoragePath);
    ret = load_image_to_media_source(pszValue, source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_facial_expression_recognize(
                source,
                NULL,
                location,
                face_expression_cb,
                NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_destroy_source(source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_facial_expression_recognize_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_face_recogniztion_model_create()
 * @testcase        utc_mediavision_mv_face_recognition_model_create_p
 * @since_tizen     3.0
 * @description     Create face recognition model
 */
int utc_mediavision_mv_face_recognition_model_create_p(void)
{
    printf("Inside mv_face_recognition_model_create_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_face_recognition_model_h recognition_model = NULL;
    const int ret = mv_face_recognition_model_create(&recognition_model);
    assert_neq(NULL, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_recognition_model_create_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_recognition_model_create()
 * @testcase        utc_mediavision_mv_face_recognition_model_create_n
 * @since_tizen     3.0
 * @description     Create face recognition model,
 *                  but fail because input parameter is NULL
 */
int utc_mediavision_mv_face_recognition_model_create_n(void)
{
    printf("Inside mv_face_recognition_model_create_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_face_recognition_model_create(NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_face_recognition_model_create_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_face_recognition_model_destroy()
 * @testcase        utc_mediavision_mv_face_recognition_model_destroy_p
 * @since_tizen     3.0
 * @description     Destroy face recognition model
 */
int utc_mediavision_mv_face_recognition_model_destroy_p(void)
{
    printf("Inside mv_face_recognition_model_destroy_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_face_recognition_model_h recognition_model = NULL;
    int ret = mv_face_recognition_model_create(&recognition_model);
    assert_neq(NULL, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_recognition_model_destroy(recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_recognition_model_destroy_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_recognition_model_destroy()
 * @testcase        utc_mediavision_mv_face_recognition_model_destroy_n
 * @since_tizen     3.0
 * @description     Destroy face recognition model,
 *                  but fail input parameter is NULL
 */
int utc_mediavision_mv_face_recognition_model_destroy_n(void)
{
    printf("Inside mv_face_recognition_model_destroy_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_face_recognition_model_destroy(NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_face_recognition_model_destroy_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_face_recognition_model_clone()
 * @testcase        utc_mediavision_mv_face_recognition_model_clone_p
 * @since_tizen     3.0
 * @description     Clone face recognition model
 */
int utc_mediavision_mv_face_recognition_model_clone_p(void)
{
    printf("Inside mv_face_recognition_model_clone_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_face_recognition_model_h source_model = NULL;
    int ret = mv_face_recognition_model_create(&source_model);
    assert_neq(NULL, source_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_source_h *p1_face_examples = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE,
                init_examples_by_dir(p1_face_examples_dir, p1_face_examples_n, &p1_face_examples));

    ret = mv_face_recognition_model_add(
                      p1_face_examples[0], source_model, NULL, 1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    // Learn for the collected face examples:
    ret = mv_face_recognition_model_learn(NULL, source_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_face_recognition_model_h dest_model = NULL;

    ret = mv_face_recognition_model_clone(source_model, &dest_model);
    assert_neq(NULL, dest_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    // Check whether source_model and dest_model equal or not
    char path_to_save_src[FILE_PATH_SIZE] = "";
    snprintf(path_to_save_src, FILE_PATH_SIZE, "%s/test_rec_src_model", pInternalDataPath);
    ret = mv_face_recognition_model_save(path_to_save_src, source_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    char path_to_save_dst[FILE_PATH_SIZE] = "";
    snprintf(path_to_save_dst, FILE_PATH_SIZE, "%s/test_rec_dst_model", pInternalDataPath);
    ret = mv_face_recognition_model_save(path_to_save_dst, dest_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    bool compare_models = check_model_files(path_to_save_src, path_to_save_dst);
    assert_eq(true, compare_models);

    ret = mv_face_recognition_model_destroy(source_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_recognition_model_destroy(dest_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    assert_eq(MEDIA_VISION_ERROR_NONE, free_examples_set(p1_face_examples, p1_face_examples_n));

    printf("Before return mv_face_recognition_model_clone_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_recognition_model_clone()
 * @testcase        utc_mediavision_mv_face_recognition_model_clone_n
 * @since_tizen     3.0
 * @description     Clone face recognition model,
 *                  but fail because input parameter are NULL
 */
int utc_mediavision_mv_face_recognition_model_clone_n(void)
{
    printf("Inside mv_face_recognition_model_clone_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_face_recognition_model_h recognition_model = NULL;
    int ret = mv_face_recognition_model_create(&recognition_model);
    assert_neq(NULL, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_recognition_model_clone(recognition_model, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_face_recognition_model_clone(NULL, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_face_recognition_model_clone(NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_face_recognition_model_destroy(recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_recognition_model_clone_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_face_recognition_model_save()
 * @testcase        utc_mediavision_mv_face_recognition_model_save_p
 * @since_tizen     3.0
 * @description     Save face recognition model
 */
int utc_mediavision_mv_face_recognition_model_save_p(void)
{
    printf("Inside mv_face_recognition_model_save_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_face_recognition_model_h recognition_model = NULL;
    int ret = mv_face_recognition_model_create(&recognition_model);
    assert_neq(NULL, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_source_h source1 = NULL;
    ret = mv_create_source(&source1);
    assert_neq(NULL, source1);

    char modelDataPath [FILE_PATH_SIZE];
    snprintf(modelDataPath, strlen(pInternalDataPath) + strlen("/test_rec_model")+1, "%s/test_rec_model", pInternalDataPath);

    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/rec/P1/09.jpg")+1, "%s/res/rec/P1/09.jpg", pInternalStoragePath);
    ret = load_image_to_media_source(pszValue,
                                     source1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_source_h source2 = NULL;
    ret = mv_create_source(&source2);
    assert_neq(NULL, source2);
    memset(pszValue, 0, CONFIG_VALUE_LEN_MAX);
    snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/rec/P2/00.jpg")+1, "%s/res/rec/P2/00.jpg", pInternalStoragePath);
    ret = load_image_to_media_source(pszValue,
                                     source2);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_recognition_model_add(source1, recognition_model, NULL, 1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_recognition_model_add(source2, recognition_model, NULL, 2);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_recognition_model_learn(NULL, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_destroy_source(source1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_destroy_source(source2);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_recognition_model_save(modelDataPath, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_recognition_model_destroy(recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_recognition_model_save_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_recognition_model_save()
 * @testcase        utc_mediavision_mv_face_recognition_model_save_n
 * @since_tizen     3.0
 * @description     Save face recognition model,
 *                  but fail because input parameter is NULL or
 *                  the path is invalid
 */
int utc_mediavision_mv_face_recognition_model_save_n(void)
{
    printf("Inside mv_face_recognition_model_save_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_face_recognition_model_h recognition_model = NULL;
    int ret = mv_face_recognition_model_create(&recognition_model);
    assert_neq(NULL, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    // Save before mv_face_recognition_model_learn call is forbidden:
    ret = mv_face_recognition_model_save(path_to_rec_model, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_INVALID_OPERATION, ret);

    ret = mv_face_recognition_model_save(NULL, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PATH, ret);

    ret = mv_face_recognition_model_save(NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_face_recognition_model_destroy(recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_recognition_model_save_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_face_recognition_model_load()
 * @testcase        utc_mediavision_mv_face_recognition_model_load_p
 * @since_tizen     3.0
 * @description     Load face recognition model
 */
int utc_mediavision_mv_face_recognition_model_load_p(void)
{
    printf("Inside mv_face_recognition_model_load_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_face_recognition_model_h recognition_model = NULL;

    int ret = mv_face_recognition_model_load(
            path_to_rec_model, &recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_recognition_model_destroy(recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_recognition_model_load_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_recognition_model_load()
 * @testcase        utc_mediavision_mv_face_recognition_model_load_n
 * @since_tizen     3.0
 * @description     Load face recognition model,
 *                  but fail because input parameter is NULL or
 *                  the path is invalid
 */
int utc_mediavision_mv_face_recognition_model_load_n(void)
{
    printf("Inside mv_face_recognition_model_load_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_face_recognition_model_h recognition_model = NULL;

    // Not existed file
    int ret = mv_face_recognition_model_load(
            "/fake/path/test_rec_model", &recognition_model);
    assert_eq(ret, MEDIA_VISION_ERROR_INVALID_PATH);

    ret = mv_face_recognition_model_load(NULL, &recognition_model);
    assert_eq(ret, MEDIA_VISION_ERROR_INVALID_PATH);

    ret = mv_face_recognition_model_load(NULL, NULL);
    assert_eq(ret, MEDIA_VISION_ERROR_INVALID_PARAMETER);

    ret = mv_face_recognition_model_destroy(recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_recognition_model_load_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_face_recognition_model_add()
 * @testcase        utc_mediavision_mv_face_recognition_model_add_p
 * @since_tizen     3.0
 * @description     Add face example to recognition model
 */
int utc_mediavision_mv_face_recognition_model_add_p(void)
{
    printf("Inside mv_face_recognition_model_add_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_face_recognition_model_h recognition_model = NULL;
    int ret = mv_face_recognition_model_create(&recognition_model);
    assert_neq(NULL, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_source_h source = NULL;
    ret = mv_create_source(&source);
    assert_neq(NULL, source);
    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/rec/P1/00.jpg")+1, "%s/res/rec/P1/00.jpg", pInternalStoragePath);
    ret = load_image_to_media_source(pszValue,
                                     source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_recognition_model_add(source, recognition_model, NULL, 1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_rectangle_s roi;
    roi.point.x = 0;
    roi.point.y = 0;
    roi.width = 0;
    roi.height = 0;
    assert_eq(MEDIA_VISION_ERROR_NONE,
            mv_source_get_width(source, &(roi.width)));
    assert_eq(MEDIA_VISION_ERROR_NONE,
            mv_source_get_height(source, &(roi.height)));

    ret = mv_face_recognition_model_add(source, recognition_model, &roi, 1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_destroy_source(source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_recognition_model_destroy(recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_recognition_model_face_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_recognition_model_add()
 * @testcase        utc_mediavision_mv_face_recognition_model_add_n
 * @since_tizen     3.0
 * @description     Add face example to recognition model,
 *                  but fail because input parameters are NULL
 */
int utc_mediavision_mv_face_recognition_model_add_n(void)
{
    printf("Inside mv_face_recognition_model_add_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_face_recognition_model_h recognition_model = NULL;
    int ret = mv_face_recognition_model_create(&recognition_model);
    assert_neq(NULL, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_source_h source = NULL;
    ret = mv_create_source(&source);
    assert_neq(NULL, source);
    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/rec/P1/00.jpg")+1, "%s/res/rec/P1/00.jpg", pInternalStoragePath);
    ret = load_image_to_media_source(pszValue,
                                     source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_recognition_model_add(source, NULL, NULL, 0);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_face_recognition_model_add(NULL, recognition_model,  NULL, 0);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_face_recognition_model_add(NULL, NULL, NULL, 0);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    mv_rectangle_s bad_roi1;
    bad_roi1.point.x = -5;
    bad_roi1.point.y = -5;
    bad_roi1.width = 100;
    bad_roi1.height = 100;

    mv_rectangle_s bad_roi2;
    bad_roi2.point.x = 0;
    bad_roi2.point.y = 0;
    bad_roi2.width = 0;
    bad_roi2.height = 0;

    mv_rectangle_s bad_roi3;
    bad_roi3.point.x = 0;
    bad_roi3.point.y = 0;
    assert_eq(MEDIA_VISION_ERROR_NONE,
            mv_source_get_width(source, &(bad_roi3.width)));
    assert_eq(MEDIA_VISION_ERROR_NONE,
            mv_source_get_height(source, &(bad_roi3.height)));

    bad_roi3.width += 1;
    bad_roi3.height += 1;

    ret = mv_face_recognition_model_add(source, recognition_model, &bad_roi1, 0);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_face_recognition_model_add(source, recognition_model, &bad_roi2, 0);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_face_recognition_model_add(source, recognition_model, &bad_roi3, 0);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_destroy_source(source);
    source = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_recognition_model_destroy(recognition_model);
    recognition_model = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_recognition_model_add_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_face_recognition_model_reset()
 * @testcase        utc_mediavision_mv_face_recognition_model_reset_p
 * @since_tizen     3.0
 * @description     Reset face example from recognition model
 */
int utc_mediavision_mv_face_recognition_model_reset_p(void)
{
    printf("Inside mv_face_recognition_model_reset_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h *p1_face_examples = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE,
                init_examples_by_dir(p1_face_examples_dir, p1_face_examples_n, &p1_face_examples));

    mv_source_h *p2_face_examples = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE,
                init_examples_by_dir(p2_face_examples_dir, p2_face_examples_n, &p2_face_examples));

    mv_face_recognition_model_h recognition_model = NULL;
    int ret = mv_face_recognition_model_create(&recognition_model);
    assert_neq(NULL, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    unsigned int ex_ind = 0;
    for (ex_ind = 0; ex_ind < p1_face_examples_n; ++ex_ind)
    {
        ret = mv_face_recognition_model_add(
                      p1_face_examples[ex_ind], recognition_model, NULL, 1);
        assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    }

    for (ex_ind = 0; ex_ind < p2_face_examples_n; ++ex_ind)
    {
        ret = mv_face_recognition_model_add(
                      p2_face_examples[ex_ind], recognition_model, NULL, 2);
        assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    }

    int reset_label = 1;
    // Reset only examples labeled 1:
    ret = mv_face_recognition_model_reset(recognition_model, &reset_label);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    // Reset all the rest examples:
    ret = mv_face_recognition_model_reset(recognition_model, NULL);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    assert_eq(MEDIA_VISION_ERROR_NONE,
              mv_face_recognition_model_destroy(recognition_model));

    assert_eq(MEDIA_VISION_ERROR_NONE, free_examples_set(p1_face_examples, p1_face_examples_n));
    assert_eq(MEDIA_VISION_ERROR_NONE, free_examples_set(p2_face_examples, p2_face_examples_n));

    printf("Before return mv_face_recognition_model_reset_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_recognition_model_reset()
 * @testcase        utc_mediavision_mv_face_recognition_model_reset_n
 * @since_tizen     3.0
 * @description     Reset face example from recognition model,
 *                  but fail because input parameter are NULL or
 *                  the face example doesn't exist
 */
int utc_mediavision_mv_face_recognition_model_reset_n(void)
{
    printf("Inside mv_face_recognition_model_reset_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h *p1_face_examples = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE,
                init_examples_by_dir(p1_face_examples_dir, p1_face_examples_n, &p1_face_examples));

    mv_source_h *p2_face_examples = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE,
                init_examples_by_dir(p2_face_examples_dir, p2_face_examples_n, &p2_face_examples));

    mv_face_recognition_model_h recognition_model = NULL;
    int ret = mv_face_recognition_model_create(&recognition_model);
    assert_neq(NULL, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    unsigned int ex_ind = 0;
    for (ex_ind = 0; ex_ind < p1_face_examples_n; ++ex_ind)
    {
        ret = mv_face_recognition_model_add(
                      p1_face_examples[ex_ind], recognition_model, NULL, 1);
        assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    }

    for (ex_ind = 0; ex_ind < p2_face_examples_n; ++ex_ind)
    {
        ret = mv_face_recognition_model_add(
                      p2_face_examples[ex_ind], recognition_model, NULL, 2);
        assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    }

    int reset_label = 3;
    // Reset examples for unexisted label 3:
    ret = mv_face_recognition_model_reset(recognition_model, &reset_label);
    assert_eq(MEDIA_VISION_ERROR_KEY_NOT_AVAILABLE, ret);

    // Reset all examples for unexisted model:
    ret = mv_face_recognition_model_reset(NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    reset_label = 1;
    // Reset examples labeled 1 for unexisted model:
    ret = mv_face_recognition_model_reset(NULL, &reset_label);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    assert_eq(MEDIA_VISION_ERROR_NONE,
              mv_face_recognition_model_destroy(recognition_model));

    assert_eq(MEDIA_VISION_ERROR_NONE, free_examples_set(p1_face_examples, p1_face_examples_n));
    assert_eq(MEDIA_VISION_ERROR_NONE, free_examples_set(p2_face_examples, p2_face_examples_n));

    printf("Before return mv_face_recognition_model_reset_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_face_recognition_model_learn()
 * @testcase        utc_mediavision_mv_face_recognition_model_learn_p
 * @since_tizen     3.0
 * @description     Learn recognition model
 */
int utc_mediavision_mv_face_recognition_model_learn_p(void)
{
    printf("Inside mv_face_recognition_model_learn_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h *p1_face_examples = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE,
                init_examples_by_dir(p1_face_examples_dir, p1_face_examples_n, &p1_face_examples));

    mv_source_h *p2_face_examples = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE,
                init_examples_by_dir(p2_face_examples_dir, p2_face_examples_n, &p2_face_examples));

    mv_face_recognition_model_h recognition_model = NULL;
    int ret = mv_face_recognition_model_create(&recognition_model);
    assert_neq(NULL, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    unsigned int ex_ind = 0;
    for (ex_ind = 0; ex_ind < p1_face_examples_n - 1; ++ex_ind)
    {
        ret = mv_face_recognition_model_add(
                      p1_face_examples[ex_ind], recognition_model, NULL, 1);
        assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    }

    for (ex_ind = 0; ex_ind < p2_face_examples_n - 1; ++ex_ind)
    {
        ret = mv_face_recognition_model_add(
                      p2_face_examples[ex_ind], recognition_model, NULL, 2);
        assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    }

    // Learn for the collected face examples:
    ret = mv_face_recognition_model_learn(NULL, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    // Recognize on the 1 example from both face classes,
    // just to see how processes learned model, without correctness check:
    mv_face_recognize(
            p1_face_examples[p1_face_examples_n - 1], recognition_model,
            NULL, NULL, face_recognized_cb, NULL);
    mv_face_recognize(
            p2_face_examples[p2_face_examples_n - 1], recognition_model,
            NULL, NULL, face_recognized_cb, NULL);

    assert_eq(MEDIA_VISION_ERROR_NONE,
              mv_face_recognition_model_destroy(recognition_model));

    assert_eq(MEDIA_VISION_ERROR_NONE, free_examples_set(p1_face_examples, p1_face_examples_n));
    assert_eq(MEDIA_VISION_ERROR_NONE, free_examples_set(p2_face_examples, p2_face_examples_n));

    printf("Before return mv_face_recognition_model_learn_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_recognition_model_learn()
 * @testcase        utc_mediavision_mv_face_recognition_model_learn_n
 * @since_tizen     3.0
 * @description     Learn recognition model,
 *                  but fail because input parameters are NULL or
 *                  the recognition model include no face and
 *                  thus there is nothing to be leanred
 */
int utc_mediavision_mv_face_recognition_model_learn_n(void)
{
    printf("Inside mv_face_recognition_model_learn_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    int ret = mv_face_recognition_model_learn(NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    mv_face_recognition_model_h recognition_model = NULL;
    ret = mv_face_recognition_model_create(&recognition_model);
    assert_neq(NULL, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    // Learn the model without added face examples doesn't allow recognition:
    ret = mv_face_recognition_model_learn(NULL, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NO_DATA, ret);

    assert_eq(MEDIA_VISION_ERROR_NONE,
            mv_face_recognition_model_destroy(recognition_model));

    printf("Before return mv_face_recognition_model_learn_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_face_recognition_model_query_labels()
 * @testcase        utc_mediavision_mv_face_recognition_model_query_labels_p
 * @since_tizen     3.0
 * @description     Query labels list and the number of labels
 */
int utc_mediavision_mv_face_recognition_model_query_labels_p(void)
{
    printf("Inside mv_face_recognition_model_query_labels_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h *p1_face_examples = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE,
                init_examples_by_dir(p1_face_examples_dir, p1_face_examples_n, &p1_face_examples));

    mv_source_h *p2_face_examples = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE,
                init_examples_by_dir(p2_face_examples_dir, p2_face_examples_n, &p2_face_examples));

    mv_face_recognition_model_h recognition_model = NULL;
    int ret = mv_face_recognition_model_create(&recognition_model);
    assert_neq(NULL, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    unsigned int ex_ind = 0;
    for (ex_ind = 0; ex_ind < p1_face_examples_n - 1; ++ex_ind)
    {
        ret = mv_face_recognition_model_add(
                      p1_face_examples[ex_ind], recognition_model, NULL, 1);
        assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    }

    for (ex_ind = 0; ex_ind < p2_face_examples_n - 1; ++ex_ind)
    {
        ret = mv_face_recognition_model_add(
                      p2_face_examples[ex_ind], recognition_model, NULL, 2);
        assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    }

    int *labels = NULL;
    unsigned int labels_n = 0;

    ret = mv_face_recognition_model_query_labels(recognition_model, &labels, &labels_n);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(0, labels_n);

    // Learn for the collected face examples:
    ret = mv_face_recognition_model_learn(NULL, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_recognition_model_query_labels(recognition_model, &labels, &labels_n);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(2, labels_n);
    assert((1 == labels[0] && 2 == labels[1]) || (2 == labels[0] && 1 == labels[1]));

    free(labels);

    assert_eq(MEDIA_VISION_ERROR_NONE,
            mv_face_recognition_model_destroy(recognition_model));

    assert_eq(MEDIA_VISION_ERROR_NONE, free_examples_set(p1_face_examples, p1_face_examples_n));
    assert_eq(MEDIA_VISION_ERROR_NONE, free_examples_set(p2_face_examples, p2_face_examples_n));

    printf("Before return mv_face_recognition_model_query_labels_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_recognition_model_query_labels()
 * @testcase        utc_mediavision_mv_face_recognition_model_query_labels_n
 * @since_tizen     3.0
 * @description     Query labels list and the number of labels,
 *                  but fail because input parameters are NULL
 */
int utc_mediavision_mv_face_recognition_model_query_labels_n(void)
{
    printf("Inside mv_face_recognition_model_query_labels_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_face_recognition_model_h recognition_model = NULL;
    int ret = mv_face_recognition_model_create(&recognition_model);
    assert_neq(NULL, recognition_model);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    int *labels = NULL;
    unsigned int labels_n = 0;

    ret = mv_face_recognition_model_query_labels(NULL, &labels, &labels_n);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_face_recognition_model_query_labels(recognition_model, NULL, &labels_n);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_face_recognition_model_query_labels(recognition_model, &labels, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    if (NULL != labels)
    {
        free(labels);
    }

    assert_eq(MEDIA_VISION_ERROR_NONE,
            mv_face_recognition_model_destroy(recognition_model));

    printf("Before return mv_face_query_labels_of_recognition_model_n\n");

    return 0;
}

void face_detected_cb(
         mv_source_h source,
         mv_engine_config_h engine_cfg,
         mv_rectangle_s *faces_locations,
         int number_of_faces,
         void *user_data)
{
    const int *expected_number_of_faces = (int*) user_data;

    is_face_detected_cb_called = true;
    printf("Test with %d face(s): ", *expected_number_of_faces);
    *expected_number_of_faces == number_of_faces ?
                                 printf("Passed\n") : printf("Failed\n");
}


/**
 * @brief Positive test case of mv_face_detect()
 * @testcase        utc_mediavision_mv_face_detect_p
 * @since_tizen     3.0
 * @description     Detect faces and invoke callback providing results
 */
int utc_mediavision_mv_face_detect_p(void)
{
    printf("Inside mv_face_detect_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h source1 = NULL;
    int ret = mv_create_source(&source1);
    assert_neq(NULL, source1);

    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/facedetect/face1.jpg")+1, "%s/res/facedetect/face1.jpg", pInternalStoragePath);
    ret = load_image_to_media_source(pszValue,
              source1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    int number_of_faces_on_image = 1;
    is_face_detected_cb_called = false;
    ret = mv_face_detect(source1, NULL, face_detected_cb, &number_of_faces_on_image);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(true, is_face_detected_cb_called);

    ret = mv_destroy_source(source1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_detect_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_face_detect()
 * @testcase        utc_mediavision_mv_face_detect_n
 * @since_tizen     3.0
 * @description     Detect faces and invoke callback providing results,
 *                  but fail because input parameters are NULL
 */
int utc_mediavision_mv_face_detect_n(void)
{
    printf("Inside mv_face_detect_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    int ret = mv_face_detect(NULL, NULL, face_detected_cb, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    mv_source_h source1 = NULL;
    ret = mv_create_source(&source1);
    assert_neq(NULL, source1);

    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/facedetect/face1.jpg")+1, "%s/res/facedetect/face1.jpg", pInternalStoragePath);
    ret = load_image_to_media_source(pszValue,
              source1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_face_detect(source1, NULL, NULL, NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    ret = mv_destroy_source(source1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_face_detect_n\n");

    return 0;
}
