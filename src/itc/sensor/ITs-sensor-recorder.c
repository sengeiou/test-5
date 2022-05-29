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

static bool sensor_recorder_supported[30]; //This needs to be increased, with addition of new sensors in "Sensor[]".
static bool g_bCallbackHit = false;
static int g_nRet;
static bool g_bStatus;
static bool g_bIsFeatureSupported = false;


SensorFeature Sensor[] = {	
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
	{SENSOR_HUMAN_SLEEP_MONITOR, "http://tizen.org/feature/sensor.sleep_monitor"},
	{SENSOR_HUMAN_SLEEP_DETECTOR, "http://tizen.org/feature/sensor.sleep_monitor"},
	{SENSOR_HRM_BATCH, "http://tizen.org/feature/sensor.heart_rate_monitor.batch"},
	{SENSOR_HRM_LED_GREEN_BATCH, "http://tizen.org/feature/sensor.heart_rate_monitor.led_green.batch"},
	{SENSOR_ORIENTATION, "http://tizen.org/feature/sensor.orientation"},
	{SENSOR_GYROSCOPE_ORIENTATION, "http://tizen.org/feature/sensor.gyroscope_orientation"},
	{SENSOR_GEOMAGNETIC_ORIENTATION, "http://tizen.org/feature/sensor.geomagnetic_orientation"}
};


/**
* @function			SensorRecorderDatacb
* @description		Called during sensor recorder read.
* @parameter[IN]	sensor_type_e
* @parameter[IN]	sensor_recorder_data_h
* @parameter[IN]	int
* @parameter[IN]	sensor_error_e
* @parameter[IN]	The user data passed from the callback registration function			
* @return			bool
*/
static bool SensorRecorderDatacb(sensor_type_e type, sensor_recorder_data_h data, int remains, sensor_error_e error, void *user_data)
{
	g_bCallbackHit = true;
	if (error != SENSOR_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] SensorRecorderSyncCb error = %d \\n", __LINE__, API_NAMESPACE,error);
	}
	
	if ( g_pSensorMainLoop )
	{
		g_main_loop_quit(g_pSensorMainLoop);
		g_main_loop_unref(g_pSensorMainLoop);
		g_pSensorMainLoop = NULL;
	}
	return true;
}

/**
* @function			SensorRecorderSyncCb
* @description		Called during sensor recorder read sync.
* @parameter[IN]	sensor_type_e
* @parameter[IN]	sensor_recorder_data_h
* @parameter[IN]	int
* @parameter[IN]	sensor_error_e
* @parameter[IN]	The user data passed from the callback registration function			
* @return			bool
*/
static bool SensorRecorderSyncCb(sensor_type_e type, sensor_recorder_data_h data, int remains, sensor_error_e error, void *user_data)
{
	g_bCallbackHit = true;

	if (error != SENSOR_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] SensorRecorderSyncCb error = %d \\n", __LINE__, API_NAMESPACE,error);
	}
	if ( g_pSensorMainLoop )
	{
		g_main_loop_quit(g_pSensorMainLoop);
		g_main_loop_unref(g_pSensorMainLoop);
		g_pSensorMainLoop = NULL;
	}

	return true;
}

/**
* @function			SensorRecorderReadSyncCbGetDouble
* @description		Called during sensor recorder read sync.
* @parameter[IN]	sensor_type_e
* @parameter[IN]	sensor_recorder_data_h
* @parameter[IN]	int
* @parameter[IN]	sensor_error_e
* @parameter[IN]	The user data passed from the callback registration function			
* @return			bool
*/
static bool SensorRecorderReadSyncCbGetDouble(sensor_type_e type, sensor_recorder_data_h data, int remains, sensor_error_e error, void *user_data)
{
	double val_double ;
	int nEnumCount;
	int arrSensorRecorderData[] = 
	{
		SENSOR_RECORDER_DATA_STEPS,
		SENSOR_RECORDER_DATA_WALK_STEPS,
		SENSOR_RECORDER_DATA_RUN_STEPS,
		SENSOR_RECORDER_DATA_DISTANCE,
		SENSOR_RECORDER_DATA_CALORIE,
		SENSOR_RECORDER_DATA_HEART_RATE,
		SENSOR_RECORDER_DATA_SLEEP_STATE,
		SENSOR_RECORDER_DATA_PRESSURE,
		SENSOR_RECORDER_DATA_MAX_PRESSURE,
		SENSOR_RECORDER_DATA_MIN_PRESSURE,
		SENSOR_RECORDER_DATA_AVERAGE_PRESSURE,
	};
	int nSensorRecorderTypeCount = sizeof(arrSensorRecorderData) / sizeof(arrSensorRecorderData[0]);
	
	g_bCallbackHit = true;
	
	if (error != SENSOR_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] SensorRecorderReadSyncCbGetDouble error = %d \\n", __LINE__, API_NAMESPACE,error);
	}

	if (type == SENSOR_HUMAN_PEDOMETER) 
	{
		for(nEnumCount = 0;nEnumCount < nSensorRecorderTypeCount;nEnumCount++ )
		{
			val_double = -1.0;
			g_nRet = sensor_recorder_data_get_double(data, arrSensorRecorderData[nEnumCount], &val_double);
			if(g_nRet != SENSOR_ERROR_NONE)
			{
				FPRINTF("[Line : %d][%s] sensor_recorder_data_get_double failed \\n", __LINE__, API_NAMESPACE);
				return false;
			}
			if(val_double == -1.0)
			{
				FPRINTF("[Line : %d][%s] sensor_recorder_data_get_double failed as val_double is incorrect \\n", __LINE__, API_NAMESPACE);
				g_bStatus = false;
				return false;
			}
		}
	}
	if ( g_pSensorMainLoop )
	{
		g_main_loop_quit(g_pSensorMainLoop);
		g_main_loop_unref(g_pSensorMainLoop);
		g_pSensorMainLoop = NULL;
	}

	return true;
}

