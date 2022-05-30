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

//& set: Camera

int g_nSupportedFormats = 0;

/**
* @function 		CTs_camera_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_camera_startup(void)
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
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Camera_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		CTs_camera_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_camera_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Camera_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

// At least one of these formats must be supported
int szSupportedFormats[] = {CAMERA_PIXEL_FORMAT_RGB565,
							CAMERA_PIXEL_FORMAT_ARGB,
							CAMERA_PIXEL_FORMAT_RGB888,
							CAMERA_PIXEL_FORMAT_RGBA,
							CAMERA_PIXEL_FORMAT_I420,
							CAMERA_PIXEL_FORMAT_JPEG,
							CAMERA_PIXEL_FORMAT_NV12,
							CAMERA_PIXEL_FORMAT_UYVY};

/**
* @function 		CameraPreviewFormatCallback
* @description	 	callback for camera preview
* @parameter		format : camera pixel format, user_data : user data sent to callback
* @return 			true
*/
static bool CameraPreviewFormatCallback(camera_pixel_format_e format, void *user_data)
{
	FPRINTF("[Line : %d][%s] CameraPreviewFormatCallback invoked, preview format supported = %d(%s) \\n", __LINE__, API_NAMESPACE, format, CameraPixelFormat(format));
	int nIterator;
	int nSize = sizeof(szSupportedFormats)/sizeof(int);
	for ( nIterator = 0; nIterator < nSize; nIterator++ )
	{
		if ( format == szSupportedFormats[nIterator] )
		{
			g_nSupportedFormats++;
		}
	}
	return true;
}
 
/** @addtogroup	ctc-camera-testcases
* @brief 		Integration testcases for module camera
* @ingroup		ctc-camera
* @{
*/

/**
* @testcase 		CTc_camera_supported_preview_pixel_format
* @since_tizen		2.3
* @author			SRID(tewari.r)
* @reviewer         SRID(gupta.sanjay)
* @type 			auto
* @scenario			Create a camera handler\n
* 					Set display handler and preview resolution\n
* 					Now perform start-preview by calling set-preview callback\n
* 					Get camera state and check camera's state equal preview state\n
* 					Confirm to act preview normal
* @apicovered		system_info_get_platform_bool,camera_unset_preview_cb,camera_create,camera_set_display,camera_set_preview_cb,camera_start_preview,camera_get_state,camera_stop_preview,camera_destroy
* @passcase			Return CAMERA_ERROR_NONE on Successful
* @failcase			Return  CAMERA_ERROR_INVALID_PARAMETER on failure
* @precondition		NA
* @postcondition	NA
*/
int CTc_camera_supported_preview_pixel_format(void)
{
	START_TEST;
	
	g_nSupportedFormats = 0;
	bool bCameraSupported;
	IS_FEATURE_SUPPORTED(CAMERA_FEAUTRE, bCameraSupported, API_NAMESPACE);
	
	if ( bCameraSupported )
	{
		/** Compliance specification states that if camera is supported then atleast one of :
		RGB565 : The RGB565 pixel format
		ARGB8888 : The ARGB8888 pixel format
		R8G8B8A8 : The R8G8B8A8 pixel format The order of color component is guaranteed by the byte unit.
		YCbCr420_PLANAR : The 8-bit Y-plane followed by 8-bit 2x2 sub sampled U-plane and V-plane
		JPEG : The encoded formats
		NV12 : The NV12 pixel formats
		UYVY :	The UYVY pixel format*/

		camera_h hCamera;
		int nRet = CAMERA_ERROR_NONE;
		nRet = camera_create(CAMERA_DEVICE_CAMERA0, &hCamera);
		PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_create", CameraGetError(nRet));
		
		nRet = camera_foreach_supported_preview_format(hCamera, CameraPreviewFormatCallback, NULL);
		PRINT_RESULT_CLEANUP(CAMERA_ERROR_NONE, nRet, "camera_foreach_supported_preview_format", CameraGetError(nRet), camera_destroy(hCamera));
		
		if ( g_nSupportedFormats == 0 )
		{
			FPRINTF("[Line : %d][%s] No supported pixel format among the mentioned ones\\n", __LINE__, API_NAMESPACE);
			camera_destroy(hCamera);
			return 1;
		}
		
		FPRINTF("[Line : %d][%s] %d pixel formats supported among the mentioned ones\\n", __LINE__, API_NAMESPACE, g_nSupportedFormats);
		camera_destroy(hCamera);
	}	
	return 0;
}

/** @} */ //end of ctc-camera-testcases
/** @} */ //end of ctc-camera