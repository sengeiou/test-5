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

 static bool g_bCallbackHit = false;
 static bool g_bCameraCaptureStarted = false;
 static bool g_bCameraCaptureStopped = false;
static GMainLoop *g_pCameraMainLoop = NULL;

 static bool g_bFeatureCamera = false;
 static bool g_bFeatureCameraBack = false;
 static bool g_bFeatureCameraFront = false;
 static bool g_bFeatureCameraBackFlash = false;
 static bool g_bFeatureCameraFrontFlash = false;
 static bool g_bCameraReadFeatureStatusDone = false;

 static bool g_bSkipExecutionWithPass = false;
 static bool g_bSkipExecutionWithFail = false;
  
 
 #define BITRATE 16
 #define GOPINTERVAL 4  

/**
* @function 		ITs_camera_startup
* @description	 	Called before each test, created camera handle
* @parameter		NA
* @return 			NA
*/
void ITs_camera_attribute_startup(void)
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
void ITs_camera_attribute_cleanup(void)
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
* @function 		CameraCapturingCB
* @description	 	Callback function which is invoked when capture starts
* @parameter		camera_image_data_s *image, camera_image_data_s *postview, camera_image_data_s *thumbnail, void *user_data
* @return 			NA
*/
static void CameraCapturingCB(camera_image_data_s *image, camera_image_data_s *postview, camera_image_data_s *thumbnail, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached capturing started callback\\n", __LINE__, API_NAMESPACE);
#endif

	g_bCameraCaptureStarted = true;
	return;
}


/**
* @function 		CameraCapturingCompletedCB
* @description	 	Callback function which is invoked when capture completed
* @parameter		void *user_data : user data to be passed
* @return 			NA
*/
static void CameraCapturingCompletedCB(void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached capturing completed callback\\n", __LINE__, API_NAMESPACE);
#endif

	usleep(5000);
	g_bCameraCaptureStopped = true;
	if ( g_pCameraMainLoop )
	{
		g_main_loop_quit(g_pCameraMainLoop);
		g_main_loop_unref(g_pCameraMainLoop);
		g_pCameraMainLoop = NULL;
	}
	return;
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
* @function 		CameraAttrSupportedTheaterModeCB
* @description	 	Callback function which is invoked when camera_attr_foreach_supported_theater_mode is called
* @parameter		camera_attr_theater_mode_e mode, void *user_data : user data to be passed
* @return 			false: skip next value, true: check next value
*/
static bool CameraAttrSupportedTheaterModeCB(camera_attr_theater_mode_e mode, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached camera supported theatre mode callback, supported mode = %d\\n", __LINE__, API_NAMESPACE, mode);
#endif

	usleep(5000);
	g_bCallbackHit = true;
	if ( user_data != NULL )
	{
		*( (camera_attr_theater_mode_e *)user_data) = mode;
	}

	return true;
}


/**
* @function 		CameraAttrHdrProgressCB
* @description	 	Callback function which is invoked when camera_start_capture is called
* @parameter		int nPercent, void *user_data
* @return 			NA
*/
void CameraAttrHdrProgressCB(int nPercent, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached camera supported preview format callback, percent = %d\\n", __LINE__, API_NAMESPACE, nPercent);
#endif

	usleep(5000);
	g_bCallbackHit = true;
	return;
}

/**
* @function 		CameraAttrSupportedPtzTypeCB
* @description	 	Callback function which is invoked by camera_attr_foreach_supported_ptz_type
* @parameter		camera_attr_ptz_type_e type, void *user_data
* @return 			bool
*/
bool CameraAttrSupportedPtzTypeCB(camera_attr_ptz_type_e type, void *user_data)
{
	FPRINTF("[Line : %d][%s] callback hit CameraAttrSupportedPtzTypeCB \\n", __LINE__, API_NAMESPACE);
	g_bCallbackHit = true;
	return false;
}

/** @addtogroup itc-camera-testcases
*  @brief 		Integration testcases for module camera
*  @ingroup 	itc-camera
*  @{
*/

//& purpose: Sets and gets preview fps.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_preview_fps_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets preview fps
* @scenario				Set preview fps\n
* 						Get preview fps
* @apicovered			camera_attr_set_preview_fps, camera_attr_get_preview_fps
* @passcase				When camera_attr_set_preview_fps and camera_attr_get_preview_fps are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_preview_fps or camera_attr_get_preview_fps fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_preview_fps_p(void)
{
	START_TEST;
	camera_attr_fps_e eSetPreviewsFps /*= CAMERA_ATTR_FPS_AUTO*/;
	camera_attr_fps_e eGetPreviewsFps;

	g_bCallbackHit = false;
	int nRet = camera_attr_foreach_supported_fps(g_camera, CameraAttrSupportedFpsCB , (void*)(&eSetPreviewsFps));
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_fps");

	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] fps not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s]camera_attr_foreach_supported_fps failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}

	nRet = camera_attr_set_preview_fps(g_camera, eSetPreviewsFps);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_preview_fps", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_preview_fps(g_camera, &eGetPreviewsFps);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_preview_fps", CameraGetError(nRet));

	if ( eSetPreviewsFps != eGetPreviewsFps )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Sets and gets image quality.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_image_quality_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets image quality
