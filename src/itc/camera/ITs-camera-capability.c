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
#include "ITs-camera-common.h"

/** @addtogroup itc-camera
*  @ingroup itc
*  @{
*/

//& set: Camera
static camera_h g_camera;
 static camera_device_e g_eCameraDev = CAMERA_DEVICE_CAMERA0;
 static bool g_bCameraCreation = false;
 static GMainLoop *g_pCameraMainLoop = NULL;

 static bool g_bCallbackHit = false;
 static bool g_bFeatureCamera = false;
 static bool g_bFeatureCameraBack = false;
 static bool g_bFeatureCameraFront = false;
 static bool g_bFeatureCameraBackFlash = false;
 static bool g_bFeatureCameraFrontFlash = false;
 static bool g_bCameraReadFeatureStatusDone = false;

 static bool g_bSkipExecutionWithPass = false;
 static bool g_bSkipExecutionWithFail = false;

 static camera_pixel_format_e g_eCamPixFmt;
 static int g_nCapResWidth;
 static int g_nCapResHeight;

/**
* @function 		CameraTimeout
* @description	 	Called if some callback is not invoked for a particular CameraTimeout
* @parameter		gpointer data
* @return 			gboolean
*/
static gboolean CameraTimeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
		g_main_loop_unref(pMainLoop);
		pMainLoop = NULL;
	}
	FPRINTF("[Line : %d][%s] Callback CameraTimeout\\n", __LINE__, API_NAMESPACE);
	return false;
}

/**
* @function 		ITs_camera_startup
* @description	 	Called before each test, created camera handle
* @parameter		NA
* @return 			NA
*/
void ITs_camera_capability_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Camera_p\\n", __LINE__, API_NAMESPACE, API_NAMESPACE);
#endif

	if ( false == g_bCameraReadFeatureStatusDone )
	{
		g_bFeatureCamera = TCTCheckSystemInfoFeatureSupported(CAMERA_FEATURE, API_NAMESPACE);
		g_bFeatureCameraBack = TCTCheckSystemInfoFeatureSupported(CAMERA_FEATURE_BACK, API_NAMESPACE);
		g_bFeatureCameraFront = TCTCheckSystemInfoFeatureSupported(CAMERA_FEATURE_FRONT, API_NAMESPACE);
		g_bFeatureCameraBackFlash = TCTCheckSystemInfoFeatureSupported(CAMERA_FEATURE_BACK_FLASH, API_NAMESPACE);
		g_bFeatureCameraFrontFlash = TCTCheckSystemInfoFeatureSupported(CAMERA_FEATURE_FRONT_FLASH, API_NAMESPACE);

		g_bCameraReadFeatureStatusDone = true;
	}

	/* camera_Create required atleast one feature "http://tizen.org/feature/camera.back" or
	"http://tizen.org/feature/camera.front" so checking accordingly, As we have used camera_Create
	in startup, if this is not supported we will skip execution for TC, as this is precondition for all*/


	int nRet = camera_create(g_eCameraDev, &g_camera);
	if ( (g_bFeatureCameraBack == false ) && (g_bFeatureCameraFront == false ) )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			/* The API required atleast one feature "http://tizen.org/feature/camera.back" || "http://tizen.org/feature/camera.front"
			But both camera back and camera front features are not supported,
			also the API returned CAMERA_ERROR_NOT_SUPPORTED, hence we can conclude that feature not supported and skip execution
			with verdict as pass tc as feature could not be checked*/

			g_bSkipExecutionWithPass = true;
			return;
		}

		/* The API required atleast one feature "http://tizen.org/feature/camera.back" || "http://tizen.org/feature/camera.front"
		both camera back and camera front features are not supported, but the API did not return CAMERA_ERROR_NOT_SUPPORTED,
		we can conclude that feature values in model_config does not match with API return type*/

		g_bSkipExecutionWithFail = true;
		return;
	}

	if ( nRet != CAMERA_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to Create camera, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		g_bCameraCreation = false;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Camera created successfully\\n", __LINE__, API_NAMESPACE);
		g_bCameraCreation = true;
	}
	return;
}

/**
* @function 		ITs_camera_cleanup
* @description	 	Called after each test, destroys camera handle
* @parameter		NA
* @return 			NA
*/
void ITs_camera_capability_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Camera_p\\n", __LINE__, API_NAMESPACE, API_NAMESPACE);
#endif

	int nRet = camera_destroy(g_camera);
	if ( nRet != CAMERA_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] camera_Destroy failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
	}
	else
	{
		g_camera = NULL;
		FPRINTF("[Line : %d][%s] Camera destroyed successfully\\n", __LINE__, API_NAMESPACE);
	}
	return;
}




/**
* @function 		CameraAttrSupportedExposureModeCB
* @description	 	Callback function which is invoked when camera_attr_foreach_supported_exposure_mode is called
* @parameter		camera_attr_af_mode_e mode, void *user_data : user data to be passed
* @return 			false: skip next value, true: check next value
*/
static bool CameraAttrSupportedExposureModeCB(camera_attr_exposure_mode_e mode, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached camera supported exposure mode callback, supported mode = %d\\n", __LINE__, API_NAMESPACE, mode);
#endif

	usleep(5000);
	g_bCallbackHit = true;
	if ( user_data != NULL )
	{
		*( (camera_attr_exposure_mode_e *)user_data) = mode;
	}
	return false;
}

