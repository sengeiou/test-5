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

//Add helper function definitions here

/**
* @function 	ImageUtilGetError
* @description	Display the details error information
* @parameter	[IN] nResult, 		api return value code
* 				[IN] pszApi, 		api name
* 				[IN] nLineNumber	line number
* @return		NA
*/
char* ImageUtilGetError(int nResult)
{
	char* pszErrInfo = NULL;
	switch ( nResult )
	{
	case IMAGE_UTIL_ERROR_INVALID_PARAMETER :		pszErrInfo = "IMAGE_UTIL_ERROR_INVALID_PARAMETER";		break;
	case IMAGE_UTIL_ERROR_OUT_OF_MEMORY :			pszErrInfo = "IMAGE_UTIL_ERROR_OUT_OF_MEMORY";			break;
	case IMAGE_UTIL_ERROR_NO_SUCH_FILE:				pszErrInfo = "IMAGE_UTIL_ERROR_NO_SUCH_FILE";			break;
	case IMAGE_UTIL_ERROR_INVALID_OPERATION :		pszErrInfo = "IMAGE_UTIL_ERROR_INVALID_OPERATION";		break;
	case IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT :	pszErrInfo = "IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT";	break;
	case IMAGE_UTIL_ERROR_PERMISSION_DENIED:		pszErrInfo = "IMAGE_UTIL_ERROR_PERMISSION_DENIED";		break;
	default:										pszErrInfo = "Unknown Error";
	}

	return pszErrInfo;
}

/**
* @function 	ImageUtilDecode
* @description	Dncode the image.
* @parameter	[IN] pPath, 			image path
* 				[IN] eColorSpace,		image colorspace
* 				[OUT] nWidth,			image width
* 				[OUT] nHeight,			image height
* 				[OUT] upszDecodeBuffer,		decode result
* @return		true if all api return success otherwise false
*/
bool ImageUtilDecode(const char *pszImgPath, image_util_colorspace_e eColorSpace, unsigned long *nWidth, unsigned long *nHeight, unsigned char **upszDecodeBuffer, unsigned long long *unDecodeSize)
{
	image_util_decode_h decHandle = NULL;

	int nRet = image_util_decode_create(&decHandle);
	if (nRet != IMAGE_UTIL_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] image_util_decode_create\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	nRet = image_util_decode_set_input_path(decHandle, pszImgPath);
	if (nRet != IMAGE_UTIL_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] image_util_decode_set_input_path\\n", __LINE__, API_NAMESPACE);
		image_util_decode_destroy(decHandle);
		return false;
	}
	nRet = image_util_decode_set_colorspace(decHandle, IMAGE_UTIL_COLORSPACE_RGB888);
	if (nRet != IMAGE_UTIL_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] image_util_decode_set_input_path\\n", __LINE__, API_NAMESPACE);
		image_util_decode_destroy(decHandle);
		return false;
	}

	nRet = image_util_decode_set_output_buffer(decHandle, upszDecodeBuffer);
	if (nRet != IMAGE_UTIL_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] image_util_decode_set_input_path\\n", __LINE__, API_NAMESPACE);
		image_util_decode_destroy(decHandle);
		return false;
	}

	nRet = image_util_decode_run(decHandle, nWidth, nHeight, unDecodeSize);
	if (nRet != IMAGE_UTIL_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] image_util_decode_set_input_path\\n", __LINE__, API_NAMESPACE);
		image_util_decode_destroy(decHandle);
		return false;
	}

	image_util_decode_destroy(decHandle);
	return true;
}

