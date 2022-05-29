#include "CTs-platform-permission-common.h"
#include <sensor.h>
#define PATH_LEN					1024

typedef enum FeatureCheck {
	FEATURE_SUPPORTED = 0,
	FEATURE_UNSUPPORTED,
	FEATURE_MISMATCH
} feature_check_e;
sensor_h g_pstSensorHandle;
typedef struct Sensor
{
	sensor_type_e eSensorType;
	char szFeature[PATH_LEN];
} SensorFeature;
SensorFeature stSensor[] = {	
	{SENSOR_HRM, "http://tizen.org/feature/sensor.heart_rate_monitor"},
	{SENSOR_HRM_LED_GREEN, "http://tizen.org/feature/sensor.heart_rate_monitor.led_green"},
	{SENSOR_HRM_LED_IR, "http://tizen.org/feature/sensor.heart_rate_monitor.led_ir"},
	{SENSOR_HRM_LED_RED, "http://tizen.org/feature/sensor.heart_rate_monitor.led_red"}
	
};

int enum_size = sizeof(stSensor) / sizeof(stSensor[0]);
int enum_counter = 0;
/**
* @function 		CTs_platform_permission_sensor_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_sensor_startup(void)
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
* @function 		CTs_platform_permission_sensor_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_sensor_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
/**
* @function 		SensorGetType
* @description	 	Maps sensor type enums
* @parameter		nSensorType : sensor type
* @return 			sensor type string
*/
char* SensorGetType(sensor_type_e nSensorType)
{
	char *szErrorVal = "Unknown Error";
	switch ( nSensorType )
	{
	case SENSOR_ACCELEROMETER: 					szErrorVal = "SENSOR_ACCELEROMETER";					break;
	case SENSOR_GRAVITY: 						szErrorVal = "SENSOR_GRAVITY";							break;
	case SENSOR_LINEAR_ACCELERATION: 			szErrorVal = "SENSOR_LINEAR_ACCELERATION";				break;
	case SENSOR_MAGNETIC: 						szErrorVal = "SENSOR_MAGNETIC";							break;
	case SENSOR_ROTATION_VECTOR: 				szErrorVal = "SENSOR_ROTATION_VECTOR";					break;
	case SENSOR_ORIENTATION: 					szErrorVal = "SENSOR_ORIENTATION";						break;
	case SENSOR_GYROSCOPE: 						szErrorVal = "SENSOR_GYROSCOPE";						break;
	case SENSOR_LIGHT: 							szErrorVal = "SENSOR_LIGHT";							break;
	case SENSOR_PROXIMITY: 						szErrorVal = "SENSOR_PROXIMITY";						break;
	case SENSOR_PRESSURE: 						szErrorVal = "SENSOR_PRESSURE";							break;
	case SENSOR_ULTRAVIOLET: 					szErrorVal = "SENSOR_ULTRAVIOLET";						break;
	case SENSOR_TEMPERATURE: 					szErrorVal = "SENSOR_TEMPERATURE";						break;
	case SENSOR_HUMIDITY: 						szErrorVal = "SENSOR_HUMIDITY";							break;
	case SENSOR_HRM: 							szErrorVal = "SENSOR_HRM";								break;	/**< Heart Rate Monitor sensor */
	case SENSOR_HRM_LED_GREEN: 					szErrorVal = "SENSOR_HRM_LED_GREEN";					break;	/**< HRM (LED Green) sensor */
	case SENSOR_HRM_LED_IR: 					szErrorVal = "SENSOR_HRM_LED_IR";						break;	/**< HRM (LED IR) sensor */
	case SENSOR_HRM_LED_RED: 					szErrorVal = "SENSOR_HRM_LED_RED";						break;	/**< HRM (LED RED) sensor */
	case SENSOR_GYROSCOPE_UNCALIBRATED:			szErrorVal = "SENSOR_GYROSCOPE_UNCALIBRATED";			break;	 /**< Uncalibrated Gyroscope sensor (Since Tizen 2.4) */
	case SENSOR_GEOMAGNETIC_UNCALIBRATED:		szErrorVal = "SENSOR_GEOMAGNETIC_UNCALIBRATED";			break;	 /**< Uncalibrated Geomagnetic sensor (Since Tizen 2.4) */
	case SENSOR_GYROSCOPE_ROTATION_VECTOR:		szErrorVal = "SENSOR_GYROSCOPE_ROTATION_VECTOR";		break;	 /**< Gyroscope-based rotation vector sensor (Since Tizen 2.4) */
	case SENSOR_GEOMAGNETIC_ROTATION_VECTOR:	szErrorVal = "SENSOR_GEOMAGNETIC_ROTATION_VECTOR";		break;	 /**< Geomagnetic-based rotation vector sensor (Since Tizen 2.4) */
	case SENSOR_LAST: 							szErrorVal = "SENSOR_LAST";								break;
	case SENSOR_CUSTOM: 						szErrorVal = "SENSOR_CUSTOM";							break;
	}
	return szErrorVal;
}
/**
* @function 		SensorsGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
/*char* SensorsGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case SENSOR_ERROR_NONE: 					szErrorVal = "SENSOR_ERROR_NONE";						break;
	case SENSOR_ERROR_IO_ERROR: 				szErrorVal = "SENSOR_ERROR_IO_ERROR";					break;
	case SENSOR_ERROR_INVALID_PARAMETER: 		szErrorVal = "SENSOR_ERROR_INVALID_PARAMETER";			break;
	case SENSOR_ERROR_OUT_OF_MEMORY: 			szErrorVal = "SENSOR_ERROR_OUT_OF_MEMORY";				break;
	case SENSOR_ERROR_NOT_NEED_CALIBRATION: 	szErrorVal = "SENSOR_ERROR_NOT_NEED_CALIBRATION";		break;
	case SENSOR_ERROR_NOT_SUPPORTED: 			szErrorVal = "SENSOR_ERROR_NOT_SUPPORTED";				break;
	case SENSOR_ERROR_OPERATION_FAILED: 		szErrorVal = "SENSOR_ERROR_OPERATION_FAILED";			break;
	case SENSOR_ERROR_PERMISSION_DENIED: 		szErrorVal = "SENSOR_ERROR_PERMISSION_DENIED";			break;
	default : 									szErrorVal = "Unknown error";							break;
	}
	return szErrorVal;
}*/
/**
* @function 		SensorCheckFeature
* @description	 	Checks if the sensor feature is supported, unsupported or mismatched
* @parameter		sensor : sensor type
* @parameter		feature : sensor feature
* @return 			error string
*/
feature_check_e SensorCheckFeature(sensor_type_e sensor, char* feature)
{
	bool bIsFeatureSupported = TCTCheckSystemInfoFeatureSupported(feature, API_NAMESPACE);
	bool bSupported = false;

	int nRet = sensor_is_supported(sensor, &bSupported);
	if ( nRet != SENSOR_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] sensor_is_supported failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(sensor), SensorsGetError(nRet));
		return FEATURE_MISMATCH;
	}
	if ( bIsFeatureSupported != bSupported )
	{
		FPRINTF("[Line : %d][%s] sensor_is_supported return value (%s) mismatched with expected value (%s) for feature %s and sensor %s\\n", __LINE__, API_NAMESPACE, bSupported ? "true": "false", bIsFeatureSupported ? "true": "false", feature, SensorGetType(sensor));
		return FEATURE_MISMATCH;
	}
	
	if ( bSupported )
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] Sensor %s is supported on device\\n", __LINE__, API_NAMESPACE, SensorGetType(sensor));
#endif
		return FEATURE_SUPPORTED;
	}
	
