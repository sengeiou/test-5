//
// Copyright (c) 2020 Samsung Electronics Co., Ltd.
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
#include "ITs-image-util-common.h"

#define NUM_OF_ANIM_FILES	5
#define LAST_ANIM_TYPE		IMAGE_UTIL_ANIM_WEBP

typedef struct {
	unsigned char *buffer;
	size_t buffer_size;
} buffer_data_t;

static const char *g_pszAnimFiles[NUM_OF_ANIM_FILES] = {
	"sample_anim1.png",
	"sample_anim2.png",
	"sample_anim3.png",
	"sample_anim4.png",
	"sample_anim5.png",
};
static const char *g_pszAnimOutputFiles[] = {
	[IMAGE_UTIL_ANIM_GIF] = "test_output.gif",
	[IMAGE_UTIL_ANIM_WEBP] = "test_output.webp",
};

static unsigned int g_nAnimIdx = 0;
static image_util_anim_type_e g_eAnimType = IMAGE_UTIL_ANIM_GIF;
static image_util_image_h g_hAnimImages[NUM_OF_ANIM_FILES] = { NULL, };
static image_util_anim_encode_h g_hAnimEncode[] = {
	[IMAGE_UTIL_ANIM_GIF] = NULL,
	[IMAGE_UTIL_ANIM_WEBP] = NULL,
};
static char *g_pszAnimOutputPath[] = {
	[IMAGE_UTIL_ANIM_GIF] = NULL,
	[IMAGE_UTIL_ANIM_WEBP] = NULL,
};
static buffer_data_t g_AnimOutputBuffer[] = {
	[IMAGE_UTIL_ANIM_GIF] = { NULL, 0 },
	[IMAGE_UTIL_ANIM_WEBP] = { NULL, 0 },
};

/** @addtogroup itc-image-util
*  @ingroup itc
*  @{
*/