/**
* @function 	ImageUtilEncode
* @description	Calculate image buffer and encode the image.
* @parameter	[IN] nWidth, 			image width
* 				[IN] nHeight,			image height
* 				[IN] eColorSpace,		image colorspace  				
* @return		true if all api return success otherwise false
*/
bool ImageUtilEncode(unsigned long nWidth, unsigned long nHeight, image_util_colorspace_e eColorSpace)
{
	int nRet= IMAGE_UTIL_ERROR_NONE;
	unsigned int unSize = 0;
	unsigned long long unEncodeSize = 0;

	nRet = image_util_calculate_buffer_size (nWidth, nHeight, eColorSpace , &unSize);
	if ( nRet != IMAGE_UTIL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] image_util_calculate_buffer_size failed, error returned = %s\\n", __LINE__, API_NAMESPACE, ImageUtilGetError(nRet));
		return false;
	}
	if (unSize == 0)
	{
		FPRINTF("[Line : %d][%s] Calculated Image Buffer Size is returned zero\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	g_upszImgDestBuffer = malloc(unSize);

	image_util_encode_h encHandle = NULL;

	nRet = image_util_encode_create(IMAGE_UTIL_JPEG, &encHandle);
	if ( nRet != IMAGE_UTIL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] image_util_encode_create failed, error returned = %s\\n", __LINE__, API_NAMESPACE, ImageUtilGetError(nRet));
		FREE_MEMORY(g_upszImgDestBuffer);
		return false;
	}
	nRet = image_util_encode_set_resolution(encHandle, nWidth, nHeight );
	if ( nRet != IMAGE_UTIL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] image_util_encode_set_resolution failed, error returned = %s\\n", __LINE__, API_NAMESPACE, ImageUtilGetError(nRet));
		image_util_encode_destroy(encHandle);
		FREE_MEMORY(g_upszImgDestBuffer);
		return false;
	}
	nRet = image_util_encode_set_input_buffer(encHandle, g_upszImgDestBuffer);
	if ( nRet != IMAGE_UTIL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] image_util_encode_set_input_buffer failed, error returned = %s\\n", __LINE__, API_NAMESPACE, ImageUtilGetError(nRet));
		image_util_encode_destroy(encHandle);
		FREE_MEMORY(g_upszImgDestBuffer);
		return false;
	}
	nRet = image_util_encode_set_colorspace(encHandle, eColorSpace);
	if ( nRet != IMAGE_UTIL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] image_util_encode_set_colorspace failed, error returned = %s\\n", __LINE__, API_NAMESPACE, ImageUtilGetError(nRet));
		image_util_encode_destroy(encHandle);
		FREE_MEMORY(g_upszImgDestBuffer);
		return false;
	}
	nRet = image_util_encode_set_quality(encHandle, QUALITY);
	if ( nRet != IMAGE_UTIL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] image_util_encode_set_quality failed, error returned = %s\\n", __LINE__, API_NAMESPACE, ImageUtilGetError(nRet));
		image_util_encode_destroy(encHandle);
		FREE_MEMORY(g_upszImgDestBuffer);
		return false;
	}
	nRet = image_util_encode_set_output_path(encHandle, OUTPUT_FILE_PATH);
	if ( nRet != IMAGE_UTIL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] image_util_encode_set_output_path failed, error returned = %s\\n", __LINE__, API_NAMESPACE, ImageUtilGetError(nRet));
		image_util_encode_destroy(encHandle);
		FREE_MEMORY(g_upszImgDestBuffer);
		return false;
	}

	nRet = image_util_encode_run(encHandle, &unEncodeSize);
	if ( nRet != IMAGE_UTIL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] image_util_encode_run failed, error returned = %s\\n", __LINE__, API_NAMESPACE, ImageUtilGetError(nRet));
		image_util_encode_destroy(encHandle);
		FREE_MEMORY(g_upszImgDestBuffer);
		return false;
	}

	image_util_encode_destroy(encHandle);
	FREE_MEMORY(g_upszImgDestBuffer);

	return true;
}

/**
* @function 			ImageUtilCheckFunction
* @description			Calculate image buffer and encode the image.
* @parameter	[IN]	upszImageBuffer, 		image buffer
* 				[IN]	nWidth,				image width
* 				[IN]	nHeight,				image Height 
* 				[IN]	unDecodeSize,			buffer size
* @return		true if all api return success otherwise false.
*
*/
bool ImageUtilCheckFunction(unsigned char *upszImageBuffer, unsigned long nWidth, unsigned long nHeight, unsigned long long unDecodeSize)
{
	if ( upszImageBuffer == NULL )
	{
		FPRINTF("[Line : %d][%s] Decoded Image Buffer is NULL\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	if ( unDecodeSize == 0 )
	{
		FPRINTF("[Line : %d][%s] Decoded Image Buffer Size is zero\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	return true;
}

/**
* @function 		ImageUtilGetDataPath
* @description 		Get the path to application data directory
* @parameter[IN]	char* pszFileName [file name]
* @return 			NA
*/
char* ImageUtilGetDataPath(char *pszFileName)
{
	char *pszAppData = app_get_data_path(),*pszImgPath = NULL;
	if(pszAppData == NULL || strlen(pszAppData) == 0)
	{
		FPRINTF("[Line : %d][%s] app_get_data_path is failed, error returned = invalid path\\n", __LINE__, API_NAMESPACE);
		return pszImgPath;
	}
	
	pszImgPath = (char*) calloc(1, strlen(pszAppData) + strlen(pszFileName)+1);
	snprintf(pszImgPath, strlen(pszAppData) + strlen(pszFileName)+2, "%s%s",pszAppData, pszFileName);
	return pszImgPath;
}

/** @} */ //end of ctc-image-util