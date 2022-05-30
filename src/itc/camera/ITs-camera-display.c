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
 static bool g_bFeatureCamera = false;
 static bool g_bFeatureCameraBack = false;
 static bool g_bFeatureCameraFront = false;
 static bool g_bFeatureCameraBackFlash = false;
 static bool g_bFeatureCameraFrontFlash = false;
 static bool g_bCameraReadFeatureStatusDone = false;

 static bool g_bSkipExecutionWithPass = false;
 static bool g_bSkipExecutionWithFail = false;



/**
* @function 		ITs_camera_startup
* @description	 	Called before each test, created camera handle
* @parameter		NA
* @return 			NA
*/
void ITs_camera_display_startup(void)
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
void ITs_camera_display_cleanup(void)
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



//& purpose: Sets and gets display rotation.
//& type: auto
/**
* @testcase 			ITc_camera_set_get_display_rotation_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets display rotation
* @scenario				Set display rotation\n
* 						Get display rotation
* @apicovered			camera_set_display_rotation, camera_get_display_rotation
* @passcase				When camera_set_display_rotation and camera_get_display_rotation are successful and set/get values are matched.
* @failcase				If target API camera_set_display_rotation or camera_get_display_rotation fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_set_get_display_rotation_p(void)
{
	START_TEST;

	camera_rotation_e eSetVal = CAMERA_ROTATION_90;
	camera_rotation_e eGetVal;

	int nRet = camera_set_display_rotation(g_camera, eSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_set_display_rotation", CameraGetError(nRet));

	// Give some sleep between start and stop
	usleep(2000);

	nRet = camera_get_display_rotation(g_camera, &eGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_get_display_rotation", CameraGetError(nRet));

	if ( eSetVal != eGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Sets and gets display flip.
//& type: auto
/**
* @testcase 			ITc_camera_set_get_display_flip_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets display flip
* @scenario				Set display flip\n
* 						Get display flip
* @apicovered			camera_set_display_flip, camera_get_display_flip
* @passcase				When camera_set_display_flip and camera_get_display_flip are successful and set/get values are matched.
* @failcase				If target API camera_set_display_flip or camera_get_display_flip fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_set_get_display_flip_p(void)
{
	START_TEST;

	camera_flip_e eSetVal = CAMERA_FLIP_HORIZONTAL;
	camera_flip_e eGetVal;

	int nRet = camera_set_display_flip(g_camera, eSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_set_display_flip", CameraGetError(nRet));

	// Give some sleep between start and stop
	usleep(2000);

	nRet = camera_get_display_flip(g_camera, &eGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_get_display_flip", CameraGetError(nRet));

	if ( eSetVal != eGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}



//& purpose: Sets display and checks if it is visible.
//& type: auto
/**
* @testcase 			ITc_camera_set_display_isvisible_display_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets display and checks if it is visible.
* @scenario				Sets display\n
* 						check if display is visible
* @apicovered			camera_set_display_visible, camera_is_display_visible
* @passcase				When camera_set_display_visible and camera_is_display_visible are successful and set/get values are matched.
* @failcase				If target API camera_set_display_visible or camera_is_display_visible fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_set_display_isvisible_display_p(void)
{
	START_TEST;

	bool bSetVal = true;
	bool bGetVal;

	int nRet = camera_set_display_visible(g_camera, bSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_set_display_visible", CameraGetError(nRet));

	usleep(2000);

	nRet = camera_is_display_visible(g_camera, &bGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_is_display_visible", CameraGetError(nRet));

	if ( bSetVal != bGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Sets and gets display mode.
//& type: auto
/**
* @testcase 			ITc_camera_set_get_display_mode_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets display mode
* @scenario				Set display mode\n
* 						Get display mode
* @apicovered			camera_set_display_mode, camera_get_display_mode
* @passcase				When camera_set_display_mode and camera_get_display_mode are successful and set/get values are matched.
* @failcase				If target API camera_set_display_mode or camera_get_display_mode fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_set_get_display_mode_p(void)
{
	START_TEST;

	camera_display_mode_e eSetVal = CAMERA_DISPLAY_MODE_LETTER_BOX;
	camera_display_mode_e eGetVal;

	int nRet = camera_set_display_mode(g_camera, eSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_set_display_mode", CameraGetError(nRet));

	// Give some sleep between start and stop
	usleep(2000);

	nRet = camera_get_display_mode(g_camera, &eGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_get_display_mode", CameraGetError(nRet));

	if ( eSetVal != eGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


/** @} */
/** @} */
