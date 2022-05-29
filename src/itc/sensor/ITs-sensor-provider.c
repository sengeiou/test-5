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
#define TEST_SENSOR_URI "http://samsung.com/sensor/general/test_sensor/test_sensor"
#define TEST_STRING "TEST_TEST_TEST"
#define CB_TIMEOUT 2000
#define TEST_STRING_TERM "TERM"

bool g_bSensorAddCallback;
bool g_bSensorAccuracyChangeCallback;


/**
* @function 		ITs_Sensors_startup
* @description	 	Called before each test, creates Sensors
* @parameter		NA
* @return 			NA
*/
void ITs_sensor_provider_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		int nRet = remove(ERR_LOG);
		PRINT_RESULT_NORETURN(0, nRet, "ITs_sensor_provider_startup -remove", "Remove failed for ERR_LOG");
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Sensor_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		ITs_Sensors_cleanup
* @description	 	Called after each test, destroys Sensors
* @parameter		NA
* @return 			NA
*/
void ITs_sensor_provider_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Sensor_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function			SensorAddCallback
* @description		Called when a new sensor is added.
* @parameter[IN]	The sensor uri
* @parameter[IN]	The user data passed from the callback registration function
* @return			NA
*/
void SensorAddCallback(const char *uri, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] SensorAddCallback is called\\n", __LINE__, API_NAMESPACE);
#endif
	char *szud = (char *)user_data;

	if (strcmp(szud, TEST_STRING) == 0)
		g_bSensorAddCallback = true;

	if ( g_pSensorMainLoop )
	{
		g_main_loop_quit(g_pSensorMainLoop);
		g_main_loop_unref(g_pSensorMainLoop);
		g_pSensorMainLoop = NULL;
	}
}
/**
* @function			SensorRemoveCallback
* @description		Called when a new sensor is removed.
* @parameter[IN]	The sensor uri
* @parameter[IN]	The user data passed from the callback registration function
* @return			NA
*/
void SensorRemoveCallback(const char *uri, void *user_data)
{
	#if DEBUG
		FPRINTF("[Line : %d][%s] SensorAddCallback is called\\n", __LINE__, API_NAMESPACE);
	#endif
	char *szud = (char *)user_data;

	if (strcmp(szud, TEST_STRING) == 0)
	{
		g_bSensorAddCallback = true;
	}

	if ( g_pSensorMainLoop )
	{
		g_main_loop_quit(g_pSensorMainLoop);
		g_main_loop_unref(g_pSensorMainLoop);
		g_pSensorMainLoop = NULL;
	}
}
/**
* @function			SensorStartCallback
* @description		Called when the sensor is started .
* @parameter[IN]	The sensor handle
* @parameter[IN]	The user data passed from the callback registration function
* @return			NA
*/
void SensorStartCallback(sensor_provider_h provider, void *user_data)
{
	#if DEBUG
		FPRINTF("[Line : %d][%s] SensorStartCallback is called\\n", __LINE__, API_NAMESPACE);
	#endif
	char *pszud = (char *)user_data;
	if (strcmp(pszud, TEST_STRING) == 0)
	{
		g_bSensorAddCallback = true;
	}

	if ( g_pSensorMainLoop )
	{
		g_main_loop_quit(g_pSensorMainLoop);
		g_main_loop_unref(g_pSensorMainLoop);
		g_pSensorMainLoop = NULL;
	}
}

/**
* @function			SensorStopCallback
* @description		Called when the sensor is stopped .
* @parameter[IN]	The sensor handle
* @parameter[IN]	The user data passed from the callback registration function
* @return			NA
*/
void SensorStopCallback(sensor_provider_h provider, void *user_data)
{
	#if DEBUG
		FPRINTF("[Line : %d][%s] SensorStartCallback is called\\n", __LINE__, API_NAMESPACE);
	#endif

	char *pszud = (char *)user_data;

	if (strcmp(pszud, TEST_STRING) == 0)
	{
		g_bSensorAddCallback = true;
	}

	if ( g_pSensorMainLoop )
	{
		g_main_loop_quit(g_pSensorMainLoop);
		g_main_loop_unref(g_pSensorMainLoop);
		g_pSensorMainLoop = NULL;
	}
}

