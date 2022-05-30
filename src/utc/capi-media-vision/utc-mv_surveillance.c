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

#include <mv_surveillance.h>

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include <unistd.h>
#include <image_util.h>
#include <system_info.h>
#include "tct_common.h"
#include <storage.h>

#define API_NAMESPACE "[MediaVision]"

static bool isVisionSupported = false;
static int gStartupError;
static mv_surveillance_event_trigger_h movement_detected_trigger = NULL;
static mv_surveillance_event_trigger_h person_appeared_trigger = NULL;
static mv_surveillance_event_trigger_h person_recognized_trigger = NULL;
static mv_engine_config_h engine_cfg = NULL;

static mv_source_h source_det1;
static mv_source_h source_det2;
static mv_source_h source_face;
static mv_source_h source_recog;

static char* pInternalStoragePath=NULL;

/**
 * @function            utc_capi_media_vision_surveillance_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_capi_media_vision_surveillance_startup(void)
{
	bool isFaceRecognitionSupported = false;
	bool isImageRecognitionSupported = false;

	printf("capi-media-vision surveillance tests STARTUP is launched\n");

	system_info_get_platform_bool("http://tizen.org/feature/vision.face_recognition", &isFaceRecognitionSupported);
	system_info_get_platform_bool("http://tizen.org/feature/vision.image_recognition", &isImageRecognitionSupported);

	if (isFaceRecognitionSupported || isImageRecognitionSupported)
		isVisionSupported = true;
	else
		isVisionSupported = false;

	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if (true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE)) {
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received %s\\n", __LINE__, API_NAMESPACE, pszValue);
		pInternalStoragePath = (char*)calloc(strlen(pszValue)+1, sizeof(char));
		snprintf(pInternalStoragePath, strlen(pszValue)+1, "%s", pszValue);
	} else {
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

	gStartupError = MEDIA_VISION_ERROR_NONE;

	gStartupError = mv_surveillance_event_trigger_create(
			MV_SURVEILLANCE_EVENT_TYPE_MOVEMENT_DETECTED,
			&movement_detected_trigger);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	gStartupError = mv_surveillance_event_trigger_create(
			MV_SURVEILLANCE_EVENT_TYPE_PERSON_APPEARED_DISAPPEARED,
			&person_appeared_trigger);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	gStartupError = mv_surveillance_event_trigger_create(
			MV_SURVEILLANCE_EVENT_TYPE_PERSON_RECOGNIZED,
			&person_recognized_trigger);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	gStartupError = mv_create_engine_config(&engine_cfg);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	gStartupError = mv_create_source(&source_det1);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	gStartupError = mv_create_source(&source_det2);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	gStartupError = mv_create_source(&source_face);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	gStartupError = mv_create_source(&source_recog);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}
	printf("Before return utc_capi_media_vision_surveillance_startup\n");
}

/**
 * @function            utc_capi_media_vision_surveillance_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_capi_media_vision_surveillance_cleanup(void)
{
	printf("Inside utc_capi_media_vision_surveillance_cleanup\n");
	if (movement_detected_trigger != NULL)
		mv_surveillance_event_trigger_destroy(movement_detected_trigger);

	if (person_appeared_trigger != NULL)
		mv_surveillance_event_trigger_destroy(person_appeared_trigger);

	if (person_recognized_trigger != NULL)
		mv_surveillance_event_trigger_destroy(person_recognized_trigger);

	if (engine_cfg != NULL)
		mv_destroy_engine_config(engine_cfg);

	if (source_det1 != NULL)
		mv_destroy_source(source_det1);

	if (source_det2 != NULL)
		mv_destroy_source(source_det2);

	if (source_face != NULL)
		mv_destroy_source(source_face);

	if (source_recog != NULL)
		mv_destroy_source(source_recog);

	if (pInternalStoragePath) {
		free(pInternalStoragePath);
		pInternalStoragePath = NULL;
	}

	movement_detected_trigger = NULL;
	person_appeared_trigger = NULL;
	person_recognized_trigger = NULL;
	engine_cfg = NULL;
	source_det1 = NULL;
	source_det2 = NULL;
	source_face = NULL;
	source_recog = NULL;
	printf("Before return utc_capi_media_vision_surveillance_cleanup\n");
}

static int load_image_to_media_source(const char *file_path, mv_source_h source)
{
	printf("Inside load_image_to_media_source\n");
	if (NULL == file_path || NULL == source) {
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

	/* Only grayscale and RGB jpegs in test set: */
	mv_colorspace_e source_colorspace = MEDIA_VISION_COLORSPACE_RGB888;

	ret2 = mv_source_clear(source);
	if (ret2 != MEDIA_VISION_ERROR_NONE) goto _LOAD_IMAGE_FAIL;

	ret2 = mv_source_fill_by_buffer(source, data_buffer, (unsigned int)buffer_size, (unsigned int)width,
			(unsigned int)height, source_colorspace);

_LOAD_IMAGE_FAIL:
	image_util_decode_destroy(_decoder);
	if(data_buffer)
		free(data_buffer);

	assert_eq(IMAGE_UTIL_ERROR_NONE, ret1);
	assert_eq(MEDIA_VISION_ERROR_NONE, ret2);

	printf("Before return load_image_to_media_source\n");
	return MEDIA_VISION_ERROR_NONE;
}

void empty_cb(mv_surveillance_event_trigger_h person_appeared_trigger,
		mv_source_h source, int video_id, mv_surveillance_result_h event_result,
		void *user_data)
{
	printf("Inside empty_cb\n");
	; /* NULL */
}

/**
 * @testcase            utc_mediavision_mv_surveillance_event_trigger_create_p
 * @since_tizen         3.0
 * @description         Create event trigger with proper parameter
 */