/**
* @function 		ITs_image_util_anim_encode_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_image_util_anim_encode_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Image_Util_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet = IMAGE_UTIL_ERROR_NONE;
	char *pszAnimSrcPaths[NUM_OF_ANIM_FILES] = { NULL, };
	g_bStartUpSuccess = false;

	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == ImageUtilGetDataPath(pszValue)) {
		FPRINTF("[Line : %d][%s] 'ImageUtilGetDataPath' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
		for (g_nAnimIdx = 0; g_nAnimIdx < NUM_OF_ANIM_FILES; g_nAnimIdx++) {
			pszAnimSrcPaths[g_nAnimIdx] = ImageUtilGetTestPath(pszValue, g_pszAnimFiles[g_nAnimIdx]);
			FPRINTF("[%d:%s] IMAGE PATH [Decode: %s] \\n", __LINE__, __FUNCTION__, pszAnimSrcPaths[g_nAnimIdx]);
		}

		for (g_eAnimType = 0; g_eAnimType <= LAST_ANIM_TYPE; g_eAnimType++) {
			g_pszAnimOutputPath[g_eAnimType] = ImageUtilGetTestPath(pszValue, g_pszAnimOutputFiles[g_eAnimType]);
			FPRINTF("[%d:%s] IMAGE PATH [Encode: %s] \\n", __LINE__, __FUNCTION__, g_pszAnimOutputPath[g_eAnimType]);
		}
	} else {
		FPRINTF("[Line : %d][%s] ImageUtilGetDataPath didn't returned proper path\\n", __LINE__, API_NAMESPACE);
		return;
	}

	for (g_nAnimIdx = 0; g_nAnimIdx < NUM_OF_ANIM_FILES; g_nAnimIdx++) {
		nRet = ImageUtilAnimEncodeRunSetUp(&g_hAnimImages[g_nAnimIdx], pszAnimSrcPaths[g_nAnimIdx]);
		if (nRet != IMAGE_UTIL_ERROR_NONE) {
			FPRINTF("[%d:%s] Startup error! \\n", __LINE__, __FUNCTION__);
			g_free(pszAnimSrcPaths[g_nAnimIdx]);
			return;
		}
		g_free(pszAnimSrcPaths[g_nAnimIdx]);
	}

	g_bStartUpSuccess = true;

	return;
}

/**
* @function 		ITs_image_util_anim_encode_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_image_util_anim_encode_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Image_Util_p\\n", __LINE__, API_NAMESPACE);
#endif

	for (g_nAnimIdx = 0; g_nAnimIdx < NUM_OF_ANIM_FILES; g_nAnimIdx++) {
		image_util_destroy_image(g_hAnimImages[g_nAnimIdx]);
		g_hAnimImages[g_nAnimIdx] = NULL;
	}

	for (g_eAnimType = 0; g_eAnimType <= LAST_ANIM_TYPE; g_eAnimType++) {
		g_free(g_pszAnimOutputPath[g_eAnimType]);
		g_pszAnimOutputPath[g_eAnimType] = NULL;

		g_free(g_AnimOutputBuffer[g_eAnimType].buffer);
		g_AnimOutputBuffer[g_eAnimType].buffer = NULL;

		image_util_anim_encode_destroy(g_hAnimEncode[g_eAnimType]);
		g_hAnimEncode[g_eAnimType] = NULL;
	}

	return;
}

//& purpose: To create and destroy handle for encoding animation.
//& type: auto
/**
* @testcase   			ITc_image_util_anim_encode_create_destroy_p
* @since_tizen			6.0
* @author             	SRID(priya.kohli)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Creates and destroys handle for encoding animation.
* @scenario			Creates and destroys handle for encoding animation.
* @apicovered			image_util_anim_encode_create, image_util_anim_encode_destroy
* @passcase			When image_util_anim_encode_create and image_util_anim_encode_destroy are successful.
* @failcase			If target API image_util_anim_encode_create or image_util_anim_encode_destroy fails or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_anim_encode_create_destroy_p(void)
{
	START_TEST_ANIM;
	int nRet;

	for (g_eAnimType = 0; g_eAnimType <= LAST_ANIM_TYPE; g_eAnimType++) {
		nRet = image_util_anim_encode_create(g_eAnimType, &g_hAnimEncode[g_eAnimType]);
		PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_create", ImageUtilGetError(nRet));
		CHECK_HANDLE(g_hAnimEncode[g_eAnimType],"image_util_anim_encode_create");

		nRet = image_util_anim_encode_destroy(g_hAnimEncode[g_eAnimType]);
		PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_destroy", ImageUtilGetError(nRet));
		g_hAnimEncode[g_eAnimType] = NULL;
	}

	return 0;
}

//& purpose: To set a number of times to repeat the animation.
//& type: auto
/**
* @testcase   			ITc_image_util_anim_encode_set_loop_count_p
* @since_tizen			6.0
* @author             	SRID(priya.kohli)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets a number of times to repeat the animation.
* @scenario			Sets a number of times to repeat the animation.
* @apicovered			image_util_anim_encode_set_loop_count
* @passcase			When image_util_anim_encode_set_loop_count is successful.
* @failcase			If target API image_util_anim_encode_set_loop_count fails or any precondition API fails.
* @precondition			Create handle for encoding animation.
* @postcondition		Destroys handle.
*/
int ITc_image_util_anim_encode_set_loop_count_p(void)
{
	START_TEST_ANIM;
	int nRet;

	for (g_eAnimType = 0; g_eAnimType <= LAST_ANIM_TYPE; g_eAnimType++) {
		nRet = image_util_anim_encode_create(g_eAnimType, &g_hAnimEncode[g_eAnimType]);
		PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_create", ImageUtilGetError(nRet));
		CHECK_HANDLE(g_hAnimEncode[g_eAnimType],"image_util_anim_encode_create");

		nRet = image_util_anim_encode_set_loop_count(g_hAnimEncode[g_eAnimType], 0);
		PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_set_loop_count", ImageUtilGetError(nRet), image_util_anim_encode_destroy(g_hAnimEncode[g_eAnimType]));

		nRet = image_util_anim_encode_set_loop_count(g_hAnimEncode[g_eAnimType], 10);
		PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_set_loop_count", ImageUtilGetError(nRet), image_util_anim_encode_destroy(g_hAnimEncode[g_eAnimType]));

		nRet = image_util_anim_encode_destroy(g_hAnimEncode[g_eAnimType]);
		PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_destroy", ImageUtilGetError(nRet));
		g_hAnimEncode[g_eAnimType] = NULL;
	}

	return 0;
}

