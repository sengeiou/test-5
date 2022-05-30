//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
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
#include "CTs-image-util-common.h"


/** @addtogroup ctc-image-util
* @ingroup		ctc
* @{
*/

//& set: ImageUtil

/**
* @function 		CTs_image_util_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_image_util_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Image_Util_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function 		CTs_image_util_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_image_util_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Image_Util_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}


/** @addtogroup	ctc-image-util-testcases
* @brief 		Integration testcases for module image-util
* @ingroup		ctc-image-util
* @{
*/

//& purpose: Encode jpeg image to jpg format.
//& type: auto
/**
* @testcase			CTc_ImageUtil_ImageEncoder_JPEG_p
* @since_tizen		2.3
* @author            SRID(sk.roy)
* @reviewer         SRID(gupta.sanjay)
* @type 			auto
* @scenario			Decodes jpeg image to the buffer\n
* 					Calculates the size of image buffer for the specified resolution and colorspace\n
* 					Encodes image to the jpeg image
* @apicovered		image_util_decode_jpeg,image_util_calculate_buffer_size,image_util_encode_jpeg
* @passcase			If image encoding to jpeg image is done successfully and all api returns success message.
* @failcase			If an api returns error message.
* @precondition		NA
* @postcondition	NA
*/
int CTc_ImageUtil_ImageEncoder_JPEG_p(void)
{
	START_TEST;

	unsigned long nWidth = 0, nHeight = 0;
	unsigned long long unDecodeSize = 0;
	unsigned char * upszImgSourceBuffer = NULL;
	char * pszImgPath = ImageUtilGetDataPath(SAMPLE_FILE);
	if(pszImgPath == NULL)
	{
		FPRINTF("[Line : %d][%s] ImageUtilGetDataPath failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( ImageUtilDecode(pszImgPath, IMAGE_UTIL_COLORSPACE_RGB888, &nWidth, &nHeight, &upszImgSourceBuffer, &unDecodeSize) == false )
	{
		FREE_MEMORY(upszImgSourceBuffer);
		FREE_MEMORY(pszImgPath);
		return 1;
	}

	if ( ImageUtilCheckFunction(upszImgSourceBuffer, nWidth, nHeight, unDecodeSize) == false )
	{
		FREE_MEMORY(upszImgSourceBuffer);
		FREE_MEMORY(pszImgPath);
		return 1;
	}

	FREE_MEMORY(upszImgSourceBuffer);
	FREE_MEMORY(pszImgPath);

	if ( ImageUtilEncode(nWidth, nHeight, IMAGE_UTIL_COLORSPACE_RGB888) == false )
	{
		return 1;
	}

	return 0;
}

//& purpose: Decode jpg image
//& type: auto
/**
* @testcase			CTc_ImageUtil_ImageDecoder_JPG_p
* @since_tizen		2.3
* @author            SRID(sk.roy)
* @reviewer         SRID(gupta.sanjay)
* @type 			auto
* @scenario			Decodes jpeg image to the buffer\n
* 					Calculates the size of image buffer for the specified resolution and colorspace\n
* 					Encodes image to the jpeg image\n
* 					Decodes the encoded jpeg image to the buffer
* @apicovered		image_util_decode_jpeg,image_util_calculate_buffer_size,image_util_encode_jpeg
* @passcase			All api returns success message.
* @failcase			An api returns error message.
* @precondition		NA
* @postcondition	NA
*/
int CTc_ImageUtil_ImageDecoder_JPG_p(void)
{
	START_TEST;
	
	image_util_decode_h dstHandle = NULL;
	unsigned long nWidth = 0, nHeight = 0;
	unsigned long long unDecodeSize = 0;
	unsigned char * upszImgSourceBuffer = NULL;
	char * pszImgPath = ImageUtilGetDataPath(SAMPLE_FILE);
	if(pszImgPath == NULL)
	{
		FPRINTF("[Line : %d][%s] ImageUtilGetDataPath failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( ImageUtilDecode(pszImgPath, IMAGE_UTIL_COLORSPACE_RGB888, &nWidth, &nHeight, &upszImgSourceBuffer, &unDecodeSize) == false )
	{
		FREE_MEMORY(upszImgSourceBuffer);
		FREE_MEMORY(pszImgPath);
		return 1;
	}

	if ( ImageUtilCheckFunction(upszImgSourceBuffer, nWidth, nHeight, unDecodeSize) == false )
	{
		FREE_MEMORY(upszImgSourceBuffer);
		FREE_MEMORY(pszImgPath);
		return 1;
	}

	if ( ImageUtilEncode(nWidth, nHeight, IMAGE_UTIL_COLORSPACE_RGB888) == false )
	{
		FREE_MEMORY(upszImgSourceBuffer);
		FREE_MEMORY(pszImgPath);
		return 1;
	}

	int nRet = image_util_decode_create(&dstHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(dstHandle,"image_util_decode_create");

	nRet = image_util_decode_set_input_path(dstHandle, OUTPUT_FILE_PATH);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_input_buffer", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));
	nRet = image_util_decode_set_colorspace(dstHandle, IMAGE_UTIL_COLORSPACE_RGB888);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_colorspace", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));

	nRet = image_util_decode_set_output_buffer(dstHandle, &upszImgSourceBuffer);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_output_buffer", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));

	nRet = image_util_decode_run(dstHandle, &nWidth, &nHeight, &unDecodeSize);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_run", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));

	nRet = image_util_decode_destroy(dstHandle);
	if ( nRet != IMAGE_UTIL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] image_util_decode_jpeg failed, error returned = %s\\n", __LINE__, API_NAMESPACE, ImageUtilGetError(nRet));
		FREE_MEMORY(upszImgSourceBuffer);
		FREE_MEMORY(pszImgPath);
		return 1;
	}

	if ( ImageUtilCheckFunction(upszImgSourceBuffer, nWidth, nHeight, unDecodeSize) == false )
	{
		FREE_MEMORY(upszImgSourceBuffer);
		FREE_MEMORY(pszImgPath);
		return 1;
	}

	FREE_MEMORY(upszImgSourceBuffer);
	FREE_MEMORY(pszImgPath);
	return 0;
}

/** @} */ //end of ctc-image-util
/** @} */ //end of ctc-image-util-testcases