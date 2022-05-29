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

/**
* @function 		ImageUtilGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* ImageUtilGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case IMAGE_UTIL_ERROR_INVALID_PARAMETER:	szErrorVal = "IMAGE_UTIL_ERROR_INVALID_PARAMETER";		break;
	case IMAGE_UTIL_ERROR_OUT_OF_MEMORY:		szErrorVal = "IMAGE_UTIL_ERROR_OUT_OF_MEMORY";			break;
	case IMAGE_UTIL_ERROR_NO_SUCH_FILE:			szErrorVal = "IMAGE_UTIL_ERROR_NO_SUCH_FILE";			break;
	case IMAGE_UTIL_ERROR_INVALID_OPERATION:	szErrorVal = "IMAGE_UTIL_ERROR_INVALID_OPERATION";		break;
	case IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT:	szErrorVal = "IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT";	break;
	case IMAGE_UTIL_ERROR_NONE:					szErrorVal = "IMAGE_UTIL_ERROR_NONE";					break;
	default:									szErrorVal = "Unknown Error";							break;
	}
	return szErrorVal;
}

/**
* @function 		ImageUtilScale
* @description	 	Maps error enums 
* @parameter		nRet : error code returned
* @return 			error string
*/
char* ImageUtilScale(image_util_scale_e nRet)
{
	char *szErrorVal = "Unknown Error";
	switch ( nRet )
	{
	case IMAGE_UTIL_DOWNSCALE_1_1 : 			szErrorVal = "IMAGE_UTIL_DOWNSCALE_1_1" ;	 break; 
	case IMAGE_UTIL_DOWNSCALE_1_2 : 			szErrorVal = "IMAGE_UTIL_DOWNSCALE_1_2" ;	 break; 
	case IMAGE_UTIL_DOWNSCALE_1_4 : 			szErrorVal = "IMAGE_UTIL_DOWNSCALE_1_4" ;	 break; 
	case IMAGE_UTIL_DOWNSCALE_1_8 : 			szErrorVal = "IMAGE_UTIL_DOWNSCALE_1_8" ;	 break; 	
	}

	return szErrorVal;
}
/**
* @function 		ImageUtilColorspace
* @description	 	Maps error enums 
* @parameter		nRet : error code returned
* @return 			error string
*/
char* ImageUtilColorspace(image_util_colorspace_e nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case IMAGE_UTIL_COLORSPACE_YV12:			szErrorVal = "IMAGE_UTIL_COLORSPACE_YV12";			break;
		//case IMAGE_UTIL_COLORSPACE_YUV422:		szErrorVal = "IMAGE_UTIL_COLORSPACE_YUV422";		break;
	case IMAGE_UTIL_COLORSPACE_I420:			szErrorVal = "IMAGE_UTIL_COLORSPACE_I420";			break;
		//case IMAGE_UTIL_COLORSPACE_NV12:			szErrorVal = "IMAGE_UTIL_COLORSPACE_NV12";			break;
		//case IMAGE_UTIL_COLORSPACE_UYVY:			szErrorVal = "IMAGE_UTIL_COLORSPACE_UYVY";			break;
		//case IMAGE_UTIL_COLORSPACE_YUYV:			szErrorVal = "IMAGE_UTIL_COLORSPACE_YUYV";			break;
		//case IMAGE_UTIL_COLORSPACE_RGB565:		szErrorVal = "IMAGE_UTIL_COLORSPACE_RGB565";		break;
	case IMAGE_UTIL_COLORSPACE_RGB888:			szErrorVal = "IMAGE_UTIL_COLORSPACE_RGB888";		break;
	case IMAGE_UTIL_COLORSPACE_ARGB8888:		szErrorVal = "IMAGE_UTIL_COLORSPACE_ARGB8888";		break;
	case IMAGE_UTIL_COLORSPACE_BGRA8888:		szErrorVal = "IMAGE_UTIL_COLORSPACE_BGRA8888";		break;
	case IMAGE_UTIL_COLORSPACE_RGBA8888:		szErrorVal = "IMAGE_UTIL_COLORSPACE_RGBA8888";		break;
		//case IMAGE_UTIL_COLORSPACE_BGRX8888:		szErrorVal = "IMAGE_UTIL_COLORSPACE_BGRX8888";		break;
		//case IMAGE_UTIL_COLORSPACE_NV21:			szErrorVal = "IMAGE_UTIL_COLORSPACE_NV21";			break;
		//case IMAGE_UTIL_COLORSPACE_NV16:			szErrorVal = "IMAGE_UTIL_COLORSPACE_NV16";			break;
		//case IMAGE_UTIL_COLORSPACE_NV61:			szErrorVal = "IMAGE_UTIL_COLORSPACE_NV61";			break;
	default:									szErrorVal = "Unknown Error";						break;
	}

	return szErrorVal;
}