/**
* @function			SensorRecorderReadSyncCbGetTime
* @description		Called during sensor recorder read sync.
* @parameter[IN]	sensor_type_e
* @parameter[IN]	sensor_recorder_data_h
* @parameter[IN]	int
* @parameter[IN]	sensor_error_e
* @parameter[IN]	The user data passed from the callback registration function			
* @return			bool
*/
static bool SensorRecorderReadSyncCbGetTime(sensor_type_e type, sensor_recorder_data_h data, int remains, sensor_error_e error, void *user_data)
{
	time_t start = time(NULL), end = time(NULL);
	g_bCallbackHit = true;
	if (error != SENSOR_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] SensorRecorderReadSyncCbGetTime error = %d \\n", __LINE__, API_NAMESPACE,error);
	}
	
	if (data == NULL)
	{
		FPRINTF("[Line : %d][%s] SensorRecorderReadSyncCbGetTime input data is NULL = %d \\n", __LINE__, API_NAMESPACE,error);
		g_bStatus = false;
		return false;
	}

	g_nRet = sensor_recorder_data_get_time(data, &start, &end);
	if(g_nRet != SENSOR_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] sensor_recorder_data_get_time failed \\n", __LINE__, API_NAMESPACE);
		return false;
	}
	if( (start == time(NULL)) || (end == time(NULL)) )
	{
		FPRINTF("[Line : %d][%s] sensor_recorder_data_get_time failed as time is incorrect \\n", __LINE__, API_NAMESPACE);
		g_bStatus = false;
		return false;
	}
	if ( g_pSensorMainLoop )
	{
		g_main_loop_quit(g_pSensorMainLoop);
		g_main_loop_unref(g_pSensorMainLoop);
		g_pSensorMainLoop = NULL;
	}

	return true;
}

