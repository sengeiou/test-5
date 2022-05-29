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

//& set: ImageUtil
bool g_bImageUtilSupportedJpegCallback;
bool g_bImageUtilEncodeCompletedCallback;
bool g_bImageUtilDecodeCompletedCallback;
bool g_bImageUtilForeachSupporedColorspace;
bool g_bImageUtilEncodeToFileCompletedCallback;
bool g_bImageUtilEncodeToBufferCompletedCallback;
static image_util_colorspace_e eSupportedColorspace = 0;

image_util_colorspace_e  eImageUtilColorspace[] = {
	IMAGE_UTIL_COLORSPACE_RGB888,
	IMAGE_UTIL_COLORSPACE_YV12, 
	IMAGE_UTIL_COLORSPACE_I420, 
	IMAGE_UTIL_COLORSPACE_ARGB8888, 
	IMAGE_UTIL_COLORSPACE_BGRA8888,
	IMAGE_UTIL_COLORSPACE_RGBA8888
};
int enum_size = sizeof(eImageUtilColorspace) / sizeof(eImageUtilColorspace[0]);
int enum_counter = 0;

typedef struct {
	unsigned char *pszBuffer;
	size_t tBufferSize;
} g_sBufferEncodedImage;

static int JpegColorspace[] = {
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_YUV420 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUV422 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_I420 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_NV12 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_UYVY */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUYV */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_RGB565 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_RGB888 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_ARGB8888 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_BGRA8888 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_RGBA8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_BGRX8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV21 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV16 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV61 */
};

static int PngColorspace[] = {
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUV420 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUV422 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_I420 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV12 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_UYVY */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUYV */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_RGB565 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_RGB888 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_ARGB8888 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_BGRA8888 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_RGBA8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_BGRX8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV21 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV16 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV61 */
};

static int GifColorspace[] = {
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUV420 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUV422 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_I420 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV12 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_UYVY */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUYV */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_RGB565 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_RGB888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_ARGB8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_BGRA8888 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_RGBA8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_BGRX8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV21 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV16 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV61 */
};

static int BmpColorspace[] = {
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUV420 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUV422 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_I420 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV12 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_UYVY */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_YUYV */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_RGB565 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_RGB888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_ARGB8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_BGRA8888 */
	IMAGE_UTIL_ERROR_NONE,						/* IMAGE_UTIL_COLORSPACE_RGBA8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_BGRX8888 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV21 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV16 */
	IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT,	/* IMAGE_UTIL_COLORSPACE_NV61 */
};

/**
* @function 		ITs_image_util_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_image_util_startup(void)
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
* @function 		ITs_image_util_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_image_util_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Image_Util_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function			ImageUtilSupportedJpegCallback
* @description		Called once for each supported JPEG encode/decode colorspace.
* @parameter[IN]	The interrupted error code 
* @parameter[IN]	The user data passed from the for each function			
* @return			NA
*/
bool ImageUtilSupportedJpegCallback(image_util_colorspace_e  Colourspace,  void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] ImageUtilSupportedJpegCallback is called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bImageUtilSupportedJpegCallback = true;
	if ( g_mainloop )
	{
		g_main_loop_quit(g_mainloop);
		g_main_loop_unref(g_mainloop);
		g_mainloop = NULL;
	}
	return false;
}

/**
* @function			Image_util_transform_completed_CallBack
* @description		Called when transform is finished just before returning the output.
* @parameter[IN]	The error code of image-util transfrom
* @parameter[IN]	Media packet handle	
* @parameter[IN]	The user data passed from the for each function
* @return			NA
*/
void Image_util_transform_completed_CallBack(media_packet_h *packet, int error_code, void *user_data)
{
	g_bImageUtilSupportedJpegCallback = true;
#if DEBUG
	FPRINTF("[Line : %d][%s] Image_util_transform_completed_CallBack is called\\n", __LINE__, API_NAMESPACE);
#endif	
	if ( g_mainloop )
	{
		g_main_loop_quit(g_mainloop);
		g_main_loop_unref(g_mainloop);
		g_mainloop = NULL;
	}
}

