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

static camera_pixel_format_e g_eCamPixFmt;
static int g_nCapResWidth;
static int g_nCapResHeight;

static Evas_Object *camera_win = NULL;
bool g_bCameraWindowFail = false;

static void DeleteCameraWindow(void *data, Evas_Object *obj, void *event)
{
	return;
}

static void DestroyCameraWindow()
{
	if (camera_win) {
		evas_object_del(camera_win);
		camera_win = NULL;
	}

	return;
}

static void CreateCameraWindow()
{
	int w = 0;
	int h = 0;

	DestroyCameraWindow();   /* destroy window in case the clean_up is not called */

	camera_win = elm_win_util_standard_add("camera_itc", "camera_itc");

	if (camera_win) {
		elm_win_borderless_set(camera_win, EINA_TRUE);
		evas_object_smart_callback_add(camera_win, "delete,request", DeleteCameraWindow, NULL);
		elm_win_screen_size_get(camera_win, NULL, NULL, &w, &h);
		evas_object_resize(camera_win, w, h);
		elm_win_autodel_set(camera_win, EINA_TRUE);
	} else {
		FPRINTF("\n\nfail to create window\n\n");
		g_bCameraWindowFail = true;		
	}

	return;
}

/**
* @function 		ITs_camera_startup
* @description	 	Called before each test, created camera handle
* @parameter		NA
* @return 			NA
*/
void ITs_camera_startup(void)
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
void ITs_camera_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Camera_p\\n", __LINE__, API_NAMESPACE, API_NAMESPACE);
#endif

#ifndef TIZENIOT
	if(!g_bCameraWindowFail)
	{
		DestroyCameraWindow();
	}
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
* @function 		CameraPreviewCB
* @description	 	Callback function which is invoked when startpreview is called
* @parameter		camera_preview_data_s *frame : preview frame, void *user_data : user data to be passed
* @return 			NA
*/
static void CameraPreviewCB(camera_preview_data_s *frame, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached preview callback\\n", __LINE__, API_NAMESPACE);
#endif
	usleep(5000);
	g_bCallbackHit = true;
	if ( g_pCameraMainLoop )
	{
		g_main_loop_quit(g_pCameraMainLoop);
		g_main_loop_unref(g_pCameraMainLoop);
		g_pCameraMainLoop = NULL;
	}
	return;
}

/**
* @function 		CameraStateChangedCB
* @description	 	Callback function which is invoked when capture completed
* @parameter		void *user_data : user data to be passed
* @return 			NA
*/
void CameraStateChangedCB(camera_state_e previous, camera_state_e current, bool by_policy, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached camera state changed callback\\n", __LINE__, API_NAMESPACE);
#endif

	usleep(5000);
	g_bCallbackHit = true;
	if ( g_pCameraMainLoop )
	{
		g_main_loop_quit(g_pCameraMainLoop);
		g_main_loop_unref(g_pCameraMainLoop);
		g_pCameraMainLoop = NULL;
	}
	return;
}