int utc_mediavision_mv_surveillance_event_trigger_create_p(void)
{
	printf("Inside mv_surveillance_event_trigger_create_p\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	/* MV_SURVEILLANCE_EVENT_MOVEMENT_DETECTED */
	mv_surveillance_event_trigger_h mMovDetTrigger = NULL;
	int error = mv_surveillance_event_trigger_create(
			MV_SURVEILLANCE_EVENT_TYPE_MOVEMENT_DETECTED,
			&mMovDetTrigger);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_event_trigger_destroy(mMovDetTrigger);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_APPEARED_DISAPEARED */
	mv_surveillance_event_trigger_h mPerAppearTrigger = NULL;
	error = mv_surveillance_event_trigger_create(
			MV_SURVEILLANCE_EVENT_TYPE_PERSON_APPEARED_DISAPPEARED,
			&mPerAppearTrigger);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_event_trigger_destroy(mPerAppearTrigger);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_RECOGNIZED */
	mv_surveillance_event_trigger_h mPerRcogTrigger = NULL;
	error = mv_surveillance_event_trigger_create(
			MV_SURVEILLANCE_EVENT_TYPE_PERSON_RECOGNIZED,
			&mPerRcogTrigger);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_event_trigger_destroy(mPerRcogTrigger);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	printf("Before return mv_surveillance_event_trigger_create_p\n");

	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_event_trigger_create_n
 * @since_tizen         3.0
 * @description         Create event trigger but fail because of invalid parameter
 */
int utc_mediavision_mv_surveillance_event_trigger_create_n(void)
{
	printf("Inside mv_surveillance_event_trigger_create_n\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	/* MV_SURVEILLANCE_EVENT_MOVEMENT_DETECTED */
	mv_surveillance_event_trigger_h mMovDetTrigger = NULL;
	int error = mv_surveillance_event_trigger_create(
			MV_SURVEILLANCE_EVENT_TYPE_MOVEMENT_DETECTED, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	error = mv_surveillance_event_trigger_create(NULL,
			&mMovDetTrigger);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_APPEARED_DISAPEARED */
	mv_surveillance_event_trigger_h mPerAppearTrigger = NULL;
	error = mv_surveillance_event_trigger_create(
			MV_SURVEILLANCE_EVENT_TYPE_PERSON_APPEARED_DISAPPEARED, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	error = mv_surveillance_event_trigger_create(NULL,
			&mPerAppearTrigger);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_RECOGNIZED */
	mv_surveillance_event_trigger_h mPerRcogTrigger = NULL;
	error = mv_surveillance_event_trigger_create(
			MV_SURVEILLANCE_EVENT_TYPE_PERSON_RECOGNIZED, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	error = mv_surveillance_event_trigger_create(NULL,
			&mPerRcogTrigger);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	printf("Before return mv_surveillance_event_trigger_create_n\n");

	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_event_trigger_destroy_p
 * @since_tizen         3.0
 * @description         Destroy event trigger
 */
int utc_mediavision_mv_surveillance_event_trigger_destroy_p(void)
{
	printf("Inside mv_surveillance_event_trigger_destroy_p\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	/* MV_SURVEILLANCE_EVENT_MOVEMENT_DETECTED */
	mv_surveillance_event_trigger_h mMovDetTrigger = NULL;
	int error = mv_surveillance_event_trigger_create(
			MV_SURVEILLANCE_EVENT_TYPE_MOVEMENT_DETECTED,
			&mMovDetTrigger);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_event_trigger_destroy(mMovDetTrigger);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_APPEARED_DISAPEARED */
	mv_surveillance_event_trigger_h mPerAppearTrigger = NULL;
	error = mv_surveillance_event_trigger_create(
			MV_SURVEILLANCE_EVENT_TYPE_PERSON_APPEARED_DISAPPEARED,
			&mPerAppearTrigger);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_event_trigger_destroy(mPerAppearTrigger);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_RECOGNIZED */
	mv_surveillance_event_trigger_h mPerRcogTrigger = NULL;
	error = mv_surveillance_event_trigger_create(
			MV_SURVEILLANCE_EVENT_TYPE_PERSON_RECOGNIZED,
			&mPerRcogTrigger);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_event_trigger_destroy(mPerRcogTrigger);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	printf("Before return mv_surveillance_event_trigger_destroy_p\n");

	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_event_trigger_destroy_n
 * @since_tizen         3.0
 * @description         Destroy event trigger but fail because of invalid parameter
 */
int utc_mediavision_mv_surveillance_event_trigger_destroy_n(void)
{
	printf("Inside mv_surveillance_event_trigger_destroy_n\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int error = mv_surveillance_event_trigger_destroy(NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	printf("Before return mv_surveillance_event_trigger_destroy_n\n");

	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_subscribe_event_trigger_p
 * @since_tizen         3.0
 * @description         Subscribe event trigger
 */
int utc_mediavision_mv_surveillance_subscribe_event_trigger_p(void)
{
	printf("Inside mv_surveillance_subscribe_event_trigger_p\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	/* MV_SURVEILLANCE_EVENT_MOVEMENT_DETECTED */
	int error = mv_surveillance_subscribe_event_trigger(movement_detected_trigger,
			0, NULL, empty_cb, NULL);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_unsubscribe_event_trigger(movement_detected_trigger,
			0);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_APPEARED_DISAPEARED */
	error = mv_surveillance_subscribe_event_trigger(person_appeared_trigger, 0,
			NULL, empty_cb, NULL);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_unsubscribe_event_trigger(person_appeared_trigger,
			0);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_RECOGNIZED */
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/res/surv/model.txt")+1, "%s/res/res/surv/model.txt", pInternalStoragePath);
	error = mv_engine_config_set_string_attribute(engine_cfg,
			MV_SURVEILLANCE_FACE_RECOGNITION_MODEL_FILE_PATH,
			pszValue);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_subscribe_event_trigger(person_recognized_trigger,
			0, engine_cfg, empty_cb, NULL);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_unsubscribe_event_trigger(person_recognized_trigger,
			0);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	printf("Before return mv_surveillance_subscribe_event_trigger_p\n");

	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_subscribe_event_trigger_n
 * @since_tizen         3.0
 * @description         Subscribe event trigger but fail because of invalid parameter
 */
int utc_mediavision_mv_surveillance_subscribe_event_trigger_n(void)
{
	printf("Inside mv_surveillance_subscribe_event_trigger_n\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int error = mv_surveillance_subscribe_event_trigger(
			NULL, 0, NULL, NULL, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	/* MV_SURVEILLANCE_EVENT_MOVEMENT_DETECTED */
	error = mv_surveillance_subscribe_event_trigger(movement_detected_trigger,
			0, NULL, NULL, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_APPEARED_DISAPEARED */
	error = mv_surveillance_subscribe_event_trigger(person_appeared_trigger, 0,
			NULL, NULL, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_RECOGNIZED */
	error = mv_surveillance_subscribe_event_trigger(person_recognized_trigger,
			0, NULL, NULL, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	printf("Before return mv_surveillance_subscribe_event_trigger_n\n");

	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_unsubscribe_event_trigger_p
 * @since_tizen         3.0
 * @description         Unsubscribe event trigger
 */
int utc_mediavision_mv_surveillance_unsubscribe_event_trigger_p(void)
{
	printf("Inside mv_surveillance_unsubscribe_event_trigger_p\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	/* MV_SURVEILLANCE_EVENT_MOVEMENT_DETECTED */
	int error = mv_surveillance_subscribe_event_trigger(movement_detected_trigger,
			0, NULL, empty_cb, NULL);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_unsubscribe_event_trigger(movement_detected_trigger,
			0);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_APPEARED_DISAPEARED */
	error = mv_surveillance_subscribe_event_trigger(person_appeared_trigger, 0,
			NULL, empty_cb, NULL);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_unsubscribe_event_trigger(person_appeared_trigger,
			0);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_RECOGNIZED */
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/res/surv/model.txt")+1, "%s/res/res/surv/model.txt", pInternalStoragePath);
	error = mv_engine_config_set_string_attribute(engine_cfg,
			MV_SURVEILLANCE_FACE_RECOGNITION_MODEL_FILE_PATH,
			pszValue);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_subscribe_event_trigger(person_recognized_trigger,
			0, engine_cfg, empty_cb, NULL);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_unsubscribe_event_trigger(person_recognized_trigger,
			0);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	printf("Before return mv_surveillance_unsubscribe_event_trigger_p\n");

	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_unsubscribe_event_trigger_n
 * @since_tizen         3.0
 * @description         Unsubscribe event trigger but fail because of invalid parameter
 */
int utc_mediavision_mv_surveillance_unsubscribe_event_trigger_n(void)
{
	printf("Inside mv_surveillance_unsubscribe_event_trigger_n\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int error = mv_surveillance_unsubscribe_event_trigger(NULL, 0);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	printf("Before return mv_surveillance_unsubscribe_event_trigger_n\n");

	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_push_source_p
 * @since_tizen         3.0
 * @description         Push source for movement detection/person detection/person recognition
 */
int utc_mediavision_mv_surveillance_push_source_p(void)
{
	printf("Inside mv_surveillance_push_source_p\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	/* MV_SURVEILLANCE_EVENT_MOVEMENT_DETECTED */
	int error = mv_surveillance_subscribe_event_trigger(movement_detected_trigger,
			0, NULL, empty_cb, NULL);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/res/surv/move_det_1.jpg")+1, "%s/res/res/surv/move_det_1.jpg", pInternalStoragePath);
	error = load_image_to_media_source(pszValue, source_det1);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_push_source(source_det1, 0);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_unsubscribe_event_trigger(movement_detected_trigger,
			0);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_APPEARED_DISAPEARED */
	error = mv_surveillance_subscribe_event_trigger(person_appeared_trigger, 0,
			NULL, empty_cb, NULL);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	memset(pszValue, 0, CONFIG_VALUE_LEN_MAX);
	snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/res/surv/move_det_2.jpg")+1, "%s/res/res/surv/move_det_2.jpg", pInternalStoragePath);
	error = load_image_to_media_source(
			pszValue, source_det2);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_push_source(source_det2, 0);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_unsubscribe_event_trigger(person_appeared_trigger,
			0);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_RECOGNIZED */
	memset(pszValue, 0, CONFIG_VALUE_LEN_MAX);
	snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/res/surv/model.txt")+1, "%s/res/res/surv/model.txt", pInternalStoragePath);
	error = mv_engine_config_set_string_attribute(engine_cfg,
			MV_SURVEILLANCE_FACE_RECOGNITION_MODEL_FILE_PATH,
			pszValue);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_subscribe_event_trigger(person_recognized_trigger,
			0, engine_cfg, empty_cb, NULL);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	memset(pszValue, 0, CONFIG_VALUE_LEN_MAX);
	snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/res/surv/pers_recogn.jpg")+1, "%s/res/res/surv/pers_recogn.jpg", pInternalStoragePath);
	error = load_image_to_media_source(pszValue, source_recog);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_push_source(source_recog, 0);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_unsubscribe_event_trigger(person_recognized_trigger,
			0);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	printf("Before return mv_surveillance_push_source_p\n");

	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_push_source_n
 * @since_tizen         3.0
 * @description         Push source but fail because of invalid parameter
 */
int utc_mediavision_mv_surveillance_push_source_n(void)
{
	printf("Inside mv_surveillance_push_source_n\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int error = mv_surveillance_push_source(NULL, 0);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/res/facedetect/face1.jpg")+1, "%s/res/res/facedetect/face1.jpg", pInternalStoragePath);
	error = load_image_to_media_source(
			pszValue, source_face);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	error = mv_surveillance_push_source(source_face, 5);
	assert_eq(MEDIA_VISION_ERROR_INVALID_OPERATION, error);

	printf("Before return mv_surveillance_push_source_n\n");

	return 0;
}

#define EOA "END OF ARRAY"

const char *event_types[] = {
		MV_SURVEILLANCE_EVENT_TYPE_MOVEMENT_DETECTED,
		MV_SURVEILLANCE_EVENT_TYPE_PERSON_APPEARED_DISAPPEARED,
		MV_SURVEILLANCE_EVENT_TYPE_PERSON_RECOGNIZED, EOA};

const char *event_mov_names[] = {
		MV_SURVEILLANCE_MOVEMENT_NUMBER_OF_REGIONS,
		MV_SURVEILLANCE_MOVEMENT_REGIONS, EOA};

const char *event_appear_names[] = {
		MV_SURVEILLANCE_PERSONS_APPEARED_NUMBER,
		MV_SURVEILLANCE_PERSONS_DISAPPEARED_NUMBER,
		MV_SURVEILLANCE_PERSONS_TRACKED_NUMBER,
		MV_SURVEILLANCE_PERSONS_APPEARED_LOCATIONS,
		MV_SURVEILLANCE_PERSONS_DISAPPEARED_LOCATIONS,
		MV_SURVEILLANCE_PERSONS_TRACKED_LOCATIONS, EOA};

const char *event_rec_names[] = {
		MV_SURVEILLANCE_PERSONS_RECOGNIZED_NUMBER,
		MV_SURVEILLANCE_PERSONS_RECOGNIZED_LOCATIONS,
		MV_SURVEILLANCE_PERSONS_RECOGNIZED_LABELS,
		MV_SURVEILLANCE_PERSONS_RECOGNIZED_CONFIDENCES, EOA};

char **test_array = NULL;

bool event_type_name_cb(const char *name, void *user_data)
{
	printf("Inside event_type_name_cb\n");

	int *cb_counter = (int *) user_data;
	if (NULL == cb_counter) {
		printf("Callback counter is NULL\n");
		return false;
	}

	if (NULL == name) {
		printf("Name obtained in foreach callback is null!\n");
		(*cb_counter) = -1;
		return false;
	}

	bool known_event_type = false;
	int idx = 0;
	while (strncmp(EOA, test_array[idx], 255) != 0) {
		if (strncmp(name, test_array[idx], 255) == 0)
			known_event_type = true;
		++idx;
	}

	if (!known_event_type) {
		printf("Name '%s' is unknown!\n", name);
		(*cb_counter) = -1;
		return false;
	}

	printf("Name obtained in foreach callback: %s\n", name);

	if (*cb_counter < 0) {
		(*cb_counter) = 1;
		return false;
	} else {
		++(*cb_counter);
	}

	printf("Before return event_type_name_cb\n");
	return true;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_foreach_supported_event_type_p
 * @since_tizen         3.0
 * @description         Check surpported event type
 */
int utc_mediavision_mv_surveillance_foreach_supported_event_type_p(void)
{
	printf("Inside mv_surveillance_foreach_supported_event_type_p\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	test_array = event_types;

	int cb_counter = 0;
	int error = mv_surveillance_foreach_supported_event_type(event_type_name_cb,
			&cb_counter);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);
	assert_eq(3, cb_counter);

	/* -1 value is used to traverse only first element in foreach */
	cb_counter = -1;
	error = mv_surveillance_foreach_supported_event_type(event_type_name_cb,
			&cb_counter);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);
	assert_eq(1, cb_counter);

	printf("Before return mv_surveillance_foreach_supported_event_type_p\n");
	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_foreach_supported_event_type_n
 * @since_tizen         3.0
 * @description         Check supported event type but fail because of invalid parameter
 */
int utc_mediavision_mv_surveillance_foreach_supported_event_type_n(void)
{
	printf("Inside mv_surveillance_foreach_supported_event_type_n\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	const int error = mv_surveillance_foreach_supported_event_type(NULL, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	printf("Before return mv_surveillance_foreach_supported_event_type_n\n");
	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_foreach_event_result_name_p
 * @since_tizen         3.0
 * @description         Check event result name
 */
int utc_mediavision_mv_surveillance_foreach_event_result_name_p(void)
{
	printf("Inside mv_surveillance_foreach_event_result_name_p\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int cb_counter = 0;
	test_array = event_mov_names;
	int error = mv_surveillance_foreach_event_result_name(
			MV_SURVEILLANCE_EVENT_TYPE_MOVEMENT_DETECTED, event_type_name_cb,
			&cb_counter);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);
	assert_eq(2, cb_counter);

	cb_counter = 0;
	test_array = event_appear_names;
	error = mv_surveillance_foreach_event_result_name(
			MV_SURVEILLANCE_EVENT_TYPE_PERSON_APPEARED_DISAPPEARED,
			event_type_name_cb, &cb_counter);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);
	assert_eq(6, cb_counter);

	cb_counter = 0;
	test_array = event_rec_names;
	error = mv_surveillance_foreach_event_result_name(
			MV_SURVEILLANCE_EVENT_TYPE_PERSON_RECOGNIZED,
			event_type_name_cb, &cb_counter);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);
	assert_eq(4, cb_counter);

	/* -1 value is used to traverse only first element in foreach */
	cb_counter = -1;
	test_array = event_mov_names;
	error = mv_surveillance_foreach_event_result_name(
			MV_SURVEILLANCE_EVENT_TYPE_MOVEMENT_DETECTED, event_type_name_cb,
			&cb_counter);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);
	assert_eq(1, cb_counter);

	printf("Before return mv_surveillance_foreach_event_result_name_p\n");
	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_foreach_event_result_name_n
 * @since_tizen         3.0
 * @description         Check event result name but fail beacuse of invalid parameter
 */
int utc_mediavision_mv_surveillance_foreach_event_result_name_n(void)
{
	printf("Inside mv_surveillance_foreach_event_result_name_n\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int error = mv_surveillance_foreach_event_result_name(NULL,
			event_type_name_cb, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	error = mv_surveillance_foreach_event_result_name(
			MV_SURVEILLANCE_EVENT_TYPE_MOVEMENT_DETECTED, NULL, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	error = mv_surveillance_foreach_event_result_name(
			MV_SURVEILLANCE_EVENT_TYPE_PERSON_APPEARED_DISAPPEARED, NULL, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	error = mv_surveillance_foreach_event_result_name(
			MV_SURVEILLANCE_EVENT_TYPE_PERSON_RECOGNIZED, NULL, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	printf("Before return mv_surveillance_foreach_event_result_name_n\n");
	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_get_event_trigger_type_p
 * @since_tizen         3.0
 * @description         Get event trigger
 */
int utc_mediavision_mv_surveillance_get_event_trigger_type_p(void)
{
	printf("Inside mv_surveillance_get_event_trigger_type_p\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	char *event_type = NULL;

	/* MV_SURVEILLANCE_EVENT_MOVEMENT_DETECTED */
	int error = mv_surveillance_get_event_trigger_type(movement_detected_trigger,
			&event_type);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	assert_eq(strcmp(event_type, MV_SURVEILLANCE_EVENT_TYPE_MOVEMENT_DETECTED),
			0);

	free(event_type);
	event_type = NULL;

	/* MV_SURVEILLANCE_EVENT_PERSON_APPEARED_DISAPEARED */
	error = mv_surveillance_get_event_trigger_type(person_appeared_trigger,
			&event_type);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	assert_eq(strcmp(event_type,
		 MV_SURVEILLANCE_EVENT_TYPE_PERSON_APPEARED_DISAPPEARED), 0);

	free(event_type);
	event_type = NULL;

	/* MV_SURVEILLANCE_EVENT_PERSON_RECOGNIZED */
	error = mv_surveillance_get_event_trigger_type(person_recognized_trigger,
			&event_type);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	assert_eq(strcmp(event_type, MV_SURVEILLANCE_EVENT_TYPE_PERSON_RECOGNIZED),
			0);

	free(event_type);
	event_type = NULL;

	printf("Before return mv_surveillance_get_event_trigger_type_p\n");

	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_get_event_trigger_type_n
 * @since_tizen         3.0
 * @description         Get event trigger type but fail beacuse of invalid parameter
 */
int utc_mediavision_mv_surveillance_get_event_trigger_type_n(void)
{
	printf("Inside mv_surveillance_get_event_trigger_type_n\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int error = mv_surveillance_get_event_trigger_type(NULL, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	char *event_type = NULL;

	error = mv_surveillance_get_event_trigger_type(NULL, &event_type);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	/* MV_SURVEILLANCE_EVENT_MOVEMENT_DETECTED */
	error = mv_surveillance_get_event_trigger_type(movement_detected_trigger,
			NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_APPEARED_DISAPEARED */
	error = mv_surveillance_get_event_trigger_type(person_appeared_trigger,
			NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_RECOGNIZED */
	error = mv_surveillance_get_event_trigger_type(person_recognized_trigger,
			NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	printf("Before return mv_surveillance_get_event_trigger_type_n\n");

	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_set_event_trigger_roi_p1
 * @since_tizen         3.0
 * @description         Set roi(region of interest) in event trigger
 */
int utc_mediavision_mv_surveillance_set_event_trigger_roi_p1(void)
{
	printf("Inside mv_surveillance_set_event_trigger_roi_p1\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	const int number_of_points = 4;
	mv_point_s *roi = calloc(number_of_points, sizeof(mv_point_s));
	if (roi == NULL) {
		printf("Error occured in memory allocation to mv_point_s roi\n");
		return 1;
	}

	roi[0].x = 100;
	roi[0].y = 100;

	roi[1].x = 100;
	roi[1].y = 200;

	roi[2].x = 200;
	roi[2].y = 200;

	roi[3].x = 200;
	roi[3].y = 100;

	/* MV_SURVEILLANCE_EVENT_MOVEMENT_DETECTED */
	int error = mv_surveillance_set_event_trigger_roi(movement_detected_trigger,
			number_of_points, roi);
	if (error != MEDIA_VISION_ERROR_NONE) {
		free(roi);
		printf("Error occured in mv_surveillance_set_event_trigger_roi_p1\n");
		return 1;
	}

	/* MV_SURVEILLANCE_EVENT_PERSON_APPEARED_DISAPEARED */
	error = mv_surveillance_set_event_trigger_roi(person_appeared_trigger,
			number_of_points, roi);
	if (error != MEDIA_VISION_ERROR_NONE) {
		free(roi);
		printf("Error occured in mv_surveillance_set_event_trigger_roi_p1\n");
		return 1;
	}

	/* MV_SURVEILLANCE_EVENT_PERSON_RECOGNIZED */
	error = mv_surveillance_set_event_trigger_roi(person_recognized_trigger,
			number_of_points, roi);
	if (error != MEDIA_VISION_ERROR_NONE) {
		free(roi);
		printf("Error occured in mv_surveillance_set_event_trigger_roi_p1\n");
		return 1;
	}

	free(roi);
	roi = NULL;

	printf("Before return mv_surveillance_set_event_trigger_roi_p1\n");

	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_set_event_trigger_roi_p2
 * @since_tizen         3.0
 * @description         Set roi(region of interest) in event trigger
 *                      and then set different roi again
 */
int utc_mediavision_mv_surveillance_set_event_trigger_roi_p2(void)
{
	printf("Inside mv_surveillance_set_event_trigger_roi_p2\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	const int number_of_points = 4;
	mv_point_s *roi_1 = calloc(number_of_points, sizeof(mv_point_s));
	if (roi_1 == NULL) {
		printf("Error occured in memory allocation to mv_point_s roi_1\n");
		return 1;
	}

	roi_1[0].x = 100;
	roi_1[0].y = 100;

	roi_1[1].x = 100;
	roi_1[1].y = 200;

	roi_1[2].x = 200;
	roi_1[2].y = 200;

	roi_1[3].x = 200;
	roi_1[3].y = 100;

	mv_point_s *roi_2 = calloc(number_of_points, sizeof(mv_point_s));
	if (roi_2 == NULL) {
		printf("Error occured in memory allocation to mv_point_s roi_2\n");
		free(roi_1);
		return 1;
	}

	roi_2[0].x = 100;
	roi_2[0].y = 100;

	roi_2[1].x = 100;
	roi_2[1].y = 300;

	roi_2[2].x = 300;
	roi_2[2].y = 300;

	roi_2[3].x = 300;
	roi_2[3].y = 100;

	/* MV_SURVEILLANCE_EVENT_MOVEMENT_DETECTED */
	int error = mv_surveillance_set_event_trigger_roi(movement_detected_trigger,
			number_of_points, roi_1);
	if (error != MEDIA_VISION_ERROR_NONE) {
		free(roi_1);
		free(roi_2);
		printf("Error occured in mv_surveillance_set_event_trigger_roi_p2\n");
		return 1;
	}

	error = mv_surveillance_set_event_trigger_roi(movement_detected_trigger,
			number_of_points, roi_2);
	if (error != MEDIA_VISION_ERROR_NONE) {
		free(roi_1);
		free(roi_2);
		printf("Error occured in mv_surveillance_set_event_trigger_roi_p2\n");
		return 1;
	}

	free(roi_1);
	roi_1 = NULL;
	free(roi_2);
	roi_2 = NULL;

	printf("Before return mv_surveillance_set_event_trigger_roi_p2\n");

	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_set_event_trigger_roi_n1
 * @since_tizen         3.0
 * @description         Set roi(region of interest) but fail because of invalid parameter
 */
int utc_mediavision_mv_surveillance_set_event_trigger_roi_n1(void)
{
	printf("Inside mv_surveillance_set_event_trigger_roi_n1\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int error = mv_surveillance_set_event_trigger_roi(NULL, 0, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	const int number_of_points = 4;
	mv_point_s *roi = calloc(number_of_points, sizeof(mv_point_s));
	if (roi == NULL) {
		printf("Error occured in memory allocation to mv_point_s roi\n");
		return 1;
	}

	roi[0].x = 100;
	roi[0].y = 100;

	roi[1].x = 100;
	roi[1].y = 200;

	roi[2].x = 200;
	roi[2].y = 200;

	roi[3].x = 200;
	roi[3].y = 100;

	error = mv_surveillance_set_event_trigger_roi(NULL, number_of_points, roi);
	free(roi);
	roi = NULL;
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	/* MV_SURVEILLANCE_EVENT_MOVEMENT_DETECTED */
	error = mv_surveillance_set_event_trigger_roi(movement_detected_trigger, 0,
			NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_APPEARED_DISAPEARED */
	error = mv_surveillance_set_event_trigger_roi(person_appeared_trigger, 0,
			NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_RECOGNIZED */
	error = mv_surveillance_set_event_trigger_roi(person_recognized_trigger, 0,
			NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	printf("Before return mv_surveillance_set_event_trigger_roi_n1\n");

	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_set_event_trigger_roi_n2
 * @since_tizen         3.0
 * @description         Set roi(region of interest) but fail because of invalid parameter
 */
int utc_mediavision_mv_surveillance_set_event_trigger_roi_n2(void)
{
	printf("Inside mv_surveillance_set_event_trigger_roi_n2\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	const int number_of_points = 4;
	mv_point_s *roi = calloc(number_of_points, sizeof(mv_point_s));
	if (roi == NULL) {
		printf("Error occured in memory allocation to mv_point_s roi\n");
		return 1;
	}

	roi[0].x = 100;
	roi[0].y = 100;

	roi[1].x = 100;
	roi[1].y = 200;

	roi[2].x = 200;
	roi[2].y = 200;

	roi[3].x = 200;
	roi[3].y = 100;

	/* MV_SURVEILLANCE_EVENT_MOVEMENT_DETECTED */
	int error = mv_surveillance_set_event_trigger_roi(movement_detected_trigger, 0,
			roi);
	free(roi);
	roi = NULL;

	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	printf("Before return mv_surveillance_set_event_trigger_roi_n2\n");

	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_get_event_trigger_roi_p
 * @since_tizen         3.0
 * @description         Get roi(region of interest) in event trigger
 */
int utc_mediavision_mv_surveillance_get_event_trigger_roi_p(void)
{
	printf("Inside mv_surveillance_get_event_trigger_roi_p\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int test_number_of_points = 0;
	mv_point_s *test_roi = NULL;

	/* MV_SURVEILLANCE_EVENT_MOVEMENT_DETECTED */
	int error = mv_surveillance_get_event_trigger_roi(movement_detected_trigger,
			&test_number_of_points, &test_roi);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	assert_eq(test_number_of_points, 0);
	assert_eq(test_roi, NULL);

	const int number_of_points = 4;
	mv_point_s *roi = calloc(number_of_points, sizeof(mv_point_s));
	if (roi == NULL) {
		printf("Error occured in memory allocation to mv_point_s roi\n");
		return 1;
	}

	roi[0].x = 100;
	roi[0].y = 100;

	roi[1].x = 100;
	roi[1].y = 200;

	roi[2].x = 200;
	roi[2].y = 200;

	roi[3].x = 200;
	roi[3].y = 100;

	error = mv_surveillance_set_event_trigger_roi(movement_detected_trigger,
			number_of_points, roi);
	if (error != MEDIA_VISION_ERROR_NONE) {
		free(roi);
		roi = NULL;
		return 1;
	}

	error = mv_surveillance_get_event_trigger_roi(movement_detected_trigger,
			&test_number_of_points, &test_roi);
	if (test_roi == NULL) {
		free(roi);
		roi = NULL;
		return 1;
	}
	if (error != MEDIA_VISION_ERROR_NONE) {
		free(roi);
		free(test_roi);
		roi = test_roi = NULL;
		return 1;
	}
	if (number_of_points != test_number_of_points) {
		free(roi);
		free(test_roi);
		roi = test_roi = NULL;
		return 1;
	}

	int i = 0;
	bool roi_match = true;
	for (; i < number_of_points; ++i) {
		if (roi[i].x != test_roi[i].x || roi[i].y != test_roi[i].y)
			roi_match = false;
	}
	free(roi);
	free(test_roi);
	roi = test_roi = NULL;
	test_number_of_points = 0;

	assert(roi_match);

	/* MV_SURVEILLANCE_EVENT_PERSON_APPEARED_DISAPEARED */
	error = mv_surveillance_get_event_trigger_roi(person_appeared_trigger,
			&test_number_of_points, &test_roi);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	assert_eq(test_number_of_points, 0);
	assert_eq(test_roi, NULL);

	roi = calloc(number_of_points, sizeof(mv_point_s));
	if (roi == NULL) {
		printf("Error occured in memory allocation to mv_point_s roi\n");
		return 1;
	}

	roi[0].x = 100;
	roi[0].y = 100;

	roi[1].x = 100;
	roi[1].y = 200;

	roi[2].x = 200;
	roi[2].y = 200;

	roi[3].x = 200;
	roi[3].y = 100;

	error = mv_surveillance_set_event_trigger_roi(person_appeared_trigger,
			number_of_points, roi);
	if (error != MEDIA_VISION_ERROR_NONE) {
		free(roi);
		roi = NULL;
		return 1;
	}

	error = mv_surveillance_get_event_trigger_roi(person_appeared_trigger,
			&test_number_of_points, &test_roi);
	if (test_roi == NULL) {
		free(roi);
		roi = NULL;
		return 1;
	}
	if (error != MEDIA_VISION_ERROR_NONE) {
		free(roi);
		free(test_roi);
		roi = test_roi = NULL;
		return 1;
	}
	if (number_of_points != test_number_of_points) {
		free(roi);
		free(test_roi);
		roi = test_roi = NULL;
		return 1;
	}

	roi_match = true;
	for (i = 0; i < number_of_points; ++i) {
		if (roi[i].x != test_roi[i].x || roi[i].y != test_roi[i].y)
			roi_match = false;
	}
	free(roi);
	free(test_roi);
	roi = test_roi = NULL;
	test_number_of_points = 0;

	assert(roi_match);

	/* MV_SURVEILLANCE_EVENT_PERSON_RECOGNIZED */
	error = mv_surveillance_get_event_trigger_roi(person_recognized_trigger,
			&test_number_of_points, &test_roi);
	assert_eq(MEDIA_VISION_ERROR_NONE, error);

	assert_eq(test_number_of_points, 0);
	assert_eq(test_roi, NULL);

	roi = calloc(number_of_points, sizeof(mv_point_s));
	if (roi == NULL) {
		printf("Error occured in memory allocation to mv_point_s roi\n");
		return 1;
	}

	roi[0].x = 100;
	roi[0].y = 100;

	roi[1].x = 100;
	roi[1].y = 200;

	roi[2].x = 200;
	roi[2].y = 200;

	roi[3].x = 200;
	roi[3].y = 100;

	error = mv_surveillance_set_event_trigger_roi(person_recognized_trigger,
			number_of_points, roi);
	if (error != MEDIA_VISION_ERROR_NONE) {
		free(roi);
		roi = NULL;
		return 1;
	}

	error = mv_surveillance_get_event_trigger_roi(person_recognized_trigger,
			&test_number_of_points, &test_roi);
	if (test_roi == NULL) {
		free(roi);
		roi = NULL;
		return 1;
	}
	if (error != MEDIA_VISION_ERROR_NONE) {
		free(roi);
		free(test_roi);
		roi = test_roi = NULL;
		return 1;
	}
	if (number_of_points != test_number_of_points) {
		free(roi);
		free(test_roi);
		roi = test_roi = NULL;
		return 1;
	}

	roi_match = true;
	for (i = 0; i < number_of_points; ++i) {
		if (roi[i].x != test_roi[i].x || roi[i].y != test_roi[i].y)
			roi_match = false;
	}
	free(roi);
	free(test_roi);
	roi = test_roi = NULL;
	test_number_of_points = 0;

	assert(roi_match);

	printf("Before return mv_surveillance_get_event_trigger_roi_p\n");

	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_get_event_trigger_roi_n
 * @since_tizen         3.0
 * @description         Get roi(region of interest) but fail because of invalid parameter
 */
int utc_mediavision_mv_surveillance_get_event_trigger_roi_n(void)
{
	printf("Inside mv_surveillance_get_event_trigger_roi_n\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	int error = mv_surveillance_get_event_trigger_roi(NULL, NULL, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	int number_of_points = 0;
	mv_point_s *roi = NULL;

	error = mv_surveillance_get_event_trigger_roi(NULL, NULL, &roi);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	error = mv_surveillance_get_event_trigger_roi(NULL, &number_of_points, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	error = mv_surveillance_get_event_trigger_roi(NULL, &number_of_points, &roi);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	/* MV_SURVEILLANCE_EVENT_MOVEMENT_DETECTED */
	error = mv_surveillance_get_event_trigger_roi(movement_detected_trigger,
			NULL, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	error = mv_surveillance_get_event_trigger_roi(movement_detected_trigger,
			&number_of_points, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	error = mv_surveillance_get_event_trigger_roi(movement_detected_trigger,
			NULL, &roi);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_APPEARED_DISAPEARED */
	error = mv_surveillance_get_event_trigger_roi(person_appeared_trigger, NULL,
			NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	error = mv_surveillance_get_event_trigger_roi(person_appeared_trigger,
			&number_of_points, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	error = mv_surveillance_get_event_trigger_roi(person_appeared_trigger,
			NULL, &roi);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	/* MV_SURVEILLANCE_EVENT_PERSON_RECOGNIZED */
	error = mv_surveillance_get_event_trigger_roi(person_recognized_trigger,
			NULL, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	error = mv_surveillance_get_event_trigger_roi(person_recognized_trigger,
			&number_of_points, NULL);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	error = mv_surveillance_get_event_trigger_roi(person_recognized_trigger,
			NULL, &roi);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	printf("Before return mv_surveillance_get_event_trigger_roi_n\n");

	return 0;
}

typedef struct movement_detection_result_s {

	bool callback_is_called;
	size_t number_of_mov_regions;
	int invalid_value_type_obtaining_err;
	int number_of_mov_regions_obtaining_err;
	int mov_locations_obtaining_err;

} movement_detection_result;

void get_movement_detection_result_cb(mv_surveillance_event_trigger_h event_trigger,
		mv_source_h source, int video_id, mv_surveillance_result_h event_result,
		void *user_data)
{
	printf("Inside get_movement_detection_result_cb (%p)\n", event_result);

	movement_detection_result *res = (movement_detection_result*)user_data;

	res->callback_is_called = true;

	size_t fake_value = 0;
	res->invalid_value_type_obtaining_err = mv_surveillance_get_result_value(
			event_result, "AAA", &fake_value);

	res->number_of_mov_regions_obtaining_err = mv_surveillance_get_result_value(
			event_result, MV_SURVEILLANCE_MOVEMENT_NUMBER_OF_REGIONS,
			&(res->number_of_mov_regions));

	mv_rectangle_s *mov_locations = malloc(sizeof(mv_rectangle_s) * res->number_of_mov_regions);

	res->mov_locations_obtaining_err = mv_surveillance_get_result_value(
			event_result, MV_SURVEILLANCE_MOVEMENT_REGIONS, mov_locations);

	/* free() covers every case of the return value of malloc() */
	free(mov_locations);

	printf("Before return get_movement_detection_result_cb\n");
}

movement_detection_result movement_detection_data;

/**
 * @function            utc_capi_media_vision_surveillance_cb1_startup
 * @description         Called before MOVEMENT DETECT TRIGGER callback function test
 * @parameter           NA
 * @return              NA
 */
void utc_capi_media_vision_surveillance_cb1_startup(void)
{
	printf("Inside utc_capi_media_vision_surveillance_cb1_startup\n");
	utc_capi_media_vision_surveillance_startup();

	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	movement_detection_data.callback_is_called = false;

	gStartupError = mv_surveillance_subscribe_event_trigger(movement_detected_trigger,
			0, NULL, get_movement_detection_result_cb, &movement_detection_data);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/res/surv/move_det_1.jpg")+1, "%s/res/res/surv/move_det_1.jpg", pInternalStoragePath);
	gStartupError = load_image_to_media_source(pszValue, source_det1);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	gStartupError = mv_surveillance_push_source(source_det1, 0);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	memset(pszValue, 0, CONFIG_VALUE_LEN_MAX);
	snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/res/surv/move_det_2.jpg")+1, "%s/res/res/surv/move_det_2.jpg", pInternalStoragePath);
	gStartupError = load_image_to_media_source(pszValue, source_det2);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	gStartupError = mv_surveillance_push_source(source_det2, 0);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	gStartupError = mv_surveillance_unsubscribe_event_trigger(movement_detected_trigger,
			0);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	printf("Before return utc_capi_media_vision_surveillance_cb1_startup\n");
}

/**
 * @testcase            utc_mediavision_mv_surveillance_get_result_value_n
 * @since_tizen         3.0
 * @description         Get result value but fail beacuse of invalid event name
 */
int utc_mediavision_mv_surveillance_get_result_value_n(void)
{
	printf("Inside mv_surveillance_get_result_value_n\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(movement_detection_data.callback_is_called);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER,
			movement_detection_data.invalid_value_type_obtaining_err);
	size_t fake_value = 0;
	int error = mv_surveillance_get_result_value(NULL, "AAA", &fake_value);
	assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, error);

	printf("Before return mv_surveillance_get_result_value_n\n");

	return 0;
}

/**
 * @testcase            utc_mediavision_mv_surveillance_get_result_value_p1
 * @since_tizen         3.0
 * @description         Get result value as MOVEMENT DETECT TRIGGER result
 */
int utc_mediavision_mv_surveillance_get_result_value_p1(void)
{
	printf("Inside mv_surveillance_get_result_value_p1\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(movement_detection_data.callback_is_called);
	assert_eq(MEDIA_VISION_ERROR_NONE,
			movement_detection_data.number_of_mov_regions_obtaining_err);
	const int expected_number_of_mov_regions = 2;
	assert_eq(expected_number_of_mov_regions,
			movement_detection_data.number_of_mov_regions);
	assert_eq(MEDIA_VISION_ERROR_NONE,
			movement_detection_data.mov_locations_obtaining_err);

	printf("Before return mv_surveillance_get_result_value_p1\n");

	return 0;
}

typedef struct person_appearance_result_s {

	bool callback_is_called;

	int number_of_appeared_persons_obtaining_err;
	int number_of_tracked_persons_obtaining_err;
	int number_of_disappeared_persons_obtaining_err;

	int appeared_locations_obtaining_err;
	int disappeared_locations_obtaining_err;
	int tracked_locations_obtaining_err;

} person_appearance_result;

void get_person_appearance_result_cb(mv_surveillance_event_trigger_h event_trigger,
		mv_source_h source, int video_id, mv_surveillance_result_h event_result,
		void *user_data)
{
	printf("Inside get_person_appearance_result_cb\n");

	person_appearance_result *res = (person_appearance_result*)user_data;

	res->callback_is_called = true;

	size_t number_appeared_persons = 0;
	res->number_of_appeared_persons_obtaining_err =
			mv_surveillance_get_result_value(event_result,
					MV_SURVEILLANCE_PERSONS_APPEARED_NUMBER,
					&number_appeared_persons);

	if (number_appeared_persons > 0) {
		mv_rectangle_s *appeared_locations = malloc(
				sizeof(mv_rectangle_s) * number_appeared_persons);

		res->appeared_locations_obtaining_err =
				mv_surveillance_get_result_value(event_result,
						MV_SURVEILLANCE_PERSONS_APPEARED_LOCATIONS,
						appeared_locations);

		free(appeared_locations);
	}

	size_t number_of_tracked_persons = 0;
	res->number_of_tracked_persons_obtaining_err =
			mv_surveillance_get_result_value(event_result,
					MV_SURVEILLANCE_PERSONS_TRACKED_NUMBER,
					&number_of_tracked_persons);

	if (number_of_tracked_persons > 0) {
		mv_rectangle_s *tracked_locations = malloc(
				sizeof(mv_rectangle_s) * number_of_tracked_persons);

		res->tracked_locations_obtaining_err =
				mv_surveillance_get_result_value(event_result,
						MV_SURVEILLANCE_PERSONS_TRACKED_LOCATIONS,
						tracked_locations);

		free(tracked_locations);
	}

	size_t number_of_disappeared_persons = 0;
	res->number_of_disappeared_persons_obtaining_err =
			mv_surveillance_get_result_value(event_result,
					MV_SURVEILLANCE_PERSONS_DISAPPEARED_NUMBER,
					&number_of_disappeared_persons);

	if (number_of_disappeared_persons > 0) {
		mv_rectangle_s *disappeared_locations = malloc(
				sizeof(mv_rectangle_s) * number_of_disappeared_persons);

		res->disappeared_locations_obtaining_err =
				mv_surveillance_get_result_value(event_result,
						MV_SURVEILLANCE_PERSONS_DISAPPEARED_LOCATIONS,
						disappeared_locations);

		free(disappeared_locations);
	}

	printf("Before return get_person_appearance_result_cb\n");
}

person_appearance_result person_appearance_data;

/**
 * @function            utc_capi_media_vision_surveillance_cb2_startup
 * @description         Called before PERSON APPEARED/DISAPPEARED TRIGGER callback function test
					PERSON RECOGNITION TRIGGER callback function test
 * @parameter           NA
 * @return              NA
 */
void utc_capi_media_vision_surveillance_cb2_startup(void)
{
	printf("Inside utc_capi_media_vision_surveillance_cb2_startup\n");
	utc_capi_media_vision_surveillance_startup();

	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	person_appearance_data.callback_is_called = false;

	gStartupError = mv_surveillance_subscribe_event_trigger(person_appeared_trigger,
			0, NULL, get_person_appearance_result_cb, &person_appearance_data);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/res/surv/move_det_1.jpg")+1, "%s/res/res/surv/move_det_1.jpg", pInternalStoragePath);
	gStartupError = load_image_to_media_source(pszValue, source_det1);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	gStartupError = mv_surveillance_push_source(source_det1, 0);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	memset(pszValue, 0, CONFIG_VALUE_LEN_MAX);
	snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/res/surv/pers_det.jpg")+1, "%s/res/res/surv/pers_det.jpg", pInternalStoragePath);
	gStartupError = load_image_to_media_source(pszValue, source_recog);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	gStartupError = mv_surveillance_push_source(source_recog, 0);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	gStartupError = mv_surveillance_unsubscribe_event_trigger(person_appeared_trigger,
			0);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	printf("Before return utc_capi_media_vision_surveillance_cb2_startup\n");
}

/**
 * @testcase            utc_mediavision_mv_surveillance_get_result_value_p2
 * @since_tizen         3.0
 * @description         Get result value as PERSON APPEARED/DISAPPEARED TRIGGER result
 */
int utc_mediavision_mv_surveillance_get_result_value_p2(void)
{
	printf("Inside mv_surveillance_get_result_value_p2\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(person_appearance_data.callback_is_called);
	assert_eq(MEDIA_VISION_ERROR_NONE,
			person_appearance_data.number_of_appeared_persons_obtaining_err);
	assert_eq(MEDIA_VISION_ERROR_NONE,
			person_appearance_data.appeared_locations_obtaining_err);
	assert_eq(MEDIA_VISION_ERROR_NONE,
			person_appearance_data.number_of_tracked_persons_obtaining_err);
	assert_eq(MEDIA_VISION_ERROR_NONE,
			person_appearance_data.tracked_locations_obtaining_err);
	assert_eq(MEDIA_VISION_ERROR_NONE,
			person_appearance_data.number_of_disappeared_persons_obtaining_err);
	assert_eq(MEDIA_VISION_ERROR_NONE,
			person_appearance_data.disappeared_locations_obtaining_err);

	printf("Before return mv_surveillance_get_result_value_p2\n");

	return 0;
}

typedef struct person_recognition_result_s {

	bool callback_is_called;

	size_t number_of_persons;
	int number_of_persons_obtaining_err;
	int locations_obtaining_err;
	int labels_obtaining_err;
	int confidences_obtaining_err;

} person_recognition_result;

void get_person_recognition_result_cb(mv_surveillance_event_trigger_h event_trigger,
		mv_source_h source, int video_id, mv_surveillance_result_h event_result,
		void *user_data)
{
	printf("Inside get_person_recognition_result_cb\n");

	person_recognition_result *res = (person_recognition_result*)user_data;

	res->callback_is_called = true;

	res->number_of_persons_obtaining_err = mv_surveillance_get_result_value(
			event_result, MV_SURVEILLANCE_PERSONS_RECOGNIZED_NUMBER,
			&res->number_of_persons);

	mv_rectangle_s *locations = malloc(
			sizeof(mv_rectangle_s) * res->number_of_persons);

	res->locations_obtaining_err = mv_surveillance_get_result_value(event_result,
			MV_SURVEILLANCE_PERSONS_RECOGNIZED_LOCATIONS, locations);

	if (res->number_of_persons > 0) {
		free(locations);
		locations = NULL;
	}

	int *labels = malloc(sizeof(int) * res->number_of_persons);
	res->labels_obtaining_err = mv_surveillance_get_result_value(event_result,
			MV_SURVEILLANCE_PERSONS_RECOGNIZED_LABELS, labels);

	if (res->number_of_persons > 0) {
		free(labels);
		labels = NULL;
	}

	double *confidences = malloc(sizeof(double) * res->number_of_persons);
	res->confidences_obtaining_err = mv_surveillance_get_result_value(event_result,
			MV_SURVEILLANCE_PERSONS_RECOGNIZED_CONFIDENCES, confidences);

	if (res->number_of_persons > 0) {
		free(confidences);
		confidences = NULL;
	}

	if (labels != NULL)
		free(labels);

	if (locations != NULL)
		free(locations);

	if (confidences != NULL)
		free(confidences);

	printf("Before return get_person_recognition_result_cb\n");
}

person_recognition_result person_recognition_data;

/**
 * @function            utc_capi_media_vision_surveillance_cb3_startup
 * @description         Called before PERSON RECOGNITION TRIGGER callback function test
 * @parameter           NA
 * @return              NA
 */
void utc_capi_media_vision_surveillance_cb3_startup(void)
{
	printf("Inside utc_capi_media_vision_surveillance_cb3_startup\n");
	utc_capi_media_vision_surveillance_startup();

	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/res/surv/model.txt")+1, "%s/res/res/surv/model.txt", pInternalStoragePath);
	gStartupError = mv_engine_config_set_string_attribute(engine_cfg,
			MV_SURVEILLANCE_FACE_RECOGNITION_MODEL_FILE_PATH,
			pszValue);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	person_recognition_data.callback_is_called = false;

	gStartupError = mv_surveillance_subscribe_event_trigger(person_recognized_trigger,
			0, engine_cfg, get_person_recognition_result_cb, &person_recognition_data);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	memset(pszValue, 0, CONFIG_VALUE_LEN_MAX);
	snprintf(pszValue, strlen(pInternalStoragePath)+strlen("/res/res/surv/pers_recogn.jpg")+1, "%s/res/res/surv/pers_recogn.jpg", pInternalStoragePath);
	gStartupError = load_image_to_media_source(pszValue, source_recog);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	gStartupError = mv_surveillance_push_source(source_recog, 0);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	gStartupError = mv_surveillance_unsubscribe_event_trigger(
			person_recognized_trigger, 0);
	if (gStartupError != MEDIA_VISION_ERROR_NONE) {
		return;
	}

	printf("Before return utc_capi_media_vision_surveillance_cb3_startup\n");
}

/**
 * @testcase            utc_mediavision_mv_surveillance_get_result_value_p3
 * @since_tizen         3.0
 * @description         Get result value as PERSON RECOGNITION TRIGGER result
 */
int utc_mediavision_mv_surveillance_get_result_value_p3(void)
{
	printf("Inside mv_surveillance_get_result_value_p3\n");

	if(!isVisionSupported) {
		assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert(person_recognition_data.callback_is_called);
	assert_eq(MEDIA_VISION_ERROR_NONE,
			person_recognition_data.number_of_persons_obtaining_err);
	assert(person_recognition_data.number_of_persons);
	assert_eq(MEDIA_VISION_ERROR_NONE,
			person_recognition_data.locations_obtaining_err);
	assert_eq(MEDIA_VISION_ERROR_NONE,
			person_recognition_data.labels_obtaining_err);
	assert_eq(MEDIA_VISION_ERROR_NONE,
			person_recognition_data.confidences_obtaining_err);

	printf("Before return mv_surveillance_get_result_value_p3\n");

	return 0;
}