//& purpose: To set background color of the animation.
//& type: auto
/**
* @testcase   			ITc_image_util_anim_encode_set_background_color_p
* @since_tizen			6.0
* @author             	SRID(priya.kohli)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets a background color of the animation.
* @scenario			Sets a background color of the animation.
* @apicovered			image_util_anim_encode_set_background_color
* @passcase			When image_util_anim_encode_set_background_color is successful.
* @failcase			If target API image_util_anim_encode_set_background_color fails or any precondition API fails.
* @precondition			Create handle for encoding animation.
* @postcondition		Destroys handle.
*/
int ITc_image_util_anim_encode_set_background_color_p(void)
{
	START_TEST_ANIM;
	int nRet;

	nRet = image_util_anim_encode_create(IMAGE_UTIL_ANIM_WEBP, &g_hAnimEncode[IMAGE_UTIL_ANIM_WEBP]);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(g_hAnimEncode[IMAGE_UTIL_ANIM_WEBP],"image_util_anim_encode_create");

	nRet = image_util_anim_encode_set_background_color(g_hAnimEncode[IMAGE_UTIL_ANIM_WEBP], 0xFF, 0x00, 0x00, 0xFF);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_set_background_color", ImageUtilGetError(nRet), image_util_anim_encode_destroy(g_hAnimEncode[IMAGE_UTIL_ANIM_WEBP]));

	nRet = image_util_anim_encode_set_background_color(g_hAnimEncode[IMAGE_UTIL_ANIM_WEBP], 0x00, 0xFF, 0x00, 0xFF);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_set_background_color", ImageUtilGetError(nRet), image_util_anim_encode_destroy(g_hAnimEncode[IMAGE_UTIL_ANIM_WEBP]));

	nRet = image_util_anim_encode_set_background_color(g_hAnimEncode[IMAGE_UTIL_ANIM_WEBP], 0x00, 0x00, 0xFF, 0xFF);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_set_background_color", ImageUtilGetError(nRet), image_util_anim_encode_destroy(g_hAnimEncode[IMAGE_UTIL_ANIM_WEBP]));

	nRet = image_util_anim_encode_destroy(g_hAnimEncode[IMAGE_UTIL_ANIM_WEBP]);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_destroy", ImageUtilGetError(nRet));
	g_hAnimEncode[IMAGE_UTIL_ANIM_WEBP] = NULL;

	return 0;
}

//& purpose: To set lossless compression of animation.
//& type: auto
/**
* @testcase   			ITc_image_util_anim_encode_set_lossless_p
* @since_tizen			6.0
* @author             	SRID(priya.kohli)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets lossless compression of animation.
* @scenario			Sets lossless compression of animation.
* @apicovered			image_util_anim_encode_set_lossless
* @passcase			When image_util_anim_encode_set_lossless is successful.
* @failcase			If target API image_util_anim_encode_set_lossless fails or any precondition API fails.
* @precondition			Create handle for encoding animation.
* @postcondition		Destroys handle.
*/
int ITc_image_util_anim_encode_set_lossless_p(void)
{
	START_TEST_ANIM;
	int nRet;

	nRet = image_util_anim_encode_create(IMAGE_UTIL_ANIM_WEBP, &g_hAnimEncode[IMAGE_UTIL_ANIM_WEBP]);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(g_hAnimEncode[IMAGE_UTIL_ANIM_WEBP],"image_util_anim_encode_create");

	nRet = image_util_anim_encode_set_lossless(g_hAnimEncode[IMAGE_UTIL_ANIM_WEBP], true);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_set_lossless", ImageUtilGetError(nRet), image_util_anim_encode_destroy(g_hAnimEncode[IMAGE_UTIL_ANIM_WEBP]));

	nRet = image_util_anim_encode_set_lossless(g_hAnimEncode[IMAGE_UTIL_ANIM_WEBP], false);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_set_lossless", ImageUtilGetError(nRet), image_util_anim_encode_destroy(g_hAnimEncode[IMAGE_UTIL_ANIM_WEBP]));

	nRet = image_util_anim_encode_destroy(g_hAnimEncode[IMAGE_UTIL_ANIM_WEBP]);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_destroy", ImageUtilGetError(nRet));
	g_hAnimEncode[IMAGE_UTIL_ANIM_WEBP] = NULL;

	return 0;
}