/**
* @function 		ImageUtilColorspace
* @description	 	Maps error enums 
* @parameter		nRet : error code returned
* @return 			error string
*/
char* ImageUtilRotaion(image_util_rotation_e nRet)
{
	char *szErrorVal = "Unknown Error";
	switch ( nRet )
	{
	case IMAGE_UTIL_ROTATION_NONE:			szErrorVal = "IMAGE_UTIL_ROTATION_NONE";		break;
	case IMAGE_UTIL_ROTATION_90:			szErrorVal = "IMAGE_UTIL_ROTATION_90";			break;
	case IMAGE_UTIL_ROTATION_180:			szErrorVal = "IMAGE_UTIL_ROTATION_180";			break;
	case IMAGE_UTIL_ROTATION_270:			szErrorVal = "IMAGE_UTIL_ROTATION_270";			break;
	case IMAGE_UTIL_ROTATION_FLIP_HORZ:		szErrorVal = "IMAGE_UTIL_ROTATION_FLIP_HORZ";	break;
	case IMAGE_UTIL_ROTATION_FLIP_VERT:		szErrorVal = "IMAGE_UTIL_ROTATION_FLIP_VERT";	break;
	}

	return szErrorVal;
}

/**
* @function 		MediaToolsGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* MediaToolsGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case MEDIA_PACKET_ERROR_NONE:						szErrorVal = "MEDIA_PACKET_ERROR_NONE";						break;
	case MEDIA_PACKET_ERROR_OUT_OF_MEMORY:				szErrorVal = "MEDIA_PACKET_ERROR_OUT_OF_MEMORY";			break;
	case MEDIA_PACKET_ERROR_INVALID_PARAMETER:			szErrorVal = "MEDIA_PACKET_ERROR_INVALID_PARAMETER";		break;
	case MEDIA_PACKET_ERROR_INVALID_OPERATION:			szErrorVal = "MEDIA_PACKET_ERROR_INVALID_OPERATION";		break;
	case MEDIA_PACKET_ERROR_FILE_NO_SPACE_ON_DEVICE:	szErrorVal = "MEDIA_PACKET_ERROR_FILE_NO_SPACE_ON_DEVICE";	break;
	default:											szErrorVal = "Unknown Error";								break;
	}

	return szErrorVal;
}

/**
* @function 		MediaFormatGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* MediaFormatGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case MEDIA_FORMAT_ERROR_NONE:						szErrorVal = "MEDIA_FORMAT_ERROR_NONE";						break;
	case MEDIA_FORMAT_ERROR_OUT_OF_MEMORY:				szErrorVal = "MEDIA_FORMAT_ERROR_OUT_OF_MEMORY";			break;
	case MEDIA_FORMAT_ERROR_INVALID_PARAMETER:			szErrorVal = "MEDIA_FORMAT_ERROR_INVALID_PARAMETER";		break;
	case MEDIA_FORMAT_ERROR_INVALID_OPERATION:			szErrorVal = "MEDIA_FORMAT_ERROR_INVALID_OPERATION";		break;
	case MEDIA_FORMAT_ERROR_FILE_NO_SPACE_ON_DEVICE:	szErrorVal = "MEDIA_FORMAT_ERROR_FILE_NO_SPACE_ON_DEVICE";	break;
	default:											szErrorVal = "Unknown Error";								break;
	}

	return szErrorVal;
}

/**
* @function 		ImageUtilGetDataPath
* @description	 	Returns the application data path
* @parameter		pAppDataPath: application data path
* @return 			true if succeed else false
*/
bool ImageUtilGetDataPath(char* pAppDataPath)
{
	if ( NULL == pAppDataPath )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	memset(pAppDataPath, 0, PATH_LEN);

	char* pPath = NULL;
	pPath = app_get_data_path();
	if ( NULL == pPath )
	{
		FPRINTF("[Line : %d][%s] Unable to get application data path; app_get_data_path returned null value\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	strncpy(pAppDataPath, pPath, PATH_LEN-1);

	FPRINTF("[Line : %d][%s] application data path returned = %s\\n", __LINE__, API_NAMESPACE, pAppDataPath);

	return true;
}

/**
* @function 		ImageUtilAppendToAppDataPath
* @description	 	Appends the input string to application data path
* @parameter		pInputPath: path to append to data path; pFinalPath: final resultant path
* @return 			true if succeed else false
*/
bool ImageUtilAppendToAppDataPath(char* pInputPath, char* pFinalPath)
{
	if ( (NULL == pInputPath) || (NULL == pFinalPath) )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	char pAppDataPath[PATH_LEN] = {0,};
	if ( false == ImageUtilGetDataPath(pAppDataPath) )
	{
		return false;
	}

	memset(pFinalPath, 0, PATH_LEN);
	strncpy(pFinalPath, pAppDataPath, PATH_LEN-1);
	strncat(pFinalPath, pInputPath, strlen(pInputPath)+1);

	FPRINTF("[Line : %d][%s] result path returned = %s\\n", __LINE__, API_NAMESPACE, pFinalPath);

	return true;
}

/**
* @function             timeout_func
* @description          callback function for capturing context event change callbacks
* @parameter            gpointer data
* @return                       False
*/
gboolean timeout_func(gpointer data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Timeout! Test case failed!\\n",__LINE__, API_NAMESPACE);
#endif
	g_main_loop_quit((GMainLoop *) data);
	return FALSE;
}

/**
* @function             signal_for_async
* @description          callback function for signalling callbacks
* @parameter            	NA
* @return                       NA
*/
void signal_for_async()
{
	FPRINTF("[Line : %d][%s] Invoked completed callback\\n",__LINE__, API_NAMESPACE);
	if (g_timeout_id > 0)
		g_source_remove(g_timeout_id);
	if (g_mainloop != NULL)
		g_main_loop_quit(g_mainloop);
}

/**
* @function             wait_for_async
* @description          callback function for waiting for callbacks
* @parameter            	NA
* @return                       NA
*/
void wait_for_async()
{
	g_mainloop = g_main_loop_new(NULL, FALSE);

	g_timeout_id = g_timeout_add(TIMEOUT_CB, timeout_func, g_mainloop);
	g_main_loop_run(g_mainloop);
	g_source_remove(g_timeout_id);
}

/**
* @function             ImageUtilEncodeRunSetUp
* @description          Prerequisite for image_util_encode_run apis
* @parameter            	image_util_image_h *stDecodedImage, image_util_encode_h *stHandle, char *pPath
* @return                       0 if all the apis are successful else error is returned.
*/
int ImageUtilEncodeRunSetUp(image_util_image_h *stDecodedImage, image_util_encode_h *stHandle, char *pPath)
{

	image_util_decode_h dstHandle = NULL;

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

	nRet = image_util_decode_run2(dstHandle, stDecodedImage);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_run2", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));
	CHECK_HANDLE_CLEANUP(*stDecodedImage,"image_util_decode_run2", image_util_decode_destroy(dstHandle));

	nRet = image_util_decode_destroy(dstHandle);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet), image_util_destroy_image(*stDecodedImage));

	nRet = image_util_encode_create(IMAGE_UTIL_JPEG, stHandle);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_encode_create", ImageUtilGetError(nRet), image_util_destroy_image(*stDecodedImage));
	CHECK_HANDLE_CLEANUP(*stHandle,"image_util_encode_create", image_util_destroy_image(*stDecodedImage));

	return 0;
}