/**
* @function			Image_util_supported_colorspace_CallBack
* @description		Called once for each supported image encode/decode colorspace.
* @parameter[IN]	colorspace The colorspace
* @return		NA
*/
void Image_util_supported_colorspace_CallBack(image_util_colorspace_e colorspace, void *user_data)
{
	g_bImageUtilForeachSupporedColorspace = true;
	eSupportedColorspace = colorspace;
#if DEBUG
	FPRINTF("[Line : %d][%s] Image_util_supported_colorspace_CallBack is called\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function			Image_util_encode_to_buffer_completed_Callback
* @description		Callback to encode the image to a buffer with the given encode handle asynchronously.
* @parameter[IN]	image_util_error_e error, unsigned char *buffer, size_t buffer_size, void *user_data
* @return		NA
*/
static void Image_util_encode_to_buffer_completed_Callback(image_util_error_e error, unsigned char *buffer, size_t buffer_size, void *user_data)
{
#if DEBUG
	FPRINTF("Image_util_encode_to_buffer_completed_Callback invoked\\n");
#endif
	g_sBufferEncodedImage *buf_enc = (g_sBufferEncodedImage *)user_data;

	if (buffer && buffer_size > 0) {
		buf_enc->pszBuffer = calloc(1, buffer_size);
		if (!buf_enc->pszBuffer) {
			FPRINTF("[%d:%s] Memory allocation error\\n", __LINE__, __FUNCTION__);
			signal_for_async();
			return;
		}
		memcpy(buf_enc->pszBuffer, buffer, buffer_size);
		buf_enc->tBufferSize = buffer_size;
		g_bImageUtilEncodeToBufferCompletedCallback = true;
	}

	signal_for_async();
}

/**
* @function			Image_util_encode_to_file_completed_Callback
* @description		Callback to encode the image to a file with the given encode handle asynchronously.
* @parameter[IN]	image_util_error_e error, void *user_data
* @return		NA
*/
static void Image_util_encode_to_file_completed_Callback(image_util_error_e error, void *user_data)
{
#if DEBUG
	FPRINTF("Image_util_encode_to_file_completed_Callback invoked\\n");
#endif
	g_bImageUtilEncodeToFileCompletedCallback = true;
	signal_for_async();
}

//& purpose: Creates and destroy a handle to image-util transform. 
//& type: auto
/**
* @testcase   			ITc_image_util_transform_create_destroy_p
* @since_tizen			2.3
* @author             	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Create and Destroy a  handle to image-util transform.  
* @scenario				Creates a handle to image-util transform\n
*						Destroy handle to image-util transform.
* @apicovered			image_util_transform_create, image_util_transform_destroy
* @passcase				When image_util_transform_create and  image_util_transform_destory are successful.
* @failcase				If target API image_util_transform_create or image_util_transform_destory or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_transform_create_destroy_p(void)
{
	START_TEST;

	transformation_h stHandle = NULL;
	int nRet = image_util_transform_create(&stHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(stHandle,"image_util_transform_create");

	//Target API
	nRet = image_util_transform_destroy(stHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_destroy", ImageUtilGetError(nRet));

	return 0;
}

//& purpose: To Set and get the information of the converting
//& type: auto
/**
* @testcase   			ITc_image_util_transform_set_get_colorspace_p
* @since_tizen			2.3
* @author             	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To Set and get the information of the converting
* @scenario				Creates a handle to image-util transform\n
*						To Set the information of the converting\n
*						To get the information of the converting\n
*						Destroy handle to image-util transform.
* @apicovered			image_util_transform_set_crop_area,image_util_transform_get_colorspace,image_util_transform_set_colorspace
* @passcase				When image_util_transform_get_colorspace and  image_util_transform_set_colorspace are successful.
* @failcase				If target API image_util_transform_get_colorspace or image_util_transform_set_colorspace or any precondition API fails.
* @precondition			image_util_transform_create, image_util_transform_set_crop_area must be called
* @postcondition		NA
*/
int ITc_image_util_transform_set_get_colorspace_p(void)
{
	START_TEST;

	transformation_h stHandle;
	image_util_colorspace_e setImageUtilColorspace = 0;
	image_util_colorspace_e getImageUtilColorspace;

	int nRet = image_util_transform_create(&stHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(stHandle,"image_util_transform_create");

	//Target API
	nRet = image_util_transform_set_colorspace(stHandle, setImageUtilColorspace);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_set_colorspace", ImageUtilGetError(nRet), image_util_transform_destroy(stHandle));

	//Target API
	nRet = image_util_transform_get_colorspace(stHandle, &getImageUtilColorspace);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_get_colorspace", ImageUtilGetError(nRet), image_util_transform_destroy(stHandle));

	if( getImageUtilColorspace != setImageUtilColorspace)
	{
		FPRINTF("\\n [Line : %d][%s] colorspace set and get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = image_util_transform_destroy(stHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_destroy", ImageUtilGetError(nRet));

	return 0;
}

//& purpose: To Set and Get the information of the cropping
//& type: auto
/**
* @testcase   			ITc_image_util_transform_set_get_crop_area_p
* @since_tizen			2.3
* @author             	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To Set and Get the information of the cropping
* @scenario				Create a handle to image-util transform\n
*						Set the startX startY endX endY positions of cropped image buffer\n
*						Get the startX startY endX endY positions of cropped image buffer\n
*						Destroy handle to image-util transform.
* @apicovered			image_util_transform_set_crop_area, image_util_transform_set_crop_area
* @passcase				When image_util_transform_set_crop_area and  image_util_transform_set_crop_area are successful.
* @failcase				If target API image_util_transform_set_crop_area or image_util_transform_set_crop_area or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_transform_set_get_crop_area_p(void)
{
	START_TEST;

	unsigned int unStartX = 9, unStartY = 9, unEndX = 16, unEndY = 16;
	unsigned int unGetStartX = 0, unGetStartY = 0, unGetEndX = 0, unGetEndY = 0;
	transformation_h stHandle;

	int nRet = image_util_transform_create(&stHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(stHandle,"image_util_transform_create");

	//Target API
	nRet = image_util_transform_set_crop_area(stHandle, unStartX, unStartY, unEndX, unEndY );
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_set_crop_area", ImageUtilGetError(nRet), image_util_transform_destroy(stHandle));

	//Target API
	nRet = image_util_transform_get_crop_area(stHandle, &unGetStartX, &unGetStartY, &unGetEndX, &unGetEndY );
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_get_crop_area", ImageUtilGetError(nRet), image_util_transform_destroy(stHandle));

	if( (unStartX != unGetStartX) || (unStartY != unGetStartY) || (unEndX != unGetEndX) || (unEndY != unGetEndY) )
	{
		FPRINTF("\\n [Line : %d][%s] crop_area set and get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = image_util_transform_destroy(stHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_destroy", ImageUtilGetError(nRet));

	return 0;
}

//& purpose: To Set and Get the resolution of the image buffer
//& type: auto
/**
* @testcase				ITc_image_util_transform_set_get_resolution_p
* @since_tizen			2.3
* @author					SRID(sk.roy)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To Set and Get the resolution of the image buffer 
* @scenario				Create a handle to image-util transform\n
*						Set the width and height of source image buffer\n
*						Get the width and height of source image buffer\n
*						Destroy handle to image-util transform.
* @apicovered			image_util_transform_set_resolution, image_util_transform_get_resolution
* @passcase				When image_util_transform_set_resolution and  image_util_transform_get_resolution are successful.
* @failcase				If target API image_util_transform_set_resolution or image_util_transform_get_resolution or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_transform_set_get_resolution_p(void)
{
	START_TEST;

	unsigned int unHeight = 16,unWidth = 9;
	unsigned int unGetHeight = 0,unGetWidth = 0;
	transformation_h stHandle;

	int nRet = image_util_transform_create(&stHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(stHandle,"image_util_transform_create");

	//Target API
	nRet = image_util_transform_set_resolution(stHandle, unWidth, unHeight );
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_set_resolution", ImageUtilGetError(nRet), image_util_transform_destroy(stHandle));

	//Target API
	nRet = image_util_transform_get_resolution(stHandle, &unGetWidth, &unGetHeight );
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_get_resolution", ImageUtilGetError(nRet), image_util_transform_destroy(stHandle));
	if( (unWidth != unGetWidth) || (unHeight != unGetHeight) )
	{
		FPRINTF("\\n [Line : %d][%s] resolution set and get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = image_util_transform_destroy(stHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_destroy", ImageUtilGetError(nRet));

	return 0;
}

//& purpose: To set and get the information of the rotating
//& type: auto
/**
* @testcase   			ITc_image_util_transform_set_get_rotation_p
* @since_tizen			2.3
* @author             	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To set and get the information of the rotating 
* @scenario				Create a handle to image-util transform\n
*						Set rotation value of image buffer\n
*						Get rotation value of image buffer\n
*						Destroy handle to image-util transform.
* @apicovered			image_util_transform_set_rotation, image_util_transform_get_rotation
* @passcase				When image_util_transform_set_rotation and  image_util_transform_get_rotation are successful.
* @failcase				If target API image_util_transform_set_rotation or image_util_transform_get_rotation or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_transform_set_get_rotation_p(void)
{
	START_TEST;

	transformation_h stHandle;
	image_util_rotation_e eImageUtilRotaion[] = {IMAGE_UTIL_ROTATION_90, 
		IMAGE_UTIL_ROTATION_180,
		IMAGE_UTIL_ROTATION_270, 
		IMAGE_UTIL_ROTATION_NONE, 
		IMAGE_UTIL_ROTATION_FLIP_HORZ, 
		IMAGE_UTIL_ROTATION_FLIP_VERT};
	int enum_size1 = sizeof(eImageUtilRotaion) / sizeof(eImageUtilRotaion[0]);
	int enum_counter1 = 0;

	int nRet = image_util_transform_create(&stHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(stHandle,"image_util_transform_create");

	for ( enum_counter1=0; enum_counter1<enum_size1; enum_counter1++)
	{
		image_util_rotation_e eGetImageUtilRotaion;
		
		//Target API
		nRet = image_util_transform_set_rotation(stHandle, eImageUtilRotaion[enum_counter1] );
		if ( nRet != IMAGE_UTIL_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] image_util_transform_set_rotation failed, error returned = %s for rotation %s\\n", __LINE__, API_NAMESPACE, ImageUtilGetError(nRet), ImageUtilRotaion(eImageUtilRotaion[enum_counter1]));
			image_util_transform_destroy(stHandle);
			return 1;
		}
		else
		{
#if DEBUG
			FPRINTF("[Line : %d][%s] image_util_transform_set_rotation failed is successful\\n", __LINE__, API_NAMESPACE);
#endif
		}

		//Target API
		nRet = image_util_transform_get_rotation(stHandle, &eGetImageUtilRotaion );
		if ( nRet != IMAGE_UTIL_ERROR_NONE )
		{		
			FPRINTF("[Line : %d][%s] image_util_transform_get_rotation failed, error returned = %s for rotation %s\\n", __LINE__, API_NAMESPACE, ImageUtilGetError(nRet), ImageUtilRotaion(eImageUtilRotaion[enum_counter1]));
			image_util_transform_destroy(stHandle);
			return 1;
		}
		else
		{
#if DEBUG
			FPRINTF("[Line : %d][%s] image_util_transform_get_rotation is successful\\n", __LINE__, API_NAMESPACE);
#endif	
		}
		
		if( eImageUtilRotaion[enum_counter1] != eGetImageUtilRotaion )
		{
			FPRINTF("\\n [Line : %d][%s] rotation set and get values mismatch\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	nRet = image_util_transform_destroy(stHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_destroy", ImageUtilGetError(nRet));

	return 0;
}

//& purpose: To Transform the image for given image-util handle. 
//& type: auto
/**
* @testcase   			ITc_image_util_transform_run_p
* @since_tizen			2.3
* @author             	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To Transform the image for given image-util handle.
* @scenario				Create a handle to image-util transform\n
*						Media format is to be called\n
*						image_util_transform_completed_cb callback is invoked\n
*						Get rotation value of image buffer\n
*						Destroy handle to image-util transform.
* @apicovered			image_util_transform_run
* @passcase				When image_util_transform_run, media_format_create, media_format_set_video_mime, media_format_set_video_width
*						media_format_set_video_height, media_format_set_video_avg_bps, media_format_set_video_max_bps,media_packet_create_alloc
*						image_util_transform_set_resolution, media_packet_destroy,image_util_transform_destroy	is successful.
* @failcase				If target API image_util_transform_run fails or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_transform_run_p(void)
{
	START_TEST;

	transformation_h pstHandle;
	media_format_h hfmt;
	media_packet_h hpacket ;
	int nWidth = 320, nHeight = 240;
	int nAvgBps = 10000000;
	int nMaxBps = 20000000;
	unsigned int unHeight = 16, unWidth = 9;

	int nRet = image_util_transform_create(&pstHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(pstHandle, "image_util_transform_create");

	nRet = media_format_create(&hfmt);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaFormatGetError(nRet), image_util_transform_destroy(pstHandle));

	nRet = media_format_set_video_mime(hfmt, MEDIA_FORMAT_I420);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet), image_util_transform_destroy(pstHandle));

	nRet = media_format_set_video_width(hfmt, nWidth);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_width", MediaFormatGetError(nRet), image_util_transform_destroy(pstHandle));

	nRet = media_format_set_video_height(hfmt, nHeight);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_height", MediaFormatGetError(nRet), image_util_transform_destroy(pstHandle));

	nRet = media_format_set_video_avg_bps(hfmt, nAvgBps);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_avg_bps", MediaFormatGetError(nRet), image_util_transform_destroy(pstHandle));

	nRet = media_format_set_video_max_bps(hfmt, nMaxBps);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_max_bps", MediaFormatGetError(nRet), image_util_transform_destroy(pstHandle));

	nRet = media_packet_create_alloc(hfmt, (media_packet_finalize_cb)NULL, NULL, &hpacket);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_create_alloc", MediaToolsGetError(nRet), image_util_transform_destroy(pstHandle));

	nRet = image_util_transform_set_resolution(pstHandle, unWidth, unHeight);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_set_resolution", ImageUtilGetError(nRet), media_format_unref(hfmt);image_util_transform_destroy(pstHandle));

	g_bImageUtilSupportedJpegCallback = false;
	nRet = image_util_transform_run(pstHandle, hpacket, (image_util_transform_completed_cb) Image_util_transform_completed_CallBack, NULL);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_run", ImageUtilGetError(nRet), media_format_unref(hfmt);image_util_transform_destroy(pstHandle));

	wait_for_async();

	if ( !g_bImageUtilSupportedJpegCallback )
	{
		FPRINTF("[Line : %d][%s] Image_util_transform_completed_CallBack failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		media_format_unref(hfmt);
		image_util_transform_destroy(pstHandle);
		return 1;
	}
	else
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] image_util_transform_run is successful\\n", __LINE__, API_NAMESPACE);
#endif
	}

	nRet = media_format_unref(hfmt);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaFormatGetError(nRet), image_util_transform_destroy(pstHandle));

	nRet = media_packet_destroy(hpacket);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_destroy", MediaToolsGetError(nRet), image_util_transform_destroy(pstHandle));

	nRet = image_util_transform_destroy(pstHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_transform_destroy", ImageUtilGetError(nRet));

	return 0;
}

//& purpose: To extract representative colour from an image buffer.
//& type: auto
/**
* @testcase   			ITc_image_util_extract_color_from_memory_p
* @since_tizen 			3.0
* @author             	SRID(arvind.ky)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			To extract representative colour from an image buffer.
* @scenario				image_util_decode_jpeg \n
*						image_util_extract_color_from_memory\n
* @apicovered			image_util_decode_jpeg, image_util_extract_color_from_memory
* @passcase				When image_util_extract_color_from_memory is successful.
* @failcase				If target api image_util_extract_color_from_memory fails.
* @precondition			NA
* @postcondition		NA
*/

int ITc_image_util_extract_color_from_memory_p(void)
{
    unsigned char *puszImageSourceBuffer = NULL;
    unsigned char rgb_r, rgb_g, rgb_b;
	unsigned long long unDecodeSize = 0;
	image_util_decode_h dstHandle = NULL;
	image_util_image_h stDecodedImage = NULL;
	unsigned long nDecWidth = 0;
	unsigned long nDecHeight = 0;

	char pPath[PATH_LEN] = {0,};
	if ( false == ImageUtilAppendToAppDataPath(SAMPLE_FILE_PATH, pPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = image_util_decode_create(&dstHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(dstHandle,"image_util_decode_create");

	nRet = image_util_decode_set_input_path(dstHandle, pPath);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_input_path", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));

	nRet = image_util_decode_set_colorspace(dstHandle, IMAGE_UTIL_COLORSPACE_RGB888);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_colorspace", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));

	nRet = image_util_decode_run2(dstHandle, &stDecodedImage);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_run2", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));
	CHECK_HANDLE_CLEANUP(stDecodedImage,"image_util_decode_run2", image_util_decode_destroy(dstHandle));

	nRet = image_util_decode_destroy(dstHandle);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage));

	nRet = image_util_get_image(stDecodedImage, &nDecWidth, &nDecHeight, NULL, &puszImageSourceBuffer, &unDecodeSize);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_get_image", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage));
	CHECK_HANDLE_CLEANUP(puszImageSourceBuffer, "image_util_get_image", image_util_destroy_image(stDecodedImage));

	nRet = image_util_destroy_image(stDecodedImage);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_destroy_image", ImageUtilGetError(nRet));

	//target api
	nRet = image_util_extract_color_from_memory(puszImageSourceBuffer, (int)nDecWidth, (int)nDecHeight, &rgb_r, &rgb_g, &rgb_b);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_extract_color_from_memory", ImageUtilGetError(nRet), FREE_MEMORY(puszImageSourceBuffer));

	FREE_MEMORY(puszImageSourceBuffer);

	return 0;
}
//& purpose: To create and destroy a handle to image util decoding. 
//& type: auto
/**
* @testcase   			ITc_image_util_decode_create_destroy_p
* @since_tizen			3.0
* @author             	SRID(manu.tiwari)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			To create and destroy a handle to image util decoding.
* @scenario				Get the size of buffer\n
*						Allocate it to image-util buffer
* @apicovered			image_util_decode_create,image_util_decode_destroy
* @passcase				When image_util_decode_create & image_util_decode_destroy is successful.
* @failcase				If target API image_util_decode_create or image_util_decode_destroy fails or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_decode_create_destroy_p(void)
{
	START_TEST;
	image_util_decode_h stHandle = NULL;
	//target api
	int nRet = image_util_decode_create(&stHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(stHandle,"image_util_decode_create");
	//target api
	nRet = image_util_decode_destroy(stHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet));
	return 0;
}
//& purpose: To set the input file path from which to decode. 
//& type: auto
/**
* @testcase			ITc_image_util_decode_set_input_path_p
* @since_tizen			3.0
* @author				SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 				auto
* @description			To set the input file path from which to decode.
* @scenario				Get the size of buffer\n
*						Allocate it to image-util buffer
* @apicovered			image_util_decode_set_input_path
* @passcase				When ITc_image_util_decode_set_input_path_p is successful.
* @failcase				If target API ITc_image_util_decode_set_input_path_p fails or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_decode_set_input_path_p(void)
{
	START_TEST;

	image_util_decode_h stHandle = NULL;
	char *eImageUtilType[5] = {
		"Image_01.jpg",
		"sample.png",
		"sample.gif",
		"sample.bmp",
		"sample.heic"
	};
	int enum_size = 5;
	int enum_counter = 0;
	for(enum_counter = 0;enum_counter<enum_size;enum_counter++)
	{
		int nRet = image_util_decode_create(&stHandle);
		PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_create", ImageUtilGetError(nRet));
		CHECK_HANDLE(stHandle,"image_util_decode_create");

		char pPath[PATH_LEN] = {0,};
		if ( false == ImageUtilAppendToAppDataPath(eImageUtilType[enum_counter], pPath) )
		{
			FPRINTF("[Line : %d][%s] unable to get the app data path of file %s\\n", __LINE__, API_NAMESPACE,eImageUtilType[enum_counter]);
			image_util_decode_destroy(stHandle);
			return 1;
		}
		//target api
		nRet = image_util_decode_set_input_path(stHandle, pPath);
		PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_input_path", ImageUtilGetError(nRet), image_util_decode_destroy(stHandle));

		nRet = image_util_decode_destroy(stHandle);
		PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet));
	}
	return 0;
}
//& purpose: To create a handle to image util decoding.
//& type: auto
/**
* @testcase				ITc_image_util_decode_set_input_buffer_p
* @since_tizen			3.0
* @author				SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 				auto
* @description			To set the input buffer to image util decoding.
* @scenario				To set the input buffer to image util decoding.
* @apicovered			image_util_decode_set_input_buffer
* @passcase				When image_util_decode_set_input_buffer is successful.
* @failcase				If target API image_util_decode_set_input_buffer fails or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_decode_set_input_buffer_p(void)
{
	START_TEST;

	image_util_encode_h stEncHandle = NULL;
	image_util_decode_h stDecHandle = NULL;
	image_util_decode_h stDecodedHandle = NULL;
	image_util_image_h stDecodedImage = NULL;
	unsigned char *puszImageOutputbuffer = NULL;
	unsigned long long nDecsize;
	unsigned long nDecWidth;
	unsigned long nDecHeight;
	unsigned char *pszBuffer = NULL;
	size_t tBufferSize;

	int nRet = image_util_foreach_supported_colorspace(IMAGE_UTIL_JPEG,(image_util_supported_colorspace_cb)Image_util_supported_colorspace_CallBack , NULL);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_foreach_supported_colorspace", ImageUtilGetError(nRet));
	if ( !g_bImageUtilForeachSupporedColorspace )
	{
		FPRINTF("[Line : %d][%s] image_util_foreach_supported_colorspace failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = image_util_decode_create(&stDecHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(stDecHandle,"image_util_decode_create");

	char pPath[PATH_LEN] = {0,};
	if ( false == ImageUtilAppendToAppDataPath(SAMPLE_FILE_PATH, pPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = image_util_decode_set_input_path(stDecHandle, pPath);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_input_path", ImageUtilGetError(nRet), image_util_decode_destroy(stDecHandle));

	nRet = image_util_decode_set_colorspace(stDecHandle, eSupportedColorspace);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_colorspace", ImageUtilGetError(nRet), image_util_decode_destroy(stDecHandle));

	nRet = image_util_decode_run2(stDecHandle, &stDecodedImage);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_run2", ImageUtilGetError(nRet), image_util_decode_destroy(stDecHandle));
	CHECK_HANDLE_CLEANUP(stDecodedImage,"image_util_decode_run2", image_util_decode_destroy(stDecHandle));

	nRet = image_util_decode_destroy(stDecHandle);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage));

	nRet = image_util_get_image(stDecodedImage, &nDecWidth, &nDecHeight, NULL, &puszImageOutputbuffer, &nDecsize);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_get_image", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage));
	CHECK_HANDLE_CLEANUP(puszImageOutputbuffer, "image_util_get_image", image_util_destroy_image(stDecodedImage));

	nRet = image_util_destroy_image(stDecodedImage);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_destroy_image", ImageUtilGetError(nRet));

	nRet = image_util_create_image(nDecWidth, nDecHeight, eSupportedColorspace, puszImageOutputbuffer, nDecsize, &stDecodedImage);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_create_image", ImageUtilGetError(nRet));
	CHECK_HANDLE(stDecodedImage,"image_util_create_image");

	nRet = image_util_encode_create(IMAGE_UTIL_JPEG, &stEncHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE_CLEANUP(stEncHandle,"image_util_encode_create", image_util_destroy_image(stDecodedImage));

	nRet = image_util_encode_run_to_buffer(stEncHandle, stDecodedImage, &pszBuffer, &tBufferSize);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_run_to_buffer", ImageUtilGetError(nRet), image_util_encode_destroy(stEncHandle);image_util_destroy_image(stDecodedImage));
	CHECK_HANDLE_CLEANUP(pszBuffer,"image_util_encode_run_to_buffer", image_util_encode_destroy(stEncHandle);image_util_destroy_image(stDecodedImage));

	nRet = image_util_encode_destroy(stEncHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_destroy", ImageUtilGetError(nRet));

	nRet = image_util_destroy_image(stDecodedImage);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_destroy_image", ImageUtilGetError(nRet));

	nRet = image_util_decode_create(&stDecodedHandle);
        PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_create", ImageUtilGetError(nRet));
        CHECK_HANDLE(stDecodedHandle,"image_util_decode_create");

	//Target API
	nRet = image_util_decode_set_input_buffer(stDecodedHandle, pszBuffer, tBufferSize);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_input_buffer", ImageUtilGetError(nRet), image_util_decode_destroy(stDecodedHandle));

	nRet = image_util_decode_destroy(stDecodedHandle);
        PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet));

	return 0;
}

//& purpose: To create and destroy a handle to image util decoding.
//& type: auto
/**
* @testcase			ITc_image_util_encode_create_destroy_p
* @since_tizen			3.0
* @author             	SRID(manu.tiwari)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			To create and destroy a handle to image util encoding.
* @scenario				To create and destroy a handle to image util encoding
* @apicovered			image_util_encode_create,image_util_encode_destroy
* @passcase				When image_util_encode_create and image_util_encode_destroy is successful.
* @failcase				If target API image_util_encode_create or image_util_encode_destroy fails or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_encode_create_destroy_p(void)
{
	START_TEST;

	image_util_encode_h stHandle = NULL;
	image_util_type_e eImageUtilType[] =
	{
		IMAGE_UTIL_PNG,  /**< Image format PNG */
		IMAGE_UTIL_GIF,  /**< Image format GIF */
		IMAGE_UTIL_JPEG,
		IMAGE_UTIL_BMP,  /**< Image format BMP */
		IMAGE_UTIL_WEBP,  /**< Image format WEBP */
	};
	int enum_size = sizeof(eImageUtilType) / sizeof(eImageUtilType[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++)
	{
		//target api
		int nRet = image_util_encode_create(eImageUtilType[enum_counter], &stHandle);
		PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_create", ImageUtilGetError(nRet));
		CHECK_HANDLE(stHandle,"image_util_encode_create");
		//target api
		nRet = image_util_encode_destroy(stHandle);
		PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_destroy", ImageUtilGetError(nRet));
	}

	return 0;
}

//& purpose: To create a handle to image util decoding. 
//& type: auto
/**
* @testcase   			ITc_image_util_encode_set_png_compression_p
* @since_tizen			3.0
* @author				SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 				auto
* @description			To set png compression to image util decoding. 
* @scenario				To set png compression to image util decoding
* @apicovered			image_util_encode_set_png_compression
* @passcase				When image_util_encode_set_png_compression is successful.
* @failcase				If target API image_util_encode_set_png_compressionn fails or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_encode_set_png_compression_p(void)
{
	START_TEST;
	image_util_encode_h stHandle = NULL;

	int nRet = image_util_encode_create(IMAGE_UTIL_PNG, &stHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(stHandle,"image_util_encode_create");

	//target api
	nRet = image_util_encode_set_png_compression(stHandle, IMAGE_UTIL_PNG_COMPRESSION_6);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_set_png_compression", ImageUtilGetError(nRet), image_util_encode_destroy(stHandle));

	nRet = image_util_encode_destroy(stHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_destroy", ImageUtilGetError(nRet));

	return 0;
}

//& purpose: To set lossless compression of WEBP images.
//& type: auto
/**
* @testcase   			ITc_image_util_encode_set_webp_lossless_p
* @since_tizen			6.0
* @author				SRID(priya.kohli)
* @reviewer			SRID(shobhit.v)
* @type 				auto
* @description			To set lossless compression of WEBP images.
* @scenario				Sets lossless compression of WEBP images.
* @apicovered			image_util_encode_set_webp_lossless
* @passcase				When image_util_encode_set_webp_lossless is successful.
* @failcase				If target API image_util_encode_set_webp_lossless fails or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_encode_set_webp_lossless_p(void)
{
	START_TEST;
	image_util_encode_h stHandle = NULL;

	int nRet = image_util_encode_create(IMAGE_UTIL_WEBP, &stHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(stHandle,"image_util_encode_create");

	nRet = image_util_encode_set_webp_lossless(stHandle, true);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_set_webp_lossless", ImageUtilGetError(nRet), image_util_encode_destroy(stHandle));

	nRet = image_util_encode_set_webp_lossless(stHandle, false);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_set_webp_lossless", ImageUtilGetError(nRet), image_util_encode_destroy(stHandle));

	nRet = image_util_encode_destroy(stHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_destroy", ImageUtilGetError(nRet));

	return 0;
}

//& purpose: To decode the image with the given decode handle.
//& type: auto
/**
* @testcase   			ITc_image_util_decode_run2_p
* @since_tizen			5.5
* @author				SRID(karanam.s)
* @reviewer			SRID(manoj.g2)
* @type 				auto
* @description			To decode the image with the given decode handle.
* @scenario				To decode the image with the given decode handle.
* @apicovered			image_util_decode_run2
* @passcase				When  image_util_decode_run2 is successful.
* @failcase				If target API  image_util_decode_run2 fails or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_decode_run2_p(void)
{
	START_TEST;
	unsigned char *puszImageOutputBuffer = NULL;
	image_util_decode_h dstHandle = NULL;
	image_util_image_h stDecodedImage = NULL;

	int nRet = image_util_decode_create(&dstHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(dstHandle,"image_util_decode_create");

	char pPath[PATH_LEN] = {0,};
	if ( false == ImageUtilAppendToAppDataPath(SAMPLE_FILE_PATH, pPath) )
	{
	FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
	return 1;
	}

	nRet = image_util_decode_set_input_path(dstHandle, pPath);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_input_path", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));

	//target api
	nRet = image_util_decode_run2(dstHandle, &stDecodedImage);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_run2", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));
	CHECK_HANDLE_CLEANUP(stDecodedImage,"image_util_decode_run2", image_util_decode_destroy(dstHandle));

	nRet = image_util_decode_destroy(dstHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet));
	nRet = image_util_destroy_image(stDecodedImage);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_destroy_image", ImageUtilGetError(nRet));
	return 0;
}

/**
* @function			Image_util_decode_completed2_CallBack
* @description		Called when transform is finished just before returning the output.
* @parameter[IN]	The error code of image-util transfrom
* @parameter[IN]	Media packet handle
* @parameter[IN]	The user data passed from the for each function
* @return			NA
*/
void Image_util_decode_completed2_CallBack(int error_code, image_util_image_h image, void *user_data)
{
	g_bImageUtilDecodeCompletedCallback = true;
#if DEBUG
	FPRINTF("[Line : %d][%s] Image_util_decode_completed2_CallBack is called\\n", __LINE__, API_NAMESPACE);
#endif	
}

//& purpose: To start decoding of the image with the given decode handle.
//& type: auto
/**
* @testcase   			ITc_image_util_decode_run_async2_p
* @since_tizen			5.5
* @author             	SRID(karanam.s)
* @reviewer         	SRID(manoj.g2)
* @type 				auto
* @description			To start decoding of the image with the given decode handle.
* @scenario				To start decoding of the image with the given decode handle.
* @apicovered			  image_util_decode_run_async2
* @passcase				When image_util_decode_run_async2 is successful.
* @failcase				If target API image_util_decode_run_async2 fails or any precondition API fails.
* @precondition			Handle of image util decoding should be created.
* @postcondition		NA
*/
int ITc_image_util_decode_run_async2_p(void)
{
	START_TEST;
	unsigned char *puszImageInputBuffer = NULL;
	image_util_decode_h dstHandle = NULL;
	image_util_image_h stDecodedImage = NULL;

	int nRet = image_util_decode_create(&dstHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(dstHandle,"image_util_decode_create");

	char pPath[PATH_LEN] = {0,};
	if ( false == ImageUtilAppendToAppDataPath(SAMPLE_FILE_PATH, pPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	nRet = image_util_decode_set_input_path(dstHandle, pPath);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_input_path", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));

	nRet = image_util_decode_run2(dstHandle, &stDecodedImage);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_run2", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));
	CHECK_HANDLE_CLEANUP(stDecodedImage,"image_util_decode_run2", image_util_decode_destroy(dstHandle));

	g_bImageUtilDecodeCompletedCallback = false;
	//target api
	nRet = image_util_decode_run_async2(dstHandle, (image_util_decode_completed2_cb) Image_util_decode_completed2_CallBack, NULL);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_run_async2", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));
	wait_for_async();

	if ( !g_bImageUtilDecodeCompletedCallback )
	{
		FPRINTF("[Line : %d][%s] Image_util_decode_completed2_CallBack failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		nRet = image_util_decode_destroy(dstHandle);
		PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet));
		nRet = image_util_destroy_image(stDecodedImage);
		PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_destroy_image", ImageUtilGetError(nRet));
		return 1;
	}
	else
	{
		#if DEBUG
		FPRINTF("[Line : %d][%s] image_util_decode_run_async2 is successful\\n", __LINE__, API_NAMESPACE);
		#endif
	}

	nRet = image_util_decode_destroy(dstHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet));

	nRet = image_util_destroy_image(stDecodedImage);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_destroy_image", ImageUtilGetError(nRet));

	return 0;
}

//& purpose: Retrieves all supported image encoding/decoding colorspace by invoking a
// callback function once for each one. 
//& type: auto
/**
* @testcase   			ITc_image_util_foreach_supported_colorspace_p
* @since_tizen			3.0
* @author             	SRID(manu.tiwari)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Retrieves all supported image encoding/decoding colorspace by 
                        invoking a callback function once for each one 
* @scenario				
* @apicovered			image_util_foreach_supported_colorspace
* @passcase				When image_util_foreach_supported_colorspace is successful.
* @failcase				If target API image_util_foreach_supported_colorspace fails or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_foreach_supported_colorspace_p(void)
{
	START_TEST;
	g_bImageUtilForeachSupporedColorspace = false;
	//target api
	int nRet = image_util_foreach_supported_colorspace(IMAGE_UTIL_JPEG,(image_util_supported_colorspace_cb)Image_util_supported_colorspace_CallBack , NULL);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_foreach_supported_colorspace", ImageUtilGetError(nRet));
	if ( !g_bImageUtilForeachSupporedColorspace )
	{
		FPRINTF("[Line : %d][%s] image_util_foreach_supported_colorspace failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	else
	{
		#if DEBUG
		FPRINTF("[Line : %d][%s] image_util_foreach_supported_colorspace is successful\\n", __LINE__, API_NAMESPACE);
		#endif
	}
	return 0;
}

//& purpose: Sets the decoded image for JPEG colorspace format
//& type: auto
/**
* @testcase   			ITc_image_util_decode_set_colorspace_jpeg_p
* @since_tizen			6.0
* @author             	SRID(priya.kohli)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets the decoded image for JPEG colorspace format
* @scenario
* @apicovered			image_util_decode_set_colorspace
* @passcase				When image_util_decode_set_colorspace is successful.
* @failcase				If target API image_util_decode_set_colorspace fails or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_decode_set_colorspace_jpeg_p(void)
{
	START_TEST;
	image_util_decode_h stHandle = NULL;
	g_bImageUtilForeachSupporedColorspace = false;

	int nRet = image_util_decode_create(&stHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(stHandle,"image_util_decode_create");

	nRet = image_util_foreach_supported_colorspace(IMAGE_UTIL_JPEG,(image_util_supported_colorspace_cb)Image_util_supported_colorspace_CallBack , NULL);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_foreach_supported_colorspace", ImageUtilGetError(nRet));
	if ( !g_bImageUtilForeachSupporedColorspace )
	{
		FPRINTF("[Line : %d][%s] image_util_foreach_supported_colorspace failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		nRet = image_util_decode_destroy(stHandle);
		PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet));
		return 1;
	}
	else
	{
		char pPath[PATH_LEN] = {0,};
		if ( false == ImageUtilAppendToAppDataPath(SAMPLE_FILE_PATH, pPath) )
		{
			FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
			return 1;
		}

		nRet = image_util_decode_set_input_path(stHandle, pPath);
		PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_input_path", ImageUtilGetError(nRet), image_util_decode_destroy(stHandle));

		for (int nColorSpace = IMAGE_UTIL_COLORSPACE_YV12; nColorSpace <= IMAGE_UTIL_COLORSPACE_NV61; nColorSpace++)
		{
			if (JpegColorspace[nColorSpace] == IMAGE_UTIL_ERROR_NONE)
			{
				nRet = image_util_decode_set_colorspace(stHandle,nColorSpace);
				PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_colorspace", ImageUtilGetError(nRet), image_util_decode_destroy(stHandle));
			}
		}
	}

	nRet = image_util_decode_destroy(stHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet));

	return 0;
}

//& purpose: Sets the decoded image for PNG colorspace format
//& type: auto
/**
* @testcase   			ITc_image_util_decode_set_colorspace_png_p
* @since_tizen			6.0
* @author             	SRID(priya.kohli)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets the decoded image for PNG colorspace format
* @scenario
* @apicovered			image_util_decode_set_colorspace
* @passcase				When image_util_decode_set_colorspace is successful.
* @failcase				If target API image_util_decode_set_colorspace fails or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_decode_set_colorspace_png_p(void)
{
	START_TEST;
	image_util_decode_h stHandle = NULL;
	g_bImageUtilForeachSupporedColorspace = false;

	int nRet = image_util_decode_create(&stHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(stHandle,"image_util_decode_create");

	nRet = image_util_foreach_supported_colorspace(IMAGE_UTIL_PNG,(image_util_supported_colorspace_cb)Image_util_supported_colorspace_CallBack , NULL);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_foreach_supported_colorspace", ImageUtilGetError(nRet));
	if ( !g_bImageUtilForeachSupporedColorspace )
	{
		FPRINTF("[Line : %d][%s] image_util_foreach_supported_colorspace failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		nRet = image_util_decode_destroy(stHandle);
		PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet));
		return 1;
	}
	else
	{
		char pPath[PATH_LEN] = {0,};
		if ( false == ImageUtilAppendToAppDataPath(SAMPLE_PNG_FILE_PATH, pPath) )
		{
			FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
			return 1;
		}

		nRet = image_util_decode_set_input_path(stHandle, pPath);
		PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_input_path", ImageUtilGetError(nRet), image_util_decode_destroy(stHandle));

		for (int nColorSpace = IMAGE_UTIL_COLORSPACE_YV12; nColorSpace <= IMAGE_UTIL_COLORSPACE_NV61; nColorSpace++)
		{
			if (PngColorspace[nColorSpace] == IMAGE_UTIL_ERROR_NONE)
			{
				nRet = image_util_decode_set_colorspace(stHandle,nColorSpace);
				PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_colorspace", ImageUtilGetError(nRet), image_util_decode_destroy(stHandle));
			}
		}
	}

	nRet = image_util_decode_destroy(stHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet));

	return 0;
}

//& purpose: Sets the decoded image for GIF colorspace format
//& type: auto
/**
* @testcase   			ITc_image_util_decode_set_colorspace_gif_p
* @since_tizen			6.0
* @author             	SRID(priya.kohli)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets the decoded image for GIF colorspace format
* @scenario
* @apicovered			image_util_decode_set_colorspace
* @passcase				When image_util_decode_set_colorspace is successful.
* @failcase				If target API image_util_decode_set_colorspace fails or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_decode_set_colorspace_gif_p(void)
{
	START_TEST;
	image_util_decode_h stHandle = NULL;
	g_bImageUtilForeachSupporedColorspace = false;

	int nRet = image_util_decode_create(&stHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(stHandle,"image_util_decode_create");

	nRet = image_util_foreach_supported_colorspace(IMAGE_UTIL_GIF,(image_util_supported_colorspace_cb)Image_util_supported_colorspace_CallBack , NULL);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_foreach_supported_colorspace", ImageUtilGetError(nRet));
	if ( !g_bImageUtilForeachSupporedColorspace )
	{
		FPRINTF("[Line : %d][%s] image_util_foreach_supported_colorspace failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		nRet = image_util_decode_destroy(stHandle);
		PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet));
		return 1;
	}
	else
	{
		char pPath[PATH_LEN] = {0,};
		if ( false == ImageUtilAppendToAppDataPath(SAMPLE_GIF_FILE_PATH, pPath) )
		{
			FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
			return 1;
		}

		nRet = image_util_decode_set_input_path(stHandle, pPath);
		PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_input_path", ImageUtilGetError(nRet), image_util_decode_destroy(stHandle));

		for (int nColorSpace = IMAGE_UTIL_COLORSPACE_YV12; nColorSpace <= IMAGE_UTIL_COLORSPACE_NV61; nColorSpace++)
		{
			if (GifColorspace[nColorSpace] == IMAGE_UTIL_ERROR_NONE)
			{
				nRet = image_util_decode_set_colorspace(stHandle,nColorSpace);
				PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_colorspace", ImageUtilGetError(nRet), image_util_decode_destroy(stHandle));
			}
		}
	}

	nRet = image_util_decode_destroy(stHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet));

	return 0;
}

//& purpose: Sets the decoded image for BMP colorspace format
//& type: auto
/**
* @testcase   			ITc_image_util_decode_set_colorspace_bmp_p
* @since_tizen			6.0
* @author             	SRID(priya.kohli)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets the decoded image for BMP colorspace format
* @scenario
* @apicovered			image_util_decode_set_colorspace
* @passcase				When image_util_decode_set_colorspace is successful.
* @failcase				If target API image_util_decode_set_colorspace fails or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_decode_set_colorspace_bmp_p(void)
{
	START_TEST;
	image_util_decode_h stHandle = NULL;
	g_bImageUtilForeachSupporedColorspace = false;

	int nRet = image_util_decode_create(&stHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(stHandle,"image_util_decode_create");

	nRet = image_util_foreach_supported_colorspace(IMAGE_UTIL_BMP,(image_util_supported_colorspace_cb)Image_util_supported_colorspace_CallBack , NULL);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_foreach_supported_colorspace", ImageUtilGetError(nRet));
	if ( !g_bImageUtilForeachSupporedColorspace )
	{
		FPRINTF("[Line : %d][%s] image_util_foreach_supported_colorspace failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		nRet = image_util_decode_destroy(stHandle);
		PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet));
		return 1;
	}
	else
	{
		char pPath[PATH_LEN] = {0,};
		if ( false == ImageUtilAppendToAppDataPath(SAMPLE_BMP_FILE_PATH, pPath) )
		{
			FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
			return 1;
		}

		nRet = image_util_decode_set_input_path(stHandle, pPath);
		PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_input_path", ImageUtilGetError(nRet), image_util_decode_destroy(stHandle));

		for (int nColorSpace = IMAGE_UTIL_COLORSPACE_YV12; nColorSpace <= IMAGE_UTIL_COLORSPACE_NV61; nColorSpace++)
		{
			if (BmpColorspace[nColorSpace] == IMAGE_UTIL_ERROR_NONE)
			{
				nRet = image_util_decode_set_colorspace(stHandle,nColorSpace);
				PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_colorspace", ImageUtilGetError(nRet), image_util_decode_destroy(stHandle));
			}
		}
	}

	nRet = image_util_decode_destroy(stHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet));

	return 0;
}

//& purpose: Sets the decoded image for HEIF colorspace format
//& type: auto
/**
* @testcase   			ITc_image_util_decode_set_colorspace_heif_p
* @since_tizen			6.5
* @author             	SRID(nibha.sharma)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets the decoded image for HEIF colorspace format
* @scenario
* @apicovered			image_util_decode_set_colorspace
* @passcase				When image_util_decode_set_colorspace is successful.
* @failcase				If target API image_util_decode_set_colorspace fails or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_decode_set_colorspace_heif_p(void)
{
	START_TEST;
	image_util_decode_h stHandle = NULL;
	g_bImageUtilForeachSupporedColorspace = false;

	int nRet = image_util_decode_create(&stHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(stHandle,"image_util_decode_create");

	nRet = image_util_foreach_supported_colorspace(IMAGE_UTIL_HEIF,(image_util_supported_colorspace_cb)Image_util_supported_colorspace_CallBack , NULL);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_foreach_supported_colorspace", ImageUtilGetError(nRet), image_util_decode_destroy(stHandle));
	if ( !g_bImageUtilForeachSupporedColorspace )
	{
		FPRINTF("[Line : %d][%s] image_util_foreach_supported_colorspace failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		nRet = image_util_decode_destroy(stHandle);
		PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet));
		return 1;
	}
	else
	{
		char pPath[PATH_LEN] = {0,};
		if ( false == ImageUtilAppendToAppDataPath(SAMPLE_HEIF_FILE_PATH, pPath) )
		{
			FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
			nRet = image_util_decode_destroy(stHandle);
			PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet));
			return 1;
		}

		nRet = image_util_decode_set_input_path(stHandle, pPath);
		PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_input_path", ImageUtilGetError(nRet), image_util_decode_destroy(stHandle));

		for (int nColorSpace = IMAGE_UTIL_COLORSPACE_YV12; nColorSpace <= IMAGE_UTIL_COLORSPACE_NV61; nColorSpace++)
		{
			if (BmpColorspace[nColorSpace] == IMAGE_UTIL_ERROR_NONE)
			{
				nRet = image_util_decode_set_colorspace(stHandle,nColorSpace);
				PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_colorspace", ImageUtilGetError(nRet), image_util_decode_destroy(stHandle));
			}
		}
	}

	nRet = image_util_decode_destroy(stHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet));

	return 0;
}

//& purpose: Sets the downscale value at which JPEG image should be decoded.
//& type: auto
/**
* @testcase   			ITc_image_util_decode_set_jpeg_downscale_p
* @since_tizen			3.0
* @author             	SRID(manu.tiwari)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Sets the downscale value at which JPEG image should be decoded.
* @scenario
* @apicovered			image_util_decode_set_jpeg_downscale
* @passcase				When image_util_decode_set_jpeg_downscale is successful.
* @failcase				If target API image_util_decode_set_jpeg_downscale fails or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_decode_set_jpeg_downscale_p(void)
{
	START_TEST;
	image_util_decode_h stHandle = NULL;

	int nRet = image_util_decode_create(&stHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(stHandle,"image_util_decode_create");
	//target api
	image_util_decode_set_jpeg_downscale(stHandle,IMAGE_UTIL_DOWNSCALE_1_1);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_jpeg_downscale", ImageUtilGetError(nRet), image_util_decode_destroy(stHandle));
	nRet = image_util_decode_destroy(stHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet));
	return 0;
}

//& purpose: Sets the quality for JPEG image encoding.
//& type: auto
/**
* @testcase   			ITc_image_util_encode_set_quality_p
* @since_tizen			3.0
* @author             	SRID(manu.tiwari)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Sets the quality for JPEG image encoding.
* @scenario
* @apicovered			image_util_encode_set_quality
* @passcase				When image_util_encode_set_quality is successful.
* @failcase				If target API image_util_encode_set_quality fails or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_image_util_encode_set_quality_p(void)
{
	START_TEST;
	image_util_encode_h stHandle = NULL;
	int quality = 1;   //quality from 1~100 default - 2
	int nRet = image_util_encode_create(IMAGE_UTIL_JPEG, &stHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(stHandle,"image_util_encode_create");
	//target api
	nRet = image_util_encode_set_quality(stHandle, quality);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_set_quality", ImageUtilGetError(nRet), image_util_encode_destroy(stHandle));
	nRet = image_util_encode_destroy(stHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_destroy", ImageUtilGetError(nRet));
	return 0;
}

//& purpose: Encodes the image to a file with the given encode handle.
//& type: auto
/**
* @testcase   			ITc_image_util_encode_run_to_file_p
* @since_tizen			5.5
* @author             	SRID(karanam.s)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Encodes the image to a file with the given encode handle.
* @scenario			The function executes synchronously.
* @apicovered			image_util_encode_run_to_file
* @passcase				When image_util_encode_run_to_file is successful.
* @failcase				If target API image_util_encode_run_to_file fails or any precondition API fails.
* @precondition			image_util_encode_create
* @postcondition		image_util_encode_destroy
*/
int ITc_image_util_encode_run_to_file_p(void)
{
	START_TEST;

	image_util_image_h stDecodedImage = NULL;
	image_util_encode_h stHandle = NULL;

	char pPath[PATH_LEN] = {0,};

	int nRet = ImageUtilEncodeRunSetUp(&stDecodedImage, &stHandle, pPath);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "ImageUtilEncodeRunSetUp", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage));

	nRet = image_util_encode_run_to_file(stHandle, stDecodedImage, pPath);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_run_to_file", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage);image_util_encode_destroy(stHandle));

	nRet = image_util_destroy_image(stDecodedImage);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_destroy_image", ImageUtilGetError(nRet));

	nRet = image_util_encode_destroy(stHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_destroy", ImageUtilGetError(nRet));

	return 0;

}

//& purpose: Encodes the image to a buffer with the given encode handle.
//& type: auto
/**
* @testcase   			ITc_image_util_encode_run_to_buffer_p
* @since_tizen			5.5
* @author             	SRID(karanam.s)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Encodes the image to a buffer with the given encode handle.
* @scenario			The function executes synchronously.
* @apicovered			image_util_encode_run_to_buffer
* @passcase			When image_util_encode_run_to_buffer is successful.
* @failcase			If target API image_util_encode_run_to_buffer fails or any precondition API fails.
* @precondition			image_util_encode_create
* @postcondition		image_util_encode_destroy
*/
int ITc_image_util_encode_run_to_buffer_p(void)
{
	START_TEST;

	image_util_image_h stDecodedImage = NULL;
	image_util_encode_h stHandle = NULL;
	unsigned char *pszBuffer = NULL;
	size_t tBufferSize;
	char pPath[PATH_LEN] = {0,};

	int nRet = ImageUtilEncodeRunSetUp(&stDecodedImage, &stHandle, pPath);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "ImageUtilEncodeRunSetUp", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage));

	nRet = image_util_encode_run_to_buffer(stHandle, stDecodedImage, &pszBuffer, &tBufferSize);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_run_to_buffer", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage);image_util_encode_destroy(stHandle));
	CHECK_HANDLE_CLEANUP(pszBuffer,"image_util_encode_run_to_buffer", image_util_destroy_image(stDecodedImage);image_util_encode_destroy(stHandle));

	nRet = image_util_destroy_image(stDecodedImage);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_destroy_image", ImageUtilGetError(nRet));

	nRet = image_util_encode_destroy(stHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_destroy", ImageUtilGetError(nRet));

	return 0;
}

//& purpose: Encodes the image to a file with the given encode handle asynchronously.
//& type: auto
/**
* @testcase   			ITc_image_util_encode_run_async_to_file_p
* @since_tizen			5.5
* @author             	SRID(karanam.s)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Encodes the image to a file with the given encode handle asynchronously.
* @scenario			The function executes asynchronously.
* @apicovered			image_util_encode_run_async_to_file
* @passcase			When image_util_encode_run_async_to_file is successful.
* @failcase			If target API image_util_encode_run_async_to_file fails or any precondition API fails.
* @precondition			image_util_encode_create
* @postcondition		image_util_encode_destroy
*/
int ITc_image_util_encode_run_async_to_file_p(void)
{
	START_TEST;

	image_util_image_h stDecodedImage = NULL;
	image_util_encode_h stHandle = NULL;
	g_bImageUtilEncodeToFileCompletedCallback = false;
	char pPath[PATH_LEN] = {0,};

	int nRet = ImageUtilEncodeRunSetUp(&stDecodedImage, &stHandle, pPath);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "ImageUtilEncodeRunSetUp", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage));

	nRet = image_util_encode_run_async_to_file(stHandle, stDecodedImage, pPath, Image_util_encode_to_file_completed_Callback, NULL);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_run_async_to_file", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage);image_util_encode_destroy(stHandle));

	wait_for_async();

	if ( !g_bImageUtilEncodeToFileCompletedCallback )
	{
		FPRINTF("[Line : %d][%s] Image_util_encode_to_file_completed_Callback failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		nRet = image_util_encode_destroy(stHandle);
		PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_destroy", ImageUtilGetError(nRet));
		nRet = image_util_destroy_image(stDecodedImage);
		PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_destroy_image", ImageUtilGetError(nRet));
		return 1;
	}

	nRet = image_util_destroy_image(stDecodedImage);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_destroy_image", ImageUtilGetError(nRet));

	nRet = image_util_encode_destroy(stHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_destroy", ImageUtilGetError(nRet));
}

//& purpose: Encodes the image to a buffer with the given encode handle asynchronously.
//& type: auto
/**
* @testcase   			ITc_image_util_encode_run_async_to_buffer_p
* @since_tizen			5.5
* @author             	SRID(karanam.s)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Encodes the image to a buffer with the given encode handle asynchronously.
* @scenario			The function executes asynchronously.
* @apicovered			image_util_encode_run_async_to_buffer
* @passcase			When image_util_encode_run_async_to_buffer is successful.
* @failcase			If target API image_util_encode_run_async_to_buffer fails or any precondition API fails.
* @precondition			image_util_encode_create
* @postcondition		image_util_encode_destroy
*/
int ITc_image_util_encode_run_async_to_buffer_p(void)
{
	START_TEST;
	image_util_decode_h dstHandle = NULL;
	image_util_image_h stDecodedImage = NULL;
	image_util_encode_h stHandle = NULL;
	g_bImageUtilEncodeToBufferCompletedCallback = false;
	g_sBufferEncodedImage sBufencImg = { NULL, 0 };
	char pPath[PATH_LEN] = {0,};


	int nRet = ImageUtilEncodeRunSetUp(&stDecodedImage, &stHandle, pPath);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "ImageUtilEncodeRunSetUp", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage));

	nRet = image_util_encode_run_async_to_buffer(stHandle, stDecodedImage, Image_util_encode_to_buffer_completed_Callback, &sBufencImg);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_run_async_to_buffer", ImageUtilGetError(nRet), image_util_destroy_image(stDecodedImage);image_util_encode_destroy(stHandle));

	wait_for_async();

	if ( !g_bImageUtilEncodeToBufferCompletedCallback )
	{
		FPRINTF("[Line : %d][%s] Image_util_encode_to_buffer_completed_Callback failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		nRet = image_util_encode_destroy(stHandle);
		PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_destroy", ImageUtilGetError(nRet));
		nRet = image_util_destroy_image(stDecodedImage);
		PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_destroy_image", ImageUtilGetError(nRet));
		return 1;
	}

	nRet = image_util_destroy_image(stDecodedImage);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_destroy_image", ImageUtilGetError(nRet));

	nRet = image_util_encode_destroy(stHandle);
	PRINT_RESULT_NORETURN(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_destroy", ImageUtilGetError(nRet));

	return 0;
}


/** @} */
/** @} */