/**
* @function 		CameraAttrSupportedPreviewFormatCB
* @description	 	Callback function which is invoked when camera_foreach_supported_preview_format is called
* @parameter		camera_pixel_format_e format, void *user_data : user data to be passed
* @return 			false: skip next value, true: check next value
*/
static bool CameraAttrSupportedPreviewFormatCB(camera_pixel_format_e format, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached camera supported preview format callback, supported format = %d\\n", __LINE__, API_NAMESPACE, format);
#endif

	usleep(5000);
	g_bCallbackHit = true;
	g_eCamPixFmt = format;
	camera_pixel_format_e *peFormat = NULL;

	if ( user_data == NULL )
	{
		FPRINTF("[Line : %d][%s] user data is null \\n", __LINE__, API_NAMESPACE);
	}

	if ( user_data != NULL )
	{
		peFormat = (camera_pixel_format_e *)user_data;
		*peFormat = format;
	}

	return false;
}


/**
* @function 		CameraAttrSupportedPreviewResolutionCB
* @description	 	Callback function which is invoked when camera_foreach_supported_preview_resolution is called
* @parameter		int width, int height, void *user_data : user data to be passed
* @return 			false: skip next value, true: check next value
*/
static bool CameraAttrSupportedPreviewResolutionCB(int width, int height, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached camera supported preview resolution callback, supported width = %d, height = %d\\n", __LINE__, API_NAMESPACE, width, height);
#endif

	usleep(5000);
	g_bCallbackHit = true;
	g_nCapResWidth = width;
	g_nCapResHeight = height;
	CameraResolution *pstCamRes = NULL;

	if ( user_data == NULL )
	{
		FPRINTF("[Line : %d][%s] user data is null \\n", __LINE__, API_NAMESPACE);
	}

	if ( user_data != NULL )
	{
		pstCamRes = (CameraResolution *)user_data;
		pstCamRes->nWidth = width;
		pstCamRes->nHeight = height;
	}

	return false;
}



/**
* @function 		CameraAttrSupportedAfModeCB
* @description	 	Callback function which is invoked when camera_attr_foreach_supported_af_mode is called
* @parameter		camera_attr_af_mode_e mode, void *user_data : user data to be passed
* @return 			false: skip next value, true: check next value
*/
static bool CameraAttrSupportedAfModeCB(camera_attr_af_mode_e mode, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached camera supported af mode callback, supported mode = %d\\n", __LINE__, API_NAMESPACE, mode);
#endif

	usleep(5000);
	g_bCallbackHit = true;

	if ( user_data != NULL )
	{
		*( (camera_attr_af_mode_e *)user_data) = mode;
	}

	return true;
}


/**
* @function 		CameraAttrSupportedEffectCB
* @description	 	Callback function which is invoked when camera_attr_foreach_supported_effect is called
* @parameter		camera_attr_af_mode_e mode, void *user_data : user data to be passed
* @return 			false: skip next value, true: check next value
*/
static bool CameraAttrSupportedEffectCB(camera_attr_effect_mode_e effect, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached camera supported effect callback, supported effect = %d\\n", __LINE__, API_NAMESPACE, effect);
#endif

	usleep(5000);
	g_bCallbackHit = true;
	if ( user_data != NULL )
	{
		*( (camera_attr_effect_mode_e *)user_data) = effect;
	}

	return true;
}


/**
* @function 		CameraAttrSupportedFlashModeCB
* @description	 	Callback function which is invoked when camera_attr_foreach_supported_flash_mode is called
* @parameter		camera_attr_flash_mode_e mode, void *user_data : user data to be passed
* @return 			false: skip next value, true: check next value
*/
static bool CameraAttrSupportedFlashModeCB(camera_attr_flash_mode_e mode, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached camera supported flash mode callback, supported mode = %d\\n", __LINE__, API_NAMESPACE, mode);
#endif

	usleep(5000);
	g_bCallbackHit = true;
	if ( user_data != NULL )
	{
		*( (camera_attr_flash_mode_e *)user_data) = mode;
	}

	return true;
}


/**
* @function 		CameraAttrSupportedFpsCB
* @description	 	Callback function which is invoked when camera_attr_foreach_supported_fps is called
* @parameter		camera_attr_fps_e mode, void *user_data : user data to be passed
* @return 			false: skip next value, true: check next value
*/
static bool CameraAttrSupportedFpsCB(camera_attr_fps_e mode, void *user_data)
{
//#if DEBUG
	FPRINTF("[Line : %d][%s] reached camera supported fps callback, supported mode = %d\\n", __LINE__, API_NAMESPACE, mode);
//#endif

	usleep(5000);
	g_bCallbackHit = true;
	if ( user_data != NULL )
	{
		*( (camera_attr_fps_e *)user_data) = mode;
	}
	return false;
}


/**
* @function 		CameraAttrSupportedIsoCB
* @description	 	Callback function which is invoked when camera_attr_foreach_supported_iso is called
* @parameter		camera_attr_iso_e mode, void *user_data : user data to be passed
* @return 			false: skip next value, true: check next value
*/
static bool CameraAttrSupportedIsoCB(camera_attr_iso_e mode, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached camera supported iso callback, supported mode = %d\\n", __LINE__, API_NAMESPACE, mode);
#endif

	usleep(5000);
	g_bCallbackHit = true;
	if ( user_data != NULL )
	{
		*( (camera_attr_iso_e *)user_data) = mode;
	}
	return false;
}