/**
* @function			ImageUtilAnimEncodeRunSetUp
* @description			Prerequisite for image_util_anim_encode_add_frame api
* @parameter			image_util_image_h *stDecodedImage, char *pPath
* @return			0 if all the apis are successful else error is returned.
*/
int ImageUtilAnimEncodeRunSetUp(image_util_image_h *stDecodedImage, char *pPath)
{

	image_util_decode_h dstHandle = NULL;

	int nRet = image_util_decode_create(&dstHandle);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_create", ImageUtilGetError(nRet));
	CHECK_HANDLE(dstHandle,"image_util_decode_create");

	nRet = image_util_decode_set_input_path(dstHandle, pPath);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_set_input_path", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));

	nRet = image_util_decode_run2(dstHandle, stDecodedImage);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_run2", ImageUtilGetError(nRet), image_util_decode_destroy(dstHandle));
	CHECK_HANDLE_CLEANUP(*stDecodedImage,"image_util_decode_run2", image_util_decode_destroy(dstHandle));

	nRet = image_util_decode_destroy(dstHandle);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet, "image_util_decode_destroy", ImageUtilGetError(nRet), image_util_destroy_image(*stDecodedImage));

	return 0;
}

/**
* @function 		ImageUtilGetTestPath
* @description	 	Returns image data path
* @parameter		const char *base_dir, const char *filename
* @return		char
*/
char *ImageUtilGetTestPath(const char *base_dir, const char *filename)
{
	if (!base_dir || !strlen(base_dir) ||
		!filename || !strlen(filename))
		return NULL;

	return g_strdup_printf("%s/%s", base_dir, filename);
}

/** @} */