//& purpose: To encode an image and add image to the frame of the animated image.
//& type: auto
/**
* @testcase   			ITc_image_util_anim_encode_add_frame_p
* @since_tizen			6.0
* @author             	SRID(priya.kohli)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Encodes an image and adds image to the frame of the animated image.
* @scenario			Encodes an image and adds image to the frame of the animated image.
* @apicovered			image_util_anim_encode_add_frame
* @passcase			When image_util_anim_encode_add_frame is successful.
* @failcase			If target API image_util_anim_encode_add_frame fails or any precondition API fails.
* @precondition			Create handle for encoding animation.
* @postcondition		Destroys handle.
*/
int ITc_image_util_anim_encode_add_frame_p(void)
{
	START_TEST_ANIM;
	int nRet;

	for (g_eAnimType = 0; g_eAnimType <= LAST_ANIM_TYPE; g_eAnimType++) {
		nRet = image_util_anim_encode_create(g_eAnimType, &g_hAnimEncode[g_eAnimType]);
		PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_create", ImageUtilGetError(nRet));
		CHECK_HANDLE(g_hAnimEncode[g_eAnimType],"image_util_anim_encode_create");

		nRet = image_util_anim_encode_add_frame(g_hAnimEncode[g_eAnimType], g_hAnimImages[0], 20);
		PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_add_frame", ImageUtilGetError(nRet), image_util_anim_encode_destroy(g_hAnimEncode[g_eAnimType]));

		nRet = image_util_anim_encode_destroy(g_hAnimEncode[g_eAnimType]);
		PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_destroy", ImageUtilGetError(nRet));
		g_hAnimEncode[g_eAnimType] = NULL;
	}

	return 0;
}

//& purpose: To save the animated WEBP or GIF image to the file.
//& type: auto
/**
* @testcase   			ITc_image_util_anim_encode_save_to_file_p
* @since_tizen			6.0
* @author             	SRID(priya.kohli)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Saves the animated WEBP or GIF image to the file.
* @scenario			Saves the animated WEBP or GIF image to the file.
* @apicovered			image_util_anim_encode_save_to_file
* @passcase			When image_util_anim_encode_save_to_file is successful.
* @failcase			If target API image_util_anim_encode_save_to_file fails or any precondition API fails.
* @precondition			Create handle for encoding animation.
* @postcondition		Destroys handle.
*/
int ITc_image_util_anim_encode_save_to_file_p(void)
{
	START_TEST_ANIM;
	int nRet;

	for (g_eAnimType = 0; g_eAnimType <= LAST_ANIM_TYPE; g_eAnimType++) {
		nRet = image_util_anim_encode_create(g_eAnimType, &g_hAnimEncode[g_eAnimType]);
		PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_create", ImageUtilGetError(nRet));
		CHECK_HANDLE(g_hAnimEncode[g_eAnimType],"image_util_anim_encode_create");

		nRet = image_util_anim_encode_set_loop_count(g_hAnimEncode[g_eAnimType], 0);
		PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_set_loop_count", ImageUtilGetError(nRet), image_util_anim_encode_destroy(g_hAnimEncode[g_eAnimType]));

		for (g_nAnimIdx = 0; g_nAnimIdx < NUM_OF_ANIM_FILES; g_nAnimIdx++) {
			nRet = image_util_anim_encode_add_frame(g_hAnimEncode[g_eAnimType], g_hAnimImages[g_nAnimIdx], 100);
			PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_add_frame", ImageUtilGetError(nRet), image_util_anim_encode_destroy(g_hAnimEncode[g_eAnimType]));
		}

		nRet = image_util_anim_encode_save_to_file(g_hAnimEncode[g_eAnimType], g_pszAnimOutputPath[g_eAnimType]);
		PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_save_to_file", ImageUtilGetError(nRet), image_util_anim_encode_destroy(g_hAnimEncode[g_eAnimType]));

		nRet = image_util_anim_encode_destroy(g_hAnimEncode[g_eAnimType]);
		PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_destroy", ImageUtilGetError(nRet));
		g_hAnimEncode[g_eAnimType] = NULL;
	}

	return 0;
}