* @scenario				Set image quality\n
* 						Get image quality
* @apicovered			camera_attr_set_image_quality, camera_attr_get_image_quality
* @passcase				When camera_attr_set_image_quality and camera_attr_get_image_quality are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_image_quality or camera_attr_get_image_quality fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_image_quality_p(void)
{
	START_TEST;

	int nSetVal = 1;
	int nGetVal;

	int nRet = camera_attr_set_image_quality(g_camera, nSetVal);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_set_image_quality");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_image_quality", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_image_quality(g_camera, &nGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_image_quality", CameraGetError(nRet));

	if ( nSetVal != nGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Sets and gets zoom .
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_zoom_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets zoom 9
* @scenario				Set zoom\n
* 						Get zoom
* @apicovered			camera_attr_set_zoom , camera_attr_get_zoom
* @passcase				When camera_attr_set_zoom and camera_attr_get_zoom are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_zoom or camera_attr_get_zoom fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_zoom_p(void)
{
	START_TEST;

	int nSetVal = 0;
	int nGetVal;
	int nMin = 0, nMax = 0;

	int nRet = camera_attr_get_zoom_range(g_camera, &nMin, &nMax);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_get_zoom_range");

	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] zoom not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s] camera_attr_get_zoom_range failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}
	else
	{
		FPRINTF("[Line : %d][%s] camera_attr_get_zoom_range min = %d, max = %d\\n", __LINE__, API_NAMESPACE, nMin, nMax);
		nSetVal = ( nMin + nMax ) / 2;
	}

	if ( nMin > nMax )
	{
		/** If Max value is less than Min value, it indicates zoom not supported*/
		FPRINTF("[Line : %d][%s][NOT SUPPORTED] zoom not supported on the device\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	nRet = camera_attr_set_zoom (g_camera, nSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_zoom", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_zoom (g_camera, &nGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_zoom", CameraGetError(nRet));

	if ( nSetVal != nGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Gets zoom range.
//& type: auto
/**
* @testcase 			ITc_camera_attr_get_zoom_range_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Gets zoom range
* @scenario				gets zoom range
* @apicovered			camera_attr_get_zoom_range
* @passcase				When camera_attr_get_zoom_range is successful
* @failcase				If target API camera_attr_get_zoom_range fails.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_get_zoom_range_p(void)
{
	START_TEST;

	int nMinVal = 0, nMaxVal = 0;
	int nRet = camera_attr_get_zoom_range(g_camera, &nMinVal, &nMaxVal);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_get_zoom_range");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_zoom_range", CameraGetError(nRet));

	FPRINTF("[Line : %d][%s] zoom range = %d ~ %d\\n", __LINE__, API_NAMESPACE, nMinVal, nMaxVal);
	return 0;
}


//& purpose: Sets and gets af mode.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_af_mode_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets af mode
* @scenario				Set af mode\n
* 						Get af mode
* @apicovered			camera_attr_set_af_mode, camera_attr_get_af_mode
* @passcase				When camera_attr_set_af_mode and camera_attr_get_af_mode are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_af_mode or camera_attr_get_af_mode fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_af_mode_p(void)
{
	START_TEST;
	camera_attr_af_mode_e eSetAFmode;
	camera_attr_af_mode_e eGetAFmode;

	g_bCallbackHit = false;
	int nRet = camera_attr_foreach_supported_af_mode(g_camera, CameraAttrSupportedAfModeCB, (void*)(&eSetAFmode));
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_af_mode");

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

	if ( eSetAFmode == CAMERA_ATTR_AF_NONE )
	{
		FPRINTF("[Line : %d][%s][NOT SUPPORTED] for each only gave CAMERA_ATTR_AF_NONE, which means not supported on the device\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	nRet = camera_attr_set_af_mode(g_camera, eSetAFmode);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_af_mode", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_af_mode(g_camera, &eGetAFmode);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_af_mode", CameraGetError(nRet));

	if ( eSetAFmode != eGetAFmode )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Sets and clears af area.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_clear_af_area_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and clears af area
* @scenario				Set af area\n
* 						clear af area
* @apicovered			camera_attr_set_af_area, camera_attr_clear_af_area
* @passcase				When camera_attr_set_af_area and camera_attr_clear_af_area are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_af_area or camera_attr_clear_af_area fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_clear_af_area_p(void)
{
	START_TEST;

	int nSetX = 1, nSetY = 1;
	camera_attr_af_mode_e eSetAFmode = CAMERA_ATTR_AF_NORMAL;
	g_bCallbackHit = false;

	int nRet = camera_attr_foreach_supported_af_mode(g_camera, CameraAttrSupportedAfModeCB, (void*)(&eSetAFmode));
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_af_mode");

	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] Auto focus not supported\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s] camera_attr_foreach_supported_af_mode failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}
	else if ( g_bCallbackHit == false || eSetAFmode == CAMERA_ATTR_AF_NONE )
	{
		FPRINTF("[Line : %d][%s][Not Supported] Auto focus not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	nRet = camera_attr_set_af_mode(g_camera, eSetAFmode);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_af_mode", CameraGetError(nRet));

	nRet = camera_attr_set_af_area(g_camera, nSetX, nSetY);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_af_area", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_clear_af_area(g_camera);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_clear_af_area", CameraGetError(nRet));

	return 0;
}

//& purpose: Sets and gets exposure mode.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_exposure_mode_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets exposure mode
* @scenario				Set exposure mode\n
* 						Get exposure mode
* @apicovered			camera_attr_set_exposure_mode, camera_attr_get_exposure_mode
* @passcase				When camera_attr_set_exposure_mode and camera_attr_get_exposure_mode are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_exposure_mode or camera_attr_get_exposure_mode fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_exposure_mode_p(void)
{
	START_TEST;

	camera_attr_exposure_mode_e eSetVal;
	camera_attr_exposure_mode_e eGetVal;
	g_bCallbackHit = false;

	int nRet = camera_attr_foreach_supported_exposure_mode(g_camera, CameraAttrSupportedExposureModeCB , (void*)(&eSetVal));
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_exposure_mode");

	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] exposure mode not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s]camera_attr_foreach_supported_exposure_mode failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}

	nRet = camera_attr_set_exposure_mode(g_camera, eSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_exposure_mode", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_exposure_mode(g_camera, &eGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_exposure_mode", CameraGetError(nRet));
	if ( eSetVal != eGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Sets and gets exposure value.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_exposure_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets exposure value
* @scenario				Set exposure\n
* 						Get exposure
* @apicovered			camera_attr_set_exposure, camera_attr_get_exposure
* @passcase				When camera_attr_set_exposure and camera_attr_get_exposure are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_exposure or camera_attr_get_exposure fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_exposure_p(void)
{
	START_TEST;

	int nSetVal, nGetVal;
	int nMinVal = 0, nMaxVal = 0;

	int nRet = camera_attr_get_exposure_range(g_camera, &nMinVal, &nMaxVal);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_get_exposure_range");
	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] exposure not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s] camera_attr_get_contrast_range failed , error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}

	nSetVal = (nMinVal + nMaxVal)/2;
	FPRINTF("[Line : %d][%s] set val = %d\\n", __LINE__, API_NAMESPACE, nSetVal);
	if ( nMinVal > nMaxVal )
	{
		// If Max value is less than Min value, it indicates exposure not supported
		FPRINTF("[Line : %d][%s][NOT SUPPORTED] exposure not supported on the device\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	nRet = camera_attr_set_exposure(g_camera, nSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_exposure", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_exposure(g_camera, &nGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_exposure", CameraGetError(nRet));
	if ( nSetVal != nGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}



//& purpose: Gets exposure range.
//& type: auto
/**
* @testcase 			ITc_camera_attr_get_exposure_range_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Gets exposure range
* @scenario				gets exposure range
* @apicovered			camera_attr_get_exposure_range
* @passcase				When camera_attr_get_exposure_range is successful
* @failcase				If target API camera_attr_get_exposure_range fails
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_get_exposure_range_p(void)
{
	START_TEST;

	int nMinVal = 0, nMaxVal = 0;
	int nRet = camera_attr_get_exposure_range(g_camera, &nMinVal, &nMaxVal);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_get_exposure_range");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_exposure_range", CameraGetError(nRet));

	FPRINTF("[Line : %d][%s] exposure range = %d ~ %d\\n", __LINE__, API_NAMESPACE, nMinVal, nMaxVal);
	return 0;
}

//& purpose: Sets and gets flash mode.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_flash_mode_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets flash mode
* @scenario				Set flash mode\n
* 						Get flash mode
* @apicovered			camera_attr_set_flash_mode, camera_attr_get_flash_mode
* @passcase				When camera_attr_set_flash_mode and camera_attr_get_flash_mode are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_flash_mode or camera_attr_get_flash_mode fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_flash_mode_p(void)
{
	START_TEST;

	if ( !(TCTCheckSystemInfoFeatureSupported("http://tizen.org/feature/camera.back.flash", API_NAMESPACE) ||
		TCTCheckSystemInfoFeatureSupported("http://tizen.org/feature/camera.front.flash", API_NAMESPACE)) )
	{
		FPRINTF("[Line : %d][%s] Required feature of camera is not supported. So leaving test", __LINE__, API_NAMESPACE);
		return 0;
	}

	camera_attr_flash_mode_e eSetVal;// = CAMERA_ATTR_FLASH_MODE_AUTO;
	camera_attr_flash_mode_e eGetVal;

	g_bCallbackHit = false;
	int nRet = camera_attr_foreach_supported_flash_mode(g_camera, CameraAttrSupportedFlashModeCB, (void*)(&eSetVal));

	if ( g_bFeatureCameraBackFlash == false && g_bFeatureCameraFrontFlash == false )
	{
		/** Flash feature not supported according to model-config.xml */

		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			/** camera_attr_foreach_supported_flash_mode required either of feature http://tizen.org/feature/camera.back.flash 'OR' http://tizen.org/feature/camera.front.flash,
			whose value is true, but is_supported still returns false*/
			FPRINTF("[Line : %d][%s] [Not supported] According to feature value from model_config, it should be supported, but API says not supported\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] camera_attr_foreach_supported_flash_mode call correctly returned %s error for unsupported feature", __LINE__, API_NAMESPACE, CameraGetError(nRet));
			return 0;
		}
	}
	nRet = camera_attr_set_flash_mode(g_camera, eSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_flash_mode", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_flash_mode(g_camera, &eGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_flash_mode", CameraGetError(nRet));

	if ( eSetVal != eGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Sets and gets iso.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_iso_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets iso
* @scenario				Set iso\n
* 						Get iso
* @apicovered			camera_attr_set_iso, camera_attr_get_iso
* @passcase				When camera_attr_set_iso and camera_attr_get_iso are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_iso or camera_attr_get_iso fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_iso_p(void)
{
	START_TEST;

	camera_attr_iso_e eSetVal /*= CAMERA_ATTR_ISO_AUTO*/;
	camera_attr_iso_e eGetVal;
	g_bCallbackHit = false;

	int nRet = camera_attr_foreach_supported_iso(g_camera, CameraAttrSupportedIsoCB , (void*)(&eSetVal));
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_iso");
	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] iso not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s]camera_attr_foreach_supported_iso failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}

	nRet = camera_attr_set_iso(g_camera, eSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_iso", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_iso(g_camera, &eGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_iso", CameraGetError(nRet));

	if ( eSetVal != eGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}



//& purpose: Sets and gets theatre mode.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_theater_mode_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets theatre mode
* @scenario				Set theatre mode\n
* 						Get theatre mode
* @apicovered			camera_attr_set_theater_mode, camera_attr_get_theater_mode
* @passcase				When camera_attr_set_theater_mode and camera_attr_get_theater_mode are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_theater_mode or camera_attr_get_theater_mode fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_theater_mode_p(void)
{
	START_TEST;

	camera_attr_theater_mode_e eSetVal;// = CAMERA_ATTR_THEATER_MODE_ENABLE;
	camera_attr_theater_mode_e nGetVal;
	g_bCallbackHit = false;

	int nRet = camera_attr_foreach_supported_theater_mode(g_camera, CameraAttrSupportedTheaterModeCB, (void*)(&eSetVal));
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_theater_mode");

	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] theatre mode not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s] camera_attr_foreach_supported_theater_mode failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}

	nRet = camera_attr_set_theater_mode(g_camera, eSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_theater_mode", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_theater_mode(g_camera, &nGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_theater_mode", CameraGetError(nRet));

	if ( eSetVal != nGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}