/**
* @function			SensorRecorderReadSyncCbGetInt
* @description		Called during sensor recorder read sync.
* @parameter[IN]	sensor_type_e
* @parameter[IN]	sensor_recorder_data_h
* @parameter[IN]	int
* @parameter[IN]	sensor_error_e
* @parameter[IN]	The user data passed from the callback registration function			
* @return			bool
*/
static bool SensorRecorderReadSyncCbGetInt(sensor_type_e type, sensor_recorder_data_h data, int remains, sensor_error_e error, void *user_data)
{
	int val_int = -1;
	int nEnumCount;
	int arrSensorRecorderData[] = 
	{
		SENSOR_RECORDER_DATA_STEPS,
		SENSOR_RECORDER_DATA_WALK_STEPS,
		SENSOR_RECORDER_DATA_RUN_STEPS,
		SENSOR_RECORDER_DATA_DISTANCE,
		SENSOR_RECORDER_DATA_CALORIE,
		SENSOR_RECORDER_DATA_HEART_RATE,
		SENSOR_RECORDER_DATA_SLEEP_STATE,
		SENSOR_RECORDER_DATA_PRESSURE,
		SENSOR_RECORDER_DATA_MAX_PRESSURE,
		SENSOR_RECORDER_DATA_MIN_PRESSURE,
		SENSOR_RECORDER_DATA_AVERAGE_PRESSURE,
	};
	int nSensorRecorderTypeCount = sizeof(arrSensorRecorderData) / sizeof(arrSensorRecorderData[0]);
		
	g_bCallbackHit = true;
	if (error != SENSOR_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] SensorRecorderReadSyncCbGetInt error = %d \\n", __LINE__, API_NAMESPACE,error);
	}

	if (data == NULL)
	{
		FPRINTF("[Line : %d][%s] SensorRecorderReadSyncCbGetTime input data is NULL = %d \\n", __LINE__, API_NAMESPACE,error);
		g_bStatus = false;
		return false;
	}
	
	if (type == SENSOR_HUMAN_PEDOMETER)
	{
		for(nEnumCount = 0;nEnumCount < nSensorRecorderTypeCount;nEnumCount++ )
		{			
			val_int = -1;
			g_nRet = sensor_recorder_data_get_int(data, arrSensorRecorderData[nEnumCount], &val_int);
			if(g_nRet != SENSOR_ERROR_NONE)
			{
				FPRINTF("[Line : %d][%s] sensor_recorder_data_get_int failed \\n", __LINE__, API_NAMESPACE);
				return false;
			}
			if(val_int == -1)
			{
				FPRINTF("[Line : %d][%s] sensor_recorder_data_get_double failed as val_int is incorrect \\n", __LINE__, API_NAMESPACE);
				g_bStatus = false;
				return false;
			}
		}
	}

	if (type == SENSOR_HRM)
	{
		for(nEnumCount = 0;nEnumCount < nSensorRecorderTypeCount;nEnumCount++ )
		{
			val_int = -1;
			g_nRet = sensor_recorder_data_get_int(data, arrSensorRecorderData[nEnumCount], &val_int);
			if(g_nRet != SENSOR_ERROR_NONE)
			{
				FPRINTF("[Line : %d][%s] sensor_recorder_data_get_int failed \\n", __LINE__, API_NAMESPACE);
				return false;
			}
			if(val_int == -1)
			{
				FPRINTF("[Line : %d][%s] sensor_recorder_data_get_double failed as val_int is incorrect \\n", __LINE__, API_NAMESPACE);
				g_bStatus = false;
				return false;
			}
		}
	}

	if (type == SENSOR_HUMAN_SLEEP_MONITOR || type == SENSOR_HUMAN_SLEEP_DETECTOR)
	{
		for(nEnumCount = 0;nEnumCount < nSensorRecorderTypeCount;nEnumCount++ )
		{
			val_int = -1;
			g_nRet = sensor_recorder_data_get_int(data, arrSensorRecorderData[nEnumCount], &val_int);
			if(g_nRet != SENSOR_ERROR_NONE)
			{
				FPRINTF("[Line : %d][%s] sensor_recorder_data_get_int failed \\n", __LINE__, API_NAMESPACE);
				return false;
			}
			if(val_int == -1)
			{
				FPRINTF("[Line : %d][%s] sensor_recorder_data_get_double failed as val_int is incorrect \\n", __LINE__, API_NAMESPACE);
				g_bStatus = false;
				return false;
			}
		}
	}

	if ( g_pSensorMainLoop )
	{
		g_main_loop_quit(g_pSensorMainLoop);
		g_main_loop_unref(g_pSensorMainLoop);
		g_pSensorMainLoop = NULL;
	}

	return true;
}


/**
* @function 		ITs_sensor_recorder_startup
* @description	 	Called before each test, creates Sensors 
* @parameter		NA
* @return 			NA
*/ 
void ITs_sensor_recorder_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	int i;
	int enum_size = sizeof(Sensor) / sizeof(Sensor[0]);
	
	for ( i=0; i<enum_size; i++ )
	{
		bool bIsFeatureSupported = TCTCheckSystemInfoFeatureSupported(Sensor[i].szFeature, API_NAMESPACE);
		g_bIsFeatureSupported = g_bIsFeatureSupported | bIsFeatureSupported;
		
		// Target API
		int nRet = sensor_recorder_is_supported(Sensor[i].eSensorType, &sensor_recorder_supported[i]);
		if ( nRet != SENSOR_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] sensor_is_supported failed for sensor %s, error returned = %s\\n", __LINE__, API_NAMESPACE, SensorGetType(Sensor[i].eSensorType), SensorsGetError(nRet));
			return ;
		}
		
		if ( bIsFeatureSupported != sensor_recorder_supported[i] )
		{
			FPRINTF("[Line : %d][%s] sensor_is_supported return value (%s) mismatched with expected value (%s) for feature %s and sensor %s\\n", __LINE__, API_NAMESPACE, sensor_recorder_supported[i] ? "true": "false", bIsFeatureSupported ? "true": "false", Sensor[i].szFeature, SensorGetType(Sensor[i].eSensorType));
			return ;
		}
	}
	
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_sensor_recorder_startup\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		ITs_sensor_recorder_cleanup
* @description	 	Called after each test, destroys Sensors 
* @parameter		NA
* @return 			NA
*/ 
void ITs_sensor_recorder_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_sensor_recorder_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
	
	return;
}

/** @addtogroup itc-sensor-testcases
*  @brief 		Integration testcases for module sensor
*  @ingroup 	itc-sensor
*  @{
*/

