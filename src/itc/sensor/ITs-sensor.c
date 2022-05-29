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

bool g_bSensorEventCallback;
bool g_bSensorAccuracyChangeCallback;

SensorFeature stSensor[] = {
	{SENSOR_ACCELEROMETER, "http://tizen.org/feature/sensor.accelerometer"},
	{SENSOR_GRAVITY, "http://tizen.org/feature/sensor.gravity"},
	{SENSOR_LINEAR_ACCELERATION, "http://tizen.org/feature/sensor.linear_acceleration"},
	{SENSOR_MAGNETIC, "http://tizen.org/feature/sensor.magnetometer"},
	{SENSOR_ROTATION_VECTOR, "http://tizen.org/feature/sensor.rotation_vector"},
	{SENSOR_GYROSCOPE, "http://tizen.org/feature/sensor.gyroscope"},
	{SENSOR_LIGHT, "http://tizen.org/feature/sensor.photometer"},
	{SENSOR_PROXIMITY, "http://tizen.org/feature/sensor.proximity"},
	{SENSOR_PRESSURE, "http://tizen.org/feature/sensor.barometer"},
	{SENSOR_ULTRAVIOLET, "http://tizen.org/feature/sensor.ultraviolet"},
	{SENSOR_TEMPERATURE, "http://tizen.org/feature/sensor.temperature"},
	{SENSOR_HUMIDITY, "http://tizen.org/feature/sensor.humidity"},
	{SENSOR_HRM, "http://tizen.org/feature/sensor.heart_rate_monitor"},
	{SENSOR_HRM_LED_GREEN, "http://tizen.org/feature/sensor.heart_rate_monitor.led_green"},
	{SENSOR_HRM_LED_IR, "http://tizen.org/feature/sensor.heart_rate_monitor.led_ir"},
	{SENSOR_HRM_LED_RED, "http://tizen.org/feature/sensor.heart_rate_monitor.led_red"},
	{SENSOR_GYROSCOPE_UNCALIBRATED, "http://tizen.org/feature/sensor.gyroscope.uncalibrated"},
	{SENSOR_GEOMAGNETIC_UNCALIBRATED, "http://tizen.org/feature/sensor.magnetometer.uncalibrated"},
	{SENSOR_GYROSCOPE_ROTATION_VECTOR, "http://tizen.org/feature/sensor.gyroscope_rotation_vector"},
	{SENSOR_GEOMAGNETIC_ROTATION_VECTOR, "http://tizen.org/feature/sensor.geomagnetic_rotation_vector"},
	{SENSOR_SIGNIFICANT_MOTION, "http://tizen.org/feature/sensor.significant_motion"},
	{SENSOR_HRM_BATCH, "http://tizen.org/feature/sensor.heart_rate_monitor.batch"},
	{SENSOR_HRM_LED_GREEN_BATCH, "http://tizen.org/feature/sensor.heart_rate_monitor.led_green.batch"},
	{SENSOR_ORIENTATION, "http://tizen.org/feature/sensor.orientation"},
	{SENSOR_GYROSCOPE_ORIENTATION, "http://tizen.org/feature/sensor.gyroscope_orientation"},
	{SENSOR_GEOMAGNETIC_ORIENTATION, "http://tizen.org/feature/sensor.geomagnetic_orientation"}
};

const char *stUriTypes[] = {
	"http://tizen.org/sensor/general/accelerometer",                   /**< Accelerometer */
	"http://tizen.org/sensor/general/gravity",                         /**< Gravity sensor */
	"http://tizen.org/sensor/general/linear_acceleration",             /**< Linear acceleration sensor */
	"http://tizen.org/sensor/general/magnetic",                        /**< Magnetic sensor */
	"http://tizen.org/sensor/general/rotation_vector",                 /**< Rotation Vector sensor */
	"http://tizen.org/sensor/general/orientation",                     /**< Orientation sensor */
	"http://tizen.org/sensor/general/gyroscope",                       /**< Gyroscope sensor */
	"http://tizen.org/sensor/general/light",                           /**< Light sensor */
	"http://tizen.org/sensor/general/pressure",                        /**< Pressure sensor */
	"http://tizen.org/sensor/general/ultraviolet",                     /**< Ultraviolet sensor */
	"http://tizen.org/sensor/general/temperature",                     /**< Temperature sensor */
	"http://tizen.org/sensor/general/humidity",                        /**< Humidity sensor */
	"http://tizen.org/sensor/healthinfo/heart_rate_monitor",           /**< Heart Rate Monitor sensor */
	"http://tizen.org/sensor/healthinfo/heart_rate_monitor.led_green", /**< HRM (LED Green) sensor */
	"http://tizen.org/sensor/healthinfo/heart_rate_monitor.led_ir",    /**< HRM (LED IR) sensor */
	"http://tizen.org/sensor/healthinfo/heart_rate_monitor.led_red",   /**< HRM (LED RED) sensor */
	"http://tizen.org/sensor/general/gyroscope.uncalibrated",          /**< Uncalibrated Gyroscope sensor (Since Tizen 2.4) */
	"http://tizen.org/sensor/general/geomagnetic.uncalibrated",        /**< Uncalibrated Geomagnetic sensor (Since Tizen 2.4) */
	"http://tizen.org/sensor/general/gyroscope_rotation_vector",       /**< Gyroscope-based rotation vector sensor (Since Tizen 2.4) */
	"http://tizen.org/sensor/general/geomagnetic_rotation_vector",     /**< Geomagnetic-based rotation vector sensor (Since Tizen 2.4) */
	"http://tizen.org/sensor/healthinfo/human_pedometer",              /**< Pedometer
	                                                                        @if MOBILE (Since 3.0) @elseif WEARABLE (Since 2.3.2) @endif
	                                                                        @n Privilege : http://tizen.org/privilege/healthinfo */
	"http://tizen.org/sensor/healthinfo/heart_rate_monitor.batch",           /**< Heart Rate Monitor Batch sensor */
	"http://tizen.org/sensor/healthinfo/heart_rate_monitor.led_green.batch" /**< HRM (LED Green) Batch sensor */
};

int enum_size = sizeof(stSensor) / sizeof(stSensor[0]);
int enum_counter = 0;
int nUriTypeSize = sizeof(stUriTypes) / sizeof(stUriTypes[0]);

/**
* @function 		ITs_Sensors_startup
* @description	 	Called before each test, creates Sensors
* @parameter		NA
* @return 			NA
*/
void ITs_sensor_listener_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Sensor_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function			ITs_Sensors_cleanup
* @description		Called after each test, destroys Sensors
* @parameter		NA
* @return			NA
*/
void ITs_sensor_listener_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Sensor_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}