/**
* @function 		CameraAttrSupportedSceneModeCB
* @description	 	Callback function which is invoked when camera_attr_foreach_supported_scene_mode is called
* @parameter		camera_attr_scene_mode_e mode, void *user_data : user data to be passed
* @return 			false: skip next value, true: check next value
*/
static bool CameraAttrSupportedSceneModeCB(camera_attr_scene_mode_e mode, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached camera supported scene mode callback, supported mode = %d\\n", __LINE__, API_NAMESPACE, mode);
#endif

	usleep(5000);
	g_bCallbackHit = true;
	if ( user_data != NULL )
	{
		*( (camera_attr_scene_mode_e *)user_data) = mode;
	}
	return false;
}


/**
* @function 		CameraAttrSupportedWhiteBalanceCB
* @description	 	Callback function which is invoked when camera_attr_foreach_supported_whitebalance is called
* @parameter		camera_attr_whitebalance_e mode, void *user_data : user data to be passed
* @return 			NA
*/
static bool CameraAttrSupportedWhiteBalanceCB(camera_attr_whitebalance_e mode, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached camera supported white balance callback, supported mode = %d\\n", __LINE__, API_NAMESPACE, mode);
#endif

	usleep(5000);
	g_bCallbackHit = true;
	if ( user_data != NULL )
	{
		*((camera_attr_whitebalance_e* ) user_data ) = mode;
	}

	return true;
}


/**
* @function 		CameraAttrSupportedCaptureFormatCB
* @description	 	Callback function which is invoked when camera_foreach_supported_capture_format is called
* @parameter		camera_pixel_format_e mode, void *user_data : user data to be passed
* @return 			false: skip next value, true: check next value
*/
static bool CameraAttrSupportedCaptureFormatCB(camera_pixel_format_e mode, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached camera supported capture format callback, supported mode = %d\\n", __LINE__, API_NAMESPACE, mode);
#endif
	usleep(5000);
	g_bCallbackHit = true;

	g_eCamPixFmt = mode;
	if ( user_data == NULL )
	{
		FPRINTF("[Line : %d][%s] user data is null \\n", __LINE__, API_NAMESPACE);
	}

	if ( user_data != NULL )
	{
		*( (camera_pixel_format_e *)user_data) = mode;
	}

	return true;
}



/**
* @function 		CameraAttrSupportedStreamFlipCB
* @description	 	Callback function which is invoked when camera_attr_foreach_supported_stream_flip is called
* @parameter		camera_flip_e flip, void *user_data : user data to be passed
* @return 			false: skip next value, true: check next value
*/

static bool CameraAttrSupportedStreamFlipCB(camera_flip_e flip, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached camera supported stream flip callback, supported mode = %d\\n", __LINE__, API_NAMESPACE, flip);
#endif
	usleep(5000);
	g_bCallbackHit = true;
	if ( user_data != NULL )
	{
		*( (camera_flip_e *)user_data) = flip;
	}
	return true;
}



/**
* @function 		CameraAttrSupportedStreamRotationCB
* @description	 	Callback function which is invoked when camera_attr_foreach_supported_stream_rotation is called
* @parameter		camera_rotation_e rotation, void *user_data : user data to be passed
* @return 			false: skip next value, true: check next value
*/
static bool CameraAttrSupportedStreamRotationCB(camera_rotation_e rotation, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached camera supported stream rotation callback, supported mode = %d\\n", __LINE__, API_NAMESPACE, rotation);
#endif
	usleep(5000);
	g_bCallbackHit = true;
	if ( user_data != NULL )
	{
		*( (camera_rotation_e *)user_data) = rotation;
	}

	return true;
}


/**
* @function 		CameraAttrSupportedCaptureResolutionCB
* @description	 	Callback function which is invoked when camera_foreach_supported_capture_resolution is called
* @parameter		int width, int height, void *user_data : user data to be passed
* @return 			false: skip next value, true: check next value
*/
static bool CameraAttrSupportedCaptureResolutionCB(int width, int height, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached camera supported capture resolution callback, supported width = %d, height = %d\\n", __LINE__, API_NAMESPACE, width, height);
#endif

	usleep(5000);
	g_bCallbackHit = true;
	g_nCapResWidth = width;
	g_nCapResHeight = height;
	CameraResolution *pstCamRes = NULL;

	if ( user_data == NULL )
	{
		FPRINTF("[Line : %d][%s] user data is null \\n", __LINE__, API_NAMESPACE);
	}

	if ( user_data != NULL )
	{
		pstCamRes = (CameraResolution *)user_data;
		pstCamRes->nWidth = width;
		pstCamRes->nHeight = height;
	}

	return false;
}




/**
* @function 		DeviceStateChangedCB
* @description	 	Callback function which is invoked when camera_add_device_state_changed_cb is called
* @parameter		int width, int height, void *user_data : user data to be passed
* @return 			false: skip next value, true: check next value
*/

static bool CameraDeviceStateChangedCB(camera_device_e device, camera_device_state_e state, void *user_data)
{
	g_bCallbackHit = true;
	FPRINTF("reached camera add device state changed callback");
	usleep(5000);
	if ( g_pCameraMainLoop )
	{
		g_main_loop_quit(g_pCameraMainLoop);
		g_main_loop_unref(g_pCameraMainLoop);
		g_pCameraMainLoop = NULL;
	}
	
	return false;
}