#if DEBUG
	FPRINTF("[Line : %d][%s] Sensor %s is unsupported on device. Skipping test\\n", __LINE__, API_NAMESPACE, SensorGetType(sensor));
#endif

	return FEATURE_UNSUPPORTED;
}
//& purpose: To get a specific sensor handle
//& type: auto
/**
* @testcase 			CTc_Sensor_PrivilegeHealthInfo_get_default_sensor
* @type 				auto
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @since_tizen 			2.3
* @description			To get a specific sensor handle
* @scenario				Get the sensor type\n
*						Check whether it is supported in device or not\n
*						Get the sensor handle if its supported
* @apicovered			sensor_get_default_sensor
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition			NA
* @postcondition		NA
*/
int CTc_Sensor_PrivilegeHealthInfo_get_default_sensor(void)
{
	START_TEST;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		feature_check_e eFeatureCheck = SensorCheckFeature(stSensor[enum_counter].eSensorType, stSensor[enum_counter].szFeature);
		if ( eFeatureCheck == FEATURE_MISMATCH )
		{
			return 1;
		}
		else if ( eFeatureCheck == FEATURE_UNSUPPORTED )
		{
			return 0;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			// Target API
			int nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "sensor_get_default_sensor", SensorsGetError(nRet));
			
		}
	}

	return 0;
}

//& purpose: To Get the sensor list
//& type: auto
/**
* @testcase 			CTc_Sensor_PrivilegeHealthInfo_sensor_get_sensor_list
* @type 				auto
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @since_tizen 			2.3
* @description			To Get the sensor list
* @scenario				Get the sensor handle\n
*						Get the sensor list
* @apicovered			sensor_get_sensor_list				
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int CTc_Sensor_PrivilegeHealthInfo_sensor_get_sensor_list(void)
{
	START_TEST;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		feature_check_e eFeatureCheck = SensorCheckFeature(stSensor[enum_counter].eSensorType, stSensor[enum_counter].szFeature);
		if ( eFeatureCheck == FEATURE_MISMATCH )
		{
			return 1;
		}
		else if ( eFeatureCheck == FEATURE_UNSUPPORTED )
		{
			return 0;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			sensor_h *pstList;
			int nSensorCount = -1;

			// Target API
			int nRet = sensor_get_sensor_list(stSensor[enum_counter].eSensorType, &pstList, &nSensorCount);
			PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "runtime_info_get_process_cpu_usage", SensorsGetError(nRet));
		
		}
	}

	return 0;
}