/**
* @function			SensorTestCallback
* @description		Called when the sensor is started .
* @parameter[IN]	The sensor handle
* @parameter[IN]	The user data passed from the callback registration function
* @return			NA
*/
void SensorTestCallback(sensor_h sensor, sensor_event_s events[], int events_count, void* user_data)
{
	#if DEBUG
		FPRINTF("[Line : %d][%s] SensorTestCallback is called\\n", __LINE__, API_NAMESPACE);
	#endif
	g_bSensorAddCallback = true;
	if ( g_pSensorMainLoop )
	{
		g_main_loop_quit(g_pSensorMainLoop);
		g_main_loop_unref(g_pSensorMainLoop);
		g_pSensorMainLoop = NULL;
	}
}
/**
* @function			SensorTestIntervalCallback
* @description		Called when  interval is set to sensor.
* @parameter[IN]	The sensor provider handle
* @parameter[IN]	The sensor event
* @parameter[IN]	The user data passed from the callback registration function
* @return			NA
*/
void SensorTestIntervalCallback(sensor_provider_h provider,unsigned int interval_ms, void *user_data)
{
	#if DEBUG
		FPRINTF("[Line : %d][%s] SensorTestIntervalCallback is called\\n", __LINE__, API_NAMESPACE);
	#endif
	char *pszud = (char *)user_data;
	if (strcmp(pszud, TEST_STRING) == 0)
	{
		g_bSensorAddCallback = true;
	}
	g_bSensorAddCallback = true;
	//FPRINTF(" SensorTestIntervalCallback  stringvalue is not equal\\n");
	if ( g_pSensorMainLoop )
	{
		g_main_loop_quit(g_pSensorMainLoop);
		g_main_loop_unref(g_pSensorMainLoop);
		g_pSensorMainLoop = NULL;
	}
}
/**
* @function			Sensor_Start
* @description		Called to start sensor.
* @parameter[IN]	The sensor listener
* @parameter[IN]	The sensor msg
* @return			0 on success
*/
int Sensor_Start(sensor_listener_h *listener, const char *msg)
{
	sensor_h hsensor;
	g_bSensorAddCallback = false;
	int nRet = sensor_get_default_sensor_by_uri(TEST_SENSOR_URI, &hsensor);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_get_default_sensor_by_uri", SensorsGetError(nRet));

	nRet = sensor_create_listener(hsensor,listener);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_create_listener", SensorsGetError(nRet));

	nRet = sensor_listener_set_events_cb(*listener, SensorTestCallback, (void *)msg);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_listener_set_events_cb", SensorsGetError(nRet));

	nRet = sensor_listener_start(*listener);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_listener_start", SensorsGetError(nRet));

	return 0;

}
/**
* @function			Sensor_Stop
* @description		Called on stop of sensor.
* @parameter[IN]	The sensor listener
* @return			0 on success
*/
int Sensor_Stop(sensor_listener_h listener)
{
	int nRet = sensor_listener_stop(listener);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_get_default_sensor_by_uri", SensorsGetError(nRet));

	nRet = sensor_listener_unset_events_cb(listener);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_listener_unset_events_cb", SensorsGetError(nRet));

	nRet = sensor_destroy_listener(listener);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_destroy_listener", SensorsGetError(nRet));

	return 0;

}
/**
* @function			SensorTestPublish
* @description		Called for publish.
* @parameter[IN]	gpointer
* @return			0 on success
*/
gboolean SensorTestPublish(gpointer gdata)
{
	fprintf(stderr, "test_callback was called\n");
	int count = 1;
	if (g_bSensorAddCallback)
		return FALSE;

	sensor_provider_h hprovider = (sensor_provider_h)(gdata);

	sensor_event_s data[count];
	data[0].accuracy = 3;
	data[0].timestamp = 9999;
	data[0].value_count = 3;
	data[0].values[0] = 1;
	data[0].values[1] = 2;
	data[0].values[2] = 3;

	int nRet = sensor_provider_publish_events(hprovider, data, count);
	if(nRet != SENSOR_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] sensor_provider_publish_events failed: ITc_sensor_provider_publish_events_p \\n", __LINE__, API_NAMESPACE);
		return FALSE;
	}
	return TRUE;
}
/**
* @function			SensorTestStart
* @description		Called to start sensor.
* @parameter[IN]	gpointer
* @return			TRUE on success
*/
gboolean SensorTestStart(gpointer gdata)
{
	sensor_listener_h *hlistener = (sensor_listener_h *)(gdata);
	Sensor_Start(hlistener, TEST_STRING_TERM);
	return FALSE;
}
/**
* @function			SensorTestStop
* @description		Called to stop sensor.
* @parameter[IN]	gpointer
* @return			TRUE on success
*/
gboolean SensorTestStop(gpointer gdata)
{
	sensor_listener_h *hlistener = (sensor_listener_h *)(gdata);
	Sensor_Stop(*hlistener);
	return FALSE;
}

