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
#include "ITs-sensor-common.h"
/** @addtogroup itc-sensor
*  @ingroup itc
*  @{
*/

/**
* @function 		SensorsGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* SensorsGetError(int nRet)
{
	char *szErrorVal = "Unknown error";

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
		case SENSOR_ERROR_NO_DATA: 					szErrorVal = "SENSOR_ERROR_NO_DATA";					break;
		case SENSOR_ERROR_NOT_AVAILABLE: 			szErrorVal = "SENSOR_ERROR_NOT_AVAILABLE";				break;
	}
	return szErrorVal;
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
		case SENSOR_SIGNIFICANT_MOTION:			szErrorVal = "SENSOR_SIGNIFICANT_MOTION";			break;
		case SENSOR_HUMAN_PEDOMETER:       			szErrorVal = "SENSOR_HUMAN_PEDOMETER";					break; 
		case SENSOR_HUMAN_SLEEP_MONITOR :	        szErrorVal = "SENSOR_HUMAN_SLEEP_MONITOR";		        break;  	
		case SENSOR_HUMAN_SLEEP_DETECTOR :	        szErrorVal = "SENSOR_HUMAN_SLEEP_DETECTOR";		        break;  	
		case SENSOR_HRM_BATCH :	        szErrorVal = "SENSOR_HRM_BATCH";		        break;
		case SENSOR_HRM_LED_GREEN_BATCH :	        szErrorVal = "SENSOR_HRM_LED_GREEN_BATCH";		        break;
		case SENSOR_ORIENTATION :	        szErrorVal = "SENSOR_ORIENTATION";		        break;
		case SENSOR_GYROSCOPE_ORIENTATION :	        szErrorVal = "SENSOR_GYROSCOPE_ORIENTATION";		        break;
		case SENSOR_GEOMAGNETIC_ORIENTATION:	        szErrorVal = "SENSOR_GEOMAGNETIC_ORIENTATION";		        break;
	}
	return szErrorVal;
}

/**
* @function 		SensorOption
* @description	 	Maps sensor option enums 
* @parameter		nSensorOption : sensor option
* @return 			error string
*/
char* SensorOption(sensor_option_e nSensorOption)
{
	char *szErrorVal = "Unknown Error";
	switch ( nSensorOption )
	{
	case SENSOR_OPTION_DEFAULT: 					szErrorVal = "SENSOR_OPTION_DEFAULT";					break;
	case SENSOR_OPTION_ON_IN_SCREEN_OFF: 			szErrorVal = "SENSOR_OPTION_ON_IN_SCREEN_OFF";			break;
	case SENSOR_OPTION_ON_IN_POWERSAVE_MODE: 		szErrorVal = "SENSOR_OPTION_ON_IN_POWERSAVE_MODE";		break;
	case SENSOR_OPTION_ALWAYS_ON: 					szErrorVal = "SENSOR_OPTION_ALWAYS_ON";					break;	
	}
	return szErrorVal;
}

/**
* @function 		SensorTimeout
* @description	 	Called if some callback is not invoked for a particular SensorTimeout
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean SensorTimeout(gpointer data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Callback Time-out\\n", __LINE__, API_NAMESPACE);
#endif

	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(g_pSensorMainLoop);
		g_main_loop_unref(g_pSensorMainLoop);
		g_pSensorMainLoop = NULL;
	}
	return false;
}

/**	
* @function               SensorAttributeOption	
* @description            Maps sensorattribute option enums 	
* @parameter              nSensorAttrOption : sensor attribute option	
* @return                 error string	
*/	
char* SensorAttributeOption(sensor_attribute_e nSensorAttrOption)	
{	
   char *szErrorVal = "Unknown Error";	
   switch ( nSensorAttrOption )	
   {	
	   case SENSOR_ATTRIBUTE_AXIS_ORIENTATION:        szErrorVal = "SENSOR_ATTRIBUTE_AXIS_ORIENTATION";              break;	
	   case SENSOR_ATTRIBUTE_PAUSE_POLICY:            szErrorVal = "SENSOR_ATTRIBUTE_PAUSE_POLICY";                  break;       	
	
   }	
   return szErrorVal;	
}			
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

/** @} */