/**
* @function 		CameraErrorCB
* @description	 	Callback function which is invoked when shutter sound is played
* @parameter		camera_error_e error : error occurred, camera_state_e current_state : state of camera, void *user_data: user data to be passed
* @return 			NA
*/
void CameraErrorCB(camera_error_e error, camera_state_e current_state, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached shutter sound callback\\n", __LINE__, API_NAMESPACE);
#endif

	usleep(5000);
	g_bCallbackHit = true;
	if ( g_pCameraMainLoop )
	{
		g_main_loop_quit(g_pCameraMainLoop);
		g_main_loop_unref(g_pCameraMainLoop);
		g_pCameraMainLoop = NULL;
	}
	return;
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
* @function 		CameraFocusChangedCB
* @description	 	Callback function which is invoked when focus changes
* @parameter		camera_error_e error : error occurred, camera_state_e current_state : state of camera, void *user_data: user data to be passed
* @return 			NA
*/
void CameraFocusChangedCB(camera_focus_state_e state, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached shutter sound callback\\n", __LINE__, API_NAMESPACE);
#endif

	usleep(5000);
	g_bCallbackHit = true;
	if ( g_pCameraMainLoop )
	{
		g_main_loop_quit(g_pCameraMainLoop);
		g_main_loop_unref(g_pCameraMainLoop);
		g_pCameraMainLoop = NULL;
	}
	return;
}

/**
* @function 		CameraInterruptedCB
* @description	 	Callback function which is invoked when camera is interrupted by policy
* @parameter		camera_error_e error : error occurred, camera_state_e current_state : state of camera, void *user_data: user data to be passed
* @return 			NA
*/
void CameraInterruptedCB(camera_policy_e policy, camera_state_e previous, camera_state_e current, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached shutter sound callback\\n", __LINE__, API_NAMESPACE);
#endif

	usleep(5000);
	g_bCallbackHit = true;
	if ( g_pCameraMainLoop )
	{
		g_main_loop_quit(g_pCameraMainLoop);
		g_main_loop_unref(g_pCameraMainLoop);
		g_pCameraMainLoop = NULL;
	}
	return;
}

/**
* @function 		CameraMediaPacketCB
* @description	 	Call to register for notification about delivering media packet when every preview frame is displayed
* @parameter		media_packet_h pkt : media packet occurred, void *user_data: user data to be passed
* @return 			NA
*/
void CameraMediaPacketCB(media_packet_h pkt, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached media packet callback\\n", __LINE__, API_NAMESPACE);
#endif

	usleep(5000);
	g_bCallbackHit = true;
	if ( g_pCameraMainLoop )
	{
		g_main_loop_quit(g_pCameraMainLoop);
		g_main_loop_unref(g_pCameraMainLoop);
		g_pCameraMainLoop = NULL;
	}
	return;
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

/** @addtogroup itc-camera-testcases
*  @brief 		Integration testcases for module camera
*  @ingroup 	itc-camera
*  @{
*/

//& purpose: Creates and destroys camera handle
//& type: auto
/**
* @testcase 			ITc_camera_create_destroy_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Create and Destroy the camera handle
* @scenario				Destroy created handle in startup\n
* 						Create camera handle\n
*						Destroy camera handle
* @apicovered			camera_create, camera_destroy
* @passcase				When camera_Create and camera_Destroy are successful
* @failcase				If target API camera_Create or camera_Destroy fails
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_create_destroy_p(void)
{
	START_TEST;

	camera_destroy(g_camera);
	g_camera = NULL;
	int nRet = camera_create(g_eCameraDev, &g_camera);
	PRINT_RESULT_CLEANUP(CAMERA_ERROR_NONE, nRet, "camera_create", CameraGetError(nRet), camera_create(g_eCameraDev, &g_camera););
	if( g_camera ==  NULL)
	{
		FPRINTF("[Line : %d][%s] camera handle g_camera is null \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	usleep(2000);

	nRet = camera_destroy(g_camera );
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_destroy", CameraGetError(nRet));
	g_camera = NULL;

	nRet = camera_create(g_eCameraDev, &g_camera);
	PRINT_RESULT_NORETURN(CAMERA_ERROR_NONE, nRet, "camera_create", CameraGetError(nRet));
	if( g_camera ==  NULL)
	{
		FPRINTF("[Line : %d][%s] camera handle g_camera is null \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Sets preview callback, check if state change is detected in callback.
//& type: auto
/**
* @testcase 			ITc_camera_start_stop_preview_set_unset_preview_cb_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Starts and stop Camera preview, and check if preview callback is invoked
* @scenario				Set preview callback\n
* 						Start preview\n
*						Stop preview\n
* 						unset preview format
* @apicovered			camera_set_preview_cb, camera_start_preview, camera_stop_preview, camera_unset_preview_cb
* @passcase				When camera_set_preview_cb, camera_start_preview, camera_stop_preview, camera_unset_preview_cb and preview callback is invoked.
* @failcase				If target API camera_start_preview or camera_stop_preview fails or any precondition API fails
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_start_stop_preview_set_unset_preview_cb_p(void)
{
	START_TEST;

	int nRet = -1;
	int nCameraTimeoutId = 0;
	g_bCallbackHit = false;

	nRet = camera_start_preview (g_camera);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_start_preview", CameraGetError(nRet));

	nRet = camera_set_preview_cb(g_camera, CameraPreviewCB, NULL);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_set_preview_cb");
	PRINT_RESULT_CLEANUP(CAMERA_ERROR_NONE, nRet, "camera_set_preview_cb", CameraGetError(nRet), camera_stop_preview(g_camera););

	RUN_POLLING_LOOP;

	if ( g_bCallbackHit == false )
	{
		camera_unset_preview_cb(g_camera);
		camera_stop_preview(g_camera);
		return 1;
	}

	nRet = camera_unset_preview_cb(g_camera);
	PRINT_RESULT_CLEANUP(CAMERA_ERROR_NONE, nRet, "camera_unset_preview_cb", CameraGetError(nRet), camera_stop_preview(g_camera););

	nRet = camera_stop_preview(g_camera);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_stop_preview", CameraGetError(nRet));

	return 0;
}

//& purpose: To check camera start capture.
//& type: auto
/**
* @testcase 			ITc_camera_start_capture_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Starts camera capture
* @scenario				Start preview\n
* 						Start capture\n
*						Stop preview
* @apicovered			camera_start_preview, camera_start_capture, camera_stop_preview
* @passcase				When camera_start_preview, camera_start_capture are successful and capturing callback and capturing completed callback are invoked.
* @failcase				If camera_start_preview, camera_start_capture fails or capturing callback and capturing completed callback are not invoked.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_start_capture_p(void)
{
	START_TEST;

	int nCameraTimeoutId = 0;
	g_bCameraCaptureStarted = false;
	g_bCameraCaptureStopped = false;

	int nRet = camera_start_preview (g_camera);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_start_preview");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_start_preview", CameraGetError(nRet));

	nRet = camera_start_capture(g_camera, &CameraCapturingCB, &CameraCapturingCompletedCB, NULL);
	PRINT_RESULT_CLEANUP(CAMERA_ERROR_NONE, nRet, "camera_start_capture", CameraGetError(nRet), camera_stop_preview(g_camera););
	RUN_POLLING_LOOP;

	//after captured, start_preview should be called.
	camera_start_preview (g_camera);
	camera_stop_preview(g_camera);

	if ( g_bCameraCaptureStarted == false || g_bCameraCaptureStopped == false )
	{
		FPRINTF("[Line : %d][%s] callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: To check camera start stop continuous capture.
//& type: auto
/**
* @testcase 			ITc_camera_start_stop_continuous_capture_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Starts and stops camera continuous capture
* @scenario				Start preview\n
* 						Start continuous capture\n
*						Stop continuous capture\n
*						Stop preview
* @apicovered			camera_start_preview, camera_start_continuous_capture, camera_stop_continuous_capture, camera_stop_preview
* @passcase				When camera_start_preview, camera_start_continuous_capture, camera_stop_continuous_capture are successful and capturing callback and capturing completed callback are invoked.
* @failcase				If camera_start_preview, camera_start_continuous_capture, camera_stop_continuous_capture fails or capturing callback and capturing completed callback are not invoked.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_start_stop_continuous_capture_p(void)
{
	START_TEST;

	int nCameraTimeoutId = 0;
	bool bRet = camera_is_supported_continuous_capture(g_camera);
	if ( g_bFeatureCamera == false )
	{
		if ( bRet == true )
		{
			FPRINTF("[Line : %d][%s] According to feature value from model_config, continuous capture should not be supported, but API says supported\\n", __LINE__, API_NAMESPACE);
			return 1;
		}

		FPRINTF("[Line : %d][%s] [Not supported] continuous capture not supported on the device\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	else
	{
		if ( bRet == false )
		{
			/** although tizen.org/feature/camera is true in model-config, specific feature continuous capture might not be supported*/
			FPRINTF("[Line : %d][%s] [Not supported] continuous capture not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	g_bCameraCaptureStarted = false;
	g_bCameraCaptureStopped = false;

	int nRet = camera_start_preview (g_camera);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_start_preview", CameraGetError(nRet));

	nRet = camera_start_continuous_capture(g_camera, IMAGECOUNT, IMAGE_INTERVAL, &CameraCapturingCB, &CameraCapturingCompletedCB, NULL);
	PRINT_RESULT_CLEANUP(CAMERA_ERROR_NONE, nRet, "camera_start_continuous_capture", CameraGetError(nRet), camera_stop_preview(g_camera););
	
	RUN_POLLING_LOOP;
	if ( g_bCameraCaptureStarted == false)
	{
		FPRINTF("[Line : %d][%s] callback not invoked\\n", __LINE__, API_NAMESPACE);
		camera_stop_preview(g_camera);
		return 1;
	}
	if ( !g_bCameraCaptureStopped )
	{
		nRet = camera_stop_continuous_capture(g_camera);
		PRINT_RESULT_CLEANUP(CAMERA_ERROR_NONE, nRet, "camera_stop_continuous_capture", CameraGetError(nRet), camera_start_preview (g_camera);camera_stop_preview(g_camera););
	}
	camera_start_preview (g_camera);
	camera_stop_preview(g_camera);


	return 0;
}

//& purpose: Gets camera state
//& type: auto
/**
* @testcase 			ITc_camera_get_state_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Gets camera state
* @scenario				get camera state
* @apicovered			camera_get_state
* @passcase				When camera_get_state passes
* @failcase				If target API camera_get_state fails
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_get_state_p(void)
{
	START_TEST;

	camera_state_e eGetState;
	int nRet = camera_get_state(g_camera, &eGetState);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_get_state");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_get_state", CameraGetError(nRet));

	if ( eGetState != CAMERA_STATE_CREATED )
	{
		FPRINTF("[Line : %d][%s] camera_get_state returned wrong state\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Check camera start and cancel focusing .
//& type: auto
/**
* @testcase 			ITc_camera_start_cancel_focusing_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Starts and cancels camera focusing
* @scenario				Start preview\n
* 						Start focusing\n
*						cancel focusing\n
*						cancel preview
* @apicovered			camera_start_preview, camera_start_focusing , camera_cancel_focusing
* @passcase				When camera_start_preview, camera_start_focusing , camera_cancel_focusing are successful and capturing callback and capturing completed callback are invoked.
* @failcase				If camera_start_preview, camera_start_focusing , camera_cancel_focusing fails or capturing callback and capturing completed callback are not invoked.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_start_cancel_focusing_p(void)
{
	START_TEST;

	camera_attr_af_mode_e eSetAFmode = CAMERA_ATTR_AF_NORMAL;
	g_bCallbackHit = false;

	int nRet = camera_attr_foreach_supported_af_mode(g_camera, CameraAttrSupportedAfModeCB, (void*)(&eSetAFmode));
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_attr_foreach_supported_af_mode");

	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] exposure not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s]camera_attr_foreach_supported_af_mode failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
		return 1;
	}
	else if ( g_bCallbackHit == false || eSetAFmode == CAMERA_ATTR_AF_NONE )
	{
		FPRINTF("[Line : %d][%s][Not Supported] It gives CAMERA_ATTR_AF_NONE , although camera_attr_foreach_supported_af_mode did not return NOT_SUPPORTED\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	nRet = camera_start_preview (g_camera);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_start_preview", CameraGetError(nRet));

	nRet = camera_start_focusing (g_camera, true);
	PRINT_RESULT_CLEANUP(CAMERA_ERROR_NONE, nRet, "camera_start_focusing", CameraGetError(nRet), camera_stop_preview(g_camera););

	nRet = camera_cancel_focusing(g_camera);
	PRINT_RESULT_CLEANUP(CAMERA_ERROR_NONE, nRet, "camera_cancel_focusing", CameraGetError(nRet), camera_stop_preview(g_camera););
	camera_stop_preview(g_camera);

	return 0;
}

//& purpose: Sets display.
//& type: auto
/**
* @testcase 			ITc_camera_set_display_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets zoom
* @scenario				Sets display
* @apicovered			camera_set_display
* @passcase				When camera_set_display is successful
* @failcase				If target API camera_set_display fails
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_set_display_p(void)
{
	START_TEST;

	camera_display_type_e eSetDispType = CAMERA_DISPLAY_TYPE_NONE;

	// Target API
	int nRet = camera_set_display (g_camera, eSetDispType,0);

	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_set_display");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_set_display", CameraGetError(nRet));

	return 0;
}

//& purpose: Set/Get supported preview resolution
//& type: auto
/**
* @testcase 			ITc_camera_set_get_preview_resolution_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get supported preview resolution
* @scenario				Get supported preview resolution\n
*						Set preview resolution\n
*						Get preview resolution
* @apicovered			camera_foreach_supported_preview_resolution, camera_set_preview_resolution, camera_get_preview_resolution
* @passcase				When camera_set_preview_resolution and camera_get_preview_resolution passes, and set/get values match.
* @failcase				If target API camera_set_preview_resolution and camera_get_preview_resolution fails or set/get values do not match.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_set_get_preview_resolution_p(void)
{
	START_TEST;

	int nGetWidth = 0, nGetHeight = 0;
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

	nRet = camera_set_preview_resolution(g_camera, stPreviewresolution.nWidth, stPreviewresolution.nHeight);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_set_preview_resolution", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_get_preview_resolution(g_camera, &nGetWidth, &nGetHeight);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_get_preview_resolution", CameraGetError(nRet));

	if ( (nGetWidth != stPreviewresolution.nWidth) || (nGetHeight != stPreviewresolution.nHeight) )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Gets recommended preview resolution
//& type: auto
/**
* @testcase 			ITc_camera_get_recommended_preview_resolution_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Gets recommended preview resolution
* @scenario				get recommended preview resolution
* @apicovered			camera_get_recommended_preview_resolution
* @passcase				When camera_get_recommended_preview_resolution passes
* @failcase				If target API camera_get_recommended_preview_resolution fails
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_get_recommended_preview_resolution_p(void)
{
	START_TEST;

	int nGetWidth = 0, nGetHeight = 0;
	int nRet = camera_get_recommended_preview_resolution(g_camera, &nGetWidth, &nGetHeight);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_get_recommended_preview_resolution");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_get_recommended_preview_resolution", CameraGetError(nRet));

	FPRINTF("[Line : %d][%s] recommended preview resolution : width = %d, height = %d\\n", __LINE__, API_NAMESPACE, nGetWidth, nGetHeight);
	return 0;
}

//& purpose: Set/Get supported capture resolution
//& type: auto
/**
* @testcase 			ITc_camera_set_get_capture_resolution_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get supported capture resolution
* @scenario				Get supported capture resolution\n
*						Set capture resolution\n
*						Get capture resolution
* @apicovered			camera_foreach_supported_capture_resolution, camera_set_capture_resolution, camera_get_capture_resolution
* @passcase				When camera_set_capture_resolution and camera_get_capture_resolution passes, and set/get values match.
* @failcase				If target API camera_set_capture_resolution and camera_get_capture_resolution fails or set/get values do not match.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_set_get_capture_resolution_p(void)
{
	START_TEST;

	g_bCallbackHit = false;
	int nGetWidth = 0, nGetHeight = 0;
	CameraResolution stCaptureResolution = {0};

	int nRet = camera_foreach_supported_capture_resolution(g_camera, CameraAttrSupportedCaptureResolutionCB, (void *)(&stCaptureResolution));
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_foreach_supported_capture_resolution");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_foreach_supported_capture_resolution", CameraGetError(nRet));

	if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s]Unable to call callback function\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( (stCaptureResolution.nWidth != g_nCapResWidth) || (stCaptureResolution.nHeight != g_nCapResHeight) )
	{
		FPRINTF("[Line : %d][%s] stCaptureResolution values are not properly passed from CB funtion. \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = camera_set_capture_resolution(g_camera, stCaptureResolution.nWidth, stCaptureResolution.nHeight);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_set_capture_resolution", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_get_capture_resolution(g_camera, &nGetWidth, &nGetHeight);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_get_capture_resolution", CameraGetError(nRet));
	if ( (nGetWidth != stCaptureResolution.nWidth) || (nGetHeight != stCaptureResolution.nHeight) )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Sets and gets capture format.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_get_capture_format_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets capture format
* @scenario				Set capture format\n
* 						Get capture format
* @apicovered			camera_set_capture_format, camera_get_capture_format
* @passcase				When camera_set_capture_format and camera_get_capture_format are successful and set/get values are matched.
* @failcase				If target API camera_set_capture_format or camera_get_capture_format fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_get_capture_format_p(void)
{
	START_TEST;

	camera_pixel_format_e eSetVal;// = CAMERA_PIXEL_FORMAT_NV12;
	camera_pixel_format_e eGetVal;

	g_bCallbackHit = false;
	int nRet = camera_foreach_supported_capture_format(g_camera, CameraAttrSupportedCaptureFormatCB, (void*)(&eSetVal));
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_foreach_supported_capture_format");

	if ( nRet != CAMERA_ERROR_NONE )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] capture format supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s]camera_foreach_supported_capture_format failed, error returned = %s\\n", __LINE__, API_NAMESPACE, CameraGetError(nRet));
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

	nRet = camera_set_capture_format(g_camera, eSetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_set_capture_format", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_get_capture_format(g_camera, &eGetVal);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_get_capture_format", CameraGetError(nRet));

	if ( eSetVal != eGetVal )
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Set/Get supported preview format.
//& type: auto
/**
* @testcase 			ITc_camera_set_get_preview_format_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get supported preview format
* @scenario				Get supported preview format\n
*						Set preview format\n
*						Get preview format
* @apicovered			camera_foreach_supported_preview_format, camera_set_preview_format, camera_get_preview_format
* @passcase				When camera_set_preview_format and camera_get_preview_format passes, and set/get values match.
* @failcase				If target API camera_set_preview_format and camera_get_preview_format fails or set/get values do not match.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_set_get_preview_format_p(void)
{
	START_TEST;

	camera_pixel_format_e eGetFormat, eSetFormat;
	int nCameraTimeoutId = 0;

	g_bCallbackHit = false;
	int nRet = camera_foreach_supported_preview_format(g_camera, CameraAttrSupportedPreviewFormatCB, (void *)(&eSetFormat));
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_foreach_supported_preview_format");
	RUN_POLLING_LOOP;

	if ( nRet != CAMERA_ERROR_NONE || g_bCallbackHit == false )
	{
		if ( nRet == CAMERA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s][NOT SUPPORTED] preview format not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		FPRINTF("[Line : %d][%s] failed to get supported format\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	else if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s]callback did not invoke\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( eSetFormat != g_eCamPixFmt )
	{
		FPRINTF("[Line : %d][%s] eSetFormat is not properly passed from CB funtion. \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = camera_set_preview_format(g_camera, eSetFormat);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_set_preview_format", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_get_preview_format(g_camera, &eGetFormat);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_get_preview_format", CameraGetError(nRet));

	if (eGetFormat != eSetFormat)
	{
		FPRINTF("[Line : %d][%s] Set/Get values mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Sets and unset media packet cb.
//& type: auto
/**
* @testcase 			ITc_camera_set_unset_media_packet_preview_cb_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and unset media packet cb
* @scenario				Set media packet cb\n
* 						Get media packet cb
* @apicovered			camera_is_supported_media_packet_preview_cb, camera_set_media_packet_preview_cb, camera_start_preview, camera_stop_preview,camera_unset_media_packet_preview_cb
* @passcase				When camera_set_media_packet_preview_cb, camera_start_preview, camera_stop_preview and camera_unset_media_packet_preview_cb are successful
* @failcase				If target API camera_set_media_packet_preview_cb or camera_unset_media_packet_preview_cb fails
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_set_unset_media_packet_preview_cb_p(void)
{
	START_TEST;

	int nCameraTimeoutId = 0;
	bool bRet = camera_is_supported_media_packet_preview_cb(g_camera );
	if ( g_bFeatureCamera == false )
	{
		if ( bRet == true )
		{
			FPRINTF("[Line : %d][%s] According to feature value from model_config, media packet preview should not be supported, but API says supported\\n", __LINE__, API_NAMESPACE);
			return 1;
		}

		FPRINTF("[Line : %d][%s] [Not supported] media packet preview not supported on the device\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	else
	{
		if ( bRet == false )
		{
			FPRINTF("[Line : %d][%s] [Not supported] media packet preview not supported on the device\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}

	g_bCallbackHit = false;
	int nRet = camera_set_media_packet_preview_cb(g_camera, CameraMediaPacketCB, NULL);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_set_media_packet_preview_cb", CameraGetError(nRet));

	nRet = camera_start_preview (g_camera);
	PRINT_RESULT_CLEANUP(CAMERA_ERROR_NONE, nRet, "camera_start_preview", CameraGetError(nRet), camera_unset_media_packet_preview_cb(g_camera););
	RUN_POLLING_LOOP;

	if ( g_bCallbackHit == false )
	{
		camera_unset_media_packet_preview_cb(g_camera);
		return 1;
	}

	nRet = camera_stop_preview(g_camera);
	PRINT_RESULT_CLEANUP(CAMERA_ERROR_NONE, nRet, "camera_stop_preview", CameraGetError(nRet), camera_unset_media_packet_preview_cb(g_camera););

	nRet = camera_unset_media_packet_preview_cb(g_camera);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_unset_media_packet_preview_cb", CameraGetError(nRet));

	return 0;
}

//& purpose: Sets state change callback, check if state change is detected in callback.
//& type: auto
/**
* @testcase 			ITc_camera_set_unset_state_change_cb_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and unsets state changes callback.
* @scenario				Set state change callback\n
* 						Start preview\n
*						Stop preview\n
* 						unset state change callback
* @apicovered			camera_set_state_changed_cb, camera_start_preview, camera_stop_preview, camera_unset_state_changed_cb
* @passcase				When camera_set_state_changed_cb, camera_unset_state_changed_cb succeeds and callback is hit on state change
* @failcase				If camera_set_state_changed_cb, camera_unset_state_changed_cb fails or callback is not hit on state change
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_set_unset_state_change_cb_p(void)
{
	START_TEST;

	int nCameraTimeoutId = 0;
	int nRet = camera_set_state_changed_cb(g_camera, CameraStateChangedCB, NULL);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_set_state_changed_cb");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_set_state_changed_cb", CameraGetError(nRet));

	camera_start_preview (g_camera);
	usleep(5000);
	camera_stop_preview(g_camera);

	RUN_POLLING_LOOP;
	if ( g_bCallbackHit == false )
	{
		return 1;
	}
	nRet = camera_unset_state_changed_cb(g_camera);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_unset_state_changed_cb", CameraGetError(nRet));

	return 0;
}

//& purpose: Sets and unsets interrupt cb.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_unset_interrupted_cb_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and unsets interrupt cb
* @scenario				Set interrupt cb\n
* 						Get interrupt cb
* @apicovered			camera_set_interrupted_cb, camera_unset_interrupted_cb
* @passcase				When camera_set_interrupted_cb and camera_unset_interrupted_cb are successful
* @failcase				If target API camera_set_interrupted_cb or camera_unset_interrupted_cb fails
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_unset_interrupted_cb_p(void)
{
	START_TEST;

	int nRet = camera_set_interrupted_cb(g_camera, CameraInterruptedCB, NULL);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_set_interrupted_cb");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_set_interrupted_cb", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_unset_interrupted_cb(g_camera);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_unset_interrupted_cb", CameraGetError(nRet));

	return 0;
}

//& purpose: Sets and unsets focus changed cb.
//& type: auto
/**
* @testcase 			ITc_camera_set_unset_focus_changed_cb_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and unsets focus changed cb
* @scenario				Set focus changed cb\n
* 						Get focus changed cb\n
* @apicovered			camera_set_focus_changed_cb, camera_unset_focus_changed_cb
* @passcase				When camera_set_focus_changed_cb and camera_unset_focus_changed_cb are successful
* @failcase				If target API camera_set_focus_changed_cb or camera_unset_focus_changed_cb fails
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_set_unset_focus_changed_cb_p(void)
{
	START_TEST;

	int nRet = camera_set_focus_changed_cb(g_camera, CameraFocusChangedCB, NULL);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_set_focus_changed_cb");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_set_focus_changed_cb", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_unset_focus_changed_cb(g_camera);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_unset_focus_changed_cb", CameraGetError(nRet));

	return 0;
}

//& purpose: Sets and unsets error cb.
//& type: auto
/**
* @testcase 			ITc_camera_attr_set_unset_error_cb_p
* @since_tizen 			2.3
* @author				SRID(m.khalid)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and unsets error cb
* @scenario				Set error cb\n
* 						Get error cb
* @apicovered			camera_set_error_cb, camera_unset_error_cb
* @passcase				When camera_set_error_cb and camera_unset_error_cb are successful and set/get values are matched.
* @failcase				If target API camera_set_error_cb or camera_unset_error_cb fails or set/get values are unmatched.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_attr_set_unset_error_cb_p(void)
{
	START_TEST;

	int nRet = camera_set_error_cb(g_camera, CameraErrorCB, NULL);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_set_error_cb");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_set_error_cb", CameraGetError(nRet));
	usleep(2000);

	nRet = camera_unset_error_cb(g_camera);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_unset_error_cb", CameraGetError(nRet));

	return 0;
}

//& purpose: Get Facing Direction
//& type: auto
/**
* @testcase 			ITc_camera_get_facing_direction_p
* @since_tizen 			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			get facing direction
* @scenario				Get Facing Direction
* @apicovered			camera_get_facing_direction
* @passcase				When camera_get_facing_direction passess.
* @failcase				If target API camera_get_facing_direction fails.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_get_facing_direction_p(void)
{
	START_TEST;
	
	camera_facing_direction_e eGetFacingDir;

	int nRet = camera_get_facing_direction(g_camera, &eGetFacingDir);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_get_state");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_get_facing_direction", CameraGetError(nRet));
	if((eGetFacingDir == CAMERA_FACING_DIRECTION_REAR) || (eGetFacingDir == CAMERA_FACING_DIRECTION_FRONT))
	{
		FPRINTF("[Line : %d][%s] eGetFacingDir value is correct\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] eGetFacingDir value is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}
//& purpose: Get flash state
//& type: auto
/**
* @testcase 			ITc_camera_get_flash_state_p
* @since_tizen 			3.0
* @author				SRID(manu.tiwari)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			Get flash state
* @scenario				Get flash state
* @apicovered			camera_get_flash_state
* @passcase				When camera_get_flash_state passes with valid flash state.
* @failcase				If target API camera_get_flash_state fails or flash state is not valid.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_get_flash_state_p(void)
{
	START_TEST;
	
	bool l_bFeatureSupported = false;
	camera_flash_state_e eGetFlashState;
    
	l_bFeatureSupported = g_bFeatureCamera && (g_bFeatureCameraBackFlash || g_bFeatureCameraFrontFlash);
	
	int nRet = camera_get_flash_state(g_eCameraDev, &eGetFlashState);
	CHECK_UNSUPPORTED_ERROR_RETURN(l_bFeatureSupported, "camera_get_flash_state");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_get_flash_state", CameraGetError(nRet));
	if((eGetFlashState == CAMERA_FLASH_STATE_NOT_USED) || (eGetFlashState == CAMERA_FLASH_STATE_USED))
	{
		FPRINTF("[Line : %d][%s] eGetFlashState value is correct\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] eGetFlashState value is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Changes the camera device
//& type: auto
/**
* @testcase 			ITc_camera_change_device_p
* @since_tizen 			3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Changes the camera device
* @scenario				1. Check camera device which is supported or not. \n
*                       2. Change camera device
* @apicovered			camera_change_device
* @passcase				When camera_change_device passes with valid flash state.
* @failcase				If target API camera_change_device fails or flash state is not valid.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_change_device_p(void)
{
	START_TEST;	

	int device_count = 0;

	int nRet = camera_get_device_count(g_camera, &device_count);	
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_get_device_count", CameraGetError(nRet));
	if (device_count < 2) {
		FPRINTF("[Line : %d][%s] Not support secondary CAMERA \\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	
	nRet = camera_change_device(g_camera, CAMERA_DEVICE_CAMERA1);	
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_change_device");
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_change_device", CameraGetError(nRet));
		
	return 0;
}

#ifndef TIZENIOT
//& purpose: To check display reuse hint with valid pointer and value in parameters.
//& type: auto
/**
* @testcase 			ITc_camera_set_get_display_reuse_hint_p
* @since_tizen 			3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			To set and get display reuse hint 
* @scenario				To set and get display reuse hint 
* @apicovered			camera_set_display_reuse_hint camera_get_display_reuse_hint
* @passcase				To check display reuse hint with valid pointer and value in parameters.
* @failcase				If target API camera_set_display_reuse_hint camera_get_display_reuse_hint fails or flash state is not valid.
* @precondition			Camera handle must be created
* @postcondition		Camera handle must be released
*/
int ITc_camera_set_get_display_reuse_hint_p(void)
{
	START_TEST;
		
	bool bHint = true;
    bool bGetHint = false;
	g_bCameraWindowFail = false;
	
	CreateCameraWindow();

	if(g_bCameraWindowFail)
	{
		FPRINTF("[Line : %d][%s] camera creation window fails\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nRet = camera_set_display(g_camera, CAMERA_DISPLAY_TYPE_OVERLAY, GET_DISPLAY(camera_win));	
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_set_display", CameraGetError(nRet));
	
	nRet = camera_start_preview(g_camera);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_start_preview", CameraGetError(nRet));
	
	nRet = camera_set_display_reuse_hint(g_camera, bHint);
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureCamera, "camera_set_display_reuse_hint");
	PRINT_RESULT_CLEANUP(CAMERA_ERROR_NONE, nRet, "camera_set_display_reuse_hint", CameraGetError(nRet),camera_stop_preview(g_camera));
	
	nRet = camera_get_display_reuse_hint(g_camera, &bGetHint);
	PRINT_RESULT_CLEANUP(CAMERA_ERROR_NONE, nRet, "camera_get_display_reuse_hint", CameraGetError(nRet),camera_stop_preview(g_camera));
		
	if(bGetHint != bHint)
	{
		FPRINTF("[Line : %d][%s] bGetHint value is invalid\\n", __LINE__, API_NAMESPACE);	
		camera_stop_preview(g_camera);		
		return 1;
	}
	
	nRet = camera_stop_preview(g_camera);
	PRINT_RESULT_NORETURN(CAMERA_ERROR_NONE, nRet, "camera_stop_preview", CameraGetError(nRet));
		
	return 0;
}
#endif
/** @} */
/** @} */