/**
* @function			SensorEventCallback
* @description		Called when sensor handle is interrupted.
* @parameter[IN]	The sensor handle
* @parameter[IN]	The event information
* @parameter[IN]	The user data passed from the callback registration function
* @return			NA
*/
void SensorEventCallback(sensor_h g_stSensorHandle, sensor_event_s peSensorEventsCallback[], int pCount, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] SensorEventCallback is called\\n", __LINE__, API_NAMESPACE);
#endif

	g_bSensorEventCallback = true;
	if ( g_pSensorMainLoop )
	{
		g_main_loop_quit(g_pSensorMainLoop);
		g_main_loop_unref(g_pSensorMainLoop);
		g_pSensorMainLoop = NULL;
	}
}

/** @addtogroup itc-sensor-testcases
*  @brief 		Integration testcases for module sensor
*  @ingroup 	itc-sensor
*  @{
*/
//& purpose: To check whether a given sensor type is available on a device
//& type: auto
/**
* @testcase 			ITc_sensor_is_supported_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To check whether a given sensor type is available on a device
* @scenario				Get the sensor type\n
*						Check whether it is supported in device or not
* @apicovered			sensor_is_supported
* @passcase				When sensor_is_supported is successful
* @failcase				If target API sensor_is_supported fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_is_supported_p(void)
{
	START_TEST;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		bool bIsFeatureSupported = TCTCheckSystemInfoFeatureSupported(stSensor[enum_counter].szFeature, API_NAMESPACE);
		bool bSupported = false;

		// Target API
		int nRet = sensor_is_supported(stSensor[enum_counter].eSensorType, &bSupported);
		if ( nRet != SENSOR_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] sensor_is_supported failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
			return 1;
		}

		if ( bIsFeatureSupported != bSupported )
		{
			FPRINTF("[Line : %d][%s] sensor_is_supported return value (%s) mismatched with expected value (%s) for feature %s and sensor %s\\n", __LINE__, API_NAMESPACE, bSupported ? "true": "false", bIsFeatureSupported ? "true": "false", stSensor[enum_counter].szFeature, SensorGetType(stSensor[enum_counter].eSensorType));
			return 1;
		}
	}

	return 0;
}

//& purpose: To get a specific sensor handle
//& type: auto
/**
* @testcase 			ITc_sensor_get_default_sensor_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To get a specific sensor handle
* @scenario				Get the sensor type\n
*						Check whether it is supported in device or not\n
*						Get the sensor handle if its supported
* @apicovered			sensor_get_default_sensor
* @passcase				When sensor_get_default_sensor is successful
* @failcase				If target API sensor_get_default_sensor fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_get_default_sensor_p(void)
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
			continue;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			// Target API
			int nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_default_sensor failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");
		}
	}

	return 0;
}

//& purpose: To get FIFO count of sensor
//& type: auto
/**
* @testcase 			ITc_sensor_get_fifo_count_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To get FIFO count of sensor
* @scenario				Create the sensor handle\n
*						Get the FIFO count
* @apicovered			sensor_get_fifo_count
* @passcase				When sensor_get_fifo_count is successful
* @failcase				If target API sensor_get_fifo_count fails or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_get_fifo_count_p(void)
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
			continue;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			int nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_default_sensor failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");

			int nFifoCount = -1;

			// Target API
			nRet = sensor_get_fifo_count(g_pstSensorHandle, &nFifoCount);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_fifo_count failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			if ( nFifoCount < 0 )
			{
				FPRINTF("[Line : %d][%s] sensor_get_fifo_count returned unexpected value %d for sensor %s\\n", __LINE__, API_NAMESPACE, nFifoCount, SensorGetType(stSensor[enum_counter].eSensorType));
				return 1;
			}
		}
	}

	return 0;
}

//& purpose: To get maximum batch count of sensor.
//& type: auto
/**
* @testcase 			ITc_sensor_get_max_batch_count_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To get maximum batch count of sensor.
* @scenario				Get the sensor handle\n
*						Get the maximum batch count of sensor
* @apicovered			sensor_get_max_batch_count
* @passcase				When sensor_get_max_batch_count is successful
* @failcase				If target API sensor_get_max_batch_count fails or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_get_max_batch_count_p(void)
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
			continue;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			int nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_default_sensor failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");

			int nMaxBatchCount = -1;

			// Target API
			nRet = sensor_get_max_batch_count(g_pstSensorHandle, &nMaxBatchCount);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_max_batch_count failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			if ( nMaxBatchCount < 0 )
			{
				FPRINTF("[Line : %d][%s] sensor_get_max_batch_count returned unexpected value %d for sensor %s\\n", __LINE__, API_NAMESPACE, nMaxBatchCount, SensorGetType(stSensor[enum_counter].eSensorType));
				return 1;
			}
		}
	}

	return 0;
}

//& purpose: To get maximum range of sensor.
//& type: auto
/**
* @testcase 			ITc_sensor_get_max_range_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To get maximum range of sensor.
* @scenario				Get the sensor handle\n
*						Get the maximum range
* @apicovered			sensor_get_max_range
* @passcase				When sensor_get_max_range is successful
* @failcase				If target API sensor_get_max_range fails or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_get_max_range_p(void)
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
			continue;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			int nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_default_sensor failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");

			float fMaxRange = -1;

			// Target API
			nRet = sensor_get_max_range(g_pstSensorHandle, &fMaxRange);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_max_range failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			if ( fMaxRange < 0 )
			{
				FPRINTF("[Line : %d][%s] sensor_get_max_range returned unexpected value %f for sensor %s\\n", __LINE__, API_NAMESPACE, fMaxRange, SensorGetType(stSensor[enum_counter].eSensorType));
				return 1;
			}
		}
	}

	return 0;
}

//& purpose: To get minimum range of sensor.
//& type: auto
/**
* @testcase 			ITc_sensor_get_min_range_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To get minimum range of sensor.
* @scenario				Get the sensor handle\n
*						Get minimum range of sensor.
* @apicovered			sensor_get_min_range
* @passcase				When sensor_get_min_range is successful
* @failcase				If target API sensor_get_min_range fails or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_get_min_range_p(void)
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
			continue;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			int nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_default_sensor failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");

			float fMinRange = -1;

			// Target API
			nRet = sensor_get_min_range(g_pstSensorHandle, &fMinRange);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_min_range failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
		}
	}

	return 0;
}

//& purpose: To get minimum interval of sensor.
//& type: auto
/**
* @testcase 			ITc_sensor_get_min_interval_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To get minimum interval of sensor.
* @scenario				Get the sensor handle\n
*						Get minimum interval of sensor and check whether it is valid or not
* @apicovered			sensor_get_min_interval
* @passcase				When sensor_get_min_interval is successful
* @failcase				If target API sensor_get_min_interval fails or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_get_min_interval_p(void)
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
			continue;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			int nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_default_sensor failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");

			int nMinInterval = -1;

			// Target API
			nRet = sensor_get_min_interval(g_pstSensorHandle, &nMinInterval);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_min_interval failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			if ( nMinInterval < 0 )
			{
				FPRINTF("[Line : %d][%s] sensor_get_min_interval returned unexpected value %d for sensor %s\\n", __LINE__, API_NAMESPACE, nMinInterval, SensorGetType(stSensor[enum_counter].eSensorType));
				return 1;
			}
		}
	}

	return 0;
}

//& purpose: To get a name of sensor
//& type: auto
/**
* @testcase 			ITc_sensor_get_name_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To get a name of sensor
* @scenario				Get the sensor handle\n
*						Get a name of sensor.
* @apicovered			sensor_get_name
* @passcase				When sensor_get_name is successful
* @failcase				If target API sensor_get_name fails or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_get_name_p(void)
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
			continue;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			int nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_default_sensor failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");

			char *pszName = NULL;

			// Target API
			nRet = sensor_get_name(g_pstSensorHandle, &pszName);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_name failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			CHECK_VALUE_STRING(pszName, "sensor_get_name");
		}
	}

	return 0;
}

//& purpose: To get resolution of sensor
//& type: auto
/**
* @testcase 			ITc_sensor_get_resolution_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To get resolution of sensor
* @scenario				Get the sensor handle\n
*						Get a resolution of sensor
* @apicovered			sensor_get_resolution
* @passcase				When sensor_get_resolution is successful
* @failcase				If target API sensor_get_resolution fails or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_get_resolution_p(void)
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
			continue;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			int nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_default_sensor failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");

			float fResolution = -1;

			// Target API
			nRet = sensor_get_resolution(g_pstSensorHandle, &fResolution);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_resolution failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			if ( fResolution < 0 )
			{
				FPRINTF("[Line : %d][%s] sensor_get_resolution returned unexpected value %f for sensor %s\\n", __LINE__, API_NAMESPACE, fResolution, SensorGetType(stSensor[enum_counter].eSensorType));
				return 1;
			}
		}
	}

	return 0;
}

//& purpose: To Get the sensor list
//& type: auto
/**
* @testcase 			ITc_sensor_get_sensor_list_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To Get the sensor list
* @scenario				Get the sensor handle\n
*						Get the sensor list
* @apicovered			sensor_get_sensor_list
* @passcase				When sensor_get_sensor_list is successful
* @failcase				If target API sensor_get_sensor_list fails or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_get_sensor_list_p(void)
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
			continue;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			sensor_h *pstList;
			int nSensorCount = -1;

			// Target API
			int nRet = sensor_get_sensor_list(stSensor[enum_counter].eSensorType, &pstList, &nSensorCount);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_sensor_list failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			if ( pstList == NULL )
			{
				FPRINTF("[Line : %d][%s] sensor_get_sensor_list is unsuccessful as psList is NULL\\n", __LINE__, API_NAMESPACE);
				return 1;
			}
		}
	}

	return 0;
}

//& purpose: To get the type of sensor.
//& type: auto
/**
* @testcase 			ITc_sensor_get_type_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To get the type of sensor.
* @scenario				Get the sensor handle\n
*						Get the type of sensor and check whether its correct or not.
* @apicovered			sensor_get_type
* @passcase				When sensor_get_type is successful
* @failcase				If target API sensor_get_type fails or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_get_type_p(void)
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
			continue;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			int nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_default_sensor failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");

			sensor_type_e nType = -1;

			// Target API
			nRet = sensor_get_type(g_pstSensorHandle, &nType);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_type failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			if ( nType != stSensor[enum_counter].eSensorType)
			{
				FPRINTF("[Line : %d][%s] sensor_get_type returned mismatched value %s for sensor %s\\n", __LINE__, API_NAMESPACE, SensorGetType(nType), SensorGetType(stSensor[enum_counter].eSensorType));
				return 1;
			}
		}
	}

	return 0;
}

//& purpose: To get the vendor of the sensor
//& type: auto
/**
* @testcase 			ITc_sensor_get_vendor_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To get the vendor of the sensor
* @scenario				Get the sensor handle\n
*						Get the vendor of the sensor
* @apicovered			sensor_get_vendor
* @passcase				When sensor_get_vendor is successful
* @failcase				If target API sensor_get_vendor fails or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_get_vendor_p(void)
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
			continue;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			int nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_default_sensor failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");

			char *pszVendor = NULL;

			// Target API
			nRet = sensor_get_vendor(g_pstSensorHandle, &pszVendor);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_vendor failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			CHECK_VALUE_STRING(pszVendor, "sensor_get_vendor");
		}
	}

	return 0;
}

//& purpose: To create and destroy the sensor listener
//& type: auto
/**
* @testcase 			ITc_sensor_create_destroy_listener_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To create and destroy the sensor listener
* @scenario				Create the sensor handle\n
*						Create the sensor listener\n
*						Destroy the sensor listener
* @apicovered			sensor_create_listener, sensor_destroy_listener
* @passcase				When sensor_create_listener and sensor_destroy_listener is successful
* @failcase				If target API sensor_create_listener or sensor_destroy_listener fails or any precondition API fails
* @precondition			Sensors handle must be created
* @postcondition		Sensors handle must be released
*/
int ITc_sensor_create_destroy_listener_p(void)
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
			continue;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			int nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_default_sensor failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");

			// Target API
			nRet = sensor_create_listener(g_pstSensorHandle, &g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_create_listener failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			if ( g_pstSensorListener == NULL)
			{
				FPRINTF("[Line : %d][%s] sensor_create_listener failed to create listener of sensor %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType));
				sensor_destroy_listener(g_pstSensorListener);
				return 1;
			}

			// Target API
			nRet = sensor_destroy_listener(g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_destroy_listener failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
		}
	}

	return 0;
}

