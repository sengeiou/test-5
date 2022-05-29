#include "CTs-platform-permission-common.h"

/**
* @function         CTs_platform_permission_camera_startup
* @description         Called before each test
* @parameter        NA
* @return             NA
*/
void CTs_platform_permission_camera_startup(void)
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
    FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function         CTs_platform_permission_camera_cleanup
* @description         Called after each test
* @parameter        NA
* @return             NA
*/
void CTs_platform_permission_camera_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
    return;
}

//& purpose: Checking tizen.org/privilege/camera privilege
//& type: auto
/**
* @testcase			CTc_Camera_Privilege_Camera
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type				auto
* @scenario			Creates a new camera handle for controlling a camera\n
* 					Destroy camera handle
* @apicovered		camera_create and camera_destroy
* @passcase			If target privileged Apis return TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged Apis do not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Camera_Privilege_Camera(void)
{
	START_TEST;
	g_hCamera = NULL;
	int nRet = -1;
	
	IS_FEATURE_SUPPORTED(FEATURE_CAMERA_BACK, g_bIsSupported, API_NAMESPACE);
	if (!g_bIsSupported)
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_CAMERA_BACK);
		return 0;
	}
	
	g_bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_CAMERA_FRONT, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_CAMERA_FRONT);
		return 0;
	}
	
	g_bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_AUDIO_CAMERA, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
    {
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_AUDIO_CAMERA);
		return 0;
    }
	
	g_bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_CAMERA_BACK_FLASH, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_CAMERA_BACK_FLASH);
		return 0;
	}
	
	g_bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_CAMERA_FRONT_FLASH, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
    {
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_CAMERA_FRONT_FLASH);
		return 0;
    }
	
	nRet = camera_create(CAMERA_DEVICE_CAMERA0, &g_hCamera);
	PRINT_RESULT(CAMERA_ERROR_NONE, nRet, "camera_create", CameraPrintErrorMsg(nRet));
	
	//Target API
	nRet = camera_start_preview(g_hCamera);
	if ( nRet != TIZEN_ERROR_PERMISSION_DENIED)
    {
		FPRINTF("[Line : %d][%s] camera_start_preview failed. Error returned = %s: \\n", __LINE__, API_NAMESPACE, CameraPrintErrorMsg(nRet));
		camera_stop_preview(g_hCamera);
		camera_destroy(g_hCamera);
		return 1;
	}
	
	camera_stop_preview(g_hCamera);
	camera_destroy(g_hCamera);
	return 0;
}