//& purpose: Sets and gets brightness.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_brightness_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets auto white balance lock
* @scenario				Set brightness\n
* 						Get brightness
* @apicovered			camera_attr_set_brightness, camera_attr_get_brightness
* @passcase				When camera_attr_set_brightness and camera_attr_get_brightness are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_brightness or camera_attr_get_brightness fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_brightness_p(void)
{
	START_TEST;

	int nSetValue = 1;
	int nGetValue;
	int nMinVal = 0, nMaxVal = 0;

	int nRet = camera_attr_get_brightness_range(g_camera, &nMinVal, &nMaxVal);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_get_brightness_range");

	if ( nRet != CAMERA_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] camera_attr_get_brightness_range failed , error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}

	if ( nMinVal > nMaxVal )
	{
		// If Max value is less than Min value, it indicates exposure not supported
		FPRINTF("[Line : %d][%s]Although feature http://tizen.org/feature/camera is true, max val is less than min val, which 			means brightness not supported device\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	nRet = camera_attr_set_brightness(g_camera, nSetValue);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_brightness", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_brightness(g_camera, &nGetValue);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_brightness", CameraGetError(nRet));

	if ( nSetValue != nGetValue )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Gets brightness range.
//& type: auto
/**
* @testcase 			ITc_camera_attr_get_brightness_range_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Gets brightness range
* @scenario				gets brightness range
* @apicovered			camera_attr_get_brightness_range
* @passcase				When camera_attr_get_brightness_range is successful
* @failcase				If target API camera_attr_get_brightness_range fails.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_get_brightness_range_p(void)
{
	START_TEST;

	int nMinVal = 0, nMaxVal = 0;
	int nRet = camera_attr_get_brightness_range(g_camera, &nMinVal, &nMaxVal);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_get_brightness_range");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_brightness_range", CameraGetError(nRet));

	FPRINTF("[Line : %d][%s] brightness range = %d ~ %d\\n", __LINE__, API_NAMESPACE, nMinVal, nMaxVal);
	return 0;
}



//& purpose: Find contrast range, then set and get contrast.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_contrast_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Find contrast range, then set and get contrast
* @scenario				Find contrast range\n
*						Set contrast\n
* 						Get contrast
* @apicovered			camera_attr_get_contrast_range, camera_attr_set_contrast, camera_attr_get_contrast
* @passcase				When camera_attr_get_contrast_range, camera_attr_set_contrast and camera_attr_get_contrast are successful and set/get values are matched.
* @failcase				If target API camera_attr_get_contrast_range, camera_attr_set_contrast or camera_attr_get_contrast fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_contrast_p(void)
{
	START_TEST;

	int nSetVal;
	int nGetVal;
	int nContrastMin = 0, nContrastMax = 0;

	int nRet = camera_attr_get_contrast_range(g_camera, &nContrastMin, &nContrastMax);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_get_contrast_range");

	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] contrast not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s] camera_attr_get_contrast_range failed , error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}

	nSetVal = (nContrastMin + nContrastMax ) / 2;
	if ( nContrastMin > nContrastMax )
	{
		/** If Max value is less than Min value, it indicates zoom not supported*/
		FPRINTF("[Line : %d][%s][NOT SUPPORTED] contrast not supported on the device\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	nRet = camera_attr_set_contrast(g_camera, nSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_contrast", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_contrast(g_camera, &nGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_contrast", CameraGetError(nRet));

	if ( nSetVal != nGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Gets contrast range.
//& type: auto
/**
* @testcase 			ITc_camera_attr_get_contrast_range_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Gets contrast range
* @scenario				gets contrast range
* @apicovered			camera_attr_get_contrast_range
* @passcase				When camera_attr_get_contrast_range is successful
* @failcase				If target API camera_attr_get_contrast_range fails.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_get_contrast_range_p(void)
{
	START_TEST;

	int nMinVal = 0, nMaxVal = 0;
	int nRet = camera_attr_get_contrast_range(g_camera, &nMinVal, &nMaxVal);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_get_contrast_range");
	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] contrast not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s] camera_attr_get_contrast_range failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Contrast range = %d ~ %d\\n", __LINE__, API_NAMESPACE, nMinVal, nMaxVal);
	}
	return 0;
}


//& purpose: Sets and gets whitebalance
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_whitebalance_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets whitebalance
* @scenario				Set whitebalance\n
* 						Get whitebalance
* @apicovered			camera_attr_set_whitebalance , camera_attr_get_whitebalance
* @passcase				When camera_attr_set_whitebalance and camera_attr_get_whitebalance are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_whitebalance or camera_attr_get_whitebalance fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_whitebalance_p(void)
{
	START_TEST;

	camera_attr_whitebalance_e eSetVal;
	camera_attr_whitebalance_e nGetVal;
	g_bCallbackHit = false;

	int nRet = camera_attr_foreach_supported_whitebalance(g_camera, CameraAttrSupportedWhiteBalanceCB, (void*) &eSetVal);
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

	FPRINTF("[Line : %d][%s] Setting for enum %d\\n", __LINE__, API_NAMESPACE, eSetVal);

	nRet = camera_attr_set_whitebalance (g_camera, eSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_whitebalance", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_whitebalance (g_camera, &nGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_whitebalance", CameraGetError(nRet));

	if ( eSetVal != nGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Sets and gets effect.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_effect_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets effect
* @scenario				Set effect\n
* 						Get effect
* @apicovered			camera_attr_set_effect, camera_attr_get_effect
* @passcase				When camera_attr_set_effect and camera_attr_get_effect are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_effect or camera_attr_get_effect fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_effect_p(void)
{
	START_TEST;

	camera_attr_effect_mode_e eSetVal;
	camera_attr_effect_mode_e eGetVal;
	g_bCallbackHit = false;

	int nRet = camera_attr_foreach_supported_effect(g_camera, CameraAttrSupportedEffectCB , (void*)(&eSetVal));
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_effect");

	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] effect not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s]camera_attr_foreach_supported_effect failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}
	else if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] [Not Supported] Effect not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	if ( eSetVal == CAMERA_ATTR_EFFECT_NONE )
	{
		FPRINTF("[Line : %d][%s][NOT SUPPORTED] for each only gave CAMERA_ATTR_EFFECT_NONE, which means not supported on the device\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	nRet = camera_attr_set_effect(g_camera, eSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_effect", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_effect(g_camera, &eGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_effect", CameraGetError(nRet));

	if ( eSetVal != eGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Sets and gets scene mode.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_scene_mode_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets scene mode
* @scenario				Set scene mode\n
* 						Get scene mode
* @apicovered			camera_attr_set_scene_mode, camera_attr_get_scene_mode
* @passcase				When camera_attr_set_scene_mode and camera_attr_get_scene_mode are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_scene_mode or camera_attr_get_scene_mode fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_scene_mode_p(void)
{
	START_TEST;

	camera_attr_scene_mode_e eSetVal /*= CAMERA_ATTR_SCENE_MODE_NORMAL*/;
	camera_attr_scene_mode_e eGetVal;
	g_bCallbackHit = false;

	int nRet = camera_attr_foreach_supported_scene_mode(g_camera, CameraAttrSupportedSceneModeCB , (void*)(&eSetVal));
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_scene_mode");

	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] scene mode not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s]camera_attr_foreach_supported_scene_mode failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}

	nRet = camera_attr_set_scene_mode(g_camera, eSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_scene_mode", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_scene_mode(g_camera, &eGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_scene_mode", CameraGetError(nRet));

	if ( eSetVal != eGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Enables tag and checks if its is enabled.
//& type: auto
/**
* @testcase 			ITc_camera_attr_enable_is_enabled_tag_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Enables tag and checks if its is enabled
* @scenario				Enable tag\n
* 						check if tag is enabled
* @apicovered			camera_attr_enable_tag, camera_attr_is_enabled_tag
* @passcase				When camera_attr_enable_tag and camera_attr_is_enabled_tag are successful
* @failcase				If target API camera_attr_enable_tag or camera_attr_is_enabled_tag fails
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_enable_is_enabled_tag_p(void)
{
	START_TEST;

	bool bSetVal = true;
	bool bGetVal;

	int nRet = camera_attr_enable_tag(g_camera, bSetVal);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_enable_tag");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_enable_tag", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_is_enabled_tag(g_camera, &bGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_is_enabled_tag", CameraGetError(nRet));
	if ( bSetVal != bGetVal )
	{
		FPRINTF("[Line : %d][%s]Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Sets and gets tag image description.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_tag_image_description_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets tag image description
* @scenario				Set tag image description\n
* 						Get tag image description
* @apicovered			camera_attr_set_tag_image_description, camera_attr_get_tag_image_description
* @passcase				When camera_attr_set_tag_image_description and camera_attr_get_tag_image_description are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_tag_image_description or camera_attr_get_tag_image_description fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_tag_image_description_p(void)
{
	START_TEST;
	char szSetDescription[LOG]= {0};
	char *pszGetDescription = NULL;
	strncpy(szSetDescription, "Core API TCT-test", LOG);

	int nRet = camera_attr_set_tag_image_description(g_camera, szSetDescription);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_set_tag_image_description");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_tag_image_description", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_tag_image_description(g_camera, &pszGetDescription);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_tag_image_description", CameraGetError(nRet));
	CHECK_HANDLE(pszGetDescription, "camera_attr_get_tag_image_description");

	if ( strcmp(szSetDescription, pszGetDescription) != 0 )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszGetDescription);
		return 1;
	}
	FREE_MEMORY(pszGetDescription);

	return 0;
}


//& purpose: Sets and gets tag orientation.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_tag_orientation_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets tag orientation
* @scenario				Set tag orientation\n
* 						Get tag orientation
* @apicovered			camera_attr_set_tag_orientation, camera_attr_get_tag_orientation
* @passcase				When camera_attr_set_tag_orientation and camera_attr_get_tag_orientation are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_tag_orientation or camera_attr_get_tag_orientation fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_tag_orientation_p(void)
{
	START_TEST;

	camera_attr_tag_orientation_e eSetVal = CAMERA_ATTR_TAG_ORIENTATION_TOP_LEFT;
	camera_attr_tag_orientation_e nGetVal;

	int nRet = camera_attr_set_tag_orientation(g_camera, eSetVal);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_set_tag_orientation");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_tag_orientation", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_tag_orientation(g_camera, &nGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_tag_orientation", CameraGetError(nRet));

	if ( eSetVal != nGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Sets and gets tag software.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_tag_software_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets tag software
* @scenario				Set tag software\n
* 						Get tag software
* @apicovered			camera_attr_set_tag_software, camera_attr_get_tag_software
* @passcase				When camera_attr_set_tag_software and camera_attr_get_tag_software are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_tag_software or camera_attr_get_tag_software fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_tag_software_p(void)
{
	START_TEST;

	char szSetSoftwareInfo[LOG]= {0};
	char *pszGetSoftwareInfo = NULL;
	strncpy(szSetSoftwareInfo, "Tizen 2.3", LOG);

	int nRet = camera_attr_set_tag_software(g_camera, szSetSoftwareInfo);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_set_tag_software");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_tag_software", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_tag_software(g_camera, &pszGetSoftwareInfo);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_tag_software", CameraGetError(nRet));
	CHECK_HANDLE(pszGetSoftwareInfo, "camera_attr_get_tag_software");

	if ( strcmp(szSetSoftwareInfo, pszGetSoftwareInfo) != 0 )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszGetSoftwareInfo);
		return 1;
	}
	FREE_MEMORY(pszGetSoftwareInfo);

	return 0;
}


//& purpose: Sets, gets and remove geotag.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_remove_geotag_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets exposure value
* @scenario				Set geotag\n
* 						Get geotag\n
*						Remove geotag
* @apicovered			camera_attr_set_geotag, camera_attr_get_geotag
* @passcase				When camera_attr_set_geotag and camera_attr_get_geotag are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_geotag or camera_attr_get_geotag fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_remove_geotag_p(void)
{
	START_TEST;

	double dSetLat = 20.0, dSetLong = 20.0, dSetAlt = 20.0;
	double dGetLat, dGetLong, dGetAlt;

	int nRet = camera_attr_set_geotag(g_camera, dSetLat, dSetLong, dSetAlt);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_set_geotag");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_geotag", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_geotag(g_camera, &dGetLat, &dGetLong, &dGetAlt);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_geotag", CameraGetError(nRet));

	if (dSetLat != dGetLat || dSetLong != dGetLong || dSetAlt != dGetAlt)
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = camera_attr_remove_geotag(g_camera);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_remove_geotag", CameraGetError(nRet));

	return 0;
}


//& purpose: Gets lens orientation.
//& type: auto
/**
* @testcase 			ITc_camera_attr_get_lens_orientation_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets zoom
* @scenario				Get lens orientation
* @apicovered			camera_attr_get_lens_orientation
* @passcase				When camera_attr_get_lens_orientation is successful
* @failcase				If target API camera_attr_get_lens_orientation fails
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_get_lens_orientation_p(void)
{
	START_TEST;

	int nGetLensOrientation = -1;
	int nRet = camera_attr_get_lens_orientation (g_camera, &nGetLensOrientation);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_get_lens_orientation");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_lens_orientation", CameraGetError(nRet));

	FPRINTF("[Line : %d][%s] orientation = %d\\n", __LINE__, API_NAMESPACE, nGetLensOrientation);
	return 0;
}



//& purpose: Sets and gets stream rotation.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_stream_rotation_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets stream rotation
* @scenario				Set stream rotation\n
* 						Get stream rotation
* @apicovered			camera_attr_set_stream_rotation, camera_attr_get_stream_rotation
* @passcase				When camera_attr_set_stream_rotation and camera_attr_get_stream_rotation are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_stream_rotation or camera_attr_get_stream_rotation fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_stream_rotation_p(void)
{
	START_TEST;

	camera_rotation_e eSetVal;// = CAMERA_ROTATION_90;
	camera_rotation_e nGetVal;
	g_bCallbackHit = false;

	int nRet = camera_attr_foreach_supported_stream_rotation(g_camera, CameraAttrSupportedStreamRotationCB, (void*) &eSetVal);
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

	nRet = camera_attr_set_stream_rotation(g_camera, eSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_stream_rotation", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_stream_rotation(g_camera, &nGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_stream_rotation", CameraGetError(nRet));
	if ( eSetVal != nGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}



//& purpose: Sets and gets stream flip.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_stream_flip_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets stream flip
* @scenario				Set stream flip\n
* 						Get stream flip
* @apicovered			camera_attr_set_stream_flip, camera_attr_get_stream_flip
* @passcase				When camera_attr_set_stream_flip and camera_attr_get_stream_flip are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_stream_flip or camera_attr_get_stream_flip fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_stream_flip_p(void)
{
	START_TEST;

	camera_flip_e eSetVal;// = CAMERA_FLIP_HORIZONTAL;
	camera_flip_e nGetVal;
	g_bCallbackHit = false;

	int nRet = camera_attr_foreach_supported_stream_flip(g_camera, CameraAttrSupportedStreamFlipCB, (void*)(&eSetVal));
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

	nRet = camera_attr_set_stream_flip(g_camera, eSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_stream_flip", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_stream_flip(g_camera, &nGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_stream_flip", CameraGetError(nRet));

	if ( eSetVal != nGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}



//& purpose: Sets and gets hdr mode.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_hdr_mode_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets hdr mode
* @scenario				Set hdr mode\n
* 						Get hdr mode
* @apicovered			camera_attr_set_hdr_mode, camera_attr_get_hdr_mode
* @passcase				When camera_attr_set_hdr_mode and camera_attr_get_hdr_mode are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_hdr_mode or camera_attr_get_hdr_mode fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_hdr_mode_p(void)
{
	START_TEST;

	camera_attr_hdr_mode_e eSetVal = CAMERA_ATTR_HDR_MODE_ENABLE;
	camera_attr_hdr_mode_e eGetVal;

	bool bRet = camera_attr_is_supported_hdr_capture(g_camera );
	if ( g_bFeatureCamera == false )
	{
		if ( bRet == true )
		{
			/** camera_attr_is_supported_anti_shake required feature http://tizen.org/feature/camera, whose value is true, but is_supported still returns false*/
			FPRINTF("[Line : %d][%s] [Not supported] According to feature value from model_config, it should be supported, but API says not supported\\n", __LINE__, API_NAMESPACE);
			return 1;
		}

		FPRINTF("[Line : %d][%s] [Not supported] hdr capture not supported on the device\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	else
	{
		if ( bRet == false )
		{
			FPRINTF("[Line : %d][%s] [Not supported] hdr capture not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}

	int nRet = camera_attr_set_hdr_mode(g_camera, eSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_hdr_mode", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_get_hdr_mode(g_camera, &eGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_hdr_mode", CameraGetError(nRet));

	if ( eSetVal != eGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Sets/unsets hdr capture progress callback.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_unset_hdr_capture_progress_cb_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Checks if hdr capture is supported, sets /unsets hdr capture callback
* @scenario				Check if hdr capture is supported\n
*						Sets hdr mode\n
*						Sets hdr progress callback\n
*						starts capture\n
*						unset hdr progress callback
* @apicovered			camera_attr_is_supported_hdr_capture
* @passcase				Pass if camera_attr_set_hdr_capture_progress_cb, camera_attr_unset_hdr_capture_progress_cb and camera_start_capture pass and callback is invoked.
* @failcase				If camera_attr_set_hdr_capture_progress_cb, camera_attr_unset_hdr_capture_progress_cb or camera_start_capture fails, or callback is not invoked.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_unset_hdr_capture_progress_cb_p(void)
{
	START_TEST;

	int nCameraTimeoutId = 0;
	bool bRetVal = camera_attr_is_supported_hdr_capture(g_camera);
	if ( g_bFeatureCamera == false )
	{
		if ( bRetVal == true )
		{
			FPRINTF("[Line : %d][%s] According to feature value from model_config, hdr capture should not be supported, but API says supported\\n", __LINE__, API_NAMESPACE);
			return 1;
		}

		FPRINTF("[Line : %d][%s] [Not supported] hdr capture not supported on the device\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	else
	{
		if ( bRetVal == false )
		{
			FPRINTF("[Line : %d][%s] [Not supported] hdr capture not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}

	int nRet = camera_attr_set_hdr_mode(g_camera,CAMERA_ATTR_HDR_MODE_ENABLE );
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_hdr_mode", CameraGetError(nRet));

	if ( !(camera_is_supported_media_packet_preview_cb(g_camera)) )
	{
		FPRINTF("[Line : %d][%s][Not Supported] Media packet preview is not supported on this device\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	nRet = camera_start_preview (g_camera);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_start_preview", CameraGetError(nRet));

	g_bCallbackHit = false;

	nRet = camera_attr_set_hdr_capture_progress_cb(g_camera, CameraAttrHdrProgressCB, NULL);
	PRINT_RESULT_CLEANUP(CAMERA_ERROR_NONE, nRet, "camera_attr_set_hdr_capture_progress_cb", CameraGetError(nRet),camera_stop_preview(g_camera););

	nRet = camera_start_capture(g_camera, CameraCapturingCB, CameraCapturingCompletedCB, NULL );
	PRINT_RESULT_CLEANUP(CAMERA_ERROR_NONE, nRet, "camera_start_capture", CameraGetError(nRet), camera_attr_unset_hdr_capture_progress_cb(g_camera);camera_start_preview(g_camera);camera_stop_preview(g_camera););

	RUN_POLLING_LOOP;
	if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] callback did not invoke\\n", __LINE__, API_NAMESPACE);
		camera_attr_unset_hdr_capture_progress_cb(g_camera);
		camera_start_preview(g_camera);
		camera_stop_preview(g_camera);
		return 1;
	}

	nRet = camera_attr_unset_hdr_capture_progress_cb(g_camera);
	PRINT_RESULT_CLEANUP(CAMERA_ERROR_NONE, nRet, "camera_attr_unset_hdr_capture_progress_cb", CameraGetError(nRet), camera_start_preview(g_camera);camera_stop_preview(g_camera););
	camera_start_preview(g_camera);
	camera_stop_preview(g_camera);

	return 0;
}


//& purpose: Enables antishake and checks if it is enabled.
//& type: auto
/**
* @testcase 			ITc_camera_attr_enable_is_enabled_antishake_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			enables antishake and checks if it is enabled.
* @scenario				Check if antishake is supported\n
*						Enable antishake\n
* 						check if antishake is enabled
* @apicovered			camera_attr_enable_anti_shake, camera_attr_is_enabled_anti_shake
* @passcase				When camera_attr_enable_anti_shake and camera_attr_is_enabled_anti_shake are successful and set/get values are matched.
* @failcase				If target API camera_attr_enable_anti_shake or camera_attr_is_enabled_anti_shake fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_enable_is_enabled_antishake_p(void)
{
	START_TEST;

	bool bSetVal = true;
	bool bGetVal;

	bool bRet = camera_attr_is_supported_anti_shake(g_camera );
	if ( g_bFeatureCamera == false )
	{
		if ( bRet == true )
		{
			FPRINTF("[Line : %d][%s] According to feature value from model_config, anti_shake should not be supported, but API says supported\\n", __LINE__, API_NAMESPACE);
			return 1;
		}

		FPRINTF("[Line : %d][%s] [Not supported] anti shake not supported on the device\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	else
	{
		if ( bRet == false )
		{
			FPRINTF("[Line : %d][%s] [Not supported] anti shake not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	int nRet = camera_attr_enable_anti_shake(g_camera, bSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_enable_anti_shake", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_is_enabled_anti_shake(g_camera, &bGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_is_enabled_anti_shake", CameraGetError(nRet));

	if ( bSetVal != bGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Enables video stabilization and checks if its is enabled.
//& type: auto
/**
* @testcase 			ITc_camera_attr_enable_is_enabled_video_stabilization_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Enables video stabilization and checks if its is enabled
* @scenario				Enable video stabilization\n
* 						check if video stabilization is enabled
* @apicovered			camera_attr_enable_video_stabilization, camera_attr_is_enabled_video_stabilization
* @passcase				When camera_attr_enable_video_stabilization and camera_attr_is_enabled_video_stabilization are successful and set/get values are matched.
* @failcase				If target API camera_attr_enable_video_stabilization or camera_attr_is_enabled_video_stabilization fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_enable_is_enabled_video_stabilization_p(void)
{
	START_TEST;

	bool bSetVal = true;
	bool bGetVal;

	bool bRet = camera_attr_is_supported_video_stabilization(g_camera );
	if ( g_bFeatureCamera == false )
	{
		if ( bRet == true )
		{
			FPRINTF("[Line : %d][%s] [Not supported] According to feature value from model_config, video_stabilization should not be supported, but API says supported\\n", __LINE__, API_NAMESPACE);
			return 1;
		}

		FPRINTF("[Line : %d][%s] [Not supported] video stabilisation not supported on the device\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	else
	{
		if ( bRet == false )
		{
			/** feature tizen.org/feature/camera is true, but video stabilisation might not be supported */
			FPRINTF("[Line : %d][%s] [Not supported] video stabilisation not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}

	int nRet = camera_attr_enable_video_stabilization(g_camera, bSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_enable_video_stabilization", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_is_enabled_video_stabilization(g_camera, &bGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_is_enabled_video_stabilization", CameraGetError(nRet));
	if ( bSetVal != bGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Enables auto_contrast and checks if its is enabled.
//& type: auto
/**
* @testcase 			ITc_camera_attr_enable_is_enabled_auto_contrast_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Enables auto_contrast and checks if its is enabled
* @scenario				Enable auto_contrast\n
* 						check if auto_contrast is enabled
* @apicovered			camera_attr_enable_auto_contrast, camera_attr_is_enabled_auto_contrast
* @passcase				When camera_attr_enable_auto_contrast and camera_attr_is_enabled_auto_contrast are successful and set/get values are matched.
* @failcase				If target API camera_attr_enable_auto_contrast or camera_attr_is_enabled_auto_contrast fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_enable_is_enabled_auto_contrast_p(void)
{
	START_TEST;

	bool bSetVal = true;
	bool bGetVal;

	bool bRet = camera_attr_is_supported_auto_contrast(g_camera);
	if ( g_bFeatureCamera == false )
	{
		/** If feature tizen.org/feature/camera is false then auto contrast should also not be supported*/
		if ( bRet == true )
		{
			FPRINTF("[Line : %d][%s] [Not supported] According to feature value from model_config, camera_attr_is_supported_auto_contrast should not be supported, but API says supported\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		FPRINTF("[Line : %d][%s] [Not supported] auto contrast not supported on the device\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	else
	{
		/** If feature tizen.org/feature/camera is present then still specific feature auto contrast might not be supported*/
		if ( bRet == false )
		{
			FPRINTF("[Line : %d][%s] [Not supported] auto contrast not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}

	int nRet = camera_attr_enable_auto_contrast(g_camera, bSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_enable_auto_contrast", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_attr_is_enabled_auto_contrast(g_camera, &bGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_is_enabled_auto_contrast", CameraGetError(nRet));

	if ( bSetVal != bGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Disable shutter sound.
//& type: auto
/**
* @testcase 			ITc_camera_attr_disable_shutter_sound_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Disable shutter sound
* @scenario				Disable shutter sound
* @apicovered			camera_attr_disable_shutter_sound
* @passcase				When camera_attr_disable_shutter_sound is successful
* @failcase				If target API camera_attr_disable_shutter_sound fails
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_disable_shutter_sound_p(void)
{
	START_TEST;

	int nRet = camera_attr_disable_shutter_sound (g_camera, true);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_disable_shutter_sound");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_disable_shutter_sound", CameraGetError(nRet));

	return 0;
}
//& purpose: Sets and gets encoded preview bitrate .
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_encoded_preview_bitrate_p
* @since_tizen 			3.0
* @author				SRID(manu.tiwari)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			Sets and gets encoded preview bitrate
* @scenario				Set encoded preview bitrate\n
* 						Get encoded preview bitrate
* @apicovered			camera_attr_set_encoded_preview_bitrate , camera_attr_get_encoded_preview_bitrate
* @passcase				When camera_attr_set_encoded_preview_bitrate and camera_attr_get_encoded_preview_bitrate are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_encoded_preview_bitrate or camera_attr_get_encoded_preview_bitrate fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_encoded_preview_bitrate_p(void)
{
	START_TEST;
	int nGetVal;
	camera_pixel_format_e eSetFormat[] = {CAMERA_PIXEL_FORMAT_H264, CAMERA_PIXEL_FORMAT_MJPEG};
	int nEnumSize = sizeof(eSetFormat) / sizeof(eSetFormat[0]);
	int enum_counter = 0;
	bool l_bFeatureSupported = false;
	
	l_bFeatureSupported = g_bFeatureCamera && (g_bFeatureCameraBack || g_bFeatureCameraFront);
	
	for(enum_counter = 0 ; enum_counter < nEnumSize; enum_counter++)
	{
		int nRet = camera_set_preview_format(g_camera, eSetFormat[enum_counter]);
		CHECK_UNSUPPORTED_ERROR_RETURN(l_bFeatureSupported, "camera_set_preview_format");

		if ( nRet != CAMERA_ERROR_NONE )
		{
			if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("[Line : %d][%s][NOT SUPPORTED] format %d is not supported on the device\\n", __LINE__, API_NAMESPACE, eSetFormat[enum_counter]);
				return 0;
			}

			FPRINTF("[Line : %d][%s] camera_set_preview_format failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
			return 1;
		}

		PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_set_preview_format", CameraGetError(nRet));
		usleep(2000);

		nRet = camera_attr_set_encoded_preview_bitrate (g_camera, BITRATE);
		PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_encoded_preview_bitrate", CameraGetError(nRet));
		usleep(2000);

		nRet = camera_attr_get_encoded_preview_bitrate (g_camera, &nGetVal);
		PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_encoded_preview_bitrate", CameraGetError(nRet));

		if ( nGetVal != BITRATE )
		{
			FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	return 0;
	
}
//& purpose: Sets and gets encoded_preview_gop_interval.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_encoded_preview_gop_interval_p
* @since_tizen 			3.0
* @author				SRID(manu.tiwari)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			Sets and gets encoded_preview_gop_interval
* @scenario				Set encoded preview gop interval\n
* 						Get encoded preview gop interval
* @apicovered			camera_attr_set_encoded_preview_gop_interval , camera_attr_get_encoded_preview_gop_interval
* @passcase				When camera_attr_set_encoded_preview_gop_interval and camera_attr_get_encoded_preview_gop_interval are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_encoded_preview_gop_interval or camera_attr_get_encoded_preview_gop_interval fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_encoded_preview_gop_interval_p(void)
{
	START_TEST;

	int nGetVal;
	camera_pixel_format_e eSetFormat[] = {CAMERA_PIXEL_FORMAT_H264, CAMERA_PIXEL_FORMAT_MJPEG};
	int nEnumSize = sizeof(eSetFormat) / sizeof(eSetFormat[0]);
	int enum_counter=0;
	bool l_bFeatureSupported = false;

	l_bFeatureSupported = g_bFeatureCamera && (g_bFeatureCameraBack || g_bFeatureCameraFront);

	for(enum_counter = 0 ; enum_counter < nEnumSize; enum_counter++)
        {
		int nRet = camera_set_preview_format(g_camera, eSetFormat[enum_counter]);
		CHECK_UNSUPPORTED_ERROR_RETURN(l_bFeatureSupported, "camera_set_preview_format");

		if ( nRet != CAMERA_ERROR_NONE )
		{
			if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("[Line : %d][%s][NOT SUPPORTED] format %d is not supported on the device\\n", __LINE__, API_NAMESPACE, eSetFormat[enum_counter]);
				return 0;
			}

			FPRINTF("[Line : %d][%s] camera_set_preview_format failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
			return 1;
		}
		PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_set_preview_format", CameraGetError(nRet));
		usleep(2000);

		nRet = camera_attr_set_encoded_preview_gop_interval (g_camera, GOPINTERVAL);
		PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_encoded_preview_gop_interval", CameraGetError(nRet));
		usleep(2000);

		nRet = camera_attr_get_encoded_preview_gop_interval (g_camera, &nGetVal);
		PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_encoded_preview_gop_interval", CameraGetError(nRet));

		if ( nGetVal != GOPINTERVAL )
		{
			FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	return 0;
}	

//& purpose: Sets and gets pan.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_pan_p
* @since_tizen 			3.0
* @author				SRID(asit.s)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			Sets and gets pan
* @scenario				Set pan\n
* 						Get pan
* @apicovered			camera_attr_set_pan , camera_attr_get_pan
* @passcase				When camera_attr_set_pan and camera_attr_get_pan are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_pan or camera_attr_get_pan fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_pan_p(void)
{
	START_TEST;
	int SetPanDegree = 1;
	int GetPanDegree = 0;
	int nGetCameraAttr[] = {
			CAMERA_ATTR_PTZ_MOVE_ABSOLUTE ,
			CAMERA_ATTR_PTZ_MOVE_RELATIVE,
		};

	int nRet = -1;
	int nEnumStartCount = 0 ;

	int nGetCameraAttrCount = sizeof(nGetCameraAttr) / sizeof(nGetCameraAttr[0]);
	
	int nMin,nMax;
	nRet = camera_attr_get_pan_range(g_camera,&nMin,&nMax);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_get_pan_range");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_pan_range", CameraGetError(nRet));	
	//Note:- If the nMin value is greater than the nMax value, it means that this feature is not supported.
	if(nMin > nMax)
	{
		FPRINTF("[Line : %d][%s] nMin value is greater than nMax value ,it means that this feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	for(nEnumStartCount = 0 ; nEnumStartCount < nGetCameraAttrCount ; nEnumStartCount++ )
	{
	  nRet = camera_attr_set_pan(g_camera, nGetCameraAttr[nEnumStartCount], SetPanDegree);
	  PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_pan", CameraGetError(nRet));	  
	  
	  nRet = camera_attr_get_pan(g_camera,&GetPanDegree);
	  PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_pan", CameraGetError(nRet));	  
	  
	  if(GetPanDegree != SetPanDegree)
	  {
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	  }
	}

	return 0;
}


//& purpose: get pan range.
//& type: auto
/**
* @testcase 			ITc_camera_attr_get_pan_range_p
* @since_tizen 			3.0
* @author				SRID(asit.s)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			Sets and gets camera_attr_get_pan_range
* @scenario				Get pan range
* @apicovered			camera_attr_get_pan_range
* @passcase				When camera_attr_get_pan_range is successful.
* @failcase				If target API camera_attr_get_pan_range fails.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_get_pan_range_p(void)
{
	START_TEST;
	int min,max;
	int nRet = camera_attr_get_pan_range(g_camera,&min,&max);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_get_pan_range");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_pan_range", CameraGetError(nRet));	
	//Note:- If the min value is greater than the max value, it means that this feature is not supported.
	if(min > max)
	{
		FPRINTF("[Line : %d][%s] min value is greater than max value ,it means that this feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	return 0;
}


//& purpose: Sets and gets tilt.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_tilt_p
* @since_tizen 			3.0
* @author				SRID(asit.s)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			Sets and gets tilt
* @scenario				Set tilt\n
* 						Get tilt
* @apicovered			camera_attr_set_tilt , camera_attr_get_tilt
* @passcase				When camera_attr_set_tilt and camera_attr_get_tilt are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_tilt or camera_attr_get_tilt fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_tilt_p(void)
{
	START_TEST;

	int SettiltDegree = 1;
	int GettiltDegree = 0;
	int nGetCameraAttr[] = {
			CAMERA_ATTR_PTZ_MOVE_ABSOLUTE ,
			CAMERA_ATTR_PTZ_MOVE_RELATIVE,
		};

	int nRet = -1;
	int nEnumStartCount = 0 ;

	int nGetCameraAttrCount = sizeof(nGetCameraAttr) / sizeof(nGetCameraAttr[0]);

	int nMin,nMax;
	nRet = camera_attr_get_tilt_range(g_camera,&nMin,&nMax);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_get_tilt_range");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_tilt_range", CameraGetError(nRet));	
	//Note:- If the nMin value is greater than the nMax value, it means that this feature is not supported.
	if(nMin > nMax)
	{
		FPRINTF("[Line : %d][%s] nMin value is greater than nMax value ,it means that this feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	
	for(nEnumStartCount = 0 ; nEnumStartCount < nGetCameraAttrCount ; nEnumStartCount++ )
	{
	  nRet = camera_attr_set_tilt(g_camera, nGetCameraAttr[nEnumStartCount], SettiltDegree);
	  PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_tilt", CameraGetError(nRet));	  
	  
	  nRet = camera_attr_get_tilt(g_camera,&GettiltDegree);
	  PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_tilt", CameraGetError(nRet));	  
	  
	  if(GettiltDegree != SettiltDegree)
	  {
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	  }
	}

	return 0;
}


//& purpose: Get tilt range.
//& type: auto
/**
* @testcase 			ITc_camera_attr_get_tilt_range_p
* @since_tizen 			3.0
* @author				SRID(asit.s)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			Get tilt range.
* @scenario				Set tilt range.
* @apicovered			camera_attr_get_tilt_range. 
* @passcase				When camera_attr_get_tilt_range is successful.
* @failcase				If target API camera_attr_get_tilt_range is fails.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_get_tilt_range_p(void)
{
	START_TEST;
	int min,max;
	int nRet = camera_attr_get_tilt_range(g_camera,&min,&max);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_get_tilt_range");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_tilt_range", CameraGetError(nRet));	
	//Note:- If the min value is greater than the max value, it means that this feature is not supported.
	if(min > max)
	{
		FPRINTF("[Line : %d][%s] min value is greater than max value ,it means that this feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	return 0;
}


//& purpose: Sets camera_attr_set_ptz_type.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_ptz_type_p
* @since_tizen 			3.0
* @author				SRID(asit.s)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			Sets camera_attr_set_ptz_type.
* @scenario				Sets camera_attr_set_ptz_type.
* @apicovered			camera_attr_set_ptz_type.
* @passcase				When camera_attr_set_ptz_type is successful.
* @failcase				If target API camera_attr_set_ptz_type fails.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_ptz_type_p(void)
{
	START_TEST;
	int nGetCameraAttr[] = {
			CAMERA_ATTR_PTZ_TYPE_MECHANICAL ,
			CAMERA_ATTR_PTZ_TYPE_ELECTRONIC,
		};

	int nRet = -1;
	int nEnumStartCount = 0 ;

	int nGetCameraAttrCount = sizeof(nGetCameraAttr) / sizeof(nGetCameraAttr[0]);

	camera_attr_ptz_type_e ptz_type = -1;
	nRet = camera_attr_foreach_supported_ptz_type(g_camera, CameraAttrSupportedPtzTypeCB, &ptz_type);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_ptz_type");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_foreach_supported_ptz_type", CameraGetError(nRet));

	if ((int)ptz_type < 0) 
	{
		FPRINTF("[Line : %d][%s] PTZ is not supported.\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	
	for(nEnumStartCount = 0 ; nEnumStartCount < nGetCameraAttrCount ; nEnumStartCount++ )
	{
		nRet = camera_attr_set_ptz_type( g_camera, nGetCameraAttr[nEnumStartCount]);
		PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_ptz_type", CameraGetError(nRet));	
	}
	return 0;
}


//& purpose: call camera_attr_foreach_supported_ptz_type and hit callback camera_attr_supported_ptz_type_cb.
//& type: auto
/**
* @testcase 			ITc_camera_attr_foreach_supported_ptz_type_p
* @since_tizen 			3.0
* @author				SRID(asit.s)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			call camera_attr_foreach_supported_ptz_type and hit callback camera_attr_supported_ptz_type_cb.
* @scenario				create camera handle and call camera_attr_foreach_supported_ptz_type and hit callback camera_attr_supported_ptz_type_cb.
* @apicovered			camera_attr_foreach_supported_ptz_type .
* @passcase				When camera_attr_foreach_supported_ptz_type is successful.
* @failcase				If target API When camera_attr_foreach_supported_ptz_type is fails.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_foreach_supported_ptz_type_p(void)
{
	START_TEST;
	g_bCallbackHit = false;
		
	camera_attr_ptz_type_e ptz_type = -1;
	int nRet = camera_attr_foreach_supported_ptz_type(g_camera, CameraAttrSupportedPtzTypeCB, &ptz_type);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_ptz_type");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_foreach_supported_ptz_type", CameraGetError(nRet));

	if ((int)ptz_type < 0) 
	{
		FPRINTF("[Line : %d][%s] PTZ is not supported.\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] callback CameraAttrSupportedPtzTypeCB did not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}


//& purpose: Sets and gets Sets the ROI(Region Of Interest) area of display.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_display_roi_area_p
* @since_tizen 			3.0
* @author				SRID(asit.s)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			Sets and gets display roi area
* @scenario				Set display roi area\n
* 						Get display roi area
* @apicovered			camera_attr_set_display_roi_area , camera_attr_get_display_roi_area
* @passcase				When camera_attr_set_display_roi_area and camera_attr_get_display_roi_area are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_display_roi_area or camera_attr_get_display_roi_area fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_display_roi_area_p(void)
{
	START_TEST;
	int setx = 1, sety = 1, setwidth = 10, setheight = 20;
	int getx,gety,getwidth,getheight;
	
	int nRet = camera_set_display_mode(g_camera , CAMERA_DISPLAY_MODE_CUSTOM_ROI);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_set_display_mode", CameraGetError(nRet));
	
	nRet = camera_attr_set_display_roi_area( g_camera, setx, sety, setwidth, setheight);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_set_display_roi_area");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_display_roi_area", CameraGetError(nRet));
	
	nRet = camera_attr_get_display_roi_area( g_camera, &getx, &gety, &getwidth, &getheight);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_display_roi_area", CameraGetError(nRet));

	if( (setx != getx) || (sety != gety) || (setwidth != getwidth) || (setheight != getheight) )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}	
	
	return 0;
}

//& purpose: Sets and gets hue level.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_hue_p
* @since_tizen 			5.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Sets and gets hue level
* @scenario				Set hue level\n
* 						Get hue level
* @apicovered			camera_attr_set_hue , camera_attr_get_hue
* @passcase				When camera_attr_set_hue and camera_attr_get_hue are successful and set/get values are matched.
* @failcase				If target API camera_attr_set_hue or camera_attr_get_hue fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_hue_p(void)
{
	START_TEST;

	int nMinLevel, nMaxLevel, nGetLevel=0;

	int nRet = camera_attr_get_hue_range( g_camera, &nMinLevel, &nMaxLevel);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_get_hue_range");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_hue_range", CameraGetError(nRet));
	if(nMinLevel > nMaxLevel)
	{
		FPRINTF("[Line : %d][%s] Min value is greater than max value.Hue is not supported MinLevel%d MaxLevel%d\\n", __LINE__, API_NAMESPACE,nMinLevel,nMaxLevel);
		return 0;
	}

	nRet = camera_attr_set_hue( g_camera, nMaxLevel);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_set_hue", CameraGetError(nRet));

	nRet = camera_attr_get_hue( g_camera, &nGetLevel);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_hue", CameraGetError(nRet));

	if( nMaxLevel != nGetLevel )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets the available hue level
//& type: auto
/**
* @testcase 			ITc_camera_attr_get_hue_range_p
* @since_tizen 			5.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Gets the available hue level
* @scenario				Gets the available hue level
* @apicovered			camera_attr_get_hue_range
* @passcase				When camera_attr_get_hue_range is successful
* @failcase				If target API camera_attr_get_hue_range pass
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_get_hue_range_p(void)
{
	START_TEST;
	int nMinLevel, nMaxLevel, nGetLevel=0;

	int nRet = camera_attr_get_hue_range( g_camera, &nMinLevel, &nMaxLevel);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_get_hue_range");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_attr_get_hue_range", CameraGetError(nRet));
	if(nMinLevel > nMaxLevel)
	{
		FPRINTF("[Line : %d][%s] Min value is greater than max value.Hue is not supported MinLevel%d MaxLevel%d\\n", __LINE__, API_NAMESPACE,nMinLevel,nMaxLevel);
		return 0;
	}

	return 0;
}
/** @} */
/** @} */