//& purpose: 
//& type: auto
/**
* @testcase 			ITc_sensor_recorder_is_supported_p
* @type 				auto
* @author				SRID(asit.s)
* @reviewer				SRID(shobhit.v)
* @since_tizen 			3.0
* @description			checks supported features
* @scenario				call sensor_recorder_is_supported
* @apicovered			sensor_recorder_is_supported
* @passcase				When Target api is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_recorder_is_supported_p(void)
{
	START_TEST;
	int i;
	int sensor_count = sizeof(Sensor)/sizeof(Sensor[0]);
	int nRet;
	bool supported;	
	for (i = 0; i < sensor_count; ++i)
	{
		nRet = sensor_recorder_is_supported(Sensor[i].eSensorType,&supported);
		if ( false == g_bIsFeatureSupported && TIZEN_ERROR_NOT_SUPPORTED == nRet )
		{
			FPRINTF("[Line : %d][%s] Sensor Features not supported \\n", __LINE__, API_NAMESPACE);
			return 0;
		}

		PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_recorder_is_supported", SensorsGetError(nRet));
	}

	return 0;
}

//& purpose: 
//& type: auto
/**
* @testcase 			ITc_sensor_recorder_start_stop_p
* @type 				auto
* @author				SRID(asit.s)
* @reviewer				SRID(shobhit.v)
* @since_tizen 			3.0
* @description			start stop recorder
* @scenario				call sensor_recorder_start,sensor_recorder_stop
* @apicovered			sensor_recorder_start,sensor_recorder_stop
* @passcase				When Target api is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_recorder_start_stop_p(void)
{
	START_TEST;
	int i;
	int nRet;
	int sensor_count = sizeof(Sensor)/sizeof(Sensor[0]);
	for (i = 0; i < sensor_count; ++i)
	{
		if (!sensor_recorder_supported[i])
			continue;
		//Target API
		nRet = sensor_recorder_start(Sensor[i].eSensorType, NULL);
		if ( false == g_bIsFeatureSupported && TIZEN_ERROR_NOT_SUPPORTED == nRet )
		{
			FPRINTF("[Line : %d][%s] Sensor Features not supported \\n", __LINE__, API_NAMESPACE);
			return 0;
		}
		PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_recorder_start", SensorsGetError(nRet));

		//Target API
		nRet = sensor_recorder_stop(Sensor[i].eSensorType);
		PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_recorder_stop", SensorsGetError(nRet));
	}
	
	return 0;
}


//& purpose: 
//& type: auto
/**
* @testcase 			ITc_sensor_recorder_create_destroy_option_p
* @type 				auto
* @author				SRID(asit.s)
* @reviewer				SRID(shobhit.v)
* @since_tizen 			3.0
* @description			create and destroy recorder option
* @scenario				call sensor_recorder_create_option,sensor_recorder_destroy_option 
* @apicovered			sensor_recorder_create_option,sensor_recorder_destroy_option
* @passcase				When Target api is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_recorder_create_destroy_option_p(void)
{
	START_TEST;

	int nRet = SENSOR_ERROR_NONE;
	sensor_recorder_option_h option;

	//Target API
	nRet = sensor_recorder_create_option(&option);
	if ( false == g_bIsFeatureSupported && TIZEN_ERROR_NOT_SUPPORTED == nRet )
	{
		FPRINTF("[Line : %d][%s] Sensor Features not supported \\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_recorder_create_option", SensorsGetError(nRet));
	CHECK_HANDLE(option,"sensor_recorder_create_option");
	//Target API
	nRet = sensor_recorder_destroy_option(option);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_recorder_destroy_option", SensorsGetError(nRet));

	return 0;
}


//& purpose: 
//& type: auto
/**
* @testcase 			ITc_sensor_recorder_option_set_int_p
* @type 				auto
* @author				SRID(asit.s)
* @reviewer				SRID(shobhit.v)
* @since_tizen 			3.0
* @description			set int option
* @scenario				call sensor_recorder_create_option,sensor_recorder_option_set_int,sensor_recorder_destroy_option 
* @apicovered			sensor_recorder_create_option,sensor_recorder_option_set_int,sensor_recorder_destroy_option 
* @passcase				When Target api is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_recorder_option_set_int_p(void)
{
	START_TEST;

	sensor_recorder_option_h option;

	int nEnumCountOption;
	int nEnumCountInterval;
	int arrSensorRecorderOption[] = 
	{
		SENSOR_RECORDER_OPTION_RETENTION_PERIOD,
		SENSOR_RECORDER_OPTION_INTERVAL,
	};
	
	int arrSensorRecorderInterval[] = 
	{
		SENSOR_RECORDER_INTERVAL_10_MINUTES,
		SENSOR_RECORDER_INTERVAL_1_HOUR,
		SENSOR_RECORDER_INTERVAL_3_HOURS,
		SENSOR_RECORDER_INTERVAL_6_HOURS,
		SENSOR_RECORDER_INTERVAL_12_HOURS,
		SENSOR_RECORDER_INTERVAL_1_DAY,
	};
	
	int nSensorRecorderOptionCount = sizeof(arrSensorRecorderOption) / sizeof(arrSensorRecorderOption[0]);
	int nSensorRecorderIntervalCount = sizeof(arrSensorRecorderInterval) / sizeof(arrSensorRecorderInterval[0]);
	
	int nRet = sensor_recorder_create_option(&option);
	if ( false == g_bIsFeatureSupported && TIZEN_ERROR_NOT_SUPPORTED == nRet )
	{
		FPRINTF("[Line : %d][%s] Sensor Features not supported \\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_recorder_create_option", SensorsGetError(nRet));
	CHECK_HANDLE(option,"sensor_recorder_create_option");

	for(nEnumCountOption = 0;nEnumCountOption < nSensorRecorderOptionCount;nEnumCountOption++ )
	{
		for(nEnumCountInterval = 0;nEnumCountInterval < nSensorRecorderIntervalCount;nEnumCountInterval++ )
		{
			//Target API
			nRet = sensor_recorder_option_set_int(option, arrSensorRecorderOption[nEnumCountOption], arrSensorRecorderInterval[nEnumCountInterval]);
			PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_option_set_int", SensorsGetError(nRet),sensor_recorder_destroy_option(option));
		}
	}
	
	nRet = sensor_recorder_destroy_option(option);
	PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_recorder_destroy_option", SensorsGetError(nRet));

	return 0;
}


//& purpose: 
//& type: auto
/**
* @testcase 			ITc_sensor_recorder_create_destroy_query_p
* @type 				auto
* @author				SRID(asit.s)
* @reviewer				SRID(shobhit.v)
* @since_tizen 			3.0
* @description			create and destroy query
* @scenario				call sensor_recorder_create_query,sensor_recorder_destroy_query
* @apicovered			
* @passcase				When Target api is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_recorder_create_destroy_query_p(void)
{
	START_TEST;

	sensor_recorder_query_h query;

	//Target API
	int nRet = sensor_recorder_create_query(&query);
	if ( false == g_bIsFeatureSupported && TIZEN_ERROR_NOT_SUPPORTED == nRet )
	{
		FPRINTF("[Line : %d][%s] Sensor Features not supported \\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_recorder_create_query", SensorsGetError(nRet));
	CHECK_HANDLE(query,"sensor_recorder_create_query");
	//Target API
	nRet = sensor_recorder_destroy_query(query);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_recorder_destroy_query", SensorsGetError(nRet));

	return 0;
}


//& purpose: 
//& type: auto
/**
* @testcase 			ITc_sensor_recorder_query_set_int_p
* @type 				auto
* @author				SRID(asit.s)
* @reviewer				SRID(shobhit.v)
* @since_tizen 			3.0
* @description			set int query
* @scenario				call sensor_recorder_create_query,sensor_recorder_query_set_int,sensor_recorder_destroy_query
* @apicovered			sensor_recorder_create_query,sensor_recorder_query_set_int,sensor_recorder_destroy_query
* @passcase				When Target api is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_recorder_query_set_int_p(void)
{
	START_TEST;
		
	sensor_recorder_query_h query;
	
	int nEnumCountQuery;
	int nEnumCountInterval;
	int arrSensorRecorderQuery[] = 
	{
		SENSOR_RECORDER_QUERY_START_TIME,
		SENSOR_RECORDER_QUERY_END_TIME,
		SENSOR_RECORDER_QUERY_ANCHOR_TIME,
		SENSOR_RECORDER_QUERY_TIME_INTERVAL,
	};
	
	int arrSensorRecorderInterval[] = 
	{
		SENSOR_RECORDER_INTERVAL_10_MINUTES,
		SENSOR_RECORDER_INTERVAL_1_HOUR,
		SENSOR_RECORDER_INTERVAL_3_HOURS,
		SENSOR_RECORDER_INTERVAL_6_HOURS,
		SENSOR_RECORDER_INTERVAL_12_HOURS,
		SENSOR_RECORDER_INTERVAL_1_DAY,
	};
	
	int nSensorRecorderQueryCount = sizeof(arrSensorRecorderQuery) / sizeof(arrSensorRecorderQuery[0]);
	int nSensorRecorderIntervalCount = sizeof(arrSensorRecorderInterval) / sizeof(arrSensorRecorderInterval[0]);
	
	int nRet = sensor_recorder_create_query(&query);
	if ( false == g_bIsFeatureSupported && TIZEN_ERROR_NOT_SUPPORTED == nRet )
	{
		FPRINTF("[Line : %d][%s] Sensor Features not supported \\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_recorder_create_query", SensorsGetError(nRet));
	CHECK_HANDLE(query,"sensor_recorder_create_query");

	for(nEnumCountQuery = 0;nEnumCountQuery < nSensorRecorderQueryCount;nEnumCountQuery++ )
	{
		for(nEnumCountInterval = 0;nEnumCountInterval < nSensorRecorderIntervalCount;nEnumCountInterval++ )
		{
			//Target API
			nRet = sensor_recorder_query_set_int(query, arrSensorRecorderQuery[nEnumCountQuery], arrSensorRecorderInterval[nEnumCountInterval]);
			PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_int", SensorsGetError(nRet),sensor_recorder_destroy_query(query));
		}
	}

	nRet = sensor_recorder_destroy_query(query);
	PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_recorder_destroy_query", SensorsGetError(nRet));

	return 0;
}


//& purpose: 
//& type: auto
/**
* @testcase 			ITc_sensor_recorder_query_set_time_p
* @type 				auto
* @author				SRID(asit.s)
* @reviewer				SRID(shobhit.v)
* @since_tizen 			3.0
* @description			set time query
* @scenario				call sensor_recorder_create_query,sensor_recorder_query_set_time,sensor_recorder_destroy_query
* @apicovered			sensor_recorder_create_query,sensor_recorder_query_set_time,sensor_recorder_destroy_query
* @passcase				When Target api is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_recorder_query_set_time_p(void)
{
	START_TEST;
	
	sensor_recorder_query_h query;
	time_t now;
	time_t start, end;
	time_t anchor;

	int nRet = sensor_recorder_create_query(&query);
	if ( false == g_bIsFeatureSupported && TIZEN_ERROR_NOT_SUPPORTED == nRet )
	{
		FPRINTF("[Line : %d][%s] Sensor Features not supported \\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_recorder_create_query", SensorsGetError(nRet));
	CHECK_HANDLE(query,"sensor_recorder_create_query");

	now = time(NULL);

	/* start time : 1 months ago */
	start = now - TIME_1_MONTH_SEC;
	/* end time : now */
	end = now;
	/* anchor time : 7 AM */
	anchor = 7 * TIME_1_HOUR_SEC;

	//Target API
	nRet = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_START_TIME, start);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_time", SensorsGetError(nRet),sensor_recorder_destroy_query(query));
	
	nRet = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_END_TIME, end);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_time", SensorsGetError(nRet),sensor_recorder_destroy_query(query));
	
	nRet = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_ANCHOR_TIME, anchor);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_time", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

	nRet = sensor_recorder_destroy_query(query);
	PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_recorder_destroy_query", SensorsGetError(nRet));

	return 0;
}


