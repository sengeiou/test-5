#include <device/battery.h>
#include <device/callback.h>
#include <device/display.h>
#include <device/haptic.h>
#include <device/led.h>
#include <device/power.h>
#include "CTs-platform-permission-common.h"

#define DISPLAY_FEATURE				"http://tizen.org/feature/camera.back.flash"
#define LED_FEATURE				"http://tizen.org/feature/led"
#define IR_FEATURE				"http://tizen.org/feature/consumer_ir"
#define BATTERY_FEATURE				"http://tizen.org/feature/battery"
#define DISPLAY_FEATURE_MAIN			"http://tizen.org/feature/display"
#define DISPLAY_STATE_FEATURE			"http://tizen.org/feature/display.state"

/**
* @function 		CTs_platform_permission_device_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_device_startup(void)
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
* @function 		CTs_platform_permission_device_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_device_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
/**
* @function 		DeviceGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* DeviceGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case DEVICE_ERROR_NONE:						szErrorVal = "DEVICE_ERROR_NONE";					break;
	case DEVICE_ERROR_OPERATION_FAILED:			szErrorVal = "DEVICE_ERROR_OPERATION_FAILED";		break;
	case DEVICE_ERROR_PERMISSION_DENIED:		szErrorVal = "DEVICE_ERROR_PERMISSION_DENIED";		break;
	case DEVICE_ERROR_INVALID_PARAMETER:		szErrorVal = "DEVICE_ERROR_INVALID_PARAMETER";		break;
	case DEVICE_ERROR_ALREADY_IN_PROGRESS:		szErrorVal = "DEVICE_ERROR_ALREADY_IN_PROGRESS";	break;
	case DEVICE_ERROR_NOT_SUPPORTED:			szErrorVal = "DEVICE_ERROR_NOT_SUPPORTED";			break;
	case DEVICE_ERROR_NOT_INITIALIZED:			szErrorVal = "DEVICE_ERROR_NOT_INITIALIZED";		break;
	default:									szErrorVal = "Unknown Error";						break;
	}

	return szErrorVal;
}
//& purpose: Checking tizen.org/privilege/display privilege
//& type: auto
/**
* @testcase			CTc_Device_PrivilegeDisplay_get_numbers
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Gets the number of display devices
* @apicovered		device_display_get_numbers
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Device_PrivilegeDisplay_get_numbers(void)
{
	START_TEST;

	int nDevice = 0;
	int nRet = device_display_get_numbers(&nDevice);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "device_display_get_numbers", DeviceGetError(nRet));
	return 0;
}

//& purpose: Checking tizen.org/privilege/power privilege
//& type: auto
/**
* @testcase			CTc_Device_PrivilegePower_wakeup
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Changes the current power state to the normal/dim state
* @apicovered		device_power_wakeup
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Device_PrivilegePower_wakeup(void)
{
	START_TEST;
	bool flag = true;
	bool bIsDisplayStateFeatureSupported = false;
	int nRet = device_power_wakeup(flag);

	IS_FEATURE_SUPPORTED(DISPLAY_STATE_FEATURE, bIsDisplayStateFeatureSupported, API_NAMESPACE);
	if (false == bIsDisplayStateFeatureSupported)
	{
		assert_eq(nRet, DEVICE_ERROR_NOT_SUPPORTED);
		return 0;
	}
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "device_power_wakeup", DeviceGetError(nRet));
	return 0;
}


//& purpose: Checking tizen.org/privilege/display privilege
//& type: auto
/**
* @testcase 		CTc_Device_PrivilegeDisplay_state_change
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description		To change and get the display state
* @scenario			Change the display state\n
*					Get the display state
* @apicovered		device_display_change_state, device_display_get_state
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Device_PrivilegeDisplay_state_change(void)
{
	START_TEST;

	bool bIsDisplayStateFeatureSupported = false;
	int nRet = device_display_change_state(DISPLAY_STATE_NORMAL);

	IS_FEATURE_SUPPORTED(DISPLAY_STATE_FEATURE, bIsDisplayStateFeatureSupported, API_NAMESPACE);
	if (false == bIsDisplayStateFeatureSupported)
	{
		assert_eq(nRet, DEVICE_ERROR_NOT_SUPPORTED);
		return 0;
	}
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "device_display_change_state", DeviceGetError(nRet));

	return 0;
}
//& purpose: Checking tizen.org/privilege/display privilege
//& type: auto
/**
* @testcase 		CTc_Device_PrivilegeDisplay_get_max_brightness
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description		To  get  maximum the display brigtness
* @scenario			device_display_get_max_brightness\n
* @apicovered		device_display_get_max_brightness
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Device_PrivilegeDisplay_get_max_brightness(void)
{
	START_TEST;
	int nDisplayIndex = 0;
	int nMaximumBrightness = 0;
	
	int nRet = device_display_get_max_brightness(nDisplayIndex, &nMaximumBrightness);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "device_display_get_max_brightness", DeviceGetError(nRet));
	
	return 0;
}

//& purpose: Checking tizen.org/privilege/display privilege
//& type: auto
/**
* @testcase 		CTc_Device_PrivilegeDisplay_get_brightness
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description		To change and get the display state
* @scenario			device_display_get_brightness\n
* @apicovered		device_display_get_brightness
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Device_PrivilegeDisplay_get_brightness(void)
{
	START_TEST;
	int nDisplayIndex = 0;
	int nGetBrigntness = 0;

	// Target API
	int nRet = device_display_get_brightness(nDisplayIndex, &nGetBrigntness);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "device_display_get_brightness", DeviceGetError(nRet));
	
	return 0;
}


//& purpose: To get the max brightnrss
//& type: auto
/**
* @testcase 		CTc_Device_PrivilegeFlash_get_max_brightness
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description		To get the max brightness
* @scenario			device_flash_get_max_brightness\n
* @apicovered		device_flash_get_max_brightness
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Device_PrivilegeFlash_get_max_brightness(void)
{
	START_TEST;
	int nMaximumBrightness = 0;
	bool bIsDisplayFeatureSupported = false;
	bool bIsBackFlashFeatureSupported = false;
	IS_FEATURE_SUPPORTED(DISPLAY_FEATURE, bIsBackFlashFeatureSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(LED_FEATURE, bIsDisplayFeatureSupported, API_NAMESPACE);
	if ( ( false == bIsDisplayFeatureSupported ) || ( bIsBackFlashFeatureSupported == false) )
		{
			FPRINTF("[Line : %d][%s] Feature is not supported\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	int nRet = device_flash_get_max_brightness(&nMaximumBrightness);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "device_flash_get_max_brightness", DeviceGetError(nRet));
	return 0;
}

//& purpose: To get the  brightness
//& type: autof
/**
* @testcase 		CTc_Device_PrivilegeFlash_set_brightness
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description		To  get the brightness
* @scenario			device_flash_set_brightness\n
* @apicovered		device_flash_get_brightness
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Device_PrivilegeFlash_set_brightness(void)
{
	START_TEST;

	int nSetBrightness = 0;
	bool bIsDisplayFeatureSupported = false;
	bool bIsBackFlashFeatureSupported = false;
	IS_FEATURE_SUPPORTED(DISPLAY_FEATURE, bIsBackFlashFeatureSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(LED_FEATURE, bIsDisplayFeatureSupported, API_NAMESPACE);
	if ( ( false == bIsDisplayFeatureSupported ) || ( bIsBackFlashFeatureSupported == false) )
		{
			FPRINTF("[Line : %d][%s] Feature is not supported\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	// Target API
	int nRet = device_flash_set_brightness(nSetBrightness);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "device_flash_set_brightness", DeviceGetError(nRet));
	
	return 0;
}
//& purpose: To get the  brightness
//& type: auto
/**
* @testcase 		CTc_Device_PrivilegeFlash_get_brightness
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description		To  get the brightness
* @scenario			device_flash_set_brightness\n
* @apicovered		device_flash_get_brightness
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Device_PrivilegeFlash_get_brightness(void)
{
	START_TEST;
	int nGetBrightness =0;
	bool bIsDisplayFeatureSupported = false;
	bool bIsBackFlashFeatureSupported = false;
	IS_FEATURE_SUPPORTED(DISPLAY_FEATURE, bIsBackFlashFeatureSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(LED_FEATURE, bIsDisplayFeatureSupported, API_NAMESPACE);
	if ( ( false == bIsDisplayFeatureSupported ) || ( bIsBackFlashFeatureSupported == false) )
		{
			FPRINTF("[Line : %d][%s] Feature is not supported\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	
	int nRet = device_flash_get_brightness(&nGetBrightness);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "device_flash_set_brightness", DeviceGetError(nRet));

	return 0;
}
//& purpose: To get the haptic count
//& type: auto
/**
* @testcase 		CTc_Device_PrivilegeHaptic_open
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description		To open the haptic count
* @scenario			device_haptic_open\n
* @apicovered		device_haptic_open
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Device_PrivilegeHaptic_open(void)
{
	START_TEST;
	int nDeviceIndex  =0;
	bool bIsBatteryFeatureSupported = false;
	haptic_device_h hHapticDevice;
	IS_FEATURE_SUPPORTED(BATTERY_FEATURE, bIsBatteryFeatureSupported, API_NAMESPACE);

	if (!bIsBatteryFeatureSupported)
	{
		FPRINTF("[Line : %d][%s] Feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	int nRet = device_haptic_open(nDeviceIndex, &hHapticDevice);
	if(nRet == DEVICE_ERROR_NONE)
	device_haptic_close(hHapticDevice);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "device_haptic_open", DeviceGetError(nRet));

	return 0;
}

//& purpose: To play and stop led custom
//& type: auto
/**
* @testcase 		CTc_Device_PrivilegeLed_play_stop
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description		To play and stop led custom
* @scenario			device_led_play_custom\n
* @apicovered		device_led_play_custom
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Device_PrivilegeLed_play_stop(void)
{
	START_TEST;
	int nRet = 0;
	int on = 1000;						//Turn on time in milliseconds
	int off = 1000;						//Turn off time in milliseconds
	unsigned int color = 0xFF101010;	//Color value
	
   bool bIsDisplayFeatureSupported = false;
	bool bIsBackFlashFeatureSupported = false;
	IS_FEATURE_SUPPORTED(DISPLAY_FEATURE, bIsBackFlashFeatureSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(LED_FEATURE, bIsDisplayFeatureSupported, API_NAMESPACE);
	if ( ( false == bIsDisplayFeatureSupported ) || ( bIsBackFlashFeatureSupported == false) )
		{
			FPRINTF("[Line : %d][%s] Feature is not supported\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	nRet = device_led_play_custom(on, off, color, LED_CUSTOM_DEFAULT);
	if(nRet == DEVICE_ERROR_NONE)
	device_led_stop_custom();
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "device_haptic_get_count", DeviceGetError(nRet),device_led_stop_custom(),DEVICE_ERROR_NONE);

	return 0;
}

//& purpose: To power request
//& type: auto
/**
* @testcase 		CTc_Device_PrivilegePower_request
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description		To request and release power
* @scenario			device_power_request_lock\n
* @apicovered		device_power_request_lock
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Device_PrivilegePower_request_release(void)
{
	START_TEST;
	static bool bIsDisplayFeatureSupported;
	static bool bIsDisplayStateFeatureSupported;

	IS_FEATURE_SUPPORTED(DISPLAY_FEATURE_MAIN, bIsDisplayFeatureSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(DISPLAY_STATE_FEATURE, bIsDisplayStateFeatureSupported, API_NAMESPACE);

	if ((bIsDisplayFeatureSupported == false) || (bIsDisplayStateFeatureSupported == false))
	{
		FPRINTF("[Line : %d][%s] Feature is not supported\\n", __LINE__, API_NAMESPACE);
			return 0;
	}

	int nRet = device_power_request_lock(POWER_LOCK_DISPLAY, 10);
	if(nRet == DEVICE_ERROR_NONE)
		device_power_release_lock(POWER_LOCK_DISPLAY);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "device_power_release_lock", DeviceGetError(nRet));

	return 0;
}

#ifdef MOBILE	//Starts MOBILE
//& purpose: To power request
//& type: auto
/**
* @testcase 		CTc_Device_Privilege_ir_is_available
* @since_tizen		3.0
* @author			SRID(arvin.mittal)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description		Gets the information whether IR module is available
* @scenario			Feature check and then get information for availability of IR module
* @apicovered		device_ir_is_available
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Device_Privilege_ir_is_available(void)
{
	START_TEST;
	int nRet;	
	bool val;
	bool bIsIRFeatureSupported = false;
	
	IS_FEATURE_SUPPORTED(IR_FEATURE, bIsIRFeatureSupported, API_NAMESPACE);
	if ( false == bIsIRFeatureSupported )
	{
		FPRINTF("[Line : %d][%s] Feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	nRet = device_ir_is_available(&val);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "device_ir_is_available", DeviceGetError(nRet));

	return 0;
}

//& purpose: To power request
//& type: auto
/**
* @testcase 		CTc_Device_Privilege_ir_transmit
* @since_tizen		3.0
* @author			SRID(arvin.mittal)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description		Transmits IR command
* @scenario			Feature check and then transmits IR command
* @apicovered		device_ir_transmit
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Device_Privilege_ir_transmit(void)
{
	START_TEST;
	int nRet;
	int pattern[5] = {100, 200, 300, 400, 500};

	bool bIsIRFeatureSupported = false;
	
	IS_FEATURE_SUPPORTED(IR_FEATURE, bIsIRFeatureSupported, API_NAMESPACE);
	if ( false == bIsIRFeatureSupported )
	{
		FPRINTF("[Line : %d][%s] Feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	nRet = device_ir_transmit(38000, pattern, 5);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "device_ir_transmit", DeviceGetError(nRet));

	return 0;
}
#endif  //End MOBILE

