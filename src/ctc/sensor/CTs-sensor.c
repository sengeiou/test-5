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
#include "CTs-sensor-common.h"

/** @addtogroup ctc-sensor
* @ingroup		ctc
* @{
*/

//& set: Sensor

/**
* @function 		CTs_sensor_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_sensor_startup(void)
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
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Sensor_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function 		CTs_sensor_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_sensor_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Sensor_p\\n", __LINE__, API_NAMESPACE);
#endif
	g_hSensor = NULL;
	return;
}

/**
* @function			Sensor_event_cb
* @description 		Called when an sensor event occurs. 
* @param	[IN]	g_hSensor		[The sensor handle.] 
* @param	[IN]	pEvent			[The event information.]
* @param	[IN]	pUserdata		[The user data passed from the callback registration function.]
* @return 			NA
*/
static void Sensor_event_cb (sensor_h g_hSensor, sensor_event_s *pEvent,  void *pUserdata)
{
	static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);		
}

/** @addtogroup	ctc-sensor-testcases
* @brief 		Integration testcases for module sensor
* @ingroup		ctc-sensor
* @{
*/

//& purpose: Check whether the accelerometer sensor is supported or not 
//& type: auto
/**
* @testcase			CTc_Sensor_SensorIsSupported_acceleration_p
* @since_tizen		2.3
* @author			SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type  			auto
* @scenario			Check if acceleration sensor is supported\n
* 					Gets Acceleration sensor handle\n
* 					Creates a sensor handle\n
* 					Registers a callback function to be invoked when a accelerometer  event occurs\n
*                   Starts a sensor server for a given sensor handle and sensor type\n
* 					Stops a sensor server for a given sensor handle and type\n
*                   Unregisters the accelerometer callback function\n
* 					destroy a sensor handle
* @apicovered		sensor_is_supported, sensor_get_default_sensor, sensor_create_listener, sensor_listener_set_event_cb, sensor_listener_start, sensor_listener_unset_event_cb, sensor_listener_stop, sensor_destroy_listener
* @passcase			covered API should return zero success value and and accelerometer sensor must be supported in device.
* @failcase			covered API returns negative error value 
* @precondition		Shake the device
* @postcondition	NA
*/
int CTc_Sensor_SensorIsSupported_acceleration_p(void)
{
	START_TEST;
	
	g_hSensor=NULL; 
	g_listener=NULL;
	int nRet = SENSOR_ERROR_NONE;
	unsigned int nIntervalms =0;

	IS_FEATURE_SUPPORTED(SENSOR_ACCELEROMETER_FEATURE, g_bIsSupportedSensor, API_NAMESPACE);
	if ( !g_bIsSupportedSensor )
	{
		FPRINTF("[Line : %d][%s] Device doesn't Support Accelerometer\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	if ( SensorCheckSupport(SENSOR_ACCELEROMETER) == false )
	{
		return 1;
	}

	if ( SensorGetDefaultSensor(SENSOR_ACCELEROMETER) == false )
	{
		return 1;
	}

	if ( SensorCreate() == false )
	{
		return 1;
	}

	nIntervalms = MIN_INTERVAL[ACCELERATION];

	nRet = sensor_listener_set_event_cb(g_listener,  nIntervalms, Sensor_event_cb, NULL);
	if ( nRet != SENSOR_ERROR_NONE )
	{   
		SensorApiErrorInfo("sensor_listener_set_event_cb", nRet);
		SensorDestroy();
		return 1;
	}

	if ( SensorIsStart() == false )
	{
		SensorUnsetcb();
		SensorDestroy();
		return 1;
	}

	if ( SensorStop() == false )
	{
		SensorUnsetcb();
		SensorDestroy();
		return 1;
	}

	if ( SensorUnsetcb() == false )
	{
		SensorDestroy();
		return 1;
	}

	if ( SensorDestroy() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Check whether the Magnetic sensor is supported or not 
//& type: auto
/**
* @testcase			CTc_Sensor_SensorIsSupported_Magnetic_p
* @since_tizen		2.3
* @author			SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type  			auto
* @scenario			Check if Magnetic sensor is supported\n
* 					Gets Magnetic sensor handle\n
* 					Creates a sensor handle\n
* 					Registers a callback function to be invoked when a Magnetic  event occurs\n
*                   Starts a sensor server for a given sensor handle and sensor type\n
* 					Stops a sensor server for a given sensor handle and type\n
*                   Unregisters the accelerometer callback function\n
* 					destroy a sensor handle
* @apicovered		sensor_is_supported, sensor_get_default_sensor, sensor_create_listener, sensor_listener_set_event_cb, sensor_listener_start, sensor_listener_unset_event_cb, sensor_listener_stop, sensor_destroy_listener
* @passcase			covered API should return zero success value and and Magnetic sensor must be supported in device.
* @failcase			covered API returns negative error value 
* @precondition		NA
* @postcondition	NA 
*/
int CTc_Sensor_SensorIsSupported_Magnetic_p(void)
{
	START_TEST;

	g_hSensor=NULL;
	g_listener=NULL;
	int nRet = SENSOR_ERROR_NONE;
	unsigned int nIntervalms =0;

	IS_FEATURE_SUPPORTED(SENSOR_MAGNETIC_FEATURE, g_bIsSupportedSensor, API_NAMESPACE);
	if ( !g_bIsSupportedSensor )
	{
		FPRINTF("[Line : %d][%s] Device doesn't Support Magnetometer\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	if ( SensorCheckSupport(SENSOR_MAGNETIC) == false )
	{
		return 1;
	}

	if ( SensorGetDefaultSensor(SENSOR_MAGNETIC) == false )
	{
		return 1;
	}

	if ( SensorCreate() == false )
	{
		return 1;
	}

	nIntervalms = MIN_INTERVAL[MAGNETIC];	
	nRet =  sensor_listener_set_event_cb(g_listener,  nIntervalms, Sensor_event_cb, NULL);

	if ( nRet != SENSOR_ERROR_NONE )
	{   
		SensorApiErrorInfo("sensor_listener_set_event_cb", nRet);
		SensorDestroy();
		return 1;
	}

	if ( SensorIsStart() == false )
	{
		SensorUnsetcb();
		SensorDestroy();
		return 1;
	}

	if ( SensorStop() == false )
	{
		SensorUnsetcb();
		SensorDestroy();
		return 1;
	}

	if ( SensorUnsetcb() == false )
	{
		SensorDestroy();
		return 1;
	}

	if ( SensorDestroy() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Check whether the light sensor is supported or not 
//& type: auto
/**
* @testcase			CTc_Sensor_SensorIsSupported_light_p
* @since_tizen		2.3
* @author			SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type  			auto
* @scenario			Check if light sensor is supported\n
* 					Gets Photometer(Light) sensor handle\n
* 					Creates a sensor handle\n
* 					Registers a callback function to be invoked when a light  event occurs\n
*                   Starts a sensor server for a given sensor handle and sensor type\n
* 					Stops a sensor server for a given sensor handle and type\n
*                   Unregisters the accelerometer callback function\n
* 					destroy a sensor handle
* @apicovered		sensor_is_supported, sensor_get_default_sensor, sensor_create_listener, sensor_listener_set_event_cb, sensor_listener_start, sensor_listener_unset_event_cb, sensor_listener_stop, sensor_destroy_listener
* @passcase			covered API should return zero success value and and light sensor must be supported in device.
* @failcase			covered API returns negative error value 
* @precondition		NA
* @postcondition	NA 
*/
int CTc_Sensor_SensorIsSupported_light_p(void)
{
	START_TEST;

	g_hSensor=NULL;
	g_listener=NULL;
	int nRet = SENSOR_ERROR_NONE;
	unsigned int nIntervalms =0;

	IS_FEATURE_SUPPORTED(SENSOR_LIGHT_FEATURE, g_bIsSupportedSensor, API_NAMESPACE);
	if ( !g_bIsSupportedSensor )
	{
		FPRINTF("[Line : %d][%s] Device doesn't Support Photometer\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	if ( SensorCheckSupport(SENSOR_LIGHT) == false )
	{
		return 1;
	}

	if ( SensorGetDefaultSensor(SENSOR_LIGHT) == false )
	{
		return 1;
	}

	if ( SensorCreate() == false )
	{
		return 1;
	}

	nIntervalms = MIN_INTERVAL[LIGHT];
	nRet =  sensor_listener_set_event_cb(g_listener,  nIntervalms, Sensor_event_cb, NULL);

	if ( nRet != SENSOR_ERROR_NONE )
	{   
		SensorApiErrorInfo("sensor_listener_set_event_cb", nRet);
		SensorDestroy();
		return 1;
	}

	if ( SensorIsStart() == false )
	{
		SensorUnsetcb();
		SensorDestroy();
		return 1;
	}

	if ( SensorStop() == false )
	{
		SensorUnsetcb();
		SensorDestroy();
		return 1;
	}

	if ( SensorUnsetcb() == false )
	{
		SensorDestroy();
		return 1;
	}

	if ( SensorDestroy() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Check whether the gyroscope sensor is supported or not 
//& type: auto
/**
* @testcase			CTc_Sensor_SensorIsSupported_gyroscope_p
* @since_tizen		2.3
* @author			SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type  			auto
* @scenario			Check if gyroscope sensor is supported\n
* 					Gets gyroscope sensor handle\n
* 					Creates a sensor handle\n
* 					Registers a callback function to be invoked when a gyroscope  event occurs\n
*                   Starts a sensor server for a given sensor handle and sensor type\n
* 					Stops a sensor server for a given sensor handle and type\n
*                   Unregisters the accelerometer callback function\n
* 					destroy a sensor handle
* @apicovered		sensor_is_supported, sensor_get_default_sensor, sensor_create_listener, sensor_listener_set_event_cb, sensor_listener_start, sensor_listener_unset_event_cb, sensor_listener_stop, sensor_destroy_listener
* @passcase			covered API should return zero success value and and gyroscope sensor must be supported in device.
* @failcase			covered API returns negative error value 
* @precondition		Shake the device
* @postcondition	NA 
*/
int CTc_Sensor_SensorIsSupported_gyroscope_p(void)
{
	START_TEST;

	g_hSensor=NULL;
	g_listener=NULL;
	int nRet = SENSOR_ERROR_NONE;
	unsigned int nIntervalms =0;

	IS_FEATURE_SUPPORTED(SENSOR_GYROSCOPE_FEATURE, g_bIsSupportedSensor, API_NAMESPACE);
	if ( !g_bIsSupportedSensor )
	{
		FPRINTF("[Line : %d][%s] Device doesn't Support Gyroscope\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	if ( SensorCheckSupport(SENSOR_GYROSCOPE) == false )
	{
		return 1;
	}

	if ( SensorGetDefaultSensor(SENSOR_GYROSCOPE) == false )
	{
		return 1;
	}

	if ( SensorCreate() == false )
	{
		return 1;
	}

	nIntervalms = MIN_INTERVAL[GYRO];	
	nRet =  sensor_listener_set_event_cb(g_listener,  nIntervalms, Sensor_event_cb, NULL);
	if ( nRet != SENSOR_ERROR_NONE )
	{   
		SensorApiErrorInfo("sensor_listener_set_event_cb", nRet);
		SensorDestroy();
		return 1;
	}

	if ( SensorIsStart() == false )
	{
		SensorUnsetcb();
		SensorDestroy();
		return 1;
	}
	if ( SensorStop() == false )
	{
		SensorUnsetcb();
		SensorDestroy();
		return 1;
	}

	if ( SensorUnsetcb() == false )
	{
		SensorDestroy();
		return 1;
	}

	if ( SensorDestroy() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Check whether the Proximity sensor is supported or not 
//& type: auto
/**
* @testcase			CTc_Sensor_SensorIsSupported_Proximity_p
* @since_tizen		2.3
* @author			SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type  			auto
* @scenario			Check if Proximity sensor is supported\n
* 					Gets Proximity sensor handle\n
* 					Creates a sensor handle\n
* 					Registers a callback function to be invoked when a Proximity event occurs\n
*                   Starts a sensor server for a given sensor handle and sensor type\n
* 					Stops a sensor server for a given sensor handle and type\n
*                   Unregisters the accelerometer callback function\n
* 					destroy a sensor handle
* @apicovered		sensor_is_supported, sensor_get_default_sensor, sensor_create_listener, sensor_listener_set_event_cb, sensor_listener_start, sensor_listener_unset_event_cb, sensor_listener_stop, sensor_destroy_listener
* @passcase			covered API should return zero success value and and tilt Proximity must be supported in device.
* @failcase			covered API returns negative error value 
* @precondition		Proximity sensor detects how far is the user from the device and  detection range start from 4cm.
* @postcondition	NA 
*/
int CTc_Sensor_SensorIsSupported_Proximity_p(void)
{
	START_TEST;

	g_hSensor=NULL;
	g_listener=NULL;
	int nRet = SENSOR_ERROR_NONE;
	unsigned int nIntervalms =0;

	IS_FEATURE_SUPPORTED(SENSOR_PROXIMITY_FEATURE, g_bIsSupportedSensor, API_NAMESPACE);
	if ( !g_bIsSupportedSensor )
	{
		FPRINTF("[Line : %d][%s] Device doesn't Support Proximity\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	
	if ( SensorCheckSupport(SENSOR_PROXIMITY) == false )
	{
		return 1;
	}

	if ( SensorGetDefaultSensor(SENSOR_PROXIMITY) == false )
	{
		return 1;
	}

	if ( SensorCreate() == false )
	{
		return 1;
	}

	nIntervalms = MIN_INTERVAL[PROXIMITY];
	nRet = sensor_listener_set_event_cb(g_listener,  nIntervalms, Sensor_event_cb, NULL);
	if ( nRet != SENSOR_ERROR_NONE )
	{   
		SensorApiErrorInfo("sensor_listener_set_event_cb", nRet);
		SensorDestroy();
		return 1;
	}

	if ( SensorIsStart() == false )
	{
		SensorUnsetcb();
		SensorDestroy();
		return 1;
	}

	if ( SensorStop() == false )
	{
		SensorUnsetcb();
		SensorDestroy();
		return 1;
	}

	if ( SensorUnsetcb() == false )
	{
		SensorDestroy();
		return 1;
	}	

	if ( SensorDestroy() == false )
	{
		return 1;
	}	
	return 0;
}

//& purpose: Check whether the gravity sensor is supported or not 
//& type: auto
/**
* @testcase			CTc_Sensor_SensorIsSupported_Gravity_p
* @since_tizen		2.3
* @author			SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type  			auto
* @scenario			Check if gravity sensor is supported\n
* 					Gets Gravity sensor handle\n
* 					Creates a sensor handle\n
* 					Registers a callback function to be invoked when a gravity  event occurs\n
*                   Starts a sensor server for a given sensor handle and sensor type\n
* 					Stops a sensor server for a given sensor handle and type\n
*                   Unregisters the gravity callback function\n
* 					destroy a sensor handle
* @apicovered		sensor_is_supported, sensor_get_default_sensor, sensor_create_listener, sensor_listener_set_event_cb, sensor_listener_start, sensor_listener_unset_event_cb, sensor_listener_stop, sensor_destroy_listener
* @passcase			covered API should return zero success value and and gravity sensor must be supported in device.
* @failcase			covered API returns negative error value 
* @precondition		NA
* @postcondition	NA 
*/
int CTc_Sensor_SensorIsSupported_Gravity_p(void)
{
	START_TEST;

	g_hSensor=NULL; 
	g_listener=NULL;
	int nRet = SENSOR_ERROR_NONE;
	unsigned int nIntervalms =0;

	IS_FEATURE_SUPPORTED(SENSOR_GRAVITY_FEATURE, g_bIsSupportedSensor, API_NAMESPACE);
	if ( !g_bIsSupportedSensor )
	{
		FPRINTF("[Line : %d][%s] Device doesn't Support Gravity\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	if ( SensorCheckSupport(SENSOR_GRAVITY) == false )
	{
		return 1;
	}

	if ( SensorGetDefaultSensor(SENSOR_GRAVITY) == false )
	{
		return 1;
	}

	if ( SensorCreate() == false )
	{
		return 1;
	}

	nIntervalms = MIN_INTERVAL[GRAVITY];

	nRet = sensor_listener_set_event_cb(g_listener,  nIntervalms, Sensor_event_cb, NULL);
	if ( nRet != SENSOR_ERROR_NONE )
	{   
		SensorApiErrorInfo("sensor_listener_set_event_cb", nRet);
		SensorDestroy();
		return 1;
	}

	if ( SensorIsStart() == false )
	{
		SensorUnsetcb();
		SensorDestroy();
		return 1;
	}

	if ( SensorStop() == false )
	{
		SensorUnsetcb();
		SensorDestroy();
		return 1;
	}

	if ( SensorUnsetcb() == false )
	{
		SensorDestroy();
		return 1;
	}

	if ( SensorDestroy() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Check whether the linear acceleration sensor is supported or not 
//& type: auto
/**
* @testcase			CTc_Sensor_SensorIsSupported_Linear_Acceleration_p
* @since_tizen		2.3
* @author			SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type  			auto
* @scenario			Check if linear acceleration sensor is supported\n
* 					Gets Linear Acceleration sensor handle\n
* 					Creates a sensor handle\n
* 					Registers a callback function to be invoked when a linear acceleration  event occurs\n
*                   Starts a sensor server for a given sensor handle and sensor type\n
* 					Stops a sensor server for a given sensor handle and type\n
*                   Unregisters the linear acceleration callback function\n
* 					destroy a sensor handle
* @apicovered		sensor_is_supported, sensor_get_default_sensor, sensor_create_listener, sensor_listener_set_event_cb, sensor_listener_start, sensor_listener_unset_event_cb, sensor_listener_stop, sensor_destroy_listener
* @passcase			covered API should return zero success value and and linear acceleration sensor must be supported in device.
* @failcase			covered API returns negative error value 
* @precondition		NA
* @postcondition	NA 
*/
int CTc_Sensor_SensorIsSupported_Linear_Acceleration_p(void)
{
	START_TEST;

	g_hSensor=NULL; 
	g_listener=NULL;
	int nRet = SENSOR_ERROR_NONE;
	unsigned int nIntervalms =0;

	IS_FEATURE_SUPPORTED(SENSOR_LINEAR_ACCELERATION_FEATURE, g_bIsSupportedSensor, API_NAMESPACE);
	if ( !g_bIsSupportedSensor )
	{
		FPRINTF("[Line : %d][%s] Device doesn't Support Linear Acceleration\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	if ( SensorCheckSupport(SENSOR_LINEAR_ACCELERATION) == false )
	{
		return 1;
	}

	if ( SensorGetDefaultSensor(SENSOR_LINEAR_ACCELERATION) == false )
	{
		return 1;
	}

	if ( SensorCreate() == false )
	{
		return 1;
	}

	nIntervalms = MIN_INTERVAL[LINEAR_ACCELERATION];

	nRet = sensor_listener_set_event_cb(g_listener,  nIntervalms, Sensor_event_cb, NULL);
	if ( nRet != SENSOR_ERROR_NONE )
	{   
		SensorApiErrorInfo("sensor_listener_set_event_cb", nRet);
		SensorDestroy();
		return 1;
	}

	if ( SensorIsStart() == false )
	{
		SensorUnsetcb();
		SensorDestroy();
		return 1;
	}

	if ( SensorStop() == false )
	{
		SensorUnsetcb();
		SensorDestroy();
		return 1;
	}

	if ( SensorUnsetcb() == false )
	{
		SensorDestroy();
		return 1;
	}

	if ( SensorDestroy() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Check whether the orientation sensor is supported or not 
//& type: auto
/**
* @testcase			CTc_Sensor_SensorIsSupported_Orientation_p
* @since_tizen		2.3
* @author			SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type  			auto
* @scenario			Check if orientation sensor is supported\n
* 					Gets Orientation sensor handle\n
* 					Creates a sensor handle\n
* 					Registers a callback function to be invoked when a orientation event occurs\n
*                   Starts a sensor server for a given sensor handle and sensor type\n
* 					Stops a sensor server for a given sensor handle and type\n
*                   Unregisters the orientation callback function\n
* 					destroy a sensor handle
* @apicovered		sensor_is_supported, sensor_get_default_sensor, sensor_create_listener, sensor_listener_set_event_cb, sensor_listener_start, sensor_listener_unset_event_cb, sensor_listener_stop, sensor_destroy_listener
* @passcase			covered API should return zero success value and and orientation sensor must be supported in device.
* @failcase			covered API returns negative error value 
* @precondition		NA
* @postcondition	NA 
*/
int CTc_Sensor_SensorIsSupported_Orientation_p(void)
{
	START_TEST;

	g_hSensor=NULL; 
	g_listener=NULL;
	int nRet = SENSOR_ERROR_NONE;
	unsigned int nIntervalms =0;

	IS_FEATURE_SUPPORTED(SENSOR_ORIENTATION_FEATURE, g_bIsSupportedSensor, API_NAMESPACE);
	if ( !g_bIsSupportedSensor )
	{
		FPRINTF("[Line : %d][%s] Device doesn't Support Orientation\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	if ( SensorCheckSupport(SENSOR_ORIENTATION) == false )
	{
		return 1;
	}

	if ( SensorGetDefaultSensor(SENSOR_ORIENTATION) == false )
	{
		return 1;
	}

	if ( SensorCreate() == false )
	{
		return 1;
	}

	nIntervalms = MIN_INTERVAL[ORIENTATION];

	nRet = sensor_listener_set_event_cb(g_listener,  nIntervalms, Sensor_event_cb, NULL);
	if ( nRet != SENSOR_ERROR_NONE )
	{   
		SensorApiErrorInfo("sensor_listener_set_event_cb", nRet);
		SensorDestroy();
		return 1;
	}

	if ( SensorIsStart() == false )
	{
		SensorUnsetcb();
		SensorDestroy();
		return 1;
	}

	if ( SensorStop() == false )
	{
		SensorUnsetcb();
		SensorDestroy();
		return 1;
	}

	if ( SensorUnsetcb() == false )
	{
		SensorDestroy();
		return 1;
	}

	if ( SensorDestroy() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Check whether the rotation vector sensor is supported or not 
//& type: auto
/**
* @testcase			CTc_Sensor_SensorIsSupported_Rotation_Vector_p
* @since_tizen		2.3
* @author			SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type  			auto
* @scenario			Check if rotation vector sensor is supported\n
* 					Gets Rotation Vector sensor handle\n
* 					Creates a sensor handle\n
* 					Registers a callback function to be invoked when a Rotation Vector  event occurs\n
*                   Starts a sensor server for a given sensor handle and sensor type\n
* 					Stops a sensor server for a given sensor handle and type\n
*                   Unregisters the Rotation vector callback function\n
* 					destroy a sensor handle
* @apicovered		sensor_is_supported, sensor_get_default_sensor, sensor_create_listener, sensor_listener_set_event_cb, sensor_listener_start, sensor_listener_unset_event_cb, sensor_listener_stop, sensor_destroy_listener
* @passcase			covered API should return zero success value and and Rotation Vector sensor must be supported in device.
* @failcase			covered API returns negative error value 
* @precondition		NA
* @postcondition	NA
*/
int CTc_Sensor_SensorIsSupported_Rotation_Vector_p(void)
{
	START_TEST;

	g_hSensor=NULL; 
	g_listener=NULL;
	int nRet = SENSOR_ERROR_NONE;
	unsigned int nIntervalms =0;

	IS_FEATURE_SUPPORTED(SENSOR_ROTATION_VECTOR_FEATURE, g_bIsSupportedSensor, API_NAMESPACE);
	if ( !g_bIsSupportedSensor )
	{
		FPRINTF("[Line : %d][%s] Device doesn't Support Rotation Vector\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	if ( SensorCheckSupport(SENSOR_ROTATION_VECTOR) == false )
	{
		return 1;
	}

	if ( SensorGetDefaultSensor(SENSOR_ROTATION_VECTOR) == false )
	{
		return 1;
	}

	if ( SensorCreate() == false )
	{
		return 1;
	}

	nIntervalms = MIN_INTERVAL[ROTATION_VECTOR];

	nRet = sensor_listener_set_event_cb(g_listener,  nIntervalms, Sensor_event_cb, NULL);
	if ( nRet != SENSOR_ERROR_NONE )
	{   
		SensorApiErrorInfo("sensor_listener_set_event_cb", nRet);
		SensorDestroy();
		return 1;
	}

	if ( SensorIsStart() == false )
	{
		SensorUnsetcb();
		SensorDestroy();
		return 1;
	}

	if ( SensorStop() == false )
	{
		SensorUnsetcb();
		SensorDestroy();
		return 1;
	}

	if ( SensorUnsetcb() == false )
	{
		SensorDestroy();
		return 1;
	}

	if ( SensorDestroy() == false )
	{
		return 1;
	}
	return 0;
}

/** @} */ //end of ctc-sensor
/** @} */ //end of ctc-sensor-testcases