//& purpose: To change the interval at sensor measurements.
//& type: auto
/**
* @testcase 			ITc_sensor_listener_set_interval_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To change the interval at sensor measurements.
* @scenario				Get the listener handle\n
*						Change the interval at sensor measurements
* @apicovered			sensor_listener_set_interval
* @passcase				When sensor_listener_set_interval is successful
* @failcase				If target API sensor_listener_set_interval fails or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_listener_set_interval_p(void)
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
			continue;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			int nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_default_sensor failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");

			nRet = sensor_create_listener(g_pstSensorHandle, &g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] Support API sensor_create_listener failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			if ( g_pstSensorListener == NULL)
			{
				FPRINTF("[Line : %d][%s] Support API sensor_create_listener failed to create listener of sensor %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType));
				return 1;
			}

			unsigned int unInterval = 0;
			nRet = sensor_listener_set_events_cb(g_pstSensorListener, SensorEventCallback, NULL);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] Support API sensor_listener_set_events_cb failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				sensor_destroy_listener(g_pstSensorListener);
				return 1;
			}

			nRet = sensor_listener_start(g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] Support API sensor_listener_start failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				sensor_listener_unset_events_cb(g_pstSensorListener);
				sensor_destroy_listener(g_pstSensorListener);
				return 1;
			}

			// Target API
			nRet = sensor_listener_set_interval(g_pstSensorListener, unInterval);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_listener_set_interval failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				sensor_listener_stop(g_pstSensorListener);
				sensor_listener_unset_events_cb(g_pstSensorListener);
				sensor_destroy_listener(g_pstSensorListener);
				return 1;
			}

			nRet = sensor_listener_stop(g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] Support API sensor_listener_stop failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				sensor_listener_unset_events_cb(g_pstSensorListener);
				sensor_destroy_listener(g_pstSensorListener);
				return 1;
			}

			nRet = sensor_listener_unset_events_cb(g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] Support API sensor_listener_unset_events_cb failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				sensor_destroy_listener(g_pstSensorListener);
				return 1;
			}

			nRet = sensor_destroy_listener(g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] Support API sensor_destroy_listener failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
		}
	}

	return 0;
}

//& purpose: To change the maximum batch latency at sensor measurements.
//& type: auto
/**
* @testcase 			ITc_sensor_listener_set_option_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To change the maximum batch latency at sensor measurements.
* @scenario				Get the listener handle\n
*						Change the batch latency
* @apicovered			sensor_listener_set_option
* @passcase				When sensor_listener_set_option is successful
* @failcase				If target API sensor_listener_set_option fails or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_listener_set_option_p(void)
{
	START_TEST;

	sensor_option_e eSensorOption[] = {
		SENSOR_OPTION_DEFAULT,
		SENSOR_OPTION_ON_IN_SCREEN_OFF,
		SENSOR_OPTION_ON_IN_POWERSAVE_MODE,
		SENSOR_OPTION_ALWAYS_ON
	};
	int enum2_size = sizeof(eSensorOption) / sizeof(eSensorOption[0]);
	int enum2_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		feature_check_e eFeatureCheck = SensorCheckFeature(stSensor[enum_counter].eSensorType, stSensor[enum_counter].szFeature);
		if ( eFeatureCheck == FEATURE_MISMATCH )
		{
			return 1;
		}
		else if ( eFeatureCheck == FEATURE_UNSUPPORTED )
		{
			continue;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			int nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_default_sensor failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");

			nRet = sensor_create_listener(g_pstSensorHandle, &g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] Support API sensor_create_listener failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			if ( g_pstSensorListener == NULL)
			{
				FPRINTF("[Line : %d][%s] Support API sensor_create_listener failed to create listener of sensor %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType));
				return 1;
			}

			for ( enum2_counter=0;enum2_counter<enum2_size;enum2_counter++)
			{
				// Target API
				nRet = sensor_listener_set_option(g_pstSensorListener, eSensorOption[enum2_counter]);
				if ( nRet != SENSOR_ERROR_NONE )
				{
					FPRINTF("[Line : %d][%s] sensor_listener_set_option failed for sensor %s and option %s, error returned = %s\\n",
						__LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorOption(eSensorOption[enum2_counter]), SensorsGetError(nRet));
					sensor_destroy_listener(g_pstSensorListener);
					return 1;
				}
			}

			nRet = sensor_destroy_listener(g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] Support API sensor_destroy_listener failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
		}
	}

	return 0;
}

//& purpose: To start and stop sensor server for the given listener
//& type: auto
/**
* @testcase 			ITc_sensor_listener_start_stop_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To start and stop sensor server for the given listener
* @scenario				Start the sensor sever for sensor listener and sensor type
*						Stop the sensor sever
* @apicovered			sensor_listener_start, sensor_listener_stop
* @passcase				When sensor_listener_start and sensor_listener_stop is successful
* @failcase				If target API sensor_listener_start or sensor_listener_stop fails or any precondition API fails
* @precondition			Sensors handle must be created
* @postcondition		Sensors handle must be released
*/
int ITc_sensor_listener_start_stop_p(void)
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
			continue;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			int nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_default_sensor failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");

			nRet = sensor_create_listener(g_pstSensorHandle, &g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] Support API sensor_create_listener failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			if ( g_pstSensorListener == NULL)
			{
				FPRINTF("[Line : %d][%s] Support API sensor_create_listener failed to create listener of sensor %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType));
				return 1;
			}

			// Target API
			nRet = sensor_listener_start(g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_listener_start failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				sensor_destroy_listener(g_pstSensorListener);
				return 1;
			}

			// Target API
			nRet = sensor_listener_stop(g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_listener_stop failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				sensor_destroy_listener(g_pstSensorListener);
				return 1;
			}

			nRet = sensor_destroy_listener(g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] Support API sensor_destroy_listener failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
		}
	}

	return 0;
}