//& purpose: 
//& type: auto
/**
* @testcase 			ITc_sensor_recorder_read_p
* @type 				auto
* @author				SRID(asit.s)
* @reviewer				SRID(shobhit.v)
* @since_tizen 			3.0
* @description			read recorder
* @scenario				call sensor_recorder_create_query,sensor_recorder_query_set_time,sensor_recorder_read,sensor_recorder_destroy_query
* @apicovered			sensor_recorder_create_query,sensor_recorder_query_set_time,sensor_recorder_read,sensor_recorder_destroy_query
* @passcase				When Target api is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_recorder_read_p(void)
{
	START_TEST;
	int nSensorTimeoutId = 0;
	int nTimeOutCB = 2000;
	time_t now;
	time_t start, end;
	time_t anchor;
	sensor_recorder_query_h query;
	int i;
	int sensor_count = sizeof(Sensor)/sizeof(Sensor[0]);
	
	int nRet = sensor_recorder_create_query(&query);
	if ( false == g_bIsFeatureSupported && TIZEN_ERROR_NOT_SUPPORTED == nRet )
	{
		FPRINTF("[Line : %d][%s] Sensor Features not supported \\n", __LINE__, API_NAMESPACE);
		return 0;
	}
		
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_recorder_create_query", SensorsGetError(nRet));
	CHECK_HANDLE(query,"sensor_recorder_create_query");
	
	now = time(NULL);
	start = now - TIME_1_MONTH_SEC;
	end = now;
	anchor = 7 * TIME_1_HOUR_SEC;

	nRet = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_START_TIME, start);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_time", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

	nRet = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_END_TIME, end);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_time", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

	nRet = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_ANCHOR_TIME, anchor);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_time", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

	nRet = sensor_recorder_query_set_int(query, SENSOR_RECORDER_QUERY_TIME_INTERVAL, SENSOR_RECORDER_INTERVAL_1_DAY);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_int", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

	for (i = 0; i < sensor_count; ++i) 
	{
		if (!sensor_recorder_supported[i])
			continue;

		g_bCallbackHit = false;
		if(Sensor[i].eSensorType == SENSOR_HRM_BATCH || Sensor[i].eSensorType == SENSOR_HRM_LED_GREEN_BATCH)
		{
			nTimeOutCB = 30000;
		}
		//Target API
		nRet = sensor_recorder_read(Sensor[i].eSensorType, query, SensorRecorderDatacb, NULL);
		PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_read", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

		RUN_POLLING_LOOP;
		if(g_bCallbackHit == false)
		{
			FPRINTF("[Line : %d][%s] callback hit failed \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	
	}

	nRet = sensor_recorder_destroy_query(query);
	PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_recorder_destroy_query", SensorsGetError(nRet));
	
	return 0;
}


//& purpose: 
//& type: auto
/**
* @testcase 			ITc_sensor_recorder_read_sync_p
* @type 				auto
* @author				SRID(asit.s)
* @reviewer				SRID(shobhit.v)
* @since_tizen 			3.0
* @description			read recorder sync
* @scenario				call sensor_recorder_create_query,sensor_recorder_query_set_time,sensor_recorder_read,sensor_recorder_destroy_query
* @apicovered			sensor_recorder_create_query,sensor_recorder_query_set_time,sensor_recorder_read,sensor_recorder_destroy_query
* @passcase				When Target api is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_recorder_read_sync_p(void)
{
	START_TEST;
	
	time_t now;
	time_t start, end;
	time_t anchor;
	sensor_recorder_query_h query;
	int i;
	int sensor_count = sizeof(Sensor)/sizeof(Sensor[0]);
	
	int nRet = sensor_recorder_create_query(&query);
	if ( false == g_bIsFeatureSupported && TIZEN_ERROR_NOT_SUPPORTED == nRet )
	{
		FPRINTF("[Line : %d][%s] Sensor Features not supported \\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_recorder_create_query", SensorsGetError(nRet));
	CHECK_HANDLE(query,"sensor_recorder_create_query");
	
	now = time(NULL);
	start = now - TIME_1_MONTH_SEC;
	end = now;
	anchor = 7 * TIME_1_HOUR_SEC;

	nRet = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_START_TIME, start);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_time", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

	nRet = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_END_TIME, end);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_time", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

	nRet = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_ANCHOR_TIME, anchor);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_time", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

	nRet = sensor_recorder_query_set_int(query, SENSOR_RECORDER_QUERY_TIME_INTERVAL, SENSOR_RECORDER_INTERVAL_1_DAY);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_int", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

	for (i = 0; i < sensor_count; ++i) 
	{
		if (!sensor_recorder_supported[i])
			continue;

		g_bCallbackHit = false;
		
		//Target API
		nRet = sensor_recorder_read_sync(Sensor[i].eSensorType, query, SensorRecorderSyncCb, NULL);
		PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_read_sync", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

		if(g_bCallbackHit == false)
		{
			FPRINTF("[Line : %d][%s] callback hit failed \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	
	}

	nRet = sensor_recorder_destroy_query(query);
	PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_recorder_destroy_query", SensorsGetError(nRet));
	
	return 0;
}


//& purpose: 
//& type: auto
/**
* @testcase 			ITc_sensor_recorder_data_get_time_p
* @type 				auto
* @author				SRID(asit.s)
* @reviewer				SRID(shobhit.v)
* @since_tizen 			3.0
* @description			recorder get time data
* @scenario				call sensor_recorder_create_query,sensor_recorder_query_set_time,sensor_recorder_read,sensor_recorder_destroy_query
* @apicovered			sensor_recorder_create_query,sensor_recorder_query_set_time,sensor_recorder_read,sensor_recorder_destroy_query
* @passcase				When Target api is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_recorder_data_get_time_p(void)
{
	START_TEST;
	
	time_t now;
	time_t start, end;
	time_t anchor;
	sensor_recorder_query_h query;
	int i;
	int sensor_count = sizeof(Sensor)/sizeof(Sensor[0]);
	int nRet = sensor_recorder_create_query(&query);
	if ( false == g_bIsFeatureSupported && TIZEN_ERROR_NOT_SUPPORTED == nRet )
	{
		FPRINTF("[Line : %d][%s] Sensor Features not supported \\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_recorder_create_query", SensorsGetError(nRet));
	CHECK_HANDLE(query,"sensor_recorder_create_query");
	
	now = time(NULL);
	start = now - TIME_1_MONTH_SEC;
	end = now;
	anchor = 7 * TIME_1_HOUR_SEC;

	nRet = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_START_TIME, start);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_time", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

	nRet = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_END_TIME, end);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_time", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

	nRet = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_ANCHOR_TIME, anchor);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_time", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

	nRet = sensor_recorder_query_set_int(query, SENSOR_RECORDER_QUERY_TIME_INTERVAL, SENSOR_RECORDER_INTERVAL_1_DAY);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_int", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

	for (i = 0; i < sensor_count; ++i) 
	{
		if (!sensor_recorder_supported[i])
			continue;

		g_bCallbackHit = false;
		g_bStatus = true;
		//Target API
		nRet = sensor_recorder_read_sync(Sensor[i].eSensorType, query, SensorRecorderReadSyncCbGetTime, NULL);
		PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_read_sync", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

		if(g_bCallbackHit == false)
		{
			FPRINTF("[Line : %d][%s] callback hit failed \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		if(g_bStatus == false)
		{
			return 1;
		}		
		PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, g_nRet, "sensor_recorder_data_get_time", SensorsGetError(nRet),sensor_recorder_destroy_query(query));
	
	}

	nRet = sensor_recorder_destroy_query(query);
	PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_recorder_destroy_query", SensorsGetError(nRet));
	
	return 0;
}


//& purpose: 
//& type: auto
/**
* @testcase 			ITc_sensor_recorder_data_get_int_p
* @type 				auto
* @author				SRID(asit.s)
* @reviewer				SRID(shobhit.v)
* @since_tizen 			3.0
* @description			recorder get int data
* @scenario				call sensor_recorder_create_query,sensor_recorder_query_set_time,sensor_recorder_read,sensor_recorder_destroy_query
* @apicovered			sensor_recorder_create_query,sensor_recorder_query_set_time,sensor_recorder_read,sensor_recorder_destroy_query
* @passcase				When Target api is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_recorder_data_get_int_p(void)
{
	START_TEST;
	
	time_t now;
	time_t start, end;
	time_t anchor;
	sensor_recorder_query_h query;
	int i;
	int sensor_count = sizeof(Sensor)/sizeof(Sensor[0]);
	int nRet = sensor_recorder_create_query(&query);
	if ( false == g_bIsFeatureSupported && TIZEN_ERROR_NOT_SUPPORTED == nRet )
	{
		FPRINTF("[Line : %d][%s] Sensor Features not supported \\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_recorder_create_query", SensorsGetError(nRet));
	CHECK_HANDLE(query,"sensor_recorder_create_query");
	
	now = time(NULL);
	start = now - TIME_1_MONTH_SEC;
	end = now;
	anchor = 7 * TIME_1_HOUR_SEC;

	nRet = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_START_TIME, start);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_time", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

	nRet = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_END_TIME, end);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_time", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

	nRet = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_ANCHOR_TIME, anchor);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_time", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

	nRet = sensor_recorder_query_set_int(query, SENSOR_RECORDER_QUERY_TIME_INTERVAL, SENSOR_RECORDER_INTERVAL_1_DAY);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_int", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

	for (i = 0; i < sensor_count; ++i) 
	{
		if (!sensor_recorder_supported[i])
			continue;

		g_bCallbackHit = false;
		g_bStatus = true;
		//Target API
		nRet = sensor_recorder_read_sync(Sensor[i].eSensorType, query, SensorRecorderReadSyncCbGetInt, NULL);
		PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_read_sync", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

		if(g_bCallbackHit == false)
		{
			FPRINTF("[Line : %d][%s] callback hit failed \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		if(g_bStatus == false)
		{
			return 1;
		}
		PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, g_nRet, "sensor_recorder_data_get_int", SensorsGetError(nRet),sensor_recorder_destroy_query(query));
	
	}

	nRet = sensor_recorder_destroy_query(query);
	PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_recorder_destroy_query", SensorsGetError(nRet));
	
	return 0;;
}


//& purpose: 
//& type: auto
/**
* @testcase 			ITc_sensor_recorder_data_get_double_p
* @type 				auto
* @author				SRID(asit.s)
* @reviewer				SRID(shobhit.v)
* @since_tizen 			3.0
* @description			recorder get double data
* @scenario				call sensor_recorder_create_query,sensor_recorder_query_set_time,sensor_recorder_read,sensor_recorder_destroy_query
* @apicovered			sensor_recorder_create_query,sensor_recorder_query_set_time,sensor_recorder_read,sensor_recorder_destroy_query
* @passcase				When Target api is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_recorder_data_get_double_p(void)
{
	START_TEST;
	
	time_t now;
	time_t start, end;
	time_t anchor;
	sensor_recorder_query_h query;
	int i;
	int sensor_count = sizeof(Sensor)/sizeof(Sensor[0]);
	int nRet = sensor_recorder_create_query(&query);
	if ( false == g_bIsFeatureSupported && TIZEN_ERROR_NOT_SUPPORTED == nRet )
	{
		FPRINTF("[Line : %d][%s] Sensor Features not supported \\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_recorder_create_query", SensorsGetError(nRet));
	CHECK_HANDLE(query,"sensor_recorder_create_query");
	
	now = time(NULL);
	start = now - TIME_1_MONTH_SEC;
	end = now;
	anchor = 7 * TIME_1_HOUR_SEC;

	nRet = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_START_TIME, start);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_time", SensorsGetError(nRet),sensor_recorder_destroy_query(query));
	
	nRet = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_END_TIME, end);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_time", SensorsGetError(nRet),sensor_recorder_destroy_query(query));
	
	nRet = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_ANCHOR_TIME, anchor);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_time", SensorsGetError(nRet),sensor_recorder_destroy_query(query));
	
	nRet = sensor_recorder_query_set_int(query, SENSOR_RECORDER_QUERY_TIME_INTERVAL, SENSOR_RECORDER_INTERVAL_1_DAY);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_query_set_int", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

	for (i = 0; i < sensor_count; ++i) 
	{
		if (!sensor_recorder_supported[i])
			continue;

		g_bCallbackHit = false;
		g_bStatus = true;
		//Target API
		nRet = sensor_recorder_read_sync(Sensor[i].eSensorType, query, SensorRecorderReadSyncCbGetDouble, NULL);
		PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_recorder_read_sync", SensorsGetError(nRet),sensor_recorder_destroy_query(query));

		if(g_bCallbackHit == false)
		{
			FPRINTF("[Line : %d][%s] callback hit failed \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		
		if(g_bStatus == false)
		{
			return 1;
		}
		
		PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, g_nRet, "sensor_recorder_data_get_double", SensorsGetError(nRet),sensor_recorder_destroy_query(query));
	
	}

	nRet = sensor_recorder_destroy_query(query);
	PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_recorder_destroy_query", SensorsGetError(nRet));
	
	return 0;
}

/** @} */ 
/** @} */ 