//& purpose: To save the animation WEBP or GIF image to the buffer.
//& type: auto
/**
* @testcase   			ITc_image_util_anim_encode_save_to_buffer_p
* @since_tizen			6.0
* @author             	SRID(priya.kohli)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Saves the animation WEBP or GIF image to the buffer.
* @scenario			Saves the animation WEBP or GIF image to the buffer.
* @apicovered			image_util_anim_encode_save_to_buffer
* @passcase			When image_util_anim_encode_save_to_buffer is successful.
* @failcase			If target API image_util_anim_encode_save_to_buffer fails or any precondition API fails.
* @precondition			Create handle for encoding animation.
* @postcondition		Destroys handle.
*/
int ITc_image_util_anim_encode_save_to_buffer_p(void)
{
	START_TEST_ANIM;
	int nRet;

	for (g_eAnimType = 0; g_eAnimType <= LAST_ANIM_TYPE; g_eAnimType++) {
		nRet = image_util_anim_encode_create(g_eAnimType, &g_hAnimEncode[g_eAnimType]);
		PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_create", ImageUtilGetError(nRet));
		CHECK_HANDLE(g_hAnimEncode[g_eAnimType],"image_util_anim_encode_create");

		nRet = image_util_anim_encode_set_loop_count(g_hAnimEncode[g_eAnimType], 0);
		PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_set_loop_count", ImageUtilGetError(nRet), image_util_anim_encode_destroy(g_hAnimEncode[g_eAnimType]));

		for (g_nAnimIdx = 0; g_nAnimIdx < NUM_OF_ANIM_FILES; g_nAnimIdx++) {
			nRet = image_util_anim_encode_add_frame(g_hAnimEncode[g_eAnimType], g_hAnimImages[g_nAnimIdx], 100);
			PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_add_frame", ImageUtilGetError(nRet), image_util_anim_encode_destroy(g_hAnimEncode[g_eAnimType]));
		}

		nRet = image_util_anim_encode_save_to_buffer(g_hAnimEncode[g_eAnimType],
							&g_AnimOutputBuffer[g_eAnimType].buffer,
							&g_AnimOutputBuffer[g_eAnimType].buffer_size);
		PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_save_to_buffer", ImageUtilGetError(nRet), image_util_anim_encode_destroy(g_hAnimEncode[g_eAnimType]));
		CHECK_HANDLE_CLEANUP(g_AnimOutputBuffer[g_eAnimType].buffer,"image_util_anim_encode_save_to_buffer", image_util_anim_encode_destroy(g_hAnimEncode[g_eAnimType]));
		if(g_AnimOutputBuffer[g_eAnimType].buffer_size <= 8) {
			FPRINTF("[Line : %d][%s] Wrong buffer_size value : buffer_size = %d \\n", __LINE__, API_NAMESPACE, g_AnimOutputBuffer[g_eAnimType].buffer_size);
			image_util_anim_encode_destroy(g_hAnimEncode[g_eAnimType]);
			return 1;
		}

		nRet = image_util_anim_encode_destroy(g_hAnimEncode[g_eAnimType]);
		PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_anim_encode_destroy", ImageUtilGetError(nRet));
		g_hAnimEncode[g_eAnimType] = NULL;
	}

	return 0;
}

/** @} */
/** @} */