//& purpose: To read the current sensor data list via a given sensor listener.
//& type: auto
/**
* @testcase 			ITc_sensor_listener_read_data_list_p
* @type 				auto
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @since_tizen 			6.0
* @description			Reads the current sensor data list via a given sensor listener.
* @scenario				This function synchronously reads the sensor reading of the corresponding sensor, if available.
*						Otherwise, if the sensor is not ready to report its values, this function fails and returns
* @apicovered			sensor_listener_read_data_list
* @passcase				When sensor_listener_read_data_list is successful
* @failcase				If target API sensor_listener_read_data_list fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_listener_read_data_list_p(void)
{
	START_TEST;

	int nSensorTimeoutId = 0;
	int nTimeOutCB = 2000;
	int nRet = -1;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		if ( SENSOR_PROXIMITY == stSensor[enum_counter].eSensorType )
		{
			//For SENSOR_PROXIMITY type sensor, sensor_listener_read_data() will not return the sensor_event_s
			//Instead read the value of sensor_proximity_e in some way
			continue;
		}

		if(stSensor[enum_counter].eSensorType == SENSOR_HRM_BATCH || stSensor[enum_counter].eSensorType == SENSOR_HRM_LED_GREEN_BATCH)
		{
			nTimeOutCB = 30000;
		}

		feature_check_e eFeatureCheck = SensorCheckFeature(stSensor[enum_counter].eSensorType, stSensor[enum_counter].szFeature);
		if ( eFeatureCheck == FEATURE_MISMATCH )
		{
			return 1;
		}
		else if ( eFeatureCheck == FEATURE_UNSUPPORTED )
		{
			continue;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_get_default_sensor", SensorsGetError(nRet));
			CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");

			nRet = sensor_create_listener(g_pstSensorHandle, &g_pstSensorListener);
			PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_create_listener", SensorsGetError(nRet));
			CHECK_HANDLE(g_pstSensorHandle, "sensor_create_listener");

			nRet = sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_ALWAYS_ON);
			PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_listener_set_option", SensorsGetError(nRet), sensor_destroy_listener(g_pstSensorListener));

			nRet = sensor_listener_set_events_cb(g_pstSensorListener, SensorEventCallback, NULL);
			PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_listener_set_events_cb", SensorsGetError(nRet), sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT);sensor_destroy_listener(g_pstSensorListener));

			nRet = sensor_listener_start(g_pstSensorListener);
			PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_listener_start", SensorsGetError(nRet), sensor_listener_unset_events_cb(g_pstSensorListener);sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT);sensor_destroy_listener(g_pstSensorListener));

			RUN_POLLING_LOOP;

			sensor_event_s *pstSensorEvent;
			int nCount = 0;

			// Target API
			nRet = sensor_listener_read_data_list(g_pstSensorListener, &pstSensorEvent, &nCount);//check for nCount
			PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_listener_read_data_list", SensorsGetError(nRet), sensor_listener_stop(g_pstSensorListener);sensor_listener_unset_events_cb(g_pstSensorListener);sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT);sensor_destroy_listener(g_pstSensorListener));

			if ( pstSensorEvent->accuracy < SENSOR_DATA_ACCURACY_UNDEFINED
				|| pstSensorEvent->accuracy > SENSOR_DATA_ACCURACY_VERYGOOD
				||  pstSensorEvent->value_count < 0
				|| nCount <= 0 )
			{
				FPRINTF("[Line : %d][%s] sensor_listener_read_data_list retrieved wrong pstSensorEvent for sensor %s: accuracy = %d, timestamp = %llu, value_count = %d, values = %f, nCount = %d\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), pstSensorEvent->accuracy, pstSensorEvent->timestamp, pstSensorEvent->value_count, *(pstSensorEvent->values), nCount);
				sensor_listener_stop(g_pstSensorListener);
				sensor_listener_unset_events_cb(g_pstSensorListener);
				sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT);
				sensor_destroy_listener(g_pstSensorListener);
				return 1;
			}

			nRet = sensor_listener_stop(g_pstSensorListener);
			PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_listener_stop", SensorsGetError(nRet), sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT);sensor_listener_unset_events_cb(g_pstSensorListener);sensor_destroy_listener(g_pstSensorListener));

			nRet = sensor_listener_unset_events_cb(g_pstSensorListener);
PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_listener_unset_events_cb", SensorsGetError(nRet), sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT);sensor_destroy_listener(g_pstSensorListener));

			//Reset option
			nRet = sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT);
			PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_listener_set_option", SensorsGetError(nRet), sensor_destroy_listener(g_pstSensorListener));

			nRet = sensor_destroy_listener(g_pstSensorListener);
			PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_destroy_listener", SensorsGetError(nRet));
		}
	}

	return 0;
}

//& purpose: To flush stored data of a sensor.
//& type: auto
/**
* @testcase 			ITc_sensor_listener_flush_p
* @type 				auto
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @since_tizen 			6.0
* @description			Flushes stored data of a sensor.
* @scenario				Flushes all data of a sensor as if the max batch latency has expired.
*						Data is delivered in the usual way through the event callback function.
*						In case of non-batching sensors, this function does nothing and returns #SENSOR_ERROR_NONE.
* @apicovered			sensor_listener_flush
* @passcase				When sensor_listener_flush is successful
* @failcase				If target API sensor_listener_flush fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_listener_flush_p(void)
{
	START_TEST;

	int nRet = -1;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		if ( SENSOR_PROXIMITY == stSensor[enum_counter].eSensorType )
		{
			//For SENSOR_PROXIMITY type sensor, sensor_listener_read_data() will not return the sensor_event_s
			//Instead read the value of sensor_proximity_e in some way
			continue;
		}

		feature_check_e eFeatureCheck = SensorCheckFeature(stSensor[enum_counter].eSensorType, stSensor[enum_counter].szFeature);
		if ( eFeatureCheck == FEATURE_MISMATCH )
		{
			return 1;
		}
		else if ( eFeatureCheck == FEATURE_UNSUPPORTED )
		{
			continue;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_get_default_sensor", SensorsGetError(nRet));
			CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");

			nRet = sensor_create_listener(g_pstSensorHandle, &g_pstSensorListener);
			PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_create_listener", SensorsGetError(nRet));
			CHECK_HANDLE(g_pstSensorHandle, "sensor_create_listener");

			nRet = sensor_listener_start(g_pstSensorListener);
			PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_listener_start", SensorsGetError(nRet), sensor_destroy_listener(g_pstSensorListener));

			nRet = sensor_listener_flush(g_pstSensorListener);
			PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_listener_flush", SensorsGetError(nRet), sensor_destroy_listener(g_pstSensorListener));

			nRet = sensor_listener_stop(g_pstSensorListener);
			PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_listener_stop", SensorsGetError(nRet), sensor_destroy_listener(g_pstSensorListener));

			nRet = sensor_destroy_listener(g_pstSensorListener);
			PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_destroy_listener", SensorsGetError(nRet));
		}
	}

	return 0;
}

//& purpose: To register and unregister a callback function to be invoked when an sensor event occurs.
//& type: auto
/**
* @testcase 			ITc_sensor_listener_set_unset_events_cb_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To register and un-register a callback function to be invoked when an sensor event occurs.
* @scenario				Get the handle to the Sensor\n
*						Get the listener handle\n
*						Register the callback function\n
*						Check the user data received in callback function
* @apicovered			sensor_listener_set_events_cb,sensor_listener_unset_events_cb
* @passcase				When sensor_listener_set_events_cb or sensor_listener_unset_events_cb is successful
* @failcase				If target API sensor_listener_set_events_cb fails or callback or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_listener_set_unset_events_cb_p(void)
{
	START_TEST;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		if ( SENSOR_PROXIMITY == stSensor[enum_counter].eSensorType || SENSOR_HRM_LED_GREEN_BATCH  == stSensor[enum_counter].eSensorType )
		{
			//For SENSOR_PROXIMITY type sensor, callback sensor_event_cb will not be invoked
			//Instead read the value of sensor_proximity_e in some way
			// For SENSOR_HRM_LED_GREEN_BATCH type sensor, callback sensor_event_cb will be invoked in another TC
			continue;
		}

		feature_check_e eFeatureCheck = SensorCheckFeature(stSensor[enum_counter].eSensorType, stSensor[enum_counter].szFeature);
		if ( eFeatureCheck == FEATURE_MISMATCH )
		{
			return 1;
		}
		else if ( eFeatureCheck == FEATURE_UNSUPPORTED )
		{
			continue;
		}
		else if ( eFeatureCheck == FEATURE_SUPPORTED )
		{
			int nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_get_default_sensor failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");

			nRet = sensor_create_listener(g_pstSensorHandle, &g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] Support API sensor_create_listener failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			if ( g_pstSensorListener == NULL)
			{
				FPRINTF("[Line : %d][%s] Support API sensor_create_listener failed to create listener of sensor %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType));
				return 1;
			}

			nRet = sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_ALWAYS_ON);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] Support API sensor_listener_set_option is failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				sensor_destroy_listener(g_pstSensorListener);
				return 1;
			}

			usleep(200);
			g_bSensorEventCallback = false;

			int nSensorTimeoutId = 0;
			int nTimeOutCB = 2000;
			if(stSensor[enum_counter].eSensorType == SENSOR_HRM_BATCH)
			{
				nTimeOutCB = 30000;
			}

			// Target API
			nRet = sensor_listener_set_events_cb(g_pstSensorListener, SensorEventCallback, NULL);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_listener_set_events_cb failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT);
				sensor_destroy_listener(g_pstSensorListener);
				return 1;
			}

			nRet = sensor_listener_start(g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] Support API sensor_listener_start failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				sensor_listener_unset_events_cb(g_pstSensorListener);
				sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT);
				sensor_destroy_listener(g_pstSensorListener);
				return 1;
			}

			RUN_POLLING_LOOP;

			if ( !g_bSensorEventCallback )
			{
				FPRINTF("[Line : %d][%s] sensor_listener_set_events_cb failed to invoke callback for sensor %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType));
				sensor_listener_stop(g_pstSensorListener);
				sensor_listener_unset_events_cb(g_pstSensorListener);
				sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT);
				sensor_destroy_listener(g_pstSensorListener);
				return 1;
			}

			nRet = sensor_listener_stop(g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] Support API sensor_listener_stop failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				sensor_listener_unset_events_cb(g_pstSensorListener);
				sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT);
				sensor_destroy_listener(g_pstSensorListener);
				return 1;
			}

			g_bSensorEventCallback = false;

			// Target API
			nRet = sensor_listener_unset_events_cb(g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] sensor_listener_unset_events_cb failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT);
				sensor_destroy_listener(g_pstSensorListener);
				return 1;
			}

			nRet = sensor_listener_start(g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] Support API sensor_listener_start failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT);
				sensor_destroy_listener(g_pstSensorListener);
				return 1;
			}

			RUN_POLLING_LOOP;

			if ( g_bSensorEventCallback )
			{
				FPRINTF("[Line : %d][%s] sensor_listener_unset_events_cb failed to stop callback invocation for sensor %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType));
				sensor_listener_stop(g_pstSensorListener);
				sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT);
				sensor_destroy_listener(g_pstSensorListener);
				return 1;
			}

			nRet = sensor_listener_stop(g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] Support API sensor_listener_stop failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT);
				sensor_destroy_listener(g_pstSensorListener);
				return 1;
			}

			nRet = sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] Support API sensor_listener_set_option is failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				sensor_destroy_listener(g_pstSensorListener);
				return 1;
			}

			nRet = sensor_destroy_listener(g_pstSensorListener);
			if ( nRet != SENSOR_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] Support API sensor_destroy_listener failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
		}
	}

	return 0;
}
//& purpose: To check whether sensor is wake up
//& type: auto
/**
* @testcase                      ITc_sensor_is_wake_up_p
* @type                             auto
* @author                            SRID(shilpa.j)
* @reviewer                            SRID(parshant.v)
* @since_tizen                      3.0
* @description                     To check whether sensor is wake up
* @scenario                            Create the sensor handle\n
*                                          Check whether sensor is wake up
* @apicovered                     sensor_is_wake_up
* @passcase                            When sensor_is_wake_up is successful
* @failcase                            If target API sensor_is_wake_up fails or any precondition API fails
* @precondition                     Sensor handle must be created
* @postcondition              NA
*/
int ITc_sensor_is_wake_up_p(void)
{
	START_TEST;

	for(enum_counter=0; enum_counter<enum_size; enum_counter++)
	{
		feature_check_e eFeatureCheck = SensorCheckFeature(stSensor[enum_counter].eSensorType, stSensor[enum_counter].szFeature);
		if(eFeatureCheck == FEATURE_MISMATCH )
		{
			return 1;
		}
		else if(eFeatureCheck == FEATURE_UNSUPPORTED)
		{
			continue;
		}
		else if(eFeatureCheck == FEATURE_SUPPORTED)
		{
			int nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			if(nRet != SENSOR_ERROR_NONE)
			{
				FPRINTF("[Line : %d][%s] sensor_get_default_sensor failed for sensor%s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");
			//Since the out param bIsWakeup is of type bool we cannot cannot check for out param since it can be true or false
			bool bIsWakeup = false;

			//Target API
			nRet = sensor_is_wake_up(g_pstSensorHandle, &bIsWakeup);
			if(nRet != SENSOR_ERROR_NONE)
			{
				FPRINTF("[Line : %d][%s] sensor_is_wake_up failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
		}
	}

	return 0;
}

//& purpose: To set an attribute to control the behavior of a sensor listener
//& type: auto
/**
* @testcase         ITc_sensor_listener_set_attribute_int_p
* @type             auto
* @author           SRID(shilpa.j)
* @reviewer         SRID(parshant.v)
* @since_tizen      3.0
* @description      To set an attribute to control the behavior of a sensor listener.
* @scenario         Get the listener handle\n
*                   set an attribute ofthe sensor listener
* @apicovered       sensor_listener_set_attribute_int
* @passcase         When sensor_listener_set_attribute_int is successful
* @failcase         If target API sensor_listener_set_attribute_int fails or any precondition API fails
* @precondition     Sensor handle must be created
* @postcondition    NA
*/
int ITc_sensor_listener_set_attribute_int_p(void)
{
	START_TEST;
	int nValue = 1;

	sensor_attribute_e eSensorAttribute[] =
	{
		SENSOR_ATTRIBUTE_AXIS_ORIENTATION,
		SENSOR_ATTRIBUTE_PAUSE_POLICY
	};
	int enum2_size = sizeof(eSensorAttribute) / sizeof(eSensorAttribute[0]);
	int enum2_counter = 0;

	for(enum_counter=0; enum_counter<enum_size; enum_counter++)
	{
		feature_check_e eFeatureCheck = SensorCheckFeature(stSensor[enum_counter].eSensorType, stSensor[enum_counter].szFeature);
		if(eFeatureCheck == FEATURE_MISMATCH)
		{
			 return 1;
		}
		else if(eFeatureCheck == FEATURE_UNSUPPORTED)
		{
			continue;
		}
		else if(eFeatureCheck == FEATURE_SUPPORTED)
		{
			int nRet = sensor_get_default_sensor(stSensor[enum_counter].eSensorType, &g_pstSensorHandle);
			if(nRet != SENSOR_ERROR_NONE)
			{
				FPRINTF("[Line : %d][%s] sensor_get_default_sensor failed for sensor%s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");

			nRet = sensor_create_listener(g_pstSensorHandle, &g_pstSensorListener);
			if(nRet != SENSOR_ERROR_NONE)
			{
				FPRINTF("[Line : %d][%s] Support API sensor_create_listener failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
			if(g_pstSensorListener == NULL)
			{
				FPRINTF("[Line : %d][%s] Support API sensor_create_listener failed to create listener of sensor %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType));
				return 1;
			}

			for(enum2_counter=0;enum2_counter<enum2_size;enum2_counter++)
			{
				// Target API
				nRet = sensor_listener_set_attribute_int(g_pstSensorListener, eSensorAttribute[enum2_counter],nValue);
				if(nRet != SENSOR_ERROR_NONE)
				{
					FPRINTF("[Line : %d][%s] sensor_listener_set_option failed for sensor %s and option %s, error returned = %s\\n",	__LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorAttributeOption(eSensorAttribute[enum2_counter]), SensorsGetError(nRet));
					sensor_destroy_listener(g_pstSensorListener);
					return 1;
				}
			}

			nRet = sensor_destroy_listener(g_pstSensorListener);
			if(nRet != SENSOR_ERROR_NONE)
			{
				FPRINTF("[Line : %d][%s] Support API sensor_destroy_listener failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(stSensor[enum_counter].eSensorType), SensorsGetError(nRet));
				return 1;
			}
		}
	}

	return 0;
}

//& purpose: Checks whether a given sensor URI is available on a device
//& type: auto
/**
* @testcase         ITc_sensor_sensor_is_supported_by_uri_p
* @type             auto
* @author           SRID(shilpa.j)
* @reviewer         SRID(nibha.sharma)
* @since_tizen      4.0
* @description      Checks whether a given sensor URI is available on a device.
* @scenario         calls sensor_is_supported_by_uri to check whether a given.
                    sensor URI is available on a device*
* @apicovered       sensor_is_supported_by_uri
* @passcase         When sensor_is_supported_by_uri is successful
* @failcase         If target API sensor_is_supported_by_uri fails or any precondition API fails
* @precondition     NA
* @postcondition    NA
*/
int ITc_sensor_sensor_is_supported_by_uri_p(void)
{
	START_TEST;
	bool bsupport = false;

	for(enum_counter=0; enum_counter<nUriTypeSize; enum_counter++ )
	{
		// Target API
		int nRet = sensor_is_supported_by_uri(stUriTypes[enum_counter],&bsupport);
		if ( nRet != SENSOR_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] sensor_is_supported_by_uri failed for uri %s, error returned = %s\\n",	__LINE__, API_NAMESPACE, stUriTypes[enum_counter], SensorsGetError(nRet));
			return 1;
		}
	}

	return 0;
}


//& purpose: Gets a specific sensor handle
//& type: auto
/**
* @testcase         ITc_sensor_sensor_is_supported_by_uri_p
* @type             auto
* @author           SRID(shilpa.j)
* @reviewer         SRID(nibha.sharma)
* @since_tizen      4.0
* @description      Gets a specific sensor handle.
* @scenario         calls sensor_get_default_sensor_by_uri to get a specific sensor handle
* @apicovered       sensor_get_default_sensor_by_uri
* @passcase         When sensor_get_default_sensor_by_uri is successful
* @failcase         If target API sensor_get_default_sensor_by_uri fails or any precondition API fails
* @precondition     NA
* @postcondition    NA
*/
int ITc_sensor_get_default_sensor_by_uri_p(void)
{
	START_TEST;

	for(enum_counter=0; enum_counter<nUriTypeSize; enum_counter++)
	{
		sensor_h hSensor;
		// Target API
		int nRet = sensor_get_default_sensor_by_uri(stUriTypes[enum_counter],&hSensor);

		if(nRet == SENSOR_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] sensor_get_default_sensor_by_uri is not supported for uri  %s, error returned = %s\\n", __LINE__, API_NAMESPACE,stUriTypes[enum_counter], SensorsGetError(nRet));
		}
		else if(nRet != SENSOR_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] sensor_get_default_sensor_by_uri failed for uri  %s, error returned = %s\\n", __LINE__, API_NAMESPACE,stUriTypes[enum_counter], SensorsGetError(nRet));
			return 1;
		}
		else
		{
			if(hSensor == NULL)
			{
				FPRINTF("[Line : %d][%s] sensor_get_default_sensor_by_uri failed for uri  %s, NULL value returned = %s\\n", __LINE__, API_NAMESPACE,stUriTypes[enum_counter], SensorsGetError(nRet));
				return 1;
			}
		}
	}

	return 0;
}

//& purpose: Gets a sensor list
//& type: auto
/**
* @testcase         ITc_sensor_get_sensor_list_by_uri_p
* @type             auto
* @author           SRID(shilpa.j)
* @reviewer         SRID(nibha.sharma)
* @since_tizen      4.0
* @description      Gets a sensor list.
* @scenario         calls sensor_get_sensor_list_by_uri to get sensor list
* @apicovered       sensor_get_sensor_list_by_uri
* @passcase         When sensor_get_sensor_list_by_uri is successful
* @failcase         If target API sensor_get_sensor_list_by_uri fails or any precondition API fails
* @precondition     NA
* @postcondition    NA
*/
int ITc_sensor_get_sensor_list_by_uri_p(void)
{
	START_TEST;

	sensor_h *hsenlist;
	int count;

	for ( enum_counter=0; enum_counter<nUriTypeSize; enum_counter++)
	{
		// Target API
		int nRet = sensor_get_sensor_list_by_uri(stUriTypes[enum_counter], &hsenlist, &count);

		if(nRet == SENSOR_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] sensor_get_sensor_list_by_uri is not supported for uri  %s, error returned = %s\\n", __LINE__, API_NAMESPACE,stUriTypes[enum_counter], SensorsGetError(nRet));
		}
		else if(nRet != SENSOR_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] sensor_get_sensor_list_by_uri failed for uri  %s, error returned = %s\\n", __LINE__, API_NAMESPACE,stUriTypes[enum_counter], SensorsGetError(nRet));
			return 1;
		}

		if(hsenlist == NULL)
		{
			FPRINTF("[Line : %d][%s] sensor_get_sensor_list_by_uri failed for uri  %s, NULL value returned = %s\\n", __LINE__, API_NAMESPACE,stUriTypes[enum_counter], SensorsGetError(nRet));
			return 1;
		}
	}

	return 0;
}

//& purpose:Gets the uri of the sensor
//& type: auto
/**
* @testcase         ITc_sensor_get_uri_p
* @type             auto
* @author           SRID(shilpa.j)
* @reviewer         SRID(nibha.sharma)
* @since_tizen      4.0
* @description      Gets the uri of the sensor.
* @scenario         calls sensor_get_uri to get uri of the sensor
* @apicovered       sensor_get_uri
* @passcase         When sensor_get_uri is successful
* @failcase         If target API sensor_get_uri fails or any precondition API fails
* @precondition     NA
* @postcondition    NA
*/
int ITc_sensor_get_uri_p(void)
{
	START_TEST;
	char *pszUri;

	for ( enum_counter=0; enum_counter<nUriTypeSize; enum_counter++)
	{
		sensor_h hSensor;

		int nRet = sensor_get_default_sensor_by_uri(stUriTypes[enum_counter],&hSensor);

		if ( nRet == SENSOR_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] sensor_get_sensor_list_by_uri is not supported for uri  %s, error returned = %s\\n", __LINE__, API_NAMESPACE,stUriTypes[enum_counter], SensorsGetError(nRet));
		}
		else if(nRet != SENSOR_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] sensor_get_sensor_list_by_uri failed for uri  %s, error returned = %s\\n", __LINE__, API_NAMESPACE,stUriTypes[enum_counter], SensorsGetError(nRet));
			return 1;
		}
		else
		{
			if(hSensor == NULL)
			{
				FPRINTF("[Line : %d][%s] sensor_get_default_sensor_by_uri failed for uri  %s, NULL handle value returned = %s\\n", __LINE__, API_NAMESPACE,stUriTypes[enum_counter], SensorsGetError(nRet));
				return 1;
			}

			// Target API
			nRet = sensor_get_uri(hSensor, &pszUri);

			if(nRet == SENSOR_ERROR_NOT_SUPPORTED)
			{
				FPRINTF("[Line : %d][%s] sensor_get_uri is not supported for uri  %s, error returned = %s\\n", __LINE__, API_NAMESPACE,stUriTypes[enum_counter], SensorsGetError(nRet));
			}
			else if(nRet != SENSOR_ERROR_NONE)
			{
				FPRINTF("[Line : %d][%s] sensor_get_uri failed for uri  %s, error returned = %s\\n", __LINE__, API_NAMESPACE,stUriTypes[enum_counter], SensorsGetError(nRet));
				return 1;
			}
			else
			{
				if(pszUri == NULL)
				{
					FPRINTF("[Line : %d][%s] sensor_get_uri failed for uri  %s, NULL value returned = %s\\n", __LINE__, API_NAMESPACE,stUriTypes[enum_counter], SensorsGetError(nRet));
					return 1;
				}
			}
		}
	}

	return 0;
}

//& purpose: To register and unregister a callback function to be invoked when SENSOR_HRM_LED_GREEN_BATCH sensor event occurs.
//& type: auto
/**
* @testcase 			ITc_sensor_listener_set_unset_events_cb_led_green_batch_p
* @type 			auto
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @since_tizen 		5.5
* @description			To register and un-register a callback function to be invoked when SENSOR_HRM_LED_GREEN_BATCH sensor event occurs.
* @scenario			Get the handle to the Sensor\n
*				Get the listener handle\n
*				Register the callback function\n
*				Check the user data received in callback function
* @apicovered			sensor_listener_set_events_cb,sensor_listener_unset_events_cb
* @passcase			When sensor_listener_set_events_cb and sensor_listener_unset_events_cb is successful
* @failcase			If target API sensor_listener_set_events_cb fails or callback or any precondition API fails
* @precondition		Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_listener_set_unset_events_cb_led_green_batch_p(void)
{
	START_TEST;

	int nRet = SENSOR_ERROR_NONE;
	SensorFeature stSensorBatch = {SENSOR_HRM_LED_GREEN_BATCH, "http://tizen.org/feature/sensor.heart_rate_monitor.led_green.batch"};

	feature_check_e eFeatureCheck = SensorCheckFeature(stSensorBatch.eSensorType, stSensorBatch.szFeature);
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
		int nSensorTimeoutId = 0;
		int nTimeOutCB = 30000;

		nRet = sensor_get_default_sensor(stSensorBatch.eSensorType, &g_pstSensorHandle);
		PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_get_default_sensor", SensorsGetError(nRet));
		CHECK_HANDLE(g_pstSensorHandle, "sensor_get_default_sensor");

		nRet = sensor_create_listener(g_pstSensorHandle, &g_pstSensorListener);
		PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_create_listener", SensorsGetError(nRet));
		CHECK_HANDLE(g_pstSensorListener, "sensor_create_listener");

		nRet = sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_ALWAYS_ON);
		PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_listener_set_option", SensorsGetError(nRet), sensor_destroy_listener(g_pstSensorListener));

		usleep(200);
		g_bSensorEventCallback = false;

		// Target API
		nRet = sensor_listener_set_events_cb(g_pstSensorListener, SensorEventCallback, NULL);
		PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_listener_set_events_cb", SensorsGetError(nRet), sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT); sensor_destroy_listener(g_pstSensorListener));

		nRet = sensor_listener_start(g_pstSensorListener);
		PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_listener_start", SensorsGetError(nRet), sensor_listener_unset_events_cb(g_pstSensorListener); sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT); sensor_destroy_listener(g_pstSensorListener));

		RUN_POLLING_LOOP;

		if ( !g_bSensorEventCallback )
		{
			FPRINTF("[Line : %d][%s] sensor_listener_set_events_cb failed to invoke callback\\n", __LINE__, API_NAMESPACE);
			sensor_listener_stop(g_pstSensorListener);
			sensor_listener_unset_events_cb(g_pstSensorListener);
			sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT);
			sensor_destroy_listener(g_pstSensorListener);
			return 1;
		}

		nRet = sensor_listener_stop(g_pstSensorListener);
		PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_listener_stop", SensorsGetError(nRet), sensor_listener_unset_events_cb(g_pstSensorListener); sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT); sensor_destroy_listener(g_pstSensorListener));

		g_bSensorEventCallback = false;

		// Target API
		nRet = sensor_listener_unset_events_cb(g_pstSensorListener);
		PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_listener_unset_events_cb", SensorsGetError(nRet), sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT); sensor_destroy_listener(g_pstSensorListener));

		nRet = sensor_listener_start(g_pstSensorListener);
		PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_listener_start", SensorsGetError(nRet), sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT); sensor_destroy_listener(g_pstSensorListener));

		RUN_POLLING_LOOP;

		if ( g_bSensorEventCallback )
		{
			FPRINTF("[Line : %d][%s] sensor_listener_unset_events_cb failed to stop callback invocation\\n", __LINE__, API_NAMESPACE);
			sensor_listener_stop(g_pstSensorListener);
			sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT);
			sensor_destroy_listener(g_pstSensorListener);
			return 1;
		}

		nRet = sensor_listener_stop(g_pstSensorListener);
		PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_listener_stop", SensorsGetError(nRet), sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT); sensor_destroy_listener(g_pstSensorListener));

		nRet = sensor_listener_set_option(g_pstSensorListener, SENSOR_OPTION_DEFAULT);
		PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_listener_set_option", SensorsGetError(nRet));

		nRet = sensor_destroy_listener(g_pstSensorListener);
		PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_destroy_listener", SensorsGetError(nRet));
	}
	return 0;
}
/** @} */
/** @} */
