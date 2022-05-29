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
#include "CTs-camera-common.h"

/** @addtogroup ctc-camera
* @ingroup		ctc
* @{
*/

/**
* @function 			CameraPixelFormat
* @description 			Returns pixel format description, corresponding to enum value
* @parameter	[IN]	int format [the enum value of pixel format]
* @return 				description of pixel format
*/
char* CameraPixelFormat(int format)
{
	char *szPixFormat = NULL;

	switch ( format )
	{
	case CAMERA_PIXEL_FORMAT_INVALID:	szPixFormat = "Invalid pixel format";				break;
	case CAMERA_PIXEL_FORMAT_NV12:		szPixFormat = "NV12 pixel format";					break;
	case CAMERA_PIXEL_FORMAT_NV12T:		szPixFormat = "NV12 Tiled pixel format";			break;
	case CAMERA_PIXEL_FORMAT_NV16:		szPixFormat = "NV16 pixel format";					break;
	case CAMERA_PIXEL_FORMAT_NV21:		szPixFormat = "NV21 pixel format";					break;
	case CAMERA_PIXEL_FORMAT_YUYV:		szPixFormat = "YUYV(YUY2) pixel format";			break;
	case CAMERA_PIXEL_FORMAT_UYVY:		szPixFormat = "UYVY pixel format";					break;
	case CAMERA_PIXEL_FORMAT_422P:		szPixFormat = "YUV422(Y:U:V) planar pixel format";	break;
	case CAMERA_PIXEL_FORMAT_I420:		szPixFormat = "I420 pixel format";					break;
	case CAMERA_PIXEL_FORMAT_YV12:		szPixFormat = "YV12 pixel format";					break;
	case CAMERA_PIXEL_FORMAT_RGB565:	szPixFormat = "RGB565 pixel format";				break;
	case CAMERA_PIXEL_FORMAT_RGB888:	szPixFormat = "RGB888 pixel format";				break;
	case CAMERA_PIXEL_FORMAT_RGBA:		szPixFormat = "RGBA pixel format";					break;
	case CAMERA_PIXEL_FORMAT_ARGB:		szPixFormat = "ARGB pixel format";					break;
	case CAMERA_PIXEL_FORMAT_JPEG:		szPixFormat = "Encoded pixel format";				break;
	}

	return szPixFormat;
}

/**
* @function 			CameraGetError
* @description 			Print message.
* @parameter	[IN]	pszApiName	[String pointer contains api name]
* 			 	[IN]	nRet		[api return value]
* @return 				NA
*/
char* CameraGetError(int nRet)
{
	char *pszErrorMsg = NULL;
	
	switch ( nRet )
	{
	case CAMERA_ERROR_NONE:						pszErrorMsg = "CAMERA_ERROR_NONE";					break;
	case CAMERA_ERROR_INVALID_PARAMETER:		pszErrorMsg = "CAMERA_ERROR_INVALID_PARAMETER";		break;
	case CAMERA_ERROR_INVALID_STATE:			pszErrorMsg = "CAMERA_ERROR_INVALID_STATE";			break;
	case CAMERA_ERROR_OUT_OF_MEMORY:			pszErrorMsg = "CAMERA_ERROR_OUT_OF_MEMORY";			break;
	case CAMERA_ERROR_DEVICE:					pszErrorMsg = "CAMERA_ERROR_DEVICE";				break;
	case CAMERA_ERROR_INVALID_OPERATION:		pszErrorMsg = "CAMERA_ERROR_INVALID_OPERATION";		break;
	case CAMERA_ERROR_SECURITY_RESTRICTED:		pszErrorMsg = "CAMERA_ERROR_SECURITY_RESTRICTED";	break;
	case CAMERA_ERROR_DEVICE_BUSY:				pszErrorMsg = "CAMERA_ERROR_DEVICE_BUSY";			break;
	case CAMERA_ERROR_DEVICE_NOT_FOUND:			pszErrorMsg = "CAMERA_ERROR_DEVICE_NOT_FOUND";		break;
	case CAMERA_ERROR_ESD:						pszErrorMsg = "CAMERA_ERROR_ESD";					break;
	case CAMERA_ERROR_PERMISSION_DENIED:		pszErrorMsg = "CAMERA_ERROR_PERMISSION_DENIED";		break;
	case TIZEN_ERROR_NOT_SUPPORTED:				pszErrorMsg = "TIZEN_ERROR_NOT_SUPPORTED";			break;
	default:									pszErrorMsg = "UNKNOWN";
	}

	return pszErrorMsg;
}

/** @} */ //end of ctc-camera
