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
#include "ITs-image-util-common.h"

/** @addtogroup itc-image-util
*  @ingroup itc
*  @{
*/

#define RESIZE_WIDTH	320
#define RESIZE_HEIGHT	240

static transformation_h g_hTransform = NULL;
static char* g_pszImgFile = "sample.jpg";
static char* g_pszImgPath = NULL;
static image_util_colorspace_e eSupportedColorspace = 0;
static gboolean g_bStartupRet = FALSE;
static gboolean g_bAsyncResult = FALSE;

typedef struct {
	unsigned char *buffer;
	unsigned long long size;
	unsigned long width;
	unsigned long height;
} itc_decoded_image;

static itc_decoded_image g_hDecodedImage = {NULL, 0, 0, 0};
static image_util_image_h g_hImage = NULL;


/**
* @function             ImageUtilSupportedColorspaceCb
* @description          Callback function which is invoked to set Colorspace.
* @parameter            image_util_colorspace_e eColorspace, void * user_data
* @return                    False
*/
static bool ImageUtilSupportedColorspaceCb( image_util_colorspace_e eColorspace, void * user_data)
{
	FPRINTF("[%s:%d] invoked (colorspace: %d)\\n", __FILE__, __LINE__, eColorspace);

	eSupportedColorspace = eColorspace;

	return false;
}

/**
* @function 		ImageUtilTransformCompleted2Cb
* @description	 	Callback Function to check complete transformation.
* @parameters		image_util_image_h hImageUtilDst, int nErrorCode, void *user_data
* @return 		NA
*/
static void ImageUtilTransformCompleted2Cb(image_util_image_h hImageUtilDst, int nErrorCode, void *user_data)
{
	int nRet = IMAGE_UTIL_ERROR_NONE;
	unsigned int nWidth  = 0;
	unsigned int nHeight  = 0;
	image_util_colorspace_e eColorspace = IMAGE_UTIL_COLORSPACE_I420;
	unsigned char *puszImageBuffer = NULL;
	size_t buffer_size = 0;

	FPRINTF("[%s:%d] invoked (error code: %d)\\n", __FILE__, __LINE__, nErrorCode);

	nRet = image_util_get_image(hImageUtilDst, &nWidth, &nHeight, &eColorspace, &puszImageBuffer, &buffer_size);
	if (nRet != IMAGE_UTIL_ERROR_NONE) {
		g_bAsyncResult = FALSE;
		FREE_MEMORY(puszImageBuffer);
		signal_for_async();
		FPRINTF("[Line : %d][%s] image_util_get_image failed. nRet = %d\\n", __LINE__, API_NAMESPACE, nRet);
		return;
	}

	FPRINTF("[%s:%d] image (w: %u, h: %u, eColorspace: %d, buf: %p, buf_size: %zu)\\n", __FILE__, __LINE__,
			nWidth, nHeight, eColorspace, puszImageBuffer, buffer_size);

	if (puszImageBuffer == NULL || buffer_size == 0) {
		g_bAsyncResult = FALSE;
		FREE_MEMORY(puszImageBuffer);
		signal_for_async();
		FPRINTF("[Line : %d][%s] Image buffer and buffer size are NULL. \\n", __LINE__, API_NAMESPACE);
		return;
	}

	if (nWidth != RESIZE_WIDTH && nHeight != RESIZE_HEIGHT) {
		g_bAsyncResult = FALSE;
		FREE_MEMORY(puszImageBuffer);
		signal_for_async();
		FPRINTF("[Line : %d][%s] width and height are not equal to default value. \\n", __LINE__, API_NAMESPACE);
		return;
	}

	g_bAsyncResult = TRUE;

	FREE_MEMORY(puszImageBuffer);
	signal_for_async();
}

