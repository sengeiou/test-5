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
#include "ITs-tbm-common.h"

/** @addtogroup itc-tbm
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		LibtbmGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char *LibtbmGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case TBM_SURFACE_ERROR_NONE:				szErrorVal = "TBM_SURFACE_ERROR_NONE";				break;
	case TBM_SURFACE_ERROR_INVALID_PARAMETER:	szErrorVal = "TBM_SURFACE_ERROR_INVALID_PARAMETER";	break;
	case TBM_SURFACE_ERROR_INVALID_OPERATION:	szErrorVal = "TBM_SURFACE_ERROR_INVALID_OPERATION";	break;
	default:									szErrorVal = "Unknown Error";						break;
	}
	return szErrorVal;
}

/**
* @function 		LibtbmCreateSurface
* @description	 	Helper function to create tbm surface
* @parameter		int
* @return 			bool
*/
bool LibtbmCreateSurface(unsigned int nFormat)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] Creating tbm surface for format = %s\\n", __LINE__, API_NAMESPACE, LibtbmGetFormatType(nFormat));
#endif
	g_surface = tbm_surface_create(128,128,nFormat);
	if ( g_surface != NULL )
	{
#if DEBUG
		FPRINTF("\\n[Line : %d][%s] tbm_surface_create passed in LibtbmCreateSurface\\n", __LINE__, API_NAMESPACE);
#endif
		return true;
	}
	else
	{
		FPRINTF("\\n[Line : %d][%s] tbm_surface_create failed in LibtbmCreateSurface, for Format = %s\\n", __LINE__, API_NAMESPACE, LibtbmGetFormatType(nFormat));
		return false;
	}
}
/**
* @function 		LibtbmDestroySurface
* @description	 	Helper function to destroy tbm surface
* @parameter		NA
* @return 			NA
*/
void LibtbmDestroySurface()
{
	int eRetValue = tbm_surface_destroy(g_surface);
	if ( TBM_SURFACE_ERROR_NONE == eRetValue )
	{
#if DEBUG
		FPRINTF("\\n[Line : %d][%s] tbm_surface_destroy passed in LibtbmDestroySurface\\n", __LINE__, API_NAMESPACE);			
#endif
	}
	else
	{
		FPRINTF("\\n[Line : %d][%s] tbm_surface_destroy failed in LibtbmDestroySurface, error = %s\\n", __LINE__, API_NAMESPACE, LibtbmGetError(eRetValue));
	}
}


