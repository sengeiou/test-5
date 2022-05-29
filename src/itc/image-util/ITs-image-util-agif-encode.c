//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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

/** @addtogroup itc-image-util
*  @ingroup itc
*  @{
*/

/**
* @function 		ITs_image_util_agif_encode_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_image_util_agif_encode_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Image_Util_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		ITs_image_util_agif_encode_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_image_util_agif_encode_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Image_Util_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& purpose: Creates and destroys handle of animated GIF encoding.
//& type: auto
/**
* @testcase   			ITc_image_util_agif_encode_create_destroy_p
* @since_tizen			5.5
* @author             	SRID(karanam.s)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Creates and destroys handle of animated GIF encoding.
* @scenario			Creates and destroys handle of animated GIF encoding.
* @apicovered			image_util_agif_encode_create, image_util_agif_encode_destroy
* @passcase			When image_util_agif_encode_create and image_util_agif_encode_destroy is successful.
* @failcase			If target API image_util_agif_encode_create or image_util_agif_encode_destroy fails or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_agif_encode_create_destroy_p(void)
{
	START_TEST;
	image_util_agif_encode_h hImgUtilAgifEncode;

	int nRet = image_util_agif_encode_create(&hImgUtilAgifEncode);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_agif_encode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(hImgUtilAgifEncode, "image_util_agif_encode_create");

	nRet = image_util_agif_encode_destroy(hImgUtilAgifEncode);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_agif_encode_destroy", ImageUtilGetError(nRet));

	return 0;
}

//& purpose: Encodes an image and adds the encoded image to the frames of the animated GIF.
//& type: auto
/**
* @testcase   			ITc_image_util_agif_encode_add_frame_p
* @since_tizen			5.5
* @author             	SRID(karanam.s)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Encodes an image and adds the encoded image to the frames of the animated GIF.
* @scenario			Encodes an image and adds the encoded image to the frames of the animated GIF.
* @apicovered			image_util_agif_encode_add_frame
* @passcase			When image_util_agif_encode_add_frame is successful.
* @failcase			If target API image_util_agif_encode_add_frame fails or any precondition API fails.
* @precondition			image_util_agif_encode_create
* @postcondition		image_util_agif_encode_destroy
*/
int ITc_image_util_agif_encode_add_frame_p(void)
{
	START_TEST;
	image_util_agif_encode_h hImgUtilAgifEncode = NULL;
	image_util_decode_h dstHandle = NULL;
	image_util_image_h stDecodedImage = NULL;
	image_util_encode_h stHandle = NULL;
	unsigned int nDelayTime = 20;

	char pPath[PATH_LEN] = {0,};
	if ( false == ImageUtilAppendToAppDataPath(SAMPLE_GIF_FILE_PATH, pPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = image_util_decode_create(&dstHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(dstHandle,"image_util_decode_create");

	nRet = image_util_decode_set_input_path(dstHandle, pPath);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_input_path", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));

	nRet = image_util_decode_run2(dstHandle, &stDecodedImage);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_run2", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));
	CHECK_HANDLE_CLEANUP(stDecodedImage,"image_util_decode_run2", image_util_decode_destroy(dstHandle));

	nRet = image_util_decode_destroy(dstHandle);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage));

	nRet = image_util_agif_encode_create(&hImgUtilAgifEncode);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_agif_encode_create", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage));
	CHECK_HANDLE_CLEANUP(hImgUtilAgifEncode,"image_util_agif_encode_create", image_util_destroy_image(stDecodedImage));

	nRet = image_util_agif_encode_add_frame(hImgUtilAgifEncode, stDecodedImage, nDelayTime);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_agif_encode_add_frame", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage);image_util_agif_encode_destroy(hImgUtilAgifEncode));

	nRet = image_util_destroy_image(stDecodedImage);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_destroy_image", ImageUtilGetError(nRet));

	nRet = image_util_agif_encode_destroy(hImgUtilAgifEncode);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_agif_encode_destroy", ImageUtilGetError(nRet));

	return 0;
}

//& purpose: Saves the animated GIF image to the file.
//& type: auto
/**
* @testcase   			ITc_image_util_agif_encode_save_to_file_p
* @since_tizen			5.5
* @author             	SRID(karanam.s)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Saves the animated GIF image to the file.
* @scenario			Saves the animated GIF image to the file.
* @apicovered			image_util_agif_encode_save_to_file
* @passcase			When image_util_agif_encode_save_to_file is successful.
* @failcase			If target API image_util_agif_encode_save_to_file fails or any precondition API fails.
* @precondition			image_util_agif_encode_create
* @postcondition		image_util_agif_encode_destroy
*/
int ITc_image_util_agif_encode_save_to_file_p(void)
{
	START_TEST;
	image_util_agif_encode_h hImgUtilAgifEncode = NULL;
	image_util_decode_h dstHandle = NULL;
	image_util_image_h stDecodedImage = NULL;
	image_util_encode_h stHandle = NULL;
	unsigned int nDelayTime = 20;

	char pPath[PATH_LEN] = {0,};
	if ( false == ImageUtilAppendToAppDataPath(SAMPLE_GIF_FILE_PATH, pPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = image_util_decode_create(&dstHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(dstHandle,"image_util_decode_create");

	nRet = image_util_decode_set_input_path(dstHandle, pPath);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_input_path", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));

	nRet = image_util_decode_run2(dstHandle, &stDecodedImage);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_run2", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));
	CHECK_HANDLE_CLEANUP(stDecodedImage,"image_util_decode_run2", image_util_decode_destroy(dstHandle));

	nRet = image_util_decode_destroy(dstHandle);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage));

	nRet = image_util_agif_encode_create(&hImgUtilAgifEncode);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_agif_encode_create", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage));
	CHECK_HANDLE_CLEANUP(hImgUtilAgifEncode,"image_util_agif_encode_create", image_util_destroy_image(stDecodedImage));

	nRet = image_util_agif_encode_add_frame(hImgUtilAgifEncode, stDecodedImage, nDelayTime);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_agif_encode_add_frame", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage);image_util_agif_encode_destroy(hImgUtilAgifEncode));

	nRet = image_util_agif_encode_save_to_file(hImgUtilAgifEncode, pPath);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_agif_encode_save_to_file", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage);image_util_agif_encode_destroy(hImgUtilAgifEncode));

	nRet = image_util_destroy_image(stDecodedImage);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_destroy_image", ImageUtilGetError(nRet));

	nRet = image_util_agif_encode_destroy(hImgUtilAgifEncode);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_agif_encode_destroy", ImageUtilGetError(nRet));

	return 0;
}

//& purpose: Saves the animated GIF image to the buffer.
//& type: auto
/**
* @testcase   			ITc_image_util_agif_encode_save_to_buffer_p
* @since_tizen			5.5
* @author             	SRID(karanam.s)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Saves the animated GIF image to the buffer.
* @scenario			Saves the animated GIF image to the buffer.
* @apicovered			image_util_agif_encode_save_to_buffer
* @passcase			When image_util_agif_encode_save_to_buffer is successful.
* @failcase			If target API image_util_agif_encode_save_to_buffer fails or any precondition API fails.
* @precondition			image_util_agif_encode_create
* @postcondition		image_util_agif_encode_destroy
*/
int ITc_image_util_agif_encode_save_to_buffer_p(void)
{
	START_TEST;
	image_util_agif_encode_h hImgUtilAgifEncode = NULL;
	image_util_decode_h dstHandle = NULL;
	image_util_image_h stDecodedImage = NULL;
	image_util_encode_h stHandle = NULL;
	unsigned int nDelayTime = 20;
	char *pszBuffer = NULL;
	size_t tBufferSize;

	char pPath[PATH_LEN] = {0,};
	if ( false == ImageUtilAppendToAppDataPath(SAMPLE_GIF_FILE_PATH, pPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = image_util_decode_create(&dstHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(dstHandle,"image_util_decode_create");

	nRet = image_util_decode_set_input_path(dstHandle, pPath);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_input_path", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));

	nRet = image_util_decode_run2(dstHandle, &stDecodedImage);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_run2", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));
	CHECK_HANDLE_CLEANUP(stDecodedImage,"image_util_decode_run2", image_util_decode_destroy(dstHandle));

	nRet = image_util_decode_destroy(dstHandle);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage));

	nRet = image_util_agif_encode_create(&hImgUtilAgifEncode);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_agif_encode_create", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage));
	CHECK_HANDLE_CLEANUP(hImgUtilAgifEncode,"image_util_agif_encode_create", image_util_destroy_image(stDecodedImage));

	nRet = image_util_agif_encode_add_frame(hImgUtilAgifEncode, stDecodedImage, nDelayTime);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_agif_encode_add_frame", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage);image_util_agif_encode_destroy(hImgUtilAgifEncode));

	nRet = image_util_agif_encode_save_to_buffer(hImgUtilAgifEncode, &pszBuffer, &tBufferSize);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_agif_encode_save_to_buffer", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage);image_util_agif_encode_destroy(hImgUtilAgifEncode));
	CHECK_HANDLE_CLEANUP(hImgUtilAgifEncode,"image_util_agif_encode_save_to_buffer", image_util_destroy_image(stDecodedImage);image_util_agif_encode_destroy(hImgUtilAgifEncode));
	if(tBufferSize <= 0)
	{
		FPRINTF("image_util_agif_encode_save_to_buffer failed, tBufferSize is %d", tBufferSize);
		image_util_destroy_image(stDecodedImage);
		image_util_agif_encode_destroy(hImgUtilAgifEncode);
		return 1;
	}

	nRet = image_util_destroy_image(stDecodedImage);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_destroy_image", ImageUtilGetError(nRet));

	nRet = image_util_agif_encode_destroy(hImgUtilAgifEncode);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_agif_encode_destroy", ImageUtilGetError(nRet));
}
/** @} */
/** @} */