static int ITc_decode_jpeg(void)
{
	int nRet = IMAGE_UTIL_ERROR_NONE;
	image_util_decode_h hImageDecoder = NULL;
	image_util_image_h hDecodedImage = NULL;

	nRet = image_util_decode_create(&hImageDecoder);
	if (nRet != IMAGE_UTIL_ERROR_NONE){
		image_util_decode_destroy(hImageDecoder);
		FPRINTF("[Line : %d][%s] image_util_decode_create failed.nRet = %d\\n", __LINE__, API_NAMESPACE, nRet);
		return nRet;
	}
	nRet = image_util_decode_set_input_path(hImageDecoder, g_pszImgPath);
	if (nRet != IMAGE_UTIL_ERROR_NONE){
		image_util_decode_destroy(hImageDecoder);
		FPRINTF("[Line : %d][%s] image_util_decode_set_input_path failed.nRet = %d\\n", __LINE__, API_NAMESPACE, nRet);
		return nRet;
	}
	nRet = image_util_decode_set_colorspace(hImageDecoder, eSupportedColorspace);
	if (nRet != IMAGE_UTIL_ERROR_NONE){
		image_util_decode_destroy(hImageDecoder);
		FPRINTF("[Line : %d][%s] image_util_decode_set_colorspace failed.nRet = %d\\n", __LINE__, API_NAMESPACE, nRet);
		return nRet;
	}
	nRet = image_util_decode_run2(hImageDecoder, &hDecodedImage);
	if (nRet != IMAGE_UTIL_ERROR_NONE){
		image_util_decode_destroy(hImageDecoder);
		FPRINTF("[Line : %d][%s] image_util_decode_run2 failed.nRet = %d\\n", __LINE__, API_NAMESPACE, nRet);
		return nRet;
	}
	image_util_decode_destroy(hImageDecoder);
	nRet = image_util_get_image(hDecodedImage, &g_hDecodedImage.width, &g_hDecodedImage.height, NULL, &g_hDecodedImage.buffer, &g_hDecodedImage.size);
	if (nRet != IMAGE_UTIL_ERROR_NONE){
		image_util_destroy_image(hDecodedImage);
		FPRINTF("[Line : %d][%s] image_util_get_image failed.nRet = %d\\n", __LINE__, API_NAMESPACE, nRet);
		return nRet;
	}

	image_util_destroy_image(hDecodedImage);

	return nRet;
}