/**
* @function 		LibtbmGetFormatType
* @description	 	Maps TBM format enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char *LibtbmGetFormatType(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case TBM_FORMAT_C8:					szErrorVal = "TBM_FORMAT_C8";					break;
	case TBM_FORMAT_RGB332:				szErrorVal = "TBM_FORMAT_RGB332";				break;
	case TBM_FORMAT_BGR233:				szErrorVal = "TBM_FORMAT_BGR233";				break;
	case TBM_FORMAT_XRGB4444:			szErrorVal = "TBM_FORMAT_XRGB4444";				break;
	case TBM_FORMAT_XBGR4444:			szErrorVal = "TBM_FORMAT_XBGR4444";				break;
	case TBM_FORMAT_RGBX4444:			szErrorVal = "TBM_FORMAT_RGBX4444";				break;
	case TBM_FORMAT_BGRX4444:			szErrorVal = "TBM_FORMAT_BGRX4444";				break;
	case TBM_FORMAT_ARGB4444:			szErrorVal = "TBM_FORMAT_ARGB4444";				break;
	case TBM_FORMAT_ABGR4444:			szErrorVal = "TBM_FORMAT_ABGR4444";				break;
	case TBM_FORMAT_RGBA4444:			szErrorVal = "TBM_FORMAT_RGBA4444";				break;
	case TBM_FORMAT_BGRA4444:			szErrorVal = "TBM_FORMAT_BGRA4444";				break;
	case TBM_FORMAT_XRGB1555:			szErrorVal = "TBM_FORMAT_XRGB1555";				break;
	case TBM_FORMAT_XBGR1555:			szErrorVal = "TBM_FORMAT_XBGR1555";				break;
	case TBM_FORMAT_RGBX5551:			szErrorVal = "TBM_FORMAT_RGBX5551";				break;
	case TBM_FORMAT_BGRX5551:			szErrorVal = "TBM_FORMAT_BGRX5551";				break;
	case TBM_FORMAT_ARGB1555:			szErrorVal = "TBM_FORMAT_ARGB1555";				break;
	case TBM_FORMAT_ABGR1555:			szErrorVal = "TBM_FORMAT_ABGR1555";				break;
	case TBM_FORMAT_RGBA5551:			szErrorVal = "TBM_FORMAT_RGBA5551";				break;
	case TBM_FORMAT_BGRA5551:			szErrorVal = "TBM_FORMAT_BGRA5551";				break;
	case TBM_FORMAT_RGB565:				szErrorVal = "TBM_FORMAT_RGB565";				break;
	case TBM_FORMAT_BGR565:				szErrorVal = "TBM_FORMAT_BGR565";				break;
	case TBM_FORMAT_RGB888:				szErrorVal = "TBM_FORMAT_RGB888";				break;
	case TBM_FORMAT_BGR888:				szErrorVal = "TBM_FORMAT_BGR888";				break;
	case TBM_FORMAT_XRGB8888:			szErrorVal = "TBM_FORMAT_XRGB8888";				break;
	case TBM_FORMAT_XBGR8888:			szErrorVal = "TBM_FORMAT_XBGR8888";				break;
	case TBM_FORMAT_RGBX8888:			szErrorVal = "TBM_FORMAT_RGBX8888";				break;
	case TBM_FORMAT_BGRX8888:			szErrorVal = "TBM_FORMAT_BGRX8888";				break;
	case TBM_FORMAT_ARGB8888:			szErrorVal = "TBM_FORMAT_ARGB8888";				break;
	case TBM_FORMAT_ABGR8888:			szErrorVal = "TBM_FORMAT_ABGR8888";				break;
	case TBM_FORMAT_RGBA8888:			szErrorVal = "TBM_FORMAT_RGBA8888";				break;
	case TBM_FORMAT_BGRA8888:			szErrorVal = "TBM_FORMAT_BGRA8888";				break;
	case TBM_FORMAT_XRGB2101010:		szErrorVal = "TBM_FORMAT_XRGB2101010";			break;
	case TBM_FORMAT_XBGR2101010:		szErrorVal = "TBM_FORMAT_XBGR2101010";			break;
	case TBM_FORMAT_RGBX1010102:		szErrorVal = "TBM_FORMAT_RGBX1010102";			break;
	case TBM_FORMAT_BGRX1010102:		szErrorVal = "TBM_FORMAT_BGRX1010102";			break;
	case TBM_FORMAT_ARGB2101010:		szErrorVal = "TBM_FORMAT_ARGB2101010";			break;
	case TBM_FORMAT_ABGR2101010:		szErrorVal = "TBM_FORMAT_ABGR2101010";			break;
	case TBM_FORMAT_RGBA1010102:		szErrorVal = "TBM_FORMAT_RGBA1010102";			break;
	case TBM_FORMAT_BGRA1010102:		szErrorVal = "TBM_FORMAT_BGRA1010102";			break;
	case TBM_FORMAT_YUYV:				szErrorVal = "TBM_FORMAT_YUYV";					break;
	case TBM_FORMAT_YVYU:				szErrorVal = "TBM_FORMAT_YVYU";					break;
	case TBM_FORMAT_UYVY:				szErrorVal = "TBM_FORMAT_UYVY";					break;
	case TBM_FORMAT_VYUY:				szErrorVal = "TBM_FORMAT_VYUY";					break;
	case TBM_FORMAT_AYUV:				szErrorVal = "TBM_FORMAT_AYUV";					break;
	case TBM_FORMAT_NV12:				szErrorVal = "TBM_FORMAT_NV12";					break;
	case TBM_FORMAT_NV21:				szErrorVal = "TBM_FORMAT_NV21";					break;
	case TBM_FORMAT_NV16:				szErrorVal = "TBM_FORMAT_NV16";					break;
	case TBM_FORMAT_NV61:				szErrorVal = "TBM_FORMAT_NV61";					break;
	case TBM_FORMAT_YUV410:				szErrorVal = "TBM_FORMAT_YUV410";				break;
	case TBM_FORMAT_YVU410:				szErrorVal = "TBM_FORMAT_YVU410";				break;
	case TBM_FORMAT_YUV411:				szErrorVal = "TBM_FORMAT_YUV411";				break;
	case TBM_FORMAT_YVU411:				szErrorVal = "TBM_FORMAT_YVU411";				break;
	case TBM_FORMAT_YUV420:				szErrorVal = "TBM_FORMAT_YUV420";				break;
	case TBM_FORMAT_YVU420:				szErrorVal = "TBM_FORMAT_YVU420";				break;
	case TBM_FORMAT_YUV422:				szErrorVal = "TBM_FORMAT_YUV422";				break;
	case TBM_FORMAT_YVU422:				szErrorVal = "TBM_FORMAT_YVU422";				break;
	case TBM_FORMAT_YUV444:				szErrorVal = "TBM_FORMAT_YUV444";				break;
	case TBM_FORMAT_YVU444:				szErrorVal = "TBM_FORMAT_YVU444";				break;
	default:							szErrorVal = "Unknown Format";					break;
	}
	return szErrorVal;
}
/** @} */