/** @addtogroup itc-sensor-testcases
*  @brief 		Integration testcases for module sensor
*  @ingroup 	itc-sensor
*  @{
*/
//& purpose: Creates and destroys sensor provider.
//& type: auto
/**
* @testcase 			ITc_sensor_create_destroy_provider_p
* @type 				auto
* @author				SRID(shilpa.j)
* @reviewer				SRID(nibha.sharma)
* @since_tizen 			4.0
* @description			Creates and destroys sensor provider
* @scenario				Creates the sensor provider
*						destroy the sensor provider
* @apicovered			sensor_is_supported
* @passcase				When sensor_is_supported is successful
* @failcase				If target API sensor_is_supported fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_create_destroy_provider_p(void)
{
	START_TEST;
	sensor_provider_h hSensorProvider;

	int nRet = sensor_create_provider(TEST_SENSOR_URI, &hSensorProvider);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_create_provider", SensorsGetError(nRet));
	CHECK_HANDLE(hSensorProvider, "sensor_create_provider");

	nRet = sensor_destroy_provider(hSensorProvider);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_destroy_provider", SensorsGetError(nRet));

	return 0;
}

//& purpose: Adds the sensor provider handle and releases all its resources.
//& type: auto
/**
* @testcase 			ITc_sensor_add_remove_provider_p
* @type 				auto
* @author				SRID(shilpa.j)
* @reviewer				SRID(nibha.sharma)
* @since_tizen 			4.0
* @description			Adds the sensor provider handle and releases all its resources
* @scenario				Creates the sensor provider
						Add the provider
						Remove the provider
*						destroy the sensor provider
* @apicovered			sensor_is_supported
* @passcase				When sensor_add_provider,sensor_remove_provider is successful
* @failcase				If target API sensor_add_provider,sensor_remove_provider fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_add_remove_provider_p(void)
{
	START_TEST;
	sensor_provider_h hSensorProvider;

	int nRet = sensor_create_provider(TEST_SENSOR_URI, &hSensorProvider);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_create_provider", SensorsGetError(nRet));
	CHECK_HANDLE(hSensorProvider, "sensor_create_provider");

	//Target API
	nRet = sensor_add_provider(hSensorProvider);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_add_provider", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	nRet = sensor_remove_provider(hSensorProvider);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_remove_provider", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	nRet = sensor_destroy_provider(hSensorProvider);
	PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_destroy_provider", SensorsGetError(nRet));

	return 0;
}

//& purpose: Sets the name of the sensor.
//& type: auto
/**
* @testcase 			ITc_sensor_provider_set_name_p
* @type 				auto
* @author				SRID(shilpa.j)
* @reviewer				SRID(nibha.sharma)
* @since_tizen 			4.0
* @description			Sets the name of the sensor
* @scenario				Creates the sensor provider
						Sets the name of the sensor
*						destroy the sensor provider
* @apicovered			sensor_provider_set_name,sensor_create_provider,sensor_destroy_provider
* @passcase				When sensor_provider_set_name is successful
* @failcase				If target API sensor_provider_set_name fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_provider_set_name_p(void)
{
	START_TEST;
	sensor_provider_h hSensorProvider;

	int nRet = sensor_create_provider(TEST_SENSOR_URI, &hSensorProvider);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_create_provider", SensorsGetError(nRet));
	CHECK_HANDLE(hSensorProvider, "sensor_create_provider");

	nRet = sensor_provider_set_name(hSensorProvider,"mysensor");
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_provider_set_name", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	nRet = sensor_destroy_provider(hSensorProvider);
	PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_destroy_provider", SensorsGetError(nRet));

	return 0;
}

//& purpose: Sets the vendor of the sensor.
//& type: auto
/**
* @testcase 			ITc_sensor_provider_set_vendor_p
* @type 				auto
* @author				SRID(shilpa.j)
* @reviewer				SRID(nibha.sharma)
* @since_tizen 			4.0
* @description			Sets the vendor of the sensor
* @scenario				Creates the sensor provider
						Sets the vendor of the sensor
*						destroy the sensor provider
* @apicovered			sensor_provider_set_vendor,sensor_create_provider,sensor_destroy_provider
* @passcase				When sensor_provider_set_vendor is successful
* @failcase				If target API sensor_provider_set_vendor fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_provider_set_vendor_p(void)
{
	START_TEST;
	sensor_provider_h hSensorProvider;
	char*szTempString = "Tizen";

	int nRet = sensor_create_provider(TEST_SENSOR_URI, &hSensorProvider);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_create_provider", SensorsGetError(nRet));
	CHECK_HANDLE(hSensorProvider, "sensor_create_provider");

	nRet = sensor_provider_set_vendor(hSensorProvider,szTempString);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_provider_set_vendor", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	nRet = sensor_destroy_provider(hSensorProvider);
	PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_destroy_provider", SensorsGetError(nRet));

	return 0;
}

//& purpose: Sets the value range of the sensor
//& type: auto
/**
* @testcase 			ITc_sensor_provider_set_range_p
* @type 				auto
* @author				SRID(shilpa.j)
* @reviewer				SRID(nibha.sharma)
* @since_tizen 			4.0
* @description			Sets the value range of the sensor
* @scenario				Creates the sensor provider
						Sets the value range of the sensor
*						destroy the sensor provider
* @apicovered			sensor_provider_set_range,sensor_create_provider,sensor_destroy_provider
* @passcase				When sensor_provider_set_range is successful
* @failcase				If target API sensor_provider_set_range fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_provider_set_range_p(void)
{
	START_TEST;
	sensor_provider_h hSensorProvider;
	float fStartRange =  0.0;
	float fEndRange =  0.1;

	int nRet = sensor_create_provider(TEST_SENSOR_URI, &hSensorProvider);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_create_provider", SensorsGetError(nRet));
	CHECK_HANDLE(hSensorProvider, "sensor_create_provider");

	nRet = sensor_provider_set_range(hSensorProvider,fStartRange,fEndRange);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_provider_set_range", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	nRet = sensor_destroy_provider(hSensorProvider);
	PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_destroy_provider", SensorsGetError(nRet));

	return 0;
}

//& purpose: Sets the resolution of the sensor
//& type: auto
/**
* @testcase 			ITc_sensor_provider_set_resolution_p
* @type 				auto
* @author				SRID(shilpa.j)
* @reviewer				SRID(nibha.sharma)
* @since_tizen 			4.0
* @description			Sets the resolution of the sensor
* @scenario				Creates the sensor provider
						Sets the resolution of the sensor
*						destroy the sensor provider
* @apicovered			sensor_provider_set_resolution,sensor_create_provider,sensor_destroy_provider
* @passcase				When sensor_provider_set_resolution is successful
* @failcase				If target API sensor_provider_set_resolution fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_provider_set_resolution_p(void)
{
	START_TEST;
	sensor_provider_h hSensorProvider;
	float fResolution =  0.1;

	int nRet = sensor_create_provider(TEST_SENSOR_URI, &hSensorProvider);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_create_provider", SensorsGetError(nRet));
	CHECK_HANDLE(hSensorProvider, "sensor_create_provider");

	nRet = sensor_provider_set_resolution(hSensorProvider,fResolution);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_provider_set_resolution", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	nRet = sensor_destroy_provider(hSensorProvider);
	PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_destroy_provider", SensorsGetError(nRet));

	return 0;
}

//& purpose: Registers a callback function to be invoked when a new sensor is added
//& type: auto
/**
* @testcase 			ITc_sensor_add_remove_sensor_added_cb_p
* @type 				auto
* @author				SRID(shilpa.j)
* @reviewer				SRID(nibha.sharma)
* @since_tizen 			4.0
* @description			Registers a callback function to be invoked when a new sensor is added
* @scenario				Creates the sensor provider
						Adds a sensor
*						destroy the sensor provider
* @apicovered			sensor_add_sensor_added_cb,sensor_remove_sensor_added_cb,sensor_create_provider,sensor_destroy_provider
* @passcase				When sensor_remove_sensor_added_cb, sensor_remove_sensor_added_cbis successful
* @failcase				If target API sensor_remove_sensor_added_cb,sensor_remove_sensor_added_cb fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_add_remove_sensor_added_cb_p(void)
{
	START_TEST;
	sensor_provider_h hSensorProvider;
	int nSensorTimeoutId = 0;
	int nTimeOutCB = 2000;
	g_bSensorAddCallback = false;

	int nRet = sensor_create_provider(TEST_SENSOR_URI, &hSensorProvider);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_create_provider", SensorsGetError(nRet));
	CHECK_HANDLE(hSensorProvider, "sensor_create_provider");
	 //Target API
	nRet = sensor_add_sensor_added_cb(SensorAddCallback,TEST_STRING);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_add_sensor_added_cb", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	nRet = sensor_add_provider(hSensorProvider);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_add_provider", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	RUN_POLLING_LOOP;

	if(g_bSensorAddCallback != true)
	{
		FPRINTF("[Line : %d][%s] g_bSensorAddCallback failed to invoke callback for sensor \n", __LINE__, API_NAMESPACE);
		sensor_remove_provider(hSensorProvider);
		sensor_destroy_provider(hSensorProvider);
		return 1;
	}

	 //Target API
	nRet = sensor_remove_sensor_added_cb(SensorAddCallback);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_remove_sensor_added_cb", SensorsGetError(nRet),sensor_remove_provider(hSensorProvider);sensor_destroy_provider(hSensorProvider));

	nRet = sensor_remove_provider(hSensorProvider);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_remove_provider", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	nRet = sensor_destroy_provider(hSensorProvider);
	PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_destroy_provider", SensorsGetError(nRet));

	return 0;
}

//& purpose: Registers a callback function to be invoked when a sensor is removed
//& type: auto
/**
* @testcase 			ITc_sensor_add_remove_sensor_removed_cb_p
* @type 				auto
* @author				SRID(shilpa.j)
* @reviewer				SRID(nibha.sharma)
* @since_tizen 			4.0
* @description			Registers a callback function to be invoked when a new sensor is added
* @scenario				Creates the sensor provider
						Adds a sensor
*						destroy the sensor provider
* @apicovered			sensor_add_sensor_added_cb,sensor_remove_sensor_added_cb,sensor_create_provider,sensor_destroy_provider
* @passcase				When sensor_remove_sensor_added_cb, sensor_remove_sensor_added_cbis successful
* @failcase				If target API sensor_remove_sensor_added_cb,sensor_remove_sensor_added_cb fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_add_remove_sensor_removed_cb_p(void)
{
	START_TEST;
	sensor_provider_h hSensorProvider;
	int nSensorTimeoutId = 0;
	int nTimeOutCB = 2000;
	g_bSensorAddCallback = false;

	int nRet = sensor_create_provider(TEST_SENSOR_URI, &hSensorProvider);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_create_provider", SensorsGetError(nRet));
	CHECK_HANDLE(hSensorProvider, "sensor_create_provider");
	 //Target API
	nRet = sensor_add_sensor_removed_cb(SensorRemoveCallback,TEST_STRING);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_add_sensor_removed_cb", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	nRet = sensor_add_provider(hSensorProvider);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_add_provider", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	nRet = sensor_remove_provider(hSensorProvider);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_remove_provider", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	RUN_POLLING_LOOP;

	if(g_bSensorAddCallback != true)
	{
		FPRINTF("[Line : %d][%s] g_bSensorAddCallback failed to invoke callback for sensor \n", __LINE__, API_NAMESPACE);
		sensor_destroy_provider(hSensorProvider);
		return 1;
	}

	//Target API
	nRet = sensor_remove_sensor_removed_cb(SensorRemoveCallback);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_remove_sensor_removed_cb", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	nRet = sensor_destroy_provider(hSensorProvider);
	PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_destroy_provider", SensorsGetError(nRet));

	return 0;
}

//& purpose: Registers a callback function to be invoked when a sensor is started
//& type: auto
/**
* @testcase 			ITc_sensor_provider_set_start_cb_p
* @type 				auto
* @author				SRID(shilpa.j)
* @reviewer				SRID(nibha.sharma)
* @since_tizen 			4.0
* @description			Registers a callback function to be invoked when a sensor is started
* @scenario				Creates the sensor provider
						Adds a sensor
*						destroy the sensor provider
* @apicovered			sensor_provider_set_start_cb,,sensor_create_provider,sensor_destroy_provider
* @passcase				When sensor_remove_sensor_added_cb, sensor_remove_sensor_added_cbis successful
* @failcase				If target API sensor_remove_sensor_added_cb,sensor_remove_sensor_added_cb fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_provider_set_start_cb_p(void)
{
	START_TEST;

	sensor_provider_h hSensorProvider;
	sensor_listener_h hlistener;
	int nSensorTimeoutId = 0;
	int nTimeOutCB = 2000;
	g_bSensorAddCallback = false;

	int nRet = sensor_create_provider(TEST_SENSOR_URI, &hSensorProvider);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_create_provider", SensorsGetError(nRet));
	CHECK_HANDLE(hSensorProvider, "sensor_create_provider");

	nRet = sensor_add_provider(hSensorProvider);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_add_provider", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	//Target API
	nRet = sensor_provider_set_start_cb(hSensorProvider,SensorStartCallback,TEST_STRING);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_provider_set_start_cb", SensorsGetError(nRet),sensor_remove_provider(hSensorProvider);sensor_destroy_provider(hSensorProvider));

	g_timeout_add(100, SensorTestStart, &hlistener);

	RUN_POLLING_LOOP;

	if(g_bSensorAddCallback != true)
	{
		FPRINTF("[Line : %d][%s] g_bSensorAddCallback failed to invoke callback for sensor \n", __LINE__, API_NAMESPACE);
		sensor_remove_provider(hSensorProvider);
		sensor_destroy_provider(hSensorProvider);
		return 1;
	}

	nRet = sensor_remove_provider(hSensorProvider);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_remove_provider", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	nRet = sensor_destroy_provider(hSensorProvider);
	PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_destroy_provider", SensorsGetError(nRet));

	return 0;
}

//& purpose: Registers a callback function to be invoked when a sensor is stopped
//& type: auto
/**
* @testcase 			ITc_sensor_provider_set_stop_cb_p
* @type 				auto
* @author				SRID(shilpa.j)
* @reviewer				SRID(nibha.sharma)
* @since_tizen 			4.0
* @description			Registers a callback function to be invoked when a sensor is stopped
* @scenario				Creates the sensor provider
						Adds a sensor
*						destroy the sensor provider
* @apicovered			sensor_provider_set_stop_cb,sensor_create_provider,sensor_add_provider,sensor_remove_provider,sensor_destroy_provider
* @passcase				When sensor_remove_sensor_added_cb, sensor_remove_sensor_added_cbis successful
* @failcase				If target API sensor_remove_sensor_added_cb,sensor_remove_sensor_added_cb fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_provider_set_stop_cb_p(void)
{
	START_TEST;

	sensor_provider_h hSensorProvider;
	sensor_listener_h hlistener;
	int nSensorTimeoutId = 0;
	int nTimeOutCB = 2000;
	g_bSensorAddCallback = false;

	int nRet = sensor_create_provider(TEST_SENSOR_URI, &hSensorProvider);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_create_provider", SensorsGetError(nRet));
	CHECK_HANDLE(hSensorProvider, "sensor_create_provider");

	nRet = sensor_add_provider(hSensorProvider);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_add_provider", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	//Target API
	nRet = sensor_provider_set_stop_cb(hSensorProvider,SensorStopCallback,(void *)TEST_STRING);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_provider_set_stop_cb", SensorsGetError(nRet),sensor_remove_provider(hSensorProvider);sensor_destroy_provider(hSensorProvider));

	g_timeout_add(100, SensorTestStart, &hlistener);
	g_timeout_add(300, SensorTestStop, &hlistener);

	RUN_POLLING_LOOP;

	if(g_bSensorAddCallback != true)
	{
		FPRINTF("[Line : %d][%s] g_bSensorAddCallback failed to invoke callback for sensor \n", __LINE__, API_NAMESPACE);
		sensor_remove_provider(hSensorProvider);
		sensor_destroy_provider(hSensorProvider);
		return 1;
	}

	nRet = sensor_remove_provider(hSensorProvider);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_remove_provider", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	nRet = sensor_destroy_provider(hSensorProvider);
	PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_destroy_provider", SensorsGetError(nRet));

	return 0;
}

//& purpose:Registers a callback function to be invoked when interval is set to sensor
//& type: auto
/**
* @testcase 			ITc_sensor_provider_set_interval_changed_cb_p
* @type 				auto
* @author				SRID(shilpa.j)
* @reviewer				SRID(nibha.sharma)
* @since_tizen 			4.0
* @description			Registers a callback function to be invoked when interval is set to sensor
* @scenario				Creates the sensor provider
						Adds a sensor
*						destroy the sensor provider
* @apicovered			sensor_provider_set_start_cb,sensor_create_provider,sensor_destroy_provider
* @passcase				When sensor_provider_set_interval_changed_cb is successful
* @failcase				If target API sensor_provider_set_interval_changed_cb fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_provider_set_interval_changed_cb_p(void)
{
	START_TEST;

	sensor_provider_h hSensorProvider;
	sensor_listener_h hlistener;
	int nSensorTimeoutId = 0;
	int nTimeOutCB = 2000;
	g_bSensorAddCallback = false;

	int nRet = sensor_create_provider(TEST_SENSOR_URI, &hSensorProvider);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_create_provider", SensorsGetError(nRet));
	CHECK_HANDLE(hSensorProvider, "sensor_create_provider");

	nRet = sensor_add_provider(hSensorProvider);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_add_provider", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	//Target API
	nRet = sensor_provider_set_interval_changed_cb(hSensorProvider,SensorTestIntervalCallback,TEST_STRING);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_provider_set_interval_changed_cb", SensorsGetError(nRet),sensor_remove_provider(hSensorProvider);sensor_destroy_provider(hSensorProvider));

	g_timeout_add(100, SensorTestStart, &hlistener);

	RUN_POLLING_LOOP;

	if(g_bSensorAddCallback != true)
	{
		FPRINTF("[Line : %d][%s] g_bSensorAddCallback failed to invoke callback SensorTestIntervalCallback for sensor \n", __LINE__, API_NAMESPACE);
		sensor_remove_provider(hSensorProvider);
		sensor_destroy_provider(hSensorProvider);
		return 1;
	}

	nRet = sensor_remove_provider(hSensorProvider);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_remove_provider", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	nRet = sensor_destroy_provider(hSensorProvider);
	PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_destroy_provider", SensorsGetError(nRet));

	return 0;
}

//& purpose: Publishes a sensor event to it's listeners
//& type: auto
/**
* @testcase 			ITc_sensor_provider_publish_events_p
* @type 				auto
* @author				SRID(shilpa.j)
* @reviewer				SRID(nibha.sharma)
* @since_tizen 			4.0
* @description			Publishes a sensor event to it's listeners
* @scenario				Creates the sensor provider
						Adds a sensor
						Publishes a sensor event
*						destroy the sensor provider
* @apicovered			sensor_provider_publish,sensor_create_provider,sensor_add_provider,sensor_remove_provider,sensor_destroy_provider
* @passcase				When sensor_provider_publish is successful
* @failcase				If target API sensor_provider_publish fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_sensor_provider_publish_events_p(void)
{
	START_TEST;

	sensor_provider_h hSensorProvider;
	sensor_listener_h hlistener;
	int nSensorTimeoutId = 0;
	int nTimeOutCB = 2000;
	g_bSensorAddCallback = false;

	int nRet = sensor_create_provider(TEST_SENSOR_URI, &hSensorProvider);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_create_provider", SensorsGetError(nRet));
	CHECK_HANDLE(hSensorProvider, "sensor_create_provider");

	nRet = sensor_add_provider(hSensorProvider);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_add_provider", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	g_timeout_add(100, SensorTestPublish, hSensorProvider);

	nRet = Sensor_Start(&hlistener, TEST_STRING);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "Sensor_Stop", SensorsGetError(nRet),sensor_remove_provider(hSensorProvider);sensor_destroy_provider(hSensorProvider));

	RUN_POLLING_LOOP;

	if(g_bSensorAddCallback != true)
	{
		FPRINTF("[Line : %d][%s] g_bSensorAddCallback failed to invoke callback for sensor \n", __LINE__, API_NAMESPACE);
		sensor_remove_provider(hSensorProvider);
		sensor_destroy_provider(hSensorProvider);
		return 1;
	}

	nRet = Sensor_Stop(hlistener);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "Sensor_Stop", SensorsGetError(nRet),sensor_remove_provider(hSensorProvider);sensor_destroy_provider(hSensorProvider));

	nRet = sensor_remove_provider(hSensorProvider);
	PRINT_RESULT_CLEANUP(SENSOR_ERROR_NONE, nRet, "sensor_remove_provider", SensorsGetError(nRet),sensor_destroy_provider(hSensorProvider));

	nRet = sensor_destroy_provider(hSensorProvider);
	PRINT_RESULT_NORETURN(SENSOR_ERROR_NONE, nRet, "sensor_destroy_provider", SensorsGetError(nRet));

	return 0;
}

/** @} */
/** @} */