/**
* @function 		ITs_image_util_image_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_image_util_image_startup(void)
{
	struct stat stBuff;
	int nImageSize = 6;

	if(stat(ERR_LOG, &stBuff) == 0)
	{
		remove(ERR_LOG);
	}

	#if DEBUG
		FPRINTF("[Line: %d][%s] TEST SUIT start-up: ITs_image_util_p\n", __LINE__, API_NAMESPACE);
	#endif

	int nRet = IMAGE_UTIL_ERROR_NONE;
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

	g_bStartupRet = FALSE;

	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
	{
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
		g_pszImgPath = (char*)malloc(strlen(pszValue) + strlen(g_pszImgFile) + nImageSize);
        	snprintf(g_pszImgPath, strlen(pszValue) + strlen(g_pszImgFile) + nImageSize, "%s/res/%s", pszValue, g_pszImgFile);
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

	image_util_foreach_supported_colorspace(IMAGE_UTIL_JPEG, ImageUtilSupportedColorspaceCb, NULL);

	nRet = ITc_decode_jpeg();
	if (nRet != IMAGE_UTIL_ERROR_NONE) {
		FPRINTF("[%s:%d] ITc_decode_jpeg failed (nRet: %d)\\n", __FILE__, __LINE__, nRet);
		return;
	}

	nRet = image_util_transform_create(&g_hTransform);
	if (nRet != IMAGE_UTIL_ERROR_NONE) {
		FPRINTF("[%s:%d] image_util_transform_create failed (nRet: %d)\\n", __FILE__, __LINE__, nRet);
		return;
	}

	g_bAsyncResult = FALSE;
	g_bStartupRet = TRUE;

	return;
}

/**
* @function 		ITs_image_util_image_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_image_util_image_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Image_Util_p\\n", __LINE__, API_NAMESPACE);
#endif
	if (g_hImage) {
		image_util_destroy_image(g_hImage);
		g_hImage = NULL;
	}
	if (g_hDecodedImage.buffer) {
		FREE_MEMORY(g_hDecodedImage.buffer);
		g_hDecodedImage.buffer = NULL;
	}
	if(g_pszImgPath) {
		FREE_MEMORY(g_pszImgPath);
		g_pszImgPath = NULL;
	}
	if(g_hTransform) {
		image_util_transform_destroy(g_hTransform);
		g_hTransform = NULL;
	}
	return;
}

/**
* @testcase				ITc_image_util_create_destroy_image_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Creates and destroys a image handle.
* @scenario				Creates and destroys a image handle.
* @apicovered				image_util_create_image, ge_util_destroy_image
* @passcase				image_util_create_image, ge_util_destroy_image return(s) 0
* @failcase				image_util_create_image, ge_util_destroy_image return(s) 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_image_util_create_destroy_image_p(void)
{
	START_TEST;

	int nRet = IMAGE_UTIL_ERROR_NONE;

	nRet = image_util_create_image(g_hDecodedImage.width, g_hDecodedImage.height, eSupportedColorspace, g_hDecodedImage.buffer, g_hDecodedImage.size, &g_hImage);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_create_image", ImageUtilGetError(nRet));


	return 0;
}

/**
* @testcase				ITc_image_util_clone_image_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Clones a image handle.
* @scenario				Creates the handle and Clones a image handle and compares the values and then destroys it.
* @apicovered				image_util_clone_image
* @passcase				image_util_clone_image return(s) 0
* @failcase				image_util_clone_image return(s) 1
* @precondition				image_util_create_image
* @postcondition			image_util_get_image
* */
int ITc_image_util_clone_image_p(void)
{
	START_TEST;

	int nRet = IMAGE_UTIL_ERROR_NONE;
	image_util_image_h hCloneImage = NULL;
	unsigned int nWidth  = 0;
	unsigned int nHeight  = 0;
	image_util_colorspace_e eColorspace = IMAGE_UTIL_COLORSPACE_I420;
	unsigned char *puszbuffer = NULL;
	size_t buffer_size = 0;

	nRet = image_util_create_image(g_hDecodedImage.width, g_hDecodedImage.height, eSupportedColorspace, g_hDecodedImage.buffer, g_hDecodedImage.size, &g_hImage);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_create_image", ImageUtilGetError(nRet));

	nRet = image_util_clone_image(g_hImage, &hCloneImage);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_create_image", ImageUtilGetError(nRet));

	nRet = image_util_get_image(hCloneImage, &nWidth, &nHeight, &eColorspace, &puszbuffer, &buffer_size);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_create_image", ImageUtilGetError(nRet), FREE_MEMORY(puszbuffer);image_util_destroy_image(hCloneImage));

	if(puszbuffer == NULL)
	{
		FPRINTF("\\n [Line : %d][%s] Buffer is NULL. \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	FREE_MEMORY(puszbuffer);

	if(buffer_size != g_hDecodedImage.size)
	{
		FPRINTF("\\n [Line : %d][%s] Buffer size set and get mismatch. \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(nWidth != g_hDecodedImage.width)
	{
		FPRINTF("\\n [Line : %d][%s] Width set and get mismatch. \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(nHeight != g_hDecodedImage.height)
	{
		FPRINTF("\\n [Line : %d][%s] Height set and get mismatch. \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(eColorspace != eSupportedColorspace)
	{
		FPRINTF("\\n [Line : %d][%s] Colorspace set and get values mismatch. \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

/**
* @testcase				ITc_image_util_get_image_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets the information from the image.
* @scenario				Creates the handle and Gets the information from the image and destroys it.
* @apicovered				image_util_get_image
* @passcase				image_util_get_image return(s) 0
* @failcase				image_util_get_image return(s) 1
* @precondition				image_util_create_image
* @postcondition			N/A
* */
int ITc_image_util_get_image_p(void)
{
	START_TEST;

	int nRet = IMAGE_UTIL_ERROR_NONE;
	unsigned int nWidth  = 0;
	unsigned int nHeight  = 0;
	image_util_colorspace_e eColorspace = IMAGE_UTIL_COLORSPACE_I420;
	unsigned char *puszbuffer = NULL;
	size_t buffer_size = 0;

	nRet = image_util_create_image(g_hDecodedImage.width, g_hDecodedImage.height, eSupportedColorspace, g_hDecodedImage.buffer, g_hDecodedImage.size, &g_hImage);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_create_image", ImageUtilGetError(nRet));

	nRet = image_util_get_image(g_hImage, &nWidth, &nHeight, &eColorspace, &puszbuffer, &buffer_size);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_create_image", ImageUtilGetError(nRet));

	if(puszbuffer == NULL)
	{
		FPRINTF("\\n [Line : %d][%s]image_util_get_image failed. Buffer is NULL. \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	FREE_MEMORY(puszbuffer);
	if(buffer_size != g_hDecodedImage.size)
	{
		FPRINTF("\\n [Line : %d][%s] image_util_get_image failed. Buffer size set and get mismatch. \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(nWidth != g_hDecodedImage.width)
	{
		FPRINTF("\\n [Line : %d][%s] image_util_get_image failed. Width set and get mismatch. \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(nHeight != g_hDecodedImage.height)
	{
		FPRINTF("\\n [Line : %d][%s] image_util_get_image failed. Height set and get mismatch. \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(eColorspace != eSupportedColorspace)
	{
		FPRINTF("\\n [Line : %d][%s] image_util_get_image failed. Colorspace set and get values mismatch. \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

/**
* @testcase				ITc_image_util_transform_run2_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Transforms an image with given transformation handle.
* @scenario				Creates the handle and Transforms an image with given transformation handle and then destroys it.
* @apicovered				image_util_transform_run2
* @passcase				image_util_transform_run2 return(s) 0
* @failcase				image_util_transform_run2 return(s) 1
* @precondition				Set the transformation information by calling image_util_transform_set_colorspace(), image_util_transform_set_resolution(), 
* @postcondition			N/A
* */
int ITc_image_util_transform_run2_p(void)
{
	START_TEST;

	int nRet = IMAGE_UTIL_ERROR_NONE;
	image_util_image_h hTransformedImage = NULL;

	nRet = image_util_create_image(g_hDecodedImage.width, g_hDecodedImage.height, eSupportedColorspace, g_hDecodedImage.buffer, g_hDecodedImage.size, &g_hImage);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_create_image", ImageUtilGetError(nRet));

	nRet = image_util_transform_set_resolution(g_hTransform, RESIZE_WIDTH, RESIZE_HEIGHT);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_set_resolution", ImageUtilGetError(nRet));

	nRet = image_util_transform_run2(g_hTransform, g_hImage, &hTransformedImage);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_run2", ImageUtilGetError(nRet));

	nRet = image_util_destroy_image(hTransformedImage);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_destroy_image", ImageUtilGetError(nRet));

	return 0;
}

/**
* @testcase				ITc_image_util_transform_run2_async_p
* @since_tizen				5.5
* @author				SRID(p.chauhan)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Transforms an image with given transformation handle.
* @scenario				Creates the handle and Transforms an image with given transformation handle then destroys it.
* @apicovered				image_util_transform_run2_async
* @passcase				image_util_transform_run2_async return(s) 0
* @failcase				image_util_transform_run2_async return(s) 1
* @precondition				Set the transformation information by calling image_util_transform_set_colorspace(), image_util_transform_set_resolution(), 
* @postcondition			N/A
* */
int ITc_image_util_transform_run2_async_p(void)
{
	START_TEST;

	int nRet = IMAGE_UTIL_ERROR_NONE;

	nRet = image_util_create_image(g_hDecodedImage.width, g_hDecodedImage.height, eSupportedColorspace,
			g_hDecodedImage.buffer, g_hDecodedImage.size, &g_hImage);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_create_image", ImageUtilGetError(nRet));

	nRet = image_util_transform_set_resolution(g_hTransform, RESIZE_WIDTH, RESIZE_HEIGHT);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_set_resolution", ImageUtilGetError(nRet));

	g_bAsyncResult = FALSE;
	nRet = image_util_transform_run2_async(g_hTransform, g_hImage, ImageUtilTransformCompleted2Cb, NULL);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_run2_async", ImageUtilGetError(nRet));

	wait_for_async();
	if(g_bAsyncResult != TRUE)
	{
		FPRINTF("\\n [Line : %d][%s]ImageUtilTransformCompleted2Cb Failed. Callback Not Invoked. \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

/** @} */
/** @} */