//& purpose: Checks if continuous_capture is supported.
//& type: auto
/**
* @testcase 			ITc_camera_is_supported_continuous_capture_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Checks if continuous_capture is supported
* @scenario				Check if continuous_capture is supported
* @apicovered			camera_is_supported_continuous_capture
* @passcase				Always pass if API does not crash, just prints if anti shake is supported or not.
* @failcase				If camera_is_supported_continuous_capture crashes or throws exception.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_is_supported_continuous_capture_p(void)
{
	START_TEST;

	// Target API
	bool bRetVal = camera_is_supported_continuous_capture(g_camera);
	if ( g_bFeatureCamera == false )
	{
		if ( bRetVal == true )
		{
			FPRINTF("[Line : %d][%s] [Not supported] According to feature value from model_config, continuous_capture should not be supported, but API says supported\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] continuous_capture is not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	else
	{
		/** although feature http://tizen.org/feature/camera, is true, still continuous capture might not be supported*/
		if ( bRetVal == false )
		{
			FPRINTF("[Line : %d][%s] continuous_capture is not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}

	return 0;
}


//& purpose: Get supported preview resolution
//& type: auto
/**
* @testcase 			ITc_camera_foreach_supported_preview_resolution_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Get supported preview resolution
* @scenario				Get supported preview resolution
* @apicovered			camera_foreach_supported_preview_resolution
* @passcase				When camera_foreach_supported_preview_resolution passes
* @failcase				If target API camera_foreach_supported_preview_resolution fails or callback is not invoked.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_foreach_supported_preview_resolution_p(void)
{
	START_TEST;
	CameraResolution stSetCamRes;

	g_bCallbackHit = false;
	int nRet = camera_foreach_supported_preview_resolution(g_camera, CameraAttrSupportedPreviewResolutionCB, (void*)(&stSetCamRes));
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_foreach_supported_preview_resolution");
	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] preview resolution not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s] camera_foreach_supported_preview_resolution failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}
	else if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] callback did not invoke\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( (stSetCamRes.nWidth != g_nCapResWidth) || (stSetCamRes.nHeight != g_nCapResHeight) )
	{
		FPRINTF("[Line : %d][%s] stSetCamRes values are not properly passed from CB funtion. \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Get supported capture resolution
//& type: auto
/**
* @testcase 			ITc_camera_foreach_supported_capture_resolution_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Get supported capture resolution
* @scenario				Get supported capture resolution
* @apicovered			camera_foreach_supported_capture_resolution
* @passcase				When camera_foreach_supported_capture_resolution passes
* @failcase				If target API camera_foreach_supported_capture_resolutionfails or callback is not invoked.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_foreach_supported_capture_resolution_p(void)
{
	START_TEST;
	CameraResolution stSetCamRes;

	g_bCallbackHit = false;
	int nRet = camera_foreach_supported_capture_resolution(g_camera, CameraAttrSupportedCaptureResolutionCB, (void *)(&stSetCamRes));
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_foreach_supported_capture_resolution");
	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] capture resolution not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
		FPRINTF("[Line : %d][%s] camera_foreach_supported_capture_resolution failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}
	else if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] callback did not invoke\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( (stSetCamRes.nWidth != g_nCapResWidth) || (stSetCamRes.nHeight != g_nCapResHeight) )
	{
		FPRINTF("[Line : %d][%s] stSetCamRes values are not properly passed from CB funtion. \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Get supported capture format.
//& type: auto
/**
* @testcase 			ITc_camera_foreach_supported_capture_format_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Get supported capture format
* @scenario				Get supported capture format
* @apicovered			camera_foreach_supported_capture_format
* @passcase				When camera_foreach_supported_capture_format passes
* @failcase				If target API camera_foreach_supported_capture_formatfails or callback is not invoked.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_foreach_supported_capture_format_p(void)
{
	START_TEST;
	camera_pixel_format_e eSetVal;

	g_bCallbackHit = false;
	int nRet = camera_foreach_supported_capture_format(g_camera, CameraAttrSupportedCaptureFormatCB, (void*)(&eSetVal));
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_foreach_supported_capture_format");

	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] capture format not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
		FPRINTF("[Line : %d][%s] camera_foreach_supported_capture_format failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}
	else if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s]callback did not invoke\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( eSetVal != g_eCamPixFmt )
	{
		FPRINTF("[Line : %d][%s] eSetVal is not properly passed from CB funtion. \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}


//& purpose: Get supported preview format.
//& type: auto
/**
* @testcase 			ITc_camera_foreach_supported_preview_format_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Get supported preview format
* @scenario				Get supported preview format
* @apicovered			camera_foreach_supported_preview_format
* @passcase				When camera_foreach_supported_preview_format passes
* @failcase				If target API camera_foreach_supported_preview_formatfails or callback is not invoked.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_foreach_supported_preview_format_p(void)
{
	START_TEST;
	camera_pixel_format_e eSetVal;

	g_bCallbackHit = false;
	int nRet = camera_foreach_supported_preview_format(g_camera, CameraAttrSupportedPreviewFormatCB, (void*)(&eSetVal));
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_foreach_supported_preview_format");
	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] preview format not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s] camera_foreach_supported_preview_format failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}
	else if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s]callback did not invoke\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( eSetVal != g_eCamPixFmt )
	{
		FPRINTF("[Line : %d][%s] eSetVal is not properly passed from CB funtion. \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Checks if face detection is supported.
//& type: auto
/**
* @testcase 			ITc_camera_is_supported_face_detection_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Checks if face detection is supported
* @scenario				Check if face detection is supported
* @apicovered			camera_is_supported_face_detection
* @passcase				Always passes if camera_is_supported_face_detection does not crash, and tells if face detection is supported or not on the device.
* @failcase				If camera_is_supported_face_detection crashes or throws exception.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_is_supported_face_detection_p(void)
{
	START_TEST;

	bool bRetVal = camera_is_supported_face_detection(g_camera );
	if ( g_bFeatureCamera == false )
	{
		if ( bRetVal == true )
		{
			FPRINTF("[Line : %d][%s] According to feature value from model_config, it should not be supported, but API says supported\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] [Not supported] face detection is not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	else
	{
		/** camera_is_supported_face_detection required feature http://tizen.org/feature/camera, whose value is true, but is_supported still returns false*/
		if ( bRetVal == false )
		{
			FPRINTF("[Line : %d][%s] [Not supported] face detection is not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}

	return 0;
}


//& purpose: Checks if zero shutter lag is supported.
//& type: auto
/**
* @testcase 			ITc_camera_is_supported_zero_shutter_lag_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Checks if zero shutter lag is supported
* @scenario				Check if zero shutter lag is supported
* @apicovered			camera_is_supported_zero_shutter_lag
* @passcase				Always passes if camera_is_supported_zero_shutter_lag does not crash, and tells if zero shutter lag is supported or not on the device.
* @failcase				If camera_is_supported_zero_shutter_lag crashes or throws exception.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_is_supported_zero_shutter_lag_p(void)
{
	START_TEST;

	bool bRetVal = camera_is_supported_zero_shutter_lag(g_camera );
	if ( g_bFeatureCamera == false )
	{
		if ( bRetVal == true )
		{
			FPRINTF("[Line : %d][%s]According to feature value from model_config, zero shutter lag should not be supported, but API says supported\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] [Not supported] zero shutter lag is not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	else
	{
		/** although feature http://tizen.org/feature/camera, is true, still zero shutter might not be supported */
		if ( bRetVal == false )
		{
			FPRINTF("[Line : %d][%s] [Not supported] zero shutter lag is not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	return 0;
}


//& purpose: Gets device count.
//& type: auto
/**
* @testcase 			ITc_camera_get_device_count_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Get device count
* @scenario				Get device count
* @apicovered			camera_get_device_count
* @passcase				When camera_get_device_count is successful
* @failcase				If target API camera_get_device_count fails
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_get_device_count_p(void)
{
	START_TEST;

	int nDeviceCount = -1;
	int nRet = camera_get_device_count(g_camera, &nDeviceCount);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_get_device_count");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_get_device_count", CameraGetError(nRet));

	if ( nDeviceCount == -1 )
	{
		FPRINTF("[Line : %d][%s] unable to get device count\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Gets the state of camera device.
//& type: auto
/**
* @testcase 			ITc_camera_get_device_state_p
* @since_tizen 			3.0
* @author				SRID(satinder.s)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Gets the state of camera 
* @scenario				Gets the state of camera
* @apicovered			camera_get_device_state
* @passcase				When camera_get_device_state is successful
* @failcase				If target API camera_get_device_state fails
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released 
*/
int ITc_camera_get_device_state_p(void)
{
	START_TEST;

	camera_device_state_e device_state = -1;
	
	int nRet = camera_get_device_state(g_eCameraDev, &device_state);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_get_device_state");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_get_device_state", CameraGetError(nRet));
	
	if(device_state < CAMERA_DEVICE_STATE_NULL || device_state > CAMERA_DEVICE_STATE_WORKING)
	{ 
		FPRINTF("[Line : %d][%s] camera_get_device_state returned invalid output parameter\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}



//& purpose: Check add and remove device state changed callback.
//& type: auto
/**
* @testcase 			ITc_camera_add_remove_device_state_changed_cb_p
* @since_tizen 			3.0
* @author				SRID(satinder.s)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Check add and remove device state changed callback.
* @scenario				Check add and remove device state changed callback.
* @apicovered			1. camera_add_device_state_changed_cb
						2. camera_remove_device_state_changed_cb
* @passcase				When camera_add_remove_device_state_changed_cb is successful
* @failcase				If target API camera_add_remove_device_state_changed_cb fails
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_add_remove_device_state_changed_cb_p(void)
{
	START_TEST;
	g_bCallbackHit = false;

	int nCB_id = -1,nCameraTimeoutId = 0;
	
	int nRet = camera_add_device_state_changed_cb(CameraDeviceStateChangedCB, NULL ,&nCB_id);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_add_device_state_changed_cb");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_add_device_state_changed_cb", CameraGetError(nRet));

	nRet = camera_start_preview(g_camera);
	RUN_POLLING_LOOP;
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_start_preview", CameraGetError(nRet));

	if ( nCB_id < 0 )
	{
		FPRINTF("[Line : %d][%s] callback id returned zero\\n", __LINE__, API_NAMESPACE);
		camera_stop_preview(g_camera);
		return 1;
	}
	if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] callback did not invoke\\n", __LINE__, API_NAMESPACE);
		camera_stop_preview(g_camera);
		return 1;
	}
	
	nRet = camera_remove_device_state_changed_cb(nCB_id);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_remove_device_state_changed_cb", CameraGetError(nRet));
	
	nRet = camera_stop_preview(g_camera);
	PRINT_RESULT_NORETURN(CAMERA_ERROR_NONE, nRet, "camera_stop_preview", CameraGetError(nRet));

	return 0;
}


//& purpose: Gets the media packet preview callback feature's supported state
//& type: auto
/**
* @testcase 			ITc_camera_is_supported_media_packet_preview_cb_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the media packet preview callback feature's supported state
* @scenario				Gets the media packet preview callback feature's supported state
* @apicovered			camera_is_supported_media_packet_preview_cb
* @passcase				When camera_is_supported_media_packet_preview_cb does not crash, it just tells if media preview is supported or not
* @failcase				If target API camera_is_supported_media_packet_preview_cb crashes.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_is_supported_media_packet_preview_cb_p(void)
{
	START_TEST;

	bool bRetVal = camera_is_supported_media_packet_preview_cb(g_camera);
	if ( g_bFeatureCamera == false )
	{
		if ( bRetVal == true )
		{
			FPRINTF("[Line : %d][%s] [Not supported] According to feature value from model_config, media_packet_preview should not be supported, but API says supported\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] media_packet_preview is not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	else
	{
		if ( bRetVal == false )
		{
			FPRINTF("[Line : %d][%s] [Not supported] According to feature value from model_config, media_packet_preview should be supported, but API says not supported\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	return 0;
}


//& purpose: Get supported fps.
//& type: auto
/**
* @testcase 			ITc_camera_attr_foreach_supported_fps_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Get supported fps
* @scenario				Get supported fps
* @apicovered			camera_attr_foreach_supported_fps
* @passcase				When camera_attr_foreach_supported_fps passes
* @failcase				If target API camera_attr_foreach_supported_fpsfails or callback is not invoked.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_foreach_supported_fps_p(void)
{
	START_TEST;

	g_bCallbackHit = false;
	int nRet = camera_attr_foreach_supported_fps(g_camera, CameraAttrSupportedFpsCB, NULL);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_fps");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_foreach_supported_fps", CameraGetError(nRet));
	if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] callback did not invoke\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}



//& purpose: Get for each supported fps by resolution
//& type: auto
/**
* @testcase 			ITc_camera_attr_foreach_supported_fps_by_resolution_p
* @since_tizen 			2.4
* @author				SRID(arjun.kumar)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Get all fps at given resolution by invoking callback function
* @scenario				Get for each supported fps at provided resolution
* @apicovered			camera_attr_foreach_supported_fps_by_resolution
* @passcase				When camera_attr_foreach_supported_fps_by_resolution passes
* @failcase				If target API camera_attr_foreach_supported_fps_by_resolution fails or callback is not invoked.
* @precondition			N/A
* @postcondition		N/A
*/
int ITc_camera_attr_foreach_supported_fps_by_resolution_p(void)
{
	START_TEST;
	CameraResolution stPreviewresolution = {0};

	g_bCallbackHit = false;
	int nRet = camera_foreach_supported_preview_resolution(g_camera, CameraAttrSupportedPreviewResolutionCB, (void *)(&stPreviewresolution));
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_foreach_supported_preview_resolution");

	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] preview not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
		FPRINTF("[Line : %d][%s]failed to get supported resolution\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	else if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s]callback did not invoke\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( (stPreviewresolution.nWidth != g_nCapResWidth) || (stPreviewresolution.nHeight != g_nCapResHeight) )
	{
		FPRINTF("[Line : %d][%s] stPreviewresolution values are not properly passed from CB funtion. \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bFeatureCamera = TCTCheckSystemInfoFeatureSupported(CAMERA_FEATURE, API_NAMESPACE);
	g_bFeatureCameraBack = TCTCheckSystemInfoFeatureSupported(CAMERA_FEATURE_BACK, API_NAMESPACE);
	g_bFeatureCameraFront = TCTCheckSystemInfoFeatureSupported(CAMERA_FEATURE_FRONT, API_NAMESPACE);

	nRet = camera_attr_foreach_supported_fps_by_resolution(g_camera, stPreviewresolution.nWidth, stPreviewresolution.nHeight, CameraAttrSupportedFpsCB, NULL);

	if ( !g_bFeatureCamera && !g_bFeatureCameraBack && !g_bFeatureCameraFront )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("\\n[Line : %d][%s] camera_attr_foreach_supported_fps_by_resolution returned %s error for unsupported feature",__LINE__, API_NAMESPACE, CameraGetError(nRet));
			return 1;;
		}
		FPRINTF("\\n[Line : %d][%s] camera_attr_foreach_supported_fps_by_resolution API call correctly returned %s error for unsupported feature",__LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 0;
	}

	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_foreach_supported_fps_by_resolution", CameraGetError(nRet));

	return 0;
}


//& purpose:Get supported af mode.
//& type: auto
/**
* @testcase 			ITc_camera_attr_foreach_supported_af_mode_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Get supported af mode
* @scenario				Get supported af mode
* @apicovered			camera_attr_foreach_supported_af_mode
* @passcase				When camera_attr_foreach_supported_af_mode passes
* @failcase				If target API camera_attr_foreach_supported_af_mode fails or callback is not invoked.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_foreach_supported_af_mode_p(void)
{
	START_TEST;

	g_bCallbackHit = false;
	int nRet = camera_attr_foreach_supported_af_mode(g_camera, CameraAttrSupportedAfModeCB , NULL);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_af_mode");
	//CHECK_CALLBACK_STATUS("CameraAttrSupportedAfModeCB");
	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] auto focus not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
		FPRINTF("[Line : %d][%s] camera_attr_foreach_supported_af_mode failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}
	else if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] callback did not invoke\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Get supported exposure mode.
//& type: auto
/**
* @testcase 			ITc_camera_attr_foreach_supported_exposure_mode_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Get supported af mode
* @scenario				Get supported af mode
* @apicovered			camera_attr_foreach_supported_exposure_mode
* @passcase				When camera_attr_foreach_supported_exposure_mode passes
* @failcase				If target API camera_attr_foreach_supported_exposure_modefails or callback is not invoked.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_foreach_supported_exposure_mode_p(void)
{
	START_TEST;

	g_bCallbackHit = false;
	int nRet = camera_attr_foreach_supported_exposure_mode(g_camera, CameraAttrSupportedExposureModeCB, NULL);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_exposure_mode");
		usleep(6000);

	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] exposure not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s] camera_attr_foreach_supported_exposure_mode failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}
	else if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] callback did not invoke\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Get supported iso.
//& type: auto
/**
* @testcase 			ITc_camera_attr_foreach_supported_iso_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Get supported iso
* @scenario				Get supported iso
* @apicovered			camera_attr_foreach_supported_iso
* @passcase				When camera_attr_foreach_supported_iso passes
* @failcase				If target API camera_attr_foreach_supported_isofails or callback is not invoked.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_foreach_supported_iso_p(void)
{
	START_TEST;

	g_bCallbackHit = false;
	int nRet = camera_attr_foreach_supported_iso(g_camera, CameraAttrSupportedIsoCB, NULL);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_iso");
	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] iso not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
		FPRINTF("[Line : %d][%s] camera_attr_foreach_supported_iso failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}
	else if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] callback did not invoke\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Get supported white balance.
//& type: auto
/**
* @testcase 			ITc_camera_attr_foreach_supported_whitebalance_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Get supported white balance
* @scenario				Get supported white balance
* @apicovered			camera_attr_foreach_supported_whitebalance
* @passcase				When camera_attr_foreach_supported_whitebalance passes
* @failcase				If target API camera_attr_foreach_supported_whitebalancefails or callback is not invoked.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_foreach_supported_whitebalance_p(void)
{
	START_TEST;

	g_bCallbackHit = false;
	int nRet = camera_attr_foreach_supported_whitebalance(g_camera, CameraAttrSupportedWhiteBalanceCB, NULL);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_whitebalance");
	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] whitebalance not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
		FPRINTF("[Line : %d][%s] camera_attr_foreach_supported_whitebalance failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}
	else if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] callback did not invoke\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}



//& purpose: Get supported effect.
//& type: auto
/**
* @testcase 			ITc_camera_attr_foreach_supported_effect_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Get supported af mode
* @scenario				Get supported af mode
* @apicovered			camera_attr_foreach_supported_effect
* @passcase				When camera_attr_foreach_supported_effect passes
* @failcase				If target API camera_attr_foreach_supported_effectfails or callback is not invoked.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_foreach_supported_effect_p(void)
{
	START_TEST;

	g_bCallbackHit = false;
	int nRet = camera_attr_foreach_supported_effect (g_camera, CameraAttrSupportedEffectCB , NULL);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_effect");
	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] effect not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s] camera_attr_foreach_supported_effect failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}
	else if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] callback did not invoke\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Get supported scene mode.
//& type: auto
/**
* @testcase 			ITc_camera_attr_foreach_supported_scene_mode_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Get supported scene mode
* @scenario				Get supported scene mode
* @apicovered			camera_attr_foreach_supported_scene_mode
* @passcase				When camera_attr_foreach_supported_scene_mode passes
* @failcase				If target API camera_attr_foreach_supported_scene_modefails or callback is not invoked.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_foreach_supported_scene_mode_p(void)
{
	START_TEST;

	g_bCallbackHit = false;
	int nRet = camera_attr_foreach_supported_scene_mode(g_camera, CameraAttrSupportedSceneModeCB, NULL);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_scene_mode");
	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] scene mode not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
		FPRINTF("[Line : %d][%s] camera_attr_foreach_supported_scene_mode failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}
	else if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s]callback did not invoke\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Get supported flash mode.
//& type: auto
/**
* @testcase 			ITc_camera_attr_foreach_supported_flash_mode_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Get supported flash mode
* @scenario				Get supported flash mode
* @apicovered			camera_attr_foreach_supported_flash_mode
* @passcase				When camera_attr_foreach_supported_flash_mode passes
* @failcase				If target API camera_attr_foreach_supported_flash_mode fails or callback is not invoked.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_foreach_supported_flash_mode_p(void)
{
	START_TEST;

	if ( !(TCTCheckSystemInfoFeatureSupported("http://tizen.org/feature/camera.back.flash", API_NAMESPACE) ||
		TCTCheckSystemInfoFeatureSupported("http://tizen.org/feature/camera.front.flash", API_NAMESPACE)) )
	{
		FPRINTF("[Line : %d][%s] Required feature of camera is not supported. So leaving test", __LINE__, API_NAMESPACE);
		return 0;
	}


	g_bCallbackHit = false;
	int nRet = camera_attr_foreach_supported_flash_mode(g_camera, CameraAttrSupportedFlashModeCB, NULL);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_flash_mode");
	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] flash mode not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s] camera_attr_foreach_supported_flash_mode failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}
	else if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] callback did not invoke\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Get supported stream rotation.
//& type: auto
/**
* @testcase 			ITc_camera_attr_foreach_supported_stream_rotation_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Get supported stream rotation
* @scenario				Get supported stream rotation
* @apicovered			camera_attr_foreach_supported_stream_rotation
* @passcase				When camera_attr_foreach_supported_stream_rotation passes
* @failcase				If target API camera_attr_foreach_supported_stream_rotation fails or callback is not invoked.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_foreach_supported_stream_rotation_p(void)
{
	START_TEST;

	g_bCallbackHit = false;
	int nRet = camera_attr_foreach_supported_stream_rotation(g_camera, CameraAttrSupportedStreamRotationCB, NULL);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_stream_rotation");
	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] stream rotation not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s] camera_attr_foreach_supported_stream_rotation failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}
	else if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s]callback did not invoke\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Get supported stream flip.
//& type: auto
/**
* @testcase 			ITc_camera_attr_foreach_supported_stream_flip_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Get supported stream flip
* @scenario				Get supported stream flip
* @apicovered			camera_attr_foreach_supported_stream_flip
* @passcase				When camera_attr_foreach_supported_stream_flip passes
* @failcase				If target API camera_attr_foreach_supported_stream_flip fails or callback is not invoked.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_foreach_supported_stream_flip_p(void)
{
	START_TEST;

	g_bCallbackHit = false;
	int nRet = camera_attr_foreach_supported_stream_flip(g_camera, CameraAttrSupportedStreamFlipCB, NULL);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_stream_flip");
	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] stream flip not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
		FPRINTF("[Line : %d][%s] camera_attr_foreach_supported_stream_flip failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}
	else if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] callback did not invoke\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Checks if hdr capture is supported.
//& type: auto
/**
* @testcase 			ITc_camera_attr_is_supported_hdr_capture_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Checks if hdr capture is supported
* @scenario				Check if hdr capture is supported
* @apicovered			camera_attr_is_supported_hdr_capture
* @passcase				Always pass if API does not crash, and just prints if hdr capture is supported or not.
* @failcase				If camera_attr_is_supported_hdr_capture crashes or throws exception.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_is_supported_hdr_capture_p(void)
{
	START_TEST;

	bool bRetVal = camera_attr_is_supported_hdr_capture(g_camera);
	if ( g_bFeatureCamera == false )
	{
		if ( bRetVal == true )
		{
			FPRINTF("[Line : %d][%s] According to feature value from model_config, it should not be supported, but API says supported\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] [Not supported] hdr capture is not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	else
	{
		/** even if http://tizen.org/feature/camera, is true, still hdr capture might not be supported*/
		if ( bRetVal == false )
		{
			FPRINTF("[Line : %d][%s] [Not supported] hdr capture is not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	return 0;
}


//& purpose: Checks if antishake is supported.
//& type: auto
/**
* @testcase 			ITc_camera_attr_is_supported_anti_shake_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Checks if antishake is supported
* @scenario				Check if antishake is supported
* @apicovered			camera_attr_is_supported_anti_shake
* @passcase				Always pass if API does not crash, just prints if anti shake is supported or not.
* @failcase				If camera_attr_is_supported_anti_shake crashes or throws exception.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_is_supported_anti_shake_p(void)
{
	START_TEST;

	bool bRetVal = camera_attr_is_supported_anti_shake(g_camera);
	if ( g_bFeatureCamera == false )
	{
		if ( bRetVal == true )
		{
			FPRINTF("[Line : %d][%s] [Not supported] According to feature value from model_config, it should not be supported, but API says supported\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] anti shake is not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	else
	{
		/** even if tizen.org/feature/camera feature is true, still antishake might not be supported */
		if (bRetVal == false )
		{
			FPRINTF("[Line : %d][%s] anti shake is not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	return 0;
}


//& purpose: Checks if video_stabilization is supported.
//& type: auto
/**
* @testcase 			ITc_camera_attr_is_supported_video_stabilization_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Checks if video_stabilization is supported
* @scenario				Check if video_stabilization is supported
* @apicovered			camera_attr_is_supported_video_stabilization
* @passcase				Always passes if camera_attr_is_supported_video_stabilization does not crash, and tells if video_stabilization is supported or not on the device.
* @failcase				If camera_attr_is_supported_video_stabilization crashes or throws exception.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_is_supported_video_stabilization_p(void)
{
	START_TEST;

	bool bRetVal = camera_attr_is_supported_video_stabilization(g_camera );
	if ( g_bFeatureCamera == false )
	{
		if ( bRetVal == true )
		{
			FPRINTF("[Line : %d][%s] [Not supported] According to feature value from model_config, it should not be supported, but API says supported\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] video stabilization is not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	else
	{
		/** even if feature http://tizen.org/feature/camera, is true, still video_stabilisation may not be supported */
		if ( bRetVal == false )
		{
			FPRINTF("[Line : %d][%s] video stabilization is not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	return 0;
}

//& purpose: Checks if auto_contrast is supported.
//& type: auto
/**
* @testcase 			ITc_camera_attr_is_supported_auto_contrast_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Checks if auto_contrast is supported
* @scenario				Check if auto_contrast is supported
* @apicovered			camera_attr_is_supported_auto_contrast
* @passcase				Always pass if API does not crash, just prints if auto contrast is supported or not.
* @failcase				If camera_attr_is_supported_auto_contrast crashes or throws exception.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_is_supported_auto_contrast_p(void)
{
	START_TEST;

	// Target API
	bool bRetVal = camera_attr_is_supported_auto_contrast(g_camera);
	if ( g_bFeatureCamera == false )
	{
		if ( bRetVal == true )
		{
			FPRINTF("[Line : %d][%s] [Not supported] According to feature value from model_config, auto contrast should not be supported, but API says supported\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] auto contrast is not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	else
	{
		if ( bRetVal == false )
		{
			FPRINTF("[Line : %d][%s] [Not supported] According to feature value from model_config, auto contrast should be supported, but API says not supported\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	return 0;
}



/** @} */
/** @} */






